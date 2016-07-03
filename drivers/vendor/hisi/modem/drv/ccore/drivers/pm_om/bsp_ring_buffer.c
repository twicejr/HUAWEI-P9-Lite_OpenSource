
#include <osl_generic.h>
#include <bsp_ring_buffer.h>

int bsp_ring_buffer_in(struct ring_buffer *rb, void *data, u32 len, MEMCPY_FUNC memcpy_func)
{
	u32 left = 0;

	if (is_ring_buffer_full(rb))
	{
		return 0;
	}

	/* copy data from rb->write to buffer tail */
	left = min(len, rb->size - rb->write);
	if (left && memcpy_func && memcpy_func((void *)(rb->buf + rb->write), rb->size, (void *)data, left))
	{
		return -1;
	}
 
	/* copy left data(if neccessary) from buffer head */
	if (len != left)
	{
		if (memcpy_func && memcpy_func((void *)rb->buf, rb->size, (void*)((char *)data + left), (len - left)))
		{
			return -1;
		}
	}

	rb->write += len;
	rb->write %= (rb->size);

	return (int)len;
}

int bsp_ring_buffer_out(struct ring_buffer *rb, void *data, u32 len, MEMCPY_FUNC memcpy_func)
{
	u32 left = 0;

	if (is_ring_buffer_empty(rb))
	{
		return 0;
	}

	left = min(len, rb->size - rb->read);
	if (memcpy_func && memcpy_func(data, rb->size, (void *)(rb->buf + rb->read), left))
	{
		return -1;
	}

	if (len != left)
	{
		if (memcpy_func && memcpy_func((void *)((char *)data + left), rb->size, rb->buf, (len - left)))
		{
			return -1;
		}
	}

	rb->read += len;
	rb->read %= (rb->size);

	return (int)len;
}