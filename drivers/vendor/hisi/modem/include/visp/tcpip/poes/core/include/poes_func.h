/*******************************************************************************
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              poes_func.h
*
* Project Code: VISPV100R006C02
*  Module Name: POES
* Date Created: 2007-07-18
*       Author: lijing(52889)
*  Description: POES模块的所有函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-18   lijing(52889)           Create
*
*******************************************************************************/

#ifndef  _POES_FUNC_H_
#define  _POES_FUNC_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* begin of ipoes.c */
ULONG POES_QueryInterface(IUnknown *This, COMP_IID iid, LPVOID *ppvObj);
/* end of ipoes.c */

/* begin of ipoes_fac.c */
ULONG ImplPOESFactoryQueryInterface(IUnknown *This,COMP_IID iid, LPVOID *ppvObj);
ULONG ImplPOESFactoryCreateInstance(IComponentFactory *This,  COMP_IID iid, VOID **ppvObj );
/* end of ipoes_fac.c */

/* begin of poes_init.c */
ULONG POES_Init_Com(const COM_ID_INFO_S* pstComInfo, ULONG ulComLen);
ULONG POES_Active_Com (VOID);
ULONG POES_SetModuleInfo(POES_MOD_INFO_S *pstMInfo);
ULONG POES_RegShellApi(POES_SHELL_CALLBACK_SET_S *pstShellApi);
/* end of poes_init.c */

/* begin of poes_ifctl.c */
ULONG POES_Enable(ULONG ulEthIfIndex, ULONG ulVTIfIndex);
ULONG POES_Disable(ULONG ulEthIfIndex);
ULONG POES_SetEncapPppoe (POES_SB_S *pstSession);
VOID POES_UnSetEncapPppoe (POES_SB_S *pstSession);
ULONG POES_EtherIoCtl(UINTPTR ulHandle, ULONG ulCmd, CHAR *pcPara);
ULONG POES_PppIoCtl(UINTPTR ulHandle, ULONG ulCmd, CHAR *pcPara);
ULONG POES_VTIsBinded(IFNET_S *pstIf, ULONG *pulEthIfIndex);
ULONG POES_OpenList(UINTPTR *pulPOESWaitListHandle);
ULONG POES_GetPoesCB(UINTPTR ulPOESWaitListHandle, POES_CB_S *pstPoesCb);
ULONG POES_CloseList(UINTPTR ulPOESWaitListHandle);
VOID *POES_GetNextCB(VOID *pCur, VOID **ppNext);
ULONG POES_DelAllSess(ULONG ulEthIfIndex);/*Add by Q62011 for BC3D01354*/
/* end poes_ifctl.c */

/* begin poes_debug.c */
VOID POES_Dbg_NegoPkt(POES_CB_S *pstPoesCb, UCHAR *pucData, ULONG ulTotalDataLength, ULONG ulDirection);
VOID POES_Dbg_DataPkt(POES_SB_S *pstSession, MBUF_S *pstMBuf, ULONG ulDirection);
VOID POES_Dbg_Events(POES_CB_S *pstPoesCb, POES_SB_S *pstSession, CHAR *szString);
VOID POES_Dbg_Errors(POES_CB_S *pstPoesCb, USHORT usSessionId, CHAR *szString);
CHAR *POES_GetInterfaceName(POES_CB_S *pstPoesCb, CHAR *pszIfName, ULONG ulStrLen);
LONG POES_PrintDataToChar(CHAR *pcBuf, UCHAR *pucData, ULONG ulDataLen, LONG ulStrLen);
/* end poes_debug.c */

