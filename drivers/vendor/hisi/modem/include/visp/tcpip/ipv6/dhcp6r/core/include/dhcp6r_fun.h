/*******************************************************************************
*
*
*                Copyright 2011, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp6r_fun.h
*
*  Project Code: VISP V2R3C06
*   Module Name: DHCP6R  
*  Date Created: 2011-7-19
*        Author: PBQ(RT24429)
*   Description: DHCP6R模块的函数声明
*
*-------------------------------------------------------------------------------
*  Modification  History
*  DATE          NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2011-7-19     PBQ(RT24429)     Create the first version.
*
*******************************************************************************/

#ifndef _DHCP6R_FUN_H_
#define _DHCP6R_FUN_H_

#ifdef __cplusplus
    extern "C"{
#endif  /* end of __cplusplus */

/*dhcp6r_fun.c*/
VOID  DHCP6R_TaskMain(VOID);
ULONG DHCP6R_Notify_CreateSocket(VOID);
ULONG DHCP6R_CreateSocket(LONG *lRelaySocket);
VOID  DHCP6R_UpdateRecvStatistic(UCHAR ucMsgType);
ULONG DHCP6R_Recv(LONG lsock);
ULONG DHCP6R_Relay(DHCP6R_HEADER_S *pstDhcp6rHdr, ULONG ulLen, ULONG ulIfIndex, IN6ADDR_S *stFromAddr);
ULONG DHCP6R_RelayToServer(VOID *pDhcpPack, USHORT usLen, IN6ADDR_S *stFromAddr, ULONG ulIfindex);
ULONG DHCP6R_RelayToClient(VOID *pDhcpPack, ULONG ulLen, IN6ADDR_S *stFromAddr, ULONG ulIfindex); 
ULONG DHCP6R_SendtoServer(VOID *pDhcpPack, ULONG ulLen, ULONG ulIfindex, UCHAR ucOldMsgType);
ULONG DHCP6R_SendtoClient(VOID *pDhcpPack, ULONG ulLen, IN6ADDR_S *stDstAddr, ULONG ulOutIfindex);
ULONG DHCP6R_PacketSend(VOID *pDhcpPack, ULONG ulLen, IN6ADDR_S *stDstAddr, ULONG ulOutIfindex, USHORT usDstPort);
VOID  DHCP6R_UpdateSendStatistic(VOID *pDhcpPack, IN6ADDR_S *pstDstAddr, USHORT usSendErrFlag);
ULONG DHCP6R_SetInterfaceID(ULONG ulInIfindex, DHCP6R_INTERFACEID_S  *pstInterfaceID);
ULONG DHCP6R_GetCfgNode(ULONG ulIfindex, DHCP6R_CFG_NODE_S  **pstDHCP6R_CfgNode);
ULONG DHCP6R_GetGlobalAddrByIf(ULONG ulIfindex, IN6ADDR_S **stLinkAddr);
ULONG DHCP6R_CodeNametoFullName(UCHAR* pucIfFullName, const DHCP6R_INTERFACEID_S *pstInterfaceID);
ULONG DHCP6R_FullNametoCodeName(UCHAR* pucIfFullName, DHCP6R_INTERFACEID_S *pstInterfaceID);
LONG  DHCP6R_GetCodeByName(const UCHAR* pucIfFullName);
ULONG DHCP6R_GetDuid(const VOID *pDhcpPack, const ULONG ulLen, ULONG *pulDuid);
ULONG DHCP6R_GetOpt(UCHAR **ppDhcpPack, const ULONG ulLen, ULONG *ulTempLen, const USHORT usOptType);
ULONG DHCP6R_GetNameByCode(UCHAR* pucIfFullName, const UCHAR* pucName, const ULONG ulCode );
ULONG DHCP6R_CopyRelayForw(VOID *pDhcpRelayForw, ULONG ulLen, DHCP6R_OPTBUF_S  *stRelayMessage, 
                                    DHCP6R_INTERFACEID_S  *stInterfaceID, DHCP6R_HEADER_S  *stRelayForwHead, 
                                    ULONG ulInterfaceFlag );

/* iDHCP6R_fac.c */
ULONG ImplDHCP6RFactoryQueryInterface(IUnknown *This,COMP_IID iid, LPVOID *ppvObj);
ULONG ImplDHCP6RFactoryCreateInstance(IComponentFactory *This,  COMP_IID iid, VOID **ppvObj);

/* iDHCP6R.c*/
ULONG DHCP6R_QueryInterface(IUnknown *This, COMP_IID iid, LPVOID *ppvObj);

/* DHCP6R_init.c */
ULONG DHCP6R_Init_Com(VOID);
ULONG DHCP6R_Active_Com(VOID);
VOID  DHCP6R_SetTaskId(ULONG ulTask);
ULONG DHCP6R_RegShellApi(DHCP6R_SHELL_CALLBACK_SET_S *pstShellApi);

/* DHCP6R_sh_init.c */
VOID  DHCP6R_SH_TaskEntry(UINTPTR ulArg0, UINTPTR ulArg1, UINTPTR ulArg2, UINTPTR ulArg3);
ULONG DHCP6R_SH_Init(VOID);
VOID  DHCP6R_SH_DelInit(VOID);
ULONG DHCP6R_RegApp(VOID);

/*dhcp6r_debug.c*/
ULONG DHCP6R_DebugSwitchCheck(ULONG ulIfIndex, ULONG ulDebugType);
ULONG DHCP6R_DebugPacketDetail(CHAR *pszDhcpPacket, USHORT usPacketLen, ULONG ulPktType);
ULONG DHCP6R_DebugErrorCheck(CHAR *pszCurrentFileName, ULONG ulFileLine, CHAR *pszErrInfo);
ULONG DHCP6R_DebugError(CHAR* szErrInfo);
ULONG DHCP6R_DebugPacket(CHAR *szDhcprPacket, USHORT usPacketLen, ULONG ulPktType,
                         ULONG ulTxRx, ULONG ulOutIfIndex, IN6ADDR_S *pstDstIPAddr);
ULONG DHCP6R_Debug_Info(CHAR* szString);

/*dhcp6r_cfg.c*/
LONG  DHCP6R_fnCfgIndexCmp(VOID * val, DLL_NODE_S * pNode);
LONG  DHCP6R_fnDbgIndexCmp(VOID * val, DLL_NODE_S * pNode);
DHCP6R_CFG_NODE_S * DHCP6R_GetCfgNodeByIfIndex(ULONG ulInIfIndex);
DHCP6R_DEBUG_NODE_S * DHCP6R_GetDbgNodeByIfIndex(ULONG ulIfIndex);
ULONG DHCP6R_CheckIfValid(ULONG ulIfIndex, ULONG ulCheckType);
ULONG DHCP6R_SetMultiGroup(ULONG ulIfIndex, ULONG ulFlag);
ULONG DHCP6R_AllJoinMultiGroup(VOID);
ULONG DHCP6R_AllLeaveMultiGroup(VOID);
ULONG DHCP6R_Enable(ULONG ulIfIndex);
ULONG DHCP6R_Disable(ULONG ulIfIndex);
ULONG DHCP6R_AddServerList(ULONG ulInIfIndex, DHCP6R_SERVERNODE_S *pstServerNode);
ULONG DHCP6R_DelServerList(ULONG ulInIfIndex, DHCP6R_SERVERNODE_S *pstServerNode);
ULONG DHCP6R_DelAllServerList(ULONG ulInIfIndex);
ULONG DHCP6R_GetServerList(ULONG ulIfIndex, DHCP6R_SERVERNODE_S *pstServerNodeast);
ULONG DHCP6R_ShowServerList(ULONG ulIfIndex);
ULONG DHCP6R_ShowCfgInfo(ULONG ulIfIndex);
ULONG DHCP6R_SetFwdMode(ULONG ulMode);
ULONG DHCP6R_GetFwdMode(ULONG *pulMode);
VOID  DHCP6R_ShowFwdMode(VOID);
ULONG DHCP6R_SetDebugSwitch(ULONG ulIfIndex, ULONG ulDebugSwitch);
ULONG DHCP6R_GetDebugSwitch(ULONG ulIfIndex, ULONG *pulDebugSwitch);
ULONG DHCP6R_SetDbgPktLen(USHORT usPacketLen);
ULONG DHCP6R_ShowDebugSwitch(ULONG ulIfIndex);
ULONG DHCP6R_SetMaxHops(ULONG ulHops);
ULONG DHCP6R_GetMaxHops(ULONG *pulHops);
VOID  DHCP6R_ShowMaxHops(VOID);
ULONG DHCP6R_GetStatInfo(DHCP6R_STATINFO_S *pstDhcp6rStat);
VOID  DHCP6R_ClrStatInfo(VOID);
VOID  DHCP6R_ShowStatInfo(VOID);

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _DHCP6R_FUN_H_ */

