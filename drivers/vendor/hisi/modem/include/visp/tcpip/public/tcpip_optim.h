/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_optim.h
*
*  Project Code: VISP V1R6C02
*   Module Name: OPTIM
*  Date Created: 2008-04-17
*        Author: mafeng(59090)
*   Description: 性能优化处理宏定义与函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-17   mafeng(59090)           Create
*
*******************************************************************************/

#ifndef _TCPIP_OPTIM_H_
#define _TCPIP_OPTIM_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*struct id,供申请内存时使用*/
#define SID_PUBLIC_OPTIM_S 1


/* 缓存表索引长度(接收缓存表、发送缓存表) */
#define CACHE_HASHLEN 256

/* 定时器周期 10s */
#define OPTIM_TIMECYCLE 10000
#define OPTIM_DEF_ENTRYNUM 32

#define OPTIM_EN_STATUS 1
#define OPTIM_DIS_STATUS 0

#define OPTIM_DEBUG_ON 1
#define OPTIM_DEBUG_OFF 0

#define OPTIM_MBUF_OURRCV 0x0001

/* BFD报文的端口号 */
#define OPTIM_BFD_DPORT 3784
#define OPTIM_BFD_SPORT 4784

/* IKE的端口号 */
#define OPTIM_IKE_PACK_UDPPORT 500
#define OPTIM_IKE_NAT_PACK_UDPPORT 4500

/* TTL值,转发报文进行判断 */
#define OPTIM_IP_TTLDEC 1

/* DHCP CLIENT PORT */
#define OPTIM_DHCP4C_CLIENT_PORT 0x44

enum tagOPTProcRet
{
    OPTIM_GOTO_VISP = VOS_OK, /* 优化处理失败,返回VISP正常处理流程 */
    OPTIM_GOTO_END,           /* 报文被释放(钩子函数处理失败或VLAN处理失败),报文处理流程结束 */
    OPTIM_GOTO_OPTIM,         /* 报文优化处理成功,报文处理流程结束 */
};

#define CACHE_HASHMASK (CACHE_HASHLEN - 1)

/* 判断当前是否使能性能优化 */
#define OPTIM_IS_DISENABLE_STATUS (OPTIM_DIS_STATUS == g_ulOptimEnable)
#define OPTIM_IS_ENABLE_STATUS (OPTIM_EN_STATUS == g_ulOptimEnable)

/* 缓存表项数据结构 */
typedef struct tagOptimCache
{
    struct tagOptimCache *pstNextNode;
    
    /* 1, host receive, 2, forward, 3, host send */
    UCHAR ucCacheType; /* SEND/RECEIVE/FORWARD */

    /* 17:udp,6:tcp,0:rawip,17:iwf */
    UCHAR ucPktType;   /* UDP/TCP/RAWIP/IWF */
    UCHAR ucNPFlag;    /* NP flag */
    UCHAR ucTmFlag;    /* time 老化标志*/

    LONG  iFd;            /* visp rcv/send skt id  */
    ULONG ulOutIfIndex;   /* snd ifnet index */
    ULONG ulVLINKIndex;   /* vlink index */
    ULONG ulNextHop;      /* next hop,network seq */
    
    ULONG   ulDstIp;     /* dst ip,network seq    */
    ULONG   ulSrcIp;     /* src ip,network seq    */
    USHORT  usDstPort;   /* dst port,network seq  */
    USHORT  usSrcPort;   /* src port,network seq  */
    UCHAR   ucProtocol;  /* rip protocol          */
    UCHAR   ucPad;

    USHORT  usHeadLen;   /* 转发或发送时的报文头长度 */
    UCHAR pucPktHead[48];
}OPTIM_CACHE_S;

/* IP报文中五元组的信息network seq */
typedef struct tagOptimIpInfo
{
    ULONG ulSIP;    /* 源地址 */            
    ULONG ulDIP;    /* 目的地址 */ 
    USHORT usSP;    /* 源端口号 */            
    USHORT usDP;    /* 目的端口号 */            
    UCHAR ucPID;    /* 协议号 */
    UCHAR ucPadding[3];
}OPTIM_IPINFO_S;

/* 优化使能状态标志1:使能 0:去使能 */
extern ULONG g_ulOptimEnable;

/* 调试开关状态 */
extern ULONG g_ulOptimDebug;

/* 缓存表刷新定时器ID */
extern ULONG g_ulOptimTimerID;

/* 用户使能优化时指定的缓存表项数量 */
extern ULONG g_ulOptEntrySum;

/* 当前可用缓存表项的数量 */
extern ULONG g_ulOptEntryUsable;

/*性能优化表项老化定时器超时时间(供内部测试使用)*/
extern ULONG g_ulOptTimeOutValue;

extern TCPIP_OPTIMSTAT_S g_pstOptStatInfo;
extern OPTIM_CACHE_S *g_pstOptEntryHead;
extern OPTIM_CACHE_S *g_pstOptEntryUsable;

/* 发送缓存表 */
extern OPTIM_CACHE_S *g_pstOptSndEntry[CACHE_HASHLEN];

/* 接收缓存表 */
extern OPTIM_CACHE_S *g_pstOptRcvEntry[CACHE_HASHLEN];

extern OPTIM_INTERMEDIATE_HOOK_FUNC g_pfOptimIntermediateHook;

/*Added by qinyun62011, (Distribute socket)分布式socket裁剪，性能优化解耦合，与其他模块有调用关系的函数采用全局钩子的方式提供, 2014/3/7 */
typedef struct tagTCPIP_OPTIM_HOOK
{
    ULONG (*pfOPTIM_AllocEntryForIWF)(MBUF_S *pstMbuf, LONG nIpHLen);
    VOID (*pfOPTIM_AllocEntryForUDP)(IP_S *pstIP, LONG iFd);
    VOID (*pfOPTIM_DelEntryBySocket)(ULONG ulEntryType, LONG iFd);
    ULONG (*pfOPTIM_SndUDP)(MBUF_S *pstMbuf, MBUF_S *pMAddr, USHORT usSPort);
}TCPIP_OPTIM_HOOK_S;
extern TCPIP_OPTIM_HOOK_S g_stOptimHook;

/* 根据五元组信息HASH缓存表索引 */
#define OPTIM_HASHINDEX(ulSIP, usSP, ulDIP, usDP, ucPID, HashIndex) \
{\
    ULONG ulTemp = (ulSIP) ^ (usSP) ^ ((ulDIP)>>1)  ^((usDP)>>1)^(ucPID);\
    ulTemp ^= (ulTemp >> 20) ^ (ulTemp >> 12) ^ (ulTemp >> 7) ^ (ulTemp >> 4);\
    (HashIndex) = (ulTemp & CACHE_HASHMASK);\
}

/* 缓存表项插入到缓存表中 */
#define OPTIM_ENTRY_INSERT(g_pstCache, ulHashIndex, pstEntry) \
{\
    (pstEntry)->pstNextNode = (g_pstCache)[(ulHashIndex)];\
    (g_pstCache)[(ulHashIndex)] = (pstEntry);\
}

/* 更新ip头的ttl和校验和 */
/* Modified by y00176567, at 2011-05-26. 修改原因: 消除VC三级告警 */
/* ulCheck = (pstIp)->ip_usSum;更改为ulCheck = (ULONG)((pstIp)->ip_usSum);以保证类型一致 */
/* (pstIp)->ip_usSum = ulCheck + ((ulCheck >= 0xFFFF)?1:0)右边添加(USHORT)以保证类型一致 */
#define OPTIM_FAST_CKSUM(pstIp)\
{\
    ULONG ulCheck;\
    ulCheck = (ULONG)((pstIp)->ip_usSum);\
    ulCheck += VOS_HTONS(0x0100);\
    (pstIp)->ip_usSum = (USHORT)(ulCheck + ((ulCheck >= 0xFFFF)?1:0));\
    --(pstIp)->ip_chTTL;\
}

