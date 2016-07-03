

#ifndef __TAF_MMA_FSM_PHONE_MODE_H__
#define __TAF_MMA_FSM_PHONE_MODE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "siappstk.h"
#include  "UsimPsInterface.h"
#include  "MmaMsccInterface.h"




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaInterPowerInit_PhoneMode_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMmaInterUsimStatusChangeInd_PhoneMode_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvOMPhoneModeSet_PhoneMode_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_WaitExternalModuleInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_WaitExternalModuleInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvUphyInitStatusInd_PhoneMode_WaitExternalModuleInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_MMA_RcvTafPhoneModeSet_PhoneMode_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_WaitPihUsimStatusInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvTiWaitPihUsimStatusIndExpired_PhoneMode_WaitPihUsimStatusInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);




VOS_VOID TAF_MMA_SndStartReq_PhoneMode(
);

VOS_VOID TAF_MMA_SndPowerOffReq_PhoneMode(
    VOS_UINT32                          ulReceivePid
);

VOS_UINT32 TAF_MMA_RcvMsccStartCnf_PhoneMode_WaitMsccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvTiWaitMsccStartCnfExpired_PhoneMode_WaitMsccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMsccPowerOffCnf_PhoneMode_WaitMsccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvTiWaitMsccPowerOffCnfExpired_PhoneMode_WaitMsccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



VOS_VOID    TAF_MMA_ProcStartReq_PhoneMode(VOS_VOID);

VOS_VOID    TAF_MMA_ProcPowerOffReq_PhoneMode(VOS_VOID);

VOS_UINT32  TAF_MMA_GetCurrFsmEntryMsgId_PhoneMode(VOS_VOID);

VOS_UINT8   TAF_MMA_GetCurrFsmEntryMsgOpId_PhoneMode(VOS_VOID);

VOS_UINT8  TAF_MMA_GetCurrFsmEntryMsgPhoneMode_PhoneMode(VOS_VOID);

VOS_VOID TAF_MMA_ReportPhoneModeCnf_PhoneMode(VOS_VOID);

VOS_VOID TAF_MMA_SndAtPsInitRsltInd_PhoneMode(
    TAF_MMA_PS_INIT_RSLT_ENUM_UINT32    enPsInitRslt
);

VOS_VOID TAF_MMA_ReportPhoneModeInd_PhoneMode(VOS_VOID);

NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32 TAF_MMA_GetMsccPowerOffCause_PhoneMode(VOS_VOID);
VOS_VOID TAF_MMA_ProcStartExpired_PhoneMode(VOS_VOID);

VOS_VOID TAF_MMA_ProcPowerOffExpired_PhoneMode(VOS_VOID);

VOS_UINT32 TAF_MMA_ProcStartComplete_PhoneMode(
    VOS_UINT32                          ulRslt
);

VOS_UINT32 TAF_MMA_ProcPowerOffComplete_PhoneMode(VOS_VOID);



NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 TAF_MMA_ConvertSdcSimStatusToMsccFormat_PhoneMode(
    VOS_UINT8                           ucSdcSimStatus,
    VOS_UINT8                           ucSimType
);

VOS_VOID TAF_MMA_ProcStartCnfSucc_NoPowerInit_PhoneMode(VOS_VOID);

VOS_VOID TAF_MMA_ProcGetGeoNoSimStartReq_PhoneMode(VOS_VOID);

VOS_VOID TAF_MMA_ProcGetGeoNoSimPowerOffReq_PhoneMode(VOS_VOID);

VOS_VOID TAF_MMA_ProcStopGetGeoReq_PhoneMode(VOS_VOID);

VOS_UINT32 TAF_MMA_RcvMsccGetGeoCnf_PhoneMode_WaitMsccGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvTiWaitMsccGetGeoCnfExpired_PhoneMode_WaitMsccGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_WaitMsccGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_WaitMsccGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeoCmpWaitUsimStatusInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_GetGeoCmpWaitUsimStatusInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMsccStopGetGeoCnf_PhoneMode_WaitMsccStopGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMsccGetGeoCnf_PhoneMode_WaitMsccStopGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_WaitMsccStopGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvTiWaitMsccStopGetGeoCnfExpired_PhoneMode_WaitMsccStopGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMsccStartCnf_PhoneMode_GetGeoWaitMsccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeoWaitMsccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvTiWaitMsccStartCnfExpired_PhoneMode_GetGeoWaitMsccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_GetGeoWaitMsccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMsccPowerOffCnf_PhoneMode_GetGeoWaitMsccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeoWaitMsccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvTiWaitMsccPowerOffCnfExpired_PhoneMode_GetGeoWaitMsccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_VOID TAF_MMA_SndRatModInd_PhoneMode(VOS_VOID);
#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafMmaFsmPhoneMode.h */


