#ifndef _IPB_IR_VISP_ACL_MAPP_H_
#define _IPB_IR_VISP_ACL_MAPP_H_

#ifdef    __cplusplus
extern "C"{
#endif



#include "common/visp/VISP_IR_ACL.h"  /*Common headfile visp provided*/

extern ULONG VRPAdapt_ACL_NumberUpdate( ULONG* pulAclNumber);
extern ULONG VRPAdapt_ACL_IsACLNodeExistByNumber( ULONG ulNumber, ULONG ulSubitem);
extern BOOL_T VRPAdapt_ACL_MatchACLItem ( ULONG ulACLNumber, ACL_Item * pstFlow );
extern ULONG VRPAdapt_ACL_GetMatchedACLItem ( MBUF_S *pMBuf, ULONG ulACLNumber, ACL_Item * pstFlow );
extern ULONG VRPAdapt_ACL_ClassifyInMBufByNumber ( MBUF_S *pMBuf, ULONG ulNumber );
VOID VRPAdapt_VRPAdapt_ACL_GetConfig(VOID * pstAclconfig);
extern BOOL_T  VRPAdapt_ACL_ClassifyInMBufByItem(MBUF_S *pMBuf, ACL_Item *pItem);
extern BOOL_T  VRPAdapt_ACL_ClassifyMBufByItem(MBUF_S *pMBuf, ACL_Item *pItem);
extern ULONG VRPAdapt_ACL_ClassifyMBufByNumber ( MBUF_S *pMBuf, ULONG ulNumber );
extern ULONG  VRPAdapt_ACL_GetFlowOfFirstRule(ULONG ulListNumber,
                                                            ACL_Item *pstFlow);
extern ULONG VRPAdapt_ACL_RefreshAclRegister(PF_ACLREFRESHCALLBACK pfFunc,
                                                                ULONG ulModId);
/*IKE/IPSEC: PICO Wi-Max DSCP changes*/

/* Get Flow information with the DSCP value configured, If DSCP is not
    configured the following API returns INVALID DSCP value (0xFF)*/
extern ULONG VRPAdapt_ACL_GetFlowOfFirstRulewithDSCP(ULONG ulListNumber,
                                            ACL_Item *pstFlow, ULONG *pulDscp);

/* The following API matches the all parameters in the MBUF except DSCP value
    configured */
extern ULONG VRPAdapt_ACL_ClassifyInMBufByNumberWithoutDSCP(MBUF_S *pMBuf,
                                                            ULONG ulGroupNum);

/* The following API matches the all parameter in the flow, except DSCP
    value configured */
extern BOOL_T VRPAdapt_ACL_MatchACLItemWithoutDSCP(ULONG ulACLNumber,
                                                        ACL_Item * pstFlow);

/*IKE/IPSEC: End of PICO Wi-Max DSCP changes*/

#define IPB_IR_ACLNUM_UPDATE(pulACLNumber)  \
    VRPAdapt_ACL_NumberUpdate(pulACLNumber)

#define IPB_IR_ACL_ISACLNODE_EXISTBYNUMBER(ulNumber,ulSubitem) \
    VRPAdapt_ACL_IsACLNodeExistByNumber(ulNumber,ulSubitem)

#define IPB_IR_ACL_CLASSIFYINMBUFBYITEM(pMBuf,pItem)\
    VRPAdapt_ACL_ClassifyInMBufByItem(pMBuf,pItem)

#define IPB_IR_ACL_CLASSIFYINMBUFBYNUMBER(pMBuf,ulNumber)\
   VRPAdapt_ACL_ClassifyInMBufByNumber(pMBuf,ulNumber)

#define IPB_IR_ACL_CLASSIFYMBUFBYITEM(pMBuf,pItem)\
    VRPAdapt_ACL_ClassifyMBufByItem(pMBuf,pItem)

#define IPB_IR_ACL_CLASSIFYMBUFBYNUMBER(pMBuf,ulNumber)\
    VRPAdapt_ACL_ClassifyMBufByNumber(pMBuf,ulNumber)

#define IPB_IR_ACL_MATCHACLITEM(ulACLNumber,pstFlow)\
    VRPAdapt_ACL_MatchACLItem(ulACLNumber,pstFlow)

#define IPB_IR_ACL_GETMATCHEDACLITEM(pMBuf,ulACLNumber,pstFlow)\
    VRPAdapt_ACL_GetMatchedACLItem(pMBuf,ulACLNumber,pstFlow)

#define IPB_IR_ACL_GETCONFIG(pstAclconfig)  \
    VRPAdapt_ACL_GetConfig(pstAclconfig)

#define IPB_IR_ACL_GETFLOWOFFIRSTRULE(ulListNumber, pstFlow)\
    VRPAdapt_ACL_GetFlowOfFirstRule(ulListNumber, pstFlow)

#define IPB_IR_ACL_REFRESHSECACLREGISTER(pfFunc, ulModId)  \
    VRPAdapt_ACL_RefreshAclRegister(pfFunc, ulModId)

/*IKE/IPSEC: End of PICO Wi-Max DSCP changes*/

#define IPB_IR_ACL_GETFLOWOFFIRSTRULEWITHDSCP(ulListNumber, pstFlow, pulDscp)\
    VRPAdapt_ACL_GetFlowOfFirstRulewithDSCP((ulListNumber), (pstFlow), \
                                                                (pulDscp))

#define IPB_IR_ACL_CLASSIFYINMBUFBYNUMBERWITHOUTDSCP(pMBuf,ulNumber)\
   VRPAdapt_ACL_ClassifyInMBufByNumberWithoutDSCP((pMBuf),(ulNumber))

/*IKE/IPSEC: End of PICO Wi-Max DSCP changes*/

#define IPB_IR_ACL_ITEM_S     ACL_Item
#define IPB_IR_ACLCONFIG_S  ACLCONFIG_S

#define IPB_IR_ACL_INVALID_SUBNO  ACL_INVALID_SUBNO

#define IPB_IR_ACL_UPDATE_GROUP_DELETE      ACL_UPDATE_GROUP_DELETE
#define IPB_IR_ACL_UPDATE_RULE_DELETE       ACL_UPDATE_RULE_DELETE
#define IPB_IR_ACL_UPDATE_RULE_MODIFY       ACL_UPDATE_RULE_MODIFY
#define IPB_IR_ACL_UPDATE_RULE_ADD          ACL_UPDATE_RULE_ADD
#define IPB_IR_ACL_UPDATE_GROUP_DELETE_ALL  ACL_UPDATE_GROUP_DELETE_ALL

#ifdef __cplusplus
}
#endif        /* end of __cplusplus */


#endif  /* end of _IPB_IR_VISP_ACL_MAPP_H_ */


