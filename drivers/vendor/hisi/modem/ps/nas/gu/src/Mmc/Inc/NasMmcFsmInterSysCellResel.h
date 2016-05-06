/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcInterSysCellResel.h
  版 本 号   : 初稿
  作    者   : W00167002
  生成日期   : 2011年4月12日
  最近修改   :
  功能描述   : NasMmcInterSysCellResel.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年4月12日
    作    者   : W00167002
    修改内容   : 创建文件

******************************************************************************/
#ifndef __NAS_MMC_FSM_INTER_SYS_CELLRESEL_H__
#define __NAS_MMC_FSM_INTER_SYS_CELLRESEL_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "Nasrrcinterface.h"

#include "NasMmlCtx.h"
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

VOS_UINT32 NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitAsResumeInd(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGasSuspendInd_InterSysCellResel_Init(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGmmResumeRsp_InterSysCellResel_WaitMmResumeRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGmmSuspendRsp_InterSysCellResel_WaitMmSuspendRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmResumeRsp_InterSysCellResel_WaitMmResumeRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmSuspendRsp_InterSysCellResel_WaitMmSuspendRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCellResel_WaitAsResumeInd(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmRelInd_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCellResel_WaitMmResumeRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCellResel_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCellResel_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCellResel_WaitMmSuspendRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvWasSuspendRelCnf_InterSysCellResel_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysCellResel_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrmmRelInd_InterSysCellResel_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGasSuspendRelCnf_InterSysCellResel_WaitGasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitGasSuspendRelCnf_InterSysCellResel_WaitGasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if   (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_MMC_RcvLmmSuspendRelCnf_InterSysCellResel_WaitLmmSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitAsSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitLmmSuspendRelCnf_InterSysCellResel_WaitLmmSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#endif
VOS_VOID NAS_MMC_SndSuspendRelReq_InterSysCellResel(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);

VOS_VOID NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);



VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitAsResumeInd(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvWasSuspendInd_InterSysCellResel_Init(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitAsResumeInd(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_InterSysCellResel_Init(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLSysInfoInd_InterSysCellResel_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitLSysInfoExpired_InterSysCellResel_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_RcvLmmSuspendInfoChangeNotify_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


#endif

/* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
#if   (FEATURE_ON == FEATURE_CL_INTERWORK)
VOS_UINT32 NAS_MMC_RcvCmmcaResumeInd_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitCmmcaResumeIndExpired_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif
/* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))

VOS_UINT32 NAS_MMC_RcvMsccInterSysHrpdNtf_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitMsccInterSysHrpdNtfExpired_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccInterSysHrpdNtf_InterSysCellResel_WaitAsSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#endif

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysCellResel_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
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

#endif /* end of NasMmcFsmInterSysCellResel.h */

