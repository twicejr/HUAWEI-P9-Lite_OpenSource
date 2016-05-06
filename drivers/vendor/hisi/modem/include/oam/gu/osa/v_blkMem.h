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
/* FileName: v_blkmen.h                                                      */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement memory allotee                                     */
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

#ifndef _VOS_BLOCK_MEM_H
#define _VOS_BLOCK_MEM_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#include "v_typdef.h"

/* errno definiens */
#define VOS_ERRNO_MEMORY_ALLOC_CHECK                    0x20030084
#define VOS_ERRNO_MEMORY_NON_DOPRAMEM                   0x20030085
#define VOS_ERRNO_MEMORY_DOPRAMEM_OVERFLOW              0x20030086
#define VOS_ERRNO_MEMORY_HEAD_COVER                     0x20030087
#define VOS_ERRNO_MEMORY_TAIL_COVER                     0x20030088
#define VOS_ERRNO_MEMORY_GLOBAL_COVER                   0x20030089
#define VOS_ERRNO_MEMORY_LINK_COVER                     0x20030090

#define VOS_ERRNO_MSG_MEMORY_FULL                       0x2003FFFF
#define VOS_ERRNO_MEMORY_FULL                           0x2003FFFE
#define VOS_ERRNO_MEMORY_FREE_INPUTMSGISNULL            0x20030091
#define VOS_ERRNO_MEMORY_FREE_REPECTION                 0x20030092
#define VOS_ERRNO_MEMORY_ALLOC_INPUTMSGISNULL           0x20030093
#define VOS_ERRNO_MEMORY_FREE_INPUTPIDINVALID           0x20030035
#define VOS_ERRNO_MEMORY_LOCATION_INPUTINVALID          0x2003EEEE
#define VOS_ERRNO_MEMORY_LOCATION_TIMERSPACE            0x2003DDDD
#define VOS_ERRNO_MEMORY_LOCATION_CANNOTDO              0x2003CCCC

#define VOS_ARM_ALIGNMENT                               (0x03U)

typedef struct MEM_HEAD_BLOCK
{
    VOS_UINT_PTR      ulMemCtrlAddress;/* the address of  VOS_MEM_CTRL_BLOCK */
    VOS_UINT_PTR      ulMemAddress;/* the address of User's */
    VOS_UINT32        ulMemUsedFlag;/* whether be used or not */
    struct MEM_HEAD_BLOCK  *pstNext;/*  next block whether allocated or not */

#if VOS_YES == VOS_MEMORY_CHECK
    struct MEM_HEAD_BLOCK  *pstPre;/* the allocated block's previous */
    VOS_UINT32        ulAllocSize;/* the actual allocated size */
    VOS_UINT32        ulcputickAlloc;/* CPU tick of message allocation */
    VOS_UINT32        ulAllocPid;/* Pid who alloc the memory */
    VOS_UINT32        aulMemRecord[8];/* record something of user */
#endif

#if VOS_YES == VOS_MEMORY_COUNT
    VOS_UINT_PTR      ulRealCtrlAddr;/* which VOS_MEM_CTRL_BLOCK should be allocated */
#endif
} VOS_MEM_HEAD_BLOCK;

typedef struct
{
    VOS_INT             BlockLength;/* block size */
    VOS_INT             TotalBlockNumber;/* block number */
    VOS_UINT_PTR        Buffer;/*start address of block */
    VOS_UINT_PTR        BufferEnd;/*end address of block*/
    VOS_INT             IdleBlockNumber;/* the number of free block*/
    VOS_UINT8           aucRsv[4];
    VOS_MEM_HEAD_BLOCK  *Blocks;/*list of free block*/

#if VOS_YES == VOS_MEMORY_CHECK
    VOS_MEM_HEAD_BLOCK  *BusyBlocks;/*list of busy block*/
#endif

#if VOS_YES == VOS_MEMORY_COUNT
    VOS_INT             MinIdleBlockNumber;/*the MIN value of free block*/
    VOS_INT             MinSize;/* the Min allocated size */
    VOS_INT             MaxSize;/* the Max allocated size */
    VOS_INT             lRealNumber;
    VOS_INT             lMaxRealNumber;
#endif
    VOS_UINT8           aucRsv1[4];
} VOS_MEM_CTRL_BLOCK;

