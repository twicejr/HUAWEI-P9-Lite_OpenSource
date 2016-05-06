/*************************************************************************
 *
 *              Copyright 2006, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 *
 *-----------------------------------------------------------------------*
 *
 *                         VISP_IR_SOCKET.H
 *
 *  Project Code: VISP1.6
 *   Module Name: MBUF
 *  Date Created: 2006/11/16
 *        Author: liuyong 57500
 *   Description:   这个头文件内容是从VISP SOCKET相关的各个头文件抽取IR需要的宏和结构构成，
 *                  在后续开发和维护时，需要关注同VISP保持同步!
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *
 ************************************************************************/
#ifndef _VISP_IR_SOCKET_H_
#define _VISP_IR_SOCKET_H_

#ifdef    __cplusplus
extern "C"{
#endif


/****************    from sock6_pub.h    ************/
#define SO_ZONEID     0x00100000          /* set zoneid for ipv6 */
#define SO_ZONEIDANY  0xffffffff          /* wildcard value of zoneid, not the option name */


#ifndef IPPROTO_IPV6
#define IPPROTO_IPV6        41        /* IPV6 protocol */
#endif

#ifndef IPPROTO_ICMPV6
#define IPPROTO_ICMPV6      58        /* UDP protocol */
#endif

#ifndef IPPROTO_DONE
#define IPPROTO_DONE        257        /* protocol done */
#endif

#define INET6_ADDRSTRLEN 46        /* for IPv6 hex string */

#ifndef AF_INET6
#define AF_INET6        29             /* added by mayun for IPv6 */
#endif

#define IPV6_USE_MIN_MTU        18 /* bool; send packets at the minimum MTU */

#define IPV6_CHECKSUM           10 /* int; checksum offset for raw socket */

/* Round len up to next alignment boundary */
#define ALIGN(p) (((ULONG)(p) + (sizeof(LONG) - 1)) &~ (sizeof(LONG) - 1))

#define CMSG_ALIGN(p) (((ULONG)(p) + (sizeof(LONG) - 1)) &~ (sizeof(LONG) - 1))

/*
 * TODO: RFC 2292 requires to check msg_controllen, in case that the kernel returns
 * an empty list for some reasons.
 */
#define CMSG_FIRSTHDR(mhdr)     ((cmsghdr *)(mhdr)->msg_control)


/* given pointer to struct cmsghdr, return pointer to next cmsghdr */
/* TODO: as per RFC 3542  CMSG_NXTHDR has beend extended to handle a NULL 2nd argument
             to mean "get the first header" */
#define CMSG_NXTHDR(mhdr, cmsg) \
    (((CHAR *)(cmsg) + (cmsg)->cmsg_len + sizeof(cmsghdr) > \
        (mhdr)->msg_control + (mhdr)->msg_controllen) ? \
        (cmsghdr *)NULL : \
        (cmsghdr *)((CHAR *)(cmsg) + ALIGN((cmsg)->cmsg_len)))

#define CMSG_DATA(cmsg)  ((UCHAR *)((cmsg) + 1))

/* Length of the contents of a control message of length len */
#define CMSG_LEN(len)    (CMSG_ALIGN(sizeof(cmsghdr)) + (len))

/* Length of the space taken up by a padded control message of length len */
#define CMSG_SPACE(len)  (CMSG_ALIGN(sizeof(struct cmsghdr)) + CMSG_ALIGN(len))


#define IPV6_MULTICAST_IF       3  /* u_int; set/get IP6 multicast i/f  */
#define IPV6_JOIN_GROUP         6  /* ip6_mreq; join a group membership */
#define IPV6_LEAVE_GROUP        7  /* ip6_mreq; leave a group membership */
#define IPV6_RECVPKTINFO        12 /* bool; recv if, dst addr */
#define IPV6_PKTINFO            22 /* in6_pktinfo; send if, src addr */
#define IPV6_HOPLIMIT           23 /* int, send hop limit */
#define IPV6_NEXTHOP            24 /* sockaddr, next hop address */
#define IPV6_TCLASS             28 /* int;  发送TS值           int; send traffic class value */

/* Modefied by wuling for DTS2014101506425 
   性能优化，取16与替代原来的32位与，解决低16位变化对HASH索引值没影响的问题 */

#define HASHFUNC6_ADDR6(pstAddr) \
    (((pstAddr)->s6_addr8[0])^((pstAddr)->s6_addr8[1])^((pstAddr)->s6_addr8[2])^((pstAddr)->s6_addr8[3])^ \
        ((pstAddr)->s6_addr8[4])^((pstAddr)->s6_addr8[5])^((pstAddr)->s6_addr8[6])^((pstAddr)->s6_addr8[7])^ \
        ((pstAddr)->s6_addr8[8])^((pstAddr)->s6_addr8[9])^((pstAddr)->s6_addr8[10])^((pstAddr)->s6_addr8[11])^ \
        ((pstAddr)->s6_addr8[12])^((pstAddr)->s6_addr8[13])^((pstAddr)->s6_addr8[14])^((pstAddr)->s6_addr8[15]))

#define HASHFUNC6_SECOND(usFPort, pstFAddr) \
    ((HASHFUNC6_ADDR6(pstFAddr) + (usFPort) )&(HASH_SECONDLEVEL_MASK))

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

typedef struct tagIN6PCB_CALLBACUP_SET_S
{
    ULONG    (*pfIP6_IN6PCB_SetParameter)(UINTPTR, enum tageIn6PcbField, VOID*);
    ULONG    (*pfIP6_IN6PCB_GetParameter)(UINTPTR, enum tageIn6PcbField, VOID *);
    ULONG    (*pfIP6_IN6PCB_GetHashFHT) (USHORT, UINTPTR *);
    ULONG    (*pfIP6_IN6PCB_GetIN6PCBFromSecondHash)(UINTPTR ,USHORT , UINTPTR *);
    VOID     *(*pfIN6PCB_GetNextPCB) (VOID *,VOID **);
    LONG     (*pfIN6PCB_Init) (UCHAR, UINTPTR *, UINTPTR *);
    LONG     (*pfIN6PCB_Alloc)(UINTPTR, UINTPTR , UINTPTR);
    LONG     (*pfIN6PCB_Bind)(UINTPTR, struct tagSOCKADDR_IN6 *);
    LONG     (*pfIN6PCB_Connect)(UINTPTR, struct tagSOCKADDR_IN6 *);
    LONG     (*pfIN6PCB_Detach)(UINTPTR);
    LONG     (*pfIN6PCB_Disconnect)(UINTPTR);
    LONG     (*pfIN6PCB_Notify)(UINTPTR,struct tagSOCKADDR*,ULONG,struct
                         tagIN6Addr*,ULONG,LONG,VOID (*)(UINTPTR,LONG));
    LONG     (*pfIN6PCB_SetPeerAddr)(UINTPTR, struct tagMBuf*);
    LONG     (*pfIN6PCB_SetSockAddr)(UINTPTR,struct tagMBuf *);
    UINTPTR  (*pfIN6PCB_HashSearch)(UINTPTR,struct tagIN6Addr*,USHORT,struct
                                    tagIN6Addr*, USHORT,LONG, ULONG, ULONG);
    LONG     (*pfIN6PCB_SearchSecond)(UINTPTR,struct tagIN6Addr*, USHORT, struct
                                      tagIN6Addr*, ULONG, ULONG);
    ULONG    (*pfIN6PCB_BindFAddress)(UINTPTR, IN6ADDR_S *);
}IN6PCB_CALLBACUP_SET_S;

typedef struct tagPMTU_CALLBACKUP_SET_S
{
   LONG   (*pfIP6_Socket_PMTU_Notify)(IN6ADDR_S *, ULONG,ULONG, LONG, ULONG, UCHAR);
   ULONG  (*pfIP6_Socket_Search)(UCHAR, IN6ADDR_S *, USHORT, IN6ADDR_S *, USHORT,  LONG *, ULONG *, ULONG);
   LONG   (*pfIP6_Socket_Notification_deletion)(LONG,ULONG, IN6ADDR_S *, ULONG);
   void   (*pfIP6_Socket_Notification_delete_all)();
}PMTU_CALLBACKUP_SET_S;


/***************** from in6_pcb.h   ***************/
#define IN6P_MINMTU        0x20000000 /* use minimum MTU */

/*
 * ulIn6p_flags of IN6PCB define
 */
#define IN6P_IPV6_V6ONLY    0x008000 /* restrict AF_INET6 socket for v6 */

#define IN6P_DONTFRAG        0x001000 /* do not fragment packets*/

#define IN6P_RECVPKTINFO    0x010000 /* receive IP6 dst and I/F */
#define IN6P_RECVHOPLIMIT   0x020000 /* receive hoplimit */
#define IN6P_RECVHOPOPTS    0x040000 /* receive hop-by-hop options */
#define IN6P_RECVDSTOPTS    0x080000 /* receive dst options after rthdr */
#define IN6P_RECVRTHDR      0x100000 /* receive routing header */
#define IN6P_RECVRTHDRDSTOPTS   0x200000 /* receive dstoptions before rthdr */
#define IN6P_RECVTCLASS          0x400000 /* receive traffic class value */
#define IN6P_RECVAUTOFLOWLABEL 0x800000 /* attach flowlabel automatically */

#define IN6P_HIGHPORT       0x1000000 /* user wants "high" port binding */
#define IN6P_LOWPORT        0x2000000 /* user wants "low" port binding */
#define IN6P_ANONPORT       0x4000000 /* port chosen for user */

#define IN6P_MINMTU        0x20000000 /* use minimum MTU */
#define IN6P_RECVRFC2292    0x40000000 /* used RFC2292 API on the socket */
#define IN6P_RECVPATHMTU    0x80000000 /* receive path MTU */

#define IN6P_CONTROLOPTS    (IN6P_RECVPKTINFO|IN6P_RECVHOPLIMIT|IN6P_RECVHOPOPTS|\
                 IN6P_RECVDSTOPTS|IN6P_RECVRTHDR|IN6P_RECVRTHDRDSTOPTS|\
                 IN6P_RECVTCLASS|IN6P_RECVAUTOFLOWLABEL|IN6P_RECVRFC2292|\
                 IN6P_RECVPATHMTU)

