
/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEmmDetachCnMsgProcess.h
  Description     : NasEmmDetachCnMsgProcess.h
  History           :
      1.leili 132387       2008-09-09  Draft Enact

******************************************************************************/
#ifndef __NASEMMDETACHCNMSGPROCESS_H__
#define __NASEMMDETACHCNMSGPROCESS_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "NasEmmPubUGlobal.h"
#include    "NasEmmAttach.h"
#include    "NasEmmDetach.h"
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
extern  VOS_UINT32  NAS_EMM_CnDetachAcpMoMsgChk(
                                    const NAS_EMM_CN_DETACH_ACP_MO_STRU   *pMsgMsg );
extern  VOS_UINT32  NAS_EMM_CnDetachReqMtMsgChk(
                                    const NAS_EMM_CN_DETACH_REQ_MT_STRU   *pMsgMsg );
extern  VOS_VOID    NAS_EMM_DetCauseValProc(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucDetCause);
extern  VOS_VOID    NAS_EMM_ProcDetCauseVal2( VOS_VOID );
extern  VOS_VOID    NAS_EMM_ProcDetCauseVal3678(VOS_UINT8 ucDetCause);
extern  VOS_VOID    NAS_EMM_ProcDetCauseVal11(VOS_UINT8 ucDetCause);
extern  VOS_VOID    NAS_EMM_ProcDetCauseVal12(VOS_UINT8 ucDetCause);
extern  VOS_VOID    NAS_EMM_ProcDetCauseVal13(VOS_UINT8 ucDetCause);
extern  VOS_VOID    NAS_EMM_ProcDetCauseVal14(VOS_UINT8 ucDetCause);
extern  VOS_VOID    NAS_EMM_ProcDetCauseVal15(VOS_UINT8 ucDetCause);
#if(FEATURE_ON == FEATURE_CSG)
extern VOS_VOID    NAS_EMM_ProcDetCauseVal25(VOS_UINT8 ucDetCause);
#endif
extern  VOS_VOID    NAS_EMM_ProcDetNoCauseOrOtherCause(VOS_VOID);
extern  VOS_VOID    NAS_EMM_CompCnDetachAcpMt(NAS_EMM_MRRC_DATA_REQ_STRU *pDetAccMtMsg);
extern  VOS_VOID    NAS_EMM_DetDataUpdate(VOS_UINT32 ulDeleteRplmn,VOS_UINT8 ucCnCause);
extern  VOS_UINT32  NAS_EMM_CountCnDetAcpMtLen(VOS_VOID);
extern  VOS_UINT32  NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachAcp
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern  VOS_UINT32  NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgRrcRelInd
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_VOID  NAS_EMM_ProcMsRegImsiDetachInitMsgRrcRelInd
(
    VOS_UINT32                          ulCause
);

extern VOS_VOID  NAS_EMM_ProcNoUsimOfDrgInitMsgCnDetachReq( VOS_VOID   *pMsgStru);
extern VOS_VOID  NAS_EMM_ProcNoUsimCnDetReqNotReattach(
                               const NAS_EMM_CN_DETACH_REQ_MT_STRU       *pRcvEmmMsg);

extern VOS_VOID NAS_EMM_DetachErrRecord(
        NAS_EMM_CN_DETACH_REQ_MT_STRU       *pstCnDetach);
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











































