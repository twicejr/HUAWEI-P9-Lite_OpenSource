/*******************************************************************************
*
*
*                Copyright 2011, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp6r_def.h
*
*  Project Code: VISP V2R3C06
*   Module Name: DHCP6R  
*  Date Created: 2011-7-19
*        Author: PBQ(RT24429)
*   Description: DHCP6R模块的宏和枚举定义
*
*-------------------------------------------------------------------------------
*  Modification  History
*  DATE          NAME                DESCRIPTION    
*-------------------------------------------------------------------------------
*  2011-7-19     PBQ(RT24429)        Create the first version.
*
*******************************************************************************/

#ifndef _DHCP6R_DEF_H_
#define _DHCP6R_DEF_H_

#ifdef __cplusplus
    extern "C"{
#endif  /* end of __cplusplus */

/* 使能配置模式: 0 - 接口模式，1 - 全局模式 */
#define DHCP6R_ENABLE_INTERFACE     0
#define DHCP6R_ENABLE_GLOBAL        1

/* 接口检查类型 */
#define DHCP6R_CHECKTYPE_INIF       0   /* 0 使能接口检查,支持接口类型有eth/ppp/mp*/
#define DHCP6R_CHECKTYPE_OUTIF      1   /* 1 出接口检查,支持接口类型有eth/ppp/mp/trunk/vlanif*/

/* Relay6监听端口号 */
#define DHCP6R_LISTEN_PORT          547
/* Relay6目的端口号 */
#define DHCP6R_SERVER_PORT          547
#define DHCP6R_CLIENT_PORT          546

/* 地址宏定义 */
#define IN6ADDR_UNSPECIFIED         "::"
#define IN6ADDR_All_AGENTS_SERVERS  "ff02::1:2"

/* 最大中继跳数限制 */
#define DHCP6R_HOPS_MAX             255

/* 多播目的地址中继hop limit */
#define DHCP6R_IPV6MULTI_HOPLIMIT   32

/*接口名的最大长度*/
#define IFNAME_MAX_LEN              128

/* 最大接口数 */
#define DHCP6R_INDEX_MAX            9999

/* ipv6地址的长度 */
#define IPV6_ADDR_LEN               16

/* 存储ipv6地址字符串的最大长度 */
#define DHCP6R_IPV6_ADDR_STR_MAX_LEN       46

/* Relay forward 报文头部的长度 */
#define RELAY_FORWARD_HEAD_LEN      34
 
 /* 选项头部的长度 */
#define OPT_HEAD_LEN                4

#define DHCP6R_HEAD_MIN_LEN         4

#define DHCP6C_HEAD_LEN             4

#define DHCP6R_INTERFACEID_LEN      4

/* 选项头部的两个字段的长度 即type 和 len字段 */
#define OPT_HEADFIELD_LEN           2

/* 接口索引的长度 */
#define IFINDEX_LEN                 4

/* 公共配置信息(使能配置模式，最大hops,中继方式)的默认值 */
#define DHCP6R_ENABLE_DEFAULT       DHCP6R_ENABLE_INTERFACE
#define DHCP6R_HOPS_DEFAULT         32
#define DHCP6R_FORWORD_DEFAULT      DHCP6R_FORWORD_CYCLE

/* relay接收发送报文缓冲区长度 */
#define DHCP6R_UDPBUF_MAXLEN        16384

/* 打印DHCP报文长度 */
#define DHCP6R_PRINT_LEN_MIN        34
#define DHCP6R_PRINT_LEN_DEFAULT    128
#define DHCP6R_PRINT_LEN_MAX        16384

#define DHCP6R_DBG_CHK_PAKCET       0x1     /* 简略报文调试开关检查值 */
#define DHCP6R_DBG_CHK_ERROR        0x2     /* 错误调试开关检查值 */
#define DHCP6R_DBG_CHK_DETAIL       0x4     /* 详细报文调试开关检查值 */

#define DHCP6R_FLAG_SET             0x1     /* 设置标识 */
#define DHCP6R_FLAG_UNSET           0x0     /* 不设置标识 */

/* DHCP6R模块事件位 */
/* 配置消息使用同一个配置消息队列和相同事件，但通过不同的消息类型来区分  */
#define DHCP6R_EV_CNTRL             0x1     /* 其他模块通知DHCP6R事件   */

#define DHCP6R_MSG_CRTSKT           0x2     /* 创建relay socket消息     */

/* 无效的索引值 */
#define DHCP6R_INVALID_INDEX        0xffffffff

/**********************************************************\ 
 * 用户配置接口中传入的接口索引值在当前配置模式下是否有效 *
 * 接口配置模式(0),接口索引必须 非0                       *
 * 全局配置模式(1),接口索引必须 为0                       *
 * 宏值为1表示传入索引与配置模式冲突                      *
\**********************************************************/
#define DHCP6R_MODE_NO_MATCH(ulMode, ulIfIndex) (((!(ulMode))&&(!(ulIfIndex))) || ((ulMode)&&(ulIfIndex)))

/************************************************************************
                  DHCP6R ADDR module defination
                  
 以下地址类型判断宏使用说明:
 pAddress必须是一个IPv6地址结构指针，且其结构中的数组元素是4字节，ULONG类型
 返回值: 
      1 -- pAddress 地址类型与宏名相同
      0 -- pAddress 地址类型与宏名不同
*************************************************************************/
/* 判断地址是否为"::" */
#define DHCP6R_IS_ADDR_UNSPECIFIED( pAddress ) \
        ((0 == ((pAddress)->s6_addr32[0])) \
         && (0 == ((pAddress)->s6_addr32[1])) \
         && (0 == ((pAddress)->s6_addr32[2])) \
         && (0 == ((pAddress)->s6_addr32[3])))
            
/* 判断地址是否相同的宏 */
#define DHCP6R_ARE_ADDR_EQUAL(pDstAddr,pSrcAddr) \
        (((pDstAddr)->s6_addr32[0] == (pSrcAddr)->s6_addr32[0]) \
         && ((pDstAddr)->s6_addr32[1] == (pSrcAddr)->s6_addr32[1]) \
         && ((pDstAddr)->s6_addr32[2] == (pSrcAddr)->s6_addr32[2]) \
         && ((pDstAddr)->s6_addr32[3] == (pSrcAddr)->s6_addr32[3]))

/* 环回地址判断宏 */
#define DHCP6R_IS_ADDR_LOOPBACK( pAddress ) \
        ((0 == ((pAddress)->s6_addr32[0])) \
         && (0 == ((pAddress)->s6_addr32[1])) \
         && (0 == ((pAddress)->s6_addr32[2])) \
         && (1 == ((pAddress)->s6_addr32[3])))

/* 链路本地地址判断宏 */
#define DHCP6R_IS_ADDR_LINKLOCAL( pAddress ) \
        (0xFE800000 == (0xFFC00000&((pAddress)->s6_addr32[0])))

/* 站点本地地址判断宏 */
#define DHCP6R_IS_ADDR_SITELOCAL( pAddress ) \
        (0xFEC00000 == (0xFFC00000&((pAddress)->s6_addr32[0])))

/* 组播地址判断宏 */
#define DHCP6R_IS_ADDR_MULTICAST( pAddress ) \
        (0xFF000000 == (0xFF000000&((pAddress)->s6_addr32[0])))
        
#define DHCP6R_IS_ADDR_LINKLOCAL_MULTICAST( pAddress )    \
        (0xFF020000 == (0xFFFF0000&((pAddress)->s6_addr32[0])))

/* All_DHCP_Relay_Agents_and_Servers地址判断宏 */
#define DHCP6R_IS_ADDR_ALL_DHCP_RELAYS( pAddress ) \
        ((0xFF020000 == ((pAddress)->s6_addr32[0])) \
         && (0 == ((pAddress)->s6_addr32[1])) \
         && (0 == ((pAddress)->s6_addr32[2])) \
         && (0x00010002 == ((pAddress)->s6_addr32[3])))

/* All_DHCP_Servers地址判断宏 */
#define DHCP6R_IS_ADDR_ALL_DHCP_SERVERS( pAddress ) \
        ((0xFF050000 == ((pAddress)->s6_addr32[0])) \
         && (0 == ((pAddress)->s6_addr32[1])) \
         && (0 == ((pAddress)->s6_addr32[2])) \
         && (0x00010003 == ((pAddress)->s6_addr32[3])))

/* 全球单播地址判断宏 */
/* Modified by w00207740, DTS2013121700565 ,sitelocal地址属于global地址, 2013/12/17 */
#define DHCP6R_IS_ADDR_GLOBAL( pAddress ) \
        (!((DHCP6R_IS_ADDR_MULTICAST(pAddress)) \
            ||(DHCP6R_IS_ADDR_LOOPBACK(pAddress)) \
            ||(DHCP6R_IS_ADDR_LINKLOCAL(pAddress)) \
            ||(DHCP6R_IS_ADDR_UNSPECIFIED(pAddress))))

/* IPV6地址拷贝宏 */
#define DHCP6R_IPV6_ADDRESS_COPY( pDest, pSrc ) \
{\
    (pDest)->s6_addr32[0] = (pSrc)->s6_addr32[0];\
    (pDest)->s6_addr32[1] = (pSrc)->s6_addr32[1];\
    (pDest)->s6_addr32[2] = (pSrc)->s6_addr32[2];\
    (pDest)->s6_addr32[3] = (pSrc)->s6_addr32[3];\
}

/* IPv6地址字节序转换宏 */
#define DHCP6R_ADDRESS_NTOH(pAddress) \
{\
    (pAddress)->s6_addr32[0] = VOS_NTOHL((pAddress)->s6_addr32[0]);\
    (pAddress)->s6_addr32[1] = VOS_NTOHL((pAddress)->s6_addr32[1]);\
    (pAddress)->s6_addr32[2] = VOS_NTOHL((pAddress)->s6_addr32[2]);\
    (pAddress)->s6_addr32[3] = VOS_NTOHL((pAddress)->s6_addr32[3]);\
}
     
/* IPv6地址字节序转换宏 */
#define DHCP6R_ADDRESS_HTON(pAddress) \
{\
    (pAddress)->s6_addr32[0] = VOS_HTONL((pAddress)->s6_addr32[0]);\
    (pAddress)->s6_addr32[1] = VOS_HTONL((pAddress)->s6_addr32[1]);\
    (pAddress)->s6_addr32[2] = VOS_HTONL((pAddress)->s6_addr32[2]);\
    (pAddress)->s6_addr32[3] = VOS_HTONL((pAddress)->s6_addr32[3]);\
}

/*************************************************************************
                END DHCP6R ADDR module defination
*************************************************************************/

/* DHCPv6数据报文类型 */
enum enDHCP6R_MsgType
{
    DHCP6R_MSG_SOLICIT = 1,             /* 1  Solicit */
    DHCP6R_MSG_ADVERTISE,               /* 2  Advertise */
    DHCP6R_MSG_REQUEST,                 /* 3  Request */
    DHCP6R_MSG_CONFIRM,                 /* 4  Confirm */
    DHCP6R_MSG_RENEW,                   /* 5  Renew */
    DHCP6R_MSG_REBIND,                  /* 6  Rebind */
    DHCP6R_MSG_REPLY,                   /* 7  Reply */
    DHCP6R_MSG_RELEASE,                 /* 8  Release */
    DHCP6R_MSG_DECLINE,                 /* 9  Decline */
    DHCP6R_MSG_RECONFIGURE,             /* 10 Reconfigure */
    DHCP6R_MSG_INFORMATION_REQUEST,     /* 11 Information-Request */
    DHCP6R_MSG_RELAY_FORW,              /* 12 Relay-Forward */
    DHCP6R_MSG_RELAY_REPL,              /* 13 Relay-Reply */
    DHCP6R_MSG_MAX,
};

/* 定义非法dhcp消息类型宏 */
#define DHCP6R_BAD_MSG    0

/* 选项的类型*/
enum enDHCP6R_OPTTYPE
{
    DHCP6C_DUID               = 1,      /* DUID */
    DHCP6R_RELAY_MESSAGE      = 9,      /* Relay message */
    DHCP6R_INTERFACEID        = 18,     /* interfaceID */
};

/* 定义dhcp报文流方向 */
enum enDHCP6RTxRx
{
    DHCP6R_FROM_CLIENT        = 0,      /* 0 从client接收 */
    DHCP6R_TO_CLIENT,                   /* 1 向client发送 */
    DHCP6R_FROM_SERVER,                 /* 2 从server接收 */
    DHCP6R_TO_SERVER,                   /* 3 向server发送 */
    DHCP6R_TXRX_UNKNOWN,                /* 4 报文方向未知 */
};

/* DHCP6R模块使用的SID统一在此定义 */
#define SID_COMP_DHCP6R_DLL_S   1       /* DLL_S */
#define SID_COMP_DHCP6R_CFG_S   2       /* DHCP6R_CFG_NODE_S */
#define SID_COMP_DHCP6R_DBG_S   3       /* DHCP6R_DEBUG_NODE_S */

/* 调试错误信息打印文件名和出错行数宏定义 */
#define DHCP6R_DEBUGERROR(szErrInfo) \
{ \
    CHAR  szCurrentFileName[FILENAME_LEN] = {0}; \
    TCPIP_GetFileName(__FILE__, szCurrentFileName, FILENAME_LEN); \
    (VOID)DHCP6R_DebugErrorCheck(szCurrentFileName, __LINE__, szErrInfo); \
}

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif    /* end of _DHCP6R_DEF_H_ */

