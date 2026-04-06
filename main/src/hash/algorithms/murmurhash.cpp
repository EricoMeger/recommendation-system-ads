#include "../../../include/hash/algorithms/murmurhash.hpp"

static inline uint32_t murmur_32_scramble(uint32_t k, int8_t r)
{
	return ( k << r) | ( k >> (32 - r));
}

uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed)
{
	const uint8_t* data = (const uint8_t*)key;
	const int nblocks = len / 4;
	uint32_t h1 = seed;

	const uint32_t c1 = 0xcc9e2d51;
	const uint32_t c2 = 0x1b873593;

	//----------body----------
	const uint32_t* blocks = (const uint32_t*)(data);

	for (int i = 0; i < nblocks; i++)
	{
		uint32_t k1 = blocks[i];

		k1 *= c1;
		k1 = murmur_32_scramble(k1, 15);
		k1 *= c2;

		h1 ^= k1;
		h1 = murmur_32_scramble(h1, 13);
		h1 = h1 * 5 + 0xe6546b64;
	}
	//----------tail----------
	const uint8_t* tail = (const uint8_t*)(data + nblocks * 4);
	uint32_t k1 = 0;

	switch(len & 3){
		case 3: k1 ^= tail[2] << 16;
		case 2: k1 ^= tail[1] << 8;
		case 1: k1 ^= tail[0];
		 		k1 *= c1; k1 = murmur_32_scramble(k1, 15); k1 *= c2; h1 ^= k1;
	}

	h1 ^= len;
    h1 ^= h1 >> 16;
    h1 *= 0x85ebca6b;
    h1 ^= h1 >> 13;
    h1 *= 0xc2b2ae35;
    h1 ^= h1 >> 16;

	return h1;
}
