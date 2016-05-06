
#ifndef __MNMSGAPI_H__
#define __MNMSGAPI_H__


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "product_config.h"
#include "TafTypeDef.h"
#include "AtMnInterface.h"

#include "TafNvInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
/* Deleted MN_MSG_7BIT_MASK */
#define MN_MSG_RP_REPORT_CAUSE_VALUE_MASK                   (0xff)
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */


/*------------------------TP-MTI(TP-Message-Type-Indicator,Bit 0 and 1)---------*/
/*------------------------------------------------------------------------------*/
#define MN_MSG_TP_MTI_DELIVER                               (0x00)              /* SMS-DELIVER       */
#define MN_MSG_TP_MTI_DELIVER_REPORT                        (0x00)              /* SMS-DELIVER-REPORT*/
#define MN_MSG_TP_MTI_STATUS_REPORT                         (0x02)              /* SMS-STATUS-REPORT */
#define MN_MSG_TP_MTI_COMMAND                               (0x02)              /* SMS-COMMAND       */
#define MN_MSG_TP_MTI_SUBMIT                                (0x01)              /* SMS-SUBMIT        */
#define MN_MSG_TP_MTI_SUBMIT_REPORT                         (0x01)              /* SMS-SUBMIT-REPORT */
#define MN_MSG_TP_MTI_RESERVE                               (0x03)              /* RESERVE           */
/*------------------------------------------------------------------------------*/

#define MN_MSG_TIMESTAMP_SIGN_MASK                          (0x08)
#define MN_MSG_MAX_TIMEZONE_VALUE                           (48)

#define MN_MSG_NVIM_ITEM_ACTIVE                             (1)                 /*NVIM项已激活*/
#define MN_MSG_NVIM_ITEM_INACTIVE                           (0)                 /*NVIM项未激活*/


typedef  VOS_UINT8   MN_MSG_ADDR_NUM_TYPE_T;
#define MN_MSG_MIN_BCD_NUM_LEN                              (2 - 1)
#define MN_MSG_MAX_BCD_NUM_LEN                              (11 - 1)

typedef VOS_UINT8    MN_MSG_OPER_TYPE_T;
#define MN_MSG_OPER_SET                                     0
#define MN_MSG_OPER_GET                                     1
#define MN_MSG_OPER_CHANGED                                 2


#define MN_MSG_CMGD_PARA_MAX_LEN                            16
/*Content of TPDU*/
#define MN_MSG_MAX_7_BIT_LEN                                160
#define MN_MSG_MAX_8_BIT_LEN                                140
#define MN_MSG_MAX_LEN                                      255
#define MN_MAX_ASCII_ADDRESS_NUM                            20
#define MSG_MAX_TPDU_MSG_LEN                                232

#define MN_MSG_ABSOLUTE_TIMESTAMP_LEN                       0x07

/*->f62575*/
#define MN_MSG_MAX_UDH_EO_DATA_LEN                          131
#define MN_MSG_MAX_UDH_EO_NUM                               7
/*<-f62575*/

#define MN_MSG_ACTIVE_MESSAGE_MAX_URL_LEN                   (160)
#define MN_MSG_ACTIVE_MESSAGE_PARA_LEN                      ((MN_MSG_ACTIVE_MESSAGE_MAX_URL_LEN) + 8)

#define MN_GET_ADDRTYPE(ucAddrType, enNumType, enNumPlan)                           \
                        ((ucAddrType) = 0x80 | (VOS_UINT8)((enNumType) << 4) | enNumPlan)

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


#define TAF_CBA_MAX_CBPAGE_LEN                              (88)                /* 广播短消息一页的最大长度 */
#define TAF_CBA_MAX_CBDATA_LEN                              (82)                /* 广播短消息页数据区的最大长度 */
#define TAF_CBA_MAX_CBMPAGE_NUM                             (15)                /* 广播短消息最多包含的页数 */
#define TAF_CBA_MAX_CBMID_RANGE_NUM                         (100)               /* 用户最多可输入的消息ID范围个数，在接受模式下还要受到CBMIR文件大小限制 */
#define TAF_CBA_MAX_LABEL_NUM                               (16)                /* 用户最多可输入的描述信息的长度，单位BYTE */
#define TAF_CBA_MAX_RAW_CBDATA_LEN                          (93)                /* 广播短消息页数据区的最大长度 */


#endif

/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
/* DCS GROUP为1，则CB DATA字段携带语言类型，占2个7位位组长度 */
#define TAF_MSG_CBA_LANG_LENGTH                             (2)
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

/*****************************************************************************
  3 类型定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : MN_MSG_MO_DOMAIN_CUSTOMIZE_TYPE
 结构说明  : 短信发送域定制类型
             0: 通用的短信发送域定制，自动选择可用的发送域，不受+CGSMS命令的限制
             1: 短信发送流程严格按照+CGSMS命令的配置执行；

  1.日    期   : 2013年01月04日
    作    者   : f62575
    修改内容   : 创建
*****************************************************************************/
enum MN_MSG_MO_DOMAIN_CUSTOMIZE_TYPE
{
    MN_MSG_MO_DOMAIN_CUSTOMIZE_GLOBAL,
    MN_MSG_MO_DOMAIN_CUSTOMIZE_PROTOCOL,
    MN_MSG_MO_DOMAIN_CUSTOMIZE_BUTT
};
typedef VOS_UINT8 MN_MSG_MO_DOMAIN_CUSTOMIZE_TYPE_UINT8;

/* Added by f62575 for AT Project，2011-10-03,  Begin*/
enum MN_MSG_DATE_INVALID_TYPE_ENUM
{
    MN_MSG_DATE_INVALID_YEAR            = 0x01,
    MN_MSG_DATE_INVALID_MONTH           = 0x02,
    MN_MSG_DATE_INVALID_DAY             = 0x04,
    MN_MSG_DATE_INVALID_HOUR            = 0x08,
    MN_MSG_DATE_INVALID_MINUTE          = 0x10,
    MN_MSG_DATE_INVALID_SECOND          = 0x20,
    MN_MSG_DATE_INVALID_MAX
};
typedef VOS_UINT8  MN_MSG_DATE_INVALID_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MN_MSG_STUB_TYPE_ENUM
 枚举说明  : 短信相关桩类型
            0: efsms文件不可用
            1: efsms文件容量为1
            2: efsmss溢出标志清除操作；
            3: efsmsp文件获取无响应；
            4: efsms文件获取无响应；
            5: 触发STK短信发送，STK短信内容需要压缩编码
            6: 触发STK短信发送，STK短信长度超过标准短信长度，需要分段发送；
            7: 去使能短信重发功能；
            8: 设置CLASS0类短信的定制配置；
            9: 设置PP DOWNLOAD操作失败，并指定失败原因值
           10: PS域短信连发开关
           11: 触发短信自动回复功能
*****************************************************************************/
enum MN_MSG_STUB_TYPE_ENUM
{
    MN_MSG_STUB_TYPE_SET_EFSMS_INAVAILABLE                  = 0,
    MN_MSG_STUB_TYPE_SET_EFSMS_CAPACITY                     = 1,
    MN_MSG_STUB_TYPE_EFSMSS_RESET                           = 2,
    MN_MSG_STUB_TYPE_EFSMSP_GET_NO_RESPONSE                 = 3,
    MN_MSG_STUB_TYPE_EFSMS_GET_NO_RESPONSE                  = 4,
    MN_MSG_STUB_TYPE_STK_8BIT_TO_7BIT                       = 5,
    MN_MSG_STUB_TYPE_STK_SEGMENT                            = 6,
    MN_MSG_STUB_TYPE_DISABLE_MO_RETRY                       = 7,
    MN_MSG_STUB_TYPE_CLASS0_TAILOR                          = 8,
    MN_MSG_STUB_TYPE_PP_DOWNLOAD_RSP_TYPE                   = 9,
    MN_MSG_STUB_TYPE_PS_CONCATENATE_FLAG                    = 10,
    MN_MSG_STUB_TYPE_SMS_AUTO_REPLY                         = 11,
    MN_MSG_STUB_TYPE_BUTT
};
typedef VOS_UINT32 MN_MSG_STUB_TYPE_ENUM_U32;
/* Added by f62575 for AT Project，2011-10-03,  End*/

enum MN_MSG_LINK_CTRL
{
    MN_MSG_LINK_CTRL_DISABLE,
    MN_MSG_LINK_CTRL_ONEOFF_ENABLE,
    MN_MSG_LINK_CTRL_ENABLE,
    MN_MSG_LINK_CTRL_BUTT
};
typedef VOS_UINT8 MN_MSG_LINK_CTRL_U8;

/*Type fo Sms TPDU*/
enum MN_MSG_TPDU_TYPE_ENUM
{
    MN_MSG_TPDU_DELIVER,                                                        /*SMS DELIVER type*/
    MN_MSG_TPDU_DELIVER_RPT_ACK,                                                /*SMS DELIVER REPORT for RP ACK*/
    MN_MSG_TPDU_DELIVER_RPT_ERR,                                                /*SMS DELIVER REPORT for RP ERROR*/
    MN_MSG_TPDU_STARPT,                                                         /*SMS STATUS REPORT type*/
    MN_MSG_TPDU_COMMAND,                                                        /*SMS COMMAND type*/
    MN_MSG_TPDU_SUBMIT,                                                         /*SMS SUBMIT type*/
    MN_MSG_TPDU_SUBMIT_RPT_ACK,                                                 /*SMS SUBMIT REPORT for RP ACK*/
    MN_MSG_TPDU_SUBMIT_RPT_ERR,                                                 /*SMS SUBMIT REPORT for RP ERROR*/
    MN_MSG_TPDU_MAX
};
typedef VOS_UINT8  MN_MSG_TPDU_TYPE_ENUM_U8;

/*Sms Rp Cause */
enum MN_MSG_RP_CAUSE_ENUM
{
    MN_MSG_RP_CAUSE_UNASSIGNED_NUMBER                       = 1,                /*Unassigned (unallocated) number*/
    MN_MSG_RP_CAUSE_OPERATOR_DETERMINED_BARRING             = 8,                /*Operator determined barring*/
    MN_MSG_RP_CAUSE_CALL_BARRED                             = 10,               /*Call barred*/
    MN_MSG_RP_CAUSE_RESERVED                                = 11,               /*Reserved*/
    MN_MSG_RP_CAUSE_SM_TRANSFER_REJECTED                    = 21,               /*Short message transfer rejected*/
    MN_MSG_RP_CAUSE_MEMORY_EXCEEDED                         = 22,               /*Memory capacity exceeded*/
    MN_MSG_RP_CAUSE_DESTINATION_OUT_OF_ORDER                = 27,               /*Destination out of order*/
    MN_MSG_RP_CAUSE_UNIDENTIFIED_SUBSCRIBER                 = 28,               /*Unidentified subscriber*/
    MN_MSG_RP_CAUSE_FACILITY_REJECTED                       = 29,               /*Facility rejected*/
    MN_MSG_RP_CAUSE_UNKNOWN_SUBSCRIBER                      = 30,               /*Unknown subscriber*/
    MN_MSG_RP_CAUSE_NETWORK_OUT_OF_ORDER                    = 38,               /*Network out of order*/
    MN_MSG_RP_CAUSE_TEMPORARY_FAILURE                       = 41,               /*Temporary failure*/
    MN_MSG_RP_CAUSE_CONGESTION                              = 42,               /*Congestion*/
    MN_MSG_RP_CAUSE_RESOURCES_UNAVAILABLE_UNSPECIFIED       = 47,               /*Resources unavailable, unspecified*/
    MN_MSG_RP_CAUSE_REQUESTED_FACILITY_NOT_SUBSCRIBED       = 50,               /*Requested facility not subscribed*/
    MN_MSG_RP_CAUSE_REQUESTED_FACILITY_NOT_IMPLEMENTED      = 69,               /*Requested facility not implemented*/
    MN_MSG_RP_CAUSE_INVALID_SM_TRANSFER_REFERENCE_VALUE     = 81,               /*Invalid short message transfer reference value*/
    MN_MSG_RP_CAUSE_INVALID_MSG_UNSPECIFIED                 = 95,               /*Semantically incorrect message*/
    MN_MSG_RP_CAUSE_INVALID_MANDATORY_INFORMATION           = 96,               /*Invalid mandatory information*/
    MN_MSG_RP_CAUSE_MSG_TYPE_NON_EXISTENT                   = 97,               /*Message type non existent or not implemented*/
    MN_MSG_RP_CAUSE_MSG_NOT_COMPATIBLE                      = 98,               /*Message not compatible with short message protocol state*/
    MN_MSG_RP_CAUSE_IE_NON_EXISTENT                         = 99,               /*Information element non existent or not implemented*/
    MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED                = 111,              /*Protocol error, unspecified*/
    MN_MSG_RP_CAUSE_INTERWORKING_UNSPECIFIED                = 127               /*Interworking, unspecified*/
};
typedef VOS_UINT8  MN_MSG_RP_CAUSE_ENUM_U8;

/*Sms Tp Cause*/
enum MN_MSG_TP_CAUSE_ENUM
{
    MN_MSG_TP_CAUSE_TELEMATIC_NOT_SUPPORTED                 = 0x80,             /*Telematic interworking not supported*/
    MN_MSG_TP_CAUSE_SM_TYPE0_NOT_SUPPORTED                  = 0x81,             /*Short message Type 0 not supported*/
    MN_MSG_TP_CAUSE_CANNOT_REPLACE_SM                       = 0x82,             /*Cannot replace short message*/
    MN_MSG_TP_CAUSE_UNSPECIFIED_PID_ERR                     = 0x8f,             /*Unspecified TP-PID error*/
    MN_MSG_TP_CAUSE_DCS_NOT_SUPPORTED                       = 0x90,             /*Data coding scheme (alphabet) not supported*/
    MN_MSG_TP_CAUSE_MSG_CLASS_NOT_SUPPORTED                 = 0x91,             /*Message class not supported*/
    MN_MSG_TP_CAUSE_UNSPECIFIED_DCS_ERR                     = 0x9f,             /*Unspecified TP-DCS error*/
    MN_MSG_TP_CAUSE_CANNOT_PERFORM_CMD                      = 0xa0,             /*Command cannot be actioned*/
    MN_MSG_TP_CAUSE_CMD_NOT_SUPPORTED                       = 0xa1,             /*Command unsupported*/
    MN_MSG_TP_CAUSE_UNSPECIFIED_CMD_ERR                     = 0xaf,             /*Unspecified TP-Command error*/
    MN_MSG_TP_CAUSE_TPDU_NOT_SUPPORTED                      = 0xb0,             /*TPDU not supported*/
    MN_MSG_TP_CAUSE_SC_BUSY                                 = 0xc0,             /*SC busy*/
    MN_MSG_TP_CAUSE_NO_SC_SUBSCRIPTION                      = 0xc1,             /*No SC subscription*/
    MN_MSG_TP_CAUSE_SC_FAILURE                              = 0xc2,             /*SC system failure*/
    MN_MSG_TP_CAUSE_INVALID_SME_ADDRESS                     = 0xc3,             /*Invalid SME address*/
    MN_MSG_TP_CAUSE_DESTINATION_SME_BARRED                  = 0xc4,             /*Destination SME barred*/
    MN_MSG_TP_CAUSE_REJECTED_DUPLICATE_SM                   = 0xc5,             /*SM Rejected-Duplicate SM*/
    MN_MSG_TP_CAUSE_VPF_NOT_SUPPORTED                       = 0xc6,             /*TP-VPF not supported*/
    MN_MSG_TP_CAUSE_VP_NOT_SUPPORTED                        = 0xc7,             /*TP-VP not supported*/
    MN_MSG_TP_CAUSE_SIM_FULL                                = 0xd0,             /*(U)SIM SMS storage full*/
    MN_MSG_TP_CAUSE_NO_SM_STORAGE_IN_SIM                    = 0xd1,             /*No SMS storage capability in (U)SIM*/
    MN_MSG_TP_CAUSE_ERR_IN_MS                               = 0xd2,             /*Error in MS*/
    MN_MSG_TP_CAUSE_MEMORY_FULL                             = 0xd3,             /*Memory Capacity Exceeded*/
    MN_MSG_TP_CAUSE_SAT_BUSY                                = 0xd4,             /*(U)SIM Application Toolkit Busy*/
    MN_MSG_TP_CAUSE_SIM_DATA_DOWNLOAD_ERR                   = 0xd5,             /*(U)SIM data download error*/
    MN_MSG_TP_CAUSE_UNSPECIFIED_ERR                         = 0xff
} ;
typedef VOS_UINT8  MN_MSG_TP_CAUSE_ENUM_U8;

/* IMS cause */
/*****************************************************************************
 枚举名    : MN_MSG_IMS_CAUSE_ENUM_UINT8
 枚举说明  : IMS cause值
 1.日    期   : 2013年12月25日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum MN_MSG_IMS_CAUSE_ENUM
{
    MN_MSG_IMS_CAUSE_INNER_ERROR                            = 0x01,
    MN_MSG_IMS_CAUSE_SMS_INCAPABILITY                       = 0x06,
    MN_MSG_IMS_CAUSE_SMS_NO_SMSC                            = 0x07,
    MN_MSG_IMS_CAUSE_SMS_NO_IPSMGW                          = 0x08,

    MN_MSG_IMS_CAUSE_UNSPECIFIED_ERR                        = 0xff
};
typedef VOS_UINT8  MN_MSG_IMS_CAUSE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MN_MSG_IMSA_CAUSE_ENUM_UINT8
 枚举说明  : IMSA内部 cause值
 1.日    期   : 2013年12月25日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum MN_MSG_IMSA_CAUSE_ENUM
{
    MN_MSG_IMSA_CAUSE_NO_SERVICE                             = 0x01,
    MN_MSG_IMSA_CAUSE_SMS_OPERATING                          = 0x02,

    MN_MSG_IMSA_CAUSE_NO_RF                                  = 0x03,

    MN_MSG_IMSA_CAUSE_UNSPECIFIED_ERR                        = 0xff
};
typedef VOS_UINT8  MN_MSG_IMSA_CAUSE_ENUM_UINT8;

/*Sms Pid */
enum MN_MSG_TP_PID_TYPE_ENUM
{
    MN_MSG_TP_PID_DEFAULT                                   = 0x00,             /*default value to use */
    MN_MSG_TP_PID_IMPLICIT                                  = 0x20,             /*implicit   device type is specific to this SC, or can be concluded on the basis of the address*/
    MN_MSG_TP_PID_TELEX                                     = 0x21,             /*telex (or teletex reduced to telex format)*/
    MN_MSG_TP_PID_G3_FAX                                    = 0x22,             /*group 3 telefax*/
    MN_MSG_TP_PID_G4_FAX                                    = 0x23,             /*group 4 telefax*/
    MN_MSG_TP_PID_VOICE_PHONE                               = 0x24,             /*voice telephone (i.e. conversion to speech)*/
    MN_MSG_TP_PID_ERMES                                     = 0x25,             /*ERMES (European Radio Messaging System)*/
    MN_MSG_TP_PID_NATIONAL_PAGING                           = 0x26,             /*National Paging system (known to the SC)*/
    MN_MSG_TP_PID_VIDEOTEX                                  = 0x27,             /*Videotex */
    MN_MSG_TP_PID_TELETEX_UNSPEC                            = 0x28,             /*teletex, carrier unspecified*/
    MN_MSG_TP_PID_TELETEX_PSPDN                             = 0x29,             /*teletex, in PSPDN*/
    MN_MSG_TP_PID_TELETEX_CSPDN                             = 0x2a,             /*teletex, in CSPDN*/
    MN_MSG_TP_PID_TELETEX_PSTN                              = 0x2b,             /*teletex, in analog PSTN*/
    MN_MSG_TP_PID_TELETEX_ISDN                              = 0x2c,             /*teletex, in digital ISDN*/
    MN_MSG_TP_PID_UCI                                       = 0x2d,             /*UCI */
    MN_MSG_TP_PID_MSG_HANDLING                              = 0x30,             /*a message handling facility (known to the SC)*/
    MN_MSG_TP_PID_X400                                      = 0x31,             /*any public X.400 based message handling system*/
    MN_MSG_TP_PID_INTERNET_EMAIL                            = 0x32,             /*Internet Electronic Mail*/
    MN_MSG_TP_PID_SC_SPECIFIC_1                             = 0x38,             /*values specific to each SC, usage based on mutual agreement between the SME and the SC*/
    MN_MSG_TP_PID_SC_SPECIFIC_2                             = 0x39,             /*values specific to each SC, usage based on mutual agreement between the SME and the SC*/
    MN_MSG_TP_PID_SC_SPECIFIC_3                             = 0x3a,             /*values specific to each SC, usage based on mutual agreement between the SME and the SC*/
    MN_MSG_TP_PID_SC_SPECIFIC_4                             = 0x3b,             /*values specific to each SC, usage based on mutual agreement between the SME and the SC*/
    MN_MSG_TP_PID_SC_SPECIFIC_5                             = 0x3c,             /*values specific to each SC, usage based on mutual agreement between the SME and the SC*/
    MN_MSG_TP_PID_SC_SPECIFIC_6                             = 0x3d,             /*values specific to each SC, usage based on mutual agreement between the SME and the SC*/
    MN_MSG_TP_PID_SC_SPECIFIC_7                             = 0x3e,             /*values specific to each SC, usage based on mutual agreement between the SME and the SC*/
    MN_MSG_TP_PID_GSM_UMTS                                  = 0x3f,             /*values specific to each SC, usage based on mutual agreement between the SME and the SC*/
    MN_MSG_TP_PID_SM_TYPE_0                                 = 0x40,             /*Short Message Type 0*/
    MN_MSG_TP_PID_REPLACE_SM_1                              = 0x41,             /*Replace Short Message Type 1*/
    MN_MSG_TP_PID_REPLACE_SM_2                              = 0x42,             /*Replace Short Message Type 2*/
    MN_MSG_TP_PID_REPLACE_SM_3                              = 0x43,             /*Replace Short Message Type 3*/
    MN_MSG_TP_PID_REPLACE_SM_4                              = 0x44,             /*Replace Short Message Type 4*/
    MN_MSG_TP_PID_REPLACE_SM_5                              = 0x45,             /*Replace Short Message Type 5*/
    MN_MSG_TP_PID_REPLACE_SM_6                              = 0x46,             /*Replace Short Message Type 6*/
    MN_MSG_TP_PID_REPLACE_SM_7                              = 0x47,             /*Replace Short Message Type 7*/
    MN_MSG_TP_PID_EMS                                       = 0x5e,             /*Enhanced Message Service (Obsolete)*/
    MN_MSG_TP_PID_RETURN_CALL                               = 0x5f,             /*Return Call Message*/
    MN_MSG_TP_PID_ANSI136_R_DATA                            = 0x7c,             /*ANSI-136 R-DATA*/
    MN_MSG_TP_PID_ME_DATA_DOWNLOAD                          = 0x7d,             /*ME Data download*/
    MN_MSG_TP_PID_ME_DEPERSONALIZE                          = 0x7e,             /*ME De personalization Short Message*/
    MN_MSG_TP_PID_SIM_DATA_DOWNLOAD                         = 0x7f,             /*(U)SIM Data download*/
    MN_MSG_TP_PID_MAX                                       = 0xFF
};
typedef VOS_UINT8  MN_MSG_TP_PID_TYPE_ENUM_U8;

/*Sms Class*/
enum MN_MSG_MSG_CLASS_ENUM
{
    MN_MSG_MSG_CLASS_0,                                                         /*Display only not store*/
    MN_MSG_MSG_CLASS_1,                                                         /*Default meaning: ME-specific*/
    MN_MSG_MSG_CLASS_2,                                                         /*(U)SIM specific message*/
    MN_MSG_MSG_CLASS_3,                                                         /*Default meaning: TE specific */
    MN_MSG_MSG_CLASS_NONE,
    MN_MSG_MSG_CLASS_MAX
};
typedef VOS_UINT8  MN_MSG_MSG_CLASS_ENUM_U8;

/*Sms Msg Code*/
enum MN_MSG_MSG_CODING_ENUM
{
    MN_MSG_MSG_CODING_7_BIT,
    MN_MSG_MSG_CODING_8_BIT,
    MN_MSG_MSG_CODING_UCS2,
    MN_MSG_MSG_CODING_MAX
};
typedef VOS_UINT8  MN_MSG_MSG_CODING_ENUM_U8;

/*Sms Msg Waiting*/
enum MN_MSG_MSG_WAITING_ENUM
{
    MN_MSG_MSG_WAITING_NONE,
    MN_MSG_MSG_WAITING_DISCARD,                                                 /*Message Waiting Indication Group: Discard Message*/
    MN_MSG_MSG_WAITING_STORE,                                                   /*Message Waiting Indication Group: Store Message*/
    MN_MSG_MSG_WAITING_NONE_1111,
    MN_MSG_MSG_WAITING_AUTO_DELETE,                                             /*Message Marked for Automatic Deletion Group*/
    MN_MSG_MSG_WAITING_MAX
} ;
typedef VOS_UINT8  MN_MSG_MSG_WAITING_ENUM_U8;

/*Sms Msg Waiting King*/
enum MN_MSG_MSG_WAITING_KIND_ENUM
{
    MN_MSG_MSG_WAITING_VOICEMAIL,                                               /*Voicemail Message Waiting*/
    MN_MSG_MSG_WAITING_FAX,                                                     /*Fax Message Waiting*/
    MN_MSG_MSG_WAITING_EMAIL,                                                   /*Electronic Mail Message Waiting*/
    MN_MSG_MSG_WAITING_OTHER,                                                   /*Other Message Waiting*/
    MN_MSG_MSG_WAITING_KIND_MAX
} ;
typedef VOS_UINT8  MN_MSG_MSG_WAITING_KIND_ENUM_U8;

/*Validity Period of TP User Data*/
enum MN_MSG_VALIDITY_PERIOD_ENUM
{
    MN_MSG_VALID_PERIOD_NONE,                                                   /*TP VP field not present*/
    MN_MSG_VALID_PERIOD_ENHANCED        ,                                       /*TP-VP field present - enhanced format*/
    MN_MSG_VALID_PERIOD_RELATIVE        ,                                       /*TP VP field present - relative format*/
    MN_MSG_VALID_PERIOD_ABSOLUTE        ,                                       /*TP VP field present - absolute format*/
    MN_MSG_VALID_PERIOD_MAX
} ;
typedef VOS_UINT8  MN_MSG_VALID_PERIOD_ENUM_U8;

/*Sms Tp Staus */
enum MN_MSG_TP_STATUS_ENUM
{
    MN_MSG_TP_STATUS_RECEIVED_OK                            = 0x00,             /*Short message received by the SME*/
    MN_MSG_TP_STATUS_UNABLE_TO_CONFIRM_DELIVERY             = 0x01,             /*Short message forwarded by the SC to the SME but the SC is unable to confirm delivery*/
    MN_MSG_TP_STATUS_REPLACED                               = 0x02,             /*Short message replaced by the SC*/
    MN_MSG_TP_STATUS_TRYING_CONGESTION                      = 0x20,             /*Congestion*/
    MN_MSG_TP_STATUS_TRYING_SME_BUSY                        = 0x21,             /*SME busy*/
    MN_MSG_TP_STATUS_TRYING_NO_RESPONSE_FROM_SME            = 0x22,             /*No response from SME*/
    MN_MSG_TP_STATUS_TRYING_SERVICE_REJECTED                = 0x23,             /*Service rejected*/
    MN_MSG_TP_STATUS_TRYING_QOS_NOT_AVAILABLE               = 0x24,             /*Quality of service not available*/
    MN_MSG_TP_STATUS_TRYING_SME_ERR                         = 0x25,             /*Error in SME*/
    MN_MSG_TP_STATUS_PERM_REMOTE_PROCEDURE_ERR              = 0x40,             /*Remote procedure error*/
    MN_MSG_TP_STATUS_PERM_INCOMPATIBLE_DEST                 = 0x41,             /*Incompatible destination*/
    MN_MSG_TP_STATUS_PERM_REJECTED_BY_SME                   = 0x42,             /*Connection rejected by SME*/
    MN_MSG_TP_STATUS_PERM_NOT_OBTAINABLE                    = 0x43,             /*Not obtainable*/
    MN_MSG_TP_STATUS_PERM_QOS_NOT_AVAILABLE                 = 0x44,             /*Quality of service not available*/
    MN_MSG_TP_STATUS_PERM_NO_INTERWORKING                   = 0x45,             /*No interworking available*/
    MN_MSG_TP_STATUS_PERM_VP_EXPIRED                        = 0x46,             /*SM Validity Period Expired*/
    MN_MSG_TP_STATUS_PERM_DELETED_BY_ORIG_SME               = 0x47,             /*SM Deleted by originating SME*/
    MN_MSG_TP_STATUS_PERM_DELETED_BY_SC_ADMIN               = 0x48,             /*SM Deleted by SC Administration*/
    MN_MSG_TP_STATUS_PERM_SM_NO_EXISTING                    = 0x49,             /*SM does not exist*/
    MN_MSG_TP_STATUS_TEMP_CONGESTION                        = 0x60,             /*Congestion*/
    MN_MSG_TP_STATUS_TEMP_SME_BUSY                          = 0x61,             /*SME busy*/
    MN_MSG_TP_STATUS_TEMP_NO_RESPONSE_FROM_SME              = 0x62,             /*No response from SME*/
    MN_MSG_TP_STATUS_TEMP_SERVICE_REJECTED                  = 0x63,             /*Service rejected*/
    MN_MSG_TP_STATUS_TEMP_QOS_NOT_AVAILABLE                 = 0x64,             /*Quality of service not available*/
    MN_MSG_TP_STATUS_TEMP_SME_ERR                           = 0x65,             /*Error in SME*/
    MN_MSG_TP_STATUS_MAX                                    = 0xFF
} ;
typedef VOS_UINT8  MN_MSG_TP_STATUS_ENUM_U8;


/*Sms Command Type*/
enum MN_MSG_COMMAND_ENUM
{
    MN_MSG_COMMAND_TYPE_ENQUIRY                             = 0x00,             /*Enquiry relating to previously submitted short message*/
    MN_MSG_COMMAND_TYPE_CANCEL_STATUS_RPT                   = 0x01,             /*Cancel Status Report Request relating to previously submitted short message*/
    MN_MSG_COMMAND_TYPE_DELETE_SM                           = 0x02,             /*Delete previously submitted Short Message*/
    MN_MSG_COMMAND_TYPE_ENABLE_STATUS_RPT                   = 0x03,             /*Enable Status Report Request relating to previously submitted short message*/
    MN_MSG_COMMAND_MAX
} ;
typedef VOS_UINT8  MN_MSG_COMMAND_TYPE_ENUM_U8;

/*Sms Status*/
enum MN_MSG_STATUS_TYPE_ENUM
{
    MN_MSG_STATUS_MT_NOT_READ                               = 0,                                                 /*unread sms*/
    MN_MSG_STATUS_MT_READ,                                                      /*read sms*/
    MN_MSG_STATUS_MO_NOT_SENT,                                                  /*not sent sms*/
    MN_MSG_STATUS_MO_SENT,                                                      /*sent sms*/
    MN_MSG_STATUS_NONE,                                                         /*all status sms,including read,unread,sent,not sent ,and not including sms status report*/
    MN_MSG_STATUS_STARPT,                                                       /*sms status report*/
    MN_MSG_STATUS_MAX
} ;
typedef VOS_UINT8  MN_MSG_STATUS_TYPE_ENUM_U8;

/*Sms Memory Store*/
enum MN_MSG_MEM_STORE_ENUM
{
    MN_MSG_MEM_STORE_NONE                                   = 0,                                                     /*not saved by PS*/
    MN_MSG_MEM_STORE_SIM,                                                       /*saved in USIM*/
    MN_MSG_MEM_STORE_NV,                                                        /*saved in NVIM*/
    MN_MSG_MEM_STORE_MAX
} ;
typedef VOS_UINT8  MN_MSG_MEM_STORE_ENUM_U8;

/*Sms Write Mode */
enum MN_MSG_WRITE_MODE_TYPE_ENUM
{
    MN_MSG_WRITE_MODE_INSERT,                                                   /*write mode is insert*/
    MN_MSG_WRITE_MODE_REPLACE,                                                  /*write mode is replace*/
    MN_MSG_WRITE_MODE_MAX
} ;
typedef VOS_UINT8  MN_MSG_WRITE_MODE_ENUM_U8;

/*Type of delete*/
enum MN_MSG_DELETE_TYPE_ENUM
{
    MN_MSG_DELETE_SINGLE                                    = 0,                                                      /*delete single sms or status report or sms service para*/
    MN_MSG_DELETE_READ,                                                         /*delete read sms (the para is not  applicable to status report and sms service para)*/
    MN_MSG_DELETE_UNREAD,                                                       /*delete unread sms (the para is not applicable to status report and sms service para)*/
    MN_MSG_DELETE_SENT,                                                         /*delete sms sent sms (the para is not applicable to status report and sms service para)*/
    MN_MSG_DELETE_NOT_SENT,                                                     /*delete sms unsend sms (the para is not  applicable to status report and sms service para)*/
    MN_MSG_DELETE_ALL,                                                          /*delete all sms or status report or sms service para*/
    MN_MSG_DELETE_MAX
};
typedef VOS_UINT8  MN_MSG_DELETE_TYPE_ENUM_U8;

/*Sms Type of number*/
enum MN_MSG_TON_ENUM
{
    MN_MSG_TON_UNKNOWN                                      = 0  ,              /*000: unknown */
    MN_MSG_TON_INTERNATIONAL            ,                                       /*001: international number */
    MN_MSG_TON_NATIONAL                 ,                                       /*010: national number */
    MN_MSG_TON_NETWORK_SPEC             ,                                       /*011: network specific number */
    MN_MSG_TON_SUBSCRIBER_NUMBER        ,                                       /*100: Subscriber number */
    MN_MSG_TON_ALPHANUMERIC             ,                                       /*101: Alphanumeric GSM SMS: addr value is GSM 7-bit chars */
    MN_MSG_TON_ABBREVIATED              ,                                       /*110: Abbreviated number*/
    MN_MSG_TON_Reserved                                                         /*111: Reserved for extension*/
} ;
typedef VOS_UINT8   MN_MSG_TON_ENUM_U8 ;

/*Sms Number Plan*/
enum MN_MSG_NPI_ENUM
{
    MN_MSG_NPI_UNKNOWN                                      = 0,                /*0000: unknown */
    MN_MSG_NPI_ISDN                                         = 1,                /*0001: ISDN/telephony numbering plan  */
    MN_MSG_NPI_DATA                                         = 3,                /*0011: data numbering plan  */
    MN_MSG_NPI_TELEX                                        = 4,                /*0100: telex numbering plan  */
    MN_MSG_NPI_SC_SPECIFIC1                                 = 5,                /*0101: Service Centre Specific plan 1)*/
    MN_MSG_NPI_SC_SPECIFIC2                                 = 6,                /*0101: Service Centre Specific plan 1)*/
    MN_MSG_NPI_NATIONAL                                     = 8,                /*1000: national numbering plane */
    MN_MSG_NPI_PRIVATE                                      = 9,                /*1001: private numbering plan */
    MN_MSG_NPI_ERMES                                        = 10                /*1010: ERMES numbering plan (ETSI DE/PS 3 01 3) */

} ;
typedef VOS_UINT8   MN_MSG_NPI_ENUM_U8;


/*****************************************************************************
 枚举名    : MN_MSG_CNMI_MT_TYPE_ENUM_U8
 结构说明  : <mt>类型
 1.日    期   : 2013年10月17日
   作    者   : w00167002
   修改内容   : 新增结构体
*****************************************************************************/
enum MN_MSG_CNMI_MT_TYPE_ENUM
{
    MN_MSG_CNMI_MT_NO_SEND_TYPE                             = 0,                /* No SMS-DELIVER indications are routed to the TE */
    MN_MSG_CNMI_MT_CMTI_TYPE                                = 1,                /* +CMTI */
    MN_MSG_CNMI_MT_CMT_TYPE                                 = 2,                /* +CMT */
    MN_MSG_CNMI_MT_CLASS3_TYPE                              = 3,                /* CLASS3 MSG IS indicated by +CMT type, others is indicated by +CMTI type */
    MN_MSG_CNMI_MT_TYPE_BUTT
} ;
typedef  VOS_UINT8  MN_MSG_CNMI_MT_TYPE_ENUM_U8;

/*Action of rcv sms*/
enum MN_MSG_RCVMSG_ACT_ENUM
{
    MN_MSG_RCVMSG_ACT_DISCARD                               = 0,                                                 /*Discard message */
    MN_MSG_RCVMSG_ACT_STORE,                                                    /*Store message and notify clients*/
    MN_MSG_RCVMSG_ACT_TRANSFER_ONLY,                                            /*Don't store msg but send it to clients*/
    MN_MSG_RCVMSG_ACT_TRANSFER_AND_ACK,                                         /*Send the message to clients and ack it*/
    MN_MSG_RCVMSG_ACT_MAX
} ;
typedef  VOS_UINT8  MN_MSG_RCVMSG_ACT_ENUM_U8;

/*Domain of send sms*/
enum MN_MSG_SEND_DOMAIN_ENUM
{
    MN_MSG_SEND_DOMAIN_PS                                   = 0       ,         /*only PS,consistent with Ps Send Domain in NAS-SMS */
    MN_MSG_SEND_DOMAIN_CS               ,                                       /*only CS,,consistent with Ps Send Domain in NAS-SMS */
    MN_MSG_SEND_DOMAIN_PS_PREFERRED     ,                                       /*PS PREFERRED*/
    MN_MSG_SEND_DOMAIN_CS_PREFERRED     ,                                       /*CS PREFERRED*/
    MN_MSG_SEND_DOMAIN_NO,                                                      /*No Domain*/
    MN_MSG_SEND_DOMAIN_MAX
};
typedef VOS_UINT8  MN_MSG_SEND_DOMAIN_ENUM_U8;

enum MN_MSG_RCV_DOMAIN_ENUM
{
    MN_MSG_RCV_DOMAIN_PS                                   = 0       ,          /* PS域接收短信 */
    MN_MSG_RCV_DOMAIN_CS,                                                       /* CS域接收短信 */
    MN_MSG_RCV_DOMAIN_BUTT                                                      /* 无效值 */
};
typedef VOS_UINT8  MN_MSG_RCV_DOMAIN_ENUM_U8;

