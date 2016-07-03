
#ifndef _ETHARP_CORE_API_H_
#define _ETHARP_CORE_API_H_

#ifdef    __cplusplus
extern "C"{
#endif

ULONG  ETHARP_EtherOutput( MBUF_S *pMBuf );
ULONG  ETHARP_LinkIoCtl(IFNET_S* pIf, ULONG ulCmdIndex, CHAR *pData);
ULONG  ETHARP_IoCtl(IFNET_S* pIf, ULONG ulCmdIndex, CHAR *pData);
ULONG  ETHARP_SubIoCtl(IFNET_S* pIf, ULONG ulCmdIndex, CHAR *pData);
ULONG  ETHARP_ArpRequest( ULONG ulIfIndex,  ULONG ulSrcIpAddr, ULONG ulDstIpAddr, UCHAR *pEnAddr);
ETHARP_ARPRTENTRY_S*   ETHARP_LookupArp(ETHARP_MTSOFTC_S* pMtSoft, ULONG  ulIpAddr,ULONG ulVrfIndex);
ULONG  ETHARP_ArpFreeAll( IFNET_S* pIf);
ULONG  ETHARP_InsertArp(ETHARP_MTSOFTC_S* pMtSoft, ULONG  ulIpAddr,ULONG ulVrfIndex,ULONG ulFlag,ETHARP_ARPRTENTRY_S** pRetNode);
ULONG  ImplEthFactoryQueryInterface(IUnknown *This, COMP_IID iid, LPVOID * ppvObj);
ULONG  ImplEthFactoryCreateInstance (IComponentFactory *This,  COMP_IID iid, VOID **ppvObj );
ENQUEUE_PF  ETHARP_EtherInput(IFNET_S*  pIf, MBUF_S * pMBuf);
ULONG  ETHARP_ArpInput(MBUF_S *pMBuf);
ULONG  ETHARP_ArpDropPacket(MBUF_S *pMBuf, ULONG ulCmd, CHAR *pcData);
ULONG  ETHARP_SendFreeArp(ULONG ulIfIndex, ULONG ulIpAddr);
ULONG  ETHARP_Init_Com(COM_ID_INFO_S *pComInfo, ULONG  ulComLen);
ULONG  ETHARP_Activate_Com ();
ULONG  ETHARP_SetModuleInfo(ETHARP_MOD_INFO_S *pstMInfo);
ULONG  ETHARP_OpenArpEntry (UINTPTR *pulWaitListHandle);
ULONG  ETHARP_GetArpEntry (UINTPTR ulEntryWaitList, ETHARP_ARPRTENTRY_S *pstArpEntry);
ULONG  ETHARP_CloseObject ( UINTPTR ulWaitListHandle );
/* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
ULONG  ETHARP_DeleteARPEntry ( ULONG ulIpAddr, ULONG ulScope,ULONG ulVrfIndex);
/* End:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
ULONG   ETHARP_ClearStaticARPEntry();
ULONG  ETHARP_ClearDynamiccARPEntryByInterface(ULONG ulIfIndex);
ULONG   ETHARP_ClearAllARPEntry();
/* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
ULONG  ETHARP_AddStaticARPEntry ( ULONG ulIpAddr , UCHAR ucMacAddr[],ULONG ulVrfIndex);
/* End:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
ULONG  ETHARP_GetStaticArpNumber();
VOID   ETHARP_SetDebugSwitch ( ULONG ulDebugArp, ULONG ulDebugEthernet, ULONG ulAclGroupNum);
ULONG  ETHARP_GetDebugSwitch(ULONG* pulDebugArp, ULONG* pulDebugEthernet, ULONG* pulAclGroupNum);
ULONG  ETHARP_RegShellApi ( ETHARP_SHELL_CALLBACK_SET_S *pstCallBkSet);
VOID   ETHARP_ARPDebugInfo(ETHARP_ETHERARP_S *pArp, ULONG ulArpEvent,CHAR *pszIfName);
VOID   ETHARP_EthPacketDebugInfo(IFNET_S * pIf, ETHARP_ETSNAPHDR_S * pHead, ULONG ulErrCode, ULONG ulDebugEvent);
ULONG  ETHARP_IsEthernetType(ULONG ulIndex);
ULONG  ETHARP_GetMac(ULONG ulIfIndex, UCHAR *pucMac);
ULONG  ETHARP_InitEthIf(IFNET_S *pIf, ULONG ulPosition, ULONG *pulRet);
ULONG  ETHARP_StartEthIf(IFNET_S *pIf, ULONG ulPosition, ULONG *pulRet);
ULONG  ETHARP_LinkHideCmd(IFNET_S *pIf, ULONG ulPosition, ULONG *pulRet);
ULONG  ETHARP_FreeBlock(IFNET_S *pIf, ULONG ulPosition, ULONG *pulRet);
VOID   ETHARP_SendGratuitousArp(MBUF_S *pMBuf, UCHAR* szSrcMacAddr, 
                              UCHAR* szProAddr, USHORT usOpType, ULONG ulIfIndex, ULONG ulUserOrVISP);

ULONG  ETHARP_ArpRequestForVLAN( ULONG ulIfIndex,  ULONG ulSrcIpAddr, ULONG ulDstIpAddr, 
                                 UCHAR *pEnAddr, ULONG ulVID);
ULONG  ETHARP_DealInput(ETHARP_MTSOFTC_S*   pMt, 
                              IFNET_S *pIf, 
                              MBUF_S * pMBuf, 
                              ULONG ulProtocolType,
                              ULONG ulVLANFlag,
                              ULONG ulPktFmt,
                              ETHARP_ETSNAPHDR_S* pHead);
ULONG  ETHARP_ArpRequestForVLAN( ULONG ulIfIndex,  ULONG ulSrcIpAddr, ULONG ulDstIpAddr, UCHAR *pEnAddr, ULONG ulVID);
ULONG  ETHARP_ResendRequest(ETHARP_MTSOFTC_S* pMtSoft, ETHARP_ARPRTENTRY_S* pNode, ULONG ulflag);
ULONG  ETHARP_SetArpProxy(ULONG ulIfIndex, ULONG ulFlag, ULONG ulSetYes) ;
ULONG  ETHARP_AddrCheck(ULONG ulAddr);

VOID  ETHARP_DebugACLFilter(MBUF_S* pMBuf, ULONG* pulMatch);

/****************************extern functions**********************************/
extern ULONG getSelfBoardId ();
/*******************************************************************************************/
ULONG  ETHARP_SetVlan (ULONG ulIfIndex , ULONG ulSetYes);
ULONG  ETHARP_GetVlan(ULONG ulIfIndex, ULONG * pulVlanFlag);

ULONG ETHARP_AddStaticARPEntryWithVlan_PT( ULONG ulIpAddr , UCHAR ucMacAddr[],USHORT usVID,ULONG ulVrfIndex);

/* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
ULONG  ETHARP_AddStaticARPEntry_PT( ULONG ulIpAddr , UCHAR ucMacAddr[],ULONG ulVrfIdex);

ULONG  ETHARP_DeleteARPEntry_PT(ULONG ulIpAddr, ULONG ulScope, ULONG ulVrfIndex);
/* End:VISP1.7C03 VRF wangchengyang , 2009-02-06 */

ULONG  ETHARP_ClearDynamiccARPEntryByInterface_PT(ULONG ulIfIndex);
ULONG  ETHARP_ClearAllARPEntry_PT();
ULONG  ETHARP_ClearAllDynamicARPEntry_PT();
ULONG  ETHARP_ClearStaticARPEntry_PT();
ULONG  ETHARP_OpenArpEntry_PT (UINTPTR *pulWaitListHandle);
ULONG  ETHARP_GetArpEntry_PT(UINTPTR ulEntryWaitList, ETHARP_ARPRTENTRY_S *pstArpEntry);

ULONG ETHARP_PPI_GetArpByIp(ULONG ulIfIndex, ULONG ulIpAddr, PPI_ARP_S *pstPpiArp);
VOID  ETHARP_DealLinkCtrlMsg(UINTPTR aulMsg[4]);
ULONG ETHARP_ArpMissNotify(ULONG ulIfIndex, ULONG ulDstIpAddr);
ULONG ETHARP_PPI_ArpMiss(ULONG ulIfIndex, ULONG ulDstIpAddr, ULONG ulVlinkIndex,ULONG ulIfVrfIndex);
VOID ETHARP_DelStaticVlinkBySubnet(ULONG ulIPaddr, ULONG ulMask, ULONG ulIfindex);
/* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-09 */
ULONG ETHARP_GetArpEntryByIPAddr(ULONG ulIPAddr, ARPINFO_S *pstARPInfo, ULONG ulVrfIndex, ULONG ulFlag);
/* End:VISP1.7C03 VRF wangchengyang , 2009-02-09 */
ULONG ETHARP_GetArpNum(ULONG ulType);
ULONG ETHARP_GetStatInfo(ULONG ulIfIndex, ETHSTAT_S *pstETHSTAT_S);
ULONG ETHARP_ClearStatInfo(ULONG ulIfIndex);

/* 查询指定的地址是否和接口上的地址处于相同网段 */
VOID ETHARP_DeleteArpEntry_NoSameNet(IFNET_S* pstIf);
ULONG ETHARP_ArpDeleteEntry_ForSubIF( IFNET_S* pMainIf, IFNET_S* pSubIf );
/* End of addition */

/*Added by x36317, 获取ETH控制块首指针, A82D21234*/
ETHARP_MTSOFTC_S * ETHARP_GetFirstMt();

/* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-09 */
ULONG ETHARP_DelStaticArpByVrf( ULONG ulVrfIndex);
/* End:VISP1.7C03 VRF wangchengyang , 2009-02-09 */
ULONG ETHARP_SendUnArp(ETHARP_UNARPINFO_S *pstUnarpInfo);

ETHARP_INTERMEDIATE_HOOK_FUNC ETHARP_GetOutputIntermediateHook(VOID);
ULONG TCPIP_GetVlanHead(MBUF_S * pstMbuf, ULONG * pulVlanHead);

ULONG TCPIP_SpecialArpProxy(SPECIAL_ARPPROXY_PARA_S *pstSpecArpPrxyPara);

ULONG ETHARP_DeleteARPEntryBySubIndex(IFNET_S *pSubIf);
ULONG ETHARP_DeleteARPEntryByVlan(ULONG ulSubIndex,IFNET_S* pMainIf,USHORT usVID, ULONG ulScope);
ULONG ETHARP_Ethvlan_Proc_Hook_Register(ETHARP_VLAN_PROC_HOOK_S *pfHookFunc);
ULONG ETHARP_DealIpConflict(ULONG ulIPType, IFNET_S* pstRcvIf, ULONG ulIpAddr, UCHAR *pucMac);

VOID ETHARP_IPConflictPrcs1STimer(VOID *pVoid);
VOID ETHARP_IPConflictClearWarning(ULONG ulClearType, ETHARP_IP_CONFLICT_ITEM_S *pstIPConflictItem, UCHAR *pucMac);
VOID ETHARP_ExponentialSendFreeArp(VOID);
ULONG ETHARP_ConflictIPIsExist(ULONG i);

ULONG ETHARP_AddStaticARPEntryWithVlan ( ULONG ulIpAddr , UCHAR ucMacAddr[], ULONG ulIfIndex, 
                                                      USHORT usVID, ULONG ulPortIfIndex,ULONG ulVrfIndex);
ULONG ETHARP_AddStaticArpWithVlanAndPortIfIndex(ULONG ulIpAddr , UCHAR ucMacAddr[],USHORT usVID, ULONG ulPortIfIndex);
ULONG Etharp_FreeDynamicArpWithVlan(IFNET_S *pVlanIf, USHORT usVlanId);
ULONG Etharp_FreeAllArpWithVlan(IFNET_S *pVlanIf, USHORT usVlanId);
ULONG ETHARP_FreeDynamicArpWithPortIfIndex(IFNET_S *pVlanIf, ULONG ulPortIfIndex);
ULONG ETHARP_FreeAllArpWithVlanAndPortIfIndex(IFNET_S *pVlanIf, USHORT usVlanId, ULONG ulPortIfIndex);
ULONG ETHARP_ResolveForVlanArpProxy(IFNET_S *pIf, ULONG ulDstIpAddr, ULONG ulSrcIpAddrToReply);
ULONG ETHARP_FreeStaticArpWithPortIfIndex(ULONG ulPortIfIndex);
ULONG ETHARP_FreeAllArpInVlanIf(IFNET_S *pstVlanIf);
ULONG ETHARP_PacketDebugInfoForL2VLAN(MBUF_S *pMBuf, IFNET_S *pIf, ULONG ulDebugEvent);
ULONG ETHARP_ArpFreeBasedOnVlanAndIfIndex(USHORT usVlan, ULONG ulIfIndex);
ULONG ETHARP_ArpAgeAll(ULONG ulIfIndex);
ULONG ETHARP_ArpFreeDynamicBasedOnVlanAndOutPort(USHORT usVlan,ULONG ulIfIndex,ULONG ulVlanif);
ULONG ETHARP_ArpRequestForUser(ULONG ulIfIndex, ULONG ulSrcIpAddr, ULONG ulDstIpAddr, 
                               ULONG ulIsUnicast, UCHAR* pucSrcMac, UCHAR *pucDstMac);
ULONG ETHARP_SendUserArp(ULONG ulIfIndex, ULONG ulDstIP, ULONG ulIsUnicast);
ULONG ETHARP_GetUserArpStat(ULONG ulIfIndex, USERARPSTAT_S *pstStat);
ULONG ETHARP_ClearUserArpStat(ULONG ulIfIndex);

ULONG ETHARP_SendArpPkt(ULONG ulIfIndex, ULONG ulSrcIpAddr, 
                            ULONG ulDstIpAddr, UCHAR* pucDstMac, USHORT usVid,
                            BOOL_T bIsReply);
ULONG ETHARP_GetLinkStatus(ULONG ulIfIndex, ULONG *pulLinkStatus, ULONG *pulLink6Status);
LONG  ETHARP_FindFreeArpNodeCmp(VOID *pVal, SLL_NODE_S * pNode);
ULONG ETHARP_DealFirstSendFreeArp(ULONG ulIfIndex, ULONG ulIpAddr);
ULONG ETHARP_Is_Vrrp_VirtualIpAddr(ULONG ulIfIndex, ULONG ulIpAddr);
VOID ETHARP_SetMbufMacFlag(MBUF_S *pstMbuf, UCHAR *ucMacAddr);

ULONG ETHARP_CheckVaild(IFNET_S *pstIfNet);
ULONG ETHARP_CheckEthIfVaild(IFNET_S *pstIfNet);

VOID  ETHARP_ARPLogInfo(ULONG ulIfIndex, ULONG ulArpEvent, ETHARP_ETHERARP_S *pArp,ULONG ulVlanId);
ULONG ETHARP_SetArpLogSwitch(ULONG ulIfIndex, ULONG ulLogSwitch);
ULONG ETHARP_GetArpLogSwitch(ULONG ulIfIndex, ULONG *pulLogSwitch);

ULONG ETHARP_RegFuncEtharpDealHook(ULONG ulInOrOut, ULONG ulPriority, ETHARP_INTERMEDIATE_HOOK_FUNC pfHookFunc);
ULONG ETHARP_UnRegFuncEtharpDealHook(ULONG ulInOrOut, ETHARP_INTERMEDIATE_HOOK_FUNC pfHookFunc);
ULONG ETHARP_Intermediate_Process(MBUF_S *pstMBuf, ETHARP_INTERMEDIATE_DEAL_HOOK_S *psttmpInter);

ULONG ETHARP_AddDynamicARPEntry(ULONG ulIfIndex, UCHAR *pucMacAddr, ULONG ulDstIpAddr);

ULONG ETHARP_AddDynamicARPEntryWithVlan_PT(ULONG ulIfIndex, UCHAR *pucMacAddr, ULONG ulDstIpAddr, USHORT usVID);
ULONG ETHARP_AddDynamicARPEntryWithVlan(ULONG ulIfIndex, UCHAR *pucMacAddr, ULONG ulDstIpAddr, USHORT usVID);

ULONG ETHARP_SendArpRequest(ULONG ulIfIndex, ULONG ulDstIpAddr);
ULONG ETHARP_SetVlanTag (ULONG ulIfIndex , ULONG ulVlanTag);
ULONG ETHARP_GetVlanTag (ULONG ulIfIndex , ULONG* pulVlanTag);
ULONG ETHARP_SetARPExpireTimeByIndex(ULONG ulTime, ULONG ulIfIndex);
ULONG ETHARP_GetARPExpireTimeByIndex(ULONG* pulTime, ULONG ulIfIndex);
VOID  ETHARP_ArpMissDebug(CHAR *pIntfName, ULONG ulIfIndex, ULONG ulDstIpAddr, ULONG ulCmd);
VOID  ETHARP_ShowOneArpInfoByEntry(ETHARP_ARPRTENTRY_S *pstArpEntry,ULONG ulCount);
ULONG ETHARP_ShowArpByIfIndex(ULONG ulIfIndex);
VOID ETHARP_PpiAddARPEntry(ETHARP_ARPRTENTRY_S *pstArpEntry);
VOID ETHARP_PpiDelARPEntry(ETHARP_ARPRTENTRY_S *pstArpEntry);
VOID ETHARP_PpiUpdateARPEntry(ETHARP_ARPRTENTRY_S *pstArpEntry);

ULONG ETHARP_PpiAddFakeNode(PPI_ARP_S *pstPpiEntry, ULONG *pulVlinkIndex);
VOID ETHARP_PpiDelFakeNode(PPI_ARP_S *pstPpiEntry);
VOID ETHARP_CopyARPEntryToPpi(PPI_ARP_S *pstPpiArp, ETHARP_ARPRTENTRY_S *pstNode);
VOID ETHARP_PpiUpdateARPEntryNoUpdateRoute(ETHARP_ARPRTENTRY_S *pstArpEntry,ULONG ulInterTime);
ULONG ETHARP_Guard_Proc_Hook_Register(ETHARP_GUARD_PROC_HOOK_S *pfHookFunc);
ULONG ETHARP_SetUnicastARPCount(ULONG ulCount);
ULONG ETHARP_GetUnicastARPCount(ULONG *pulCount);
ULONG ETHARP_SetARPCapture(ULONG ulIfIndex, ULONG ulRcvCaptureQueLen, ULONG ulSndCaptureQueLen);
ULONG ETHARP_GetARPCapture(ULONG ulIfIndex,ULONG *pulRcvCaptureQueLen, ULONG *pulSndCaptureQueLen);
ULONG ETHARP_GetARPCaptureQue(ULONG ulIfIndex, ULONG *pulRcvQueMbufNum, MBUF_S **ppstRcvMbuf,
                              ULONG *pulSndQueMbufNum, MBUF_S **ppstSndMbuf);
ULONG ETHARP_GetPktInfo(MBUF_S *pstMBuf, ETHARP_PKT_INFO_S *pstEthPktInfo);
ULONG ETHARP_ARPCaptureQue_Save(MBUF_S *pMBuf, MBUF_QUEUE_S *pstArpPktQue);
ULONG ETHARP_DelTimerEntryNode(ETHARP_ARPRTENTRY_S* pNode);
ULONG ETHARP_AddRefreshTimerEntryNode(ETHARP_ARPRTENTRY_S* pNode);
VOID   ETHARP_ArpTimer(VOID* pTimerList);
ULONG ETHARP_SetArpDelayDelTime(IFNET_S* pIf, ULONG ulTime);

ULONG ETHARP_SetArpEntryAgeTime(ETHARP_ARPRTENTRY_S* pArpEntry, ULONG ulAgeTime);

ULONG ETHARP_AdjExpTime(ETHARP_ARPRTENTRY_S* pNode);

ULONG ETHARP_SetArpExpireOffsetTime(UCHAR ucTime);
ULONG ETHARP_GetArpExpireOffsetTime(UCHAR *pucTime);
ULONG ETHARP_SetARPExpireTimeByIf( ULONG ulTime, ULONG ulIfIndex);

ULONG ETHARP_SetARPDetectTimes( ULONG ulDetectTimes, ULONG ulIfIndex );

ETHARP_MTSOFTC_S* ETHARP_GetMTSoftForMainIf(IFNET_S *pstIfnet);
ULONG ETHARP_ClearIPConflict(IFNET_S* pIf, ULONG ulIpAddr);

ULONG ETHARP_CheckIpConflictResp(ULONG ulDstIpAddr, ULONG ulVrfIndex, ULONG ulSecHigh, ULONG ulSecLow);

extern ULONG ETHARP_CopyARPEntryToArpInfo(ARP_INFO_S *pstArpInfo, ETHARP_ARPRTENTRY_S *pstNode);
extern VOID ETHARP_GetBasicArpInfoFromARPEntry(ARPINFO_S *pstArpInfo, ETHARP_ARPRTENTRY_S *pstArpNode);
extern ULONG ETHARP_GetArpNodeByIfAndIP(ULONG ulIfIndex, ULONG ulIpAddr, ULONG ulScope, ETHARP_ARPRTENTRY_S **ppstArpNode);
extern ULONG ETHARP_GetArpEntryByIntfAndIPAddr(ULONG ulIfIndex, ULONG ulIpAddr, ARPINFO_S *pstArpInfo);
extern ULONG ETHARP_DelDynamicArpEntryByIntf(ULONG ulIfIndex, ULONG ulIpAddr);

#ifdef __cplusplus
}
#endif    

#endif /* _ETHARP_CORE_API_H_ */   

