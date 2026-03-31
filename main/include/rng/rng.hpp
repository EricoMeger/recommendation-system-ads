#pragma once

class RNG {
public:
    explicit RNG(int seed) {
        this->seed = seed;
    }

    virtual int generate() = 0; // = 0 vai forçar que classe filha implemente esse método
    // int talvez n seja uma boa tipagem, talvez considerar uint32? pesquisar
    virtual void reset() = 0; // resetar a seed sem precisar criar outro objeto (pensando nos tests)

    virtual std::string getName() const = 0;

    // essas duas n vao ser virtuais pq a implementação vai ser a mesma independente do gerador 
    int uniform_int_distribution(int min, int max) {
        return generate(); //pesquisar como retornar essa distribuicao, pensando em geracao de rating talvez usar um tipo de distribuicao q n seja uniforme
    }

    double uniform_real_distribution() {
        return generate(); // ditto
    }

    int getSeed() const {
        return seed;
    }

    virtual ~RNG() = default;

protected:
    int seed;
};