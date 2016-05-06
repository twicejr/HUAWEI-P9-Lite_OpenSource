/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              vrp_pktqueue.h
*
*  Project Code: VISPV100R005
*   Module Name: VRPVOS  
*  Date Created: 2002-5-6
*        Author: zhu heng jun(08391)
*   Description: TCPIP独立协议栈系统参考模型队列调度头文件，依照原VRP实现
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-5-6  zhu heng jun(08391)  Create the first version.
*  2006-4-27 wang xin(03278)      根据编程规范，对文件进行规范化整理
*******************************************************************************/

#ifndef    _VRP_PKTQUEUE_H_
#define    _VRP_PKTQUEUE_H_

#ifdef    __cplusplus
extern "C"{
#endif

#include "tcpip/public/tcpip_pub_api.h"

#define        VRP_MAX_QUEUE_NUM         32
#define        VRP_LINKLAYER_QUEUE_LEN   2048
#define        VRP_DEFAULT_QUEUE_LEN     1024
#define        VRP_FORWARD_QUEUE_LEN     1800
#define        VRP_MAX_QUEUE_LIMITED     10000
#define        VRP_QUE_MIN_PKT_PER_TIME  1
#define        VRP_QUE_DEFAULT_PKT_PER_TIME    VRP_DEFAULT_QUEUE_LEN
#define        VRP_QUE_ACTIVE            2
#define        VRP_QUE_REGISTERED        1 
#define        VRP_QUE_EMPTY             0 
#define        VRP_QUE_ERROR             1
#define        VRP_QUE_NOERR             0

typedef ULONG    (* QueDealPacketFunc)(MBUF_S *);            /* 处理包的函数 */
typedef ULONG    (* QueIsDropThisPacketFunc)(MBUF_S *,ULONG,CHAR*);    /* 是否丢弃 */


typedef struct tagQELEMENT
{
    MBUF_QUEUE_S    stQueueIn;               /* 入队列 */
    MBUF_QUEUE_S    stQueueOut;              /* 出队列 */
    ULONG           ulOutPktPerTimes;        /* 一次取出的数目 */
    ULONG           (* Que_pfDealPacket)(MBUF_S *);                      /* 处理包的函数 */
    ULONG           (* Que_pfIsDropThisPacket)(MBUF_S *,ULONG,CHAR*);    /* 是否丢弃 */
    ULONG           ulNextActiveQueID;        /* 下一个活动队列ID */
    ULONG           ulPreActiveQueID;         /* 上一个活动队列ID */
    ULONG           ulSelfID;                 /* 本队列ID */
}QELEMENT_S;


/* 使用这个宏为SockRun任务的子任务设置调度标志*/
#define    VRP_SchedSock() \
{ \
    (VOID)VOS_Ev_Write( ulVRPTID_SOCK, VRP_SOCK_EVENT_DATAREQ ); \
}

extern ULONG g_ulLinkSchNum;

extern QELEMENT_S gpstQueue[QUE_MAX_NUMBER];


/* function */
ULONG    Que_SetQueLen(ULONG ulQueID,ULONG ulMaxLen);

ULONG    Que_EnQueue(MBUF_S* pMBuf);

ULONG    Que_RegisterQue(ULONG ulQueID,ULONG ulGetCntPerTimes,
                         QueDealPacketFunc pfDealPkt,
                         QueIsDropThisPacketFunc pfIsDropThisPkt,ULONG ulMaxLen);

ULONG   Que_UnRegisterQue(ULONG ulQueID);

ULONG   Que_ActiveQue(ULONG ulQueID);

ULONG   Que_DeActiveQue(ULONG ulQueID);

ULONG   Que_Init(VOID);

VOID    Que_DealPackets(ULONG ulQueID);

VOID    Que_Schedule(VOID);

VOID    Que_FreePacketInQueueForRequest(ULONG ulQueID,ULONG ulCmd,CHAR* pData);

ULONG   Que_GetOutPktPerTimes(ULONG ulQueID);



#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

