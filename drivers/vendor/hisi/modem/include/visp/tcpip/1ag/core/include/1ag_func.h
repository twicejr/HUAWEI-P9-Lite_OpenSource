/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              1ag_fun.h
*
*  Project Code: VISPV100R007
*   Module Name: 1AG  
*  Date Created: 2008-3-3
*        Author: yebo(62007)
*   Description: 1AG模块公共函数集
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-3-3  yebo(62007)         Create the first version.
*
*******************************************************************************/
#ifndef _1AG_FUN_H
#define _1AG_FUN_H

#ifdef  __cplusplus
    extern "C"{
#endif

/*------------------------------------------------begin 1ag_init------------------------*/
extern ULONG OAM_1AG_Active_Com (VOID);
extern VOID OAM_1AG_DeInit(VOID);
extern ULONG OAM_1AG_Init_Com(VOID);
extern ULONG OAM_1AG_RegShellApi(OAM_1AG_SHELL_CALLBACK_S *pstShellApi);
extern ULONG OAM_1AG_SetModuleInfo(OAM_1AG_MOD_INFO_S *pstMInfo);
/*------------------------------------------------end 1ag_init--------------------------*/

/*---------------------------------------CCM_Func_Begin------------------------------------*/
extern VOID  OAM_1AG_CC_Init(VOID);
extern ULONG OAM_1AG_RcvCcm(MBUF_S *pstMbuf);
extern ULONG OAM_1AG_CheckCcmLoop(USHORT usMepId,ULONG ulIfIndex,ULONG ulMaIndex,UCHAR *ucSMAC);
extern ULONG OAM_1AG_ForwardCcmPacket(ULONG ulIfIndex,UCHAR ucInterfaceTLV,ULONG ulMaIndex,MBUF_S *pstMbuf,OAM_1AG_CCM_UPDATE_INFO_S *pstCcmInfo);
extern ULONG OAM_1AG_SendCCMPacket(VOID * pstMep,ULONG ulSendTLVFlag);
extern ULONG OAM_1AG_UpdateCCMData(ULONG ulIfIndex,UCHAR ucInterfaceTLV,
                                   ULONG ulMaIndex,UCHAR ucMdLevelFlag,
                                   OAM_1AG_CCM_PACKET_S  *pstCcmPacket, OAM_1AG_CCM_UPDATE_INFO_S *pstCcmInfo);
extern ULONG OAM_1AG_DynamicCreateRmep( ULONG  ulIfIndex, UCHAR  ucInterface, ULONG  ulMaIndex, USHORT usRmepId,
                                        UCHAR  ucMdLevelFlag, VOID  *pPrara, OAM_1AG_CCM_UPDATE_INFO_S *pstCcmInfo );
extern ULONG OAM_1AG_ChangeList(ULONG ulType , UCHAR ucOldInterval,UCHAR ucNewInterval,ULONG ulIndex);
extern VOID  OAM_1AG_MepTimerOut(VOID *pPara);
extern VOID  OAM_1AG_CcmSend_Timer(ULONG  ulIndex);
extern VOID  OAM_1AG_RmepTimerOut(VOID *pPara);
extern VOID  OAM_1AG_CcmTimeOut_Timer( ULONG ulIndex);

/*---------------------------------------CCM_Func_End-------------------------------------*/

/* ------------------------------------------lb 开始--------------------------------------*/
extern ULONG  OAM_1AG_LB_Forward(MBUF_S  *pstMbuf,ULONG  ulMaIndex);
extern ULONG  OAM_1AG_LB_Check( MBUF_S *pstMbuf,CHAR   **ppcErrReason);
extern ULONG  OAM_1AG_LB_Distinguish( CHAR *pucLBPacket,ULONG  *ulType);
extern ULONG  OAM_1AG_LB_Encapsulte( MACPINGPARAM_S * pstMacPingParam,UCHAR  *pucLBMPacket,
                                       ULONG *ulSequence, OAM_1AG_MEP_S *pstMep);
extern VOID  OAM_1AG_LB_Init(VOID);
extern ULONG  OAM_1AG_LB_MainProc( MACPINGPARAM_S * pstMacPingParam,ULONG ulExecID);
extern LBRQUE_NODE_S* OAM_1AG_LB_ReadLbr( ULONG   ulsequence);
extern ULONG  OAM_1AG_LB_UserEncapsulate( UCHAR *pucDestMacAddr,ULONG ulIfIndex,ULONG ulMAIndex,
                                       UCHAR *buff,ULONG len ,MBUF_S **ppstMbuf, OAM_1AG_MEP_S *pstMep,
                                       UCHAR ucVlanPri);
extern ULONG  OAM_1AG_LB_UserMainProc( UCHAR *pucDestMacAddr,IFNET_S  *pstIf,ULONG ulMAIndex,
                                       UCHAR *buff,ULONG len,ULONG ulLocalMepIndex, UCHAR ucVlanPri);
extern ULONG  OAM_1AG_RcvLbm( MBUF_S  *pstMbuf);
extern ULONG  OAM_1AG_RcvLbr( MBUF_S  *pstMbuf );

/* ------------------------------------------lb 结束-------------------------------------- */

/* ------------------------------------------lt 开始--------------------------------------*/
extern ULONG OAM_1AG_FindPath(OAM_1AG_LTM_SENDOUTDATA_S* pstLtm);
extern ULONG OAM_1AG_ForwardLtm(MBUF_S *pstMbuf, ULONG ulMaIndex, OAM_1AG_MEP_S* pstMepInfo);
extern ULONG OAM_1AG_ForwardLtr(MBUF_S *pstMbuf, ULONG ulMaIndex, OAM_1AG_MEP_S* pstMepInfo);
extern ULONG OAM_1AG_GetLocalLtm(ULONG ulLtmSendId, OAM_1AG_LTM_SENDOUTDATA_S** ppstLTM);
extern ULONG OAM_1AG_LTM_Free(UCHAR ucFreeLtmIndex);
extern ULONG OAM_1AG_LTM_Insert(OAM_1AG_LTM_SENDOUTDATA_S* pstLtm, UCHAR* pucFreeLtmIndex);
extern ULONG OAM_1AG_LTR_Insert(OAM_1AG_LTR_RECV_S* pstRecvLtr);
extern ULONG OAM_1AG_LT_Init(VOID);
extern ULONG OAM_1AG_LT_MainProc(OAM_1AG_LT_PARA_S* pstLtPara);
extern ULONG OAM_1AG_PrintPath(UCHAR ucLtrIndex, ULONG ulExecID);
extern ULONG OAM_1AG_RcvLtm(MBUF_S *pstMbuf);
extern ULONG OAM_1AG_RcvLtr(MBUF_S *pstMbuf);
extern ULONG OAM_1AG_RcvLtr_Draft7(MBUF_S *pstMbuf);
extern ULONG OAM_1AG_RcvLtr_Std(MBUF_S *pstMbuf);
extern ULONG OAM_1AG_ReplyLtr_Draft7(MBUF_S *pstMbuf, ULONG ulIfIndex);
extern ULONG OAM_1AG_ReplyLtr_Std(MBUF_S *pstMbuf, ULONG ulIfIndex);
extern ULONG OAM_1AG_SendLtm(OAM_1AG_LT_PARA_S* pstLtPara);
extern VOID OAM_1AG_LTRTimer(VOID *pPara);
extern ULONG OAM_1AG_Trace(ULONG ulIfIndex, UCHAR *pcMacAddr, UCHAR * pszMdName, UCHAR * pszMaName, 
                                 USHORT usRmepId, UCHAR ucTtl, USHORT usTimeOut, ULONG ulExecID);

extern ULONG OAM_1AG_ReplyLtr_StdOr1731(MBUF_S *pstMbuf, ULONG ulIfIndex);
/* ------------------------------------------lt 结束-------------------------------------- */

/* ------------------------------------------debug 开始--------------------------------------*/
extern VOID OAM_1AG_ErrDebugPkt(CHAR *pcErrorString,CHAR *pszBuf,ULONG ulLength);
extern VOID  OAM_1AG_Debug_CCM(ULONG ulInOrOut,UCHAR ucInterfaceTLV,OAM_1AG_CCM_PACKET_S  *pstCcmPacket);
extern ULONG  OAM_1AG_Debug_LB( UCHAR *pcLBPacket,ULONG ulLen,ULONG ulDirection);
extern ULONG OAM_1AG_Debug_LTM_Draft7(UCHAR* pszPacket, ULONG ulPacketLen, ULONG ulInOrOut);
extern ULONG OAM_1AG_Debug_LTM_Std(UCHAR* pszPacket, ULONG ulPacketLen, ULONG ulInOrOut);
extern ULONG OAM_1AG_Debug_LTR_Draft7(UCHAR* pszPacket, ULONG ulPacketLen, ULONG ulInOrOut);
extern ULONG OAM_1AG_Debug_LTR_Std(UCHAR* pszPacket, ULONG ulPacketLen, ULONG ulInOrOut);
extern VOID OAM_1AG_VerboseDebugInfo(IFNET_S *pIfnet,CHAR* pcString,ULONG ulLength,ULONG ulInOrOut);
/* ------------------------------------------debug 结束-------------------------------------- */

/* ------------------------------------------func 开始--------------------------------------*/
extern VOID OAM_1AG_CalculateHash(VOID* pKey, ULONG ulKeyLen, ULONG* pulHash);
extern ULONG OAM_1AG_CcInterval2TimeOut(UCHAR ucCcInterval, USHORT* pusTimeOut);
extern ULONG OAM_1AG_CheckMac(UCHAR *pszMac);
extern ULONG OAM_1AG_GetMac(ULONG ulIfIndex, UCHAR *pucMac);
extern ULONG OAM_1AG_GetMaIndex(ULONG ulMdIndex,UCHAR *pszMaName,ULONG *pulMaIndex);
extern ULONG OAM_1AG_GetMaMepWithVIDPlusIfIndex(USHORT VLANID, IFNET_S* pstIfnet, 
                                                        OAM_1AG_MA_S **ppstMaInfo, ULONG *pulMepIndex);
extern ULONG OAM_1AG_GetMdIndexByName(UCHAR *pszMdName,ULONG *pulMdIndex);
extern ULONG OAM_1AG_GetMdMaIndexByName(UCHAR *pszMdName,UCHAR *pszMaName,ULONG *pulMdIndex,ULONG *pulMaIndex);
extern ULONG OAM_1AG_GetMepIndexById(ULONG ulMaIndex,USHORT usMepId,ULONG *pulMepIndex);
extern ULONG OAM_1AG_GetMepIndexByIfIndex(ULONG ulMaIndex,ULONG ulIfIndex,ULONG *pulMepIndex);
extern ULONG OAM_1AG_GetRmepIndexById(ULONG ulIfIndex,ULONG ulMaIndex,USHORT usRmepId,ULONG *pulRmepIndex);
extern ULONG OAM_1AG_GetRmepIndexBymac(UCHAR *pszMac,ULONG ulMaIndex,ULONG *pulRmepIndex);
extern ULONG OAM_1AG_IfDel(ULONG ulIfIndex);
extern ULONG OAM_Y1731_GetMaMepWithVIDPlusMDLevel(USHORT usVlanID, IFNET_S* pstIfNet, UCHAR ucMdLevel, 
                                                            OAM_1AG_MA_S **ppstMaInfo, ULONG *pulMepIndex);
extern ULONG OAM_Y1731_GetMaMepWithVIDPlusMegID(USHORT usVlanID, IFNET_S *pstIfNet, UCHAR* pucMegID,
                                                        OAM_1AG_MA_S **ppstMaInfo, ULONG *pulMepIndex);
extern ULONG OAM_1AG_IsMaExist(ULONG ulMdIndex, UCHAR *pszMaName);

extern ULONG OAM_1AG_Mac2Str(UCHAR *pucMac,UCHAR *pszMacStr);
extern ULONG OAM_1AG_Str2Mac(UCHAR *pStrMac,UCHAR szMac[]);
extern ULONG OAM_1AG_AddTimerList(ULONG ulMepOrRmep, ULONG ulIndex);
extern ULONG OAM_1AG_DeleteTimerList(ULONG ulMepOrRmep, ULONG ulIndex);
extern ULONG OAM_1AG_CheckIfValid(IFNET_S *pstIf);
extern ULONG OAM_1AG_JudgeNameValue(UCHAR* pszMdName, UCHAR* pszMaName);
extern ULONG OAM_1AG_GetRmepStatus(UCHAR* pszMdName,UCHAR* pszMaName, USHORT usRmepId, ULONG* pulStatus);
extern ULONG OAM_1AG_GetPktHeaderInfo(UCHAR * pucPacket, USHORT *pusVlanId, UCHAR **puc1agPktHeader);
extern ULONG OAM_1AG_EthHeader_Encapsulte(UCHAR *pucPacket, UCHAR ucVlanFlag, UCHAR *pucDstMac,
                                               UCHAR *pucSrcMac, USHORT usEthType, USHORT usVlanId, UCHAR ucVlanPri);
extern ULONG OAM_1AG_NoVlanPkt_GetVlanIdByIfIndex(ULONG ulIfIndex, UCHAR ucPktTypeCode,
                                                                UCHAR *pszPktSrcMacAddr, USHORT *pusVlanID, OAM_1AG_MA_S** ppstMa);

/*i1ag.c*/
extern ULONG OAM_1AG_QueryInterface(IUnknown *This, COMP_IID iid, LPVOID *ppvObj);
/*i1ag_fac.c*/
extern ULONG ImplOAM1AGFactoryCreateInstance(IComponentFactory *This,  COMP_IID iid, VOID **ppvObj );
extern ULONG ImplOAM1AGFactoryQueryInterface(IUnknown *This,COMP_IID iid, LPVOID *ppvObj);
/*1ag_pktctl.c*/
extern VOID OAM_1AG_CutTrunkPortVlanHead(MBUF_S* pstMBuf);
extern ULONG OAM_1AG_PktSnd(IFNET_S *pstIfnet,MBUF_S *pstMbuf);
extern ULONG OAM_1AG_RcvPkt(MBUF_S *pstMbuf);

/*1ag_cfg.c*/
extern ULONG  OAM_1AG_ClearHaStat(VOID);
extern ULONG  OAM_1AG_ClearMepStat(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId);
extern ULONG OAM_1AG_CreateMa(UCHAR * pszMdName, UCHAR * pszMaName, ULONG ulVlanId, VOID *pPara, VOID *pstTlvData);
extern ULONG OAM_1AG_CreateMd(UCHAR * pszMdName, UCHAR ucMdLevel);
extern ULONG OAM_1AG_CreateMep(ULONG ulIfIndex, UCHAR* pszMdName, UCHAR* pszMaName, USHORT usMepId,
                                        VOID *pPara, VOID *pstTlvData);
extern ULONG OAM_1AG_CreateRmep(ULONG ulIfIndex, UCHAR *pucMacAddr, UCHAR * pszMdName, UCHAR * pszMaName,
                                   USHORT usRmepId, VOID *pPara, VOID *pstTlvData);
extern ULONG OAM_1AG_DeleteMa(UCHAR * pszMdName, UCHAR * pszMaName, ULONG ulIsBackUp);
extern ULONG OAM_1AG_DeleteMd(UCHAR * pszMdName);
extern ULONG OAM_1AG_DeleteMep(UCHAR* pszMdName, UCHAR* pszMaName, USHORT usMepId, ULONG ulIsBackUp);
extern ULONG OAM_1AG_DeleteAllMepOnIfIndex(ULONG ulIfIndex);
extern ULONG OAM_1AG_DeleteOneMep(UCHAR* pszMdName, ULONG ulMaIndex, USHORT usMepId);
extern ULONG OAM_1AG_DeleteRmep(UCHAR* pszMdName, UCHAR* pszMaName, USHORT usRmepId, ULONG ulIsBackUp);
extern ULONG OAM_1AG_DeleteOneRmep(ULONG ulMaIndex, USHORT usRmepId);
extern ULONG OAM_1AG_EnableCcmSend(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId, UCHAR ucSendFlag);
extern ULONG  OAM_1AG_GetCompatible(UCHAR * pszMdName ,UCHAR *pszMaName,ULONG *pulValue);
extern ULONG  OAM_1AG_GetDebug(ULONG *pul1AgPktDebug,ULONG *pulError1AgPktDebug,ULONG 
                               *pul1AgVerbosePktDebug,ULONG *pulPacketNum,ULONG *pulPacketOctets);
extern ULONG OAM_1AG_GetHaDebug (ULONG *pulValue);
extern ULONG  OAM_1AG_GetHaStat(HA1AGSTAT_S *pstHa1agStat);
extern ULONG  OAM_1AG_GetMaInfo(UCHAR *pszMdName,UCHAR *pszMaName, DISP_MA_INFO_S *pstDispMaInfo);
extern ULONG  OAM_1AG_GetMdInfo(UCHAR *pszMdName, DISP_MD_INFO_S *pstDispMdInfo);
extern ULONG  OAM_1AG_GetMepInfo(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId, 
                                   DISP_MEP_INFO_S * pstDispMepInfo);
extern ULONG  OAM_1AG_GetAllMepInfoById(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId,
                                        DISP_MEP_INFO_LIST_S ** ppstDispMepInfoList);
extern ULONG  OAM_1AG_FreeMepInfoList(DISP_MEP_INFO_LIST_S * pstDispMepInfoList);
extern ULONG  OAM_1AG_GetMepStat(UCHAR *pszMdName,UCHAR * pszMaName, USHORT usMepId, 
                               OAM_1AG_STAT_S *pstOam1agStat);
extern ULONG  OAM_1AG_GetPktType(USHORT *pusEthType, UCHAR *pucPriority);
extern ULONG  OAM_1AG_GlobalDisable(VOID);
extern ULONG OAM_1AG_IsEnable1ag(ULONG ulIfIndex, ULONG* pulIsEnable);
extern ULONG  OAM_1AG_NpNotify(UINTPTR aulMsg[4]);
extern ULONG  OAM_1AG_Ping(ULONG ulIfIndex ,UCHAR *pucMacAddr,UCHAR * pszMdName, 
                               UCHAR * pszMaName, USHORT usRmepId, ULONG ulCount, 
                               USHORT usPacketSize, USHORT usTimeOut,ULONG ulSendInterval,ULONG ulID,
                               UCHAR  ucVlanPri);
extern ULONG OAM_1AG_SetCcmInterval(UCHAR * pszMdName, UCHAR * pszMaName, ULONG ulInterval);
extern ULONG OAM_1AG_SetCompatible(UCHAR * pszMdName ,UCHAR *pszMaName,ULONG ulValue);
extern ULONG OAM_1AG_SetDebug (ULONG ulType,ULONG ulFlag,ULONG ulPacketNum,ULONG ulPacketOctets);
extern ULONG OAM_1AG_SetHaDebug (ULONG ulFlag);
extern ULONG OAM_1AG_SetPktType(USHORT usPktType, UCHAR ucPriority);
extern ULONG OAM_1AG_SetMaVlanPri(UCHAR *pucMdName,UCHAR *pucMaName,UCHAR ucPriority);
extern ULONG  OAM_1AG_UserPing(ULONG ulIfIndex ,UCHAR *pucMacAddr,UCHAR * pszMdName, 
                    UCHAR * pszMaName, USHORT usRmepId, 
                    UCHAR *pBuffer, ULONG ulLen, UCHAR ucVlanPri);
extern ULONG OAM_1AG_SetVersion(ULONG ulIfIndex, ULONG ulVersion, ULONG ulIsTrunkPort);
extern ULONG OAM_1AG_GetVersion(ULONG ulIfIndex, ULONG *pulVersion);
extern ULONG OAM_1AG_SetRcvDefaultVlan(ULONG ulIfIndex, ULONG ulDefaultVlan);
extern ULONG OAM_1AG_GetRcvDefaultVlan(ULONG ulIfIndex, ULONG *pulDefaultVlan);
extern ULONG OAM_1AG_SetRmepCheck(UCHAR* pszMdName, UCHAR* pszMaName, USHORT usRmepId, ULONG ulSetYes, ULONG ulPPIMode);
extern ULONG OAM_1AG_GetRmepCheck(UCHAR* pszMdName, UCHAR* pszMaName, USHORT usRmepId, ULONG *pulSetYes);
extern ULONG OAM_1AG_SetLossDetectInterval(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId, USHORT ulInterval);
extern ULONG OAM_1AG_GetLossDetectInterval(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId, USHORT *pulInterval);
extern ULONG OAM_1AG_GetRmepWarnState(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usRmepId, OAM1AG_WARN_STATE_S* pst1agWarnState);
extern ULONG OAM_1AG_IfStatus(ULONG ulIfIndex,ULONG ulCmd);
/* Add for V2R3C06, by shuxieliu00176784, at 2011-10-04. 修改原因: 支持EOAM协议版本全局设置 */
extern ULONG OAM_1AG_SetGlobalVersion(ULONG ulVersion);
extern ULONG OAM_1AG_GetGlobalVersion(ULONG *pulVersion);
/* Add for V2R3C06, by z00171897/p00193127, at 2011-10-06. 修改原因: 扩展告警类型 */
extern ULONG OAM_1AG_NpNotify_CC(OAM_1AG_NPNOTIFYPARA_S *pstNpNotifyPara);
extern ULONG OAM_Y1731_NpNotify(OAM_1AG_NPNOTIFYPARA_S *pstNpNotifyPara);
/* Add for V2R3C06, by z00187940, at 2011-10-13. 修改原因: 支持AIS 功能 */
extern ULONG OAM_Y1731_EnableAIS(UCHAR *pucMdName,UCHAR *pucMaName,UCHAR ucEnable);
extern ULONG  OAM_1AG_RcvAis(MBUF_S  *pstMbuf);
extern ULONG  OAM_Y1731_AIS_Check( MBUF_S *pstMbuf,CHAR   **ppcErrReason);
extern ULONG  OAM_Y1731_Debug_AIS( UCHAR *pcAisPacket,ULONG ulLen,ULONG ulDirection);
extern VOID OAM_Y1731_AISTimerOut(VOID *pPara);
extern VOID OAM_Y1731_AISTimer(ULONG ulIndex);
extern LONG  OAM_Y1731_fnAISMA(VOID * val, DLL_NODE_S * pNode);
extern ULONG OAM_Y1731_AISChangeList(UCHAR ucOldInterval,UCHAR ucNewInterval,DLL_NODE_S * pstNode);
extern VOID  OAM_Y1731_AIS_Init(VOID);
extern VOID OAM_Y1731_AISWarningProc(UCHAR ucWarnState,  UCHAR ucMdLevel, UCHAR *szMdName , UCHAR *szMaName);
/* Add for V2R3C06, by z00171897/p00193127, at 2011-10-17. 修改原因: 支持Y1731使能/去使性能检测 */
extern ULONG OAM_Y1731_EnablePMCheck(UCHAR *pszMdName, UCHAR *pszMaName, USHORT usMepId, USHORT usRmepId, 
                            UCHAR ucPMType, UCHAR ucCheckFlag, ULONG ulSendInterval, ULONG ulTimeOut);
extern ULONG OAM_Y1731_PMCheck_ProEnable(MEP_PM_INFO_S *pstPMCheck, RMEP_PM_INFO_S *pstRmepPMCheck, USHORT usMepId, USHORT usRmepId, 
                                 ULONG ulSendInterval, ULONG ulTimeOut);
extern ULONG OAM_Y1731_PMCheck_ProDisable(MEP_PM_INFO_S *pstPMCheck, RMEP_PM_INFO_S *pstRmepPMCheck,USHORT usRmepId);
extern ULONG OAM_Y1731_PMCheck_Pro(OAM_1AG_MEP_S *pstMepNode, MEP_PM_INFO_S *pstPMCheck, RMEP_PM_INFO_S *pstRmepPMCheck, USHORT usMepId, 
                            USHORT usRmepId, ULONG ulOprType, UCHAR ucCheckFlag, ULONG ulSendInterval, ULONG ulTimeOut);
extern ULONG OAM_Y1731_GetRmepForPMCheck(ULONG ulIfIndex, ULONG ulMaIndex, USHORT usRmepId, ULONG *pulRmepIndex);
extern ULONG OAM_1AG_DeleteShortMepOnIf(IFNET_S *pstIf, ULONG ulMepIndex);
extern ULONG OAM_1AG_MepVlanCheckOnIf(IFNET_S* pstIfNet, ULONG ulMdLevel, USHORT usVlanId);
/* Modified by likaikun213099, 支持基于RMEP的CCM统计, 2014/10/15   问题单号:DTS2014101504612  */
extern ULONG  OAM_1AG_GetRMepStat(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usRMepId, OAM_1AG_RMEP_STAT_S * pstRMepPkt);
extern ULONG  OAM_1AG_ClearRMepStat(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usRMepId);
/*End of Modified by likaikun213099, 2014/10/15   问题单号:DTS2014101504612  */
/* Modified by likaikun213099, 迭代4检视意见修改, 2014/12/3   问题单号:DTS2014120209605  */
extern ULONG OAM_1AG_GetRmepIndexByComInfo(UCHAR * pszMdName, UCHAR * pszMaName, 
                                                        USHORT usRMepId, ULONG *pulRMepIndex);
/*End of Modified by likaikun213099, 2014/12/3   问题单号:DTS2014120209605  */
/* ------------------------------------------func 结束-------------------------------------- */
#ifdef  __cplusplus
}
#endif

#endif

