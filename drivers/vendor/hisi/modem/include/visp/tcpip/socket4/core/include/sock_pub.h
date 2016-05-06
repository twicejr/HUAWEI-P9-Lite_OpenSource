/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock_pub.h
*
*  Project Code: VISP1.5
*   Module Name: socket4
*  Date Created: 2006-4-29
*        Author: chenbin
*   Description: the macro,struct,function used by application
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2000-04-03   chenbin         created
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*  2006-05-11   luyao           为支持ARM CPU字节对齐特性，修改结构。
*  2007-09-20   z62474            同步A82D20312
*******************************************************************************/
#ifndef  _SOCK_PUB_H
#define  _SOCK_PUB_H

#ifdef   __cplusplus
extern   "C"{
#endif

#include "tcpip/socket4/core/include/macro.h"
#include "tcpip/socket4/core/include/sock_host.h"


/***********************************************************************
* the macros for application
***********************************************************************/
#define AF_MPLS         28
#ifndef AF_UNSPEC
#define AF_UNSPEC       0                 /* unspecified */
#endif

#ifndef AF_LOCAL
#define AF_LOCAL        1                   /* local to host (pipes, portals) */
#endif

#ifndef AF_UNIX
#define AF_UNIX         AF_LOCAL        /* backward compatibility */
#endif

#ifndef AF_INET
#define AF_INET         2                       /* internetwork: UDP, TCP, etc. */
#endif

#ifndef AF_IMPLINK
#define AF_IMPLINK      3                   /* arpanet imp addresses */
#endif

#ifndef AF_PUP
#define AF_PUP          4                       /* pup protocols: e.g. BSP */
#endif

#ifndef AF_CHAOS
#define AF_CHAOS        5                   /* mit CHAOS protocols */
#endif

#ifndef AF_NS
#define AF_NS           6                       /* XEROX NS protocols */
#endif

#ifndef OSI_ISIS
#define OSI_ISIS           7                    /* FOR IS-IS ADDED BY ZHAOBIAO. */
#endif
#ifndef AF_ISO
#define AF_ISO          OSI_ISIS           /* ISO protocols */
#endif

#ifndef AF_OSI
#define AF_OSI          AF_ISO            /*ISO*/
#endif

#ifndef AF_ECMA
#define AF_ECMA         8                   /* european computer manufacturers */
#endif

#ifndef AF_DATAKIT
#define AF_DATAKIT      9                /* datakit protocols */
#endif

#ifndef AF_CCITT
#define AF_CCITT        10                /* CCITT protocols, X.25 etc */
#endif

#ifndef AF_SNA
#define AF_SNA          11                  /* IBM SNA */
#endif

#ifndef AF_DECnet
#define AF_DECnet       12               /* DECnet */
#endif

#ifndef AF_DLI
#define AF_DLI          13                   /* DEC Direct data link interface */
#endif

#ifndef AF_LAT
#define AF_LAT          14                  /* LAT */
#endif

#ifndef AF_HYLINK
#define AF_HYLINK       15              /* NSC Hyperchannel */
#endif

#ifndef AF_APPLETALK
#define AF_APPLETALK    16         /* Apple Talk */
#endif

#ifndef AF_ROUTE
#define AF_ROUTE        17             /* Internal Routing Protocol */
#endif

#ifndef AF_LINK
#define AF_LINK         18                 /* Link layer interface */
#endif

#ifndef pseudo_AF_XTP
#define pseudo_AF_XTP   19         /* eXpress Transfer Protocol (no AF) */
#endif

#ifndef AF_COIP
#define AF_COIP         20              /* connection-oriented IP, aka ST II */
#endif

#ifndef AF_CNT
#define AF_CNT          21              /* Computer Network Technology */
#endif

#ifndef pseudo_AF_RTIP
#define pseudo_AF_RTIP  22      /* Help Identify RTIP packets */
#endif

#ifndef AF_IPX
#define AF_IPX          23               /* Novell Internet Protocol */
#endif

#ifndef AF_SIP
#define AF_SIP          24               /* Simple Internet Protocol */
#endif

#ifndef pseudo_AF_PIP
#define pseudo_AF_PIP   25       /* Help Identify PIP packets */
#endif

#ifndef AF_BRIDGE
#define AF_BRIDGE       26         /* bridge flag*/
#endif

#ifndef AF_KEY
#define AF_KEY          27            /* IPSEC and IKE */
#endif

#ifndef AF_MPLS
#define AF_MPLS         28
#endif

#ifndef AF_INET6
#define AF_INET6        29             /* added by mayun for IPv6 */
#endif

#ifndef GRE_FR
#define GRE_FR          30             /* moved out from fr_def.h, Terry, 2003/09/13 */
#endif

#ifndef AF_MAX
#define AF_MAX          28
#endif

#ifndef INADDR_ANY
#define    INADDR_ANY            (ULONG)0x00000000L
#endif

#define MAX_FREE_PORT_NUM_RECENTLY 1024
/*
 * 协议族，现在和地址族一样    Protocol families, same as address families for now.
 */
#define PF_UNSPEC       AF_UNSPEC       /* 未指定  */
#define PF_LOCAL        AF_LOCAL        /* 本地    */
#define PF_UNIX         PF_LOCAL        /* 向后兼容   backward compatibility */
#define PF_INET         AF_INET         /* 地址族类型  */
#define PF_IMPLINK      AF_IMPLINK      /* 阿帕网地址    */
#define PF_PUP          AF_PUP          /* PUP协议    */
#define PF_CHAOS        AF_CHAOS        /* CHAOS协议   */
#define PF_NS           AF_NS           /* NS协议    */
#define PF_ISO          AF_ISO          /* ISO协议    */
#define PF_OSI          AF_ISO          /* ISO协议    */
#define PF_ECMA         AF_ECMA         /* 欧洲电脑制造商  */
#define PF_DATAKIT      AF_DATAKIT      /* datakit协议   */
#define PF_CCITT        AF_CCITT        /* CCITT协议    */
#define PF_SNA          AF_SNA          /* IBM SNA    */
#define PF_DECnet       AF_DECnet       /* DECnet   */
#define PF_DLI          AF_DLI          /* 直接数据链路接口 */
#define PF_LAT          AF_LAT          /* LAT */
#define PF_HYLINK       AF_HYLINK       /* NSC Hyperchannel */
#define PF_APPLETALK    AF_APPLETALK    /* apple会话 */
#define PF_ROUTE        AF_ROUTE        /* 内部路由协议 */
#define PF_LINK         AF_LINK         /* 链路层接口  */
#define PF_XTP          pseudo_AF_XTP     /* 仅仅是协议族，不是地址族  really just proto family, no AF */
#define PF_COIP         AF_COIP          /*  connection-oriented IP, aka ST II */
#define PF_CNT          AF_CNT           /*  计算机网络技术 */
#define PF_SIP          AF_SIP           /*  简单网路协议 */
#define PF_IPX          AF_IPX           /* 同AF_NS格式一样    same format as AF_NS */
#define PF_RTIP         pseudo_AF_FTIP   /* 同AF_INET格式一样  same format as AF_INET */
#define PF_PIP          pseudo_AF_PIP    /* Help Identify PIP packets */
#define PF_KEY          AF_KEY           /* IPSEC and IKE */

#define PF_MAX          AF_MAX

#define    CTL_NET        4

#define NET_RT_DUMP        1             /* 堆放; 可能限制在a.f       dump; may limit to a.f. */
#define NET_RT_FLAGS       2             /* 标志，例如 RESOLVING      by flags, e.g. RESOLVING */
#define NET_RT_IFLIST      3             /* 查找接口列表              survey interface list */
#define NET_RT_MAXID    4

/*socket type*/
#define SOCK_STREAM     1               /* 流套接口       stream socket */
#define SOCK_DGRAM      2               /* 数据套接口     datagram socket */
#define SOCK_RAW        3               /* raw协议接口    raw-protocol interface */
#define SOCK_RDM        4               /* 可靠传输消息   reliably-delivered message */
#define SOCK_SEQPACKET  5               /* 序列化报文流   sequenced packet stream */

#define MSG_OOB         0x1             /* 处理超出带宽的数据     process out-of-band data */
#define MSG_PEEK        0x2             /* 监听收到的消息         peek at incoming message */
#define MSG_DONTROUTE   0x4             /* 不使用路由表发送       send without using routing tables */
#define MSG_EOR         0x8             /* 数据完成记录           data completes record */
#define MSG_TRUNC       0x10            /* 数据在传输前丢弃       data discarded before delivery */
#define MSG_CTRUNC      0x20            /* 在传输前控制数据丢失   control data lost before delivery */
#define MSG_WAITALL     0x40            /* 等待请求或出错         wait for full request or error */
#define MSG_DONTWAIT    0x80            /* 该消息不能被阻塞       this message should be nonblocking */

/*---------------------------------------------------------------------*/
/* Maximum queue length specifiable by listen()                        */
/*---------------------------------------------------------------------*/
/* 修改原因:5的队列规格不能满足LTE产品需求,扩充为64,但为了不影响其他产品使用保留原有宏值SOMAXCONN */
#define SONEWMAXCONN    0x80    /* maximum queue length */
#define SOMAXCONN       0x5     /* queue length is 5*/

#define SOL_SOCKET      0xffff

/*  Option flags per-socket.*/
#define SO_DEBUG         0x00000001          /* turn on debugging info recording */
#define SO_ACCEPTCONN    0x00000002          /* socket has had listen() */
#define SO_REUSEADDR     0x00000004          /* allow local address reuse */
#define SO_KEEPALIVE     0x00000008          /* keep connections alive */
#define SO_DONTROUTE     0x00000010          /* just use interface addresses */
#define SO_BROADCAST     0x00000020          /* permit sending of broadcast msgs */
#define SO_USELOOPBACK   0x00000040          /* bypass hardware when possible */
#define SO_LINGER        0x00000080          /* linger on close if data present */
#define SO_OOBINLINE     0x00000100          /* leave received OOB data in line */
#define SO_REUSEPORT     0x00000200          /* allow local address & port reuse */
#define SO_SENDDATAIF    0x00000400          /* allow send data accross the specifed interface*/
#define SO_UDPCHECKSUM   0x00000800          /* set/unset udp output to calculate check sum */
#define SO_NSYNDROMESVR  0x00001000          /* set no parallel bgp server */
#define SO_SNDBYDSTMAC   0x00002000          /* set snd mac for dhcp relay */
#define SO_SETSRCADDR    0x00004000         /* set source address of output packet */
#define SO_SENDVPNID     0x00008000          /* VPN use this option */

/* set outif and nexthop of output packet mayun 2002-12-17 */
/* Now this option only support Raw Socket, but it can set in UDP/TCP successfully. */
/*If this option set in UDP socket, the socket will cann't send packet .*/
/*IF this option set in TCP socket, the option is invalide*/
#define SO_SENDBY_IF_NEXTHOP 0x00010000

#define SO_SETKEEPALIVE 0x00020000
/* end of mayun */
#define SO_SEQPACKET  0x00040000         /* sequnce tcp packet */

/*set the vlanid of the socket add by gao 03/12/31 BYDD01389*/
#define SO_SETVLANID   0x00100000

#define SO_SENDBY_LSPV_FEC  0x00200000

#define SO_HEADCACHE  0x00400000

#define SO_SENDDATAIF_DONTSETTTL    0x00800000      /* allow send data accross the specifed interface,but not set TTL*/

#define SO_SENDDATAIF_WITHROUTE 0x01000000  /*支持tracerouter指定出接口发送报文*/

#define SO_GETKEEPALIVE         SO_SETKEEPALIVE /* 获取keepalive配置，与SO_SETKEEPALIVE重用 */
#define SO_SETKEEPIDLE          0x02000000     /* 设置keepidle配置 */
#define SO_GETKEEPIDLE          SO_SETKEEPIDLE  /* 获取keepidle配置，与SO_SETKEEPIDLE重用 */
/* End of likaikun */

#define VRP_SOCKET_LISTEN 1

#define SO_SETPEER_ADDR_PORT      0x04000000


/* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
/* 原来是(FILENUM + 1)，把它更改成下面值，如果创建VRF的个数等于FILENUM + 1,则会存在问题，目前PTN最大支持VPN个数为512 ,支持预配置*/
#define SO_VRFINDEX_ANY (0xFFFFFFFF)
/* End:VISP1.7C03 VRF wangchengyang , 2009-02-06 */

/*  Additional options, not kept in so_options. */
#define SO_SNDBUF       0x1001          /* send buffer size */
#define SO_RCVBUF       0x1002          /* receive buffer size */
#define SO_SNDLOWAT     0x1003          /* send low-water mark */
#define SO_RCVLOWAT     0x1004          /* receive low-water mark */
#define SO_SNDTIMEO     0x1005          /* send timeout */
#define SO_RCVTIMEO     0x1006          /* receive timeout */
#define SO_ERROR        0x1007          /* get error status and clear */
#define SO_TYPE         0x1008          /* get socket type */
#define SO_RCVVLANID    0x1009        /* get vlan info from mbuf */
#define SO_RCVPVCID     0x1010        /* get pvc info from mbuf */

/*---------------------------------------------------------------------*/
/* Protocols Supported by pNA+                                         */
/*---------------------------------------------------------------------*/
#ifndef ICMP
#define ICMP            0x1         /* ICMP protocol */
#endif

#ifndef IGMP
#define IGMP            0x2         /* IGMP protocol */
#endif

#ifndef TCP
#define TCP             0x6         /* TCP protocol */
#endif

#ifndef UDP
#define UDP             0x11        /* UDP protocol */
#endif

#ifndef IPPROTO_IP
#define IPPROTO_IP      0x0         /* IP protocol */
#endif

#ifndef IPPROTO_ICMP
#define IPPROTO_ICMP    0x1         /* ICMP protocol */
#endif

#ifndef IPPROTO_IGMP
#define IPPROTO_IGMP    0x2         /* IGMP protocol */
#endif

#ifndef IPPROTO_IPIP
#define IPPROTO_IPIP      0x4         /* IP in IP protocol */
#endif

#ifndef IPPROTO_TCP
#define IPPROTO_TCP     0x6         /* TCP protocol */
#endif

#ifndef IPPROTO_UDP
#define IPPROTO_UDP     0x11        /* UDP protocol */
#endif

#ifndef IPPROTO_RAWSCTP
#define IPPROTO_RAWSCTP     132        /* SCTP protocol */
#endif

/*---------------------------------------------------------------------*/
/* Options for use with getsockopt at the IP level.                 */
/*---------------------------------------------------------------------*/
#define    IP_OPTIONS             1      /* set/get IP per-packet options */
#define    IP_HDRINCL             2   /* long; header is included with data */
#define    IP_TOS                 3   /* long; IP type of service and preced. */
#define    IP_TTL                 4   /* long; IP time to live */
#define    IP_RECVOPTS            5   /* 接收所有IP选项  bool; receive all IP opts w/dgram */
#define    IP_RECVRETOPTS         6   /* 接收IP选项来应答  bool; receive IP opts for response */
#define    IP_RECVDSTADDR         7   /* 接收IP目的地址  bool; receive IP dst addr w/dgram */
#define    IP_RETOPTS             8   /* 设置IP选项  ip_opts; set/get IP options */
#define    IP_MULTICAST_IF        9   /* 设置IP多点传输i/f  u_char; set/get IP multicast i/f  */
#define    IP_MULTICAST_TTL      10   /* 设置IP多电传输生存时间  u_char; set/get IP multicast ttl */
#define    IP_MULTICAST_LOOP     11   /* 设置IP多点传输环回接口  u_char; set/get IP multicast loopback*/
#define    IP_ADD_MEMBERSHIP     12   /* 增加一个IP组成员  ip_mreq; add an IP group membership */
#define    IP_DROP_MEMBERSHIP    13   /* 丢弃一个IP组成员  ip_mreq; drop an IP group membership */
#define    IP_MULTICAST_INTF     14   /* 设置IP多点传输i/f  u_char; set/get IP multicast i/f */
#define    IP_ADD_MEMBERSHIP_INTF  15 /* 增加一个IP组  ip_mreq_intf; add an IP group */
                                      /* 成员数目给出临界数  membership given interface number */
#define    IP_DROP_MEMBERSHIP_INTF    16 /* 丢弃一个IP组  ip_mreq_intf; drop an IP group */
                                   /* 成员数目给出临界数  membership given interface number */

#define    IP_ROUT_ALERT         17   /* 设置IP选项  ip_opts; set/get IP options mayun 2002-12-17 */
#define    IP_TOS_TOTAL          18   /* IP服务类型和优先级  long; IP type of service and preced. */
#define    IP_BLOCK_SOURCE            19   /* 资源表中的资源阻塞  block source from sourcelist*/
#define    IP_UNBLOCK_SOURCE          20   /* 资源表中的资源除去阻塞  unblock source from sourcelist*/
#define    IP_ADD_SOURCE_MEMBERSHIP   21   /* add source to sourcelist or join multi_group with source*/
#define    IP_DROP_SOURCE_MEMBERSHIP  22   /* drop source from sourcelist or leave group with deleting the last source*/
#define    IP_ONLYRECVMULTICAST       23   /* for ospf socket only receive multicast ip pkt*/

/*---------------------------------------------------------------------*/
/* Options for use with getsockopt at the TCP level.                */
/*---------------------------------------------------------------------*/
#define TCP_NODELAY         1       /* set/get tcp nodelay option */
#define TCP_MAXSEG          2       /* set/get tcp max segment size */
#define TCP_KEEPALIVE_IDLE  3       /* set/get TCP Keepalive timer value */
#define TCP_KEEPALIVE_CNT   4       /* set/get TCP Keepalive probe count */
#define TCP_KEEPALIVE_INTVL 5       /* set/get TCP Keepalive probing interval*/
#define TCP_MSL             6       /* set/get TCP Maximum Segment Lifetime */
#define TCP_BINDFOREIGNADDR    7

/* TCP with MD5 authentication, zhangfeng, 2002,07,20 */
#define TCP_SETPASSWORD        8       /* set/get tcp md5 authentication P***W*** */
#define TCP_SETPASSWORD_EX        10       /* set/get tcp md5 authentication P***W*** */
/* TCP with MD5 authentication, zhangfeng, 2002,07,20 */

#define TCP_ROUTINEBACKUP  9        /* set/get routine backup interval of tcp socket buffer */

/*---------------------------------------------------------------------*/
/* error and message id for asynsock                                   */
/*---------------------------------------------------------------------*/
#define        ASYN_MESSAGE        0X12345678

#define        SE_QUEUEERR    0x0080

#define        EQUEEMPTY   -1
#define        ENOTASYN    -2
#define        ENOTIME     -3
#define        ENORECORD   -4
#define        ENOASYNSOCK -5
#define        EUDPNODATA  -6
#define        EMBUFEMPTY  -7
#define        EQUEUEERROR -8
#define        EQUEUEFULL  -9
#define        EISASYNC    -10
#define        EISBACKCALL -11
#define        ETIMEWAIT   -15
#define        ENOFIOMAXMBUF    -16
#define        ENOFIOTCPDROPALL -17
#define        ENOFIOSENDONLY   -18
#define        ESENDDATAIF      -19
#define        ENORTENTRY       -20

/*---------------------------------------------------------------------*/
/* macros for ioctl called by application                              */
/*---------------------------------------------------------------------*/
#define FIOGETOWN       0x4004667C      /* Get owner of the socket */
/* added by mayun 获得发送缓冲区空闲空间大小 */
#define FIOSBFREE       0x4004667B      /* Get bytes of socket send buffer's free space */
/* end of mayun */
#define FIOREAD         0x4004667F      /* Get bytes in socket read buffer */
#define SIOCATMARK      0x40047307      /* Get OOB data in line */
#define FIOSETOWN       0x8004667C      /* Set owner of the socket */
#define FIOASYNC        0x8004667D      /* Set/Unset socket to receive */                                      /* Asyncronous signal */
#define FIONBIO         0x8004667E      /* Set/Unset socket non-blocking */
#define FIORECALL       0x8004668D      /* Set/Unset socket to call back */
#define    FSENDDATAIF        0x80046684      /* Set/Unset socket send data out from a ifnet */

#define FNEEDBACKUP     0x8004668E      /* Set/Unset socket to backup */       /* added by mayun for socket ha */

#define F_GETFL         1               /* get file status flags */
#define F_SETFL         2               /* set file status flags */
#define F_GETOWN        3               /* get SIGIO/SIGURG proc/pgrp */

#define FASYNC          0x04            /* kernel/compat */
#define FNONBLOCK       0x08            /* kernel */
#define FNDELAY         0x08            /* compat */

#define FCNTLFLAGS      (FASYNC|FNONBLOCK)

/*---------------------------------------------------------------------*/
/* macro for select()                                                  */
/*---------------------------------------------------------------------*/

/*Added by zhoushisong202096, 支持大规格SOCKET, 2013/11/7 */
#ifdef TCPIP_NOVRP_HUGE_SOCKET
#define FD_SETSIZE      128*1024
#else
/* added by tangcongfeng for D01009 */
#define FD_SETSIZE      3072
#endif

#define FDSETLEN        (((FD_SETSIZE) + (NFDBITS)) /(NFDBITS))    /* fd_set lenth, xxx long */
/* ended of tangcongfeng for D01009 */

#define    NFDBITS        0x20
#define    NBBY        8
#ifndef FD_SET

#define FD_SET(n, p)    {\
            if ((n) > 0 ){\
            ((p)->fds_bits[(n)/NFDBITS] |= \
                        (((ULONG) 0x00000001) << ((n) % NFDBITS))); \
                    }\
                    }
