

#ifndef _NASEMMPUBUSUSPEND_H
#define _NASEMMPUBUSUSPEND_H


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "LRrcLNasInterface.h"
#include    "MmcLmmInterface.h"
#include    "NasLmmPubMFsm.h"


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
#define NAS_EMM_T3412EXP_NO                         0

#define NAS_EMM_SUSPEND_UPLAYER_NUM_CM              2
#define NAS_EMM_SUSPEND_UPLAYER_NUM_ALL             3
#define NAS_EMM_SUSPEND_UPLAYER_NUM_INITVALUE    0
#define NAS_EMM_PUBU_BIT_SLCT                       1
#define NAS_EMM_PUBU_BIT_NO_SLCT                    0

#define NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES           1
#define NAS_EMM_SUSPEND_GU_ACT_DOMAIN_NO            0
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID  NAS_EMM_ProcInterSystemTransferBearerInfo(VOS_VOID);
extern VOS_UINT32   NAS_EMM_PreProcMsgMmcSuspendReq( MsgBlock * pMsg );
extern VOS_VOID  NAS_EMM_ValidStateMsgMmcSuspendReq
(
    NAS_LMM_FSM_STATE_STRU *pstState
);
extern VOS_VOID  NAS_EMM_ProcMsResumeMsgMmcSuspendReq(VOS_VOID);
extern VOS_VOID  NAS_EMM_ProcRrcOriResumeMsgMmcSuspendReq(VOS_VOID);
extern VOS_UINT32   NAS_EMM_PreProcMsgRrcSuspendInd( MsgBlock * pMsg );
extern VOS_UINT32  NAS_EMM_PreProcMsgRrcSuspendRelCnf( MsgBlock * pMsg );
extern VOS_UINT32   NAS_EMM_ValidStateMsgLrrcSuspendInd(
                                        VOS_UINT32  ulMsgId,
                                  const VOS_VOID   *pMsgStru  );
extern VOS_UINT32   NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgSusRsp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  );
extern VOS_UINT32   NAS_EMM_MsSuspendSsMmcOriWaitOtherMsgSusRsp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  );
extern VOS_UINT32  NAS_EMM_MsSuspendSsMmcOrSyscfgOriWaitOtherMsgMmcDetachReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                     *pMsgStru
);

extern VOS_UINT32   NAS_EMM_MsSuspendSsWaitOtherMsgTimerExp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  );
extern VOS_UINT32   NAS_EMM_MsSuspendSsWaitEndMsgMmcResumeNotify(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  );
extern VOS_UINT32  NAS_EMM_MsSuspendSsWaitEndMsgMmcSuspendRelReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);

extern VOS_UINT32  NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcSuspendRelReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcDetachReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                            *pMsgStru
);

extern VOS_UINT32   NAS_EMM_MsSuspendSsWaitEndMsgWtEndTimerExp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  );
extern VOS_UINT32  NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  );
extern VOS_VOID     NAS_EMM_SaveLrrcSuspendPara( const LRRC_LMM_SUSPEND_IND_STRU  *pLrrcLmmSuspendInd );
extern VOS_VOID     NAS_EMM_SuspendInitRelResource( VOS_VOID);
extern VOS_VOID     NAS_EMM_SuspendEndRelResource( VOS_VOID);
extern VOS_VOID     NAS_EMM_SendMmcSuspendCnf(
                                    MMC_LMM_RESULT_ID_ENUM_UINT32 ulSuspendRst );
extern VOS_VOID     NAS_EMM_SendMmcSuspendInd(VOS_VOID );
extern VOS_VOID  NAS_EMM_SendMmcSuspendRelCnf(VOS_VOID );
extern VOS_VOID     NAS_EMM_SendEsmSuspendInd( VOS_VOID );
extern VOS_VOID     NAS_EMM_SendErabmSuspendInd( VOS_VOID );
extern VOS_VOID     NAS_EMM_SendLrrcSuspendReq( VOS_VOID );
extern VOS_VOID  NAS_EMM_SndLrrcSuspendRelReq( VOS_VOID );
extern VOS_VOID     NAS_EMM_SendLrrcSuspendRsp( LRRC_LNAS_RESULT_ENUM_UINT32 ulRst );
extern VOS_VOID     NAS_EMM_SuspendEndStateChng( VOS_VOID);
extern VOS_UINT32   NAS_EMM_PreProcMsgMmcActionRstReq( MsgBlock * pMsg );
extern VOS_VOID NAS_EMM_ProGuAttachRst( MsgBlock * pMsg );
extern VOS_VOID NAS_EMM_ProGuRauRst( MsgBlock * pMsg );
extern VOS_UINT32  NAS_EMM_PreProcMsgMmcActionRstReq( MsgBlock * pMsg );
extern VOS_UINT32  NAS_EMM_CheckMmcActionRstReqStateValid( VOS_VOID );
extern VOS_VOID  NAS_EMM_SaveGuActRstPara( MsgBlock * pMsg  );

extern VOS_VOID  NAS_EMM_GuActionMsgDistr( MsgBlock * pMsg  );
extern VOS_VOID  NAS_EMM_GuActionSendStatusInd( NAS_LMM_MAIN_STATE_ENUM_UINT16 enPreMainState );
extern VOS_VOID  NAS_EMM_GuAttachActionRej( MsgBlock * pMsg  );
extern VOS_VOID  NAS_EMM_GuActionDestStateDeregWriteEpsSecuContext( VOS_VOID );
extern VOS_UINT32  NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb( MsgBlock * pMsg  );
extern VOS_UINT32  NAS_EMM_CheckGuActReqDomainPsRstDomainPs( MsgBlock * pMsg  );
extern VOS_UINT32  NAS_EMM_CheckGuActReqDomainCombiRstDomainPs( MsgBlock * pMsg  );

extern VOS_UINT32  NAS_EMM_CheckMmUpStateAndLaiChange( MsgBlock * pMsg  );
extern VOS_UINT32  NAS_EMM_CheckGprsUpStateAndRaiChange( MsgBlock * pMsg  );
extern VOS_VOID  NAS_EMM_ProcCsDomainRetainPsDomainNull
(
    NAS_EMM_SUB_STATE_ENUM_UINT16   usSs
);
extern VOS_VOID  NAS_EMM_ProcPsDomainRetainCsDomainNull( VOS_VOID);

extern VOS_VOID  NAS_EMM_GuCombinedAndPsOnlyAttachRej( MsgBlock * pMsg  );
/*extern VOS_VOID  NAS_EMM_GuCombinedAttachPsOnlySucc( MsgBlock * pMsg  );*/
extern VOS_VOID  NAS_EMM_GuRauActionRej( MsgBlock * pMsg  );
extern VOS_VOID  NAS_EMM_GuCmbAndPsOnlyRauRej( MsgBlock * pMsg  );

extern VOS_VOID  NAS_EMM_GuLauActionRej( MsgBlock * pMsg  );
extern VOS_VOID  NAS_EMM_ProcGuLauAttemptCounter(MsgBlock * pMsg  );
/*extern VOS_VOID  NAS_EMM_GuCmbRauPsOnlyRej( MsgBlock * pMsg  );*/

extern VOS_VOID  NAS_EMM_ProcGuRauAttemptCounter (MsgBlock * pMsg );
extern VOS_UINT32  NAS_EMM_CheckGuMtDetachTypeImsi( MsgBlock * pMsg  );
extern VOS_UINT32  NAS_EMM_CheckGuMtDetachTypePsReAttNotRequ( MsgBlock * pMsg  );
extern VOS_UINT32  NAS_EMM_CheckGuMtDetachTypePsReAttRequ( MsgBlock * pMsg  );
extern VOS_VOID NAS_EMM_ProGuMtDetachRst( MsgBlock * pMsg );
extern VOS_VOID NAS_EMM_ProGuLocalDetachRst( MsgBlock * pMsg );
extern VOS_VOID NAS_EMM_ProGuMoDetachRst( MsgBlock * pMsg );
extern VOS_VOID NAS_EMM_ProGuLauRst
(
    MsgBlock                           *pstMsg
);

extern VOS_VOID NAS_EMM_ProGuCmRst
(
    MsgBlock                           *pstMsg
);
extern VOS_VOID NAS_EMM_ProGuAbortRst
(
    MsgBlock                           *pstMsg
);

extern VOS_VOID NAS_EMM_ProGuServiceRst( MsgBlock * pMsg );
extern VOS_VOID  NAS_EMM_GuActionClearRegInfo( VOS_UINT32 ulDelteRplmn );
extern VOS_VOID  NAS_EMM_ProcGuAttRejCause3( VOS_VOID );
extern VOS_VOID  NAS_EMM_ProcGuAttRejCause7( VOS_VOID );
extern VOS_VOID  NAS_EMM_ProcGuDettRejCause3(VOS_VOID);
extern VOS_VOID  NAS_EMM_ProcGuDettRejCause7( VOS_VOID );
extern VOS_VOID  NAS_EMM_ProcGuAttachRejCause11( VOS_VOID );
extern VOS_VOID  NAS_EMM_ProcGuAttachRejCause14( VOS_VOID );
extern VOS_VOID  NAS_EMM_ProcGuAttachAttemptCounterEq5( MsgBlock * pMsg );
extern VOS_VOID  NAS_EMM_ProcGuRauSerRejCause9( VOS_VOID );
extern VOS_VOID  NAS_EMM_ProcGuRauSerRejCause11( VOS_VOID );
extern VOS_VOID  NAS_EMM_ProcGuRauSerRejCause14( VOS_VOID );
extern VOS_VOID  NAS_EMM_ProcGuDettachRejCause11( VOS_VOID );
extern VOS_VOID  NAS_EMM_ProcGuDettachRejCause14( VOS_VOID );
extern VOS_VOID  NAS_EMM_ProcGuRauSerRejCause13( VOS_VOID );
extern VOS_UINT32  NAS_EMM_MsSuspendSsSysCfgOriWaitOtherMsgSusRsp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  );
extern VOS_UINT32  NAS_EMM_MsSuspendSsSyscfgWaitOtherMsgTimerExp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  );
extern VOS_VOID  NAS_LMM_ProcRrcSysCfgCnfBandNotSupport( VOS_VOID );
extern VOS_VOID  NAS_LMM_ProcRrcSysCfgCnfLteNotActive( VOS_VOID );
extern VOS_UINT32  NAS_LMM_ProcRrcSysCfgCnfNotSuspend(VOS_VOID);
extern VOS_UINT32  NAS_EMM_MsRegInitRcvLrrcSyscfgCnfProc(VOS_VOID);
extern VOS_UINT32  NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc(VOS_VOID);
extern VOS_UINT32  NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc(VOS_VOID);
extern VOS_UINT32  NAS_EMM_MsTauSerWaitRrcRelRcvLrrcSyscfgCnfProc(VOS_VOID);
extern VOS_UINT32  NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc(VOS_VOID);
VOS_UINT32  NAS_EMM_PreProcMmcSuspendRsp(MsgBlock *pMsg   );

extern VOS_UINT32  NAS_EMM_RcvLrrcSuspendInd( VOS_UINT32  ulMsgId,
                                  const VOS_VOID   *pMsgStru  );
extern VOS_UINT32  NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendMmcSusRsp(VOS_UINT32        ulMsgId,
                                                             VOS_VOID   *pMsgStru   );
extern VOS_UINT32  NAS_EMM_SsRrcOriWaitMmcSuspenTimerExp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  );

extern VOS_UINT32  NAS_EMM_MsSuspendSsSomeStatusMsgIntraTauReq( VOS_UINT32  ulMsgId,
                                    VOS_VOID   *pMsgStru  );
extern VOS_VOID NAS_EMM_MsRegInitRcvLrrcSuspendIndProc(const MsgBlock * pMsg );
extern VOS_VOID NAS_EMM_MsDeregInitRcvLrrcSuspendIndProc(const MsgBlock * pMsg );
extern VOS_VOID NAS_EMM_MsSerInitRcvLrrcSuspendIndProc(const MsgBlock * pMsg );
extern VOS_VOID NAS_EMM_MsTauInitRcvLrrcSuspendIndProc(const MsgBlock * pMsg );
extern VOS_VOID  NAS_EMM_MsAuthInitRcvLrrcSuspendIndProc(const MsgBlock * pMsg );
extern VOS_VOID  NAS_EMM_MsRrcConnRelInitRcvLrrcSuspendIndProc( VOS_VOID);
extern VOS_VOID  NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendFailProc(VOS_VOID);

extern VOS_UINT32  NAS_EMM_PreProcMsgRrcSuspendInfoChangeInd( MsgBlock  *pstMsg );

/* leixiantiao 00258641 降低圈复杂度 begin */
extern VOS_VOID NAS_EMM_MsRrcConnEstInitRcvLrrcSuspendIndProc(MsgBlock * pMsg);
/* leixiantiao 00258641 降低圈复杂度 end */
extern VOS_UINT32  NAS_LMM_ProcRrcUeCapChangeIndComm(VOS_VOID);


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

#endif /* end of NasEmmPubUSuspend.h*/

