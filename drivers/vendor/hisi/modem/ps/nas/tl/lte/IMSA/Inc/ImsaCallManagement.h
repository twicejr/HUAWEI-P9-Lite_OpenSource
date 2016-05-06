/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : ImsaCallManagement.h
    Description : ImsaCallManagement.c头文件
    History     :
      1.sunbing 00049683    2013-06-19  Draft Enact


******************************************************************************/

#ifndef __IMSACALLMANAGEMENT_H__
#define __IMSACALLMANAGEMENT_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "ImsaEntity.h"
#include    "TafNvInterface.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
/* 27007 7.18章节规定CALL ID有效值为1-N，没有上限，因此将无效CALL ID定义为0；
   SPM在ORIG REQ、START DTMF、STOP DTMP以及SUS REQ等时都会将CALL ID指定为0，表示
   无效CALL ID */
#define IMSA_CALL_INVALID_ID            (0x0)
#define IMSA_CALL_FIND_SUCC             (0)
#define IMSA_CALL_FIND_SUCC_DTMF        (1)
#define IMSA_CALL_FIND_FAIL             (2)

/* 将资源预留定时器时长修改为2s */
#ifdef PS_ITT_PC_TEST_NAS
#define IMSA_CALL_TIMER_LEN_PROTECT     (10*1000)
#define IMSA_CALL_TIMER_LEN_WAIT_RES    (2*1000)
#else
#define IMSA_CALL_TIMER_LEN_PROTECT     (390*1000)
#define IMSA_CALL_TIMER_LEN_WAIT_RES    (10*1000)
#define IMSA_CALL_WAIT_RESOURCE_APPLY_CNF_LENGTH     5000

#endif

#define IMSA_CALL_AVAILABILITY_CHECK_RESULT_CONTINUE            0  /* 可以直接发起呼叫*/
#define IMSA_CALL_AVAILABILITY_CHECK_RESULT_REJECT              1  /* 直接回复拒绝 */
#define IMSA_CALL_AVAILABILITY_CHECK_RESULT_CACHED              2  /* 直接发起注册，等注册结果 */
#define IMSA_CALL_AVAILABILITY_CHECK_RESULT_NO_RF               3  /* 需要申请资源 */
#define IMSA_CALL_AVAILABILITY_CHECK_RESULT_APPLY_NOTNEED_WAIT  4  /* 发起资源申请后，直接发呼叫*/
#define IMSA_CALL_AVAILABILITY_CHECK_RESULT_WAIT_STATUS_IND     5
#define IMSA_CALL_AVAILABILITY_CHECK_RESULT_CACHED_NOTNEED_WAIT 6  /* 先发资源申请，然后直接注册 */


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
#define IMSA_DTMF_MIN_ONLENGTH          (70)                                    /* DTMF音最小时长 */




/*****************************************************************************
  5 STRUCT
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
/**
 * Declaration for global entity context
 */
extern IMSA_ENTITY_STRU *pgstImsaEntity;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
#define IMSA_CallCtxGet()                   (&pgstImsaEntity->stImsaCallManager)
#define IMSA_CallGetDtmfState()             (pgstImsaEntity->stImsaCallManager.stDtmfCtx.enDtmfState)
#define IMSA_CallSetDtmfState(enDtmfState)  (IMSA_CallGetDtmfState() = (enDtmfState))
#define IMSA_CallGetCurrentDtmfInfo()       (&pgstImsaEntity->stImsaCallManager.stDtmfCtx.stCurrentDtmf)

#define IMSA_CallGetDtmfCnt()               (pgstImsaEntity->stImsaCallManager.stDtmfCtx.ucDtmfCnt)
#define IMSA_CallGetDtmfBufList(ucIndex)    (pgstImsaEntity->stImsaCallManager.stDtmfCtx.stDtmfBufList[ucIndex])


extern VOS_UINT32 IMSA_CallProcSpmSupsReq();
extern VOS_UINT32 IMSA_CallProcSpmStartDtmfReq();
extern VOS_UINT32 IMSA_CallProcSpmStopDtmfReq();
extern VOS_UINT32 IMSA_CallProcSpmGetInfoReq();

