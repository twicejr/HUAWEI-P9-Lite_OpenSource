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


#ifndef __DIAG_MSGPHY_H__
#define __DIAG_MSGPHY_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include <mdrv.h>
#include  "vos.h"
#include "msp_diag_comm.h"
#include "diag_common.h"
#include "msp_errno.h"
#if (VOS_OS_VER != VOS_LINUX)
#include "TLPhyInterface.h"
#endif


/*****************************************************************************
  2 macro
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum DIAG_SOCP_STATE_ENUM
{
    SOCP_DISABLE,       /* SOCP不可用 */
    SOCP_ENABLE,        /* SOCP可用 */
    SOCP_STATE_BUTT
};
typedef unsigned int DIAG_SOCP_STATE_ENUM_U32;

enum DIAG_LDSP_STATE_ENUM
{
    LDSP_NOT_INIT,      /* 未初始化 */
    LDSP_INITING,       /* 正在初始化 */
    LDSP_INITED,        /* 初始化完成 */
    LDSP_SOCP_ENABLE,   /* DIAG已通知LDSP SOCP可用 */
    LDSP_SOCP_DISABLE,  /* DIAG已通知LDSP SOCP不可用 */
    LDSP_STATE_BUTT
};
typedef unsigned int DIAG_LDSP_STATE_ENUM_U32;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/* 发给DSP的工具连接状态变化请求 */
typedef struct
{
    VOS_UINT32                  ulMsgId;
    VOS_UINT32                  ulOpId;
    VOS_UINT32                  ulReq;
} DIAG_MSG_TO_DSP_STRU;

/* DSP对DIAG发送邮箱消息的回复 */
typedef struct
{
    VOS_UINT32  ulMsgId;
    VOS_UINT32  ulOpId;
    VOS_UINT32  ulCnf;
} DIAG_MSG_FROM_DSP_STRU;

typedef struct
{
    VOS_MSG_HEADER
    DIAG_MSG_FROM_DSP_STRU  ulMsgData;
} DIAG_MSG_DSP_CNF_TO_AGENT_STRU;

/* 核间透传通信结构体 */
typedef struct
{
     VOS_MSG_HEADER                     /*VOS头 */
     VOS_UINT32                         ulMsgId;
     DIAG_FRAME_INFO_STRU               stInfo;
}DIAG_PHY_MSG_A_TRANS_C_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
VOS_UINT32 diag_DspMsgProc(DIAG_FRAME_INFO_STRU *pData);
VOS_UINT32 diag_AppTransPhyProc(MsgBlock* pMsgBlock);
VOS_VOID   diag_DspMsgInit(VOS_VOID);
VOS_VOID   diag_DspNotifySocpState(DIAG_SOCP_STATE_ENUM_U32 state);
VOS_VOID   diag_DspMailboxSelfTask(VOS_VOID);
VOS_VOID   diag_DspConnMsgProc(DIAG_CONNECT_CMD_ENUM_U32 connCmd);

#if (VOS_OS_VER != VOS_LINUX)
VOS_UINT32 diag_DspSendMsg(MAILBOX_SERVICE_TYPE_E serType,VOS_UINT8* pstReq ,VOS_UINT32 ulCmdId,VOS_UINT32 ulDataLen);
VOS_VOID   diag_DspMailboxCb(MAILBOX_INT_TYPE_E enIntType);
#endif
VOS_UINT32 diag_DspSocpVoteCnfMsgProc(MsgBlock * pMsgBlock);
VOS_VOID diag_DspVoteToSocp(SOCP_VOTE_TYPE_ENUM_U32 voteType);
/*****************************************************************************
  9 OTHERS
*****************************************************************************/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of  */


