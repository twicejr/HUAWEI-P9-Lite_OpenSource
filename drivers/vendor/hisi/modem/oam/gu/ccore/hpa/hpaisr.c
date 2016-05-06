/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: HpaIsr.c                                                        */
/*                                                                           */
/* Author: Xu cheng                                                          */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-02                                                             */
/*                                                                           */
/* Description: implement HPA Isr subroutine                                 */
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
#include "bbp_wcdma_on_interface.h"
#include "bbp_wcdma_interface.h"
#include "bbp_gsm_on_interface.h"
#include "bbp_gsm_interface.h"
#include "bbp_cdma_on_interface.h"
#include "sleepflow.h"
#include "spysystem.h"
#include "apminterface.h"
#include "apmprocess.h"
#include "TtfOamInterface.h"
#include "HifiOmInterface.h"
#include "product_config.h"
#include "omprivate.h"
#include "psregrpt.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#include "cdma_timing_drv.h"

#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/* Macro of log */
/*lint -e767  修改人：m00128685；检视人: l46160；原因简述:打点日志文件宏ID定义*/
#define    THIS_FILE_ID        PS_FILE_ID_HPA_ISR_C
/*lint +e767 修改人：m00128685；检视人: l46160*/
typedef  void (*VOID_FUNCPTR) ();


/*记录ZSP Watch Dog中断号*/
VOS_INT             g_ulZSPWatchDogIntNO = 0;

/*记录HIFI Watch Dog中断号*/
VOS_INT             g_ulHIFIWatchDogIntNO =0;

/*记录GBBP 帧中断号*/
VOS_INT             g_aulGBBPIntNO[MODEM_ID_BUTT] = {0};

/*记录GBBP 唤醒中断号*/
VOS_INT             g_aulGBBPAwakeIntNO[MODEM_ID_BUTT] = {0};

/*记录SIMI 中断号*/
VOS_INT             g_ulSIMIIntNO = 0;

/*记录WBBP 帧中断号*/
VOS_INT             g_ulWBBP0MsIntNO = 0;

/*记录WBBP 唤醒中断号*/
VOS_INT             g_ulWBBPAwakeIntNO = 0;

/*记录CBBP 唤醒中断号*/
VOS_INT             g_ulCBBPAwakeIntNO = 0;

/*记录WBBP 时钟切换中断号*/
VOS_INT             g_ulWBBPSwtichIntNO = 0;

VOS_UINT32          g_ul3GISRNum = 0;
VOS_UINT32          g_ul2GISRNum0= 0;
VOS_UINT32          g_ul2GISRNum1= 0;
VOS_UINT32          g_ul2GISRNum2= 0;

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
extern VOS_VOID I1_SLEEP_32KIsr(SLEEP_MODE_ENUM_UINT32 enMode);
extern VOS_VOID I1_SLEEP_NormalClockIsr(SLEEP_MODE_ENUM_UINT32 enMode);
extern VOS_VOID I1_SLEEP_AwakeIsr(SLEEP_MODE_ENUM_UINT32 enMode);
extern VOS_BOOL I1_SLEEP_IsAwakeProc(SLEEP_MODE_ENUM_UINT32 enMode);
#if ( 3 == MULTI_MODEM_NUMBER )
/* Modem2中断处理接口 */
extern VOS_VOID I2_SLEEP_32KIsr(SLEEP_MODE_ENUM_UINT32 enMode);
extern VOS_VOID I2_SLEEP_NormalClockIsr(SLEEP_MODE_ENUM_UINT32 enMode);
extern VOS_VOID I2_SLEEP_AwakeIsr(SLEEP_MODE_ENUM_UINT32 enMode);
extern VOS_BOOL I2_SLEEP_IsAwakeProc(SLEEP_MODE_ENUM_UINT32 enMode);
#endif
#endif
/*****************************************************************************
 Function   : atomic_inc
 Description: increasde atomic counter.comes from linux
 Input      : atomic counter
 Return     : void
 Other      :
 *****************************************************************************/
void atomic_inc( hpa_atomic_t *v )
{
    int flags;

    flags = VOS_SplIMP();

    (v->counter)++;

    VOS_Splx(flags);

    return;
}

/*****************************************************************************
 Function   : HPA_3GIsrEnable
 Description: 3G Isr Enable
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_3GIsrEnable(MODEM_ID_ENUM_UINT16 enModemID)
{
#if 0
    if (MODEM_ID_0 == enModemID)
    {
        /*Clear W frmae interrupt*/
        HPA_Write32Reg(WBBP_ARM_INT01_CLR_ADDR, 1);

        /*Enable W frame interrupt*/
        HPA_Write32Reg(WBBP_ARM_INT01_MASK_ADDR, 0xFFFFFFFE);
        HPA_Write32Reg(WBBP_ARM_INT01_EN_ADDR, 1);
        mdrv_int_enable(g_ulWBBP0MsIntNO);
    }
#endif
    return;
}

/*****************************************************************************
 Function   : HPA_3GIsrDisable
 Description: 3G Isr Disable
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_3GIsrDisable(MODEM_ID_ENUM_UINT16 enModemID)
{
#if 0
    if (MODEM_ID_0 == enModemID)
    {
        /*Disable W frame INT*/
        mdrv_int_disable(g_ulWBBP0MsIntNO);

        /*Clear W frmae interrupt*/
        HPA_Write32Reg(WBBP_ARM_INT01_CLR_ADDR, 1);
    }
#endif
    return ;
}

/*****************************************************************************
 Function   : HPA_2GIsrEnable
 Description: 2G Isr Enable
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_2GIsrEnable(MODEM_ID_ENUM_UINT16 enModemID)
{
#if 0
    if (MODEM_ID_BUTT <= enModemID)
    {
        return;
    }

    /* clear interrupt */
    HPA_Write32Reg(g_aulGUCBBPRegAddr[INT_CLR][enModemID], 1);

    /*Enable G frame interrupt*/
    HPA_Clear32RegMask(g_aulGUCBBPRegAddr[INT_MASK][enModemID], OAM_GBBP_FRAME_INT_BIT);

    /*lint -e662 -e661*/
    mdrv_int_enable(g_aulGBBPIntNO[enModemID]);
    /*lint +e662 +e661*/
#endif
    return;
}

/*****************************************************************************
 Function   : HPA_2GIsrDisable
 Description: 2G Isr Disable
 Input      : MODEM_ID_ENUM_UINT16 enModemID
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_2GIsrDisable(MODEM_ID_ENUM_UINT16 enModemID)
{
#if 0
    if (MODEM_ID_BUTT <= enModemID)
    {
        return;
    }

    /*Disable W frame INT*/
    /*lint -e662 -e661*/
    mdrv_int_disable(g_aulGBBPIntNO[enModemID]);
    /*lint +e662 +e661*/

    /* clear interrupt */
    HPA_Write32Reg(g_aulGUCBBPRegAddr[INT_CLR][enModemID], 1);
