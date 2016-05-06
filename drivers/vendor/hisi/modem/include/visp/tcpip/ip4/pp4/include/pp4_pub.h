/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pp4_pub.h
*
*  Project Code: VISP1.5
*   Module Name: PP4  
*  Date Created: 2002-06-18
*        Author: chenshuanglong(28510)
*   Description: PP4对外提供的宏、数据结构集合
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-06-18   chenshuanglong(28510)   Create
*  2006-05-11   luyao(60000758)         为支持ARM CPU字节对齐特性，修改结构。
*  2006-11-01   zhoutong(43740)         规范性整改
*
*******************************************************************************/


#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _PP4_PUB_H_
#define _PP4_PUB_H_

#include"tcpip/ip4/pp4/include/pp4_api.h"

#define PR_SLOWHZ   2       /* 500ms定时器        2 slow timeouts per second */
#define PR_FASTHZ   5       /* 200ms定时器        5 fast timeouts per second */
/* syn D038 by x36530 20050715*/


/*
 * 端口号 < IPPORT_RESERVED 供本地高优先级的进程使用
 * Local port number conventions:
 * Ports < IPPORT_RESERVED are reserved for
 * privileged processes (e.g. root).
 *
 * 端口号 > IPPORT_RESERVED 的供服务器使用
 * Ports > IPPORT_USERRESERVED are reserved
 * for servers, not necessarily privileged.
 */


/*
 *根据最新的IANA(2006-05-31), 扩充临时端口号到 l60006581   
 *extend temporary port's range by l60006581 for lastly 'iana', 2006-05-31 
 */ 
extern USHORT g_usIpPortReservedStart;
extern USHORT g_usIpPortReservedEnd;
#define IPPORT_TRRTDEFAULT   30000

#ifndef IPPROTO_LEG_DHCP
#define IPPROTO_LEG_DHCP 0xffffffff
#endif



/* socket上多播组超过256个时按256步长扩充内存 */
#define EX_MULTILEN     256

#ifndef MACADDRLEN
#define MACADDRLEN       6       /*physical地址长度*/
#endif

/*
 * usrreq的参数是(*protosw[].pr_usrreq)(up, req, m, nam, opt) ;
 * The arguments to usrreq are:
 *  (*protosw[].pr_usrreq)(up, req, m, nam, opt);

 * 其中up是socket指针,req是这些请求之一
 * where up is a (struct socket *), req is one of these requests,
 
 * m是保存消息的可选mbuf链
 * m is a optional mbuf chain containing a message,
 
 * nam是保存地址的可选mbuf链
 * nam is an optional mbuf chain containing an address,

 * opt是socketopt指针,或者空指针
 * and opt is a pointer to a socketopt structure or nil.

 * 本协议只负责处理mbuf链
 * The protocol is responsible for disposal of the mbuf chain m,

 * 调用者需提供nam和opt使用的空间
 * the caller is responsible for any space held by nam and opt.

 * 若usrrep返回非零, 则需传递一个UNIX错误码给上层软件处理
 * A non-zero return from usrreq gives an
 * UNIX error number which should be passed to higher level software.
 */
 
#define PRU_ATTACH          0   /* 服从协议             attach protocol to up */
#define PRU_DETACH          1   /* 从协议分离           detach protocol from up */
#define PRU_BIND            2   /* 为socket绑定地址     bind socket to address */
#define PRU_LISTEN          3   /* 监听连接             listen for connection */
#define PRU_CONNECT         4   /* 建立对端的连接       establish connection to peer */
#define PRU_ACCEPT          5   /* 接受对端的连接       accept connection from peer */
#define PRU_DISCONNECT      6   /* 取消对端的连接       disconnect from peer */
#define PRU_SHUTDOWN        7   /* 不再发送数据         won't send any more data */
#define PRU_RCVD            8   /* 接收数据             have taken data; more room now */
#define PRU_SEND            9   /* 发送数据             send this data */
#define PRU_ABORT           10  /* 中止[快速断开,分离]  abort (fast DISCONNECT, DETATCH) */
#define PRU_CONTROL         11  /* 协议控制             control operations on protocol */
#define PRU_SENSE           12  /* 返回状态至m          return status into m */
#define PRU_RCVOOB          13  /* 获取band数据         retrieve out of band data */
#define PRU_SENDOOB         14  /* 发送band数据         send out of band data */
#define PRU_SOCKADDR        15  /* 获取socket地址       fetch socket's address */
#define PRU_PEERADDR        16  /* 获取对端地址         fetch peer's address */
#define PRU_CONNECT2        17  /* 连接两个socket       connect two sockets */

/* 供协议内部使用   begin for protocols internal use */
#define PRU_FASTTIMO        18  /* 200ms 超时    200ms timeout */
#define PRU_SLOWTIMO        19  /* 500ms 超时    500ms timeout */
#define PRU_PROTORCV        20  /* 下层接收      receive from below */
#define PRU_PROTOSEND       21  /* 下层分发      send to below */

#define PRU_NREQ            21
#define PRU_UNBIND          22  /* 解除socket和接口的邦定   unbind socket to interface */

/*
 * ctlinput routine的参数是: (*protosw[].pr_ctlinput)(cmd, sa, arg);
 * The arguments to the ctlinput routine are
 *  (*protosw[].pr_ctlinput)(cmd, sa, arg);
 
 * 其中cmd是以下命令之一:  sa是sockaddr指针
 * where cmd is one of the commands below, sa is a pointer to a sockaddr,

 * arg是在协议族中使用的一个caddr_t可选参数
 * and arg is an optional caddr_t argument used within a protocol family.
 */
 
#define PRC_IFDOWN              0   /* 接口转换             interface transition */
#define PRC_ROUTEDEAD           1   /* 选择新路由           select new route if possible ??? */
#define PRC_QUENCH2             3   /* DEC拥塞指示位        DEC congestion bit says slow down */
#define PRC_QUENCH              4   /* 源站被抑制           some one said to slow down */
#define PRC_MSGSIZE             5   /* 报文过大,强制丢弃    message size forced drop */
#define PRC_HOSTDEAD            6   /* 无主机响应           host appears to be down */
#define PRC_HOSTUNREACH         7   /* 不推荐(请使用PRC_UNREACH_HOST)   deprecated (use PRC_UNREACH_HOST) */
#define PRC_UNREACH_NET         8   /* 无网络路由           no route to network */
#define PRC_UNREACH_HOST        9   /* 无主机路由           no route to host */
#define PRC_UNREACH_PROTOCOL    10  /* 目的端回复错误协议   dst says bad protocol */
#define PRC_UNREACH_PORT        11  /* 错误端口号           bad port # */

/* was  PRC_UNREACH_NEEDFRAG    12     (use PRC_MSGSIZE) */
#define PRC_UNREACH_SRCFAIL     13  /* 源路由失败           source route failed */
#define PRC_REDIRECT_NET        14  /* 网络路由重定向       net routing redirect */
#define PRC_REDIRECT_HOST       15  /* 主机路由重定向       host routing redirect */
#define PRC_REDIRECT_TOSNET     16  /* 对服务类型和网络重定向  redirect for type of service & net */
#define PRC_REDIRECT_TOSHOST    17  /* 对服务类型和主机重定向  direct for tos & host */
#define PRC_TIMXCEED_INTRANS    18  /* 传输期间数据报到期     packet lifetime expired in transit */
#define PRC_TIMXCEED_REASS      19  /* reass q数据报到期      lifetime expired on reass q */
#define PRC_PARAMPROB           20  /* 头部错误             header incorrect */

/* Start: RFC4443 compliance changes */ 
#define PRC_BEYOND_SCOPE          21 /* 超出作用域          Beyond scope */ 
#define PRC_INGRESS_EGRESS_POLICY 22 /* 入口/出口规则过滤   ingress/egress policy filter */ 
#define PRC_REJECT_ROUTE          23 /* 拒绝路由配置成dst   reject route configured to dst */ 
/* End: RFC4443 compliance changes */ 
 
#define PRC_NCMDS               24

#define PRC_IS_REDIRECT(cmd)    \
    ((cmd) >= PRC_REDIRECT_NET && (cmd) <= PRC_REDIRECT_TOSHOST)

/* control code */
#define PRCO_GETOPT 0
#define PRCO_SETOPT 1
#define PRCO_NCMDS  2



/*
 * pr_flags使用的值:
 * Values for pr_flags.

 * PR_ADDR 需要PR_ATOMIC
 * PR_ADDR requires PR_ATOMIC;

 * PR_ADDR 和 PR_CONNREQUIRED 是相互独立的
 * PR_ADDR and PR_CONNREQUIRED are mutually exclusive.
 */
 
#define PR_ATOMIC       0x01        /* 只交换少量的信息    exchange atomic messages only */
#define PR_ADDR         0x02        /* 消息中包含地址      addresses given with messages */
#define PR_CONNREQUIRED 0x04        /* 协议要求连接        connection required by protocol */
#define PR_WANTRCVD     0x08        /* 需要PRU_RCVD调用    want PRU_RCVD calls */
#define PR_RIGHTS       0x10        /*                     passes capabilities */


