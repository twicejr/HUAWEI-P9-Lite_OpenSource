/*******************************************************************************
*
*
*                Copyright 2011, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp6r_var.h
*
*  Project Code: VISP V2R3C06
*   Module Name: DHCP6R  
*  Date Created: 2011-7-19
*        Author: PBQ(RT24429)
*   Description: 变量声明
*
*-------------------------------------------------------------------------------
*  Modification  History
*  DATE          NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2011-7-27     PBQ(RT24429)     Create the first version.
*
*******************************************************************************/
#ifndef _DHCP6R_VAR_H_
#define _DHCP6R_VAR_H_

#ifdef __cplusplus
    extern "C"{
#endif  /* end of __cplusplus */

/* DHCP6R组件类工厂虚表 */
extern IComponentFactory m_DHCP6R_CompFactory;

/* DHCP6R模块组件功能和配置虚表 */
extern IIF_COMP_DHCP6R_ComIntFUN g_IComInt_DHCP6R_FUN;
extern IIF_COMP_DHCP6R_ComIntCFG g_IComInt_DHCP6R_CFG;

/* DHCP6R模块组件信息 */
extern struct ComponentInfo m_CompDHCP6RInfo;

/* 组件注册信息 */
extern APP_INIT_INFO_S g_stDHCP6RAppInfo;

/* 全局控制块 */
extern DHCP6R_CFG_HEAD_S g_stDHCP6RCfgHead;
extern DHCP6R_DBG_S g_stDHCP6RDbg;

/* Relay异步socket消息ID */
extern ULONG g_ulDHCP6RSocketQId;

/* Relay其他模块通知消息ID  */
extern ULONG g_ulDHCP6RCntrlQId;

/* Relay模块共享数据互斥信号量 */
extern ULONG g_ulDHCP6RSm;

/* 指向RELAY用于保存接收的DHCP报文的缓冲区的指针 */
extern UCHAR *g_pucDHCP6RUdpBuf; 

/* Relay全局socket */
extern LONG  g_lDHCP6RSocket; 

/* 报文处理流程中保存报文接收接口 */
extern ULONG g_ulInIfIndex;

/* DHCP6R模块信息 */
extern DHCP6R_MOD_INFO_S g_stDHCP6RModInfo;

/* Core中使用的回调函数集 */
extern DHCP6R_SHELL_CALLBACK_SET_S g_stDHCP6RShellApi;
    
/* DHCP6R模块的IFNET组件功能虚表指针 */
extern struct IIF_IFNET_ComIntFUNVtbl *g_pstDHCP6RIfnetFunTable;

/* DHCP6R模块的IPV6组件配置虚表指针 */
extern struct IIF_IP6_ADDR_HOST_CFGVtbl *g_pstDHCP6RIp6CfgTable;

/* DHCP6R模块的IPV6组件功能虚表指针 */
extern struct IIF_IP6_ADDR_HOST_FUNVtbl *g_pstDHCP6RIp6FunTable;

/* DHCP6R模块的SOCKET6组件配置虚表指针 */
extern struct IIF_IP6_SOCK_ComIntFUNVtbl *g_pstDHCP6RSock6FunTable;

/* dhcp6r组件功能虚表 */
extern struct IIF_COMP_DHCP6R_ComIntFUNVtbl *g_pstDHCP6RFunTable;

/* dhcp6r组件配置虚表 */
extern struct IIF_COMP_DHCP6R_ComIntCFGVtbl *g_pstDHCP6RCfgTable;

/* 外部模块定义变量 */
/* VISP紧密模块全局互斥信号量 */
extern ULONG g_ulSemForTightMods;

/* dhcp6r debug status */
extern CHAR *g_aszDHCP6RDbgStatus[];

/* dhcp报文消息类型字符串 */
extern CHAR *g_aszDHCP6RPkt[]; 

/* dhcp6r接口使能状态字符串 */
extern CHAR *g_aszDHCP6REnableStatus[]; 

/* DHCP6R使能模式对应的描述字符串 */
extern CHAR *g_aszDHCP6RCfgMode[];

/* DHCP6R中继模式对应的描述字符串 */
extern CHAR *g_aszDHCP6RFwdMode[];

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _DHCP6R_VAR_H_ */

