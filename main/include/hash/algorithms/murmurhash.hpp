#pragma once

#include <cstddef>
#include <cstdint>

static inline uint32_t murmur_32_scramble(uint32_t k);
uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed);
