/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TcpIpTypeDef.h
  版 本 号   : 初稿
  作    者   : y00151394
  生成日期   : 2013-07-25
  最近修改   :
  功能描述   : 定义和TCP/IP协议栈相关的类型
  函数列表   :
  修改历史   :
  1.日    期   : 2013-07-25
    作    者   : y00151394
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TCP_IP_TYPE_DEF_H__
#define __TCP_IP_TYPE_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#pragma warning(disable:4200)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
/*Ehternet Max MTU*/
#define ETH_MAX_MTU                 (1500)

/* Define IP Version */
#define IP_VERSION_V4               (4)
#define IP_VERSION_V6               (6)

/* Define IPV4/IPV6 Address Length */
#ifndef IPV4_ADDR_LEN
#define IPV4_ADDR_LEN               (4)
#endif

#ifndef IPV6_ADDR_LEN
#define IPV6_ADDR_LEN               (16)
#endif

/*IPv4和IPv6头长度*/
#define IPV4_HDR_LEN                (20)
#define IPV6_HDR_LEN                (40)

/* IPv4 flags. network byte order*/
#define IPV4_MF_MASK                (0x2000)      /* Flag: "More Fragments" */
#define IPV4_DF_MASK                (0x4000)      /* Flag: "Don't Fragment" */
#define IPV4_OFFSET_MASK            (0x1FFF)      /* Fragment Offset part */

/*IPv6 Fragment Flg*/
#define IPV6_MF_MASK                (0x0001)        /*Flag : More Fragments*/
#define IPV6_OFFSET_MASK            (0xFFF8)        /*Fragment Offset part*/
#define IPV6_FLOW_LABLE_MASK        (0x000FFFFFUL)  /* FlowLable Mask, FlowLabel length is  20bit*/

/* Protocol field of IPv4 header. */
#define IPV4_PROTOCOL_ICMP          (1)         /* IP承载协议是ICMP */
#define IPV4_PROTOCOL_TCP           (6)         /* IP承载协议是TCP  */
#define IPV4_PROTOCOL_UDP           (17)        /* IP承载协议是UDP  */
#define IPV4_PROTOCOL_ESP           (50)        /* IPSec ESP */
#define IPV4_PROTOCOL_AUTH          (51)        /* IPSec AH */


/* Nextheader fields of IPV6 header. reference linux ipv6 implement. */
#define IPV6_NEXTHDR_HOP            (0)       /*Hop-by-hop option header*/
#define IPV6_NEXTHDR_TCP            (6)       /*TCP segment*/
#define IPV6_NEXTHDR_UDP            (17)      /*UDP message*/
#define IPV6_NEXTHDR_IPV6           (41)      /*IPv6 in IPv6*/
#define IPV6_NEXTHDR_ROUTING        (43)      /*Routing header*/
#define IPV6_NEXTHDR_FRAGMENT       (44)      /*Fragmentation/reassembly header*/
#define IPV6_NEXTHDR_ESP            (50)      /*Encapsulating security payload*/
#define IPV6_NEXTHDR_AUTH           (51)      /*Auhtentication header*/
#define IPV6_NEXTHDR_ICMP           (58)      /*ICMP for IPv6*/
#define IPV6_NEXTHDR_NONE           (59)      /*No next header*/
#define IPV6_NEXTHDR_DEST           (60)      /*Destination options header*/
#define IPV6_NEXTHDR_MOBILITY       (135)     /*Mobility header*/
#define IPV6_NEXTHDR_MAX            (255)

/*Get IP Version*/
#define IP_GET_VERSION(pucIpPkt)                ((pucIpPkt)[0] >> 4)

/*Get IPv6 Traffic Class*/
#define IPV6_TRAFFIC_CLASS(pstIpv6Hdr)          ((((pstIpv6Hdr)->ucPriority) << 4) | ((((pstIpv6Hdr)->aucFlowLabel[0]) & 0xF0) >> 4))

/*Get IPv6 Flow Lable*/
#define IPV6_FLOW_LABLE(pstIpv6Hdr)             (VOS_UINT32)(((((pstIpv6Hdr)->aucFlowLabel[0]) & 0x0F) << 16) \
                                                            | (((pstIpv6Hdr)->aucFlowLabel[1]) << 8) \
                                                            | (((pstIpv6Hdr)->aucFlowLabel[2])))

/* Get Ipv6 Option Len */
#define IPV6_OPTION_LEN(pstOptHdr)              (((pstOptHdr)->ucHdrLen + 1) << 3)


/*define transfer between network byte order and host byte order*/
#if (VOS_BYTE_ORDER == VOS_BIG_ENDIAN)
#define IP_NTOHL(x)    (x)
#define IP_HTONL(x)    (x)
#define IP_NTOHS(x)    (x)
#define IP_HTONS(x)    (x)
#else
#define IP_NTOHL(x)    ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))

#define IP_HTONL(x)    ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))

#define IP_NTOHS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#define IP_HTONS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#endif  /* _BYTE_ORDER==_LITTLE_ENDIAN */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
 结构名    : ICMPV4_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : ICMPv4头中类型定义
