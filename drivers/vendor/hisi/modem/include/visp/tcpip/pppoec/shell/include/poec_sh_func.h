

#ifndef  _POEC_SH_FUNC_H_
#define  _POEC_SH_FUNC_H_

#ifdef __cplusplus
extern "C"{
#endif

/*poec_sh_init.c*/
ULONG PPPOE_Client_RegApp ( VOID );
ULONG PPPOE_Client_SH_GlobalInit ( VOID );
ULONG PPPOE_Client_SH_DeInit ( VOID );
ULONG PPPOE_Client_SH_Init ( VOID );
VOID PPPOE_Client_IfnetHotNotifyCB ( ULONG ulEvent, ULONG ulSlot, VOID *pstIfnet, ULONG ulIfIndex );
VOID PPPOE_Client_DiscoveryTimeout ( VOID *pData );
VOID PPPOE_Client_IdleTimeout ( VOID *pData );
VOID PPPOE_Client_CreateDisTimer ( VOID );
VOID PPPOE_Client_CreateIdleTimer ( VOID );
VOID PPPOE_Client_DeleteDisTimer ( VOID );
VOID PPPOE_Client_DeleteIdleTimer ( VOID );
VOID PPPOE_Client_PauseDisTimer ( VOID );
VOID PPPOE_Client_ResumeDisTimer ( VOID );


/*poec_sh_dbg.c*/
VOID PPPOE_Client_RegToIC ( VOID );
VOID PPPOE_Client_DebugToIC ( CHAR *szString, ULONG ulLen );
VOID PPPOE_Client_DbgOut ( CHAR *strDbgOut );
VOID PPPOE_Client_CFG_ExecOutStr ( ULONG ulExecID, ULONG ulInfoID );


/*poec_sh_disp.c*/
VOID * PPPOE_Client_CMD_GetNext ( UCHAR ucGetNextType, VOID *pCurNode );
VOID * PPPOE_Client_CMD_GetFirst ( UCHAR ucGetFirstType, ULONG ulDialBundleNum );
VOID * PPPOE_Client_CMD_WaitListGetNext ( VOID *pParam, VOID **ppNewParam );
VOID PPPOE_Client_CMD_Display_Title ( UCHAR ucDisplayType, ULONG ulExecID );
LONG PPPOE_Client_CMD_FormSessionSummInfo ( PPPOECSTAT_S *pstSesDispInfo, CHAR *pcBuffer,
                                                                        INT32 i32BufLen, INT32 i32InputOffset);
LONG PPPOE_Client_CMD_FormSessionPackInfo ( PPPOECSTAT_S *pstPppoeSesDisp, CHAR *pcBuffer,
                                                                      INT32 i32BufLen, INT32 i32InputOffset);
LONG PPPOE_Client_CMD_DumpDisplayInfo ( UCHAR ucDisplayType, ULONG ulDialBundleNum, PPPOE_CLIENT_DISPLAY_BLOCK_S *pstDisplayBlock );
ULONG PPPOE_Client_Cmd_DisplayMainBoard ( UCHAR ucDisplayType, ULONG ulDialBundleNum, BOOL_T *pbUserAbort, ULONG *pulCurLine, ULONG ulExecID );
VOID PPPOE_Client_CMD_Display ( UCHAR ucDisplayType, ULONG ulPoecIfIndex, ULONG ulExecID );

ULONG PPPOE_Client_Cmd_DisplayIOBoard ( ULONG ulSlot, UCHAR ucDisplayType, ULONG ulBundleNumber, BOOL_T *pbUserAbort, ULONG *pulCurLine, ULONG ulExecID );
VOID PPPOE_Client_CMD_DisplayRpcCallBack ( ULONG ulSourceSlot, VOID *pRpcEnq, 
                                           ULONG ulRpcEnqLen, VOID **ppRpcRpl,
                                           ULONG *pulRpcRplLen );


#ifdef __cplusplus
}
#endif

#endif 

