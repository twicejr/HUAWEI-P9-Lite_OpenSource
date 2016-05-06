/*************************************************************************
*   版权所有(C) 1987-2011, 深圳华为技术有限公司.
*
*   文 件 名 :  SOCP_BALONG.h
*
*   作    者 :  z00212940
*
*   描    述 :  SOCP模块用户头文件
*
*   修改记录 :  2013年1月29日  v1.00  z00212940  创建
*
*************************************************************************/

#ifndef _SOCP_BALONG_H
#define _SOCP_BALONG_H

#ifdef __cplusplus
extern "C"
{
#endif

/**************************************************************************
  头文件包含
**************************************************************************/
#include <string.h>
#include <stdio.h>
#include "product_config.h"
#include "osl_bio.h"
#include "hi_socp.h"
#include "soc_interrupts.h"
#include "bsp_memmap.h"
#include "bsp_external_stub.h"
#include "bsp_socp.h"
#include "bsp_om.h"
#if defined(__OS_RTOSCK__)
#include "securec.h"
#endif
#include "drv_comm.h"
/**************************************************************************
  宏定义
**************************************************************************/
/*系统控制器*/
#define SOCP_REG_BASEADDR           (g_strSocpStat.baseAddr)

/**************************************************************************
  寄存器定义,偏移地址
**************************************************************************/
#define SOCP_REG_GBLRST             (HI_SOCP_GLOBAL_SRST_CTRL_OFFSET)
#define SOCP_REG_ENCRST             (HI_SOCP_ENC_SRST_CTRL_OFFSET)
#define SOCP_REG_DECRST             (HI_SOCP_DEC_SRST_CTRL_OFFSET)
#define SOCP_REG_ENCSTAT            (HI_SOCP_ENC_CH_STATUS_OFFSET)
#define SOCP_REG_DECSTAT            (HI_SOCP_DEC_CH_STATUS_OFFSET)
#define SOCP_REG_CLKCTRL            (HI_SOCP_CLK_CTRL_OFFSET)
#define SOCP_REG_PRICFG             (HI_SOCP_PRIOR_CFG_OFFSET)
#define SOCP_REG_INTTIMEOUT         (HI_SOCP_INT_TIMEOUT_OFFSET)
#define SOCP_REG_BUFTIMEOUT         (HI_SOCP_BUFFER_TIMEOUT_OFFSET)
#define SOCP_REG_DEC_PKTLEN         (HI_SOCP_DEC_PKT_LEN_CFG_OFFSET)
#define SOCP_REG_GBL_INTSTAT        (HI_SOCP_GLOBAL_INT_STATUS_OFFSET)

    /* 编码器 中断寄存器*/
#define SOCP_REG_ENC_MASK0          (HI_SOCP_ENC_CORE0_MASK0_OFFSET)
#define SOCP_REG_ENC_RAWINT0        (HI_SOCP_ENC_CORE0_RAWINT0_OFFSET)
#define SOCP_REG_ENC_INTSTAT0       (HI_SOCP_ENC_CORE0_INT0_OFFSET)
#define SOCP_REG_APP_MASK1          (HI_SOCP_ENC_CORE0_MASK1_OFFSET)
#define SOCP_REG_MODEM_MASK1        (HI_SOCP_ENC_CORE1_MASK1_OFFSET)
#define SOCP_REG_ENC_RAWINT1        (HI_SOCP_ENC_RAWINT1_OFFSET)
#define SOCP_REG_APP_INTSTAT1       (HI_SOCP_ENC_CORE0_INT1_OFFSET)
#define SOCP_REG_MODEM_INTSTAT1     (HI_SOCP_ENC_CORE1_INT1_OFFSET)
#define SOCP_REG_ENC_MASK2          (HI_SOCP_ENC_CORE0_MASK2_OFFSET)
#define SOCP_REG_ENC_RAWINT2        (HI_SOCP_ENC_CORE0_RAWINT2_OFFSET)
#define SOCP_REG_ENC_INTSTAT2       (HI_SOCP_ENC_CORE0_INT2_OFFSET)
#define SOCP_REG_APP_MASK3          (HI_SOCP_ENC_CORE0_MASK3_OFFSET)
#define SOCP_REG_MODEM_MASK3        (HI_SOCP_ENC_CORE1_MASK3_OFFSET)
#define SOCP_REG_ENC_RAWINT3        (HI_SOCP_ENC_RAWINT3_OFFSET)
#define SOCP_REG_APP_INTSTAT3       (HI_SOCP_ENC_CORE0_INT3_OFFSET)
#define SOCP_REG_MODEM_INTSTAT3     (HI_SOCP_ENC_CORE1_INT3_OFFSET)
#define SOCP_REG_ENC_CORE1_MASK0    (HI_SOCP_ENC_CORE1_MASK0_OFFSET)
#define SOCP_REG_ENC_CORE1_INT0     (HI_SOCP_ENC_CORE1_INT0_OFFSET)
#define SOCP_REG_ENC_CORE1_MASK2    (HI_SOCP_ENC_CORE1_MASK2_OFFSET)
#define SOCP_REG_ENC_CORE1_INT2     (HI_SOCP_ENC_CORE1_INT2_OFFSET)

    /* 解码器中断寄存器*/
#define SOCP_REG_DEC_CORE0MASK0     (HI_SOCP_DEC_CORE0_MASK0_OFFSET)
#define SOCP_REG_DEC_CORE1MASK0     (HI_SOCP_DEC_CORE1_MASK0_OFFSET)
#define SOCP_REG_DEC_RAWINT0        (HI_SOCP_DEC_RAWINT0_OFFSET)
#define SOCP_REG_DEC_CORE0ISTAT0    (HI_SOCP_DEC_CORE0_INT0_OFFSET)
#define SOCP_REG_DEC_CORE1ISTAT0    (HI_SOCP_DEC_CORE1_INT0_OFFSET)
#define SOCP_REG_DEC_MASK1          (HI_SOCP_DEC_CORE0_MASK1_OFFSET)
#define SOCP_REG_DEC_RAWINT1        (HI_SOCP_DEC_CORE0_RAWINT1_OFFSET)
#define SOCP_REG_DEC_INTSTAT1       (HI_SOCP_DEC_CORE0_INT1_OFFSET)
#define SOCP_REG_DEC_CORE0MASK2     (HI_SOCP_DEC_CORE0_MASK2_OFFSET)
#define SOCP_REG_DEC_CORE1MASK2     (HI_SOCP_DEC_CORE1NOTE_MASK2_OFFSET)
#define SOCP_REG_DEC_RAWINT2        (HI_SOCP_DEC_RAWINT2_OFFSET)
#define SOCP_REG_DEC_CORE0ISTAT2    (HI_SOCP_DEC_CORE0NOTE_NT2_OFFSET)
#define SOCP_REG_DEC_CORE1ISTAT2    (HI_SOCP_DEC_CORE1NOTE_INT2_OFFSET)
#define SOCP_REG_DEC_CORE1_MASK1    (HI_SOCP_DEC_CORE1_MASK1_OFFSET)
#define SOCP_REG_DEC_CORE1_INT1     (HI_SOCP_DEC_CORE1_INT1_OFFSET)

    /*编码器通道buffer寄存器*/
#define SOCP_REG_ENCSRC_BUFWPTR(m)  (HI_SOCP_ENC_SRC_BUFM_WPTR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_BUFRPTR(m)  (HI_SOCP_ENC_SRC_BUFM_RPTR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_BUFADDR(m)  (HI_SOCP_ENC_SRC_BUFM_ADDR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_BUFCFG0(m)  (HI_SOCP_ENC_SRC_BUFM_CFG0_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_BUFCFG1(m)  (HI_SOCP_ENC_SRC_BUFM_CFG1_0_OFFSET + m*0x40)

#define SOCP_REG_ENCSRC_RDQWPTR(m)  (HI_SOCP_ENC_SRC_RDQ_WPTR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_RDQRPTR(m)  (HI_SOCP_ENC_SRC_RDQ_RPTR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_RDQADDR(m)  (HI_SOCP_ENC_SRC_RDQ_BADDR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_RDQCFG(m)   (HI_SOCP_ENC_SRC_RDQ_CFG_0_OFFSET + m*0x40)

#define SOCP_REG_ENCDEST_BUFWPTR(n) (HI_SOCP_ENC_DEST_BUFN_WPTR_0_OFFSET + n*0x20)
#define SOCP_REG_ENCDEST_BUFRPTR(n) (HI_SOCP_ENC_DEST_BUFN_RPTR_0_OFFSET + n*0x20)
#define SOCP_REG_ENCDEST_BUFADDR(n) (HI_SOCP_ENC_DEST_BUFN_ADDR_0_OFFSET + n*0x20)
#define SOCP_REG_ENCDEST_BUFCFG(n)  (HI_SOCP_ENC_DEST_BUFN_CFG_0_OFFSET + n*0x20)
#define SOCP_REG_ENCDEST_BUFTHRH(n) (HI_SOCP_ENC_DEST_BUFN_THRH_0_OFFSET + n*0x20)
#define SOCP_REG_ENCDEST_BUFTHRESHOLD(n) (HI_SOCP_ENC_INT_THRESHOLD_0_OFFSET + n*0x20)

    /*解码器通道buffer寄存器*/
#define SOCP_REG_DECSRC_BUFWPTR(x)  (HI_SOCP_DEC_SRC_BUFX_WPTR_0_OFFSET + x*0x40)
#define SOCP_REG_DECSRC_BUFRPTR(x)  (HI_SOCP_DEC_SRC_BUFX_RPTR_0_OFFSET + x*0x40)
#define SOCP_REG_DECSRC_BUFADDR(x)  (HI_SOCP_DEC_SRC_BUFX_ADDR_0_OFFSET + x*0x40)
#define SOCP_REG_DECSRC_BUFCFG0(x)  (HI_SOCP_DEC_SRC_BUFX_CFG0_0_OFFSET + x*0x40)
#define SOCP_REG_DEC_BUFSTAT0(x)    (HI_SOCP_DEC_BUFX_STATUS0_0_OFFSET + x*0x40)
#define SOCP_REG_DEC_BUFSTAT1(x)    (HI_SOCP_DEC_BUFX_STATUS1_0_OFFSET + x*0x40)

#define SOCP_REG_DECDEST_BUFWPTR(y) (HI_SOCP_DEC_DEST_BUFY_WPTR_0_OFFSET + y*0x10)
#define SOCP_REG_DECDEST_BUFRPTR(y) (HI_SOCP_DEC_DEST_BUFY_RPTR_0_OFFSET + y*0x10)
#define SOCP_REG_DECDEST_BUFADDR(y) (HI_SOCP_DEC_DEST_BUFY_ADDR_0_OFFSET + y*0x10)
#define SOCP_REG_DECDEST_BUFCFG(y)  (HI_SOCP_DEC_DEST_BUFY_CFG0_0_OFFSET + y*0x10)

    /*DEBUG寄存器*/
#define SOCP_REG_ENCCD_DBG0         (HI_SOCP_ENC_CD_DBG0_OFFSET)
#define SOCP_REG_ENCCD_DBG1         (HI_SOCP_ENC_CD_DBG1_OFFSET)
#define SOCP_REG_ENCIBUF_DBG0       (HI_SOCP_ENC_IBUF_DBG0_OFFSET)
#define SOCP_REG_ENCIBUF_DBG1       (HI_SOCP_ENC_IBUF_DBG1_OFFSET)
#define SOCP_REG_ENCIBUF_DBG2       (HI_SOCP_ENC_IBUF_DBG2_OFFSET)
#define SOCP_REG_ENCIBUF_DBG3       (HI_SOCP_ENC_IBUF_DBG3_OFFSET)
#define SOCP_REG_ENCOBUF_DBG0       (HI_SOCP_ENC_OBUF_DBG0_OFFSET)
#define SOCP_REG_ENCOBUF_DBG1       (HI_SOCP_ENC_OBUF_DBG1_OFFSET)
#define SOCP_REG_ENCOBUF_DBG2       (HI_SOCP_ENC_OBUF_DBG2_OFFSET)
#define SOCP_REG_ENCOBUF_DBG3       (HI_SOCP_ENC_OBUF_DBG3_OFFSET)
#define SOCP_REG_DECIBUF_DBG0       (HI_SOCP_DEC_IBUF_DBG0_OFFSET)
#define SOCP_REG_DECIBUF_DBG1       (HI_SOCP_DEC_IBUF_DBG1_OFFSET)
#define SOCP_REG_DECIBUF_DBG2       (HI_SOCP_DEC_IBUF_DBG2_OFFSET)
#define SOCP_REG_DECIBUF_DBG3       (HI_SOCP_DEC_IBUF_DBG3_OFFSET)
#define SOCP_REG_DECOBUF_DBG0       (HI_SOCP_DEC_OBUF_DBG0_OFFSET)
#define SOCP_REG_DECOBUF_DBG1       (HI_SOCP_DEC_OBUF_DBG1_OFFSET)
#define SOCP_REG_DECOBUF_DBG2       (HI_SOCP_DEC_OBUF_DBG2_OFFSET)
#define SOCP_REG_DECOBUF_DBG3       (HI_SOCP_DEC_OBUF_DBG3_OFFSET)

/*版本寄存器*/
#define SOCP_REG_SOCP_VERSION       (HI_SOCP_SOCP_VERSION_OFFSET)
#define SOCP_NEW_VERSION            (0x201)

    /* BBP 通道寄存器 */
#define BBP_REG_LOG_ADDR(m)         (0x0200 + 0x10*m)
#define BBP_REG_LOG_WPTR(m)         (0x0204 + 0x10*m)
#define BBP_REG_LOG_RPTR(m)         (0x0208 + 0x10*m)
#define BBP_REG_LOG_CFG(m)          (0x020C + 0x10*m)
#define BBP_REG_DS_ADDR             (0x0280)
#define BBP_REG_DS_WPTR             (0x0284)
#define BBP_REG_DS_RPTR             (0x0288)
#define BBP_REG_DS_CFG              (0x028C)
#define BBP_REG_PTR_ADDR            (0x0290)
#define BBP_REG_CH_EN               (0x0294)
#define BBP_REG_PKT_CNT             (0x0298)
#define BBP_REG_CH_STAT             (0x029C)
#define BBP_REG_LOG_EN              (0x02B8)

/**************************************************************************
  寄存器位域定义
**************************************************************************/

/*
 * Bit masks for registers: ENCSTAT,DECSTAT, channel state
 */
#define SOCP_CHN_BUSY ((s32) 1)   /*通道忙*/
#define SOCP_CHN_IDLE ((s32) 0)   /*通道闲*/

/*
 * 通道打开宏定义，适用于编码源通道和解码目的通道
 */
#define SOCP_CHN_ALLOCATED ((s32) 1)    /*通道已经分配*/
#define SOCP_CHN_UNALLOCATED ((s32) 0)    /*通道没有分配*/

/*
 * 通道使能宏定义，同时适用于编码源通道和解码源通道
 */
#define SOCP_CHN_ENABLE ((s32) 1)   /*通道打开*/
#define SOCP_CHN_DISABLE ((s32) 0)   /*通道关闭*/

/*
 * 通道是否已经设置
 */
#define SOCP_CHN_SET ((s32) 1)     /*通道已经配置*/
#define SOCP_CHN_UNSET ((s32) 0)     /*通道没有配置*/

/*
 * 编码旁路设置使能位
 */
#define SOCP_ENCSRC_BYPASS_ENABLE ((s32) 1)     /*通道旁路使能*/
#define SOCP_ENCSRC_BYPASS_DISABLE ((s32) 0)     /*通道旁路没有使能*/

/*
 * 编码旁路设置使能位
 */
#define SOCP_DECSRC_DEBUG_ENBALE ((s32) 1)     /*通道DEBUG 使能*/
#define SOCP_DECSRC_DEBUG_DISBALE ((s32) 0)     /*通道DEBUG 没有使能*/

#define SOCP_CORE0_DEC_OUTOVFINT_MASK ((s32)(1))          /* 解码core0 目的BUFFER溢出中断 */
#define SOCP_DEC_INERRINT_MASK ((s32)(1 << 1))       /* 编码输入检测错误中断 */
#define SOCP_CORE0_DEC_TFRINT_MASK ((s32)(1 << 2))       /* 编码core0传输完成中断 */
#define SOCP_CORE1_DEC_TFRINT_MASK ((s32)(1 << 3))       /* 解码core1 传输完成中断 */
#define SOCP_CORE1_DEC_OUTOVFINT_MASK ((s32)(1 << 4))       /* 编码core1 目的BUFFER溢出中断*/
#define SOCP_MODEM_ENC_RDINT_MASK ((s32)(1 << 10))      /* 编码RDBUFFER完成中断 */
#define SOCP_APP_ENC_RDINT_MASK ((s32)(1 << 11))      /* 编码MODEMCPU包头检测错误中断 */
#define SOCP_APP_ENC_OUTOVFINT_MASK ((s32)(1 << 12))      /* 编码RDBUFFER完成中断 */
#define SOCP_MODEM_ENC_FLAGINT_MASK ((s32)(1 << 13))      /* 编码MODEMCPU包头检测错误中断 */
#define SOCP_APP_ENC_FLAGINT_MASK ((s32)(1 << 14))      /* 编码RDBUFFER完成中断 */
#define SOCP_APP_ENC_TFRINT_MASK ((s32)(1 << 15))      /* 编码MODEMCPU包头检测错误中断 */
#define SOCP_DEC_SRCINT_NUM (6)              /* 编码MODEMCPU包头检测错误中断 */

#define SOCP_TRANS_TIMEOUT_DEFAULT (0x17)  //dec:23
#define SOCP_OVERFLOW_TIMEOUT_DEFAULT (0x5969) //dec:22889

#define SOCP_DEC_PKTLGTH_MAX (0x04) //dec:4090

#define SOCP_DEC_PKTLGTH_MIN (0x06)  //dec:6
#define SOCP_TIMEOUT_MAX (0xffff)
#define SOCP_DEC_MAXPKT_MAX (0x1000)
#define SOCP_DEC_MINPKT_MAX (0x1f)
#define SOCP_ENC_SRC_BUFLGTH_MAX (0x7ffffff)
#define SOCP_ENC_SRC_RDLGTH_MAX (0xffff)
#define SOCP_ENC_DST_BUFLGTH_MAX (0x1fffff)
#define SOCP_ENC_DST_TH_MAX (0x7ff)
#define SOCP_DEC_SRC_BUFLGTH_MAX (0xffff)
#define SOCP_DEC_SRC_RDLGTH_MAX (0xffff)
#define SOCP_DEC_DST_BUFLGTH_MAX (0xffff)
#define SOCP_DEC_DST_TH_MAX (0xff)

// 编码目的buffer上溢中断状态寄存器16-22位指示阈值溢出中断
#define SOCP_ENC_DST_BUFF_THRESHOLD_OVF_MASK    (0x007f0000)
#define SOCP_ENC_DST_BUFF_OVF_MASK              (0x0000007f)
// 阈值中断寄存器起始位
#define SOCP_ENC_DST_BUFF_THRESHOLD_OVF_BEGIN   (16)

#define SOCP_RESET_TIME (1000)
#define SOCP_GBLRESET_TIME (100)

/**************************************************************************
  通道最大值定义
**************************************************************************/
#define SOCP_MAX_ENCSRC_CHN             (0x20)
#define SOCP_MAX_ENCDST_CHN             (0x07)
#define SOCP_MAX_DECSRC_CHN             (0x04)
#define SOCP_MAX_DECDST_CHN             (0x10)

#define SOCP_ENCSRC_CHN_BASE            (4)
#define SOCP_ENCSRC_CHN_NUM             (5)

#define BBP_REG_ARM_BASEADDR            (HI_BBP_DMA_BASE_ADDR_VIRT)
#define SOCP_BBPDS_CHN_ADDR             (DDR_SOCP_ADDR)
#define SOCP_BBPDS_CHN_SIZE             (DDR_SOCP_SIZE)
#define SOCP_BBPLOG_CHN_SIZE            (0x2000)/*lint !e830*/
#define SOCP_DSPLOG_CHN                 (0x0e)         // 14
#define SOCP_BBPLOG_CHN                 (SOCP_DSPLOG_CHN + 2)  // 16开始，共8个
#define SOCP_BBPDS_CHN                  (SOCP_BBPLOG_CHN + 8)  // 24
#define SOCP_FIXCHN_BASE              (SOCP_DSPLOG_CHN)
#define SOCP_FIXCHN_END               (SOCP_BBPDS_CHN)

#define SOCP_CCORE_ENCSRC_CHN_BASE    (4)
#define SOCP_CCORE_ENCSRC_CHN_NUM     (5)



#define SOCP_DSPLOG_CHN_ADDR          (SOCP_DSP_CHN_ADDR)
#define SOCP_DSPLOG_CHN_SIZE          (SOCP_DSP_CHN_SIZE)

#define SOCP_BBPLOG0_CHN_SIZE         (0x2000*8)
#define SOCP_FIXEDID_BASE             (SOCP_DSPLOG_CHN - SOCP_FIXCHN_BASE)

#define SOCP_DSPLOG_DST_BUFID         ((s32) 1)
#define SOCP_BBPLOG_DST_BUFID         ((s32) 1)
#define SOCP_BBPDS_DST_BUFID          ((s32) 1)

/* 检测是否初始化的宏定义 */
#define SOCP_CHECK_INIT() \
    do {\
        if (!g_strSocpStat.bInitFlag)\
        {\
            socp_printf("the module has not been initialized!\n"); \
            return BSP_ERR_SOCP_NOT_INIT; \
        } \
    } while (0)

/* 检测参数是否有效 */
#define SOCP_CHECK_PARA(para) \
    do {\
        if (0 == para)\
        {\
            socp_printf("the parameter is NULL!\n"); \
            return BSP_ERR_SOCP_NULL; \
        } \
    } while (0)

#define SOCP_CHECK_BUF_ADDR(start, end) \
    do {\
        if (start >= end)\
        {\
            socp_printf("the buff is invalid!\n"); \
            return BSP_ERR_SOCP_INVALID_PARA; \
        } \
    } while (0)

#define SOCP_CHECK_CHAN_TYPE(para, type) \
    do {\
        if (type != para)\
        {\
            socp_printf("the Chan's Type is invalid!\n"); \
            return BSP_ERR_SOCP_INVALID_CHAN; \
        } \
    } while (0)

#define SOCP_CHECK_CHAN_ID(para, id) \
    do {\
        if (para >= id)\
        {\
            socp_printf("the Chan Id is invalid!\n"); \
            return BSP_ERR_SOCP_INVALID_CHAN; \
        } \
    } while (0)

#define SOCP_CHECK_ENCSRC_CHAN_ID(id) \
    do {\
        if ((id >= SOCP_CODER_SRC_BUTT))\
        {\
            socp_printf("the Chan Id is invalid!\n"); \
            return BSP_ERR_SOCP_INVALID_CHAN; \
        } \
    } while (0)

/* 检测是否8字节对齐 */
#define SOCP_CHECK_8BYTESALIGN(para) \
    do {\
        if (0 != (para % 8))\
        {\
            socp_printf("the parameter is not 8 bytes aligned!\n"); \
            return BSP_ERR_SOCP_NOT_8BYTESALIGN; \
        } \
    } while (0)

#define SOCP_CHECK_ENCSRC_CHNMODE(para) \
    do {\
        if (para >= SOCP_ENCSRC_CHNMODE_BUTT)\
        {\
            socp_printf("encoder src channele mode is %d, which is invalid!\n", para); \
            return BSP_ERR_SOCP_INVALID_PARA; \
        } \
    } while (0)

#define SOCP_CHECK_DECSRC_CHNMODE(para) \
    do {\
        if (para >= SOCP_DECSRC_CHNMODE_BUTT)\
        {\
            socp_printf("decoder dst channele mode is %d, which is invalid!\n", para); \
            return BSP_ERR_SOCP_INVALID_PARA; \
        } \
    } while (0)

#define SOCP_CHECK_CHAN_PRIORITY(para) \
    do {\
        if (para >= SOCP_CHAN_PRIORITY_BUTT)\
        {\
            socp_printf("encoder src channele priority is %d, which is invalid!\n", para); \
            return BSP_ERR_SOCP_INVALID_PARA; \
        } \
    } while (0)

#define SOCP_CHECK_DATA_TYPE(para) \
    do {\
        if (para >= SOCP_DATA_TYPE_BUTT)\
        {\
            socp_printf("channel data type is %d, which is invalid!\n", para); \
            return BSP_ERR_SOCP_INVALID_PARA; \
        } \
    } while (0)

#define SOCP_CHECK_ENCSRC_ALLOC(id) \
    do {\
        if (SOCP_CHN_ALLOCATED != g_strSocpStat.sEncSrcChan[id].u32AllocStat)\
        {\
            socp_printf("encoder src[%d] not allocated!\n", id); \
            return BSP_ERR_SOCP_INVALID_CHAN; \
        } \
    } while (0)

#define SOCP_CHECK_ENCDST_SET(id) \
    do {\
        if (SOCP_CHN_SET != g_strSocpStat.sEncDstChan[id].u32SetStat)\
        {\
            socp_printf("encoder dst[%d] set failed!\n", id); \
            return BSP_ERR_SOCP_INVALID_CHAN; \
        } \
    } while (0)

#define SOCP_CHECK_DECSRC_SET(id) \
    do {\
        if (SOCP_CHN_SET != g_strSocpStat.sDecSrcChan[id].u32SetStat)\
        {\
            socp_printf("decoder[%d] src set failed!\n", id); \
            return BSP_ERR_SOCP_INVALID_CHAN; \
        } \
    } while (0)

#define SOCP_CHECK_DECDST_ALLOC(id) \
    do {\
        if (SOCP_CHN_ALLOCATED != g_strSocpStat.sDecDstChan[id].u32AllocStat)\
        {\
            socp_printf("decoder dst[%d] alloc failed!\n", id); \
            return BSP_ERR_SOCP_INVALID_CHAN; \
        } \
    } while (0)

#define SOCP_CHECK_DATA_TYPE_EN(param) \
    do {\
        if (param >= SOCP_DATA_TYPE_EN_BUTT)\
        {\
            socp_printf("the data type en is valid, para is %d!\n", param); \
            return BSP_ERR_SOCP_INVALID_PARA; \
        } \
    } while (0)

#define SOCP_CHECK_ENC_DEBUG_EN(param) \
    do {\
        if (param >= SOCP_ENC_DEBUG_EN_BUTT)\
        {\
            socp_printf("the enc src debug en is invalid, para is %d!\n", param); \
            return BSP_ERR_SOCP_INVALID_PARA; \
        } \
    } while (0)

/**************************************************************************
  结构定义
**************************************************************************/

/* 通道状态结构体，共四类 */
typedef struct tagSOCP_RING_BUF_S
{
    u32 u32Start;
    u32 u32End;
    u32 u32Write;
    u32 u32Read;
    u32 u32Length;
    u32 u32IdleSize;
} SOCP_RING_BUF_S;

typedef struct tagSOCP_ENCSRC_CHAN_S
{
    u32                   u32ChanID;
    u32                   u32ChanEn;
    u32                   u32DestChanID;
    u32                   u32BypassEn;
    u32                   u32AllocStat;    /* 通道已经或没有分配的标识*/
    u32                   u32LastRdSize;
    u32                   u32RdThreshold;
    SOCP_ENCSRC_CHNMODE_ENUM_UIN32 eChnMode;      /* 数据结构类型 */
    SOCP_CHAN_PRIORITY_ENUM_UIN32  ePriority;
    SOCP_DATA_TYPE_ENUM_UIN32      eDataType;
    SOCP_DATA_TYPE_EN_ENUM_UIN32   eDataTypeEn;
    SOCP_ENC_DEBUG_EN_ENUM_UIN32   eDebugEn;
    SOCP_RING_BUF_S       sEncSrcBuf;
    SOCP_RING_BUF_S       sRdBuf;
    socp_event_cb         event_cb;
    socp_rd_cb            rd_cb;
} SOCP_ENCSRC_CHAN_S;

typedef struct tagSOCP_ENCSRC_FIXCHAN_S
{
    u32                   u32ChanID;
    u32                   u32ChanEn;
    u32                   u32DestChanID;
    SOCP_ENCSRC_CHNMODE_ENUM_UIN32 eChnMode;      /* 数据结构类型 */
    SOCP_CHAN_PRIORITY_ENUM_UIN32  ePriority;
    SOCP_DATA_TYPE_ENUM_UIN32      eDataType;
    SOCP_DATA_TYPE_EN_ENUM_UIN32   eDataTypeEn;
    SOCP_ENC_DEBUG_EN_ENUM_UIN32   eDebugEn;
    SOCP_RING_BUF_S       sEncSrcBuf;
    SOCP_RING_BUF_S       sRdBuf;
    socp_event_cb         event_cb;
    socp_rd_cb            rd_cb;
} SOCP_ENCSRC_FIXCHAN_S;

typedef struct tagSOCP_ENCDST_CHAN_S
{
    u32                   u32ChanID;
    u32                   u32SetStat;            /* 通道已经或没有配置的标识*/
    u32                   u32Thrh;               /* 阈值*/
    SOCP_RING_BUF_S       sEncDstBuf;
    SOCP_EVENT_ENUM_UIN32          eChnEvent;
    socp_event_cb         event_cb;
    socp_read_cb          read_cb;
} SOCP_ENCDST_CHAN_S;

typedef struct tagSOCP_DECSRC_CHAN_S
{
    u32                   u32ChanID;
    u32                   u32ChanEn;
    u32                   u32SetStat;      /* 通道已经或没有配置的标识*/
    u32                   u32RdThreshold;
    SOCP_DATA_TYPE_EN_ENUM_UIN32   eDataTypeEn;
    SOCP_DECSRC_CHNMODE_ENUM_UIN32 eChnMode;      /* 数据结构类型 */
    SOCP_RING_BUF_S       sDecSrcBuf;
    SOCP_RING_BUF_S       sDecRdBuf;
    socp_event_cb         event_cb;
    socp_rd_cb            rd_cb;
} SOCP_DECSRC_CHAN_S;

typedef struct tagSOCP_DECDST_CHAN_S
{
    u32          u32ChanID;
    u32          u32AllocStat;
    SOCP_DATA_TYPE_ENUM_UIN32 eDataType;
    SOCP_RING_BUF_S  sDecDstBuf;
    socp_event_cb    event_cb;
    socp_read_cb     read_cb;
} SOCP_DECDST_CHAN_S;

/* 全局状态结构体 */
typedef struct tagSOCP_GBL_STATE
{
    int                 bInitFlag;
    u32                 baseAddr;
    SOCP_ENCSRC_CHAN_S  sEncSrcChan[SOCP_MAX_ENCSRC_CHN];
} SOCP_GBL_STATE;

typedef struct tagSOCP_DEBUG_GBL_S
{
    u32 u32SocpAllocEncSrcCnt;         /* SOCP申请编码源通道的次数*/
    u32 u32SocpAllocEncSrcSucCnt;      /* SOCP申请编码源通道成功的次数*/
    u32 u32SocpModemEtrIntCnt;         /* 进入Modem中断的次数*/
    u32 u32SocpModemSucIntCnt;         /* 进入Modem中断处理成功的次数*/
} SOCP_DEBUG_GBL_S;

typedef struct tagSOCP_DEBUG_ENCSRC_S
{
    u32 u32SocpFreeEncSrcCnt[SOCP_MAX_ENCSRC_CHN];         /* SOCP释放编码源通道成功的次数*/
    u32 u32SocpSoftResetEncSrcCnt[SOCP_MAX_ENCSRC_CHN];    /* SOCP软复位编码源通道的次数*/
    u32 u32SocpStartEncSrcCnt[SOCP_MAX_ENCSRC_CHN];        /* SOCP启动编码源通道的次数*/
    u32 u32SocpStopEncSrcCnt[SOCP_MAX_ENCSRC_CHN];         /* SOCP关闭编码源通道的次数*/
    u32 u32SocpRegEventEncSrcCnt[SOCP_MAX_ENCSRC_CHN];     /* SOCP注册编码源通道事件的次数*/
    u32 u32SocpGetWBufEncSrcEtrCnt[SOCP_MAX_ENCSRC_CHN];      /* SOCP编码源通道尝试获得写buffer的次数*/
    u32 u32SocpGetWBufEncSrcSucCnt[SOCP_MAX_ENCSRC_CHN];      /* SOCP编码源通道成功获得写buffer的次数*/
    u32 u32socp_write_doneEncSrcEtrCnt[SOCP_MAX_ENCSRC_CHN];    /* SOCP编码源通道尝试写回buffer的次数*/
    u32 u32socp_write_doneEncSrcSucCnt[SOCP_MAX_ENCSRC_CHN];    /* SOCP编码源通道成功写回buffer的次数*/
    u32 u32socp_write_doneEncSrcFailCnt[SOCP_MAX_ENCSRC_CHN];    /* SOCP编码源通道写回buffer失败的次数*/
    u32 u32SocpRegRdCBEncSrcCnt[SOCP_MAX_ENCSRC_CHN];          /* SOCP注册编码源通道RDbuffer回调函数的次数*/
    u32 u32SocpGetRdBufEncSrcEtrCnt[SOCP_MAX_ENCSRC_CHN];     /* SOCP编码源通道尝试获得Rdbuffer的次数*/
    u32 u32SocpGetRdBufEncSrcSucCnt[SOCP_MAX_ENCSRC_CHN];     /* SOCP编码源通道成功获得Rdbuffer的次数*/
    u32 u32SocpReadRdDoneEncSrcEtrCnt[SOCP_MAX_ENCSRC_CHN];   /* SOCP编码源通道尝试写回Rdbuffer的次数*/
    u32 u32SocpReadRdDoneEncSrcSucCnt[SOCP_MAX_ENCSRC_CHN];   /* SOCP编码源通道成功写回Rdbuffer的次数*/
    u32 u32SocpReadRdDoneEncSrcFailCnt[SOCP_MAX_ENCSRC_CHN];   /* SOCP编码源通道写回Rdbuffer失败的次数*/
    u32 u32SocpEncSrcTskHeadCbCnt[SOCP_MAX_ENCSRC_CHN];      /* 任务中回调编码源通道包头错误中断处理函数完成的次数*/
    u32 u32SocpEncSrcTskHeadCbOriCnt[SOCP_MAX_ENCSRC_CHN];   /* 任务中回调编码源通道包头错误中断处理函数次数*/
    u32 u32SocpEncSrcTskRdCbCnt[SOCP_MAX_ENCSRC_CHN];        /* 任务中回调编码源通道Rd 完成中断处理函数完成的次数*/
    u32 u32SocpEncSrcTskRdCbOriCnt[SOCP_MAX_ENCSRC_CHN];     /* 任务中回调编码源通道Rd 完成中断处理函数次数*/
    u32 u32SocpEncSrcIsrHeadIntCnt[SOCP_MAX_ENCSRC_CHN];      /* ISR中进入编码源通道包头错误中断次数*/
    u32 u32SocpEncSrcIsrRdIntCnt[SOCP_MAX_ENCSRC_CHN];        /* ISR进入编码源通道Rd 完成中断次数*/
} SOCP_DEBUG_ENCSRC_S;

/* 调试信息*/
typedef struct tagSOCP_DEBUG_INFO_S
{
    SOCP_DEBUG_GBL_S    sSocpDebugGBl;
    SOCP_DEBUG_ENCSRC_S sSocpDebugEncSrc;
} SOCP_DEBUG_INFO_S;

/* 低功耗相关 begin */
typedef struct tagSOCP_DRX_ENCSRC_S
{
	u32 u32WriteAddr;
	u32 u32ReadAddr;
	u32 u32StartAddr;
	u32 u32Config0;
	u32 u32Config1;
	u32 u32RDWriteAddr;
	u32 u32RDReadAddr;
	u32 u32RDStartAddr;
	u32 u32RDConfig;
    u32 u32Dump[7];
}SOCP_DRX_ENCSRC_S;

typedef struct tagSOCP_DRX_ENCDST_S
{
	u32 u32WriteAddr;
	u32 u32ReadAddr;
	u32 u32StartAddr;
	u32 u32Config;
	u32 u32Thrh;
    u32 u32Dump[3];
}SOCP_DRX_ENCDST_S;


typedef struct tagSOCP_DRX_DECSRC_S
{
	u32 u32WriteAddr;
	u32 u32ReadAddr;
	u32 u32StartAddr;
	u32 u32Config;
       u32 u32Dump[12];
}SOCP_DRX_DECSRC_S;

typedef struct tagSOCP_DRX_DECDST_S
{
	u32 u32WriteAddr;
	u32 u32ReadAddr;
	u32 u32StartAddr;
	u32 u32Config;
}SOCP_DRX_DECDST_S;

typedef struct tagBBPDMA_DRX_LOG_S
{
	u32 u32StartAddr;
    u32 u32WriteAddr;
	u32 u32ReadAddr;
	u32 u32Config;
}BBPDMA_DRX_LOG_S;

typedef struct tagBBPDMA_DRX_DS_S
{
	u32 u32StartAddr;
    u32 u32WriteAddr;
	u32 u32ReadAddr;
	u32 u32Config;
    u32 u32RegStart;
    u32 u32ChEn;
}BBPDMA_DRX_DS_S;
/* 低功耗相关 end */

/**************************************************************************
  函数声明
**************************************************************************/
extern SOCP_GBL_STATE g_strSocpStat;/*lint !e830*/




#define SOCP_REG_WRITE(reg, data) (writel(data, (g_strSocpStat.baseAddr + reg)))
#define SOCP_REG_READ(reg, result) (result = readl(g_strSocpStat.baseAddr + reg))
#define SOCP_REG_SETBITS(reg, pos, bits, val) BSP_REG_SETBITS(g_strSocpStat.baseAddr, reg, pos, bits, val)
#define SOCP_REG_GETBITS(reg, pos, bits) BSP_REG_GETBITS(g_strSocpStat.baseAddr, reg, pos, bits)

#define BBP_REG_WRITE(reg, data) (writel(data, (BBP_REG_ARM_BASEADDR + reg)))
#define BBP_REG_READ(reg, result) (result = readl(BBP_REG_ARM_BASEADDR + reg))
#define BBP_REG_SETBITS(reg, pos, bits, val) BSP_REG_SETBITS(BBP_REG_ARM_BASEADDR, reg, pos, bits, val)
#define BBP_REG_GETBITS(reg, pos, bits) BSP_REG_GETBITS(BBP_REG_ARM_BASEADDR, reg, pos, bits)


//函数声明增加2013年11月23日14:22:24
void socp_get_idle_buffer(SOCP_RING_BUF_S *pRingBuffer, SOCP_BUFFER_RW_STRU *pRWBuffer);
void socp_get_data_buffer(SOCP_RING_BUF_S *pRingBuffer, SOCP_BUFFER_RW_STRU *pRWBuffer);
void get_socp_base(void);
void socp_write_done(SOCP_RING_BUF_S *pRingBuffer, u32 u32Size);
void socp_read_done(SOCP_RING_BUF_S *pRingBuffer, u32 u32Size);
s32 socp_reset_enc_chan(u32 u32ChanID);
u32 socp_get_enc_rd_size(u32 u32ChanID);
void socp_help(void);
void socp_show_debug_gbl(void);
u32 socp_show_enc_src_chan_cur(u32 u32UniqueId);/*lint !e830*/
u32 socp_show_enc_src_chan_add(u32 u32UniqueId);
void socp_show_enc_src_chan_all(void);
void socp_debug_cnt_show(void);
void  bsp_socp_enable_lte_dsp_bbp(u32 ulChanId);
u32  bsp_socp_init_lte_dsp(u32 ulChanId,u32 ulPhyAddr,u32 ulSize);
u32  bsp_socp_init_lte_bbp_log(u32 ulChanId,u32 ulPhyAddr,u32 ulSize);
u32  bsp_socp_int_lte_bbp_ds(u32 ulChanId,u32 ulPhyAddr,u32 ulSize);
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
s32 socp_icc_read_cb(u32 id, u32 len, void * context);
s32 socp_icc_chan_init(void);
#endif
int socp_debug_init(void);

#if defined(__KERNEL__)

#define Socp_Memcpy(dst,src,len)       (void)memcpy(dst,src,len)
#define Socp_Memset(src,count,len)     (void)memset(src,count,len)

#elif defined(__OS_VXWORKS__)

#define Socp_Memcpy(dst,src,len)       (void)memcpy(dst,src,len)
#define Socp_Memset(src,count,len)     (void)memset(src,count,len)

#elif defined(__OS_RTOSCK__)

#define Socp_Memcpy(dst,src,len)       (void)memcpy_s(dst,len,src,len)
#define Socp_Memset(src,count,len)     (void)memset_s(src, len, count,len)

#endif
#define socp_printf(fmt,...)     bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_SOCP,fmt,##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif
