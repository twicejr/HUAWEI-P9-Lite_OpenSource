/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : ImsaProcImsCallMsg.h
    Description : ImsaProcImsCallMsg.c头文件
    History     :
      1.sunbing 00049683    2013-06-19  Draft Enact


******************************************************************************/

#ifndef __IMSAPROCIMSCALLMSG_H__
#define __IMSAPROCIMSCALLMSG_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "ImsaImsEvent.h"

#include    "MnCallApi.h"
#include    "ImsaEntity.h"
#include    "ImsaLrrcInterface.h"

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
enum IMSA_MT_CALL_STATUS_ENUM
{
    IMSA_MT_CALL_STATUS_INVITE_RECEIVED,           /* reveived INVITE */
    IMSA_MT_CALL_STATUS_LOST_ABNORMALLY,           /* received disconnect event, not RING yet */
    IMSA_MT_CALL_STATUS_BUTT                       /* invalid */
};
typedef VOS_UINT8 IMSA_MT_CALL_STATUS_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
typedef VOS_UINT32 ( * IMSA_IMS_CALL_MSG_ACTION_FUN )
(
    const IMSA_IMS_OUTPUT_CALL_EVENT_STRU  *  /* ???￠???? */
);

typedef struct
{
    IMSA_IMS_OUTPUT_CALL_REASON_ENUM_UINT32         enOutputCallReason;            /* 消息ID*/
    IMSA_IMS_CALL_MSG_ACTION_FUN                    pfActionFun;            /* 处理函数 */
}IMSA_IMS_CALL_MSG_ACT_STRU;

typedef struct
{
    TAF_CS_CAUSE_ENUM_UINT32             ulCauseCode;
    IMSA_MT_CALL_STATUS_ENUM_UINT8       enMtStatus;
    VOS_CHAR                             acRsv[3];
    VOS_CHAR                             acNumber[IMSA_IMS_NUMBER_STRING_SZ + 1];
    VOS_CHAR                             acReserved[3];
}IMSA_MT_STATUS_REPORT_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID IMSA_CallClearLocalAlertInfo(VOS_VOID );

extern VOS_VOID IMSA_ImsMsgCallEvent(VOS_VOID *pCallEvent);

extern VOS_VOID IMSA_CallProcImsSupsrvInfo
(
    const IMSA_IMS_CALL_SUPSRV_INFO_STRU  *pstSupsrvInfo,
    VOS_UINT32                             ulCallId
);


extern VOS_VOID IMSA_CallDtmfInfoInit(VOS_VOID);

extern VOS_VOID IMSA_CallDeleteSavedDtmfInfo(VOS_UINT8 ucIndex);

extern VOS_VOID IMSA_CallClearDtmfInfo(TAF_CS_CAUSE_ENUM_UINT32 enCause);
extern VOS_VOID IMSA_CallSrvccSuccClearDtmfInfo(TAF_CS_CAUSE_ENUM_UINT32 enCause);

extern TAF_CS_CAUSE_ENUM_UINT32 IMSA_CallSaveDtmfInfo(VOS_UINT8 ucCallId,
                                                             VOS_CHAR  cKey,
                                                             VOS_UINT16 usDuration,
                                                             VOS_UINT16 usClientId,
                                                             VOS_UINT8  ucSpmOpid);

/* 修改函数入参 */
extern TAF_CS_CAUSE_ENUM_UINT32 IMSA_CallTransImsErr2SpmErr
(
    const IMSA_IMS_OUTPUT_ERROR_STRU              *pstErrorCode
);

extern VOS_VOID IMSA_CallReleaseCallCommonProc
(
    IMSA_CALL_ENTITY_STRU              *pstCallEntity,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
);
extern VOS_UINT32 IMSA_CallProcImsMsgErrorWhenFindOpidSucc
(
    const IMSA_IMS_OUTPUT_CALL_EVENT_STRU  *pstOutputCallEvent,
    VOS_UINT32                              ulFindOpidResult
);


extern VOS_UINT32 IMSA_CallProcImsMsgModifyStatusInd(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent);
extern VOS_UINT32 IMSA_CallProcImsMsgModifyStatusBegin(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent);
extern VOS_UINT32 IMSA_CallProcImsMsgModifyStatusEnd(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent);
extern IMSA_CALL_CALL_REASON_RESOURCE_RESULT_ENUM_UINT8 IMSA_CallIsResourceReady
(
    IMSA_CALL_ENTITY_STRU              *pstCallEntity
);

extern VOS_UINT32 IMSA_CallIsNormal380Call2EmergencyCall(const IMSA_IMS_EMERGENCY_TYPE_ENUM_UINT8 EmcSubType);
extern VOS_VOID   IMSA_CallSetSpmEmergencyCat(const IMSA_IMS_EMERGENCY_TYPE_ENUM_UINT8 EmcSubType, MN_CALL_EMERGENCY_CAT_STRU* pstEmergencyCat);
extern TAF_CALL_ECONF_STATE_ENUM_U8 IMSA_EconfImsState2CsState(IMSA_IMS_ECONF_CALLER_STATE_ENUM_UINT8 enImsState);
#if (FEATURE_ON == FEATURE_DSDS)
extern VOS_VOID IMSA_CallReleaseCallResourceCommonProc(VOS_VOID);
#endif
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

#endif /* end of ImsaProcImsCallMsg.h */




