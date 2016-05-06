/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : ExtAppCmInterface.h
  Author      : ---
  Version     : V200R001
  Date        : 2005-08-17
  Description : 协议栈软件CM子层(CC/SS/SM)与APP接口头文件
  History     :
      1.  张志勇  2004-12-24   新规作成
      2.  张志勇  2005-02-12   在CC接口中增加CCBS相关原语的ucChoice定义
      3.  崔建海  2005-06-16   在CC接口中增加STATUS相关原语的ucChoice和结构定义
      4.  蒋丽萍  2006-08-09   A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
      5.  zhoujun40661 2006-7-27 A32D04798
      6. 日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 增加 #pragma pack(4)，问题单号:A32D07779
************************************************************************/

#ifndef _EXT_APP_CM_INTERFACE_H_
#define _EXT_APP_CM_INTERFACE_H_

#include "vos.h"
#include "TafSmInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif    /* __cpluscplus */
#endif    /* __cpluscplus */
#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define             SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN                (0x0100)
#define             SSA_SS_REL_CAUSE_CM_SRV_REJ_END                  (0x01FF)
#define             SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN              (0x0200)
#define             SSA_SS_REL_CAUSE_CSFB_SRV_REJ_END                (0x02FF)
#define             SSA_SS_REL_CAUSE_SMS_CP_ERR_BEGIN                (0x0300)
#define             SSA_SS_REL_CAUSE_SMS_CP_ERR_END                  (0x03FF)
#define             SSA_SS_REL_CAUSE_SMS_RP_ERR_BEGIN                (0x0400)
#define             SSA_SS_REL_CAUSE_SMS_RP_ERR_END                  (0x04FF)
#define             SSA_SS_REL_CAUSE_SS_NW_REJ_BEGIN                 (0x0500)
#define             SSA_SS_REL_CAUSE_SS_NW_REJ_END                   (0x05FF)
#define             SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN              (0x0600)
#define             SSA_SS_REL_CAUSE_RR_CONN_FAIL_END                (0x06FF)
#define             SSA_SS_REL_CAUSE_RR_REL_BEGIN                    (0x0700)
#define             SSA_SS_REL_CAUSE_RR_REL_END                      (0x07FF)
#define             SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_BEGIN             (0x0800)
#define             SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_END               (0x08FF)
#define             SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN              (0x0900)
#define             SSA_SS_REL_CAUSE_MM_INTER_ERR_END                (0x09FF)

/* ------------------------------API 参数结构---------------------------------*/
/************************** BASIC TYPE DEFINITION START ************************/

/********************** ENUMERATED STRUCT DEFINITION START *********************/

/* APP-NAS structure : SspTaCause */
typedef enum {
    EN_STC_NORMAL = 0,
    EN_STC_NOT_SUPPT,
    EN_STC_TE_NOT_CONN,
    EN_STC_SSP_TIMEOUT,
    EN_STC_MSG_ERR,
    EN_STC_IE_ERR,
    EN_STC_OTHER_REASON
    /* ... */
} SSP_TA_CAUSE;
typedef VOS_UINT8  ENUM_SSP_TA_CAUSE;

/* APP-NAS structure : SspMtCause */
typedef enum {
    EN_SMC_QUAL_WORSE = 0,
    EN_SMC_CONGEST,
    EN_SMC_COVERAGE_OUT,
    EN_SMC_ACC,
    EN_SMC_NW_OUT_OF_ORDER,
    EN_SMC_BATTERY_ALERM_CONN,
    EN_SMC_BATTERY_ALERM_IDLE,
    EN_SMC_NO_UIM,
    EN_SMC_INVALID_UIM,
    EN_SMC_PIN_BLOCK,
    EN_SMC_ENSURE_EC,
    EN_SMC_NOT_SUPPT,
    EN_SMC_INSUFF_CAPAB,
    EN_SMC_ALREADY_CONNECT,
    EN_SMC_SSP_TIMEOUT,
    EN_SMC_SS_TIMEOUT,
    EN_SMC_SS_PROT_ERR,
    EN_SMC_RRC_PROT_ERR,
    EN_SMC_MM_GMM_PROT_ERR,
    EN_SMC_MSG_ERR,
    EN_SMC_IE_ERR,
    EN_SMC_OTHER_REASON
    /* ... */
} SSP_MT_CAUSE;
typedef VOS_UINT8  ENUM_SSP_MT_CAUSE;
/********************** ENUMERATED STRUCT DEFINITION END   *********************/

/********************** OCTET STRING STRUCT DEFINITION START *******************/
/*Modified by Jim J00240*/
#pragma pack(4)

/* APP-NAS structure : Facility */
typedef struct {
    VOS_UINT32  ulCnt;
    VOS_UINT8  Facility[255];
} ST_SSP_IES_FACILITY;

/* APP-NAS structure : Sspversion */
typedef struct {
    VOS_UINT32  ulCnt;
    VOS_UINT8  Sspversion[1];
} ST_SSP_IES_SSPVERSION;

/* APP-NAS structure : Cause */
typedef struct {
    VOS_UINT32  ulCnt;
    VOS_UINT8  Cause[30];
} ST_SSP_IES_CAUSE;

/********************** OCTET STRING STRUCT DEFINITION END   *******************/

/********************** COMPLEX TYPE STRUCT DEFINITION START *******************/

/* APP-NAS structure : Begin-req */
typedef struct {
    VOS_UINT32  OP_Sspversion    : 1;
    VOS_UINT32  OP_Spare         : 31;

    ST_SSP_IES_FACILITY      Facility;                                          /* OCTET STRING(SIZE(0..255,...)) */
    ST_SSP_IES_SSPVERSION    Sspversion;                                        /* OCTET STRING(SIZE(1,...))  OPTIONAL */
                                                                                /* ... */
} ST_BEGIN_REQ;

/* APP-NAS structure : Facility-req */
typedef struct {
    ST_SSP_IES_FACILITY    Facility;                                            /* OCTET STRING(SIZE(0..255,...)) */
                                                                                /* ... */
} ST_SSP_MSGS_FACILITY_REQ;

/* APP-NAS structure : End-req */
typedef struct {
    VOS_UINT32  OP_Cause       : 1;
    VOS_UINT32  OP_Facility    : 1;
    VOS_UINT32  OP_SspTaCause  : 1;
    VOS_UINT32  OP_Spare       : 29;

    ST_SSP_IES_CAUSE       Cause;                                               /* OCTET STRING(SIZE(2..30,...))  OPTIONAL */
    ST_SSP_IES_FACILITY    Facility;                                            /* OCTET STRING(SIZE(0..255,...))  OPTIONAL */
                                                                                /* ... */
    ENUM_SSP_TA_CAUSE      enSspTaCause;                                        /* ENUMERATED  OPTIONAL */
} ST_END_REQ;

/* APP-NAS structure : Begin-ind */
typedef struct {
    ST_SSP_IES_FACILITY    Facility;                                            /* OCTET STRING(SIZE(0..255,...)) */
                                                                                /* ... */
} ST_BEGIN_IND;

/* APP-NAS structure : Facility-ind */
typedef struct {
    ST_SSP_IES_FACILITY    Facility;                                            /* OCTET STRING(SIZE(0..255,...)) */
                                                                                /* ... */
} ST_SSP_MSGS_FACILITY_IND;

/*****************************************************************************
 枚举名    : SSA_SS_REL_CAUSE_ENUM_UINT32
 枚举说明  : mm给ss回复失败原因值，ss转给ssa，ssa根据原因值判断是否需要重发
 1.日    期   : 2013年9月12日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
enum SSA_SS_REL_CAUSE_ENUM
{
    /* cm service rej */
    SSA_SS_REL_CAUSE_CM_SRV_REJ_IMSI_UNKNOWN_IN_HLR                                 = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 2,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_ILLEGAL_MS                                          = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 3,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_IMSI_UNKNOWN_IN_VLR                                 = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 4,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_IMEI_NOT_ACCEPTED                                   = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 5,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_ILLEGAL_ME                                          = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 6,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_PLMN_NOT_ALLOWED                                    = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 11,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_LOCATION_AREA_NOT_ALLOWED                           = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 12,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_ROAMING_NOT_ALLOWED_IN_THIS_LOCATION_AREA           = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 13,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_NO_SUITABLE_CELLS_IN_LOCATION_AREA                  = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 15,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_NETWORK_FAILURE                                     = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 17,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_MAC_FAILURE                                         = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 20,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_SYNCH_FAILURE                                       = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 21,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_CONGESTION                                          = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 22,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_GSM_AUTHENTICATION_UNACCEPTABLE                     = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 23,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_NOT_AUTHORIZED_FOR_THIS_CSG                         = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 25,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_SERVICE_OPTION_NOT_SUPPORTED                        = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 32,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_REQUESTED_SERVICE_OPTION_NOT_SUBSCRIBED             = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 33,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_SERVICE_OPTION_TEMPORARILY_OUT_OF_ORDER             = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 34,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_CALL_CANNOT_BE_IDENTIFIED                           = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 38,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_0                  = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 48,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_1                  = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 49,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_2                  = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 50,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_3                  = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 51,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_4                  = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 52,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_5                  = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 53,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_6                  = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 54,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_7                  = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 55,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_8                  = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 56,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_9                  = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 57,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_10                 = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 58,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_11                 = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 59,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_12                 = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 60,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_13                 = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 61,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_14                 = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 62,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_15                 = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 63,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_SEMANTICALLY_INCORRECT_MESSAGE                      = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 95,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_INVALID_MANDATORY_INFORMATION                       = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 96,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_MESSAGE_TYPE_NONEXISTENT_OR_NOT_IMPLEMENTED         = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 97,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_THE_PROTOCAL_STATE = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 98,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_INFOMATION_ELEMENT_NONEXISTENT_OR_NOT_IMPLEMENTED   = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 99,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_CONDITIONAL_IE_ERROR                                = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 100,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_MESSAGE_NOT_COMPATIBLE_WITH_THE_PROTOCOL_STATE      = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 101,
    SSA_SS_REL_CAUSE_CM_SRV_REJ_PROTOCOL_ERROR_UNSPECIFIED                          = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 111,

    SSA_SS_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246                               = SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN + 127,


    /* CSFB service rej */
    SSA_SS_REL_CAUSE_CSFB_SRV_REJ_ILLEGAL_UE                                        = SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 3,
    SSA_SS_REL_CAUSE_CSFB_SRV_REJ_ILLEGAL_ME                                        = SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 6,
    SSA_SS_REL_CAUSE_CSFB_SRV_REJ_EPS_SERVICES_NOT_ALLOWED                          = SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 7,
    SSA_SS_REL_CAUSE_CSFB_SRV_REJ_EPS_SERVICES_AND_NONEPS_SERVICES_NOT_ALLOWED      = SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 8,
    SSA_SS_REL_CAUSE_CSFB_SRV_REJ_UE_IDENTITY_CANNOT_BE_DERIVED_BY_NW               = SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 9,
    SSA_SS_REL_CAUSE_CSFB_SRV_REJ_IMPLICITLY_DETACHED                               = SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 10,
    SSA_SS_REL_CAUSE_CSFB_SRV_REJ_PLMN_NOT_ALLOWED                                  = SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 11,
    SSA_SS_REL_CAUSE_CSFB_SRV_REJ_TRACKING_AREA_NOT_ALLOWED                         = SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 12,
    SSA_SS_REL_CAUSE_CSFB_SRV_REJ_ROAMING_NOT_ALLOWED_IN_THIS_TA                    = SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 13,
    SSA_SS_REL_CAUSE_CSFB_SRV_REJ_NO_SUITABLE_CELLS_IN_TRACKING_AREA                = SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 15,
    SSA_SS_REL_CAUSE_CSFB_SRV_REJ_CS_DOMAIN_NOT_AVAILABLE                           = SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 18,
    SSA_SS_REL_CAUSE_CSFB_SRV_REJ_CONGESTION                                        = SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 22,
    SSA_SS_REL_CAUSE_CSFB_SRV_REJ_NOT_AUTHORIZED_FOR_THIS_CSG                       = SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 25,
    SSA_SS_REL_CAUSE_CSFB_SRV_REJ_REQ_SER_OPTION_NOT_AUTHORIZED_IN_PLMN             = SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 35,
    SSA_SS_REL_CAUSE_CSFB_SRV_REJ_CS_SERVICE_TEMPORARILY_NOT_AVAILABLE              = SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 39,
    SSA_SS_REL_CAUSE_CSFB_SRV_REJ_NO_EPS_BEARER_CONTEXT_ACTIVATED                   = SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 40,
    SSA_SS_REL_CAUSE_CSFB_SRV_REJ_SEVERE_NETWORK_FAILURE                            = SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN + 42,


    /* AS rr connection fail */
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_CONGESTION                              = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 1,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_UNSPECIFIED                             = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 2,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_ACCESS_BAR                              = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 3,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_EST_CONN_FAIL                           = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 4,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT                 = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 5,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_RANDOM_ACCESS_REJECT                    = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 6,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_T3122_RUNING                            = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 7,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_NO_RF                                   = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 8,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_LOW_LEVEL_SEARCHING_NETWORK             = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 9,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_RANDOM_ACCESS_SEND_FAIL                 = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 10,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_NO_VALID_INFO                           = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 11,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_UE_NOT_ALLOW                            = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 12,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_TIME_OUT                                = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 13,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_NO_RANDOM_ACCESS_RESOURCE               = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 14,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_INVALID_IMMEDIATE_ASSIGNED_MSG          = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 15,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_ACTIVE_PHYSICAL_CHANNEL_FAIL            = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 16,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_AIR_MSG_DECODE_ERROR                    = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 17,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_CURRENT_PROTOCOL_NOT_SUPPORT            = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 18,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_INVALID_UE_STATE                        = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 19,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_CELL_BARRED                             = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 20,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_FAST_RETURN_TO_LTE                      = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 21,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_RA_FAIL_NO_VALID_INFO                   = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 22,
    SSA_SS_REL_CAUSE_RR_CONN_FAIL_RJ_INTER_RAT                            = SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN + 23,


    /* AS Rel ind */
    SSA_SS_REL_CAUSE_RR_REL_AUTH_REJ                                      = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 0,
    SSA_SS_REL_CAUSE_RR_REL_NORMAL_EVENT                                  = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 1,
    SSA_SS_REL_CAUSE_RR_REL_NORMAL_UNSPECIFIED                            = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 2,
    SSA_SS_REL_CAUSE_RR_REL_PREEMPTIVE_RELEASE                            = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 3,
    SSA_SS_REL_CAUSE_RR_REL_CONGESTION                                    = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 4,
    SSA_SS_REL_CAUSE_RR_REL_REEST_REJ                                     = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 5,
    SSA_SS_REL_CAUSE_RR_REL_DIRECTED_SIGNAL_CONN_REEST                    = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 6,
    SSA_SS_REL_CAUSE_RR_REL_USER_INACTIVE                                 = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 7,
    SSA_SS_REL_CAUSE_RR_REL_UTRAN_RELEASE                                 = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 8,
    SSA_SS_REL_CAUSE_RR_REL_RRC_ERROR                                     = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 9,
    SSA_SS_REL_CAUSE_RR_REL_RL_FAILURE                                    = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 10,
    SSA_SS_REL_CAUSE_RR_REL_OTHER_REASON                                  = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 11,
    SSA_SS_REL_CAUSE_RR_REL_NO_RF                                         = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 12,
    SSA_SS_REL_CAUSE_RR_REL_RLC_ERR_OR                                    = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 13,
    SSA_SS_REL_CAUSE_RR_REL_CELL_UP_DATE_FAIL                             = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 14,
    SSA_SS_REL_CAUSE_RR_REL_NAS_REL_REQ                                   = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 15,
    SSA_SS_REL_CAUSE_RR_REL_CONN_FAIL                                     = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 16,     /* redial */
    SSA_SS_REL_CAUSE_RR_REL_NAS_DATA_ABSENT                               = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 17,     /* redial */
    SSA_SS_REL_CAUSE_RR_REL_T314_EXPIRED                                  = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 18,
    SSA_SS_REL_CAUSE_RR_REL_W_RL_FAIL                                     = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 19,

    SSA_SS_REL_CAUSE_RR_REL_G_RL_FAIL                                     = SSA_SS_REL_CAUSE_RR_REL_BEGIN + 20,

    /* CSFB LMM Error */
    SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_LMM_LOCAL_FAIL                         = SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 0,
    SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_AUTH_REJ                               = SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 1,
    SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_T3417_TIME_OUT                         = SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 2,
    SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_APP_DETACH_SERVICE                     = SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 3,
    SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_CN_DETACH_SERVICE                      = SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 4,
    SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_FOR_OTHERS                             = SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 5,
    SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_FOR_EMM_STATE                          = SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 6,
    SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_SMS_ONLY                               = SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 7,
    SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_PS_ONLY                                = SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 8,
    SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_TAU_COLL_ABNORMAL                      = SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_BEGIN + 9,


    /* MM Inter Error */
    SSA_SS_REL_CAUSE_MM_INTER_ERR_FORB_LA                                 = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 0,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_FORB_OTHER                              = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 1,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR                           = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 2,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_CS_DETACH                               = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 3,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID                          = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 4,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION                   = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 5,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT                         = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 6,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_SEARCHING_NETWORK                       = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 7,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE                 = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 8,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY        = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 9,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE                         = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 10,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE                    = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 11,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_CSFB_ALREADY_EXISTS                     = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 12,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL                       = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 13,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_TI_INVALID                              = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 14,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT                   = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 15,   /* redial */
    SSA_SS_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST                       = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 16,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE                        = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 17,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT                  = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 18,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_BACK_TO_LTE                             = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 19,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_RESUME_TO_EHRPD                         = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 20,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL                          = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 21,   /* 短信业务SAPI3发送失败,不重拨 */
    SSA_SS_REL_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL                          = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 22,   /* 短信业务SAPI3建立时GAS回复失败,重拨 */
    SSA_SS_REL_CAUSE_MM_INTER_ERR_ECALL_INACTIVE                          = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 23,   /* eCall Inactive状态,不重拨 */
    SSA_SS_REL_CAUSE_MM_INTER_ERR_REEST_FAIL                              = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 24,   /* MM reest状态收到est_cnf(失败)或rel ind,不重拨 */
    SSA_SS_REL_CAUSE_MM_INTER_ERR_CC_REL_REQ                              = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 25,
    SSA_SS_REL_CAUSE_MM_INTER_ERR_LTE_LIMITED_SERVICE                     = SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN + 26,


    SSA_SS_REL_CAUSE_BUTT                                                 = 0xFFFFFFFF
};
typedef VOS_UINT32 SSA_SS_REL_CAUSE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : SSA_SS_CS_CONN_STATE_ENUM
 结构说明  : 链接状态
 1.日    期   : 2013年9月11日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
enum SSA_SS_CS_CONN_STATE_ENUM
{
    SSA_SS_CS_CONN_STATE_ABSENT,                                                /* 连接不存在 */
    SSA_SS_CS_CONN_STATE_PRESENT,                                               /* 连接存在 */
    SSA_SS_CS_CONN_STATE_BUTT
};
typedef VOS_UINT8 SSA_SS_CS_CONN_STATE_ENUM_UINT8;


typedef struct
{
    SSA_SS_CS_CONN_STATE_ENUM_UINT8     enConnState;
    VOS_UINT8                           aucReserved[3];
}SSA_SS_CS_CONN_IND_STRU;



/*****************************************************************************
 枚举名    : SSA_SS_STATUS_ENUM_UINT8
 结构说明  : SS建立状态
 1.日    期   : 2015年8月18日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
enum SSA_SS_STATUS_ENUM
{
    SSA_SS_STATUS_SETUP_SUCC,                                                   /* 连接建立成功 */
    SSA_SS_STATUS_SETUP_FAIL,                                                   /* 连接建立失败 */
    SSA_SS_STATUS_BUTT
};
typedef VOS_UINT8 SSA_SS_STATUS_ENUM_UINT8;

/*****************************************************************************
 结构名    : SSA_SS_STATUS_NTY_STRU
 结构说明  : 通知SS建立状态
  1.日    期   : 2015年8月18日
    作    者   : s00217060
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    SSA_SS_STATUS_ENUM_UINT8            enSsStatus;
    VOS_UINT8                           aucReserved[3];
}SSA_SS_STATUS_NTY_STRU;

/* APP-NAS structure : End-ind */
typedef struct {
    VOS_UINT32  OP_Cause       : 1;
    VOS_UINT32  OP_Facility    : 1;
    VOS_UINT32  OP_SspMtCause  : 1;
    VOS_UINT32  OP_Spare       : 29;

    ST_SSP_IES_CAUSE       Cause;                                               /* OCTET STRING(SIZE(2..30,...))  OPTIONAL */
    ST_SSP_IES_FACILITY    Facility;                                            /* OCTET STRING(SIZE(0..255,...))  OPTIONAL */
                                                                                /* ... */
    ENUM_SSP_MT_CAUSE      enSspMtCause;                                        /* ENUMERATED  OPTIONAL */

    SSA_SS_REL_CAUSE_ENUM_UINT32      enSsaSsRelCause;
    VOS_UINT8                         aucReserved[3];

} ST_END_IND;

