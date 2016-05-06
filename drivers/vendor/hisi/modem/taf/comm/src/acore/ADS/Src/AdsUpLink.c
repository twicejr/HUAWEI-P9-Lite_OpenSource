
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AdsUpLink.h"
#include "AcpuReset.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "AdsFilter.h"
#include "AdsDebug.h"
#include "AdsMntn.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_UPLINK_C
/*lint +e767*/


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : ADS_UL_CCpuResetCallback
 功能描述  : C核单独复位时ADS UL的回调处理函数
 输入参数  : enParam   -- 0表示复位前， 其他表示复位后
             iUserData -- 用户数据
 输出参数  : 无
 返 回 值  : VOS_INT
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年04月10日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_INT ADS_UL_CCpuResetCallback(
    DRV_RESET_CB_MOMENT_E               enParam,
    VOS_INT                             iUserData
)
{
    ADS_CCPU_RESET_IND_STRU                 *pstMsg = VOS_NULL_PTR;

    /* 参数为0表示复位前调用 */
    if (MDRV_RESET_CB_BEFORE == enParam)
    {
        ADS_TRACE_HIGH("before reset: enter.\n");

        ADS_SetUlResetFlag(VOS_TRUE);

        /* 构造消息 */
        pstMsg = (ADS_CCPU_RESET_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_ADS_UL,
                                                                        sizeof(ADS_CCPU_RESET_IND_STRU));
        if (VOS_NULL_PTR == pstMsg)
        {
            ADS_TRACE_HIGH("before reset: alloc msg failed.\n");
            return VOS_ERROR;
        }

        /* 填写消息头 */
        pstMsg->ulReceiverPid               = ACPU_PID_ADS_UL;
        pstMsg->enMsgId                     = ID_ADS_CCPU_RESET_START_IND;

        /* 发消息 */
        if (VOS_OK != PS_SEND_MSG(ACPU_PID_ADS_UL, pstMsg))
        {
            ADS_TRACE_HIGH("before reset: send msg failed.\n");
            return VOS_ERROR;
        }

        /* 等待回复信号量初始为锁状态，等待消息处理完后信号量解锁。 */
        if (VOS_OK != VOS_SmP(ADS_GetULResetSem(), ADS_RESET_TIMEOUT_LEN))
        {
            ADS_TRACE_HIGH("before reset: VOS_SmP failed.\n");
            ADS_DBG_UL_RESET_LOCK_FAIL_NUM(1);
            return VOS_ERROR;
        }

        ADS_TRACE_HIGH("before reset: succ.\n");
        return VOS_OK;
    }
    /* 复位后 */
    else if (MDRV_RESET_CB_AFTER == enParam)
    {
        ADS_TRACE_HIGH("after reset enter.\n");

        ADS_SetUlResetFlag(VOS_FALSE);

        ADS_TRACE_HIGH("after reset: succ.\n");
        ADS_DBG_UL_RESET_SUCC_NUM(1);
        return VOS_OK;
    }
    else
    {
        return VOS_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : ADS_UL_StartDsFlowStats
 功能描述  : 启动流量统计
 输入参数  : ucInstance - 实体索引
             ucRabId    - RABID [5,15]
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月22日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID ADS_UL_StartDsFlowStats(
    VOS_UINT8                           ucInstance,
    VOS_UINT8                           ucRabId
)
{
    /* 如果上行队列存在, 则启动流量统计定时器 */
    if (VOS_OK == ADS_UL_IsQueueExistent(ucInstance, ucRabId))
    {
        ADS_StartTimer(TI_ADS_DSFLOW_STATS, TI_ADS_DSFLOW_STATS_LEN);
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_UL_StopDsFlowStats
 功能描述  : 停止流量统计
 输入参数  : ucInstance - 实体索引
             ucRabId    - RABID [5,15]
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月22日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID ADS_UL_StopDsFlowStats(
    VOS_UINT8                           ucInstance,
    VOS_UINT8                           ucRabId
)
{
    /* 如果所有上行队列已不存在，则停止流量统计定时器并清空流量统计信息 */
    if (VOS_FALSE == ADS_UL_IsAnyQueueExist())
    {
        ADS_StopTimer(ACPU_PID_ADS_UL, TI_ADS_DSFLOW_STATS, ADS_TIMER_STOP_CAUSE_USER);
        ADS_InitStatsInfoCtx();
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_UL_SendPacket
 功能描述  : ADS上行为上层模块提供的数据发送函数，本接口不释放内存。
             上层模块根据返回值判断是否需要释放内存
 输入参数  : pstImmZc  --- IMM数据
             ucExRabId --- RABID [5, 15]
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_UL_SendPacket(
    IMM_ZC_STRU                        *psImmZc,
    VOS_UINT8                           ucExRabId
)
{
    VOS_UINT8                           ucInstance;
    VOS_UINT8                           ucRabId;

    /* 判断是否为空数据包 */
    if (VOS_NULL_PTR == psImmZc)
    {
        ADS_WARNING_LOG(ACPU_PID_ADS_UL, "ADS_UL_SendPacket: psImmZc is null!");
        return VOS_ERR;
    }

    /* 增加上行接收数据统计个数 */
    ADS_DBG_UL_RMNET_RX_PKT_NUM(1);

    /* 统计上行周期性收到的数据字节数，用于流量查询 */
    ADS_RECV_UL_PERIOD_PKT_NUM(psImmZc->len);

    /* 检查MODEMID */
    ucInstance = ADS_GET_MODEMID_FROM_EXRABID(ucExRabId);
    if (ucInstance >= ADS_INSTANCE_MAX_NUM)
    {
        ADS_DBG_UL_RMNET_MODEMID_ERR_NUM(1);
        return VOS_ERR;
    }

    /* 检查RABID */
    ucRabId = ADS_GET_RABID_FROM_EXRABID(ucExRabId);
    if (!ADS_IS_RABID_VALID(ucRabId))
    {
        ADS_DBG_UL_RMNET_RABID_NUM(1);
        return VOS_ERR;
    }

    /* 将pstData插入到ucRabId对应的缓存队列中 */
    if (VOS_OK != ADS_UL_InsertQueue(ucInstance, psImmZc, ucRabId))
    {
        ADS_DBG_UL_RMNET_ENQUE_FAIL_NUM(1);
        return VOS_ERR;
    }

    ADS_DBG_UL_RMNET_ENQUE_SUCC_NUM(1);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_UL_SendPacketEx
 功能描述  : 上行发送数据扩展接口, 使用该接口发送的数据在ADS记录其信息, 用于
             下行数据过滤匹配, 该接口必须和ADS_DL_RegFilterDataCallback配合
             使用, 只有使用ADS_DL_RegFilterDataCallback注册过下行过滤回调后,
             下行数据才需要根据使用该接口记录的信息进行过滤
 输入参数  : pstImmZc  --- IMM数据
             enIpType  --- IP类型
             ucExRabId --- RABID [5, 15]
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年6月3日
    作    者   : L47619
    修改内容   : V3R3 Share-PDP项目修改
*****************************************************************************/
VOS_UINT32 ADS_UL_SendPacketEx(
    IMM_ZC_STRU                        *pstImmZc,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType,
    VOS_UINT8                           ucExRabId
)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo;
    VOS_UINT8                           ucInstance;
    VOS_UINT8                           ucRabId;

    /* 判断是否为空数据包 */
    if (VOS_NULL_PTR == pstImmZc)
    {
        ADS_WARNING_LOG(ACPU_PID_ADS_UL, "ADS_UL_SendPacketEx: pstImmZc is null!");
        return VOS_ERR;
    }

    /* 增加上行接收数据统计个数 */
    ADS_DBG_UL_RMNET_RX_PKT_NUM(1);

    /* 统计上行周期性收到的数据字节数，用于流量查询 */
    ADS_RECV_UL_PERIOD_PKT_NUM(pstImmZc->len);

    /* 检查MODEMID */
    ucInstance = ADS_GET_MODEMID_FROM_EXRABID(ucExRabId);
    if (ucInstance >= ADS_INSTANCE_MAX_NUM)
    {
        ADS_DBG_UL_RMNET_MODEMID_ERR_NUM(1);
        return VOS_ERR;
    }

    /* 检查RABID */
    ucRabId = ADS_GET_RABID_FROM_EXRABID(ucExRabId);
    if (!ADS_IS_RABID_VALID(ucRabId))
    {
        ADS_DBG_UL_RMNET_RABID_NUM(1);
        return VOS_ERR;
    }

    /* 判断是否已经注册过下行过滤回调函数，若注册过，则需要进行过滤信息的提取，否则直接发送报文 */
    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstance, ucRabId);
    if (VOS_NULL_PTR != pstDlRabInfo->pRcvDlFilterDataFunc)
    {
        /* 调用过滤上行数据包处理函数 */
        ADS_FILTER_ProcUlPacket(pstImmZc, enIpType);
    }

    /* 将pstData插入到ucRabId对应的缓存队列中 */
    if (VOS_OK != ADS_UL_InsertQueue(ucInstance, pstImmZc, ucRabId))
    {
        ADS_DBG_UL_RMNET_ENQUE_FAIL_NUM(1);
        return VOS_ERR;
    }

    ADS_DBG_UL_RMNET_ENQUE_SUCC_NUM(1);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_UL_GetInstanceNextQueueNode
 功能描述  : 获取上行一个实例的结点
 输入参数  : VOS_UINT8                           ucInstanceIndex,
 输出参数  : VOS_UINT8                          *pucRabId
 返 回 值  : IMM_ZC_STRU                        *pstNode
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月20日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年02月21日
    作    者   : f00179208
    修改内容   : V7R1C50项目，根据优先级发送数据
  3.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例
*****************************************************************************/
IMM_ZC_STRU* ADS_UL_GetInstanceNextQueueNode(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                          *pucRabId,
    VOS_UINT8                          *puc1XorHrpdUlIpfFlag
)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucCurIndex;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx;
    IMM_ZC_STRU                        *pstNode;

    pstAdsUlCtx = ADS_GetUlCtx(ucInstanceIndex);

    pucCurIndex = &pstAdsUlCtx->ucAdsUlCurIndex;

    pstNode     = VOS_NULL_PTR;

    /* 优先级方式 */
    for (i = 0; i < ADS_RAB_NUM_MAX; i++)
    {
        /* 因为队列已经有序，当前队列无效则代表后面所有队列都无效
           需跳过后面所有无效队列，继续从头查找 */
        if (VOS_NULL_PTR == ADS_UL_GET_QUEUE_LINK_INFO(ucInstanceIndex, *pucCurIndex))
        {
            i += ADS_RAB_NUM_MAX - (*pucCurIndex + 1U);

            *pucCurIndex = 0;

            continue;
        }

        /* 队列为有效队列但无数据时，继续向后查找 */
        if (0 == ADS_UL_GET_QUEUE_LINK_INFO(ucInstanceIndex, *pucCurIndex)->qlen)
        {
            /* 发送下一个队列的数据时，将本队列记录数清空 */
            ADS_UL_CLR_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex);

            *pucCurIndex = (*pucCurIndex + 1) % ADS_RAB_NUM_MAX;

            continue;
        }

        /* 根据优先级等级对应的加权数发送数据 */
        /* 优先级高的先发送 */
        if (ADS_UL_GET_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex) < ADS_UL_GET_QUEUE_PRI_WEIGHTED_NUM(ucInstanceIndex, *pucCurIndex))
        {
            /* 获取队列头结点 */
            pstNode = IMM_ZcDequeueHead(ADS_UL_GET_QUEUE_LINK_INFO(ucInstanceIndex, *pucCurIndex));

            /* 获取该结点的RabId */
            *pucRabId = ADS_UL_GET_PRIO_QUEUE_INDEX(ucInstanceIndex, *pucCurIndex);

            /* 获取该节点是否是1X或者HRPD的包 */
            *puc1XorHrpdUlIpfFlag = ADS_UL_GET_1X_OR_HRPD_UL_IPF_FLAG(ucInstanceIndex, *pucCurIndex);

            /* 本队列记录数增加 1*/
            ADS_UL_SET_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex, 1);

            /* 如果已经发送完本队列的优先级加权数个数的数据，则跳到下个队列发送数据 */
            if (ADS_UL_GET_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex) == ADS_UL_GET_QUEUE_PRI_WEIGHTED_NUM(ucInstanceIndex, *pucCurIndex))
            {
                /* 发送下一个队列的数据时，将本队列记录数清空 */
                ADS_UL_CLR_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex);

                *pucCurIndex = (*pucCurIndex + 1) % ADS_RAB_NUM_MAX;
            }

            break;
        }
    }


    return pstNode;
}

