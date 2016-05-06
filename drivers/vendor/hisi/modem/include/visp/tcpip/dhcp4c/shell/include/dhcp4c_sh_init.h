

#ifndef _DHCP4C_SH_INIT_H_
#define _DHCP4C_SH_INIT_H_


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/* dhcpc component SSA,CFG and Functional Interface pointers global access */
extern struct IIF_IPV4_DHCP4C_ComIntSSAVtbl     * g_pstDHCP4CComSSATable;
/* dhcpc component CFG Interface pointers global access */
extern struct IIF_IPV4_DHCP4C_ComIntCFGVtbl     * g_pstDHCP4CComCfgTable;
/* dhcpc component  Functional Interface pointers global access */
extern struct IIF_IPV4_DHCP4C_ComIntFunVtbl     * g_pstDHCP4CComFunTable;

/* 全局调试开关 */
extern ULONG           g_ulDHCP4CDebugFlag;
/*DHCP初始化信息*/
extern APP_INIT_INFO_S g_stDHCP4CAppInfo;

ULONG DHCP4C_RegApp ();
VOID  DHCP4C_SH_DeInit(VOID);
ULONG DHCP4C_SH_GlobalInit( );
ULONG DHCP4C_SH_Init();
VOID  DHCP4C_SH_TaskEntry(UINTPTR ulArg0, UINTPTR ulArg1, UINTPTR ulArg2, UINTPTR ulArg3);
VOID  DHCP4C_TaskMain();
VOID  DHCP4C_SetTaskId(ULONG ulTask);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif

