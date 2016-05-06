/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLmmCore.h
    Description :
    History     :
      1.  hanlufeng 41410  Draft Enact
      2. zhengjunyan 2009-12-09  24301-CR39:TAU REQ信元变更
      3. zhengjunyan 2011-05-28  文件名由 NasMmCore.h修改为 NasLmmCore.h
******************************************************************************/

#ifndef _NASLMMCORE_H
#define _NASLMMCORE_H

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "AppNasComm.h"
#include    "EmmEsmInterface.h"
#include    "NasLmmPubMFsm.h"
#include    "GmmLmmInterface.h"
#include    "NasEmmTauInterface.h"
#include    "MmLmmInterface.h"
#include    "LNasNvInterface.h"
#include    "UsimPsInterface.h"
#include    "EmmRabmInterface.h"
#include    "AppEsmInterface.h"

#include "product_config.h"



/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define NAS_LMM_MAX_EQU_PLMN_NUM         16

#define NAS_LMM_MAX_FORBTA_NUM           64                  /* FORBID TA 最大个数 */
#define NAS_LMM_MAX_FORBLA_NUM           64                  /* FORBID LA 最大个数 */

#define NAS_LMM_AUTH_RES_LEN             8
#define NAS_LMM_ALGORITHM_NOT_SUPPORT    0
#define NAS_LMM_ALGORITHM_SUPPORT        1

#define NAS_LMM_MAX_SUP_CODEC_NUM        10

#define NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE 7

#define NAS_LMM_UE_NET_CAP_LEN           0x04

#define NAS_EMM_CN_NAME_MAX_LEN         255                 /* 网络名字的最大长度 */

#define NAS_LMM_UE_NET_CAP_EEA           0xA0
#define NAS_LMM_UE_NET_CAP_EIA           0x20
#define NAS_LMM_UE_NET_CAP_UEA           0x00
#define NAS_LMM_UE_NET_CAP_UIA           0x00

#define NAS_LMM_MAX_EMG_NUM_LEN          48

#define NAS_EMM_EPS_LOC_MAX_LEN          sizeof(LNAS_LMM_NV_EPS_LOC_STRU)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
结构名称    :NAS_MM_CN_CAUSE_ENUM
使用说明    :24301 9.9.3.7 EMM cause
*****************************************************************************/
enum    NAS_MM_CN_CAUSE_ENUM
{
    NAS_LMM_CAUSE_NULL                                       = 0x00, /* NULL（无原因）                           */
    NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS                        = 0x02, /* IMSI unknown in HLR                      */
    NAS_LMM_CAUSE_ILLEGAL_UE                                 = 0x03, /* Illegal MS                               */

    NAS_LMM_CAUSE_IMEI_NOT_ACCEPTED                          = 0x05, /* IMEI not accepted                        */
    NAS_LMM_CAUSE_ILLEGAL_ME                                 = 0x06, /* Illegal ME                               */
    NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW                         = 0x07, /* GPRS services not allowed                */
    NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW        = 0x08, /* GPRS services and non-GPRS
                                                                       services not allowed                     */
    NAS_LMM_CAUSE_UE_ID_NOT_DERIVED                          = 0x09, /* MS identity cannot be derived
                                                                       by the network                           */
    NAS_LMM_CAUSE_IMPLICIT_DETACHED                          = 0x0A, /* Implicitly detached                      */
    NAS_LMM_CAUSE_PLMN_NOT_ALLOW                             = 0x0B, /* PLMN not allowed                         */
    NAS_LMM_CAUSE_TA_NOT_ALLOW                               = 0x0C, /* Location area not allowed                */
    NAS_LMM_CAUSE_ROAM_NOT_ALLOW                             = 0x0D, /* Roaming not allowed in
                                                                       this location area                       */
    NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN                 = 0x0E, /* GPRS services not allowed in this PLMN   */
    NAS_LMM_CAUSE_NO_SUITABL_CELL                            = 0x0F, /* No Suitable Cells In Location Area       */
    NAS_LMM_CAUSE_MSC_UNREACHABLE                            = 0x10, /* MSC temporarily not reachable            */
    NAS_LMM_CAUSE_NETWORK_FAILURE                            = 0x11, /* Network failure                          */
    NAS_LMM_CAUSE_CS_NOT_AVAIL                               = 0x12,
    NAS_LMM_CAUSE_ESM_FAILURE                                = 0x13,
    NAS_LMM_CAUSE_MAC_FAILURE                                = 0x14, /* MAC failure                              */
    NAS_LMM_CAUSE_SYNCH_FAILURE                              = 0x15, /* Synch failure                            */
    NAS_LMM_CAUSE_PROCEDURE_CONGESTION                       = 0x16, /* Congestion                               */
    NAS_LMM_CAUSE_UE_SECU_CAP_MISMATCH                       = 0x17,
    NAS_LMM_CAUSE_SECU_MODE_REJECTED_UNSPECIFIED             = 0x18,
    NAS_LMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG                = 0x19,

    NAS_LMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN= 0x23,/* Requested service option not authorized in this PLMN */

    NAS_LMM_CAUSE_CS_FALLBACK_CALL_EST_NOT_ALLOWED           = 0x26,
    NAS_LMM_CAUSE_CS_DOMAIN_TMP_NOT_ALLOWED                  = 0x27,
    NAS_LMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED            = 0x28,

    NAS_LMM_CAUSE_SERVER_NETWORK_FAILURE                     = 0x2A,

    NAS_LMM_CAUSE_SEMANTICALLY_INCORRECT_MSG                 = 0x5F, /* Semantically incorrect message           */
    NAS_LMM_CAUSE_INVALID_MANDATORY_INF                      = 0x60, /* Invalid mandatory information            */
    NAS_LMM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE                 = 0x61, /* Message type non-existent or
                                                                       not implemented                          */
    NAS_LMM_CAUSE_MSG_TYPE_NOT_COMPATIBLE                    = 0x62, /* Message type not compatible with the
                                                                       protocol state                           */
    NAS_LMM_CAUSE_IE_NONEXIST_NOTIMPLEMENTED                 = 0x63, /* Information element non-existent or
                                                                       not implemented                          */
    NAS_LMM_CAUSE_CONDITIONAL_IE_ERROR                       = 0x64, /* Conditional IE error                     */
    NAS_LMM_CAUSE_MSG_NOT_COMPATIBLE                         = 0x65, /* Message not compatible with
                                                                       protocol state                           */
    NAS_LMM_CAUSE_PROTOCOL_ERROR                             = 0x6F /* Protocol error, unspecified              */
};
typedef VOS_UINT8 NAS_MM_CN_CAUSE_ENUM_UINT8;
typedef NAS_MM_CN_CAUSE_ENUM_UINT8  NAS_EMM_CN_CAUSE_ENUM_UINT8;
typedef NAS_MM_CN_CAUSE_ENUM_UINT8  NAS_EMMC_CN_CAUSE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : NAS_EMM_EPS_BEARER_CONTEXT_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 接入技术的取值
*****************************************************************************/
enum NAS_EMM_EPS_BEARER_CONTEXT_STATUS_ENUM
{
    NAS_EMM_EPS_BEARER_STATUS_NOCHANGE = 0,
    NAS_EMM_EPS_BEARER_STATUS_CHANGEED = 1,
    NAS_EMM_EPS_BEARER_STATUS_BUTT
};
typedef VOS_UINT32  NAS_EMM_EPS_BEARER_CONTEXT_STATUS_ENUM_UINT32;
typedef NAS_EMM_EPS_BEARER_CONTEXT_STATUS_ENUM_UINT32  NAS_EMMC_EPS_BEARER_CONTEXT_STATUS_ENUM_UINT32;



/*****************************************************************************
 枚举名    : NAS_LMM_GLOBLE_PARA_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 全局参数类型
*****************************************************************************/
enum NAS_LMM_GLOBLE_PARA_ENUM
{
    NAS_LMM_GLOBLE_PARA_UPLMNLIST                    = 0,
    NAS_LMM_GLOBLE_PARA_OPLMNLIST                       ,
    NAS_LMM_GLOBLE_PARA_IMSI                            ,
    NAS_LMM_GLOBLE_PARA_UEID                            ,
    NAS_LMM_GLOBLE_PARA_MNC_LEN                         ,
    NAS_LMM_GLOBLE_PARA_FPLMNLIST                       ,
    NAS_LMM_GLOBLE_FORB_TA_FOR_ROAMING                  ,
    NAS_LMM_GLOBLE_FORB_TA_FOR_RPOS                     ,
    NAS_LMM_GLOBLE_PRESENT_NET_ID                       ,
    NAS_LMM_GLOBLE_NET_INFO                             ,
    NAS_LMM_GLOBLE_TA_LIST                              ,
    NAS_LMM_GLOBLE_PARA_MAX_NUM_OF_FPLMN_BY_USIM        ,
    NAS_LMM_GLOBLE_PARA_HPLMN_ACT_LIST                  ,
    NAS_LMM_GLOBLE_PARA_LRPLMNSI                        ,
    NAS_LMM_GLOBLE_PARA_BUTT
};
typedef VOS_UINT32  NAS_LMM_GLOBLE_PARA_ENUM_UINT32;

