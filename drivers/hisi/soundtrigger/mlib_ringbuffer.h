/******************************************************************************

				  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名	 : mlib_ringbuffer.h
  版 本 号	 : 初稿
  作	者	 : l00279082
  生成日期	 : 2014年9月2日
  最近修改	 :
  功能描述	 : 环状Buffer实现
  修改历史	 :
  1.日	  期   : 2014年9月1日
	作	  者   : l00279082
	修改内容   : 创建文件
******************************************************************************/
#ifndef __MLIB_RINGBUFFER_H__
#define __MLIB_RINGBUFFER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

//Return Code
enum RING_BUFFER_RET_CODE {
	RING_BUFFER_NORMAL,
	RING_BUFFER_BAD_PARAM,
	RING_BUFFER_ALLOCATE_FAIL,
	RING_BUFFER_EMPTY,
	RING_BUFFER_OVERWRITE,
	RING_BUFFER_NO_SKIP
};

struct _RingBuffer;
typedef struct _RingBuffer RingBuffer;

//#define RING_BUFFER_THREAD_SAFE

/*****************************************************************************
 函 数 名  : RingBuffer_Init
 功能描述  : 初始化Ring Buffer结构体并分配相关memory。
 输入参数  : rb: 指向RingBuffer结构体的指针
 输入参数  : element_size: Ring Buffer单个元素大小
 输入参数  : element_count: Ring Buffer总元素个数
 返 回 值  : RING_BUFFER_NORMAL：Success, RING_BUFFER_ALLOCATE_FAIL: Fail
*****************************************************************************/
extern RingBuffer *RingBuffer_Init(void * ringbufferAddr);

/*****************************************************************************
 函 数 名  : RingBuffer_GetCount
 功能描述  : 获取Ring buffer中的元素个数
 输入参数  : rb: 指向RingBuffer结构体的指针
 返 回 值  : 元素个数
*****************************************************************************/
extern unsigned int RingBuffer_GetCount(RingBuffer *rb);

/*****************************************************************************
 函 数 名  : RingBuffer_IsEmpty
 功能描述  : 判断Buffer是否为空
 输入参数  : rb: 指向RingBuffer结构体的指针
 返 回 值  : True：Buffer空， FALSE：Buffer非空
*****************************************************************************/
extern int RingBuffer_IsEmpty(RingBuffer *rb);

/*****************************************************************************
 函 数 名  : RingBuffer_IsFull
 功能描述  : 判断Buffer是否满
 输入参数  : rb: 指向RingBuffer结构体的指针
 返 回 值  : True：Buffer满， FALSE：Buffer非满
*****************************************************************************/
extern int RingBuffer_IsFull(RingBuffer *rb);

extern int RingBuffer_GetTransFlag(RingBuffer *rb);

extern int RingBuffer_SetTransFlag(RingBuffer *rb, int transFlag);


/*****************************************************************************
 函 数 名  : RingBuffer_Get
 功能描述  : 从Ring Buffer中获取一个元素。
 输入参数  : rb: 指向RingBuffer结构体的指针
 输入参数  : element: 存放元素的指针
 返 回 值  : Return Code
*****************************************************************************/
extern int RingBuffer_Get(RingBuffer *rb, void *element);

/*****************************************************************************
 函 数 名  : RingBuffer_Put
 功能描述  : 向Ring Buffer中写入一个元素。
 输入参数  : rb: 指向RingBuffer结构体的指针
 输入参数  : element: 要写入的元素的指针
 返 回 值  : 无
*****************************************************************************/
extern int RingBuffer_Put(RingBuffer *rb, void *element);

/*****************************************************************************
 函 数 名  : RingBuffer_Get_FastData
 功能描述  : 从Ring Buffer中快速读取数据。
 输入参数  : rb: 指向RingBuffer结构体的指针
			dstAddr：目的地址
			stopFlag：结束标志
 输入参数  :
 返 回 值  : 无
*****************************************************************************/
extern int RingBuffer_Compare(RingBuffer *rb,void *element,int compareCount);
extern int RingBuffer_Backspace(RingBuffer *rb, unsigned int skip_cnt);



/*****************************************************************************
 函 数 名  : RingBuffer_Erase
 功能描述  : 删除元素
 输入参数  : rb: 指向RingBuffer结构体的指针
 输入参数  : eraze_count: 要删除的元素个数
 返 回 值  : 无
*****************************************************************************/
extern int RingBuffer_Skip(RingBuffer *rb, unsigned int skip_count);

/*****************************************************************************
 函 数 名  : RingBuffer_DeInit
 功能描述  : 释放Ring Buffer使用的动态内存
 输入参数  : rb: 指向RingBuffer结构体的指针
 返 回 值  : 无
*****************************************************************************/
extern void RingBuffer_DeInit(RingBuffer *rb);

#ifdef __cplusplus
	#if __cplusplus
		}
	#endif
#endif
#endif
