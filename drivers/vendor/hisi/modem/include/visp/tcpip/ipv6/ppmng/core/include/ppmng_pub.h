/******************************************************************************
 *
 *        Copyright 2003-2006  Huawei Technologies India Private Limited
 *                          All Rights Reserved
 *
 *------------------------------------------------------------------------------
 *                            ppmng_pub.h
 *    Project Code:  VRP5.0
 *    Module Name:  IP6 PP
 *    Create Date:  2003/06/10
 *         Author:  Arun H S
 *     Description: Declaration of public data structures of the PP Core 
 *               (Defined Here, Used by other Modules).
 *------------------------------------------------------------------------------
 *  Modification History                                                        
 *  DATE        NAME             DESCRIPTION                                    
 * -----------------------------------------------------------------------------
 *  2003-06-10  Arun H S         Create
 *  2006-05-11   luyao           为支持ARM CPU字节对齐特性，修改结构。
 ******************************************************************************/

#ifndef _IP6_PUB_H_
#define _IP6_PUB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/ipv6/ppmng/include/ppmng_api.h"
#define SYSTRC_IPV6_PPMNG_BASE      00

#define IP6_PPMNG_CORE ((SYSTRC_IPV6_PPMNG_BASE << 8) + 022) 
#define IP6_PP_CKSUM ((SYSTRC_IPV6_PPMNG_BASE << 8) + 32) 
#define IP6_PPMNG_CONTROL ((SYSTRC_IPV6_PPMNG_BASE << 8) + 011) 
#define IP6_PPMNG_DISTRIBUTE ((SYSTRC_IPV6_PPMNG_BASE << 8) + 015) 
#define IP6_PPMNG_EXTENSION ((SYSTRC_IPV6_PPMNG_BASE << 8) + 012) 
#define IP6_PPMNG_FORWARD ((SYSTRC_IPV6_PPMNG_BASE << 8) + 013) 
#define IP6_PPMNG_HDRUTILS ((SYSTRC_IPV6_PPMNG_BASE << 8) + 014) 
#define IP6_PPMNG_INIT ((SYSTRC_IPV6_PPMNG_BASE << 8) + 19)
#define IP6_PPMNG_INPUT ((SYSTRC_IPV6_PPMNG_BASE << 8) + 010) 
#define IP6_PPMNG_INTERMEDIATE ((SYSTRC_IPV6_PPMNG_BASE << 8) + 016) 
#define IP6_PPMNG_OUTPUT ((SYSTRC_IPV6_PPMNG_BASE << 8) + 18) 
#define IP6_PPMNG_PROTOMGNT ((SYSTRC_IPV6_PPMNG_BASE << 8) + 017) 
#define IP6_PPMNG_PPMNG ((SYSTRC_IPV6_PPMNG_BASE << 8) + 020) 
#define IP6_PPMNG_FAC ((SYSTRC_IPV6_PPMNG_BASE << 8) + 021) 
#define IP6_PPMNG_HA ((SYSTRC_IPV6_PPMNG_BASE << 8) + 35) 


/* IPv6 Stack Enable/Disable. */
#define IP6_PP_DISABLED         0
#define IP6_PP_ENABLED          1

#ifndef EUNREACH
#define EUNREACH 31  /* defect id : 5997 */
#endif

#define IP6_DEFAULT_HOPLIMIT    255;  /* 本机发送报文时缺省的Hop Limit的宏 */
#define IP6_DEFAULT_FLOWLABEL   0;   /* 本机发送报文时缺省的Flow Label的宏 */

#define IP6_MIN_MTU         1280    /* 接口上可配置的最小MTU */
/*#define IP6_MAX_MTU         1500    */ /* 接口上可配置的最大MTU, should be 65534 according to RFC */

/* 在不使用JumboPayload选项时,IPv6报文负载的最大长度 */
#define IPV6_MAXPACKET      65535

/* 接口上缺省的IPv6 MTU的值, 目前所有接口上缺省MTU是相同的 */
#define IP6_DEFAULT_MTU     1500

/* 转发报文时应减去的Hop Limit的值 */
#define IPV6_HLIMDEC        1

/* 下面的宏用于调用函数IP6_Output时设置参数lFlag */
/* Different Values for the lFlags used in IP6_PP_Output () */
#define IPV6_UNSPECSRC              0x00000001   /* 表示发出的报文源地址为0 */
#define IPV6_DADPACKET              0x00000002   /* 表示发出的是用于DAD检测的报文 */

#define IPV6_USEMINMTU              0x00000004
#define IPV6_DONT_FRAG              0x00001000

#define IPV6_NEXTHOP_SPECIFIED      0x00000010
#define IPV6_INTERMEDIATE_PKT       0x00000020

/* User Application has either directed use of Kernel Default Hop Limit for Outgoing Unicast packets */  
#define IPV6_USEDEFAULT_HOPLIMIT    0x00000040

/* END: Different Values for the lFlags used in IP6_PP_Output () */

/* 发出组播报文的缺省HOP LIMIT值 */
#define IP6_DEFAULT_MULTICAST_TTL     255

/* 组播选项结构IP6_MOPTIONS_S中im6o_multicast_loop的缺省值 */
#define IP6_DEFAULT_MULTICAST_LOOP      1

/* 下面的宏用于判断一个头类型是否为扩展头(包括IPPROTO_NONE) */
#define IP6_ISEXTENSIONHEADER(proto) \
    ( (proto == IPPROTO_HOPOPTS) || (proto == IPPROTO_ROUTING) || \
      (proto == IPPROTO_FRAGMENT) || (proto == IPPROTO_DSTOPTS) || \
      (proto == IPPROTO_NONE) )

/* 用于操作扩展头的宏 */
#define IP6_EXTHDR_GET(m, val, type, off, len, mid, ret) \
{ \
    MBUF_MAKE_MEMORY_CONTINUOUS( (m), (off)+(len), (mid), (ret) ); \
    if ( (ret) == 0 ) \
    { \
        (val) = (type)(MBUF_MTOD(m, UCHAR *) + off); \
    } \
}

/*
   获得扩展头的长度,支持逐跳,目的地和路由三种扩展头
 */
#define IP6_GET_HDRLEN( phdr ) \
(NULL == (phdr) ? 0 : (((IP6_EXT_S *) (phdr))->ip6e_uclen + 1) << 3)

/*
   下面的宏用于将扩展头数据拷贝到报文MBUF中, 拷贝时应按照从后到前的顺序进行
   参数如下：
phdr  : 扩展头数据的指针
type  : 这个扩展头的类型
pmbuf : 报文MBUF的指针
off   : MBUF中前面剩余空间的长度
nxt   : 下一个扩展头的类型
pdata : 拷贝结束后指向MBUF中这个扩展头的指针

说明:这个宏目前支持逐跳扩展头, 目的地扩展头和路由扩展头
 */
#define ADD_EXTHDR(phdr, type, pmbuf, off, nxt, pdata, datatype)\
{\
    if (phdr) \
    {\
        off -= (((IP6_EXT_S *)phdr)->ip6e_uclen + 1) << 3; \
        pdata = (datatype) (MBUF_MTOD((pmbuf), UCHAR *) + off); \
        (VOID)TCPIP_Mem_Copy(pdata, (((IP6_EXT_S *)phdr)->ip6e_uclen + 1)<<3, phdr, (((IP6_EXT_S *)phdr)->ip6e_uclen + 1)<<3); \
        ((IP6_EXT_S *)pdata)->ip6e_ucnxt = nxt; \
        nxt = type; \
    }\
}

/* Copy IP6 Address from the Structure to the ULONG */
#define PP_COPY_IP6ADDR_STRUCT_TO_ARRAY(dst,src)\
{\
    dst[0] = (src)->s6_addr32[0];\
    dst[1] = (src)->s6_addr32[1];\
    dst[2] = (src)->s6_addr32[2];\
    dst[3] = (src)->s6_addr32[3];\
}

