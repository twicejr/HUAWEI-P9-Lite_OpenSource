
#ifndef __PP4_API_H__
#define __PP4_API_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/* address family  */
#ifndef AF_INET
#define AF_INET         2               /* internetwork: UDP, TCP, etc. */
#endif


/* protocol number */
#ifndef IPPROTO_MAX
#define IPPROTO_MAX     256
#endif

#ifndef IPPROTO_RAW
#define IPPROTO_RAW     255     /* raw IP packet */
#endif

#ifndef IPPROTO_IP
#define IPPROTO_IP      0       /* 虚拟IP  dummy for IP */
#endif
#ifndef IPPROTO_ICMP
#define IPPROTO_ICMP    1       /* 控制报文协议  control message protocol */
#endif
#ifndef IPPROTO_IGMP
#define IPPROTO_IGMP    2       /* 组管理协议  group mgmt protocol */
#endif
#ifndef IPPROTO_GGP
#define IPPROTO_GGP     3       /* 路由^2协议澹(不建议)  gateway^2 (deprecated) */
#endif
#ifndef IPPROTO_IPIP            /* IP协议之上的IP  ip over ip protocol */
#define IPPROTO_IPIP    4
#endif
#ifndef IPPROTO_TCP
#define IPPROTO_TCP     6       /* 传输控制协议  tcp */
#endif
#ifndef IPPROTO_EGP
#define IPPROTO_EGP     8       /* 外部路由协议  exterior gateway protocol */
#endif
#ifndef IPPROTO_PUP
#define IPPROTO_PUP     12      /* pup */
#endif
#ifndef IPPROTO_UDP
#define IPPROTO_UDP     17      /* user datagram protocol */
#endif
#ifndef IPPROTO_IDP
#define IPPROTO_IDP     22      /* xns idp */
#endif
#ifndef IPPROTO_TP
#define IPPROTO_TP      29      /* tp-4 w/ class negotiation */
#endif
#ifndef IPPROTO_IPV6
#define IPPROTO_IPV6    41      /* IPv6 in IP */
#endif
#ifndef IPPROTO_GRE
#define IPPROTO_GRE     47      /* Generic Route Encapsulation Protocol */
#endif
#ifndef IPPROTO_ESP
#define IPPROTO_ESP     50      /* Ip Sec */
#endif
#ifndef IPPROTO_AH 
#define IPPROTO_AH      51      /* Ip Sec */
#endif
#ifndef IPPROTO_EON
#define IPPROTO_EON     80      /* ISO cnlp */
#endif
#ifndef IPPROTO_ENCAP
#define IPPROTO_ENCAP   98      /* encapsulation header */
#endif
#ifndef IPPROTO_PIM             /* PIM */
#define IPPROTO_PIM     103
#endif
#ifndef IPPROTO_VRRP
#define IPPROTO_VRRP    112     /*  VRRP */
#endif
#ifndef IPPROTO_ISIS
#define IPPROTO_ISIS    124
#endif

#ifndef IPPROTO_RAWSCTP
#define IPPROTO_RAWSCTP     132        /* SCTP protocol */
#endif

#ifndef IP_VERSION
#define IP_VERSION  4
#endif

#define PP4_INPUT_NORMAL        0
#define PP4_INPUT_DISTRIBUTE    1

/* pp4错误码定义，挪自pp4_core.h */
/* return value for methods in pp4 Cfg interface  */
#define IP_PP4_CFG_OK        VOS_OK
#define IP_PP4_CFG_GEN_ERR   VOS_ERR
#define IP_PP4_CFG_PARA_ERR  2
#define IP_PP4_CFG_IOREQ_ERR 3
#define IP_PP4_CFG_NULL_INT      4   /* 指定的接口指针为空，或由于接口索引无效而无相应接口 */
#define IP_PP4_CFG_NULL_POINTER  5   /* 输入的指针为空 */
#define IP_PP4_CFG_ERR_HOOKTYPE  6   /* 输入的HOOK函数类型错误 */
#define IP_PP4_CFG_HA_IS_SMOOTHING 7  /*HA正在平滑处理或手动倒换处理*/
#define IP_PP4_CFG_NULL_HEAD       8  /*链表头结点为空*/
#define IP_PP4_CFG_MEMMALLOC_FAIL  9  /*内存分配失败*/
#define IP_PP4_CFG_UNREGISTER_FAIL  10 /*动态解注册失败*/
#define IP_PP4_CFG_ALREADY_REGISTERED  11 /* 函数已经注册 */
#define IP_PP4_CFG_NULLIPCTLBLOCK      12 /* IP控制块为空 */
#define IP_PP4_ERR_IS_L2PORT           13 /* 输入的目标接口是二层端口 */

