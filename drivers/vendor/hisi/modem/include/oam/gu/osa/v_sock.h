

/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: v_sock.h                                                        */
/*                                                                           */
/* Author: dopra                                                             */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement socket. copy this file from dopra                  */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/* 2. Date: 2006-10                                                          */
/*    Author: Xu Cheng                                                       */
/*    Modification: Standardize code                                         */
/*                                                                           */
/*****************************************************************************/

#ifndef _V_SOCK_H
#define _V_SOCK_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "dopra_def.h"
#include "vos_config.h"

/*½ûÖ¹pclint¸æ´íExpression-like macro    'name' not parenthesized*/
/*lint -save -e773 */

#ifdef VOS_OS_VER
#ifdef RUN_IN_TIPS
#define _V_PUBLIC_H  /* If run in TIPS, then do not to include v_public.h */
/***********************************************************************
* the macros for application
***********************************************************************/
#define AF_MPLS         28
#ifndef AF_UNSPEC
#define AF_UNSPEC       0               /* unspecified */
#endif

#ifndef AF_LOCAL
#define AF_LOCAL        1               /* local to host (pipes, portals) */
#endif

#ifndef AF_UNIX
#define AF_UNIX         AF_LOCAL        /* backward compatibility */
#endif

#ifndef AF_INET
#define AF_INET         2               /* internetwork: UDP, TCP, etc. */
#endif

#ifndef AF_IMPLINK
#define AF_IMPLINK      3               /* arpanet imp addresses */
#endif

#ifndef AF_PUP
#define AF_PUP          4               /* pup protocols: e.g. BSP */
#endif

#ifndef AF_CHAOS
#define AF_CHAOS        5               /* mit CHAOS protocols */
#endif

#ifndef AF_NS
#define AF_NS           6               /* XEROX NS protocols */
#endif

#ifndef OSI_ISIS
#define OSI_ISIS        7               /* FOR IS-IS ADDED BY ZHAOBIAO. */
#endif
#ifndef AF_ISO
#define AF_ISO          OSI_ISIS               /* ISO protocols */
#endif

#ifndef AF_OSI
#define AF_OSI          AF_ISO
#endif

#ifndef AF_ECMA
#define AF_ECMA         8               /* european computer manufacturers */
#endif

#ifndef AF_DATAKIT
#define AF_DATAKIT      9               /* datakit protocols */
#endif

#ifndef AF_CCITT
#define AF_CCITT        10              /* CCITT protocols, X.25 etc */
#endif

#ifndef AF_SNA
#define AF_SNA          11              /* IBM SNA */
#endif

#ifndef AF_DECnet
#define AF_DECnet       12              /* DECnet */
#endif

#ifndef AF_DLI
#define AF_DLI          13              /* DEC Direct data link interface */
#endif

#ifndef AF_LAT
#define AF_LAT          14              /* LAT */
#endif

#ifndef AF_HYLINK
#define AF_HYLINK       15              /* NSC Hyperchannel */
#endif

#ifndef AF_APPLETALK
#define AF_APPLETALK    16              /* Apple Talk */
#endif

#ifndef AF_ROUTE
#define AF_ROUTE        17              /* Internal Routing Protocol */
#endif

#ifndef AF_LINK
#define AF_LINK         18              /* Link layer interface */
#endif

#ifndef pseudo_AF_XTP
#define pseudo_AF_XTP   19              /* eXpress Transfer Protocol (no AF) */
#endif

#ifndef AF_COIP
#define AF_COIP         20              /* connection-oriented IP, aka ST II */
#endif

#ifndef AF_CNT
#define AF_CNT          21              /* Computer Network Technology */
#endif

#ifndef pseudo_AF_RTIP
#define pseudo_AF_RTIP  22              /* Help Identify RTIP packets */
#endif

#ifndef AF_IPX
#define AF_IPX          23              /* Novell Internet Protocol */
#endif

#ifndef AF_SIP
#define AF_SIP          24              /* Simple Internet Protocol */
#endif

#ifndef pseudo_AF_PIP
#define pseudo_AF_PIP   25              /* Help Identify PIP packets */
#endif

#ifndef AF_BRIDGE
#define AF_BRIDGE       26              /* bridge flag*/
#endif

#ifndef AF_KEY
#define AF_KEY          27              /* IPSEC and IKE */
#endif

/* VRP_MODULE_IPV6  */
#ifndef AF_INET6
#define AF_INET6        29             /* added by mayun for IPv6 */
#endif

#ifndef GRE_FR
#define GRE_FR          30             /* moved out from fr_def.h, Terry, 2003/09/13 */
#endif

#ifndef INADDR_ANY
#define INADDR_ANY          (VOS_UINT32)0x00000000L
#endif

#ifndef INADDR_BROADCAST
#define INADDR_BROADCAST    (VOS_UINT32)0xffffffffL /* must be masked */
#endif

#ifndef INADDR_NONE
#define INADDR_NONE         0xffffffffUL        /* -1 return */
#endif

/*
 * Definitions of bits in internet address integers.
 * On subnets, the decomposition of addresses to host and net parts
 * is done according to subnet mask, not the masks here.
 */
#define PF_MAX          AF_MAX

#define CTL_NET     4

#define NET_RT_DUMP     1       /* dump; may limit to a.f. */
#define NET_RT_FLAGS    2       /* by flags, e.g. RESOLVING */
#define NET_RT_IFLIST   3       /* survey interface list */
#define NET_RT_MAXID    4

/*socket type*/
#define SOCK_STREAM     1               /* stream socket */
#define SOCK_DGRAM      2               /* datagram socket */
#define SOCK_RAW        3               /* raw-protocol interface */
#define SOCK_RDM        4               /* reliably-delivered message */
#define SOCK_SEQPACKET  5               /* sequenced packet stream */

#define MSG_OOB         0x1             /* process out-of-band data */
#define MSG_PEEK        0x2             /* peek at incoming message */
#define MSG_DONTROUTE   0x4             /* send without using routing tables */
#define MSG_EOR         0x8             /* data completes record */
#define MSG_TRUNC       0x10            /* data discarded before delivery */
#define MSG_CTRUNC      0x20            /* control data lost before delivery */
#define MSG_WAITALL     0x40            /* wait for full request or error */
#define MSG_DONTWAIT    0x80            /* this message should be nonblocking */

/*---------------------------------------------------------------------*/
/* Maximum queue length specifiable by listen()                        */
/*---------------------------------------------------------------------*/
#define SOMAXCONN       0x5         /* maximum queue length */

#define SOL_SOCKET      0xffff

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

#define SO_SENDDATAPORT  0x00080000

/*set the vlanid of the socket add by gao 03/12/31 BYDD01389*/
#define SO_SETVLANID   0x00100000

#define SO_VRFINDEX_ANY (FILENUM + 1)


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

/*---------------------------------------------------------------------*/
/* Options for use with [gs]etsockopt at the IP level.                 */
/*---------------------------------------------------------------------*/
#undef IP_OPTIONS
#define IP_OPTIONS                          1   /* set/get IP per-packet options */
#undef IP_HDRINCL
#define IP_HDRINCL                          2   /* long; header is included with data */
#undef IP_TOS
#define IP_TOS                              3   /* long; IP type of service and preced. */
#undef IP_TTL
#define IP_TTL                              4   /* long; IP time to live */
#undef IP_RECVOPTS
#define IP_RECVOPTS                         5   /* bool; receive all IP opts w/dgram */
#undef IP_RECVRETOPTS
#define IP_RECVRETOPTS                      6   /* bool; receive IP opts for response */
#undef IP_RECVDSTADDR
#define IP_RECVDSTADDR                      7   /* bool; receive IP dst addr w/dgram */
#undef IP_RETOPTS
#define IP_RETOPTS                          8   /* ip_opts; set/get IP options */
#undef IP_MULTICAST_IF
#define IP_MULTICAST_IF                     9   /* u_char; set/get IP multicast i/f  */
#undef IP_MULTICAST_TTL
#define IP_MULTICAST_TTL                    10  /* u_char; set/get IP multicast ttl */
#undef IP_MULTICAST_LOOP
#define IP_MULTICAST_LOOP                   11  /* u_char; set/get IP multicast loopback*/
#undef IP_ADD_MEMBERSHIP
#define IP_ADD_MEMBERSHIP                   12  /* ip_mreq; add an IP group membership */
#undef IP_DROP_MEMBERSHIP
#define IP_DROP_MEMBERSHIP                  13  /* ip_mreq; drop an IP group membership */
#undef IP_MULTICAST_INTF
#define IP_MULTICAST_INTF                   14  /* u_char; set/get IP multicast i/f */
#undef IP_ADD_MEMBERSHIP_INTF
#define IP_ADD_MEMBERSHIP_INTF              15  /* ip_mreq_intf; add an IP group */
                                                /* membership given interface number */
#undef IP_DROP_MEMBERSHIP_INTF
#define IP_DROP_MEMBERSHIP_INTF             16 /* ip_mreq_intf; drop an IP group */
                                                /* membership given interface number */
#undef IP_ROUT_ALERT
#define  IP_ROUT_ALERT                      17   /* ip_opts; set/get IP options mayun 2002-12-17 */
#undef IP_TOS_TOTAL
#define IP_TOS_TOTAL                        18   /* long; IP type of service and preced. */

/*  Option flags per-socket.*/
#undef SO_DEBUG
#define SO_DEBUG                        0x00000001          /* turn on debugging info recording */
#undef SO_ACCEPTCONN
#define SO_ACCEPTCONN                   0x00000002          /* socket has had listen() */
#undef SO_REUSEADDR
#define SO_REUSEADDR                    0x00000004          /* allow local address reuse */
#undef SO_KEEPALIVE
#define SO_KEEPALIVE                    0x00000008          /* keep connections alive */
#undef SO_DONTROUTE
#define SO_DONTROUTE                    0x00000010          /* just use interface addresses */
#undef SO_BROADCAST
#define SO_BROADCAST                    0x00000020          /* permit sending of broadcast msgs */
#undef SO_USELOOPBACK
#define SO_USELOOPBACK                  0x00000040          /* bypass hardware when possible */
#undef SO_LINGER
#define SO_LINGER                       0x00000080          /* linger on close if data present */
#undef SO_OOBINLINE
#define SO_OOBINLINE                    0x00000100          /* leave received OOB data in line */
#undef SO_REUSEPORT
#define SO_REUSEPORT                    0x00000200          /* allow local address & port reuse */
#undef SO_SENDDATAIF
#define SO_SENDDATAIF                   0x00000400          /* allow send data accross the specifed interface*/
#undef SO_UDPCHECKSUM
#define SO_UDPCHECKSUM                  0x00000800          /* set/unset udp output to calculate check sum */
#undef SO_NSYNDROMESVR
#define SO_NSYNDROMESVR                 0x00001000          /* set no parallel bgp server */
#undef SO_SNDBYDSTMAC
#define SO_SNDBYDSTMAC                  0x00002000          /* set snd mac for dhcp relay */
#undef SO_SETSRCADDR
#define SO_SETSRCADDR                   0x00004000          /* set source address of output packet */
#undef SO_SENDVPNID
#define SO_SENDVPNID                    0x00008000          /* VPN use this option */
#undef SO_SENDBY_IF_NEXTHOP
#define SO_SENDBY_IF_NEXTHOP            0x00010000          /* set outif and nexthop of output packet mayun 2002-12-17 */

/*---------------------------------------------------------------------*/
/* macro for select()                                                  */
/*---------------------------------------------------------------------*/
#define FD_SETSIZE      256

#define FDSETLEN        97     /* fd_set lenth, 97 long */

#define NFDBITS     0x20
#define NBBY        8

#define FD_SET(n, p)    {\
            if ((n) > 0 ){\
            ((p)->fds_bits[(n)/NFDBITS] |= \
                        (((VOS_UINT32) 0x80000000) >> ((n) % NFDBITS))); \
                    }\
                    }
#define FD_CLR(n, p)    ((p)->fds_bits[(n)/NFDBITS] &= \
                       ~(((VOS_UINT32) 0x80000000) >> ((n) % NFDBITS)))
#define FD_ISSET(n, p)  ((p)->fds_bits[(n)/NFDBITS] & \
                        (((VOS_UINT32) 0x80000000) >> ((n) % NFDBITS)))

#define FD_ZERO(p)  { \
                        VOS_INT32 xxx; \
                        for( xxx = 0; xxx<FDSETLEN; xxx++ ) \
                        { \
                            ((p)->fds_bits[xxx] = 0); \
                        } \
                    }

/* ipc/network software -- argument errors */
#define ENOTSOCK    -38     /* Socket operation on non-socket */
#define EDESTADDRREQ    -39     /* Destination address required */
#define EMSGSIZE    -40     /* Message too LONG */
#define EPROTOTYPE  -41     /* Protocol wrong type for socket */
#define ENOPROTOOPT -42     /* Protocol not available */
#define EPROTONOSUPPORT -43     /* Protocol not supported */
#define ESOCKTNOSUPPORT -44     /* Socket type not supported */
#define EOPNOTSUPP  -45     /* Operation not supported */
#define EPFNOSUPPORT    -46     /* Protocol family not supported */
#define EAFNOSUPPORT    -47     /* Address family not supported by protocol family */
#define EADDRINUSE  -48     /* Address already in use */
#define EADDRNOTAVAIL   -49     /* Can't assign requested address */

/*---------------------------------------------------------------------*/
/* following two used for recvmsg and sendmsg functions                */
/*---------------------------------------------------------------------*/
typedef struct iovec
{
    VOS_CHAR *iov_base;     /* base address */
    VOS_INT32 iov_len;        /* buffer length */
}iovec;

typedef struct msghdr
{
    VOS_CHAR  *msg_name;             /* optional address */
    VOS_INT16 msg_namelen;            /* size of address */
    iovec *msg_iov;      /* scatter/gather array */
    VOS_INT16 msg_iovlen;             /* # elements in msg_iov */
    VOS_CHAR  *msg_control;        /* access rights */
    VOS_INT16 msg_controllen;       /* length of the rights buffer */
    VOS_INT16 msg_flags;
}msghdr;


typedef struct cmsghdr
{
    VOS_INT16       cmsg_len;   /* data byte count, including hdr */
    VOS_INT16       cmsg_level; /* originating protocol */
    VOS_INT16       cmsg_type;  /* protocol-specific type */
    VOS_CHAR        cmsg_data[2];  /* assign byte */
}cmsghdr;
/*---------------------------------------------------------------------*/
/* following two used for select                                       */
/* this is defined in select.h as FD_SET_S, the two must be altered at */
/* same time                                                           */
/*---------------------------------------------------------------------*/
typedef struct fd_set
{
    VOS_INT32 fds_bits[FDSETLEN];  /* we support for 3072 socket in a task */
} fd_set;

struct timeval
{
    VOS_INT32  tv_sec;       /* no. of seconds */
    VOS_INT32  tv_usec;      /* no. of micro seconds */
};

typedef struct in_addr
{
    VOS_UINT32 s_addr;       /* IP address of the socket */
}in_addr;

#define IP_HOSTNAME_LEN    20
struct  hostent
{
        VOS_CHAR    h_name[IP_HOSTNAME_LEN + 1];         /* official name of host */ /* 10->21 by mayun 20010608 */
        VOS_CHAR    h_aliases[4][IP_HOSTNAME_LEN + 1];      /* alias list */
        VOS_INT16   h_addrtype;         /* host address type */
        VOS_INT16   h_length;           /* length of address */
        VOS_CHAR    h_addr_list[4][20]; /* list of addresses */
#define h_addr  h_addr_list[0]      /* address, for backward compat */
};

