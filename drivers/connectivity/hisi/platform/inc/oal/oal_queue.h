

#ifndef __OAL_DATA_STRU_H__
#define __OAL_DATA_STRU_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_types.h"
#include "oal_mem.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID 0

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define OAL_QUEUE_DESTROY

/* 判断x是否是2的整数幂 */
#define OAL_IS_NOT_POW_OF_2(_x)   (_x & (_x - 1))

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
typedef struct
{
    oal_uint8           uc_element_cnt;    /* 本队列中已经存放的元素个数 */
    oal_uint8           uc_max_elements;   /* 本队列中所能存放的最大元素个数 */
    oal_uint8           uc_tail_index;     /* 指向下一个元素入队位置的索引 */
    oal_uint8           uc_head_index;     /* 指向当前元素出队位置的索引 */
    oal_uint         	*pul_buf;           /* 队列缓存 */
}oal_queue_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


OAL_STATIC OAL_INLINE oal_void oal_queue_set(oal_queue_stru *pst_queue, oal_uint *pul_buf, oal_uint8 uc_max_elements)
{
    pst_queue->pul_buf         = pul_buf;

    pst_queue->uc_tail_index   = 0;
    pst_queue->uc_head_index   = 0;
    pst_queue->uc_element_cnt  = 0;
    pst_queue->uc_max_elements = uc_max_elements;
}


OAL_STATIC OAL_INLINE oal_uint32 oal_queue_init(oal_queue_stru *pst_queue, oal_uint8 uc_max_events)
{
    oal_uint *pul_buf;

    if (0 == uc_max_events)
    {
        return OAL_SUCC;
    }
    else
    {
        if (OAL_UNLIKELY(OAL_IS_NOT_POW_OF_2(uc_max_events)))
        {
            return OAL_ERR_CODE_CONFIG_UNSUPPORT;
        }
    
        pul_buf = (oal_uint *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, (oal_uint16)(uc_max_events * OAL_SIZEOF(oal_uint)), OAL_TRUE);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pul_buf))
        {
            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }
    
        OAL_MEMZERO(pul_buf, uc_max_events * sizeof(oal_uint));
        oal_queue_set(pst_queue, pul_buf, uc_max_events);
    
        return OAL_SUCC;
    }
}


OAL_STATIC OAL_INLINE oal_void  oal_queue_destroy(oal_queue_stru *pst_queue)
{
    if (OAL_PTR_NULL == pst_queue)
    {
        return;
    }

    if (OAL_PTR_NULL == pst_queue->pul_buf)
    {
        return;
    }

    OAL_MEM_FREE(pst_queue->pul_buf, OAL_TRUE);

    oal_queue_set(pst_queue, OAL_PTR_NULL, 0);
}


OAL_STATIC OAL_INLINE oal_uint32  oal_queue_enqueue(oal_queue_stru *pst_queue, oal_void *p_element)
{
    oal_uint8   uc_tail_index;

    /* 异常: 队列已满 */
    if (pst_queue->uc_element_cnt == pst_queue->uc_max_elements)
    {
        return OAL_FAIL;
    }

    uc_tail_index = pst_queue->uc_tail_index;

    /* 将元素的地址保存在队列中 */
    pst_queue->pul_buf[uc_tail_index] = (oal_uint)p_element;

    uc_tail_index++;

    pst_queue->uc_tail_index = ((uc_tail_index >= pst_queue->uc_max_elements)? 0 : uc_tail_index);

    pst_queue->uc_element_cnt++;

    return OAL_SUCC;
}


OAL_STATIC OAL_INLINE oal_void* oal_queue_dequeue(oal_queue_stru *pst_queue)
{
    oal_uint8    uc_head_index;
    oal_void     *p_element;

    /* 异常: 队列为空 */
    if (0 == pst_queue->uc_element_cnt)
    {
        return OAL_PTR_NULL;
    }

    uc_head_index = pst_queue->uc_head_index;

    p_element = (oal_void *)pst_queue->pul_buf[uc_head_index];

    uc_head_index++;

    pst_queue->uc_head_index = ((uc_head_index >= pst_queue->uc_max_elements)? 0 : uc_head_index);
    pst_queue->uc_element_cnt--;

    return p_element;
}


OAL_STATIC OAL_INLINE oal_uint8  oal_queue_get_length(oal_queue_stru *pst_queue)
{
    if (OAL_PTR_NULL == pst_queue)
    {
        return 0;
    }

    return pst_queue->uc_element_cnt;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_data_stru.h */
