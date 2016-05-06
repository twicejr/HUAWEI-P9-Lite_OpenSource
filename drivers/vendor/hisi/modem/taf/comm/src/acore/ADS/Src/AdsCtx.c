

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AdsCtx.h"
#include "AdsUpLink.h"
#include "AdsDownLink.h"
#include "AdsFilter.h"
#include "AdsDebug.h"
#include "mdrv.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_CTX_C
/*lint +e767*/

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

VOS_UINT32                              g_ulAdsULTaskId        = 0;  /* ADS上行任务ID */
VOS_UINT32                              g_ulAdsDLTaskId        = 0;  /* ADS下行任务ID */
VOS_UINT32                              g_ulAdsULTaskReadyFlag = 0;  /* ADS上行任务运行状态 */
VOS_UINT32                              g_ulAdsDLTaskReadyFlag = 0;  /* ADS下行任务运行状态 */

/* ADS模块的上下文 */
ADS_CTX_STRU                            g_stAdsCtx;
VOS_UINT64                              g_ullAdsDmaMask = 0xffffffffULL;


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : ADS_UL_CheckAllQueueEmpty
 功能描述  : 所有的PDP都去激活，队列为空
 输入参数  : VOS_UINT8 ucInstanceIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月31日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例

*****************************************************************************/
VOS_UINT32 ADS_UL_CheckAllQueueEmpty(VOS_UINT8 ucInstanceIndex)
{
    VOS_UINT32                          i;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx = VOS_NULL_PTR;

    pstAdsUlCtx = ADS_GetUlCtx(ucInstanceIndex);

    for (i = ADS_RAB_ID_MIN; i < ADS_RAB_ID_MAX + 1; i++)
    {
        if (VOS_FALSE != pstAdsUlCtx->astAdsUlQueue[i].ucIsQueueValid)
        {
            break;
        }
    }

    /* 所有的PDP都去激活　*/
    if ((ADS_RAB_ID_MAX + 1) != i)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : ADS_UL_SetProtectTmrLen
 功能描述  : 设置ADS上行发送数据保护定时器时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月12日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例
*****************************************************************************/
VOS_VOID ADS_UL_SetProtectTmrLen(VOS_UINT32 ulTimerLen)
{
    g_stAdsCtx.stAdsIpfCtx.ulProtectTmrLen = ulTimerLen;
    return;
}

/*****************************************************************************
 函 数 名  : ADS_UL_IsQueueExistent
 功能描述  : 判断队列是否存在
 输入参数  : VOS_UINT8                           ucInstanceIndex,
             VOS_UINT8                           ucRabId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月12日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例
*****************************************************************************/
VOS_UINT32 ADS_UL_IsQueueExistent(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
)
{
    /* 队列为空 */
    if (VOS_NULL_PTR == ADS_UL_GET_QUEUE_LINK_PTR(ucInstanceIndex, ucRabId))
    {
        ADS_WARNING_LOG(ACPU_PID_ADS_UL, "ADS_UL_IsQueueExistent: g_stAdsCtx.stAdsUlCtx.astAdsUlQueue[ulIndex].pstAdsUlLink is NULL");
        return VOS_ERR;
    }
    else
    {
        return VOS_OK;
    }
}

/*****************************************************************************
 函 数 名  : ADS_UL_IsAnyQueueExist
 功能描述  : 检测是否有队列存在
 输出参数  : VOS_VOID
 返 回 值  : VOS_TRUE
             VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月22日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_UL_IsAnyQueueExist(VOS_VOID)
{
    VOS_UINT8                           ucInstance;
    VOS_UINT8                           ucRabId;

    for (ucInstance = 0; ucInstance < ADS_INSTANCE_MAX_NUM; ucInstance++)
    {
        for (ucRabId = ADS_RAB_ID_MIN; ucRabId <= ADS_RAB_ID_MAX; ucRabId++)
        {
            if (VOS_OK == ADS_UL_IsQueueExistent(ucInstance, ucRabId))
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : ADS_UL_InsertQueue
 功能描述  : 将数据插入对应的队列
 输入参数  : VOS_UINT8                           ucInstance
           　IMM_ZC_STRU                        *pstImmZc
             VOS_UINT8                           ucRabId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月12日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年02月24日
    作    者   : f00179208
    修改内容   : V7R1C50项目，上行队列管理使用RABID来索引
  3.日    期   : 2012年4月12日
    作    者   : A00165503
    修改内容   : DTS2012020708222: ADS性能优化
  4.日    期   : 2012年4月27日
    作    者   : l60609
    修改内容   : DTS2012041802250: ADS上行10ms延时
  5.日    期   : 2012年8月31日
    作    者   : l60609
    修改内容   : AP适配项目：上行队列限长
  6.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例
  7.日    期   : 2013年05月09日
    作    者   : f00179208
    修改内容   : DTS2013050806891:ADS上行组包优化
  8.日    期   : 2014年06月03日
    作    者   : f00179208
    修改内容   : CCPU LOAD优化
*****************************************************************************/
VOS_UINT32 ADS_UL_InsertQueue(
    VOS_UINT8                           ucInstance,
    IMM_ZC_STRU                        *pstImmZc,
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                          ulNonEmptyEvent;
    VOS_UINT32                          ulAllUlQueueDataNum;
    VOS_UINT32                          ulSlice;
    VOS_UINT                            ulQueueLen;
    VOS_ULONG                           ulLockLevel;
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;

    ulNonEmptyEvent = VOS_FALSE;

    /* 此接口不释放pstData，由上层模块根据函数返回值判断是否需要释放内存 */

    /* 队列加锁 */
    /*lint -e571*/
    VOS_SpinLockIntLock(ADS_UL_GET_QUEUE_LINK_SPINLOCK(ucInstance, ucRabId), ulLockLevel);
    /*lint +e571*/

    /* 结点存在，但队列不存在 */
    if (VOS_OK != ADS_UL_IsQueueExistent(ucInstance, ucRabId))
    {
        /* 队列操作完成解锁 */
        VOS_SpinUnlockIntUnlock(ADS_UL_GET_QUEUE_LINK_SPINLOCK(ucInstance, ucRabId), ulLockLevel);
        ADS_WARNING_LOG(ACPU_PID_ADS_UL, "ADS_UL_InsertQueue:the queue is not ext!");
        ADS_DBG_UL_PKT_ENQUE_FAIL_NUM(1);
        return VOS_ERR;
    }

    ulQueueLen = IMM_ZcQueueLen(ADS_UL_GET_QUEUE_LINK_PTR(ucInstance, ucRabId));
    if (ulQueueLen >= ADS_UL_GET_MAX_QUEUE_LENGTH(ucInstance))
    {
        /* 队列操作完成解锁 */
        VOS_SpinUnlockIntUnlock(ADS_UL_GET_QUEUE_LINK_SPINLOCK(ucInstance, ucRabId), ulLockLevel);
        ADS_DBG_UL_PKT_ENQUE_FAIL_NUM(1);
        return VOS_ERR;
    }

    /* 保存ModemId/PktType/RabId到IMM */
    enPktType = ADS_UL_GET_QUEUE_PKT_TYPE(ucInstance, ucRabId);
    ADS_UL_SAVE_MODEMID_PKTTYEP_RABID_TO_IMM(pstImmZc, ucInstance, enPktType, ucRabId);

    /* 插入队列前将数据打上时间戳 */
    ulSlice = VOS_GetSlice();
    ADS_UL_SAVE_SLICE_TO_IMM(pstImmZc, ulSlice);

    /* 插入队列 */
    IMM_ZcQueueTail(ADS_UL_GET_QUEUE_LINK_PTR(ucInstance, ucRabId), pstImmZc);
    ADS_DBG_UL_PKT_ENQUE_SUCC_NUM(1);

    /* 队列由空变为非空 */
    if (1 == IMM_ZcQueueLen(ADS_UL_GET_QUEUE_LINK_PTR(ucInstance, ucRabId)))
    {
        ulNonEmptyEvent = VOS_TRUE;
    }

    /* 队列操作完成解锁 */
    VOS_SpinUnlockIntUnlock(ADS_UL_GET_QUEUE_LINK_SPINLOCK(ucInstance, ucRabId), ulLockLevel);

    ulAllUlQueueDataNum = ADS_UL_GetAllQueueDataNum();

    if (VOS_TRUE == ADS_UL_GET_THRESHOLD_ACTIVE_FLAG())
    {
        /* (1).jiffies超时,则直接触发发数,并停止发数定时器
           (2).队列中数据已到攒包门限且当前没有在处理数据,触发上行缓存缓存处理事件
           (3).队列由空变为非空时启动数据统计定时器以及保护定时器
         */
        ADS_UL_ADD_STAT_PKT_NUM(1);

        /* 超时长度为非零则需要启动触发发数 */
        if (0 != ADS_UL_GET_JIFFIES_EXP_TMR_LEN())
        {
            if (ADS_TIME_AFTER_EQ(ADS_GET_CURR_KERNEL_TIME(),
                                  (ADS_UL_GET_JIFFIES_TMR_CNT() + ADS_UL_GET_JIFFIES_EXP_TMR_LEN())))
            {
                ADS_UL_SET_JIFFIES_TMR_CNT(ADS_GET_CURR_KERNEL_TIME());
                ADS_UL_SndEvent(ADS_UL_EVENT_DATA_PROC);
                ADS_DBG_UL_TMR_HIT_THRES_TRIG_EVENT(1);
                return VOS_OK;
            }
        }

        if (ADS_UL_IS_REACH_THRESHOLD(ulAllUlQueueDataNum, ADS_UL_GET_SENDING_FLAG()))
        {
            ADS_UL_SndEvent(ADS_UL_EVENT_DATA_PROC);
            ADS_DBG_UL_QUE_HIT_THRES_TRIG_EVENT(1);
        }

        /* 队列由空变为非空 */
        if (VOS_TRUE == ulNonEmptyEvent)
        {
            ADS_StartTimer(TI_ADS_UL_DATA_STAT, ADS_UL_GET_STAT_TIMER_LEN());
            ADS_StartTimer(TI_ADS_UL_SEND, ADS_UL_GET_PROTECT_TIMER_LEN());
        }
    }
    else
    {
        /* (1).队列由空变为非空时触发上行缓存处理事件
           (2).队列中数据已到攒包门限的整数倍且当前没有在处理数据
               触发上行缓存缓存处理事件
         */
        if (VOS_TRUE == ulNonEmptyEvent)
        {
            ADS_UL_SndEvent(ADS_UL_EVENT_DATA_PROC);
            ADS_DBG_UL_QUE_NON_EMPTY_TRIG_EVENT(1);
        }
        else
        {
            if (ADS_UL_IS_REACH_THRESHOLD(ulAllUlQueueDataNum, ADS_UL_GET_SENDING_FLAG()))
            {
                ADS_UL_SndEvent(ADS_UL_EVENT_DATA_PROC);
                ADS_DBG_UL_QUE_HIT_THRES_TRIG_EVENT(1);
            }
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_UL_GetInstanceAllQueueDataNum
 功能描述  : 获取一个实例中所有上行缓存队列中的数据包个数
 输入参数  : VOS_UINT8 ucInstanceIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : 鲁琳/l60609
    修改内容   :DSDA Phase II: 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_UL_GetInstanceAllQueueDataNum(VOS_UINT8 ucInstanceIndex)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTotalNum;
    ADS_SPEC_CTX_STRU                  *pstAdsSpecCtx = VOS_NULL_PTR;

    pstAdsSpecCtx = &(g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex]);

    ulTotalNum = 0;

    for (i = ADS_RAB_ID_MIN; i < ADS_RAB_ID_MAX + 1; i++)
    {
        if (VOS_NULL_PTR != pstAdsSpecCtx->stAdsUlCtx.astAdsUlQueue[i].pstAdsUlLink)
        {
            ulTotalNum += pstAdsSpecCtx->stAdsUlCtx.astAdsUlQueue[i].pstAdsUlLink->qlen;
        }
    }

    return ulTotalNum;
}

/*****************************************************************************
 函 数 名  : ADS_UL_GetAllQueueDataNum
 功能描述  : 获取所有上行缓存队列中的数据包个数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例

*****************************************************************************/
VOS_UINT32 ADS_UL_GetAllQueueDataNum(VOS_VOID)
{
    VOS_UINT32                          ulTotalNum;
    VOS_UINT8                           i;

    ulTotalNum = 0;

    for (i = 0; i < ADS_INSTANCE_MAX_NUM; i++)
    {
        ulTotalNum = ulTotalNum + ADS_UL_GetInstanceAllQueueDataNum(i);
    }

    return ulTotalNum;
}

/*****************************************************************************
 函 数 名  : ADS_UL_CreateQueue
 功能描述  : 创建上行缓存队列
 输入参数  : VOS_UINT8                           ucInstanceIndex,
             VOS_UINT8                           ucRabId,
             ADS_QCI_TYPE_ENUM_UINT8             enPrio
             ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType
输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年02月21日
    作    者   : f00179208
    修改内容   : V7R1C50项目，创建队列时根据优先级设置队列的信息
  3.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例
  4.日    期   : 2013年05月22日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT
*****************************************************************************/
VOS_UINT32 ADS_UL_CreateQueue(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId,
    ADS_QCI_TYPE_ENUM_UINT8             enPrio,
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType,
    VOS_UINT8                           uc1XorHrpdUlIpfFlag
)
{
    IMM_ZC_HEAD_STRU                   *pstUlQueue;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx;

    pstAdsUlCtx = ADS_GetUlCtx(ucInstanceIndex);

    /* RabId的队列已经存在 */
    if (VOS_OK == ADS_UL_IsQueueExistent(ucInstanceIndex, ucRabId))
    {
        /* 对应的调度优先级也一样或者是比之前的要低，不更新QCI直接返回OK */
        if (enPrio >= pstAdsUlCtx->astAdsUlQueue[ucRabId].enPrio)
        {
            return VOS_OK;
        }
        /* 如果对应的调度优先级比之前的要高，需要更新该PDP的队列优先级，并对队列管理进行排序 */
        else
        {
            ADS_UL_UpdateQueueInPdpModified(ucInstanceIndex, enPrio, ucRabId);
            return VOS_OK;
        }
    }

    /* ucRabID的队列不存在, 需要创建队列头结点 */
    pstUlQueue = (IMM_ZC_HEAD_STRU *)PS_MEM_ALLOC(ACPU_PID_ADS_UL, sizeof(IMM_ZC_HEAD_STRU));

    if (VOS_NULL_PTR == pstUlQueue)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_CreateQueue: pstUlQueue is null");
        return VOS_ERR;
    }

    /* 队列初始化 */
    IMM_ZcQueueHeadInit(pstUlQueue);

    /* 将队列信息更新到上行上下文 */
    ADS_UL_SetQueue(ucInstanceIndex,
                    ucRabId,
                    VOS_TRUE,
                    pstUlQueue,
                    enPrio,
                    enPktType,
                    uc1XorHrpdUlIpfFlag);

    /* 队列不可能被用尽，一个RABID对应一个队列，而无效的已经在消息处理处屏蔽，
       故不需要判断是否满，可以直接重新排序 */
    ADS_UL_OrderQueueIndex(ucInstanceIndex, ucRabId);

    /*lint -e429*/
    return VOS_OK;
    /*lint +e429*/
}

/*****************************************************************************
 函 数 名  : ADS_UL_ClearQueue
 功能描述  : 清空队列中的数据
 输入参数  : VOS_UINT8                           ucRabId,
             IMM_ZC_HEAD_STRU                   *pstQueue,
             VOS_SPINLOCK                       *pstSpinLock
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月13日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年8月31日
    作    者   : l60609
    修改内容   : AP适配项目：使用自旋锁
  3.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例
  4.日    期   : 2014年04月03日
    作    者   : m00217266
    修改内容   : DTS2014032902757
*****************************************************************************/
VOS_VOID ADS_UL_ClearQueue(
    VOS_UINT8                           ucRabId,
    IMM_ZC_HEAD_STRU                   *pstQueue
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulQueueCnt;
    IMM_ZC_STRU                        *pstNode;

    ulQueueCnt = IMM_ZcQueueLen(pstQueue);

    for (i = 0; i < ulQueueCnt; i++)
    {
        pstNode = IMM_ZcDequeueHead(pstQueue);

        /* 释放结点内容 */
        IMM_ZcFree(pstNode);
    }
}

/*****************************************************************************
 函 数 名  : ADS_UL_DestroyQueue
 功能描述  : 销毁上行缓存队列
 输入参数  : VOS_UINT8                           ucInstanceIndex
             VOS_UINT8                           ucRabId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年02月20日
    作    者   : f00179208
    修改内容   : V7R1C50项目，增加队列调度的优先级以及上行队列管理使用RABID来索引
  3.日    期   : 2012年9月12日
    作    者   : l60609
    修改内容   : AP适配项目：增加锁处理
  4.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例
  5.日    期   : 2013年05月22日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT
*****************************************************************************/
VOS_VOID ADS_UL_DestroyQueue(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
)
{
    VOS_ULONG                           ulLockLevel;

    /* 结点存在但队列为空 */
    if (VOS_ERR == ADS_UL_IsQueueExistent(ucInstanceIndex, ucRabId))
    {
        /* Rab Id以及优先级置为无效值 */
        ADS_UL_SetQueue(ucInstanceIndex,
                        ucRabId,
                        VOS_FALSE,
                        VOS_NULL_PTR,
                        ADS_QCI_TYPE_BUTT,
                        ADS_PDP_TYPE_BUTT,
                        VOS_FALSE);

        /* 根据最新的队列管理进行排序 */
        ADS_UL_UpdateQueueInPdpDeactived(ucInstanceIndex, ucRabId);

        return;
    }

    /* 队列加锁 */
    /*lint -e571*/
    VOS_SpinLockIntLock(ADS_UL_GET_QUEUE_LINK_SPINLOCK(ucInstanceIndex, ucRabId), ulLockLevel);
    /*lint +e571*/

    /* Modified by l60609 for AP适配项目 ，2012-09-10 Begin */
    /* 销毁队列中的数据 */
    ADS_UL_ClearQueue(ucRabId,
                      ADS_UL_GET_QUEUE_LINK_PTR(ucInstanceIndex, ucRabId));
    /* Modified by l60609 for AP适配项目 ，2012-09-10 End */

    /* 销毁队列头结点*/
    PS_MEM_FREE(ACPU_PID_ADS_DL, ADS_UL_GET_QUEUE_LINK_PTR(ucInstanceIndex, ucRabId));

    /* 将队列信息更新到上行上下文 */
    ADS_UL_SetQueue(ucInstanceIndex,
                    ucRabId,
                    VOS_FALSE,
                    VOS_NULL_PTR,
                    ADS_QCI_TYPE_BUTT,
                    ADS_PDP_TYPE_BUTT,
                    VOS_FALSE);

    /* 队列操作完成解锁 */
    VOS_SpinUnlockIntUnlock(ADS_UL_GET_QUEUE_LINK_SPINLOCK(ucInstanceIndex, ucRabId), ulLockLevel);

    /* 根据最新的队列管理进行排序 */
    ADS_UL_UpdateQueueInPdpDeactived(ucInstanceIndex, ucRabId);

}

/*****************************************************************************
 函 数 名  : ADS_UL_GetInsertIndex
 功能描述  : 获取需要插入的索引
 输入参数  : VOS_UINT8                           ucInstanceIndex
             VOS_UINT8                           ucRabId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月22日
    作    者   : f00179208
    修改内容   : 新生成函数

  2.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例

*****************************************************************************/
VOS_UINT32 ADS_UL_GetInsertIndex(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                          i;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx;

    pstAdsUlCtx = ADS_GetUlCtx(ucInstanceIndex);

    /* 根据优先级来获取上行上下文中队列的Index值 */
    for (i = 0; i < ADS_RAB_NUM_MAX; i++)
    {
        if (pstAdsUlCtx->aucPrioIndex[i] == ucRabId)
        {
            break;
        }
    }

    return i;

}

/*****************************************************************************
 函 数 名  : ADS_UL_UpdateQueueInPdpActive
 功能描述  : 根据新PDP激活后所带的优先级对上行队列管理排序
 输入参数  : VOS_UINT8                           ucInstanceIndex
             VOS_UINT32                          ulIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月21日
    作    者   : f00179208
    修改内容   : 新生成函数

  2.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例

*****************************************************************************/
VOS_VOID ADS_UL_OrderQueueIndex(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx;

    pstAdsUlCtx = ADS_GetUlCtx(ucInstanceIndex);

    /* 如果该PDP的优先级比较高，需要插入到其他PDP的前面，比其优先级低的需要向后移一位 */
    for (i = 0; i < ADS_RAB_NUM_MAX; i++)
    {
        if (pstAdsUlCtx->astAdsUlQueue[ucIndex].enPrio < pstAdsUlCtx->astAdsUlQueue[pstAdsUlCtx->aucPrioIndex[i]].enPrio)
        {
            for (j = ADS_RAB_NUM_MAX - 1; j > i; j--)
            {
                pstAdsUlCtx->aucPrioIndex[j] = pstAdsUlCtx->aucPrioIndex[j - 1];
            }
            pstAdsUlCtx->aucPrioIndex[i] = ucIndex;

            break;
        }
    }
}

/*****************************************************************************
 函 数 名  : ADS_UL_UpdateQueueInPdpModified
 功能描述  : 根据PDP信息的修改所带的优先级对上行队列管理排序
 输入参数  : VOS_UINT8                           ucInstanceIndex,
             ADS_QCI_TYPE_ENUM_UINT8             enPrio
             VOS_UINT8                           ucRabId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月21日
    作    者   : f00179208
    修改内容   : 新生成函数

  2.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例

*****************************************************************************/
VOS_VOID ADS_UL_UpdateQueueInPdpModified(
    VOS_UINT8                           ucInstanceIndex,
    ADS_QCI_TYPE_ENUM_UINT8             enPrio,
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx;

    pstAdsUlCtx = ADS_GetUlCtx(ucInstanceIndex);

    /* 将修改的优先级更新到对于的队列管理中 */
    pstAdsUlCtx->astAdsUlQueue[ucRabId].enPrio = enPrio;

    /* 获取修改的RABID在aucPrioIndex数组中位置 */
    ulIndex = ADS_UL_GetInsertIndex(ucInstanceIndex, ucRabId);

    /* 没有找到，则不做处理 */
    if (ulIndex >= ADS_RAB_NUM_MAX)
    {
        return;
    }

    /* 先将修改对应位后面的向前移动一位 */
    for (i = ulIndex; i <  ADS_RAB_NUM_MAX - 1; i++)
    {
        pstAdsUlCtx->aucPrioIndex[i] = pstAdsUlCtx->aucPrioIndex[i + 1UL];
    }
    pstAdsUlCtx->aucPrioIndex[ADS_RAB_NUM_MAX - 1] = ADS_RAB_ID_INVALID;

    /* 移动后相当于是重新插入到队列管理中 */
    ADS_UL_OrderQueueIndex(ucInstanceIndex, ucRabId);

}

/*****************************************************************************
 函 数 名  : ADS_UL_UpdateQueueInPdpDeactive
 功能描述  : PDP去激活删除对于的队列信息后，对队列管理进行排序
 输入参数  : VOS_UINT8                           ucInstanceIndex,
             VOS_UINT8                           ucRabId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月21日
    作    者   : f00179208
    修改内容   : 新生成函数

  2.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例

*****************************************************************************/
VOS_VOID ADS_UL_UpdateQueueInPdpDeactived(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx;

    pstAdsUlCtx = ADS_GetUlCtx(ucInstanceIndex);

    /* 根据删除的PDP索引，将其后面的元素向前移动一位 */
    ulIndex = ADS_UL_GetInsertIndex(ucInstanceIndex, ucRabId);

    if (ulIndex >= ADS_RAB_NUM_MAX)
    {
        return;
    }

    for (i = ulIndex; i < ADS_RAB_NUM_MAX - 1; i++)
    {
        pstAdsUlCtx->aucPrioIndex[i] = pstAdsUlCtx->aucPrioIndex[i + 1UL];
    }
    pstAdsUlCtx->aucPrioIndex[ADS_RAB_NUM_MAX - 1] = ADS_RAB_ID_INVALID;

}

/*****************************************************************************
 函 数 名  : ADS_UL_SetQueue
 功能描述  : 在创建和销毁队列的时候，设置上行队列上下文信息
 输入参数  : VOS_UINT8                           ucInstanceIndex,
             VOS_UINT8                           ucRabId,
             VOS_UINT8                           ucIsQueueValid,
             IMM_ZC_HEAD_STRU                   *pstUlQueue,
             ADS_QCI_TYPE_ENUM_UINT8             enPrio
             ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月12日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年02月20日
    作    者   : f00179208
    修改内容   : V7R1C50项目，增加队列调度的优先级
  3.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例
  4.日    期   : 2013年05月22日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT
*****************************************************************************/
VOS_VOID ADS_UL_SetQueue(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucIsQueueValid,
    IMM_ZC_HEAD_STRU                   *pstUlQueue,
    ADS_QCI_TYPE_ENUM_UINT8             enPrio,
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType,
    VOS_UINT8                           uc1XorHrpdUlIpfFlag
)
{
    g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex].stAdsUlCtx.astAdsUlQueue[ucRabId].pstAdsUlLink   = pstUlQueue;
    g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex].stAdsUlCtx.astAdsUlQueue[ucRabId].ucIsQueueValid = ucIsQueueValid;
    g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex].stAdsUlCtx.astAdsUlQueue[ucRabId].enPrio         = enPrio;
    g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex].stAdsUlCtx.astAdsUlQueue[ucRabId].usRecordNum    = 0;
    g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex].stAdsUlCtx.astAdsUlQueue[ucRabId].enPktType      = enPktType;
    g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex].stAdsUlCtx.astAdsUlQueue[ucRabId].uc1XorHrpdUlIpfFlag = uc1XorHrpdUlIpfFlag;
}

/*****************************************************************************
 函 数 名  : ADS_UL_SndEvent
 功能描述  : 触发上行事件
 输入参数  : ulEvent                    - 事件ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月12日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_UL_SndEvent(VOS_UINT32 ulEvent)
{
    if (1 == g_ulAdsULTaskReadyFlag)
    {
        (VOS_VOID)VOS_EventWrite(g_ulAdsULTaskId, ulEvent);
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_UL_ProcEvent
 功能描述  : ADS上行事件处理
 输入参数  : ulEvent                    - 事件ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月12日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2015年9月22日
    作    者   : A00165503
    修改内容   : DTS2015081008249: ADS数传过程中持锁, 防止系统进入休眠

*****************************************************************************/
VOS_VOID ADS_UL_ProcEvent(VOS_UINT32 ulEvent)
{
    if (ulEvent & ADS_UL_EVENT_DATA_PROC)
    {
        ADS_UL_WakeLock();
        ADS_UL_ProcLinkData();
        ADS_UL_WakeUnLock();
        ADS_DBG_UL_PROC_EVENT_NUM(1);
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_DL_SndEvent
 功能描述  : 触发下行事件
 输入参数  : ulEvent                    - 事件ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月12日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_DL_SndEvent(VOS_UINT32 ulEvent)
{
    if (1 == g_ulAdsDLTaskReadyFlag)
    {
        (VOS_VOID)VOS_EventWrite(g_ulAdsDLTaskId, ulEvent);
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_DL_ProcEvent
 功能描述  : ADS下行事件处理
 输入参数  : ulEvent                    - 事件ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月12日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2015年4月24日
    作    者   : A00165503
    修改内容   : DTS2015042201072: 优化ADQ空中断处理, 防止内存无法及时补充

  3.日    期   : 2015年9月22日
    作    者   : A00165503
    修改内容   : DTS2015081008249: ADS数传过程中持锁, 防止系统进入休眠

*****************************************************************************/
VOS_VOID ADS_DL_ProcEvent(VOS_UINT32 ulEvent)
{
    if (ulEvent & ADS_DL_EVENT_IPF_RD_INT)
    {
        ADS_DL_WakeLock();
        ADS_DL_ProcIpfResult();
        ADS_DL_WakeUnLock();
        ADS_DBG_DL_PROC_IPF_RD_EVENT_NUM(1);
    }

    if (ulEvent & ADS_DL_EVENT_IPF_ADQ_EMPTY_INT)
    {
        ADS_DL_AllocMemForAdq();
        ADS_DBG_DL_PROC_IPF_AD_EMPTY_EVENT_NUM(1);
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_DL_InitFcAssemParamInfo
 功能描述  : 初始化底软动态组包参数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月19日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID ADS_DL_InitFcAssemParamInfo(VOS_VOID)
{
    ADS_DL_FC_ASSEM_STRU               *pstFcAssemInfo;

    pstFcAssemInfo = ADS_DL_GET_FC_ASSEM_INFO_PTR(ADS_INSTANCE_INDEX_0);

    pstFcAssemInfo->ulEnableMask     = VOS_FALSE;
    pstFcAssemInfo->ulFcActiveFlg    = VOS_FALSE;
    pstFcAssemInfo->ulTmrCnt         = ADS_GET_CURR_KERNEL_TIME();
    pstFcAssemInfo->ulRdCnt          = 0;
    pstFcAssemInfo->ulRateUpLev      = 0;
    pstFcAssemInfo->ulRateDownLev    = 0;
    pstFcAssemInfo->ulExpireTmrLen   = 0;
    pstFcAssemInfo->pFcAssemTuneFunc = VOS_NULL_PTR;

    return;
}

/*****************************************************************************
 函 数 名  : ADS_DL_ResetFcAssemParamInfo
 功能描述  : 重置底软动态组包参数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月19日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID ADS_DL_ResetFcAssemParamInfo(VOS_VOID)
{
    ADS_DL_FC_ASSEM_STRU               *pstFcAssemInfo;

    pstFcAssemInfo = ADS_DL_GET_FC_ASSEM_INFO_PTR(ADS_INSTANCE_INDEX_0);

    pstFcAssemInfo->ulFcActiveFlg    = VOS_FALSE;
    pstFcAssemInfo->ulRdCnt          = 0;

    return;
}

/*****************************************************************************
 函 数 名  : ADS_UL_EnableRxWakeLockTimeout
 功能描述  : 使能上行接收WAKE LOCK定时器
 输入参数  : ulValue --- 定时器(单位: ms)
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月22日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_UL_EnableRxWakeLockTimeout(VOS_UINT32 ulValue)
{
    ADS_IPF_CTX_STRU                   *pstIpfCntxt = VOS_NULL_PTR;

    pstIpfCntxt = ADS_GET_IPF_CTX_PTR();
    if (ulValue > pstIpfCntxt->ulRxWakeLockTimeout)
    {
        pstIpfCntxt->ulRxWakeLockTimeout = ulValue;
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : ADS_UL_WakeLockTimeout
 功能描述  : 上行发送WAKE LOCK TIMEOUT
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月22日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_UL_WakeLockTimeout(VOS_VOID)
{
    ADS_IPF_CTX_STRU                   *pstIpfCntxt = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstIpfCntxt = ADS_GET_IPF_CTX_PTR();
    ulRet       = pstIpfCntxt->ulRxWakeLockTimeout;

    if (0 != pstIpfCntxt->ulRxWakeLockTimeout)
    {
        /*lint -e713*/
        wake_lock_timeout(&(pstIpfCntxt->stRxWakeLock),
                          msecs_to_jiffies(pstIpfCntxt->ulRxWakeLockTimeout));
        /*lint +e713*/
    }

    pstIpfCntxt->ulRxWakeLockTimeout = 0;

    return ulRet;
}

/*****************************************************************************
 函 数 名  : ADS_UL_WakeLock
 功能描述  : 上行发送WAKE LOCK BD
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月22日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_UL_WakeLock(VOS_VOID)
{
    ADS_IPF_CTX_STRU                   *pstIpfCntxt = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstIpfCntxt = ADS_GET_IPF_CTX_PTR();
    if (VOS_FALSE == pstIpfCntxt->ulWakeLockEnable)
    {
        return 0;
    }

    wake_lock(&(pstIpfCntxt->stUlBdWakeLock));
    pstIpfCntxt->ulUlBdWakeLockCnt++;

    ulRet = pstIpfCntxt->ulUlBdWakeLockCnt;
    return ulRet;
}

/*****************************************************************************
 函 数 名  : ADS_WakeUnLock
 功能描述  : 上行发送WAKE UNLOCK BD
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月22日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_UL_WakeUnLock(VOS_VOID)
{
    ADS_IPF_CTX_STRU                   *pstIpfCntxt = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstIpfCntxt = ADS_GET_IPF_CTX_PTR();
    if (VOS_FALSE == pstIpfCntxt->ulWakeLockEnable)
    {
        return 0;
    }

    ADS_UL_WakeLockTimeout();

    wake_unlock(&(pstIpfCntxt->stUlBdWakeLock));
    pstIpfCntxt->ulUlBdWakeLockCnt--;

    ulRet = pstIpfCntxt->ulUlBdWakeLockCnt;
    return ulRet;
}

/*****************************************************************************
 函 数 名  : ADS_DL_EnableTxWakeLockTimeout
 功能描述  : 使能下行发送WAKE LOCK定时器
 输入参数  : ulValue --- 定时器(单位: ms)
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月22日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_DL_EnableTxWakeLockTimeout(VOS_UINT32 ulValue)
{
    ADS_IPF_CTX_STRU                   *pstIpfCntxt = VOS_NULL_PTR;

    pstIpfCntxt = ADS_GET_IPF_CTX_PTR();
    if (ulValue > pstIpfCntxt->ulTxWakeLockTimeout)
    {
        pstIpfCntxt->ulTxWakeLockTimeout = ulValue;
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : ADS_DL_WakeLockTimeout
 功能描述  : 启动下行接收WAKE LOCK TIMEOUT
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月22日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_DL_WakeLockTimeout(VOS_VOID)
{
    ADS_IPF_CTX_STRU                   *pstIpfCntxt = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstIpfCntxt = ADS_GET_IPF_CTX_PTR();
    ulRet       = pstIpfCntxt->ulTxWakeLockTimeout;

    if (0 != pstIpfCntxt->ulTxWakeLockTimeout)
    {
        /*lint -e713*/
        wake_lock_timeout(&(pstIpfCntxt->stTxWakeLock),
                          msecs_to_jiffies(pstIpfCntxt->ulTxWakeLockTimeout));
        /*lint +e713*/
    }

    pstIpfCntxt->ulTxWakeLockTimeout = 0;

    return ulRet;
}

/*****************************************************************************
 函 数 名  : ADS_DL_WakeLock
 功能描述  : 下行接收WAKE LOCK RD
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月22日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_DL_WakeLock(VOS_VOID)
{
    ADS_IPF_CTX_STRU                   *pstIpfCntxt = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstIpfCntxt = ADS_GET_IPF_CTX_PTR();
    if (VOS_FALSE == pstIpfCntxt->ulWakeLockEnable)
    {
        return 0;
    }

    wake_lock(&(pstIpfCntxt->stDlRdWakeLock));
    pstIpfCntxt->ulDlRdWakeLockCnt++;

    ulRet = pstIpfCntxt->ulDlRdWakeLockCnt;
    return ulRet;
}

/*****************************************************************************
 函 数 名  : ADS_DL_WakeUnLock
 功能描述  : 下行接收WAKE UNLOCK RD
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月22日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_DL_WakeUnLock(VOS_VOID)
{
    ADS_IPF_CTX_STRU                   *pstIpfCntxt = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstIpfCntxt = ADS_GET_IPF_CTX_PTR();
    if (VOS_FALSE == pstIpfCntxt->ulWakeLockEnable)
    {
        return 0;
    }

    ADS_DL_WakeLockTimeout();

    wake_unlock(&(pstIpfCntxt->stDlRdWakeLock));
    pstIpfCntxt->ulDlRdWakeLockCnt--;

    ulRet = pstIpfCntxt->ulDlRdWakeLockCnt;
    return ulRet;
}

/*****************************************************************************
 函 数 名  : ADS_IPF_MapRequset
 功能描述  : CACHE操作
 输入参数  : pstImmZc --- imm memory
             ulLen    --- cache size
             ucIsIn   --- 1 -> DMA_TO_DEVICE
                          0 -> DMA_TO_DEVICE
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_IPF_MemMapRequset(
    IMM_ZC_STRU                        *pstImmZc,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucIsIn
)
{
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    dma_addr_t                          ulDmaAddr;

    pucData   = IMM_ZcGetDataPtr(pstImmZc);
    ulDmaAddr = dma_map_single(ADS_GET_IPF_DEV(), pucData, ulLen,
                        (ucIsIn) ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
    ADS_IPF_SetMemDma(pstImmZc, ulDmaAddr);
    return;
}

/*****************************************************************************
 函 数 名  : ADS_IPF_MemMapByDmaRequset
 功能描述  : CACHE操作
 输入参数  : pstImmZc --- imm memory
             ulLen    --- cache size
             ucIsIn   --- 1 -> DMA_TO_DEVICE
                          0 -> DMA_TO_DEVICE
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_IPF_MemMapByDmaRequset(
    IMM_ZC_STRU                        *pstImmZc,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucIsIn
)
{
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    dma_addr_t                          ulDmaAddr;

    ulDmaAddr = ADS_IPF_GetMemDma(pstImmZc);
    pucData   = phys_to_virt(ulDmaAddr);
    dma_map_single(ADS_GET_IPF_DEV(), pucData, ulLen,
                        (ucIsIn) ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
    return;
}

/*****************************************************************************
 函 数 名  : ADS_IPF_UnmapRequset
 功能描述  : CACHE操作
 输入参数  : pstImmZc --- imm memory
             ulLen    --- cache size
             ucIsIn   --- 1 -> DMA_TO_DEVICE
                          0 -> DMA_TO_DEVICE
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_IPF_MemUnmapRequset(
    IMM_ZC_STRU                        *pstImmZc,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucIsIn
)
{
    dma_addr_t                          ulDmaAddr;

    ulDmaAddr = ADS_IPF_GetMemDma(pstImmZc);
    dma_unmap_single(ADS_GET_IPF_DEV(), ulDmaAddr, ulLen,
                        (ucIsIn) ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
    return;
}

#if (defined(CONFIG_BALONG_SPE))
/*****************************************************************************
 函 数 名  : ADS_IPF_IsSpeMem
 功能描述  : 检查SPE内存
 输入参数  : pstImmZc --- imm memory
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_IPF_IsSpeMem(IMM_ZC_STRU *pstImmZc)
{
    return (0 != pstImmZc->spe_own);
}

/*****************************************************************************
 函 数 名  : ADS_IPF_SetMemDma
 功能描述  : 设置内存的物理地址
 输入参数  : pstImmZc  --- imm memory
             ulDmaAddr --- phy addr
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_IPF_SetMemDma(IMM_ZC_STRU *pstImmZc, dma_addr_t ulDmaAddr)
{
    ADS_SPE_MEM_CB(pstImmZc)->ulDmaAddr = ulDmaAddr;
    return;
}

/*****************************************************************************
 函 数 名  : ADS_IPF_GetMemDma
 功能描述  : 获取内存的物理地址
 输入参数  : pstImmZc --- imm memory
 输出参数  : 无
 返 回 值  : dma_addr_t
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
dma_addr_t ADS_IPF_GetMemDma(IMM_ZC_STRU *pstImmZc)
{
    return ADS_SPE_MEM_CB(pstImmZc)->ulDmaAddr;
}

/*****************************************************************************
 函 数 名  : ADS_IPF_RefreshMem
 功能描述  : 刷新内存
 输入参数  : pstImmZc --- imm memory
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_IPF_RefreshMem(IMM_ZC_STRU *pstImmZc)
{
    IMM_ZcResetTailPointer(pstImmZc);
    pstImmZc->cloned = 0;
    pstImmZc->len    = 0;
    pstImmZc->psh    = 0;
    return;
}

/*****************************************************************************
 函 数 名  : ADS_IPF_RecycleMem
 功能描述  : 回收内存
 输入参数  : pstImmZc --- imm memory
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERROR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_INT ADS_IPF_RecycleMem(IMM_ZC_STRU *pstImmZc)
{
    ADS_IPF_MEM_POOL_CFG_STRU          *pstMemPoolCfg = VOS_NULL_PTR;
    dma_addr_t                          ulDmaAddr;
    VOS_UINT32                          ulPoolId;

    /* 检查内存池是否使能 */
    pstMemPoolCfg = ADS_GET_IPF_MEM_POOL_CFG_PTR();
    if (VOS_FALSE == pstMemPoolCfg->ulEnable)
    {
        ADS_DBG_DL_ADQ_RECYCLE_MEM_FAIL_NUM(1);
        return VOS_ERROR;
    }

    /* 操作顺序: 还原数据指针地址, 刷新内存 */
    ulDmaAddr = ADS_IPF_GetMemDma(pstImmZc);
    pstImmZc->data = phys_to_virt(ulDmaAddr);
    ADS_IPF_RefreshMem(pstImmZc);

    ulPoolId = (ADS_IPF_SPE_PORT_0 == pstImmZc->spe_own) ?
                    ADS_IPF_MEM_POOL_ID_AD0 : ADS_IPF_MEM_POOL_ID_AD1;

    /* 入队 */
    IMM_ZcQueueTail(ADS_GET_IPF_MEM_QUE(ulPoolId), pstImmZc);
    ADS_DBG_DL_ADQ_RECYCLE_MEM_SUCC_NUM(1);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_IPF_AllocMem
 功能描述  : 申请需的内存
 输入参数  : ulPoolId      --- 内存池
             ulLen         --- 内存大小
             ulReservedLen --- 保留字节
 输出参数  : 无
 返 回 值  : IMM_ZC_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
IMM_ZC_STRU* ADS_IPF_AllocMem(VOS_UINT32 ulPoolId, VOS_UINT32 ulLen, VOS_UINT32 ulReserveLen)
{
    ADS_IPF_MEM_POOL_CFG_STRU          *pstMemPoolCfg = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstImmZc      = VOS_NULL_PTR;

    if (ulPoolId >= ADS_IPF_MEM_POOL_ID_BUTT)
    {
        return VOS_NULL_PTR;
    }

    /* 检查内存池是否使能 */
    pstMemPoolCfg = ADS_GET_IPF_MEM_POOL_CFG_PTR();
    if (VOS_FALSE == pstMemPoolCfg->ulEnable)
    {
        /* 申请系统内存 */
        pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(ulLen);
        if (VOS_NULL_PTR == pstImmZc)
        {
            ADS_DBG_DL_ADQ_ALLOC_SYS_MEM_FAIL_NUM(1);
            return VOS_NULL_PTR;
        }

        ADS_DBG_DL_ADQ_ALLOC_SYS_MEM_SUCC_NUM(1);
        ADS_IPF_DL_MEM_MAP(pstImmZc, ulLen);
    }
    else
    {
        /* 出队 */
        pstImmZc = IMM_ZcDequeueHead(ADS_GET_IPF_MEM_QUE(ulPoolId));
        if (VOS_NULL_PTR == pstImmZc)
        {
            return VOS_NULL_PTR;
        }
    }

    /* 预留头部空间 */
    IMM_ZcReserve(pstImmZc, ulReserveLen);
    return pstImmZc;
}

/*****************************************************************************
 函 数 名  : ADS_IPF_CreateMemPool
 功能描述  : 创建内存池
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_IPF_CreateMemPool(VOS_VOID)
{
    ADS_IPF_MEM_POOL_CFG_STRU          *pstMemPoolCfg = VOS_NULL_PTR;
    ADS_IPF_MEM_POOL_STRU              *pstMemPool    = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstImmZc      = VOS_NULL_PTR;
    VOS_UINT32                          ulPoolId;
    VOS_UINT32                          ulCnt;

    pstMemPoolCfg = ADS_GET_IPF_MEM_POOL_CFG_PTR();
    if (VOS_FALSE == pstMemPoolCfg->ulEnable)
    {
        return;
    }

    for (ulPoolId = 0; ulPoolId < ADS_IPF_MEM_POOL_ID_BUTT; ulPoolId++)
    {
        pstMemPool = ADS_GET_IPF_MEM_POOL_PTR(ulPoolId);
        pstMemPool->usBlkSize = pstMemPoolCfg->astMemCfg[ulPoolId].usBlkSize;
        pstMemPool->usBlkNum  = pstMemPoolCfg->astMemCfg[ulPoolId].usBlkNum;
        pstMemPool->ucPort    = pstMemPoolCfg->astMemCfg[ulPoolId].ucPort;

        IMM_ZcQueueHeadInit(&(pstMemPool->stQue));

        for (ulCnt = 0; ulCnt < pstMemPool->usBlkNum; ulCnt++)
        {
            pstImmZc = IMM_ZcStaticAlloc(pstMemPool->usBlkSize);
            if (VOS_NULL_PTR == pstImmZc)
            {
                ADS_DBG_DL_ADQ_ALLOC_SYS_MEM_FAIL_NUM(1);
                break;
            }

            /* 操作顺序: 刷CACHE, 设置SPE端口 */
            ADS_IPF_DL_MEM_MAP(pstImmZc, pstMemPool->usBlkSize);
            pstImmZc->spe_own = pstMemPool->ucPort;

            /* 入内存池 */
            IMM_ZcQueueTail(&(pstMemPool->stQue), pstImmZc);
            ADS_DBG_DL_ADQ_ALLOC_SYS_MEM_SUCC_NUM(1);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_IPF_InitMemPoolCfg
 功能描述  : 初始化内存池配置
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_IPF_InitMemPoolCfg(VOS_VOID)
{
    ADS_IPF_MEM_POOL_CFG_STRU          *pstMemPoolCfg  = VOS_NULL_PTR;
    TAF_NV_ADS_MEM_POOL_CFG_STRU        stNvMemPoolCfg = {0};
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stNvMemPoolCfg, 0x00, sizeof(TAF_NV_ADS_MEM_POOL_CFG_STRU));

    pstMemPoolCfg = ADS_GET_IPF_MEM_POOL_CFG_PTR();
    pstMemPoolCfg->ulEnable = VOS_FALSE;

    pstMemPoolCfg->astMemCfg[ADS_IPF_MEM_POOL_ID_AD0].usBlkNum  = ADS_IPF_AD0_MEM_BLK_NUM;
    pstMemPoolCfg->astMemCfg[ADS_IPF_MEM_POOL_ID_AD0].usBlkSize = ADS_IPF_AD0_MEM_BLK_SIZE;
    pstMemPoolCfg->astMemCfg[ADS_IPF_MEM_POOL_ID_AD0].ucPort    = ADS_IPF_SPE_PORT_0;

    pstMemPoolCfg->astMemCfg[ADS_IPF_MEM_POOL_ID_AD1].usBlkNum  = ADS_IPF_AD1_MEM_BLK_NUM;
    pstMemPoolCfg->astMemCfg[ADS_IPF_MEM_POOL_ID_AD1].usBlkSize = ADS_IPF_AD1_MEM_BLK_SIZE;
    pstMemPoolCfg->astMemCfg[ADS_IPF_MEM_POOL_ID_AD1].ucPort    = ADS_IPF_SPE_PORT_1;

    ulRet = NV_ReadEx(MODEM_ID_0,
                      en_NV_Item_ADS_MEM_POOL_CFG,
                      &stNvMemPoolCfg,
                      sizeof(TAF_NV_ADS_MEM_POOL_CFG_STRU));
    if (NV_OK == ulRet)
    {
        pstMemPoolCfg->ulEnable = stNvMemPoolCfg.ulEnable;

        if (stNvMemPoolCfg.astMemCfg[0].usBlkNum >= ADS_IPF_AD0_MEM_BLK_NUM)
        {
            pstMemPoolCfg->astMemCfg[ADS_IPF_MEM_POOL_ID_AD0].usBlkNum = stNvMemPoolCfg.astMemCfg[0].usBlkNum;
        }

        if (stNvMemPoolCfg.astMemCfg[1].usBlkNum >= ADS_IPF_AD1_MEM_BLK_NUM)
        {
            pstMemPoolCfg->astMemCfg[ADS_IPF_MEM_POOL_ID_AD1].usBlkNum = stNvMemPoolCfg.astMemCfg[1].usBlkNum;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_IPF_SpeIntWakeupADS
 功能描述  : SPE中断触发事件, 唤醒ADS任务处理上行数据
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月1日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_IPF_SpeIntWakeupADS(VOS_VOID)
{
    ADS_UL_SndEvent(ADS_UL_EVENT_DATA_PROC);
    ADS_DBG_UL_SPE_INT_TRIG_EVENT(1);
    return;
}

/*****************************************************************************
 函 数 名  : ADS_IPF_RegSpeWPort
 功能描述  : 注册SPE端口
 输入参数  : lPort --- 端口
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_IPF_RegSpeWPort(VOS_INT32 lPort)
{
    ADS_IPF_CTX_STRU                   *pstIpfCntxt = VOS_NULL_PTR;

    pstIpfCntxt = ADS_GET_IPF_CTX_PTR();
    pstIpfCntxt->lSpeWPort = lPort;
    return;
}
#else
/*****************************************************************************
 函 数 名  : ADS_IPF_CheckSpeMem
 功能描述  : 检查SPE内存
 输入参数  : pstImmZc --- imm memory
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_IPF_IsSpeMem(IMM_ZC_STRU *pstImmZc)
{
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : ADS_IPF_SetMemDma
 功能描述  : 设置内存的物理地址
 输入参数  : pstImmZc  --- imm memory
             ulDmaAddr --- phy addr
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_IPF_SetMemDma(IMM_ZC_STRU *pstImmZc, dma_addr_t ulDmaAddr)
{
    ADS_IMM_MEM_CB(pstImmZc)->ulDmaAddr = ulDmaAddr;
    return;
}

/*****************************************************************************
 函 数 名  : ADS_IPF_GetMemDma
 功能描述  : 获取内存的物理地址
 输入参数  : pstImmZc --- imm memory
 输出参数  : 无
 返 回 值  : dma_addr_t
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
dma_addr_t ADS_IPF_GetMemDma(IMM_ZC_STRU *pstImmZc)
{
    return ADS_IMM_MEM_CB(pstImmZc)->ulDmaAddr;
}


/*****************************************************************************
 函 数 名  : ADS_IPF_AllocMem
 功能描述  : 申请ADQ所需的内存
 输入参数  : ulPoolId      --- 内存池
             ulLen         --- 内存大小
             ulReservedLen --- 保留字节
 输出参数  : 无
 返 回 值  : IMM_ZC_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
IMM_ZC_STRU* ADS_IPF_AllocMem(VOS_UINT32 ulPoolId, VOS_UINT32 ulLen, VOS_UINT32 ulReserveLen)
{
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(ulLen);
    if (VOS_NULL_PTR == pstImmZc)
    {
        ADS_DBG_DL_ADQ_ALLOC_SYS_MEM_FAIL_NUM(1);
        return VOS_NULL_PTR;
    }

    ADS_DBG_DL_ADQ_ALLOC_SYS_MEM_SUCC_NUM(1);

    /* 操作顺序: 刷CACHE, 预留头部空间 */
    ADS_IPF_DL_MEM_MAP(pstImmZc, ulLen);
    IMM_ZcReserve(pstImmZc, ulReserveLen);
    return pstImmZc;
}
#endif

/*****************************************************************************
 函 数 名  : ADS_GetULResetSem
 功能描述  : 获取ADS UL复位信号量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ADS复位信号量
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年04月15日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_SEM ADS_GetULResetSem(VOS_VOID)
{
    return g_stAdsCtx.hULResetSem;
}

/*****************************************************************************
 函 数 名  : ADS_GetDLResetSem
 功能描述  : 获取ADS DL复位信号量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ADS复位信号量
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年04月15日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_SEM ADS_GetDLResetSem(VOS_VOID)
{
    return g_stAdsCtx.hDLResetSem;
}

/*****************************************************************************
 函 数 名  : ADS_GetCurrentRate
 功能描述  : 设置当前上行速率
 输入参数  : 无
 输出参数  : VOS_UINT32                         *pulUlBpsRate,
             VOS_UINT32                         *pulDlBpsRate
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年1月10日
   作    者   : l60609
   修改内容   : 新生成函数

 2.日    期   : 2012年11月24日
   作    者   : l60609
   修改内容   : DSDA Phase II：双实例
*****************************************************************************/
VOS_UINT32 ADS_GetCurrentRate(
    VOS_UINT32                         *pulUlBpsRate,
    VOS_UINT32                         *pulDlBpsRate
)
{
    /* FC只有stick用，只返回实例0的 */
    *pulUlBpsRate = g_stAdsCtx.stDsFlowStatsCtx.stULDataStats.ulULCurDataRate << 3;
    *pulDlBpsRate = g_stAdsCtx.stDsFlowStatsCtx.stDLDataStats.ulDLCurDataRate << 3;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_GetUlResetFlag
 功能描述  : 获取ADS上行复位标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月27日
    作    者   : z00301431
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 ADS_GetUlResetFlag(VOS_VOID)
{
    return g_stAdsCtx.ucUlResetFlag;
}

/*****************************************************************************
 函 数 名  : ADS_SetUlResetFlag
 功能描述  : 设置ADS上行复位标志
 输入参数  : VOS_UINT8
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月27日
    作    者   : z00301431
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_SetUlResetFlag(VOS_UINT8 ucFlag)
{
    g_stAdsCtx.ucUlResetFlag = ucFlag;

    return;
}



/*****************************************************************************
 函 数 名  : ADS_GetTiCtx
 功能描述  : 获取ADS上行的上下文
 输入参数  : VOS_UINT8 ucInstanceIndex
 输出参数  : 无
 返 回 值  : ADS_TIMER_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月13日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例

*****************************************************************************/
ADS_UL_CTX_STRU* ADS_GetUlCtx(VOS_UINT8 ucInstanceIndex)
{
    ADS_SPEC_CTX_STRU                  *pstAdsSpecCtx = VOS_NULL_PTR;

    pstAdsSpecCtx = &(g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex]);

    return &(pstAdsSpecCtx->stAdsUlCtx);
}

/*****************************************************************************
 函 数 名  : ADS_GetTiCtx
 功能描述  : 获取ADS下行的上下文
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : ADS_TIMER_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月13日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例

*****************************************************************************/
ADS_DL_CTX_STRU* ADS_GetDlCtx(VOS_UINT8 ucInstanceIndex)
{
    ADS_SPEC_CTX_STRU                  *pstAdsSpecCtx = VOS_NULL_PTR;

    pstAdsSpecCtx = &(g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex]);

    return &(pstAdsSpecCtx->stAdsDlCtx);
}

/*****************************************************************************
 函 数 名  : ADS_GetTiCtx
 功能描述  : 获取ADS定时器的上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ADS_TIMER_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月13日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
ADS_TIMER_CTX_STRU* ADS_GetTiCtx(VOS_VOID)
{
    return g_stAdsCtx.astAdsTiCtx;
}

/*****************************************************************************
 函 数 名  : ADS_GetAllCtx
 功能描述  : 获取ADS所有的上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ADS_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:新生成函数

*****************************************************************************/
ADS_CTX_STRU* ADS_GetAllCtx(VOS_VOID)
{
    return &g_stAdsCtx;
}

/*****************************************************************************
 函 数 名  : ADS_InitUlCtx
 功能描述  : 初始化上行的上下文
 输入参数  : VOS_UINT8 ucInstanceIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年2月20日
    作    者   : f00179208
    修改内容   : 新增ADS优先级的NV项，上行上下文初始化时从NV中读出

  3.日    期   : 2012年4月12日
    作    者   : A00165503
    修改内容   : DTS2012020708222: ADS性能优化

  4.日    期   : 2012年8月31日
    作    者   : l60609
    修改内容   : AP适配项目：增加上行释放队列

  5.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II :双实例
  6.日    期   : 2013年05月22日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT
*****************************************************************************/
VOS_VOID ADS_InitUlCtx(VOS_UINT8 ucInstanceIndex)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRst;
    ADS_SPEC_CTX_STRU                  *pstAdsSpecCtx = VOS_NULL_PTR;

    pstAdsSpecCtx = &(g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex]);

    /* 默认从第一个队列开始调度 */
    pstAdsSpecCtx->stAdsUlCtx.ucAdsUlCurIndex      = 0;

    for (i = 0; i < ADS_RAB_ID_MAX + 1; i++)
    {
        pstAdsSpecCtx->stAdsUlCtx.astAdsUlQueue[i].pstAdsUlLink    = VOS_NULL_PTR;
        pstAdsSpecCtx->stAdsUlCtx.astAdsUlQueue[i].ucIsQueueValid  = VOS_FALSE;
        pstAdsSpecCtx->stAdsUlCtx.astAdsUlQueue[i].enPrio          = ADS_QCI_TYPE_BUTT;
        pstAdsSpecCtx->stAdsUlCtx.astAdsUlQueue[i].usRecordNum     = 0;
        pstAdsSpecCtx->stAdsUlCtx.astAdsUlQueue[i].enPktType       = ADS_CDS_IPF_PKT_TYPE_IP;

        /* Added by l60609 for AP适配项目 ，2012-09-10 Begin */
        /* 锁初始化 */
        VOS_SpinLockInit(&(pstAdsSpecCtx->stAdsUlCtx.astAdsUlQueue[i].stSpinLock));
        /* Added by l60609 for AP适配项目 ，2012-09-10 End */
    }

    PS_MEM_SET(pstAdsSpecCtx->stAdsUlCtx.aucPrioIndex, 0, ADS_RAB_NUM_MAX);

    /* 读NV，将优先级加权数读写到ADS上下文中 */
    ulRst = NV_ReadEx(ucInstanceIndex,
                      en_NV_Item_ADS_Queue_Scheduler_Pri,
                      &(pstAdsSpecCtx->stAdsUlCtx.stQueuePriNv),
                      sizeof(ADS_UL_QUEUE_SCHEDULER_PRI_NV_STRU));
    if(NV_OK != ulRst)
    {
        pstAdsSpecCtx->stAdsUlCtx.stQueuePriNv.ulStatus = VOS_FALSE;

        for (i = 0; i < ADS_UL_QUEUE_SCHEDULER_PRI_MAX; i++)
        {
            pstAdsSpecCtx->stAdsUlCtx.stQueuePriNv.ausPriWeightedNum[i] = ADS_UL_DEFAULT_PRI_WEIGHTED_NUM;
        }

        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_InitUlCtx: NV read failed !");
    }

    if (VOS_FALSE == pstAdsSpecCtx->stAdsUlCtx.stQueuePriNv.ulStatus)
    {
        for (i = 0; i < ADS_UL_QUEUE_SCHEDULER_PRI_MAX; i++)
        {
            pstAdsSpecCtx->stAdsUlCtx.stQueuePriNv.ausPriWeightedNum[i] = ADS_UL_DEFAULT_PRI_WEIGHTED_NUM;
        }
    }

    /* Added by l60609 for AP适配项目 ，2012-08-31 Begin */
    pstAdsSpecCtx->stAdsUlCtx.ulUlMaxQueueLength     = ADS_UL_MAX_QUEUE_LENGTH;
    /* Added by l60609 for AP适配项目 ，2012-08-31 End */

    return;
}

