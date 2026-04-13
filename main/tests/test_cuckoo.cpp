#include "include/cuckoo/cuckoo_filter.hpp"
#include "include/hash/algorithms/fnv1a.hpp"
#include "include/hash/algorithms/murmurhash.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

static void expect(bool cond, const char* msg) {
    if (!cond) {
        std::cerr << "[FAIL] " << msg << "\n";
        std::exit(1);
    }
}

int main() {
    FNV1a indexHash;
    MurmurHash fpHash(67);
    CuckooFilter cf(&indexHash, &fpHash, 256, 4, 8, 200);

    // insert/query/remove
    expect(cf.insert("u1:i1"), "insert u1:i1 deve funcionar");
    expect(cf.query("u1:i1"), "query u1:i1 deve ser true");
    expect(cf.remove("u1:i1"), "remove u1:i1 deve ser true");
    expect(!cf.query("u1:i1"), "query u1:i1 após remove deve ser false (na prática esperada)");

    // popular
    for (int i = 0; i < 500; ++i) {
        cf.insert("in:" + std::to_string(i));
    }

    // false positives (tenta fazer query em chves q n existem)
    int fp = 0;
    const int queries = 2000;
    for (int i = 0; i < queries; ++i) {
        if (cf.query("out:" + std::to_string(i))) {
            fp++;
        }
    }

    double fpr = static_cast<double>(fp) / queries;
    std::cout << "false_positive_rate=" << fpr << "\n";
    expect(fpr < 0.35, "false positive rate acima do limite de sanity check");

    double lf = cf.loadFactor();
    expect(lf >= 0.0 && lf <= 1.0, "loadFactor deve estar em [0,1]");

    std::cout << "[OK] test_cuckoo\n";
    return 0;
}