/* intermediate process not processed the packet. 
 * Stack (PP) will do the processing
 */
#define IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE              0 
/* intermediate found the packet has Error, Stack will Destroy the Packet */
#define IP_PP4_INTER_PROCESS_ERROR                        1
/* Intermediate Processing will continue processing and will own the packet
 * PP do not need to process the packet any more
 */
#define IP_PP4_PROCESSED_BY_INTERMEDIATE                  2 

/* ip pakcet hooks type */
#define IP_PP4_HOOK_INPUT_ALL_PKT                   0x01
#define IP_PP4_HOOK_INPUT_LOCAL_PKT                 0x02
#define IP_PP4_HOOK_FORWARD_PKT                     0x04
#define IP_PP4_HOOK_OUTPUT_LOCAL_PKT                0x08
#define IP_PP4_HOOK_OUTPUT_ALL_PKT                  0x10
/* Add for BC3D03018*/
#define IP_PP4_HOOK_REASS_PKT                       0x20

/* 在MBUF的TAG域里设置，表示该IP报文的目地地址是本机某个接口的地址 */
#define IP_PKT_ISOURS           0x00000001

/* 在MBUF的TAG域里设置，表示是报文输入接口的广播报文 */
#define IP_PKT_IIFBRAODCAST     0x00000002

/* 在MBUF的TAG域里设置，表示是报文输出接口的广播报文 */
#define IP_PKT_OIFBRAODCAST     0x00000004

/* 在MBUF的TAG域里设置，表示是本机发送的IP报文 */
#define IP_PKT_OURSENDPKT       0x00000008

/* 在MBUF的TAG域里设置，表示是转发的IP报文 */
#define IP_PKT_FORWARDPKT       0x00000010

/* 在MBUF的TAG域里设置，表示是该报文以太网的广播报文 */
#define IP_PKT_ETHBCAST         0x00000020

/*added by zhaobiao for resolve wether source route opt is set*/
#define IP_PKT_SRCROUTE         0x80000000

/* 标志报文为组播策略路由转发,需要检查出接口的合法性 */
#define IP_PKT_MCAST_PR         0x40000000

#define IPOPT_EOL           0       /* 选项列表结束 end of option list */
#define IPOPT_NOP           1       /* 无操作 no operation */
#define IPOPT_RR            7       /* 记录报文经过路由 record packet route */
#define IPOPT_TS            68      /* 时间戳 timestamp */
#define IPOPT_SECURITY      130     /* 提供s,c,h,tcc  provide s,c,h,tcc */
#define IPOPT_LSRR          131     /* 宽松源站选路  loose source route */
#define IPOPT_SATID         136     /* satnet id */
#define IPOPT_SSRR          137     /* 严格源站选路 strict source route */
#define IPOPT_ROUTE_ALERT   148     /* 传输路线告警，若值为零则直接发送 route alert, if value is 0, then delivertoup */
#define IPOPT_UNKOWN        0x80000000 /*不识别的选项标记*/

/* IP选项对应开关状态宏定义 */
#define IPOPT_PS_ON 1
#define IPOPT_PS_OFF 0
/* IP选项的初始值(缺省值)宏定义 */
#define IPOPT_PS_DEFAULT 0xFFFFFFFF

/* IP层报文过滤条件相关枚举定义 */
typedef enum tagIP_DEBUG_FILTER
{
    IP_DEBUG_FILTER_IFINDEX = 0,      /* 接口索引 */
    IP_DEBUG_FILTER_SRCIP,            /* 源IP */
    IP_DEBUG_FILTER_DSTIP,            /* 目的IP */
    IP_DEBUG_FILTER_PROTO,            /* 协议号 */
    IP_DEBUG_FILTER_SRCPORT,          /* 源端口 */
    IP_DEBUG_FILTER_DSTPORT,          /* 目的端口 */
    IP_DEBUG_FILTER_MAX               /* end */
}IP_DEBUG_FILTER_E;

/* IP层报文过滤条件相关宏定义 */
#define IP_DEBUG_FILTER_FLAG_NOR 1    /* 打开普通报文过滤 */
#define IP_DEBUG_FILTER_FLAG_VBS 2    /* 打开详细报文过滤 */

/* 注册源IP路由后,报文发送方式宏定义 */
#define IP_GO_WITH_SRCROUTE      0    /* 按源路由发送报文 */
#define IP_DROP_PACKET           1    /* 丢弃报文 */
#define IP_GO_PASS               2    /* 按原有方式发送报文 */

typedef ULONG (*IP_PP4_INTERMEDIATE_HOOK_FUNC)(struct tagMBuf *pstMBuf);

/* 在IP发送分片之前钩取完整的IP报文, 钩取到的IP报文首部所有字段都已使用网络序填写完毕，且已计算校验和
   入参说明:
   pstMbuf: IP报文
   返回值说明:
   0  钩子函数已处理且释放了报文
   1  钩子函数未处理报文，由VISP继续发送 */
typedef ULONG (*IP4_SEND_WHOLE_PKT_HOOK)(struct tagMBuf *pstMbuf);

typedef struct tagIP
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR   ip_chHLen:4;        /* header length */
    UCHAR   ip_chVer: 4;         /* version */
#else
    UCHAR  ip_chVer:  4;         /* version */
    UCHAR  ip_chHLen: 4;        /* header length */
#endif
    UCHAR   ip_chTOS;           /* type of service */
    USHORT  ip_usLen;           /* total length */
#define ip_sLen ip_usLen
    USHORT  ip_usId;            /* identification */
    USHORT  ip_usOff;           /* fragment offset field */
#define ip_sOff ip_usOff
#define IP_DF 0x4000            /* dont fragment flag */
#define IP_MF 0x2000            /* more fragments flag */
#define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
    UCHAR   ip_chTTL;           /* time to live */
    UCHAR   ip_chPr;            /* protocol */
    USHORT  ip_usSum;           /* checksum */
    struct  tagINADDR ip_stSrc;
    struct  tagINADDR ip_stDst; /* source and dest address */
}IP_S;

typedef struct  tagIPIFSTAT
{   /* generic interface information */
    ULONG   ifi_ulMetric;    /* routing metric (external only) */
    ULONG   ifi_ulLoad;      /* load on in this interface */
    /* volatile statistics */
    ULONG   ifi_ulIPackets;  /* packets received on interface */
    ULONG   ifi_ulOPackets;  /* packets sent on interface */
    ULONG   ifi_ulIBytes;    /* total number of octets received */
    ULONG   ifi_ulOBytes;    /* total number of octets sent */
    ULONG   ifi_ulIMcasts;   /* packets received via multicast */
    ULONG   ifi_ulOMcasts;   /* packets sent via multicast */
    ULONG   ifi_ulIDropPkts; /* drop packets received on interface */
    ULONG   ifi_ulIDropBytes;/* drop bytes received on interface */
    ULONG   ifi_ulODropPkts; /* drop packets sent on interface */
    ULONG   ifi_ulODropBytes;/* dorp bytes sent on interface */
    ULONG   ipi_ulHookProcessed;    /* processed by hook */
    ULONG   ipi_ulHookNotProcessed; /* not processed by hook */
    ULONG   ipi_ulHookBcastProcessed;   /* b-cast packets processed by hook */
    ULONG   ipi_ulHookBcastNotProcessed;/* b-cast packets not processed by hook */
    ULONG   ipi_ulHookMcastProcessed;   /* m-cast packets processed by hook */
    ULONG   ipi_ulHookMcastNotProcessed;/* m-cast packets not processed by hook */
    ULONG   ipi_ulPpiProcessed;         /* processed by ppi output */
    ULONG   ipi_ulPpiNotProcessed;      /* not processed by ppi output */
    ULONG   ipi_ulPpiBcastProcessed;    /* b-cast packets processed by ppi output */
    ULONG   ipi_ulPpiBcastNotProcessed; /* b-cast packets not processed by ppi output */
    ULONG   ipi_ulPpiMcastProcessed;    /* m-cast packets processed by ppi output */
    ULONG   ipi_ulPpiMcastNotProcessed; /* m-cast packets not processed by ppi output */
}IPIFSTAT_S;

typedef struct  tagIPIFSTAT_LIST
{
    ULONG      ulIfIndex;
    IPIFSTAT_S stIpIfStat;
}IPIFSTAT_LIST_S;



/*****************************************************************
* global ip statictics struct 挪自pp4_pub.h
*****************************************************************/
typedef struct tagIPSTAT
{
    ULONG   ips_ulTotal;         /* total packets received */
    ULONG   ips_ulBadVers;       /* ip version != 4 */
    ULONG   ips_ulBadSum;        /* checksum bad */
    ULONG   ips_ulBadHLen;       /* ip header length < data size */
    ULONG   ips_ulBadLen;        /* ip length < ip header length */
    ULONG   ips_ulTooShort;      /* packet too short */
    ULONG   ips_ulTooSmall;      /* not enough data */
    ULONG   ips_ulTTLExceed;
    ULONG   ips_ulBadOptions;    /* error in option processing */
    ULONG   ips_ulCantForward;   /* packets rcvd for unreachable dest */
    ULONG   ips_ulForward;       /* packets forwarded */
    ULONG   ips_ulNoProto;       /* unknown or unsupported protocol */
    ULONG   ips_ulInDiscards;    /* packets discarded because resource limit */
    ULONG   ips_ulDelivered;     /* datagrams delivered to upper level*/
    ULONG   ips_ulLocalOut;      /* total ip packets generated here */
    ULONG   ips_ulODropped;      /* lost packets due to nobufs, etc. */
    ULONG   ips_ulNoRoute;       /* packets discarded due to no route */
    ULONG   ips_ulFragments;     /* fragments received */
    ULONG   ips_ulReassembled;   /* total packets reassembled ok */
    ULONG   ips_ulFragDropped;   /* frags dropped (dups, out of space) */
    ULONG   ips_ulFragTimeout;   /* fragments timed out */
    ULONG   ips_ulFragmented;    /* datagrams sucessfully fragmented */
    ULONG   ips_ulCantFrag;      /* don't fragment flag was set, etc. */
    ULONG   ips_ulOFragments;    /* output fragments created */
    ULONG   ips_ulRedirectSent;  /* packets forwarded on same net */
    ULONG   ips_ulRawOut;        /* total raw ip packets generated */
    ULONG   ips_ulDistSockSent;  /* distributed socket send package */
}IPSTAT_S;

typedef struct tagSrcRtSearch
{
    ULONG ulNextHopIPAddr;  /* 下一跳地址, 网络序 */
    ULONG ulOutIfIndex;  /* 出接口, 必须是三层接口 */
} SRC_RT_SEARCH_S;


typedef ULONG (*gpfTCPIPSrcRtSearch)(ULONG ulSrcIPAddr, ULONG ulDstIPAddr, SRC_RT_SEARCH_S *pstOutput);

typedef struct tagSrcRtPacket
{
    ULONG ulSrcIPAddr; /* 报文的源地址,网络序     */
    ULONG ulDstIPAddr; /* 报文的目的地址,网络序   */
    ULONG ulVrfIndex;
} SRC_RT_PKT_S;

typedef ULONG (*TCPIP_SRC_RT_SEARCH_FUN)( SRC_RT_PKT_S *pstPktInfo, SRC_RT_SEARCH_S *pstOutput);


