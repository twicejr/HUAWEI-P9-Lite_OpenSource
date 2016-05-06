/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_sock.h
*
*  Project Code: VISPV1R5
*   Module Name: Public
*  Date Created: 2005-05-10
*        Author: Liqiang17164
*   Description: VISP socket API的头文件，供非数通产品引用
*                申明与VISP socket API相关的函数格式、数据结构、宏定义
*                对本文件的必要说明：
*                1、由于VISP和VXWORKS的协议栈代码都来源于FreeBSD，导致
*                   必然存在着相同的数据结构定义、宏定义，因材，VISP必须对
*                   相关的数据结构定义、宏定义做封装，具体办法就是在定义之前
*                   添加"VRP"标识，以保证产品显示地调用VISP的API、数据结构
*                   和宏定义
*                2、对于非数通产品使用的VISP独有的数据结构、宏定义，直接在
*                   本文件中重复定义，以避免使用对应的VISP H文件后导致产品
*                   链编时产生大量的编译告警，很难解决，主要原因是DOPRA LIB +
*                   VISP LIB + 产品代码，混在一起编译非常难解决编译告警
*                3、本文件不在VISP内部使用，仅仅给非数通产品使用
*                4、tcpip_sock.h文件中唯一允许用户修改取值的宏定义是
*                   VRP_FD_SETSIZE，其余的宏定义、数据结构禁止修改
*                5、本文件的内容主要来自sock_pub.h/sock_com.h/
*                   sock_err.h/sock6_pub.h文件，因此当这些文件的对应定义发生
*                   变化时，一定要及时同步到本文件之中.本文件的维护方法是:
*                   VISP内部的相关定义修改后必须同步到本文件的对等定义之中；
*                   否则，会出问题的
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2005-05-10      Liqiang17164       Create
*  2005-05-16      Liqiang17164       根据朱昆意见---am4_pub.h文件中的数据结构
*                                     不需要封装，非数通产品可以直接include该文件
*  2007-09-20      z62474             同步A82D20312
*  2008-09-28      z62474             modify for BC3D00425
*******************************************************************************/

#ifndef _TCPIP_SOCK_H_
#define _TCPIP_SOCK_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cpluscplus */


/**********************************************************************
*                        1. Socket API对外提供的错误码
***********************************************************************/

/* 1.1Error Number for socket(tcp/udp/Rawip) same with Sock_err.h file */
#define VRP_EPERM           -1          /* Operation not permitted */
#define VRP_ENOENT          -2          /* No such file or directory */
#define VRP_ESRCH           -3          /* No such process */
#define VRP_EINTR           -4          /* Interrupted system call */
#define VRP_EIO             -5          /* Input/output error */
#define VRP_ENXIO           -6          /* Device not configured */
#define VRP_E2BIG           -7          /* Argument list too long */
#define VRP_ENOEXEC         -8          /* Exec format error */
#define VRP_EBADF           -9          /* Bad file descriptor */
#define VRP_ECHILD          -10         /* No child processes */
#define VRP_EDEADLK         -11         /* Resource deadlock avoided */ /* 11 was EAGAIN */
#define VRP_ENOMEM          -12         /* Cannot allocate memory */
#define VRP_EACCES          -13         /* Permission denied */
#define VRP_EFAULT          -14         /* Bad address */
#define VRP_ENOTBLK         -15         /* Block device required */
#define VRP_EBUSY           -16         /* Device busy */
#define VRP_EEXIST          -17         /* File exists */
#define VRP_EXDEV           -18         /* Cross-device link */
#define VRP_ENODEV          -19         /* Operation not supported by device */
#define VRP_ENOTDIR         -20         /* Not a directory */
#define VRP_EISDIR          -21         /* Is a directory */
#define VRP_EINVALID        -22         /* Invalid argument */
#define VRP_ENFILE          -23         /* Too many open files in system */
#define VRP_EMFILE          -24         /* Too many open files */
#define VRP_ENOTTY          -25         /* Inappropriate ioctl for device */
#define VRP_ETXTBSY         -26         /* Text file busy */
#define VRP_EFBIG           -27         /* File too large */
#define VRP_ENOSPC          -28         /* No space left on device */
#define VRP_ESPIPE          -29         /* Illegal seek */
#define VRP_EROFS           -30         /* Read-only file system */
#define VRP_EMLINK          -31         /* Too many links */
#define VRP_EPIPE           -32         /* Broken pipe */
#define VRP_EDOM            -33         /* Numerical argument out of domain */
#define VRP_ERANGEE         -34         /* Result too large */

/*1.2 non-blocking and interrupt i/o */
#define VRP_EAGAIN          -35         /* Resource temporarily unavailable */
#define VRP_EWOULDBLOCK     VRP_EAGAIN  /* Operation would block */
#define VRP_EINPROGRESS     -36         /* Operation now in progress */
#define VRP_EALREADY        -37         /* Operation already in progress */

/*1.3 ipc/network software -- argument errors */
#define VRP_ENOTSOCK        -38         /* Socket operation on non-socket */
#define VRP_EDESTADDRREQ    -39         /* Destination address required */
#define VRP_EMSGSIZE        -40         /* Message too LONG */
#define VRP_EPROTOTYPE      -41         /* Protocol wrong type for socket */
#define VRP_ENOPROTOOPT     -42         /* Protocol not available */
#define VRP_EPROTONOSUPPORT -43         /* Protocol not supported */
#define VRP_ESOCKTNOSUPPORT -44         /* Socket type not supported */
#define VRP_EOPNOTSUPP      -45         /* Operation not supported */
#define VRP_EPFNOSUPPORT    -46         /* Protocol family not supported */
#define VRP_EAFNOSUPPORT    -47         /* Address family not supported by protocol family */
#define VRP_EADDRINUSE      -48         /* Address already in use */
#define VRP_EADDRNOTAVAIL   -49         /* Can't assign requested address */

/*1.4 ipc/network software -- operational errors */
#define VRP_ENETDOWN        -50         /* Network is down */
#define VRP_ENETUNREACH     -51         /* Network is unreachable */
#define VRP_ENETRESET       -52         /* Network dropped connection on reset */
#define VRP_ECONNABORTED    -53         /* Software caused connection abort */
#define VRP_ECONNRESET      -54         /* Connection reset by peer */
#define VRP_ENOBUFS         -55         /* No buffer space available */
#define VRP_EQDROP          -56         /* Drops a packet because queue us full */
#define VRP_EISCONN         -57         /* Socket is already connected */
#define VRP_ENOTCONN        -58         /* Socket is not connected */
#define VRP_ESHUTDOWN       -59         /* Can't send after socket shutdown */
#define VRP_ETOOMANYREFS    -60         /* Too many references: can't splice */
#define VRP_ETIMEDOUT       -61         /* Operation timed out */
#define VRP_ECONNREFUSED    -62         /* Connection refused */
#define VRP_ELOOP           -63         /* Too many levels of symbolic links */
#define VRP_ENAMETOOLONG    -64         /* File name too long */
#define VRP_EHOSTDOWN       -65         /* Host is down */
#define VRP_EHOSTUNREACH    -66         /* No route to host */
#define VRP_ENOTEMPTY       -67         /* Directory not empty */
#define VRP_EPROCLIM        -68         /* Too many processes */
#define VRP_EUSERS          -69         /* Too many users */
#define VRP_EDQUOT          -70         /* Disc quota exceeded */

/*1.5 Network File System */
#define VRP_ESTALE          -71         /* Stale NFS file handle */
#define VRP_EREMOTE         -72         /* Too many levels of remote in path */
#define VRP_EBADRPC         -73         /* RPC struct is bad */
#define VRP_ERPCMISMATCH    -74         /* RPC version wrong */
#define VRP_EPROGUNAVAIL    -75         /* RPC prog. not avail */
#define VRP_EPROGMISMATCH   -76         /* Program version wrong */
#define VRP_EPROCUNAVAIL    -77         /* Bad procedure for program */
#define VRP_ENOLCK          -78         /* No locks available */
#define VRP_ENOSYS          -79         /* Function not implemented */
#define VRP_EFTYPE          -80         /* Inappropriate file type or format */
#define VRP_EAUTH           -81         /* Authentication error */
#define VRP_ENEEDAUTH       -82         /* Need authenticator */
#define VRP_ELAST           -83         /* Must be equal largest errno */

/*1.6 pseudo-errors returned inside kernel to modify return to process */
#define VRP_ERESTART        -84         /* restart syscall */
#define VRP_EJUSTRETURN     -85         /* don't modify regs, just return    */

#define VRP_ETASKCREATE     -86         /*don't create task */
#define VRP_ETASKDELETE     -87         /*don't delete task */
#define VRP_ETASKGETID      -88         /*have not task */
#define VRP_EPRISET         -89         /*can't set pritioy */
#define VRP_EEVRECEIVE      -90         /*time is out */
#define VRP_EEVSEND         -91         /*ev_nowait is select */
#define VRP_EQUCREATE       -92         /*node's object table full */
#define VRP_EQUDELETE       -93         /*delete queue fail */
#define VRP_EQUSEND         -94         /*send message fail */
#define VRP_EQURECEIVE      -95         /*receive message fail */
#define VRP_ESMCREATE       -96         /*sm create fail */
#define VRP_ESMDELETE       -97         /*sm delete fail */
#define VRP_ESMP            -98         /*sm p fail */
#define VRP_ESMV            -99         /*sm v fai */
#define VRP_ETCBCHECK       -100        /*has not find the tcb*/
#define VRP_ETCBCREATE      -101        /*has not create tcb*/
#define VRP_ETCBDELETE      -102        /*tcb has not delete*/
#define VRP_ENONBIO         -103
#define VRP_ENOASYNC        -104
#define VRP_ENOSETOWN       -105
#define VRP_ENOGETOWN       -106
#define VRP_ENOFIONBIO      -107
#define VRP_ENOFIOASYNC     -108
#define VRP_ENOFIOBACKCALL  -109
#define VRP_ECANTTCB        -107
#define VRP_EUIO            -108
#define VRP_ENOPROTO        -109
#define VRP_ENOMG           -110
#define VRP_EBLOCKING       -111
#define VRP_ENOTUDPSOCK     -112
#define VRP_ETCBINUSE       -113
#define VRP_ESNDBUFHIWAT    -114

#define VRP_ENOTBOUNDALGIN   -117    /*  Not Boundary algin Error for ARM   2006-5-12   x43050  */
#define VRP_EDISABLEDFORTEST -118    /*  VISP V100R005   2006-4-25   x43050  */