/* begin poes_cfg.c */
ULONG POES_SetSesLimit(ULONG ulSesLimit);
ULONG POES_SetOurSesLimit (ULONG ulSesLimit);
ULONG POES_SetHisSesLimit(ULONG ulSesLimit);
ULONG POES_SetServiceName(ULONG ulEthIfIndex, CHAR *pszName );
ULONG POES_GetSysCfgInfo (POES_SYS_CFG_INFO_S *pstSysCfgInfo);
ULONG POES_GetIfCfgInfo (ULONG ulEthIfIndex , POES_IF_CFG_INFO_S *pstIfCfgInfo);
ULONG POES_GetHisMacSessions (UCHAR *pucHisMac, USHORT *pusSesNum);
ULONG POES_GetSesStatInfo (ULONG ulEthIfIndex, POES_SESSION_STAT_INFO_S *pstSesStatInfo);
ULONG POES_GetSesInfo(ULONG ulEthIfIndex, USHORT *pusSessionID, POES_SESSION_INFO_S *pstSesInfo);
ULONG POES_GetSesPktStatInfo(ULONG ulEthIfIndex, USHORT *pusSessionID, POES_SES_PKT_STAT_INFO_S *pstPktStatInfo);
ULONG POES_ClearStatInfo(ULONG ulEthIfIndex,ULONG ulType);
VOID POES_ClearPktStatByIf (POES_CB_S *pstPoesCb);
VOID POES_ClearSesStatByIf(POES_CB_S *pstPoesCb);
ULONG POES_SetWarningSwitch(ULONG ulWarnSw);
ULONG POES_GetWarningSwitch(ULONG *pulSwitch);
ULONG POES_SetDbgSwitch(ULONG ulEthIfIndex, ULONG ulType, ULONG ulValue);
ULONG POES_GetDbgSwitch(ULONG ulEthIfIndex, POES_DEBUG_INFO_S *pstDbgInfo);
ULONG TCPIP_ADP_GetACName();

/* end poes_cfg.c */


/*报文处理函数声明 poes_pkctl.c */
extern ULONG POES_Input(MBUF_S *pstMbuf);
extern ULONG POES_SessionOutput (IFNET_S *pstIfEth,UINTPTR ulSesPointer,MBUF_S *pstMbuf);
extern ULONG POES_SessionInput(IFNET_S *pstIf,MBUF_S *pstMbuf,POES_ETHPOE_S *pstHeader);
extern ULONG POES_DropPacket(MBUF_S *pstMBuf,ULONG ulCmd,CHAR *pcData);
extern VOID POES_DiscoveryOutput(POES_SB_S *pstSession,IFNET_S *pstIfEth,MBUF_S *pstMbuf);

/*end 报文处理函数 poes_pkctl.c */

/*POES 协商处理函数 poes_nego.c*/
extern ULONG POES_DiscoveryInput(IFNET_S *pstIfEth,MBUF_S *pstMbuf);

extern ULONG POES_RecvPadi (POES_SB_S **ppstSesInfo,
                    UCHAR *pucResvHeader,
                    ULONG *pulDataLen,
                    POES_ETHPOE_S *pstHeader,
                    POES_CB_S *pstPoesCb);
extern ULONG POES_RecvPadr(POES_CB_S *pstPoesCb,
                      POES_SB_S **ppstSesInfo,
                      UCHAR *pucResvHeader,
                      ULONG *pulDataLen,
                      POES_ETHPOE_S *pstHeader);
extern ULONG POES_RecvPadt(UCHAR *pucData,
                      POES_ETHPOE_S *pstHeader,
                      POES_CB_S *pstPoesCb);
extern ULONG POES_SendPadt(POES_SB_S *pstSession);

extern VOID  POES_FillPPPoEHeader(UCHAR *pucData,
                            POES_SB_S *pstSesInfo,UCHAR ucCode,USHORT usPayLoadLength);
extern ULONG POES_EncapUpdateSession(POES_SB_S *pstSession);
extern POES_SB_S *POES_NewSession(POES_CB_S *pstPoesCb,POES_HIS_MAC_S *pstHisMac);

extern POES_SB_S *POES_FindSession(POES_CB_S *pstPoesCb,POES_ETHPOE_S *pstHeader);

extern VOID POES_DelSession(POES_SB_S *pstSession);

extern USHORT POES_GetFreeSessionId(POES_SB_S *pstSession,POES_CB_S *pstPoesCb);
extern VOID POES_ReleaseSessionId(POES_SB_S *pstSession);
extern POES_HIS_MAC_S *POES_NewHisMacNode(UCHAR *pucMacAddr);
extern VOID POES_DelHisMacNode(POES_HIS_MAC_S *pstHisMac);
extern LONG POES_HisMacValCmp(VOID *pVal,DLL_NODE_S *pstNode);
extern VOID POES_Timer(VOID *pVoid);
extern VOID POES_SessionCleanTimer(POES_CB_S *pstPoesCb);
extern VOID POES_SessionStatTimer(POES_CB_S *pstPoesCb);

/*end poes_nego.c*/
#ifdef __cplusplus
}
#endif

#endif 

