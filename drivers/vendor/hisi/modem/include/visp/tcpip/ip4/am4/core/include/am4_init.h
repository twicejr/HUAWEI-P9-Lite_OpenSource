/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              am4_init.h
*
* Project Code: VISPV100R005
*  Module Name: AM4  
* Date Created: 2006-01-04
*       Author: Li LiXiang
*  Description: 声明了AM4中的初始化函数
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-04   Li LiXiang              Create
*  2006-04-21   Jiangtao                根据编程规范，对文件进行规范化整理 
*
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _AM4_INIT_H_
#define _AM4_INIT_H_

/* component info for am4 */
extern IP_AM4_MOD_INFO_S g_stIPAm4ModInfo;

/* point to vtable */
extern struct IIF_IPV4_IP_PP4_ComIntFUNVtbl * g_pstAm4Pp4Vtbl ;

extern struct IIF_IPV4_DHCP4C_ComIntFunVtbl* g_pstAm4Dhcpc4Vtbl;


extern AM4_SHELL_RM_CALLBACK_FUNC_PTR  g_pfAm4ShSrmCallback;

extern struct IIF_IFNET_ComIntFUNVtbl       * g_pstAM4ComIfFunVtbl;

/* Am4模块的DHCP4R组件功能虚表指针 */
extern struct IIF_COMP_DHCP4R_ComIntCFGVtbl *g_pstAm4Dhcp4rCfgTable;

extern struct IIF_IPV6_NATPT_ComINTF_V4STKVtbl *g_pstAm4NatptV4Stk;


ULONG IP_AM4_Init_Com();
ULONG IP_AM4_Activate_Com();
ULONG IP_AM4_SetModuleInfo(IP_AM4_MOD_INFO_S *pstMInfo );
ULONG IP_AM4_RegisterShSrmCallback(AM4_SHELL_RM_CALLBACK_FUNC_PTR pfShCallback);
ULONG IP_AM4_RegShSrmJudgeFun(AM4_SHELL_RM_FUNC_PTR *pfShCallback);

extern ULONG (*g_pfIpChangeNotifyBfd)(ULONG, ULONG, ULONG);
extern ULONG (*g_pfIpChangeNotifyPolicyRoute)(ULONG, ULONG, ULONG, ULONG);

/* Add by zhaoyue00171897/shuxieliu00176784, at 2011-06-04. 修改原因: 支持VLAN配置不一致的告警 */
ULONG IP_AM4_Ethvlan_VlanWarningHook_Register(IP_AM4_ETHVLN_VLANWARNING_HOOK_FUNC pfHookFunc);

#endif  /* end of _AM4_INIT_H_ */ 


#ifdef __cplusplus
}
#endif/* end of __cplusplus */

