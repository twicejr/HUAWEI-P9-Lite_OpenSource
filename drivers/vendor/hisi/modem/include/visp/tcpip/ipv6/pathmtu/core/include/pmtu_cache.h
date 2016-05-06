

#ifndef _IP6_PMTUCACHE_H
#define _IP6_PMTUCACHE_H

#ifdef  __cplusplus
extern "C"{
#endif

ULONG IP6_PMTU_DelSBYIO (ULONG ulMultiIndex);
ULONG IP6_PMTU_AddSBYIO (ULONG ulMultiIndex, IN6ADDR_S stDA, ULONG ulZoneid);
ULONG IP6_PMTU_DelAllSBYIO (VOID);
ULONG IP6_PMTU_DelAllStaticSBYIO (VOID);
ULONG IP6_PMTU_DelAllDynamicSBYIO (VOID);
VOS_BOOL  IP6_PMTU_ReserveEntry (const PMTU_ENTRY_S *pstPmtuEntry);
ULONG IP6_PMTU_ResetPMTUEntries(PMTU_ENTRY_S *pstPMTUEntry);
void *IP6_PMTU_SearchNode (void *pSearchNode, void *pHead, ULONG ulType);
ULONG IP6_PMTU_AddPMTUEntry (IN6ADDR_S stDA, ULONG ulZoneid, ULONG ulMTU,
                             USHORT usAgetime, UCHAR ucControlflag,
                             LONG ulSocketid, ULONG ulTaskid,
                             PMTU_ENTRY_S **ppstPmtuEntry);
ULONG IP6_PMTU_ModifyEntry (PMTU_ENTRY_S *pstPMTUEntry,
                            LONG lSocketid, ULONG ulTaskid,
                            ULONG ulEvent, ULONG ulFlag);
ULONG IP6_PMTU_AddNode (void *pAddNode, void *pHead, ULONG ulType);
ULONG IP6_PMTU_AddEntry (PMTU_ENTRY_S *pstPMTUEntry, IN6ADDR_S stDA,
                         ULONG ulZoneid, ULONG ulMTU, USHORT usAgetime,
                         UCHAR ucControlflag, LONG ulSocketid, ULONG ulTaskid);
ULONG IP6_PMTU_DeleteNode (void *pDelNode, void *pHead, ULONG ulType);
ULONG IP6_PMTU_NotifySocketsPMTUDelete (PMTU_ENTRY_S *pstPmtuEntry);
ULONG IP6_PMTU_DeleteEntry (PMTU_ENTRY_S *pstPMTUEntry, ULONG ulMultipleIndex);
ULONG IP6_PMTU_DeleteLeastUsedEntry (VOID);
ULONG IP6_PMTU_AddSockidEntry (LONG lSocketid, ULONG ulTaskid, IN6ADDR_S stDA,
                               ULONG ulZoneid);
ULONG IP6_PMTU_DeleteSockidEntry (LONG lSocketid, ULONG ulTaskid,
                                   IN6ADDR_S stDA, ULONG ulZoneid);


#ifdef  __cplusplus
}
#endif

#endif


