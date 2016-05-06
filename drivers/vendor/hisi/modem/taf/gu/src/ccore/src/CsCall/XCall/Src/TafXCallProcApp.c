/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallProcApp.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年09月03日
  功能描述   : TAF X CALL处理来自APP的消息
  函数列表   :
  修改历史   :
  1.日    期   : 2014年09月03日
    作    者   : l60609
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXCallProcApp.h"
#include "TafXCallSndXcc.h"
#include "TafXCallSndApp.h"
#include "TafXCallSndMma.h"
#include "TafAgentInterface.h"
#include "MnComm.h"
#include "TafLog.h"

#include "TafSdcCtx.h"
#include "TafXCallProcXcc.h"

#include "TafCdmaPlusTranslate.h"

#include "TafMmaSndOm.h"

#include "TafStdlib.h"

#include "TafXCallProcEccSrv.h"

#include "TafXCallProcNvim.h"
#include "TafSpmComFunc.h"
#include "TafSdcLib.h"
#include "MnCallCtx.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_PROC_APP_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvAppCallOrigReq
 功能描述  : 处理MN_CALL_APP_ORIG_REQ消息,(AT&STK统一使用该函数)
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月3日
    作    者   : y00213812
    修改内容   : 新生成函数
  2.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : CDMA 1x项目迭代5修改
  3.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppCallOrigReq(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucCallId;
    MN_CALL_APP_REQ_MSG_STRU           *pstCallOrig = VOS_NULL_PTR;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsSrvStatus;

    enCsSrvStatus                       = TAF_SDC_GetCsServiceStatus();

    ucCallId                            = 0;
    pstCallOrig                         = (MN_CALL_APP_REQ_MSG_STRU *)pMsg;

    /* 判断当前是否可以发起呼叫 */
    ulRet = TAF_XCALL_IsAllowMoCallInCurrentStatus(pstCallOrig->unParm.stOrig.enCallType);

    /* 判断是否允许发起呼叫 */
    if (VOS_FALSE == ulRet)
    {
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        TAF_XCALL_ProcEccEvent(TAF_XCALL_XCC_MSG_EVENT_INT_CALL_REL_IND,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                               pMsg,
                               VOS_NULL_PTR);
#endif

        /* 上报呼叫失败 */
        TAF_XCALL_SndCallOrigCnf(TAF_CS_CAUSE_NOT_ALLOW,
                                 pstCallOrig->ulSenderPid,
                                 pstCallOrig->clientId,
                                 pstCallOrig->unParm.stOrig.enCallType);

        return;
    }

    /* 分配call Id */
    ulRet = TAF_XCALL_AllocCallId(&ucCallId);
    if (VOS_FALSE == ulRet)
    {
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        TAF_XCALL_ProcEccEvent(TAF_XCALL_XCC_MSG_EVENT_INT_CALL_REL_IND,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                               pMsg,
                               VOS_NULL_PTR);
#endif

        /* 上报呼叫失败 */
        TAF_XCALL_SndCallOrigCnf(TAF_CS_CAUSE_NO_CALL_ID,
                                 pstCallOrig->ulSenderPid,
                                 pstCallOrig->clientId,
                                 pstCallOrig->unParm.stOrig.enCallType);

        return;
    }

    /* 新建一个呼叫实体 */
    TAF_XCALL_CreateMoCallEntity(ucCallId, pstCallOrig);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* TO DO:给MTC模块上报当前CS域业务状态 */
    /* TAF_SendMtcCsSrvInfoInd(); */
#endif

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    TAF_XCALL_ProcEccEvent(TAF_XCALL_APP_MSG_EVENT_ORIG_REQ,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           pMsg,
                           VOS_NULL_PTR);
#endif

    /* 根据当前1X的服务状态判定是否需要发送呼叫请求给XCC,如果当前非正常服务,
       不发给XCC呼叫请求,重拨情况下直接通知XSD进行重拨;否则发给XCC */

    /* 通知MMA CALL NTF */
    TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, pstCallOrig->clientId, TAF_XCALL_BuildMmaCallType(pstCallOrig->unParm.stOrig.enCallType));

    /* 回复呼叫成功 */
    TAF_XCALL_SndCallOrigCnf(TAF_CS_CAUSE_SUCCESS,
                             pstCallOrig->ulSenderPid,
                             pstCallOrig->clientId,
                             pstCallOrig->unParm.stOrig.enCallType);

    /* 上报呼叫事件 */
    TAF_XCALL_SndCallOrigInd(ucCallId);

    /* 启动silent redial定时器 */
    TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, TAF_XCALL_GetRedialPeriodTimerLen(ucCallId), ucCallId);

    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enCsSrvStatus)
    {
        /* 发送呼叫消息给XCC */
        TAF_XCALL_SndXccOrigCallReq(ucCallId);

        return;
    }

    if (TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE == enCsSrvStatus)
    {
        /* 紧急呼且Limit Service，直接发起呼叫 */
        if (MN_CALL_TYPE_EMERGENCY == TAF_XCALL_GetCallType(ucCallId))
        {
            /* 发送呼叫消息给XCC */
            TAF_XCALL_SndXccOrigCallReq(ucCallId);

            return;
        }

        TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN, ucCallId);

        return;
    }

    if (MN_CALL_TYPE_EMERGENCY == TAF_XCALL_GetCallType(ucCallId))
    {
        TAF_SndMmaCdmaCallRedialSystemAcquireNtf(WUEPS_PID_TAF,
                                     pstCallOrig->clientId,
                                     TAF_XCALL_BuildMmaCallType(pstCallOrig->unParm.stOrig.enCallType),
                                     TAF_CS_CAUSE_XCALL_INTERNAL_NO_SERVICE);
    }

    TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN, ucCallId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvAppSupsCmdReq
 功能描述  : 处理MN_CALL_APP_SUPS_CMD_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月3日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppSupsCmdReq(VOS_VOID *pMsg)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq = VOS_NULL_PTR;
    MN_CALL_SUPS_PARAM_STRU            *pstCallSupsParam = VOS_NULL_PTR;

    pstAppCallSupsReq = (MN_CALL_APP_REQ_MSG_STRU *)pMsg;
    pstCallSupsParam  = &(pstAppCallSupsReq->unParm.stCallMgmtCmd);

    /* 1、当前有一路处于active状态的通话:
        如果再收到APP的orig请求，直接回复失败，
        也不会收到XCC的incoming消息，
        只处理flash消息
        所以处于active状态的通话只有一路，而且不会有其它状态的通话存在

        2、暂时存在两路通话的场景:
        有一路处于dialing状态的通话，此时又收到XCC的incoming消息
     */

    switch (pstCallSupsParam->enCallSupsCmd)
    {
        /* CHLD=0, Releases all held calls or sets User Determined User Busy (UDUB) for a waiting call */
        case MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB:
            TAF_XCALL_ProcCallSupsCmdRelHoldOrUdubReq(pstAppCallSupsReq);
            break;

        /* CHLD=1, Releases all active calls (if any exist) and accepts the other (held or waiting) call */
        case MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH:
            TAF_XCALL_ProcCallSupsCmdRelActAcptOthReq(pstAppCallSupsReq);
            break;

        /* CHLD=1x, Releases a specific active call X*/
        case MN_CALL_SUPS_CMD_REL_CALL_X:
            TAF_XCALL_ProcCallSupsCmdRelCallXReq(pstAppCallSupsReq);
            break;

        /* ATH, Release all calls */
        case MN_CALL_SUPS_CMD_REL_ALL_CALL:
            TAF_XCALL_ProcCallSupsCmdRelAllCallReq(pstAppCallSupsReq);
            break;

        /* CHLD=2, Places all active calls (if any exist) on hold and accepts the other (held or waiting) call */
        case MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH:
            TAF_XCALL_ProcCallSupsCmdHoldActAcptOthReq(pstAppCallSupsReq);
            break;

        default:
            /* 其它情况，直接回复失败 */
            TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                    pstAppCallSupsReq->clientId,
                                    pstAppCallSupsReq->opId,
                                    pstCallSupsParam->callId,
                                    TAF_CS_CAUSE_NOT_ALLOW);
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvAppSendFlashReq
 功能描述  : 处理TAF_CALL_APP_SEND_FLASH_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月5日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年11月7日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
  3.日    期   : 2015年07月23日
    作    者   : y00307564
    修改内容   : 增加"+"号转换逻辑修改
  4.日    期   : 2015年08月10日
    作    者   : y00307564
    修改内容   : DTS2015080608576修改

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppSendFlashReq(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    TAF_CALL_APP_SEND_FLASH_REQ_STRU   *pstFlashReqMsg;
    VOS_UINT8                           ucDstDigitNum;
    VOS_UINT8                           aucDstDigit[TAF_CALL_MAX_FLASH_DIGIT_LEN + 1];

    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    MN_CALL_CALLED_NUM_STRU             stDialNumber;
    MN_CALL_EMERGENCY_CAT_STRU          stEmergencyCat;
    VOS_UINT32                          ulRslt;

    pstFlashReqMsg = (TAF_CALL_APP_SEND_FLASH_REQ_STRU *)pMsg;

    /* 根据状态查找处于ACTIVE状态的call id，目前只支持在ACTIVE状态下发送Flash */
    TAF_XCALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aucCallIds);

    /* 处于Active状态的实例至多只能有1个 */
    if (1 != ulNumOfCalls)
    {
        TAF_XCALL_SndFlashRslt(pstFlashReqMsg->usClientId, pstFlashReqMsg->ucOpId, VOS_ERR);
        return;
    }

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(aucCallIds[0]);

    PS_MEM_SET(&(pstCallEntity->stFlashInfo), 0x00, sizeof(TAF_XCALL_FLASH_INFO_STRU));
    PS_MEM_SET(&stDialNumber, 0x00, sizeof(MN_CALL_CALLED_NUM_STRU));

    pstCallEntity->stFlashInfo.ucIsEmcCall = VOS_FALSE;

    if ('+' == pstFlashReqMsg->stFlashPara.aucDigit[0])
    {
        ulRslt = TAF_STD_ConvertAsciiNumberToBcd(((VOS_CHAR *)pstFlashReqMsg->stFlashPara.aucDigit) + 1,
                                                              stDialNumber.aucBcdNum,
                                                             &stDialNumber.ucNumLen);

        stDialNumber.enNumType = (MN_CALL_IS_EXIT | (MN_CALL_TON_INTERNATIONAL << 4) | MN_CALL_NPI_ISDN);

    }
    else
    {

        ulRslt = TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR *)pstFlashReqMsg->stFlashPara.aucDigit,
                                                             stDialNumber.aucBcdNum,
                                                            &stDialNumber.ucNumLen);

        stDialNumber.enNumType = (MN_CALL_IS_EXIT | (MN_CALL_TON_UNKNOWN << 4) | MN_CALL_NPI_ISDN);
    }

    if (MN_ERR_NO_ERROR != ulRslt)
    {
        TAF_XCALL_SndFlashRslt(pstFlashReqMsg->usClientId, pstFlashReqMsg->ucOpId, VOS_ERR);

        return;
    }

    if (VOS_TRUE  == TAF_SPM_IsEmergencyNum_CDMA(&stDialNumber,
                                                 &stEmergencyCat.bExist,
                                                 &stEmergencyCat.ucEmergencyCat))
    {
        pstCallEntity->stFlashInfo.ucIsEmcCall = VOS_TRUE;
    }

    ucDstDigitNum = 0;
    PS_MEM_SET(aucDstDigit, 0x00, sizeof(aucDstDigit));

    TAF_XCALL_ReplaceFlashPlusWithDigit(pstFlashReqMsg->stFlashPara.ucDigitNum,
                                        pstFlashReqMsg->stFlashPara.aucDigit,
                                        &ucDstDigitNum,
                                        aucDstDigit);

    /* 向XCC发送ID_XCALL_XCC_SEND_FLASH_REQ */
    if (VOS_OK != TAF_XCALL_SndXccFlashReq(aucCallIds[0],
                                           ucDstDigitNum,
                                           aucDstDigit,
                                           pstCallEntity->stFlashInfo.ucIsEmcCall))
    {
        PS_MEM_SET(&(pstCallEntity->stFlashInfo), 0x00, sizeof(TAF_XCALL_FLASH_INFO_STRU));

        TAF_XCALL_SndFlashRslt(pstFlashReqMsg->usClientId, pstFlashReqMsg->ucOpId, VOS_ERR);
        return;
    }

    pstCallEntity->stFlashInfo.stClientInfo.ulModuleId = pstFlashReqMsg->ulSenderPid;
    pstCallEntity->stFlashInfo.stClientInfo.usClientId = pstFlashReqMsg->usClientId;
    pstCallEntity->stFlashInfo.stClientInfo.ucOpId     = pstFlashReqMsg->ucOpId;

    if (VOS_TRUE == pstCallEntity->stFlashInfo.ucIsEmcCall)
    {
        PS_MEM_CPY(&pstCallEntity->stFlashInfo.stDialNumber, &stDialNumber, sizeof(MN_CALL_CALLED_NUM_STRU));

        TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_EMERGENCY_VOICE_CALL);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcCallSupsCmdRelHoldOrUdubReq
 功能描述  : 处理MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB请求
 输入参数  : MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月5日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_ProcCallSupsCmdRelHoldOrUdubReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    MN_CALL_SUPS_PARAM_STRU            *pstCallSupsParam = VOS_NULL_PTR;

    pstCallSupsParam  = &(pstAppCallSupsReq->unParm.stCallMgmtCmd);

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetCallsByState(MN_CALL_S_INCOMING, &ulNumOfCalls, aucCallIds);

    /* 挂断Incoming状态的呼叫，Incoming状态的呼叫只可能一个 */
    if (1 == ulNumOfCalls)
    {
        /* 挂断该呼叫 */
        TAF_XCALL_SndXccHangUpCallReq(aucCallIds[0], TAF_XCC_END_REASON_NORMAL_RELEASE);

        TAF_XCALL_RegSsKeyEvent(aucCallIds[0], TAF_XCALL_SS_PROG_EVT_REL, TAF_XCALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* 更新client info */
        TAF_XCALL_UpdateClientInfo(aucCallIds[0],
                                   pstAppCallSupsReq->ulSenderPid,
                                   pstAppCallSupsReq->clientId,
                                   pstAppCallSupsReq->opId);

        /* 记录主动挂断的原因值 */
        TAF_XCALL_UpdateCcCause(aucCallIds[0], TAF_CS_CAUSE_XCALL_MS_NORMAL_RELEASE);

        /* 记录呼叫挂断的方向 */
        TAF_XCALL_UpdateDiscCallDir(aucCallIds[0], VOS_TRUE);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        TAF_XCALL_ProcEccEvent(TAF_XCALL_APP_MSG_EVENT_HANG_UP_REQ,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                               (VOS_VOID *)pstAppCallSupsReq,
                               VOS_NULL_PTR);
#endif

        /* 回复请求结果 */
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                aucCallIds[0], TAF_CS_CAUSE_SUCCESS);
    }
    else
    {
        /* 回复失败 */
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                pstCallSupsParam->callId, TAF_CS_CAUSE_NOT_ALLOW);
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcCallSupsCmdRelActAcptOthReq
 功能描述  : 处理MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH请求
 输入参数  : MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月5日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_ProcCallSupsCmdRelActAcptOthReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
)
{
    /* active call和incoming call不可能同时存在，所以或者挂断active call或者接听incoming call */
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    MN_CALL_SUPS_PARAM_STRU            *pstCallSupsParam = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstCallSupsParam  = &(pstAppCallSupsReq->unParm.stCallMgmtCmd);

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aucCallIds);

    if (0 != ulNumOfCalls)
    {
        /* 目前只可能有一个active状态的呼叫 */
        for (i = 0; i < TAF_XCALL_MIN(ulNumOfCalls, TAF_XCALL_CALL_ENTITY_MAX_NUM); i++)
        {
            /* 挂断该呼叫 */
            TAF_XCALL_SndXccHangUpCallReq(aucCallIds[i], TAF_XCC_END_REASON_NORMAL_RELEASE);

            TAF_XCALL_DeRegSsKeyEvent(aucCallIds[i], TAF_XCALL_SS_PROG_EVT_REL);

            /* 更新client info */
            TAF_XCALL_UpdateClientInfo(aucCallIds[i],
                                       pstAppCallSupsReq->ulSenderPid,
                                       pstAppCallSupsReq->clientId,
                                       pstAppCallSupsReq->opId);

            /* 记录主动挂断的原因值 */
            TAF_XCALL_UpdateCcCause(aucCallIds[i], TAF_CS_CAUSE_XCALL_MS_NORMAL_RELEASE);

            /* 记录呼叫挂断的方向 */
            TAF_XCALL_UpdateDiscCallDir(aucCallIds[i], VOS_TRUE);

        }

        TAF_XCALL_RegSsKeyEvent(aucCallIds[ulNumOfCalls - 1], TAF_XCALL_SS_PROG_EVT_REL, TAF_XCALL_SS_SUBSEQ_OP_RPT_SUCC);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        TAF_XCALL_ProcEccEvent(TAF_XCALL_APP_MSG_EVENT_HANG_UP_REQ,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                               (VOS_VOID *)pstAppCallSupsReq,
                               VOS_NULL_PTR);

#endif

        /* 回复请求结果 */
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetCallsByState(MN_CALL_S_INCOMING, &ulNumOfCalls, aucCallIds);

    /* Incoming状态的呼叫只可能一个 */
    if (1 == ulNumOfCalls)
    {
        /* 接听该呼叫 */
        TAF_XCALL_SndXccAnswerCallReq(aucCallIds[0]);

        TAF_XCALL_RegSsKeyEvent(aucCallIds[0], TAF_XCALL_SS_PROG_EVT_ANS, TAF_XCALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* 更新client info */
        TAF_XCALL_UpdateClientInfo(aucCallIds[0],
                                   pstAppCallSupsReq->ulSenderPid,
                                   pstAppCallSupsReq->clientId,
                                   pstAppCallSupsReq->opId);

        /* 回复请求结果 */
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                aucCallIds[0], TAF_CS_CAUSE_SUCCESS);

        return;
    }

    TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                            pstAppCallSupsReq->clientId,
                            pstAppCallSupsReq->opId,
                            pstCallSupsParam->callId, TAF_CS_CAUSE_NOT_ALLOW);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcCallSupsCmdRelCallXReq
 功能描述  : 处理MN_CALL_SUPS_CMD_REL_ALL_CALL请求，挂断指定呼叫
 输入参数  : MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月5日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : CDMA 1x项目迭代5修改