/*****************************************************************************
 函 数 名  : ADS_UL_GetNextQueueNode
 功能描述  : DSDA Phase II:双实例
 输入参数  : VOS_UINT8 *pucRabId
 输出参数  : 无
 返 回 值  : IMM_ZC_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
IMM_ZC_STRU* ADS_UL_GetNextQueueNode(
    VOS_UINT8                          *pucRabId,
    VOS_UINT8                          *pucInstanceIndex,
    VOS_UINT8                          *puc1XorHrpdUlIpfFlag
)
{
    ADS_CTX_STRU                       *pstAdsCtx = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstNode = VOS_NULL_PTR;
    VOS_UINT8                           i;
    VOS_UINT8                           ucCurInstanceIndex;

    pstAdsCtx = ADS_GetAllCtx();

    ucCurInstanceIndex = pstAdsCtx->ucAdsCurInstanceIndex;

    for (i = 0; i < ADS_INSTANCE_MAX_NUM; i++)
    {
        ucCurInstanceIndex = ucCurInstanceIndex % ADS_INSTANCE_MAX_NUM;

        pstNode = ADS_UL_GetInstanceNextQueueNode(ucCurInstanceIndex, pucRabId, puc1XorHrpdUlIpfFlag);

        if (VOS_NULL_PTR != pstNode)
        {
            break;
        }

        ucCurInstanceIndex++;
    }

    /* 返回实例号用于配置BD时填modem id */
    *pucInstanceIndex = ucCurInstanceIndex;

    /* 记录下次从哪个实例中去数据 */
    pstAdsCtx->ucAdsCurInstanceIndex = (ucCurInstanceIndex + 1) % ADS_INSTANCE_MAX_NUM;

    return pstNode;
}