#endif


#define FD_CLR(n, p)    ((p)->fds_bits[(n)/NFDBITS] &= \
                       ~(((ULONG) 0x00000001) << ((n) % NFDBITS)))
#define FD_ISSET(n, p)  ((p)->fds_bits[(n)/NFDBITS] & \
                        (((ULONG) 0x00000001) << ((n) % NFDBITS)))

#define FD_ZERO(p)  { \
                        LONG xxx; \
                        for( xxx = 0; xxx<FDSETLEN; xxx++ ) \
                        { \
                            ((p)->fds_bits[xxx] = 0); \
                        } \
                    }

/*---------------------------------------------------------------------*/
/* little and big byte order convert                                   */
/*---------------------------------------------------------------------*/
/*
#ifdef _INTEL_
    #define htonl(addr)     ( (((ULONG)(addr) & 0x000000FF)<<24) | \
                             (((ULONG)(addr) & 0x0000FF00)<<8)  | \
                             (((ULONG)(addr) & 0x00FF0000)>>8)  | \
                             (((ULONG)(addr) & 0xFF000000)>>24))
    #define ntohl(addr)     htonl(addr)
    #define htons(addr)     ( (((USHORT)(addr) & 0x000000FF)<<8)  | \
                             (((USHORT)(addr) & 0x0000FF00)>>8))
    #define ntohs(addr)     htons(addr)

#else

    #define htonl(a)       ((ULONG)(a))
    #define ntohl(a)       ((ULONG)(a))
    #define htons(a)       ((USHORT)(a))
    #define ntohs(a)       ((USHORT)(a))
#endif
*/
#ifndef ntohl
#define ntohl      VOS_NTOHL
#endif
#ifndef ntohs
#define ntohs      VOS_NTOHS
#endif
#ifndef htonl
#define htonl      VOS_HTONL
#endif
#ifndef htons
#define htons      VOS_HTONS
#endif


#define HC_EVENT_FIBREFRESH   0    /*FIB 更新事件*/
#define HC_EVENT_ARP          1    /*ARP删除或更新事件*/
/* add by l57500,06/12/07.for support ipv6 hc */
#define HC_EVENT_ND           2   /* ipv6 nd删除或更新 */
#define HC_EVENT_MAC          3   /* 本机接口MAC变化 */
#define HC_EVENT_FIB6REFRESH  4   /* FIB6 更新事件 */
/* Added by z43740 to Support IPv6 HC for ND Host */
#define HC_EVENT_ND_HOST      5   /* IPv6 ND Host: Update One Dst */
#define HC_EVENT_ND_HOST_ALL  6   /* IPv6 ND Host: Update All Dst */

/***********************************************************************
* end of the macros for application
***********************************************************************/


/***********************************************************************
* the struct for application
***********************************************************************/

/*---------------------------------------------------------------------*/
/* Structure used for manipulating linger option.                      */
/*---------------------------------------------------------------------*/
struct linger
{
    LONG l_onoff;        /* option on/off */
    LONG l_linger;       /* linger time */
};
#ifdef  sockaddr
#undef sockaddr
#endif

struct sockaddr
{
  USHORT sa_family;
  CHAR  sa_data[14];
};

/*internet address*/
typedef struct in_addr
{
    ULONG s_addr;       /* address of the socket */
}in_addr;

