/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmInterSysCco.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2011年6月29日
  最近修改   :
  功能描述   : NasMmcFsmInterSysCco.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年6月29日
    作    者   : W00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef __NAS_MMC_FSM_INTER_SYS_CCO_H__
#define __NAS_MMC_FSM_INTER_SYS_CCO_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"


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
VOS_UINT32  NAS_MMC_RcvWasSuspendInd_InterSysCco_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGasSuspendInd_InterSysCco_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmSuspendRsp_InterSysCco_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGmmSuspendRsp_InterSysCco_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCco_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysCco_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGasResumeInd_InterSysCco_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCco_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmRelInd_InterSysCco_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGmmResumeRsp_InterSysCco_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmResumeRsp_InterSysCco_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitWSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCco_WaitWSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitGSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCco_WaitGSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmRrConnInfoInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGmmSignalingStatusInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGmmTbfRelInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvWasSuspendInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGasSuspendInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_RcvTiWaitEstCnfExpired_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvWasSuspendInd_InterSysCco_WaitAsSuspendIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGasSuspendInd_InterSysCco_WaitAsSuspendIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitAsSuspendIndExpired_InterSysCco_WaitAsSuspendIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmSuspendRsp_InterSysCco_WaitMmSuspendRspFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_RcvGmmSuspendRsp_InterSysCco_WaitMmSuspendRspFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCco_WaitMmSuspendRspFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysCco_WaitAsResumeIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGasResumeInd_InterSysCco_WaitAsResumeIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCco_WaitAsResumeIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_RcvRrMmRelInd_InterSysCco_WaitAsResumeIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGmmResumeRsp_InterSysCco_WaitMmResumeRspFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmResumeRsp_InterSysCco_WaitMmResumeRspFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRspFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitEstIndExpired_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitWSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCco_WaitWSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitGSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCco_WaitGSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_InterSysCco_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysCco_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_InterSysCco_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitLSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_InterSysCco_WaitLSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitLSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_InterSysCco_WaitAsSuspendIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysCco_WaitAsResumeIndFallBack(
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

#endif /* end of NasMmcFsmInterSysCco.h */


