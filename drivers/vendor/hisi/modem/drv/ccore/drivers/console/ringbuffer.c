#include <securec.h>
#include "ringbuffer.h"

void con_ring_init(struct con_ring_buffer * buf, unsigned char * addr, unsigned long size)
{
	buf->addr = addr;
	buf->size = size;
	buf->rpos = 0;
	buf->wpos = 0;
}

static unsigned int con_ring_free_sz(struct con_ring_buffer * buf)
{
	long long widx = 0, ridx = 0, bufsize = 0, empty = 0;

	widx = buf->wpos;
	ridx = buf->rpos;
	bufsize = buf->size;

	empty = (ridx - widx + bufsize - 1);

	return (unsigned int)(empty & (bufsize - 1));
}

/*
 * NOTE:when this function is called, it is assumed that the 'buf' has enough space for 'inbuf'.
 */
static void ring_data_cpy(struct con_ring_buffer * buf, unsigned char * inbuf, unsigned int size)
{
	unsigned int cpy_sz = 0, widx = 0, bufsize = 0;

	widx    = buf->wpos;
	bufsize = buf->size;

	cpy_sz = size <= (bufsize - widx) ? size : bufsize - widx;

	/* copy data to the right part of 'buf' */
	(void)memcpy_s(buf->addr + widx, cpy_sz, inbuf, cpy_sz);

	/* calc */
	size  -= cpy_sz;
	inbuf += cpy_sz;
	widx = (widx + cpy_sz) & (bufsize - 1);
	cpy_sz = size;

	/* copy data to the left part of 'buf' */
	(void)memcpy_s(buf->addr + widx, cpy_sz, inbuf, cpy_sz);

	buf->wpos = (widx + cpy_sz) & (bufsize - 1);
}

/*
 * The returned value indicates the accepted byte number.
 */
unsigned int con_ring_append(struct con_ring_buffer * buf, unsigned char * inbuf, unsigned long size)
{
	unsigned int free_sz = 0;

	free_sz = con_ring_free_sz(buf);
	free_sz = free_sz <= size ? free_sz : size;
	ring_data_cpy(buf, inbuf, free_sz);

	return free_sz;
}

/*
 * The returned value indicates the accepted byte number.
 * So, it is always equal to size.
 */
unsigned int con_ring_force_append(struct con_ring_buffer * buf, unsigned char * inbuf, unsigned int size)
{
	unsigned int free_sz = 0;
	unsigned int org_sz = size;

	if(size >= buf->size)
	{
		inbuf += (size - buf->size + 1);
		size = buf->size - 1;
		buf->rpos = buf->wpos;
	}
	else
	{
		free_sz = con_ring_free_sz(buf);
		if(free_sz < size)
		{
			buf->rpos += (size - free_sz);
			buf->rpos &= (buf->size - 1);
		}
	}

	ring_data_cpy(buf, inbuf, size);

	return org_sz;
}

static unsigned int con_ring_size(struct con_ring_buffer * buf)
{
	long long widx = 0, ridx = 0, bufsize = 0, empty = 0;

	widx = buf->wpos;
	ridx = buf->rpos;
	bufsize = buf->size;

	empty = (widx - ridx + bufsize);

	return (unsigned int)(empty & (bufsize - 1));
}

unsigned int con_ring_get(struct con_ring_buffer * buf, unsigned char * outbuf, unsigned long size)
{
	unsigned int cpy_sz = 0;
	unsigned int data_size = 0;

	data_size = con_ring_size(buf);

	for(cpy_sz = 0; (cpy_sz < size) && (cpy_sz < data_size); cpy_sz++)
	{
		outbuf[cpy_sz] = buf->addr[buf->rpos];
		buf->rpos = (buf->rpos + 1) & (buf->size - 1);
	}

	return cpy_sz;
}

void con_ring_reset(struct con_ring_buffer * buf)
{
	buf->rpos = buf->wpos;
}