/* APP-NAS structure : SSPmsgCore */
typedef struct {
    VOS_UINT8      ucChoice;

    #define    D_SMC_BEGIN_REQ       0
    #define    D_SMC_FACILITY_REQ    1
    #define    D_SMC_END_REQ         2
    #define    D_SMC_BEGIN_IND       3
    #define    D_SMC_FACILITY_IND    4
    #define    D_SMC_END_IND         5

    #define    SSA_SS_CS_CONN_IND         (6)
    #define    SSA_SS_STATUS_NTY        (7)

    union  {
        ST_BEGIN_REQ                BeginReq;
        ST_SSP_MSGS_FACILITY_REQ    FacilityReq;
        ST_END_REQ                  EndReq;
        ST_BEGIN_IND                BeginInd;
        ST_SSP_MSGS_FACILITY_IND    FacilityInd;
        ST_END_IND                  EndInd;

        SSA_SS_CS_CONN_IND_STRU     stCsConnInd;
        SSA_SS_STATUS_NTY_STRU      stSsStatusNty;

    } u;
} ST_SSP_MSG_CORE;

/* APP-NAS structure : SSPmessage */
typedef struct {
    VOS_UINT8                           ucCr;                                   /* INTEGER(0..255) */
    VOS_UINT8                           ucRedialFlg;                            /* 重拨标志 */
    VOS_UINT8                           aucReserve[2];
    ST_SSP_MSG_CORE                     SspmsgCore;
} ST_SSP_MSG;


typedef struct
{
    MSG_HEADER_STRU                 MsgHeader;                                  /* 消息头                                   */
    ST_SSP_MSG                      stSspMsg;
}APP_SS_MSG_DATA;
/*_H2ASN_Length VOS_UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    APP_SS_MSG_DATA                 MsgData;
}AppSsInterface_MSG;



#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif
/********************** COMPLEX TYPE STRUCT DEFINITION END   *******************/
#ifdef __cplusplus
#if __cplusplus
}
#endif    /* __cpluscplus */
#endif    /* __cpluscplus */

#endif    /* _PER_INTERFACE_H_ */
