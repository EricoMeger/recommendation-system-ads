#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "../hash/hash_function.hpp"

class CuckooFilter {
public:
    CuckooFilter(HashFunction* hashIndex,
                 HashFunction* hashFingerprint,
                 size_t numBuckets,
                 size_t bucketSize,
                 uint8_t fingerprintBits = 8,
                 size_t maxKicks = 500);

    bool insert(const std::string& item);
    bool query(const std::string& item) const;
    bool remove(const std::string& item);
    double loadFactor() const;
    std::string getName() const;

private:
    uint8_t computeFingerprint(const std::string& item) const;
    size_t computeIndex1(const std::string& item) const;
    size_t computeIndex2(size_t index1, uint8_t fingerprint) const;

    bool containsInBucket(size_t index, uint8_t fingerprint) const;
    bool insertInBucket(size_t index, uint8_t fingerprint);
    bool removeFromBucket(size_t index, uint8_t fingerprint);

    std::vector<std::vector<uint8_t>> table_;
    HashFunction* hashIndex_;
    HashFunction* hashFingerprint_;
    size_t bucketSize_;
    size_t numBuckets_;
    uint8_t fingerprintBits_;
    size_t maxKicks_;
};
