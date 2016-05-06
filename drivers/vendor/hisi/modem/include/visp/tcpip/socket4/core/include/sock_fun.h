/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock_fun.h
*
*  Project Code: VISP1.5
*   Module Name: socket4  
*  Date Created: 2006-4-29
*        Author: l(48769)
*   Description: socket functions
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*
*******************************************************************************/
#ifndef        _SOCK_FUN_H
#define        _SOCK_FUN_H

#ifdef    __cplusplus
extern    "C"{
#endif

ULONG IP4_SOCK4_QueryInterface(IUnknown * This, COMP_IID iid, LPVOID *ppvObj);

ULONG IP4_INPCB_GetParameter(VOID *pPcb, ULONG ulType, VOID*pValue);
ULONG IP4_INPCB_SetParameter(VOID* pPcb, ULONG ulType, VOID* pValue);
ULONG IP4_Socket_GetParameter(VOID* pSock, ULONG ulType, VOID  *pValue);
ULONG IP4_Socket_SetParameter(VOID* pSock, ULONG ulType, VOID  *pValue);
VOID  SO_IsDisconnected(SOCKET_S *pSocket);
VOID  SO_IsConnected(SOCKET_S *pSocket);
VOID  SoWakeUp(SOCKET_S *pSocket, LONG iKind);
LONG  AsynWakeUp(SOCKET_S * pSocket,LONG iEventType,LONG iError);
ULONG AsynReCall( SOCKET_S *pSock, MBUF_S *pstMBuf, IP_S *pIp, USHORT usSurPort );
VOID SO_CantSendMore(SOCKET_S *pSocket);
LONG SO_Reserve(SOCKET_S *pSocket,  ULONG ulSndCC, ULONG ulRcvCC);
LONG SB_AppendAddr(SOCKET_S *pSocket,SOCKADDR_S *pstAsa,MBUF_S *pstMData, MBUF_S *pstMControl);
VOID SO_IsConnecting(SOCKET_S *pSocket);
VOID SO_IsDisconnecting(SOCKET_S *pSocket);
SOCKET_S *SO_NewConn(SOCKET_S *pHead, LONG iConnStatus);
VOID SB_Drop(SOCKBUF_S *pSb, LONG nLen);
LONG SO_Abort(SOCKET_S *pSocket);
VOID SBAppend(SOCKBUF_S *pSb, MBUF_S *pstMTail);
VOID SB_Append(SOCKET_S *pSocket, LONG iKind, MBUF_S *pstMTail);
VOID SBFlush(SOCKBUF_S *pSb);
VOID SB_Flush(SOCKET_S *pSocket, LONG iKind);
LONG WakeUp(ULONG ulTaskId,ULONG ulEvent);
VOID *INPCB_HashInit(ULONG ulConnectionsType);
VOID SO_CantRcvMore(SOCKET_S *pSocket);
VOID SO_HasOutOfBand(SOCKET_S *pSocket);
LONG INPCB_Notify(INPCB_S *pHead, SOCKADDR_S *pDst, ULONG uFPortArg,
    INADDR_S stLAddr, ULONG uLPortArg, LONG nCmd,VOID (*pfNotify)(INPCB_S *,LONG ));
LONG INPCB_Bind( INPCB_S *pInPcb, SOCKADDRIN_S *pSockIn);
VOID *INPCB_Init(ULONG ulConnectionsType);
LONG INPCB_Alloc(SOCKET_S *pSock, INPCB_S *pProHead, PCBHASH_S *pHashHead);
LONG INPCB_Detach(INPCB_S *pInPcb);
LONG INPCB_Connect( INPCB_S *pInPcb, SOCKADDRIN_S *pSockIn);
struct tagINPCB *INPCB_HashSearch( PCBHASH_S* pstPcbHash,
                                   INADDR_S stFAddr,
                                   USHORT usFPort,
                                   INADDR_S stLAddr,
                                   USHORT usLPort,
                                   LONG nFlags,
                                   ULONG ulVrfIndex
                                 );
LONG IN_SetPeerAddr(INPCB_S *pInPcb, MBUF_S *pMName);
LONG IN_SetSockAddr( INPCB_S *pInPcb,MBUF_S *pMName);
LONG INPCB_Disconnect(INPCB_S *pInPcb);
struct tagINPCB *INPCB_HashLookPort( PCBHASH_S* pstPcbHash,
                                     INADDR_S stFAddr,
                                     USHORT usFPort,
                                     INADDR_S stLAddr,
                                     USHORT usLPort,
                                     LONG nFlags,
                                     ULONG ulVrfIndex
                                   );
VOID reorderpcbltob(INPCB_S *pInPcb);
ULONG SOCK_Init_Com(const COM_ID_INFO_S * pstComInfo, ULONG  ulComLen);
ULONG SOCK_Activate_Com (VOID);
ULONG SOCK_SetModuleInfo (SOCK_MOD_INFO_S *pstMInfo);
ULONG SOCK_RegShellApi ( IP_SOCK_SH_CALLBACUP_SET_S *pfCallBackSet);
USHORT AddHost(CHAR * stHostName, CHAR * stHostIP);
USHORT AddHost_PT(CHAR * stHostName, CHAR * stHostIP);
USHORT DelHost(LONG lKind,CHAR *stHostName, CHAR *stHostIP);
USHORT DelHost_PT(LONG lKind,CHAR *stHostName, CHAR *stHostIP);
LONG GetHost(ULONG ulIndex , SOCKHOST_S **ppHost);
LONG GetSock(ULONG ulTaskId,LONG iFd,SOCKET_S **ppSocket);
ULONG SOCK_OpenObject(ULONG ulMainType, UINTPTR * pulHandle);
ULONG SOCK_CloseObject(UINTPTR  ulHandle);
LONG SOCK_Get_Object_First(UINTPTR ulHandle, ULONG ulSocketType,
                           INPCB_S **ppReturnInPCB);
LONG SOCK_Get_Object_Next(UINTPTR ulHandle, ULONG ulSocketType,
                INPCB_S *pCurrentInPCB, INPCB_S **ppReturnInPCB);
ULONG SOCK_DebugAll( VOID );
ULONG SOCK_NoDebugAll( VOID );
ULONG SOCK_ShowDebugging( CHAR *szStatusStr,INT32 iMaxLen,ULONG ulDebugIndx,ULONG *pulWaitlistHandle,ULONG ulInterface);
struct tagSOCKDBUGFILTRD;
ULONG  SOCK_ProDbugFilter(ULONG ulFlag, struct tagSOCKDBUGFILTRD *pstDbugFiltRd,  ULONG ulTaskId, ULONG ulSockId );
ULONG  SOCK_ProIp6DbugFilter(ULONG ulFlag, struct tagSOCKDBUGFILTRD *pstDbugFiltRd, ULONG ulTaskId, ULONG ulSockId );
ULONG  SOCK_BuildRun(CHAR szSectionName[], CHAR** pszBuildRunInfo);
VOID SOCK_ShowOneSocket(SOCKET_S *pSocket);

ULONG HeadCache_GetTotalNum(SOCKET_S *pSocket, ULONG *pulNum);
LONG  HeadCache_Create(SOCKET_S *pSocket, ULONG ulMaxNum);
VOID  HeadCache_Destroy(SOCKET_S *pSocket);

VOID HeadCache_Event(ULONG ulEventType, VOID* pData);
VOID HeadCache_Update(const MBUF_S * pMbuf);
ULONG HeadCache_GetSingleInfo(ULONG ulTaskId, LONG iFd,ULONG ulDstIp,\
                                USHORT usDstPort, HEADCACHE_ENTRY_S *pstEntry);
ULONG HeadCache_GetSingleInfo_PT(ULONG ulTaskId, LONG iFd,ULONG ulDstIp,\
                                USHORT usDstPort, HEADCACHE_ENTRY_S *pstEntry);

ULONG HeadCache_OpenEntry (ULONG ulTaskId, LONG iFd, UINTPTR *pulWaitListHandle);
ULONG HeadCache_GetEntry(UINTPTR ulEntryWaitList, HEADCACHE_ENTRY_S *pstEntry);
VOID  HeadCache_CloseObject ( UINTPTR ulWaitListHandle );
ULONG HeadCache_SetFunctionSwitch(ULONG ulSetYes);

extern ULONG HeadCache_VlanCheck_Hook_Register(HEADCACHE_VLANCHECK_HOOK_FUNC pfHCHookFunc);

LONG SOCK_GetMaxFD(struct fd_set *pFdSet,LONG iMinFd, LONG iMaxFd);

extern ULONG SOCK_SocketID_Check(ULONG ulProType, ULONG ulTaskID, ULONG ulSocketID,
                                    SOCKET_S **ppstSocket, INPCB_S **ppstInPCB);
ULONG SOCK_SetSockLogSwitch(ULONG ulProtocol, ULONG ulLogSwitch);
ULONG SOCK_GetSockLogSwitch(ULONG ulProtocol, ULONG *pulLogSwitch);
ULONG SOCK_SetSockGlobleConfig(USHORT usStart, USHORT usEnd);
UINT32 SO_CheckCookieStart(SOCKET_S *pHead);

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif
