/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : QosFcRabStatus.c
  版 本 号   : 初稿
  作    者   : w00145177
  生成日期   : 2011年12月23日
  最近修改   :
  功能描述   : QoS流控承载状态管理
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月23日
    作    者   : w00145177
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "CDS.h"
#include "QosFcCommon.h"
#include "QosFcRabStatus.h"
#include "QosFcOm.h"
#include "QosFcStatus.h"
#include "QosFcChannelFlowCtrl.h"


/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_QOS_FC_RAB_STATUS_C
/*lint +e767*/




/*****************************************************************************
  2 外部函数声明
*****************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/

/******************************************************************************
   4 全局变量定义
******************************************************************************/
VOS_INT32 g_iRabEntityCnt = 0;
QOS_FC_RAB_ENTITY_STRU g_stQosFcRabEntity[FC_MAX_RAB_NUM];
QOS_FC_RAB_STATE_ENUM_UINT32 g_enRabState[MODEM_ID_BUTT][FC_MAX_RAB_NUM]; /* RABID序，提升丢包处理性能 */
VOS_UINT8 g_ucQosFcQci2Priority[QCI_TYPE_BUTT] = {0xff,
                2, 4, 3, 5, 1, 6, 7, 8, 9};

/******************************************************************************
   5 函数实现
******************************************************************************/
/*****************************************************************************
 函 数 名  : QosFc_UpdateRabStatus
 功能描述  : 更新流控实体状态
 输入参数  : VOS_UINT8 ucRabId
             QOS_FC_RAB_STATE_ENUM_UINT32 enRabState
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID QosFc_UpdateRabStatus(VOS_UINT8 ucRabId, QOS_FC_RAB_STATE_ENUM_UINT32 enRabState)
{
    MODEM_ID_ENUM_UINT16    enModemId;
    VOS_UINT32              ulRabId;

    enModemId = ucRabId >> FC_MODEMID_SHIFT;
    ulRabId = FC_MASK_RABID & ucRabId;
    if(QosFc_IsInValidRabId(ulRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_UpdateRabStatus : Error RabId: ", ucRabId);
        CDS_PRINT_ERROR1(QosFc_UpdateRabStatus_ENUM,CDS_RAB_ID_INVALID,ucRabId);
        return;
    }
    if(QOS_FC_RAB_STATE_BUTT <= enRabState)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_UpdateRabStatus : Error Rab State: ", enRabState);
        CDS_PRINT_ERROR1(QosFc_UpdateRabStatus_ENUM,CDS_FC_RAB_STATE_ERROR,enRabState);
        return;
    }

    if(g_enRabState[enModemId][ulRabId - 5] != enRabState)
    {
        /* 输出承载流控状态迁移信息 */
        CDS_WARNING_LOG3(UEPS_PID_CDS,"QosFc_UpdateRabStatus : g_enRabState: ->: ", ucRabId, g_enRabState[enModemId][ulRabId - 5], enRabState);
        CDS_PRINT_ERROR1(QosFc_UpdateRabStatus_ENUM,CDS_RAB_ID_VALUE,ucRabId);
        CDS_PRINT_ERROR2(QosFc_UpdateRabStatus_ENUM,CDS_FC_RAB_STATE_UPDATE,g_enRabState[enModemId][ulRabId - 5], enRabState);

        /* 设置承载状态 */
        g_enRabState[enModemId][ulRabId - 5] = enRabState;
    }

    return;
}

/*****************************************************************************
 函 数 名  : QosFc_GetRabStatus
 功能描述  : 获取流控实体状态
 输入参数  : VOS_UINT8 ucRabId
 输出参数  : 无
 返 回 值  : QOS_FC_RAB_STATE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
QOS_FC_RAB_STATE_ENUM_UINT32 QosFc_GetRabStatus(VOS_UINT8 ucRabId)
{
    MODEM_ID_ENUM_UINT16    enModemId;

    if(QosFc_IsInValidRabId(FC_MASK_RABID & ucRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_GetRabStatus : Error RabId: ", ucRabId);
        CDS_PRINT_ERROR1(QosFc_GetRabStatus_ENUM,CDS_RAB_ID_INVALID,ucRabId);
        /* 非法承载，丢包 */
        return QOS_FC_RAB_STATE_DISCARD;
    }

    enModemId = ucRabId >> FC_MODEMID_SHIFT;

    return g_enRabState[enModemId][(FC_MASK_RABID & ucRabId) - 5];
}

