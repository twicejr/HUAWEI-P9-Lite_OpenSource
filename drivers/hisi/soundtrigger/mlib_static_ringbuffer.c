#include "mlib_static_ringbuffer.h"

static RingBuffer *rb;

RingBuffer *Static_RingBuffer_Init(void * ringbufferAddr)
{
	rb = RingBuffer_Init(ringbufferAddr);

	return rb;
}

unsigned int Static_RingBuffer_GetCount(void)
{
	return RingBuffer_GetCount(rb);
}

int Static_RingBuffer_GetTransFlag(void)
{
	return RingBuffer_GetTransFlag(rb);
}

int Static_RingBuffer_SetTransFlag(int transFlag)
{
	return RingBuffer_SetTransFlag(rb,transFlag);
}

int Static_RingBuffer_IsEmpty(void)
{
	return RingBuffer_IsEmpty(rb);
}

int Static_RingBuffer_IsFull(void)
{
	return RingBuffer_IsFull(rb);
}

int Static_RingBuffer_Get(void *element)
{
	return RingBuffer_Get(rb, element);
}

int Static_RingBuffer_Put(void *element)
{
	return RingBuffer_Put(rb, element);
}

int Static_RingBuffer_Compare(void *element,int compareCount)
{
	return RingBuffer_Compare(rb,element,compareCount);
}

int Static_RingBuffer_Skip(unsigned int skip_cnt)
{
	return RingBuffer_Skip(rb, skip_cnt);
}

int Static_RingBuffer_Backspace(unsigned int skip_cnt)
{
	return RingBuffer_Backspace(rb, skip_cnt);
}

void Static_RingBuffer_DeInit(void)
{
	RingBuffer_DeInit(rb);

}
