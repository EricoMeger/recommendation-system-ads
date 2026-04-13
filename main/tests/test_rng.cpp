#include "include/rng/engines/algorithms/acorn.hpp"
#include "include/rng/engines/algorithms/xorshift.hpp"
#include "include/rng/distributions/types/uniform_distribution.hpp"
#include "include/rng/distributions/types/normal_distribution.hpp"

#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

static void expect(bool condition, const char* msg) {
    if (!condition) {
        std::cout << "[FAIL] " << msg << "\n";
        std::exit(1);
    }
}

int main() {
    ACORN a1(67), a2(67);
    for (int i = 0; i < 200; ++i) {
        expect(a1.generate() == a2.generate(), "ACORN must be reprodutible");
    }

    Xorshift x1(67), x2(67);
    for (int i = 0; i < 200; ++i) {
        expect(x1.generate() == x2.generate(), "Xorshift must be reprodutible");
    }

    Xorshift xr(99);
    std::vector<uint64_t> seqX;
    for (int i = 0; i < 50; ++i) seqX.push_back(xr.generate());
    xr.reset();
    for (int i = 0; i < 50; ++i) {
        expect(seqX[i] == xr.generate(), "Xorshift reset must restore sequence");
    }

    ACORN ar(99);
    std::vector<uint64_t> seqA;
    for (int i = 0; i < 50; ++i) seqA.push_back(ar.generate());
    ar.reset();
    for (int i = 0; i < 50; ++i) {
        expect(seqA[i] == ar.generate(), "ACORN reset must restore sequence");
    }

    Xorshift xu(123);
    UniformDistribution ud(0, 9);
    std::array<int, 10> freq{};
    const int nUniform = 20000;
    for (int i = 0; i < nUniform; ++i) {
        int v = static_cast<int>(ud.sample(xu));
        expect(v >= 0 && v <= 9, "UniformDistribution outside the range");
        freq[v]++;
    }

    const double expected = nUniform / 10.0;
    for (int c : freq) {
        expect(std::fabs(c - expected) <= expected * 0.30, "UniformDistribution very biased");
    }

    ACORN an(321);
    NormalDistribution nd(3.5, 1.0, 1.0, 5.0);
    const int nNormal = 20000;
    double sum = 0.0;
    for (int i = 0; i < nNormal; ++i) {
        double v = nd.sample(an);
        expect(v >= 1.0 && v <= 5.0, "NormalDistribution outside the clamp [1,5]");
        sum += v;
    }
    double mean = sum / nNormal;
    expect(std::fabs(mean - 3.5) < 0.30, "Mean of NormalDistribution outside the expected");

    std::cout << "[OK] test_rng\n";
    return 0;
}