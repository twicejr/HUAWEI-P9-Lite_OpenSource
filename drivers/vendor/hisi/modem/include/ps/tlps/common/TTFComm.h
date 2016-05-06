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


#ifndef __TTF_COMM_H_
#define __TTF_COMM_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/******************************************************************************
  1 其他头文件包含
******************************************************************************/
#include "vos.h"
#include "PsLogdef.h"
#include "PsCommonDef.h"
#include "PsLib.h"
#include "PsTypeDef.h"
#include "LPSCommon.h"
#include "product_config.h"
#include "msp_diag_comm.h"

/******************************************************************************
  2 宏定义
******************************************************************************/

#define PS_UE_CAP_2507_SUPPT                  (PS_CAP_SUPPORT)
#define PS_UE_CAP_1144_SUPPT                  (PS_CAP_SUPPORT)
#define PS_UE_CAP_V42_SUPPT                   (PS_CAP_SUPPORT)



/*移位宏*/
#define TTF_BIT_MOVE_24  (24)
#define TTF_BIT_MOVE_16  (16)
#define TTF_BIT_MOVE_8   (8)

/*位运算宏*/
#define TTF_BIT_OPR_8    (0xFF)
#define TTF_BIT_OPR_16   (0xFFFF)
#define TTF_BIT_OPR_24   (0xFFFFFF)
#define TTF_BIT_OPR_32   (0xFFFFFFFF)

/*无符号整数模*/
#define TTF_UNSIGN_LONG_MOD         (0x7FFFFFFFUL)

/*把4个的UINT8型组成UINT32, UINT8从高位到低位*/
#define TTF_CONN_UINT32_FROM_UINT8(ulNum, ucNum1, ucNum2, ucNum3, ucNum4)   \
{       \
    (ulNum) = 0;        \
    (ulNum) |= (VOS_UINT32)(((VOS_UINT32)(ucNum1)) << TTF_BIT_MOVE_24);     \
    (ulNum) |= (VOS_UINT32)(((VOS_UINT32)(ucNum2)) << TTF_BIT_MOVE_16);     \
    (ulNum) |= (VOS_UINT32)(((VOS_UINT32)(ucNum3)) << TTF_BIT_MOVE_8);     \
    (ulNum) |= (VOS_UINT32)(ucNum4);     \
}

#define TTF_MOD_GET(x, y)                       ((x) % (y))
#define TTF_MOD_ADD_GU(x, y, z)                 (((x) + (y)) % (z))
#define TTF_MOD_SUB_GU(x, y, z)                 ((((x) + (z)) - (y)) % (z))
#ifdef _lint
#define TTF_MOD_ADD(x, y, z)                    (((x) + (y)) % (z))
#define TTF_MOD_SUB(x, y, z)                    ((((x) + (z)) - (y)) % (z))
#else
#define TTF_MOD_ADD(x, y, z)                    ((((x) + (y)) < (z))? ((x) + (y)):(((x) + (y)) - (z)))
#define TTF_MOD_SUB(x, y, z)                    (((x) < (y))?(((x) + (z)) - (y)):((x) - (y)))
#endif


/* X除以Y，向上取整 */
#define TTF_CEIL(x, y) \
            /*lint -e{961} */ \
            ((0==(x)%(y))?((x)/(y)):((x)/(y)+1))

#define TTF_MIN(x, y)                           (((x)<(y))?(x):(y))
#define TTF_MAX(x, y)                           (((x)>(y))?(x):(y))

/* SN在窗口[lower, upper]区间外，不包含窗口lower upper上下边界 */
#define TTF_SN_OUTSIDE_WINDOW(sn, lowerEdge, upperEdge, module) \
            /*lint -e{961,731} */ \
            ((TTF_MOD_SUB(sn, lowerEdge, module) >= TTF_MOD_SUB(sn, upperEdge, module)) && ((sn) != (upperEdge)))

/* SN在窗口[lower, upper]区间内，包含窗口lower upper上下边界 */
#define TTF_SN_WITHIN_WINDOW(sn, lowerEdge, upperEdge, module)  \
            /*lint -e{961,731} */ \
            ((TTF_MOD_SUB(sn, lowerEdge, module) < TTF_MOD_SUB(sn, upperEdge, module)) || ((sn) == (upperEdge)))

#define TTF_SN1_BELOW_SN2_WITHIN_WINDOW(sn1, sn2, upperEdge, module)\
            (TTF_MOD_SUB(upperEdge, sn1, module) > TTF_MOD_SUB(upperEdge, sn2, module))

#define TTF_SN_IN_WINDOW(sn, lowerEdge, winSize, module) \
            ( TTF_MOD_SUB((sn), (lowerEdge), (module)) < (winSize) )

/*根据块号usSn，获取它在窗口中的存储位置索引:
usSns:块号的模
usWndSize:窗口大小
usHeader:窗口中某一块号为usHeaderSn的节点，在窗口中对应的存储位置索引
usHeaderSn:窗口中某一节点的块号
usSn:当前期望获取其存储位置的块的块号*/
#define TTF_GET_WND_POS(usSns, usWndSize, usHeader, usHeaderSn, usSn)   \
    TTF_MOD_GET(((usHeader) + TTF_MOD_SUB((usSn), (usHeaderSn), (usSns))), (usWndSize))

/* change bit to byte */
#define TTF_BIT2BYTE(BitLen)        (((BitLen) + 7) >> 3)
/* change byte to bit */
#define TTF_BYTE2BIT(ByteLen)       (VOS_UINT32)(((VOS_UINT32)(ByteLen)) << 3)

/*=============*/   /*获取结构体成员变量offset的办法*/
#define TTF_OFFSET_OF(s, m) /*lint -e(413)*/((VOS_SIZE_T)(VOS_UINT_PTR)(&(((s *)0)->m)))

#define TTF_GET_OFFSET(offset, s, m) \
{ \
    /*lint --e{545,413,831} */ \
    offset  = TTF_OFFSET_OF(s, m); \
}

/* 将一个整型数据ucSrc，填入另一个整型数据ucDest中从bitstart(取值范围0到7)开始的bitlen(取值范围1到8)长度的IE中,
   输入的有效性由输入者保证,各个模块可以类似定义设置值的宏。 ucDest在使用前需要清零。*/
#define TTF_SET_UC_BIT(ucSrc, ucDest, bitstart, bitlen) \
((ucDest) |= (VOS_UINT8)( (VOS_UINT8)((VOS_UINT32)(ucSrc) << (8 - bitlen)) >> ((8 - bitstart) - bitlen) ))

/* 将一个整型数据ucSrc，填入另一个整型数据ucDest中从最高位开始的bitlen(取值范围1到8)长度的IE中,
   输入的有效性由输入者保证,各个模块可以类似定义设置值的宏。 ucDest在使用前需要清零。*/
#define TTF_SET_UC_HIGH_BIT(ucSrc, ucDest, bitlen) \
((ucDest) |= (VOS_UINT8)( (VOS_UINT8)((VOS_UINT32)(ucSrc) << (8 - bitlen)) ))

/* 将一个整型数据usSrc，填入另一个整型数据usDest中从bitstart(取值范围0到15)开始的bitlen(取值范围1到16)长度的IE中,
   输入的有效性由输入者保证,各个模块可以类似定义设置值的宏。 usDest在使用前需要清零。*/
#define TTF_SET_US_BIT(usSrc, usDest, bitstart, bitlen) \
((usDest) |= (VOS_UINT16)( (VOS_UINT16)((VOS_UINT32)(usSrc) << (16 - bitlen)) >> ((16 - bitstart) - bitlen) ))

/* 将一个整型数据usSrc，填入另一个整型数据usDest中从最高位开始的bitlen(取值范围1到16)长度的IE中,
   输入的有效性由输入者保证,各个模块可以类似定义设置值的宏。 ucDest在使用前需要清零。*/
#define TTF_SET_US_HIGH_BIT(usSrc, usDest, bitlen) \
((usDest) |= (VOS_UINT16)( (VOS_UINT16)((VOS_UINT32)(usSrc) << (16 - bitlen)) ))

/* 从一个US型数据中获取从bitstart(取值范围0到15)开始的bitlen(取值范围1到16)长度的值,
   输入的有效性由输入者保证,各个模块可以类似定义设置值的宏
   注意: bitstart是按照下边顺序来输入的
   +  -  +  -  +  -  + - + - + - + - + -
   15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
   +  -  +  -  +  -  + - + - + - + - + -
*/
#define TTF_GET_US_BIT(us, bitstart, bitlen) \
((VOS_UINT16)((VOS_UINT32)(us) << ((16 - (bitstart)) - (bitlen))) >> (16 - (bitlen)))

#define TTF_GET_US_HIGH_BIT(us, bitlen) \
((VOS_UINT16)((us)  >> (16 - (bitlen))))

/* 从一个UC型数据中获取从bitstart(取值范围0到7)开始的bitlen(取值范围1到8)长度的值,
   输入的有效性由输入者保证,各个模块可以类似定义设置值的宏 */
#define TTF_GET_UC_BIT(uc, bitstart, bitlen) \
((VOS_UINT8)((VOS_UINT32)(uc) << ((8 - (bitstart)) - (bitlen))) >> (8 - (bitlen)))

/* 从一个整型数据uc中，获取从最高位开始的bitlen(取值范围1到8)长度的IE,
   输入的有效性由输入者保证,各个模块可以类似定义设置值的宏。 */
#define TTF_GET_UC_HIGH_BIT(uc, bitlen) \
((VOS_UINT8)(uc) >> (8 - (bitlen)))

#define TTF_GET_HIGH_16BIT_FROM_32BIT(ul32BitValue) ((VOS_UINT16)((ul32BitValue) >> 16))
#define TTF_GET_HIGH_8BIT_FROM_32BIT(ul32BitValue)  ((VOS_UINT8)((ul32BitValue) >> 24))
#define TTF_GET_LOW_16BIT_FROM_32BIT(ul32BitValue)  ((VOS_UINT16)((ul32BitValue) & 0xFFFF))
#define TTF_MAKE_32BIT(usHighVal, usLowVal)         ( (((VOS_UINT32)(usHighVal))<<16) | ((VOS_UINT32)((usLowVal) & 0xFFFF)) )
#define TTF_MAKE_16BIT(ucHighVal, ucLowVal)         ( (VOS_UINT16)(((VOS_UINT8)(ucLowVal)) | (((VOS_UINT16)((VOS_UINT8)(ucHighVal)))<<8)) )

#define TTF_SET_HIGH_16BIT_TO_32BIT(ul32BitVal, usHigh16BitVal) \
    ( (((VOS_UINT32)ul32BitVal) & 0xFFFF) | (((VOS_UINT32)usHigh16BitVal) << 16) )

#define TTF_GET_4BYTE_ALIGN_VALUE(ulSize)   ( ((ulSize) + 0x03) & (~0x03) )

#define TTF_GET_8BYTE_ALIGN_VALUE(ulSize)   ( ((ulSize) + 0x07) & (~0x07) )


/* 设置标志比特位的值为1，bitpos:[0..31] */
#define TTF_SET_A_BIT(value, bitpos)    ((value) |= (1UL << (bitpos)))

/* 清除标志比特位的值为0，bitpos:[0..31] */
#define TTF_CLEAR_A_BIT(value, bitpos)  ((value) &= (~(1UL << (bitpos))))

/* 获取标志比特位的值，结果返回1和0，bitpos:[0..31] */
#define TTF_GET_A_BIT(value, bitpos)    (((value) & (1UL << (bitpos))) >> (bitpos))

/* 获取数组的大小 */
#define TTF_GET_ARRAYSIZE(array)        (sizeof(array)/sizeof(array[0]))


/* 从一个消息中获取消息类型的宏，输入参数的有效性由输入者保证 */
#define TTF_GET_MSGTYPE(pMsg) \
    (*(VOS_UINT16*)((VOS_UINT8*)(pMsg) + VOS_MSG_HEAD_LENGTH))

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#ifndef __PS_WIN32_RECUR__
#define TTF_TRACE_MSG(pMsg)     DIAG_TraceReport(pMsg)
#else
#define TTF_TRACE_MSG(pMsg)     TTF_TraceMsgHook(pMsg)
#endif
#else
#define TTF_TRACE_MSG(pMsg)
#endif
/* 回放时标识是否回放ST工程抓的Trace,UT工程也需要 */
#define RECUR_ST_TRACE      (1)
#define RECUR_OTHER_TRACE   (0)

/*避免与其它模块在相同时间点导出全局变量,所以设一个特殊值
  现有导出全局变量模块，NAS每一分钟导一次，GRM与LLC导出时间见如下设置
 */
#define GRM_MNTN_TIMER_PC_RECUR_LEN     60533
#define LLC_MNTN_TIMER_PC_RECUR_LEN     60503

/* 16bit 32 bit 寄存器读写 */
#define TTF_WRITE_32REG(pAddr, value)       ( *((volatile VOS_UINT32 *)(pAddr)) = (value) )
#define TTF_WRITE_16REG(pAddr, value)       ( *((volatile VOS_UINT16 *)(pAddr)) = (value) )
#define TTF_READ_32REG(pAddr)               ( *((volatile VOS_UINT32 *)(pAddr)) )
#define TTF_READ_16REG(pAddr)               ( *((volatile VOS_UINT16 *)(pAddr)) )

/* 32 bit 寄存器屏蔽 */
#define TTF_WRITE_32REG_MASK(pAddr,ulMask)  ( *(volatile VOS_UINT32 *)(pAddr) |= (ulMask) )

/* 32 bit 寄存器清除 */
#define TTF_CLEAR_32REG_MASK(pAddr,ulMask)  ( *(volatile VOS_UINT32 *)(pAddr) &= ~(ulMask) )

/* 从一个消息中获取消息类型的宏，输入参数的有效性由输入者保证 */
#define TTF_GET_MSG_NAME(pRcvMsg)           (*((VOS_UINT32 *)(VOS_VOID *)((VOS_UINT8 *)(pRcvMsg) + VOS_MSG_HEAD_LENGTH)))
#define TTF_GET_MSG_SENDER_PID(pRcvMsg)     (*((VOS_UINT32 *)(VOS_VOID *)(pRcvMsg) + 1))
#define TTF_GET_MSG_RECV_PID(pRcvMsg)       (*((VOS_UINT32 *)(VOS_VOID *)(pRcvMsg) + 3))
#define TTF_GET_MSG_MSG_LEN(pRcvMsg)        (*((VOS_UINT32 *)(VOS_VOID *)(pRcvMsg) + 4))
#define TTF_GET_MSG_OPID(pRcvMsg)      (*(VOS_UINT16 *)(VOS_VOID*)((VOS_UINT8 *)pRcvMsg + 24))


/*设置消息头的数据*/
#define TTF_SET_MSG_SENDER_PID(pRcvMsg, ulPid)          \
                                            (*((VOS_UINT32 *)(VOS_VOID *)(pRcvMsg) + 1) = (ulPid))
#define TTF_SET_MSG_RECV_PID(pRcvMsg, ulPid)          \
                                            (*((VOS_UINT32 *)(VOS_VOID *)(pRcvMsg) + 3) = (ulPid))
#define TTF_SET_MSG_LEN(pRcvMsg, ulLen)            \
                                            (*((VOS_UINT32 *)(VOS_VOID *)(pRcvMsg) + 4) = (ulLen))


#define  ETH_MAC_HEADER_LEN             (14)      /*以太网帧头长度*/
/*Ethenet*/
#define ETH_MAC_ADDR_LEN                6         /*以太网帧MAC地址长度*/
#define ETH_MIN_FRAME_SIZE              60        /*以太网帧最小长度*/
#define ETH_CRC_LEN                     4
#define ETH_MAX_FRAME_SIZE              (1514)    /*以太网最大长度*/