*****************************************************************************/
VOS_VOID TAF_XCALL_ProcCallSupsCmdRelCallXReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
)
{
    MN_CALL_SUPS_PARAM_STRU            *pstCallSupsParam = VOS_NULL_PTR;
    MN_CALL_STATE_ENUM_U8               enCallState;

    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT16                          usClientId;

    pstCallSupsParam  = &(pstAppCallSupsReq->unParm.stCallMgmtCmd);

    /* 判断Call Id的有效性 */
    if (VOS_TRUE != TAF_XCALL_IsAvailCallId(pstCallSupsParam->callId))
    {
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                pstCallSupsParam->callId, TAF_CS_CAUSE_NOT_ALLOW);
        return;
    }

    enCallState = TAF_XCALL_GetCallState(pstCallSupsParam->callId);

    if (MN_CALL_S_IDLE == enCallState)
    {
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                pstCallSupsParam->callId, TAF_CS_CAUSE_NOT_ALLOW);

        return;
    }

    if (TAF_XCALL_TIMER_STATUS_RUNING == TAF_XCALL_GetTimerStatus(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, pstCallSupsParam->callId))
    {
        /* 停止定时器 */
        TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, pstCallSupsParam->callId);
        TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, pstCallSupsParam->callId);

        /* 通知呼叫终止 */
        enCallType = TAF_XCALL_GetCallType(pstCallSupsParam->callId);
        usClientId = TAF_XCALL_GetClientInfo(pstCallSupsParam->callId)->usClientId;
        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));

        /* 记录主动挂断的原因值 */
        TAF_XCALL_UpdateCcCause(pstCallSupsParam->callId, TAF_CS_CAUSE_XCALL_MS_NORMAL_RELEASE);

        /* 记录呼叫挂断的方向 */
        TAF_XCALL_UpdateDiscCallDir(pstCallSupsParam->callId, VOS_TRUE);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        TAF_XCALL_ProcEccEvent(TAF_XCALL_APP_MSG_EVENT_HANG_UP_REQ,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                               (VOS_VOID *)pstAppCallSupsReq,
                               VOS_NULL_PTR);
#endif

        /* 回复请求结果 */
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);

        /* 给APP上报MN_CALL_EVT_RELEASED事件 */
        TAF_XCALL_SndCallReleaseInd(pstCallSupsParam->callId);

        /* 清空对应的实体信息 */
        TAF_XCALL_FreeCallEntity(pstCallSupsParam->callId);

        return;

    }

    /* 停止重拨定时器,如果定时器未启动或call id不一致则跳过 */
    TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, pstCallSupsParam->callId);
    TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, pstCallSupsParam->callId);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    TAF_XCALL_ProcEccEvent(TAF_XCALL_APP_MSG_EVENT_HANG_UP_REQ,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           (VOS_VOID *)pstAppCallSupsReq,
                           VOS_NULL_PTR);
#endif

    /* 挂断该呼叫 */
    TAF_XCALL_SndXccHangUpCallReq(pstCallSupsParam->callId, TAF_XCC_END_REASON_NORMAL_RELEASE);

    TAF_XCALL_RegSsKeyEvent(pstCallSupsParam->callId, TAF_XCALL_SS_PROG_EVT_REL, TAF_XCALL_SS_SUBSEQ_OP_RPT_SUCC);

    /* 更新client info */
    TAF_XCALL_UpdateClientInfo(pstCallSupsParam->callId,
                               pstAppCallSupsReq->ulSenderPid,
                               pstAppCallSupsReq->clientId,
                               pstAppCallSupsReq->opId);

    /* 记录主动挂断的原因值 */
    TAF_XCALL_UpdateCcCause(pstCallSupsParam->callId, TAF_CS_CAUSE_XCALL_MS_NORMAL_RELEASE);

    /* 记录呼叫挂断的方向 */
    TAF_XCALL_UpdateDiscCallDir(pstCallSupsParam->callId, VOS_TRUE);

    /* 回复请求结果 */
    TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                            pstAppCallSupsReq->clientId,
                            pstAppCallSupsReq->opId,
                            pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcCallSupsCmdRelAllCallReq
 功能描述  : 处理MN_CALL_SUPS_CMD_REL_ALL_CALL请求，挂断所有呼叫
 输入参数  : MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月5日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : CDMA 1x项目迭代5修改
  3.日    期   : 2015年7月23日
    作    者   : c00299063
    修改内容   : DTS2015072309638
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcCallSupsCmdRelAllCallReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
)
{
    /* 暂时存在两路通话的场景:
        有一路处于dialing状态的通话，此时又收到XCC的incoming消息
     */
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    MN_CALL_SUPS_PARAM_STRU            *pstCallSupsParam = VOS_NULL_PTR;
    VOS_UINT8                           i;

    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT16                          usClientId;
    VOS_UINT32                          ulModuleId;

    pstCallSupsParam  = &(pstAppCallSupsReq->unParm.stCallMgmtCmd);

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetNotIdleStateCalls(&ulNumOfCalls, aucCallIds);

    if (0 == ulNumOfCalls)
    {
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    ulModuleId = pstAppCallSupsReq->ulSenderPid;

    /* 循环挂断所有非idle的呼叫 */
    for (i = 0; i < TAF_XCALL_MIN(ulNumOfCalls, TAF_XCALL_CALL_ENTITY_MAX_NUM); i++)
    {
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        TAF_XCALL_ProcEccEvent(TAF_XCALL_APP_MSG_EVENT_HANG_UP_REQ,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                               (VOS_VOID *)pstAppCallSupsReq,
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
            TAF_XCALL_UpdateCcCause(aucCallIds[i], TAF_CS_CAUSE_XCALL_MS_NORMAL_RELEASE);

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

            /* 更新client info */
            TAF_XCALL_UpdateClientInfo(aucCallIds[i],
                                       pstAppCallSupsReq->ulSenderPid,
                                       pstAppCallSupsReq->clientId,
                                       pstAppCallSupsReq->opId);

            /* 记录主动挂断的原因值 */
            TAF_XCALL_UpdateCcCause(aucCallIds[i], TAF_CS_CAUSE_XCALL_MS_NORMAL_RELEASE);

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
            TAF_XCALL_SetCsCallExistFlg(VOS_FALSE, MN_CALL_TYPE_BUTT);
        }

        /* 给APP上报MN_CALL_EVT_ALL_RELEASED事件 */
        TAF_XCALL_SndCallAllReleaseInd(ulModuleId);
    }
    else
    {

        TAF_XCALL_RegSsKeyEvent(aucCallIds[ulNumOfCalls - 1], TAF_XCALL_SS_PROG_EVT_REL, TAF_XCALL_SS_SUBSEQ_OP_RPT_SUCC);
    }


    /* 回复请求结果 */
    TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                            pstAppCallSupsReq->clientId,
                            pstAppCallSupsReq->opId,
                            pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcCallSupsCmdHoldActAcptOthReq
 功能描述  : 处理MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH请求
 输入参数  : MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月5日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_ProcCallSupsCmdHoldActAcptOthReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    MN_CALL_SUPS_PARAM_STRU            *pstCallSupsParam = VOS_NULL_PTR;

    pstCallSupsParam  = &(pstAppCallSupsReq->unParm.stCallMgmtCmd);

    /* 处于active状态的通话只有一路，而且不会有其它状态的通话存在

        存在两路通话的场景:
        有一路处于dialing状态的通话，此时又收到XCC的incoming消息 */

    /* 3GPP2中hold操作都是通过FLASH消息，所以收到该请求只判断当前是否有incoming call */

    /* 如果没有incoming call，有一个active的，并且bypass为true，回复成功 */

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aucCallIds);

    if (1 == ulNumOfCalls)
    {
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                aucCallIds[0], TAF_CS_CAUSE_SUCCESS);

        /* 给APP回复MN_CALL_EVT_SS_CMD_RSLT事件 */
        TAF_XCALL_SndSupsResult(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                aucCallIds[0], MN_CALL_SS_RES_SUCCESS);

        /* 不需要给APP上报MN_CALL_EVT_CONNECT事件，在收到XCC的connect ind时已上报 */

        return;
    }

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetCallsByState(MN_CALL_S_INCOMING, &ulNumOfCalls, aucCallIds);

    /* Incoming状态的呼叫只可能一个 */
    if (1 == ulNumOfCalls)
    {
        /* 接听该呼叫 */
        TAF_XCALL_SndXccAnswerCallReq(aucCallIds[0]);

        TAF_XCALL_RegSsKeyEvent(aucCallIds[0], TAF_XCALL_SS_PROG_EVT_ANS, TAF_XCALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* 更新client info */
        TAF_XCALL_UpdateClientInfo(aucCallIds[0],
                                   pstAppCallSupsReq->ulSenderPid,
                                   pstAppCallSupsReq->clientId,
                                   pstAppCallSupsReq->opId);

        /* 回复请求结果 */
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                aucCallIds[0], TAF_CS_CAUSE_SUCCESS);

        return;
    }

    TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                            pstAppCallSupsReq->clientId,
                            pstAppCallSupsReq->opId,
                            pstCallSupsParam->callId, TAF_CS_CAUSE_NOT_ALLOW);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvAppSendBurstDTMFReq
 功能描述  : 处理TAF_CALL_SEND_BURST_DTMF_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改，Cont DTMF和Burst DTMF的等待XCC响应公用一个标志
  3.日    期   : 2015年8月18日
    作    者   : l00324781
    修改内容   : DTS2015081708770修改，向xcc发送消息前，
                判断定时器StopAndStartContDtmfInterval是否处于运行态
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppSendBurstDTMFReq(VOS_VOID *pMsg)
{
    TAF_CALL_BURST_DTMF_REQ_MSG_STRU                       *pstBurstDTMFReqMsg;
    TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8             enResult;

    pstBurstDTMFReqMsg = (TAF_CALL_BURST_DTMF_REQ_MSG_STRU *)pMsg;

    /* 判断该call_id对应的状态是否为ACTIVE,目前只支持在该状态下发送Burst DTMF  */
    if(MN_CALL_S_ACTIVE != TAF_XCALL_GetCallState(pstBurstDTMFReqMsg->stBurstDTMFPara.ucCallId))
    {
        /* send TAF_CALL_EVT_SEND_BURST_DTMF_CNF */
        TAF_XCALL_SndBurstDTMFCnf(pstBurstDTMFReqMsg->usClientId,
                                  pstBurstDTMFReqMsg->ucOpId,
                                  TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ABNORMAL_STATE,
                                  pstBurstDTMFReqMsg->stBurstDTMFPara.ucCallId);
        return;
    }

    /*如果等待XCC回复的Burst DTMF CNF消息的标识为VOS_FALSE，XCALL可以给XCC发送ID_XCALL_XCC_BURST_DTMF_REQ消息
      如果等待XCC回复的Burst DTMF CNF消息的标识为VOS_TRUE,XCALL需要等待发送中的ID_XCALL_XCC_BURST_DTMF_REQ的回复消息，
      同时把最新收到的TAF_CALL_SEND_BURST_DTMF_REQ消息缓存起来
    */
    if(TAF_XCALL_WAIT_NO_XCC_CNF == TAF_XCALL_GetWaitForXCCDTMFCnfFlag(pstBurstDTMFReqMsg->stBurstDTMFPara.ucCallId))
    {
        /* 如果此时状态为:收到Start Cont Dtmf Req的响应，但是定时器处于运行态，此时收到消息，应该缓存
            等待定时器超时，再处理
        */
        if (TAF_XCALL_TIMER_STATUS_RUNING
            == TAF_XCALL_GetTimerStatus(TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL, pstBurstDTMFReqMsg->stBurstDTMFPara.ucCallId))
        {
            enResult = TAF_XCALL_SaveBurstDtmfInfo(pstBurstDTMFReqMsg);
        }
        else
        {
            enResult = TAF_XCALL_SndXccBurstDTMFReq(&pstBurstDTMFReqMsg->stBurstDTMFPara);

            TAF_XCALL_SetWaitForXCCDTMFCnfFlag(pstBurstDTMFReqMsg->stBurstDTMFPara.ucCallId, TAF_XCALL_WAIT_XCC_CNF_BURST_DTMF);
        }

    }
    else
    {
        enResult = TAF_XCALL_SaveBurstDtmfInfo(pstBurstDTMFReqMsg);
    }

    /* 回复XCALL TAF_CALL_EVT_SEND_BURST_DTMF_CNF (ucResult)*/
    TAF_XCALL_SndBurstDTMFCnf(pstBurstDTMFReqMsg->usClientId,
                              pstBurstDTMFReqMsg->ucOpId,
                              enResult,
                              pstBurstDTMFReqMsg->stBurstDTMFPara.ucCallId);

    return;
}

/* Buffer操作函数从XCallProcApp挪到XCallCtx.c中 */


/*****************************************************************************
 函 数 名  : TAF_XCALL_GetRedialPeriodTimerLen
 功能描述  : 获取重拨定时器时长
 输入参数  : VOS_UINT8    ucCallIds
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月14日
    作    者   : y00314741
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XCALL_GetRedialPeriodTimerLen(
    VOS_UINT8                           ucCallId
)
{
    if (MN_CALL_TYPE_EMERGENCY == TAF_XCALL_GetCallType(ucCallId))
    {
        return TAF_XCALL_GetConfigInfo()->ulEmcRedialPeriod;
    }
    else
    {
        return TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD_LEN;
    }
}

/* 删除无效的函数 */

/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvAppGetCallInfoReq
 功能描述  : 处理ID_TAFAGENT_MN_GET_CALL_INFO_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : h00246512
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAgentGetCallInfoReq(VOS_VOID *pMsg)
{
    TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU                    *pstCnf;
    VOS_UINT8                                               ucCallId;
    TAF_XCALL_CALL_ENTITY_STRU                             *pstXcallEntity = VOS_NULL_PTR;

    pstCnf = (TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                              sizeof(TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstCnf)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,"TAF_XCALL_RcvAppGetCallInfoReq:alloc msg failed.");
        return;
    }

    PS_MEM_SET(pstCnf, 0x00, sizeof(TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU));


    for (ucCallId = 1; ucCallId <= TAF_XCALL_CALL_ENTITY_MAX_NUM; ucCallId++)
    {
        pstXcallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);
        if ((VOS_TRUE == pstXcallEntity->ulUsed)
         && (MN_CALL_S_IDLE != pstXcallEntity->enCallState))

        {
            pstCnf->stCallInfo[pstCnf->ucNumOfCalls].callId       = ucCallId;
            pstCnf->stCallInfo[pstCnf->ucNumOfCalls].enCallType   = pstXcallEntity->enCallType;
            pstCnf->stCallInfo[pstCnf->ucNumOfCalls].enCallState  = pstXcallEntity->enCallState;

            (pstCnf->ucNumOfCalls)++;
        }
    }

    pstCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pstCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pstCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pstCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pstCnf->ulLength                      = sizeof(TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCnf->enMsgId                       = ID_TAFAGENT_MN_GET_CALL_INFO_CNF;

    PS_SEND_MSG(WUEPS_PID_TAF, pstCnf);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvAppGetCallInfoReq
 功能描述  : 处理MN_CALL_APP_GET_INFO_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppGetCallInfoReq(VOS_VOID *pMsg)
{
    MN_CALL_INFO_QRY_CNF_STRU          *pstAppCnfMsg   = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstXcallEntity = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstCallMsg = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucCallId;


    pstCallMsg = (MN_CALL_APP_REQ_MSG_STRU *)pMsg;

    /* 初始化 */
    usLength     = 0;

    pstAppCnfMsg = (MN_CALL_INFO_QRY_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                    sizeof(MN_CALL_INFO_QRY_CNF_STRU));

    if (VOS_NULL_PTR == pstAppCnfMsg)
    {
        return;
    }
    /* 获取当前所有状态不为IDLE的呼叫信息 */
    /*遍历所有呼叫控制实体*/
    VOS_MemSet(pstAppCnfMsg, 0x00, sizeof(MN_CALL_INFO_QRY_CNF_STRU));

    for (ucCallId = 1; ucCallId <= TAF_XCALL_CALL_ENTITY_MAX_NUM; ucCallId++)
    {
        pstXcallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);
        if ((VOS_TRUE == pstXcallEntity->ulUsed)
         && (MN_CALL_S_IDLE != pstXcallEntity->enCallState))

        {
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].callId      = ucCallId;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enCallDir   = pstXcallEntity->enCallDir;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enCallState = pstXcallEntity->enCallState;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enMptyState = MN_CALL_NOT_IN_MPTY;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enCallType  = pstXcallEntity->enCallType;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP2;

            PS_MEM_CPY(&(pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].stCallNumber),
                       &(pstXcallEntity->stCallNumber),
                       sizeof(MN_CALL_BCD_NUM_STRU));

            PS_MEM_CPY(&(pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].stConnectNumber),
                       &(pstXcallEntity->stConnectNumber),
                       sizeof(MN_CALL_BCD_NUM_STRU));

            PS_MEM_CPY(&(pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].stCalledNumber),
                       &(pstXcallEntity->stCalledNumber),
                       sizeof(MN_CALL_CALLED_NUM_STRU));

            (pstAppCnfMsg->ucNumOfCalls)++;
        }
    }

    /* 填写事件名称 */
    pstAppCnfMsg->enEvent  = MN_CALL_EVT_CLCC_INFO;
    pstAppCnfMsg->clientId = MN_GetRealClientId(pstCallMsg->clientId, WUEPS_PID_TAF);

    /* 确定消息长度 */
    usLength = (TAF_UINT16)sizeof(MN_CALL_INFO_QRY_CNF_STRU);

    /* 通过异步消息发送给AT */
    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (TAF_UINT8 *)pstAppCnfMsg, usLength);

    PS_MEM_FREE(WUEPS_PID_TAF, pstAppCnfMsg);
    return;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvAppXlemaReq
 功能描述  : 紧急呼号码查询处理
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月6日
    作    者   : h0246512
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppXlemaReq(VOS_VOID *pMsg)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstCallMsg      = VOS_NULL_PTR;
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo   = VOS_NULL_PTR;

    pstCallMsg = (MN_CALL_APP_REQ_MSG_STRU*)pMsg;

    pstEccNumInfo = (MN_CALL_ECC_NUM_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_CALL_ECC_NUM_INFO_STRU));
    if (VOS_NULL_PTR == pstEccNumInfo)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_XCALL_RcvAppXlemaReq: Alloc Mem Fail.");
        return;
    }

    /* 消息初始化 */
    PS_MEM_SET(pstEccNumInfo, 0, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    pstEccNumInfo->enEvent    = MN_CALL_EVT_XLEMA_CNF;
    pstEccNumInfo->usClientId = pstCallMsg->clientId;

    /* 获取紧急呼列表 */
    TAF_XCALL_GetEccNumList(pstEccNumInfo);

    TAF_XCALL_SndXlemaCnf(pstEccNumInfo);

    /* 内存释放 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstEccNumInfo);
    return;
}



/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvAppCallOrigReq
 功能描述  : 处理MN_CALL_APP_ORIG_REQ消息,(AT&STK统一使用该函数)
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月8日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppCustomDialReq(VOS_VOID *pMsg)
{
    VOS_UINT32                                    ulRet;
    VOS_UINT8                                     ucCallId;
    TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU       *pstCallOrig = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU                   *pstCallEntity = VOS_NULL_PTR;

    ucCallId                            = 0;
    pstCallOrig                         = (TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU *)pMsg;

    /* 判断当前是否可以发起呼叫 */
    ulRet = TAF_XCALL_IsAllowMoCallInCurrentStatus(pstCallOrig->stCustomDialPara.enCallType);

    /* 判断是否允许发起呼叫 */
    if (VOS_FALSE == ulRet)
    {
        /* 上报呼叫失败 */
        TAF_XCALL_SndCallOrigCnf(TAF_CS_CAUSE_NOT_ALLOW,
                                 pstCallOrig->ulSenderPid,
                                 pstCallOrig->usClientId,
                                 pstCallOrig->stCustomDialPara.enCallType);

        return;
    }

    /* 分配call Id */
    ulRet = TAF_XCALL_AllocCallId(&ucCallId);
    if (VOS_FALSE == ulRet)
    {
        /* 上报呼叫失败 */
        TAF_XCALL_SndCallOrigCnf(TAF_CS_CAUSE_NO_CALL_ID,
                                 pstCallOrig->ulSenderPid,
                                 pstCallOrig->usClientId,
                                 pstCallOrig->stCustomDialPara.enCallType);

        return;
    }

    /* 新建一个呼叫实体 */
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    /* 记录发起call业务用户的信息(AT/STK) */
    TAF_XCALL_UpdateClientInfo(ucCallId,
                               pstCallOrig->ulSenderPid,
                               pstCallOrig->usClientId,
                               pstCallOrig->ucOpId);
    /* 初始化呼叫参数 */
    pstCallEntity->enCallDir            = MN_CALL_DIR_MO;
    pstCallEntity->enCallState          = MN_CALL_S_DIALING;
    pstCallEntity->enCallType           = pstCallOrig->stCustomDialPara.enCallType;
    pstCallEntity->enCause              = TAF_CS_CAUSE_SUCCESS;
    pstCallEntity->ucConnectId          = 0;
    pstCallEntity->ucConRef             = 0;
    pstCallEntity->enSo                 = (TAF_XCALL_SO_TYPE_ENUM_UINT16)pstCallOrig->stCustomDialPara.ulSo;
    pstCallEntity->ucIsAlertAnsByPass   = VOS_FALSE;


    /* 初始化被叫号码 */
    PS_MEM_CPY(&pstCallEntity->stCalledNumber,
               &pstCallOrig->stCustomDialPara.stDialNumber,
               sizeof(MN_CALL_CALLED_NUM_STRU));

    /* TO DO:设置SDC中CS呼叫标志 */
    /* TAF_SDC_SetCsCallExistFlg(VOS_TRUE); */

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* TO DO:给MTC模块上报当前CS域业务状态 */
    /* TAF_SendMtcCsSrvInfoInd(); */
#endif

    /* 根据当前1X的服务状态判定是否需要发送呼叫请求给XCC,如果当前非正常服务,
       不发给XCC呼叫请求,重拨情况下直接通知XSD进行重拨;否则发给XCC */

    /* 通知MMA CALL NTF */
    TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, pstCallOrig->usClientId, TAF_XCALL_BuildMmaCallType(pstCallOrig->stCustomDialPara.enCallType));

    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == TAF_SDC_GetCsServiceStatus())
    {
        /* 发送呼叫消息给XCC */
        TAF_XCALL_SndXccOrigCallReq(ucCallId);

        /* 启动silent redial定时器 */
        TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD_LEN, ucCallId);
    }
    else
    {


        /* 启动silent redial定时器 */
        TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD_LEN, ucCallId);

        TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN, ucCallId);
    }

    /* 回复呼叫成功 */
    TAF_XCALL_SndCallOrigCnf(TAF_CS_CAUSE_SUCCESS,
                             pstCallOrig->ulSenderPid,
                             pstCallOrig->usClientId,
                             pstCallOrig->stCustomDialPara.enCallType);

    /* 上报呼叫事件 */
    TAF_XCALL_SndCallOrigInd(ucCallId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvAppSendContDTMFReq
 功能描述  : 处理AT模块发来的TAF_CALL_SEND_CONT_DTMF_REQ消息，或向XCC转发，或缓存
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月24日
    作    者   : l00324781
    修改内容   : Iter16 新生成函数
  2.日    期   : 2015年8月18日
    作    者   : l00324781
    修改内容   : DTS2015081708770修改，向xcc发送消息前，
                判断定时器StopAndStartContDtmfInterval是否处于运行态
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppSendContDTMFReq(VOS_VOID *pMsg)
{
    TAF_CALL_CONT_DTMF_REQ_MSG_STRU                        *pstContDTMFReqMsg;
    TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8              enResult;
    MN_CALL_STATE_ENUM_U8                                   enCallState;

    pstContDTMFReqMsg = (TAF_CALL_CONT_DTMF_REQ_MSG_STRU *)pMsg;

    /* 判断该call_id对应的状态是否为ACTIVE,目前只支持在该状态下发送CONT DTMF  */
    enCallState = TAF_XCALL_GetCallState(pstContDTMFReqMsg->stContDTMFPara.ucCallId);
    if (MN_CALL_S_ACTIVE != enCallState)
    {
        TAF_ERROR_LOG2(WUEPS_PID_TAF,"TAF_XCALL_RcvAppSendContDTMFReq: Call State is error. CallID:, State:",
                      pstContDTMFReqMsg->stContDTMFPara.ucCallId, enCallState);

        /* 不是ACTIVE态，向AT返回TAF_CALL_EVT_SEND_CONT_DTMF_CNF */
        TAF_XCALL_SndContDTMFCnf(pstContDTMFReqMsg->usClientId,
                                 pstContDTMFReqMsg->ucOpId,
                                 TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ABNORMAL_STATE,
                                 pstContDTMFReqMsg->stContDTMFPara.ucCallId);
        return;
    }

    /*如果等待XCC回复的Cont DTMF CNF消息的标识为VOS_FALSE，XCALL可以给XCC发送ID_XCALL_XCC_CONT_DTMF_REQ消息
      如果等待XCC回复的Cont DTMF CNF消息的标识为VOS_TRUE,XCALL需要等待发送中的ID_XCALL_XCC_CONT_DTMF_REQ的回复消息，
      同时把最新收到的TAF_CALL_SEND_CONT_DTMF_REQ消息缓存起来
    */
    if (TAF_XCALL_WAIT_NO_XCC_CNF == TAF_XCALL_GetWaitForXCCDTMFCnfFlag(pstContDTMFReqMsg->stContDTMFPara.ucCallId))
    {
        /* 如果此时状态为:收到Start Cont Dtmf Req的响应，但是定时器处于运行态，此时收到消息，应该缓存,
            等待定时器超时，再处理
        */
        if (TAF_XCALL_TIMER_STATUS_RUNING == TAF_XCALL_GetTimerStatus(TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL,
                                                                      pstContDTMFReqMsg->stContDTMFPara.ucCallId))
        {
            enResult = TAF_XCALL_SaveContDtmfInfo(pstContDTMFReqMsg);
        }
        else
        {
            enResult = TAF_XCALL_SndXccContDTMFReq(&pstContDTMFReqMsg->stContDTMFPara);

            /* 向XCC发送ID_XCALL_XCC_SEND_CONT_DTMF_REQ后，设置标识,区分是start还是stop */
            if (TAF_CALL_CONT_DTMF_START == pstContDTMFReqMsg->stContDTMFPara.enSwitch)
            {
                TAF_XCALL_SetWaitForXCCDTMFCnfFlag(pstContDTMFReqMsg->stContDTMFPara.ucCallId, TAF_XCALL_WAIT_XCC_CNF_START_CONT_DTMF);
            }
            else
            {
                TAF_XCALL_SetWaitForXCCDTMFCnfFlag(pstContDTMFReqMsg->stContDTMFPara.ucCallId, TAF_XCALL_WAIT_XCC_CNF_STOP_CONT_DTMF);
            }
        }
    }
    else
    {
        enResult = TAF_XCALL_SaveContDtmfInfo(pstContDTMFReqMsg);
    }

    /* 回复XCALL TAF_CALL_EVT_SEND_CONT_DTMF_CNF (ucResult)*/
    TAF_XCALL_SndContDTMFCnf(pstContDTMFReqMsg->usClientId,
                             pstContDTMFReqMsg->ucOpId,
                             enResult,
                             pstContDTMFReqMsg->stContDTMFPara.ucCallId);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_ReplaceFlashPlusWithDigit
 功能描述  : 将^CFSH命令中号码携带的加号转换为数字
 输入参数  : VOS_UINT8      ucSrcDigitNum ---下发的^CFSH命令中携带的号码个数
             VOS_UINT8     *pucSrcDigit   ---下发的^CFSH命令中携带的号码
 输出参数  : VOS_UINT8      ucDstDigitNum ---转换后的号码个数
             VOS_UINT8     *pucDstDigit   ---转换后的号码
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月23日
    作    者   : y00307564
    修改内容   : 新生成函数

  2.日    期   : 2015年12月31日
    作    者   : h00313353
    修改内容   : DTS2015122804554
*****************************************************************************/
VOS_VOID TAF_XCALL_ReplaceFlashPlusWithDigit(
    VOS_UINT8                           ucSrcDigitNum,
    VOS_UINT8                          *pucSrcDigit,
    VOS_UINT8                          *pucDstDigitNum,
    VOS_UINT8                          *pucDstDigit
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           j;
    MN_CALL_NUM_TYPE_ENUM_U8            enCurNumType;
    VOS_INT32                           lSid;

    if (0 != ucSrcDigitNum)
    {
        /* 若有加号，记录该号码为国际号码，否则为unknown */
        if ('+' == pucSrcDigit[0])
        {
            enCurNumType = (VOS_UINT8)(0x80 | (MN_CALL_TON_INTERNATIONAL << 4) | MN_CALL_NPI_ISDN);

            i = 1;
        }
        else
        {
            enCurNumType = (VOS_UINT8)(0x80 | (MN_CALL_TON_UNKNOWN << 4) | MN_CALL_NPI_ISDN);

            i = 0;
        }

        j = 0;
        for (; i < ucSrcDigitNum; i++)
        {
            pucDstDigit[j] = pucSrcDigit[i];

            j++;
        }

        *pucDstDigitNum = j;

        lSid              = TAF_SDC_GetSdcCtx()->stNetworkInfo.lSid;

        /* 加号转换 */
        TAF_TranslatePlusToNum(lSid, TAF_PLUS_TRANSLATE_DIAL_TYPE_VOICE, &enCurNumType, pucDstDigit, pucDstDigitNum);
    }
    else
    {
        *pucDstDigitNum = 0;
        pucDstDigit[0]  = '\0';
    }
}
/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvAtCclprGetReq
 功能描述  : 处理TAF_CALL_APP_SND_CCLPR_REQ消息,呼叫源号码命令处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月10日
    作    者   : f00279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAtCclprGetReq(VOS_VOID *pstMsg)
{
    TAF_CALL_EVT_CCLPR_GET_CNF_STRU                         stAppCnfMsg;
    TAF_XCALL_CALL_ENTITY_STRU                             *pstXcallEntity = VOS_NULL_PTR;
    TAF_CALL_SND_CCLPR_REQ_MSG_STRU                        *pstCallMsg = VOS_NULL_PTR;

    pstCallMsg = (TAF_CALL_SND_CCLPR_REQ_MSG_STRU *)pstMsg;

    PS_MEM_SET(&stAppCnfMsg, 0x00, sizeof(TAF_CALL_EVT_CCLPR_GET_CNF_STRU));

    pstXcallEntity = TAF_XCALL_GetCallEntityAddr(pstCallMsg->ucCallId);
    if ((VOS_TRUE == pstXcallEntity->ulUsed)
     && (MN_CALL_DIR_MT == pstXcallEntity->enCallDir))

    {
        stAppCnfMsg.enPI = pstXcallEntity->ucPi;
    }
    else
    {
        stAppCnfMsg.enPI = TAF_CALL_PRESENTATION_BUTT;
    }

    stAppCnfMsg.ucCallId        = pstCallMsg->ucCallId;
    stAppCnfMsg.ulRet           = TAF_ERR_NO_ERROR;

    /* 上报TAF_CALL_EVT_CCLPR_SET_CNF */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_CCLPR_SET_CNF,
                           pstCallMsg->usClientId,
                           sizeof(TAF_CALL_EVT_CCLPR_GET_CNF_STRU),
                          &stAppCnfMsg);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_ReportEccNumList
 功能描述  : 向AT上报紧急呼列表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月28日
    作    者   : h00313353
    修改内容   : Ecc List Report
*****************************************************************************/
VOS_VOID TAF_XCALL_ReportEccNumList(VOS_VOID)
{
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo = VOS_NULL_PTR;
    VOS_UINT16                          usLen;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl          = VOS_NULL_PTR;

    pstCurcRptCtrl                  = TAF_SDC_GetCurcRptCtrl();

    /* 判断主动上报是否打开 */
    if (VOS_FALSE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                               TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                               TAF_SDC_RPT_CMD_XLEMA))
    {
        return;
    }

    pstEccNumInfo = (MN_CALL_ECC_NUM_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_CALL_ECC_NUM_INFO_STRU));
    if (VOS_NULL_PTR == pstEccNumInfo)
    {
        MN_WARN_LOG("TAF_XCALL_ReportEccNumList: Alloc Mem Fail.");
        return;
    }

    /* 消息初始化 */
    PS_MEM_SET(pstEccNumInfo, 0x00, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    pstEccNumInfo->enEvent    = MN_CALL_EVT_ECC_NUM_IND;
    pstEccNumInfo->usClientId = MN_GetRealClientId(MN_CLIENT_ALL, WUEPS_PID_TAF);

    /* 获取紧急呼列表 */
    TAF_XCALL_GetEccNumList(pstEccNumInfo);

    usLen = (VOS_UINT16)sizeof(MN_CALL_ECC_NUM_INFO_STRU);

    /*  上报AT */
    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (TAF_UINT8 *)pstEccNumInfo, usLen);

    /* 内存释放 */
    PS_MEM_FREE(WUEPS_PID_TAF,pstEccNumInfo);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_SaveCustomEccNum
 功能描述  : 将APP定制的紧急呼号码保存到全局变量
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月28日
    作    者   : h00313353
    修改内容   : Save Custom Ecc Num

*****************************************************************************/
VOS_VOID TAF_XCALL_SaveCustomEccNum(
    MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU*    pstCustomEccNumReq
)
{
    VOS_UINT8                               ucIndex;
    TAF_SDC_CUSTOM_ECC_NUM_STRU            *pstCustomEccNum            = VOS_NULL_PTR;
    TAF_SDC_CUSTOM_ECC_CTX_STRU            *pstCustomCallEmerNumCtx    = VOS_NULL_PTR;

    pstCustomCallEmerNumCtx = TAF_SDC_GetCustomCallEccNumCtx();

    /* 当前PLMN不存在定制紧急呼号码，清除当前列表 */
    if ((1 == pstCustomEccNumReq->ucIndex)
     && (1 == pstCustomEccNumReq->ucTotal)
     && (MN_CALL_INVALID_CATEGORY == pstCustomEccNumReq->ucCategory))
    {
        PS_MEM_SET(&(pstCustomCallEmerNumCtx->stCustomEccNumList), 0x00, sizeof(TAF_SDC_CUSTOM_ECC_NUM_LIST_STRU));
    }
    else
    {
        /* 保存定制号码到全局变量 */
        ucIndex         = pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount;
        pstCustomEccNum = &(pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[ucIndex]);

        pstCustomEccNum->ucCategory             = pstCustomEccNumReq->ucCategory;
        pstCustomEccNum->ucValidSimPresent      = pstCustomEccNumReq->ucSimPresent;
        pstCustomEccNum->ulMcc                  = pstCustomEccNumReq->ulMcc;
        pstCustomEccNum->ucEccNumLen            = pstCustomEccNumReq->stEccNum.ucNumLen;
        pstCustomEccNum->ucAbnormalServiceFlg   = pstCustomEccNumReq->ucAbnormalServiceFlg;

        PS_MEM_CPY(pstCustomEccNum->aucEccNum,
                   pstCustomEccNumReq->stEccNum.aucBcdNum,
                   pstCustomEccNumReq->stEccNum.ucNumLen);

        (pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount)++;
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvAppEccNumSetReq
 功能描述  : 处理AT模块发来的MN_CALL_APP_CUSTOM_ECC_NUM_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月26日
    作    者   : h00313353
    修改内容   : 紧急呼定制号码请求
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppEccNumSetReq(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT32                              ulRst;
    MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU   stNvimCustomEccNumList;
    VOS_UINT8                               i;
    MN_CALL_CUSTOM_CFG_INFO_STRU           *pstCustomCfg            = VOS_NULL_PTR;
    TAF_SDC_CUSTOM_ECC_NUM_STRU            *pstCustomEccNum         = VOS_NULL_PTR;
    TAF_SDC_CUSTOM_ECC_CTX_STRU            *pstCustomCallEmerNumCtx = VOS_NULL_PTR;
    MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU    *pstCustomEccNumReq      = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU               *pstAppReq               = VOS_NULL_PTR;

    pstAppReq = (MN_CALL_APP_REQ_MSG_STRU *)pMsg;
    pstCustomEccNumReq      = (MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU *)&(pstAppReq->unParm.stEccNumReq);
    pstCustomCallEmerNumCtx = TAF_SDC_GetCustomCallEccNumCtx();

    pstCustomCfg      = MN_CALL_GetCustomCfgInfo();

    /* 如果index为1,清空定制列表, 标记定制开始 */
    if (1 == pstCustomEccNumReq->ucIndex)
    {
        PS_MEM_SET(&(pstCustomCallEmerNumCtx->stCustomEccNumList), 0x00, sizeof(TAF_SDC_CUSTOM_ECC_NUM_LIST_STRU));

        pstCustomCallEmerNumCtx->ucCustomSetFlg = VOS_TRUE;
    }

    /* 当前不在定制过程 */
    if (VOS_FALSE == pstCustomCallEmerNumCtx->ucCustomSetFlg)
    {
        /* 丢弃不保存 */
        return;
    }

    /* 保存定制号码到全局变量 */
    TAF_XCALL_SaveCustomEccNum(pstCustomEccNumReq);

    /* 当INDEX = TOTAL或者定制号码条数达到最大认为本次定制结束 */
    if ((pstCustomEccNumReq->ucIndex == pstCustomEccNumReq->ucTotal)
     || (TAF_SDC_MAX_CUSTOM_ECC_NUM == pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount))
    {
        PS_MEM_SET(&stNvimCustomEccNumList, 0, sizeof(MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU));

        stNvimCustomEccNumList.ucEccNumCount = pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount;

        for (i = 0; i < pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount; i++)
        {
            pstCustomEccNum = &(pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i]);

            stNvimCustomEccNumList.astCustomEccNumList[i].ucCategory
                = pstCustomEccNum->ucCategory;
            stNvimCustomEccNumList.astCustomEccNumList[i].ulMcc
                = pstCustomEccNum->ulMcc;
            stNvimCustomEccNumList.astCustomEccNumList[i].ucValidSimPresent
                = pstCustomEccNum->ucValidSimPresent;
            stNvimCustomEccNumList.astCustomEccNumList[i].ucAbnormalServiceFlg
                = pstCustomEccNum->ucAbnormalServiceFlg;
            stNvimCustomEccNumList.astCustomEccNumList[i].ucEccNumLen
                = pstCustomEccNum->ucEccNumLen;

            PS_MEM_CPY(stNvimCustomEccNumList.astCustomEccNumList[i].aucEccNum,
                       pstCustomEccNum->aucEccNum,
                       pstCustomEccNum->ucEccNumLen);
        }

        /* 标记定制结束 */
        pstCustomCallEmerNumCtx->ucCustomSetFlg = VOS_FALSE;

        /* 将全局变量保存的列表写入NV */
        ulRst = NV_Write(en_NV_Item_CUSTOM_ECC_NUM_LIST,(VOS_VOID *)&stNvimCustomEccNumList, sizeof(MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU));
        if (NV_OK != ulRst)
        {
            MN_ERR_LOG("TAF_XCALL_RcvAppEccNumSetReq:Write NVIM Error");
        }

        /* 紧急呼上报控制NV开关打开 */
        if (VOS_TRUE == pstCustomCfg->ucReportEccNumFlg)
        {
            /* 向AT上报当前所有的紧急呼号码 */
            TAF_XCALL_ReportEccNumList();
        }
    }

    return;
}

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvAppEncryptVoiceReq
 功能描述  : 收到用户的密话请求消息
 输入参数  : pstMsg -- 密话请求消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppEncryptVoiceReq(VOS_VOID *pstMsg)
{
    TAF_XCALL_ProcEccEvent(TAF_XCALL_APP_MSG_EVENT_ENC_VOICE_REQ,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           pstMsg,
                           VOS_NULL_PTR);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvAppRemoteCtrlAnswerReq
 功能描述  : 收到用户下发的自动密话请求应答请求
 输入参数  : pstMsg -- 密话请求应答请求消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppRemoteCtrlAnswerReq(VOS_VOID *pstMsg)
{
    TAF_XCALL_ProcEccEvent(TAF_XCALL_APP_MSG_EVENT_REMOTE_CTRL_ANSWER_REQ,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_REMOTE_CTRL,
                           pstMsg,
                           VOS_NULL_PTR);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvAppEccSrvCapCfgReq
 功能描述  : 收到用户下发ECC服务能力配置请求
 输入参数  : pstMsg -- ECC服务能力配置请求消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : l00359089
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppEccSrvCapCfgReq(VOS_VOID *pstMsg)
{
    TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU                  *pstAppSetEccSrvCap = VOS_NULL_PTR;
    TAF_XCALL_ECC_SRV_CAP_INFO_STRU                        *pstEccSrvCap       = VOS_NULL_PTR;
    TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT32                    enEccSrvCap;

    enEccSrvCap                                             = TAF_CALL_APP_ECC_SRV_CAP_DISABLE;
    pstAppSetEccSrvCap                                      = (TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU*)pstMsg;
    pstEccSrvCap                                            = TAF_XCALL_GetVoiceEncryptCapCfgPara();

    if (VOS_TRUE == pstEccSrvCap->ucEccSrvCap)
    {
        enEccSrvCap = TAF_CALL_APP_ECC_SRV_CAP_ENABLE;
    }

    /*更新上下文*/
    if (TAF_CALL_APP_ECC_SRV_CAP_DISABLE == pstAppSetEccSrvCap->enEccSrvCap)
    {
        pstEccSrvCap->ucEccSrvCap                           = VOS_FALSE;
        enEccSrvCap                                         = TAF_CALL_APP_ECC_SRV_CAP_DISABLE;
    }

    if (TAF_CALL_APP_ECC_SRV_CAP_ENABLE == pstAppSetEccSrvCap->enEccSrvCap)
    {
        pstEccSrvCap->ucEccSrvCap                           = VOS_TRUE;
        enEccSrvCap                                         = TAF_CALL_APP_ECC_SRV_CAP_ENABLE;
    }

    if (TAF_CALL_APP_ECC_SRV_STATUS_CLOSE == pstAppSetEccSrvCap->enEccSrvStatus)
    {
        pstEccSrvCap->ucEccSrvStatus                        = VOS_FALSE;
    }

    if (TAF_CALL_APP_ECC_SRV_STATUS_OPEN == pstAppSetEccSrvCap->enEccSrvStatus)
    {
        pstEccSrvCap->ucEccSrvStatus                        = VOS_TRUE;
    }

    /*更新NV*/
    TAF_XCALL_WriteVoiceEncryptCapCfgPara(enEccSrvCap, pstAppSetEccSrvCap->enEccSrvStatus);

    /*回复APP配置结果*/
    TAF_XCALL_SndAppEccSrvCapCfgCnf(&pstAppSetEccSrvCap->stCtrl, TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_SUCC);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvAppEccSrvCapQryReq
 功能描述  : 收到用户下发ECC服务能力查询请求
 输入参数  : pstMsg -- ECC服务能力查询请求消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : l00359089
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppEccSrvCapQryReq(VOS_VOID *pstMsg)
{
    TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU                  *pstAppGetEccSrvCap = VOS_NULL_PTR;
    TAF_XCALL_ECC_SRV_CAP_INFO_STRU                        *pstEccSrvCap       = VOS_NULL_PTR;
    TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT32                    enEccSrvCap;
    TAF_CALL_APP_ECC_SRV_STATUS_ENUM_UINT32                 enEccSrvStatus;

    enEccSrvCap                                             = TAF_CALL_APP_ECC_SRV_CAP_DISABLE;
    enEccSrvStatus                                          = TAF_CALL_APP_ECC_SRV_STATUS_CLOSE;
    pstAppGetEccSrvCap                                      = (TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU*)pstMsg;
    pstEccSrvCap                                            = TAF_XCALL_GetVoiceEncryptCapCfgPara();

    if (VOS_TRUE == pstEccSrvCap->ucEccSrvCap)
    {
        enEccSrvCap                                         = TAF_CALL_APP_ECC_SRV_CAP_ENABLE;
    }

    if (VOS_TRUE == pstEccSrvCap->ucEccSrvStatus)
    {
        enEccSrvStatus                                      = TAF_CALL_APP_ECC_SRV_STATUS_OPEN;
    }

    TAF_XCALL_SndAppEccSrvCapQryCnf(&pstAppGetEccSrvCap->stCtrl,
                                    enEccSrvCap,
                                    enEccSrvStatus);

}
#endif

/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvAppPrivacyModeSetReq
 功能描述  : 处理用户下发的privacy mode请求设置
 输入参数  : pstMsg -- privacy mode请求设置
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppPrivacyModeSetReq(VOS_VOID *pstMsg)
{
    TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU                 *pstPrivacyModeReq = VOS_NULL_PTR;
    XCALL_XCC_PRIVACY_MODE_ENUM_UINT8                       enPrivacyMode;

    pstPrivacyModeReq = (TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU *)pstMsg;

    enPrivacyMode     = (XCALL_XCC_PRIVACY_MODE_ENUM_UINT8)pstPrivacyModeReq->enPrivacyMode;

    TAF_XCALL_SendPrivacyModeSetReq(enPrivacyMode,
                                    pstPrivacyModeReq->stCtrl.ulModuleId,
                                    pstPrivacyModeReq->stCtrl.usClientId,
                                    pstPrivacyModeReq->stCtrl.ucOpId);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvAppPrivacyModeQryReq
 功能描述  : 处理用户下发的privacy mode查询设置
 输入参数  : pstMsg -- privacy mode查询设置
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppPrivacyModeQryReq(VOS_VOID *pstMsg)
{
    TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU                 *pstPrivacyModeQryReq = VOS_NULL_PTR;

    pstPrivacyModeQryReq = (TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU *)pstMsg;

    TAF_XCALL_SendPrivacyModeQryReq(pstPrivacyModeQryReq->stCtrl.ulModuleId,
                                    pstPrivacyModeQryReq->stCtrl.usClientId,
                                    pstPrivacyModeQryReq->stCtrl.ucOpId);
}
/*lint -restore*/

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