typedef struct
{
#if VOS_YES == VOS_MEMORY_COUNT
    VOS_INT             MinSize;/* the Min allocated size */
    VOS_INT             MaxSize;/* the Max allocated size */
    VOS_INT             lMaxRealNumber;
    VOS_UINT8           aucRsv[4];
#endif
} VOS_MEM_RECORD_ST;

typedef struct
{
    VOS_UINT32          ulTotalNumber;/* the total number of occupying Msg\Mem*/
    VOS_UINT32          ulSize;/* the total size of occupying Msg\Mem*/
}VOS_MEM_OCCUPYING_INFO_ST;

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
/* the type of info which come from task */
enum VOS_EXC_DUMP_MEM_NUM_ENUM
{
    VOS_EXC_DUMP_MEM_NUM_1,
    VOS_EXC_DUMP_MEM_NUM_2,
    VOS_EXC_DUMP_MEM_NUM_3,
    VOS_EXC_DUMP_MEM_NUM_4,
    VOS_EXC_DUMP_MEM_NUM_BUTT
};
#else
enum VOS_EXC_DUMP_MEM_NUM_ENUM
{
    VOS_EXC_DUMP_MEM_NUM_1,
    VOS_EXC_DUMP_MEM_NUM_2,
    VOS_EXC_DUMP_MEM_NUM_3,
    VOS_EXC_DUMP_MEM_NUM_4,
    VOS_EXC_DUMP_MEM_NUM_BUTT
};
#endif

typedef VOS_UINT32      VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32;

VOS_UINT32 VOS_MemInit( VOS_VOID );

VOS_VOID * VOS_MemBlkMalloc( VOS_PID PID, VOS_INT ulLength,
                            VOS_UINT32 ulFileID, VOS_INT32 usLineNo );

VOS_VOID* VOS_TIMER_MemCtrlBlkMalloc( VOS_PID PID, VOS_INT ulLength );

/*lint -function(malloc(1),V_MemAlloc(3))*/
VOS_VOID * V_MemAlloc( VOS_UINT32 ulInfo, VOS_UINT8  ucPtNo, VOS_UINT32 ulSize,
                        VOS_UINT32 ulRebootFlag, VOS_UINT32 ulFileID, VOS_INT32 usLineNo  );

#define VOS_MemAlloc( ulInfo, ucPtNo, ulSize )\
    V_MemAlloc( (ulInfo), (ucPtNo), (ulSize), VOS_TRUE, VOS_FILE_ID, __LINE__)

#define VOS_AssistantMemAlloc( ulInfo, ucPtNo, ulSize )\
    V_MemAlloc( (ulInfo), (ucPtNo), (ulSize), VOS_FALSE, VOS_FILE_ID, __LINE__)

VOS_VOID *VOS_MemReAlloc ( VOS_UINT32 ulPid, VOS_UINT8 ucPtNo,
                           VOS_VOID *pOldMemPtr, VOS_UINT32 ulNewSize );

VOS_UINT32 V_MemFree( VOS_UINT32 ulInfo, VOS_VOID **ppAddr,
                          VOS_UINT32 ulFileID, VOS_INT32 usLineNo );

#define VOS_MemFree( ulInfo, pAddr )\
    V_MemFree( (ulInfo), (VOS_VOID**)(&(pAddr)), VOS_FILE_ID, __LINE__ )

VOS_UINT32 VOS_MemCheck( VOS_VOID *pAddr, VOS_UINT_PTR *pulBlock,
                         VOS_UINT_PTR *pulCtrl, VOS_UINT32 ulFileID,
                         VOS_INT32 usLineNo );

