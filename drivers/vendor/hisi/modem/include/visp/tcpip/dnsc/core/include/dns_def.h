/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dns_def.h
*
*  Project Code: VISP1.5
*   Module Name: DNSC Module
*  Date Created: 2002-11-25
*        Author: Sun Yanfeng(32084)
*   Description: 1、这个头文件是DNS模块的定义全局宏的头文件
*                2、DNS模块的C文件需要包含该头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION
*  -----------------------------------------------------------------------------
*  2002-11-25  Sun Yanfeng(32084)         Creat the first version.
*
*******************************************************************************/

#ifndef _DNS_DEF_H_
#define _DNS_DEF_H_

/*In case of the C++.*/
#ifdef  __cplusplus
extern "C" {
#endif

#define DNS_DEFAULT_USERID   0Xffffffff

#define MAXDNSRCH       6   /* max # domains in search path */
#define DNS_MAXRESOLVSORT   10  /* number of net to sort on */
#define DNS_RES_TIMEOUT     5   /* min. seconds between retries, for function select() */
#define DNS_RES_RETRY       2   /* number of send retry time */

#define RES_INIT        0x00000001  /* 地址初始化 *************************************************/
#define RES_DEBUG       0x00000002  /* 打印调试信息 ***********************************************/
#define RES_AAONLY      0x00000004  /* 强制回答    authoritative answers only (!IMPL)**************/
#define RES_USEVC       0x00000008  /* 使用虚电路 *************************************************/
#define RES_PRIMARY     0x00000010  /* 查询主服务器  query primary server only (!IMPL) ************/
#define RES_IGNTC       0x00000020  /* 忽略停止错误  ignore trucation errors **********************/
#define RES_RECURSE     0x00000040  /* 需要递归      recursion desired ****************************/
#define RES_DEFNAMES    0x00000080  /* 使用缺省域名  **********************************************/
#define RES_STAYOPEN    0x00000100  /* 保持TCP套接字开启 ******************************************/
#define RES_DNSRCH      0x00000200  /* 搜索本地域名树 *********************************************/
#define RES_INSECURE1   0x00000400  /* 禁用类型1安全 **********************************************/
#define RES_INSECURE2   0x00000800  /* 禁用类型2安全 **********************************************/
#define RES_NOALIASES   0x00001000  /* 关闭HOSTALIASES特性 ****************************************/
#define RES_USE_INET6   0x00002000  /* 使用map IPv6  **********************************************/

#define RES_DEFAULT     (RES_RECURSE | RES_DEFNAMES | RES_DNSRCH)
#define MAXADDRS                4
#define DNS_TIME_TIMOUT      3      /*dns time out */

/*Byte order commented by Suraj 04- Sept 2003 to take the byte order from platform.*/
/*#define BYTE_ORDER  _BIG_ENDIAN*/

/* 资源和查询的类型值 */
#define T_A         1        /* 主机地址   ********************************************************/
#define T_NS        2        /* 授权服务器 ********************************************************/
#define T_MD        3        /* 邮件地址   ********************************************************/
#define T_MF        4        /* 邮件转发器  *******************************************************/
#define T_CNAME     5        /* 规范的名字  *******************************************************/
#define T_SOA       6        /* 授权域的起始 ******************************************************/
#define T_MB        7        /* 邮箱域名   ********************************************************/
#define T_MG        8        /* 邮件组员   ********************************************************/
#define T_MR        9        /* 邮件重命名 ********************************************************/
#define T_NULL      10       /* NULL资源记录  *****************************************************/
#define T_WKS       11       /* 知名服务   ********************************************************/
#define T_PTR       12       /* 域名指针  *********************************************************/
#define T_HINFO     13       /* 主机信息  *********************************************************/
#define T_MINFO     14       /* 邮箱信息   ********************************************************/
#define T_MX        15       /* 邮件路由信息 ******************************************************/
#define T_TXT       16       /* 文本字符串*********************************************************/
#define T_RP        17       /* 责任人    *********************************************************/
#define T_AFSDB     18       /* AFS元数据库 *******************************************************/
#define T_X25       19       /* X_25呼叫地址  *****************************************************/
#define T_ISDN      20       /* ISDN呼叫地址  *****************************************************/
#define T_RT        21       /* 路由器   **********************************************************/
#define T_NSAP      22       /* NSAP地址 **********************************************************/
#define T_NSAP_PTR  23      /* 反向NSAP查询 (不推荐) **********************************************/
#define T_SIG       24      /* 安全签名    ********************************************************/
#define T_KEY       25      /* 安全码   ***********************************************************/
#define T_PX        26      /* X.400邮件映射 ******************************************************/
#define T_GPOS      27      /* 地理位置   *********************************************************/
#define T_AAAA      28      /* IP6地址    *********************************************************/
#define T_LOC       29      /* 地址信息  **********************************************************/
#define T_NXT       30      /* 区域内的下一个合法名字  ********************************************/
#define T_EID       31      /* 端点标识     *******************************************************/
#define T_NIMLOC    32      /* NImrod定位器   *****************************************************/
#define T_SRV       33      /* 服务器选择   *******************************************************/
#define T_ATMA      34      /* ATM地址    *********************************************************/
#define T_NAPTR     35      /* 命名授权指针 *******************************************************/
/* 非标准  */
#define T_UINFO     100     /* 用户(手指)信息  ****************************************************/
#define T_UID       101     /* 用户ID  ************************************************************/
#define T_GID       102     /* 组ID    ************************************************************/
#define T_UNSPEC    103     /* 为指定格式(二进制数据) **********************************************/
/* 不出现在资源记录中的查询类型值   */
#define T_IXFR      251     /* 增量域传输  ********************************************************/
#define T_AXFR      252     /* 传输授权域  ********************************************************/
#define T_MAILB     253     /* 传输邮箱记录 *******************************************************/
#define T_MAILA     254     /* 传输邮件代理记录 ***************************************************/
#define T_ANY       255     /* 通配符匹配 *********************************************************/

/*#if BYTE_ORDER == _LITTLE_ENDIAN*/
/* Changed by Suraj to make compatible for the VRP platform.*/
#if (VRP_YES == VRP_LITTLE_ENDIAN )
    #define HTONS(a)        (USHORT) ((((USHORT)(a) & 0x00FF)<<8)  | \
                             (((USHORT)(a) & 0xFF00)>>8))

    #define NTOHS(a)        HTONS(a)
