/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcSndMm.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2011年5月9日
  最近修改   :
  功能描述   : 定义MMC发送给MM的消息处理头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年5月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_MMC_SND_MM_H
#define _NAS_MMC_SND_MM_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "Nasrrcinterface.h"
#include  "MmcGmmInterface.h"
#include  "MmcMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include  "NasCommDef.h"
#include  "NasMmlCtx.h"
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
VOS_VOID NAS_MMC_SndMmStartReq(VOS_VOID);

VOS_VOID   NAS_MMC_SndMmPlmnSchInit(VOS_VOID);

VOS_VOID   NAS_MMC_SndMmWasSysInfoInd(
    VOS_UINT32                          ulForbiddenFlg,
    VOS_UINT32                          ulUserSpecSrchPlmnFlg,
    struct MsgCB                       *pstMsg
);

VOS_VOID   NAS_MMC_SndMmGsmSysInfoInd(
    VOS_UINT32                          ulForbiddenFlg,
    VOS_UINT32                          ulUserSpecSrchPlmnFlg,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_SndMmPowerOffReq(VOS_VOID);

VOS_VOID NAS_MMC_SndMmSuspendInd(
    RRMM_SUSPEND_IND_ST                *pstMsg
);

VOS_VOID NAS_MMC_SndMmResumeInd(
    RRMM_RESUME_IND_ST                 *pstMsg
);

VOS_VOID  NAS_MMC_SndMmCoverageLostInd(VOS_VOID);

VOS_VOID NAS_MMC_SndMmRelReq(VOS_VOID);

VOS_VOID NAS_MMC_SndMmAttachReq(
                                            VOS_UINT32 ulOpid,
                                            VOS_UINT32 ulAttachType);
VOS_VOID NAS_MMC_SndMmDetachReq(
    VOS_UINT32                          ulOpid,
    MMC_MM_DETACH_TYPE_ENUM_UINT32      enDetachType,  /* detach类型 */
    MMC_MM_DETACH_REASON_ENUM_UINT32    enDetachReason /* detach原因 */
);

VOS_VOID NAS_MMC_SndMmRatChangeInd(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_SndMmLteSysinfoInd(
    LMM_MMC_SYS_INFO_IND_STRU          *pstLmmSysInfoMsg
);


VOS_VOID  NAS_MMC_SndMmLmmAttachInd(
    LMM_MMC_ATTACH_IND_STRU            *pstAttachInd
);

VOS_VOID  NAS_MMC_SndMmLmmTauResultInd(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstTauResultInd
);

VOS_VOID  NAS_MMC_SndMmLmmSerResultnd(
    LMM_MMC_SERVICE_RESULT_IND_STRU    *pstSerInd
);


VOS_VOID  NAS_MMC_SndMmLmmMtDetachInd(
    LMM_MMC_DETACH_IND_STRU            *pstDetachInd
);

VOS_VOID  NAS_MMC_SndMmLmmMoDetachInd(
    LMM_MMC_DETACH_CNF_STRU            *pstDetachCnf
);

VOS_VOID  NAS_MMC_SndMmLmmLocalDetachInd(
    LMM_MMC_DETACH_IND_STRU            *pstDetachInd
);

VOS_VOID  NAS_MMC_SndMmLmmTimerStateNotify(
    LMM_MMC_TIMER_STATE_NOTIFY_STRU    *pstTimerStatusNotify
);


#endif


VOS_VOID NAS_MMC_SndMmModeChangeReq(
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode
);

VOS_VOID NAS_MMC_SndMmLauReq(
    MMC_MM_LAU_REQ_REASON_ENUM_UINT32   enLauReqReason
);
VOS_VOID  NAS_MMC_SndMmWasAcInfoChangeInd(
    VOS_UINT8                           ucCsResTrictionRegister,
    VOS_UINT8                           ucPsResTrictionRegister,
    VOS_UINT8                           ucOldCsResTrictionRegister,
    VOS_UINT8                           ucOldPsResTrictionRegister
);

VOS_VOID NAS_MMC_SndMmSrvccInfoNotify(VOS_VOID);

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


