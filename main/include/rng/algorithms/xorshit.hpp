#pragma once
#include "../rng.hpp"
class Xorshift : public RNG {
private:
    int initialSeed;

public:    
    explicit Xorshift(int seed) : RNG(seed), initialSeed(seed) {}

    int generate() override;
    void reset() override;
    std::string getName() const override;
};