/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: HPAInit.c                                                       */
/*                                                                           */
/* Author: Xu cheng                                                          */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-02                                                             */
/*                                                                           */
/* Description: HPA Init                                                     */
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
#include "DspInterface.h"
#include "mdrv.h"
#include "TtfOamInterface.h"
#include "NVIM_Interface.h"
#include "apminterface.h"
#include "sleepsleep.h"
#include "omnosig.h"
#include "PamOamSpecTaskDef.h"
#include "bbp_gsm_interface.h"
#include "bbp_gsm_on_interface.h"
#include "bbp_cdma_on_interface.h"
#include "apmprocess.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/* Macro of log */
/*lint -e(767) 修改人：m00128685；检视人: l46160；原因简述:打点日志文件宏ID定义*/
#define    THIS_FILE_ID        PS_FILE_ID_HPA_INIT_C
/*lint +e767 修改人：m00128685；检视人：l46160；*/

/*****************************************************************************
 Function   : HPA_Init
 Description: HPA Init
 Input      : void
 Return     : OK or Error
 Other      :
 *****************************************************************************/
VOS_UINT32 HPA_Init(VOS_VOID)
{
    /* set SFN & CFN */
    g_ucHpaCfnRead = 0;
    g_usHpaSfnRead = 0;

    /*Hpa Error Count global Var. Init*/
    /*lint -e534*/
    VOS_MemSet((VOS_VOID *)(g_astHpaErrorCount), (VOS_CHAR)0x00,
        sizeof(g_astHpaErrorCount));

    /*Hpa Interrupt Count global Var. Init*/
    VOS_MemSet((VOS_VOID *)(&g_stHpaIntCount), (VOS_CHAR)0x00,
        sizeof(HPA_INT_COUNT_STRU));

    VOS_MemSet((VOS_VOID *)(g_aulGUCBBPRegAddr), (VOS_CHAR)0x00,
        sizeof(g_aulGUCBBPRegAddr));
    /*lint +e534*/

    g_aulGUCBBPRegAddr[INT_STA][MODEM_ID_0][VOS_RATMODE_GSM]        = GBBP_CPU_INT_STA_ADDR;
    g_aulGUCBBPRegAddr[INT_MASK][MODEM_ID_0][VOS_RATMODE_GSM]       = GBBP_CPU_INT_MASK_ADDR;
    g_aulGUCBBPRegAddr[INT_CLR][MODEM_ID_0][VOS_RATMODE_GSM]        = GBBP_CPU_INT_CLR_ADDR;
    g_aulGUCBBPRegAddr[BLER_ERR][MODEM_ID_0][VOS_RATMODE_GSM]       = GBBP_BLER_ERRR_RPT_ADDR;
    g_aulGUCBBPRegAddr[BLER_TOTAL][MODEM_ID_0][VOS_RATMODE_GSM]     = GBBP_BLER_TOTAL_RPT_ADDR;
    g_aulGUCBBPRegAddr[GTC_FN][MODEM_ID_0][VOS_RATMODE_GSM]         = GBBP_GTC_FN_RPT_ADDR;

    g_aulGUCBBPRegAddr[DRX_INT_STA][MODEM_ID_0][VOS_RATMODE_GSM]    = GBBP_DRX_CPU_INT_STA_ADDR;
    g_aulGUCBBPRegAddr[DRX_INT_MASK][MODEM_ID_0][VOS_RATMODE_GSM]   = GBBP_DRX_CPU_INT_MASK_ADDR;
    g_aulGUCBBPRegAddr[DRX_INT_CLR][MODEM_ID_0][VOS_RATMODE_GSM]    = GBBP_DRX_CPU_INT_CLR_ADDR;


    g_aulGUCBBPRegAddr[DRX_INT_STA][MODEM_ID_0][VOS_RATMODE_1X]     = CBBP_WAKEUP_INT_STA_ARM_ADDR;
    g_aulGUCBBPRegAddr[DRX_INT_MASK][MODEM_ID_0][VOS_RATMODE_1X]    = CBBP_WAKEUP_INT_ARM_ADDR;
    g_aulGUCBBPRegAddr[DRX_INT_CLR][MODEM_ID_0][VOS_RATMODE_1X]     = CBBP_WAKEUP_INT_ARM_ADDR;

    g_aulGUCBBPRegAddr[DRX_INT_STA][MODEM_ID_0][VOS_RATMODE_HRPD]   = CBBP_WAKEUP_INT_STA_ARM_ADDR;
    g_aulGUCBBPRegAddr[DRX_INT_MASK][MODEM_ID_0][VOS_RATMODE_HRPD]  = CBBP_WAKEUP_INT_ARM_ADDR;
    g_aulGUCBBPRegAddr[DRX_INT_CLR][MODEM_ID_0][VOS_RATMODE_HRPD]   = CBBP_WAKEUP_INT_ARM_ADDR;

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    g_aulGUCBBPRegAddr[INT_STA][MODEM_ID_1][VOS_RATMODE_GSM]    = (GBBP_CPU_INT_STA_ADDR - SOC_BBP_GSM0_BASE_ADDR)
                                            + SOC_BBP_GSM1_BASE_ADDR;
    g_aulGUCBBPRegAddr[INT_MASK][MODEM_ID_1][VOS_RATMODE_GSM]   = (GBBP_CPU_INT_MASK_ADDR - SOC_BBP_GSM0_BASE_ADDR)
                                            + SOC_BBP_GSM1_BASE_ADDR;
    g_aulGUCBBPRegAddr[INT_CLR][MODEM_ID_1][VOS_RATMODE_GSM]    = (GBBP_CPU_INT_CLR_ADDR - SOC_BBP_GSM0_BASE_ADDR)
                                            + SOC_BBP_GSM1_BASE_ADDR;
    g_aulGUCBBPRegAddr[BLER_ERR][MODEM_ID_1][VOS_RATMODE_GSM]   = (GBBP_BLER_ERRR_RPT_ADDR - SOC_BBP_GSM0_BASE_ADDR)
                                            + SOC_BBP_GSM1_BASE_ADDR;
    g_aulGUCBBPRegAddr[BLER_TOTAL][MODEM_ID_1][VOS_RATMODE_GSM] = (GBBP_BLER_TOTAL_RPT_ADDR - SOC_BBP_GSM0_BASE_ADDR)
                                            + SOC_BBP_GSM1_BASE_ADDR;
    g_aulGUCBBPRegAddr[GTC_FN][MODEM_ID_1][VOS_RATMODE_GSM]     = (GBBP_GTC_FN_RPT_ADDR - SOC_BBP_GSM0_BASE_ADDR)
                                            + SOC_BBP_GSM1_BASE_ADDR;

/*lint -e778*/
/*  Constant expression evaluates to 0 in operation*/
    g_aulGUCBBPRegAddr[DRX_INT_STA][MODEM_ID_1][VOS_RATMODE_GSM]    = (GBBP_DRX_CPU_INT_STA_ADDR - SOC_BBP_GSM0_ON_BASE_ADDR)
                                            + SOC_BBP_GSM1_ON_BASE_ADDR;
/*lint +e778*/

    g_aulGUCBBPRegAddr[DRX_INT_MASK][MODEM_ID_1][VOS_RATMODE_GSM]   = (GBBP_DRX_CPU_INT_MASK_ADDR - SOC_BBP_GSM0_ON_BASE_ADDR)
                                            + SOC_BBP_GSM1_ON_BASE_ADDR;
    g_aulGUCBBPRegAddr[DRX_INT_CLR][MODEM_ID_1][VOS_RATMODE_GSM]    = (GBBP_DRX_CPU_INT_CLR_ADDR - SOC_BBP_GSM0_ON_BASE_ADDR)
                                            + SOC_BBP_GSM1_ON_BASE_ADDR;


#if ( 3 == MULTI_MODEM_NUMBER )
    /* Modem2地址初始化，Austin上和Modem0使用相同基地址 */
    g_aulGUCBBPRegAddr[INT_STA][MODEM_ID_2][VOS_RATMODE_GSM]    = GBBP_CPU_INT_STA_ADDR;
    g_aulGUCBBPRegAddr[INT_MASK][MODEM_ID_2][VOS_RATMODE_GSM]   = GBBP_CPU_INT_MASK_ADDR;
    g_aulGUCBBPRegAddr[INT_CLR][MODEM_ID_2][VOS_RATMODE_GSM]    = GBBP_CPU_INT_CLR_ADDR;
    g_aulGUCBBPRegAddr[BLER_ERR][MODEM_ID_2][VOS_RATMODE_GSM]   = GBBP_BLER_ERRR_RPT_ADDR;
    g_aulGUCBBPRegAddr[BLER_TOTAL][MODEM_ID_2][VOS_RATMODE_GSM] = GBBP_BLER_TOTAL_RPT_ADDR;
    g_aulGUCBBPRegAddr[GTC_FN][MODEM_ID_2][VOS_RATMODE_GSM]     = GBBP_GTC_FN_RPT_ADDR;

/*lint -e778*/
/*  Constant expression evaluates to 0 in operation*/
    g_aulGUCBBPRegAddr[DRX_INT_STA][MODEM_ID_2][VOS_RATMODE_GSM]  = GBBP_DRX_CPU_INT_STA_ADDR;
/*lint +e778*/

    g_aulGUCBBPRegAddr[DRX_INT_MASK][MODEM_ID_2][VOS_RATMODE_GSM] = GBBP_DRX_CPU_INT_MASK_ADDR;
    g_aulGUCBBPRegAddr[DRX_INT_CLR][MODEM_ID_2][VOS_RATMODE_GSM]  = GBBP_DRX_CPU_INT_CLR_ADDR;

#endif
#endif

    if ( VOS_OK != VOS_SmCCreate( "TRAN", 0, VOS_SEMA4_FIFO, &g_ulHpaTransferSem))
    {
        PS_LOG(UEPS_PID_WHPA, 0, PS_PRINT_WARNING,
            "HPA: creat g_ulHpaTransferSem Err");

        return VOS_ERR;
    }

#ifdef HPA_ITT
    g_pfnHpaDspIsrStub = VOS_NULL_PTR;

    g_pfnHpaIttMsgFilterFunc = VOS_NULL_PTR;
#endif

    if(NV_OK != NV_Read(en_NV_Item_Max_Gsm_Reg_Cnt,&g_stGhpaRegCnt,sizeof(g_stGhpaRegCnt)))
    {
        PS_LOG(UEPS_PID_SHPA, 0, PS_PRINT_WARNING,
            "HPA: Read en_NV_Item_Max_Gsm_Reg_Cnt Err");
    }

    return VOS_OK;
}

/*****************************************************************************
 Function   : atomic_dec
 Description: decrease atomic counter.comes from linux
 Input      : atomic counter
 Return     : void
 Other      :
 *****************************************************************************/
void atomic_dec( hpa_atomic_t *v )
{
    int flags;

    flags = VOS_SplIMP();

    (v->counter)--;

    VOS_Splx(flags);

    return;
}

/*****************************************************************************
 函 数 名  : HPA_TransferTaskEntry
 功能描述  : HPA dispatch task Entry
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   : 新生成函数
  2.日    期   : 2012年5月12日
    作    者   : s00207770
    修改内容   : DSP上移适配，HPA模块

*****************************************************************************/
VOS_VOID HPA_TransferTaskEntry(VOS_VOID)
{
    for ( ; ; )
    {
        if (VOS_OK != VOS_SmP(g_ulHpaTransferSem, 0))
        {
            /*lint -e534*/
            LogPrint("HPA_TransferTaskEntry: VOS_SmP Fail.\r\n");
            /*lint +e534*/
#if (VOS_WIN32 != VOS_OS_VER)
            continue;
#else
            break;
#endif
        }

        if ( MAIL_BOX_PROTECTWORD_SND == g_ulOmNosigEnable )
        {
            if (MAIL_BOX_PROTECTWORD_SND == g_ulListmodeEnable)
            {
                CBT_FramesStatistics();
            }
            else if (VOS_RATMODE_WCDMA == g_usListModeCurrentMode)
            {
                OM_LoopTestProc();
            }
            else if (VOS_RATMODE_1X == g_usListModeCurrentMode)
            {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA) 

                CBT_CLoopTestProc();
#endif
            }
            else
            {
                /* for pclint */
            }
        }

#if (VOS_WIN32 == VOS_OS_VER)
        break;
#endif
    }

}

