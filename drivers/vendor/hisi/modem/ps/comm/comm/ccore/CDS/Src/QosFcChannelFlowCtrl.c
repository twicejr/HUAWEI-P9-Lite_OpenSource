/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : QosFcChannelFlowCtrl.c
  版 本 号   : 初稿
  作    者   : w00145177
  生成日期   : 2011年12月23日
  最近修改   :
  功能描述   : QoS流控通道流控管理
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
#include "QosFcChannelFlowCtrl.h"
#include "QosFcOm.h"
#include "FcCdsInterface.h"
#include "CdsMsgProc.h"


/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_QOS_FC_CHANNEL_FLOWCTRL_C
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
QOS_FC_CHANNEL_ENTITY_STRU g_stQosFcChannelEntity[FC_MAX_RAB_NUM];

/******************************************************************************
   5 函数实现
******************************************************************************/
/*****************************************************************************
 函 数 名  : QosFcChannelInit
 功能描述  : 通道实体初始化
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID QosFcChannelInit(VOS_VOID)
{
    VOS_UINT32 i=0;
    for(i = 0; i < FC_MAX_RAB_NUM; i++)
    {
        g_stQosFcChannelEntity[i].ucRabId = FC_INVALID_RABID;
        g_stQosFcChannelEntity[i].enQci = QCI_TYPE_BUTT;
        g_stQosFcChannelEntity[i].enChannelState = QOS_FC_CHANNEL_STATE_BUTT;
    }

    return;
}

/*****************************************************************************
 函 数 名  : QosFc_SendStopChannel2AFC
 功能描述  : 通知A核流控模块关闭通道数传
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
VOS_VOID QosFc_SendStopChannel2AFC(VOS_UINT32 ulIndex)
{
    CDS_FC_STOP_CHANNEL_IND_STRU    *pstStopChannelInd;
    QOS_FC_CHANNEL_ENTITY_STRU      *pstQosFcChannelEntity;
    MODEM_ID_ENUM_UINT16             enModemId;

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter QosFc_SendStopChannel2AFC ");
    CDS_PRINT_ERROR(QosFc_SendStopChannel2AFC_ENUM, CDS_FUNCTION_ENTER);

    if(FC_MAX_RAB_NUM <= ulIndex)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_SendStopChannel2AFC : Error Index: ",ulIndex);
        CDS_PRINT_ERROR1(QosFc_SendStopChannel2AFC_ENUM, CDS_FC_CH_INDEX_INVALID,ulIndex);
        return;
    }

    pstQosFcChannelEntity = &g_stQosFcChannelEntity[ulIndex];
    if(QosFc_IsInValidRabId(FC_MASK_RABID & pstQosFcChannelEntity->ucRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_SendStopChannel2AFC : Error RabId: ",pstQosFcChannelEntity->ucRabId);
        CDS_PRINT_ERROR1(QosFc_SendStopChannel2AFC_ENUM, CDS_RAB_ID_INVALID,pstQosFcChannelEntity->ucRabId);
        return ;
    }

    enModemId = pstQosFcChannelEntity->ucRabId >> FC_MODEMID_SHIFT;
    if(MODEM_ID_BUTT <= enModemId)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_SendStopChannel2AFC : Error ModemId:", enModemId);
        CDS_PRINT_ERROR1(QosFc_SendStopChannel2AFC_ENUM, CDS_MODEM_ID_INVALID,enModemId);
        return;
    }

    /*申请OSA消息内存*/
    pstStopChannelInd = (VOS_VOID *)PS_ALLOC_MSG_ALL_CHECK(UEPS_PID_CDS, sizeof(CDS_FC_STOP_CHANNEL_IND_STRU));
    if (VOS_NULL_PTR == pstStopChannelInd)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"QosFc_SendStopChannel2AFC : Error to Alloc Msg Mem");
        CDS_PRINT_ERROR(QosFc_SendStopChannel2AFC_ENUM, CDS_ALLOC_MSG_FAIL);
        return ;
    }

    /*填写消息内容*/
    CDS_CFG_MSG_HDR(pstStopChannelInd, ACPU_PID_FC);
    pstStopChannelInd->enMsgName = ID_CDS_FC_STOP_CHANNEL_IND;
    pstStopChannelInd->ucRabId = FC_MASK_RABID & pstQosFcChannelEntity->ucRabId;
    pstStopChannelInd->enModemId = enModemId;

    /*发送消息*/
    if (VOS_OK != PS_SND_MSG_ALL_CHECK(UEPS_PID_CDS, pstStopChannelInd))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"QosFc_SendStopChannel2AFC : Send Msg Fail");
        CDS_PRINT_ERROR(QosFc_SendStopChannel2AFC_ENUM, CDS_SEND_MSG_FAIL);
        return;
    }

    FC_DBG_CHANNEL_FC_STAT(enModemId, (FC_MASK_RABID & pstQosFcChannelEntity->ucRabId), 1);
    CDS_WARNING_LOG1(UEPS_PID_CDS,"QosFc_SendStopChannel2AFC: Send Stop Msg Succ:", pstQosFcChannelEntity->ucRabId);
    CDS_PRINT_ERROR(QosFc_SendStopChannel2AFC_ENUM, CDS_FUNCTION_LEAVE);

    return;
}

