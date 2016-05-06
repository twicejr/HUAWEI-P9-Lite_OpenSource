/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmPreProcAct
  版 本 号   : 初稿
  作    者   : s00217060
  生成日期   : 2013年12月14日
  最近修改   :
  功能描述   : TafSpmPreProcAct.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年12月14日
    作    者   : s00217060
    修改内容   : 创建文件

******************************************************************************/
#ifndef _TAF_SPM_PREPROCACT_H_
#define _TAF_SPM_PREPROCACT_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include "UsimPsInterface.h"
#include "MnErrorCode.h"

/* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
#include "siapppb.h"
/* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

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
VOS_UINT32 TAF_SPM_RcvAppOrigReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppSupsCmdReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppGetInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppStartDtmfReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppStopDtmfReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppGetCdurReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppGetCallInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppGetClprReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppSendRpdataDirect_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvProcUssSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvRegisterSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvEraseSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvActivateSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvDeactivateSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvInterrogateSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvRegPwdSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvEraseCCentrySsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvRleaseSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvStkOrigReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32 TAF_SPM_RcvMsgSmmaInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvMsgReportInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvMsgCheckRsltInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvImsaCallOrigCnf_PreProc(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaCallOrig_PreProc(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaCallProc_PreProc(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaCallAlerting_PreProc(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaCallConnect_PreProc(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaCallSupsCmdCnf_PreProc(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaCallRelease_PreProc(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaCallIncoming_PreProc(
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvImsaCallStartDtmfCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaCallStopDtmfCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvImsaCallStartDtmfRsltInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaCallStopDtmfRsltInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvImsaCallSsCmdRslt_PreProc(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaCallSsNotify_PreProc(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaCallAllRelease_PreProc(
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvImsaCallMsg_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaGetCallInfoCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaChannelInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaGetClprCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaCallHold_PreProc(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaCallRetrieve_PreProc(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaSsMsg_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstRcvMsg
);
VOS_UINT32 TAF_SPM_RcvInternalDomainSelInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaNormalRegStatusNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvMmaServiceStatusChangeNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvMmaNetworkCapabilityChangeNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvMmaRatChangeNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-31, begin */
VOS_UINT32 TAF_SPM_RcvMmaImsVoiceCapInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-31, end */

VOS_UINT32 TAF_SPM_RcvImsaCallMsgSyncInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvImsaCallInviteNewPtptCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvImsaCallTypeChangeInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvAppCallModifyReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppCallAnswerRemoteModifyReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaCallModifyCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaCallAnswerRemoteModifyCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvImsaCallModifyStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvAppEconfDialReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvImsaEconfDialCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvImsaEconfAddUsersCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvImsaEconfNotifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvImsaGetEconfInfoCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvAppGetEconfInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#endif

/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, begin */
VOS_UINT32 TAF_SPM_RcvCcSrvReqProtectTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvSmsSrvReqProtectTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvSsSrvReqProtectTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, end */

VOS_UINT32 TAF_SPM_RcvMmaPowerOffInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvMmaSrvAcqCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_IsSsServiceReqAllowed_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_ERROR_CODE_ENUM_UINT32         *penCause
);
VOS_UINT32 TAF_SPM_IsSmsServiceReqAllowed_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    VOS_UINT32                         *pulCause
);

/* Added by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
#if (FEATURE_ON == FEATURE_ECALL)
VOS_UINT32 TAF_SPM_RcvMmaPhoneModeSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvTafRelCallCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvPbQryECallNumCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvPbECallInitInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_ProcEcallReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_SPM_ProcPbQryFdnECallNumCnf_PreProc(
    SI_PB_ECALLQRY_CNF_STRU            *pstPbMsg
);

VOS_VOID TAF_SPM_ProcPbQrySdnECallNumCnf_PreProc(
    SI_PB_ECALLQRY_CNF_STRU            *pstPbMsg
);

#endif
/* Added by s00261364 for V3R360_eCall项目, 2014-4-4, end */
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

#endif /* end of TafSpmPreProcAct */

