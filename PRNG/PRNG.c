#include <stdint.h>
#include <time.h>

void chacha20_block(uint32_t input_block[16]);

static uint32_t prng_seed[16];

void refresh_prng_seed()
{
    time_t t = time(NULL);

    if (t == (time_t)(-1))
    {
        prng_seed[0] = 0xffffffff;
    }
    else
    {
        prng_seed[0] = (uint32_t)t;
    }

    chacha20_block(prng_seed);
}

uint32_t prng_uint32(uint32_t min, uint32_t max)
{
    refresh_prng_seed();

    return (((((uint64_t)prng_seed[7]) * (max - min + 1)) >> 32) + min);
}