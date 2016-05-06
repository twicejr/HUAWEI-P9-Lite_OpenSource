/******************************************************************************

				  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名	 : mlib_ringbuffer.c
  版 本 号	 : 初稿
  作	者	 : l00279082
  生成日期	 : 2014年9月1日
  最近修改	 :
  功能描述	 : 环状Buffer实现
  修改历史	 :
  1.日	  期   : 2014年9月1日
	作	  者   : l00279082
	修改内容   : 创建文件

******************************************************************************/

#include <linux/slab.h>
#include "mlib_ringbuffer.h"
#include "soundtrigger_log.h"

#ifdef RING_BUFFER_THREAD_SAFE
#include "kernel.h"


#endif



// Ring Buffer Structure
struct _RingBuffer {
   unsigned int size;
   unsigned int start;
   unsigned int count;
   unsigned int element_size;
   int			transFlag;
   char buffer[0];
};

#undef NULL
#define NULL ((void *)0)

#define   ELEMENT_SIZE	   320
#define   ELEMENT_CNT	   200
#define   HEAD_SIZE   20
#define   RINGBUFFER_SIZE	 (ELEMENT_SIZE)*(ELEMENT_CNT)


/*****************************************************************************
 函 数 名  : RingBuffer_Init
 功能描述  : 初始化Ring Buffer结构体并分配相关memory。
 输入参数  : rb: 指向RingBuffer结构体的指针
 输入参数  : size: Ring Buffer元素个数
 返 回 值  : Ring Buffer Return Code

 修改历史	   :
  1.日	  期   : 2014年9月1日
	作	  者   :
	修改内容   : 新生成函数

*****************************************************************************/
RingBuffer *RingBuffer_Init(void * ringbufferAddr)
{
	RingBuffer *rb;

	rb = ringbufferAddr;

	if (NULL == rb)
	{
		return NULL;
	}

	memset(rb,0X00,HEAD_SIZE+RINGBUFFER_SIZE);

	rb->element_size = ELEMENT_SIZE;
	rb->size = ELEMENT_CNT;
	rb->start = 0;
	rb->count = 0;
	rb->transFlag = 0;

	return rb;
}

/*****************************************************************************
 函 数 名  : RingBuffer_GetCount
 功能描述  : 获取Ring buffer中的元素个数
 输入参数  : rb: 指向RingBuffer结构体的指针
 返 回 值  : Ring Buffer当前元素个数
 修改历史	   :
  1.日	  期   : 2014年9月1日
	作	  者   :
	修改内容   : 新生成函数

*****************************************************************************/
unsigned int RingBuffer_GetCount(RingBuffer *rb)
{
	return rb->count;
}

/*****************************************************************************
 函 数 名  : RingBuffer_IsEmpty
 功能描述  : 判断Buffer是否为空
 输入参数  : rb: 指向RingBuffer结构体的指针
 返 回 值  : 1：Buffer空， 0：Buffer非空

 修改历史	   :
  1.日	  期   : 2014年9月1日
	作	  者   :
	修改内容   : 新生成函数

*****************************************************************************/
int RingBuffer_IsEmpty(RingBuffer *rb)
{
	return (rb->count == 0);
}

/*****************************************************************************
 函 数 名  : RingBuffer_IsFull
 功能描述  : 判断Buffer是否满
 输入参数  : rb: 指向RingBuffer结构体的指针
 返 回 值  : True：Buffer满， FALSE：Buffer非满

 修改历史	   :
  1.日	  期   : 2014年9月1日
	作	  者   :
	修改内容   : 新生成函数

*****************************************************************************/
int RingBuffer_IsFull(RingBuffer *rb)
{
	return (rb->count == rb->size);
}

int RingBuffer_GetTransFlag(RingBuffer *rb)
{
	return rb->transFlag;
}

int RingBuffer_SetTransFlag(RingBuffer *rb, int transFlag)
{
	rb->transFlag = transFlag;
	return 0;
}


/*****************************************************************************
 函 数 名  : RingBuffer_Get
 功能描述  : 从Ring Buffer中获取一个元素。
 输入参数  : rb: 指向RingBuffer结构体的指针
 返 回 值  : 元素存放地址

 修改历史	   :
  1.日	  期   : 2014年9月1日
	作	  者   :
	修改内容   : 新生成函数

*****************************************************************************/
int RingBuffer_Get(RingBuffer *rb, void *element)
{
	int retval;

#ifdef RING_BUFFER_THREAD_SAFE
	VOS_SmP(rb->sem, 50);
#endif
	if (!RingBuffer_IsEmpty(rb))
	{
		memcpy(element, rb->buffer + rb->start * rb->element_size, rb->element_size);
		rb->start = (rb->start + 1) % rb->size;
		--rb->count;
		retval = 320;
	}
	else
	{
		retval = 0;
	}
#ifdef RING_BUFFER_THREAD_SAFE
	VOS_SmV(rb->sem);
#endif

	return retval;
}

