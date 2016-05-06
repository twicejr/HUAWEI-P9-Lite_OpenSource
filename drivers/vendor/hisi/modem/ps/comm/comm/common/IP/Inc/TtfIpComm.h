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

#ifndef __TTFIPCOMM_H__
#define __TTFIPCOMM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TTFComm.h"
#include "TTFMemInterface.h"

#pragma pack(4)

/*****************************************************************************
  2 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : IP_HEAD_PROTOCOL_ENUM
 协议表格  :
 ASN.1描述 : IP包协议解析
 枚举说明  : IP头按照协议解析出来的格式
*****************************************************************************/
enum IP_DATA_PROTOCOL_ENUM
{
    IP_DATA_PROTOCOL_ICMPV4                 = 0x01,         /* ICMPV4协议标识的值 */
    IP_DATA_PROTOCOL_IGMP                   = 0x02,         /* IGMP协议标识的值 */
    IP_DATA_PROTOCOL_IPINIP                 = 0x04,         /* IP in IP (encapsulation)协议标识的值 */
    IP_DATA_PROTOCOL_TCP                    = 0x06,         /* TCP协议标识的值 */
    IP_DATA_PROTOCOL_UDP                    = 0x11,         /* UDP协议标识的值 */
    IP_DATA_PROTOCOL_IPV6_ROUTE             = 0x2b,         /* Routing Header for IPv6协议标识的值 */
    IP_DATA_PROTOCOL_IPV6_FRAGMENT          = 0x2c,         /* Fragment Header for IPv6协议标识的值 */
    IP_DATA_PROTOCOL_ESP                    = 0x32,         /* Encapsulating Security Payload协议标识的值 */
    IP_DATA_PROTOCOL_AH                     = 0x33,         /* Authentication Header协议标识的值 */
    IP_DATA_PROTOCOL_ICMPV6                 = 0x3a,         /* ICMPV6协议标识的值 */
    IP_DATA_PROTOCOL_IPV6_NONEXT            = 0x3b,         /* No Next Header for IPv6协议标识的值 */
    IP_DATA_PROTOCOL_IPV6_OPTS              = 0x3c,         /* Destination Options for IPv6协议标识的值 */
    IP_DATA_PROTOCOL_IPV6_IPIP              = 0x5e,         /* IP-within-IP Encapsulation Protocol协议标识的值 */
    IP_DATA_PROTOCOL_IPCOMP                 = 0x6c,         /* IP Payload Compression Protocol协议标识的值 */

    IP_DATA_PROTOCOL_BUTT
};
typedef VOS_UINT8 IP_DATA_PROTOCOL_ENUM_UINT8;

/* IP数据承载协议 */
/*****************************************************************************
 枚举名    : IP_DATA_PROTOCOL_TYPE_ENUM
 协议表格  :
 ASN.1描述 : 数据承载协议
 枚举说明  : TTF内部实现枚举的数据类型
*****************************************************************************/
enum IP_DATA_TYPE_ENUM
{
    IP_DATA_TYPE_NULL                   = 0,    /* NULL */
    IP_DATA_TYPE_ICMP                   = 1,    /* ICMP */
    IP_DATA_TYPE_IGMP                   = 2,    /* IGMP */
    IP_DATA_TYPE_TCP                    = 3,    /* TCP */
    IP_DATA_TYPE_TCP_SYN                = 4,    /* TCP ACK */
    IP_DATA_TYPE_TCP_ACK                = 5,    /* TCP ACK */
    IP_DATA_TYPE_FTP_SIGNALLING         = 6,    /* FTP SIGNALLING */
    IP_DATA_TYPE_UDP                    = 7,    /* UDP */
    IP_DATA_TYPE_UDP_DNS                = 8,    /* UDP DNS */
    IP_DATA_TYPE_USER_HIGH              = 9,    /* user high data */

    IP_DATA_TYPE_BUTT
};
typedef VOS_UINT8 IP_DATA_TYPE_ENUM_UINT8;

/*****************************************************************************
  3 宏定义
*****************************************************************************/
#ifndef ntohs
#define ntohs(x)                            ((((VOS_UINT16)(x) & 0x00ff) << 8) | (((VOS_UINT16)(x) & 0xff00) >> 8))
#endif

#ifndef ntohl
#define ntohl(x)                            ((((VOS_UINT32)(x) & 0x000000ff) << 24) | (((VOS_UINT32)(x) & 0x0000ff00) <<  8) | \
                                             (((VOS_UINT32)(x) & 0x00ff0000) >>  8) | (((VOS_UINT32)(x) & 0xff000000) >> 24))
#endif

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
typedef struct
{
    IP_DATA_TYPE_ENUM_UINT8                 enParseDataType;
    VOS_UINT8                               ucIpVer;            /* IP 协议版本 */
    IP_DATA_PROTOCOL_ENUM_UINT8             enProto;            /* IPv4 Proto协议类型，IPv6为Next Header */
    VOS_UINT8                               ucFragmentFlag;
    VOS_UINT32                              ulSrcIpAddr;        /* IPv4 源IP ADDR */
    VOS_UINT32                              ulDstIpAddr;        /* IPv4 目的IP ADDR */

    VOS_UINT16                              usSrcPort;          /* IP 源端口号 */
    VOS_UINT16                              usDstPort;          /* IP 目的端口号 */
    VOS_UINT8                               ucIcmpType;         /* ICMP报文类型 */
    VOS_UINT8                               ucIcmpCode;         /* ICMP报文CODE */
    VOS_UINT16                              usIdentify;         /* IPv4 IDENTIFY字段 */

    VOS_UINT32                              ulTcpSeq;           /* TCP SEQ */
    VOS_UINT32                              ulTcpAckSeq;        /* TCP ACK SEQ */
}TTF_IP_DATA_PARAM_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
IP_DATA_TYPE_ENUM_UINT8 TTF_ParseIpDataType(VOS_UINT32 ulPid, TTF_MEM_ST *pMemPt);
VOS_UINT16 TTF_GetIpDataTraceLen
(
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pData,
    VOS_UINT16                          usSduLen
);
VOS_UINT32 TTF_GetTcpIpDataInfo(VOS_UINT32 ulPid, TTF_MEM_ST *pstSdu, TTF_IP_DATA_PARAM_STRU *pstParseParam);

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

#endif /* end of TtfIpComm.h */