/*****************************************************************************
 函 数 名  : ADS_InitDlCtx
 功能描述  : 初始化下行的上下文
 输入参数  : ucInstance --- 实例号(ModemId)
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_InitDlCtx(VOS_UINT8 ucInstance)
{
    ADS_SPEC_CTX_STRU                  *pstAdsSpecCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstAdsSpecCtx = &(g_stAdsCtx.astAdsSpecCtx[ucInstance]);

    /* 初始化下行的RAB信息 */
    for (i = 0; i < ADS_RAB_NUM_MAX; i++)
    {
        pstAdsSpecCtx->stAdsDlCtx.astAdsDlRabInfo[i].ucRabId              = ADS_RAB_ID_INVALID;
        pstAdsSpecCtx->stAdsDlCtx.astAdsDlRabInfo[i].enPktType            = ADS_CDS_IPF_PKT_TYPE_IP;
        pstAdsSpecCtx->stAdsDlCtx.astAdsDlRabInfo[i].ulExParam            = 0;
        pstAdsSpecCtx->stAdsDlCtx.astAdsDlRabInfo[i].pRcvDlDataFunc       = VOS_NULL_PTR;
        pstAdsSpecCtx->stAdsDlCtx.astAdsDlRabInfo[i].pRcvDlFilterDataFunc = VOS_NULL_PTR;
        pstAdsSpecCtx->stAdsDlCtx.astAdsDlRabInfo[i].pstLstPkt            = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_InitStatsInfoCtx
 功能描述  : 初始化数据统计的上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月10日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_InitStatsInfoCtx(VOS_VOID)
{
    ADS_STATS_INFO_CTX_STRU            *pstDsFlowStatsCtx = VOS_NULL_PTR;

    pstDsFlowStatsCtx = ADS_GET_DSFLOW_STATS_CTX_PTR();

    pstDsFlowStatsCtx->stULDataStats.ulULPeriodSndBytes = 0;
    pstDsFlowStatsCtx->stULDataStats.ulULCurDataRate    = 0;
    pstDsFlowStatsCtx->stDLDataStats.ulDLPeriodRcvBytes = 0;
    pstDsFlowStatsCtx->stDLDataStats.ulDLCurDataRate    = 0;
}

/*****************************************************************************
 函 数 名  : ADS_InitSpecCtx
 功能描述  : 初始化每个实例专有的上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:新生成函数

  2.日    期   : 2013年9月22日
    作    者   : A00165503
    修改内容   : DTS2013092200927: 定时器使用优化
*****************************************************************************/
VOS_VOID ADS_InitSpecCtx(VOS_VOID)
{
    VOS_UINT8                           i;

    for (i = 0; i < ADS_INSTANCE_MAX_NUM; i++)
    {
        /* 初始化上行上下文 */
        ADS_InitUlCtx(i);

        /* 初始化下行上下文 */
        ADS_InitDlCtx(i);
    }

    /* 初始化底软动态组包参数 */
    ADS_DL_InitFcAssemParamInfo();
}

/*****************************************************************************
 函 数 名  : ADS_ResetSpecUlCtx
 功能描述  : 重置下行的上下文
 输入参数  : VOS_UINT8 ucInstance
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月14日
    作    者   : m00217266
    修改内容   : DTS2014032902757(与函数ADS_InitUlCtx基本一致，只删除了spinloc初始化)

*****************************************************************************/
VOS_VOID ADS_ResetSpecUlCtx(VOS_UINT8 ucInstance)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRst;
    ADS_SPEC_CTX_STRU                  *pstAdsSpecCtx = VOS_NULL_PTR;

    pstAdsSpecCtx = &(g_stAdsCtx.astAdsSpecCtx[ucInstance]);

    /* 默认从第一个队列开始调度 */
    pstAdsSpecCtx->stAdsUlCtx.ucAdsUlCurIndex      = 0;

    for (i = 0; i < ADS_RAB_ID_MAX + 1; i++)
    {
        pstAdsSpecCtx->stAdsUlCtx.astAdsUlQueue[i].pstAdsUlLink    = VOS_NULL_PTR;
        pstAdsSpecCtx->stAdsUlCtx.astAdsUlQueue[i].ucIsQueueValid  = VOS_FALSE;
        pstAdsSpecCtx->stAdsUlCtx.astAdsUlQueue[i].enPrio          = ADS_QCI_TYPE_BUTT;
        pstAdsSpecCtx->stAdsUlCtx.astAdsUlQueue[i].usRecordNum     = 0;
        pstAdsSpecCtx->stAdsUlCtx.astAdsUlQueue[i].enPktType       = ADS_CDS_IPF_PKT_TYPE_IP;
    }

    PS_MEM_SET(pstAdsSpecCtx->stAdsUlCtx.aucPrioIndex, 0, ADS_RAB_NUM_MAX);

    /* 读NV，将优先级加权数读写到ADS上下文中 */
    ulRst = NV_ReadEx(ucInstance,
                      en_NV_Item_ADS_Queue_Scheduler_Pri,
                      &(pstAdsSpecCtx->stAdsUlCtx.stQueuePriNv),
                      sizeof(ADS_UL_QUEUE_SCHEDULER_PRI_NV_STRU));
    if(NV_OK != ulRst)
    {
        pstAdsSpecCtx->stAdsUlCtx.stQueuePriNv.ulStatus = VOS_FALSE;

        for (i = 0; i < ADS_UL_QUEUE_SCHEDULER_PRI_MAX; i++)
        {
            pstAdsSpecCtx->stAdsUlCtx.stQueuePriNv.ausPriWeightedNum[i] = ADS_UL_DEFAULT_PRI_WEIGHTED_NUM;
        }

        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_InitUlCtx: NV read failed !");
    }

    if (VOS_FALSE == pstAdsSpecCtx->stAdsUlCtx.stQueuePriNv.ulStatus)
    {
        for (i = 0; i < ADS_UL_QUEUE_SCHEDULER_PRI_MAX; i++)
        {
            pstAdsSpecCtx->stAdsUlCtx.stQueuePriNv.ausPriWeightedNum[i] = ADS_UL_DEFAULT_PRI_WEIGHTED_NUM;
        }
    }

    pstAdsSpecCtx->stAdsUlCtx.ulUlMaxQueueLength     = ADS_UL_MAX_QUEUE_LENGTH;

    return;
}

