/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              isock.h
*
*  Project Code: VISP1.5
*   Module Name: socket4
*  Date Created: 2006-4-29
*        Author: l(48769)
*   Description: socket component header file
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*
*******************************************************************************/
#ifndef _ISOCK_H_
#define _ISOCK_H_

#ifdef __cplusplus
extern "C"{
#endif


struct tagMBuf;
struct tagSOCKADDR;
struct tagSOCKADDRIN;
struct tagSOCKET;
struct tagINPCB;
struct tagSOCKHOST;
struct tagMREGINFO;
struct tagSOCK_MOD_INFO_S;
struct tagIP_SOCK_SH_CALLBACUP_SET_S;
struct tagSOCKDBUGFILTRD;
struct tag_HeadCache;
struct tagRAWSTAT;

DECLARE_INTERFACE( IIF_IP4_SOCK_ComIntCfg)
{
    IUNKNOWN_METHODS

    METHOD_ (ULONG ,pfSOCK4_Init_Com) (const COM_ID_INFO_S *pComInfo, ULONG ulComLen);
    METHOD_ (ULONG ,pfSOCK4_Activate_Com)();
    METHOD_ (ULONG ,pfSOCK4_Set_Module_Info)(struct tagSOCK_MOD_INFO_S * pstMInfo);
    METHOD_ (ULONG ,pfSOCK4_RegisterAll)(struct tagIP_SOCK_SH_CALLBACUP_SET_S * pfTCP4CallBack);

    METHOD_ (USHORT ,pfAddHost)(CHAR * stHostName, CHAR * stHostIP);
    METHOD_ (USHORT ,pfDelHost)(LONG lKind,CHAR *stHostName, CHAR *stHostIP);
    METHOD_ (LONG ,  pfGetHost)(ULONG ulIndex , struct tagSOCKHOST **ppHost);

    METHOD_ (LONG ,pfGetSock)(ULONG ulTaskId,LONG iFd,struct tagSOCKET **ppSocket);

    METHOD_ (ULONG ,pfSOCK_OpenObject)(ULONG ulMainType, UINTPTR * pulHandle);
    METHOD_ (ULONG ,pfSOCK_CloseObject)(UINTPTR  ulHandle);
    METHOD_ (LONG , pfSOCK_Get_Object_First)(UINTPTR ulHandle, ULONG ulSocketType,struct tagINPCB **ppReturnInPCB);
    METHOD_ (LONG , pfSOCK_Get_Object_Next)(UINTPTR ulHandle, ULONG ulSocketType,struct tagINPCB *pCurrentInPCB, struct tagINPCB **ppReturnInPCB);

    METHOD_ (ULONG ,pfSOCK_DebugAll)( VOID );
    METHOD_ (ULONG ,pfSOCK_NoDebugAll)( VOID );
    METHOD_ (ULONG ,pfSOCK_ShowDebugging)( CHAR *szStatusStr,INT32 iMaxLen ,ULONG ulDebugIndx,ULONG *pulWaitlistHandle,ULONG ulInterface);
    METHOD_(ULONG,pfSOCK_ProDbugFilter)(ULONG ulFlag, struct tagSOCKDBUGFILTRD *pstDbugFiltRd, ULONG ulTaskId, ULONG ulSockId);
    METHOD_(ULONG, pfSOCK_SetSockLogSwitch)(ULONG ulProtocol, ULONG ulLogSwitch);
    METHOD_(ULONG, pfSOCK_GetSockLogSwitch)(ULONG ulProtocol, ULONG *pulLogSwitch);

    /* Added for SOCKET HA */
    METHOD_(ULONG, pfTCPIP_HA_SetSockDbg)(ULONG ulDbg, LONG lSocketID);
    METHOD_(ULONG, pfTCPIP_HA_GetSockDbg)(ULONG *pulSockHaDbg);

    /* Added for ISIS*/
    METHOD_(ULONG, pfSOCK_GetISISStaData)(struct tagRAWSTAT *pstRawStat);
    METHOD_(VOID, pfSOCK_ClearISISStaData)(VOID);
    METHOD_(ULONG, pfSOCK_SetSockGlobleConfig)(USHORT usStart, USHORT usEnd);
};

DECLARE_INTERFACE( IIF_IP4_SOCK_ComIntFun)
{
    IUNKNOWN_METHODS

    METHOD_ (ULONG ,pfSOCK_GetParameter)(VOID *pSocket, ULONG ulType, VOID *pValue);
    METHOD_ (ULONG ,pfSOCK_SetParameter)(VOID *pInPcb, ULONG ulType, VOID *pValue);

    METHOD_ (ULONG ,pfINPCB_GetParameter)(VOID *pInPcb, ULONG ulType, VOID *pValue);
    METHOD_ (ULONG ,pfINPCB_SetParameter)(VOID *pInPcb, ULONG ulType, VOID *pValue);

    METHOD_ (VOID ,pfSO_IsDisconnected)(SOCKET_S *pSocket);
    METHOD_ (VOID ,pfSO_IsConnected)(SOCKET_S *pSocket);

    METHOD_ (VOID ,pfSoWakeUp)(SOCKET_S *pSocket, LONG iKind);

    METHOD_ (LONG ,pfSO_AsynWakeUp)(SOCKET_S *pSocket,LONG,LONG);
    METHOD_ (ULONG ,pfSO_AsynReCall)( SOCKET_S *pSock, struct tagMBuf *pstMBuf, struct tagIP *pIp, USHORT usSurPort );
    METHOD_ (VOID ,pfSO_CantSendMore)(SOCKET_S *pSocket);
    METHOD_ (LONG ,pfSO_Reserve)(SOCKET_S *pSocket,  ULONG ulSndCC, ULONG ulRcvCC);
    METHOD_ (LONG ,pfSB_AppendAddr)(SOCKET_S *pSocket,struct tagSOCKADDR *pstAsa,struct tagMBuf *pstMData,struct tagMBuf *pstMControl);
    METHOD_ (VOID ,pfSO_IsConnecting)(SOCKET_S *pSocket);
    METHOD_ (VOID ,pfSO_IsDisconnecting)(SOCKET_S *pSocket);
    /*f47854 modify : 函数参数或者返回值类型与函数指针定义不匹配*/
    METHOD_ (SOCKET_S* ,pfSO_NewConn)(SOCKET_S *pHead, LONG iConnStatus);
    METHOD_ (VOID ,pfSB_Drop)(SOCKBUF_S *pSb, LONG nLen);
    METHOD_ (LONG ,pfSO_Abort)(SOCKET_S *pSocket);
    METHOD_ (VOID ,pfSB_Append)(SOCKET_S *pSocket, LONG iKind, struct tagMBuf *pstMTail);
    METHOD_ (VOID ,pfSB_Flush)(SOCKET_S *pSocket, LONG iKind);
    METHOD_ (LONG ,pfWakeUp)(ULONG ulTaskId,ULONG ulEvent);
    METHOD_ (VOID *,pfINPCB_HashInit)(ULONG ulConnectionsType);
    METHOD_ (VOID ,pfSO_CantRcvMore)(SOCKET_S *pSocket);
    METHOD_ (VOID ,pfSO_HasOutOfBand)(SOCKET_S *pSocket);


    METHOD_ (LONG ,pfINPCB_Notify)(INPCB_S *pHead, struct tagSOCKADDR *pDst, ULONG uFPortArg,
                struct tagINADDR stLAddr, ULONG uLPortArg, LONG nCmd,
                VOID (*pfNotify)(INPCB_S *,LONG ));
    METHOD_ (LONG ,pfINPCB_Bind)(INPCB_S *pInPcb, struct tagSOCKADDRIN *pSockIn);
    METHOD_ (VOID* ,pfINPCB_Init)(ULONG ulConnectionsType);
    METHOD_ (LONG ,pfINPCB_Alloc)(SOCKET_S *pSock, INPCB_S *pProHead, PCBHASH_S *pHashHead);
    METHOD_ (LONG ,pfINPCB_Detach)(INPCB_S *pInPcb);
    METHOD_ (LONG ,pfINPCB_Connect)(INPCB_S *pInPcb, struct tagSOCKADDRIN *pSockIn);
    /*f47854 modify : 函数参数或者返回值类型与函数指针定义不匹配*/
    METHOD_ (struct tagINPCB* ,pfINPCB_HashSearch)(PCBHASH_S* pstPcbHash,struct tagINADDR stFAddr,USHORT usFPort,
                               struct tagINADDR stLAddr,USHORT usLPort,LONG nFlags,ULONG ulVrfIndex
                             );
    METHOD_ (LONG ,pfINCB_SetPeerAddr)(INPCB_S* pInPcb, struct tagMBuf *pstMBuf); /*modified by x36317 for avoiding warning*/
    METHOD_ (LONG ,pfINPCB_SetSockAddr)(INPCB_S* pInPcb, struct tagMBuf *pstMBuf);
    METHOD_ (LONG ,pfINPCB_Disconnect)(INPCB_S *pInPcb);
    /*f47854 modify : 函数参数或者返回值类型与函数指针定义不匹配*/
    METHOD_ (struct tagINPCB * ,pfINPCB_HashLookPort)(PCBHASH_S* pstPcbHash,struct tagINADDR stFAddr,USHORT usFPort,
                                 struct tagINADDR stLAddr, USHORT usLPort,LONG nFlags,ULONG ulVrfIndex
                               );
    METHOD_ (VOID ,pfreorderpcbltob)(INPCB_S *);

    /*add by y36299 for Head Cache*/
    METHOD_(VOID, pfHC_Event)(ULONG ulEvent, VOID* pData); /* modfiy by l57500,06/12/06. 2nd formal param:long -> VOID* */
    METHOD_(VOID, pfHC_Update)(const MBUF_S *pstMbuf);
    /*获取指定socket下的单个head cache节点的信息*/
    METHOD_(ULONG, pfHC_GetSingleInfo)(ULONG ulTaskId, LONG iFd,\
                   ULONG ulDstIp, USHORT usDstPort, struct tag_HeadCache *pstEntry);
    /*下面3个方法用于访问head cache链*/
    METHOD_(ULONG, pfHC_OpenEntry)(ULONG ulTaskId, LONG iFd, UINTPTR *pulWaitListHandle);
    METHOD_(ULONG, pfHC_GetEntry)(UINTPTR ulEntryWaitList, struct tag_HeadCache *pstEntry);
    METHOD_(VOID, pfHC_CloseObject)( UINTPTR ulWaitListHandle );
    /*设置head cache的功能开关*/
    METHOD_(ULONG, pfHC_SetSwitch)(ULONG ulSetYes);
    METHOD_(ULONG, pfHC_VlanCheck_Hook_Register)(HEADCACHE_VLANCHECK_HOOK_FUNC pfHCHookFunc);
    METHOD_(ULONG, pfSOCK_SetEnableStatus)(ULONG iFamily, ULONG ulIsenable);
    METHOD_(ULONG, pfSOCK_GetEnableStatus)(ULONG iFamily, ULONG* pulIsenable);

    /* Added for SOCKET HA */
    METHOD_(LONG, pfSOCK_HA_NeedBackup)(SOCKET_S *pSocket);
    METHOD_(LONG, pfSOCK_HA_BackupNotify)(LONG lFd, UCHAR ucOperation, CHAR *pszInfo);
    METHOD_(LONG, pfSOCK_HA_BatchBackup)();
    METHOD_(LONG, pfSOCK_HA_SwitchNotify)();
    METHOD_(LONG, pfSOCK_HA_RealTimeBackup)(LONG lFd, UCHAR ucOperation, CHAR *pszInfo, CHAR *pszBuf, ULONG *pulBufLen);
    METHOD_(LONG, pfSOCK_HA_BackupQueueDeal)(LONG lIsSwitching);
    METHOD_(LONG, pfSOCK_HA_BackupInput)(CHAR *pszBackupBuf, ULONG ulBackupBufLen);
    METHOD_(LONG, pfSOCK_HA_Smooth)();
    METHOD_(ULONG, pfTCPIP_HA_VerifySocket)(LONG lSocketID);
    METHOD_(ULONG, pfSOCK_HA_Clean)();
    METHOD_ (UINT32 ,pfSO_CheckCookieStart)(SOCKET_S *pHead);
};


typedef struct tagIPV4_SOCK_INT_OBJ_S
{
    struct IIF_IP4_SOCK_ComIntCfg * g_IComInt_SOCK4_CFG;
    struct IIF_IP4_SOCK_ComIntFun * g_IComInt_SOCK4_FUN;
} IPV4_SOCK_INT_OBJ_S;

#define IP4_SOCK_EXT_COMIF_CNT 12 /* Aravind */

#ifdef __cplusplus
}
#endif

#endif
