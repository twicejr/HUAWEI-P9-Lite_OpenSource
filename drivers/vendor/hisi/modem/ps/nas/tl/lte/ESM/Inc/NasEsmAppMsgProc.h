/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmAppMsgProc.h
    Description :
    History     :
     1.丁丽 00128736      2008-09-01  Draft Enact
     2.祝义强 00138739    2008-09-10
     3.杨茜惠 00135146    2008-12-19  Modify  BA8D00752
     4.杨茜惠 00135146    2009-03-06  Modify  BA8D01127
******************************************************************************/

#ifndef _NASESMAPPMSGPROC_H
#define _NASESMAPPMSGPROC_H



/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

#define NAS_ESM_APP_ORIGIN_MID           (UE_MODULE_ESM_ID)              /*ESM 模块ID*/
#define NAS_ESM_APP_TERMIN_MID           (UE_APP_SUBSYS_ID)              /*APP通用ID*/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/



/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*ESM 记录APP CNF消息的数据结构*/
typedef struct
{
    VOS_UINT32                          bitOpEpsbId                       : 1;
    VOS_UINT32                          bitOpCId                          : 1;/*bsun 给APP的消息里，必然有CID*/
    VOS_UINT32                          bitOpOpId                         : 1;
    VOS_UINT32                          bitOpErrorCode                    : 1;
    VOS_UINT32                          bitOpMid                          : 1;
    VOS_UINT32                          bitOpModifyType                   : 1;

    VOS_UINT32                          bitOpSpare                        : 26;

    VOS_UINT32                          ulRst;
    VOS_UINT32                          ulEpsbId;
    VOS_UINT32                          ulCId;
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulErrorCode;
    VOS_UINT16                          usOriginalId;      /* 源MID */
    VOS_UINT16                          usTerminalId;      /* 目的ID */
    VOS_UINT32                          ulSn;
    APP_ESM_BEARER_MODIFY_ENUM_UINT32   enModfyType;
}NAS_ESM_APP_CNF_MSG_STRU;




typedef struct
{
    /*APP_PS_MSG_HEADER*/
    VOS_MSG_HEADER
    VOS_UINT32          ulMsgId;
    APP_MSG_HEADER

}APP_PS_MSG_HEADER_STRU;