/*****************************************************************************
 函 数 名  : ADS_UL_SaveIpfSrcMem
 功能描述  : 在上行配置完IPF BD后，保存需要释放的源内存
 输入参数  : const ADS_IPF_BD_BUFF_STRU         *pstIpfUlBdBuff
             VOS_UINT32                          ulSaveNum
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_UL_SaveIpfSrcMem(
    const ADS_IPF_BD_BUFF_STRU         *pstIpfUlBdBuff,
    VOS_UINT32                          ulSaveNum
)
{
    VOS_UINT32                          ulCnt;

    if (ulSaveNum > IPF_ULBD_DESC_SIZE)
    {
        return;
    }

    for (ulCnt = 0; ulCnt < ulSaveNum; ulCnt++)
    {
        IMM_ZcQueueTail(ADS_UL_IPF_SRCMEM_FREE_QUE(), pstIpfUlBdBuff[ulCnt].pstPkt);
        ADS_DBG_UL_BDQ_SAVE_SRC_MEM_NUM(1);
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_UL_FreeIpfSrcMem
 功能描述  : 释放源内存队列中可释放的已经配置成功的源系统内存
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_UL_FreeIpfSrcMem(VOS_VOID)
{
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    VOS_UINT32                          ulIdleBD;
    VOS_UINT32                          ulBusyBD;
    VOS_UINT32                          ulCanFree;
    VOS_UINT32                          ulQueCnt;
    VOS_UINT32                          ulCnt;

    /* que is empty */
    ulQueCnt = IMM_ZcQueueLen(ADS_UL_IPF_SRCMEM_FREE_QUE());
    if (0 == ulQueCnt)
    {
        return;
    }

    /* get busy bd num */
    ulIdleBD = mdrv_ipf_get_uldesc_num();
    ulBusyBD = IPF_ULBD_DESC_SIZE - ulIdleBD;
    if (ulQueCnt >= ulBusyBD)
    {
        ulCanFree = ulQueCnt - ulBusyBD;
    }
    else
    {
        ADS_ERROR_LOG3(ACPU_PID_ADS_UL, "ADS_UL_FreeIpfUlSrcMem: Buff Num Less IPF Busy BD Num. ulQueCnt, ulBusyBD, ulIdleBD", ulQueCnt, ulBusyBD, ulIdleBD);
        ADS_DBG_UL_BDQ_FREE_SRC_MEM_ERR(1);
        return;
    }

    /* free src mem */
    for (ulCnt = 0; ulCnt < ulCanFree; ulCnt++)
    {
        pstImmZc = IMM_ZcDequeueHead(ADS_UL_IPF_SRCMEM_FREE_QUE());
        if (VOS_NULL_PTR == pstImmZc)
        {
            break;
        }

        /* 先刷CACHE, 再释放回收 */
        ADS_IPF_UL_MEM_UNMAP(pstImmZc, IMM_ZcGetUsedLen(pstImmZc));
        IMM_ZcFree(pstImmZc);
        ADS_DBG_UL_BDQ_FREE_SRC_MEM_NUM(1);
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_UL_ClearIpfSrcMem
 功能描述  : 清空上行IPF Src Mem
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月31日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_UL_ClearIpfSrcMem(VOS_VOID)
{
    IMM_ZC_STRU                      *pstImmZc = VOS_NULL_PTR;
    VOS_UINT32                        ulQueCnt;
    VOS_UINT32                        ulCnt;
    VOS_UINT32                        ulIpfUlBdNum;
    VOS_UINT8                         i;

    ulQueCnt = IMM_ZcQueueLen(ADS_UL_IPF_SRCMEM_FREE_QUE());
    if (0 == ulQueCnt)
    {
        return;
    }

    /* 所有的PDP都去激活后，并且BD已经全部空闲，即上行数据全部搬完，才清空上行源内存队列 */
    for (i = 0; i < ADS_INSTANCE_MAX_NUM; i++)
    {
        if (VOS_FALSE == ADS_UL_CheckAllQueueEmpty(i))
        {
            return;
        }
    }

    ulIpfUlBdNum = mdrv_ipf_get_uldesc_num();
    /* 空闲BD最多63个 */
    if (IPF_ULBD_DESC_SIZE != ulIpfUlBdNum)
    {
        return;
    }

    /*free src mem*/
    for (ulCnt = 0; ulCnt < ulQueCnt; ulCnt++)
    {
        pstImmZc = IMM_ZcDequeueHead(ADS_UL_IPF_SRCMEM_FREE_QUE());
        if (VOS_NULL_PTR == pstImmZc)
        {
            break;
        }

        /* 先刷CACHE, 再释放回收 */
        ADS_IPF_UL_MEM_UNMAP(pstImmZc, pstImmZc->len);
        IMM_ZcFree(pstImmZc);
        ADS_DBG_UL_BDQ_FREE_SRC_MEM_NUM(1);
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_UL_GetBdFcHead
 功能描述  : 获取IPF过滤组
 输入参数  : VOS_UINT8                           ucInstanceIndex
             VOS_UINT8                           uc1XorHrpdUlIpfFlag
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月19日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 ADS_UL_GetBdFcHead(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           uc1XorHrpdUlIpfFlag
)
{
    VOS_UINT8                           ucIpfFlterCh;
    if (VOS_TRUE == uc1XorHrpdUlIpfFlag)
    {
        ucIpfFlterCh = ADS_UL_IPF_1XHRPD;
    }
    else
    {
        ucIpfFlterCh = ucInstanceIndex;
    }

    return ucIpfFlterCh;
}

/*****************************************************************************
 函 数 名  : ADS_UL_CalcBuffTime
 功能描述  : 计算数据缓存时间
 输入参数  : ulBeginSlice --- 起始时间
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_UL_CalcBuffTime(VOS_UINT32 ulBeginSlice)
{
    VOS_UINT32                          ulEndSlice;

    ulEndSlice = VOS_GetSlice();
    if (ulEndSlice > ulBeginSlice)
    {
        return (ulEndSlice - ulBeginSlice);
    }
    else
    {
        return (VOS_NULL_DWORD - ulBeginSlice + ulEndSlice + 1);
    }
}

/*****************************************************************************
 函 数 名  : ADS_UL_ConfigBD
 功能描述  : ADS配置上行BD写入IPF
 输入参数  : VOS_UINT32 ulBdNum
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年9月22日
    作    者   : A00165503
    修改内容   : DTS2015081008249: ADS数传过程中持锁, 防止系统进入休眠

*****************************************************************************/
VOS_VOID ADS_UL_ConfigBD(VOS_UINT32 ulBdNum)
{
    IPF_CONFIG_ULPARAM_S               *pstUlCfgParam = VOS_NULL_PTR;
    ADS_IPF_BD_BUFF_STRU               *pstUlBdBuff   = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstImmZc      = VOS_NULL_PTR;
    VOS_UINT32                          ulBeginSlice;
    VOS_UINT32                          ulTmp;
    VOS_UINT32                          ulCnt;
    VOS_INT32                           lRslt;
    VOS_UINT8                           ucInstance;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           uc1XorHrpdUlIpfFlag;

    for (ulCnt = 0; ulCnt < ulBdNum; ulCnt++)
    {
        pstImmZc = ADS_UL_GetNextQueueNode(&ucRabId, &ucInstance, &uc1XorHrpdUlIpfFlag);
        if (VOS_NULL_PTR == pstImmZc)
        {
            break;
        }

        pstUlBdBuff = ADS_UL_GET_BD_BUFF_PTR(ulCnt);
        pstUlBdBuff->pstPkt = pstImmZc;

        ulBeginSlice  = ADS_UL_GET_SLICE_FROM_IMM(pstImmZc);
        pstUlCfgParam = ADS_UL_GET_BD_CFG_PARA_PTR(ulCnt);
        pstUlCfgParam->u32Data      = (VOS_UINT32)virt_to_phys((VOS_VOID *)pstImmZc->data);
        pstUlCfgParam->u16Len       = (VOS_UINT16)pstImmZc->len;
        pstUlCfgParam->u16UsrField1 = (VOS_UINT16)ADS_UL_BUILD_BD_USER_FIELD_1(ucInstance, ucRabId);
        pstUlCfgParam->u32UsrField3 = (VOS_UINT32)ADS_UL_CalcBuffTime(ulBeginSlice);

        /* Attribute: 中断使能，过滤加搬移，过滤器组号modem0用0，modem1用1 */
        pstUlCfgParam->u16Attribute = (VOS_UINT16)ADS_UL_BUILD_BD_ATTRIBUTE(VOS_FALSE, IPF_MODE_FILTERANDTRANS, ADS_UL_GetBdFcHead(ucInstance, uc1XorHrpdUlIpfFlag));

        ADS_MNTN_HookIpPkt(pstImmZc, ID_IPS_TRACE_ADS_UL,
                           pstUlCfgParam->u16UsrField1, pstUlCfgParam->u32UsrField2,
                           pstUlCfgParam->u32UsrField3, 0);

        /* 刷CAHCE */
        ADS_IPF_UL_MEM_MAP(pstImmZc, pstImmZc->len);
    }

    /* 配置上行数据个数为0 */
    if (0 == ulCnt)
    {
        return;
    }

    /* 最后一个BD配置中断使能 */
    pstUlCfgParam = ADS_UL_GET_BD_CFG_PARA_PTR(ulCnt - 1);
    ADS_UL_SET_BD_ATTR_INT_FLAG(pstUlCfgParam->u16Attribute);

    /* 配置IPF上行BD */
    lRslt = mdrv_ipf_config_ulbd(ulCnt, ADS_UL_GET_BD_CFG_PARA_PTR(0));
    if (IPF_SUCCESS != lRslt)
    {
        /* IPF配置失败, 需要释放源内存 */
        ulTmp = ulCnt;
        for (ulCnt = 0; ulCnt < ulTmp; ulCnt++)
        {
            pstUlBdBuff = ADS_UL_GET_BD_BUFF_PTR(ulCnt);
            IMM_ZcFree(pstUlBdBuff->pstPkt);
            ADS_DBG_UL_BDQ_CFG_BD_FAIL_NUM(1);
        }

        ADS_DBG_UL_BDQ_CFG_IPF_FAIL_NUM(1);
        return;
    }

    /* 将已配置的BD源内存保存到源内存队列 */
    ADS_UL_SaveIpfSrcMem(ADS_UL_GET_BD_BUFF_PTR(0), ulCnt);
    ADS_DBG_UL_BDQ_CFG_BD_SUCC_NUM(ulCnt);
    ADS_DBG_UL_BDQ_CFG_IPF_SUCC_NUM(1);

    ADS_UL_EnableRxWakeLockTimeout(ADS_UL_RX_WAKE_LOCK_TMR_LEN);
    return;
}

/*****************************************************************************
 函 数 名  : ADS_UL_ProcLinkData
 功能描述  : 从缓存队列中取数据包，经过处理后写入IPF
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年3月30日
    作    者   : l60609
    修改内容   : DTS2012031206512：十次获取不到BD启定时器

  3.日    期   : 2012年4月12日
    作    者   : A00165503
    修改内容   : DTS2012020708222: ADS性能优化

  4.日    期   : 2012年4月27日
    作    者   : l60609
    修改内容   : DTS2012041802250: ADS上行10ms延时

  5.日    期   : 2012年8月31日
    作    者   : l60609
    修改内容   : AP适配项目：配置BD前，释放源内存队列中可释放的内存

*****************************************************************************/
VOS_VOID ADS_UL_ProcLinkData(VOS_VOID)
{
    VOS_UINT32                          ulAllUlQueueDataNum;
    VOS_UINT32                          ulIpfUlBdNum;
    VOS_UINT32                          ulSndBdNum;

    /* 处理队列时中的数据 */
    for (;;)
    {
        /* 正在复位过程中直接退出 */
        if (VOS_TRUE == ADS_GetUlResetFlag())
        {
            printk(KERN_ERR "\n ADS_UL_ProcLinkData in ccore reset \n");
            return;
        }


        /* 获取上行可以发送的BD数。 */
        ulIpfUlBdNum = mdrv_ipf_get_uldesc_num();
        if (0 == ulIpfUlBdNum)
        {
            ADS_DBG_UL_BDQ_CFG_IPF_HAVE_NO_BD_NUM(1);

            /* 设置发送结束标志 */
            ADS_UL_SET_SENDING_FLAG(VOS_FALSE);

            /* 启动定时器退出 */
            ADS_StartTimer(TI_ADS_UL_SEND, ADS_UL_GET_PROTECT_TIMER_LEN());
            break;
        }


        /* 设置正在发送标志 */
        ADS_UL_SET_SENDING_FLAG(VOS_TRUE);

        /* 获取当前所有队列中的数据包个数 */
        ulAllUlQueueDataNum = ADS_UL_GetAllQueueDataNum();

        /* 计算当前可发送的BD数目 */
        ulSndBdNum = PS_MIN(ulIpfUlBdNum, ulAllUlQueueDataNum);

        /* 释放保存的源内存 */
        ADS_UL_FreeIpfSrcMem();

        /* 配置BD，写入IPF */
        ADS_UL_ConfigBD(ulSndBdNum);

        /* 获取当前所有队列中的数据包个数 */
        ulAllUlQueueDataNum = ADS_UL_GetAllQueueDataNum();

        /* 当前队列中没有数据，退出，等待下次队列由空变为非空处理 */
        if (0 == ulAllUlQueueDataNum)
        {
            /* 设置发送结束标志 */
            ADS_UL_SET_SENDING_FLAG(VOS_FALSE);
            break;
        }
        /* 当前队列中有数据，但是需要继续攒包 */
        else if (ulAllUlQueueDataNum <= ADS_UL_SEND_DATA_NUM_THREDHOLD)
        {
            ADS_StartTimer(TI_ADS_UL_SEND, ADS_UL_GET_PROTECT_TIMER_LEN());

            /* 设置发送结束标志 */
            ADS_UL_SET_SENDING_FLAG(VOS_FALSE);
            break;
        }
        else
        {
            continue;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_UL_ProcPdpStatusInd
 功能描述  : 处理PDP状态变化函数
 输入参数  : MsgBlock *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_UL_ProcPdpStatusInd(
    ADS_PDP_STATUS_IND_STRU            *pstStatusInd
)
{
    VOS_UINT8                           ucInstanceIndex;
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;
    ADS_QCI_TYPE_ENUM_UINT8             enPrio;

    enPktType                           = ADS_CDS_IPF_PKT_TYPE_IP;

    ucInstanceIndex                     = (VOS_UINT8)pstStatusInd->enModemId;

    enPrio                              = pstStatusInd->enQciType;

    /* RabId合法性检查 */
    if (!ADS_IS_RABID_VALID(pstStatusInd->ucRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_UL, "ADS_UL_ProcPdpStatusInd: ucRabId is ", pstStatusInd->ucRabId);
        return VOS_ERR;
    }

    /* 如果不采用优先级，则修改所有PDP的QCI为相同优先级，根据排序算法这样可以使先激活的PDP优先处理 */
    if (VOS_FALSE == g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex].stAdsUlCtx.stQueuePriNv.ulStatus)
    {
        enPrio = ADS_QCI_TYPE_QCI9_NONGBR;
    }

    if (ADS_PDP_PPP == pstStatusInd->enPdpType)
    {
        enPktType = ADS_CDS_IPF_PKT_TYPE_PPP;
    }

    /* 根据PDP状态分别进行处理 */
    switch(pstStatusInd->enPdpStatus)
    {
        /* PDP激活 */
        case ADS_PDP_STATUS_ACT:

            /* 创建缓存队列 */
            ADS_UL_CreateQueue(ucInstanceIndex, pstStatusInd->ucRabId, enPrio, enPktType, pstStatusInd->uc1XorHrpdUlIpfFlag);

            /* 启动流量统计 */
            ADS_UL_StartDsFlowStats(ucInstanceIndex, pstStatusInd->ucRabId);

            break;

        /* PDP修改 */
        case ADS_PDP_STATUS_MODIFY:

            /* 将修改的队列信息更新到上行队列管理中 */
            ADS_UL_UpdateQueueInPdpModified(ucInstanceIndex, enPrio, pstStatusInd->ucRabId);

            break;

        /* PDP去激活 */
        case ADS_PDP_STATUS_DEACT:

            /* 销毁缓存队列 */
            ADS_UL_DestroyQueue(ucInstanceIndex, pstStatusInd->ucRabId);

            /* 当所有的PDP都去激活后，清空源内存队列 */
            ADS_UL_ClearIpfSrcMem();

            /* 停止流量统计 */
            ADS_UL_StopDsFlowStats(ucInstanceIndex, pstStatusInd->ucRabId);

            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_UL_RcvAtPdpStatusInd
 功能描述  : 处理ID_APS_ADS_PDP_STATUS_IND消息
 输入参数  : MsgBlock *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年02月20日
    作    者   : f00179208
    修改内容   : V7R1C50项目，新增PDP状态
  3.日    期   : 2012年8月31日
    作    者   : l60609
    修改内容   : AP适配项目：释放源内存队列
  4.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例
  5.日    期   : 2013年05月22日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT

  6.日    期   : 2013年9月22日
    作    者   : A00165503
    修改内容   : DTS2013092200927: 定时器使用优化
*****************************************************************************/
VOS_UINT32 ADS_UL_RcvTafPdpStatusInd(MsgBlock *pMsg)
{
    ADS_PDP_STATUS_IND_STRU            *pstPdpStatusInd;
    VOS_UINT32                          ulRslt;

    pstPdpStatusInd = (ADS_PDP_STATUS_IND_STRU *)pMsg;

    ulRslt = ADS_UL_ProcPdpStatusInd(pstPdpStatusInd);

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : ADS_UL_RcvCdsIpPacketMsg
 功能描述  : 接收ID_CDS_ADS_IP_PACKET_IND消息
 输入参数  : MsgBlock *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年8月31日
    作    者   : l60609
    修改内容   : AP适配项目：IMM接口修改

  3.日    期   : 2012年12月21日
    作    者   : l60609
    修改内容   : DSDA Phase II
*****************************************************************************/
VOS_UINT32 ADS_UL_RcvCdsIpPacketMsg(MsgBlock *pMsg)
{
    VOS_UINT32                          ulResult;
    ADS_NDIS_DATA_IND_STRU             *pstAdsNdisDataInd;
    IMM_ZC_STRU                        *pstZcData;
    CDS_ADS_DATA_IND_STRU              *pstDataInd;
    VOS_CHAR                           *pstZcPutData;

    pstDataInd = (CDS_ADS_DATA_IND_STRU *)pMsg;

    /* 申请消息  */
    pstAdsNdisDataInd = (ADS_NDIS_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ACPU_PID_ADS_UL,
                                             sizeof(ADS_NDIS_DATA_IND_STRU));

    if (VOS_NULL_PTR == pstAdsNdisDataInd)
    {
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstAdsNdisDataInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(ADS_NDIS_DATA_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息内容 */
    pstAdsNdisDataInd->ulReceiverPid  = PS_PID_APP_NDIS;
    pstAdsNdisDataInd->enMsgId        = ID_ADS_NDIS_DATA_IND;
    pstAdsNdisDataInd->enModemId      = pstDataInd->enModemId;
    pstAdsNdisDataInd->ucRabId        = pstDataInd->ucRabId;
    pstAdsNdisDataInd->enIpPacketType = pstDataInd->enIpPacketType;

    pstZcData = (IMM_ZC_STRU *)IMM_ZcStaticAlloc((VOS_UINT32)pstDataInd->usLen);

    if (VOS_NULL_PTR == pstZcData)
    {
        PS_MEM_FREE(ACPU_PID_ADS_UL, pstAdsNdisDataInd);

        return VOS_ERR;
    }

    /*此步骤不能少，用来偏移数据尾指针*/
    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstZcData, pstDataInd->usLen);

    PS_MEM_CPY(pstZcPutData, pstDataInd->aucData, pstDataInd->usLen);

    pstAdsNdisDataInd->pstSkBuff = pstZcData;

    /* 调用VOS发送原语 */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_UL, pstAdsNdisDataInd);

    if(VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_RcvCdsIpPacketMsg: Send Msg Fail!");

        IMM_ZcFree(pstZcData);

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_UL_RcvCcpuResetStartInd
 功能描述  : ADS_UL收到ADS_UL消息ID_CCPU_RESET_START_ADS_UL_TO_ADS_UL_NOTIFY的处理
 输入参数  : pMsg:消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年04月15日
   作    者   : f00179208
   修改内容   : 新生成函数

 2.日    期   : 2013年06月18日
   作    者   : l00198894
   修改内容   : V3R3 Share-PDP项目新增函数

  3.日    期   : 2015年9月1日
    作    者   : A00165503
    修改内容   : DTS2015082300106: 下行灌小包, A核触发C核单独复位后整机重启
*****************************************************************************/
VOS_UINT32 ADS_UL_RcvCcpuResetStartInd(
    MsgBlock                           *pstMsg
)
{
    VOS_UINT8                           ucInsIndex;
    VOS_UINT8                           ucRabIndex;
    VOS_UINT8                           ucTiIndex;
    ADS_CTX_STRU                       *pstAdsCtx = VOS_NULL_PTR;

    ADS_TRACE_HIGH("enter.\n");

    pstAdsCtx = ADS_GetAllCtx();

    /* 清空所有上行缓存队列 */
    for (ucInsIndex = 0; ucInsIndex < ADS_INSTANCE_MAX_NUM; ucInsIndex++)
    {
        for (ucRabIndex = 0; ucRabIndex < ADS_RAB_ID_MAX + 1; ucRabIndex++)
        {
            ADS_UL_DestroyQueue(ucInsIndex, ucRabIndex);
        }
    }

    /* 清空源内存队列 */
    ADS_UL_ClearIpfSrcMem();

    /* 停止所有启动的定时器 */
    for (ucTiIndex = 0; ucTiIndex < ADS_MAX_TIMER_NUM; ucTiIndex++)
    {
        ADS_StopTimer(ACPU_PID_ADS_UL, ucTiIndex, ADS_TIMER_STOP_CAUSE_USER);
    }

    /* 重置上行上下文 */
    ADS_ResetUlCtx();

    /* 重置IPF相关的上下文 */
    ADS_ResetIpfCtx();

    /* 重置当前实例索引值 */
    pstAdsCtx->ucAdsCurInstanceIndex = ADS_INSTANCE_INDEX_0;

    /* 重置ADS Filter过滤上下文 */
    ADS_FILTER_Reset();

    /* 释放信号量，使得调用API任务继续运行 */
    VOS_SmV(ADS_GetULResetSem());

    ADS_TRACE_HIGH("leave.\n");
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_UL_RcvTiSendExpired
 功能描述  : TI_ADS_UL_SEND超时处理函数
 输入参数  : VOS_UINT32                          ulParam,
             VOS_UINT32                          ulTimerName
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年01月25日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_UL_RcvTiSendExpired(
    VOS_UINT32                          ulParam,
    VOS_UINT32                          ulTimerName
)
{
    ADS_UL_SndEvent(ADS_UL_EVENT_DATA_PROC);
    ADS_DBG_UL_10MS_TMR_TRIG_EVENT(1);
    return;
}

/*****************************************************************************
 函 数 名  : ADS_UL_RcvTiDsFlowStatsExpired
 功能描述  : 流量统计定时器超时处理，计算ADS数传中当前的速率
 输入参数  : ulTimerName
             ulParam
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年1月10日
   作    者   : l60609
   修改内容   : 新生成函数

  2.日    期   : 2012年4月12日
    作    者   : A00165503
    修改内容   : DTS2012020708222: ADS性能优化

  3.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例

  4.日    期   : 2013年9月22日
    作    者   : A00165503
    修改内容   : DTS2013092200927: 定时器使用优化

  5.日    期   : 2015年5月21日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_VOID ADS_UL_RcvTiDsFlowStatsExpired(
    VOS_UINT32                          ulTimerName,
    VOS_UINT32                          ulParam
)
{
    VOS_UINT32                          ulTaBytes;
    VOS_UINT32                          ulRate;

    /* 如果没有上行队列存在, 无需统计流量 */
    if (VOS_FALSE == ADS_UL_IsAnyQueueExist())
    {
        ADS_NORMAL_LOG(ACPU_PID_ADS_DL, "ADS_UL_RcvTiDsFlowStatsExpired: no queue is exist!");
        return;
    }

    /* 获取1秒的下行数据个数 */
    ulTaBytes = ADS_GET_DL_PERIOD_PKT_NUM();

    /* 每1秒钟计算一次,单位为:byte/s */
    ulRate = ulTaBytes;
    ADS_SET_CURRENT_DL_RATE(ulRate);

    /* 获取1秒的上行流量 */
    ulTaBytes = ADS_GET_UL_PERIOD_PKT_NUM();

    /* 每1秒钟计算一次,单位为:byte/s */
    ulRate = ulTaBytes;
    ADS_SET_CURRENT_UL_RATE(ulRate);

    /* 每个流量统计周期结束后，需要将周期统计Byte数清除 */
    ADS_CLEAR_UL_PERIOD_PKT_NUM();
    ADS_CLEAR_DL_PERIOD_PKT_NUM();

    /* 启动流量统计定时器*/
    ADS_StartTimer(TI_ADS_DSFLOW_STATS, TI_ADS_DSFLOW_STATS_LEN);

    return ;
}

/*****************************************************************************
 函 数 名  : ADS_UL_RcvTiStatExpired
 功能描述  : 上行统计定时器超时处理
 输入参数  : VOS_UINT32    ulParam,
             VOS_UINT32    ulTimerName
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年06月03日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID ADS_UL_RcvTiDataStatExpired(
    VOS_UINT32                          ulTimerName,
    VOS_UINT32                          ulParam
)
{
    VOS_UINT32                          ulStatPktNum;

    ulStatPktNum = ADS_UL_GET_STAT_PKT_NUM();

    /* 根据数据包个数调整赞包门限 */
    if (ulStatPktNum < ADS_UL_GET_WATER_LEVEL_ONE())
    {
        ADS_UL_SET_SEND_DATA_NUM_THREDHOLD(ADS_UL_DATA_THRESHOLD_ONE);
        ADS_DBG_UL_WM_LEVEL_1_HIT_NUM(1);
    }
    else if (ulStatPktNum <  ADS_UL_GET_WATER_LEVEL_TWO())
    {
        ADS_UL_SET_SEND_DATA_NUM_THREDHOLD(ADS_UL_DATA_THRESHOLD_TWO);
        ADS_DBG_UL_WM_LEVEL_2_HIT_NUM(1);
    }
    else if (ulStatPktNum <  ADS_UL_GET_WATER_LEVEL_THREE())
    {
        ADS_UL_SET_SEND_DATA_NUM_THREDHOLD(ADS_UL_DATA_THRESHOLD_THREE);
        ADS_DBG_UL_WM_LEVEL_3_HIT_NUM(1);
    }
    else
    {
        ADS_UL_SET_SEND_DATA_NUM_THREDHOLD(ADS_UL_DATA_THRESHOLD_FOUR);
        ADS_DBG_UL_WM_LEVEL_4_HIT_NUM(1);
    }

    /* 100ms内没有数据包则该定时器不再启动 */
    if (0 != ulStatPktNum)
    {
        /* 重新启动上行统计定时器 */
        ADS_StartTimer(TI_ADS_UL_DATA_STAT, ADS_UL_GET_STAT_TIMER_LEN());
    }

    /* 清空统计包的个数 */
    ADS_UL_CLR_STAT_PKT_NUM();

    return;
}

/*****************************************************************************
 函 数 名  : ADS_UL_RcvTafMsg
 功能描述  : 接收来自AT的消息
 输入参数  : MsgBlock *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年02月14日
    作    者   : m00217266
    修改内容   : pdp status ind 改为taf aps发送
*****************************************************************************/
VOS_UINT32 ADS_UL_RcvTafMsg(MsgBlock *pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;


    switch(pstMsg->ulMsgName)
    {
        case ID_APS_ADS_PDP_STATUS_IND:
            ADS_UL_RcvTafPdpStatusInd(pMsg);
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_UL_RcvCdsMsg
 功能描述  : 接收来自CDS的消息
 输入参数  : MsgBlock *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年6月16日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_UINT32 ADS_UL_RcvCdsMsg(MsgBlock *pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case ID_CDS_ADS_IP_PACKET_IND:
            ADS_UL_RcvCdsIpPacketMsg(pMsg);
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_UL_RcvTimerMsg
 功能描述  : 处理定时器超时消息
 输入参数  : MsgBlock *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

  2.日    期   : 2013年9月22日
    作    者   : A00165503
    修改内容   : DTS2013092200927: 定时器使用优化

  3.日    期   : 2014年06月03日
    作    者   : f00179208
    修改内容   : CCPU LOAD优化

  4.日    期   : 2015年5月21日
    作    者   : l00198894
    修改内容   : TSTS

  5.日    期   : 2015年9月22日
    作    者   : A00165503
    修改内容   : DTS2015081008249: ADS数传过程中持锁, 防止系统进入休眠

*****************************************************************************/
VOS_UINT32 ADS_UL_RcvTimerMsg(MsgBlock *pMsg)
{
    REL_TIMER_MSG                      *pstTimerMsg;

    pstTimerMsg = (REL_TIMER_MSG *)pMsg;

    /* 停止该定时器 */
    ADS_StopTimer(ACPU_PID_ADS_UL, pstTimerMsg->ulName, ADS_TIMER_STOP_CAUSE_TIMEOUT);

    switch (pstTimerMsg->ulName)
    {
        case TI_ADS_DSFLOW_STATS:
            ADS_UL_RcvTiDsFlowStatsExpired(pstTimerMsg->ulName, pstTimerMsg->ulPara);
            ADS_MNTN_ReportAllStatsInfo();
#if (defined(CONFIG_BALONG_SPE))
            SPE_MNTN_ReportAllStatsInfo();
#endif
            break;

        case TI_ADS_UL_DATA_STAT:
            ADS_UL_RcvTiDataStatExpired(pstTimerMsg->ulName, pstTimerMsg->ulPara);
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_UL_RcvAdsUlMsg
 功能描述  : 接收来自ADS UL的消息
 输入参数  : MsgBlock *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年04月15日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_UL_RcvAdsUlMsg(MsgBlock *pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case ID_ADS_CCPU_RESET_START_IND:
            ADS_UL_RcvCcpuResetStartInd(pMsg);
            break;

        case ID_ADS_CCPU_RESET_END_IND:
            /* do nothing */
            ADS_NORMAL_LOG(ACPU_PID_ADS_UL, "ADS_DL_RcvAdsDlMsg: rcv ID_CCPU_ADS_UL_RESET_END_IND");
            break;

        default:
            ADS_NORMAL_LOG1(ACPU_PID_ADS_UL, "ADS_UL_RcvAdsUlMsg: rcv error msg id %d\r\n", pstMsg->ulMsgName);
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_UL_ProcMsg
 功能描述  : ADS上行消息处理函数
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年4月12日
    作    者   : A00165503
    修改内容   : DTS2012020708222: ADS性能优化
  3.日    期   : 2013年4月15日
    作    者   : f00179208
    修改内容   : C核单独复位项目
  4.日    期   : 2014年02月14日
    作    者   : m00217266
    修改内容   : pdp status ind 改为taf aps发送
  5.日    期   : 2015年5月21日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_VOID ADS_UL_ProcMsg(MsgBlock* pMsg)
{
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    /* 消息的分发处理 */
    switch ( pMsg->ulSenderPid )
    {
        /* 来自Timer的消息 */
        case VOS_PID_TIMER:
            ADS_UL_RcvTimerMsg(pMsg);
            return;

        /* 来自TAF的消息 */
        case I0_WUEPS_PID_TAF:
        case I1_WUEPS_PID_TAF:
        case I2_WUEPS_PID_TAF:
            ADS_UL_RcvTafMsg(pMsg);
            return;

        /* 来自CDS的消息 */
        case UEPS_PID_CDS:
            ADS_UL_RcvCdsMsg(pMsg);
            return;

        /* 来自ADS UL的消息 */
        case ACPU_PID_ADS_UL:
            ADS_UL_RcvAdsUlMsg(pMsg);
            return;

        default:
            return;
    }
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
