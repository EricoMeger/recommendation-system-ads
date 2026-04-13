#include "../../../../include/rng/engines/algorithms/xorshift.hpp"

Xorshift::Xorshift(int seed) : RNG(seed), 
      state(static_cast<uint32_t>(seed == 0 ? 1 : seed)), 
      initialState(static_cast<uint32_t>(seed == 0 ? 1 : seed)) {}

uint64_t Xorshift::generate() {
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return static_cast<uint64_t>(state);
}

void Xorshift::reset() {
    state = initialState;
}
