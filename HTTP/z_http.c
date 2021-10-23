#include <stdint.h>

#include "z_http.h"
#include "z_str.h"

#define z_http_char_test1(c) ((c > 96 && c < 123) || (c > 45 && c < 58) || (c > 64 && c < 91) || c == 95)

uint_fast8_t z_http_parse_request(struct z_http_context *ctx, void *buf, uint64_t len)
{
    if (len == 0) { return 1; }

    struct z_http_context_request *req;
    req = &(ctx->request);

    uint8_t *s;
    s = (uint8_t *)buf;

    int64_t s_i;
    int64_t s_i_1;

    uint64_t u_i;

    uint_fast8_t f1;

    uint8_t c;

    if (req->is_request_line_finished == 0)
    {
        s_i = z_str_find_CRLF((void *)s, len);
        if (s_i == -1) { return 1; }

        if (s_i > 3 && z_str_cmp4char(s, 'G', 'E', 'T', ' '))
        {
            req->method = Z_HTTP_REQUEST_METHOD_GET;
            s_i_1 = 4;
        }
        else if (s_i > 4 && z_str_cmp5char(s, 'P', 'O', 'S', 'T', ' '))
        {
            req->method = Z_HTTP_REQUEST_METHOD_POST;
            s_i_1 = 5;
        }
        else
        {
            return 0; 
        }

        if (s_i_1 == s_i) { return 0; }

        u_i = 0;
        f1 = 0;
        while (s_i_1 < s_i)
        {
            c = s[s_i_1];
            s_i_1++;
            if (z_http_char_test1(c) && (u_i != (sizeof(req->uri) - 1)))
            {
                (req->uri)[u_i] = c;
                u_i++;
            }
            else if (c == 32)
            {
                (req->uri)[u_i] = '\0';
                f1 = 1;
                break;
            }
            else
            {
                return 0;
            }
        }
        if (f1 == 0) { return 0; }

        u_i = 0;
        while (s_i_1 < s_i)
        {
            c = s[s_i_1];
            s_i_1++;
            if (s_i_1 == s_i)
            {
                if (u_i == 0) { return 0; }
                (req->version)[u_i] = '\0';
                break;
            }
            else if (z_http_char_test1(c) && (u_i != (sizeof(req->version) - 1)))
            {
                (req->version)[u_i] = c;
                u_i++;
            }
            else
            {
                return 0;
            }
        }
        req->is_request_line_finished = 1;
    }
    


}