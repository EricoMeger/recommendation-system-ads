#include "hash/algorithms/fnv1a.hpp"

uint64_t FNV1a::hash(const std::string& input) {
    uint64_t h = OFFSET_BASIS;
    for (unsigned char byte : input) {
        h ^= byte;
        h *= PRIME;
    }
    return h;
}