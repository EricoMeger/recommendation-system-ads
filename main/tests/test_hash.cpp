#include "include/hash/algorithms/fnv1a.hpp"
#include "include/hash/algorithms/murmurhash.hpp"
#include "include/hash/hash_table.hpp"
#include "include/hash/item_score_table.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>

static void expect(bool cond, const char* msg) {
    if (!cond) {
        std::cerr << "[FAIL] " << msg << "\n";
        std::exit(1);
    }
}

static void runHashSuite(HashFunction& hashFn, const char* hashName) {
    std::cout << "[INFO] Running hash suite with " << hashName << "\n";

    // insert/find/hasRated
    HashTable table(11, &hashFn);
    table.insert(1, 10, 4.5f);
    table.insert(1, 11, 3.0f);
    table.insert(2, 10, 2.5f);

    auto* ratings1 = table.find(1);
    expect(ratings1 != nullptr, "find(user=1) deve existir");
    expect(ratings1->size() == 2, "user=1 deve ter 2 ratings");
    expect(table.hasRated(1, 10), "hasRated(1,10) deve ser true");
    expect(!table.hasRated(1, 99), "hasRated(1,99) deve ser false");

    // colisões (forçadas)
    HashTable tiny(1, &hashFn);
    tiny.insert(1, 1, 5.0f);
    tiny.insert(2, 1, 4.0f); // mesma posição
    expect(tiny.getCollisions() == 1, "colisão esperada em tabela tamanho 1");
    expect(tiny.getElementCount() == 2, "2 usuários distintos esperados");

    // ItemScoreTable: agregação por item
    ItemScoreTable scores(7, &hashFn);
    scores.addScore(42, 4.0f);
    scores.addScore(42, 2.0f);
    scores.addScore(7, 5.0f);

    auto* e42 = scores.find(42);
    expect(e42 != nullptr, "item 42 deve existir");
    expect(e42->scoreCount == 2, "item 42 deve ter 2 avaliações");
    expect(std::fabs(e42->avgScore() - 3.0f) < 1e-6, "média do item 42 incorreta");

    auto all = scores.toItemScores();
    expect(all.size() == 2, "toItemScores deve retornar 2 itens");
}

int main() {
    FNV1a fnv1a;
    MurmurHash murmur(42);

    runHashSuite(fnv1a, "FNV1a");
    runHashSuite(murmur, "MurmurHash");

    std::cout << "[OK] test_hash\n";
    return 0;
}