#pragma once
#include "rng/engines/rng.hpp"
#include "rng/distributions/distribution.hpp"
#include "hash/hash_table.hpp"
#include "hash/hash_function.hpp"
#include "heap/heap.hpp"
#include "cuckoo/cuckoo_filter.hpp"
#include "hash/item_score_table.hpp"

#include <string>
#include <memory>

struct RecommenderConfig {
    int seed;
    int numUsers;
    int numItems;
    int numRatings;
    int topK;
    bool useCuckoo;
    std::string rngName;
    std::string hashName;
};

class Recommender {
public:
    Recommender(const RecommenderConfig& config, RNG* engine, HashFunction* hashFn, HashTable* hashTable,
                Heap* heap, CuckooFilter* cuckoo = nullptr);

    void run();

private:
    RecommenderConfig config;

    RNG* engine;
    HashFunction* hashFn;
    HashTable* hashTable;
    Heap* heap;
    CuckooFilter* cuckoo;

    void generateData();
    void printTrending();
    void printMetrics();
};