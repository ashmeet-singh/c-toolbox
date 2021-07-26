#include <stdint.h>
#include <stddef.h>
#include <time.h>

void chacha20_block(uint32_t input_block[16]);

static uint32_t prng_seed[16];

uint32_t prng_int32(uint32_t min, uint32_t max)
{

    prng_seed[0] = prng_seed[0] + ((uint32_t)time(NULL));

    chacha20_block(prng_seed);

    return ((uint32_t)(((((uint64_t)prng_seed[0]) * (max - min + 1)) >> 32) + min));
}
