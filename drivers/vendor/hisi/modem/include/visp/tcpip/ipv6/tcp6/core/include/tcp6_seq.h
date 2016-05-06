/*****************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------
*                              tcp6_seq.h
*
*    Project Code:  VRP5.0
*    Module Name:  IP6 TCP6
*   Version     : Initial Draft
*    Create Date:  2003/06/27
*    Author:       Naina Gupta
*    Description:  TCP6 sequence macros and defines
*-----------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------
*  2003-06-27  Naina Gupta         Created
******************************************************************
*/

#ifndef _TCP6_SEQ_H
#define _TCP6_SEQ_H

#ifdef  __cplusplus
extern "C"{
#endif

#define    SEQ_LT(a,b)    ((LONG)((a)-(b)) < 0)
#define    SEQ_LEQ(a,b)    ((LONG)((a)-(b)) <= 0)
#define    SEQ_GT(a,b)    ((LONG)((a)-(b)) > 0)
#define    SEQ_GEQ(a,b)    ((LONG)((a)-(b)) >= 0)

/*
 * Macros to initialize tcp sequence numbers for
 * send and receive from initial send and receive
 * sequence numbers.
 */
#define    TCP6_RCVSEQINIT(pTCPCB) \
    (pTCPCB)->seqRcvAdvertise = (pTCPCB)->seqRcvNxt\
    = (pTCPCB)->seqInitRcvSeq + 1

#define    TCP6_SENDSEQINIT(pTCPCB) \
    (pTCPCB)->seqSndUnack = (pTCPCB)->seqSndNxt = (pTCPCB)->seqSndMax = \
        (pTCPCB)->seqSndUrgentPoint = (pTCPCB)->seqISS

#define TCP6_ISN_BYTES_PER_SECOND    (1024*1024)
#define TCP6_ISN_STATIC_INCREMENT    4096
#define TCP6_ISN_RADNOM_INCREMENT    (4096-1)
#define TCP6_ISN_BYTES_FREQUENCY     100


#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif
