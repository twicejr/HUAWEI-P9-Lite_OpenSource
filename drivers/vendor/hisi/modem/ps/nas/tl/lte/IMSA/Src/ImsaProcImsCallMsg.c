/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaProcImsCallMsg.c
  Description     : 该C文件实现IMS呼叫消息处理和IMS呼叫消息发送
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaProcImsCallMsg.h"
#include "ImsaEntity.h"
#include "ImsaImsEvent.h"
#include "ImsaImsApi.h"
#include "ImsaEntity.h"
#include "ImsaCallManagement.h"
#include "ImsaPublic.h"
#include "ImsaRegManagement.h"
#include "ImsaImsInterface.h"
#include "CallImsaInterface.h"
#include "MnClient.h"
#include "ImsaProcSpmMsg.h"
#include "ImsaProcAtMsg.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_IMSAPROCIMSCALLMSG_C
#define    THIS_NAS_FILE_ID    NAS_FILE_ID_IMSAPROCIMSCALLMSG_C
/*lint +e767*/

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#if (FEATURE_ON == FEATURE_IMS)

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

VOS_UINT32 IMSA_CallProcImsStateActive(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary);
VOS_UINT32 IMSA_CallProcImsStateHeld(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary);
VOS_UINT32 IMSA_CallProcImsStateTrying(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary);
VOS_UINT32 IMSA_CallProcImsStateDialing(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary);
VOS_UINT32 IMSA_CallProcImsStateAlerting(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary);
VOS_UINT32 IMSA_CallProcImsStateIncoming(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary);
VOS_UINT32 IMSA_CallProcImsStateWaiting(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary);
VOS_UINT32 IMSA_CallProcImsStateInitializing(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary);

VOS_UINT32 IMSA_CallProcImsState(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary);
CALL_IMSA_SRVCC_CALL_STATE_ENUM_UINT8 IMSA_CallImsSrvccState2TafCallState(IMSA_IMS_CALL_STATE_ENUM_UINT8  enCallState);

extern VOS_VOID IMSA_CallEntityUpdateByCallSummary
(
    IMSA_CALL_ENTITY_STRU *pstCallEntity,
    const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary
);
extern VOS_VOID  IMSA_CallRcvImsStartDtmfOk( VOS_VOID );
extern VOS_VOID  IMSA_CallRcvImsStopDtmfOk( VOS_VOID );
extern VOS_UINT32 IMSA_CallProcImsMsgOk(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent);
extern VOS_VOID IMSA_CallEntitySaveErrorInfo
(
    IMSA_CALL_ENTITY_STRU                  *pstCallEntity,
    const IMSA_IMS_OUTPUT_CALL_EVENT_STRU  *pstOutputCallEvent
);
extern VOS_VOID  IMSA_CallRcvImsStartDtmfError( VOS_VOID );
extern VOS_UINT32 IMSA_CallProcImsMsgError(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent);
extern VOS_UINT32 IMSA_CallProcImsMsgIncoming(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent);
extern VOS_UINT32 IMSA_CallEntityProcErrorInfo380ForNormal
(
    IMSA_CALL_ENTITY_STRU *pstCallEntity,
    const IMSA_IMS_CALL_ERROR_STRU *pstImsError
);
extern VOS_UINT32 IMSA_CallEntityProcErrorInfo380ForEmc
(
    IMSA_CALL_ENTITY_STRU        *pstCallEntity,
    const IMSA_IMS_CALL_ERROR_STRU     *pstImsError
);
extern VOS_UINT32 IMSA_CallEntityProcErrorInfo380
(
    IMSA_CALL_ENTITY_STRU *pstCallEntity,
    const IMSA_IMS_CALL_ERROR_STRU *pstImsError
);
extern VOS_UINT32 IMSA_CallEntityProcErrorInfo503
(
    IMSA_CALL_ENTITY_STRU *pstCallEntity,
    const IMSA_IMS_CALL_ERROR_STRU *pstImsError
);
extern VOS_UINT32 IMSA_CallEntityProcErrorInfo504
(
    IMSA_CALL_ENTITY_STRU *pstCallEntity,
    const IMSA_IMS_CALL_ERROR_STRU *pstImsError
);
extern VOS_UINT32 IMSA_CallEntityProcErrorInfo
(
    IMSA_CALL_ENTITY_STRU *pstCallEntity,
    const IMSA_IMS_CALL_ERROR_STRU *pstImsError
);
/*extern TAF_CS_CAUSE_ENUM_UINT32 IMSA_CallTransImsErr2SpmErr
(
    VOS_UINT16                          usImsErr
);
extern VOS_VOID IMSA_CallReleaseCallCommonProc
(
    IMSA_CALL_ENTITY_STRU              *pstCallEntity,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
);*/
extern VOS_UINT32 IMSA_CallProcImsMsgDisconnect(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent);
extern VOS_UINT32 IMSA_CallProcImsMsgWaiting(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent);
extern VOS_UINT32 IMSA_CallProcImsMsgCallEarlyMedia(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent);
extern VOS_UINT32 IMSA_CallProcImsMsgInitializing(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent);
extern VOS_UINT32 IMSA_CallProcImsMsgSrvccCallList(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent);
extern VOS_UINT32 IMSA_CallProcImsMsgEmergencyInd(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent);
extern VOS_UINT32 IMSA_CallIsProccessCallSwap(VOS_VOID);
extern VOS_UINT32 IMSA_CallIsAllCallOnHold(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent);
extern VOS_UINT32 IMSA_CallIsAllCallInConference(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent);
extern VOS_UINT32 IMSA_CallProcImsMsgCallList(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent);
extern VOS_UINT32 IMSA_CallProcImsStateInvalid
(
    IMSA_CALL_ENTITY_STRU *pstCallEntity,
    const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary
);
extern IMSA_CALL_STATUS_ENUM_UINT8 IMSA_CallImsState2ImsaState
(
    IMSA_IMS_CALL_STATE_ENUM_UINT8 enImsState,
    IMSA_CALL_STATUS_ENUM_UINT8 enOldState
);
extern VOS_UINT32 IMSA_CallAllStateWillBeHeld(VOS_UINT32 ulWillChangedId);

extern VOS_UINT32 IMSA_CallProcImsMsgEconfNotifyInd(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent);
extern VOS_UINT32 IMSA_CallProcImsMsgMtBegin(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent);


IMSA_IMS_CALL_MSG_ACT_STRU g_stImsaImsCallMsgActTbl[] =
{
    {IMSA_IMS_OUTPUT_CALL_REASON_OK,                    IMSA_CallProcImsMsgOk},
    {IMSA_IMS_OUTPUT_CALL_REASON_ERROR,                 IMSA_CallProcImsMsgError},
    {IMSA_IMS_OUTPUT_CALL_REASON_CALL_LIST,             IMSA_CallProcImsMsgCallList},
    {IMSA_IMS_OUTPUT_CALL_REASON_DISCONNECT_EVENT,      IMSA_CallProcImsMsgDisconnect},
    {IMSA_IMS_OUTPUT_CALL_REASON_INCOMING_EVENT,        IMSA_CallProcImsMsgIncoming},
    {IMSA_IMS_OUTPUT_CALL_REASON_WAITING_EVENT,         IMSA_CallProcImsMsgWaiting},
    {IMSA_IMS_OUTPUT_CALL_REASON_INITIALIZING_EVENT,    IMSA_CallProcImsMsgInitializing},
    {IMSA_IMS_OUTPUT_CALL_REASON_SRVCC_CALL_LIST,       IMSA_CallProcImsMsgSrvccCallList},
    {IMSA_IMS_OUTPUT_CALL_REASON_EMERGENCY_INDICATION,  IMSA_CallProcImsMsgEmergencyInd},
    {IMSA_IMS_OUTPUT_CALL_REASON_MODIFY_IND,            IMSA_CallProcImsMsgModifyStatusInd},
    {IMSA_IMS_OUTPUT_CALL_REASON_MODIFY_BEGIN,          IMSA_CallProcImsMsgModifyStatusBegin},
    {IMSA_IMS_OUTPUT_CALL_REASON_MODIFY_END,            IMSA_CallProcImsMsgModifyStatusEnd},
    {IMSA_IMS_OUTPUT_CALL_REASON_ECONF_NOTIFY_IND,      IMSA_CallProcImsMsgEconfNotifyInd},
    {IMSA_IMS_OUTPUT_CALL_REASON_MT_BEGIN,              IMSA_CallProcImsMsgMtBegin}

};
VOS_UINT32        g_ulImsaImsCallMsgActTblLen = sizeof(g_stImsaImsCallMsgActTbl)
                                                / sizeof(IMSA_IMS_CALL_MSG_ACT_STRU);

/*****************************************************************************
  3 Function
*****************************************************************************/

/*lint -e961*/
/*****************************************************************************
 Function Name  : IMSA_CallEntityUpdateByCallSummary
 Description    : 根据D2 IMS上报的呼叫信息更新IMSA内部的呼叫实体
 Input          : pstCallEntity         呼叫实体指针
                  pstCallSummary        D2上报的呼叫信息
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallEntityUpdateByCallSummary(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary)
{

    /* 更新呼叫Id */
    pstCallEntity->ucImscallId = (VOS_UINT8)pstCallSummary->ulCallIndex;

    /* 更新呼叫方向 */
    if (IMSA_IMS_CALL_DIR_MOBILE_ORIGINATED == pstCallSummary->enCallDirection)
    {
        pstCallEntity->enDir = MN_CALL_DIR_MO;
    }
    else
    {
        pstCallEntity->enDir = MN_CALL_DIR_MT;
    }

    /* 更新呼叫类型 */
    pstCallEntity->enType = (IMSA_CALL_TYPE_ENUM_UINT8)pstCallSummary->enCallMode;

    /* 更新呼叫方式 */
    /**
     * 呼叫模式使用ORIG REQ命令参数的数值，
     * 这里不进行更新
     */

    /* 更新多方呼叫标识 */
    if (IMSA_IMS_CALL_SINGLE_PARTY == pstCallSummary->enMultiParty)
    {
        pstCallEntity->enMpty = MN_CALL_NOT_IN_MPTY;
    }
    else if (IMSA_IMS_CALL_CONFERENCE == pstCallSummary->enMultiParty)
    {
        pstCallEntity->enMpty = MN_CALL_IN_MPTY;
        pstCallEntity->ucIsEconfFlag = IMSA_FALSE;
    }
    else
    {
        pstCallEntity->enMpty = MN_CALL_IN_MPTY;
        /* 更新增强多方通话的标识 */
        pstCallEntity->ucIsEconfFlag = IMSA_TRUE;
    }

    /* 更新主叫号码或者被叫号码 */
    if (IMSA_IMS_CALL_DIR_MOBILE_ORIGINATED == pstCallSummary->enCallDirection)
    {
        IMSA_CallEntityUpdateCalledNumberByAscii((VOS_CHAR *)pstCallSummary->acNumber, &pstCallEntity->stCalledNumber);
        IMSA_CallEntityUpdateCallNumberByAscii((VOS_CHAR *)pstCallSummary->acConnectNumber, &pstCallEntity->stConnectNumber);
    }
    else
    {
        IMSA_CallEntityUpdateCallNumberByAscii((VOS_CHAR *)pstCallSummary->acNumber, &pstCallEntity->stCallNumber);

        if (IMSA_IMS_CALL_STATE_INCOMING == pstCallSummary->enCallState)
        {
            /* 只有在INCOMMING状态下，才更新呼叫转移号码，其他状态下，该号码不会变更，没有必要更新 */
            IMSA_CallEntityUpdateCallNumberByAscii((VOS_CHAR *)pstCallSummary->acRedirectNumber, &pstCallEntity->stRedirectNumber);
        }
    }
}

/*****************************************************************************
 Function Name  : IMSA_CallDtmfInfoInit
 Description    : 初始化DTMF信息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310     2013-12-06  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallDtmfInfoInit(VOS_VOID)
{
    VOS_UINT8                          ucIndex = 0;

    for(ucIndex = 0; ucIndex < IMSA_CALL_DTMF_BUF_MAX_NUM; ucIndex++)
    {
        IMSA_MEM_SET_S( &IMSA_CallGetDtmfBufList(ucIndex),
                        sizeof(IMSA_CALL_DTMF_INFO_STRU),
                        0,
                        sizeof(IMSA_CALL_DTMF_INFO_STRU));
    }

    IMSA_MEM_SET_S( IMSA_CallGetCurrentDtmfInfo(),
                    sizeof(IMSA_CALL_DTMF_INFO_STRU),
                    0,
                    sizeof(IMSA_CALL_DTMF_INFO_STRU));

    IMSA_CallSetDtmfState(IMSA_CALL_DTMF_IDLE);

    IMSA_CallGetDtmfCnt() = 0;

    return;

}


/*****************************************************************************
 Function Name  : IMSA_CallSaveDtmfInfo
 Description    : 缓存DTMF信息
 Input          : ucCallId---------------------CALL ID
                  cKey-------------------------字符
                  usDuration-------------------持续时长
                  usClientId-------------------CLIENT ID
                  ucSpmOpid--------------------SPM OPID
 Output         : VOS_VOID
 Return Value   : TAF_CS_CAUSE_ENUM_UINT32

 History        :
      1.xiongxianghui 253310      2013-12-05  Draft Enact
*****************************************************************************/
TAF_CS_CAUSE_ENUM_UINT32 IMSA_CallSaveDtmfInfo(VOS_UINT8 ucCallId,
                                                      VOS_CHAR  cKey,
                                                      VOS_UINT16 usDuration,
                                                      VOS_UINT16 usClientId,
                                                      VOS_UINT8  ucSpmOpid)
{
    IMSA_CALL_DTMF_INFO_STRU stDtmfInfo;

    IMSA_MEM_SET_S( &stDtmfInfo,
                    sizeof(IMSA_CALL_DTMF_INFO_STRU),
                    0,
                    sizeof(IMSA_CALL_DTMF_INFO_STRU));

    /* 判断缓存是否已经满了 */
    if(IMSA_CallGetDtmfCnt() >= IMSA_CALL_DTMF_BUF_MAX_NUM)
    {
        return TAF_CS_CAUSE_DTMF_BUF_FULL;
    }

    /* 判断是否连续缓存两个STOP DTMF请求*/
    if((0 == usDuration) && (IMSA_CallGetDtmfCnt() >= 1))
    {
        if(0 == IMSA_CallGetDtmfBufList(IMSA_CallGetDtmfCnt() - 1).usOnLength)
        {
            return TAF_CS_CAUSE_DTMF_REPEAT_STOP;
        }
    }

    /* 缓存成功 */
    stDtmfInfo.ucCallId = ucCallId;
    stDtmfInfo.cKey = cKey;
    stDtmfInfo.usOnLength = usDuration;
    stDtmfInfo.usClientId = usClientId;
    stDtmfInfo.ucSpmOpId = ucSpmOpid;

    IMSA_MEM_CPY_S( &IMSA_CallGetDtmfBufList(IMSA_CallGetDtmfCnt()),
                    sizeof(IMSA_CALL_DTMF_INFO_STRU),
                    &stDtmfInfo,
                    sizeof(IMSA_CALL_DTMF_INFO_STRU));
    IMSA_CallGetDtmfCnt()++;

    return TAF_CS_CAUSE_SUCCESS;
}


/*****************************************************************************
 Function Name  : IMSA_CallDeleteSavedDtmfInfo
 Description    : 删除缓存中ucIndex标识的DTMF信息
 Input          : ucIndex 数组下标
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310     2013-12-06  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallDeleteSavedDtmfInfo(VOS_UINT8 ucIndex)
{
    VOS_UINT8 i = 0;

    if(ucIndex >= IMSA_CallGetDtmfCnt())
    {
        return;
    }
    for(i = 0; i < ((IMSA_CallGetDtmfCnt() - ucIndex) - 1); i++)
    {
        IMSA_MEM_CPY_S( &IMSA_CallGetDtmfBufList(ucIndex + i),
                        sizeof(IMSA_CALL_DTMF_INFO_STRU),
                        &IMSA_CallGetDtmfBufList(ucIndex + i + 1),
                        sizeof(IMSA_CALL_DTMF_INFO_STRU));
    }

    IMSA_MEM_SET_S( &IMSA_CallGetDtmfBufList(IMSA_CallGetDtmfCnt() - 1),
                    sizeof(IMSA_CALL_DTMF_INFO_STRU),
                    0,
                    sizeof(IMSA_CALL_DTMF_INFO_STRU));

    IMSA_CallGetDtmfCnt()--;

    return;
}

/*****************************************************************************
 Function Name  : IMSA_CallClearDtmfInfo
 Description    : 清除DTMF信息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310     2013-12-06  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallClearDtmfInfo(TAF_CS_CAUSE_ENUM_UINT32 enCause)
{
    IMSA_CALL_MANAGER_STRU            *pstCallCtx  = IMSA_CallCtxGet();
    VOS_UINT8                          ucIndex = 0;

    IMSA_INFO_LOG("IMSA_CallClearDtmfInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallClearDtmfInfo_ENUM, LNAS_ENTRY);

    /* 清除缓存的DTMF信息 */
    for(ucIndex = 0; ucIndex < IMSA_CallGetDtmfCnt(); ucIndex++)
    {
        if(0 == IMSA_CallGetDtmfBufList(ucIndex).usOnLength)
        {
            (VOS_VOID)IMSA_CallSendSpmStopDtmfRsltMsg(IMSA_CallGetDtmfBufList(ucIndex).usClientId,
                                                      IMSA_CallGetDtmfBufList(ucIndex).ucSpmOpId,
                                                      IMSA_CallGetDtmfBufList(ucIndex).ucCallId,
                                                      enCause);
        }
        else
        {
            (VOS_VOID)IMSA_CallSendSpmStartDtmfRsltMsg(IMSA_CallGetDtmfBufList(ucIndex).usClientId,
                                                       IMSA_CallGetDtmfBufList(ucIndex).ucSpmOpId,
                                                       IMSA_CallGetDtmfBufList(ucIndex).ucCallId,
                                                       enCause);
        }

        IMSA_MEM_SET_S( &IMSA_CallGetDtmfBufList(ucIndex),
                        sizeof(IMSA_CALL_DTMF_INFO_STRU),
                        0,
                        sizeof(IMSA_CALL_DTMF_INFO_STRU));
    }

    /* 清除当前的DTMF信息 */
    switch(IMSA_CallGetDtmfState())
    {
    case IMSA_CALL_DTMF_WAIT_START_CNF:
        IMSA_StopTimer(&pstCallCtx->stDtmfCtx.stDtmfProtectTimer);
        (VOS_VOID)IMSA_CallSendSpmStartDtmfRsltMsg(IMSA_CallGetCurrentDtmfInfo()->usClientId,
                                                   IMSA_CallGetCurrentDtmfInfo()->ucSpmOpId,
                                                   IMSA_CallGetCurrentDtmfInfo()->ucCallId,
                                                   enCause);
        break;
    case IMSA_CALL_DTMF_WAIT_STOP_CNF:
        IMSA_StopTimer(&pstCallCtx->stDtmfCtx.stDtmfProtectTimer);
        (VOS_VOID)IMSA_CallSendSpmStopDtmfRsltMsg(IMSA_CallGetCurrentDtmfInfo()->usClientId,
                                                  IMSA_CallGetCurrentDtmfInfo()->ucSpmOpId,
                                                  IMSA_CallGetCurrentDtmfInfo()->ucCallId,
                                                  enCause);
        break;
    case IMSA_CALL_DTMF_WAIT_AUTO_STOP_CNF:
        IMSA_StopTimer(&pstCallCtx->stDtmfCtx.stDtmfProtectTimer);
        break;
    case IMSA_CALL_DTMF_WAIT_TIME_OUT:
        IMSA_StopTimer(&pstCallCtx->stDtmfCtx.stDtmfDurationTimer);
        break;
    default:
        IMSA_INFO_LOG("IMSA_CallClearDtmfInfo: nothing process on this state");
        TLPS_PRINT2LAYER_INFO(IMSA_CallClearDtmfInfo_ENUM, 1);
        break;
    }

    IMSA_MEM_SET_S( IMSA_CallGetCurrentDtmfInfo(),
                    sizeof(IMSA_CALL_DTMF_INFO_STRU),
                    0,
                    sizeof(IMSA_CALL_DTMF_INFO_STRU));

    IMSA_CallSetDtmfState(IMSA_CALL_DTMF_IDLE);

    IMSA_CallGetDtmfCnt() = 0;

    return;
}

/*****************************************************************************
 Function Name  : IMSA_CallSrvccSuccClearDtmfInfo
 Description    : SRVCC成功时清除DTMF信息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010     2014-01-04  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallSrvccSuccClearDtmfInfo(TAF_CS_CAUSE_ENUM_UINT32 enCause)
{
    IMSA_CALL_MANAGER_STRU            *pstCallCtx  = IMSA_CallCtxGet();
    VOS_UINT8                          ucIndex = 0;

    IMSA_INFO_LOG("IMSA_CallSrvccSuccClearDtmfInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSrvccSuccClearDtmfInfo_ENUM, LNAS_ENTRY);

    /* 清除缓存的DTMF信息，不用回复结果，SRVCC成功后在CS域继续处理 */
    for(ucIndex = 0; ucIndex < IMSA_CallGetDtmfCnt(); ucIndex++)
    {
        IMSA_MEM_SET_S( &IMSA_CallGetDtmfBufList(ucIndex),
                        sizeof(IMSA_CALL_DTMF_INFO_STRU),
                        0,
                        sizeof(IMSA_CALL_DTMF_INFO_STRU));
    }

    /* 清除当前的DTMF信息 */
    switch(IMSA_CallGetDtmfState())
    {
    case IMSA_CALL_DTMF_WAIT_START_CNF:
        IMSA_StopTimer(&pstCallCtx->stDtmfCtx.stDtmfProtectTimer);
        (VOS_VOID)IMSA_CallSendSpmStartDtmfRsltMsg(IMSA_CallGetCurrentDtmfInfo()->usClientId,
                                                   IMSA_CallGetCurrentDtmfInfo()->ucSpmOpId,
                                                   IMSA_CallGetCurrentDtmfInfo()->ucCallId,
                                                   enCause);
        break;
    case IMSA_CALL_DTMF_WAIT_STOP_CNF:
        IMSA_StopTimer(&pstCallCtx->stDtmfCtx.stDtmfProtectTimer);
        (VOS_VOID)IMSA_CallSendSpmStopDtmfRsltMsg(IMSA_CallGetCurrentDtmfInfo()->usClientId,
                                                  IMSA_CallGetCurrentDtmfInfo()->ucSpmOpId,
                                                  IMSA_CallGetCurrentDtmfInfo()->ucCallId,
                                                  enCause);
        break;
    case IMSA_CALL_DTMF_WAIT_AUTO_STOP_CNF:
        IMSA_StopTimer(&pstCallCtx->stDtmfCtx.stDtmfProtectTimer);
        break;
    case IMSA_CALL_DTMF_WAIT_TIME_OUT:
        IMSA_StopTimer(&pstCallCtx->stDtmfCtx.stDtmfDurationTimer);
        break;
    default:
        IMSA_INFO_LOG("IMSA_CallSrvccSuccClearDtmfInfo: nothing process on this state");
        TLPS_PRINT2LAYER_INFO(IMSA_CallSrvccSuccClearDtmfInfo_ENUM, 1);
        break;
    }

    IMSA_MEM_SET_S(IMSA_CallGetCurrentDtmfInfo(), sizeof(IMSA_CALL_DTMF_INFO_STRU), 0, sizeof(IMSA_CALL_DTMF_INFO_STRU));

    IMSA_CallSetDtmfState(IMSA_CALL_DTMF_IDLE);

    IMSA_CallGetDtmfCnt() = 0;

    return;
}



/*****************************************************************************
 Function Name  : IMSA_CallRcvImsStartDtmfOk
 Description    : start dtmf成功消息处理
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.lihong 0015001     2013-10-14  Draft Enact
*****************************************************************************/
VOS_VOID  IMSA_CallRcvImsStartDtmfOk( VOS_VOID )
{
    IMSA_CALL_DTMF_INFO_STRU           *pstDtmfCurInfo  = VOS_NULL_PTR;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();

    VOS_UINT32                          ulResult = VOS_FALSE;

    /* 判断状态是否异常 */
    if (IMSA_CallGetDtmfState() != IMSA_CALL_DTMF_WAIT_START_CNF)
    {
        IMSA_WARN_LOG("IMSA_CallRcvImsStartDtmfOk: Dtmf State Error!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CallRcvImsStartDtmfOk_ENUM, IMSA_STATE_ERROR);
        return;
    }

    /* 停止DTMF保护定时器 */
    IMSA_StopTimer(&pstCallCtx->stDtmfCtx.stDtmfProtectTimer);

    /* 回复DTMF正式响应事件 */
    pstDtmfCurInfo  = IMSA_CallGetCurrentDtmfInfo();
    (VOS_VOID)IMSA_CallSendSpmStartDtmfRsltMsg( pstDtmfCurInfo->usClientId,
                                                pstDtmfCurInfo->ucSpmOpId,
                                                pstDtmfCurInfo->ucCallId,
                                                TAF_CS_CAUSE_SUCCESS);

    /* 如果有缓存且为STOP_DTMF请求，则直接发送 */
    if(IMSA_CallGetDtmfCnt() > 0)
    {
        /* 判断是否有合适的CALL来传输DTMF音 */
        ulResult = IMSA_CallCheckUserDtmfCallId(0);
        if(TAF_CS_CAUSE_SUCCESS != ulResult)
        {
            IMSA_WARN_LOG("IMSA_CallRcvImsStartDtmfOk: Call Check User Dtmf Fail!");
            TLPS_PRINT2LAYER_WARNING(IMSA_CallRcvImsStartDtmfOk_ENUM, LNAS_FAIL);

            IMSA_CallClearDtmfInfo(TAF_CS_CAUSE_UNKNOWN);
            return;
        }

        if(0 == IMSA_CallGetDtmfBufList(0).usOnLength)
        {
            /* 给IMS发送STOP DTMF */
            if (VOS_TRUE != IMSA_CallSendImsMsgStopDtmf(0, IMSA_CallGetDtmfBufList(0).cKey))
            {
                IMSA_WARN_LOG("IMSA_CallRcvImsStartDtmfOk: Send Stop Dtmf Fail!");
                TLPS_PRINT2LAYER_WARNING(IMSA_CallRcvImsStartDtmfOk_ENUM, 2);

                IMSA_CallClearDtmfInfo(TAF_CS_CAUSE_UNKNOWN);
                return;
            }

            /* 发送成功，启动保护定时器，更新状态*/
            IMSA_StartTimer(&pstCallCtx->stDtmfCtx.stDtmfProtectTimer);
            IMSA_CallSetDtmfState(IMSA_CALL_DTMF_WAIT_STOP_CNF);
            IMSA_MEM_CPY_S( IMSA_CallGetCurrentDtmfInfo(),
                            sizeof(IMSA_CALL_DTMF_INFO_STRU),
                            &IMSA_CallGetDtmfBufList(0),
                            sizeof(IMSA_CALL_DTMF_INFO_STRU));
            IMSA_CallGetCurrentDtmfInfo()->ulImsOpid = IMSA_GetImsOpId();

            /* 删除这条STOP DTMF缓存*/
            IMSA_CallDeleteSavedDtmfInfo(0);
            return;
        }
    }

    /* 没有缓存，或缓存为START_DTMF请求，则启动dtmf duration定时器，更改DTMF状态 */
    pstCallCtx->stDtmfCtx.stDtmfDurationTimer.ulTimerLen = (VOS_UINT32)pstDtmfCurInfo->usOnLength;
    IMSA_StartTimer(&pstCallCtx->stDtmfCtx.stDtmfDurationTimer);
    IMSA_CallSetDtmfState(IMSA_CALL_DTMF_WAIT_TIME_OUT);

    return;
}

/*****************************************************************************
 Function Name  : IMSA_CallRcvImsStopDtmfOk
 Description    : stop dtmf成功消息处理
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.lihong 0015001     2013-10-14  Draft Enact
*****************************************************************************/
VOS_VOID  IMSA_CallRcvImsStopDtmfOk( VOS_VOID )
{
    IMSA_CALL_DTMF_INFO_STRU           *pstDtmfCurInfo  = VOS_NULL_PTR;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();
    IMSA_CALL_DTMF_STATE_ENUM_UINT8     enDtmfState     = IMSA_CALL_DTMF_STATE_BUTT;

    VOS_UINT32                          ulResult = VOS_FALSE;

    /* 判断状态是否异常 */
    enDtmfState = IMSA_CallGetDtmfState();
    if ( (enDtmfState != IMSA_CALL_DTMF_WAIT_STOP_CNF)
      && (enDtmfState != IMSA_CALL_DTMF_WAIT_AUTO_STOP_CNF) )
    {
        IMSA_WARN_LOG("IMSA_CallRcvImsStopDtmfOk: Dtmf State Error!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CallRcvImsStopDtmfOk_ENUM, IMSA_STATE_ERROR);
        return;
    }

    /* 停止DTMF保护定时器 */
    IMSA_StopTimer(&pstCallCtx->stDtmfCtx.stDtmfProtectTimer);

    /* 如果是用户发出的STOP_DTMF需要回复正式响应事件 */
    pstDtmfCurInfo  = IMSA_CallGetCurrentDtmfInfo();
    if (enDtmfState != IMSA_CALL_DTMF_WAIT_AUTO_STOP_CNF)
    {
        (VOS_VOID)IMSA_CallSendSpmStopDtmfRsltMsg(  pstDtmfCurInfo->usClientId,
                                                    pstDtmfCurInfo->ucSpmOpId,
                                                    pstDtmfCurInfo->ucCallId,
                                                    TAF_CS_CAUSE_SUCCESS);
    }

    IMSA_CallSetDtmfState(IMSA_CALL_DTMF_IDLE);

    /* 处理缓存，待三阶段实现 */
    if(IMSA_CallGetDtmfCnt() > 0)
    {
        /* 判断缓存的第一条是STOP DTMF*/
        if(0 == IMSA_CallGetDtmfBufList(0).usOnLength)
        {
            (VOS_VOID)IMSA_CallSendSpmStopDtmfRsltMsg(IMSA_CallGetDtmfBufList(0).usClientId,
                                                      IMSA_CallGetDtmfBufList(0).ucSpmOpId,
                                                      IMSA_CallGetDtmfBufList(0).ucCallId,
                                                      TAF_CS_CAUSE_SUCCESS);

            /* 删除这条STOP DTMF缓存 */
            IMSA_CallDeleteSavedDtmfInfo(0);
        }

        /* 判断是否还有缓存 */
        if(0 == IMSA_CallGetDtmfCnt())
        {
            return;
        }

        /* 缓存的第一条是STRAT DTMF */
        ulResult = IMSA_CallCheckUserDtmfCallId(0);
        if(TAF_CS_CAUSE_SUCCESS != ulResult)
        {
            IMSA_WARN_LOG("IMSA_CallRcvImsStopDtmfOk: Call Check User Dtmf Fail!");
            TLPS_PRINT2LAYER_WARNING(IMSA_CallRcvImsStopDtmfOk_ENUM, LNAS_FAIL);
            IMSA_CallClearDtmfInfo(TAF_CS_CAUSE_UNKNOWN);
            return;
        }

        if (VOS_TRUE != IMSA_CallSendImsMsgStartDtmf(IMSA_CallGetDtmfBufList(0).ucCallId,
                                                     IMSA_CallGetDtmfBufList(0).cKey,
                                                     IMSA_CallGetDtmfBufList(0).usOnLength))
        {
            IMSA_WARN_LOG("IMSA_CallRcvImsStopDtmfOk: Send Start Dtmf Fail!");
            TLPS_PRINT2LAYER_WARNING(IMSA_CallRcvImsStopDtmfOk_ENUM, 2);

            IMSA_CallClearDtmfInfo(TAF_CS_CAUSE_UNKNOWN);
            return;
        }

        IMSA_StartTimer(&pstCallCtx->stDtmfCtx.stDtmfProtectTimer);
        IMSA_CallSetDtmfState(IMSA_CALL_DTMF_WAIT_START_CNF);
        IMSA_MEM_CPY_S( IMSA_CallGetCurrentDtmfInfo(),
                        sizeof(IMSA_CALL_DTMF_INFO_STRU),
                        &IMSA_CallGetDtmfBufList(0),
                        sizeof(IMSA_CALL_DTMF_INFO_STRU));
        IMSA_CallGetCurrentDtmfInfo()->ulImsOpid = IMSA_GetImsOpId();

        /* 删除这条START DTMF缓存 */
        IMSA_CallDeleteSavedDtmfInfo(0);
    }

    return;
}
/*****************************************************************************
 Function Name  : IMSA_CallProcImsMsgOKOrERRORToSpmSupsCmreq
 Description    : IMS REASON OK消息的处理
 Input          : ulFindOpidResult----------IMSA_CallImsMsgFind执行结果
                  pstOutputCallEvent--------IMS OUTPUT CALL消息指针
 Output         : VOS_UINT32
 Return Value   : 处理结果

 History        :
      1.wangchen 00209181   2014-07-08  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcImsMsgOKOrERRORToSpmSupsCmreq
(
    VOS_VOID
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();
    IMSA_CALL_ENTITY_STRU              *pstCallEntity   = VOS_NULL_PTR;
    VOS_UINT8                           i = 0;
    TAF_CS_CAUSE_ENUM_UINT32            enSpmErr = IMSA_NULL;
    VOS_UINT8                           ucRedialCallIndex   = IMSA_NULL;

    /* 如果SPM下发的是REL_ALL的挂断命令，如果存在IMS未上报过DIALING状态的呼叫实体，需要IMSA
        自己释放，因为IMS上报INVILED状态时，会携带callid，但是IMSA并不认识该callid，导致找不到呼叫实体*/
    if (MN_CALL_SUPS_CMD_REL_ALL_CALL == pstCallCtx->stSpmMsg.stParam.stSupsParam.enCallSupsCmd)
    {
        for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
        {
            if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
                (IMSA_CALL_INVALID_ID == pstCallCtx->astCallEntity[i].ucImscallId))
            {

                 /* 如果请求释放的CALL ID跟重拨CALL ID一致，则直接回复成功，并打断重播流程 */
                if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stRedialIntervelTimer))
                {
                    ucRedialCallIndex   = (VOS_UINT8)pstCallCtx->stRedialIntervelTimer.usPara;
                    if (ucRedialCallIndex < IMSA_CALL_MAX_NUM)
                    {
                        pstCallEntity = &pstCallCtx->astCallEntity[ucRedialCallIndex];
                        IMSA_CallInterruptRedial(pstCallEntity);
                    }
                }
                /*  如果请求释放的CALL ID和正在紧急重注册的CALL ID一致，则通知SPM RELEASE 事件 */
                else if (IMSA_TRUE == pstCallCtx->ucRetryEmcRegFlag)
                {
                    pstCallEntity = &pstCallCtx->astCallEntity[pstCallCtx->ucCallEntityIndex];


                    /* 将IMS错误原因值转化为SPM错误原因值 */
                    /* 修改函数入参 */
                    enSpmErr = IMSA_CallTransImsErr2SpmErr(&pstCallEntity->stImsError.stErrorCode);

                    pstCallEntity->ucSpmcallId = pstCallCtx->ucId;

                    IMSA_CallReleaseCallCommonProc(pstCallEntity, enSpmErr);

                    /* 清除保存的重注册标识等参数 */
                    pstCallCtx->ucRetryEmcRegFlag = IMSA_FALSE;
                    pstCallCtx->ucId = IMSA_NULL;
                    pstCallCtx->ucCallEntityIndex = IMSA_NULL;

                }
                else
                {

                    IMSA_CallUpdateDiscCallDir( pstCallCtx->astCallEntity[i].ucSpmcallId, IMSA_TRUE);

                    IMSA_CallReleaseCallCommonProc(&(pstCallCtx->astCallEntity[i]), TAF_CS_CAUSE_SUCCESS);
                }

            }
        }
    }
    return;
}
/*****************************************************************************
 Function Name  : IMSA_CallProcImsMsgOKWhenFindOpidSucc
 Description    : IMS REASON OK消息的处理
 Input          : ulFindOpidResult----------IMSA_CallImsMsgFind执行结果
                  pstOutputCallEvent--------IMS OUTPUT CALL消息指针
 Output         : VOS_UINT32
 Return Value   : 处理结果

 History        :
      1.wangchen 00209181   2014-07-08  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsMsgOKWhenFindOpidSucc
(
    const IMSA_IMS_OUTPUT_CALL_EVENT_STRU  *pstOutputCallEvent
)
{
    VOS_UINT32                          ulResult        = VOS_FALSE;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();
    IMSA_CALL_ENTITY_STRU              *pstCallEntity   = VOS_NULL_PTR;

    (VOS_VOID)pstOutputCallEvent;

    /* 根据不同命令回复SPM */
    switch (pstCallCtx->stSpmMsg.ulSpmMsgId)
    {
    case ID_SPM_IMSA_CALL_ORIG_REQ:

        IMSA_INFO_LOG1("IMSA_CallProcImsMsgOKWhenFindOpidSucc: pstCallCtx->ucRetryEmcRegFlag = ",pstCallCtx->ucRetryEmcRegFlag);
        TLPS_PRINT2LAYER_INFO1(IMSA_CallProcImsMsgOKWhenFindOpidSucc_ENUM, 1, pstCallCtx->ucRetryEmcRegFlag);

        /* 如果是重播时回复的OK，则不报给SPM */
        if ((VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stRedialMaxTimer))
            && (pstCallCtx->stRedialMaxTimer.usPara < IMSA_CALL_MAX_NUM))
        {
            pstCallEntity = &pstCallCtx->astCallEntity[pstCallCtx->stRedialMaxTimer.usPara];
            if (pstCallEntity->ucRedialTimes > 0)
            {
                break;
            }
        }

        if (IMSA_TRUE == pstCallCtx->ucRetryEmcRegFlag)
        {
            IMSA_INFO_LOG("IMSA_CallProcImsMsgOKWhenFindOpidSucc: pstCallCtx->ucRetryEmcRegFlag is false");
            TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgOKWhenFindOpidSucc_ENUM, 2);
            /* 如果是紧急呼叫收到#380，重新发起紧急呼叫时，收到OK,不需要报给SPM */
            pstCallCtx->ucRetryEmcRegFlag = IMSA_FALSE;
            pstCallCtx->ucId = IMSA_NULL;
            pstCallCtx->ucCallEntityIndex = IMSA_NULL;
            break;
        }

        break;
    case ID_SPM_IMSA_CALL_SUPS_CMD_REQ:
        ulResult = IMSA_CallSendSpmSupsResultMsg(pstCallCtx->stSpmMsg.usClientId,
                                              pstCallCtx->stSpmMsg.ulOpId,
                                              pstCallCtx->stSpmMsg.ulCallId,
                                              MN_CALL_SS_RES_SUCCESS);

        IMSA_CallProcImsMsgOKOrERRORToSpmSupsCmreq();
        break;
    case ID_SPM_IMSA_CALL_GET_CALL_INFO_REQ:
        IMSA_INFO_LOG("IMSA_CallProcImsMsgOKWhenFindOpidSucc: this command has handled by IMSA");
        TLPS_PRINT2LAYER_INFO1(IMSA_CallProcImsMsgOKWhenFindOpidSucc_ENUM, LNAS_RCV_MSG, 1);
        break;
    case ID_SPM_IMSA_CALL_GET_CUDR_REQ:
        IMSA_INFO_LOG("IMSA_CallProcImsMsgOKWhenFindOpidSucc: this command is not supported by IMSA");
        TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgOKWhenFindOpidSucc_ENUM, IMSA_NOT_SUPPORT);
        break;
    case ID_SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ:
        ulResult = IMSA_CallSendSpmInviteNewPtptCnfMsg(pstCallCtx->stSpmMsg.usClientId,
                                                       pstCallCtx->stSpmMsg.ulOpId,
                                                       pstCallCtx->stSpmMsg.ulCallId,
                                                       TAF_CS_CAUSE_SUCCESS);
        break;

    case ID_SPM_IMSA_CALL_MODIFY_REQ:
        ulResult = IMSA_CallSendSpmModifyCnfMsg(pstCallCtx->stSpmMsg.usClientId,
                                               pstCallCtx->stSpmMsg.ulOpId,
                                               pstCallCtx->stSpmMsg.ulCallId,
                                               TAF_CS_CAUSE_SUCCESS);
        break;
    case ID_SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ:
        ulResult = IMSA_CallSendSpmAnswerRemoteModifyCnfMsg(pstCallCtx->stSpmMsg.usClientId,
                                                           pstCallCtx->stSpmMsg.ulOpId,
                                                           pstCallCtx->stSpmMsg.ulCallId,
                                                           TAF_CS_CAUSE_SUCCESS);
        break;
    case ID_SPM_IMSA_CALL_ECONF_DIAL_REQ:
        IMSA_INFO_LOG("IMSA_CallProcImsMsgOKWhenFindOpidSucc: ID_SPM_IMSA_CALL_ECONF_DIAL_REQ command processed by IMSA");
        TLPS_PRINT2LAYER_INFO1(IMSA_CallProcImsMsgOKWhenFindOpidSucc_ENUM, LNAS_RCV_MSG, 2);
        break;
    case ID_SPM_IMSA_CALL_ECONF_ADD_USERS_REQ:
        (VOS_VOID)IMSA_CallSendSpmEconfAddUserCnfMsg(pstCallCtx->stSpmMsg.usClientId,
                                           pstCallCtx->stSpmMsg.ulOpId,
                                           TAF_CS_CAUSE_SUCCESS);
        break;
    default:
        ulResult = VOS_FALSE;
        IMSA_ERR_LOG1("IMSA_CallProcImsMsgOKWhenFindOpidSucc: invalid call request", pstCallCtx->stSpmMsg.ulSpmMsgId);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallProcImsMsgOKWhenFindOpidSucc_ENUM, LNAS_MSG_INVALID, pstCallCtx->stSpmMsg.ulSpmMsgId);
        break;
    }

    /* 清除缓存命令 */
    IMSA_CallImsMsgClear();
    IMSA_CallSpmMsgClear();

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcImsMsgOk
 Description    : IMS REASON OK消息的处理
 Input          : pstOutputCallEvent      D2输出事件
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-12-23  Moidfy:Redail
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsMsgOk(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent)
{
    VOS_UINT32                          ulResult        = VOS_FALSE;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();


    /* 如果REASON OK对应的opid检查失败，则丢弃该消息 */
    ulResult = IMSA_CallImsMsgFind(pstOutputCallEvent->ulOpId);
    if (IMSA_CALL_FIND_FAIL == ulResult)
    {
        IMSA_ERR_LOG1("IMSA_CallProcImsMsgOk: not found op id", pstOutputCallEvent->ulOpId);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallProcImsMsgOk_ENUM, IMSA_NORMAL_OPID, pstOutputCallEvent->ulOpId);
        return VOS_TRUE;
    }

    if (IMSA_CALL_FIND_SUCC_DTMF == ulResult)
    {
        if (IMSA_CallGetDtmfState() == IMSA_CALL_DTMF_WAIT_START_CNF)
        {
            IMSA_CallRcvImsStartDtmfOk();
        }
        else
        {
            IMSA_CallRcvImsStopDtmfOk();
        }

        return VOS_TRUE;
    }

    /* 停止保护定时器 */
    IMSA_StopTimer(&pstCallCtx->stProctectTimer);

    /* 根据不同命令回复SPM */
    return IMSA_CallProcImsMsgOKWhenFindOpidSucc(pstOutputCallEvent);

}

/*****************************************************************************
 Function Name  : IMSA_CallEntitySaveErrorInfo
 Description    : 如果D2携带Reason Description，则进行解析并保存在呼叫实体中
 Input          : pstCallEntity         呼叫实体
                  pstOutputCallEvent      D2输出事件
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-20  Draft Enact
      2.lihong 00150010    2013-10-09  Modify
*****************************************************************************/
VOS_VOID IMSA_CallEntitySaveErrorInfo
(
    IMSA_CALL_ENTITY_STRU                  *pstCallEntity,
    const IMSA_IMS_OUTPUT_CALL_EVENT_STRU  *pstOutputCallEvent
)
{
    pstCallEntity->bitOpErrorInfo = IMSA_OP_TRUE;

    IMSA_MEM_CPY_S( &pstCallEntity->stImsError,
                    sizeof(IMSA_IMS_CALL_ERROR_STRU),
                    &pstOutputCallEvent->stCallError,
                    sizeof(IMSA_IMS_CALL_ERROR_STRU));

    IMSA_INFO_LOG1("IMSA_CallEntitySaveErrorInfo:errorCode:", pstCallEntity->stImsError.stErrorCode.usSipStatusCode);
    TLPS_PRINT2LAYER_INFO1(IMSA_CallEntitySaveErrorInfo_ENUM, 1, pstCallEntity->stImsError.stErrorCode.usSipStatusCode);
}

/*****************************************************************************
 Function Name  : IMSA_CallRcvImsStartDtmfError
 Description    : start dmtf失败处理
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.lihong 0015001     2013-10-14  Draft Enact
*****************************************************************************/
VOS_VOID  IMSA_CallRcvImsStartDtmfError( VOS_VOID )
{
    IMSA_CALL_DTMF_INFO_STRU           *pstDtmfCurInfo  = VOS_NULL_PTR;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();

    VOS_UINT32                          ulResult = VOS_FALSE;

    /* 判断状态是否异常 */
    if (IMSA_CallGetDtmfState() != IMSA_CALL_DTMF_WAIT_START_CNF)
    {
        IMSA_WARN_LOG("IMSA_CallRcvImsStartDtmfError: Dtmf State Error!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CallRcvImsStartDtmfError_ENUM, IMSA_STATE_ERROR);
        return;
    }

    /* 停止DTMF保护定时器 */
    IMSA_StopTimer(&pstCallCtx->stDtmfCtx.stDtmfProtectTimer);

    /* 回复DTMF正式响应事件 */
    pstDtmfCurInfo  = IMSA_CallGetCurrentDtmfInfo();
    (VOS_VOID)IMSA_CallSendSpmStartDtmfRsltMsg( pstDtmfCurInfo->usClientId,
                                                pstDtmfCurInfo->ucSpmOpId,
                                                pstDtmfCurInfo->ucCallId,
                                                TAF_CS_CAUSE_DTMF_REJ);

    IMSA_CallSetDtmfState(IMSA_CALL_DTMF_IDLE);

    /* 缓存处理*/
    if(IMSA_CallGetDtmfCnt() > 0)
    {
        /* 判断缓存的第一条是STOP DTMF*/
        if(0 == IMSA_CallGetDtmfBufList(0).usOnLength)
        {
            (VOS_VOID)IMSA_CallSendSpmStopDtmfCnfMsg( IMSA_CallGetDtmfBufList(0).usClientId,
                                                      IMSA_CallGetDtmfBufList(0).ucSpmOpId,
                                                      IMSA_CallGetDtmfBufList(0).ucCallId,
                                                      TAF_CS_CAUSE_DTMF_REJ);

            /* 删除这条STOP DTMF缓存 */
            IMSA_CallDeleteSavedDtmfInfo(0);
        }

        /* 判断是否还有缓存 */
        if(0 == IMSA_CallGetDtmfCnt())
        {
            return;
        }

        /* 缓存的第一条是START DTMF */
        ulResult = IMSA_CallCheckUserDtmfCallId(0);
        if(TAF_CS_CAUSE_SUCCESS != ulResult)
        {
            IMSA_WARN_LOG("IMSA_CallRcvImsStartDtmfError: Call Check User Dtmf Fail!");
            TLPS_PRINT2LAYER_WARNING1(IMSA_CallRcvImsStartDtmfError_ENUM, LNAS_FAIL, 1);
            IMSA_CallClearDtmfInfo(TAF_CS_CAUSE_UNKNOWN);
            return;
        }

        if (VOS_TRUE != IMSA_CallSendImsMsgStartDtmf(IMSA_CallGetDtmfBufList(0).ucCallId,
                                                     IMSA_CallGetDtmfBufList(0).cKey,
                                                     IMSA_CallGetDtmfBufList(0).usOnLength))
        {
            IMSA_WARN_LOG("IMSA_CallRcvImsStartDtmfError: Send Start Dtmf Fail!");
            TLPS_PRINT2LAYER_WARNING1(IMSA_CallRcvImsStartDtmfError_ENUM, LNAS_FAIL, 2);

            IMSA_CallClearDtmfInfo(TAF_CS_CAUSE_UNKNOWN);
            return;
        }

        IMSA_StartTimer(&pstCallCtx->stDtmfCtx.stDtmfProtectTimer);
        IMSA_CallSetDtmfState(IMSA_CALL_DTMF_WAIT_START_CNF);
        IMSA_MEM_CPY_S(IMSA_CallGetCurrentDtmfInfo(),
                     sizeof(IMSA_CALL_DTMF_INFO_STRU),
                     &IMSA_CallGetDtmfBufList(0),
                     sizeof(IMSA_CALL_DTMF_INFO_STRU));
        IMSA_CallGetCurrentDtmfInfo()->ulImsOpid = IMSA_GetImsOpId();

        /* 删除这条START DTMF缓存 */
        IMSA_CallDeleteSavedDtmfInfo(0);
    }

    return;
}
/*****************************************************************************
 Function Name  : IMSA_CallRcvImsOrigReqError
 Description    : Orig Req失败处理
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.wangchen 00209181   2014-07-24  Draft Enact
*****************************************************************************/
VOS_VOID  IMSA_CallRcvImsOrigReqError
(
    const IMSA_IMS_OUTPUT_CALL_EVENT_STRU  *pstOutputCallEvent
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();
    IMSA_CALL_ENTITY_STRU              *pstCallEntity   = VOS_NULL_PTR;
    TAF_CS_CAUSE_ENUM_UINT32            enSpmErr        = IMSA_NULL;
    VOS_UINT16                          usRedialCallIndex = IMSA_NULL;

    /* 如果是重播时回复的ERROR，则打断重播流程 */
    if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stRedialMaxTimer))
    {
        usRedialCallIndex   = pstCallCtx->stRedialMaxTimer.usPara;
        if (usRedialCallIndex < IMSA_CALL_MAX_NUM)
        {
            pstCallEntity = &pstCallCtx->astCallEntity[usRedialCallIndex];
            if (pstCallEntity->ucRedialTimes > 0)
            {
                #if (FEATURE_ON == FEATURE_PTM)
                IMSA_CallErrRecord(pstCallEntity->stImsError.stErrorCode.usSipStatusCode, pstCallEntity);
                #endif
                IMSA_INFO_LOG("IMSA_CallProcImsMsgError:redial orig error");
                TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgError_ENUM, LNAS_ERROR);
                IMSA_CallEntitySaveErrorInfo(pstCallEntity, pstOutputCallEvent);
                IMSA_CallInterruptRedial(pstCallEntity);
                return;
            }
        }
    }
    if(IMSA_TRUE == pstCallCtx->ucRetryEmcRegFlag)
    {
        /* 如果是紧急呼叫收到#380，重新发起紧急呼叫时，收到ERROR，需要给SPM发送release事件 */
        pstCallEntity = &pstCallCtx->astCallEntity[pstCallCtx->ucCallEntityIndex];

        IMSA_CallEntitySaveErrorInfo(pstCallEntity, pstOutputCallEvent);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallErrRecord(pstCallEntity->stImsError.stErrorCode.usSipStatusCode, pstCallEntity);
        #endif
        /* 修改函数入参 */
        enSpmErr = IMSA_CallTransImsErr2SpmErr(&pstCallEntity->stImsError.stErrorCode);

        pstCallEntity->ucSpmcallId = pstCallCtx->ucId;
        IMSA_CallReleaseCallCommonProc(pstCallEntity, enSpmErr);

        pstCallCtx->ucRetryEmcRegFlag = IMSA_FALSE;
        pstCallCtx->ucId = IMSA_NULL;
        pstCallCtx->ucCallEntityIndex = IMSA_NULL;
        return;
    }

    /* 由于在收到SPM的ORIG_REQ消息时，已经给SPM回复过ORIG_CNF事件，同时上报过ORIG，所以再收到IMS上报的ERROR时，
    需要给SPM发送RELEASE事件 */
    pstCallEntity = IMSA_CallEntityGetUsedByImsCallId(IMSA_CALL_INVALID_ID);
    if (VOS_NULL_PTR != pstCallEntity)
    {
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallErrRecord(pstCallEntity->stImsError.stErrorCode.usSipStatusCode, pstCallEntity);
        #endif
        IMSA_CallReleaseCallCommonProc(pstCallEntity, TAF_CS_CAUSE_SUCCESS);
    }

    return;
}

/* lihong00150010 2014-04-21 降全复杂度 begin */
/*****************************************************************************
 Function Name  : IMSA_CallProcImsMsgError
 Description    : IMS REASON ERROR消息的处理
 Input          : ulFindOpidResult----------IMSA_CallImsMsgFind执行结果
                  pstOutputCallEvent--------IMS OUTPUT CALL消息指针
 Output         : VOS_UINT32
 Return Value   : 处理结果

 History        :
      1.lihong 00150010    2014-04-21  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsMsgErrorWhenFindOpidSucc
(
    const IMSA_IMS_OUTPUT_CALL_EVENT_STRU  *pstOutputCallEvent,
    VOS_UINT32                              ulFindOpidResult
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();
    IMSA_CALL_ENTITY_STRU              *pstCallEntity   = VOS_NULL_PTR;
    VOS_UINT32                          ulResult        = VOS_FALSE;
    TAF_CS_CAUSE_ENUM_UINT32            enSpmErr        = IMSA_NULL;

    if (IMSA_CALL_FIND_SUCC_DTMF == ulFindOpidResult)
    {
        if (IMSA_CallGetDtmfState() == IMSA_CALL_DTMF_WAIT_START_CNF)
        {
            IMSA_CallRcvImsStartDtmfError();
        }
        else
        {
            /* 与IMS协议栈接口约定，STOP DTMF没有失败 */
              IMSA_INFO_LOG("IMSA_CallProcImsMsgErrorWhenFindOpidSucc: stop dtmf can not error!");
              TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgErrorWhenFindOpidSucc_ENUM, 1);
        }

        return VOS_TRUE;
    }

    /* 停止保护定时器 */
    IMSA_StopTimer(&pstCallCtx->stProctectTimer);

    /* 根据不同命令回复SPM */
    switch (pstCallCtx->stSpmMsg.ulSpmMsgId)
    {
    case ID_SPM_IMSA_CALL_ORIG_REQ:
        if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stNormalTcallTimer))
        {
            IMSA_StopTimer(&pstCallCtx->stNormalTcallTimer);
        }
        if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stEmcTcallTimer))
        {
            IMSA_StopTimer(&pstCallCtx->stEmcTcallTimer);
        }

        IMSA_CallRcvImsOrigReqError(pstOutputCallEvent);
        #if (FEATURE_ON == FEATURE_PTM)
        /* 待新的CHR生效后，需要将旧CHR删除 */
        IMSA_CallErrRecord(IMSA_ERR_LOG_CALL_FAIL_REASON_REMOTE, VOS_NULL_PTR);
        IMSA_CallFailErrRecord( pstCallCtx->stSpmMsg.stParam.stOrigParam.enCallType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_REMOTE,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_REMOTE,
                                VOS_NULL_PTR,
                                pstOutputCallEvent->stCallError.stErrorCode.usSipStatusCode);
        #endif
        break;

    case ID_SPM_IMSA_CALL_SUPS_CMD_REQ:
        ulResult = IMSA_CallSendSpmSupsResultMsg(pstCallCtx->stSpmMsg.usClientId,
                                              pstCallCtx->stSpmMsg.ulOpId,
                                              pstCallCtx->stSpmMsg.ulCallId,
                                              MN_CALL_SS_RES_FAIL);
        IMSA_CallProcImsMsgOKOrERRORToSpmSupsCmreq();

        break;
    case ID_SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ:
        /* 修改函数入参 */
        enSpmErr = IMSA_CallTransImsErr2SpmErr(&pstOutputCallEvent->stCallError.stErrorCode);

        ulResult = IMSA_CallSendSpmInviteNewPtptCnfMsg(pstCallCtx->stSpmMsg.usClientId,
                                                       pstCallCtx->stSpmMsg.ulOpId,
                                                       pstCallCtx->stSpmMsg.ulCallId,
                                                       enSpmErr);

        pstCallEntity = IMSA_CallEntityGetUsedByImsCallId(IMSA_CALL_INVALID_ID);
        if (VOS_NULL_PTR != pstCallEntity)
        {
            IMSA_CallEntityFree(pstCallEntity);
        }
        break;
    case ID_SPM_IMSA_CALL_MODIFY_REQ:
        /* 修改函数入参 */
        enSpmErr = IMSA_CallTransImsErr2SpmErr(&pstOutputCallEvent->stCallError.stErrorCode);

        ulResult = IMSA_CallSendSpmModifyCnfMsg(pstCallCtx->stSpmMsg.usClientId,
                                               pstCallCtx->stSpmMsg.ulOpId,
                                               pstCallCtx->stSpmMsg.ulCallId,
                                               enSpmErr);

        #if (FEATURE_ON == FEATURE_PTM)
        pstCallEntity = IMSA_CallEntityGetUsedBySpmCallId(pstCallCtx->stSpmMsg.ulCallId);
        if (VOS_NULL_PTR != pstCallEntity)
        {
            IMSA_ModifyCallTypeErrRecord(pstCallEntity->enType, pstOutputCallEvent->stCallError.stErrorCode.usSipStatusCode);
        }
        #endif
        break;
    case ID_SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ:
        /* 修改函数入参 */
        enSpmErr = IMSA_CallTransImsErr2SpmErr(&pstOutputCallEvent->stCallError.stErrorCode);

        ulResult = IMSA_CallSendSpmAnswerRemoteModifyCnfMsg(pstCallCtx->stSpmMsg.usClientId,
                                                           pstCallCtx->stSpmMsg.ulOpId,
                                                           pstCallCtx->stSpmMsg.ulCallId,
                                                           enSpmErr);

        #if (FEATURE_ON == FEATURE_PTM)
        pstCallEntity = IMSA_CallEntityGetUsedBySpmCallId(pstCallCtx->stSpmMsg.ulCallId);
        if (VOS_NULL_PTR != pstCallEntity)
        {
            IMSA_ModifyCallTypeErrRecord(pstCallEntity->enType, pstOutputCallEvent->stCallError.stErrorCode.usSipStatusCode);
        }
        #endif
        break;
    case ID_SPM_IMSA_CALL_ECONF_DIAL_REQ:
        pstCallEntity = IMSA_CallEntityGetUsedByImsCallId(IMSA_CALL_INVALID_ID);
        if (VOS_NULL_PTR != pstCallEntity)
        {
            IMSA_CallReleaseCallCommonProc(pstCallEntity, TAF_CS_CAUSE_SUCCESS);
        }

        break;
    case ID_SPM_IMSA_CALL_ECONF_ADD_USERS_REQ:
        /* 修改函数入参 */
        enSpmErr = IMSA_CallTransImsErr2SpmErr(&pstOutputCallEvent->stCallError.stErrorCode);
        ulResult = IMSA_CallSendSpmEconfAddUserCnfMsg(pstCallCtx->stSpmMsg.usClientId,
                                                       pstCallCtx->stSpmMsg.ulOpId,
                                                       enSpmErr);
        break;
    default:
        ulResult = VOS_FALSE;
        IMSA_ERR_LOG1("IMSA_CallProcImsMsgErrorWhenFindOpidSucc: invalid call request", pstCallCtx->stSpmMsg.ulSpmMsgId);
        TLPS_PRINT2LAYER_INFO1(IMSA_CallProcImsMsgErrorWhenFindOpidSucc_ENUM, LNAS_MSG_INVALID, pstCallCtx->stSpmMsg.ulSpmMsgId);
    }

    /* 清除缓存命令 */
    IMSA_CallImsMsgClear();
    IMSA_CallSpmMsgClear();

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcImsMsgError
 Description    : IMS REASON ERROR消息的处理
 Input          : pstOutputCallEvent      D2输出事件
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 0015001     2013-09-30  Modify
      3.lihong 00150010    2013-12-23  Moidfy:Redail
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsMsgError(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent)
{
    IMSA_CALL_ENTITY_STRU              *pstCallEntity   = VOS_NULL_PTR;
    VOS_UINT32                          ulResult        = VOS_FALSE;
    VOS_UINT32                          ulCallId        = 0;

    /* 如果REASON ERROR对应的opid检查失败，则说明是IMS回复OK之后，网侧拒绝UE的场景；
       如果OPID查找成功，则是没有发起空口流程，IMS直接回复的ERROR */
    ulResult = IMSA_CallImsMsgFind(pstOutputCallEvent->ulOpId);
    if (IMSA_CALL_FIND_FAIL == ulResult)
    {
        ulCallId = (VOS_UINT32)pstOutputCallEvent->stCallError.ulCallIndex;
        /**
         * TODO:
         * 1. 如果是呼叫失败的场景，需要D2在REASON ERROR中也携带呼叫Id
         * 2. 之所以找不到csmid，是因为在之前收到的REASON OK中已经将保存的csmid清除
         * 3. 这里将ErrorInfo保存到每个呼叫实体考虑当有多个呼叫同时发生错误时可以正确处理，
         */
        pstCallEntity = IMSA_CallEntityGetUsedByImsCallId(ulCallId);
        if (VOS_NULL_PTR != pstCallEntity)
        {
            IMSA_CallEntitySaveErrorInfo(pstCallEntity, pstOutputCallEvent);
        }
        else
        {
            IMSA_ERR_LOG1("IMSA_CallProcImsMsgError: invalid err call id", ulCallId);
            TLPS_PRINT2LAYER_ERROR1(IMSA_CallProcImsMsgError_ENUM, IMSA_CALL_ID, ulCallId);
        }

        return VOS_TRUE;
    }

    return IMSA_CallProcImsMsgErrorWhenFindOpidSucc(pstOutputCallEvent, ulResult);
}
/* lihong00150010 2014-04-21 降全复杂度 end */

/*****************************************************************************
 Function Name  : IMSA_CallProcImsMsgIncoming
 Description    : IMS INCOMING事件的处理
 Input          : pstOutputCallEvent      D2输出事件
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsMsgIncoming(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent)
{
    IMSA_NORM_LOG("IMSA_CallProcImsMsgIncoming: enterd");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgIncoming_ENUM, LNAS_ENTRY);

    /**
     * 1. MT时因Incoming事件可能是第一个事件(无Precondition)，也可能是中间事件(有Precondition)
     * 2. Incoming事件中只包含了remote address，而该信息在其它呼叫相关事件/状态通知中也包含
     * 3. Incoming事件中无Call Id，即使发生一些异常(如Call Entity分配失败)，IMSA也无法去拒绝该呼叫
     *
     * 综上原因，Incoming事件不做任何处理。同理，Waiting事件也不做任何处理
     */


    (VOS_VOID)pstOutputCallEvent;

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallIsNormal380Call2EmergencyCall
 Description    : 判断是否将普通380呼叫转换为紧急呼叫。
 Input          : EmcSubType     紧急呼叫子类型，火警，匪警等。
 Output         : VOS_UINT32
 Return Value   : 处理结果， VOS_TRUE表明需要转换，VOS_FALSE表明不需要转换。

 History        :
      1.mengchao 277840      2014-09-09  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallIsNormal380Call2EmergencyCall(const IMSA_IMS_EMERGENCY_TYPE_ENUM_UINT8 EmcSubType)
{
    if(IMSA_IMS_EMERGENCY_SUB_TYPE_AMBULANCE <= EmcSubType
        && IMSA_IMS_EMERGENCY_SUB_TYPE_MOUNTAIN >= EmcSubType)
    {
        IMSA_INFO_LOG1("Normal Call switch to known Emc call, Type: ", EmcSubType);
        TLPS_PRINT2LAYER_INFO1(IMSA_CallIsNormal380Call2EmergencyCall_ENUM, IMSA_EMERGENCY, EmcSubType);
        return VOS_TRUE;
    }

    if(IMSA_IMS_EMERGENCY_SUB_TYPE_EXTENSION == EmcSubType
        && IMSA_EMS_STAUTS_SUPPORT == IMSA_GetNetInfoAddress()->enImsaEmsStatus)
    {
        IMSA_INFO_LOG("Normal Call switch to unknown Emc call.");
        TLPS_PRINT2LAYER_INFO(IMSA_CallIsNormal380Call2EmergencyCall_ENUM, 2);
        return VOS_TRUE;
    }

    if(IMSA_IMS_EMERGENCY_SUB_TYPE_GENERIC == EmcSubType)
    {
        IMSA_INFO_LOG("Normal Call switch to generic Emc call.");
        TLPS_PRINT2LAYER_INFO(IMSA_CallIsNormal380Call2EmergencyCall_ENUM, 3);
        return VOS_TRUE;
    }

    if(IMSA_IMS_EMERGENCY_SUB_TYPE_NONE == EmcSubType
        && IMSA_EMS_STAUTS_SUPPORT == IMSA_GetNetInfoAddress()->enImsaEmsStatus)
    {
        IMSA_INFO_LOG("Normal Call switch to Emc call.");
        TLPS_PRINT2LAYER_INFO(IMSA_CallIsNormal380Call2EmergencyCall_ENUM, 4);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_CallSetSpmEmergencyCat
 Description    : 设置SPM紧急呼叫子类型。
 Input          : EmcSubType     紧急呼叫子类型，火警，匪警等。
 Output         : pstEmergencyCat  SPM紧急呼叫子类型。
 Return Value   : VOS_VOID

 History        :
      1.mengchao 277840      2014-09-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallSetSpmEmergencyCat(const IMSA_IMS_EMERGENCY_TYPE_ENUM_UINT8 EmcSubType, MN_CALL_EMERGENCY_CAT_STRU* pstEmergencyCat)
{
    pstEmergencyCat->bExist = VOS_FALSE;

    if(IMSA_IMS_EMERGENCY_SUB_TYPE_AMBULANCE <= EmcSubType
        && IMSA_IMS_EMERGENCY_SUB_TYPE_MOUNTAIN >= EmcSubType)
    {
        pstEmergencyCat->bExist = VOS_TRUE;
        pstEmergencyCat->ucEmergencyCat = IMSA_CallEmcSubType2SPMEmcCat(EmcSubType);
    }
}

/*****************************************************************************
 Function Name  : IMSA_CallEntityProcErrorInfo380ForNormal
 Description    : 正常呼叫被380拒绝的处理
 Input          : pstCallEntity      呼叫实体
                  pstImsError        错误信息
 Output         : VOS_UINT32
 Return Value   : 处理结果:0表示不发RELEASED事件，1表示发RELEASED事件

 History        :
      1.liuhua 212067      2013-07-25  Draft Enact
      2.lihong 00150010    2013-09-02  Modify
      3.wangchen 00209181  2014-12-09  Modify:DTS2014112906255
*****************************************************************************/
VOS_UINT32 IMSA_CallEntityProcErrorInfo380ForNormal(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_ERROR_STRU *pstImsError)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx = IMSA_CallCtxGet();
    VOS_UINT32                          ulCheckRet      = 0;
    IMSA_EMC_CALL_TYPE_ENUM_UINT32      enEmcType       = IMSA_EMC_CALL_TYPE_BUTT;
    TAF_CS_CAUSE_ENUM_UINT32            enSpmErr        = IMSA_NULL;
    SPM_IMSA_CALL_ORIG_REQ_STRU         stCallOrigReq       = {0};
    VOS_UINT32                          ulResult            = VOS_FALSE;

    /* 如果网侧指示UE重新发起紧急注册，且UE支持紧急呼叫，则先通知SPM呼叫类型变更，然后发起初始紧急注册；
    如果UE不支持紧急呼叫，则先通知SPM呼叫类型变更，然后通知SPM release事件 */
    if ((IMSA_IMS_3GPP_TYPE_ACTION_EMERGENCY_REG == pstImsError->stErrorCode.usIms3gppAction)||
        (IMSA_IMS_3GPP_TYPE_ACTION_EMERGENCY == pstImsError->stErrorCode.usIms3gppAction))
    {
        if(IMSA_CallIsNormal380Call2EmergencyCall(pstImsError->stErrorCode.ucEmergencyType))
        {
            pstCallEntity->stSpmMsg.stParam.stOrigParam.enCallType = MN_CALL_TYPE_EMERGENCY;
            pstCallEntity->enType = IMSA_CALL_TYPE_EMC;

            /* 填写SPM紧急呼叫类型*/
            IMSA_CallSetSpmEmergencyCat(pstImsError->stErrorCode.ucEmergencyType, &(pstCallEntity->stSpmMsg.stParam.stOrigParam.stEmergencyCat));

            /* 通知SPM呼叫类型变更 */
            (VOS_VOID)IMSA_CallSendSpmCallTypeChangeInfoIndMsg(pstCallEntity->stSpmMsg.usClientId,
                                                               pstCallEntity->stSpmMsg.ulOpId,
                                                               pstCallEntity->ucSpmcallId,
                                                               MN_CALL_TYPE_VOICE,
                                                               MN_CALL_TYPE_EMERGENCY,
                                                               pstImsError->stErrorCode.ucEmergencyType);
        }

        if(IMSA_EMS_STAUTS_SUPPORT != IMSA_GetNetInfoAddress()->enImsaEmsStatus)
        {
            ulCheckRet = IMSA_CALL_AVAILABILITY_CHECK_RESULT_REJECT;
        }
        else if ((1 == IMSA_CallEntityGetUsedCount()) && (VOS_OK != IMSA_LRRC_JudgeCurrCellSingalQuality()))
        {
            /* 第一路CALL收到380时, 当前小区信号质量不好则返回呼叫不可用, 使上层去GU下继续CS电话 */
            ulCheckRet = IMSA_CALL_AVAILABILITY_CHECK_RESULT_REJECT;
        }
        else
        {
            /* 进行呼叫可用性检查 */
            ulCheckRet = IMSA_CallEmcCallAvailabilityCheck(&enEmcType);
        }

        /* 由于当前存在普通呼叫资源，所以呼叫可用性检查结果只可能是直接发起，
             或者需要紧急注册，或者需要先申请资源，再紧急注册 */
        switch (ulCheckRet)
        {
        /* 在普通服务上发起紧急呼叫 */
        case IMSA_CALL_AVAILABILITY_CHECK_RESULT_CONTINUE:

            /* 给IMS发送DIAL消息 */
            /* 取存储的ORIG REQ信息，再次发起呼叫建立请求 */
            stCallOrigReq.ulMsgId       = ID_SPM_IMSA_CALL_ORIG_REQ;
            stCallOrigReq.usClientId      = pstCallEntity->stSpmMsg.usClientId;
            stCallOrigReq.ucOpId          = (MN_OPERATION_ID_T)pstCallEntity->stSpmMsg.ulOpId;
            stCallOrigReq.stOrig        = pstCallEntity->stSpmMsg.stParam.stOrigParam;
            ulResult = IMSA_CallSendImsMsgDial(IMSA_CALL_INVALID_ID, &stCallOrigReq);
            if (VOS_TRUE == ulResult)
            {
                /* 启动保护定时器 */
                IMSA_StartTimer(&pstCallCtx->stProctectTimer);

                IMSA_MEM_CPY_S( &pstCallCtx->stSpmMsg,
                                sizeof(IMSA_CALL_SPM_MSG_STRU),
                                &pstCallEntity->stSpmMsg,
                                sizeof(IMSA_CALL_SPM_MSG_STRU));

                /* 保存呼叫实体ID和call ID，如果IMS收到DIAL消息后，直接回复ERROR，则IMSA需要使用原call id，
                给SPM发送release事件 */
                pstCallCtx->ucRetryEmcRegFlag = IMSA_TRUE;
                pstCallCtx->ucCallEntityIndex = pstCallEntity->ucCallEntityIndex;
                pstCallCtx->ucId = pstCallEntity->ucSpmcallId;

                /* 清除CALL ID，否则紧急注册成功，发起紧急呼叫后，IMS上报DAILING状态查找CALL实体时会查找不到;
                   而且该路电话对于IMS不可见，因此IMS可能将该CALL ID重新分配给INCOMING
                   CALL */
                pstCallEntity->ucImscallId = IMSA_CALL_INVALID_ID;

                /* 清除CALL状态，否则IMSA收到IMS上报的DIALING状态后，不会通知SPM */
                pstCallEntity->enStatus = IMSA_CALL_STATUS_IDLE;
            }
            else
            {
                /* 将IMS错误原因值转化为SPM错误原因值 */
                /* 修改函数入参 */
                enSpmErr = IMSA_CallTransImsErr2SpmErr(&pstCallEntity->stImsError.stErrorCode);

                IMSA_CallReleaseCallCommonProc(pstCallEntity, enSpmErr);
            }
            break;

        /* 首先发起紧急注册流程 */
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_CALL_AVAILABILITY_CHECK_RESULT_CACHED_NOTNEED_WAIT:

            (VOS_VOID)IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL,
                                                   IMSA_RF_RES_APPLY_TRIGER_SRC_EMC_CALL,
                                                   VOS_FALSE,
                                                   VOS_FALSE);

            /* 记录重新发起紧急注册的标识，保存呼叫实体ID和call ID */
            pstCallCtx->ucRetryEmcRegFlag = IMSA_TRUE;
            pstCallCtx->ucCallEntityIndex = pstCallEntity->ucCallEntityIndex;
            pstCallCtx->ucId = pstCallEntity->ucSpmcallId;

            /* 清除CALL ID，否则紧急注册成功，发起紧急呼叫后，IMS上报DAILING状态查找CALL实体时会查找不到;
               而且该路电话对于IMS不可见，因此IMS可能将该CALL ID重新分配给INCOMING
               CALL */
            pstCallEntity->ucImscallId = IMSA_CALL_INVALID_ID;

            /* 清除CALL状态，否则IMSA收到IMS上报的DIALING状态后，不会通知SPM */
            pstCallEntity->enStatus = IMSA_CALL_STATUS_IDLE;

            /* 触发紧急注册*/
            IMSA_StartImsEmcService();

            break;
        #endif
        case IMSA_CALL_AVAILABILITY_CHECK_RESULT_CACHED:

            /* 记录重新发起紧急注册的标识，保存呼叫实体ID和call ID */
            pstCallCtx->ucRetryEmcRegFlag = IMSA_TRUE;
            pstCallCtx->ucCallEntityIndex = pstCallEntity->ucCallEntityIndex;
            pstCallCtx->ucId = pstCallEntity->ucSpmcallId;

            /* 清除CALL ID，否则紧急注册成功，发起紧急呼叫后，IMS上报DAILING状态查找CALL实体时会查找不到;
               而且该路电话对于IMS不可见，因此IMS可能将该CALL ID重新分配给INCOMING
               CALL */
            pstCallEntity->ucImscallId = IMSA_CALL_INVALID_ID;

            /* 清除CALL状态，否则IMSA收到IMS上报的DIALING状态后，不会通知SPM */
            pstCallEntity->enStatus = IMSA_CALL_STATUS_IDLE;

            /* 触发紧急注册*/
            IMSA_StartImsEmcService();

            break;
        /* 呼叫被拒绝，通知SPM release事件 */
        default:
            /* 将IMS错误原因值转化为SPM错误原因值 */
            /* 修改函数入参 */
            enSpmErr = IMSA_CallTransImsErr2SpmErr(&pstCallEntity->stImsError.stErrorCode);

            IMSA_CallReleaseCallCommonProc(pstCallEntity, enSpmErr);

            break;
        }

        /* 普通呼叫已经转为紧急呼叫，所以如果不存在MO CALL时，需要将普通资源释放 */
        #if (FEATURE_ON == FEATURE_DSDS)
        IMSA_CallReleaseCallResourceCommonProc();
        #endif
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallEntityProcErrorInfo380ForEmc
 Description    : 紧急呼叫被380拒绝的处理
 Input          : pstCallEntity      呼叫实体
                  pstImsError        错误信息
 Output         : VOS_UINT32
 Return Value   : 处理结果:0表示不发RELEASED事件，1表示发RELEASED事件

 History        :
      1.liuhua 212067      2013-07-25  Draft Enact
      2.lihong 00150010    2013-09-02  Modify
      3.wangchen 00209181   2014-12-09 Modify:DTS2014112906255
*****************************************************************************/
VOS_UINT32 IMSA_CallEntityProcErrorInfo380ForEmc
(
    IMSA_CALL_ENTITY_STRU        *pstCallEntity,
    const IMSA_IMS_CALL_ERROR_STRU     *pstImsError
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx = IMSA_CallCtxGet();

    switch (pstCallEntity->enEmcType)
    {
        case IMSA_EMC_CALL_TYPE_IN_NORMAL_SRV:

            /* 根据Action的值来处理 */
            if (IMSA_IMS_3GPP_TYPE_ACTION_EMERGENCY_REG == pstImsError->stErrorCode.usIms3gppAction)
            {
                /* 记录重新发起紧急注册的标识，保存呼叫实体ID和call ID */
                pstCallCtx->ucRetryEmcRegFlag = IMSA_TRUE;
                pstCallCtx->ucCallEntityIndex = pstCallEntity->ucCallEntityIndex;
                pstCallCtx->ucId = pstCallEntity->ucSpmcallId;

                /* 清除CALL ID，否则紧急注册成功，发起紧急呼叫后，IMS上报DAILING状态查找CALL实体时会查找不到;
                   而且该路电话对于IMS不可见，因此IMS可能将该CALL ID重新分配给INCOMING
                   CALL */
                pstCallEntity->ucImscallId = IMSA_CALL_INVALID_ID;

                /* 清除CALL状态，否则IMSA收到IMS上报的DIALING状态后，不会通知SPM */
                pstCallEntity->enStatus = IMSA_CALL_STATUS_IDLE;

                /* 通知主控模块进行紧急注册 */
                (VOS_VOID)IMSA_CallSendIntraResultAction(IMSA_CALL_TYPE_EMC, IMSA_RESULT_ACTION_REG_WITH_FIRST_ADDR_PAIR);

                /* 不发RELEASED事件，不清除CALL实体，待IMS紧急注册成功后再尝试紧急呼 */
                return VOS_FALSE;
            }

            break;
        case IMSA_EMC_CALL_TYPE_EMC_CONN_EMC_REG:

            if ((VOS_FALSE == pstCallEntity->bitOpRetryCsCall)
                && (IMSA_IMS_3GPP_TYPE_ACTION_EMERGENCY_REG == pstImsError->stErrorCode.usIms3gppAction))
            {
                /* 记录重新发起紧急注册的标识，保存呼叫实体ID和call ID */
                pstCallCtx->ucRetryEmcRegFlag = IMSA_TRUE;
                pstCallCtx->ucCallEntityIndex = pstCallEntity->ucCallEntityIndex;
                pstCallCtx->ucId = pstCallEntity->ucSpmcallId;

                /* 清除CALL ID，否则紧急注册成功，发起紧急呼叫后，IMS上报DAILING状态查找CALL实体时会查找不到;
                   而且该路电话对于IMS不可见，因此IMS可能将该CALL ID重新分配给INCOMING
                   CALL */
                pstCallEntity->ucImscallId = IMSA_CALL_INVALID_ID;

                /* 清除CALL状态，否则IMSA收到IMS上报的DIALING状态后，不会通知SPM */
                pstCallEntity->enStatus = IMSA_CALL_STATUS_IDLE;

                /* 通知主控模块尝试使用下一组参数进行注册 */
                (VOS_VOID)IMSA_CallSendIntraResultAction(pstCallEntity->enType, IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR);

                /* 不发RELEASED事件，不清除CALL实体，待更换参数重新IMS紧急注册成功后再尝试紧急呼 */
                return VOS_FALSE;
            }
            break;

        default:

            IMSA_ERR_LOG1("IMSA_CallEntityProcErrorInfo380ForEmc: invalid emergency type", pstCallEntity->enEmcType);
            TLPS_PRINT2LAYER_ERROR1(IMSA_CallEntityProcErrorInfo380ForEmc_ENUM, LNAS_PARAM_INVALID, pstCallEntity->enEmcType);
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallEntityProcErrorInfo380ForEmc
 Description    : 呼叫被380拒绝的处理
 Input          : pstCallEntity      呼叫实体
                  pstImsError        错误信息
 Output         : VOS_UINT32
 Return Value   : 处理结果:0表示不发RELEASED事件，1表示发RELEASED事件

 History        :
      1.liuhua 212067      2013-07-25  Draft Enact
      2.lihong 00150010    2013-09-02  Modify
*****************************************************************************/
VOS_UINT32 IMSA_CallEntityProcErrorInfo380(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_ERROR_STRU *pstImsError)
{
    VOS_UINT32 ulResult = VOS_TRUE;

    switch (pstCallEntity->enType)
    {
    case IMSA_CALL_TYPE_VOICE:
    case IMSA_CALL_TYPE_VIDEO:
    case IMSA_CALL_TYPE_VIDEO_RX:
    case IMSA_CALL_TYPE_VIDEO_TX:
        ulResult = IMSA_CallEntityProcErrorInfo380ForNormal(pstCallEntity, pstImsError);
        break;
    case IMSA_CALL_TYPE_EMC:
        ulResult = IMSA_CallEntityProcErrorInfo380ForEmc(pstCallEntity, pstImsError);
        break;
    default:
        ulResult = VOS_TRUE;
        IMSA_ERR_LOG1("IMSA_CallEntityProcErrorInfo380: invalid call type", pstCallEntity->enType);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallEntityProcErrorInfo380_ENUM, LNAS_PARAM_INVALID, pstCallEntity->enType);
    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallEntityProcErrorInfo503
 Description    : 呼叫被503拒绝的处理
 Input          : pstCallEntity      呼叫实体
                  pstImsError        错误信息
 Output         : VOS_UINT32
 Return Value   : 处理结果:0表示不发RELEASED事件，1表示发RELEASED事件

 History        :
      1.liuhua 212067      2013-07-25  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallEntityProcErrorInfo503(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_ERROR_STRU *pstImsError)
{
    (VOS_VOID)pstCallEntity;
    (VOS_VOID)pstImsError;

    /**
     * 如果503响应中包含Retry-After，应该通知SPM，在普通错误通知中作为参数报上去吗？
     * 这里需要和GU讨论接口
     *
     * 暂时先不实现此功能
     */

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallEntityProcErrorInfo504
 Description    : 呼叫被503拒绝的处理
 Input          : pstCallEntity      呼叫实体
                  pstImsError        错误信息
 Output         : VOS_UINT32
 Return Value   : 处理结果:0表示不发RELEASED事件，1表示发RELEASED事件

 History        :
      1.liuhua 212067      2013-07-25  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallEntityProcErrorInfo504(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_ERROR_STRU *pstImsError)
{
    (VOS_VOID)pstCallEntity;

    if (IMSA_IMS_3GPP_TYPE_ACTION_RESTORATION_INIT_REG == pstImsError->stErrorCode.usIms3gppAction)
    {
        /* 通知Service进行Restoration操作 */
        (VOS_VOID)IMSA_CallSendIntraResultAction(pstCallEntity->enType, IMSA_RESULT_ACTION_REG_RESTORATION);
    }
    else
    {
        IMSA_ERR_LOG("IMSA_CallEntityProcErrorInfo504: not defined procedure");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallEntityProcErrorInfo504_ENUM, LNAS_ERROR);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcErrorInfo
 Description    : 根据服务器返回的错误信息进行处理
 Input          : pstCallEntity      呼叫实体
 Output         : VOS_VOID
 Return Value   : 处理结果:0表示不发RELEASED事件，1表示发RELEASED事件

 History        :
      1.liuhua 212067      2013-07-20  Draft Enact
      2.lihong 00150010    2013-09-02  Modify
*****************************************************************************/
VOS_UINT32 IMSA_CallEntityProcErrorInfo(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_ERROR_STRU *pstImsError)
{
    VOS_UINT32 ulResult = VOS_TRUE;

    IMSA_INFO_LOG1("IMSA_CallEntityProcErrorInfo: process error code", pstImsError->stErrorCode.usSipStatusCode);
    TLPS_PRINT2LAYER_INFO1(IMSA_CallEntityProcErrorInfo_ENUM, LNAS_ERROR, pstImsError->stErrorCode.usSipStatusCode);

    switch (pstImsError->stErrorCode.usSipStatusCode)
    {
    /* 380 */
    case IMSA_SIP_NW_ERROR_CAUSE_ALTERNATIVE_SERVICE:
        ulResult = IMSA_CallEntityProcErrorInfo380(pstCallEntity, pstImsError);
        break;
    /* 503 */
    case IMSA_SIP_NW_ERROR_CAUSE_SERVICE_UNAVAILABLE:
        ulResult = IMSA_CallEntityProcErrorInfo503(pstCallEntity, pstImsError);
        break;
    /* 504 */
    case IMSA_SIP_NW_ERROR_CAUSE_SERVER_TIMEOUT:
        ulResult = IMSA_CallEntityProcErrorInfo504(pstCallEntity, pstImsError);
        break;
    default:
        break;
    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallTransImsErr2SpmErr
 Description    : 将IMS错误原因值转化为SPM错误原因值
 Input          : ulImsErr-------------------IMS错误原因值
 Output         : VOS_VOID
 Return Value   : TAF_CS_CAUSE_ENUM_UINT32

 History        :
      1.lihong      00150010    2013-09-02  Draft Enact
      2.leixiantiao 00258641    2015-12-11  for DTS2015121609605
*****************************************************************************/
TAF_CS_CAUSE_ENUM_UINT32 IMSA_CallTransImsErr2SpmErr
(
    const IMSA_IMS_OUTPUT_ERROR_STRU              *pstErrorCode
)
{
    TAF_CS_CAUSE_ENUM_UINT32            enSpmErr = (TAF_CS_CAUSE_ENUM_UINT32)TAF_CS_CAUSE_BUTT;

    IMSA_INFO_LOG1("IMSA_CallTransImsErr2SpmErr: ims error code:", pstErrorCode->usSipStatusCode);

    /* 0-99原因值按以前实现转换为IMSA ERROR, 不判断子原因值 */
    if (IMSA_IMS_INT_ERROR_CODE_STRM_RTP_BREAK > pstErrorCode->usSipStatusCode)
    {
        enSpmErr = TAF_CS_CAUSE_IMSA_ERROR;
        return enSpmErr;
    }

    /* STRM_RTP_BREAK(通话过程中无语音包)原因上层需要知道不能转, 不需判断子原因值 */
    if (IMSA_IMS_INT_ERROR_CODE_STRM_RTP_BREAK == pstErrorCode->usSipStatusCode)
    {
        enSpmErr = TAF_CS_CAUSE_IMSA_STRM_RTP_BREAK;
        return enSpmErr;
    }

    /* 其他IMS内部原因值处理 */
    if ((pstErrorCode->usSipStatusCode < 300) || (pstErrorCode->usSipStatusCode > 699))
    {
        if (IMSA_IMS_CALL_FAIL_DETAIL_REASON_NULL == pstErrorCode->enCallFailDetailReason)
        {
            /* 若没有携带子原因值, 则表示需要重播, IMSA把IMS内部原因值转为TAF_CS_CAUSE_IMSA_RETRY_VIA_CS */
            enSpmErr = TAF_CS_CAUSE_IMSA_RETRY_VIA_CS;
        }
        else
        {
            /* 若携带子原因值, 则表示不需要重播, IMSA把IMS内部原因值转为TAF_CS_CAUSE_IMSA_IMS_ERROR */
            enSpmErr = TAF_CS_CAUSE_IMSA_IMS_ERROR;
        }
        return enSpmErr;
    }

    /* SIP原因值处理 */
    if (IMSA_IMS_CALL_FAIL_DETAIL_REASON_NULL == pstErrorCode->enCallFailDetailReason)
    {
        /* 若没有携带子原因值, 则表示由上层NV判断是否需要重播, IMSA把IMS内部原因值透给上层 */
        enSpmErr = pstErrorCode->usSipStatusCode + TAF_CS_CAUSE_IMS_BEGIN;
    }
    else
    {
        /* 若没有携带子原因值, 则表示不需要重播, IMSA把IMS内部原因值转为TAF_CS_CAUSE_IMS_OTHERS */
        enSpmErr = TAF_CS_CAUSE_IMS_OTHERS;
    }
    return enSpmErr;
}

/*****************************************************************************
 Function Name  : IMSA_CallIsExitMoNormalCall
 Description    : 释放CALL的公共处理
 Input          : pstCallEntity----------CALL实体指针
                  ulResult---------------原因值
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.wangchen 00209181   2015-11-28  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallIsExitMoNormalCall()
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx  = IMSA_CallCtxGet();
    VOS_UINT32                          i = 0;

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if (VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed)
        {
            if ((MN_CALL_DIR_MO == pstCallCtx->astCallEntity[i].enDir) &&
                (IMSA_CALL_TYPE_EMC != pstCallCtx->astCallEntity[i].enType))
            {
                return IMSA_TRUE;
            }
        }
    }
    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_CallIsExitMoNormalCall
 Description    : 释放CALL的公共处理
 Input          : pstCallEntity----------CALL实体指针
                  ulResult---------------原因值
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.wangchen 00209181   2015-11-28  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallIsExitEmcCall()
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx  = IMSA_CallCtxGet();
    VOS_UINT32                          i = 0;

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if (VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed)
        {
            if ((MN_CALL_DIR_MO == pstCallCtx->astCallEntity[i].enDir) &&
                (IMSA_CALL_TYPE_EMC == pstCallCtx->astCallEntity[i].enType))
            {
                return IMSA_TRUE;
            }
        }
    }
    return IMSA_FALSE;
}
/*****************************************************************************
 Function Name  : IMSA_CallIsExitMoNormalCall
 Description    : 释放CALL的公共处理
 Input          : pstCallEntity----------CALL实体指针
                  ulResult---------------原因值
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.wangchen 00209181   2015-11-28  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallIsExitMtCall()
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx  = IMSA_CallCtxGet();
    VOS_UINT32                          i = 0;

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if (VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed)
        {
            if (MN_CALL_DIR_MT == pstCallCtx->astCallEntity[i].enDir)
            {
                return IMSA_TRUE;
            }
        }
    }
    return IMSA_FALSE;
}
/*****************************************************************************
 Function Name  : IMSA_CallReleaseMtCallBeforSendToSpm
 Description    : 释放CALL的公共处理
 Input          : pstCallEntity----------CALL实体指针
                  ulResult---------------原因值
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.wangchen 00209181    2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallReleaseMtCallBeforSendToSpm
(
    IMSA_CALL_ENTITY_STRU              *pstCallEntity
)
{
    IMSA_MT_STATUS_REPORT_STRU         *pstMtReport = VOS_NULL_PTR;

    /* report AT that we missed this call. */
    pstMtReport = (IMSA_MT_STATUS_REPORT_STRU*)IMSA_MEM_ALLOC(sizeof(IMSA_MT_STATUS_REPORT_STRU));
    if(VOS_NULL_PTR == pstMtReport)
    {
        IMSA_ERR_LOG("IMSA_CallReleaseCallCommonProc: alloc memory failure.");
        IMSA_CallEntityFree(pstCallEntity);
        return;
    }

    IMSA_MEM_SET_S(pstMtReport, sizeof(IMSA_MT_STATUS_REPORT_STRU), 0, sizeof(IMSA_MT_STATUS_REPORT_STRU));

    if(IMSA_FALSE != pstCallEntity->bitOpErrorInfo)
    {
        /* 修改函数入参 */
        pstMtReport->ulCauseCode = IMSA_CallTransImsErr2SpmErr(&pstCallEntity->stImsError.stErrorCode);
    }
    pstMtReport->enMtStatus = IMSA_MT_CALL_STATUS_LOST_ABNORMALLY;
    IMSA_UtilStrNCpy(pstMtReport->acNumber, pstCallEntity->stCallNumber.aucNumber, IMSA_CALL_NUMBER_MAX_NUM);
    IMSA_SndMsgAtMtStatusInd(pstMtReport);

    IMSA_MEM_FREE(pstMtReport);

    IMSA_CallEntityFree(pstCallEntity);

    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CallReleaseCallResourceCommonProc();
    #endif
}

/*****************************************************************************
 Function Name  : IMSA_CallReleaseCallCommonProc
 Description    : 释放CALL的公共处理
 Input          : pstCallEntity----------CALL实体指针
                  ulResult---------------原因值
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.lihong 00150010    2013-09-29  Draft Enact
      2.sunbing 49683      2013-10-16  Modify for SRVCC
*****************************************************************************/
VOS_VOID IMSA_CallReleaseCallCommonProc
(
    IMSA_CALL_ENTITY_STRU              *pstCallEntity,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx  = IMSA_CallCtxGet();
    VOS_UINT32                          i           = IMSA_NULL;

    /* 如果此CALL是未上报过INCOMING事件给SPM的MT CALL（即IsUsed为TRUE，
       但状态为IDLE，方向为MT），则不需要上报releasd事件 */
    if ((IMSA_CALL_STATUS_IDLE == pstCallEntity->enStatus )
        && (MN_CALL_DIR_MT == pstCallEntity->enDir))
    {
        IMSA_INFO_LOG1("IMSA_CallReleaseCallCommonProc:MT, status: ", pstCallEntity->enStatus);
        IMSA_CallReleaseMtCallBeforSendToSpm(pstCallEntity);
        return ;
    }

    /* 如果是被叫流程，且DSDS，且资源处于正在申请过程中，收到IMS上报的DISCONNECT事件，则直接释放，不需要
    给SPM上报discconnect事件 */
    if ((MN_CALL_DIR_MT == pstCallEntity->enDir) &&
        (IMSA_RESOURCE_STATUS_ACTIVE != IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL)))
    {
        IMSA_CallReleaseMtCallBeforSendToSpm(pstCallEntity);
        return;
    }


    /*如果SRVCC流程，该电话已转到CS域，则不上报给SPM，但是要释放call信息*/
    if(pstCallEntity->bitOpTransToCs == VOS_TRUE)
    {
        IMSA_INFO_LOG("IMSA_CallReleaseCallCommonProc:Call transfered to CS.");
        TLPS_PRINT2LAYER_INFO(IMSA_CallReleaseCallCommonProc_ENUM, 2);
        IMSA_CallEntityFree(pstCallEntity);
        if (IMSA_CallEntityGetUsedCount() == 0)
        {
            IMSA_CallSetNotReportAllReleasedFlag(IMSA_FALSE);

            /* 不存在CALL实体, 通知LRRC VOLTE电话结束 */
            IMSA_SndRrcVolteStatusNotify(IMSA_LRRC_VOLTE_STATUS_END);
        }
        #if (FEATURE_ON == FEATURE_DSDS)
        IMSA_CallReleaseCallResourceCommonProc();
        #endif
        return;
    }

    (VOS_VOID)IMSA_CallSendSpmReleasedEvt(  pstCallEntity,
                                            ulResult);

    IMSA_CallEntityFree(pstCallEntity);

    /* 如果不存在CALL（即IsUsed都为FALSE），或者只存在未上报INCOMING事件给SPM的
       MT CALL（即IsUsed为TRUE，但状态为IDLE，方向为MT），则上报
       MN_CALL_EVT_ALL_RELEASED事件 */
    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if ((VOS_FALSE == pstCallCtx->astCallEntity[i].bitOpIsUsed)
          ||((IMSA_CALL_STATUS_IDLE == pstCallCtx->astCallEntity[i].enStatus)
                && (MN_CALL_DIR_MT == pstCallCtx->astCallEntity[i].enDir)))
        {
            continue;
        }

        break;
    }

    if (IMSA_CALL_MAX_NUM == i)
    {
        /* 不存在CALL实体, 通知LRRC VOLTE电话结束 */
        IMSA_SndRrcVolteStatusNotify(IMSA_LRRC_VOLTE_STATUS_END);

        (VOS_VOID)IMSA_CallSendSpmAllReleasedEvt();
    }

    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CallReleaseCallResourceCommonProc();
    #endif
}

/*****************************************************************************
 Function Name  : IMSA_CallClearLocalAlertInfo
 Description    : 启动HIFI后，清除本地振铃信息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-10-11  Draft Enact
      2.wangchen 00209181   2015-07-30 Modify:DTS2015072500342
*****************************************************************************/
VOS_VOID IMSA_CallClearLocalAlertInfo(VOS_VOID )
{
    VOS_UINT32 i = 0;
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
            (VOS_TRUE== pstCallCtx->astCallEntity[i].bitOpLocalAlerting))
        {
            IMSA_INFO_LOG("IMSA_CallClearLocalAlertInfo: Clear Local Alert Info!");

            pstCallCtx->astCallEntity[i].bitOpLocalAlerting = VOS_FALSE;
        }
    }

}

/*****************************************************************************
 Function Name  : IMSA_CallIsNeedCsRedialSrvccSucc
 Description    : 判断SRVCC成功后此CALL是否有可能到CS域重播
 Input          : pstCallEntity----------CALL实体指针
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.lihong 00150010    2013-12-19  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallIsNeedCsRedialSrvccSucc
(
    const IMSA_CALL_ENTITY_STRU        *pstCallEntity
)
{
    if (IMSA_TRUE != IMSA_CallGetNotReportAllReleasedFlag())
    {
        return IMSA_FALSE;
    }

    if (MN_CALL_DIR_MO != pstCallEntity->enDir)
    {
        return IMSA_FALSE;
    }

    if ((IMSA_CALL_STATUS_DIALING != pstCallEntity->enStatus)
        && (IMSA_CALL_STATUS_TRYING != pstCallEntity->enStatus))
    {
        return IMSA_FALSE;
    }

    return IMSA_TRUE;
}
/*****************************************************************************
 Function Name  : IMSA_CallIsResourceReady
 Description    : 判断呼叫所需要的资源是否已经预留成功
 Input          : pstCallEntity----------CALL实体指针
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.wangchen 00209181   2014-06-23  Draft Enact
      2.wangchen 00209181   2015-03-17  Modify:volte
*****************************************************************************/
IMSA_CALL_CALL_REASON_RESOURCE_RESULT_ENUM_UINT8 IMSA_CallIsResourceReady
(
    IMSA_CALL_ENTITY_STRU              *pstCallEntity
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx = IMSA_CallCtxGet();

    /* 根据call类型，判断所需要的资源是否已经预留成功 */
    /* 不论哪种类型的call都需要语音类型的承载。 只要语音承载不存在，资源预留结果肯定为失败。*/
    if (IMSA_FALSE == pstCallCtx->ucVoiceBearExistFlag)
    {
        return IMSA_CALL_CALL_REASON_RESOURCE_FAILED;
    }

    if ((IMSA_CALL_TYPE_VOICE == pstCallEntity->enType)
        || ((IMSA_TRUE == pstCallCtx->ucVideoBearExistFlag) && (IMSA_CALL_TYPE_VIDEO == pstCallEntity->enType))
        || (IMSA_CALL_TYPE_EMC == pstCallEntity->enType))
    {
        return IMSA_CALL_CALL_REASON_RESOURCE_READY;
    }

    /* 如果是MO 视频电话，判断是否语音预留成功 */
    if ((IMSA_CALL_TYPE_VIDEO == pstCallEntity->enType) && (MN_CALL_DIR_MO == pstCallEntity->enDir))
    {
        if ((IMSA_TRUE == pstCallCtx->ucVoiceBearExistFlag) && (IMSA_FALSE == pstCallCtx->ucVideoBearExistFlag))
        {
            return IMSA_CALL_CALL_REASON_RESOURCE_ONLY_VOICE;
        }
    }

    return IMSA_CALL_CALL_REASON_RESOURCE_FAILED;
}

/*****************************************************************************
 Function Name  : IMSA_CallFindCauseInRedialCauseList
 Description    : 在IMS域内重播原因值列表中查找某原因值
 Input          : usSipStatusCode--------------SIP原因值
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010    2013-12-19  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallFindCauseInRedialCauseList
(
    VOS_UINT16                          usSipStatusCode
)
{
    IMSA_IMS_REDIAL_CFG_STRU           *pstImsRedialCfg = VOS_NULL_PTR;
    VOS_UINT32                          i               = IMSA_NULL;

    pstImsRedialCfg = IMSA_GetImsRedialCfgAddress();

    for (i = 0; i < pstImsRedialCfg->ucRedialCauseNum; i++)
    {
        if (usSipStatusCode == pstImsRedialCfg->ausRedialCauseList[i])
        {
            return IMSA_SUCC;
        }
    }

    return IMSA_FAIL;
}

/*****************************************************************************
 Function Name  : IMSA_CallIsNeedRedial
 Description    : 判定是否需要重播
 Input          : pstCallEntity-----------CALL实体指针
                  usSipStatusCode---------SIP原因值
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010    2013-12-19  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallIsNeedRedial
(
    const IMSA_CALL_ENTITY_STRU        *pstCallEntity,
    VOS_UINT16                          usSipStatusCode
)
{
    IMSA_IMS_REDIAL_CFG_STRU           *pstImsRedialCfg         = VOS_NULL_PTR;
    VOS_UINT32                          ulRedialMaxTimeRemainLen= IMSA_NULL;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx              = IMSA_CallCtxGet();

    /* IMS重播功能未打开，则不重播 */
    pstImsRedialCfg = IMSA_GetImsRedialCfgAddress();
    if (IMSA_FALSE == pstImsRedialCfg->ucIsCallRedialSupportFlg)
    {
        IMSA_INFO_LOG("IMSA_CallIsNeedRedial: ims redial not support");
        TLPS_PRINT2LAYER_INFO(IMSA_CallIsNeedRedial_ENUM, IMSA_NOT_SUPPORT);
        return IMSA_FALSE;
    }

    /* 如果正在释放，则不重播 */
    if (VOS_TRUE == pstCallEntity->stDiscDir.ucDiscCallFlag)
    {
        IMSA_INFO_LOG("IMSA_CallIsNeedRedial: releasing");
        TLPS_PRINT2LAYER_INFO(IMSA_CallIsNeedRedial_ENUM, IMSA_STATUS_RELEASING);
        return IMSA_FALSE;
    }

    /* 如果不是MO，则不重播 */
    if (MN_CALL_DIR_MO != pstCallEntity->enDir)
    {
        IMSA_INFO_LOG("IMSA_CallIsNeedRedial: not mo");
        TLPS_PRINT2LAYER_INFO(IMSA_CallIsNeedRedial_ENUM, 3);
        return IMSA_FALSE;
    }

    /* 状态不为DIALING和TRYING，则不重播 */
    if ((IMSA_CALL_STATUS_DIALING != pstCallEntity->enStatus)
        && (IMSA_CALL_STATUS_TRYING != pstCallEntity->enStatus))
    {
        IMSA_INFO_LOG("IMSA_CallIsNeedRedial: call state is not dailing or trying");
        TLPS_PRINT2LAYER_INFO(IMSA_CallIsNeedRedial_ENUM, IMSA_STATE_ERROR);
        return IMSA_FALSE;
    }

    /* 不在重播错误原因值列表中，则不重播 */
    if (IMSA_FAIL == IMSA_CallFindCauseInRedialCauseList(usSipStatusCode))
    {
        IMSA_INFO_LOG("IMSA_CallIsNeedRedial: not in redial cause list");
        TLPS_PRINT2LAYER_INFO(IMSA_CallIsNeedRedial_ENUM, 5);
        return IMSA_FALSE;
    }

    /* 重播次数已达最大次数，则不重播 */
    if (pstCallEntity->ucRedialTimes >= pstImsRedialCfg->ulCallRedialMaxNum)
    {
        IMSA_INFO_LOG("IMSA_CallIsNeedRedial: redial times is already max");
        TLPS_PRINT2LAYER_INFO(IMSA_CallIsNeedRedial_ENUM, 6);
        return IMSA_FALSE;
    }

    /* 获取当前定时器的剩余时间 */
    IMSA_GetRemainTimeLen(&pstCallCtx->stRedialMaxTimer, &ulRedialMaxTimeRemainLen);

    IMSA_INFO_LOG1("Get redial max timer remain time tick:", PS_GET_TICK());
    TLPS_PRINT2LAYER_INFO1(IMSA_CallIsNeedRedial_ENUM, IMSA_TICK, PS_GET_TICK());

    IMSA_INFO_LOG1("redial max timer length:", pstCallCtx->stRedialMaxTimer.ulTimerLen);
    TLPS_PRINT2LAYER_INFO1(IMSA_CallIsNeedRedial_ENUM, 7, pstCallCtx->stRedialMaxTimer.ulTimerLen);

    IMSA_INFO_LOG1("remain time:", ulRedialMaxTimeRemainLen);
    TLPS_PRINT2LAYER_INFO1(IMSA_CallIsNeedRedial_ENUM, 8, ulRedialMaxTimeRemainLen);

    /* 如果剩余重播时间小于重播间隔，则不重播 */

    if (ulRedialMaxTimeRemainLen < pstImsRedialCfg->ulCallRedialInterval)
    {
        IMSA_INFO_LOG("IMSA_CallIsNeedRedial: remain time < intervel time");
        TLPS_PRINT2LAYER_INFO(IMSA_CallIsNeedRedial_ENUM, 9);
        return IMSA_FALSE;
    }

    return IMSA_TRUE;
}
/*****************************************************************************
 Function Name  : IMSA_CallProcImsMsgDisconnect
 Description    : IMS DISCONNECT事件的处理
 Input          : pstOutputCallEvent      输出事件
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-09-02  Modify
      3.lihong 00150010    2013-12-20  Modify:SRVCC Buffer and Redial
      4.wangchen 00209181  2014-12-09  Modify:DTS2014112906255
*****************************************************************************/
VOS_VOID IMSA_CallProcImsMsgDisconnectNoErrInfo
(
    IMSA_CALL_ENTITY_STRU              *pstCallEntity
)
{
    TAF_CS_CAUSE_ENUM_UINT32            enSpmErr        = IMSA_NULL;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();

     /* 如果是SRVCC成功，且是MO CALL，且当前转该为DIALING或TRYING，
       则将原因值填为SRVCC_SUCC，由SPM决定是否到CS域重播 */
    if (IMSA_TRUE == IMSA_CallIsNeedCsRedialSrvccSucc(pstCallEntity))
    {
        enSpmErr = TAF_CS_CAUSE_IMSA_SRVCC_SUCC;
    }
    else if(VOS_TRUE == pstCallCtx->ucIsTcallTimeOutProc)
    {
        /*CMCC Tcall timer expires, delegate SPM to retry over CS domian.*/
        IMSA_INFO_LOG("Tcall time out, retry over CS.");
        TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgDisconnectNoErrInfo_ENUM, LNAS_TIMER_EXPIRED);
        /* 如果是视频呼叫，需要通知SPM呼叫类型转换为VOICE，去CS域重拨 */
        if (IMSA_CALL_TYPE_VIDEO == pstCallEntity->enType)
        {
            (VOS_VOID)IMSA_CallSendSpmCallTypeChangeInfoIndMsg(pstCallEntity->usClientId,
                                                                pstCallEntity->ulOpId,
                                                                pstCallEntity->ucSpmcallId,
                                                                pstCallEntity->enType,
                                                                MN_CALL_TYPE_VOICE,
                                                                IMSA_IMS_EMERGENCY_SUB_TYPE_NONE);
            pstCallEntity->enType = IMSA_CALL_TYPE_VOICE;
        }

        enSpmErr = TAF_CS_CAUSE_IMSA_CMCC_TCALL_TIMEOUT;
        pstCallCtx->ucIsTcallTimeOutProc = VOS_FALSE;

        #if (FEATURE_ON == FEATURE_PTM)
        /* 等新CHR生效后，删除旧的 */
        IMSA_CallFailErrRecord( pstCallEntity->enType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_TCALL_TIMEOUT,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_TCALL_TIMEOUT,
                                pstCallEntity,
                                VOS_FALSE);
        #endif
    }
    else if( (IMSA_TRUE == pstCallEntity->ucTqosExpFlag)
            && (MN_CALL_DIR_MO == pstCallEntity->enDir))
    {
        /* 如果是视频呼叫，需要通知SPM呼叫类型转换为VOICE，去CS域重拨 */
        if (IMSA_CALL_TYPE_VIDEO == pstCallEntity->enType)
        {
            (VOS_VOID)IMSA_CallSendSpmCallTypeChangeInfoIndMsg(pstCallEntity->usClientId,
                                                               pstCallEntity->ulOpId,
                                                               pstCallEntity->ucSpmcallId,
                                                               pstCallEntity->enType,
                                                               MN_CALL_TYPE_VOICE,
                                                               IMSA_IMS_EMERGENCY_SUB_TYPE_NONE);

            pstCallEntity->enType = IMSA_CALL_TYPE_VOICE;
        }
        /*CMCC Tqos timer expires, delegate SPM to retry over CS domian.*/
        IMSA_INFO_LOG("Tqos time out, retry over CS.");
        TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgDisconnectNoErrInfo_ENUM, 2);
        enSpmErr = TAF_CS_CAUSE_IMSA_CMCC_TQOS_TIMEOUT;

        /* ESR与ACK网侧同时收到，导致失败。正确方案是SIP消息处理完后SDK应通知IMSA，
           然后触发CSFB，但由于SDK架构比较复杂，SDK不想修改。最后经刘继武裁决，
           规避方案是当IMSA收到DISCONNECT后要延迟1秒，之后触发CSFB。虽影响用户体验
           但认为可以接受 */
        (VOS_VOID)TLPS_TaskDelay(1000);
        #if (FEATURE_ON == FEATURE_PTM)
        /* 等新CHR生效后，删除旧的 */
        IMSA_CallFailErrRecord( pstCallEntity->enType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_TQOS_TIMEOUT,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_TQOS_TIMEOUT,
                                pstCallEntity,
                                VOS_FALSE);
        #endif
    }
    else if (IMSA_TRUE == pstCallEntity->ucIsImsaRelCallFlag)
    {
        enSpmErr = TAF_CS_CAUSE_IMSA_ERROR;
    }
    else
    {
        enSpmErr = TAF_CS_CAUSE_SUCCESS;
    }

    IMSA_CallReleaseCallCommonProc(pstCallEntity, enSpmErr);

    if (IMSA_CallEntityGetUsedCount() == 0)
    {
        IMSA_SrvccSuccBuffProc();
    }

    return;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcImsMsgDisconnect
 Description    : IMS DISCONNECT事件的处理
 Input          : pstOutputCallEvent      输出事件
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-09-02  Modify
      3.lihong 00150010    2013-12-20  Modify:SRVCC Buffer and Redial
      4.wangchen 00209181  2014-12-09  Modify:DTS2014112906255
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsMsgDisconnect
(
    const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent
)
{
    IMSA_CALL_ENTITY_STRU              *pstCallEntity   = VOS_NULL_PTR;
    VOS_UINT32                          ulResult        = VOS_TRUE;
    TAF_CS_CAUSE_ENUM_UINT32            enSpmErr        = IMSA_NULL;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();
    IMSA_IMS_REDIAL_CFG_STRU           *pstImsRedialCfg = VOS_NULL_PTR;

    pstCallEntity = IMSA_CallEntityGetUsedByImsCallId((VOS_UINT32)pstOutputCallEvent->stCallReport.astCalls[0].ulCallIndex);
    if (VOS_NULL_PTR == pstCallEntity)
    {
        IMSA_ERR_LOG1("IMSA_CallProcImsMsgDisconnect: not found call entity ",
            pstOutputCallEvent->stCallReport.astCalls[0].ulCallIndex);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallProcImsMsgDisconnect_ENUM, IMSA_CALL_NOT_EXIST, pstOutputCallEvent->stCallReport.astCalls[0].ulCallIndex);

        return VOS_TRUE;
    }

    if (IMSA_FALSE != pstCallEntity->bitOpErrorInfo)
    {
        ulResult = IMSA_CallEntityProcErrorInfo(    pstCallEntity,
                                                    &pstCallEntity->stImsError);

        /* 根据返回值，决定是否向SPM发released事件 */
        if (VOS_TRUE != ulResult)
        {
            IMSA_INFO_LOG("IMSA_CallProcImsMsgDisconnect:Not report released event to spm!");
            TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgDisconnect_ENUM, 2);
            return VOS_TRUE;
        }

        /* 判定是否需要重播 */
        if ((IMSA_TRUE == IMSA_CallIsNeedRedial(pstCallEntity, pstCallEntity->stImsError.stErrorCode.usSipStatusCode)) &&
            (VOS_TRUE == IMSA_IsCurrentAccessTypeSupportIms()))
        {
            IMSA_INFO_LOG("IMSA_CallProcImsMsgDisconnect:redial!");
            TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgDisconnect_ENUM, IMSA_REDIAL);

            pstImsRedialCfg = IMSA_GetImsRedialCfgAddress();
            pstCallCtx->stRedialIntervelTimer.ulTimerLen = pstImsRedialCfg->ulCallRedialInterval;

            /* 索引和CALL ID都得放到para中，第8位放索引，高8位放CALL ID；
               记录CALL ID信息，为了防止在间隔定时器启动时，用户下释放这个CALL的动作 */
            pstCallCtx->stRedialIntervelTimer.usPara = pstCallEntity->ucSpmcallId << IMSA_MOVEMENT_8;
            pstCallCtx->stRedialIntervelTimer.usPara |= pstCallEntity->ucCallEntityIndex;
            IMSA_StartTimer(&pstCallCtx->stRedialIntervelTimer);

            /* 清除CALL ID，否则重播时IMS上报DAILING状态查找CALL实体时会查找不到;
               而且重播对于IMS不可见，因此IMS可能将重播的CALL ID重新分配给INCOMING
               CALL，如果这里不清CALL ID，则INCOMING CALL就直接能找到CALL实体，
               被误认为preconditon场景；
               但这里清除了CALL ID，则需要在打断重播流程时，即在IMSA_CallInterruptRedial
               函数中重新将间隔定时器中记录的CALLID写回CALL实体中，才能保证上报
               RELEASD事件时填写的CALL ID正确 */
            /* 由于重拨过程中，spmcallid并未发生变化，所以不需要在保存callid */
            pstCallEntity->ucImscallId = IMSA_CALL_INVALID_ID;
            return VOS_TRUE;
        }

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallErrRecord(pstCallEntity->stImsError.stErrorCode.usSipStatusCode, pstCallEntity);
        /* 等新CHR生效后，删除旧的 */
        IMSA_CallFailErrRecord( pstCallEntity->enType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_REMOTE,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_REMOTE,
                                pstCallEntity,
                                pstCallEntity->stImsError.stErrorCode.usSipStatusCode);
        #endif

        if ((IMSA_CALL_TYPE_VIDEO == pstCallEntity->enType)
            && (MN_CALL_DIR_MO == pstCallEntity->enDir))
        {
            (VOS_VOID)IMSA_CallSendSpmCallTypeChangeInfoIndMsg(pstCallEntity->usClientId,
                                                               pstCallEntity->ulOpId,
                                                               pstCallEntity->ucSpmcallId,
                                                               pstCallEntity->enType,
                                                               MN_CALL_TYPE_VOICE,
                                                               IMSA_IMS_EMERGENCY_SUB_TYPE_NONE);

            pstCallEntity->enType = IMSA_CALL_TYPE_VOICE;
        }

        /* 将IMS错误原因值转化为SPM错误原因值 */
        /* 修改函数入参 */
        enSpmErr = IMSA_CallTransImsErr2SpmErr(&pstCallEntity->stImsError.stErrorCode);

        IMSA_CallReleaseCallCommonProc(pstCallEntity, enSpmErr);

        if (IMSA_CallEntityGetUsedCount() == 0)
        {
            IMSA_SrvccSuccBuffProc();
        }
    }
    else
    {
        IMSA_CallProcImsMsgDisconnectNoErrInfo(pstCallEntity);
    }

    /* 清除DTMF信息 */
    if(TAF_CS_CAUSE_SUCCESS != IMSA_CallCheckUserDtmfCallId(0))
    {
        IMSA_CallClearDtmfInfo(TAF_CS_CAUSE_CALL_RELEASE);
    }

    IMSA_CommonDeregProc();
    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcImsMsgWaiting
 Description    : IMS WAITING事件的处理
 Input          : pstOutputCallEvent      D2输出事件
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsMsgWaiting(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent)
{

    /**
     * 同Incoming事件的处理，#IMSA_CallProcImsMsgIncomings
     */


    (VOS_VOID)pstOutputCallEvent;

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcMocallImsMsgInitializing
 Description    : IMS 初始化事件的处理
 Input          : pstOutputCallEvent      输出事件
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.wangchen 00209181   2015-12-01  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcMocallImsMsgInitializing
(
    const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent,
    IMSA_CALL_ENTITY_STRU              *pstCallEntity
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx = IMSA_CallCtxGet();
    IMSA_CALL_TYPE_ENUM_UINT8           enCallType = IMSA_CALL_TYPE_BUTT;

    pstCallEntity->ulResRspOpId = pstOutputCallEvent->ulOpId;

    /* 备份原来的呼叫类型 */
    enCallType = pstCallEntity->enType;

    /* 暂不实现承载修改场景下的precondition流程，只要是媒体承载存在就认为
       资源已具备，用于解决媒体承载建立比ims流程快的场景 */
    /* 更新呼叫实体 */
    IMSA_CallEntityUpdateByCallSummary(pstCallEntity, &(pstOutputCallEvent->stCallReport.astCalls[0]));

    /* 如果呼叫类型改变，需要通知SPM */
    if (enCallType != pstCallEntity->enType)
    {
        (VOS_VOID)IMSA_CallSendSpmCallTypeChangeInfoIndMsg(pstCallEntity->usClientId,
                                                           pstCallEntity->ulOpId,
                                                           pstCallEntity->ucSpmcallId,
                                                           (MN_CALL_TYPE_ENUM_U8)enCallType,
                                                           (MN_CALL_TYPE_ENUM_U8)pstCallEntity->enType,
                                                           IMSA_IMS_EMERGENCY_SUB_TYPE_NONE);
    }

    if (IMSA_CALL_CALL_REASON_RESOURCE_READY == IMSA_CallIsResourceReady(pstCallEntity))
    {
        IMSA_INFO_LOG("IMSA_CallProcImsMsgInitializing:call already exist,resource already!");
        TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgInitializing_ENUM, IMSA_EXISTED);
        TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgInitializing_ENUM, IMSA_RESOURCE_READY);

        (VOS_VOID)IMSA_CallSendImsMsgResRsp(pstCallEntity->ucImscallId,
                                            pstCallEntity->ulResRspOpId,
                                            IMSA_CALL_CALL_REASON_RESOURCE_READY);
    }
    else
    {
        IMSA_INFO_LOG("IMSA_CallProcImsMsgInitializing:call already exist,wati for resource!");
        TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgInitializing_ENUM, IMSA_EXISTED);
        TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgInitializing_ENUM, IMSA_RESOURCE_NOT_READY);

        /* 设置呼叫对应的资源标志位 */
        pstCallEntity->bitOpNeedSendResResult = IMSA_TRUE;

        /* 刷新等待资源建立定时器 */
        if(VOS_TRUE == IMSA_GetConfigParaAddress()->stCMCCCustomReq.ucCMCCCustomTqosFlag)
        {
            pstCallCtx->stResReadyTimer.ulTimerLen = IMSA_GetConfigParaAddress()->stCMCCCustomReq.ulTqosTimerLen;
        }
        IMSA_RegTimerRefresh(&pstCallCtx->stResReadyTimer, pstCallEntity->ucCallEntityIndex);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcMocallImsMsgInitializing
 Description    : IMS 初始化事件的处理
 Input          : pstOutputCallEvent      输出事件
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.wangchen 00209181   2015-12-01  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcMtcallImsMsgInitializing
(
    const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx = IMSA_CallCtxGet();
    IMSA_CALL_ENTITY_STRU              *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucRedialCallIndex   = IMSA_NULL;
    IMSA_CALL_ENTITY_STRU              *pstRedailCallEntity = VOS_NULL_PTR;

    pstCallEntity = IMSA_CallEntityAlloc();
    if (pstCallEntity)
    {
        /* 如果存在重拨流程，则打断重拨流程 */
        if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stRedialIntervelTimer))
        {
            ucRedialCallIndex   = (VOS_UINT8)pstCallCtx->stRedialIntervelTimer.usPara;
            if (ucRedialCallIndex < IMSA_CALL_MAX_NUM)
            {
                pstRedailCallEntity = &pstCallCtx->astCallEntity[ucRedialCallIndex];
                IMSA_CallInterruptRedial(pstRedailCallEntity);
            }
        }

        /* 更新呼叫实体 */
        IMSA_CallEntityUpdateByCallSummary(pstCallEntity, &(pstOutputCallEvent->stCallReport.astCalls[0]));

        pstCallEntity->ucImscallId = (VOS_UINT8)pstOutputCallEvent->stCallReport.astCalls[0].ulCallIndex;
        pstCallEntity->ulResRspOpId = pstOutputCallEvent->ulOpId;

        pstCallEntity->enStatus = IMSA_CALL_STATUS_IDLE;

        if (IMSA_RESOURCE_STATUS_ACTIVE == IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL))
        {
            if (IMSA_CALL_CALL_REASON_RESOURCE_READY == IMSA_CallIsResourceReady(pstCallEntity))
            {
                IMSA_INFO_LOG("IMSA_CallProcImsMsgInitializing:call already exist,resource already!");
                TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgInitializing_ENUM, IMSA_EXISTED);
                TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgInitializing_ENUM, IMSA_RESOURCE_READY);

                (VOS_VOID)IMSA_CallSendImsMsgResRsp(pstCallEntity->ucImscallId,
                                                    pstCallEntity->ulResRspOpId,
                                                    IMSA_CALL_CALL_REASON_RESOURCE_READY);
            }
            else
            {
                IMSA_INFO_LOG("IMSA_CallProcImsMsgInitializing:call not exist,wait for resource!");
                TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgInitializing_ENUM, IMSA_CALL_NOT_EXIST);
                TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgInitializing_ENUM, IMSA_RESOURCE_NOT_READY);

                /* 设置呼叫对应的资源标志位 */
                pstCallEntity->bitOpNeedSendResResult = IMSA_TRUE;

                /* 刷新等待资源建立定时器 */
                if(VOS_TRUE == IMSA_GetConfigParaAddress()->stCMCCCustomReq.ucCMCCCustomTqosFlag)
                {
                    pstCallCtx->stResReadyTimer.ulTimerLen = IMSA_GetConfigParaAddress()->stCMCCCustomReq.ulTqosTimerLen;
                }
                IMSA_RegTimerRefresh(&pstCallCtx->stResReadyTimer, pstCallEntity->ucCallEntityIndex);
            }
        }
        #if (FEATURE_ON == FEATURE_DSDS)
        else if (IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF == IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL))
        {
            (VOS_VOID)IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL,
                                                    IMSA_RF_RES_APPLY_TRIGER_SRC_MT_CALL,
                                                    IMSA_IMS_CALL_STATE_INITIALIZING,
                                                    VOS_FALSE);

            if (IMSA_CALL_CALL_REASON_RESOURCE_READY == IMSA_CallIsResourceReady(pstCallEntity))
            {
                IMSA_INFO_LOG("IMSA_CallProcImsMsgInitializing:call already exist,resource already!");
                TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgInitializing_ENUM, IMSA_EXISTED);
                TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgInitializing_ENUM, IMSA_RESOURCE_READY);

                (VOS_VOID)IMSA_CallSendImsMsgResRsp(pstCallEntity->ucImscallId,
                                                    pstCallEntity->ulResRspOpId,
                                                    IMSA_CALL_CALL_REASON_RESOURCE_READY);
            }
            else
            {
                IMSA_INFO_LOG("IMSA_CallProcImsMsgInitializing:call not exist,wait for resource!");
                TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgInitializing_ENUM, IMSA_CALL_NOT_EXIST);
                TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgInitializing_ENUM, IMSA_RESOURCE_NOT_READY);

                /* 设置呼叫对应的资源标志位 */
                pstCallEntity->bitOpNeedSendResResult = IMSA_TRUE;

                /* 刷新等待资源建立定时器 */
                if(VOS_TRUE == IMSA_GetConfigParaAddress()->stCMCCCustomReq.ucCMCCCustomTqosFlag)
                {
                    pstCallCtx->stResReadyTimer.ulTimerLen = IMSA_GetConfigParaAddress()->stCMCCCustomReq.ulTqosTimerLen;
                }
                IMSA_RegTimerRefresh(&pstCallCtx->stResReadyTimer, pstCallEntity->ucCallEntityIndex);
            }
        }
        else
        {
            (VOS_VOID)IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL,
                                                   IMSA_RF_RES_APPLY_TRIGER_SRC_MT_CALL,
                                                   IMSA_IMS_CALL_STATE_INITIALIZING,
                                                   VOS_FALSE);
        }
        #endif
        return VOS_TRUE;
    }
    else
    {
            /* 如果分配呼叫实体失败，则拒绝该呼叫 */
        (VOS_VOID)IMSA_CallImsCmdRel((VOS_UINT32)pstOutputCallEvent->stCallReport.astCalls[0].ulCallIndex,
                                        IMSA_IMS_CALL_REL_CAUSE_IMSA_ALLOC_ENTITY_FAIL);
    }
    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcImsMsgInitializing
 Description    : IMS 初始化事件的处理
 Input          : pstOutputCallEvent      输出事件
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-12-06  Modify:Emc dedicated
      3.lihong 00150010    2013-12-23  Modify:Redail
      4.wangchen 00209181  2014-12-09  Modify:DTS2014112906255
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsMsgInitializing(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent)
{
    IMSA_CALL_ENTITY_STRU              *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulResult = VOS_FALSE;


    pstCallEntity = IMSA_CallEntityGetUsedByImsCallId((VOS_UINT32)pstOutputCallEvent->stCallReport.astCalls[0].ulCallIndex);

    /* 如果找到对应的呼叫实体，则是MO呼叫的INITIALIZING事件 */
    if (pstCallEntity)
    {
        ulResult = IMSA_CallProcMocallImsMsgInitializing(pstOutputCallEvent, pstCallEntity);
    }
    /* 如果找不到对应的呼叫实体，则是MT呼叫的INITIALIZING事件 */
    else
    {

        /* 多方会议请求资源预留，上报的CallID IMSA不感知，直接下发资源预留结果 */
        if (IMSA_IMS_CALL_CONFERENCE == pstOutputCallEvent->stCallReport.astCalls[0].enMultiParty)
        {
            IMSA_INFO_LOG("IMSA_CallProcImsMsgInitializing:mpty+precondition!");
            TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgInitializing_ENUM, 3);
            (VOS_VOID)IMSA_CallSendImsMsgResRsp(pstOutputCallEvent->stCallReport.astCalls[0].ulCallIndex,
                                                pstOutputCallEvent->ulOpId,
                                                IMSA_CALL_CALL_REASON_RESOURCE_READY);
            return VOS_TRUE;
        }

        ulResult = IMSA_CallProcMtcallImsMsgInitializing(pstOutputCallEvent);

    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallImsSrvccState2TafCallState
 Description    : SRVCC呼叫状态到IMSA呼叫状态的映射
 Input          : enCallState   呼叫状态
 Output         :
 Return Value   : 映射的新状态，如果没有对应项，则原状态不变

 History        :
      1.sunbing 49683      2013-10-12  Draft Enact
*****************************************************************************/
CALL_IMSA_SRVCC_CALL_STATE_ENUM_UINT8 IMSA_CallImsSrvccState2TafCallState
(
    IMSA_IMS_CALL_STATE_ENUM_UINT8  enCallState
)
{
    CALL_IMSA_SRVCC_CALL_STATE_ENUM_UINT8  enMnCallState = 0;

    switch(enCallState)
    {
        case IMSA_IMS_CALL_STATE_ACTIVE:
            enMnCallState = CALL_IMSA_SRVCC_CALL_ACTIVE;
            break;

        case IMSA_IMS_CALL_STATE_HOLD:
            enMnCallState = CALL_IMSA_SRVCC_CALL_HELD;
            break;
        case IMSA_IMS_CALL_STATE_TRYING:
        case IMSA_IMS_CALL_STATE_DIALING:
            enMnCallState = CALL_IMSA_SRVCC_CALL_DIALING;
            break;

        case IMSA_IMS_CALL_STATE_ALERTING:
            enMnCallState = CALL_IMSA_SRVCC_CALL_ALERTING;
            break;

        case IMSA_IMS_CALL_STATE_INCOMING:
            enMnCallState = CALL_IMSA_SRVCC_CALL_INCOMING;
            break;

        case IMSA_IMS_CALL_STATE_WAITING:
            enMnCallState = CALL_IMSA_SRVCC_CALL_WAITING;
            break;

        case IMSA_IMS_CALL_STATE_ACTIVING:
            enMnCallState = CALL_IMSA_SRVCC_CALL_ACTVING;
            break;

        case IMSA_IMS_CALL_STATE_INITIALIZING:
        case IMSA_IMS_CALL_STATE_INVALID:
        default:
            IMSA_ERR_LOG1("IMSA_CallImsSrvccState2TafCallState: invalid mapping state", enCallState);
            TLPS_PRINT2LAYER_ERROR1(IMSA_CallImsSrvccState2TafCallState_ENUM, IMSA_STATE_ERROR, enCallState);

    }

    return enMnCallState;
}


/*****************************************************************************
 Function Name  : CALL_IMSA_GetSrvccCallInfo
 Description    :  IMSA提供的API，供TAF CALL模块调用。
                   CALL模块通知IMSA SRVCC启动时，CALL模块调用该函数，
                   用于获取SRVCC过程中转入CS域的呼叫信息。
                   入参内存由调用方分配，pstCallInfo指向的内存大小为CALL_IMSA_MAX_ENTITY_NUM*sizeof(CALL_IMSA_SRVCC_CALL_INFO_STRU)

 Input          : pucCallNum指向存放call个数内容，pstCallInfo指向call信息
 Output         :
 Return Value   : 0 失败，1 成功

 History        :
      1.sunbing 49683     2013-12-11  Draft Enact
*****************************************************************************/
VOS_UINT32 CALL_IMSA_GetSrvccCallInfo(VOS_UINT8* pucCallNum,
                                      CALL_IMSA_SRVCC_CALL_INFO_STRU* pstCallInfo)
{
    VOS_UINT8                               ucCount;
    IMSA_CALL_ENTITY_STRU                  *pstCallEntity     = VOS_NULL_PTR;
    IMSA_IMS_SRVCC_CALL_INFO_STRU          *pstSrvccCallInfo  = VOS_NULL_PTR;
    CALL_IMSA_SRVCC_CALL_INFO_STRU         *pstTmpCallInfo    = VOS_NULL_PTR;
    IMSA_IMS_SRVCC_CALL_LIST_STRU           stImsSrvccCallList= {0};

    if((pucCallNum == VOS_NULL_PTR)||(pstCallInfo == VOS_NULL_PTR))
    {
        IMSA_ERR_LOG("CALL_IMSA_GetSrvccCallInfo:Para is err!");
        TLPS_PRINT2LAYER_ERROR(CALL_IMSA_GetSrvccCallInfo_ENUM, LNAS_PARAM_INVALID);
        return VOS_FALSE;
    }

    /*初始化call个数*/
    *pucCallNum = 0;

    /*从IMS协议栈获取call列表*/
    stImsSrvccCallList.ulCallNum = 0;
    (VOS_VOID)IMSA_ImsWriteSrvccCallList((void*)&stImsSrvccCallList);

    /*判断获取列表信息是否合法，不合法则获取失败*/
    if((stImsSrvccCallList.ulCallNum > IMSA_IMS_EVENT_MAX_CALL_LIST_SIZE)
        ||(stImsSrvccCallList.ulCallNum == 0))
    {
        IMSA_ERR_LOG("CALL_IMSA_GetSrvccCallInfo:call not exist!");
        TLPS_PRINT2LAYER_ERROR(CALL_IMSA_GetSrvccCallInfo_ENUM, IMSA_CALL_NOT_EXIST);

        return VOS_FALSE;
    }

    pstTmpCallInfo = pstCallInfo;

    /*循环处理转到CS域的call信息*/
    for(ucCount = 0; ucCount < stImsSrvccCallList.ulCallNum; ucCount++)
    {
        pstSrvccCallInfo = &stImsSrvccCallList.astCallInfo[ucCount];

        /*根据call id找到呼叫实体*/
        pstCallEntity = IMSA_CallEntityGetUsedByImsCallId(pstSrvccCallInfo->ulCallIndex);
        if(VOS_NULL_PTR == pstCallEntity)
        {
            IMSA_ERR_LOG("CALL_IMSA_GetSrvccCallInfo: Call info err.");
            TLPS_PRINT2LAYER_ERROR(CALL_IMSA_GetSrvccCallInfo_ENUM, LNAS_ERROR);
            continue;
        }

        pstTmpCallInfo->ucCallId    = pstCallEntity->ucSpmcallId;

        pstTmpCallInfo->enCallState = \
              IMSA_CallImsSrvccState2TafCallState(pstSrvccCallInfo->enCallState);
        pstTmpCallInfo->ucTi        = pstSrvccCallInfo->ucTi;

        /*记录该call转到CS域*/
        pstCallEntity->bitOpTransToCs                       = VOS_TRUE;

        /*把call信息转成CS域需要的信息*/
        pstTmpCallInfo->clientId    = pstCallEntity->usClientId;
        pstTmpCallInfo->opId        = (VOS_UINT8)pstCallEntity->ulOpId;
        pstTmpCallInfo->enCallDir   = pstCallEntity->enDir;
        pstTmpCallInfo->enMptyState = pstCallEntity->enMpty;
        pstTmpCallInfo->ucEConferenceFlag = pstCallEntity->ucIsEconfFlag;
        pstTmpCallInfo->enCallMode  = pstCallEntity->enMode;

        if(IMSA_CALL_TYPE_EMC == pstCallEntity->enType)
        {
            pstTmpCallInfo->enCallType = MN_CALL_TYPE_EMERGENCY;
        }
        else
        {
            pstTmpCallInfo->enCallType = MN_CALL_TYPE_VOICE;
        }

        /*没有EarlyMedia标示，说明HIFI没有启动，或者没有网络振铃，需要本地振铃*/

        if(VOS_TRUE == pstCallEntity->bitOpLocalAlerting)
        {
            pstTmpCallInfo->ucLocalAlertedFlag = VOS_TRUE;
        }

        /* 更新主叫号码 */
        IMSA_CallCallNumberImsa2CS(&pstCallEntity->stCallNumber, \
                                   &pstTmpCallInfo->stCallNumber);

        /* 更新被叫号码 */
        IMSA_CallCalledNumberImsa2CS(&pstCallEntity->stCalledNumber, \
                                   &pstTmpCallInfo->stCalledNumber);

        /*Call个数增加，call信息指针偏移到下一个结构*/
        *pucCallNum += 1;
        pstTmpCallInfo ++;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 Function Name  : IMSA_CallProcImsMsgEmergencyInd
 Description    : SRVCC过程中，IMS上报转到CS域的call信息
 Input          : pstOutputCallEvent      s输出事件
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.sunbing 49683     2013-10-11  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsMsgSrvccCallList(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent)
{
    VOS_UINT8                               ucCount;
    VOS_UINT32                              ulCallNum;
    IMSA_CALL_ENTITY_STRU                  *pstCallEntity     = VOS_NULL_PTR;
    IMSA_IMS_SRVCC_CALL_INFO_STRU          *pstSrvccCallInfo  = VOS_NULL_PTR;
    CALL_IMSA_SRVCC_CALL_INFO_NOTIFY_STRU  *pstCallInfoNotify = VOS_NULL_PTR;
    IMSA_CALL_ECONF_SUMMARY_STRU           *pEconfSummary = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallProcImsMsgSrvccCallList is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgSrvccCallList_ENUM, LNAS_ENTRY);

    ulCallNum = pstOutputCallEvent->stSrvccCallList.ulCallNum;

    if(pstOutputCallEvent->stSrvccCallList.ulCallNum > IMSA_IMS_EVENT_MAX_CALL_LIST_SIZE)
    {
        ulCallNum = IMSA_IMS_EVENT_MAX_CALL_LIST_SIZE;
    }

    pstCallInfoNotify = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(CALL_IMSA_SRVCC_CALL_INFO_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstCallInfoNotify)
    {
        IMSA_ERR_LOG("IMSA_CallProcImsMsgSrvccCallList: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallProcImsMsgSrvccCallList_ENUM, LNAS_NULL_PTR);
        return VOS_TRUE;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstCallInfoNotify),
                    IMSA_GET_MSG_LENGTH(pstCallInfoNotify),
                    0,
                    IMSA_GET_MSG_LENGTH(pstCallInfoNotify));

    pstCallInfoNotify->ucCallNum = (VOS_UINT8)ulCallNum;

    pstCallInfoNotify->ucStartedHifiFlag = pstOutputCallEvent->stSrvccCallList.ucHifiStatus;

    /*循环处理转到CS域的call信息*/
    for(ucCount = 0; ucCount < ulCallNum; ucCount++)
    {
        pstSrvccCallInfo = (IMSA_IMS_SRVCC_CALL_INFO_STRU *)&pstOutputCallEvent->stSrvccCallList.astCallInfo[ucCount];

        /*根据call id找到呼叫实体*/
        pstCallEntity = IMSA_CallEntityGetUsedByImsCallId(pstSrvccCallInfo->ulCallIndex);
        if(VOS_NULL_PTR == pstCallEntity)
        {
            IMSA_ERR_LOG("IMSA_CallProcImsMsgSrvccCallList: Call info err.");
            TLPS_PRINT2LAYER_ERROR(IMSA_CallProcImsMsgSrvccCallList_ENUM, 1);
            continue;
        }

        pstCallInfoNotify->astCallInfo[ucCount].ucCallId    = pstCallEntity->ucSpmcallId;

        pstCallInfoNotify->astCallInfo[ucCount].enCallState = \
              IMSA_CallImsSrvccState2TafCallState(pstSrvccCallInfo->enCallState);
        pstCallInfoNotify->astCallInfo[ucCount].ucTi        = pstSrvccCallInfo->ucTi;

        /*记录该call转到CS域*/
        pstCallEntity->bitOpTransToCs                       = VOS_TRUE;

        /*把call信息转成CS域需要的信息*/
        pstCallInfoNotify->astCallInfo[ucCount].clientId    = pstCallEntity->usClientId;
        pstCallInfoNotify->astCallInfo[ucCount].opId        = (VOS_UINT8)pstCallEntity->ulOpId;
        pstCallInfoNotify->astCallInfo[ucCount].enCallDir   = pstCallEntity->enDir;
        pstCallInfoNotify->astCallInfo[ucCount].enMptyState = pstCallEntity->enMpty;
        pstCallInfoNotify->astCallInfo[ucCount].ucEConferenceFlag = pstCallEntity->ucIsEconfFlag;
        pstCallInfoNotify->astCallInfo[ucCount].enCallMode  = pstCallEntity->enMode;


        if(IMSA_CALL_TYPE_EMC == pstCallEntity->enType)
        {
            pstCallInfoNotify->astCallInfo[ucCount].enCallType = MN_CALL_TYPE_EMERGENCY;
        }
        else
        {
            pstCallInfoNotify->astCallInfo[ucCount].enCallType = MN_CALL_TYPE_VOICE;
        }


        /*没有EarlyMedia标示，说明HIFI没有启动，或者没有网络振铃，需要本地振铃*/
        if(VOS_TRUE == pstCallEntity->bitOpLocalAlerting)
        {
            pstCallInfoNotify->astCallInfo[ucCount].ucLocalAlertedFlag = VOS_TRUE;
        }

        /* 如果是普通的通话，直接填被叫号码等，如果是增强型类型的，需要通过IMS上报的被叫号码从
        被叫列表中查找对应的存储信息 */
        if (VOS_FALSE == pstCallEntity->ucIsEconfFlag)
        {
            /* 更新主叫号码 */
            IMSA_CallCallNumberImsa2CS(&pstCallEntity->stCallNumber, \
                                       &pstCallInfoNotify->astCallInfo[ucCount].stCallNumber);

            /* 更新被叫号码 */
            IMSA_CallCalledNumberImsa2CS(&pstCallEntity->stCalledNumber, \
                                       &pstCallInfoNotify->astCallInfo[ucCount].stCalledNumber);

            /* 更新连接号码 */
            IMSA_CallCallNumberImsa2CS(&pstCallEntity->stConnectNumber, \
                                       &pstCallInfoNotify->astCallInfo[ucCount].stConnectNumber);

            /* 更新转移号码 */
            IMSA_CallCallNumberImsa2CS(&pstCallEntity->stRedirectNumber, \
                                       &pstCallInfoNotify->astCallInfo[ucCount].stRedirectNumber);
        }
        else
        {
            pEconfSummary = IMSA_EconfCalledGetUsedByCalledNum(pstCallEntity,
                                                                (VOS_CHAR *)pstSrvccCallInfo->acNumber);
            if (VOS_NULL_PTR != pEconfSummary)
            {
                /* 更新主叫号码 */
                IMSA_CallCallNumberImsa2CS(&pEconfSummary->stCallNumber, \
                                           &pstCallInfoNotify->astCallInfo[ucCount].stCallNumber);

                /* 更新被叫号码 */
                IMSA_CallCalledNumberImsa2CS(&pEconfSummary->stCalledNumber, \
                                           &pstCallInfoNotify->astCallInfo[ucCount].stCalledNumber);

                /* 更新连接号码 */
                IMSA_CallCallNumberImsa2CS(&pEconfSummary->stConnectNumber, \
                                           &pstCallInfoNotify->astCallInfo[ucCount].stConnectNumber);

                /* 更新转移号码 */
                IMSA_CallCallNumberImsa2CS(&pEconfSummary->stRedirectNumber, \
                                           &pstCallInfoNotify->astCallInfo[ucCount].stRedirectNumber);

            }
        }
    }

    /* 赋值DTMF缓存 */
    pstCallInfoNotify->stDtmfBuffInfo.ucNum = IMSA_CallGetDtmfCnt();
    for(ucCount = 0; ucCount < IMSA_CallGetDtmfCnt(); ucCount++)
    {
        pstCallInfoNotify->stDtmfBuffInfo.astDtmf[ucCount].CallId
                = IMSA_CallGetDtmfBufList(ucCount).ucCallId;
        pstCallInfoNotify->stDtmfBuffInfo.astDtmf[ucCount].cKey
                = IMSA_CallGetDtmfBufList(ucCount).cKey;
        pstCallInfoNotify->stDtmfBuffInfo.astDtmf[ucCount].usOnLength
                = IMSA_CallGetDtmfBufList(ucCount).usOnLength;
        pstCallInfoNotify->stDtmfBuffInfo.astDtmf[ucCount].usClientId
                = IMSA_CallGetDtmfBufList(ucCount).usClientId;
        pstCallInfoNotify->stDtmfBuffInfo.astDtmf[ucCount].opId
                = IMSA_CallGetDtmfBufList(ucCount).ucSpmOpId;
    }

    /* 填写消息头 */
    IMSA_WRITE_CALL_MSG_HEAD(pstCallInfoNotify, ID_IMSA_CALL_SRVCC_CALL_INFO_NOTIFY);

    /* 调用消息发送函数 */
    IMSA_SND_MSG(pstCallInfoNotify);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcImsMsgEmergencyInd
 Description    : IMS 紧急呼通知事件的处理
 Input          : pstOutputCallEvent      输出事件
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsMsgEmergencyInd(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent)
{
    IMSA_CALL_ENTITY_STRU *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = IMSA_CallEntityGetUsedByImsCallId((VOS_UINT32)pstOutputCallEvent->stCallReport.astCalls[0].ulCallIndex);
    if (pstCallEntity)
    {
        pstCallEntity->enType = IMSA_CALL_TYPE_EMC;
    }
    else
    {
        IMSA_ERR_LOG1("IMSA_CallProcImsMsgEmergencyInd: not found call entity ",
            pstOutputCallEvent->stCallReport.astCalls[0].ulCallIndex);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallProcImsMsgSrvccCallList_ENUM, IMSA_CALL_NOT_EXIST, pstOutputCallEvent->stCallReport.astCalls[0].ulCallIndex);
    }

    return VOS_TRUE;
}
/*****************************************************************************
 Function Name  : IMSA_CallProcImsMsgModifyInd
 Description    : IMS 通知对端请求发起voice<->video的切换
 Input          : pstOutputCallEvent      输出事件
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.wangchen 00209181 2014-06-19   Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsMsgModifyStatusInd(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent)
{
    IMSA_SPM_CALL_MODIFY_STATUS_IND_STRU  *pstModifyStatusInd = VOS_NULL_PTR;
    IMSA_CALL_ENTITY_STRU                 *pstCallEntity = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallProcImsMsgModifyStatusInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgModifyStatusInd_ENUM, LNAS_ENTRY);

    pstCallEntity = IMSA_CallEntityGetUsedByImsCallId((VOS_UINT32)pstOutputCallEvent->stCallModify.ulCallIndex);

    if (VOS_NULL_PTR == pstCallEntity)
    {
        IMSA_ERR_LOG1("IMSA_CallProcImsMsgModifyStatusInd: not found call entity ",
            pstOutputCallEvent->stCallModify.ulCallIndex);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallProcImsMsgModifyStatusInd_ENUM, IMSA_CALL_NOT_EXIST, pstOutputCallEvent->stCallModify.ulCallIndex);
        return VOS_FALSE;
    }

    pstModifyStatusInd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CALL_MODIFY_STATUS_IND_STRU));

    if (VOS_NULL_PTR == pstModifyStatusInd)
    {
        IMSA_ERR_LOG("IMSA_CallProcImsMsgModifyStatusInd: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallProcImsMsgModifyStatusInd_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstModifyStatusInd),
                    IMSA_GET_MSG_LENGTH(pstModifyStatusInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstModifyStatusInd));

    /*lint -e734*/
    pstModifyStatusInd->callId = pstCallEntity->ucSpmcallId;

    pstModifyStatusInd->enVoiceDomain = TAF_CALL_VOICE_DOMAIN_IMS;
    pstModifyStatusInd->usClientId = MN_CLIENT_ALL;
    pstModifyStatusInd->ucOpId = 0;
    /*lint +e734*/
    pstModifyStatusInd->enModifyStatus = SPM_IMSA_CALL_MODIFY_REMOTE_USER_REQUIRE_TO_MODIFY;

    pstModifyStatusInd->enCurrCallType = pstOutputCallEvent->stCallModify.enSrcCallMode;
    pstModifyStatusInd->enExpectCallType = pstOutputCallEvent->stCallModify.enDstCallMode;

    /* 填写消息头 */
    IMSA_WRITE_CALL_MSG_HEAD(pstModifyStatusInd, ID_IMSA_SPM_CALL_MODIFY_STATUS_IND);

    /* 调用消息发送函数 */
    IMSA_SND_MSG(pstModifyStatusInd);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcImsMsgModifyInd
 Description    : IMS 响应UE发起的voice<->video的切换
 Input          : pstOutputCallEvent      输出事件
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.wangchen 00209181 2014-06-19  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsMsgModifyStatusBegin(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent)
{
    IMSA_SPM_CALL_MODIFY_STATUS_IND_STRU  *pstModifyStatusInd = VOS_NULL_PTR;
    IMSA_CALL_ENTITY_STRU                 *pstCallEntity = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallProcImsMsgModifyStatusBegin is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgModifyStatusBegin_ENUM, LNAS_ENTRY);

    pstCallEntity = IMSA_CallEntityGetUsedByImsCallId((VOS_UINT32)pstOutputCallEvent->stCallModify.ulCallIndex);

    if (VOS_NULL_PTR == pstCallEntity)
    {
        IMSA_ERR_LOG1("IMSA_CallProcImsMsgModifyStatusBegin: not found call entity ",
            pstOutputCallEvent->stCallModify.ulCallIndex);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallProcImsMsgModifyStatusBegin_ENUM, IMSA_CALL_NOT_EXIST, pstOutputCallEvent->stCallModify.ulCallIndex);
        return VOS_FALSE;
    }

    pstModifyStatusInd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CALL_MODIFY_STATUS_IND_STRU));

    if (VOS_NULL_PTR == pstModifyStatusInd)
    {
        IMSA_ERR_LOG("IMSA_CallProcImsMsgModifyStatusBegin: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallProcImsMsgModifyStatusBegin_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstModifyStatusInd),
                    IMSA_GET_MSG_LENGTH(pstModifyStatusInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstModifyStatusInd));
    /*lint -e734*/
    pstModifyStatusInd->callId = pstCallEntity->ucSpmcallId;

    pstModifyStatusInd->enVoiceDomain = TAF_CALL_VOICE_DOMAIN_IMS;
    pstModifyStatusInd->usClientId = MN_CLIENT_ALL;
    pstModifyStatusInd->ucOpId = 0;
    /*lint +e734*/
    pstModifyStatusInd->enModifyStatus = SPM_IMSA_CALL_MODIFY_PROC_BEGIN;

    pstModifyStatusInd->enCurrCallType = pstOutputCallEvent->stCallModify.enSrcCallMode;
    pstModifyStatusInd->enExpectCallType = pstOutputCallEvent->stCallModify.enDstCallMode;

    /* 填写消息头 */
    IMSA_WRITE_CALL_MSG_HEAD(pstModifyStatusInd, ID_IMSA_SPM_CALL_MODIFY_STATUS_IND);

    /* 调用消息发送函数 */
    IMSA_SND_MSG(pstModifyStatusInd);

    return VOS_TRUE;
}
/*****************************************************************************
 Function Name  : IMSA_CallProcImsMsgModifyInd
 Description    : IMS 响应UE发起的voice<->video的切换
 Input          : pstOutputCallEvent      输出事件
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.wangchen 00209181 2014-06-19  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsMsgModifyStatusEnd(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent)
{
    IMSA_SPM_CALL_MODIFY_STATUS_IND_STRU  *pstModifyStatusInd = VOS_NULL_PTR;
    TAF_CS_CAUSE_ENUM_UINT32                enSpmErr        = IMSA_NULL;
    IMSA_CALL_ENTITY_STRU                 *pstCallEntity = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallProcImsMsgModifyStatusEnd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgModifyStatusEnd_ENUM, LNAS_ENTRY);

    pstCallEntity = IMSA_CallEntityGetUsedByImsCallId((VOS_UINT32)pstOutputCallEvent->stCallModify.ulCallIndex);

    if (VOS_NULL_PTR == pstCallEntity)
    {
        IMSA_ERR_LOG1("IMSA_CallProcImsMsgModifyStatusInd: not found call entity ",
            pstOutputCallEvent->stCallModify.ulCallIndex);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallProcImsMsgModifyStatusEnd_ENUM, IMSA_CALL_NOT_EXIST, pstOutputCallEvent->stCallModify.ulCallIndex);
        return VOS_FALSE;
    }


    pstModifyStatusInd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CALL_MODIFY_STATUS_IND_STRU));

    if (VOS_NULL_PTR == pstModifyStatusInd)
    {
        IMSA_ERR_LOG("IMSA_CallProcImsMsgModifyStatusEnd: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallProcImsMsgModifyStatusEnd_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstModifyStatusInd),
                    IMSA_GET_MSG_LENGTH(pstModifyStatusInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstModifyStatusInd));

    /*lint -e734*/
    pstModifyStatusInd->callId = pstCallEntity->ucSpmcallId;

    pstModifyStatusInd->enVoiceDomain = TAF_CALL_VOICE_DOMAIN_IMS;
    pstModifyStatusInd->usClientId = MN_CLIENT_ALL;
    pstModifyStatusInd->ucOpId = 0;
    /*lint +e734*/
    pstModifyStatusInd->enModifyStatus = SPM_IMSA_CALL_MODIFY_PROC_END;

    if(IMSA_SUCC == pstOutputCallEvent->stCallModify.ucResult)
    {
        pstModifyStatusInd->enCause = TAF_CS_CAUSE_SUCCESS;
    }
    else
    {
        /* 修改函数入参 */
        enSpmErr = IMSA_CallTransImsErr2SpmErr(&pstOutputCallEvent->stCallModify.stErrorCode);

        pstModifyStatusInd->enCause = enSpmErr;
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_ModifyCallTypeErrRecord(pstCallEntity->enType, pstOutputCallEvent->stCallError.stErrorCode.usSipStatusCode);
        #endif
    }
    pstModifyStatusInd->enCurrCallType = pstOutputCallEvent->stCallModify.enSrcCallMode;
    pstModifyStatusInd->enExpectCallType = pstOutputCallEvent->stCallModify.enDstCallMode;

    /* 填写消息头 */
    IMSA_WRITE_CALL_MSG_HEAD(pstModifyStatusInd, ID_IMSA_SPM_CALL_MODIFY_STATUS_IND);

    /* 调用消息发送函数 */
    IMSA_SND_MSG(pstModifyStatusInd);

    return VOS_TRUE;
}


