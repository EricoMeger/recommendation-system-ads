#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include "../include/factory/factory.hpp"

struct SystemBenchResult {
    std::string rng;
    std::string hash;
    bool        cuckoo;
    int         users, items, ratings;
    double      timeMs;
    int         collisions;
    float       loadFactor;
};

SystemBenchResult benchSystem(const RecommenderConfig& config) {
    auto start = std::chrono::high_resolution_clock::now();

    Recommender* rec = ObjectFactory::create(config);
    rec->run();

    auto end = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();

    delete rec;

    return { config.rngName, config.hashName, config.useCuckoo,
             config.numUsers, config.numItems, config.numRatings, ms, 0, 0 };
}

int main() {
    const int SEED = 67;

    const std::vector<std::tuple<int,int,int>> sizes = {
        { 10000,    5000,    100000},
        { 100000,   50000,   1000000},
        { 500000,   75000,   5000000},
    };

    const std::vector<std::pair<std::string,std::string>> algos = {
        { "acorn",    "fnv1a"  },
        { "acorn",    "murmur" },
        { "xorshift", "fnv1a"  },
        { "xorshift", "murmur" }
    };

    std::cout << "=== Benchmark Sistema Completo ===\n";

    for (auto& [users, items, ratings] : sizes) {
        std::cout << "\n[ users=" << users
                  << " items="   << items
                  << " ratings=" << ratings << " ]\n";

        std::cout << "  " << std::left
                  << std::setw(12) << "rng"
                  << std::setw(10) << "hash"
                  << std::setw(10) << "cuckoo"
                  << "tempo\n";
        std::cout << "  " << std::string(44, '-') << "\n";

        for (auto& [rng, hash] : algos) {
            for (bool cuckoo : { false, true }) {
                RecommenderConfig config;
                config.seed       = SEED;
                config.numUsers   = users;
                config.numItems   = items;
                config.numRatings = ratings;
                config.topK       = 5;
                config.rngName    = rng;
                config.hashName   = hash;
                config.useCuckoo  = cuckoo;

                auto start = std::chrono::high_resolution_clock::now();
                Recommender* rec = ObjectFactory::create(config);
                rec->run();
                auto end = std::chrono::high_resolution_clock::now();
                double ms = std::chrono::duration<double, std::milli>(end - start).count();
                delete rec;

                std::cout << "  " << std::left
                          << std::setw(12) << rng
                          << std::setw(10) << hash
                          << std::setw(10) << (cuckoo ? "sim" : "nao")
                          << std::fixed << std::setprecision(2) << ms << "ms\n";
            }
        }
    }

    return 0;
}