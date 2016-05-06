/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trunk_var.h
*
*  Project Code: VISP V100R006
*   Module Name: Trunk  
*  Date Created: 2006-11-27
*        Author: sunmo(44939)
*   Description: Trunk模块全局变量的声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2006-11-27  sunmo(44939)     Create the first version.
*
*******************************************************************************/

#ifndef _TRUNK_VAR_H_
#define _TRUNK_VAR_H_

#ifdef __cplusplus
extern "C"{
#endif

/* 全局Trunk信息表数组 */
extern TRUNK_INFO_TBL_S *g_stTrunkInfoTbl;

/* Trunk系统MAC, 记录Trunk模块的系统MAC, 供LACP协商使用 */
extern UCHAR g_ucSysMacAddress[6];

/* Trunk系统优先级, 记录Trunk模块的系统优先级, 供LACP协商使用 */
extern USHORT g_usSysPri;

extern UCHAR g_ucWarningForPortRemove;
extern ULONG g_ulWarningForLacpDisable;


/* eth主备mac一致预配置 */
extern ULONG g_ulEthBakMac;

/* Trunk模块LACP报文处理调试开关(0-关闭, 1-打开) */
extern ULONG g_ulDebugLacpPkt;
/* Trunk模块其它报文处理调试开关(0-关闭, 1-打开) */
extern ULONG g_ulDebugOtherPkt;
/* Trunk模块状态机变迁信息调试开关(0-关闭, 1-打开) */
extern ULONG g_ulDebugFsm;

/* Trunk模块物理定时器ID */
extern ULONG g_ulTrunkGlobalTimerId;

/* Trunk模块信息 */
extern TRUNK_MOD_INFO_S g_stTrunkModInfo;

/* Core中使用的回调函数集 */
extern TRUNK_SHELL_CALLBACK_SET_S g_stTrunkShellApi;

/* Trunk模块的IFNET组件功能虚表指针 */
extern struct IIF_IFNET_ComIntFUNVtbl *g_pstTrunkIfnetFunTable;

/* Trunk模块的ETHARP组件功能虚表指针 */
extern struct IIF_COMP_ETHERNET_ComIntFUNVtbl *g_pstTrunkEthFunTable;

/* Trunk模块的AM4组件功能虚表指针 */
extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl *g_pstTrunkAm4FunTable;

/* Trunk模块的DHCP4R组件功能虚表指针 */
extern struct IIF_COMP_DHCP4R_ComIntCFGVtbl *g_pstTrunkDhcp4rCfgTable;

/* Trunk模块OAM3AH 组件功能虚表 */
extern struct IIF_COMP_OAM3AH_ComIntFUNVtbl *g_pstTrunkOam3ahFuncTable;

/* Trunk模块OAM1AG 组件功能虚表 */
extern struct IIF_COMP_OAM1AG_ComIntFUNVtbl *g_pstTrunkOam1agFuncTable;

/* Trunk模块OAM1AG 组件配置虚表 */
extern struct IIF_COMP_OAM1AG_ComIntCFGVtbl *g_pstTrunkOam1agCfgTable;

/* Trunk模块L2IF 组件功能虚表 */
extern struct IIF_COMP_L2IF_ComIntFUNVtbl *g_pstTrunkL2ifFuncTable;

/* Trunk组件配置虚表 */
extern struct IIF_COMP_TRUNK_ComIntCFGVtbl *g_pstTrunkCfgTable;

/*增加SyncE组件虚表*/
extern struct IIF_COMP_SYNCE_ComIntFUNVtbl *g_pstTrunkSyncEFunVtbl;

/*Added by w00207740, NSR TRUNK,添加与NSR模块配合需要的虚表, 2013/10/9 */
extern struct IIF_COMP_NSR_ComIntFUNVtbl *g_pstNsrTrunkFunTable;

/* 全局分发策略钩子函数  */
extern TRUNK_DISTRIBUTE_HOOK_FUNC g_pfUserDistributeHookFunc;

extern TRUNK_VLANCHECK_HOOK_FUNC g_pfVlanCheckHookFunc;

/* 慢协议多播physical地址 */
extern UCHAR g_ucSlowProtocolMacAddr[TRUNK_MACADDR_LEN];

/* 调试信息输出字符串 */
extern CHAR* g_pcFsmType[];
extern CHAR* g_pcTranStateReason[];
extern CHAR* g_pcFsmState[][7];

/* 接口增加或移除trunk时通知bfd,进行告警输出 */
extern ULONG (*g_pfTrunkPortChangeNotifyBfd)(ULONG, ULONG);

/* 用户注册获取系统MAC和trunk MAC函数 */
extern TRUNK_GETMACADDRRESS_HOOK_FUNC g_pfTrunkGetMacAddress;

/* 用户注册释放系统MAC和trunk MAC函数 */
extern TRUNK_FREEMACADDRRESS_HOOK_FUNC g_pfTrunkFreeMacAddress;

/* 用户注册的根据三维值获取Port Id的钩子函数 */
extern TRUNK_GETLACPPORTID_HOOK_FUNC g_pfLacpPortIdHook;

/* 以太全0地址 */
extern UCHAR g_szEtherAllZeroAddr_trunk[MACADDRLEN];

/* 保存Trunk首次协商不通过对外告警的时间 */
extern ULONG g_ulTrunkNegTime;

/* 首次协商不通过对外告警定时器ID*/
extern ULONG g_ulTrunkNegTimerId;

/* 首次协商不通过对外告警的物理定时器周期 5s */
/* 用户配置的协商告警时间必须是5s的倍数 */
extern ULONG g_ulTrunkNegPhyTimer;

/* TURNK LACP状态变化通知钩子函数*/
extern TrunkLacpChangeNotify g_pfTrunkLacpNotify;

/* Add for V2R3C07, by z00208058/w00207740, at 2012-4-16. 修改原因: TRUNK LACP下移需求开发 */
extern ULONG g_ulTrunkNPMode ;

extern ULONG g_ulTkParnterMacRefreshDropSwitch;

extern ULONG g_ulDealTrunkLinkLB;                  /* Trunk子链路环回LACP报文增强处理 */

extern ULONG g_ulTrunkMaxIfNums ;
extern ULONG g_ulDropNoLacpPkt ;

/* 处理PTPV2报文并释放 */
extern ULONG (*g_pfETH_PTPV2_HOOK)(MBUF_S*);

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _TRUNK_VAR_H_ */

