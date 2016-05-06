/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trunk_fun.h
*
*  Project Code: VISP V100R006
*   Module Name: Trunk
*  Date Created: 2006-11-27
*        Author: sunmo(44939)
*   Description: Trunk模块的函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*-------------------------------------------------------------------------------
*  2006-11-27  sunmo(44939)     Create the first version.
*
*******************************************************************************/

#ifndef _TRUNK_FUN_H_
#define _TRUNK_FUN_H_

#ifdef __cplusplus
extern "C"{
#endif

/* trunk_api.c */
ULONG TRUNK_AddPort_PT(ULONG ulIfIndex, ULONG ulTrunkId, USHORT usPri);
ULONG TRUNK_AddVPort_PT(ULONG ulIfIndex, ULONG ulTrunkId, USHORT usPri);

ULONG TRUNK_RemovePort_PT(ULONG ulIfIndex);
ULONG TRUNK_GetPortStat_PT(ULONG ulIfIndex, PORT_STAT_INFO_S *pstPortStatInfo);
ULONG TRUNK_ClearPortStatInfo_PT(ULONG ulIfIndex);
ULONG TRUNK_SetDebug_PT(ULONG ulSwitch, ULONG ulValue);
ULONG TRUNK_GetDebug_PT(ULONG *pulLacpPktDbgSw, ULONG *pulOtherPktDbgSw, ULONG *pulFsmDbgSw);
ULONG TRUNK_GetTrunkInfo_PT(ULONG ulTrunkId, TRUNK_INFO_S * pstTrunkInfo);
ULONG TRUNK_GetTrunkIdByIf_PT(ULONG ulIfIndex, ULONG *pulTrunkId);
ULONG TRUNK_SetLacp_PT(ULONG ulIfIndex, ULONG ulValue);
ULONG TRUNK_LACP_SetPeriodMode_PT(ULONG ulIfIndex, ULONG ulValue);
ULONG TRUNK_LACP_GetFsmInfo_PT(ULONG ulIfIndex, LACP_FSM_INFO_S *pstFsmInfo);
ULONG TRUNK_LACP_GetNegoInfo_PT(ULONG ulIfIndex, LACP_NEGO_INFO_S *pstNegoInfo);
USHORT TRUNK_LACP_GetSysPri_PT(VOID);
ULONG TRUNK_Distribute_Hook_Register_PT(TRUNK_DISTRIBUTE_HOOK_FUNC pfTrunkHookFunc);
ULONG TRUNK_JudgeIfType_PT(ULONG ulIfIndex);
/* end of trunk_api.c */

/* itrunk.c */
ULONG TRUNK_QueryInterface(IUnknown *This, COMP_IID iid, LPVOID *ppvObj);
/* end of itrunk.c */

/* itrunk_fac.c */
ULONG ImplTRUNKFactoryQueryInterface(IUnknown *This,COMP_IID iid, LPVOID *ppvObj);
ULONG ImplTRUNKFactoryCreateInstance(IComponentFactory *This,  COMP_IID iid, VOID **ppvObj );
/* end of itrunk_fac.c */

/* trunk_init.c */
ULONG TRUNK_Init_Com(const COM_ID_INFO_S* pstComInfo, ULONG ulComLen);
ULONG TRUNK_Active_Com (VOID);
ULONG TRUNK_SetModuleInfo(TRUNK_MOD_INFO_S *pstMInfo);
ULONG TRUNK_RegShellApi(TRUNK_SHELL_CALLBACK_SET_S *pstShellApi);
/* end of trunk_init.c */

/* trunk_ifctl.c */
ULONG TCPIP_ADP_GetMacAddress(ULONG ulTrunkId, UCHAR* pucMacAddr);
VOID TCPIP_ADP_FreeMacAddress(ULONG ulTrunkId, UCHAR * pucMacAddr);
ULONG TRUNK_AddPortCommon(ULONG ulIfIndex, ULONG ulTrunkId, USHORT usPri, UCHAR ucVirtualAdd);
ULONG TRUNK_AddPort(ULONG ulIfIndex, ULONG ulTrunkId, USHORT usPri);
ULONG TRUNK_AddVPort(ULONG ulIfIndex, ULONG ulTrunkId, USHORT usPri);

ULONG TRUNK_RemovePort(ULONG ulIfIndex);
ULONG TRUNK_PhyInit(IFNET_S *pIf);
ULONG TRUNK_TrunkPhyIOCtl(UINTPTR ulPhyLink, ULONG ulCmdIndex, char *pData);
ULONG TRUNK_PortLinkIOCtl(IFNET_S *pIf, ULONG ulCmd, CHAR * pData);
/* 0-无成员端口, 1-有成员端口, 2-异常返回 */
ULONG TRUNK_IsHavingPort(IFNET_S *pIf);
ULONG TRUNK_FreeBlock(IFNET_S *pIf);
ULONG TRUNK_IsTrunkPort(IFNET_S* pIf);
ULONG TRUNK_PortOutput(MBUF_S* pMBuf);
ULONG TRUNK_GetTrunkId(ULONG ulTrunkId);
ULONG TRUNK_GetTrunkIfByPortIf(ULONG ulPortIfIndex, ULONG *pulTrunkIfIndex);
ULONG TRUNK_RefreshMac(ULONG ulTkId);
ULONG TRUNK_1AG_MultiMac_Update(ULONG ulTkIfIndex, ULONG ulCmd, UCHAR *pucMacMask);
ULONG TRUNK_1AG_MultiMac_UpdateWhenSetVersion(ULONG ulTkIfIndex, UCHAR uc1AGNewVersion);
/* end of trunk_ifctl.c */

/* Trunk_debug.c */
ULONG TRUNK_Debug_LacpPkt(IFNET_S* pIf, VOID* pPacket, ULONG ulInOrOut);
ULONG TRUNK_Debug_OtherPkt(IFNET_S* pIf, VOID* pPacket, ULONG ulLen, ULONG ulInOrOut);
ULONG TRUNK_Debug_FsmTran(IFNET_S* pIf, ULONG ulFsmType, LACP_FSMTRAN_S *pstState);
/* end of Trunk_debug.c */

/* Trunk_cfg.c */
ULONG TRUNK_GetPortStat(ULONG ulIfIndex, PORT_STAT_INFO_S *pstPortStatInfo);
ULONG TRUNK_ClearPortStatInfo(ULONG ulIfIndex);
ULONG TRUNK_SetDebug(ULONG ulSwitch, ULONG ulValue);
ULONG TRUNK_GetDebug(ULONG *pulLacpPktDbgSw, ULONG *pulOtherPktDbgSw, ULONG *pulFsmDbgSw);
ULONG TRUNK_GetTrunkInfo(ULONG ulTrunkId, TRUNK_INFO_S * pstTrunkInfo);
ULONG TRUNK_GetTrunkIdByIf(ULONG ulIfIndex, ULONG *ulTrunkId);
ULONG TRUNK_SetLacp(ULONG ulIfIndex, ULONG ulValue);
ULONG TRUNK_LACP_SetPeriodMode(ULONG ulIfIndex, ULONG ulValue);
ULONG TRUNK_LACP_GetFsmInfo(ULONG ulIfIndex, LACP_FSM_INFO_S *pstFsmInfo);
ULONG TRUNK_LACP_GetNegoInfo(ULONG ulIfIndex, LACP_NEGO_INFO_S *pstNegoInfo);
USHORT TRUNK_LACP_GetSysPri(VOID);
ULONG TRUNK_Distribute_Hook_Register(TRUNK_DISTRIBUTE_HOOK_FUNC pfTrunkHookFunc);
ULONG TRUNK_JudgeIfType(ULONG ulIfIndex);
ULONG TRUNK_SetBfd_Mode(ULONG ulTrunkIfIndex, UCHAR ucValue);
ULONG TRUNK_GetBfd_Mode(ULONG ulTrunkIfIndex, UCHAR *pucValue);
ULONG TRUNK_NegTimerCntProc(ULONG ulFlag);
VOID  TRUNK_NegTimeout_Callback(VOID *pArg);
ULONG TRUNK_GetPortRemoveWarningFlag(ULONG ulIfIndex, UCHAR *pucWarning);
ULONG TRUNK_GetWarningFlagWhenLacpDisable(ULONG ulIfIndex, ULONG *pulRet);
ULONG TRUNK_SetTrunkSysPri(USHORT usSysPri);
ULONG TRUNK_SetTrunkPortPri(ULONG ulIfIndex, USHORT usPri);
ULONG TRUNK_GetTrunkPortPri(ULONG ulIfIndex, USHORT *pusPri);

ULONG TRUNK_SetMode_Check(ULONG ulTrunkId);
ULONG TRUNK_SetTrunkBackupMode(ULONG ulTrunkId, ULONG ulMode);
ULONG TRUNK_GetTrunkBackupMode(ULONG ulTrunkId, ULONG *pulMode);
ULONG TRUNK_SetTrunkMasterPort(ULONG ulTrunkId,ULONG ulIfIndex);
ULONG TRUNK_GetTrunkMasterPort(ULONG ulTrunkId,ULONG *pulIfIndex);
ULONG TRUNK_SetTrunkActiveNum(ULONG ulTrunkId, ULONG ulActiveNum);
ULONG TRUNK_GetTrunkActiveNum(ULONG ulTrunkId, ULONG *pulActiveNum);
ULONG TRUNK_SetTrunkRecoverMode(ULONG ulTrunkId, ULONG ulMode);
ULONG TRUNK_GetTrunkRecoverMode(ULONG ulTrunkId, ULONG *pulMode);
ULONG TRUNK_ActiveNumChangeProcess(ULONG ulTrunkId);

ULONG  TRUNK_SetTrunkSysPriById(ULONG ulTrunkId, USHORT usSysPri);
ULONG  TRUNK_GetTrunkSysPriById(ULONG ulTrunkId, USHORT *pusSysPri);

/* Add by shuxieliu00176784/baiweiqiang00177000, at 2011-06-27. 修改原因: 获取TRUNK成员接口的原始physical地址*/
ULONG TRUNK_GetTrunkPortOriginalMac(ULONG ulIfIndex, UCHAR *pucMac);
/* Add by shuxieliu00176784/baiweiqiang00177000, at 2011-06-27. 修改原因: 设置指定trunk的产品定制策略*/
ULONG TRUNK_SetTrunkProductProcPolicy(ULONG ulTrunkId, ULONG ulPolicy);
/* Add by shuxieliu00176784/baiweiqiang00177000, at 2011-06-27. 修改原因: 对指定trunk进行产品定制策略设置判断*/
ULONG TRUNK_SetPolicy_Check(ULONG ulTrunkId, ULONG ulPolicy);
/* end of Trunk_cfg.c */

/* trunk_fun.c */
ULONG TRUNK_Distribute(IFNET_S* pIf, UINTPTR ulPhyLink, MBUF_S *pMBuf);
ENQUEUE_PF TRUNK_PortCollect(IFNET_S* pIf, MBUF_S *pMBuf);
/* end of trunk_fun.c */

/* trunk_lacp_ctl.c */
VOID TRUNK_LACP_ReceiveEventFromExt(IFNET_S* pIf, ULONG ulCmd, VOID *pData);
VOID TRUNK_LACP_ReceiveEventFromFsm(IFNET_S* pIf, ULONG ulCmd);
ULONG TRUNK_LACP_RefreshTrunkInfo(ULONG ulTrunkId, ULONG ulCmd, IFNET_S *pIf);
ULONG TRUNK_LACP_ReceivePacket(MBUF_S *pMbuf);
ULONG TRUNK_LACP_SendPacket(IFNET_S* pIf);
ULONG TRUNK_LACP_DropPacket(MBUF_S *pMBuf, ULONG ulCmd, CHAR *pcData);
VOID TRUNK_LACP_Timer(VOID* pTemp);
VOID TRUNK_LACP_DealPeriodicTimer (IFNET_S* pIf);
VOID TRUNK_LACP_DealCurWhileTimer(IFNET_S* pIf );
TRUNK_PORT_INFO_S *TRUNK_LACP_GetPortCtl(IFNET_S *pIf);
ULONG TRUNK_GetPortOperKey(IFNET_S *pstPortIf, USHORT *pusOperKey);
ULONG TRUNK_SetPortOperKey(IFNET_S *pstPortIf, USHORT usOperKey);
ULONG TRUNK_SetPortOperKey_InPortNum(IFNET_S *pstPortIf, USHORT usOperKey, ULONG ulPortNum);
ULONG TRUNK_IS_UpPort(ULONG ulTrunkId, ULONG ulIfIndex);
VOID TRUNK_RecordDownReason(IFNET_S *pIf, ULONG ulDownReason);
VOID TRUNK_RecordPartnerParaChange(TRUNK_PORT_INFO_S *pstPortCtl, 
        LACP_NEGO_S *pstPortNegoInfo, LACP_PDU_S *pstLACPDU);

VOID TRUNK_RecordActorParaChange(TRUNK_PORT_INFO_S *pstPortCtl, 
    TRUNK_BASIC_INFO_S *pstTrunkBaseInfo,
    LACP_NEGO_S *pstPortNegoInfo, LACP_PDU_S *pstLACPDU);

/*Added by z00208058/w00207740, TRUNK LACP下移需求开发, 2012/4/25 */
VOID TRUNK_BuildLacpPPIInfo(TRUNK_PORT_INFO_S *pstPortCtl, TRUNK_INFO_TBL_S *pstTrunkInfo, PPI_TRUNK_LACP_S *stTrunkPPI);
VOID TRUNK_LACP_PPI_Update(TRUNK_PORT_INFO_S *pstPortCtl, TRUNK_INFO_TBL_S *pstTrunkInfo, ULONG ulCmd);

BOOL_T Trunk_DropPacket_ParnterMacChange(IFNET_S* pIf, LACP_PDU_S *pstLACPDU);
/* end of trunk_lacp_ctl.c */
/* trunk_ha.c */
VOID TRUNK_HA_TrunkGCfgPack(UCHAR* pucData, const USHORT usOffset, USHORT* usAddLen);
VOID TRUNK_HA_CntTrunkBakLen(ULONG ulTrunkId,USHORT* pusTrunkBakLen);
ULONG TRUNK_HA_TrunkPack(UCHAR* pucData, const USHORT usOffset, ULONG ulTrunkId,USHORT* pusMsgAddLen);
ULONG TRUNK_HA_BatchBackup(VOID);
ULONG TRUNK_HA_RealTimePack(ULONG ulMsgType, VOID* pData);
ULONG TRUNK_HA_OutputMsg(UCHAR * pucData, USHORT usDataLen);
ULONG TRUNK_HA_Trunk_Input(TRUNK_INFO_BAK_S* pstBakTrunkInfo);
VOID TRUNK_HA_PortCntRefresh(TRUNK_PORT_INFO_S* pstTrunkPortInfo,TRUNK_INFO_TBL_S* pstTrunkInfo);
ULONG TRUNK_HA_PortNego_Input(TRUNK_PORT_NEGO_BAK_S *pstTrunkPortNego);
ULONG TRUNK_HA_PortNoNego_Input(TRUNK_PORT_NONEGO_BAK_S *pstTrunkPortNoNego);
ULONG TRUNK_HA_PortAdd_Input(TRUNK_PORTADD_BAK_S* pstTrunkPortAdd);
ULONG TRUNK_HA_PortRemove_Input( ULONG* pulIfIndex);
ULONG TRUNK_HA_PortUp_Input( TRUNK_PORT_NEGO_BAK_S* pstTrunkPortUpBak);
ULONG TRUNK_HA_PortDown_Input( ULONG* pulIfIndex);
ULONG TRUNK_HA_SetNewRef(TRUNK_NEWREFPORT_BAK_S* pstNewRefPort );
ULONG TRUNK_HA_Input(UCHAR * pucData, const USHORT usDataLen);
ULONG TRUNK_HA_Smooth(VOID);
ULONG TCPIP_HA_SetTrunkDbg (ULONG ulDbg);
ULONG TRUNK_HA_GetTrunkDbg (ULONG* pulDbg);
ULONG TRUNK_HA_Clean(VOID);
ULONG TRUNK_HA_SetPassiveMode(ULONG ulTrunkId,ULONG ulPassiveMode);

ULONG TRUNK_HA_SetTrunkVerboseDbg(ULONG ulDbg);
ULONG TRUNK_HA_GetTrunkVerboseDbg(ULONG* pulDbg);
VOID TRUNK_HA_DebugOutPut(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);
extern ULONG TRUNK_VlanCheck_Hook_Register(TRUNK_VLANCHECK_HOOK_FUNC pfTrunkHookFunc);

/* end of trunk_ha.c */
ULONG TRUNK_SetTrunkGateValue(ULONG ulTrunkId,ULONG ulGateValue);
ULONG TRUNK_GetTrunkGateValue(ULONG ulTrunkId,ULONG *pulGateValue);

ULONG TRUNK_NotifyLacpStatus(ULONG ulIfIndex, ULONG ulStatus);
ULONG TRUNK_Set_NegTimeoutWaring(ULONG ulTime);
ULONG TRUNK_Get_NegTimeoutWaring(ULONG *pulTime);


/* if_init.c */
extern VOID TRUNKPORT_PPI_Download_State(IFNET_S *pstPortIf, ULONG ulCmd, VOID* pstTrunkIf);
/* end of if_init.c */

/* tcpip_ppi.c */
extern VOID TCPIP_PPI_LogTrunkPortMsg(ULONG ulRet,
                             IFNET_S *pstPortIf, ULONG ulOprType, IFNET_S *pstTrunkIf);
/* end of tcpip_ppi.c*/

/* trunk_lacp_rx.c */
ULONG TRUNK_LACP_RXMachine(IFNET_S* pIf, LACP_PDU_S *pstLACPDU);
ULONG TRUNK_LACP_RecordDefault(TRUNK_PORT_INFO_S *pstPortCtl);
ULONG TRUNK_LACP_UpdateSelected(TRUNK_PORT_INFO_S *pstPortCtl, LACP_PDU_S *pstLACPDU,
                                            ULONG *pulIsNeedSelected );
ULONG TRUNK_LACP_UpdateNTT(TRUNK_BASIC_INFO_S *pstTrunkBaseInfo,LACP_PDU_S *pstLACPDU );
ULONG TRUNK_LACP_UpdateDefaultSelected( TRUNK_PORT_INFO_S *pstPortCtl );
VOID TRUNK_LACP_RecordPDU(TRUNK_BASIC_INFO_S *pstTrunkBaseInfo, LACP_PDU_S *pstLACPDU );
VOID TRUNK_LACP_StartCurrentWhileTimer(LACP_PORT_FSM_S *pstPortFSMInfo, ULONG ulTimeOutLen);
/* Add for V2R3C07, by z00208058/w00207740, at 2012-4-16. 修改原因: TRUNK LACP下移需求开发 */
VOID TRUNK_LACP_StopCurrentWhileTimer(LACP_PORT_FSM_S *pstPortFSMInfo);

ULONG TRUNK_LACP_RXSetPartnerStateSync_FALSE(TRUNK_PORT_INFO_S *pstPortCtl);
ULONG TRUNK_LACP_RXInit_Operating(TRUNK_PORT_INFO_S *pstPortCtl);
ULONG TRUNK_LACP_RXLacpDisable_Operating(TRUNK_PORT_INFO_S *pstPortCtl);
ULONG TRUNK_LACP_RXExpire_Operating(TRUNK_PORT_INFO_S *pstPortCtl);
ULONG TRUNK_LACP_RXDefault_Operating(TRUNK_PORT_INFO_S *pstPortCtl);
ULONG TRUNK_LACP_RXCurrent_Operating(TRUNK_BASIC_INFO_S *pstTrunkBaseInfo, LACP_PDU_S *pstLACPDU);
ULONG TRUNK_LACP_RXPortDisable_Operating(TRUNK_PORT_INFO_S *pstPortCtl);
ULONG TRUNK_LACP_TransferTo_RXPortDisable(LACP_PORT_FSM_S *pstPortFSMInfo);
ULONG TRUNK_LACP_TransferTo_RXExpire(LACP_PORT_FSM_S *pstPortFSMInfo);
ULONG TRUNK_LACP_TransferTo_RXLacpDisable(LACP_PORT_FSM_S *pstPortFSMInfo);
ULONG TRUNK_LACP_TransferTo_RXInit(LACP_PORT_FSM_S *pstPortFSMInfo);
ULONG TRUNK_LACP_TransferTo_RXDefault(LACP_PORT_FSM_S *pstPortFSMInfo);
ULONG TRUNK_LACP_TransferTo_RXCurrent(LACP_PORT_FSM_S *pstPortFSMInfo);
/*Added by z00208058/w00207740, TRUNK LACP下移需求开发, 2012/4/28 */
ULONG LACP_PPI_UpdatePartenerInfo(TRUNK_BASIC_INFO_S *pstTrunkBaseInfo, LACP_PDU_S *pstLACPDU);
/* end of trunk_lacp_rx.c */

/* trunk_lacp_mux.c */
ULONG TRUNK_LACP_MUXMachine(IFNET_S* pIf);
ULONG TRUNK_LACP_Enable_CollectDistrib(IFNET_S *pIf);
ULONG TRUNK_LACP_Disable_CollectDistrib(IFNET_S *pIf);
ULONG TRUNK_LACP_MUXDisCollect_Operating(TRUNK_PORT_INFO_S *pstPortCtl);
ULONG TRUNK_LACP_MUXAttach_Operating(TRUNK_PORT_INFO_S *pstPortCtl);
ULONG TRUNK_LACP_MUXDetach_Operating(TRUNK_PORT_INFO_S *pstPortCtl);
ULONG TRUNK_LACP_Transferto_MUXDisCollect(LACP_PORT_FSM_S *pstPortFSMInfo);
ULONG TRUNK_LACP_Transferto_MUXDetach(LACP_PORT_FSM_S *pstPortFSMInfo);
ULONG TRUNK_LACP_Transferto_MUXAttach(LACP_PORT_FSM_S *pstPortFSMInfo);
ULONG TRUNK_LACP_Transferto_MUXWaiting(LACP_PORT_FSM_S *pstPortFSMInfo);
VOID TRUNK_LACP_Attach_Mux_toAgg(VOID);
VOID TRUNK_LACP_Detach_Mux_toAgg(VOID);
/* end of trunk_lacp_mux.c */

/* trunk_lacp_ptx.c */
ULONG TRUNK_LACP_PTXMachine(IFNET_S* pIf);
ULONG TRUNK_LACP_StartPeriodicTimer(LACP_PORT_FSM_S *pstPortFSMInfo, ULONG ulTimeOutLen);
ULONG TRUNK_LACP_StopPeriodicTimer(LACP_PORT_FSM_S *pstPortFSMInfo);
ULONG TRUNK_LACP_PTXNoPeriodic_Operating(LACP_PORT_FSM_S *pstPortFSMInfo);
ULONG TRUNK_LACP_PTXFastPeriodic_Operating(LACP_PORT_FSM_S *pstPortFSMInfo);
ULONG TRUNK_LACP_PTXSlowPeriodic_Operating(LACP_PORT_FSM_S *pstPortFSMInfo);
ULONG TRUNK_LACP_PTXPeriodicTx_Operating(IFNET_S *pIf);
ULONG TRUNK_LACP_TransferTo_PTXNoperiodic(LACP_PORT_FSM_S *pstPortFSMInfo);
ULONG TRUNK_LACP_TransferTo_PTXPeriodicTx(LACP_PORT_FSM_S *pstPortFSMInfo);
ULONG TRUNK_LACP_TransferTo_PTXSlowperiodic(LACP_PORT_FSM_S *pstPortFSMInfo);
ULONG TRUNK_LACP_TransferTo_PTXFastperiodic(LACP_PORT_FSM_S *pstPortFSMInfo);
/* end of trunk_lacp_ptx.c */

/* trunk_lacp_tx.c */
ULONG TRUNK_LACP_PDUTX(IFNET_S *pIf);
/* end of trunk_lacp_tx.c */

/* trunk_lacp_sl.c */

ULONG TRUNK_LACP_SelectLogic_BasicCheck(LACP_NEGO_S *pstPortNegoInfo, LACP_PORT_FSM_S *pstPortFSMInfo, TRUNK_INFO_TBL_S *pstTrunkInfo);
ULONG TRUNK_LACP_PortGetCtl(IFNET_S *pIf, TRUNK_PORT_INFO_S **pstPortInfo,
                            LACP_NEGO_S **pstPortNegoInfo, LACP_PORT_FSM_S **pstPortFSMInfo);
ULONG TRUNK_LACP_SelectLogic(ULONG ulTrunkId);
ULONG TRUNK_NOLACP_SelectLogic(ULONG ulTrunkId);
ULONG TRUNK_NOLACP_SelectLogic_InPortNum(ULONG ulTrunkId, ULONG ulPortNum);
ULONG TRUNK_PORT_WarningCheck(TRUNK_WARN_SELECT_PORT_INFO_S astWarnSelectPorts[TRUNK_PORT_MAX_NUM], ULONG ulSelectPortNum, ULONG ulWarnMaxSpeedKey);
ULONG TRUNK_PORT_CheckEndWarning(IFNET_S *pPortIf, TRUNK_PORT_INFO_S *pstPortInfo);
ULONG TRUNK_LACP_SortLinkPriority(TRUNK_LACP_MTON_PORT_INFO_S stMtoNSelectPorts[TRUNK_PORT_MAX_NUM], ULONG ulActiveNum);
ULONG TRUNK_LACP_PriCompare(TRUNK_LACP_MTON_PORT_INFO_S stLink_A, TRUNK_LACP_MTON_PORT_INFO_S stLink_B);
ULONG TRUNK_LACP_ModifyPortIndex(TRUNK_INFO_TBL_S *pstTrunkInfo, IFNET_S *pstPortIf);

/* end of trunk_lacp_sl.c */


/* trunk_hdr.c  */
VOID TRUNK_Health_BatchCheckup(VOID);
ULONG TRUNK_Health_TrunkPack(UCHAR *pucData, USHORT usOffset, ULONG ulTrunkId,
                                              USHORT *pusMsgAddLen, USHORT *pusItemAddNum);
VOID TRUNK_Health_CntPackLen(ULONG ulTrunkId, USHORT *pusTrunkPackLen);
ULONG TRUNK_LastWord_BatchCheckup(CHAR *pstBuf, ULONG *pulLastWordLen);
/* Add for V2R3C07, by z00208058/w00207740, at 2012-4-16. 修改原因: TRUNK LACP下移需求开发 */
ULONG TRUNK_LacpExpiredNotify(TRUNK_LACP_NOTIFY_S *pstData);
VOID Trunk_Lacp_DealMsg(UINTPTR aulMsg[4]);
ULONG TRUNK_LACP_PPIUpdateTrunkById(ULONG ulTkId);


/* Modified by likaikun213099, 按AC要求，L2 TRUNK会下发（PPI_TRUNK_IS_PHYUP和PPI_TRUNK_IS_PHYDOWN）的PPI，
不用编译宏控制，但是结果没有下发, 2014/11/21   问题单号:DTS2014112008708 */
/* IFNET是不可裁减组件 */
#define TRUNK_PPI_DOWNLOAD_IFSTATE(pIf, ulIfState)\
if(g_pfTCPIP_PPI_IFNET_Update)\
{\
    ULONG ulPpiRet = VOS_OK;\
    ULONG ulPpiOpr = ulIfState;\
    ULONG ulProtocol = PPI_NETPROTO_LACP;\
    MAKE_NP_STARTDOT(PPI_TYPE_IFNETMSG, ulPpiOpr);/*记录下发前时间点*/\
    ulPpiRet = g_pfTCPIP_PPI_IFNET_Update(pIf->if_ulIfIndex, ulPpiOpr, (VOID *)&ulProtocol);\
    MAKE_NP_ENDDOT(PPI_TYPE_IFNETMSG);/*记录下发后时间点*/\
    TCPIP_PPI_LogIfMsg(ulPpiRet, pIf, ulPpiOpr, (VOID *)&ulProtocol);\
}
/*End of Modified by likaikun213099, 2014/11/21   问题单号:DTS2014112008708 */

/* end of trunk_hdr.c */

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _TRUNK_FUN_H_ */

