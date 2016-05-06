/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: vos_main.c                                                      */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement root function                                      */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/

#include "vos.h"
#include "mdrv.h"
#include <product_config.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 modify:x51137; review:h59254; cause:print log */
#define    THIS_FILE_ID        PS_FILE_ID_VOS_MAIN_C
/*lint +e767 modify:x51137; review:h59254; */

extern VOS_UINT32 SCM_ChannelInit(VOS_VOID);
extern VOS_UINT32 SCM_ChannelMemInit(VOS_VOID);
extern VOS_UINT32 VOS_ICC_Init(VOS_VOID);
extern VOS_UINT32 APM_InitSystemAddr(VOS_VOID);

#if (FEATURE_ON == FEATURE_HIFI_USE_ICC)
extern VOS_UINT32 VOS_Hifi_ICC_Init(VOS_VOID);
#endif


VOS_UINT32 g_ulVosOutsideStep = 0;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
extern signed int VOS_MsgLpmCb(int x);

/*****************************************************************************
 Function   : VOS_OutSideInit
 Description: finish the outside device init,eg. ICC
 Calls      :
 Called By  : VOS_Startup
 Input      : None
 Return     : VOS_OK or VOS_ERROR
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_OutsideInit(VOS_VOID)
{
    VOS_UINT32                          ulResult = 0;

    g_ulVosOutsideStep = 0x00200000;

    mdrv_icc_register_resume_cb(UDI_ICC_GUOM4, VOS_MsgLpmCb, 0);

    /*DRV MB Init*/
    if(VOS_OK != VOS_DRVMB_Init())
    {
        ulResult |= 0x00200000;
    }

    g_ulVosOutsideStep = 0x00100000;

    if (VOS_OK != SCM_ChannelMemInit())/* 通道内存初始化 */
    {
        ulResult |= 0x00100000;
    }

    g_ulVosOutsideStep = 0x00400000;

    /*SCM  Init*/
    if(VOS_OK != SCM_ChannelInit())
    {
        ulResult |= 0x00800000;
    }

    g_ulVosOutsideStep = 0x1000;

    /*OSA ICC Channel Init*/
    if(VOS_OK != VOS_ICC_Init())
    {
        ulResult |= 0x1000;
    }

    g_ulVosOutsideStep = 0x2000;

    return ulResult;
}
#endif  /*(OSA_CPU_ACPU == VOS_OSA_CPU)*/

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
/*****************************************************************************
 Function   : VOS_OutSideInit
 Description: finish the outside device init,eg. ICC
 Calls      :
 Called By  : VOS_Startup
 Input      : None
 Return     : VOS_OK or VOS_ERROR
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_OutsideInit(VOS_VOID)
{
    VOS_UINT32                          ulResult = 0;

    g_ulVosOutsideStep = 0x1000;

    /*ICC channel Init*/
    if(VOS_OK != VOS_ICC_Init())
    {
        ulResult |= 0x1000;
    }

    g_ulVosOutsideStep = 0x2000;
    
#if (FEATURE_ON == FEATURE_HIFI_USE_ICC)
    g_ulVosOutsideStep = 0x4000;

    /*ICC channel Init*/
    if(VOS_OK != VOS_Hifi_ICC_Init())
    {
        ulResult |= 0x4000;
    }
#endif

    g_ulVosOutsideStep = 0x00200000;

    /*DRV MB Init*/
    if(VOS_OK != VOS_DRVMB_Init())
    {
        ulResult |= 0x00200000;
    }

    g_ulVosOutsideStep = 0x00100000;

    if (VOS_OK != SCM_ChannelMemInit())/* 通道内存初始化 */
    {
        ulResult |= 0x00100000;
    }

    g_ulVosOutsideStep = 0x00400000;

    /*SCM  Init*/
    if(VOS_OK != SCM_ChannelInit())
    {
        ulResult |= 0x00800000;
    }

    g_ulVosOutsideStep = 0x01000000;

    if (VOS_OK != APM_InitSystemAddr()) /*放在这里初始化HPA相关的基地址，HPA任务后面会删除*/
    {
        ulResult |= 0x01000000;
    }

    return ulResult;
}
#endif  /*(OSA_CPU_CCPU == VOS_OSA_CPU)*/

VOS_VOID OM_OutsideShow(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("OM_OutsideShow:g_ulVosOutsideStep = %d\n", g_ulVosOutsideStep);
    /*lint +e534*/

    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

