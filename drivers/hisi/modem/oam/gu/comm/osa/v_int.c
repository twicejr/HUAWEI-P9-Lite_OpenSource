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
/* FileName: v_int.c                                                         */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement int function                                       */
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
/*                                                                           */
/*****************************************************************************/

#include "vos_config.h"
#include "v_typdef.h"
#include "v_int.h"
#include "v_IO.h"
#include "v_timer.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#if (VOS_VXWORKS == VOS_OS_VER)

#if (VOS_DEBUG == VOS_CHECK_INTLOCK)

/* VOS 支持的最大中断嵌套数目 */
#define VOS_NESTED_INTLOCK_MAX_NUM      (128)

/* VOS 统计的锁中断时间间隔 单位slice 30us */
#define VOS_INTLOCK_MAX_INTERVAL        (900)

/* 嵌套信息记录 */
typedef struct
{
    VOS_UINT32                          ulSuffix; /* 数组下标 */
    VOS_NESTED_LOCK_INFO_STRU           astNestedInfo[VOS_NESTED_INTLOCK_MAX_NUM];
}VOS_NESTED_INTLOCK_STRU;

VOS_NESTED_INTLOCK_STRU g_stVosIntLockNestedInfo = {0};

/*****************************************************************************
 Function   : V_IntLock
 Description: Turn off the interrupt
 Input      : file line
 Return     : CPSR;
 Other      : none
 *****************************************************************************/
VOS_INT V_IntLock(VOS_UINT32 ulFileID, VOS_INT32 lLineNo)
{
    VOS_INT lFlag;

    lFlag = intLock();

    if ( VOS_NESTED_INTLOCK_MAX_NUM <= g_stVosIntLockNestedInfo.ulSuffix )
    {
        g_stVosIntLockNestedInfo.ulSuffix++;

        /*lint -e534*/
        LogPrint2("# Info: intlock nested too big.F %d L %d.\r\n", (VOS_INT32)ulFileID, (VOS_INT32)lLineNo);
        /*lint +e534*/

        return lFlag;
    }

    g_stVosIntLockNestedInfo.astNestedInfo[g_stVosIntLockNestedInfo.ulSuffix].ulFile  = ulFileID;
    g_stVosIntLockNestedInfo.astNestedInfo[g_stVosIntLockNestedInfo.ulSuffix].lLine   = lLineNo;
    g_stVosIntLockNestedInfo.astNestedInfo[g_stVosIntLockNestedInfo.ulSuffix].ulSlice = VOS_GetSlice();

    g_stVosIntLockNestedInfo.ulSuffix++;

    return lFlag;

}

/*****************************************************************************
 Function   : V_IntUnlock
 Description: Turn on the interrupt
 Input      : CPSR
 Return     : void;
 Other      : none
 *****************************************************************************/
VOS_VOID V_IntUnlock(VOS_INT lLockKey)
{
    g_stVosIntLockNestedInfo.ulSuffix--;

    if ( VOS_NESTED_INTLOCK_MAX_NUM <= g_stVosIntLockNestedInfo.ulSuffix )
    {
        intUnlock(lLockKey);

        return;
    }

    if ( VOS_INTLOCK_MAX_INTERVAL <
        (VOS_GetSlice() - g_stVosIntLockNestedInfo.astNestedInfo[g_stVosIntLockNestedInfo.ulSuffix].ulSlice) )
    {
         /*lint -e534*/
         LogPrint2("# Info: intlock time too big.F %d L %d.\r\n",
            (VOS_INT32)g_stVosIntLockNestedInfo.astNestedInfo[g_stVosIntLockNestedInfo.ulSuffix].ulFile,
            (VOS_INT32)g_stVosIntLockNestedInfo.astNestedInfo[g_stVosIntLockNestedInfo.ulSuffix].lLine);
         /*lint +e534*/
    }

    intUnlock(lLockKey);

    return;
}


#endif

#endif

#if (VOS_RTOSCK == VOS_OS_VER)

#if (VOS_DEBUG == VOS_CHECK_INTLOCK)

/* VOS 支持的最大中断嵌套数目 */
#define VOS_NESTED_INTLOCK_MAX_NUM      (128)

/* VOS 统计的锁中断时间间隔 单位slice 30us */
#define VOS_INTLOCK_MAX_INTERVAL        (900)

/* 嵌套信息记录 */
typedef struct
{
    VOS_UINT32                          ulSuffix; /* 数组下标 */
    VOS_NESTED_LOCK_INFO_STRU           astNestedInfo[VOS_NESTED_INTLOCK_MAX_NUM];
}VOS_NESTED_INTLOCK_STRU;

VOS_NESTED_INTLOCK_STRU g_stVosIntLockNestedInfo = {0};

/*****************************************************************************
 Function   : V_IntLock
 Description: Turn off the interrupt
 Input      : file line
 Return     : CPSR;
 Other      : none
 *****************************************************************************/
VOS_INT V_IntLock(VOS_UINT32 ulFileID, VOS_INT32 lLineNo)
{
    VOS_INT lFlag;

    lFlag = (VOS_INT)SRE_IntLock();

    if ( VOS_NESTED_INTLOCK_MAX_NUM <= g_stVosIntLockNestedInfo.ulSuffix )
    {
        g_stVosIntLockNestedInfo.ulSuffix++;

        /*lint -e534*/
        LogPrint2("# Info: intlock nested too big.F %d L %d.\r\n", (VOS_INT32)ulFileID, (VOS_INT32)lLineNo);
        /*lint +e534*/

        return lFlag;
    }

    g_stVosIntLockNestedInfo.astNestedInfo[g_stVosIntLockNestedInfo.ulSuffix].ulFile  = ulFileID;
    g_stVosIntLockNestedInfo.astNestedInfo[g_stVosIntLockNestedInfo.ulSuffix].lLine   = lLineNo;
    g_stVosIntLockNestedInfo.astNestedInfo[g_stVosIntLockNestedInfo.ulSuffix].ulSlice = VOS_GetSlice();

    g_stVosIntLockNestedInfo.ulSuffix++;

    return lFlag;

}

/*****************************************************************************
 Function   : V_IntUnlock
 Description: Turn on the interrupt
 Input      : CPSR
 Return     : void;
 Other      : none
 *****************************************************************************/
VOS_VOID V_IntUnlock(VOS_INT lLockKey)
{
    g_stVosIntLockNestedInfo.ulSuffix--;

    if ( VOS_NESTED_INTLOCK_MAX_NUM <= g_stVosIntLockNestedInfo.ulSuffix )
    {
        SRE_IntRestore((VOS_UINT32)lLockKey);

        return;
    }

    if ( VOS_INTLOCK_MAX_INTERVAL <
        (VOS_GetSlice() - g_stVosIntLockNestedInfo.astNestedInfo[g_stVosIntLockNestedInfo.ulSuffix].ulSlice) )
    {
         /*lint -e534*/
         LogPrint2("# Info: intlock time too big.F %d L %d.\r\n",
            (VOS_INT32)g_stVosIntLockNestedInfo.astNestedInfo[g_stVosIntLockNestedInfo.ulSuffix].ulFile,
            (VOS_INT32)g_stVosIntLockNestedInfo.astNestedInfo[g_stVosIntLockNestedInfo.ulSuffix].lLine);
         /*lint +e534*/
    }

    SRE_IntRestore((VOS_UINT32)lLockKey);

    return;
}


#endif

#endif

#if (VOS_WIN32 == VOS_OS_VER)

CRITICAL_SECTION VOS_CriticalSection;

/*****************************************************************************
 Function   : VOS_SplInit()
 Description: Initialize the interrupt
 Input      : None
 Return     : Nnoe
 *****************************************************************************/
VOS_VOID VOS_SplInit()
{
    InitializeCriticalSection( &VOS_CriticalSection );
}

/*****************************************************************************
 Function   : VOS_SplIMP()
 Description: Turn off the interrupt
 Input      : None
 Return     : VOS_OK;
 Other      : none
 *****************************************************************************/
VOS_INT32 VOS_SplIMP()
{
    EnterCriticalSection( &VOS_CriticalSection );
    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_Splx()
 Description: Turn on the interrupt
 Input      : s -- value returned by VOS_SplIMP()
 Return     : None
 *****************************************************************************/
VOS_VOID VOS_Splx( VOS_INT32 s )
{
    LeaveCriticalSection ( &VOS_CriticalSection );
}

/*****************************************************************************
 Function   : atomic_inc_return()
 Description: add atomic Var then return
 Input      : atomic Var
 Return     : current value
 *****************************************************************************/
VOS_UINT32 atomic_inc_return(atomic_t *pstV)
{
    VOS_INT32   lFlags;
    VOS_UINT32  ulCounter;

    lFlags = VOS_SplIMP();

    (pstV->ulCounter)++;

    ulCounter = pstV->ulCounter;

    VOS_Splx(lFlags);

    return ulCounter;
}

#endif

#if (VOS_LINUX == VOS_OS_VER)
/*****************************************************************************
 Function   : VOS_SplIMP()
 Description: Turn off the interrupt
 Input      : None
 Return     : VOS_OK;
 Other      : none
 *****************************************************************************/
VOS_ULONG VOS_SplIMP(VOS_VOID)
{
    VOS_ULONG  flags;

    local_irq_save(flags);

    return flags;
}

/*****************************************************************************
 Function   : VOS_Splx()
 Description: Turn on the interrupt
 Input      : s -- value returned by VOS_SplIMP()
 Return     : None
 *****************************************************************************/
VOS_VOID VOS_Splx( VOS_ULONG s )
{
    local_irq_restore(s);
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


