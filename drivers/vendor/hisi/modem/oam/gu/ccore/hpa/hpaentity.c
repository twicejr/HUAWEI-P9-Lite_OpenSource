/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: HPAEntity.c                                                     */
/*                                                                           */
/* Author: Xu cheng                                                          */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-02                                                             */
/*                                                                           */
/* Description: implement HPA subroutine                                     */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 2008-02                                                          */
/*    Author: Xu cheng                                                       */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/

#include "hpacomm.h"

#include "bbp_wcdma_interface.h"
#include "DspInterface.h"
#include "apminterface.h"
#include "apmprocess.h"
#include "omprivate.h"
#include "sleepflow.h"
#include "rfa.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/* Macro of log */
/*lint -e767  修改人: m00128685；检视人：l46160 原因简述:打点日志文件宏ID定义*/
#define    THIS_FILE_ID        PS_FILE_ID_HPA_ENTITY_C
/*lint +e767  修改人: m00128685；检视人：l46160 */

#ifndef BIT
#define BIT(x)                  ((unsigned)0x1 << (x))
#endif

VOS_UINT32                              g_ulUsimLowPowerMap = 0;

/*****************************************************************************
 Function   : HPA_ReadCfnSfn
 Description: Read SFN & CFN from register
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_ReadCfnSfn(VOS_VOID)
{
    VOS_UINT16                          usHpaCfnRead;

    /* Read SFN */
    g_usHpaSfnRead = (VOS_UINT16)HPA_Read32Reg(WBBP_SFN_ADDR);
    g_usHpaSfnRead &= 0x0FFF; /* SFN Last 12 bit is vaild  */

    /* Read CFN */
    usHpaCfnRead = (VOS_UINT16)HPA_Read32Reg(WBBP_CFN_ADDR);
    /* SFN Last 8 bit is vaild  */
    g_ucHpaCfnRead = (VOS_UCHAR)(usHpaCfnRead & 0xFF);

    /* Tell MAC */
    /*g_stMacFnInfoInd.enMsgName = ID_PHY_MAC_INFO_IND;
    g_stMacFnInfoInd.usCfn = (VOS_UINT16)g_ucHpaCfnRead;
    g_stMacFnInfoInd.ulSfn = (VOS_UINT32)g_usHpaSfnRead;*/

    return;
}

/*****************************************************************************
 函 数 名  : HPA_USIMLowPowerLock
 功能描述  : 提供给USIM模块禁止睡眠接口
 输入参数  : VOS_UINT32 ulPid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月23日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID HPA_USIMLowPowerLock( VOS_UINT32 ulPid )
{
    MODEM_ID_ENUM_UINT16                    enModem;
    VOS_INT                                 lLockLevel;

    enModem = VOS_GetModemIDFromPid(ulPid);

    if (MODEM_ID_BUTT == enModem)
    {
        return;
    }

    lLockLevel = VOS_SplIMP();

    /* 收集USIM投票，确认是否满足唤醒投票 */
    g_ulUsimLowPowerMap   |= BIT(enModem);

    if ( 0 == g_ulUsimLowPowerMap )
    {
        VOS_Splx(lLockLevel);

        return;
    }

    VOS_Splx(lLockLevel);

    /*lint -e534*/
    mdrv_pm_wake_lock(PWRCTRL_SLEEP_USIM);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : HPA_USIMLowPowerUnLock
 功能描述  : 提供给USIM模块允许睡眠接口
 输入参数  : VOS_UINT32 ulPid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月23日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID HPA_USIMLowPowerUnLock( VOS_UINT32 ulPid )
{
    MODEM_ID_ENUM_UINT16                    enModem;
    VOS_INT                                 lLockLevel;

    enModem = VOS_GetModemIDFromPid(ulPid);

    if (MODEM_ID_BUTT == enModem)
    {
        return;
    }

    lLockLevel = VOS_SplIMP();

    /* 收集USIM投票，确认是否满足睡眠投票 */
    g_ulUsimLowPowerMap   &= (~ BIT(enModem));

    if ( 0 != g_ulUsimLowPowerMap )
    {
        VOS_Splx(lLockLevel);

        return;
    }

    VOS_Splx(lLockLevel);

    /*lint -e534*/
    mdrv_pm_wake_unlock(PWRCTRL_SLEEP_USIM);
    /*lint +e534*/

    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


