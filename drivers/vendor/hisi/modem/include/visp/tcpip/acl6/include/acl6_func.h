/*************************************************************************
 *
 *              Copyright 2009, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              acl6_func.h
 *
 *  Project Code: VISP1.8
 *   Module Name: ACL6
 *  Date Created: 
 *        Author: 
 *   Description: 
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 ************************************************************************/
#ifndef _ACL6_FUNC_H_
#define _ACL6_FUNC_H_

#ifdef  __cplusplus
extern "C" {
#endif

/* acl6_api.c ÐÅºÅÁ¿PVº¯Êý */
extern VOID *TCPIP_Malloc(ULONG ulInfo, ULONG ulSize);
extern ULONG TCPIP_Free(VOID* pBuf);

/* functions in acl6.c */
extern ACL6_GROUP_S *ACL6_Core_GetGroup(ULONG ulGroupIndex);
extern VOID ACL6_Core_RebuildRuleIndex(ACL6_GROUP_S *pstGroup);
extern ULONG ACL6_Core_GetTypeIDByIndex(ULONG ulGroupIndex, ULONG *pulTypeID);
extern ULONG ACL6_Core_GroupIndexIsValid(ULONG ulGroupIndex);
extern VOID * ACL6_GetNextGroupInfoByFilter(VOID *pFilter,VOID *pCurEntry);
extern VOID *ACL6_GetNextACLRuleByFilter(VOID *pFilter,VOID *pCurEntry);
extern ULONG ACL6_Core_CheckRuleIsEmpty(ACL6_GROUP_S *pstGroup, ULONG ulRuleIndex);
extern ULONG ACL6_Core_CheckGroupRuleExist(ULONG ulGroupIndex, ULONG ulRuleIndex);
extern ACL6_TYPE_S *ACL6_Core_GetType(ULONG ulTypeID);
extern ULONG ACL6_Core_ClearMatchStat(ACL6_FILTER_S *pstACL6Filter);
extern ULONG ACL6_Core_GetGroupInfo(ULONG ulGroupIndex, ACL6_GET_GROUP_INFO_S *pstGroupInfo);
extern ULONG ACL6_Core_GetRuleInfo(ULONG ulGroupIndex, ULONG ulRuleIndex, ACL6_RULE_INFO_OUT_S *pstRuleInfo);
extern ACL6_RULE_NODE_S *ACL6_Core_GetRule(ACL6_GROUP_S *pstGroup, ULONG ulRuleIndex);
extern VOID ACL6_Core_OutPutRuleInfo(ACL6_GROUP_S *pstGroup, 
                                              ACL6_RULE_NODE_S *pstRule, 
                                              ACL6_RULE_INFO_OUT_S *pstRuleInfo);
extern VOID ACL6_Core_IFDelete(ULONG ulIfIndex);
extern ULONG ACL6_Core_ClassifyByIpInfo(ACL6_CLASSIFY_IP_IN_S* pstAcl6_ClassifyIn,
                                                 ACL6_CLASSIFY_IP_OUT_S* pstAcl6_ClassifyOut, ULONG ulFlag);
extern ULONG ACL6_Core_ClassifyByIfInfo(ACL6_CLASSIFY_IF_IN_S* pstAcl6_ClassifyIn,
                                                ACL6_CLASSIFY_IF_OUT_S* pstAcl6_ClassifyOut);

/* functions in acl6_oper.c */
extern ULONG ACL6_Core_B_IsEqual(VOID *p1, VOID *p2);
extern ULONG ACL6_Core_B_IsBefore (VOID *p1, VOID *p2);
extern ULONG ACL6_Core_B_HaveIt(VOID *pRule, VOID *pPackInfo);
extern VOID *ACL6_Core_B_CreateNode();
extern VOID ACL6_Core_ReleaseNode(VOID * pContent);
extern ULONG ACL6_Core_A_IsEqual(VOID *p1, VOID* p2);
extern ULONG ACL6_Core_A_IsBefore (VOID *p1, VOID *p2);
extern ULONG ACL6_Core_A_HaveIt(VOID *pRule, VOID *pPackInfo);
extern VOID *ACL6_Core_A_CreateNode();
extern ULONG ACL6_Core_IF_IsEqual(VOID *p1, VOID *p2);
extern ULONG ACL6_Core_IF_IsBefore (VOID *p1, VOID *p2);
extern ULONG ACL6_Core_IF_HaveIt(VOID *pRule, VOID *pPackInfo);
extern VOID *ACL6_Core_IF_CreateNode();

/* functions in acl6_group.c */
extern ULONG ACL6_Core_ManageGroup(ACL6_CFG_MANAGEGROUP_S *pstManageGroup);

/* functions in acl6_rule.c */
extern ULONG ACL6_Core_ManageAdvRule(ACL6_CFG_ADV_RULE_S* pstAcl6_AdvRule);
extern ULONG ACL6_Core_GetRuleSum(VOID);
extern VOID ACL6_Core_DeleteAllRule(ACL6_GROUP_S *pstGroup);
extern ULONG ACL6_Core_ManageIfBasedRule(ACL6_CFG_IFBASED_RULEINFO_S* pstAcl6_IfBaseRule);
extern ULONG ACL6_Core_DeleteRule(ACL6_GROUP_S  *pstGroup, ULONG ulRuleIndex);
extern ULONG ACL6_Core_ManageBasicRule(ACL6_CFG_BASIC_RULE_S * pstAcl6_BaseRule);

extern VOID ACL6_Core_GetMatchInfo(ACL6_CLASSIFY_IP_IN_S* pstAcl6_ClassifyIn,
                                     IP6PACKETINFO_S *pstMatchInfo);
extern VOID ACL6_Update_RegCallBacks(ULONG ulGroupId, ULONG ulRuleId, ULONG ulEventType);

#ifdef  __cplusplus
}
#endif


#endif
