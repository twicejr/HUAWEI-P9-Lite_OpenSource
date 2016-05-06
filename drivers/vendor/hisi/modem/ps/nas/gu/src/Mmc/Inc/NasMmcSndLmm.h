/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcSndLmm.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2011年5月9日
  最近修改   :
  功能描述   : 定义MMC发送给LMM的消息处理头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年5月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_MMC_SND_LMM_H
#define _NAS_MMC_SND_LMM_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include  "MmcGmmInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
#include  "NasCommDef.h"
#include  "NasMmcCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_SndLmmStopReq( VOS_VOID );

VOS_VOID NAS_MMC_SndLmmPlmnAnyCellSrchReq(VOS_VOID);

VOS_VOID NAS_MMC_SndLmmPlmnListReq(VOS_VOID);

VOS_VOID NAS_MMC_SndLmmUsimStatusReq(
    MMC_LMM_USIM_STATUS_ENUM_UINT32     enUsimState
);

VOS_VOID NAS_MMC_SndLmmSuspendReq(VOS_VOID);

VOS_VOID NAS_MMC_SndLmmPlmnSrchStopReq(VOS_VOID);

VOS_VOID NAS_MMC_SndLmmStartReq(VOS_VOID);

VOS_VOID NAS_MMC_SndLmmEquPlmnReq(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
);

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
VOS_VOID NAS_MMC_BuildSndLmmEquPlmnInfo(
     NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
);
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

VOS_VOID NAS_MMC_SndLmmMtDetachIndActionResultReq(
    NAS_MMC_GMM_NT_DETACH_ENUM_U32      enMtType,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCnCause
);

VOS_VOID NAS_MMC_SndLmmLocalDetachIndActionResultReq(
    MMC_LMM_GU_LOCAL_DETACH_TYPE_ENUM_UINT32                ulLocalDetachType
);

VOS_VOID NAS_MMC_SndLmmMoDetachIndActionResultReq(
    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32  ulMoDetachType
);


VOS_VOID NAS_MMC_SndLmmRegActionResultReq(
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU   *pstGuActionRslt
);

VOS_VOID NAS_MMC_SndLmmRelReq( VOS_VOID );

/* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
VOS_VOID NAS_MMC_SndLmmAttachReq(
    VOS_UINT32                                              ulOpId,
    VOS_UINT32                                              ulAttachType,
    NAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM_UINT32                   enEpsAttachReason
);

VOS_VOID NAS_MMC_SndLmmDetachReq(
    VOS_UINT32                          ulOpId,
    VOS_UINT32                          ulDetachType,
    NAS_MSCC_PIF_DETACH_REASON_ENUM_UINT32   enDetachReason
);

/* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */

VOS_VOID NAS_MMC_SndLmmResumeNotify( VOS_VOID );

VOS_VOID NAS_MMC_SndLmmSuspendRsp(
    VOS_UINT32                          ulRst
);

VOS_UINT32  NAS_MMC_FormatProcTypeToLmm(
    NAS_MML_PROC_TYPE_ENUM_U32          enProcType,
    MMC_LMM_ACTION_TYPE_ENUM_UINT32    *penActionType
);

VOS_UINT32  NAS_MMC_ConvertAttachTypeToLmm(
    VOS_UINT32                          ulAttachType,
    MMC_LMM_ATT_REQ_TYPE_ENUM_UINT32   *penLmmAttachType
);


VOS_VOID  NAS_MMC_ConvertLmmPlmnToGUNasFormat(
    MMC_LMM_PLMN_ID_STRU               *pstLMMPlmn,
    NAS_MML_PLMN_ID_STRU               *pstGUNasPlmn
);

VOS_VOID NAS_MMC_ConvertLmmPlmnToGUNasPlmn(
    VOS_UINT32                          ulLmmPlmnNum,
    MMC_LMM_PLMN_ID_STRU               *pstLmmPlmn,
    NAS_MML_PLMN_ID_STRU               *pstGUNasPlmn
);

VOS_UINT32  NAS_MMC_ConvertDetachTypeToLmm(
    VOS_UINT32                          ulDetachType,
    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32 *penLmmDetachType
);

/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
VOS_VOID  NAS_MMC_SndLmmSyscfgReq(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgMsg
);
/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

VOS_VOID  NAS_MMC_SndLmmDisableLteNotify(
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason
);

VOS_VOID  NAS_MMC_SndLmmEnableLteNotify(VOS_VOID);

VOS_VOID NAS_MMC_SndLmmCsConnStatusNotify(
    VOS_UINT8                           ucCsRrConnStatusFlg,
    VOS_UINT8                           ucCsEmergencyConnStatusFlg
);


VOS_VOID NAS_MMC_FillGprsRegInfoInLmmActionRslt(
    MMC_LMM_ACTION_RESULT_REQ_STRU                         *pstMsg
);

VOS_VOID NAS_MMC_FillCsRegInfoInLmmActionRslt(
    MMC_LMM_ACTION_RESULT_REQ_STRU                         *pstMsg
);

VOS_VOID NAS_MMC_BuildLmmSpecPlmnSearchReqMsg(
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList,
    VOS_UINT32                          ulUserSpecFlag,
    VOS_UINT32                          ulPlmnSearchScene
);

