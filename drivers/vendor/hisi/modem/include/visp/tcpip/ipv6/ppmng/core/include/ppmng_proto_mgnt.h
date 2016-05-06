/******************************************************************************
 *
 *        Copyright 2003-2006  Huawei Technologies India Private Limited
 *                          All Rights Reserved
 *
 *------------------------------------------------------------------------------
 *                            ppmng_proto_mgnt.h
 *    Project Code:  VRP5.0
 *    Module Name:  IP6 PP
 *    Create Date:  2003/06/10
 *         Author:  Arun H S
 *     Description: Protocol Management Module of PP
 *------------------------------------------------------------------------------
 *  Modification History
 *  DATE        NAME             DESCRIPTION
 *  ----------------------------------------------------------------------------
 *  2003-06-10  Arun H S         Create
 ******************************************************************************/

#ifndef _IP6_PPMNGPROTOMGNT_H
#define _IP6_PPMNGPROTOMGNT_H

#ifdef __cplusplus
extern "C"{
#endif

/* Modified by Rajesh for defect id BYAD11233 */
/* 将IPV6协议开关表额规格扩展至15个,原有规格为10个,增加5个 */
#define PP_MAX_PROTO_TABLE          15


/*
 * Definitions for internet protocol version 4.
 * Per RFC 791, September 1981.
 */
#ifndef IPPROTO_HOPOPTS
#define IPPROTO_HOPOPTS    0        /* Hop-by-hop option header */
#endif
#ifndef IPPROTO_ICMP
#define    IPPROTO_ICMP    1        /* 控制报文协议 control message protocol */
#endif
#ifndef IPPROTO_IGMP
#define    IPPROTO_IGMP    2        /* 组管理协议 group mgmt protocol */
#endif
#ifndef IPPROTO_GGP
#define    IPPROTO_GGP     3        /* 路由 gateway^2 (deprecated) */
#endif
#ifndef IPPROTO_IPIP                /* IP协议上的IP ip over ip protocol */
#define IPPROTO_IPIP       4
#endif
#ifndef IPPROTO_TCP
#define    IPPROTO_TCP     6        /* 控制传输协议 tcp */
#endif
#ifndef IPPROTO_EGP
#define    IPPROTO_EGP     8        /* 外部路由协议 exterior gateway protocol */
#endif
#ifndef IPPROTO_PUP
#define    IPPROTO_PUP     12       /* pup */
#endif
#ifndef IPPROTO_UDP
#define    IPPROTO_UDP     17       /* user datagram protocol */
#endif
#ifndef IPPROTO_IDP
#define    IPPROTO_IDP     22       /* xns idp */
#endif
#ifndef IPPROTO_TP
#define    IPPROTO_TP      29       /* tp-4等级协商 tp-4 w/ class negotiation */
#endif
#ifndef IPPROTO_IPV6
#define IPPROTO_IPV6       41       /* 协议版本号6 IPv6 in IPv6 */
#endif
#ifndef IPPROTO_ROUTING
#define IPPROTO_ROUTING    43       /* 选路 IPv6 Routing header */
#endif
#ifndef IPPROTO_FRAGMENT
#define IPPROTO_FRAGMENT   44       /* IPv6 Fragmentation header */
#endif
#ifndef IPPROTO_GRE
#define    IPPROTO_GRE     47       /* 常规路由封装协议 Generic Route Encapsulation Protocol */
#endif
#ifndef IPPROTO_ESP
#define IPPROTO_ESP        50       /* IP数据 Ip Sec */
#endif
#ifndef IPPROTO_AH
#define IPPROTO_AH         51       /* IP数据 Ip Sec */
#endif
#ifndef IPPROTO_ICMPV6
#define IPPROTO_ICMPV6     58       /* 控制报文协议 ICMP6 */
#endif
#ifndef IPPROTO_NONE
#define IPPROTO_NONE       59       /* IP无下一项 IPv6 No next header */
#endif
#ifndef IPPROTO_DSTOPTS
#define IPPROTO_DSTOPTS    60       /* IP目的地址 IPv6 Destination header */
#endif
#ifndef IPPROTO_EON
#define    IPPROTO_EON     80       /* ISO cnlp */
#endif

 /* Modified by Rajesh for defect id BYAD11538 */
#ifndef   IPPROTO_OSPF
#define    IPPROTO_OSPF        89        /* ISO cnlp */
#endif


#ifndef IPPROTO_ENCAP
#define    IPPROTO_ENCAP    98        /* encapsulation header */
#endif

#ifndef IPPROTO_VRRP
#define    IPPROTO_VRRP    112        /*  VRRP */
#endif


#ifndef IPPROTO_MAX
#define    IPPROTO_MAX        256
#endif

#ifndef IPPROTO_DONE
#define IPPROTO_DONE    257 /* 标志扩展头和上层协议处理结束 */
#endif

#ifndef SLOWTIMEOUT
#define SLOWTIMEOUT         500
#endif

#ifndef FASTTIMEOUT
#define FASTTIMEOUT         200
#endif

#ifndef IPPROTO_RAW
#define    IPPROTO_RAW        255        /* raw IP packet */
#endif

#ifndef SOCK_RAW
#define SOCK_RAW        3               /* raw-protocol interface */
#endif


#ifndef IPPROTO_ISIS
#define IPPROTO_ISIS    124
#endif

/* Function Prototypes. */
ULONG IP6_PP_PM_RegisterHook (ULONG ulType, ULONG ulPriority, IP6_PP_Register pfIpFwHookFunc);

ULONG IP6_PP_PM_Get_PST (ULONG ulProtocolNumber, IP6_PP_PROTOSW_S **pstProtocolInfo);
ULONG IP6_PP_Get_PSTField (SHORT sType, UCHAR ucProtocol, IP6_PP_PROTOCOLFIELD ePfield, VOID *pvRetVal);
VOID IP6_PP_Slowtimo ();
/* END: Function Prototypes. */

#ifdef __cplusplus
}
#endif

#endif

