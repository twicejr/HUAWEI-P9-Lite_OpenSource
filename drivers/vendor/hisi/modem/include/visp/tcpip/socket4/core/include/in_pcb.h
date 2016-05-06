/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              in_pcb.h
*
*  Project Code: VISP1.5
*   Module Name: socket4  
*  Date Created: 2006-4-28
*        Author: l(48769)
*   Description: INPCB definition
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*  2006-05-11   luyao           为支持ARM CPU字节对齐特性，修改结构。
*
*******************************************************************************/
#ifndef        _INPCB_H
#define        _INPCB_H

struct tagINADDR;
struct tagSOCKET;
struct tagROUTE;
struct tagIP;
struct tagMBuf;
struct tagIPMOPTIONS;

struct tagPCBHASH;
struct tagSOCK_SEARCH_IN_S;
struct tagSOCK_SEARCH_OUT_S;
struct tagSOCKPQNODEINFO;

/*
 * Common structure pcb for internet protocol implementation.
 * Here are stored pointers to local and foreign host table
 * entries, local and foreign socket numbers, and pointers
 * up (to a socket structure) and down (to a protocol-specific)
 * control block.
 */
typedef struct tagINPCB
{
    struct tagINPCB   *inp_pNext, *inp_pPrev;
    struct tagINPCB   *inp_pProHead;  /* pointer back to udp,tcp protocol special head 
                                       * which contain information about protocol */

    struct tagPCBHASH *inp_pHashHead; /* pointer back to hash table head */

    struct tagINPCB   *inp_pHashNext; /* for tcp/udp which use hash table */
    union
    {
        /* inp_pHashPrev will never be null except this pcb not in hash train */
        struct tagINPCB *inp_uipHashPrev;
        struct tagINPCB **inp_uipHashEntrance; /* it this pcb is in the first position, it point to the entrance of this hash */
    }inp_uiPrev;
    
    UCHAR    inp_ucHeader;          /* if this pcb is in the first one of the hash table */
                                    /* if inp_ucHeader=1, inp_uipHashEntrance will work */
    UCHAR    ucPadding_1[3];
#define inp_pHashPrev      inp_uiPrev.inp_uipHashPrev
#define inp_pHashEntrance  inp_uiPrev.inp_uipHashEntrance
    
    INADDR_S  inp_stFAddr;            /* foreign host table entry */
    USHORT    inp_usFPort;            /* foreign port */
    UCHAR     ucPadding_2[2];
    INADDR_S  inp_stLAddr;            /* local host table entry */
    USHORT    inp_usLPort;            /* local port */
    UCHAR     ucPadding_3[2];
    SOCKET_S *inp_pSocket;            /* back pointer to socket */
    CHAR     *inp_pPPcb;              /* pointer to per-protocol pcb */
    /*struct tagROUTE inp_stRoute;*/  /* placeholder for routing entry */
    LONG      inp_nFlags;             /* generic IP/datagram flags */
    IP_S      inp_stIp;               /* header prototype; should have more */
    MBUF_S   *inp_pOptions;           /* IP options */
    IPMOPTIONS_S *inp_pMOptions;      /* IP multicast options */
}INPCB_S;

/* flags in inp_flags: */
#define    INP_RECVOPTS           0x01    /* receive incoming IP options  not support now */
#define    INP_RECVRETOPTS        0x02    /* receive IP options for reply, not support now */
#define    INP_RECVDSTADDR        0x04    /* receive IP dst address */
#define    INP_CONTROLOPTS        (INP_RECVOPTS|INP_RECVRETOPTS|INP_RECVDSTADDR)
#define    INP_HDRINCL            0x08    /* user supplies entire IP header */
#define    INP_ROUT_ALERT         0x10
#define    INP_ONLYRECVMULTICAST  0x20    /* for ospf socket only receive multicast ip pkt*/

#define    INPLOOKUP_WILDCARD    1  /* 能够进行通配地址匹配，即全零地址可以匹配其它任何地址 */
#define    INPLOOKUP_SETLOCAL    2

#define    SOTOINPCB(so)    ((struct tagINPCB *)(so)->so_pPcb)


typedef struct tagPCBHASHTABLE
{
    struct tagINPCB ** pht_pHashForeign; /* second level hash table base on FA,FP */
    LONG    ph_nItemNum;                 /* number of items in this hash table */
}PCBHASHTABLE_S;

typedef struct tagPCBHASH
{
    PCBHASHTABLE_S *pht_pstHashLocal; /* first level hash table base on LP,LA */

    LONG pht_nFirstLevelMask;    /* 127 */
    LONG pht_nSecondLevelMask;   /* 511 */
    LONG pht_nFirstLevelNum;     /* 128 */
    LONG pht_nSecondLevelNum;    /* 512 */
}PCBHASH_S;
#define  HASH_FIRSTLEVEL_MASK     127        /* 128 - 1 */
#define  HASH_SECONDLEVEL_MASK    511        /* 512 - 1 */

/*Raw SCTP support SCTP header structure*/
typedef struct sctphdr {
    USHORT  uh_sport;   /* source port */
    USHORT  uh_dport;   /* destination port */
    ULONG   ul_vtag;    /* sctp verification tag */
    ULONG   ul_cksum;   /* sctp checksum */
}SCTP_HDR_S;

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

typedef    VOID (*PFRTCHANGE)(struct tagINPCB *, LONG);

/*added by zhaobiao for tcp/udp mib get table var operation */
VOID     reorderpcbltob(INPCB_S *);
VOID    *INPCB_GetNextPCB(VOID *,VOID **);
LONG     INPCB_Alloc(struct tagSOCKET *, struct tagINPCB *, PCBHASH_S *);
LONG     INPCB_Bind(struct tagINPCB *, SOCKADDRIN_S *);
LONG     INPCB_Connect(struct tagINPCB *, SOCKADDRIN_S *);
LONG     INPCB_Detach(struct tagINPCB *);
LONG     INPCB_Disconnect(struct tagINPCB *);

INPCB_S *INPCB_LookUp(INPCB_S *pHead, INADDR_S stFAddr,
                      ULONG uFPortArg, INADDR_S stLAddr, ULONG uLPortArg, LONG nFlags);

LONG     INPCB_Notify( struct tagINPCB *,
                       struct tagSOCKADDR *,
                       ULONG,
                       struct tagINADDR,
                       ULONG,
                       LONG,
                       VOID (*)(struct tagINPCB *, LONG)
                     );
VOID IN_RtChange(struct tagINPCB *, LONG);

LONG IN_SetPeerAddr( INPCB_S *pInPcb, MBUF_S *pMName );
LONG IN_SetSockAddr(register INPCB_S *pInPcb,MBUF_S *pMName);

/* insert a pcb into a hash table */
LONG INPCB_HashInsert( struct tagPCBHASH*, struct tagINPCB * );
/* detach a pcb from a hash table */
LONG INPCB_HashRemove( PCBHASH_S* pstPcbHash, INPCB_S * pstRemPcb);

/* search the hash table to find a most match pcb 
 * changed for socket muti_instance 2002-10-30 by mayun
 */
struct tagINPCB *INPCB_HashSearch( struct tagPCBHASH*,
                                   struct tagINADDR,
                                   USHORT,
                                   struct tagINADDR,
                                   USHORT,
                                   LONG,
                                   ULONG
                                 );
LONG INPCB_SearchSecond(PCBHASH_S* pstPcbHash,INADDR_S stLAddr, USHORT usLPort, INADDR_S stFAddr,
                        ULONG ulVrfIndex);

/* look up the hash table to see if a port has been used 
 * changed for socket muti_instance 2002-10-30 by mayun
 */
struct tagINPCB *INPCB_HashLookPort( struct tagPCBHASH*,
                                     struct tagINADDR,
                                     USHORT,
                                     struct tagINADDR,
                                     USHORT,
                                     LONG,
                                     ULONG  
                                    );
ULONG INPCB_GetSockTcpState(PCBHASH_S* pstPcbHash, struct tagSOCK_SEARCH_IN_S * pstSearchIn, struct tagSOCK_SEARCH_OUT_S * pstSearchOut);
ULONG INPCB_GETSOCKNODEINFO(SOCKET_S *pstSocket, struct  tagSOCKPQNODEINFO *pstSockPQNodeInfo);
#endif
