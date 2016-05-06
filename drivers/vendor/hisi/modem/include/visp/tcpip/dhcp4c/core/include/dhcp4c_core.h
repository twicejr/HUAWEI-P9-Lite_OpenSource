/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4c_core.h
*
*  Project Code: VISP1.5
*   Module Name: DHCP client Module    
*  Date Created: 2004-06-08 
*        Author: tangcongfeng(36956)
*   Description: Header of dhcp_core.c
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                   DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2004-06-08 tangcongfeng(36956)    Creat the first version.
*
*******************************************************************************/

#ifndef _DHCP4C_CORE_H_
#define _DHCP4C_CORE_H_


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
/* DHCP 组件信息*/
extern DHCP4C_MOD_INFO_S                    g_stDHCP4CModInfo;
/*DHCP模块 回调函数*/
extern DHCP4C_SH_CALLBACUP_SET_S g_stDHCP4CShellFun;

/* the other component interface instances */
/*ETHERNET 组件功能虚表*/
extern struct IIF_COMP_ETHERNET_ComIntFUNVtbl  * g_pstDhcp4cEthFunVtabl;
/*AM4 组件功能虚表*/
extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl    * g_pstDhcp4cAM4FunVtable;
/*DNS 组件功能虚表*/
extern struct IIF_COMP_DNSC_ComIntFUNVtbl      * g_pstDhcp4cDNSCFunVtable;
/*AM4 组件配置虚表*/
extern struct IIF_IPV4_IP_AM4_ComIntCFGVtbl    * g_pstDhcp4cAM4ComCfgTable;
/*UDP4 组件配置虚表*/
extern struct IIF_IP4_UDP4_ComIntCfgVtbl       * g_pstDhcp4cUDP4CfgTable;

/*DHCP的信号量*/
extern ULONG g_ulSemForDHCP4C;

ULONG DHCP4C_Activate_Com();
ULONG DHCP4C_Init_Com(VOID);
ULONG DHCP4C_DeInit_Com(VOID);
ULONG DHCP4C_RegShellApi ( DHCP4C_SH_CALLBACUP_SET_S * pstCallBkSet);
ULONG DHCP4C_SetModuleInfo(DHCP4C_MOD_INFO_S *pstMInfo );

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif

