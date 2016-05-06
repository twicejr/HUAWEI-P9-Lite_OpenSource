/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              poec_var.h
 *
 *  Project Code: VISP1.5
 *   Module Name: PPPoE Client
 *  Date Created: 2003-01-11
 *        Author: liuhui
 *   Description: PPPoE Client模块Core部分私有全局变量的引用说明
 *                      其他任何地方不能再出现对私有全局变量的extern引用
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2003-01-11      liuhui          Create file
 *  2005-09-15      t45114          Modify  
 *  2006-03-30      liai            Adjust for D00660
 *  2006/04/21      liai            Adjust for D00865
 *   
 ************************************************************************/

#ifndef  _POEC_VAR_H_
#define  _POEC_VAR_H_

#if __cplusplus
extern "C"{
#endif


/* 全局PPPoE Client CB双向链表头接点 */
extern DLL_S  g_stPPPoEClientCB;

/* 全局PPPoE Session索引数组，下标为dialer bundle号码，内容为对应的Session控制块指针 */
extern UINTPTR  g_ulPPPoESessionIndexArray[MAX_BUNDLENUMBER + 1];

/* 全局BundleNumber数组 */
extern ULONG g_ulDialerBundleNumber[MAX_BUNDLENUMBER + 1];

/* 全局PPPoE Client模块调试开关 */
extern ULONG g_ulPoeClientDebugFlag;

/* POEC保活模式 */
extern ULONG g_ulCurrentPOECGRState;

/* 全局以太功能函数指针 */
extern struct IIF_COMP_ETHERNET_ComIntFUNVtbl  *g_pstEthernetComFunTable;

/* 全局PPP功能函数指针 */
extern struct IIF_COMP_PPP_ComIntFUNVtbl  *g_pstPoecPppComFunTable;

/* SAPRO module info & shell SSP API */
extern PPPOE_CLIENT_MOD_INFO_S        g_stPPPOEClientModInfo;
extern PPPOE_CLIENT_SHELL_CALLBACK_S  g_stPPPOEClientShellApi;

extern POEC_PHASE_NOTIFY g_pfPoecPhaseNotifyHook;

/* 基于Dialer接口的调试开关 */
extern ULONG g_aulPoecDialerDebugFlag[MAX_BUNDLENUMBER + 1];

#if __cplusplus
}
#endif

#endif 