#define IN6PLOOKUP_WILDCARD 1
#define IN6PLOOKUP_SETLOCAL  2


/***************** from sock_pub.h   ***************/
#ifndef AF_INET
#define AF_INET         2                       /* internetwork: UDP, TCP, etc. */
#endif

#ifndef AF_KEY
#define AF_KEY          27            /* IPSEC and IKE */
#endif

#define PF_KEY          AF_KEY


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
#define IPPROTO_IPIP    0x4         /* IP in IP protocol */
#endif

#ifndef IPPROTO_TCP
#define IPPROTO_TCP     0x6         /* TCP protocol */
#endif

#ifndef IPPROTO_UDP
#define IPPROTO_UDP     0x11        /* UDP protocol */
#endif

#ifndef INADDR_ANY
#define INADDR_ANY             (ULONG)0x00000000L
#endif


#define HC_EVENT_ND             2   /* for support ipv6 headcache */
/* Added by z43740 to Support IPv6 HC for ND Host */
#define HC_EVENT_ND_HOST        5   /* IPv6 ND Host: Update One Dst */
#define HC_EVENT_ND_HOST_ALL    6   /* IPv6 ND Host: Update All Dst */

#define SOL_SOCKET      0xffff

/*---------------------------------------------------------------------*/
/* Options for use with getsockopt at the IP level.                 */
/*---------------------------------------------------------------------*/
#define IP_OPTIONS              1   /* set/get IP per-packet options */
#define IP_HDRINCL              2   /* long; header is included with data */
#define IP_TOS                  3   /* long; IP type of service and preced. */
#define IP_TTL                  4   /* long; IP time to live */
#define IP_RECVOPTS             5   /*********************** 收到所有的IP选项 bool; receive all IP opts w/dgram ***********************/
#define IP_RECVRETOPTS          6   /*********************** 回应收到的IP选项 bool; receive IP opts for response ***********************/
#define IP_RECVDSTADDR          7   /*********************** 接收IP目的地址 bool; receive IP dst addr w/dgram ***********************/
#define IP_RETOPTS              8   /*********************** 设置IP选项 ip_opts; set/get IP options ***********************/
#define IP_MULTICAST_IF         9   /*********************** 设置IP多点传送 u_char; set/get IP multicast i/f  ***********************/
#define IP_MULTICAST_TTL        10  /*********************** 设置IP多点传送生存时间 u_char; set/get IP multicast ttl ***********************/
#define IP_MULTICAST_LOOP       11  /*********************** 设置IP多播环回 u_char; set/get IP multicast loopback ***********************/
#define IP_ADD_MEMBERSHIP       12  /*********************** 增加一个 IP组成员 ip_mreq; add an IP group membership ***********************/
#define IP_DROP_MEMBERSHIP      13  /*********************** 丢弃一个IP组成员 ip_mreq; drop an IP group membership ***********************/
#define IP_MULTICAST_INTF       14  /* u_char; set/get IP multicast i/f */
#define IP_ADD_MEMBERSHIP_INTF  15  /* ip_mreq_intf; add an IP group */
                                    /* membership given interface number */
