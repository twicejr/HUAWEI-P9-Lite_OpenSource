
#ifdef  __cplusplus
extern  "C"{
#endif
#ifndef _I_ATK_FUNC_H_
#define _I_ATK_FUNC_H_


VOID ATK_Sock_TimeCallBack(VOID *pArg);


ULONG ATK_AddAtkStat(ULONG ulIfIndex, ULONG ulAttackType, IP_S *pstIp);


ULONG ATK_AddIcmpJumbogramStat(ULONG ulIfIndex, ULONG ulLen, IP_S *pstIp);


ULONG ATK_DelAllStats();


VOID ATK_IfDelete_Notify(ULONG ulIfIndex);


ULONG ATK_AddAtkStat_PT(ULONG ulIfIndex, ULONG ulAttackType, IP_S *pstIp);


ULONG ATK_AddIcmpJumbogramStat_PT(ULONG ulIfIndex, ULONG ulLen, IP_S *pstIp);


VOID ATK_IfDelete_Notify_PT(ULONG ulIfIndex);


ULONG ATK_IsSwitchOpen();


#endif  /* I_ATK_FUNC_H_ */
#ifdef  __cplusplus
}
#endif