#define VRP_EMORECONTROL    -120
#define VRP_EVOIDINPCB      -121
#define VRP_EVOIDTCPCB      -122
#define VRP_EISSWITCHINGORSMOOTHING -123

#define VRP_ENOTMULTI               -124
#define VRP_EINPUTIF                -125
#define VRP_ENOTBIND                -126

#define VRP_EMD5LEN                 -127  /* MD5 p**s***d length is error */
#define VRP_EMD5MBFCONT             -128  /* continue MD5 mbuf failed */
#define VRP_EMD5PWDCONF             -129  /* add or modify MD5 p**s***d failed */


/*1.8 Others*/
#define VRP_EINVAL          -1
#define VRP_EFULLSOCK       -200    /*Socket缓存区满*/
#define VRP_EGADDR          -201    /*错误的组地址*/
#define VRP_ESADDR          -202    /*错误的源地址*/
#define VRP_EGOVERFLOW      -203    /*接口上配置的组超过限制*/
#define VRP_ESOVERFLOW      -204    /*socket上配置的源地址超过限制*/
#define VRP_EBLOCKSOURCE    -205    /*阻止一个本身已经被阻止的源地址（组相同）*/
#define VRP_EUNBLOCKSOURCE  -206    /*允许一个本身没有被阻止的源地址（组相同）*/
#define VRP_EADDSOURCE      -207    /*增加一个已经存在的源地址（组相同）*/
#define VRP_EDROPSOURCE     -208    /*删除一个不存在的源地址（组相同）*/
#define VRP_EFILTERMODE     -209    /*多播组过滤模式不允许该操作*/
#define VRP_ESOURCELISTNULL -210    /*源列表为空*/
#define VRP_EIGMPCOMPNULL   -211    /*IGMP组件为空*/
#define VRP_EIFTYPE         -212    /*错误的接口类型*/
#define VRP_EIFTHISBORD     -213    /*非本板接口*/
#define VRP_EGROUPNULL      -214    /*接口未加入指定多播组*/
#define VRP_EINVALIDVRF     -215    /*配置接口与当前的所属的VRF冲突或配置的VRF无效*/
#define VRP_ENEEDFRAG       -216    /*IP报文需要分片，但是设置了DF标识*/

#define VRP_ESOCKCLOSE      -217    /*socket异常，需要关闭*/

/*1.9 TCPIP_SetSockDbgFilter和TCPIP_SetSock6DbgFilter返回的错误码*/
#define VRP_SOCK_FILTOK          0
#define VRP_SOCK_FILTINUSE       1
#define VRP_SOCK_FILTTOOMUCH     2
#define VRP_SOCK_FILTNOTFOUND    3
#define VRP_SOCK_FILTNONE        4
#define VRP_SOCK_FILTADD         5
#define VRP_SOCK_FILTNULLPOINTER 6 /* pointer argument is NULL */
#define VRP_SOCK_PARAINVAILED    7

/*1.10 TCPIP_AddHost和TCPIP_AddHost6返回的错误码*/
#define VRP_ADD_HOST_ERR_TOO_MUCH_HOSTS           8
#define VRP_ADD_HOST_ERR_TOO_MUCH_IP_ADDR         9
#define VRP_ADD_HOST_ERR_ALREADY_ADDED            10
#define VRP_ADD_HOST_ERR_INVALID_HOST_NAME        11
#define VRP_ADD_HOST_ERR_INVALID_IP_ADDR          12
#define VRP_ADD_HOST_ERR_ISSWITCHINGORSMOOTHING   13

#define VRP_SOCK6_ERR_NOT_REGISTER                14
#define VRP_SOCK6_GET_HOST_FAIL                   15

/* 1.11 TCPIP_DelHost和TCPIP_Del6Host返回错误码 */
#define VRP_DEL_HOST_ERR_INVALID_NAME_OR_ADDR   16
#define VRP_DEL_HOST_ERR_MNAY_IP_ADDR           17
#define VRP_DEL_HOST_ERR_ISSWITCHINGORSMOOTHING 18 /* Added for SOCKET HA */






/**********************************************************************
*                        2. Socket API对外提供的宏定义
***********************************************************************/

/*2.1 select相关的宏定义*/

/* 单个任务下允许的socket数目的最大值，产品可以通过修改该宏定义来预设置单个任务下允许的socket数目的最大值，
而VISP内部始终是以3072作为上限值，VISP对select函数已经作了性能优化的设计，如果用户设置了32，那么在select操作时就按照
 32个socket数目来进行扫描，因此性能有保证.
    VRP_FD_SETSIZE宏是tcpip_sock.h文件中唯一允许用户修改取值的宏定义,取值必须是32的整数倍，取值范围是[32，3072].
即用户可以设置32/64/96/128。。。等，如果产品定义的值不为32的整数倍，则取默认值32 */
/*为支持OSPF规格扩展为32个，并且需要同时支持OSPFv3,OSPF,RIP,RIPng，因此从32扩展到128*/
/*Added by zhoushisong202096, 支持大规格SOCKET, 2013/11/7 */
#ifdef TCPIP_NOVRP_HUGE_SOCKET
#define VRP_FD_SETSIZE  128*1024
#else
/*Begin 同步 BC3D01799 liangjicheng 2009-07-27*/
#define VRP_FD_SETSIZE  3072
/*End 同步 BC3D01799 liangjicheng 2009-07-27*/
#endif

#define VRP_NFDBITS     0x20    /* number of bits in a long */
#define VRP_NBBY        8       /* number of bits in a byte */

/*Added by zhoushisong202096, 支持大规格SOCKET, 2013/11/7 */
#ifdef TCPIP_NOVRP_HUGE_SOCKET
#define VRP_FDSETLEN    4097    /* fd_set lenth, xxx long */
#else
/*Begin 同步 BC3D01799 liangjicheng 2009-07-28*/
#define VRP_FDSETLEN    97    /* fd_set lenth, xxx long */
/*End 同步 BC3D01799 liangjicheng 2009-07-28*/
#endif

#define VRP_TCPMD5PWDMAXLEN 256


#define VRP_FD_SET(n, p)    {\
            if ((n) > 0 ){\
            ((p)->fds_bits[(n)/VRP_NFDBITS] |= \
                        ((0x00000001) << ((n) % VRP_NFDBITS))); \
                    }\
                    }
#define VRP_FD_CLR(n, p)    ((p)->fds_bits[(n)/VRP_NFDBITS] &= \
                       ~((0x00000001) << ((n) % VRP_NFDBITS)))
#define VRP_FD_ISSET(n, p)  ((p)->fds_bits[(n)/VRP_NFDBITS] & \
                        ((0x00000001) << ((n) % VRP_NFDBITS)))
#define VRP_FD_ZERO(p)  { \
                        LONG xxx; \
                        for( xxx = 0; xxx<VRP_FDSETLEN; xxx++ ) \
                        { \
                            ((p)->fds_bits[xxx] = 0); \
                        } \
                    }

/*2.2 Add or Del Host相关的宏定义*/
#define VRP_IP_HOSTNAME_LEN    254
#define VRP_HostNameLen        VRP_IP_HOSTNAME_LEN+1
#define VRP_IPADDRMAXLEN       19
#define VRP_MAXHOSTADDRNO      8

/*2.3 异步SOCKET相关的宏定义*/
#define VRP_SE_ASYNC           0x0020
#define VRP_ASYN_MESSAGE       0X12345678

/*2.4 地址相关的宏定义*/
#define VRP_IP_VERSION         4       /*IPV4版本号*/
#define VRP_MAX_MAC_LEN        6
#define VRP_IP_BORROW          0x04    /* 主地址是借用的 */

#define VRP_INADDR_ANY              (ULONG)0x00000000L
#define VRP_INADDR_LOOPBACK         (ULONG)0x7f000001
#define VRP_INADDR_BROADCAST        (ULONG)0xffffffffL  /* must be masked */
#define VRP_INADDR_NONE             0xffffffff          /* -1 return */

/*2.5 字节序相关的宏定义*/
#ifndef vrp_ntohl
#define vrp_ntohl    VOS_NTOHL
#endif
#ifndef vrp_ntohs
#define vrp_ntohs    VOS_NTOHS
#endif
#ifndef vrp_htonl
#define vrp_htonl    VOS_HTONL
#endif
#ifndef vrp_htons
#define vrp_htons    VOS_HTONS
#endif


/*2.6 socket API涉及的地址类型、协议类型、SOCK选项类型*/

/* 2.6.1 Address families types */
#define VRP_AF_INET         2               /* internetwork: UDP, TCP, etc. */
#define VRP_AF_OSI          7
#define VRP_AF_INET6        29              /* added by mayun for IPv6 */

/* 2.6.2 protocol type number */
#define VRP_IPPROTO_IP          0       /* dummy for IP */
#define VRP_IPPROTO_ICMP        1       /* control message protocol */
#define VRP_IPPROTO_IGMP        2       /* group mgmt protocol */
#define VRP_IPPROTO_TCP         6       /* tcp */
#define VRP_IPPROTO_UDP         17      /* user datagram protocol */
#define VRP_IPPROTO_IPV6        41      /* IPv6 in IP */
#define VRP_IPPROTO_ICMPV6      58      /* ICMP over IPv6 */
#define VRP_IPPROTO_ISIS        124     /* ISIS over IPv4 */
#define VRP_IPPROTO_RAW         255     /* raw IP packet */

/* 2.6.3 socket types */
#define VRP_SOCK_STREAM         1       /* stream socket */
#define VRP_SOCK_DGRAM          2       /* datagram socket */
#define VRP_SOCK_RAW            3       /* raw-protocol interface */

/* 2.6.4 Maximum queue length specifiable by listen */
/* 修改原因:5的队列规格不能满足LTE需求,扩充为64,但为了不影响其他产品使用保留原有宏值VRP_SOMAXCONN */
#define VRP_SONEWMAXCONN    0x40       /* maximum queue length */
#define VRP_SOMAXCONN       0x5        /* queue length  is 5 */

#define VRP_SOL_SOCKET      0xffff

