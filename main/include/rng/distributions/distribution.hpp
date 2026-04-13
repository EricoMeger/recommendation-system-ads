#pragma once
#include "../engines/rng.hpp"

class Distribution {
public:
    virtual double sample(RNG& engine) = 0;
    virtual std::string getName() const = 0;
    virtual ~Distribution() = default;
};