/* Copy IP6 Address from the ULONG to the Structure */
#define PP_COPY_IP6ADDR_ARRAY_TO_STRUCT(dst,src)\
{\
    (dst)->s6_addr32[0] = src[0];\
    (dst)->s6_addr32[1] = src[1];\
    (dst)->s6_addr32[2] = src[2];\
    (dst)->s6_addr32[3] = src[3];\
}

/* Judge IP6 Address Zeor or Not */
#define PP_Judge_IP6ADDR_ARRAY_VALUE_ZERO(ipaddr)\
    (0 == (ipaddr)->s6_addr32[0])&&(0 == (ipaddr)->s6_addr32[0])&&\
    (0 == (ipaddr)->s6_addr32[0])&&(0 == (ipaddr)->s6_addr32[0])



/************************************************************************************/
/* Start Of IP在MBUF中的TAG域里对IP报文的表示 */

/* 在MBUF的TAG域里设置，表示是本机发送的IP报文 */
#define IP6_PKT_OURSENDPKT          0x00000001

/* 在MBUF的TAG域里设置，表示是转发的IP报文 */
#define IP6_PKT_FORWARDPKT          0x00000002

/* 在MBUF的TAG域里设置，表示该IP报文的目地地址是本机某个接口的地址 */
#define IP6_PKT_ISOURS              0x00000004

/* 表示本报文是DAD报文 */
#define IP6_PKT_ISDADPKT            0x00000008

/* 表示本报文的源地址是0  */
#define IP6_PKT_UNSPECSRC           0x00000010

#define IPV6_PKT_USEMINMTU          0x00000100

/* IPV6报文不分片标志,注意与Ppmng_api.h保持一致 */
#define IPV6_PKT_DONTFRAG           0x00000200

/*
    Defect Id: BYAD03474
    Description: ICMP error not generated when the pkt size is greater than path mtu on v6 side
*/
#define IPV6_PKT_ISINTERMEDIATE     0x00000400 /* BYAD04518 */

/* 
 * Defect id : BYAD02397 Reason: Processing of extension headers in main board also Modified by Arun H S on 08 Oct 2003
 * These flags added for FE functionality and for further processing in main board.
 * these flags indicates till which header or ext hdr the packet is been processed
 */
#define IP6_PKT_HDR_BASE            0x00001000
#define IP6_PKT_HDR_EXT_HBH         0x00002000
#define IP6_PKT_HDR_EXT_FRAG        0x00004000
#define IP6_PKT_HDR_EXT_DST         0x00008000
#define IP6_PKT_HDR_EXT_ROUTE       0x00010000
#define IP6_PKT_HDR_EXT_IPV6        0x00020000 /* For the next hdr field, not the base */
#define IP6_PKT_HDR_EXT_UL          0x00040000
/* FIB Notify */
#define PP_FORWARD_FIB_NOTIFY       0x00080000

/*modified by pei gangqiang for VRP_MODULE_QOS_NEST_POLICY_II*/
#define IP6_PKT_HDR_EXT_TCP            0x00100000
#define IP6_PKT_HDR_EXT_UDP            0x00200000
#define IP6_PKT_HDR_EXT_ICMPV6         0x00400000

/* End of IP在MBUF中的TAG域里对IP报文的表示 */
/*************************************************************************************/

/* 下面的宏用于判断一个报文是否是DAD报文 */
#define IP6_ISDADPACKET(pstMBuf) \
    (((MBUF_IP6_PACKET_INFO_S *)MBUF_GET_TAG_NETWORK_IP6_PTR(pstMBuf))->ulIpPktType & IP6_PKT_ISDADPKT)

/*
下面的宏用于释放一个MBUF链,
目前MBUF中没有相应的宏,MBUF_Destroy只释放一个MBUF,以后应将这个宏加到MBUF模块中
*/
#define IP6_FREE_MBUF_CHAIN(pstMBuf) \
{ \
    MBUF_S *pTmpMBuf = pstMBuf; \
    \
    while (NULL != pTmpMBuf) \
    { \
        pstMBuf = MBUF_GET_PTR_NEXT_MBUF(pTmpMBuf); \
        MBUF_Destroy(pTmpMBuf); \
        pTmpMBuf = pstMBuf; \
    } \
}



