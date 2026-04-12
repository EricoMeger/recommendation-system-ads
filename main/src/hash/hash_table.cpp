#include "hash_table.hpp"

HashTable::HashTable(int tableSize, HashFunction* hashFunc)
    : tableSize(tableSize), elementCount(0), collisions(0),
      hashFunc(hashFunc), buckets(tableSize) {}

int HashTable::getIndex(int userId) {
    std::string key = std::to_string(userId);
    return hashFunc->hash(key) % tableSize;
}

void HashTable::insert(int userId, int itemId, float score) {
    int index = getIndex(userId);

    // user ja existe no bucket?
    for (auto& entry : buckets[index]) {
        if (entry.userId == userId) {
            entry.ratings.push_back({itemId, score});
            return;
        }
    }

    // novo usuario indo para um bucket que jja tem um usuario, colisao
    if (!buckets[index].empty()) collisions++;

    Entry newEntry;
    newEntry.userId = userId;
    newEntry.ratings.push_back({itemId, score});
    buckets[index].push_back(newEntry);
    elementCount++;
}

std::vector<Rating>* HashTable::find(int userId) {
    int index = getIndex(userId);
    for (auto& entry : buckets[index]) {
        if (entry.userId == userId)
            return &entry.ratings;
    }
    return nullptr; // usuario nao encontrado
}

bool HashTable::hasRated(int userId, int itemId) {
    std::vector<Rating>* ratings = find(userId);
    if (ratings == nullptr) return false;
    for (const auto& r : *ratings) {
        if (r.itemId == itemId) return true;
    }
    return false;
}