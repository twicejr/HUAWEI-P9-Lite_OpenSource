/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcp_time.h
*
*  Project Code: VISP1.5
*   Module Name: IP TCP4  
*  Date Created: 2000-03-25
*        Author: Chen Bin
*   Description: TCP定时器相关的常量和宏定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2000-03-25  Chen Bin         Create the first version.
*
*******************************************************************************/
#ifndef _TCP_TIME_H
#define _TCP_TIME_H

#ifdef __cplusplus
extern "C"{
#endif

/*
 * Definitions of the TCP timers.  These timers are counted
 * down PR_SLOWHZ times a second.
 */
#define    TCPT_NTIMERS     4

#define    TCPT_REXMT       0    /* retransmit                 */
#define    TCPT_PERSIST     1    /* retransmit persistance     */
#define    TCPT_KEEP        2    /* keep alive                 */
#define    TCPT_2MSL        3    /* 2*msl quiet time timer     */

/* 时间常量  Time constants */
#define    TCPTV_MSL        (30*PR_SLOWHZ)      /* 最大生存时间           max seg lifetime (hah!) */
#define    TCPTV_SRTTBASE   0                   /* 基础持续时间           base roundtrip time;  */
                                                /* 如果值为零表示还不知道   if 0, no idea yet */
#define    TCPTV_SRTTDFLT   (3*PR_SLOWHZ)       /* 没有其它信息时的假定RTT值          assumed RTT if no info */
                                                                
#define    TCPTV_PERSMIN    (5*PR_SLOWHZ)        /* 持续转发时间           retransmit persistance */
#define    TCPTV_PERSMAX    (60*PR_SLOWHZ)       /* 最大持续时间间隔       maximum persist interval */                                                  
#define    TCPTV_KEEP_INIT  (75*PR_SLOWHZ)       /* 维持有效的最初连接     initial connect keep alive */
#define    TCPTV_KEEP_IDLE  (120*60*PR_SLOWHZ)   /* 查询前空闲时间         dflt time before probing */
#define    TCPTV_KEEPINTVL  (75*PR_SLOWHZ)       /* 默认查询时间间隔       default probe interval */
#define    TCPTV_KEEPCNT    8                    /* 丢弃前最大查询数目     max probes before drop */
                                                
#define    TCPTV_MIN        (1*PR_SLOWHZ)        /* 最小允许值         minimum allowable value */
#define    TCPTV_REXMTMAX   (64*PR_SLOWHZ)       /* 最大允许REXMT值    max allowable REXMT value */
                                                 
#define    TCP_LINGERTIME   120                  /* 滞留时间2分钟       linger at most 2 minutes */                                            
#define    TCP_MAXRXTSHIFT  12                   /* 最大转发数目     maximum retransmits */

/* Add for DTS2011042101731, by z00166124, at 2011-04-21. 修改原因: 重传日志的记录门限 */
#define    TCP_RXTSHIFT_LOGTHRESHOLD  5             /* 重传记录日志的门限 */

#ifdef    TCPTIMERS
CHAR *psTCPTimers[] =
    {  "REXMT",           /* 重传定时器 */
       "PERSIST",         /* 坚持定时器 */  
       "KEEP",            /* 饱和定时器 */   
       "2MSL"             /* 2MSL定时器 */
    };
#endif

/* Force a time value to be in a certain range. */
#define    TCPT_RANGESET(tv, value, tvmin, tvmax) { \
    if ((ULONG)(value) < (ULONG)(tvmin)) \
        (tv) = (tvmin); \
    else if ((ULONG)(value) > (ULONG)(tvmax)) \
        (tv) = (tvmax); \
    else \
        (tv) = (SHORT)(value); \
}

#define    TCPT_ACKDELAYSTAT(cur, last, total, totaldev) { \
    total += cur; \
    if (last) \
    { \
        totaldev += (cur > last) ? (cur - last) : (last - cur); \
    } \
    last = cur; \
}

/* insert tcpcb into g_pstTcpFastHead */
/*#define TCPT_INSFASTTIME( pTCPCB )   \
    if( ((pTCPCB)->pNextFastTimer==NULL)&&((pTCPCB)->pPrevFastTimer==NULL)) \
    { \
        (pTCPCB)->pNextFastTimer = g_pstTcpFastHead; \
        g_pstTcpFastHead = (pTCPCB); \
    }


#define TCPT_DELFASTTIME( pTCPCB )   \
{ \
    if( (pTCPCB)->pNextFastTimer ) \
    { \
        (pTCPCB)->pNextFastTimer->pPrevFastTimer = (pTCPCB)->pPrevFastTimer; \
    } \
    if( (pTCPCB)->pPrevFastTimer ) \
    { \
        (pTCPCB)->pPrevFastTimer->pNextFastTimer = (pTCPCB)->pNextFastTimer; \
    } \
    else if( g_pstTcpFastHead == (pTCPCB) ) \
    { \
        g_pstTcpFastHead = (pTCPCB)->pNextFastTimer; \
    } \
    (pTCPCB)->pNextFastTimer = NULL; \
    (pTCPCB)->pPrevFastTimer = NULL; \
}*/


#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

