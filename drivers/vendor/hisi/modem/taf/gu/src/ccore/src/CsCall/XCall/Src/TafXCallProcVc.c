/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallPorcVc.c
  版 本 号   : 初稿
  作    者   : Y00213812
  生成日期   : 2014年09月13日
  功能描述   : TAF X CALL处理VC的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年09月13日
    作    者   : Y00213812
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsCommonDef.h"
#include "TafXCallCtx.h"
#include "TafCsCallCommDef.h"
#include "VcCallInterface.h"
#include "TafXCallProcEccSrv.h"
#include "TafXCallSndXcc.h"
#include "TafXCallSndApp.h"
#include "TafXCallSndMma.h"
#include "MnComm.h"
#include "TafSdcCtx.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_PROC_VC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvVcEndCall
 功能描述  : 处理VC_CALL_END_CALL消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月3日
    作    者   : y00213812
    修改内容   : 新生成函数
  2.日    期   : 2015年12月22日
    作    者   : l00359089
    修改内容   : 实现函数功能
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvVcEndCall(VOS_VOID *pMsg)
{
    VC_CALL_MSG_STRU                   *pstRcvMsg = VOS_NULL_PTR;
    TAF_CS_CAUSE_ENUM_UINT32            enEndCause;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT16                          usClientId;
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    VOS_UINT8                           i;

    pstRcvMsg    = (VC_CALL_MSG_STRU*)pMsg;
    enEndCause   = TAF_CALL_ConvertVcCauseToTafCsCause(pstRcvMsg->enCause);

    ulNumOfCalls = 0;
    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetNotIdleStateCalls(&ulNumOfCalls, aucCallIds);
    ulModuleId = pstRcvMsg->ulSenderPid;

    /* 循环挂断所有非idle的呼叫 */
    for (i = 0; i < TAF_XCALL_MIN(ulNumOfCalls, TAF_XCALL_CALL_ENTITY_MAX_NUM); i++)
    {
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        TAF_XCALL_ProcEccEvent(TAF_XCALL_APP_MSG_EVENT_HANG_UP_REQ,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                               (VOS_VOID *)pstRcvMsg,
                               VOS_NULL_PTR);
#endif

        /* 停止重拨时长定时器 */
        TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, aucCallIds[i]);

        if (TAF_XCALL_TIMER_STATUS_RUNING == TAF_XCALL_GetTimerStatus(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, aucCallIds[i]))
        {
            /* 停止重拨间隔定时器 */
            TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, aucCallIds[i]);

            /* 通知呼叫终止 */
            enCallType = TAF_XCALL_GetCallType(aucCallIds[i]);
            usClientId = TAF_XCALL_GetClientInfo(aucCallIds[i])->usClientId;
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));

            /* 记录主动挂断的原因值 */
            TAF_XCALL_UpdateCcCause(aucCallIds[i], enEndCause);

            /* 给APP上报MN_CALL_EVT_RELEASED事件 */
            TAF_XCALL_SndCallReleaseInd(aucCallIds[i]);

            /* 清空对应的实体信息 */
            TAF_XCALL_FreeCallEntity(aucCallIds[i]);

            /* 记录ulModuleId*/
            ulModuleId = TAF_XCALL_GetClientInfo(aucCallIds[i])->ulModuleId;
        }
        else
        {
            /* 挂断该呼叫 */
            TAF_XCALL_SndXccHangUpCallReq(aucCallIds[i], TAF_XCC_END_REASON_NORMAL_RELEASE);

            TAF_XCALL_DeRegSsKeyEvent(aucCallIds[i], TAF_XCALL_SS_PROG_EVT_REL);

            /* 记录主动挂断的原因值 */
            TAF_XCALL_UpdateCcCause(aucCallIds[i], enEndCause);

            /* 记录呼叫挂断的方向 */
            TAF_XCALL_UpdateDiscCallDir(aucCallIds[i], VOS_TRUE);
        }
    }

    TAF_XCALL_GetNotIdleStateCalls(&ulNumOfCalls, aucCallIds);

    if (0 == ulNumOfCalls)
    {
        if (VOS_FALSE == TAF_XCALL_ExistCallInstance())
        {
            /* 清除SDC中CS呼叫标志 */
            TAF_SDC_SetCsCallExistFlg(VOS_FALSE);
        }

        /* 给APP上报MN_CALL_EVT_ALL_RELEASED事件 */
        TAF_XCALL_SndCallAllReleaseInd(ulModuleId);
    }
    else
    {
        TAF_XCALL_RegSsKeyEvent(aucCallIds[ulNumOfCalls - 1], TAF_XCALL_SS_PROG_EVT_REL, TAF_XCALL_SS_SUBSEQ_OP_RPT_SUCC);
    }
    return;
}


/*lint -restore*/
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


