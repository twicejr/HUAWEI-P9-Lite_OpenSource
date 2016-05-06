
#ifndef _IP6_PMTUCFG_H
#define _IP6_PMTUCFG_H

#ifdef  __cplusplus
extern "C"{
#endif

ULONG IP6_PMTU_ModifyGlobalAgeTime (USHORT usAgetime);

ULONG IP6_PMTU_SetResSpecs (SPECS_RES_VALUE_S  *pstResSpecs);
ULONG IP6_PMTU_SetDefAgetime (USHORT usAgetime);
ULONG IP6_PMTU_SetPmtu (IN6ADDR_S *pstDA, ULONG ulZoneid, ULONG ulPmtu);
ULONG IP6_PMTU_DeleteMatchingEntry (IN6ADDR_S stDA,
                                    ULONG ulZoneid, ULONG ulFlag);
ULONG IP6_PMTU_DeleteAllEntries (VOID);
ULONG IP6_PMTU_GetFirst (UINTPTR ulHandle, PMTU_CLI_DISPLAY_S *pstCLIDisplay,
                         ULONG *pulMultiIndex);
ULONG IP6_PMTU_GetNext (ULONG *pulMultiIndex,
                        PMTU_CLI_DISPLAY_S *pstCLIDisplay,
                        UINTPTR ulWaitListHandle);
ULONG IP6_PMTU_SearchObj (IN6ADDR_S *pstDA, ULONG ulZoneid,
                          PMTU_CLI_DISPLAY_S *pstCLIDisplay);
ULONG IP6_PMTU_DefaultMTU (IN6ADDR_S *pstDA, ULONG ulZoneid);
VOID  IP6_PMTU_Mindex_GetNext (ULONG *pulMiltiIndex, ULONG **ppulMindex);
ULONG IP6_PMTU_OpenTable (UINTPTR *pulUserHandle);
ULONG IP6_PMTU_CloseTable (UINTPTR *pulUserHandle);
ULONG IP6_PMTU_ClearPMTUEntries (ULONG ulType);
ULONG IP6_PMTU_GetPathMTU (IN6ADDR_S *pstDA, ULONG ulZoneid, ULONG *pulPmtu);

/* Begin :Defect ID: D01006,
   Reason :Initial, Max Mtu change for Pos, GE interfaces*/
ULONG IP6_PMTU_SetMaxMtu (ULONG ulMaxMtu);
ULONG IP6_PMTU_GetResSpecs (SPECS_RES_VALUE_S  *pstResSpecs);
ULONG IP6_PMTU_GetTotalEntries (ULONG ulFlag, ULONG *pulTotalEntries);
ULONG IP6_PMTU_GetDefAgetime (USHORT *pusAge);
#ifdef  __cplusplus
}
#endif

#endif

