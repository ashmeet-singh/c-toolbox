#ifndef _CHACHA20_H_INCLUDED_
#define _CHACHA20_H_INCLUDED_

#include <stdint.h>

void chacha20_quarter_round(uint32_t *v0, uint32_t *v1, uint32_t *v2, uint32_t *v3);
void chacha20_process_block(uint32_t input_block[16], uint32_t output_block[16]);
uint_fast8_t chacha20_test();

#endif /* _CHACHA20_H_INCLUDED_ */
