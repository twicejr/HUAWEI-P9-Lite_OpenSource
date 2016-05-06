/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmNwMsgPdnConProc.h
    Description :
    History     :
     1.丁丽 00128736      2008-09-01  Draft Enact
     2.杨茜惠 00135146    2009-03-06  Modify  BA8D01127
******************************************************************************/

#ifndef _NASESMNWMSGPDNCONPROC_H
#define _NASESMNWMSGPDNCONPROC_H

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "NasEsmPublic.h"
#include    "NasEsmNwMsgEncode.h"


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
#define NAS_ESM_GATEWAYE_IP1             0x01
#define NAS_ESM_GATEWAYE_IP2             0xFE

#define NAS_ESM_SetSubnetMask(stSubnetMask)\
{\
    stSubnetMask.ucIpType       = NAS_ESM_PDN_IPV4;\
    stSubnetMask.aucIpV4Addr[0] = 255;\
    stSubnetMask.aucIpV4Addr[1] = 255;\
    stSubnetMask.aucIpV4Addr[2] = 255;\
    stSubnetMask.aucIpV4Addr[3] = 0;\
}

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/



/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_CheckNwActDefltEpsbReqMsg(const  NAS_ESM_NW_MSG_STRU *pstMsgIE,
                                                           NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbCntxtInfo);
extern VOS_VOID NAS_ESM_ProcValidNwMsgActDefltEpsbReq
(
    VOS_UINT32                                  ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU          *pRcvMsg
);
extern VOS_VOID NAS_ESM_ProcValidNwMsgPdnConnRej
       (
           VOS_UINT32                          ulStateTblIndex,
           const EMM_ESM_INTRA_DATA_IND_STRU  *pRcvMsg
       );

extern VOS_VOID NAS_ESM_SaveNwActDefltEpsbReqInfo
(
        const  NAS_ESM_NW_MSG_STRU      *pstMsgIE,
        VOS_UINT32                       ulStateTblIndex
);

extern VOS_VOID  NAS_ESM_SndEsmAppPdpManageIndMsg
(
    const APP_ESM_PDP_MANAGER_IND_STRU       *pstPdpManInd
);

extern VOS_VOID NAS_ESM_DefltBearActMsgAutoAccept
(
    VOS_UINT32                          ulStateTblIndex,
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo,
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg
);

extern VOS_VOID  NAS_ESM_DefltBearActMsgManualProc
(
    VOS_UINT32                          ulStateTblIndex,
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg
);

extern VOS_VOID  NAS_ESM_ActDefltBearFailProc
(
    const NAS_ESM_ENCODE_INFO_STRU     *pstEncodeInfo,
    VOS_UINT32                          ulStateTblIndex
);
extern VOS_VOID NAS_ESM_SetEpsBearInfo
(
    const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbCntxtInfo,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearInfoInd
);
extern VOS_VOID NAS_ESM_SndSmEspBearerActIndMsg
(
    VOS_UINT32                          ulEpsbId
);
extern VOS_VOID NAS_ESM_ProcNwMsgEsmCause54
(
    VOS_UINT32                          ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU  *pRcvMsg
);
extern VOS_UINT32 NAS_ESM_IsDhcpProcedureNeeded
(
    VOS_UINT32                          ucEpsbId
);
extern VOS_VOID NAS_ESM_SndEsmAppSdfSetupSuccMsg
(
    VOS_UINT32                          ulStateTblIndex
);
extern VOS_VOID NAS_ESM_SetEpsBearTftInfo
(
    VOS_UINT32                          ulBitCId,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearInfoInd
);
extern VOS_VOID NAS_ESM_SetEpsBearPcoIpv4Item
(
    const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbCntxtInfo,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearInfoInd
);
extern VOS_VOID NAS_ESM_SetEpsBearPcoIpv6Item
(
    const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbCntxtInfo,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearInfoInd
);


extern VOS_VOID NAS_ESM_PdnRejListDestroy
(
    NAS_ESM_PDN_REJ_INFO_STRU *pstListHead
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

#endif /* end of NasEsmNwMsgPdnConProc.h*/
