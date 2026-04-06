#pragma once
#include <iostream>
#include <cstdint>
#include <string>
class RNG {
protected:
    int seed;

public:
    explicit RNG(int seed) : seed(seed) {}

    virtual uint64_t generate() = 0;
    virtual void reset() = 0;
    virtual std::string getName() const = 0;

    virtual int nextInt(int min, int max) { 
        return min + (generate() % (max - min + 1));
        // ao inves de ser so uma distribuicao uniforme, podemos considerar o teorema do limite central
        // parece ser fácil de implementar e gera numeros mais "factiveis", no sentido
        // q seria possivel gerar mais notas "médias" (2,3,4, pensando de 1 a 5) para um item, alem de ser possivel
        // "parametrizar" isso pra ele gerar notas mais altas ou mais baixas 
        // como o trabalho é pra ser algo mais simples mesmo acho q uniforme ta de boas
    }

    virtual double nextDouble() {
        return generate() / (double)UINT64_MAX;
    }

    int getSeed() const {
        return seed;
    }

    virtual ~RNG() = default;
};