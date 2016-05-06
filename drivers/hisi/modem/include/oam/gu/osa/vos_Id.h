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
/* FileName: vos_Id.h                                                        */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement FID&PID                                            */
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

#ifndef _VOS_ID_H
#define _VOS_ID_H


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "dopra_def.h"

#if (VOS_VXWORKS== VOS_OS_VER)
#include "stdio.h"
#endif

#include "v_typdef.h"
#include "vos_config.h"
#include "v_queue.h"
#include "v_msg.h"
#include "v_id.h"
#include "v_IO.h"
#include "v_task.h"

/* errno definiens */
#define VOS_ERRNO_REG_FID_PID_INVALID_PID                   0x20000001
#define VOS_ERRNO_REG_FID_PID_INVALID_FID                   0x20000002

#define VOS_ERRNO_FIDPID_REGPIDI_INPUTPIDINVALID            0x20140006
#define VOS_ERRNO_FIDPID_REGPIDI_INPUTFUNCARENULL           0x20140007
#define VOS_ERRNO_FIDPID_REGPIDI_PIDINACTIVE                0x20140008
#define VOS_ERRNO_FIDPID_REGMPRI_INPUT1INVALID              0x2014000F
#define VOS_ERRNO_FIDPID_REGMPRI_INPUT2INVALID              0x20140010

/* the type of buffer.msg or mem */
enum
{
    VOS_LOCATION_MSG,
    VOS_LOCATION_MEM
};

/* the Max messages stored in queue of one FID */
#define VOS_FID_QUEUE_LENGTH                                120
/* the Max length of message stored in queue of one FID */
/* the pointer of address be sent not the message self */
#define VOS_FID_MAX_MSG_LENGTH                              sizeof(VOS_VOID *)

#define VOS_ID_PID_NULL                 -1
#define VOS_ID_FID_NULL                 -1

typedef struct
{
    int                 Pid;
    int                 Fid;
    Init_Fun_Type       InitFunc;
    Msg_Fun_Type        MsgFunction;
    int                 priority;
#if VOS_YES == VOS_ANALYZE_PID_MEM
    VOS_UINT32          ulMsgSize;
    VOS_UINT32          ulMemSize;
    VOS_UINT32          ulMsgPeakSize;
    VOS_UINT32          ulMemPeakSize;
#endif
    MODEM_ID_ENUM_UINT16 usModemId;
    VOS_UINT16          usReserved; 
    VOS_UINT8           aucRsv[4];
} VOS_PID_RECORD;

enum
{
    VOS_PID_INVAILD,
    VOS_PID_AVAILABLE,
    VOS_PID_UNSURE
};

typedef struct
{
    MODEM_ID_ENUM_UINT16    usModemId;
    VOS_UINT16              usPidInvaild;
}VOS_QUERY_PID_INFO_STRU;

extern VOS_PID_RECORD   vos_PidRecords[ ];

#define VOS_ID_MAX_FID_NAME_LENGTH      16

/* the max selftask belong to one FID*/
#define VOS_MAX_SELF_TASK_OF_FID        6

typedef struct
{
    int                 Fid;
    VOS_UINT8           aucRsv[4];
    Init_Fun_Type       InitFunc;     /* VOS_ULFUNCPTR       InitFunc; */
    VOS_UINT32          StartOrder;

    VOS_UINT32          Tid;
    VOS_UINT32          Priority;
    VOS_UINT32          StackSize;
    VOS_TASK_ENTRY_TYPE TaskFunction;
    VOS_UINT32          TaskArgument[VOS_TARG_NUM];

    VOS_UINT32          Qid;
    VOS_UINT32          MaxMsgNumber;
    VOS_UINT32          MaxMsgLength;
    VOS_UINT32          QueueOptions;
    /* which should be del when only one FID exists */
    VOS_UINT32          MAXQidSize;
    VOS_UINT8           aucRsv1[4];

    /*VOS_UINT32          EventProcTaskTid;
    VOS_UINT32          EventProcTaskPriority;
    VOS_UINT32          EventProcTaskStackSize;
    Event_Fun_Type      EventProcTaskFunc;*/

    /*VOS_PID             SelfProcTaskPid;*/
    VOS_UINT32          SelfProcTaskTid[VOS_MAX_SELF_TASK_OF_FID];
    VOS_UINT32          SelfProcTaskPriority[VOS_MAX_SELF_TASK_OF_FID];
    VOS_UINT32          SelfProcTaskStack[VOS_MAX_SELF_TASK_OF_FID];
    VOS_TASK_ENTRY_TYPE SelfProcTaskFunc[VOS_MAX_SELF_TASK_OF_FID];
    char                Name[VOS_ID_MAX_FID_NAME_LENGTH];
} VOS_FID_CONTROL_BLOCK;

