/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallProcMma.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年09月11日
  最近修改   :
  功能描述   : 处理来自MMA模块的消息
  函数列表   :

  修改历史   :
  1.日    期   : 2014年09月11日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "TafXCallProcMma.h"
#include "TafXCallCtx.h"
#include "TafXCallSndApp.h"
#include "TafXCallSndMma.h"
#include "TafXCallProcUsim.h"
#include "TafXCallSndXcc.h"
#include "TafSdcCtx.h"
#include "TafMmaSndOm.h"

#include "TafXCallProcEccSrv.h"
#include "TafSdcLib.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_TAF_X_CALL_PROC_MMA_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
   2 变量定义
*****************************************************************************/


/*****************************************************************************
   3 函数实现
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : TAF_XCALL_ResetAllCalls
 功能描述  : 重置所有呼叫
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月17日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : CDMA 1x项目迭代5修改

*****************************************************************************/
VOS_VOID TAF_XCALL_ResetAllCalls(VOS_VOID)
{
    VOS_UINT32                                              ulNumOfCalls;
    VOS_UINT8                                               aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    VOS_UINT32                                              ulModuleId;
    VOS_UINT8                                               i;
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt;
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                       enSubseqOp;
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                                              usClientId;
    MN_CALL_TYPE_ENUM_U8                                    enCallType;

    enEvt        = TAF_XCALL_SS_PROG_EVT_BUTT;
    enSubseqOp   = TAF_XCALL_SS_SUBSEQ_OP_BUTT;

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetNotIdleStateCalls(&ulNumOfCalls, aucCallIds);

    if (0 == ulNumOfCalls)
    {
        return;
    }

    /* 保存当前call id的module id，用于release all上报 */
    ulModuleId = TAF_XCALL_GetClientInfo(aucCallIds[0])->ulModuleId;

    /* 软关机时需要判断当前是否有非IDLE态的呼叫，如果有需要上报MN_CALL_EVT_RELEASED事件 */
    for (i = 0; i < TAF_XCALL_MIN(ulNumOfCalls, TAF_XCALL_CALL_ENTITY_MAX_NUM); i++)
    {
        /* 记录主动挂断的原因值 */
        TAF_XCALL_UpdateCcCause(aucCallIds[i], TAF_CS_CAUSE_XCALL_POWER_DOWN_IND);

        /* 给MMA发送TAF_MMA_1X_CALL_END_NTF消息 */
        pstCallEntity       = TAF_XCALL_GetCallEntityAddr(aucCallIds[i]);
        usClientId          = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
        enCallType          = TAF_XCALL_GetCallType(aucCallIds[i]);

        if (MN_CALL_DIR_MO == TAF_XCALL_GetCallDir(aucCallIds[i]))
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));
        }

        /* 进行保护停止相关重拨定时器 */
        TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, aucCallIds[i]);
        TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, aucCallIds[i]);

        /* 给APP上报MN_CALL_EVT_RELEASED事件 */
        TAF_XCALL_SndCallReleaseInd(aucCallIds[i]);


        TAF_XCALL_GetSsKeyEvent(aucCallIds[i], &enEvt, &enSubseqOp);

        /* 如果正在挂断过程中，网络挂断，给APP回复挂断成功 */
        if (TAF_XCALL_SS_PROG_EVT_REL == enEvt)
        {
            /* 给APP回复MN_CALL_EVT_SS_CMD_RSLT事件 */
            TAF_XCALL_SndSupsResult(TAF_XCALL_GetClientInfo(aucCallIds[i])->ulModuleId,
                                    TAF_XCALL_GetClientInfo(aucCallIds[i])->usClientId,
                                    TAF_XCALL_GetClientInfo(aucCallIds[i])->ucOpId,
                                    aucCallIds[i], MN_CALL_SS_RES_SUCCESS);

            TAF_XCALL_DeRegSsKeyEvent(aucCallIds[i], TAF_XCALL_SS_PROG_EVT_REL);
        }

        /* 如果正在接听过程中，网络挂断，给APP回复接听失败 */
        if (TAF_XCALL_SS_PROG_EVT_ANS == enEvt)
        {
            /* 给APP回复MN_CALL_EVT_SS_CMD_RSLT事件 */
            TAF_XCALL_SndSupsResult(TAF_XCALL_GetClientInfo(aucCallIds[i])->ulModuleId,
                                    TAF_XCALL_GetClientInfo(aucCallIds[i])->usClientId,
                                    TAF_XCALL_GetClientInfo(aucCallIds[i])->ucOpId,
                                    aucCallIds[i], MN_CALL_SS_RES_FAIL);

            TAF_XCALL_DeRegSsKeyEvent(aucCallIds[i], TAF_XCALL_SS_PROG_EVT_ANS);
        }
    }

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    TAF_XCALL_ProcEccEvent(TAF_XCALL_XCC_MSG_EVENT_INT_CALL_REL_IND,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           VOS_NULL_PTR,
                           VOS_NULL_PTR);
#endif

    /* 给APP上报MN_CALL_EVT_ALL_RELEASED事件 */
    TAF_XCALL_SndCallAllReleaseInd(ulModuleId);

}

/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvMmaPowerOffInd
 功能描述  : 处理来自MMA的关机指示消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月11日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvMmaPowerOffInd(VOS_VOID *pMsg)
{
    /* 重置所有呼叫 */
    TAF_XCALL_ResetAllCalls();

    /* 上下文初始化 */
    TAF_XCALL_InitCtx();

}



/*****************************************************************************
 函 数 名  : TAF_XCALL_IsNeedRedialImmediately
 功能描述  : 判断是否需要及时重拨
 输入参数  : TAF_CS_CAUSE_ENUM_UINT32            enCause
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月19日
    作    者   : c00299063
    修改内容   : 新生成函数
  2.日    期   : 2015年11月24日
    作    者   : w00242748
    修改内容   : DTS2015032800395:根据RSSI原因值重播
*****************************************************************************/
VOS_UINT8 TAF_XCALL_IsNeedRedialImmediately(
    TAF_CS_CAUSE_ENUM_UINT32            enCause,
    VOS_INT32                           lRssi
)
{
    switch(enCause)
    {
        case TAF_CS_CAUSE_XCALL_REORDER:
        case TAF_CS_CAUSE_XCALL_SIGNAL_FADE_IN_ACH:
        case TAF_CS_CAUSE_XCALL_SIGNAL_FADE_IN_TCH:
        case TAF_CS_CAUSE_XCALL_CHANNEL_ASSIGN_TIMEOUT:
            /* reorder order/signal fade原因值时，如果RSSI大于-100，需等定时器超时后，
               再进行重播；如果RSSI小于等于-100的话，需立即重播 */
            if (lRssi > -100)
            {
                return VOS_FALSE;
            }

        case TAF_CS_CAUSE_XCALL_NDSS:
        case TAF_CS_CAUSE_XCALL_REDIRECTION:
        case TAF_CS_CAUSE_XCALL_ABORT:
        case TAF_CS_CAUSE_XCALL_NO_SERVICE:
        case TAF_CS_CAUSE_XCALL_MAX_ACCESS_PROBES:
        case TAF_CS_CAUSE_XCALL_ACCESS_DENYIED:
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }
}
/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvMmaServiceStatusInd
 功能描述  : 处理来自mma的ServiceStatusInd消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月23日
    作    者   : c00299063
    修改内容   : 新生成函数

  2.日    期   : 2015年7月28日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
  3.日    期   : 2015年11月24日
    作    者   : w00242748
    修改内容   : DTS2015012804417:根据RSSI值进行重播

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvMmaServiceStatusInd(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCallFound;
    TAF_XCALL_CALL_ENTITY_STRU         *pstXcallEntity   = VOS_NULL_PTR;
    VOS_UINT8                           ucRedialFlg;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enServiceStatus;

    MMA_TAF_1X_SERVICE_STATUS_IND_STRU *pstMmaServiceStatusInd;

    pstMmaServiceStatusInd = (MMA_TAF_1X_SERVICE_STATUS_IND_STRU*)pMsg;

    if (VOS_TRUE != pstMmaServiceStatusInd->ulExist1XService)
    {
        return;
    }


    ucCallFound     = VOS_FALSE;
    enServiceStatus = TAF_SDC_GetCsServiceStatus();

    for (ucCallId = 1; ucCallId <= TAF_XCALL_CALL_ENTITY_MAX_NUM; ucCallId++)
    {
        pstXcallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

        /* 如果是紧急呼，认为需要立即尝试发起呼叫 */
        if ((VOS_TRUE == pstXcallEntity->ulUsed)
         && (MN_CALL_TYPE_EMERGENCY == pstXcallEntity->enCallType))
        {
            ucCallFound = VOS_TRUE;
            break;
        }

        /*获取是否需要立即重拨的标记 */
        ucRedialFlg    = TAF_XCALL_IsNeedRedialImmediately(pstXcallEntity->enCause, pstXcallEntity->sRssi);

        /*是否存在重拨呼叫 */
        if ((VOS_TRUE == pstXcallEntity->ulUsed)
         && (VOS_TRUE == ucRedialFlg))
        {
            ucCallFound = VOS_TRUE;
            break;
        }
    }

    if (VOS_FALSE == ucCallFound)
    {
        return;
    }

    /*判断呼叫状态 */
    if (MN_CALL_TYPE_EMERGENCY == pstXcallEntity->enCallType)
    {
        /*判断服务状态*/
        if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE  == enServiceStatus)
         || (TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE == enServiceStatus))
         {
            /*判断呼叫重拨定时器是否已经超时 */
            if (TAF_XCALL_TIMER_STATUS_RUNING == TAF_XCALL_GetTimerStatus(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, ucCallId))
            {
                /*关闭重拨定时器，发起重拨 */
                TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, ucCallId);

                TAF_XCALL_SndXccOrigCallReq(ucCallId);
            }
         }
    }
    else
    {
        if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enServiceStatus)
        {
            /*判断呼叫重拨定时器是否已经超时 */
            if (TAF_XCALL_TIMER_STATUS_RUNING == TAF_XCALL_GetTimerStatus(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, ucCallId))
            {
                /*关闭重拨定时器，发起重拨 */
                TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, ucCallId);

                TAF_XCALL_SndXccOrigCallReq(ucCallId);
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvMmaSysCfgInfoInd
 功能描述  : 处理来自mma的ServiceStatusInd消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月19日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvMmaSysCfgInfoInd(VOS_VOID *pstMsg)
{
    MMA_TAF_SYS_CFG_INFO_IND_STRU      *pstSysCfgInd = VOS_NULL_PTR;
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT8                           ucCallId;
    VOS_UINT16                          usClientId;
    VOS_UINT32                          ulModuleId;

    pstSysCfgInd = (MMA_TAF_SYS_CFG_INFO_IND_STRU *)pstMsg;

    if ( VOS_TRUE == TAF_SDC_IsSpecRatInRatList(TAF_MMA_RAT_1X, &(pstSysCfgInd->stNewRatOrder)))
    {
        return;
    }

    for (ucCallId = 1; ucCallId < TAF_XCALL_CALL_ENTITY_MAX_NUM + 1; ucCallId++)
    {
        pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

        if (VOS_FALSE == pstCallEntity->ulUsed)
        {
            continue;
        }

        if (TAF_XCALL_TIMER_STATUS_RUNING != TAF_XCALL_GetTimerStatus(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, ucCallId))
        {
            continue;
        }

        /* 停止重拨定时器和重拨间隔定时器 */
        TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, ucCallId);
        TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, ucCallId);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        /*******************************************************************************************
         * 如果当前呼叫不满足重拨，则通知密话状态机，呼叫释放
         ******************************************************************************************/
        TAF_XCALL_ProcEccEvent(TAF_XCALL_XCC_MSG_EVENT_INT_CALL_REL_IND,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                               pstMsg,
                               VOS_NULL_PTR);
#endif

        pstCallEntity->enCause = TAF_CS_CAUSE_SYSCFG_MODE_CHANGE;
        TAF_XCALL_SndCallReleaseInd(ucCallId);

        usClientId = TAF_XCALL_GetClientInfo(ucCallId)->usClientId;
        ulModuleId = TAF_XCALL_GetClientInfo(ucCallId)->ulModuleId;

        enCallType  = TAF_XCALL_GetCallType(ucCallId);

        /* 给MMA发送TAF_MMA_1X_CALL_END_NTF消息 */
        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));

        /* 释放呼叫实体 */
        TAF_XCALL_FreeCallEntity(ucCallId);

        if (VOS_FALSE == TAF_XCALL_ExistCallInstance())
        {
            /* 清除SDC中CS呼叫标志 */
            TAF_SDC_SetCsCallExistFlg(VOS_FALSE);
        }

        ulNumOfCalls = 0;

        PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

        TAF_XCALL_GetNotIdleStateCalls(&ulNumOfCalls, aucCallIds);

        /* 如果没有呼叫实体 */
        if (0 == ulNumOfCalls)
        {
            /* 给APP上报MN_CALL_EVT_ALL_RELEASED事件 */
            TAF_XCALL_SndCallAllReleaseInd(ulModuleId);
        }
    }
}

#endif

/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



