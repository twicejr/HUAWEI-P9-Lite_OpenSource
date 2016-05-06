/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         IF_FUNC.H
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2000/02/28 
 *        Author: yuanjie
 *   Description: Ifnet功能函数头文件
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2000/02/28      yuanjie         Create
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *
 ************************************************************************/

#ifndef _TCPIP_IF_FUNC_H_
#define _TCPIP_IF_FUNC_H_

#ifdef  __cplusplus
extern "C"{
#endif

/************************************************************************
 * 请在这里填写该头文件的具体内容                                       *
 ************************************************************************/


/*  DEFINE IN IF_INDEX.C  ************************************************/
extern ULONG  IF_DelFromIndex (IFNET_S* pIf);
extern ULONG IF_InitIfIndex(VOID);
extern ULONG IF_GetSlotByIndex(ULONG ulIfIndex);
extern ULONG IF_AddToIndex(IFNET_S *);
extern IFNET_S * IF_GetIfByIndex(ULONG);
extern ULONG IF_GetLineProtoByIndex(ULONG ulIfIndex);
extern ULONG IF_DelFromVAIndex(ULONG ulIfIndex);
extern ULONG IF_CloneIndex(IFNET_S *, ULONG);
extern ULONG IO_IF_AddVAToIndex ( IFNET_S *pIf);
extern ULONG IF_InitVAIfIndexState(ULONG ulVTNO);
extern ULONG IF_GetVAIndex(ULONG ulVTNO, ULONG* pulIndex);
extern VOID IF_DelMaxIndex( ULONG , ULONG ) ;


/************************************************************************/


/*  DEFINE IN IF_FIND.C  ************************************************/

extern IFNET_S * IF_FindFirstSubIfnet(IFNET_S * pMain);
extern IFNET_S * IF_FindNextSubIfnet(IFNET_S * pSub);
extern IFNET_S * IF_FindSubIfWithName ( CHAR * );
extern IFNET_S * IF_FindWithMainName ( CHAR * );
extern IFNET_S * IF_FindWithSubIndex ( IFNET_S * , ULONG );
extern IFNET_S * IF_SearchIfFromChain( IFNET_S * pIf , ULONG ulSearch ) ;
extern IFNET_S * IF_SearchIfFromChainFun( IFNET_S * pIf , ULONG ulSearch ) ;

/************************************************************************/


/*  DEFINE IN IF_FUNC.C  ************************************************/
extern VOID IF_AddToConfigLink(IFNET_S *,IFNET_S *,CHAR *);
extern VOID IF_DelFromConfigLink(IFNET_S *,IFNET_S *);
extern ULONG IF_LinkUpIOCtl(ULONG ,IFNET_S *,ULONG ,CHAR * );
extern ULONG IF_NeedToProcessPhyCmd(IFNET_S* pIf, ULONG ulCmd);
extern ULONG IF_LinkIOCtl(IFNET_S *pIf, ULONG ulCmd, CHAR * pData );
extern ULONG IF_Output(MBUF_S *);
extern ULONG IF_VT_Output(MBUF_S *);
/*VRPV3R001M07_IFNET_XHZ_BEG for R.FUNC.IFNET.014 支持standby操作*/
extern ULONG IF_SubShutdown(IFNET_S *);
extern ULONG IF_SubNoShutdown(IFNET_S *);
extern ULONG IF_Shutdown(IFNET_S *);
extern ULONG IF_NoShutdown(IFNET_S *);
/*VRPV3R001M07_IFNET_XHZ_END for R.FUNC.IFNET.010 创建pri-group时隙捆绑接口*/
extern ULONG IF_Delete(IFNET_S *);
extern ULONG IF_IsIfSupportEncap(IFNET_S*,ULONG );
extern ULONG IF_IsEthernetType(ULONG ulIndex);
extern LONG IF_DeleteSonLink(IFNET_S* pIf);
extern LONG IF_DeleteSubLink(IFNET_S* pIf);
extern LONG IF_FreeLinkControlBlock(IFNET_S* pIf);
extern LONG IF_FreeThisIf(IFNET_S* pIf);
extern LONG IF_JudgeNameOrder(CHAR * Sour,CHAR * if_pName);
extern LONG IF_IsSameBoard(ULONG);


extern LONG IsDigit( CHAR temp );
extern LONG atoulp(CHAR **Sour,ULONG * pTemp,ULONG ulLower,ULONG ulUpper);
//extern VOID ultoa(ULONG Value,CHAR *szDest,ULONG Radix);
extern LONG atoul(CHAR *Sour,ULONG * pTemp);
extern LONG Split(CHAR **Sour,CHAR *Dest,CHAR flag,LONG Len);
/************************************************************************/
extern ULONG IF_DefaultTransmit(IFNET_S *pIf, UINTPTR ulPhyLink, MBUF_S *pMBuf);
extern ULONG IF_L2TrunkDefaultTransmit(IFNET_S *pIf, UINTPTR ulPhyLink, MBUF_S *pMBuf);
extern ULONG IF_DefaultTransmitDone(IFNET_S *pIf, UINTPTR ulPhyLink, MBUF_S *pMBuf);
extern ULONG IF_LinkIOCtl(IFNET_S *pIf, ULONG ulCmd, CHAR * pData );

extern ENQUEUE_PF IF_BlackHoleReceived(IFNET_S *,MBUF_S * );
extern ULONG IF_BlackHoleOutput(MBUF_S *);
extern ULONG IF_BlackHoleTransmit(ULONG,MBUF_S *);
extern ULONG IF_BlackHoleLinkDownIOCtl(IFNET_S *pIf,ULONG ulCmd,CHAR * pData);
extern ULONG IF_BlackHoleIOCtlFn( ULONG ulProtocol,IFNET_S*,ULONG ,CHAR * );
extern ULONG IF_BlackHoleLinkIOCtlFn(IFNET_S* pIf,ULONG ulCmd,CHAR * pData);

extern ULONG IF_BlackHolePhyIOCtlFn(ULONG ulProtocol,ULONG ulCmd,CHAR * pData);

extern ULONG IF_EnDropQueue(MBUF_S *);
extern IFNET_S * IF_GetIfByFullName(CHAR * ) ;
extern UINTPTR IF_GetIfByStName(IFNAME_S * pstIfName);

extern ULONG IF_IsTempIf( ULONG ulIndex );
extern ULONG IF_IsTempIfByPtr( IFNET_S *pIf );
extern DEVLINK_S * IF_FindDevByName(DEVLINK_S *,CHAR *);
extern DEVLINK_S * IF_FindDevByIfIndex(DEVLINK_S *pstDevLink, ULONG ulIfIndex);

extern ULONG VLINK_If_NotifyRouter(IFNET_S *, ULONG, UINTPTR );

extern ULONG IF_AfterEncap( IFNET_S *pIf , ULONG ulShutdown ) ;
extern ULONG IF_BeforeEncap( IFNET_S *pIf , ULONG *ulShutdown, ULONG ulExecID, ULONG ulNewProtocol) ;
extern VOID IF_EncapSub(IFNET_S * pMainIf, IFNET_S * pSubIf) ;

extern VOID * IF_WaitListGet( VOID *pParam,VOID **pNewParam ) ;

extern ULONG IF_ResetVTMTU(IFNET_S * pIf);

extern ULONG IF_GetKeepAliveValue( IFNET_S* pIf, ULONG* pValue );

extern IFNET_S* IF_GetConfigHead( );

extern ULONG IF_IsConfigure(IFNET_S * ) ;

extern ULONG IF_IsVisible(IFNET_S * ) ;

extern ULONG IF_DeleteVA( IFNET_S* pIf );

extern ULONG IF_GetIfLineState(IFNET_S *pstIf, ULONG *pulIfState);

extern ULONG IF_GetSlotByIfname(IFNAME_S * pstIfName);

extern ULONG IF_GetIfNumByIfname(IFNAME_S * pstIfName);

extern VOID IF_SetLastChangeTime( IFNET_S * pIf );

extern IFNET_S * IF_CreateByDev_PT( DEVLINK_S * pstDev ,ULONG ulIndex);
extern IFNET_S * IF_CreateByDevForPort( DEVLINK_S * pstDev ,ULONG ulIndex, ULONG ulL2Flag);
extern IFNET_S * IF_CreateByDevCommon( DEVLINK_S * pstDev ,ULONG ulIndex, ULONG ulL2Flag);

extern ULONG IF_Delete_PT( IFNET_S *pIf );
extern ULONG IF_Shutdown_PT( IFNET_S *pIf );
extern ULONG IF_NoShutdown_PT(IFNET_S *pIf);
extern ULONG IF_LinkIoCtl (ULONG ulIfIndex, ULONG ulCmdIndex, CHAR *pData);
extern ULONG IF_Received (ULONG ulIfIndex, MBUF_S * pMBuf);
extern ULONG IF_OpenIfConfigEntry(UINTPTR *pulWaitListHandle);
extern ULONG IF_GetIfConfigEntry(UINTPTR ulEntryWaitList, IFNET_S * pstIfConfig);
extern ULONG IF_CloseIfConfigEntry(UINTPTR ulWaitListHandle); /*VISP V100R005   x43050 2006-5-9 Interface Check  */
extern ULONG IF_OpenIfConfigEntry_PT(UINTPTR *pulWaitListHandle);
extern ULONG IF_GetIfConfigEntry_PT(UINTPTR ulEntryWaitList, IFNET_S * pstIfConfig);
extern ULONG IF_IsTrunkPort(IFNET_S* pIf);
extern ULONG IF_RegisterVlanCheck(IF_VLANCHECKFN pfVlanCheck);
extern ULONG IF_VTIsBinded(IFNET_S *pstIf, ULONG *pulEthIndex);
extern ULONG IF_LinkInput(MBUF_S *pstMbuf); 
extern ULONG IF_GetIfFullNameByIndex(ULONG ulIfIndex, CHAR *pszIfName);
extern ULONG IF_GetIfIndexByFullName(CHAR *pszIfName, ULONG *pulIfIndex);
extern VOID IF_DealIoCtlMsgs(UINTPTR aulMsg[4]);

extern ULONG IF_SetIsisFlag_PT( ULONG ulIfIndex ,ULONG ulFlag );
extern ULONG IF_GetIsisFlag_PT( ULONG ulIfIndex ,ULONG *pulFlag );
extern ULONG IF_Is_3Dim();
extern ULONG IF_Is_Central_3Dim();
extern ULONG IF_Is_Distribute_3Dim();
extern ULONG IF_VirtualInterfaceOutput(MBUF_S * pMBuf);
extern VOID IF_DeletePppVlinkRoute(IFNET_S *pstIf);
extern VOID IF_DeleteVirtualDhcpcInfo(IFNET_S *pstIf);
extern TCPIP_GETVIADDR_HOOK_FUNC g_pfGetVIAddrHook;

extern ULONG IF_QosTransmitDoneHook(IFNET_S *pstIf, ULONG ulPhyLink, MBUF_S *pMBuf);
extern ULONG IF_QosTransmitHook(IFNET_S *pstIf, ULONG ulPhyLink, MBUF_S *pMBuf);

extern ULONG IF_SetDevLink(DEVLINK_S *pstDevLink);
extern ULONG IF_GetDevLink(ULONG ulIfIndex, DEVLINK_S *pstDevLink);

extern ULONG IF_SetIfEventDebugSwitch(ULONG ulValue);
extern ULONG IF_GetIfEventDebugSwitch(ULONG *pulValue);

ULONG TCPIP_GetCrossVIAddr(VOID);

extern ULONG IF_IsIpcInteface(ULONG ulIndex);
extern ULONG IF_IpcCheckByName(CHAR * szName);
extern ULONG IF_PhyIoCtrl(IFNET_S *pstIf, ULONG ulCmd, CHAR *pszData);

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
extern ULONG IF_GetVrfByIfIndex( ULONG ulIndex, ULONG * pVrfIndex);
extern VOID IF_CreateBasicIfNetByVrf( ULONG ulVrfIndex );
extern VOID IF_DeleteBasicIfNetByVrf( ULONG ulVrfIndex );
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
extern ULONG IF_IsRecognisePhyIf(ULONG ulIfIndex);

extern ULONG IF_GetISIStatus(ULONG ulIfIndex, ULONG *pulIfState);
extern ULONG IF_GetIfNum(ULONG *pulIfNum);
extern ULONG IF_GetAllIfIndex(ULONG *pulIfNum, ULONG *pulIfIndex);
extern VOID IF_SetNoPhyShutdown(IFNET_S *pstIfnet);
extern VOID IF_GetInLoopBackName(IFNET_S *pstIf, CHAR *szInLoopBackName, ULONG ulVrfIndex);

/*Added by apurba for VRF6*/
extern VOID IF_UpdateBasicIfNetByVrf( ULONG ulVrfIndex ,ULONG ulVRFType,ULONG ulOper);
extern ULONG IF_GetVrf6ByIfIndex( ULONG ulIndex, ULONG * pVrfIndex);

extern ULONG IF_GetLoopBackIfIndex(ULONG ulVrfIndex, ULONG *pulIfIndex);

extern ULONG IF_IsEthernetOrTrunk(IFNET_S *pstIfnet);

ULONG IF_GetVrf6FullNameByIndex(CHAR *pszVrfName, ULONG ulVrfIndex);

extern ULONG IF_Tunn_SetTunnelPara(ULONG ulIfIndex, TCPIP_TUNNEL_IF_PPI_S *pstTunnelPPI);
extern ULONG IF_Tunn_GetIfInfoByIfIndex(ULONG ulIfIndex, TCPIP_TUNNEL_IF_PPI_S *pstTunnInfo);
extern ULONG IF_Tunn_ShowIfByName(CHAR *szIfName);
extern ULONG IF_Tunn_DelTunnelPara(ULONG ulIfIndex);
extern VOID IF_Tunn_HA_DebugOutPut(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);
extern ULONG IF_Tunn_HA_BatchBackup(VOID);
extern ULONG IF_Tunn_HA_Input(UCHAR *pBuf,ULONG ulMsgLen);

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif


