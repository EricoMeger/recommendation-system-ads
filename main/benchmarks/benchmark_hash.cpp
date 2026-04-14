#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include "../include/hash/hash_table.hpp"
#include "../include/hash/algorithms/fnv1a.hpp"
#include "../include/hash/algorithms/murmurhash.hpp"
#include "../include/rng/engines/algorithms/acorn.hpp"
#include "../include/rng/distributions/types/uniform_distribution.hpp"

void benchHash(HashFunction* hashFn, int numUsers, int numItems, int numRatings, int seed) {
    HashTable table(numUsers * 2 + 1, hashFn);
    ACORN engine(seed);
    UniformDistribution userDist(0, numUsers - 1);
    UniformDistribution itemDist(0, numItems - 1);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numRatings; i++) {
        int userId = (int)userDist.sample(engine);
        int itemId = (int)itemDist.sample(engine);
        table.insert(userId, itemId, 3.5f);
    }

    auto end = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "  " << std::left << std::setw(12) << hashFn->getName()
              << "  tempo: "          << std::fixed << std::setprecision(2) << std::setw(8) << ms << "ms"
              << "  colisoes: "       << std::setw(6) << table.getCollisions()
              << "  fator de carga: " << std::setprecision(3) << table.getLoadFactor()
              << "  elementos: "      << table.getElementCount() << "\n";
}

int main() {
    const int SEED = 42;
    const std::vector<std::tuple<int,int,int>> configs = {
        { 10000,    5000,    100000},
        { 100000,   50000,   1000000},
        { 500000,   75000,   5000000},
    };

    std::cout << "=== Benchmark Hash ===\n";

    for (auto& [users, items, ratings] : configs) {
        std::cout << "\n[ users=" << users << " items=" << items << " ratings=" << ratings << " ]\n";

        FNV1a    fnv;
        MurmurHash murmur(SEED);

        benchHash(&fnv,    users, items, ratings, SEED);
        benchHash(&murmur, users, items, ratings, SEED);
    }

    return 0;
}