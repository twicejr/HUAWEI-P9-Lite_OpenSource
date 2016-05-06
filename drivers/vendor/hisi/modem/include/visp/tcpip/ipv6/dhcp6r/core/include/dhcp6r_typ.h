/*******************************************************************************
*
*
*                Copyright 2011, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp6r_typ.h
*
*  Project Code: VISP V2R3C06
*   Module Name: DHCP6R  
*  Date Created: 2011-7-15
*        Author: PBQ(RT24429)
*   Description: DHCP6R模块的数据结构定义
*
*-------------------------------------------------------------------------------
*  Modification  History
*  DATE          NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2011-7-27     PBQ(RT24429)     Create the first version.
*
*******************************************************************************/

#ifndef _DHCP6R_TYP_H_
#define _DHCP6R_TYP_H_

#ifdef __cplusplus
    extern "C"{
#endif  /* end of __cplusplus */

/* IPv6 socket通用结构 */
typedef struct tagSockaddr_Storage
{
    UCHAR               ss_ucLen;
    UCHAR               ss_ucFamily;
    UCHAR               aucFill[126];
}SOCKADDR_STORAGE_S;

/* relay使能配置控制块 */
typedef struct tagDHCP6RCfgNode
{
    DLL_NODE_S          stDLLNode;
    ULONG               ulIfIndex;       /* 配置接口索引,如果为全局配置，则index为0 */
    ULONG               ulEnableStatus;  /* 使能状态 0-未使能 1-使能 */
    ULONG               ulServerNum;     /* 接口上server地址数目 */       
    DHCP6R_SERVERNODE_S astServer[DHCP6R_SERVERLIST_MAX_NUM]; /* server地址结构数组 */
}DHCP6R_CFG_NODE_S;

/*全局控制块*/
typedef struct tagDHCP6RCfgHead
{
    DLL_S               stCfgList;       /* 接口配置链表 */
    ULONG               ulEnableCount;   /* 使能计数 */
    UCHAR               ucCfgMode;       /* Relay使能模式，全局模式(1),接口模式(0) */
    UCHAR               ucFwdMode;       /* 中继方式,初始值0-分担方式，1-广播方式 */
    USHORT              usMaxHops;       /* 最大RELAY跳数,默认值为32 */
    DHCP6R_STATINFO_S   stStatistics;    /* 统计信息 */ 
}DHCP6R_CFG_HEAD_S;

typedef struct tagDHCP6RDbgEntry
{
    DLL_S               stDebugList;     /* Debug开关链表 */
    ULONG               ulGlobalDebug;   /* 全局调试开关 */ 
    USHORT              usDbgPktLen;     /* 报文调试信息输出长度 */ 
}DHCP6R_DBG_S;

/* 接口调试开关控制块 */
typedef struct tagDHCP6RDebug
{
    DLL_NODE_S          stDLLNode;
    ULONG               ulIfIndex;    
    ULONG               ulDebug;
}DHCP6R_DEBUG_NODE_S; 

/* 报文源(目的)地址和出(入)接口索引 */
typedef struct in6_pktinfo
{
    IN6ADDR_S           stIp6Addr;       /* src/dst IPv6 address */
    ULONG               ulIfIndex;       /* send/recv interface index */
}IN6_PKTINFO_S;

#pragma pack(1)
/* DHCPv6 relay报文头 */
typedef struct tgDHCP6R_HEADER
{
    UCHAR               ucMsgType;
    UCHAR               ucHopCnt;
    IN6ADDR_S           stLinkAddr;
    IN6ADDR_S           stPeerAddr;
}DHCP6R_HEADER_S;

/* Begin: Add by pengbinquan for 2011080012, 华为检视意见调试信息打印详细报文 */
/* Relay-Forward和Relay-Reply类型之外的其他报文头公共部分 */
typedef struct tagPublicHeader
{
    ULONG               ulMsgType  :8;   /* 报文前8位为报文类型 */
    ULONG               ulTranID   :24;  /* 报文后24位为TranID */
}DHCP6R_PUBLIC_HEADER_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/* 通用选项结构 */
typedef struct tagDHCP6ROptBuf
{
    USHORT              usOptCode;
    USHORT              usOptLen;
    CHAR               *pOptData;
}DHCP6R_OPTBUF_S;

/* InterfaceID选项结构 */
typedef struct tagDHCP6RInterfaceID
{
    USHORT              usOptCode;
    USHORT              usOptLen;
#pragma pack(1)
    struct packed_data
    {
        UCHAR           ucInterfaceType; /* 接口类型 */
        UCHAR           ucReserved;
        USHORT          usInterfaceNum;  /* 接口编号 */
    }OptData;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

}DHCP6R_INTERFACEID_S;

/* Relay 报文选项结构 */
typedef struct tagDHCP6ROptInfo
{
    DHCP6R_OPTBUF_S     stRelayMsgOpt;   /* 中继报文选项 */
    DHCP6R_OPTBUF_S     stIfIdOpt;       /* 接口ID选项 */
}DHCP6R_OPTINFO_S; 

/* Shell向Core注册的回调函数集 */
typedef struct tagDHCP6RShellCallbackSet
{
    ULONG (*pfDHCP6R_DebugOutString)(CHAR * szStr); /* 调试信息输出函数 */
}DHCP6R_SHELL_CALLBACK_SET_S;

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _DHCP6R_TYP_H_ */

