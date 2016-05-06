
#ifndef _IP6_PMTUICMPPROC_H
#define _IP6_PMTUICMPPROC_H

#ifdef  __cplusplus
extern "C"{
#endif

ULONG  IP6_PMTU_ICMP_Input (IP6_CTLPARAM_S *pstTooBigNotify);
VOID IP6_PMTU_IncreaseAccessCount (PMTU_ENTRY_S *pstPmtuEntry);

/* Defect ID: BYAD011814,Reason   : Component issues*/
ULONG IP6_PMTU_TooBigHandler (TOO_BIG_INFO_S *pstTooBigInfo);

VOID IP6_PMTU_NotifySocketsPMTUChange (PMTU_ENTRY_S *pstPmtuEntry,
                    ULONG ulPmtuChanged, LONG lSocketid, ULONG ulTaskid);

#ifdef  __cplusplus
}
#endif

#endif