#endif
    return ;
}

/*lint -e960 修改人：甘兰47350；检视人：xucheng 51137；原因简述：清中断*/

/*****************************************************************************
 Function   : HPA_2GFrameClockIsr
 Description: Gsm BBP frame and clock switch ISR
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_2GFrameClockIsr(MODEM_ID_ENUM_UINT16 enModemID)
{
    VOS_UINT32                          ulDrxStatus;
    VOS_UINT32                          ulBeginSlice;

    if (enModemID >= MODEM_ID_BUTT)
    {
        return;
    }

    if (PWRCTRL_COMM_OFF == mdrv_pm_get_pwrstatus((PWC_COMM_MODE_E)VOS_RATMODE_GSM,
                                                  PWC_COMM_MODULE_BBP_DRX,
                                                  (PWC_COMM_MODEM_E)enModemID,
                                                  PWC_COMM_CHANNEL_0))
    {
        VOS_ProtectionReboot(DRX_REPORT_BBP_POWERDOWN_ERROR, PS_FILE_ID_HPA_ISR_C, __LINE__,
                             VOS_NULL_PTR, 0);

        return;
    }

    /*lint -e662 -e661 -e534*/
    mdrv_int_disable(g_aulGBBPIntNO[enModemID]);
    /*lint +e662 +e661 +e534*/

#if 0
    ulBbpStatus = HPA_Read32Reg(g_aulGUCBBPRegAddr[INT_STA][enModemID]) & OAM_GBBP_FRAME_INT_BIT;

    HPA_Write32RegMask(g_aulGUCBBPRegAddr[INT_CLR][enModemID], ulBbpStatus );
#endif

    ulDrxStatus = HPA_Read32Reg(g_aulGUCBBPRegAddr[DRX_INT_STA][enModemID][VOS_RATMODE_GSM]) & (OAM_GBBP_DRX_CLK_SWITCH_32K_INT_BIT | OAM_GBBP_DRX_CLK_SWITCH_52M_INT_BIT);

    HPA_Write32RegMask(g_aulGUCBBPRegAddr[DRX_INT_CLR][enModemID][VOS_RATMODE_GSM], ulDrxStatus );

#if 0
    if ( 0 != ( OAM_GBBP_FRAME_INT_BIT & ulBbpStatus ) )
    {
        ulBeginSlice = OM_GetSlice();

        while((0 != (HPA_Read32Reg(g_aulGUCBBPRegAddr[INT_STA][enModemID]) & OAM_GBBP_FRAME_INT_BIT))
            &&(BBP_DRX_INT_SLICE_COUNT > (OM_GetSlice() - ulBeginSlice)))
        {
            ;
        }
    }
#endif

    if ((0 != ( OAM_GBBP_DRX_CLK_SWITCH_32K_INT_BIT & ulDrxStatus))
        || (0 != ( OAM_GBBP_DRX_CLK_SWITCH_52M_INT_BIT & ulDrxStatus)))
    {
        ulBeginSlice = OM_GetSlice();

        while((0 != (HPA_Read32Reg(g_aulGUCBBPRegAddr[DRX_INT_STA][enModemID][VOS_RATMODE_GSM]) & (OAM_GBBP_DRX_CLK_SWITCH_32K_INT_BIT | OAM_GBBP_DRX_CLK_SWITCH_52M_INT_BIT)))
            &&(BBP_DRX_INT_SLICE_COUNT > (OM_GetSlice() - ulBeginSlice)))
        {
            ;
        }
    }

#if 0
    if ( 0 != ( OAM_GBBP_FRAME_INT_BIT & ulBbpStatus ) )
    {
        /*lint -e661*/
        g_stHpaIntCount.aulPpIntNum[enModemID]++;
        g_stHpaIntCount.aulPpIntSlice[enModemID] = OM_GetSlice();
        /*lint +e661*/

        if(MODEM_ID_1 == enModemID)
        {
            g_ul2GISRNum1++;

            atomic_inc(&g_stGDsp1MailBoxTransferCount);
        }
        else
        {
            g_ul2GISRNum0++;

        }

        /*lint -e534*/
        VOS_SmV(g_ulHpaTransferSem);
        /*lint +e534*/
    }
#endif

    if (0 != ( OAM_GBBP_DRX_CLK_SWITCH_32K_INT_BIT & ulDrxStatus))
    {
        if ((MODEM_ID_0 == enModemID) || (MODEM_ID_2 == enModemID))
        {
            SLEEP_32KIsr(VOS_RATMODE_GSM);
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
        #if ( 3 == MULTI_MODEM_NUMBER )
            I2_SLEEP_32KIsr(VOS_RATMODE_GSM);
        #endif
#endif
        }

/*lint -e718 -e746 修改人:ganlan;检视人:徐铖 51137 */
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
        if (MODEM_ID_1 == enModemID)
        {
            I1_SLEEP_32KIsr(VOS_RATMODE_GSM);
        }
#endif
/*lint +e718 +e746 修改人:ganlan;检视人:徐铖 51137 */

    }

    if (0 != ( OAM_GBBP_DRX_CLK_SWITCH_52M_INT_BIT & ulDrxStatus))
    {
        if ((MODEM_ID_0 == enModemID) || (MODEM_ID_2 == enModemID))
        {
            SLEEP_NormalClockIsr(VOS_RATMODE_GSM);
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
        #if ( 3 == MULTI_MODEM_NUMBER )
            I2_SLEEP_NormalClockIsr(VOS_RATMODE_GSM);
        #endif
#endif
        }

/*lint -e718 -e746 修改人:ganlan;检视人:徐铖 51137 */
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
        if (MODEM_ID_1 == enModemID)
        {
            I1_SLEEP_NormalClockIsr(VOS_RATMODE_GSM);
        }
#endif
/*lint +e718 +e746 修改人:ganlan;检视人:徐铖 51137 */
    }

    /*lint -e662 -e661 -e534*/
    mdrv_int_enable(g_aulGBBPIntNO[enModemID]);
    /*lint +e662 +e661 +e534*/
}