/*---------------------------------------------------------------------*/
/* Structure used for manipulating address in bind,sendto and so on */
/*---------------------------------------------------------------------*/
typedef struct sockaddr_in
{
    unsigned char sin_len;      /* zy */
    unsigned char sin_family;   /* must be AF_INET */
    unsigned short sin_port;    /* 16-bit port number */
    struct in_addr sin_addr;    /* 32-bit address */
    CHAR sin_zero[8];           /* must be 0 */
}sockaddr_in;


/*---------------------------------------------------------------------*/
/* Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP.    */
/*---------------------------------------------------------------------*/
typedef struct ip_mreq
{
    in_addr   imr_mcastaddr;  /* IP multicast address of group */
    ULONG     imr_ifindex;    /* local address of interface */
}ip_mreq;

/*--------------------------------------------------------------------------*/
/* Argument structure for IP_ADD_MEMBERSHIP_INTF and IP_DROP_MEMBERSHIP_INTF*/
/*--------------------------------------------------------------------------*/
typedef struct ip_mreq_intf
{
    in_addr imrif_mcastaddr; /* IP multicast address of group */
    LONG    imrif_ifno;      /* local interface number */
}ip_mreq_intf;

/*--------------------------------------------------------------------------*/
/* Argument structure for IP_ADD_SOURCE_MEMBERSHIP, IP_DROP_SOURCE_MEMBERSHIP */
/* IP_BLOCK_SOURCE AND IP_UNBLOCK_SOURCE                                    */
/*--------------------------------------------------------------------------*/
typedef struct ip_mreq_source
{
    in_addr imr_mcastaddr;  /*  IP multicast address of group  */
    in_addr imr_msrcaddr;   /*  address of source for group */
    ULONG   imr_ifindex;    /*  local address of interface   */
}ip_mreq_source;


