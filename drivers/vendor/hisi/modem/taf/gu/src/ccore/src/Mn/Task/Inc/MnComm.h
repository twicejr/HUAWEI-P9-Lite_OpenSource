/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnComm.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2008年1月10日
  最近修改   : 2008年1月10日
  功能描述   : 该文件包含所有在TAF子系统中公共使用的常量、宏、变量和函数
  函数列表   :
  修改历史   :
  1.日    期   : 2008年1月10日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
  2.日    期   : 2010年2月23日
    作    者   : f62575
    修改内容   : 问题单号：增加短信功能任意点回放功能
  3.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
  3.日    期   : 2010年04月10日
    作    者   : f62575
    修改内容   : 问题单号AT2D18035
                 写PDU短信到SIM卡,BALONG对TP-SCTS的检查与标杆不一致；
******************************************************************************/
#ifndef  MN_COMM_H
#define  MN_COMM_H

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
#include "Ps.h"

#include "TafTypeDef.h"
/* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
#include "TafClientApi.h"
/* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */
#include "product_config.h"
/* Added by L60609 for AT Project，2011-10-05,  Begin*/
#include "MnClient.h"
/* Added by L60609 for AT Project，2011-10-05,  End*/

/* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
#include "TafOamInterface.h"
#include "NasStkInterface.h"
#include "AppVcApi.h"
/* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-10-05, begin */
#include "TafMntn.h"
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-10-05, end */

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-16, begin */
#include "NasCcIe.h"
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-16, end */

#include "NasSms.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif
/* Added by wx270776 for OM融合, 2015-6-27, begin */
#include "msp_diag_comm.h"
#include "errorlog.h"
/* Added by wx270776 for OM融合, 2015-6-27, end */

#include "TafLog.h"

/*****************************************************************************
  2 常量定义
*****************************************************************************/

/* LOCAL */
#ifdef  LOCAL
#undef  LOCAL
#endif

#ifdef _EXPORT_LOCAL
#define LOCAL
#else
#define LOCAL static
#endif


/*****************************************************************************
 枚举名    : TAF_FDN_ME_STATUS_ENUM
 结构说明  : ME是否启动FDN业务检查
             0: TAF_FDN_CHECK_FEATURE_OFF  ME不启动FDN检查
             1: TAF_FDN_CHECK_FEATURE_ON   ME启动FDN检查
*****************************************************************************/
enum TAF_FDN_ME_STATUS_ENUM
{
    TAF_FDN_CHECK_FEATURE_OFF,
    TAF_FDN_CHECK_FEATURE_ON,
    TAF_FDN_CHECK_FEATURE_BUTT
};
typedef VOS_UINT32 TAF_FDN_ME_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TAF_FDN_FEATURE_STATUS_ENUM
 结构说明  : ME不支持FDN功能时是否参照协议禁止所有呼叫
             0: TAF_FDN_FEATURE_DISABLE  FDN功能
             1: TAF_FDN_FEATURE_ENABLE   FDN功能禁止所有呼叫
*****************************************************************************/
enum TAF_FDN_FEATURE_STATUS_ENUM
{
    TAF_FDN_FEATURE_DISABLE,
    TAF_FDN_FEATURE_ENABLE,
    TAF_FDN_FEATURE_BUTT
};
typedef VOS_UINT32 TAF_FDN_FEATURE_STATUS_ENUM_UINT32;


/* 定时器名称分类 */
enum
{
    MN_TIMER_CLASS_CCA                                      = 0,
    MN_TIMER_CLASS_MSG                                      = 0x00001000,
    MN_TIMER_CLASS_SSA                                      = 0x00002000,
    MN_TIMER_CLASS_MMA                                      = 0x00004000,
    MN_TIMER_CLASS_APS                                      = 0x00008000,
    MN_TIMER_CLASS_SPM                                      = 0x0000C000,
    MN_TIMER_CLASS_XCALL                                    = 0x0000D000,
    MN_TIMER_CLASS_MASK                                     = 0xfffff000
};

#define MN_MO_CTRL_LAI_LEN                                  (0xf)


/* 定义TAF_FID优先级 */
#define TAF_TASK_PRIORITY                                   (145)

/* 表示所有的Client */
#define MN_CLIENT_ALL                                       ((MN_CLIENT_ID_T)(-1))
#define MN_OP_ID_BUTT                                       ((MN_OPERATION_ID_T)(-1))


#define MN_COM_SRVDOMAIN_CS                                 (1)
#define MN_COM_SRVDOMAIN_PS                                 (2)

/* MN_USIM_STATUS_IND和MMCM_OM_MAINTAIN_INFO_IND放在了MMA_MN_MSG_TYPE_ENUM_UINT32中 */

#define MN_WORD_UCS2_ENCODE_LEN                             (2)


/*当前网络类型*/
#define MN_NET_MODE_INVALID                                 (3)                 /* 网络模式无效 */
#define MN_NET_MODE_LTE                                     (2)                 /* L模式 */
#define MN_NET_MODE_WCDMA                                   (1)                 /* W模式 */
#define MN_NET_MODE_GSM                                     (0)                 /* G模式 */

#define MN_MAX_GSM7BITDEFALPHA_NUM                          (128)


#define NAS_EVT_TYPE_DEF(ulSndPid, usMsgName) \
    (((VOS_UINT32)(/*lint -e778*/((ulSndPid) & 0xF0000)/*lint +e778*/ \
    | (((ulSndPid) & 0xFFF) << 4)) << 12) | (usMsgName))      /* 根据 Pid以及usMsgName 构建EventType  */





/* Added by L60609 for AT Project，2011-10-03,  Begin*/
#define MN_AT_INTERFACE_MSG_HEADER_LEN                      ((sizeof(MN_AT_IND_EVT_STRU) - VOS_MSG_HEAD_LENGTH) - 4)
/* Added by L60609 for AT Project，2011-10-03,  End*/

/*****************************************************************************
 枚举名    : TAF_SERVICE_TYPE_ENUM
 结构说明  : USIM上报TAF消息类型
  1.日    期   : 2013年01月18日
    作    者   : z00214637
    修改内容   : 新建
*****************************************************************************/
enum TAF_SERVICE_TYPE_ENUM
{
    TAF_SERVICE_TYPE_CALL           = 0,  /*call 类型 */
    TAF_SERVICE_TYPE_MSG            = 1,  /*MSG  类型 */
    TAF_SERVICE_TYPE_UNASSIGNED     = 2,  /*FDN INFO 开机主动上报消息 */
    TAF_SERVICE_TYPE_BUTT
};
typedef VOS_UINT32  TAF_SERVICE_TYPE_ENUM_U32;

/*****************************************************************************
 枚举名    : TAF_EMERGENCY_NOTIFY_ENUM
 结构说明  :
             0: TAF_EMERGENCY_NOTIFY_DISABLE  紧急呼叫与温保交互NV项关闭
             1: TAF_EMERGENCY_NOTIFY_ENABLE   紧急呼叫与温保交互NV项开启
*****************************************************************************/
enum TAF_EMERGENCY_NOTIFY_ENUM
{
    TAF_EMERGENCY_NOTIFY_DISABLE,
    TAF_EMERGENCY_NOTIFY_ENABLE,
    TAF_EMERGENCY_NOTIFY_BUTT
};
typedef VOS_UINT32 TAF_EMERGENCY_NOTIFY_ENUM_UINT8;



/*****************************************************************************
  3 宏定义
*****************************************************************************/
#define TAF_NUMTYE_INTERNAL_NUMBER                          (0x91)

extern VOS_UINT16 f_ausMnAsciiSfxDefAlpha[MN_MAX_GSM7BITDEFALPHA_NUM];


/* 调试输出 */
#define MN_INFO_LOG(str)                    TAF_LOG(WUEPS_PID_TAF, 0, PS_LOG_LEVEL_INFO, str)
#define MN_NORM_LOG(str)                    TAF_LOG(WUEPS_PID_TAF, 0, PS_LOG_LEVEL_NORMAL, str)
#define MN_WARN_LOG(str)                    TAF_LOG(WUEPS_PID_TAF, 0, PS_LOG_LEVEL_WARNING, str)
#define MN_ERR_LOG(str)                     TAF_LOG(WUEPS_PID_TAF, 0, PS_LOG_LEVEL_ERROR, str)

#define MN_INFO_LOG1(str, x1)               TAF_LOG1(WUEPS_PID_TAF, 0, PS_LOG_LEVEL_INFO, str, x1)
#define MN_INFO_LOG2(str, x1, x2)           TAF_LOG2(WUEPS_PID_TAF, 0, PS_LOG_LEVEL_INFO, str, x1, x2)
#define MN_INFO_LOG3(str, x1, x2, x3)       TAF_LOG3(WUEPS_PID_TAF, 0, PS_LOG_LEVEL_INFO, str, x1, x2, x3)
#define MN_INFO_LOG4(str, x1, x2, x3, x4)   TAF_LOG4(WUEPS_PID_TAF, 0, PS_LOG_LEVEL_INFO, str, x1, x2, x3, x4)

#define MN_NORM_LOG1(str, x)                TAF_LOG1(WUEPS_PID_TAF, 0, PS_LOG_LEVEL_NORMAL, str, x)
#define MN_WARN_LOG1(str, x)                TAF_LOG1(WUEPS_PID_TAF, 0, PS_LOG_LEVEL_WARNING, str, x)
#define MN_WARN_LOG2(str, x1,x2)            TAF_LOG2(WUEPS_PID_TAF, 0, PS_LOG_LEVEL_WARNING, str,x1,x2)
#define MN_ERR_LOG1(str, x)                 TAF_LOG1(WUEPS_PID_TAF, 0, PS_LOG_LEVEL_ERROR, str, x)


/* ASSERT */
#ifdef  _DEBUG
#define  MN_ASSERT(expr) \
    if(!(expr)) \
    { \
        MN_ERR_LOG("Assertion failed: " #expr); \
    }
#else
#define  MN_ASSERT(expr)  ((VOS_VOID)0)
#endif /* _DEBUG */

#define MN_GET_TON(enNumType, ucAddrType) ((enNumType) = ((ucAddrType >> 4) & 0x07))
#define MN_GET_NPI(enNumPlan, ucAddrType) ((enNumPlan) = (ucAddrType & 0x0f))
#define MN_GET_ADDRTYPE(ucAddrType, enNumType, enNumPlan)                           \
                        ((ucAddrType) = 0x80 | (VOS_UINT8)((enNumType) << 4) | enNumPlan)

#if !defined(MN_ARRAY_SIZE)
#define MN_ARRAY_SIZE(a)                (sizeof((a)) / sizeof((a[0])))
#endif
#define TAF_CS_GET_CC_ERR_CODE_MAP_TBL_PTR()   (g_astMnCallErrCodeMapTbl)
#define TAF_CS_GET_CC_ERR_CODE_MAP_TBL_SIZE()  (sizeof(g_astMnCallErrCodeMapTbl)/sizeof(TAF_CS_ERR_CODE_MAP_STRU))
/*****************************************************************************
  4 结构定义
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatus;                               /*是否激活，0不激活，1激活 */
    VOS_UINT32                          ulCustomizeService;                     /*终端说明书是1个byte，为了没有空洞，扩充成4byte，高3byte保留*/
}MN_NV_ITEM_CUSTOMIZE_SERV_STRU;

/*SMA定时器ID的定义*/
enum MN_MSG_TIMER_ID_ENUM
{
    MN_MSG_TID_WAIT_GET_EF_RSP                             = MN_TIMER_CLASS_MSG,/*初始化,读取USIM中EFSMSS,EFSMSP,EFSMSR,EFSMS文件启动的定时器*/
    MN_MSG_TID_LINK_CTRL,                                                       /*初始化,读取USIM中EFSMSS,EFSMSP,EFSMSR,EFSMS文件启动的定时器*/
    MN_MSG_TID_WAIT_USIM,
    MN_MSG_ID_WAIT_RETRY_PERIOD,                                                /* 短信重发时间周期 */
    MN_MSG_ID_WAIT_RETRY_INTERVAL,                                              /* 短信重发时间间隔 */
    MN_MGS_ID_WAIT_FDN_CHECK,                                                   /* 等待FDN检查结果 */
    MN_MGS_ID_WAIT_MO_SMS_CTRL_CHECK,                                           /* 等待MO SMS CONTROL检查结果 */
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    TI_TAF_CBA_WAIT_GET_CB_EF_RSP,
#if (FEATURE_ON == FEATURE_ETWS)
    TI_TAF_CBA_RCV_ETWS_TEMP_ENABLE_CBS,                                        /* CBS未开启时，收到主通知时临时使能CBS的Timer */
#endif
#endif
    MN_MSG_TID_MAX
};
typedef VOS_UINT32 MN_MSG_TIMER_ID_ENUM_U32;

/* 来自RABM的请求消息结构 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;                              /* 消息名 */
    VOS_UINT8                           aucReserve1[2];                             /* 保留 */
} MN_RABM_IND_MSG_STRU;

/* Added by L60609 for AT Project，2011-10-05,  Begin*/
/*应用查询参数:f_astMnQryMsgParaAttr*/
typedef struct
{
    TAF_PARA_TYPE                       QueryType;
    TAF_UINT8                           aucReserve1[3];
    TAF_UINT32                          ulFixedPartLen;
}MN_QRYMSGPARA_ATTR;

typedef struct{
    TAF_PARA_TYPE                       QueryType;
    TAF_UINT8                           aucReserve1[3];
    TAF_UINT32                          ulVarPartLen;
}MN_QRYMSGVARLEN_UNIT_STRU;
/* Added by L60609 for AT Project，2011-10-05,  End*/

/*****************************************************************************
 结构名    : TAF_FDN_CONFIG_STRU
 结构说明  : FDN业务特性参数结构
             enMeStatus         ME是否启动FDN业务检查
1.日    期   : 2012年02月23日
  作    者   : f62575
  修改内容   : 创建
*****************************************************************************/
typedef struct
{
    TAF_FDN_ME_STATUS_ENUM_UINT32       enMeStatus;
}TAF_FDN_CONFIG_STRU;


/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
typedef VOS_VOID (*TAF_STK_MSG_FUNC_MAP)(struct MsgCB * pstMsg);

/*****************************************************************************
 结构名    : MN_STK_MSG_FUNC_MAP_STRU
 结构说明  : STK消息分发结果
  1.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulAppMsgName;
    TAF_STK_MSG_FUNC_MAP                pStkMsgFunc;
}MN_STK_MSG_FUNC_MAP_STRU;

/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */


/*****************************************************************************
  5 函数声明
*****************************************************************************/
/* 检查USIM是否可用 */
VOS_BOOL  MN_IsUsimPresent(VOS_VOID);

/* 设置USIM的可用状态 */
VOS_VOID  MN_SetUsimPresent(
    VOS_BOOL                            bPresent
);

/* 向指定的Client发送异步请求的响应 */
VOS_VOID  MN_SendClientResponse(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulErrorCode
);

/* 向指定的或所有的Client上报事件 */
VOS_VOID  MN_SendClientEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_CALLBACK_TYPE_T                  callbackType,
    VOS_UINT32                          ulEventType,
    VOS_VOID                            *pEventContent
);


/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
/* Deleted MN_UnPack7Bit, MN_Pack7Bit */
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */

/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */


/*号码类型检查,参考协议23040 9.1.2.5*/
TAF_UINT32 MN_ChkNumType(
    MN_MSG_TON_ENUM_U8                  enNumType
);

/*拨号计划类型检查,参考协议23040 9.1.2.5*/
TAF_UINT32 MN_ChkNumPlan(
    MN_MSG_NPI_ENUM_U8                  enNumPlan
);

