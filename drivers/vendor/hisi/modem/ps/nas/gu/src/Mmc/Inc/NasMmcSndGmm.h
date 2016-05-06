/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcSndGmm.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2011年5月9日
  最近修改   :
  功能描述   : 定义MMC发送给GMM的消息处理头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年5月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_MMC_SND_GMM_H
#define _NAS_MMC_SND_GMM_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "MmcGmmInterface.h"

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
VOS_VOID NAS_MMC_SndGmmStartReq(VOS_VOID);
VOS_VOID   NAS_MMC_SndGmmPlmnSchInit(VOS_VOID);
VOS_VOID NAS_MMC_SndGmmPowerOffReq(VOS_VOID);

VOS_VOID NAS_MMC_SndGmmSuspendInd(
    RRMM_SUSPEND_IND_ST                *pstMsg
);

VOS_VOID NAS_MMC_SndGmmResumeInd(
    RRMM_RESUME_IND_ST                 *pstMsg
);

VOS_VOID  NAS_MMC_SndGmmCoverageLostInd(VOS_VOID);

VOS_VOID NAS_MMC_SndGmmLuResult(
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulCause
);
VOS_VOID NAS_MMC_SndGmmRelReq(VOS_VOID);

VOS_VOID NAS_MMC_SndGmmAttachReq(
                                              VOS_UINT32  ulOpid,
                                              VOS_UINT32  ulMmcAttachType);
VOS_VOID NAS_MMC_SndGmmDetachReq(
    VOS_UINT32                          ulOpid,
    MMC_GMM_DETACH_TYPE_ENUM_UINT32     enDetachType,  /* detach类型 */
    MMC_GMM_DETACH_REASON_ENUM_UINT32   enDetachReason /* detach原因 */
);


#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_SndGmmLteSysinfoInd(
    LMM_MMC_SYS_INFO_IND_STRU          *pstLmmSysInfoMsg
);

VOS_VOID  NAS_MMC_SndGmmLmmAttachInd(
    LMM_MMC_ATTACH_IND_STRU            *pstAttachInd
);

VOS_VOID  NAS_MMC_SndGmmLmmTauResultInd(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstTauResultInd
);

VOS_VOID  NAS_MMC_SndGmmLmmSerResultnd(
    LMM_MMC_SERVICE_RESULT_IND_STRU    *pstSerInd
);

VOS_VOID  NAS_MMC_SndGmmLmmMtDetachInd(
    LMM_MMC_DETACH_IND_STRU            *pstDetachInd
);

VOS_VOID  NAS_MMC_SndGmmLmmLocalDetachInd(
    LMM_MMC_DETACH_IND_STRU            *pstActionResultInd
);

VOS_VOID  NAS_MMC_SndGmmLmmMoDetachInd(
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf
);


VOS_VOID  NAS_MMC_SndGmmLmmStatusInd(
    LMM_MMC_STATUS_IND_STRU        *pstStatusInd
);

VOS_VOID  NAS_MMC_SndGmmLmmTimerStateNotify(
    LMM_MMC_TIMER_STATE_NOTIFY_STRU    *pstTimerStatusNotify
);


VOS_VOID  NAS_MMC_SndGmmEmergencyNumList(
    MMCGMM_EMERGENCY_NUM_LIST_IND_STRU *pstEmergencyNumList
);

#endif

VOS_VOID NAS_MMC_SndGmmModeChangeReq(
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode
);

VOS_VOID   NAS_MMC_SndGmmWasSysInfoInd(
    VOS_UINT32                          ulForbiddenFlg,
    VOS_UINT32                          ulUserSrchFlg,
    struct MsgCB                       *pstMsg
);

VOS_VOID   NAS_MMC_SndGmmGsmSysInfoInd(
    VOS_UINT32                          ulForbiddenFlg,
    VOS_UINT32                          ulUserSrchFlg,
    struct MsgCB                       *pstMsg
);

VOS_VOID  NAS_MMC_SndGmmWasAcInfoChangeInd(
    VOS_UINT8                           ucCsResTrictionRegister,
    VOS_UINT8                           ucPsResTrictionRegister,
    VOS_UINT8                           ucOldCsResTrictionRegister,
    VOS_UINT8                           ucOldPsResTrictionRegister
);

VOS_VOID  NAS_MMC_SndGmmVoiceDomainChangeNotify(VOS_VOID);

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

