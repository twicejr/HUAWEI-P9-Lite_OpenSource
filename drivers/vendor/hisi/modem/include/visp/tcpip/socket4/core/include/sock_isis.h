/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock_isis.h
*
*  Project Code: VISP1.5
*   Module Name: socket4  
*  Date Created: 2006-4-29
*        Author: l(48769)
*   Description: socket isis defintion
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*  2006-05-11   luyao           为支持ARM CPU字节对齐特性，修改结构。
*
*******************************************************************************/
#ifndef  _SOCK_ISIS_H
#define  _SOCK_ISIS_H

#include "tcpip/public/ip_dmain.h"

#ifdef  __cplusplus
extern  "C"{
#endif 

#define PROTO_ISIS          0


/*next macro definition is for setopt*/

#ifndef PF_ISIS
#define PF_ISIS     0x25        /*sock_pub.h define other protocol */
#endif

#define PACKET_ADD_MEMBERSHIP     0
#define PACKET_DROP_MEMBERSHIP    1
/*add by fujibin for isis packet priority*/
#define PACKET_PRIORITY_LEVEL     2 


#define MACADDRLEN                6

/*Add for A82D19782 z62474, 报文是多播报文 */
#define ETHER_MAC_MCAST(enaddr)     ((((enaddr)[0]) & 0x01) && \
((0xFFFFFFFF != (*(ULONG *)enaddr)) && (0xFFFF != (*(USHORT *)(enaddr +4)))))? 1 : 0 


/*used for bind ,sendto,recvfrom */
typedef struct sockaddr_isis
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
}sockaddr_isis;

typedef struct tagMACCHAIN
{
    struct tagMACCHAIN *pNextMac;
    UCHAR mac[MACADDRLEN];
    UCHAR ucPadding[2];
}MACCHAIN_S;

typedef struct tagIFINFO
{
    struct tagIFINFO *pNext;
    ULONG ulIfIndex;
    struct tagMACCHAIN *pMacChainHead;
}IFINFO_S;

typedef struct tagISISPCB
{    
    struct tagISISPCB *inp_pNext,*inp_pPrev;
    struct tagISISPCB   *inp_pProHead;      
    
    IFINFO_S *inp_pstIfInfo;
    SOCKET_S *inp_pSocket;
    LONG     inp_nFlags;    
    LONG    inp_ulPriority;

}ISISPCB_S;

#define    SOTOISISPCB(so)    ((struct tagISISPCB *)((so)->so_pPcb))

typedef struct tagMACGROUP
{
    ULONG ulIfIndex;
    UCHAR mac[MACADDRLEN];
    UCHAR ucPadding[2];
}MACGROUP_S; 

typedef struct tagMultiMacList
{
    struct tagMultiMacList *pNext; /*the next point*/
    ULONG ulIfIndex;                 /*ifnet index*/
    ULONG ulRefCnt;                   /*ref count*/
    UCHAR mac[MACADDRLEN];  /*mac addr*/
    UCHAR ucPadding[2];           /*pad char*/
}MultiMacList;

 /*修改问题单A82D18380，rgx 35545 2007-08-08，多加个统计项*/
typedef struct tagRAWSTAT
{
    ULONG   rawl_ulInPackets;        /* total input packets */
    ULONG   rawl_ulPcbCacheMiss;    /* input packets missing pcb cache */    
    ULONG   rawl_ulNotPassMulti;                           /* not pass multicast*/
    ULONG   rawl_ulFullSockAndFreeMBuf;          /*  full socket and pstMBuf to be freed */
    ULONG   rawl_ulFullSockAndNotFreeMBuf;    /*  full socket and nothing to be freed */
    ULONG   rawl_ulFullSockOther;                       /*  full socket and other reasonl */
    ULONG   rawl_IfNetIsNull;                               /*ifnet is null*/
    ULONG   rawl_NotJoinMulti;                            /*not join multicast*/    
    ULONG   rawl_ulOutPackets;                          /* total output packets */
    ULONG   rawl_ulOutIfNetNull;                        /* output packet nof find ifnet */
    ULONG   rawl_ulOutMacInvalid;                     /* Dest Mac Invalid */
    ULONG   rawl_ulOutDataLarge;                     /* the packet is too large */
}RAWLSTAT_S;

