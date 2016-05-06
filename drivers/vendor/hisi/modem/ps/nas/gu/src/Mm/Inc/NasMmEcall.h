/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmEcall.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年3月31日
  最近修改   :
  功能描述   : NasMmEcall.c的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年3月31日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/
#ifndef _NAS_MM_ECALL_H_
#define _NAS_MM_ECALL_H_


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*******************************************************************************
  3 枚举定义
*******************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/
/*模块名＋意义＋HEADER
 */


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
VOS_UINT8 NAS_MM_GetT3242ExpiredFlg(VOS_VOID);
VOS_VOID NAS_MM_SetT3242ExpiredFlg(VOS_UINT8 ucT3242ExpiredFlg);

VOS_VOID NAS_MM_SetT3243ExpiredFlg(VOS_UINT8 ucT3243ExpiredFlg);
VOS_UINT8 NAS_MM_GetT3243ExpiredFlg(VOS_VOID);

VOS_UINT8 NAS_MM_GetT3242StartNeededFlg(VOS_VOID);
VOS_VOID NAS_MM_SetT3242StartNeededFlg(VOS_UINT8 ucT3242StartNeededFlg);

VOS_UINT8 NAS_MM_GetT3243StartNeededFlg(VOS_VOID);
VOS_VOID NAS_MM_SetT3243StartNeededFlg(VOS_UINT8 ucT3243StartNeededFlg);

VOS_VOID NAS_MM_RcvT3242Expired_MmIdleNoCellAvailable(VOS_VOID *pRcvMsg);

VOS_VOID NAS_MM_RcvT3242Expired_MmIdleNormalService(VOS_VOID *pRcvMsg);

VOS_VOID NAS_MM_RcvT3243Expired_MmIdleNoCellAvailable(VOS_VOID *pRcvMsg);

VOS_VOID NAS_MM_RcvT3243Expired_MmIdleNormalService(VOS_VOID *pRcvMsg);

VOS_VOID NAS_MM_StopAllTimersRelatedToEcall(VOS_VOID);

VOS_VOID NAS_MM_ClearAllEcallTimersExpiredFlg(VOS_VOID);

VOS_VOID NAS_MM_RcvMmcMmSysInfo_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
);

VOS_VOID NAS_MM_RcvMmcMmAttachReq_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
);


VOS_VOID NAS_MM_ProcMmcMmDetachReq_MmIdleECallInactive( VOS_VOID );

VOS_VOID NAS_MM_RcvMmcMmPlmnSrchInit_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
);

VOS_VOID NAS_MM_RcvMmcMmCoverageLostInd_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
);

VOS_VOID NAS_MM_RcvMmcMmPowerOffReq_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
);

VOS_VOID NAS_MM_RcvMmcMmWAcInfoChangeInd_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
);

VOS_VOID NAS_MM_RcvSmsEstReq_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
);

VOS_VOID NAS_MM_RcvSsEstReq_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
);

VOS_VOID NAS_MM_RcvCcEstReq_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
);

VOS_VOID NAS_MM_PerformECallInactivity( VOS_VOID );

VOS_VOID NAS_MM_RecordEcallTimerStartNeededFlag(VOS_VOID);

VOS_VOID NAS_MM_InitEcallInfo(VOS_VOID);

VOS_VOID NAS_MM_ClearEcallTimerInfo(VOS_VOID);

VOS_VOID NAS_MM_ProcEcallTimerStartNeededFlg(VOS_VOID);

VOS_VOID NAS_MM_ProcBufferMsg_MmIdleECallInactive( VOS_VOID );

#endif /* end of FEATURE_ECALL */


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasMmEcall.h*/