/*---------------------------------------------------------------------*/
/* following two used for recvmsg and sendmsg functions                */
/*---------------------------------------------------------------------*/
typedef struct iovec
{
    CHAR *iov_base;     /* base address */
    LONG iov_len;       /* buffer length */
}iovec;

/*message to  output */
typedef struct msghdr
{
    CHAR  *msg_name;        /* optional address */
    SHORT msg_namelen;      /* size of address */
    UCHAR ucPadding_1[2];
    iovec *msg_iov;         /* scatter/gather array */
    SHORT msg_iovlen;       /* # elements in msg_iov */
    UCHAR ucPadding_2[2];
    CHAR  *msg_control;     /* access rights */
    SHORT msg_controllen;   /* length of the rights buffer */
    SHORT msg_flags;
}msghdr;


typedef struct cmsghdr
{
    SHORT cmsg_len;         /* data byte count, including hdr */
    SHORT cmsg_level;       /* originating protocol */
    SHORT cmsg_type;        /* protocol-specific type */
    CHAR  cmsg_data[2];     /* assign byte */
}cmsghdr;
/*---------------------------------------------------------------------*/
/* following two used for select                                       */
/* this is defined in select.h as FD_SET_S, the two must be altered at */
/* same time                                                           */
/*---------------------------------------------------------------------*/
typedef struct fd_set
{
    LONG fds_bits[FDSETLEN];  /* we support for 3072 socket in a task */
} fd_set;

struct timeval
{
    LONG  tv_sec;       /* no. of seconds */
    LONG  tv_usec;      /* no. of micro seconds */
};


/*  请注意　hostent　结构在用与返回IPv4和IPv6主机信息时的不一致, 与BSD原始实现也不一致
    h_addr_list　成员在返回IPv4主机地址时存储的是ASCII码形式的字符串，而在返回IPv6主机地址
    时返回的则是　二进制形式存储的IPv6地址，即结构　IN6ADDR_S
    Please note at this .     x43050 2006-6-16   */
struct  hostent
{
    CHAR    h_name[IP_HOSTNAME_LEN + 1];         /* official name of host */ /* 10->21 by mayun 20010608 */
    UCHAR   ucPadding[4-((IP_HOSTNAME_LEN + 1)%4)];
    CHAR    h_aliases[4][IP_HOSTNAME_LEN + 1];      /* alias list */
    SHORT   h_addrtype;         /* host address type */
    SHORT   h_length;           /* length of address */
    CHAR    h_addr_list[4][20]; /* list of addresses */
#define h_addr  h_addr_list[0]      /* address, for backward compat */
};

/*---------------------------------------------------------------------*/
/* struct used by application to send data direct out of a interface   */
/* this is defined in sockcom.h also, the two must be altered at same time */
/*---------------------------------------------------------------------*/
typedef struct senddataif
{
    ULONG  ulIfIndex;
    ULONG  ulSrcAddr;
}senddataif;

/*---------------------------------------------------------------------*/
/* struct used by application to set socket to be a asyn socket        */
/* this is defined in sockcom.h also, the two must be altered at same time */
/*---------------------------------------------------------------------*/
typedef struct  asynsockset
{
    ULONG  ulQueueID;
    ULONG  ulPointer;
    ULONG  ulWakeTaskID;
}asynsockset;


/*--------------------------------------------------------------------*/
/* used in callback function to get information about data            */
/*--------------------------------------------------------------------*/
typedef struct callbackinfo
{
    LONG iFd;
    LONG iDataLen;
    LONG iFlags;
    sockaddr_in stFromAddr;
    in_addr stDstAddr;
    ULONG ulUserData;
}callbackinfo;

#define SE_ASYNC   0x0020
/*--------------------------------------------------------------------*/
/* set socket to callback when there is data input                    */
/*--------------------------------------------------------------------*/
typedef struct  recallsockset
{
    ULONG  (*so_pfCallBack)( CHAR *, callbackinfo * );
    CHAR  *pszDataBuf;
    ULONG  ulBufLen;
    ULONG ulUserData;
}recallsockset;

/*---------------------------------------------------------------------*/
/* struct contain message which is send to application's queue by      */
/* AsynWakeUp(), the application get this message to determind what to do */
/* this is defined in asynsock.h also, the two must be altered at same time */
/*---------------------------------------------------------------------*/
typedef struct asynsockmsg
{
    ULONG ulMsgType;    /*表明此消息是异步SOCKET发送的消息,数值为ASYN_MESSAGE*/
    ULONG ulPointer;    /*原先是src分配的buffer, 现表明是src指定的pointer */
                            /*绑定于异步SOCKET的一个数值*/
    LONG  iError;

#define SUCCEEDED       0
#define FAILED          1

    /* Modefied by fengjing209023 ASYNMSG_S.FD.type.defect 将FD由16位改为24位,涉及接口变更，需知会产品 */
    /* 注意: VOS_Que_Write函数写的消息最大长度为16字节(32bit环境)，故该结构体定义不能超过16字节*/
    unsigned usFd:24;
    unsigned usEventType:8;
    /* Modefied end */    
    
#define ASYN_READ       1
#define ASYN_WRITE      2
#define ASYN_CONNECT    3
#define ASYN_CLOSE      4
#define ASYN_ACCEPT     5
#define ASYN_PEERCLOSE  6
}asynsockmsg;



/* added by mayun for socket HA */
#define EV_SOCKHA_BATCHMSG     0x00000001
#define EV_SOCKHA_REALTIMEMSG  0x00000002
#define EV_SOCKHA_ALL          0xffffffff

/******************************备份数据结构定义************************************/
typedef struct tagSockBackupMsg    /*发送的备份消息*/
{
    ULONG ulMsgType;                 /*消息类型*/
#define SOCK_BAKALL_MSG     0
#define SOCK_CLR_MSG        1
    ULONG ulTaskId;                  /*Socket所在任务的ID*/
    LONG  lSockNum;                  /*要备份或清除的Socket号*/
    ULONG ulSockType;                /*socket type:ipv6 or ipv4*/
}SockBackupMsg_S;

typedef struct tagSOCK_SEARCH_IN_S
{
    struct sockaddr_in *pstLaddr; /* 32-bit Local address + local port*/
    struct sockaddr_in *pstFaddr; /* 32-bit Remote address + Remote port*/
    ULONG ulVrfIndex;                /*vrf index*/
    UCHAR ucPro;               /*  8-bit Protocal */
    UCHAR ucRes[7];            /* 56-bit Reserved */
} SOCK_SEARCH_IN_S;

typedef struct tagSOCK_SEARCH_OUT_S
{
    ULONG ulSockId;          /* socket id */
    ULONG ulTcpState;        /* TCP连接状态 */
} SOCK_SEARCH_OUT_S;

typedef struct  tagSOCKPQNODEINFO
{
    ULONG ulVrfIndex;                /*vrf index*/
    ULONG ulTcpState;                /*TCP 状态*/
    struct sockaddr_in *pstLaddr;/* 32-bit Local address + local port*/
    struct sockaddr_in *pstFaddr;/* 32-bit Remote address + Remote port*/
} SOCKPQNODEINFO_S;

typedef struct  tagSOCKPQINFO
{
    ULONG   ulConfiguredQLen;   /* 配置的监听队列长度 */
    ULONG   ulActualQLen;       /* 目前监听队列的总长度(Q0或Q，分别查询) */
    ULONG   ulBacklogDrop;      /* 因超过Backlog而丢弃的socket个数 */
    ULONG   ulTimeODrop;        /* 因超时而丢弃的socket个数 */
} SOCKPQINFO_S;

/* 本段开启端口时回调通知产品 */
typedef struct tagTCPIP_SOCKNOTIFYINFO
{
    ULONG   ulSockId;          /* socket id */    
    ULONG   ulTaskId;          /* 使用本socket的TASK ID */ 
    ULONG   ulSrcIp;           /* 源地址，主机序 */
    USHORT  usSrcPort;         /* 源端口号，主机序 */
    USHORT  usSockState;       /* socket类型，监听socket或者其他 */
    ULONG   ulSockType;        /* 套接字类型，SOCK_STREAM(1),SOCK_DGRAM(2)*/
}TCPIP_SOCKNOTIFYINFO_S;

typedef ULONG (*TCPIP_SOCK_PORT_NOTIFY_HOOK_FUNC)(TCPIP_SOCKNOTIFYINFO_S *pstData);

extern TCPIP_SOCK_PORT_NOTIFY_HOOK_FUNC  g_pfSockPortNotifyHookFunc;

typedef struct tagTCPIP_SOCK_GLOBLE
{
    USHORT usAutoPortStart; /* 动态分配端口号起始值,1~65535，默认值为49152*/
    USHORT usAutoPortEnd;   /* 动态分配端口号结束值,1~65535，默认值为65535*/
}TCPIP_SOCK_GLOBLE_S;

typedef struct tagSOCK_QOS_INFO_S
{
    ULONG ulRexmtPercent;   /* 消息重传比例，百分比 */
    ULONG ulAvgRtt;         /* 消息平均时延 */
    ULONG ulAvgRttWarp;     /* 消息平均时延偏差 */
} SOCK_QOS_INFO_S;

/***********************************************************************
* funtions used by application
***********************************************************************/
extern LONG socket(LONG, LONG, LONG);
extern LONG bind(LONG, struct sockaddr_in *,LONG);
extern LONG unbind(LONG, struct sockaddr_in *,LONG);
extern LONG listen(LONG, LONG);
extern LONG accept(LONG, struct sockaddr_in *, LONG *);
extern LONG connect(LONG,struct sockaddr_in *,LONG);
extern LONG read(LONG,CHAR *,LONG);
extern LONG readv(LONG,struct iovec *,LONG);
extern LONG recv(LONG,CHAR *,LONG,LONG);
extern LONG recvfrom(LONG,CHAR *,LONG ,LONG,struct sockaddr_in *,LONG *);
extern LONG recvmsg(LONG,struct msghdr *,LONG);
extern LONG write(LONG,CHAR *,LONG);
extern LONG writev(LONG,struct iovec *,LONG);
extern LONG send(LONG,CHAR *,LONG,LONG);
extern LONG sendto(LONG,CHAR *,LONG ,LONG,struct sockaddr_in *,LONG);
extern LONG sendmsg(LONG,struct msghdr *,LONG);
extern LONG select(LONG,struct fd_set *,struct fd_set *,struct fd_set *,struct timeval *);
extern LONG shutdown(LONG,LONG);
extern LONG close(LONG );
extern LONG close_s();
extern LONG fcntl(LONG,LONG,ULONG *);
extern LONG ioctl(LONG, ULONG ,CHAR *);

extern LONG setsockopt(LONG ,LONG, LONG, CHAR *, LONG);
extern LONG getsockopt(LONG,LONG,LONG,CHAR *,LONG *);
extern LONG getsockname(LONG,struct sockaddr_in *,LONG *);
extern LONG Sock_Rls_Tcb(VOID);


extern LONG  GetTcpState(LONG );
extern LONG  GetOobState(LONG );

extern LONG  CopySocket(ULONG , ULONG , LONG, LONG);

extern LONG  sysctl(LONG *,ULONG,VOID *,ULONG *,VOID *,ULONG);
extern LONG  gethostname(CHAR *,LONG);
extern struct hostent *gethostbyaddr(CHAR *,LONG ,LONG);
extern struct hostent *gethostbyname(CHAR *);
extern LONG inet_pton4(const CHAR * , VOID * );
extern CHAR* inet_ntop4(const CHAR * , CHAR * , ULONG );

extern LONG  getrcvifindex( LONG iFd, ULONG *pulIfIndex );
extern ULONG getsrcbydst(ULONG ulDstAddr);

extern LONG   IsAsynSocket(LONG);

extern LONG getrcvvlaninfo(LONG iFd, USHORT *pusVlanInfo);


#ifndef socket
LONG vrp_socket(LONG, LONG, LONG);
#define socket(a,b,c)    vrp_socket(a,b,c)
#endif

#ifndef    bind
LONG vrp_bind(LONG, struct sockaddr_in *,LONG);
#define bind(a,b,c)    vrp_bind(a,b,c)
#endif

#ifndef    listen
LONG vrp_listen(LONG, LONG);
#define listen(a,b)    vrp_listen(a,b)
#endif

#ifndef    accept
LONG vrp_accept(LONG, struct sockaddr_in *, LONG *);
#define    accept(a,b,c)    vrp_accept(a,b,c)
#endif

#ifndef    connect
LONG vrp_connect(LONG,struct sockaddr_in *,LONG);
#define    connect(a,b,c)    vrp_connect(a,b,c)
#endif

#ifndef read
LONG vrp_read(LONG,CHAR *,LONG);
#define read(a,b,c)        vrp_read(a,b,c)
#endif

#ifndef readv
LONG vrp_readv(LONG,struct iovec *,LONG);
#define readv(a,b,c)    vrp_readv(a,b,c)
#endif

#ifndef recv
LONG vrp_recv(LONG,CHAR *,LONG,LONG);
#define recv(a,b,c,d)    vrp_recv(a,b,c,d)
#endif

#ifndef recvfrom
LONG vrp_recvfrom(LONG,CHAR *,LONG ,LONG,struct sockaddr_in *,LONG *);
#define    recvfrom(a,b,c,d,e,f)    vrp_recvfrom(a,b,c,d,e,f)
#endif

#ifndef    recvmsg
LONG vrp_recvmsg(LONG,struct msghdr *,LONG);
#define    recvmsg(a,b,c)    vrp_recvmsg(a,b,c)
#endif

#ifndef write
LONG vrp_write(LONG,CHAR *,LONG);
#define  write(a,b,c)    vrp_write(a,b,c)
#endif

#ifndef writev
LONG vrp_writev(LONG,struct iovec *,LONG);
#define  writev(a,b,c)    vrp_writev(a,b,c)
#endif

#ifndef    send
LONG vrp_send(LONG,CHAR *,LONG,LONG);
#define    send(a,b,c,d) vrp_send(a,b,c,d)
#endif

#ifndef sendto
LONG vrp_sendto(LONG,CHAR *,LONG ,LONG,struct sockaddr_in *,LONG);
#define sendto(a,b,c,d,e,f)    vrp_sendto(a,b,c,d,e,f)
#endif

#ifndef    sendmsg
LONG vrp_sendmsg(LONG,struct msghdr *,LONG);
#define sendmsg(a,b,c)    vrp_sendmsg(a,b,c)
#endif


#ifndef shutdown
LONG vrp_shutdown(LONG,LONG);
#define    shutdown(a,b)    vrp_shutdown(a,b)
#endif

#ifndef fcntl
LONG vrp_fcntl(LONG,LONG,ULONG *);
#define fcntl(a,b,c)    vrp_fcntl(a,b,c)
#endif

#ifndef select
LONG vrp_select(LONG,struct fd_set *,struct fd_set *,struct fd_set *,struct
timeval *);
#define select(a,b,c,d,e)    vrp_select(a,b,c,d,e)
#endif

#ifndef ioctl
LONG vrp_ioctl(LONG, ULONG ,CHAR *);
#define    ioctl(a,b,c)    vrp_ioctl(a,b,c)
#endif

#ifndef close
LONG vrp_close(LONG );
#define close(a)    vrp_close(a)
#endif

#ifndef    setsockopt
LONG vrp_setsockopt(LONG ,LONG, LONG, CHAR *, LONG);
#define    setsockopt(a,b,c,d,e)    vrp_setsockopt(a,b,c,d,e)
#endif

#ifndef    getsockopt
LONG vrp_getsockopt(LONG,LONG,LONG,CHAR *,LONG *);
#define    getsockopt(a,b,c,d,e)    vrp_getsockopt(a,b,c,d,e)
#endif

#ifndef    getsockname
LONG vrp_getsockname(LONG,struct sockaddr_in *,LONG *);
#define    getsockname(a,b,c)    vrp_getsockname(a,b,c)
#endif

#ifndef    sysctl
LONG vrp_sysctl(LONG *,ULONG,VOID *,ULONG *,VOID *,ULONG);
#define    sysctl(a,b,c,d,e,f)    vrp_sysctl(a,b,c,d,e,f)
#endif

