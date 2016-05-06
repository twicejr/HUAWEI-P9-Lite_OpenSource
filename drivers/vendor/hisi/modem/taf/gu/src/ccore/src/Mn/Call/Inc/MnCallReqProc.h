/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallReqProc.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年8月22日
  最近修改   : 2007年8月22日
  功能描述   : 应用请求处理模块的接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2007年8月22日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
******************************************************************************/
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


/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-15, begin */
/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-15, end */


/*****************************************************************************
  4 宏定义
*****************************************************************************/


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 接口函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : MN_CALL_CallOrigReqProc
 功能描述  : 处理来自应用层的主叫请求
             该函数将检查当前状态是否允许发起一个主叫，并且检查呼叫的号码以确定
             该号码是否被允许以及是否是紧急呼叫号码。检查通过后，向CC发送
             MNCC_SETUP_REQ或MNCC_EMERG_SETUP_REQ原语发起一个呼叫或紧急呼叫。
 输入参数  : clientId    - 发起该请求的Client的ID
             opId        - Operation ID, 标识本次操作
             callId      - 本次主叫的呼叫ID，用来唯一的标识这个呼叫
             pstOrigParm - 主叫请求中携带的参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_CallOrigReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    MN_CALL_ORIG_PARAM_STRU             *pstOrigParm
);

/*****************************************************************************
 函 数 名  : MN_CALL_InternalCallEndReqProc
 功能描述  : 释放呼叫本地资源，并向CC发送MNCC_DISC_REQ原语
 输入参数  : clientId    - 发起该请求的Client的ID
             opId        - Operation ID, 标识本次操作
             callId      - 需要挂断的呼叫的ID
             pstEndParm  - 挂断请求中携带的参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月17日
    作    者   : f62575
    修改内容   : DTS2013091104858，挂机前结束完成的用户请求
*****************************************************************************/
VOS_UINT32 MN_CALL_InternalCallEndReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_END_PARAM_STRU       *pstEndParm
);

/*****************************************************************************
 函 数 名  : MN_CALL_CallEndReqProc
 功能描述  : 处理来自应用层的挂断请求
             该函数将根据当前状态判断向CC发送MNCC_DISC_REQ还是MNCC_REL_REQ原语，
             然后发送原语来挂断呼叫。
 输入参数  : clientId    - 发起该请求的Client的ID
             opId        - Operation ID, 标识本次操作
             callId      - 需要挂断的呼叫的ID
             pstEndParm  - 挂断请求中携带的参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2013年11月04日                                                    
    作    者   : s00217060                                                         
    修改内容   : VoLTE_PhaseII项目
*****************************************************************************/
VOS_VOID  MN_CALL_CallEndReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        uccallId,
    const MN_CALL_END_PARAM_STRU        *pstEndParm
);

/*****************************************************************************
 函 数 名  : MN_CALL_CallAnswerReqProc
 功能描述  : 处理来自应用层的应答请求
             该函数将检查当前状态是否允许接听一个来电，检查通过后向CC发送
             MNCC_SETUP_RES原语接听来电
 输入参数  : clientId    - 发起该请求的Client的ID
             opId        - Operation ID, 标识本次操作
             callId      - 需要接听的呼叫的ID
             pstAnsParam - 应答请求中携带的参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_CallAnswerReqProc(
    MN_CLIENT_ID_T                      ucClientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_ANS_PARAM_STRU        *pstAnsParam
);

/* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
/*****************************************************************************
 函 数 名  : MN_CALL_CallSupsCmdReqProc
 功能描述  : 处理来自应用层的补充业务操作请求
             该函数根据应用发起的补充业务操作类型和当前所有呼叫的状态，向CC发送
             一条或多条原语，并记录下期望得到的网络的响应，以便在收到网络的响应
             时能判断出整个操作是否已执行完成，或是否需要发送后续的原语
 输入参数  : clientId    - 发起该请求的Client的ID
             opId        - Operation ID, 标识本次操作
             pstSsParm   - 补充业务操作参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
*****************************************************************************/
VOS_VOID  MN_CALL_CallSupsCmdReqProc(struct MsgCB *pstCallSups);
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

/*****************************************************************************
 函 数 名  : MN_CALL_BuildNormalCallReqProc
 功能描述  : 处理来自应用层的普通请求
             该函数构造普通呼叫的Setup消息
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             callId         - 本次主叫的呼叫ID，用来唯一的标识这个呼叫
             pstOrigParam   - 主叫请求中携带的参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 周君 40661
    修改内容   : 新生成函数
  2.日    期   : 2012年02月24日
    作    者   : 傅映君/f62575
    修改内容   : C50_IPC Project 为适配FDN业务CALL SETUP消息的所有信息均从呼叫实体获取
*****************************************************************************/
VOS_UINT32  MN_CALL_BuildNormalCallReqProc(MN_CALL_ID_T callId);

/*****************************************************************************
 函 数 名  : MN_CALL_GetMoCallBc
 功能描述  : 获取呼叫的BC信息
 输入参数  : pstCallInfo         - 呼叫的ID
 输出参数  : pstBc1    -
             pstBc2    -
             penBcRepeatInd
 返 回 值  : VOS_UINT32
                VOS_ERR        获取呼叫的BC信息失败
                VOS_OK         获取呼叫的BC信息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月23日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MN_CALL_GetMoCallBc(
    MN_CALL_ID_T                        CallId,
    NAS_CC_IE_BC_STRU                  *pstBc1,
    NAS_CC_IE_BC_STRU                  *pstBc2,
    MN_CALL_REP_IND_ENUM_U8            *penBcRepeatInd
);


VOS_VOID MN_CALL_ReportEccNumList(VOS_VOID);

/* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
/*****************************************************************************
 函 数 名  : MN_CALL_StkCallOrigReqProc
 功能描述  : 处理来自STK模块的呼叫请求
 输入参数  : pstOrigParam   - STK主叫请求中携带的参数
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级，修改函数入口参数

*****************************************************************************/
VOS_VOID MN_CALL_StkCallOrigReqProc(struct MsgCB * pstMsg);
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */

/* Added by y00245242 for V3R3C60_eCall项目, 2014-5-5, begin */
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
/* Added by y00245242 for V3R3C60_eCall项目, 2014-5-5, end */

/*****************************************************************************
 函 数 名  : MN_CALL_MakeNewCall
 功能描述  : 创建新的主叫
 输入参数  : MN_CALL_TYPE_ENUM_U8                enCallType   用户下发的新呼叫类型
 输出参数  : MN_CALL_ID_T                        *pNewCallId  新呼叫CALLID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月21日
    作    者   : f62575
    修改内容   : 新生成函数

  2.日    期   : 2012年9月25日
    作    者   : A00165503
    修改内容   : STK&DCM项目: CS域错误码上报
*****************************************************************************/
VOS_UINT32 MN_CALL_MakeNewCall(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_ID_T                       *pNewCallId
);


/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-8, begin */
VOS_VOID  MN_CALL_RcvAtCssnSetReq(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_SET_CSSN_REQ_STRU          *pstSetCssnReq
);
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-8, end */
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


/* Added by l00198894 for V9R1 STK升级, 2013/07/11, begin */
VOS_VOID  TAF_CALL_RcvStartDtmfReq(struct MsgCB * pstMsgSend);

VOS_VOID  TAF_CALL_RcvStopDtmfReq(struct MsgCB * pstStopDtmf);
/* Added by l00198894 for V9R1 STK升级, 2013/07/11, end */

/* Added by y00245242 for V3R3C60_eCall项目, 2014-3-29, begin */
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
/* Added by y00245242 for V3R3C60_eCall项目, 2014-3-29, end */

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