/*设置指定索引节点的位图*/
VOS_VOID MN_SetBitMap(
    VOS_UINT32                          *pulBitMap,
    VOS_UINT32                          ulIndex,
    VOS_BOOL                            bReset
);

/*获取指定索引节点的位图*/
VOS_UINT32 MN_GetBitMap(
    VOS_UINT32                          *pulBitMap,
    VOS_UINT32                          ulIndex
);

extern VOS_INT8 NAS_Common_Get_Supported_3GPP_Version(VOS_UINT32 ulCnDomainId);

/*比较ASCII字符串和UCS2字符串,比较结果作为输出参数输出
  此函数仅作UCS2高位为0情况的比较: 比较UCS2的低位和ASCII码*/
VOS_VOID MN_CmpAsciiStrAndUcs2StrCaseInsensitive(
    VOS_UINT8                           *pucUcs2Str,
    VOS_UINT32                          ulUcs2Strlen,
    VOS_UINT8                           *pucAsciiStr,
    VOS_BOOL                            *pbEqualFlag
);

VOS_UINT32 MN_DeciDigit2Ascii(
    VOS_UINT8                           aucDeciDigit[],
    VOS_UINT32                          ulLength,
    VOS_UINT8                           aucAscii[]
);

/* 获取当前发送短信时,短信的实际发送域 */
VOS_VOID MN_MSG_GetCurSendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain,
    MN_MSG_SEND_DOMAIN_ENUM_U8          *penRealSendDomain
);

/* 短信发送相关信息导出到异常事件记录 */
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
VOS_VOID MN_MSG_OutputSmsMoFailureInfo(
    TAF_MSG_ERROR_ENUM_UINT32           enErrorCode,
    NAS_MNTN_SMS_MO_INFO_STRU          *pstSmsMo
);
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

/* 记录短信发送失败事件 */
VOS_VOID MN_MNTN_RecordSmsMoFailure(TAF_MSG_ERROR_ENUM_UINT32 enErrorCode);
VOS_UINT32 MN_GetFileSize(
    FILE                                *fp,
    VOS_UINT32                          *pulFileSize
);

/* 记录短信ME操作失败事件 */
VOS_VOID MN_MNTN_RecordSmsMeError (
    MNTN_ME_OPERATION_ENUM_UINT32       enOperation,
    VOS_UINT32                          ulErrorNo
);

/* Added by L60609 for AT Project，2011-10-05,  Begin*/
VOS_VOID MN_CS_SendMsgToOam(
    MN_CLIENT_ID_T                      clientId,
    MN_CALL_EVENT_ENUM_U32              enEventType,
    VOS_UINT32                          ulOamRcvPid,
    MN_CALL_INFO_STRU                  *pstEvent
);

VOS_VOID MN_CS_SendMsg(
    MN_CLIENT_ID_T                      usClientId,
    MN_CALL_EVENT_ENUM_U32              enEventType,
    MN_CALL_INFO_STRU                  *pstEvent
);

VOS_VOID MN_MSG_SendMsg(
    MN_CLIENT_ID_T                      usClientId,
    MN_MSG_EVENT_ENUM_U32               enEventType,
    MN_MSG_EVENT_INFO_STRU             *pstEvent
);


VOS_VOID  MN_SendReportMsg(TAF_UINT8 ucType,TAF_UINT8* pData,TAF_UINT16 usLen);

VOS_VOID MN_SS_SendMsg(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulEventType,
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent
);


VOS_VOID MN_CMDCNF_SendMsg(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_UINT32                          ulErrorCode
);

/* Added by s00246516 for L-C互操作项目, 2014-3-31, Begin */
MN_CLIENT_ID_TYPE_UINT16 MN_GetClientIdType(MN_CLIENT_ID_T usClientId);

VOS_UINT32 MN_GetPidFromClientId(MN_CLIENT_ID_T usClientId);
/* Added by s00246516 for L-C互操作项目, 2014-3-31, End */

VOS_VOID MN_PH_SendMsg(MN_CLIENT_ID_T usClientId,VOS_UINT8 *pEvent,VOS_UINT32 ulLen);

