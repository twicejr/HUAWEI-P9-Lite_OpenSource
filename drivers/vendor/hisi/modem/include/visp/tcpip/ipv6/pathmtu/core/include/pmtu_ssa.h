
#ifndef _IP6_PMTU_SSA_H
#define _IP6_PMTU_SSA_H

#ifdef  __cplusplus
extern "C"{
#endif


VOID  IP6_PMTU_ActualAgeTimeout(PMTU_ENTRY_S *pstPMTUEntry, ULONG ulMultiIndex);
ULONG IP6_PMTU_DeleteNotUsed (const PMTU_ENTRY_S *pstPMTUEntry);
ULONG IP6_PMTU_EV_OnReceivedEvent_IPC        (UCHAR *pData);
ULONG IP6_PMTU_Synchronize (UCHAR *pData, ULONG ulLen);
VOID  IP6_PMTU_EV_OnReceivedEvent_Cachetimeout (VOID);
VOID  IP6_PMTU_EV_OnReceivedEvent_Agetimeout (VOID);
VOID  IP6_PMTU_HotInsertProc (ULONG ulSlot);
/*Changed for VISPV1R7 integration by wan, 2008-05-02*/


#ifdef  __cplusplus
}
#endif

#endif

