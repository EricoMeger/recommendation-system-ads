#pragma once
#include "../hash_function.hpp"
#include <string>
#include <cstdint>

class FNV1a : public HashFunction {
public:
    uint64_t hash(const std::string& input) override;
    std::string getName() const override;

private:
   /* from wikipedia
    algorithm fnv-1a is
    hash := FNV_offset_basis

    for each byte_of_data to be hashed do
        hash := hash XOR byte_of_data
        hash := hash × FNV_prime

    return hash 

    The FNV_offset_basis is the 64-bit value: 14695981039346656037 (in hex, 0xcbf29ce484222325).
    The FNV_prime is the 64-bit value 1099511628211 (in hex, 0x100000001b3).
   */
    static constexpr uint64_t OFFSET_BASIS = 14695981039346656037ULL;
    static constexpr uint64_t PRIME        = 1099511628211ULL;
};