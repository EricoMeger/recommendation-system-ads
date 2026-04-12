#pragma once
#include "../distribution.hpp"
#include <algorithm>
#include <cmath>
#include <string>

class NormalDistribution : public Distribution {
public:
    // mean: centro das notas 
    // stddev: dispersão 
    // min/max: limites da escala 
    // cltSamples: qtde de uniformes somadas (12 eh o padrao)
    explicit NormalDistribution(double mean = 3.5, double stddev = 1.0, double min = 1.0,
        double max = 5.0, int cltSamples = 12 ) : mean(mean), stddev(stddev), min(min), 
        max(max), cltSamples(cltSamples) {}

    double sample(RNG& engine) override {
        double sum = 0.0;
        for (int i = 0; i < cltSamples; ++i) {
            sum += engine.nextDouble();
        }

        const double n = static_cast<double>(cltSamples);
        const double z = (sum - n * 0.5) / std::sqrt(n / 12.0);

        double value = mean + z * stddev;

        value = std::clamp(value, min, max);

        return value;
    }

    std::string getName() const override {
        return "Teorema do Limite Central";
    }

private:
    double mean;
    double stddev;
    double min;
    double max;
    int cltSamples;
};