/*ARP*/
#define ETH_ARP_REQ_TYPE                0x0100      /*ARP Request*/
#define ETH_ARP_RSP_TYPE                0x0200      /*ARP Reply*/
#define ETH_ARP_FIXED_MSG_LEN           8           /*ARP固定部分长度*/

/*IP*/
/*#define IPPACKET_MIN_LEN                (1500)
 */
#define IPV4_FIX_HDR_LEN                (20)       /* IPV4固定头长度*/
#define IPV4_HDR_TTL                    (128)      /* IPV4 头中的TTL字段默认值*/

#define IP_IPV4_VERSION                 (4)        /* IP V4版本号      */
#define IP_PROTOCOL_UDP                 (0x11)     /* IP承载协议是UDP  */
#define IP_PROTOCOL_TCP                 (0x06)     /* IP承载协议是TCP  */
#define IP_PROTOCOL_ICMP                (0x01)     /* IP承载协议是ICMP */

/*DHCP报文目的端口67,定义为网络字节序*/
#define UDP_DHCP_SERVICE_PORT           (0x4300)   /* DHCP服务的端口号 */
#define UDP_DHCP_CLIENT_PORT            (0x4400)   /* DHCP Client的端口号*/

#define TTF_L1_CACHE_SHIFT              (5)
#define TTF_L1_CACHE_BYTES              (1UL << TTF_L1_CACHE_SHIFT)


#define TTF_SMP_CACHE_BYTES             (TTF_L1_CACHE_BYTES)        /* Linux版本发生改变时需要重新check该值 */

#define TTF_DATA_ALIGN(X)               (((X) + (TTF_SMP_CACHE_BYTES - 1)) & \
                                        ~(TTF_SMP_CACHE_BYTES - 1))

/* TCP/IP相关 */
#define IP_VER_MASK                         (0xF0)    /* 用于取IP协议版本的掩码 */
#define IP_HEADER_LEN_MASK                  (0x0F)    /* 用于取IP首部长度的掩码 */
#define IPV4_VER_VAL                        (0x40)    /* IP v4 */
#define IPV6_VER_VAL                        (0x60)    /* IP v6 */

#define PROTOCOL_POS                        (9)       /* 协议标识相对IP头部首字节Protocal 的偏移 */
#define NEXT_HEADER_POS                     (6)       /* 协议标识相对IP头部首字节Next header 的偏移 */

#define IPV4_HEAD_NORMAL_LEN                (20)      /* IPV4头长典型值 */
#define IPV6_HEAD_NORMAL_LEN                (40)      /* IPV6头长典型值 */

#define IP_VER_VAL                          (0x40)    /* IP v4 */
#define TCP_IP_OFFSET_LEN_POS               (32)      /* TCP头部长度字段相对IP头部首字节的偏移 */

#define IPV4_INDENTIFY_OFFSET_POS           (4)        /* IPV4 Identification offset相对于IPV4首字节的偏移 */

#define IPV4_SRC_IP_ADDR_OFFSET_POS         (12)       /* IPV4 Src Ip Adrr offset相对于IPV4首字节的偏移 */
#define IPV4_DST_IP_ADDR_OFFSET_POS         (16)       /* IPV4 Dst Ip Adrr offset相对于IPV4首字节的偏移 */

#define IP_VER_VAL_V6                       (0x60)    /* IP v6 */

#define IPV4_HEAD_FRAGMENT_OFFSET_POS       (6)       /* IPV4 Fragment offset相对于IPV4首字节的偏移 */
#define IPV6_HEAD_FRAGMENT_OFFSET_POS       (20)      /* IPV6 Fragment offset相对于IPV4首字节的偏移 */
#define IPV4_HEAD_FRAGMENT_OFFSET_MASK      (0x3FFF)  /* IPV4 Fragment offset掩码 */
#define ICMP_TYPE_CODE_OFFSET_POS           (1)       /* ICMP CODE首字节的偏移 */
#define ICMP_HEADER_LEN                     (8)       /* ICMP 头长度 */
#define ICMP_TYPE_REPLY                     (0)       /* ICMP回显应答报文类型 */
#define ICMP_TYPE_REQUEST                   (8)       /* ICMP请求回显报文类型 */

#define TCP_DST_PORT_POS                    (2)       /* TCP头部目的端口号相对TCP头部首字节的偏移 */
#define TCP_SEQ_NUM_POS                     (4)       /* TCP头部Seq number相对TCP头部首字节的偏移 */
#define TCP_ACK_NUM_POS                     (8)       /* TCP头部Ack number相对TCP头部首字节的偏移 */
#define TCP_LEN_POS                         (12)      /* TCP头部长度字段相对TCP头部首字节的偏移 */
#define TCP_FLAG_POS                        (13)      /* TCP头部长度字段相对TCP头部首字节的偏移 */
#define TCP_SYN_MASK                        (0x02)    /* 用于取TCP头部长度字段值的掩码 */
#define TCP_ACK_MASK                        (0x10)    /* 用于取TCP头部长度字段值的掩码 */
#define TCP_LEN_MASK                        (0xF0)    /* 用于取TCP头部长度字段值的掩码 */
#define FTP_DEF_SERVER_SIGNALLING_PORT      (21)      /* FTP熟知的服务器侧信令端口号 */

#define PROTOCOL_POS_V6                     (6)       /* 协议标识相对IP头部首字节的偏移 */

#define TCP_LEN_POS_V6                      (52)      /* TCP头部长度字段相对IP头部首字节的偏移 */

#define ICMPV6_TYPE_REQUEST                 (128)     /* ICMP请求回显报文类型 */
#define ICMPV6_TYPE_REPLY                   (129)     /* ICMP回显应答报文类型 */

#define UDP_HEAD_LEN                        (8)       /* UDP数据包头部长度 */
#define UDP_DST_PORT_POS                    (2)       /* UDP目的端口相对于UDP头部基地址的偏移 */
#define DNS_QR_POS                          (2)       /* DNS QR相对于QR头部基地址的偏移 */
#define DNS_QR_MASK                         (0x80)    /* 用于取DNS QR字段值的掩码 */
#define DNS_DEF_SERVER_PORT                 (53)      /* DNS熟知的服务器侧端口号 */

#define TCP_ACK_MIN_LEN                     (40)       /* TCP ACK最小长度, 字节为单位, typically IP header 20 bytes and TCP header 20 bytes */
#define TCP_ACK_MIN_LEN_V6                  (60)       /* TCP ACK最小长度, 字节为单位, typically IP header 40 bytes and TCP header 20 bytes */
#define TCP_ACK_MAX_LEN                     (80)       /* TCP ACK最大长度, 字节为单位, typically IP header 20 bytes, and TCP header max size 60 bytes */
#define TCP_ACK_MAX_LEN_V6                  (100)      /* TCP ACK最大长度, 字节为单位, typically IP header 40 bytes, and TCP header max size 60 bytes */
#define ICMP_PROTOCOL_VAL                   (0x01)     /* ICMP协议标识的值 */
#define ICMP_PROTOCOL_VAL_V6                (0x3A)     /* ICMP协议标识的值 */

/* IP 数据包可维可测*/
#define IP_IPV4_PROTO_VERSION        4      /* IPV4协议版本号 */
#define IP_IPV4_HEAD_LEN             20     /* IPV4数据头头部长度 */
#define IP_IPV4_PROTO_TCP            6      /* IPV4的TCP协议号 */
#define IP_IPV4_PROTO_UDP            17     /* IPV4的UDP协议号 */
#define IP_IPV4_PROTO_ICMP           1      /* IPV4的ICMP协议号 */
#define IP_IPV4_ICMP_ECHO_REQUEST    8      /* IPV4的ICMP的TYPE ECHO REQ */
#define IP_IPV4_ICMP_ECHO_REPLY      0      /* IPV4的ICMP的TYPE ECHO REPLY */
#define IP_IPV4_DATA_LEN_POS         2      /* IPV4的IP数据包长度字段偏移 */
#define IP_IPV4_IDENTIFY_POS         4      /* IPV4的IP数据包IDENTIFY字段偏移 */
#define IP_IPV4_PROTO_POS            9      /* IPV4的IP数据包协议字段偏移 */
#define IP_IPV4_ICMP_IDENTIFY_POS    4      /* 去除IP头，ICMP的IDENTIFY字段偏移 */
#define IP_IPV4_ICMP_SN_POS          6      /* 去除IP头，ICMP的SN字段偏移 */
#define IP_IPV4_TCP_SEQ_POS          4      /* 去除IP头，TCP的SEQ字段偏移 */
#define IP_IPV4_TCP_ACK_POS          8      /* 去除IP头，TCP的ACK字段偏移 */
#define IP_IPV4_DST_PORT_POS         2      /* 去除IP头，IPV4的目的端口字段偏移 */
#define IP_PROTO_VERSION_POS         4      /* IP数据包的协议版本字段偏移 */

