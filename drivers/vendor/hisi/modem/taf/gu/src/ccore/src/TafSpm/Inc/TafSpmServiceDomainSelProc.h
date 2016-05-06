/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmServiceDomainSelProc.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2013年7月16日
  最近修改   :
  功能描述   : TafSpmServiceDomainSelProc.h的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月16日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/
#ifndef _TAF_SPM_SERVICE_DOMAIN_SEL_PROC_H_
#define _TAF_SPM_SERVICE_DOMAIN_SEL_PROC_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "PsTypeDef.h"
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-10-17, begin */
#include  "MnCallApi.h"
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-10-17, end */
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
/*****************************************************************************
 枚举名    : TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8
 枚举说明  : 域选择结果类型
 1.日    期   : 2013年9月24日
   作    者   : y00245242
   修改内容   : 新建
 2.日    期   : 2014年7月08日
   作    者   : w00176964
   修改内容   : DSDS III修改
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

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-16, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-16, end */

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
/*****************************************************************************
 函 数 名  : TAF_SPM_ProcReqMsgBasedOnCsOverIp
 功能描述  : 处理基于SIP信令承载的请求消息，通过消息跳转表，选择对应的消息处理
             函数

 输入参数  : ulEventType -- 由PID与message name组成
             pstMsg      -- 消息地址

 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息已经处理
             VOS_FALSE: 消息未处理完
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcReqMsgBasedOnCsOverIp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvRegisterSsReqBasedOnCsOverIp
 功能描述  : 处理来自AT或STK的register SS请求消息
 输入参数  : pstRcvMsg  消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE  消息已处理

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvRegisterSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvEraseSsReqBasedOnCsOverIp
 功能描述  : 处理来自AT或STK的SS erase请求消息
 输入参数  : pstRcvMsg  消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE  消息已处理

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvEraseSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvActivateSsReqBasedOnSipSignallingType
 功能描述  : 处理来自AT或STK的SS activate请求消息
 输入参数  : pstRcvMsg  消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE  消息已处理

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvActivateSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvDeactivateSsReqBasedOnSipSignallingType
 功能描述  : 处理来自AT或STK的SS deactivate请求消息
 输入参数  : pstRcvMsg  消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE  消息已处理

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvDeactivateSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvInterrogateSsReqBasedOnCsOverIp
 功能描述  : 处理来自AT或STK的SS interrogate请求消息
 输入参数  : pstRcvMsg  消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE  消息已处理

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvInterrogateSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvProcUssSsReqBasedOnCsOverIp
 功能描述  : 处理来自AT或STK的SS process Ussd请求消息
 输入参数  : pstRcvMsg  消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE  消息已处理

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvProcUssSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvRleaseSsReqBasedOnCsOverIp
 功能描述  : 处理来自AT或STK的SS release请求消息
 输入参数  : pstRcvMsg  消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE  消息已处理

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
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
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-18, begin */
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

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-18, end */

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvSendRpdataDirectBasedOnCsOverIp
 功能描述  : 处理来自AT或STK的SMS RP DATA消息，设置消息路由类型为IMS
 输入参数  : pstRcvMsg  消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE  消息已处理

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月11日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvSendRpdataDirectBasedOnCsOverIp(
    struct MsgCB                       *pstRcvMsg
);

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvSendRpdataFromMemBasedOnCsOverIp
 功能描述  : 处理从memory中发送的SMS的消息，设置消息路由类型为IMS
 输入参数  : pstRcvMsg  消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE  消息已处理

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月11日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
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

/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, begin */
VOS_UINT32 TAF_SPM_ProcCcSrvReqProtectTimerExpired(VOS_VOID);

VOS_UINT32 TAF_SPM_ProcSsSrvReqProtectTimerExpired(VOS_VOID);

VOS_UINT32 TAF_SPM_ProcSmsSrvReqProtectTimerExpired(
    struct MsgCB                       *pstMsg
);
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, end */

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

/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcReqMsgBasedOnNasSignalling
 功能描述  : 处理将基于GUL信令发送的APP的请求消息
 输入参数  : ulEventType -- 由PID与message name组成
             pstRcvMsg   -- 消息指针

 输出参数  : 无
 返 回 值  : VOS_FALSE  消息未处理完成

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月31日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/

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

