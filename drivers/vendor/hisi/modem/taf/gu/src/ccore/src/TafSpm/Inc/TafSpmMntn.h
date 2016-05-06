/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmMntn.h
  版 本 号   : 初稿
  作    者   : W00176964
  生成日期   : 2013年5月8日
  最近修改   :
  功能描述   : TafSpmMntn.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月8日
    作    者   : W00176964
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_SPM_MNTN_H__
#define __TAF_SPM_MNTN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafSpmCtx.h"
#include "siappstk.h"
#include "UsimPsInterface.h"
#include  "TafMntn.h"

/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-22, begin */
#if (FEATURE_IMS == FEATURE_ON)
#include "TafSdcCtx.h"
#include "SpmImsaInterface.h"
#endif
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-22, end */

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
 枚举名    : TAF_SPM_MNTN_MSG_ID_ENUM
 结构说明  : MMC发送给OM的可维可测消息
  1.日    期   : 2013年5月16日
    作    者   : s46746
    修改内容   : SPM的可维可测消息ID枚举
  2.日    期   : 2013年6月17日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
  3.日    期   : 2013年10月15日
    作    者   : y00245242
    修改内容   : 为VOLTE开发增加消息
  4.日    期   : 2014年2月10日
    作    者   : y00245242
    修改内容   : 增加重拨消息
*****************************************************************************/
enum TAF_SPM_MNTN_MSG_ID_ENUM
{
    TAF_SPM_LOG_FSM_INFO_IND                              = ID_TAF_MNTN_MSG_SPM_BASE,  /*_H2ASN_MsgChoice TAF_SPM_LOG_FSM_INFO_STRU */

    TAF_SPM_LOG_SRV_DOMAIN_SEL_QUEQUE_INFO_IND,                                        /*_H2ASN_MsgChoice TAF_SPM_LOG_SRV_DOMAIN_SEL_QUEQUE_INFO_IND_STRU */

    TAF_SPM_LOG_SRV_DOMAIN_SEL_PRECONDITION_INFO_IND,                                  /*_H2ASN_MsgChoice TAF_SPM_LOG_SRV_DOMAIN_SEL_PRECONDITION_INFO_IND_STRU */

    TAF_SPM_LOG_SRV_DOMAIN_SEL_REDIAL_INFO_IND,                                        /*_H2ASN_MsgChoice TAF_SPM_LOG_SRV_DOMAIN_SEL_REDIAL_INFO_IND_STRU */

    TAF_SPM_LOG_REDIAL_CALL_INFO_IND,                                                  /*_H2ASN_MsgChoice TAF_SPM_LOG_REDIAL_CALL_INFO_IND_STRU */

    TAF_SPM_MNTN_MSG_ID_BUTT
};
typedef VOS_UINT32 TAF_SPM_MNTN_MSG_ID_ENUM_UINT32;


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
 结构名    : TAF_SPM_LOG_FSM_INFO_STRU
 结构说明  : SPM状态机可维可测消息

 修改记录  :
 1.日    期   : 2013年05月16日
   作    者   : s46746
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    TAF_SPM_FSM_ID_ENUM_UINT32          enFsmId;
    VOS_UINT32                          ulState;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucFsmRunFlg;
    VOS_UINT8                           aucRsv[1];
}TAF_SPM_LOG_FSM_INFO_STRU;

/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-15, begin */
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, begin */
/*****************************************************************************
 结构名    : TAF_SPM_LOG_SRV_DOMAIN_SEL_QUEUE_INFO_STRU
 结构说明  : SPM业务域选择可维可测消息

 修改记录  :
 1.日    期   : 2013年10月15日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucCachedCcMsgNum;
    VOS_UINT8                           ucMaxCcMsgQueueNum;
    VOS_UINT8                           ucCachedSmsMsgNum;
    VOS_UINT8                           ucMaxSmsMsgQueueNum;
    VOS_UINT8                           ucCachedSsMsgNum;
    VOS_UINT8                           ucMaxSsMsgQueueNum;
    VOS_UINT8                           aucRsv[2];
}TAF_SPM_LOG_SRV_DOMAIN_SEL_QUEUE_INFO_STRU;
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, end */

