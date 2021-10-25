#include <stdint.h>
#include <string.h>

#include "z_http.h"
#include "z_str.h"

#define z_http_char_test1(c) ((c > 96 && c < 123) || (c > 45 && c < 58) || (c > 64 && c < 91) || c == 95)

static uint8_t known_headers[15] = { 'C', 'o', 'n', 't', 'e', 'n', 't', '-', 'L', 'e', 'n', 'g', 't', 'h', '\0' };
static uint_fast32_t known_headers_index[1] = { 0 };
static uint_fast32_t known_headers_length[1] = { 14 };

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
    uint64_t u_i_1;

    uint_fast8_t f;

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
        else { return 0; }

        if (s_i_1 == s_i) { return 0; }

        u_i = 0;
        f = 0;
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
                f = 1;
                break;
            }
            else { return 0; }
        }
        if (f == 0) { return 0; }

        if (s_i_1 == s_i) { return 0; }

        u_i = 0;
        while (s_i_1 < s_i)
        {
            c = s[s_i_1];
            s_i_1++;
            if (z_http_char_test1(c) && (u_i != (sizeof(req->version) - 1)))
            {
                (req->version)[u_i] = c;
                u_i++;
            }
            else { return 0; }
            if (s_i_1 == s_i) { (req->version)[u_i] = '\0'; }
        }
        req->is_request_line_finished = 1;
        req->parsed_bytes_count = req->parsed_bytes_count + s_i + 2;
    }

    if(req->are_request_headers_finished == 0)
    {
        s = s + req->parsed_bytes_count;
        len = len - req->parsed_bytes_count;
        for (u_i = 0; u_i < (sizeof(known_headers_index) / sizeof(known_headers_index[0])); u_i++)
        {
            s_i = z_str_find_CRLF((void *)s, len);
            if (s_i == -1) { return 1; }
            if (s_i == 0)
            {
                req->are_request_headers_finished = 1;
                req->parsed_bytes_count = req->parsed_bytes_count + 2;
                break;
            }
            u_i_1 = known_headers_length[u_i];
            if ((s_i > u_i_1) && (memcmp((void *)s, (void *)(known_headers + known_headers_index[u_i]), u_i_1) == 0))
            {
                s_i_1 = u_i_1;
                while (s_i_1 < s_i)
                {
                    if (s[s_i_1] == 58) { break; }
                    s_i_1++;
                    if (s_i_1 == s_i) { return 0; }
                }
                if (u_i == 0)
                {
                    if (sizeof((req->headers).content_type) < s_i) { return 0; }
                    memcpy((void *)((req->headers).content_type), (void *)(s + s_i_1 + 1), s_i - s_i_1 - 1);
                    (req->headers).content_type[s_i - s_i_1 - 1] = '\0';
                }

                req->parsed_bytes_count = req->parsed_bytes_count + s_i + 2;
                s = s + s_i + 2;
                len = len - s_i - 2;
            }
        }
    }
    return 1;
}