typedef enum tagProtoSWField 
{
    IP6_PP_SOCK_TYPE = 1,
    IP6_PP_DOMAIN,
    IP6_PP_PROTOCOL_NUMBER,
    IP6_PP_FLAGS,
    IP6_PP_INPUT_FN,
    IP6_PP_OUTPUT_FN,
    IP6_PP_CTL_INPUT_FN,
    IP6_PP_CTL_OUTPUT_FN,
    IP6_PP_USR_REQUEST_FN,
    IP6_PP_INIT_FN,
    IP6_PP_FASTTIMEO_FN,
    IP6_PP_SLOWTIMEO_FN,
    IP6_PP_DRAIN_FN,
    IP6_PP_SYSCTL_FN
}IP6_PP_PROTOCOLFIELD;

/*w39533 2004-11-08 sync D24*/
/* Modified by Rajesh for Product support Defect id BYAD11615 */

typedef enum tagProduct
{
    IP6_PRODUCT_GSR =1,
    /*syn D038 by x36308 20005-7-5*/
    IP6_PRODUCT_PPI
}IP6_PRODUCT;

#define IP6_PRODUCT_GSR_REG          0x00000001
/*syn D038 by x36308 2005-7-5*/
/*added by huweihua for a28d00455 2005_05_05*/
#define VRP_MODULE_IPV6_REG          0x00000002
#define VRP_MODULE_IPV6_TUNNEL_REG          0x00000004
/*ended*/

/*Added by wangbin, for DTS2015102607923 ，解决发送IP报文频繁使用TCPIP_Rand_Safe导致性能恶化问题, 2015/10/24 */
#define IP_PP6_NEWID_TIMEOUT    2
#define IP6ID_UPDATECOUNT     0x400

/* NE5000 macro remove */
#define IP6_PRODUCT_PPI_REG          0x00000002

#define IPV6_INTF_STAT_GET         1    
#define IPV6_INTF_STAT_CLEAR       2     
#define IPV6_GLOBAL_STAT_GET    3
#define IPV6_GLOBAL_STAT_CLEAR 4




 typedef struct tagGSRFuncRegister
{
  /* ADDRMNG related function */ 
   VOID  (*pfAGT_DisplayIp6Brief)(ULONG);
   ULONG (*pfADP_MIBIP6_GetNDMIBEntryFromIO)(IFNET_S  * pstIf , 
                            VOID * pstOutNet2MediaEntry, ULONG ulRequestType);
   /* Need to  pass  *IP6_ND_Net2MediaTbl_S , in place of VOID * ,  This is to avoid dependency  */
   ULONG (*pfADP_GetFib6RouteLen)(VOID); /*Added for VRPV5R001-PLT-E006 */
   /*syn D038 by x36308 2005-7-5*/
   /* guohongtao 29200 2005.03.05 for NHP downloading */
   ULONG (*pfFIB6_8011_NHPSync_TimerDownload)(VOID); 
   ULONG (*pfADP_IP6_Addr_Sync_NegMtu_FromIO)(ULONG);
}GSR_FUNC_REGISTER_S;

/*syn D038 by x36308 2005-7-5*/
/* NE5000 macro remove */
 typedef struct tagIP6PPPPIFuncRegister
{
    ULONG (*pfPPI_INTF_SetAttribute)(IFNET_S * pstIf, ULONG ulSetCmd, VOID * pData);
    ULONG (*pfPPI_IPV6_NdEntryOper)(ULONG ulOperType, VOID *pstNdEntry);
    VOID (*pfPPI_FW_PrintProductInfo)(ULONG ulProductInfoType, VOID *pstPdtInfoStruct, CHAR *pszBuf);
    ULONG (*pfPPI_IPV6_InterfaceStatGlobal)(ULONG ulOperType, VOID *pstIp6Stat);
    ULONG (*pfPPI_IPV6_InterfaceStatOper)(ULONG ulOperType, ULONG ulIpv6IfIndex, VOID *pstIp6Stat);

}IP6_PP_PPI_FUNC_REGISTER_S;

/* END: Protcol Management related Data Structures */