/* 2.6.5 Socket Option flags per-socket */
#define VRP_SO_DEBUG            0x00000001      /* turn on debugging info recording */
#define VRP_SO_ACCEPTCONN       0x00000002      /* socket has had listen() */
#define VRP_SO_REUSEADDR        0x00000004      /* allow local address reuse */
#define VRP_SO_KEEPALIVE        0x00000008      /* keep connections alive */
#define VRP_SO_DONTROUTE        0x00000010      /* just use interface addresses */
#define VRP_SO_BROADCAST        0x00000020      /* permit sending of broadcast msgs */
#define VRP_SO_USELOOPBACK      0x00000040      /* bypass hardware when possible */
#define VRP_SO_LINGER           0x00000080      /* linger on close if data present */
#define VRP_SO_OOBINLINE        0x00000100      /* leave received OOB data in line */
#define VRP_SO_REUSEPORT        0x00000200      /* allow local address & port reuse */
#define VRP_SO_SENDDATAIF       0x00000400      /* allow send data accross the specifed interface*/
#define VRP_SO_UDPCHECKSUM      0x00000800      /* set/unset udp output to calculate check sum */
#define VRP_SO_NSYNDROMESVR     0x00001000      /* set no parallel bgp server */
#define VRP_SO_SNDBYDSTMAC      0x00002000      /* set snd mac for dhcp relay */
#define VRP_SO_SETSRCADDR       0x00004000      /* set source address of output packet */
#define VRP_SO_SENDVPNID        0x00008000      /* VPN use this option */
#define VRP_SO_SENDBY_IF_NEXTHOP 0x00010000     /* set outif and nexthop of output packet mayun 2002-12-17 */
#define VRP_SO_SETKEEPALIVE     0x00020000      /* setting keepalive time value and count */
#define VRP_SO_SEQPACKET        0x00040000      /* sequnce tcp packet */
#define VRP_SO_SENDDATAPORT     0x00080000      /* added by mayun for GSR*/
#define VRP_SO_SETVLANID        0x00100000      /*set the vlanid of the socket */
#define VRP_SO_SENDBY_LSPV_FEC  0x00200000      /* Added by Yiyu for MPLS Ping/Traceroute */
#define VRP_SO_HEADCACHE        0x00400000
#define VRP_SO_SENDDATAIF_DONTSETTTL    0x00800000      /* allow send data accross the specifed interface,but not set TTL*/

#define VRP_SO_SETPEER_ADDR_PORT      0x04000000

#define VRP_SO_GETKEEPALIVE         VRP_SO_SETKEEPALIVE
#define VRP_SO_SETKEEPIDLE          0x02000000
#define VRP_SO_GETKEEPIDLE          VRP_SO_SETKEEPIDLE
/* End of likaikun */

#define VRP_SOCKET_LISTEN 1

/* 2.6.6 Additional options, not kept in so_options */
#define VRP_SO_SNDBUF           0x1001          /* send buffer size */
#define VRP_SO_RCVBUF           0x1002          /* receive buffer size */
#define VRP_SO_SNDLOWAT         0x1003          /* send low-water mark */
#define VRP_SO_RCVLOWAT         0x1004          /* receive low-water mark */
#define VRP_SO_SNDTIMEO         0x1005          /* send timeout */
#define VRP_SO_RCVTIMEO         0x1006          /* receive timeout */
#define VRP_SO_ERROR            0x1007          /* get error status and clear */
#define VRP_SO_TYPE             0x1008          /* get socket type */
#define VRP_SO_RCVVLANID        0x1009          /* get vlan info from mbuf */
#define VRP_SO_RCVPVCID         0x1010          /* get pvc info from mbuf */

/* 2.6.7 Options for use with [g/s]etsockopt at the IP level */
#define VRP_IP_OPTIONS              1   /* set/get IP per-packet options */
#define VRP_IP_HDRINCL              2   /* long; header is included with data */
#define VRP_IP_TOS                  3   /* long; IP type of service and preced. */
#define VRP_IP_TTL                  4   /* long; IP time to live */
#define VRP_IP_RECVOPTS             5   /* bool; receive all IP opts w/dgram */
#define VRP_IP_RECVRETOPTS          6   /* bool; receive IP opts for response */
#define VRP_IP_RECVDSTADDR          7   /* bool; receive IP dst addr w/dgram */
#define VRP_IP_RETOPTS              8   /* ip_opts; set/get IP options */
#define VRP_IP_MULTICAST_IF         9   /* u_char; set/get IP multicast i/f  */
#define VRP_IP_MULTICAST_TTL        10  /* u_char; set/get IP multicast ttl */
#define VRP_IP_MULTICAST_LOOP       11  /* u_char; set/get IP multicast loopback*/
#define VRP_IP_ADD_MEMBERSHIP       12  /* ip_mreq; add an IP group membership */
#define VRP_IP_DROP_MEMBERSHIP      13  /* ip_mreq; drop an IP group membership */
#define VRP_IP_MULTICAST_INTF       14  /* u_char; set/get IP multicast i/f */
#define VRP_IP_ADD_MEMBERSHIP_INTF  15  /* ip_mreq_intf; add an IP group */ /* membership given interface number */
#define VRP_IP_DROP_MEMBERSHIP_INTF 16  /* ip_mreq_intf; drop an IP group */ /* membership given interface number */
#define VRP_IP_ROUT_ALERT           17  /* ip_opts; set/get IP options mayun 2002-12-17 */
#define VRP_IP_TOS_TOTAL            18  /* long; IP type of service and preced. */
#define VRP_IP_BLOCK_SOURCE            19   /* block source from sourcelist*/
#define VRP_IP_UNBLOCK_SOURCE          20   /* unblock source from sourcelist*/
#define VRP_IP_ADD_SOURCE_MEMBERSHIP   21   /* add source to sourcelist or join multi_group with source*/
#define VRP_IP_DROP_SOURCE_MEMBERSHIP  22   /* drop source from sourcelist or leave group with deleting the last source*/
#define VRP_IP_ONLYRECVMULTICAST       23   /* for ospf socket only receive multicast ip pkt*/

/* 2.6.8 Options for use with [gs]etsockopt at the TCP level */
#define VRP_TCP_NODELAY                 1   /* set/get tcp nodelay option */
#define VRP_TCP_MAXSEG                  2   /* set/get tcp max segment size */
#define VRP_TCP_KEEPALIVE_IDLE          3   /* set/get TCP Keepalive timer value */
#define VRP_TCP_KEEPALIVE_CNT           4   /* set/get TCP Keepalive probe count */
#define VRP_TCP_KEEPALIVE_INTVL         5   /* set/get TCP Keepalive probing interval*/
#define VRP_TCP_MSL                     6   /* set/get TCP Maximum Segment Lifetime */
#define VRP_TCP_BINDFOREIGNADDR         7
#define VRP_TCP_SETPASSWORD             8   /* set/get tcp md5 authentication p**s***d */
#define VRP_TCP_ROUTINEBACKUP           9   /* set/get routine backup interval of tcp socket buffer */
#define VRP_TCP_SETPASSWORD_EX             10   /* set/get tcp md5 authentication p**s***d uing IP and mask*/



/* 2.6.9 Flag of send or recv */
#define VRP_MSG_OOB                 0x1     /* process out-of-band data */
#define VRP_MSG_PEEK                0x2     /* peek at incoming message */
#define VRP_MSG_DONTROUTE           0x4     /* send without using routing tables */
#define VRP_MSG_EOR                 0x8     /* data completes record */
#define VRP_MSG_TRUNC               0x10    /* data discarded before delivery */
#define VRP_MSG_CTRUNC              0x20    /* control data lost before delivery */
#define VRP_MSG_WAITALL             0x40    /* wait for full request or error */
#define VRP_MSG_DONTWAIT            0x80    /* this message should be nonblocking */

/* 2.6.10 macros for ioctl called by application */
#define VRP_FIOGETOWN           0x4004667C      /* Get owner of the socket */
#define VRP_FIOSBFREE           0x4004667B      /* Get bytes of socket send buffer's free space */
#define VRP_FIOREAD             0x4004667F      /* Get bytes in socket read buffer */
#define VRP_SIOCATMARK          0x40047307      /* Get OOB data in line */
#define VRP_FIOSETOWN           0x8004667C      /* Set owner of the socket */
#define VRP_FIOASYNC            0x8004667D      /* Set/Unset socket to receive */ /* Asyncronous signal */
#define VRP_FIONBIO             0x8004667E      /* Set/Unset socket non-blocking */
#define VRP_FIORECALL           0x8004668D      /* Set/Unset socket to call back */
#define VRP_FSENDDATAIF         0x80046684      /* Set/Unset socket send data out from a ifnet */
#define VRP_FNEEDBACKUP         0x8004668E      /* Set/Unset socket to backup */



/**********************************************************************
*                        3. IPV6 Socket API对外提供的特有的宏定义
***********************************************************************/

/* Options for use with [gs]etsockopt at the IPV6 level. First word of comment is data type; bool is stored in int. */
#define VRP_IPV6_SOCKOPT_RESERVED1      1   /* reserved for future use */
#define VRP_IPV6_UNICAST_HOPS           2   /* int; IP6 hops */
#define VRP_IPV6_MULTICAST_IF           3   /* u_int; set/get IP6 multicast i/f  */
#define VRP_IPV6_MULTICAST_HOPS         4   /* int; set/get IP6 multicast hops */
#define VRP_IPV6_MULTICAST_LOOP         5   /* u_int; set/get IP6 multicast loopback */
#define VRP_IPV6_JOIN_GROUP             6   /* ip6_mreq; join a group membership */
#define VRP_IPV6_LEAVE_GROUP            7   /* ip6_mreq; leave a group membership */
#define VRP_IPV6_PORTRANGE              8   /* int; range to choose for unspec port */
#define VRP_ICMP6_FILTER                9   /* icmp6_filter; icmp6 filter */

#define VRP_IPV6_CHECKSUM               10  /* int; checksum offset for raw socket */
#define VRP_IPV6_V6ONLY                 11  /* bool; make AF_INET6 sockets v6 only */

/* new socket options introduced in RFC2292bis */
#define VRP_IPV6_RTHDRDSTOPTS           11  /* ip6_dest; send dst option before rthdr */

#define VRP_IPV6_RECVPKTINFO            12  /* bool; recv if, dst addr */
#define VRP_IPV6_RECVHOPLIMIT           13  /* bool; recv hop limit */
#define VRP_IPV6_RECVRTHDR              14  /* bool; recv routing header */
#define VRP_IPV6_RECVHOPOPTS            15  /* bool; recv hop-by-hop option */
#define VRP_IPV6_RECVDSTOPTS            16  /* bool; recv dst option after rthdr */
#define VRP_IPV6_RECVRTHDRDSTOPTS       17  /* bool; recv dst option before rthdr */