struct  netent
{
        VOS_CHAR            n_name[10];          /* official name of net */
        VOS_CHAR            n_aliases[4][10];   /* alias list */
        VOS_INT16           n_addrtype;         /* net address type */
        VOS_UINT32   n_net;              /* network # */
};

/*---------------------------------------------------------------------*/
/* Structure used for manipulating ip address in bind,sendto and so on */
/*---------------------------------------------------------------------*/
typedef struct sockaddr_in
{
    VOS_UCHAR sin_len;      /* zy */
    VOS_UCHAR sin_family;   /* must be AF_INET */
    VOS_UINT16 sin_port;    /* 16-bit port number */
    struct in_addr sin_addr;    /* 32-bit IP address */
    VOS_CHAR sin_zero[8];           /* must be 0 */
}sockaddr_in;
#ifndef sockaddr
#define sockaddr sockaddr_in
#endif

/*for option SO_SENDBY_IF_NEXTHOP*/
typedef struct tagSENDDATAIF
{
    VOS_UINT32           ulIfIndex;
    VOS_UINT32           ulSrcAddr;
}SENDDATAIF_S;

/*---------------------------------------------------------------------*/
/* Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP.    */
/*---------------------------------------------------------------------*/
typedef struct ip_mreq
{
    in_addr   imr_mcastaddr;  /* IP multicast address of group */
    VOS_UINT32     imr_ifindex;  /* local IP address of interface */
}ip_mreq;


#elif( ( VOS_OS_VER == VOS_WIN32 ) || ( VOS_OS_VER == VOS_RTT ) )
#include <winsock2.h>
#include <ws2tcpip.h>

#elif ( VOS_OS_VER == VOS_PSOS )

#include <pna.h>

#elif ( VOS_OS_VER == VOS_VXWORKS )
#include <sockLib.h>
#include <socket.h>
#include <in.h>
#include <ioLib.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#elif (( VOS_OS_VER == VOS_LINUX ) || ( VOS_OS_VER == VOS_UCLINUX ))

#include <sys/socket.h>
#if ( VOS_CPU_TYPE == VOS_8245 )
#include <sys/uio.h>
#endif
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#elif ( VOS_OS_VER == VOS_SOLARIS)
/*
#include <netinet/in.h>
#include <sys/socket.h>
*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/sockio.h>
#include <netdb.h>

#elif ( VOS_OS_VER == VOS_HPUNIX || VOS_OS_VER == VOS_IBMUNIX )

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socketvar.h>
#include <netdb.h>

#elif ( VOS_OS_VER == VOS_UNIX )

#elif (VOS_OS_VER == VOS_TLINUX)
#endif /* VOS_OS_VER */
#endif /* VOS_OS_VER */

/************************* MACRO & TYPE DEFINITION ***************************/

#ifdef VOS_OS_VER
#ifdef RUN_IN_TIPS

#elif( ( VOS_OS_VER == VOS_WIN32 ) || ( VOS_OS_VER == VOS_WINCE ) )

struct iovec
{
   VOS_CHAR *iov_base;   /* base address */
   VOS_INT iov_len;      /* buffer length */
};

typedef struct msghdr
{
   VOS_CHAR *msg_name;          /* optional address */
   VOS_INT msg_namelen;         /* size of address */
   struct iovec *msg_iov;   /* scatter/gather array */
   VOS_INT msg_iovlen;          /* # elements in msg_iov */
   VOS_CHAR *msg_accrights;     /* access rights */
   VOS_INT msg_accrightslen;    /* size of access rights buffer */
} VOS_MSGHDR;


#elif (VOS_OS_VER == VOS_PSOS)

typedef struct msghdr VOS_MSGHDR;

