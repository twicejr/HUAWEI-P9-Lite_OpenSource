/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock6_callback.h
*
*  Project Code: VISPV100R007
*   Module Name: socket
*  Date Created: 2008-04-11
*        Author: zhoutong(43740)
*   Description: 上述定义从sock_pub.h中复制了一份，仅用于sock6_api.c引用
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-11   zhoutong(43740)         Create
*
*******************************************************************************/

#ifndef _SOCK6_CALLBACK_H_
#define _SOCK6_CALLBACK_H_

#ifdef __cplusplus
extern "C"{
#endif

struct tagSOCKET;

typedef struct tagPMTU_CALLBACKUP_SET_S
{
    LONG  (*pfIP6_Socket_PMTU_Notify)(IN6ADDR_S *, ULONG,ULONG, LONG, ULONG, UCHAR);
    ULONG (*pfIP6_Socket_Search)(UCHAR, IN6ADDR_S *, USHORT, IN6ADDR_S *, USHORT, LONG *, ULONG *, ULONG);
    LONG  (*pfIP6_Socket_Notification_deletion)(LONG,ULONG, IN6ADDR_S *, ULONG);
    void  (*pfIP6_Socket_Notification_delete_all)();
}PMTU_CALLBACKUP_SET_S;

typedef struct tagSOSB6_CALLBACUP_SET_S
{
    /*Generic Get socket field Interface function */
    ULONG     (*pfIP6_Socket_SetParameter)(UINTPTR, ULONG, VOID *);
    /*Generic Set socket field Interface function */
    ULONG     (*pfIP6_Socket_GetParameter)(UINTPTR, ULONG, VOID *);

    VOID      (*pfSO6_CantSendMore)(UINTPTR);
    VOID      (*pfSO6_CantRcvMore)(UINTPTR);
    VOID      (*pfSO6_IsConnecting)(UINTPTR);
    VOID      (*pfSO6_IsConnected)(UINTPTR);
    VOID      (*pfSO6_IsDisconnecting)(UINTPTR);
    VOID      (*pfSO6_IsDisconnected)(UINTPTR);
    UINTPTR   (*pfSO6_NewConn)(UINTPTR, LONG);
    VOID      (*pfSO6_HasOutOfBand)(UINTPTR);
    LONG      (*pfSO6_Reserve)(UINTPTR, ULONG, ULONG);
    VOID      (*pfSB6_Append)(UINTPTR, struct tagMBuf *);
    LONG      (*pfSB6_AppendAddr)(UINTPTR ,struct tagSOCKADDR *,struct tagMBuf *, struct tagMBuf *);
    VOID      (*pfSB6_Flush)(UINTPTR);
    VOID      (*pfSB6_Drop)(UINTPTR, LONG);
    VOID      (*pfSo6WakeUp)(UINTPTR, LONG);
    ULONG     (*pfSO6_AsynReCall)( UINTPTR, struct tagMBuf *, struct tagIP6_S *, USHORT );
    LONG      (*pfSO6_AsynWakeUp)(UINTPTR, LONG, LONG );
    LONG      (*pfSysCtl_int)(VOID *, ULONG *, VOID *, ULONG , LONG *);
    LONG      (*pfWakeUp)(ULONG ulTaskId, ULONG ulEvent);
    LONG      (*pfSO6_Abort) (UINTPTR pSocket);
    /* add 06-12-06, IR加了两个回调函数 */
    CHAR      (*pfSock_IP6_GetErrMap)(ULONG ulCmdIndex);
    CHAR*     (*pfinet_ntop6)(const CHAR*, CHAR*, ULONG);
    ULONG     (*pfHeadCache6_LookUpSrcAddr)(struct tagSOCKET*, IN6ADDR_S*, USHORT, IN6ADDR_S*, USHORT *);
    LONG      (*pfSOCK6_SocketID_Check)(ULONG ulProType, ULONG ulTaskID, ULONG ulSocketID,
                                    VOID **ppstSocket, VOID **ppstIn6PCB);
    UINT32    (*pfSO6_CheckCookieStart)(UINTPTR);
}SOSB6_CALLBACUP_SET_S;

typedef struct tagIN6PCB_CALLBACUP_SET_S
{
    ULONG    (*pfIP6_IN6PCB_SetParameter)(UINTPTR, ULONG, VOID*);

    ULONG    (*pfIP6_IN6PCB_GetParameter)(UINTPTR, ULONG, VOID *);

    ULONG    (*pfIP6_IN6PCB_GetHashFHT) (USHORT, UINTPTR *);

    ULONG    (*pfIP6_IN6PCB_GetIN6PCBFromSecondHash)(UINTPTR ,USHORT , UINTPTR *);

    VOID     *(*pfIN6PCB_GetNextPCB)(VOID *,VOID **);

    LONG     (*pfIN6PCB_Init) (UCHAR, UINTPTR *, UINTPTR *);

    LONG     (*pfIN6PCB_Alloc)(UINTPTR, UINTPTR , UINTPTR);

    LONG     (*pfIN6PCB_Bind)(UINTPTR , struct tagSOCKADDR_IN6 *);

    LONG     (*pfIN6PCB_Connect)(UINTPTR, struct tagSOCKADDR_IN6 *);

    LONG     (*pfIN6PCB_Detach)(UINTPTR);

    LONG     (*pfIN6PCB_Disconnect)(UINTPTR);

    LONG     (*pfIN6PCB_Notify)(UINTPTR, struct tagSOCKADDR*, ULONG, struct tagIN6Addr* ,
                ULONG,LONG, VOID (*)(UINTPTR, LONG));

    LONG     (*pfIN6PCB_SetPeerAddr)( UINTPTR, struct tagMBuf*);

    LONG     (*pfIN6PCB_SetSockAddr)(UINTPTR,struct tagMBuf *);

    UINTPTR    (*pfIN6PCB_HashSearch)(UINTPTR,struct tagIN6Addr*,USHORT,struct tagIN6Addr*, USHORT,LONG, ULONG, ULONG);

    LONG     (*pfIN6PCB_SearchSecond)(UINTPTR,struct tagIN6Addr*, USHORT, struct tagIN6Addr*, ULONG, ULONG);

    /* add 06-12-06, IR加了一个回调函数 */
    ULONG    (*pfIN6PCB_BindFAddress)(UINTPTR, IN6ADDR_S *);
}IN6PCB_CALLBACUP_SET_S;

typedef CHAR* (*SOCK6_INETNTOP_CALLBACK)(const CHAR *pSrcAddr,CHAR *pszDstAddr, ULONG ulAddrLen);
extern SOCK6_INETNTOP_CALLBACK g_pstSock6CallBackFunc;

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif


