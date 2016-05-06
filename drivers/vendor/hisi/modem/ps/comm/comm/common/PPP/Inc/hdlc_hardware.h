/*
 *
 * All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses. You may choose this file to be licensed under the terms
 * of the GNU General Public License (GPL) Version 2 or the 2-clause
 * BSD license listed below:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */


#ifndef __HDLC_HARDWARE_H__
#define __HDLC_HARDWARE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "product_config.h"

#include "PPP/Inc/hdlc_interface.h"
#include "TTFComm.h"
#include "TtfMemoryMap.h"
#include "soc_hdlc_interface.h"
#if (VOS_LINUX == VOS_OS_VER)
#include <linux/io.h>
#endif


#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#if (VOS_RTOSCK == VOS_OS_VER)
#define     PS_PID_PPP_HDLC                                     MSPS_PID_PPPC

#define     PPP_HDLC_WRITE_32REG(pAddr, value)                  TTF_WRITE_32REG(pAddr, value)
#define     PPP_HDLC_READ_32REG(pAddr)                          TTF_READ_32REG(pAddr)

#define     PPP_IO_ADDRESS(a)                                   (a)

#else
#define     PS_PID_PPP_HDLC                                     PS_PID_APP_PPP
#define     PPP_HDLC_WRITE_32REG(pAddr, value)                  writel(value, (volatile unsigned int *)pAddr)
#define     PPP_HDLC_READ_32REG(pAddr)                          readl((volatile unsigned int *)pAddr)

#define     PPP_HDLC_MEM_MAP_SIZE                               (4096)  /* 一个页表最小长度 */
#define     PPP_IO_ADDRESS(a)                                    ioremap((a),PPP_HDLC_MEM_MAP_SIZE)
#endif

/* 1.============================================================================================ */
/* definitions of bit basic operations */
#define GET_HIGH_WORD_FROM_DWORD(l)           ((VOS_UINT16)((((VOS_UINT32)(l)) >> 16) & 0xFFFF))
#define GET_LOW_WORD_FROM_DWORD(l)           ((VOS_UINT16)(VOS_UINT32)(l))
#define GET_HIGH_BYTE_FROM_WORD(w)           ((VOS_UINT8)(((VOS_UINT16)(w) >> 8) & 0xFF))
#define GET_LOW_BYTE_FROM_WORD(w)           ((VOS_UINT8)(w))
#define HDLC_MAKE_DWORD(hi,low)    ((VOS_UINT32)(((VOS_UINT16)(low))|(((VOS_UINT32)((VOS_UINT16)(hi)))<<16)))
#define HDLC_MAKE_WORD(hi,low)    ((VOS_UINT16)(((VOS_UINT8)(low))|(((VOS_UINT16)((VOS_UINT8)(hi)))<<8)))

#define GET_BITS_FROM_DWORD(DWord, BitMask) ((DWord) & (BitMask))
#define GET_BITS_FROM_WORD(Word, BitMask) ((Word) & (BitMask))
#define GET_BITS_FROM_BYTE(Byte, BitMask)  ((Byte) & (BitMask))
#define SET_BITS_VALUE_TO_BYTE(ucValue, ucStartBitPosition)     ((VOS_UINT8)(((VOS_UINT32)(ucValue)) << (ucStartBitPosition)))

#define SET_BIT_TO_BYTE(ucByte, ucBitPosition)          ((ucByte) |= (0x01 << (ucBitPosition)))
#define CLEAR_BIT_TO_BYTE(ucByte, ucBitPosition)        ((ucByte) &= ~(0x01 << (ucBitPosition)))

#define SET_BIT_TO_WORD(usWord, ucBitPosition)          ((usWord) |= (0x0001 << (ucBitPosition)))
#define CLEAR_BIT_TO_WORD(usWord, ucBitPosition)        ((usWord) &= ~(0x0001 << (ucBitPosition)))

#define SET_BIT_TO_DWORD(ulDWord, ucBitPosition)        ((ulDWord) |= (0x00000001 << (ucBitPosition)))
#define CLEAR_BIT_TO_DWORD(ulDWord, ucBitPosition)      ((ulDWord) &= ~(0x00000001 << (ucBitPosition)))

#define INSERT_BYTE_LAST(pstMem, pstData, usLen, byte) \
{ \
    pstData[usLen]     = pstData[usLen - 1]; \
    pstData[usLen - 1] = byte; \
    PPP_ZC_SET_DATA_LEN(pstMem, 1); \
}
/* 2.============================================================================================ */

/* definition of bit positions and masks in a register */
/* ========================= 1.hdlc_frm_en (0x10) begin ======================= */
/*
   定义寄存器在32bit Reg中的bit位置:
        寄存器frm_en在bit0;
*/
#define     HDLC_FRM_EN_BITPOS                                      (0UL)

/* ========================= 2.hdlc_def_en (0x60) begin ======================= */
/*
   定义寄存器在32bit Reg中的bit位置:
        寄存器def_en在bit0;
*/
#define     HDLC_DEF_EN_BITPOS                                      (0UL)

/* ========================= 3.hdlc_frm_cfg (0x20) begin ======================= */
/*
   定义寄存器在32bit Reg中的bit位置:
        寄存器frm_in_lli_1dor2d在bit0;
        寄存器frm_acfc在bit1;
*/
#define     HDLC_FRM_IN_LLI_1DOR2D_BITPOS                           (0UL)
#define     HDLC_FRM_ACFC_BITPOS                                    (1UL)
#define     HDLC_FRM_PFC_BITPOS                                     (2UL)

/*
   寄存器frm_pfc(2bits)各值含义:
        00b: 硬件模块添加P域, P域无压缩;
        01b: 硬件模块添加P域, P域压缩;
        11b: 硬件模块不添加P域;
*/
#define     HDLC_PROTOCOL_ADD_WITHOUT_COMPRESS   (0x00)
#define     HDLC_PROTOCOL_ADD_WITH_COMPRESS      (0x01)
#define     HDLC_PROTOCOL_NO_ADD                 (0x03)

/* ========================= 4.hdlc_def_cfg (0x70) begin ======================= */
/*
   定义寄存器在32bit Reg中的bit位置:
        寄存器def_uncompleted_ago在bit0;
        寄存器def_acfc在bit1;
*/
#define     HDLC_DEF_IS_UNCOMPLETED_AGO_BITPOS                      (0UL)
#define     HDLC_DEF_ACFC_BITPOS                                    (1UL)
#define     HDLC_DEF_PFC_BITPOS                                     (2UL)


/* 寄存器frm_protocol(16bits)的MASK表 */
#define     HDLC_FRM_PROTOCOL_MASK                       (0x0000FFFF)

