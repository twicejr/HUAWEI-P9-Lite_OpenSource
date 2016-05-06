/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trrt_fun.h
*
*  Project Code: VISP1.5
*   Module Name: Traceroute Module 
*  Date Created: 2003-07-14
*        Author: suraj( )
*   Description: This file contatins the declarations of the external interfaces used 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2003-07-14  suraj( )         Creat the first version.
*
*******************************************************************************/
#ifndef _TRACERT_FUNC_H_
#define _TRACERT_FUNC_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TRRT_ICMP_HEADLEN        8        /* ICMP首部长度 */

#define TRRT_MIN_IGNORE_MTU      0        /* 多次路径MTU探测可忽略的最小误差值*/

#define TRRT_GET_NEXT_MTU_NORMAL 0       /* 返回正常MTU值*/
#define TRRT_GET_NEXT_MTU_ZERO   1       /* 返回MTU值为0 */
#define TRRT_GET_NEXT_MTU_ERROR  2       /* 返回MTU值错误 */

enum enumMultiPmtuDetectState
{
    TRRT_MULTI_PMTU_DETECT_OFF,      /* 多次PMTU探测开关关闭 */
    TRRT_MULTI_PMTU_DETECT_ON,       /* 多次探测取最开关打开，当路径中存在老路由器或黑洞路由器时需要打开 */
};

typedef struct tagTrrtMultiPMTUDetect
{
    USHORT    usHighPMTU;          /* 二分法PMTU高位值，此值以上为路径无法通过的报文长度 */
    USHORT    usLowPMTU;           /* 二分法PMTU低位值 此值以下为路径已探测到可以通过的报文长度 */
    USHORT    usCurrentPMTU;       /* 多次探测MTU的当前所用MTU值 */
    USHORT    usPmtuDetectState;   /* 当前PMTU多次探测状态开开关值 */
}TRRT_MULTI_PMTU_DETECT_S;

extern USHORT g_usTrrtMinPort;        /* 用户设置的目的端口号下限，缺省值为49152 */
extern USHORT g_usTrrtMaxPort;        /* 用户设置的目的端口号上限，缺省值为65535 */
extern USHORT g_usTrrtDefaultPort;    /* 用户设置的默认目的端口号，缺省值为52889 */

/* 回调函数*/
extern    TRRT_SH_CALLBACK_S  g_stTrrtCallFuction;
/*------------------------------------------------------------------------*/
/*                 ipv6                                                   */
/*------------------------------------------------------------------------*/

ULONG TRACERTV6_TraceRoute( ULONG ulExecID, struct tagTrrtDetectMtuParam *pstTrrtParam);
VOID TRACERTV6_SendProbe( ULONG ulExecID, 
         struct tagOutData          *pstOutData, 
         struct tagTraceRoute * pstTraceRouteParam ,              
         LONG lSeq, LONG lTTL, struct timeval *pstTp );
         
LONG TRACERTV6_WaitForReply( ULONG ulExecID, struct timeval stTimeout,
         struct tagTraceRoute * pstTraceRouteParam ,                               
         SOCKADDR_IN6_S *pstFromp,  msghdr *pstRecvMsg );
         
LONG TRACERTV6_PacketOk( ULONG ulExecID, struct tagTraceRoute * pstTraceRouteParam ,              
         UCHAR *pucBuf, LONG lCc,
         SOCKADDR_IN6_S *pstFrom, LONG lSeq );
         
CHAR *TRACERTV6_PrType( UCHAR );

VOID TRACERTV6_PrintTrace( ULONG ulExecID, struct tagTraceRoute * pstTraceRouteParam ,               
                      LONG lCc, SOCKADDR_IN6_S *pstFrom );

LONG TRACERTV6_Get_HopLim(msghdr * pstRecvMsg);

IP6_PKTINFO_S *TRACERTV6_Get_RcvPktInfo(msghdr * pstRecvMsg);


ULONG  TRACERT_TraceRoute( ULONG ulExecID, struct tagTrrtDetectMtuParam *pstTrrtParam);
VOID  TRACERT_SendProbe( ULONG ulExecID, struct tagIP  *pstOutIP,
         struct tagUDPHDR        *pstOutUdp,  
         struct tagOutData          *pstOutData, 
         struct tagTraceRoute * pstTraceRouteParam ,              
         LONG lSeq, LONG lTTL, struct timeval *pstTp );
         
LONG TRACERT_WaitForReply( ULONG ulExecID, struct timeval stTimeout,
         struct tagTraceRoute * pstTraceRouteParam ,                               
         LONG lSock, struct sockaddr_in *pstFromp );
         
LONG TRACERT_PacketOk( ULONG ulExecID,  struct tagTraceRoute * pstTraceRouteParam ,              
         UCHAR *pucBuf, LONG lCc,
         struct sockaddr_in *pstFrom, LONG lSeq );
         
CHAR *TRACERT_PrType( UCHAR );

VOID TRACERT_PrintTrace( ULONG ulExecID,  struct tagTraceRoute * pstTraceRouteParam ,               
         UCHAR *pucBuf, 
         LONG lCc, struct sockaddr_in *pstFrom );
         
ULONG TRACERT_IsSupportOutIf(ULONG ulIfIndex);

ULONG TRACERT_Timer_Read( );

extern TCPIP_TRRTOutput_HOOK_FUNC g_pstTRRTOutputHook;
VOID TCPIP_TRRTOutput(CHAR *szBuf);

extern TCPIP_TRRTExOutput_HOOK_FUNC g_pstTRRTExOutputHook;
VOID TCPIP_TRRTOutputEx(CHAR *szBuf,ULONG ulExecID);

extern TCPIP_TRRTSTAT_HOOK_FUNC g_pfTrrtStatOutputHook;

extern TCPIP_TRRTEXSTAT_HOOK_FUNC g_pfTrrtExStatOutputHook;

extern TCPIP_TRRTDETECTMTU_HOOK_FUNC g_pfTrrtDetectMtuHook;

ULONG TRRT_GetNextMtu(CHAR *pcBuf, ULONG *ulMtu, ULONG *ulDstIp,ULONG ulMaxMtu);

#ifdef __cplusplus
}
#endif

#endif
