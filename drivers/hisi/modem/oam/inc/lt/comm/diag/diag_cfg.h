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


#ifndef __DIAG_CFG_H__
#define __DIAG_CFG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "VosPidDef.h"
#include  "msp_nv_def.h"
#include  "msp_diag.h"
#include  "diag_common.h"

#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/

#define DIAG_CFG_PID_NUM                        (VOS_PID_BUTT - VOS_PID_DOPRAEND)

#define DIAG_CFG_MODULE_IS_VALID(ulModuleId)    ((ulModuleId < VOS_PID_BUTT)&&(ulModuleId >= VOS_PID_DOPRAEND))
#define DIAG_CFG_MODULE_IS_INVALID(ulModuleId)  ((ulModuleId >= VOS_PID_BUTT)||(ulModuleId < VOS_PID_DOPRAEND))

/*层间消息模块ID合法性检查*/
#define DIAG_CFG_LAYER_MODULE_IS_ACORE(ulModuleId) ((ulModuleId >= VOS_PID_CPU_ID_1_DOPRAEND)&&(ulModuleId < VOS_CPU_ID_1_PID_BUTT))
#define DIAG_CFG_LAYER_MODULE_IS_CCORE(ulModuleId) ((ulModuleId >= VOS_PID_CPU_ID_0_DOPRAEND)&&(ulModuleId < VOS_CPU_ID_0_PID_BUTT))

#define DIAG_CFG_LAYER_MODULE_ACORE_OFFSET(ulModuleId)  (ulModuleId - VOS_PID_CPU_ID_1_DOPRAEND)
#define DIAG_CFG_LAYER_MODULE_CCORE_OFFSET(ulModuleId)  (ulModuleId - VOS_PID_CPU_ID_0_DOPRAEND)


/* DIAG已初始化 */
#define DIAG_CFG_INIT                0x00000001

/* HSO已连接 */
#define DIAG_CFG_CONN                0x00000002

/* LT空口消息已打开 */
#define DIAG_CFG_LT_AIR              0x00000004

/* GU空口消息已打开 */
#define DIAG_CFG_GU_AIR              0x00000008

/* 用户面开关已打开 */
#define DIAG_CFG_EVT                 0x00000010

#define DIAG_CMD_DATA_MAX_LEN                       (4096)

#define DIAG_CFG_CAT_CFG_NUM                        (50)

#define DIAG_CMD_CFG_SWT_CLOSE                      (0x00000000)
#define DIAG_CMD_CFG_SWT_OPEN                       (0x80000000)

#define DIAG_GET_PRINT_CFG_SWT(swt)                 (swt>>24)

#define DIAG_GET_CFG_SWT(swt)   ((DIAG_CMD_CFG_SWT_OPEN == swt) ? DIAG_CFG_SWT_OPEN : DIAG_CFG_SWT_CLOSE )

#define DIAG_EVENT_MODID(id)    (id & 0x7fffffff)   /* 低31 bits是PID */
#define DIAG_EVENT_SWT(id)      (id >> 31)          /* 最高bit是开关 */

#define DIAG_CFG_PRINT_TOTAL_MODULE_SWT_NOT_USE     (0xFFFFFFFF)
#define DIAG_CFG_PRINT_TOTAL_MODULE                 (0xFFFFFFFF)

/* 层间消息模块类型定义*/
#define DIAG_CMD_LAYER_MOD_SRC                      (0)
#define DIAG_CMD_LAYER_MOD_DST                      (1)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum ENUM_DIAG_CFG_BIT
{
    DIAG_CFG_INIT_BIT     = 0,
    DIAG_CFG_CONN_BIT,
    DIAG_CFG_LT_AIR_BIT,
    DIAG_CFG_GU_AIR_BIT,
    DIAG_CFG_EVENT_BIT,
    DIAG_CFG_BIT_BUTT
};
typedef VOS_UINT32 ENUM_DIAG_CFG_BIT_U32 ;

/*层间、空口、用户面数据的开关采用如下宏定义，注意由U32改成U8*/
enum ENUM_DIAG_CFG_SWT
{
    DIAG_CFG_SWT_CLOSE  = 0,
    DIAG_CFG_SWT_OPEN,
    DIAG_CFG_SWT_BUTT
};
typedef VOS_UINT8 ENUM_DIAG_CFG_SWT_U8;

