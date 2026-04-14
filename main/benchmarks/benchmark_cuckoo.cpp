#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include "../include/hash/hash_table.hpp"
#include "../include/hash/algorithms/fnv1a.hpp"
#include "../include/hash/algorithms/murmurhash.hpp"
#include "../include/cuckoo/cuckoo_filter.hpp"
#include "../include/rng/engines/algorithms/acorn.hpp"
#include "../include/rng/distributions/types/uniform_distribution.hpp"

struct CuckooBenchResult {
    double timeMs;
    int    duplicatesFound;
    int    hashTableQueries;
    double cuckooLoadFactor;
};

CuckooBenchResult benchWithCuckoo(int numUsers, int numItems, int numRatings, int seed) {
    FNV1a    fnv1;
    FNV1a    fnv2;
    MurmurHash murmur(0);
    HashTable table(numUsers * 2 + 1, &fnv1);
    CuckooFilter cuckoo(&fnv2, &murmur, numItems * 4, 4);
    ACORN engine(seed);
    UniformDistribution userDist(0, numUsers - 1);
    UniformDistribution itemDist(0, numItems - 1);

    int duplicates = 0, hashQueries = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numRatings; i++) {
        int userId = (int)userDist.sample(engine);
        int itemId = (int)itemDist.sample(engine);
        std::string key = std::to_string(userId) + ":" + std::to_string(itemId);

        if (cuckoo.query(key)) {
            hashQueries++;
            if (table.hasRated(userId, itemId)) { duplicates++; continue; }
        }
        cuckoo.insert(key);
        table.insert(userId, itemId, 3.5f);
    }

    auto end = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();

    return { ms, duplicates, hashQueries, cuckoo.loadFactor() };
}

CuckooBenchResult benchWithoutCuckoo(int numUsers, int numItems, int numRatings, int seed) {
    FNV1a fnv;
    HashTable table(numUsers * 2 + 1, &fnv);
    ACORN engine(seed);
    UniformDistribution userDist(0, numUsers - 1);
    UniformDistribution itemDist(0, numItems - 1);

    int duplicates = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numRatings; i++) {
        int userId = (int)userDist.sample(engine);
        int itemId = (int)itemDist.sample(engine);
        if (table.hasRated(userId, itemId)) { duplicates++; continue; }
        table.insert(userId, itemId, 3.5f);
    }

    auto end = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();

    return { ms, duplicates, 0, 0.0 };
}

void printResult(const std::string& label, const CuckooBenchResult& r) {
    std::cout << "  " << std::left << std::setw(16) << label
              << "  tempo: "       << std::fixed << std::setprecision(2) << std::setw(8) << r.timeMs << "ms"
              << "  duplicatas: "  << std::setw(6) << r.duplicatesFound;
    if (r.cuckooLoadFactor > 0)
        std::cout << "  cuckoo load: " << std::setprecision(3) << r.cuckooLoadFactor
                  << "  queries evitadas: " << (r.duplicatesFound - r.hashTableQueries);
    std::cout << "\n";
}

int main() {
    const int SEED = 42;
    const std::vector<std::tuple<int,int,int>> configs = {
        { 100,   50,   1000   },
        { 1000,  500,  10000  },
        { 10000, 5000, 100000 }
    };

    std::cout << "=== Benchmark Cuckoo Filter ===\n";

    for (auto& [users, items, ratings] : configs) {
        std::cout << "\n[ users=" << users << " items=" << items << " ratings=" << ratings << " ]\n";
        printResult("com cuckoo",    benchWithCuckoo(users, items, ratings, SEED));
        printResult("sem cuckoo",    benchWithoutCuckoo(users, items, ratings, SEED));
    }

    return 0;
}