/*****************************************************************************
 Function   : HPA_FIDInit
 Description: HPA FID Init
 Input      : Ip
 Return     : void
 Other      :
 *****************************************************************************/
VOS_UINT32 HPA_FIDInit( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch ( ip )
    {
        case VOS_IP_LOAD_CONFIG:
            if ( VOS_OK != VOS_RegisterPIDInfo(UEPS_PID_SHPA,
                APM_PIDInit, (Msg_Fun_Type)HPA_ApmMsgPIDProc))
            {
                PS_LOG(  UEPS_PID_SHPA, 0, PS_PRINT_ERROR,
                    "HPA_FIDInit:VOS_RegisterPIDInfo UEPS_PID_SHPA failure !\n");

                return VOS_ERR;
            }

            if ( VOS_OK
                != VOS_RegisterTaskPrio(WUEPS_FID_HPA, COMM_HPA_TASK_PRIO) )
            {
                PS_LOG(  UEPS_PID_SHPA, 0, PS_PRINT_ERROR,
                    "HPA_FIDInit:VOS_RegisterMsgTaskPrio failure !\n");

                return VOS_ERR;
            }

            if ( VOS_NULL_BYTE == VOS_RegisterSelfTaskPrio(WUEPS_FID_HPA,
                (VOS_TASK_ENTRY_TYPE)HPA_TransferTaskEntry,
                COMM_HPA_SELFTASK_PRIO, HPA_TRANSFER_TASK_STACK_SIZE ) )
            {
                PS_LOG(  UEPS_PID_SHPA, 0, PS_PRINT_ERROR,
                    "HPA_FIDInit:VOS_RegisterSelfTask:HPA_TransferTaskEntry failure !\n");

                return VOS_ERR;
            }

            break;

        case VOS_IP_FARMALLOC:
            if(VOS_OK != HPA_Init())
            {
                PS_LOG(  UEPS_PID_SHPA, 0, PS_PRINT_ERROR,
                    "HPA_FIDInit:HPA Init failure !\n");
                return VOS_ERR;
            }
            break;

        default:
            break;
    }

    return VOS_OK;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