/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern VOS_VOID NAS_ESM_AppMsgDistr( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AppSdfModifyMsgProc( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AppPdpManageRspMsgProc( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AppSdfReleaseMsgProc( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AppSdfSetupMsgProc( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AssignMidHeader( VOS_UINT16  *pusOriMid,VOS_UINT16 *pusTerMid);
extern VOS_VOID  NAS_ESM_DedictdAttMsgAppSdfModifyReq
       (
const APP_ESM_PDP_MODIFY_REQ_STRU *pRcvMsg
       );
extern VOS_VOID  NAS_ESM_DedictdAttMsgAppSdfRelReq(const VOS_VOID *pRcvMsg );
extern VOS_VOID  NAS_ESM_DedictdAttMsgAppSdfSetupReq(VOS_VOID *pRcvMsg );
extern VOS_VOID  NAS_ESM_AppSdfSetupReqRefusedProc(VOS_VOID *pRcvMsg );
extern VOS_VOID  NAS_ESM_DefltAttMsgAppSdfRelReq(const VOS_VOID *pRcvMsg );
extern VOS_VOID  NAS_ESM_DefltAttMsgAppSdfSetupReq(const VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_DefltDetMsgAppSdfSetupReq(const VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_SaveAppMidHeader( VOS_UINT32 ulStateTblIndex,
                                                       VOS_UINT16  usOriMid,
                                                       VOS_UINT16 usTerMid);
extern VOS_VOID  NAS_ESM_SaveAppMsgType( VOS_UINT32 ulStateTblIndex, APP_ESM_MSG_TYPE_ENUM_UINT32 enAppMsgType );
extern VOS_VOID NAS_ESM_SaveAppOpId( VOS_UINT32 ulStateTblIndex, VOS_UINT32 ulOpId );
extern VOS_VOID  NAS_ESM_SaveLinkedEpbsId( VOS_UINT32 ulStateTblIndex, VOS_UINT32 ulLinkedEpsbId );
extern VOS_VOID NAS_ESM_SndEsmAppSdfModCnfMsg(const NAS_ESM_APP_CNF_MSG_STRU      *pstEsmAppCnfMsg);
extern VOS_VOID NAS_ESM_SndEsmAppSdfModIndMsg
(
    VOS_UINT32                          ulStateTblIndex,
    APP_ESM_BEARER_MODIFY_ENUM_UINT32   enModfyType
);
extern VOS_VOID NAS_ESM_SndEsmAppSdfRelCnfMsg( const NAS_ESM_APP_CNF_MSG_STRU *pstEsmAppCnfMsg );
extern VOS_VOID NAS_ESM_SndEsmAppSdfRelIndMsg
(
    VOS_UINT32                          ulCid,
    VOS_UINT32                          ulEpsbId
);
extern VOS_VOID NAS_ESM_SndEsmAppSdfSetupCnfMsg(const NAS_ESM_APP_CNF_MSG_STRU *pstEsmAppCnfMsg);
extern VOS_VOID NAS_ESM_SndEsmAppSdfSetupIndMsg
(
    VOS_UINT32                          ulStateTblIndex,
    VOS_UINT32                          ulRslt
);
extern VOS_VOID NAS_ESM_AppPdpManageRspMsgRefuseProc
(
    VOS_UINT32                          ulStateTblIndex
);
extern VOS_VOID  NAS_ESM_AppPdpManageRspMsgAcceptProc
(
    VOS_UINT32                          ulStateTblIndex
);

extern VOS_VOID  NAS_ESM_ProcSetUpMsgPcoInfo( VOS_VOID *pstRsvMsg ,VOS_VOID *pstCntxtInfo);

extern VOS_VOID NAS_ESM_SndSmEspBearerMdfIndMsg
(
    VOS_UINT32                          ulEpsbId
);

extern VOS_VOID NAS_ESM_AppProcAbortNotifyProc
(
    VOS_VOID *pRcvMsg
);
extern VOS_UINT32 NAS_ESM_VerifyAppPppDialSceneAndParam
(
    VOS_VOID *pRcvMsg
);

extern VOS_VOID NAS_ESM_SendPdnConReq(NAS_ESM_BEARER_TYPE_ENUM_UINT8 enBearerType, VOS_VOID *pRcvMsg);

extern VOS_VOID  NAS_ESM_AppNdisconnMsgProc( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_SndEsmAppNdisConnCnfMsg(const NAS_ESM_APP_CNF_MSG_STRU *pstEsmAppCnfMsg);
extern VOS_VOID NAS_ESM_SendNdisConnReq(NAS_ESM_BEARER_TYPE_ENUM_UINT8 enBearerType,VOS_VOID *pRcvMsg);
extern VOS_VOID  NAS_ESM_DefltAttMsgAppNdisConnReq(const VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_DefltDetMsgAppNidsConnReq(const VOS_VOID *pRcvMsg );
extern VOS_VOID  NAS_ESM_AppNdisConnReqRefusedProc(VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AppInfoIndMsgProc(VOS_VOID *pRcvMsg);
extern VOS_UINT32  NAS_ESM_CompareEsmInfo( VOS_VOID );

extern VOS_UINT32  NAS_ESM_DtComparePdpInfo( VOS_VOID );
extern VOS_VOID  NAS_ESM_DtJudgeifNeedRpt(VOS_VOID);

extern VOS_VOID NAS_ESM_EncodeEpsDlAmbr
(
    const NAS_ESM_CONTEXT_APN_AMBR_STRU         *pstEpsAmbr,
    VOS_UINT32                          *pSendDlAmbr
);
extern VOS_VOID NAS_ESM_EncodeEpsUlAmbr
(
    const NAS_ESM_CONTEXT_APN_AMBR_STRU         *pstEpsAmbr,
    VOS_UINT32                          *pSendUlAmbr
);

extern VOS_VOID NAS_ESM_GetAppNdisconnInfo(VOS_VOID *pRcvMsg);

extern VOS_UINT32  NAS_ESM_AppNdisconnMsgCheckApnValid
(
    VOS_UINT32                           ulBitOpPdnType,
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType,
    VOS_UINT32                           ulBitOpApnInfo,
    const APP_ESM_APN_INFO_STRU         *pstApnInfo,
    NAS_ESM_APP_CNF_MSG_STRU            *pstEsmAppCnfMsg
);

extern VOS_UINT32 NAS_ESM_CheckSdfHaveUplinkPacketFilter
(
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara
);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/



#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasEsmAppMsgProc.h*/
