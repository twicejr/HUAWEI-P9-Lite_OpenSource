/************************************************************************
 *                                                                      *
 *                          pppc_eap_fun.h                              *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2010/07/05                                      *
 *  Author:             WANGYONG                                        *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           EAP模块私有函数说明                             *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 * Copyright 2000-2010 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
 *                     ALL RIGHTS RESERVED                              *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   这个文件包含了EAP模块所有私有函数的申明                            *
 *                                                                      *
 ************************************************************************/

#if( VRP_MODULE_LINK_PPP == VRP_YES )

#ifndef      _PPPC_EAP_FUNC_H_
#define      _PPPC_EAP_FUNC_H_

#ifdef      __cplusplus
extern "C" {
#endif        /* end of __cplusplus */

VOS_VOID PPPC_EAP_PeerProcessEvent
(
    VOS_UINT32                          ulPppId,
    PPPC_EAP_PEER_EVENT_ENUM_UINT16     enEvent,
    VOS_VOID                           *pData
);
VOS_VOID PPPC_EAP_PeerIdleIdentityReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
);
VOS_VOID PPPC_EAP_PeerNotifyReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
);
VOS_VOID PPPC_EAP_PeerIdleNak
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
);
VOS_VOID PPPC_EAP_PeerIdleAuthReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
);
VOS_VOID PPPC_EAP_PeerIdleSuccess
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
);
VOS_VOID PPPC_EAP_PeerIdleFailure
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
);
VOS_VOID PPPC_EAP_PeerTimeout(PPPINFO_S *pstPppInfo, VOS_VOID *pData);
VOS_VOID PPPC_EAP_PeerAuthAuthReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
);
VOS_VOID PPPC_EAP_PeerAuthNotifyAuthInd
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
);
VOS_VOID PPPC_EAP_PeerAuthNotifySuccess
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
);
VOS_VOID PPPC_EAP_PeerAuthNotifyFailure
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
);
VOS_VOID PPPC_EAP_PeerNotifyAuthReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
);
VOS_VOID PPPC_EAP_PeerClosingNotifyReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
);
VOS_VOID PPPC_EAP_PeerClosingAuthReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
);
VOS_VOID PPPC_EAP_PeerClosingAuthInd
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
);
VOS_VOID PPPC_EAP_PeerClosingSuccess
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
);
VOS_VOID PPPC_EAP_PeerClosingFailure
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
);
VOS_VOID PPPC_EAP_MD5_ProcessPkt
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstMethodOutput,
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPInput
);
VOS_VOID PPPC_EAP_InitMethod
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo
);
VOS_VOID PPPC_EAP_SendResponse(VOS_UINT32 ulPppId);
VOS_VOID PPPC_EAP_SyncState(PPPINFO_S *pstPppInfo);
VOS_VOID PPPC_EAP_RcvReqTimeout(VOS_UINT32 ulPppId);
VOS_VOID PPPC_EAP_DeleteTimer(PPPC_EAP_INFO_STRU *pstEapInfo);
VOS_VOID PPPC_EAP_Init(PPPINFO_S *pstPppInfo);
VOS_VOID PPPC_EAP_LowerDown(PPPINFO_S *pstPppInfo);
VOS_VOID PPPC_EAP_ReceiveEventFromCore (PPPINFO_S *pstPppInfo, VOS_UINT32 ulCmd, VOS_UINT8 *pPara);
VOS_VOID PPPC_EAP_ReceivePacket(PPPINFO_S *pstPppInfo, VOS_UINT8* pHead, VOS_UINT8* pPacket, VOS_UINT32 ulLen);
VOS_VOID PPPC_EAP_ReceiveRequest(PPPINFO_S *pstPppInfo, UCHAR *pPacket, UCHAR ucId, VOS_UINT32 ulLen);
VOS_VOID PPPC_EAP_ReceiveSuccess(PPPINFO_S *pstPppInfo, UCHAR *pPacket, UCHAR ucId, VOS_UINT32 ulLen);
VOS_VOID PPPC_EAP_ReceiveFailure(PPPINFO_S *pstPppInfo, UCHAR *pPacket, UCHAR ucId, VOS_UINT32 ulLen);

/*EAP 调试函数 */
VOS_VOID EAP_Debug_Event(PPPINFO_S* pstPppInfo, UCHAR ucEvent);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PPPC_EAP_FUNC_H_ */

#endif      /* #if( VRP_MODULE_LINK_PPP == VRP_YES ) */