#define IP_IPV6_PROTO_VERSION        6      /* IPV6协议版本号 */
#define IP_IPV6_HEAD_LEN             40     /* IPV6数据头头部长度 */
#define IP_IPV6_PROTO_TCP            6      /* IPV6的TCP协议号 */
#define IP_IPV6_PROTO_UDP            17     /* IPV6的UDP协议号 */
#define IP_IPV6_PROTO_ICMP           58     /* IPV6的ICMP协议号 */
#define IP_IPV6_ICMP_ECHO_REQUEST    128    /* IPV6的ICMP的TYPE ECHO REQ */
#define IP_IPV6_ICMP_ECHO_REPLY      129    /* IPV6的ICMP的TYPE ECHO REPLY */
#define IP_IPV6_DATA_LEN_POS         4      /* IPV6的IP数据包长度字段偏移 */
#define IP_IPV6_PROTO_POS            6      /* IPV6的IP数据包协议字段偏移 */
#define IP_IPV6_ICMP_IDENTIFY_POS    4      /* 去除IP头，ICMP的IDENTIFY字段偏移 */
#define IP_IPV6_TCP_SEQ_POS          4      /* 去除IP头，TCP的SEQ字段偏移 */
#define IP_IPV6_TCP_ACK_POS          8      /* 去除IP头，TCP的ACK字段偏移 */
#define IP_IPV6_DST_PORT_POS         2      /* 去除IP头，IPV6的目的端口字段偏移 */

#define IP_IPV4_VER_AND_HEAD         0x45   /* IPv4版本号字段的值 */
#define IP_IPV6_VER_AND_HEAD         0x60   /* IPv6版本号字段的值 */
#define MAC_HEAD_LEN                 14     /* MAC头长度 */

/* 从IP数据包中提取数据，并把网络字节序转换为主机字节序 */
#define IP_GET_VAL_NTOH_U8(data,pos)    ((data)[pos])
#define IP_GET_VAL_NTOH_U16(data,pos)   (((data)[pos]<<8)|((data)[pos+1]))
#define IP_GET_VAL_NTOH_U32(data,pos)   (((VOS_UINT32)((data)[pos])<<24)|((VOS_UINT32)((data)[pos+1])<<16)|((VOS_UINT32)((data)[pos+2])<<8)|((data)[pos+3]))



/* TTF Log输出 */
#define TTF_LOG(ModulePID, ModeType, Level, String) \
        ((VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(ModulePID), ModeType, Level), (ModulePID), __FILE__, __LINE__, "%s \r\n", String))

#define TTF_LOG1(ModulePID, ModeType, Level, String, Para1) \
        ((VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(ModulePID), ModeType, Level), (ModulePID), __FILE__, __LINE__, "%s, %d \r\n", String, Para1))

#define TTF_LOG2(ModulePID, ModeType, Level, String, Para1, Para2) \
        ((VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(ModulePID), ModeType, Level), (ModulePID), __FILE__, __LINE__, "%s, %d, %d \r\n", String, Para1, Para2))

#define TTF_LOG3(ModulePID, ModeType, Level, String,Para1, Para2, Para3) \
        ((VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(ModulePID), ModeType, Level), (ModulePID), __FILE__, __LINE__, "%s, %d, %d, %d \r\n", String, Para1, Para2, Para3))

