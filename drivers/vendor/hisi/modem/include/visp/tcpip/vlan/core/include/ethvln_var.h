/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ethvln_var.h
*
*  Project Code: VISPV100R007
*   Module Name: Ethvlan  
*  Date Created: 2008-08-01
*        Author: qinyun(62011)
*   Description: ethvln_var.h
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME              DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-08-01   qinyun(62011)     Create the first version.
*******************************************************************************/


#ifndef _ETHVLNVAR_H_
#define _ETHVLNVAR_H_

#ifdef  __cplusplus
extern "C"{
#endif

extern ULONG g_ulVlanInitFlag;
extern ULONG g_ETHVLAN_InputErrorCnt;
extern ULONG g_ETHVLAN_OutputErrorCnt;
extern ETHVLAN_VID_NODE_S * g_pstVIDNode[MAX_VLAN_NUM];
extern ETHVLAN_TOS_TO_VLAN_PRIORITY g_pfEthvlanTosToPriority;
extern BOOL_T g_ETHVLAN_bDebugPacket;
extern BOOL_T g_ETHVLAN_bDebugErr;
extern struct IIF_IP4_SOCK_ComIntFunVtbl *g_pstVlanSockFunTable;
extern struct IIF_IFNET_ComIntFUNVtbl *g_pstVlanIFNETFunTable;
extern struct IIF_COMP_ETHERNET_ComIntFUNVtbl  *g_pstVlanEthFUNTable;
extern struct IIF_COMP_ETHERNET_ComIntCFGVtbl  *g_pstVlanEthCFGTable;
extern struct IIF_IPV4_IP_PP4_ComIntCFGVtbl  *g_pstVlanPp4FUNTable;
extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl * g_pstVlanAM4ComFunTable;
extern struct IIF_COMP_TRUNK_ComIntCFGVtbl *g_pstVlanTrunkCFGTable;
extern struct IIF_COMP_TRUNK_ComIntFUNVtbl *g_pstVlanTrunkFUNTable;
/* IPV6×é¼þ */
extern struct IIF_IP6_ADDR_ComIntFunVtbl *g_pstVlanIpv6AddrFunTable; 
extern struct IIF_IP6_ND_ComIntCFGVtbl *g_pstVlanIpv6NdCfgTable; 

extern ETHVLAN_BCPKT_HOOK_FUNC g_pfEthvlnBCPktFun;

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif /* end of  _ETHVLN_VAR_H_*/

