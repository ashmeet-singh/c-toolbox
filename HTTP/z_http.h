#ifndef _Z_HTTP_H_INCLUDED_
#define _Z_HTTP_H_INCLUDED_

#include <stdint.h>

#define Z_HTTP_REQUEST_METHOD_GET 1
#define Z_HTTP_REQUEST_METHOD_POST 2

struct z_http_context_headers
{
    uint8_t content_type[200];
};

struct z_http_context_request
{
    uint_fast8_t is_request_line_finished;
    uint_fast8_t method;
    uint8_t uri[2000];
    uint8_t version[50];
    uint_fast8_t are_request_headers_finished;
    struct z_http_context_headers headers;
    uint64_t parsed_bytes_count;
};

struct z_http_context
{
    struct z_http_context_request request;
    uint8_t tempbuf[10000];
};

uint_fast8_t z_http_parse_request_line_and_request_headers(struct z_http_context *ctx, void *buf, uint64_t len)

#endif /* _Z_HTTP_H_INCLUDED_ */