extern VOS_UINT32 IMSA_CallImsMsgFind(VOS_UINT32 ulOpId);
extern VOS_VOID   IMSA_CallImsMsgClear(VOS_VOID);

extern VOS_VOID IMSA_CallSpmOrigReqMsgSave(const SPM_IMSA_CALL_ORIG_REQ_STRU *pstAppMsg);
extern VOS_VOID IMSA_CallSpmSupsCmdReqMsgSave
(
    const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU  *pstAppMsg
);
extern VOS_VOID   IMSA_CallSpmMsgClear(VOS_VOID);

extern IMSA_CALL_ENTITY_STRU* IMSA_CallEntityAlloc( VOS_VOID );
extern VOS_VOID   IMSA_CallEntityFree(IMSA_CALL_ENTITY_STRU *pstCallEntity);
extern IMSA_CALL_ENTITY_STRU* IMSA_CallEntityGetUsedByImsCallId(VOS_UINT32 ulCallId);
extern IMSA_CALL_ENTITY_STRU* IMSA_CallEntityGetUsedBySpmCallId(VOS_UINT32 ulCallId);


extern VOS_UINT32 IMSA_CallImsCmdRelAll(VOS_VOID);
extern VOS_UINT32 IMSA_CallImsCmdRel
(
    VOS_UINT32                              ulCallId,
    IMSA_IMS_CALL_REL_CAUSE_ENUM_UINT8      enRelCause

);

extern VOS_VOID IMSA_CallProcTimeoutProtect(const VOS_VOID *pTimerMsg);
extern VOS_VOID IMSA_CallProcTimeoutResReady(const VOS_VOID *pTimerMsg);
extern VOS_VOID IMSA_CallProcTimeoutDtmfDuration(const VOS_VOID *pTimerMsg);
extern VOS_VOID IMSA_CallProcTimeoutDtmfProtect(const VOS_VOID *pTimerMsg);
extern VOS_VOID IMSA_CallProcTimeoutRedialMaxTime(const VOS_VOID *pTimerMsg);
extern VOS_VOID IMSA_CallProcTimeoutRedialIntervel(const VOS_VOID *pTimerMsg);
extern VOS_VOID IMSA_CallProcTimeoutTCall(const VOS_VOID *pTimerMsg);
extern VOS_VOID IMSA_StartTcallTimer(const IMSA_CALL_ENTITY_STRU *pstCallEntity);
extern VOS_VOID IMSA_CallProcTimeoutEmcTCall(const VOS_VOID *pTimerMsg);
extern VOS_VOID IMSA_CallProcEmcTcallExpWhenEmcSrvEstablishSucc(VOS_VOID);

extern VOS_UINT32 IMSA_CallProcIntraMsgEmcCallSrvStatus(const VOS_VOID *pMsg);
extern VOS_UINT32 IMSA_CallProcIntraMsgNrmCallSrvStatus(const VOS_VOID *pMsg);

extern VOS_UINT32 IMSA_CallSendSpmStateEvt(VOS_UINT32 ulCallId,VOS_UINT16 usClientId,
                                          VOS_UINT32 ulOpId, MN_CALL_EVENT_ENUM_UINT32 enEvt);
extern VOS_UINT32 IMSA_CallSendSpmReleasedEvt
(
    const IMSA_CALL_ENTITY_STRU        *pstCallEntity,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
);
extern VOS_UINT32 IMSA_CallSendSpmSupsResultMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT32                          ulOpId,
    VOS_UINT32                          ulCallId,
    MN_CALL_SS_RESULT_ENUM_U8           enSsResult
);
extern VOS_UINT32 IMSA_CallSendSpmClccInfoCnf
(
    const IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU *pstMsg
);
extern VOS_VOID IMSA_CallSendSpmLocalAlertingInd(VOS_UINT16 usClientId,
                                                   VOS_UINT8 ucIsLocalAlerting);

extern VOS_UINT32 IMSA_CallSendIntraResultAction(IMSA_CALL_TYPE_ENUM_UINT8 enCallType,
                                                 IMSA_RESULT_ACTION_ENUM_UINT32 enAction);

extern VOS_UINT32 IMSA_CallSendIntraSrvccSucc(VOS_VOID);

extern VOS_UINT32 IMSA_CallSendImsMsgResRsp
(
    VOS_UINT32 ulCallId,
    VOS_UINT32 ulImsOpId,
    IMSA_CALL_CALL_REASON_RESOURCE_RESULT_ENUM_UINT8 enResResult
);

extern VOS_UINT32 IMSA_CallCtxInit(VOS_VOID);
extern VOS_UINT32 IMSA_CallCtxDeinit(VOS_VOID);

extern VOS_VOID   IMSA_ProcHifiExceptionNtf(VOS_VOID *pRcvMsg);

extern VOS_VOID IMSA_CallCalledNumberImsa2CS(const IMSA_CALLED_NUMBER_STRU *pstSrcNumber,
                                             MN_CALL_CALLED_NUM_STRU *pstDstNumber);
extern VOS_VOID IMSA_CallCallNumberImsa2CS(const IMSA_CALL_NUMBER_STRU *pstSrcNumber,
                                           MN_CALL_BCD_NUM_STRU *pstDstNumber);

extern VOS_VOID IMSA_CallEntityUpdateCallNumberByAscii(const VOS_CHAR *pcAddress,
                                                       IMSA_CALL_NUMBER_STRU *pstDstNumber);
extern VOS_VOID IMSA_CallEntityUpdateCalledNumberByAscii(const VOS_CHAR *pcAddress,
                                                         IMSA_CALLED_NUMBER_STRU *pstDstNumber);

extern VOS_VOID IMSA_CallEntityUpdateCalledNumber(const MN_CALL_CALLED_NUM_STRU *pstSrcNumber,
                                                  IMSA_CALLED_NUMBER_STRU *pstDstNumber);
extern VOS_UINT32 IMSA_CallSendSpmEvtAndCallInfo(VOS_UINT16 usClientId,
                                          VOS_UINT32 ulOpId,
                                          VOS_UINT32 ulCallId,
                                          MN_CALL_EVENT_ENUM_UINT32 enEvt,
                                          TAF_CS_CAUSE_ENUM_UINT32 ulResult);
extern VOS_VOID IMSA_ProcTafCallMsg(const VOS_VOID *pRcvMsg);
extern VOS_UINT32 IMSA_CallSendImsMsgSrvcc(IMSA_IMS_INPUT_CALL_REASON_ENUM_UINT32 enSrvccReason);
extern VOS_UINT32 IMSA_CallSendSpmEventMsg(const VOS_VOID  *pEvtData,
                                                     VOS_UINT16 usLen);
extern VOS_VOID IMSA_CallEntity2SpmCallInfo(const IMSA_CALL_ENTITY_STRU  *pstCallEntity,
                                            MN_CALL_EVENT_ENUM_UINT32  enEvt,
                                            MN_CALL_INFO_STRU *pstCallInfo);
extern MN_CALL_STATE_ENUM_UINT8 IMSA_CallImsaState2SpmState(IMSA_CALL_STATUS_ENUM_UINT8 enImsaState);
extern MN_CALL_NUM_TYPE_ENUM_U8 IMSA_CallImsaNumType2SpmNumType(IMSA_CALL_NUM_TYPE_ENUM_UINT8 enNumType);

