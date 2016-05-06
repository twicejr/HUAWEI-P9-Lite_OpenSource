

/******************************************************************************


        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEmmTauSerInclude.h
    Description : EMM的C文件要包含的头文件
    History     :
      1. 周岩  00125190 2008-10-08 Initial

******************************************************************************/

#ifndef __NASEMMTAUSERINCLUDE_H__
#define __NASEMMTAUSERINCLUDE_H__




/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"

#include    "PsCommonDef.h"

#include    "LRrcLNasInterface.h"

#include    "NasEmmPubUGlobal.h"
#include    "NasEmmPubUCnMsgDecode.h"
#include    "NasEmmPubUMain.h"
#include    "NasLmmPubMNvim.h"
#include    "NasLmmPubMIntraMsg.h"
#include    "NasLmmPubMFsm.h"
#include    "NasLmmPubMEntry.h"
#include    "NasLmmPubMTimer.h"
#include    "NasLmmPublic.h"
#include    "NasLmmPubMOm.h"


#include    "AppMmInterface.h"
#include    "EmmEsmInterface.h"
#include    "EmmRabmInterface.h"
#include    "NasEmmcEmmInterface.h"
#include    "NasEmmAttDetInterface.h"
#include    "NasEmmMrrcPubInterface.h"
#include    "NasEmmSerInterface.h"
#include    "NasEmmTauInterface.h"
#include    "NasEmmGutiPubInterface.h"
#include    "NasEmmSecuInterface.h"
#include    "NasEmmSmsInterface.h"

#include    "NasEmmTAUProc.h"
#include    "NasEmmSerProc.h"
#include    "NasEmmDetachAppMsgProcess.h"
#include    "NasCommPrint.h"
#include    "NasEmmcSendMsg.h"
#include    "LnasErrlogInterface.h"



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
/*========================= EMM全局变量的宏简写 =========================*/
#define NAS_EMM_SER_CN_REJ_CAUSE_NULL     0

/* TALIST相关操作，包括得到和保存 */
#define NAS_EMM_TAUSER_GetGUTIAddr()        (&(g_stEmmInfo.stMmUeId.stGuti))
#define NAS_EMM_TAUSER_OP_GUTI()            (g_stEmmInfo.stMmUeId.bitOpGuti)
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
extern VOS_VOID  NAS_EMM_SetBarInfo(NAS_EMM_BAR_PROCEDURE_ENUM_UINT32 enBarProc,
                            LRRC_LNAS_EST_RESULT_ENUM_UINT32 enBarType);
/* leixiantiao 00258641 重构函数降低圈复杂度 begin */
extern VOS_UINT32 NAS_EMM_IsBarTypeMoSingal(VOS_VOID);
extern VOS_UINT32 NAS_EMM_IsBarTypeMoCall(VOS_VOID);
extern VOS_UINT32 NAS_EMM_IsBarTypeMt(VOS_VOID);
extern VOS_UINT32 NAS_EMM_IsBarTypeMoCsfb(VOS_VOID);
extern VOS_UINT32 NAS_EMM_IsBarTypeMoCallAndCsfb(VOS_VOID);
/* leixiantiao 00258641 重构函数降低圈复杂度 end */
extern VOS_UINT32  NAS_EMM_JudgeBarType( NAS_EMM_BAR_TYPE_ENUM_UINT32 enBarType);
extern VOS_VOID  NAS_EMM_ClearBarType( LRRC_LNAS_ACCESS_GRANT_ENUM_UINT32 enBarType);
extern VOS_UINT32  NAS_EMM_GetBarProcedure(VOS_VOID );
extern VOS_VOID  NAS_EMM_SER_UplinkPending( VOS_VOID );
extern VOS_VOID  NAS_EMM_SER_SmsEstReq( VOS_VOID );

/*for test*/
extern VOS_UINT32  NAS_EMM_SrvBarIsTauStarted( VOS_VOID);
extern VOS_VOID    NAS_EMM_ProcSrvBar( VOS_VOID );
extern VOS_VOID NAS_EMM_ExtServiceErrRecord(
        NAS_EMM_CN_CAUSE_ENUM_UINT8                 enCnRejCause,
        EMM_OM_LMM_CSFB_FAIL_CAUSE_ENUM_UINT8       enCsfbFailCause);
extern VOS_VOID NAS_EMM_NorServiceErrRecord(
            VOS_VOID*                         pstNorServiceFail,
            EMM_OM_ERRLOG_TYPE_ENUM_UINT16    enErrType);
extern VOS_VOID NAS_EMM_SerCnRejErrRecord(
                    NAS_EMM_CN_SER_REJ_STRU *pMsgStru,
                    EMM_OM_LMM_CSFB_FAIL_CAUSE_ENUM_UINT8 enCsfbFailCause,
                    EMM_OM_ERRLOG_TYPE_ENUM_UINT16   enErrlogType);

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

#endif /* end of ErrcFsmComm.h */




























