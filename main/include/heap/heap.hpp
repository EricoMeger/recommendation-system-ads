#pragma once
#include <iostream>
#include <cstdint>
#include <string>

class Heap {
public:
    virtual void push(uint64_t value) = 0;
    virtual void pop() = 0;
    virtual uint64_t top() const = 0;
    virtual bool empty() const = 0;
    virtual size_t size() const = 0;
    virtual std::string getName() const = 0;
    virtual ~Heap() = default;
};
