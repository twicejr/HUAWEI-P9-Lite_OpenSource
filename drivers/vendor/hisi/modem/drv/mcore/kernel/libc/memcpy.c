#include <libc.h>

void *memcpy(void *_dst, const void *_src, unsigned int len)
{
	unsigned char *dst = _dst;
	const unsigned char *src = _src;
	while(len-- > 0) {
		*dst++ = *src++;
	}
	return _dst;
}
