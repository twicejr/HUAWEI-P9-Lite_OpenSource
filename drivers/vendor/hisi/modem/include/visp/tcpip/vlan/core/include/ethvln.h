/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ethvln.h
*
*  Project Code: VISPV100R007
*   Module Name: Ethvlan  
*  Date Created: 2008-08-01
*        Author: qinyun(62011)
*   Description: ethvln.h
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME               DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-08-01   qinyun(62011)      Create the first version.
*******************************************************************************/
#ifndef _ETHVLN_H_
#define _ETHVLN_H_

#ifdef  __cplusplus
extern "C"{
#endif

typedef struct  tagETSNAP_8021Q_HDR  
{
    UCHAR                   ucHdrDstMacAddr[6]; /*目的physical地址              */
    UCHAR                   ucHdrSrcMacAddr[6]; /*源physical地址                */
    VLAN_DOT1QHDR_S         stDot1qHdr;         /* 802.1q header */
    USHORT                  usLen;              /*以太网幀长度             */
    UCHAR                   ucDSAP;             /* destination access point*/
    UCHAR                   ucSSAP;             /* source access point     */
    UCHAR                   ucCtrl;             /* control domain          */
    UCHAR                   ucORI[3];                              
    USHORT                  usType;             /*协议类型                 */
}ETHARP_ETSNAP_8021Q_HDR_S; 

extern ULONG ETHVLAN_Init(VOID);
extern VOID ETHVLAN_GetVlanNode(USHORT usVID,ULONG ifIndex,ETHVLAN_VID_NODE_S **ppVidNode);
extern ULONG ETHVLAN_Input(MBUF_S * pstMbuf,IFNET_S *pstIf);
/* extern ULONG ETHVLAN_Output(IFNET_S *pIf, MBUF_S * pstMBuf,USHORT usVID); */
extern ULONG ETHVLAN_Output(IFNET_S *pIf, MBUF_S * pstMBuf,USHORT usVID,ULONG *pulSndPkts);
extern ULONG ETHVLAN_InitPortInfo (ETHARP_MTSOFTC_S *pBufMtSoftC);

/* Begin Add by zhaoyue00171897/shuxieliu00176784, at 2011-06-04. 修改原因: 支持VLAN配置不一致的告警 */
extern VOID ETHVLAN_VlanConsistencyWarningProc(MBUF_S *pstMBuf, USHORT usVlanId, ULONG ulMainIfIndex,
                                               ULONG ulVlanSubIfIndex);
extern VOID ETHVLAN_VlanConsistencyWarningBegin(ETHVLAN_PORTINFO_S  *pEthvlnPortInfo, ULONG ulIfIndex, 
                                                USHORT usVlanId, ULONG ulSrcIp, ULONG ulDstIp);
extern ULONG ETHVLAN_VlanConsistencyWarningEnd(IFNET_S *pstSubtIf, ULONG ulLocalIP, ULONG ulNeighbourIP,
                                               ULONG ulMatchMode, UCHAR ucRecoverReason);
/* End Add by zhaoyue00171897/shuxieliu00176784, at 2011-06-04. 修改原因: 支持VLAN配置不一致的告警 */

/* Begin Add by y00176567/z00171897, at 2011-06-29. 修改原因: 增加VLAN一致性告警显示功能 */
VOID ETHVLAN_ShowVlanConsistencyWarningInfo(ULONG ulSubIfIndex);
ULONG ETHVLAN_OpenWtLstObject(UINTPTR *pulWaitListHandle, VLAN_CONSISTENCY_WARN_NODE_S *pstHeadList);
VOID *ETHVLAN_GetWtLstNext(VOID *pCur,VOID **ppNext);
ULONG ETHVLAN_GetWtLstEntry(UINTPTR ulWaitListHandle, VLAN_CONSISTENCY_WARN_NODE_S *pstFindWarningNode);
ULONG ETHVLAN_CloseWtLstObject(UINTPTR ulWaitListHandle);
/* End Add by y00176567/z00171897, at 2011-06-29. 修改原因: 增加VLAN一致性告警显示功能 */

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif /* end of  _ETHVLN_H*/

