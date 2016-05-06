

#ifndef _ATK_CFG_H_
#define _ATK_CFG_H_

/*In case of the C++.*/
#ifdef  __cplusplus
extern "C" {
#endif


ULONG ATK_SetWarningSwitch(ULONG ulSwitch, ULONG ulMaxThreshold, ULONG ulMinThreshold);


ULONG ATK_SetLargeIcmpLen(ULONG ulMaxSize);


ULONG ATK_GetCfgInfo(ATTACK_CFG_INFO_S *pstAtkCfgInfo);


ULONG ATK_GetStats(TCPIP_ATTACKSTAT_S *pstAtkStat);



ULONG ATK_GetStatsByIf(ULONG ulIfIndex, TCPIP_ATTACKSTAT_S *pstAtkStat);


ULONG ATK_ClrStatsByIf(ULONG ulIfIndex, ULONG ulOper);


ULONG ATK_ClrStats();


VOID ATK_ShowStats(const TCPIP_ATTACKSTAT_S *pstAtkStat);

/*In case of the C++.*/
#ifdef  __cplusplus
}
#endif


#endif  /* ATK_CFG_H_ */

