/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasCcMmccSend.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年10月17日
  最近修改   : 2007年10月17日
  功能描述   : MMCC原语发送模块的接口
  函数列表   :
  修改历史   :
  1.日    期   : 2007年10月17日
    作    者   : 丁庆 49431
    修改内容   : 创建文件

  2.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
******************************************************************************/
#ifndef  NAS_CC_MMCC_SEND_H
#define  NAS_CC_MMCC_SEND_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "MmCcInterface.h"

/*****************************************************************************
  2 函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccAbortReq
 功能描述  : 发送MMCC_ABORT_REQ原语
 输入参数  : ucTi - Transaction ID
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccAbortReq(
    VOS_UINT8                           ucTi
);


/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccRelReq
 功能描述  : 发送MMCC_REL_REQ原语
 输入参数  : ucTi      - Transaction ID
             ulRelType - 释放的类型(MMCC_RELEASE_ALL/MMCC_RELEASE_SPECIFIC)
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccRelReq(
    VOS_UINT8                           ucTi,
    VOS_UINT32                          ulRelType
);


/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccEstReq
 功能描述  : 发送MMCC_EST_REQ原语
 输入参数  : ucTi       - Transaction ID
             ulCallType - 呼叫的类型(紧急呼叫/普通呼叫)
             ulPriority - 呼叫的优先级
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

  2.日    期   : 2010年3月1日
    作    者   : zhoujun /z40661
    修改内容   : 增加当前电话模式，可视电话或语音电话
  3.日    期   : 2015年8月13日
    作    者   : s00217060
    修改内容   : User_Exp_Improve修改：增加redial入参
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccEstReq(
    VOS_UINT8                           ucTi,
    VOS_UINT32                          ulCallType,
    VOS_UINT32                          ulCallMode,
    VOS_UINT32                          ulPriority,
    VOS_UINT8                           ucRedialFlg
);


/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccDataReq
 功能描述  : 发送MMCC_DATA_REQ原语
 输入参数  : ucTi        - Transaction ID
             pucCcMsg    - 原语中携带的CC消息
             ulCcMsgSize - CC消息的长度
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccDataReq(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           *pucCcMsg,
    VOS_UINT32                          ulCcMsgSize
);


/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccPromptRej
 功能描述  : 发送MMCC_PROMPT_REJ原语
 输入参数  : ulCause - 拒绝的原因
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccPromptRej(
    VOS_UINT32                          ulCause
);


/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccReestReq
 功能描述  : 发送MMCC_REEST_REQ原语
 输入参数  : ucTi - Transaction ID
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccReestReq(
    VOS_UINT8                           ucTi
);

/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccStartCc
 功能描述  : 发送MMCC_START_CC原语
 输入参数  : ucTi      - Transaction ID
             pucCcMsg  - 原语中携带的CC消息
             ulCcMsgSize - CC消息的长度
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-12-25
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccStartCc(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           *pucCcMsg,
    VOS_UINT32                          ulCcMsgSize
);
VOS_VOID  NAS_CC_SendMmccCallStatusNty(
    MMCC_CALL_STATUS_ENUM_UINT8         enCallStatus
);

/* Added by n00355355 for 呼叫重建, 2015-9-17, begin */
//VOS_VOID NAS_CC_SendMmccCallInfoCnf(VOS_VOID);
VOS_VOID NAS_CC_SendMmccCallInfoCnf(
    MMCC_CALL_INFO_STRU                *pstCallInfo
);


/* Added by n00355355 for 呼叫重建, 2015-9-17, end */

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, begin */
#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID  NAS_CC_SendMmccSrvccCallInfoNtf(
    VOS_UINT8                           ucSyncTiNum,
    VOS_UINT8                          *pucSyncTi
);
#endif
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, end */

#if(FEATURE_ON == FEATURE_DSDS)
VOS_VOID  NAS_CC_SendMmccBeginSessionNotify(
    MMCC_SESSION_TYPE_ENUM_UINT8        enSessionType
);

VOS_VOID  NAS_CC_SendMmccEndSessionNotify(
    MMCC_SESSION_TYPE_ENUM_UINT8        enSessionType
);
#endif

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

#endif /* NAS_CC_MMCC_SEND_H */