#define IP_DROP_MEMBERSHIP_INTF 16  /* ip_mreq_intf; drop an IP group */
                                    /* membership given interface number */

#define IP_ROUT_ALERT           17  /* ip_opts; set/get IP options mayun 2002-12-17 */
#define IP_TOS_TOTAL            18  /* long; IP type of service and preced. */

#define FIOREAD         0x4004667F  /* Get bytes in socket read buffer */

/*  Option flags per-socket.*/
#define SO_DEBUG         0x00000001          /* turn on debugging info recording */
#define SO_ACCEPTCONN   0x00000002          /* socket has had listen() */
#define SO_REUSEADDR    0x00000004          /* allow local address reuse */
#define SO_KEEPALIVE     0x00000008          /* keep connections alive */
#define SO_DONTROUTE    0x00000010          /* just use interface addresses */
#define SO_BROADCAST    0x00000020          /* permit sending of broadcast msgs */
#define SO_USELOOPBACK  0x00000040          /* bypass hardware when possible */
#define SO_LINGER        0x00000080          /* linger on close if data present */
#define SO_OOBINLINE     0x00000100          /* leave received OOB data in line */
#define SO_REUSEPORT     0x00000200          /* allow local address & port reuse */
#define SO_SENDDATAIF    0x00000400          /* allow send data accross the specifed interface*/
#define SO_UDPCHECKSUM  0x00000800          /* set/unset udp output to calculate check sum */
#define SO_NSYNDROMESVR 0x00001000          /* set no parallel bgp server */
#define SO_SNDBYDSTMAC  0x00002000          /* set snd mac for dhcp relay */
#define SO_SETSRCADDR    0x00004000         /* set source address of output packet */
#define SO_SENDVPNID     0x00008000          /* VPN use this option */
#define SO_SENDBY_IF_NEXTHOP 0x00010000     /* set outif and nexthop of output packet mayun 2002-12-17 */

#define SO_SETKEEPALIVE 0x00020000
/* end of mayun */
#define SO_SEQPACKET  0x00040000         /* sequnce tcp packet */
/*set the vlanid of the socket add by gao 03/12/31 BYDD01389*/
#define SO_SETVLANID   0x00100000

#define SO_SENDBY_LSPV_FEC  0x00200000

#define SO_HEADCACHE  0x00400000

#define SO_SENDDATAIF_WITHROUTE 0x01000000  /*支持tracerouter指定出接口发送报文*/

#define SO_GETKEEPALIVE         SO_SETKEEPALIVE /* 获取keepalive配置，与SO_SETKEEPALIVE重用 */
#define SO_SETKEEPIDLE          0x02000000     /* 设置keepidle配置 */
#define SO_GETKEEPIDLE          SO_SETKEEPIDLE  /* 获取keepidle配置，与SO_SETKEEPIDLE重用 */
/* End of likaikun */

/* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
/* 原来是(FILENUM + 1)，把它更改成下面值，如果创建VRF的个数等于FILENUM + 1,则会存在问题，目前PTN最大支持VPN个数为512 ,支持预配置*/
#define SO_VRFINDEX_ANY (0xFFFFFFFF)
/* End:VISP1.7C03 VRF wangchengyang , 2009-02-06 */

/* Added for IKE/IPSEC to increase pfkey socket recv buffer size */
/*  Additional options, not kept in so_options. */
#define SO_SNDBUF       0x1001          /* send buffer size */
#define SO_RCVBUF       0x1002          /* receive buffer size */
#define SO_SNDLOWAT     0x1003          /* send low-water mark */
#define SO_RCVLOWAT     0x1004          /* receive low-water mark */
#define SO_SNDTIMEO     0x1005          /* send timeout */
#define SO_RCVTIMEO     0x1006          /* receive timeout */
#define SO_ERROR        0x1007          /* get error status and clear */
#define SO_TYPE         0x1008          /* get socket type */
#define SO_RCVVLANID    0x1009          /* get vlan info from mbuf */
#define SO_RCVPVCID     0x1010          /* get pvc info from mbuf */

/*---------------------------------------------------------------------*/
/* error and message id for asynsock                                   */
/*---------------------------------------------------------------------*/
#define        ASYN_MESSAGE        0X12345678

#define SE_ASYNC   0x0020

#define FIOASYNC        0x8004667D      /* Set/Unset socket to receive */  /* Asyncronous signal */

/*---------------------------------------------------------------------*/
/* macro for select()                                                  */
/*---------------------------------------------------------------------*/

/* added by tangcongfeng for D01009 */
#define FD_SETSIZE      3072

#define FDSETLEN        (((FD_SETSIZE) + (NFDBITS)) /(NFDBITS))    /* fd_set lenth, xxx long */
/* ended of tangcongfeng for D01009 */

#define    NFDBITS        0x20

#ifndef FD_SET

