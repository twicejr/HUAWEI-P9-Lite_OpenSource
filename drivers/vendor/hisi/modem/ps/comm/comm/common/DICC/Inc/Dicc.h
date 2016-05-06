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

#ifndef __DICC_H__
#define __DICC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/******************************************************************************
  1 其他头文件包含
******************************************************************************/
#include "TTFLink.h"
#include "TTFComm.h"
#include "DiccInterface.h"

#if( FEATURE_ON == FEATURE_CSD )

/******************************************************************************
  2 宏定义
******************************************************************************/
/*
注意DICC内存是按照前来初始化的通道顺序组织的, 并不一定是按照通道ID进行组织
*/
/************** DICC mem() begin **************
  ->startAddr|                                               |
             |            DICC总控制结构DICC Ctrl            |
             |-----------------------------------------------|
             |   第一个初始化的通道的控制结构(channel ctrl)  |
             |-----------------------------------------------|
             |   第二个初始化的通道的控制结构(channel ctrl)  |
             |-----------------------------------------------|
             |   第三个初始化的通道的控制结构(channel ctrl)  |
             |-----------------------------------------------|
             |   第四个初始化的通道的控制结构(channel ctrl)  |    各通道结点个数由用户配置, 可以一样, 也可以不一样, 即可以 n != m != k != j, 但是结点结构相同
             |-----------------------------------------------|       |---------------------------------------------------|-----|------------------------|
             |        第一个初始化的通道的 ring queue        |  ===> |      queue node_1 *      |     queue node_2 *     | ... |     queue node_n *     |
             |-----------------------------------------------|       |---------------------------------------------------|-----|------------------------|
             |        第一个初始化的通道的 queue data        |  ===> |       queue node_1       |      queue node_2      | ... |      queue node_n      |
             |-----------------------------------------------|       |--------------------------|------------------------|-----|------------------------|
             |        第二个初始化的通道的 ring queue        |  ===> |      queue node_1 *      |     queue node_2 *     | ... |     queue node_m *     |
             |-----------------------------------------------|       |---------------------------------------------------|-----|------------------------|
             |        第二个初始化的通道的 queue data        |  ===> |       queue node_1       |      queue node_2      | ... |      queue node_m      |
             |-----------------------------------------------|       |--------------------------|------------------------|-----|------------------------|
             |        第三个初始化的通道的 ring queue        |  ===> |      queue node_1 *      |     queue node_2 *     | ... |     queue node_k *     |
             |-----------------------------------------------|       |---------------------------------------------------|-----|------------------------|
             |        第三个初始化的通道的 queue data        |  ===> |       queue node_1       |      queue node_2      | ... |      queue node_k      |
             |-----------------------------------------------|       |--------------------------|------------------------|-----|------------------------|
             |        第四个初始化的通道的 ring queue        |  ===> |      queue node_1 *      |     queue node_2 *     | ... |     queue node_j *     |
             |-----------------------------------------------|       |---------------------------------------------------|-----|------------------------|
             |        第四个初始化的通道的 queue data        |  ===> |       queue node_1       |      queue node_2      | ... |      queue node_j      |
             |-----------------------------------------------|       |--------------------------|------------------------|-----|------------------------|
 **************** DICC mem end ****************/


#define DICC_MEM_INIT_MAGIC_NUM                             (0x1D2D3D4D)                    /* DICC同步魔术字 */
/* 用于防止数据被篡改的魔术字, 其值固定为0xACAC */
#define DICC_MAGIC_NUM_VALUE                                (0xACAC)

#define DICC_MEMORY_TOTAL_SIZE                              (DICC_QUEUE_MEM_SIZE)   /* 核间通信内存, 单位: 字节 */

#define DICC_MAX_SENDER_NUM_PER_CPU                         (2)       /* 各CPU上充当通道sender端的通道个数 */
#define DICC_MAX_RECVER_NUM_PER_CPU                         (2)       /* 各CPU上充当通道recver端的通道个数 */

#define DICC_SERVICE_TYPE_NUM_PER_CPU                       (2)                         /* 各CPU上 服务类型种数 */

