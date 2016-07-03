
#ifndef _TAF_SPM_SERVICE_DOMAIN_SEL_PROC_H_
#define _TAF_SPM_SERVICE_DOMAIN_SEL_PROC_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "MnCallApi.h"
#include "TafSpmCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_SPM_IS_PS_VIDEO(CallType, CsVpCfgState, VoiceDomain)    \
           (((MN_CALL_TYPE_VIDEO_TX    == CallType)                 \
          || (MN_CALL_TYPE_VIDEO_RX    == CallType)                 \
          || (MN_CALL_TYPE_VIDEO       == CallType))                \
         && ((TAF_SPM_VP_NONE          == CsVpCfgState)             \
          || (TAF_SPM_VP_MT_ONLY       == CsVpCfgState))            \
         && (TAF_CALL_VOICE_DOMAIN_IMS == VoiceDomain))


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum
{
    TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING,   /* result of domain selection: over nas signalling */
    TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP,       /* result of domain selection: over IP */
    TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE,   /* result of domain selection: buffer message */
    TAF_SPM_DOMAIN_SEL_RESULT_SELECT_FAIL,      /* result of domain selection: select fail */

    TAF_SPM_DOMAIN_SEL_RESULT_BUTT
};
typedef VOS_UINT8 TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8;



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
#if (FEATURE_ON == FEATURE_IMS)

VOS_UINT32 TAF_SPM_ProcReqMsgBasedOnCsOverIp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_SPM_RcvRegisterSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_SPM_RcvEraseSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_SPM_RcvActivateSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_SPM_RcvDeactivateSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_SPM_RcvInterrogateSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_SPM_RcvProcUssSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_SPM_RcvRleaseSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvAppOrigReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppSupsCmdReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppGetInfoReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppStartDtmfReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppStopDtmfReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppGetCdurReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvStkOrigReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvStkSupsCmdReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvStkStartDtmfReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvStkStopDtmfReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppGetCallInfoReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvAppGetClprReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSmsDomainSelection(VOS_VOID);

VOS_UINT32 TAF_SPM_ProcImsaNormalRegStatusNotify(
    struct MsgCB                       *pstMsg
);

/* 函数放到IMS宏外面 */

VOS_VOID TAF_SPM_ProcMmaPowerOffInd(VOS_VOID);

/* 函数放到IMS宏外面 */



VOS_UINT32 TAF_SPM_RcvSendRpdataDirectBasedOnCsOverIp(
    struct MsgCB                       *pstRcvMsg
);


VOS_UINT32 TAF_SPM_RcvSendRpdataFromMemBasedOnCsOverIp(
    struct MsgCB                       *pstRcvMsg
);

/* 移到IMS编译开关之外 */

TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcCcDomainSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSsDomainSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_SPM_ProcSmmaIndDomainSelectionResult(
    VOS_UINT32                                              ulEventType,
    struct MsgCB                                           *pstMsg,
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt
);

/* 函数放到IMS宏外面 */

VOS_UINT8 TAF_SPM_IsNeedtoWaitImsRegStatus(
    TAF_SPM_SERVICE_STATUS_ENUM_UINT8   enLastPsStatus
);

VOS_UINT32 TAF_SPM_RcvAppCallModifyReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppCallAnswerRemoteModifyReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvAppEconfDialReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvAppGetEconfInfoReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

#endif

TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcServiceRequestDomainSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_ProcInitialDomainSelectionResult
(
    VOS_UINT32                                              ulEventType,
    struct MsgCB                                           *pstMsg,
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt
);

VOS_UINT32 TAF_SPM_ProcCcSrvReqProtectTimerExpired(VOS_VOID);

VOS_UINT32 TAF_SPM_ProcSsSrvReqProtectTimerExpired(VOS_VOID);

VOS_UINT32 TAF_SPM_ProcSmsSrvReqProtectTimerExpired(
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_SPM_SendCcServiceRequetFail(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);
VOS_VOID TAF_SPM_SendSmsServiceRequetFail(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    VOS_UINT32                          ulCause
);
VOS_VOID TAF_SPM_SendSsServiceRequetFail(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_SS_ERROR                        errorCode
);




VOS_UINT32 TAF_SPM_ProcReqMsgBasedOnNasSignalling(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstRcvMsg
);

/* 函数放到IMS宏外面 */
VOS_UINT32 TAF_SPM_ProcServiceRequestFail(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_ProcBufferedMsgInQueue(VOS_VOID);

VOS_UINT32 TAF_SPM_BufferAppRequestMessage(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_ProcSmsMsgQueue(TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 *pEnDomainSelRslt);

TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcCcDomainSelectionByProtectTimerLen(VOS_VOID);
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSmsDomainSelectionByProtectTimerLen(VOS_VOID);
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSsDomainSelectionByProtectTimerLen(VOS_VOID);

#if (FEATURE_ON == FEATURE_ECALL)
VOS_UINT32 TAF_SPM_IsEcallAllowedSelNasSignalling(
    MN_CALL_TYPE_ENUM_U8                enCallType
);
#endif



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

#endif /* _TAF_SPM_IMS_DOMAIN_SEL_PROC_H_ end */

