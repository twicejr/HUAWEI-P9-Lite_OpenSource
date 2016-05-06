#include <libc.h>

void *memset(void *_p, unsigned int v, unsigned int count)
{
    unsigned char *p = _p;
    while(count-- > 0) *p++ = v;
    return _p;
}
