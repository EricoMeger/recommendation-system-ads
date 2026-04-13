#include "include/heap/algorithms/floyd.hpp"

#include <cstdlib>
#include <iostream>
#include <vector>

static void expect(bool cond, const char* msg) {
    if (!cond) {
        std::cerr << "[FAIL] " << msg << "\n";
        std::exit(1);
    }
}

int main() {
    std::vector<ItemScore> items = {
        {1, 4.2f, 10},
        {2, 3.9f, 8},
        {3, 4.8f, 2},
        {4, 4.5f, 6}
    };

    Floyd heap(items);
    expect(!heap.empty(), "heap não deve estar vazio");
    expect(heap.top().itemId == 3, "top inicial deve ser item 3 (4.8)");

    heap.push({5, 5.0f, 1});
    expect(heap.top().itemId == 5, "top após push deve ser item 5 (5.0)");

    heap.pop();
    expect(heap.top().itemId == 3, "top após pop deve voltar ao item 3");

    auto top3 = heap.topK(3);
    expect(top3.size() == 3, "topK(3) deve retornar 3 itens");
    expect(top3[0].avgScore >= top3[1].avgScore, "topK deve estar ordenado");
    expect(top3[1].avgScore >= top3[2].avgScore, "topK deve estar ordenado");

    std::cout << "[OK] test_heap\n";
    return 0;
}