#include "../../include/rng/algorithms/acorn.hpp"

Acorn::Acorn(int seed) : RNG(seed) {}

int Acorn::generate() {
    // TODO
    return 0;
}

void Acorn::reset() {
    this->seed = this->initialSeed; // o this é redundante mas (acho que) deixa mais claro que estamos modificando o atributo da classe 
}

std::string Acorn::getName() const {
    return "ACORN";
}