typedef struct
{
    VOS_PID             ulPid;
    VOS_UINT32          ulMsgPeakSize;
    VOS_UINT32          ulMemPeakSize;
}VOS_PID_PEAK_MEM_STRU;

extern VOS_FID_CONTROL_BLOCK   vos_FidCtrlBlk[ ];

VOS_UINT32 VOS_RegisterPIDInfo( VOS_PID ulPID ,
                               Init_Fun_Type pfnInitFun ,
                               Msg_Fun_Type pfnMsgFun );

VOS_UINT32 VOS_RegisterMsgTaskPrio(VOS_FID ulFID,
                                   enum VOS_PRIORITY_DEFINE TaskPrio);

VOS_UINT32 VOS_RegisterTaskPrio( VOS_FID ulFID, VOS_UINT32 ulTaskRealPri);


VOS_UINT8 VOS_RegisterSelfTask( VOS_FID                   ulFID,
                                VOS_TASK_ENTRY_TYPE       pfnSelfTask,
                                enum VOS_PRIORITY_DEFINE  TaskPrio,
                                VOS_UINT32                ulStackSize);

VOS_UINT8 VOS_RegisterSelfTaskPrio( VOS_FID             ulFID ,
                                    VOS_TASK_ENTRY_TYPE       pfnSelfTask,
                                    VOS_UINT32                ulTaskRealPri,
                                    VOS_UINT32                ulStackSize);

/*VOS_UINT32 VOS_BindPIDToSelfTask( VOS_PID ulPid, VOS_FID ulFid,
                                  VOS_UINT8 ucIndex );*/

VOS_UINT32 VOS_PidCtrlBlkInit(VOS_VOID);

VOS_UINT32 VOS_PidsInit(VOS_VOID);

VOS_UINT32 VOS_FidCtrlBlkInit(VOS_VOID);

VOS_UINT32 VOS_FidsInit(VOS_VOID);

VOS_UINT32 CreateFidsQueque(VOS_VOID);

VOS_UINT32 CreateFidsTask(VOS_VOID);

VOS_VOID vos_FidTask( VOS_UINT32 ulQueueID, VOS_UINT32 FID_value,
                      VOS_UINT32 Para1, VOS_UINT32 Para2 );

typedef VOS_UINT32 (*VOS_MSG_HOOK_FUNC)( VOS_VOID * pMsg );

VOS_MSG_HOOK_FUNC VOS_RegisterMsgGetHook( VOS_MSG_HOOK_FUNC pfnMsgHook );

VOS_UINT32 VOS_RegisterMsgTaskEntry(VOS_FID ulFID, VOS_VOIDFUNCPTR pfnMsgTask);

VOS_UINT32 VOS_GetQueueIDFromFid(VOS_UINT32 ulFid);

VOS_UINT32 VOS_SuspendFidTask(VOS_FID ulFid);

VOS_UINT32 VOS_ResumeFidTask(VOS_FID ulFid);

VOS_UINT32 VOS_SuspendFidsTask(VOS_VOID);

VOS_UINT32 VOS_ResumeFidsTask(VOS_VOID);

#if VOS_YES == VOS_ANALYZE_PID_MEM
VOS_VOID VOS_IncreasePidMemory(VOS_PID ulPid, VOS_UINT32 ulSize, VOS_UINT32 ulType);

VOS_VOID VOS_DecreasePidMemory(VOS_PID ulPid, VOS_UINT32 ulSize, VOS_UINT32 ulType);
#endif

VOS_UINT32 VOS_AnalyzePidMemory(VOS_VOID *pBUffer, VOS_UINT32 ulSize, VOS_UINT32 *pulNum);

VOS_UINT32 VOS_GetTCBFromPid(VOS_UINT32 ulPid);

MODEM_ID_ENUM_UINT16 VOS_GetModemIDFromPid(VOS_UINT32 ulPid);

VOS_BOOL VOS_CheckPSPidValidity(VOS_UINT32 ulPid);

VOS_VOID VOS_OsaGlobalShow(VOS_VOID);

VOS_UINT32 VOS_GetFIdRelPri(enum VOS_PRIORITY_DEFINE ulFidPri, VOS_UINT32 *pulTaskRealPri);

VOS_UINT32 VOS_CheckPidValidity(VOS_UINT32 ulPid);

VOS_UINT32 VOS_QueryPidInfoBufSize(VOS_VOID);

VOS_VOID VOS_QueryPidInfo(VOS_VOID *pBuf);

VOS_VOID VOS_SetPidInfo(VOS_VOID *pBuf, VOS_UINT16 usLen);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _VOS_ID_H */