VOS_UINT32 VOS_MemCtrlBlkFree( VOS_MEM_CTRL_BLOCK *VOS_MemCtrlBlock,
                               VOS_MEM_HEAD_BLOCK *Block,
                               VOS_UINT32 ulFileID, VOS_INT32 usLineNo );

VOS_UINT32 VOS_LocationMem( VOS_VOID *pAddr, VOS_UINT32 *pulRealSize,
                            VOS_UINT32 ulFileID, VOS_INT32 usLineNo );

VOS_VOID VOS_RecordmemInfo( VOS_MEM_RECORD_ST *pstPara );

VOS_UINT32 VOS_GetFreeMemoryInfo(VOS_UINT32 ulSize, VOS_UINT32 *pulFreeBlockNum,
                                 VOS_UINT32 *pulTotalBlockNum);

VOS_UINT32 VOS_GetMemOccupyingInfo(VOS_MEM_OCCUPYING_INFO_ST *pstInfo,
                                   VOS_UINT32 ulLen);

VOS_UINT32 VOS_GetMsgOccupyingInfo(VOS_MEM_OCCUPYING_INFO_ST *pstInfo,
                                   VOS_UINT32 ulLen);

VOS_VOID * VOS_StaticMemAlloc( VOS_CHAR *pcBuf, VOS_UINT32 ulBufSize,
                                    VOS_UINT32 ulAllocSize, VOS_UINT32 *pulSuffix);

VOS_BOOL VOS_CalcMsgInfo(VOS_VOID);

VOS_BOOL VOS_CalcMemInfo(VOS_VOID);

VOS_BOOL VOS_CalcAppMemInfo(VOS_VOID);

#if VOS_YES == VOS_MEMORY_CHECK

VOS_VOID VOS_AutoCheckMemory( VOS_VOID );

extern VOS_UINT32 g_ulAutoCheckMemoryThreshold;

#endif

#if (VOS_DEBUG == VOS_DOPRA_VER)

typedef VOS_VOID  (*MEMORY_HOOK_FUNC)( VOS_UINT32 ulPara );

#define VOS_ALLOC_MODE    0
#define VOS_FREE_MODE     1

VOS_UINT32 VOS_RegisterMemAllocHook( VOS_UINT32 ulMode, MEMORY_HOOK_FUNC pfnHook);

#endif

VOS_VOID VOS_ModifyMemBlkInfo(VOS_UINT_PTR ulAddr, VOS_PID PID);

VOS_VOID *VOS_ExcDumpMemAlloc(VOS_UINT32 ulNumber);

VOS_VOID *VOS_CacheMemAlloc(VOS_UINT32 ulSize);

VOS_UINT32 VOS_CacheMemFree(VOS_VOID *pAddr);

VOS_VOID *VOS_UnCacheMemAlloc(VOS_UINT32 ulSize, VOS_UINT_PTR *pulRealAddr);

VOS_VOID VOS_UnCacheMemFree(VOS_VOID *pVirtAddr, VOS_VOID *pPhyAddr, VOS_UINT32 ulSize);

VOS_UINT_PTR VOS_UncacheMemPhyToVirt(VOS_UINT8 *pucCurPhyAddr, VOS_UINT8 *pucPhyStart, VOS_UINT8 *pucVirtStart, VOS_UINT32 ulBufLen);

VOS_UINT_PTR VOS_UncacheMemVirtToPhy(VOS_UINT8 *pucCurVirtAddr, VOS_UINT8 *pucPhyStart, VOS_UINT8 *pucVirtStart, VOS_UINT32 ulBufLen);

VOS_VOID VOS_FlushCpuWriteBuf(VOS_VOID);

VOS_VOID VOS_FlushCpuCache( VOS_VOID *pAddress, VOS_UINT ulSize );

#if defined(COMM_ACPU_PC_LINT_HAPPY) || (VOS_WIN32 == VOS_OS_VER)

enum
{
    GFP_KERNEL,
    GFP_DMA
};

VOS_VOID *kmalloc(VOS_UINT32 ulSize, VOS_UINT32 ulFlag);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _VOS_BLOCK_MEM_H */

