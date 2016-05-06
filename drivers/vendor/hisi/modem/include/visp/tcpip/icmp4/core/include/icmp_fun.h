/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              icmp_fun.h
*
* Project Code: VISPV100R005
*  Module Name: ICMP4
* Date Created: 2006-01-24
*       Author: Li LiXiang
*  Description: 声明了Icmp中的功能函数,宏和枚举定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-24   Li LiXiang              Create
*  2006-04-21   Jiangtao                根据编程规范，对文件进行规范化整理 
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _ICMP_FUN_H_
#define _ICMP_FUN_H_

#include "tcpip/public/arith_cbb/include/avltree.h"

#define ICMP_DEBUG_PKT_RECV  0
#define ICMP_DEBUG_PKT_SEND  1


enum enumIcmpDiscardType
{
    ICMP_DISCARD_SPLIMP = 0,             /*0*/
    ICMP_DISCARD_MBUF_CONCATENATE,       /*1*/
    ICMP_DISCARD_MBUF_FRAGMENT,          /*2*/
    ICMP_DISCARD_MBUF_CUTTAIL,           /*3*/
    ICMP_DISCARD_MBUF_PREPEND,           /*4*/
    ICMP_DISCARD_WRONG_TYPECODE,         /*5*/
    ICMP_DISCARD_UNKOWN                  /*6*/
};


#define ICMP_PINGALLOWLIST_MAXNUM       6

typedef struct tagPING_ALLOW_ADDR
{
    ULONG ulIPAddr;                     /*地址*/
    ULONG ulSubnetMask;                 /*子网掩码*/
} PING_ALLOW_ADDR_S;

#ifndef MIN
#define MIN(a, b)       ((a)>(b) ? (b):(a)) 
#endif

/*
 * Lower bounds on packet lengths for various types.
 * For the error advice packets must first insure that the
 * packet is large enought to contain the returned ip header.
 * Only then can we do the check to see if 64 bits of packet
 * data have been returned, since we need to check the returned
 * ip header length.
 */
#define ICMP_MINLEN     8               /* abs minimum */
#define ICMP_TSLEN      (8 + 3 * sizeof (NTIME))    /* timestamp */
#define ICMP_MASKLEN    12              /* address mask */
#define ICMP_ADVLENMIN  (8 + sizeof (struct tagIP) + 8) /* min */
#define ICMP_ADVLEN(p)  (8 + ((p)->icmp_stIp.ip_chHLen << 2) + 8)
/* N.B.: must separately check that ip_chHLen >= 5 */


/*
 * Definitions for IP options.
 */
#define IPOPT_EOL       0       /* end of option list */
#define IPOPT_NOP       1       /* no operation */
#define IPOPT_RR        7       /* record packet route */
#define IPOPT_TS        68      /* timestamp */
#define IPOPT_SECURITY  130     /* provide s,c,h,tcc */
/*
 * Offsets to fields in options other than EOL and NOP.
 */
#define IPOPT_OPTVAL    0       /* option ID */
#define IPOPT_OLEN      1       /* option length */



#define ICMP_FLOWSTAT_TYPE_NUM      4       /* Number of types of flow stats */

#define ICMP_TYPE_ALL_MASK          0x0F

extern LONG ICMP_FLOW_COMPARE(VOID *a, VOID *b);
#define ICMP_FLOW_STAT_OFFSETOF(STRUCT,FIELD) (USHORT)((UCHAR *)(&((STRUCT *)1)->FIELD) - (UCHAR *)1)
#define ICMP_FLOW_STAT_INSERT(TREE, NODE, TREE_INFO)                                    \
                            (NULL == AVL3_FindToInsert(&(TREE), &(NODE), &(TREE_INFO)))
#define ICMP_FLOW_STAT_INIT_NODE(NODE)            (NODE).parent = NULL;                \
                                             (NODE).left = NULL;                  \
                                             (NODE).right = NULL;                 \
                                             (NODE).sLeftHeight = -1;                \
                                             (NODE).sLeftHeight = -1
#define ICMP_FLOW_STAT_DELETE(TREE, NODE)            AVL3_DeleteNode(&(TREE), &(NODE))
#define ICMP_FLOW_STAT_FIND(TREE, KEY, TREE_INFO)    AVL3_FindNode(&(TREE), (KEY), &(TREE_INFO))
#define ICMP_FLOW_STAT_NEXT(NODE, TREE_INFO)         AVL3_GetNextNode(&(NODE), &(TREE_INFO))
#define ICMP_FLOW_STAT_FIRST(TREE, TREE_INFO)        AVL3_GetFirstNode(&(TREE), &(TREE_INFO))





/* FIFO Queue for storing statistics. */
typedef struct tagICMPFlowStatQueue
{
    VOID *pvStat;               /* Points to either ICMPFLOWSTAT_ECHO_S or
                                   ICMPFLOWSTAT_PORTUNREACH_S depending on
                                   TCPIP_ICMP_FLOW_STAT_TYPE_E */
    struct tagICMPFlowStatQueue *pstNext;
}ICMP_FLOW_STAT_QUEUE_S;

typedef struct tagICMPFlowStat
{
    /* ICMP_FLOW_STAT_HASH_ENTRY_S **pstHashTable; pointer to hash table */
    ICMP_FLOW_STAT_QUEUE_S *pstHeadList;        /* pointer to the head of queue */
    ICMP_FLOW_STAT_QUEUE_S *pstTailList;        /* pointer to the tail of queue */
    UCHAR ucTableSize;          /* Number of entires currently stored. */
    UCHAR ucPad[3];
}ICMP_FLOW_STAT_S;

typedef struct tagICMPFlowStatCache
{
    VOID *pvStat;
    ULONG ulVrfIndex;
}ICMP_FLOW_STAT_CACHE_S;

/* Node of the AVL tree, contain flow stats for that Vrf. */
typedef struct tagICMPFlowStat_AVL_NODE
{
    ULONG ulVrfIndex;
    ICMP_FLOW_STAT_S *pstFlowStatArray[ICMP_FLOWSTAT_TYPE_NUM];
    struct tagICMPSTATVRF stIcmpStat;
    AVL3_NODE_S stFlowStatNode;    /* AVL Node */
}ICMP_FLOW_STAT_AVL_NODE_S;


/* icmp4 statictics variable */
extern struct  tagICMPSTAT stIcmpStat;

extern VOID ICMP_Input(MBUF_S *pstMBuf, LONG lHLen);
extern LONG ICMP_SysCtl(LONG *plName, ULONG ulNameLen, VOID *pOld, ULONG *plOldLen, VOID *pNew, ULONG ltNewLen);
extern VOID ICMP_Error(MBUF_S *pstMBuf, LONG ltype, LONG lcode, ULONG ulnlDest, struct tagIFNET *pstIfNet );
extern ULONG ICMP_SetPingAllowList(ULONG ulOperation, ULONG ulIpAddr, ULONG ulMask);
extern VOID ICMP_ShowPingAllowList ( );

extern ULONG ICMP_IsAttackGuardSwitchOn(LONG ltype);
extern ULONG ICMP_GetTmSinceMnht(VOID);

ULONG ICMP_Vrf_DelCallback(ULONG ulEvents, VOID * pulVrfIndex);
ULONG ICMP_AddIcmpFlowStat(UCHAR ucFlowStatType, ULONG ulLocalIP, ULONG ulRemoteIP,
                            UCHAR ucIcmpType, ULONG ulSendErr, ULONG ulVrfIndex);
ULONG ICMP_AddIcmpStatbyVrf(ULONG ulVrfIndex, UCHAR ucIcmpType,
                            UCHAR ucIcmpCode, UCHAR ucPacketDir);
ULONG ICMP_GetReflectSrcIP(MBUF_S *pstMBuf, IP_S *pstIp, SOCKADDRIN_S *pstIcmpReqDstIp);

extern ULONG IP_ICMP_ClearIcmpFlowStatByType(UCHAR ucFlowStatType, ULONG ulVrfIndex, ICMP_FLOW_STAT_S *pstFlowStatArray);
extern ULONG IP_ICMP_CreateIcmpFlowStatByVrf(UCHAR ucFlowStatType, UCHAR ucNumber, ICMP_FLOW_STAT_S *pstFlowStatArray[]);

#endif  /*  _ICMP_FUN_H_  */

#ifdef  __cplusplus
}
#endif

