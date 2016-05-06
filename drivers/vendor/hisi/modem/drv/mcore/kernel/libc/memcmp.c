#include "libc.h"

int memcmp(void *_a, void *_b, unsigned len)
{
    char *a = _a;
    char *b = _b;

    while(len-- > 0) {
        if(*a++ != *b++) return 1;
    }
    return 0;
}
