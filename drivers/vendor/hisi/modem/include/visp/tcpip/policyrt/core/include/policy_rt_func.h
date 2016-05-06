
#ifndef _POLICY_RT_FUNC_H_
#define _POLICY_RT_FUNC_H_

#ifdef __cplusplus
extern "C" {
#endif
ULONG PolicyRt_init (VOID);

ULONG PolicyRt_ValidateVrfIndex(ULONG ulVrfIndex);
ULONG PolicyRt_CreatePolicyGroup(POLICYRT_CFG_POLICY_S *pstPolicy);
ULONG PolicyRt_DeletePolicyGroup(POLICYRT_CFG_POLICY_S *pstPolicy);
ULONG PolicyRt_CreatePolicyNode(POLICYRT_CFG_NODE_S *pstNode);
ULONG PolicyRt_DeletePolicyNode(POLICYRT_CFG_NODE_S *pstNode);
ULONG PolicyRt_UpdateMatchData(POLICYRT_CFG_MATCH_S *pstCfgMatch);
ULONG PolicyRt_AddOrUpdateApplyItem(POLICYRT_NODE_S *pstPolicyNode, POLICYRT_CFG_APPLY_S *pstCfgApply);
ULONG PolicyRt_DeleteApplyItem(POLICYRT_NODE_S *pstPolicyNode, POLICYRT_CFG_APPLY_S *pstCfgApply);
ULONG PolicyRt_UpdateApplyData(POLICYRT_CFG_APPLY_S *pstCfgApply);
ULONG PolicyRt_SetAdminStatusToNode(POLICYRT_ADMIN_NODE_S *pstNode);
extern ULONG PolicyRt_PPI_Update(ULONG ulCmd, ULONG ulVrfIndex, ULONG ulPolicyId, POLICYRT_NODE_S *pstNode);
ULONG PolicyRt_FinishConfigNode(POLICYRT_FIN_CFG_S *pstCfgLoad);
VOID PolicyRt_FreePolicyGroup(POLICY_CNTRL_BLK_S *pstPolicyGroup);
VOID POLICYRT_DeleteFromNextHopList(POLICY_CNTRL_BLK_S *pstPolicyGroup, POLICYRT_NODE_S *pstPolicyNode);
ULONG POLICYRT_ProcessOnlyNextHopApply(POLICYRT_FIN_CFG_S *pstCfgLoad, POLICYRT_NODE_S *pstPolicyNode);
VOID POLICYRT_ProcessUpEvent(ULONG ulIfIndex);
VOID POLICYRT_ProcessDownEvent(ULONG ulIfIndex);
ULONG POLCYRT_SearchSrcRoute( SRC_RT_PKT_S *pstPktInfo, SRC_RT_SEARCH_S *pstOutput);
ULONG POLICYRT_GetTranMatchCount(POLICYRT_NODE_S *pstNode,
                                            ULONG *pulLow32, ULONG *pulHigh32);
ULONG POLICYRT_ProcessOnlyOutIntf(POLICYRT_FIN_CFG_S *pstCfgLoad,
                                POLICYRT_NODE_S *pstPolicyNode, IFNET_S *pstIf);

#ifdef __cplusplus
}
#endif   /* end of __cplusplus */

#endif   /* end of _POLICY_RT_FUNC_H_ */

