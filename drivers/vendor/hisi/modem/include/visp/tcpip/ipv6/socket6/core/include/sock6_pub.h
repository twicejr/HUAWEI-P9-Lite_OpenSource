/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock6_pub.h
*
*  Project Code: VISP1.5
*   Module Name: Socket6
*  Date Created: 2000-4-3
*        Author: chenbin
*   Description: the macro,struct,function used by for IPV6 application
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2000-4-3    chenbin          Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*  2006-05-11  luyao            为支持ARM CPU字节对齐特性，修改结构。
*
*******************************************************************************/

#ifndef         _SOCK6_PUB_H
#define         _SOCK6_PUB_H

#ifdef    __cplusplus
extern    "C"{
#endif

#include "tcpip/socket4/core/include/sock_pub.h"
#include "tcpip/ipv6/socket6/core/include/sock6_callback.h"

extern CHAR chInet6CtlErrMap_a[];

/* socket option name for ipv6 */
/* mayun for zoneid */
#define SO_ZONEID     0x00100000          /* 为IPV6设置zoneid                 set zoneid for ipv6 */
#define SO_ZONEIDANY  0xffffffff          /* zoneid通配符值,不是可选名        wildcard value of zoneid, not the option name */


#ifndef IPPROTO_IPV6
#define IPPROTO_IPV6        41        /* IPV6 协议   IPV6 protocol */
#endif

#ifndef IPPROTO_ICMPV6
#define IPPROTO_ICMPV6      58        /* UDP 协议    UDP protocol */
#endif

#ifndef IPPROTO_DONE
#define IPPROTO_DONE        257        /*已完成协议  protocol done */
#endif

/*--------------------------------------------------------------------*/
/* 用在回调函数中,获得数据的相关信息                                   */
/* used in callback function to get information about data            */
/*--------------------------------------------------------------------*/
typedef struct tagSo6_CallbackInfo
{
    LONG lFd;
    LONG lDataLen;
    LONG lFlags;
    SOCKADDR_IN6_S stFromAddr;
    IN6ADDR_S stDstAddr;
    ULONG ulUserData;
}SO6_CALLBACKINFO_S;


/* 到下一个对齐边界的Round len
   Round len up to next alignment boundary */

#define ALIGN(p) (((LONG)(p) + (sizeof(LONG) - 1)) &~ (sizeof(LONG) - 1))

#define CMSG_ALIGN(p) (((LONG)(p) + (sizeof(LONG) - 1)) &~ (sizeof(LONG) - 1))

/*
 * TODO: RFC 2292 requires to check msg_controllen, in case that the kernel returns
 * an empty list for some reasons.
 */
#define CMSG_FIRSTHDR(mhdr)     ((cmsghdr *)(mhdr)->msg_control)


/* 给出cmsghdr的指针, 返回下一个cmsghdr的指针    given pointer to struct cmsghdr, return pointer to next cmsghdr */

/* 注意: RFC 3542中, CMSG_NXTHDR可以处理第二个参数为空(意义是: 取得第一个头)的情况
  TODO: as per RFC 3542  CMSG_NXTHDR has beend extended to handle a NULL 2nd argument
             to mean "get the first header" */
#define CMSG_NXTHDR(mhdr, cmsg) \
    (((CHAR *)(cmsg) + (cmsg)->cmsg_len + sizeof(cmsghdr) > \
        (mhdr)->msg_control + (mhdr)->msg_controllen) ? \
        (cmsghdr *)NULL : \
        (cmsghdr *)((CHAR *)(cmsg) + ALIGN((cmsg)->cmsg_len)))

#define CMSG_DATA(cmsg)  ((UCHAR *)((cmsg) + 1))

/* 长度为len的控制报文中的内容长度     Length of the contents of a control message of length len */
#define CMSG_LEN(len)    (CMSG_ALIGN(sizeof(cmsghdr)) + (len))

/* 长度为len的控制报文中的填充符长度   Length of the space taken up by a padded control message of length len */
#define CMSG_SPACE(len)  (CMSG_ALIGN(sizeof(struct cmsghdr)) + CMSG_ALIGN(len))



extern LONG inet_pton(USHORT usFamily,  const CHAR *szSrcAddr, VOID *pDstAddr);
extern CHAR *inet_ntop(USHORT usFamily, const CHAR *pSrcAddr, CHAR *szDstAddr, ULONG ulAddrLen);

#define INET_ADDRSTRLEN     16        /* 用于IPv4                   for IPv4 dotted_decimal */
#define INET6_ADDRSTRLEN    46        /* 用于IPv6的十六进制字符串   for IPv6 hex string */

#define NS_INADDRSZ         4         /* sizeof INADDR_S */
#define NS_IN6ADDRSZ        16        /* sizeof IN6ADDR_S */

#ifndef NS_INT16SZ
#define NS_INT16SZ sizeof(USHORT)
#endif


/*
 * 在IPv6中选项
 * Options for use with [gs]etsockopt at the IPV6 level.
 * First word of comment is data type; bool is stored in int.
 * 英文注释中第一个词为数据类型，bool存在int
 */
#define IPV6_SOCKOPT_RESERVED1  1  /* 保留为以后使用 reserved for future use */
#define IPV6_UNICAST_HOPS       2  /* int; IP6 跳            int; IP6 hops */
#define IPV6_MULTICAST_IF       3  /* 设置IP6多点传送  u_int; set/get IP6 multicast i/f  */
#define IPV6_MULTICAST_HOPS     4  /* 设置IP6多点传送跳步  int; set/get IP6 multicast hops */
#define IPV6_MULTICAST_LOOP     5  /* 设置IP6多点传送环回接口  u_int; set/get IP6 multicast loopback */
#define IPV6_JOIN_GROUP         6  /* 加入一组成员  ip6_mreq; join a group membership */
#define IPV6_LEAVE_GROUP        7  /* 离开一组成员  ip6_mreq; leave a group membership */
#define IPV6_PORTRANGE          8  /* 排列选择非特定接口  int; range to choose for unspec port */
#define ICMP6_FILTER            9  /* icmp6过滤  icmp6_filter; icmp6 filter */

#define IPV6_CHECKSUM           10 /* 未处理Socket校验和偏移量 int; checksum offset for raw socket */
#define IPV6_V6ONLY             11 /* AF_INET6  bool; make AF_INET6 sockets v6 only */

/*
 * 新增socket选项  new socket options introduced in RFC2292bis
 */
#define IPV6_RTHDRDSTOPTS       11 /* 在路由头前发送目的选项  ip6_dest; send dst option before rthdr */

#define IPV6_RECVPKTINFO        12 /* 接收目的地址  bool; recv if, dst addr */
#define IPV6_RECVHOPLIMIT       13 /* 接收跳步限制  bool; recv hop limit */
#define IPV6_RECVRTHDR          14 /* 接收路由头  bool; recv routing header */
#define IPV6_RECVHOPOPTS        15 /* 接收逐跳选项  bool; recv hop-by-hop option */
#define IPV6_RECVDSTOPTS        16 /* 在路由头后接收目的选项  bool; recv dst option after rthdr */
#define IPV6_RECVRTHDRDSTOPTS   17 /* 在路由头前接收目的选项  bool; recv dst option before rthdr */

#define IPV6_USE_MIN_MTU        18 /* bool; 发送最小MTU大小的包           bool; send packets at the minimum MTU */
#define IPV6_RECVPATHMTU        19 /* bool; 通告相应的MTU                 bool; notify an according MTU */

/*
 * the followings are used as cmsg type only
 */
#define IPV6_PATHMTU            20 /* 4 bytes int; MTU通告         4 bytes int; MTU notification */
#define IPV6_REACHCONF          21 /* 无数据;ND可达确认            no data; ND reachability confirm */

/*
 * more new socket options introduced in RFC2292bis
 */
#define IPV6_PKTINFO            22 /* in6_pktinfo; 发送源段地址                  in6_pktinfo; send if, src addr */
#define IPV6_HOPLIMIT           23 /* int;  发送跳数限制                         int; send hop limit */
#define IPV6_NEXTHOP            24 /* sockaddr;  下一跳地址                      sockaddr; next hop addr */
#define IPV6_HOPOPTS            25 /* ip6_hbh;   发送hop-by-hop选项              ip6_hbh; send hop-by-hop option */
#define IPV6_DSTOPTS            26 /* ip6_dest;  怎么会有相同的注释?(见146行)   ip6_dest; send dst option befor rthdr */
#define IPV6_RTHDR              27 /* ip6_rthdr; 发送路由头    ip6_rthdr; send routing header */

#define IPV6_TCLASS             28 /* int;  发送TS值           int; send traffic class value */

#define IPV6_RECVTCLASS         29 /* bool;  接收TS值          bool; recv traffic class values */

#define IPV6_DONTFRAG           30

#define IPV6_TOS                31

#define IPV6_FLOWID             32 /* 报文发送流标签值  4 bytes int; send FlowID value */

/*
 * 选项的缺省和限制值
 * Defaults and limits for options
 */
#define IPV6_DEFAULT_MULTICAST_HOPS 1    /* 缺省限制多播报文为1跳       normally limit m'casts to 1 hop  */
#define IPV6_DEFAULT_MULTICAST_LOOP 1    /* normally hear sends if a member  */


enum enum6_SOCK
{
    SOCK_CMDELEMENT6_IP,
    SOCK_CMDELEMENT6_HOST,
    SOCK_CMDELEMENT6_WORD1_20,
    SOCK_CMDELEMENT6_IPADDR,
    SOCK_CMDELEMENT6_HOSTS,
    SOCK_CMDELEMENT6_SHOWIP,
    SOCK_CMDELEMENT6_TASKID,
    SOCK_CMDELEMENT6_SOCKID,
    SOCK_CMDELEMENT6_IPDBUG,
    SOCK_CMDELEMENT6_SOCKET,
    SOCK_CMDELEMENT6_SOCKETSHOW,
    SOCK_CMDELEMENT6_SOCKTYPE,
    SOCK_CMDELEMENT6_SOCKTYPE_INTEGER1_3

};

 typedef enum tageIn6PcbField
{
    IP6_IN6PCB_NEXT = 1,
    IP6_IN6PCB_PREV,
    IP6_IN6PCB_HNEXT,
    IP6_IN6PCB_FADDR,
    IP6_IN6PCB_FPORT,
    IP6_IN6PCB_LADDR,
    IP6_IN6PCB_LPORT,
    IP6_IN6PCB_FINFO,
    IP6_IN6PCB_SOCKET,
    IP6_IN6PCB_PPCB,
    IP6_IN6PCB_FLAGS,
    IP6_IN6PCB_HOPS,
    IP6_IN6PCB_IP6_PROTO,
    IP6_IN6PCB_INPUTOPTS,
    IP6_IN6PCB_OUTPUTOPTS,
    IP6_IN6PCB_MOPTS,
    IP6_IN6PCB_ICMP6FILT,
    IP6_IN6PCB_CKSUM,
    IP6_IN6PCB_TUPLE

}eIn6PcbField;

typedef enum tageSocketField
{
    IP6_SOCKET_TYPE = 1,
    IP6_SOCKET_LINGER,
    IP6_SOCKET_OPTIONS,
    IP6_SOCKET_ZONEID,
    IP6_SOCKET_OR_STATE,
    IP6_SOCKET_AND_STATE,
    IP6_SOCKET_STATE,
    IP6_SOCKET_IPCB,
    IP6_SOCKET_ERROR,
    IP6_SOCKET_OOBMARK,
    IP6_SOCKET_SENDDATAIF_ADDR,
    IP6_SOCKET_SRC_ADDR,
    IP6_SOCKET_RECVBUF,
    IP6_SOCKET_RECVBUF_IFNET,
    IP6_SOCKET_RECVBUF_ACHARS,
    IP6_SOCKET_RECVBUF_HiWAT,
    IP6_SOCKET_RECVBUF_LOWAT,
    IP6_SOCKET_SENDBUF,
    IP6_SOCKET_SENDBUF_PMBUF,
    IP6_SOCKET_SENDBUF_FLAGS,
    IP6_SOCKET_SENDBUF_IFNET,
    IP6_SOCKET_SENDBUF_ACHARS,
    IP6_SOCKET_SENDBUF_HiWAT,
    IP6_SOCKET_SENDBUF_LOWAT,
    IP6_SOCKET_INCR_DROP_PACK,
    IP6_SOCKET_CBDATABUF,
    IP6_SOCKET_TASK_ID,
    IP6_SOCKET_PR_PSW_PROTO,
    IP6_SOCKET_FD,
    IP6_SOCKET_VRFINDEX,
    IP6_SOCKET_KEEPALIVE,
    IP6_SOCKET_TCP6_STATISTIC,
    IP6_SOCKET_KEEPIDLE
}eSocketField;

typedef struct  tagIN6PCB_TUPLE
{
    IN6ADDR_S stIn6p_faddr;    /* 外部主机表项      foreign host table entry */
    USHORT    usIn6p_fport;    /* 外部端口          foreign port */
    UCHAR     ucPadding_1[2];
    IN6ADDR_S stIn6p_laddr;    /* 本地主机表项      local host table entry */
    USHORT    usIn6p_lport;    /* 本地端口          local port */
    UCHAR     ucPadding_2[2];
}IN6PCB_TUPLE_S;


ULONG  SOCK_RegCmd6(VOID);
struct hostent *gethostbyname6(CHAR *pName, ULONG ulPolicy);
struct hostent *gethostbyaddr6(CHAR *pAddr,LONG iLen,LONG iType);


#ifndef gethostbyname6
struct hostent *vrp_gethostbyname6(CHAR *pName, ULONG ulPolicy);
#define gethostbyname6(a,b)     vrp_gethostbyname6(a,b)
#endif

#ifndef gethostbyaddr6
struct hostent *vrp_gethostbyaddr6(CHAR *pAddr,LONG iLen,LONG iType);
#define gethostbyaddr6(a,b,c)     vrp_gethostbyaddr6(a,b,c)
#endif


#define mid_Socket_PMTUSAVEOPT     (MID_SOCKET6 | 49)  /* PmtuSaveOpt() */
#define mid_SOCKET_GETHOSTBYNAME6  (MID_SOCKET6 | 50) /* gethostbyname6 */
#define mid_SOCKET_GETHOSTBYADDR6  (MID_SOCKET6 | 51) /*   gethostbyaddr6*/


/*
 * SID of IN6PCB.
 */
#define SID_IN6PCB_ALLOC                         52
#define SID_IN6PCB_IN6PCBALLOC_IP6_RECVPKTOPTS   53
#define SID_IN6PCB_IN6_SETSOCKADDR               54
#define SID_IN6PCB_IN6_SETPEERADDR               55

#define SID_IN6PCB_INIT                          56

/*
 * SID of RAWIP6.
 */
#define SID_RIP6_INPUT                           57
#define SID_RIP6_OUTPUT_PREPEND                  58
#define SID_RIP6_OUTPUT_COPY                     59
#define SID_RIP6_CTLOUTPUT                       60
#define SID_RIP6_USRREQ_ICMP6_FILTER             61
#define SID_RIP6_INPUT_NEAT                      62


/*
 * SID of UDP6.
 */
#define SID_UDP6_INPUT_NEAT                      63

/* SID of BUILD RUN socket6 related */
#define SID_BUILDRUN                             64


#define SOCK6_ERR_NOT_REGISTER              14
#define SOCK6_GET_HOST_FAIL                 15


#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif  /* _SOCK6_PUB_H */

