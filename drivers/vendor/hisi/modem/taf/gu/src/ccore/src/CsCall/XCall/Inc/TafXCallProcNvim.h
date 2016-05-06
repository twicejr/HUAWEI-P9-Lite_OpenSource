/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallProcNvim.h
  版 本 号   : 初稿
  作    者   : h00313353
  生成日期   : 2015年07月07日
  最近修改   :
  功能描述   : TafXCallProcNvim.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年07月07日
    作    者   : h00313353
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_X_CALL_PROC_NVIM_H__
#define __TAF_X_CALL_PROC_NVIM_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "vos.h"
#include "TafAppCall.h"
#include "TafStdlib.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 全局变量定义
*****************************************************************************/

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
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_XCALL_ReadEmcCallRedialPeriod(VOS_VOID);

VOS_VOID TAF_XCALL_Read1xVoiceSoCfgNvim(VOS_VOID);
VOS_VOID TAF_XCALL_ReadStartAndStopContDtmfIntervalLen(VOS_VOID);

VOS_VOID  TAF_XCALL_ReadEmcCallBackCfgNvim(VOS_VOID);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_VOID TAF_XCALL_ReadVoiceEncryptPublicKeyAndVersionNumber(VOS_VOID);

VOS_VOID TAF_XCALL_WriteVoiceEncryptPublicKeyAndVersionNumber(
    VOS_UINT8                          *pucPubKey,
    VOS_UINT8                           ucVerNum
);

VOS_VOID TAF_XCALL_ReadVoiceEncryptCapCfgPara(VOS_VOID);

VOS_VOID TAF_XCALL_WriteVoiceEncryptCapCfgPara(
    TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT32                    enEccSrvCap,
    TAF_CALL_APP_ECC_SRV_STATUS_ENUM_UINT32                 enEccSrvStatus
);

VOS_VOID TAF_XCALL_ReadVoiceEncryptSecInfoEraseSysTime(VOS_VOID);

VOS_VOID TAF_XCALL_WriteVoiceEncryptSecInfoEraseSysTime(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstSysTime
);

VOS_VOID TAF_XCALL_ReadVoiceEncryptPassWordResetSysTime(VOS_VOID);

VOS_VOID TAF_XCALL_WriteVoiceEncryptPassWordResetSysTime(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstSysTime
);

VOS_VOID TAF_XCALL_ReadVoiceEncryptTimerCfgInfo(VOS_VOID);
#endif
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

#endif /* end of TafXCallProcNvim.h */



