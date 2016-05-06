

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

#ifndef _UDP6_H
#define _UDP6_H

#ifdef    __cplusplus
extern    "C"{
#endif

#define SID_UDP6_INPUT_NEAT       63   /*SID of UDP6*/

#define UDP6CTL_SENDSPACE    1    /* default send buffer */

#define UDP6CTL_RECVSPACE    2    /* default recv buffer */

#define IP6_UDP6_SOCK_SET_PARAM   (g_pfUDP6SocketAPI->pfIP6_Socket_SetParameter)
#define IP6_UDP6_SOCK_GET_PARAM   (g_pfUDP6SocketAPI->pfIP6_Socket_GetParameter)
#if (UDP6_VRP_MODULE_IPV6_VPN == VRP_YES)
/* KLSRINI : Added for supporting SOCKIP interface change */
#define     IP6_UDP6_SOCKET_GET_EXTOPTS(ulSocket, pulExtOpts) \
(VOID)IP6_UDP6_SOCK_GET_PARAM((ulSocket), IP6_SOCKET_EXTOPTIONS, (pulExtOpts))
#endif

#define  UDP6_ASYNRECALL          (g_pfUDP6SocketAPI->pfSO6_AsynReCall)
#define  UDP6_SOWAKEUP            (g_pfUDP6SocketAPI->pfSo6WakeUp)
#define  UDP6_ASYNWAKEUP          (g_pfUDP6SocketAPI->pfSO6_AsynWakeUp)
#define  UDP6_SB_APPENDADDR       (g_pfUDP6SocketAPI->pfSB6_AppendAddr)
#define  UDP6_SOCANTSENDMORE      (g_pfUDP6SocketAPI->pfSO6_CantSendMore)
#define  UDP6_SOISCONNECTED       (g_pfUDP6SocketAPI->pfSO6_IsConnected)
#define  UDP6_SOISDISCONNECTED    (g_pfUDP6SocketAPI->pfSO6_IsDisconnected)
#define  UDP6_SO_RESERVE          (g_pfUDP6SocketAPI->pfSO6_Reserve)
#define  UDP6_SYSCTL_INT          (g_pfUDP6SocketAPI->pfSysCtl_int)
#define  UDP6_SOCK_GETERRMAP      (g_pfUDP6SocketAPI->pfSock_IP6_GetErrMap)

#if(TCPIP_IN_VRP == VRP_NO)
#define UDP6_SRCCACHE_SEARCH  (g_pfUDP6SocketAPI->pfHeadCache6_LookUpSrcAddr)
#else
#define UDP6_SRCCACHE_SEARCH(a, b, c, d, e) (VOS_ERR)
#endif

#define IP6_UDP6_IN6PCB_SET_PARAM \
    (g_pfUDP6In6PCBCallBack->pfIP6_IN6PCB_SetParameter)

#define IP6_UDP6_IN6PCB_GET_PARAM \
    (g_pfUDP6In6PCBCallBack->pfIP6_IN6PCB_GetParameter)

#define IP6_UDP6_IN6PCB_HASH_SEARCH \
    (g_pfUDP6In6PCBCallBack->pfIN6PCB_HashSearch)

#define IP6_UDP6_IN6PCB_GET_HASH_FIRST \
    (g_pfUDP6In6PCBCallBack->pfIP6_IN6PCB_GetHashFHT)

#define IP6_UDP6_IN6PCB_GET_HASH_SECOND \
    (g_pfUDP6In6PCBCallBack->pfIP6_IN6PCB_GetIN6PCBFromSecondHash)


#define UDP6_TASKID_MIN 1
#define UDP6_TASKID_MAX 100
#define UDP6_SOCKID_MAX 3072

#define UDP6_DEBUG_DISABLE 0
#define UDP6_DEBUG_ENABLE 1
#define UDP6_SOCK_FILT_PERMIT   0
#define UDP6_SOCK_FILT_DENY    1

#define UDP6_ERROR_MEMNOTFREED 1
#define UDP6_ERROR_MEMFREED 2
#define UDP6_OK 0

#define UDP6_INVALID_IFINDEX 0xffffffff

#define UDP6_INVALID_ZONEID 0xffffffff

#define UDP6_NOIFINDEX 0

#if (ARM_SUPPORT == VRP_YES)
#define UDP6_CHECK_MEMORYADDRESS(pstPointer)   \
{\
    if (0 != ((ULONG)pstPointer % 4 ))\
    {\
        VOS_DBGASSERT(0);\
    }\
}
#else
#define UDP6_CHECK_MEMORYADDRESS(pstPointer)
#endif

#define UDP6_SOCKBUFTYPE_RCV   2
#define UDP6_SOCKBUFTYPE_SND   1

/*Default value for socket send buffer*/
#define  UDP6_DEF_SEND_SPACE    9216

/*Default value for socket receive buffer*/
#define  UDP6_DEF_RECV_SPACE     (40 * (1024 + sizeof(SOCKADDR_IN6_S)))

#define UDP6_DEFHOPLIMIT    -1

#ifndef NO_USE
#define NO_USE(var)     ((VOID)(var))
#endif


/* For VISP LOG Framework */
#define IP6_NULL_LOGID     0
#define IP6_NULL_PARA      0

/* Added by Anand - V1R7 Workspace Integration */
#define UDP6_MEM_ZERO(m_pBufPtr, m_ulBufLen)\
                        (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), 0, (m_ulBufLen))

VOID    IP6_UDP6_CtlInput(LONG cmd, VOID *pSockAd, VOID *pIpCtl);
VOID    IP6_UDP6_Init(VOID);
ULONG   IP6_UDP6_Input(MBUF_S **ppstMBuf, ULONG *pulOff, ULONG ulProto);
LONG     IP6_UDP6_Output(UINTPTR ulInPcb,MBUF_S *pMBuf, MBUF_S *pMAddr,
                                 MBUF_S *pMCtl);
LONG IP6_UDP6_SysCtl(LONG *pName, ULONG ulNameLen,
                    VOID *pOld, ULONG *pulOldLen, VOID *pNew, ULONG ultNewLen);
LONG IP6_UDP6_UsrReq(UINTPTR  ulSock, LONG nReq,
                VOID *pMBuf, VOID *pMAddr, VOID *pMCtl);
VOID IP6_UDP6_ClearStatist(VOID);
VOID IP6_UDP6_DisplayStatist(ULONG ulLanMode, CHAR *szOut);
IP6_UDP6_MIB_CONN_S* IP6_UDP6_ConnTableMatch(IN6ADDR_S  *pstLAddr,
                                                ULONG ulLPort, ULONG ulIfIndx);
IP6_UDP6_MIB_CONN_S* IP6_UDP6_ConnTableGetNext(IN6ADDR_S  stLAddr,
                                                ULONG ulLPort, ULONG ulIfIndx);

IP6_UDP6_MIB_CONN_S* IP6_UDP6_ConnTableGetFirst(VOID);

LONG IP6_UDP6_CtlOutput(LONG lOper, UINTPTR ulSocket, LONG lLevel,
                            LONG lOptName, MBUF_S **ppMBuf);

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */
#endif