/*****************************************************************************
 Function Name  : IMSA_CallProcImsMsgEconfNotifyInd
 Description    : IMS 增强型多方通话的notify消息的处理
 Input          : pstCallEntity      对应的IMSA呼叫实体
                  pstCallSummary     对应的D2呼叫信息
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.wangchen 00209181   2014-12-15  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsMsgEconfNotifyInd(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent)
{
    IMSA_CALL_ENTITY_STRU                   *pstCallEntity = VOS_NULL_PTR;
    IMSA_CALL_ECONF_SUMMARY_STRU            *pEconfSummary = VOS_NULL_PTR;
    VOS_UINT8                               i = 0;
    VOS_UINT8                               ucSendNotifyFlag = VOS_FALSE;

    IMSA_INFO_LOG("IMSA_CallProcImsMsgEconfNotifyInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgEconfNotifyInd_ENUM, LNAS_ENTRY);

    pstCallEntity = IMSA_CallEntityGetUsedByImsCallId((VOS_UINT32)pstOutputCallEvent->stEconfNotifyInd.ulCallConfId);

    if (VOS_NULL_PTR == pstCallEntity)
    {
        IMSA_ERR_LOG1("IMSA_CallProcImsMsgEconfNotifyInd: not found call entity ",
            pstOutputCallEvent->stEconfNotifyInd.ulCallConfId);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallProcImsMsgEconfNotifyInd_ENUM, IMSA_CALL_NOT_EXIST, pstOutputCallEvent->stEconfNotifyInd.ulCallConfId);
        return VOS_FALSE;
    }

    /* 如果允许的最大个数 不同，则是IMS第一次上报notify，IMSA需要通知SPM */
    if (pstOutputCallEvent->stEconfNotifyInd.ucMaxUserNum != pstCallEntity->ucMaxUserNum)
    {
         ucSendNotifyFlag = VOS_TRUE;
         /* 更新允许的最大个数 */
        pstCallEntity->ucMaxUserNum = pstOutputCallEvent->stEconfNotifyInd.ucMaxUserNum;
    }

    /* 如果与会者个数发生变化，需要通知SPM */
    if (pstCallEntity->ucCurUserNum != pstOutputCallEvent->stEconfNotifyInd.ucCurUserNum)
    {
        ucSendNotifyFlag = VOS_TRUE;

        /* 更新当前用户个数 */
        pstCallEntity->ucCurUserNum = pstOutputCallEvent->stEconfNotifyInd.ucCurUserNum;
    }

    /* 更新呼叫实体 */
    for (i = 0; i < pstOutputCallEvent->stEconfNotifyInd.ucCurUserNum; i ++)
    {
        pEconfSummary = IMSA_EconfCalledGetUsedByCalledNum(pstCallEntity, (VOS_CHAR *)pstOutputCallEvent->stEconfNotifyInd.astCalls[i].acNumber);

        /* 如果IMS上报的与会者不在列表中，则需要将被叫号码添加到呼叫实体中,增强型多方通话和普通通话合并时，IMS会多报一个用户上来 */
        if (VOS_NULL_PTR == pEconfSummary)
        {
            continue;
        }

        /* 更新被叫号码 */
        IMSA_CallEntityUpdateCalledNumberByAscii((VOS_CHAR *)pstOutputCallEvent->stEconfNotifyInd.astCalls[i].acNumber,
                                                &pEconfSummary->stCalledNumber);

        /* 更新连接号码 */
        IMSA_CallEntityUpdateCallNumberByAscii((VOS_CHAR *)pstOutputCallEvent->stEconfNotifyInd.astCalls[i].acConnectNumber,
                                                &pEconfSummary->stConnectNumber);

        /* 更新状态 */
        if (pEconfSummary->enCallState != pstOutputCallEvent->stEconfNotifyInd.astCalls[i].enCallState )
        {
            ucSendNotifyFlag = VOS_TRUE;
            pEconfSummary->enCallState = pstOutputCallEvent->stEconfNotifyInd.astCalls[i].enCallState;

        }

        /* 更新display name */
        IMSA_MEM_CPY_S(   pEconfSummary->acAlpha,
                          (IMSA_IMS_ALPHA_STRING_SZ+1),
                          pstOutputCallEvent->stEconfNotifyInd.astCalls[i].acAlpha,
                          (IMSA_IMS_ALPHA_STRING_SZ+1));

        /* 更新错误码 */
        if (IMSA_OP_TRUE == pstOutputCallEvent->stEconfNotifyInd.astCalls[i].bitOpError)
        {
            pEconfSummary->bitOpErrorInfo = IMSA_OP_TRUE;
            IMSA_MEM_CPY_S( &pEconfSummary->stErrorCode,
                            sizeof(IMSA_IMS_OUTPUT_ERROR_STRU),
                            &pstOutputCallEvent->stEconfNotifyInd.astCalls[i].stErrorCode,
                            sizeof(IMSA_IMS_OUTPUT_ERROR_STRU));
        }
        else
        {
            pEconfSummary->bitOpErrorInfo = IMSA_OP_FALSE;
        }

    }

    /* 如果有与会者的状态发生变化，需要通知SPM */
    if (VOS_TRUE == ucSendNotifyFlag)
    {
        IMSA_CallSendSpmEconfNotifyInd(pstCallEntity);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 Function Name  : IMSA_CallProcImsMsgMtBegin
 Description    : 被叫INVITE事件的处理
 Input          : pstOutputCallEvent      IMS呼叫事件
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.mengchao 0077840   2015-03-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsMsgMtBegin(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent)
{
    IMSA_MT_STATUS_REPORT_STRU         *pstMtReport = VOS_NULL_PTR;

    IMSA_INFO_LOG("received invite msg.");

    //check call event.
    if(1 != pstOutputCallEvent->stCallReport.ulNumCalls)
    {
        IMSA_ERR_LOG1("IMSA_CallProcImsMsgMtBegin: invalid number of calls. ", pstOutputCallEvent->stCallReport.ulNumCalls);
        return VOS_FALSE;
    }

    if(IMSA_IMS_CALL_DIR_MOBILE_TERMINATED != pstOutputCallEvent->stCallReport.astCalls[0].enCallDirection)
    {
        IMSA_ERR_LOG1("IMSA_CallProcImsMsgMtBegin: invalid call direction. ", pstOutputCallEvent->stCallReport.astCalls[0].enCallDirection);
        return VOS_FALSE;
    }

    pstMtReport = (IMSA_MT_STATUS_REPORT_STRU*)IMSA_MEM_ALLOC(sizeof(IMSA_MT_STATUS_REPORT_STRU));
    if(VOS_NULL_PTR == pstMtReport)
    {
        IMSA_ERR_LOG("IMSA_CallProcImsMsgMtBegin: alloc memory fail.");
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S( pstMtReport,
                    sizeof(IMSA_MT_STATUS_REPORT_STRU),
                    0,
                    sizeof(IMSA_MT_STATUS_REPORT_STRU));

    pstMtReport->enMtStatus = IMSA_MT_CALL_STATUS_INVITE_RECEIVED;
    IMSA_UtilStrNCpy(pstMtReport->acNumber, pstOutputCallEvent->stCallReport.astCalls[0].acNumber, IMSA_CALL_NUMBER_MAX_NUM);

    //send msg to AT
    IMSA_SndMsgAtMtStatusInd(pstMtReport);

    IMSA_MEM_FREE(pstMtReport);
    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallIsProccessCallSwap
 Description    : 判断当前是否正在执行CALL SWAP操作
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : 如果是则返回VOS_TRUE, 否者返回VOS_FALSE

 History        :
      1.liuhua 212067      2013-07-20  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallIsProccessCallSwap(VOS_VOID)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    if ((IMSA_OP_TRUE == pstCallCtx->stSpmMsg.bitOpSpmMsg) &&
        (ID_SPM_IMSA_CALL_SUPS_CMD_REQ == pstCallCtx->stSpmMsg.ulSpmMsgId) &&
        (MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH == pstCallCtx->stSpmMsg.stParam.stSupsParam.enCallSupsCmd))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 Function Name  : IMSA_CallIsAllCallOnHold
 Description    : D2上报的所有呼叫状态是否都是HOLD
 Input          : pstOutputCallEvent      D2输出事件
 Output         : VOS_VOID
 Return Value   : 如果是，则返回VOS_TRUE;如果不是，则返回VOS_FALSE

 History        :
      1.liuhua 212067      2013-07-30  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallIsAllCallOnHold(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent)
{
    VOS_UINT32 i = 0;

    for (i = 0; i < pstOutputCallEvent->stCallReport.ulNumCalls; i++)
    {
        if (IMSA_IMS_CALL_STATE_HOLD != pstOutputCallEvent->stCallReport.astCalls[i].enCallState)
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallIsAllCallInConference
 Description    : D2上报的所有呼叫都在会议里
 Input          : pstOutputCallEvent      D2输出事件
 Output         : VOS_VOID
 Return Value   : 如果是，则返回VOS_TRUE;如果不是，则返回VOS_FALSE

 History        :
      1.lihong 00150010      2013-08-21  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallIsAllCallInConference(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent)
{
    VOS_UINT32 i = 0;

    for (i = 0; i < pstOutputCallEvent->stCallReport.ulNumCalls; i++)
    {
        if (IMSA_IMS_CALL_SINGLE_PARTY == pstOutputCallEvent->stCallReport.astCalls[i].enMultiParty)
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcImsStateInvalid
 Description    : IMS INVALID事件的处理
 Input          : pstOutputCallEvent      输出事件
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsStateInvalid(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary)
{
    /* 收到Invalid状态通知不做处理 */

    (VOS_VOID)pstCallEntity;
    (VOS_VOID)pstCallSummary;

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallImsState2ImsaState
 Description    : 呼叫状态到IMSA呼叫状态的映射
 Input          : enImsState      呼叫状态
 Output         : enOldState      之前状态
 Return Value   : 映射的新状态，如果没有对应项，则原状态不变

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
IMSA_CALL_STATUS_ENUM_UINT8 IMSA_CallImsState2ImsaState(IMSA_IMS_CALL_STATE_ENUM_UINT8 enImsState, IMSA_CALL_STATUS_ENUM_UINT8 enOldState)
{
    IMSA_CALL_STATUS_ENUM_UINT8 enNewState = enOldState;

    switch (enImsState)
    {
    case IMSA_IMS_CALL_STATE_ACTIVE:
        enNewState = IMSA_CALL_STATUS_ACTIVE;
        break;
    case IMSA_IMS_CALL_STATE_HOLD:
        enNewState = IMSA_CALL_STATUS_HELD;
        break;
    case IMSA_IMS_CALL_STATE_TRYING:
        enNewState = IMSA_CALL_STATUS_TRYING;
        break;
    case IMSA_IMS_CALL_STATE_DIALING:
        enNewState = IMSA_CALL_STATUS_DIALING;
        break;
    case IMSA_IMS_CALL_STATE_ALERTING:
        enNewState = IMSA_CALL_STATUS_ALERTING;
        break;
    case IMSA_IMS_CALL_STATE_INCOMING:
        enNewState = IMSA_CALL_STATUS_INCOMING;
        break;
    case IMSA_IMS_CALL_STATE_WAITING:
        enNewState = IMSA_CALL_STATUS_WAITING;
        break;
    case IMSA_IMS_CALL_STATE_INVALID:
    case IMSA_IMS_CALL_STATE_INITIALIZING:
    default:
        IMSA_ERR_LOG1("IMSA_CallImsState2ImsaState: invalid mapping state", enImsState);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallImsState2ImsaState_ENUM, IMSA_STATE_ERROR, enImsState);
    }

    return enNewState;
}

/*****************************************************************************
 Function Name  : IMSA_EconfImsState2ImsaState
 Description    : 呼叫状态到IMSA呼叫状态的映射
 Input          : enImsState      呼叫状态
 Output         : enOldState      之前状态
 Return Value   : 映射的新状态，如果没有对应项，则原状态不变

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
TAF_CALL_ECONF_STATE_ENUM_U8 IMSA_EconfImsState2CsState(IMSA_IMS_ECONF_CALLER_STATE_ENUM_UINT8 enImsState)
{
    TAF_CALL_ECONF_STATE_ENUM_U8 enNewState = TAF_CALL_ECONF_STATE_DISCONNECTED;

    switch (enImsState)
    {
    case IMSA_IMS_ECONF_CALLER_STATE_BOOK:
    case IMSA_IMS_ECONF_CALLER_STATE_PREDIALING:
        enNewState = TAF_CALL_ECONF_STATE_PREDIALING;
        break;
    case IMSA_IMS_ECONF_CALLER_STATE_DIALING:
        enNewState = TAF_CALL_ECONF_STATE_DIALING;
        break;
    case IMSA_IMS_ECONF_CALLER_STATE_HOLD:
        enNewState = TAF_CALL_ECONF_STATE_ONHOLD;
        break;
    case IMSA_IMS_ECONF_CALLER_STATE_AVTIVE:
        enNewState = TAF_CALL_ECONF_STATE_CONNECTED;
        break;
    case IMSA_IMS_ECONF_CALLER_STATE_DISCONNECT:
        enNewState = TAF_CALL_ECONF_STATE_DISCONNECTED;
        break;
    default:
        IMSA_ERR_LOG1("IMSA_EconfImsState2CsState: invalid mapping state", enImsState);
        TLPS_PRINT2LAYER_ERROR1(IMSA_EconfImsState2CsState_ENUM, IMSA_STATE_ERROR, enImsState);
    }

    return enNewState;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcImsStateActive
 Description    : IMS 呼叫状态(active)的处理
 Input          : pstCallEntity      对应的IMSA呼叫实体
                  pstCallSummary     对应的D2呼叫信息
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-12-23  Modify
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsStateActive(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary)
{
    IMSA_CALL_STATUS_ENUM_UINT8         enPreStatus = IMSA_CALL_STATUS_BUTT;
    IMSA_CALL_STATUS_ENUM_UINT8         enNewStatus = IMSA_CALL_STATUS_BUTT;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx  = IMSA_CallCtxGet();


    /**
     * 如果没有找到对应的呼叫实体，则挂断该呼叫
     * 这种场景下，是否需要保存IMS的呼叫并启动保护定时器？
     * 目前先简单来做，不保存，不启动保护定时器
     */

    /* 如果没有找到对应的呼叫实体，直接返回失败 */
    if (VOS_NULL_PTR == pstCallEntity)
    {
        return VOS_FALSE;
    }

    /* 如果重拨的CALL进入ACTIVE状态，则停止重拨相关定时器 */
    if ((VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stRedialMaxTimer))
        && (pstCallCtx->stRedialMaxTimer.usPara < IMSA_CALL_MAX_NUM))
    {
        if (pstCallEntity == &pstCallCtx->astCallEntity[pstCallCtx->stRedialMaxTimer.usPara])
        {
            IMSA_INFO_LOG("IMSA_CallProcImsStateActive stop redial timer");
            TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsStateActive_ENUM, LNAS_TIMER_STOP);

            /* 需要清错误原因值，否则CALL释放时上报RELEASE事件时携带原因值会出错 */
            pstCallEntity->bitOpErrorInfo = IMSA_OP_FALSE;

            IMSA_MEM_SET_S( &pstCallEntity->stImsError,
                            sizeof(IMSA_IMS_CALL_ERROR_STRU),
                            0,
                            sizeof(IMSA_IMS_CALL_ERROR_STRU));

            pstCallEntity->ucRedialTimes = 0;

            IMSA_StopTimer(&pstCallCtx->stRedialMaxTimer);
            IMSA_StopTimer(&pstCallCtx->stRedialIntervelTimer);
        }
    }

    /* 保存之前的状态 */
    enPreStatus = pstCallEntity->enStatus;

    /* IMS上报CALL状态为ACTIVE和ACTIVING状态时，都会进到该函数下处理；IMS上报ACTIVING状态时，需要直接当做
    ACTIVE处理，因此在状态转换时，入参直接传入IMSA_IMS_CALL_STATE_ACTIVE */
    enNewStatus = IMSA_CallImsState2ImsaState(IMSA_IMS_CALL_STATE_ACTIVE, enPreStatus);

    if (enPreStatus != enNewStatus)
    {
        /* 更新呼叫状态 */
        pstCallEntity->enStatus = enNewStatus;

        IMSA_CallEntityUpdateByCallSummary(pstCallEntity, pstCallSummary);

        IMSA_INFO_LOG1("IMSA_CallProcImsStateActive: MptyState1", pstCallEntity->enMpty);
        TLPS_PRINT2LAYER_INFO1(IMSA_CallProcImsStateActive_ENUM, 1, pstCallEntity->enMpty);

        /* 如果原状态是HELD，则通知SPM Retrieve事件 */
        if (enPreStatus == IMSA_CALL_STATUS_HELD)
        {
            (VOS_VOID)IMSA_CallSendSpmStateEvt( pstCallEntity->ucSpmcallId,
                                                pstCallEntity->usClientId,
                                                pstCallEntity->ulOpId,
                                                MN_CALL_EVT_RETRIEVE);
        }
        /* 如果状态发生变化，且原状态不是Active，则通知SPM CONNECT事件 */
        else
        {
            (VOS_VOID)IMSA_CallSendSpmStateEvt( pstCallEntity->ucSpmcallId,
                                                pstCallEntity->usClientId,
                                                pstCallEntity->ulOpId,
                                                MN_CALL_EVT_CONNECT);
        }

        /* 由于Alerting不是必须的消息, 所以网侧可能不下发Alerting, 若之前没有通知过LRRC Start,
           此时需要通知LRRC Start, LRRC收到该消息后,当信号质量不好时将提前上报A2/B2事件, 触发网侧提前下发Srvcc */
        if (VOS_FALSE == g_ulImsaNotifyRrcVoLteCallStartFlag)
        {
            IMSA_SndRrcVolteStatusNotify(IMSA_LRRC_VOLTE_STATUS_START);
        }

    }
    else
    {
        /* 多方会议拉人，原状态是ACTIVE，新状态仍是ACTIVE，只更新IMSA内部呼叫实体 */
        if (IMSA_IMS_CALL_CONFERENCE == pstCallSummary->enMultiParty)
        {
            IMSA_CallEntityUpdateByCallSummary(pstCallEntity, pstCallSummary);

            (VOS_VOID)IMSA_CallSendSpmStateEvt( pstCallEntity->ucSpmcallId,
                                                pstCallEntity->usClientId,
                                                pstCallEntity->ulOpId,
                                                MN_CALL_EVT_CONNECT);

            IMSA_INFO_LOG1("IMSA_CallProcImsStateActive: MptyState2", pstCallEntity->enMpty);
            TLPS_PRINT2LAYER_INFO1(IMSA_CallProcImsStateActive_ENUM, 2, pstCallEntity->enMpty);
        }
        /* 语音切视频时，如果切换成功，需要更新call类型 */
        if (pstCallSummary->enCallMode != pstCallEntity->enType)
        {
            IMSA_CallEntityUpdateByCallSummary(pstCallEntity, pstCallSummary);

            (VOS_VOID)IMSA_CallSendSpmStateEvt( pstCallEntity->ucSpmcallId,
                                                pstCallEntity->usClientId,
                                                pstCallEntity->ulOpId,
                                                MN_CALL_EVT_CONNECT);
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 Function Name  : IMSA_CallAllStateWillBeHeld
 Description    : 判断将某个呼叫状态更新为HELD后，是否会导致所有呼叫均处于HELD状态
 Input          : ulWillChangedId    将要变更状态的呼叫Id
 Output         : VOS_VOID
 Return Value   : 如果是则返回VOS_TRUE, 如果不是则返回VOS_FALSE

 History        :
      1.liuhua 212067      2013-07-20  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallAllStateWillBeHeld(VOS_UINT32 ulWillChangedId)
{
    VOS_UINT32 ulUsedCallCount = 0;
    VOS_UINT32 ulHeldCallCount = 0;
    VOS_UINT32 ulNonHeldCallId = 0;
    VOS_UINT32 i = 0;
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    /* 遍历所有呼叫并统计信息 */
    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if (VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed)
        {
            ulUsedCallCount++;
            if (IMSA_CALL_STATUS_HELD == pstCallCtx->astCallEntity[i].enStatus)
            {
                ulHeldCallCount++;
            }
            else
            {
                ulNonHeldCallId = i;
            }
        }
    }

    /**
     * 如果可用呼叫和处于HELD状态呼叫数相差1，
     * 且相差的这个呼叫Id刚好等于将要变更状态的Id，则满足条件；否则返回失败
     */
    if ((ulUsedCallCount > 1) &&
        (ulUsedCallCount == ulHeldCallCount + 1) &&
        (ulNonHeldCallId == ulWillChangedId))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 Function Name  : IMSA_CallProcImsStateHeld
 Description    : IMS 呼叫状态(held)的处理
 Input          : pstCallEntity      对应的IMSA呼叫实体
                  pstCallSummary     对应的D2呼叫信息
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsStateHeld(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary)
{
    IMSA_CALL_STATUS_ENUM_UINT8 enPreStatus = IMSA_CALL_STATUS_BUTT;
    IMSA_CALL_STATUS_ENUM_UINT8 enNewStatus = IMSA_CALL_STATUS_BUTT;


    /* 如果没有找到对应的呼叫实体，直接返回失败 */
    if (VOS_NULL_PTR == pstCallEntity)
    {
        return VOS_FALSE;
    }

    enPreStatus = pstCallEntity->enStatus;
    enNewStatus = IMSA_CallImsState2ImsaState(pstCallSummary->enCallState, enPreStatus);

    /* 如果原状态和新状态不一致，则通知SPM HELD事件 */
    if (enPreStatus != enNewStatus)
    {
        /* 更新呼叫状态 */
        pstCallEntity->enStatus = enNewStatus;
        (VOS_VOID)IMSA_CallSendSpmStateEvt( pstCallEntity->ucSpmcallId,
                                            pstCallEntity->usClientId,
                                            pstCallEntity->ulOpId,
                                            MN_CALL_EVT_HOLD);
    }

    if(IMSA_CALL_STATUS_HELD == pstCallEntity->enStatus)
    {
        /* 清除DTMF信息 */
        IMSA_CallClearDtmfInfo(TAF_CS_CAUSE_CALL_ON_HOLD);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcImsStateTrying
 Description    : IMS 呼叫状态(trying)的处理
 Input          : pstCallEntity      对应的IMSA呼叫实体
                  pstCallSummary     对应的D2呼叫信息
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.wangchen 00209181  2015-07-02   Modify:非中移动定制版本也启动TCALL，所以需要删除中移动定制条件
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsStateTrying(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary)
{
    IMSA_CALL_STATUS_ENUM_UINT8 enPreStatus = IMSA_CALL_STATUS_BUTT;
    IMSA_CALL_STATUS_ENUM_UINT8 enNewStatus = IMSA_CALL_STATUS_BUTT;


    /* 如果没有找到对应的呼叫实体，直接返回失败 */
    if (VOS_NULL_PTR == pstCallEntity)
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == IMSA_CallCtxGet()->ucIsTcallTimeOutProc)
    {
        IMSA_INFO_LOG("Filter trying msg while Tcall time out.");
        TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsStateTrying_ENUM, LNAS_TIMER_EXPIRED);
        return VOS_FALSE;
    }

    enPreStatus = pstCallEntity->enStatus;
    enNewStatus = IMSA_CallImsState2ImsaState(pstCallSummary->enCallState, enPreStatus);

    /* 如果原状态和新状态不一致，则通知SPM PROC事件 */
    if (enPreStatus != enNewStatus)
    {
        /* 更新呼叫状态 */
        pstCallEntity->enStatus = enNewStatus;

        /* 通知SPM */
        (VOS_VOID)IMSA_CallSendSpmStateEvt( pstCallEntity->ucSpmcallId,
                                            pstCallEntity->usClientId,
                                            pstCallEntity->ulOpId,
                                            MN_CALL_EVT_CALL_PROC);
        if( VOS_TRUE == IMSA_IsTimerRunning(&(IMSA_CallCtxGet()->stNormalTcallTimer)))
        {
            IMSA_StopTimer(&(IMSA_CallCtxGet()->stNormalTcallTimer));
        }
        if (VOS_TRUE == IMSA_IsTimerRunning(&(IMSA_CallCtxGet()->stEmcTcallTimer)))
        {
            IMSA_StopTimer(&(IMSA_CallCtxGet()->stEmcTcallTimer));
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcImsStateDialing
 Description    : IMS 呼叫状态(dialing)的处理
 Input          : pstCallEntity      对应的IMSA呼叫实体
                  pstCallSummary     对应的D2呼叫信息
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsStateDialing(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary)
{
    IMSA_CALL_STATUS_ENUM_UINT8 enPreStatus = IMSA_CALL_STATUS_BUTT;
    IMSA_CALL_STATUS_ENUM_UINT8 enNewStatus = IMSA_CALL_STATUS_BUTT;


    if (pstCallEntity)
    {
        /* 保存呼叫之前状态 */
        enPreStatus = pstCallEntity->enStatus;
        enNewStatus = IMSA_CallImsState2ImsaState(pstCallSummary->enCallState, enPreStatus);

        /* 更新呼叫的其它部分 */
        IMSA_CallEntityUpdateByCallSummary(pstCallEntity, pstCallSummary);

        /* 如果原状态和新状态不一致，则通知SPM ORIG事件 */
        if (enPreStatus != enNewStatus)
        {
            /* 更新呼叫状态 */
            pstCallEntity->enStatus = enNewStatus;

            /* 通知SPM */
            (VOS_VOID)IMSA_CallSendSpmStateEvt( pstCallEntity->ucSpmcallId,
                                                pstCallEntity->usClientId,
                                                pstCallEntity->ulOpId,
                                                MN_CALL_EVT_ORIG);
            if(VOS_TRUE == IMSA_GetConfigParaAddress()->stCMCCCustomReq.ucCMCCCustomTcallFlag
               && VOS_TRUE == IMSA_CallCtxGet()->ucIsTcallTimeOutProc)
            {
                IMSA_INFO_LOG1("IMSA_CallProcImsStateDialing: Hang up call id: ", pstCallEntity->ucImscallId);
                TLPS_PRINT2LAYER_INFO1(IMSA_CallProcImsStateDialing_ENUM, IMSA_CALL_ID, pstCallEntity->ucImscallId);
                (VOS_VOID)IMSA_CallImsCmdRel(pstCallEntity->ucImscallId, IMSA_IMS_CALL_REL_CAUSE_TCALL_EXPIR);
                return VOS_TRUE;
            }
        }
    }
    else
    {
        /* MO CALL,IMSA将DIAL消息发给IMS，在收到IMS上报DIALING状态前，用户主动挂断电话，所以在收到IMS上报的DIAL状态后，需要
        通知IMS释放call */
        (VOS_VOID)IMSA_CallImsCmdRel(pstCallSummary->ulCallIndex, IMSA_IMS_CALL_REL_CAUSE_USER_REL);
        IMSA_ERR_LOG1("IMSA_CallProcImsStateDialing: not found call ", pstCallSummary->ulCallIndex);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallProcImsStateDialing_ENUM, IMSA_CALL_NOT_EXIST, pstCallSummary->ulCallIndex);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcImsStateAlerting
 Description    : IMS 呼叫状态(alerting)的处理
 Input          : pstCallEntity      对应的IMSA呼叫实体
                  pstCallSummary     对应的D2呼叫信息
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-12-23  Modify
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsStateAlerting(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary)
{
    IMSA_CALL_STATUS_ENUM_UINT8         enPreStatus = IMSA_CALL_STATUS_BUTT;
    IMSA_CALL_STATUS_ENUM_UINT8         enNewStatus = IMSA_CALL_STATUS_BUTT;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx  = IMSA_CallCtxGet();


    /* 如果没有找到对应的呼叫实体，直接返回失败 */
    if (VOS_NULL_PTR == pstCallEntity)
    {
        return VOS_FALSE;
    }

    /* 如果重拨的CALL进入ALERTING状态，则停止重拨相关定时器 */
    if ((VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stRedialMaxTimer))
        && (pstCallCtx->stRedialMaxTimer.usPara < IMSA_CALL_MAX_NUM))
    {
        if (pstCallEntity == &pstCallCtx->astCallEntity[pstCallCtx->stRedialMaxTimer.usPara])
        {
            IMSA_INFO_LOG("IMSA_CallProcImsStateAlerting stop redial timer");
            TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsStateAlerting_ENUM, LNAS_TIMER_STOP);

            /* 需要清错误原因值，否则CALL释放时上报RELEASE事件时携带原因值会出错 */
            pstCallEntity->bitOpErrorInfo = IMSA_OP_FALSE;

            IMSA_MEM_SET_S( &pstCallEntity->stImsError,
                            sizeof(IMSA_IMS_CALL_ERROR_STRU),
                            0,
                            sizeof(IMSA_IMS_CALL_ERROR_STRU));

            pstCallEntity->ucRedialTimes = 0;
            IMSA_StopTimer(&pstCallCtx->stRedialMaxTimer);
            IMSA_StopTimer(&pstCallCtx->stRedialIntervelTimer);
        }
    }

    enPreStatus = pstCallEntity->enStatus;
    enNewStatus = IMSA_CallImsState2ImsaState(pstCallSummary->enCallState, enPreStatus);

    /* 中移动定制 */
    /* 如果呼叫类型发生变化，则通知SPM，并更新呼叫实体 */
    if (pstCallEntity->enType != pstCallSummary->enCallMode)
    {


        (VOS_VOID)IMSA_CallSendSpmCallTypeChangeInfoIndMsg(pstCallEntity->usClientId,
                                                           pstCallEntity->ulOpId,
                                                           pstCallEntity->ucSpmcallId,
                                                           (MN_CALL_TYPE_ENUM_U8)pstCallEntity->enType,
                                                           (MN_CALL_TYPE_ENUM_U8)pstCallSummary->enCallMode,
                                                           IMSA_IMS_EMERGENCY_SUB_TYPE_NONE);

        pstCallEntity->enType = pstCallSummary->enCallMode;
    }

    /* 如果原状态和新状态不一致，或者振铃方式发生变化，则通知SPM ALERT事件 */
    if ((enPreStatus != enNewStatus) || (pstCallEntity->bitOpLocalAlerting != pstCallSummary->ucIsLocalAlertingFlag))
    {
        /* 更新网络振铃标识 */
        pstCallEntity->bitOpLocalAlerting = pstCallSummary->ucIsLocalAlertingFlag;

        /* 更新呼叫状态 */
        pstCallEntity->enStatus = enNewStatus;

        /* 通知是否本地振铃 */
        if (VOS_TRUE == pstCallEntity->bitOpLocalAlerting)
        {
            IMSA_CallSendSpmLocalAlertingInd(MN_CLIENT_ID_BROADCAST, VOS_TRUE);
        }
        /* lihong00150010 上报网络放音导致AT修改CODEC类型问题 begin */
        else
        {
            /* IMSA_CallSendSpmLocalAlertingInd(MN_CLIENT_ID_BROADCAST, VOS_FALSE); */
            IMSA_INFO_LOG("IMSA_CallProcImsStateAlerting: do not send ID_IMSA_SPM_CHANNEL_INFO_IND");
            TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsStateAlerting_ENUM, 2);
        }
        /* lihong00150010 上报网络放音导致AT修改CODEC类型问题 end */

        /* 通知SPM */
        (VOS_VOID)IMSA_CallSendSpmStateEvt( pstCallEntity->ucSpmcallId,
                                            pstCallEntity->usClientId,
                                            pstCallEntity->ulOpId,
                                            MN_CALL_EVT_ALERTING);

        /* 若之前没有通知过LRRC Start, 此时需要通知LRRC Start, LRRC收到该消息后,
           当信号质量不好时将提前上报A2/B2事件, 触发网侧提前下发Srvcc, 为了防止出
           现振铃前的Srvcc增多, 所以在Alering时通知LRRC Start */
        if (VOS_FALSE == g_ulImsaNotifyRrcVoLteCallStartFlag)
        {
            IMSA_SndRrcVolteStatusNotify(IMSA_LRRC_VOLTE_STATUS_START);
        }
    }

    return VOS_TRUE;

}

/*****************************************************************************
 Function Name  : IMSA_CallProcImsStateIncoming
 Description    : IMS 呼叫状态(incoming)的处理
 Input          : pstCallEntity      对应的IMSA呼叫实体
                  pstCallSummary     对应的D2呼叫信息
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-12-23  Modify:Redial
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsStateIncoming(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary)
{
    VOS_UINT32                          ulResult            = VOS_TRUE;
    IMSA_CALL_STATUS_ENUM_UINT8         enPreStatus         = IMSA_CALL_STATUS_BUTT;
    IMSA_CALL_STATUS_ENUM_UINT8         enNewStatus         = IMSA_CALL_STATUS_BUTT;
    IMSA_CALL_ENTITY_STRU              *pstRedailCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucRedialCallIndex   = IMSA_NULL;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx          = IMSA_CallCtxGet();
    TAF_CS_CAUSE_ENUM_UINT32            enSpmErr    = IMSA_NULL;

    /* 被叫统一在Incoming处理里通知LRRC VoLTE Call Start, LRRC收到该消息后,
        当信号质量不好时将提前上报A2/B2事件 */
    if (VOS_FALSE == g_ulImsaNotifyRrcVoLteCallStartFlag)
    {
        IMSA_SndRrcVolteStatusNotify(IMSA_LRRC_VOLTE_STATUS_START);
    }

    /* 如果能够找到呼叫实体，则认为之前在收到了INITIALIZING EVENT，在那里分配了呼叫实体 */
    if (pstCallEntity)
    {
        enPreStatus = pstCallEntity->enStatus;
        enNewStatus = IMSA_CallImsState2ImsaState(pstCallSummary->enCallState, enPreStatus);

        if (enPreStatus != enNewStatus)
        {
            pstCallEntity->enStatus = enNewStatus;

            /* 通知SPM */
            (VOS_VOID)IMSA_CallSendSpmStateEvt( pstCallEntity->ucSpmcallId,
                                                pstCallEntity->usClientId,
                                                pstCallEntity->ulOpId,
                                                MN_CALL_EVT_INCOMING);
        }
    }
    else
    /* 如果没有找到呼叫实体，则尝试分配呼叫实体 */
    {
        /* 如果存在重拨流程，则打断重拨流程 */
        if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stRedialIntervelTimer))
        {
            ucRedialCallIndex   = (VOS_UINT8)pstCallCtx->stRedialIntervelTimer.usPara;
            if (ucRedialCallIndex < IMSA_CALL_MAX_NUM)
            {
                pstRedailCallEntity = &pstCallCtx->astCallEntity[ucRedialCallIndex];
                IMSA_CallInterruptRedial(pstRedailCallEntity);
            }
        }

        /* 如果存在紧急重注册流程，需要通知Spm release事件 */
        if(IMSA_TRUE == pstCallCtx->ucRetryEmcRegFlag)
        {
            /* 如果是紧急呼叫收到#380，重新发起紧急呼叫时，收到ERROR，需要给SPM发送release事件 */
            pstCallEntity = &pstCallCtx->astCallEntity[pstCallCtx->ucCallEntityIndex];

            /* 修改函数入参 */
            enSpmErr = IMSA_CallTransImsErr2SpmErr(&pstCallEntity->stImsError.stErrorCode);

            pstCallEntity->ucSpmcallId = pstCallCtx->ucId;
            IMSA_CallReleaseCallCommonProc(pstCallEntity, enSpmErr);

            pstCallCtx->ucRetryEmcRegFlag = IMSA_FALSE;
            pstCallCtx->ucId = IMSA_NULL;
            pstCallCtx->ucCallEntityIndex = IMSA_NULL;
        }

        pstCallEntity = IMSA_CallEntityAlloc();
        if (pstCallEntity)
        {
            pstCallEntity->enStatus = IMSA_CallImsState2ImsaState(  pstCallSummary->enCallState,
                                                                    pstCallEntity->enStatus);

            /* 保存呼叫实体 */
            IMSA_CallEntityUpdateByCallSummary(pstCallEntity, pstCallSummary);


            if (IMSA_RESOURCE_STATUS_ACTIVE == IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL))
            {
                /* 通知SPM */
                (VOS_VOID)IMSA_CallSendSpmStateEvt( pstCallEntity->ucSpmcallId,
                                                    pstCallEntity->usClientId,
                                                    pstCallEntity->ulOpId,
                                                    MN_CALL_EVT_INCOMING);
            }
            #if (FEATURE_ON == FEATURE_DSDS)
            else if (IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF == IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL))
            {
                IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL,
                                              IMSA_RF_RES_APPLY_TRIGER_SRC_MT_CALL,
                                              IMSA_IMS_CALL_STATE_INCOMING,
                                              VOS_FALSE);

                (VOS_VOID)IMSA_CallSendSpmStateEvt( pstCallEntity->ucSpmcallId,
                                                    pstCallEntity->usClientId,
                                                    pstCallEntity->ulOpId,
                                                    MN_CALL_EVT_INCOMING);
            }
            else
            {
                IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL,
                                              IMSA_RF_RES_APPLY_TRIGER_SRC_MT_CALL,
                                              IMSA_IMS_CALL_STATE_INCOMING,
                                              VOS_FALSE);
            }
            #endif

        }
        else
        {
            /* 如果实体分配失败，则拒绝该呼叫 */
            (VOS_VOID)IMSA_CallImsCmdRel((VOS_UINT32)pstCallSummary->ulCallIndex, IMSA_IMS_CALL_REL_CAUSE_IMSA_ALLOC_ENTITY_FAIL);

            ulResult = VOS_FALSE;
        }
    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcImsStateWaiting
 Description    : IMS 呼叫状态(waiting)的处理
 Input          : pstCallEntity      对应的IMSA呼叫实体
                  pstCallSummary     对应的D2呼叫信息
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsStateWaiting(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary)
{
    return IMSA_CallProcImsStateIncoming(pstCallEntity, pstCallSummary);
}

/*****************************************************************************
 Function Name  : IMSA_CallProcImsStateInitializing
 Description    : IMS 呼叫状态(initializing)的处理
 Input          : pstCallEntity      对应的IMSA呼叫实体
                  pstCallSummary     对应的D2呼叫信息
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsStateInitializing(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary)
{
    /**
     * 暂不处理，逻辑均在INITIALIZING EVENT中进行
     */

    (VOS_VOID)pstCallEntity;
    (VOS_VOID)pstCallSummary;

    return VOS_TRUE;
}

/**
 * 收到IMS上报的呼叫状态处理函数，根据呼叫状态进行分别处理
 *
 * @param[in]   pstCallEntity   该呼叫对应的实体
 * @param[in]   pstCallSummary  该呼叫对应上报的信息
 *
 * \note
 * 这里的pstCallEntity可能会空指针，对应到无法找到对应呼叫实体的场景，
 * 各状态处理函数需要根据各自的逻辑来处理这种场景
 */
VOS_UINT32 IMSA_CallProcImsState(IMSA_CALL_ENTITY_STRU *pstCallEntity, const IMSA_IMS_CALL_SUMMARY_STRU *pstCallSummary)
{
    VOS_UINT32 ulResult = VOS_FALSE;


    switch(pstCallSummary->enCallState)
    {
    case IMSA_IMS_CALL_STATE_INVALID:
        ulResult = IMSA_CallProcImsStateInvalid(pstCallEntity, pstCallSummary);
        break;
    case IMSA_IMS_CALL_STATE_ACTIVE:
        ulResult = IMSA_CallProcImsStateActive(pstCallEntity, pstCallSummary);
        break;
    case IMSA_IMS_CALL_STATE_HOLD:
        ulResult = IMSA_CallProcImsStateHeld(pstCallEntity, pstCallSummary);
        break;
    case IMSA_IMS_CALL_STATE_TRYING:
        ulResult = IMSA_CallProcImsStateTrying(pstCallEntity, pstCallSummary);
        break;
    case IMSA_IMS_CALL_STATE_DIALING:
        ulResult = IMSA_CallProcImsStateDialing(pstCallEntity, pstCallSummary);
        break;
    case IMSA_IMS_CALL_STATE_ALERTING:
        ulResult = IMSA_CallProcImsStateAlerting(pstCallEntity, pstCallSummary);
        break;
    case IMSA_IMS_CALL_STATE_INCOMING:
        ulResult = IMSA_CallProcImsStateIncoming(pstCallEntity, pstCallSummary);
        break;
    case IMSA_IMS_CALL_STATE_WAITING:
        ulResult = IMSA_CallProcImsStateWaiting(pstCallEntity, pstCallSummary);
        break;
    case IMSA_IMS_CALL_STATE_INITIALIZING:
        ulResult = IMSA_CallProcImsStateInitializing(pstCallEntity, pstCallSummary);
        break;
    /* 接听过程中，IMSA不再将actving状态转换为active上报，避免接听过程中发生SRVCC，电话由接听状态
    切换为来电状态；以及界面显示接听，但是没有声音的问题；如果2.5s未收到网侧的200ok，AP侧会提示用户
    电话接听过程中 */
    case IMSA_IMS_CALL_STATE_ACTIVING:
        break;
    default:
        IMSA_ERR_LOG1("IMSA_CallProcImsState: invalid call state", pstCallSummary->enCallState);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallProcImsState_ENUM, IMSA_STATE_ERROR, pstCallSummary->enCallState);
        break;
    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcImsMsgCallList
 Description    : IMS CALL LIST事件的处理
 Input          : pstOutputCallEvent      输出事件
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcImsMsgCallList(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent)
{
    IMSA_CALL_ENTITY_STRU *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT32 i = 0;
    VOS_UINT32 ulResult = VOS_FALSE;
    /*IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();*/

    /**
     * 如果正在执行Call Swap操作，且本次状态跟新会导致所有呼叫状态均为HELD
     * 则不进行呼叫状态的更新，待后续通知后再进行更新
     */
    if ((VOS_TRUE == IMSA_CallIsProccessCallSwap()) &&
        (pstOutputCallEvent->stCallReport.ulNumCalls > 1) &&
        (VOS_TRUE == IMSA_CallIsAllCallOnHold(pstOutputCallEvent)) &&
        (VOS_FALSE == IMSA_CallIsAllCallInConference(pstOutputCallEvent)))
    {
        IMSA_INFO_LOG("IMSA_CallProcImsMsgCallList: skip temporary state notification");
        TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgCallList_ENUM, 1);

        ulResult = VOS_TRUE;
    }
    else
    {
        for (i = 0; i < pstOutputCallEvent->stCallReport.ulNumCalls; i++)
        {
            if (IMSA_IMS_CALL_STATE_DIALING == pstOutputCallEvent->stCallReport.astCalls[i].enCallState)
            {
                pstCallEntity = IMSA_CallEntityGetUsedByImsCallId(IMSA_CALL_INVALID_ID);
            }
            else
            {
                pstCallEntity = IMSA_CallEntityGetUsedByImsCallId((VOS_UINT32)pstOutputCallEvent->stCallReport.astCalls[i].ulCallIndex);
            }
            ulResult = IMSA_CallProcImsState(pstCallEntity, &pstOutputCallEvent->stCallReport.astCalls[i]);
        }
    }

    /* 只有在发生补充业务的呼叫实体存在，才需要上报 */
    if (VOS_TRUE == pstOutputCallEvent->bitOpSupsrvInfo)
    {
        pstCallEntity = IMSA_CallEntityGetUsedByImsCallId((VOS_UINT32)pstOutputCallEvent->stSupsrvInfo.ulCallIndex);
        if (VOS_NULL_PTR != pstCallEntity)
        {
            IMSA_CallProcImsSupsrvInfo(&pstOutputCallEvent->stSupsrvInfo, pstCallEntity->ucSpmcallId);
        }
    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallImsSupsrvInfo2TafSupsrvInfo
 Description    : IMS 补充业务类型到 TAF补充业务类型映射
 Input          : enSupsrvNotification   IMS补充业务类型
 Output         :
 Return Value   : 映射补充业务类型

 History        :
      1.wangchen 00209181   2013-12-19  Draft Enact
*****************************************************************************/
MN_CALL_SS_NOTIFY_CODE_ENUM_U8 IMSA_CallImsSupsrvInfo2TafSupsrvInfo
(
    IMSA_IMS_SUPSRV_CALL_NOTICE_ENUM_UINT32 enSupsrvNotification
)
{
    MN_CALL_SS_NOTIFY_CODE_ENUM_U8  enMnSupsrvNotification = MN_CALL_SS_NTFY_BUTT;

    IMSA_INFO_LOG1("IMSA_CallImsSupsrvInfo2TafSupsrvInfo: enSupsrvNotification = ", enSupsrvNotification);
    TLPS_PRINT2LAYER_INFO1(IMSA_CallImsSupsrvInfo2TafSupsrvInfo_ENUM, 1, enSupsrvNotification);

    switch(enSupsrvNotification)
    {
        case IMSA_IMS_SUPSRV_MO_CALL_BEING_FORWARDED:
            enMnSupsrvNotification = MN_CALL_SS_NTFY_BE_FORWORDED;
            break;

        case IMSA_IMS_SUPSRV_MO_CALL_IS_WAITING:
            enMnSupsrvNotification = MN_CALL_SS_NTFY_IS_WAITING;
            break;

        case IMSA_IMS_SUPSRV_MO_CALL_BE_DEFLECTED:
            enMnSupsrvNotification = MN_CALL_SS_NTFY_BE_DEFLECTED;
            break;

        case IMSA_IMS_SUPSRV_MT_CALL_IS_FORWARDED:
            enMnSupsrvNotification = MN_CALL_SS_NTFY_FORWORDED_CALL;
            break;

        case IMSA_IMS_SUPSRV_MT_CALL_IS_HELD:
            enMnSupsrvNotification = MN_CALL_SS_NTFY_ON_HOLD;
            break;

        case IMSA_IMS_SUPSRV_MT_CALL_IS_UNHELD:
            enMnSupsrvNotification = MN_CALL_SS_NTFY_RETRIEVED;
            break;

        case IMSA_IMS_SUPSRV_MT_CALL_JOINED_CONFCALL:
            enMnSupsrvNotification = MN_CALL_SS_NTFY_ENTER_MPTY;
            break;

        case IMSA_IMS_SUPSRV_MT_CALL_EXPLICIT_CALL_TRANSFER:
            enMnSupsrvNotification = MN_CALL_SS_NTFY_EXPLICIT_CALL_TRANSFER;
            break;

        case IMSA_IMS_SUPSRV_MT_CALL_IS_DEFLECTED_CALL:
            enMnSupsrvNotification = MN_CALL_SS_NTFY_DEFLECTED_CALL;
            break;

        default:
            IMSA_ERR_LOG1("IMSA_CallImsSupsrvInfo2TafSupsrvInfo: invalid SupsrvInfo", enSupsrvNotification);
            TLPS_PRINT2LAYER_ERROR1(IMSA_CallImsSupsrvInfo2TafSupsrvInfo_ENUM, LNAS_PARAM_INVALID, enSupsrvNotification);

    }
    return enMnSupsrvNotification;

}

/*****************************************************************************
 Function Name  : IMSA_CallProcImsSupsrvInfo()
 Description    : IMS补充业务的事件处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2013-12-19  Draft Enact
      2.wangchen 00209181   2014-12-01  Modify:DTS2014112906255
*****************************************************************************/
VOS_VOID IMSA_CallProcImsSupsrvInfo
(
    const IMSA_IMS_CALL_SUPSRV_INFO_STRU  *pstSupsrvInfo,
    VOS_UINT32                             ulCallId
)
{
    MN_CALL_SS_NOTIFY_CODE_ENUM_U8  enMnSupsrvNotification = 0;

    IMSA_INFO_LOG("IMSA_CallProcImsSupsrvInfo entered");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsSupsrvInfo_ENUM, LNAS_ENTRY);

    enMnSupsrvNotification = IMSA_CallImsSupsrvInfo2TafSupsrvInfo(pstSupsrvInfo->enSupsrvNotification);

    /* 如果SPM上报的补充业务类型错误，不需要报给SPM */
    if (MN_CALL_SS_NTFY_BUTT != enMnSupsrvNotification)
    {
        /* 同GU确认，CLIENT ID填为广播，OPID 填为0 */
        (VOS_VOID)IMSA_CallSendSpmSsNotifyEvt(MN_CLIENT_ALL,
                                              0,
                                              ulCallId,
                                              MN_CALL_EVT_SS_NOTIFY,
                                              TAF_CS_CAUSE_SUCCESS,
                                              enMnSupsrvNotification);
    }

}


/*****************************************************************************
 Function Name  : IMSA_ImsMsgCallEvent()
 Description    : D2IMS呼叫类型的事件处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-21  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ImsMsgCallEvent(VOS_VOID *pCallEvent)
{
    IMSA_IMS_OUTPUT_CALL_EVENT_STRU      *pstOutCall;
    VOS_UINT32                          ulIndex = 0;
    IMSA_IMS_CALL_MSG_ACTION_FUN        pfActionFun;

    pstOutCall = (IMSA_IMS_OUTPUT_CALL_EVENT_STRU *)pCallEvent;

    if (VOS_NULL_PTR == pstOutCall)
    {
        IMSA_ERR_LOG("IMSA_ImsMsgCallEvent: NULL message");
        TLPS_PRINT2LAYER_ERROR(IMSA_ImsMsgCallEvent_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_INFO_LOG1("IMSA_ImsMsgCallEvent: ", pstOutCall->enOutputCallReason);
    TLPS_PRINT2LAYER_INFO1(IMSA_ImsMsgCallEvent_ENUM, 2, pstOutCall->enOutputCallReason);

    for (ulIndex = 0; ulIndex < g_ulImsaImsCallMsgActTblLen; ulIndex++)
    {
        /* 通过MSG ID查找处理函数 */
        if(pstOutCall->enOutputCallReason == g_stImsaImsCallMsgActTbl[ulIndex].enOutputCallReason)
        {
            pfActionFun = g_stImsaImsCallMsgActTbl[ulIndex].pfActionFun;

            /* 有处理函数 */
            if (VOS_NULL_PTR != pfActionFun)
            {
                (VOS_VOID)(pfActionFun)(pstOutCall);
            }
        }
    }
}

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 Function Name  : IMSA_CallReleaseCallResourceCommonProc
 Description    : 释放CALL的公共处理
 Input          : pstCallEntity----------CALL实体指针
                  ulResult---------------原因值
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
       1.wangchen 00209181   2015-11-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallReleaseCallResourceCommonProc(VOS_VOID)
{
    if (PS_RRM_RF_SHARED != IMSA_Dsds_RRM_RfResourceIsShared())
    {
        return;
    }

    if (IMSA_FALSE == IMSA_CallIsExitMoNormalCall())
    {
        IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL);
    }

    if (IMSA_FALSE == IMSA_CallIsExitMtCall())
    {
        IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL);
    }

    if (IMSA_FALSE == IMSA_CallIsExitEmcCall())
    {
        IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL);
    }
}

#endif

/*lint +e961*/



#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaProcImsCallMsg.c */