/*****************************************************************************
 函 数 名  : QosFc_RabEntityInit
 功能描述  : 流控实体初始化
 输入参数  : VOS_UINT32 ulIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID QosFc_RabEntityInit(VOS_UINT32 ulIndex)
{
    if(FC_MAX_RAB_NUM <= ulIndex)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_RabEntityInit : Error Index: ", ulIndex);
        CDS_PRINT_ERROR1(QosFc_RabEntityInit_ENUM,CDS_FC_CH_INDEX_INVALID,ulIndex);
        return;
    }

    g_stQosFcRabEntity[ulIndex].ucRabId = FC_INVALID_RABID;
    g_stQosFcRabEntity[ulIndex].enQci = QCI_TYPE_BUTT;
    g_stQosFcRabEntity[ulIndex].ucPriority = 0xff;
    g_stQosFcRabEntity[ulIndex].ucLinkRabId = FC_INVALID_RABID;
    g_stQosFcRabEntity[ulIndex].enRabState = QOS_FC_RAB_STATE_BUTT;

    return;

}

/*****************************************************************************
 函 数 名  : QosFcRabInit
 功能描述  : QoS流控承载状态管理模块初始化
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月24日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID QosFcRabInit(VOS_VOID)
{
    VOS_UINT32 i,j = 0;
    for(i = 0; i < FC_MAX_RAB_NUM; i++)
    {
        QosFc_RabEntityInit(i);

        for(j = 0; j < MODEM_ID_BUTT; j++)
        {
            g_enRabState[j][i] = QOS_FC_RAB_STATE_NORMAL;
        }
    }
    g_iRabEntityCnt = 0;

    return;
}

/*****************************************************************************
 函 数 名  : QosFc_IsInValidRabId
 功能描述  : RABID合法性检查
 输入参数  : VOS_UINT8 ucRabId
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_BOOL QosFc_IsInValidRabId(VOS_UINT32 ulRabId)
{
    if ((ulRabId < FC_MIN_RABID) || (ulRabId > FC_MAX_RABID))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : QosFc_OtherAvailRabOfPdn
 功能描述  : 判断PDN上是否还有承载处于数传状态
 输入参数  : VOS_UINT8 ucRabId
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 QosFc_OtherAvailRabOfPdn(VOS_UINT8 ucRabId)
{
    VOS_UINT32  i;

    for(i = 0; i < FC_MAX_RAB_NUM; i++)
    {
        if(FC_INVALID_RABID == g_stQosFcRabEntity[i].ucRabId)
        {
            return FC_INVALID_RABID;
        }

        if((ucRabId == g_stQosFcRabEntity[i].ucLinkRabId)
            &&(QOS_FC_RAB_STATE_DISCARD != g_stQosFcRabEntity[i].enRabState))
        {
            return g_stQosFcRabEntity[i].ucRabId;
        }
    }

    return FC_INVALID_RABID;

}

/*****************************************************************************
 函 数 名  : QosFc_RabNeedFlowCtrl
 功能描述  : 判断是否是可流控承载
 输入参数  : VOS_UINT32 ulIndex
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_BOOL QosFc_RabNeedFlowCtrl(VOS_UINT32 ulIndex)
{
    if(FC_MAX_RAB_NUM <= ulIndex)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "QosFc_RabNeedFlowCtrl : Invalid ulIndex:", ulIndex);
        CDS_PRINT_ERROR1(QosFc_RabNeedFlowCtrl_ENUM,CDS_FC_CH_INDEX_INVALID,ulIndex);
        return VOS_FALSE;
    }

    /* 判断是否不流控的优先级 */
    if(FC_NOT_FLOWCTRL_PRIO < g_stQosFcRabEntity[ulIndex].ucPriority)
    {
        /* 是否是更高优先级承载 */
        if((g_stQosFcCtrl.bHighFcEnable)
            || (g_stQosFcRabEntity[0].ucPriority != g_stQosFcRabEntity[ulIndex].ucPriority))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : QosFc_SetRabDiscard
 功能描述  : 承载丢包状态设置
 输入参数  : VOS_UINT32 ulIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月26日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID QosFc_SetRabDiscard(VOS_UINT32 ulIndex)
{
    MODEM_ID_ENUM_UINT16    enModemId;

    if(FC_MAX_RAB_NUM <= ulIndex)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "QosFc_SetRabDiscard : Invalid ulIndex:", ulIndex);
        CDS_PRINT_ERROR1(QosFc_SetRabDiscard_ENUM,CDS_FC_CH_INDEX_INVALID,ulIndex);
        return;
    }

    if(QOS_FC_RAB_STATE_DISCARD == g_stQosFcRabEntity[ulIndex].enRabState)
    {
        return;
    }

    enModemId = g_stQosFcRabEntity[ulIndex].ucRabId >> FC_MODEMID_SHIFT;
    FC_DBG_TO_DISCARD_STAT(enModemId, (FC_MASK_RABID & g_stQosFcRabEntity[ulIndex].ucRabId), 1);



    CDS_WARNING_LOG3(UEPS_PID_CDS, "QosFc_SetRabDiscard : RabId: -> ",
                                        g_stQosFcRabEntity[ulIndex].ucRabId,
                                        g_stQosFcRabEntity[ulIndex].enRabState,
                                        QOS_FC_RAB_STATE_DISCARD);

    CDS_PRINT_WARNING1(QosFc_SetRabDiscard_ENUM,CDS_RAB_ID_VALUE,g_stQosFcRabEntity[ulIndex].ucRabId);
    CDS_PRINT_WARNING2(QosFc_SetRabDiscard_ENUM,CDS_FC_RAB_STATE_UPDATE,g_stQosFcRabEntity[ulIndex].enRabState,QOS_FC_RAB_STATE_DISCARD);

    g_stQosFcRabEntity[ulIndex].enRabState = QOS_FC_RAB_STATE_DISCARD;

    /* 最高优先级不丢包处理 */
    if((g_stQosFcCtrl.bHighDiscardEnable)
        || (g_stQosFcRabEntity[0].ucPriority != g_stQosFcRabEntity[ulIndex].ucPriority))
    {
        QosFc_UpdateRabStatus(g_stQosFcRabEntity[ulIndex].ucRabId, QOS_FC_RAB_STATE_DISCARD);
    }
    else
    {
        QosFc_UpdateRabStatus(g_stQosFcRabEntity[ulIndex].ucRabId, QOS_FC_RAB_STATE_NOT_DISCARD);
    }

    if(FC_INVALID_RABID == QosFc_OtherAvailRabOfPdn(g_stQosFcRabEntity[ulIndex].ucLinkRabId))
    {
        QosFc_ChannelControl(g_stQosFcRabEntity[ulIndex].ucLinkRabId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : QosFc_DiscardAllDataFlow
 功能描述  : 进入警戒门限时，一次置所有低优先级承载进入丢包流控状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 QosFc_DiscardAllDataFlow(VOS_VOID)
{
    VOS_INT32  i,j;

    if((g_iRabEntityCnt < 1)
        || (g_iRabEntityCnt > FC_MAX_RAB_NUM))
    {
        return PS_FAIL;
    }

    for(i = g_iRabEntityCnt-1; i >= 0; i--)
    {
        if(FC_INVALID_RABID == g_stQosFcRabEntity[i].ucRabId)
        {
            continue;
        }

        /* 找到优先级最低的非丢包状态承载 */
        if(QOS_FC_RAB_STATE_DISCARD != g_stQosFcRabEntity[i].enRabState)
        {
            break;
        }
    }

    if(0 <= i)
    {
        for(j = i; j >= 0; j--)
        {
            /* 判断是否需要流控 */
            if(QosFc_RabNeedFlowCtrl((VOS_UINT32)j))
            {
                /* 置丢包状态 */
                QosFc_SetRabDiscard((VOS_UINT32)j);
            }
        }
    }
    else
    {
        CDS_WARNING_LOG(UEPS_PID_CDS, "QosFc_DiscardAllDataFlow : All Entity Flow Control!");
        CDS_PRINT_WARNING(QosFc_DiscardAllDataFlow_ENUM,CDS_FC_RAB_ALL_IN_FC_STATE);
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : QosFc_DiscardDataFlow
 功能描述  : 进行丢包流控处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 QosFc_DiscardDataFlow(VOS_VOID)
{
    VOS_INT32  i,j;

    if((g_iRabEntityCnt < 1)
        || (g_iRabEntityCnt > FC_MAX_RAB_NUM))
    {
        return PS_FAIL;
    }

    for(i = g_iRabEntityCnt-1; i >= 0; i--)
    {
        if(FC_INVALID_RABID == g_stQosFcRabEntity[i].ucRabId)
        {
            continue;
        }

        /* 找到优先级最低的非丢包状态承载 */
        if(QOS_FC_RAB_STATE_DISCARD != g_stQosFcRabEntity[i].enRabState)
        {
            break;
        }
    }

    if(0 <= i)
    {
        /* 判断是否需要流控 */
        if(QosFc_RabNeedFlowCtrl((VOS_UINT32)i))
        {
            for(j = i; j >= 0; j--)
            {
                if(g_stQosFcRabEntity[i].ucPriority != g_stQosFcRabEntity[j].ucPriority)
                {
                    /* 一组承载处理完 */
                    break;
                }
                /* 置丢包状态 */
                QosFc_SetRabDiscard((VOS_UINT32)j);
            }
        }
    }
    else
    {
        CDS_WARNING_LOG(UEPS_PID_CDS, "QosFc_DiscardDataFlow : All Entity Flow Control!");
        CDS_PRINT_WARNING(QosFc_DiscardDataFlow_ENUM,CDS_FC_RAB_ALL_IN_FC_STATE);
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : QosFc_SetRabRandomDiscard
 功能描述  : 承载随机丢包状态设置
 输入参数  : VOS_UINT32 ulIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月26日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID QosFc_SetRabRandomDiscard(VOS_UINT32 ulIndex)
{
    MODEM_ID_ENUM_UINT16    enModemId;

    if(FC_MAX_RAB_NUM <= ulIndex)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "QosFc_SetRabRandomDiscard : Invalid ulIndex:", ulIndex);
        CDS_PRINT_ERROR1(QosFc_SetRabRandomDiscard_ENUM,CDS_FC_CH_INDEX_INVALID,ulIndex);
        return;
    }

    if(QOS_FC_RAB_STATE_RANDOM_DISCARD == g_stQosFcRabEntity[ulIndex].enRabState)
    {
        return;
    }

    enModemId = g_stQosFcRabEntity[ulIndex].ucRabId >> FC_MODEMID_SHIFT;
    FC_DBG_TO_RANDOMDISCARD_STAT(enModemId, (FC_MASK_RABID & g_stQosFcRabEntity[ulIndex].ucRabId), 1);

    CDS_WARNING_LOG3(UEPS_PID_CDS, "QosFc_SetRabRandomDiscard : RabId: -> ",
                                        g_stQosFcRabEntity[ulIndex].ucRabId,
                                        g_stQosFcRabEntity[ulIndex].enRabState,
                                        QOS_FC_RAB_STATE_RANDOM_DISCARD);
    CDS_PRINT_WARNING1(QosFc_SetRabRandomDiscard_ENUM,CDS_RAB_ID_VALUE,g_stQosFcRabEntity[ulIndex].ucRabId);
    CDS_PRINT_WARNING2(QosFc_SetRabRandomDiscard_ENUM,CDS_FC_RAB_STATE_UPDATE,g_stQosFcRabEntity[ulIndex].enRabState,QOS_FC_RAB_STATE_RANDOM_DISCARD);

    g_stQosFcRabEntity[ulIndex].enRabState = QOS_FC_RAB_STATE_RANDOM_DISCARD;

    QosFc_UpdateRabStatus(g_stQosFcRabEntity[ulIndex].ucRabId, QOS_FC_RAB_STATE_RANDOM_DISCARD);

    return;
}

/*****************************************************************************
 函 数 名  : QosFc_RandomDiscardDataFlow
 功能描述  : 进行随机丢包流控处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 QosFc_RandomDiscardDataFlow(VOS_VOID)
{
    VOS_INT32  i,j;

    if((g_iRabEntityCnt < 1)
        || (g_iRabEntityCnt > FC_MAX_RAB_NUM))
    {
        return PS_FAIL;
    }

    for(i = g_iRabEntityCnt-1; i >= 0; i--)
    {
        if(FC_INVALID_RABID == g_stQosFcRabEntity[i].ucRabId)
        {
            continue;
        }

        /* 找到最低优先级的可置为随机丢包状态的承载 */
        /* 只有一组优先级承载会处于随机丢包状态 */
        if(QOS_FC_RAB_STATE_DISCARD != g_stQosFcRabEntity[i].enRabState)
        {
            break;
        }
    }

    if(0 <= i)
    {
        /* 判断是否需要流控 */
        if(QosFc_RabNeedFlowCtrl((VOS_UINT32)i))
        {
            for(j = i; j >= 0; j--)
            {
                if(g_stQosFcRabEntity[i].ucPriority != g_stQosFcRabEntity[j].ucPriority)
                {
                    /* 一组承载处理完 */
                    break;
                }
                if(QOS_FC_RAB_STATE_NORMAL == g_stQosFcRabEntity[j].enRabState)
                {
                    /* 置随机丢包状态 */
                    QosFc_SetRabRandomDiscard((VOS_UINT32)j);
                }
            }
        }
    }
    else
    {
        CDS_WARNING_LOG(UEPS_PID_CDS, "QosFc_RandomDiscardDataFlow : All Entity Flow Control!");
        CDS_PRINT_WARNING(QosFc_RandomDiscardDataFlow_ENUM,CDS_FC_RAB_ALL_IN_FC_STATE);
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : QosFc_SetRabNormal
 功能描述  : 承载正常状态设置
 输入参数  : VOS_UINT32 ulIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月26日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID QosFc_SetRabNormal(VOS_UINT32 ulIndex)
{
    MODEM_ID_ENUM_UINT16    enModemId;

    if(FC_MAX_RAB_NUM <= ulIndex)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "QosFc_SetRabNormal : Invalid ulIndex:", ulIndex);
        CDS_PRINT_ERROR1(QosFc_SetRabNormal_ENUM,CDS_FC_CH_INDEX_INVALID,ulIndex);
        return;
    }

    if(QOS_FC_RAB_STATE_NORMAL == g_stQosFcRabEntity[ulIndex].enRabState)
    {
        return;
    }

    enModemId = g_stQosFcRabEntity[ulIndex].ucRabId >> FC_MODEMID_SHIFT;
    FC_DBG_TO_NORMAL_STAT(enModemId, (FC_MASK_RABID & g_stQosFcRabEntity[ulIndex].ucRabId), 1);

    CDS_WARNING_LOG3(UEPS_PID_CDS, "QosFc_SetRabNormal : RabId: -> ",
                                        g_stQosFcRabEntity[ulIndex].ucRabId,
                                        g_stQosFcRabEntity[ulIndex].enRabState,
                                        QOS_FC_RAB_STATE_NORMAL);

    CDS_PRINT_WARNING1(QosFc_SetRabNormal_ENUM,CDS_RAB_ID_VALUE,g_stQosFcRabEntity[ulIndex].ucRabId);
    CDS_PRINT_WARNING2(QosFc_SetRabNormal_ENUM,CDS_FC_RAB_STATE_UPDATE,g_stQosFcRabEntity[ulIndex].enRabState,QOS_FC_RAB_STATE_NORMAL);

    g_stQosFcRabEntity[ulIndex].enRabState = QOS_FC_RAB_STATE_NORMAL;

    QosFc_UpdateRabStatus(g_stQosFcRabEntity[ulIndex].ucRabId, QOS_FC_RAB_STATE_NORMAL);

    return;
}

/*****************************************************************************
 函 数 名  : QosFc_RestoreHighPriRab
 功能描述  : 优先级小于6的承载首先恢复正常数传
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月26日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 QosFc_RestoreHighPriRab(VOS_VOID)
{
    /* 优先级小于6的承载首先恢复正常数传 */

    VOS_UINT32  i;

    for(i = 0; i < FC_MAX_RAB_NUM; i++)
    {
        if(FC_FAST_RESTORE_PRIO < g_stQosFcRabEntity[i].ucPriority)
        {
            return PS_FAIL;
        }

        if(QOS_FC_RAB_STATE_NORMAL != g_stQosFcRabEntity[i].enRabState)
        {
            break;
        }
    }

    if((FC_MAX_RAB_NUM != i)
        && (FC_INVALID_RABID != g_stQosFcRabEntity[i].ucRabId))
    {
        QosFc_SetRabNormal(i);
        QosFc_ChannelRestore(g_stQosFcRabEntity[i].ucLinkRabId);
        return PS_SUCC;
    }

    return PS_FAIL;
}


/*****************************************************************************
 函 数 名  : QosFc_RestoreRabStatus
 功能描述  : 恢复数传状态，分两步完成恢复过程
 输入参数  : VOS_UINT32 ulIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月26日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID QosFc_RestoreRabStatus(VOS_UINT32 ulIndex)
{
    if(FC_MAX_RAB_NUM <= ulIndex)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "QosFc_RestoreRabStatus : Invalid ulIndex:", ulIndex);
        CDS_PRINT_ERROR1(QosFc_RestoreRabStatus_ENUM,CDS_FC_CH_INDEX_INVALID,ulIndex);
        return;
    }

    if(QOS_FC_RAB_STATE_DISCARD == g_stQosFcRabEntity[ulIndex].enRabState)
    {
        QosFc_SetRabRandomDiscard(ulIndex);

        QosFc_ChannelRestore(g_stQosFcRabEntity[ulIndex].ucLinkRabId);
    }
    else if(QOS_FC_RAB_STATE_RANDOM_DISCARD == g_stQosFcRabEntity[ulIndex].enRabState)
    {
        QosFc_SetRabNormal(ulIndex);
    }
    else
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS, "QosFc_RestoreRabStatus : Invalid State::", ulIndex, g_stQosFcRabEntity[ulIndex].enRabState);
        CDS_PRINT_ERROR2(QosFc_RestoreRabStatus_ENUM,CDS_FC_RAB_STATE_ERROR,ulIndex, g_stQosFcRabEntity[ulIndex].enRabState);
        /* 保护 */
        QosFc_SetRabNormal(ulIndex);
    }

    return;

}

/*****************************************************************************
 函 数 名  : QosFc_RestoreDataFlow
 功能描述  : 进行流控实体恢复数传处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 QosFc_RestoreDataFlow(VOS_VOID)
{
    VOS_UINT32  i,j;

    for(i = 0; i < FC_MAX_RAB_NUM; i++)
    {
        if(QOS_FC_RAB_STATE_NORMAL != g_stQosFcRabEntity[i].enRabState)
        {
            break;
        }
    }

    if((FC_MAX_RAB_NUM != i)
        && (FC_INVALID_RABID != g_stQosFcRabEntity[i].ucRabId))
    {
        if(QOS_FC_RAB_STATE_RANDOM_DISCARD == g_stQosFcRabEntity[i].enRabState)
        {
            /* 优先恢复同优先级丢包承载 */
            for(j = i; j < FC_MAX_RAB_NUM; j++)
            {
                if(g_stQosFcRabEntity[i].ucPriority != g_stQosFcRabEntity[j].ucPriority)
                {
                    break;
                }
                if(QOS_FC_RAB_STATE_DISCARD == g_stQosFcRabEntity[j].enRabState)
                {
                    /* 找到丢包承载优先恢复 */
                    i = j;
                    break;
                }
            }
        }

        QosFc_RestoreRabStatus(i);
        return PS_SUCC;
    }

    return PS_FAIL;
}

