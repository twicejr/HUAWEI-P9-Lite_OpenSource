

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _IETH_H
#define _IETH_H

#include "tcpip/public/tcpip_id.h" 

DECLARE_INTERFACE( IIF_COMP_ETHERNET_ComIntFUN ) 
{
    IUNKNOWN_METHODS
  
    /* This method has to be used by bottom layer (driver) for sending packet to ethernet module */
    METHOD_( ENQUEUE_PF, pfETHARP_EtherInput) (IFNET_S*  pIf, MBUF_S * pMBuf);    
    /* This method has to be used by upper layer for sending packet by ethernet module */
    METHOD_( ULONG, pfETHARP_EtherOutput)( MBUF_S *pMBuf);

    /* This method have to be used by queue management modle to process packet in ARP queue */
    METHOD_( ULONG, pfETHARP_ArpInput)( MBUF_S *pMBuf);

    /* This methods have to be used by IFNET for sending control message to ethernet module */
    METHOD_( ULONG, pfETHARP_IoCtl)( IFNET_S* pIf, ULONG ulCmdIndex, CHAR *pData);
    METHOD_( ULONG, pfETHARP_LinkIoCtl)( IFNET_S* pIf, ULONG ulCmdIndex, CHAR *pData);    
    METHOD_( ULONG, pfETHARP_SubIoCtl)( IFNET_S* pIf, ULONG ulCmdIndex, CHAR *pData);      

    METHOD_( ULONG, pfETHARP_SendFreeArp)( ULONG ulIfIndex, ULONG ulIpAddr);  

    METHOD_(ULONG, pfETHARP_RegisterHook)(ULONG ulType, ETHARP_INTERMEDIATE_HOOK_FUNC pfFun);
    METHOD_(ULONG, pfETHARP_PPI_GetArpByIp)(ULONG ulIfIndex, ULONG ulIpAddr, PPI_ARP_S *pstPpiArp);
    METHOD_(VOID,  pfETHARP_DealLinkCtrlMsg)(UINTPTR aulMsg[4]);
    METHOD_(ULONG, pfETHARP_PPI_ArpMiss)(ULONG ulIfIndex, ULONG ulDstIpAddr, ULONG ulVlinkIndex,ULONG ulIfVrfIndex);
    METHOD_(VOID, pfETHARP_DelStaticVlinkBySubnet)(ULONG ulIPaddr, ULONG ulMask, ULONG ulIfindex);
    METHOD_(ULONG, pfETHARP_HA_SendCfgMsg) (ETHARP_MTSOFTC_S    *pstMt);
    METHOD_(ULONG, pfETHARP_HA_BatchBackup)();
    METHOD_(ULONG, pfETHARP_HA_Input)(UCHAR *pBuf, ULONG ulMsgLen);
    METHOD_(ULONG, pfETHARP_HA_Smooth)();
    METHOD_(ULONG, pfETHARP_HA_Clean)();
    METHOD_(ETHARP_MTSOFTC_S *, pfETHARP_GetFirstMt)();
    METHOD_( ULONG , pfTCPIP_SpecialArpProxy)(SPECIAL_ARPPROXY_PARA_S *pstSpecArpPrxyPara);
    METHOD_(ULONG, pfETHARP_SendUserArp)(ULONG ulIfIndex, ULONG ulDstIP, ULONG ulIsUnicast);
    METHOD_( ULONG , pfETHARP_DeleteARPEntryByVlan)(ULONG ulSubIndex,IFNET_S* pMainIf,USHORT usVID, ULONG ulScope);
    METHOD_( ULONG , pfETHARP_Ethvlan_Proc_Hook_Register)(ETHARP_VLAN_PROC_HOOK_S *pfHookFunc);
    METHOD_(ULONG, pfETHARP_SendArpPkt)(ULONG ulIfIndex, ULONG ulSrcIpAddr, ULONG ulDstIpAddr, 
                                        UCHAR* pucDstMac,USHORT usVid,BOOL_T bIsReply);
    METHOD_(ULONG, pfETHARP_GetLinkStatus)(ULONG ulIfIndex, ULONG *pulLinkStatus, ULONG *pulLink6Status);
    METHOD_(ULONG, pfETHARP_ArpRequest)(ULONG ulIfIndex,  ULONG ulSrcIpAddr, ULONG ulDstIpAddr, UCHAR *pEnAddr);
    METHOD_(VOID, pfETHARP_SendGratuitousArp)(MBUF_S *pMBuf, UCHAR* szSrcMacAddr,
                              UCHAR* szProAddr, USHORT usOpType, ULONG ulIfIndex, ULONG ulUserOrVISP);
    METHOD_(VOID, pfETHARP_Health_BatchCheckup)();
    METHOD_(ULONG, pfETHARP_LastWord_BatchCheckup)(CHAR *pstBuf, ULONG *pulLastWordLen);
    /* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-09 */
    METHOD_(ULONG, pfETHARP_DelStaticArpByVrf)(ULONG ulVrfIndex);
    /* End:VISP1.7C03 VRF wangchengyang , 2009-02-09 */
    METHOD_(ULONG, pfETHARP_SendUnArp)(ETHARP_UNARPINFO_S *pstUnarpInfo);
    METHOD_(ULONG, pfETHARP_ArpMissNotify)(ULONG ulIfIndex, ULONG ulDstIpAddr);
    METHOD_(ULONG, pfETHARP_ShowArpByIfIndex)(ULONG ulIfIndex);
    METHOD_(ULONG, pfTCPIP_CheckSrcMac)(UCHAR * ucSrcMacAddr);
    METHOD_(ULONG, pfETHARP_Guard_Proc_Hook_Register)(ETHARP_GUARD_PROC_HOOK_S * pfHookFunc);
    
    METHOD_(ULONG, pfETHARP_GetPktInfo)(MBUF_S *pstMBuf, ETHARP_PKT_INFO_S *pstEthPktInfo);
    METHOD_(ULONG, pfETHARP_ARPCaptureQue_Save)(MBUF_S *pMBuf, MBUF_QUEUE_S *pstArpPktQue);

    METHOD_(ULONG, pfETHARP_ClearIPConflict)(IFNET_S*  pIf, ULONG ulIpAddr);
};

DECLARE_INTERFACE( IIF_COMP_ETHERNET_ComIntCFG )
{
    IUNKNOWN_METHODS

    /* Methods provided to shell for com init, activate, and module info registration */
    METHOD_( ULONG , pfETHARP_Init_Com ) (COM_ID_INFO_S *pComInfo, ULONG  ulComLen);
    METHOD_( ULONG , pfETHARP_Activate_Com) ();
    METHOD_( ULONG , pfETHARP_SetModuleInfo ) ( ETHARP_MOD_INFO_S *pstMInfo );

    /*以下三个方法用来取ARP表项，从静态到动态，依次遍历*/
    METHOD_( ULONG , pfETHARP_OpenArpEntry ) ( UINTPTR *pulWaitlistHandler);        
    METHOD_( ULONG , pfETHARP_GetArpEntry ) (UINTPTR ulWaitlistHandler, ETHARP_ARPRTENTRY_S *pstArpEntry );            
    METHOD_( ULONG , pfETHARP_CloseObject ) ( UINTPTR ulWaitlistHandler);/*  VISP V100R005   2006-5-9   x43050  */
    
    METHOD_( ULONG , pfETHARP_DeleteARPEntryBySubIndex ) (IFNET_S *pSubIf );                    
    METHOD_( ULONG , pfETHARP_AddStaticARPEntryWithVlan ) (ULONG ulIpAddr , UCHAR ucMacAddr[], USHORT usVID,ULONG ulVrfIndex);                    
    
    /* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-09 */
    METHOD_( ULONG , pfETHARP_DeleteARPEntry ) (ULONG ulIpAddress, ULONG ulScope,ULONG ulVrfIndex );
    /* End:VISP1.7C03 VRF wangchengyang , 2009-02-09 */
    
    METHOD_( ULONG , pfETHARP_ClearStaticARPEntry ) ();                    
    METHOD_( ULONG , pfETHARP_ClearDynamiccARPEntryByInterface ) (ULONG ulIfIndex);                    
    METHOD_( ULONG , pfETHARP_ClearAllARPEntry ) ();                        
    METHOD_( ULONG , pfETHARP_ClearAllDynamicARPEntry ) ();
    
    /* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-09 */
    METHOD_( ULONG , pfETHARP_AddStaticARPEntry ) (ULONG ulIpAddr , UCHAR ucMacAddr[],ULONG ulVrfIndex);     
    
    METHOD_( ULONG , pfETHARP_GetArpEntryByIPAddr ) (ULONG ulIPAddr, ARPINFO_S *pstARPInfo, ULONG ulVrfIndex, ULONG ulFlag);
    /* End:VISP1.7C03 VRF wangchengyang , 2009-02-09 */
    METHOD_( ULONG , pfETHARP_GetArpNum ) (ULONG ulType);
    METHOD_( ULONG , pfETHARP_GetStatInfo)(ULONG ulIfIndex, ETHSTAT_S *pstETHSTAT_S);
    METHOD_( ULONG , pfETHARP_ClearStatInfo)(ULONG ulIfIndex);
    
    /* for optic arp proxy*/
    METHOD_( ULONG, pfSetArpProxy) (ULONG ulIfIndex, ULONG ulFlag, ULONG ulSetYes);

    METHOD_( VOID , pfETHARP_SetDebugSwitch) ( ULONG ulDebugArp, ULONG ulDebugEthernet, ULONG ulAclGroupNum);
    METHOD_( ULONG , pfETHARP_GetDebugSwitch) (ULONG* pulDebugArp, ULONG* pulDebugEthernet, ULONG* pulAclGroupNum);
    METHOD_( ULONG ,pfETHARP_GetMac) (ULONG ulIfIndex, UCHAR *pucMac);
    
    METHOD_( ULONG , pfETHARP_RegShellApi ) ( ETHARP_SHELL_CALLBACK_SET_S *pstCallBkSet);
    METHOD_( ULONG , pfETHARP_SetVlan ) (ULONG ulIfIndex , ULONG ulSetYes);
    METHOD_( ULONG , pfETHARP_GetVlan ) (ULONG ulIfIndex , ULONG *pulVlanFlag);
    METHOD_( ULONG , pfETHARP_SetDhcpflag ) (ULONG ulIfindex , ULONG ulflag);
    METHOD_( ULONG , pfTCPIP_HA_SetEthDbg ) (ULONG ulDbg);
    METHOD_( ULONG , pfETHARP_HA_GetEthDbg ) (ULONG *pulDbg);
    METHOD_( ULONG , pfETHARP_HA_SetVerboseDbg) (ULONG ulDbg);
    METHOD_( ULONG , pfETHARP_HA_GetVerboseDbg) (ULONG *pulDbg);
    METHOD_( VOID  , pfETHARP_HA_DebugOutPut)(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);
    METHOD_(ETHARP_INTERMEDIATE_HOOK_FUNC,pfETHARP_GetOutputIntermediateHook)(VOID);
    METHOD_( ULONG , pfTCPIP_GetVlanHead) (MBUF_S* pstMbuf, ULONG* pulVlanHead);
    METHOD_( ULONG , pfETHARP_GetUserArpStat)(ULONG ulIfIndex, USERARPSTAT_S* pstStat);
    METHOD_( ULONG , pfETHARP_ClearUserArpStat)(ULONG ulIfIndex);

    METHOD_( ULONG , pfETHARP_AddStaticArpWithVlanAndPortIfIndex)(ULONG ulIpAddr,UCHAR ucMacAddr[],USHORT usVID,ULONG ulPortIfIndex);
    METHOD_( ULONG , pfEtharp_FreeDynamicArpWithVlan)(IFNET_S *pVlanIf, USHORT usVlanId);
    METHOD_( ULONG , pfEtharp_FreeAllArpWithVlan)(IFNET_S *pVlanIf, USHORT usVlanId);
    METHOD_( ULONG , pfETHARP_FreeDynamicArpWithPortIfIndex)(IFNET_S *pVlanIf, ULONG ulPortIfIndex);
    METHOD_( ULONG , pfETHARP_FreeAllArpWithVlanAndPortIfIndex)(IFNET_S *pVlanIf, USHORT usVlanId, ULONG ulPortIfIndex);
    METHOD_( ULONG , pfETHARP_PacketDebugInfoForL2VLAN)(MBUF_S *pMBuf, IFNET_S *pIf, ULONG ulDebugEvent);

    METHOD_( ULONG , pfETHARP_ArpFreeBasedOnVlanAndIfIndex)(USHORT usVlan, ULONG ulIfIndex);
    METHOD_( ULONG , pfETHARP_ArpAgeAll)(ULONG ulIfIndex);
    METHOD_( ULONG , pfETHARP_ArpFreeDynamicBasedOnVlanAndOutPort)(USHORT usVlan,ULONG ulIfIndex,ULONG ulVlanif);
    METHOD_( ULONG , pfETHARP_SetArpLogSwitch)(ULONG ulIfIndex, ULONG ulLogSwitch);
    METHOD_( ULONG , pfETHARP_GetArpLogSwitch)(ULONG ulIfIndex, ULONG *pulLogSwitch);
    METHOD_( ULONG , pfETHARP_RegFuncEtharpDealHook)(ULONG ulInOrOut, ULONG ulPriority, ETHARP_INTERMEDIATE_HOOK_FUNC pfHookFunc);
    METHOD_( ULONG , pfETHARP_UnRegFuncEtharpDealHook)(ULONG ulInOrOut, ETHARP_INTERMEDIATE_HOOK_FUNC pfHookFunc);

    METHOD_( ULONG , pfETHARP_SetVlanTag)(ULONG ulIfIndex , ULONG ulVlanTag);
    METHOD_( ULONG , pfETHARP_GetVlanTag)(ULONG ulIfIndex , ULONG *pulVlanTag);
    METHOD_( ULONG , pfETHARP_AddDynamicARPEntry)(ULONG ulIfIndex, UCHAR *pucMacAddr, ULONG ulDstIpAddr);
    METHOD_( ULONG , pfETHARP_AddDynamicARPEntryWithVlan)(ULONG ulIfIndex, UCHAR *pucMacAddr, ULONG ulDstIpAddr, USHORT usVlanid);
    METHOD_( ULONG , pfETHARP_SendArpRequest)(ULONG ulIfIndex, ULONG ulDstIpAddr);
    METHOD_( ULONG , pfETHARP_SetARPExpireTimeByIndex)(ULONG ulTime, ULONG ulIfIndex);
    METHOD_( ULONG , pfETHARP_GetARPExpireTimeByIndex)(ULONG *pulTime, ULONG ulIfIndex);
    METHOD_( ULONG , pfETHARP_SetUnicastARPCount)(ULONG ulCount);
    METHOD_( ULONG , pfETHARP_GetUnicastARPCount)(ULONG *pulCount);
   
    METHOD_( ULONG , pfETHARP_SetARPCapture)(ULONG ulIfIndex, ULONG ulRcvCaptureQueLen, ULONG ulSndCaptureQueLen);
    METHOD_( ULONG , pfETHARP_GetARPCapture)(ULONG ulIfIndex, ULONG *pulRcvCaptureQueLen, ULONG *pulSndCaptureQueLen);
    METHOD_( ULONG , pfETHARP_GetARPCaptureQue)(ULONG ulIfIndex, ULONG *pulRcvQueMbufNum, MBUF_S **ppstRcvMbuf,
                                                ULONG *pulSndQueMbufNum, MBUF_S **ppstSndMbuf);    
    METHOD_( ULONG , pfETHARP_SetArpExpireOffsetTime)(UCHAR ucTime);
    METHOD_( ULONG , pfETHARP_GetArpExpireOffsetTime)(UCHAR *pucTime);
    METHOD_( ULONG , pfETHARP_SetARPExpireTimeByIf)(ULONG ulTime, ULONG ulIfIndex);
    METHOD_( ULONG , pfETHARP_SetARPDetectTimes)( ULONG ulDetectTimes, ULONG ulIfIndex );
};    

DECLARE_INTERFACE( IIF_COMP_ETHERNET_ComIntSSA )
{
    IUNKNOWN_METHODS

    /* Methods provided to shell for functionality purpose */ 
    METHOD_( ULONG , pfETHARP_RegShellApi ) ( ETHARP_SHELL_CALLBACK_SET_S *pstCallBkSet);

};


/* For implement of QuerfyInstance() */
typedef struct tagINT_OBJ_S
{
    IIF_COMP_ETHERNET_ComIntFUN  *pComIntFUN;
    IIF_COMP_ETHERNET_ComIntCFG  *pComIntCFG;
    IIF_COMP_ETHERNET_ComIntSSA  *pComIntSSA;
    IIF_IFS_IntFun  *pComIntIFG;
}ETHERNET_INT_OBJ_S;

#endif


#ifdef  __cplusplus
}
#endif