/*
 * Internet 实现参数
 * Internet implementation parameters.
 */
#define MAXTTL      255     /* 最长生存时间(秒)        maximum time to live (seconds) */
#define IP_DEFTTL   255     /* 默认TTL由64变为255,     default ttl changed from 64 to 255, by heqiangc for D13166, 2001-11-24 */
#define IP_FRAGTTL  60      /* 分片报文的最长生存时间  time to live for frags, slowhz */
#define IP_TTLDEC   1       /* 转发时的减去值          subtracted when forwarding */

#define IP_SENDBY_LSPV_FEC  SO_SENDBY_LSPV_FEC       /* 同步D24代码  x36530 20041103 */

/*
 * 供选择的缺省值和限制值
 * Defaults and limits for options
 */
#define IP_DEFAULT_MULTICAST_TTL  1 /* 缺省限制多播报文为1跳                      normally limit m'casts to 1 hop  */
#define IP_DEFAULT_MULTICAST_LOOP 1 /* 监听成员发送                               normally hear sends if a member  */
#define IP_MAX_MEMBERSHIPS        4096  /* 每个socket必须保存在一个one mbuf中     per socket; must fit in one mbuf */

#define IP_MAX_SOURCE       16    /* 在socket中,每个多组的源端限制为16    the source number of per multi-group in socket limits to 16*/

#define IP_MSS              576     /* 缺省的最大段长    default maximum segment size */


#define IP_RAWOUTPUT        0x2     /* 存在raw ip头     raw ip header exists */


#define EUNREACH            31
/* FIB */
#define IP_FIB_BLACKHOLE    1
#define IP_ENETUNREACH      2
#define IP_FIB_REJECT2      3
#define IP_LOCAL_FORWARDING    (0)    /* 表示该报文走本地转发 */
#define MPLS_L3VPN_FORWARDING (4)     /* 表示报文是VPN 报文，走隧道转发 */
/* End: VISP Support multi-instance project */

/************************************************************************************/
/* syn D038 by x36530 20050715*/
#define   DISP_HEAD               VRP_YES 
#define   DISP_NONE               VRP_NO

#define IPVLAN_VLANID_MASK  0xfff
#define IPGETPRECEDENCE(pIp) ((pIp->ip_chTOS>>5)&0x07)

/*Added by wangbin, for DTS2015102607923 ，解决发送IP报文频繁使用TCPIP_Rand_Safe导致性能恶化问题, 2015/10/24 */
#define IPID_UPDATECOUNT     0x400

/*
 * 不带选项的,Internet 头结构
 * Structure of an internet header, naked of options.

 * 我们要求ip_len和ip_off是short型的,而不是u_short
 * We declare ip_len and ip_off to be short, rather than u_short

 * 因为无符号型的比较能 , 容易出错
 * pragmatically since otherwise unsigned comparisons can result
 * against negative integers quite easily, and fail in subtle ways.
 */
struct  tagINADDR;

/* IP_S已经挪到pp4_api.h */

/*IPSTAT_S已经挪到pp4_api.h*/


typedef struct tagIpGlobalMibStat{
    ULONG ulInReceives;
    ULONG ulInHdrErrors;
    ULONG ulInAddrErrors;
    ULONG ulForwDatagrams;
    ULONG ulInUnknownProtos;
    ULONG ulInDiscards;
    ULONG ulInDelivers;
    ULONG ulOutRequests;
    ULONG ulOutDiscards;
    ULONG ulOutNoRoutes;
    ULONG ulReasmTimeout;
    ULONG ulReasmReqds;
    ULONG ulReasmOKs;
    ULONG ulReasmFails;
    ULONG ulFragOKs;
    ULONG ulFragFails;
    ULONG ulFragCreates;
    ULONG ulRoutingdiscards;
}IP_PP4_GLOBALMIB_STAT_S;


/*---------------------------------------------------------------*/
/* for IP and TCP reassemble                                     */
/*---------------------------------------------------------------*/
struct tagQUEUE;
typedef struct tagQUEUE
{
    struct tagQUEUE    *pNext;
    struct tagQUEUE    *pPrev;
}QUEUE_S;