/*****************************************************************************
 函 数 名  : QosFc_SetRabEntity
 功能描述  : 根据承载更新消息设置流控实体
 输入参数  : QOS_FC_RAB_ENTITY_STRU *pstQosFcRabEntity
             CONST QOS_FC_RAB_CREATE_IND_STRU *pstRabCreate
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID QosFc_SetRabEntity(QOS_FC_RAB_ENTITY_STRU *pstQosFcRabEntity, CONST QOS_FC_RAB_CREATE_IND_STRU *pstRabCreate)
{
    if((VOS_NULL_PTR == pstRabCreate) || (VOS_NULL_PTR == pstQosFcRabEntity))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"QosFc_SetRabEntity : Invalid parameter!");
        CDS_PRINT_ERROR(QosFc_SetRabEntity_ENUM,CDS_INPUT_NULL_PARA);
        return;
    }
    pstQosFcRabEntity->ucRabId = pstRabCreate->ucRabId;
    pstQosFcRabEntity->enQci = pstRabCreate->enQci;
    pstQosFcRabEntity->ucPriority = g_ucQosFcQci2Priority[pstRabCreate->enQci];
    pstQosFcRabEntity->ucLinkRabId = pstRabCreate->ucLinkRabId;
    pstQosFcRabEntity->enRabState = QOS_FC_RAB_STATE_NORMAL;

    QosFc_UpdateRabStatus(pstRabCreate->ucRabId, QOS_FC_RAB_STATE_NORMAL);

    return;

}

/*****************************************************************************
 函 数 名  : QosFc_MoveUpEntityPos
 功能描述  : 实体排序
 输入参数  : VOS_UINT32 ulInitPos
             VOS_UINT8 ucPriority
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月6日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 QosFc_MoveUpEntityPos(VOS_UINT32 ulInitPos, VOS_UINT8 ucPriority)
{
    VOS_UINT32  j;

    for(j = ulInitPos; j > 0 ; j--)
    {
        if(ucPriority < g_stQosFcRabEntity[j-1].ucPriority)
        {
            (VOS_VOID)VOS_MemCpy(&g_stQosFcRabEntity[j], &g_stQosFcRabEntity[j-1], sizeof(QOS_FC_RAB_ENTITY_STRU));
        }
        else
        {
            /* 找到插入位置 j */
            break;
        }
    }

    return j;
}

/*****************************************************************************
 函 数 名  : QosFc_MoveDownEntityPos
 功能描述  : 实体排序
 输入参数  : VOS_UINT32 ulInitPos
             VOS_UINT8 ucPriority
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月6日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 QosFc_MoveDownEntityPos(VOS_UINT32 ulInitPos, VOS_UINT8 ucPriority)
{
    VOS_UINT32  j;

    for(j = ulInitPos; j < (FC_MAX_RAB_NUM - 1) ; j++)
    {
        if(ucPriority > g_stQosFcRabEntity[j+1].ucPriority)
        {
            (VOS_VOID)VOS_MemCpy(&g_stQosFcRabEntity[j], &g_stQosFcRabEntity[j+1], sizeof(QOS_FC_RAB_ENTITY_STRU));
        }
        else
        {
            if(FC_INVALID_RABID == g_stQosFcRabEntity[j].ucRabId)
            {
                CDS_ERROR_LOG1(UEPS_PID_CDS, "QosFc_MoveDownEntityPos : Error Prio:", g_stQosFcRabEntity[j].ucPriority);
                CDS_PRINT_ERROR1(QosFc_MoveDownEntityPos_ENUM, CDS_RAB_ID_INVALID, g_stQosFcRabEntity[j].ucPriority);
            }
            /* 找到插入位置 j */
            break;
        }
    }

    return j;
}

/*****************************************************************************
 函 数 名  : QosFc_CreateRabEntity
 功能描述  : 创建或更新流控实体
 输入参数  : QOS_FC_RAB_CREATE_IND_STRU *pstRabCreate
 输出参数  : 无
 返 回 值  : QOS_FC_RAB_ENTITY_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月24日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
QOS_FC_RAB_ENTITY_STRU* QosFc_CreateRabEntity(CONST QOS_FC_RAB_CREATE_IND_STRU *pstRabCreate, VOS_UINT8 *pucOldLinkRabId)
{
    VOS_UINT8   ucPriority;             /* 承载优先级 */
    VOS_UINT32  i;
    VOS_UINT32  idx = FC_MAX_RAB_NUM;

    if((VOS_NULL_PTR == pstRabCreate) || (VOS_NULL_PTR == pucOldLinkRabId))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"QosFc_CreateRabEntity : Invalid parameter!");
        CDS_PRINT_ERROR(QosFc_CreateRabEntity_ENUM,CDS_INPUT_NULL_PARA);
        return VOS_NULL_PTR;
    }

    for(i = 0; i < FC_MAX_RAB_NUM; i++)
    {
        if((pstRabCreate->ucRabId == g_stQosFcRabEntity[i].ucRabId)
            || (FC_INVALID_RABID == g_stQosFcRabEntity[i].ucRabId))
        {
            break;
        }
    }

    if( FC_MAX_RAB_NUM == i )
    {
        /* 出现异常，超出可支持数量 */
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_CreateRabEntity : too many Rab Entity, fail to create Entity: ",pstRabCreate->ucRabId);
        CDS_PRINT_ERROR1(QosFc_CreateRabEntity_ENUM,CDS_FC_CH_INDEX_INVALID,pstRabCreate->ucRabId);
        return VOS_NULL_PTR;
    }

    ucPriority = g_ucQosFcQci2Priority[pstRabCreate->enQci];

    /* 新建承载 */
    if(FC_INVALID_RABID == g_stQosFcRabEntity[i].ucRabId)
    {
        /* 逆序排列，高 -> 低 */
        idx = QosFc_MoveUpEntityPos(i, ucPriority);

        /* 增加实体计数 */
        g_iRabEntityCnt++;
        if((g_iRabEntityCnt < 0)
            || (g_iRabEntityCnt > FC_MAX_RAB_NUM))
        {
            CDS_ERROR_LOG1(UEPS_PID_CDS, "QosFc_CreateRabEntity : Error g_iRabEntityCnt:", g_iRabEntityCnt);
            CDS_PRINT_ERROR1(QosFc_CreateRabEntity_ENUM,CDS_FC_RAB_ENTITY_CNT_ERR,g_iRabEntityCnt);
            g_iRabEntityCnt = FC_MAX_RAB_NUM;
        }

        CDS_WARNING_LOG4(UEPS_PID_CDS, "QosFc_CreateRabEntity : Create Entity RabId: LinkRabId: Qci: Prio:",
                        pstRabCreate->ucRabId, pstRabCreate->ucLinkRabId, pstRabCreate->enQci, ucPriority);
        CDS_PRINT_ERROR2(QosFc_CreateRabEntity_ENUM,CDS_RAB_ID_VALUE,pstRabCreate->ucRabId, pstRabCreate->ucLinkRabId);
        CDS_PRINT_ERROR2(QosFc_CreateRabEntity_ENUM,CDS_FC_RAB_ENTITY_CREATE,pstRabCreate->enQci, ucPriority);

        FC_DBG_CREATE_RAB_STAT(1);
    }
    else
    {
        FC_DBG_UPDATE_RAB_STAT(1);
        *pucOldLinkRabId = g_stQosFcRabEntity[i].ucLinkRabId;

        CDS_WARNING_LOG3(UEPS_PID_CDS, "QosFc_CreateRabEntity : Update Entity  FROM  RabId: LinkRabId: Qci: ",
                        g_stQosFcRabEntity[i].ucRabId, g_stQosFcRabEntity[i].ucLinkRabId, g_stQosFcRabEntity[i].enQci);
        CDS_WARNING_LOG4(UEPS_PID_CDS, "QosFc_CreateRabEntity : Update Entity  TO  RabId: LinkRabId: Qci: Prio:",
                        pstRabCreate->ucRabId, pstRabCreate->ucLinkRabId, pstRabCreate->enQci, ucPriority);

        CDS_PRINT_ERROR2(QosFc_CreateRabEntity_ENUM,CDS_FC_RAB_ENTITY_UPDATE,g_stQosFcRabEntity[i].ucRabId, pstRabCreate->ucRabId);

        /* 更新承载 */
        /*if(pstRabCreate->ucRabId == g_stQosFcRabEntity[i].ucRabId)
 */
        {
            if(ucPriority == g_stQosFcRabEntity[i].ucPriority)
            {
                /* 优先级保持不变，实体排序不变 */
                idx = i;;
            }
            else if(ucPriority > g_stQosFcRabEntity[i].ucPriority)
            {
                idx = QosFc_MoveDownEntityPos(i, ucPriority);
            }
            else
            {
                idx = QosFc_MoveUpEntityPos(i, ucPriority);
            }
        }
    }

    if(FC_MAX_RAB_NUM <= idx)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "QosFc_CreateRabEntity : Error Insert Position: ", idx);
        CDS_PRINT_ERROR1(QosFc_CreateRabEntity_ENUM,CDS_FC_RAB_ENTITY_CNT_ERR,idx);
        return VOS_NULL_PTR;
    }

    /* 承载恢复正常数传态 */
    QosFc_SetRabEntity(&g_stQosFcRabEntity[idx], pstRabCreate);

    return &g_stQosFcRabEntity[idx];
}

/*****************************************************************************
 函 数 名  : QosFc_GetPdnQci
 功能描述  : 获取PDN上所有承载的最小QCI
 输入参数  : VOS_UINT8 ucRabId
 输出参数  : 无
 返 回 值  : QCI_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
QCI_TYPE_ENUM_UINT8 QosFc_GetPdnQci(VOS_UINT8 ucRabId)
{
    QCI_TYPE_ENUM_UINT8     enQci = QCI_TYPE_BUTT;
    VOS_UINT32  i;

    for(i = 0; i < FC_MAX_RAB_NUM; i++)
    {
        if(FC_INVALID_RABID == g_stQosFcRabEntity[i].ucRabId)
        {
            break;
        }

        if((ucRabId == g_stQosFcRabEntity[i].ucLinkRabId)
            && (enQci > g_stQosFcRabEntity[i].enQci))
        {
            enQci = g_stQosFcRabEntity[i].enQci;
        }
    }

    return enQci;
}

/*****************************************************************************
 函 数 名  : QosFc_RabCreate
 功能描述  : 承载更新消息处理
 输入参数  : MsgBlock  *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID QosFc_RabCreate(CONST MsgBlock  *pstMsg)
{
    QOS_FC_RAB_CREATE_IND_STRU *pstRabCreate = (QOS_FC_RAB_CREATE_IND_STRU *)(VOS_VOID*)pstMsg;
    QOS_FC_RAB_ENTITY_STRU *pstQosFcRabEntity = VOS_NULL_PTR;
    QCI_TYPE_ENUM_UINT8     enQci;
    VOS_UINT8               ucOldLinkRabId = FC_INVALID_RABID;
    MODEM_ID_ENUM_UINT16    enModemId;

    FC_DBG_CREATE_MSG_STAT(1);

    /*入参判断*/
    if (VOS_NULL_PTR == pstRabCreate)
    {
        CDS_PRINT_ERROR(QosFc_RabCreate_ENUM,CDS_INPUT_NULL_PARA);
        return;
    }

    /*lint -e960*/
    if(QosFc_IsInValidRabId(pstRabCreate->ucRabId)
        || QosFc_IsInValidRabId(pstRabCreate->ucLinkRabId)
        || (pstRabCreate->enQci < QCI_TYPE_QCI1_GBR)
        || (pstRabCreate->enQci > QCI_TYPE_QCI9_NONGBR))
    {
        CDS_ERROR_LOG3(UEPS_PID_CDS, "QosFc_RabCreate : Invalid MSG RabId: LinkRabId: Qci:",
                                pstRabCreate->ucRabId, pstRabCreate->ucLinkRabId, pstRabCreate->enQci);
        CDS_PRINT_ERROR2(QosFc_RabCreate_ENUM,CDS_INPUT_PARA_ERROR,pstRabCreate->ucRabId,pstRabCreate->enQci);
        return;
    }
    /*lint +e960*/

    /* 流控都按拼接处理 */
    /*lint -e960*/
    enModemId = VOS_GetModemIDFromPid(TTF_GET_MSG_SENDER_PID(pstRabCreate));
    if (MODEM_ID_BUTT <= enModemId)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "QosFc_RabCreate : ModemId Error",enModemId);
        return;
    }
    /*lint +e960*/

    /*lint -e734*/
    /*lint -e960*/
    pstRabCreate->ucRabId |= (enModemId << FC_MODEMID_SHIFT);
    pstRabCreate->ucLinkRabId |= (enModemId << FC_MODEMID_SHIFT);
    /*lint +e734*/
    /*lint +e960*/

    pstQosFcRabEntity = QosFc_CreateRabEntity(pstRabCreate, &ucOldLinkRabId);

    /*lint -e960*/
    if(VOS_NULL_PTR != pstQosFcRabEntity)
    {
        /* 获得PDN上最高的QCI */
        enQci = QosFc_GetPdnQci(pstRabCreate->ucLinkRabId);
        QosFc_UpdateChannelQos(pstRabCreate->ucLinkRabId, enQci);
        /* 新建承载处于非流控状态，打开数传通道 */
        QosFc_ChannelRestore(pstRabCreate->ucLinkRabId);

        if((FC_INVALID_RABID != ucOldLinkRabId)
                && (ucOldLinkRabId != pstRabCreate->ucLinkRabId))
        {
            /* 获得PDN上最高的QCI */
            enQci = QosFc_GetPdnQci(ucOldLinkRabId);
            QosFc_UpdateChannelQos(ucOldLinkRabId, enQci);
            /* PDN是否需要流控 */
            /*lint -e960*/
            if((QCI_TYPE_BUTT != enQci) && (FC_INVALID_RABID == QosFc_OtherAvailRabOfPdn(ucOldLinkRabId)))
            /*lint +e960*/
            {
                QosFc_ChannelControl(ucOldLinkRabId);
            }
        }
    }
    /*lint +e960*/

    return;

}

/*****************************************************************************
 函 数 名  : QosFc_ReleaseRabEntity
 功能描述  : 流控实体释放处理
 输入参数  : VOS_UINT8 ucRabId
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 QosFc_ReleaseRabEntity(VOS_UINT8 ucRabId)
{
    VOS_UINT32  i,j;
    VOS_UINT8 ucLinkRabId;

    for(i = 0; i < FC_MAX_RAB_NUM; i++)
    {
        if((ucRabId == g_stQosFcRabEntity[i].ucRabId)
            || (FC_INVALID_RABID == g_stQosFcRabEntity[i].ucRabId))
        {
            break;
        }
    }

    /* 更新承载至默认状态 */
    QosFc_UpdateRabStatus(ucRabId, QOS_FC_RAB_STATE_NORMAL);

    if(( FC_MAX_RAB_NUM == i )
        || (FC_INVALID_RABID == g_stQosFcRabEntity[i].ucRabId))
    {
        /* 未找到待释放承载 */
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_ReleaseRabEntity : Not find releasing RAB: ", ucRabId);
        CDS_PRINT_ERROR1(QosFc_ReleaseRabEntity_ENUM,CDS_RAB_ID_INVALID,ucRabId);
        return FC_INVALID_RABID;
    }

    ucLinkRabId = g_stQosFcRabEntity[i].ucLinkRabId;

    /* 紧凑排列，释放时要消除空隙 */
    for(j = i; j < (FC_MAX_RAB_NUM - 1); j++)
    {
        if(FC_INVALID_RABID == g_stQosFcRabEntity[j+1].ucRabId)
        {
            break;
        }
        (VOS_VOID)VOS_MemCpy(&g_stQosFcRabEntity[j], &g_stQosFcRabEntity[j+1], sizeof(QOS_FC_RAB_ENTITY_STRU));
    }

    QosFc_RabEntityInit(j);

    /* 减少实体计数 */
    g_iRabEntityCnt--;
    if((g_iRabEntityCnt < 0)
        || (g_iRabEntityCnt > FC_MAX_RAB_NUM))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "QosFc_ReleaseRabEntity : Error g_iRabEntityCnt:", g_iRabEntityCnt);
        CDS_PRINT_ERROR1(QosFc_ReleaseRabEntity_ENUM,CDS_FC_RAB_ENTITY_CNT_ERR,g_iRabEntityCnt);
        g_iRabEntityCnt = FC_MAX_RAB_NUM;
    }

    FC_DBG_RELEASE_RAB_STAT(1);

    return ucLinkRabId;
}

