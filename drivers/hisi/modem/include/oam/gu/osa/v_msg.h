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
/* FileName: v_msg.h                                                         */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement message function                                   */
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

#ifndef _VOS_MSG_H
#define _VOS_MSG_H

#include "v_typdef.h"
#include "vos_config.h"
#include "v_blkMem.h"
#include "VosPidDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/* errno definiens */
#define VOS_ERRNO_MSG_GETPRIO_INPUT1ISNULL                  0x20040003
#define VOS_ERRNO_MSG_FREE_INPUTMSGISNULL                   0x20040091
#define VOS_ERRNO_MSG_FREE_INPUTPIDINVALID                  0x20040035
#define VOS_ERRNO_MSG_FREE_NON_DOPRA_ADDR                   0x20040036
#define VOS_ERRNO_MSG_FREE_NON_START_ADDR                   0x20040083
#define VOS_ERRNO_MSG_FREE_NON_START_UNIT                   0x20040084
#define VOS_ERRNO_MSG_FREE_STATUSERROR                      0x20040037
#define VOS_ERRNO_MSG_FREERES_STATUSERROR                   0x2004009B
#define VOS_ERRNO_MSG_RESERVE_INVALIDMSG                    0x20040095
#define VOS_ERRNO_MSG_POST_INPUTMSGISNULL                   0x20040039
#define VOS_ERRNO_MSG_POST_INPUTPIDINVALID                  0x20040038
#define VOS_ERRNO_MSG_POST_RECVCPUNOTLOCAL                  0x20040040
#define VOS_ERRNO_MSG_POST_RECVPIDINVALID                   0x20040041
#define VOS_ERRNO_MSG_POST_MSGFUNCISNULL                    0x20040042
#define VOS_ERRNO_MSG_ICC_CPUIDISBIG                        0x20040050
#define VOS_ERRNO_MSG_ICC_WRITEMSGERROR                     0x20040051
#define VOS_ERRNO_MSG_ICC_DATALENISNULL                     0x20040052
#define VOS_ERRNO_MSG_ICC_READDATAFAIL                      0x20040053
#define VOS_ERRNO_MSG_ICC_PIDTOOSMALL                       0x20050054
#define VOS_ERRNO_MSG_ICC_PIDTERROR                         0x20050055
#define VOS_ERRNO_MSG_ICC_UDIHANDLERERROR                   0x20050056
#define VOS_ERRNO_MSG_SEND_FUNCEMPTY                        0x20050057
#define VOS_ERRNO_MSG_PID_NO_FID                            0x20050058
#define VOS_ERRNO_MSG_MB_PIDTERROR                          0x20050059
#define VOS_ERRNO_MSG_MB_SENDERROR                          0x20050060
#define VOS_ERRNO_MSG_MB_DATALENISNULL                      0x20050061
#define VOS_ERRNO_MSG_INT_MSGERROR                          0x20050062
#define VOS_ERRNO_MSG_CCORE_RESET                           0x20050063
#define VOS_ERRNO_MSG_MAILBOX_RESET                         0x20050064
#define VOS_ERRNO_MSG_DRV_READ_MAIL_FAIL                    0x20050065
#define VOS_ERRNO_MSG_ICC_WRITEMSGFULL                      0x20050066
#define VOS_ERRNO_MSG_ICC_WRITEHIFIMSGFULL                  0x20050067

/* The message block (packege) head for each message package    */
typedef struct tagMsgBlockHead_S
{
    VOS_UINT32    ulFlag;  /* The message head flag, = VOS_MSG_HEAD_FLAG  */
} MSG_BLOCK_HEAD;

#if(VOS_OS_VER == VOS_WIN32)

#define VOS_LOCAL_CPUID                  0x7F000001

#else

#define VOS_LOCAL_CPUID                  0

#endif

#define VOS_MSG_HEADER  VOS_UINT32 ulSenderCpuId;  \
                        VOS_UINT32 ulSenderPid;    \
                        VOS_UINT32 ulReceiverCpuId;\
                        VOS_UINT32 ulReceiverPid;  \
                        VOS_UINT32 ulLength;

/* VOS common message header length, sizeof(VOS_MSG_HEADER) */
#define VOS_MSG_HEAD_LENGTH              20

