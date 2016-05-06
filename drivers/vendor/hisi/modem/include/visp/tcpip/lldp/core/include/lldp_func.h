/*******************************************************************************
*
*
*                Copyright 2011, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              lldp_func.h
*
*  Project Code: V2R3C06
*   Module Name:   
*  Date Created: 2011-09-27
*        Author: liangjicheng 00103192
*   Description: 内部函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2011-09-27   liangjicheng 00103192   Create
*
*******************************************************************************/
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
/*Added by guo00178934, 函数参数变更, 2011/11/8   问题单号:DTS2011110800968 */
ULONG LLDP_PacketToNeighbourNode(UCHAR *pucPkt, ULONG ulPktLen, ULONG ulIfIndex, 
  ULONG ulMacIndex, LLDP_LOCAL_REM_INFO_S *pstRemInfoNode, LLDP_LOCAL_AGENT_S *pstAgent);
/* End of Added by guo00178934, 2011/11/8   问题单号:DTS2011110800968 */
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
/*Added by zhang00187023,管理地址比较由字符串比较改为内存比较, 2011/11/11   问题单号:DTS2011111104717 */
ULONG LLDP_ManageAddressCmp(CHAR * pcManageAddrA, CHAR *pcManageAddrB, ULONG ulAddrType);
/* End of Added by zhang00187023, 2011/11/11   问题单号:DTS2011111104717 */
ULONG LLDP_ChassisidCmp(LLDP_CHASSISID_INFO_S *pstRemChassisIdInfoA, LLDP_CHASSISID_INFO_S *pstRemChassisIdInfoB);
/*Added by guo00178934, 补充接口索引显示, 2011/11/8   问题单号:DTS2011110800968 */
VOID LLDP_PrintPortInfo(CHAR *pIfName, ULONG ulIfIndex, LLDP_PORT_INFO_S *pstPortInfo);
/* End of Added by guo00178934, 2011/11/10   问题单号:DTS2011110800968 */
VOID LLDP_PrintRemInfo(LLDP_REM_INFO_S *pstRemInfo);
VOID LLDP_CopyRemInfo(LLDP_REM_INFO_S * pstRemInfo, LLDP_LOCAL_REM_INFO_S *pstLocalRem);
VOID LLDP_PrintPortStat(LLDP_PORT_STAT_S *pstPortStat);
/*Added by guo00178934, 函数参数变更, 2011/11/8   问题单号:DTS2011110800968 */
VOID LLDP_PrintSysStat(LLDP_SYS_STAT_S *pstSysStat);
/* End of Added by guo00178934, 2011/11/8   问题单号:DTS2011110800968 */
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
/*Added by guo00178934, 补充TLV收发开关；补充TLV详细查询接口, 2011/11/8   问题单号:DTS2011110800426 */
ULONG  LLDP_SetRxTxFilter(ULONG ulTxFilter, ULONG ulRxFilter);
VOID LLDP_ShowLocalAgentStat(CHAR* pszIfName, ULONG ulDestAddrGroup);
/* End of Added by guo00178934, 2011/11/8   问题单号:DTS2011110800426 */
ULONG LLDP_CheckSysCapInfo(LLDP_SYS_CAPABILITY_INFO_S *pstSysCap)  ;
/* Modified by zhangliangzhi00187023, 【检视发现问题】支持managevid tlv配置可删除, 2012/8/28   问题单号:DTS2012082808698  */
ULONG LLDP_CheckManageVidInfo(ULONG ulOperate, LLDP_MANAGEMENT_VID_INFO_S *pstMngVid) ;
/*End of Modified by zhangliangzhi00187023, 2012/8/28   问题单号:DTS2012082808698  */
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


/*******************************************************************************
*    Func Name: LLDP_SetLinkAggrTlvSwitch
* Date Created: 2011-11-04
*       Author: limin00188004
*  Description: 报文发送时选择802.1或802.3协议规定的Link Aggregation TLV。
*        Input: ULONG ulLinkAggrTlvSwitch:
*               值为0, 选择发送802.1中的规定; 值大于0，选择发送802.3中的规定.
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-11-04   limin00188004           Create
*
*******************************************************************************/
VOID LLDP_SetLinkAggrTlvSwitch(ULONG ulLinkAggrTlvSwitch);
BOOL_T LLDP_IsEmptyMacAddr(CHAR *pszMacAddr);

extern LONG vos_printf(const CHAR *fmt, ...);
extern ULONG TCPIP_CreateMutex(CHAR *pMutexName, ULONG *pulMutexID);
extern ULONG TCPIP_DeleteMutex(ULONG ulMutexID);
extern VOID TCPIP_InfoOutput(CHAR *pInfo);

extern VOS_UINT32 VOS_Tm_BootInSec( VOS_UINT32 *pulSecond,
                                    VOS_UINT32 *pulUSecond );

/*Added by zhangliangzhi00187023, 【检视发现问题】需要支持下发组播地址过滤功能, 2012/8/29   问题单号:DTS2012082907401 */
extern ULONG PPI_MultiMac_Update(ULONG ulIfIndex, ULONG ulOptType, UCHAR *pszMacAddr, UCHAR *pszMacMask);
/* End of Added by zhangliangzhi00187023, 2012/8/29   问题单号:DTS2012082907401 */

/*Added by luogaowei, 该函数用于拷贝上报告警时携带的邻居信息, 2013/4/7, DTS2013040700481 */
extern VOID LLDP_WarningRemInfoCopy(LLDP_REM_INFO_S **pstDest, LLDP_LOCAL_REM_INFO_S *pstSource);
extern ULONG LLDP_IsPPVIDExist(LLDP_LOCAL_REM_INFO_S *pstRemInfoNode, USHORT usPpvid);
extern ULONG LLDP_IsVlanNameExist(LLDP_LOCAL_REM_INFO_S *pstRemInfoNode, LLDP_VLAN_NAME_INFO_S *RemVlanName);
#ifdef  __cplusplus
}
#endif

#endif

