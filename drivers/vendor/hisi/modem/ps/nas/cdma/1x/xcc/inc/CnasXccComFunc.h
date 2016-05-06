/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccComFunc.h
  版 本 号   : 初稿
  作    者   : w00242748
  生成日期   : 2014年9月15日
  最近修改   :
  功能描述   : CnasXccComFunc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年9月15日
    作    者   : w00242748
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XCC_COM_FUNC_H__
#define __CNAS_XCC_COM_FUNC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "cas_1x_access_ctrl_proc_nas_pif.h"
#include "CnasXccTimer.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "UserDefinedDataTypes_cs0005.h"
#endif
#include "cas_1x_control_main_nas_pif.h"
#include "csn1clib.h"
#include "xcc_taf_pif.h"
#include "xcc_xcall_pif.h"
#include "xcc_aps_pif.h"
#include "xcc_mma_pif.h"
#include "CnasCcb.h"
#include "TafApi.h"
#include "TafMtcApi.h"
#include "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CNAS_XCC_MAX_DATA_SDU_OCTET_NUM                     ( 512 )             /* maximum octet number of a L3 data sdu */

#define CNAS_XCC_MAX_DISPALY_CHARI_OCTET_NUM                (64)
#define CNAS_XCC_MAX_CALLED_NUMBER_CHARI_OCTET_NUM          (64)
#define CNAS_XCC_MAX_CALLING_NUMBER_CHARI_OCTET_NUM         (64)
#define CNAS_XCC_MAX_CONNECTED_NUMBER_CHARI_OCTET_NUM       (64)
#define CNAS_XCC_MAX_REDIRECTING_NUMBER_CHARI_OCTET_NUM     (64)
#define CNAS_XCC_MAX_EXT_DISPLAY_DATA_NUM                   (3)
#define CNAS_XCC_MAX_EXTENDED_DISPLAY_CHARI_OCTET_NUM       (64)

#define CNAS_XCC_MAX_FWIM_EFWIM_INFO_RECO_NUM               (15)
#define CNAS_XCC_MAX_AWIM_EAWIM_INFO_RECO_NUM               (15)



#define CNAS_XCC_DTMF_PULSE_WIDTH_95                        (95)    /* DTMF Pulse Width 90ms */
#define CNAS_XCC_DTMF_PULSE_WIDTH_150                       (150)   /* DTMF Pulse Width 150ms */
#define CNAS_XCC_DTMF_PULSE_WIDTH_200                       (200)   /* DTMF Pulse Width 200ms */
#define CNAS_XCC_DTMF_PULSE_WIDTH_250                       (250)   /* DTMF Pulse Width 250ms */
#define CNAS_XCC_DTMF_PULSE_WIDTH_300                       (300)   /* DTMF Pulse Width 30ms */
#define CNAS_XCC_DTMF_PULSE_WIDTH_350                       (350)   /* DTMF Pulse Width 350ms */

#define CNAS_XCC_END_BURST_DTMF_MIN_INTER_DIGIT_INTERVAL_60             (60)   /* DTMF Minimum Inter-digit Interval 60ms */
#define CNAS_XCC_END_BURST_DTMF_MIN_INTER_DIGIT_INTERVAL_100            (100)  /* DTMF Minimum Inter-digit Interval 100ms */
#define CNAS_XCC_END_BURST_DTMF_MIN_INTER_DIGIT_INTERVAL_150            (150)  /* DTMF Minimum Inter-digit Interval 150ms */
#define CNAS_XCC_END_BURST_DTMF_MIN_INTER_DIGIT_INTERVAL_200            (200)  /* DTMF Minimum Inter-digit Interval 200ms */

#define CNAS_XCC_MAX_SOCM_FIELD_DATA_LEN                    (8)

#define CNAS_XCC_MAX_PKT_ZONE_LIST_LEN                      (15)
#define CNAS_XCC_PKT_CON_RESP_HEADER_LEN                    (1)
#define CNAS_XCC_OCTET_LEN_8_BIT                            (8)

#define CNAS_XCC_MAX_BURST_DTMF_NUM                         (255)
#define CNAS_XCC_INVALID_DTMF_SWITCH                        (0xff)
#define CNAS_XCC_INVALID_DTMF_DIGIT                         (0xff)

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#define CNAS_XCC_SetCS0005EDetailPara(pstCS0005Detail,usMsgTag,usPRevInUse,usAuthMode)\
        {\
            NAS_MEM_SET_S(pstCS0005Detail, sizeof(CS0005E_Details), 0, sizeof(CS0005E_Details));\
            (pstCS0005Detail)->n_MSG_TAG          = (usMsgTag);\
            (pstCS0005Detail)->n_P_REV_IN_USEs    = (usPRevInUse);\
            (pstCS0005Detail)->n_AUTH_MODE        = (usAuthMode);\
        }

/* RDSCH消息编码 对原始函数进行转定义的宏 */
#define CNAS_XCC_EncodeRDschMsg(Buffer, BitOffset, Source, pp_CS0005E_Details) \
            ENCODE_c_r_dsch( (Buffer), (BitOffset), (Source), (pp_CS0005E_Details) )

/* FDSCH普通消息解码 */
#define CNAS_XCC_DecodeFDschMsg(Buffer, BitOffset, Destin, Length, pp_CS0005E_Details)\
            DECODE_c_f_dsch((Buffer), (BitOffset), (Destin), (Length), (pp_CS0005E_Details))

/* 普通消息释放内存 对原始函数进行转定义的宏 */
#define CNAS_XCC_FreeFDschMsg(sp) \
            FREE_c_f_dsch( (sp) )

/* FCSCH普通消息解码 对原始函数进行转定义的宏 */
#define CNAS_XCC_DecodeFCschMsg(Buffer, BitOffset, Destin, Length, pp_CS0005E_Details) \
            DECODE_c_f_csch_mini6( (Buffer), (BitOffset), (Destin), (Length), (pp_CS0005E_Details) )

/* 普通消息释放内存 对原始函数进行转定义的宏 */
#define CNAS_XCC_FreeFCschMsg(sp) \
            FREE_c_f_csch_mini6( (sp) )

#define CNAS_XCC_EncodeRCschMsg(Buffer, BitOffset, Source, pp_CS0005E_Details) \
            ENCODE_c_r_csch_mini6( (Buffer), (BitOffset), (Source), (pp_CS0005E_Details) )


#endif

#define CNAS_XCC_SO3_MAX_RATE_REDUC                         (4)
#define CNAS_XCC_MAX_DORM_CNTL_VAL                          (2)
#define CNAS_XCC_MAX_PKT_CONN_CTRL_VAL                      (3)

#define CNAS_XCC_BIT_LEN_8_BIT                              (0x08)
#define CNAS_XCC_BIT_LEN_16_BIT                             (0x10)
#define CNAS_XCC_BIT_LEN_5_BIT                              (0x05)

#define CNAS_XCC_LOW_3_BIT_MASK                             (0x07)
#define CNAS_XCC_LOW_4_BIT_MASK                             (0x0f)

#define CNAS_XCC_5_BIT_OFFSET                               (5)

#define CNAS_XCC_MAX_FNM_INFO_RECO_NUM                      (15)


#define CNAS_XCC_L2_ERR_MAX_RE_ORIG_COUNT                   CNAS_XCC_RE_ORIG_COUNT_3
#define CNAS_XCC_RE_ORIG_COUNT_0                            (0)
#define CNAS_XCC_RE_ORIG_COUNT_1                            (1)
#define CNAS_XCC_RE_ORIG_COUNT_2                            (2)
#define CNAS_XCC_RE_ORIG_COUNT_3                            (3)
#define CNAS_XCC_RE_ORIG_COUNT_4                            (4)
#define CNAS_XCC_RE_ORIG_COUNT_5                            (5)
#define CNAS_XCC_RE_ORIG_COUNT_6                            (6)
#define CNAS_XCC_RE_ORIG_COUNT_7                            (7)
#define CNAS_XCC_RE_ORIG_COUNT_8                            (8)

#define CNAS_XCC_DTMF_DIGIT_MIN                             (1)
#define CNAS_XCC_DTMF_DIGIT_MAX                             (12)

#define CNAS_XCC_CONT_DTMF_ORDQ_STOP                        (0xFF)
#define CNAS_XCC_CONT_DTMF_ORDQ_START                       (0x00)

#define CNAS_XCC_BIT_LEN_9_BIT                              (9)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/** ****************************************************************************
 * Name        : SEND_BURST_DTMF_ON_LENGTH_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum SEND_BURST_DTMF_ON_LENGTH_ENUM
{
    CNAS_XCC_SEND_BURST_DTMF_ON_LEN_0                   = 0x00,
    CNAS_XCC_SEND_BURST_DTMF_ON_LEN_1                   = 0x01,
    CNAS_XCC_SEND_BURST_DTMF_ON_LEN_2                   = 0x02,
    CNAS_XCC_SEND_BURST_DTMF_ON_LEN_3                   = 0x03,
    CNAS_XCC_SEND_BURST_DTMF_ON_LEN_4                   = 0x04,
    CNAS_XCC_SEND_BURST_DTMF_ON_LEN_5                   = 0x05,
    CNAS_XCC_SEND_BURST_DTMF_ON_LEN_BUTT                = 0x06
};
typedef VOS_UINT8 SEND_BURST_DTMF_ON_LENGTH_ENUM_UINT8;


/** ****************************************************************************
 * Name        : SEND_BURST_DTMF_OFF_LENGTH_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum SEND_BURST_DTMF_OFF_LENGTH_ENUM
{
    CNAS_XCC_SEND_BURST_DTMF_OFF_LEN_0                   = 0x00,
    CNAS_XCC_SEND_BURST_DTMF_OFF_LEN_1                   = 0x01,
    CNAS_XCC_SEND_BURST_DTMF_OFF_LEN_2                   = 0x02,
    CNAS_XCC_SEND_BURST_DTMF_OFF_LEN_3                   = 0x03,
    CNAS_XCC_SEND_BURST_DTMF_OFF_LEN_BUTT                = 0x04
};
typedef VOS_UINT8 SEND_BURST_DTMF_OFF_LENGTH_ENUM_UINT8;

/*****************************************************************************
 结构名    : CAS_TAF_EST_CAUSE_CODE_MAP_STRU
 结构说明  : CAS EST REASON与TAF原因值的对应结构
  1.日    期   : 2014年9月22日
    作    者   : c00294324
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          enCasCause;
    TAF_XCC_CAUSE_ENUM_UINT32           enXccCause;
}CAS_TAF_EST_CAUSE_CODE_MAP_STRU;


/*****************************************************************************
 结构名    : CAS_TAF_TERMINATE_CAUSE_CODE_MAP_STRU
 结构说明  : CAS TERMINATE REASON与TAF原因值的对应结构
  1.日    期   : 2014年9月22日
    作    者   : c00294324
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  enCasCause;
    TAF_XCC_CAUSE_ENUM_UINT32                   enXccCause;
}CAS_TAF_TERMINATE_CAUSE_CODE_MAP_STRU;

/*****************************************************************************
 枚举名    : CNAS_XCC_SERVICE_TYPE_ENUM
 枚举说明  : 服务类型枚举定义
 1.日    期   : 2014年9月5日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
enum CNAS_XCC_SERVICE_TYPE_ENUM
{
    /* 语音呼叫 */
    CNAS_XCC_SERVICE_TYPE_VOICE_CALL                        = 0x00,

    /* 数据呼叫 */
    CNAS_XCC_SERVICE_TYPE_DATA_CALL                         = 0x01,

    /* 短消息 */
    CNAS_XCC_SERVICE_TYPE_SMS                               = 0x02,

    /* LOOPBACK */
    CNAS_XCC_SERVICE_TYPE_LOOPBACK                          = 0X03,

    /* AGPS */
    CNAS_XCC_SERVICE_TYPE_AGPS_CALL                         = 0X04,

    CNAS_XCC_SERVICE_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_XCC_SERVICE_TYPE_ENUM_UINT32;
/*****************************************************************************
 枚举名    :CNAS_XCC_REV_MS_REJECT_ORDQ_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 反向MS REJECT ORDER 类型TABLE 2.7.3-1
*****************************************************************************/
enum CNAS_XCC_REV_MS_REJECT_ORDQ_ENUM
{
    CNAS_XCC_REV_ORDER_MS_REJECT_UNSPECT_REASON      = 0x01,                    /* unspecified reason */
    CNAS_XCC_REV_ORDER_MS_REJECT_STATE               = 0X02,                    /* message not accepted in this state  */
    CNAS_XCC_REV_ORDER_MS_REJECT_STRUCT              = 0X03,                    /* message structure not acceptable */
    CNAS_XCC_REV_ORDER_MS_REJECT_FIELD               = 0X04,                    /* message field not in valid range */
    CNAS_XCC_REV_ORDER_MS_REJECT_CODE                = 0X05,                    /* message type or order code not understood */
    CNAS_XCC_REV_ORDER_MS_REJECT_CAPABILITY          = 0X06,                    /* message requires a capability that is not supported by the mobile station */
    CNAS_XCC_REV_ORDER_MS_REJECT_CONFIG              = 0X07,                    /* message cannot be handled by the current mobile station configuration */
    CNAS_XCC_REV_ORDER_MS_REJECT_LENGTH              = 0X08,                    /* response message would exceed allowable length */
    CNAS_XCC_REV_ORDER_MS_REJECT_MODE                = 0X09,                    /* information record is not supported for the specified band class and operating mode */
    CNAS_XCC_REV_ORDER_MS_REJECT_SRCH                = 0X0A,                    /* search set not specified */
    CNAS_XCC_REV_ORDER_MS_REJECT_INVALID_SRCH        = 0X0B,                    /* invalid search request */
    CNAS_XCC_REV_ORDER_MS_REJECT_INVALID_FREQ        = 0X0C,                    /* invalid Frequency Assignment */
    CNAS_XCC_REV_ORDER_MS_REJECT_SRCH_PERIOD         = 0X0D,                    /* earch period too short */
    CNAS_XCC_REV_ORDER_MS_REJECT_DEFAULT_CFG         = 0X0E,                    /* RC does not match with the value in the field DEFAULT_CONFIG  */
    CNAS_XCC_REV_ORDER_MS_REJECT_CALL_ASSIGN         = 0X10,                    /* call assignment not accepted */
    CNAS_XCC_REV_ORDER_MS_REJECT_NO_CC_INST          = 0X11,                    /* no call control instance present with the specified identifier */
    CNAS_XCC_REV_ORDER_MS_REJECT_CC_ALREADY_PRESENT  = 0X12,                    /* a call control instance is already present with the specified identifier */
    CNAS_XCC_REV_ORDER_MS_REJECT_TAG_MISMATCH        = 0X13,                    /* TAG received does notmatch any of the TAGstored */
    CNAS_XCC_REV_ORDER_MS_REJECT_BUTT
};
typedef VOS_UINT8 CNAS_XCC_REV_MS_REJECT_ORDQ_ENUM_UINT8;

/*****************************************************************************
 枚举名    :CNAS_XCC_REV_ORDER_CODE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 反向order CODE消息类型 TABLE 2.7.3-1
*****************************************************************************/
enum CNAS_XCC_REV_ORDER_CODE_ENUM
{
    CNAS_XCC_REV_ORDER_CODE_MS_ACKNOWLEDGEMENT       = 0X10,                     /* MOBILE Station Acknowledgment Order */
    CNAS_XCC_REV_ORDER_CODE_LONG_CODE_TRANSITION     = 0X17,                     /* LONG CODE TRANSITION */
    CNAS_XCC_REV_ORDER_CODE_CONNECT                  = 0X18,                     /* CONNECT ORDER */
    CNAS_XCC_REV_ORDER_CODE_CONTINUOUS_DTMF_TONE     = 0X19,                     /* CONTINUOUE DTMF TONE ORDER */
    CNAS_XCC_REV_ORDER_CODE_SERVICE_OPTION_CONTROL   = 0X1D,                     /* SERVICE OPTION CONTROL */
    CNAS_XCC_REV_ORDER_CODE_LOCAL_CONTROL_RESPONSE   = 0X1E,                     /* LOCAL CONTROL RESPONSE */
    CNAS_XCC_REV_ORDER_CODE_MS_REJECT                = 0X1F,                     /* MS REJECT 2.7.3.4  */

    CNAS_XCC_REV_ORDER_CODE_BUTT
};
typedef VOS_UINT8 CNAS_XCC_REV_ORDER_CODE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : CNAS_XCC_ORDER_MSG_TYPE
 协议表格  :
 ASN.1描述 :
 枚举说明  : order消息类型
*****************************************************************************/
enum CNAS_XCC_ORDER_TYPE_ENUM
{
    CNAS_XCC_ORDER_TYPE_ABBREVIATED_ALERT          = 0x00,                             /* Abbreviated Alert Order  */
    CNAS_XCC_ORDER_TYPE_BS_CHALLENGE_CONFIRMATION        ,                             /* Base Station Challenge Confirmation Order  */
    CNAS_XCC_ORDER_TYPE_MSG_ENCRYPTION_MODE              ,                             /* Message Encryption Mode Order (where nn is the mode per Table 3.7.2.3.2.8-2 */
    CNAS_XCC_ORDER_TYPE_RECORDER                         ,                             /* Reorder Order */
    CNAS_XCC_ORDER_TYPE_PARAMETER_UPDATE                 ,                             /* Parameter Update Order (where 'nnnn' is the Request Number)  */
    CNAS_XCC_ORDER_TYPE_AUDIT                            ,                             /* Audit Order */
    CNAS_XCC_ORDER_TYPE_INTERCEPT                        ,                             /* Intercept Order */
    CNAS_XCC_ORDER_TYPE_MAINTENANCE                      ,                             /* Maintenance Order */
    CNAS_XCC_ORDER_TYPE_BS_ACKNOWLEDGMENT                ,                             /* Base Station Acknowledgment Order  */
    CNAS_XCC_ORDER_TYPE_PILOT_MEASUREMENT                ,                             /* Pilot Measurement Request Order */
    CNAS_XCC_ORDER_TYPE_PERIODIC_PILOT_MEASUREMENT       ,                             /* Periodic Pilot Measurement Request Order  (see 3.7.4.6) */
    CNAS_XCC_ORDER_TYPE_LOCK_UNTIL_PWR_CYCLED            ,                             /* Lock Until Power-Cycled Order */
    CNAS_XCC_ORDER_TYPE_MAINTENANCE_REQUIRED             ,                             /* Maintenance Required Order */
    CNAS_XCC_ORDER_TYPE_UNLOCK                           ,                             /* Unlock Order */
    CNAS_XCC_ORDER_TYPE_SERVICE_OPTION_REQUEST           ,                             /* Service Option Request Order */
    CNAS_XCC_ORDER_TYPE_SERVICE_OPTION_RESPONSE          ,                             /* Service Option Response Order  */
    CNAS_XCC_ORDER_TYPE_RELEASE                          ,                             /* Release Order */
    CNAS_XCC_ORDER_TYPE_OUTER_LOOP_REPORT_REQUEST        ,                             /* Outer Loop Report Request Order */
    CNAS_XCC_ORDER_TYPE_LONG_CODE_TRANSITION             ,                             /* Long Code Transition Request Order  */
    CNAS_XCC_ORDER_TYPE_CONTINUOUS_DTMF_TONE             ,                             /* Continuous DTMF Tone Order */
    CNAS_XCC_ORDER_TYPE_STATUS_REQUEST                   ,                             /* Status Request Order  */
    CNAS_XCC_ORDER_TYPE_REGISTRATION_ACCEPTED            ,                             /* Registration Accepted Order */
    CNAS_XCC_ORDER_TYPE_REGISTRATION_REQUEST             ,                             /* Registration Request Order  */
    CNAS_XCC_ORDER_TYPE_REGISTRATION_REJECTED            ,                             /* Registration Rejected Order */
    CNAS_XCC_ORDER_TYPE_SERVICE_OPTION_CONTROL           ,                             /* Service Option Control Order */
    CNAS_XCC_ORDER_TYPE_LOCAL_CONTROL                    ,                             /* Local Control Order */
    CNAS_XCC_ORDER_TYPE_SLOTTED_MODE                     ,                             /* Slotted Mode Order  */
    CNAS_XCC_ORDER_TYPE_RETRY                            ,                             /* Retry Order  */
    CNAS_XCC_ORDER_TYPE_BS_REJECT                        ,                             /* Base Station Reject Order */

    CNAS_XCC_ORDER_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_XCC_ORDER_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_XCC_R_DSCH_INFO_RECORD_TYPE
 协议表格  :
 ASN.1描述 :
 枚举说明  : r-dsch information record type
*****************************************************************************/
enum CNAS_XCC_R_DSCH_INFO_RECORD_TYPE
{
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_RESERVED                                     = 0x01,          /* Reserved */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_RESERVED_FOR_OBSOLETE_IDENTIFICATION1        = 0x02,          /* Reserved for Obsolete Identification */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_KEYPAD_FACILITY                              = 0x03,          /* Keypad Facility */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_CALLED_PARTY_NUMBER                          = 0x04,          /* Called Party Number */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_CALLING_PARTY_NUMBER                         = 0x05,          /* Calling Party Number */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_RESERVED_FOR_OBSOLETE_IDENTIFICATION2        = 0x06,          /* Reserved for Obsolete Identification */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_CALL_MODE                                    = 0x07,          /* Call Mode */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_TERMINAL_INFORMATION                         = 0x08,          /* Terminal Information */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_ROAMING_INFORMATION                          = 0x09,          /* Roaming Information */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_SECURITY_STATUS                              = 0x0A,          /* Security Status */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_CONNECTED_NUMBER                             = 0x0B,          /* Connected Number */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_IMSI                                         = 0x0C,          /* IMSI */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_ESN                                          = 0x0D,          /* ESN */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_BAND_CLASS_INFORMATION                       = 0x0E,          /* Band Class Information */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_POWER_CLASS_INFORMATION                      = 0x0F,          /* Power Class Information */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_OPERATION_MODE_INFORMATION                   = 0x10,          /* Operating Mode Information */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_SERVICE_OPTION_INFORMATION                   = 0x11,          /* Service Option Information */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_MULTIPLEX_OPTION_INFORMATION                 = 0x12,          /* Multiplex Option Information */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_SERVICE_CONFIGURATION_INFORMATION            = 0x13,          /* Service Configuration Information */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_CALLED_PARTY_SUBADDRESS                      = 0x14,          /* Called Party Subaddress */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_CALLING_PARTY_SUBADDRESS                     = 0x15,          /* Calling Party Subaddress */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_CONNECTED_SUBADDRESS                         = 0x16,          /* Connected Subaddress */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_POWER_CONTROL_INFORMATION                    = 0x17,          /* Power Control Information */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_IMSI_M                                       = 0x18,          /* IMSI_M */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_IMSI_T                                       = 0x19,          /* IMSI_T */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_CAPABILITY_INFORMATION                       = 0x1A,          /* Capability Information */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_CHANNEL_CONFIGURATION_CAPABILITY_INFORMATION = 0x1B,          /* Channel Configuration Capability Information */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_EXTENDED_MULTIPLEX_OPTION_INFORMATION        = 0x1C,          /* Extended Multiplex Option Information */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_RESERVED_FOR_OBSOLETE_IDENTIFICATION3        = 0x1D,          /* Reserved for Obsolete Identification */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_GEO_LOCATION_INFORMATION                     = 0x1E,          /* Geo-location Information */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_BAND_SUBCLASS_INFORMATION                    = 0x1F,          /* Band Subclass Information */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_GLOBAL_EMERGENCY_CALL                        = 0x20,          /* Global Emergency Call */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_HOOK_STATUS                                  = 0x21,          /* Hook Status */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_QOS_PARAMETERS                               = 0x22,          /* QoS Parameters */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_ENCRYPTION_CAPABILITY                        = 0x23,          /* Encryption Capability */
    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_EXTENDED_RECORD_TYPE_INTERNATIONAL           = 0xFE,          /* Extended Record Type-International */

    CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_XCC_R_DSCH_INFO_RECORD_TYPE_UINT8;

/*****************************************************************************
 枚举名    : CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_ENUM
 协议表格  : C.S0005-A Tsable 3.7.5-1
 ASN.1描述 :
 枚举说明  : f-dsch information record type
*****************************************************************************/
enum CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_ENUM
{
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_DISPLAY                              = 0x01,       /* Display */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_CALLED_PARTY_NUMBER                  = 0x02,       /* Called Party Number */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_CALLING_PARTY_NUMBER                 = 0x03,       /* Calling Party Number */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_CONNECTED_NUMBER                     = 0x04,       /* Connected Number */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_SIGNAL                               = 0x05,       /* Signal */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_MESSAGE_WAITING                      = 0x06,       /* Message Waiting */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_SERVICE_CONFIGURATION                = 0x07,       /* Service Configuration */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_CALLED_PARTY_SUBADDRESS              = 0x08,       /* Called Party Subaddress */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_CALLING_PARTY_SUBADDRESS             = 0x09,       /* Calling Party Subaddress */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_CONNECTED_SUBADDRESS                 = 0x0A,       /* Connected Subaddress */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_REDIRECTING_NUMBER                   = 0x0B,       /* Redirecting Number */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_REDIRECTING_SUBADDRESS               = 0x0C,       /* Redirecting Subaddress */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_METER_PULSES                         = 0x0D,       /* Meter Pulses */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_PARAMETRIC_ALERTING                  = 0x0E,       /* Parametric Alerting */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_LINE_CONTROL                         = 0x0F,       /* Line control */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_EXTENDED_DISPLAY                     = 0x10,       /* Extended Display */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_NON_NEGOTIABLE_SERVICE_CONFIGURATION = 0x13,       /* Non Negotiable Service Configuration */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_MULTIPLE_CHARACTER_EXTENDED_DISPLAY  = 0x14,       /* Multiple Character Extended Display */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_CALL_WAITING_INDICATOR               = 0x15,       /* Call Waiting Indicator */
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_EXTENDED_RECORD_TYPE_INTERNATIONAL   = 0xFE,       /* Extended Record Type International */

    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    :CNAS_XCC_SIGNAL_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : signal中的SIGNAL TYPE类型
*****************************************************************************/
enum CNAS_XCC_SIGNAL_TYPE_ENUM
{
    CNAS_XCC_SIGNAL_TYPE_TONE_SIGNAL     = 0x00,    /* Tone signal */
    CNAS_XCC_SIGNAL_TYPE_ISDN_ALERTING   = 0x01,    /* ISDN Alerting */
    CNAS_XCC_SIGNAL_TYPE_IS_54B_ALERTING = 0x02,    /* IS-54B Alerting */
    CNAS_XCC_SIGNAL_TYPE_RESERVED        = 0x03,    /* Reserved */