extern VOS_UINT32 IMSA_CallCheckIsAllowNewOrig(VOS_VOID);
extern VOS_UINT32 IMSA_CallEmcCallAvailabilityCheck
(
    IMSA_EMC_CALL_TYPE_ENUM_UINT32 *penEmcType
);
extern VOS_UINT32 IMSA_CallNormalCallAvailabilityCheck
(
    MN_CALL_TYPE_ENUM_UINT8 enCallType
);
extern VOS_UINT32 IMSA_CallSendImsMsgDial(VOS_UINT32 ulCallId, const SPM_IMSA_CALL_ORIG_REQ_STRU     *pstAppMsg);
extern VOS_UINT32 IMSA_CallEntityGetUsedCount(VOS_VOID);
extern VOS_UINT32 IMSA_CallImsMsgSave(const IMSA_IMS_INPUT_CALL_EVENT_STRU *pstCallEvt);
extern IMSA_IMS_EMERGENCY_TYPE_ENUM_UINT8 IMSA_CallNum2EmcSubType(const MN_CALL_EMERGENCY_CAT_STRU *pstEmcCat);
extern MN_CALL_EMER_CATEGORG_TYPE_ENUM_U8 IMSA_CallEmcSubType2SPMEmcCat(const IMSA_IMS_EMERGENCY_TYPE_ENUM_UINT8 EmcSubType);
extern IMSA_IMS_CALL_CLIR_TYPE_ENUM_UINT8 IMSA_CallConverterClir2Ims(MN_CALL_CLIR_CFG_ENUM_UINT8 enClir);
extern VOS_UINT32 IMSA_CallSendSpmSsNotifyEvt
(
    VOS_UINT16 usClientId,
    VOS_UINT32 ulOpId,
    VOS_UINT32 ulCallId,
    MN_CALL_EVENT_ENUM_UINT32 enEvt,
    TAF_CS_CAUSE_ENUM_UINT32 ulResult,
    MN_CALL_SS_NOTIFY_CODE_ENUM_U8 enCode
);

extern VOS_VOID IMSA_CallCopyRemoteAddrForm(const MN_CALL_CALLED_NUM_STRU *pstCalledNum, VOS_CHAR *paucRemoteAddr);
extern VOS_VOID IMSA_CallConverterOrig2Ims(VOS_UINT32 ulCallId,
                                                  const MN_CALL_ORIG_PARAM_STRU*  pSpmParam,
                                                  IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent);
extern VOS_VOID IMSA_CallConverterSups2Ims(VOS_UINT32 ulCallId,
                                                   const MN_CALL_SUPS_PARAM_STRU*  pSpmParam,
                                                   IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent);


extern VOS_VOID IMSA_CallConverterResRsp2Ims
(
    VOS_UINT32 ulImsOpId,
    VOS_UINT32 ulCallId,
    IMSA_CALL_CALL_REASON_RESOURCE_RESULT_ENUM_UINT8 enResResult,
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent
);

extern VOS_UINT32 IMSA_CallInviteNewPtptAvailableCheck(VOS_VOID);

extern VOS_VOID IMSA_CallSpmInviteNewPtptReqMsgSave(const SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ_STRU *pstAppMsg);
extern VOS_VOID IMSA_CallConverterInviteNewPtpt2Ims(VOS_UINT32 ulCallId,
                                                            const MN_CALL_CALLED_NUM_STRU* pstCalledNum,
                                                            IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent);

extern VOS_UINT32 IMSA_CallSendImsMsgInviteNewPtpt
(
    VOS_UINT32 ulCallId,
    const SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ_STRU *pstAppMsg
);



extern VOS_UINT32 IMSA_CallSendImsMsgStartDtmf
(
    VOS_UINT32                          ulCallId,
    VOS_CHAR                            cKey,
    VOS_UINT32                          ulDuration
);
extern VOS_UINT32 IMSA_CallSendImsMsgStopDtmf
(
    VOS_UINT32                          ulCallId,
    VOS_CHAR                            cKey
);
extern VOS_UINT32 IMSA_CallSendImsMsgSups(VOS_UINT32 ulCallId, const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU     *pstAppMsg);
extern VOS_UINT32 IMSA_CallCmdRelAllEmc
(
    VOS_UINT8                           ucIsUserDisc,
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32  enNoSrvCause

);
extern VOS_UINT32 IMSA_CallCmdRelAllNormal
(
    VOS_UINT8                           ucIsUserDisc,
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32  enNoSrvCause
);
extern VOS_VOID IMSA_CallSaveCliendIdOpidWhenAnswerCall(const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU *pstAppMsg);
extern VOS_UINT32 IMSA_CallProcSpmMsgSupsBuidMpty(VOS_UINT32 ulCallId, const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU *pstAppMsg);
extern VOS_UINT32 IMSA_CallProcSpmMsgSupsHoldAllExpectX
(
    VOS_UINT32                              ulCallId,
    const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU  *pstAppMsg
);
extern VOS_UINT32 IMSA_CallProcSpmMsgSupsHoldActAcptOth
(
    VOS_UINT32                              ulCallId,
    const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU  *pstAppMsg
);
extern VOS_UINT32 IMSA_CallProcSpmMsgSupsRelAllCall
(
    VOS_UINT32                              ulCallId,
    const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU  *pstAppMsg
);
extern VOS_VOID IMSA_CallUpdateDiscCallDir(VOS_UINT32 ulCallId, VOS_UINT8 ucIsUser);
extern VOS_VOID IMSA_CallGetCallsByState(IMSA_CALL_STATUS_ENUM_UINT8 enStatus,
                                               VOS_UINT32 *pulNumOfCalls,
                                               VOS_UINT32 *pulCallIds);
extern VOS_UINT32 IMSA_CallProcSpmMsgSupsRelCallX
(
    VOS_UINT32                              ulCallId,
    const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU  *pstAppMsg
);
extern VOS_UINT32 IMSA_CallProcSpmMsgSupsRelActAcptOth
(
    VOS_UINT32                              ulCallId,
    const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU  *pstAppMsg
);
extern VOS_UINT32 IMSA_CallProcSpmMsgSupsRelHeldOrUdub
(
    VOS_UINT32                              ulCallId,
    const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU  *pstAppMsg
);
extern VOS_VOID IMSA_CallClearTransToCsInfo(VOS_VOID);
extern VOS_UINT32 IMSA_CallSendSpmStartDtmfRsltMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
);
extern VOS_UINT32 IMSA_CallSendSpmStopDtmfRsltMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
);
extern VOS_UINT32 IMSA_ProcSsacInfo
(
    MN_CALL_TYPE_ENUM_UINT8             enCallType
);
extern VOS_VOID IMSA_ProcCallSrvccSatusNoify(const VOS_VOID *pRcvMsg);
extern VOS_VOID IMSA_CallProcTimeoutDtmfDuration(const VOS_VOID *pTimerMsg);
extern TAF_CS_CAUSE_ENUM_UINT32  IMSA_CallCheckUserDtmfCallId(VOS_UINT8 ucCallId);
extern VOS_VOID  IMSA_CallRcvImsStopDtmfProtectTimerExp( VOS_VOID );
extern VOS_VOID  IMSA_CallRcvImsStartDtmfProtectTimerExp( VOS_VOID );
extern VOS_VOID IMSA_CallEntity2SpmCallInfoParam(const IMSA_CALL_ENTITY_STRU *pstCallEntity,                                                 MN_CALL_INFO_PARAM_STRU *pstCallInfoParam);
extern VOS_UINT32 IMSA_CallSendSpmAllReleasedEvt( VOS_VOID );
extern VOS_VOID  IMSA_CallReadCallEntityRedirectInfo
(
    const IMSA_CALL_ENTITY_STRU        *pstCallEntity,
    IMSA_SPM_CALL_GET_CLPR_CNF_STRU    *pstGetClprCnf
);
extern VOS_UINT32 IMSA_CallCheckDtmfKey
(
    VOS_CHAR                           *pckey
);
extern VOS_VOID IMSA_CallFillCurrentDtmfInfo
(
    VOS_UINT8                           ucCallId,
    VOS_CHAR                            cKey,
    VOS_UINT16                          usDuration,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucSpmOpid
);
extern VOS_VOID IMSA_CallInterruptRedial
(
    IMSA_CALL_ENTITY_STRU        *pstCallEntity
);