/*Modify by z62474 2007-10-08 for A82D20452 ,同步问题单A82D20312 */
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
/* struct used by application to set socket to be a asyn socket        */
/* this is defined in sockcom.h also, the two must be altered at same time */
/*---------------------------------------------------------------------*/
typedef struct  asynsockset
{
    ULONG  ulQueueID;
    ULONG  ulPointer;
    ULONG  ulWakeTaskID;
}asynsockset;

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

#ifndef InetAddr
ULONG vrp_InetAddr(CHAR *);
#define InetAddr(a)   vrp_InetAddr(a)
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
ULONG vrp_IsAsynSocket(LONG);
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
#ifndef gethostbyname6
struct hostent *vrp_gethostbyname6(CHAR *pName, ULONG ulPolicy);
#define gethostbyname6(a,b)     vrp_gethostbyname6(a,b)
#endif

#ifndef gethostbyaddr6
struct hostent *vrp_gethostbyaddr6(CHAR *pAddr,LONG iLen,LONG iType);
#define gethostbyaddr6(a,b,c)     vrp_gethostbyaddr6(a,b,c)
#endif

/********************   sock_err.h start **********************************/
#define EPERM           -1      /***************** Operation not permitted ************************/
#define ENOENT          -2      /***************** No such file or directory **********************/
#define ESRCH           -3      /***************** No such process ********************************/
#define EINTR           -4      /***************** Interrupted system call ************************/
#define EIO             -5      /***************** Input/output error *****************************/
#define ENXIO           -6      /***************** Device not configured **************************/
#define E2BIG           -7      /***************** Argument list too long *************************/
#define ENOEXEC         -8      /***************** Exec format error ******************************/
#define EBADF           -9      /***************** Bad file descriptor ****************************/
#define ECHILD          -10     /***************** No child processes *****************************/
#define EDEADLK         -11     /***************** Resource deadlock avoided **********************/
                                /***************** 11 was EAGAIN **********************************/
#define ENOMEM          -12     /***************** Cannot allocate memory *************************/
#define EACCES          -13     /***************** Permission denied ******************************/
#define EFAULT          -14     /***************** Bad address ************************************/
#define ENOTBLK         -15     /***************** Block device required **************************/
#define EBUSY           -16     /***************** Device busy ************************************/
#define EEXIST          -17     /***************** File exists ************************************/
#define EXDEV           -18     /***************** Cross-device link ******************************/
#define ENODEV          -19     /***************** Operation not supported by device **************/
#define ENOTDIR         -20     /***************** Not a directory ********************************/
#define EISDIR          -21     /***************** Is a directory *********************************/
#define EINVALID        -22     /***************** Invalid argument *******************************/
#define ENFILE          -23     /***************** Too many open files in system ******************/
#define EMFILE          -24     /***************** Too many open files ****************************/
#define ENOTTY          -25     /***************** Inappropriate ioctl for device *****************/
#define ETXTBSY         -26     /***************** Text file busy *********************************/
#define EFBIG           -27     /***************** File too large *********************************/
#define ENOSPC          -28     /***************** No space left on device ************************/
#define ESPIPE          -29     /***************** Illegal seek ***********************************/
#define EROFS           -30     /***************** Read-only file system **************************/
#define EMLINK          -31     /***************** Too many links *********************************/
#define EPIPE           -32     /***************** Broken pipe ************************************/

/* math software */
#define EDOM            -33     /* Numerical argument out of domain */
#define ERANGEE         -34     /* Result too large */

/* non-blocking and interrupt i/o */
#define EAGAIN          -35     /* Resource temporarily unavailable */
#define EWOULDBLOCK     EAGAIN  /* Operation would block */
#define EINPROGRESS     -36     /* Operation now in progress */
#define EALREADY        -37     /* Operation already in progress */

/* ipc/network software -- argument errors */
#define ENOTSOCK        -38     /* Socket operation on non-socket */
#define EDESTADDRREQ    -39     /* Destination address required */
#define EMSGSIZE        -40     /* Message too LONG */
#define EPROTOTYPE      -41     /* Protocol wrong type for socket */
#define ENOPROTOOPT     -42     /* Protocol not available */
#define EPROTONOSUPPORT -43     /* Protocol not supported */
#define ESOCKTNOSUPPORT -44     /* Socket type not supported */
#define EOPNOTSUPP      -45     /* Operation not supported */
#define EPFNOSUPPORT    -46     /* Protocol family not supported */
#define EAFNOSUPPORT    -47     /* Address family not supported by protocol family */
#define EADDRINUSE      -48     /* Address already in use */
#define EADDRNOTAVAIL   -49     /* Can't assign requested address */

/* ipc/network software -- operational errors */
#define ENETDOWN        -50    /* Network is down */
#define ENETUNREACH     -51    /* Network is unreachable */
#define ENETRESET       -52    /* Network dropped connection on reset */
#define ECONNABORTED    -53    /* Software caused connection abort */
#define ECONNRESET      -54    /* Connection reset by peer */
#define ENOBUFS         -55    /* No buffer space available */
#define EQDROP          -56    /* Drops a packet because queue us full */
#define EISCONN         -57    /* Socket is already connected */
#define ENOTCONN        -58    /* Socket is not connected */
#define ESHUTDOWN       -59    /* Can't send after socket shutdown */
#define ETOOMANYREFS    -60    /* Too many references: can't splice */
#define ETIMEDOUT       -61    /* Operation timed out */
#define ECONNREFUSED    -62    /* Connection refused */

#define ELOOP           -63    /* Too many levels of symbolic links */

#define ENAMETOOLONG    -64    /* File name too long */

/* should be rearranged */
#define EHOSTDOWN       -65    /* Host is down */
#define EHOSTUNREACH    -66    /* No route to host */
#define ENOTEMPTY       -67    /* Directory not empty */

/* quotas & mush */
#define EPROCLIM        -68    /* Too many processes */
#define EUSERS          -69    /* Too many users */
#define EDQUOT          -70      /* Disc quota exceeded */