/*****************************************************************************
 Function   : HPA_2GAwakeIsr
 Description: Gsm BBP0 frame and clock isr
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_2GFrameClockIsr0(VOS_VOID)
{
    HPA_2GFrameClockIsr(MODEM_ID_0);
}

/*****************************************************************************
 Function   : HPA_2GAwakeIsr
 Description: Gsm BBP0 frame and clock isr
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_2GFrameClockIsr1(VOS_VOID)
{
    HPA_2GFrameClockIsr(MODEM_ID_1);
}

/*****************************************************************************
 Function   : HPA_2GAwakeIsr
 Description: Gsm BBP0 frame and clock isr
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_2GFrameClockIsr2(VOS_VOID)
{
    HPA_2GFrameClockIsr(MODEM_ID_2);
}

/*****************************************************************************
 Function   : HPA_2GAwakeIsr
 Description: Gsm Awake isr
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_2GAwakeIsr(MODEM_ID_ENUM_UINT16 enModemID)
{
    VOS_UINT32  ulBeginSlice;

    if(enModemID >= MODEM_ID_BUTT)
    {
        return;
    }

    /*lint -e662 -e661 -e534*/
    mdrv_int_disable(g_aulGBBPAwakeIntNO[enModemID]);
    /*lint +e662 +e661 +e534*/

    if ((MODEM_ID_0 == enModemID) || (MODEM_ID_2 == enModemID))
    {
        SLEEP_AwakeIsr(VOS_RATMODE_GSM);
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    #if ( 3 == MULTI_MODEM_NUMBER )
        I2_SLEEP_AwakeIsr(VOS_RATMODE_GSM);
    #endif
#endif
    }

/*lint -e718 -e746 修改人:ganlan;检视人:徐铖 51137 */
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    if (MODEM_ID_1 == enModemID)
    {
        I1_SLEEP_AwakeIsr(VOS_RATMODE_GSM);
    }
#endif
/*lint +e718 +e746 修改人:ganlan;检视人:徐铖 51137 */

    /*lint -e662 -e661 -e534*/
    HPA_Write32RegMask(g_aulGUCBBPRegAddr[DRX_INT_CLR][enModemID][VOS_RATMODE_GSM], OAM_GBBP_WAKE_UP_INT_BIT );
    /*lint +e662 +e661 +e534*/

    ulBeginSlice = OM_GetSlice();

    /*lint -e662 -e661 -e534*/
    while((0 != (HPA_Read32Reg(g_aulGUCBBPRegAddr[DRX_INT_STA][enModemID][VOS_RATMODE_GSM]) & (OAM_GBBP_WAKE_UP_INT_BIT)))
        &&(BBP_DRX_INT_SLICE_COUNT > (OM_GetSlice() - ulBeginSlice)))
    {
        ;
    }
    /*lint +e662 +e661 +e534*/

    /*lint -e662 -e661 -e534*/
    mdrv_int_enable(g_aulGBBPAwakeIntNO[enModemID]);
    /*lint +e662 +e661 +e534*/

    return;
}

/*****************************************************************************
 Function   : HPA_2GAwakeIsr0
 Description: ISR of BBP0 Awack ISR
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/

VOS_VOID HPA_2GAwakeIsr0(VOS_VOID)
{
    HPA_2GAwakeIsr(MODEM_ID_0);
}

/*****************************************************************************
 Function   : HPA_2GAwakeIsr0
 Description: ISR of BBP0 Awack ISR
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/

VOS_VOID HPA_2GAwakeIsr1(VOS_VOID)
{
    HPA_2GAwakeIsr(MODEM_ID_1);
}

/*****************************************************************************
 函 数 名  : HPA_2GAwakeIsr2
 功能描述  : Modem2 GBBP唤醒中断服务程序
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID HPA_2GAwakeIsr2( VOS_VOID )
{
    HPA_2GAwakeIsr(MODEM_ID_2);
}

#if (FEATURE_GUDRX_NEWVERSION == FEATURE_ON)
/*****************************************************************************
 Function   : HPA_2GFrameClockIsr
 Description: Gsm BBP frame and clock switch ISR
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_2GDrxIsr(MODEM_ID_ENUM_UINT16 enModemID)
{
    VOS_UINT32                          ulDrxStatus;
    VOS_UINT32                          ulBeginSlice;

    if (enModemID >= MODEM_ID_BUTT)
    {
        return;
    }

    /*lint -e662 -e661 -e534*/
    mdrv_int_disable(g_aulGBBPIntNO[enModemID]);
    /*lint +e662 +e661 +e534*/

    ulDrxStatus = HPA_Read32Reg(g_aulGUCBBPRegAddr[DRX_INT_STA][enModemID][VOS_RATMODE_GSM]) &
                                      (OAM_GBBP_WAKE_UP_INT_BIT|
                                       OAM_GBBP_DRX_CLK_SWITCH_32K_INT_BIT|
                                       OAM_GBBP_DRX_CLK_SWITCH_52M_INT_BIT);

    HPA_Write32RegMask(g_aulGUCBBPRegAddr[DRX_INT_CLR][enModemID][VOS_RATMODE_GSM], ulDrxStatus );

    if ((0 != ( OAM_GBBP_WAKE_UP_INT_BIT & ulDrxStatus))
        || (0 != ( OAM_GBBP_DRX_CLK_SWITCH_32K_INT_BIT & ulDrxStatus))
        || (0 != ( OAM_GBBP_DRX_CLK_SWITCH_52M_INT_BIT & ulDrxStatus)))
    {
        ulBeginSlice = OM_GetSlice();

        while((0 != (HPA_Read32Reg(g_aulGUCBBPRegAddr[DRX_INT_STA][enModemID][VOS_RATMODE_GSM]) & (OAM_GBBP_WAKE_UP_INT_BIT | OAM_GBBP_DRX_CLK_SWITCH_32K_INT_BIT | OAM_GBBP_DRX_CLK_SWITCH_52M_INT_BIT)))
            &&(BBP_DRX_INT_SLICE_COUNT > (OM_GetSlice() - ulBeginSlice)))
        {
            ;
        }
    }

    /*lint -e718 -e746 修改人:ganlan;检视人:徐铖 51137 */
    if (0 != ( OAM_GBBP_WAKE_UP_INT_BIT & ulDrxStatus))
    {
        if (MODEM_ID_0 == enModemID)
        {
            SLEEP_AwakeIsr(VOS_RATMODE_GSM);
        }
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
        if (MODEM_ID_1 == enModemID)
        {
            I1_SLEEP_AwakeIsr(VOS_RATMODE_GSM);
        }
#endif
    }

    if (0 != ( OAM_GBBP_DRX_CLK_SWITCH_32K_INT_BIT & ulDrxStatus))
    {
        if (MODEM_ID_0 == enModemID)
        {
            SLEEP_32KIsr(VOS_RATMODE_GSM);
        }
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
        if (MODEM_ID_1 == enModemID)
        {
            I1_SLEEP_32KIsr(VOS_RATMODE_GSM);
        }
#endif
    }

    if (0 != ( OAM_GBBP_DRX_CLK_SWITCH_52M_INT_BIT & ulDrxStatus))
    {
        if (MODEM_ID_0 == enModemID)
        {
            SLEEP_NormalClockIsr(VOS_RATMODE_GSM);
        }
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
        if (MODEM_ID_1 == enModemID)
        {
            I1_SLEEP_NormalClockIsr(VOS_RATMODE_GSM);
        }
#endif
    }
    /*lint +e718 +e746 修改人:ganlan;检视人:徐铖 51137 */

    /*lint -e662 -e661 -e534*/
    mdrv_int_enable(g_aulGBBPIntNO[enModemID]);
    /*lint +e662 +e661 +e534*/
}

/*****************************************************************************
 Function   : HPA_2GDrxIsr0
 Description: Gsm BBP0 drx isr
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_2GDrxIsr0(VOS_VOID)
{
    HPA_2GDrxIsr(MODEM_ID_0);
}

/*****************************************************************************
 Function   : HPA_2GDrxIsr1
 Description: Gsm BBP1 drx isr
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_2GDrxIsr1(VOS_VOID)
{
    HPA_2GDrxIsr(MODEM_ID_1);
}

/*****************************************************************************
 Function   : HPA_2GAwakeIsr
 Description: Gsm BBP2 drx isr
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_2GDrxIsr2(VOS_VOID)
{
}
#endif

#if 0
/*****************************************************************************
 Function   : HPA_3G0MsIsr
 Description: ISR of R99 0ms
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_3G0MsIsr(VOS_VOID)
{
    if (PWRCTRL_COMM_OFF == mdrv_pm_get_pwrstatus((PWC_COMM_MODE_E)VOS_RATMODE_WCDMA,
                                                  PWC_COMM_MODULE_BBP_DRX,
                                                  (PWC_COMM_MODEM_E)MODEM_ID_0,
                                                  PWC_COMM_CHANNEL_0))
    {
        VOS_ProtectionReboot(DRX_REPORT_BBP_POWERDOWN_ERROR, PS_FILE_ID_HPA_ISR_C, __LINE__,
                VOS_NULL_PTR, 0);

        return;
    }

    mdrv_int_disable(g_ulWBBP0MsIntNO);

    /* Clear interrupt */
    HPA_Write32Reg(WBBP_ARM_INT01_CLR_ADDR, 1);

    g_stHpaIntCount.ul0msIntNum++;
    g_stHpaIntCount.ul0msIntSlice = OM_GetSlice();

#ifdef HPA_ITT
    Stub_RttRegGet();

    if ( VOS_NULL_PTR != g_pfnHpaDspIsrStub )
    {
        g_pfnHpaDspIsrStub();
    }
#endif

    /* Read SFN & CFN */
    HPA_ReadCfnSfn();

    /* Trigger HPA_TransferTaskEntry task to transfer msg
       between ARM and DSP.*/
    /*lint -e534*/
    VOS_SmV(g_ulHpaTransferSem);
    /*lint +e534*/

    g_ul3GISRNum++;

    mdrv_int_enable(g_ulWBBP0MsIntNO);

    return ;
}
#endif

/*****************************************************************************
 Function   : HPA_3GAwakeIsr
 Description: ISR of W Wake INT
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_3GAwakeIsr(VOS_VOID)
{
    VOS_UINT32      ulRegValue;
    VOS_UINT32      ulBeginSlice;

    /*lint -e534*/
    mdrv_int_disable(g_ulWBBPAwakeIntNO);
    /*lint +e534*/

    SLEEP_AwakeIsr(VOS_RATMODE_WCDMA);

    ulRegValue = HPA_Read32Reg(WBBP_ARM_INT02_STA_ADDR);

    /* Clear interrupt */
    HPA_Write32Reg(WBBP_ARM_INT02_CLR_1CARD_ADDR, ulRegValue);

    ulBeginSlice = OM_GetSlice();

    while((0 != HPA_Read32Reg(WBBP_ARM_INT02_STA_ADDR))
        &&(BBP_DRX_INT_SLICE_COUNT > (OM_GetSlice() - ulBeginSlice)))
    {
        ;
    }

    /*lint -e534*/
    mdrv_int_enable(g_ulWBBPAwakeIntNO);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 Function   : HPA_2GFrameIsr_CB
 Description: Gsm BBP frame and clock switch ISR
              为确保时序，该函数只能在中断上下文中运行，否则单板复位
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_2GFrameIsr_CB(MODEM_ID_ENUM_UINT16 enModemID)
{
    if (enModemID >= MODEM_ID_BUTT)
    {
        return;
    }

    /*lint -e661*/
    g_stHpaIntCount.aulPpIntNum[enModemID]++;
    g_stHpaIntCount.aulPpIntSlice[enModemID] = OM_GetSlice();
    /*lint +e661*/

    /* 确保在中断上下文中运行 */
    if (VOS_FALSE == VOS_CheckInterrupt())
    {
        VOS_ProtectionReboot(HPA_2GFRAME_ISR_NOT_INTERRUPT_CALL,
                             (VOS_INT)PS_FILE_ID_HPA_ISR_C,
                             (VOS_INT)enModemID,
                             (VOS_CHAR *)VOS_NULL_PTR,
                             0);
        return;
    }

    if ( MAIL_BOX_PROTECTWORD_SND == g_ulOmNosigEnable )
    {
        if ((VOS_RATMODE_GSM == g_usListModeCurrentMode)
         && (enModemID == g_enListModeWorkModem))
        {
            /*lint -e534*/
            VOS_SmV(g_ulHpaTransferSem);
            /*lint +e534*/
        }
    }

#if (FEATURE_GUC_BBP_TRIG == FEATURE_OFF)

    if (MODEM_ID_0 == enModemID)
    {
        g_ul2GISRNum0++;
        PsRegCapture(PS_REG_SYS_MODE_GSM);
    }
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )

#if (3 == MULTI_MODEM_NUMBER)
    else if (MODEM_ID_2 == enModemID)
    {
        PsRegCapture(PS_REG_SYS_MODE_GSM2);
        g_ul2GISRNum2++;
    }
#endif
    else
    {
        g_ul2GISRNum1++;
        PsRegCapture(PS_REG_SYS_MODE_GSM1);
    }
#endif

#endif

    return;
}

/*****************************************************************************
 Function   : HPA_3GFrameIsr_CB
 Description: ISR of R99 0ms
              为确保时序，该函数只能在中断上下文中运行，否则单板复位
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_3GFrameIsr_CB(VOS_VOID)
{
    /* 确保在中断上下文中运行 */
    if(VOS_FALSE == VOS_CheckInterrupt())
    {
        VOS_ProtectionReboot(HPA_3GFRAME_ISR_NOT_INTERRUPT_CALL, (VOS_INT)PS_FILE_ID_HPA_ISR_C,
                             (VOS_INT)__LINE__, (VOS_CHAR *)VOS_NULL_PTR, 0);
        return;
    }

    g_stHpaIntCount.ul0msIntNum++;
    g_stHpaIntCount.ul0msIntSlice = OM_GetSlice();

#ifdef HPA_ITT
    Stub_RttRegGet();

    if ( VOS_NULL_PTR != g_pfnHpaDspIsrStub )
    {
        g_pfnHpaDspIsrStub();
    }
#endif

    /* Read SFN & CFN */
    HPA_ReadCfnSfn();

    /* Trigger HPA_TransferTaskEntry task to transfer msg
       between ARM and DSP.*/
    if ( MAIL_BOX_PROTECTWORD_SND == g_ulOmNosigEnable )
    {
        if (VOS_RATMODE_WCDMA == g_usListModeCurrentMode)
        {
            /*lint -e534*/
            VOS_SmV(g_ulHpaTransferSem);
            /*lint +e534*/
        }
    }

#if (FEATURE_GUC_BBP_TRIG == FEATURE_OFF)
    PsRegCapture(PS_REG_SYS_MODE_WCDMA);
#endif

    g_ul3GISRNum++;

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID HPA_10msOffsetCdmaIsr(CDMA_TIME pstCdmaSysTime, VOS_VOID *pvParam)
{
    if ( (MAIL_BOX_PROTECTWORD_SND == g_ulOmNosigEnable )
     &&  (VOS_RATMODE_1X == g_usListModeCurrentMode) )
    {
        /*lint -e534*/
        VOS_SmV(g_ulHpaTransferSem);
        /*lint +e534*/
    }
}
#endif

/*****************************************************************************
 Function   : HPA_BbpAwakeIsr
 Description: Gsm&Wcdma Drx isr,Only used for asic platform
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_3GSwitchClockIsr(VOS_VOID)
{
    VOS_UINT32  ulBbpStatus;
    VOS_UINT32  ulBeginSlice;

    /*lint -e534*/
    mdrv_int_disable(g_ulWBBPSwtichIntNO);
    /*lint +e534*/

    ulBbpStatus = HPA_Read32Reg(WBBP_ARM_INT03_STA_ADDR);

    /* Clear interrupt */
    HPA_Write32Reg(WBBP_ARM_INT03_CLR_1CARD_ADDR, ulBbpStatus);

    if(0 != ulBbpStatus)
    {
        ulBeginSlice = OM_GetSlice();

        while((0 != HPA_Read32Reg(WBBP_ARM_INT03_STA_ADDR))
            &&(BBP_DRX_INT_SLICE_COUNT > (OM_GetSlice() - ulBeginSlice)))
        {
            ;
        }

        if( BIT_N(WSLEEP_64M_TO_32K_TYPE_BIT) & ulBbpStatus )
        {
            SLEEP_32KIsr(VOS_RATMODE_WCDMA);
        }
        else if (BIT_N(WSLEEP_32K_TO_64M_TYPE_BIT) & ulBbpStatus)
        {
            SLEEP_NormalClockIsr(VOS_RATMODE_WCDMA);
        }
        else
        {
            ;
        }
    }

    /*lint -e534*/
    mdrv_int_enable(g_ulWBBPSwtichIntNO);
    /*lint +e534*/

    return;
}

/*lint +e960 修改人：甘兰47350；检视人：xucheng；*/

/*****************************************************************************
 Function   : HPA_Conncet2GISR0
 Description: 2G Isr Connect
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_Conncet2GISR0(VOS_VOID)
{
    VOS_INT                             lIntLevel;

#if (FEATURE_GUDRX_NEWVERSION == FEATURE_ON)
    /*CCPU单独复位挂接中断前需清中断*/
    HPA_Write32RegMask(g_aulGUCBBPRegAddr[DRX_INT_CLR][MODEM_ID_0][VOS_RATMODE_GSM],
                        OAM_GBBP_WAKE_UP_INT_BIT|
                        OAM_GBBP_DRX_CLK_SWITCH_32K_INT_BIT|
                        OAM_GBBP_DRX_CLK_SWITCH_52M_INT_BIT);

    /*挂接BBP0 BSP_INT_TYPE_GBBP_AWAKE中断*/
    lIntLevel = mdrv_int_get_num(BSP_INT_TYPE_GBBP_AWAKE);  /*获取BSP_INT_TYPE_GBBP_AWAKE的值*/

    /*lint -e534*/
    mdrv_int_connect(lIntLevel, (VOIDFUNCPTR)HPA_2GDrxIsr0, 0);
    /*lint +e534*/

    /* 默认屏蔽该mask位 */
    HPA_Clear32RegMask(g_aulGUCBBPRegAddr[DRX_INT_MASK][MODEM_ID_0][VOS_RATMODE_GSM],
                        OAM_GBBP_WAKE_UP_INT_BIT|
                        OAM_GBBP_DRX_CLK_SWITCH_32K_INT_BIT|               /* 2G Bbp Switch 32k Int */
                        OAM_GBBP_DRX_CLK_SWITCH_52M_INT_BIT);              /* 2G Bbp Switch 52M Int */

    /*lint -e534*/
    mdrv_int_enable(lIntLevel);  /*使能BSP_INT_TYPE_GBBP的中断*/
    /*lint +e534*/

    g_aulGBBPIntNO[MODEM_ID_0] = lIntLevel;

#else
    HPA_Write32RegMask(g_aulGUCBBPRegAddr[INT_CLR][MODEM_ID_0][VOS_RATMODE_GSM], OAM_GBBP_FRAME_INT_BIT );

    /*CCPU单独复位挂接中断前需清中断*/
    HPA_Write32RegMask(g_aulGUCBBPRegAddr[DRX_INT_CLR][MODEM_ID_0][VOS_RATMODE_GSM],
                        OAM_GBBP_DRX_CLK_SWITCH_32K_INT_BIT|
                        OAM_GBBP_DRX_CLK_SWITCH_52M_INT_BIT);

    /*挂接BBP0 BSP_INT_TYPE_GBBP中断*/
    lIntLevel = mdrv_int_get_num(BSP_INT_TYPE_GBBP);  /*获取BSP_INT_TYPE_GBBP的值*/

    /*lint -e534*/
    mdrv_int_connect(lIntLevel, (VOIDFUNCPTR)HPA_2GFrameClockIsr0, 0);
    /*lint +e534*/

#if 0
    HPA_Clear32RegMask(g_aulGUCBBPRegAddr[INT_MASK][MODEM_ID_0], OAM_GBBP_FRAME_INT_BIT);    /* 2G Bbp Frame Int */
