/*******************************************************************************
*
*
*                Copyright 2014, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              if_tunnel.h
*
*  Project Code: V3R2C20
*   Module Name:   
*  Date Created: 2014-11-12
*        Author: wuling201943
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-11-12   wuling201943            Create
*
*******************************************************************************/
#ifndef _TCPIP_IF_TUNNEL_H_
#define _TCPIP_IF_TUNNEL_H_
    
#ifdef  __cplusplus
    extern "C"{
#endif

#define IF_TUNNEL_BAK_ADD  0x1
#define IF_TUNNEL_BAK_DEL  0x2

#define IF_TUNNEL_COPY_ADDR(dst, src)\
{\
    dst[0] = src[0];\
    dst[1] = src[1];\
    dst[2] = src[2];\
    dst[3] = src[3];\
}

#define IF_TUNNEL_BAK_INFO_COPY(to,from)\
{\
    to->ulIpVer = from->ulIpVer;\
    to->ulProMode = from->ulProMode;\
    IF_TUNNEL_COPY_ADDR(to->ulDstIP, from->ulDstIP)\
    IF_TUNNEL_COPY_ADDR(to->ulSrcIP, from->ulSrcIP)\
    to->ulGreKey = from->ulGreKey;\
    to->ucNeedGreKey = from->ucNeedGreKey;\
}

typedef struct tagTCPIP_TUNNEL_IF_INFO
{
    ULONG  ulIpVer;        /* IP版本标识:TUNNEL_IP_VERSION_IPV4--IPv4;TUNNEL_IP_VERSION_IPV6--IPv6 */
    ULONG  ulProMode;      /* 隧道协议模式*/
    ULONG  ulDstIP[4];     /* 隧道的目的地址，主机序，V4地址ulDstIP[0]有效*/
    ULONG  ulSrcIP[4];     /* 隧道的源地址，主机序，V4地址ulSrcIP[0]有效*/
    ULONG  ulGreKey;       /* GRE Key，范围为0~0xFFFFFFFF*/
    UCHAR  ucNeedGreKey;   /* 标识用户是否配置了Gre key，1(VRP_YES)表示配置Gre Key， 0(VRP_NO)表示不配置Gre Key*/
    UCHAR  ucPad[3];
}TCPIP_TUNNEL_IF_INFO_S;

typedef struct tagTCPIP_TUNNEL_HA_TLV
{
    USHORT usTlvType;
    USHORT usTlvLen;
} TCPIP_TUNNEL_HA_TLV_S;

typedef struct tagTCPIP_TUNNEL_BAK_S
{
    ULONG  ulIfIndex;      /* tunnel接口索引*/
    ULONG  ulIpVer;        /* IP版本标识:0--IPv4;1--IPv6 */
    ULONG  ulProMode;      /* 隧道协议模式*/
    ULONG  ulDstIP[4];     /* 隧道的目的地址，主机序，V4地址ulDstIP[0]有效*/
    ULONG  ulSrcIP[4];     /* 隧道的源地址，主机序，V4地址ulSrcIP[0]有效*/
    ULONG  ulGreKey;       /* GRE Key*/
    UCHAR  ucNeedGreKey;   /* 标识用户是否配置了Gre key*/
    UCHAR  ucPad[3];
}TCPIP_TUNNEL_BAK_S;

#define IF_TUNNEL_TLV_HEADER_LEN (sizeof(TCPIP_TUNNEL_HA_TLV_S))
#define IF_TUNNEL_HA_BAK_TLV_LEN (sizeof(TCPIP_TUNNEL_HA_TLV_S) + sizeof(TCPIP_TUNNEL_BAK_S))

#define IF_TUNNEL_CONTINUE_WITH_END_PT(ulFlag)\
if (ulFlag)\
{\
    TCPIP_END_PT(g_ulSemForTightMods);\
    continue;\
}


#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif

