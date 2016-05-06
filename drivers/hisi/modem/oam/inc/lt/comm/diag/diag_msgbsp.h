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


#ifndef __DIAG_MSGBSP_H__
#define __DIAG_MSGBSP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "mdrv.h"
#include "NVIM_Interface.h"
#include "msp_diag_comm.h"
#include "diag_common.h"
#include "msp_errno.h"

/*****************************************************************************
  2 macro
*****************************************************************************/


#define DIAG_CMD_BSP_LOG_SET                        (DIAG_CMD_BSP_LOG_SET_ACORE)
#define DIAG_CMD_BSP_SYSVIEW_SWT                    (DIAG_CMD_BSP_SYSVIEW_SWT_ACORE)
#define DIAG_CMD_BSP_SYSVIEW_IND                    (DIAG_CMD_BSP_SYSVIEW_IND_ACORE)
#define DIAG_CMD_BSP_CPU_SWT                        (DIAG_CMD_BSP_CPU_SWT_ACORE)


#define DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pstDiagHead, pstInfo, ret) \
do {    \
    ulLen = sizeof(DIAG_BSP_MSG_A_TRANS_C_STRU)-VOS_MSG_HEAD_LENGTH + pstDiagHead->ulMsgLen;  \
    pstInfo = (DIAG_BSP_MSG_A_TRANS_C_STRU*)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, ulLen);  \
    if(VOS_NULL == pstInfo) \
    {   \
        ret = ERR_MSP_MALLOC_FAILUE;    \
        goto DIAG_ERROR;    \
    }   \
    pstInfo->ulReceiverPid = MSP_PID_DIAG_AGENT;    \
    pstInfo->ulSenderPid   = MSP_PID_DIAG_APP_AGENT;    \
    pstInfo->ulMsgId       = DIAG_MSG_BSP_A_TRANS_C_REQ;    \
    ulLen = sizeof(DIAG_FRAME_INFO_STRU)+pstDiagHead->ulMsgLen; \
    VOS_MemCpy(&pstInfo->stInfo, pstDiagHead, ulLen);   \
    ret = VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, pstInfo); \
    if(ret) \
    {   \
        goto DIAG_ERROR;    \
    }   \
}while(0)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

enum
{
    DIAG_LEVEL_NORMAL = 0,
    DIAG_LEVEL_ADVANCED
};


/*****************************************************************************
   5 STRUCT
*****************************************************************************/
typedef struct
{
    VOS_UINT32 trace_type;
    VOS_UINT32 trace_swt;
    VOS_UINT32 period;
} DIAG_BSP_SYVIEW_SWT_CFG_STRU;

typedef struct
{
    VOS_UINT32                task_id;
    VOS_UINT8                  name[12];
} DIAG_BSP_TASK_INFO_STRU;

typedef struct
{
    VOS_UINT32  ulAuid;                     /* 原AUID*/
    VOS_UINT32  ulSn;                       /* HSO分发，插件命令管理*/
    VOS_UINT32  trace_type;
    VOS_UINT32  ulRet;
    VOS_UINT32  ullen;
    DIAG_BSP_TASK_INFO_STRU st_task_info[0];
} DIAG_BSP_SYVIEW_SWT_CNF_STRU;

typedef struct
{
    VOS_UINT32  ulAuid;                     /* 原AUID*/
    VOS_UINT32  ulSn;                       /* HSO分发，插件命令管理*/
    VOS_UINT8*  ucData[0];
}DIAG_BSP_COMM_AXI_CNF_STRU;

typedef struct
{
    VOS_UINT32  ulAuid;                     /* 原AUID*/
    VOS_UINT32  ulSn;                       /* HSO分发，插件命令管理*/
    VOS_UINT32  ulRet;
}DIAG_BSP_COMM_CNF_STRU;


typedef VOS_UINT32 (*DIAG_BSP_PROC)(VOS_UINT8 *pData);
typedef struct
{
    DIAG_BSP_PROC   pFunc;
    VOS_UINT32      ulCmdId;
    VOS_UINT32      ulReserve;
}DIAG_BSP_PROC_FUN_STRU;


/* 核间透传通信结构体 */
typedef struct
{
     VOS_MSG_HEADER                     /*VOS头 */
     VOS_UINT32                         ulMsgId;
     DIAG_FRAME_INFO_STRU               stInfo;
}DIAG_BSP_MSG_A_TRANS_C_STRU;


/*****************************************************************************
描述 : 读NV
ID   : DIAG_CMD_NV_RD
REQ : DIAG_CMD_NV_QRY_REQ_STRU
CNF : DIAG_CMD_NV_QRY_CNF_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulModemid;      /* 0-modem0;1-modem1;2-modem2 */
    VOS_UINT32 ulCount;
    VOS_UINT32 ulNVId[0];      /* 待获取的NV项Id */
} DIAG_CMD_NV_QRY_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;         /* 原AUID*/
    VOS_UINT32 ulSn;           /* HSO分发，插件命令管理*/
    VOS_UINT32 ulRc;           /* 表明执行结果是否成功, 0表示成功，其他的为错误码*/
    VOS_UINT32 ulModemid;      /* 0-modem0;1-modem1;2-modem2 */
    VOS_UINT32 ulCount;
    VOS_UINT32 ulNVId;         /* 获取的NV项Id*/
    VOS_UINT32 ulDataSize;     /* 获取的NV项数据的大小*/
    VOS_UINT8  aucData[0];     /* 获取的NV项数据*/
} DIAG_CMD_NV_QRY_CNF_STRU;