#endif
    /* 默认屏蔽该mask位 */
    HPA_Write32RegMask(g_aulGUCBBPRegAddr[INT_MASK][MODEM_ID_0][VOS_RATMODE_GSM], OAM_GBBP_FRAME_INT_BIT);    /* 2G Bbp Frame Int */

    HPA_Clear32RegMask(g_aulGUCBBPRegAddr[DRX_INT_MASK][MODEM_ID_0][VOS_RATMODE_GSM],
                        OAM_GBBP_DRX_CLK_SWITCH_32K_INT_BIT|               /* 2G Bbp Switch 32k Int */
                        OAM_GBBP_DRX_CLK_SWITCH_52M_INT_BIT);              /* 2G Bbp Switch 52M Int */

    /*lint -e534*/
    mdrv_int_enable(lIntLevel);  /*使能BSP_INT_TYPE_GBBP的中断*/
    /*lint +e534*/

    g_aulGBBPIntNO[MODEM_ID_0] = lIntLevel;

    /*CCPU单独复位挂接中断前需清中断*/
    HPA_Write32RegMask(g_aulGUCBBPRegAddr[DRX_INT_CLR][MODEM_ID_0][VOS_RATMODE_GSM], OAM_GBBP_WAKE_UP_INT_BIT );

    /*挂接BBP0 BSP_INT_TYPE_GBBP_AWAKE中断*/
    lIntLevel = mdrv_int_get_num(BSP_INT_TYPE_GBBP_AWAKE);  /*获取BSP_INT_TYPE_GBBP_AWAKE的值*/

    /*lint -e534*/
    mdrv_int_connect(lIntLevel, (VOIDFUNCPTR)HPA_2GAwakeIsr0, 0);
    /*lint +e534*/

    HPA_Clear32RegMask(g_aulGUCBBPRegAddr[DRX_INT_MASK][MODEM_ID_0][VOS_RATMODE_GSM], OAM_GBBP_WAKE_UP_INT_BIT);   /* 2G Bbp Wake up Int */

    /*lint -e534*/
    mdrv_int_enable(lIntLevel);  /*使能BSP_INT_TYPE_GBBP_AWAKE的中断*/
    /*lint +e534*/

    g_aulGBBPAwakeIntNO[MODEM_ID_0] = lIntLevel;

#endif

    return;
}

/*****************************************************************************
 Function   : HPA_Conncet2GISR1
 Description: 2G Isr Connect
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_Conncet2GISR1(VOS_VOID)
{
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    VOS_INT32                           lIntLevel;

#if (FEATURE_GUDRX_NEWVERSION == FEATURE_ON)
    /*CCPU单独复位挂接中断前需清中断*/
    HPA_Write32RegMask(g_aulGUCBBPRegAddr[DRX_INT_CLR][MODEM_ID_1][VOS_RATMODE_GSM],
                        OAM_GBBP_WAKE_UP_INT_BIT|
                        OAM_GBBP_DRX_CLK_SWITCH_32K_INT_BIT|
                        OAM_GBBP_DRX_CLK_SWITCH_52M_INT_BIT);

    /*挂接BBP1 BSP_INT_TYPE_GBBP_AWAKE中断*/
    lIntLevel = mdrv_int_get_num(BSP_INT_TYPE_GBBP1_AWAKE);     /*获取BSP_INT_TYPE_GBBP1_AWAKE的值*/

    /*lint -e534*/
    mdrv_int_connect(lIntLevel, (VOIDFUNCPTR)HPA_2GDrxIsr1, 0);
    /*lint +e534*/

    /* 默认屏蔽该mask位 */
    HPA_Clear32RegMask(g_aulGUCBBPRegAddr[DRX_INT_MASK][MODEM_ID_1][VOS_RATMODE_GSM],
                        OAM_GBBP_WAKE_UP_INT_BIT|
                        OAM_GBBP_DRX_CLK_SWITCH_32K_INT_BIT|               /* 2G Bbp Switch 32k Int */
                        OAM_GBBP_DRX_CLK_SWITCH_52M_INT_BIT);              /* 2G Bbp Switch 52M Int */

    /*lint -e534*/
    mdrv_int_enable(lIntLevel);  /*使能BSP_INT_TYPE_GBBP的中断*/
    /*lint +e534*/

    g_aulGBBPIntNO[MODEM_ID_1] = lIntLevel;

#else
    HPA_Write32RegMask(g_aulGUCBBPRegAddr[INT_CLR][MODEM_ID_1][VOS_RATMODE_GSM], OAM_GBBP_FRAME_INT_BIT );

    /*CCPU单独复位挂接中断前需清中断*/
    HPA_Write32RegMask(g_aulGUCBBPRegAddr[DRX_INT_CLR][MODEM_ID_1][VOS_RATMODE_GSM],
                        OAM_GBBP_DRX_CLK_SWITCH_32K_INT_BIT|
                        OAM_GBBP_DRX_CLK_SWITCH_52M_INT_BIT);

    /*挂接BBP1 BSP_INT_TYPE_GBBP中断*/
    lIntLevel = mdrv_int_get_num(BSP_INT_TYPE_GBBP1);  /*获取BSP_INT_TYPE_GBBP1的值*/

    /*lint -e534*/
    mdrv_int_connect(lIntLevel, (VOIDFUNCPTR)HPA_2GFrameClockIsr1, 0);
    /*lint +e534*/

#if 0
    HPA_Clear32RegMask(g_aulGUCBBPRegAddr[INT_MASK][MODEM_ID_1], OAM_GBBP_FRAME_INT_BIT);    /* 2G Bbp Frame Int */
#endif
    /* 默认屏蔽该mask位 */
    HPA_Write32RegMask(g_aulGUCBBPRegAddr[INT_MASK][MODEM_ID_1][VOS_RATMODE_GSM], OAM_GBBP_FRAME_INT_BIT);    /* 2G Bbp Frame Int */

    HPA_Clear32RegMask(g_aulGUCBBPRegAddr[DRX_INT_MASK][MODEM_ID_1][VOS_RATMODE_GSM],
                        OAM_GBBP_DRX_CLK_SWITCH_32K_INT_BIT|               /* 2G Bbp Switch 32k Int */
                        OAM_GBBP_DRX_CLK_SWITCH_52M_INT_BIT);              /* 2G Bbp Switch 52M Int */

    /*lint -e534*/
    mdrv_int_enable(lIntLevel);  /*使能BSP_INT_TYPE_GBBP的中断*/
    /*lint +e534*/

    g_aulGBBPIntNO[MODEM_ID_1] = lIntLevel;

    /*CCPU单独复位挂接中断前需清中断*/
    HPA_Write32RegMask(g_aulGUCBBPRegAddr[DRX_INT_CLR][MODEM_ID_1][VOS_RATMODE_GSM], OAM_GBBP_WAKE_UP_INT_BIT );

    /*挂接BBP0 BSP_INT_TYPE_GBBP_AWAKE中断*/
    lIntLevel = mdrv_int_get_num(BSP_INT_TYPE_GBBP1_AWAKE);  /*获取BSP_INT_TYPE_GBBP_AWAKE的值*/

    /*lint -e534*/
    mdrv_int_connect(lIntLevel, (VOIDFUNCPTR)HPA_2GAwakeIsr1, 0);
    /*lint +e534*/

    HPA_Clear32RegMask(g_aulGUCBBPRegAddr[DRX_INT_MASK][MODEM_ID_1][VOS_RATMODE_GSM], OAM_GBBP_WAKE_UP_INT_BIT);   /* 2G Bbp Wake up Int */

    /*lint -e534*/
    mdrv_int_enable(lIntLevel);  /*使能BSP_INT_TYPE_GBBP_AWAKE的中断*/
    /*lint +e534*/

    g_aulGBBPAwakeIntNO[MODEM_ID_1] = lIntLevel;
#endif
#endif

    return;
}

/*****************************************************************************
 函 数 名  : HPA_Conncet2GISR2
 功能描述  : 挂接Modem2 GSM中断处理流程
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID HPA_Conncet2GISR2( VOS_VOID )
{
    /* Austin上由于没有Modem2独立的GBBP，不需要单独挂接 */

    return;
}

/*****************************************************************************
 Function   : HPA_Conncet3GISR
 Description: 3G Isr Connect
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_Conncet3GISR(VOS_VOID)
{
    VOS_INT32                           lIntLevel;
#if 0
    /*CCPU单独复位挂接中断前需清中断*/
    HPA_Write32Reg(WBBP_ARM_INT01_CLR_ADDR, 1);

    /*Connect W BBP interrupt*/
    lIntLevel = mdrv_int_get_num(BSP_INT_TYPE_WBBP_0MS);  /*查询BSP_INT_TYPE_WBBP_0MS*/
    mdrv_int_connect(lIntLevel, (VOIDFUNCPTR)HPA_3G0MsIsr, 0);
    HPA_Write32Reg(WBBP_ARM_INT01_MASK_ADDR, 0xFFFFFFFE);
    HPA_Write32Reg(WBBP_ARM_INT01_EN_ADDR, 1);
    mdrv_int_enable(lIntLevel);    /*使能BSP_INT_TYPE_WBBP_0MS*/

    g_ulWBBP0MsIntNO = lIntLevel;
#endif

    /*CCPU单独复位挂接中断前需清中断*/
    HPA_Write32Reg(WBBP_ARM_INT02_CLR_1CARD_ADDR, 1);

    /*Connect W BBP DRX interrupt*/
    lIntLevel = mdrv_int_get_num(BSP_INT_TYPE_WBBP_AWAKE);  /*查询BSP_INT_TYPE_WBBP_AWAKE*/
    /*lint -e534*/
    mdrv_int_connect(lIntLevel, (VOIDFUNCPTR)HPA_3GAwakeIsr, 0);
    /*lint +e534*/
    HPA_Write32Reg(WBBP_ARM_INT02_MASK_1CARD_ADDR, 0xFFFFFFFC);
    HPA_Write32Reg(WBBP_ARM_INT02_EN_ADDR, 1);
    /*lint -e534*/
    mdrv_int_enable(lIntLevel);    /*使能BSP_INT_TYPE_WBBP_AWAKE*/
    /*lint +e534*/

    g_ulWBBPAwakeIntNO = lIntLevel;

    /*CCPU单独复位挂接中断前需清中断*/
    HPA_Write32Reg(WBBP_ARM_INT03_CLR_1CARD_ADDR, 1);

    /*Connect W BBP clock switch interrupt*/
    lIntLevel = mdrv_int_get_num(BSP_INT_TYPE_WBBP_SWITCH);  /*查询BSP_INT_TYPE_WBBP_SWITCH*/
    /*lint -e534*/
    mdrv_int_connect(lIntLevel, (VOIDFUNCPTR)HPA_3GSwitchClockIsr, 0 );
    /*lint +e534*/
    HPA_Write32Reg(WBBP_ARM_INT03_MASK_1CARD_ADDR, 0xFFFFFFFC);
    HPA_Write32Reg(WBBP_ARM_INT03_EN_ADDR, 1);
    /*lint -e534*/
    mdrv_int_enable(lIntLevel);    /*使能BSP_INT_TYPE_WBBP_SWITCH*/
    /*lint +e534*/

    g_ulWBBPSwtichIntNO = lIntLevel;

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : HPA_Cdma1XAwakeIsr
 功能描述  : 1X模式唤醒中断服务程序
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID HPA_Cdma1XAwakeIsr( VOS_VOID )
{
    SLEEP_BBE16AwakeIsr(VOS_RATMODE_1X);
}

/*****************************************************************************
 函 数 名  : HPA_CdmaHrpdAwakeIsr
 功能描述  : HRPD模式唤醒中断服务程序
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID HPA_CdmaHrpdAwakeIsr( VOS_VOID )
{
    SLEEP_BBE16AwakeIsr(VOS_RATMODE_HRPD);
}

/*****************************************************************************
 函 数 名  : HPA_CdmaAwakeIsr
 功能描述  : X模式唤醒中断服务程序
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID HPA_CdmaAwakeIsr( VOS_VOID )
{
    /* 先关中断 */
    (VOS_VOID)mdrv_int_disable(g_ulCBBPAwakeIntNO);

    /* 1x的唤醒中断，走1x唤醒 */
    if (0 != mdrv_bbp_get_wakeup_intr_src(PWC_COMM_MODE_CDMA_1X))
    {
        /* 清中断，清完中断后才返回 */
        (VOS_VOID)mdrv_bbp_clear_wakeup_intr(PWC_COMM_MODE_CDMA_1X);

        HPA_Cdma1XAwakeIsr();
    }

    /* hrpd的唤醒中断，走hrpd唤醒，共票方案只走1x唤醒 */
    if (0 != mdrv_bbp_get_wakeup_intr_src(PWC_COMM_MODE_CDMA_HRPD))
    {
        (VOS_VOID)mdrv_bbp_clear_wakeup_intr(PWC_COMM_MODE_CDMA_HRPD);

        HPA_Cdma1XAwakeIsr();
    }

    /* 最后开中断 */
    (VOS_VOID)mdrv_int_enable(g_ulCBBPAwakeIntNO);

    return;
}

