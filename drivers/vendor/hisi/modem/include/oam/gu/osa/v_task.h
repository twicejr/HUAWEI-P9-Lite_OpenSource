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
/* FileName: v_task.h                                                        */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement task                                               */
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


#ifndef _VOS_TASK_H
#define _VOS_TASK_H

#include "v_typdef.h"
#include "vos_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/* errno definiens */
#define VOS_ERRNO_TASK_CREATE_INPUTENTRYISNULL              0x20000014
#define VOS_ERRNO_TASK_CREATE_INPUTARGSISNULL               0x20000015
#define VOS_ERRNO_TASK_CREATE_INPUTTIDISNULL                0x20000016
#define VOS_ERRNO_TASK_CREATE_INPUTNAMEISNULL               0x20000017
#define VOS_ERRNO_TASK_CREATE_INPUTPRIOINVALID              0x20000018
#define VOS_ERRNO_TASK_CREATE_NAMESAMETOPREV                0x20000019
#define VOS_ERRNO_TASK_CREATE_NOFREETCB                     0x2000001A
#define VOS_ERRNO_TASK_CREATE_CREATEEVENTFAIL               0x2000001B
#define VOS_ERRNO_TASK_CREATE_OSALCREATEFAIL                0x2000001C

#define VOS_TASK_MAGIC_WORD                                 0x55AA5A5A

/* the state of control block */
#define VOS_TASK_CTRL_BLK_IDLE                              0
#define VOS_TASK_CTRL_BLK_BUSY                              1

/* errno define */
#define VOS_TASK_CTRL_BLK_NULL                              0xffffffff
#define VOS_TASK_CTRL_BLK_VXWORKS_TASKID_NULL               -1

#define VOS_MAX_LENGTH_TASK_NAME                            16

#define VOS_TARG_NUM                                        4

#define VOS_EVENT_NOWAIT       0x00000001  /* Don't wait for events */
#define VOS_EVENT_WAIT         0x00000000  /* Wait for events */
#define VOS_EVENT_ANY          0x00000002  /* Wait for ANY of desired bits */
#define VOS_EVENT_ALL          0x00000000  /* Wait for ALL of desired bits */

#define VOS_MSG_SYNC_EVENT             0x200

#if (VOS_WIN32 == VOS_OS_VER)
/* the Max task number supported by VOS */
#define VOS_MAX_TASK_NUMBER                                 190
#else
/* the Max task number supported by VOS */
#define VOS_MAX_TASK_NUMBER                                 165
#endif

VOS_VOID VOS_TaskCtrlBlkInit(VOS_VOID);

typedef VOS_VOID ( * VOS_TASK_ENTRY_TYPE )( VOS_UINT32 ulPara0,
                                            VOS_UINT32 ulPara1,
                                            VOS_UINT32 ulPara2,
                                            VOS_UINT32 ulPara3);

typedef VOS_VOID (*VOS_TASK_SWITCH_HOOK)( VOS_UINT32, VOS_UINT32 );

VOS_UINT32 VOS_CreateTask( VOS_CHAR * puchName,
                           VOS_UINT32 * pulTaskID,
                           VOS_TASK_ENTRY_TYPE pfnFunc,
                           VOS_UINT32 ulPriority,
                           VOS_UINT32 ulStackSize,
                           VOS_UINT32 aulArgs[VOS_TARG_NUM] );

VOS_UINT32 VOS_SuspendTask( VOS_UINT32 ulTaskID );

VOS_UINT32 VOS_ResumeTask( VOS_UINT32 ulTaskID );

#if (VOS_LINUX == VOS_OS_VER)
VOS_VOID VOS_RunTask(VOS_VOID);
#endif

VOS_UINT32 VOS_TaskDelay( VOS_UINT32 ulMillSecs );

#if ((VOS_VXWORKS == VOS_OS_VER) || (VOS_RTOSCK == VOS_OS_VER))

#if (VOS_DEBUG == VOS_CHECK_TASKLOCK)

VOS_UINT32 V_TaskLock( VOS_UINT32 ulFileID, VOS_INT32 lLineNo );

VOS_UINT32 V_TaskUnlock( VOS_VOID );

#define VOS_TaskLock() \
        V_TaskLock( VOS_FILE_ID, __LINE__ )

#define VOS_TaskUnlock() \
        V_TaskUnlock()

#else

VOS_UINT32 VOS_TaskLock( VOS_VOID );

VOS_UINT32 VOS_TaskUnlock( VOS_VOID );

#endif

#else

VOS_UINT32 VOS_TaskLock( VOS_VOID );

VOS_UINT32 VOS_TaskUnlock( VOS_VOID );

#endif

VOS_UINT32 VOS_GetCurrentTaskID( VOS_VOID );

VOS_UINT32 VOS_SuspendFidsTask(VOS_VOID);

VOS_VOID VOS_SuspendAllTask( VOS_UINT32 Para0, VOS_UINT32 Para1,
                             VOS_UINT32 Para2, VOS_UINT32 Para3 );

VOS_VOID VOS_ShowFidsQueueInfo(VOS_UINT32 Para0, VOS_UINT32 Para1,
                               VOS_UINT32 Para2, VOS_UINT32 Para3 );

VOS_UINT32 VOS_RecordFIDTIDInfo( VOS_UINT32 ulFid, VOS_UINT32 ulTid );

VOS_UINT32 VOS_CreateEvent( VOS_UINT32 ulTaskID );

VOS_UINT32 VOS_CheckEvent( VOS_UINT32 ulTaskID );

VOS_UINT32 VOS_EventWrite( VOS_UINT32 ulTaskID, VOS_UINT32 ulEvents );

VOS_UINT32 VOS_EventRead( VOS_UINT32 ulEvents,
                          VOS_UINT32 ulFlags,
                          VOS_UINT32 ulTimeOutInMillSec,
                          VOS_UINT32 *pulRetEvents );

VOS_UINT32 VOS_GetQueueIDFromTID(VOS_UINT32 ulTid);

VOS_UINT32 VOS_GetTCBFromTID(VOS_UINT32 ulTid);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _VOS_TASK_H */