#ifndef    gethostname
LONG vrp_gethostname(CHAR *,LONG);
#define gethostname(a,b)    vrp_gethostname(a,b)
#endif

#ifndef    getpeername
LONG vrp_getpeername(LONG ,struct sockaddr_in *,LONG *);
#define getpeername(a,b,c)    vrp_getpeername(a,b,c)
#endif

/*x36317 Trace item No: D00396 2004-8-18*/
#ifndef inet_pton
LONG vrp_inet_pton(USHORT usFamily,  const CHAR *szSrcAddr, VOID *pDstAddr);
#define inet_pton(a,b,c)     vrp_inet_pton(a,b,c)
#endif

#ifndef inet_ntop
CHAR * vrp_inet_ntop(USHORT usFamily, const CHAR *pSrcAddr, CHAR *szDstAddr, ULONG ulAddrLen);
#define inet_ntop(a,b,c,d)     vrp_inet_ntop(a,b,c,d)
#endif

#ifndef CopySocket
LONG vrp_CopySocket(ULONG, ULONG, LONG, LONG);
#define CopySocket(a,b,c,d)     vrp_CopySocket(a,b,c,d)
#endif

#ifndef getrcvifindex
LONG vrp_getrcvifindex(LONG,ULONG *);
#define getrcvifindex(a,b)   vrp_getrcvifindex(a,b)
#endif

#ifndef getsrcbydst
ULONG vrp_getsrcbydst(ULONG);
#define getsrcbydst(a) vrp_getsrcbydst(a)
#endif

#ifndef unbind
LONG vrp_unbind(LONG, struct sockaddr_in *, LONG);
#define unbind(a,b,c)   vrp_unbind(a,b,c)
#endif

#ifndef close_s
LONG vrp_close_s();
#define close_s()   vrp_close_s()
#endif

#ifndef Sock_Rls_Tcb
LONG vrp_Sock_Rls_Tcb();
#define Sock_Rls_Tcb()   vrp_Sock_Rls_Tcb()
#endif

#ifndef GetTcpState
LONG vrp_GetTcpState(LONG);
#define GetTcpState(a)   vrp_GetTcpState(a)
#endif

#ifndef GetOobState
LONG vrp_GetOobState(LONG);
#define GetOobState(a)   vrp_GetOobState(a)
#endif

#ifndef IsAsynSocket
LONG vrp_IsAsynSocket(LONG);
#define IsAsynSocket(a)   vrp_IsAsynSocket(a)
#endif

#ifndef gethostbyaddr
struct hostent *vrp_gethostbyaddr(CHAR *,LONG ,LONG);
#define gethostbyaddr(a,b,c)   vrp_gethostbyaddr(a,b,c)
#endif

#ifndef gethostbyname
struct hostent *vrp_gethostbyname(CHAR *);
#define gethostbyname(a)   vrp_gethostbyname(a)
#endif
/*end.20050513*/

/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-05 */
#ifndef getrcvvpnid
LONG vrp_getrcvvpnid(LONG , ULONG *);
#define getrcvvpnid(a,b)   vrp_getrcvvpnid(a,b)
#endif
/* End:VISP1.7C03 VRF wangchengyang,2009-02-05 */

/* 当前该接口仅为内部接口,不是对外接口 */
#ifndef getrcvvlaninfo
LONG vrp_getrcvvlaninfo(LONG iFd, USHORT* pusVlanInfo);
#define getrcvvlaninfo(a,b)   vrp_getrcvvlaninfo(a,b)
#endif

#define SOCK4_ERR_BUF_SIZE 100 /**???*/
#define SOCK4_DEBUG_INFO_BUF_SIZE 64 /**debug infomation buffer*/

/*the length of task length*/
#define TASK_NAME_LEN   5

/* error code for del host */
#define ADD_HOST_ERR_TOO_MUCH_HOSTS         8
#define ADD_HOST_ERR_TOO_MUCH_IP_ADDR       9
#define ADD_HOST_ERR_ALREADY_ADDED          10
#define ADD_HOST_ERR_INVALID_HOST_NAME      11
#define ADD_HOST_ERR_INVALID_IP_ADDR        12
#define ADD_HOST_ERR_ISSWITCHINGORSMOOTHING 13 /* Added for SOCKET HA */

#define DEL_HOST_ERR_INVALID_NAME_OR_ADDR   16
#define DEL_HOST_ERR_MNAY_IP_ADDR           17
#define DEL_HOST_ERR_ISSWITCHINGORSMOOTHING 18 /* Added for SOCKET HA */

/* error code for socket api */
#define SOCK_SOCKETNOTFOUND                 19 /* 没有找到socket */
#define SOCK_INVALIDPRO                     20 /* 非法的协议号 */
#define SOCK_QZEROEMPTY                     21 /* Q0队列中没有节点 */
#define SOCK_QZEROEND                       22 /* 已到队列末端 */
#define SOCK_INVALIDHANDLE                  23 /* 句柄无效 */
#define SOCK_QEMPTY                         24 /* Q队列没有节点 */
#define SOCK_QEND                           25 /* 已到队列末端 */
#define SOCK_TCBNOTFOUND                    26 /* 无法获取Tcb */
#define SOCK_INPUTNULL                      27 /* 输入为空 */
#define SOCK_TCPCBNULL                      28 /* TCP控制块为空 */
#define SOCK_INVALIDFAMILY                  29 /* FAMILY不合法 */
#define SOCK_TCP6NOTINIT                    30 /* TCP6未初始化 */
#define SOCK_IN6PCBNULL                     31 /* INPCB为空 */

typedef ULONG (*IN6PCB_GETSOCKTCPSTATE)(SOCK_SEARCH_IN_S * pstSearchIn, SOCK_SEARCH_OUT_S * pstSearchOut);
typedef ULONG (*INP6CB_GETSOCKQOSINFO)(VOID *pData, SOCK_QOS_INFO_S *pstQosInfo);
typedef ULONG (*IN6PCB_GETSOCKNODEINFO)(VOID *pData, SOCKPQNODEINFO_S *pstSockPQNodeInfo);

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */


#endif
