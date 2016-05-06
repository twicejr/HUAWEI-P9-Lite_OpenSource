/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallSendCc.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年9月15日
  最近修改   : 2007年9月15日
  功能描述   : MNCC原语发送模块的接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2007年9月15日
    作    者   : 丁庆 49431
    修改内容   : 创建文件

  2.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
******************************************************************************/
#ifndef  MN_CALL_SEND_CC_H
#define  MN_CALL_SEND_CC_H


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "MnCallApi.h"
#include "MnCallMnccProc.h"
#include "MnCallFacilityDecode.h"
#include "MnCallBcProc.h"
#include "MnCallCtx.h"
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
VOS_UINT32  MN_CALL_SendMnccPrimitive(MsgBlock * pMsg);

/*****************************************************************************
 函 数 名  : MN_CALL_SendCcSetupReq
 功能描述  : 发送MNCC_SETUP_REQ原语
 输入参数  : ucRepeatInd   - Repeat Indicator, 如果pstBc2为空该参数将被忽略
             pstBc1        - Bear capability 1
             pstBc2        - Bear capability 2 (可选)
             pstCallInfo   - 呼叫实体消息
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年09月18日
    作    者   : y00213812
    修改内容   : STK&DCM 项目增加带子地址的呼叫,重构该函数，以MN_CALL_MGMT_STRU
                 替代原有入参。
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcSetupReq(
    MN_CALL_REP_IND_ENUM_U8             enRepeatInd,
    const NAS_CC_IE_BC_STRU            *pstBc1,
    const NAS_CC_IE_BC_STRU            *pstBc2,
    const MN_CALL_MGMT_STRU            *pstCallInfo
);

/*****************************************************************************
 函 数 名  : MN_CALL_SendCcEmergSetupReq
 功能描述  : 发送MNCC_EMERG_SETUP_REQ原语
 输入参数  : CallId        - 呼叫的ID
             ucCategory    - 紧急呼叫种类
             pstBc         - Bear capability (可选)
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcEmergSetupReq(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           *pucCategory
);


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcCallConfReq
 功能描述  : 发送MNCC_CALL_CONF_REQ原语
 输入参数  : CallId        - 呼叫的ID
             ucRepeatInd   - Repeat Indicator, 如果pstBc2为空该参数将被忽略
             pstBc1        - Bear capability 1 (可选)
             pstBc2        - Bear capability 2 (可选), 如果pstBc1为空该参数将被忽略
             Cause         - 原因值
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcCallConfReq(
    MN_CALL_ID_T                        CallId,
    MN_CALL_REP_IND_ENUM_U8             enRepeatInd,
    const NAS_CC_IE_BC_STRU             *pstBc1,
    const NAS_CC_IE_BC_STRU             *pstBc2,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
);


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcDiscReq
 功能描述  : 发送MNCC_DISC_REQ原语(不携带Facility)
 输入参数  : CallId        - 呼叫的ID
             Cause         - 挂断的原因
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcDiscReq(
    MN_CALL_ID_T                        callId,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
);


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcRelReq
 功能描述  : 发送MNCC_REL_REQ原语(不携带Facility)
 输入参数  : CallId        - 呼叫的ID
             Cause         - 挂断的原因
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcRelReq(
    MN_CALL_ID_T                        callId,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
);


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcRejReq
 功能描述  : 发送MNCC_REJ_REQ原语
 输入参数  : CallId        - 呼叫的ID
             Cause         - 拒绝的原因
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_SendCcRejReq(
    MN_CALL_ID_T                        callId,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
);


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcSetupRsp
 功能描述  : 发送MNCC_SETUP_RES原语
 输入参数  : CallId - 呼叫的ID
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcSetupRsp(
    MN_CALL_ID_T                        callId
);


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcHoldReq
 功能描述  : 发送MNCC_HOLD_REQ原语
 输入参数  : CallId - 呼叫的ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_SendCcHoldReq(
    MN_CALL_ID_T                        callId
);


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcRetrieveReq
 功能描述  : 发送MNCC_RETRIEVE_REQ原语
 输入参数  : CallId - 呼叫的ID
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_SendCcRetrieveReq(
    MN_CALL_ID_T                        callId
);


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcSimpleFacility
 功能描述  : 发送简单的MNCC_FACILITY_REQ原语(除Operation Code之外没有其它参数)
 输入参数  : CallId - 呼叫的ID
             OpCode - Operation Code
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_SendCcSimpleFacility(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_OPERATION_CODE_T         opCode
);


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcStartDtmfReq
 功能描述  : 发送MNCC_START_DTMF_REQ原语
 输入参数  : CallId - 呼叫的ID
             ucKey  - 要发送的DTMF按键
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcStartDtmfReq(
    MN_CALL_ID_T                        callId,
    VOS_INT8                            cKey
);


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcStopDtmfReq
 功能描述  : 发送MNCC_STOP_DTMF_REQ原语
 输入参数  : CallId - 呼叫的ID
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcStopDtmfReq(
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 函 数 名  : MN_CALL_SendCcAlertReq
 功能描述  : 发送MNCC_ALERT_REQ原语
 输入参数  : CallId        - 呼叫的ID
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcAlertReq(
    MN_CALL_ID_T                        callId
);


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcDeflectFacility
 功能描述  : 发送MNCC_DISC_REQ原语, 其中携带激活呼叫偏转业务的Facility IE
 输入参数  : CallId      - 呼叫的ID
             pstRedirNum - 偏转号码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_SendCcDeflectFacility(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstRedirNum
);

/*****************************************************************************
 函 数 名  : MN_CALL_SendCcActCcbsReq
 功能描述  : 发送MNCC_REL_REQ原语, 其中携带激活CCBS业务的Facility IE
 输入参数  : CallId - 呼叫的ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-12-25
    作    者   : z00161729
    修改内容   :新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_SendCcActCcbsReq(
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 函 数 名  : MN_CALL_SendCcEstCnfReq
 功能描述  : 发送MNCC_CC_EST_CNF_REQ原语
 输入参数  : CallId        - 呼叫的ID
             ucRepeatInd   - Repeat Indicator, 如果pstBc2为空该参数将被忽略
             pstBc1        - Bear capability 1 (可选)
             pstBc2        - Bear capability 2 (可选), 如果pstBc1为空该参数将被忽略
             Cause         - 原因值
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-12-25
    作    者   : z00161729
    修改内容   :新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcEstCnfReq(
    MN_CALL_ID_T                        callId,
    MN_CALL_REP_IND_ENUM_U8             enRepeatInd,
    const NAS_CC_IE_BC_STRU             *pstBc1,
    const NAS_CC_IE_BC_STRU             *pstBc2,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
);

/*****************************************************************************
 函 数 名  : MN_CALL_SendCcbsSetupReq
 功能描述  : 发送MNCC_SETUP_REQ原语
 输入参数  : CallId        - 呼叫的ID

 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-12-25
    作    者   : z00161729
    修改内容   :新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcbsSetupReq(
    MN_CALL_ID_T                        callId
);

VOS_UINT32  MN_CALL_SendCcBufferedEmgSetupReq(
    MNCC_REQ_PRIM_MSG_STRU             *pstBufferdEmgSetupMsg
);

VOS_UINT32  MN_CALL_SendCcBufferedSetupReq(
    MNCC_REQ_PRIM_MSG_STRU             *pstBufferdSetupMsg
);


/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-11, begin */
#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID  TAF_CALL_SendCcSrvccCallInfoNtf(
    VOS_UINT8                           ucCallNum,
    MNCC_ENTITY_STATUS_STRU            *pstEntitySta
);
#endif
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-11, end */
VOS_VOID TAF_CALL_ProcCallStatusFail(
    VOS_UINT8                           ucCallId,
    MN_CALL_STATE_ENUM_U8               enCallState
);
VOS_VOID TAF_CALL_SendCcCallStatusNty(
    VOS_UINT8                           ucCallId,
    MNCC_CALL_STATUS_ENUM_UINT8         enCallStatus
);

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

#endif /* MN_CALL_SEND_CC_H */


