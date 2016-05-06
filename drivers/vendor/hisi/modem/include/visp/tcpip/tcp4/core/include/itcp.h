/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              itcp.h
*
*  Project Code: VISP1.5
*   Module Name: IP TCP4  
*  Date Created: 2004-05-04
*        Author: w25705
*   Description: To define tcp component interfaces
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2004-05-04  w25705           Create the first version.
*
*******************************************************************************/
#ifndef ITCP_H
#define ITCP_H

#ifdef __cplusplus
extern "C" {
#endif

/* TCP4组件配置接口的结构 */
DECLARE_INTERFACE( IIF_IP4_TCP4_ComIntCfg)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG,pfTCP4_Init_Com) (const COM_ID_INFO_S *pComInfo, ULONG ulComLen);
    METHOD_(ULONG,pfTCP4_Activate_Com)();
    METHOD_(ULONG,pfTCP4_Set_Module_Info)(TCP4_MOD_INFO_S * pstMInfo);
    METHOD_(ULONG,pfTCP4_RegisterAll)(IP4_TCP4_SH_CALLBACUP_SET_S * pfTCP4CallBack);
   
    METHOD_(VOID,pfTCP4_GetStatistics)(TCPSTAT_S *pstTCPStat);
    METHOD_(VOID,pfTCP4_SetStatisticsZero) (VOID);        
    
    METHOD_(VOID,pfTCP4_SetFilterZero) (VOID);
    METHOD_(VOID,pfTCP4_SetFilterAll)(VOID);
    METHOD_(ULONG,pfTCP4_ProDbugFilter)(ULONG ulFlag, ULONG ulDbgFilterId, ULONG ulTaskId, ULONG ulSockId);        
    
    METHOD_(ULONG,pfTCP4_FindTCPCB)(VOID *pAddress, TCPCB_INFO_S *pInfo);

    METHOD_(LONG, pfTCP4_SetRespondQuench)(ULONG ulValue);
    
    METHOD_(ULONG,pfTCP_GetTcpHash)(VOID **pstTcpHash);
    METHOD_(ULONG,pfTCP_GetPerTcp4ConnStats)(TCP4CONN_S *pstConnInfo, TCP4PERSTAT_S *pstRetStats);
    METHOD_(ULONG,pfTCP_ResetPerTcp4ConnStats)(TCP4CONN_S *pstConnInfo);
    /*Added by wangtong207740, 基于socket id 获取对应的tcp报文统计, 2012/9/5 */
    METHOD_(ULONG,pfTCP_GetInfoBySocket)(ULONG ulSocketId ,TCP_SOCK_INFO_S *pstTcpInfo);
    /* Add by heyijun 00218462 for DTS2012092803600 维测需求开发, 2012-9 */
    METHOD_(ULONG,pfTCP_GetTcpInfoBySocketNum)(TCP_SOCK_INFO_S *pstTcpConStat, ULONG ulRetSize);
    /* End of Add by heyijun 00218462 for DTS2012092803600 维测需求开发, 2012-9 */    
};

/* TCP4组件功能接口的结构 */
DECLARE_INTERFACE( IIF_IP4_TCP4_ComIntFun)
{
    IUNKNOWN_METHODS
        
    METHOD_(VOID,pfTCP4_Get_Param)(ULONG ulType, ULONG * pulValue);
    METHOD_(ULONG,pfTCP4_Set_Param) (ULONG ulType ,ULONG ulValue);
    
    METHOD_(ULONG,pfTCP4_OpenObject) (ULONG ulMainType, UINTPTR * pulHandle);
    METHOD_(ULONG,pfTCP4_CloseObject) (UINTPTR  ulHandle);
    METHOD_(ULONG,pfTCP4_Get_Object_First )(UINTPTR ulHandle, INPCB_INFO_S *pPCBInfo);
    METHOD_(ULONG,pfTCP4_Get_Object_Next )(UINTPTR ulHandle, INPCB_INFO_S *pPCBInfo);      
    
    METHOD_(VOID,pfTCP4_GetFilter)(ULONG *pulDebugFlag,TCPDBUGFILTRD_S *pstPacketFilter, TCPDBUGFILTRD_S*pstEventFilter,TCPDBUGFILTRD_S *pstMD5Filter);

    METHOD_(ULONG,pfTCP_ClearTcbCache)();
    
    /* Added for tcp ha */
    METHOD_(VOID, pfTCP_HA_FreeTCPCB)(TCPCB_S *pTCPCB);
    METHOD_(VOID, pfTCP_HA_SockShutdownRead)(SOCKET_S *pSocket);
    METHOD_(VOID, pfTCP_HA_SockBackupStateChange)(SOCKET_S *pSocket);
    METHOD_(LONG, pfTCP_HA_TCPCBPack)(TCPCB_S *pTCPCB, BKTCPCB_S *pBkTCPCB);
    METHOD_(LONG, pfTCP_HA_TCPCBUnpack)(TCPCB_S *pTCPCB, BKTCPCB_S *pBkTCPCB, ULONG ulBkTCPCBLen);
    METHOD_(LONG, pfTCP_HA_BatchBackup)();
    METHOD_(LONG, pfTCP_HA_BackupMsgDeal)(UINTPTR ulMsg[4], CHAR **ppszBuf, ULONG *pulBufLen);
    METHOD_(LONG, pfTCP_HA_Restore)(CHAR *pszBackupMsg);

    METHOD_(ULONG, pfTCP_OpenTcpNetInfo)(UINTPTR *pulWaitlist);
    METHOD_(ULONG, pfTCP_GetTcpNetInfo)(UINTPTR ulWaitlist, TCPIP_TCPNETINFO_S *pstNetInfo);
    METHOD_(ULONG, pfTCP_CloseTcpNetInfo)(UINTPTR pulWaitlist);
};

typedef struct tagTCP4_INT_OBJ_S
{
    struct IIF_IP4_TCP4_ComIntCfg * pstIComInt_TCP4_Cfg;
    struct IIF_IP4_TCP4_ComIntFun * pstIComInt_TCP4_Fun;
} TCP4_INT_OBJ_S;

#ifdef __cplusplus
}
#endif

#endif
