


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "eil.h"
#include "vos.h"
#include "v_timer.h"
#include "cprocstime.h"
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/


VOS_UINT32 eil_get_power( VOS_VOID )
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    return (VOS_UINT32)CAS_1X_GetPower();
#else
    return 0;
#endif
#endif
}


VOS_UINT32  eil_get_battery( VOS_VOID )
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    /* 使用slice代替 */
    return (VOS_UINT32)VOS_GetSlice();
#else
    return 0;
#endif
#endif
}


VOS_UINT32 eil_get_rssi( VOS_VOID )
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    return (VOS_UINT32)CAS_1X_GetRssi();
#else
    return 0;
#endif
#endif
}

VOS_UINT32 eil_get_ecio( VOS_VOID )
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    return (VOS_UINT32)CAS_1X_GetEcio();
#else
    return 0;
#endif
#endif
}



VOS_UINT32 eil_get_pilot_strength( VOS_VOID )
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    return (VOS_UINT32)CAS_1X_GetPilotStrength();
#else
    return 0;
#endif
#endif
}


VOS_UINT32 eil_get_time( VOS_VOID )
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    return (VOS_UINT32)CDMA_Timing_GetSystemTime80ms(CDMA_TIMING_RTT_1X);
#else
    return 0;
#endif
#endif
}

/*lint +e961*/
/*lint +e958*/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

