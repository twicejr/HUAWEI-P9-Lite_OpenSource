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
#ifndef _DEFLATE_H
#define _DEFLATE_H
#endif

#include <product_config.h>

#include "osl_types.h"
#include "osl_sem.h"

#include "osl_spinlock.h"
#include "osl_thread.h"
#include "drv_nv_id.h"

#include "bsp_socp.h"

#include "socp_balong.h"
#include "hi_deflate.h"


#define DEFLATE_NULL            (void*)0
#define DEFLATE_OK                  (0)
#define DEFLATE_ERROR               (1)
#define DEFLATE_ERR_SET_FAIL        (2)
#define DEFLATE_ERR_SET_INVALID     (3)
#define DEFLATE_ERR_INVALID_PARA    (4)
#define DEFLATE_ERR_NOT_INIT        (5)
#define DEFLATE_ERR_NULL            (6)
#define DEFLATE_ERR_NOT_8BYTESALIGN (7)
#define DEFLATE_TRANS_TIMEOUT_DEFAULT      (0x17) 

typedef SOCP_CODER_DEST_CHAN_S DEFLATE_CHAN_CONFIG_S;

typedef SOCP_BUFFER_RW_STRU    DEFLATE_BUFFER_RW_STRU;

typedef SOCP_RING_BUF_S         DEFLATE_RING_BUF_STRU;

typedef socp_read_cb    deflate_read_cb;
typedef socp_event_cb   deflate_event_cb;
/* DEFLATE_REG Base address of Module's Register */
 enum DEFLATE_STATE_ENUM
    {
    DEFLATE_IDLE               = 0,    /* DEFLATE处于空闲态 */
    DEFLATE_BUSY,                      /* DEFLATE处忙 */
    DEFLATE_UNKNOWN_BUTT              /*  未知状态 */
};
#define  SOCP_REG_DEFLATE_INFORMATION                  Hi_SOCP_REG_DEFLATE_INFORMATION            /* deflate压缩模块版本信息 */
#define  SOCP_REG_DEFLATE_GLOBALCTRL                   Hi_SOCP_REG_DEFLATE_GLOBALCTRL             /* SOCP deflate全局控制寄存器 */
#define  SOCP_REG_DEFLATE_IBUFTIMEOUTCFG               Hi_SOCP_REG_DEFLATE_IBUFTIMEOUTCFG         /* 压缩模块ibuf超时计数器配置 */
#define  SOCP_REG_DEFLATE_RAWINT                       Hi_SOCP_REG_DEFLATE_RAWINT                 /* 原始中断寄存器 */
#define  SOCP_REG_DEFLATE_INT                          Hi_SOCP_REG_DEFLATE_INT                    /* 中断状态寄存器 */
#define  SOCP_REG_DEFLATE_INTMASK                      Hi_SOCP_REG_DEFLATE_INTMASK                /* 中断屏蔽寄存器 */
#define  SOCP_REG_DEFLATE_TFRTIMEOUTCFG                Hi_SOCP_REG_DEFLATE_TFRTIMEOUTCFG          /* 压缩数据块传输超时计数器配置阈值 */
#define  SOCP_REG_DEFLATE_STATE                        Hi_SOCP_REG_DEFLATE_STATE                  /* 压缩模块操作控制 */
#define  SOCP_REG_DEFLATE_ABORTSTATERECORD             Hi_SOCP_REG_DEFLATE_ABORTSTATERECORD       /* 压缩异常状态记录 */
#define  SOCP_REG_DEFLATEDEBUG_CH                      Hi_SOCP_REG_DEFLATEDEBUG_CH                /* 压缩模块bug通道 */
#define  SOCP_REG_DEFLATEDEST_BUFREMAINTHCFG           Hi_SOCP_REG_DEFLATEDEST_BUFREMAINTHCFG     /* 压缩通路目的buffer溢出中断阈值寄存器 */
#define  SOCP_REG_DEFLATEDEST_BUFRPTR            	   Hi_SOCP_REG_DEFLATEDEST_BUFRPTR            /* 压缩通路目的buffer读指针寄存器 */
#define  SOCP_REG_DEFLATEDEST_BUFWPTR                  Hi_SOCP_REG_DEFLATEDEST_BUFWPTR            /* 压缩通路目的buffer写指针寄存器 */
#define  SOCP_REG_DEFLATEDEST_BUFADDR                  Hi_SOCP_REG_DEFLATEDEST_BUFADDR            /* 压缩通路目的buffer起始地址寄存器 */
#define  SOCP_REG_DEFLATEDEST_BUFDEPTH                 Hi_SOCP_REG_DEFLATEDEST_BUFDEPTH           /* 压缩通路目的buffer深度寄存器 */
#define  SOCP_REG_DEFLATEDEST_BUFTHRH                  Hi_SOCP_REG_DEFLATEDEST_BUFTHRH            /* 传输阈值中断配置寄存器 */
#define  SOCP_REG_DEFLATEDEST_BUFOVFTIMEOUT            Hi_SOCP_REG_DEFLATEDEST_BUFOVFTIMEOUT      /* 压缩目的BUFFER溢出超时配置寄存器 */
#define  SOCP_REG_SOCP_MAX_PKG_BYTE_CFG                Hi_SOCP_REG_SOCP_MAX_PKG_BYTE_CFG          /* socp最大包长字节阈值配置 */
#define  SOCP_REG_DEFLATE_OBUF_DEBUG                   Hi_SOCP_REG_DEFLATE_OBUF_DEBUG             /* 压缩目的buffer DEBUG */
#define DEFLATE_DRX_BACKUP_DDR_ADDR        (SHM_BASE_ADDR + SHM_OFFSET_DEFLATE)
#define DEFLATE_REG_ADDR_DRX(addr)  (addr + g_strDeflateCtrl.baseAddr)
#define DEFLATE_DRX_REG_GBLRST_NUM   (18)
struct deflate_ctrl_info
{
    u32                     initFlag;
    u32                     u32ChanID;
    void*                     baseAddr;
    u32                     u32SetStat;    /* 通道已经或没有配置的标识*/
    u32                     u32Thrh;       /* 阈值*/
    socp_event_cb           event_cb;
    socp_read_cb            read_cb;
    osl_sem_id              task_sem;
    OSL_TASK_ID             taskid;
    spinlock_t              intSpinLock;
    u32                     intState;
    DEFLATE_RING_BUF_STRU   sDeflateDstChan;
    u32 u32IntDeflateDstTfr;
    u32 u32IntDeflateDstThresholdOvf ;
    u32 u32IntDeflateDstOvf    ;
    u32 u32IntDeflateWorkAbort ;
};
struct deflate_debug_info
{  
    u32 u32DeflateDstSetCnt;                  /*deflate目的buffer配置次数*/
    u32 u32DeflateDstSetSucCnt;               /*deflate目的buffer配置成功次数*/
    u32 u32DeflateRegReadCBCnt;               /*注册deflate目的通道读数据回调函数次数*/
    u32 u32DeflateRegEventCBCnt;              /*注册deflate目的通道异常事件回调函数次数*/   
    u32 u32DeflateGetReadBufEtrCnt;           /*尝试获取deflate目的buffer次数*/
    u32 u32DeflateGetReadBufSucCnt;           /*获取deflate目的buffer成功次数*/   
    u32 u32DeflateReaddoneEtrCnt;             /*尝试读取deflate目的数据次数*/
    u32 u32DeflateReaddoneZeroCnt;            /*尝试读取deflate目的数据长度等于0次数*/
    u32 u32DeflateReaddoneValidCnt;           /*读取deflate目的数据长度不等于0次数*/
    u32 u32DeflateReaddoneFailCnt;            /*读取deflate目的数据失败的次数*/
    u32 u32DeflateReaddoneSucCnt;             /*读取deflate目的数据成功的次数*/  
    u32 u32DeflateTskTrfCbOriCnt;             /*处理传输中断任务的次数*/
    u32 u32DeflateTskTrfCbCnt;                /*处理完传输中断任务的次数*/
    u32 u32DeflateTskOvfCbOriCnt;             /*处理上溢中断的次数*/
    u32 u32DeflateTskOvfCbCnt;                /*处理完上溢中断的次数*/
    u32 u32DeflateTskThresholdOvfCbOriCnt;    /*处理阈值溢出的次数*/
    u32 u32DeflateTskThresholdOvfCbCnt;       /*处理完阈值溢出的次数*/
    u32 u32DeflateTskIntWorkAortCbOriCnt;     /*处理异常的次数*/                       
    u32 u32DeflateTskIntWorkAortCbCnt;        /*处理完异常的次数*/       
};
struct deflate_abort_info
{
	u32 u32DeflateGlobal;
	u32 u32IbufTimeoutConfig;
	u32 u32RawInt;
	u32 u32IntState;
	u32 u32IntMask;
	u32 u32ThfTimeoutConfig;
	u32 u32DeflateState;
	u32 u32AbortStateRecord;
    u32 u32DebugChan;
	u32 u32ObufThrh;
    u32 u32ReadAddr;
    u32 u32WriteAddr;
    u32 u32StartAddr;
    u32 u32BufSize;
    u32 u32IntThrh;
    u32 u32OvfTimeoutEn;
    u32 u32PkgConfig;
    u32 u32ObufDebug;
};

enum tagDEFLATE_EVENT_E
{
        DEFLATE_EVENT_WORK_ABORT          = 0x5,    /* YICHANG*/
        DEFLATE_EVENT_OVERFLOW            = 0x6,    /* 目的buffer上溢 */
        DEFLATE_EVENT_THRESHOLD_OVERFLOW  = 0x7,    /* 目的buffer阈值溢出中断 */
        DEFLATE_EVENT_BUTT
};
typedef unsigned int DEFLATE_EVENT_ENUM_UIN32;



#define deflate_printf(fmt, ...)   (bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_SOCP, "[deflate]: <%s> %d  "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define deflate_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_INFO ,BSP_MODU_SOCP, "[deflate]: <%s> %d  "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define  DEFLATE_CHN_SET ((s32) 1)     /*通道已经配置*/
#define DEFLATE_WORK_ABORT_MASK ((s32)(1)<<2 )
#define DEFLATE_THROVF_MASK ((s32)(1)<<6 )
#define DEFLATE_OVF_MASK ((s32)(1)<<7 )
#define DEFLATE_TFR_MASK ((s32)(1)<<8 )
#define DEFLATE_WORK_STATE ((s32)(1)<<19)
#define DEFLATE_CHAN_DEF(chan_type, chan_id)   ((chan_type<<16)|chan_id)
#define DEFLATE_REAL_CHAN_ID(unique_chan_id)   (unique_chan_id & 0xFFFF)
#define DEFLATE_REAL_CHAN_TYPE(unique_chan_id) (unique_chan_id>>16)


/* 检测是否初始化的宏定义 */
#define DEFLATE_CHECK_INIT() \
    do{\
        if (!g_strDeflateCtrl.initFlag)\
        {\
            deflate_printf("%s line %d:the module has not been initialized!\n",__FUNCTION__,__LINE__);\
            return DEFLATE_ERR_NOT_INIT;\
        }\
    }while(0)

/* 检测参数是否有效 */
#define DEFLATE_CHECK_PARA(para) \
    do{\
        if (0 == para)\
        {\
            deflate_printf("%s line %d:the parameter is NULL!\n",__FUNCTION__,__LINE__);\
            return DEFLATE_ERR_NULL;\
        }\
    }while(0)

/* 检测是否8字节对齐 */
#define DEFLATE_CHECK_8BYTESALIGN(para) \
    do{\
        if (0 != (para%8))\
        {\
            deflate_printf("%s line %d:the parameter is not 8 bytes aligned!\n",__FUNCTION__,__LINE__);\
            return DEFLATE_ERR_NOT_8BYTESALIGN;\
        }\
    }while(0)
/*检查起始地址是否有效*/

#define DEFLATE_CHECK_BUF_ADDR(start, end) \
    do{\
        if (start >= end)\
        {\
            deflate_printf("%s line %d:the buff is invalid!\n",__FUNCTION__,__LINE__);\
            return DEFLATE_ERR_INVALID_PARA;\
        }\
    }while(0)
    

#define DEFLATE_REG_READ(reg, result)           (result = readl((volatile void *)(g_strDeflateCtrl.baseAddr + reg)))
#define DEFLATE_REG_SETBITS(reg, pos, bits, val) BSP_REG_SETBITS(g_strDeflateCtrl.baseAddr, reg, pos, bits, val)
#define DEFLATE_REG_WRITE(reg, data)            (writel(data, (volatile void *)(g_strDeflateCtrl.baseAddr + reg)))

 u32 deflate_set(u32 u32DestChanID, DEFLATE_CHAN_CONFIG_S *pDeflateAttr);
 u32 deflate_clear(void);

 u32 deflate_enable(u32 u32DstChanId);

 u32 deflate_unable(u32 u32DstChanId);

 u32 deflate_int_handler(void);

 u32 deflate_read_data_done(u32 u32DstChanId,u32 ulDatalen);

 u32 deflate_get_read_buffer(u32 u32DstChanId,DEFLATE_BUFFER_RW_STRU *pBuff);

 u32 deflate_register_read_cb(u32 u32DstChanId, deflate_read_cb ReadCB);

 u32 deflate_register_event_cb(u32 u32DstChanId, deflate_event_cb ReadCB);



