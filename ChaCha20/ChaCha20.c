#include <stdint.h>

void chacha20_quarter_round(uint32_t *v0, uint32_t *v1, uint32_t *v2, uint32_t *v3)
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

void process_chacha20_block(uint32_t input_block[16], uint32_t output_block[16])
{
    int i;
    for (i = 0; i < 16; i++)
    {
        output_block[i] = input_block[i];
    }
    for (i = 0; i < 10; i++)
    {
        chacha20_quarter_round(&output_block[0], &output_block[4], &output_block[8], &output_block[12]);
        chacha20_quarter_round(&output_block[1], &output_block[5], &output_block[9], &output_block[13]);
        chacha20_quarter_round(&output_block[2], &output_block[6], &output_block[10], &output_block[14]);
        chacha20_quarter_round(&output_block[3], &output_block[7], &output_block[11], &output_block[15]);
        chacha20_quarter_round(&output_block[0], &output_block[5], &output_block[10], &output_block[15]);
        chacha20_quarter_round(&output_block[1], &output_block[6], &output_block[11], &output_block[12]);
        chacha20_quarter_round(&output_block[2], &output_block[7], &output_block[8], &output_block[13]);
        chacha20_quarter_round(&output_block[3], &output_block[4], &output_block[9], &output_block[14]);
    }
}

uint8_t test_chacha20_block_function()
{
    uint32_t test_input_block[16] = {0x61707865, 0x3320646e, 0x79622d32, 0x6b206574, 0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c, 0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c, 0x00000001, 0x09000000, 0x4a000000, 0x00000000};
    uint32_t test_output_block[16] = {0x837778ab, 0xe238d763, 0xa67ae21e, 0x5950bb2f, 0xc4f2d0c7, 0xfc62bb2f, 0x8fa018fc, 0x3f5ec7b7, 0x335271c2, 0xf29489f3, 0xeabda8fc, 0x82e46ebd, 0xd19c12b4, 0xb04e16de, 0x9e83d0cb, 0x4e3c50a2};
    uint32_t output_block[16];
    process_chacha20_block(test_input_block, output_block);

    int i;
    for (i = 0; i < 16; i++)
    {
        if (output_block[i] != test_output_block[i])
        {
            return 0;
        }
    }

    return 1;
}