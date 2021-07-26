#include <stdint.h>
#include <stddef.h>
#include <time.h>

void chacha20_block(uint32_t input_block[16]);

static uint32_t prng_seed[16];

uint32_t prng_int32(uint32_t min, uint32_t max)
{
    time_t ts = time(NULL);

    if (ts == (time_t)(-1))
    {
        prng_seed[0] = 0xffffffff;
    }
    else
    {
        prng_seed[0] = (uint32_t)ts;
    }

    chacha20_block(prng_seed);

    return ((uint32_t)(((((uint64_t)prng_seed[0]) * (max - min + 1)) >> 32) + min));
}