    CNAS_XCC_SIGNAL_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_XCC_SIGNAL_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    :CNAS_XCC_ALERT_PITCH_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : signal中的ALERT PITCH类型
*****************************************************************************/
enum CNAS_XCC_ALERT_PITCH_ENUM
{
    CNAS_XCC_ALERT_PITCH_MEDIUM_PITCH = 0x00,    /* Medium pitch (standard alert)  */
    CNAS_XCC_ALERT_PITCH_HIGH_PITCH   = 0x01,    /* High pitch */
    CNAS_XCC_ALERT_PITCH_LOW_PITCH    = 0x02,    /* Low pitch */
    CNAS_XCC_ALERT_PITCH_RESERVED     = 0x03,    /* Reserved */

    CNAS_XCC_ALERT_PITCH_BUTT
};
typedef VOS_UINT8 CNAS_XCC_ALERT_PITCH_ENUM_UINT8;

/*****************************************************************************
 枚举名    :CNAS_XCC_TONE_SIGNAL_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : signal中的Signals (SIGNAL_TYPE = '00')
*****************************************************************************/
enum CNAS_XCC_TONE_SIGNAL_ENUM
{
    CNAS_XCC_TONE_SIGNAL_DIAL_TONE_ON                   = 0x00,    /* Dial tone on:  a continuous 350 Hz tone added to a 440 Hz tone.  */
    CNAS_XCC_TONE_SIGNAL_RING_BACK_TONE_ON              = 0x01,    /* Ring back tone on: a 440 Hz tone added to a 480 Hz tone repeated in a 2s on, 4s off pattern. */
    CNAS_XCC_TONE_SIGNAL_INTERCEPT_TONE_ON              = 0x02,    /* Intercept tone on:  alternating 440 Hz and 620 Hz tones, each on for 250 ms.  */
    CNAS_XCC_TONE_SIGNAL_ABBREVIATED_INTERCEPT          = 0x03,    /* Abbreviated intercept:  alternating 440 Hz and 620 Hz tones, each on for 250 ms, repeated for four seconds.   */
    CNAS_XCC_TONE_SIGNAL_NETWORK_CONGESTION_TONE_ON     = 0x04,    /* Network congestion (reorder) tone on:  a 480 Hz tone added to a 620 Hz tone repeated in a 250 ms on, 250 ms off cycle  */
    CNAS_XCC_TONE_SIGNAL_ABBREVIATED_NETWORK_CONGESTION = 0x05,    /* Abbreviated network congestion (reorder):  a 480 Hz tone added to a 620 Hz tone repeated in a 250 ms on, 250 ms off cycle for four seconds. */
    CNAS_XCC_TONE_SIGNAL_BUSY_TONE_ON                   = 0x06,    /* Busy tone on:  a 480 Hz tone added to a 620 Hz tone repeated in a 500 ms on, 500 ms off cycle. */
    CNAS_XCC_TONE_SIGNAL_CONFIRMS_TONE_ON               = 0x07,    /* Confirm tone on:  a 350 Hz tone added to a 440 Hz tone repeated 3 times in a 100 ms on, 100 ms off cycle. */
    CNAS_XCC_TONE_SIGNAL_ANSWER_TONE_ON                 = 0x08,    /* Answer tone on:  answer tone is not presently used in North American networks. */
    CNAS_XCC_TONE_SIGNAL_CALL_WAITING_TONE_ON           = 0x09,    /* Call waiting tone on: a 300 ms burst of 440 Hz tone */
    CNAS_XCC_TONE_SIGNAL_CALL_PIP_TONE_ON               = 0x0A,    /* Pip tone on: four bursts of 480 Hz tone (0.1 s on, 0.1 s off). */
    CNAS_XCC_TONE_SIGNAL_CALL_TONES_OFF                 = 0x3F,    /* Tones off. */

    CNAS_XCC_TONE_SIGNAL_BUTT
};
typedef VOS_UINT8 CNAS_XCC_TONE_SIGNAL_ENUM_UINT8;

/*****************************************************************************
 枚举名    :CNAS_XCC_ISDN_ALERTING_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : signal中的Signals 取值(SIGNAL_TYPE = '01')
*****************************************************************************/
enum CNAS_XCC_ISDN_ALERTING_ENUM
{
    CNAS_XCC_ISDN_ALERTING_NORMAL_ALERTING           = 0x00,    /* Normal Alerting:  2.0 s on, 4.0 s off, repeating  */
    CNAS_XCC_ISDN_ALERTING_INTERGROUP_ALERTING       = 0x01,    /* Intergroup Alerting:  0.8 s on, 0.4 s off, 0.8 s on, 4.0 s off, repeating  */
    CNAS_XCC_ISDN_ALERTING_SPECIAL_PRIORITY_ALERTING = 0x02,    /* Special/Priority Alerting:  0.4 s on, 0.2 s off, 0.4 s on, 0.2 s off, 0.8 s on, 4.0 s off,repeating */
    CNAS_XCC_ISDN_ALERTING_RESERVED_PATTERN_3        = 0x03,    /* Reserved (ISDN Alerting pattern 3) */
    CNAS_XCC_ISDN_ALERTING_PING_RING                 = 0x04,    /* Ping ring:single burst of 500 ms */
    CNAS_XCC_ISDN_ALERTING_RESERVED_PATTERN_5        = 0x05,    /* Reserved (ISDN Alerting pattern 5)  */
    CNAS_XCC_ISDN_ALERTING_RESERVED_PATTERN_6        = 0x06,    /* Reserved (ISDN Alerting pattern 6)  */
    CNAS_XCC_ISDN_ALERTING_RESERVED_PATTERN_7        = 0x07,    /* Reserved (ISDN Alerting pattern 6)  */
    CNAS_XCC_ISDN_ALERTING_ALERTING_OFF              = 0x0F,    /* Alerting off */

    CNAS_XCC_ISDN_ALERTING_BUTT
};
typedef VOS_UINT8 CNAS_XCC_ISDN_ALERTING_ENUM_UINT8;

/*****************************************************************************
 枚举名    :CNAS_XCC_IS_54B_ALERTING_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : signal中的Signals 取值(SIGNAL_TYPE = '10')
*****************************************************************************/
enum CNAS_XCC_IS_54B_ALERTING_ENUM
{
    CNAS_XCC_IS_54B_ALERTING_NO_TONE                     = 0x00,    /* No Tone:   Off  */
    CNAS_XCC_IS_54B_ALERTING_LONG                        = 0x01,    /* Long:  2.0 s on, 4.0 s off, repeating (standard alert)  */
    CNAS_XCC_IS_54B_ALERTING_SHORT_SHORT                 = 0x02,    /* Short-Short:   0.8 s on, 0.4 s off, 0.8 s on, 4.0 s off, repeating   */
    CNAS_XCC_IS_54B_ALERTING_SHORT_SHORT_LONG            = 0x03,    /* Short-Short-Long:   0.4 s on, 0.2 s off, 0.4 s on, 0.2 s off, 0.8 s on, 4.0 s off, repeating   */
    CNAS_XCC_IS_54B_ALERTING_SHORT_SHORT_2               = 0x04,    /* Short-Short-2:  1.0 s on, 1.0 s off, 1.0 s on, 3.0 s off, repeating */
    CNAS_XCC_IS_54B_ALERTING_SHORT_LONG_SHORT            = 0x05,    /* Short-Long-Short:  0.5 s on, 0.5 s off, 1.0 s on, 0.5 s off, 0.5 s on, 3.0 s off, repeating */
    CNAS_XCC_IS_54B_ALERTING_SHORT_SHORT_SHORT_SHORT     = 0x06,    /* Short-Short-Short-Short:  0.5 s on, 0.5 s off, 0.5 s on, 0.5 s off, 0.5 s on, 0.5 s off, 0.5 s on, 2.5 s off, repeating. */
    CNAS_XCC_IS_54B_ALERTING_PBX_LONG                    = 0x07,    /* PBX Long:  1.0 s on, 2.0 s off, repeating. */
    CNAS_XCC_IS_54B_ALERTING_PBX_SHORT_SHORT             = 0x08,    /* PBX Short-Short:  0.4 s on, 0.2 s off, 0.4 s on, 2.0 off, repeating.  */
    CNAS_XCC_IS_54B_ALERTING_PBX_SHORT_SHORT_LONG        = 0x09,    /* PBX Short-Short-Long:  0.4 s on, 0.2 s off,0.4 s on, 0.2 s off, 0.8 s on, 1.0 s off, repeating.   */
    CNAS_XCC_IS_54B_ALERTING_PBX_SHORT_LONG_SHORT        = 0x0A,    /* PBX Short-Long-Short:  0.4 s on, 0.2 s off, 0.8 s on, 0.2 s off, 0.4 s on, 1.0 s off, repeating.  */
    CNAS_XCC_IS_54B_ALERTING_PBX_SHORT_SHORT_SHORT_SHORT = 0x0B,    /* PBX Short-Short-Short-Short:  0.4 s on, 0.2 s off, 0.4 s on, 0.2 s off, 0.4 s on, 0.2 s off, 0.4 s on, 0.8 s off, repeating.  */
    CNAS_XCC_IS_54B_ALERTING_PBX_PIP_PIP_PIP_PIP         = 0x0C,    /* Pip-Pip-Pip-Pip: 0.1 s on, 0.1 s off, 0.1 s on, 0.1 s off, 0.1 s on, 0.1 s off, 0.1 s on */

    CNAS_XCC_IS_54B_ALERTING_BUTT
};
typedef VOS_UINT8 CNAS_XCC_IS_54B_ALERTING_ENUM_UINT8;



/****************************************************************************
 枚举名    :CNAS_XCC_DECODE_ERRCODE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 解码勾包对应错误码
*****************************************************************************/
enum CNAS_XCC_DECODE_ERRCODE_ENUM
{
    CNAS_XCC_DECODE_ERRCODE_EAWI_IS_NULL_PTR                = 0x00,     /* 解码后EAWI指针为空 */
    CNAS_XCC_DECODE_ERRCODE_AWI_IS_NULL_PTR                 = 0x01,     /* 解码后AWI指针为空 */
    CNAS_XCC_DECODE_ERRCODE_EFWI_IS_NULL_PTR                = 0x02,     /* 解码后FWI指针为空 */
    CNAS_XCC_DECODE_ERRCODE_FWI_IS_NULL_PTR                 = 0x03,     /* 解码后EFWI指针为空 */
    CNAS_XCC_DECODE_ERRCODE_EAWI_RECNUM_NE_NUMINFORECORD    = 0x04,     /* 解码填充后EAWI RECNUM与实际填充的info record个数不一致 */
    CNAS_XCC_DECODE_ERRCODE_AWI_RECNUM_EQ_ZERO              = 0x05,     /* 解码后AWI info record个数为0 */
    CNAS_XCC_DECODE_ERRCODE_EFWI_RECNUM_NE_NUMINFORECORD    = 0x06,     /* 解码填充后EFWI RECNUM与实际填充的info record个数不一致 */
    CNAS_XCC_DECODE_ERRCODE_FWI_RECNUM_EQ_ZERO              = 0x07,     /* 解码后FWI info record个数为0 */
    CNAS_XCC_DECODE_ERRCODE_FNM_IS_NULL_PTR                 = 0x08,     /* 解码后FNM指针为空*/
    CNAS_XCC_DECODE_ERRCODE_SOCM_IS_NULL_PTR                = 0x09,     /* 解码后SOCM指针为空*/
    CNAS_XCC_DECODE_ERRCODE_BDTMFM_IS_NULL_PTR              = 0x0A,     /* If BDTMF M is NULL pointer after decode */

    CNAS_XCC_DECODE_ERRCODE_BUTT
};
typedef VOS_UINT8 CNAS_XCC_DECODE_ERRCODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    :CNAS_XCC_FDSCH_SO_CTRL_FIELD_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : Service Option Control消息中中的FIELD TYPE 取值
*****************************************************************************/
enum CNAS_XCC_FDSCH_SO_CTRL_FIELD_ENUM
{
    CNAS_XCC_FDSCH_SO_CTRL_FIELD_DORMANT_TIMER_CTRL           = 0x03,           /* Dormant Timer Control , FIELD TYPE取值为 '011' */
    CNAS_XCC_FDSCH_SO_CTRL_FIELD_PACKET_ZONE_RECONN_CTRL      = 0x04,           /* Packet Zone Reconnection Control   FIELD TYPE取值为 '100' */
    CNAS_XCC_FDSCH_SO_CTRL_FIELD_BUTT                         = 0xff
};
typedef VOS_UINT8 CNAS_XCC_FDSCH_SO_CTRL_FIELD_ENUM_UINT8;


/*****************************************************************************
 枚举名    :CNAS_XCC_RDSCH_SO_CTRL_FIELD_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : Service Option Control消息中中的FIELD TYPE 取值
*****************************************************************************/
enum CNAS_XCC_RDSCH_SO_CTRL_FIELD_ENUM
{
    CNAS_XCC_RDSCH_SO_CTRL_FIELD_PKT_CON_RESP                 = 0x04,
    CNAS_XCC_RDSCH_SO_CTRL_FIELD_BUTT                         = 0xff
};
typedef VOS_UINT8 CNAS_XCC_RDSCH_SO_CTRL_FIELD_ENUM_UINT8;



enum CNAS_XCC_DECODE_RESULT_ENUM
{
    CNAS_XCC_DECODE_RSLT_SUCCESS        = 0x00,
    CNAS_XCC_DECODE_RSLT_FAILURE        = 0x01,
    CNAS_XCC_DECODE_RSLT_INVALID_FIELD  = 0x02
};
typedef VOS_UINT8 CNAS_XCC_DECODE_RESULT_ENUM_UINT8;

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
结构名    : CNAS_XCC_ORDER_MSG_STRU
协议表格  :
ASN.1描述 :
结构说明  : ORDER消息映射表对应的元素结构
****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucOrder;                                /* ORDER */
    VOS_UINT8                           ucOrdqMin;                              /* ORDQ取值范围的最小值 */
    VOS_UINT8                           ucOrdqMax;                              /* ORDQ取值范围的最大值 */                                 /* ORDQ */
    CNAS_XCC_ORDER_TYPE_ENUM_UINT8      enOrderMsgType;                         /* 具体的order消息类型 */
}CNAS_XCC_ORDER_TO_SPECIFIC_MSG_STRU;

/*****************************************************************************
结构名    : CNAS_XCC_ORDER_MSG_STRU
协议表格  :
ASN.1描述 :
结构说明  : ORDER消息映射表对应的元素结构
****************************************************************************/
typedef struct
{
    VOS_UINT8                                       ucConRef;
    CAS_CNAS_1X_RX_TCH_MSG_TYPE_ENUM_UINT8          enRejRxTchMsgType;
    VOS_UINT8                                       ucRejOrderCode;
    VOS_UINT8                                       ucRejOrdq;
    CNAS_XCC_REV_ORDER_CODE_ENUM_UINT8              enRevOrderCode;
    CNAS_XCC_REV_MS_REJECT_ORDQ_ENUM_UINT8          enRevOrdq;
    VOS_UINT8                                       aucReserved[2];
    VOS_UINT32                                      ulL3PduBitLen;
    VOS_UINT8                                      *pucPdudata;

}CNAS_XCC_REJ_ORDER_INFO_STRU;


/*************************************************************
   建议代码里定义的结构赋值值，最好不要整个结构使用PS_MEM_CPY。
   协议上定义的结构可能是没有4字节对齐
**************************************************************/

/*****************************************************************************
结构名    : CNAS_XCC_INFO_RECS_DISP_STRU
协议表格  :
ASN.1描述 :
结构说明  :information records中dispaly的元素结构
****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDigitNum;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucDigit[CNAS_XCC_MAX_DISPALY_CHARI_OCTET_NUM];
}CNAS_XCC_INFO_RECS_DISP_STRU;

/*****************************************************************************
结构名    : CNAS_XCC_INFO_RECS_CALLED_NUM_STRU
协议表格  :
ASN.1描述 :
结构说明  :information records中called party number的元素结构
****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumberType;
    VOS_UINT8                           ucNumberPlan;
    VOS_UINT8                           ucDigitNum;
    VOS_UINT8                           ucReserved;
    VOS_UINT8                           aucDigit[CNAS_XCC_MAX_CALLED_NUMBER_CHARI_OCTET_NUM];
}CNAS_XCC_INFO_RECS_CALLED_NUM_STRU;

/*****************************************************************************
结构名    : CNAS_XCC_INFO_RECS_CALLING_NUM_STRU
协议表格  :
ASN.1描述 :
结构说明  :information records中calling party number的元素结构
****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumberType;
    VOS_UINT8                           ucNumberPlan;
    VOS_UINT8                           ucPi;
    VOS_UINT8                           ucSi;
    VOS_UINT8                           ucDigitNum;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucDigit[CNAS_XCC_MAX_CALLING_NUMBER_CHARI_OCTET_NUM];
}CNAS_XCC_INFO_RECS_CALLING_NUM_STRU;

/*****************************************************************************
结构名    : CNAS_XCC_INFO_RECS_CON_NUM_STRU
协议表格  :
ASN.1描述 :
结构说明  :information records中connected number的元素结构
****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumberType;
    VOS_UINT8                           ucNumberPlan;
    VOS_UINT8                           ucPi;
    VOS_UINT8                           ucSi;
    VOS_UINT8                           ucDigitNum;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucDigit[CNAS_XCC_MAX_CONNECTED_NUMBER_CHARI_OCTET_NUM];
}CNAS_XCC_INFO_RECS_CON_NUM_STRU;

/*****************************************************************************
结构名    : CNAS_XCC_INFO_RECS_SIGNAL_STRU
协议表格  :
ASN.1描述 :
结构说明  :information records中signal的元素结构
****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSignalType;
    VOS_UINT8                           ucAlertPitch;
    VOS_UINT8                           ucSignal;
    VOS_UINT8                           ucReserved;
}CNAS_XCC_INFO_RECS_SIGNAL_STRU;

/*****************************************************************************
结构名    : CNAS_XCC_INFO_RECS_REDIR_NUM_STRU
协议表格  :
ASN.1描述 :
结构说明  :information records中redirecting number的元素结构
****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucExtensionBit1;
    VOS_UINT8                           ucNumbertype;
    VOS_UINT8                           ucNumberPlan;
    VOS_UINT8                           ucExtensionBit2;
    VOS_UINT8                           ucExtensionBit2Present;
    VOS_UINT8                           ucPi;
    VOS_UINT8                           ucPiPresent;
    VOS_UINT8                           ucSi;
    VOS_UINT8                           ucSiPresent;
    VOS_UINT8                           ucExtensionBit3;
    VOS_UINT8                           ucExtensionBit3Present;
    VOS_UINT8                           ucRedirectionReason;
    VOS_UINT8                           ucRedirectionReasonPresent;
    VOS_UINT8                           ucDigitNum;
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucDigit[CNAS_XCC_MAX_REDIRECTING_NUMBER_CHARI_OCTET_NUM];
}CNAS_XCC_INFO_RECS_REDIR_NUM_STRU;

/*****************************************************************************
结构名    : CNAS_XCC_INFO_RECS_LINE_CTR_STRU
协议表格  :
ASN.1描述 :
结构说明  :information records中line control的元素结构
****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPolarityIncluded;
    VOS_UINT8                           ucToggleMode;
    VOS_UINT8                           ucToggleModePresent;
    VOS_UINT8                           ucReversePolarity;
    VOS_UINT8                           ucReversePolarityPresent;
    VOS_UINT8                           ucPowerDenialTime;
    VOS_UINT8                           aucReserved[2];
}CNAS_XCC_INFO_RECS_LINE_CTR_STRU;

/*****************************************************************************
结构名    : CNAS_XCC_INFO_RECS_EXTDISP_DATA_STRU
协议表格  :
ASN.1描述 :
结构说明  :Extented dispaly中data的元素结构
****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDispalyTag;
    VOS_UINT8                           ucDispalyLen;
    VOS_UINT8                           ucDigitNum;
    VOS_UINT8                           ucReserved;
    VOS_UINT8                           aucDigit[CNAS_XCC_MAX_EXTENDED_DISPLAY_CHARI_OCTET_NUM];
} CNAS_XCC_INFO_RECS_EXTDISP_DATA_STRU;

/*****************************************************************************
结构名    : CNAS_XCC_INFO_RECS_EXTDISP_STRU
协议表格  :
ASN.1描述 :
结构说明  :information records中Extented dispaly的元素结构
****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucExtDisplayInd;
    VOS_UINT8                               ucDispalyType;
    VOS_UINT8                               ucNumExtDispData;
    VOS_UINT8                               ucReserved;
    CNAS_XCC_INFO_RECS_EXTDISP_DATA_STRU    astExtDispData[CNAS_XCC_MAX_EXT_DISPLAY_DATA_NUM];
}CNAS_XCC_INFO_RECS_EXTDISP_STRU;

/*****************************************************************************
结构名    : CNAS_XCC_INFO_RECS_MSG_WAITING_STRU
协议表格  :
ASN.1描述 :
结构说明  :information records中message waiting的元素结构
****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucMsgCnt;
    VOS_UINT8                               aucReserved[3];
}CNAS_XCC_INFO_RECS_MSG_WAITING_STRU;


/*****************************************************************************
 结构名    : CNAS_XCC_INFO_RECS_STRU
 结构说明  : information records消息结构
  1.日    期   : 2014年11月10日
    作    者   : y00307564
    修改内容   : 1X SS Project 新增
*****************************************************************************/
typedef struct
{
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_ENUM_UINT32            enInfoRecsType;
    union
    {
        CNAS_XCC_INFO_RECS_DISP_STRU                        stDisp;
        CNAS_XCC_INFO_RECS_CALLED_NUM_STRU                  stCalledNum;
        CNAS_XCC_INFO_RECS_CALLING_NUM_STRU                 stCallingNum;
        CNAS_XCC_INFO_RECS_CON_NUM_STRU                     stConNum;
        CNAS_XCC_INFO_RECS_SIGNAL_STRU                      stSignal;
        CNAS_XCC_INFO_RECS_REDIR_NUM_STRU                   stRedirNum;
        CNAS_XCC_INFO_RECS_LINE_CTR_STRU                    stLineCtr;
        CNAS_XCC_INFO_RECS_EXTDISP_STRU                     stExtDisp;
        CNAS_XCC_INFO_RECS_MSG_WAITING_STRU                 stMsgWaiting;
    }u;

}CNAS_XCC_INFO_RECS_STRU;

typedef struct
{
    VOS_UINT8                           ucRecordType;
    VOS_UINT8                           ucRecordLen;
    VOS_UINT8                           aucReserved[2];
    CNAS_XCC_INFO_RECS_STRU             stInfoRecs;
}CNAS_XCC_INFO_RECS_DATA_STRU;


/*****************************************************************************
 结构名    : CNAS_XCC_AWIM_STRU
 结构说明  : AWIM消息结构
  1.日    期   : 2014年11月12日
    作    者   : l00256032
    修改内容   : 1X SS Project 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumInfoRecs;
    VOS_UINT8                           aucReserved[3];
    CNAS_XCC_INFO_RECS_DATA_STRU        astInfoRecsData[CNAS_XCC_MAX_AWIM_EAWIM_INFO_RECO_NUM];
}CNAS_XCC_AWIM_STRU;

/*****************************************************************************
 结构名    : CNAS_XCC_EAWIM_STRU
 结构说明  : EAWIM消息结构
  1.日    期   : 2014年10月15日
    作    者   : w00242748
    修改内容   : 新增
  2.日    期   : 2014年11月10日
    作    者   : y00307564
    修改内容   : 1X SS Project 修改
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucConRef;           /* 对应协议字段CON_REF */
    VOS_UINT8                           ucConRefPresent;    /* 对应协议字段CON_REF_Present */
    VOS_UINT8                           ucConRefIncl;       /* 对应协议字段CON_REF_INCL */
    VOS_UINT8                           ucRecNum;           /* 对应协议字段NUM_REC */
    VOS_UINT8                           ucNumInfoRecs;      /* 实际的info record个数 */
    VOS_UINT8                           aucReserved[3];
    CNAS_XCC_INFO_RECS_DATA_STRU        astInfoRecsData[CNAS_XCC_MAX_AWIM_EAWIM_INFO_RECO_NUM];
}CNAS_XCC_EAWIM_STRU;

/*****************************************************************************
 结构名    : CNAS_XCC_EFWIM_STRU
 结构说明  : EFWIM消息结构
  1.日    期   : 2014年10月15日
    作    者   : w00242748
    修改内容   : 新增
  2.日    期   : 2014年11月10日
    作    者   : y00307564
    修改内容   : 1X SS Project 修改
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucConRef;           /* 对应协议字段CON_REF */
    VOS_UINT8                           ucConRefPresent;    /* 对应协议字段CON_REF_Present */
    VOS_UINT8                           ucConRefIncl;       /* 对应协议字段CON_REF_INCL */
    VOS_UINT8                           ucRecNum;           /* 对应协议字段NUM_REC */
    VOS_UINT8                           ucNumInfoRecs;      /* 实际的info record个数 */
    VOS_UINT8                           aucReserved[3];
    CNAS_XCC_INFO_RECS_DATA_STRU        astInfoRecsData[CNAS_XCC_MAX_FWIM_EFWIM_INFO_RECO_NUM];
}CNAS_XCC_EFWIM_STRU;

/*****************************************************************************
 结构名    : CNAS_XCC_FWIM_STRU
 结构说明  : FWIM消息结构
  1.日    期   : 2014年11月10日
    作    者   : y00307564
    修改内容   : 1X SS Project 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumInfoRecs;
    VOS_UINT8                           aucReserved[3];
    CNAS_XCC_INFO_RECS_DATA_STRU        astInfoRecsData[CNAS_XCC_MAX_FWIM_EFWIM_INFO_RECO_NUM];
}CNAS_XCC_FWIM_STRU;

/*****************************************************************************
 结构名    : CNAS_XCC_ORDERS_STRU
 结构说明  : ORDERS消息结构
  1.日    期   : 2014年10月15日
    作    者   : w00242748
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulOrderDesc;  /* 对应协议字段ORDER_DESC,类型unsigned long */
    VOS_UINT32 ulNNNN;        /* 对应协议字段NNNN,类型unsigned long */
    VOS_UINT8  ucOrder;       /* 对应协议字段ORDER */
    VOS_UINT8  ucOrdq;        /* 对应协议字段ORDQ */
    VOS_UINT8  aucReserve[2];

    /* c_F_Orders_parameters parameters; */
}CNAS_XCC_ORDERS_STRU;

/*****************************************************************************
 结构名    : CNAS_XCC_ORDRM_STRU
 结构说明  : ORDER消息结构
  1.日    期   : 2014年10月15日
    作    者   : w00242748
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucUseTime;              /* 对应协议字段USE_TIME */
    VOS_UINT8               ucActionTime;           /* 对应协议字段ACTION_TIME */
    VOS_UINT8               ucConRefIncl;           /* 对应协议字段CON_REF_INCL */
    VOS_UINT8               ucConRefInclPresent;    /* 对应协议字段CON_REF_INCL_Present */
    VOS_UINT8               ucConRef;               /* 对应协议字段CON_REF */
    VOS_UINT8               ucConRefPresent;        /* 对应协议字段CON_REF_Present */
    /* 协议定义的结构并未4字节对齐 */
    VOS_UINT8               aucReserve[2];

    CNAS_XCC_ORDERS_STRU    stOrder;
}CNAS_XCC_ORDRM_STRU;

/*****************************************************************************
 结构名    : CNAS_XCC_FNM_STRU
 结构说明  : FNM消息结构
  1.日    期   : 2014年11月18日
    作    者   : h00246512
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsRelease;
    VOS_UINT8                           ucNumInfoRecs;
    VOS_UINT8                           aucReserved[2];
    CNAS_XCC_INFO_RECS_DATA_STRU        astInfoRecsData[CNAS_XCC_MAX_FNM_INFO_RECO_NUM];
}CNAS_XCC_FNM_STRU;

/*****************************************************************************
 结构名    : CNAS_XCC_SOCM_STRU
 结构说明  : SOCM消息结构
  1.日    期   : 2014年11月18日
    作    者   : h00246512
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSo;
    VOS_UINT8                           ucActionTime;
    VOS_UINT8                           ucConRef;
    VOS_UINT8                           ucCtlRecLen;
    VOS_UINT8                           ucUseTime;
    VOS_UINT16                          usBitLen;                               /* 参考解码函数注释:Variable size; bits needed 64 */
    VOS_UINT8                           aucData[CNAS_XCC_MAX_SOCM_FIELD_DATA_LEN];
}CNAS_XCC_SOCM_STRU;



typedef struct
{
    VOS_UINT8                           ucConRef;                                   /* 当前呼叫的呼叫ID */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           ucDigitNum;                                 /**<  Digit number */
    VOS_UINT8                           aucDigit[CNAS_XCC_MAX_BURST_DTMF_NUM];      /**<  DTMF digits */
    VOS_UINT32                          ulOnLength;                                 /**<  refers to S.0005 3.7.3.3.2.9 */
    VOS_UINT32                          ulOffLength;                                /**<  refers to S.0005 3.7.3.3.2.9 */
}CNAS_XCC_SEND_BURST_DTMF_STRU;
/*****************************************************************************
 结构名    : XCC_MMA_1X_CALL_STATE_MAP_STRU
 结构说明  : 1x call state 的对应结构
  1.日    期   : 2014年9月22日
    作    者   : c00294324
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    CNAS_CCB_1X_CALL_STATE_ENUM_UINT8           enCcbCallState;
    XCC_MMA_1X_CALL_STATE_ENUM_UINT8            enXccMmaCallState;
    VOS_UINT8                                   aucRslv[2];
}XCC_MMA_1X_CALL_STATE_MAP_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT8 CNAS_XCC_IsConcurrentSupported(VOS_VOID);

VOS_VOID CNAS_XCC_ConvertSoToServiceType(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                  enSo,
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32                      *penServiceType
);
VOS_VOID CNAS_XCC_ConvertSoToCasSessionType(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                  enSo,
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                   *penCasSessionType
);

VOS_VOID CNAS_XCC_ConvertSoToMtcSessionType(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                  enSo,
    MTC_SESSION_TYPE_ENUM_UINT8                            *penMtcSessionType
);
VOS_UINT32 CNAS_XCC_ConvertTerminateReasonToTafCause(
    CAS_CNAS_1X_TERMINATE_REASON_ENUM_UINT8                 enCasCause
);

VOS_UINT32 CNAS_XCC_ConvertEstReasonToTafCause(
    CAS_CNAS_1X_EST_RSLT_ENUM_UINT8                 enCasCause
);

VOS_VOID CNAS_XCC_ConvertTafHangupReasonToCas(
    TAF_XCC_END_REASON_ENUM_UINT8       tafEndReason,
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8  *penReason
);

VOS_UINT32 CNAS_XCC_EncodeDschMsg(
    CAS_CNAS_1X_TX_TCH_MSG_TYPE_ENUM_UINT8           usMsgTag,
    c_r_dsch                                        *pstRDschMsg,
    VOS_UINT8                                       *pucBuff,
    VOS_UINT32                                      *pulDataLen
);

VOS_UINT32 CNAS_XCC_EncodeTxTchConnectOrderMsg(
    VOS_UINT8                           ucConRef,
    VOS_UINT8                          *pucPdudata,
    VOS_UINT32                         *pulL3PduBit
);

VOS_UINT32 CNAS_XCC_EncodeTxTchMSRejectOrderMsg(
    CNAS_XCC_REJ_ORDER_INFO_STRU                   *pstRejInfo
);
VOS_UINT32 CNAS_XCC_FillRDschMSRejectInvalidMsg(
    c_r_dsch                                       *pstMsgRDsch,
    CNAS_XCC_REJ_ORDER_INFO_STRU                   *pstRejInfo
);
VOS_VOID CNAS_XCC_RestartTimer(
    VOS_UINT8                           ucConnectId,
    CNAS_XCC_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulTimerLen
);
VOS_VOID CNAS_XCC_StartTimer(
    VOS_UINT8                           ucConnectId,
    CNAS_XCC_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulTimerLen
);
VOS_VOID CNAS_XCC_StopTimer(
    VOS_UINT8                           ucConnectId,
    CNAS_XCC_TIMER_ID_ENUM_UINT32       enTimerId
);

VOS_UINT32 CNAS_XCC_DecodeOrderMsg(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd,
    CNAS_XCC_ORDRM_STRU                *pstOrdrm
);

VOS_UINT32 CNAS_XCC_GetOrderSpecificMsgType(
    CNAS_XCC_ORDERS_STRU                *pstOrderMsg,
    CNAS_XCC_ORDER_TYPE_ENUM_UINT8      *penOrderMsgType
);
VOS_UINT32 CNAS_XCC_DecodeServiceOptionCtrlMsg(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd,
    VOS_UINT8                          *pucSoCtrlMsgData,
    VOS_UINT8                          *pucConRef
);


VOS_VOID CNAS_XCC_FillDecodeEAWIMRecords(
    c_f_dsch_EAWIM_RECs                *pstEAWIMInfoRecords,
    CNAS_XCC_EAWIM_STRU                *pstEAWIM
);

VOS_UINT32 CNAS_XCC_DecodeExtendedAlertWithInformationMsg(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd,
    CNAS_XCC_EAWIM_STRU                *pstEAWIM
);

VOS_UINT32 CNAS_XCC_DecodeExtendedFlashWithInformationMsg(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd,
    CNAS_XCC_EFWIM_STRU                *pstEFWIM
);

VOS_UINT32 CNAS_XCC_EncodeFlashWithInformationMsgWithFlashReq(
    VOS_UINT8                           ucDigitNum,
    VOS_UINT8                          *pucDigit,
    VOS_UINT8                          *pucPdudata,
    VOS_UINT32                         *pulL3PduBitLen
);

VOS_UINT32 CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithFlashReq(
    VOS_UINT8                           ucConRef,
    VOS_UINT8                           ucDigitNum,
    VOS_UINT8                          *pucDigit,
    VOS_UINT8                          *pucPdudata,
    VOS_UINT32                         *pulL3PduBitLen
);


extern VOS_UINT32 CNAS_XCC_ConvertDtmfMinInterDigitIntervalToDtmfOffLength(
    VOS_UINT32                          ulDtmfMinInterDigitInterval,
    VOS_UINT8                          *pucDtmfOffLen
);

extern VOS_UINT32 CNAS_XCC_ConvertDtmfPulseWidthCodeToDtmfOnLength(
    VOS_UINT32                          ulDtmfPulseWidth,
    VOS_UINT8                          *pucDtmfOnLen
);

extern VOS_UINT32 CNAS_XCC_DecodeFlashWithInformationMsg(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd,
    CNAS_XCC_FWIM_STRU                 *pstFWIM
);

extern VOS_VOID CNAS_XCC_FillDecodeEFWIMRecords(
    c_f_dsch_EFWIM_RECs                *pstEFWIMInfoRecords,
    CNAS_XCC_EFWIM_STRU                *pstEFWIM
);
extern VOS_VOID CNAS_XCC_FillDecodeFWIMRecords(
    c_f_dsch_FWIM_INFO_RECORDs         *pstFWIMInfoRecords,
    CNAS_XCC_FWIM_STRU                 *pstFWIM
);

extern VOS_UINT32 CNAS_XCC_FillDecodeInfoRecs(
    c_F_InformationRecords             *pstInformationRecords,
    CNAS_XCC_INFO_RECS_STRU            *pstInfoRecs
);

extern VOS_UINT32 CNAS_XCC_FillDecodeInfoRecsDisp(
    c_InfoRec_Display                  *pstInfoRecDsip,
    CNAS_XCC_INFO_RECS_DISP_STRU       *pstXccInfoRecsDsip
);
extern VOS_UINT32 CNAS_XCC_FillDecodeInfoRecsCalledNum(
    c_InfoRec_Called_Party_Number      *pstInfoRecCalledNum,
    CNAS_XCC_INFO_RECS_CALLED_NUM_STRU *pstXccInfoRecsCalledNum
);

extern VOS_UINT32 CNAS_XCC_FillDecodeInfoRecsCallingNum(
    c_InfoRec_Calling_Party_Number                         *pstInfoRecCallingNum,
    CNAS_XCC_INFO_RECS_CALLING_NUM_STRU                    *pstXccInfoRecsCallingNum
);

extern VOS_UINT32 CNAS_XCC_FillDecodeInfoRecsConnNum(
    c_InfoRec_Connected_Number         *pstInfoRecConnNum,
    CNAS_XCC_INFO_RECS_CON_NUM_STRU    *pstXccInfoRecsConnNum
);

extern VOS_UINT32 CNAS_XCC_FillDecodeInfoRecsSignal(
    c_InfoRec_Signal                   *pstInfoRecSignal,
    CNAS_XCC_INFO_RECS_SIGNAL_STRU     *pstXccInfoRecsSignal
);

extern VOS_UINT32 CNAS_XCC_FillDecodeInfoRecsRedirNum(
    c_InfoRec_Redirecting_Number       *pstInfoRecRedirNum,
    CNAS_XCC_INFO_RECS_REDIR_NUM_STRU  *pstXccInfoRecsRedirNum
);

extern VOS_UINT32 CNAS_XCC_FillDecodeInfoRecsLineCtr(
    c_InfoRec_Line_Control             *pstInfoRecLineCtr,
    CNAS_XCC_INFO_RECS_LINE_CTR_STRU   *pstXccInfoRecsLineCtr
);

extern VOS_UINT32 CNAS_XCC_FillDecodeInfoRecsExtDisp(
    c_InfoRec_Extended_Display         *pstInfoRecExtDsip,
    CNAS_XCC_INFO_RECS_EXTDISP_STRU    *pstXccInfoRecsExtDsip
);

extern VOS_UINT32  CNAS_XCC_AsciiToBcdCode(
    VOS_CHAR                            cAsciiCode,
    VOS_UINT8                          *pucBcdCode
);

extern VOS_UINT32  CNAS_XCC_ConvertBcdCodeToDtmfKey(
    VOS_UINT8                           ucBcdCode,
    VOS_UINT8                          *pucAsciiCode
);

VOS_UINT32 CNAS_XCC_GetDigitAndSwitchFromORDQ(
    VOS_UINT8                           ucOrdq,
    VOS_UINT8                          *pucDigit,
    VOS_UINT8                          *pucSwitch
);

extern VOS_UINT32 CNAS_XCC_EncodeSendBurstDTMFMsg(
    XCALL_XCC_BURST_DTMF_REQ_STRU      *pstXcallBurstDTMFReq,
    VOS_UINT8                          *pucPdudata,
    VOS_UINT32                         *pulL3PduBitLen
);
extern VOS_UINT32  CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList(
    CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_ENUM_UINT32            enInfoRecsType,
    VOS_UINT8                                               ucNumInfoRecs,
    CNAS_XCC_INFO_RECS_DATA_STRU                           *pstInfoRecsData,
    VOS_UINT8                                              *pucIndex
);

extern VOS_UINT32 CNAS_XCC_DecodeAlertWithInformationMsg(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd,
    CNAS_XCC_AWIM_STRU                 *pstAWIM
);

extern VOS_VOID CNAS_XCC_FillDecodeAWIMRecords(
    c_f_dsch_AWIM_INFO_RECORDs         *pstAWIMInfoRecords,
    CNAS_XCC_AWIM_STRU                 *pstAWIM
);

VOS_UINT32 CNAS_XCC_DecodeFeatureNotificationMsg(
    CAS_CNAS_1X_CSCH_DATA_IND_STRU     *pstCschDataInd,
    CNAS_XCC_FNM_STRU                  *pstFNM
);
VOS_UINT32 CNAS_XCC_DecodeServiceOptionControlMsg(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd,
    CNAS_XCC_SOCM_STRU                 *pstSOCM
);
VOS_UINT32 CNAS_XCC_VoiceSoCtrlMsgParaCheck(
    CNAS_XCC_SOCM_STRU                 *pstSOCM
);
VOS_UINT32 CNAS_XCC_DataSoCtrlMsgParaCheck(
    CNAS_XCC_SOCM_STRU                 *pstSOCM
);
VOS_UINT32 CNAS_XCC_FillDecodeInfoRecsMsgWaiting(
    c_InfoRec_Message_Waiting              *pstInfoRecMsgWaiting,
    CNAS_XCC_INFO_RECS_MSG_WAITING_STRU    *pstXccInfoRecsMsgWaiting
);

VOS_UINT32 CNAS_XCC_EncodeFlashWithInformationMsgWithEmergencyCallReq(
    XCC_XCALL_DIGIT_MODE_ENUM_UINT8                         enDigitMode,
    XCC_XCALL_CALLED_PARTY_NUM_INFO_STRU                   *pstCalledPartyNum,
    VOS_UINT8                                              *pucPdudata,
    VOS_UINT32                                             *pulL3PduBitLen
);

VOS_UINT32 CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithEmergencyCallReq(
    VOS_UINT8                                               ucConRef,
    XCC_XCALL_DIGIT_MODE_ENUM_UINT8                         enDigitMode,
    XCC_XCALL_CALLED_PARTY_NUM_INFO_STRU                   *pstCalledPartyNum,
    VOS_UINT8                                              *pucPdudata,
    VOS_UINT32                                             *pulL3PduBitLen
);
VOS_VOID CNAS_XCC_FillDecodeFNMRecords(
    c_f_csch_FNM_INFO_RECORDs          *pstFNMInfoRecords,
    CNAS_XCC_FNM_STRU                  *pstFNM
);

VOS_UINT32 CNAS_XCC_EncodeCschMsg(
    CAS_CNAS_1X_TX_COMMON_MSG_TYPE_ENUM_UINT8        enMsgTag,
    c_r_csch_mini6                                  *pstRDschMsg,
    VOS_UINT8                                       *pucBuff,
    VOS_UINT32                                      *pulBitDataLen
);
VOS_UINT32 CNAS_XCC_EncodeCschMsAckOrderMsg(
    VOS_UINT8                          *pucPdudata,
    VOS_UINT32                         *pulL3PduBitLen
);
VOS_UINT32 CNAS_XCC_EncodeServiceOptionCtrlMsg(
    APS_XCC_PZID_INFO_NTF_STRU         *pstPzidInfo,
    VOS_UINT8                           ucConRef,
    VOS_UINT8                          *pucPdudata,
    VOS_UINT32                         *pulL3PduBitLen
);
VOS_UINT8 CNAS_XCC_IsL3ErrReOrigCount(VOS_VOID);

VOS_UINT8 CNAS_XCC_ConvertL3ErrReOrigCount(
    VOS_UINT8                           ReOrigCount
);

VOS_VOID CNAS_XCC_SendComDschDataRejectOrder(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU                         *pst1xDschDataInd,
    VOS_UINT8                                               ucConRef,
    CNAS_XCC_REV_MS_REJECT_ORDQ_ENUM_UINT8                  enRejectRevOrdq
);

CNAS_XCC_DECODE_RESULT_ENUM_UINT8 CNAS_XCC_DecodeSndBurstDtmfMsg(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd,
    CNAS_XCC_SEND_BURST_DTMF_STRU      *pstSndBurstDtmfMsg
);

VOS_VOID CNAS_XCC_DecodeConRefFromFDschOrdmMsg(
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                          usMsgDataLen,
    VOS_UINT8                          *pucConRefIncl,
    VOS_UINT8                          *pucConRef
);

VOS_UINT8 CNAS_XCC_GetAddRecLenFromOrderMsg(
    VOS_UINT8                          *pucMsgData
);

VOS_UINT32 CNAS_XCC_EncodeSendContDTMFToneOrder(
    XCALL_XCC_SEND_CONT_DTMF_REQ_STRU  *pstContDtmfMsg,
    VOS_UINT8                          *pucPdudata,
    VOS_UINT32                         *pulL3PduBitLen,
    VOS_UINT8                           ucIndex
);

VOS_UINT32 CNAS_XCC_ConvertDtmfOffLengthToDtmfMinInterDigitInterval(
    VOS_UINT8                           ucDtmfOffLen,
    VOS_UINT32                         *pulDtmfMinInterDigitInterval
);

VOS_UINT32 CNAS_XCC_ConvertDtmfOnLengthToDtmfPulseWidthCode(
    VOS_UINT8                           ucDtmfOnLen,
    VOS_UINT32                         *pulDtmfPulseWidth
);

VOS_UINT8 CNAS_XCC_Convert1XcallState(
    CNAS_CCB_1X_CALL_STATE_ENUM_UINT8   enCcb1XCallState
);

VOS_UINT8 CNAS_XCC_IsPagingRspSo33InNoDataSrv(VOS_VOID);

VOS_VOID CNAS_XCC_SndSessionBeginNtf(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                  enSo
);

VOS_VOID CNAS_XCC_SndSessionEndNtf(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                  enSo
);
#endif /* #if (FEATURE_ON == FEATURE_UE_MODE_CDMA) */




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

#endif /* end of __CNAS_XSD_COM_FUNC_H__ */
