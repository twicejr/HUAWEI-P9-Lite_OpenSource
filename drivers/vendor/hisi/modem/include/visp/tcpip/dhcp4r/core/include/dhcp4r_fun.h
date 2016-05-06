/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4r_fun.h
*
*  Project Code: VISPV1R6
*   Module Name: DHCP4R  
*  Date Created: 2007-7-23
*        Author: LY(57500)
*   Description: dhcp4r模块的函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2007-7-23  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _DHCP4R_FUN_H_
#define _DHCP4R_FUN_H_

#ifdef __cplusplus
extern "C"{
#endif

/* idhcp4r_fac.c */
ULONG ImplDHCP4RFactoryQueryInterface(IUnknown *This,COMP_IID iid, LPVOID *ppvObj);
ULONG ImplDHCP4RFactoryCreateInstance(IComponentFactory *This,  COMP_IID iid, VOID **ppvObj);

/* idhcp4r.c*/
ULONG DHCP4R_QueryInterface(IUnknown *This, COMP_IID iid, LPVOID *ppvObj);

/* dhcp4r_init.c */
ULONG DHCP4R_Init_Com(const COM_ID_INFO_S* pstComInfo, ULONG ulComLen);
ULONG DHCP4R_Active_Com(VOID);
VOID  DHCP4R_SetTaskId(ULONG ulTask);
ULONG DHCP4R_SetModuleInfo(DHCP4R_MOD_INFO_S *pstMInfo);
ULONG DHCP4R_RegShellApi(DHCP4R_SHELL_CALLBACK_SET_S *pstShellApi);

/* dhcp4r_sh_init.c */
VOID DHCP4R_SH_TaskEntry(UINTPTR ulArg0, UINTPTR ulArg1, UINTPTR ulArg2, UINTPTR ulArg3);
ULONG DHCP4R_SH_Init(VOID);
VOID DHCP4R_SH_DeInit(VOID);
VOID DHCP4R_Debug_Info(CHAR* szString);
ULONG DHCP4R_RegApp(VOID);

/* dhcp4r_cfg.h */
ULONG DHCP4R_CheckIfValid(ULONG ulIndex);
LONG DHCP4R_fnCfgIndexCmp(VOID * val, DLL_NODE_S * pNode);
LONG DHCP4R_fnDbgIndexCmp(VOID * val, DLL_NODE_S * pNode);
ULONG DHCP4R_RelayEnable(ULONG ulIndex, ULONG ulSetYes);
ULONG DHCP4R_CfgServer(ULONG ulOperate, ULONG ulIndex, ULONG ulServerIP);
ULONG DHCP4R_CfgOption82(ULONG ulOperate, ULONG ulIndex, ULONG ulSubCode, ULONG ulSubLen, UCHAR *szSubVar);
ULONG DHCP4R_GetCfg(ULONG ulIndex, DHCP4R_CFG_INFO_S *pstDHCP4RCfg);
ULONG DHCP4R_SetDebug(ULONG ulOperate, ULONG ulIndex, ULONG ulDebugLevel);
ULONG DHCP4R_GetDebug(ULONG ulIndex, ULONG *pulDebug);
ULONG DHCP4R_SetFwdMode(ULONG ulFwdMode);
ULONG DHCP4R_GetFwdMode(ULONG *pulMode);
ULONG DHCP4R_SetMaxHops(ULONG ulhops);
ULONG DHCP4R_GetMaxHops(ULONG *pulhops);
ULONG DHCP4R_SetTos(UCHAR ucTos);
ULONG DHCP4R_GetTos(UCHAR *pucTos);
ULONG DHCP4R_GetStatistics(DHCP4R_STATINFO_S *pstDHCP4RStat);
VOID  DHCP4R_ClearStatistics(VOID);
VOID *DHCP4R_GetNext(VOID *pCur, VOID **ppNext);
ULONG DHCP4R_OpenEntryByVrf(ULONG ulVrfIndex, UINTPTR *pulWaitListHandle);
ULONG DHCP4R_GetEntryByVrf(ULONG ulVrfIndex, UINTPTR ulEntryWaitList, DHCP4R_CFG_NODE_S *pstDhcp4rCfgNode);
ULONG DHCP4R_CloseObject (UINTPTR ulWaitListHandle);
VOID  DHCP4R_IfDel(ULONG ulVrfIndex,ULONG ulIfIndex);
ULONG DHCP4R_Notify_IfDelete(ULONG ulIfIndex);
ULONG DHCP4R_Notify_VRFDelete(ULONG ulVrfIndex);
ULONG DHCP4R_Cfg_Judge(ULONG ulIfIndex);
ULONG DHCP4R_NoCfgAll(VOID);
VOID  DHCP4R_Show_CfgAll(VOID);

/* dhcp4r_main.c */
VOID  DHCP4R_TaskMain(VOID);
ULONG DHCP4R_DealPacket(LONG lSockFd, DHCP4C_PACKET_S *pstDhcpPkt, ULONG ulRecLen);
VOID  DHCP4R_RelayRequest(ULONG ulVrfIndex,LONG lSockFd, DHCP4C_PACKET_S *pstDhcpRequst, ULONG ulRecLen, USHORT usVlanInfo);
VOID  DHCP4R_RelayReply(ULONG ulVrfIndex, LONG lSockFd, DHCP4C_PACKET_S *pstDhcpReply, ULONG ulRecLen);
ULONG DHCP4R_Add_82Option(ULONG ulVrfIndex, DHCP4C_PACKET_S *pstDhcpRequst, 
                        ULONG ulRecLen,  ULONG ulOpt82Mode,
                        DHCP4R_OPTION82_S *pstDhcp4r82, LONG *plOp82Len);
ULONG DHCP4R_Strip_82Option(DHCP4C_PACKET_S *pstDhcpReply, ULONG ulRecLen,
                        DHCP4R_OPTION82_S *pstDhcp4r82, ULONG *pulOp82Len);
ULONG DHCP4R_GetMsgType(DHCP4C_PACKET_S *pstDhcpPkt, ULONG ulDataLen);
ULONG DHCP4R_ReadOverloadOption(UCHAR *pucOptRead, ULONG ulDataLen);
ULONG DHCP4R_CreateSocket(LONG *lRelaySocket);
ULONG DHCP4R_Notify_CreateSocket(VOID);
VOID  DHCP4R_Incr_StatisticByVrf(ULONG ulVrfIndex,ULONG ulMsgType);

/* dhcp4r_ha.c */
VOID  DHCP4R_HA_CntCfgBakLen(DHCP4R_CFG_NODE_S *pstDhcp4rCfg, ULONG *pulBakLen);
ULONG DHCP4R_HA_CfgPack(UCHAR* pucData, ULONG ulOffset, DHCP4R_CFG_NODE_S *pstDhcp4rCfg, ULONG* pulMsgAddLen);
ULONG DHCP4R_HA_BatchBackup(VOID);
ULONG DHCP4R_HA_RealTimePack(ULONG ulMsgType, VOID *pData);
ULONG DHCP4R_HA_OutputMsg(UCHAR * pucData, ULONG ulDataLen);
ULONG DHCP4R_HA_Input(UCHAR * pucData, ULONG ulDataLen);
ULONG DHCP4R_HA_Restore (UCHAR * pucData, ULONG ulDataLen);
ULONG DHCP4R_HA_Smooth(VOID);    
ULONG TCPIP_HA_SetDHCP4RDbg(ULONG ulDbg);
ULONG DHCP4R_HA_GetDHCP4RDbg(ULONG* pulDbg);
ULONG DHCP4R_HA_SetDHCP4RVerboseDbg(ULONG ulDbg);
ULONG DHCP4R_HA_GetDHCP4RVerboseDbg(ULONG* pulDbg);
VOID  DHCP4R_HA_DebugOutPut(UCHAR *pucBuf, ULONG ulMsgLen, ULONG ulCmd); 
ULONG DHCP4R_HA_Clean(VOID);
ULONG DHCP4R_HA_CfgPktByVrf(ULONG ulVrfIndex, UCHAR* pucData, ULONG ulOffset, 
                            DHCP4R_CFG_NODE_S *pstDhcp4rCfg, ULONG *pulMsgAddLen);

/* dhcp4r_debug.c */
VOID DHCP4R_DebugPacket(ULONG ulVrfIndex,DHCP4C_PACKET_S *pstDhcprHead, ULONG ulPacketLen, ULONG ulPktType,
                        ULONG ulTxRx, ULONG ulIfIndex, ULONG ulDstIP);
VOID DHCP4R_DebugOption82(ULONG ulVrfIndex,DHCP4R_OPTION82_S *pstDhcp82, ULONG ulAddStrip, ULONG ulIfIndex);
VOID DHCP4R_DebugError(CHAR* szErrInfo, ULONG ulVrfIndex, ULONG ulIfIndex);

BOOL_T DHCP4R_IsValidVRFIndex(ULONG ulVRFIndex);
ULONG DHCP4R_CheckVrfIfValid(ULONG ulVrfIndex, ULONG ulIfIndex);
ULONG DHCP4R_GetCfgModeByIf(ULONG ulVrfIndex, ULONG ulIfIndex, ULONG *pulRelayCfgMode);
DHCP4R_CFG_VRF_S * DHCP4R_CreateVrfRelay(ULONG ulVrfIndex);
ULONG DHCP4R_RelayEnableByVrf(ULONG ulVrfIndex, ULONG ulIfIndex, ULONG ulEnable);
ULONG DHCP4R_CfgServerByVrf(ULONG ulVrfIndex, ULONG ulOperate, ULONG ulIfIndex, ULONG ulServerIP);
ULONG DHCP4R_CfgOption82ByVrf(ULONG ulVrfIndex, ULONG ulOperate, ULONG ulIfIndex, 
                              ULONG ulSubCode, ULONG ulSubLen, UCHAR *szSubVar);
ULONG DHCP4R_GetCfgByVrf(ULONG ulVrfIndex,ULONG ulIfIndex, DHCP4R_CFG_INFO_S *pstDHCP4RCfg);
ULONG DHCP4R_SetFwdModeByVrf(ULONG ulVrfIndex, ULONG ulFwdMode);
ULONG DHCP4R_GetFwdModeByVrf(ULONG ulVrfIndex, ULONG *pulFwdMode);
ULONG DHCP4R_GetStatisticsByVrf(ULONG ulVrfIndex, DHCP4R_STATINFO_S *pstDHCP4RStat);
VOID  DHCP4R_ClearStatisticsByVrf(ULONG ulVrfIndex);
ULONG DHCP4R_SetMaxHopsByVrf(ULONG ulVrfIndex, ULONG ulMaxHops);
ULONG DHCP4R_GetMaxHopsByVrf(ULONG ulVrfIndex, ULONG *pulMaxHops);
ULONG DHCP4R_SetTosByVrf(ULONG ulVrfIndex, UCHAR ucTos);
ULONG DHCP4R_GetTosByVrf(ULONG ulVrfIndex, UCHAR *pucTos);
ULONG DHCP4R_SetDebugByVrf(ULONG ulVrfIndex, ULONG ulOperate, ULONG ulIfIndex, ULONG ulDebugLevel);
ULONG DHCP4R_GetDebugByVrf(ULONG ulVrfIndex, ULONG ulIfIndex, ULONG *pulDbgLevel);
VOID  DHCP4R_DeleteVrfRelay(ULONG ulVrfIndex, ULONG ulIfIndex);
VOID  DHCP4R_DeleteVrfDebug(ULONG ulVrfIndex, ULONG ulIfIndex);
ULONG DHCP4R_VRFDel(ULONG ulVrfIndex);
ULONG DHCP4R_SetVrfComCfgInfo(ULONG ulVrfIndex, ULONG ulFwdMode, ULONG ulMaxHops, UCHAR ucTos);
ULONG DHCP4R_SetOpt82ModeByVrf(ULONG ulVrfIndex, ULONG ulIfIndex, ULONG ulMode);
ULONG DHCP4R_GetOpt82ModeByVrf(ULONG ulVrfIndex, ULONG ulIfIndex, ULONG 
*pulMode);
/*ULONG DHCP4R_RequesePro(ULONG ulVrfIndex, DHCP4C_PACKET_S *pstDhcpRequst, ULONG ulSvrIp, ULONG ulIfIndex);*/
ULONG DHCP4R_RequestSend(LONG lSockFd, ULONG ulVrfIndex, DHCP4C_PACKET_S *pstDhcpRequst, 
                                    ULONG ulRecLen, ULONG ulSvrIp, ULONG ulIfIndex);
ULONG DHCP4R_RequestProc(LONG lSockFd, ULONG ulVrfIndex, DHCP4C_PACKET_S *pstDhcpRequst, 
                                    ULONG ulRecLen,ULONG ulSvrIp, ULONG ulIfIndex, USHORT usVlanInfo);
ULONG DHCP4R_GetPortSwitch(VOID);
ULONG DHCP4R_CloseSocket(LONG lRelaySocket);
ULONG DHCP4R_Notify_CloseSocket(VOID);
VOID DHCP4R_CheckToCreateSocket(VOID);
VOID DHCP4R_CheckToCloseSocket(VOID);

#ifdef __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _DHCP4R_FUN_H_ */