/* 最大支持打印DICC通道数据的字节数 */
#define DICC_DEBUG_PRINT_MAX_LEN                            (128)

/* 用于定位的最大trace的数据块 */
#define DICC_MAX_TRACE_QUEUE_DATA_CNT                       (10)

/* DICC Interupt */
#define DICC_SERVICE_0_INT_LEVEL                            (IPC_INT_DICC_USRDATA)       /* 核间数据面通道中断向量号(数据到达通知中断) */
#define DICC_SERVICE_1_INT_LEVEL                            (IPC_INT_DICC_RELDATA)       /* 核间数据面通道中断向量号(内存释放通知中断) */

/* DICC channel state and mask */
#define DICC_CHAN_BOTH_CLOSE_MASK                           (0x00)     /* 通道两端都关闭 */
#define DICC_CHAN_SENDER_OPEN_MASK                          (0x01)    /* 通道仅发送端打开 */
#define DICC_CHAN_RECVER_OPEN_MASK                          (0x02)    /* 通道仅接收端打开 */
#define DICC_CHAN_BOTH_OPEN_MASK                            ((DICC_CHAN_SENDER_OPEN_MASK) | (DICC_CHAN_RECVER_OPEN_MASK))    /* 通道两端都打开 */

/* 判断DICC通道是否一直处于满状态, 无外部使用者读取的场景, 此时说明外部使用者出现异常, 进行单板复位, 暂定1s
   使用32K时钟来计数, 1s = 1*32K slice = 32768 slice */
#define DICC_CHAN_QUEUE_FULL_TIME                           (32768)

/* DICC通道一旦出现满状态, 就会计数, 当出现下面这么多次后, 则上报SDT一次 */
#define DICC_CHAN_QUEUE_FULL_REPORT_TIMES                   (50)

#define TTF_SOFT_REBOOT_MODULE_ID_DICC_CHAN_ALWAYS_FULL     (0x30000000)    /* DICC因为通道数据一直满而产生软复位的复位module-id */
#define TTF_SOFT_REBOOT_MODULE_ID_DICC_CHAN_INIT_FAIL       (0x30000001)    /* DICC因为通道初始化失败而产生软复位的复位module-id */
#define TTF_SOFT_REBOOT_MODULE_ID_DICC_MEM_CLEAN_SYNC_FAIL  (0x30000002)    /* DICC因为通道内存初始化失败而产生软复位的复位module-id */


/* DICC打印使用的module-id */
#define MODULE_DICC_LOG_ID                                  (0x8200)

/* 设置中断操作记录的宏 */
#define SET_ISR_RECORD(pstIsrRecord, Pid, ServiceType, IsrOp, OpResult)\
                                                    {\
                                                        (pstIsrRecord)->ulPid         = (Pid);\
                                                        (pstIsrRecord)->enServiceType = (ServiceType);\
                                                        (pstIsrRecord)->enIsrOp       = (IsrOp);\
                                                        (pstIsrRecord)->enOpResult    = (OpResult);\
                                                    }

/* 获取DICC管理结构DFx的内存地址 */
#define DICC_GET_CHAN_DFX(pastDICCMgmt)             ((DICC_DFX_STRU *)(&((pastDICCMgmt)->stDFx)))

/* DICC自旋锁, 基于IPC实现 */
#define DICC_SPIN_LOCK()                            (mdrv_ipc_spin_lock(IPC_SEM_DICC))
#define DICC_SPIN_UNLOCK()                          (mdrv_ipc_spin_unlock(IPC_SEM_DICC))

/* TRACE路径功能引入的宏 */
#define DICC_TRACE_OK                               (DICC_OK)

/* 设置跟踪函数执行步骤的宏, TRACE默认打开, 建议仅在单板启动阶段使用, 以减少调试对性能的损失 */
#define SET_DICC_TRACE_INFO_RECORD(pstTrace, CpuId, Pid, FuncId, LineNo, OpResult)\
                                                    {\
                                                        (pstTrace)->enCpuId           = (CpuId);\
                                                        (pstTrace)->ulPid             = (Pid);\
                                                        (pstTrace)->enFuncId          = (FuncId);\
                                                        (pstTrace)->ulLine            = (LineNo);\
                                                        (pstTrace)->enResult          = (OpResult);\
                                                    }

/* 设置软复位基本信息 */
#define SET_DICC_SOFT_REBOOT_INFO(pstRebootInfo, Module, FuncId, LineNo, pUserDataStart, UserDataLen)\
                                                    {\
                                                        (pstRebootInfo)->ulModule     = (Module);\
                                                        (pstRebootInfo)->ulFile       = (FuncId);\
                                                        (pstRebootInfo)->ulLine       = (LineNo);\
                                                        (pstRebootInfo)->pucData      = (VOS_UINT8 *)(pUserDataStart);\
                                                        (pstRebootInfo)->ulDataLen    = (UserDataLen);\
                                                    }

#define DICC_MUTEX_SEM_NOT_CREATE   0
#define DICC_MUTEX_SEM_CREATED      1

/******************************************************************************
  3 枚举定义
******************************************************************************/
/* 记录某个通道是否已经被初始化的枚举 */
enum DICC_CHAN_INIT_STATUS_ENUM
{
    DICC_CHAN_STATUS_NOT_INITIALED                   = 0,            /* The channel is not initialed */
    DICC_CHAN_STATUS_INITIALED                       = 1,            /* The channel is already initialed */

    DICC_CHAN_STATUS_BUTT
};
typedef VOS_UINT8 DICC_CHAN_INIT_STATUS_ENUM_UINT8;

/* DICC中断使能/去使能枚举 */
enum DICC_SERVICE_ISR_OP_ENUM
{
    DICC_SERVICE_ISR_ENABLE                           = 0,            /* enable interrupt */
    DICC_SERVICE_ISR_DISABLE                          = 1,            /* disable interrupt */

    DICC_SERVICE_STATUS_BUTT
};
typedef VOS_UINT8 DICC_SERVICE_ISR_OP_ENUM_UINT8;

/* DICC通道上报事件 */
enum DICC_MNTN_EVENT_ID_ENUM
{
    ID_DICC_MNTN_CLOSE_FLUSH_EVENT                  = 0x0001,         /* _H2ASN_MsgChoice DICC_CHAN_CLOSE_FLUSH_EVENT_STRU */
    ID_DICC_MNTN_MAGIC_NUM_CHANGED_EVENT            = 0x0002,         /* _H2ASN_MsgChoice DICC_CHAN_MAGIC_NUM_CHANGED_EVENT_STRU */
    ID_DICC_MNTN_QUEUE_FULL_EVENT                   = 0x0003,         /* _H2ASN_MsgChoice DICC_CHAN_QUEUE_FULL_EVENT_STRU */

    ID_DICC_MNTN_EVENT_TYPE_BUTT
};
typedef VOS_UINT16 DICC_MNTN_EVENT_ID_ENUM_UINT16;

/* DICC定位文件标号, 对要定位的函数定义出一个标号,
   易出现问题的函数是单板启动阶段, 由于是此阶段死机,
   串口通常无法用LOG输出, 打印偶尔会有延迟, 看不到 */
enum DICC_TRACE_FUNC_MARK_ID_ENUM
{
    ID_DICC_TRACE_FUNC_BEGIN                        = 0,    /* 因全局变量初始化为0 */
    ID_DICC_TRACE_FUNC_MARK_SYNC                    = 1,
    ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT        = 2,
    ID_DICC_TRACE_FUNC_MARK_OPEN                    = 3,
    ID_DICC_TRACE_FUNC_MARK_CLOSE                   = 4,

    ID_DICC_TRACE_FUNC_MARK_BUTT
};
typedef VOS_UINT8 DICC_TRACE_FUNC_MARK_ID_ENUM_UINT8;

/******************************************************************************
  4 全局变量声明
******************************************************************************/


/******************************************************************************
  5 消息头定义
******************************************************************************/


/******************************************************************************
  6 消息定义
******************************************************************************/


/******************************************************************************
  7 STRUCT定义
******************************************************************************/
#pragma pack(4)

/* 外部用户误操作中断的记录结构 */
typedef struct
{
    VOS_UINT32                      ulInvalidDisableOpPid;                                 /* 误操作中断的PID */
    VOS_UINT32                      ulInvalidDisableOpTime;                                /* 误操作中断的slice */
    VOS_UINT32                      ulInvalidEnableOpPid;                                  /* 误操作中断的PID */
    VOS_UINT32                      ulInvalidEnableOpTime;                                 /* 误操作中断的slice */
} DICC_ISR_DEBUG_STRU;

/* 外部用户正确操作中断的记录结构 */
typedef struct
{
    VOS_UINT32                      ulDisableOpPid;                              /* 操作中断的PID */
    VOS_UINT32                      ulDisableOpTime;                             /* 操作中断的slice */
    VOS_UINT32                      ulDisableCnt;                                /* 操作次数 */
    VOS_UINT32                      ulEnableOpPid;                               /* 操作中断的PID */
    VOS_UINT32                      ulEnableOpTime;                              /* 操作中断的slice */
    VOS_UINT32                      ulEnableCnt;                                 /* 操作次数 */
} DICC_ISR_OP_STRU;

/* 硬件信号量操作记录 */
typedef struct
{
    VOS_UINT32                          ulSingnalNum;       /* 硬件信号量编号 */
    VOS_INT32                           lTimeout;           /* 获取信号量等待时间 */
    VOS_INT32                           lResult;            /* 硬件信号量操作结果 */
} DICC_CHAN_HW_SEM_PAPA_STRU;

/* 本地信号量操作记录 */
typedef struct
{
    VOS_UINT32                          ulResult;            /* 信号量操作结果 */
} DICC_CHAN_LOCAL_SEM_PAPA_STRU;

/* 外部用户误操作通道的记录结构 */
typedef struct
{
    VOS_UINT32                  ulOpPid;                                        /* 误操作通道的PID */
    VOS_UINT32                  ulOpTime;                                       /* 误操作通道的slice */
} DICC_CHAN_DEBUG_STRU;

/* 用于核间数据通道统计计数的结构 */
typedef struct
{
    VOS_UINT32                  ulInsertPid;                                    /* Insert操作PID */
    VOS_UINT32                  ulInsertCnt;                                    /* 插入次数 */
    VOS_UINT32                  ulQueueFullCnt;                                 /* 插入出现队列满次数 */
    VOS_UINT32                  ulConsecutiveQueueFullCnt;                      /* 插入时连续出现队列满计数, 不连续时清零 */
    VOS_UINT32                  ulLastInsertTime;                               /* 最后一次插入数据的时间, 单位: slice */
    VOS_UINT32                  ulRemovePid;                                    /* Remove操作PID */
    VOS_UINT32                  ulRemoveCnt;                                    /* 移出次数 */
    VOS_UINT32                  ulLastRemoveTime;                               /* 最后一次移出数据的时间, 单位: slice */
    VOS_UINT32                  ulTrigIsrPid;                                   /* 触发中断操作PID */
    VOS_UINT32                  ulTrigIsrCnt;                                   /* 触发中断次数 */
    VOS_UINT32                  ulLastTrigIsrTime;                              /* 最后一次触发中断数据的时间, 单位: slice */
} DICC_CHAN_STATISTICS_STRU;

/* 定位时, 用于导出通道数据内容的结构 */
typedef struct
{
    VOS_UINT32                  ulInsertTime;                                   /* 插入数据的时间, 单位: slice */
    VOS_UINT8                   ucPriDataLen;                                   /* 待传递的信息内容长度, 单位: 字节 */
    VOS_UINT8                   aucReserve[3];
    VOS_UINT8                   aucPriData[DICC_INFO_BLOCK_MAX_LEN];            /* 待传递的信息内容 */
} DICC_TRACE_QUEUE_DATA_STRU;

