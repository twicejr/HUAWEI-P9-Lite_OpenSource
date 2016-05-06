/*****************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------
*                              tcp6_var.h
*
*    Project Code:      VRP5.0
*    Module Name:  IP6 TCP6
*    Version    : Initial Draft
*    Create Date:      2003/06/27
*    Author:           Naina Gupta
*    Description:  Contains the set  declaration for the globals, internal
*                 functions along with defines to access the socket registered
*                 functions
*-----------------------------------------------------------------
*  Modification History
*  DATE                NAME                 DESCRIPTION
*  ----------------------------------------------------------------
*  2003-06-27      Naina Gupta     Created
*  2006-06-02      Alok            Updated for 14 Fly-Check rules adherence
*                                  for IPOSIR-V1R1-IPv6
*  2006-08-29      Prabhu H        Updated for RFC 4022 MIB implmentation
******************************************************************
*/

#ifndef _TCP6_VAR_H
#define _TCP6_VAR_H

#ifdef    __cplusplus
extern    "C"{
#endif

/* Reason: This data structure needs to be moved to the public header file
           (tcp6_pub_type.h) and that in turn needs to be
           included in this file*/
#include "common/ipos/ipv6/tcp6_public.h"
#include "ipv6/tcp6/include/tcp6_int_pub.h"

extern TCP6_MOD_INFO_S   g_stTCP6ModInfo;

/*  0x0392001e, SOCKET -- TCPTemplate() */
#define mid_TCP6_TCPTEMPLATE (g_stTCP6ModInfo.ulModID | 30)

/*  0x0392001f, SOCKET -- TCPRespond() */
#define mid_TCP6_TCPRESPOND (g_stTCP6ModInfo.ulModID | 31)

/*  0x03920020, SOCKET -- TCPNewTCPCB() */
#define mid_TCP6_TCPNEWTCPCB (g_stTCP6ModInfo.ulModID | 32)

/*  0x03920022, SOCKET -- TCPOutput() */
#define mid_TCP6_TCPOUTPUT (g_stTCP6ModInfo.ulModID | 33)

/*  0x03920023, SOCKET -- TCPUserRequest() */
#define mid_TCP6_TCPUSERREQUEST (g_stTCP6ModInfo.ulModID | 34)

/*  0x03920024, SOCKET -- TCPCtlOutput() */
#define mid_TCP6_TCPCTLOUTPUT (g_stTCP6ModInfo.ulModID | 35)

#define TCP6_NODELAY         1       /* set/get tcp nodelay option */
#define TCP6_MAXSEG          2       /* set/get tcp max segment size */
#define TCP6_STDURG          3
#define TCP6_KEEPALIVE_IDLE  4       /* set/get TCP Keepalive timer value */
#define TCP6_KEEPALIVE_CNT   5       /* set/get TCP Keepalive probe count */
#define TCP6_KEEPALIVE_INTVL 6       /* set/get TCP Keepalive probing interval*/
#define TCP6_MSL             7       /* set/get TCP Maximum Segment Lifetime */

 /* Added by Rajesh/Suraj for Defect BYAD13890 IPsec6 */
#define TCP6_BINDFOREIGNADDR    8   /*IR_DEP_REMV:v5r2 merge, 2006-06-30*/


#define    TCP6_RTT_SCALE        8     /****** 亩蔚淖畛な奔鋗multiplier for source retransmission timer .3 bits fraction   ******/ 
#define    TCP6_RTT_SHIFT        3     /****** 段的最长时间shift for source retransmission timer 3 bits fraction           ******/
#define    TCP6_RTTVAR_SCALE    4      /****** 段的最长时间multiplier for retransmission timer var; 2 bits                 ******/ 
#define    TCP6_RTTVAR_SHIFT    2      /****** 段的最长时间multiplier for retransmission timer var; 2 bits                 ******/ 

#define    TCP6_OFFSET_VALUE   5

/* Reason: Macro definitions for slave and master boards */
#define TCP6_SMB 1
#define TCP6_AMB 0

#define    TCP6_REXMTVAL(t6p) \
    (((t6p)->sSRTT >> TCP6_RTT_SHIFT) + (t6p)->sRTTVar)

#define REASS_MBUF6(i6tr) (*(struct tagMBuf **)&((i6tr)->i6tr_m))

/* insert tcpcb into fast timer serial */
/*
 * if this tcpcb is already in the fast timeout train,
 * we do not insert it once more.
 */

#define TCP6T_INSFASTTIMER(pstTCP6CB)   \
{   \
    if ((NULL == pstTCP6CB->pNextFastTimer) \
        && (NULL == pstTCP6CB->pPrevFastTimer) \
        && (g_pstTcp6FastHead != (pstTCP6CB)) \
        ) \
    { \
        (pstTCP6CB)->pNextFastTimer = g_pstTcp6FastHead; \
        if ( g_pstTcp6FastHead ) \
        { \
            g_pstTcp6FastHead->pPrevFastTimer = (pstTCP6CB); \
        } \
        g_pstTcp6FastHead = (pstTCP6CB); \
    } \
}


/* del tcpcb from fast timer serial */
/* although if pNextFastTimer,pPrevFastTimer all are null,
 * it may be in the serial, because g_pstTcpFastHead == pTcpcb */
#define TCP6T_DELFASTTIMER(pstTCP6CB)   \
{  \
    if ((pstTCP6CB)->pNextFastTimer)  \
    { \
        (pstTCP6CB)->pNextFastTimer->pPrevFastTimer = \
                        (pstTCP6CB)->pPrevFastTimer; \
    } \
    if ((pstTCP6CB)->pPrevFastTimer) \
    { \
        (pstTCP6CB)->pPrevFastTimer->pNextFastTimer = \
                        (pstTCP6CB)->pNextFastTimer; \
    } \
    else if (g_pstTcp6FastHead == (pstTCP6CB)) \
    { \
        g_pstTcp6FastHead = (pstTCP6CB)->pNextFastTimer; \
    } \
    (pstTCP6CB)->pNextFastTimer = NULL; \
    (pstTCP6CB)->pPrevFastTimer = NULL; \
}

extern UCHAR   ucTCP6OutFlags[TCP6_NSTATES];
extern SHORT   sTCP6BackOff[TCP6_MAXRXTSHIFT + 1];

#define TCP6_PAWS_IDLE   (24 * 24 * 60 * 60 * (PR_SLOWHZ))

/* used in TCPInput(), it is the second of 24 days */
#define TCP_PAWS_IDLE   (24 * 24 * 60 * 60 * (PR_SLOWHZ))

/* Comparisons of timestamps */
#define TSTMP_LT(a,b)   ((LONG)((a) - (b)) < 0)
#define TSTMP_GEQ(a,b)  ((LONG)((a) - (b)) >= 0)

#define MAX_TCP6OPTLEN    32       /* max # bytes that go in options */


#define TCP6_DBUG_OFF 0
extern ULONG g_ulTcp6DbugFlag;

extern SOSB6_CALLBACUP_SET_S      *g_pstTCP6CallBackupSocket;
extern IN6PCB_CALLBACUP_SET_S     *g_pstTCP6CallBackupIn6PCB;

extern IP6_TCP6_SH_CALLBACUP_SET_S    *g_pstTCP6Callback;

#define     IP6_TCP6_SOCKET_ID_CHECK      \
            (g_pstTCP6CallBackupSocket->pfSOCK6_SocketID_Check)
#define     IP6_TCP6_SOCKET_GET_PARAM      \
            (g_pstTCP6CallBackupSocket->pfIP6_Socket_GetParameter)
#define     IP6_TCP6_SOCKET_SET_PARAM      \
            (g_pstTCP6CallBackupSocket->pfIP6_Socket_SetParameter)
#if (TCP6_VRP_MODULE_IPV6_VPN == VRP_YES)

/* KLSRINI : Added for supporting SOCKIP interface change */
#define     IP6_TCP6_SOCKET_GET_EXTOPTS(ulSocket, pulExtOpts) \
    IP6_TCP6_SOCKET_GET_PARAM((ulSocket), IP6_SOCKET_EXTOPTIONS, (pulExtOpts))
#define     IP6_TCP6_SOCKET_SET_EXTOPTS(ulSocket, pulExtOpts) \
    IP6_TCP6_SOCKET_SET_PARAM((ulSocket), IP6_SOCKET_EXTOPTIONS, (pulExtOpts))

#endif

/* macro: get/set in6pcb variables */
#define     IP6_TCP6_IN6PCB_GET_PARAM      \
            (g_pstTCP6CallBackupIn6PCB->pfIP6_IN6PCB_GetParameter)
#define     IP6_TCP6_IN6PCB_SET_PARAM      \
            (g_pstTCP6CallBackupIn6PCB->pfIP6_IN6PCB_SetParameter)

/* macro: socket syscall for tcp */
#define TCP6_SO6_ISDISCONNECTED     \
            g_pstTCP6CallBackupSocket->pfSO6_IsDisconnected
#define TCP6_SO6_ISCONNECTED        \
            g_pstTCP6CallBackupSocket->pfSO6_IsConnected
#define TCP6_SO6_ISCONNECTING       \
            g_pstTCP6CallBackupSocket->pfSO6_IsConnecting
#define TCP6_SO6_ISDISCONNECTING    \
            g_pstTCP6CallBackupSocket->pfSO6_IsDisconnecting
#define TCP6_SO6_NEWCONN            g_pstTCP6CallBackupSocket->pfSO6_NewConn
#define TCP6_SB6_DROP               g_pstTCP6CallBackupSocket->pfSB6_Drop
#define TCP6_SO6_ABORT              g_pstTCP6CallBackupSocket->pfSO6_Abort
#define TCP6_DEBUGTOIC              g_pstTCP6Callback->pfIP6_TCP6_SH_SendInfo2IC
#define TCP6_DBUGPKT                g_pstTCP6Callback->pfIP6_TCP6_DbugPkt
#define TCP6_SB6_APPEND             g_pstTCP6CallBackupSocket->pfSB6_Append
#define TCP6_WAKEUP                 g_pstTCP6CallBackupSocket->pfWakeUp
#define TCP6_SORWAKEUP(so)          \
            g_pstTCP6CallBackupSocket->pfSo6WakeUp((so), 2)
#define TCP6_SOWWAKEUP(so)          \
            g_pstTCP6CallBackupSocket->pfSo6WakeUp((so), 1)
#define TCP6_SO6_CHECKCOOKIESTART   g_pstTCP6CallBackupSocket->pfSO6_CheckCookieStart 
#define TCP6_ASYNWAKEUP             g_pstTCP6CallBackupSocket->pfSO6_AsynWakeUp
#define TCP6_ASYNRECALL             g_pstTCP6CallBackupSocket->pfSO6_AsynReCall
#define TCP6_IN6PCB_NOTIFY          g_pstTCP6CallBackupIn6PCB->pfIN6PCB_Notify
#define TCP6_IN6PCB_BIND            g_pstTCP6CallBackupIn6PCB->pfIN6PCB_Bind
#define TCP6_IN6PCB_ALLOC           g_pstTCP6CallBackupIn6PCB->pfIN6PCB_Alloc
#define TCP6_IN6PCB_DETACH          g_pstTCP6CallBackupIn6PCB->pfIN6PCB_Detach
#define TCP6_IN6PCB_DISCONNECT      \
            g_pstTCP6CallBackupIn6PCB->pfIN6PCB_Disconnect
#define TCP6_IN6PCB_CONNECT         g_pstTCP6CallBackupIn6PCB->pfIN6PCB_Connect
#define TCP6_IN6PCB_HASHSEARCH      \
            g_pstTCP6CallBackupIn6PCB->pfIN6PCB_HashSearch

/* Added by Rajesh/Suraj for Defect BYAD13890 IPsec6 */
#define TCP6_IN6PCB_BFADDR    g_pstTCP6CallBackupIn6PCB->pfIN6PCB_BindFAddress

#define TCP6_IN6PCB_SEARCHSECOND    \
                              g_pstTCP6CallBackupIn6PCB->pfIN6PCB_SearchSecond

#define TCP6_IN6PCB_ATTACH          g_pstTCP6CallBackupIn6PCB->pfIN6PCB_Attach
#define TCP6_IN6PCB_SETPEERADDR     \
            g_pstTCP6CallBackupIn6PCB->pfIN6PCB_SetPeerAddr
#define TCP6_IN6PCB_SETSOCKADDR     \
            g_pstTCP6CallBackupIn6PCB->pfIN6PCB_SetSockAddr
#define TCP6_SB6_FLUSH              g_pstTCP6CallBackupSocket->pfSB6_Flush
#define TCP6_IN6PCB_INIT            g_pstTCP6CallBackupIn6PCB->pfIN6PCB_Init
#define TCP6_SO6_CANTRECVMORE       \
            g_pstTCP6CallBackupSocket->pfSO6_CantRcvMore
#define TCP6_SO6_CANTSENDMORE       \
            g_pstTCP6CallBackupSocket->pfSO6_CantSendMore
#define TCP6_SO6_RESERVE            g_pstTCP6CallBackupSocket->pfSO6_Reserve
#define TCP6_SO6_HASOUTOFBAND       \
            g_pstTCP6CallBackupSocket->pfSO6_HasOutOfBand

/* Reason: These new Socket APIs need to be registered by Socket to eliminate
           direct dependency */

#define TCP6_SO6_HA_EVENT_NOTIFY     \
            g_pstTCP6CallBackupSocket->pfSock_Ha_EventNotify
#define TCP6_SO6_IP6_GETERRMAP       \
            g_pstTCP6CallBackupSocket->pfSock_IP6_GetErrMap
#define TCP6_SO6_INET_NTOP6          g_pstTCP6CallBackupSocket->pfinet_ntop6

#define TCP6_IN6_CKSUM              IPB_IR_IP6_PP_CKSUM
#define TCP6_IP6_OUTPUT             IPB_IR_IP6_PP_OUTPUT
#define TCP6_IP6_EXTHDRLEN          IPB_IR_IP6_PP_EXTHDRLEN
#define TCP6_IP6_CTLOUTPUT          IPB_IR_IP6_PP_CTLOUTPUT
#define TCP6_IP6_COPYPKTOPTS        IPB_IR_IP6_PP_COPYPKTOPTS

/* Appln. specified Hop Limit Value specifying use of Kernel Default Value */
#define TCP6_DEFHOPLIMIT    -1

/* Added by Suraj_R for Per-Connection Statistics */
/* Macro to increment the global and TCP6 connection specific statistics */
#define TCP6_INCR_STATS_BOTH(m_pstTCP6CB, m_StatType, m_Step) \
{                                                             \
    TCP6_INCR_PERCONN_STATS(m_pstTCP6CB, m_StatType, m_Step); \
    TCP6_INCR_GLOBAL_STATS(m_StatType, m_Step);  \
}

/* Macro to increment only the global TCP6 statistics */
#define TCP6_INCR_GLOBAL_STATS(m_StatType, m_Step) \
            (g_stTCP6Stat.m_StatType += m_Step)

/* Macro to increment TCP6 connection specific statistics */
#define TCP6_INCR_PERCONN_STATS(m_pstTCP6CB, m_StatType, m_Step) \
    ((NULL != m_pstTCP6CB) && (NULL != (m_pstTCP6CB->pstTCP6ConnStats)))? \
            ( ((m_pstTCP6CB->pstTCP6ConnStats)->m_StatType) += m_Step):0;

#define TCP6_ISN_CHANGE_LIMIT   1000
#define TCP6_ISN_SEC_SIZE       16

/* function declaration */
LONG                       TCP6_Attach(UINTPTR);
VOID                       TCP6_CancelTimers(struct tagTCP6CB *);
VOID                       TCP6_CtlInput(LONG, VOID *,VOID *);
LONG                       TCP6_CtlOutput(LONG, UINTPTR, LONG, LONG,
                                                struct tagMBuf **);
struct tagTCP6CB           *TCP6_Close(struct tagTCP6CB *);
struct tagTCP6CB           *TCP6_Disconnect(struct tagTCP6CB *);
struct tagTCP6CB           *TCP6_Drop(struct tagTCP6CB *, LONG);
struct tagTCP6CB           *TCP6_NewTCPCB(UINTPTR);
VOID                       TCP6_DoOptions(struct tagTCP6CB *, UCHAR *,
                            LONG, struct tagTCP6HDR *, LONG *,
                            ULONG *, ULONG *);
VOID                       TCP6_Drain(VOID);
VOID                       TCP6_FastTimeOut(VOID);
VOID                       TCP6_Init(VOID);
ULONG                      TCP6_Input(struct tagMBuf **, ULONG *, ULONG);
LONG                       TCP6_Mss(struct tagTCP6CB *, ULONG, TCP6IP6HDR_S *);
VOID                       TCP6_Notify(UINTPTR ulIn6PCB, LONG lError);
LONG                       TCP6_Output(struct tagTCP6CB *);
VOID                       TCP6_PullOutOfBand
                            (UINTPTR, struct tagTCP6IP6HDR *, struct tagMBuf *);
VOID                       TCP6_Quench(UINTPTR, LONG);
LONG                       TCP6_Reass(struct tagTCP6CB  *,
                                            IP6TCP6REASS_S *,
                                            struct tagTCP6HDR*,
                                            struct tagMBuf *, LONG);
VOID                       TCP6_InsQueue(QUEUE_S *pstFrag,
                                                QUEUE_S *pstHead);
VOID                       TCP6_RemQueue(QUEUE_S *pstFrag);
VOID                       TCP6_Respond(TCP6CB_S *pstTCP6CB,
                                                TCP6IP6HDR_S *pstHeader,
                                                MBUF_S *pstRcvSeg,
                                                TCP6_SEQ seqAck,
                                                TCP6_SEQ seqSeq,
                                                LONG  lFlags);
VOID                       TCP6_SetPersist(struct tagTCP6CB *);
VOID                       TCP6_SlowTimeOut(VOID);
struct tagTCP6IP6HDR       *TCP6_Template(struct tagTCP6CB *);
struct tagTCP6CB           *TCP6_Timers(struct tagTCP6CB *, LONG);
struct tagTCP6CB           *TCP6_UsrClosed(struct tagTCP6CB *);
LONG                       TCP6_UserRequest(UINTPTR, LONG, VOID *,
                                                    VOID *, VOID *);
VOID                       TCP6_XmitTimer(struct tagTCP6CB *, SHORT);
VOID                       TCP6_PrintState(SHORT sState,CHAR *pszBuf,INT32 i32BufLen);
VOID                       TCP6_Pmtu_Notify (UINTPTR ulTCP6CB,
                                                     ULONG ulMtuVal,
                                                     UCHAR ucEvokingFlag);
ULONG                       TCP6_GetKeepIdle(UINTPTR ulSocket);
VOID TCP6_RespondEX(TCP6CB_S *pstTCP6CB, TCP6IP6HDR_S *pstHeader, MBUF_S *pstRcvSeg,
                    TCP6_SEQ seqAck, TCP6_SEQ seqSeq, LONG lTcpFlags, UINT16 u16MSS, UINT32 u32TimeStamp);
UINT32 TCPCOOKIE_CalcCookie_Ipv6(TCP6CB_S *pTCP6CB, TCP6IP6HDR_S *pRcvHeader, UINT16 *pu16MSS, UINT32 *pu32TimeStamp);
UINT32 TCPCOOKIE_ChkCookie_Ipv6(TCP6CB_S *pTCP6CB, IP6_S *pstIpHdr, UINT16 *u16MSS);
ULONG TCP6_NeedClose(VOID *pSocket);

/* TCP6 debug packet filter global structure
   Used by : TCP6_ProDbugFilter
             IP6_TCP6_GetDebugFilter
             TCP6_Input
             TCP6_Output
             TCP6_SetFilterZero */

extern TCP6DBUGFILTRD_S      g_stDbugTcp6PktFilter;

/* TCP6 debug Trans filter global structure
   Used by : TCP6_StateChangeOutput
             TCP6_TransaOutput
             TCP6_ProDbugFilter
             IP6_TCP6_GetDebugFilter
             TCP6_SetFilterZero */
extern TCP6DBUGFILTRD_S      g_stDbugTcp6TscFilter;

extern LONG             g_lTCP6TotalBackOff; /* sum of sTCPBackOff */

/* Global variable - Time to wait before sending out the keep alive probe
   Used by : TCP6_Init
             TCP6_Input
             TCP6_Timers */
extern LONG             g_lTCP6KeepIdle;

/* Global variable - TCP6 SYN timeout value
   Used by : TCP6_Init
             TCP6_Input
             TCP6_Timers */
extern LONG             g_lTCP6KeepIntvl;

/* Global variable - max idle probes
   Used by : TCP6_Init */
extern LONG             g_lTCP6KeepCnt;

/* Global variable - max idle time in persist
   Used by : TCP6_Init
             TCP6_Timers */
extern LONG             g_lTCP6MaxPersistIdle;

/* Global variable - TCP6 FIN Timeout value
   Used by : TCP6_Get_Param
             TCP6_Set_Fin_TimeOut
             TCP6_Input
             TCP6_Timers */
extern LONG             g_lTCP6MaxIdle;

/* Global variable - RFC1323 Timestamps
   Used by : TCP6_Init
             TCP6_Input
             TCP6_GetTCP6Now
             TCP6_SetTCP6Now
             TCP6_Output
             TCP6_SlowTimeOut */
extern ULONG            g_ulTCP6Now;



/* Global variable - head of queue of active TCPCBs
   Used by : TCP6_TCP6CBFound
             TCP6_ConnTableMatch
             TCP6_ConnTableGetNext
             TCP6_ConnTableGetFirst
             TCP6_GetIn6PCBFromConnections
             TCP6_OpenObject_TCP6Conn
             TCP6_Get_Object_NextTCP6Conn
             TCP6_Get_TCPCBParam
             TCP6_Get_ulCurrEstablished
             TCP6_Close
             TCP6_CtlInput
             TCP6_Init
             TCP6_SlowTimeOut
             TCP6_Attach */
extern UINTPTR          g_ulTCP6Conn;

/* Global variable - TCP fast timer head structure
   Used by : TCP6_TCP6CBFound
             TCP6T_INSFASTTIMER macro also uses this global  */
extern TCP6CB_S        *g_pstTcp6FastHead;

/* Global variable - hash table structure
   Used by : TCP6_Init
             TCP6_Input
             TCP6_Attach */
extern UINTPTR          g_ulTCP6Hash;

/* Global variable - TCP Send space
   Used by : TCP6_Get_Param
             TCP6_Set_Window
             TCP6_Init
             TCP6_Attach */
extern ULONG           g_ulTCP6SndSpace;

/* Global variable - TCP Receive space
   Used by : TCP6_Set_Window
             TCP6_Init
             TCP6_Attach */
extern ULONG           g_ulTCP6RcvSpace;

/* Global variable - TCP6 Statistics */
extern TCP6STAT_S      g_stTCP6Stat;

/* Global variable - TCP6 Max Segment Size
   Used by : TCP6_NewTCPCB
             TCP6_Init
             TCP6_Mss */
extern LONG             g_lTCP6MSSDefault;

/* Global variable - TCP6 Round Trip time
   Used by : TCP6_Init
             TCP6_NewTCPCB */
extern LONG             g_lTCP6RTTDefault;

/* Global variable - If this is set, Window scale and Timestamp options
                     are supported
   Used by : TCP6_Init
             TCP6_NewTCPCB */
extern LONG             g_lTCP6DoRFC1323;

/* Global variable - Threshold value for number of retransmissions
   Used by : TCP6_Init
             TCP6_Input */
extern LONG             g_lTCP6RexmtThresh;

/* Global variable - pointer to last IN6PCB
   Used by : TCP6_Init
             TCP6_Close
             TCP6_Input */
extern UINTPTR          g_ulTCP6LastInPCB;

/* Global variable - Largest link-level header
   Used by : TCP6_Init
             TCP6_Output
             TCP6_Respond */
extern LONG             g_lMaxLinkHdr;

/* Global variable - Largest protocol header
   Used by : TCP6_Init */
extern LONG             g_lMaxProtoHdr;

/* Global variable - To record foreign address
   Used by : TCP6_Init
             TCP6_Input */
extern SOCKADDR_IN6_S   g_stForeignAddr;

/* Added in IR V1R3 by Arvind for Hop Limit Issue */
extern ULONG g_ulTCP6IsHostNode;    /* Node Type (Host/Router) */

typedef ULONG (*TCP_NEED_CLOSE_HOOK)(VOID *pSocket);
extern TCP_NEED_CLOSE_HOOK g_pfTcp6NeedClose;

extern VOID TCP6_StatDelay(TCP6CB_S *pTCP6CB);

extern VOID TCP6_RandIsnSec();

extern VOID TCP6_ISNTick();

extern ULONG TCP6_NewISN(TCP6CB_S * pTCP6CB);
#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

