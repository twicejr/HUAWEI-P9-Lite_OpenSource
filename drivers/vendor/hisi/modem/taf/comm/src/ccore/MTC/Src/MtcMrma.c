/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MtcMrma.c
  版 本 号   : 初稿
  作    者   : j00174725
  生成日期   : 2014年06月16日
  最近修改   :
  功能描述   : 多模多天线相关功能函数定义
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : 新生成
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MtcRcmInterface.h"
#include "ImsaMtcInterface.h"
#include "MtcCtx.h"
#include "MtcDebug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 修改人: j00174725; */
#define    THIS_FILE_ID        PS_FILE_ID_MTC_MRMA_C
/*lint +e767 修改人: j00174725; */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : MTC_SndRcmModemStateInd
 功能描述  : MTC模块通知RCM模块各个Modem状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性
  2.日    期   : 2015年07月20日
    作    者   : zwx247453
    修改内容   : 3 modem TAS
*****************************************************************************/
VOS_VOID MTC_SndRcmModemStateInd(VOS_VOID)
{
    MTC_RCM_MODEM_STATE_NOTIFY_STRU    *pstModemState;
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvStatus;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enPsSrvStatus;

    enPsSrvStatus                       = TAF_MTC_SRV_CONN_STATE_BUTT;

    /* 申请消息包 */
    pstModemState = (MTC_RCM_MODEM_STATE_NOTIFY_STRU *)MTC_ALLOC_MSG_WITH_HDR(sizeof(MTC_RCM_MODEM_STATE_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstModemState)
    {
        MTC_ERROR_LOG("MTC_SndRcmModemStateInd: Alloc Msg Fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstModemState) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MTC_RCM_MODEM_STATE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    MTC_CFG_RCM_MSG_HDR(&pstModemState->stMsgHeader, ID_MTC_RCM_MODEM_STATUS_NOTIFY);

    /* 填写各modem的状态信息 */
    for (enModemId = 0; enModemId < MODEM_ID_BUTT ; enModemId++)
    {
        enPsSrvStatus           = MTC_GetPsSrvState(enModemId);
        if ((PS_TRUE           == MTC_IsPsSessionInfoExit(enModemId))
         || (TAF_MTC_SRV_EXIST == enPsSrvStatus))
        {
            pstModemState->astModemState[enModemId].enPsSrvConnState        = TAF_MTC_SRV_EXIST;
        }
        else
        {
            pstModemState->astModemState[enModemId].enPsSrvConnState        = TAF_MTC_SRV_NO_EXIST;
        }
        pstModemState->astModemState[enModemId].enModemPowerState       = MTC_GetModemPowerState(enModemId);

        pstModemState->astModemState[enModemId].enModemType             = MTC_RCM_MODEM_0 + enModemId;
        enCsSrvStatus                                                   = MTC_GetCsSrvState(enModemId);

        pstModemState->astModemState[enModemId].enModemRatCfg           = MTC_ConvertToRcmRatCfg(MTC_GetUsimStateInfo(enModemId),
                                                                                                 MTC_GetRatCfgByModemId(enModemId));
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if ((MTC_RCM_MODEM_RAT_CFG_CL == pstModemState->astModemState[enModemId].enModemRatCfg)
         || (MTC_RCM_MODEM_RAT_CFG_C  == pstModemState->astModemState[enModemId].enModemRatCfg))
        {
            pstModemState->astModemState[enModemId].enUsimmCardState    = MTC_GetCsimStateInfo(enModemId);
        }
        else
#endif
        {
            pstModemState->astModemState[enModemId].enUsimmCardState    = MTC_GetUsimStateInfo(enModemId);
        }

        if ( (PS_TRUE           == MTC_IsCsSessionInfoExit(enModemId))
          || (TAF_MTC_SRV_EXIST == enCsSrvStatus) )
        {
            pstModemState->astModemState[enModemId].enCsSrvConnState        = TAF_MTC_SRV_EXIST;
        }
        else
        {
            pstModemState->astModemState[enModemId].enCsSrvConnState        = TAF_MTC_SRV_NO_EXIST;
        }
    }

    /* 填写CDMA状态信息 */
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enCsSrvConnState   = MTC_GetOutSideCsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enPsSrvConnState   = MTC_GetOutSidePsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enModemPowerState  = MTC_GetOutSideModemPowerState(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enUsimmCardState   = MTC_GetOutSideModemUsimmState(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enModemType        = MTC_RCM_MODEM_OTHER;
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enModemRatCfg      = MTC_RCM_MODEM_RAT_CFG_C;

    /* 发送消息 */
    MTC_SEND_MSG(pstModemState);

    return;
}

/*****************************************************************************
 函 数 名  : MTC_SndImsaModem1InfoInd
 功能描述  : MTC模块通知IMSA模块Modem1信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月05日
    作    者   : l00198894
    修改内容   : VOLTE Rank1方案项目
*****************************************************************************/
VOS_VOID MTC_SndImsaModem1InfoInd(VOS_VOID)
{
    MTC_IMSA_MODEM1_INFO_IND_STRU      *pstModem1Info = VOS_NULL_PTR;

    /* IMSA没有Start则不需要发消息 */
    if (MTC_MODEM_POWER_ON != MTC_GetModemImsaState(MODEM_ID_0))
    {
        return;
    }

    /* 申请消息包 */
    pstModem1Info = (MTC_IMSA_MODEM1_INFO_IND_STRU *)MTC_ALLOC_MSG_WITH_HDR(sizeof(MTC_IMSA_MODEM1_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstModem1Info)
    {
        MTC_ERROR_LOG("MTC_SndImsaModem1InfoInd: Alloc Msg Fail!");
        return;
    }

    /* 清空消息内容 */
    PS_MEM_SET(MTC_GET_MSG_ENTITY(pstModem1Info), 0x00, MTC_GET_MSG_LENGTH(pstModem1Info));

    /* 填充消息头 */
    MTC_CFG_IMSA_MSG_HDR(pstModem1Info, ID_MTC_IMSA_MODEM1_INFO_IND);

    /* 填写Modem1的信息 */
    pstModem1Info->enPowerState = MTC_GetModemPowerState(MODEM_ID_1);

    /* 发送消息 */
    MTC_SEND_MSG(pstModem1Info);

    return;
}

/*****************************************************************************
 函 数 名  : MTC_SndRcmModemImsVoiceCapInd
 功能描述  : MTC模块通知RCM IMS开关机状态和IMS语音可用状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月17日
    作    者   : w00316404
    修改内容   : NEXT Band26项目
*****************************************************************************/
VOS_VOID MTC_SndRcmModemImsVoiceCapInd(VOS_VOID)
{
    MTC_RCM_IMS_STATE_NOTIFY_STRU              *pstImsStateNotify   = VOS_NULL_PTR;

    /* 申请消息包 */
    pstImsStateNotify = (MTC_RCM_IMS_STATE_NOTIFY_STRU *)MTC_ALLOC_MSG_WITH_HDR(sizeof(MTC_RCM_IMS_STATE_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstImsStateNotify)
    {
        MTC_ERROR_LOG("MTC_SndRcmModemImsVoiceCapInd: Alloc Msg Fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstImsStateNotify) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MTC_RCM_IMS_STATE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    MTC_CFG_RCM_MSG_HDR(pstImsStateNotify, ID_MTC_RCM_IMS_STATUS_NOTIFY);

    /* 填充消息 */
    pstImsStateNotify->enIMSPowerState      = MTC_GetModemImsaState(MODEM_ID_0);
    pstImsStateNotify->enIMSVoiceCapState   = MTC_GetModemImsVoiceCap(MODEM_ID_0);

    /* 发送消息 */
    MTC_SEND_MSG(pstImsStateNotify);

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : MTC_SndRcmTcStatusNtf
 功能描述  : MTC模块通知RCM环回测试状态
 输入参数  : MTC_RCM_TC_STATUS_ENUM_UINT16       enTcStatus 环回测试状态
             MODEM_ID_ENUM_UINT16                enModemId  Modem Id
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月24日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_VOID MTC_SndRcmTcStatusNtf(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_RCM_TC_STATUS_ENUM_UINT16       enTcStatus
)
{
    MTC_RCM_TC_STATUS_NOTIFY_STRU      *pstTcStatus = VOS_NULL_PTR;

    /* 申请消息包 */
    pstTcStatus = (MTC_RCM_TC_STATUS_NOTIFY_STRU *)MTC_ALLOC_MSG_WITH_HDR(sizeof(MTC_RCM_TC_STATUS_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstTcStatus)
    {
        MTC_ERROR_LOG("MTC_SndRcmTcStatusNtf: Alloc Msg Fail!");
        return;
    }

    /* 清空消息内容 */
    PS_MEM_SET(MTC_GET_MSG_ENTITY(pstTcStatus), 0x00, MTC_GET_MSG_LENGTH(pstTcStatus));

    /* 填充消息头 */
    MTC_CFG_RCM_MSG_HDR(&pstTcStatus->stMsgHeader, ID_MTC_RCM_TC_STATUS_NOTIFY);

    /* 填充消息内容 */
    pstTcStatus->enModemId            = (MTC_RCM_MODEM_TYPE_ENUM_UINT16)enModemId;
    pstTcStatus->enRatMode            = MTC_RCM_RAT_MODE_CDMA;
    pstTcStatus->enTcStatus           = enTcStatus;

    /* 发送消息 */
    MTC_SEND_MSG(pstTcStatus);

    return;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

