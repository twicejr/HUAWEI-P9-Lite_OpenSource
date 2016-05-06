#include "libc.h"

void *memchr(void const *buf, int c, unsigned int len)
{
	unsigned int i;
	unsigned char const *b= buf;
	unsigned char        x= (c&0xff);

	for(i= 0; i< len; i++) {
		if(b[i]== x) {
			return (void*)(b+i);
		}
	}

	return NULL;
}
