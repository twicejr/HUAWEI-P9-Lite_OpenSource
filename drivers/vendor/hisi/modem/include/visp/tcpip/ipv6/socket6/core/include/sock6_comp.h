/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock6_comp.h
*
*  Project Code: VISP1.5
*   Module Name: socket6
*  Date Created: 2000-4-3
*        Author: chenbin
*   Description: the macro,struct,function used by application
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2000-4-3    chenbin          Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/

#ifndef _SOCK6_COMP_H
#define _SOCK6_COMP_H

#ifdef __cplusplus
extern "C"{
#endif

typedef struct tagIP6_MTU_INFO 
{
    SOCKADDR_IN6_S ip6m_addr; /* dst address including zone ID */
    ULONG ip6m_mtu;           /* path MTU in host byte order */
}IP6_MTU_INFO;

extern struct IIF_IP6_ADDR_ComIntFunVtbl        *g_pstSockAddr6Vtbl;
extern struct IIF_IPV6_FIBAGENT_ComIntFUNVtbl   *g_pstSockFib6Vtbl;
extern struct IIF_IP6_PP_ComIntFunVtbl          *g_pstSockPP6Vtbl;
extern struct IIF_IP6_TCP6_ComIntFunVtbl        *g_pstSock6TCP6Vtbl;
extern struct IIF_IP6_RIP_ComIntFunVtbl         *g_pstSockRIP6Vtbl;
extern struct IIF_IP6_PMTU_ComIntFunVtbl        *g_pstSock6PmtuVtbl;
    
ULONG  Socket_Search (UCHAR , IN6ADDR_S *, USHORT , IN6ADDR_S *, USHORT, LONG *, ULONG *, ULONG);
LONG   Socket_Notification_deletion (LONG, ULONG , IN6ADDR_S *, ULONG );
VOID   Socket_Notification_delete_all ();
LONG   Socket_PMTU_Notify (IN6ADDR_S *, ULONG ,ULONG , LONG , ULONG ,UCHAR);

MBUF_S *    PmtuSaveOpt(CHAR *, register LONG , LONG);
ULONG IP6_Socket_SetParameter(UINTPTR, ULONG, VOID*);
ULONG IP6_Socket_GetParameter(UINTPTR, ULONG, VOID*);
ULONG IP6_IN6PCB_SetParameter(UINTPTR, ULONG, VOID*);
ULONG IP6_IN6PCB_GetParameter(UINTPTR, ULONG, VOID*);
ULONG IP6_IN6PCB_GetHashFHT (USHORT, UINTPTR *);
ULONG IP6_IN6PCB_GetIN6PCBFromSecondHash(UINTPTR ,USHORT, UINTPTR *);
        
extern VOID  IP6_PMTU_Socket_RegisterCallBack(PMTU_CALLBACKUP_SET_S*);
extern VOID  IP6_TCP6_SOSB6_Socket_RegisterCallBack(SOSB6_CALLBACUP_SET_S* );    
extern VOID  IP6_TCP6_IN6PCB_Socket_RegisterCallBack(IN6PCB_CALLBACUP_SET_S *);
extern VOID  IP6_UDP_SOSB6_Socket_RegisterCallBack(SOSB6_CALLBACUP_SET_S*);    
extern VOID  IP6_UDP_IN6PCB_Socket_RegisterCallBack(IN6PCB_CALLBACUP_SET_S *);
extern VOID  IP6_RIP_SOSB6_Socket_RegisterCallBack(SOSB6_CALLBACUP_SET_S*);    
extern VOID  IP6_RIP_IN6PCB_Socket_RegisterCallBack(IN6PCB_CALLBACUP_SET_S *);


#ifdef    __cplusplus
}
#endif

#endif

