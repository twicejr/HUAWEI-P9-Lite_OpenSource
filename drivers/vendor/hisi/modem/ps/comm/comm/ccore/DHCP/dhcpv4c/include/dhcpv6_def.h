/*************************************************************************************
*
*                       dhcpv6_def.h
*
*  项目代码：           UGW9811 V900R010C00
*  创建日期：           2012-07-10
*  作者：               Y00170683
*  修改历史列表：
*  参考文档：
*  功能：               DHCPV6相关宏定义(client-server共用)
*  其他：
*
*-----------------------------------------------------------------------------------
*
*  Copyright  Beijing Institute HuaWei Tech, Inc.
*                     ALL RIGHTS RESERVED
*
*************************************************************************************/
#ifndef __DHCPV6_DEF_H__

#define __DHCPV6_DEF_H__


/*******************************************************************************************************/
/********************                          宏定义                           ************************/
/*******************************************************************************************************/

/*  DHCP 的多播地址

      All_DHCP_Relay_Agents_and_Servers address:   FF02::1:2
      All_DHCP_Servers address:                    FF05::1:3

     Clients listen for DHCP messages on UDP port 546.
     Servers and relay agents listen for DHCP messages on UDP port 547.

*/


/* ipv6地址字节序转换 */
#define DHCPV6_NTOHL_IPV6_ADDR(stIpv6Addr)\
{\
    (stIpv6Addr).s6_addr32[0] = VOS_NTOHL((stIpv6Addr).s6_addr32[0]);\
    (stIpv6Addr).s6_addr32[1] = VOS_NTOHL((stIpv6Addr).s6_addr32[1]);\
    (stIpv6Addr).s6_addr32[2] = VOS_NTOHL((stIpv6Addr).s6_addr32[2]);\
    (stIpv6Addr).s6_addr32[3] = VOS_NTOHL((stIpv6Addr).s6_addr32[3]);\
}

#define DHCPV6_HTONL_IPV6_ADDR(stIpv6Addr)\
{\
    (stIpv6Addr).s6_addr32[0] = VOS_HTONL((stIpv6Addr).s6_addr32[0]);\
    (stIpv6Addr).s6_addr32[1] = VOS_HTONL((stIpv6Addr).s6_addr32[1]);\
    (stIpv6Addr).s6_addr32[2] = VOS_HTONL((stIpv6Addr).s6_addr32[2]);\
    (stIpv6Addr).s6_addr32[3] = VOS_HTONL((stIpv6Addr).s6_addr32[3]);\
}


#define    UDPV6_HEADER_LEN                                    8
#define    DHCPV6_HEADER_LEN                                  4
#define    DHCPV6_OPT_HEADER_LEN                          4
#define    DHCPV6_CLIENT_UDP_PORT                        546
#define    DHCPV6_SERVER_UDP_PORT                        547
#define    DHCPV6_RELAY_UDP_PORT             DHCPV6_SERVER_UDP_PORT

/* DHCPv6 消息类型 */
#define     DHCPV6_MSG_TYPE_SOLICIT               1
#define     DHCPV6_MSG_TYPE_ADVERTISE             2
#define     DHCPV6_MSG_TYPE_REQUEST               3
#define     DHCPV6_MSG_TYPE_CONFIRM               4
#define     DHCPV6_MSG_TYPE_RENEW                 5
#define     DHCPV6_MSG_TYPE_REBIND                6
#define     DHCPV6_MSG_TYPE_REPLY                 7
#define     DHCPV6_MSG_TYPE_RELEASE               8
#define     DHCPV6_MSG_TYPE_DECLINE               9
#define     DHCPV6_MSG_TYPE_RECONFIGURE           10
#define     DHCPV6_MSG_TYPE_INFORMATION_REQUEST   11
#define     DHCPV6_MSG_TYPE_RELAY_FORW            12
#define     DHCPV6_MSG_TYPE_RELAY_REPL            13

