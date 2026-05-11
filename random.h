#pragma once

#include <cstdint>

class PRNG {
    public:
    PRNG() : keys()
}
#include <inttypes.h>

uint64_t rotate(uint64_t v, uint8_t s);
uint64_t RandomUInt64();
void SeedRandom(uint64_t seed);
uint64_t RandomMagic();
