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



#ifndef __DIAG_DEBUG_H__
#define __DIAG_DEBUG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "product_config.h"
#include  "mdrv.h"
#include  "vos.h"
#include  "msp_errno.h"
#include  "SCMProc.h"
#include  "msp_diag_comm.h"

#pragma pack(4)

typedef enum
{
   DIAG_DEBUG_API = 0,
   DIAG_DEBUG_API_AIR,
   DIAG_DEBUG_API_TRACE,
   DIAG_DEBUG_API_USERPLANE,
   DIAG_DEBUG_API_EVENT,
   DIAG_DEBUG_API_PRINT,
   DIAG_DEBUG_API_VOLTE,
   DIAG_DEBUG_API_TRANS,
   DIAG_DEBUG_API_DEFAULT
}DIAG_DEBUG_API_ENUM;


/* CBT ***********************************************************************/

#define DIAG_DEBUG_SDM_FUN(enType,ulRserved1,ulRserved2,ulRserved3)  \
            diag_CBT(enType,ulRserved1,ulRserved2,ulRserved3)

#define DIAG_PRINT_INFO
#ifdef DIAG_PRINT_INFO
#define diag_printf        (VOS_VOID)vos_printf
#else
#define diag_printf( fmt...)
#endif

typedef enum
{
    EN_DIAG_CBT_MSGMSP_CMD_ENTER,
    EN_DIAG_CBT_MSGMSP_TRANS_ENTER,
    EN_DIAG_CBT_MSGMSP_SYS_ENTER,
    EN_DIAG_CBT_MSGMSP_DFLT_ENTER,

    EN_DIAG_CBT_MSGMSP_TRANS_REQ,
    EN_DIAG_CBT_MSGMSP_TRANS_CNF,

    EN_DIAG_CBT_API_PRINTFV_OK,
    EN_DIAG_CBT_API_PRINTFV_ERR,

    EN_DIAG_CBT_API_EVENT_OK,
    EN_DIAG_CBT_API_EVENT_ERR,

    EN_DIAG_CBT_API_AIR_OK,
    EN_DIAG_CBT_API_AIR_ERR,

    EN_DIAG_CBT_API_TRACE_OK,
    EN_DIAG_CBT_API_TRACE_ERR,
    EN_DIAG_CBT_API_TRACE_FILTER,
    EN_DIAG_CBT_API_TRACE_MATCH,

    EN_DIAG_CBT_API_USER_OK,
    EN_DIAG_CBT_API_USER_ERR,

    EN_DIAG_CBT_API_PACKET_ERR_REQ,

    EN_DIAG_CBT_API_TRANS_OK,
    EN_DIAG_CBT_API_TRANS_ERR,

    EN_DIAG_CBT_API_VOLTE_ERR,
    EN_DIAG_CBT_API_VOLTE_OK,

    EN_DIAG_DEBUG_CODE_PACKET_START,
    EN_DIAG_DEBUG_CODE_PACKET_START_ERROR,

    EN_DIAG_DEBUG_GET_SRC_BUF_START,
    EN_DIAG_DEBUG_GET_SRC_BUF_START_ERROR,

    EN_SDM_DIAG_DOT,
    EN_SDM_DIAG_DOT_ERR,
    EN_SDM_DIAG_DOT_OK,

    EN_DIAG_DEBUG_MSG,
    EN_DIAG_DEBUG_MSG_ERR,
    EN_DIAG_DEBUG_CONN_CFG,
    EN_DIAG_DEBUG_DIS_CONN_CFG,
    EN_DIAG_DEBUG_LAYER_CFG,
    EN_DIAG_DEBUG_PRINT_CFG,
    EN_DIAG_DEBUG_EVENT_CFG,
    EN_DIAG_DEBUG_AIR_CFG,
	EN_DIAG_DEBUG_USEPLANE_CFG,

    EN_DIAG_DEBUG_AGENT_INIT,
    EN_DIAG_DEBUG_AGENT_INIT_ERROR,
    EN_DIAG_DEBUG_AGENT_DISPATCH_CMD,
    EN_DIAG_DEBUG_REG_RD,
    EN_DIAG_DEBUG_REG_WR,
    EN_DIAG_DEBUG_BBP_LOG,
    EN_DIAG_DEBUG_BBP_SAMPLE,
    EN_DIAG_DEBUG_LTE_DSP_CNF,
    EN_DIAG_DEBUG_TDS_DSP_CNF,

    EN_DIAG_DEBUG_BBP_AGENT_TIME_OUT_ENTRY,
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
    /* DIAG APP SOCP投票 */
    EN_DIAG_APP_SOCP_VOTE,
    EN_DIAG_APP_SOCP_VOTE_ERR,
#endif
    /* DIAG AGENT与LDSP邮箱交互 */
    EN_DIAG_AGENT_LDSP_MB_MSG,
    EN_DIAG_DEBUG_INFO_MAX
} DIAG_CBT_ID_ENUM;

/*发起主动复位时MSP传入的参数ID最小值为:0xB000000*/
#define DIAG_BASE_ERROR_NUMBER          (0xB0000000)

enum MSP_SYSTEMERROR_MODID_ENUM
{
    DIAG_ERROR_MODID_BASE       = (0xB0000000),
    DIAG_CALLED_IN_IRQ          = DIAG_ERROR_MODID_BASE,
    DIAG_ERROR_MODID_OVERFLOW,
    DIAG_ERROR_MODID_BUTT       = (0xB0000010)
};

typedef struct
{
    VOS_UINT32 ulCalledNum;  /* 调用次数或者消息次数,或者表明该函数是否被调用*/
    VOS_UINT32 ulRserved1;
    VOS_UINT32 ulRserved2;
    VOS_UINT32 ulRserved3;
    VOS_UINT32 ulRtcTime;
} DIAG_CBT_INFO_TBL_STRU;

typedef struct
{
    VOS_CHAR                pucApiName[8];
    DIAG_CBT_ID_ENUM        ulOk;
    DIAG_CBT_ID_ENUM        ulErr;
    VOS_UINT32              ulSlice;
    VOS_UINT32              ulOkNum;
    VOS_UINT32              ulErrNum;
}DIAG_DEBUG_API_INFO_STRU;


extern VOS_VOID diag_CBT(DIAG_CBT_ID_ENUM ulType, VOS_UINT32 ulRserved1,
                        VOS_UINT32 ulRserved2, VOS_UINT32 ulRserved3);


/* LNR ***********************************************************************/

#define DIAG_LNR_NUMBER             (100)

typedef enum
{
    EN_DIAG_LNR_CMDID = 0,  /* 最后N条接收到的诊断命令 */

    EN_DIAG_LNR_LOG_LOST,   /* 最后N条log丢失的记录 */

    EN_DIAG_LNR_PS_TRANS,   /* 最后N条PS透传命令的记录 */

    EN_DIAG_LNR_CCORE_MSG,  /* 最后N条C核从A核收到的消息ID的记录 */

    EN_DIAG_LNR_MESSAGE_RPT,/* 最后N条通过message模块report上报的cmdid的记录 */

    EN_DIAG_LNR_TRANS_IND,  /* 最后N条透传上报的记录 */

    EN_DIAG_LNR_INFO_MAX
} DIAG_LNR_ID_ENUM;

typedef struct
{
    VOS_UINT32 ulCur;
    VOS_UINT32 ulRserved1[DIAG_LNR_NUMBER];
    VOS_UINT32 ulRserved2[DIAG_LNR_NUMBER];
} DIAG_LNR_INFO_TBL_STRU;


extern VOS_VOID diag_LNR(DIAG_LNR_ID_ENUM ulType, VOS_UINT32 ulRserved1, VOS_UINT32 ulRserved2);


/* DFR (Data Flow Record，码流录制)*******************************************/

#define     DIAG_DFR_NAME_MAX       (8)
#define     DIAG_DFR_BUFFER_MAX     (8*1024)
#define     DIAG_DFR_MAGIC_NUM      (0x44494147)    /* DIAG */

