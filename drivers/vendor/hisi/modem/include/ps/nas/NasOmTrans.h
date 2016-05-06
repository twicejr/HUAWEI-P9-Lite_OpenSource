/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasOmTrans.h
  版 本 号   : 初稿
  作    者   : l00171473
  生成日期   : 2012年04月27日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2012年04月27日
    作    者   : l00171473
    修改内容   : 创建文件, DTS2011102200898, 由于TRANS消息和EVENT消息的顶级结构不同,
                 为了ASN解析TRANS消息, 将该头文件中的TRANS消息相关部分提取到新增的
                 NasOmTrans.h 中

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
/* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */
#include  "MmcLmmInterface.h"
/* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, end */
/* Added by wx270776 for OM融合, 2015-8-10, begin */
#include  "NasOmInterface.h"
/* Added by wx270776 for OM融合, 2015-8-10, end */
#ifndef __NASOMTRANS_H__
#define __NASOMTRANS_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define LEN_PTMSI                       4
#define LEN_TMSI                        4


#define LEN_MOBILE                      16

#define MAX_AVAILABEL_PLMN_NUM          16

#define NAS_OM_PDP_CONTEXT_MAX          11                                      /* 最大的PDP上下文的个数 */

#define SM_MAX_LENGTH_OF_APN            101
#define SM_IP_ADDR_LEN                  4
#define SM_IPV6_ADDR_LEN                16

/* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */
#define NAS_MS_ID_GUTI_VALID            (1)
#define NAS_MS_ID_PTMSI_IMSI_VALID      (2)
/* Deleted by z00301431 for OM融合, 2015-6-27 begin */
/* Deleted by z00301431 for OM融合, 2015-6-27 end */
#define NAS_MAX_IMSI_LEN                (9)
/* Added by wx270776 for OM融合, 2015-8-3, begin */
#define NAS_MAX_IMSI_ASN_LEN            (12)
/* Added by wx270776 for OM融合, 2015-8-3, end */
/* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, end */
/*增加NAS和OM之间的TRANS_PRIMID*/
#define NAS_OM_TRANS_PRIMID             0x5001

/* Added by wx270776 for OM融合, 2015-7-23, begin */
#define NAS_OTA_MSG_ASN_LEN_OFFSET      (8)
/* Added by wx270776 for OM融合, 2015-7-23, end */
#define NAS_OM_MMA_UATI_OCTET_LENGTH       (16)
#define NAS_OM_MMA_MEID_OCTET_NUM          (7)

#define NAS_OM_CDMA_ZONE_NODE_MAX_NUM                   (7)
#define NAS_OM_CDMA_SIDNID_NODE_MAX_NUM                 (4)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : NAS_OM_TRANS_MSG_TYPE_ENUM
 结构说明  : NAS透传消息类型枚举
 修改历史      :
 1.日    期   : 2012年04月27日
   作    者   : L00171473
   修改内容   : DTS2011102200898, 调整TRANS消息相关结构到新增头文件, 以支持ANS解析

 2.日    期   : 2012年11月06日
   作    者   : l00198894
   修改内容   : Probe路测工具对接项目新增数据业务相关消息
*****************************************************************************/
enum NAS_OM_TRANS_MSG_TYPE_ENUM
{
    /* NAS层分配区间[0xC000,0x0xC7FF] */

    ID_NAS_OM_MM_INQUIRE                                    = 0xC001,   /*_H2ASN_MsgChoice ID_NAS_OM_INQUIRE_ASN_STRU*/
    ID_NAS_OM_MM_CONFIRM                                    = 0xC002,   /*_H2ASN_MsgChoice NAS_OM_MM_IND_ASN_STRU*/

    ID_NAS_OM_QOS_INQUIRE                                   = 0xC003,   /*_H2ASN_MsgChoice ID_NAS_OM_INQUIRE_ASN_STRU*/
    ID_NAS_OM_QOS_CONFIRM                                   = 0xC004,   /*_H2ASN_MsgChoice NAS_QOS_IND_ASN_STRUCT*/

    ID_NAS_OM_PDP_CONTEXT_INQUIRE                           = 0xC005,   /*_H2ASN_MsgChoice ID_NAS_OM_INQUIRE_ASN_STRU*/
    ID_NAS_OM_PDP_CONTEXT_CONFIRM                           = 0xC006,   /*_H2ASN_MsgChoice NAS_OM_PDP_CONTEXT_IND_ASN_STRU*/

    /*增加GSM CODEC类型的设置*/
    ID_NAS_OM_SET_CODEC_TYPE_REQUIRE                        = 0xC007,   /*_H2ASN_MsgChoice NAS_OM_SET_GSM_CODEC_CONFIG_REQ_STRU*/
    ID_NAS_OM_SET_CODEC_TYPE_CONFIRM                        = 0xC008,   /*_H2ASN_MsgChoice NAS_OM_SET_GSM_CODEC_CONFIG_CNF_STRU*/

    /*增加当前使用CODEC类型和GSM CODEC集合的查询*/
    ID_NAS_OM_CODEC_TYPE_INQUIRE                            = 0xC009,   /*_H2ASN_MsgChoice ID_NAS_OM_INQUIRE_ASN_STRU*/
    ID_NAS_OM_CODEC_TYPE_CONFIRM                            = 0xC00a,   /*_H2ASN_MsgChoice NAS_OM_CODEC_TYPE_CNF_STRU*/

    /* 查询数据业务流量、速率等 */
    ID_NAS_OM_SET_DSFLOW_RPT_REQ                            = 0xC00B,   /*_H2ASN_MsgChoice NAS_OM_SET_DSFLOW_RPT_REQ_STRU*/
    ID_NAS_OM_SET_DSFLOW_RPT_CNF                            = 0xC00C,   /*_H2ASN_MsgChoice NAS_OM_SET_DSFLOW_RPT_CNF_STRU*/
    ID_NAS_OM_DSFLOW_RPT_IND                                = 0xC00D,   /*_H2ASN_MsgChoice NAS_OM_DSFLOW_RPT_IND_STRU*/

    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */
    ID_NAS_OM_SMS_INQUIRE                                   = 0xC00E,   /*_H2ASN_MsgChoice ID_NAS_OM_INQUIRE_ASN_STRU*/
    ID_NAS_OM_SMS_CONFIRM                                   = 0xC00F,   /*_H2ASN_MsgChoice NAS_OM_SMS_IND_ASN_STRU*/

    ID_NAS_OM_CONFIG_TIMER_REPORT_REQ                       = 0xC010,   /*_H2ASN_MsgChoice NAS_OM_CONFIG_TIMER_REPORT_REQ_ASN_STRU*/
    ID_NAS_OM_CONFIG_TIMER_REPORT_CNF                       = 0xC011,   /*_H2ASN_MsgChoice NAS_OM_CONFIG_TIMER_REPORT_CNF_ASN_STRU*/
    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */

    ID_OM_NAS_MMA_CDMA_STATUS_INFO_REPORT_REQ               = 0xC012,     /* _H2ASN_MsgChoice OM_NAS_MMA_CDMA_STATUS_INFO_REPORT_REQ_ASN_STRU */
    ID_NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_CNF               = 0xC013,     /* _H2ASN_MsgChoice NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_CNF_ASN_STRU */
    ID_NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_IND               = 0xC014,     /* _H2ASN_MsgChoice NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_IND_ASN_STRU */

    ID_OM_NAS_CDMA_REG_INFO_REPORT_REQ                      = 0xC015,
    ID_NAS_OM_CDMA_REG_INFO_REPORT_CNF                      = 0xC016,
    ID_NAS_OM_CDMA_REG_PRD_REPORT_IND                       = 0xC017,
    ID_NAS_OM_CDMA_REG_TYPE_REPORT_IND                      = 0xC018,
    ID_NAS_OM_CDMA_REG_LIST_REPORT_IND                      = 0xC019,

    ID_OM_NAS_CDMA_START_GPS_FIX_REQ                        = 0xC020, /* _H2ASN_MsgChoice OM_NAS_CDMA_START_GPS_FIX_REQ_STRU */
    ID_NAS_OM_CDMA_START_GPS_FIX_CNF                        = 0xC021, /* _H2ASN_MsgChoice NAS_OM_CDMA_START_GPS_FIX_CNF_STRU */
    ID_OM_NAS_CDMA_STOP_GPS_FIX_REQ                         = 0xC022, /* _H2ASN_MsgChoice OM_NAS_CDMA_STOP_GPS_FIX_REQ_STRU */
    ID_NAS_OM_CDMA_STOP_GPS_FIX_CNF                         = 0xC023, /* _H2ASN_MsgChoice NAS_OM_CDMA_STOP_GPS_FIX_CNF_STRU */
    ID_NAS_OM_CDMA_GPS_FIX_RSLT_IND                         = 0xC024, /* _H2ASN_MsgChoice NAS_OM_CDMA_GPS_FIX_RSLT_IND_STRU */
    ID_NAS_OM_CDMA_GPS_SIGNAL_MSG_IND                       = 0xC025, /* _H2ASN_MsgChoice NAS_OM_CDMA_GPS_SIGNAL_MSG_IND_STRU */
    ID_NAS_OM_CDMA_GPS_FIX_START_IND                        = 0xC026, /* _H2ASN_MsgChoice NAS_OM_CDMA_GPS_FIX_START_IND_STRU */

    /* NAS层分配区间[0xC000,0x0xC7FF] */
    ID_NAS_OM_TRANS_BUTT                                    = 0xC7FF
};

typedef VOS_UINT16 NAS_OM_TRANS_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : NAS_OM_MM_STATE_ENUM
 结构说明  : MM 状态枚举
 修改历史      :
 1.日    期   : 2012年04月27日
   作    者   : L00171473
   修改内容   : DTS2011102200898, 调整TRANS消息相关结构到新增头文件, 以支持ANS解析
*****************************************************************************/
enum NAS_OM_MM_STATE_ENUM
{
    STATE_MM_NULL                                           = 0,
    STATE_MM_IDLE                                           = 1,
    WAIT_FOR_OUTGOING_MM_CONNECT                            = 9,
    MM_CONNECT_ACT                                          = 10,
    WAIT_FOR_NET_COMMAND                                    = 11,
    WAIT_FOR_RR_CONNECT_MM_CONNECT                          = 12,
    WAIT_FOR_REEST_WAIT_FOR_REEST_REQ                       = 13,
    WAIT_FOR_REEST_WAIT_FOR_EST_CNF                         = 14,
    WAIT_FOR_RR_ACT                                         = 15,
    WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECT                 = 16,
    LOCATION_UPDATING_PEND                                  = 17,
    IMSI_DETACH_PEND                                        = 18,
    MM_WAIT_FOR_ATTCH                                       = 19,
    WAIT_FOR_RR_CONNECT_LOCATION_UPDATING                   = 22,
    LU_INITIATED                                            = 23,
    LU_REJECTED                                             = 24,
    WAIT_FOR_RR_CONNECT_IMSI_DETACH                         = 25,
    IMSI_DETACH_INITIATE                                    = 26,
    PROCESS_CM_SERV_PROMPT                                  = 27,
    TEST_CONTROL_ACT                                        = 31,
    MM_INTER_RAT_CHG                                        = 32,
    MM_STATE_BUTT
};
typedef VOS_UINT8 NAS_OM_MM_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MM_UPDATE_STATUS_ENUM
 结构说明  : MM UPDATE 状态枚举
 修改历史      :
 1.日    期   : 2012年04月27日
   作    者   : L00171473
   修改内容   : DTS2011102200898, 调整TRANS消息相关结构到新增头文件, 以支持ANS解析
 2.日    期   : 2014年6月16日
   作    者   : w00176964
   修改内容   : DTS2014061006131:MM增加新的U值
*****************************************************************************/
enum MM_UPDATE_STATUS_ENUM
{
    UPDATE_STATUS_U1                    = 0,                                    /* U1 */
    UPDATE_STATUS_U2                    = 1,                                    /* U2 */
    UPDATE_STATUS_U3                    = 2,                                    /* U3 */
    UPDATE_STATUS_U4                    = 3,                                    /* U4 */
    MM_UPDATE_STATUS_BUTT
};
typedef VOS_UINT8 MM_UPDATE_STATUS_ENUM_UINT8;

/* 以下二个枚举宏与MS VisualStudio 中定义冲突，注意值不同带来影响 */
#ifdef __NAS_OM_UT__
#ifdef DEREGISTERED
#undef DEREGISTERED
#endif
#ifdef REGISTERED
#undef REGISTERED
#endif
#endif

/*****************************************************************************
 枚举名    : NAS_OM_GMM_STATE_ENUM
 结构说明  : GMM 状态枚举
 修改历史      :
 1.日    期   : 2012年04月27日
   作    者   : L00171473
   修改内容   : DTS2011102200898, 调整TRANS消息相关结构到新增头文件, 以支持ANS解析
*****************************************************************************/
enum NAS_OM_GMM_STATE_ENUM
{
    STATE_GMM_NULL                      = 0x00,
    REGISTERED_INITIATED                = 0x01,
    DEREGISTERED_INITIATED              = 0x02,
    ROUTING_AREA_UPDATING_INITIATED     = 0x03,
    SERVICE_REQUEST_INITIATED           = 0x04,
    TC_ACTIVE                           = 0x05,
    GPRS_SUSPENSION                     = 0x06,
    DEREGISTERED                        = 0x10,
    REGISTERED                          = 0X20,
    SUSPENDED_NORMAL_SERVICE            = 0x30,
    SUSPENDED_GPRS_SUSPENSION           = 0x31,
    SUSPENDED_WAIT_FOR_SYSINFO          = 0x32,
    GMM_STATE_BUTT
};
typedef VOS_UINT8 NAS_OM_GMM_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GMM_UPDATE_STATUS_ENUM
 结构说明  : GMM UPDATE 状态枚举
 修改历史      :
 1.日    期   : 2012年04月27日
   作    者   : L00171473
   修改内容   : DTS2011102200898, 为了TRANS消息的ANS解析, 新增头文件
*****************************************************************************/
enum GMM_UPDATE_STATUS_ENUM
{
    UPDATE_STATUS_GU1                   = 0,                                    /* GU1 */
    UPDATE_STATUS_GU2                   = 1,                                    /* GU2 */
    UPDATE_STATUS_GU3                   = 2,                                    /* GU3 */
    GMM_UPDATE_STATUS_BUTT
};
typedef VOS_UINT8 GMM_UPDATE_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : PLMN_SEL_MODE_ENUM
 结构说明  : 选网模式枚举
 修改历史      :
 1.日    期   : 2012年04月27日
   作    者   : L00171473
   修改内容   : DTS2011102200898, 为了TRANS消息的ANS解析, 新增头文件
*****************************************************************************/
enum PLMN_SEL_MODE_ENUM
{
    PLMN_SEL_MODE_AUTO                  = 0,
    PLMN_SEL_MODE_MANUAL                = 1,
    PLMN_SEL_MODE_BUTT
};
typedef VOS_UINT8 PLMN_SEL_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : UE_OPERATE_MODE_ENUM
 结构说明  : 选网模式
 修改历史      :
 1.日    期   : 2012年04月27日
   作    者   : L00171473
   修改内容   : DTS2011102200898, 为了TRANS消息的ANS解析, 新增头文件
*****************************************************************************/
enum UE_OPERATE_MODE_ENUM
{
    UE_OPERATE_MODE_NULL                = 0,
    UE_OPERATE_MODE_A                   = 1,
    UE_OPERATE_MODE_CG                  = 2,
    UE_OPERATE_MODE_CC                  = 3,
    UE_OPERATE_MODE_B                   = 4,
    UE_OPERATE_MODE_BUTT
};
typedef VOS_UINT8 UE_OPERATE_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NET_OPERATE_MODE_ENUM
 结构说明  : 网络模式枚举
 修改历史      :
 1.日    期   : 2012年04月27日
   作    者   : L00171473
   修改内容   : DTS2011102200898, 为了TRANS消息的ANS解析, 新增头文件
*****************************************************************************/
enum NET_OPERATE_MODE_ENUM
{
    NET_OPERATE_MODE_1                  = 0,
    NET_OPERATE_MODE_2                  = 1,
    NET_OPERATE_MODE_3                  = 2,
    NET_OPERATE_MODE_BUTT
};
typedef VOS_UINT8 NET_OPERATE_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NET_TYPE_ENUM
 结构说明  : 接入模式枚举
 修改历史      :
 1.日    期   : 2012年04月27日
   作    者   : L00171473
   修改内容   : DTS2011102200898, 为了TRANS消息的ANS解析, 新增头文件
*****************************************************************************/
enum NET_TYPE_ENUM
{
    NET_TYPE_GSM                        = 0,
    NET_TYPE_WCDMA                      = 1,
    NET_TYPE_LTE                        = 2,
    NET_TYPE_BUTT
};
typedef VOS_UINT8 NET_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_MM_SUB_STATE_ENUM
 结构说明  : MM 子状态枚举
 修改历史      :
 1.日    期   : 2012年04月27日
   作    者   : L00171473
   修改内容   : DTS2011102200898, 为了TRANS消息的ANS解析, 新增头文件
 2.日    期   : 2014年6月16日
   作    者   : w00176964
   修改内容   : DTS2014061006131:MM增加新的协议状态
*****************************************************************************/
enum NAS_OM_MM_SUB_STATE_ENUM
{
    NO_CELL_AVAILABLE                   = 1,
    PLMN_SEARCH                         = 2,
    NORMAL_SERVICE                      = 3,
    LIMITED_SERVICE                     = 4,
    ATTEMPTING_TO_UPDATE                = 5,
    LOCATION_UPDATE_NEEDED              = 6,
    PLMN_SEARCH_NORMAL_SERVICE          = 7,
    NO_IMSI                             = 8,
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-6-11, begin */
    ECALL_INACTIVE                      = 9,
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-6-11, end */
    MM_SUB_STATE_BUTT
};
typedef VOS_UINT8 NAS_OM_MM_SUB_STATE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : NAS_OM_GMM_SUB_STATE_ENUM
 结构说明  : GMM 子状态枚举
 修改历史      :
 1.日    期   : 2012年04月27日
   作    者   : L00171473
   修改内容   : DTS2011102200898, 为了TRANS消息的ANS解析, 新增头文件
*****************************************************************************/
enum NAS_OM_GMM_SUB_STATE_ENUM
{
    DEREGISTERED_NORMAL_SERVICE         = 0x10,
    DEREGISTERED_LIMITED_SERVICE        = 0x11,
    DEREGISTERED_ATTACH_NEEDED          = 0x12,
    DEREGISTERED_ATTEMPTING_TO_ATTACH   = 0x13,
    DEREGISTERED_NO_CELL_AVAILABLE      = 0x14,
    DEREGISTERED_PLMN_SEARCH            = 0x15,
    DEREGISTERED_NO_IMSI                = 0x16,
    REGISTERED_NORMAL_SERVICE           = 0x20,
    REGISTERED_LIMITED_SERVICE          = 0x21,
    REGISTERED_UPDATE_NEEDED            = 0x22,
    REGISTERED_ATTEMPTING_TO_UPDATE     = 0x23,
    REGISTERED_NO_CELL_AVAILABLE        = 0x24,
    REGISTERED_PLMN_SEARCH              = 0x25,
    REGISTERED_ATTEMPTING_TO_UPDATE_MM  = 0x26,
    REGISTERED_IMSI_DETACH_INITIATED    = 0x27,
    REGISTERED_WAIT_FOR_RAU             = 0x28,
    GMM_SUB_STATE_BUTT
};
typedef VOS_UINT8 NAS_OM_GMM_SUB_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_SERVICE_STATE_ENUM
 结构说明  : 服务状态枚举
 修改历史      :
 1.日    期   : 2012年04月27日
   作    者   : L00171473
   修改内容   :
*****************************************************************************/
enum NAS_OM_SERVICE_STATE_ENUM
{
    NAS_OM_SERVICE_STATE_NO_SERVICE                         = 0,                /* 无服务状态       */
    NAS_OM_SERVICE_STATE_LIMITED_SERVICE                    = 1,                /* 限制服务状态     */
    NAS_OM_SERVICE_STATE_NORMAL_SERVICE                     = 2,                /* 正常工作状态     */
    NAS_OM_SERVICE_STATE_REGIONAL_LIMITED_SERVICE           = 3,                /* 有限制的区域服务 */
    NAS_OM_SERVICE_STATE_DEEP_SLEEP                         = 4,                /* 省电和深睡眠状态 */
    NAS_OM_SERVICE_STATE_BUTT
};
typedef VOS_UINT8 NAS_OM_SERVICE_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_PDP_ACT_TYPE_ENUM
 结构说明  : PDP激活类型枚举
 修改历史      :
 1.日    期   : 2012年04月27日
   作    者   : L00171473
   修改内容   :
*****************************************************************************/
enum NAS_OM_PDP_ACT_TYPE_ENUM
{
    NAS_OM_PDP_ACT_PRI                  = 0,                                    /* 主激活PDP */
    NAS_OM_PDP_ACT_SEC,                                                         /* 二次激活PDP */
    NAS_OM_PDP_ACT_BUTT                 = 0xFF
};
typedef VOS_UINT8 NAS_OM_PDP_ACT_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_CURR_CODEC_TYPE_ENUM
 结构说明  : CODEC类型枚举
             当前使用的CODEC类型,不和CALL模块定义的一致目的是为了匹配上报可配置的当前GSM支持的CODEC类型
 修改历史      :
 1.日    期   : 2012年04月27日
   作    者   : L00171473
   修改内容   :
*****************************************************************************/
enum NAS_OM_CURR_CODEC_TYPE_ENUM
{
    NAS_OM_CODEC_TYPE_FR                = 0x01,                                 /* full rate */
    NAS_OM_CODEC_TYPE_HR                = 0x02,                                 /* half rate */
    NAS_OM_CODEC_TYPE_EFR               = 0x04,                                 /* enhanced full rate */
    NAS_OM_CODEC_TYPE_AMR               = 0x08,                                 /* amr */
    NAS_OM_CODEC_TYPE_AMR2              = 0x10,                                 /* amr2 */

    NAS_OM_CODEC_TYPE_AMRWB             = 0x20,                                 /* amr2 */

    NAS_OM_CODEC_TYPE_BUTT                                                      /* invalid value */
};
typedef VOS_UINT8 NAS_OM_CURR_CODEC_TYPE_ENUM_U8;

/*****************************************************************************
 枚举名    : NAS_OM_GSM_CODEC_CONFIG_ENUM
 结构说明  : GSM CODEC类型枚举
 修改历史      :
 1.日    期   : 2012年04月27日
   作    者   : L00171473
   修改内容   :
*****************************************************************************/
enum NAS_OM_GSM_CODEC_CONFIG_ENUM
{
    NAS_OM_GSM_CODEC_FR                 = 0x01,                                 /* FR */
    NAS_OM_GSM_CODEC_FR_HR              = 0x03,                                 /* FR+HR */
    NAS_OM_GSM_CODEC_FR_EFR             = 0x05,                                 /* FR+EFR */
    NAS_OM_GSM_CODEC_FR_AMR             = 0x09,                                 /* FR+AMR */
    NAS_OM_GSM_CODEC_FR_EFR_HR_AMR      = 0x0F,                                 /* FR+EFR+HR+AMR */
    NAS_OM_GSM_CODEC_BUTT
};
typedef VOS_UINT8 NAS_OM_GSM_CODEC_CONFIG_ENUM_U8;

/*******************************************************************************
 枚举名    : NAS_OM_GMM_GPRS_STATE_ENUM
 结构说明  : GMM GPRS 状态枚举
 修改历史      :
 1.日    期   : 2012年11月06日
   作    者   : l00198894
   修改内容   : Probe路测工具对接项目新增枚举
*******************************************************************************/
enum NAS_OM_GMM_GPRS_STATE_ENUM
{
    NAS_OM_GMM_GPRS_IDLE                                    = 0x00,             /* GPRS空闲态 */
    NAS_OM_GMM_GPRS_STANDBY                                 = 0x01,             /* GPRS等待态 */
    NAS_OM_GMM_GPRS_READY                                   = 0x02,             /* GPRS可用态 */
    NAS_OM_GMM_GPRS_STATE_BUTT                              = 0xFF              /* GPRS状态无效值 */
};
typedef VOS_UINT8 NAS_OM_GMM_GPRS_STATE_ENUM_UINT8;

/*******************************************************************************
 枚举名    : NAS_OM_REPORT_ACTION_ENUM
 结构说明  : NAS给OM主动上报状态枚举
 修改历史      :
 1.日    期   : 2012年11月06日
   作    者   : l00198894
   修改内容   : Probe路测工具对接项目新增枚举
*******************************************************************************/
enum NAS_OM_REPORT_ACTION_ENUM
{
    NAS_OM_REPORT_STOP                                      = 0x00,             /* 停止主动上报 */
    NAS_OM_REPORT_START                                     = 0x01,             /* 启动主动上报 */

    NAS_OM_REPORT_BUTT
};
typedef VOS_UINT8 NAS_OM_REPORT_ACTION_ENUM_UINT8;

/*******************************************************************************
 枚举名    : NAS_OM_RESULT_ENUM
 结构说明  : NAS与OM间结果错误码枚举
 修改历史      :
 1.日    期   : 2012年11月06日
   作    者   : l00198894
   修改内容   : Probe路测工具对接项目新增枚举
*******************************************************************************/
enum NAS_OM_RESULT_ENUM
{
    NAS_OM_RESULT_NO_ERROR                                  = 0,                /* 消息处理正常 */
    NAS_OM_RESULT_ERROR                                     = 1,                /* 消息处理出错 */
    NAS_OM_RESULT_INCORRECT_PARAMETERS,