/*
   寄存器def_pfc(2bits)各值含义:
        00b: P域无压缩, 需剥离;
        01b: P域压缩, 需剥离;
        11b: P域不剥离;
*/
#define     HDLC_PROTOCOL_REMOVE_WITHOUT_COMPRESS      (0x00)
#define     HDLC_PROTOCOL_REMOVE_WITH_COMPRESS         (0x01)
#define     HDLC_PROTOCOL_NO_REMOVE                    (0x03)

/* ========================= hdlc_prior_ctrl (0x04) begin ======================= */
/*
   寄存器hdlc_prior_ctrl(2bits)各值含义:
        00b: 谁先被使能则先将谁处理完;
        01b: 下行封装优先级高;
        10b: 上行解封装优先级高;
        11b: 无效;
*/
#define     HDLC_PRIOR_FCFS               (0x00)
#define     HDLC_PRIOR_DL_FRM_HIGHER      (0x01)
#define     HDLC_PRIOR_UL_DEF_HIGHER      (0x02)
#define     HDLC_PRIOR_INVALID            (0x03)

/* ====================== 封装状态寄存器地址 hdlc_frm_status (0x28) begin ====================== */
/* 封装模块状态寄存器地址: 相对偏移地址量0x28 */

/* 寄存器frm_out_seg_num(16bits)的MASK表 */
#define     HDLC_FRM_OUT_SEG_NUM_MASK                       (0x0000FFFF)

/* 寄存器frm_valid_num(8bits)的MASK表 */
#define     HDLC_FRM_VALID_NUM_MASK                         (0x000000FF)

/* 寄存器frm_all_pkt_done(1bit)的MASK表 */
#define     HDLC_FRM_ALL_PKT_DONE_MASK                      (0x00000001)

/* 查询封装状态信息的掩码 */
#define     HDLC_FRM_STATUS_MASK                            (0x00000003)

/*
   寄存器frm_block_done([0]位)各值含义:
        0b: 未完成一套链表数据处理;
        1b: 完成一套链表数据处理;
*/
/*
   寄存器frm_error_index([1]位)各值含义:
        1b: 封装发生错误;
*/
#define     HDLC_FRM_ALL_PKT_DOING                     (0x00)
#define     HDLC_FRM_ALL_PKT_DONE                      (0x01)
#define     HDLC_FRM_STOP_EXCEPTION_OCCUR              (0x02)
#define     HDLC_FRM_DONE_EXCEPTION_OCCUR              (0x03)




/* ======================= 解封装状态寄存器地址dlc_def_status (0x88) begin ===================== */
/* 寄存器dlc_def_status(5bits)的MASK表 */
#define     HDLC_DEFRAMER_BLOCK_STATUS_MASK                     (0x0000001B)

/* 查询解封装状态信息的掩码 */
#define     HDLC_DEF_STATUS_MASK                                (0x0000003B)

/*
   寄存器dlc_def_status(5bits)各值含义:
        000000b: 未完成一组数据处理;
        010000b: 未完成一组数据处理，解封装外部正确帧信息上报空间存满暂停;
        001000b: 未完成一组数据处理, 解封装外部输出存储空间存满暂停;
        000001b: 未完成一组数据处理, 已解出LCP帧, 硬件处于暂停状态;
        000010b: 完成一组数据处理, 但无帧上报;
        000011b: 完成一组数据处理, 且有帧上报;
        1xx0xxb: 有异常发生;
*/
#define     HDLC_DEF_STATUS_DOING                               (0x00)
#define     HDLC_DEF_STATUS_PAUSE_RPT_SPACE_FULL                (0x10)
#define     HDLC_DEF_STATUS_PAUSE_OUTPUT_SPACE_FULL             (0x08)
#define     HDLC_DEF_STATUS_PAUSE_LCP                           (0x01)
#define     HDLC_DEF_STATUS_DONE_WITHOUT_FRAMES                 (0x02)
#define     HDLC_DEF_STATUS_DONE_WITH_FRAMES                    (0x03)

/* 3.============================================================================================ */
/* definition of HDLC module: FRAMER, DEFRAMER */
#define     HDLC_FRM_MODULE                                     (0UL)
#define     HDLC_DEF_MODULE                                     (1UL)

/* definition of PPP Link type */
#define     HDLC_IP_MODE                                        (0UL)
#define     HDLC_PPP_MODE                                       (1UL)

/* 解封装是否有非完整帧标识 */
#define     HDLC_DEF_UNCOMPLETED_NOT_EXIST                      (0x0)
#define     HDLC_DEF_UNCOMPLETED_EXIST                          (0x1)

#define     HDLC_INPUT_PARA_LINK_MAX_SIZE                       (TTF_MAX(TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_NUM, TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM))
#define     HDLC_OUTPUT_PARA_LINK_MAX_SIZE                      (TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM)

/* 根据PPP ID获取对应内存，暂时只有一路，填为定值，后续可能有多路 */
#define     HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId)              (&g_stUncompletedInfo)
#define     HDLC_DEF_GET_BUF_INFO(usPppId)                      (g_pstHdlcDefBufInfo)
#define     HDLC_FRM_GET_BUF_INFO(usPppId)                      (g_pstHdlcFrmBufInfo)

/* 解封装输出空间首、尾地址，用于判断是否绕回 */
#define     HDLC_DEF_OUTPUT_BUF_START_ADDR                      ((VOS_UINT8 *)(&g_pstHdlcDefBufInfo->aucOutputDataBuf[0]))
#define     HDLC_DEF_OUTPUT_BUF_END_ADDR                        (HDLC_DEF_OUTPUT_BUF_START_ADDR + TTF_HDLC_DEF_OUTPUT_DATA_BUF_LEN)

/* 轮询封装或解封装完成的次数 */
#ifndef  __UT_CENTER__
#define     HDLC_FRM_MAX_WAIT_RESULT_NUM                        (0xFFFF)
#define     HDLC_DEF_MAX_WAIT_RESULT_NUM                        (0xFFFF)
#else
#define     HDLC_FRM_MAX_WAIT_RESULT_NUM                        (0x01)
#define     HDLC_DEF_MAX_WAIT_RESULT_NUM                        (0x01)
#endif

/* 等待封装或解封装响应中断时间,以毫秒为单位 */
#define     HDLC_FRM_MASTER_INT_TIMER_LEN                       (5000)
#define     HDLC_DEF_MASTER_INT_TIMER_LEN                       (5000)

/* 约定软硬件, 封装一组最多提交1502字节给Framer */
#define     HDLC_FRM_IN_PER_MAX_CNT                             (1502L)
#define     HDLC_FRM_OUT_PER_MAX_CNT                            (3013UL)

/* 解封装最大单个数据长度,规避HDLC BUG,最大长度需要+1,但在C核中,长度不会增加 */
#if (VOS_RTOSCK == VOS_OS_VER)
#define     PPP_ZC_MAX_DATA_LEN                                 (1536)            /* 可申请内存块最大长度 */
#define     HDLC_DEF_IN_PER_MAX_CNT                             (PPP_ZC_MAX_DATA_LEN)
#else
#define     HDLC_DEF_IN_PER_MAX_CNT                             (PPP_ZC_MAX_DATA_LEN + 1)
#endif

