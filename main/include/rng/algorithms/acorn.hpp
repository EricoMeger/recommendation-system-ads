#pragma once
#include "../rng.hpp"

class Acorn : public RNG {
private:
    int initialSeed;
    
public:
    explicit Acorn(int seed) : RNG(seed), initialSeed(seed) {}

    int generate() override;
    void reset() override;
    std::string getName() const override;
}