extern ULONG TCPIP_ClrIpStatByIf(ULONG ulIfIndex);

extern ULONG TCPIP_ClrIpStatics (VOID);

extern ULONG TCPIP_GetDefaultTTL(VOID);

extern ULONG TCPIP_GetIpStatByIf(ULONG ulIfIndex, IPIFSTAT_S * pstIpStat);

extern ULONG TCPIP_GetIpStatics (IPSTAT_S* pstIpStat);

extern ULONG TCPIP_GetPP4DebugFlag(ULONG *pulDebugFlag, ULONG *pulDebugIpAcl, ULONG *pulDebugIpIfAcl,
    ULONG *pulDebugIpIfOpt, ULONG *pulDebugIpErr, ULONG *pulDebugPacketVerbose);

extern ULONG TCPIP_IpOutput (MBUF_S* pstMBuf);

extern ULONG TCPIP_IP_IF_Output(MBUF_S *pstMbuf);

extern ULONG TCPIP_IP_PP4_Intermediate_Hook_Register(ULONG ulType, ULONG ulPriority, 
    IP_PP4_INTERMEDIATE_HOOK_FUNC pfIpFwHookFunc);

extern ULONG TCPIP_IP_PP4_Intermediate_Hook_UnRegister(ULONG ulType, 
    IP_PP4_INTERMEDIATE_HOOK_FUNC pfIpFwHookFunc);

extern ULONG TCPIP_SetDefaultTTL(ULONG ulTtl);

extern ULONG TCPIP_SetIcmpHostUnreach (ULONG ulIfIndex, ULONG ulFlag);

extern ULONG TCPIP_SetIcmpRedirects(ULONG ulIfIndex, ULONG ulFlag);

extern ULONG TCPIP_SetPP4DebugFlag(ULONG ulIpDebugNo, ULONG ulDebugAcl, ULONG ulDebugIfAcl, 
    ULONG ulDebugIfOpt, ULONG ulDebugIpErr, ULONG ulDebugIpVerbose);

extern VOID TCPIP_ShowPP4Statistic(VOID);

extern VOID TCPIP_ShowPP4StatisticByInterface(CHAR *pName);

extern ULONG TCPIP_SetForwardFlag(ULONG ulFlag);

extern ULONG TCPIP_GetForwardFlag(ULONG *pulFlag);

extern ULONG TCPIP_GetIpId(USHORT *pusIpId);

extern VOID TCPIP_IncreaseIpId(VOID);
extern ULONG TCPIP_ShowPP4DebugFlag( VOID );
/*******************************************************************************
*    Func Name: TCPIP_RegFuncIpSendWholePktHook
*  Description: 注册钩子函数, 在IP发送分片之前钩取完整的IP报文
*        Input: IP4_SEND_WHOLE_PKT_HOOK pfHook: 钩子函数指针
*       Output: 
*       Return: VOS_OK   成功
*               VOS_ERR  钩子函数指针为空
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-10-24  wujie(61195)     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncIpSendWholePktHook(IP4_SEND_WHOLE_PKT_HOOK pfHook);

/*******************************************************************************
*    Func Name: TCPIP_SetIpOptAttackGuardSwitch
* Date Created: 2009-09-15
*       Author: wuhailan103194
*  Description: 设置针对IP选项攻击进行控制、防范IP选项攻击的开关
*               开关打开后将不再支持带IP选项的报文处理
*        Input: ULONG ulSwitch:开关,0 关闭, 1 打开, 默认关闭
*       Output: 
*       Return: VOS_OK:成功 其他返回失败
*      Caution: 本接口与TCPIP_SetIpOptPermitSwitch接口不建议同时使用，如果设置
*               全部选项调用本接口，设置单个选项调用TCPIP_SetIpOptPermitSwitch
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-15   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIpOptAttackGuardSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetIpOptAttackGuardSwitch
* Date Created: 2009-09-22
*       Author: wuhailan103194
*  Description: 获取针对IP选项攻击进行控制、防范IP选项攻击的开关
*        Input: 
*       Output: ULONG *pulSwitch:返回的开关值
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-22   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIpOptAttackGuardSwitch(ULONG *pulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SetIpOptPermitSwitch
* Date Created: 2011-03-28
*       Author: mafeng59090
*  Description: 设置指定选项是否允许处理,缺省允许所有选项
*        Input: ULONG ulOption:选项值，目前VISP支持设置的选项如下:
* IPOPT_RR            7        记录报文经过路由 
* IPOPT_TS            68       时间戳 
* IPOPT_SECURITY      130      提供s,c,h,tcc 
* IPOPT_LSRR          131      宽松源站选路 
* IPOPT_SATID         136      satnet id 
* IPOPT_SSRR          137      严格源站选路 
* IPOPT_ROUTE_ALERT   148      传输路线告警 
* IPOPT_UNKOWN        0x80000000 不识别选项处理
*               ULONG ulSwitch:1 支持允许处理该选项,0 不允许处理含该选项的报文
*       Output: 
*       Return: 成功/失败
*      Caution: 本接口与TCPIP_SetIpOptAttackGuardSwitch接口不建议同时使用，
*               如果设置单个选项的开关调用本接口，如果设置全部的接口则调用
*               TCPIP_SetIpOptAttackGuardSwitch接口
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-03-28   mafeng59090             Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIpOptPermitSwitch(ULONG ulOption, ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetIpOptPermitSwitch
* Date Created: 2011-03-28
*       Author: mafeng59090
*  Description: 获取指定选项的VISP允许处理开关
*        Input: ULONG ulOption:选项值，目前VISP支持设置的选项如下:
* IPOPT_RR            7        记录报文经过路由 
* IPOPT_TS            68       时间戳 
* IPOPT_SECURITY      130      提供s,c,h,tcc 
* IPOPT_LSRR          131      宽松源站选路 
* IPOPT_SATID         136      satnet id 
* IPOPT_SSRR          137      严格源站选路 
* IPOPT_ROUTE_ALERT   148      传输路线告警 
* IPOPT_UNKOWN        0x80000000 不识别选项处理
*               ULONG *pulSwitch:开关值，1 允许，0 不允许
*       Output: pulSwitch
*       Return: 成功/失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-03-28   mafeng59090             Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIpOptPermitSwitch(ULONG ulOption, ULONG *pulSwitch);


extern ULONG TCPIP_SetIpDebugFilter(ULONG ulSetYes, ULONG ulIfIndex, CHAR *szSrcIp, CHAR *szDstIp,
    ULONG ulProtocol, ULONG ulSrcPort, ULONG ulDstPort);


extern ULONG TCPIP_GetIpDebugFilter(ULONG *pulDebugFlag, ULONG *pulDebugFilter);


extern VOID TCPIP_ShowIpDebugFilter(VOID);


extern ULONG TCPIP_RegFuncSrcRtSearch(gpfTCPIPSrcRtSearch pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncSrcRtSearchByVrf
* Date Created: 2013-12-06
*       Author: likaikun213099
*  Description: 注册根据源IP查找路由钩子
*        Input: TCPIP_SRC_RT_SEARCH_FUN pfHookFunc:产品注册根据源IP查找路由钩子函数
*       Output: 
*       Return: IP_GO_WITH_SRCROUTE     按源路由发送报文
*               IP_DROP_PACKET          丢弃报文
*               IP_GO_PASS              按原有方式发送报文
*      Caution: 不允许解注册,相对TCPIP_RegFuncSrcRtSearch增加VRF特性支持
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-06   likaikun213099          Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncSrcRtSearchByVrf(TCPIP_SRC_RT_SEARCH_FUN pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncIpSendPktNoFibSearchHook
* Date Created: 2014-03-12
*       Author: qinyun62011
*  Description: 注册IP发送钩子函数，此钩子在路由查询之前调用
*        Input: IP4_SEND_WHOLE_PKT_HOOK pfHook:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-12   qinyun62011             Create for (Distribute socket)分布式socket裁剪
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncIpSendPktNoFibSearchHook(IP4_SEND_WHOLE_PKT_HOOK pfHook);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __PP4_API_H__ */

