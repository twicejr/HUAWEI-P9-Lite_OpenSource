
/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEmmAttachCnMsgProcess.h
  Description     : NasEmmAttachCnMsgProcess.h
  History           :
      1.leili 132387       2008-09-09  Draft Enact

******************************************************************************/

#ifndef __NASEMMATTACHCNMSGPROCESS_H__
#define __NASEMMATTACHCNMSGPROCESS_H__




/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "NasEmmAttach.h"
#include    "NasEmmPubUGlobal.h"
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
/*#define NAS_EMM_SECOND_TRANSFER_MILLISECOND    1000
#define NAS_EMM_MINUTE_TRANSFER_MILLISECOND    60000*/


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
extern  VOS_UINT32  NAS_EMM_CnAttachAcpMsgChk(const NAS_EMM_CN_ATTACH_ACP_STRU  *pMsgMsg);
extern  VOS_UINT32  NAS_EMM_CnAttachRejMsgChk(const NAS_EMM_CN_ATTACH_REJ_STRU *pMsgMsg);

extern  VOS_VOID    NAS_EMM_EsmSendEstCnf (EMM_ESM_ATTACH_STATUS_ENUM_UINT32 ucEstRst);
extern  VOS_UINT32  NAS_EMM_CountEsmDataIndLen(VOS_UINT32 ulNasEsmMsgLen);
extern  VOS_UINT32  NAS_EMM_CountTcDataIndLen(VOS_UINT32 ulNasTcMsgLen);
extern  VOS_VOID    NAS_EMM_RejCauseValProc(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal);
extern  VOS_VOID    NAS_EMM_ProcEpsOnlySucc
(
    VOS_VOID                *pstRcvMsg
);
extern  VOS_VOID    NAS_EMM_ProcEpsOnlyWithCause(VOS_VOID *pstRcvMsg);
extern  VOS_VOID    NAS_EMM_ProcEpsOnlyNoCause( VOS_VOID);
extern  VOS_VOID    NAS_EMM_ProcRejCauseVal2(VOS_VOID);
extern  VOS_VOID    NAS_EMM_ProcRejCauseVal5(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal);
extern  VOS_VOID    NAS_EMM_ProcRejCauseVal3678(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal);
extern  VOS_VOID    NAS_EMM_ProcRejCauseVal11(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal);
extern  VOS_VOID    NAS_EMM_ProcRejCauseVal12(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal);
extern  VOS_VOID    NAS_EMM_ProcRejCauseVal13(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal);
extern  VOS_VOID    NAS_EMM_ProcRejCauseVal14(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal);
extern  VOS_VOID    NAS_EMM_ProcRejCauseVal15(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal);
extern  VOS_VOID    NAS_EMM_ProcRejCauseVal1617(VOS_VOID);
extern  VOS_VOID    NAS_EMM_ProcRejCauseVal22(VOS_VOID);
extern  VOS_VOID    NAS_EMM_ProcRejCauseVal18(VOS_VOID);
#if(FEATURE_ON == FEATURE_CSG)
extern VOS_VOID  NAS_EMM_ProcRejCauseVal25(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal);
#endif
extern  VOS_VOID    NAS_EMM_ProcRejCauseVal35(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal);
extern  VOS_VOID    NAS_EMM_ProcRejCauseVal42(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal);
/*extern  VOS_VOID    NAS_EMM_ProcEpsOnlyOtherCause( NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal );*/

extern  VOS_VOID    NAS_EMM_ProcRejCauseValOther(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal);
extern  VOS_VOID   NAS_EMM_AttDataUpdate(VOS_UINT32 ulDeleteRplmn);
extern VOS_VOID  NAS_EMM_TcSendDataInd
(
    const NAS_EMM_CN_MSGCON_STRU       *pstTcMsg
);

extern VOS_VOID NAS_EMM_EsmSendStopNotifyInd (VOS_VOID);

extern VOS_VOID  NAS_LMM_LteNoSubscribeWithExtCauseHandle(
                               MMC_LMM_LTE_NO_SUBSCRIBE_PLMN_LIST_STRU  *pstLteNoSubsPLmnList);
extern VOS_VOID  NAS_LMM_LteNoSubscribeWithOutExtCauseHandle(
                        MMC_LMM_LTE_NO_SUBSCRIBE_PLMN_LIST_STRU  *pstLteNoSubsPLmnList);

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











