/* 定位时, 用于导出通道数据的结构 */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChanId;                                       /* 通道ID */
    VOS_UINT8                           ucDataCnt;                                      /* 通道中trace数据的块数 */
    VOS_UINT8                           aucReserve[2];
    DICC_TRACE_QUEUE_DATA_STRU          astQueueData[DICC_MAX_TRACE_QUEUE_DATA_CNT];    /* 通道中前十块数据 */
} DICC_TRACE_QUEUE_STRU;

/* 通道状态记录 */
typedef struct
{
    DICC_ISR_OP_STRU                    stIsrOp;        /* 正确操作中断的记录 */
    DICC_CHAN_STATISTICS_STRU           stStatistics;       /* 通道统计信息 */
} DICC_CHAN_STATUS_STRU;

/* DICC DFx结构 */
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enDFxEnabled;                           /* DFx功能使能与否: TRUE表示使能, FALSE表示未使能, 未使能则不能记录 */
    VOS_UINT8                           aucReserve[3];
    DICC_CHAN_STATUS_STRU               astChanStatus[DICC_MAX_CHAN_NUM];       /* 通道状态记录 */
    DICC_ISR_DEBUG_STRU                 stIsrDbg;                               /* 误操作中断的记录(不区分核, 只记录最近一次) */
} DICC_DFX_STRU;

/* 核间内存所有通道管理控制结构 */
typedef struct
{
    VOS_UINT32                  ulCurrSize;                                  /* 核间当前使用的内存大小, 单位: 字节 */
    DICC_DFX_STRU               stDFx;
} DICC_CTRL_STRU;

/* 核间数据通道管理控制结构 */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChanId;                            /* 通道ID */
    VOS_UINT8                           ucStateMask;                         /* 标记通道两端打开或者关闭状态 */
    DICC_CHAN_INIT_STATUS_ENUM_UINT8    enValidFlag;                         /* 标记通道是否已经初始化, 1为初始化; 0为未初始化 */
    VOS_UINT8                           ucPriDataLen;                        /* 用户私有数据长度, 单位: 字节 */
    VOS_UINT16                          usChnBlkNum;                         /* 核间传递内存块块数 */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulTtfRingQStAddrOffSet;              /* 核间传递信息数据TTFRINGQST的内存偏移量, 单位: 字节 */
    VOS_UINT32                          ulQueueNodeAddrOffSet;               /* 核间传递信息数据块的内存偏移量, 单位: 字节 */
    TTF_RING_Q_ST                       stRingBuffer;                        /* 环形互斥队列 */
} DICC_CHAN_CTRL_STRU;

/* 待传递信息的数据结构(也称核间传递结点) */
typedef struct
{
    VOS_UINT16                  usIndex;                                     /* 核间传递内存块编号 */
    VOS_UINT16                  usMagicNum;                                  /* 用于防止传递信息被篡改的魔术字 */
    VOS_UINT8                   ucPriDataLen;                                /* 待传递的信息内容长度, 单位: 字节 */
    VOS_UINT8                   aucReserve[3];
    VOS_UINT32                  ulInsertTime;                                /* 插入数据的时间, 单位: slice */
    VOS_UINT8                   aucPriData[DICC_INFO_BLOCK_MAX_LEN];         /* 待传递的信息内容 */
} DICC_QUEUE_NODE_STRU;

/* DICC通道对象映射表 */
typedef struct
{
    DICC_CPU_ID_ENUM_UINT8      enLocalCpuId;                                /* CPU指示符 */
    DICC_CHAN_ID_ENUM_UINT8     aenSender[DICC_MAX_SENDER_NUM_PER_CPU];      /* 记录充当sender的通道ID,脚标为服务类型 */
    DICC_CHAN_ID_ENUM_UINT8     aenRecver[DICC_MAX_RECVER_NUM_PER_CPU];      /* 记录充当recver的通道ID,脚标为服务类型 */
    DICC_CHAN_ROLE_ENUM_UINT8   aenRole[DICC_MAX_CHAN_NUM];                  /* 脚标为通道号 */
    VOS_UINT8                   aucReserve[2];
    VOS_UINT8                   ucSemCreated;                                /* 用于防止同一核上重复创建硬件信号量/本地互斥信号量的互斥标识
                                                                                未创建时, 设置为0, 创建后设置为1 */
    VOS_SEM                     ulDiccLocalMutexSem;                         /* 防止同一时刻在一核上用于互斥的本地互斥信号量 */
    volatile DICC_CTRL_STRU    *pastDICCMgmt;                                /* DICC管理结构的首地址 */
    VOS_UINT32                  ulPid;                                       /* DICC PID */
} DICC_CHAN_ROLE_STRU;

/* 中断操作结果记录 */
typedef struct
{
    VOS_UINT32                          ulIntLevel;    /* 中断服务号 */
    VOS_INT32                           lResult;       /* 操作结果 */
}DICC_INT_OP_STRU;

/* 单通道初始化上报信息 */
typedef struct
{
    DICC_SERVICE_TYPE_ENUM_UINT8        enServiceType; /* 用户填写的服务号 */
    VOS_UINT8                           aucReserve[3];
    DICC_INIT_CHN_INFO_STRU             stInitPara;    /* 记录用户初始化通道参数 */
    DICC_INT_OP_STRU                    stIntOp;       /* 记录操作中断的参数 */
    DICC_CHAN_LOCAL_SEM_PAPA_STRU       stLocalSemPara;     /* 记录本地信号量操作 */
} DICC_CHAN_SINGLE_INIT_CONTENT_STRU;

/* 双通道初始化上报信息 */
typedef struct
{
    DICC_SERVICE_TYPE_ENUM_UINT8        enServiceType;      /* 用户填写的服务号 */
    VOS_UINT8                           aucReserve[3];
    DICC_INIT_CHN_INFO_STRU             stInitSendChanPara; /* 记录用户初始化通道参数(充当发送者角色的通道) */
    DICC_INIT_CHN_INFO_STRU             stInitRecvChanPara; /* 记录用户初始化通道参数(充当接收者角色的通道) */
    DICC_INT_OP_STRU                    stIntOp;            /* 记录操作中断的参数 */
    DICC_CHAN_LOCAL_SEM_PAPA_STRU       stLocalSemPara;     /* 记录本地信号量操作 */
} DICC_CHAN_DUAL_INIT_CONTENT_STRU;

/* 打开通道参数 */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    DICC_CHAN_ROLE_ENUM_UINT8           enUserRole;
    VOS_UINT8                           aucReserve[2];
    DICC_CHAN_LOCAL_SEM_PAPA_STRU       stLocalSemPara;     /* 记录本地信号量操作 */
} DICC_CHAN_OPEN_PAPA_STRU;

/* 关闭通道参数 */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    VOS_UINT8                           aucReserve[3];
    DICC_CHAN_LOCAL_SEM_PAPA_STRU       stLocalSemPara;     /* 记录本地信号量操作 */
} DICC_CHAN_CLOSE_PAPA_STRU;

/* 触发通道数据发送的记录 */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    VOS_UINT8                           aucReserve[3];
    DICC_INT_OP_STRU                    stIntOp;            /* 中断操作记录 */
} DICC_CHAN_TRIG_CONTENT_STRU;

/* DICC通道数据满堵住, 无使用者读取 */
typedef struct
{
    VOS_UINT32                          ulResetSlice;       /* 单板复位时间 */
    DICC_TRACE_QUEUE_STRU               stTraceQueue;       /* 定位时, 用于导出通道数据的结构 */
    DICC_ISR_DEBUG_STRU                 stIsrDbg;           /* 误操作中断的记录 */
    DICC_CHAN_STATUS_STRU               stChanStatus;       /* 通道状态记录 */
}DICC_CHAN_EXECPTION_STRU;

/* 通道插入操作数据参数 */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    DICC_CHAN_INIT_STATUS_ENUM_UINT8    enChanInitFlag;         /* 标记通道是否已经初始化, 1为初始化; 0为未初始化 */
    VOS_UINT8                           ucChanStateMask;        /* 0: 通道两端未开启, 1: 仅发送端开启, 2: 仅接收端开启, 3: 两端都开启 */
    VOS_UINT8                           aucReserve[1];
    DICC_INSERT_DSCP_BLK_STRU           stDscpBlk;              /* 用户的信息传递描述结构 */
    DICC_CHAN_LOCAL_SEM_PAPA_STRU       stLocalSemPara;         /* 信号量操作记录 */
} DICC_CHAN_INSERT_PAPA_STRU;

/* 通道取出操作数据参数 */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    DICC_CHAN_INIT_STATUS_ENUM_UINT8    enChanInitFlag;         /* 标记通道是否已经初始化, 1为初始化; 0为未初始化 */
    VOS_UINT8                           ucChanStateMask;        /* 0: 通道两端未开启, 1: 仅发送端开启, 2: 仅接收端开启, 3: 两端都开启 */
    VOS_UINT8                           ucFlushData;            /* 0: 没有放弃取数, 1: 放弃取数 */
    VOS_UINT8                          *pucToSaveUsrData;       /* 用户提供的用于存放跨核信息的指针 */
    DICC_QUEUE_NODE_STRU                stTamperedQueueNode;    /* 跨核传递信息被篡改的现场 */
    DICC_CHAN_LOCAL_SEM_PAPA_STRU       stLocalSemPara;         /* 信号量操作记录 */
} DICC_CHAN_REMOVE_PAPA_STRU;

/* 获取通道数据块数操作参数 */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    DICC_GET_CHN_NODE_CNT_ENUM_UINT8    enGetChnNodeCntType;    /* 用于指示获取通道中已经存放的数据个数, 或者通道中可以继续存放的个数 */
    DICC_CHAN_INIT_STATUS_ENUM_UINT8    enChanInitFlag;         /* 标记通道是否已经初始化, 1为初始化; 0为未初始化 */
    VOS_UINT8                           ucChanStateMask;        /* 0: 通道两端未开启, 1: 仅发送端开启, 2: 仅接收端开启, 3: 两端都开启 */
} DICC_CHAN_GET_CNT_PAPA_STRU;

/* DICC上报用户异常操作事件(通道完全关闭时, 有数据块残留) */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    VOS_UINT8                           ucFlushCnt;        /* 通道完全关闭时残留的数据块 */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulOpPid;           /* 操作PID */
} DICC_CHAN_CLOSE_FLUSH_EVENT_STRU;

/* DICC上报用户异常操作事件(从通道取数据时, 数据块被篡改) */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulOpPid;           /* 操作PID */
    DICC_QUEUE_NODE_STRU                stQueueNode;       /* 被篡改的数据结点 */
} DICC_CHAN_MAGIC_NUM_CHANGED_EVENT_STRU;

/* DICC上报用户异常操作事件(向通道插入数据时, 出现通道数据满) */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulOpPid;           /* 操作PID */
    VOS_UINT32                          ulQueueFullCnt;    /* 上报事件时, 队列满总次数 */
} DICC_CHAN_QUEUE_FULL_EVENT_STRU;

/* 记录用户中断操作的结构 */
typedef struct
{
    VOS_UINT32                          ulPid;
    DICC_SERVICE_TYPE_ENUM_UINT8        enServiceType;
    DICC_SERVICE_ISR_OP_ENUM_UINT8      enIsrOp;           /* 对中断的操作 */
    PS_BOOL_ENUM_UINT8                  enOpResult;        /* PS_FALSE - 误操作中断 */
    VOS_UINT8                           aucReserve[1];
} DICC_RECORD_ISR_STRU;

/* 同步DICC内存清零时操作结果的记录 */
typedef struct
{
    DICC_CHAN_LOCAL_SEM_PAPA_STRU       stLocalSemPara;    /* 本地信号量操作记录 */
    DICC_CHAN_HW_SEM_PAPA_STRU          stHwSemPara;       /* 硬件信号量操作记录 */
    VOS_UINT32                          ulDiccMagic;
} DICC_CHAN_SYNC_PARA_STRU;

