
#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _I_ATK_H_
#define _I_ATK_H_


DECLARE_INTERFACE(IIF_COMP_ATK_ComIntCFG)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfATK_InitCom)();
    METHOD_(ULONG, pfATK_SetModuleInfo)(ATK_MOD_INFO_S  *pstMInfo);
    METHOD_(ULONG, pfATK_SetWarningSwitch)(ULONG ulSwitch, ULONG ulMaxThreshold, ULONG ulMinThreshold);
    METHOD_(ULONG, pfATK_SetLargeIcmpLen)(ULONG ulMaxSize);
    METHOD_(ULONG, pfATK_GetCfgInfo)(ATTACK_CFG_INFO_S *pstAtkCfgInfo);
    METHOD_(ULONG, pfATK_GetStats)(TCPIP_ATTACKSTAT_S *pstAtkStat);
    METHOD_(ULONG, pfATK_GetStatsByIf)(ULONG ulIfIndex, TCPIP_ATTACKSTAT_S *pstAtkStat);
    METHOD_(ULONG, pfATK_ClrStatsByIf)(ULONG ulIfIndex, ULONG ulOper);
    METHOD_(ULONG, pfATK_ClrStats)();
};

DECLARE_INTERFACE(IIF_COMP_ATK_ComIntFUN)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfATK_AddAtkStat)(ULONG ulIfIndex, ULONG ulAttackType, IP_S *pstIp);
    METHOD_(ULONG, pfATK_AddIcmpJumbogramStat)(ULONG ulIfIndex, ULONG ulLen, IP_S *pstIp);
    METHOD_(VOID, pfATK_IfDelete_Notify)(ULONG ulIfIndex);
    METHOD_(ULONG, pfATK_IsSwitchOpen)();
};

#endif  /*  _I_ATK_H_  */

#ifdef  __cplusplus
}
#endif

