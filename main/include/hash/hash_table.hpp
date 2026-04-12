#pragma once
#include "hash_function.hpp"
#include <vector>
#include <list>
#include <string>
#include <cstdint>

// representa uma avaliacao de um item por um usuario
struct Rating {
    int itemId;
    float score;
};

// cada entrada na tabela mapeia um usuario para suas avaliacoes
struct Entry {
    int userId;
    std::vector<Rating> ratings;
};

class HashTable {
public:
    explicit HashTable(int tableSize, HashFunction* hashFunc);

    void insert(int userId, int itemId, float score);
    std::vector<Rating>* find(int userId);
    bool hasRated(int userId, int itemId);

    // pra gerar as metricas dps
    int getCollisions() const  { return collisions; }
    // seria interessante fazer o rehashing, nao parece ser tao complicado
    // por agora vamos citar de trabalhos futuros, se der tempo implementamos
    float getLoadFactor() const { return (float)elementCount / tableSize; }
    int getTableSize() const   { return tableSize; }
    int getElementCount() const { return elementCount; }

private:
    int tableSize;
    int elementCount;
    int collisions;
    HashFunction* hashFunc;

    std::vector<std::list<Entry>> buckets; // encader

    int getIndex(int userId);
};