#define VRP_IPV6_USE_MIN_MTU            18  /* bool; send packets at the minimum MTU */
#define VRP_IPV6_RECVPATHMTU            19  /* bool; notify an according MTU */

/* the followings are used as cmsg type only */
#define VRP_IPV6_PATHMTU                20  /* 4 bytes int; MTU notification */
#define VRP_IPV6_REACHCONF              21  /* no data; ND reachability confirm */

/* more new socket options introduced in RFC2292bis */
#define VRP_IPV6_PKTINFO                22  /* in6_pktinfo; send if, src addr */
#define VRP_IPV6_HOPLIMIT               23  /* int; send hop limit */
#define VRP_IPV6_NEXTHOP                24  /* sockaddr; next hop addr */
#define VRP_IPV6_HOPOPTS                25  /* ip6_hbh; send hop-by-hop option */
#define VRP_IPV6_DSTOPTS                26  /* ip6_dest; send dst option befor rthdr */
#define VRP_IPV6_RTHDR                  27  /* ip6_rthdr; send routing header */

#define VRP_IPV6_TCLASS                 28  /* int; send traffic class value */
#define VRP_IPV6_RECVTCLASS             29  /* bool; recv traffic class values */
#define VRP_IPV6_DONTFRAG               30
#define VRP_IPV6_TOS                    31  /* ipv6 precedence */
#define VRP_IPV6_FLOWID                 32  /* int; send flow ID value */

/* Defaults and limits for options */
#define VRP_IPV6_DEFAULT_MULTICAST_HOPS 1   /* normally limit m'casts to 1 hop  */
#define VRP_IPV6_DEFAULT_MULTICAST_LOOP 1   /* normally hear sends if a member  */


/**********************************************************************
*                        4. Socket API对外提供的数据结构定义
***********************************************************************/

/*select*/
typedef struct vrp_fd_set
{
    LONG fds_bits[VRP_FDSETLEN];
}vrp_fd_set;

struct vrp_timeval
{
    LONG  tv_sec;       /* no. of seconds */
    LONG  tv_usec;      /* no. of micro seconds */
};

/* Structure used for manipulating linger option */
struct vrp_linger
{
    LONG l_onoff;        /* option on/off */
    LONG l_linger;       /* linger time */
};

/* Structure used for manipulating address in bind,sendto and so on */
struct vrp_sockaddr
{
    USHORT sa_family;
    CHAR   sa_data[14];
};
/* 如果产品包含了windows系统头文件，s_addr被定义为一个宏，此处编译有问题 */
#if (VRP_OS_WINDOWS == VRP_YES)
#ifdef s_addr
#undef s_addr
#endif
#endif

typedef struct vrp_in_addr
{
    ULONG s_addr; /* address of the socket */
}vrp_in_addr;

typedef struct vrp_sockaddr_in
{
    unsigned char        sin_len;       /* zy */
    unsigned char        sin_family;    /* must be AF_INET */
    unsigned short       sin_port;      /* 16-bit port number */
    struct vrp_in_addr   sin_addr;      /* 32-bit address */
    CHAR                 sin_zero[8];   /* must be 0 */
}vrp_sockaddr_in;

/*used for bind ,sendto,recvfrom */
typedef struct vrp_sockaddr_isis
{
    UCHAR  sin_chLen;
    UCHAR  sin_chFamily;         /* must be AF_OSI, 该项必须填写*/
    UCHAR  ucPadding_1[2];
    ULONG  ulIfIndex  ;          /* 绑定的接口索引 */
    ULONG  ulVlinkIndex;         /* vlink 索引     */
    USHORT usMacLen;             /* physical地址长度    */
    UCHAR  ucPadding_2[2];
    UCHAR  SrcMac[8];            /* 源physical地址      */
    UCHAR  DstMac[8];            /* 目的physical地址    */
}vrp_sockaddr_isis;

/* Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP */
typedef struct vrp_ip_mreq
{
    struct vrp_in_addr   imr_mcastaddr; /* IP multicast address of group */
    ULONG                imr_ifindex;   /* local address of interface */
}vrp_ip_mreq;

/* Argument structure for IP_ADD_MEMBERSHIP_INTF and IP_DROP_MEMBERSHIP_INTF */
typedef struct vrp_ip_mreq_intf
{
    struct vrp_in_addr imrif_mcastaddr; /* IP multicast address of group */
    LONG               imrif_ifno;      /* local interface number */
}vrp_ip_mreq_intf;

/*--------------------------------------------------------------------------*/
/* Argument structure for IP_ADD_SOURCE_MEMBERSHIP, IP_DROP_SOURCE_MEMBERSHIP */
/* IP_BLOCK_SOURCE AND IP_UNBLOCK_SOURCE                                    */
/*--------------------------------------------------------------------------*/
typedef struct vrp_ip_mreq_source
{
    struct vrp_in_addr imr_mcastaddr;  /*  IP multicast address of group  */
    struct vrp_in_addr imr_msrcaddr;   /*  address of source for group */
    ULONG   imr_ifindex;    /*  local address of interface   */
}vrp_ip_mreq_source;

/* following two used for recvmsg and sendmsg functions */
typedef struct vrp_iovec
{
    CHAR *iov_base;         /* base address */
    LONG iov_len;           /* buffer length */
}vrp_iovec;

typedef struct vrp_msghdr
{
    CHAR*       msg_name;       /* optional address */
    SHORT       msg_namelen;    /* size of address */
    UCHAR       ucPadding_1[2];
    vrp_iovec*  msg_iov;        /* scatter/gather array */
    SHORT       msg_iovlen;     /* # elements in msg_iov */
    UCHAR       ucPadding_2[2];
    CHAR*       msg_control;    /* access rights */
    SHORT       msg_controllen; /* length of the rights buffer */
    SHORT       msg_flags;
}vrp_msghdr;

typedef struct vrp_cmsghdr
{
    SHORT   cmsg_len;       /* data byte count, including hdr */
    SHORT   cmsg_level;     /* originating protocol */
    SHORT   cmsg_type;      /* protocol-specific type */
    CHAR    cmsg_data[2];   /* assign byte */
}vrp_cmsghdr;

/* following one used for gethostbyaddr/gethostbyaddr6/gethostbyname/gethostbyname6 */
struct  vrp_hostent 
{
    CHAR    h_name[VRP_IP_HOSTNAME_LEN + 1];            /* official name of host */ /* 10->21 by mayun 20010608 */
    UCHAR   ucPadding[4-((VRP_IP_HOSTNAME_LEN+1)%4)];
    CHAR    h_aliases[4][VRP_IP_HOSTNAME_LEN + 1];      /* alias list */
    SHORT   h_addrtype;             /* host address type */
    SHORT   h_length;               /* length of address */
    CHAR    h_addr_list[4][20];     /* list of addresses */
#define vrp_h_addr  h_addr_list[0]  /* address, for backward compat */
};

/* struct used by application to send data direct out of a interface this is defined in sockcom.h also, the two must be altered at same time */
typedef struct vrp_senddataif
{
    ULONG           ulIfIndex;
    ULONG           ulSrcAddr;
}vrp_senddataif;

typedef struct VRP_KEEPALIVESET
{
    USHORT usKeepintvl;       /* second */
    USHORT usKeepcount;       /* keepintvl's count */
}VPR_KEEPALIVESET_S;

/* struct used by application to set socket to be a asyn socket this is defined in sockcom.h also, the two must be altered at same time */
typedef struct  vrp_asynsockset
{
    ULONG           ulQueueID;
    ULONG           ulPointer;
    ULONG           ulWakeTaskID;
}vrp_asynsockset;

/* used in callback function to get information about data */
typedef struct vrp_callbackinfo
{
    LONG iFd;
    LONG iDataLen;
    LONG iFlags;
    struct vrp_sockaddr_in stFromAddr;
    struct vrp_in_addr stDstAddr;
    ULONG ulUserData;
}vrp_callbackinfo;

/* set socket to callback when there is data input */
typedef struct  vrp_recallsockset
{
    ULONG (*so_pfCallBack)( CHAR *, vrp_callbackinfo * );
    CHAR  *pszDataBuf;
    ULONG ulBufLen;
    ULONG ulUserData;
}vrp_recallsockset;

/*--------------------------------------------------------------------------*/
/* struct contain message which is send to application's queue by           */
/* AsynWakeUp(), the application get this message to determind what to do   */
/* this is defined in asynsock.h also, the two must be altered at same time */
/*--------------------------------------------------------------------------*/
typedef struct vrp_asynsockmsg
{
    ULONG    ulMsgType;    /*表明此消息是异步SOCKET发送的消息,数值为ASYN_MESSAGE*/
    ULONG    ulPointer;    /*原先是src分配的buffer, 现表明是src指定的pointer *//*绑定于异步SOCKET的一个数值*/
    LONG     iError;
#define SUCCEEDED           0
#define FAILED              1

    /* Modefied by fengjing209023 ASYNMSG_S.FD.type.defect 将FD由16位改为24位,涉及接口变更，需知会产品 */
    /* 注意: VOS_Que_Write函数写的消息最大长度为16字节(32bit环境)，故该结构体定义不能超过16字节*/
    unsigned usFd:24;
    unsigned usEventType:8;
    /* Modefied end */    
    
#define VRP_ASYN_READ       1
#define VRP_ASYN_WRITE      2
#define VRP_ASYN_CONNECT    3
#define VRP_ASYN_CLOSE      4
#define VRP_ASYN_ACCEPT     5
#define VRP_ASYN_PEERCLOSE  6
#define VRP_ASYN_KEEPALIVEDOWN  7

}vrp_asynsockmsg;

typedef struct  VRP_ASYNSOCKET
{
    ULONG           ulQueueID;
    ULONG           ulPointer;
    ULONG           ulWakeTaskID;
}VRP_ASYNSOCKET_S;

/* following onw used for TCPIP_GetHost/TCPIP_GetHost6/gethostbyname/gethostbyname6 */
typedef struct tagTCPIP_SOCKHOST_S
{
    CHAR  HostName[VRP_HostNameLen];
    UCHAR ucPadding_1[4-((VRP_HostNameLen)%4)];
    CHAR  HostIP[VRP_MAXHOSTADDRNO][VRP_IPADDRMAXLEN];
    UCHAR ucPadding_2[4-(((VRP_MAXHOSTADDRNO)*(VRP_IPADDRMAXLEN))%4)];
    LONG  AddrNo;
    ULONG ulAge;
    CHAR  Flags;
    CHAR  type;
    UCHAR ucPadding_3[2];
}TCPIP_SOCKHOST_S;

/* 设置MD5pwd对应的数据结构 */
typedef struct tagmd5password
{
    ULONG sin_addr;            /* 32-bit address of the socket */
    CHAR  szMd5Password[VRP_TCPMD5PWDMAXLEN];  /* MD5 p**s***d(len < 256 bit) */
}VRP_SOCKMD5PWD_S;


/* adding the structure for extended TCPMD5 functionality using new socket option TCP_SETPASSWORD_EX for wildcard addres and mask*/
typedef struct tagmd5password_ex
{
    ULONG ulsin_addr;            /* 32-bit address of the socket */
    ULONG ulmask;                 /* subnet mask*/
    CHAR  szMd5Password[VRP_TCPMD5PWDMAXLEN];  /* MD5 p**s***d(len < 256 bit) */
}VRP_SOCKMD5PWD_EX_S;


/**********************************************************************
*               5. IPV6 Socket API对外提供的特有数据结构定义
***********************************************************************/

/* IPv6 address数据结构,该结构定义了IPv6地址的内容。
   描述了IPv6地址128bit的具体内容，采用共用体来方便对地址字段的操作 */
#ifndef _VRP_IN6ADDR_S
#define _VRP_IN6ADDR_S
typedef   struct    tagVRPIN6Addr
{
    union
    {
        UCHAR   u6_ucaddr[16];
        USHORT  u6_usaddr[8];
        ULONG   u6_uladdr[4];
    } vrp_u6_addr;    /* 128-bit IP6 address */
}VRP_IN6ADDR_S;
#endif

/* 为了引用方便，进行如下宏定义*/
#define vrp_s6_addr      vrp_u6_addr.u6_ucaddr
#define vrp_s6_addr8     vrp_u6_addr.u6_ucaddr
#define vrp_s6_addr16    vrp_u6_addr.u6_usaddr
#define vrp_s6_addr32    vrp_u6_addr.u6_uladdr

typedef struct tagVRPSOCKADDR_IN6 {
    UCHAR       ucSin6_len;         /* length of this struct(sa_family_t)*/
    UCHAR       ucSin6_family;      /* AF_INET6 (sa_family_t) */
    USHORT      usSin6_port;        /* Transport layer port # (in_port_t)*/
    ULONG       ulSin6_flowinfo;    /* IP6 flow information */
    VRP_IN6ADDR_S   stSin6_addr;    /* IP6 address */
    ULONG       ulSin6_scope_id;    /* scope zone index */
}VRP_SOCKADDR_IN6_S;

/* socket6异步回调方式传给回调函数的参数,
   如果用户设置socker回调属性时指定了接收缓冲区,则将报文数据拷贝到用户指定的缓冲区;
   否则则将报文MBUF交给回调函数,此时回调函数中需要负责报文MBUF的释放;
*/
typedef struct tagVRPSo6_CallbackInfo
{
    LONG lFd;                       /* 收到报文的socket id */
    LONG lDataLen;                  /* 交给回调函数的数据长度 */
    LONG lFlags;                    /* 一般情况下为0: 表示交给回调函数的是完整的报文数据;
                                       MSG_EOR: 表示TCP6链接收到了对端的断连请求;
                                       MSG_TRUNC: 表示UDP6/RAWIP6报文被截断,用户提供的接收缓冲区比报文长度小则将报文截断,
                                       只将报文前部分数据交给回掉函数; */
    VRP_SOCKADDR_IN6_S stFromAddr;  /* 报文中的源地址信息,地址和端口号为网络序 */
    VRP_IN6ADDR_S stDstAddr;        /* 报文中的目的地址,网络序 */
    ULONG ulUserData;               /* 用户注册回掉函数时传入的参数 */
}VRP_SO6_CALLBACKINFO_S;

/* 流缓存头最大长度 */
#define HC_MAX_HDR   64

/* HEADCACHE 实体 */
typedef struct tagTCPIP_HEADCACHE_ENTRY
{
    ULONG      ulFlag;                /* Head Cache标志，表明Head Cache的状态，具体请见下面的宏定义*/
    ULONG      ulSrcIP;               /* 源地址*/
    ULONG      ulDstIp;               /* 目的地址*/
    VRP_IN6ADDR_S  stSrcIP6;              /* IPv6 源地址   */
    VRP_IN6ADDR_S  stDstIP6;              /* IPv6 目的地址 */
    ULONG      ulIpPro;               /* 协议号*/
    ULONG      ulIfIndex;             /* 出接口索引*/
    ULONG      ulNextHop;             /* 下一跳的地址*/
    VRP_IN6ADDR_S stNextHop6;             /* IPv6 下一跳地址 */
    USHORT     usSrcPort;             /* 本地端口号*/
    USHORT     usDstPort;             /* 远端端口号*/
    UCHAR      aucHead[HC_MAX_HDR];   /* 报文首部，(UDP首部)+IP首部+链路层首部*/
    ULONG      ulHeadLen;             /* 报文首部长度*/
    ULONG      ulNormalSendTotal;     /* 统计走正常流程报文数 */
    ULONG      ulHCSendTotal;         /* 统计流发送成功报文数（走流发送流程报文数）*/
}TCPIP_HEADCACHE_ENTRY_S;

typedef struct tagTCPIP_SOCK_SEARCH_IN_S
{
    struct vrp_sockaddr_in *pstLaddr; /* 32-bit Local address + local port*/
    struct vrp_sockaddr_in *pstFaddr; /* 32-bit Remote address + Remote port*/
    ULONG ulVrfIndex;                /*vrf index*/
    UCHAR ucPro;               /*  8-bit Protocal */
    UCHAR ucRes[7];            /* 56-bit Reserved */
} TCPIP_SOCK_SEARCH_IN_S;

typedef struct tagTCPIP_SOCK_SEARCH_OUT_S
{
    ULONG ulSockId;          /* socket id */
    ULONG ulTcpState;        /* TCP连接状态 */
} TCPIP_SOCK_SEARCH_OUT_S;

typedef struct  tagTCPIP_SOCKPQNODEINFO
{
    ULONG ulVrfIndex;                /*vrf index*/
    ULONG ulTcpState;                /*TCP 状态*/
    struct vrp_sockaddr_in *pstLaddr;/* 32-bit Local address + local port*/
    struct vrp_sockaddr_in *pstFaddr;/* 32-bit Remote address + Remote port*/
} TCPIP_SOCKPQNODEINFO_S;

typedef struct  tagTCPIP_SOCKPQINFO
{
    ULONG   ulConfiguredQLen;   /* 配置的监听队列长度 */
    ULONG   ulActualQLen;       /* 目前监听队列的总长度(Q0或Q，分别查询) */
    ULONG   ulBacklogDrop;      /* 因超过Backlog而丢弃的socket个数 */
    ULONG   ulTimeODrop;        /* 因超时而丢弃的socket个数 */
} TCPIP_SOCKPQINFO_S;

typedef struct tagTCPIP_SOCK_QOS_INFO_S
{
    ULONG ulRexmtPercent;   /* 消息重传比例，百分比 */
    ULONG ulAvgRtt;         /* 消息平均时延 */
    ULONG ulAvgRttWarp;     /* 消息平均时延偏差 */
} TCPIP_SOCK_QOS_INFO_S;
/**********************************************************************
*               6. Socket API声明
***********************************************************************/
/*如果需要支持双栈(如Vxworks和VISP)下的Socket编程，则产品makefile需要定义TCPIP_DOUBLESOCK，
  否则用户在调用socket或调用vrp_socket等时，实际均指向VISP的Socket API(即单栈)*/

/* 6.1 标准socket API函数申明 */
extern LONG vrp_socket(LONG iFamily, LONG iType, LONG iProtocol);
extern LONG vrp_bind(LONG iFd, struct vrp_sockaddr_in *pSockAddr, LONG nAddrLen);
extern LONG vrp_unbind(LONG iFd, struct vrp_sockaddr_in *pSockAddr, LONG nAddrLen);
extern LONG vrp_listen(LONG iFd, LONG iBackLog);
extern LONG vrp_accept(LONG iFd, struct vrp_sockaddr_in *pAddr, LONG *pAddrLen);
extern LONG vrp_connect(LONG iFd, struct vrp_sockaddr_in *pAddr, LONG nAddrLen);
extern LONG vrp_read(LONG iFd, CHAR *pString, LONG nLen);
extern LONG vrp_readv(LONG iFd, struct vrp_iovec *pIovec0, LONG nIovCnt);
extern LONG vrp_recv(LONG iFd, CHAR *pBuf, LONG nLen, LONG iFlags);
extern LONG vrp_recvfrom(LONG iFd, CHAR *pBuf, LONG nLen, LONG iFlags,
                         struct vrp_sockaddr_in *pFrom, LONG *pFromLen);
extern LONG vrp_recvmsg(LONG iFd,struct vrp_msghdr *pMsg,LONG iFlags);
extern LONG vrp_write(LONG iFd, CHAR *pString,LONG nLen);
extern LONG vrp_writev(LONG iFd, struct vrp_iovec *pIovec0, LONG nIovCnt);
extern LONG vrp_send(LONG iFd, CHAR *pString, LONG nLen, LONG iFlags);
extern LONG vrp_sendto(LONG iFd, CHAR *pString, LONG nLen, LONG iFlags,
                       struct vrp_sockaddr_in *pAddr, LONG nAddrLen);
extern LONG vrp_sendmsg(LONG iFd, struct vrp_msghdr *pMsg, LONG iFlags);
extern LONG vrp_shutdown(LONG iFd, LONG iHow);
extern LONG vrp_select(LONG iNd, struct vrp_fd_set *pIn, struct vrp_fd_set *pOut,
                       struct vrp_fd_set *pEx,struct vrp_timeval *pTv0);
extern LONG vrp_ioctl(LONG iFd, ULONG ulReq, CHAR *pVal);
extern LONG vrp_close(LONG iFd);
extern LONG vrp_setsockopt(LONG iFd, LONG iLevel, LONG iOptName, CHAR *pOptVal, LONG nOptLen);
extern LONG vrp_getsockopt(LONG iFd, LONG iLevel, LONG iOptName, CHAR *pOptVal, LONG *pOptLen);
extern LONG vrp_getsockname(LONG iFd, struct vrp_sockaddr_in *pAddr, LONG *pAddrLen);
extern LONG vrp_gethostname(CHAR *pName, LONG iNameLen);
extern LONG vrp_getpeername(LONG iFd, struct vrp_sockaddr_in *pAddr, LONG *pAddrLen);
extern struct hostent *vrp_gethostbyaddr(CHAR *pAddr, LONG iLen, LONG iType);
extern struct hostent *vrp_gethostbyname(CHAR *pName);

#ifndef TCPIP_DOUBLESOCK
#define     socket(a,b,c)    vrp_socket(a,b,c)
#define     bind(a,b,c)    vrp_bind(a,b,c)
#define     unbind(a,b,c)   vrp_unbind(a,b,c)
#define     listen(a,b)    vrp_listen(a,b)
#define     accept(a,b,c)    vrp_accept(a,b,c)
#define     connect(a,b,c)    vrp_connect(a,b,c)
#define     read(a,b,c)        vrp_read(a,b,c)
#define     readv(a,b,c)    vrp_readv(a,b,c)
#define     recv(a,b,c,d)    vrp_recv(a,b,c,d)
#define     recvfrom(a,b,c,d,e,f)    vrp_recvfrom(a,b,c,d,e,f)
#define     recvmsg(a,b,c)    vrp_recvmsg(a,b,c)
#define     write(a,b,c)    vrp_write(a,b,c)
#define     writev(a,b,c)    vrp_writev(a,b,c)
#define     send(a,b,c,d) vrp_send(a,b,c,d)
#define     sendto(a,b,c,d,e,f)    vrp_sendto(a,b,c,d,e,f)
#define     sendmsg(a,b,c)    vrp_sendmsg(a,b,c)
#define     shutdown(a,b)    vrp_shutdown(a,b)
#define     select(a,b,c,d,e)    vrp_select(a,b,c,d,e)
#define     ioctl(a,b,c)    vrp_ioctl(a,b,c)
#define     close(a)    vrp_close(a)
#define     setsockopt(a,b,c,d,e)    vrp_setsockopt(a,b,c,d,e)
#define     getsockopt(a,b,c,d,e)    vrp_getsockopt(a,b,c,d,e)
#define     getsockname(a,b,c)    vrp_getsockname(a,b,c)
#define     gethostname(a,b)    vrp_gethostname(a,b)
#define     getpeername(a,b,c)    vrp_getpeername(a,b,c)
#define     gethostbyaddr(a,b,c)   vrp_gethostbyaddr(a,b,c)
#define     gethostbyname(a)   vrp_gethostbyname(a)
#endif

/* 6.2 标准IPV6 socket API函数申明 */
extern LONG   vrp_inet_pton(USHORT usFamily,  const CHAR *szSrcAddr, VOID *pDstAddr);
extern CHAR * vrp_inet_ntop(USHORT usFamily, const CHAR *pSrcAddr, CHAR *szDstAddr, ULONG ulAddrLen);
extern struct hostent * vrp_gethostbyname6(CHAR *pName, ULONG ulPolicy);
extern struct hostent * vrp_gethostbyaddr6(CHAR *pAddr,LONG iLen,LONG iType);

#ifndef TCPIP_DOUBLESOCK
#define     inet_pton(a,b,c)     vrp_inet_pton(a,b,c)
#define     inet_ntop(a,b,c,d)     vrp_inet_ntop(a,b,c,d)
#define     gethostbyname6(a,b)     vrp_gethostbyname6(a,b)
#define     gethostbyaddr6(a,b,c)     vrp_gethostbyaddr6(a,b,c)
#endif

/* 6.3 VISP扩展的socket API函数申明 */
extern LONG vrp_CopySocket(ULONG ulTaskIdFrom, ULONG ulTaskIdTo, LONG iFd, LONG iAlterFd);
extern ULONG vrp_InetAddr(CHAR *pIpChar);
extern LONG vrp_getrcvifindex( LONG iFd, ULONG *usIfIndex );
extern ULONG vrp_getsrcbydst(ULONG ulDstAddr);

#ifndef TCPIP_DOUBLESOCK
#define     CopySocket(a,b,c,d)     vrp_CopySocket(a,b,c,d)
#define     InetAddr(a)   vrp_InetAddr(a)
#define     getrcvifindex(a,b)   vrp_getrcvifindex(a,b)
#define     getsrcbydst(a) vrp_getsrcbydst(a)
#endif

/* 6.4 VISP提供的可维可测相关的Socket API */
typedef ULONG (*DrvDataSendDirect_HOOK_FUNC)(ULONG dwIfIndex,
                                             vrp_iovec *msg_pIov,
                                             SHORT msg_nIovLen,
                                             VOID *pHeadBuf,
                                             ULONG ulHlen);
/* 本段开启端口时回调通知产品 */
typedef struct tagSOCKNOTIFYINFO
{
    ULONG   ulSockId;          /* socket id */    
    ULONG   ulTaskId;          /* 使用本socket的TASK ID */ 
    ULONG   ulSrcIp;           /* 源地址，主机序 */
    USHORT  usSrcPort;         /* 源端口号，主机序 */
    USHORT  usSockState;       /* socket类型，监听socket或者其他 */
    ULONG   ulSockType;        /* 套接字类型，SOCK_STREAM(1),SOCK_DGRAM(2)*/
}SOCKNOTIFYINFO_S;

typedef ULONG (*SOCK_PORT_NOTIFY_HOOK_FUNC)(SOCKNOTIFYINFO_S *pstData);

typedef struct tagSOCK_GLOBLE
{
    USHORT usAutoPortStart; /* 动态分配端口号起始值,1~65535，默认值为49152*/
    USHORT usAutoPortEnd;   /* 动态分配端口号结束值,1~65535，默认值为65535*/
}SOCK_GLOBLE_S;