#if ( FEATURE_ON == FEATURE_IMS )
/*****************************************************************************
 结构名    : TAF_SPM_SRV_DOMAIN_SEL_NV_INFO_STRU
 结构说明  : 业务域选择时与NV相关信息

 修改记录  :
 1.日    期   : 2013年10月22日
   作    者   : y00245242
   修改内容   : 新增
 2.日    期   : 2014年2月10日
   作    者   : y00245242
   修改内容   : 增加漫游NV控制信息
  3.日    期   : 2014年04月01日
    作    者   : y00245242
    修改内容   : 为DTS2014040203732修改，增加NV控制USSD业务域选择；USSD业务NV打开，
                 进行正常域选择，否则选择CS域
*****************************************************************************/
typedef struct
{
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVociceDomain;             /* voice domain prefer */

    TAF_SDC_SMS_DOMAIN_ENUM_UINT8       enSmsDomain;                /* SMS domain prefer */
    TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8 enUeUsageSetting;           /* UE usage setting */
    TAF_SDC_LTE_CS_SERVICE_ENUM_UINT8   enLteCsServiceCfg;          /* LTE CS service capability supported by UE*/
    VOS_UINT8                           ucVoiceCallOnImsSupport;    /* voice call supported on IMS */

    VOS_UINT8                           ucSmsOnImsSupport;          /* SMS supported on IMS */
    VOS_UINT8                           ucVideoCallOnImsSupport;    /* video call supported on IMS */
    VOS_UINT8                           ucLteImsSupport;            /* LTE IMS supported by UE */
    VOS_UINT8                           ucLteEmsSupport;            /* LTE EMS supported by UE */

    VOS_UINT8                           ucImsRoamSupport;           /* IMS supported by UE in roaming state */
    VOS_UINT8                           ucUssdOnImsSupportFlag;     /* 是否支持IMS USSD 标志 */
    VOS_UINT8                           aucReserved[2];

}TAF_SPM_SRV_DOMAIN_SEL_NV_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_SRV_DOMAIN_SEL_NW_INFO_STRU
 结构说明  : 业务域选择时与网络相关信息

 修改记录  :
 1.日    期   : 2013年10月22日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    TAF_SDC_NW_IMS_VOICE_CAP_ENUM_UINT8   enNwImsVoCap;             /* IMS voice capability supported by network */
    TAF_SDC_NW_EMC_BS_CAP_ENUM_UINT8      enNwEmcBsCap;             /* EMC BS capability supported by network */
    TAF_SDC_LTE_CS_CAPBILITY_ENUM_UINT8   enLteCsCap;               /* LTE CS capability supported by network */
    VOS_UINT8                             ucSmsSupportOnImsServer;  /* IMS SMS supported by IMS server */

    VOS_UINT8                             ucRoamFlag;               /* roaming flag */
    VOS_UINT8                             aucReserved[3];
}TAF_SPM_SRV_DOMAIN_SEL_NW_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_SRV_DOMAIN_SEL_SRV_STATUS_INFO_STRU
 结构说明  : 业务域选择时与服务状态相关的信息

 修改记录  :
 1.日    期   : 2013年10月22日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enImsRegStatus;             /* IMS register status */
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsSrvStatus;              /* CS service status */
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enPsSrvStatus;              /* PS service status */
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;                  /* system mode */
    VOS_UINT8                           aucReserved[1];
}TAF_SPM_SRV_DOMAIN_SEL_SRV_STATUS_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_SRV_DOMAIN_SEL_SRV_EXIST_INFO_STRU
 结构说明  : 业务域选择时，与业务存在相关信息

 修改记录  :
 1.日    期   : 2013年10月22日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCsCallExistFlag;          /* cs call exist */
    VOS_UINT8                           ucImsCallExistFlag;         /* ims call exist */
    VOS_UINT8                           ucCsSsExistFlag;            /* cs ss exist */
    VOS_UINT8                           ucImsSsExistFlag;           /* ims ss exist */
    VOS_UINT8                           ucCsSmsExistFlag;           /* cs sms exist */
    VOS_UINT8                           ucPsSmsExistFlag;           /* ps sms exist */
    VOS_UINT8                           ucImsSmsExistFlag;          /* ims sms exist */
    VOS_UINT8                           aucReserved[1];
}TAF_SPM_SRV_DOMAIN_SEL_SRV_EXIST_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_LOG_SRV_DOMAIN_SEL_PRECONDITION_INFO_STRU
 结构说明  : SPM业务域选择可维可测消息

 修改记录  :
 1.日    期   : 2013年10月15日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    TAF_SPM_SRV_DOMAIN_SEL_NV_INFO_STRU                     stNvInfo;
    TAF_SPM_SRV_DOMAIN_SEL_NW_INFO_STRU                     stNwInfo;
    TAF_SPM_SRV_DOMAIN_SEL_SRV_STATUS_INFO_STRU             stSrvStatusInfo;
    TAF_SPM_SRV_DOMAIN_SEL_SRV_EXIST_INFO_STRU              stSrvExistInfo;
}TAF_SPM_LOG_SRV_DOMAIN_SEL_PRECONDITION_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_LOG_SRV_DOMAIN_SEL_REDIAL_INFO_IND_STRU
 结构说明  : SPM业务域选择换域重拨可维可测消息

 修改记录  :
 1.日    期   : 2014年2月10日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                                               ucCallRedialSupport;
    VOS_UINT8                                               ucCallCachedMsgNum;
    VOS_UINT8                                               ucCallMaxCachedMsgNum;
    VOS_UINT8                                               ucSmsRedialSupport;
    VOS_UINT8                                               ucSmsCachedMsgNum;
    VOS_UINT8                                               ucSmsMaxCachedMsgNum;

    VOS_UINT8                                               ucImsSmsSendingFlg; /* IMS短信正在发送标志 */
    VOS_UINT8                                               aucReserved[1];
    
}TAF_SPM_LOG_SRV_DOMAIN_SEL_REDIAL_INFO_IND_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_LOG_REDIAL_CALL_INFO_IND_STRU
 结构说明  : SPM业务域选择换域重拨可维可测消息

 修改记录  :
 1.日    期   : 2014年06月06日
   作    者   : s00217060
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                                               ucNumOfCalls;                           /* 所有正在通话的个数 */
    VOS_UINT8                                               aucReserve[3];
    MN_CALL_INFO_PARAM_STRU                                 astCallInfo[MN_CALL_MAX_NUM];           /* 所用正在通话的信息 */
}TAF_SPM_LOG_REDIAL_CALL_INFO_IND_STRU;

#endif
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-15, end */

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
/* Deleted by wx270776 for OM融合, 2015-7-16, begin */
/* Deleted by wx270776 for OM融合, 2015-7-16, end */


VOS_VOID  TAF_SPM_LogFsmInfo(VOS_VOID);

/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-15, begin */
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, begin */
VOS_VOID  TAF_SPM_LogSrvDomainSelQueueInfo(VOS_VOID);
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, end */
#if ( FEATURE_ON == FEATURE_IMS )
VOS_VOID  TAF_SPM_LogSrvDomainSelPreconditionInfo(VOS_VOID);

VOS_VOID TAF_SPM_LogSrvDomainSelRedialInfo(VOS_VOID);

VOS_VOID TAF_SPM_LogRedialCallInfo(
    IMSA_SPM_CALL_GET_CALL_INFO_IND_STRU                   *pstCallInfoInd
);

#endif
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-15, end */

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

#endif /* end of TafSpmMntn.h */

