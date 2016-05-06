
#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__


struct s_ring_buffer {
	unsigned char *buffer;	/* the buffer holding the data */
	unsigned int size;	/* the size of the allocated buffer. must be asigned*/
	unsigned int in;	/* data is added at offset (in % size) */
	unsigned int out;	/* data is extracted from off. (out % size) */
};


/* helper macro */
#define __s_ring_buffer_initializer(s, b) \
	(struct s_ring_buffer) { \
		.size	= s, \
		.in	= 0, \
		.out	= 0, \
		.buffer = b \
	}


#define DECLARE_S_RING_BUFFER(name, size) \
union { \
	struct s_ring_buffer name; \
	unsigned char name##s_ring_buffer_buffer[size + sizeof(struct s_ring_buffer)]; \
}


#define INIT_S_RING_BUFFER(name) \
	name = __s_ring_buffer_initializer(sizeof(name##s_ring_buffer_buffer) - \
				sizeof(struct s_ring_buffer), \
				name##s_ring_buffer_buffer + sizeof(struct s_ring_buffer))

#define INIT_S_RING_BUFFER_STRUCT(tag, name) \
	.name = __s_ring_buffer_initializer(sizeof((&tag)->name##s_ring_buffer_buffer) - \
				sizeof(struct s_ring_buffer), \
				(&tag)->name##s_ring_buffer_buffer + sizeof(struct s_ring_buffer))


static inline int s_ring_buffer_is_empty(struct s_ring_buffer *rb)
{
	return (rb->in == rb->out);
}

static inline int s_ring_buffer_is_full(struct s_ring_buffer *rb)
{
	return rb->in - rb->out >= rb->size;
}

static inline unsigned int s_ring_buffer_wl(struct s_ring_buffer *rb)
{
	return rb->in - rb->out >= rb->size / 2;
}

static inline void s_ring_buffer_xin(struct s_ring_buffer *rb, const char* ch)
{
	rb->buffer[(rb->in & (rb->size -1))] = *ch;
	rb->in++;
	if (rb->in - rb->out > rb->size)
		rb->out  = rb->in - rb->size;
}

static inline unsigned int s_ring_buffer_xout(struct s_ring_buffer *rb, char *ch)
{
	if ( !s_ring_buffer_is_empty(rb)) {
		if (ch) 
			*ch = rb->buffer[(rb->out & (rb->size -1))];
		rb->out++;
		return 1;
	}
	return 0;
}


static inline void s_ring_buffer_in(struct s_ring_buffer *rb, const char *from, unsigned int len)
{
	int i;
	for ( i=0; i<len; i++) {
		s_ring_buffer_xin(rb, &from[i]);
	}
}
static inline unsigned int s_ring_buffer_out(struct s_ring_buffer *rb, char *to, unsigned int len)
{
	int i;
	for ( i=0; i<len && s_ring_buffer_xout(rb, &to[i]); i++) 
	{}
	return i;
}

static inline unsigned int s_ring_buffer_line_size(struct s_ring_buffer *rb)
{
	unsigned int i, out;
	for ( i=0, out=rb->out; out != rb->in ; i++, out++) {
		if (rb->buffer[(out & (rb->size -1))] == '\r' 
			|| rb->buffer[(out & (rb->size -1))] == '\n')
			return i+1;
	}
	return 0;
}

#endif
