#include "../../../include/rng/algorithms/xorshift.hpp"

Xorshift::Xorshift(int seed) : RNG(seed), initialSeed(seed) {}

int Xorshift::generate() {
    uint32_t x = static_cast<uint32_t>(seed);
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    seed = static_cast<int>(x);
    return seed;
}

void Xorshift::reset() {
    seed = initialSeed;
}

std::string Xorshift::getName() const {
    return "XORSHIFT";
}