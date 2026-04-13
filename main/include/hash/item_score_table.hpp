#pragma once
#include "../hash/hash_function.hpp"
#include "../heap/heap.hpp"
#include <vector>
#include <list>
#include <string>

struct ItemScoreEntry {
    int itemId;
    float scoreSum;
    int scoreCount;

    float avgScore() const { return scoreSum / scoreCount; }
};

class ItemScoreTable {
public:
    explicit ItemScoreTable(int tableSize, HashFunction* hashFn);

    void addScore(int itemId, float score);
    ItemScoreEntry* find(int itemId);

    // converte toda a tabela em vetord e ItemScore pro heap
    std::vector<ItemScore> toItemScores() const;

    int getTableSize() const { return tableSize; }
    int getElementCount() const { return elementCount; }
    int getCollisions() const { return collisions; }

private:
    int tableSize;
    int elementCount;
    int collisions;
    HashFunction* hashFn;

    std::vector<std::list<ItemScoreEntry>> buckets;

    int getIndex(int itemId);
};