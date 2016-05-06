/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              iudp.h
*
*  Project Code: VISP1.5
*   Module Name: UDP4
*  Date Created: 2004-05-04
*        Author: w25705
*   Description: To define udp4 component interfaces
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2004-05-04  w25705           Create the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/
#ifndef _IUDP_H_
#define _IUDP_H_

#ifdef __cplusplus
extern "C" {
#endif

#define IP4_UDP4_EXT_COMIF_CNT  7/* Aravind*/

typedef struct tagUDP4_INT_OBJ_S
{
    struct IIF_IP4_UDP4_ComIntCfg *pstIComInt_UDP4_Cfg;
} UDP4_INT_OBJ_S;


DECLARE_INTERFACE( IIF_IP4_UDP4_ComIntCfg)
{
    IUNKNOWN_METHODS

    METHOD_(ULONG,pfIP4_UDP4_Init_Com) (const COM_ID_INFO_S *pComInfo, ULONG ulComLen);
    METHOD_(ULONG,pfIP4_UDP4_Activate_Com)( );
    METHOD_(ULONG,pfIP4_UDP4_SetModuleInfo) (struct  tagIP4_UDP4_MOD_INFO_S *pMInfo);
    METHOD_(ULONG,pfIP4_UDP4_RegisterAll) (struct tagIP4_UDP4_SH_CALLBACUP_SET_S *pfUDP4CallBack);

    METHOD_(VOID,pfIP4_UDP4_SetFilterZero ) ( VOID );
    METHOD_(VOID,pfIP4_UDP4_SetFilterAll ) ( VOID );
    METHOD_(ULONG,pfIP4_UDP4_SetFilter ) ( ULONG ulFlag, ULONG ulTaskId, ULONG ulSockId );
    METHOD_(VOID,pfIP4_UDP4_GetFilter ) (ULONG *pulDebugFlag,struct tagUDP_DEBUGFILTER_S *pstUdpDbgFilter);

    METHOD_(VOID,pfIP4_UDP4_GetStatistics)( struct tagUDPSTAT_S *pstUdpStatistics);
    METHOD_(VOID,pfIP4_UDP4_ClearStatistics )( VOID );

    METHOD_(VOID, pfIP4_UDP4_SetIKETaskId)(ULONG ulTaskId);

    METHOD_(ULONG, pfUDP_ClearSFIBCache)(VOID);
    METHOD_(VOID , pfUDP_Input)(MBUF_S *pMBuf, LONG nIpHLen);
    METHOD_(ULONG, pfOPTIM_UdpInput)(MBUF_S *pstMbuf, LONG iFd);
    METHOD_(ULONG, pfUDP4_Process_For_InterMediate)(MBUF_S *pMBuf, LONG nIpHLen);
    METHOD_(ULONG, pfUDP_GetPerUdp4ConnStats)(UDP4CONN_S *pstConnInfo, UDP4PERSTAT_S  *pstRetStats);
    METHOD_(ULONG, pfUDP_ResetPerUdp4ConnStats)(UDP4CONN_S *pstConnInfo);

    METHOD_(ULONG, pfUDP_OpenUdpNetInfo)(UINTPTR *pulWaitlist);
    METHOD_(ULONG, pfUDP_GetUdpNetInfo)(UINTPTR ulWaitlist , TCPIP_UDPNETINFO_S *pstNetInfo);
    METHOD_(ULONG, pfUDP_GetBFDNetInfo)(TCPIP_UDPNETINFO_S *pstNetInfo);
    METHOD_(ULONG, pfUDP_CloseUdpNetInfo)(UINTPTR ulWaitlist);
};

#ifdef __cplusplus
}
#endif

#endif /* _IUDP_H_ */