/* Network File System */
#define ESTALE          -71    /* Stale NFS file handle */
#define EREMOTE         -72    /* Too many levels of remote in path */
#define EBADRPC         -73    /* RPC struct is bad */
#define ERPCMISMATCH    -74    /* RPC version wrong */
#define EPROGUNAVAIL    -75    /* RPC prog. not avail */
#define EPROGMISMATCH   -76    /* Program version wrong */
#define EPROCUNAVAIL    -77    /* Bad procedure for program */

#define ENOLCK          -78    /* No locks available */
#define ENOSYS          -79    /* Function not implemented */

#define EFTYPE          -80    /* Inappropriate file type or format */
#define EAUTH           -81    /* Authentication error */
#define ENEEDAUTH       -82    /* Need authenticator */
#define ELAST           -83    /* Must be equal largest errno */


/* pseudo-errors returned inside kernel to modify return to process */
#define ERESTART        -84    /* restart syscall */
#define EJUSTRETURN     -85    /* don't modify regs, just return    */

#define ETASKCREATE     -86    /* don't create task */
#define ETASKDELETE     -87    /* don't delete task */
#define ETASKGETID      -88    /* have not task */
#define EPRISET         -89    /* can't set pritioy */

#define EEVRECEIVE      -90    /* time is out */
#define EEVSEND         -91    /* ev_nowait is select */

#define EQUCREATE       -92    /* node's object table full */
#define EQUDELETE       -93    /* delete queue fail */
#define EQUSEND         -94    /* send message fail */
#define EQURECEIVE      -95    /* receive message fail */

#define ESMCREATE       -96    /* sm create fail */
#define ESMDELETE       -97    /* sm delete fail */
#define ESMP            -98    /* sm p fail */
#define ESMV            -99    /* sm v fail */

#define ETCBCHECK       -100   /* has not find the tcb */
#define ETCBCREATE      -101   /* has not create tcb */
#define ETCBDELETE      -102   /* tcb has not delete */

#define ENONBIO         -103
#define ENOASYNC        -104
#define ENOSETOWN       -105
#define ENOGETOWN       -106
#define ENOFIONBIO      -107
#define ENOFIOASYNC     -108
#define ENOFIOBACKCALL  -109

#define ECANTTCB        -107

#define EUIO            -108

#define ENOPROTO        -109
#define ENOMG           -110

#define EBLOCKING       -111
#define ENOTUDPSOCK     -112
#define ETCBINUSE       -113

#define ESNDBUFHIWAT    -114

#define ENOTBOUNDALGIN   -117  	/*  Not Boundary algin Error for ARM   2006-5-12   x43050  */
#define EDISABLEDFORTEST -118  	/*  VISP V100R005   2006-4-25   x43050  */

#define EMORECONTROL    -120
#define EVOIDINPCB      -121
#define EVOIDTCPCB      -122
/* zhangfeng, 2004,02,27 */

#define ENOTMULTI       -124
#define EINPUTIF        -125
#define ENOTBIND        -126    /*修改问题单A82D18705，rgx 2007-08-09*/

#define EINVAL          -1

#define EFULLSOCK       -200

#define EGADDR          -201    /*错误的组地址*/
#define ESADDR          -202    /*错误的源地址*/
#define EGOVERFLOW      -203    /*接口上配置的组超过限制*/
#define ESOVERFLOW      -204    /*socket上配置的源地址超过限制*/
#define EBLOCKSOURCE    -205    /*阻止一个本身已经被阻止的源地址（组相同）*/
#define EUNBLOCKSOURCE  -206    /*允许一个本身没有被阻止的源地址（组相同）*/
#define EADDSOURCE      -207    /*增加一个已经存在的源地址（组相同）*/
#define EDROPSOURCE     -208    /*删除一个不存在的源地址（组相同）*/
#define EFILTERMODE     -209    /*多播组过滤模式不允许该操作*/
#define ESOURCELISTNULL -210    /*源列表为空*/
#define EIGMPCOMPNULL   -211    /*IGMP组件为空*/
#define EIFTYPE         -212    /*错误的接口类型*/
#define EIFTHISBORD     -213    /*非本板接口*/
#define EGROUPNULL      -214    /*接口未加入指定多播组*/
#define EINVALIDVRF     -215
#define ENEEDFRAG       -216    /*IP报文需要分片，但是设置了DF标识*/

#define ESOCKCLOSE      -217    /*socket异常，需要关闭*/

#define ENOREMOTEHOST   1000
#define ENOREMOTEADDR   1001
#define ENOBUF          1002

/********************** sock_err.h end**************************************/

/********************** sock_com.h start ***********************************/

/* socket状态  socket state */
#define SS_NOFDREF           0x001    /************************ no file table ref any more ***********************************/
#define SS_ISCONNECTED       0x002    /************************ socket connected to a peer ***********************************/
#define SS_ISCONNECTING      0x004    /************************ in process of connecting to peer *****************************/
/*****************************************************************************************************************************/
/*****************************************************************************************************************************/
/*****************************************************************************************************************************/
#define SS_ISDISCONNECTING   0x008    /************************ in process of disconnecting **********************************/
#define SS_CANTSENDMORE      0x010    /************************ can't send more data to peer *********************************/
#define SS_CANTRCVMORE       0x020    /************************ can't receive more data from peer ****************************/
#define SS_RCVATMARK         0x040    /************************ at mark on input *********************************************/
/*****************************************************************************************************************************/
/*****************************************************************************************************************************/
/*****************************************************************************************************************************/
#define SS_PRIV              0x080    /************************ privileged for broadcast, raw... *****************************/
#define SS_NBIO              0x100    /************************ non-blocking ops *********************************************/
#define SS_ASYNC             0x200    /************************ async i/o notify *********************************************/
#define SS_ISCONFIRMING      0x400    /************************ deciding to accept connection req ****************************/

#define SS_CONNECT           0x800

#define SS_BLOCKING          0x1000    /* there is one task blocking on this socket*/
                                /* used in global socket*/
#define SS_RECALL               0x2000  /* set socket to call back */
#define SS_SENDDATAIF           0X20000
#define SS_WOULDWAKEUP          0X40000
#define SS_ASYNWAKEUP           0x80000  /* asynsocket to wake up peerclose message */

#define    SS_BACK              0x4000  /* set socket to backup */ /* added by mayun for socket ha */

