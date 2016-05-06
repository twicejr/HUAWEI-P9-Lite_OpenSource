/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              poec_func.h 
 *
 *  Project Code: VISP1.5
 *   Module Name: PPPoE Client
 *  Date Created: 2003-01-11
 *        Author: liuhui
 *   Description: PPPoE Client模块的私有函数说明
 *               
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE             NAME               DESCRIPTION
 *  2003-01-11       liuhui             Create file
 *  2005-09-15       t45114             Modify
 *  2006-03-30       liai               Adjust for D00660
 *  2006/04/21       liai               Adjust for D00865
 *  2007-01-04       f54882             Adjust for A82D10682
 ************************************************************************/

#ifndef  _POEC_FUNC_H_
#define  _POEC_FUNC_H_

#ifdef  __cplusplus
extern "C"{
#endif

#include "tcpip/pppoec/include/tcpip_poec.h"


/* Macro definition for Shell API funciton */
#define PPPOE_Client_DBGOUT_VERBOSE g_stPPPOEClientShellApi.pfPPPOE_Client_DbgOut
#define PPPOE_CLIENT_DBGOUT_EVENT   g_stPPPOEClientShellApi.pfPPPOE_Client_DbgOut
#define PPPOE_CLIENT_DBGOUT_DATA    g_stPPPOEClientShellApi.pfPPPOE_Client_DbgOut
#define PPPOE_CLIENT_DBGOUT_ERROR   g_stPPPOEClientShellApi.pfPPPOE_Client_DbgOut
#define PPPOE_CLIENT_DBGOUT_PACKET  g_stPPPOEClientShellApi.pfPPPOE_Client_DbgOut
#define PPPOE_CLIENT_DBGOUT_GR      g_stPPPOEClientShellApi.pfPPPOE_Client_DbgOut
#define POEC_CFG_ExecOutStr         g_stPPPOEClientShellApi.pfPPPOE_Client_CFG_ExecOutStr
#define POEC_CreateDisTimer         g_stPPPOEClientShellApi.pfPPPOE_Client_CreateDisTimer
#define POEC_CreateIdleTimer        g_stPPPOEClientShellApi.pfPPPOE_Client_CreateIdleTimer
#define POEC_DeleteDisTimer         g_stPPPOEClientShellApi.pfPPPOE_Client_DeleteDisTimer
#define POEC_DeleteIdleTimer        g_stPPPOEClientShellApi.pfPPPOE_Client_DeleteIdleTimer
#define POEC_PauseDisTimer          g_stPPPOEClientShellApi.pfPPPOE_Client_PauseDisTimer
#define POEC_ResumeDisTimer         g_stPPPOEClientShellApi.pfPPPOE_Client_ResumeDisTimer


/*ipoec_api.c*/
ULONG PPPOE_Client_Reset_Session_PT ( ULONG ulPoecIfIndex );
ULONG PPPOE_Client_Reset_All_Session_PT ( VOID );
ULONG PPPOE_Client_GetSesStat_PT ( ULONG ulDialerIfIndex, PPPOECSTAT_S *pstStat );
ULONG PPPOE_Client_ResetSesStat_PT( ULONG ulDialerIfIndex );
ULONG PPPOE_Client_CreatePoecIntf_PT(ULONG *pulPoecIfIndex, ULONG ulPortNo);
ULONG PPPOE_Client_DelPoecIntf_PT(ULONG ulPoecIfIndex);
ULONG PPPOE_Client_StartPoecSession_PT(ULONG ulEthIfIndex, ULONG ulPoecIfIndex);
ULONG PPPOE_Client_StopPoecSession_PT(ULONG ulEthIfIndex, ULONG ulPoecIfIndex);

/*ipoec.c*/
ULONG PPPOE_Client_QueryInterface ( IUnknown *This, COMP_IID iid, LPVOID *ppvObj );



/*ipoec_fac.c*/
ULONG PPPOE_Client_FactoryQueryInterface ( IUnknown *This, COMP_IID iid, LPVOID *ppvObj );
ULONG PPPOE_Client_FactoryCreateInstance ( IComponentFactory *This,  COMP_IID iid, VOID **ppvObj );



/*poec_init.c*/
/*f47854 modify : 函数参数或者返回值类型与函数指针定义不匹配*/
ULONG PPPOE_Client_Init_Com ( COM_ID_INFO_S *pstComInfo, ULONG ulComLen );
ULONG PPPOE_Client_Activate_Com ( VOID );
ULONG PPPOE_Client_SetModuleInfo ( PPPOE_CLIENT_MOD_INFO_S *pstMInfo );
ULONG PPPOE_Client_InitData ( VOID );
ULONG PPPOE_Client_RegShellApi ( PPPOE_CLIENT_SHELL_CALLBACK_S *pstShellApi );

/*poec_intr.c*/
VOID CheckSumAdjust ( UCHAR *chksum, UCHAR *optr, LONG olen, UCHAR *nptr, LONG nlen );

ULONG PPPOE_Client_Input ( MBUF_S *pstMbuf );
ULONG PPPOE_Client_SessionOutput ( PPPOE_C_SESSION_S *pstSession, MBUF_S *pstMbuf );
ULONG  PPPOE_Client_PppIoctl ( UINTPTR ulLinkHandle, ULONG ulCmd, char *pcPara);
ULONG PPPOE_Client_SendPadi ( PPPOE_C_SESSION_S *pstSession );
/*modify by wht06310 for PPP接口整改,2006-05-29*/
ULONG PPPOE_Client_Reset_Session ( ULONG ulPoecIfIndex ); 
ULONG PPPOE_Client_Reset_All_Session ( VOID );
VOID PPPOE_Client_Clear_Intf_Session ( IFNET_S *pstEthIfNet );
ULONG PPPOE_Client_No_Session ( IFNET_S *pstEthIfNet, ULONG ulBundleNumber ); 
ULONG PPPOE_Client_Create_Session ( IFNET_S *pstEthIfNet, ULONG ulBundleNumber, 
                                                ULONG ulIdleTime, UCHAR ucHostUniq, ULONG ulQueueLength); 
ULONG PPPOE_Client_DDR_Send ( MBUF_S *pstMBuf );
VOID PPPOE_Client_DDR_Proc_PoeSession ( IFNET_S *pstDialerIf, UCHAR ucDisc ); 
ULONG PPPoE_Client_IfDelete (ULONG ulIfIndex);

VOID PPPOE_Client_DestroySessions ( VOID *pPoeClientCB );

ULONG PPPOE_Client_GetStatFromSessionInfo ( PPPOE_C_SESSION_S *pstSesInfo, PPPOECSTAT_S *pstSesDispInfo ); 
ULONG PPPOE_Client_GetSesStat ( ULONG ulDialerIfIndex, PPPOECSTAT_S *pstStat );
ULONG PPPOE_Client_ResetSesStat ( ULONG ulDialerIfIndex );
ULONG PPPOE_Client_GetSessionInfo (ULONG ulPoecIfIndex, TCPIP_PPPOE_C_SESSION_S *pstSessionInfo );

ULONG PPPOE_Client_GetFreeNumber ( ULONG ulPortNo);

ULONG PPPOE_Client_SetDialerBundleNum ( ULONG ulCmdSwitch, ULONG ulIfIndex, ULONG ulBundleNumber );
ULONG PPPOE_Client_GetBundleNumFromDialer ( ULONG ulDialerIfIndex );

UINTPTR PPPOE_Client_GetPoecSession ( ULONG ulBundleNumber );
ULONG PPPOE_Client_GetPoecEthIf ( ULONG ulBundleNumber, IFNET_S **ppstEthIf );

VOID PPPOE_Client_CfgDebug ( ETHARP_MTSOFTC_S *pstMT, ULONG ulDebugFlag, UCHAR bSetFlag );
ULONG PPPOE_Client_GetPoecDebugFlag ( VOID );

/*此定义从poec_sh_func.h中移入，modified for D00016 by t45114, 2005/12/01*/
INT32 PrintLineBinAndAscii ( UCHAR *pucData, CHAR *pcPrintBuffer, ULONG ulLen,
                                        INT32 i32BufLen, INT32 i32InputOffset);
INT32 PrintBinAsciiByLine ( UCHAR *pucData, CHAR *pcPrintBuffer, ULONG ulLen, 
                                      INT32 i32BufLen, INT32 i32InputOffset);
INT32 PPPOE_Client_translate_packet ( UCHAR *pucPacket, CHAR *pcBuf,  
                                                      INT32 i32BufLen, INT32 i32InputOffset);
VOID PPPOE_Client_DbgOutVerbose ( MBUF_S *pstMBuf, ULONG ulDirction, IFNET_S *pstEthIf );

ULONG PPPOE_Client_CreatePoecIntf(ULONG *pulPoecIfIndex, ULONG ulPortNo);
ULONG PPPOE_Client_DelPoecIntf(ULONG ulPoecIfIndex);
ULONG PPPOE_Client_StartPoecSession(ULONG ulEthIfIndex, ULONG ulPoecIfIndex);
ULONG PPPOE_Client_StopPoecSession(ULONG ulEthIfIndex, ULONG ulPoecIfIndex);

/*poec_proc.c*/
ULONG PPPOE_Client_SetEncapPPPoE ( PPPOE_C_SESSION_S *pstSession, IFNET_S * pstVAIf );
ULONG PPPOE_Client_Move_Session ( PPPOE_C_SESSION_S *pstSession, DLL_S *pstFrom, DLL_S *pstTo );
PPPOE_C_SESSION_S * PPPOE_Client_Discovery_FindSession ( USHORT usHostUniqValue, 
                                                        PPPOE_ETHER_ADDR_S *pstEthAddr, 
                                                        ULONG ulPackType,
                                                        PPPOE_CLIENT_CB_S *pstPoeClientCB );
PPPOE_C_SESSION_S * PPPOE_Client_Session_FindSession ( USHORT usSessionId, PPPOE_ETHER_ADDR_S *pstEthAddr, 
                                                         PPPOE_CLIENT_CB_S *pstPoeClientCB );
VOID PPPOE_Client_FillPPPoEHeader ( UCHAR *pucData,
                                    PPPOE_C_SESSION_S *pstSession,
                                    UCHAR ucCode,
                                    USHORT usPayLoadLength );
ULONG PPPOE_Client_ProcPado ( PPPOE_ETHER_ADDR_S *pstEthernetAdd, 
                                MBUF_S *pstMbuf,
                                PPPOE_CLIENT_CB_S *pstPoeClientCB,
                                ULONG ulPoeClientDbgFlag );                    
ULONG PPPOE_Client_ProcPads ( PPPOE_ETHER_ADDR_S *pstEthernetAdd, 
                                MBUF_S *pstMbuf,
                                PPPOE_CLIENT_CB_S *pstPoeClientCB,
                                ULONG ulPoeClientDbgFlag );                    
ULONG PPPOE_Client_ProcPadt ( PPPOE_ETHER_ADDR_S *pstEthernetAdd, 
                                MBUF_S *pstMbuf,
                                PPPOE_CLIENT_CB_S *pstPoeClientCB,
                                ULONG ulPoeClientDbgFlag );                    
VOID  PPPOE_Client_DiscoveryInput ( IFNET_S *pstEthIf, 
                                       MBUF_S *pstMbuf, 
                                       PPPOE_ETHER_ADDR_S *pstEthernetAdd, 
                                       PPPOE_CLIENT_CB_S  *pstPoeClientCB,
                                       ULONG ulPoeClientDbgFlag );
VOID  PPPOE_Client_SessionInput ( IFNET_S *pstEthIf, 
                                     MBUF_S *pstMbuf, 
                                     PPPOE_ETHER_ADDR_S *pstEthAdd,
                                     PPPOE_CLIENT_CB_S *pstPoeClientCB,
                                     ULONG ulPoeClientDbgFlag );
VOID PPPOE_Client_DiscoveryOutput ( PPPOE_C_SESSION_S *pstSession, MBUF_S *pstMbuf, char *pszPacketType, ULONG ulPktType );
VOID  PPPOE_Client_DiscoveryTimerOutProc ( VOID ); 
VOID  PPPOE_Client_IdleTimerOutProc ( VOID );
ULONG PPPOE_Client_SendPadt ( PPPOE_C_SESSION_S *pstSession );
PPPOE_C_SESSION_S * PPPOE_Client_NewSession ( ULONG ulQueueLength,
                                                 ULONG  ulIdleToutMaxLength,
                                                 IFNET_S *pstEthIf,
                                                 IFNET_S *pstDialerIf,
                                                 USHORT usBundleNumber,
                                                 UCHAR  ucHostUniq );
VOID PPPOE_Client_DelSession ( PPPOE_C_SESSION_S *pstSession );
ULONG PPPOE_Client_DropPacket ( MBUF_S *pstMbuf, ULONG ulCmd, CHAR *pcData );
/*Add by Q62011 for BC3D01354*/
ULONG PPPOE_Client_Reset_SessOnEth(ULONG ulEthIfIndex);
ULONG PPPOE_PPI_Update(PPPOE_C_SESSION_S *pstSession, ULONG ulCmd, VOID *pstPpiPppoeInfo);
ULONG PPPOE_SetPoecDebugFlag(IFNET_S *pstDialerIf, IFNET_S *pstEthIf, ULONG ulFlag);
ULONG PPPOE_GetPoecDebugFlag(IFNET_S *pstDialerIf, IFNET_S *pstEthIf, ULONG *pulFlag);
ULONG PPPOE_CheckMac(UCHAR * ucSrcMacAddr);
ULONG POEC_GR_Smooth();
VOID POEC_GR_DealMsg(UINTPTR aulMsg[4]);

#ifdef __cplusplus
}
#endif

#endif 

