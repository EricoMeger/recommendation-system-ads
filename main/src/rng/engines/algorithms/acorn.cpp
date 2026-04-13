#include "include/rng/engines/algorithms/acorn.hpp"
#include <cmath>

ACORN::ACORN(int seed, int order) : RNG(seed), order(order), modulus(1ULL << 60), state(order + 1, 0) {
    init(seed);
    initialState = state;
}

void ACORN::init(int seed) {
    // no paper é sugerido usar seeds "não óbvias", com o exemplo de seeds baseadas na sqrt de 2.
    // a ideia aq é seguir a sugestao. Pegamos o resto da divisao pelo módulo para ter ctz
    // q a seed n vai passar de 2^60;
    // a conversao para int64 é necessaria pq o ACORN so trabalha com inteiros
    uint64_t s = (uint64_t)(seed * std::sqrt(2)) % modulus;
    if (s % 2 == 0) s++; // no paper se pede uma seed ímpar
    state[0] = s;
    for (int i = 1; i <= order; i++)
        state[i] = 0;
}

uint64_t ACORN::generate() {
    for (int i = 1; i <= order; i++) {
        state[i] = (state[i] + state[i-1]) % modulus;
    }
    return state[order];
}

void ACORN::reset() {
    state = initialState;
}