/*******************************************************************************
*    Func Name: TCPIP_ShowSocket
*  Description: 显示根据输入参数显示socket的相关信息
*        Input: ULONG ulSockType:需要显示的类型
*               ULONG ulTaskId:需要显示的socket所属的任务ID
*               ULONG ulSockId:指定特定任务的Socket
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID  TCPIP_ShowSocket(ULONG ulSockType, ULONG ulTaskId, ULONG ulSockId);
/*******************************************************************************
*    Func Name: TCPIP_ShowSocketTCB
*  Description: 显示特定任务TCB信息,当输入为0时，显示当前任务信息。
*        Input: ULONG ulTaskId:指定的任务ID
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID  TCPIP_ShowSocketTCB(ULONG ulTaskId);
/*******************************************************************************
*    Func Name: TCPIP_ShowSockInfo
*  Description: 显示SOCKET相关信息
*        Input: ULONG ulTaskId:任务ID
*               ULONG iFd:接口描述字
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID  TCPIP_ShowSockInfo(ULONG ulTaskId, ULONG iFd);
/*******************************************************************************
*    Func Name: TCPIP_ShowSockBufInfo
*  Description: 显示发送接收缓冲区相关信息
*        Input: ULONG ulTaskId:任务ID
*               ULONG iFd:接口描述字
*               ULONG ulBufType:SOCKET_SENDBUF发送缓冲区，SOCKET_RECVBUF接收缓冲区
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID  TCPIP_ShowSockBufInfo(ULONG ulTaskId, ULONG iFd, ULONG ulBufType);
/*******************************************************************************
*    Func Name: TCPIP_SetSockStatus
*  Description: 提供给SOCKET4/6模块, 进行设置SOCKET功能的使能/去使能
*        Input: ULONG iFamily:协议域
*               ULONG ulSetYes: 0 去使能 1 使能
*       Output:
*       Return: VOS_OK  操作成功
*               VOS_ERR 操作失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_SetSockStatus(ULONG iFamily, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_GetSockStatus
*  Description: 提供给SOCKET4/6模块, 进行查询SOCKET功能的使能/去使能
*        Input: ULONG iFamily:协议域
*       Output: ULONG* pulFlag:查询出的结果 (0 去使能 1 使能)
*       Return: VOS_OK  操作成功
*               VOS_ERR 操作失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_GetSockStatus(ULONG iFamily, ULONG* pulFlag);
/*******************************************************************************
*    Func Name: TCPIP_GetHCInfo
*  Description: 对设置了流发送的SOCKET4根据目的IP和端口获取缓存表项信息
*        Input: ULONG ulTaskId:创建socket的任务ID
*               LONG iFd:socket描述符
*               ULONG ulDstIp:目的地址（网络序）
*               USHORT usDstPort:目的端口号（网络序）
*       Output: TCPIP_HEADCACHE_ENTRY_S *pstEntry:查找成功则输出缓存对应IP和端口号的缓存结点信息
*       Return: VOS_OK  操作成功
*               VOS_ERR 操作失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_GetHCInfo(ULONG ulTaskId, LONG iFd,ULONG ulDstIp, USHORT usDstPort, TCPIP_HEADCACHE_ENTRY_S *pstEntry);
/*******************************************************************************
*    Func Name: TCPIP_AddHost
*  Description: 设置远程主机名和地址
*        Input: CHAR * stHostName:指向主机名称的字符串
*               CHAR * stHostIP:要设置的地址，ASCII码存储形式，以'\0' 结尾
*       Output:
*       Return: VOS_OK  操作成功
*               ADD_HOST_ERR_TOO_MUCH_HOSTS 失败，已经达到可以存储的最大主机数目（50）
*               ADD_HOST_ERR_ALREADY_ADDED  已经有一样的配置存在
*               ADD_HOST_ERR_INVALID_HOST_NAME 无效的主机名(如主机名为空或长度超过254)
*               ADD_HOST_ERR_INVALID_IP_ADDR   无效的地址(地址取值范围0.0.0.0 ~ 255.255.255.255，不能为空)
*               ADD_HOST_ERR_ISSWITCHINGORSMOOTHING 正在在手动倒换或平滑处理中，禁止用户配置操作
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_AddHost(CHAR * stHostName, CHAR * stHostIP);
/*******************************************************************************
*    Func Name: TCPIP_DelHost
*  Description: 从协议栈中删除远程主机名和地址
*        Input: LONG lKind:DELHOSTBYNAME 或者 DELHOSTBYNAMEADDR
*               CHAR *stHostName:指向主机名称的字符串
*               CHAR *stHostIP: 要设置的地址，ASCII码存储形式，以'\0' 结尾
*       Output:
*       Return: VOS_OK  操作成功
*               DEL_HOST_ERR_INVALID_NAME_OR_ADDR   失败，没有发现有输入的主机IP对或参数输入无效
*               DEL_HOST_ERR_MNAY_IP_ADDR           预留参数（为了扩展一个主机名可以配置多个地址的情况）
*               DEL_HOST_ERR_ISSWITCHINGORSMOOTHING 正在在手动倒换或平滑处理中，禁止用户配置操作
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_DelHost(LONG lKind,CHAR *stHostName, CHAR *stHostIP);
/*******************************************************************************
*    Func Name: TCPIP_GetHost
*  Description: 根据相应的索引得到对应的远程主机结构
*        Input: ULONG ulIndex:需要查找的主机结构在存储主机结构的数组中的索引下标
*               TCPIP_SOCKHOST_S *pSockHost:指向返回结果的指针
*       Output:
*       Return: VOS_OK  操作成功
*               EINVALID   输入参数无效
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
LONG  TCPIP_GetHost(ULONG ulIndex , TCPIP_SOCKHOST_S *pSockHost);
/*******************************************************************************
*    Func Name: TCPIP_DebugSockAll
*  Description: 打开调试开关，默认打开所有调试选项
*        Input: VOID
*       Output:
*       Return: VOS_OK  操作成功
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_DebugSockAll(VOID);
/*******************************************************************************
*    Func Name: TCPIP_NoDebugSockAll
*  Description: 关闭调试开关，所有socket相关调试信息均被关闭
*        Input: VOID
*       Output:
*       Return:  VOS_OK  操作成功
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_NoDebugSockAll(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowSockDebugging
*  Description: 显示调试开关的状态
*        Input: VOID
*       Output:
*       Return: VOS_OK  操作成功
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_ShowSockDebugging(VOID);
/*******************************************************************************
*    Func Name: TCPIP_SetSockDbgFilter
*  Description: 函数用于设置SOCKET调试的过滤信息
*        Input: ULONG ulFlag:标志：0:取消 1:设置
*               ULONG ulTaskId:调试的任务ID
*               ULONG ulSockId:调试的socket描述符
*       Output:
*       Return: SOCK_FILTOK  操作成功
*               SOCK_FILTINUSE 过滤条件已经存在
*               SOCK_FILTTOOMUCH 已经达到最大数限制
*               SOCK_FILTNOTFOUND 没找到相应的过滤条件
*               SOCK_FILTNONE 没有过滤条件
*               SOCK_FILTNULLPOINTER 指针参数为空
*               SOCK_PARAINVAILED 输入的ulFlag非0或1
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_SetSockDbgFilter(ULONG ulFlag, ULONG ulTaskId, ULONG ulSockId);
/*******************************************************************************
*    Func Name: TCPIP_SetSockHADbg
*  Description: 设置socket模块HA功能调试开关状态
*        Input: ULONG ulDbg:设置socket模块的HA调试信息。开关被打开（1）;开关被关闭（0）
*               LONG lSocketID:调试的socket描述符
*       Output:
*       Return: VOS_OK(0): Success
*               VOS_ERR(1): Socket is based on task
*               2: Debugging socket is full
*               3: Debugging socket is not found
*               4: Invalid argument
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_SetSockHADbg(ULONG ulDbg, LONG lSocketID);
/*******************************************************************************
*    Func Name: TCPIP_GetSockHADbg
*  Description: 获取socket模块HA功能调试开关状态
*        Input: ULONG *pulSockHaDbg:获取socket模块的HA调试信息，输入参数为一个有5个元素的ULONG型数组。开关被打开（1
）;开关被关闭（0）
*       Output:
*       Return: VOS_OK(0) : 操作成功
*               VOS_ERR(1): 操作失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_GetSockHADbg(ULONG *pulSockHaDbg);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncDrvDataSendDirectHook
*  Description: 产品向VISP注册钩子函数，用于Socket直接调用驱动发送数据函数
*        Input: DrvDataSendDirect_HOOK_FUNC pfHookFunc:钩子函数指针
*       Output:
*       Return: VOS_OK(0) : 操作成功
*               VOS_ERR   : 操作失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_RegFuncDrvDataSendDirectHook(DrvDataSendDirect_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncOpenPortNotifyHook
* Date Created: 2014-02-11
*       Author: fengjing209023
*  Description: 产品向VISP注册钩子函数，当本端开启端口时调用
*        Input: SOCK_PORT_NOTIFY_HOOK_FUNC pfHookFunc:钩子函数指针
*       Output: 
*       Return: VOS_OK(0) : 操作成功
*               VOS_ERR   : 操作失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-11   fengjing209023  Create
*
*******************************************************************************/
ULONG TCPIP_RegFuncOpenPortNotifyHook(SOCK_PORT_NOTIFY_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncOpenPortNotifyHook
* Date Created: 2014-02-14
*       Author: fengjing209023
*  Description: 设置socket组件的全局参数
*        Input: pstData: 全局参数
*       Output: 
*       Return: 成功：VOS_OK
*               失败：VOS_ERR
*     调用时机: 任意Socket配置之前配置
*      Caution: (1)产品保证该函数在协议栈启动之后,socket创建之前配置。VISP不做校验。
*               (2)与预配置参数SOCK_RAND_PORT_ENHANCE不兼容，即如果配置了
*               SOCK_RAND_PORT_ENHANCE为1，则本配置不生效。
*               (3)产品调用BIND接口时指定的端口号不受此上下限的约束
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-14   fengjing209023  Create
*
*******************************************************************************/
ULONG TCPIP_SetSockGlobleConfig(SOCK_GLOBLE_S *pstData);
/*******************************************************************************
*    Func Name: TCPIP_GetSockGlobleConfig
* Date Created: 2014-04-23
*       Author: fengjing209023
*  Description: 设置socket组件的全局参数
*        Input: 
*       Output: pstData: 全局参数
*       Return: 成功：VOS_OK
*               失败：VOS_ERR
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-23   fengjing209023  Create
*
*******************************************************************************/
ULONG TCPIP_GetSockGlobleConfig(SOCK_GLOBLE_S *pstData);
/*******************************************************************************
*    Func Name: TCPIP_ShowSockGlobleConfig
* Date Created: 2014-04-23
*       Author: fengjing209023
*  Description: 设置socket组件的全局参数
*        Input: 
*       Output: 
*       Return: VOID
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-23   fengjing209023  Create
*
*******************************************************************************/
VOID TCPIP_ShowSockGlobleConfig(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowMGInfoBySock
*  Description: 基于socket显示多播信息
*        Input: ULONG ulTaskId:任务ID
*               ULONG ulSockId:socket ID
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   z00104207               Create
*
*******************************************************************************/
VOID  TCPIP_ShowMGInfoBySock(ULONG ulTaskId, LONG lSockId);

/*******************************************************************************
*    Func Name: TCPIP_SetSockLogSwitch
* Date Created: 2010-12-14
*       Author: mafeng59090
*  Description: 设置指定类型的socket日志输出开关(关闭，缺省为打开)，
*               包括create/close/setsockopt，异常日志输出，错误日志不受这个影响
*        Input: ULONG ulProtocol:协议号,IPPROTO_TCP(TCP)、IPPROTO_UDP(UDP)、
*                              IPPROTO_ICMP等
*               ULONG ulLogSwitch:开关类型,1 打开(缺省打开),0 关闭
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-12-14   mafeng59090             Create
*
*******************************************************************************/
ULONG TCPIP_SetSockLogSwitch(ULONG ulProtocol, ULONG ulLogSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetSockLogSwitch
* Date Created: 2010-12-18
*       Author: mafeng59090
*  Description: 获取指定协议号对应的开关情况
*        Input: ULONG ulProtocol:协议号
*               ULONG *pulLogSwitch:开关情况
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-12-18   mafeng59090             Create
*
*******************************************************************************/
ULONG TCPIP_GetSockLogSwitch(ULONG ulProtocol, ULONG *pulLogSwitch);

/*******************************************************************************
*    Func Name: TCPIP_ShowISISInfoBySock
* Date Created: 2011-4-14
*       Author: y00171195
*  Description: 基于socket显示ISIS sock统计信息
*        Input: ULONG ulTaskId:任务ID
*               ULONG ulSockId:socket ID
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-4-14    y00171195               Create(DTS2011041801697)
*
*******************************************************************************/
VOID TCPIP_ShowISISInfoBySock(ULONG ulTaskId, LONG lSockId);

/*ipv6相关*/
/*******************************************************************************
*    Func Name: TCPIP_AddHost6
*  Description: 设置远程主机名和地址
*        Input: CHAR * pst6HostName:
*               CHAR * pst6HostIP:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9   wangbin(62223)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_AddHost6 ( CHAR * pst6HostName, CHAR * pst6HostIP );
/*******************************************************************************
*    Func Name: TCPIP_DelHost6
*  Description: 删除已设置的远程主机
*        Input: LONG lKind:
*               CHAR *pst6HostName:
*               CHAR *pst6HostIP:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9   wangbin(62223)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_DelHost6(LONG lKind, CHAR *pst6HostName, CHAR *pst6HostIP);
/*******************************************************************************
*    Func Name: TCPIP_GetHost6
*  Description: 显示所有远程主机
*        Input: ULONG ulIndex:索引
*       Output: TCPIP_SOCKHOST_S *pSockHost:待显示的远端主机
*       Return: SOCK6_ERR_NOT_REGISTER
*               VOS_ERR
*               SOCK6_GET_HOST_FAIL
*               VOS_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9   wangbin(62223)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_GetHost6(ULONG ulIndex , TCPIP_SOCKHOST_S *pSockHost);
/*******************************************************************************
*    Func Name: TCPIP_GetHC6Info
*  Description: 根据目的IP和目的端口号获取Head Cache结点
*        Input: ULONG ulTaskId: 要查询Head Cache结点的任务号
*               LONG iFd: socket的描叙符号
*               IN6ADDR_S* pstDstAddr6: 目的地址
*               USHORT usDstPort: 目的端口号(对RIP6端口号填0)
*       Output: TCPIP_HEADCACHE_ENTRY_S *pstEntry:  获取到的Head Cache结点
*       Return: VOS_ERR
*               SOCK6_ERR_NOT_REGISTER
*               VOS_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9   wangbin(62223)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_GetHC6Info(ULONG ulTaskId, LONG iFd, VRP_IN6ADDR_S* pstDstAddr6,
                              USHORT usDstPort, TCPIP_HEADCACHE_ENTRY_S *pstEntry);
/*******************************************************************************
*    Func Name: TCPIP_DebugSock6All
*  Description: 打开所有socket调试开关。
*        Input: VOID
*       Output:
*       Return: VOS_OK
*      Caution: None
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9   wangbin(62223)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_DebugSock6All(VOID);
/*******************************************************************************
*    Func Name:  TCPIP_NoDebugSock6All
*  Description: 关闭所有调试开关。
*        Input: VOID
*       Output:
*       Return: VOS_OK
*      Caution: None
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9   wangbin(62223)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_NoDebugSock6All(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowSock6Debugging
*  Description: 显示某个调试开关的状态 dispaly:e.g.
*               TCP:
*                  TCP packet debugging is on for task 11 socket 1
*                  TCP packet debugging is on for task any socket any
*                  TCP event debugging is on for task 11 socket 2
*               SOCKET:
*                  SOCKET debugging is on for task 11 socket 2
*                  SOCKET debugging is on for task 11 socket 3
*               UDP:
*                  UDP packet debugging is on for task 14 socket 2
*
*        Input: CHAR *szStatusStr: 开关状态
*               ULONG ulDebugIndx: 开关索引
*       Output: pbEnd:索引状态,如果是最后一个debug开关,则为BOOL_TRUE
*       Return: 0:成功, 其他:错误码
*      Caution: None
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9   wangbin(62223)     Creat the first version.
*
*******************************************************************************/
VOID  TCPIP_ShowSock6Debugging(VOID);
/*******************************************************************************
*    Func Name: TCPIP_SetSock6DbgFilter
*  Description: 所有需要进行任务名和套接口描述符过滤的调试命令的实现
*        Input: ULONG ulFlag: 是否为no命令的标志（0为no命令，1为非no命令）
*               SOCKDBUGFILTRD_S *pstDbugFiltRd: 指向存储过滤条件的全局结构的指针
*               ULONG ulTaskId: 任务id
*               ULONG ulSockId: 套接口描述符
*       Output:
*       Return: 过滤条件
*      Caution: None
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9   wangbin(62223)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_SetSock6DbgFilter(ULONG ulFlag, ULONG ulTaskId, ULONG ulSockId);

/*******************************************************************************
*    Func Name: TCPIP_GetSockTcpState
* Date Created: 2013-12-06
*       Author: d00217007
*  Description: 基于三元组/五元组查询socket信息
*        Input: TCPIP_SOCK_SEARCH_IN_S * pstSearchIn:用于查询的五元组信息和vrf，其中TCP协议号为6
*       Output: TCPIP_SOCK_SEARCH_OUT_S * pstSearchOut:查询到的socket id和TCP状态
*       Return: VOS_OK:
*               SOCK_SOCKETNOTFOUND:没有找到socket
*               SOCK_INVALIDPRO:非法的协议号
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-06   d00217007               Create
*
*******************************************************************************/
ULONG TCPIP_GetSockTcpState(TCPIP_SOCK_SEARCH_IN_S * pstSearchIn, TCPIP_SOCK_SEARCH_OUT_S * pstSearchOut);

/*******************************************************************************
*    Func Name: TCPIP_GetSockPQ0Info
* Date Created: 2013-12-06
*       Author: d00217007
*  Description: 查询监听socket Q0队列 
*        Input: LONG lFd:socket id
*       Output: TCPIP_SOCKPQINFO_S *pstSockPQInfo:获取到的socket信息
*       Return: VOS_OK
*               SOCK_QZEROEMPTY:Q0队列中没有节点
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-06   d00217007               Create
*
*******************************************************************************/
ULONG TCPIP_GetSockPQ0Info(LONG lFd, TCPIP_SOCKPQINFO_S *pstPQInfo);

/*******************************************************************************
*    Func Name: TCPIP_OpenSockPQ0Entry
* Date Created: 2013-12-06
*       Author: d00217007
*  Description: 查询监听socket Q0队列 Open操作
*        Input: LONG lFd:socket id
*       Output: UINTPTR *pulWaitListHandle:wait list句柄
*       Return: VOS_OK
*               SOCK_QZEROEMPTY:Q0队列中没有节点
*               SOCK_FILTNULLPOINTER:传入的句柄指针为空
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-06   d00217007               Create
*
*******************************************************************************/
ULONG TCPIP_OpenSockPQ0Entry (LONG lFd ,UINTPTR *pulWaitListHandle);

/*******************************************************************************
*    Func Name: TCPIP_GetSockPQ0Entry
* Date Created: 2013-12-06
*       Author: d00217007
*  Description: 查询监听socket Q0队列 Get操作
*        Input: UINTPTR ulWaitListHandle:wait list句柄
*       Output: TCPIP_SOCKPQINFO_S *pstSockPQInfo:获取到的socket信息
*       Return: VOS_OK
*               SOCK_QZEROEND:已到队列末端
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-06   d00217007               Create
*
*******************************************************************************/
ULONG TCPIP_GetSockPQ0Entry(UINTPTR pulWaitListHandle, TCPIP_SOCKPQNODEINFO_S *pstSockNodePQInfo);

/*******************************************************************************
*    Func Name: TCPIP_CloseSockPQ0Entry
* Date Created: 2013-12-06
*       Author: d00217007
*  Description: 查询监听socket Q0队列 Close操作
*        Input: UINTPTR ulWaitListHandle:wait list句柄
*       Output: 
*       Return: VOS_OK
*               SOCK_INVALIDHANDLE:句柄无效
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-06   d00217007               Create
*
*******************************************************************************/
ULONG TCPIP_CloseSockPQ0Entry(UINTPTR ulWaitListHandle);

/*******************************************************************************
*    Func Name: TCPIP_GetSockPQInfo
* Date Created: 2013-12-06
*       Author: d00217007
*  Description: 查询监听socket Q队列 
*        Input: LONG lFd:socket id
*       Output: TCPIP_SOCKPQINFO_S *pstSockPQInfo:获取到的socket信息
*       Return: VOS_OK
*               SOCK_QEMPTY:Q队列没有节点
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-06   d00217007               Create
*
*******************************************************************************/
ULONG TCPIP_GetSockPQInfo(LONG lFd, TCPIP_SOCKPQINFO_S *pstPQInfo);

/*******************************************************************************
*    Func Name: TCPIP_OpenSockPQEntry
* Date Created: 2013-12-06
*       Author: d00217007
*  Description: 查询监听socket Q队列 Open操作
*        Input: LONG lFd:socket id
*       Output: UINTPTR *pulWaitListHandle:wait list句柄
*       Return: VOS_OK
*               SOCK_QEMPTY:Q队列没有节点
*               SOCK_FILTNULLPOINTER:传入的句柄指针为空
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-06   d00217007               Create
*
*******************************************************************************/
ULONG TCPIP_OpenSockPQEntry (LONG lFd ,UINTPTR *pulWaitListHandle);

/*******************************************************************************
*    Func Name: TCPIP_GetSockPQEntry
* Date Created: 2013-12-06
*       Author: d00217007
*  Description: 查询监听socket Q队列 Get操作
*        Input: UINTPTR ulWaitListHandle:wait list句柄
*       Output: TCPIP_SOCKPQINFO_S *pstSockPQInfo:获取到的socket信息
*       Return: VOS_OK
*               SOCK_QEND:已到队列末端
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-06   d00217007               Create
*
*******************************************************************************/
ULONG TCPIP_GetSockPQEntry(UINTPTR pulWaitListHandle, TCPIP_SOCKPQNODEINFO_S *pstSockPQNodeInfo);

/*******************************************************************************
*    Func Name: TCPIP_CloseSockPQEntry
* Date Created: 2013-12-06
*       Author: d00217007
*  Description: 查询监听socket Q队列 Close操作
*        Input: UINTPTR ulWaitListHandle:wait list句柄
*       Output: 
*       Return: VOS_OK
*               SOCK_INVALIDHANDLE:句柄无效
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-06   d00217007               Create
*
*******************************************************************************/
ULONG TCPIP_CloseSockPQEntry(UINTPTR ulWaitListHandle);

/*******************************************************************************
*    Func Name: TCPIP_GetSockResourceStatus
* Date Created: 2013-12-06
*       Author: d00217007
*  Description: 查询socket使用情况
*        Input: 
*       Output: ULONG *pulTotalNum:当前配置的socket总数
*               ULONG *pulUsedNum:当前已使用的socket总数
*       Return: VOS_OK:
*               SOCK_TCBNOTFOUND:无法获取Tcb
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-06   d00217007               Create
*
*******************************************************************************/
ULONG TCPIP_GetSockResourceStatus(ULONG *pulTotalNum, ULONG *pulUsedNum);

typedef ULONG (*TCPKEEPALIVECLOSE_HOOK_FUNC)(LONG lSocketId, vrp_asynsockset *pstAsynsocket, ULONG *pulCloseFlag );
/*******************************************************************************
*    Func Name: TCPIP_RegFuncTCPKeepAliveCloseHook
* Date Created: 2014-01-16
*       Author: l00213099
*  Description: 注册TCP非保活时超时判断是否关闭连接钩子函数
*        Input: pfHookFunc
*       Output: 无
*       Return: 成功或失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-01-16   l00213099               Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncTCPKeepAliveCloseHook( TCPKEEPALIVECLOSE_HOOK_FUNC pfFuncHook );

/*******************************************************************************
*    Func Name: TCPIP_GetSockQosInfo
* Date Created: 2013-12-06
*       Author: d00217007
*  Description: 查询TCP连接Qos使用情况
*        Input: LONG lFd:socket id
*       Output: TCPIP_SOCK_QOS_INFO_S *pstQosInfo:Qos信息
*       Return: VOS_OK:
*               VOS_ERR:当前发包量为0
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-06   d00217007               Create
*
*******************************************************************************/
ULONG TCPIP_GetSockQosInfo(LONG lFd, TCPIP_SOCK_QOS_INFO_S *pstQosInfo);

/*******************************************************************************
*    Func Name: TCPIP_ShowSocket6
* Date Created: 2014-06-10
*       Author: likaikun213099
*  Description: 查询socket6信息
*        Input: ULONG ulSockType:需要显示的类型
*               ULONG ulTaskId:需要显示的socket所属的任务ID
*               ULONG ulSockId:指定特定任务的Socket
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-06-10   likaikun213099          Create
*
*******************************************************************************/
VOID  TCPIP_ShowSocket6(ULONG ulSockType, ULONG ulTaskId, ULONG ulSockId);

#ifdef __cplusplus
}
#endif /* __cpluscplus */

#endif