/* 解封装上报每帧最长1502字节, IPv4最长1500字节, PPP模式带上协议字段2字节, 共1502字节 */
#define     HDLC_DEF_OUT_PER_MAX_CNT                            (1502UL)

/* 申请封装目的空间失败定时器时长,单位毫秒 */
#define     HDLC_FRM_TIME_INTERVAL                              (100)

/* 申请封装目的空间失败定时器参数 */
#if (VOS_RTOSCK == VOS_OS_VER)
#define     HDLC_FRM_OUTPUT_SPACE_ALLOC_FAIL                    (PPPC_HDLC_FRM_OUTPUT_SPACE_ALLOC_FAIL)
#else
#define     HDLC_FRM_OUTPUT_SPACE_ALLOC_FAIL                    (10)
#endif

/* 封装后内存最大值 */
#define     HDLC_FRM_GET_MAX_FRAMED_LEN(usLen)                  (2*usLen + 13)

/* 采用轮询还是中断使能的水线，默认值 */
#define     HDLC_DEF_INTERRUPT_LIMIT_DEFAULT                    (2*1024)
#define     HDLC_FRM_INTERRUPT_LIMIT_DEFAULT                    (2*1024)

/* 采用轮询还是中断使能的水线 */
#if (VOS_OS_VER == VOS_WIN32)
/* PC上无法模拟中断，都使用查询 */
#define     HDLC_DEF_INTERRUPT_LIMIT                            (TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE + 1)
#define     HDLC_FRM_INTERRUPT_LIMIT                            (TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_SIZE + 1)
#else
#define     HDLC_DEF_INTERRUPT_LIMIT                            (g_stHdlcConfigInfo.ulHdlcDefIntLimit)
#define     HDLC_FRM_INTERRUPT_LIMIT                            (g_stHdlcConfigInfo.ulHdlcFrmIntLimit)
#endif

/* AXI总线读写请求超时的判断值，该值由SoC提供，软件负责配置 */
#define     HDLC_AXI_REQ_TIMEOUT_VALUE                          (255)

/* 解封装错误类型个数 */
#define     HDLC_DEF_MAX_TYPE_CNT                               (7UL)

/* 可维可测申请的内存最大长度，防止因为可维可测申请不到内存导致单板复位 */
#define     HDLC_MNTN_ALLOC_MEM_MAX_SIZE                        (2*1024)

/*
   定义异常信息bit位置:
        bit0代表是否进入异常处理(1是进入异常处理，0是没有进入异常处理);
        bit1代表是否是中断处理(1是中断处理，0是轮询处理);
        bit2代表是否等待信号量超时(1是，0否);
        bit3代表是否轮询超时(1是，0否);
*/
#define     HDLC_EXCEPTION_IND_BITPOS                           (0UL)
#define     HDLC_INTERRUPT_IND_BITPOS                           (1UL)
#define     HDLC_SEM_TIMEOUT_IND_BITPOS                         (2UL)
#define     HDLC_WAIT_STATUS_TIMEOUT_IND_BITPOS                 (3UL)

#define     PPP_HDLC_CACHE_INVALID(data, len)                   dma_map_single(0, data, len, DMA_FROM_DEVICE)
#define     PPP_HDLC_CACHE_FLUSH(data, len)                     dma_map_single(0, data, len, DMA_TO_DEVICE)

/* =========V3R3中使用: HDLC时钟在寄存器SC_PERIPH_CLKEN0 和 C_PERIPH_CLKDIS0 16bit的位置======== */
#define     HDLC_PERIPH_CLK_BITPOS                              (16UL)

#if (SC_CTRL_MOD_6250_SFT == SC_CTRL_MOD)
/* =========dallas中使用: HDLC时钟在寄存器CRG_CLKEN4 和 CRG_CLKDIS4 24bit的位置======== */
#define     HDLC_CRG_CLK_BITPOS                                 (24UL)

#else
/* =========V7R2中使用: HDLC时钟在寄存器CRG_CLKEN4 和 CRG_CLKDIS4 10bit的位置======== */
#define     HDLC_CRG_CLK_BITPOS                                 (10UL)

#endif

#if (SC_CTRL_MOD_P532 == SC_CTRL_MOD)
#define     HDLC_CRG_CLKEN_OFFSET                               (0x24)      /* HDLC时钟使能OFFSET */
#define     HDLC_CRG_CLKDIS_OFFSET                              (0x28)      /* HDLC时钟关闭OFFSET */
#define     HDLC_CRG_CLKSTAT_OFFSET                             (0x2C)      /* HDLC时钟状态OFFSET */

#elif ((SC_CTRL_MOD_6950_SFT == SC_CTRL_MOD) || (SC_CTRL_MOD_6932_SFT == SC_CTRL_MOD))
#define     HDLC_CRG_CLKEN_OFFSET                               (0x30)      /* HDLC时钟使能OFFSET */
#define     HDLC_CRG_CLKDIS_OFFSET                              (0x34)      /* HDLC时钟关闭OFFSET */
#define     HDLC_CRG_CLKSTAT_OFFSET                             (0x38)      /* HDLC时钟状态OFFSET */

#elif (SC_CTRL_MOD_6250_SFT == SC_CTRL_MOD)
/* =========dallas中使用: HDLC时钟使能控制寄存器MDM_CRG_CLKEN0、
                          HDLC时钟关闭控制寄存器MDM_CRG_CLKDIS0、
                          HDLC时钟控制状态MDM_CRG_CLKSTAT0相对基地址的偏移======== */
#define     HDLC_CRG_CLKEN_OFFSET                               (0x00)      /* HDLC时钟使能OFFSET */
#define     HDLC_CRG_CLKDIS_OFFSET                              (0x04)      /* HDLC时钟关闭OFFSET */
#define     HDLC_CRG_CLKSTAT_OFFSET                             (0x08)      /* HDLC时钟状态OFFSET */

#else
#define     HDLC_CRG_CLKEN_OFFSET                               (0x30)      /* HDLC时钟使能OFFSET */
#define     HDLC_CRG_CLKDIS_OFFSET                              (0x34)      /* HDLC时钟关闭OFFSET */
#define     HDLC_CRG_CLKSTAT_OFFSET                             (0x38)      /* HDLC时钟状态OFFSET */

#endif

/* =========时钟使能寄存器======== */
#define     HDLC_CRG_CLKEN4_ADDR(base)                          ((base) + (HDLC_CRG_CLKEN_OFFSET))

/* =========时钟关闭寄存器======== */
#define     HDLC_CRG_CLKENDIS4_ADDR(base)                       ((base) + (HDLC_CRG_CLKDIS_OFFSET))

