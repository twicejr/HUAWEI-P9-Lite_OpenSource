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
/* FileName: v_root.h                                                        */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: used bu vos_main.c                                           */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/* 2. Date: 2006-10                                                          */
/*    Author: Xu Cheng                                                       */
/*    Modification: Standardize code                                         */
/*                                                                           */
/*****************************************************************************/

#ifndef _V_ROOT_H
#define _V_ROOT_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif /* __cplusplus */
#endif /* __cplusplus */

enum VOS_STARTUP_PHASE
{
    VOS_STARTUP_INIT_DOPRA_SOFEWARE_RESOURCE   = 0,           /* DOPRA resource initialization                               */
    VOS_STARTUP_SET_TIME_INTERRUPT             = 1,           /* Set time interrupt and calculate the base value of cpu load */
    VOS_STARTUP_CREATE_TICK_TASK               = 2,           /* Create TICK task                                            */
    VOS_STARTUP_CREATE_ROOT_TASK               = 3,           /* Create ROOT task                                            */
    VOS_STARTUP_SUSPEND_MAIN_TASK              = 4            /* System startup complete. Suspend the main task              */
};

enum VOS_STARTUP_MODEL                                        /* System startup model            */
{
    VOS_STARTUP_NORMAL_MODEL                   = 0,           /* Normal model, restart if failed */
    VOS_STARTUP_DEBUG_MODEL                    = 1            /* Debug model, suspend if failed  */
};


VOS_UINT32 VOS_Startup( enum VOS_STARTUP_PHASE ph );

VOS_BOOL   VOS_IsSystemStartUp(VOS_VOID);

VOS_UINT32 VOS_GetStartUpOrder(VOS_VOID);

VOS_VOID   VOS_SetStartUpModel( VOS_UINT32 ulStartUpModel );

VOS_UINT32 VOS_GetStartUpModel(VOS_VOID);

VOS_VOID   VOS_NotifyDOPRAGoNext(VOS_VOID);

VOS_UINT32 VOS_RegModuleInfo( VOS_UINT32 ulModID, VOS_VOID* pFuncLib );

VOS_UINT32 VOS_GetModuleInfo( VOS_UINT32 ulModID, VOS_VOID* *pFuncLib );

VOS_UINT32 VOS_InitTrace( VOS_UINT32 ulLevel, VOS_CHAR * format, ... );

VOS_UINT32 VOS_SetInitTraceLevel( VOS_UINT32 ulLevel );

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif


