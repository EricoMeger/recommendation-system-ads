#pragma once
#include "../distribution.hpp"
#include <cstdint>

class UniformDistribution : public Distribution {
public:
    explicit UniformDistribution(int min, int max) : min(min), max(max) {}
    // distribuicao uniforme vai ser usada so para gerar os ids, entao o sample
    // retorna semmpre um int mesmo
    // a tipagem double é pra menter consistente com a classe
    double sample(RNG& engine) override {
        return min + (engine.nextInt() % (max - min + 1));
    }

    std::string getName() const override { 
        return "Uniform"; 
    }

private:
    int min, max;
};