/**********************************************************************
* ip multicast source list struct used by socket
**********************************************************************/
typedef struct tagIPMREQ_SOURCELIST
{
    ULONG ulSourceAddr;                               /* 接收到的多播数据包中的地址   address that is in the multicast packet recieved*/
    struct tagIPMREQ_SOURCELIST * pstNextSourceAddr;  /* 指向下一个源地址               point to next source address*/
}IPMREQ_SOURCELIST_S;
/*
 * Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP.
 */
typedef struct tagIPMREQ
{
    struct  tagINADDR imr_stMultiAddr;              /* 组的IP 多播地址     IP multicast address of group */
    ULONG   imr_ulIndexIf;                          /* 接口的本地地址      local address of interface */
    ULONG   imr_ulFilterMode;                       /* 多播组过滤模式,只能是IGMP_REPORT_MODE_IN 或 IGMP_REPORT_MODE_EX
                                                     * multicast group filter mode, only be IGMP_REPORT_MODE_IN or IGMP_REPORT_MODE_EX*/
    ULONG   imr_ulSourceCount;                      /* 在socket中的多组源数目 the number of source on the multi-group in socket*/
    struct  tagIPMREQ_SOURCELIST * pstSourcelist;   /* 源地址链表指针    point to source address list*/
}IPMREQ_S, *PIPMREQ_S;

/**********************************************************************
* ip multicast option struct
**********************************************************************/
struct tagIPMREQ;
typedef struct tagIPMOPTIONS
{
    ULONG   imo_ulIndexIf;      /* 外发的多播ifp        ifp for outgoing multicasts */
    UCHAR   imo_bTTL;           /* 外发的多播TTL        TTL for outgoing multicasts */
    UCHAR   imo_bLoop;          /* 1 =>如果有成员收到   1 => hear sends if a member       */
    USHORT  imo_usVIF;          /* outgoing vif no             */

    USHORT  imo_usNumMemberships;       /* socket成员数 no. memberships this socket */
    UCHAR   ucPadding_1[2];
    struct  tagIPMREQ *imo_pMembership_a; /* modifed structure imo_pMembership_a by mayun for D13667 2002-01-10 */
    USHORT  imo_usMaxMemberships;
    UCHAR   ucPadding_2[2]; 
}IPMOPTIONS_S, *PIPMOPTIONS_S;

extern LONG     nMaxLinkHdr;            /* 最大的链路层头             largest link-level header */
extern LONG     nMaxProtoHdr;           /* 最大的协议头               largest protocol header */
extern LONG     g_lMaxHdr;              /* 最大的链路和协议头         largest link+protocol header */

/*****************************************************************************
 * 外部接口定义. 这些接口可以被其它模块直接调用, 或则使用组件中的接口方法
 * extern interface definition. these interface can be called by other module*
 * directly. also can use component interface method.                        *
 *****************************************************************************/
struct tagROUTE;

/* 包处理接口, 使不在VISP的模块能直接调用, 为保持兼容性,将他们保留在这里
 * interface for packet process, for modules not in VISP to call directly */
/*  these are kept here for compatibility                                  */

extern ULONG IP_Input(struct tagMBuf * pstMBuf);
extern ULONG IP_IF_Output( struct tagMBuf *pstMBuf, ULONG ulPmtu );
extern ULONG IP_Output(struct tagMBuf *pstMBuf, struct tagMBuf *pstMOpt, struct tagROUTE *pstRo, 
                       LONG lFlags, struct tagIPMOPTIONS *pstIpMo );
extern ULONG IP_Output_ForInternal(struct tagMBuf *pstMBuf, struct tagMBuf *pstMOpt, struct tagROUTE *pstRo, 
                                   LONG lFlags, struct tagIPMOPTIONS *pstIpMo );
extern MBUF_S *IP_SrcRoute();
extern VOID IP_StrIpOptions(register struct tagMBuf *, struct tagMBuf *);
extern USHORT IN_Cksum(struct tagMBuf *pstMBuf, LONG lLen);
extern USHORT Ip_Fast_Cksum(USHORT * pusWord);
/* 多播  multicast */
extern LONG IP_SetMOptions(LONG lOptName, struct tagIPMOPTIONS **ppstIpMopP, struct tagMBuf *pstMBuf);
extern LONG IP_GetMOptions(LONG lOptName, struct tagIPMOPTIONS *pstIpMo, struct tagMBuf **ppstMBufP);
extern void IP_FreeMOptions(struct tagIPMOPTIONS *pstIpMo);

extern VOID IP_PP4_DebugACLFilter(MBUF_S *pMBuf, ULONG *pulMatch);

extern USHORT IP_Get_IpId(VOID);


#endif  /* _PP4_PUB_H_  */

#ifdef  __cplusplus
}
#endif