    NAS_OM_RESULT_BUTT
};
typedef VOS_UINT32 NAS_OM_RESULT_ENUM_UINT32;
/*****************************************************************************
 枚举名    : NAS_OM_MMA_CDMA_STATUS_REPORT_RESRLT_ENUM_UINT32
 结构说明  : om 请求mma上报cdma状态信息结果值
 1.日    期   : 2015年7月09日
   作    者   : y00322978
   修改内容   :
*****************************************************************************/
enum NAS_OM_MMA_CDMA_STATUS_REPORT_RESRLT_ENUM
{
    NAS_OM_MMA_CDMA_STATUS_REPORT_RESULT_FAIL = 0X0,
    NAS_OM_MMA_CDMA_STATUS_REPORT_RESULT_SUCC = 0X1,
    NAS_OM_MMA_CDMA_STATUS_REPORT_RESULT_BUTT
};
typedef VOS_UINT32 NAS_OM_MMA_CDMA_STATUS_REPORT_RESRLT_ENUM_UINT32;
/*****************************************************************************
 枚举名    : OM_NAS_MMA_CDMA_STATUS_REPORT_CMD_ENUM_UINT8
 结构说明  : om 请求mma上报cdma状态信息 命令枚举值
 1.日    期   : 2015年7月09日
   作    者   : y00322978
   修改内容   :
*****************************************************************************/
enum OM_NAS_MMA_CDMA_STATUS_REPORT_CMD_ENUM
{
    OM_NAS_MMA_CDMA_STATUS_REPORT_CMD_NOT_REPORT = 0X0,
    OM_NAS_MMA_CDMA_STATUS_REPORT_CMD_ONCE = 0X1,
    OM_NAS_MMA_CDMA_STATUS_REPORT_CMD_FOREVER = 0X2,
    OM_NAS_MMA_CDMA_STATUS_REPORT_CMD_BUTT
};
typedef VOS_UINT8 OM_NAS_MMA_CDMA_STATUS_REPORT_CMD_ENUM_UINT8;


/*****************************************************************************
 枚举名    : NAS_OM_MMA_SYS_MODE_ENUM_UINT8
 结构说明  : 驻留网络的系统模式枚举
 1.日    期   : 2015年7月09日
   作    者   : y00322978
   修改内容   :
*****************************************************************************/
enum NAS_OM_MMA_SYS_MODE_ENUM
{
    SYS_MODE_GSM = 0x0,
    SYS_MODE_WCDMA = 0x1,
    SYS_MODE_LTE = 0x2,
    SYS_MODE_CDMA_1X = 0x3,
    SYS_MODE_EVDO = 0x4,
    SYS_MODE_HYBRID = 0x5,
    SYS_MODE_SVLTE = 0x6,
    SYS_MODE_BUTT
};
typedef VOS_UINT8  NAS_OM_MMA_SYS_MODE_ENUM_UINT8;
/*****************************************************************************
 枚举名    : NAS_OM_MMA_PHONE_MODE_ENUM
 枚举说明  : 手机模式枚举
 1.日    期   : 2015年05月22日
   作    者   : y00322978
   修改内容   : 新增
*****************************************************************************/
enum NAS_OM_MMA_PHONE_MODE_ENUM
{
    PHONE_MODE_MINI                = 0,   /* minimum functionality*/
    PHONE_MODE_FULL                = 1,   /* full functionality */
    PHONE_MODE_TXOFF               = 2,   /* disable phone transmit RF circuits only */
    PHONE_MODE_RXOFF               = 3,   /* disable phone receive RF circuits only */
    PHONE_MODE_RFOFF               = 4,   /* disable phone both transmit and receive RF circuits */
    PHONE_MODE_FT                  = 5,   /* factory-test functionality */
    PHONE_MODE_RESET               = 6,   /* reset */
    PHONE_MODE_VDFMINI             = 7,   /* mini mode required by VDF*/
    PHONE_MODE_POWEROFF            = 8,   /* 关机下电模式 */
    PHONE_MODE_LOWPOWER            = 9,
    PHONE_MODE_BUTT
};
typedef VOS_UINT8 NAS_OM_MMA_PHONE_MODE_ENUM_UINT8;

/* Added by wx270776 for OM融合, 2015-8-26, begin */
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )

#if ( 3 == MULTI_MODEM_NUMBER )/* three modems */

enum MODEM_ID_ASN_ENUM
{
    MODEM_0 = 0,
    MODEM_1 = 1,
    MODEM_2 = 2,
    MODEM_BUTT
};

#else/* two modems */

enum MODEM_ID_ASN_ENUM
{
    MODEM_0 = 0,
    MODEM_1 = 1,
    MODEM_BUTT,
    MODEM_2
};

#endif

#else/* only one */

enum MODEM_ID_ASN_ENUM
{
    MODEM_0 = 0,
    MODEM_BUTT,
    MODEM_1,
    MODEM_2
};

#endif

typedef VOS_UINT16 MODEM_ID_ASN_ENUM_UINT16;
/* Added by wx270776 for OM融合, 2015-8-26, end */



enum NAS_OM_MMA_HRPD_SESSION_STATUS_ENUM
{
    HRPD_SESSION_STATUS_CLOSE              = 0x00,
    HRPD_SESSION_STATUS_OPEN               = 0x01,

    HRPD_SESSION_STATUS_BUTT               = 0XFF
};
typedef VOS_UINT8 NAS_OM_MMA_HRPD_SESSION_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_1X_CALL_STATE_ENUM
 结构说明  : 1X呼叫状态

 1.日    期   : 2015年05月22日
   作    者   : y00322978
   修改内容   : 新增
*****************************************************************************/
enum NAS_OM_1X_CALL_STATE_ENUM
{
    CDMA_1X_CALL_STATE_IDLE  = 0x0,
    CDMA_1X_CALL_STATE_ORIGNALING_CALL = 0x1,
    CDMA_1X_CALL_STATE_INCOMING_CALL = 0x2,
    CDMA_1X_CALL_STATE_CONVERSATION = 0x3,

    CDMA_1X_CALL_STATE_BUTT = 0XFF
};
typedef VOS_UINT8 NAS_OM_1X_CALL_STATE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : NAS_OM_MMA_SYS_SUBMODE_ENUM_UINT8
 结构说明  : 驻留网络的系统子模式枚举
 1.日    期   : 2015年7月9日
   作    者   : y00322978
   修改内容   :
*****************************************************************************/
enum NAS_OM_MMA_SYS_SUBMODE_ENUM
{
    SYS_SUBMODE_NONE                = 0,                                /* 无服务 */
    SYS_SUBMODE_GSM                 = 1,                                /* GSM模式 */
    SYS_SUBMODE_GPRS                = 2,                                /* GPRS模式 */
    SYS_SUBMODE_EDGE                = 3,                                /* EDGE模式 */
    SYS_SUBMODE_WCDMA               = 4,                                /* WCDMA模式 */
    SYS_SUBMODE_HSDPA               = 5,                                /* HSDPA模式 */
    SYS_SUBMODE_HSUPA               = 6,                                /* HSUPA模式 */
    SYS_SUBMODE_HSDPA_HSUPA         = 7,                                /* HSDPA+HSUPA模式 */
    SYS_SUBMODE_TD_SCDMA            = 8,                                /* TD_SCDMA模式 */
    SYS_SUBMODE_HSPA_PLUS           = 9,                                /* HSPA+模式 */
    SYS_SUBMODE_LTE                 = 10,                               /* LTE模式 */
    SYS_SUBMODE_DC_HSPA_PLUS        = 17,                               /* DC-HSPA+模式 */
    SYS_SUBMODE_DC_MIMO             = 18,                               /* MIMO-HSPA+模式 */

    SYS_SUBMODE_CDMA_1X             = 23,                               /* CDMA2000 1X*/
    SYS_SUBMODE_EVDO_REL_0          = 24,                               /* EVDO Rel0*/
    SYS_SUBMODE_EVDO_REL_A          = 25,                               /* EVDO RelA*/
    SYS_SUBMODE_HYBRID_EVDO_REL_0   = 28,                               /* Hybrid(EVDO Rel0)*/
    SYS_SUBMODE_HYBRID_EVDO_REL_A   = 29,                               /* Hybrid(EVDO RelA)*/

    SYS_SUBMODE_EHRPD               = 31,                               /* EHRPD模式 */

    NAS_OM_MMA_SYS_SUBMODE_BUTT     = 0XFF
};
typedef VOS_UINT8  NAS_OM_MMA_SYS_SUBMODE_ENUM_UINT8;


/** ****************************************************************************
 * Name        : NAS_OM_MMA_PPP_STATUS_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum NAS_OM_MMA_PPP_STATUS_ENUM
{
    PPP_STATUS_INACTIVE     = 0x00,
    PPP_STATUS_IDLE         = 0x01,
    PPP_STATUS_ACTIVE       = 0x02,
    PPP_STATUS_BUTT         = 0x03
};
typedef VOS_UINT8 NAS_OM_MMA_PPP_STATUS_ENUM_UINT8;


/* Added by zwx247453 for 寄存器上报, 2015-09-17, begin */
/*****************************************************************************
 枚举名    : NAS_OM_FSM_ID_ENUM
 枚举说明  : 状态机ID枚举定义
 1.日    期   : 2015年9月17日
   作    者   : zwx247453
   修改内容   : 新建
*****************************************************************************/
enum NAS_OM_FSM_ID_ENUM
{
    /* NAS MMC L1状态机的名称 */
    NAS_OM_FSM_L1_MAIN                                     =0,

    /* NAS MMC L2状态机的名称,存在多个L2状态机 */

    /* 协议栈初始化L2状态机 */
    NAS_OM_FSM_SWITCH_ON                                   =1,

    /* 协议栈关机L2状态机 */
    NAS_OM_FSM_POWER_OFF                                   =2,

    /* PLMN SELECTION 状态机 */
    NAS_OM_FSM_PLMN_SELECTION                              =3,

    /* ANYCELL搜网状态机 */
    NAS_OM_FSM_ANYCELL_SEARCH                              =4,

    /* 异系统重选状态机 */
    NAS_OM_FSM_INTER_SYS_CELLRESEL                         =5,

    /* 异系统出服务区搜网状态机 */
    NAS_OM_FSM_INTER_SYS_OOS                               =6,

    /* 列表搜网状态机 */
    NAS_OM_FSM_PLMN_LIST                                   =7,

    /* SYSCFG配置L2状态机 */
    NAS_OM_FSM_SYSCFG                                      =8,

    /* BG搜网L2状态机 */
    NAS_OM_FSM_BG_PLMN_SEARCH                              =9,

    /* 异系统Handover状态机 */
    NAS_OM_FSM_INTER_SYS_HO                                =10,

    /* 异系统CellChange状态机 */
    NAS_OM_FSM_INTER_SYS_CCO                               =11,

    /* 获取地理信息状态机 */
    NAS_OM_FSM_GET_GEO                                     =12,

    NAS_OM_FSM_BUTT

};
typedef VOS_UINT8 NAS_OM_FSM_ID_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_TIN_TYPE_ENUM
 结构说明  : TIN的类型
  1.日    期   : 2015年9月21日
    作    者   : zwx247453
    修改内容   : 新增加操作类型
*****************************************************************************/
enum NAS_OM_TIN_TYPE_ENUM
{
    NAS_OM_TIN_TYPE_PTMSI             = 0,                                    /* TIN类型为PTMSI */
    NAS_OM_TIN_TYPE_GUTI              = 1,                                    /* TIN类型为GUTI */
    NAS_OM_TIN_TYPE_RAT_RELATED_TMSI  = 2,                                    /* TIN类型为RAT_RELATED_TMSI */
    NAS_OM_TIN_TYPE_INVALID           = 3,                                    /* TIN类型无效 */
    NAS_OM_TIN_TYPE_BUTT
};
typedef VOS_UINT8 NAS_OM_TIN_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_DELAY_CLASS_ENUM
 结构说明  : Delayclass的类型
  1.日    期   : 2015年9月21日
    作    者   : zwx247453
    修改内容   : 新增加操作类型
*****************************************************************************/
enum NAS_OM_DELAY_CLASS_ENUM
{
    NAS_OM_SUBSCRIBED_DELAY_CLASS      = 0,
    NAS_OM_DELAY_CLASS1                = 1,
    NAS_OM_DELAY_CLASS2                = 2,
    NAS_OM_DELAY_CLASS3                = 3,
    NAS_OM_DELAY_CLASS4_BEST_EFFORT    = 4,
    NAS_OM_DELAY_RESERVED              = 7
};
typedef VOS_UINT8 NAS_OM_DELAY_CLASS_ENUM_UINT8;


/*****************************************************************************
 枚举名    : NAS_OM_RELIABILITY_CLASS_ENUM
 结构说明  : Reliabilityclass的类型
  1.日    期   : 2015年9月21日
    作    者   : zwx247453
    修改内容   : 新增加操作类型
*****************************************************************************/
enum NAS_OM_RELIABILITY_CLASS_ENUM
{
    NAS_OM_SUBSCRIBED_RELIABILITY_CLASS                           = 0,
    NAS_OM_ACKNOWLEDGED_GTP_LLC_RLC_PROTEDTED_DATA                = 1,
    NAS_OM_UNACKNOWLEDGED_GTP_ACKNOWLEDGED_LLC_RLC_PROTECTED_DATA = 2,
    NAS_OM_UNACKNOWLEDGED_GTP_LLC_ACKNOWLEDGED_RLC_PROTECTED_DATA = 3,
    NAS_OM_UNACKNOWLEDGED_GTP_LLC_RLC_PROTECTED_DATA              = 4,
    NAS_OM_UNACKNOWLEDGED_GTP_LLC_RLC_UNPROTECTED_DATA            = 5,
    NAS_OM_RELIABILITY_RESERVED                                   = 7
};
typedef VOS_UINT8 NAS_OM_RELIABILITY_CLASS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_PEAK_THROUGH_PUT_ENUM
 结构说明  : Peakthroughput的类型
  1.日    期   : 2015年9月21日
    作    者   : zwx247453
    修改内容   : 新增加操作类型
*****************************************************************************/
enum NAS_OM_PEAK_THROUGH_PUT_ENUM
{
    NAS_OM_SUBSCRIBED_PEAK_THROUGH      = 0,
    NAS_OM_UPTO1000                     = 1,
    NAS_OM_UPTO2000                     = 2,
    NAS_OM_UPTO4000                     = 3,
    NAS_OM_UPTO8000                     = 4,
    NAS_OM_UPTO16000                    = 5,
    NAS_OM_UPTO32000                    = 6,
    NAS_OM_UPTO64000                    = 7,
    NAS_OM_UPTO128000                   = 8,
    NAS_OM_UPTO256000                   = 9,
    NAS_OM_PEAK_THROUGH_RESERVED        = 15
};
typedef VOS_UINT8 NAS_OM_PEAK_THROUGH_PUT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_PRECEDENCE_CLASS_ENUM
 结构说明  : Precedenceclass的类型
  1.日    期   : 2015年9月21日
    作    者   : zwx247453
    修改内容   : 新增加操作类型
*****************************************************************************/
enum NAS_OM_PRECEDENCE_CLASS_ENUM
{
    NAS_OM_SUBSCRIBED_PRECEDENCE      = 0,
    NAS_OM_HIGH_PRIORITY              = 1,
    NAS_OM_NORMAL_PRIORITY            = 2,
    NAS_OM_LOW_PRIORITY               = 3,
    NAS_OM_PRECEDENCE_RESERVED        = 7
};
typedef VOS_UINT8 NAS_OM_PRECEDENCE_CLASS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_MEAN_THROUGH_ENUM
 结构说明  : Meanthroughput的类型
  1.日    期   : 2015年9月21日
    作    者   : zwx247453
    修改内容   : 新增加操作类型
*****************************************************************************/
enum NAS_OM_MEAN_THROUGH_ENUM
{
    NAS_OM_SUBSCRIBED_MEAN_THROUGH      = 0,
    NAS_OM_M100                         = 1,
    NAS_OM_M200                         = 2,
    NAS_OM_M500                         = 3,
    NAS_OM_M1000                        = 4,
    NAS_OM_M2000                        = 5,
    NAS_OM_M5000                        = 6,
    NAS_OM_M10000                       = 7,
    NAS_OM_M20000                       = 8,
    NAS_OM_M50000                       = 9,
    NAS_OM_M100000                      = 10,
    NAS_OM_M200000                      = 11,
    NAS_OM_M500000                      = 12,
    NAS_OM_M1000000                     = 13,
    NAS_OM_M2000000                     = 14,
    NAS_OM_M5000000                     = 15,
    NAS_OM_M10000000                    = 16,
    NAS_OM_M20000000                    = 17,
    NAS_OM_M50000000                    = 18,
    NAS_OM_MEAN_THROUGH_RESERVED        = 30,
    NAS_OM_BEST_EFFORT                  = 31
};
typedef VOS_UINT8 NAS_OM_MEAN_THROUGH_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_TRAFFIC_CLASS_ENUM
 结构说明  : Traffic-Class的类型
  1.日    期   : 2015年9月21日
    作    者   : zwx247453
    修改内容   : 新增加操作类型
*****************************************************************************/
enum NAS_OM_TRAFFIC_CLASS_ENUM
{
    NAS_OM_SUBSCRIBED_TRAFFIC_CLASS   = 0,
    NAS_OM_CONVERSATIONAL_CLASS       = 1,
    NAS_OM_STREAMING_CLASS            = 2,
    NAS_OM_INTERACTIVE_CLASS          = 3,
    NAS_OM_BACKGROUND_CLASS           = 4,
    NAS_OM_TRAFFIC_CLASS_RESERVED     = 7
};
typedef VOS_UINT8 NAS_OM_TRAFFIC_CLASS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_DELIVERY_ORDER_ENUM
 结构说明  : Delivery-order的类型
  1.日    期   : 2015年9月21日
    作    者   : zwx247453
    修改内容   : 新增加操作类型
*****************************************************************************/
enum NAS_OM_DELIVERY_ORDER_ENUM
{
    NAS_OM_SUBSCRIBED_DELIVERY_ORDER   = 0,
    NAS_OM_WITH_DELIVERY_ORDER         = 1,
    NAS_OM_WITHOUT_DELIVERY_ORDER      = 2,
    NAS_OM_DELIVERY_ORDER_RESERVED     = 3
};
typedef VOS_UINT8 NAS_OM_DELIVERY_ORDER_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_DELIVERY_ERR_SDU_ENUM
 结构说明  : Delivery-of-err-SDU的类型
  1.日    期   : 2015年9月21日
    作    者   : zwx247453
    修改内容   : 新增加操作类型
*****************************************************************************/
enum NAS_OM_DELIVERY_ERR_SDU_ENUM
{
    NAS_OM_SUBSCRIBED_DELIVERY_OF_ERRONEOUS_SDUS   = 0,
    NAS_OM_NO_DETECT                               = 1,
    NAS_OM_ERRONEOUS_SDUS_ARE_DELIVERED            = 2,
    NAS_OM_ERRONEOUS_SDUS_ARE_NOT_DELIVERED        = 3,
    NAS_OM_ERRONEOUS_SDUS_RESERVED                 = 7
};
typedef VOS_UINT8 NAS_OM_DELIVERY_ERR_SDU_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_RESIDUAL_BER_ENUM
 结构说明  : Residual-BER的类型
  1.日    期   : 2015年9月21日
    作    者   : zwx247453
    修改内容   : 新增加操作类型
*****************************************************************************/
enum NAS_OM_RESIDUAL_BER_ENUM
{
    NAS_OM_SUBSCRIBED_RESIDUAL_BER = 0,
    NAS_OM_RBER52                  = 1,
    NAS_OM_RBER12                  = 2,
    NAS_OM_RBER53                  = 3,
    NAS_OM_RBER43                  = 4,
    NAS_OM_RBER13                  = 5,
    NAS_OM_RBER14                  = 6,
    NAS_OM_RBER15                  = 7,
    NAS_OM_RBER16                  = 8,
    NAS_OM_RBER68                  = 9,
    NAS_OM_RESIDUAL_BER_RESERVED   = 10
};
typedef VOS_UINT8 NAS_OM_RESIDUAL_BER_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_SDU_ERROR_RATIO_ENUM
 结构说明  : SDU-error-ratio的类型
  1.日    期   : 2015年9月21日
    作    者   : zwx247453
    修改内容   : 新增加操作类型
*****************************************************************************/
enum NAS_OM_SDU_ERROR_RATIO_ENUM
{
    NAS_OM_SUBSCRIBED_SDU_ERROR_RATIO = 0,
    NAS_OM_ERROR_RATIO12              = 1,
    NAS_OM_ERROR_RATIO73              = 2,
    NAS_OM_ERROR_RATIO13              = 3,
    NAS_OM_ERROR_RATIO14              = 4,
    NAS_OM_ERROR_RATIO15              = 5,
    NAS_OM_ERROR_RATIO16              = 6,
    NAS_OM_ERROR_RATIO11              = 7,
    NAS_OM_SDU_ERROR_RATIO_RESERVED   = 15
};
typedef VOS_UINT8 NAS_OM_SDU_ERROR_RATIO_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_TRAFF_HAND_PRIO_ENUM
 结构说明  : Traffic-Handling-priority的类型
  1.日    期   : 2015年9月21日
    作    者   : zwx247453
    修改内容   : 新增加操作类型
*****************************************************************************/
enum NAS_OM_TRAFF_HAND_PRIO_ENUM
{
    NAS_OM_SUBSCRIBED_TRAFFIC_HANDLING_PRIORITY = 0,
    NAS_OM_PRIORITY_LEVEL1                      = 1,
    NAS_OM_PRIORITY_LEVEL2                      = 2,
    NAS_OM_PRIORITY_LEVEL3                      = 3
};
typedef VOS_UINT8 NAS_OM_TRAFF_HAND_PRIO_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_APS_ADDR_ENUM
 结构说明  : PDP上下文的状态

 1.日    期   : 2015年09月17日
   作    者   : zwx247453
   修改内容   : 新增
*****************************************************************************/
enum NAS_OM_APS_ADDR_ENUM
{
    NAS_OM_APS_ADDR_DYNAMIC_IPV4         = 0,
    NAS_OM_APS_ADDR_STATIC_IPV4          = 1,
    NAS_OM_APS_ADDR_PPP                  = 2,
    NAS_OM_MN_APS_ADDR_IPV6              = 3,
    NAS_OM_MN_APS_ADDR_IPV4V6            = 4,

    NAS_OM_APS_ADDR_TYPE_BUTT
};
typedef VOS_UINT8 NAS_OM_APS_ADDR_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_SM_PDP_STATE_ENUM
 结构说明  : PDP上下文的状态

 1.日    期   : 2015年09月17日
   作    者   : zwx247453
   修改内容   : 新增
*****************************************************************************/
enum NAS_OM_SM_PDP_STATE_ENUM
{
    NAS_OM_SM_PDP_ACTIVATED              = 0x0,
    NAS_OM_SM_PDP_NOT_ACTIVATED          = 0x1,

    NAS_OM_SM_PDP_STATE_BUTT
};
typedef VOS_UINT8 NAS_OM_SM_PDP_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_SMC_MO_STATE_ENUM
 结构说明  : SMC MO实体的状态

 1.日    期   : 2015年09月17日
   作    者   : zwx247453
   修改内容   : 新增
*****************************************************************************/
enum NAS_OM_SMC_MO_STATE_ENUM
{
    NAS_OM_SMC_MO_IDLE                = 0x0,
    NAS_OM_SMC_MO_GMM_CONN_PENDING    = 0x1,
    NAS_OM_SMC_MO_WAIT_FOR_CP_ACK     = 0x2,
    NAS_OM_SMC_MO_WAIT_FOR_CP_DATA    = 0x3,
    NAS_OM_SMC_MO_MM_CONN_PENDING     = 0x4,
    NAS_OM_SMC_MO_MM_CONN_EST         = 0x5,
    NAS_OM_SMC_MO_WAIT_TO_SND_CP_ACK  = 0x6,

    NAS_OM_SMC_MO_STATE_BUTT
};
typedef VOS_UINT8 NAS_OM_SMC_MO_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_SMC_MT_STATE_ENUM
 结构说明  : SMC MT实体的状态

 1.日    期   : 2015年09月17日
   作    者   : zwx247453
   修改内容   : 新增
*****************************************************************************/
enum NAS_OM_SMC_MT_STATE_ENUM
{
    NAS_OM_SMC_MT_IDLE                = 0x0,
    NAS_OM_SMC_MT_WAIT_FOR_RP_ACK     = 0x1,
    NAS_OM_SMC_MT_WAIT_FOR_CP_ACK     = 0x2,
    NAS_OM_SMC_SMC_MT_MM_CONN_EST     = 0x3,

    NAS_OM_SMC_MT_STATE_BUTT
};
typedef VOS_UINT8 NAS_OM_SMC_MT_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_SMR_STATE_ENUM
 结构说明  : SMR MT实体的状态

 1.日    期   : 2015年09月17日
   作    者   : zwx247453
   修改内容   : 新增
*****************************************************************************/
enum NAS_OM_SMR_STATE_ENUM
{
    NAS_OM_SMR_IDLE                   = 0x0,
    NAS_OM_SMR_WAIT_FOR_RP_ACK        = 0x1,
    NAS_OM_SMR_WAIT_TO_SND_RP_ACK     = 0x2,
    NAS_OM_SMR_WAIT_FOR_RETRANS_TIMER = 0x3,

    NAS_OM_SMR_STATE_BUTT
};
typedef VOS_UINT8 NAS_OM_SMR_STATE_ENUM_UINT8;
/* Added by zwx247453 for 寄存器上报, 2015-09-17, end */

/*****************************************************************************
 枚举名    : NAS_OM_CDMA_REG_TYPE_ENUM_UINT32
 枚举说明  : 注册类型
  1.日    期   : 2015年10月20日
    作    者   : g00256031
    修改内容   : 创建
*****************************************************************************/
enum NAS_OM_CDMA_REG_TYPE_ENUM
{
    NAS_OM_CDMA_TIMER_BASED_REGISTRATION                    = 0x00,
    NAS_OM_CDMA_POWER_UP_REGISTRATION                       = 0x01,
    NAS_OM_CDMA_ZONE_BASED_REGISTRATION                     = 0x02,
    NAS_OM_CDMA_POWER_DOWN_REGISTRATION                     = 0x03,
    NAS_OM_CDMA_PARAMETER_CHANGED_REGISTRATION              = 0x04,
    NAS_OM_CDMA_ORDERED_REGISTRATION                        = 0x05,
    NAS_OM_CDMA_DISTANCE_BASED_REGISTRATION                 = 0x06,
    NAS_OM_CDMA_USER_ZONE_BASED_REGISTRATION                = 0x07,
    NAS_OM_CDMA_ENCRYPTION_RE_SYNC_REQUIRED_REGISTRATION    = 0x08,
    NAS_OM_CDMA_IMPLICIT_REGISTRATION                       = 0x09,
    NAS_OM_CDMA_TRAFFIC_CHANNEL_REGISTRATION                = 0x0a,
    NAS_OM_CDMA_REG_MODE_BUTT,
};
typedef VOS_UINT32 NAS_OM_CDMA_REG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_OM_CDMA_BLKSYS_ENUM_UINT8
 枚举说明  : 系统块
