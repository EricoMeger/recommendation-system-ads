#include "../../include/factory/factory.hpp"
#include "../../include/rng/engines/algorithms/acorn.hpp"
#include "../../include/rng/engines/algorithms/xorshift.hpp"
#include "../../include/hash/algorithms/fnv1a.hpp"
#include "../../include/hash/algorithms/murmurhash.hpp"
#include "../../include/hash/hash_table.hpp"
#include "../../include/heap/algorithms/floyd.hpp"
#include "../../include/cuckoo/cuckoo_filter.hpp"

RNG* ObjectFactory::createEngine(const RecommenderConfig& config) {
    if(config.rngName == "xorshift") {
        return new Xorshift(config.seed);
    }
    return new ACORN(config.seed);
}

HashFunction* ObjectFactory::createHashFunction(const RecommenderConfig& config) {
    if(config.hashName == "murmur") {
        return new MurmurHash(config.seed);
    }
    return new FNV1a();
}

HashTable* ObjectFactory::createHashTable(const RecommenderConfig& config, HashFunction* hashFn) {
    return new HashTable(config.numUsers * 2 + 1, hashFn);
}

Heap* ObjectFactory::createHeap() {
    return new Floyd();
}

CuckooFilter* ObjectFactory::createCuckoo(const RecommenderConfig& config) {
    if(!config.useCuckoo) return nullptr;
    return new CuckooFilter(new FNV1a(), new MurmurHash(67), config.numRatings * 8, 4);
}

Recommender* ObjectFactory::create(const RecommenderConfig& config) {
    RNG* engine = createEngine(config);
    HashFunction* hashFn = createHashFunction(config);
    HashTable* hashTable = createHashTable(config, hashFn);
    Heap* heap = createHeap();
    CuckooFilter* cuckoo = createCuckoo(config);

    return new Recommender(config, engine, hashFn, hashTable, heap, cuckoo);
}