/* 为了引用方便，进行如下宏定义*/
#define s6_addr      u6_addr.u6_ucaddr
#define s6_addr8     u6_addr.u6_ucaddr
#define s6_addr16    u6_addr.u6_usaddr
#define s6_addr32    u6_addr.u6_uladdr

#ifndef _IP6_S
#define _IP6_S
typedef struct tagIP6_S {

    union {
        struct ip6_hdrctl {

            ULONG ul_ip6_tclass_flow;   /* 4 bits unused, 8 bits traffic class and 20 bits of flow-ID */
            USHORT us_ip6_plen;         /* 16 bits payload length */
            UCHAR uc_ip6_nxt;           /* 8 bits next header */
            UCHAR uc_ip6_hlim;          /* 8 bits hop limit */

        } ip6_un1;

        struct ip6_hdrctl1 {

#if (VRP_LITTLE_ENDIAN == VRP_YES)
/*syn D038 by x36308 2005-7-5*/
/*peigangqiang modified for VRP_MODULE_QOS_NEST_POLICY_II*/
        /*ULONG ul_ip6_flowid:20;*/           /*20 bits flow id*/
        /*ULONG uc_ip6_Trafclass:8;*/     /* 8 bits traffic class */
           /*ULONG uc_ip6_ver:4; */               /* 4 bits version */

            /* LITTLE_ENDIAN */
            UCHAR uc_ip6_unused:4;      /* 4 bits traffic class */
            UCHAR uc_ip6_ver:4;         /* 4 bits version */
#else
            /*ULONG uc_ip6_ver:4; */               /* 4 bits version */
            /*ULONG uc_ip6_Trafclass:8; */     /* 8 bits traffic class */
            /*ULONG ul_ip6_flowid:20; */         /*20 bits flow id*/

/* BIG_ENDIAN */
            UCHAR uc_ip6_ver:4;     /* 4 bits version */
            UCHAR uc_ip6_unused:4;      /* 4 bits traffic class */
#endif
        } ip6_un2;

    } ip6_ctlun;

    IN6ADDR_S ip6_stSrc;                /* source address */
    IN6ADDR_S ip6_stDst;                /* destination address */

} IP6_S;
#endif


#define ip6_ucVer                ip6_ctlun.ip6_un2.uc_ip6_ver
/*peigangqiang modified for VRP_MODULE_QOS_NEST_POLICY_II*/
/*syn D038 by x36308 2005-7-5*/
/*#define ip6_ucTrafclass      ip6_ctlun.ip6_un2.uc_ip6_Trafclass*/
/*#define ip6_ulFlowId           ip6_ctlun.ip6_un2.ul_ip6_flowid*/
#define ip6_ulFlow              ip6_ctlun.ip6_un1.ul_ip6_tclass_flow
#define ip6_usPLen             ip6_ctlun.ip6_un1.us_ip6_plen
#define ip6_ucNxtHdr         ip6_ctlun.ip6_un1.uc_ip6_nxt
#define ip6_ucHLim             ip6_ctlun.ip6_un1.uc_ip6_hlim


#define IP6_FLOWINFO_MASK       VOS_HTONL(0x0fffffff)  /* flow info (28 bits) */
#define IP6_FLOWLABEL_MASK      VOS_HTONL(0x000fffff)  /* flow label (20 bits) */

#define IPV6_VERSION        0x06         /* the macro used to set or get the flow label */

#if (VRP_LITTLE_ENDIAN == VRP_YES)
/* LITTLE_ENDIAN */
#define IPV6_VERSION_MASK   0xf0

#else
/* BIG_ENDIAN */
#define IPV6_VERSION_MASK   0x0f

#endif

/* Add for 新需求, by mengzechao176865, at 2011-02-23. 
   修改原因: 将IPv6头的TOS映射到VLAN优先级,其中魔鬼字的定义 */
#define IPV6_FLOWLABELBIT       20      /* IPV6头 flow label字段BIT数 */
#define IPV6_TRAFFICCLASSBIT    8       /* IPV6头 Traffic class 字段BIT数 */
#define IPV6_TOSPRIBIT          3       /* IPV6头 Traffic class优先级BIT数 */

/*syn D038 by x36308 2005-7-5*/
/* Get different fields from the first four bytes in IPv6 Header, Input ULONG variable is network byte order*/
#define IPV6_HDR_GET_FLOWLABEL(ip6_ulFlow)    (VOS_NTOHL(ip6_ulFlow) & 0x000fffff)

#define IPV6_HDR_GET_TRAFFICCLASS(ip6_ulFlow)    ((VOS_NTOHL(ip6_ulFlow) & 0x0ff00000)>> 20)

#define IPV6_HDR_GET_VERSION(ip6_ulFlow)    ((VOS_NTOHL(ip6_ulFlow) & 0xf0000000)>> 28)

/* Put different fields in the first four bytes in IPv6 Header */
#define IPV6_HDR_PUT_FLOWLABEL(pip6_ulFlow, ip6_Value)\
{                                               \
    ULONG * pulFlow = (ULONG *)(pip6_ulFlow);       \
    *pulFlow = VOS_HTONL((VOS_NTOHL(*pulFlow) & 0xfff00000) | ((ULONG)ip6_Value)); \
}

#define IPV6_HDR_PUT_TRAFFICCLASS(pip6_ulFlow, ip6_Value)\
{                                               \
    ULONG * pulFlow = (ULONG *)(pip6_ulFlow);       \
    *pulFlow = VOS_HTONL((VOS_NTOHL(*pulFlow) & 0xf00fffff) | (((ULONG)ip6_Value) << 20)); \
}

#define IPV6_HDR_PUT_VERSION(pip6_ulFlow, ip6_Value)\
{                                               \
    ULONG * pulFlow = (ULONG *)(pip6_ulFlow);       \
    *pulFlow = VOS_HTONL((VOS_NTOHL(*pulFlow) & 0x0fffffff) | (((ULONG)ip6_Value) << 28)); \
}


#define IPV6_RECVTCLASS     29 /* bool; recv traffic class values */

#define IPV6_DONTFRAG       30

#ifndef _SOCKADDR_IN6_S
#define _SOCKADDR_IN6_S
typedef struct tagSOCKADDR_IN6 {
    UCHAR       ucSin6_len;         /* length of this struct(sa_family_t)*/
    UCHAR       ucSin6_family;      /* AF_INET6 (sa_family_t) */
    USHORT      usSin6_port;        /* Transport layer port # (in_port_t)*/
    ULONG       ulSin6_flowinfo;    /* IP6 flow information */
    IN6ADDR_S   stSin6_addr;        /* IP6 address */
    ULONG       ulSin6_scope_id;    /* scope zone index */
}SOCKADDR_IN6_S;
#endif


/* END: Basic Header Data Structures. */


/* Extension Header Data Structures. */

/*
因为结构IP6_EXT_S长度不是4的倍数,所以需要按照1个字节进行对齐.
以下各结构的情况相同.
*/

#pragma    pack( 1 )
typedef struct tagIP6_EXT{
    UCHAR   ip6e_ucnxt;   /* next header */
    UCHAR   ip6e_uclen;   /* header length */
}IP6_EXT_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif





#pragma    pack( 1 )
typedef struct tagIP6_OPT {
    UCHAR ip6o_uctype;    /* option type */
    UCHAR ip6o_uclen;     /* option data length, in octets */
}IP6_OPT_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif




typedef struct tagIP6_ROUTE_TYPE0 {
    UCHAR  ip6r0_ucnxt;       /* next header */
    UCHAR  ip6r0_uclen;       /* length in units of 8 octets, exclude first 8 octets */
    UCHAR  ip6r0_uctype;      /* always zero */
    UCHAR  ip6r0_ucsegleft;   /* segments left */
    ULONG  ip6r0_ulreserved;  /* reserved field */

    /* followed by up to 127 struct in6_addr */
}IP6_ROUTE_TYPE0_S;

/* 0型路由扩展头中type域的值 */
#define IPV6_RTHDR_TYPE_0       0

/* Fragment Header */
typedef struct tagIP6_FRAG {
    UCHAR  ip6f_ucnxt;        /* next header */
    UCHAR  ip6f_ucreserved;   /* reserved field */
    USHORT ip6f_usofflg;      /* offset, reserved, and flag */
    ULONG  ip6f_ulident;      /* identification */
}IP6_FRAG_S;

/* 
 * Fragment Group Structure. 
 * Linked List For the given source addr, dest addr and identification in the Reassembly Queue.
 */
typedef struct tagIP6FRAG {
    ULONG ip6f_ulHead;
    USHORT ip6f_usLen;
    UCHAR ip6f_ucNxt;
    UCHAR ip6f_ucHlim;
    /* must not override the above members during reassembling */
    struct tagIP6FRAG *ip6f_pstNext;
    struct tagIP6FRAG *ip6f_pstPrev;
    MBUF_S *ip6f_pstMBuf;
    ULONG ip6f_ulOff;    /* offset in ip6f_pstMBuf to next header */
    ULONG ip6f_ulFragLen;  /* fragmentable part length */
    ULONG ip6f_ulFragOff;  /* fragment offset */
    USHORT ip6f_usMff;  /* more fragment bit in frag off */
    UCHAR  ucPadding[2];
}IP6FRAG_S;

/* Reassembly Queue. */
typedef struct tagIP6REASSQUEUE {
    ULONG ip6q_ulHead;
    USHORT ip6q_usLen;
    UCHAR ip6q_ucNxt;   /* ip6f_nxt in first fragment */
    UCHAR ip6q_ucHlim;
    IP6FRAG_S *ip6q_pstfNext;
    IP6FRAG_S *ip6q_pstfPrev;
    ULONG ip6q_ulId;
    USHORT ip6q_usTTL;
    UCHAR ucPadding[2];
    IN6ADDR_S ip6q_stSrc, ip6q_stDst;
    struct tagIP6REASSQUEUE *ip6q_pstqNext;
    struct tagIP6REASSQUEUE *ip6q_pstqPrev;
    LONG ip6q_lUnFragLen; /* len of unfragmentable part */
}IP6REASSQUEUE_S;

#if (VRP_BIG_ENDIAN == VRP_YES)
/* BIG_ENDIAN */
#define IP6F_OFF_MASK       0xfff8  /* mask out offset from _offlg */
#define IP6F_RESERVED_MASK  0x0006  /* reserved bits in ip6f_offlg */
#define IP6F_MORE_FRAG      0x0001  /* more-fragments flag */
#else 
/* LITTLE_ENDIAN */
#define IP6F_OFF_MASK       0xf8ff  /* mask out offset from _offlg */
#define IP6F_RESERVED_MASK  0x0600  /* reserved bits in ip6f_offlg */
#define IP6F_MORE_FRAG      0x0100  /* more-fragments flag */
#endif 

typedef struct tagIP6_EXTHDRS_S {
    IP6_S       *ip6e_pstip6;      /* IPv6头的指针 */
    IP6_HBH_S   *ip6e_psthbh;      /* 逐跳扩展头的指针 */
    IP6_DEST_S  *ip6e_pstdest1;    /* 路由扩展头之前的目的地扩展头指针 */
    IP6_ROUTE_S *ip6e_pstrthdr;    /* 路由扩展头的指针 */
    IP6_DEST_S  *ip6e_pstdest2;    /* 路由扩展头之后的目的地扩展头指针 */
}IP6_EXTHDRS_S;

/* END: Extension Header Data Structures. */


#define ip6po_nexthop       ip6po_pstNHinfo->stip6po_nhi_nexthop.stSin6_addr




typedef struct tagIP6_RECVPKTOPTS{
    MBUF_S *pstHead;       /* head of mbuf chain of this struct */

    MBUF_S *pstHlim;       /* received hop limit */
    MBUF_S *pstPktinfo;    /* packet information of rcv packet */
    MBUF_S *psthbh;        /* HbH options header of rcv packet */
    MBUF_S *pstdest1;      /* Dest opt header of rcv packet */
    MBUF_S *pstdest2;      /* Dest opt header (after rthdr) of rcv packet */
    MBUF_S *pstrthdr;      /* Routing header of rcv packet */
}IP6_RECVPKTOPTS_S;

/* Argument structure for IPV6_JOIN_GROUP and IPV6_LEAVE_GROUP. */
/* 用于设置选项 IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP的参数 */
typedef struct tagIP6_Mreq {
    IN6ADDR_S stIp6multiaddr;       /* IP multicast address of group */
    ULONG ulIfIndex;                /* local address of interface */
}IP6_PP_MREQ_S;

/* END: Control Options Data Structures. */

/* IPv6 Statistics */

#define IP6_PP_INCREMENT       0
#define IP6_PP_DECREMENT       1


typedef enum tageIP6_STATISTICS
{
       IP6_TOTALRECEIVED = 1,   /* total packets received */
       IP6_TOOSHORT,            /* packet too short */
       IP6_TOOSMALL,            /* not enough data */
       IP6_HOPLIMITEXCEED,      /* hop limit exceed */
       IP6_BADHEADER,           /* error in header processing */
       IP6_BADOPTION,           /* error in option processing */    
       IP6_FRAGMENTS,           /* fragments received */
       IP6_REASSEMBLED,         /* total packets reassembled ok */
       IP6_FRAGDROPPED,         /* frags dropped (dups, out of space) */
       IP6_FRAGTIMEOUT,         /* fragments timed out */
       IP6_FAILEDFRAGMENTS,     /* Fragments Failed to Sent Out. */
       IP6_NOPROTO,             /* unknown or unsupported protocol */
       IP6_DELIVERED,           /* datagrams delivered to upper level*/
       IP6_LOCALOUT,            /* total ipv6 packets generated */
       IP6_FORWARD,             /* packets forwarded */
       IP6_NOROUTE,             /* packets discarded due to no route */
       IP6_TOOBIG,              /* packets discarded due to bigger than mtu*/
       IP6_FRAGMENTED,          /* datagrams sucessfully fragmented */
       IP6_OFRAGMENTS,          /* output fragments created */
       IP6_INMULTICASTS,        /* multicast packets received */
       IP6_NOTMEMBER,           /* donot join this multicast group */
       IP6_OUTMULTICASTS,       /* multicast packets sent */
       IP6_DSTADDRERR,          /* error in incoming dest addr (invalid and unsupported) */

/* TODO: Where will this happen ??? - this is a MIB requirement */
       IP6_INDISCARDS,          /* Input Dgms which had no pbms, but were discarded due to lack of buffer space */
       IP6_OUTDISCARDS          /* Output Dgms which had no pbms, but were discarded due to lack of buffer space */
}IP6_PP_STATISTICS;

/* END: IPv6 Statistics */


/* END: Intermediate Processing. */
typedef ULONG (*IP6_PP_Register_Notify) (ULONG ulRoutingFlag);

#define IP6_PP_MAX_NOTIFY_REGISTER 10

/*
 * Defect Id: BYAD08299
 * Description: Add Log Info for the PPMNG part as IPv4
 */
typedef enum tageIP6_ICINFO
{
    IP6_REASFULL = 0,
    /*syn D038 by x36308 2005-7-5*/
    IP6_REASPAFULL,
    IP6_IC_RPCCALLFAIL
} IP6_PP_ICINFO;


 /*w39533 2004-11-08 sync D24*/
 /* Begin : Defect ID: BYAD011817,     Modifier:Rajesh,   Date:2004/9/15 
     Reason   : Component issues*/

 typedef struct tagSocket_CALLBACKUP_SET_S
{
    ULONG (*pfIP6_PP_SH_RegisterCliChangeNotify)(ULONG (* pfIP6_PP_NotifyCliChange)(ULONG ulCliState));
   
}Socket_CALLBACKUP_SET_S;

#define  PP6_FLOWSTAT_MAXNUM         8/*最多支持8个,如AH、ESP、IKE、OSPFv3、RIPng*/

#define PP6_PKT_STAT_RECV    0x1
#define PP6_PKT_STAT_SEND    0x2
#define PP6_PKT_STAT_SENDERR 0x3

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _IP6_PUB_H_ */

