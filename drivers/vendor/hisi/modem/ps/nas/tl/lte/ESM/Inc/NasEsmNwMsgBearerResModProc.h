/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmNwMsgBearerResModProc.h
    Description :
    History     :
     1.丁丽 00128736      2008-09-01  Draft Enact
     2.孙兵 49683         2009-01-06  BA8D00870
     3.杨茜惠 00135146    2009-03-06  Modify  BA8D01127
     4.李洪00150010       2009-08-03  Modify  BJ9D01608
******************************************************************************/

#ifndef _NASESMNWMSGBEARERRESMODPROC_H
#define _NASESMNWMSGBEARERRESMODPROC_H


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
#define NAS_ESM_EVENT_BEARER_SETUP(ulEpsbId)\
(VOS_UINT8)(ESM_KEY_EVENT_BEARER_5_SETUP + (VOS_UINT8)(((VOS_UINT8)ulEpsbId - (VOS_UINT8)(NAS_ESM_MIN_EPSB_ID))*((VOS_UINT8)(ESM_KEY_EVENT_BEARER_6_SETUP) - (VOS_UINT8)(ESM_KEY_EVENT_BEARER_5_SETUP))))


#define NAS_ESM_EVENT_BEARER_RELEASE(ulEpsbId)\
(VOS_UINT8)(ESM_KEY_EVENT_BEARER_5_RELEASE + (VOS_UINT8)(((VOS_UINT8)ulEpsbId - (VOS_UINT8)NAS_ESM_MIN_EPSB_ID)*((VOS_UINT8)ESM_KEY_EVENT_BEARER_6_RELEASE - (VOS_UINT8)ESM_KEY_EVENT_BEARER_5_RELEASE)))


#define NAS_ESM_EVENT_BEARER_MODIFY(ulEpsbId)\
(VOS_UINT8)(ESM_KEY_EVENT_BEARER_5_MODIFY + (VOS_UINT8)(((VOS_UINT8)ulEpsbId - (VOS_UINT8)NAS_ESM_MIN_EPSB_ID)*((VOS_UINT8)ESM_KEY_EVENT_BEARER_6_MODIFY - (VOS_UINT8)ESM_KEY_EVENT_BEARER_5_MODIFY)))


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/* 比较结果枚举 */
enum NAS_ESM_COMPARE_RESULT_ENUM
{
    NAS_ESM_COMPARE_RESULT_BIG      = 0x0 ,
    NAS_ESM_COMPARE_RESULT_SMALL    = 0x1,
    NAS_ESM_COMPARE_RESULT_EQUAL    = 0x2,
    NAS_ESM_COMPARE_RESULT_OTHER    = 0x3,

    NAS_ESM_QOS_COMPARE_RESULT_BUTT
};
typedef VOS_UINT8  NAS_ESM_COMPARE_RESULT_ENUM_UINT8;



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
extern VOS_VOID NAS_ESM_DeactBearerAndInformApp(   VOS_UINT32 ulEpsbId );
extern VOS_VOID NAS_ESM_InformAppEpsBearerModSucc
       (
           const  NAS_ESM_NW_MSG_STRU         *pstMsgIE,
           VOS_UINT32                          ulStateTblIndex
       );
extern VOS_VOID  NAS_ESM_ProcValidNwMsgActDedictdEpsbReq
       (
           VOS_UINT32                          ulStateTblIndex,
           const EMM_ESM_INTRA_DATA_IND_STRU              *pRcvMsg
       );
extern VOS_VOID  NAS_ESM_ProcValidNwMsgModEpsbReq
       (
           VOS_UINT32                          ulStateTblIndex,
           const EMM_ESM_INTRA_DATA_IND_STRU  *pRcvMsg
       );
extern VOS_VOID  NAS_ESM_ProcValidNwMsgResModRej
       (
           VOS_UINT32                          ulStateTblIndex,
           const EMM_ESM_INTRA_DATA_IND_STRU  *pRcvMsg
       );
extern VOS_VOID NAS_ESM_SndEsmAppSdfModCnfFailMsg
(
    VOS_UINT32                          ulStateTblIndex,
    VOS_UINT32                          ulErrorCode
);
extern VOS_VOID NAS_ESM_SndEsmAppSdfModCnfSuccMsg
(
    VOS_UINT32                          ulStateTblIndex,
    APP_ESM_BEARER_MODIFY_ENUM_UINT32   enModfyType
);
extern VOS_VOID NAS_ESM_SndEsmAppSdfRelCnfFailMsg
(
    VOS_UINT32                          ulStateTblIndex,
    VOS_UINT32                          ulErrorCode
);
extern VOS_VOID NAS_ESM_SndEsmAppSdfRelCnfSuccMsg(   VOS_UINT32 ulStateTblIndex);
extern VOS_VOID NAS_ESM_SndEsmAppSdfSetupCnfFailMsg
(
    VOS_UINT32                          ulStateTblIndex,
    VOS_UINT32                          ulErrorCode
);
extern VOS_VOID NAS_ESM_SndEsmAppSdfSetupCnfSuccMsg(   VOS_UINT32 ulStateTblIndex);

extern VOS_VOID  NAS_ESM_UpdatePacketFilterToSdfCntxt
(
    const  NAS_ESM_NW_MSG_STRU         *pstMsgIE,
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo,
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo,
    VOS_UINT32                          ulStateTblIndex
);
extern VOS_VOID  NAS_ESM_UpdateEpsQosInfo
(
    const  NAS_ESM_NW_MSG_STRU         *pstMsgIE,
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo,
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo
);
extern APP_ESM_BEARER_MODIFY_ENUM_UINT32  NAS_ESM_GetBearModifyType
(
    const  NAS_ESM_NW_MSG_STRU *pstMsgIE
);
extern VOS_UINT32 NAS_ESM_PfMatch
(
    const NAS_ESM_CONTEXT_TFT_STRU              *pstTFT1,
    const NAS_ESM_CONTEXT_TFT_STRU              *pstTFT2
);
extern VOS_UINT32 NAS_ESM_TftMatch
(
    const NAS_ESM_CONTEXT_TFT_STRU           *pstTft1PfInfo,
    VOS_UINT32                                ulTft1PfNum,
    NAS_ESM_CONTEXT_TFT_STRU                 *pstTft2PfInfo,
    VOS_UINT32                                ulTft2PfNum
);
extern VOS_VOID NAS_ESM_SaveNwActDedictdEpsbReqInfo
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
);
extern VOS_VOID  NAS_ESM_SaveNwModEpsbReqInfo
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
);
extern VOS_VOID  NAS_ESM_DediBearActMsgManualProc
(
    VOS_UINT32                          ulStateTblIndex,
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg
);
extern VOS_VOID NAS_ESM_DediBearActMsgAutoAccept
(
    VOS_UINT32                          ulStateTblIndex,
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo,
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg
);
extern VOS_VOID  NAS_ESM_BearModMsgManualProc
(
    VOS_UINT32                          ulStateTblIndex,
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg
);
extern VOS_VOID NAS_ESM_BearModMsgAutoAccept
(
    VOS_UINT32                          ulStateTblIndex,
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo,
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg
);
extern VOS_VOID  NAS_ESM_ActDediBearFailProc
(
    const NAS_ESM_ENCODE_INFO_STRU     *pstEncodeInfo,
    VOS_UINT32                          ulStateTblIndex
);
extern VOS_VOID  NAS_ESM_BearModFailProc
(
    const NAS_ESM_ENCODE_INFO_STRU     *pstEncodeInfo,
    VOS_UINT32                          ulStateTblIndex
);
extern VOS_VOID NAS_ESM_SndSmEspBearerDeactIndMsg
(
    VOS_UINT32                          ulEpsbId
);
extern VOS_VOID  NAS_ESM_SaveNwModEpsbNoTft
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
);
extern VOS_VOID  NAS_ESM_SaveNwModDeftEpsbAddPf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
);
extern VOS_VOID  NAS_ESM_SaveNwModDeftEpsbReplacePf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
);
extern VOS_VOID  NAS_ESM_SaveNwModDeftEpsbDeletePf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
);
extern VOS_VOID  NAS_ESM_SaveNwModDeftEpsbNoOperation
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
);
extern VOS_VOID  NAS_ESM_SaveNwModDeftEpsbCreateTft
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
);
extern VOS_VOID  NAS_ESM_SaveNwModDeftEpsbDeleteTft
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
);

extern VOS_UINT32 NAS_ESM_IsExistlinkedPfInSdfCntxt( VOS_UINT32 ulCid,VOS_UINT32 ulSdfParaPfId );
extern VOS_UINT8 NAS_ESM_GetAppPfId( VOS_UINT32 ulCid );
extern VOS_VOID NAS_ESM_ModulateSdfTft
(
    VOS_UINT32                          ulStateTblIndex
);
extern VOS_VOID NAS_ESM_ModulateSdfQos
(
    VOS_UINT32                          ulStateTblIndex
);
extern VOS_VOID  NAS_ESM_SaveNwModDediEpsbAddPf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
);
extern VOS_VOID  NAS_ESM_SaveNwModDediEpsbReplacePf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
);
extern VOS_VOID  NAS_ESM_SaveNwModDediEpsbCreatPf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
);
extern VOS_VOID  NAS_ESM_SaveNwModDediEpsbDeletePf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
);
extern VOS_VOID  NAS_ESM_SaveNwModDediEpsbNoOperation
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
);
extern VOS_VOID  NAS_ESM_SaveNwModDeftEpsbReqInfo
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
);
extern VOS_VOID  NAS_ESM_SaveNwModDediEpsbReqInfo
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
);

extern VOS_VOID NAS_ESM_SndEsmAppNdisConnCnfFailMsg
(
    VOS_UINT32                          ulStateTblIndex,
    VOS_UINT32                          ulErrorCode
);
extern VOS_VOID NAS_ESM_SndEsmAppNdisConnCnfSuccMsg(   VOS_UINT32 ulStateTblIndex);

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

#endif /* end of NasEsmNwMsgBearerResModProc.h*/
