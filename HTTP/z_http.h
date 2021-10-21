#ifndef _Z_HTTP_H_INCLUDED_
#define _Z_HTTP_H_INCLUDED_

#include <stdint.h>

struct z_http_context_request_headers
{
};

struct z_http_context_request
{
    uint_fast8_t is_request_line_finished;
    uint_fast8_t method;
    uint8_t uri[1000];
    uint8_t version[50];
    struct http_request_box_headers headers;
};

struct z_http_context
{
    struct z_http_context_request request;
};

#endif /* _Z_HTTP_H_INCLUDED_ */