1.日    期   : 2015年10月20日
  作    者   : g00256031
  修改内容   : 创建
*****************************************************************************/
enum NAS_OM_CDMA_BLKSYS_ENUM
{
    NAS_OM_CDMA_BLKSYS_PCS_A = 0,
    NAS_OM_CDMA_BLKSYS_PCS_B,
    NAS_OM_CDMA_BLKSYS_PCS_C,
    NAS_OM_CDMA_BLKSYS_PCS_D,
    NAS_OM_CDMA_BLKSYS_PCS_E,
    NAS_OM_CDMA_BLKSYS_PCS_F,
    NAS_OM_CDMA_BLKSYS_CELL_A,
    NAS_OM_CDMA_BLKSYS_CELL_B,
    NAS_OM_CDMA_BLKSYS_BUTT
};
typedef VOS_UINT8 NAS_OM_CDMA_BLKSYS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_CDMA_GPS_FIX_MODE_ENUM
 枚举说明  :
1.日    期   : 2015年12月16日
  作    者   : y00174758
  修改内容   : 创建
*****************************************************************************/
enum NAS_OM_CDMA_GPS_FIX_MODE_ENUM
{
    NAS_OM_CDMA_GPS_FIX_MODE_UNKNOWN    = 0,
    NAS_OM_CDMA_GPS_FIX_MODE_MSA,
    NAS_OM_CDMA_GPS_FIX_MODE_MSB,
    NAS_OM_CDMA_GPS_FIX_MODE_MSS,
    NAS_OM_CDMA_GPS_FIX_MODE_MONITOR,
    NAS_OM_CDMA_GPS_FIX_MODE_BUTT
};
typedef VOS_UINT8 NAS_OM_CDMA_GPS_FIX_MODE_ENUM_UINT8;

/*****************************************************************************
枚举名    : NAS_OM_CDMA_GPS_START_MODE_ENUM
枚举说明  : GPS启动类型

  1.日    期   : 2015年12月17日
    作    者   : y00174758
    修改内容   : 新增枚举
*****************************************************************************/
enum NAS_OM_CDMA_GPS_START_MODE_ENUM
{
    NAS_OM_CDMA_GPS_START_MODE_COLD,
    NAS_OM_CDMA_GPS_START_MODE_HOT,
    NAS_OM_CDMA_GPS_START_MODE_BUTT
};
typedef VOS_UINT8 NAS_OM_CDMA_GPS_START_MODE_ENUM_UINT8;

/*****************************************************************************
枚举名    : NAS_OM_CDMA_GPS_FIX_RSLT_ENUM
枚举说明  : GPS定位结果

  1.日    期   : 2015年12月18日
    作    者   : y00174758
    修改内容   : 新增枚举
*****************************************************************************/
enum NAS_OM_CDMA_GPS_FIX_RSLT_ENUM
{
    NAS_OM_CDMA_GPS_FIX_RSLT_SUCCESS,
    NAS_OM_CDMA_GPS_FIX_RSLT_FAIL_MPC,
    NAS_OM_CDMA_GPS_FIX_RSLT_FAIL_OTHER,
    NAS_OM_CDMA_GPS_FIX_RSLT_BUTT
};
typedef VOS_UINT8 NAS_OM_CDMA_GPS_FIX_RSLT_ENUM_UINT8;

/*****************************************************************************
枚举名    : NAS_OM_CDMA_GPS_FIX_TYPE_ENUM
枚举说明  :

  1.日    期   : 2015年12月18日
    作    者   : y00174758
    修改内容   : 新增枚举
*****************************************************************************/
enum NAS_OM_CDMA_GPS_FIX_TYPE_ENUM
{
    NAS_OM_CDMA_GPS_FIX_TYPE_UNKNOWN    = 0x00,
    NAS_OM_CDMA_GPS_FIX_TYPE_2D         = 0x01,
    NAS_OM_CDMA_GPS_FIX_TYPE_3D         = 0x02,
    NAS_OM_CDMA_GPS_FIX_TYPE_MAX        = 0x10,
    NAS_OM_CDMA_GPS_FIX_TYPE_ENUM_BUTT  = 0x11
};
typedef VOS_UINT8 NAS_OM_CDMA_GPS_FIX_TYPE_ENUM_UINT8;

/*****************************************************************************
枚举名    : NAS_OM_CDMA_GPS_MSG_TYPE_ENUM
枚举说明  :

  1.日    期   : 2015年12月18日
    作    者   : y00174758
    修改内容   : 新增枚举
*****************************************************************************/
enum NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_ENUM
{
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_TCP_MPC_RL_START_POS_REQ,          /* 0 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_TCP_MPC_RL_POS_REPORT,             /* 1 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_TCP_MPC_RL_CANCEL_TRACK,           /* 2 */

    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_TCP_MPC_FL_START_POS_RSP,          /* 3 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_TCP_MPC_FL_POS_REPORT_RSP,         /* 4 */

    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_SMS_MPC_RL_REJ_POS_REQ,            /* 5 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_SMS_MPC_RL_CANCEL_POS_NTF,         /* 6 */

    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_SMS_MPC_FL_POS_REQ,                /* 7 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_SMS_MPC_FL_CANCEL_NI_TRACK,        /* 8 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_SMS_MPC_FL_REFRESH_MR_TRACK,       /* 9 */

    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_RL_REQ_LOC_RSP,                /* 10 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_RL_REQ_GPS_ACQ_ASSIST,         /* 11 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_RL_REQ_GPS_ALM,                /* 12 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_RL_REQ_GPS_EPH,                /* 13 */

    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_RL_RSP_PROV_LOC_RSP,           /* 14 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_RL_RSP_PROV_MS_INFO,           /* 15 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_RL_RSP_PROV_PSUEDO_MEAS,       /* 16 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_RL_RSP_PROV_PH_MEAS,           /* 17 */

    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_REQ_LOC_RSP,                /* 18 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_REQ_MS_INFO,                /* 19 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_REQ_PSUEDO_MEAS,            /* 20 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_REQ_PH_MEAS,                /* 21 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_REQ_CANCELLATION,           /* 22 */

    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_RSP_REJECT,                 /* 23 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_RSP_PROV_LOC_RSP,           /* 24 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_RSP_PROV_GPS_ACQ_ASSIST,    /* 25 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_RSP_PROV_GPS_ALM,           /* 26 */
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_RSP_PROV_GPS_EPH,           /* 27 */

    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_BUTT,
};
typedef VOS_UINT8 NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_ENUM_UINT8;

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

/*******************************************************************************
 结构名    : MS_ID_STRUCT
 结构说明  : MS ID 结构定义
 修改历史      :
  1.日    期   : 2012年04月27日
    作    者   : l00171473
    修改内容   :
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;
    VOS_UINT8                           ucMobileIDValue[LEN_MOBILE];
    VOS_UINT8                           ucReserved[3];
}MS_ID_STRUCT;

/*******************************************************************************
 结构名    : PLMN_ID_STRUCT
 结构说明  : PLMN ID 结构定义
 修改历史      :
  1.日    期   : 2012年04月27日
    作    者   : l00171473
    修改内容   :
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucMccDigit[3];
    VOS_UINT8                           ucMncCount;
    VOS_UINT8                           aucMncDigit[3];
    VOS_UINT8                           ucReserved[1];
}PLMN_ID_STRUCT;

/*******************************************************************************
 结构名    : AVAILABLE_PLMN_STRUCT
 结构说明  : AVAILABLE ID 结构定义
 修改历史      :
  1.日    期   : 2012年04月27日
    作    者   : l00171473
    修改内容   :
*******************************************************************************/
typedef struct
{
    PLMN_ID_STRUCT                      Plmn;
    NET_TYPE_ENUM_UINT8                 ucRat;
    VOS_UINT8                           ucReserved[3];
}AVAILABLE_PLMN_STRUCT;

/* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */
/*****************************************************************************
 结构名称: NAS_GUMM_PTMSI_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 见 24.008 10.5.1.4
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPtmsi[NAS_MAX_SIZE_PTMSI];
} NAS_OM_PTMSI_STRU;
/*******************************************************************************
 结构名    : NAS_OM_MS_ID_STRU
 结构说明  : 上报TIN值的数据结构
 修改历史      :
  1.日    期   : 2013年06月26日
    作    者   : l00167671
    修改内容   : DCM LOGGER可谓可测SMC SMR状态上报
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsId;
    NAS_LMM_GUTI_STRU                   stGuti;
    NAS_OM_PTMSI_STRU                   stPtmsi;
    VOS_UINT8                           aucImsi[NAS_MAX_IMSI_LEN];
}NAS_OM_MS_ID_STRU;

/* Added by wx270776 for OM融合, 2015-8-3, begin */
/*******************************************************************************
 结构名    : NAS_OM_MS_ID_ASN_STRU
 结构说明  : 上报TIN值的数据结构，ASN解析需4字节对齐
 修改历史      :
  1.日    期   : 2015年08月03日
    作    者   : wx270776
    修改内容   : 新建
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsId;
    NAS_LMM_GUTI_STRU                   stGuti;
    NAS_OM_PTMSI_STRU                   stPtmsi;
    VOS_UINT8                           aucImsi[NAS_MAX_IMSI_ASN_LEN];
}NAS_OM_MS_ID_ASN_STRU;

/*******************************************************************************
 结构名    : ID_NAS_OM_INQUIRE_ASN_STRU
 结构说明  : 上报TIN值的数据结构，ASN解析对应的结构体
 修改历史      :
  1.日    期   : 2015年08月03日
    作    者   : wx270776
    修改内容   : 新建
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;
    VOS_UINT8                           aucData[4];
}ID_NAS_OM_INQUIRE_ASN_STRU;

/*****************************************************************************
 结构名    : NAS_TIMER_EVENT_INFO_ASN_STRU
 结构说明  : 定时器事件信息
 1.日    期   : 2015年8月11日
   作    者   : wx270776
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulItems;
    VOS_UINT32                          aulTimerMsg[100];
}NAS_TIMER_EVENT_INFO_ASN_STRU;

/*****************************************************************************
 结构名    : NAS_OM_CONFIG_TIMER_REPORT_REQ_ASN_STRU
 结构说明  : OAM发给MMA的TIMER OTA上报事件 配置信息，ASN解析对应的结构体
 1.日    期   : 2015年7月14日
   作    者   : wx270776
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;
    VOS_UINT32                          ulCommand;
    NAS_TIMER_EVENT_INFO_ASN_STRU       stTimerMsg;
}NAS_OM_CONFIG_TIMER_REPORT_REQ_ASN_STRU;

/*****************************************************************************
 结构名    : NAS_OM_CONFIG_TIMER_REPORT_CNF_ASN_STRU
 结构说明  : MMC回复OM TIMER OTA上报事件 配置信息，ASN解析对应的结构体
 1.日    期   : 2015年7月14日
   作    者   : wx270776
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;
}NAS_OM_CONFIG_TIMER_REPORT_CNF_ASN_STRU;
/* Added by wx270776 for OM融合, 2015-8-8, end */

/*******************************************************************************
 结构名    : NAS_OM_SMS_CONFIRM_STRU
 结构说明  : 发给OM的MM信息的透传消息结构定义
 修改历史      :
  1.日    期   : 2013年06月26日
    作    者   : l00167671
    修改内容   : DCM LOGGER可谓可测SMC SMR状态上报

  2.日    期   : 2015年07月18日
    作    者   : wx270776
    修改内容   : OM融合
*******************************************************************************/
typedef struct
{
    /* Added by wx270776 for OM融合, 2015-7-18, begin */
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;                                /* 原语ID                                   */
    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;

    NAS_OM_RESULT_ENUM_UINT32           enResult;
}NAS_OM_SMS_CONFIRM_STRU;
    /* Added by wx270776 for OM融合, 2015-7-18, end */
typedef struct
{
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    /* Added by wx270776 for OM融合, 2015-7-18, begin */
    NAS_OM_TRANS_MSG_TYPE_ENUM_UINT16   enPrimId;
    VOS_UINT16                          usToolsId;
    /* Added by wx270776 for OM融合, 2015-7-18, end */
    NAS_OM_SMC_MO_STATE_ENUM_UINT8      enSmcCsMoState;
    NAS_OM_SMC_MT_STATE_ENUM_UINT8      enSmcCsMtState;
    NAS_OM_SMC_MO_STATE_ENUM_UINT8      enSmcPsMoState;
    NAS_OM_SMC_MT_STATE_ENUM_UINT8      enSmcPsMtState;
    NAS_OM_SMR_STATE_ENUM_UINT8         enSmrMoState;
    NAS_OM_SMR_STATE_ENUM_UINT8         enSmrMtState;
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */
    VOS_UINT8                           aucReserved[2];
}NAS_OM_SMS_IND_STRU;