/* =========时钟状态寄存器======== */
#define     HDLC_CRG_CLKSTA4_ADDR(base)                         ((base) + (HDLC_CRG_CLKSTAT_OFFSET))

#define     HDLC_DMA_VIRT_TO_PHY(ulVirtAddr)                    ((ulVirtAddr) - (g_ulPppVirtAddr) + (g_ulPppPhyAddr))
#define     HDLC_DMA_PHY_TO_VIRT(ulPhyAddr)                     ((ulPhyAddr) - (g_ulPppPhyAddr) + (g_ulPppVirtAddr))


#if (VOS_RTOSCK== VOS_OS_VER)
#define PPP_HDLC_INFO_LOG(String) \
            PPPC_INFO_LOG(String)
#define PPP_HDLC_INFO_LOG1(String, Para1) \
            PPPC_INFO_LOG1(String, Para1)
#define PPP_HDLC_INFO_LOG2(String, Para1, Para2) \
            PPPC_INFO_LOG2(String, Para1, Para2)
#define PPP_HDLC_INFO_LOG3(String, Para1, Para2, Para3) \
            PPPC_INFO_LOG3(String, Para1, Para2, Para3)
#define PPP_HDLC_INFO_LOG4(String, Para1, Para2, Para3, Para4) \
            PPPC_INFO_LOG4(String, Para1, Para2, Para3, Para4)
#define PPP_HDLC_NORMAL_LOG(String) \
            PPPC_WARNING_LOG(String)
#define PPP_HDLC_NORMAL_LOG1(String, Para1) \
            PPPC_WARNING_LOG1(String, Para1)
#define PPP_HDLC_NORMAL_LOG2(String, Para1, Para2) \
            PPPC_WARNING_LOG2(String, Para1, Para2)
#define PPP_HDLC_NORMAL_LOG3(String, Para1, Para2, Para3) \
            PPPC_WARNING_LOG3(String, Para1, Para2, Para3)
#define PPP_HDLC_NORMAL_LOG4(String, Para1, Para2, Para3, Para4) \
            PPPC_WARNING_LOG4(String, Para1, Para2, Para3, Para4)
#define PPP_HDLC_WARNING_LOG(String) \
            PPPC_WARNING_LOG(String)
#define PPP_HDLC_WARNING_LOG1(String, Para1) \
            PPPC_WARNING_LOG1(String, Para1)
#define PPP_HDLC_WARNING_LOG2(String, Para1, Para2) \
            PPPC_WARNING_LOG2(String, Para1, Para2)
#define PPP_HDLC_WARNING_LOG3(String, Para1, Para2, Para3) \
            PPPC_WARNING_LOG3(String, Para1, Para2, Para3)
#define PPP_HDLC_WARNING_LOG4(String, Para1, Para2, Para3, Para4) \
            PPPC_WARNING_LOG4(String, Para1, Para2, Para3, Para4)
#define PPP_HDLC_ERROR_LOG(String) \
            PPPC_ERROR_LOG(String)
#define PPP_HDLC_ERROR_LOG1(String, Para1) \
            PPPC_ERROR_LOG1(String, Para1)
#define PPP_HDLC_ERROR_LOG2(String, Para1, Para2) \
            PPPC_ERROR_LOG2(String, Para1, Para2)
#define PPP_HDLC_ERROR_LOG3(String, Para1, Para2, Para3) \
            PPPC_ERROR_LOG3(String, Para1, Para2, Para3)
#define PPP_HDLC_ERROR_LOG4(String, Para1, Para2, Para3, Para4) \
            PPPC_ERROR_LOG4(String, Para1, Para2, Para3, Para4)
#else
#define PPP_HDLC_INFO_LOG(String) \
            PPP_MNTN_LOG(PS_PID_PPP_HDLC, 0, PS_PRINT_INFO, String)
#define PPP_HDLC_INFO_LOG1(String, Para1) \
            PPP_MNTN_LOG1(PS_PID_PPP_HDLC, 0, PS_PRINT_INFO, String, Para1)
#define PPP_HDLC_INFO_LOG2(String, Para1, Para2) \
            PPP_MNTN_LOG2(PS_PID_PPP_HDLC, 0, PS_PRINT_INFO, String, Para1, Para2)
#define PPP_HDLC_INFO_LOG3(String, Para1, Para2, Para3) \
            PPP_MNTN_LOG3(PS_PID_PPP_HDLC, 0, PS_PRINT_INFO, String, Para1, Para2, Para3)
#define PPP_HDLC_INFO_LOG4(String, Para1, Para2, Para3, Para4) \
            PPP_MNTN_LOG4(PS_PID_PPP_HDLC, 0, PS_PRINT_INFO, String, Para1, Para2, Para3, Para4)
#define PPP_HDLC_NORMAL_LOG(String) \
            PPP_MNTN_LOG(PS_PID_PPP_HDLC, 0, PS_PRINT_NORMAL, String)
#define PPP_HDLC_NORMAL_LOG1(String, Para1) \
            PPP_MNTN_LOG1(PS_PID_PPP_HDLC, 0, PS_PRINT_NORMAL, String, Para1)
#define PPP_HDLC_NORMAL_LOG2(String, Para1, Para2) \
            PPP_MNTN_LOG2(PS_PID_PPP_HDLC, 0, PS_PRINT_NORMAL, String, Para1, Para2)
#define PPP_HDLC_NORMAL_LOG3(String, Para1, Para2, Para3) \
            PPP_MNTN_LOG3(PS_PID_PPP_HDLC, 0, PS_PRINT_NORMAL, String, Para1, Para2, Para3)
#define PPP_HDLC_NORMAL_LOG4(String, Para1, Para2, Para3, Para4) \
            PPP_MNTN_LOG4(PS_PID_PPP_HDLC, 0, PS_PRINT_NORMAL, String, Para1, Para2, Para3, Para4)
#define PPP_HDLC_WARNING_LOG(String) \
            PPP_MNTN_LOG(PS_PID_PPP_HDLC, 0, PS_PRINT_WARNING, String)
#define PPP_HDLC_WARNING_LOG1(String, Para1) \
            PPP_MNTN_LOG1(PS_PID_PPP_HDLC, 0, PS_PRINT_WARNING, String, Para1)
#define PPP_HDLC_WARNING_LOG2(String, Para1, Para2) \
            PPP_MNTN_LOG2(PS_PID_PPP_HDLC, 0, PS_PRINT_WARNING, String, Para1, Para2)
#define PPP_HDLC_WARNING_LOG3(String, Para1, Para2, Para3) \
            PPP_MNTN_LOG3(PS_PID_PPP_HDLC, 0, PS_PRINT_WARNING, String, Para1, Para2, Para3)
#define PPP_HDLC_WARNING_LOG4(String, Para1, Para2, Para3, Para4) \
            PPP_MNTN_LOG4(PS_PID_PPP_HDLC, 0, PS_PRINT_WARNING, String, Para1, Para2, Para3, Para4)