/*    sockbuf     state */
#define SB_LOCK              0x01    /* lock on data queue */
#define SB_WANT              0x02    /* someone is waiting to lock */
#define SB_WAIT              0x04    /* someone is waiting for data/space */
#define SB_SEL               0x08    /* someone is selecting */
#define SB_ASYNC             0x10    /* ASYNC I/O, need signals */
#define SB_NOTIFY            (SB_WAIT|SB_SEL|SB_ASYNC)
#define SB_NOINTR            0x40    /* operations not interruptible */
#define SB_SELOOB            0x80
#define SB_LOCKWAIT          0x100
#define SB_BLOCKING          0x1000   /* there has been a task blocking on this sb */

/* Added by fengjing209023 DTS2014032706863 本段调用了CLOSE后不需要再上报ASYN_CLOSE事件 */
/* user close  state */
#define    SS_USERCLOSECALLED     0x01  /* 用户已经调用过CLOSE */
#define    SS_PEERCLOSENOTIFIED   0x02  /* SOCKET已经上报过PEERCLOSE */

/*socket events*/
#define SE_CONNECT  0x0001
#define SE_CLOSE    0x0002
#define SE_LOCKWAIT 0x0004
#define SE_WAIT     0x0008
#define SE_SEL      0x0010
#define SE_ASYNSOCK SE_ASYNC
#define SE_SP       0x0040


/*socket type*/
#define SOCK_STREAM     1               /* stream socket */
#define SOCK_DGRAM      2               /* datagram socket */
#define SOCK_RAW        3               /* raw-protocol interface */
#define SOCK_RDM        4                    /* reliably-delivered message */
#define SOCK_SEQPACKET  5            /* sequenced packet stream */

#define MSG_OOB         0x1                  /* process out-of-band data */
#define MSG_PEEK        0x2                  /* peek at incoming message */
#define MSG_DONTROUTE   0x4         /* send without using routing tables */
#define MSG_EOR         0x8                   /* data completes record */
#define MSG_TRUNC       0x10              /* data discarded before delivery */
#define MSG_CTRUNC      0x20            /* control data lost before delivery */
#define MSG_WAITALL     0x40              /* wait for full request or error */
#define MSG_DONTWAIT    0x80           /* this message should be nonblocking */

typedef struct tagSOCK_MOD_INFO_S
{
    ULONG ulModID;
    ULONG ulSubModID;
    ULONG ulSKT_MAX_SOCK_N;
    ULONG ulHC_ENTRY_MAINTYPE;
    ULONG ulSKT_GLOBAL_SOCKET_EN;
    ULONG ulHC_IR_Enable_flag;    /* add by l57500,06/12/08. for support IR hc */
}SOCK_MOD_INFO_S;

typedef struct tagKEEPALIVESET
{
    USHORT usKeepintvl;       /* second */
    USHORT usKeepcount;       /* keepintvl's count */
}KEEPALIVESET_S;

#ifndef TYPEDEF_TASK_T
#define TYPEDEF_TASK_T
typedef ULONG    task_t;
#endif

typedef struct tagSELINFO
{
    task_t      si_tTaskId;   /* 保存等待这个Socket的进程ID（仅仅select使用）*/
    SHORT       si_sFlags;    /* 若有多个进程选中该SB，这个标志位将被设为SI_COLL（仅仅select使用）*/
    UCHAR       ucPadding[2];
}SELINFO_S;
#define        L_SELINFO_S        sizeof(SELINFO_S)

/*
 * Structure used by kernel to pass protocol
 * information in raw sockets.
 */
typedef struct tagSOCKPROTO
{
    USHORT    sp_usFamily;        /* address family */
    USHORT    sp_usProtocol;       /* protocol */
}SOCKPROTO_S;

typedef struct tagSENDDATAIF
{
    ULONG           ulIfIndex;
    ULONG           ulSrcAddr;
}SENDDATAIF_S;
#define         L_SENDDATAIF_S  sizeof(SENDDATAIF_S)

typedef struct tagSENDBY_IF_NEXTHOP
{
    ULONG           ulOutIfIndex;
    ULONG           ulNextHopAddr;     /* must be net-order */
}SENDBY_IF_NEXTHOP_S;
#define         L_SENDBY_IF_NEXTHOP_S  sizeof(SENDBY_IF_NEXTHOP_S)

#define         L_SNDBYDSTMAC_S  sizeof(SNDBYDSTMAC_S)
#define         MAXMACLEN        8
typedef struct tagSNDBYDSTMAC
{
    UCHAR           ucDstMac[MAXMACLEN];
    ULONG           ulMacLen;
}SNDBYDSTMAC_S;
/* ended add for dhcp-relay */

typedef struct  tagASYNSOCKET
{
    ULONG           ulQueueID;
    ULONG           ulPointer;
    task_t          ulWakeTaskID;
}ASYNSOCKET_S;
#define L_ASYNSOCKET_S sizeof(struct tagASYNSOCKET)

typedef struct  tagRECALLSOCKET
{
    ULONG (*so_pfCallBack)( CHAR *, VOID *ulValue );
    CHAR  *pszDataBuf;
    ULONG ulBufLen;
    ULONG ulUserData;  /* the data user set and will be return at ulValue */
}RECALLSOCKET_S;

#define L_RECALLSOCKET_S sizeof(RECALLSOCKET_S)

typedef union tagAsyncsock_un
{
    ASYNSOCKET_S    so_unstAsynSocket; /* this is set by the application, to wakeup application */
    RECALLSOCKET_S  so_unstCallBack;
}ASYNSOCKINFO_UN;
#define L_SO_UNASYNSOCK sizeof(ASYNSOCKINFO_UN)

