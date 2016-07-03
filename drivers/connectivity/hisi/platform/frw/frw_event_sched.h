

#ifndef __FRW_EVENT_SCHED_H__
#define __FRW_EVENT_SCHED_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "frw_main.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_EVENT_SCHED_H


/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 获取事件队列中已经缓存的事件个数 */
#define FRW_EVENT_QUEUE_GET_PENDING_EVENTS_NUM(_pst_event_queue)    oal_queue_get_length(&(_pst_event_queue)->st_queue)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
  枚举名  : frw_sched_policy_enum_uint8
  协议表格:
  枚举说明: 事件队列对应的调度策略
*****************************************************************************/
typedef enum
{
    FRW_SCHED_POLICY_HI     = 0,   /* 高优先级队列 */
    FRW_SCHED_POLICY_NORMAL = 1,   /* 普通优先级队列 */

    FRW_SCHED_POLICY_BUTT
}frw_sched_policy_enum;
typedef oal_uint8 frw_sched_policy_enum_uint8;

/*****************************************************************************
  枚举名  : frw_event_queue_state_enum_uint8
  协议表格:
  枚举说明: 事件队列状态
*****************************************************************************/
typedef enum
{
    FRW_EVENT_QUEUE_STATE_INACTIVE = 0,   /* 事件队列不活跃(不可被调度) */
    FRW_EVENT_QUEUE_STATE_ACTIVE,         /* 事件队列活跃(可被调度) */

    FRW_EVENT_QUEUE_STATE_BUTT
}frw_event_queue_state_enum;
typedef oal_uint8 frw_event_queue_state_enum_uint8;

/*****************************************************************************
  枚举名  : frw_vap_state_enum_uint8
  协议表格:
  枚举说明: 事件部署类型
*****************************************************************************/
typedef enum
{
    FRW_VAP_STATE_RESUME  = 0,    /* VAP恢复 */
    FRW_VAP_STATE_PAUSE,          /* VAP暂停 */

    FRW_VAP_STATE_BUTT
}frw_vap_state_enum;
typedef oal_uint8 frw_vap_state_enum_uint8;

/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
  结构名  : frw_event_sched_queue_stru
  结构说明: 可调度队列
*****************************************************************************/
typedef struct
{
    oal_spin_lock_stru                   st_lock;
    oal_uint32                           ul_total_weight_cnt;    /* 可调度队列上的总权重计数器 */
    oal_dlist_head_stru                  st_head;                /* 可调度队列的事件链表头 */
}frw_event_sched_queue_stru;

/*****************************************************************************
  结构名  : frw_event_queue_stru
  结构说明: 事件队列结构体
*****************************************************************************/
typedef struct tag_frw_event_queue_stru
{
    oal_spin_lock_stru                  st_lock;
    oal_queue_stru                      st_queue;       /* 队列 */
    frw_event_queue_state_enum_uint8    en_state;       /* 队列状态 */
    frw_sched_policy_enum_uint8         en_policy;      /* 队列调度策略(高优先级、普通优先级) */

    oal_uint8                           uc_weight;      /* WRR权重配置值 */
    oal_uint8                           uc_weight_cnt;  /* WRR权重计数器 */

    frw_vap_state_enum_uint8            en_vap_state;   /* VAP的状态值，0为恢复，1为暂停 */
    oal_uint8                           auc_resv[3];

    oal_dlist_head_stru                 st_list;
}frw_event_queue_stru;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32  frw_event_sched_init(frw_event_sched_queue_stru *pst_sched_queue);
extern oal_uint32  frw_event_queue_init(
                frw_event_queue_stru               *pst_event_queue,
                oal_uint8                           uc_weight,
                frw_sched_policy_enum_uint8         en_policy,
                frw_event_queue_state_enum_uint8    en_state,
                oal_uint8                           uc_max_events);
extern oal_void  frw_event_queue_destroy(frw_event_queue_stru *pst_event_queue);
extern oal_void* frw_event_sched_pick_next_event_queue_wrr(frw_event_sched_queue_stru *pst_sched_queue);
extern oal_uint32  frw_event_sched_deactivate_queue(
                frw_event_sched_queue_stru         *pst_sched_queue,
                frw_event_queue_stru               *pst_event_queue);

extern oal_uint32  frw_event_sched_activate_queue(
                frw_event_sched_queue_stru   *pst_sched_queue,
                frw_event_queue_stru         *pst_event_queue);

extern oal_void  frw_event_sched_pause_queue(
                frw_event_sched_queue_stru   *pst_sched_queue,
                frw_event_queue_stru         *pst_event_queue);
extern oal_void  frw_event_sched_resume_queue(
                frw_event_sched_queue_stru   *pst_sched_queue,
                frw_event_queue_stru         *pst_event_queue);

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


OAL_STATIC OAL_INLINE oal_void  frw_event_sched_reset_weight(frw_event_sched_queue_stru *pst_sched_queue)
{
    oal_dlist_head_stru    *pst_list;
    frw_event_queue_stru   *pst_event_queue;

    /* 遍历整个调度链表 */
    OAL_DLIST_SEARCH_FOR_EACH(pst_list, &pst_sched_queue->st_head)
    {
        /* 获取调度链表中的一个事件队列 */
        pst_event_queue = OAL_DLIST_GET_ENTRY(pst_list, frw_event_queue_stru, st_list);

        /* 只是重置恢复状态VAP的权重值 */
        if(FRW_VAP_STATE_RESUME == pst_event_queue->en_vap_state)
        {
            /* 重置事件队列的权重计数器 */
            pst_event_queue->uc_weight_cnt = pst_event_queue->uc_weight;

            /* 更新调度队列上的总权重计数器 */
            pst_sched_queue->ul_total_weight_cnt += pst_event_queue->uc_weight;
        }
    }
}


OAL_STATIC OAL_INLINE oal_void* frw_event_schedule(frw_event_sched_queue_stru *pst_sched_queue)
{
    oal_void                     *p_event;
    frw_event_sched_queue_stru   *pst_queue;

    /* 遍历全部调度类 */
    pst_queue = &pst_sched_queue[FRW_SCHED_POLICY_HI];

    /* 如果高优先级调度队列为空，则取下一个调度队列 */
    if (!oal_dlist_is_empty(&pst_queue->st_head))
    {
    	/* 从调度类中挑选下一个待处理的事件 */
    	p_event = frw_event_sched_pick_next_event_queue_wrr(pst_queue);

    	if (p_event)
    	{
    	    return p_event;
    	}
    }

    pst_queue = &pst_sched_queue[FRW_SCHED_POLICY_NORMAL];

    /* 如果普通优先级调度队列为空，则取下一个调度队列 */
    if (!oal_dlist_is_empty(&pst_queue->st_head))
    {
    	/* 从调度类中挑选下一个待处理的事件 */
    	p_event = frw_event_sched_pick_next_event_queue_wrr(pst_queue);

    	if (p_event)
    	{
    	    return p_event;
    	}
    }

    return OAL_PTR_NULL;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of frw_event_sched.h */
