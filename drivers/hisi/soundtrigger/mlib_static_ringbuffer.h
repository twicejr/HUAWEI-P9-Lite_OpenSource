#ifndef __MLIB_STATIC_RINGBUFFER_H__
#define __MLIB_STATIC_RINGBUFFER_H__

#include "mlib_ringbuffer.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

extern RingBuffer *Static_RingBuffer_Init(void * ringbufferAddr);

extern unsigned int Static_RingBuffer_GetCount(void);

extern int Static_RingBuffer_IsEmpty(void);

extern int Static_RingBuffer_IsFull(void);

extern int Static_RingBuffer_Get(void *element);

extern int Static_RingBuffer_Put(void *element);
extern int Static_RingBuffer_Compare(void *element,int compareCount);

extern int Static_RingBuffer_Start_FastTrans(int skip_cnt,int pre_cnt);

extern int Static_RingBuffer_Skip(unsigned int skip_count);

extern void Static_RingBuffer_DeInit(void);

extern int Static_RingBuffer_SetTransFlag(int transFlag);

extern int Static_RingBuffer_GetTransFlag(void);

extern int Static_RingBuffer_Compare(void *element,int compareCount);

#ifdef __cplusplus
	#if __cplusplus
		}
	#endif
#endif

#endif