#define     DIAG_DFR_START_NUM      (0xabcd4321)

#define DFR_ALIGN_WITH_4BYTE(len)      (((len) + 3)&(~3))

typedef struct
{
    VOS_UINT32  ulMagicNum;                 /* 魔术字 */
    VOS_SEM     semid;                      /* 存储空间访问的互斥信号量 */
    VOS_CHAR    name[DIAG_DFR_NAME_MAX];    /* 存储码流的名字 */
    VOS_UINT32  ulCur;                      /* 存储空间的当前地址 */
    VOS_UINT32  ulLen;                      /* 存储空间的总长度 */
    VOS_UINT8   *pData;                     /* 存储空间的首地址 */
} DIAG_DFR_INFO_STRU;


typedef struct
{
    VOS_UINT32      ulStart;
    VOS_UINT32      ulTime;
}DIAG_DFR_HEADER_STRU;

/* throughput 吞吐率信息*******************************************/

#define     DIAG_THRPUT_DEBUG_NUM       (100)       /* 缓存100个点 */

#define     DIAG_THRPUT_DEBUG_LEN       (5*32768)   /* 每次统计吞吐率最少间隔5秒以上 */

typedef enum
{
    EN_DIAG_THRPUT_DATA_CHN_ENC = 0,    /* 数据通道编码输入端 */
#if (VOS_OS_VER == VOS_LINUX)
    EN_DIAG_THRPUT_DATA_CHN_PHY,        /* 数据通道写入物理通道 */

    EN_DIAG_THRPUT_DATA_CHN_CB,         /* 数据物理通道回调 */
#endif
    EN_DIAG_THRPUT_MAX
} DIAG_THRPUT_ID_ENUM;


typedef struct
{
    VOS_UINT32      ulSlice;            /* 当前时间戳时间戳 */
    VOS_UINT32      ulThroughput;       /* 吞吐率(Bytes/s) */
}DIAG_THRPUT_NODE_STRU;

typedef struct
{
    VOS_UINT32              ulSlice;            /* 最近一次统计的时间戳 */
    VOS_UINT32              ulBytes;            /* 当前已累计的字节数 */
    VOS_UINT32              ulMax;              /* 吞吐率峰值 */
    VOS_UINT32              ulPtr;              /* 当前指针 */
    DIAG_THRPUT_NODE_STRU   stNode[DIAG_THRPUT_DEBUG_NUM];
}DIAG_THRPUT_INFO_STRU;

/* DIAG MNTN *******************************************/

#define DIAG_DEBUG_LOST_LEN             (5*32768)

#define DIAG_DEBUG_MNTN_CMDID           (0x1)
#define DIAG_DEBUG_LOST_CMDID           (0x2)

typedef struct
{
    VOS_UINT32      ulModuleId;
    VOS_UINT32      ulNo;               /* 序号 */
    
    VOS_UINT32      ulTraceNum;         /* 层间消息成功上报次数 */
    VOS_UINT32      ulEventNum;         /* event成功上报次数 */
    VOS_UINT32      ulLogNum;           /* Log成功上报次数 */
    VOS_UINT32      ulAirNum;           /* 空口成功上报次数 */
    VOS_UINT32      ulTransNum;         /* 透传成功上报次数 */
    
    VOS_UINT32      ulThrputEnc;        /* 编码源吞吐率 */
    
    VOS_UINT32      ulThrputPhy;        /* 物理通道吞吐率 */
    VOS_UINT32      ulThrputCb;         /* 回调吞吐率 */

    VOS_UINT32      ulSrcChnSize;       /* 编码源通道剩余字节数 */
    VOS_UINT32      ulDstChnSize;       /* 编码目的通道剩余字节数 */

    VOS_UINT32      ulTotalSocpDstLen;  /* 从SOCP编码目的buffer中读取的总字节数 */

    VOS_UINT32      ulTotalUSBLen;      /* 向USB写入的总字节数 */
    VOS_UINT32      ulTotalUSBFreeLen;  /* USB回调释放的总字节数 */
    VOS_UINT32      ulTotalVCOMLen;     /* 向VCOM写入的总字节数 */
    VOS_UINT32      ulTotalVCOMErrLen;  /* 向VCOM写入失败的总字节数 */
    VOS_UINT32      ulVCOMMaxTimeLen;   /* 调用VCOM写接口话费的最大时长 */
    
    VOS_UINT32      ulTotalSOCKETLen;   /* 向SOCKET写入的总字节数 */

    VOS_UINT8       aucToolreserve[64]; /* 给工具预留的64个字节，用于在工具上显示工具的维测信息 */
}DIAG_MNTN_INFO_STRU;

typedef struct
{
    DIAG_FRAME_INFO_STRU                pstFrameInfo;
    DIAG_MNTN_INFO_STRU                 pstMntnInfo;
}DIAG_DEBUG_MNTN_STRU;


/* DIAG LOST *******************************************/

typedef enum
{
    EN_DIAG_LOST_ALLOC = 0,         /* 当前时间段内存申请失败次数 */

    EN_DIAG_LOST_SEND,              /* 当前时间段写源buffer失败次数 */

    EN_DIAG_LOST_BRANCH,            /* 当前时间段分支失败次数 */

    EN_DIAG_LOST_CPMWR,             /* 当前时间段CPM写失败次数 */

    EN_DIAG_LOST_CPMCB,             /* 当前时间段CPM写回调失败次数 */
    
    EN_DIAG_LOST_OVERFLOW,          /* 当前SOCP buffer溢出次数 */

    EN_DIAG_LOST_MAX
} DIAG_LOST_ID_ENUM;


typedef struct
{
    VOS_UINT32      ulModuleId;
    VOS_UINT32      ulNo;                   /* 序号 */
    
    VOS_UINT32      ulLostTotalNum;         /* 丢包总次数 */

    VOS_UINT32      aulCurFailNum[EN_DIAG_LOST_MAX];    /* 当前时间段内丢包的各类次数 */
    
    VOS_UINT32      ulSrcChnSize;       /* 编码源通道剩余字节数 */
    VOS_UINT32      ulDstChnSize;       /* 编码目的通道剩余字节数 */
    VOS_UINT32      ulDSPChnSize;       /* DSP编码源通道剩余字节数 */
    
    VOS_UINT32      ulThrputPhy;        /* 物理通道吞吐率 */
    VOS_UINT32      ulThrputCb;         /* 回调吞吐率 */

    VOS_UINT32      ulTotalSocpDstLen;  /* 从SOCP编码目的buffer中读取的总字节数 */

    VOS_UINT32      ulTotalUSBLen;      /* 向USB写入的总字节数 */
    VOS_UINT32      ulTotalUSBFreeLen;  /* USB回调释放的总字节数 */
    VOS_UINT32      ulTotalVCOMLen;     /* 向VCOM写入的总字节数 */
    VOS_UINT32      ulTotalVCOMErrLen;  /* 向VCOM写入失败的总字节数 */
    VOS_UINT32      ulVCOMMaxTimeLen;   /* 调用VCOM写接口话费的最大时长 */
    
    VOS_UINT32      ulTotalSOCKETLen;   /* 向SOCKET写入的总字节数 */

    VOS_UINT8       aucToolreserve[64]; /* 给工具预留的64个字节，用于在工具上显示工具的维测信息 */
}DIAG_LOST_INFO_STRU;

typedef struct
{
    DIAG_FRAME_INFO_STRU                pstFrameInfo;
    DIAG_LOST_INFO_STRU                 pstLostInfo;
}DIAG_DEBUG_LOST_STRU;


extern DIAG_DEBUG_LOST_STRU g_stLostInfo;

/* DIAG_TRACE *******************************************/

#define DIAG_DEBUG_TRACE_DELAY          (1*32768)
#define DIAG_DEBUG_TXT_LOG_DELAY        (10*32768)
#define DIAG_DEBUG_TXT_LOG_LENGTH       256
typedef struct
{
    VOS_UINT32      ulModuleId;
    VOS_UINT32      ulLevel;
    VOS_UINT32      ulSn;
    VOS_CHAR        pucData[DIAG_DEBUG_TXT_LOG_LENGTH];
}DIAG_DEBUG_INFO_STRU;

typedef struct
{
    DIAG_FRAME_INFO_STRU                pstFrameInfo;
    DIAG_DEBUG_INFO_STRU                pstInfo;
}DIAG_DEBUG_FRAME_STRU;

/* A核向C核发送的debug消息 *******************************************/

#define DIAG_DEBUG_DFR_BIT          0x00000001      /* 保存码流 */
#define DIAG_DEBUG_NIL_BIT          0x00000002      /* 保存log不上报的定位信息 */

typedef struct
{
    VOS_UINT32    ulSenderCpuId;
    VOS_UINT32    ulSenderPid;
    VOS_UINT32    ulReceiverCpuid;
    VOS_UINT32    ulReceiverPid;
    VOS_UINT32    ulLength;
    VOS_UINT32    ulMsgId;

    /* bit0 : DFR */
    /* bit1 : no ind log */
    VOS_UINT32      ulFlag;
} DIAG_A_DEBUG_C_REQ_STRU;


/* 对外函数接口 *******************************************/

extern VOS_UINT32 diag_CreateDFR(VOS_CHAR *name, VOS_UINT32 ulLen, DIAG_DFR_INFO_STRU *pDfr);
extern VOS_VOID diag_SaveDFR(DIAG_DFR_INFO_STRU *pDfr, VOS_UINT8 *pData, VOS_UINT32 ulLen);
extern VOS_VOID diag_GetDFR(DIAG_DFR_INFO_STRU *pDfr);
extern DIAG_CBT_INFO_TBL_STRU* diag_DebugGetInfo(VOS_VOID);
extern VOS_VOID DIAG_ShowLNR(DIAG_LNR_ID_ENUM ulType, VOS_UINT32 n);
extern VOS_VOID DIAG_ShowLogCfg(VOS_UINT32 ulModuleId);
extern VOS_VOID DIAG_ShowEventCfg(VOS_UINT32 ulpid);
extern VOS_VOID DIAG_ShowAirCfg(VOS_VOID);
extern VOS_VOID DIAG_ShowLayerCfg(VOS_UINT32 ulModuleId, VOS_UINT32 ulSrcDst);
extern VOS_VOID DIAG_ShowUsrCfg(VOS_VOID);
extern VOS_VOID DIAG_ShowLost(VOS_VOID);
extern VOS_VOID DIAG_ShowTrans(VOS_UINT32 n);
extern VOS_VOID DIAG_ShowPsTransCmd(VOS_UINT32 n);
extern VOS_UINT32 diag_DebugMsgProc(MsgBlock* pMsgBlock);
extern VOS_VOID DIAG_DebugDFR(VOS_VOID);
extern VOS_VOID diag_ThroughputSave(DIAG_THRPUT_ID_ENUM enChn, VOS_UINT32 bytes);
extern VOS_VOID DIAG_ShowThroughput(VOS_UINT32 ulIndex);
extern VOS_VOID DIAG_DebugEventReport(VOS_UINT32 ulpid);
extern VOS_VOID DIAG_DebugLayerReport(VOS_VOID);
extern VOS_VOID DIAG_DebugLogReport(VOS_UINT32 ulpid, VOS_UINT32 level);
extern VOS_VOID DIAG_DebugTransReport(VOS_UINT32 ulpid);
extern VOS_VOID DIAG_DebugLayerCfg(VOS_UINT32 ulModuleId, VOS_UINT8 ucFlag);
extern VOS_VOID diag_ReportMntn(VOS_VOID);
extern VOS_VOID diag_ReportLost(DIAG_LOST_ID_ENUM enLostId);

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of diag_Debug.h */