/*****************************************************************************
 函 数 名  : QosFc_SendStartChannel2AFC
 功能描述  : 通知A核流控模块开启通道数传
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
VOS_VOID QosFc_SendStartChannel2AFC(VOS_UINT32 ulIndex)
{
    CDS_FC_START_CHANNEL_IND_STRU   *pstStartChannelInd;
    QOS_FC_CHANNEL_ENTITY_STRU      *pstQosFcChannelEntity;
    MODEM_ID_ENUM_UINT16             enModemId;

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter QosFc_SendStartChannel2AFC ");
    CDS_PRINT_INFO(QosFc_SendStartChannel2AFC_ENUM, CDS_FUNCTION_ENTER);

    if(FC_MAX_RAB_NUM <= ulIndex)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_SendStartChannel2AFC : Error Index: ",ulIndex);
        CDS_PRINT_ERROR1(QosFc_SendStartChannel2AFC_ENUM, CDS_FC_CH_INDEX_INVALID,ulIndex);
        return;
    }

    pstQosFcChannelEntity = &g_stQosFcChannelEntity[ulIndex];
    if(QosFc_IsInValidRabId(FC_MASK_RABID & pstQosFcChannelEntity->ucRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_SendStartChannel2AFC : Error RabId: ",pstQosFcChannelEntity->ucRabId);
        CDS_PRINT_ERROR1(QosFc_SendStartChannel2AFC_ENUM, CDS_RAB_ID_INVALID,pstQosFcChannelEntity->ucRabId);
        return;
    }

    enModemId = pstQosFcChannelEntity->ucRabId >> FC_MODEMID_SHIFT;
    if(MODEM_ID_BUTT <= enModemId)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_SendStartChannel2AFC : Error ModemId:", enModemId);
        CDS_PRINT_ERROR1(QosFc_SendStartChannel2AFC_ENUM, CDS_MODEM_ID_INVALID,enModemId);
        return;
    }

    /*申请OSA消息内存*/
    pstStartChannelInd = (VOS_VOID *)PS_ALLOC_MSG_ALL_CHECK(UEPS_PID_CDS, sizeof(CDS_FC_START_CHANNEL_IND_STRU));
    if (VOS_NULL_PTR == pstStartChannelInd)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"QosFc_SendStartChannel2AFC : Error to Alloc Msg Mem");
        CDS_PRINT_ERROR(QosFc_SendStartChannel2AFC_ENUM, CDS_ALLOC_MSG_FAIL);
        return ;
    }

    /*填写消息内容*/
    CDS_CFG_MSG_HDR(pstStartChannelInd, ACPU_PID_FC);
    pstStartChannelInd->enMsgName = ID_CDS_FC_START_CHANNEL_IND;
    pstStartChannelInd->ucRabId = FC_MASK_RABID & pstQosFcChannelEntity->ucRabId;
    pstStartChannelInd->enModemId = enModemId;

    /*发送消息*/
    if (VOS_OK != PS_SND_MSG_ALL_CHECK(UEPS_PID_CDS, pstStartChannelInd))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"QosFc_SendStartChannel2AFC : Send Msg Fail");
        CDS_PRINT_ERROR(QosFc_SendStartChannel2AFC_ENUM, CDS_SEND_MSG_FAIL);
        return;
    }

    FC_DBG_CHANNEL_RESUME_STAT(enModemId, (FC_MASK_RABID & pstQosFcChannelEntity->ucRabId), 1);
    CDS_WARNING_LOG1(UEPS_PID_CDS,"QosFc_SendStartChannel2AFC: Send Start Msg Succ:", pstQosFcChannelEntity->ucRabId);
    CDS_PRINT_INFO1(QosFc_SendStartChannel2AFC_ENUM, CDS_FUNCTION_LEAVE,pstQosFcChannelEntity->ucRabId);

    return;
}

