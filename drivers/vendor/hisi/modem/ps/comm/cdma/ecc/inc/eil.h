/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Eil.h
  版 本 号   : 初稿
  作    者   : chenqihang
  生成日期   : 2015年10月20日
  最近修改   :
  功能描述   : Eil.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月20日
    作    者   : chenqihang
    修改内容   : 创建文件

******************************************************************************/

#ifndef __EIL_H__
#define __EIL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_INT32 CAS_1X_GetPower(VOS_VOID);

VOS_INT32 CAS_1X_GetRssi(VOS_VOID);

VOS_INT32 CAS_1X_GetEcio(VOS_VOID);

VOS_INT32 CAS_1X_GetPilotStrength(VOS_VOID);
#endif
#endif
VOS_UINT32 eil_get_power(VOS_VOID);

VOS_UINT32 eil_get_battery(VOS_VOID);

VOS_UINT32 eil_get_rssi(VOS_VOID);

VOS_UINT32 eil_get_ecio(VOS_VOID);

VOS_UINT32 eil_get_pilot_strength(VOS_VOID);

VOS_UINT32 eil_get_time(VOS_VOID);

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

#endif /* end of eil.h */
