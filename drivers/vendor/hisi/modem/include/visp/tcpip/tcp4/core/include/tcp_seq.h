/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcp_seq.h
*
*  Project Code: VISP1.5
*   Module Name: IP TCP4  
*  Date Created: 2000-03-25
*        Author: Chen Bin
*   Description: TCP序号操作相关的宏
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2000-03-25  Chen Bin         Create the first version.
*
*******************************************************************************/
#ifndef _TCP_SEQ_H
#define _TCP_SEQ_H

#ifdef  __cplusplus
extern  "C"{
#endif

/* #include "kern\os_inter.h" */

#define SEQ_LT(a,b) ((LONG)((a)-(b)) < 0)
#define SEQ_LEQ(a,b)    ((LONG)((a)-(b)) <= 0)
#define SEQ_GT(a,b) ((LONG)((a)-(b)) > 0)
#define SEQ_GEQ(a,b)    ((LONG)((a)-(b)) >= 0)

/*
 * Macros to initialize tcp sequence numbers for
 * send and receive from initial send and receive
 * sequence numbers.
 */
#define TCP_RCVSEQINIT(pTCPCB) \
    (pTCPCB)->seqRcvAdvertise = (pTCPCB)->seqRcvNxt = (pTCPCB)->seqInitRcvSeq + 1

#define TCP_SENDSEQINIT(pTCPCB) \
    (pTCPCB)->seqSndUnack = (pTCPCB)->seqSndNxt = (pTCPCB)->seqSndMax = \
        (pTCPCB)->seqSndUrgentPoint = (pTCPCB)->seqISS

/*#define   TCP_RANDOM18()  ((OS_GetTime() >> 14) & 0x3ffff)

#define TCP_ISSINCR (122L*1024L + TCP_RANDOM18())*/
/* seqTCPISS is increased with tcp_issincr every 500ms 
 * and every time a connection is established */
#define TCP_ISSINCR   128000

#define ISN_BYTES_PER_SECOND    (1024*1024)
#define ISN_STATIC_INCREMENT    4096
#define ISN_RADNOM_INCREMENT    (4096-1)
#define ISN_BYTES_FREQUENCY     100
#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */


#endif

