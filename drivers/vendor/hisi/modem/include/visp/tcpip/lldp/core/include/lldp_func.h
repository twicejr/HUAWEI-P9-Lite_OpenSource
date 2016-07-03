
#ifndef _LLDP_FUNC_H_
#define _LLDP_FUNC_H_

#ifdef  __cplusplus
extern "C"{
#endif

ULONG LLDP_Init(ULONG ulSockTaskPri);
VOID LLDP_ProcTickTimerMsg();
VOID LLDP_ProcRXInfoAgeTimerMsg(VOS_VOID * arg);
VOID LLDP_ProcShutdownTimerMsg(VOS_VOID * arg);
VOID LLDP_ProcTransmitTimerMsg(VOS_VOID * arg);
VOID LLDP_TransmitProcess(ULONG ulInput,ULONG ulIfIndex,ULONG ulMacIndex);
VOID LLDP_TransmitTimerProcess(ULONG ulInput,ULONG ulIfIndex,ULONG ulMacIndex);
VOID LLDP_ReceiveProcess(ULONG ulInput,ULONG ulIfIndex,ULONG ulMacIndex,LLDP_RAW_PACKET_S *pstRcvPacket );
ULONG LLDP_GetTransmitState(ULONG ulIfIndex, ULONG ulMacIndex);
ULONG LLDP_GetReceiveState(ULONG ulIfIndex, ULONG ulMacIndex);
LLDP_LOCAL_PORT_S * LLDP_GetLocalPortNodeByIfIndex(ULONG ulIfIndex);
LLDP_LOCAL_PORT_STAT_S * LLDP_GetLocalPortStat(ULONG ulIfIndex,ULONG ulMacIndex);
LLDP_LOCAL_AGENT_S *LLDP_FindAgentByIfIndex(ULONG ulIfIndex,ULONG ulMacIndex);
ULONG LLDP_TxFrame(ULONG ulIfIndex,ULONG ulMacIndex);
ULONG LLDP_InitiAgent(LLDP_LOCAL_AGENT_S *pstAgentNode,ULONG ulIfIndex,ULONG ulMacIndex);
ULONG LLDP_InitPort(LLDP_LOCAL_PORT_S *pstLocalPort, ULONG ulIfIndex);
LLDP_MANAGEMENT_INFO_S* LLDP_GetManAddr(ULONG ulIfIndex, ULONG ulMacIndex);
ULONG LLDP_GetMacIndex(UCHAR *ppucPkt,ULONG ulPktLen);
ULONG LLDP_Core_ReceivePacket(ULONG ulIfIndex, UCHAR *pucPktStart,ULONG ulPktLen);
ULONG LLDP_GetTransmitTimerState(ULONG ulIfIndex, ULONG ulMacIndex);
ULONG LLDP_GlobalCfgMgr(ULONG ulCfgType, ULONG ulValue);
ULONG LLDP_SetPortMode(ULONG ulIfIndex, ULONG ulMacIndex, ULONG ulPortMode);
ULONG LLDP_AddPort(ULONG ulIfIndex, ULONG ulType);
ULONG LLDP_DelPort(ULONG ulIfIndex);
ULONG LLDP_UpdatePort(ULONG ulIfIndex, ULONG ulCMD, VOID *pData);

VOID LLDP_DebugFSM(ULONG ulFSMType, ULONG ulIfIndex, ULONG ulMacIndex,
                             ULONG ulInput, ULONG ulCurState,  ULONG ulNextState, 
                             ULONG ulAction);
VOID LLDP_DebugAllPKT(ULONG ulIfIndex, CHAR* pcBuf, ULONG ulLen);
VOID LLDP_DebugPKT(ULONG ulPKTType, ULONG ulIfIndex, ULONG ulMacIndex, CHAR* pcBuf, ULONG ulLen);
VOID LLDP_DebugSendPKT(ULONG ulPKTType, UCHAR* pucPkt, ULONG ulPktLen, ULONG ulIfIndex, ULONG ulMacIndex);
VOID LLDP_DebugRecvPKT(ULONG ulPKTType, ULONG ulIfIndex, ULONG ulMacIndex,LLDP_LOCAL_REM_INFO_S* pstRemInfo);
VOID LLDP_DebugRem(ULONG ulRemType, ULONG ulIfIndex, ULONG ulMacIndex, LLDP_LOCAL_REM_INFO_S* pstRem);
ULONG LLDP_SendMsg(ULONG ulQueID, ULONG ulEvtID, ULONG ulMsgID, ULONG ulIfIndex, ULONG ulMacIndex, VOID* pstPacket);
ULONG LLDP_SendGlobalMsg(ULONG ulQueID, ULONG ulEvtID, ULONG ulMsgID, ULONG ulMacIndex, VOID* pstPacket);
ULONG LLDP_PacketToNeighbourNode(UCHAR *pucPkt, ULONG ulPktLen, ULONG ulIfIndex, 
  ULONG ulMacIndex, LLDP_LOCAL_REM_INFO_S *pstRemInfoNode, LLDP_LOCAL_AGENT_S *pstAgent);
ULONG LLDP_FSM_RXFrame(ULONG ulIfIndex,ULONG ulMacIndex,LLDP_RAW_PACKET_S *pstRcvPacket,LLDP_LOCAL_REM_INFO_S 
*pstRemInfoNode);
ULONG LLDP_RxProcessFrame(ULONG ulIfIndex, ULONG ulMacIndex,UCHAR* pucPkt, ULONG ulPktLen, LLDP_LOCAL_REM_INFO_S 
*pstRemInfoNode);
LLDP_LOCAL_REM_INFO_S* LLDP_FindNeighbour(ULONG ulIfIndex,ULONG ulMacIndex,LLDP_LOCAL_REM_INFO_S *pstRemInfoNode);
BOOL_T  LLDP_IsRxChange(LLDP_LOCAL_REM_INFO_S *pstRemInfoNodeA,LLDP_LOCAL_REM_INFO_S *pstRemInfoNodeB);
ULONG LLDP_SomethingChangedRemote(ULONG ulIfIndex,ULONG ulMacIndex,ULONG operate,LLDP_LOCAL_REM_INFO_S * 
pstRemInfoNode);
ULONG LLDP_GetEthType(UCHAR *pucPkt, ULONG ulPktLen);

ULONG LLDP_GetPortByIndex(ULONG ulIfIndex, LLDP_LOCAL_PORT_S **ppstPort);  
ULONG LLDP_IfCtrl (ULONG ulCMD, ULONG ulIfIndex, VOID *pData);

/*lldp_tool.c*/
VOID LLDP_CopyPortInfo(LLDP_PORT_INFO_S *pstPortInfo, LLDP_LOCAL_PORT_S *pstLocalPortInfo);
INT32 LLDP_GetMacInfo(CHAR* pszShowInfo, UCHAR *pszMacInfo, INT32 i32OffsetInput, INT32 i32BufLen);
INT32 LLDP_GetNetAddressInfo(CHAR* pszShowInfo, UCHAR* pucNetworkAdress, 
                                INT32 i32OffsetInput, INT32 i32BufLen);
INT32 LLDP_GetIPv4AddressInfo(CHAR* pszShowInfo, UCHAR* pucIPv4AdressInfo, INT32 i32OffsetInput, INT32 i32BufLen);
INT32 LLDP_GetIPv6AddressInfo(CHAR* pszShowInfo, UCHAR* pucIPv6AdressInfo, INT32 i32OffsetInput, INT32 i32BufLen);
ULONG LLDP_CheckChassisIdNetworkAddress(UCHAR*pucPktCur, ULONG usTLVLen);
INT32 LLDP_GetChassisComponetInfo(CHAR* pszShowInfo, UCHAR *pszComponentInfo, ULONG ulComponentLen,
                                                      INT32 i32OffsetInput, INT32 i32BufLen);
INT32 LLDP_GetChassisIDInfo(CHAR* pszShowInfo, ULONG ulSubtype,
                                         UCHAR* pucChassisId, ULONG ulChassisIdLen, 
                                         INT32 i32OffsetInput, INT32 i32BufLen);
INT32 LLDP_GetPortIDInfo(CHAR* pszShowInfo, UCHAR ucSubtype, UCHAR* pucPortId,
                           INT32 i32OffsetInput, INT32 i32BufLen);
INT32 LLDP_GetManageAddressInfo(CHAR* pszShowInfo, ULONG ulSubtype, UCHAR* pucManaddr,
                                                  INT32 i32OffsetInput, INT32 i32BufLen);
ULONG LLDP_ManageAddressCmp(CHAR * pcManageAddrA, CHAR *pcManageAddrB, ULONG ulAddrType);
ULONG LLDP_ChassisidCmp(LLDP_CHASSISID_INFO_S *pstRemChassisIdInfoA, LLDP_CHASSISID_INFO_S *pstRemChassisIdInfoB);
VOID LLDP_PrintPortInfo(CHAR *pIfName, ULONG ulIfIndex, LLDP_PORT_INFO_S *pstPortInfo);
VOID LLDP_PrintRemInfo(LLDP_REM_INFO_S *pstRemInfo);
VOID LLDP_CopyRemInfo(LLDP_REM_INFO_S * pstRemInfo, LLDP_LOCAL_REM_INFO_S *pstLocalRem);
VOID LLDP_PrintPortStat(LLDP_PORT_STAT_S *pstPortStat);
VOID LLDP_PrintSysStat(LLDP_SYS_STAT_S *pstSysStat);
ULONG LLDP_GetRemTimeMark(ULONG ulLastMarkTime);
ULONG LLDP_FindPPVID(LLDP_LOCAL_PORT_S *pstPort, USHORT usPpvid);
ULONG LLDP_AddPPVID(LLDP_LOCAL_PORT_S *pstPort, LLDP_PPVID_INFO_S *pstPpvid);
ULONG LLDP_DelPPVID(LLDP_LOCAL_PORT_S *pstPort, LLDP_PPVID_INFO_S *pstPpvid);
BOOL_T LLDP_IsRemPpvidEqual(LLDP_LOCAL_REM_INFO_S *pstRemeA, LLDP_LOCAL_REM_INFO_S *pstRemB);
BOOL_T LLDP_IsRemVlanNameEqual(LLDP_LOCAL_REM_INFO_S *pstRemeA, LLDP_LOCAL_REM_INFO_S *pstRemB);
ULONG LLDP_DelAgentRemInfo(ULONG ulIfIndex, ULONG ulMacIndex);
ULONG LLDP_DelPortProcess(ULONG ulIfIndex);
ULONG LLDP_SetAgentStat(ULONG lPktChkResult, LLDP_LOCAL_AGENT_S * pstLocalAgent);
ULONG LLDP_ClearAgentStat(LLDP_LOCAL_PORT_S *pstLocalPort, ULONG ulDestAddrGroup);
ULONG  LLDP_SetRxTxFilter(ULONG ulTxFilter, ULONG ulRxFilter);
VOID LLDP_ShowLocalAgentStat(CHAR* pszIfName, ULONG ulDestAddrGroup);
ULONG LLDP_CheckSysCapInfo(LLDP_SYS_CAPABILITY_INFO_S *pstSysCap)  ;
ULONG LLDP_CheckManageVidInfo(ULONG ulOperate, LLDP_MANAGEMENT_VID_INFO_S *pstMngVid) ;
ULONG LLDP_CheckPortInfo(LLDP_CFG_PORT_INFO_S *pstPortInfo) ;
ULONG LLDP_CheckPortVidInfo(LLDP_PVID_INFO_S *pstPortVlanId)  ;
ULONG LLDP_CheckMacPhyInfo(LLDP_MAC_PHY_CFG_INFO_S *pstMacPhyCfg) ;
ULONG LLDP_CheckLinkAggInfo(ULONG ulOperate,LLDP_LINK_AGG_INFO_S *pstLinkAgg)  ;
ULONG LLDP_CheckVlanNameInfo(LLDP_LOCAL_PORT_S *pstLocalPort, ULONG ulOperate, LLDP_VLAN_NAME_INFO_S stVlanName[], ULONG ulNumber)  ;
ULONG LLDP_CopyVlanNameInfo(LLDP_LOCAL_PORT_S *pstLocalPort, ULONG ulOperate, LLDP_VLAN_NAME_INFO_S stVlanName[], ULONG ulNumber) ;
ULONG LLDP_CopyVlanNameNode(LLDP_VLAN_NAME_INFO_S *pstVlanNameA, LLDP_VLAN_NAME_INFO_S *pstVlanNameB);
CHAR **LLDP_DebugGetFSMStateInfo(ULONG ulFSMType);
ULONG LLDP_CheckSysNameAndDescInfo(LLDP_CFG_SYS_NAME_DESC_S *pstSysNameDesc);
ULONG LLDP_CheckChassisID(LLDP_CHASSISID_INFO_S *pstChassisId);
ULONG LLDP_CheckManagementInfo(ULONG ulOperate, LLDP_MANAGEMENT_INFO_S *pstManagement) ;



VOID LLDP_SetLinkAggrTlvSwitch(ULONG ulLinkAggrTlvSwitch);
BOOL_T LLDP_IsEmptyMacAddr(CHAR *pszMacAddr);

extern LONG vos_printf(const CHAR *fmt, ...);
extern ULONG TCPIP_CreateMutex(CHAR *pMutexName, ULONG *pulMutexID);
extern ULONG TCPIP_DeleteMutex(ULONG ulMutexID);
extern VOID TCPIP_InfoOutput(CHAR *pInfo);

extern VOS_UINT32 VOS_Tm_BootInSec( VOS_UINT32 *pulSecond,
                                    VOS_UINT32 *pulUSecond );

extern ULONG PPI_MultiMac_Update(ULONG ulIfIndex, ULONG ulOptType, UCHAR *pszMacAddr, UCHAR *pszMacMask);

extern VOID LLDP_WarningRemInfoCopy(LLDP_REM_INFO_S **pstDest, LLDP_LOCAL_REM_INFO_S *pstSource);
extern ULONG LLDP_IsPPVIDExist(LLDP_LOCAL_REM_INFO_S *pstRemInfoNode, USHORT usPpvid);
extern ULONG LLDP_IsVlanNameExist(LLDP_LOCAL_REM_INFO_S *pstRemInfoNode, LLDP_VLAN_NAME_INFO_S *RemVlanName);
#ifdef  __cplusplus
}
#endif

#endif

