/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.
******************************************************************************/

#ifndef __NASLPPUPPUBLIC_H__
#define __NASLPPUPPUBLIC_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"


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
#define NAS_LPP_INFINITY_CNT  0
#define TI_NAS_LPP_UP_WAIT_CN_ASSIST_DATA_LEN       (10000)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*******************************************************************************
 结构名    : NAS_LPP_UP_STATE_TIME_STRU
 结构说明  : 子状态跟定时器名字的对应关系
 1.日    期   : 2015-11-24
   作    者   :lifuxin
*******************************************************************************/
typedef struct
{
    NAS_LPP_UP_STATE_ENUM_UINT32        enLppUpSubState;
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName;
    VOS_UINT8                           aucRsv[3];
}NAS_LPP_UP_STATE_TIME_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8  NAS_LPP_GetOtdoaPosType( VOS_VOID );
extern VOS_VOID  NAS_LPP_LppUpEntityInit( VOS_VOID );
extern NAS_LPP_UP_REPORT_CRITERIA_STRU*  NAS_LPP_EcidReportTypeAddr(VOS_VOID);
extern NAS_LPP_UP_REPORT_CRITERIA_STRU*  NAS_LPP_OtdoaReportTypeAddr(VOS_VOID);
extern VOS_VOID NAS_LPP_UpTimerStop
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType,
    NAS_LPP_TIMER_PARA_ENUM_UINT8           enTimerType
);
extern NAS_LPP_UP_OTDOA_INFO_STRU*  NAS_LPP_GetLppUpOtdoaCtx( VOS_VOID );
extern VOS_VOID NAS_LPP_UpChangeTransFsmState
(
    NAS_LPP_UP_STATE_ENUM_UINT32            enLppUpState,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType
);
extern NAS_LPP_UP_ECID_INFO_STRU*  NAS_LPP_GetLppUpEcidCtx( VOS_VOID );
extern VOS_VOID NAS_LPP_UpTimerStart
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType,
    NAS_LPP_TIMER_PARA_ENUM_UINT8           enTimerType
);
extern VOS_VOID  NAS_LPP_UPClrEcidCtx(VOS_VOID);
extern VOS_VOID  NAS_LPP_UPClrOtdoaCtx( VOS_VOID );
extern NAS_LPP_USER_PLANE_ENTITY_STRU*  NAS_LPP_GetLppUpEntityCtx( VOS_VOID );
extern NAS_LPP_UP_REPORT_CRITERIA_STRU*  NAS_LPP_EcidReportTypeAddr(VOS_VOID);
extern NAS_LPP_UP_REPORT_CRITERIA_STRU*  NAS_LPP_OtdoaReportTypeAddr(VOS_VOID);
extern NAS_LPP_UP_REPORT_CRITERIA_STRU*  NAS_LPP_MultiPosTechReportTypeAddr(VOS_VOID);
extern VOS_VOID  NAS_LPP_SetEcidAndOtdoaMeasFlag(VOS_BOOL bReqEcidAndOtdoaFlag);
extern VOS_VOID  NAS_LPP_SetEcidPosType
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enEcidPosType
);
extern VOS_VOID   NAS_LPP_StopReportTimer
(
    NAS_LPP_UP_REPORT_CRITERIA_STRU        *pstReportCriteria,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType
);
extern VOS_VOID  NAS_LPP_SetEcidPosReqTechType
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosReqTech
);
extern VOS_VOID  NAS_LPP_SetOtdoaPosReqTechType
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosReqTech
);
extern VOS_VOID NAS_LPP_UPSndEcidMeasReq
(
    LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8    ucLcsMeasCmd
);
extern VOS_BOOL  NAS_LPP_GetEcidAndOtdoaMeasFlag(VOS_VOID);
extern VOS_BOOL  NAS_LPP_GetOtdoaAssistDataFlag( VOS_VOID );
extern VOS_VOID  NAS_LPP_SetOtdoaPosType
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enOtodaPosType
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

#endif /* end of NasLppSendMsg.h */
