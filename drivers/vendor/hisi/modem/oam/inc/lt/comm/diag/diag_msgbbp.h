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


#ifndef __DIAG_MSGBBP_H__
#define __DIAG_MSGBBP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include "msp_diag_comm.h"
#include "diag_common.h"
#include "msp_errno.h"


/*****************************************************************************
  2 macro
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
描述 :
ID   : DIAG_CMD_DRX_SAMPLE_REG_WR
REQ : DIAG_CMD_DRX_SAMPLE_REG_WR_REQ_STRU
CNF : DIAG_CMD_DRX_SAMPLE_REG_WR_CNF_STRU
IND : DIAG_CMD_DRX_REG_WR_IND_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulOmDrxSampleId;
	VOS_UINT16 usOpid;
	VOS_UINT16 usPowrDomainBitmap;
	VOS_UINT8  ucDrxRegData[0];
}DIAG_CMD_DRX_SAMPLE_REG_WR_REQ_STRU;

typedef struct
{
    VOS_UINT32  ulAuid;                     /* 原AUID*/
    VOS_UINT32  ulSn;                       /* HSO分发，插件命令管理*/
    VOS_UINT32   ulRet;  /*命令执行返回值，成功返回0，失败返回-1*/
} DIAG_CMD_DRX_SAMPLE_REG_WR_CNF_STRU;

/*****************************************************************************
描述 : 获取SOCP\BBP DMA基地址等
ID   : DIAG_CMD_DRX_SAMPLE_REG_WR
REQ : DIAG_CMD_DRX_SAMPLE_GET_ADDR_REQ_STRU
CNF : DIAG_CMD_DRX_SAMPLE_GET_ADDR_CNF_STRU
IND : DIAG_CMD_DRX_REG_WR_IND_STRU
*****************************************************************************/
typedef enum
{
	DRX_SAMPLE_BBP_DMA_BASE_ADDR = 0x00,
	DRX_SAMPLE_BBP_DBG_BASE_ADDR ,
	DRX_SAMPLE_BBP_SRC_BASE_ADDR ,
	DRX_SAMPLE_POW_ONOFF_CLK_BASE_ADDR ,
	DRX_SAMPLE_SOCP_BASE_ADDR
}DIAG_CMD_DRX_SAMPLE_ADDR_TYPE_E;

typedef struct
{
	DIAG_CMD_DRX_SAMPLE_ADDR_TYPE_E eDiagDrxSampleAddr;
}DIAG_CMD_DRX_SAMPLE_GET_ADDR_REQ_STRU;

typedef struct
{
    VOS_UINT32  ulAuid;                     /* 原AUID*/
    VOS_UINT32  ulSn;                       /* HSO分发，插件命令管理*/
    VOS_UINT32   ulDrxSampleType;
    VOS_UINT32   ulDrxSampleAddr;
    VOS_UINT32   ulRet;  /*命令执行返回值，成功返回0，失败返回-1*/
} DIAG_CMD_DRX_SAMPLE_GET_ADDR_CNF_STRU;

/*****************************************************************************
描述 : 配置SOCP 基地址
ID   : DIAG_CMD_DRX_SAMPLE_REG_WR
REQ : DIAG_CMD_DRX_SAMPLE_CFG_CHNADDR_REQ_STRU
CNF : DIAG_CMD_DRX_SAMPLE_CFG_CHNADDR_CNF_STRU
IND : DIAG_CMD_DRX_REG_WR_IND_STRU
*****************************************************************************/
#define DIAG_PRODUCT_VERSION_LENGTH  (16)

typedef struct
{
    VOS_UINT32  ulAddrType; /* config here */
}DIAG_CMD_DRX_SAMPLE_GET_VERSION_REQ_STRU;

typedef struct
{
    VOS_UINT32  ulAuid;                     /* 原AUID*/
    VOS_UINT32  ulSn;                       /* HSO分发，插件命令管理*/
	VOS_UINT8   ulProductName[DIAG_PRODUCT_VERSION_LENGTH];
	VOS_UINT8   ulSolutiongName[DIAG_PRODUCT_VERSION_LENGTH];
    VOS_UINT32   ulRet;  /*命令执行返回值，成功返回0，失败返回-1*/
} DIAG_CMD_DRX_SAMPLE_GET_VERSION_CNF_STRU;


/*****************************************************************************
描述 : 获取SOCP\BBP DMA基地址等
ID   : DIAG_CMD_DRX_SAMPLE_REG_WR
REQ : DIAG_CMD_DRX_SAMPLE_GET_ADDR_REQ_STRU
CNF : DIAG_CMD_DRX_SAMPLE_GET_ADDR_CNF_STRU
IND : DIAG_CMD_DRX_REG_WR_IND_STRU
*****************************************************************************/
typedef enum
{
	DRX_SAMPLE_BBP_DMA_LOG0_CHNSIZE = 0x00,
	DRX_SAMPLE_BBP_DMA_LOG1_CHNSIZE ,
	DRX_SAMPLE_BBP_DMA_LOG2_CHNSIZE ,
	DRX_SAMPLE_BBP_DMA_LOG3_CHNSIZE ,
	DRX_SAMPLE_BBP_DMA_LOG4_CHNSIZE ,
	DRX_SAMPLE_BBP_DMA_LOG5_CHNSIZE ,
	DRX_SAMPLE_BBP_DMA_LOG6_CHNSIZE ,
	DRX_SAMPLE_BBP_DMA_LOG7_CHNSIZE ,
	DRX_SAMPLE_BBP_DMA_DATA_CHNSIZE
}DIAG_CMD_DRX_SAMPLE_CHNSIZE_E;

typedef enum
{
	SOCP_BBP_DMA_LOG0_CHNSIZE = 0x10000,
	SOCP_BBP_DMA_LOG1_CHNSIZE = 0x0,
	SOCP_BBP_DMA_LOG_COM_CHNSIZE = 0x2000,
}DIAG_SOCP_SAMPLE_CHNSIZE_E;

typedef struct
{
    DIAG_CMD_DRX_SAMPLE_CHNSIZE_E   ulChanEnum;
    VOS_UINT32                      ulChan;
    VOS_UINT32                      ulAddr;
    VOS_UINT32                      ulSize;
}DIAG_DRX_SAMPLE_CHNSIZE_S;


typedef struct
{
	DIAG_CMD_DRX_SAMPLE_CHNSIZE_E eDiagDrxSampleChnSize;
}DIAG_CMD_DRX_SAMPLE_GET_CHNSIZE_REQ_STRU;

/* DIAG_CMD_DRX_DATA_SAMPLE_REG_WR_REQ命令对应的CNF，底软Sleep模块接收到该命令后即可返回成功*/
typedef struct
{
    VOS_UINT32  ulAuid;                     /* 原AUID*/
    VOS_UINT32  ulSn;                       /* HSO分发，插件命令管理*/
    VOS_UINT32   ulChnType;  /*通道类型*/
    VOS_UINT32   ulChnAddr;  /*通道内存起始地址*/
	VOS_UINT32   ulChnSize;  /*通道大小*/
    VOS_UINT32   ulRet;      /*命令执行返回值，成功返回0，失败返回-1*/
} DIAG_CMD_DRX_SAMPLE_GET_CHNSIZE_CNF_STRU;


/*****************************************************************************
描述 : 使能SOCP 通道
ID   : DIAG_CMD_DRX_SAMPLE_REG_WR
REQ : DIAG_CMD_DRX_SAMPLE_ABLE_CHN_REQ_STRU
CNF : DIAG_CMD_DRX_SAMPLE_ABLE_CHN_CNF_STRU
IND : DIAG_CMD_DRX_REG_WR_IND_STRU
*****************************************************************************/
typedef enum
{
	DRX_SAMPLE_SOCP_CHN_ENABLE   = 0x00,
	DRX_SAMPLE_SOCP_CHN_DISABLE  = 0x01
}DIAG_CMD_DRX_SAMPLE_ABLE_CHN_E;

typedef struct
{
	DIAG_CMD_DRX_SAMPLE_ABLE_CHN_E eDiagDrxSampleAbleChn;
}DIAG_CMD_DRX_SAMPLE_ABLE_CHN_REQ_STRU;

typedef struct
{
    VOS_UINT32  ulAuid;                     /* 原AUID*/
    VOS_UINT32  ulSn;                       /* HSO分发，插件命令管理*/
    VOS_UINT32   ulRet;  /*命令执行返回值，成功返回0，失败返回-1*/
} DIAG_CMD_DRX_SAMPLE_ABLE_CHN_CNF_STRU;


typedef struct
{
    VOS_UINT32  ulAuid;                     /* 原AUID*/
    VOS_UINT32  ulSn;                       /* HSO分发，插件命令管理*/
    VOS_UINT32   ulRet;  /*命令执行返回值，成功返回0，失败返回-1*/
} DIAG_CMD_DRX_SAMPLE_COMM_CNF_STRU;

typedef VOS_UINT32 (*DIAG_BBP_PROC)(DIAG_FRAME_INFO_STRU * pData);
typedef struct
{
    DIAG_BBP_PROC   pFunc;
    VOS_UINT32      ulCmdId;
    VOS_UINT32      ulReserve;
}DIAG_BBP_PROC_FUN_STRU;


#define DIAG_BBP_DS_ENABLE          (0x56784321)
typedef struct
{
    VOS_UINT32      ulenable;
    VOS_UINT32      ulSize;
    VOS_UINT64      ulAddr;
}DIAG_BBP_DS_ADDR_INFO_STRU;

/* 核间透传通信结构体 */
typedef struct
{
     VOS_MSG_HEADER                     /*VOS头 */
     VOS_UINT32                         ulMsgId;
     DIAG_FRAME_INFO_STRU                 stInfo;
}DIAG_BBP_MSG_A_TRANS_C_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
VOS_UINT32 diag_DrxSampleGenProc(DIAG_FRAME_INFO_STRU *pData);
VOS_UINT32 diag_DrxSampleGetAddrProc(DIAG_FRAME_INFO_STRU *pData);
VOS_UINT32 diag_DrxSampleGetChnSizeProc(DIAG_FRAME_INFO_STRU *pData);
VOS_UINT32 diag_DrxSampleGetVersionProc(DIAG_FRAME_INFO_STRU *pData);
VOS_UINT32 diag_DrxSampleAbleChnProc(DIAG_FRAME_INFO_STRU *pData);
VOS_UINT32 diag_BbpMsgProc(DIAG_FRAME_INFO_STRU *pData);
VOS_UINT32 diag_AppTransBbpProc(MsgBlock* pMsgBlock);
VOS_VOID diag_BbpMsgInit(VOS_VOID);
VOS_VOID diag_BbpInitSocpChan(VOS_VOID);
VOS_VOID diag_BbpEnableSocpChan(VOS_VOID);
VOS_VOID diag_BbpShowDebugInfo(VOS_VOID);
/*****************************************************************************
  9 OTHERS
*****************************************************************************/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of  */