/*****************************************************************************
 函 数 名  : QosFc_ChannelControl
 功能描述  : 通道流控处理
 输入参数  : VOS_UINT8 ucRabId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID QosFc_ChannelControl(VOS_UINT8 ucRabId)
{
    VOS_UINT32  i;

    for(i = 0; i < FC_MAX_RAB_NUM; i++)
    {
        if(ucRabId == g_stQosFcChannelEntity[i].ucRabId)
        {
            /* 找到对应通道位置 */
            break;
        }
    }
    if(FC_MAX_RAB_NUM == i)
    {
        /* 出错保护 */
        CDS_ERROR_LOG1(UEPS_PID_CDS, "QosFc_ChannelControl : Not find the channel: ", ucRabId);
        CDS_PRINT_ERROR1(QosFc_ChannelControl_ENUM, CDS_RAB_ID_INVALID,ucRabId);
        return;
    }

    if(QOS_FC_CHANNEL_STATE_FLOWCTRL != g_stQosFcChannelEntity[i].enChannelState)
    {
        CDS_WARNING_LOG2(UEPS_PID_CDS, "QosFc_ChannelControl : RabId: Pre State:", ucRabId, g_stQosFcChannelEntity[i].enChannelState );
        CDS_PRINT_WARNING2(QosFc_ChannelControl_ENUM, CDS_FC_CH_PRE_STATE, ucRabId, g_stQosFcChannelEntity[i].enChannelState);
        /* 置通道为流控状态 */
        g_stQosFcChannelEntity[i].enChannelState = QOS_FC_CHANNEL_STATE_FLOWCTRL;

        QosFc_SendStopChannel2AFC(i);
    }

    return;
}

/*****************************************************************************
 函 数 名  : QosFc_ChannelRestore
 功能描述  : 通道恢复数传处理
 输入参数  : VOS_UINT8 ucRabId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID QosFc_ChannelRestore(VOS_UINT8 ucRabId)
{
    VOS_UINT32  i;

    for(i = 0; i < FC_MAX_RAB_NUM; i++)
    {
        if(ucRabId == g_stQosFcChannelEntity[i].ucRabId)
        {
            /* 找到对应通道位置 */
            break;
        }
    }
    if(FC_MAX_RAB_NUM == i)
    {
        /* 出错保护 */
        CDS_ERROR_LOG1(UEPS_PID_CDS, "QosFc_ChannelRestore : Not find the channel: ", ucRabId);
        CDS_PRINT_ERROR1(QosFc_ChannelRestore_ENUM, CDS_RAB_ID_INVALID,ucRabId);
        return;
    }

    if(QOS_FC_CHANNEL_STATE_NORMAL != g_stQosFcChannelEntity[i].enChannelState)
    {
        CDS_WARNING_LOG2(UEPS_PID_CDS, "QosFc_ChannelRestore : RabId: Pre State:", ucRabId, g_stQosFcChannelEntity[i].enChannelState );
        CDS_PRINT_WARNING2(QosFc_ChannelRestore_ENUM, CDS_FC_CH_PRE_STATE, ucRabId, g_stQosFcChannelEntity[i].enChannelState);
        /* 恢复通道数传 */
        g_stQosFcChannelEntity[i].enChannelState = QOS_FC_CHANNEL_STATE_NORMAL;

        QosFc_SendStartChannel2AFC(i);
    }

    return;
}

/*****************************************************************************
 函 数 名  : QosFc_UpdateChannelQos
 功能描述  : 更新通道QoS
 输入参数  : VOS_UINT8 ucRabId
             QCI_TYPE_ENUM_UINT8 enQci
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID QosFc_UpdateChannelQos(VOS_UINT8 ucRabId, QCI_TYPE_ENUM_UINT8 enQci)
{

    VOS_UINT32  i,j;

    for(i = 0; i < FC_MAX_RAB_NUM; i++)
    {
        if((ucRabId == g_stQosFcChannelEntity[i].ucRabId)
            ||(FC_INVALID_RABID == g_stQosFcChannelEntity[i].ucRabId))
        {
            /* 找到对应通道位置 */
            break;
        }
    }

    if(FC_MAX_RAB_NUM == i)
    {
        /* 出错保护 */
        CDS_ERROR_LOG(UEPS_PID_CDS, "QosFc_UpdateChannelQos : too many channel created!");
        CDS_PRINT_ERROR(QosFc_UpdateChannelQos_ENUM, CDS_RAB_ID_INVALID);
        return;
    }

    if(QCI_TYPE_BUTT != enQci)
    {
        if(FC_INVALID_RABID == g_stQosFcChannelEntity[i].ucRabId)
        {
            /* 新建通道 */
            g_stQosFcChannelEntity[i].ucRabId = ucRabId;
            g_stQosFcChannelEntity[i].enQci = enQci;
            g_stQosFcChannelEntity[i].enChannelState = QOS_FC_CHANNEL_STATE_NORMAL;
            CDS_WARNING_LOG2(UEPS_PID_CDS, "QosFc_UpdateChannelQos : Create Channel: Qci:", ucRabId, enQci);
            CDS_PRINT_WARNING2(QosFc_UpdateChannelQos_ENUM, CDS_FC_CH_CREATE_QCI, ucRabId, enQci);
        }
        else
        {
            CDS_WARNING_LOG3(UEPS_PID_CDS, "QosFc_UpdateChannelQos : Update Channel: Qci: -> :", ucRabId, g_stQosFcChannelEntity[i].enQci, enQci);
            CDS_PRINT_WARNING2(QosFc_UpdateChannelQos_ENUM, CDS_FC_CH_UPDATE_QCI, g_stQosFcChannelEntity[i].enQci, enQci);
            /* 更新QCI */
            g_stQosFcChannelEntity[i].enQci = enQci;
        }

        /* 给A核流控模块发消息更新通道QCI */
        /* 暂由AT更新通道QCI，此处不发消息 */
    }
    else
    {
        /* 给A核流控模块发消息删除通道 */
        /* 暂由AT负责，此处不发消息 */

        /* 通道删除时恢复通道状态，保护设计 */
        QosFc_ChannelRestore(ucRabId);

        CDS_WARNING_LOG2(UEPS_PID_CDS, "QosFc_UpdateChannelQos : Delete Channel: Qci:", g_stQosFcChannelEntity[i].ucRabId, g_stQosFcChannelEntity[i].enQci);
        CDS_PRINT_WARNING2(QosFc_UpdateChannelQos_ENUM, CDS_FC_CH_DELETE_QCI, g_stQosFcChannelEntity[i].ucRabId, g_stQosFcChannelEntity[i].enQci);

        /* 删除通道 */
        for(j = i; j < FC_MAX_RAB_NUM-1; j++)
        {
            if(FC_INVALID_RABID == g_stQosFcChannelEntity[j+1].ucRabId)
            {
                break;
            }
            (VOS_VOID)VOS_MemCpy(&g_stQosFcChannelEntity[j], &g_stQosFcChannelEntity[j+1], sizeof(QOS_FC_CHANNEL_ENTITY_STRU));
        }

        g_stQosFcChannelEntity[j].ucRabId = FC_INVALID_RABID;
        g_stQosFcChannelEntity[j].enQci = QCI_TYPE_BUTT;
        g_stQosFcChannelEntity[j].enChannelState = QOS_FC_CHANNEL_STATE_BUTT;

    }

    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



