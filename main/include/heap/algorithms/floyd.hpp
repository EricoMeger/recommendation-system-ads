#pragma once
#include "../heap.hpp"
#include <vector>
#include <string>

class Floyd : public Heap {
public:
    Floyd() = default;
    explicit Floyd(const std::vector<ItemScore>& values);

    void buildHeap(const std::vector<ItemScore>& values);
    void push(ItemScore value) override;
    void pop() override;
    ItemScore top() const override;
    bool empty() const override;
    size_t size() const override;
    std::string getName() const override;

    std::vector<ItemScore> topK(int k); // trending topics

private:
    std::vector<ItemScore> data;
    void heapifyUp(size_t index);
    void heapifyDown(size_t index);
};