#define TTF_LOG4(ModulePID, ModeType, Level, String, Para1, Para2, Para3, Para4) \
        ((VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(ModulePID), ModeType, Level), (ModulePID), __FILE__, __LINE__, "%s, %d, %d, %d, %d \r\n", String, Para1, Para2, Para3, Para4))

/******************************************************************************
  3 枚举定义
******************************************************************************/
/*****************************************************************************
 枚举名    :
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum APPITF_RTN_CODE_ENUM
{
    APPITF_SUCC                             = 0,
    APPITF_FAIL                             = 1,

    APPITF_PTR_NULL                         = 2,    /*空指针*/
    APPITF_PARA_ERR                         = 3,    /*参数错误*/
    APPITF_STATE_ERR                        = 4,    /*状态错误*/
    APPITF_MODE_ERR                         = 5,    /*模式错误*/
    APPITF_SCOPE_ERR                        = 6,    /*范围错误*/
    APPITF_MEM_ALLOC_FAIL                   = 7,    /*内存分配失败*/
    APPITF_MSG_ALLOC_FAIL                   = 8,    /*消息分配失败*/
    APPITF_MSG_SEND_FAIL                    = 9,    /*消息发送失败*/
    APPITF_TIMER_ERR                        = 10,   /*定时器错误*/
    APPITF_TIMER_OUT                        = 11,   /*定时器超时*/
    APPITF_QUE_FULL                         = 12,   /*队列满*/
    APPITF_QUE_EMPTY                        = 13,   /*队列空*/

    APPITF_SNDTOETH_FAIL                    = 14,
    APPITF_CPYMEM_ERR                       = 15,
    APPITF_TOOBIGIPPACKET                   = 16,

    APP_RTN_CODE_BUTT
};
typedef VOS_UINT32   APP_RTN_CODE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TTF_SOFT_RESET_CAUSE_VALUE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : TTF  软复位原因值
*****************************************************************************/
enum TTF_SOFT_RESET_CAUSE_VALUE_ENUM
{
    TTF_SOFT_RESET_CAUSE_NORMAL                      = 0x30000000,  /* 新增主动软复位，目前只使用该值，日后可拓展，以0x3*******开头 */
    TTF_SOFT_RESET_CAUSE_BUTT
};
typedef VOS_INT32 TTF_SOFT_RESET_CAUSE_VALUE_ENUM_INT32;


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

typedef struct
{
    VOS_MSG_HEADER                      /* 消息头 */

    VOS_UINT16 usMsgType;               /* 消息类型 */
    VOS_UINT16 usTransId;               /* 子进程标识,用于定位子进程 */
#define TTF_MSG_HEAD    4               /* 公共消息中头部附加信息长度(usMsgType和usTransId) */

    VOS_UINT8  astMsg[4];               /* 消息结构指针，指向真正携带的消息 */
}TTF_COMM_MSG;

typedef struct
{
    VOS_MSG_HEADER                      /* 消息头 */

    VOS_UINT16 usMsgType;               /* 消息类型 */
    VOS_UINT8  astMsg[2];               /* 消息结构指针，指向真正携带的消息 */
}WTF_COMM_MSG;


/* 消息处理函数定义
   pMsg:模块收到的输入消息指针
   pSelfDefinePara:模块自定义的输入参数指针 */
typedef VOS_UINT32 (*PTTFMSGPROC)(MsgBlock *pMsg, void *pSelfDefinePara);

typedef struct
{
    VOS_UINT16 usMsgType;               /* 收到的消息ID */
    VOS_UINT8  ucState;                 /* 收到该消息时的状态 */
    VOS_UINT8  ucRsv;                   /* 预留扩展 */
    PTTFMSGPROC pProcFun;               /* 该状态下收到消息的处理函数 */
}TTF_COMM_STATUS;

extern VOS_UINT32       TTF_MEMCTRL_CCORE_AddrInit(VOS_UINT32 ulPid);
extern VOS_UINT32       TTF_MEMCTRL_DynamicAddrInit(VOS_UINT32 ulPid);

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

#endif /* TTFComm.h */