/* DHCPv6 选项类型 */
#define    DHCPV6_MSG_OPTION_CLIENTID       1
#define    DHCPV6_MSG_OPTION_SERVERID       2
#define    DHCPV6_MSG_OPTION_IA_NA          3
#define    DHCPV6_MSG_OPTION_IA_TA          4
#define    DHCPV6_MSG_OPTION_IAADDR         5
#define    DHCPV6_MSG_OPTION_ORO            6
#define    DHCPV6_MSG_OPTION_PREFERENCE     7
#define    DHCPV6_MSG_OPTION_ELAPSED_TIME   8
#define    DHCPV6_MSG_OPTION_RELAY_MSG      9
#define    DHCPV6_MSG_OPTION_AUTH           11
#define    DHCPV6_MSG_OPTION_UNICAST        12
#define    DHCPV6_MSG_OPTION_STATUS_CODE    13
#define    DHCPV6_MSG_OPTION_RAPID_COMMIT   14
#define    DHCPV6_MSG_OPTION_USER_CLASS     15
#define    DHCPV6_MSG_OPTION_VENDOR_CLASS   16
#define    DHCPV6_MSG_OPTION_VENDOR_OPTS    17
#define    DHCPV6_MSG_OPTION_INTERFACE_ID   18
#define    DHCPV6_MSG_OPTION_RECONF_MSG     19
#define    DHCPV6_MSG_OPTION_RECONF_ACCEPT  20
#define    DHCPV6_MSG_OPTION_DNS_SERVERS   23    /* defined in RFC3646 */
#define    DHCPV6_MSG_OPTION_DOMAIN_LIST   24    /* defined in RFC3646 */
#define    DHCPV6_MSG_OPTION_IAPD   25         /* defined in RFC3633 */
#define    DHCPV6_MSG_OPTION_IAPREFIX   26    /* defined in RFC3633 */
#define    DHCPV6_MSG_OPTION_PDEXCLUDE  67    /* defined in RFC6603 */

/* DHCPv6 DUID类型 */
#define    DHCPV6_MSG_OPTION_DUID_LLT  1
#define    DHCPV6_MSG_OPTION_DUID_EN  2
#define    DHCPV6_MSG_OPTION_DUID_LL  3

/* DHCPv6 消息方向 接收或者发送*/
#define    DHCPV6_MSG_DIRECTION_SEND            1
#define    DHCPV6_MSG_DIRECTION_RECEIVE       2


/* DHCPv6 华为的企业码 */
#define    DHCPV6_HUAWEI_ENTERPRISENUM  2011

#define  DHCPV6S_SERVERID_TIME  "\00\56\21\92"
#define  DHCPV6S_SERVERID_LINK  "\00\24\130\95\155\26"


/***************************************************************/
/**************         DHCPV6 消息结构体         ***************/
/***************************************************************/

/* 消息码枚举值 */
typedef enum tagDHCPV6C_STATUS_CODE_E
{
    DHCPV6C_STATUS_CODE_SUCCESS = 0,     /* 成功 */
    DHCPV6C_STATUS_CODE_UNSPECFAIL,      /* 未知错误，激活失败 */
    DHCPV6C_STATUS_CODE_NOADDRESS,       /* 没有可用地址，激活失败 */
    DHCPV6C_STATUS_CODE_NOBIND,          /* 服务器上保存的客户端信息和Renew消息中的不一致，忽略该消息码 */
    DHCPV6C_STATUS_CODE_NOONLINK,        /* 前缀地址不适合链路，忽略该消息码 */
    DHCPV6C_STATUS_CODE_USEMULTICAST,    /* 服务器发给客户端，强制客户端使用All_DHCP_Relay_Agents_and_Servers地址，激活失败 */
    DHCPV6C_STATUS_CODE_NOPREFIX,         /* 没有可用前缀 rfc3633 */

    DHCPV6C_STATUS_CODE_BUTT
} DHCPV6C_STATUS_CODE_E;


#endif /* end of __DHCPV6_PROC_H__ */
