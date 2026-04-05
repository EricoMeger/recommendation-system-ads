#pragma once
#include "../rng.hpp"
#include <vector>
class ACORN : public RNG {
public:
    explicit ACORN(int seed, int order = 12);

    uint64_t generate() override;
    void reset() override;
    std::string getName() const override;

    // sobrescreve pq o cap do ACORN é o modulus (2^60) e não o uint max
    double nextDouble() override {
        return (double)generate() / (double)modulus;
    }

private:
    int order;
    uint64_t modulus;
    std::vector<uint64_t> state;
    std::vector<uint64_t> initialState;

    void init(int seed);
};