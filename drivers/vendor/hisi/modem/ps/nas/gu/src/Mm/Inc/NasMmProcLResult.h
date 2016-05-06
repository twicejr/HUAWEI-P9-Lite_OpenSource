/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmProcLRegRst.h
  版 本 号   : 初稿
  作    者   : W00167002
  生成日期   : 2011年4月11日
  最近修改   :
  功能描述   : NasMmProcLRegRst.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年4月11日
    作    者   : W00167002
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_MM_PROCLREGRST_H_
#define _NAS_MM_PROCLREGRST_H_
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include  "GmmStru.h"
/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-16, begin */
#include "NasMmlCtx.h"
/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-16, end */






#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define MM_EMM_MAX_ATTEMPT_COUNTER      (5)

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
VOS_VOID  NAS_MM_ProcLmmAttachCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause
);

VOS_VOID  NAS_MM_ProcLmmAttachRstInd(
    MMCMM_LMM_ATTACH_IND_STRU          *pstLmmAttachInd
);

VOS_VOID  NAS_MM_ProcLmmAuthRstInd(VOS_VOID);

VOS_VOID  NAS_MM_ProcLmmNwDetachIndCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause
);

VOS_VOID NAS_MM_ProcLmmTauCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause
);


VOS_VOID NAS_MM_ProcLmmRejOtherCause(
    VOS_UINT32                          ulAttemptCounter,
    VOS_UINT32                          ulLmmBitOpAtmpCnt
);

VOS_VOID  NAS_MM_ProcLmmCombinedAttachCause(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause,
    VOS_UINT32                          ulAttemptCounter,
    VOS_UINT32                          ulLmmBitOpAtmpCnt
);

VOS_VOID  NAS_MM_ProcLmmCombinedTauCause(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause,
    VOS_UINT32                          ulAttemptCounter,
    VOS_UINT32                          ulLmmBitOpAtmpCnt
);

VOS_VOID NAS_MM_ProcLmmCombinedAttachOnlyEpsSucc(
    MMCMM_LMM_ATTACH_IND_STRU          *pstLmmCombinedAttachInd
);

VOS_VOID NAS_MM_ProcLmmCombinedAttachSucc(
    MMCMM_LMM_ATTACH_IND_STRU          *pstLmmCombinedAttachInd
);

VOS_VOID NAS_MM_ProcLmmCombinedAttachFail(
    MMCMM_LMM_ATTACH_IND_STRU          *pstLmmCombinedAttachInd
);

VOS_VOID NAS_MM_ProcLmmCombinedTauOnlyEpsSucc(
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstCombinedTauInd
);

VOS_VOID NAS_MM_ProcLmmCombinedTauSucc(
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstCombinedTauInd
);

VOS_VOID NAS_MM_ProcLmmCombinedTauFail(
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstCombinedTauInd
);

VOS_VOID NAS_MM_ProcLmmCombinedTauInd(
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstCombinedTauInd
);

VOS_UINT8 NAS_MM_RcvLmmAttachInd(
    struct MsgCB                       *pstMsg
);

VOS_UINT8 NAS_MM_RcvLmmTauInd(
    struct MsgCB                       *pstMsg
);

VOS_UINT8 NAS_MM_RcvLmmMTDetachInd(
    struct MsgCB                       *pstMsg
);

VOS_UINT8 NAS_MM_RcvLmmMoDetachInd(
    struct MsgCB                       *pstMsg
);

VOS_UINT8 NAS_MM_RcvLmmServiceRsltInd(
    struct MsgCB                       *pstMsg
);

VOS_UINT8 NAS_MM_RcvLmmSysInfoInd(
    struct MsgCB                       *pstMsg
);

VOS_UINT8 NAS_MM_RcvLmmCombinedStartNotifyReq(
    VOS_VOID                           *pstMsg
);

/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-16, begin */
VOS_VOID  NAS_MM_ConvertLmmPlmnToNasPLMN(
    VOS_UINT8                          *pucLmmPlmn,
    NAS_MML_PLMN_ID_STRU               *pstNasPlmn
);

/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-16, end */
#endif

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT8 NAS_MM_RcvLmmCsfbServiceEndInd(
    VOS_VOID                           *pstMsg
);

VOS_UINT8 NAS_MM_RcvLmmCsPagingInd(
    VOS_VOID                           *pstMsg
);

VOS_UINT8 NAS_MM_RcvLmmTimerInfoNotify(
    struct MsgCB                       *pstMsg
);

/* Deleted by y00245242 for VoLTE_PhaseI  项目, 2013-7-19, begin */
/*  删除LMM给MM的信息改变指示，已移到LMM给GMM的信息改变指示消息中处理 */
/* Deleted by y00245242 for VoLTE_PhaseI  项目, 2013-7-19, end */
#endif


/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-22, begin */
VOS_UINT8 NAS_MM_RcvLmmHoSecuInfoCnf(
    VOS_VOID                           *pstMsg
);

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-22, end */

VOS_VOID NAS_MM_ProcBufferedCsfbService(VOS_VOID);

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

#endif /* end of NasMmProcLRegRst.h */
