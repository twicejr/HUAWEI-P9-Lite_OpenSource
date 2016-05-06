/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dns_type.h
*
*  Project Code: VISP1.5
*   Module Name: DNSC Module  
*  Date Created: 2002-11-25
*        Author: Sun Yanfeng(32084)
*   Description: 定义DNS中主要数据结构
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-11-25  Sun Yanfeng(32084)   Creat the first version.
*  2006-05-10  lu yao(60000758)     为支持ARM CPU字节对齐特性，修改结构。
*
*******************************************************************************/

#ifndef _DNS_TYPE_H_
#define _DNS_TYPE_H_

/*In case of the C++.*/
#ifdef  __cplusplus
extern "C" {
#endif


/* New structure to maintain ipv4 and ipv6 server address */
typedef struct DNSC_Serv_IP
{
    UCHAR                   ucIPType;   /* ipv4 or ipv6 */
    union {
        struct sockaddr_in stAddr4;
        SOCKADDR_IN6_S      stAddr6;
    } serverIP;
} DNSC_Serv_IP_S;


typedef struct DNS_Res_State 
{
    LONG    retrans;        /* retransmition time interval */
    LONG    retry;          /* number of times to retransmit */
    ULONG   options;        /* option flags - see below. */

    LONG    nscount;        /* number of name servers */
    
    DNSC_Serv_IP_S      stServaddr_list[DNS_DOMAIN_SERVER_NUM]; /* address of name server */

    ULONG ulNsIfIndex[DNS_DOMAIN_SERVER_NUM];   /* store the interface index in case the ipv6 address is Link local.
                                                   Not used by other address types*/
    USHORT  id;         /* current message id */
    CHAR    dnsrch[DNS_DOMAIN_LIST_NUM][DNS_DOMAIN_LIST_NAME_LENGTH+1]; /* components of domain to search */
    USHORT  usdnsrch_count;
    UCHAR   ucPadding_1[2]; 
    ULONG   pfcode;         /* RES_PRF_ flags - see below. */
    unsigned ndots:4;       /* threshold for initial abs. query */
    unsigned nsort:4;       /* number of elements in sort_list[] */
    CHAR    unused[2];
    struct {
            struct in_addr  addr;
            ULONG   mask;
    } sort_list[DNS_MAXRESOLVSORT];
    ULONG ulDNS_ExecId;
    ULONG ulUSER_CtrlFlag; 
}DNS_Res_State_S;


/* 域名服务器报文格式*/
typedef struct 
{
    unsigned    id :16;     /* query identification number */
/*#if BYTE_ORDER == _BIG_ENDIAN*/
#if (VRP_YES == VRP_BIG_ENDIAN )
    /* fields in third byte */
    unsigned    qr: 1;      /* response flag : 为0--查询；为1--响应*/
    unsigned    opcode: 4;  /* 查询类型 */
    unsigned    aa: 1;      /* authoritive answer 若回答是授权，则置位为1 */
    unsigned    tc: 1;      /* truncated message 若报文被截断，则置位为1*/
    unsigned    rd: 1;      /* recursion desired 若需要递归则置位为1*/
    /* fields in fourth byte */
    unsigned    ra: 1;      /* recursion available 若有递归，则置位为1*/
    unsigned    unused :1;  /* unused bits (MBZ as of 4.9.3a3) */

    unsigned    ad: 1;      /* 已命名的可靠数据  authentic data from named */
    unsigned    cd: 1;      /* 无效检查  checking disabled by resolver */
    unsigned    rcode :4;   /* 响应类型  response code 0，1，2，3不同含义*/
#else
    unsigned    rd :1;      /* 递归式要求  recursion desired */
    unsigned    tc :1;      /* 截断信息  truncated message */
    unsigned    aa :1;      /* 权威回答  authoritive answer */
    unsigned    opcode :4;  /* 信息目的  purpose of message */
    unsigned    qr :1;      /* 应答标志  response flag */
    /* 四字节域  fields in fourth byte */
    unsigned    rcode :4;   /* 应答代码  response code */
    unsigned    cd: 1;      /* 无效性检测  checking disabled by resolver */
    unsigned    ad: 1;      /* 已命名的可靠数据  authentic data from named */
    unsigned    unused :1;  /* 未用比特  unused bits (MBZ as of 4.9.3a3) */
    unsigned    ra :1;      /* 可利用递归式  recursion available */
#endif
    /* 保留字节  remaining bytes */
    unsigned    qdcount :16;    /* number of question entries 所有问题数*/
    unsigned    ancount :16;    /* number of answer entries 回答数*/
    unsigned    nscount :16;    /* number of authority entries 管理机构数*/
    unsigned    arcount :16;    /* number of resource entries 附加信息数*/
} HEADER;



typedef union 
{
    LONG  al;
    CHAR ac;
} align;


typedef struct  hostentdns
{
    CHAR    *h_name;            /* official name of host */
    CHAR    h_aliases[4][MAXDNAME]; /* alias list */
    short   h_addrtype;         /* host address type */
    short   h_length;           /* length of address */
    CHAR    h_addr_list[4][20]; /* list of addresses from name server */
#define h_addr  h_addr_list[0]  /* address, for backward compatiblity */
    ULONG  ulTTL[4];
}hostentdns_s;  

typedef struct  hostenthw 
{
    char    h_name[MAXDNAME];         /* official name of host */
    UCHAR   ucPadding;
    char    h_aliases[4][MAXDNAME];   /* alias list 别名 */
    short   h_addrtype;               /* host address type */
    short   h_length;                 /* length of address */
    char    h_addr_list[4][20];       /* list of addresses */
#define h_addr  h_addr_list[0]        /* address, for backward compat */
    ULONG   ulTTL;                    /* the time can cache the entry */
}hostenthw_s;
/*In case of the C++.*/

#ifdef  __cplusplus
}
#endif
#endif


