/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              raw_ip_var.h
*
*  Project Code: VISP1.5
*   Module Name: RawIP
*  Date Created: 2006-4-28
*        Author: luyao(60000758)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-4-28   luyao(60000758)  Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/

#ifndef _RAW_IP_VAR_H_
#define _RAW_IP_VAR_H_

#ifdef __cplusplus
extern "C"{
#endif

extern VOID *g_pstRawInPcb;   /*The header of RawIP INPCB link*/
extern SOCKADDRIN_S stRipSrc; /*RawIP source socket address*/

extern RIP4_MOD_INFO_S g_stRIP4ModInfo; /*RawIP module information*/

extern ULONG   ulRipSndSpace ; /* RawIP4 Socket发送缓冲区大小 */
extern ULONG   ulRipRcvSpace ; /* RawIP4 Socket接收缓冲区大小 */

extern RIPSTAT_S stRipStat;    /* RawIP statistics */

/*以下是RawIP4组件用到的其他组件的接口*/
extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl    *g_pstRIPAddr4Vtbl ;    /*AM4组件功能接口*/
extern struct IIF_IPV4_IP_PP4_ComIntFUNVtbl    *g_pstRIPPP4Vtbl ;      /*PP4组件功能接口*/
extern struct IIF_IPV4_IP_ICMP_ComIntFUNVtbl   *g_pstRIPICMP4Vtbl ;    /*ICMP4组件功能接口*/
extern struct IIF_IP4_SOCK_ComIntFunVtbl       *g_pstRIPSOCK4Vtbl ;    /*Socket4组件功能接口*/
extern struct IIF_IP4_SOCK_ComIntCfgVtbl       *g_pstRIPSock4CfgVtbl ; /*Socket4组件配置接口*/
extern struct IIF_DIST_IP_ComIntFUNVtbl        *g_pstRIPDISTIPVtbl;

extern struct IIF_COMP_ATK_ComIntFUNVtbl        *g_pstRip4AtkFunVtbl;

/*get/set sock member variables*/
#define     RIP_SOCKET_GET_PARAM               (g_pstRIPSOCK4Vtbl->pfSOCK_GetParameter)
#define     RIP_SOCKET_SET_PARAM               (g_pstRIPSOCK4Vtbl->pfSOCK_SetParameter)

/*macro: get/set inpcb variables */
#define     RIP_INPCB_GET_PARAM                (g_pstRIPSOCK4Vtbl->pfINPCB_GetParameter)
#define     RIP_INPCB_SET_PARAM                (g_pstRIPSOCK4Vtbl->pfINPCB_SetParameter)

#define RIP_INPCB_INIT_CONNECTIONS_HEAD        (g_pstRIPSOCK4Vtbl->pfINPCB_Init)
#define RIP_INPCB_ALLOC                        (g_pstRIPSOCK4Vtbl->pfINPCB_Alloc)
#define RIP_INPCB_DETACH                       (g_pstRIPSOCK4Vtbl->pfINPCB_Detach)
#define RIP_INPCB_SETPEERADDR                  (g_pstRIPSOCK4Vtbl->pfINCB_SetPeerAddr)
#define RIP_INPCB_SETSOCKADDR                  (g_pstRIPSOCK4Vtbl->pfINPCB_SetSockAddr)

#define RIP_SOCKET_ASYNRECALL                  (g_pstRIPSOCK4Vtbl->pfSO_AsynReCall)
#define RIP_SOCKET_APPENDADDR                  (g_pstRIPSOCK4Vtbl->pfSB_AppendAddr)
#define RIP_SOCKET_ASYNWAKEUP                  (g_pstRIPSOCK4Vtbl->pfSO_AsynWakeUp)
#define RIP_SOCKET_SORWAKEUP(so)               (g_pstRIPSOCK4Vtbl->pfSoWakeUp)((so), 2)
#define RIP_SOCKET_RESERVE                     (g_pstRIPSOCK4Vtbl->pfSO_Reserve)
#define RIP_SOCKET_ISDISCONNECTED              (g_pstRIPSOCK4Vtbl->pfSO_IsDisconnected)
#define RIP_SOCKET_ISCONNECTED                 (g_pstRIPSOCK4Vtbl->pfSO_IsConnected)
#define RIP_SOCKET_CANTSENDMORE                (g_pstRIPSOCK4Vtbl->pfSO_CantSendMore)

#define RIP_ICMP_ERROR                         (g_pstRIPICMP4Vtbl->pfICMP_Error)

#define RAWIP_STAT_INC_VALUE 1

/* 通过INPCB获取RAWIP统计信息 */
#define    INPCB_TO_PERRAWIPSO_STAT(pInPCB, rawIpStatM, ulValue) \
{ \
    if (((struct tagINPCB *)(pInPCB))->inp_pSocket) \
    { \
        (((struct tagINPCB *)(pInPCB))->inp_pSocket)->unSocketStat.stPerRAWIP4Stat.rawIpStatM += ulValue; \
    } \
}    


#ifdef __cplusplus
}
#endif

#endif
