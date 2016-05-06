/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : eil.c
  版 本 号   : 初稿
  作    者   : chenqihang
  生成日期   : 2015年10月21日
  最近修改   :
  功能描述   : 电信加密库适配接口

  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月21日
    作    者   : chenqihang
    修改内容   : 创建文件

******************************************************************************/


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

/*****************************************************************************
 函 数 名  : eil_get_power
 功能描述  : 返回导频能量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : 00177591
    修改内容   : 新生成函数

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

/*****************************************************************************
 函 数 名  : eil_get_battery
 功能描述  : 返回电池电量
 输入参数  : 无
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : 00177591
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : eil_get_rssi
 功能描述  : 返回信号强度
 输入参数  : 无
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : 00177591
    修改内容   : 新生成函数

*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : eil_get_ecio
 功能描述  : 返回信号质量
 输入参数  : 无
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : 00177591
    修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : eil_get_pilot_strength
 功能描述  : 返回信号质量
 输入参数  : 无
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : 00177591
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : eil_get_time
 功能描述  : 返回系统时间
 输入参数  : 无
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : 00177591
    修改内容   : 新生成函数

*****************************************************************************/
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

