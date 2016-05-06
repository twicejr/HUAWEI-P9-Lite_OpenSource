/******************************************************************************

                  版权所有 (C), 2001-2020, 华为技术有限公司

 ******************************************************************************
  文 件 名   : VcMntn.h
  版 本 号   : 初稿
  作    者   : j00174725
  生成日期   : 2014年04月16日
  功能描述   : VC模块可维可测头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年04月16日
    作    者   : j00174725
    修改内容   : 创建文件
******************************************************************************/
#ifndef  VC_MNTN_H
#define  VC_MNTN_H


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#include "PsTypeDef.h"
#include "AppVcApi.h"
/* Added by wx270776 for OM融合, 2015-6-27, begin */
#include "TafLog.h"
/* Added by wx270776 for OM融合, 2015-6-27, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 调试输出 */
#define VC_INFO_LOG(str)      TAF_LOG(WUEPS_PID_VC, 0, PS_LOG_LEVEL_INFO, str)
#define VC_NORM_LOG(str)      TAF_LOG(WUEPS_PID_VC, 0, PS_LOG_LEVEL_NORMAL, str)
#define VC_WARN_LOG(str)      TAF_LOG(WUEPS_PID_VC, 0, PS_LOG_LEVEL_WARNING, str)
#define VC_ERR_LOG(str)       TAF_LOG(WUEPS_PID_VC, 0, PS_LOG_LEVEL_ERROR, str)

#define VC_INFO_LOG1(str, x)  TAF_LOG1(WUEPS_PID_VC, 0, PS_LOG_LEVEL_INFO, str, x)
#define VC_NORM_LOG1(str, x)  TAF_LOG1(WUEPS_PID_VC, 0, PS_LOG_LEVEL_NORMAL, str, x)
#define VC_WARN_LOG1(str, x)  TAF_LOG1(WUEPS_PID_VC, 0, PS_LOG_LEVEL_WARNING, str, x)
#define VC_ERR_LOG1(str, x)   TAF_LOG1(WUEPS_PID_VC, 0, PS_LOG_LEVEL_ERROR, str, x)

#define VC_WARN_LOG2(str, x1, x2)   TAF_LOG2(WUEPS_PID_VC, 0, PS_LOG_LEVEL_WARNING, str, x1, x2)
#define VC_ERR_LOG2(str, x1, x2)    TAF_LOG2(WUEPS_PID_VC, 0, PS_LOG_LEVEL_ERROR, str, x1, x2)

/* 封装可维可测事件消息头 */
#define VC_MNTN_CFG_MSG_HDR(pstMsg, enEventId, ulEventLen)\
            (pstMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;\
            (pstMsg)->ulSenderPid     = WUEPS_PID_VC;\
            (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
            (pstMsg)->ulReceiverPid   = WUEPS_PID_VC;\
            (pstMsg)->ulLength        = (ulEventLen);\
            (pstMsg)->enMsgId         = (enEventId)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : VC_MNTN_HOOK_MSG_ID_ENUM
 枚举说明  : 定义AT到AT内部消息ID

  1.日    期   : 2013年11月06日
    作    者   : j00174725
    修改内容   : 定义AT到AT内部消息ID
*****************************************************************************/
enum VC_MNTN_HOOK_MSG_ID_ENUM
{
    ID_VC_MNTN_HOOK_MSG_STATE_MGMT      = 0,                                    /* _H2ASN_MsgChoice VC_MNTN_STATE_MGMT_STRU */

    ID_VC_MNTN_HOOK_MSG_BUTT
};
typedef VOS_UINT32 VC_MNTN_HOOK_MSG_ID_ENUM_UINT32;

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : VC_MNTN_ECALL_CTX_STRU
 结构说明  : ecall 上下文可维可测定义
 1.日    期   : 2014年3月27日
   作    者   : j00174725
   修改内容   : Ecall项目
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucMsdData[APP_VC_MSD_DATA_LEN];     /* 用于保存APP下发的MSD数据 */
    PS_BOOL_ENUM_UINT8                      enMsdFlag;                          /* 用于记录是否下发过MSD数据 */
    PS_BOOL_ENUM_UINT8                      enInECall;                          /* 当前是否在eCall呼叫过程中 */
    PS_BOOL_ENUM_UINT8                      enAllowSetMsdFlag;                  /* 是否允许发送数据 */
    APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8    enEcallState;                       /* MSD传送状态 */
    APP_VC_ECALL_MSD_MODE_ENUM_UINT16       enNewEcallMode;                     /* 用于保存最新APP下发的eCall配置信息(数据传送模式) */
    APP_VC_ECALL_VOC_CONFIG_ENUM_UINT16     enNewEcallVocConfig;                /* 用于保存最新APP下发的eCall配置信息(是否在传送数据时打开声码器) */
    APP_VC_ECALL_MSD_MODE_ENUM_UINT16       enCurrEcallMode;                    /* 用于保存当前MED使用的eCall配置信息(数据传送模式) */
    APP_VC_ECALL_VOC_CONFIG_ENUM_UINT16     enCurrEcallVocConfig;               /* 用于保存当前MED使用的eCall配置信息(是否在传送数据时打开声码器) */
    VOS_UINT32                              ulEcallDescription;                 /* MSD传送状态描述,若表示允许更新MSD的时间窗长度，整数值，单位：毫秒，范围：500~10000 */
}VC_MNTN_ECALL_CTX_STRU;

/*****************************************************************************
 结构名    : VC_MNTN_MSDFLAG_STRU
 结构说明  : VC状态管理可维可测结构

  1.日    期   : 2014年04月16日
    作    者   : n00269697
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulInCall;                           /* 当前是否在呼叫过程中 */
    VOS_UINT32                              ulVoiceTestFlag;
    VC_MNTN_ECALL_CTX_STRU                  stVcEcallCtx;
}VC_MNTN_HOOK_CTX_INFO;


/*****************************************************************************
 结构名    : VC_MNTN_MSDFLAG_STRU
 结构说明  : VC状态管理可维可测结构

  1.日    期   : 2014年04月16日
    作    者   : n00269697
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VC_MNTN_HOOK_MSG_ID_ENUM_UINT32     enMsgId;                                /* _H2ASN_Skip *//* 消息类型 */
    VC_MNTN_HOOK_CTX_INFO               stVcCtxInfo;                            /* VC状态管理结构 */
} VC_MNTN_STATE_MGMT_STRU;

/*****************************************************************************
  7 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID NAS_MNTN_FailtoOpenCsChannel(
    VOS_UINT16                          usPort,
    VOS_UINT32                          ulOmOperResult
);
VOS_VOID NAS_MNTN_CsMedTimeOut(
    VOS_UINT32                          ulTimerId
);
VOS_VOID VC_MNTN_TraceEvent(
    VOS_VOID                           *pMsg
);
VOS_VOID VC_MNTN_TraceCtxInfo(VOS_VOID);

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    VC_MNTN_HOOK_MSG_ID_ENUM_UINT32    enMsgId;                                /* _H2ASN_MsgChoice_Export VC_MNTN_HOOK_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                          aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          VC_MNTN_HOOK_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} VC_MNTN_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    VC_MNTN_MSG_DATA                    stMsgData;
} VcMntn_MSG;



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

#endif /* VC_MNTN_H */