/*****************************************************************************
 函 数 名  : RingBuffer_Put
 功能描述  : 向Ring Buffer中写入一个元素。
 输入参数  : rb: 指向RingBuffer结构体的指针
 输入参数  : element: 元素地址
 返 回 值  : Ring Buffer Return Code

 修改历史	   :
  1.日	  期   : 2014年9月1日
	作	  者   :
	修改内容   : 新生成函数

*****************************************************************************/
int RingBuffer_Put(RingBuffer *rb, void *element)
{
	int end, retval;

#ifdef RING_BUFFER_THREAD_SAFE
	VOS_SmP(rb->sem, 50);
#endif
	end = (rb->start + rb->count) % rb->size;
	memcpy(rb->buffer + end * rb->element_size, element, rb->element_size);
	if (RingBuffer_IsFull(rb))
	{
		rb->start = (rb->start + 1) % rb->size; /* full, overwrite */
		retval = RING_BUFFER_OVERWRITE;
	}
	else
	{
		++rb->count;
		retval = RING_BUFFER_NORMAL;
	}
#ifdef RING_BUFFER_THREAD_SAFE
	VOS_SmV(rb->sem);
#endif

	return retval;
}


int RingBuffer_Compare(RingBuffer *rb,void *element,int compareCount)
{
	int i = 0;
	int ret = 0;

	for(i = 0 ; i < compareCount ; i++)
	{
		if (!RingBuffer_IsEmpty(rb))
		{
			ret = memcmp((char *)element + rb->element_size*i, rb->buffer + rb->start * rb->element_size, rb->element_size);

			if(0 == ret)
			{
				rb->start = (rb->start + 1) % rb->size;
				--rb->count;
			}else{
				ret = 0;
			}

		}
		else
		{
			ret = -1;
		}
	}

	return 0;
}

/*****************************************************************************
 函 数 名  : RingBuffer_Skip
 功能描述  : 删除元素(从头部后推)
 输入参数  : rb: 指向RingBuffer结构体的指针
 输入参数  : skip_cnt: 要删除的元素个数
 返 回 值  : Ring Buffer Return Code

 修改历史	   :
  1.日	  期   : 2014年9月1日
	作	  者   :
	修改内容   : 新生成函数

*****************************************************************************/
int RingBuffer_Skip(RingBuffer *rb, unsigned int skip_cnt)
{
	int retval;

#ifdef RING_BUFFER_THREAD_SAFE
	VOS_SmP(rb->sem, 50);
#endif
	if (RingBuffer_GetCount(rb) < skip_cnt)
	{
		retval = RING_BUFFER_NO_SKIP;
	}
	else
	{
		rb->start = (rb->start + skip_cnt) % rb->size;
		rb->count -= skip_cnt;
		retval = RING_BUFFER_NORMAL;
	}
#ifdef RING_BUFFER_THREAD_SAFE
	VOS_SmV(rb->sem);
#endif

	return retval;
}

/*****************************************************************************
 函 数 名  : RingBuffer_Backspace
 功能描述  : 删除元素(从尾部回退)
 输入参数  : rb: 指向RingBuffer结构体的指针
 输入参数  : skip_cnt: 要回退的元素个数
 返 回 值  : Ring Buffer Return Code

 修改历史	   :
  1.日	  期   : 2014年10月11日
	作	  者   :
	修改内容   : 新生成函数

*****************************************************************************/
int RingBuffer_Backspace(RingBuffer *rb, unsigned int skip_cnt)
{
	int retval;

#ifdef RING_BUFFER_THREAD_SAFE
	VOS_SmP(rb->sem, 50);
#endif
	if (RingBuffer_GetCount(rb) < skip_cnt)
	{
		retval = RING_BUFFER_NO_SKIP;
	}
	else
	{
		rb->start = (rb->start + rb->count - skip_cnt) % rb->size;
		rb->count = skip_cnt;
		retval =  RING_BUFFER_NORMAL;
	}
#ifdef RING_BUFFER_THREAD_SAFE
	VOS_SmV(rb->sem);
#endif

	return retval;
}

/*****************************************************************************
 函 数 名  : RingBuffer_DeInit
 功能描述  : 释放Ring Buffer使用的动态内存
 输入参数  : rb: 指向RingBuffer结构体的指针
 返 回 值  : 无

 修改历史	   :
  1.日	  期   : 2014年9月1日
	作	  者   :
	修改内容   : 新生成函数

*****************************************************************************/
void RingBuffer_DeInit(RingBuffer *rb)
{
	if (rb)
	{
		memset(rb, 0, RINGBUFFER_SIZE + HEAD_SIZE);
		rb = NULL;
	}
}

