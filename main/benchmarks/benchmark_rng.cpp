#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <cmath>
#include "../include/rng/engines/algorithms/acorn.hpp"
#include "../include/rng/engines/algorithms/xorshift.hpp"

struct BenchResult {
    std::string name;
    double timeMs;
    double mean;
    double stddev;
};

BenchResult benchRNG(RNG& engine, int n) {
    auto start = std::chrono::high_resolution_clock::now();

    double sum = 0, sumSq = 0;
    for (int i = 0; i < n; i++) {
        double v = engine.nextDouble();
        sum   += v;
        sumSq += v * v;
    }

    auto end = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();

    double mean   = sum / n;
    double stddev = std::sqrt(sumSq / n - mean * mean);

    return { engine.getName(), ms, mean, stddev };
}

void printResult(const BenchResult& r, int n) {
    std::cout << "  " << std::left << std::setw(12) << r.name
              << "  tempo: " << std::fixed << std::setprecision(2) << std::setw(8) << r.timeMs << "ms"
              << "  media: " << std::setprecision(4) << r.mean
              << "  stddev: " << r.stddev
              << "  ops/ms: " << (int)(n / r.timeMs) << "\n";
}

int main() {
    const int SEED = 42;
    const std::vector<int> sizes = { 10000, 100000, 1000000 };

    std::cout << "=== Benchmark RNG ===\n";

    for (int n : sizes) {
        std::cout << "\n[ " << n << " amostras ]\n";

        ACORN   acorn(SEED);
        Xorshift xorshift(SEED);

        printResult(benchRNG(acorn,    n), n);
        printResult(benchRNG(xorshift, n), n);
    }

    return 0;
}