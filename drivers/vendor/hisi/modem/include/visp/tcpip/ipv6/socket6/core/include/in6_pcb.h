/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              in6_pcb.h
*
*  Project Code: VISP1.5
*   Module Name: Socket6
*  Date Created: 2002-8-20
*        Author: Mayun
*   Description: 本文件描述了IN6PCB相关结构及宏定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2002-8-20   Socket6          Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*  2006-05-11  luyao            为支持ARM CPU字节对齐特性，修改结构。
*
*******************************************************************************/

#ifndef _IN6_PCB_H_
#define _IN6_PCB_H_


#ifdef  __cplusplus
extern "C"{
#endif


/* VRPV5_IPV6_DEV_ENH BEGIN  - Rajesh S  13-06-2003 for vrp5.0*/
struct tagIn6Addr;
struct tagSOCKET;
struct tagIP6_S;
struct tagMBuf;
struct tagIN6PCBHASH ;

/* VRPV5_IPV6_DEV_ENH END */

/*
 * IN6PCB structure.
 */
typedef struct  tagIN6PCB
{
    struct    tagIN6PCB *pstIn6p_next, *pstIn6p_prev;
                       /* pointers to other pcb's */
    struct    tagIN6PCB *pstIn6p_head;
                       /* pointer back to chain of IN6PCB's for this protocol */

    /* VRPV5_IPV6_DEV_ENH BEGIN  - Rajesh S  13-06-2003  for vrp5.0 */

    struct tagIN6PCBHASH *pstIn6p_pHashHead;/* pointer back to hash table head */

    struct  tagIN6PCB  *pstIn6p_pHashNext;  /* for tcp/udp which use hash table */
    union
    {
        /* inp_pHashPrev will never be null except this pcb not in hash train */
        struct tagIN6PCB *pstIn6p_uipHashPrev;
        struct tagIN6PCB **pstIn6p_uipHashEntrance; /* it this pcb is in the first position, it point to the entrance of this hash */
    }in6p_uiPrev;

    UCHAR    in6p_ucHeader;     /* if this pcb is in the first one of the hash table */
                                /* if inp_ucHeader=1, inp_uipHashEntrance will work */
    UCHAR    ucPadding_1[3];
#define in6p_pHashPrev     in6p_uiPrev.pstIn6p_uipHashPrev
#define in6p_pHashEntrance  in6p_uiPrev.pstIn6p_uipHashEntrance

/* VRPV5_IPV6_DEV_ENH END */


    IN6ADDR_S stIn6p_faddr;     /* foreign host table entry */
    USHORT    usIn6p_fport;     /* foreign port */
    UCHAR     ucPadding_2[2];
    IN6ADDR_S stIn6p_laddr;     /* local host table entry */
    USHORT    usIn6p_lport;     /* local port */
    UCHAR     ucPadding_3[2];
    ULONG     ulIn6p_flowinfo;  /* priority and flowlabel */
    SOCKET_S  *pstIn6p_socket;  /* back pointer to socket */
    CHAR      *pIn6p_ppcb;      /* pointer to per-protocol pcb */
    ULONG     ulIn6p_flags;     /* generic IP6/datagram flags */
    SHORT     sIn6p_hops;       /* default hop limit */
    UCHAR     ucPadding_4[2];
    IP6_S     stIn6p_ip6;       /* header prototype */

    IP6_RECVPKTOPTS_S  *pstIn6p_inputopts;  /*IP6 options for incoming packets */
    IP6_PKTOPTS_S      *pstIn6p_outputopts; /*IP6 options for outgoing packets */
    IP6_MOPTIONS_S     *pstIn6p_moptions;   /* IP6 multicast options */
    ICMP6_FILTER_S     *pstIn6p_icmp6filt;

    SHORT      sIn6p_cksum; /* IPV6_CHECKSUM setsockopt */
    UCHAR      ucPadding_5[2];


    union
    {

        IN6ADDR_S stIn6Addr;
        ULONG     ulRegisterFlag;
    }in6_uiPMTU;

#define in6_stAddr         in6_uiPMTU.stIn6Addr
#define in6_ulRegisterFlag  in6_uiPMTU.ulRegisterFlag


}IN6PCB_S;


#define SOTOIN6PCB(so)  ((IN6PCB_S *)(so)->so_pPcb)

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


/* VRPV5_IPV6_DEV_ENH BEGIN  - Rajesh S  13-06-2003 for vrp5.0*/

typedef struct tagPCB6HASHTABLE
{
    struct tagIN6PCB ** pht_pHashForeign; /* second level hash table base on FA,FP */
    LONG    ph_nItemNum;               /* number of items in this hash table */
}PCB6HASHTABLE_S;

typedef struct tagIN6PCBHASH
{
    PCB6HASHTABLE_S *pht_pstHashLocal; /* first level hash table base on LP,LA */

    LONG pht_nFirstLevelMask;    /* 127 */
    LONG pht_nSecondLevelMask;   /* 511 */
    LONG pht_nFirstLevelNum;     /* 128 */
    LONG pht_nSecondLevelNum;    /* 512 */
}IN6PCBHASH_S;

#define  HASH_FIRSTLEVEL_MASK     127        /* 128 - 1 */
#define  HASH_SECONDLEVEL_MASK    511        /* 512 - 1 */

/* Modefied by wuling for DTS2014101506425 
   性能优化，取16与替代原来的32位与，解决低16位变化对HASH索引值没影响的问题 */

#define HASHFUNC6_ADDR6(pstAddr) \
    (((pstAddr)->s6_addr8[0])^((pstAddr)->s6_addr8[1])^((pstAddr)->s6_addr8[2])^((pstAddr)->s6_addr8[3])^ \
        ((pstAddr)->s6_addr8[4])^((pstAddr)->s6_addr8[5])^((pstAddr)->s6_addr8[6])^((pstAddr)->s6_addr8[7])^ \
        ((pstAddr)->s6_addr8[8])^((pstAddr)->s6_addr8[9])^((pstAddr)->s6_addr8[10])^((pstAddr)->s6_addr8[11])^ \
        ((pstAddr)->s6_addr8[12])^((pstAddr)->s6_addr8[13])^((pstAddr)->s6_addr8[14])^((pstAddr)->s6_addr8[15]))

#undef HASHFUNC6_SECOND
#define HASHFUNC6_SECOND(usFPort, pstFAddr) \
    ((HASHFUNC6_ADDR6(pstFAddr) + (usFPort))&(HASH_SECONDLEVEL_MASK))

/*Added by zhoushisong202096, 针对SOCKET6做适配, 2014/1/26   问题单号:DTS2014010901642 */
/* 通过IN6PCB获取UDP统计信息 */ 
#define    INP6CB_TO_PERUDPSO_STAT(pIn6PCB, udpStatM, ulValue) \
        { \
            if (pIn6PCB) \
            {   \
                if (((struct tagIN6PCB *)(pIn6PCB))->pstIn6p_socket) \
                { \
                    (((struct tagIN6PCB *)pIn6PCB)->pstIn6p_socket)->unSocketStat.stPerUDP4Stat.udpStatM += ulValue; \
                } \
            } \
        }
  
/* 通过IN6PCB获取UDP统计信息 */ 
#define    IN6PCB_TO_PERRAWIPSO_STAT(pIn6PCB, rawIpStatM, ulValue) \
                    { \
                        if (((struct tagIN6PCB *)(pIn6PCB))->pstIn6p_socket) \
                        { \
                            (((struct tagIN6PCB *)(pIn6PCB))->pstIn6p_socket)->unSocketStat.stPerRAWIP4Stat.rawIpStatM += ulValue; \
                        } \
                    }     
/* End of Added by zhoushisong202096, 2014/1/26   问题单号:DTS2014010901642 */

/*
 * functions declaration
 */

VOID * IN6PCB_GetNextPCB(VOID *,VOID **);

LONG IN6PCB_Init (UCHAR, UINTPTR *, UINTPTR * );

LONG     IN6PCB_Alloc(UINTPTR, UINTPTR , UINTPTR);

LONG     IN6PCB_Bind(UINTPTR , SOCKADDR_IN6_S *);

LONG     IN6PCB_Connect(UINTPTR , SOCKADDR_IN6_S *);

LONG     IN6PCB_Detach(UINTPTR);
LONG     IN6PCB_Disconnect(UINTPTR);

LONG     IN6PCB_Notify(UINTPTR,
                   SOCKADDR_S *,
                    ULONG,IN6ADDR_S *,
                    ULONG,
                    LONG,
                    VOID (*)(UINTPTR , LONG));

LONG IN6PCB_SetPeerAddr( UINTPTR, MBUF_S *pMName );

LONG IN6PCB_SetSockAddr(UINTPTR,MBUF_S *pMName);

LONG IN6PCB_HashInsert(IN6PCBHASH_S*, IN6PCB_S * );

LONG IN6PCB_HashRemove( IN6PCBHASH_S* , IN6PCB_S * );

UINTPTR IN6PCB_HashSearch(UINTPTR,
                                  IN6ADDR_S *,
                                   USHORT,
                                   IN6ADDR_S *,
                                   USHORT,
                                   LONG,
                                   ULONG,
                                   ULONG);

struct tagIN6PCB *IN6PCB_HashLookPort( IN6PCBHASH_S*,
                                     IN6ADDR_S *,
                                    USHORT,
                                    IN6ADDR_S *,
                                    USHORT,
                                    LONG,
                                    ULONG,
                                    ULONG);

LONG IN6PCB_SearchSecond(UINTPTR, IN6ADDR_S *, USHORT , IN6ADDR_S *, ULONG, ULONG);

/* VRPV5_IPV6_DEV_ENH END */

/* add by l57500,06-12-06,为支持IR所添加的函数 */
ULONG IN6PCB_BindFAddress(UINTPTR ulIn6Pcb, IN6ADDR_S *stIN6FAddr);


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _IN6_PCB_H_ */

