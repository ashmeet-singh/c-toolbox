#include <stdint.h>

void quarter_round(uint32_t *v0, uint32_t *v1, uint32_t *v2, uint32_t *v3)
{
    register uint32_t a = *v0;
    register uint32_t b = *v1;
    register uint32_t c = *v2;
    register uint32_t d = *v3;
    a += b;
    d ^= a;
    d = (d << 16) | (d >> 16);
    c += d;
    b ^= c;
    b = (b << 12) | (b >> 20);
    a += b;
    d ^= a;
    d = (d << 8) | (d >> 24);
    c += d;
    b ^= c;
    b = (b << 7) | (b >> 25);
    *v0 = a;
    *v1 = b;
    *v2 = c;
    *v3 = d;
}

void chacha20_block(uint32_t input_block[16])
{
    int i;
    for (i = 0; i < 20; i = i + 2)
    {
        quarter_round(&input_block[0], &input_block[4], &input_block[8], &input_block[12]);
        quarter_round(&input_block[1], &input_block[5], &input_block[9], &input_block[13]);
        quarter_round(&input_block[2], &input_block[6], &input_block[10], &input_block[14]);
        quarter_round(&input_block[3], &input_block[7], &input_block[11], &input_block[15]);
        quarter_round(&input_block[0], &input_block[5], &input_block[10], &input_block[15]);
        quarter_round(&input_block[1], &input_block[6], &input_block[11], &input_block[12]);
        quarter_round(&input_block[2], &input_block[7], &input_block[8], &input_block[13]);
        quarter_round(&input_block[3], &input_block[4], &input_block[9], &input_block[14]);
    }
}

/*
Test Block

0x61707865, 0x3320646e, 0x79622d32, 0x6b206574, 0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c, 0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c, 0x00000001, 0x09000000, 0x4a000000, 0x00000000

0x837778ab, 0xe238d763, 0xa67ae21e, 0x5950bb2f, 0xc4f2d0c7, 0xfc62bb2f, 0x8fa018fc, 0x3f5ec7b7, 0x335271c2, 0xf29489f3, 0xeabda8fc, 0x82e46ebd, 0xd19c12b4, 0xb04e16de, 0x9e83d0cb, 0x4e3c50a2
*/