VOS_VOID NAS_MMC_SndLmmSpecPlmnSearchReq(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList,
    VOS_UINT32                          ulUserSpecFlag,
    VOS_UINT32                          ulPlmnSearchScene
);

VOS_VOID NAS_MMC_BuildLmmHistoryPlmnSearchReqMsg(
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList
);
VOS_VOID NAS_MMC_SndLmmHistoryPlmnSearchReq(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList
);

VOS_VOID NAS_MMC_BuildLmmPrefBandPlmnSearchReqMsg(
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList,
    VOS_UINT32                          ulUserSpecFlag
);
VOS_VOID NAS_MMC_SndLmmPrefBandPlmnSearchReq(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList,
    VOS_UINT32                          ulUserSpecFlag
);

#if (FEATURE_ON == FEATURE_CSG)
VOS_VOID NAS_MMC_SndLmmCsgListSearchReq(VOS_VOID);
#endif

VOS_VOID NAS_MMC_SndLmmNcellSpecPlmnSearchReq(
    NAS_MMC_LTE_NCELL_INFO_STRU        *pstLteNcellInfo,
    NAS_MML_EQUPLMN_INFO_STRU          *pstOtherModemEplmnInfo
);

VOS_VOID NAS_MMC_BuildLmmStartReqMsg(
    MMC_LMM_START_REQ_STRU             *pstLmmStartReqStru,
    MMC_LMM_USIM_STATUS_ENUM_UINT32     ulSimStatus,
    VOS_UINT32                         *pulRat
);

VOS_VOID NAS_MMC_BuildMmcLmmDetachIndActionResultReqMsg(
    NAS_MMC_GMM_NT_DETACH_ENUM_U32      enMtType,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCnCause,
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pstMsg
);




VOS_VOID NAS_MMC_BuildMmcLmmPlmnSrchReqMsg(
    MMC_LMM_PLMN_SRCH_TYPE_ENUM_UINT32  enSrchType,
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg
);

VOS_UINT32  NAS_MMC_ConvertMmCauseToEmmCause(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCnCause,
    NAS_LMM_CN_CAUSE_ENUM_UINT8        *penCnRejCause
);

VOS_UINT32 NAS_MMC_ConverCnDomainToLmm(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8      enCnDoamin,
    MMC_LMM_DOMAIN_ENUM_UINT32         *penLmmDomain
);


VOS_VOID NAS_MMC_ConvertGuRsltToLmmFormat(
    NAS_MML_REG_RESULT_ENUM_UINT8       enGuRegRslt,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enGuCnCause,
    MMC_LMM_RSLT_TYPE_ENUM_UINT32      *penLmmActRslt
);

VOS_VOID NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify( VOS_VOID );

VOS_VOID NAS_MMC_SndLmmBgStopPlmnSearchReq(VOS_VOID);
VOS_VOID NAS_MMC_SndLmmFastPlmnSearchReq(
    NAS_MML_PLMN_ID_STRU               *pstDestPlmn
);

VOS_VOID NAS_MMC_SndLmmBgPlmnSearchReq(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
);




VOS_VOID NAS_MMC_SndLmmGetGeoPlmnSearchReq(VOS_VOID);

VOS_VOID NAS_MMC_SndLmmStopGetGeoPlmnSearchReq(VOS_VOID);



VOS_VOID  NAS_MMC_SndLmmUeOocStatusInd( VOS_VOID );


VOS_VOID NAS_MMC_SndLmmWcdmaSysInfoInd(
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_SndLmmGsmSysInfoInd(
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_SndLmmCellSelReq(
    MMC_LMM_CELL_SEL_TYPE_ENUM_UINT32       ulSelType
);

VOS_VOID NAS_MMC_SndLmmSuspendRelReq(VOS_VOID);

VOS_VOID NAS_MMC_SndLmmOtherModemInfoNotify(
    MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU                   *pstOtherModemInfoMsg
);

VOS_VOID NAS_MMC_SndLmmLteSysInfoInd(
    LMM_MMC_SYS_INFO_IND_STRU          *pstLmmSysInfoMsg
);

#if (FEATURE_ON == FEATURE_DSDS)
VOS_VOID NAS_MMC_SndLmmBeginSessionNotify(
    MMC_LMM_SESSION_TYPE_ENUM_UINT8     enSessionType
);
VOS_VOID NAS_MMC_SndLmmEndSessionNotify(
    MMC_LMM_SESSION_TYPE_ENUM_UINT8     enSessionType
);

#endif


/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-19, begin */
VOS_VOID NAS_MMC_SndLmmImsVoiceCapChangeNtf(
    VOS_UINT8                           ucImsVoiceAvail
);
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-19, end */
VOS_VOID NAS_MMC_SndLmmCellSignReportNotify(VOS_VOID);

VOS_VOID NAS_MMC_SndLmmVoiceDomainChangeInd(
    MMC_LMM_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
);
#endif

VOS_VOID NAS_MMC_SndLmmBgSearchHrpdReq(VOS_VOID);
VOS_VOID NAS_MMC_SndLmmStopBgSearchHrpdReq(VOS_VOID);

#if(FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID NAS_MMC_SndLmmCLInterSysStartNtf(
    MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32                       enSuspendCause
);
#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

