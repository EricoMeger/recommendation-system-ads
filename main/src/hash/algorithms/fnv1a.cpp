#include "fnv1a.hpp"

std::string FNV1a::getName() const {
    return "FNV1a";
}

uint64_t FNV1a::hash(const std::string& input) {
    uint64_t h = OFFSET_BASIS;
    for (unsigned char byte : input) {
        h ^= byte;
        h *= PRIME;
    }
    return h;
}