/* 根据五元组信息匹配缓存表项(参数为OPTIM_CACHE_S与OPTIM_IPINFO_S类型指针) */
#define OPTIM_PKT_MATCH_CACHE_RCV(pstEntry, pstIpInfo, ulRet)\
{\
    if (((pstEntry)->ulSrcIp==(pstIpInfo)->ulSIP)&&((pstEntry)->ulDstIp==(pstIpInfo)->ulDIP)\
        &&((pstEntry)->usSrcPort==(pstIpInfo)->usSP)&&((pstEntry)->usDstPort==(pstIpInfo)->usDP)\
        &&((pstEntry)->ucProtocol==(pstIpInfo)->ucPID))\
    {\
        (ulRet) = VOS_OK;\
    }\
}

/* 根据五元组信息匹配缓存表项(参数为OPTIM_CACHE_S与OPTIM_IPINFO_S类型指针) */
#define OPTIM_PKT_MATCH_CACHE_SND(pstEntry, pstIpInfo, ulRet)\
{\
    if (((pstEntry)->ulDstIp==(pstIpInfo)->ulDIP)\
        &&((pstEntry)->usSrcPort==(pstIpInfo)->usSP)&&((pstEntry)->usDstPort==(pstIpInfo)->usDP)\
        &&((pstEntry)->ucProtocol==(pstIpInfo)->ucPID))\
    {\
        (ulRet) = VOS_OK;\
    }\
}


/* 根据mbuf信息更新缓存表项(OPTIM_CACHE_S与MBUF_IP_PACKET_INFO_S数据结构) */
#define OPTIM_MtoE(pstEntry, pstMInfo)\
{\
    (pstEntry)->ulSrcIp    = (pstMInfo)->ulSourceIpAddress;\
    (pstEntry)->usSrcPort  = (pstMInfo)->usSourcePortOrIcmpType;\
    (pstEntry)->ulDstIp    = (pstMInfo)->ulDestinationIpAddress;\
    (pstEntry)->usDstPort  = (pstMInfo)->usDestinationPortOrIcmpCode;\
    (pstEntry)->ucProtocol = (pstMInfo)->ucProtocolId;\
    (pstEntry)->ulNextHop  = (pstMInfo)->ulNextHopIpAddress;\
}

/* 根据mbuf信息更新五元组信息(OPTIM_IPINFO_S与MBUF_IP_PACKET_INFO_S数据结构) */
#define OPTIM_MtoO(pstOptIp, pstMInfo)\
{\
    (pstOptIp)->ulSIP = (pstMInfo)->ulSourceIpAddress;\
    (pstOptIp)->usSP  = (pstMInfo)->usSourcePortOrIcmpType;\
    (pstOptIp)->ulDIP = (pstMInfo)->ulDestinationIpAddress;\
    (pstOptIp)->usDP  = (pstMInfo)->usDestinationPortOrIcmpCode;\
    (pstOptIp)->ucPID = (pstMInfo)->ucProtocolId;\
}

/* 根据Entry信息更新五元组信息(OPTIM_IPINFO_S与OPTIM_CACHE_S数据结构) */
#define OPTIM_EtoO(pstOptIp, pstEntry)\
{\
    (pstOptIp)->ulSIP = (pstEntry)->ulSrcIp;\
    (pstOptIp)->usSP  = (pstEntry)->usSrcPort;\
    (pstOptIp)->ulDIP = (pstEntry)->ulDstIp;\
    (pstOptIp)->usDP  = (pstEntry)->usDstPort;\
    (pstOptIp)->ucPID = (pstEntry)->ucProtocol;\
}


/* 根据报文入接口类型更新优化统计信息 */
#define OPTIM_UPDATESTAT_BY_INIFTYPE(ulInIfType, g_stOptStatInfo)\
{\
    if ((PORT_ETHERNET == (ulInIfType))||(PORT_ETH_TRUNK == (ulInIfType)))\
    {\
        (g_stOptStatInfo).ulEthRcv++;\
    }\
    else\
    {\
        (g_stOptStatInfo).ulNoEthRcv++;\
    }\
}

/* 根据报文出接口类型更新优化统计信息 */
#define OPTIM_UPDATESTAT_BY_OUTIFTYPE(ulOutIfType, g_stOptStatInfo)\
{\
    if ((PORT_ETHERNET == (ulOutIfType))||(PORT_ETH_TRUNK == (ulOutIfType)))\
    {\
        (g_stOptStatInfo).ulEthSnd++;\
    }\
    else\
    {\
        (g_stOptStatInfo).ulNoEthSnd++;\
    }\
}

