#ifndef __BALONG_CON_RING_H_
#define __BALONG_CON_RING_H_

#define CON_RING_ERR 0
#define CON_RING_ERR_MEMCPYS (1 | CON_RING_ERR)

struct con_ring_buffer
{
	unsigned char * addr;
	unsigned int size;  /* warning:size must be power of 2, minimum 2. */
	unsigned int rpos;
	unsigned int wpos;
};

void con_ring_init(struct con_ring_buffer * buf, unsigned char * addr, unsigned long size);
unsigned int con_ring_append(struct con_ring_buffer * buf, unsigned char * inbuf, unsigned long size);
unsigned int con_ring_force_append(struct con_ring_buffer * buf, unsigned char * inbuf, unsigned int size);
unsigned int con_ring_get(struct con_ring_buffer * buf, unsigned char * outbuf, unsigned long size);
void con_ring_reset(struct con_ring_buffer * buf);

#endif