#define PPP_HDLC_ERROR_LOG(String) \
            PPP_MNTN_LOG(PS_PID_PPP_HDLC, 0, PS_PRINT_ERROR, String)
#define PPP_HDLC_ERROR_LOG1(String, Para1) \
            PPP_MNTN_LOG1(PS_PID_PPP_HDLC, 0, PS_PRINT_ERROR, String, Para1)
#define PPP_HDLC_ERROR_LOG2(String, Para1, Para2) \
            PPP_MNTN_LOG2(PS_PID_PPP_HDLC, 0, PS_PRINT_ERROR, String, Para1, Para2)
#define PPP_HDLC_ERROR_LOG3(String, Para1, Para2, Para3) \
            PPP_MNTN_LOG3(PS_PID_PPP_HDLC, 0, PS_PRINT_ERROR, String, Para1, Para2, Para3)
#define PPP_HDLC_ERROR_LOG4(String, Para1, Para2, Para3, Para4) \
            PPP_MNTN_LOG4(PS_PID_PPP_HDLC, 0, PS_PRINT_ERROR, String, Para1, Para2, Para3, Para4)
#endif


/*******************************************************************************
  3 枚举定义
*******************************************************************************/
enum PPP_HDLC_PARA_CHECK_RESULT_ENUM
{
    PPP_HDLC_PARA_CHECK_PASS            = 0,      /* 参数符合要求，将该数据出队 */
    PPP_HDLC_PARA_CHECK_FAIL_DISCARD    = 1,      /* 数据包参数不符合要求，需要丢弃，但是继续处理下一个数据包 */
    PPP_HDLC_PARA_CHECK_FAIL_KEEP       = 2,      /* 数据包参数不符合要求，但需要保留，用于下次处理 */

    PPP_HDLC_PARA_CHECK_BUTT
};
typedef VOS_UINT32   PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32;

enum HDLC_MNTN_EVENT_TYPE_ENUM
{
    ID_HDLC_MNTN_FRM_REG_BEFORE_EN     = 101,     /* _H2ASN_MsgChoice HDLC_MNTN_FRM_REG_CONFIG_STRU */
    ID_HDLC_MNTN_FRM_REG_AFTER_EN,                /* _H2ASN_MsgChoice HDLC_MNTN_FRM_REG_CONFIG_STRU */
    ID_HDLC_MNTN_FRM_INPUT_PARA,                  /* _H2ASN_MsgChoice HDLC_MNTN_INPUT_PARA_LINK_STRU */
    ID_HDLC_MNTN_FRM_OUTPUT_PARA,                 /* _H2ASN_MsgChoice HDLC_MNTN_FRM_OUTPUT_PARA_STRU */
    ID_HDLC_MNTN_FRM_INPUT_DATA,                  /* _H2ASN_MsgChoice HDLC_MNTN_NODE_DATA_STRU */
    ID_HDLC_MNTN_FRM_OUTPUT_DATA,                 /* _H2ASN_MsgChoice HDLC_MNTN_NODE_DATA_STRU */
    ID_HDLC_MNTN_DEF_REG_BEFORE_EN,               /* _H2ASN_MsgChoice HDLC_MNTN_DEF_REG_CONFIG_STRU */
    ID_HDLC_MNTN_DEF_REG_AFTER_EN,                /* _H2ASN_MsgChoice HDLC_MNTN_DEF_REG_CONFIG_STRU */
    ID_HDLC_MNTN_DEF_INPUT_PARA,                  /* _H2ASN_MsgChoice HDLC_MNTN_INPUT_PARA_LINK_STRU */
    ID_HDLC_MNTN_DEF_OUTPUT_PARA,                 /* _H2ASN_MsgChoice HDLC_MNTN_DEF_OUTPUT_PARA_STRU */
    ID_HDLC_MNTN_DEF_INPUT_DATA,                  /* _H2ASN_MsgChoice HDLC_MNTN_NODE_DATA_STRU */
    ID_HDLC_MNTN_DEF_OUTPUT_DATA,                 /* _H2ASN_MsgChoice HDLC_MNTN_NODE_DATA_STRU */
    ID_HDLC_MNTN_DEF_UNCOMPLETED_INFO,            /* _H2ASN_MsgChoice HDLC_MNTN_DEF_UNCOMPLETED_INFO_STRU */

    ID_HDLC_MNTN_EVENT_TYPE_BUTT         = 0xFFFF
};
typedef VOS_UINT32 HDLC_MNTN_EVENT_TYPE_ENUM_UINT32;

/*****************************************************************************
  4 消息头和消息类型定义
*****************************************************************************/

/*****************************************************************************
  5 STRUCT定义
*****************************************************************************/
/* 一组数据解出的错误帧数统计 */
typedef struct
{
    VOS_UINT16  usFCSErrCnt;          /* FCS错误 */
    VOS_UINT16  usLenLongCnt;         /* 帧长度过长, 超过1502字节 */
    VOS_UINT16  usLenShortCnt;        /* 帧长度过短, 少于4字节 */
    VOS_UINT16  usErrProtocolCnt;     /* 协议字段不满足xxxxxxx0, xxxxxxx1的形式 */
    VOS_UINT16  usErrCtrlCnt;         /* 控制字段不为0xFF */
    VOS_UINT16  usErrAddrCnt;         /* 地址字段不为0x03 */
    VOS_UINT16  usFlagPosErrCnt;      /* 0x7D后紧接着0x7E */
    VOS_UINT8   aucReserve[2];
} HDLC_DEF_ERR_FRAMES_CNT_STRU;

/*
   参数链表节点结构:
   软件保证解封装输入链表参数起始地址Word对齐；(参见HiHDLCV200逻辑需求规格说明书)，
   从上到下，地址增加，分别为节点内存指针、节点长度、下个节点地址；
   长度LEN有效16bits处于低Half_Word；地址ADDR 32bits
*/
typedef struct _HDLC_PARA_LINK_NODE_STRU
{
    VOS_UINT8                          *pucDataAddr;            /* 该参数节点指向内存地址 */
    VOS_UINT16                          usDataLen;              /* 内存长度，单位Byte */
    VOS_UINT8                           aucReserve[2];
    struct _HDLC_PARA_LINK_NODE_STRU   *pstNextNode;            /* 指向下一个参数节点的指针 */
} HDLC_PARA_LINK_NODE_STRU;

#if (VOS_RTOSCK == VOS_OS_VER)
/* 构造参数链表结果信息 */
typedef struct _HDLC_PARA_LINK_BUILD_PARA_STRU
{
    PPP_DATA_TYPE_ENUM_UINT8            ucDataType;             /* 数据类型 */
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT16                          usPppId;                /* PPP ID */
    VOS_UINT16                          usProtocol;             /* 协议类型，封装的时候使用 */
    TTF_LINK_ST                        *pstDlDataQ;             /* 下行数据队列 */
    TTF_LINK_ST                        *pstUlDataQ;             /* 上行数据队列 */
} HDLC_PARA_LINK_BUILD_PARA_STRU;

/* 构造参数链表结果信息 */
/*lint -e506*/
typedef struct _HDLC_PARA_LINK_BUILD_INFO_STRU
{
    VOS_UINT32                          ulDealCnt;              /* 本次构造链表过程从数据队列中总共处理的数据包个数 */
    VOS_UINT8                           ucRatMode;              /* 速率模式1X/HRPD */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulInputLinkNodeCnt;     /* 输入参数链表节点个数 */
    VOS_UINT32                          ulInputLinkTotalSize;   /* 输入参数链表节点数据包总长度 */
    PPPC_DATA_LINK_NODE_STRU           *apstInputLinkNode[HDLC_INPUT_PARA_LINK_MAX_SIZE];   /* 输入参数链表节点对应的零拷贝内存 */
    VOS_UINT32                          ulOutputLinkNodeCnt;                                /* 输出参数链表节点个数，只在封装有效 */
    VOS_UINT32                          ulOutputLinkTotalSize;                              /* 输出参数链表节点数据包总长度，只在封装有效 */
    PPPC_DATA_LINK_NODE_STRU           *apstOutputLinkNode[HDLC_OUTPUT_PARA_LINK_MAX_SIZE]; /* 输出参数链表节点对应的零拷贝内存，只在封装有效 */
} HDLC_PARA_LINK_BUILD_INFO_STRU;
/*lint +e506*/
#else
/* 构造参数链表结果信息 */
typedef struct _HDLC_PARA_LINK_BUILD_PARA_STRU
{
    PPP_DATA_TYPE_ENUM_UINT8            ucDataType;             /* 数据类型 */
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT16                          usPppId;                /* PPP ID */
    VOS_UINT16                          usProtocol;             /* 协议类型，封装的时候使用 */
    PPP_ZC_QUEUE_STRU                  *pstDataQ;               /* 数据队列 */
} HDLC_PARA_LINK_BUILD_PARA_STRU;

/* 构造参数链表结果信息 */
/*lint -e506*/
typedef struct _HDLC_PARA_LINK_BUILD_INFO_STRU
{
    VOS_UINT32                          ulDealCnt;              /* 本次构造链表过程从数据队列中总共处理的数据包个数 */
    VOS_UINT32                          ulInputLinkNodeCnt;     /* 输入参数链表节点个数 */
    VOS_UINT32                          ulInputLinkTotalSize;   /* 输入参数链表节点数据包总长度 */
    PPP_ZC_STRU *                       apstInputLinkNode[HDLC_INPUT_PARA_LINK_MAX_SIZE];   /* 输入参数链表节点对应的零拷贝内存 */
    VOS_UINT32                          ulOutputLinkNodeCnt;                                /* 输出参数链表节点个数，只在封装有效 */
    VOS_UINT32                          ulOutputLinkTotalSize;                              /* 输出参数链表节点数据包总长度，只在封装有效 */
    PPP_ZC_STRU *                       apstOutputLinkNode[HDLC_OUTPUT_PARA_LINK_MAX_SIZE]; /* 输出参数链表节点对应的零拷贝内存，只在封装有效 */
} HDLC_PARA_LINK_BUILD_INFO_STRU;
/*lint +e506*/
#endif
/*
封装上报空间结点结构:
软件保证封装上报空间起始地址Word对齐；(参见HiHDLCV200逻辑需求规格说明书)，
从上到下，地址增加，分别为输出数据起始地址、数据长度；
长度LEN有效16bits处于低Half_Word；地址ADDR 32bits
*/
typedef struct
{
    VOS_UINT8                          *pucFrmOutOneAddr;       /* 指向封装出的有效帧的在外存储起始地址 */
    VOS_UINT16                          usFrmOutOneLen;         /* 有效帧的长度 */
    VOS_UINT8                           aucReserve[2];
} HDLC_FRM_RPT_NODE_STRU;

/* 保存封装使用的内存 */
typedef struct
{
    HDLC_PARA_LINK_NODE_STRU            astInputParaLinkNodeBuf[TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM];  /* 封装输入参数链表使用的内存 */
    HDLC_FRM_RPT_NODE_STRU              astRptNodeBuf[TTF_HDLC_FRM_RPT_MAX_NUM];                        /* 封装信息上报空间使用的内存 */
    HDLC_PARA_LINK_NODE_STRU            astOutputParaLinkNodeBuf[TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM];/* 封装输出参数链表使用的内存 */
} HDLC_FRM_BUFF_INFO_STRU;


/*
解封装上报空间结点结构:
软件保证解封装上报空间起始地址Word对齐；(参见HiHDLCV200逻辑需求规格说明书)，
从上到下，地址增加，分别为输出数据协议类型、长度和存储地址；
长度LEN有效16bits处于低Half_Word；协议PRO有效16bits处于高Half-Word；地址ADDR 32bits
*/
typedef struct
{
    VOS_UINT16                          usDefOutOneLen;         /* 有效帧的长度 */
    VOS_UINT16                          usDefOutOnePro;         /* 有效帧的协议 */
    VOS_UINT8                          *pucDefOutOneAddr;       /* 指向解封装出的有效帧在外存储的起始地址 */
} HDLC_DEF_RPT_NODE_STRU;


/* 解封装非完整帧信息存储结构 */
typedef struct
{
    VOS_UINT8                           ucExistFlag;            /* 非完整帧是否存在标识 */
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT16                          usDefOutOnePro;         /* 非完整帧的协议 */
    VOS_UINT16                          usDefOutOneLen;         /* 非完整帧的长度 */
    VOS_UINT8                          *pucDefOutOneAddr;       /* 指向解封装出的非完整帧在外存储的起始地址 */
    VOS_UINT32                          ulDefStAgo;             /* 用于保存def_uncomplet_st_now寄存器值 */
    VOS_UINT32                          ulDefInfoFrlCntAgo;     /* 用于保存def_info_frl_cnt_ago寄存器值 */
} HDLC_DEF_UNCOMPLETED_INFO_STRU;

/* 保存解封装使用的内存 */
typedef struct
{
    HDLC_PARA_LINK_NODE_STRU            astInputParaLinkNodeBuf[TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_NUM];/* 解封装输入参数链表使用的内存 */
    HDLC_DEF_RPT_NODE_STRU              astRptNodeBuf[TTF_HDLC_DEF_RPT_MAX_NUM];                      /* 解封装信息上报空间使用的内存 */
    VOS_UINT8                           aucOutputDataBuf[TTF_HDLC_DEF_OUTPUT_DATA_BUF_LEN];           /* 解封装目的空间使用的内存 */
} HDLC_DEF_BUFF_INFO_STRU;