/*Sms Memory Status*/
enum MN_MSG_MEM_FLAG_ENUM
{
    MN_MSG_MEM_FULL_SET                                     = 0,                /*memory full*/
    MN_MSG_MEM_FULL_UNSET,                                                      /*memory available*/
    MN_MSG_MEM_FULL_MAX
} ;
typedef VOS_UINT8  MN_MSG_MEM_FLAG_ENUM_U8;

/*Status of Sms Status Report*/
/*****************************************************************************
 结构名    : MN_MSG_RPT_STATUS_ENUM
 结构说明  : TAF给AT上报的短信发送结果分类
  1.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级，新增MN_MSG_RPT_USER_ABORT
*****************************************************************************/
enum MN_MSG_RPT_STATUS_ENUM
{
    MN_MSG_RPT_OK,                                                              /*Success: submit_report_ack info*/
    MN_MSG_RPT_LOWERLAYER_ERR           ,                                       /*Lower layer errors*/
    MN_MSG_RPT_RP_ERR                   ,                                       /*Rp Error*/
    MN_MSG_RPT_CP_ERR                   ,                                       /*Cp Error*/
    MN_MSG_RPT_SMR_TR1M_TIMEOUT         ,                                       /*TR1M Expired*/
    MN_MSG_RPT_SMR_TR2M_TIMEOUT         ,                                       /*TR2M Expired*/
    MN_MSG_RPT_SMR_NO_RESOURCES         ,                                       /*No Resources*/
    MN_MSG_RPT_USER_ABORT,
    MN_MSG_RPT_MAX
} ;
typedef VOS_UINT8      MN_MSG_RPT_STATUS_ENUM_U8;

/*->f62575*/
enum MN_MSG_EO_TYPE_ENUM
{
    MN_MSG_UDH_EO_PRE_DEF_SOUND,
    MN_MSG_UDH_EO_IMELODY,
    MN_MSG_UDH_EO_BLACK_WHITE_BITMAP,
    MN_MSG_UDH_EO_2BITGREYSCALE_BITMAP,
    MN_MSG_UDH_EO_6BITCOLOR_BITMAP_ANIM,
    MN_MSG_UDH_EO_VCARD,
    MN_MSG_UDH_EO_VCALENDAR,
    MN_MSG_UDH_EO_STD_WVG_OBJ,
    MN_MSG_UDH_EO_POLYPHONIC_MELODY,
    MN_MSG_UDH_EO_DATA_FORMAT_DELIVERY_REQ                  = 0xff
};
typedef VOS_UINT8 MN_MSG_EO_TYPE_ENUM_U8;

enum MN_MSG_COMPRESSION_ALGORITHM
{
    MN_MSG_COMPRESSION_LZSS
};
typedef VOS_UINT8 MN_MSG_COMPRESSION_ALGORITHM_U8;
/*<-f62575*/

enum MN_MSG_CLASS0_TAILOR
{
    MN_MSG_CLASS0_VODAFONE,                                                     /* Vodafone Class0 短信定制*/
    MN_MSG_CLASS0_TIM,                                                          /* Italy TIM Class0 短信定制（即H3G Class0 短信定制） */
    MN_MSG_CLASS0_DEF,                                                          /* 默认Class 0 短信处理(Balong符合3GPP协议的处理方式即可) */
    MN_MSG_CLASS0_VIVO                                                          /* VIVO Class0 短信定制*/
};

typedef VOS_UINT8 MN_MSG_CLASS0_TAILOR_U8;

enum MN_MSG_ACTIVE_MESSAGE_STATUS_ENUM
{
    MN_MSG_ACTIVE_MESSAGE_STATUS_DEACTIVE,
    MN_MSG_ACTIVE_MESSAGE_STATUS_ACTIVE,
    MN_MSG_ACTIVE_MESSAGE_NOT_SUPPORT = 255
};
typedef VOS_UINT8 MN_MSG_ACTIVE_MESSAGE_STATUS_ENUM_UINT8;

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

enum MN_MSG_CBLANG_ENUM
{
    MN_MSG_CBLANG_GERMAN                                    = 0x00,
    MN_MSG_CBLANG_ENGLISH                                   = 0x01,
    MN_MSG_CBLANG_ITALIAN                                   = 0x02,
    MN_MSG_CBLANG_FRENCH                                    = 0x03,
    MN_MSG_CBLANG_SPANISH                                   = 0x04,
    MN_MSG_CBLANG_DUTCH                                     = 0x05,
    MN_MSG_CBLANG_SWEDISH                                   = 0x06,
    MN_MSG_CBLANG_DANISH                                    = 0x07,
    MN_MSG_CBLANG_PORTUGUESE                                = 0x08,
    MN_MSG_CBLANG_FINNISH                                   = 0x09,
    MN_MSG_CBLANG_NORWEGIAN                                 = 0x0a,
    MN_MSG_CBLANG_GREEK                                     = 0x0b,
    MN_MSG_CBLANG_TURKISH                                   = 0x0c,
    MN_MSG_CBLANG_HUNGARIAN                                 = 0x0d,
    MN_MSG_CBLANG_POLISH                                    = 0x0e,
    MN_MSG_CBLANG_CZECH                                     = 0x20,
    MN_MSG_CBLANG_HEBREW                                    = 0x21,
    MN_MSG_CBLANG_ARABIC                                    = 0x22,
    MN_MSG_CBLANG_RUSSIAN                                   = 0x23,
    MN_MSG_CBLANG_ICELANDIC                                 = 0x24,
    MN_MSG_CBLANG_MAX                                       = 0xff
};
typedef VOS_UINT8  MN_MSG_CBLANG_ENUM_U8;

/*CBS Function On or Off*/
enum MN_MSG_CBSSTATUS_ENUM
{
    MN_MSG_CBSTATUS_DISABLE             = 0x00,
    MN_MSG_CBSTATUS_W_ENABLE            = 0x01,
    MN_MSG_CBSTATUS_G_ENABLE            = 0x02,
    MN_MSG_CBSTATUS_WG_ENABLE           = 0x03,
    MN_MSG_CBSTATUS_MAX
};
typedef VOS_UINT8 MN_MSG_CBSTATUS_ENUM_U8;

/*Cbs Mode*/
enum MN_MSG_CBMODE_ENUM
{
    MN_MSG_CBMODE_ACCEPT,
    MN_MSG_CBMODE_REJECT,
    MN_MSG_CBMODE_MAX
};
typedef VOS_UINT8 MN_MSG_CBMODE_ENUM_U8;

#endif

/*SMS version PHASE2版本 SMS PHASE2+版本*/
enum MN_MSG_CSMS_MSG_VERSION_ENUM
{
    MN_MSG_CSMS_MSG_VERSION_PHASE2,
    MN_MSG_CSMS_MSG_VERSION_PHASE2_PLUS
};
typedef VOS_UINT8 MN_MSG_CSMS_MSG_VERSION_ENUM_U8;


/*****************************************************************************
 枚举名    : TAF_CBA_ETWS_PRIM_NTF_AUTH_RSLT_ENUM
 结构说明  : ETWS主通知信息鉴权结果
 1.日    期   : 2012年3月30日
   作    者   : l00171473
   修改内容   : 新建
*****************************************************************************/
enum TAF_CBA_ETWS_PRIM_NTF_AUTH_RSLT_ENUM
{
    TAF_CBA_ETWS_PRIM_NTF_AUTH_SUCCESS,                                         /* ETWS主通知信息通过鉴权 */
    TAF_CBA_ETWS_PRIM_NTF_AUTH_FAILED                                           /* ETWS主通知信息未通过鉴权 */
};
typedef VOS_UINT8 TAF_CBA_ETWS_PRIM_NTF_AUTH_RSLT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_CBA_CBMI_RANGE_RCV_TYPE_ENMU
 结构说明  : 每个CBMI RANGE 的接收类型, 目前仅支持 ACCEPT的模式
 1.日    期   : 2012年3月30日
   作    者   : l00171473
   修改内容   : 新建
*****************************************************************************/
enum TAF_CBA_CBMI_RANGE_RCV_MODE_ENMU
{
    TAF_CBA_CBMI_RANGE_RCV_MODE_REJECT,                                         /* 不接收该范围的消息 */
    TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT,                                         /* 接收该范围的消息 */
    TAF_CBA_CBMI_RANGE_RCV_MODE_BUTT
};
typedef VOS_UINT32 TAF_CBA_CBMI_RANGE_RCV_MODE_ENMU_UINT32;

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
/*****************************************************************************
 枚举名    : TAF_MSG_SIGNALLING_TYPE_ENUM
 结构说明  : SMS发送基于stack发送类型定义
 1.日    期   : 2013年7月11日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum TAF_MSG_SIGNALLING_TYPE_ENUM
{
    /* SMS基于GSM，UTRAN或LTE信令发送 */
    TAF_MSG_SIGNALLING_TYPE_NAS_SIGNALLING,
    /* SMS基于SIP信令发送 */
    TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP,

    TAF_MSG_SIGNALLING_TYPE_BUTT
};
typedef VOS_UINT32 TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32;
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*******************************************************************************
 结构名    : MN_MSG_CONFIG_PARM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 短信业务参数结构
*******************************************************************************/
typedef struct
{
    MN_MSG_RCVMSG_ACT_ENUM_U8           enRcvSmAct;                             /*action of received msg*/
    MN_MSG_MEM_STORE_ENUM_U8            enSmMemStore;                           /*Sm memory store:NVIM or USIM of received msg*/
    MN_MSG_RCVMSG_ACT_ENUM_U8           enRcvStaRptAct;                         /*action of received Status Report msg*/
    MN_MSG_MEM_STORE_ENUM_U8            enStaRptMemStore;                       /*Sm memory store:NVIM or USIM of Status Report msg*/
    MN_MSG_MEM_STORE_ENUM_U8            enCbmMemStore;                          /*Cbm memory store:NVIM of received msg*/
    MN_MSG_MEM_FLAG_ENUM_U8             enAppMemStatus;                         /*外部存储器状态,仅当协议栈不保存时有效*/
    MN_MSG_CSMS_MSG_VERSION_ENUM_U8     enSmsServVersion;                       /*巴西vivo短消息方案-添加变量*/

    MN_MSG_CNMI_MT_TYPE_ENUM_U8         enMtType;

}MN_MSG_CONFIG_PARM_STRU;

/*******************************************************************************
 结构名    : MN_MSG_TPDU_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 短信TPDU结构, 包括TPDU长度(单位: 字节)和TPDU码流
*******************************************************************************/
/*lint -e958 -e959 修改人:l60609;原因:64bit*/
typedef struct
{
    VOS_UINT32                          ulLen;
    VOS_UINT8                          *pucTpdu;
}MN_MSG_TPDU_STRU;
/*lint +e958 +e959 修改人:l60609;原因:64bit*/

typedef struct
{
    VOS_UINT32                          ulLen;
    VOS_UINT8                           aucUrl[MN_MSG_ACTIVE_MESSAGE_MAX_URL_LEN];
}MN_MSG_ACTIVE_MESSAGE_URL_STRU;

typedef struct
{
    MN_MSG_ACTIVE_MESSAGE_STATUS_ENUM_UINT8                     enActiveStatus;
    MN_MSG_MSG_CODING_ENUM_U8                                   enMsgCoding;
    VOS_UINT8                                                   aucReserve1[2];
    MN_MSG_ACTIVE_MESSAGE_URL_STRU                              stUrl;
}MN_MSG_ACTIVE_MESSAGE_STRU;

/*Content of Sms BCD Address*/
typedef struct
{
    VOS_UINT8                           ucBcdLen;
    MN_MSG_ADDR_NUM_TYPE_T              addrType;                               /*bcd number type*/
    VOS_UINT8                           aucBcdNum[MN_MSG_MAX_BCD_NUM_LEN];      /*bcd                               number array*/
} MN_MSG_BCD_ADDR_STRU;

typedef struct
{
    MN_MSG_TPDU_TYPE_ENUM_U8            enTpduType;                             /*TP Message Type*/
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT32                          ulLen;                                  /*length of sms TPDU*/
    VOS_UINT8                           aucData[MN_MSG_MAX_LEN];                /*TPDU*/
    VOS_UINT8                           aucReserve2[1];
} MN_MSG_RAW_TS_DATA_STRU;

/*Content of sms msg including TPDU and SC*/
typedef struct
{
    MN_MSG_BCD_ADDR_STRU                stScAddr;                               /*address of service center*/
    MN_MSG_RAW_TS_DATA_STRU             stTsRawData;                            /*TPDU detail*/
} MN_MSG_MSG_INFO_STRU;

/*Content of Alpha Identifier*/
#define MN_MSG_MAX_ALPHA_ID_LEN                             227                 /*255-28*/
typedef struct
{
    VOS_UINT32                          ulLen;                                  /*length of sms ALPHA IDENTIFIER*/
    VOS_UINT8                           aucData[MN_MSG_MAX_ALPHA_ID_LEN];       /*content                           of sms ALPHA IDENTIFIER*/
    VOS_UINT8                           aucReserve1[1];
} MN_MSG_ALPHA_ID_INFO_STRU;

/*Sms Service para*/
enum MN_MSG_SRV_PARM_EXIST_ENUM
{
    MN_MSG_SRV_PARM_PRESENT                                 = 0,
    MN_MSG_SRV_PARM_ABSENT                                  = 1
};
typedef VOS_UINT8 MN_MSG_SRV_PARM_EXIST_ENUM_U8;

#define MN_MSG_SRV_PARM_MASK_DEST_ADDR                      0x01
#define MN_MSG_SRV_PARM_MASK_SC_ADDR                        0x02
#define MN_MSG_SRV_PARM_MASK_PID                            0x04
#define MN_MSG_SRV_PARM_MASK_DCS                            0x08
#define MN_MSG_SRV_PARM_MASK_VALIDITY                       0x10
#define MN_MSG_SRV_PARM_TOTALABSENT                         0x1F
typedef struct
{
    VOS_UINT8                           ucParmInd;                              /*Parameter Indicators*/
    VOS_UINT8                           aucReserve1[3];
    MN_MSG_BCD_ADDR_STRU                stDestAddr;                             /*TP Destination Address*/
    MN_MSG_BCD_ADDR_STRU                stScAddr;                               /*TS Service Centre Address*/
    VOS_UINT8                           ucPid;                                  /*TP Protocol Identifier*/
    VOS_UINT8                           ucDcs;                                  /*TP Data Coding Scheme*/
    VOS_UINT8                           ucValidPeriod;                          /*TP Validity Period*/
    VOS_UINT8                           aucReserve2[1];
    MN_MSG_ALPHA_ID_INFO_STRU           stAlphaIdInfo;                          /*Alpha Identifier*/
} MN_MSG_SRV_PARAM_STRU;

/*Format of Ascii address*/
typedef struct
{
    MN_MSG_TON_ENUM_U8                  enNumType;                              /*type of number*/
    MN_MSG_NPI_ENUM_U8                  enNumPlan;                              /*Numbering plan identification*/
    VOS_UINT8                           aucReserve1[2];
    VOS_UINT32                          ulLen;                                  /*Length of AsicNum*/
    VOS_UINT8                           aucAsciiNum[MN_MAX_ASCII_ADDRESS_NUM + 1];   /*array  of ASCII Num*/
    VOS_UINT8                           aucReserve2[3];
} MN_MSG_ASCII_ADDR_STRU;

/*Sms Dcs */
typedef struct
{
    VOS_BOOL                            bCompressed;                            /*Compressed or not*/
    VOS_BOOL                            bWaitingIndiActive;                     /*Waiting Indication Active or inactive*/
    MN_MSG_MSG_CLASS_ENUM_U8            enMsgClass;                             /*sms msg class*/
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding;                            /*sms msg coding*/
    MN_MSG_MSG_WAITING_ENUM_U8          enMsgWaiting;                           /*sms msg waiting*/
    MN_MSG_MSG_WAITING_KIND_ENUM_U8     enMsgWaitingKind;                       /*sms msg waiting king*/
    VOS_BOOL                            bRawDcsValid;                            /*Compressed or not*/
    VOS_UINT8                           ucRawDcsData;                           /*Raw DCS Byte */
    VOS_UINT8                           aucReserve1[7];
} MN_MSG_DCS_CODE_STRU;

/*Sms TimeStamp */
typedef struct
{
    VOS_UINT8                           ucYear;                                 /*0x00-0x99*/
    VOS_UINT8                           ucMonth;                                /*0x01-0x12*/
    VOS_UINT8                           ucDay;                                  /*0x01-0x31*/
    VOS_UINT8                           ucHour;                                 /*0x00-0x23*/
    VOS_UINT8                           ucMinute;                               /*0x00-0x59*/
    VOS_UINT8                           ucSecond;                               /*0x00-0x59*/
    VOS_INT8                            cTimezone;                              /*+/-, [-48,+48] number of 15 minutes*/
    VOS_UINT8                           aucReserve1[1];
} MN_MSG_TIMESTAMP_STRU;

/*Sms Validity Period*/
typedef struct
{
    MN_MSG_VALID_PERIOD_ENUM_U8         enValidPeriod;                          /*TP Validity Period Format*/
    VOS_UINT8                           aucReserve1[3];
    union
    {
    MN_MSG_TIMESTAMP_STRU               stAbsoluteTime;                         /*TP-VP (Absolute format)*/
    VOS_UINT8                           ucOtherTime;                            /*TP-VP (Relative format or Enhanced format)*/
    }u;
} MN_MSG_VALID_PERIOD_STRU;

/*Type of TP User Data Header*/
enum MN_MSG_UDH_TYPE_ENUM
{
    MN_MSG_UDH_CONCAT_8                                     = 0x00,             /*Concatenated short messages, 8-bit reference number*/
    MN_MSG_UDH_SPECIAL_SM,                                                      /*Special SMS Message Indication*/
    MN_MSG_UDH_PORT_8                                       = 0x04,             /*Application port addressing scheme, 8 bit address*/
    MN_MSG_UDH_PORT_16,                                                         /*Application port addressing scheme, 16 bit address*/
    MN_MSG_UDH_SMSC_CTRL,                                                       /*SMSC Control Parameters*/
    MN_MSG_UDH_SOURCE,                                                          /*UDH Source Indicator*/
    MN_MSG_UDH_CONCAT_16,                                                       /*Concatenated short message, 16-bit reference number*/
    MN_MSG_UDH_WCMP,                                                            /*Wireless Control Message Protocol*/
    MN_MSG_UDH_TEXT_FORMATING,                                                  /*Text Formatting*/
    MN_MSG_UDH_PRE_DEF_SOUND,                                                   /*Predefined Sound*/
    MN_MSG_UDH_USER_DEF_SOUND,                                                  /*User Defined Sound (iMelody max 128 bytes)*/
    MN_MSG_UDH_PRE_DEF_ANIM,                                                    /*Predefined Animation*/
    MN_MSG_UDH_LARGE_ANIM,                                                      /*Large Animation (16*16 times 4 = 32*4 =128 bytes)*/
    MN_MSG_UDH_SMALL_ANIM,                                                      /*Small Animation (8*8 times 4 = 8*4 =32 bytes)*/
    MN_MSG_UDH_LARGE_PIC,                                                       /*Large Pic (32*32 = 128 bytes)*/
    MN_MSG_UDH_SMALL_PIC,                                                       /*Small Pic (16*16 = 32 bytes)*/
    MN_MSG_UDH_VAR_PIC,                                                         /*Variable Pic*/
    MN_MSG_UDH_USER_PROMPT                                  = 0x13,             /*User prompt indicator*/
/*->f62575*/
    MN_MSG_UDH_EO,                                                              /*Extended Object*/
    MN_MSG_UDH_REO,                                                             /*Reused Extended Object*/
    MN_MSG_UDH_CC,                                                              /*Compression Control*/
    MN_MSG_UDH_OBJ_DISTR_IND,                                                /*Object Distribution Indicator*/
    MN_MSG_UDH_STD_WVG_OBJ,                                                  /*Standard WVG object*/
    MN_MSG_UDH_CHAR_SIZE_WVG_OBJ,                                            /*Character Size WVG object*/
    MN_MSG_UDH_EXT_OBJECT_DATA_REQ_CMD,                                         /*Extended Object Data Request Command*/
/*<-f62575*/
    MN_MSG_UDH_RFC822                                       = 0x20,             /*RFC 822 E-Mail Header*/
/*->f62575*/
    MN_MSG_UDH_HYPERLINK_FORMAT,
    MN_MSG_UDH_REPLY_ADDR,
    MN_MSG_UDH_ENHANCED_VOICE_MAIL_INF,
/*<-f62575*/
    MN_MSG_UDH_MAX                                          = 0xFFFF
} ;
typedef VOS_UINT8  MN_MSG_UDH_TYPE_ENUM_U8;

/*Alignment of TP User Data*/
enum MN_MSG_UDH_ALIGNMENT_ENUM
{
    MN_MSG_UDH_ALIGN_LEFT,                                                      /*Alignment:Left*/
    MN_MSG_UDH_ALIGN_CENTER,                                                    /*Alignment:Center*/
    MN_MSG_UDH_ALIGN_RIGHT,                                                     /*Alignment:Right*/
    MN_MSG_UDH_ALIGNT_DEF,                                                      /*Alignment:Default*/
    MN_MSG_UDH_ALIGN_MAX
} ;
typedef VOS_UINT8  MN_MSG_UDH_ALIGN_ENUM_U8;

/*Font of TP User Data*/
enum MN_MSG_UDH_FONT_SIZE_ENUM
{
    MN_MSG_UDH_FONT_NORMAL,                                                     /*Font:Normal*/
    MN_MSG_UDH_FONT_LARGE,                                                      /*Font:Large*/
    MN_MSG_UDH_FONT_SMALL,                                                      /*Font:Small*/
    MN_MSG_UDH_FONT_RESERVED,                                                   /*Font:Reserved*/
    MN_MSG_UDH_FONT_MAX
} ;
typedef VOS_UINT8  MN_MSG_UDH_FONT_ENUM_U8;

/*Content of Concatenated short messages, 8-bit reference number*/
typedef struct
{
    VOS_UINT8                           ucMr;                                   /*Concatenated short message reference number*/
    VOS_UINT8                           ucTotalNum;                             /*Maximum number of short messages in the concatenated short message*/
    VOS_UINT8                           ucSeqNum;                               /*Sequence number of the current short message*/
    VOS_UINT8                           aucReserve1[1];
} MN_MSG_UDH_CONCAT_8_STRU;

/*Content of Special SMS Message Indication*/
enum MN_MSG_EXTMSG_IND_ENUM
{
    MN_MSG_EXTMSG_IND_NONE,
    MN_MSG_EXTMSG_IND_VOICEMSG_WAITING,
    MN_MSG_EXTMSG_IND_MAX
};
typedef VOS_UINT8 MN_MSG_EXTMSG_IND_ENUM_UINT8;

enum MN_MSG_PROFILE_ID_ENUM
{
    MN_MSG_PROFILE_ID_1,
    MN_MSG_PROFILE_ID_2,
    MN_MSG_PROFILE_ID_3,
    MN_MSG_PROFILE_ID_4,
    MN_MSG_PROFILE_ID_MAX
};
typedef VOS_UINT8 MN_MSG_PROFILE_ID_ENUM_UINT8;

typedef struct
{
    MN_MSG_MSG_WAITING_ENUM_U8          enMsgWaiting;                           /*Indicates whether or not the message shall be stored*/
    MN_MSG_MSG_WAITING_KIND_ENUM_U8     enMsgWaitingKind;                       /*the message indication type*/
    VOS_UINT8                           ucMsgCount;                             /*Message Count*/
    MN_MSG_PROFILE_ID_ENUM_UINT8        enProfileId;                /*Bits 6 and 5 indicate the profile ID of the Multiple Subscriber Profile (see 3GPP TS 23.097 [41]).*/
    MN_MSG_EXTMSG_IND_ENUM_UINT8        enExtMsgInd;                /*Bits 432 indicate the extended message indication type*/
    VOS_UINT8                           aucReserve1[3];
} MN_MSG_UDH_SPECIAL_SMS_STRU;

/*Content of Application port addressing scheme, 8 bit address*/
typedef struct
{
    VOS_UINT8                           ucDestPort;                             /*Destination port*/
    VOS_UINT8                           ucOrigPort;                             /*Originator port*/
    VOS_UINT8                           aucReserve1[2];
} MN_MSG_UDH_APPPORT_8_STRU;

/*Content of Application port addressing scheme, 16 bit address*/
typedef struct
{
    VOS_UINT16                          usDestPort;                             /*Destination port*/
    VOS_UINT16                          usOrigPort;                             /*Originator port*/
} MN_MSG_UDH_APPPORT_16_STRU;

/*Content of Concatenated short message, 16-bit reference number*/
typedef struct
{
    VOS_UINT16                          usMr;                               /*Concatenated short messages, 16-bit reference number*/
    VOS_UINT8                           ucTotalNum;                             /*Maximum number of short messages in the enhanced concatenated short message*/
    VOS_UINT8                           ucSeqNum;                               /*Sequence number of the current short message.*/
} MN_MSG_UDH_CONCAT_16_STRU;

/*Content of Text Formatting*/
enum MN_MSG_TEXTCOLOR_ENUM
{
    MN_MSG_TEXTCOLOR_BLACK                                  =   0x00,
    MN_MSG_TEXTCOLOR_DARKGREY                               =   0x01,
    MN_MSG_TEXTCOLOR_DARKRED                                =   0x02,
    MN_MSG_TEXTCOLOR_DARKYELLOW                             =   0x03,
    MN_MSG_TEXTCOLOR_DARKGREEN                              =   0x04,
    MN_MSG_TEXTCOLOR_DARKCYAN                               =   0x05,
    MN_MSG_TEXTCOLOR_DARKBLUE                               =   0x06,
    MN_MSG_TEXTCOLOR_DARKMAGENTA                            =   0x07,
    MN_MSG_TEXTCOLOR_GREY                                   =   0x08,
    MN_MSG_TEXTCOLOR_WHITE                                  =   0x09,
    MN_MSG_TEXTCOLOR_BRIGHTRED                              =   0x10,
    MN_MSG_TEXTCOLOR_BRIGHTYELLOW                           =   0x11,
    MN_MSG_TEXTCOLOR_BRIGHTGREEN                            =   0x12,
    MN_MSG_TEXTCOLOR_BRIGHTCYAN                             =   0x13,
    MN_MSG_TEXTCOLOR_BRIGHTBLUE                             =   0x14,
    MN_MSG_TEXTCOLOR_BRIGHTMAGENTA                          =   0x15
};
typedef VOS_UINT8 MN_MSG_TEXTCOLOR_ENUM_UINT8;

typedef struct
{
   VOS_BOOL                             bColor;
   MN_MSG_TEXTCOLOR_ENUM_UINT8          enForegroundColor;
   MN_MSG_TEXTCOLOR_ENUM_UINT8          enBackgroundColor;
    VOS_UINT8                           aucReserve1[2];
}MN_MSG_TEXT_COLOR_STRU;

typedef struct
{
    VOS_UINT8                           ucStartPos;                             /*Start position of the text formatting.*/
    VOS_UINT8                           ucLen;                                  /*Text formatting length. Gives the number of formatted characters*/
    MN_MSG_UDH_ALIGN_ENUM_U8            enAlign;                                /*Alignment bit 0 and  bit 1*/
    MN_MSG_UDH_FONT_ENUM_U8             enFontSize ;                                /*Font Size bit 3 and  bit 2*/
    VOS_BOOL                            bStyleBold;                             /*Style bold bit 4 */
    VOS_BOOL                            bStyleItalic;                           /*Style Italic bit 5  */
    VOS_BOOL                            bStyleUnderlined;                       /*Style Underlined bit 6 */
    VOS_BOOL                            bStyleStrkthrgh;                        /*Style Strikethrough bit 7 */
    MN_MSG_TEXT_COLOR_STRU              stColor;                                /*Text Colour Octet 4*/
} MN_MSG_UDH_TEXT_FORMAT_STRU;

/*Content of Predefined Sound*/
typedef struct
{
    VOS_UINT8                           ucPos;                                  /*position indicating in the SM data the instant after which the sound shall be played.*/
    VOS_UINT8                           ucdNumofSound;                          /*sound number*/
    VOS_UINT8                           aucReserve1[2];
} MN_MSG_UDH_PRE_DEF_SOUND_STRU;

/*Content of User Defined Sound (iMelody max 128 bytes)*/
#define MN_MSG_UDH_MAX_SOUND_SIZE                           128
typedef struct
{
    VOS_UINT8                           ucPos;                                  /*position indicating in the SM data the instant the after which the sound shall be played*/
    VOS_UINT8                           ucSizeofSound;                          /*size of User Defined Sound*/
    VOS_UINT8                           aucReserve1[2];
    VOS_UINT8                           aucDefSound[MN_MSG_UDH_MAX_SOUND_SIZE]; /*This octet(s) shall contain a User Defined Sound.*/
} MN_MSG_UDH_USER_DEF_SOUND_STRU;

/*Content of Predefined Animation*/
typedef struct
{
    VOS_UINT8                           ucPos;                                  /*position indicating in the SM data the instant the animation shall be displayed.*/
    VOS_UINT8                           ucNumofAnim;                            /*animation number*/
    VOS_UINT8                           aucReserve1[2];
} MN_MSG_UDH_PRE_DEF_ANIM_STRU;

/*Content of Large Animation (16*16 times 4 = 32*4 =128 bytes)*/
#define  MN_MSG_UDH_ANIM_PIC_NUM                            4
#define  MN_MSG_UDH_ANIM_LARGE_PIC_SIZE                     32
typedef struct
{
    VOS_UINT8                           ucPos;                                  /*position indicating the instant the animation shall be displayed in the SM data */
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT8                           aucData[MN_MSG_UDH_ANIM_PIC_NUM][MN_MSG_UDH_ANIM_LARGE_PIC_SIZE]; /*Protocol Data Unit*/
} MN_MSG_UDH_LARGE_ANIM_STRU;

/*Content of Small Animation (8*8 times 4 = 8*4 =32 bytes)*/
#define  MN_MSG_UDH_ANIM_SMALL_PIC_SIZE                     8
typedef struct
{
    VOS_UINT8                           ucPos;                                  /*position indicating the instant the animation shall be displayed in the SM data*/
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT8                           aucData[MN_MSG_UDH_ANIM_PIC_NUM][MN_MSG_UDH_ANIM_SMALL_PIC_SIZE];/*Protocol Data Unit*/
}MN_MSG_UDH_SMALL_ANIM_STRU;

/*Content of Large Pic (32*32 = 128 bytes)*/
#define MN_MSG_UDH_LARGE_PIC_SIZE                           128
typedef struct
{
    VOS_UINT8                           ucPos;                                  /*position indicating in the SM data the instant the picture shall be displayed.*/
    VOS_UINT8                           aucData[MN_MSG_UDH_LARGE_PIC_SIZE];     /*Protocol Data Unit*/
} MN_MSG_UDH_LARGE_PIC_STRU;

/*Content of Small Pic (16*16 = 32 bytes)*/
#define  MN_MSG_UDH_SMALL_PIC_SIZE                          32
typedef struct
{
    VOS_UINT8                           ucPos;                                  /*position indicating in the SM data the instant the picture shall be displayed in the SM data*/
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT8                           aucData[MN_MSG_UDH_SMALL_PIC_SIZE];     /*Protocol Data Unit*/
} MN_MSG_UDH_SMALL_PIC_STRU;

/*Content of Variable Pic*/
#define  MN_MSG_UDH_VAR_PIC_SIZE                            134
typedef struct
{
    VOS_UINT8                           ucPos;                                  /*position indicating in the SM data the instant the picture shall be displayed in the SM data */
    VOS_UINT8                           ucHorDim;                               /*Horizontal dimension of the picture*/
    VOS_UINT8                           ucVertDim ;                             /*Vertical dimension of the picture*/
    VOS_UINT8                           aucReserve1[1];
    VOS_UINT8                           aucData[MN_MSG_UDH_VAR_PIC_SIZE];       /*Protocol Data Unit*/
    VOS_UINT8                           aucReserve2[2];
} MN_MSG_UDH_VAR_PIC_STRU;

/*Content of User prompt indicator*/
typedef struct
{
    VOS_UINT8                           ucNumofObjects;                         /*Number of corresponding objects*/
    VOS_UINT8                           aucReserve1[3];
} MN_MSG_UDH_USER_PROMPT_STRU;

/*Content of RFC 822 E-Mail Header*/
typedef struct
{
    VOS_UINT8                           ucLen;                                  /*RFC 822 E-Mail Header length indicator*/
    VOS_UINT8                           aucReserve1[3];
} MN_MSG_UDH_RFC822_STRU;

/*Content of SMSC Control Parameters Header*/
typedef struct
{
    VOS_BOOL                            bCompletionReport;                      /* bit 0:Status Report for short message transaction completed */
    VOS_BOOL                            bPermErrReport;                         /* bit 1:Status Report for permanent error when SC is not making any more transfer attempts */
    VOS_BOOL                            bTempErrNoneAttemptReport;              /* bit 2:Status Report for temporary error when SC is not making any more transfer attempts */
    VOS_BOOL                            bTempErrWithAttemptReport;              /* bit 3:Status Report for temporary error when SC is still trying to transfer SM */
    VOS_BOOL                            bActivation;                            /* bit 6:A Status Report generated by this Short Message, due to a permanent error or last temporary error, cancels the SRR of the rest of the Short Messages in a concatenated message. This feature can only be used where a SC is aware of the segmentation of a concatenated SM and is therefore an implementation matter.*/
    VOS_BOOL                            bOrigUdhInclude;                        /* bit 7:include original UDH into the Status Report*/
}MN_MSG_SELSTATUS_REPORT_STRU;
typedef struct
{
    MN_MSG_SELSTATUS_REPORT_STRU        stSelectiveStatusReport;                /*Selective Status Report*/
}MN_MSG_UDH_SMSC_CTRL_STRU;

/*Content of UDH Source Indicator Header*/
enum MN_MSG_ORIGINALENTITY_ENUM
{
    MN_MSG_ORIGINALENTITY_SENDER                            = 0x01,
    MN_MSG_ORIGINALENTITY_RECEIVER                          = 0x02,
    MN_MSG_ORIGINALENTITY_SMSC                              = 0x03
};
typedef VOS_UINT8 MN_MSG_ORIGINALENTITY_ENUM_U8;

typedef struct
{
    MN_MSG_ORIGINALENTITY_ENUM_U8       enOrgEntity;
    VOS_UINT8                           aucReserve1[3];
}MN_MSG_UDH_SOURCE_IND_STRU;

/*->f62575*/
/*MN_MSG_MAX_UDH_EO_DATA_LEN * MN_MSG_MAX_UDH_EO_NUM - 3 */
#define MN_MSG_MAX_UDH_LONG_EO_DATA_LEN                     914
typedef struct
{
    VOS_BOOL                            bFirstSegment;
    VOS_UINT8                           ucRefNum;
    VOS_UINT8                           aucReserve1[1];
    VOS_UINT16                          usTotalLen;
    VOS_BOOL                            bObjNotFowarded;
    VOS_BOOL                            bObjHandledAsUserPrompt;
    MN_MSG_EO_TYPE_ENUM_U8              enType;
    VOS_UINT8                           aucReserve2[3];
    VOS_UINT16                          usPos;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           aucData[MN_MSG_MAX_UDH_LONG_EO_DATA_LEN];
    VOS_UINT8                           aucReserve3[2];
}MN_MSG_UDH_EO_STRU;

typedef struct
{

    VOS_UINT8                           ucRefNum;
    VOS_UINT8                           aucReserve1[1];
    VOS_UINT16                          usPos;
}MN_MSG_UDH_REO_STRU;

/*140 - 1(UDHL) - 1(IEI) - 1(IEIDL) - 3(data以外数据长度)*/
#define MN_MSG_UDH_MAX_COMPRESSION_DATA_LEN                 134
typedef struct
{
    MN_MSG_COMPRESSION_ALGORITHM_U8     enCompressionAlgorithm;
    VOS_UINT8                           aucReserve1[1];
    VOS_UINT16                          usTotalLen;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           aucData[MN_MSG_UDH_MAX_COMPRESSION_DATA_LEN];
}MN_MSG_UDH_CC_STRU;

typedef struct
{
    VOS_UINT8                           ucIeNum;
    VOS_UINT8                           aucReserve1[3];
    VOS_BOOL                            bObjNotFowarded;
}MN_MSG_UDH_OBJ_DISTR_STRU;

/*140 - 1(UDHL) - 1(IEI) - 1(IEIDL) - 1(data以外数据长度)*/
#define MN_MSG_UDH_MAX_WVG_DATA_LEN                         136
typedef struct
{
    VOS_UINT8                           ucPos;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           aucReserve1[2];
    VOS_UINT8                           aucData[MN_MSG_UDH_MAX_WVG_DATA_LEN];
}MN_MSG_UDH_WVG_OBJ_STRU;

typedef struct
{
    VOS_UINT16  usPos;
    VOS_UINT8   ucHyperLinkTitleLen;
    VOS_UINT8   ucUrlLen;
}MN_MSG_HYPERLINK_FORMAT_STRU;

typedef struct
{
    MN_MSG_ASCII_ADDR_STRU stReplyAddr;
}MN_MSG_UDH_REPLY_ADDR_STRU;

/*->f62575*/

/*Content of Other TP User Data Header*/
#define  MN_MSG_UDH_OTHER_SIZE                              160
typedef struct
{
   VOS_UINT8                            ucLen;                                  /*Length of other user header type*/
    VOS_UINT8                           aucReserve1[3];
   VOS_UINT8                            aucData[MN_MSG_UDH_OTHER_SIZE];         /*Content of other user header type*/
} MN_MSG_UDH_OTHER_STRU;

/*Detail of each TP User Data Header*/
typedef struct
{
    MN_MSG_UDH_TYPE_ENUM_U8             enHeaderID;
    VOS_UINT8                           aucReserve1[3];
    union
    {
    MN_MSG_UDH_CONCAT_8_STRU            stConcat_8;                             /*00*/
    MN_MSG_UDH_SPECIAL_SMS_STRU         stSpecial_Sms;                          /*01*/
    MN_MSG_UDH_APPPORT_8_STRU           stAppPort_8;                            /*04*/
    MN_MSG_UDH_APPPORT_16_STRU          stAppPort_16;                           /*05*/
    MN_MSG_UDH_SMSC_CTRL_STRU           stSmscCtrl;                             /*06*/
    MN_MSG_UDH_SOURCE_IND_STRU          stSrcInd;                               /*07*/
    MN_MSG_UDH_CONCAT_16_STRU           stConcat_16;                            /*08*/
    MN_MSG_UDH_TEXT_FORMAT_STRU         stText_Format;                          /*0a*/
    MN_MSG_UDH_PRE_DEF_SOUND_STRU       stPreDef_Sound;                         /*0b*/
    MN_MSG_UDH_USER_DEF_SOUND_STRU      stUserDef_Sound;                        /*0c*/
    MN_MSG_UDH_PRE_DEF_ANIM_STRU        stPreDef_Anim;                          /*0d*/
    MN_MSG_UDH_LARGE_ANIM_STRU          stLarge_Anim;                           /*0e*/
    MN_MSG_UDH_SMALL_ANIM_STRU          stSmall_Anim;                           /*0f*/
    MN_MSG_UDH_LARGE_PIC_STRU           stLarge_Pic;                            /*10*/
    MN_MSG_UDH_SMALL_PIC_STRU           stSmall_Pic;                            /*11*/
    MN_MSG_UDH_VAR_PIC_STRU             stVar_Pic;                              /*12*/
    MN_MSG_UDH_USER_PROMPT_STRU         stUser_Prompt;                          /*13*/
    MN_MSG_UDH_EO_STRU                  stEo;                                   /*14*/
    MN_MSG_UDH_REO_STRU                 stReo;                                  /*15*/
    MN_MSG_UDH_CC_STRU                  stCc;                                   /*16*/
    MN_MSG_UDH_OBJ_DISTR_STRU           stObjDistr;                             /*17*/
    MN_MSG_UDH_WVG_OBJ_STRU             stWvgObj;                               /*18,19*/
    MN_MSG_UDH_RFC822_STRU              stRfc822;                               /*20*/
    MN_MSG_HYPERLINK_FORMAT_STRU        stHyperLinkFormat;                      /*21*/
    MN_MSG_UDH_REPLY_ADDR_STRU          stReplyAddr;                            /*22*/
    MN_MSG_UDH_OTHER_STRU               stOther;
    }u;
} MN_MSG_USER_HEADER_TYPE_STRU;

/*Content of TP User Data Header*/
#define MN_MSG_MAX_UDH_NUM                                  7
typedef struct
{
    VOS_UINT32                          ulLen;                                  /*Length of sms*/
    VOS_UINT8                           aucOrgData[MN_MSG_MAX_LEN];             /*sms content,not 7bit,all 8bit */

    VOS_UINT8                           ucNumofHeaders;                         /*number of user header*/
    MN_MSG_USER_HEADER_TYPE_STRU        astUserDataHeader[MN_MSG_MAX_UDH_NUM];  /*detail of user header*/
} MN_MSG_USER_DATA_STRU;

/*Content of TP User Data(Concatenate Sms) */
#define MN_MSG_LONG_SMS_MAX_LEN                             (255*153)
typedef struct
{
    VOS_UINT8                           ucNumofHeaders;                         /*number of user header*/
    VOS_UINT8                           aucReserve1[3];
    MN_MSG_USER_HEADER_TYPE_STRU        astUserDataHeader[MN_MSG_MAX_UDH_NUM];  /*detail of user header*/
    VOS_UINT32                          ulLen;                                  /*Length of sms*/
    VOS_UINT8                           *pucOrgData;       /*sms content,not 7bit,all 8bit */
}MN_MSG_LONG_USER_DATA_STRU;

/*Content of Deliver TPDU*/
typedef struct
{
    VOS_BOOL                            bMoreMsg;                               /*TP-MMS*/
    VOS_BOOL                            bReplayPath;                            /*TP-RP*/
    VOS_BOOL                            bUserDataHeaderInd;                     /*TP-UDHI*/
    VOS_BOOL                            bStaRptInd;                             /*TP-SRI*/
    MN_MSG_ASCII_ADDR_STRU              stOrigAddr;                             /*TP-OA*/
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid;                                  /*TP-PID*/
    VOS_UINT8                           aucReserve1[3];
    MN_MSG_DCS_CODE_STRU                stDcs;                                  /*TP-DCS*/
    MN_MSG_TIMESTAMP_STRU               stTimeStamp;                            /*TP-SCTS*/
    MN_MSG_USER_DATA_STRU               stUserData;                             /*TP-UD*/
} MN_MSG_DELIVER_STRU ;

/*Content of Deliver TPDU(Concatenate Sms Msg)*/
typedef struct
{
    VOS_BOOL                            bMoreMsg;                               /*TP-MMS*/
    VOS_BOOL                            bReplayPath;                            /*TP-RP*/
    VOS_BOOL                            bUserDataHeaderInd;                     /*TP-UDHI*/
    VOS_BOOL                            bStaRptInd;                             /*TP-SRI*/
    MN_MSG_ASCII_ADDR_STRU              stOrigAddr;                             /*TP-OA*/
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid;                                  /*TP-PID*/
    VOS_UINT8                           aucReserve1[3];
    MN_MSG_DCS_CODE_STRU                stDcs;                                  /*TP-DCS*/
    MN_MSG_TIMESTAMP_STRU               stTimeStamp;                            /*TP-SCTS*/
    VOS_UINT8                           aucReserve2[4];
    MN_MSG_LONG_USER_DATA_STRU          stLongUserData;                         /*TP-UD*/
}MN_MSG_DELIVER_LONG_STRU;

/*Content of Deliver Report-Ack TPDU */
typedef struct
{
    VOS_BOOL                            bUserDataHeaderInd;                     /*TP-UDHI*/
    VOS_UINT8                           ucParaInd ;                             /*TP-PI*/
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid;                                  /*TP-PID*/
    VOS_UINT8                           aucReserve1[2];
    MN_MSG_DCS_CODE_STRU                stDcs;                                  /*TP-DCS*/
    MN_MSG_USER_DATA_STRU               stUserData;                             /*TP-UD*/
} MN_MSG_DELIVER_RPT_ACK_STRU;

/*Content of Deliver Report-Error TPDU*/
typedef struct
{
    VOS_BOOL                            bUserDataHeaderInd;                     /*TP-UDHI*/
    MN_MSG_TP_CAUSE_ENUM_U8             enFailCause ;                           /*TP-FCS*/
    VOS_UINT8                           ucParaInd ;                             /*TP-PI*/
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid;                                  /*TP-PID*/
    VOS_UINT8                           aucReserve1[1];
    MN_MSG_DCS_CODE_STRU                stDcs;                                  /*TP-DCS*/
    MN_MSG_USER_DATA_STRU               stUserData;                             /*TP-UD*/
} MN_MSG_DELIVER_RPT_ERR_STRU;

/*Content of Submit TPDU*/
typedef struct
{
    VOS_BOOL                            bRejectDuplicates;                      /*TP-RD*/
    VOS_BOOL                            bReplayPath;                            /*TP-RP*/
    VOS_BOOL                            bUserDataHeaderInd;                     /*TP-UDHI*/
    VOS_BOOL                            bStaRptReq;                             /*TP-SRR*/
    VOS_UINT8                           ucMr;                                   /*TP-MR*/
    VOS_UINT8                           aucReserve1[3];
    MN_MSG_ASCII_ADDR_STRU              stDestAddr;                             /*TP-DA*/
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid;                                  /*TP-PID*/
    VOS_UINT8                           aucReserve2[3];
    MN_MSG_DCS_CODE_STRU                stDcs;                                  /*TP-DCS*/
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;                          /*TP-VPF& TP-VP*/
    MN_MSG_USER_DATA_STRU               stUserData;                             /*TP-UD*/
} MN_MSG_SUBMIT_STRU;

/*Content of Submit TPDU(Concatenate Sms Msg)*/
typedef struct
{
    VOS_BOOL                            bRejectDuplicates;                      /*TP-RD*/
    VOS_BOOL                            bReplayPath;                            /*TP-RP*/
    VOS_BOOL                            bUserDataHeaderInd;                     /*TP-UDHI*/
    VOS_BOOL                            bStaRptReq;                             /*TP-SRR*/
    VOS_UINT8                           ucMr;                                   /*TP-MR*/
    VOS_UINT8                           aucReserve1[3];
    MN_MSG_ASCII_ADDR_STRU              stDestAddr;                             /*TP-DA*/
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid;                                  /*TP-PID*/
    VOS_UINT8                           aucReserve2[3];
    MN_MSG_DCS_CODE_STRU                stDcs;                                  /*TP-DCS*/
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;                          /*TP-VPF& TP-VP*/
    VOS_UINT8                           aucReserve3[4];
    MN_MSG_LONG_USER_DATA_STRU          stLongUserData;                         /*TP-UD*/
}MN_MSG_SUBMIT_LONG_STRU;

/*Content of Status Report-Ack TPDU*/
typedef struct
{
    VOS_BOOL                            bUserDataHeaderInd;                     /*TP-UDHI*/
    MN_MSG_TIMESTAMP_STRU               stTimeStamp;                            /*TP-SCTS*/
    VOS_UINT8                           ucParaInd;                              /*TP-PI*/
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid;                                  /*TP-PID*/
    VOS_UINT8                           aucReserve1[2];
    MN_MSG_DCS_CODE_STRU                stDcs;                                  /*TP-DCS*/
    MN_MSG_USER_DATA_STRU               stUserData;                             /*TP-UD*/
} MN_MSG_SUBMIT_RPT_ACK_STRU;

/*Content of Submit Report-Error TPDU*/
typedef struct
{
    VOS_BOOL                            bUserDataHeaderInd;                     /*TP-UDHI*/
    MN_MSG_TP_CAUSE_ENUM_U8             enFailCause;                            /*TP-FCS*/
    VOS_UINT8                           aucReserve1[3];
    MN_MSG_TIMESTAMP_STRU               stTimeStamp;                            /*TP-SCTS*/
    VOS_UINT8                           ucParaInd;                              /*TP-PI*/
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid;                                  /*TP-PID*/
    VOS_UINT8                           aucReserve2[2];
    MN_MSG_DCS_CODE_STRU                stDcs;                                  /*TP-DCS*/
    MN_MSG_USER_DATA_STRU               stUserData;                             /*TP-UD*/
} MN_MSG_SUBMIT_RPT_ERR_STRU;

/*Content of Status Report TPDU*/
typedef struct
{
    VOS_BOOL                            bUserDataHeaderInd;                     /*TP-UDHI*/
    VOS_BOOL                            bMoreMsg;                               /*TP-MMS*/
    VOS_BOOL                            bStaRptQualCommand;                     /*TP-SRQ*/
    VOS_UINT8                           ucMr;                                   /*TP-MR*/
    VOS_UINT8                           aucReserve1[3];
    MN_MSG_ASCII_ADDR_STRU              stRecipientAddr;                        /*TP-RA*/
    MN_MSG_TIMESTAMP_STRU               stTimeStamp;                            /*TP-SCTS*/
    MN_MSG_TIMESTAMP_STRU               stDischargeTime;                        /*TP-DT*/
    MN_MSG_TP_STATUS_ENUM_U8            enStatus;                               /*TP-ST*/
    VOS_UINT8                           ucParaInd ;                             /*TP-PI*/
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid;                                  /*TP-PID*/
    VOS_UINT8                           aucReserve2[1];
    MN_MSG_DCS_CODE_STRU                stDcs;                                  /*TP-DCS*/
    MN_MSG_USER_DATA_STRU               stUserData;                             /*TP-UD*/
} MN_MSG_STA_RPT_STRU;

/*Content of Command TPDU*/
#define  MN_MSG_MAX_COMMAND_DATA_LEN                        146
typedef struct
{
    VOS_BOOL                            bUserDataHeaderInd;                     /*TP-UDHI*/
    VOS_BOOL                            bStaRptReq;                             /*TP-SRR*/
    VOS_UINT8                           ucMr;                                   /*TP-MR*/
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid;                                  /*TP-PID*/
    MN_MSG_COMMAND_TYPE_ENUM_U8         enCmdType;                              /*TP-CT*/
    VOS_UINT8                           ucMsgNumber;                            /*TP-MN*/
    MN_MSG_ASCII_ADDR_STRU              stDestAddr    ;                         /*TP-DA*/
    VOS_UINT8                           ucCommandDataLen;                       /*TP-CDL*/
    VOS_UINT8                           aucCmdData[MN_MSG_MAX_COMMAND_DATA_LEN];/*TP-CD*/
    VOS_UINT8                           aucReserve1[1];
} MN_MSG_COMMAND_STRU;

/*Content of TPDU*/
typedef struct
{
    MN_MSG_TPDU_TYPE_ENUM_U8            enTpduType;
    VOS_UINT8                           aucReserve1[3];
    union
    {
    MN_MSG_DELIVER_STRU                 stDeliver;
    MN_MSG_DELIVER_RPT_ACK_STRU         stDeliverRptAck;
    MN_MSG_DELIVER_RPT_ERR_STRU         stDeliverRptErr;
    MN_MSG_SUBMIT_STRU                  stSubmit;
    MN_MSG_SUBMIT_RPT_ACK_STRU          stSubmitRptAck;
    MN_MSG_SUBMIT_RPT_ERR_STRU          stSubmitRptErr;
    MN_MSG_STA_RPT_STRU                 stStaRpt;
    MN_MSG_COMMAND_STRU                 stCommand;
    } u;
} MN_MSG_TS_DATA_INFO_STRU;

/*Sms default service para */
typedef struct
{
    VOS_BOOL                            bReplayPath;                            /*TP-RP*/
    VOS_BOOL                            bUserDataHeaderInd;                     /*TP-UDHI*/
    VOS_BOOL                            bStaRptReq;                             /*TP-SRR*/
    VOS_UINT8                           ucMr;                                   /*TP-MR*/
    VOS_UINT8                           aucReserve1[3];
    MN_MSG_ASCII_ADDR_STRU              stDestAddr;                             /*TP-DA*/
    MN_MSG_USER_DATA_STRU               stUserData;                             /*TP-UD*/
} MN_MSG_SUBMIT_DEF_PARM_STRU;

/*Sms Rp Cause Info*/
typedef struct
{
    VOS_BOOL                            bDiagnosticsExist;                      /*is true while Diagnostic field present*/
    VOS_UINT8                           ucDiagnostics;                          /*a diagnostic field giving further details of the error cause*/
    MN_MSG_RP_CAUSE_ENUM_U8             enRpCause;                              /*rp cause*/
    VOS_UINT8                           aucReserve1[2];
}MN_MSG_RP_CAUSE_STRU;

/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
/*****************************************************************************
 枚举名    : TAF_MSG_ERROR_ENUM
 结构说明  : TAF与TAF用户的接口错误码
             0              无错误，仅用于短信命令或短信命令发送成功
             1     - 0x100  内部错误码
             0x100 - 0x200  CP-ERROR消息错误码，由TAF_MSG_ERROR_CP_ERROR_BEGIN和CP-ERROR空口消息的错误码(低8BIT)组成
             0x200 - 0x300  RP-ERROR消息错误码，由TAF_MSG_ERROR_RP_ERROR_BEGIN和RP-ERROR空口消息的错误码(低8BIT)组成
             0x300 - 0x400  CS域通道错误码，由TAF_MSG_ERROR_CS_ERROR_BEGIN和MM上报消息MMSMS_REL_IND的错误码(低8BIT)组成
             0x400 - 0x500  PS域通道错误码，由TAF_MSG_ERROR_PS_ERROR_BEGIN和GMM上报消息PMMSMS_ERROR_IND的错误码(低8BIT)组成
             0x500 - 0x600  EPS域通道错误码，由TAF_MSG_ERROR_EPS_ERROR_BEGIN和GMM上报消息ID_LMM_SMS_ERR_IND的错误码(低8BIT)组成
1.日    期   : 2013年6月26日
  作    者   : f62575
  修改内容   : V9R1 STK升级，新创建
2.日    期   : 2013年10月11日
  作    者   : s00217060
  修改内容   : VoLTE_PhaseII项目，适应IMSA接口

*****************************************************************************/
enum TAF_MSG_ERROR_ENUM
{
    TAF_MSG_ERROR_NO_ERROR                = 0x0000,

    TAF_MSG_ERROR_STATE_NOT_COMPATIBLE    = 0x0001,

    TAF_MSG_ERROR_NO_SERVICE              = 0x0002,

    TAF_MSG_ERROR_TC1M_TIMEOUT            = 0x0003,

    TAF_MSG_ERROR_TR1M_TIMEOUT            = 0x0004,

    TAF_MSG_ERROR_TR2M_TIMEOUT            = 0x0005,

    TAF_MSG_ERROR_USER_ABORT              = 0x0006,

	/* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-10-11, begin */
    TAF_MSG_ERROR_TP_ERROR_BEGIN          = 0x010000,

    TAF_MSG_ERROR_TP_FCS_TELEMATIC_INTERWORKING_NOT_SUPPORTED                   = 0x010080,
    TAF_MSG_ERROR_TP_FCS_SHORT_MESSAGE_TYPE_0_NOT_SUPPORTED                     = 0x010081,
    TAF_MSG_ERROR_TP_FCS_CANNOT_REPLACE_SHORT_MESSAGE                           = 0x010082,
    TAF_MSG_ERROR_TP_FCS_UNSPECIFIED_TPPID_ERROR                                = 0x01008f,
    TAF_MSG_ERROR_TP_FCS_DATA_CODING_SCHEME_ALPHABET_NOT_SUPPORTED              = 0x010090,
    TAF_MSG_ERROR_TP_FCS_MESSAGE_CLASS_NOT_SUPPORTED                            = 0x010091,
    TAF_MSG_ERROR_TP_FCS_UNSPECIFIED_TPDCS_ERROR                                = 0x01009f,
    TAF_MSG_ERROR_TP_FCS_COMMAND_CANNOT_BE_ACTIONED                             = 0x0100a0,
    TAF_MSG_ERROR_TP_FCS_COMMAND_UNSUPPORTED                                    = 0x0100a1,
    TAF_MSG_ERROR_TP_FCS_UNSPECIFIED_TPCOMMAND_ERROR                            = 0x0100af,
    TAF_MSG_ERROR_TP_FCS_TPDU_NOT_SUPPORTED                                     = 0x0100b0,
    TAF_MSG_ERROR_TP_FCS_SC_BUSY                                                = 0x0100c0,
    TAF_MSG_ERROR_TP_FCS_NO_SC_SUBSCRIPTION                                     = 0x0100c1,
    TAF_MSG_ERROR_TP_FCS_SC_SYSTEM_FAILURE                                      = 0x0100c2,
    TAF_MSG_ERROR_TP_FCS_INVALID_SME_ADDRESS                                    = 0x0100c3,
    TAF_MSG_ERROR_TP_FCS_DESTINATION_SME_BARRED                                 = 0x0100c4,
    TAF_MSG_ERROR_TP_FCS_SM_REJECTEDDUPLICATE_SM                                = 0x0100c5,
    TAF_MSG_ERROR_TP_FCS_TPVPF_NOT_SUPPORTED                                    = 0x0100c6,
    TAF_MSG_ERROR_TP_FCS_TPVP_NOT_SUPPORTED                                     = 0x0100c7,
    TAF_MSG_ERROR_TP_FCS_SIM_SMS_STORAGE_FULL                                   = 0x0100d0,
    TAF_MSG_ERROR_TP_FCS_NO_SMS_STORAGE_CAPABILITY_IN_SIM                       = 0x0100d1,
    TAF_MSG_ERROR_TP_FCS_ERROR_IN_MS                                            = 0x0100d2,
    TAF_MSG_ERROR_TP_FCS_MEMORY_CAPACITY_EXCEEDED                               = 0x0100d3,
    TAF_MSG_ERROR_TP_FCS_SIM_APPLICATION_TOOLKIT_BUSY                           = 0x0100d4,
    TAF_MSG_ERROR_TP_FCS_SIM_DATA_DOWNLOAD_ERROR                                = 0x0100d5,
    TAF_MSG_ERROR_TP_FCS_UNSPECIFIED_ERROR_CAUSE                                = 0x0100ff,

    TAF_MSG_ERROR_CP_ERROR_BEGIN          = 0x020000,

    TAF_MSG_ERROR_RP_ERROR_BEGIN          = 0x040000,

    TAF_MSG_ERROR_RP_CAUSE_UNASSIGNED_UNALLOCATED_NUMBER                        = 0x040001,
    TAF_MSG_ERROR_RP_CAUSE_OPERATOR_DETERMINED_BARRING                          = 0x040008,
    TAF_MSG_ERROR_RP_CAUSE_CALL_BARRED                                          = 0x04000a,
    TAF_MSG_ERROR_RP_CAUSE_SHORT_MESSAGE_TRANSFER_REJECTED                      = 0x040015,
    TAF_MSG_ERROR_RP_CAUSE_DESTINATION_OUT_OF_ORDER                             = 0x04001b,
    TAF_MSG_ERROR_RP_CAUSE_UNIDENTIFIED_SUBSCRIBER                              = 0x04001c,
    TAF_MSG_ERROR_RP_CAUSE_FACILITY_REJECTED                                    = 0x04001d,
    TAF_MSG_ERROR_RP_CAUSE_UNKNOWN_SUBSCRIBER                                   = 0x04001e,
    TAF_MSG_ERROR_RP_CAUSE_NETWORK_OUT_OF_ORDER                                 = 0x040026,
    TAF_MSG_ERROR_RP_CAUSE_TEMPORARY_FAILURE                                    = 0x040029,
    TAF_MSG_ERROR_RP_CAUSE_CONGESTION                                           = 0x04002a,
    TAF_MSG_ERROR_RP_CAUSE_RESOURCES_UNAVAILABLE_UNSPECIFIED                    = 0x04002f,
    TAF_MSG_ERROR_RP_CAUSE_REQUESTED_FACILITY_NOT_SUBSCRIBED                    = 0x040032,
    TAF_MSG_ERROR_RP_CAUSE_REQUESTED_FACILITY_NOT_IMPLEMENTED                   = 0x040045,
    TAF_MSG_ERROR_RP_CAUSE_INVALID_SHORT_MESSAGE_TRANSFER_REFERENCE_VALUE       = 0x040051,
    TAF_MSG_ERROR_RP_CAUSE_INVALID_MANDATORY_INFORMATION                        = 0x040060,
    TAF_MSG_ERROR_RP_CAUSE_MESSAGE_TYPE_NON_EXISTENT_OR_NOT_IMPLEMENTED         = 0x040061,
    TAF_MSG_ERROR_RP_CAUSE_MESSAGE_NOT_COMPATIBLE_WITH_SHORT_MESSAGE_PROTOCOL_STATE = 0x040062,
    TAF_MSG_ERROR_RP_CAUSE_INFORMATION_ELEMENT_NON_EXISTENT_OR_NOT_IMPLEMENTED  = 0x040063,
    TAF_MSG_ERROR_RP_CAUSE_PROTOCOL_ERROR_UNSPECIFIED                           = 0x04006f,
    TAF_MSG_ERROR_RP_CAUSE_INTERWORKING_UNSPECIFIED                             = 0x04007f,

    TAF_MSG_ERROR_CS_ERROR_BEGIN          = 0x080000,

    TAF_MSG_ERROR_PS_ERROR_BEGIN          = 0x100000,

    TAF_MSG_ERROR_EPS_ERROR_BEGIN         = 0x200000,

    TAF_MSG_ERROR_IMS_ERROR_BEGIN         = 0x400000,
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-10-11, end */

    TAF_MSG_ERROR_CHECK_ERROR_BEGIN       = 0x800000,

    TAF_MSG_ERROR_FDN_CHECK_FAIL          = 0x800001,
    TAF_MSG_ERROR_FDN_CHECK_TIMEROUT      = 0x800002,

    TAF_MSG_ERROR_CTRL_CHECK_FAIL         = 0x800010,
    TAF_MSG_ERROR_CTRL_CHECK_TIMEOUT      = 0x800011,

    TAF_MSG_ERROR_ERROR_BUTT              = 0xFFFFFFFF
};
typedef VOS_UINT32 TAF_MSG_ERROR_ENUM_UINT32;
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

/*event report:MN_MSG_SUBMIT_RPT_EVT_INFO_STRU*/
/*****************************************************************************
 结构名    : MN_MSG_SUBMIT_RPT_EVT_INFO_STRU
 结构说明  : TAF给AT上报的短信发送结果消息结构
  1.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级，删除aucReserve1，stRpCause
                 增加enErrorCode
*****************************************************************************/
typedef struct
{
    TAF_MSG_ERROR_ENUM_UINT32           enErrorCode;
    VOS_UINT8                           ucMr;                                   /*msg reference*/
    MN_MSG_MEM_STORE_ENUM_U8            enSaveArea;                             /*save area*/
    VOS_UINT8                           aucReserve1[2];
    VOS_UINT32                          ulSaveIndex;                            /*save index*/
    MN_MSG_RAW_TS_DATA_STRU             stRawData;                              /*TPDU of sms submit report*/
} MN_MSG_SUBMIT_RPT_EVT_INFO_STRU;

/*event report:MN_MSG_EVT_MSG_SENT,MN_MSG_EVT_MSG_STORED*/
typedef struct
{
    MN_MSG_TPDU_TYPE_ENUM_U8            enTpduType;
    VOS_UINT8                           aucReserve1[3];
} MN_MSG_SENDMSG_EVT_INFO_STRU;

/*event report:MN_MSG_EVT_DELIVER*/
typedef struct
{
    VOS_UINT32                          ulInex;                                 /*index of sms*/
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore;                             /*memory store:NVIM or USIM of received msg*/
    MN_MSG_RCVMSG_ACT_ENUM_U8           enRcvSmAct;                             /*action of received msg*/
    VOS_UINT8                           aucReserve1[2];
    MN_MSG_MSG_INFO_STRU                stRcvMsgInfo;                           /*sms content*/
}MN_MSG_DELIVER_EVT_INFO_STRU;

/*event report:MN_MSG_EVT_DELIVER_ERR*/
/*****************************************************************************
 结构名    : MN_MSG_DELIVER_ERR_EVT_INFO_STRU
 结构说明  : TAF给AT上报的短信或状态报告接收失败消息结构
  1.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级，删除enRptStatus，enRpCause，ulInternalError
                 增加enErrorCode
*****************************************************************************/
typedef struct
{
    TAF_MSG_ERROR_ENUM_UINT32           enErrorCode;
} MN_MSG_DELIVER_ERR_EVT_INFO_STRU;

/*event report:MN_MSG_EVT_SM_STORAGE_LIST*/
#define  MN_MSG_MAX_SM_STATUS                               4
typedef struct
{
    MN_MSG_MEM_STORE_ENUM_U8            enMemStroe;                             /*sms memory store:NVIM or USIM*/
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT32                          ulTotalRec;                             /*sms capacity of NVIM or USIM*/
    VOS_UINT32                          ulUsedRec;                              /*used records including all status*/
    VOS_UINT32                          aulEachStatusRec[MN_MSG_MAX_SM_STATUS]; /*sms number of each status*/
}MN_MSG_STORAGE_LIST_EVT_INFO_STRU;

/*event report:MN_MSG_EVT_STORAGE_FULL,MN_MSG_EVT_STORAGE_EXCEED*/
typedef struct
{
    MN_MSG_MEM_STORE_ENUM_U8            enMemStroe;                             /*sms memory store:NVIM or USIM*/
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT32                          ulTotalRec;                             /*sms capacity of NVIM or USIM*/
    VOS_UINT32                          ulUsedRec;                              /*used records including all status*/
}MN_MSG_STORAGE_STATE_EVT_INFO_STRU;

/*event report:MN_MSG_EVT_READ ,MN_MSG_EVT_READ_STATUSREPORT*/
typedef struct
{
    VOS_BOOL                            bSuccess;                               /*read sms success or failure*/
    VOS_UINT32                          ulFailCause;                            /*Failure case when read failed*/
    VOS_UINT32                          ulIndex;                                /*sms memory index*/
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore;
    MN_MSG_STATUS_TYPE_ENUM_U8          enStatus;                               /*sms status*/
    VOS_UINT8                           aucReserve1[2];
    MN_MSG_MSG_INFO_STRU                stMsgInfo;                              /*sms content*/
}MN_MSG_READ_EVT_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulIndex;                                /*sms memory index*/
    MN_MSG_STATUS_TYPE_ENUM_U8          enStatus;                               /*sms status*/
    VOS_UINT8                           aucReserve1[3];
    MN_MSG_MSG_INFO_STRU                stMsgInfo;                              /*sms content*/
}MN_MSG_EACHSM_LIST_INFO_STRU;
/*event report:MN_MSG_EVT_LIST*/

/*****************************************************************************
 结构名    : MN_MSG_LIST_PARM_STRU
 结构说明  : SMS查询信息
 1.日    期   : 2013年9月29日
   作    者   : wumai 00167002
   修改内容   : DTS2013092100149修改:在CMGL命令查询短消息时候，如果当前短消息
                条数大于10条，则AT收到当前上报的10条消息后，需要通知SMS继续
                上报其余的SMS。
*****************************************************************************/
typedef struct
{
    MN_MSG_STATUS_TYPE_ENUM_U8          enStatus;                               /*sms status*/
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore;                             /*momory store:NVIM or USIM*/

    VOS_UINT8                           ucIsFirstTimeReq;                       /* 消息请求类型:VOS_TRUE 表示首次请求，VOS_FALSE表示请求上报余下部分MSG */
    VOS_UINT8                           aucReserve1[1];
    VOS_BOOL                            bChangeFlag;                            /*change status or not change status after read or list*/
}MN_MSG_LIST_PARM_STRU;

#define  MN_MSG_MAX_REPORT_EVENT_NUM                        10                  /*Max Report Number when List Event Report*/

/*****************************************************************************
 结构名    : MN_MSG_LIST_EVT_INFO_STRU
 结构说明  : SMS查询上报信息
 1.日    期   : 2013年9月29日
   作    者   : wumai 00167002
   修改内容   : DTS2013092100149修改:上报收到的LIST参数信息,AT根据此信息继续
                进行请求。
*****************************************************************************/
typedef struct
{
    VOS_BOOL                            bSuccess;                               /*list sms success or failure*/
    VOS_UINT32                          ulFailCause;                            /*Failure case when list failed*/
    VOS_BOOL                            bLastListEvt;                           /*The Last List Event Info*/
    VOS_UINT32                          ulReportNum;                            /*the num of report evt this time*/
    MN_MSG_EACHSM_LIST_INFO_STRU        astSmInfo[MN_MSG_MAX_REPORT_EVENT_NUM];
    VOS_BOOL                            bFirstListEvt;

    MN_MSG_LIST_PARM_STRU               stReceivedListPara;                     /* 上报收到的LIST参数信息 */
}MN_MSG_LIST_EVT_INFO_STRU;

/*event report:MN_MSG_EVT_WRITE*/
typedef struct
{
    VOS_BOOL                            bSuccess;                               /*write sms success or failure*/
    VOS_UINT32                          ulFailCause;                            /*Failure case when write failed*/
    VOS_UINT32                          ulIndex;                                /*sms memory index*/
    MN_MSG_STATUS_TYPE_ENUM_U8          enStatus;                               /*sms status*/
    MN_MSG_MEM_STORE_ENUM_U8            enMemStroe;                             /*sms memory store*/
    VOS_UINT8                           aucReserve1[2];
}MN_MSG_WRITE_EVT_INFO_STRU;

/*event report:MN_MSG_EVT_DELETE,MN_MSG_EVT_DELETE_SR,
MN_MSG_EVT_DELETE_CBS,MN_MSG_EVT_DELETE_SETSRV_PARAM*/
typedef struct
{
    VOS_BOOL                            bSuccess;                               /*delete success or failure*/
    VOS_UINT32                          ulFailCause;                            /*Failure case when delete failed*/
    VOS_UINT32                          ulIndex;                                /*sms memory index*/
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore;                             /*sms memory store:NVIM or USIM*/
    MN_MSG_DELETE_TYPE_ENUM_U8          enDeleteType;                           /*sms delete type*/
    VOS_UINT8                           aucReserve1[2];
}MN_MSG_DELETE_EVT_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulSmCapacity;
    VOS_UINT32                          aulValidLocMap[MN_MSG_CMGD_PARA_MAX_LEN];
}MN_MSG_DELETE_TEST_EVT_INFO_STRU;

/*event report:MN_MSG_MODIFY_STATUS*/
typedef struct
{
    VOS_BOOL                            bSuccess;                               /*modify success or failure*/
    VOS_UINT32                          ulFailCause;                            /*Failure case when modify failed*/
    VOS_UINT32                          ulIndex;                                /*sms memory index*/
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore;                             /*sms memory store:NVIM or USIM*/
    MN_MSG_STATUS_TYPE_ENUM_U8          enStatus;                               /*sms status*/
    VOS_UINT8                           aucReserve1[2];
}MN_MSG_MODIFY_STATUS_EVT_INFO_STRU;

/*event report:MN_MSG_EVT_SET_SETSRV_PARAM
               MN_MSG_EVT_GET_SETSRV_PARAM*/
typedef struct
{
    VOS_BOOL                            bSuccess;                               /*set(get) success or failure */
    VOS_UINT32                          ulFailCause;                            /*Failure case when set or get failed*/
    MN_MSG_OPER_TYPE_T                  operType;                               /*is Set or Get,Get Including unsolicited report*/
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT32                          ulIndex;                                /*sms serveice para index*/
    MN_MSG_SRV_PARAM_STRU                stSrvParm;                              /*sms serveice para*/
}MN_MSG_SRV_PARM_EVT_INFO_STRU;

/*event report:MN_MSG_EVT_CHANGED_SETSRV_PARAM*/
#define  MN_MSG_MAX_USIM_EFSMSP_NUM                         5                   /*Max record is 5 in USIM of EFSMSP*/
typedef struct
{
    VOS_UINT32                          ulTotalRec;
    VOS_UINT32                          ulUsedRec;
    MN_MSG_SRV_PARAM_STRU               astSrvParm[MN_MSG_MAX_USIM_EFSMSP_NUM];
}MN_MSG_SRV_PARM_CHANGED_EVT_INFO_STRU;

/*event report:MN_MSG_EVT_SETMEMSTATUS,MN_MSG_EVT_MEMSTATUS_CHANGED*/
typedef struct
{
    VOS_BOOL                            bSuccess;                               /*set success*/
    VOS_UINT32                          ulFailCause;                            /*Failure case when set or get failed*/
    MN_MSG_MEM_FLAG_ENUM_U8             enMemFlag ;
    VOS_UINT8                           aucReserve1[3];
}MN_MSG_MEMSTATUS_EVT_INFO_STRU;

/*event report:MN_MSG_EVT_SET_RCVMSG_PATH,MN_MSG_EVT_GET_RCVMSG_PATH,
               MN_MSG_EVT_RCVMSG_PATH_CHANGED*/
typedef struct
{
    VOS_BOOL                            bSuccess;                               /*set(get) success or failure */
    VOS_UINT32                          ulFailCause;                            /*Failure case when set or get failed*/
    MN_MSG_OPER_TYPE_T                  operType;                               /*is Set or Get,Get Including unsolicited report*/
    MN_MSG_RCVMSG_ACT_ENUM_U8           enRcvSmAct;                             /*action of received msg*/
    MN_MSG_MEM_STORE_ENUM_U8            enSmMemStore;                           /*Sm memory store:NVIM or USIM of received msg*/
    MN_MSG_RCVMSG_ACT_ENUM_U8           enRcvStaRptAct;                         /*action of received Status Report msg*/
    MN_MSG_MEM_STORE_ENUM_U8            enStaRptMemStore;                       /*Sm memory store:NVIM or USIM of Status Report msg*/
    MN_MSG_MEM_STORE_ENUM_U8            enCbmMemStore;                          /*Cbm memory store:NVIM of received msg*/
    MN_MSG_CSMS_MSG_VERSION_ENUM_U8     enSmsServVersion;                       /*巴西vivo短信方案-添加变量*/
    VOS_UINT8                           aucReserve1[1];
}MN_MSG_RCVMSG_PATH_EVT_INFO_STRU;

/*event report:MN_MSG_EVT_INIT_RESULT
Para of MN_MSG_SetRcvMsgPath*/
typedef struct
{
    MN_MSG_RCVMSG_ACT_ENUM_U8           enRcvSmAct;                             /*action of received SM msg*/
    MN_MSG_MEM_STORE_ENUM_U8            enSmMemStore;                           /*Sm memory store:NVIM or USIM of SM msg*/
    MN_MSG_RCVMSG_ACT_ENUM_U8           enRcvStaRptAct;                         /*action of received Status Report msg*/
    MN_MSG_MEM_STORE_ENUM_U8            enStaRptMemStore;                       /*Sm memory store:NVIM or USIM of Status Report msg*/
    MN_MSG_CSMS_MSG_VERSION_ENUM_U8     enSmsServVersion;                       /*巴西vivo短信方案-添加变量*/

    MN_MSG_CNMI_MT_TYPE_ENUM_U8         enCnmiMtType;
    VOS_UINT8                           aucReserve1[2];
}MN_MSG_SET_RCVMSG_PATH_PARM_STRU;

/*event report:MN_MSG_EVT_INIT_RESULT*/
typedef struct
{
    VOS_UINT32                          ulTotalSmRec;                           /*sms capacity of USIM*/
    VOS_UINT32                          ulUsedSmRec;                            /*used records including all status*/
    VOS_UINT32                          aulEachStatusRec[MN_MSG_MAX_SM_STATUS]; /*sms number of each status*/
    VOS_UINT32                          ulTotalSmsrRec;                         /*smsr capacity of USIM*/
    VOS_UINT32                          ulUsedSmsrRec;                          /*used records of smsr*/
}MN_MSG_INIT_EVT_INFO_STRU;

/*event report:MN_MSG_EVT_INIT_SMSP_RESULT*/
typedef struct
{
    VOS_UINT32                          ulTotalSrvParm;
    VOS_UINT32                          ulUsedSrvParm;
    MN_MSG_SRV_PARAM_STRU               astSrvParm[MN_MSG_MAX_USIM_EFSMSP_NUM];
    MN_MSG_SET_RCVMSG_PATH_PARM_STRU    stRcvMsgPath;
    MN_MSG_CLASS0_TAILOR_U8             enClass0Tailor;
    VOS_UINT8                           aucReserved[3];
}MN_MSG_INIT_SMSP_EVT_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulErrorCode;                            /*set(get) success or failure */
    MN_MSG_LINK_CTRL_U8                 enLinkCtrl;
    VOS_UINT8                           aucReserved[3];
}MN_MSG_LINK_CTRL_EVT_INFO_STRU;

/* Added by f62575 for AT Project，2011-10-03,  Begin*/
/*****************************************************************************
 枚举名    : MN_MSG_STUB_EVT_INFO_STRU
 结构说明  : 短信桩相关操作结果上报
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulErrorCode;                            /*set(get) success or failure */
}MN_MSG_RESULT_EVT_INFO_STRU;
/* Added by f62575 for AT Project，2011-10-03,  End*/

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

typedef struct
{
    VOS_UINT32                          ulLen;                                  /*Length of cbs user message content */
    VOS_UINT8                           aucContent[TAF_CBA_MAX_RAW_CBDATA_LEN];
    VOS_UINT8                           aucReserve3[3];
}MN_MSG_CBDATA_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucMsgCodingGroup;
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding;                            /*sms msg coding*/
    VOS_UINT8                           aucReserve1[2];
    VOS_BOOL                            bCompressed;
    MN_MSG_CBLANG_ENUM_U8               enMsgLang;
    MN_MSG_MSG_CLASS_ENUM_U8            enMsgClass;
    VOS_UINT8                           ucLangIndLen;                           /*used when ucCodingGroup == 1 Refer to 23038 5.*/
    VOS_UINT8                           ucRawDcsData;                           /*Raw DCS Byte */
}MN_MSG_CBDCS_CODE_STRU;

/*CBS消息中的GS相关信息*/
enum MN_MSG_CBGS_ENUM
{
    MN_MSG_CBGS_CELL_IMME             =    0x00,
    MN_MSG_CBGS_PLMN_NORMAL           =    0x01,
    MN_MSG_CBGS_LA_NORMAL             =    0x02,
    MN_MSG_CBGS_CELL_NORMAL           =    0x03
};
typedef VOS_UINT8 MN_MSG_CBGS_ENUM_UINT8;

typedef struct
{
    MN_MSG_CBGS_ENUM_UINT8              enGs;
    VOS_UINT8                           ucUpdateNumber;
    VOS_UINT16                          usMessageCode;
    VOS_UINT16                          usRawSnData;                            /*Raw SN Byte */
    VOS_UINT8                           aucReserve1[2];
}MN_MSG_CBSN_STRU;

typedef struct
{
    VOS_UINT16                          usMid;
    VOS_UINT8                           ucPageIndex;
    VOS_UINT8                           ucPageNum;

    MN_MSG_CBDCS_CODE_STRU              stDcs;
    MN_MSG_CBSN_STRU                    stSn;
    MN_MSG_CBDATA_INFO_STRU             stContent;
}MN_MSG_CBPAGE_STRU;


/*****************************************************************************
 结构名    : TAF_CBA_CBMI_RANGE_STRU
 结构说明  : 小区广播消息的范围信息
 1.日    期   : 2012年03月17日
   作    者   : z40661
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucLabel[TAF_CBA_MAX_LABEL_NUM]; /* 小区广播消息id范围标签 */
    VOS_UINT16                                              usMsgIdFrom;                    /* 小区广播消息ID的开始序号  */
    VOS_UINT16                                              usMsgIdTo;                      /* 小区广播消息ID的结束序号 */
    TAF_CBA_CBMI_RANGE_RCV_MODE_ENMU_UINT32                 enRcvMode;                      /* 每个CBMI RANGE 的接收模式, 目前仅支持 ACCEPT的模式 */
}TAF_CBA_CBMI_RANGE_STRU;

/*****************************************************************************
 结构名    : TAF_CBA_CBMIR_LIST_STRU
 结构说明  : 小区广播消息ID的范围列表信息
 1.日    期   : 2012年03月17日
   作    者   : z40661
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCbmirNum;                             /* 小区广播消息的ID个数 */
    VOS_UINT8                           aucReserve[6];
    TAF_CBA_CBMI_RANGE_STRU             astCbmiRangeInfo[TAF_CBA_MAX_CBMID_RANGE_NUM]; /* 小区广播消息的范围信息 */
}TAF_CBA_CBMI_RANGE_LIST_STRU;

/*****************************************************************************
 结构名    : TAF_CBA_PLMN_ID_STRU
 结构说明  : PLMN ID的结构
 1.日    期   : 2012年3月01日
   作    者   : l00171473
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;              /* MCC,3 bytes      */
    VOS_UINT32                          ulMnc;              /* MNC,2 or 3 bytes */
}TAF_CBA_PLMN_ID_STRU;



typedef struct
{
    VOS_UINT32                          ulLen;
    VOS_UINT8                           aucData[TAF_CBA_MAX_CBPAGE_LEN];
}MN_MSG_CBRAW_TS_DATA_STRU;


typedef struct
{
    VOS_BOOL                            bSuccess;                               /*Deliver CBM success or failure*/
    VOS_UINT32                          ulFailCause;                            /*Failure case when Deliver failed*/
    MN_MSG_CBRAW_TS_DATA_STRU           stCbRawData;                            /*TPDU*/
}MN_MSG_CB_DELIVER_EVT_INFO_STRU;

/*event report:MN_MSG_EVT_ADD_CBMIDS,MN_MSG_EVT_DELETE_CBMIDS,MN_MSG_EVT_DELETE_ALL_CBMIDS*/
typedef struct
{
    VOS_BOOL                            bSuccess;
    VOS_UINT32                          ulFailCause;
}MN_MSG_CBMIDS_CHANGE_EVT_INFO_STRU;


typedef struct
{
    VOS_BOOL                            bSuccess;                               /*set(get) success or failure */
    VOS_UINT32                          ulFailCause;                            /*Failure case when read or write failed*/
    TAF_CBA_CBMI_RANGE_LIST_STRU        stCbMidr;                               /*CBS Mid Range*/
}MN_MSG_CBMIDS_GET_EVT_INFO_STRU;



typedef struct
{
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    VOS_UINT8                           ucReserved;
    VOS_UINT32                          ulFailCause;                            /*Failure case when read failed*/
}MN_MSG_EVENT_PARM_STRU;



#if (FEATURE_ON == FEATURE_ETWS)

/*****************************************************************************
 结构名    : TAF_CBA_ETWS_PRIM_NTF_EVT_INFO_STRU
 结构说明  : 需要上报到AT的主通知信息的结构
 1.日    期   : 2012年3月01日
   作    者   : l00171473
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_CBA_PLMN_ID_STRU                                    stPlmn;             /* plmn */
    VOS_UINT16                                              usWarnType;         /* 告警类型 */
    VOS_UINT16                                              usMsgId;            /* 消息ID */

    VOS_UINT16                                              usSN;               /* 序列号 */
    TAF_CBA_ETWS_PRIM_NTF_AUTH_RSLT_ENUM_UINT8              enAuthRslt;         /* 鉴权结果 */
    VOS_UINT8                                               ucRsv;              /* 字节对齐保留 */
}TAF_CBA_ETWS_PRIM_NTF_EVT_INFO_STRU;

#endif


#endif  /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */


/*Sms Event Type*/
/*****************************************************************************
 枚举名    : MN_MSG_EVENT_ENUM
 结构说明  : TAF的短信模块事件上报的事件名称
*****************************************************************************/
enum MN_MSG_EVENT_ENUM
{
    MN_MSG_EVT_SUBMIT_RPT,                                                      /* _H2ASN_MsgChoice MN_MSG_SUBMIT_RPT_EVT_INFO_STRU */ /*send msg success or failed*/
    MN_MSG_EVT_MSG_SENT,                                                        /* _H2ASN_MsgChoice MN_MSG_SENDMSG_EVT_INFO_STRU */ /*msg has been sent*/
    MN_MSG_EVT_MSG_STORED,                                                      /*msg has been stored*/
    MN_MSG_EVT_DELIVER,                                                         /*rcv a new msg*/
    MN_MSG_EVT_DELIVER_ERR,                                                     /*rcv a new msg but not rcv deliver-report from APP on time*/
    MN_MSG_EVT_SM_STORAGE_LIST,                                                 /*number of certain status sms in nvim or usim*/
    MN_MSG_EVT_STORAGE_FULL,                                                    /*memory storage full*/
    MN_MSG_EVT_STORAGE_EXCEED,                                                  /*Rcv a SMS,but no memory to rcv*/
    MN_MSG_EVT_READ,                                                            /*read sms*/
    MN_MSG_EVT_LIST,                                                            /*list sms*/
    MN_MSG_EVT_WRITE,                                                           /*write sms*/
    MN_MSG_EVT_DELETE,                                                          /*delete sms*/
    MN_MSG_EVT_DELETE_TEST,                                                     /*delete sms test*/
    MN_MSG_EVT_MODIFY_STATUS,                                                   /*modify sms status*/
    MN_MSG_EVT_WRITE_SRV_PARM,                                                  /*set sms service parameter*/
    MN_MSG_EVT_READ_SRV_PARM,                                                   /*get sms service parameter*/
    MN_MSG_EVT_SRV_PARM_CHANGED,                                                /*service para changed*/
    MN_MSG_EVT_DELETE_SRV_PARM,                                                 /*delete sms service parameter*/
    MN_MSG_EVT_READ_STARPT,                                                     /*read sms status report*/
    MN_MSG_EVT_DELETE_STARPT,                                                   /*delete sms status report*/
    MN_MSG_EVT_SET_MEMSTATUS,                                                   /*set memory status of app*/
    MN_MSG_EVT_MEMSTATUS_CHANGED,                                               /*App memory status changed*/
    MN_MSG_EVT_MATCH_MO_STARPT_INFO,                                            /*get sms from sms status report or get sms status report from sms*/
    MN_MSG_EVT_SET_RCVMSG_PATH,                                                 /*sms set rcv msg path*/
    MN_MSG_EVT_GET_RCVMSG_PATH,                                                 /*sms get rcv msg path*/
    MN_MSG_EVT_RCVMSG_PATH_CHANGED,                                             /*sms rcv msg path changed*/
    MN_MSG_EVT_INIT_SMSP_RESULT,
    MN_MSG_EVT_INIT_RESULT,                                                     /*initialization of sms finished */
    MN_MSG_EVT_SET_LINK_CTRL_PARAM,                                             /*sms set link ctrl parameter*/
    MN_MSG_EVT_GET_LINK_CTRL_PARAM,                                             /*sms get link ctrl parameter*/
    /* Added by f62575 for AT Project，2011-10-03,  Begin*/
    MN_MSG_EVT_STUB_RESULT,                                                     /* 短信相关操作结果上报事件 */
    /* Added by f62575 for AT Project，2011-10-03,  End*/
    /*#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))*/
    MN_MSG_EVT_DELIVER_CBM,                                                     /*rcv a new msg*/
    MN_MSG_EVT_GET_CBTYPE,                                                      /*Get Cbs Type*/
    MN_MSG_EVT_ADD_CBMIDS,                                                      /*Add Cbs Mids*/
    MN_MSG_EVT_DELETE_CBMIDS,                                                   /*Delete Cbs Mids*/
    MN_MSG_EVT_DELETE_ALL_CBMIDS,                                               /*Delete ALL Cbs Mids*/
    MN_MSG_EVT_DELIVER_ETWS_PRIM_NOTIFY,                                        /* rcv a new primary notify */
    /*#endif*/
    MN_MSG_EVT_MAX
};
typedef VOS_UINT32 MN_MSG_EVENT_ENUM_U32;

/*Sms Event Report*/
typedef struct
{
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;                                   /*1-127,APP orig 128-255 Taf orig*/
    VOS_UINT8                           aucReserve1[1];
    union
    {
    MN_MSG_SUBMIT_RPT_EVT_INFO_STRU     stSubmitRptInfo;                        /*event report:MN_MSG_EVT_SUBMIT_RPT*/
    MN_MSG_SENDMSG_EVT_INFO_STRU        stSendMsgInfo;                          /*event report:MN_MSG_EVT_MSG_SENT,MN_MSG_EVT_MSG_STORED*/
    MN_MSG_DELIVER_EVT_INFO_STRU        stDeliverInfo;                          /*event report:MN_MSG_EVT_DELIVER*/
    MN_MSG_DELIVER_ERR_EVT_INFO_STRU    stDeliverErrInfo;                       /*event report:MN_MSG_EVT_DELIVER_ERR*/
    MN_MSG_STORAGE_LIST_EVT_INFO_STRU   stStorageListInfo;                      /*event report:MN_MSG_EVT_SM_STORAGE_LIST*/
    MN_MSG_STORAGE_STATE_EVT_INFO_STRU  stStorageStateInfo;                     /*event report:MN_MSG_EVT_STORAGE_FULL,MN_MSG_EVT_STORAGE_EXCEED*/
    MN_MSG_READ_EVT_INFO_STRU           stReadInfo;                             /*event report:MN_MSG_EVT_READ ,MN_MSG_EVT_READ_STARPT,MN_MSG_EVT_MATCHMO_STARPT_INFO*/
    MN_MSG_LIST_EVT_INFO_STRU           stListInfo;                             /*event report:MN_MSG_EVT_LIST*/
    MN_MSG_WRITE_EVT_INFO_STRU          stWriteInfo;                            /*event report:MN_MSG_EVT_WRITE*/
    MN_MSG_DELETE_EVT_INFO_STRU         stDeleteInfo;                           /*event report:MN_MSG_EVT_DELETE,MN_MSG_EVT_DELETE_SR,MN_MSG_EVT_DELETE_SRV_PARAM,MN_MSG_EVT_DELETE_CBS*/
    MN_MSG_DELETE_TEST_EVT_INFO_STRU    stDeleteTestInfo;                       /*event report:MN_MSG_EVT_DELETE_TEST */
    MN_MSG_MODIFY_STATUS_EVT_INFO_STRU  stModifyInfo;                           /*event report:MN_MSG_MODIFY_STATUS*/
    MN_MSG_SRV_PARM_EVT_INFO_STRU       stSrvParmInfo;                          /*event report:MN_MSG_EVT_WRITE_SRV_PARM,MN_MSG_EVT_READ_SRV_PARM*/
    MN_MSG_SRV_PARM_CHANGED_EVT_INFO_STRU stSrvParmChangeInfo;                  /*event report:MN_MSG_EVT_SRV_PARM_CHANGED*/
    MN_MSG_MEMSTATUS_EVT_INFO_STRU      stMemStatusInfo;                        /*event report:MN_MSG_EVT_SETMEMSTATUS,MN_MSG_EVT_MEMSTATUS_CHANGED*/
    MN_MSG_RCVMSG_PATH_EVT_INFO_STRU    stRcvMsgPathInfo;                       /*event report:MN_MSG_EVT_SET_RCVMSG_PATH,MN_MSG_EVT_GET_RCVMSG_PATH,MN_MSG_EVT_RCVMSG_PATH_CHANGED*/
    MN_MSG_INIT_EVT_INFO_STRU           stInitResultInfo;                       /*event report:MN_MSG_EVT_INIT_RESULT*/
    MN_MSG_INIT_SMSP_EVT_INFO_STRU      stInitSmspResultInfo;
    MN_MSG_LINK_CTRL_EVT_INFO_STRU      stLinkCtrlInfo;                         /*event report:MN_MSG_EVT_SET_LINK_CTRL_PARAM,MN_MSG_EVT_GET_LINK_CTRL_PARAM*/
    /* Added by f62575 for AT Project，2011-10-03,  Begin*/
    MN_MSG_RESULT_EVT_INFO_STRU         stResult;                               /*event report:MN_MSG_EVT_GET_LINK_CTRL_PARAM, etc */
    /* Added by f62575 for AT Project，2011-10-03,  End*/
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    MN_MSG_CB_DELIVER_EVT_INFO_STRU     stCbsDeliverInfo;                       /*event report:MN_MSG_EVT_DELIVER_CBS*/
    MN_MSG_CBMIDS_CHANGE_EVT_INFO_STRU  stCbsChangeInfo;
    MN_MSG_CBMIDS_GET_EVT_INFO_STRU     stCbsCbMids;
#if (FEATURE_ON == FEATURE_ETWS)
    TAF_CBA_ETWS_PRIM_NTF_EVT_INFO_STRU stEtwsPrimNtf;                            /* ETWS主通知信息上报 */
#endif

#endif
    }u;
}MN_MSG_EVENT_INFO_STRU;

typedef struct
{
    MN_MSG_LINK_CTRL_U8 enRelayLinkCtrl;
}MN_MSG_SET_LINK_CTRL_STRU;

/* Added by f62575 for AT Project，2011-10-03,  Begin*/
/*****************************************************************************
 枚举名    : MN_MSG_STUB_MSG_STRU
 结构说明  : 短信相关桩消息参数结构
             enStubType 桩类型
             ulValue    设置类桩消息有效，指定类型的桩需要配置C核参数的值，
                <enStubType>           <Value>的含义
                    0             efsms文件不可用； 0: efsms文件可用；1: efsms文件不可用；
                    1             efsms文件容量为1；0:不启用桩，其他 : EFSMS的容量为<Value>指定容量；
                    2             efsmss溢出标志清除操作；0: efsmss文件溢出标志有效；1: 强制清除efsmss文件溢出标志；
                    3             efsmsp文件获取无响应；0: efsmsp文件操作正常；1: efsmsp文件操作无响应；
                    4             efsms文件获取无响应；0: efsms文件操作正常；1: efsms文件操作无响应；
                    5             触发STK短信发送，STK短信内容需要压缩编码
                    6             触发STK短信发送，STK短信长度超过标准短信长度，需要分段发送；
                    7             去使能短信重发功能； 0: 短信重发功能正常；1: 不启用短信重发功能
                    8             设置CLASS0类短信的定制配置；
                    9             设置PP DOWNLOAD操作失败，并指定失败原因值
                   10             PS域短信连发开关 0: 默认关闭PS域短信连发功能；1: 启动PS域短信连发功能；
                   11             触发短信自动回复功能 0: 默认关闭短信自动回复桩过程；1: 启动短信自动回复桩过程；
*****************************************************************************/
typedef struct
{
    MN_MSG_STUB_TYPE_ENUM_U32           enStubType;
    VOS_UINT32                          ulValue;
}MN_MSG_STUB_MSG_STRU;
/* Added by f62575 for AT Project，2011-10-03,  End*/

enum MN_MSG_CLIENT_TYPE_ENUM
{
    MN_MSG_CLIENT_NORMAL          =    0,                                                     /*not saved by PS*/
    MN_MSG_CLIENT_STK,
    MN_MSG_CLIENT_BUTT
} ;
typedef VOS_UINT8  MN_MSG_CLIENT_TYPE_ENUM_UINT8;

/*Parm of MN_MSG_Send*/
typedef struct
{
    MN_MSG_SEND_DOMAIN_ENUM_U8          enDomain;
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore;
    MN_MSG_CLIENT_TYPE_ENUM_UINT8       enClientType;
    VOS_UINT8                           aucReserve1[1];
    /* Addedd by y00245242 for VoLTE_PhaseI  项目, 2013-7-9, begin */
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType;
    /* Addedd by y00245242 for VoLTE_PhaseI  项目, 2013-7-9, end */
    MN_MSG_MSG_INFO_STRU                stMsgInfo;
}MN_MSG_SEND_PARM_STRU;

