
/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ppmng_api.h
*
*  Project Code: VISPV1R7
*   Module Name: PPMNG  
*  Date Created: 2008-3-9
*        Author: wangbin(62223)
*   Description: ppmng模块对外提供的头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-3-8 wangbin(62223)     Create the first version.
*
*******************************************************************************/
#ifndef _PPMNG_API_H_
#define _PPMNG_API_H_

#ifdef __cplusplus
extern "C"{
#endif

/* wangjiaq modify for mccp headfile include */
/* Stack (PP) will do the processing*/
#define PP_NO_PROCESS_NEEDED_BY_INTER_FUNCTION              1 

/* Packet has Error, Stack will Destroy the Packet */
#define PP_RET_ERROR                                        2

/* Intermediate Processing will continue processing and will own the packet and if needed will destroy it */
#define PP_PROCESS_BY_INTER_FUNCTION                        3 

/* Packet has been administratively prohibited (for eg: by ACL) */
#define PP_SEND_ICMP_ERROR                                  4
/* Packet has been processed by Qos Input */
#define PP_PROCESS_BY_INTER_FUNCTION_QOSINPUT                       5

#ifndef IPPROTO_DONE
#define IPPROTO_DONE    257 /* 标志扩展头和上层协议处理结束 */
#endif

#define PP_INPUT_TYPE                   0x01
#define PP_OUTPUT_TYPE                  0x02
#define PP_IO_TYPE                       0x04
#define PP_IFOUTPUT_TYPE                0x08
#define PP_QOSOUTPUT_TYPE               0x10

#define PR_ATOMIC       0x01        /* 只交换少量的信息    exchange atomic messages only */
#define PR_ADDR         0x02        /* 消息中包含地址      addresses given with messages */

typedef enum tagPPMNG_ERROR
{
    PP6_OK = 0,
    PP6_ERR,
    PP6_NOT_REGISTER,               /* 2  PPMNG组件未注册 */
    PP6_ERR_HOSTNODE,               /* 3  IPV6主机模式 */
    PP6_HOOK_NULL,                  /* 4  钩子函数为NULL */
    PP6_INPUT_PARA_NULL,            /* 5  输入参数为NULL */
    PP6_FLOW_STAT_MAX_NUM,          /* 6  达到最大支持报文统计类型*/
    PP6_FLOW_NO_RECORD,             /* 7  通过协议号和端口号没有找到对应的报文统计记录*/
}PPMNG_ERROR_E;

/* IPV6报文不分片标志,
  HERT2.8的IPV6 PATH MTU 功能会使用,所以在API中定义一份,注意该宏定义必须与ppmng_pub.h中的IPV6_PKT_DONTFRAG定义保持一致 */
#define IPV6_PKT_DONTFRAG           0x00000200

#ifndef _IN6ADDR_S
#define _IN6ADDR_S
typedef   struct    tagIN6Addr
{
    union
    {
        UCHAR     u6_ucaddr[16];
        USHORT    u6_usaddr[8];
        ULONG     u6_uladdr[4];
    } u6_addr;    /* 128-bit IP6 address */
} IN6ADDR_S;
#endif

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
            /* LITTLE_ENDIAN */
            UCHAR uc_ip6_unused:4;      /* 4 bits traffic class */
            UCHAR uc_ip6_ver:4;         /* 4 bits version */
#else
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

/* IPv6报文统计信息的结构 */
typedef struct tagIP6STAT
{
    ULONG   ip6s_ulTotalReceived;   /* total packets received */
    ULONG   ip6s_ulTooShort;        /* packet too short */
    ULONG   ip6s_ulTooSmall;        /* not enough data */
    ULONG   ip6s_ulHopLimitExceed;  /* hop limit exceed */
    ULONG   ip6s_ulBadHeader;       /* error in header processing */
    ULONG   ip6s_ulBadOption;       /* error in option processing */    
    ULONG   ip6s_ulFragments;       /* fragments received */
    ULONG   ip6s_ulReassembled;     /* total packets reassembled ok */
    ULONG   ip6s_ulFragDropped;     /* frags dropped (dups, out of space) */
    ULONG   ip6s_ulFragTimeout;     /* fragments timed out */
    ULONG   ip6s_ulOFailedFragments; /* Fragments Failed to Sent Out. */
    ULONG   ip6s_ulNoProto;         /* unknown or unsupported protocol */
    ULONG   ip6s_ulDelivered;       /* datagrams delivered to upper level*/
    ULONG   ip6s_ulLocalOut;        /* total ipv6 packets generated */
    ULONG   ip6s_ulForward;         /* packets forwarded */
    ULONG   ip6s_ulNoRoute;         /* packets discarded due to no route */
    ULONG   ip6s_ulTooBig;          /* packets discarded due to bigger than mtu*/
    ULONG   ip6s_ulFragmented;      /* datagrams sucessfully fragmented */
    ULONG   ip6s_ulOFragments;      /* output fragments created */
    ULONG   ip6s_ulInMulticasts;    /* multicast packets received */
    ULONG   ip6s_ulNotMember;       /* donot join this multicast group */
    ULONG   ip6s_ulOutMulticasts;   /* multicast packets sent */
    ULONG   ip6s_ulDstAddrErr;      /* error in incoming dest addr (invalid and unsupported) */

/* TODO: Where will this happen ??? - this is a MIB requirement */
    ULONG   ip6s_ulInDiscards;      /* Input Dgms which had no pbms, but were discarded due to lack of buffer space */
    ULONG   ip6s_ulOutDiscards;     /* Output Dgms which had no pbms, but were discarded due to lack of buffer space */
}IP6STAT_S;


#ifndef _ICMP6_ERRSTAT_S 
#define _ICMP6_ERRSTAT_S

/* generate ICMP6 error packet statistics */
typedef struct tagICMP6_ERRSTAT 
{
    ULONG ulIcp6errs_dst_unreach_noroute;
    ULONG ulIcp6errs_dst_unreach_admin;
    ULONG ulIcp6errs_dst_unreach_beyondscope;
    ULONG ulIcp6errs_dst_unreach_addr;
    ULONG ulIcp6errs_dst_unreach_noport;
    ULONG ulIcp6errs_dst_unreach_ingress_egress_plcy;
    ULONG ulIcp6errs_dst_unreach_reject_route;
    ULONG ulIcp6errs_packet_too_big;
    ULONG ulIcp6errs_time_exceed_transit;
    ULONG ulIcp6errs_time_exceed_reassembly;
    ULONG ulIcp6errs_paramprob_header;
    ULONG ulIcp6errs_paramprob_nextheader;
    ULONG ulIcp6errs_paramprob_option;
    ULONG ulIcp6errs_redirect; /* we regard redirect as an error here */
    ULONG ulIcp6errs_unknown;
}ICMP6_ERRSTAT_S;
#endif


#ifndef _ICMP6STAT_S 
#define _ICMP6STAT_S

/* ICMP6 packet statistics */
typedef struct tagICMP6STAT 
{
    /* statistics related to icmp6 packets generated */
    ULONG ulIcp6s_error;            /* no of calls to icmp6_error */
    ULONG ulIcp6s_canterror;        /* no error 'cuz old was icmp */
    ULONG ulIcp6s_toofreq;          /* no error 'cuz rate limitation */
    ULONG ulIcp6s_intoofreq;        /* no error 'cuz rate limitation */
    ULONG ulIcp6s_outhist[256];

    /* statistics related to input message processed */
    ULONG ulIcp6s_badcode;          /* icmp6_code out of range */
    ULONG ulIcp6s_tooshort;         /* packet < sizeof(struct icmp6_hdr) */
    ULONG ulIcp6s_checksum;         /* bad checksum */
    ULONG ulIcp6s_badlen;           /* calculated bound mismatch */

    ULONG ulIcp6s_reflect;
    ULONG ulIcp6s_inhist[256];    
    ULONG ulIcp6s_nd_toomanyopt;    /* too many ND options */
    
    ICMP6_ERRSTAT_S stIcp6s_outerrhist;
    ICMP6_ERRSTAT_S stIcp6s_inerrhist;

    ULONG ulIcp6s_pmtuchg;           /* path MTU changes */
    ULONG ulIcp6s_nd_badopt;         /* bad ND options */
    ULONG ulIcp6s_badns;             /* bad neighbor solicitation */
    ULONG ulIcp6s_badna;             /* bad neighbor advertisement */
    ULONG ulIcp6s_badrs;             /* bad router advertisement */
    ULONG ulIcp6s_badra;             /* bad router advertisement */

    /* Added by Saravanya for ND Host */
    ULONG ulIcp6s_badredirect;       /* bad Redirect received */

    ULONG  ulIcps_totaloutput;       /* Sent total */
    ULONG  ulIcps_totalinput;        /* Recvd total */
    ULONG  ulIcps_inunknowninfo;     /* Recvd unknown info type */
    ULONG  ulIcps_inunknownerror;    /* Recvd unknown error type */
    ULONG  ulIcp6s_inhopexpired;     /* Recvd hop expired */
    ULONG  ulIcp6s_reassexpired;     /* Recvd reassemble expired */
}ICMP6STAT_S;
#endif 
typedef struct tagIP6ICMP6Stats 
{
    IP6STAT_S stIP6Stats;
    ICMP6STAT_S stICMP6Stats;
} IP6_ICMP6_STATS_S;


/* Intermediate Processing. */
typedef ULONG (*IP6_PP_Register) (MBUF_S *pstMBuf);

/* 钩子函数的返回值 */
typedef enum enumHookRetValue
{
    HOOK_RET_STACK_CONTINUE_PROC,   /* 钩子函数返回该值时协议栈继续处理报文,这要求钩子函数不能修改原有报文 */
    HOOK_RET_STACK_DROP_PAKET,      /* 钩子函数返回该值时协议栈丢弃报文 */
    
    HOOK_RET_END,                   
}HOOK_RET_VALUE_E;

/* 产品处理钩子只能返回以下值:
   HOOK_RET_STACK_CONTINUE_PROC: 钩子函数返回该值时协议栈继续处理报文,这要求钩子函数不能修改原有报文;
   HOOK_RET_STACK_DROP_PAKET: 钩子函数返回该值时协议栈丢弃报文;
*/
typedef struct tagTCPIP_IP6_PROC_ICMP6_PKT_HOOK
{
    ULONG (*pfTCPIPIp6ProcSndIcmp6PktHook) (MBUF_S *pstMBuf);
    ULONG (*pfTCPIPIp6ProcRcvIcmp6PktHook) (MBUF_S *pstMBuf);
}TCPIP_IP6_PROC_ICMP6_PKT_HOOK_S;

/*Added by wangtong207740, MRP IPv6选路需求, 2012/11/21 */
typedef enum enumIP6RetSrcRt
{
    IP6_GO_WITH_SCRRT, /*查产品源路由成功*/
    IP6_DROP_PKT,      /*查产品源路由不成功，需要丢包处理*/     
    IP6_GO_PASS,       /*查产品源路由不成功，继续走原有查路由表流程*/                   
}RET_IP6_SRC_RT_E;

typedef struct tagIP6SrcRtSearch
{
    IN6ADDR_S ulNextHopIPAddr;  /* 下一跳地址, 网络序 */
    ULONG ulOutIfIndex;  /* 出接口, 必须是三层接口 */
} IP6_SRC_RT_SEARCH_S;

/*******************************************************************************
*    Func Name: gpfIP6TCPIPSrcRtSearch
*  Description: 根据源IP查找路由钩子原型
*        Input: IN6ADDR_S ulSrcIPAddr: 报文的源地址,网络序
*             : IN6ADDR_S ulDstIPAddr: 报文的目的地址,网络序
*       Output: IP6_SRC_RT_SEARCH_S *pstOutput:  源IP路由查询结果
*       Return: 成功:VOS_OK
*               失败:其他    不通过源IP路由方式发送，VISP按照原有方式
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-01   z00171897/s00176784     Create
*  2011-07-28   z00171897               DTS2011072801526 输入参数增加目的IP
*******************************************************************************/
typedef ULONG (*gpfIP6TCPIPSrcRtSearch)(IN6ADDR_S ulSrcIPAddr, IN6ADDR_S ulDstIPAddr, IP6_SRC_RT_SEARCH_S *pstOutput);

extern gpfIP6TCPIPSrcRtSearch g_pfIp6SrcRtSearch;


typedef struct tagSrcRt6Packet
{
    IN6ADDR_S ulSrcIPAddr; /* 报文的源地址,网络序     */
    IN6ADDR_S ulDstIPAddr; /* 报文的目的地址,网络序   */
    ULONG ulVrfIndex;
} SRC_RT6_PKT_S;
typedef ULONG (*TCPIP_SRC_RT6_SEARCH_FUN)(SRC_RT6_PKT_S *pstPktInfo, IP6_SRC_RT_SEARCH_S *pstOutput);
extern TCPIP_SRC_RT6_SEARCH_FUN g_pfIp6SrcRtSearchByVrf;

/*add by wuling 00201943 for 支持IPv6无下一跳定制场景报文收发 2014-04-29 --start*/
typedef ULONG (*pfTCPIPNeedLookupNdHook)(MBUF_S* pstMbuf);
extern pfTCPIPNeedLookupNdHook g_pfIP6NeedLookupNd;

typedef enum enumIP6NeedLookUpND
{
    IP6_NO_NEED_LOOK_UP_ND,   /*不需要查找ND*/
    IP6_NEED_LOOK_UP_ND,      /*需要查找ND*/     
}IP6_NEED_LOOK_UP_E;
/*add by wuling 00201943 for 支持IPv6无下一跳定制场景报文收发 2014-04-29 --end*/

/* IPv6 address数据结构
   该结构定义了IPv6地址的内容。
   描述了IPv6地址128bit的具体内容，采用共用体来方便对地址字段的操作 */
#ifndef _IN6ADDR_S
#define _IN6ADDR_S
typedef   struct    tagIN6Addr
{
    union
    {
        UCHAR     u6_ucaddr[16];
        USHORT    u6_usaddr[8];
        ULONG     u6_uladdr[4];
    } u6_addr;    /* 128-bit IP6 address */
} IN6ADDR_S;
#endif


/* 用于设置/读取报文信息的结构 */
typedef struct tagIP6_PKTINFO {
    IN6ADDR_S   ipi6_stAddr;      /* src/dst IPv6 address */
    ULONG       ipi6_ulIfindex;   /* send/recv interface index */
}IP6_PKTINFO_S;

typedef struct tagIP6_NHINFO {
    SOCKADDR_IN6_S stip6po_nhi_nexthop;
} IP6_NHINFO;

#pragma    pack( 1 )
typedef struct tagIP6_HBH {
    UCHAR   ip6h_ucnxt;   /* next header */
    UCHAR   ip6h_uclen;   /* header length in units of 8 octets, exclude first 8 octets */
}IP6_HBH_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

#pragma    pack( 1 )
typedef struct tagIP6_DEST {
    UCHAR   ip6d_ucnxt;   /* next header */
    UCHAR   ip6d_uclen;   /* header length in units of 8 octets, exclude first 8 octets */
}IP6_DEST_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

typedef struct tagIP6_ROUTE {
    UCHAR  ip6r_ucnxt;        /* next header */
    UCHAR  ip6r_uclen;        /* length in units of 8 octets, exclude first 8 octets */
    UCHAR  ip6r_uctype;       /* routing type */
    UCHAR  ip6r_ucsegleft;    /* segments left */

    /* followed by routing type specific data */
}IP6_ROUTE_S;

typedef struct tagIp6multi {
    IN6ADDR_S stIP6Addrr;                /* IP6 multicast address */
    ULONG ulIfIndex;
} IP6Multi;

/* Multi-cast membership entry.  One for each group/ifp that a PCB belongs to. */
typedef struct tagIp6multimship {
    IP6Multi stIP6maddr;                    /* Multicast address pointer */
    struct tagIp6multimship *pstNext, *pstPrev;  /* multicast options chain */
}IP6_MultiMembership;

/* 用于设置组播报文选项的宏 */
typedef struct tagIP6_MOPTIONS_S
{
    ULONG   im6o_ulIndexIf;         /* ifp for outgoing multicasts */
    UCHAR   im6o_ucMulticast_hlim;    /* hoplimit for outgoing multicasts */
    UCHAR   im6o_ucMulticast_loop;    /* 1 >= hear sends if a member */
    UCHAR   ucPadding[2];
    IP6_MultiMembership *pstMultiMemberships;
    /* 加入的组播组等更多的参数待以后增加 */
}IP6_MOPTIONS_S;

/* 用于设置发送报文的选项的结构 */
typedef struct tagIP6_PKTOPTS_S {
    /* Hoplimit for outgoing packets */
    LONG ip6po_lHlim;   

    /* traffic class */
    LONG ip6po_lTclass;

    UCHAR ip6po_ucTos;
    UCHAR ucPadding[3];
    /* Outgoing IF/address information */
    IP6_PKTINFO_S *ip6po_pstPktinfo;

    /* Next-hop address information, not support now */
    IP6_NHINFO *ip6po_pstNHinfo;

    /* Hop-by-Hop options header */
    IP6_HBH_S *ip6po_psthbh;

    /* Destination options header (before a routing header) */
    IP6_DEST_S *ip6po_pstdest1;

    /* Routing header related info. */
    IP6_ROUTE_S *ip6po_pstroute;

    /* Destination options header (after a routing header) */
    IP6_DEST_S *ip6po_pstdest2;

    /* flags, not used now */
    ULONG ip6po_ulFlags;

    /* 标志本结构中指针指向的内存是否需要释放 */ 
    /* 
     * members dynamically allocated - 
     * this value will be 1 if the memory of the particular pkt option (or all) needs to be freed
     */
    ULONG ip6po_ulNeedFree;

    /* Add for Jira: VISPV2R3C05STACK-119 , by y00176567, at 2011-09-14. 修改原因: 增加IPv6报文头流标签选项 */
    ULONG ip6po_ulFlowID;
}IP6_PKTOPTS_S;

/* Protocol Management related Data Structures */
struct tagIP6_PROTOSW;

typedef struct  tag6DOMAIN
{
    int     dom_nFamily;            /* AF_INET6 */
    char    *dom_pName;

    void    (*dom_pfInit) (void);    /* initialize domain data structures */

    int     (*dom_pfExternalize) (MBUF_S *);   /* externalize access rights */
    int     (*dom_pfDispose) (MBUF_S *);       /* dispose of internalized rights */

    struct tagIP6_PROTOSW   *dom_pProtoSw, *dom_pNextProtoSw;
    struct tag6DOMAIN    *dom_pNext;

    int     (*dom_pfRtAttach) (void **, int);/* initialize routing table */

    int     dom_nRtOffset;          /* an arg to rtattach, in bits */
    int     dom_nMaxRtKey;          /* for routing layer */

}IP6_PP_DOMAIN_S;

typedef struct tagIP6_PROTOSW
{
    /* Modified by X36317, 将此变量类型有short改为LONG，以解决ARM CPU四字节对齐问题, 2006/5/20 */
    LONG   pr_sType;                       /* socket type used for */
    struct tag6DOMAIN *pr_pDomain;         /* domain protocol a member of */
    SHORT  pr_sProtocol;                   /* protocol number */
    SHORT  pr_sFlags;                      /* see below */

    /* protocol-protocol hooks */

    /* input to protocol (from below) */
    ULONG  (*pr_pfInput)(MBUF_S **pRcvSeg, ULONG *, ULONG);

    /* output to protocol (from above) */
    LONG   (*pr_pfOutput)(MBUF_S *,VOID *,VOID*,ULONG,VOID*);

    /* control input (from below) */
    VOID   (*pr_pfCtlInput)(LONG,VOID *,VOID *);

    /* control output (from above) */
    LONG    (*pr_pfCtlOutput)(LONG, ULONG, LONG, LONG, MBUF_S **);
    /* user-protocol hook */

    /* user request: see list below */
    LONG    (*pr_pfUsrReq)(ULONG, LONG, VOID *, VOID *, VOID *);

    /* utility hooks */
    VOID   (*pr_pfInit)(VOID);       /* initialization hook */
    VOID   (*pr_pfFastTimO)(VOID);   /* fast timeout (200ms) */
    VOID   (*pr_pfSlowTimO)(VOID);   /* slow timeout (500ms) */
    VOID   (*pr_pfDrain)(VOID);      /* flush any excess space possible */

    /* sysctl for protocol */
    LONG    (*pr_pfSysCtl)(LONG *,ULONG,VOID *,ULONG *,VOID *,ULONG);

} IP6_PP_PROTOSW_S;

typedef struct tagTCPIP_PP6_PKTTYPE_KEY
{
    USHORT  usPort;      /*本端端口号,必须传入主机序*/
    UCHAR   ucPro;       /*协议号*/
    UCHAR   ucPad[33];   /*保留字段*/
}TCPIP_PP6_PKTTYPE_STAT_KEY_S;/*IPv6 流统计 key*/ 

typedef struct tagTCPIP_PP6_PKTTYPE_STAT
{
    ULONG  ulSndPkt;     /*发送报文统计*/
    ULONG  ulRcvPkt;     /*接收报文统计*/
    ULONG  ulSndErrPkt;  /*发送错误的报文统计*/
    ULONG  ulReserve[8]; /*预留字段*/
}TCPIP_PP6_PKTTYPE_STAT_S;/*PP6类型 报文统计*/

typedef struct tagTCPIP_PP6_PKT_STAT
{
    TCPIP_PP6_PKTTYPE_STAT_KEY_S  stPktType;
    TCPIP_PP6_PKTTYPE_STAT_S      stFlowStat;
    struct tagTCPIP_PP6_PKT_STAT *pstNext;
}TCPIP_PP6_PKT_STAT_S;


typedef ULONG (*IP6_SEND_PKT_HOOK)(struct tagMBuf *pstMbuf);

/*******************************************************************************
*    Func Name: TCPIP_IP6_RegProcessIcmp6PktHook
* Date Created: 2009-12-16
*       Author: w60786
*  Description: 注册ICMP6报文处理钩子(该ICMP6报文是带IPv6头的)
*        Input: TCPIP_IP6_PROC_ICMP6_PKT_HOOK_S pfHookFunc: ICMP6报文处理钩子
*       Output: 
*       Return: PP6_OK: 钩子注册成功
*               其它: 错误码
*      Caution: 产品注册的处理钩子只能返回以下值:
*               HOOK_RET_STACK_CONTINUE_PROC: 钩子函数返回该值时协议栈继续处理报文,这要求钩子函数不能修改原有报文;
*               HOOK_RET_STACK_DROP_PAKET: 钩子函数返回该值时协议栈丢弃报文;
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-12-16   w60786           Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_IP6_RegProcessIcmp6PktHook(TCPIP_IP6_PROC_ICMP6_PKT_HOOK_S *pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_ClrPP6ICMP6Stat
*  Description: 清除PP6/ICMP6统计信息
*        Input: VOID
*       Output: VOID
*       Return: VOS_ERR
*               VOS_OK
*               PP6_NOT_REGISTER
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/

extern ULONG TCPIP_ClrPP6ICMP6Stat(VOID);

/*******************************************************************************
*    Func Name: TCPIP_GetPP6ICMP6Stat
*  Description: 获取PP6/ICMP6统计信息
*        Input: 
*       Output: IP6_ICMP6_STATS_S :pstIp6Icmp6Stats
*       Return: VOS_ERR
*               VOS_OK
*               PP6_NOT_REGISTER
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/

extern ULONG TCPIP_GetPP6ICMP6Stat(IP6_ICMP6_STATS_S *pstIp6Icmp6Stats);

/*******************************************************************************
*    Func Name: TCPIP_SetPP6Redirect
*  Description: 使能/去使能发送重定向报文功能
*        Input: ULONG ulRedirectFlag
*       Output: VOID
*       Return: VOS_ERR
*               VOS_OK
*               PP6_NOT_REGISTER
*               PP6_ERR_HOSTNODE
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetPP6Redirect (ULONG ulRedirectFlag);

/*******************************************************************************
*    Func Name: TCPIP_SetPP6DebugFlag
*  Description: 设置PP6的重定向功能
*        Input: ULONG ulDebugFlag
                ULONG ulErrpktDebugFlag
*       Output: VOID
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SetPP6DebugFlag(ULONG ulDebugFlag , ULONG ulErrpktDebugFlag);

/*******************************************************************************
*    Func Name: TCPIP_IP_PP6_Intermediate_Hook_Register
*  Description: 用户注册IP6层中间处理钩子函数。
*        Input: ULONG: ulType
                ULONG ulPriority
                IP6_PP_Register pfIpFwHookFunc
*       Output: VOID
*       Return: VOS_ERR
*               VOS_OK
*               PP6_NOT_REGISTER
*               PP6_ERR_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_IP_PP6_Intermediate_Hook_Register(ULONG ulType,ULONG ulPriority, IP6_PP_Register pfIpFwHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncIP6SrcRtSearch
* Date Created: 2012-11-21
*       Author: wangtong207740
*  Description: 
*        Input: gpfIP6TCPIPSrcRtSearch pfHookFunc:
*       Output: VOS_OK-注册钩子函数成功
*               VOS_ERR-注册钩子函数失败
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-11-21   wangtong207740          Create
*
*******************************************************************************/
extern  ULONG TCPIP_RegFuncIP6SrcRtSearch(gpfIP6TCPIPSrcRtSearch pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncIP6SrcRtSearchByVrf
* Date Created: 2013-12-06
*       Author: likaikun213099
*  Description: 注册根据源IP查找路由钩子
*        Input: TCPIP_SRC_RT6_SEARCH_FUN pfHookFunc:产品注册根据源IP查找路由钩子函数
*       Output: 
*       Return: VOS_OK-注册钩子函数成功
*               VOS_ERR-注册钩子函数失败
*      Caution: 不允许解注册,相对TCPIP_RegFuncIP6SrcRtSearch增加VRF特性支持
*               钩子返回值:
*               IP6_GO_WITH_SCRRT, 查产品源路由成功
*               IP6_DROP_PKT,      产品源路由不成功，需要丢包处
*               IP6_GO_PASS,       产品源路由不成功，继续走原有查路由表流
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-06   likaikun213099          Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncIP6SrcRtSearchByVrf(TCPIP_SRC_RT6_SEARCH_FUN pfHookFunc);


extern ULONG IP6_PP_Output (MBUF_S *pstMBuf, IP6_PKTOPTS_S *pstOpt, ULONG ulZoneId, LONG lFlags, IP6_MOPTIONS_S *pstMo);

/********************************************************************************
 * Prototype     : ULONG  IP6_PP_PM_Protocol_Register (LONG lPID,
 *                                                  IP6_PP_PROTOSW_S *pstinfo)
 * Description   : Protocol Registration Function
 * Input(s)      :
 *                 lPID -
 *                 pstProtocolInfo -
 * Output(s)     : N/A
 * Return        : TRUE/FALSE
 *-------------------------------------------------------------------------------
 * History
 * Date(yyyy-mm-dd)     Author        Modification
 *  2003-06-10           Arun          Created
 ********************************************************************************/
extern ULONG IP6_PP_PM_Protocol_Register (LONG lPID, IP6_PP_PROTOSW_S *pstProtocolInfo);

/*******************************************************************************
*    Func Name: TCPIP_PP6Output
* Date Created: 2014-02-28
*       Author: likaikun213099
*  Description: 发送IPv6报文
*        Input: MBUF_S* pstMBuf:报文，需要调用DOPRA MBUF函数，获取DOPRA的MBUF内存组装报文发送
*       Output: 成功：VOS_OK
*               失败：VOS_ERR
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-28   likaikun213099          Create
*
*******************************************************************************/
extern ULONG TCPIP_PP6Output(MBUF_S* pstMBuf);

/*******************************************************************************
*    Func Name: TCPIP_PP6_PktTypeStat_Register
* Date Created: 2014-04-03
*       Author: wuling 00201943
*  Description: 注册对应协议号&端口号的报文统计
*        Input: TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey:根据协议号和端口号注册报文
*               统计信息;结构体中的端口号usPort必须为网络序
*       Output: 成功：VOS_OK
*               失败：VOS_ERR
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-03   wuling 00201943         Create
*
*******************************************************************************/
extern ULONG TCPIP_PP6_PktTypeStat_Register(TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey);

/*******************************************************************************
*    Func Name: TCPIP_PP6_PktTypeStat_UnRegister
* Date Created: 2014-04-03
*       Author: wuling 00201943
*  Description: 删除对应协议号&端口号的报文统计
*        Input: TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey:根据协议号和端口号注册报文
*               统计信息;结构体中的端口号usPort必须为网络序
*       Output: 成功：VOS_OK
*               失败：VOS_ERR
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-03   wuling 00201943         Create
*
*******************************************************************************/
extern ULONG TCPIP_PP6_PktTypeStat_UnRegister(TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey);

/*******************************************************************************
*    Func Name: TCPIP_GetPP6PktTypeStat
* Date Created: 2014-04-03
*       Author: wuling 00201943
*  Description: 删除对应协议号&端口号的报文统计
*        Input: TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey:根据协议号和端口号注册报文
*               统计信息;结构体中的端口号usPort必须为网络序
*       Output: TCPIP_PP6_PKTTYPE_STAT_S *pstFlowStat:报文统计计数
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-03   wuling 00201943         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPP6PktTypeStat(TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey, 
                                         TCPIP_PP6_PKTTYPE_STAT_S *pstFlowStat);

/*******************************************************************************
*    Func Name: TCPIP_ClrPP6PktTypeStat
* Date Created: 2014-04-03
*       Author: wuling 00201943
*  Description: 
*        Input: TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey:根据协议号和端口号注册报文
*               统计信息;结构体中的端口号usPort必须为网络序
*       Output: 成功：VOS_OK
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-03   wuling 00201943         Create
*
*******************************************************************************/
extern ULONG TCPIP_ClrPP6PktTypeStat(TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey);


extern ULONG TCPIP_ClrPP6PktStatAll(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ShowPP6PktTypeStat
* Date Created: 2014-04-03
*       Author: wuling 00201943
*  Description: 
*        Input: 
*       Output: 成功：VOS_OK
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-03   wuling 00201943         Create
*
*******************************************************************************/
extern ULONG TCPIP_ShowPP6PktTypeStat(VOID);

/*******************************************************************************
*    Func Name: TCPIP_RegLookupNdHook
* Date Created: 2014-04-29
*       Author: wuling 00201943
*  Description: 产品注册钩子，根据Mbuf中的下一跳判断是否需要查找ND表项
*        Input: pfTCPIPNeedLookupNdHook  pfHookFunc:产品注册钩子函数
*       Output: 
*       Return: VOS_OK-注册钩子函数成功
*               PP6_INPUT_PARA_NULL-注册钩子函数失败
*      Caution: 
*               IP6_NO_NEED_LOOK_UP_ND, 不需要查找ND
*               IP6_NEED_LOOK_UP_ND,     需要查找ND
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-29   wuling 00201943         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegLookupNdHook(pfTCPIPNeedLookupNdHook pfHookFunc);


#ifdef __cplusplus
}
#endif      /* end of _cplusplus        */

#endif      /* end of _PPMNG_API_H_    */

