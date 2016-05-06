/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              3ah_var.h
*
*  Project Code: VISPV100R007
*   Module Name: ETH OAM 3AH  
*  Date Created: 2008-2-28
*        Author: LY(57500)
*   Description: 3AH模块变量声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-2-28  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _3AH_VAR_H_
#define _3AH_VAR_H_

#ifdef __cplusplus
extern "C"{
#endif

/* 探测周期默认值,单位ms,使用全局变量定义而不是宏主要是为了ST测试方便 */
extern ULONG g_ulDefaultDetectIntervar;  

/* 对端超时检测时间,5个探测周期             */
extern ULONG g_ulDefaultlostLinkTime;

/* 环回启动/终止命令响应超时时间,单位ms     */
extern ULONG g_ulLbWaitRspTime;

/* 3AH模块的IFNET组件功能虚表指针 */
extern struct IIF_IFNET_ComIntFUNVtbl          *g_pstOam3ahIfnetFunTable;

/* 3AH模块的trunk组件功能虚表指针 */
extern struct IIF_COMP_TRUNK_ComIntFUNVtbl     *g_pstOam3ahTrunkFunTable;

/* 3AH模块的etharp组件功能虚表指针 */
extern struct IIF_COMP_ETHERNET_ComIntCFGVtbl  *g_pstOam3ahEthCfgTable;

/* 3AH模块L2IF功能虚表指针 */
extern struct IIF_COMP_L2IF_ComIntFUNVtbl *g_pstoam3ahL2ifIntFunTbl;

/* 3AH模块vrrp功能虚表指针 */
extern struct IIF_COMP_VRRP_ComIntCFGVtbl *g_pstoam3ahVrrpCfgTbl;

/*Added by r62469 for defect agcdefg*/
/* 3AH模块的SyncE组件功能虚表指针 */
extern struct IIF_COMP_SYNCE_ComIntFUNVtbl     *g_pstOam3ahSyncEFunTable;

/* 获取底层错帧的函数指针 */
extern GET_PHY_ERROR_FRAME_HOOK_FUNC g_pfGetPhyErrFrm;
    
/* 下发周期事件参数的函数指针 */
extern SET_LINK_EVENT_WINTHRSH_HOOK_FUNC g_pfSetLinkEvtParam;

/* Modified by z00208058/w00207740, 3AH链路事件窗口和门限规格扩展, 2012/5/12 */
/* 支持64位下发周期事件参数的函数指针 */
extern SET_LINK_EVENT_WINTHRSH_EX_HOOK_FUNC g_pfSetLinkEvtParamEx;

/* 环回发起端报文接收处理钩子 */
extern LBINPUT_HOOK_FUNC       g_pfLbRemoteInputFunc;

/* 环回响应端报文接收处理钩子 */
extern LBINPUT_HOOK_FUNC       g_pfLbLocalInputFunc;

extern OAM3AH_ORG_SPEC_NOTIFY_HOOK_FUNC g_pfOrgSpecNotify;

/* 慢协议多播physical地址 */
extern UCHAR g_aucSlowProtocolMacAddr[MACADDRLEN];

/* 3AH模块信息 */
extern OAM3AH_MOD_INFO_S g_stOam3ahModInfo;

/* 3AH接口控制块链表   */
extern DLL_S *g_pst3ahPortInfoList;

/* 报文处理时延测试注册函数 */
extern DEALPKT_TIMETEST__HOOK_FUNC g_pfDealPktTimeTest;

/* 华为physical地址段,填充到信息TLV的OUI字段中   */
extern UCHAR g_aucHuaweiOui[][3];

/* OAMPDU中verndor specific information 字段初始值 */
extern ULONG g_ulVendorSpecInfo;

/* 3ah中用到以太广播地址 */
extern UCHAR g_szEtherBroadcastAddr_3ah[MACADDRLEN];

/* 保存3AH首次协商不通过对外告警的时间 */
extern ULONG g_ulOam3ahNegTime;

/* 首次协商不通过对外告警定时器ID*/
extern ULONG g_ulOam3ahNegTimerId;

/* 首次协商不通过对外告警的物理定时器周期 5s */
/* 用户配置的协商告警时间必须是5s的倍数 */
extern ULONG g_ulOam3ahNegPhyTimer;

/*Added by wangtong207740, DTS2012102202389 ,设置是否处理带VLAN的OAMPUD, 2012/10/22 */
extern ULONG g_ulOam3ahPktVlanSwitch;

/*Added by wangtong207740, MBSC要求3AH主备标记不影响接口物理状态, 2012/11/14 */
extern ULONG g_ulOam3ahBoardStateSwitch;

extern ULONG g_ulOam3ahWarnTraceFlag;

#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif      /* end of _3AH_VAR_H_   */

