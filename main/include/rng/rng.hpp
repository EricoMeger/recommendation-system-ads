#pragma once
#include <iostream>
class RNG {
protected:
    int seed;
    
public:
    explicit RNG(int seed) : seed(seed) {}

    virtual int generate() = 0; // = 0 vai forçar que classe filha implemente esse método
    // int talvez n seja uma boa tipagem, talvez considerar uint32? pesquisar
    virtual void reset() = 0; // resetar a seed sem precisar criar outro objeto (pensando nos tests)

    virtual std::string getName() const = 0;

    virtual int uniform_int_distribution() = 0; //pesquisar como retornar essa distribuicao, pensando em geracao de rating talvez usar um tipo de distribuicao q n seja uniforme
    virtual double uniform_real_distribution() = 0; //ditto

    int getSeed() const {
        return seed;
    }

    virtual ~RNG() = default;
};