/* Added by wx270776 for OM融合, 2015-7-22, begin */
typedef struct
{
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    NAS_OM_SMC_MO_STATE_ENUM_UINT8      enSmcCsMoState;
    NAS_OM_SMC_MT_STATE_ENUM_UINT8      enSmcCsMtState;
    NAS_OM_SMC_MO_STATE_ENUM_UINT8      enSmcPsMoState;
    NAS_OM_SMC_MT_STATE_ENUM_UINT8      enSmcPsMtState;
    NAS_OM_SMR_STATE_ENUM_UINT8         enSmrMoState;
    NAS_OM_SMR_STATE_ENUM_UINT8         enSmrMtState;
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end*/
    VOS_UINT8                           aucReserved[2];
}NAS_OM_SMS_IND_ASN_STRU;
/* Added by wx270776 for OM融合, 2015-7-22, end */


/*****************************************************************************
 枚举名    : NAS_OM_PLMN_HUO_TYPE_ENUM
 枚举说明  : DCM要求在工具中显示PLMN的类型
 1.日    期   : 2013年06月23日
   作    者   : l00167671
   修改内容   : 新建
 2.日    期   : 2013年09月3日
   作    者   : w00242748
   修改内容   : DTS2013082909799 查询NAS MM QUERY时，RPLMN显示成EHPLMN，关机时
                无效PLMN显示为OPLMN修正。
*****************************************************************************/
enum NAS_OM_PLMN_HUO_TYPE_ENUM
{
   NAS_MMC_HUO_RPLMN        = 0x1,
   NAS_MMC_HUO_HPLMN        = 0x2,
   NAS_MMC_HUO_UPLMN        = 0x3,
   NAS_MMC_HUO_OPLMN        = 0x4,
   NAS_MMC_HUO_OTHER_PLMN   = 0x5,
   NAS_MMC_HUO_INVALID_PLMN = 0x6,
   NAS_MMC_HUO_BUTT
};
typedef VOS_UINT32 NAS_OM_PLMN_HUO_TYPE_ENUM_UINT32;

/* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, end */

/*******************************************************************************
 结构名    : NAS_OM_MM_CONFIRM_STRU
 结构说明  : 发给OM的MM信息的透传消息结构定义
 修改历史      :
  1.日    期   : 2012年04月27日
    作    者   : l00171473
    修改内容   :

  2.日    期   : 2012年11月06日
    作    者   : l00198894
    修改内容   : Probe路测工具对接项目增加GPRS状态

  3.日    期   : 2015年07月18日
    作    者   : wx270776
    修改内容   : OM融合
*******************************************************************************/
typedef struct
{
    /* Added by wx270776 for OM融合, 2015-7-18, begin */
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;                                /* 原语ID                                   */
    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;

    NAS_OM_RESULT_ENUM_UINT32           enResult;
    /* Added by wx270776 for OM融合, 2015-7-18, end */
}NAS_OM_MM_CONFIRM_STRU;


typedef struct
{
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    NAS_OM_TRANS_MSG_TYPE_ENUM_UINT16   enPrimId;
    VOS_UINT16                          usToolsId;

    NAS_OM_MM_STATE_ENUM_UINT8          enMmState;
    MM_UPDATE_STATUS_ENUM_UINT8         enMmUpdateStatus;
    VOS_UINT8                           aucTmsi[LEN_TMSI];
    NAS_OM_GMM_STATE_ENUM_UINT8         enGmmState;
    GMM_UPDATE_STATUS_ENUM_UINT8        enGmmUpdateStatus;

    VOS_UINT8                           ucPtmsi[LEN_PTMSI];
    NAS_OM_FSM_ID_ENUM_UINT8            enMmcFsmId;
    PLMN_SEL_MODE_ENUM_UINT8            enPlmnSelMode;
    UE_OPERATE_MODE_ENUM_UINT8          enUeOperMode;
    NET_OPERATE_MODE_ENUM_UINT8         enNetMode;

    MS_ID_STRUCT                        IMSI;
    MS_ID_STRUCT                        IMEI;
    MS_ID_STRUCT                        IMEISV;
    PLMN_ID_STRUCT                      SelectedPlmn;

    VOS_UINT16                          usLac;
    VOS_UINT8                           ucRac;
    VOS_UINT8                           ucAvailPlmnNum;

    AVAILABLE_PLMN_STRUCT               AvailablePlmn[MAX_AVAILABEL_PLMN_NUM];

    NAS_OM_MM_SUB_STATE_ENUM_UINT8      enMmSubState;
    NAS_OM_GMM_SUB_STATE_ENUM_UINT8     enGmmSubState;
    NAS_OM_SERVICE_STATE_ENUM_UINT8     enServiceStatus;
    VOS_UINT8                           ucMmcState;

    NAS_OM_GMM_GPRS_STATE_ENUM_UINT8    enGmmGprsState;

    VOS_UINT8                           aucReserved[2];


    NAS_OM_TIN_TYPE_ENUM_UINT8          enTinType;
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */
    NAS_OM_PLMN_HUO_TYPE_ENUM_UINT32    enPlmnType;
    NAS_OM_MS_ID_STRU                   stMsId;
}NAS_OM_MM_IND_STRU;

/* Added by wx270776 for OM融合, 2015-7-22, begin */
typedef struct
{
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    NAS_OM_MM_STATE_ENUM_UINT8          enMmState;
    MM_UPDATE_STATUS_ENUM_UINT8         enMmUpdateStatus;
    VOS_UINT8                           aucTmsi[LEN_TMSI];
    NAS_OM_GMM_STATE_ENUM_UINT8         enGmmState;
    GMM_UPDATE_STATUS_ENUM_UINT8        enGmmUpdateStatus;

    VOS_UINT8                           ucPtmsi[LEN_PTMSI];
    NAS_OM_FSM_ID_ENUM_UINT8            enMmcFsmId;
    PLMN_SEL_MODE_ENUM_UINT8            enPlmnSelMode;
    UE_OPERATE_MODE_ENUM_UINT8          enUeOperMode;
    NET_OPERATE_MODE_ENUM_UINT8         enNetMode;

    MS_ID_STRUCT                        IMSI;
    MS_ID_STRUCT                        IMEI;
    MS_ID_STRUCT                        IMEISV;
    PLMN_ID_STRUCT                      SelectedPlmn;

    VOS_UINT16                          usLac;
    VOS_UINT8                           ucRac;
    VOS_UINT8                           ucAvailPlmnNum;

    AVAILABLE_PLMN_STRUCT               AvailablePlmn[MAX_AVAILABEL_PLMN_NUM];

    NAS_OM_MM_SUB_STATE_ENUM_UINT8      enMmSubState;
    NAS_OM_GMM_SUB_STATE_ENUM_UINT8     enGmmSubState;
    NAS_OM_SERVICE_STATE_ENUM_UINT8     enServiceStatus;
    VOS_UINT8                           enMmcState;

    NAS_OM_GMM_GPRS_STATE_ENUM_UINT8    enGmmGprsState;

    VOS_UINT8                           aucReserved[2];


    NAS_OM_TIN_TYPE_ENUM_UINT8          enTinType;
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */
    NAS_OM_PLMN_HUO_TYPE_ENUM_UINT32    enPlmnType;
    NAS_OM_MS_ID_ASN_STRU               stMsId;
}NAS_OM_MM_IND_ASN_STRU;
/* Added by wx270776 for OM融合, 2015-7-22, end */

/*******************************************************************************
 结构名    : NAS_QOS_STRUCT
 结构说明  : 发给OM的QOS信息的透传消息结构定义
 修改历史      :
  1.日    期   : 2012年04月27日
    作    者   : l00171473
    修改内容   :
  2.日    期   : 2015年07月18日
    作    者   : wx270776
    修改内容   : OM融合
*******************************************************************************/
typedef struct
{
    /* Added by wx270776 for OM融合, 2015-7-18, begin */
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;                                /* 原语ID                                   */
    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;

    NAS_OM_RESULT_ENUM_UINT32           enResult;
    /* Added by wx270776 for OM融合, 2015-7-18, end */
}NAS_QOS_STRUCT;

typedef struct
{
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    /* Added by wx270776 for OM融合, 2015-7-18, begin */
    NAS_OM_TRANS_MSG_TYPE_ENUM_UINT16   enPrimId;
    VOS_UINT16                          usToolsId;
    /* Added by wx270776 for OM融合, 2015-7-18, end */
    VOS_UINT8                           ucNSAPI;
    NAS_OM_DELAY_CLASS_ENUM_UINT8       enDelayClass;
    NAS_OM_RELIABILITY_CLASS_ENUM_UINT8 enReliabilityClass;
    NAS_OM_PEAK_THROUGH_PUT_ENUM_UINT8  enPeakThrough;
    NAS_OM_PRECEDENCE_CLASS_ENUM_UINT8  enPrecedenceClass;
    NAS_OM_MEAN_THROUGH_ENUM_UINT8      enMeanThrough;
    NAS_OM_TRAFFIC_CLASS_ENUM_UINT8     enTrafficClass;
    NAS_OM_DELIVERY_ORDER_ENUM_UINT8    enDeliverOrder;
    NAS_OM_DELIVERY_ERR_SDU_ENUM_UINT8  enDeliverOfErrSdu;
    VOS_UINT8                           ucReserved1[1];
    VOS_UINT16                          usMaximSduSize;
    VOS_UINT32                          ulMaxBitRateUl;
    VOS_UINT32                          ulMaxBitRateDl;
    NAS_OM_RESIDUAL_BER_ENUM_UINT8      enResidualBer;
    NAS_OM_SDU_ERROR_RATIO_ENUM_UINT8   enSduErrRatio;
    VOS_UINT16                          usTransDelay;
    NAS_OM_TRAFF_HAND_PRIO_ENUM_UINT8   enTraffHandlPrior;
    VOS_UINT8                           ucReserved2[3];
    VOS_UINT32                          ulGuarantBitRateUl;
    VOS_UINT32                          ulGuarantBitRateDl;
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */
}NAS_QOS_IND_STRUCT;

/* Added by wx270776 for OM融合, 2015-7-22, begin */
/* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
typedef struct
{
    VOS_UINT8                           ucNSAPI;
    NAS_OM_DELAY_CLASS_ENUM_UINT8       enDelayClass;
    NAS_OM_RELIABILITY_CLASS_ENUM_UINT8 enReliabilityClass;
    NAS_OM_PEAK_THROUGH_PUT_ENUM_UINT8  enPeakThrough;
    NAS_OM_PRECEDENCE_CLASS_ENUM_UINT8  enPrecedenceClass;
    NAS_OM_MEAN_THROUGH_ENUM_UINT8      enMeanThrough;
    NAS_OM_TRAFFIC_CLASS_ENUM_UINT8     enTrafficClass;
    NAS_OM_DELIVERY_ORDER_ENUM_UINT8    enDeliverOrder;
    NAS_OM_DELIVERY_ERR_SDU_ENUM_UINT8  enDeliverOfErrSdu;
    VOS_UINT8                           ucReserved1[1];
    VOS_UINT16                          usMaximSduSize;
    VOS_UINT32                          ulMaxBitRateUl;
    VOS_UINT32                          ulMaxBitRateDl;
    NAS_OM_RESIDUAL_BER_ENUM_UINT8      enResidualBer;
    NAS_OM_SDU_ERROR_RATIO_ENUM_UINT8   enSduErrRatio;
    VOS_UINT16                          usTransDelay;
    NAS_OM_TRAFF_HAND_PRIO_ENUM_UINT8   enTraffHandlPrior;
    VOS_UINT8                           ucReserved2[3];
    VOS_UINT32                          ulGuarantBitRateUl;
    VOS_UINT32                          ulGuarantBitRateDl;
}NAS_QOS_IND_ASN_STRUCT;
/* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */
/* Added by wx270776 for OM融合, 2015-7-22, end */

/*******************************************************************************
 结构名    : NAS_PDP_CONTEXT_STRU
 结构说明  : PDP上下文信息的结构定义
 修改历史      :
  1.日    期   : 2012年04月27日
    作    者   : l00171473
    修改内容   :
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNsapi;
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    NAS_OM_APS_ADDR_ENUM_UINT8          enPdpType;
    VOS_UINT8                           aucReserved1[2];
    NAS_OM_SM_PDP_STATE_ENUM_UINT8      enActivePDPContexts;
    VOS_UINT8                           ucPdpLlcSapi;
    VOS_UINT8                           ucPdpRadioPriority;
    VOS_UINT8                           aucReserved2[1];
    VOS_UINT8                           ucApnLength;
    VOS_UINT8                           aucApn[SM_MAX_LENGTH_OF_APN];
    VOS_UINT8                           aucReserved3[2];
    VOS_UINT8                           aucIpAddr[SM_IP_ADDR_LEN];
    NAS_OM_PDP_ACT_TYPE_ENUM_UINT8      enActType;                              /*激活类型*/
    VOS_UINT8                           ucLinkedNsapi;                          /*主激活的NSAPI,若激活类型是二次激活,则此成员有效*/
    VOS_UINT8                           aucReserved4[2];
    VOS_UINT8                           aucIpv6Addr[SM_IPV6_ADDR_LEN];
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */
}NAS_PDP_CONTEXT_STRU;