/*struct tagPROTOSW;*/ /* by zhangyilong 27499 重复声明，去掉 */
typedef struct tagSOCKET
{
    SHORT               so_sType;           /* generic type, see socket.h */
    SHORT               so_sLinger;         /* time to linger while closing */
    ULONG               so_sOptions;        /* from socket call, see socket.h
                                             changed by yuyong&mayun 2002/10/30 for address overlap*/
    ULONG               so_sState;          /* internal state flags SS_*, below */
    VOID                (*so_pfSignal)();
    CHAR                *so_pPcb;           /* protocol control block */
    struct tagPROTOSW   *so_pProto;         /* protocol handle */
    struct tagSOCKET    *so_pHead;          /* back pointer to accept socket */
    struct tagSOCKET    *so_pQ0;            /* queue of partial connections */
    struct tagSOCKET    *so_pQ;             /* queue of incoming connections */
    SHORT               so_sQ0Len;          /* partials on so_q0 */
    SHORT               so_sQLen;           /* number of connections on so_q */
    SHORT               so_sQLimit;         /* max number queued connections */
    SHORT               so_sTimeO;          /* connection timeout */
    SHORT               so_sError;          /* error affecting connection */
    /* Added by fengjing209023 DTS2014032706863 本段调用了CLOSE后不需要再上报ASYN_CLOSE事件 */
    UCHAR               ucUsrCloseFlag;     /* 1、用来标记用户是否调了CLOSE,2、用来标记是否上报过PEERCLOSE */
    /* Addend end */    
    UCHAR               ucPadding_1[1];
    task_t              so_tTaskId;         /* pgid for signals */
    ULONG               so_ulOobMark;       /* chars to oob mark */
    
    ULONG               ulKeepIdle;
    /* End of likaikun */
    
    KEEPALIVESET_S      so_stKeepalive;
    /* end of mayun */

    SENDDATAIF_S        so_stSendDataIf;
    
    SENDBY_IF_NEXTHOP_S so_stSendby_If_NextHop;

    SNDBYDSTMAC_S       so_stSndbyDstMac;

    ULONG               ulSrcAddr;      /* 网络字节序 */

    struct tagSOCKBUF
    {
        LONG        sb_ulCC;        /* actual chars in buffer */
        LONG        sb_ulHiWat;     /* max actual CHAR count */

        LONG        sb_ulLoWat;     /* low water mark */
        MBUF_S      *sb_pMb;        /* the mbuf chain */

        MBUF_S      *sb_pLastMbuf;  /*refer to the mbuf node next to never*/
        /*End of addition to improve search efficiency, 2002,04,19*/

        SELINFO_S   sb_stSel;       /* process selecting read/write */
        SHORT       sb_sFlags;      /* flags, see below */
        SHORT       sb_sTimeO;      /* timeout for read/write */
        ULONG       sb_ulIfIndex;   /* contain the ifnet inext of the latest sended or received datagram */
        /* we set read , connect, accept sleep in so_stRcv.sb_tTaskId,
        * and write,close in so_stSnd.sb_tTaskId */
        task_t      sb_tTaskId;     /* the task who sleep to read,write,connect,accept */

        /* Added for SOCKET HA */
        ULONG       sb_ulAddOrSubLen;     /* Save the length to be added or subtract from the socket buffer by ha */
        UCHAR       sb_ucIsInBackupQueue; /* Indicate whether this socket buf is backup queue */
        UCHAR       ucPadding_1[3];
    } so_stRcv, so_stSnd;

    SHORT so_sRefCnt;   /* the number of tasks to share this socket */
    UCHAR ucPadding_2[2];

    /* added for mpls vpn */
    ULONG           ulVrfIndex;
    ULONG           ulVrfIndex_Rcvd;

    /* mayun for zoneid */
    ULONG           ulZoneId;

    ASYNSOCKINFO_UN so_unAsynSock;

    LONG             so_iFd;            /* the file descriptor of this socket */
    struct tagTCB   *so_pTcb;           /* the tcb which this socket socket is in
                                         It is to falloc a fd in SO_IsConnected() for new socket(which is create by SO_NewConn ) */
#define so_stAsynSocket    so_unAsynSock.so_unstAsynSocket
#define so_stCallBack      so_unAsynSock.so_unstCallBack

    /* add for Socketdebug ,only use in UDP or RawIP for full drop .mayun. */
    ULONG so_ulDropPackets;

    /*供IPV4 UDP, RAW IP发送报文时填入目的地址，避免重复创建mbuf操作*/
    VOID *so_pAddr;

    VOID *pstHeadCacheInfo;/*指向Head Cache的信息结构*/
    struct tagSOCKET *pstHeadCacheSocketNext;/*指向下一个使用Head Cache的socket*/

    /* Added for SOCKET HA */
    ULONG so_ulBackupTimeStamp; /* Indicate the time when socket chain's backup msg of this
                                 * socket is put into socket backup queue.
                                 */
    UCHAR so_ucIsInBackupQueue; /* Indicate whether backup msg of socket modification
                                 * or socket chain is in socket backup queue
                                 */

    UCHAR ucPadding;        /* 保留字段,未使用 */
    USHORT usRcvVlanInfo;   /* 保存vlan tag信息,主机序 */

    SENDDATAIF_S so_stTrrtOutIfIndex;    /*trrt发送时指定的出接口*/
}SOCKET_S;

