#include "../../../include/rng/engines/algorithms/xorshift.hpp"

Xorshift::Xorshift(int seed) : RNG(seed), initialSeed(seed) {}

uint64_t Xorshift::generate() {
    uint32_t x = static_cast<uint32_t>(seed);
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    seed = static_cast<int>(x);
    return static_cast<uint64_t>(x);
}

void Xorshift::reset() {
    seed = initialSeed;
}
