/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              acl6_sh.h
*
*  Project Code: VISPV1R8
*   Module Name:   
*  Date Created: 
*        Author: 
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
        
*
*******************************************************************************/

#ifndef _ACL6_SH_H_
#define _ACL6_SH_H_

#ifdef  __cplusplus
extern "C"{
#endif

extern VOID ACL6_BEGIN_PT(VOID);
extern VOID ACL6_END_PT(VOID);
extern VOID ACL6_WaitListDelFromList(VOID *pData);
extern ULONG ACL6_SH_BasicToString(CHAR * szOut, INT32 iLen, ACL6_BASIC_CONTENT_INFO_S *pContentInfo);
extern ULONG ACL6_SH_AdvToString(CHAR *szOut, INT32 iLen, ACL6_ADVANCE_CONTENT_INFO_S *pContentInfo);
extern ULONG ACL6_SH_IfBaseToString(CHAR * szOut, INT32 iLen, ACL6_IFBASED_CONTENT_INFO_S *pContentInfo);

extern VOID ACL6_GetConfig(ACL6CONFIG_S* pstAclconfig);
extern ULONG ACL6_GetMatchedACLItem(MBUF_S *pstMBuf, ULONG ulGroupNum, ACL6_Item* pstFlow);
extern BOOL_T ACL6_MatchACLItem (ULONG ulACLNumber, ACL6_Item * pstFlow);
extern ULONG  ACL6_ClassifyByAclItemInfo(ULONG ulACLNumber, ACL6_Item * pstFlow,
         ACL6_CLASSIFY_IP_OUT_S* pstAcl6_ClassifyOut);
extern VOID ACL6_Core_GetMatchItemInfo(ACL6_Item *pstFlow,
                                         IP6PACKETINFO_S *pstMatchInfo);
extern ULONG ACL6_ClassifyInMBufByNumber(MBUF_S *pMBuf, ULONG ulGroupNum);
extern BOOL_T ACL6_ClassifyInMBufByItem(MBUF_S * pMBuf, ACL6_Item * pItem);
extern BOOL_T ACL6_ClassifyMBufByItem(MBUF_S *pstMBuf, ACL6_Item *pstFlow);
extern ULONG  ACL6_GetFlowOfFirstRule(ULONG ulListNumber, ACL6_Item *pstFlow);
extern ULONG ACL6_RefreshAclRegister(PF_ACL6_REFRESHCALLBACK pfFunc, ULONG ulModId);
extern BOOL_T ACL6_Sh_ClassifyMBufByItem(MBUF_S* pstMBuf, ACL6_Item *pstFlow, ULONG ulFlag);
extern BOOL_T ACL6_Compare_MBufWithItem(IP6PACKETINFO_S *pstMatchInfo, ACL6_Item *pstFlow);
extern BOOL_T ACL6_Compare_InMBufWithItem(IP6PACKETINFO_S *pstMatchInfo, ACL6_Item *pstFlow);

/* Added by y00176567, at 2011-05-26. 修改原因: 消除VC三级告警 */
extern ULONG ACL6_ClassifyMBufByNumber (MBUF_S *pstMBuf,ULONG ulAclNum);
extern ULONG ACL6_IsACLNodeExistByNumber (ULONG ulNumber, ULONG ulSubitem);


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif    /* end of _ACL6_SH_H_ */
