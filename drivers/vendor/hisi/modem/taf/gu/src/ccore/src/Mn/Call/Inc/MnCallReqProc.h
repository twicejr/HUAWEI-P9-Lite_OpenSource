
#ifndef  MN_CALL_REQ_PROC_H
#define  MN_CALL_REQ_PROC_H


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "MnCallApi.h"
#include "MnCallBcProc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/

/*****************************************************************************
  3类型定义
*****************************************************************************/




/*****************************************************************************
  4 宏定义
*****************************************************************************/


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 接口函数声明
*****************************************************************************/

VOS_VOID  MN_CALL_CallOrigReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    MN_CALL_ORIG_PARAM_STRU             *pstOrigParm
);


VOS_UINT32 MN_CALL_InternalCallEndReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_END_PARAM_STRU       *pstEndParm
);


VOS_VOID  MN_CALL_CallEndReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        uccallId,
    const MN_CALL_END_PARAM_STRU        *pstEndParm
);


VOS_VOID  MN_CALL_CallAnswerReqProc(
    MN_CLIENT_ID_T                      ucClientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_ANS_PARAM_STRU        *pstAnsParam
);


VOS_VOID  MN_CALL_CallSupsCmdReqProc(struct MsgCB *pstCallSups);


VOS_UINT32  MN_CALL_BuildNormalCallReqProc(MN_CALL_ID_T callId);


VOS_UINT32 MN_CALL_GetMoCallBc(
    MN_CALL_ID_T                        CallId,
    NAS_CC_IE_BC_STRU                  *pstBc1,
    NAS_CC_IE_BC_STRU                  *pstBc2,
    MN_CALL_REP_IND_ENUM_U8            *penBcRepeatInd
);


VOS_VOID MN_CALL_ReportEccNumList(VOS_VOID);


VOS_VOID MN_CALL_StkCallOrigReqProc(struct MsgCB * pstMsg);



TAF_CS_CAUSE_ENUM_UINT32 MN_CALL_GetEndCause(
    TAF_CS_CAUSE_ENUM_UINT32            enEndCause,
    MN_CALL_STATE_ENUM_U8               enCallState
);

VOS_VOID TAF_CALL_RelIncomingOrWaitingCall(
    VOS_UINT8                           ucCallId,
    MN_CALL_STATE_ENUM_U8               enCallState
);

VOS_VOID TAF_CALL_RelRedialingCall(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU      *pstCallSupsParam    
);


VOS_UINT32 MN_CALL_MakeNewCall(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_ID_T                       *pNewCallId
);


VOS_VOID  MN_CALL_RcvAtCssnSetReq(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_SET_CSSN_REQ_STRU          *pstSetCssnReq
);
/*****************************************************************************
 函 数 名  : MN_CALL_GetEccNumList
 功能描述  : 获取紧急呼号码列表
 输入参数  : 无
 输出参数  : pstEccNumInfo
 返 回 值  : 无
*****************************************************************************/
VOS_VOID MN_CALL_GetEccNumList(MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo);

/*****************************************************************************
 函 数 名  : MN_CALL_RcvAtXlemaReq
 功能描述  : 紧急呼号码查询处理
 输入参数  :
 输出参数  : 无
 返 回 值  : 无

*****************************************************************************/
VOS_VOID MN_CALL_RcvAtXlemaReq(MN_CALL_APP_REQ_MSG_STRU            *pstCallMsg);


VOS_VOID  TAF_CALL_RcvStartDtmfReq(struct MsgCB * pstMsgSend);

VOS_VOID  TAF_CALL_RcvStopDtmfReq(struct MsgCB * pstStopDtmf);

#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_CALL_RcvQryEcallInfoReq(MN_CALL_QRY_ECALL_INFO_REQ_STRU *pstQryEcallInfoReq);

VOS_VOID TAF_CALL_EcallSupsCmdRelReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
);
#endif

VOS_VOID MN_CALL_CallSupsCmdRelAllCallReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
);

VOS_VOID  TAF_CALL_RcvCcwaiSetReq(MN_CALL_APP_REQ_MSG_STRU *pstAppReq);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* MN_CALL_REQ_PROC_H */