enum NAS_LMM_TIMEZONE_ENUM
{
    NAS_LMM_TIMEZONE_POSITIVE                        = 0,
    NAS_LMM_TIMEZONE_NAGETIVE                           ,
    NAS_LMM_TIMEZONE_BUTT
};
typedef VOS_UINT8  NAS_LMM_TIMEZONE_ENUM_UINT8;

enum NAS_LMM_DAYLIGHT_SAVE_TIME_ENUM
{
    NAS_LMM_DAYLIGHT_NO_ADJUST                         = 0,
    NAS_LMM_DAYLIGHT_1_HOUR_ADJUST                        ,
    NAS_LMM_DAYLIGHT_2_HOUR_ADJUST                        ,
    NAS_LMM_DAYLIGHT_BUTT
};
typedef VOS_UINT8  NAS_LMM_DAYLIGHT_SAVE_TIME_ENUM_UINT8;

enum    NAS_EMM_CN_MSG_TYPE_ENUM
{
    EMM_MSG_TYPE_INVALID                = 0x00,

    NAS_EMM_CN_MT_ATTACH_REQ            = 0x41,
    NAS_EMM_CN_MT_ATTACH_ACP            = 0x42,
    NAS_EMM_CN_MT_ATTACH_CMP            = 0x43,
    NAS_EMM_CN_MT_ATTACH_REJ            = 0x44,

    NAS_EMM_CN_MT_DETACH_REQ_MT         = 0x45,
  /*NAS_EMM_CN_MT_DETACH_ACP_MT         = 0xC5,*/
  /*NAS_EMM_CN_MT_DETACH_REQ_MO         = 0xD6,*/
    NAS_EMM_CN_MT_DETACH_ACP_MO         = 0x46,


    NAS_EMM_CN_MT_TAU_REQ               = 0x48,
    NAS_EMM_CN_MT_TAU_ACP               = 0x49,
    NAS_EMM_CN_MT_TAU_CMP               = 0x4A,
    NAS_EMM_CN_MT_TAU_REJ               = 0x4B,

    NAS_EMM_CN_MT_SER_REQ               = 0xC7,
    NAS_EMM_CN_MT_EXT_SER_REQ           = 0x4C,
    NAS_EMM_CN_MT_SER_REJ               = 0x4E,
    /*NAS_EMM_CN_SER_ACP,*/

    NAS_EMM_CN_MT_GUTI_CMD              = 0x50,
    NAS_EMM_CN_MT_GUTI_CMP              = 0x51,

    NAS_EMM_CN_MT_AUTH_REQ              = 0x52,/* 0101 0010  Authentication request  */
    NAS_EMM_CN_MT_AUTH_RSP              = 0x53,/* 0101 0011  Authentication response */
    NAS_EMM_CN_MT_AUTH_REJ              = 0x54,/* 0101 0100  Authentication response */
    NAS_EMM_CN_MT_IDEN_REQ              = 0x55,
    NAS_EMM_CN_MT_IDEN_RSP              = 0x56,


    NAS_EMM_CN_MT_AUTH_FAIl             = 0x5C,/* 0101 0100  Authentication failure */

    NAS_EMM_CN_MT_SMC_CMD               = 0x5D,/* 0101 0010  Security mode command  */
    NAS_EMM_CN_MT_SMC_CMP               = 0x5E,/* 0101 0010  Security mode complete */
    NAS_EMM_CN_MT_SMC_REJ               = 0x5F,/* 0101 0010  Security mode reject   */

    NAS_EMM_CN_MT_EMM_STATUS            = 0x60,/* 0110 0000 */
    NAS_EMM_CN_MT_EMM_INFO              = 0x61,/* 0110 0001 */

    NAS_EMM_CN_MT_DOWNLINK_NAS_TRANSPORT= 0x62,/* 0110 0010 */
    NAS_EMM_CN_MT_UPLINK_NAS_TRANSPORT  = 0x63,/* 0110 0011 */

    NAS_EMM_CN_CS_SER_NOTIFICATION      = 0x64,/* 0110 0100 */

    NAS_EMM_CN_MT_DOWNLINK_GENERIC_NAS_TRANSPORT    = 0x68,/* 0110 1000 */
    NAS_EMM_CN_MT_UPLINK_GENERIC_NAS_TRANSPORT      = 0x69,/* 0110 1001 */

    NAS_EMM_CN_MT_BUTT
};
typedef VOS_UINT8 NAS_EMM_CN_MSG_TYPE_ENUM_UINT8;

enum    NAS_EMM_T3402_SRC_TYPE_ENUM
{

    NAS_EMM_T3402_SRC_ATTACH_REJ,
    NAS_EMM_T3402_SRC_OTHERS,

    NAS_EMM_T3402_SRC_BUTT
};
typedef VOS_UINT8 NAS_EMM_T3402_SRC_ENUM_UINT8;


/*****************************************************************************
 结构名    : NAS_LMM_SIM_SRV_STATUS_ENUM_UINT32
 结构说明  :
*****************************************************************************/
enum NAS_LMM_SIM_SRV_STATUS_ENUM
{
    NAS_LMM_SIM_SRV_UNAVAILABLE          = 0x0000,
    NAS_LMM_SIM_SRV_AVAILABLE                     ,
    NAS_LMM_SIM_SRV_BUTT
};
typedef VOS_UINT32 NAS_LMM_SIM_SRV_STATUS_ENUM_UINT32;


/*****************************************************************************
 结构名    : NAS_LMM_SIM_STAT_ENUM
 结构说明  :
*****************************************************************************/
enum NAS_LMM_SIM_STAT_ENUM
{
    NAS_LMM_SIM_STATUS_UNAVAILABLE,
    NAS_LMM_SIM_STATUS_AVAILABLE,
    NAS_LMM_SIM_STATUS_BUTT
};
typedef VOS_UINT32 NAS_LMM_SIM_STAT_ENUM_UINT32;


/*****************************************************************************
 结构名    : NAS_LMM_SIM_VALIDITY_ENUM
 结构说明  :
*****************************************************************************/
enum NAS_LMM_SIM_VALIDITY_ENUM
{
    NAS_LMM_SIM_VALID,
    NAS_LMM_SIM_INVALID,
    NAS_LMM_SIM_VALIDITY_BUTT
};
typedef VOS_UINT32 NAS_LMM_SIM_VALIDITY_ENUM_UINT32;


/*****************************************************************************
 结构名    : NAS_LMM_NET_FEATURE_ENUM
 结构说明  :
*****************************************************************************/
enum NAS_LMM_NET_FEATURE_ENUM
{
    NAS_LMM_NET_FEATURE_IMSVOPS                     = 0x01,
    NAS_LMM_NET_FEATURE_EMCBS                       = 0x02,
    NAS_LMM_NET_FEATURE_EPCLCS                      = 0x04,
    NAS_LMM_NET_FEATURE_CSLCS                       = 0x08,

    NAS_LMM_NET_FEATURE_BUTT
};
typedef VOS_UINT8 NAS_LMM_NET_FEATURE_ENUM_UINT8;


/*****************************************************************************
 结构名    : NAS_LMM_ADDITION_UPDATE_RSLT_ENUM
 结构说明  :
*****************************************************************************/
enum NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM
{
    NAS_LMM_ADDITIONAL_UPDATE_NO_INFO           = 0, /* NO_INFO表示CS支持全功能 */
    NAS_LMM_ADDITIONAL_UPDATE_CSFB_NOT_PREFERED = 1,
    NAS_LMM_ADDITIONAL_UPDATE_SMS_ONLY          = 2,
    NAS_LMM_ADDITIONAL_UPDATE_NOT_ATTACHED      = 3,
    NAS_LMM_ADDITIONAL_UPDATE_BUTT
};
typedef VOS_UINT32 NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32;
/*****************************************************************************
 结构名称:  NAS_LMM_REG_DOMAIN_ENUM
 协议表格:  L模下注册成功的域
 ASN.1 描述:
 结构说明:
*****************************************************************************/
enum NAS_LMM_REG_DOMAIN_ENUM
{
    NAS_LMM_REG_DOMAIN_NULL             = 0x00,
    NAS_LMM_REG_DOMAIN_PS               = 0x01,
    NAS_LMM_REG_DOMAIN_CS               = 0x02,
    NAS_LMM_REG_DOMAIN_CS_PS            = 0x03,