/*****************************************************************************
描述 : 写NV
ID   : DIAG_CMD_NV_WR
REQ : DIAG_CMD_NV_WR_REQ_STRU
CNF : DIAG_CMD_NV_WR_CNF_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulModemid;      /* 0-modem0;1-modem1;2-modem2 */
    VOS_UINT32 ulCount;
    VOS_UINT32 ulNVId;         /* 需要写入的NV ID*/
    VOS_UINT32 ulDataSize;     /* 需要写入的NV项数据的大小*/
    VOS_UINT8  aucData[0];     /* 数据缓冲区*/
} DIAG_CMD_NV_WR_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;         /* 原AUID*/
    VOS_UINT32 ulSn;           /* HSO分发，插件命令管理*/
    VOS_UINT32 ulModemid;      /* 0-modem0;1-modem1;2-modem2 */
    VOS_UINT32 ulRc;           /* 表明执行结果是否成功,0表示成功，其他的为错误码*/
} DIAG_CMD_NV_WR_CNF_STRU;

/*****************************************************************************
描述 : getNVidlist
ID   : DIAG_CMD_NV_LIST
REQ : DIAG_CMD_NV_LIST_REQ_STRU
CNF : DIAG_CMD_NV_LIST_CNF_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulRsv;
} DIAG_CMD_NV_LIST_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;
    VOS_UINT32 ulSn;
    VOS_UINT32 ulRc;
    VOS_UINT32 ulCount;
    NV_LIST_INFO_STRU astNvList[0];
} DIAG_CMD_NV_LIST_CNF_STRU;

/*****************************************************************************
描述 : NV鉴权
ID   : DIAG_CMD_NV_AUTH
REQ : DIAG_CMD_NV_AUTH_REQ_STRU
CNF : DIAG_CMD_NV_AUTH_CNF_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulLen;
    VOS_UINT8  aucAuth[8];
} DIAG_CMD_NV_AUTH_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;
    VOS_UINT32 ulSn;
    VOS_UINT32 ulRc;
} DIAG_CMD_NV_AUTH_CNF_STRU;


/* C核给A核发送NV鉴权结果 */
typedef struct
{
     VOS_MSG_HEADER                     /*VOS头 */
     VOS_UINT32                         ulMsgId;
     VOS_UINT32                         ulLevel;
}DIAG_BSP_NV_AUTH_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
VOS_UINT32  diag_BspAxiMonDataConfig(VOS_UINT8* pstReq);
VOS_UINT32  diag_BspAxiMonConfig(VOS_UINT8* pstReq);
VOS_UINT32  diag_BspAxiMonTerminate(VOS_UINT8* pstReq);
VOS_UINT32  diag_BspAxiMonRegConfig(VOS_UINT8* pstReq);
VOS_UINT32  diag_BspAxiMonDataCtrl(VOS_UINT8* pstReq);
VOS_UINT32  diag_BspAxiMonStart(VOS_UINT8* pstReq);
VOS_UINT32  diag_BspUtraceStart(VOS_UINT8* pstReq);
VOS_UINT32  diag_BspUtraceStop(VOS_UINT8* pstReq);
VOS_UINT32  diag_BspLogProcEntry(VOS_UINT8* pstReq);
VOS_UINT32  diag_BspSysviewProc(VOS_UINT8* pstReq);
VOS_UINT32  diag_BspMsgProc(DIAG_FRAME_INFO_STRU *pData);
VOS_UINT32  diag_NvAuthProc(VOS_UINT8* pstReq);
VOS_VOID    diag_BspShowDebugInfo(VOS_VOID);

#if (VOS_OS_VER == VOS_LINUX)
VOS_VOID    diag_BspMsgInit(VOS_VOID);
VOS_UINT32  diag_NvRdProc(VOS_UINT8* pstReq);
VOS_UINT32  diag_NvWrProc(VOS_UINT8* pstReq);
VOS_UINT32  diag_GetNvListProc(VOS_UINT8* pstReq);
VOS_VOID    diag_InitAuthVariable(VOS_VOID);
VOS_VOID    diag_AuthNvCfg(MsgBlock* pMsgBlock);
#else
VOS_UINT32  diag_AppTransBspProc(MsgBlock* pMsgBlock);
VOS_UINT32 diag_NvAuthSendAcore(VOS_UINT32 ulLev);
#endif

/*****************************************************************************
  9 OTHERS
*****************************************************************************/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of msp_diag.h */