extern DOMAIN_S stISISDomain;

/*isis_socket的所有函数*/

typedef    VOID   (*INPUT_FUN)(MBUF_S *pRcvSeg, LONG);      
typedef    LONG   (*OUTPUT_FUN)(MBUF_S *,VOID *,VOID*,ULONG,VOID*);
typedef    VOID   (*CTLINPUT_FUN)(LONG,VOID *,VOID *);   
typedef    LONG   (*CTLOUTPUT_FUN)(LONG, struct tagSOCKET *, LONG, LONG, MBUF_S **);  
typedef    LONG   (*USRREQ_FUN)(struct tagSOCKET *, LONG, VOID *,VOID *, VOID *);     

typedef    LONG    (*SYSCTL_FUN)(LONG *,ULONG,VOID *,ULONG *,VOID *,ULONG);

VOID SOCK_ISISInit(VOID);
VOID RAWL_Init();
LONG RAWL_UsrReq(SOCKET_S *,  LONG, MBUF_S *, const MBUF_S *, MBUF_S *);
LONG ISISPCB_Alloc(SOCKET_S *, ISISPCB_S *);
LONG ISISPCB_Detach(ISISPCB_S *);
LONG ISISPCB_Bind(ISISPCB_S *, const sockaddr_isis *);
LONG ISISPCB_UnBind(ISISPCB_S *, const sockaddr_isis *);
LONG RAWL_Output(const ISISPCB_S *,MBUF_S *, const MBUF_S *, MBUF_S *);
ISISPCB_S * RAWL_PcbSearch(const ISISPCB_S *, ULONG , IFINFO_S **);
LONG RAWL_isSelfMultiMac(MACCHAIN_S *,UCHAR *);
ULONG RAWL_Input(MBUF_S * );
VOID RAWL_CtlInput();
LONG RAWL_CtlOutput(LONG, SOCKET_S*, LONG, LONG, const MBUF_S**);
VOID RAWL_SysCtl();
ULONG SOCK_GetISISStaData(RAWLSTAT_S *pstRawStat);
VOID SOCK_ClearISISStaData(VOID);

/* Add for DTS2011041801697, by z00166124, at 2011-04-22. 修改原因: 增加统计 */
/* 通过INPCB设置UDP 的RAWL 统计信息 */
#define    INPCB_TO_PERRAWLSO_STAT(pInPCB, udpStatM, ulValue) \
{ \
    if (pInPCB) \
    {   \
        if (((struct tagISISPCB *)(pInPCB))->inp_pSocket) \
        { \
            ((pInPCB)->inp_pSocket)->unSocketStat.stPerUDP4Stat.udpStatM += ulValue; \
        } \
    } \
}

/*通过INPCB设置RAWIP 的RAWL 统计信息,保险起见添加此宏*/
#define    INPCB_TO_PERRAWLRWSO_STAT(pInPCB, rawIpStatM, ulValue) \
{ \
    if (pInPCB) \
    {   \
        if (((struct tagISISPCB *)(pInPCB))->inp_pSocket) \
        { \
            ((pInPCB)->inp_pSocket)->unSocketStat.stPerRAWIP4Stat.rawIpStatM += ulValue; \
        } \
    } \
}

/*引用的其他模块的函数*/
extern LONG VOS_strcmp (const CHAR *, const CHAR *);
extern LONG AsynWakeUp(SOCKET_S * ,LONG ,LONG );
extern VOID SoWakeUp(SOCKET_S *, LONG );
#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

