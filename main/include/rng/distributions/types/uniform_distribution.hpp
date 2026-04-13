#pragma once
#include "../distribution.hpp"
#include <cstdint>

class UniformDistribution : public Distribution {
public:
    explicit UniformDistribution(int min, int max) : min(min), max(max) {
        if(min > max) {
            throw std::invalid_argument("max should be greater than min");
        }
    }
    // distribuicao uniforme vai ser usada so para gerar os ids, entao o sample
    // retorna semmpre um int mesmo
    // a tipagem double é pra menter consistente com a classe
    double sample(RNG& engine) override {
        int range = max - min + 1;
        return min + static_cast<int>(engine.generate() % static_cast<uint64_t>(range));
    }

    std::string getName() const override { 
        return "Uniform"; 
    }

private:
    int min, max;
};