#include <stdio.h>
#include <string.h>

#include "z_http.h"

int main()
{
    struct z_http_context ctx;
    memset(&ctx, 0, sizeof(ctx));
    char *s;
    s = "GET /hii HTTP/1.1\r\nContent-Length: 1000\r\n\r\n";
    z_http_parse_request(&ctx, s, strlen(s));
    printf(ctx.request.headers.content_type);
    return 0;
}