/* 输入参数链表可维可测结构 */
typedef struct
{
    VOS_MSG_HEADER                                              /* 消息头 */
    HDLC_MNTN_EVENT_TYPE_ENUM_UINT32    ulMsgname;
}HDLC_MNTN_TRACE_HEAD_STRU;

/* 封装相关寄存器可维可测结构 */
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                     /* _H2ASN_Skip */
    VOS_UINT32                          ulStateSwRst;
    VOS_UINT32                          ulPriorTimeoutCtrl;
    VOS_UINT32                          ulRdErrCurrAddr;
    VOS_UINT32                          ulWrErrCurrAddr;
    VOS_UINT32                          ulHdlcFrmEn;
    VOS_UINT32                          ulHdlcFrmRawInt;
    VOS_UINT32                          ulHdlcFrmIntStatus;
    VOS_UINT32                          ulHdlcFrmIntClr;
    VOS_UINT32                          ulHdlcFrmCfg;
    VOS_UINT32                          ulHdlcFrmAccm;
    VOS_UINT32                          ulHdlcFrmStatus;
    VOS_UINT32                          ulFrmInLliAddr;
    VOS_UINT32                          ulFrmInSublliAddr;
    VOS_UINT32                          ulFrmInPktLen;
    VOS_UINT32                          ulFrmInBlkAddr;
    VOS_UINT32                          ulFrmInBlkLen;
    VOS_UINT32                          ulFrmOutLliAddr;
    VOS_UINT32                          ulFrmOutSpaceAddr;
    VOS_UINT32                          ulFrmOutSpaceDep;
    VOS_UINT32                          ulFrmRptAddr;
    VOS_UINT32                          ulFrmRptDep;
} HDLC_MNTN_FRM_REG_CONFIG_STRU;

/* 解封装相关寄存器可维可测结构 */
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                     /* _H2ASN_Skip */
    VOS_UINT32                          ulStateSwRst;
    VOS_UINT32                          ulPriorTimeoutCtrl;
    VOS_UINT32                          ulRdErrCurrAddr;
    VOS_UINT32                          ulWrErrCurrAddr;
    VOS_UINT32                          ulHdlcDefEn;
    VOS_UINT32                          ulHdlcDefRawInt;
    VOS_UINT32                          ulHdlcDefIntStatus;
    VOS_UINT32                          ulHdlcDefIntClr;
    VOS_UINT32                          ulHdlcDefCfg;
    VOS_UINT32                          ulDefUncompletedLen;
    VOS_UINT32                          ulDefUncompletedPro;
    VOS_UINT32                          ulDefUncompletedAddr;
    VOS_UINT32                          ulDefUncompleteStAgo;
    VOS_UINT32                          ulHdlcDefGoOn;
    VOS_UINT32                          ulHdlcDefStatus;
    VOS_UINT32                          ulDefUncompletStNow;
    VOS_UINT32                          ulDefInLliAddr;
    VOS_UINT32                          ulDefInPktAddr;
    VOS_UINT32                          ulDefInPktLen;
    VOS_UINT32                          ulDefInPktLenMax;
    VOS_UINT32                          ulDefOutSpcAddr;
    VOS_UINT32                          ulDefOutSpaceDep;
    VOS_UINT32                          ulDefRptAddr;
    VOS_UINT32                          ulDefRptDep;
    VOS_UINT32                          ulHdlcDefErrInfor0;
    VOS_UINT32                          ulHdlcDefErrInfor1;
    VOS_UINT32                          ulHdlcDefErrInfor2;
    VOS_UINT32                          ulHdlcDefErrInfor3;
    VOS_UINT32                          ulDefInfoFr1CntAgo;
    VOS_UINT32                          ulDefInfoFr1CntNow;
} HDLC_MNTN_DEF_REG_CONFIG_STRU;

/* 输出和输出数据内容勾包*/
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                         /* _H2ASN_Skip */
    VOS_UINT16                          usNodeIndex;
    VOS_UINT16                          usLen;
    /* VOS_UINT8[usLen]数据内容放在这里，申请的时候由头加上数据内容长度 */
}HDLC_MNTN_NODE_DATA_STRU;

/* 输入参数链表可维可测结构 */
/*lint -e506*/
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                         /* _H2ASN_Skip */
    VOS_UINT32                          ulInputLinkNodeCnt;     /* 输入参数链表节点个数 */
    VOS_UINT32                          ulInputLinkTotalSize;   /* 输入参数链表节点数据包总长度 */
    HDLC_PARA_LINK_NODE_STRU            astInputParaLinkNodeBuf[HDLC_INPUT_PARA_LINK_MAX_SIZE];
}HDLC_MNTN_INPUT_PARA_LINK_STRU;
/*lint +e506*/

/* 封装输出结果可维可测结构 */
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                         /* _H2ASN_Skip */
    VOS_UINT8                           ucFrmValidNum;
    VOS_UINT8                           ucReserve1[1];
    VOS_UINT16                          usOutputNodeUsedCnt;
    VOS_UINT32                          ulOutputLinkNodeCnt;    /* 输出参数链表节点个数，只在封装有效 */
    VOS_UINT32                          ulOutputLinkTotalSize;  /* 输出参数链表节点数据包总长度，只在封装有效 */
    HDLC_PARA_LINK_NODE_STRU            astOutputParaLinkNodeBuf[TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM];/* 封装输出参数链表使用的内存 */
    HDLC_FRM_RPT_NODE_STRU              astRptNodeBuf[TTF_HDLC_FRM_RPT_MAX_NUM];                        /* 封装信息上报空间使用的内存 */
}HDLC_MNTN_FRM_OUTPUT_PARA_STRU;

/* 解封装非完整帧可维可测结构 */
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                         /* _H2ASN_Skip */
    HDLC_DEF_UNCOMPLETED_INFO_STRU      stUncompletedInfo;
}HDLC_MNTN_DEF_UNCOMPLETED_INFO_STRU;

/* 解封装输出结果可维可测结构 */
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                         /* _H2ASN_Skip */
    VOS_UINT16                          usDefValidNum;
    VOS_UINT16                          usTraceNum;
    /* HDLC_DEF_RPT_NODE_STRU[usDefValidNum]此处为封装信息上报空间使用的内存，
       申请内存时由结构长度加上报空间需要的内存大小 */
}HDLC_MNTN_DEF_OUTPUT_PARA_STRU;

/* HDLC配置相关信息结构 */
typedef struct
{
    VOS_UINT_PTR                        ulHDLCIPBaseAddr;      /* 从底软获取的HDLC基地址 */
    VOS_UINT32                          ulHdlcDefMasterSem;    /* 解封装信号量 */
    VOS_UINT32                          ulHdlcFrmMasterSem;    /* 封装信号量 */
    VOS_INT32                           slHdlcISRDef;          /* 解封装中断号 */
    VOS_INT32                           slHdlcISRFrm;          /* 封装中断号 */
    VOS_UINT32                          ulHdlcDefIntLimit;     /* 解封装中断水线 */
    VOS_UINT32                          ulHdlcFrmIntLimit;     /* 封装中断水线 */
    HTIMER                              stHdlcFrmTimerHandle;  /* 申请封装目的空间失败定时器句柄 */
    VOS_UINT32                          ulHdlcMntnTraceCfg;    /* 可维可测等级配置 */
}HDLC_CONFIG_INFO_STRU;

/* 统计信息 */
typedef struct
{
    VOS_UINT32                  ulDefIpDataProcCnt;             /* 解封装IP数据包处理个数 */
    VOS_UINT32                  ulDefPppDataProcCnt;            /* 解封装简单PPP帧处理个数 */
    VOS_UINT32                  ulDefUncompleteCnt;             /* 解封装有非完整帧输出次数 */
    VOS_UINT32                  ulDefWaitIntCnt;                /* 解封装等待中断次数 */
    VOS_UINT32                  ulDefWaitQueryCnt;              /* 解封装等待轮询次数 */
    VOS_UINT32                  ulDefLcpPauseCnt;               /* 解封装LCP暂停次数 */
    VOS_UINT32                  ulDefFullPauseCnt;              /* 解封装输出空间或上报空间满暂停次数 */
    VOS_UINT32                  ulDefInputDiscardCnt;           /* 解封装丢弃数据包个数 */

    VOS_UINT32                  ulFrmIpDataProcCnt;             /* 封装IP数据包处理个数 */
    VOS_UINT32                  ulFrmPppDataProcCnt;            /* 封装简单PPP帧处理个数 */
    VOS_UINT32                  ulFrmWaitIntCnt;                /* 封装等待中断次数 */
    VOS_UINT32                  ulFrmWaitQueryCnt;              /* 封装等待轮询次数 */
    VOS_UINT32                  ulFrmAllocOutputMemFailCnt;     /* 封装申请目的内存失败次数 */
    VOS_UINT32                  ulFrmAllocFirstMemFailCnt;      /* 封装申请第一个节点目的内存失败次数 */
    VOS_UINT32                  ulFrmOutputLinkFullCnt;         /* 封装输出链表满次数 */
    VOS_UINT32                  ulFrmInputDiscardCnt;           /* 封装丢弃数据包个数 */

    VOS_UINT32                  ulDefMaxInputCntOnce;           /* 解封装一次最大输入数据个数 */
    VOS_UINT32                  ulDefMaxInputSizeOnce;          /* 解封装一次最大输入数据总长度 */
    VOS_UINT32                  ulDefMaxValidCntOnce;           /* 解封装一次最大输出有效帧个数 */
    VOS_UINT32                  ulDefMaxQueryCnt;               /* 解封装轮询最大次数 */

    VOS_UINT32                  ulFrmMaxInputCntOnce;           /* 封装一次最大输入数据个数 */
    VOS_UINT32                  ulFrmMaxInputSizeOnce;          /* 封装一次最大输入数据总长度 */
    VOS_UINT32                  ulFrmMaxOutputCntOnce;          /* 封装一次最大输出使用节点数个数 */
    VOS_UINT32                  ulFrmMaxOutputSizeOnce;         /* 封装一次最大输出使用节点总长度 */
    VOS_UINT32                  ulFrmMaxQueryCnt;               /* 封装轮询最大次数 */

    VOS_UINT32                  ulMaxCntOnce;                   /* PPP一次最多处理的结点个数 */
    VOS_UINT32                  ulHdlcHardProcCnt;              /* PPP一次最多处理的结点个数 */

    VOS_UINT32                  ulDefIsrCnt;                    /* 解封装中断服务程序调用次数 */
    VOS_UINT32                  ulFrmIsrCnt;                    /* 封装中断服务程序调用次数 */
    VOS_UINT32                  ulContinueCnt;                  /* 队列中的数据需要分多次处理的次数 */
    VOS_UINT16                  usDefExpInfo;                   /* 解封装异常信息 */
    VOS_UINT16                  usFrmExpInfo;                   /* 封装异常信息 */
    VOS_UINT32                  ulForbidHdlcBugNoCpy;           /* 规避HDLC BUG,不拷贝数据 */
    VOS_UINT32                  ulForbidHdlcBugCpy;             /* 规避HDLC BUG,需要拷贝数据 */
} PPP_HDLC_HARD_DATA_PROC_STAT_ST;

/* HDLC关键寄存器可维可测信息保存结构 */
typedef struct
{
    VOS_UINT32                          ulHdlcFrmRawInt;        /* 封装原始中断寄存器值 */
    VOS_UINT32                          ulHdlcFrmStatus;        /* 封装状态寄存器值 */
    VOS_UINT32                          ulHdlcDefRawInt;        /* 解封装原始中断寄存器值 */
    VOS_UINT32                          ulHdlcDefStatus;        /* 解封装状态寄存器值 */
}HDLC_REG_SAVE_INFO_STRU;

/*****************************************************************************
  6 全局变量声明
*****************************************************************************/
extern HDLC_CONFIG_INFO_STRU                          g_stHdlcConfigInfo;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_UINT32 PPP_HDLC_HARD_Init(VOS_VOID);

extern VOS_VOID   PPP_HDLC_HARD_SetUp(VOS_UINT16 usPppId);

extern VOS_VOID   PPP_HDLC_HARD_Disable(VOS_VOID);

extern VOS_VOID PPP_HDLC_HARD_PeriphClkOpen(VOS_VOID);

extern VOS_VOID PPP_HDLC_HARD_PeriphClkClose(VOS_VOID);

VOS_UINT32 PPP_HDLC_HARD_InitBuf(VOS_VOID);


#if (VOS_RTOSCK != VOS_OS_VER)
extern PPP_HDLC_RESULT_TYPE_ENUM_UINT32 PPP_HDLC_HARD_ProcData
(
    PPP_ID usPppId,
    struct link *pstLink,
    PPP_ZC_QUEUE_STRU *pstDataQ
);

extern VOS_VOID PPP_HDLC_HARD_ProcProtocolPacket
(
    struct link     *pstLink,
    struct ppp_mbuf *pstMbuf,
    VOS_INT32       ulPri,
    VOS_UINT16      ulProtocol
);

extern VOS_VOID PPP_HDLC_HARD_ProcAsFrmPacket
(
    VOS_UINT16       usPppId,
    VOS_UINT16       usProtocol,
    PPP_ZC_STRU     *pstMem
);


extern VOS_UINT32 PPP_PHY_TO_VIRT(unsigned int ulPAddr);

extern VOS_UINT_PTR PPP_VIRT_TO_PHY(VOS_UINT_PTR ulVAddr);

extern VOS_UINT32 PPP_HDLC_NODE_PHY_TO_VIRT(unsigned int ulPAddr);

extern VOS_UINT32 PPP_HDLC_NODE_VIRT_TO_PHY(unsigned int ulVAddr);

#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hdlc_hardware.h */