#ifndef FIONREAD
#define FIONREAD FIOREAD
#endif

#elif (VOS_OS_VER == VOS_VXWORKS)

typedef struct msghdr VOS_MSGHDR;

#elif ((VOS_OS_VER == VOS_LINUX) || (VOS_OS_VER == VOS_UCLINUX))

#elif (VOS_OS_VER == VOS_UNIX)
#endif
#endif

#ifdef VOS_OS_VER
#ifndef RUN_IN_TIPS
#if( VOS_OS_VER == VOS_TLINUX )

/* #include "dopra/v_private.h" */

#pragma pack (1)
struct in_addr {
    VOS_UINT32 s_addr;
};


struct sockaddr_in {
    UCHAR   sin_len;
    UCHAR   sin_family;
    VOS_UINT16  sin_port;
    struct  in_addr sin_addr;
    CHAR  sin_zero[8];
};
#pragma pack (0)
#define sockaddr sockaddr_in
#endif
#endif
#endif

/* used for shutdown() to indicate flags of operation */
#define VOS_HOW_RECEIVE            0x00
#define VOS_HOW_SEND               0x01
#define VOS_HOW_BOTH               0x02


#define WINSOCK_REQ_VER            0x202

/*
the max string length of the network address, it is "XXX.XXX.XXX.XXX",
so it should be 16
*/
#define VOS_INET_ADDR_LEN 16

#if 0   /* added for 852t compilation problem in webui */
#ifdef VOS_CPU_TYPE
#if( VOS_CPU_TYPE == VOS_860 )

#ifndef sockaddr
#define sockaddr sockaddr_in
#endif

#endif
#endif
#endif


/*
 * Macros for number representation conversion.
 */
#ifndef VOS_NTOHL
#if VOS_BYTE_ORDER==VOS_BIG_ENDIAN
#define VOS_NTOHL(x)    (x)
#define VOS_HTONL(x)    (x)
#define VOS_NTOHS(x)    (x)
#define VOS_HTONS(x)    (x)
#else
#define VOS_NTOHL(x)    ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))

#define VOS_HTONL(x)    ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))

#define VOS_NTOHS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#define VOS_HTONS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#endif  /* _BYTE_ORDER==_LITTLE_ENDIAN */

#endif

typedef struct TIPS_hostent VOS_HOSTENTRY;
typedef struct tagIOVEC VOS_IOVEC_S;
typedef struct tagMSGHDR VOS_MSGHDR_S;


/***************************VOS socket operation func*************************/
#if (VOS_VXWORKS == VOS_OS_VER)

VOS_SOCKET VOS_Accept(VOS_SOCKET s, struct sockaddr *paddr, VOS_INT32 * paddrlen);

VOS_UINT32 VOS_Bind(VOS_SOCKET s, struct sockaddr *paddr, VOS_INT32 addrlen);

VOS_UINT32 VOS_Listen(VOS_SOCKET s, VOS_INT32 backlog);

VOS_UINT32 VOS_Recv(VOS_SOCKET s, VOS_CHAR * buf, VOS_INT32 len, VOS_INT32 flags);

VOS_UINT32 VOS_Send(VOS_SOCKET s, VOS_CHAR * buf, VOS_INT32 len, VOS_INT32 flags);

VOS_SOCKET VOS_Socket(VOS_INT32 af, VOS_INT32 type, VOS_INT32 protocol);

VOS_UINT32 VOS_CloseSocket(VOS_SOCKET s);

VOS_UINT32 VOS_IoctlSocket(VOS_SOCKET s, VOS_INT32 cmd, VOS_INT32* parg);

VOS_UINT32 VOS_Select(VOS_INT32 width, struct fd_set * preadfds, struct fd_set * pwritefds,
                       struct fd_set * pexceptfds, struct timeval * ptimeout  );

VOS_UINT32 VOS_SocketInit(VOS_VOID);

#endif

#ifdef  __cplusplus
#if  __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _V_SOCK_H */


