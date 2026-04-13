#include "../include/recommender.hpp"
#include "../include/rng/distributions/types/uniform_distribution.hpp"
#include "../include/rng/distributions/types/normal_distribution.hpp"
#include "../include/heap/algorithms/floyd.hpp"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <unordered_map>

Recommender::Recommender(const RecommenderConfig& config, RNG* engine, HashFunction* hashFn,
                         HashTable* hashTable, Heap* heap, CuckooFilter* cuckoo): config(config), 
                         engine(engine), hashFn(hashFn), hashTable(hashTable), heap(heap), cuckoo(cuckoo) {}

void Recommender::generateData() {
    UniformDistribution userDist(0, config.numUsers - 1);
    UniformDistribution itemDist(0, config.numItems - 1);
    NormalDistribution  ratingDist(3.5, 1.0, 1.0, 5.0);

    ItemScoreTable itemScores(config.numItems * 2 + 1, hashFn);

    for (int i = 0; i < config.numRatings; i++) {
        int userId = (int)userDist.sample(*engine);
        int itemId = (int)itemDist.sample(*engine);
        float score  = (float)ratingDist.sample(*engine);

        std::string key = std::to_string(userId) + ":" + std::to_string(itemId);

        if (config.useCuckoo && cuckoo != nullptr) {
            if (cuckoo->query(key)) {
                if (hashTable->hasRated(userId, itemId)) continue;
            } else {
                cuckoo->insert(key);
            }
        } else {
            if (hashTable->hasRated(userId, itemId)) continue;
        }

        hashTable->insert(userId, itemId, score);
        itemScores.addScore(itemId, score);
    }

    // popula o heap com a media de cada item
    for (const auto& item : itemScores.toItemScores()) {
        heap->push(item);
    }
}

void Recommender::printTrending() {
    std::cout << "\n[ Trending Topics - Top " << config.topK << " ]\n";
    std::cout << std::string(40, '-') << "\n";

    auto topItems = dynamic_cast<Floyd*>(heap)->topK(config.topK);
    // cast seguro pois Floyd é a unica implementacao de Heap no projeto

    if (topItems.empty()) {
        std::cout << " Nenhum item avaliado.\n";
        return;
    }

    int rank = 1;
    for (const auto& item : topItems) {
        std::cout << "  " << rank++ << ". item #" << std::setw(4) << item.itemId
                  << "  media: " << std::fixed << std::setprecision(2) << item.avgScore
                  << "  avaliacoes: " << item.ratingCount << "\n";
    }
}

void Recommender::printMetrics() {
    std::cout << "\n[ Metricas ]\n";
    std::cout << std::string(40, '-') << "\n";

    std::cout << "  RNG: " << engine->getName() << " (seed=" << engine->getSeed() << ")\n";
    std::cout << "  Hash: " << hashFn->getName() << "\n";
    std::cout << "  Heap: " << heap->getName() << "\n";
    std::cout << "  Cuckoo: " << (config.useCuckoo ? "active" : "disabled") << "\n";

    std::cout << "\n  Hash Table:\n";
    std::cout << "  tamanho: " << hashTable->getTableSize() << "\n";
    std::cout << "  elementos: " << hashTable->getElementCount() << "\n";
    std::cout << "  colisoes: " << hashTable->getCollisions() << "\n";
    std::cout << "  fator de carga: " << std::fixed << std::setprecision(3)
              << hashTable->getLoadFactor() << "\n";

    if (config.useCuckoo && cuckoo != nullptr) {
        std::cout << "\n Cuckoo Filter:\n";
        std::cout << " fator de carga: " << std::fixed << std::setprecision(3)
                  << cuckoo->loadFactor() << "\n";
    }
}

void Recommender::run() {
    std::cout << "[ config ]\n";
    std::cout << std::string(40, '-') << "\n";
    std::cout << " seed: " << config.seed << "\n";
    std::cout << " usuarios: " << config.numUsers << "\n";
    std::cout << " itens: " << config.numItems << "\n";
    std::cout << " ratings: " << config.numRatings << "\n";
    std::cout << " topK: " << config.topK << "\n";

    auto start = std::chrono::high_resolution_clock::now();
    generateData();
    auto end = std::chrono::high_resolution_clock::now();

    double ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << "\n tempo de geracao: " << std::fixed << std::setprecision(2) << ms << "ms\n";

    printTrending();
    printMetrics();
}