/*****************************************************************************
 函 数 名  : ADS_ResetSpecDlCtx
 功能描述  : 重置下行的上下文
 输入参数  : VOS_UINT8 ucInstance
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年04月15日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_ResetSpecDlCtx(VOS_UINT8 ucInstance)
{
    ADS_SPEC_CTX_STRU                  *pstAdsSpecCtx  = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstAdsSpecCtx = &(g_stAdsCtx.astAdsSpecCtx[ucInstance]);

    /* 重置下行的RAB信息 */
    for (i = 0; i < ADS_RAB_NUM_MAX; i++)
    {
        pstAdsSpecCtx->stAdsDlCtx.astAdsDlRabInfo[i].ucRabId              = ADS_RAB_ID_INVALID;
        pstAdsSpecCtx->stAdsDlCtx.astAdsDlRabInfo[i].enPktType            = ADS_CDS_IPF_PKT_TYPE_IP;
        pstAdsSpecCtx->stAdsDlCtx.astAdsDlRabInfo[i].ulExParam            = 0;
        pstAdsSpecCtx->stAdsDlCtx.astAdsDlRabInfo[i].pRcvDlDataFunc       = VOS_NULL_PTR;
        pstAdsSpecCtx->stAdsDlCtx.astAdsDlRabInfo[i].pRcvDlFilterDataFunc = VOS_NULL_PTR;
        pstAdsSpecCtx->stAdsDlCtx.astAdsDlRabInfo[i].pstLstPkt            = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_ResetSpecCtx
 功能描述  : 重置每个实例专有的上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年04月15日
    作    者   : f00179208
    修改内容   : 新生成函数

  2.日    期   : 2013年9月22日
    作    者   : A00165503
    修改内容   : DTS2013092200927: 定时器使用优化

  3.日    期   : 2014年4月14日
    作    者   : m00217266
    修改内容   : DTS2014032902757: c核单独复位时上行ads空指针
*****************************************************************************/
VOS_VOID ADS_ResetUlCtx(VOS_VOID)
{
    VOS_UINT8                           i;

    for (i = 0; i < ADS_INSTANCE_MAX_NUM; i++)
    {
        /* 初始化上行上下文 */
        ADS_ResetSpecUlCtx(i);
    }

    /* 初始化数据统计的上下文 */
    ADS_InitStatsInfoCtx();

    return;
}

/*****************************************************************************
 函 数 名  : ADS_ResetDlCtx
 功能描述  : 重置下行上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月1日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID ADS_ResetDlCtx(VOS_VOID)
{
    VOS_UINT8                           i;

    for (i = 0; i < ADS_INSTANCE_MAX_NUM; i++)
    {
        /* 初始化下行上下文 */
        ADS_ResetSpecDlCtx(i);
    }

    /* 重置底软动态组包参数 */
    ADS_DL_ResetFcAssemParamInfo();

    return;
}

/*****************************************************************************
 函 数 名  : ADS_ResetIpfCtx
 功能描述  : 重置和IPF相关的上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年04月15日
    作    者   : f00179208
    修改内容   : 新生成函数

  2.日    期   : 2014年06月03日
    作    者   : f00179208
    修改内容   : CCPU LOAD优化

  3.日    期   : 2015年9月1日
    作    者   : A00165503
    修改内容   : DTS2015082300106: 下行灌小包, A核触发C核单独复位后整机重启
*****************************************************************************/
VOS_VOID ADS_ResetIpfCtx(VOS_VOID)
{
    /* 默认上行数据发送保护定时器时长为10ms */
    g_stAdsCtx.stAdsIpfCtx.ulProtectTmrLen   = 10;

    /* 默认上行数据统计定时器时长为100ms */
    g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdStatInfo.ulStatTmrLen = 100;
    g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdStatInfo.ulStatPktNum = 0;

    /* 默认攒包的最大个数 */
    if (VOS_TRUE == g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.ulActiveFlag)
    {
        g_stAdsCtx.stAdsIpfCtx.ulThredHoldNum = ADS_UL_DATA_THRESHOLD_ONE;
    }
    else
    {
        g_stAdsCtx.stAdsIpfCtx.ulThredHoldNum = 32;
    }

    /* 默认数据不在发送 */
    g_stAdsCtx.stAdsIpfCtx.ucSendingFlg = VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : ADS_InitIpfCtx
 功能描述  : 初始化和IPF相关的上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II: 新生成函数

  2.日    期   : 2014年06月03日
    作    者   : f00179208
    修改内容   : CCPU LOAD优化

  3.日    期   : 2015年9月22日
    作    者   : A00165503
    修改内容   : DTS2015081008249: ADS数传过程中持锁, 防止系统进入休眠

*****************************************************************************/
VOS_VOID ADS_InitIpfCtx(VOS_VOID)
{
    ADS_UL_DYNAMIC_ASSEM_INFO_STRU     *pstUlAssemParmInfo = VOS_NULL_PTR;
    ADS_NV_DYNAMIC_THRESHOLD_STRU       stThreshold;
    TAF_NV_ADS_WAKE_LOCK_CFG_STRU       stWakeLockCfg;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           i;

    for (i = 0; i < ADS_DL_ADQ_MAX_NUM; i++)
    {
        PS_MEM_SET(g_stAdsCtx.stAdsIpfCtx.astIpfDlAdDesc[i], 0x00, (VOS_SIZE_T)(IPF_DLAD0_DESC_SIZE * sizeof(IPF_AD_DESC_S)));
    }

    /* 初始化上行源内存释放队列 */
    IMM_ZcQueueHeadInit(&g_stAdsCtx.stAdsIpfCtx.stUlSrcMemFreeQue);

    /* 初始化上行BD BUFF*/
    PS_MEM_SET(g_stAdsCtx.stAdsIpfCtx.astIpfUlBdCfgParam, 0x00, (VOS_SIZE_T)(IPF_ULBD_DESC_SIZE * sizeof(IPF_CONFIG_ULPARAM_S)));

    /* 初始化下行RD BUFF*/
    PS_MEM_SET(g_stAdsCtx.stAdsIpfCtx.astIpfDlRdDesc, 0x00, (VOS_SIZE_T)(IPF_DLRD_DESC_SIZE * sizeof(IPF_RD_DESC_S)));

    PS_MEM_SET(&stWakeLockCfg, 0x00, sizeof(TAF_NV_ADS_WAKE_LOCK_CFG_STRU));

    /* 默认上行数据发送保护定时器时长为10ms */
    g_stAdsCtx.stAdsIpfCtx.ulProtectTmrLen   = 10;

    pstUlAssemParmInfo = &g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo;

    PS_MEM_SET(&stThreshold, 0x00, (VOS_SIZE_T)sizeof(ADS_NV_DYNAMIC_THRESHOLD_STRU));

    ulRet = NV_ReadEx(MODEM_ID_0,
                      en_NV_Item_ADS_DYNAMIC_THRESHOLD_CFG,
                      &stThreshold,
                      sizeof(ADS_NV_DYNAMIC_THRESHOLD_STRU));
    if(NV_OK != ulRet)
    {
        pstUlAssemParmInfo->ulActiveFlag                      = VOS_FALSE;
        pstUlAssemParmInfo->ulProtectTmrExpCnt                = 0;
        pstUlAssemParmInfo->stWaterMarkLevel.ulWaterLevel1    = 80;
        pstUlAssemParmInfo->stWaterMarkLevel.ulWaterLevel2    = 150;
        pstUlAssemParmInfo->stWaterMarkLevel.ulWaterLevel3    = 500;
        pstUlAssemParmInfo->stWaterMarkLevel.ulWaterLevel4    = 0xFFFFFFFF;

        pstUlAssemParmInfo->stThresholdLevel.ulThreshold1     = 1;
        pstUlAssemParmInfo->stThresholdLevel.ulThreshold2     = 13;
        pstUlAssemParmInfo->stThresholdLevel.ulThreshold3     = 60;
        pstUlAssemParmInfo->stThresholdLevel.ulThreshold4     = 64;
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_InitIpfCtx: NV read failed !");
    }

    pstUlAssemParmInfo->ulActiveFlag                      = stThreshold.ulActiveFlag;
    pstUlAssemParmInfo->ulProtectTmrExpCnt                = stThreshold.ulProtectTmrExpCnt;
    pstUlAssemParmInfo->stWaterMarkLevel.ulWaterLevel1    = stThreshold.stWaterMarkLevel.ulWaterLevel1;
    pstUlAssemParmInfo->stWaterMarkLevel.ulWaterLevel2    = stThreshold.stWaterMarkLevel.ulWaterLevel2;
    pstUlAssemParmInfo->stWaterMarkLevel.ulWaterLevel3    = stThreshold.stWaterMarkLevel.ulWaterLevel3;
    pstUlAssemParmInfo->stWaterMarkLevel.ulWaterLevel4    = stThreshold.stWaterMarkLevel.ulWaterLevel4;

    pstUlAssemParmInfo->stThresholdLevel.ulThreshold1     = stThreshold.stThresholdLevel.ulThreshold1;
    pstUlAssemParmInfo->stThresholdLevel.ulThreshold2     = stThreshold.stThresholdLevel.ulThreshold2;
    pstUlAssemParmInfo->stThresholdLevel.ulThreshold3     = stThreshold.stThresholdLevel.ulThreshold3;
    pstUlAssemParmInfo->stThresholdLevel.ulThreshold4     = stThreshold.stThresholdLevel.ulThreshold4;

    /* 默认上行数据统计定时器时长为100ms */
    pstUlAssemParmInfo->stThresholdStatInfo.ulStatTmrLen = 100;
    pstUlAssemParmInfo->stThresholdStatInfo.ulStatPktNum = 0;

    /* 超时时长大于零才需要启动jiffies保护定时器 */
    if (0 != pstUlAssemParmInfo->ulProtectTmrExpCnt)
    {
        pstUlAssemParmInfo->ulProtectTmrCnt = ADS_GET_CURR_KERNEL_TIME();
    }

    /* 默认攒包的最大个数 */
    if (VOS_TRUE == pstUlAssemParmInfo->ulActiveFlag)
    {
        g_stAdsCtx.stAdsIpfCtx.ulThredHoldNum = ADS_UL_DATA_THRESHOLD_ONE;
    }
    else
    {
        g_stAdsCtx.stAdsIpfCtx.ulThredHoldNum = 32;
    }

    /* 默认数据不在发送 */
    g_stAdsCtx.stAdsIpfCtx.ucSendingFlg = VOS_FALSE;

    PS_MEM_SET(&(g_stAdsCtx.stAdsIpfCtx.stDev), 0x00, (VOS_SIZE_T)sizeof(struct device));
    g_stAdsCtx.stAdsIpfCtx.stDev.dma_mask = &g_ullAdsDmaMask;

    wake_lock_init(&g_stAdsCtx.stAdsIpfCtx.stUlBdWakeLock, WAKE_LOCK_SUSPEND, "ipf_bd_wake");
    wake_lock_init(&g_stAdsCtx.stAdsIpfCtx.stDlRdWakeLock, WAKE_LOCK_SUSPEND, "ipf_rd_wake");

    wake_lock_init(&g_stAdsCtx.stAdsIpfCtx.stRxWakeLock, WAKE_LOCK_SUSPEND, "ads_rx_wake");
    wake_lock_init(&g_stAdsCtx.stAdsIpfCtx.stTxWakeLock, WAKE_LOCK_SUSPEND, "ads_tx_wake");

    g_stAdsCtx.stAdsIpfCtx.ulWakeLockEnable         = VOS_FALSE;

    g_stAdsCtx.stAdsIpfCtx.ulUlBdWakeLockCnt        = 0;
    g_stAdsCtx.stAdsIpfCtx.ulDlRdWakeLockCnt        = 0;

    g_stAdsCtx.stAdsIpfCtx.ulRxWakeLockTimeout      = 0;
    g_stAdsCtx.stAdsIpfCtx.ulTxWakeLockTimeout      = 0;

    g_stAdsCtx.stAdsIpfCtx.ulTxWakeLockTmrLen       = 500;
    g_stAdsCtx.stAdsIpfCtx.ulRxWakeLockTmrLen       = 500;

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_ADS_WAKE_LOCK_CFG,
                      &stWakeLockCfg, sizeof(TAF_NV_ADS_WAKE_LOCK_CFG_STRU));
    if (NV_OK == ulRet)
    {
        g_stAdsCtx.stAdsIpfCtx.ulWakeLockEnable     = stWakeLockCfg.ulEnable;
        g_stAdsCtx.stAdsIpfCtx.ulTxWakeLockTmrLen   = stWakeLockCfg.ulTxWakeTimeout;
        g_stAdsCtx.stAdsIpfCtx.ulRxWakeLockTmrLen   = stWakeLockCfg.ulRxWakeTimeout;
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_InitTiCtx
 功能描述  : 初始化定时器的上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月13日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_InitTiCtx(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i = 0; i < ADS_MAX_TIMER_NUM; i++)
    {
        g_stAdsCtx.astAdsTiCtx[i].hTimer        = VOS_NULL_PTR;
        g_stAdsCtx.astAdsTiCtx[i].enTimerStatus = ADS_TIMER_STATUS_STOP;
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_InitResetSem
 功能描述  : 初始化ADS复位的信号量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年04月15日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID ADS_InitResetSem(VOS_VOID)
{
    g_stAdsCtx.hULResetSem  = VOS_NULL_PTR;
    g_stAdsCtx.hDLResetSem  = VOS_NULL_PTR;

    /* 分配二进制信号量 */
    if (VOS_OK != VOS_SmBCreate( "UL", 0, VOS_SEMA4_FIFO, &g_stAdsCtx.hULResetSem))
    {
        ADS_TRACE_HIGH("Create ADS acpu UL_CNF sem failed!\n");
        ADS_DBG_UL_RESET_CREATE_SEM_FAIL_NUM(1);
        return;
    }

    if (VOS_OK != VOS_SmBCreate( "DL", 0, VOS_SEMA4_FIFO, &g_stAdsCtx.hDLResetSem))
    {
        ADS_TRACE_HIGH("Create ADS acpu DL_CNF sem failed!\n");
        ADS_DBG_DL_RESET_CREATE_SEM_FAIL_NUM(1);
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_InitCtx
 功能描述  : 初始化ADS上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:初始化上下文
  2.日    期   : 2013年04月15日
    作    者   : 范晶
    修改内容   : C核单独复位
  3.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : Share-PDP项目增加过滤表初始化
  4.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理编译warning
*****************************************************************************/
VOS_VOID ADS_InitCtx(VOS_VOID)
{
    PS_MEM_SET(&g_stAdsStats, 0, sizeof(g_stAdsStats));

    /* 初始化每个实例的上下文 */
    ADS_InitSpecCtx();

    /* 初始化数据统计的上下文 */
    ADS_InitStatsInfoCtx();

    /* 初始化IPF相关的上下文 */
    ADS_InitIpfCtx();

    /* 初始化定时器上下文 */
    ADS_InitTiCtx();

    /* 初始化复位信号量 */
    ADS_InitResetSem();

    /* 初始化ADS过滤器上下文 */
    ADS_FILTER_InitCtx();

    /* 初始化当前实例索引值 */
    g_stAdsCtx.ucAdsCurInstanceIndex = ADS_INSTANCE_INDEX_0;

    return;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

