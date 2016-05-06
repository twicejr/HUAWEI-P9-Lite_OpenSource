/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ethvln_cfg.h
*
*  Project Code: VISPV100R007
*   Module Name: Ethvlan  
*  Date Created: 2008-08-01
*        Author: qinyun(62011)
*   Description: ethvln_cfg.h
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME               DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-08-01   qinyun(62011)      Create the first version.
*******************************************************************************/

#ifndef _ETHVLAN_CFG_H
#define _ETHVLAN_CFG_H

#ifdef  __cplusplus
extern "C"{
#endif

extern BOOL_T ETHVLAN_ResetEncapFlag (IFNET_S *pIf);

extern ULONG  ETHVLAN_ClearVlanCounter(ULONG ulIfindex ,USHORT usVID);

extern ULONG ETHVLAN_AddSubIfVID(ULONG ulSubIndex,USHORT usLowVID,USHORT usHighVID,ULONG ulEncapType);
extern ULONG ETHVLAN_DelSubIfVID(ULONG ulSubIndex,USHORT usLowVID ,USHORT usHighVID,ULONG ulEncapType);
extern ULONG ETHVLAN_OpenDebugPacket(ULONG ulIfIndex,USHORT usDebugVID);
extern ULONG ETHVLAN_CloseDebugPacket(ULONG ulIfIndex,USHORT usDebugVID);
extern ULONG ETHVLAN_InitPortInfo (ETHARP_MTSOFTC_S *pBufMtSoftC);
extern VOID ETHVLAN_ClearPortInfo (ETHARP_MTSOFTC_S *pBufMtSoftC);
extern VOID ETHVLAN_DelVidNode(ETHVLAN_VID_NODE_S * pNode) ;
extern ULONG ETHVLAN_VlanCheck(IFNET_S *pstIf);
extern VOID * ETHVLAN_GetNextEntryByFilter(VOID *pFilter,VOID *pCurEntry);
extern BOOL_T ETHVLAN_HaveVid (ETHARP_MTSOFTCSUB_S *pBufMtSoftC);
extern ULONG ETHVLAN_IsForbidIf(IFNET_S *pstIf);

/* Begin Add by zhaoyue00171897/shuxieliu00176784, at 2011-06-04. 修改原因: 支持VLAN配置不一致的告警 */
ULONG ETHVLAN_SetVlanConsistencyMonitor(ULONG ulSubIfIndex, ULONG ulMaxWarningNum);
ULONG ETHVLAN_GetVlanConsistencyMonitor(ULONG ulSubIfIndex, ULONG *pulMaxWarningNum);
ULONG ETHVLAN_DeleteVlanConsistencyWarning(ULONG ulSubIfIndex, ULONG ulLocalIPAddr, ULONG ulNeighbourIPAddr);
ULONG ETHVLAN_FindNodeFromList(ULONG ulLocalIPAddr, ULONG ulNeighbourIPAddr,
                                VLAN_CONSISTENCY_WARN_LIST_S *pstVlanWarningList, 
                                VLAN_CONSISTENCY_WARN_NODE_S **ppstExistWarningNode,
                                ULONG ulMatchMode);
VOID ETHVLAN_RemoveNodeFromList(VLAN_CONSISTENCY_WARN_LIST_S *pstVlanWarningList, VLAN_CONSISTENCY_WARN_NODE_S *pstCurWarningNode);
VOID ETHVLAN_VlanConsistencyWarningOutput(UCHAR ucEventType, UCHAR ucRecoverReason,
                                ETHVLAN_PORTINFO_S *pEthvlnInfo,
                                VLAN_CONSISTENCY_WARN_NODE_S *pstVlanWarningNode);
/* End Add by zhaoyue00171897/shuxieliu00176784, at 2011-06-04. 修改原因: 支持VLAN配置不一致的告警 */

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif 


