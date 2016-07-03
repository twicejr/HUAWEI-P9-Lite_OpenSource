


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "platform_spec.h"
#include "oam_ext_if.h"
#include "frw_main.h"
#include "frw_event_main.h"
#include "frw_event_sched.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_EVENT_SCHED_C


/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 函数原型声明
*****************************************************************************/

/*****************************************************************************
  4 全局变量定义
*****************************************************************************/

/*****************************************************************************
  5 函数实现
*****************************************************************************/

oal_uint32  frw_event_sched_deactivate_queue_no_lock(
                frw_event_sched_queue_stru         *pst_sched_queue,
                frw_event_queue_stru               *pst_event_queue)
{
    if (0 != pst_event_queue->st_queue.uc_element_cnt)
    {
        return OAL_SUCC;
    }

    /* 更新调度队列上的总权重计数器 */
    pst_sched_queue->ul_total_weight_cnt -= pst_event_queue->uc_weight_cnt;

    /* 将事件队列的权重计数器清零 */
    pst_event_queue->uc_weight_cnt = 0;

    /* mayuan debug */
    if ((oal_uint)&pst_event_queue->st_list == (oal_uint)&pst_sched_queue->st_head)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "frw_event_sched_deactivate_queue, delete header itself.");
        OAL_BUG_ON(1);
    }

    /* 将事件队列从调度链表上删除 */
    oal_dlist_delete_entry(&pst_event_queue->st_list);

    /* 将事件队列置为不活跃状态 */
    pst_event_queue->en_state = FRW_EVENT_QUEUE_STATE_INACTIVE;


    return OAL_SUCC;
}


oal_uint32  frw_event_sched_activate_queue_no_lock(
                frw_event_sched_queue_stru   *pst_sched_queue,
                frw_event_queue_stru         *pst_event_queue)
{
    /* 如果事件队列已经在可执行队列上(处于激活状态)，则直接返回成功 */
    if (FRW_EVENT_QUEUE_STATE_ACTIVE == pst_event_queue->en_state)
    {
        return OAL_SUCC;
    }

    /* 置为事件队列的权重计数器 */
    pst_event_queue->uc_weight_cnt = pst_event_queue->uc_weight;

    /* 更新调度队列上的总权重计数器 */
    pst_sched_queue->ul_total_weight_cnt += pst_event_queue->uc_weight_cnt;

    /* 将事件队列加入调度链表的末尾 */
    oal_dlist_add_tail(&pst_event_queue->st_list, &pst_sched_queue->st_head);

    /* 将事件队列置为激活状态 */
    pst_event_queue->en_state = FRW_EVENT_QUEUE_STATE_ACTIVE;

    return OAL_SUCC;
}




oal_void* frw_event_sched_pick_next_event_queue_wrr(frw_event_sched_queue_stru *pst_sched_queue)
{
    oal_dlist_head_stru       *pst_list;
    frw_event_queue_stru   *pst_event_queue = OAL_PTR_NULL;
    oal_void                      *p_event = OAL_PTR_NULL;
    oal_uint                       ul_flag = 0;

    oal_spin_lock_irq_save(&pst_sched_queue->st_lock, &ul_flag);

    /* 遍历整个调度链表 */
    OAL_DLIST_SEARCH_FOR_EACH(pst_list, &pst_sched_queue->st_head)
    {
        pst_event_queue = OAL_DLIST_GET_ENTRY(pst_list, frw_event_queue_stru, st_list);

        /* 如果事件队列的vap_state为暂停，则跳过，继续挑选下一个事件队列 */
        if (FRW_VAP_STATE_PAUSE == pst_event_queue->en_vap_state)
        {
            continue;
        }

        /* 如果事件队列的权重计数器为0，则挑选下一个事件队列 */
        if (pst_event_queue->uc_weight_cnt == 0)
        {
            continue;
        }

        /* 更新事件队列权重计数器 */
        pst_event_queue->uc_weight_cnt--;

        /* 更新调度队列的总权重计数器 */
        pst_sched_queue->ul_total_weight_cnt--;

        /* 从事件队列中取出一个事件 */
        p_event = frw_event_queue_dequeue(pst_event_queue);

        /* 如果事件队列变空，需要将其从调度队列上删除，并将事件队列状态置为不活跃(不可被调度) */
      //  if (0 == pst_event_queue->st_queue.uc_element_cnt)
        {
            frw_event_sched_deactivate_queue_no_lock(pst_sched_queue, pst_event_queue);
        }

        break;
    }

    /* 如果调度队列的总权重计数器为0，则需要重置调度队列上各个事件队列的权重计数器 */
    if (0 == pst_sched_queue->ul_total_weight_cnt)
    {
        frw_event_sched_reset_weight(pst_sched_queue);
    }

    oal_spin_unlock_irq_restore(&pst_sched_queue->st_lock, &ul_flag);
    return p_event;
}


oal_uint32  frw_event_sched_init(frw_event_sched_queue_stru *pst_sched_queue)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_sched_queue))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_event_sched_init:: pointer is NULL!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 初始化锁 */
    oal_spin_lock_init(&pst_sched_queue->st_lock);

    /* 初始化调度队列总权重计数器 */
    pst_sched_queue->ul_total_weight_cnt = 0;

    /* 初始化调度链表头 */
    oal_dlist_init_head(&pst_sched_queue->st_head);

    return OAL_SUCC;
}



OAL_STATIC oal_void frw_event_queue_set(
                frw_event_queue_stru               *pst_event_queue,
                oal_uint8                           uc_weight,
                frw_sched_policy_enum_uint8         en_policy,
                frw_event_queue_state_enum_uint8    en_state)
{
    pst_event_queue->uc_weight     = uc_weight;
    pst_event_queue->uc_weight_cnt = 0;
    pst_event_queue->en_policy     = en_policy;
    pst_event_queue->en_state      = en_state;
    pst_event_queue->en_vap_state  = FRW_VAP_STATE_RESUME;
}


oal_uint32  frw_event_queue_init(
                frw_event_queue_stru               *pst_event_queue,
                oal_uint8                           uc_weight,
                frw_sched_policy_enum_uint8         en_policy,
                frw_event_queue_state_enum_uint8    en_state,
                oal_uint8                           uc_max_events)

{
    oal_uint32 ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_queue))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_event_queue_init:: pointer is NULL!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 初始化锁 */
    oal_spin_lock_init(&pst_event_queue->st_lock);

    ul_ret = oal_queue_init(&pst_event_queue->st_queue, uc_max_events);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_event_queue_init:: OAL_QUEUE_INIT return != OAL_SUCC! %d}", ul_ret);
        frw_event_queue_set(pst_event_queue, 0, FRW_SCHED_POLICY_BUTT, FRW_EVENT_QUEUE_STATE_INACTIVE);

        return ul_ret;
    }

    frw_event_queue_set(pst_event_queue, uc_weight, en_policy, en_state);

    return OAL_SUCC;
}


oal_void  frw_event_queue_destroy(frw_event_queue_stru *pst_event_queue)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_queue))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_event_queue_destroy:: pointer is NULL!}");
        return;
    }

    oal_queue_destroy(&pst_event_queue->st_queue);

    frw_event_queue_set(pst_event_queue, 0, FRW_SCHED_POLICY_BUTT, FRW_EVENT_QUEUE_STATE_INACTIVE);
}


oal_uint32  frw_event_sched_deactivate_queue(
                frw_event_sched_queue_stru         *pst_sched_queue,
                frw_event_queue_stru               *pst_event_queue)
{

    oal_uint      ul_flag = 0;
    oal_uint32      ul_ret = OAL_SUCC;

    /* 关中断，加锁 */
    oal_spin_lock_irq_save(&pst_sched_queue->st_lock, &ul_flag);

    ul_ret = frw_event_sched_deactivate_queue_no_lock(pst_sched_queue, pst_event_queue);

    /* 解锁，开中断 */
    oal_spin_unlock_irq_restore(&pst_sched_queue->st_lock, &ul_flag);

    return ul_ret;
}


oal_uint32  frw_event_sched_activate_queue(
                frw_event_sched_queue_stru   *pst_sched_queue,
                frw_event_queue_stru         *pst_event_queue)
{
    oal_uint      ul_flag = 0;
    oal_uint32      ul_ret = OAL_SUCC;

    oal_spin_lock_irq_save(&pst_sched_queue->st_lock, &ul_flag);

    ul_ret = frw_event_sched_activate_queue_no_lock(pst_sched_queue, pst_event_queue);

    oal_spin_unlock_irq_restore(&pst_sched_queue->st_lock, &ul_flag);

    return ul_ret;
}


oal_void  frw_event_sched_pause_queue(
                frw_event_sched_queue_stru   *pst_sched_queue,
                frw_event_queue_stru         *pst_event_queue)
{
    oal_uint      ul_flag = 0;

    oal_spin_lock_irq_save(&pst_sched_queue->st_lock, &ul_flag);

     /* 该VAP对应的所有事件队列vap_state设置为暂停 */
    pst_event_queue->en_vap_state = FRW_VAP_STATE_PAUSE;

    /* 更新调度队列的总权重计数器 */
    if (FRW_EVENT_QUEUE_STATE_ACTIVE == pst_event_queue->en_state)
    {
         pst_sched_queue->ul_total_weight_cnt -= pst_event_queue->uc_weight_cnt;
    }

    oal_spin_unlock_irq_restore(&pst_sched_queue->st_lock, &ul_flag);
}


oal_void  frw_event_sched_resume_queue(
                frw_event_sched_queue_stru   *pst_sched_queue,
                frw_event_queue_stru         *pst_event_queue)
{
    oal_uint      ul_flag = 0;

    oal_spin_lock_irq_save(&pst_sched_queue->st_lock, &ul_flag);

     /* 该VAP对应的所有事件队列vap_state设置为恢复 */
    pst_event_queue->en_vap_state = FRW_VAP_STATE_RESUME;

    /* 更新调度队列的总权重计数器 */
    if (FRW_EVENT_QUEUE_STATE_ACTIVE == pst_event_queue->en_state)
    {
         pst_sched_queue->ul_total_weight_cnt += pst_event_queue->uc_weight_cnt;
    }

    oal_spin_unlock_irq_restore(&pst_sched_queue->st_lock, &ul_flag);
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