typedef enum
{
    SYSVIEW_MEM_TRACE       = 1,
    SYSVIEW_CPU_INFO        = 2,
    SYSVIEW_TASK_INFO       = 3,
    SYSVIEW_INT_LOCK_INFO   = 4,
    SYSVIEW_SWT_ALL         = 0xff,
    SYSVIEW_SWT_MAX         /* 边界值 */
} BSP_SYSVIEW_TYPE_E;


/*****************************************************************************
   5 STRUCT
*****************************************************************************/


/*****************************************************************************
 描述 : HSO连接UE设备
ID   : DIAG_CMD_HOST_CONNECT
REQ  : DIAG_CMD_HOST_CONNECT_REQ_STRU
CNF  : DIAG_CMD_HOST_CONNECT_CNF_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulMajorMinorVersion; /* 主版本号.次版本号*/
    VOS_UINT32 ulRevisionVersion;   /* 修正版本号*/
    VOS_UINT32 ulBuildVersion;      /* 内部版本号*/
} DIAG_CMD_UE_SOFT_VERSION_STRU;

typedef struct
{
    VOS_UINT16 usVVerNo;           /* V部分*/
    VOS_UINT16 usRVerNo;           /* R部分*/
    VOS_UINT16 usCVerNo;           /* C部分*/
    VOS_UINT16 usBVerNo;           /* B部分*/
    VOS_UINT16 usSpcNo;            /* SPC部分*/
    VOS_UINT16 usHardwareVerNo;    /* 硬件PCB号和印制板版本号*/
    VOS_UINT32 ulProductNo;        /* 产品类型编号，即不同外设组合的硬件平台*/
} DIAG_CMD_UE_BUILD_VER_STRU; /* 内部版本*/

typedef struct
{
    /* 010: OM通道融合的版本        */
    /* 110: OM融合GU未融合的版本    */
    /* 100: OM完全融合的版本        */
    VOS_UINT32  ulDrxControlFlag:1; /* DRX部分*/
    VOS_UINT32  ulPortFlag      :1; /* OM Port flag 0:old,1:new */
    VOS_UINT32  ulOmUnifyFlag   :1; /* OM */
    VOS_UINT32  ulReserved      :29;
}DIAG_CONTROLFLAG_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;          /* 原AUID*/
    VOS_UINT32 ulSn;            /* HSO分发，插件命令管理*/

    VOS_UINT32 ulRc;            /* 结果码*/
    VOS_CHAR szImei[16];
    DIAG_CMD_UE_SOFT_VERSION_STRU stUeSoftVersion;
    DIAG_CMD_UE_BUILD_VER_STRU stBuildVersion;
    VOS_UINT32 ulChipBaseAddr;
    union
    {
        VOS_UINT32              UintValue;
        DIAG_CONTROLFLAG_STRU   CtrlFlag;
    } diag_cfg;/* B135新增，标示低功耗特性版本: 1:低功耗版本；0：正常版本；0xFFFFFFFF:MSP读取NV项失败，HSO会认为连接不成功并给出提示，要求重新进行连接*/
    VOS_UINT32 ulLpdMode;
    NV_ITEM_AGENT_FLAG_STRU stAgentFlag;
    VOS_CHAR szProduct[64];
} DIAG_CMD_HOST_CONNECT_CNF_STRU;

/* 断开连接 */
typedef struct
{
    VOS_UINT32 ulAuid;          /* 原AUID*/
    VOS_UINT32 ulSn;            /* HSO分发，插件命令管理*/
    VOS_UINT32 ulRc;            /* 结果码*/
} DIAG_CMD_HOST_DISCONNECT_CNF_STRU;


/* disconnect 通知结构体 */
typedef struct
{
    VOS_UINT32                  ulRsv;
} DIAG_MSG_TO_OTHERCPU_DISCONN_STRU;

/*****************************************************************************
 描述 : 针对模块的打印开关命令,支持多个命令参数
ID   : DIAG_CMD_REPLAY_SET_CNF_STRU
REQ : DIAG_CMD_REPLAY_SET_REQ_STRU
CNF : DIAG_CMD_REPLAY_SET_CNF_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulReserved;/*保留*/
} DIAG_CMD_REPLAY_SET_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;          /* 原AUID*/
    VOS_UINT32 ulSn;            /* HSO分发，插件命令管理*/
    VOS_UINT32 ulRet;
} DIAG_CMD_REPLAY_SET_CNF_STRU;


/*****************************************************************************
 描述 : 针对模块的打印开关命令,支持多个命令参数
ID   : DIAG_CMD_LOG_CAT_PRINT
REQ : DIAG_CMD_LOG_CAT_PRINT_REQ_STRU
CNF : DIAG_CMD_LOG_CAT_PRINT_CNF_STRU
IND : DIAG_CMD_LOG_PRINT_RAW_TXT_IND_STRU
*****************************************************************************/

typedef struct
{
    VOS_UINT32 ulModuleId;      /* 如果为0xFFFFFFFF表示为所有模块的Level开关*/
    VOS_UINT32 ulLevelFilter;   /* (0|ERROR|WARNING|NORMAL|INFO|0|0|0) 1:OPEN, 0:CLOSE*/
} DIAG_CMD_LOG_CAT_PRINT_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;          /* 原AUID*/
    VOS_UINT32 ulSn;            /* HSO分发，插件命令管理*/
    VOS_UINT32 ulRc;            /* 结果码*/
    VOS_UINT32 ulModuleId;
} DIAG_CMD_LOG_CAT_PRINT_CNF_STRU;

/*****************************************************************************
描述 : 针对模块的层间开关,支持多个命令参数
ID   : DIAG_CMD_LOG_CAT_LAYER
REQ : DIAG_CMD_LOG_CAT_LAYER_REQ_STRU
CNF : DIAG_CMD_LOG_CAT_LAYER_CNF_STRU
说明: 如果多包命令参数的情况，一个模块错误，就会返回失败，但是正确的模块参数依然会存储
IND : DIAG_CMD_LOG_LAYER_IND_STRU
*****************************************************************************/

typedef struct
{
    VOS_UINT32 ulModuleId;       /* 模块ID*/
    VOS_UINT32 ulIsDestModule;   /* 0: 表示Source Module， 1：表示Dest Module*/
    VOS_UINT32 ulSwitch;         /* (0x00000000): 关；(0x80000000)：开*/
} DIAG_CMD_LOG_CAT_LAYER_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;          /* 原AUID*/
    VOS_UINT32 ulSn;            /* HSO分发，插件命令管理*/
    VOS_UINT32 ulRc;            /* 结果码*/
    VOS_UINT32 ulModuleId;
} DIAG_CMD_LOG_CAT_LAYER_CNF_STRU;

/*****************************************************************************
描述 : 针对AIR的总开关,支持多个命令参数
ID   : DIAG_CMD_LOG_CAT_AIR
REQ : DIAG_CMD_LOG_CAT_AIR_REQ_STRU
CNF : DIAG_CMD_LOG_CAT_AIR_CNF_STRU
IND : DIAG_CMD_LOG_AIR_IND_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulSwitch;        /* (0x00000000): 关；(0x80000000)：开*/
    VOS_UINT32 ulGuSwitch;      /*  1开，0关*/
} DIAG_CMD_LOG_CAT_AIR_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;          /* 原AUID*/
    VOS_UINT32 ulSn;            /* HSO分发，插件命令管理*/
    VOS_UINT32 ulRc;            /* 结果码*/
} DIAG_CMD_LOG_CAT_AIR_CNF_STRU;

/*****************************************************************************
描述 : 针对EVENT的总开关,支持多个命令参数
ID   : DIAG_CMD_LOG_CAT_EVENT
REQ : DIAG_CMD_LOG_CAT_EVENT_REQ_STRU
CNF : DIAG_CMD_LOG_CAT_EVENT_CNF_STRU
IND : DIAG_CMD_LOG_EVENT_IND_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulSwt;
    VOS_UINT32 ulCount;
    VOS_UINT32 aulModuleId[0];
} DIAG_CMD_LOG_CAT_EVENT_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;          /* 原AUID*/
    VOS_UINT32 ulSn;            /* HSO分发，插件命令管理*/
    VOS_UINT32 ulRc;            /* 结果码*/
} DIAG_CMD_LOG_CAT_EVENT_CNF_STRU;

/*****************************************************************************
描述 : 针对消息ID/命令ID开关,支持多个命令参数
ID   : DIAG_CMD_LOG_CAT_CFG
REQ : DIAG_CMD_LOG_CAT_CFG_REQ_STRU
CNF : DIAG_CMD_LOG_CAT_CFG_CNF_STRU
说明:   如果多包命令参数的情况，一包MSG ID错误，就会返回失败,但是正确的参数依然会存储;
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulId;            /* 消息ID/命令ID*/
    VOS_UINT32 ulCategory;      /* 取值为 DIAG_CMD_LOG_CATETORY_XXX*/
    VOS_UINT32 ulSwitch;
} DIAG_CMD_LOG_CAT_CFG_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;          /* 原AUID*/
    VOS_UINT32 ulSn;            /* HSO分发，插件命令管理*/
    VOS_UINT32 ulRc;            /* 结果码*/
    VOS_UINT32 ulId;            /* 消息ID/命令ID*/
} DIAG_CMD_LOG_CAT_CFG_CNF_STRU;



typedef struct
{
    VOS_UINT32 ulId;           // 消息ID
    VOS_UINT32 ulSwt;
}DIAG_CFG_LOG_CAT_MSG_CFG_STRU;

typedef struct
{
    VOS_UINT32 ulCatId;
    VOS_UINT32 ulCfgCnt;
    DIAG_CFG_LOG_CAT_MSG_CFG_STRU astMsgCfgList[DIAG_CFG_CAT_CFG_NUM];
}DIAG_CFG_LOG_CAT_CFG_STRU;

/*****************************************************************************
描述 : 针对获取时间戳的参数
CNF : DIAG_TIMESTAMP_CNF_STRU
*****************************************************************************/

typedef struct
{
    VOS_UINT32  ulAuid;                     /* 原AUID*/
    VOS_UINT32  ulSn;                       /* HSO分发，插件命令管理*/
    VOS_UINT    ulErrcode;                  /* 0:成功 1:64位时间戳获取失败 2:32位时间戳获取失败*/
    VOS_UINT    ulGuTimeStampInitValue;     /* 32位时间戳 */
    VOS_UINT64  ulTLTimeStampInitValue;     /* 64位时间戳 */
}DIAG_TIMESTAMP_CNF_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_UINT32 g_ulDiagCfgInfo;

extern VOS_UINT8 g_ALayerSrcModuleCfg[VOS_CPU_ID_1_PID_BUTT - VOS_PID_CPU_ID_1_DOPRAEND];
extern VOS_UINT8 g_CLayerSrcModuleCfg[VOS_CPU_ID_0_PID_BUTT - VOS_PID_CPU_ID_0_DOPRAEND];
extern VOS_UINT8 g_ALayerDstModuleCfg[VOS_CPU_ID_1_PID_BUTT - VOS_PID_CPU_ID_1_DOPRAEND];
extern VOS_UINT8 g_CLayerDstModuleCfg[VOS_CPU_ID_0_PID_BUTT - VOS_PID_CPU_ID_0_DOPRAEND];

extern VOS_UINT8 g_PrintModuleCfg[DIAG_CFG_PID_NUM];
extern VOS_UINT32 g_PrintTotalCfg;
extern DIAG_CFG_LOG_CAT_CFG_STRU g_stMsgCfg;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/


extern VOS_VOID diag_CfgResetAllSwt(VOS_VOID);
extern VOS_UINT32 diag_CfgSetGlobalBitValue(VOS_UINT32* pstDiagGlobal,ENUM_DIAG_CFG_BIT_U32 enBit,ENUM_DIAG_CFG_SWT_U8 enSwtich);
extern VOS_UINT32 diag_CfgSetLayerSwt(DIAG_CMD_LOG_CAT_LAYER_REQ_STRU* pstLayerReq, VOS_UINT32 ulCfgSize);
extern VOS_UINT32 diag_CfgSetMsgSwt(DIAG_CMD_LOG_CAT_CFG_REQ_STRU *pstCatCfgReq,VOS_UINT32 ulCfgSize);
extern VOS_UINT32 diag_CfgSetPrintSwt(DIAG_CMD_LOG_CAT_PRINT_REQ_STRU* pstPrintReq, VOS_UINT32 ulCfgSize);
extern VOS_UINT32 diag_ConnProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_GetTimeStampInitValue(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_GetModemNum(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_DisConnProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_DisConnNotifyOtherCpu(VOS_VOID);
extern VOS_UINT32 diag_EventCfgProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_LayerCfgProc (VOS_UINT8* pstReq);
extern VOS_UINT32 diag_MsgCfgProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_PrintCfgProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_UsrPlaneCfgProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_AirCfgProc (VOS_UINT8* pstReq);
extern VOS_VOID diag_AppAgentTimeOutProcEntry(VOS_VOID* pstPara);
extern VOS_VOID diag_BbpEnableSocpChan(VOS_VOID);


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

#endif /* end of diag_cfg.h */

