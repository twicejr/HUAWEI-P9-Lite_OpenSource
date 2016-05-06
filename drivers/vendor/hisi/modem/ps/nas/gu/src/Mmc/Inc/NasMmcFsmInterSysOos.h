/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcInterSysOos.h
  版 本 号   : 初稿
  作    者   : W00167002
  生成日期   : 2011年4月12日
  最近修改   :
  功能描述   : NasMmcInterSysOos.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年7月27日
    作    者   : W00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef __NAS_MMC_FSM_INTER_SYS_OOS_H__
#define __NAS_MMC_FSM_INTER_SYS_OOS_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "Nasrrcinterface.h"


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
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_InterSysOos_WaitAsResumeInd(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmRelInd_InterSysOos_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvWasResumeInd_InterSysOos_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGmmResumeRsp_InterSysOos_WaitMmResumeRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGmmSuspendRsp_InterSysOos_WaitMmSuspendRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmResumeRsp_InterSysOos_WaitMmResumeRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmSuspendRsp_InterSysOos_WaitMmSuspendRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysOos_WaitAsResumeInd(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysOos_WaitMmResumeRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysOos_WaitMmSuspendRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysOos_WaitAsResumeInd(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvWasSuspendInd_InterSysOos_Init(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);






VOS_UINT32  NAS_MMC_RcvRrMmRelInd_InterSysOos_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


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

#endif /* end of NasMmcFsmInterSysOos.h */

