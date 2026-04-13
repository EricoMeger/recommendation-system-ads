#include "../../include/cuckoo/cuckoo_filter.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace {
uint8_t sanitizeFingerprintBits(uint8_t bits)
{
    if (bits == 0) {
        return 1;
    }

    if (bits > 8) {
        return 8;
    }

    return bits;
}

size_t sanitizeSize(size_t value)
{
    return value == 0 ? 1 : value;
}
}

CuckooFilter::CuckooFilter(HashFunction* hashIndex,
                           HashFunction* hashFingerprint,
                           size_t numBuckets,
                           size_t bucketSize,
                           uint8_t fingerprintBits,
                           size_t maxKicks)
        : hashIndex_(hashIndex), hashFingerprint_(hashFingerprint),
      bucketSize_(sanitizeSize(bucketSize)),
      numBuckets_(sanitizeSize(numBuckets)),
      fingerprintBits_(sanitizeFingerprintBits(fingerprintBits)),
      maxKicks_(sanitizeSize(maxKicks))
{
    if (!hashIndex_ || !hashFingerprint_) {
        throw std::invalid_argument("CuckooFilter requires two hash functions");
    }

    table_.assign(numBuckets_, std::vector<uint8_t>(bucketSize_, 0));
}

uint8_t CuckooFilter::computeFingerprint(const std::string& item) const
{
    const uint64_t modulo = 1ULL << fingerprintBits_;
    const uint8_t fingerprint = static_cast<uint8_t>(hashFingerprint_->hash(item) % modulo);
    return fingerprint == 0 ? 1 : fingerprint;
}

size_t CuckooFilter::computeIndex1(const std::string& item) const
{
    return hashIndex_->hash(item) % numBuckets_;
}

size_t CuckooFilter::computeIndex2(size_t index1, uint8_t fingerprint) const
{
    return (index1 ^ static_cast<size_t>(fingerprint)) % numBuckets_;
}

bool CuckooFilter::containsInBucket(size_t index, uint8_t fingerprint) const
{
    const auto& bucket = table_[index];
    return std::find(bucket.begin(), bucket.end(), fingerprint) != bucket.end();
}

bool CuckooFilter::insertInBucket(size_t index, uint8_t fingerprint)
{
    auto& bucket = table_[index];
    auto emptySlot = std::find(bucket.begin(), bucket.end(), 0);

    if (emptySlot == bucket.end()) {
        return false;
    }

    *emptySlot = fingerprint;
    return true;
}

bool CuckooFilter::removeFromBucket(size_t index, uint8_t fingerprint)
{
    auto& bucket = table_[index];
    auto it = std::find(bucket.begin(), bucket.end(), fingerprint);

    if (it == bucket.end()) {
        return false;
    }

    *it = 0;
    return true;
}

bool CuckooFilter::insert(const std::string& item)
{
    const uint8_t fingerprint = computeFingerprint(item);
    const size_t index1 = computeIndex1(item);
    const size_t index2 = computeIndex2(index1, fingerprint);

    if (insertInBucket(index1, fingerprint) || insertInBucket(index2, fingerprint)) {
        return true;
    }

    size_t currentIndex = index1;
    uint8_t currentFingerprint = fingerprint;

    for (size_t kick = 0; kick < maxKicks_; ++kick) {
        const size_t slot = kick % bucketSize_;
        std::swap(currentFingerprint, table_[currentIndex][slot]);
        currentIndex = computeIndex2(currentIndex, currentFingerprint);

        if (insertInBucket(currentIndex, currentFingerprint)) {
            return true;
        }
    }

    return false;
}

bool CuckooFilter::query(const std::string& item) const
{
    const uint8_t fingerprint = computeFingerprint(item);
    const size_t index1 = computeIndex1(item);
    const size_t index2 = computeIndex2(index1, fingerprint);

    return containsInBucket(index1, fingerprint) || containsInBucket(index2, fingerprint);
}

bool CuckooFilter::remove(const std::string& item)
{
    const uint8_t fingerprint = computeFingerprint(item);
    const size_t index1 = computeIndex1(item);
    const size_t index2 = computeIndex2(index1, fingerprint);

    return removeFromBucket(index1, fingerprint) || removeFromBucket(index2, fingerprint);
}

double CuckooFilter::loadFactor() const
{
    size_t occupied = 0;
    for (const auto& bucket : table_) {
        occupied += std::count_if(bucket.begin(), bucket.end(), [](uint8_t value) { return value != 0; });
    }

    const size_t capacity = numBuckets_ * bucketSize_;
    return static_cast<double>(occupied) / static_cast<double>(capacity);
}

std::string CuckooFilter::getName() const
{
    return "CuckooFilter with " + hashIndex_->getName() + " and " + hashFingerprint_->getName();
}