#else
    #define HTONS(a)        a
    #define NTOHS(a)        a
#endif

#define TRY_AGAIN       11002


#define MAXPACKET   1024
#define INT16SZ     2       /* for systems without 16-bit ints */
#define INT32SZ     4       /* for systems without 32-bit ints */

#define DNSC_NON_BLOCKING 1

#define HOST_NOT_FOUND   11001
#define NO_DATA          11004
#define MAXTASK             15
#define DNSFREE              0  /*for multi-task environment*/
#define DNSBUSY              1

typedef unsigned int        u_int;

#define PERIOD 0x2e
#define hyphenchar(c) ((c) == 0x2d)
#define periodchar(c) ((c) == PERIOD)

#define underscorechar(c) ((c) == 0x5f)

#define alphachar(c) (((c) >= 0x41 && (c) <= 0x5a) \
           || ((c) >= 0x61 && (c) <= 0x7a))
#define digitchar(c) ((c) >= 0x30 && (c) <= 0x39)
#define borderchar(c) (alphachar(c) || digitchar(c))
#define middlechar(c) (borderchar(c) || hyphenchar(c))

/* Define constants based on rfc883*/
#define MAXLABEL    63      /* maximum length of domain label */
#define MAXDNAME    255     /* maximum presentation domain name */
#define HFIXEDSZ    12      /* #/bytes of fixed data in header */
#define QFIXEDSZ    4       /* #/bytes of fixed data in query */
#define INADDRSZ    4       /* IPv4 T_A */
#define RRFIXEDSZ   10      /* #/bytes of fixed data in r record */


/* Values for IPv6*/
#define IN6ADDRSZ    16       /* IPv6 T_AAAA */

/* Values for class field */
#define C_IN        1       /* the arpa internet */
#define C_CHAOS     3       /* for chaos net (MIT) */
#define C_HS        4       /* for Hesiod name server (MIT) (XXX) */
/* Query class values which do not appear in resource records */
#define C_ANY       255     /* wildcard match */

/* Currently defined opcodes */
#define QUERY           0x0     /* standard query */
#define NS_NOTIFY_OP    0x4     /* notify secondary of SOA change */

/* Currently defined response codes */
#define NOERROR     0       /* no error */
#define FORMERR     1       /* format error */
#define SERVFAIL    2       /* server failure */
#define NXDOMAIN    3       /* non existent domain */
#define NOTIMP      4       /* not implemented */
#define REFUSED     5       /* query refused */

/* Internet nameserver port number*/
#define NAMESERVER_PORT 53

/* Defines for handling compressed domain names */
#define INDIR_MASK  0xc0

/* Inline versions of get/put short/long.  Pointer is advanced.

 * These macros demonstrate the property of C whereby it can be
 * portable or it can be elegant but rarely both.
 */
#define GETSHORT(s, cp) { \
    UCHAR *t_cp = (UCHAR *)(cp); \
    (s) = (USHORT)( ((USHORT)t_cp[0] << 8) \
        | ((USHORT)t_cp[1]) )\
        ; \
    (cp) += INT16SZ; \
}

#define GETLONG(l, cp) { \
    UCHAR *t_cp = (UCHAR *)(cp); \
    (l) = ((ULONG)t_cp[0] << 24) \
        | ((ULONG)t_cp[1] << 16) \
        | ((ULONG)t_cp[2] << 8) \
        | ((ULONG)t_cp[3]) \
        ; \
    (cp) += INT32SZ; \
}

#define PUTSHORT(s, cp) { \
    USHORT t_s = (USHORT)(s); \
    UCHAR *t_cp = (UCHAR *)(cp); \
    *t_cp++ = (UCHAR)(t_s >> 8); \
    *t_cp   = (UCHAR)t_s; \
    (cp) += INT16SZ; \
}

#define PUTLONG(l, cp) { \
    ULONG t_l = (ULONG)(l); \
    UCHAR *t_cp = (UCHAR *)(cp); \
    *t_cp++ = (UCHAR)(t_l >> 24); \
    *t_cp++ = (UCHAR)(t_l >> 16); \
    *t_cp++ = (UCHAR)(t_l >> 8); \
    *t_cp   = (UCHAR)t_l; \
    (cp) += INT32SZ; \
}


#define NETDB_INTERNAL  -1  /* see errno */
#define NETDB_SUCCESS   0   /* no problem */
#define NO_RECOVERY 3 /* Non recoverable errors, FORMERR, REFUSED, NOTIMP */

/*
 * Global defines and variables for resolver stub.
 */
#define MAXNS           6   /* max # name servers we'll track */

/* change this to "0"
 * if you talk to a lot
 * of multi-homed SunOS
 * ("broken") name servers.
 */
#define CHECK_SRVR_ADDR  1  /* XXX - should be in options.h */


#define NFDBITS       0x20

#define CAN_RECONNECT 1

#define DNS_INVALID_IFINDEX 0    /*invalid interface index.*/
#define DNS_MAX_IFINDEX_NUM 20   /*Max Length of Interface index string defect 3595*/

/* DNSC模块使用的SID统一在此定义 */

#define SID_COMP_DNSC_HOST_S              1  /* struct hostent */
#define SID_COMP_DNSC_CACHE_ENTRY_S       2  /* DNS_CACHE_S */
#define SID_COMP_DNSC_UDP_BUFFER_S        3  /* DNS response buffer over UDP*/
#define SID_COMP_DNSC_TCP_BUFFER_S        4  /* DNS response buffer over TCP*/
#define SID_COMP_DNSC_TCP6_BUFFER_S       5  /* DNS response buffer over TCP ipv6*/

/* end of SID */

/*In case of the C++.*/
#ifdef  __cplusplus
}
#endif

#endif