extern VOS_UINT32 IMSA_CallSendImsMsgModify
(
    const SPM_IMSA_CALL_MODIFY_REQ_STRU  *pstAppMsg
);
extern VOS_UINT32 IMSA_CallSendImsMsgAnswerRemoteModify
(
    const SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ_STRU  *pstAppMsg
);
extern VOS_UINT32 IMSA_CallTypeAvailabilityCheck(MN_CALL_TYPE_ENUM_UINT8 enCallType);
extern VOS_VOID IMSA_CallEntityUpdateCalledNumberByBcd
(
    MN_CALL_CALLED_NUM_STRU            *pstDialNumber,
    IMSA_CALLED_NUMBER_STRU              *pstCalledNumber
);

extern VOS_VOID IMSA_CallGetCurrentProcessingCallTypeByCallStatus
(
    IMSA_CALL_TYPE_ENUM_UINT8        *penCallType
);
extern VOS_UINT32 IMSA_CallSendImsMsgCreatEconf
(
    VOS_UINT32                              ulCallId,
    const SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU  *pstAppMsg
);
extern IMSA_CALL_ENTITY_STRU* IMSA_CallEntityGetUsedByEconfFlag(VOS_VOID);
extern VOS_VOID IMSA_CallSendSpmEconfNotifyInd
(
    IMSA_CALL_ENTITY_STRU* pstCallEntity
);
extern IMSA_CALL_ECONF_SUMMARY_STRU* IMSA_EconfCalledGetUsedByCalledNum
(
    IMSA_CALL_ENTITY_STRU              *pstCallEntity,
    VOS_CHAR                                 *pCalledNum
);
extern VOS_UINT32 IMSA_CallProcSpmMsgSupsEconfRelUser(VOS_UINT32 ulCallId, const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU *pstAppMsg);
extern VOS_UINT32 IMSA_CallSendImsMsgEconfAddUser
(
    VOS_UINT32                              ulCallId,
    const SPM_IMSA_CALL_ECONF_ADD_USERS_REQ_STRU  *pstAppMsg
);
extern VOS_VOID IMSA_CONN_ProcPcscfInvalid
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContext,
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContextOld
);
#if (FEATURE_ON == FEATURE_PTM)
extern VOS_VOID IMSA_SndCallErrLogInfo
(
    IMSA_ERR_LOG_CALL_FAIL_STRU  stImsCallRstEvent
);
extern VOS_VOID IMSA_CallErrRecord
(
    IMSA_ERR_LOG_CALL_FAIL_REASON_ENUM_UINT16       enCallFailReason,
    IMSA_CALL_ENTITY_STRU *pstCallEntity
);
extern VOS_VOID IMSA_NormCallErrRecord
(
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_ENUM_UINT16 enCallFailReason,
    IMSA_CALL_ENTITY_STRU                      *pstCallEntity,
    VOS_UINT16                                  usSipStatusCode
);
extern VOS_VOID IMSA_ModifyCallTypeErrRecord
(
    IMSA_ERR_LOG_CALL_TYPE_ENUM_UINT8   enCurCallType,
    VOS_UINT16                          usSipStatusCode
);
extern VOS_VOID IMSA_CallFailErrRecord
(
    IMSA_CALL_TYPE_ENUM_UINT8                       enType,
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_ENUM_UINT16  enNormCallFailReason,
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_ENUM_UINT16   enEmcCallFailReason,
    IMSA_CALL_ENTITY_STRU                           *pstCallEntity,
    VOS_UINT16                                      usSipStatusCode
);
extern IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_ENUM_UINT16 IMSA_CallTransImsaErr2ErrlogInfo
(
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32  enImsaErr
);
extern IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_ENUM_UINT16 IMSA_CallTransImsaEmcErr2ErrlogInfo
(
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32  enImsaErr
);
#endif
extern VOS_VOID IMSA_CallSrvccSuccProcSupsCmd(VOS_VOID);
extern IMSA_IMS_CALL_REL_CAUSE_ENUM_UINT8 IMSA_CallTransImsaErr2ImsInfo
(
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32  enImsaErr
);
/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of ImsaCallManagement.h */




