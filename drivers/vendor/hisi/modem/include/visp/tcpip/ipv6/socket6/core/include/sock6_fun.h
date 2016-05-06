/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock6_fun.h
*
*  Project Code: VISP1.5
*   Module Name: Socket6
*  Date Created: 2006-4-29
*        Author: luyao(60000758)
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-4-29   luyao(60000758)  Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/

#ifndef        _SOCK6_FUN_H
#define        _SOCK6_FUN_H

#ifdef    __cplusplus
extern    "C"{
#endif

LONG  SO6_AsynWakeUp(UINTPTR ulSocket,LONG lEventType,LONG lError);
ULONG SO6_AsynReCall( UINTPTR ulSocket,  MBUF_S *pstMBuf,  IP6_S *pstIp6,  USHORT usSurPort );
LONG  Sock6_Ha_GetOneSocketInfo( ULONG ulTaskId, LONG lFd, UCHAR **ppData, LONG *lDataLen );
LONG  Sock6_Ha_RestoreOneSocketInfo( UCHAR *pucData );
LONG  Sock6_Ha_ClearOneSocketResource( ULONG ulTaskId, LONG lFd );
CHAR  *SOCK6_SprintSockPair(IN6PCB_S *pIN6PCB, CHAR *pRet);
LONG  inet_pton6(const CHAR *szSrcAddr, VOID *pDstAddr);
CHAR  *inet_ntop6(const CHAR *pSrcAddr,CHAR *pszDstAddr, ULONG ulAddrLen);
LONG  SO6_Abort(UINTPTR ulSocket);
VOID  SO6_CantSendMore(UINTPTR ulSocket);

VOID  So6WakeUp(UINTPTR, LONG);
ULONG IP6_SOCK6_QueryInterface(IUnknown * This, COMP_IID iid, LPVOID *ppvObj);
ULONG SOCK6_Init_Com(const COM_ID_INFO_S * pstComInfo, ULONG  ulComLen);
ULONG SOCK6_Activate_Com (VOID);
ULONG SOCK6_SetModuleInfo (SOCK_MOD_INFO_S *pstMInfo);
ULONG SOCK6_RegShellApi ( IP_SOCK_SH_CALLBACUP_SET_S *pfCallBackSet);
USHORT SOCK_AddIp6Host(CHAR * pst6HostName, CHAR * pst6HostIP);
USHORT SOCK_AddIp6Host_PT(CHAR * pst6HostName, CHAR * pst6HostIP);
USHORT SOCK_DelIp6Host(LONG lKind,CHAR *pst6HostName, CHAR *pst6HostIP);
USHORT SOCK_DelIp6Host_PT(LONG lKind,CHAR *pst6HostName, CHAR *pst6HostIP);
LONG   SOCK_GetIp6Host(ULONG ulIndex , SOCKHOST_S **ppHost);
LONG   GetSock(ULONG ulTaskId,LONG iFd,SOCKET_S **ppSocket);
ULONG  SOCK_OpenIp6Object(ULONG ulMainType, UINTPTR * pulHandle);
ULONG  SOCK_CloseIp6Object(UINTPTR  ulHandle);
LONG   SOCK_Get_Ip6Object_First(UINTPTR ulHandle,ULONG ulSocketType, IN6PCB_S **ppReturnInPCB);
LONG   SOCK_Get_Ip6Object_Next(UINTPTR ulHandle, ULONG ulSocketType,IN6PCB_S *pCurrentInPCB, IN6PCB_S **ppReturnInPCB);
LONG   SOCK_Ip6DebugAll( VOID );
LONG   SOCK_Ip6NoDebugAll( VOID );
LONG   SOCK_ShowIp6Debugging( CHAR *szStatusStr,ULONG ulMaxLen ,ULONG ulDebugIndx,UINTPTR *pulWaitlistHandle,ULONG ulInterface);
ULONG  SOCK_Ip6BuildRun(CHAR szSectionName[], CHAR** ppszBuildRunInfo);

ULONG SOCK6_GetDebugFlag(VOID);
SOCKDBUGFILTRD_S *SOCK6_GetFilter(VOID);

ULONG HeadCache6_GetSingleInfo(ULONG ulTaskId, LONG iFd,IN6ADDR_S* pstDstAddr6, USHORT usDstPort, HEADCACHE_ENTRY_S *pstEntry);
ULONG HeadCache6_GetSingleInfo_PT(ULONG ulTaskId, LONG iFd,IN6ADDR_S* pstDstAddr6, USHORT usDstPort, HEADCACHE_ENTRY_S *pstEntry);

LONG HeadCache6_SendData(SOCKET_S *pSocket,  UIO_S *pUio, UINTPTR *pulEntryAddr);
ULONG HeadCache6_LookUpSrcAddr (SOCKET_S *pSocket, IN6ADDR_S *pstDstAddr, USHORT usDstPort, IN6ADDR_S *pstSrcAddr, USHORT *pusSrcPort);

/* add by l57500,06-12-06,为支持IR所添加的函数 */
CHAR Sock_IP6_GetErrMap(ULONG ulCmdIndex);
LONG SO6_SocketID_Check(ULONG ulProType, ULONG ulTaskID, ULONG ulSocketID,
                                    VOID **ppstSocket, VOID **ppstIn6PCB);
LONG SOCK6_SocketID_Check(ULONG ulProType, ULONG ulTaskID, ULONG ulSocketID,
                                    SOCKET_S **ppstSocket, IN6PCB_S **ppstIn6PCB);
ULONG SOCK_ShowIp6AllSockets(ULONG ulSocketType, ULONG ulExecID_SOCK);
VOID SOCK_ShowIp6Socket(ULONG ulSockType, ULONG ulTaskId, ULONG ulSockId, ULONG ulExecID_SOCK);
#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

