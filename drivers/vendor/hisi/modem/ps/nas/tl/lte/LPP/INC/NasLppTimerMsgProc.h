


#ifndef __NASLPPTIMERMSGPROC_H__
#define __NASLPPTIMERMSGPROC_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "NasLppPublic.h"


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
extern VOS_UINT8  NAS_LPP_ParsIndxFromTimePara
(
    VOS_UINT32                              ulPara,
    VOS_UINT8                              *pucSessionIndx,
    VOS_UINT8                              *pucSessionTransIndx,
    NAS_LPP_TIMER_PARA_ENUM_UINT8           enTimerType
);
extern VOS_VOID  NAS_LPP_RcvIntraDataCnfTimerExpire( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx ,VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg);
extern VOS_VOID  NAS_LPP_RcvLocationInvalidTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx ,VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg);
extern VOS_VOID  NAS_LPP_RcvUpMsgRetransTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx , VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg);
extern VOS_VOID  NAS_LPP_RcvWaitCnAssistDataTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx ,VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg);
extern VOS_VOID  NAS_LPP_RcvWaitEstCnfTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx,VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg );
extern VOS_VOID  NAS_LPP_RcvWaitGnssCapCnfTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx,VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg );
extern VOS_VOID  NAS_LPP_RcvWaitLrrcMeasCnfTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx ,VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg);
extern VOS_VOID  NAS_LPP_RcvWaitPeriodicalTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx,VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg );
extern VOS_VOID  NAS_LPP_RcvWaitReEstTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx,VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg );
extern VOS_VOID  NAS_LPP_RcvWaitReportDurationTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx ,VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg);
extern VOS_VOID  NAS_LPP_RcvWaitResponseTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx , VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg);
extern VOS_VOID NAS_LPP_TimerMsgDistr(VOS_VOID *pRcvMsg );
extern VOS_VOID  NAS_LPP_TimerInit( VOS_VOID );
extern VOS_VOID  NAS_LPP_RcvUpPeriodicalReportTimer
(
    VOS_UINT8                       ucSessionIndx,
    VOS_UINT8                       ucSessionTransIndx,
    VOS_UINT8                       ucUpReqTechType,
    VOS_VOID                       *pRcvMsg
);
extern VOS_VOID  NAS_LPP_RcvUpReportDurationTimer
(
    VOS_UINT8                       ucSessionIndx,
    VOS_UINT8                       ucSessionTransIndx,
    VOS_UINT8                       ucUpReqTechType,
    VOS_VOID                       *pRcvMsg
);
extern VOS_VOID  NAS_LPP_RcvUpResponseTimer
(
    VOS_UINT8                       ucSessionIndx,
    VOS_UINT8                       ucSessionTransIndx,
    VOS_UINT8                       ucUpReqTechType,
    VOS_VOID                       *pRcvMsg
);
extern VOS_VOID  NAS_LPP_RcvUpWaitCnAssistDataTimer
(
    VOS_UINT8                       ucSessionIndx,
    VOS_UINT8                       ucSessionTransIndx,
    VOS_UINT8                       ucUpReqTechType,
    VOS_VOID                       *pRcvMsg
);
extern VOS_VOID  NAS_LPP_RcvUpWaitLrrcEcidMeasCnfTimer
(
    VOS_UINT8                       ucSessionIndx,
    VOS_UINT8                       ucSessionTransIndx,
    VOS_UINT8                       ucUpReqTechType,
    VOS_VOID                       *pRcvMsg
);
extern VOS_VOID  NAS_LPP_RcvUpWaitLrrcOtdoaMeasCnfTimer
(
    VOS_UINT8                       ucSessionIndx,
    VOS_UINT8                       ucSessionTransIndx,
    VOS_UINT8                       ucUpReqTechType,
    VOS_VOID                       *pRcvMsg
);
extern VOS_VOID  NAS_LPP_RcvWaitSequenceNumberTimer
(
    VOS_UINT8                       ucSessionIndx,
    VOS_UINT8                       ucSessionTransIndx,
    VOS_UINT8                       ucUpReqTechType,
    VOS_VOID                       *pRcvMsg
);
extern VOS_VOID NAS_LPP_UpTimerStart
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType,
    NAS_LPP_TIMER_PARA_ENUM_UINT8           enTimerType
);
extern VOS_VOID  NAS_LPP_OtodaPeriodReportingCntAddOne( VOS_VOID );
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











































