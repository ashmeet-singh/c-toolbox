#ifndef _Z_STR_H_INCLUDED_
#define _Z_STR_H_INCLUDED_

#define z_str_cmp3char(m, c0, c1, c2) (m[0] == c0 && m[1] == c1 && m[2] == c2)
#define z_str_cmp4char(m, c0, c1, c2, c3) (m[0] == c0 && m[1] == c1 && m[2] == c2 && m[3] == c3)
#define z_str_cmp5char(m, c0, c1, c2, c3, c4) (m[0] == c0 && m[1] == c1 && m[2] == c2 && m[3] == c3 && m[4] == c4)

int64_t z_str_find_CRLF(void *buf, uint64_t len);

#endif /* _Z_STR_H_INCLUDED_ */