/*Parm of MN_MSG_SendFromMem*/
typedef struct
{
    MN_MSG_SEND_DOMAIN_ENUM_U8          enDomain;
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore;
    VOS_UINT8                           aucReserve1[2];
    /* Addedd by y00245242 for VoLTE_PhaseI  项目, 2013-7-9, begin */
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType;
    /* Addedd by y00245242 for VoLTE_PhaseI  项目, 2013-7-9, end */
    VOS_UINT32                          ulIndex;                                /*sms memory index*/
    MN_MSG_BCD_ADDR_STRU                stDestAddr;                             /*destination addr of sms*/
}MN_MSG_SEND_FROMMEM_PARM_STRU;

/*Para of Send MN_MSG_SendAck*/
typedef struct
{
    VOS_BOOL                            bRpAck;                                 /*is Rp-Ack or Rp-Error*/
    MN_MSG_RP_CAUSE_ENUM_U8             enRpCause;                              /* used when bRpAck==FALSE */
    VOS_UINT8                           aucReserve1[3];
    MN_MSG_RAW_TS_DATA_STRU             stTsRawData;
} MN_MSG_SEND_ACK_PARM_STRU;

/*Para of MN_MSG_Write*/
typedef struct
{
    VOS_UINT32                          ulIndex;
    MN_MSG_WRITE_MODE_ENUM_U8           enWriteMode;
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore;
    MN_MSG_STATUS_TYPE_ENUM_U8          enStatus;
    VOS_UINT8                           aucReserve1[1];
    MN_MSG_MSG_INFO_STRU                stMsgInfo;
}MN_MSG_WRITE_PARM_STRU;

/*Para of MN_MSG_Read,MN_MSG_ReadCbm*/
typedef struct
{
    VOS_UINT32                          ulIndex;                                /*sms memory index*/
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore;                             /*momory store:nvim or usim*/
    VOS_UINT8                           aucReserve1[3];
    VOS_BOOL                            bChangeFlag;                            /*change status or not change status after read or list*/
}MN_MSG_READ_PARM_STRU;

/*Para of MN_MSG_List,MN_MSG_ListCbm*/


/*Para of MN_MSG_Delete,MN_MSG_DeleteStaRpt,MN_MSG_DeleteSrvParm,MN_MSG_DeleteCbm*/
typedef struct
{
     VOS_UINT32                         ulIndex;                                /*sms momory index*/
     MN_MSG_MEM_STORE_ENUM_U8           enMemStore;                             /*memory store :NVIM or USIM*/
     MN_MSG_DELETE_TYPE_ENUM_U8         enDeleteType;                           /*sms delete type*/
    VOS_UINT8                           aucReserve1[2];
} MN_MSG_DELETE_PARAM_STRU;

/*Para of MN_MSG_ReadStaRpt,MN_MSG_ReadSrvParm*/
typedef struct
{
    VOS_UINT32                          ulIndex;
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore;
    VOS_UINT8                           aucReserve1[3];
}MN_MSG_READ_COMM_PARAM_STRU;

/*Para of MN_MSG_WriteSrvParm*/
typedef struct
{
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore;
    MN_MSG_WRITE_MODE_ENUM_U8           enWriteMode;
    VOS_UINT8                           aucReserve1[2];
    VOS_UINT32                          ulIndex;
    MN_MSG_SRV_PARAM_STRU               stSrvParm;
}MN_MSG_WRITE_SRV_PARAM_STRU;

/*Para of MN_MSG_ModifyStatus*/
typedef struct
{
    VOS_UINT32                          ulIndex;                                /*sms memory index*/
    MN_MSG_STATUS_TYPE_ENUM_U8          enStatus;                               /*sms status*/
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore;                             /*sms memory store:nvim or usim*/
    VOS_UINT8                           aucReserve1[2];
} MN_MSG_MODIFY_STATUS_PARM_STRU;

/*Para of MN_MSG_GetRcvMsgPath*/
typedef struct
{
    VOS_UINT32                          ulReserved;
}MN_MSG_GET_RCVMSG_PATH_PARM_STRU;

/*Para of af_SmsGetStorageStatus*/
typedef struct
{
    MN_MSG_MEM_STORE_ENUM_U8            enMem1Store;
    MN_MSG_MEM_STORE_ENUM_U8            enMem2Store;
    VOS_UINT16                          usReserved;
}MN_MSG_GET_STORAGE_STATUS_PARM_STRU;

/*Parm of MN_MSG_GetStaRptFromMoMsg,MN_MSG_GetMoMsgFromStaRpt*/
typedef struct
{
    VOS_UINT32                          ulIndex;
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore;
    VOS_UINT8                           aucReserve1[3];
}MN_MSG_STARPT_MOMSG_PARM_STRU;

/*Parm of MN_MSG_SetMemStatus*/
typedef struct
{
    MN_MSG_MEM_FLAG_ENUM_U8             enMemFlag ;
    VOS_UINT8                           aucReserve1[3];
}MN_MSG_SET_MEMSTATUS_PARM_STRU;

typedef struct
{
    MN_MSG_ADDR_NUM_TYPE_T              addrType;                                    /*bcd number type*/
    VOS_UINT8                           aucAsciiNum[MN_MAX_ASCII_ADDRESS_NUM + 1];   /*array  of ASCII Num*/
    VOS_UINT8                           aucReserve1[2];
}MN_MSG_APP_ADDR_STRU;

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    MN_MSG_EVENT_ENUM_U32               enMsgID;    /*_H2ASN_MsgChoice_Export NAS_RRC_MSG_TYPE_ENUM_UINT32*/
                                                    /* 为了兼容NAS的消息头定义，所以转换ASN.1使用NAS_RRC_MSG_TYPE_ENUM_UINT32 */

    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_RRC_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}MSG_APP_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MSG_APP_MSG_DATA                    stMsgData;
}MsgAppInterface_MSG;


/*****************************************************************************
  4 宏定义
*****************************************************************************/

/*****************************************************************************
  5 全局变量声明
*****************************************************************************/

/*****************************************************************************
  6 接口函数声明
*****************************************************************************/
/*Set command controls the continuity of SMS relay protocol link. */
VOS_UINT32   MN_MSG_SetLinkCtrl(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_SET_LINK_CTRL_STRU     *pstSetParam
);

/*Get command controls the continuity of SMS relay protocol link. */
VOS_UINT32   MN_MSG_GetLinkCtrl(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
);

/*Send Sm From Client directly*/
VOS_UINT32   MN_MSG_Send(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_SEND_PARM_STRU         *pstSendDirectParm
);

/*Send Sm From Mem*/
VOS_UINT32   MN_MSG_SendFromMem(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_SEND_FROMMEM_PARM_STRU *pstSendFromMemParm
);

/*Send Rp-Ack,Rp-Error*/
VOS_UINT32   MN_MSG_SendAck(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_SEND_ACK_PARM_STRU     *pstAckParm
);

/*Write Sm into USIM Or NVIM*/
VOS_UINT32   MN_MSG_Write(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_WRITE_PARM_STRU        *pstWriteParm
);

/*Read Sm*/
VOS_UINT32   MN_MSG_Read(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_PARM_STRU         *pstReadParm
);

/*List Sm*/
VOS_UINT32   MN_MSG_List(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_LIST_PARM_STRU         *pstListParm
);

/*Delete Sm*/
VOS_UINT32   MN_MSG_Delete(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_PARAM_STRU       *pstDeleteParm
);

/*Delete sm test command api*/
VOS_UINT32   MN_MSG_Delete_Test(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_LIST_PARM_STRU         *pstListPara
);

/*Modify Sm Status*/
VOS_UINT32   MN_MSG_ModifyStatus(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    const MN_MSG_MODIFY_STATUS_PARM_STRU *pstModifyParm
);

/*Read Status Report*/
VOS_UINT32   MN_MSG_ReadStaRpt(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_COMM_PARAM_STRU    *pstReadParm
);

/*Delete Status Report*/
VOS_UINT32   MN_MSG_DeleteStaRpt(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_PARAM_STRU       *pstDeleteParm
);

/*Write Sm ervice Parameter*/
VOS_UINT32   MN_MSG_WriteSrvParam(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_WRITE_SRV_PARAM_STRU  *pstSrvParam
);

/*Read Sm Service Parameter*/
VOS_UINT32   MN_MSG_ReadSrvParam(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_COMM_PARAM_STRU    *pstReadParm
);

/*Delete Sm Service Parameter*/
VOS_UINT32   MN_MSG_DeleteSrvParam(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_PARAM_STRU       *pstDeleteParm
);

/*Set Rcv Path of Sm */
VOS_UINT32 MN_MSG_SetRcvMsgPath(
    MN_CLIENT_ID_T                         clientId,
    MN_OPERATION_ID_T                      opId,
    const MN_MSG_SET_RCVMSG_PATH_PARM_STRU *pstRcvPathParm
);

/*Get Rcv Path of Sm */
VOS_UINT32   MN_MSG_GetRcvMsgPath(
    MN_CLIENT_ID_T                         clientId,
    MN_OPERATION_ID_T                      opId,
    const MN_MSG_GET_RCVMSG_PATH_PARM_STRU *pstRcvPathParm
);

/*Get Storage Status of Sm */
VOS_UINT32  MN_MSG_GetStorageStatus(
    MN_CLIENT_ID_T                            clientId,
    MN_OPERATION_ID_T                         opId,
    const MN_MSG_GET_STORAGE_STATUS_PARM_STRU *pstMemParm
);

/*Get Status Report From Mo Sm*/
VOS_UINT32   MN_MSG_GetStaRptIndex(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_STARPT_MOMSG_PARM_STRU *pstMoMsgParm
);

/*Get Sm From Mo Status Report*/
VOS_UINT32   MN_MSG_GetMoMsgIndex(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_STARPT_MOMSG_PARM_STRU *pstStaRptParm
);

/*Set App Mem Status*/
VOS_UINT32 MN_MSG_SetMemStatus(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    const MN_MSG_SET_MEMSTATUS_PARM_STRU *pMemStatusParm
);

/*Encode Sm*/
VOS_UINT32  MN_MSG_Encode(
     const MN_MSG_TS_DATA_INFO_STRU     *pstTsDataInfo,
     MN_MSG_RAW_TS_DATA_STRU            *pstRawData
);

/*Decode Sm*/
VOS_UINT32  MN_MSG_Decode(
     const MN_MSG_RAW_TS_DATA_STRU      *pstRawData ,
     MN_MSG_TS_DATA_INFO_STRU           *pstTsDataInfo
);

/*Segment long Sm */
VOS_UINT32   MN_MSG_Segment(
    const MN_MSG_SUBMIT_LONG_STRU       *pstLongSubmit,
    VOS_UINT8                           *pucNum,
    MN_MSG_RAW_TS_DATA_STRU             *pstRawData
);

/*Concatenate long Sm */
VOS_UINT32   MN_MSG_Concatenate(
    VOS_UINT8                           ucNum,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData ,
    MN_MSG_DELIVER_LONG_STRU            *pstLongDeliver
);

/*Encode Sm from default parameter*/
VOS_UINT32   MN_MSG_BuildDefSubmitMsg(
    const MN_MSG_SUBMIT_DEF_PARM_STRU   *pstDefSubmitParm,
    const MN_MSG_SRV_PARAM_STRU         *pstSrvParam,
    MN_MSG_RAW_TS_DATA_STRU             *pstRawData
);

/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */



/*Decode Data Coding Scheme*/
VOS_UINT32  MN_MSG_DecodeDcs(
    VOS_UINT8                           ucDcsData,
    MN_MSG_DCS_CODE_STRU                *pstDcs
);

/*Encode Data Coding Scheme*/
VOS_UINT32  MN_MSG_EncodeDcs(
    const MN_MSG_DCS_CODE_STRU          *pstDcs,
    VOS_UINT8                           *pucDcsData
);

/*Decode Relative Time*/
VOS_UINT32  MN_MSG_DecodeRelatTime(
    VOS_UINT8                           ucRelatTimeData,
    MN_MSG_TIMESTAMP_STRU               *pstRelatTime
);

/*Encode Relative Time*/
VOS_UINT32  MN_MSG_EncodeRelatTime(
    const MN_MSG_TIMESTAMP_STRU         *pstRelatTime,
    VOS_UINT8                           *pucRelatTimeData
);

/*根据TP或RP层地址解析得到ASCII码表示号码的数据结构*/
VOS_UINT32 MN_MSG_DecodeAddress(
    const VOS_UINT8                     *pucAddr,
    VOS_BOOL                            bRpAddr,
    MN_MSG_ASCII_ADDR_STRU              *pstAsciiAddr,
    VOS_UINT32                          *pulLen
);

/*根据ASCII码表示号码的数据结构编码得到TP或RP层地址*/
VOS_UINT32 MN_MSG_EncodeAddress(
    const MN_MSG_ASCII_ADDR_STRU        *pstAsciiAddr,
    VOS_BOOL                            bRpAddr,
    VOS_UINT8                           *pucAddr,
    VOS_UINT32                          *pulLen
);

/*根据VP和VPF解析得到有效期数据结构*/
VOS_UINT32 MN_MSG_DecodeValidPeriod(
    MN_MSG_VALID_PERIOD_ENUM_U8         enVpf,
    const VOS_UINT8                     *pucValidPeriod,
    MN_MSG_VALID_PERIOD_STRU            *pstValidPeriod,
    VOS_UINT32                          *pulLen
);

/*将MN_MSG_BCD_ADDR_STRU类型地址转换成MN_MSG_ASCII_ADDR_STRU类型地址*/
VOS_UINT32 MN_MSG_BcdAddrToAscii(
    MN_MSG_BCD_ADDR_STRU                *pstBcdAddr,
    MN_MSG_ASCII_ADDR_STRU              *pstAsciiAddr
);

/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */

/***********************************************************************
函 数 名  : MN_MSG_GetSmStatus
功能描述  : 获取存在USIM或NVIM中的短信状态
输入参数  : enMemStore:需要获取短信状态的存储位置,USIM或NVIM中
            ulIndex:需要获取短信状态的索引号
输出参数  : penStatus:索引为ulIndex的短信状态
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2009年7月14日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_GetSmStatus(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    MN_MSG_STATUS_TYPE_ENUM_U8          *penStatus
);

/***********************************************************************
函 数 名  : MN_MSG_GetTotalSmCapacity
功能描述  : 获取最大能存在USIM或NVIM中短信的容量
输入参数  : enMemStore:需要获取短信容量的存储位置,USIM或NVIM中
输出参数  : NONE
返 回 值  : 当前存储器的短信容量
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_GetTotalSmCapacity(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);

/***********************************************************************
函 数 名  : MN_MSG_MoRetryFlag
功能描述  : 获取短信重传功能标记
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_TRUE 当前启用了短信重传功能，VOS_FALSE 当前没有启用重传功能；
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2009年09月01日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_MoRetryFlag(
    VOS_VOID
);

/*****************************************************************************
 函 数 名  : MN_MSG_GetSmsServicePara
 功能描述  : 获取短信业务参数
 输入参数  : 无
 输出参数  : MN_MSG_CONFIG_PARM_STRU  *pstMsgCfgParm  短信业务参数
             MN_MSG_ME_STORAGE_STATUS_UINT8     *penMeStorageEnable ME使能状态
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月11日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_MSG_GetSmsServicePara(
    MN_MSG_CONFIG_PARM_STRU             *pstMsgCfgParm,
    MN_MSG_ME_STORAGE_STATUS_ENUM_UINT8 *penMeStorageEnable
);

/* Added by f62575 for AT Project，2011-10-03,  Begin*/
/*****************************************************************************
 函 数 名  : MN_MSG_ReqStub
 功能描述  : 请求C核执行短信桩请求
 输入参数  : MN_CLIENT_ID_T                 clientId 发起该请求的Client的ID
             MN_OPERATION_ID_T              opId     Operation ID, 标识本次操作
             const MN_MSG_STUB_MSG_STRU     *pstStubParam 桩操作参数
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月3日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_MSG_ReqStub(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_STUB_MSG_STRU         *pstStubParam
);

/*****************************************************************************
 函 数 名  : MN_MSG_ChkDate
 功能描述  : 检查日期是否在有效范围内
 输入参数  : pstTimeStamp   - 绝对有效时间数据结构,其中的年月日都是用BCD码顺序表示的;
 输出参数  : pucInvalidType - 无效日期类型集合;
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月1日
    作    者   : fuyingjun
    修改内容   : 新生成函数
  2.日    期   : 2010年04月10日
    作    者   : f62575
    修改内容   : 问题单号AT2D18035
                 写PDU短信到SIM卡,BALONG对TP-SCTS的检查与标杆不一致；
*****************************************************************************/
VOS_UINT32 MN_MSG_ChkDate(
    const MN_MSG_TIMESTAMP_STRU         *pstTimeStamp,
    MN_MSG_DATE_INVALID_TYPE_ENUM_UINT8 *pucInvalidType
);

/* Added by f62575 for AT Project，2011-10-03,  End*/

/*****************************************************************************
 函 数 名  : MN_MSG_GetMoSmsCtrlFlag
 功能描述  : 获取MO SMS CONTROL特性的激活标志
 输入参数  : 无
 输出参数  : VOS_BOOL  *pbMoSmsCtrlFlag  MO SMS CONTROL特性的激活标志
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月22日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_MSG_GetMoSmsCtrlFlag(
    VOS_UINT8                           *pucMoSmsCtrlFlag
);

/*****************************************************************************
 函 数 名  : MN_MGS_UpdateSmsCapability
 功能描述  : 更新SMS存储介质的容量
 输入参数  : MN_MSG_MEM_STORE_ENUM_U8            enSmMemStore 存储介质类型
             VOS_UINT32                          ulNum        指定存储介质的容量
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月22日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数 DTS2011062201273 MO SMS CONTROL
*****************************************************************************/
VOS_VOID MN_MGS_UpdateSmsCapability(
    MN_MSG_MEM_STORE_ENUM_U8            enSmMemStore,
    VOS_UINT32                          ulNum
);
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

/*Get All Cb Mids*/
VOS_UINT32 MN_MSG_GetAllCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
);

/*Add Cb Mids*/
VOS_UINT32 MN_MSG_AddCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const TAF_CBA_CBMI_RANGE_LIST_STRU *pstCbmirList
);

/*Delete Cb Mids*/
VOS_UINT32 MN_MSG_DelCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const TAF_CBA_CBMI_RANGE_LIST_STRU *pstCbmirList
);


/*Decode Cb Msg Page*/
VOS_UINT32  MN_MSG_DecodeCbmPage(
    const MN_MSG_CBRAW_TS_DATA_STRU     *pstCbRawInfo,
    MN_MSG_CBPAGE_STRU                  *pstCbmPageInfo
);


VOS_UINT32 MN_MSG_EmptyCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
);

#endif

VOS_VOID MN_MSG_GetMsgMti(
    VOS_UINT8                           ucFo,
    VOS_UINT8                          *pucMti
);

VOS_UINT32 MN_MSG_GetSubmitInfoForStk(
    MN_MSG_TPDU_STRU                   *pstTpdu,
    VOS_UINT8                          *pucUserDataLen,
    VOS_UINT8                          *pucUdhl,
    MN_MSG_MSG_CODING_ENUM_U8          *penMsgCoding,
    VOS_UINT32                         *pulDcsOffset
);


VOS_UINT32 MSG_SendAppReq(
    MN_MSG_MSGTYPE_ENUM_U16             enMsgType,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const VOS_VOID                      *pSendParm
);

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

#endif /* __MNMSGAPI_H__ */

