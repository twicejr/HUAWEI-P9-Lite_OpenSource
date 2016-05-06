/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: HPAGlobalVar.c                                                  */
/*                                                                           */
/* Author: Xu cheng                                                          */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-02                                                             */
/*                                                                           */
/* Description: Definition of HPA Global Var.                                */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 2008-02                                                          */
/*    Author: Xu cheng                                                       */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "hpacomm.h"
#include "hpaglobalvar.h"
#include "hparingbuffer.h"
#include "sleepflow.h"
#include "bbp_gsm_interface.h"
#include "apminterface.h"

/* Macro of log */
/*lint -e767  修改人: m00128685；检视人：l46160 原因简述:打点日志文件宏ID定义*/
#define    THIS_FILE_ID        PS_FILE_ID_HPA_GLOBAL_VAR_C
/*lint +e767   修改人: m00128685；检视人：l46160 */



/* the number of DSP's interrupt */
hpa_atomic_t                        g_stDspMailBoxCount;

/* the semaphore which be used to wake up transfer task */
VOS_SEM                         g_ulHpaTransferSem;

/* Record CFN */
VOS_UCHAR                       g_ucHpaCfnRead;

/* Record SFN */
VOS_UINT16                      g_usHpaSfnRead;

/* record hpa's error */
HPA_ERROR_COUNT_STRU            g_astHpaErrorCount[HPA_MB_BUTT/2];

/* record hpa's interrupt */
HPA_INT_COUNT_STRU              g_stHpaIntCount;

#ifdef HPA_ITT
/* hook function of 0ms ISR */
HPA_DSP_INT_ISR_FUNC_HOOK       g_pfnHpaDspIsrStub;

/* hook function of ITT */
HPA_ITT_MSG_FILTER_FUNC_HOOK    g_pfnHpaIttMsgFilterFunc;
#endif


OM_MAX_REG_CNT_GSM_STRU         g_stGhpaRegCnt = {500};

VOS_UINT32                      g_aulGUCBBPRegAddr[BBP_ADDR_BUTT][MODEM_ID_BUTT][VOS_RATMODE_BUTT];

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