    NAS_LMM_REG_DOMAIN_BUTT
};
typedef VOS_UINT32  NAS_LMM_REG_DOMAIN_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_EMM_LAU_OR_COMBINED_RAU_FLAG_ENUM
 枚举说明  : LAU或者联合RAU标识枚举
*****************************************************************************/
enum  NAS_EMM_LAU_OR_COMBINED_RAU_FLAG_ENUM
{
    NAS_EMM_LAU_OR_COMBINED_RAU_NOT_HAPPENED        = 0,
    NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED            = 1,

    NAS_EMM_LAU_OR_COMBINED_RAU_FLAG_BUTT
};
typedef VOS_UINT32   NAS_EMM_LAU_OR_COMBINED_RAU_FLAG_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_EMM_SRVCC_FLAG_ENUM
 枚举说明  : SRVCC标识枚举
*****************************************************************************/
enum  NAS_EMM_SRVCC_FLAG_ENUM
{
    NAS_EMM_SRVCC_NOT_HAPPENED        = 0,
    NAS_EMM_SRVCC_HAPPENED            = 1,

    NAS_EMM_SRVCC_FLAG_BUTT
};
typedef VOS_UINT32   NAS_EMM_SRVCC_FLAG_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_EMM_FIRST_TAU_FLAG_ENUM
 枚举说明  : 第一次TAU标识枚举
*****************************************************************************/
enum  NAS_EMM_FIRST_TAU_FLAG_ENUM
{
    NAS_EMM_NOT_FIRST_TAU               = 0,
    NAS_EMM_FIRST_TAU                   = 1,

    NAS_EMM_FIRST_TAU_FLAG_BUTT
};
typedef VOS_UINT32   NAS_EMM_FIRST_TAU_FLAG_ENUM_UINT32;
/*****************************************************************************
 结构名称   : NAS_LMM_SUSPEND_NOTIFY_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC在ID_LRRC_LNAS_SYS_CFG_CNF通知LMM 此次是否需要LMM挂起LRRC，以及挂起的原因
*****************************************************************************/
enum NAS_LMM_SUSPEND_TYPE_NOTIFY_ENUM
{
    NAS_LMM_NOT_SUSPEND                  = 0,
    NAS_LMM_SUSPEND_LTE_RAT_NOT_ACTIVE   = 1,
    NAS_LMM_SUSPEND_LTE_BAND_NOT_SUPPORT = 2,

    NAS_LMM_SUSPEND_NOTIFY_BUTT
};
typedef VOS_UINT32 NAS_LMM_SUSPEND_TYPE_NOTIFY_ENUM_UINT32;

/*****************************************************************************
 结构名称   : NAS_LMM_CONNECTION_CLIENTID_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   :
*****************************************************************************/
enum NAS_LMM_CONNECTION_CLIENT_ID_ENUM
{
    NAS_LMM_CONNECTION_CLIENT_ID_NULL      = 0,
    NAS_LMM_CONNECTION_CLIENT_ID_SMS      = 1,


    NAS_LMM_CONNECTION_CLIENT_ID_BUTT
};
typedef VOS_UINT32 NAS_LMM_CONNECTION_CLIENT_ID_ENUM_UINT32;
/*****************************************************************************
 枚举名    : NAS_EMM_REJ_FLAG_ENUM
 枚举说明  : 拒绝标识
*****************************************************************************/
enum  NAS_EMM_REJ_FLAG_ENUM
{
    NAS_EMM_REJ_NO                      = 0,
    NAS_EMM_REJ_YES                     = 1,

    NAS_EMM_REJ_BUTT
};
typedef VOS_UINT32   NAS_EMM_REJ_FLAG_ENUM_UINT32;
/*****************************************************************************
 枚举名    : NAS_EMM_PLMN_SRCH_ENUM
 枚举说明  : PLMN_SRCH标识
*****************************************************************************/
enum  NAS_EMM_PLMN_SRCH_FLAG_ENUM
{
    NAS_EMM_PLMN_SRCH_FLAG_INVALID                   = 0,
    NAS_EMM_PLMN_SRCH_FLAG_VALID                     = 1,

    NAS_EMM_PLMN_SRCH_FLAG_BUTT
};
typedef VOS_UINT32   NAS_EMM_PLMN_SRCH_FLAG_ENUM_UINT32;
/*****************************************************************************
 结构名称   : NAS_LMM_LTE_ENABLE_STA_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   :收到MMC下发的DISABLE或者ENABLE LTE消息，记录LTE接入技术的使能状态
             目前尚未看到该标识的作用。
*****************************************************************************/
enum NAS_LMM_LTE_ENABLE_STA_ENUM
{
    NAS_LMM_LTE_ENABLED              = 0,
    NAS_LMM_LTE_DISABLED             = 1,

    NAS_LMM_LTE_ENABLE_STA_BUTT
};

typedef VOS_UINT32 NAS_LMM_LTE_ENABLE_STA_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_EMM_FIRST_TAU_FLAG_ENUM
 枚举说明  : 标识当进入REG+NORMAL_SERVICE时，是否需要改为进入REG+ATTEMPT_TO_UPDATE_MM
*****************************************************************************/
enum  NAS_EMM_UPDATE_MM_FLAG_ENUM
{
    NAS_EMM_UPDATE_MM_FLAG_INVALID      = 0,
    NAS_EMM_UPDATE_MM_FLAG_VALID        = 1,

    NAS_EMM_UPDATE_MM_FLAG_BUTT
};
typedef VOS_UINT32   NAS_EMM_UPDATE_MM_FLAG_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_LMM_REG_STATUS_ENUM
 枚举说明  : 标识注册状态
*****************************************************************************/
enum  NAS_LMM_REG_STATUS_ENUM
{
    NAS_LMM_REG_STATUS_DEREG                    = 0,
    NAS_LMM_REG_STATUS_EMC_REGING               = 1,
    NAS_LMM_REG_STATUS_NORM_REGED               = 2,
    NAS_LMM_REG_STATUS_EMC_REGED                = 3,
    NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR  = 4,

    NAS_LMM_REG_STATUS_BUTT
};
typedef VOS_UINT32   NAS_LMM_REG_STATUS_ENUM_UINT32;

/*****************************************************************************
 结构名称   : NAS_LMM_UE_RADIO_CAP_CHANGE_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC在ID_LRRC_LNAS_SYS_CFG_CNF通知LMM , UE的无线接入能力
              发生的变化，其中，LTE发生变化包含GUL中带有L变化的所有情况，
              GU发生变化包含L不变且GU变化的所有情况。
*****************************************************************************/
enum NAS_LMM_UE_RADIO_CAP_CHANGE_ENUM
{
    NAS_LMM_UE_RADIO_CAP_NOT_CHG              = 0,
    NAS_LMM_UE_RADIO_CAP_GU_CHG               = 1,
    NAS_LMM_UE_RADIO_CAP_LTE_CHG              = 2,

    NAS_LMM_UE_RADIO_CAP_CHG_BUTT
};
typedef VOS_UINT32  NAS_LMM_UE_RADIO_CAP_CHANGE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_LMM_SYSCFG_ENUM
 结构说明  : UE的syscfg标识
*****************************************************************************/
enum NAS_LMM_SYSCFG_FLAG_ENUM
{
   NAS_LMM_SYSCFG_FLAG_INVALID                  = 0,    /* SYSCFG标识无效 */
   NAS_LMM_SYSCFG_FLAG_VALID                    = 1,    /* SYSCFG标识有效 */

   NAS_LMM_SYSCFG_FLAG_BUTT
};
typedef VOS_UINT32   NAS_LMM_SYSCFG_FLAG_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_EMM_DSDS_TAU_TYPE_ENUM_UINT32
 枚举说明  : DSDS TAU标识枚举
*****************************************************************************/
enum  NAS_EMM_DSDS_TAU_TYPE_ENUM
{
    NAS_EMM_DSDS_LOW_TAU        = 0,
    NAS_EMM_DSDS_HIGH_TAU       = 1,

