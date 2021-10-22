#ifndef _Z_HTTP_H_INCLUDED_
#define _Z_HTTP_H_INCLUDED_

#include <stdint.h>

#define Z_HTTP_REQUEST_METHOD_GET 1
#define Z_HTTP_REQUEST_METHOD_POST 2

struct z_http_context_headers
{
};

struct z_http_context_request
{
    uint_fast8_t is_request_line_finished;
    uint_fast8_t method;
    uint8_t uri[1000];
    uint8_t version[50];
    struct z_http_context_headers headers;
};

struct z_http_context
{
    struct z_http_context_request request;
};

#endif /* _Z_HTTP_H_INCLUDED_ */