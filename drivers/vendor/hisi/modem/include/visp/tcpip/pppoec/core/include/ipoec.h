/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              ipoec.h
 *
 *  Project Code: VISP1.5
 *   Module Name: PPPoE Client
 *  Date Created: 2005-09-15
 *        Author: t45114
 *   Description: Defines Component ID, and All Interface IDs
 *               
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE            NAME                DESCRIPTION
 *  2005-09-15      t45114              Create file  
 *  2006-03-30      liai                Adjust for D00660
 *  2006/04/21      liai                Adjust for D00865
 *  2007-01-04      f54882              Adjust for A82D10682
 ************************************************************************/

#ifndef _IPOEC_H_
#define _IPOEC_H_

#ifdef __cplusplus
extern "C" {
#endif



DECLARE_INTERFACE ( IIF_PPPOE_CLIENT_ComIntFUN ) 
{
    IUNKNOWN_METHODS

    METHOD_( ULONG, pfPPPOE_Client_Input ) ( MBUF_S *pstMbuf );
        
    METHOD_( ULONG, pfPPPOE_Client_DropPacket ) ( MBUF_S *pstMbuf, ULONG ulCmd, CHAR *pcData );

    METHOD_( ULONG, pfPPPOE_Client_DDR_Send ) ( MBUF_S *pstMBuf );

    METHOD_( ULONG, pfPPPoE_Client_IfDelete ) ( ULONG ulIfIndex );

    METHOD_( ULONG, pfPPPOE_Client_SessionOutput ) ( PPPOE_C_SESSION_S *pstSession, MBUF_S *pstMbuf );

    METHOD_( ULONG, pfPPPOE_Client_PppIoctl ) ( UINTPTR ulLinkHandle, ULONG ulCmd, char *pcPara);

    METHOD_( VOID, pfPPPOE_Client_Clear_Intf_Session ) ( IFNET_S *pstEthIfNet );   

    METHOD_( VOID, pfPPPOE_Client_DestroySessions ) ( VOID *pPoeClientCB );

    METHOD_( ULONG, pfPPPOE_Client_GetFreeNumber ) ( ULONG ulPortNo );

    METHOD_( ULONG, pfPPPOE_Client_GetBundleNumFromDialer ) ( ULONG ulDialerIfIndex );
        
    METHOD_( ULONG, pfPPPOE_Client_GetPoecEthIf ) ( ULONG ulBundleNumber, IFNET_S **ppstEthIf );

    METHOD_( UINTPTR, pfPPPOE_Client_GetPoecSession ) ( ULONG ulBundleNumber );

    METHOD_( ULONG, pfPPPOE_Client_GetSesStat ) ( ULONG ulDialerIfIndex, PPPOECSTAT_S *pstStat );

    METHOD_( ULONG, pfPPPOE_Client_ResetSesStat ) ( ULONG ulDialerIfIndex );
    
    METHOD_( ULONG, pfPPPOE_Client_GetSessionInfo )(ULONG ulPoecIfIndex, TCPIP_PPPOE_C_SESSION_S *pstSessionInfo);
    
    METHOD_( ULONG, pfPPPOE_Client_CreatePoecIntf  ) ( ULONG *pulPoecIfIndex, ULONG ulPortNo );
    METHOD_( ULONG, pfPPPOE_Client_DelPoecIntf ) ( ULONG ulPoecIfIndex );
    METHOD_( ULONG, pfPPPOE_Client_StartPoecSession ) ( ULONG ulEthIfIndex, ULONG ulPoecIfIndex );
    METHOD_( ULONG, pfPPPOE_Client_StopPoecSession ) ( ULONG ulEthIfIndex, ULONG ulPoecIfIndex );

    METHOD_(ULONG, pfPOEC_HA_BatchBackup)(VOID);
    METHOD_(ULONG, pfPOEC_HA_Input)(UCHAR * pBuf, ULONG ulMsgLen);
    METHOD_(ULONG, pfPOEC_HA_Smooth)(VOID);
    METHOD_(ULONG, pfPOEC_HA_Clean)(VOID);

    METHOD_(VOID, pfPOEC_GR_DealMsg)(UINTPTR aulMsg[4]);
};


DECLARE_INTERFACE (IIF_PPPOE_CLIENT_ComIntCFG)
{
    IUNKNOWN_METHODS

    METHOD_( ULONG,  pfPPPOE_Client_Init_Com ) ( COM_ID_INFO_S *pstComInfo, ULONG  ulComLen );

    METHOD_( ULONG , pfPPPOE_Client_Activate_Com ) ( VOID );

    METHOD_( ULONG , pfPPPOE_Client_SetModuleInfo ) ( PPPOE_CLIENT_MOD_INFO_S  *pstMInfo );
    

    METHOD_( ULONG, pfPPPOE_Client_Create_Session ) ( IFNET_S *pstEthIfNet, ULONG ulBundleNumber, 
            ULONG ulIdleTime, UCHAR ucHostUniq, ULONG ulQueueLength );
    
    METHOD_( VOID, pfPPPOE_Client_DDR_Proc_PoeSession ) ( IFNET_S *pstDialerIf, UCHAR ucDisc );
    
    METHOD_( ULONG,  pfPPPOE_Client_No_Session ) ( IFNET_S *pstEthIfNet, ULONG ulBundleNumber );

    METHOD_( ULONG, pfPPPOE_Client_Reset_All_Session ) ( );
    /*modify by wht06310 for PPP接口整改,2006-05-29*/
    METHOD_( ULONG, pfPPPOE_Client_Reset_Session ) ( ULONG ulPoecIfIndex );

    METHOD_( ULONG, pfPPPOE_Client_GetStatFromSessionInfo )
                                ( PPPOE_C_SESSION_S *pstSesInfo, PPPOECSTAT_S *pstSesDispInfo );
    
    METHOD_( ULONG, pfPPPOE_Client_SetDialerBundleNum ) ( ULONG ulCmdSwitch, ULONG ulIfIndex, ULONG ulBundleNumber );

    METHOD_( VOID, pfPPPOE_Client_CfgDebug ) ( ETHARP_MTSOFTC_S *pstMT, ULONG ulDebugFlag, UCHAR bSetFlag );
    
    METHOD_( ULONG, pfPPPOE_Client_GetPoecDebugFlag ) ( VOID );

    METHOD_(ULONG, pfTCPIP_HA_SetPoecDbg)(ULONG ulDbg);
    METHOD_(ULONG, pfPOEC_HA_GetPoecDbg)(ULONG *pulRet);

    METHOD_(VOID, pfPOEC_HA_DebugOutput)(UCHAR *pBuf, ULONG ulMsgLen, ULONG ulCmd);
    METHOD_(ULONG, pfPOEC_HA_SetPoecVerboseDbg)(ULONG ulDbg);
    METHOD_(ULONG, pfPOEC_HA_GetPoecVerboseDbg)(ULONG *pulRet);
    METHOD_(ULONG, pfPPPOE_Client_Reset_SessOnEth)(ULONG ulEthIfIndex);
    METHOD_(ULONG, pfPPPOE_SetPoecDebugFlag)(IFNET_S *pstDialerIf, IFNET_S *pstEthIf, ULONG ulFlag);
    METHOD_(ULONG, pfPPPOE_GetPoecDebugFlag)(IFNET_S *pstDialerIf, IFNET_S *pstEthIf, ULONG *pulFlag);
};


DECLARE_INTERFACE (IIF_PPPOE_CLIENT_ComIntSSA)
{
    IUNKNOWN_METHODS

    METHOD_( VOID, pfPPPOE_Client_DiscoveryTimerOutProc ) ( VOID );

    METHOD_( VOID, pfPPPOE_Client_IdleTimerOutProc ) ( VOID );

    METHOD_( ULONG, pfPPPOE_Client_RegShellApi ) ( PPPOE_CLIENT_SHELL_CALLBACK_S *pstShellApi );

};

/* For implement of QuerfyInstance() */
typedef struct tagPPPOE_CLIENT_IntObj
{
    struct IIF_PPPOE_CLIENT_ComIntFUN      *pCompIntFun;  
    struct IIF_PPPOE_CLIENT_ComIntCFG      *pCompIntCfg;   
    struct IIF_PPPOE_CLIENT_ComIntSSA      *pCompIntSsa;  
}PPPOE_CLIENT_INT_OBJ_S;


#ifdef __cplusplus
}
#endif

#endif /*_IPOEC_H_*/

