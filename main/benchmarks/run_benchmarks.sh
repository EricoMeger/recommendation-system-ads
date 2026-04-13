#!/bin/bash
set -e

CXX="g++ -std=c++17 -O2 -I."
SRC_COMMON="../src/hash/algorithms/fnv1a.cpp \
            ../src/hash/algorithms/murmurhash.cpp \
            ../src/hash/hash_table.cpp \
            ../src/hash/item_score_table.cpp \
            ../src/heap/algorithms/floyd.cpp \
            ../src/cuckoo/cuckoo_filter.cpp \
            ../src/rng/engines/algorithms/acorn.cpp \
            ../src/rng/engines/algorithms/xorshift.cpp \
            ../src/factory/factory.cpp \
            ../src/recommender.cpp"

echo "=== Compilando benchmarks ==="
$CXX benchmark_rng.cpp    $SRC_COMMON -o bench_rng
$CXX benchmark_hash.cpp   $SRC_COMMON -o bench_hash
$CXX benchmark_cuckoo.cpp $SRC_COMMON -o bench_cuckoo
$CXX benchmark_system.cpp $SRC_COMMON -o bench_system

echo ""
echo "=============================="
./bench_rng
echo ""
echo "=============================="
./bench_hash
echo ""
echo "=============================="
./bench_cuckoo
echo ""
echo "=============================="
./bench_system

echo ""
echo "=== Benchmarks concluidos ==="