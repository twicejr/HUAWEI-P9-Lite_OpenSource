

#ifndef _NASEMMPUBURESUME_H
#define _NASEMMPUBURESUME_H


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "LRrcLNasInterface.h"
#include    "NasEmmcEmmInterface.h"
#include    "LnasErrlogInterface.h"



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
#define NAS_EMM_RESUME_UPLAYER_NUM_CM            2
#define NAS_EMM_RESUME_UPLAYER_NUM_INITVALUE     0

/* DCM需求，GU到L的切换不考虑被禁TA */
#define NAS_EMM_HO_IGNORE_FORBID_TA_FLAG_VALID     LPS_NV_GET_GU2L_HO_IGNORE_FORBID_TA_BIT
#define NAS_EMM_HO_IGNORE_FORBID_TA_FLAG_INVALID   (0)


/* 计算组合状态: 0x主状态_0x子状态 */
#define NAS_EMM_PUBU_COMP_EMMSTATE(NAS_EMM_MAIN_STAT, NAS_EMM_SUB_STAT)\
            ((((VOS_UINT32)(NAS_EMM_MAIN_STAT)) << NAS_EMM_MOVEMENT_16_BITS) | (NAS_EMM_SUB_STAT))

#define NAS_EMM_PUBU_CHK_STAT_VALID(NAS_EMM_MAIN_STAT, NAS_EMM_SUB_STAT)\
            (\
                NAS_EMM_PUBU_COMP_EMMSTATE(NAS_EMM_MAIN_STAT, NAS_EMM_SUB_STAT) == \
                NAS_EMM_PUBU_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT, NAS_EMM_CUR_SUB_STAT)\
            )


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
extern VOS_VOID     NAS_EMM_SaveLrrcResumePara( const LRRC_LMM_RESUME_IND_STRU  *pLrrcLmmResumeInd );
extern VOS_UINT32 NAS_EMM_ProcSysCheck3412Exp( VOS_VOID );
/*extern VOS_VOID     NAS_EMM_ResumeConnStateChng(VOS_VOID);*/
extern VOS_UINT32   NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru );
extern VOS_VOID     NAS_EMM_SendMmcResumeInd( VOS_VOID );
extern VOS_VOID     NAS_EMM_SendEsmResumeInd( VOS_VOID );
extern VOS_VOID     NAS_EMM_SendErabmResumeInd( VOS_VOID );
extern VOS_UINT32   NAS_EMM_MsSuspendSsWaitEndMsgLrrcResumeInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  );
extern VOS_UINT32   NAS_EMM_MsRegSsNoCellAvailMsgRrcSecuParaInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru );
extern VOS_UINT32   NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru );
extern VOS_UINT32   NAS_EMM_MsResumeSsRrcRsmWaitOtherMsgRsmRsp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  );
extern VOS_UINT32   NAS_EMM_MsResumeSsRrcRsmWaitOtherMsgWtOtherTimerExp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  );
extern VOS_UINT32  NAS_EMM_PreProcSysWhenResumingReverse(
                            const EMMC_EMM_SYS_INFO_IND_STRU *pstsysinfo );
extern VOS_VOID     NAS_EMM_ReverseStateChng( VOS_VOID );
extern VOS_VOID  NAS_EMM_GU2LResumeStateChng(VOS_VOID);
extern VOS_UINT32   NAS_EMM_PreProcSysInfoReselReverse(
                                        const EMMC_EMM_SYS_INFO_IND_STRU *pstsysinfo );
extern VOS_UINT32  NAS_EMM_PreProcSysInfoHoAndCcoReverse(
                                   const EMMC_EMM_SYS_INFO_IND_STRU *pstsysinfo );
extern VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcPlmnInd
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcDetachReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
/* leixiantiao 00258641 重构函数降低圈复杂度 begin */
extern VOS_VOID NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExpHoProc(VOS_VOID);
/* leixiantiao 00258641 重构函数降低圈复杂度 end */

extern VOS_UINT32   NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  );
extern VOS_UINT32   NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  );
extern VOS_UINT32   NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  );
extern VOS_UINT32   NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgRrcRelInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  );
extern VOS_UINT32  NAS_EMM_MsResumeSsRrcOriMsgT3412Exp
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
/*extern VOS_VOID     NAS_EMM_ProcSysWhenRsmGu2LIdle( VOS_VOID );*/
extern VOS_VOID     NAS_EMM_ProcSysWhenRsmGu2LHo( VOS_VOID );
extern VOS_VOID     NAS_EMM_ProcSuitSysWhenRsmGu2LReg(VOS_VOID);
extern VOS_VOID  NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LDeReg(VOS_VOID);
extern VOS_VOID  NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LDeReg(VOS_VOID);
extern VOS_UINT32   NAS_EMM_NoCellSuspendMsgMmcPlmnReq( VOS_VOID );
extern VOS_VOID     NAS_EMM_NoImsiSuspendMsgMmcPlmnReq( VOS_VOID );
extern VOS_VOID     NAS_EMM_SendLrcResumeRsp( VOS_VOID);
extern VOS_VOID     NAS_EMM_MmcRsmGetSecuPara( VOS_VOID );
/* leixiantiao 00258641 重构代码降低圈复杂度 2014-7-30 begin */
extern VOS_UINT32 NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode(VOS_VOID);
extern VOS_UINT32  NAS_LMM_PreProcMmcCsConnStatusNotify(MsgBlock *    pMsg );
extern VOS_UINT32 NAS_EMM_IsLauOrComRauOrSrvccHappenedWithCsPsUeMode(VOS_VOID);
/* leixiantiao 00258641 重构代码降低圈复杂度 2014-7-30 end */

extern VOS_UINT32 NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode(VOS_VOID);
extern VOS_UINT32 NAS_EMM_IsG2LIsrActAndP4ConditionSatisfied(NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir );

/*extern VOS_VOID     NAS_EMM_ReverseFail(VOS_VOID  );*/
extern VOS_VOID  NAS_EMM_ProcSysWhenRsmGu2LRegReselect( VOS_VOID );
extern VOS_VOID  NAS_EMM_ProcSysWhenRsmGu2LRegRedirect( VOS_VOID );

extern VOS_VOID  NAS_EMM_ProcSysWhenRsmGu2LRegCco( VOS_VOID );

extern VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgMmcPlmnInd
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern VOS_VOID  NAS_EMM_MmcResumeSetTauStartCause(VOS_VOID);
extern VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgAreaLostInd
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgMmcDetachReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern VOS_VOID  NAS_EMM_MmcOriResumeSysInfoProc(VOS_VOID);
extern VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgT3412Exp
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgBearStatusReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);

extern VOS_VOID  NAS_EMM_RrcResumeReselTypeSetTauStartCause(VOS_VOID  );
extern  VOS_VOID  NAS_EMM_RrcResumeRedirTypeSetTauStartCause(VOS_VOID  );
extern VOS_UINT32  NAS_EMM_MsResumeReverseMsgRrcAccessGrantInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  );

extern VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgIntraTauReq( VOS_UINT32  ulMsgId,
                                                        VOS_VOID   *pMsgStru );
extern VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgIntraTauReq( VOS_UINT32  ulMsgId,
                                                        VOS_VOID   *pMsgStru );
extern VOS_VOID  NAS_EMM_ResumeProcPTMSITau( VOS_VOID );
extern VOS_VOID  NAS_EMM_ProcConnGu2LReselect( VOS_VOID );
extern VOS_UINT32 NAS_EMM_ProcSysCommonCheckTauFlag( VOS_VOID );
extern VOS_VOID  NAS_EMM_GU2LResumeStateChngAsPlmnInd(VOS_VOID);
extern VOS_VOID  NAS_EMM_RegForbidSysInfoProc( EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32  ulForbiddenInfo);
extern VOS_VOID  NAS_EMM_GU2LNoEpsBearProc(VOS_VOID);
extern  VOS_VOID NAS_EMM_SetTinToPtmsiWhenIsrAct(VOS_VOID);
extern VOS_VOID NAS_EMM_IsG2LGmmSuspendAndIsrAct(VOS_VOID);
extern VOS_UINT32 NAS_EMM_IsW2LAndPmmConnect
(
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir
);
extern VOS_UINT32 NAS_EMM_IsG2LAndGprsStateReady
(
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir
);
extern VOS_VOID NAS_EMM_RatErrRecord(EMM_OM_ERRLOG_RAT_ENUM_UINT16           enRatType);

extern VOS_VOID NAS_EMM_LocalDetachErrRecord(
        EMM_ERR_LOG_LOCAL_DETACH_TYPE_ENUM_UINT16       enLocalDetType);
extern VOS_UINT32  NAS_LMM_PreProcMmcImsVoiceDomainChangeInd(MsgBlock *    pMsg );
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

#endif /* end of NasEmmPubUResume.h*/
