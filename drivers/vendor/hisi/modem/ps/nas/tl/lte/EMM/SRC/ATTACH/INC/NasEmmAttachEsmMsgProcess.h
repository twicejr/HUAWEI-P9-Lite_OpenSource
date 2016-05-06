
/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEmmAttachEsmMsgProcess.h
  Description     : NasEmmAttachEsmMsgProcess.h
  History           :
      1.leili 132387       2008-09-09  Draft Enact

******************************************************************************/
#ifndef __NASEMMATTACHESMMSGPROCESS_H__
#define __NASEMMATTACHESMMSGPROCESS_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "NasEmmPubUGlobal.h"
#include    "NasEmmAttach.h"
#include    "EmmEsmInterface.h"


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
  2 Macro
*****************************************************************************/
#define NAS_EMM_IEI_TMSI                0x90
#define NAS_EMM_IE_TMSI_SPARE           0xF0

#define NAS_EMM_IEI_AUT                 0xF0
#define NAS_EMM_IE_AUT_SPARE            0xF0
#define NAS_EMM_IE_AUTV                 0x01

#define NAS_EMM_GET_MS_NET_CAPA_OPEN    VOS_TRUE
#define NAS_EMM_GET_MS_NET_CAPA_CLOSE   VOS_FALSE



#define NAS_LMM_IE_FORMAT_ERR(ucIeFormat)\
           ((NAS_LMM_IE_FORMAT_V         != ucIeFormat) &&\
            (NAS_LMM_IE_FORMAT_LV        != ucIeFormat) &&\
            (NAS_LMM_IE_FORMAT_TLV       != ucIeFormat) &&\
            (NAS_LMM_IE_FORMAT_LV_E      != ucIeFormat))

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_EMM_IE_TMSI_STATUS_ENUM
 枚举说明  : 24,008 10.5.5.4
*****************************************************************************/
enum NAS_EMM_IE_TMSI_STATUS_ENUM
{
    NAS_EMM_IE_TMSI_INVALID             = 0x00,
    NAS_EMM_IE_TMSI_VALID               = 0x01,
    NAS_EMM_IE_TMSI_VALID_STATUS_BUTT
};
typedef VOS_UINT8 NAS_EMM_IE_TMSI_STATUS_ENUM_UINT8;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern    VOS_UINT32  g_ulMsNwCapFromGU;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID* NAS_EMM_AttRsltCommProc(VOS_VOID );
extern  VOS_UINT32  NAS_EMM_EsmPdnRspMsgChk(const EMM_ESM_PDN_CON_RSP_STRU *pMsgpMsg);
/*extern  VOS_VOID    NAS_EMM_AppSendAttInd(VOS_UINT32 ulRslt);*/
extern  VOS_VOID    NAS_EMM_CompCnAttachReq(NAS_EMM_MRRC_DATA_REQ_STRU *pAttReqMsg);
extern  VOS_VOID    NAS_EMM_CompCnAttachCmp
(
    LRRC_LNAS_MSG_STRU                 *pAttCmp,
    VOS_UINT32                         *pulIndex,
    const EMM_ESM_MSG_STRU             *pstEsmMsg
);
extern  VOS_VOID    NAS_EMM_MrrcSendAttReq( VOS_VOID );
extern  VOS_VOID    NAS_EMM_MrrcSendAttCmp
(
    const EMM_ESM_MSG_STRU             *pstEsmMsg
);
extern  VOS_VOID    NAS_EMM_EncodeEpsMobileId
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
);
extern  VOS_VOID    NAS_EMM_CompCnAttachReqNasMsg(  VOS_UINT8      *pucAttReqCn,
                                                    VOS_UINT32     *pulIndex);


extern VOS_UINT32  NAS_EMM_MsAnyStateSsAnySateProcMsgEsmStatusReq( VOS_VOID );
extern VOS_VOID    NAS_EMM_EncodeEsmContainer
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
);
extern VOS_VOID    NAS_EMM_AppSendAttRstSuccFail(MMC_LMM_ATTACH_RSLT_ENUM_UINT32 ulAttRst);
extern VOS_VOID    NAS_EMM_AppSendAttPsNotAllow(  VOS_VOID );
extern  VOS_VOID NAS_EMM_AppSendAttFailWithAllPara( VOS_VOID );
extern VOS_VOID    NAS_EMM_AppSendAttRstDefaultReqType
(
    MMC_LMM_ATTACH_RSLT_ENUM_UINT32     ulAttRslt
);
extern VOS_VOID    NAS_EMM_MmcSendAttCnf
(
    MMC_LMM_ATTACH_RSLT_ENUM_UINT32                ulAttRslt
);
extern NAS_EMM_BEARER_STATE_ENUM_UINT8  NAS_EMM_ProcEsmBearState
(
    VOS_UINT32      ulEpsId,
    VOS_VOID        *pstMsg
);
extern VOS_VOID  NAS_EMM_UpdateEpsBearStatus(VOS_VOID *pstMsg);
extern VOS_VOID NAS_EMM_RestartAttProcedural(VOS_VOID);

extern NAS_EMM_BEARER_STATE_ENUM_UINT8  NAS_EMM_IsEpsBearStatusAct (VOS_VOID);
extern VOS_VOID NAS_EMM_SendEsmDataCnf(EMM_ESM_SEND_RSLT_ENUM_UINT32 enDataCnfRst, VOS_UINT32 ulEsmEmmOpId);
extern VOS_VOID NAS_EMM_RcvLrrcEsmDataCnfHandle(const LRRC_LMM_DATA_CNF_STRU  *pstRrcMmDataCnf, VOS_UINT32 ulEsmEmmOpId);

extern VOS_VOID NAS_EMM_LocalDetachErrRecord(
        EMM_ERR_LOG_LOCAL_DETACH_TYPE_ENUM_UINT16       enLocalDetType);

extern VOS_VOID NAS_EMM_EsmDataReqRetranProc(VOS_UINT32 ulOpid);


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

#endif











































