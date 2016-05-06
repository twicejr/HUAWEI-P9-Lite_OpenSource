/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmFsmServiceCtrl.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年5月8日
  最近修改   :
  功能描述   : TafSpmFsmServiceCtrl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月8日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_SPM_SERVICE_CTRL_H__
#define __TAF_SPM_SERVICE_CTRL_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "siappstk.h"
#include  "TafSpmSndInternalMsg.h"
#include  "UsimPsInterface.h"
#include  "Taf_MmiStrParse.h"

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
VOS_UINT32 TAF_SPM_RcvAtSSReqMsg_ServiceCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvStkSSReqMsg_ServiceCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-31, begin */
VOS_UINT32 TAF_SPM_RcvAtCallReqMsg_ServiceCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvStkCallReqMsg_ServiceCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvAtSmsReqMsg_ServiceCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvStkSmsReqMsg_ServiceCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-31, end */


VOS_UINT32 TAF_SPM_RcvPbFdnCheckCnf_ServiceCtrl_WaitPbFdnCheckCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvTiWaitPbFdnCheckCnfExpired_ServiceCtrl_WaitPbFdnCheckCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvUsimEnvelopeCnf_ServiceCtrl_WaitUsimCallCtrlCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_SPM_RcvTiWaitUsimCallCtrlCnfExpired_ServiceCtrl_WaitUsimCallCtrlCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-16, begin */

VOS_UINT32 TAF_SPM_SendPbFdnCheckReq_ServiceCtrl(
    VOS_UINT16                         usClientId,
    struct MsgCB                      *pstMsg
);

VOS_UINT32  TAF_SPM_SendUsimEnvelopeReq_ServiceCtrl(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
);

/* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-16, end */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */

/* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */
VOS_VOID TAF_SPM_ProcSsEnvelopeCnf(
    SI_STK_ENVELOPEDWON_CNF_STRU                           *pstEnvelopeCnf,
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                *penRslt,
    VOS_UINT32                                             *pulCause
);

VOS_VOID TAF_SPM_ProcCallEnvelopeCnf(
    SI_STK_ENVELOPEDWON_CNF_STRU                           *pstEnvelopeCnf,
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                *penRslt,
    VOS_UINT32                                             *pulCause
);


VOS_VOID TAF_SPM_ProcCallCtrlRsltAllowModify_SS(
    SI_STK_ENVELOPE_RSP_STRU                               *pstCallCtrlRsp,
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                *penRslt,
    VOS_UINT32                                             *pulCause
);
/* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */


VOS_UINT32 TAF_SPM_ModifySsEntryMsgByCallCtrlMsg(
    VOS_UINT32                          ulSenderPid,
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam
);

VOS_UINT32 TAF_SPM_Modify2SsActivateMsg(
    VOS_UINT32                          ulSenderPid,
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam,
    VOS_VOID                           *pMsg
);

VOS_UINT32 TAF_SPM_Modify2SsDeactivateMsg(
    VOS_UINT32                          ulSenderPid,
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam,
    VOS_VOID                           *pMsg
);

VOS_UINT32 TAF_SPM_Modify2SsInterrogateMsg(
    VOS_UINT32                          ulSenderPid,
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam,
    VOS_VOID                           *pMsg
);

VOS_UINT32 TAF_SPM_Modify2SsRegisterMsg(
    VOS_UINT32                          ulSenderPid,
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam,
    VOS_VOID                           *pMsg
);

VOS_UINT32 TAF_SPM_Modify2SsEraseMsg(
    VOS_UINT32                          ulSenderPid,
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam,
    VOS_VOID                           *pMsg
);

VOS_UINT32 TAF_SPM_Modify2SsRegPwdMsg(
    VOS_UINT32                          ulSenderPid,
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam,
    VOS_VOID                           *pMsg
);

VOS_UINT32 TAF_SPM_Modify2DeactivateCcbsMsg(
    VOS_UINT32                          ulSenderPid,
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam,
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_SPM_ProcSsCallCtrlRsltAllowModify(
    SI_STK_ENVELOPE_RSP_STRU                               *pstCallCtrlRsp,
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                *penRslt,
    VOS_UINT32                                             *pulCause
);

VOS_VOID TAF_SPM_ProcUssdCallCtrlRsltAllowModify(
    SI_STK_ENVELOPE_RSP_STRU                               *pstCallCtrlRsp,
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                *penRslt,
    VOS_UINT32                                             *pulCause
);

VOS_VOID TAF_SPM_StartFdnCheck_ServiceCtrl(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_SPM_StartCallControlCheck_ServiceCtrl(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_SendPbCallFdnCheckReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_SendPbUssdFdnCheckReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_SPM_SendPbSsFdnCheckReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_SPM_SendUsimUssdEnvelopeReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_SPM_SendUsimSsEnvelopeReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_SPM_ProcCallCtrlRsltAllowModify_CALL(
    SI_STK_ENVELOPE_RSP_STRU                               *pstCallCtrlRsp,
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                *penRslt,
    VOS_UINT32                                             *pulCause,
    VOS_UINT32                                              ulIndex
);

VOS_UINT32 TAF_SPM_IsCallCtrlModifyBeyondCapability_CALL(
    SI_STK_CALLCTRL_RSP_STRU           *pstCallCtrlRsp,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_TYPE_ENUM_U8               *penCallType,
    MN_CALL_EMERGENCY_CAT_STRU         *pstEmergencyCat
);

VOS_VOID TAF_SPM_ModifyCallEntryMsgByCallCtrlMsg(
    SI_STK_CALLCTRL_RSP_STRU           *pstCallCtrlRsp,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_EMERGENCY_CAT_STRU         *pstEmergencyCall,
    VOS_UINT32                          ulIndex
);

VOS_UINT32 TAF_SPM_ProcFdnCheckResult(
    VOS_UINT32                          ulRslt,
    VOS_UINT16                          usClientId,
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg
);


VOS_UINT32 TAF_SPM_ProcEconfCallCtrlCheckResult(
    VOS_UINT32                          enRslt,
    VOS_UINT16                          usClientId,
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg
);



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

#endif /* end of TafSpmServiceCtrl.h */

