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

void chacha20_process_block(uint32_t input_block[16], uint32_t output_block[16])
{
    uint_fast8_t i;
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
    for (i = 0; i < 16; i++)
    {
        output_block[i] = input_block[i] + output_block[i];
    }
}

uint8_t chacha20_test()
{
    uint32_t test_input_block[16] = {0x61707865, 0x3320646e, 0x79622d32, 0x6b206574, 0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c, 0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c, 0x00000001, 0x09000000, 0x4a000000, 0x00000000};
    uint32_t test_output_block[16] = {0xe4e7f110, 0x15593bd1, 0x1fdd0f50, 0xc47120a3, 0xc7f4d1c7, 0x0368c033, 0x9aaa2204, 0x4e6cd4c3, 0x466482d2, 0x09aa9f07, 0x05d7c214, 0xa2028bd9, 0xd19c12b5, 0xb94e16de, 0xe883d0cb, 0x4e3c50a2};
    uint32_t output_block[16];
    chacha20_process_block(test_input_block, output_block);

    uint_fast8_t i;
    for (i = 0; i < 16; i++)
    {
        if (output_block[i] != test_output_block[i])
        {
            return 0;
        }
    }

    return 1;
}