#pragma once
#include <string>
#include <cstdint>

struct ItemScore {
    int itemId;
    float avgScore;
    int ratingCount;

    // operadores para comparacao no heap
    bool operator>(const ItemScore& other) const { return avgScore > other.avgScore; }
    bool operator>=(const ItemScore& other) const { return avgScore >= other.avgScore; }
};

class Heap {
public:
    virtual void push(ItemScore value) = 0;
    virtual void pop() = 0;
    virtual ItemScore top() const = 0;
    virtual bool empty() const = 0;
    virtual size_t size() const = 0;
    virtual std::string getName() const = 0;
    virtual ~Heap() = default;
};