/*****************************************************************************
 函 数 名  : HPA_Cdma1XHaltIsr
 功能描述  : 1X模式睡眠中断服务程序
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID HPA_Cdma1XHaltIsr( VOS_VOID )
{
    SLEEP_BBE16HaltIsr(VOS_RATMODE_1X);
}

/*****************************************************************************
 函 数 名  : HPA_CdmaHrpdHaltIsr
 功能描述  : HRPD模式睡眠中断服务程序
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID HPA_CdmaHrpdHaltIsr( VOS_VOID )
{
    SLEEP_BBE16HaltIsr(VOS_RATMODE_HRPD);
}

/*****************************************************************************
 函 数 名  : HPA_Cdma1XResumeIsr
 功能描述  : 1X模式恢复成功中断服务程序
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID HPA_Cdma1XResumeIsr( VOS_VOID )
{
    SLEEP_BBE16ResumeIsr(VOS_RATMODE_1X);
}

/*****************************************************************************
 函 数 名  : HPA_CdmaHrpdResumeIsr
 功能描述  : HRPD模式恢复成功中断服务程序
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID HPA_CdmaHrpdResumeIsr( VOS_VOID )
{
    SLEEP_BBE16ResumeIsr(VOS_RATMODE_HRPD);
}

/*****************************************************************************
 函 数 名  : HPA_ConnectCdmaISR
 功能描述  : 挂接CDMA相关中断
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月15日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID HPA_ConnectCdmaISR( VOS_VOID )
{
    /* 1X&HRPD 唤醒中断 底软封装后看不到寄存器 */
    (VOS_VOID)mdrv_bbp_clear_wakeup_intr(PWC_COMM_MODE_CDMA_1X);
    (VOS_VOID)mdrv_bbp_clear_wakeup_intr(PWC_COMM_MODE_CDMA_HRPD);

    (VOS_VOID)mdrv_bbp_disable_wakeup_intr(PWC_COMM_MODE_CDMA_1X);
    (VOS_VOID)mdrv_bbp_disable_wakeup_intr(PWC_COMM_MODE_CDMA_HRPD);

    g_ulCBBPAwakeIntNO = mdrv_int_get_num(BSP_INT_TYPE_CBBP_INTR01);
    (VOS_VOID)mdrv_int_connect(g_ulCBBPAwakeIntNO, (VOIDFUNCPTR)HPA_CdmaAwakeIsr, (VOS_INT)0);

    (VOS_VOID)mdrv_bbp_enable_wakeup_intr(PWC_COMM_MODE_CDMA_1X);
    (VOS_VOID)mdrv_bbp_enable_wakeup_intr(PWC_COMM_MODE_CDMA_HRPD);
    (VOS_VOID)mdrv_int_enable(g_ulCBBPAwakeIntNO);

    /* 1X&HRPD 睡眠中断 */
    (VOS_VOID)mdrv_ipc_int_disable(IPC_CCPU_INT_SRC_XDSP_1X_HALT);

    (VOS_VOID)mdrv_ipc_int_connect(IPC_CCPU_INT_SRC_XDSP_1X_HALT, (VOIDFUNCPTR)HPA_Cdma1XHaltIsr, 0);

    (VOS_VOID)mdrv_ipc_int_enable(IPC_CCPU_INT_SRC_XDSP_1X_HALT);     /*使能IPC_CCPU_INT_SRC_XDSP_1X_HALT*/

    (VOS_VOID)mdrv_ipc_int_disable(IPC_CCPU_INT_SRC_XDSP_HRPD_HALT);

    (VOS_VOID)mdrv_ipc_int_connect(IPC_CCPU_INT_SRC_XDSP_HRPD_HALT, (VOIDFUNCPTR)HPA_CdmaHrpdHaltIsr, 0);

    (VOS_VOID)mdrv_ipc_int_enable(IPC_CCPU_INT_SRC_XDSP_HRPD_HALT);   /*使能IPC_CCPU_INT_SRC_XDSP_HRPD_HALT*/

    /* 1X&HRPD 唤醒完成中断 */
    (VOS_VOID)mdrv_ipc_int_disable(IPC_CCPU_INT_SRC_XDSP_1X_RESUME);

    (VOS_VOID)mdrv_ipc_int_connect(IPC_CCPU_INT_SRC_XDSP_1X_RESUME, (VOIDFUNCPTR)HPA_Cdma1XResumeIsr, 0);

    (VOS_VOID)mdrv_ipc_int_enable(IPC_CCPU_INT_SRC_XDSP_1X_RESUME);   /*使能IPC_CCPU_INT_SRC_XDSP_1X_RESUME*/

    (VOS_VOID)mdrv_ipc_int_disable(IPC_CCPU_INT_SRC_XDSP_HRPD_RESUME);

    (VOS_VOID)mdrv_ipc_int_connect(IPC_CCPU_INT_SRC_XDSP_HRPD_RESUME, (VOIDFUNCPTR)HPA_CdmaHrpdResumeIsr, 0);

    (VOS_VOID)mdrv_ipc_int_enable(IPC_CCPU_INT_SRC_XDSP_HRPD_RESUME); /*使能IPC_CCPU_INT_SRC_XDSP_HRPD_RESUME*/

    return;
}
#endif

/*****************************************************************************
 Function   : HPA_ShowINTNo
 Description: Show Int NO
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_ShowINTNo(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("\r\nZSP  Dog Int NO is   %d", g_ulZSPWatchDogIntNO);
    vos_printf("\r\nHIFI Dog Int NO is   %d", g_ulHIFIWatchDogIntNO);
    vos_printf("\r\nGBBP 0   Int NO is   %d", g_aulGBBPIntNO[MODEM_ID_0]);
    vos_printf("\r\nGBBP 0Aw Int NO is   %d", g_aulGBBPAwakeIntNO[MODEM_ID_0]);
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    vos_printf("\r\nGBBP 1   Int NO is   %d", g_aulGBBPIntNO[MODEM_ID_1]);
    vos_printf("\r\nGBBP 1Aw Int NO is   %d", g_aulGBBPAwakeIntNO[MODEM_ID_1]);
#endif
    vos_printf("\r\nSIMI     Int NO is   %d", g_ulSIMIIntNO);
    vos_printf("\r\nWBBP 0ms Int NO is   %d", g_ulWBBP0MsIntNO);
    vos_printf("\r\nWBBP Aw  Int NO is   %d", g_ulWBBPAwakeIntNO);
    vos_printf("\r\nWBBP Sw  Int NO is   %d", g_ulWBBPSwtichIntNO);

    vos_printf("\r\n3G ISR num is        %d", g_ul3GISRNum);
    vos_printf("\r\n2G ISR num0 is       %d", g_ul2GISRNum0);
    vos_printf("\r\n2G ISR num1 is       %d", g_ul2GISRNum1);
    vos_printf("\r\n2G ISR num2 is       %d", g_ul2GISRNum2);

    /*lint +e534*/

    return;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