    NAS_EMM_DSDS_TAU_BUTT
};
typedef VOS_UINT32  NAS_EMM_DSDS_TAU_TYPE_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 结构名    : NAS_LMM_PID_MSG_STRU
 结构说明  : NAS_LMM PID 入口消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;                /* 消息 ID */
    VOS_UINT8                           aucMsgData[4];          /* 整条消息存储 */
}NAS_LMM_PID_MSG_STRU;



/*****************************************************************************
结构名称    :
使用说明    :
*****************************************************************************/
typedef struct
{
    NAS_LMM_TIMEZONE_ENUM_UINT8          enPosNegTimeZone;
    VOS_UINT8                           ucTimeZone;
    VOS_UINT8                           aucRsv[2];
}NAS_EMM_CN_TIMEZONE_STRU;

typedef struct
{
    NAS_EMM_CN_TIMEZONE_STRU            stTimeZone;
    VOS_UINT8                           ucYear;
    VOS_UINT8                           ucMonth;
    VOS_UINT8                           ucDay;
    VOS_UINT8                           ucHour;
    VOS_UINT8                           ucMinute;
    VOS_UINT8                           ucSecond;
    VOS_UINT8                           aucRsv[2];
}NAS_EMM_CN_TIMEZONE_UNITIME_STRU;



/*****************************************************************************
结构名称    :NAS_EMM_CN_Network_Name_STRU
使用说明    :24301 8.2.1.1: Emm Information message
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMsgLen; /*表示数组中TextString的长度*/
    VOS_UINT8                           ucCodingScheme;
    VOS_UINT8                           ucAddCI;
    VOS_UINT8                           ucNumOfSpareInLastByte;
    VOS_UINT8                           aucMsg[NAS_EMM_CN_NAME_MAX_LEN];
    VOS_UINT8                           ucRsv;
}NAS_EMM_CN_NETWORK_NAME_STRU;


/*==============================================================================
结构名称    : NAS_LMM_UEID_STRU
使用说明    : IMSI, IMEI, IMEISV, TMSI, PTMSI的存放格式按照 31.102 4.2.2执行

    digit n 与 24.008 10.5.4  Mobile Identity information element 的对应关系:

    One digit occupies half of a byte.

    协议描述的 各DIGIT与字节/位的关系如下:
    ----------------------------------------------------------------------------------
    (BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ----------------------------------------------------------------------------------
        Length of mobile identity contents, UNIT is byte
    ----------------------------------------------------------------------------------
        Identity digit 1       | OorE |  Type of identity
    ----------------------------------------------------------------------------------
        Identity digit 3       |           Identity digit 2
    ----------------------------------------------------------------------------------
        Identity digit i + 1   |           Identity digit i
    ----------------------------------------------------------------------------------
        ......                 |           ......
    ----------------------------------------------------------------------------------
        Identity digit P + 1   |           Identity digit P
    ----------------------------------------------------------------------------------

    即, 接口数组中各 DIGIT与字节位置对应关系如下:
    -----------------------------------------------------------------------------------------------
    (digit 15) | (digit 14) |.....| (digit  2) | (digit  1) |OorE|TypeOfId|Length of mobile identity contents, UNIT is byte
    -----------------------------------------------------------------------------------------------
    aucImsi[7] | aucImsi [7]|.....| aucImsi[2] | aucImsi[1] | aucImsi[1]  | aucImsi[0] | aucImsi[0]
    -----------------------------------------------------------------------------------------------
    aucImei[7] | aucImei [7]|.....| aucImei[2] | aucImei[1] | aucImei[1]  | aucImei[0] | aucImei[0]
    -----------------------------------------------------------------------------------------------
    aucTmsi[7] | aucTmsi [7]|.....| aucTmsi[2] | aucTmsi[1] | aucTmsi[1]  | aucTmsi[0] | aucTmsi[0]
    -----------------------------------------------------------------------------------------------
    aucPTmsi[7]|aucPTmsi [7]|.....| aucPTmsi[2]| aucPTmsi[1]| aucPTmsi[1] | aucPTmsi[0]| aucPTmsi[0]
    -----------------------------------------------------------------------------------------------
    aucImeisv[7]|aucImeisv[7]|....|aucImeisv[2]|aucImeisv[1]|aucImeisv[1] |aucImeisv[0]| aucImeisv[0]
    -----------------------------------------------------------------------------------------------


    e.g.          IMSI = 230 040 680000079
    在RRC_NAS的接口数组 aucImsi[] 中存放位置如下:

    协议描述的存放位置如下:
    -------------------------------------------------------------------------------
                           (BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    -------------------------------------------------------------------------------
    aucImsi[0] | aucImsi[0]                           8
    ----------------------------------------------------------------------------
    aucImsi[1] | aucImsi[1]               2           |           9
    ----------------------------------------------------------------------------
    aucImsi[2] | aucImsi[2]               0           |           3
    ----------------------------------------------------------------------------
    aucImsi[3] | aucImsi[3]               4           |           0
    -------------------------- -------------------------------------------------
    aucImsi[4] | aucImsi[4]               6           |           0
    ---------------------------------------------------- -----------------------
    aucImsi[5] | aucImsi[5]               0           |           8
    ---------------------------------------------------- -----------------------
    aucImsi[6] | aucImsi[6]               0           |           0
    ----------------------------------------------------------------------------
    aucImsi[7] | aucImsi[7]               0           |           0
    ----------------------------------------------------------------------------
    aucImsi[8] | aucImsi[8]               9           |           7
    ----------------------------------------------------------------------------

    即, 接口数组中各 DIGIT与字节位置对应关系如下:
    -----------------------------------------------------------------------------------------------
    aucImsi[7] | aucImsi [7]|.....| aucImsi[2] | aucImsi[1] | aucImsi[1]|aucImsi[0] | aucImsi[0]
    -----------------------------------------------------------------------------------------------
    (   9    ) | (    7   ) |.....| (    3   ) | (    2   ) | (   9   ) |           8
    -----------------------------------------------------------------------------------------------


     bitOp**，标识对应的信息是否有效，取值及含义如下:
     #define NAS_EMM_BIT_SLCT      1 :      VALID
     #define NAS_EMM_BIT_NO_SLCT   0 :      INVALID
==============================================================================*/
typedef struct
{
    VOS_UINT32                          bitOpImsi     :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpImei     :1;
    VOS_UINT32                          bitOpImeisv   :1;
    VOS_UINT32                          bitOpTmsi     :1; /* TMSI status  24.008 10.5.5.4 */
    VOS_UINT32                          bitOpPtmsi    :1;
    VOS_UINT32                          bitOpGuti     :1;
    VOS_UINT32                          bitOpTmgiMbms :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv      :25;


    VOS_UINT8                           aucImsi[NAS_MM_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved1[2];
    VOS_UINT8                           aucImei[NAS_MM_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved2[2];
    VOS_UINT8                           aucImeisv[NAS_MM_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved3[2];
    VOS_UINT8                           aucTmsi[NAS_MM_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved4[2];
    VOS_UINT8                           aucPtmsi[NAS_MM_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved5[2];
    NAS_MM_GUTI_STRU                    stGuti;
    NAS_MM_TMGI_MBMS_STRU               stTmgiMbms;
    VOS_UINT32                          ulImsiMncLen;
}NAS_LMM_UEID_STRU;
typedef NAS_LMM_UEID_STRU                NAS_EMM_UEID_STRU;
typedef NAS_LMM_UEID_STRU                NAS_EMMC_UEID_STRU;



/*****************************************************************************
结构名称    :MS identity_STRU
使用说明    :24301 8.2.1.1: Emm Information message
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucMsId[NAS_MM_MAX_MSID_SIZE];
    VOS_UINT8                           aucReserved1[2];
}NAS_LMM_MSID_STRU;
typedef NAS_LMM_MSID_STRU                NAS_EMM_MSID_STRU;


/*****************************************************************************
结构名称    :NAS_LMM_CODEC_STRU
使用说明    :24.008 840 10.5.4.32 Supported codec list
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSysId;
    VOS_UINT8                           ucLenOfBitmap;
    VOS_UINT8                           aucCodecBitmap[2];

}NAS_LMM_CODEC_STRU;

/*****************************************************************************
结构名称    :NAS_LMM_SUP_CODEC_LIST_STRU
使用说明    :24.008 840 10.5.4.32 Supported codec list
[10.5.4.32] of 24.008
8       7       6       5       4       3       2       1
┌───────────────────────────────┐
│                  Supported Codec List IEI                    │Octet 1
├───────────────────────────────┤
│                Length Of Supported Codec list                │Octet 2
├───────────────────────────────┤
│               System Identification 1 (SysID 1)              │Octet 3
├───────────────────────────────┤
│                 Length Of Bitmap for SysID 1                 │Octet 4
├───────────────────────────────┤
│             Codec Bitmap for SysID 1, bits 1 to 8            │Octet 5
├───────────────────────────────┤
│             Codec Bitmap for SysID 1, bits 9 to 16           │Octet 6
├───────────────────────────────┤
│               System Identification 2 (SysID 2)              │Octet j
├───────────────────────────────┤
│                 Length Of Bitmap for SysID 2                 │Octet j+1
├───────────────────────────────┤
│             Codec Bitmap for SysID 2, bits 1 to 8            │Octet j+2
├───────────────────────────────┤
│             Codec Bitmap for SysID 2, bits 9 to 16           │Octet j+3
├───────────────────────────────┤
│               System Identification x (SysID x)              │Octet m
├───────────────────────────────┤
│                 Length Of Bitmap for SysID x                 │Octet m+1
├───────────────────────────────┤
│             Codec Bitmap for SysID x, bits 1 to 8            │Octet m+2
├───────────────────────────────┤
│             Codec Bitmap for SysID x, bits 9 to 16           │Octet m+3
└───────────────────────────────┘

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLenOfCodecList;
    VOS_UINT8                           aucRsv[3];

    NAS_LMM_CODEC_STRU                   astCodec[NAS_LMM_MAX_SUP_CODEC_NUM];
}NAS_LMM_CODEC_LIST_STRU;
typedef NAS_LMM_CODEC_LIST_STRU          NAS_EMM_CODEC_LIST_STRU;
typedef NAS_LMM_CODEC_LIST_STRU          NAS_EMMC_CODEC_LIST_STRU;



/*****************************************************************************
结构名称    :NAS_LMM_NETWORK_INFO_STRU
使用说明    :MM的公用网络信息
             1. FORBIDEN PLMN列表信息在MMC模块保存，不在这里保存;
             2. ATTACH, DETACH, TAU, SERVICE, AUTH的结果，涉及到的下述网络信息
                的修改操作中，只有 stEPlmnList 的操作由MMC在收到ACTION_RST 消息
                后修改此处全局变量，其他信息由各模块收到CN流程消息后修改维护。
             bitOp**，标识对应的信息是否有效，取值及含义如下:
             #define NAS_EMM_BIT_SLCT      1 :      VALID
             #define NAS_EMM_BIT_NO_SLCT   0 :      INVALID
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPresentNetId   :1;
    VOS_UINT32                          bitOpLastRegNetId   :1;
    VOS_UINT32                          bitOpLastAttmpRegTa   :1;
    VOS_UINT32                          bitOpEPlmnList      :1;
    VOS_UINT32                          bitOpTaiList        :1;
    VOS_UINT32                          bitOpHplmn          :1;

    VOS_UINT32                          bitOpEHplmnList     :1;
    VOS_UINT32                          bitOpFoibTaForRpos  :1;
    VOS_UINT32                          bitOpFoibTaForRoam  :1;
    VOS_UINT32                          bitOpForbTaForRej15 :1;
    VOS_UINT32                          bitOpRsv            :22;

    NAS_MM_NETWORK_ID_STRU              stPresentNetId;     /* 当前驻留的网络信息 */
    NAS_MM_NETWORK_ID_STRU              stLastRegNetId;     /* 上次成功注册的网络信息 */

    NAS_MM_TA_STRU                      stLastAttmpRegTa;   /* 上次尝试发起注册的TA信息 */


    NAS_MM_PLMN_LIST_STRU               stEPlmnList;
    NAS_MM_TA_LIST_STRU                 stTaiList;

    NAS_MM_PLMN_ID_STRU                 stHplmn;
    NAS_MM_PLMN_LIST_STRU               stEHplmnList;

    NAS_MM_FORB_TA_LIST_STRU            stForbTaForRoam;    /* forbidden tracking areas for roaming*/
    NAS_MM_FORB_TA_LIST_STRU            stForbTaForRpos;    /* forbidden tracking areas for
                                                               regional provision of service*/
    NAS_MM_FORB_TA_LIST_STRU            stForbTaForRej15;   /* 用户指定搜网，ATTACH或TAU拒绝#15后保存的列表*/

    NAS_MM_CSG_INFO_STRU                stLastAttmpRegCsgInfo;
}NAS_LMM_NETWORK_INFO_STRU;
typedef NAS_LMM_NETWORK_INFO_STRU        NAS_EMM_NETWORK_INFO_STRU;
typedef NAS_LMM_NETWORK_INFO_STRU        NAS_EMMC_NETWORK_INFO_STRU;

/*****************************************************************************
结构名称    :NAS_LMM_APP_PARA_STRU
使用说明    :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulOpId;
}NAS_LMM_APP_PARA_STRU;


/*****************************************************************************
结构名称    :NAS_EMM_PUB_INFO_STRU
使用说明    :MM的公用信息
             bitOp**，标识对应的信息是否有效，取值及含义如下:
             #define NAS_EMM_BIT_SLCT      1 :      VALID
             #define NAS_EMM_BIT_NO_SLCT   0 :      INVALID
*****************************************************************************/
typedef struct
{
    VOS_UINT32                            bitOpFullName              :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                            bitOpShortName             :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                            bitOpLocTimeZone           :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                            bitOpUniTimeLocTimeZone    :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                            bitOpDaylightTime          :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                            bitShare                   :27;

    NAS_EMM_CN_TIMEZONE_STRU              stLocTimeZone;
    NAS_EMM_CN_TIMEZONE_UNITIME_STRU      stTimeZoneAndTime;
    NAS_LMM_DAYLIGHT_SAVE_TIME_ENUM_UINT8  enDaylightSavingTime;
    VOS_UINT8                             aucOperatorNameLong[MMC_LMM_MAX_OPER_LONG_NAME_LEN];
    VOS_UINT8                             aucOperatorNameShort[MMC_LMM_MAX_OPER_SHORT_NAME_LEN];
    VOS_UINT8                             aucRsv[3];
}NAS_EMM_INFO_STRU;



/*****************************************************************************
 枚举名: MMC_LMM_TRANSCEIVER_TYPE_ENUM
 协议格式:
 ASN.1描述:
 枚举说明:待机类型取值
*****************************************************************************/
enum NAS_EMM_TRANSCEIVER_TYPE_ENUM
{
    NAS_EMM_TRANSCEIVER_TYPE_SINGLE     = 0,
    NAS_EMM_TRANSCEIVER_TYPE_DUAL           ,

    NAS_EMM_TRANSCEIVER_TYPE_BUTT
};
typedef VOS_UINT32 NAS_EMM_TRANSCEIVER_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_EMM_RAT_TYPE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : 制式类型
*****************************************************************************/
enum NAS_EMM_RAT_TYPE_ENUM
{
    /* 不存在某种或者所有接入技术 */
    NAS_EMM_RAT_NONE                = 0,
    NAS_EMM_RAT_LTE_FDD             = 1,
    NAS_EMM_RAT_LTE_TDD             = 2,
    NAS_EMM_RAT_LTE_ALL             = 3,
    NAS_EMM_RAT_UTRAN_FDD           = 4,
    NAS_EMM_RAT_UTRAN_TDD           = 8,
    NAS_EMM_RAT_UTRAN_ALL           = 12,
    NAS_EMM_RAT_GERAN               = 16,
    NAS_EMM_RAT_ALL                 = 31,
    NAS_EMM_RAT_BUTT
};
typedef VOS_UINT8 NAS_EMM_RAT_TYPE_ENUM_UINT8;


/*****************************************************************************
结构名称    :NAS_EMM_START_INFO_STRU
使用说明    :开机信息
*****************************************************************************/
typedef struct
{
    MMC_LMM_TRANSCEIVER_TYPE_ENUM_UINT32 ulTransceiverType;

    NAS_LMM_RAT_PRIO_ENUM_UINT8          aucRatPrioList[NAS_LMM_RAT_TYPE_BUTT];     /* 各模的优先级 */

    NAS_LMM_RAT_PRIO_ENUM_UINT8          aucCurRatPrioList[NAS_LMM_RAT_TYPE_BUTT];
    NAS_LMM_RAT_PRIO_ENUM_UINT8          aucPreRatPrioList[NAS_LMM_RAT_TYPE_BUTT];

    VOS_UINT8                            aucRsv[1];
}NAS_EMM_START_INFO_STRU;



/*****************************************************************************
 结构名称: NAS_LMM_SUS_SYS_CHNG_DIR_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
enum   NAS_LMM_SUS_SYS_CHNG_DIR_ENUM
{

    NAS_LMM_SUS_SYS_CHNG_DIR_L2W            = 0x00000000,
    NAS_LMM_SUS_SYS_CHNG_DIR_L2G,
    NAS_LMM_SUS_SYS_CHNG_DIR_L2C,

    NAS_LMM_SUS_SYS_CHNG_DIR_BUTT
};
typedef VOS_UINT32 NAS_LMM_SUS_SYS_CHNG_DIR_ENUM_UINT32;


/*****************************************************************************
 结构名称:  NAS_LMM_SYS_CHNG_DIR_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
enum    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM
{

    NAS_LMM_RSM_SYS_CHNG_DIR_W2L            = 0x00000000,
    NAS_LMM_RSM_SYS_CHNG_DIR_G2L,

    NAS_LMM_RSM_SYS_CHNG_DIR_BUTT
};
typedef VOS_UINT32  NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32;



/*****************************************************************************
 结构名称:NAS_LMM_SYS_CHNG_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:系统变更的类型
*****************************************************************************/
enum    NAS_LMM_SYS_CHNG_TYPE_ENUM
{

    NAS_LMM_SYS_CHNG_TYPE_RSL                = 0x00000000,
    NAS_LMM_SYS_CHNG_TYPE_HO ,
    NAS_LMM_SYS_CHNG_TYPE_CCO ,
    NAS_LMM_SYS_CHNG_TYPE_REDIR ,

    /* 系统回退，暂只在LRRC_LMM_RESUME_IND中使用 */
    NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL,
    NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO,
    NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO,
    NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR,

    NAS_LMM_SYS_CHNG_TYPE_BUTT
};
typedef VOS_UINT32 NAS_LMM_SYS_CHNG_TYPE_ENUM_UINT32;



/*****************************************************************************
 结构名称:NAS_LMM_SUS_CAUSE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:LRRC通知NAS挂起的原因
*****************************************************************************/
enum    NAS_LMM_SUS_CAUSE_ENUM
{

    NAS_LMM_SUS_CAUSE_CSFB                = 0x00000000,

    /* 若非CSFB导致的挂起，则填此BUTT值 */
    NAS_LMM_SUS_CAUSE_BUTT
};
typedef VOS_UINT32 NAS_LMM_SUS_CAUSE_ENUM_UINT32;



/*****************************************************************************
 结构名称:NAS_LMM_SYS_CHNG_ORI_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
enum    NAS_LMM_SYS_CHNG_ORI_ENUM
{

    NAS_LMM_SYS_CHNG_ORI_MMC                = 0x00000000,
    NAS_LMM_SYS_CHNG_ORI_LRRC,

    NAS_LMM_SYS_CHNG_ORI_BUTT
};
typedef VOS_UINT32 NAS_LMM_SYS_CHNG_ORI_ENUM_UINT32;


/*****************************************************************************
 结构名称:NAS_LMM_GU_ACTION_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:  z00179470   2011-06-02 new
            GU ACTION TYPE
*****************************************************************************/
enum    NAS_LMM_GU_ACTION_TYPE_ENUM
{
    MMC_LMM_GU_ACTION_ATTACH              = 0x00000000,
    MMC_LMM_GU_ACTION_RAU                  ,
    MMC_LMM_GU_ACTION_LAU                  ,
    MMC_LMM_GU_ACTION_PS_SERVICE_REQ       ,
    MMC_LMM_GU_ACTION_DETACH               ,
    MMC_LMM_GU_ACTION_CM_REQ               ,
    MMC_LMM_GU_ACTION_TYPE_BUTT
};
typedef VOS_UINT32 NAS_LMM_GU_ACTION_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名称:NAS_LMM_GU_ACTION_RSLT_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:  z00179470   2011-06-02 new
            GU ACTION RST
*****************************************************************************/

enum    NAS_LMM_GU_ACTION_RSLT_TYPE_ENUM
{
    MMC_LMM_GU_RSLT_TYPE_SUCCESS                     = 0,
    MMC_LMM_GU_RSLT_TYPE_FAILURE,                                                  /*失败包含网侧拒绝和无响应*/
    MMC_LMM_GU_RSLT_TYPE_CN_REJ,
    MMC_LMM_GU_RSLT_TYPE_AUTH_REJ,                                                 /* 鉴权被拒 */
    MMC_LMM_GU_RSLT_TYPE_BUTT
};
typedef VOS_UINT32 NAS_LMM_GU_ACTION_RSLT_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名称:NAS_LMM_GU_DOMAIN_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:  z00179470   2011-06-02 new
            GU ACTION REQ and RST DOMAIN
*****************************************************************************/
enum NAS_LMM_GU_DOMAIN_ENUM
{
    MMC_LMM_GU_PS_ONLY                     = 0x00000000,                           /*当前RAU/Attach类型为PS only  */
    MMC_LMM_GU_IMSI_ONLY,                                                          /*当前 类型为CS only  */
    MMC_LMM_GU_COMBINED_PS_IMSI ,                                                  /*当前 类型为联合处理  */

    MMC_LMM_GU_DOMAIN_BUTT
};
typedef VOS_UINT32 NAS_LMM_GU_DOMAIN_ENUM_UINT32;

/*****************************************************************************
 结构名称:NAS_LMM_MT_DETACH_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:  z00179470   2011-06-02 new
            GU MT DETACH TYPE
*****************************************************************************/

enum NAS_LMM_MT_DETACH_TYPE_ENUM
{
    MMC_LMM_GU_MT_DET_REATTACH_REQUIRED                = 1,
    MMC_LMM_GU_MT_DET_REATTACH_NOT_REQUIRED            = 2,
    MMC_LMM_GU_MT_DET_IMSI                             = 3,

    MMC_LMM_GU_MT_DETACH_TYPE_BUTT
};
typedef VOS_UINT32 NAS_LMM_MT_DETACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名称:NAS_EMM_CCO_CHANGE_TIN_FLAG_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: 由于CCO流程导致更改TIN值标识
*****************************************************************************/

enum NAS_EMM_CCO_CHANGE_TIN_FLAG_ENUM
{
    NAS_EMM_CCO_CHANGE_TIN_INVALID        = 0,
    NAS_EMM_CCO_CHANGE_TIN_VALID,
    NAS_EMM_CCO_CHANGE_TIN_BUTT,
};
typedef VOS_UINT32 NAS_EMM_CCO_CHANGE_TIN_FLAG_ENUM_UINT32;

/*****************************************************************************
 结构名称: NAS_LMM_HO_SECU_PARA_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHoSecuPara;
    VOS_UINT8                           aucRsv[3];
} NAS_LMM_HO_SECU_PARA_STRU;


/*****************************************************************************
 结构名称: NAS_LMM_SYS_CHNG_CTRL_STRU
 协议表格:
 ASN.1描述:
 结构说明 :
*****************************************************************************/
typedef struct
{
    NAS_LMM_SYS_CHNG_ORI_ENUM_UINT32        ulSusOri;       /* 挂起的发源地 */
    NAS_LMM_SYS_CHNG_ORI_ENUM_UINT32        ulRsmOri;       /* 恢复的发源地 */

    NAS_LMM_SUS_SYS_CHNG_DIR_ENUM_UINT32    ulSusDir;       /* RRC挂起的方向 */
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    ulRsmDir;       /* RRC恢复的方向 */

    NAS_LMM_SYS_CHNG_TYPE_ENUM_UINT32       ulSusType;      /* RRC挂起的类型 */
    NAS_LMM_SYS_CHNG_TYPE_ENUM_UINT32       ulRsmType;      /* RRC恢复的类型 */

    NAS_LMM_SUS_CAUSE_ENUM_UINT32           ulSusCause;     /* RRC挂起的原因: 如CSFB */

    /*LRRC_LMM_SUSPEND_IND消息中携带的HoSecuPra*/
    NAS_LMM_HO_SECU_PARA_STRU               stHoSecuPara;

    /* 挂起前的状态 */
    NAS_LMM_FSM_STATE_STRU                   stStateBeforeSuspend;

    /* 恢复前的状态 */
    NAS_LMM_FSM_STATE_STRU                   stStateBeforeResume;

    VOS_UINT32                              ulUpLayerCount; /* 通知高层的计数器 */

}NAS_LMM_SYS_CHNG_CTRL_STRU;

/*****************************************************************************
 结构名称: NAS_LMM_GU_ACT_RST_STRU
 协议表格:
 ASN.1描述:
 结构说明 :z00179470    2011-06-02 new
           保存GU ACTION RSLT到本地
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpGuReqDomain  : 1;
    VOS_UINT32                          bitOpGuRstDomain  : 1;
    VOS_UINT32                          bitOpGuMtDetachType:1;
    VOS_UINT32                          bitOpGuCnCause    : 1;
    VOS_UINT32                          bitOpGuAtmpCnt    : 1;
    VOS_UINT32                          bitSpare          : 27;
    /* 服务类型*/
    NAS_LMM_GU_ACTION_TYPE_ENUM_UINT32              ulGuActionType;

    /* CN_ACCEPT, CN_REJECT：各流程网络响应的结果 */
    NAS_LMM_GU_ACTION_RSLT_TYPE_ENUM_UINT32         ulGuActRst;


    /* 发起业务时的类型:仅ATTACH, RAU, DETACH时有效 */
    NAS_LMM_GU_DOMAIN_ENUM_UINT32                   ulGuActReqDomain;

    /* 结果域类型，仅ATTACH, TAU, DETACH时有效，网络响应的结果 */
    NAS_LMM_GU_DOMAIN_ENUM_UINT32                   ulGuActRstDomain;

    /*  仅 MT DETACH时有效 */
    NAS_LMM_MT_DETACH_TYPE_ENUM_UINT32              ulGuMtDetachType;

    /* 网络下发的原因 */
    NAS_EMM_CN_CAUSE_ENUM_UINT8                     ucCnCause;

    VOS_UINT8                                       aucRsv1[3];

    /* ATTACH或RAU失败尝试次数 */
    VOS_UINT32                                      ulAttemptCount;
}NAS_LMM_GU_ACT_RST_STRU;


/*****************************************************************************
 结构名称: NAS_LMM_EMERGENCY_NUM_LIST
 协议表格:
 ASN.1描述:
 结构说明 :See subclause 10.5.3.13 in 3GPP TS 24.008

        8       7       6       5       4       3       2       1
    ┌───────────────────────────────┐
    │                 Emergency Number List IEI                    │Octet 1
    ├───────────────────────────────┤
    │    Length of Emergency Number List IE contents               │Octet 2
    ├───────────────────────────────┤
    │    Length of 1st Emergency Number information note 1)        │Octet 3
    ├───────────────────────────────┤
    │              spare   │   mergency Service Category Value    │
    │                      │(see Table 10.5.135d/3GPP TS 24.008)) │Octet 4
    ├───────────────────────────────┤
    │    Number digit 2    │          Number digit 1              │Octet 5
    ├───────────────────────────────┤
    │    Number digit 4    │          Number digit 3              │Octet 6*
    ├───────────────────────────────┤
    │                    ...                                       │
    ├───────────────────────────────┤
    │                                                              │Octet j-1*
    ├───────────────────────────────┤
    │      Length of 2nd Emergency Number information note 1)      │Octet j*
    ├───────────────────────────────┤
    │              spare   │   mergency Service Category Value    │
    │                      │(see Table 10.5.135d/3GPP TS 24.008)) │Octet j+1*
    ├───────────────────────────────┤
    │    Number digit 2    │          Number digit 1              │Octet j+2*
    ├───────────────────────────────┤
    │    Number digit 4    │          Number digit 3              │Octet j+3*
    ├───────────────────────────────┤
    │                    ...                                       │
    ├───────────────────────────────┤
    │                                                              │Octet n*
    ├───────────────────────────────┤
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEmergencyNumAmount;
    VOS_UINT8                           aucReserved[3];
    LMM_MM_EMERGENCY_NUM_STRU           astEmergencyNumList[MM_LMM_EMERGENCY_NUM_LIST_MAX_RECORDS];
}NAS_LMM_EMERGENCY_NUM_LIST_STRU;

/*****************************************************************************
 结构名称: NAS_EMM_REJ_RECODE_STRU
 协议表格:
 ASN.1描述:
 结构说明 :UE被拒记录
*****************************************************************************/
typedef struct
{
    NAS_EMM_REJ_FLAG_ENUM_UINT32        enRejCause2Flag;
    NAS_EMM_REJ_FLAG_ENUM_UINT32        enRejCause18Flag;
} NAS_EMM_REJ_RECODE_STRU;
/*****************************************************************************
 结构名称: NAS_EMM_TRIGGER_TAU_FLAG_STRU
 协议表格:
 ASN.1描述:
 结构说明 :触发TAU标记
*****************************************************************************/
typedef struct
{
    GMM_LMM_GPRS_MM_STATE_ENUM_UINT32            enGprsMmState;
    GMM_LMM_PACKET_MM_STATE_ENUM_UINT32          enPacketMmState;
    GMM_LMM_GPRS_SUSPENSION_STATE_ENUM_UINT32    enGprsSuspensionState;
    NAS_EMM_LAU_OR_COMBINED_RAU_FLAG_ENUM_UINT32 enLauOrCombinedRauFlag;
    NAS_EMM_T3412_EXP_ENUM_UINT32                enEmmT3412ExpCtrl;      /*T3412超时消息是否超时*/
    VOS_UINT32                                   ulEmmDrxNetCapChange;   /*指示Drx或NetCapability改变*/
    NAS_EMM_TRIGGER_TAU_RRC_REL_ENUM_UINT32      enTriggerTauRrcRel;     /*RRC连接删除原因是否能够触发TAU*/
    VOS_UINT32                                   ulTriggerTauSysChange;  /*指示系统变换能否触发TAU*/
    NAS_EMM_EPS_BEARER_CONTEXT_STATUS_ENUM_UINT32   enStatusChange;
    NAS_EMM_SRVCC_FLAG_ENUM_UINT32                enSrvccFlag;

    VOS_UINT32                                  ulVoiceDomainChange;    /* voice domain发生变化，需要触发TAU */
    VOS_UINT8                                   ucLaiChangeFlag;        /* LAI发生变化 */
    VOS_UINT8                                   ucEmcConnExitFlag;      /* 触发了紧急建链 */
    VOS_UINT8                                   aucRsv[2];
} NAS_EMM_TRIGGER_TAU_FLAG_STRU;

/*****************************************************************************
 结构名称: NAS_EMM_TRIGGER_TAU_FLAG_STRU
 协议表格:
 ASN.1描述:
 结构说明 :触发TAU标记
*****************************************************************************/
typedef struct
{
    NAS_EMM_CCO_CHANGE_TIN_FLAG_ENUM_UINT32     ulTinChagFlag;
    MMC_LMM_TIN_TYPE_ENUM_UINT32                ulTinType;
} MMC_LMM_CCO_FLAG_STRU;
/*****************************************************************************
 结构名    : NAS_LMM_SYSCFG_CTRL_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    NAS_LMM_UE_RADIO_CAP_CHANGE_ENUM_UINT32                   enRadioAccCapChgFlag;
    NAS_LMM_SYSCFG_FLAG_ENUM_UINT32                           enSyscfgFlag;
}NAS_LMM_SYSCFG_CTRL_STRU;

/*****************************************************************************
结构名称    :LNAS_LMM_ATT_REQUIRE_PARA_STRU
使用说明    :AT&T定制需求，EMM维护参数结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                    ulCServiceMax;       /* NV中的值，有效范围1-60，默认值5 */
    VOS_UINT32                    ulCServiceCount;     /* EMM本地维护CService计数         */
    VOS_UINT32                    ulT3402Len;          /* EMM本地维护T3402时长            */
    NAS_DAM_CONFIG_PLMN_PARA      stDamConfigPlmnPara; /* DAM特性生效的PLMN列表           */
} LNAS_LMM_DAM_PARA_STRU;


/*****************************************************************************
 枚举名    : NAS_EMM_SUSPEND_CAUSE_ENUM
 枚举说明  : 标识当进入REG+NORMAL_SERVICE时，是否需要改为进入REG+ATTEMPT_TO_UPDATE_MM
*****************************************************************************/
enum  NAS_EMM_SUSPEND_REL_CAUSE_ENUM
{
    NAS_EMM_SUSPEND_REL_CAUSE_MMC_ORI       = 1,
    NAS_EMM_SUSPEND_REL_CAUSE_ABORT_CSFB    = 2,

    NAS_EMM_SUSPEND_REL_CAUSE_BUTT
};
typedef VOS_UINT32   NAS_EMM_SUSPEND_REL_CAUSE_ENUM_UINT32;


/*****************************************************************************
结构名称    :NAS_EMM_PUB_INFO_STRU
使用说明    :MM的公用信息
             bitOp**，标识对应的信息是否有效，取值及含义如下:
             #define NAS_EMM_BIT_SLCT      1 :      VALID
             #define NAS_EMM_BIT_NO_SLCT   0 :      INVALID
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpUeId           :1;
    VOS_UINT32                          bitOpNetInfo        :1;
    VOS_UINT32                          bitOpDrx            :1;
    VOS_UINT32                          bitOpUeNetCap       :1;
    VOS_UINT32                          bitOpMsNetCap       :1;
    VOS_UINT32                          bitOpSupCodecList   :1;
    VOS_UINT32                          bitOpRaMod          :1;
    VOS_UINT32                          bitOpAppPara        :1;
    VOS_UINT32                          bitOpUeMode         :1;
    VOS_UINT32                          bitOpCsService      :1;
    VOS_UINT32                          bitOpVoiceDomain    :1;
    VOS_UINT32                          bitOpEmgList        :1;
    VOS_UINT32                          bitOpNetFeature     :1;
    VOS_UINT32                          bitOpRsv            :19;

    NAS_LMM_UEID_STRU                   stMmUeId;
    NAS_LMM_NETWORK_INFO_STRU           stNetInfo;
    NAS_MM_DRX_STRU                     stDrx;
    NAS_MM_UE_NET_CAP_STRU              stUeNetCap;
    NAS_MM_MS_NET_CAP_STRU              stMsNetCap;
    /*NAS_LMM_EPS_BEARER_CONTEXT_STRU     stEpsBearerCxt;*/

    NAS_LMM_CODEC_LIST_STRU             stSupCodecList;
    NAS_EMM_RAT_TYPE_ENUM_UINT32        enRaMod;    /* V7R1只用其中LTE的TDD和FDD */
    NAS_LMM_APP_PARA_STRU               stAppPara;
    NAS_EMM_INFO_STRU                   stEmmInfoPara;
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      enLastAirMsgType;
    VOS_UINT8                           ucIsMsgIntegrityFlag; /* 消息是否是完整性保护的标识，VOS_TRUE:是完整性保护的，VOS_FALSE:明文 */
    VOS_UINT8                           ucTmoUsimCardFlag; /* 开机后根据NV和IMSI确认是否是TMO卡的标识 */
    VOS_UINT8                           aucRsv[1];
    NAS_LMM_SIM_STAT_ENUM_UINT32        ulSimStat;
    NAS_LMM_SIM_VALIDITY_ENUM_UINT32    enPsSimValidity;
    NAS_EMM_START_INFO_STRU             stEmmStartInfo;

    NAS_LMM_SYS_CHNG_CTRL_STRU          stSysChngCtrl;
    NAS_LMM_GU_ACT_RST_STRU             stLmmGuActRst;/*保存GU ACT RESULT*/

    /* h41410 for ue mode begin */
    NAS_LMM_GU_UE_MODE_ENUM_UINT32              ulGuUeMode;
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32       ulLteUeMode;    /* h41410 CHANGE for ue mode */
    NAS_EMM_USAGE_SETTING_UINT32                ulUsageSetting;
    NAS_LMM_CS_SERVICE_ENUM_UINT32              ulCsService;


    NAS_LMM_SUP_ENUM_UINT32                     aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_BUTT]; /* UE 支持哪些语音域 */
    NAS_LMM_VOICE_DOMAIN_ENUM_UINT32            ulVoiceDomain;    /*Voice domain preference for E-UTRAN*/

    NAS_LMM_SUP_ENUM_UINT32                     aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_BUTT]; /* UE 支持哪些SMS域 */
    NAS_LMM_SUP_SMS_DOMAIN_ENUM_UINT32          ulSmsDomainPrefer;  /* UE 选择优先使用哪个域执行SMS业务 */

    NAS_LMM_SUP_ENUM_UINT32                     ulLmmSupIms;    /* UE LMM是否支持IMS，不是 IMS voice not available */
    /*NAS_LMM_SUP_ENUM_UINT32                     ulCSFBAvail;   */ /*"CS fallback is not available" includes EMM causes #16, #17, #18 and #22*/

    NAS_LMM_EMERGENCY_NUM_LIST_STRU             stEmergencyNumList;

    MMC_LMM_UTRAN_MODE_ENUM_UINT8               enUtranMode;
    VOS_UINT8                                   ucNetFeature;   /* 当前网络是否支持IMS */
    /* 关机标识,提供给LRRC,用于LRRC判断空口是否是关机detach,在lmm收到mmc的关机请求时置为1，在收到LRRC关机回复、等待LRRC关机回复超时或者开机时清除 */
    VOS_UINT8                                   ucLtePowerOffFlag;

    NAS_EMM_T3402_SRC_ENUM_UINT8                enT3402Src;

    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  enAdditionUpRslt;
    NAS_LMM_REG_DOMAIN_ENUM_UINT32              enRegisteredDomain;
    NAS_EMM_FIRST_TAU_FLAG_ENUM_UINT32          enFirstTauFlag;          /* 0表示非GU注册成功后的第一次TAU，1表示GU注册成功后的第一次TAU */
    /* h41410 for ue mode end */
    /* LRRC的SYSCFG 挂起通知的类型 */
    NAS_LMM_SUSPEND_TYPE_NOTIFY_ENUM_UINT32     ulRrcSysCfgSusType;
    NAS_LMM_CONNECTION_CLIENT_ID_ENUM_UINT32     enNasConnectionClientId;
    NAS_EMM_REJ_RECODE_STRU                     stRejRecord;
    NAS_LMM_LTE_ENABLE_STA_ENUM_UINT32          enLteEnableSta; /*标识E-UNTRA是否使能*/
    NAS_EMM_UPDATE_MM_FLAG_ENUM_UINT32          enUpdateMmFlag;         /* 标识当进入REG+NORMAL_SERVICE时，是否需要改为进入REG+ATTEMPT_TO_UPDATE_MM */
    VOS_UINT32                                  ulPlmnSrchNoImsiFlag ;

    NAS_LMM_SYSCFG_CTRL_STRU                    stSyscfgCtrl;
    NAS_EMM_TRIGGER_TAU_FLAG_STRU               stTriggerTauFlag;

    MMC_LMM_ATT_REASON_ENUM_UINT32              enMmcAttachReason;  /* MMC指定的ATTACH原因，因CL多模需求新增此变量 */
    /* 保存上次写卡或写NV的EPS LOC码流 */
    VOS_UINT8        aucLastWriteUsimPsLoc[NAS_EMM_EPS_LOC_MAX_LEN];

    MMC_LMM_CCO_FLAG_STRU                       stCcoFlag;

    NAS_LMM_REG_STATUS_ENUM_UINT32              enRegStatus;        /* 标识注册状态 */
    VOS_UINT32                                  ulIsEmerPndEsting;  /* 标识是否正在紧急PDN建立，0表示不在进行，1表示正在进行 */
    VOS_UINT8                                  *pucEsmMsg;          /* 用于存储紧急类型的PDN请求以及OPID */
    /*VOS_UINT8                                   aucRsv2[3];*/
    GMM_LMM_TIMER_STATE_ENUM_UINT32             enT3312State;
    VOS_UINT32                                  ulNasRelease;

    NAS_EMM_SUSPEND_REL_CAUSE_ENUM_UINT32       ulSuspendRelCause;  /* 停止挂起流程的原因 */

    MMC_LMM_IMS_VOICE_CAP_ENUM_UINT8            enImsaVoiceCap;     /*IMS voice capability*/
    LNAS_LMM_CONFIG_NWCAUSE_STRU                stConfCause;

    NAS_EMM_DSDS_TAU_TYPE_ENUM_UINT32          enDsdsTauType;

    LNAS_LMM_DAM_PARA_STRU                      stDamPara;           /* 美国项目DAM参数 */
    VOS_UINT32                                  ulRej19AtmptCntFlag; /* NV中配置的ATTACH收到REJ#19时可尝试次数标识 */

}NAS_LMM_PUB_INFO_STRU;
typedef NAS_LMM_PUB_INFO_STRU            NAS_EMM_PUB_INFO_STRU;
typedef NAS_LMM_PUB_INFO_STRU            NAS_MMC_PUB_INFO_STRU;
/*PC REPLAY MODIFY BY LEILI DELETE*/


/*****************************************************************************
  6 UNION
*****************************************************************************/

/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

/*****************************************************************************
  9 OTHERS
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasLmmCore.h*/