VOS_VOID MN_DATASTATUS_SendMsg(
    TAF_UINT16                          usClientId,
    TAF_UINT8                           ucDomain,
    TAF_UINT8                           ucRabId,
    TAF_UINT8                           ucStatus,
    TAF_UINT8                           ucCause
);

VOS_VOID MN_SETPARA_SendMsg(
    TAF_UINT16                          usClientId,
    TAF_UINT8                           ucOpId,
    TAF_PARA_SET_RESULT                 ucResult,
    TAF_PARA_TYPE                       ucParaType,
    TAF_VOID                           *pPara
);

VOS_VOID MN_QRYPARA_SendMsg(
    TAF_UINT16                          usClientId,
    TAF_UINT8                           ucOpId,
    TAF_PARA_TYPE                       ucQueryType,
    TAF_UINT16                          usErrorCode,
    TAF_VOID                           *pPara
);

VOS_VOID MN_QRYPARA_SendMsgToAt  (
    TAF_UINT16                          usClientId,
    TAF_UINT8                           OpId,
    TAF_PARA_TYPE                       QueryType,
    TAF_UINT16                          usErrorCode,
    TAF_VOID                           *pPara
);

VOS_VOID MN_VC_SendMsgToAt(
    MN_CLIENT_ID_T                      clientId,
    VOS_UINT32                          ulEventType,
    APP_VC_EVENT_INFO_STRU             *pstEvent
);
VOS_VOID MN_PH_SendMsgToAt(VOS_UINT8  *pEvent,VOS_UINT32 ulLen);
#if ( FEATURE_ON == FEATURE_LTE )
VOS_UINT32 MN_APS_TransCsqReqToL4a(
    VOS_UINT16                      ucClientId,
    VOS_INT8                        ucOpId
);
#endif

VOS_VOID MN_VC_SendMsg(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulEventType,
    APP_VC_EVENT_INFO_STRU             *pstEvent
);


/* Added by L60609 for AT Project，2011-10-05,  End*/

/* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
VOS_VOID MN_MSG_ProcAppSend(struct MsgCB * pstMsgSend);
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
VOS_VOID TAF_ProcStkEnvelopeCnf(struct MsgCB * pstMsg);
VOS_VOID  MN_SndAppMsgToSs (struct MsgCB *pstMsg);
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */
#if (VOS_WIN32 == VOS_OS_VER)
VOS_VOID  MN_ProcUsimMsg (struct MsgCB * pstMsg);
#endif



/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */

/* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-20, begin */
TAF_CS_CAUSE_ENUM_UINT32 TAF_CALL_MapCcCauseToCsCause(
    MN_CALL_CC_CAUSE_ENUM_U8            enCcCause
);
/* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-20, end */

/* Delete MN_GetLaiForMoCtrl */

MN_CLIENT_ID_T MN_GetRealClientId(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulPid
);

VOS_VOID MN_CS_SendMsgToAt(
    MN_CLIENT_ID_T                      clientId,
    MN_CALL_EVENT_ENUM_U32              enEventType,
    MN_CALL_INFO_STRU                  *pstEvent
);

VOS_VOID MN_MSG_SendMsgToAt(
    MN_CLIENT_ID_T                      clientId,
    MN_MSG_EVENT_ENUM_U32               enEventType,
    MN_MSG_EVENT_INFO_STRU             *pstEvent
);

VOS_VOID MN_SS_SendMsgToAt(
    MN_CLIENT_ID_T                      clientId,
    VOS_UINT32                          ulEventType,
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent
);

VOS_VOID MN_CMDCNF_SendMsgToAt(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_UINT32                          ulErrorCode
);

VOS_VOID MN_DATASTATUS_SendMsgToAt(
    TAF_UINT16                          ClientId,
    TAF_UINT8                           ucDomain,
    TAF_UINT8                           ucRabId,
    TAF_UINT8                           ucStatus,
    TAF_UINT8                           ucCause
);

VOS_VOID MN_SETPARA_SendMsgToAt(
    TAF_UINT16                          ClientId,
    TAF_UINT8                           OpId,
    TAF_PARA_SET_RESULT                 Result,
    TAF_PARA_TYPE                       ParaType,
    TAF_VOID                           *pPara
);
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
VOS_UINT32 TAF_CALL_IsEventNeedRpt(
    MN_CALL_EVENT_ENUM_U32              enEventType
);
VOS_UINT32 TAF_MSG_IsEventNeedRpt(
    MN_MSG_EVENT_ENUM_U32              enEventType
);
VOS_UINT32 TAF_SS_IsEventNeedRpt (
    TAF_SS_EVENT  ulEvent
);

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

VOS_VOID MN_CS_ProcEmergencyCallEvent(
    MN_CALL_EVENT_ENUM_U32              enEventType,
    MN_CALL_INFO_STRU                  *pstEvent
);

VOS_VOID MN_SendEmergencyCallStatusToOam(
    TAF_OAM_EMERGENCY_CALL_STATUS_ENUM_UINT8                enEventType
);

/* Added by l00198894 for V9R1 STK升级, 2013/07/11, begin */
VOS_VOID TAF_CALL_SendMsg(
    MN_CLIENT_ID_T                      usClientId,
    MN_CALL_EVENT_ENUM_U32              enEventType,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
);
/* Added by l00198894 for V9R1 STK升级, 2013/07/11, end */

/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
VOS_UINT32 TAF_GetSpecificFileListRefreshFileInfo(
    VOS_UINT16                          usFileId,
    USIMM_STKREFRESH_IND_STRU           *pstRefreshInd,
    USIMM_CARDAPP_ENUM_UINT32          *penAppType
);
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

/* Added by l00198894 for V9R1 干扰控制, 2013/08/19, begin */
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
VOS_VOID TAF_SendMtcCsSrvInfoInd(VOS_VOID);
#endif
/* Added by l00198894 for V9R1 干扰控制, 2013/08/19, end */

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-16, begin */
/*****************************************************************************
 函 数 名  : MN_CALL_GetDataCfgInfoFromBc
 功能描述  : 从BC中获取数据业务配置参数，由于API下发的speed参数和上报的不同，
             需要对speed进行转换
 输入参数  : pstSsCompo - 来自网络的Facility IE中的SS component
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_GetDataCfgInfoFromBc(
    const NAS_CC_IE_BC_STRU             *pstBc,
    MN_CALL_CS_DATA_CFG_INFO_STRU       *pstDataCfgInfo
);

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-16, end */


/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
VOS_UINT32  MN_CALL_JudgeMtCallType(
    const NAS_CC_IE_BC_OCTET3_STRU      *pstOctet3,
    const NAS_CC_IE_BC_OCTET5A_STRU     *pstOctet5a,
    MN_CALL_TYPE_ENUM_U8                *penCallType
);
/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */

#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID TAF_SndAcpuOmFaultErrLogInd(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulDataLen,
    NAS_ERR_LOG_ALM_ID_ENUM_U16         usAlmId
);
#endif


#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID TAF_SndMmaImsSrvInfoNotify(
    VOS_UINT8                           ucImsCallFlg
);
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_SndMmaCdmaMoCallStartNtf(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enCallType
);

VOS_VOID TAF_SndMmaCdmaMoCallEndNtf(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enCallType
);

VOS_VOID TAF_SndMmaCdmaMoCallSuccessNtf(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enCallType
);

VOS_VOID TAF_SndMmaCdmaCallRedialSystemAcquireNtf(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enCallType,
    VOS_UINT32                          ulCause
);

VOS_VOID TAF_SndMmaPsRatTypeNotify(
    TAF_MMA_PS_RAT_TYPE_ENUM_UINT32     enRatType
);
#endif

/* Added by wx270776 for OM融合, 2015-7-3, begin */
extern VOS_UINT32 WuepsAdminPidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_VOID Admin_TaskEntry  (struct MsgCB * pRcvMsg);
/* Added by wx270776 for OM融合, 2015-7-3, end */


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

#endif /* TAF_COMM_H */


