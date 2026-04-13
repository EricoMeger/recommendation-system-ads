#pragma once
#include "../recommender.hpp"
#include "../rng/engines/rng.hpp"
#include "../hash/hash_function.hpp"
#include "../hash/hash_table.hpp"
#include "../heap/heap.hpp"
#include "../cuckoo/cuckoo_filter.hpp"

class ObjectFactory {
public:
    static RNG* createEngine(const RecommenderConfig& config);
    static HashFunction* createHashFunction(const RecommenderConfig& config);
    static HashTable* createHashTable(const RecommenderConfig& config, HashFunction* hashFn);
    static Heap* createHeap();
    static CuckooFilter* createCuckoo(const RecommenderConfig& config);
    static Recommender* create(const RecommenderConfig& config);
};