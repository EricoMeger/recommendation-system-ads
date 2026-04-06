#include "../../../include/hash/algorithms/murmurhash.hpp"

static inline uint32_t murmur_32_scramble(uint32_t k)
{
	return k;
}

uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed)
{
	(void)key;
	(void)len;
	(void)seed;
	return 0;
}
