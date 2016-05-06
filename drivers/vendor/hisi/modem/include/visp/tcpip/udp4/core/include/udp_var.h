/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              udp_var.h
*
*  Project Code: VISP1.5
*   Module Name: udp4
*  Date Created: 2004-04-25
*        Author: WeiYongDong
*   Description: 声明udp模块的全局变量及定义udp使用的宏定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2004-04-25  WeiYongDong      Create the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/

#ifndef _UDP_VAR_H_
#define _UDP_VAR_H_

#ifdef __cplusplus
extern "C" {
#endif

extern struct ComponentInfo m_CompUDP4Info; /*UDP4组件信息*/
extern UDPSTAT_S    g_stUdpStat;            /* UDP statistics */
extern VOID         *g_pstUdb;              /*The header of UDP INPCB link*/
extern PCBHASH_S    *g_pstUdpHash;          /*UDP Hash table*/
extern ULONG   g_ulUdpCksum;                /* UDP Cksum */

extern ULONG   g_ulUdpSendSpace;            /* UDP4 Socket默认发送缓冲区大小 */
extern ULONG   g_ulUdpRecvSpace;            /* UDP4 Socket默认接收缓冲区大小 */

extern SOCKADDRIN_S stUdpIn ;               /* 记录报文的源端口与源地址信息 */

extern UDP_DEBUGFILTER_S    g_stDbugUdpPktFilter; /*UDP debug filter*/
extern ULONG                g_ulUdpPktDbugFlag;   /*UDP debug Flag*/

extern ULONG g_ulUdp4IKETaskId;   /* UDP4模块中记录的IKE任务ID */

extern IP4_UDP4_MOD_INFO_S              g_stUDPModInfo;  /*UDP module information*/
extern IP4_UDP4_SH_CALLBACUP_SET_S      g_stUDPCallback; /*UDP callback functions set*/

/*UDP4组件调用到其他组件的接口虚表*/
extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl         *g_pstUDPAddr4Vtbl ; /*AM4组件的功能接口虚表*/
extern struct IIF_IPV4_IP_PP4_ComIntFUNVtbl         *g_pstUDPPP4Vtbl ;   /*PP4组件的功能接口虚表*/
extern struct IIF_IPV4_IP_ICMP_ComIntFUNVtbl        *g_pstUDPICMP4Vtbl ; /*ICMP4组件的功能接口虚表*/
extern struct IIF_IP4_SOCK_ComIntFunVtbl            *g_pstUDPSOCK4Vtbl ; /*SOCK4组件的功能接口虚表*/
extern struct IIF_COMP_FIBAGENT_ComIntFUNVtbl       *g_pstUDPFIB4Vtbl ;  /*FIBA组件的功能接口虚表*/
extern struct IIF_IPV4_FIBCONTR_ComIntCFGVtbl       *g_pstUDPFib4CCfgTable;  /* FIB4C组件配置接口虚表 */

extern ULONG (*g_pfUDP4_BFD_HOOK)(MBUF_S*);
extern USHORT IN_Cksum(MBUF_S * pstMBuf, LONG lLen);

#define UDP_SOCKID_ANY (FILENUM + 1)
#define UDP_TASKID_ANY 0xFFFFFFFF

#define UDP_PACKET_DEBUG_OFF    0   
#define UDP_PACKET_DEBUG_ON     1

/*shell call back functions*/
#define     UDP_SHELL_DEBUGPACKET       (g_stUDPCallback.pfIP4_UDP4_DbugPkt)
#define     UDP_SHELL_SENDINFO2IC       (g_stUDPCallback.pfIP4_UDP4_SH_SendInfo2IC)

/*get/set sock member variables*/
#define     UDP_SOCKET_GET_PARAM        (g_pstUDPSOCK4Vtbl->pfSOCK_GetParameter)
#define     UDP_SOCKET_SET_PARAM        (g_pstUDPSOCK4Vtbl->pfSOCK_SetParameter)

/*macro: get/set inpcb variables */
#define     UDP_INPCB_GET_PARAM         (g_pstUDPSOCK4Vtbl->pfINPCB_GetParameter)
#define     UDP_INPCB_SET_PARAM         (g_pstUDPSOCK4Vtbl->pfINPCB_SetParameter)

/*macro: socket syscall for tcp*/
#define UDP_SOCKET_ISDISCONNECTED       (g_pstUDPSOCK4Vtbl->pfSO_IsDisconnected) 
#define UDP_SOCKET_ISCONNECTED          (g_pstUDPSOCK4Vtbl->pfSO_IsConnected)
#define UDP_SOCKET_SORWAKEUP(so)        (g_pstUDPSOCK4Vtbl->pfSoWakeUp((so), 2))
#define UDP_SOCKET_SOWWAKEUP(so)        (g_pstUDPSOCK4Vtbl->pfSoWakeUp((so), 1))
#define UDP_SOCKET_ASYNWAKEUP           (g_pstUDPSOCK4Vtbl->pfSO_AsynWakeUp)
#define UDP_SOCKET_ASYNRECALL           (g_pstUDPSOCK4Vtbl->pfSO_AsynReCall)
#define UDP_INPCB_NOTIFY                (g_pstUDPSOCK4Vtbl->pfINPCB_Notify)
#define UDP_INPCB_BIND                  (g_pstUDPSOCK4Vtbl->pfINPCB_Bind)
#define UDP_INPCB_INIT_CONNECTIONS_HEAD (g_pstUDPSOCK4Vtbl->pfINPCB_Init)

#define UDP_INPCB_INIT_HASH_HEAD        (g_pstUDPSOCK4Vtbl->pfINPCB_HashInit)
#define UDP_INPCB_ALLOC                 (g_pstUDPSOCK4Vtbl->pfINPCB_Alloc)
#define UDP_INPCB_DETACH                (g_pstUDPSOCK4Vtbl->pfINPCB_Detach)
#define UDP_INPCB_DISCONNECT            (g_pstUDPSOCK4Vtbl->pfINPCB_Disconnect) 
#define UDP_INPCB_CONNECT               (g_pstUDPSOCK4Vtbl->pfINPCB_Connect)
#define UDP_INPCB_HASHSEARCH            (g_pstUDPSOCK4Vtbl->pfINPCB_HashSearch)
#define UDP_INPCB_SETPEERADDR           (g_pstUDPSOCK4Vtbl->pfINCB_SetPeerAddr)
#define UDP_INPCB_SETSOCKADDR           (g_pstUDPSOCK4Vtbl->pfINPCB_SetSockAddr)
#define UDP_SOCKET_CANTSENDMORE         (g_pstUDPSOCK4Vtbl->pfSO_CantSendMore)
#define UDP_SOCKET_RESERVE              (g_pstUDPSOCK4Vtbl->pfSO_Reserve)
#define UDP_IP_OUTPUT                   (g_pstUDPPP4Vtbl->pfIP_Output_ForInternal)

#define UDP_FIB_RTALLOC                 (g_pstUDPFIB4Vtbl->pfIP4_FIB_AllocValid)

#define UDP_PP_SRCROUTE                 (g_pstUDPPP4Vtbl->pfIP_SrcRoute)
#define UDP_PP_STRIPOPTIONS             (g_pstUDPPP4Vtbl->pfIP_StrIpOptions)

#define UDP_AM_ISBROADCAST              (g_pstUDPAddr4Vtbl->pfIP_IF_IsBroadcast)
#define UDP_PP_INCKSUM                  (IN_Cksum)
#define UDP_SOCKET_APPENDADDR           (g_pstUDPSOCK4Vtbl->pfSB_AppendAddr)

#define UDP_ICMP_ERROR                  (g_pstUDPICMP4Vtbl->pfICMP_Error)

#define UDP_STAT_INC_VALUE    1

/* 通过INPCB获取UDP统计信息 */
#define    INPCB_TO_PERUDPSO_STAT(pInPCB, udpStatM, ulValue) \
{ \
    if (pInPCB) \
    {   \
        if (((struct tagINPCB *)(pInPCB))->inp_pSocket) \
        { \
            ((pInPCB)->inp_pSocket)->unSocketStat.stPerUDP4Stat.udpStatM += ulValue; \
        } \
    } \
}

#ifdef __cplusplus
}
#endif

#endif /* _UDP_VAR_H_ */

