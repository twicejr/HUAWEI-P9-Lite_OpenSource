/******************************************************************************
 *
 *        Copyright 2003-2006  Huawei Technologies India Private Limited
 *                          All Rights Reserved
 *
 *------------------------------------------------------------------------------
 *                            ppmng_extension.h
 *    Project Code:  VRP5.0
 *    Module Name:  IP6 PP
 *    Create Date:  2003/06/10
 *         Author:  Arun H S
 *     Description: Extension Header Processing for the Input Packet.
 *------------------------------------------------------------------------------
 *  Modification History                                                        
 *  DATE        NAME             DESCRIPTION                                    
 *  ----------------------------------------------------------------------------
 *  2003-06-10  Arun H S         Create
 ******************************************************************************/
#ifndef _IP6_PPMNGEXTENSION_H
#define _IP6_PPMNGEXTENSION_H

#ifdef __cplusplus
extern "C"{
#endif


#define IP6OPT_PAD1         0x00    /* 00 0 00000 */
#define IP6OPT_PADN         0x01    /* 00 0 00001 */
#define IP6OPT_MINLEN          2

#define IP6_GET_OPT_TYPE(opt)   ((opt) & 0xC0) /* (opt & 1100 0000) For Unknown Options. the first 2 bits of "option type" */
#define IP6OPT_TYPE_SKIP        0x00
#define IP6OPT_TYPE_DISCARD     0x40
#define IP6OPT_TYPE_FORCEICMP   0x80
#define IP6OPT_TYPE_ICMP        0xC0
#define PP_SOURCE_ROUTED        1

 /* Modified by Rajesh for defect id BYAD11538 */

#define VALID_NEXT_HEADER_VALUE(val)\
    ((val) == IPPROTO_HOPOPTS || (val) == IPPROTO_DSTOPTS ||\
    (val) == IPPROTO_ROUTING || (val) == IPPROTO_FRAGMENT ||\
    (val) == IPPROTO_ICMPV6 || (val) == IPPROTO_NONE ||\
    (val) == IPPROTO_IPV6 || (val) == IPPROTO_RAW || \
    (val) == IPPROTO_TCP || (val) == IPPROTO_UDP || (val) == IPPROTO_OSPF)

/* 下面的宏表示路由器IPv6重组队列中最大的分片报文个数 */
#define IP6_MAX_FRAGS_NUM       1000

/* 下面的宏表示路由器中IPv6重组队列的最大个数 */
#define IP6_MAX_REASSQ_NUM      400

#define IPV6_FRAGTTL            120 /* ttl for fragment packets, in slowtimo tick */

/* 将分片newfrag插入到分片队列中prevfrag之后 */
#define FRAG6_ENQUE(newfrag, currfrag) \
{\
    newfrag->ip6f_pstPrev = currfrag->ip6f_pstPrev;\
    newfrag->ip6f_pstNext = currfrag;\
    currfrag->ip6f_pstPrev->ip6f_pstNext = newfrag;\
    currfrag->ip6f_pstPrev = newfrag;\
    g_ulIP6FragPacketsNum ++;\
}


/* 在分片队列中删除分片frag */
#define FRAG6_DEQUE(frag) \
{\
    frag->ip6f_pstPrev->ip6f_pstNext = frag->ip6f_pstNext;\
    frag->ip6f_pstNext->ip6f_pstPrev = frag->ip6f_pstPrev;\
    g_ulIP6FragPacketsNum --;\
}

/* 将队列newq插入到分片队列prevq之后 */
#define FRAG6_INSQUE(newq, prevq)\
{\
    newq->ip6q_pstqPrev = prevq;\
    newq->ip6q_pstqNext = prevq->ip6q_pstqNext;\
    prevq->ip6q_pstqNext->ip6q_pstqPrev = newq;\
    prevq->ip6q_pstqNext = newq;\
    g_ulIP6ReassQueNum ++;\
}

/* 从分片队列中删除队列q */
#define FRAG6_REMQUE(q) \
{\
    q->ip6q_pstqPrev->ip6q_pstqNext = q->ip6q_pstqNext;\
    q->ip6q_pstqNext->ip6q_pstqPrev = q->ip6q_pstqPrev;\
    g_ulIP6ReassQueNum --;\
}

#ifndef NO_USE       /* Added by Guru; 22-04-2004; to avoid redefinition warning */ 
#define     NO_USE(var)     (VOID)(var)
#endif

/*modified by pei gangqiang for VRP_MODULE_QOS_NEST_POLICY_II*/
/*目前仅仅拷贝了优先级*/
#define IP6_FILLMBUF_QOSTAG(pstMBuf)\
{\
    IP6_S *pstIP6 = NULL;\
    MBUF_IP6_PACKET_INFO_S *pstIp6MBufInfo = NULL;\
    pstIp6MBufInfo = (MBUF_IP6_PACKET_INFO_S *)MBUF_GET_TAG_NETWORK_IP6_PTR(pstMBuf);\
    pstIP6 = MBUF_MTOD(pstMBuf, IP6_S *);\
    /*syn D038 by x36308 2005-7-5*/\
\
    /* pstIp6MBufInfo ->ucServiceType =  pstIp6->ip6_ucTrafclass;*/\
    pstIp6MBufInfo->ucServiceType = (UCHAR)(IPV6_HDR_GET_TRAFFICCLASS(pstIP6->ip6_ulFlow));\
}

/* Prototypes Of the Functions in Extension.c */
LONG IP6_PP_UnknownOptions (MBUF_S *pstMBuf, const UCHAR *pOpt, ULONG ulOff);
ULONG IP6_PP_Process_HopOptions (MBUF_S *pstMBuf, UCHAR *pData, LONG lLen);
ULONG IP6_PP_HopbyHop_Input(MBUF_S **ppstMBuf, ULONG *pulOff, ULONG *pulNxtHdr);
ULONG IP6_PP_Process_DestOptions (MBUF_S *pstMBuf, UCHAR *pData, LONG lDestLen);
ULONG IP6_PP_Destination_Input (MBUF_S **ppstMBuf, ULONG *pulOff, ULONG ulProto);
ULONG IP6_PP_Route_Input(MBUF_S **ppstMBuf, ULONG *pulOff, ULONG ulProto);
ULONG IP6_PP_Fragment_Input (MBUF_S **ppstMBuf, ULONG *pulOff, ULONG ulProto);
VOID IP6_PP_Frag6_FreeQue (IP6REASSQUEUE_S *pIP6Q);
/* END: Prototypes Of the Functions in Extension.c */

#ifdef __cplusplus
}
#endif

#endif