/* length of message block head */
#define VOS_MSG_BLK_HEAD_LEN    ( sizeof(MSG_BLOCK_HEAD) )

/* Flag of message packet valid */
#define VOS_MSG_HEAD_FLAG                0xA1D538FB
#define VOS_MSG_RESERVED_HEAD_FLAG       0xA1D538FF

#define VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH  \
               ((VOS_MSG_BLK_HEAD_LEN) + (VOS_MSG_HEAD_LENGTH))

#pragma pack(1)
struct MsgCB
{
    VOS_MSG_HEADER
    VOS_UINT8 aucValue[2];
};
#pragma pack()

typedef struct MsgCB MSG_CB;
typedef struct MsgCB MsgBlock;

enum MSG_PRIORITY
{
    VOS_EMERGENT_PRIORITY_MSG,
    VOS_NORMAL_PRIORITY_MSG,
    VOS_AUXILIARY_PRIORITY_MSG
};

typedef VOS_VOID   (*Msg_Fun_Type)( MsgBlock * pMsg );

typedef VOS_UINT32 (*PVOSSENDMSGPROC)(VOS_PID Pid, VOS_VOID **ppMsg,VOS_UINT32 ulFileID, VOS_INT32 usLineNo);

typedef struct
{
    VOS_PID         ulEndPID;
    VOS_UINT32      ulRsv;
    PVOSSENDMSGPROC pfSendMsg;
    PVOSSENDMSGPROC pfSendUrgentMsg;
}VOS_SENDMSG_FUNCLIST_ST;


typedef struct
{
    VOS_UINT32 ulMailBoxCode;   /*邮箱编码*/
    VOS_UINT32 ulFileID;        /*函数调用的文件ID*/
    VOS_INT32 lLineNo;          /*函数调用的行号*/
}VOS_DRVMB_MSG_PARA_STRU;

#ifdef __DART__
VOS_UINT32 VOS_SendMsg( VOS_PID Pid, VOS_VOID * pMsg );
MsgBlock * VOS_AllocMsg( VOS_PID Pid, VOS_UINT32 ulLength );
VOS_UINT32 VOS_FreeMsg( VOS_PID Pid, MsgBlock * pMsg );
VOS_UINT32 VOS_ForceFreeMsg( void* pMsg );
VOS_UINT32 VOS_SendUrgentMsg(VOS_PID Pid, void* pMsg );
VOS_UINT32 VOS_PostMsg( VOS_PID Pid, VOS_VOID * pMsg);
VOS_VOID*  VOS_GetMsg( VOS_UINT32 ulTaskID );
VOS_UINT32 VOS_ReserveMsg( VOS_PID Pid, MsgBlock * pMsg);
VOS_UINT32 VOS_FreeReservedMsg( VOS_PID Pid, MsgBlock * pMsg );
#else

/*lint -function(malloc(1),V_AllocMsg(2))*/
MsgBlock * V_AllocMsg( VOS_PID Pid, VOS_UINT32 ulLength,
                       VOS_UINT32 ulFileID, VOS_INT32 usLineNo );

MsgBlock * VOS_AllocTimerMsg( VOS_PID Pid, VOS_UINT32 ulLength );

#ifndef DMT
#define VOS_AllocMsg( Pid, ulLength ) \
    V_AllocMsg( (Pid), (ulLength), VOS_FILE_ID, __LINE__)
#endif /* DMT */

#define VOS_AllocMsgPrior( Pid, ulLength, ulPrio )\
    V_AllocMsg( (Pid), (ulLength), VOS_FILE_ID, __LINE__)

VOS_UINT32 V_FreeMsg( VOS_PID Pid, VOS_VOID **ppMsg,
                         VOS_UINT32 ulFileID, VOS_INT32 usLineNo );

#define VOS_FreeMsg( Pid, pMsg )\
    V_FreeMsg( (Pid), (VOS_VOID**)(&(pMsg)), VOS_FILE_ID, __LINE__ )

VOS_UINT32 V_SendMsg( VOS_PID Pid, VOS_VOID **ppMsg,
                          VOS_UINT32 ulFileID, VOS_INT32 usLineNo );

VOS_UINT32 V_SendMsgNormally(VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 lLineNo);

#ifndef DMT
#define VOS_SendMsg( Pid, pMsg )\
    V_SendMsg( (Pid), (VOS_VOID**)(&(pMsg)), VOS_FILE_ID, __LINE__ )

#define VOS_SendMsgNormally( Pid, pMsg )\
    V_SendMsgNormally( (Pid), (VOS_VOID**)(&(pMsg)), VOS_FILE_ID, __LINE__ )
#endif /* DMT */

VOS_UINT32 V_SendUrgentMsg( VOS_PID Pid, VOS_VOID **ppMsg,
                                 VOS_UINT32 ulFileID, VOS_INT32 usLineNo );
#ifndef DMT
#define VOS_SendUrgentMsg( Pid, pMsg )\
    V_SendUrgentMsg( (Pid), (VOS_VOID**)(&(pMsg)), VOS_FILE_ID, __LINE__ )
#endif /* DMT */


VOS_UINT32 V_PostMsg( VOS_PID Pid, VOS_VOID * pMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 usLineNo );

#define VOS_PostMsg( Pid, pMsg )\
    V_PostMsg( (Pid), (pMsg), VOS_FILE_ID, __LINE__ )

/*VOS_VOID*  VOS_GetMsg( VOS_UINT32 ulTaskID );*/

VOS_UINT32 V_ReserveMsg( VOS_PID Pid, MsgBlock * pMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 usLineNo );

#define VOS_ReserveMsg( Pid, pMsg )\
    V_ReserveMsg( (Pid), (pMsg), VOS_FILE_ID, __LINE__ )

VOS_UINT32 V_UnreserveMsg( VOS_PID Pid, MsgBlock * pMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 usLineNo );

#define VOS_UnreserveMsg( Pid, pMsg )\
    V_UnreserveMsg( (Pid), (pMsg), VOS_FILE_ID, __LINE__ )

VOS_UINT32 V_FreeReservedMsg( VOS_PID Pid, VOS_VOID **ppMsg,
                                   VOS_UINT32 ulFileID, VOS_INT32 usLineNo );

#define VOS_FreeReservedMsg( Pid, pMsg )\
    V_FreeReservedMsg( (Pid), (VOS_VOID**)(&(pMsg)),  VOS_FILE_ID, __LINE__  )


VOS_UINT32 V_SendLocalMsg( VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 usLineNo );

VOS_UINT32 V_SendMsgByICC( VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 lLineNo );

#if (FEATURE_ON == FEATURE_HIFI_USE_ICC)
VOS_UINT32 V_SendHifiMsgByICC(VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 lLineNo );
#endif

VOS_UINT32 V_SendLocalUrgentMsg( VOS_PID Pid, VOS_VOID ** ppMsg,
                                  VOS_UINT32 ulFileID, VOS_INT32 lLineNo );

extern VOS_VOID VOS_DRVMB_OSAMsg_CB(VOS_VOID *pUserPara, VOS_VOID *pMailHandle, VOS_UINT32 ulLen);

extern VOS_UINT32 VOS_DRVMB_Init(VOS_VOID);

extern VOS_UINT32 VOS_SendHIFIMsg( VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 lLineNo );

extern VOS_UINT32 VOS_SendHIFIUrgentMsg( VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 lLineNo );

extern VOS_UINT32 VOS_SendMCUMsg( VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 lLineNo );

extern VOS_UINT32 VOS_SendMCUUrgentMsg( VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 lLineNo );

#if (VOS_DEBUG == VOS_DOPRA_VER)

VOS_UINT32 VOS_RegisterMsgAllocHook( VOS_UINT32 ulMode, MEMORY_HOOK_FUNC pfnHook);

#endif

VOS_VOID VOS_ModifyMsgInfo(VOS_VOID *pMsg, VOS_PID Pid);

#endif

VOS_UINT32 VOS_RegisterAwakeFun(MODEM_ID_ENUM_UINT16 enModem, Msg_Fun_Type pfnHook);

VOS_VOID VOS_ExecuteAwakeFun(MsgBlock *pstMsgCtrlBlk);

VOS_UINT32 VOS_CheckInterrupt( VOS_VOID );

VOS_UINT32 VOS_CheckRcvPid(VOS_UINT32 ulReceiverPid);

VOS_VOID VOS_IccDebugInfoInit(VOS_VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _VOS_MSG_H */