typedef struct tagSOSB6_CALLBACUP_SET_S
{
    /*Generic Get socket field Interface function */
    ULONG  (*pfIP6_Socket_SetParameter)(UINTPTR, enum tageSocketField , VOID  *);
    /*Generic Set socket field Interface function */
    ULONG  (*pfIP6_Socket_GetParameter)(UINTPTR, enum tageSocketField, VOID  *);
    VOID      (*pfSO6_CantSendMore)(UINTPTR);
    VOID      (*pfSO6_CantRcvMore)(UINTPTR);
    VOID      (*pfSO6_IsConnecting)(UINTPTR);
    VOID      (*pfSO6_IsConnected)(UINTPTR);
    VOID      (*pfSO6_IsDisconnecting)(UINTPTR);
    VOID      (*pfSO6_IsDisconnected)(UINTPTR);
    UINTPTR   (*pfSO6_NewConn)(UINTPTR, LONG);
    VOID      (*pfSO6_HasOutOfBand)(UINTPTR);
    LONG      (*pfSO6_Reserve)(UINTPTR, ULONG, ULONG);
    VOID      (*pfSB6_Append)(UINTPTR, struct tagMBuf *);
    LONG      (*pfSB6_AppendAddr)(UINTPTR ,struct tagSOCKADDR *,struct tagMBuf *,
                                  struct tagMBuf *);
    VOID      (*pfSB6_Flush)(UINTPTR);
    VOID      (*pfSB6_Drop)(UINTPTR, LONG);
    VOID      (*pfSo6WakeUp)(UINTPTR, LONG);
    ULONG     (*pfSO6_AsynReCall)(UINTPTR, struct tagMBuf *, struct tagIP6_S *,
                                  USHORT );
    LONG      (*pfSO6_AsynWakeUp)(UINTPTR, LONG, LONG );
    LONG      (*pfSysCtl_int)(VOID *, ULONG *, VOID *, ULONG , LONG *);
    LONG      (*pfWakeUp)(ULONG ulTaskId, ULONG ulEvent);
    long      (*pfSO6_Abort) (UINTPTR pSocket);
    /* add 06-12-06, IR加了两个回调函数 */
    CHAR      (*pfSock_IP6_GetErrMap)(ULONG ulCmdIndex);
    CHAR*     (*pfinet_ntop6)(const CHAR*, CHAR*, ULONG);
    ULONG     (*pfHeadCache6_LookUpSrcAddr)(struct tagSOCKET*, IN6ADDR_S*, USHORT, IN6ADDR_S*, USHORT *);
    LONG      (*pfSOCK6_SocketID_Check)(ULONG ulProType, ULONG ulTaskID, ULONG ulSocketID,
                                    VOID **ppstSocket, VOID **ppstIn6PCB);
    UINT32    (*pfSO6_CheckCookieStart)(UINTPTR);
}SOSB6_CALLBACUP_SET_S;

#define L_SOCKET_S        sizeof(SOCKET_S)

typedef struct tagSOCKBUF     SOCKBUF_S;
#define L_SOCKBUF_S       sizeof(SOCKBUF_S)


/********************** sock_com.h end  *********************************/

/********************** macro.h  *********************************/
#define     SBMAX        (8192*1024L)

extern SOCK_MOD_INFO_S g_stSOCK4ModInfo;
#define     FILENUM         g_stSOCK4ModInfo.ulSKT_MAX_SOCK_N
/* Modify for DTS2011031503749, by yuehaitao171195, at 2011-03-17. 修改原因: TSleep
   阻塞时并没有持有信号量，此时如果其他任务创建了多个socket，则socket可能扩充文件描述符，导致TSleep返回后访问野内存 */
#define     EXPANDNUM       FILENUM

/******************** from asynsock.h  ***********************/
/*消息结构定义*/
typedef struct tagASYNSOCKETMSG
{
    ULONG    ulMsgType;    /*表明此消息是异步SOCKET发送的消息,数值为ASYN_MESSAGE*/
    ULONG    ulPointer;    /*原先是src分配的buffer, 现表明是src指定的pointer */
                            /*绑定于异步SOCKET的一个数值*/
    LONG     iError;

#define SUCCEEDED       0
#define FAILED          1

    /* Modefied by fengjing209023 ASYNMSG_S.FD.type.defect 将FD由16位改为24位,涉及接口变更，需知会产品 */
    /* 注意: VOS_Que_Write函数写的消息最大长度为16字节(32bit环境)，故该结构体定义不能超过16字节*/
    unsigned usFd:24;
    unsigned usEventType:8;
    /* Modefied end */    

#define ASYN_READ       1
#define ASYN_WRITE        2
#define ASYN_CONNECT    3
#define ASYN_CLOSE      4
#define ASYN_ACCEPT     5
#define ASYN_PEERCLOSE  6
#define ASYN_KEEPALIVEDOWN  7

}ASYNMSG_S;


/******************  from in_pcb.h  *********************/
#define  HASH_FIRSTLEVEL_MASK     127        /* 128 - 1 */
#define  HASH_SECONDLEVEL_MASK    511        /* 512 - 1 */

/*
 * calculate first level hash function
 * we just use LPort and not use LAddr
 */
#define  HASHFUNC_FIRST(usLPort)    \
                    (USHORT)( (((USHORT)(usLPort)) ^ \
                               ((USHORT)(usLPort)>>8)) & \
                              HASH_FIRSTLEVEL_MASK )
/*
 * calculate second level hash function
 * we use FPort and FAddr
 */
#define  HASHFUNC_SECOND(usFPort, ulFAddr) \
             (USHORT) ((((USHORT)(usFPort)) ^ \
                        ((USHORT)((ULONG)(ulFAddr)>>16)) ^ \
                        ((USHORT)(ulFAddr))) &    \
                       HASH_SECONDLEVEL_MASK )

#define SOCK_FILT_PERMIT   0  /* 符合过滤条件，即过滤通过 */
#define SOCK_FILT_DENY    1  /* 不符合过滤条件，即过滤不通过 */


/********************  from prod.h   ********************/
#define    SOWWAKEUP(so)    SoWakeUp((so), 1)
#define    SORWAKEUP(so)    SoWakeUp((so), 2)
VOID        SO_Free(SOCKET_S *pSocket);

/********************  from sock_fun.h   ********************/
LONG SB_AppendAddr(SOCKET_S *pSocket,SOCKADDR_S *pstAsa,MBUF_S *pstMData, MBUF_S *pstMControl);
VOID  SoWakeUp(SOCKET_S *pSocket, LONG iKind);
VOID  SO_IsDisconnected(SOCKET_S *pSocket);
VOID  SO_IsConnected(SOCKET_S *pSocket);
VOID SO_CantSendMore(SOCKET_S *pSocket);
LONG SO_Reserve(SOCKET_S *pSocket,  ULONG ulSndCC, ULONG ulRcvCC);

/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-05 */
#ifndef getrcvvpnid
LONG vrp_getrcvvpnid(LONG , ULONG *);
#define getrcvvpnid(a,b)   vrp_getrcvvpnid(a,b)
#endif
/* End:VISP1.7C03 VRF wangchengyang,2009-02-05 */

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */
#endif    /* end of _VISP_IR_SOCKET_H_ */