*****************************************************************************/
enum ICMPV4_TYPE_ENUM
{
    ICMPV4_TYPE_ECHOREPLY            = 0,           /* Ping Reply*/
    ICMPV4_TYPE_DEST_UNREACH         = 3,           /* Destination Unreachable*/
    ICMPV4_TYPE_SRC_QUENCH           = 4,           /* Source Quench */
    ICMPV4_TYPE_REDIRECT             = 5,           /* Redirect (change route) */
    ICMPV4_TYPE_ECHO                 = 8,           /* Ping Request */
    ICMPV4_TYPE_TIME_EXCEEDED        = 11,          /* Time Exceeded */
    ICMPV4_TYPE_PARA_PROBLEM         = 12,          /* Parameter Problem */
    ICMPV4_TYPE_TIMESTAMP            = 13,          /* Timestamp Request */
    ICMPV4_TYPE_TIMESTAMPREPLY       = 14,          /* Timestamp Reply */
    ICMPV4_TYPE_INFO_REQUEST         = 15,          /* Information Request */
    ICMPV4_TYPE_INFO_REPLY           = 16,          /* Information Reply */
    ICMPV4_TYPE_ADDRESS              = 17,          /* Address Mask Request */
    ICMPV4_TYPE_ADDRESS_REPLY        = 18,          /* Address Mask Reply */

    ICMPV4_TYPE_BUTT
};


/*****************************************************************************
 结构名    : ICMPV6_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : ICMPv6头中类型定义
*****************************************************************************/
enum ICMPV6_TYPE_ENUM
{
    ICMPV6_TYPE_ECHOREQUEST          = 128,
    ICMPV6_TYPE_ECHOREPLY            = 129,
    ICMPV6_TYPE_RS                   = 133,
    ICMPV6_TYPE_RA                   = 134,
    ICMPV6_TYPE_NS                   = 135,
    ICMPV6_TYPE_NA                   = 136,
    ICMPV6_TYPE_REDIRECT             = 137,
    ICMPV6_TYPE_BUTT
};

/*****************************************************************************
 结构名    : TCP_OPTION_ITEM_KIND_ENUM
 协议表格  : 定义TCP选项中的类型
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
enum TCP_OPTION_ITEM_KIND_ENUM
{
    TCP_OPTION_ITEM_KIND_EOL        = 0,                     /*End of Option List*/
    TCP_OPTION_ITEM_KIND_NOP        = 1,                     /*No Operation*/
    TCP_OPTION_ITEM_KIND_MSS        = 2,                     /*MSS*/
    TCP_OPTION_ITEM_KIND_WINSCALE   = 3,                     /*Window Scale shitf count*/
    TCP_OPTION_ITEM_KIND_SACKPER    = 4,                     /*SACK Permitted*/
    TCP_OPTION_ITEM_KIND_SACK       = 5,                     /*SACK*/
    TCP_OPTION_ITEM_KIND_TIMESTAMP  = 8,                     /*时间戳*/
    TCP_OPTION_ITEM_KIND_BUTT       = 254
};

/*****************************************************************************
 结构名    : TCP_HDR_FLAG_ENUM
 协议表格  : 定义TCP头中的标志位
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
enum TCP_HDR_FLAG_ENUM
{
    TCP_HDR_FLG_FIN  = 0x1,
    TCP_HDR_FLG_SYN  = 0x2,
    TCP_HDR_FLG_RST  = 0x4,
    TCP_HDR_FLG_PSH  = 0x8,
    TCP_HDR_FLG_ACK  = 0x10,
    TCP_HDR_FLG_URG  = 0x20,
    TCP_HDR_FLG_REV  = 0x40
};


/*****************************************************************************
  5 STRUCT
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(1)
#else
#pragma pack(push, 1)
#endif

/*****************************************************************************
 结构名    : IPV4_ADDR_UN
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV4地址
*****************************************************************************/
typedef union
{
    VOS_UINT8    aucIPAddr[4];
    VOS_UINT32   ulIpAddr;
} IPV4_ADDR_UN;

/*****************************************************************************
结构名    : IPV6_ADDR_UN
协议表格  :
ASN.1描述 :
结构说明  : IPV6地址
*****************************************************************************/
typedef union
{
    VOS_UINT8    aucIPAddr[16];
    VOS_UINT16   ausIpAddr[8];
    VOS_UINT32   aulIpAddr[4];
} IPV6_ADDR_UN;

/*****************************************************************************
 结构名    : IPV4_HDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV4固定头.按little-endian定义.
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucIpHdrLen:4;                 /* header length */
    VOS_UINT8    ucIpVer:4;                    /* version */

    VOS_UINT8    ucServiceType;                /* type of service */
    VOS_UINT16   usTotalLen;                   /* total length */
    VOS_UINT16   usIdentification;             /* identification */
    VOS_UINT16   usOffset;                     /* fragment offset field */

    VOS_UINT8    ucTTL;                        /* time to live*/
    VOS_UINT8    ucProtocol;                   /* protocol */
    VOS_UINT16   usCheckSum;                   /* checksum */
    IPV4_ADDR_UN unSrcAddr;                    /* source address */
    IPV4_ADDR_UN unDestAddr;                   /* dest address */
}IPV4_HDR_STRU;


/*****************************************************************************
 结构名    : IPV6_HDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV6固定头.按little-endian定义.
*****************************************************************************/
typedef struct
{
    VOS_UINT8     ucPriority :4;               /*priority*/
    VOS_UINT8     ucIpVersion:4;               /*ip version, to be 6*/
    VOS_UINT8     aucFlowLabel[3];             /*flow lable, low 20bit*/

    VOS_UINT16    usPayloadLen;                /*not include ipv6 fixed hdr len 40bytes*/
    VOS_UINT8     ucNextHdr;                   /*for l4 protocol or ext hdr*/
    VOS_UINT8     ucHopLimit;
    IPV6_ADDR_UN  unSrcAddr;
    IPV6_ADDR_UN  unDstAddr;

}IPV6_HDR_STRU;

/*****************************************************************************
 结构名    : IPV6_FRAGMENT_HDR
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV6分片头
*****************************************************************************/
typedef struct
{
    VOS_UINT8       ucNextHdr;
    VOS_UINT8       ucReserved;
    VOS_UINT16      usFragOffset;
    VOS_UINT32      ulIdentification;
}IPV6_FRAGMENT_HDR;


/*****************************************************************************
 结构名    : IPV6_OPTION_HDR
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV6 选项头.采用TLV形式.
*****************************************************************************/
typedef struct
{
    VOS_UINT8       ucNextHdr;
    VOS_UINT8       ucHdrLen;
}IPV6_OPTION_HDR;


/*****************************************************************************
 结构名    : TCP_HDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定义TCP固定头.按little-endian定义.
*****************************************************************************/
typedef struct
{
    VOS_UINT16    usSrcPort;
    VOS_UINT16    usDstPort;
    VOS_UINT32    ulSeqNum;
    VOS_UINT32    ulAck;
    VOS_UINT8     bitRec    : 4;
    VOS_UINT8     bitHdrLen : 4;
    VOS_UINT8     ucFlag;
    VOS_UINT16    usWinSize;
    VOS_UINT16    usCheckSum;
    VOS_UINT16    usUrgentOffset;
}TCP_HDR_STRU;

/*****************************************************************************
 结构名    : TCP_FAKE_HDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定义计算校验和时用到的TCP伪首部. 按little-endian定义.
*****************************************************************************/
typedef struct
{
    VOS_UINT8             aucRec0[8];                             /*全部为0不影响CRC计算，为了同IP头大小保持相同*/
    VOS_UINT32            ulSrcIP;                                /*源IP地址*/
    VOS_UINT32            ulDstIP;                                /*目的IP地址*/
    VOS_UINT8             ucAll0;                                 /*全部为0*/
    VOS_UINT8             ucProtocol;                             /*IP首部的协议字段*/
    VOS_UINT16            usLength;
}TCP_FAKE_HDR_STRU;

/*****************************************************************************
 结构名    : TCP_OPTION_ITEM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定义TCP头Option选项结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8             ucKind;
    VOS_UINT8             ucLen;
    VOS_UINT8             aucValue[126];
}TCP_OPTION_ITEM_STRU;


/*****************************************************************************
 结构名    : UDP_HDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定义UDP头.按little-endian定义.
*****************************************************************************/
typedef struct
{
    VOS_UINT16      usSrcPort;
    VOS_UINT16      usDstPort;
    VOS_UINT16      usLen;
    VOS_UINT16      usCheckSum;
}UDP_HDR_STRU;

/*****************************************************************************
 结构名    : ICMP_HDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定义ICMP头.按little-endian定义.
*****************************************************************************/
typedef struct
{
    VOS_UINT8       ucType;
    VOS_UINT8       ucCode;
    VOS_UINT16      usCheckSum;
}ICMP_HDR_STRU;

/*****************************************************************************
 结构名    : AH_HDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定义IPSec AH头.按little-endian定义.
*****************************************************************************/
typedef struct
{
    VOS_UINT8       ucNextHdr;
    VOS_UINT8       ucHdrLen;
    VOS_UINT16      usRes;

    VOS_UINT32      ulSPI;
    VOS_UINT32      ulSn;                   /* Sequence number */
    VOS_UINT8       auth_data[0];           /* Variable len but >=4. Mind the 64 bit alignment! */
}AH_HDR_STRU;


/*****************************************************************************
 结构名    : ESP_HDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定义IPSec ESP头.按little-endian定义.
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulSPI;
    VOS_UINT32      ulSn;                   /* Sequence number */
    VOS_UINT8       enc_data[0];            /* Variable len but >=8. Mind the 64 bit alignment! */
}ESP_HDR_STRU;



#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/



/*****************************************************************************
  9 OTHERS
*****************************************************************************/



#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TcpIpTypeDef.h */
