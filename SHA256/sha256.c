#include <stdint.h>

#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define ROTL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

#define CH(x, y, z) (((x) & (y)) ^ ((~(x)) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define BSIG0(x) (ROTR((x), 2) ^ ROTR((x), 13) ^ ROTR((x), 22))
#define BSIG1(x) (ROTR((x), 6) ^ ROTR((x), 11) ^ ROTR((x), 25))
#define SSIG0(x) (ROTR((x), 7) ^ ROTR((x), 18) ^ ((x) >> 3))
#define SSIG1(x) (ROTR((x), 17) ^ ROTR((x), 19) ^ ((x) >> 10))

uint32_t SHA256_CR[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

uint32_t SHA256_SR[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

struct sha256_state
{
    uint8_t unused_bytes[64];
    uint8_t unused_bytes_count;
    uint64_t used_bytes_count;
    uint32_t hash[8];
};

void sha256_process_block(uint32_t input_block[16], uint32_t previous_hash[8], uint32_t next_hash[8])
{
    register uint32_t a;
    register uint32_t b;
    register uint32_t c;
    register uint32_t d;
    register uint32_t e;
    register uint32_t f;
    register uint32_t g;
    register uint32_t h;
    register uint32_t T1;
    register uint32_t T2;

    uint32_t B[64];

    uint8_t i;

    for (i = 0; i < 16; i++)
    {
        B[i] = input_block[i];
    }
    for (i = 16; i < 64; i++)
    {
        B[i] = SSIG1(B[i - 2]) + B[i - 7] + SSIG0(B[i - 15]) + B[i - 16];
    }

    a = previous_hash[0];
    b = previous_hash[1];
    c = previous_hash[2];
    d = previous_hash[3];
    e = previous_hash[4];
    f = previous_hash[5];
    g = previous_hash[6];
    h = previous_hash[7];

    for (i = 0; i < 64; i++)
    {
        T1 = h + BSIG1(e) + CH(e, f, g) + SHA256_CR[i] + B[i];
        T2 = BSIG0(a) + MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    next_hash[0] = a + previous_hash[0];
    next_hash[1] = b + previous_hash[1];
    next_hash[2] = c + previous_hash[2];
    next_hash[3] = d + previous_hash[3];
    next_hash[4] = e + previous_hash[4];
    next_hash[5] = f + previous_hash[5];
    next_hash[6] = g + previous_hash[6];
    next_hash[7] = h + previous_hash[7];
}

void sha256_change_input_block_endianness(uint32_t *i_b_p, uint64_t c)
{
    uint64_t i;
    register uint32_t n;
    for (i = 0; i < c; i++)
    {
        n = i_b_p[i];
        i_b_p[i] = ((n << 24) | (((n >> 8) & 255) << 16) | (((n >> 16) & 255) << 8) | (n >> 24));
    }
}

void sha256_init(struct sha256_state *s)
{
    s->unused_bytes_count = 0;
    s->used_bytes_count = 0;
}

void sha256_update(struct sha256_state *s, uint8_t *b, uint64_t c)
{
    uint32_t test_i;
    uint8_t *test_p;
    uint8_t l_e;

    test_i = 1;
    test_p = (uint8_t *)&test_i;
    if (test_p[0] == 1)
    {
        l_e = 1;
    }
    else
    {
        l_e = 0;
    }

    uint64_t nbi;
    nbi = 0;

    while (c > 0 && s->unused_bytes_count < 64)
    {
        s->unused_bytes[s->unused_bytes_count] = *(b + nbi);
        (s->unused_bytes_count)++;
        nbi++;
        c--;
    }

    if (s->unused_bytes_count == 64)
    {
        if (l_e == 1)
        {
            sha256_change_input_block_endianness((uint32_t *)(s->unused_bytes), 16);
        }

        if (s->used_bytes_count == 0)
        {
            sha256_process_block((uint32_t *)(s->unused_bytes), SHA256_SR, s->hash);
        }
        else
        {
            sha256_process_block((uint32_t *)(s->unused_bytes), s->hash, s->hash);
        }
        s->used_bytes_count = s->used_bytes_count + 64;
        s->unused_bytes_count = 0;
    }

    if (c > 63)
    {
        uint32_t *ib;
        uint64_t nibi;
        nibi = 0;
        ib = (uint32_t *)(b + nbi);

        if (l_e == 1)
        {
            sha256_change_input_block_endianness(ib, (c - (c % 64)) / 4);
        }
        
        while (c > 63)
        {
            sha256_process_block(ib + nibi, s->hash, s->hash);
            s->used_bytes_count = s->used_bytes_count + 64;
            nibi = nibi + 16;
            nbi = nbi + 64;
            c = c - 64;
        }
    }

    while (c > 0)
    {
        s->unused_bytes[s->unused_bytes_count] = *(b + nbi);
        (s->unused_bytes_count)++;
        nbi++;
        c--;
    }
}

void sha256_digest(struct sha256_state *s, uint8_t hash_output[32])
{
}