/*****************************************************************************
 函 数 名  : QosFc_RabRelease
 功能描述  : 承载释放消息处理
 输入参数  : MsgBlock  *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID QosFc_RabRelease(CONST MsgBlock  *pstMsg)
{
    QOS_FC_RAB_RELEASE_IND_STRU *pstRabRelease = (QOS_FC_RAB_RELEASE_IND_STRU *)(VOS_VOID*)pstMsg;
    QCI_TYPE_ENUM_UINT8     enQci;
    VOS_UINT8               ucLinkRabId;
    MODEM_ID_ENUM_UINT16    enModemId;
    VOS_UINT8               ucExRabId;

    FC_DBG_RELEASE_MSG_STAT(1);

    /*入参判断*/
    if (VOS_NULL_PTR == pstRabRelease)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS, "QosFc_RabRelease : NULL pointer");
        CDS_PRINT_ERROR(QosFc_RabRelease_ENUM,CDS_INPUT_NULL_PARA);
        return;
    }

    if(QosFc_IsInValidRabId(pstRabRelease->ucRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "QosFc_RabRelease : Invalid RabId:", pstRabRelease->ucRabId);
        CDS_PRINT_ERROR1(QosFc_RabRelease_ENUM,CDS_RAB_ID_INVALID,pstRabRelease->ucRabId);
        return;
    }

    enModemId = VOS_GetModemIDFromPid(TTF_GET_MSG_SENDER_PID(pstRabRelease));
    if (MODEM_ID_BUTT <= enModemId)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "QosFc_RabRelease : ModemId Error",enModemId);
        CDS_PRINT_ERROR1(QosFc_RabRelease_ENUM,CDS_MODEM_ID_INVALID,enModemId);
        return;
    }

    ucExRabId = (VOS_UINT8)((enModemId << FC_MODEMID_SHIFT) | pstRabRelease->ucRabId);
    ucLinkRabId = QosFc_ReleaseRabEntity(ucExRabId);

    if(FC_INVALID_RABID != ucLinkRabId)
    {
        /* 获得PDN上最高的QCI */
        enQci = QosFc_GetPdnQci(ucLinkRabId);
        QosFc_UpdateChannelQos(ucLinkRabId, enQci);
        /* PDN是否需要流控 */
        /*lint -e960*/
        if((QCI_TYPE_BUTT != enQci) && (FC_INVALID_RABID == QosFc_OtherAvailRabOfPdn(ucLinkRabId)))
        /*lint +e960*/
        {
            QosFc_ChannelControl(ucLinkRabId);
        }
    }
    else
    {
        CDS_ERROR_LOG(UEPS_PID_CDS, "QosFc_RabRelease : Invalid LinkRabId:");
        CDS_PRINT_ERROR1(QosFc_RabRelease_ENUM,CDS_FC_RAB_ENTITY_LINK_RAB_ERR,ucLinkRabId);
    }

    return;

}

/*****************************************************************************
 函 数 名  : QosFc_IsDiscard
 功能描述  : QoS流控丢包判断，每个包调用一次
 输入参数  : VOS_UINT8 ucRabId
             MODEM_ID_ENUM_UINT16 enModemId
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月24日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_BOOL QosFc_IsDiscard(VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId)
{
    static VOS_UINT32  ulPktCntVal = 0;         /* 包计数 */
    VOS_UINT32 ulRandValue = 0;

    if(VOS_TRUE != g_stQosFcCtrl.bQosFcEnable)
    {
        /* 流控没打开，不进流控状态 */
        return VOS_FALSE;
    }
    /*lint -e960*/
    ulPktCntVal++;
    if(ulPktCntVal >= g_stQosFcCtrl.ulPktCntLimit)
    {
        ulPktCntVal = 0;
        QosFc_FlowCtrl();
    }

    if(QosFc_IsInValidRabId(ucRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_IsDiscard : Error RabId: ", ucRabId);
        CDS_PRINT_ERROR1(QosFc_IsDiscard_ENUM,CDS_RAB_ID_INVALID,ucRabId);
        /* 非法承载，丢包 */
        return VOS_TRUE;
    }
    /*lint +e960*/

    /*lint -e960*/
    switch( g_enRabState[enModemId][ucRabId - 5] )
    {
        case QOS_FC_RAB_STATE_NORMAL:
        case QOS_FC_RAB_STATE_NOT_DISCARD:
            /* 正常数传状态，不丢包 */
            return VOS_FALSE;

        case QOS_FC_RAB_STATE_RANDOM_DISCARD:
            FC_DBG_RCV_PKT_ONRD_STAT(enModemId, ucRabId, 1);
            /* 随机丢包 */
            ulRandValue = PS_RAND(101);
            if(ulRandValue > g_stQosFcCtrl.ulRandomDiscardRate)
            {
                return VOS_FALSE;
            }
            FC_DBG_DISCARD_PKT_ONRD_STAT(enModemId, ucRabId, 1);
            return VOS_TRUE;
        case QOS_FC_RAB_STATE_DISCARD:
            FC_DBG_RCV_PKT_OND_STAT(enModemId, ucRabId, 1);
            /* 丢包 */
            ulRandValue = PS_RAND(101);
            if(ulRandValue > g_stQosFcCtrl.ulDiscardRate)
            {
                return VOS_FALSE;
            }
            FC_DBG_DISCARD_PKT_OND_STAT(enModemId, ucRabId, 1);
            return VOS_TRUE;
        default:
             /* 非法状态 */
             CDS_ERROR_LOG3(UEPS_PID_CDS, "QosFc_IsDiscard : Rab invalid state::",enModemId, ucRabId, g_enRabState[enModemId][ucRabId - 5]);
             CDS_PRINT_ERROR2(QosFc_IsDiscard_ENUM,CDS_FC_RAB_STATE_ERROR,ucRabId,g_enRabState[enModemId][ucRabId - 5]);
             break;

    }
    /*lint +e960*/

    /* 尽量不丢包 */
    return VOS_FALSE;
}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



