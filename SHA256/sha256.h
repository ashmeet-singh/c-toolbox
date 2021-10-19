#ifndef _Z_SHA256_H_INCLUDED_
#define _Z_SHA256_H_INCLUDED_

struct sha256_state
{
    uint8_t input_block_bytes[64];
    uint_fast8_t input_block_bytes_count;
    uint64_t digested_bytes_count;
    uint32_t hash[8];
};

void sha256_init(struct sha256_state *s);
void sha256_update(struct sha256_state *s, uint8_t *b, uint64_t c);
void sha256_digest(struct sha256_state *s, uint8_t output_hash[32]);

#endif /* _Z_SHA256_H_INCLUDED_ */

