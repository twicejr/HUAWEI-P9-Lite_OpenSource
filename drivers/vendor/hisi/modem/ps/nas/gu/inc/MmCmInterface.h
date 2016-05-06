/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MmcCmInterface.h
  版 本 号   : 初稿
  作    者   : z00161729
  生成日期   : 2013年09月14日
  最近修改   :
  功能描述   : mm和cm层的公共接口定义
  函数列表   :
  修改历史   :
  1.日    期   : 2013年09月14日
    作    者   : z00161729
    修改内容   : 创建文件

******************************************************************************/
#ifndef _MM_CM_INTERFACE_H_
#define _MM_CM_INTERFACE_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 全局变量定义
*****************************************************************************/

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* NAS_MMCM_REL_CAUSE_ENUM_UINT32的偏移需要与
   NAS_CC_CAUSE_VALUE_ENUM_U32和TAF_CS_CAUSE_ENUM_UINT32的偏移保持一致 */
#define             NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN                (0x0100)
#define             NAS_MMCM_REL_CAUSE_CM_SRV_REJ_END                  (0x01FF)
#define             NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN              (0x0200)
#define             NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_END                (0x02FF)
#define             NAS_MMCM_REL_CAUSE_SMS_CP_ERR_BEGIN                (0x0300)
#define             NAS_MMCM_REL_CAUSE_SMS_CP_ERR_END                  (0x03FF)
#define             NAS_MMCM_REL_CAUSE_SMS_RP_ERR_BEGIN                (0x0400)
#define             NAS_MMCM_REL_CAUSE_SMS_RP_ERR_END                  (0x04FF)
#define             NAS_MMCM_REL_CAUSE_SS_NW_REJ_BEGIN                 (0x0500)
#define             NAS_MMCM_REL_CAUSE_SS_NW_REJ_END                   (0x05FF)
#define             NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN              (0x0600)
#define             NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_END                (0x06FF)
#define             NAS_MMCM_REL_CAUSE_RR_REL_BEGIN                    (0x0700)
#define             NAS_MMCM_REL_CAUSE_RR_REL_END                      (0x07FF)
#define             NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_BEGIN             (0x0800)
#define             NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_END               (0x08FF)
#define             NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN              (0x0900)
#define             NAS_MMCM_REL_CAUSE_MM_INTER_ERR_END                (0x09FF)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_MMCM_REL_CAUSE_ENUM_UINT32
 枚举说明  : mm给cc回复链接释放原因值，cc根据原因值判断是否需要重发
 1.日    期   : 2014年9月20日
   作    者   : s00217060
   修改内容   : 新建
 2.日    期   : 2014年9月20日
   作    者   : n00269697
   修改内容   : CHR optimize项目：增加协议规定的原因值枚举
*****************************************************************************/
enum NAS_MMCM_REL_CAUSE_ENUM
{
    /* cm service rej */
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_IMSI_UNKNOWN_IN_HLR                                 = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 2,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_ILLEGAL_MS                                          = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 3,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_IMSI_UNKNOWN_IN_VLR                                 = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 4,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_IMEI_NOT_ACCEPTED                                   = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 5,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_ILLEGAL_ME                                          = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 6,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_PLMN_NOT_ALLOWED                                    = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 11,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_LOCATION_AREA_NOT_ALLOWED                           = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 12,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_ROAMING_NOT_ALLOWED_IN_THIS_LOCATION_AREA           = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 13,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_NO_SUITABLE_CELLS_IN_LOCATION_AREA                  = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 15,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_NETWORK_FAILURE                                     = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 17,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_MAC_FAILURE                                         = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 20,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_SYNCH_FAILURE                                       = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 21,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION                                          = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 22,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_GSM_AUTHENTICATION_UNACCEPTABLE                     = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 23,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_NOT_AUTHORIZED_FOR_THIS_CSG                         = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 25,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_SERVICE_OPTION_NOT_SUPPORTED                        = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 32,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_REQUESTED_SERVICE_OPTION_NOT_SUBSCRIBED             = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 33,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_SERVICE_OPTION_TEMPORARILY_OUT_OF_ORDER             = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 34,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CALL_CANNOT_BE_IDENTIFIED                           = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 38,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_0                  = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 48,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_1                  = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 49,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_2                  = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 50,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_3                  = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 51,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_4                  = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 52,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_5                  = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 53,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_6                  = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 54,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_7                  = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 55,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_8                  = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 56,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_9                  = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 57,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_10                 = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 58,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_11                 = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 59,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_12                 = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 60,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_13                 = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 61,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_14                 = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 62,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_15                 = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 63,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_SEMANTICALLY_INCORRECT_MESSAGE                      = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 95,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_INVALID_MANDATORY_INFORMATION                       = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 96,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_MESSAGE_TYPE_NONEXISTENT_OR_NOT_IMPLEMENTED         = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 97,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_THE_PROTOCAL_STATE = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 98,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_INFOMATION_ELEMENT_NONEXISTENT_OR_NOT_IMPLEMENTED   = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 99,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONDITIONAL_IE_ERROR                                = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 100,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_MESSAGE_NOT_COMPATIBLE_WITH_THE_PROTOCOL_STATE      = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 101,
    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_PROTOCOL_ERROR_UNSPECIFIED                          = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 111,

    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246                               = NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN + 127,


    /* CSFB service rej */
    NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_ILLEGAL_UE                                        = NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 3,
    NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_ILLEGAL_ME                                        = NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 6,
    NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_EPS_SERVICES_NOT_ALLOWED                          = NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 7,
    NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_EPS_SERVICES_AND_NONEPS_SERVICES_NOT_ALLOWED      = NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 8,
    NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_UE_IDENTITY_CANNOT_BE_DERIVED_BY_NW               = NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 9,
    NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_IMPLICITLY_DETACHED                               = NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 10,
    NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_PLMN_NOT_ALLOWED                                  = NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 11,
    NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_TRACKING_AREA_NOT_ALLOWED                         = NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 12,
    NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_ROAMING_NOT_ALLOWED_IN_THIS_TA                    = NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 13,
    NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_NO_SUITABLE_CELLS_IN_TRACKING_AREA                = NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 15,
    NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_CS_DOMAIN_NOT_AVAILABLE                           = NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 18,
    NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_CONGESTION                                        = NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 22,
    NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_NOT_AUTHORIZED_FOR_THIS_CSG                       = NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 25,
    NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_REQ_SER_OPTION_NOT_AUTHORIZED_IN_PLMN             = NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 35,
    NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_CS_SERVICE_TEMPORARILY_NOT_AVAILABLE              = NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 39,
    NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_NO_EPS_BEARER_CONTEXT_ACTIVATED                   = NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 40,
    NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_SEVERE_NETWORK_FAILURE                            = NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 42,

    /* AS rr connection fail */
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_CONGESTION                              = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 1,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_UNSPECIFIED                             = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 2,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_ACCESS_BAR                              = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 3,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_EST_CONN_FAIL                           = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 4,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT                 = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 5,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_RANDOM_ACCESS_REJECT                    = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 6,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_T3122_RUNING                            = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 7,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_NO_RF                                   = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 8,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_LOW_LEVEL_SEARCHING_NETWORK             = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 9,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_RANDOM_ACCESS_SEND_FAIL                 = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 10,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_NO_VALID_INFO                           = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 11,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_UE_NOT_ALLOW                            = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 12,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_TIME_OUT                                = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 13,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_NO_RANDOM_ACCESS_RESOURCE               = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 14,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_INVALID_IMMEDIATE_ASSIGNED_MSG          = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 15,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_ACTIVE_PHYSICAL_CHANNEL_FAIL            = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 16,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_AIR_MSG_DECODE_ERROR                    = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 17,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_CURRENT_PROTOCOL_NOT_SUPPORT            = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 18,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_INVALID_UE_STATE                        = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 19,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_CELL_BARRED                             = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 20,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_FAST_RETURN_TO_LTE                      = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 21,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_RA_FAIL_NO_VALID_INFO                   = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 22,
    NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_RJ_INTER_RAT                            = NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_BEGIN + 23,


    /* AS Rel ind */
    NAS_MMCM_REL_CAUSE_RR_REL_AUTH_REJ                                      = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 0,
    NAS_MMCM_REL_CAUSE_RR_REL_NORMAL_EVENT                                  = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 1,
    NAS_MMCM_REL_CAUSE_RR_REL_NORMAL_UNSPECIFIED                            = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 2,
    NAS_MMCM_REL_CAUSE_RR_REL_PREEMPTIVE_RELEASE                            = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 3,
    NAS_MMCM_REL_CAUSE_RR_REL_CONGESTION                                    = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 4,
    NAS_MMCM_REL_CAUSE_RR_REL_REEST_REJ                                     = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 5,
    NAS_MMCM_REL_CAUSE_RR_REL_DIRECTED_SIGNAL_CONN_REEST                    = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 6,
    NAS_MMCM_REL_CAUSE_RR_REL_USER_INACTIVE                                 = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 7,
    NAS_MMCM_REL_CAUSE_RR_REL_UTRAN_RELEASE                                 = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 8,
    NAS_MMCM_REL_CAUSE_RR_REL_RRC_ERROR                                     = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 9,
    NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE                                    = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 10,
    NAS_MMCM_REL_CAUSE_RR_REL_OTHER_REASON                                  = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 11,
    NAS_MMCM_REL_CAUSE_RR_REL_NO_RF                                         = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 12,
    NAS_MMCM_REL_CAUSE_RR_REL_RLC_ERR_OR                                    = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 13,
    NAS_MMCM_REL_CAUSE_RR_REL_CELL_UP_DATE_FAIL                             = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 14,
    NAS_MMCM_REL_CAUSE_RR_REL_NAS_REL_REQ                                   = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 15,
    NAS_MMCM_REL_CAUSE_RR_REL_CONN_FAIL                                     = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 16,     /* redial */
    NAS_MMCM_REL_CAUSE_RR_REL_NAS_DATA_ABSENT                               = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 17,     /* redial */
    NAS_MMCM_REL_CAUSE_RR_REL_T314_EXPIRED                                  = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 18,
    NAS_MMCM_REL_CAUSE_RR_REL_W_RL_FAIL                                     = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 19,

    NAS_MMCM_REL_CAUSE_RR_REL_G_RL_FAIL                                     = NAS_MMCM_REL_CAUSE_RR_REL_BEGIN + 20,


    /* CSFB LMM Error */
    NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_LMM_LOCAL_FAIL                         = NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 0,
    NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_AUTH_REJ                               = NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 1,
    NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_T3417_TIME_OUT                         = NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 2,
    NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_APP_DETACH_SERVICE                     = NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 3,
    NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_CN_DETACH_SERVICE                      = NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 4,
    NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_FOR_OTHERS                             = NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 5,
    NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_FOR_EMM_STATE                          = NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 6,
    NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_SMS_ONLY                               = NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 7,
    NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_PS_ONLY                                = NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 8,
    NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_TAU_COLL_ABNORMAL                      = NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 9,


    /* MM Inter Error */
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA                                 = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 0,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_OTHER                              = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 1,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR                           = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 2,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH                               = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 3,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID                          = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 4,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION                   = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 5,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT                         = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 6,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SEARCHING_NETWORK                       = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 7,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE                 = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 8,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY        = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 9,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE                         = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 10,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE                    = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 11,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CSFB_ALREADY_EXISTS                     = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 12,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL                       = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 13,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID                              = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 14,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT                   = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 15,   /* redial */
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST                       = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 16,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE                        = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 17,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT                  = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 18,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BACK_TO_LTE                             = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 19,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_RESUME_TO_EHRPD                         = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 20,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL                          = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 21,   /* 短信业务SAPI3发送失败,和GAS回复失败,不重拨 */
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL                          = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 22,   /* 短信业务SAPI3建立时GAS回复失败,重拨 */
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ECALL_INACTIVE                          = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 23,   /* eCall Inactive状态,不重拨 */
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL                              = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 24,   /* MM reest状态收到est_cnf(失败)或rel ind,不重拨 */
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_REL_REQ                              = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 25,
    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_LTE_LIMITED_SERVICE                     = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BEGIN + 26,

    NAS_MMCM_REL_CAUSE_BUTT                                                 = 0xFFFFFFFF
};
typedef VOS_UINT32 NAS_MMCM_REL_CAUSE_ENUM_UINT32;

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

#endif /* end of MmCmInterface.h */

