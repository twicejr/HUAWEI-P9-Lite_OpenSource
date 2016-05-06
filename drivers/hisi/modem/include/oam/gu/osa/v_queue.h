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
/* FileName: v_queue.h                                                       */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement queue                                              */
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

#ifndef _VOS_QUEUE_H
#define _VOS_QUEUE_H

#include "v_typdef.h"
#include "v_msg.h"
#include "v_sem.h"
#include "vos_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/* errno definiens */
#define VOS_ERRNO_QUEUE_CREATE_LENISZERO                    0x20050005
#define VOS_ERRNO_QUEUE_CREATE_SIZEISZERO                   0x20050006
#define VOS_ERRNO_QUEUE_CREATE_OPTINVALID                   0x20050007
#define VOS_ERRNO_QUEUE_CREATE_NAMEISNULL                   0x20050008
#define VOS_ERRNO_QUEUE_CREATE_OUTPUTISNULL                 0x20050009
#define VOS_ERRNO_QUEUE_CREATE_NOFREECB                     0x2005000A
#define VOS_ERRNO_QUEUE_CREATE_OSALFAIL                     0x2005000B
#define VOS_ERRNO_QUEUE_WRITE_QUEIDINVALID                  0x20050028
#define VOS_ERRNO_QUEUE_WRITE_BUFADDRISNULL                 0x20050029
#define VOS_ERRNO_QUEUE_WRITE_BUFSIZEINVALID                0x2005002A
#define VOS_ERRNO_QUEUE_FULL                                0x2005FFFF


#define VOS_DEFAULT_QUEUE_SIZE                              50

typedef enum tagVosQueueMode_E
{
    VOS_MSG_Q_FIFO,
    VOS_MSG_Q_PRIORITY,
    VOS_QUEUE_MODE_BUTT
} VOS_QUEUE_MODE;

/* the Max queue number supported by VOS */
#if (VOS_WIN32 == VOS_OS_VER)
#define VOS_MAX_QUEUE_NUMBER                               170
#else
#define VOS_MAX_QUEUE_NUMBER                               145
#endif

VOS_VOID VOS_QueueCtrlBlkInit(VOS_VOID);

VOS_UINT32 VOS_FixedQueueCreate( VOS_UINT32 ulLength,
                            VOS_UINT32 *pulQueueID,
                            VOS_UINT32 ulQueueOption,
                            VOS_UINT32 ulMaxMsgSize,
                            VOS_UINT32 ulQueueNum );

VOS_UINT32 VOS_FixedQueueWrite( VOS_UINT32 ulQueueID, VOS_VOID * pBufferAddr,
                           VOS_UINT32 ulBufferSize, VOS_UINT32 Pri,
                           VOS_UINT32 ulPid );

VOS_UINT32 VOS_FixedQueueWriteDirect( VOS_UINT32 ulQueueID, VOS_VOID * pBufferAddr, VOS_UINT32 Pri);

VOS_UINT32 VOS_FixedQueueRead( VOS_UINT32 ulQueueID, VOS_UINT32 ulTimeOut,
                          VOS_UINT_PTR *pBufferAddr, VOS_UINT32 ulBufferSize );

VOS_VOID* VOS_FixedQueueReadMsg( VOS_UINT32 ulFidID );

VOS_SEM VOS_GetSemIDFromQueue(VOS_UINT32 ulQueue);

VOS_VOID* VOS_GetMsg( VOS_UINT32 ulTaskID );

VOS_VOID* VOS_OutMsg( VOS_UINT32 ulQueueID );

VOS_UINT32 VOS_GetQueueSizeFromFid(VOS_UINT32 ulFid);

VOS_VOID VOS_QueuePrintFull( VOS_UINT32 ulQueue, VOS_CHAR *pcBuf, VOS_UINT32 ulLen);

VOS_UINT32 VOS_CheckTaskQueue(VOS_UINT32 ulPid,VOS_UINT32 ulEntries);

VOS_VOID VOS_ClearQueueInfoByFid(VOS_UINT32 ulFid);



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _VOS_QUEUE_H */