/*******************************************************************************
 结构名    : NAS_OM_PDP_CONTEXT_STRU
 结构说明  : 发给OM的激活的PDP上下文信息的透传消息结构定义
 修改历史      :
  1.日    期   : 2012年04月27日
    作    者   : l00171473
    修改内容   :
  2.日    期   : 2015年07月18日
    作    者   : wx270776
    修改内容   : OM融合
*******************************************************************************/
typedef struct
{
    /* Added by wx270776 for OM融合, 2015-7-18, begin */
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;                                /* 原语ID                                   */
    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;

    NAS_OM_RESULT_ENUM_UINT32           enResult;
    /* Added by wx270776 for OM融合, 2015-7-18, end */
}NAS_OM_PDP_CONTEXT_STRU;

typedef struct
{
    /* Added by wx270776 for OM融合, 2015-7-18, begin */
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    NAS_OM_TRANS_MSG_TYPE_ENUM_UINT16   enPrimId;
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */
    VOS_UINT16                          usToolsId;
    /* Added by wx270776 for OM融合, 2015-7-18, end */
    VOS_UINT32                          ulPdpCnt;                               /* 实际激活的PDP上下文个数 */
    NAS_PDP_CONTEXT_STRU                astPdpContext[NAS_OM_PDP_CONTEXT_MAX];
}NAS_OM_PDP_CONTEXT_IND_STRU;


/* Added by wx270776 for OM融合, 2015-7-22, begin */
typedef struct
{
    VOS_UINT32                          ulPdpCnt;                               /* 实际激活的PDP上下文个数 */
    NAS_PDP_CONTEXT_STRU                astPdpContext[NAS_OM_PDP_CONTEXT_MAX];
}NAS_OM_PDP_CONTEXT_IND_ASN_STRU;
/* Added by wx270776 for OM融合, 2015-7-22, end */

/*******************************************************************************
 结构名    : NAS_OM_SET_GSM_CODEC_CONFIG_REQ_STRU
 结构说明  : 从OM收到的CODEC设置请求
 修改历史      :
  1.日    期   : 2012年04月27日
    作    者   : l00171473
    修改内容   :
  2.日    期   : 2015年07月18日
    作    者   : wx270776
    修改内容   : OM融合
*******************************************************************************/
typedef struct
{
    /* Added by wx270776 for OM融合, 2015-7-18, begin */
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;
    /* Added by wx270776 for OM融合, 2015-7-18, end */

    NAS_OM_GSM_CODEC_CONFIG_ENUM_U8     enGsmCodec;
    VOS_UINT8                           aucReserve[3];
}NAS_OM_SET_GSM_CODEC_CONFIG_REQ_STRU;

/*******************************************************************************
 结构名    : NAS_OM_SET_GSM_CODEC_CONFIG_CNF_STRU
 结构说明  : 发给OM的CODEC设置结果的透传消息结构定义
 修改历史      :
  1.日    期   : 2012年04月27日
    作    者   : l00171473
    修改内容   :
  2.日    期   : 2015年07月18日
    作    者   : wx270776
    修改内容   : OM融合
*******************************************************************************/
typedef struct
{
    /* Added by wx270776 for OM融合, 2015-7-18, begin */
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;
    /* Added by wx270776 for OM融合, 2015-7-18, end */

    VOS_UINT32                          ulRet;                                  /* 设置结果 */
}NAS_OM_SET_GSM_CODEC_CONFIG_CNF_STRU;

/*******************************************************************************
 结构名    : NAS_OM_CODEC_TYPE_STRU
 结构说明  : 发给OM的当前CODEC信息的透传消息结构定义
 修改历史      :
  1.日    期   : 2012年04月27日
    作    者   : l00171473
    修改内容   :
  2.日    期   : 2015年07月18日
    作    者   : wx270776
    修改内容   : OM融合
*******************************************************************************/
typedef struct
{
    /* Added by wx270776 for OM融合, 2015-7-18, begin */
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;
    /* Added by wx270776 for OM融合, 2015-7-18, end */

    NAS_OM_CURR_CODEC_TYPE_ENUM_U8      enCurrCodec;                            /* 当前使用的CODEC类型 */
    NAS_OM_GSM_CODEC_CONFIG_ENUM_U8     enGsmCodecConfig;                       /* 当前GSM支持的CODEC类型 */
    VOS_UINT8                           aucReserve[2];
}NAS_OM_CODEC_TYPE_CNF_STRU;

/*******************************************************************************
 结构名    : NAS_OM_SET_DSFLOW_RPT_REQ_STRU
 结构说明  : 从OM收到的数据业务流量、速率上报设置请求
 修改历史      :
  1.日    期   : 2012年11月06日
    作    者   : l00198894
    修改内容   : Probe路测工具对接项目新增结构体
  2.日    期   : 2015年07月18日
    作    者   : wx270776
    修改内容   : OM融合
*******************************************************************************/
typedef struct
{
    /* Added by wx270776 for OM融合, 2015-7-18, begin */
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;
    /* Added by wx270776 for OM融合, 2015-7-18, end */

    NAS_OM_REPORT_ACTION_ENUM_UINT8     enRptAction;
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usRptPeriod;
}NAS_OM_SET_DSFLOW_RPT_REQ_STRU;

/*******************************************************************************
 结构名    : NAS_OM_SET_DSFLOW_RPT_CNF_STRU
 结构说明  : 发给OM数据业务流量、速率上报设置结果的透传消息结构定义
 修改历史      :
  1.日    期   : 2012年11月06日
    作    者   : l00198894
    修改内容   : Probe路测工具对接项目新增结构体
  2.日    期   : 2015年07月18日
    作    者   : wx270776
    修改内容   : OM融合
*******************************************************************************/
typedef struct
{
    /* Added by wx270776 for OM融合, 2015-7-18, begin */
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;
    /* Added by wx270776 for OM融合, 2015-7-18, end */

    NAS_OM_RESULT_ENUM_UINT32           enResult;                               /* 设置结果 */
}NAS_OM_SET_DSFLOW_RPT_CNF_STRU;

/*******************************************************************************
 结构名    : NAS_OM_DSFLOW_RPT_IND_STRU
 结构说明  : 发给OM的数据业务流量、速率等信息的透传消息结构定义
 修改历史      :
  1.日    期   : 2012年11月06日
    作    者   : l00198894
    修改内容   : Probe路测工具对接项目新增结构体

  2.日    期   : 2015年07月18日
    作    者   : wx270776
    修改内容   : OM融合
*******************************************************************************/
typedef struct
{
    /* Added by wx270776 for OM融合, 2015-7-18, begin */
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usToolsId;
    /* Added by wx270776 for OM融合, 2015-7-18, end */
    VOS_UINT32                          ulCurrentSendRate;                      /* 当前发送速率 */
    VOS_UINT32                          ulCurrentReceiveRate;                   /* 当前接收速率 */
    VOS_UINT32                          ulDSLinkTime;                           /* DS连接时间  */
    VOS_UINT32                          ulDSSendFluxLow;                        /* DS发送流量低四个字节 */
    VOS_UINT32                          ulDSSendFluxHigh;                       /* DS发送流量高四个字节 */
    VOS_UINT32                          ulDSReceiveFluxLow;                     /* DS接收流量低四个字节 */
    VOS_UINT32                          ulDSReceiveFluxHigh;                    /* DS接收流量高四个字节 */
}NAS_OM_DSFLOW_RPT_IND_STRU;


/* Added by wx270776 for OM融合, 2015-7-22, begin */
typedef struct
{
    VOS_UINT32                          ulCurrentSendRate;                      /* 当前发送速率 */
    VOS_UINT32                          ulCurrentReceiveRate;                   /* 当前接收速率 */
    VOS_UINT32                          ulDSLinkTime;                           /* DS连接时间  */
    VOS_UINT32                          ulDSSendFluxLow;                        /* DS发送流量低四个字节 */
    VOS_UINT32                          ulDSSendFluxHigh;                       /* DS发送流量高四个字节 */
    VOS_UINT32                          ulDSReceiveFluxLow;                     /* DS接收流量低四个字节 */
    VOS_UINT32                          ulDSReceiveFluxHigh;                    /* DS接收流量高四个字节 */
}NAS_OM_DSFLOW_RPT_IND_ASN_STRU;
/* Added by wx270776 for OM融合, 2015-7-22, end */


/* Added by wx270776 for OM融合, 2015-7-18, begin */
/*******************************************************************************
 结构名    : NAS_AIR_MSG_STRU
 结构说明  :
 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : wx270776
    修改内容   : OM融合
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usMsgId;
    VOS_UINT8                           ucUpDown;
    VOS_UINT8                           ucReserve;
    VOS_UINT32                          ulLengthASN;
    VOS_UINT8                           aucNasMsg[4];       /* 消息的前四个字节内容 */
}NAS_AIR_MSG_STRU;
/* Added by wx270776 for OM融合, 2015-7-18, end */

/*****************************************************************************
 结构名    : NAS_OM_MMA_1X_SYS_INFO_STRU
 结构说明  : 当前驻留的1X网络的域信息
 1.日    期   : 2015年7月9日
   作    者   : Y00322978
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usBandClass;
    VOS_UINT16                          usFreq;
    VOS_INT32                           lSid;             /**<  System identification */
    VOS_INT32                           lNid;             /**<  Network identification */
    VOS_UINT32                          ulMcc;                 /**<  Mobile country code */
    VOS_UINT16                          usMnc;                 /**<  Mobile network code */
    VOS_UINT16                          usBaseId;        /**<  Base station identification */
    NAS_OM_1X_CALL_STATE_ENUM_UINT8     en1xCallState;
    VOS_UINT8                           ucReserved[3];
}NAS_OM_MMA_1X_SYS_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_OM_MMA_CDMA_STATUS_COMMON_INFO_STRU
 结构说明  : 当前驻留的1X网络的域信息
 1.日    期   : 2015年7月9日
   作    者   : Y00322978
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_OM_MMA_PHONE_MODE_ENUM_UINT8    enPhoneMode;
    NAS_OM_MMA_SYS_MODE_ENUM_UINT8      enSysMode;
    MODEM_ID_ASN_ENUM_UINT16            enModemId;                          /*_H2ASN_MsgChoice_Export MODEM_ID_ASN_ENUM_UINT16*/
    NAS_OM_MMA_PPP_STATUS_ENUM_UINT8    enPppStatus;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulEsn;                              /* 32-bit */
    VOS_UINT32                          ulMeid;                             /* meid 高8位 */
    VOS_UINT32                          ulMeidCnt;                          /* meid低八位 */
    VOS_UINT32                          ulImsiHigh;
    VOS_UINT32                          ulImsiLow;
    VOS_UINT32                          ulRuimidHigh;
    VOS_UINT32                          ulRuimidLow;

}NAS_OM_MMA_CDMA_STATUS_COMMON_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_OM_MMA_HRPD_SYS_INFO_STRU
 结构说明  : 当前驻留的HRPD网络的域信息
 1.日    期   : 2015年5月15日
   作    者   : y00322978
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usBandClass;
    VOS_UINT16                                              usChannel;
    VOS_UINT32                                              ulMcc;                   /**<  Mobile country code */
    VOS_UINT8                                               ucColorCode;
    VOS_UINT8                                               ucSubNetMask;
    NAS_OM_MMA_HRPD_SESSION_STATUS_ENUM_UINT8               enSessionStatus;
    NAS_OM_MMA_SYS_SUBMODE_ENUM_UINT8                       enSysSubMode;
    VOS_UINT32                                              ulSessionSeed;          /*RATI*/
    VOS_UINT32                                              ulCurUATI1;             /*UATI 128bit 拆为4个32bit整数*/
    VOS_UINT32                                              ulCurUATI2;
    VOS_UINT32                                              ulCurUATI3;
    VOS_UINT32                                              ulCurUATI4;
    VOS_UINT32                                              ulSector24;
}NAS_OM_MMA_HRPD_SYS_INFO_STRU;

/*****************************************************************************
结构名    : OM_NAS_MMA_CDMA_STATUS_INFO_REPORT_REQ_STRU
结构说明  : om查询当前CDMA状态信息的请求消息结构体

  1.日    期   : 2015年05月16日
    作    者   : y00322978
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /*_H2ASN_Skip*/
    VOS_UINT32                                      ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT16                                      usOriginalId;
    VOS_UINT16                                      usTerminalId;
    VOS_UINT32                                      ulTimeStamp;
    VOS_UINT32                                      ulSn;

    OM_NAS_MMA_CDMA_STATUS_REPORT_CMD_ENUM_UINT8    enCmd;
    VOS_UINT8                                       aucRsv[3];
    VOS_UINT32                                      ulRptPeriod;
}OM_NAS_MMA_CDMA_STATUS_INFO_REPORT_REQ_STRU;

/*****************************************************************************
结构名    : OM_NAS_MMA_CDMA_STATUS_INFO_REPORT_REQ_ASN_STRU
结构说明  : om查询当前CDMA状态信息的请求消息结构体

  1.日    期   : 2015年05月16日
    作    者   : y00322978
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_UINT16                                      usOriginalId;
    VOS_UINT16                                      usTerminalId;
    VOS_UINT32                                      ulTimeStamp;
    VOS_UINT32                                      ulSn;

    OM_NAS_MMA_CDMA_STATUS_REPORT_CMD_ENUM_UINT8    enCmd;
    VOS_UINT8                                       aucRsv[3];
    VOS_UINT32                                      ulRptPeriod;
}OM_NAS_MMA_CDMA_STATUS_INFO_REPORT_REQ_ASN_STRU;
/*****************************************************************************
结构名    : NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_CNF_STRU
结构说明  : om查询当前CDMA状态信息的回复消息结构体

  1.日    期   : 2015年05月16日
    作    者   : y00322978
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /*_H2ASN_Skip*/
    VOS_UINT32                                          ulMsgId;        /*_H2ASN_Skip*/

    VOS_UINT16                                          usOriginalId;
    VOS_UINT16                                          usTerminalId;
    VOS_UINT32                                          ulTimeStamp;
    VOS_UINT32                                          ulSn;

    NAS_OM_MMA_CDMA_STATUS_REPORT_RESRLT_ENUM_UINT32    enResult;
}NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_CNF_STRU;

/*****************************************************************************
结构名    : NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_CNF_ASN_STRU
结构说明  : om查询当前CDMA状态信息的回复消息结构体

  1.日    期   : 2015年05月16日
    作    者   : y00322978
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_UINT16                                          usOriginalId;
    VOS_UINT16                                          usTerminalId;
    VOS_UINT32                                          ulTimeStamp;
    VOS_UINT32                                          ulSn;

    NAS_OM_MMA_CDMA_STATUS_REPORT_RESRLT_ENUM_UINT32    enResult;
}NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_CNF_ASN_STRU;
/*****************************************************************************
结构名    : NAS_OM_MMA_OM_CDMA_STATUS_INFO_REPORT_IND_STRU
结构说明  : 当前CDMA状态信息主动上报om结构体

  1.日    期   : 2015年05月16日
    作    者   : y00322978
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_UINT16                                          usPrimId;       /*_H2ASN_Skip*/
    VOS_UINT16                                          usToolsId;      /* 工具ID */

    NAS_OM_MMA_CDMA_STATUS_COMMON_INFO_STRU             stCdmaCommInfo;
    NAS_OM_MMA_1X_SYS_INFO_STRU                         st1xSysInfo;
    NAS_OM_MMA_HRPD_SYS_INFO_STRU                       stHrpdSysInfo;

}NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_IND_STRU;
/*****************************************************************************
结构名    : NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_IND_ASN_STRU
结构说明  : ASN解析使用

  1.日    期   : 2015年05月16日
    作    者   : y00322978
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    NAS_OM_MMA_CDMA_STATUS_COMMON_INFO_STRU             stCdmaCommInfo;
    NAS_OM_MMA_1X_SYS_INFO_STRU                         st1xSysInfo;
    NAS_OM_MMA_HRPD_SYS_INFO_STRU                       stHrpdSysInfo;

}NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_IND_ASN_STRU;





/*****************************************************************************
结构名    : OM_NAS_CDMA_REG_INFO_REPORT_REQ_STRU
结构说明  : OM查询当前CDMA REG状态信息的请求消息结构体

  1.日    期   : 2015年10月20日
    作    者   : g00256031
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /*_H2ASN_Skip*/
    VOS_UINT32                                      ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT16                                      usOriginalId;
    VOS_UINT16                                      usTerminalId;
    VOS_UINT32                                      ulTimeStamp;
    VOS_UINT32                                      ulSn;

    NAS_OM_REPORT_ACTION_ENUM_UINT8                 enReportType;
    VOS_UINT8                                       aucRsv[3];
}OM_NAS_CDMA_REG_INFO_REPORT_REQ_STRU;

/*****************************************************************************
结构名    : NAS_OM_CDMA_REG_INFO_REPORT_CNF_STRU
结构说明  : OM查询当前CDMA REG状态信息的回复消息结构体

  1.日    期   : 2015年10月20日
    作    者   : g00256031
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /*_H2ASN_Skip*/
    VOS_UINT32                                          ulMsgId;        /*_H2ASN_Skip*/

    VOS_UINT16                                          usOriginalId;
    VOS_UINT16                                          usTerminalId;
    VOS_UINT32                                          ulTimeStamp;
    VOS_UINT32                                          ulSn;

    NAS_OM_RESULT_ENUM_UINT32                           enResult;
}NAS_OM_CDMA_REG_INFO_REPORT_CNF_STRU;

/*****************************************************************************
结构名    : NAS_OM_CDMA_REG_PRD_REPORT_IND_STRU
结构说明  : 上报当前的周期性注册时长

  1.日    期   : 2015年10月20日
    作    者   : g00256031
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_UINT16                                          usPrimId;       /*_H2ASN_Skip*/
    VOS_UINT16                                          usToolsId;      /* 工具ID */

    VOS_UINT32                                          ulRegPrd;       /* 注册周期，以秒为单位 */
}NAS_OM_CDMA_REG_PRD_REPORT_IND_STRU;

/*****************************************************************************
结构名    : NAS_OM_CDMA_REG_TYPE_REPORT_IND_STRU
结构说明  : 当前CDMA REG类型上报消息结构体

1.日    期   : 2015年10月20日
  作    者   : g00256031
  修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_UINT16                                          usPrimId;       /*_H2ASN_Skip*/
    VOS_UINT16                                          usToolsId;      /* 工具ID */

    NAS_OM_CDMA_REG_TYPE_ENUM_UINT32                    enRegType;      /* 注册类型 */
}NAS_OM_CDMA_REG_TYPE_REPORT_IND_STRU;

/*****************************************************************************
结构名    : NAS_OM_CDMA_ZONE_NODE_STRU
结构说明  : 保存ZONE_LIST节点信息

  1.日    期   : 2015年10月20日
    作    者   : g00256031
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_UINT16                                          usRegZone;
    VOS_UINT16                                          usRsv;
    VOS_UINT16                                          usSid;
    VOS_UINT16                                          usNid;
    NAS_OM_CDMA_BLKSYS_ENUM_UINT8                       enBlkSys;
    VOS_UINT8                                           ucRsv1;
    VOS_UINT16                                          usBandClass;
}NAS_OM_CDMA_ZONE_NODE_STRU;

/*****************************************************************************
结构名    : NAS_OM_CDMA_SIDNID_NODE_STRU
结构说明  : 保存SID_NID_LIST节点信息

  1.日    期   : 2015年10月20日
    作    者   : g00256031
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_UINT16                                          usSid;
    VOS_UINT16                                          usNid;
    NAS_OM_CDMA_BLKSYS_ENUM_UINT8                       enBlkSys;
    VOS_UINT8                                           ucRsv;
    VOS_UINT16                                          usBandClass;
}NAS_OM_CDMA_SIDNID_NODE_STRU;

/*****************************************************************************
结构名    : NAS_OM_CDMA_REG_LIST_REPORT_IND_STRU
结构说明  : 返回当前的SID_NID_LIST和ZONE_LIST

  1.日    期   : 2015年10月20日
    作    者   : g00256031
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_UINT16                                          usPrimId;       /*_H2ASN_Skip*/
    VOS_UINT16                                          usToolsId;      /* 工具ID */

    NAS_OM_CDMA_ZONE_NODE_STRU                          astZoneList[NAS_OM_CDMA_ZONE_NODE_MAX_NUM];
    NAS_OM_CDMA_SIDNID_NODE_STRU                        astSidNidList[NAS_OM_CDMA_SIDNID_NODE_MAX_NUM];
}NAS_OM_CDMA_REG_LIST_REPORT_IND_STRU;


/*****************************************************************************
结构名    : OM_NAS_CDMA_START_GPS_FIX_REQ_STRU
结构说明  : OM发起GPS定位请求

  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /*_H2ASN_Skip*/
    VOS_UINT32                                              ulMsgId;    /*_H2ASN_Skip*/

    VOS_UINT16                                              usOriginalId;
    VOS_UINT16                                              usTerminalId;
    VOS_UINT32                                              ulTimeStamp;
    VOS_UINT32                                              ulSn;

    NAS_OM_CDMA_GPS_FIX_MODE_ENUM_UINT8                     enFixMode;
    NAS_OM_CDMA_GPS_START_MODE_ENUM_UINT8                   enStartMode;
    VOS_UINT8                                               aucRsv[2];
}OM_NAS_CDMA_START_GPS_FIX_REQ_STRU;

/*****************************************************************************
结构名    : NAS_OM_CDMA_START_GPS_FIX_CNF_STRU
结构说明  :

  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSn;
}NAS_OM_CDMA_START_GPS_FIX_CNF_STRU;

/*****************************************************************************
结构名    : OM_NAS_CDMA_STOP_GPS_FIX_REQ_STRU
结构说明  : OM停止GPS定位请求

  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSn;
}OM_NAS_CDMA_STOP_GPS_FIX_REQ_STRU;

/*****************************************************************************
结构名    : NAS_OM_CDMA_STOP_GPS_FIX_CNF_STRU
结构说明  :

  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSn;
}NAS_OM_CDMA_STOP_GPS_FIX_CNF_STRU;

typedef struct
{
    VOS_UINT16                          usYear;
    VOS_UINT16                          usMonth;
    VOS_UINT16                          usDayOfWeek;
    VOS_UINT16                          usDay;
    VOS_UINT16                          usHour;
    VOS_UINT16                          usMinute;
    VOS_UINT16                          usSecond;
    VOS_UINT16                          usMilliseconds;
    VOS_UINT32                          ulGpsWeek;
    VOS_UINT32                          ulGpsTimeOfWeek;
}NAS_OM_CDMA_GPS_UTC_TIME_STRU;

/*****************************************************************************
结构名    : NAS_OM_CDMA_GPS_POS_INFO_STRU
结构说明  :

  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    NAS_OM_CDMA_GPS_UTC_TIME_STRU                           stUtcTime;
    VOS_INT32                                               lLatitude;
    VOS_INT32                                               lLongitude;
    VOS_UINT32                                              ulHeading;
    VOS_UINT32                                              ulSpeed;
    NAS_OM_CDMA_GPS_FIX_TYPE_ENUM_UINT8                     enFixType;
    VOS_UINT8                                               aucRsv[3];
    VOS_UINT32                                              ulHDOP;
    VOS_UINT32                                              ulPDOP;
    VOS_UINT32                                              ulVDOP;
    VOS_UINT32                                              ulSeaLevelAltitude;
    VOS_UINT32                                              ulEllipsoidAltitude;
    VOS_UINT32                                              ulMagneticVariation;
}NAS_OM_CDMA_GPS_POS_INFO_STRU;

/*****************************************************************************
结构名    : NAS_OM_CDMA_GPS_FIX_RSLT_IND_STRU
结构说明  : NAS发送定位结果到OM

  1.日    期   : 2015年12月18日
    作    者   : y00174758
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_UINT16                                              usPrimId;       /*_H2ASN_Skip*/
    VOS_UINT16                                              usToolsId;      /* 工具ID */

    NAS_OM_CDMA_GPS_FIX_RSLT_ENUM_UINT8                     enRslt;
    VOS_UINT8                                               aucRsv[3];
    NAS_OM_CDMA_GPS_POS_INFO_STRU                           stPosInfo;
}NAS_OM_CDMA_GPS_FIX_RSLT_IND_STRU;

/*****************************************************************************
结构名    : NAS_OM_CDMA_GPS_FIX_RSLT_IND_STRU
结构说明  :

  1.日    期   : 2015年12月18日
    作    者   : y00174758
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_UINT16                                              usPrimId;       /*_H2ASN_Skip*/
    VOS_UINT16                                              usToolsId;      /* 工具ID */

    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_ENUM_UINT8              enMsgType;
    VOS_UINT8                                               aucRsv[3];
}NAS_OM_CDMA_GPS_SIGNAL_MSG_IND_STRU;

/*****************************************************************************
结构名    : NAS_OM_CDMA_GPS_FIX_START_IND_STRU
结构说明  :

  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_UINT16                                              usPrimId;       /*_H2ASN_Skip*/
    VOS_UINT16                                              usToolsId;      /* 工具ID */
}NAS_OM_CDMA_GPS_FIX_START_IND_STRU;


/*******************************************************************************
 结构名    : NasOmTrans_MSG
 结构说明  : NAS和OM间TRANS顶级消息定义
 修改历史      :
  1.日    期   : 2012年04月27日
    作    者   : l00171473
    修改内容   :
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimId;                               /*_H2ASN_MsgChoice_Export NAS_OM_TRANS_MSG_TYPE_ENUM_UINT16 */
    VOS_UINT16                          usToolsId;                              /* 工具ID */
    VOS_UINT8                           aucData[4];                             /* 传输消息的内容 */

    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_OM_TRANS_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/

}NasOmTrans_MSG;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/








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

#endif /* end of NasOmTrans.h */