/* 联调期间, 周边组件代码不完善,
   单板启动期间出错, 因为OM task缓存有限, LOG打不出来, 需要在串口打印
   所以设计此结构, 将各种错误都记录到一起, 暂限于单板启动阶段 */
typedef struct
{
    DICC_CPU_ID_ENUM_UINT8              enCpuId;          /* 工作CPU-ID */
    DICC_TRACE_FUNC_MARK_ID_ENUM_UINT8  enFuncId;         /* 用于跟踪执行函数 */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulPid;            /* 操作PID */
    VOS_UINT32                          ulLine;           /* 行号 */
    DICC_ERROR_CODE_ENUM_UINT32         enResult;         /* 记录操作结果 */
} DICC_TRACE_INFO_STRU;

/* DICC软复位基础信息 */
typedef struct
{
    VOS_UINT32                          ulModule;
    VOS_UINT32                          ulFile;
    VOS_UINT32                          ulLine;
    VOS_UINT8                          *pucData;
    VOS_UINT32                          ulDataLen;
} DICC_SOFT_REBOOT_INFO_STRU;

#if 0
typedef struct
{
    VOS_UINT32 ulErrChanBlkNum;  /* 通道块数错误次数 */
    VOS_UINT32 ulErrChanBlkSize;      /* 通道块大小错误次数 */
    VOS_UINT32 ulErrMemSize;     /* 通道内存总量错误次数 */
    VOS_UINT32 ulErrRecvIsrNull;       /* 通道接收端信号量句柄为空次数 */
    VOS_UINT32 ulErrChanIdUndefined; /* 通道未注册次数 */
    VOS_UINT32 ulErrInfoPtrNull; /* 通道一端信息空 */
    VOS_UINT32 ulErrServceUndefine;    /* 通道服务未注册 */
    VOS_UINT32 ulErrExistedChanId;    /* 通道重复注册 */
    VOS_UINT32 ulErrChanIdNotMatchRole;    /* 通道号与角色不匹配 */
    VOS_UINT32 ulErrChanAlreadyOpened;    /* 通道重复打开 */
    VOS_UINT32 ulErrInsertDespBlkPtrNull;    /* 通道插入信息描述符为空 */
    VOS_UINT32 ulErrInsertDespBlkDataNull;    /* 传递信息为空 */
    VOS_UINT32 ulErrDlvDataBlkSize;    /* 传递信息块大小错误 */
    VOS_UINT32 ulErrChanNotOpenInBothSides;    /* 传递或取出信息时, 通道未完全打开 */
    VOS_UINT32 ulErrInvalidChanId;   /* 不合法的通道ID */
    VOS_UINT32 ulErrGetCntTypeUndefined;    /* 获取通道块数类别错误 */
    VOS_UINT32 ulErrRemoveDataPtrNull;                          /* 存放取出数据的指针为空 */
    VOS_UINT32 ulErrOpChanNotReady;    /* 通道控制结构未准备好 */
    VOS_UINT32 ulErrGetNodeFail;    /* 获取核间传递结点失败 */
    VOS_UINT32 ulErrMagicNumChanged;    /* 核间传递数据被篡改 */
    VOS_UINT32 ulErrRingQueueFail;    /* 核间对列操作失败 */
    VOS_UINT32 ulErrLocalSemFail;    /* 本地信号量操作失败 */
    VOS_UINT32 ulErrIsrConnectFail;    /* 中断挂接失败 */
    VOS_UINT32 ulErrUseHwSemFail;    /* 硬件信号量操作失败 */
    VOS_UINT32 ulErrUseHwSemFail;    /* 触发中断失败 */
} DICC_DEBUG_INFO_STRU;
#endif

#endif  /*FEATURE_ON == FEATURE_CSD*/

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


/******************************************************************************
  8 UNION定义
******************************************************************************/


/******************************************************************************
  9 OTHERS定义
******************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* Dicc.h */


