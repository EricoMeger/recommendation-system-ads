#pragma once

#include "../heap.hpp"

#include <cstdint>
#include <string>
#include <vector>

class Floyd : public Heap {
public:
    Floyd() = default;
    explicit Floyd(const std::vector<uint64_t>& values);

    void buildHeap(const std::vector<uint64_t>& values);

    void push(uint64_t value) override;
    void pop() override;
    uint64_t top() const override;
    bool empty() const override;
    size_t size() const override;
    std::string getName() const override;

private:
    std::vector<uint64_t> data;

    void heapifyUp(size_t index);
    void heapifyDown(size_t index);
};