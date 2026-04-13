#include "../../include/hash/item_score_table.hpp"

ItemScoreTable::ItemScoreTable(int tableSize, HashFunction* hashFn): tableSize(tableSize),
      elementCount(0), collisions(0), hashFn(hashFn), buckets(tableSize) {}

int ItemScoreTable::getIndex(int itemId) {
    return hashFn->hash(std::to_string(itemId)) % tableSize;
}

void ItemScoreTable::addScore(int itemId, float score) {
    int index = getIndex(itemId);

    for (auto& entry : buckets[index]) {
        if (entry.itemId == itemId) {
            entry.scoreSum += score;
            entry.scoreCount += 1;
            return;
        }
    }

    if (!buckets[index].empty()) collisions++;

    buckets[index].push_back({ itemId, score, 1 });
    elementCount++;
}

ItemScoreEntry* ItemScoreTable::find(int itemId) {
    int index = getIndex(itemId);
    for (auto& entry : buckets[index]) {
        if (entry.itemId == itemId)
            return &entry;
    }
    return nullptr;
}

std::vector<ItemScore> ItemScoreTable::toItemScores() const {
    std::vector<ItemScore> result;
    for (const auto& bucket : buckets) {
        for (const auto& entry : bucket) {
            result.push_back({ entry.itemId, entry.avgScore(), entry.scoreCount });
        }
    }
    return result;
}