/* 根据报文协议类型更新优化统计信息 */
#define OPTIM_UPDATESTAT_BY_SNDPKTTYPE(ucPktType, g_stOptStatInfo)\
{\
    if (IPPROTO_UDP == (ucPktType))\
    {\
        (g_stOptStatInfo).ulIWFSnd++;\
    }\
    else\
    {\
        if (IPPROTO_TCP == (ucPktType))\
        {\
            (g_stOptStatInfo).ulTcpSnd++;\
        }\
        else\
        {\
            (g_stOptStatInfo).ulRipSnd++;\
        }\
    }\
}

/* 封装调试信息删除函数 */
#define OPTIM_DEBUG_OUTPUT(str)\
{\
    (VOID)TCPIP_IC_SendMsg(0, 0, str);\
}


extern VOID  OPTIM_AllocEntryForETH(MBUF_S *pstMbuf, IFNET_S *pstIfnet);
extern VOID  OPTIM_AllocEntryForIP(MBUF_S *pstMbuf, IFNET_S *pstIfnet);
extern ULONG OPTIM_AllocEntryForIWF(MBUF_S *pstMbuf, LONG nIpHLen);
extern ULONG OPTIM_AllocEntryForPPI(MBUF_S *pstMbuf, IFNET_S *pstIfnet);
extern VOID  OPTIM_AllocEntryForNoUDP(IP_S *pstIP);
extern VOID  OPTIM_AllocEntryForUDP(IP_S *pstIP, LONG iFd);

extern ULONG OPTIM_CreateEntry(ULONG ulSum);
extern VOID  OPTIM_DelAllEntry(VOID);
extern ULONG OPTIM_ETHUpdateEntry(OPTIM_CACHE_S **ppstEntry, ULONG ulIfIndex);
extern VOID  OPTIM_DelEntryByEth(ULONG ulIfIndex);
extern ULONG OPTIM_SocketUpdateEntry(OPTIM_CACHE_S **ppstEntry, LONG iFd);
extern VOID  OPTIM_DelEntryBySocket(ULONG ulEntryType, LONG iFd);
extern VOID  OPTIM_DestroyEntry(VOID);

extern OPTIM_CACHE_S *OPTIM_MallocEntry(VOID);
extern OPTIM_CACHE_S *OPTIM_Rcv_MatchEntry(ULONG ulIndex, OPTIM_IPINFO_S *pstOptInfo);
extern OPTIM_CACHE_S *OPTIM_Snd_MatchEntry(ULONG ulIndex, OPTIM_IPINFO_S *pstOptInfo);


extern VOID  OPTIM_GetIPInfo(IP_S *pstIp, OPTIM_IPINFO_S *pstOptInfo);
extern ULONG OPTIM_GetRTMODE(VOID);
extern ULONG OPTIM_GetSKMODE(VOID);
extern ULONG OPTIM_PreP_IP(MBUF_S *pstMbuf);
extern ULONG OPTIM_PreP_ETH(MBUF_S *pstMbuf);
extern ULONG OPTIM_Rcv(MBUF_S *pstMbuf, IFNET_S *pstIfnet);
extern VOID  OPTIM_FreeEntry(OPTIM_CACHE_S * pstEntry);
extern ULONG OPTIM_SndIP(MBUF_S *pstMbuf, LONG lHLen);
extern ULONG OPTIM_SndUDP(MBUF_S *pstMbuf, MBUF_S *pMAddr, USHORT usSPort);
extern VOID  OPTIM_TimerUpdateEntry(OPTIM_CACHE_S **ppstEntry);
extern VOID  OPTIM_Timer(VOID *pTemp);
extern LONG OPTIM_EntryDbgInfo(OPTIM_CACHE_S *pstEntry, CHAR *pszDbgInfo, LONG lBufLen, LONG nLen);

extern ULONG OPTIM_DoNothing(MBUF_S *pstMbuf);
extern ULONG TCPIP_AddVlanHead(MBUF_S *pMBuf, ULONG ulVlanHead);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* end of _TCPIP_OPTIM_H_ */

