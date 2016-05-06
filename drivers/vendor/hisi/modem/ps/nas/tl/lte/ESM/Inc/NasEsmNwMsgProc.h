/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEsmNwMsgProc.h
  Description     : NasEsmNwMsgProc.c header file
  History         :
     1.sunbing49683       2009-2-24     Draft Enact
     2.杨茜惠 00135146    2009-03-06    Modify  BA8D01127
******************************************************************************/

#ifndef __NASESMNWMSGPROC_H__
#define __NASESMNWMSGPROC_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "NasEsmInclude.h"


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

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum NAS_ESM_VERIFY_CN_MSG_FAIL_CAUSE_ENUM
{
    ESM_VERIFY_CN_MSG_VALUE_INVALID                     = 1,   /* ??? */
    ESM_VERIFY_CN_MSG_PTI_MISMATCH                      = 2,   /* PTI????? */
    ESM_VERIFY_CN_MSG_STATE_TABLE_FULL                  = 3,   /* ?????,?????CID */
    ESM_VERIFY_CN_MSG_IN_PDN_DISCONN_PROCEDURE          = 4,   /* ?PDN DISCONN???? */
    ESM_VERIFY_CN_MSG_FILT_NOT_SAME_CID                 = 5,   /* filter?????CID */
    ESM_VERIFY_CN_MSG_TAD_INVALID                       = 6,   /* TAD??? */
    ESM_VERIFY_CN_PF_RENDER_EMPTY                       = 7,   /* PF?? */
    ESM_VERIFY_CN_NO_UPLINK_PF                          = 8,   /* ????PF */
    ESM_VERIFY_CN_NO_OPERATION_NO_QOS                   = 9,   /* ???NO OP???QOS?? */
    ESM_VERIFY_CN_ADD_FILTER_NOT_INCREASE               = 10,  /* ??FILT?QOS???? */
    ESM_VERIFY_CN_DEL_FILTER_NOT_DECREASE               = 11,  /* ??FILT?QOS???? */
    ESM_VERIFY_CN_UE_CN_OPERATION_COLLISION             = 12,  /* UE????????? */
    ESM_VERIFY_CN_UPDATE_STATE_TABLE_FAIL               = 13,  /* ??????? */
    ESM_VERIFY_CN_MSG_CN_REJ_EPSBID_NOT_ZERO            = 14,  /* ????epsid??0 */
    ESM_VERIFY_CN_MSG_ESM_INFO_REQ_EPSBID_NOT_ZERO      = 15,  /* ????ESM INFO epsid??0 */
    ESM_VERIFY_CN_MSG_CN_MSG_TYPE_INVALID               = 16,  /* ?????? */
    ESM_VERIFY_CN_MSG_ACT_DEDIC_OP_NOT_CREATE_TFT       = 17,  /* ?????? ??????TFT */

    ESM_VERIFY_CN_MSG_FAIL_CAUSE_BUTT
};
typedef VOS_UINT32 NAS_ESM_VERIFY_CN_MSG_FAIL_CAUSE_ENUM_UINT32;




/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : NAS_ESM_PF_PRECEDENCE_VALIDATE_STRU
 结构说明  : packet filter优先级验证结构
 ***************************************************************************/
typedef struct
{
    VOS_UINT8                             ucEpsbId;
    VOS_UINT8                             ucPfId;
    VOS_UINT8                             ucPrecedence;
    VOS_UINT8                             ucCid;
    APP_ESM_TRANSFER_DIRECTION_ENUM_UINT8 enDirection;
    VOS_UINT8                             ucRsv[3];
}NAS_ESM_PF_PRCDNC_VLDT_STRU;


typedef struct
{
    MSG_HEADER_STRU                                      stMsgHeader;
    NAS_ESM_CN_MSG_IE_TYPE_ENUM_UINT32                   enIeType;
    NAS_ESM_VERIFY_CN_MSG_FAIL_CAUSE_ENUM_UINT32         enCause;
    VOS_UINT32                                           ulValue;
}NAS_ESM_OM_LOG_VERIFY_CN_MSG_FAIL_STRU;

typedef struct
{
    NAS_ESM_VERIFY_CN_MSG_FAIL_CAUSE_ENUM_UINT32         ulFailCause;
    VOS_UINT8                                            aucPrintStr[NAS_COMM_PRINT_MAX_ITEM_LEN];
}NAS_ESM_OM_VERIFY_CN_MSG_FAIL_CAUSE_PRINT_STR_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID NAS_ESM_NwMsgProcess
(
    const  EMM_ESM_INTRA_DATA_IND_STRU      *pRcvMsg
);
extern VOS_UINT32 NAS_ESM_PreProcNwMsg
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE
);
extern VOS_VOID  NAS_ESM_ProcValidNwMsgEsmInfoReq
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE
);
extern VOS_VOID NAS_ESM_ProcNwMsgForDecodeError(const NAS_ESM_NW_MSG_STRU *pstEsmNwMsgIE,
                                                            NAS_ESM_CAUSE_ENUM_UINT8  enEsmCause);
extern VOS_VOID  NAS_ESM_ProcNwMsgForIllegalEpsbId
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE
);
extern VOS_VOID NAS_ESM_ProcNwMsgForIllegalPti
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE,
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause
);
extern VOS_VOID NAS_ESM_ProcNwMsgDeactProcedureCollision
(
    VOS_UINT32                          ulStateTblId,
    const NAS_ESM_NW_MSG_STRU           *pRcvMsg
);

extern VOS_VOID  NAS_ESM_SndRejAirMsg
(
    NAS_ESMCN_MSG_TYPE_ENUM_UINT8       enEsmCnMsgType,
    const NAS_ESM_ENCODE_INFO_STRU     *pstEncodeInfo
);
extern VOS_UINT32  NAS_ESM_CreatePfPrecedenceValidateListInPdn
(
    VOS_UINT32                          ulEpsbId,
    VOS_UINT8                          *pucPfNum,
    NAS_ESM_PF_PRCDNC_VLDT_STRU        *pstPfPVList
);

extern VOS_VOID NAS_ESM_SndEsmAppSdfProcCnfSucc
(
    VOS_UINT32                          ulStateTblIndex,
    APP_ESM_BEARER_MODIFY_ENUM_UINT32   enModfyType
);

extern VOS_VOID NAS_ESM_ProcNwMsgActDediBearSamePtiWithDiffEBI
(
    const EMM_ESM_INTRA_DATA_IND_STRU        *pRcvMsg,
    VOS_UINT32                                ulStateTblIndex,
    NAS_ESM_STATE_INFO_STRU                  *pstStateAddr

);

extern VOS_VOID NAS_ESM_ProcNwMsgModDediBearSamePtiWithDiffEBI
(
    const EMM_ESM_INTRA_DATA_IND_STRU        *pRcvMsg,
    VOS_UINT32                                ulStateTblIndex,
    NAS_ESM_STATE_INFO_STRU                  *pstStateAddr

);
extern VOS_VOID NAS_ESM_ProcNwMsgDeaDediBearSamePtiWithDiffEBI
(
    const EMM_ESM_INTRA_DATA_IND_STRU        *pRcvMsg,
    VOS_UINT32                                ulStateTblIndex,
    NAS_ESM_STATE_INFO_STRU                  *pstStateAddr

);

extern VOS_UINT32 NAS_ESM_IsNwActBearerWithOnlyOneCid
(
    VOS_UINT32                      ucEpsBearer
);

extern VOS_VOID  NAS_ESM_GetPfPrecedenceValidateListInBearer
(
    VOS_UINT8                           ucEpsbId,
    VOS_UINT8                          *pucPfNum,
    NAS_ESM_PF_PRCDNC_VLDT_STRU        *pstPfPVList
);

extern VOS_VOID NAS_ESM_SndOmLogCnMsgVerifyFail
(
    NAS_ESM_CN_MSG_IE_TYPE_ENUM_UINT32                  enIeType,
    NAS_ESM_VERIFY_CN_MSG_FAIL_CAUSE_ENUM_UINT32        enCause,
    VOS_UINT32                                          ulValue
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

#endif /* end of NasEsmNwMsgProc.h */
