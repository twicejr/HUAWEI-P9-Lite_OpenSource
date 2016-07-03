

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
