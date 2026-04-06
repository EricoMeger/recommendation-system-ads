#pragma once

#include "../rng.hpp"

class Xorshift : public RNG {
private:
    int initialSeed;

public:
    explicit Xorshift(int seed);

    uint64_t generate() override;
    void reset() override;
    std::string getName() const override;
};