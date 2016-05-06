

/************************************************************************
Copyright   : 2005-2008, Huawei Tech. Co., Ltd.
File name   : SiAppSTK.h
Author      : H59254
Version     : V200R001
Date        : 2008-10-13
Description : SIM卡事件的头文件
History     :
History     :
1.日    期  : 2008年10月13日
  作    者  : H59254
  修改内容  : Create
************************************************************************/
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef __SI_APP_STK_H__
#define __SI_APP_STK_H__

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#include "TafTypeDef.h"
#include "sitypedef.h"
#include "vos.h"
#include "Taf_MmiStrParse.h"
#include "NasStkInterface.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define SI_STK_DATA_MAX_LEN             (256)

/* 定义地址最大长度 */
#define SI_STK_ADDR_MAX_LEN             (42)

#define STK_PRINT_MAX_LEN               (1024)

#define ITEMNUMMAX                      (50)

#define SI_STK_MENU_EXIST               (1)
#define SI_STK_MENU_NOTEXIST            (0)


#define SI_AT_RESULT_END_SESSION        (0x0)
#define SI_AT_RESULT_PERFORM_SUCC       (0x1)
#define SI_AT_RESULT_HELP_REQUIRED      (0x2)
#define SI_AT_RESULT_BACKWARD_MOVE      (0x3)
#define SI_AT_RESULT_ME_NOT_SUPPORT     (0x4)
#define SI_AT_RESULT_ME_BROWSER_BUSY    (0x5)
#define SI_AT_RESULT_ME_SS_BUSY         (0x6)

#define SI_DEVICE_KEYPAD                (0x01)
#define SI_DEVICE_DISPLAY               (0x02)
#define SI_DEVICE_EARPIECE              (0x03)
#define SI_DEVICE_UICC                  (0x81)
#define SI_DEVICE_TERMINAL              (0x82)
#define SI_DEVICE_NETWORK               (0x83)

#define USAT_CMDSETSTGI                 (0x01)
#define USAT_CMDQRYSTGI                 (0x02)

#define STK_AS_NMR_INFO_REQ             (0x08)
#define STK_AS_NMR_INFO_CNF             (0x11)

/* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, begin */
#define STK_AS_TA_INFO_REQ              (0x09)
#define STK_AS_TA_INFO_CNF              (0x12)
/* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, end */

#define SI_STK_DEFAULT_TA_VALUE         (0)
#define SI_STK_MAX_TA_VALUE             (0X3F)
#define SI_STK_INVALID_TA_VALUE         (0xFF)

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
enum SI_STK_MBBCMDTYPE_ENUM
{
    SI_AT_CMD_SETUP_MENU                    = 0,
    SI_AT_CMD_DISPLAY_TEXT                  = 1,
    SI_AT_CMD_GET_INKEY                     = 2,
    SI_AT_CMD_GET_INPUT                     = 3,
    SI_AT_CMD_SETUP_CALL                    = 4,
    SI_AT_CMD_PLAY_TONE                     = 5,
    SI_AT_CMD_SELECT_ITEM                   = 6,
    SI_AT_CMD_REFRESH                       = 7,
    SI_AT_CMD_SEND_SS                       = 8,
    SI_AT_CMD_SEND_SMS                      = 9,
    SI_AT_CMD_SEND_USSD                     = 10,
    SI_AT_CMD_LAUNCH_BROWSER                = 11,
    SI_AT_CMD_SETUP_IDLE_MODE_TEXT          = 12,
    SI_AT_CMD_LANGUAGENOTIFICATION          = 20,   /*暂时定为20，待APP开发该SAT功能后确认接口*/
    SI_AT_CMD_SETFRAMES                     = 21,   /*暂时定为21，待APP开发该SAT功能后确认接口*/
    SI_AT_CMD_GETFRAMESSTATUS               = 22,   /*暂时定为22，待APP开发该SAT功能后确认接口*/
    SI_AT_CMD_END_SESSION                   = 99,
    SI_STK_MBBCMDTYPE_BUTT
};

enum SI_STK_DEVICE_ENUM
{
    SI_STK_DEV_KEYPAD                       = 0x01,
    SI_STK_DEV_DISPALY                      = 0x02,
    SI_STK_DEV_EARPRIICE                    = 0x03,
    SI_STK_DEV_UICC                         = 0x81,
    SI_STK_DEV_TERMINAL                     = 0x82,
    SI_STK_DEV_NETWORK                      = 0x83,
    SI_STK_DEV_BUTT
};

enum
{
    SI_STK_ERROR_EVENT                      = 0,    /*处理错误统一回复*/
    SI_STK_CMD_IND_EVENT                    = 1,    /*主动命令广播上报*/
    SI_STK_TERMINAL_RSP_EVENT               = 2,    /*主动命令执行结果下发回复*/
    SI_STK_ENVELPOE_RSP_EVENT               = 3,    /*主菜单选择回复*/
    SI_STK_PROFILESET_RSP_EVENT             = 4,    /*Terminal Profile设置下发，保留未用*/
    SI_STK_GET_CMD_RSP_EVENT                = 5,    /*获取当前主动命令回复*/
    SI_STK_CMD_QUERY_RSP_EVENT              = 6,    /*查询当前主动命令回复*/
    SI_STK_CMD_TIMEOUT_IND_EVENT            = 7,    /*主动命令执行超时回复*/
    SI_STK_CMD_END_EVENT                    = 8,    /*后续无主动命令执行上报*/
    SI_STK_CMD_IMSICHG_EVENT                = 9,    /*沃达丰定制流程*/
    SI_STK_CC_RESULT_IND_EVENT              = 10,   /*Call Control结果上报*/
    SI_STK_SMSCTRL_RESULT_IND_EVENT         = 11,   /*Sms Control结果上报*/
#if (FEATURE_VSIM == FEATURE_ON)
    SI_STK_SMS_PP_DL_DATA_IND_EVENT         = 12,   /*SMS PP DOWNLOAD数据上报*/
#endif
    SI_STK_CALLBACK_BUTT
};
typedef VOS_UINT8 STK_CALLBACK_EVENT;

enum
{
    SI_STK_EVENT_MT_CALL                    = 0x00,
    SI_STK_EVENT_CALL_CONNECTED             = 0x01,
    SI_STK_EVENT_CALL_DISCONNECTED          = 0x02,
    SI_STK_EVENT_LOCATION_STATUS            = 0x03,
    SI_STK_EVENT_USER_ACTIVITY              = 0x04,
    SI_STK_EVENT_IDLE_SCREEN_AVAILABLE      = 0x05,
    SI_STK_EVENT_CARDREADER_STATUS          = 0x06,
    SI_STK_EVENT_LANGUAGE_SELECTION         = 0x07,
    SI_STK_EVENT_BROWSER_TERMINATION        = 0x08,
    SI_STK_EVENT_DATA_AVAILABLE             = 0x09,
    SI_STK_EVENT_CHANNEL_STATUS             = 0x0A,
    SI_STK_EVENT_ACCESS_TECHN_CHANGE        = 0x0B,
    SI_STK_EVENT_DISPLAY_PARA_CHANGED       = 0x0C,
    SI_STK_EVENT_LOCAL_CONNECTION           = 0x0D,
    SI_STK_EVENT_NET_SEARCHMODE_CHANGE      = 0x0E,
    SI_STK_EVENT_BROWSING_STATUS            = 0x0F,
    SI_STK_EVENT_FRAMES_INFO_CHANGE         = 0x10,
    SI_STK_EVENT_IWLAN_ACCESS_STATUS        = 0x11,
    SI_STK_EVENT_NETWORK_REJECTION          = 0x12,
    SI_STK_EVENT_CSG_CELL_SELECTION         = 0x15,
    SI_STK_EVENT_IMS_REGISTRATION           = 0x17,
    SI_STK_EVENT_INCOMING_IMS_DATA          = 0x18,
    SI_STK_EVENT_BUTT
};
typedef VOS_UINT32 SI_STK_EVENT_TYPE;

enum SI_STK_ENVELOPE_TYPE
{
    SI_STK_PROCMD                           = 0xD0,
    SI_STK_ENVELOPE_PPDOWN                  = 0xD1,
    SI_STK_ENVELOPE_CBDOWN                  = 0xD2,
    SI_STK_ENVELOPE_MENUSEL                 = 0xD3,
    SI_STK_ENVELOPE_CALLCRTL                = 0xD4,
    SI_STK_ENVELOPE_SMSCRTL                 = 0xD5,
    SI_STK_ENVELOPE_EVENTDOWN               = 0xD6,
    SI_STK_ENVELOPE_TIMEEXP                 = 0xD7,
    SI_STK_ENVELOPE_RFU                     = 0xD8,
    SI_STK_ENVELOPE_USSDDOWN                = 0xD9,
    SI_STK_ENVELOPE_MMSTRANSTATUS           = 0xDA,
    SI_STK_ENVELOPE_MMSNOTIFY               = 0xDB
};
typedef VOS_UINT32 SI_STK_ENVELOPE_TYPE_UINT32;

enum
{
    SI_STK_NOCMDDATA                        = 0x00,
    SI_STK_REFRESH                          = 0x01,
    SI_STK_MORETIME                         = 0x02,
    SI_STK_POLLINTERVAL                     = 0x03,
    SI_STK_POLLINGOFF                       = 0x04,
    SI_STK_SETUPEVENTLIST                   = 0x05,
    SI_STK_SETUPCALL                        = 0x10,
    SI_STK_SENDSS                           = 0x11,
    SI_STK_SENDUSSD                         = 0x12,
    SI_STK_SENDSMS                          = 0x13,
    SI_STK_SENDDTMF                         = 0x14,
    SI_STK_LAUNCHBROWSER                    = 0x15,
    SI_STK_PLAYTONE                         = 0x20,
    SI_STK_DISPLAYTET                       = 0x21,
    SI_STK_GETINKEY                         = 0x22,
    SI_STK_GETINPUT                         = 0x23,
    SI_STK_SELECTITEM                       = 0x24,
    SI_STK_SETUPMENU                        = 0x25,
    SI_STK_PROVIDELOCALINFO                 = 0x26,
    SI_STK_TIMERMANAGEMENT                  = 0x27,
    SI_STK_SETUPIDLETEXT                    = 0x28,
    SI_STK_PERFORMCARDAPDU                  = 0x30,
    SI_STK_POWERONCARD                      = 0x31,
    SI_STK_POWEROFFCARD                     = 0x32,
    SI_STK_GETREADERSTATUS                  = 0x33,
    SI_STK_RUNATCOMMAND                     = 0x34,
    SI_STK_LANGUAGENOTIFICATION             = 0x35,
    SI_STK_OPENCHANNEL                      = 0x40,
    SI_STK_CLOSECHANNEL                     = 0x41,
    SI_STK_RECEIVEDATA                      = 0x42,
    SI_STK_SENDDATA                         = 0x43,
    SI_STK_GETCHANNELSTATUS                 = 0x44,
    SI_STK_SERVICESEARCH                    = 0x45,
    SI_STK_GETSERVICEINFO                   = 0x46,
    SI_STK_DECLARESERVICE                   = 0x47,
    SI_STK_SETFRAMES                        = 0x50,
    SI_STK_GETFRAMESSTATUS                  = 0x51,
    SI_STK_CMD_BUTT
};
typedef VOS_UINT32 SI_STK_CMD_TYPE;

enum
{
    COMMAND_PERFORMED_SUCCESSFULLY                                  = 0x00,
    COMMAND_PERFORMED_WITH_PARTIAL_COMPREHENSION                    = 0x01,
    COMMAND_PERFORMED_WITH_MISSING_INFORMATION                      = 0x02,
    REFRESH_PERFORMED_WITH_ADDITIONAL_EFS_READ                      = 0x03,
    COMMAND_PERFORMED_SUCCESS_BUT_ICON_COULD_NOT_BE_DISPLAYED       = 0x04,
    COMMAND_PERFORMED_BUT_MODIFIED_BY_CALL_CONTROL_BY_NAA           = 0x05,
    COMMAND_PERFORMED_SUCCESSFULLY_LIMITED_SERVICE                  = 0x06,
    COMMAND_PERFORMED_WITH_MODIFICATION                             = 0x07,
    REFRESH_PERFORMED_BUT_INDICATED_NAA_WAS_NOT_ACTIVE              = 0x08,
    COMMAND_PERFORMED_SUCCESSFULLY_TONE_NOT_PLAYED                  = 0x09,
    PROACTIVE_UICC_SESSION_TERMINATED_BY_THE_USER                   = 0x10,
    BACKWARD_MOVE_IN_THE_PROACTIVE_UICC_SESSION_REQUESTED_BY_USER   = 0x11,
    NO_RESPONSE_FROM_USER                                           = 0x12,
    HELP_INFORMATION_REQUIRED_BY_USER                               = 0x13,
    SS_TRANS_TERMINATED_BY_USER                                     = 0x14,
    TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND                    = 0x20,
    NETWORK_CURRENTLY_UNABLE_TO_PROCESS_COMMAND                     = 0x21,
    USER_DO_NOT_ACCEPT_THE_PROACTIVE_COMMAND                        = 0x22,
    USER_CLEARED_DOWN_CALL_BEFORE_CONNECTION_OR_NETWORK_RELEASE     = 0x23,
    ACTION_IN_CONTRADICTION_WITH_THE_CURRENT_TIMER_STATE            = 0x24,
    INTERACTION_WITH_CALL_CONTROL_BY_NAA_TEMPORARY_PROBLEM          = 0x25,
    LAUNCH_BROWSER_GENERIC_ERROR_CODE                               = 0x26,
    COMMAND_BEYOND_TERMINALS_CAPABILITIES                           = 0x30,
    COMMAND_TYPE_NOT_UNDERSTOOD_BY_TERMINAL                         = 0x31,
    COMMAND_DATA_NOT_UNDERSTOOD_BY_TERMINAL                         = 0x32,
    COMMAND_NUMBER_NOT_KNOWN_BY_TERMINAL                            = 0x33,
    SS_RETURN_ERROR                                                 = 0x34,
    SMS_RP_ERROR                                                    = 0x35,
    ERROR_REQUIRED_VALUES_ARE_MISSING                               = 0x36,
    USSD_RETURN_ERROR                                               = 0x37,
    MULTIPLECARD_COMMANDS_ERROR                                     = 0x38,
    INTERACTION_WITH_CALL_CONTROL_BY_NAA_PERMANENT_PROBLEM          = 0x39,
    BEARER_INDEPENDENT_PROTOCOL_ERROR                               = 0x3A,
    ACCESS_TECHNOLOGY_UNABLE_TO_PROCESS_COMMAND                     = 0x3B,
    FRAMES_ERROR                                                    = 0x3C,
    SI_STK_RESULT_BUTT
};
typedef VOS_UINT8 SI_STK_RESULT;

/*****************************************************************************
 枚举名    : SI_STK_ADD_INFO_TERMINAL_PROBLEM_ENUM8
 结构说明  : STK回复TERMINAL RESPONSE时RESULT为TERMINAL PROBLEM时附带的ADDITIONAL RESULT值
 1.日    期: 2013年7月12日
   作    者: H59254
   修改内容: 新增
*****************************************************************************/
enum SI_STK_ADD_INFO_TERMINAL_PROBLEM
{
    NO_SPECIFIC_CAUSE_CAN_BE_GIVEN_BY_TERMINAL                      = 0x00,
    SCREEN_IS_BUSY                                                  = 0x01,
    ME_CURRENTLY_BUSY_ON_CALL                                       = 0x02,
    ME_CURRENTLY_BUSY_ON_SS_TRANSACTION                             = 0x03,
    NO_SERVICE                                                      = 0x04,
    ACCESS_CONTROL_CLASS_BAR                                        = 0x05,
    RADIO_RESOURCE_NOT_GRANTED                                      = 0x06,
    NOT_IN_SPEECH_CALL                                              = 0x07,
    ME_CURRENTLY_BUSY_ON_USSD_TRANSACTION                           = 0x08,
    ME_CURRENTLY_BUSY_ON_SEND_DTMF_TRANSACTION                      = 0x09,
    NO_USIM_ACTIVE                                                  = 0x0A,
    ADD_INFO_TERMINAL_PROBLEM_BUTT
};
typedef VOS_UINT8 SI_STK_ADD_INFO_TERMINAL_PROBLEM_ENUM8;

/*****************************************************************************
 枚举名    : SI_STK_ADD_INFO_WITH_CALL_CONTROL_ENUM8
 结构说明  : STK回复TERMINAL RESPONSE时CALL CONTROL时附带的ADDITIONAL RESULT值
 1.日    期: 2013年7月12日
   作    者: H59254
   修改内容: 新增
*****************************************************************************/
enum SI_STK_ADD_INFO_WITH_CALL_CONTROL
{
    NO_SPECIFIC_CAUSE_CAN_BE_GIVEN_BY_CALL_CONTROL                  = 0x00,
    ACTION_NOT_ALLOWED                                              = 0x01,
    TYPE_OF_REQUEST_HAS_CHANGED                                     = 0x02,
    ADD_INFO_WITH_CALL_CONTROL_BUTT
};
typedef VOS_UINT8 SI_STK_ADD_INFO_WITH_CALL_CONTROL_ENUM8;

/*****************************************************************************
 枚举名    : SI_STK_ADD_INFO_WITH_NETWORK_PROBLEM_ENUM8
 结构说明  : STK回复TERMINAL RESPONSE时NETWORK PROBLEM时附带的ADDITIONAL RESULT值
 1.日    期: 2013年7月12日
   作    者: H59254
   修改内容: 新增
*****************************************************************************/
enum SI_STK_ADD_INFO_WITH_NETWORK_PROBLEM
{
    NO_SPECIFIC_CAUSE_CAN_BE_GIVEN_BY_NETWORK                       = 0x00,
    USER_BUSY                                                       = 0x91,
    ADD_INFO_WITH_NETWORK_PROBLEM_BUTT
};
typedef VOS_UINT8 SI_STK_ADD_INFO_WITH_NETWORK_PROBLEM_ENUM8;

/*****************************************************************************
 枚举名    : SI_STK_ADD_INFO_FOR_SS_USSD_SMS_PROBLEM_ENUM8
 结构说明  : STK回复TERMINAL RESPONSE时SEND SMS/SEND SS/SEND USSD ERROR时附带的ADDITIONAL RESULT值
 1.日    期: 2013年7月12日
   作    者: H59254
   修改内容: 新增
*****************************************************************************/
enum SI_STK_ADD_INFO_FOR_SS_USSD_SMS_PROBLEM
{
    NO_SPECIFIC_CAUSE_CAN_BE_GIVEN                                  = 0x00,
    ADD_INFO_FOR_SS_USSD_SMS_PROBLEM_BUTT
};
typedef VOS_UINT8 SI_STK_ADD_INFO_FOR_SS_USSD_SMS_PROBLEM_ENUM8;


enum SI_STK_SETUPCALLCONFIRM_ENUM
{
    SI_STK_SETUPCALL_REJECT         = 0x00,   /* 用户拒绝发起呼叫 */
    SI_STK_SETUPCALL_ALLOW          = 0x01,   /* 用户同意发起呼叫 */
    SI_STK_SETUPCALL_BUTT
};
typedef VOS_UINT32 SI_STK_SETUPCALLCONFIRM_ENUM_UINT32;

enum
{
    SI_STK_TRSEND                                                   = 0,
    SI_STK_ENVELOPESEND                                             = 1,
    SI_STK_SEND_BUTT
};
typedef VOS_UINT32 SI_SEND_DATA_TYPE;

enum
{
    SI_STK_CTRL_ALLOW_NOMODIFY                                      = 0,
    SI_STK_CTRL_NOT_ALLOW                                           = 1,
    SI_STK_CTRL_ALLOW_MODIFY                                        = 2,
    SI_STK_CTRL_BUTT
};
typedef VOS_UINT32   SI_STK_CTRL_RESULT;

/* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, begin */
/* ME 状态 */
enum
{
    SI_STK_ME_STATUS_IDLE                                           = 0,
    SI_STK_ME_STATUS_NOT_IDLE                                       = 1,
    SI_STK_ME_STATUS_BUTT
};
typedef VOS_UINT8   SI_STK_ME_STATUS;

enum SI_STK_CTRL_RESULT_TYPE_ENUM
{
    SI_STK_MO_CALL_CTRL         = 0x00,   /* mo call control类型 */
    SI_STK_SS_CALL_CTRL         = 0x01,   /* ss call control类型 */
    SI_STK_USSD_CALL_CTRL       = 0x02,   /* ussd call control类型 */
    SI_STK_SMS_CTRL             = 0x03,   /* sms call control类型 */
    SI_STK_CTRL_RESULT_BUTT
};
typedef VOS_UINT32 SI_STK_CTRL_RESULT_TYPE_ENUM_UINT32;

enum SI_CC_SPECI_TAG_ENUM
{
    SI_CC_ADDRESS_TAG           = 0x06,
    SI_CC_SS_TAG                = 0x09,
    SI_CC_USSD_TAG              = 0x0A,
    SI_CC_PDP_CONTEXT           = 0x52,
    SI_CC_EPSPDN_TAG            = 0x7C,
    ST_CC_SPECI_TAG_BUTT
};

typedef VOS_UINT8 SI_CC_SPECI_TAG_ENUM_UINT8;

/*****************************************************************************
 枚举名    : SI_STK_UPDATE_ATTACH_TYPE_ENUM_UINT8
 结构说明  : NETWORK REJECTION中UPDATE和ATTACH的值
 1.日    期: 2013年7月12日
   作    者: H59254
   修改内容: 新增
*****************************************************************************/
enum SI_STK_UPDATE_ATTACH_TYPE_ENUM
{
    SI_STK_NETWORK_REJ_TYPE_NORMAL_LOCATION_UPDATING                            = 0x00,
    SI_STK_NETWORK_REJ_TYPE_PERIODIC_UPDATING_LAU                               = 0x01,
    SI_STK_NETWORK_REJ_TYPE_IMSI_ATTACH                                         = 0x02,
    SI_STK_NETWORK_REJ_TYPE_GPRS_ATTACH                                         = 0x03,
    SI_STK_NETWORK_REJ_TYPE_COMBINED_GPRS_IMSI_ATTACH                           = 0x04,
    SI_STK_NETWORK_REJ_TYPE_RA_UPDATING                                         = 0x05,
    SI_STK_NETWORK_REJ_TYPE_COMBINED_RALA_UPDATING                              = 0x06,
    SI_STK_NETWORK_REJ_TYPE_COMBINED_RALA_UPDATING_WITH_IMSI_ATTACH             = 0x07,
    SI_STK_NETWORK_REJ_TYPE_PERIODIC_UPDATING_RAU                               = 0x08,
    SI_STK_NETWORK_REJ_TYPE_EPS_ATTACH                                          = 0x09,
    SI_STK_NETWORK_REJ_TYPE_COMBINED_EPS_IMSI_ATTACH                            = 0x0A,
    SI_STK_NETWORK_REJ_TYPE_TA_UPDATING                                         = 0x0B,
    SI_STK_NETWORK_REJ_TYPE_COMBINED_TA_LA_UPDATING                             = 0x0C,
    SI_STK_NETWORK_REJ_TYPE_COMBINED_TA_LA_UPDATING_WITH_IMSI_ATTACH            = 0x0D,
    SI_STK_NETWORK_REJ_TYPE_PERIODIC_UPDATING_TAU                               = 0x0E,
    SI_STK_NETWORK_REJ_TYPE_BUTT
};
typedef VOS_UINT8 SI_STK_UPDATE_ATTACH_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : SI_STK_SERVICE_STATUS_ENUM_UINT32
 结构说明  : CS域服务状态
 1.日    期: 2013年7月12日
   作    者: H59254
   修改内容: 新增
*****************************************************************************/
enum SI_STK_SERVICE_STATUS_ENUM
{
    SI_STK_NORMAL_SERVICE           = 0x00,
    SI_STK_LIMITED_SERVICE          = 0x01,
    SI_STK_NO_SERVICE               = 0x02,
    SI_STK_SERVICE_BUTT
};

typedef VOS_UINT32 SI_STK_SERVICE_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : SI_STK_ACCESS_TECH_ENUM_UINT8
 结构说明  : 接入技术
 1.日    期: 2013年7月12日
   作    者: H59254
   修改内容: 新增
*****************************************************************************/
enum SI_STK_ACCESS_TECH_ENUM
{
    STK_ACCESS_TECH_GSM             = 0x00,
    STK_ACCESS_TECH_EIA_533         = 0x01,
    STK_ACCESS_TECH_EIA_136         = 0x02,
    STK_ACCESS_TECH_UTRAN           = 0x03,
    STK_ACCESS_TECH_TETRA           = 0x04,
    STK_ACCESS_TECH_EIA_95          = 0x05,
    STK_ACCESS_TECH_CDMA2000        = 0x06,
    STK_ACCESS_TECH_CDMA2000_HPPD   = 0x07,
    STK_ACCESS_TECH_EUTRAN          = 0x08,
    STK_ACCESS_TECH_BUTT            = 0xFF
};

typedef VOS_UINT8 SI_STK_ACCESS_TECH_ENUM_UINT8;

/*****************************************************************************
 枚举名    : SI_STK_SEARCH_MODE_ENUM_UINT8
 结构说明  : 搜网模式
 1.日    期: 2013年7月12日
   作    者: H59254
   修改内容: 新增
*****************************************************************************/
enum SI_STK_SEARCH_MODE_ENUM
{
    SI_STK_SEARCH_MODE_AUTO         = TAF_PH_PLMN_SEL_MODE_AUTO,
    SI_STK_SEARCH_MODE_MANUAL       = TAF_PH_PLMN_SEL_MODE_MANUAL,
    SI_STK_SEARCH_MODE_BUTT
};

/*****************************************************************************
 枚举名    : SI_STK_NMR_TYPE_ENUM_UINT32
 结构说明  : 网络测量类型枚举
*****************************************************************************/
enum SI_STK_NMR_TYPE_ENUM
{
    STK_WAS_QUERYTYPE_INTRA             = 0x1,
    STK_WAS_QUERYTYPE_INTER             = 0x2,
    STK_WAS_QUERYTYPE_INTER_GERAN       = 0x3,
    STK_WAS_QUERYTYPE_INTER_EUTRAN      = 0x4,
    STK_LRRC_QUERYTYPE_INTRA_FREQ       = 0x5,
    STK_LRRC_QUERYTYPE_INTER_FREQ       = 0x6,
    STK_LRRC_QUERYTYPE_INTER_GERAN      = 0x7,
    STK_LRRC_QUERYTYPE_INTER_UTRAN      = 0x8,
    STK_NMR_QUERYTYPE_BUTT
};
typedef VOS_UINT32 SI_STK_NMR_TYPE_ENUM_UINT32;

typedef VOS_UINT8 SI_STK_SEARCH_MODE_ENUM_UINT8;

enum SI_STK_ENVELOPE_SENDERPARA_ENUM
{
    /*0~FFFF是NAS内部使用，用于区分TAF的相关模块*/
    SI_STK_AT_ENVELOPE                  = 0x10000,
    SI_STK_XSMS_ENVELOPE                = 0x20000,
    SI_STK_ENVELOPE_BUTT
};

enum STK_NAS_OP_ENUM
{
    STK_NAS_STEERING_OF_ROAMING_IND     = 0,
    STK_NAS_BUTT
};


/*****************************************************************************
结构名    : SI_STK_MSG_ENUM_UINT32
结构说明  : STK模块处理的消息ID定义
*****************************************************************************/

enum SI_STK_MSG_ENUM
{
    SI_STK_NULL                     = 0x00,
    SI_STK_GETMAINMNUE              = 0x01,     /*获取主菜单请求， AT发送*/
    SI_STK_GETCOMMAND               = 0x02,     /*获取主动命令请求， AT发送*/
    SI_STK_QUERYCOMMAND             = 0x03,     /*查询主动命令请求，AT发送*/
    SI_STK_TRDOWN                   = 0x04,     /*主动命令执行结果下发，AT发送*/
    SI_STK_SIMPLEDOWN               = 0x05,     /*透明数据下发，AT发送*/
    SI_STK_ENVELOPEDOWN             = 0x06,     /*透明信封命令下发，AT发送*/
    SI_STK_PROFILESET               = 0x07,     /*设置Terimal  Profile的内容，AT发送，保留*/
    SI_STK_IMSICHG                  = 0x08,     /*更改IMSI定制*/
    SI_STK_SETUPCALL_CONFIRM        = 0x09,     /*用户确认是否发起呼叫 AT发送*/
    SI_STK_MENUSELECTION            = 0x0A,     /*主菜单选中下发，AT发送*/
    SI_STK_ENVELOPEDWON_REQ         = 0x0B,     /*信封命令下发，目前只有TAF发送的CC MO*/
    SI_STK_VIA_TRDOWN               = 0x0C,
    SI_STK_MSG_BUTT
};
typedef VOS_UINT32 SI_STK_REQMSG_ENUM_UINT32;

enum SI_STK_CNFMSG_ENUM
{
    SI_STK_NULL_CNF                 = 0x00,
    SI_STK_ENVELOPE_CNF             = 0x01,
    SI_STK_TERMIANLRSP_CNF          = 0x02,
    SI_STK_QUERYCOMMAND_CNF         = 0x03,
    SI_STK_SETUPCALL_CONFIRM_CNF    = 0x04,
    SI_STK_IMSICHG_CNF              = 0x05,
    SI_STK_CNFMSG_BUTT
};
typedef VOS_UINT32 SI_STK_CNFMSG_ENUM_UINT32;

/*****************************************************************************
  4 单一数据结构定义
*****************************************************************************/
typedef struct
{
    VOS_UINT32              SatDataLen;
    VOS_UINT8               SatCmdData[256];
}SI_STK_CMDDATA_STRU;

typedef struct
{
    VOS_UINT8               ucCommandNum;
    VOS_UINT8               ucCommandType;
    VOS_UINT8               ucCommandQua;
    VOS_UINT8               ucRsv;
}SI_STK_COMMAND_DETAILS_STRU;

typedef struct
{
    VOS_UINT8               ucSDId;
    VOS_UINT8               ucDDId;
    VOS_UINT8               aucRsv[2];
}SI_STK_DEVICE_IDENTITIES_STRU;

typedef struct
{
    SI_STK_RESULT           Result;
    VOS_UINT8               ucLen;
    VOS_UINT8               aucRsv[2];
    VOS_UINT8               *pucAddiInfo;
}SI_STK_RESULT_STRU;

typedef struct
{
    VOS_UINT8               ucUnit;
    VOS_UINT8               ucInternal;
    VOS_UINT8               aucRsv[2];
}SI_STK_DURATION_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucAlphabet;
}SI_STK_ALPHA_IDENTIFIER_STRU;

typedef struct
{
    VOS_UINT8               ucNumType;
    VOS_UINT8               ucLen;
    VOS_UINT8               aucRsv[2];
    VOS_UINT8               *pucAddr;
}SI_STK_ADDRESS_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8*              pucCCP;
}SI_STK_CAPABILITY_CFG_PARA_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8*              pucSubaddr;
}SI_STK_SUBADDRESS_STRU;

typedef struct
{
    VOS_UINT8               ucNumType;
    VOS_UINT8               ucLen;
    VOS_UINT8               aucRsv[2];
    VOS_UINT8*              pucSSString;
}SI_STK_SS_STRING_STRU;

typedef struct
{
    VOS_UINT8               ucDCScheme;
    VOS_UINT8               ucLen;
    VOS_UINT8               aucRsv[2];
    VOS_UINT8*              pucUSSDString;
}SI_STK_USSD_STRING_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8*              pucTPDU;
}SI_STK_SMS_TPDU_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucCBPage;
}SI_STK_CELL_BROADCAST_PAGE_STRU;

typedef struct
{
    VOS_UINT8               ucDCS;
    VOS_UINT8               ucLen;
    VOS_UINT8               aucRsv[2];
    VOS_UINT8               *pucText;
}SI_STK_TEXT_STRING_STRU;

typedef struct
{
    VOS_UINT8               ucTone;
    VOS_UINT8               ucRsv;
    VOS_UINT8               aucRsv[2];
}SI_STK_TONE_STRU;

typedef struct
{
    VOS_UINT8               ucItemId;
    VOS_UINT8               ucLen;
    VOS_UINT8               aucRsv[2];
    VOS_UINT8               *pucItemText;
}SI_STK_ITEM_STRU;

typedef struct
{
    VOS_UINT8               ucItemId;
    VOS_UINT8               aucRsv[3];
}SI_STK_ITEM_IDENTIFIER_STRU;

typedef struct
{
    VOS_UINT8               ucMinLen;
    VOS_UINT8               ucMaxLen;
    VOS_UINT8               aucRsv[2];
}SI_STK_RESPONSE_LENGTH_STRU;

typedef struct
{
    VOS_UINT8               ucFileNum;
    VOS_UINT8               ucLen;
    VOS_UINT8               aucRsv[2];
    VOS_UINT8*              pucFiles;
}SI_STK_FILE_LIST_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8*              pucATSLI;
}SI_STK_LOCATION_INFO_STRU;

typedef struct
{
    VOS_UINT8               aucIMEI[8];
}SI_STK_IMEI_STRU;

typedef struct
{
    VOS_UINT8               aucNetMeasure[16];
}SI_STK_NET_MEASUREMENT_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8*              pucINAIl;
}SI_STK_ITEMS_NEXTACTION_IND_STRU;

typedef struct
{
    VOS_UINT8               ucNmr;
    VOS_UINT8               ucRsv[3];
}SI_STK_UTRAN_NMR_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8*              pucEventList;
}SI_STK_EVENT_LIST_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8*              pucCause;
}SI_STK_CAUSE_STRU;

typedef struct
{
    VOS_UINT8               ucLocStatus;
    VOS_UINT8               ucRsv[3];
}SI_STK_LOCATION_STATUS_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8*              pucTransaction;
}SI_STK_TRANSACTION_IDENTIFIER_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8*              pucBCList;
}SI_STK_BCCH_CHANNEL_LIST_STRU;

typedef struct
{
    VOS_UINT8               ucQualifier;
    VOS_UINT8               ucId;
    VOS_UINT8               aucRsv[2];
}SI_STK_ICON_IDENTIFIER_STRU;

typedef struct
{
    VOS_UINT8               ucIconlistQua;
    VOS_UINT8               ucLen;
    VOS_UINT8               aucRsv[2];
    VOS_UINT8               *pucIconIdlist;
}SI_STK_ITEM_ICON_ID_LIST_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucATR;
}SI_STK_CARD_ATR_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucCAPDU;
}SI_STK_C_APDU_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucRAPDU;
}SI_STK_R_APDU_STRU;

typedef struct
{
    VOS_UINT8               DataTime[7];
    VOS_UINT8               ucRsv;
}SI_STK_DATE_TIME_ZONE_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucCCRA;
}SI_STK_CALL_CONTROL_REQUESTED_ACTION_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucATCmd;
}SI_STK_AT_COMMAND_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucATRsp;
}SI_STK_AT_RESPONSE_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucDTMFStr;
}SI_STK_DTMF_STRING_STRU;

typedef struct
{
    VOS_UINT8               aucLanguage[2];
    VOS_UINT8               aucRsv[2];
}SI_STK_LANGUAGE_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucTimeAd;
}SI_STK_TIMING_ADVANCE_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucAID;
}SI_STK_AID_STRU;

typedef struct
{
    VOS_UINT8               ucBrowserId;
    VOS_UINT8               aucRsv[3];
}SI_STK_BROWSER_IDENTITY_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucURL;
}SI_STK_URL_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucBearer;
}SI_STK_BEARER_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucProvsionRef;
}SI_STK_PRO_REFERENCE_FILE_STRU;

typedef struct
{
    VOS_UINT8               ucBearerType;
    VOS_UINT8               ucLen;
    VOS_UINT8               aucRsv[2];
    VOS_UINT8               *pucBearer;
}SI_STK_BEARER_DESCRIPTION_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucChannelData;
}SI_STK_CHANNEL_DATA_STRU;

typedef struct
{
    VOS_UINT8               aucBufferSize[2];
    VOS_UINT8               aucRsv[2];
}SI_STK_BUFFER_SIZE_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucNetworkAccessName;
}SI_STK_NETWORK_ACCESS_ANME_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucBufferReader;
}SI_STK_BUFFER_CARD_READER_IDENTIFIER_STRU;

typedef struct
{
    VOS_UINT8               ucTransType;
    VOS_UINT8               ucPortNum[2];
    VOS_UINT8               ucRsv;
}SI_STK_UICC_TERMINAL_TRANLEVEL_STRU;

typedef struct
{
    VOS_UINT8               ucBarerTech;
    VOS_UINT8               ucLen;
    VOS_UINT8               aucRsv[2];
    VOS_UINT8               *pucDeviceFilter;
}SI_STK_DEVICE_FILTER_STRU;

typedef struct
{
    VOS_UINT8               ucLocBerTechID;
    VOS_UINT8               ucLen;
    VOS_UINT8               aucRsv[2];
    VOS_UINT8               *pucServRecord;
}SI_STK_SERVICE_RECORD_STRU;

typedef struct
{
    VOS_UINT8               ucBarerTech;
    VOS_UINT8               ucLen;
    VOS_UINT8               aucRsv[2];
    VOS_UINT8               *pucServiceSearch;
}SI_STK_SERVICE_SEARCH_STRU;

typedef struct
{
    VOS_UINT8               ucBarerTech;
    VOS_UINT8               ucLen;
    VOS_UINT8               aucRsv[2];
    VOS_UINT8               *pucAttributeInfo;
}SI_STK_ATTRIBUTE_INFORMATION_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucESN;
}SI_STK_ESN_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucNetName;
}SI_STK_NETWORK_ACCESS_NAME_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucCDMASms;
}SI_STK_CDMA_SMS_STRU;

typedef struct
{
    VOS_UINT8               ucCodeType;
    VOS_UINT8               ucLen;
    VOS_UINT8               aucRsv[2];
    VOS_UINT8               *pucRemoteEntity;
}SI_STK_REMOTE_ENTITY_ADDRESS_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucText;
}SI_STK_TEXT_ATTRIBUTE_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucTAL;
}SI_STK_ITEM_TEXT_ATTRIBUTE_LIST_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucPDPPara;
}SI_STK_PDP_CONTEXT_ACTIVATION_PARAMETERS_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucIMEISV;
}SI_STK_IMEISV_STRU;

typedef struct
{
    VOS_UINT8               ucFrameLayout;
    VOS_UINT8               ucLen;
    VOS_UINT8               aucRsv[2];
    VOS_UINT8               *pucRSF;
}SI_STK_FRAME_LAYOUT_STRU;

typedef struct
{
    VOS_UINT8               ucNetSearchMode;
    VOS_UINT8               aucRsv[3];
}SI_STK_NETWORK_SEARCH_MODE_STRU;

typedef struct
{
    VOS_UINT8               ucFrameId;
    VOS_UINT8               ucLen;
    VOS_UINT8               aucRsv[2];
    VOS_UINT8               *pucFIL;
}SI_STK_FRAMES_INFORMATION_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucFrameID;
}SI_STK_FRAME_IDENTIFIER_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucMMReference;
}SI_STK_MM_MESSAGE_REFERENCE_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucMMId;
}SI_STK_MM_MESSAGE_IDENTIFIER_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucMMTStatus;
}SI_STK_MM_MESSAGE_TRANSFER_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucMMCId;
}SI_STK_MM_MESSAGE_CONTENT_ID_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucMMNotification;
}SI_STK_MM_MESSAGE_NOTIFICATION_STRU;

typedef struct
{
    VOS_UINT8               ucTech;
    VOS_UINT8               aucRsv[3];
}SI_STK_ACCESS_TECHNOLOGY_STRU;

typedef struct
{
    VOS_UINT8               ucBatState;
    VOS_UINT8               aucRsv[3];
}SI_STK_BATTERY_STATE_STRU;

typedef struct
{
    VOS_UINT8               ucReaderStatus;
    VOS_UINT8               aucRsv[3];
}SI_STK_CARD_READER_STATUS_STRU;

typedef struct
{
    VOS_UINT8               ucTimerId;
    VOS_UINT8               aucRsv[3];
}SI_STK_TIMER_IDENTIFIER_STRU;

typedef struct
{
    VOS_UINT8               ucHour;
    VOS_UINT8               ucMinute;
    VOS_UINT8               ucSecond;
    VOS_UINT8               ucRsv;
}SI_STK_TIMER_VALUE_STRU;

typedef struct
{
    VOS_UINT8               ucChannelLen;
    VOS_UINT8               aucRsv[3];
}SI_STK_CHANNEL_DATA_LENGTH_STRU;

typedef struct
{
    VOS_UINT8               ucChannelStatus[2];
    VOS_UINT8               aucRsv[2];
}SI_STK_CHANNEL_STATUS_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucService;
}SI_STK_SERVICE_AVAILABILITY_STRU;

typedef struct
{
    VOS_UINT8               pucBTC;
    VOS_UINT8               aucRsv[3];
}SI_STK_BROWSER_TERMIN_CAUSE_STRU;

typedef struct
{
    VOS_UINT8               pucParaList[3];
    VOS_UINT8               ucRsv;
}SI_STK_DISPLAY_PARAMETERS_STRU;


typedef struct
{
    VOS_UINT32              ucLen;
    VOS_UINT8               *pucBrowseStatus;
}SI_STK_BROWSING_STATUS_STRU;

typedef struct
{
    VOS_UINT32              ulLen;
    VOS_UINT8               *pucOplmnList;
}SI_STK_PLMNWACT_LIST_STRU;

typedef struct
{
    VOS_UINT8               aucRsv[4];
}SI_STK_STKHELP_REQUEST_STRU;

typedef struct
{
    VOS_UINT8               ucBCInd;
    VOS_UINT8               ucRsv;
    VOS_UINT8               aucRsv[2];
}SI_STK_BCREPIND_STRU;

typedef struct
{
    SI_CC_SPECI_TAG_ENUM_UINT8  ucTag;
    VOS_UINT8                   ucLen;
    VOS_UINT8                   aucRsv[2];
    VOS_UINT8                   *pValue;
}SI_STK_CALLCTRL_SPECIAL_STRU;

/* 31.111 8.91 Routing Area Identification */
typedef struct
{
    VOS_UINT32                  ulLen;
    VOS_UINT8                   *pucRauInfo;
}SI_STK_RAU_INFO_STRU;

/* 31.111 8.92 Update/Attach Type */
typedef struct
{
    VOS_UINT8                   ucTpye;
    VOS_UINT8                   ucRsv[3];
}SI_STK_UPDTAT_ATTACH_TYPE_STRU;

/* 31.111 8.93 Rejection Cause Code */
typedef struct
{
    VOS_UINT8                   ucCause;
    VOS_UINT8                   ucRsv[3];
}SI_STK_REJ_CAUSE_CODE_STRU;

/* 31.111 8.99 Tracking Area Identification */
typedef struct
{
    VOS_UINT32                  ulLen;
    VOS_UINT8                   *pucTauInfo;
}SI_STK_TAU_INFO_STRU;
/*****************************************************************************
  6 STK命令数据结构定义
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      OP_Text:1;
    VOS_UINT32                      OP_IconId:1;
    VOS_UINT32                      OP_Duration:1;
    VOS_UINT32                      OP_TextAttr:1;
    VOS_UINT32                      OP_ImmediateRsp:1;
    VOS_UINT32                      OP_FrameId:1;
    VOS_UINT32                      OP_Reserved:26;

    SI_STK_TEXT_STRING_STRU         TextStr;
    SI_STK_ICON_IDENTIFIER_STRU     IconId;
    SI_STK_DURATION_STRU            Duration;
    SI_STK_TEXT_ATTRIBUTE_STRU      TextAttr;
    VOS_UINT32                      FrameId;
}SI_STK_DISPLAY_TEXT_STRU;

typedef struct
{
    VOS_UINT32                      OP_Text:1;
    VOS_UINT32                      OP_IconId:1;
    VOS_UINT32                      OP_Duration:1;
    VOS_UINT32                      OP_TextAttr:1;
    VOS_UINT32                      OP_FrameId:1;
    VOS_UINT32                      OP_Reserved:27;

    SI_STK_TEXT_STRING_STRU         TextStr;
    SI_STK_ICON_IDENTIFIER_STRU     IconId;
    SI_STK_DURATION_STRU            Duration;
    SI_STK_TEXT_ATTRIBUTE_STRU      TextAttr;
    VOS_UINT32                      FrameId;
}SI_STK_GET_INKEY_STRU;

typedef struct
{
    VOS_UINT32                      OP_Text:1;
    VOS_UINT32                      OP_RpLen:1;
    VOS_UINT32                      OP_DefaultText:1;
    VOS_UINT32                      OP_IconId:1;
    VOS_UINT32                      OP_TextAttr:1;
    VOS_UINT32                      OP_FrameId:1;
    VOS_UINT32                      OP_Reserved:26;

    SI_STK_TEXT_STRING_STRU         TextStr;
    SI_STK_RESPONSE_LENGTH_STRU     RspLen;
    SI_STK_TEXT_STRING_STRU         DefaultText;
    SI_STK_ICON_IDENTIFIER_STRU     IconId;
    SI_STK_TEXT_ATTRIBUTE_STRU      TextAttr;
    VOS_UINT32                      FrameId;
}SI_STK_GET_INPUT_STRU;

typedef struct
{
    VOS_UINT32                      OP_AlphaId:1;
    VOS_UINT32                      OP_Tone:1;
    VOS_UINT32                      OP_Duration:1;
    VOS_UINT32                      OP_IconId:1;
    VOS_UINT32                      OP_TextAttr:1;
    VOS_UINT32                      OP_FrameId:1;
    VOS_UINT32                      OP_Reserved:26;

    SI_STK_ALPHA_IDENTIFIER_STRU    AlphaId;
    SI_STK_TONE_STRU                Tone;
    SI_STK_DURATION_STRU            Duration;
    SI_STK_ICON_IDENTIFIER_STRU     IconId;
    SI_STK_TEXT_ATTRIBUTE_STRU      TextAttr;
    VOS_UINT32                      FrameId;
}SI_STK_PLAY_TONE_STRU;

typedef struct
{
    VOS_UINT32                      OP_Duration:1;
    VOS_UINT32                      OP_Reserved:31;

    SI_STK_DURATION_STRU            Duration;
}SI_STK_POLLINTERVAL_STRU;

typedef struct
{
    VOS_UINT32                              OP_AlphaID:1;
    VOS_UINT32                              OP_INAIndicator:1;
    VOS_UINT32                              OP_IconId:1;
    VOS_UINT32                              OP_IIIlist:1;
    VOS_UINT32                              OP_TextAttr:1;
    VOS_UINT32                              OP_ITAList:1;
    VOS_UINT32                              OP_Item:1;
    VOS_UINT32                              OP_Reserved:25;

    SI_STK_ALPHA_IDENTIFIER_STRU            AlphaId;
    SI_STK_ITEMS_NEXTACTION_IND_STRU        INAIndicator;
    SI_STK_ICON_IDENTIFIER_STRU             IconId;
    SI_STK_ITEM_ICON_ID_LIST_STRU           IIIList;
    SI_STK_TEXT_ATTRIBUTE_STRU              TextAttr;
    SI_STK_ITEM_TEXT_ATTRIBUTE_LIST_STRU    ITAList;
    VOS_UINT32                              ulItemNum;
    SI_STK_ITEM_STRU                        Item[ITEMNUMMAX];
}SI_STK_SET_UP_MENU_STRU;

typedef struct
{
    VOS_UINT32                              OP_AlphaId:1;
    VOS_UINT32                              OP_INAIndicator:1;
    VOS_UINT32                              OP_IconId:1;
    VOS_UINT32                              OP_IIIlist:1;
    VOS_UINT32                              OP_TextAttr:1;
    VOS_UINT32                              OP_ITAList:1;
    VOS_UINT32                              OP_ItemIDTag:1;
    VOS_UINT32                              OP_FrameId:1;
    VOS_UINT32                              OP_ItemId:1;
    VOS_UINT32                              OP_Reserved:23;

    SI_STK_ALPHA_IDENTIFIER_STRU            AlphaId;
    SI_STK_ITEMS_NEXTACTION_IND_STRU        INAIndicator;
    SI_STK_ICON_IDENTIFIER_STRU             IconId;
    SI_STK_ITEM_ICON_ID_LIST_STRU           IIIList;
    SI_STK_TEXT_ATTRIBUTE_STRU              TextAttr;
    SI_STK_ITEM_TEXT_ATTRIBUTE_LIST_STRU    ITAList;
    VOS_UINT32                              ItemIDTag;
    VOS_UINT32                              FrameId;
    VOS_UINT32                              ItemNum;
    SI_STK_ITEM_STRU                        Item[ITEMNUMMAX];
}SI_STK_SELECT_ITEM_STRU;

typedef struct
{
    VOS_UINT32                      OP_AlphaId:1;
    VOS_UINT32                      OP_Addr:1;
    VOS_UINT32                      OP_WGTPDU:1;
    VOS_UINT32                      OP_CTPDU:1;
    VOS_UINT32                      OP_IconId:1;
    VOS_UINT32                      OP_TextAttr:1;
    VOS_UINT32                      OP_FrameId:1;
    VOS_UINT32                      OP_Reserved:25;

    SI_STK_ALPHA_IDENTIFIER_STRU    AlphaId;
    SI_STK_ADDRESS_STRU             Addr;
    SI_STK_SMS_TPDU_STRU            WGTPDU;
    SI_STK_SMS_TPDU_STRU            CTPDU;
    SI_STK_ICON_IDENTIFIER_STRU     IconId;
    SI_STK_TEXT_ATTRIBUTE_STRU      TextAttr;
    VOS_UINT32                      FrameId;
}SI_STK_SEND_SHORT_MESSAGE_STRU;

typedef struct
{
    VOS_UINT32                      OP_AlphaId:1;
    VOS_UINT32                      OP_SSStr:1;
    VOS_UINT32                      OP_IconId:1;
    VOS_UINT32                      OP_TextAttr:1;
    VOS_UINT32                      OP_Reserved:28;

    SI_STK_ALPHA_IDENTIFIER_STRU    AlphaId;
    SI_STK_SS_STRING_STRU           SSString;
    SI_STK_ICON_IDENTIFIER_STRU     IconId;
    SI_STK_TEXT_ATTRIBUTE_STRU      TextAttr;
}SI_STK_SEND_SS_STRU;

typedef struct
{
    VOS_UINT32                      OP_AlphaId:1;
    VOS_UINT32                      OP_USSDStr:1;
    VOS_UINT32                      OP_IconId:1;
    VOS_UINT32                      OP_TextAttr:1;
    VOS_UINT32                      OP_Reserved:28;

    SI_STK_ALPHA_IDENTIFIER_STRU    AlphaId;
    SI_STK_USSD_STRING_STRU         USSDString;
    SI_STK_ICON_IDENTIFIER_STRU     IconId;
    SI_STK_TEXT_ATTRIBUTE_STRU      TextAttr;
}SI_STK_SEND_USSD_STRU;

typedef struct
{
    VOS_UINT32                      OP_AlphaId:1;
    VOS_UINT32                      OP_Addr:1;
    VOS_UINT32                      OP_CCPara:1;
    VOS_UINT32                      OP_Subaddr:1;
    VOS_UINT32                      OP_Duration:1;
    VOS_UINT32                      OP_IconId:1;
    VOS_UINT32                      OP_TextAttr:1;
    VOS_UINT32                      OP_AlphaId2:1;
    VOS_UINT32                      OP_IconId2:1;
    VOS_UINT32                      OP_TextAttr2:1;
    VOS_UINT32                      OP_FrameId:1;
    VOS_UINT32                      OP_Reserved:21;

    SI_STK_ALPHA_IDENTIFIER_STRU    AlphaId;
    SI_STK_ADDRESS_STRU             Addr;
    SI_STK_CAPABILITY_CFG_PARA_STRU CCPara;
    SI_STK_SUBADDRESS_STRU          Subaddr;
    SI_STK_DURATION_STRU            Duration;
    SI_STK_ICON_IDENTIFIER_STRU     IconId;
    SI_STK_TEXT_ATTRIBUTE_STRU      TextAttr;
    VOS_UINT32                      FrameId;
    SI_STK_ALPHA_IDENTIFIER_STRU    AlphaId2;
    SI_STK_ICON_IDENTIFIER_STRU     IconId2;
    SI_STK_TEXT_ATTRIBUTE_STRU      TextAttr2;
}SI_STK_SET_UP_CALL_STRU;

typedef struct
{
    VOS_UINT32                      OP_FileList:1;
    VOS_UINT32                      OP_AID:1;
    VOS_UINT32                      OP_Alpha:1;
    VOS_UINT32                      OP_IconID:1;
    VOS_UINT32                      OP_TextAttr:1;
    VOS_UINT32                      OP_FrameId:1;
    VOS_UINT32                      OP_OplmnList:1;
    VOS_UINT32                      OP_Reserved:25;

    SI_STK_FILE_LIST_STRU           FileList;
    SI_STK_AID_STRU                 AID;
    SI_STK_ALPHA_IDENTIFIER_STRU    Alpha;
    SI_STK_ICON_IDENTIFIER_STRU     IconID;
    SI_STK_TEXT_ATTRIBUTE_STRU      TextAttr;
    VOS_UINT32                      FrameId;
    SI_STK_PLMNWACT_LIST_STRU       PlmnwactList;
}SI_STK_REFRESH_STRU;

typedef struct
{
    VOS_UINT32                      OP_Nmr:1;
    VOS_UINT32                      OP_Reserved:31;

    SI_STK_UTRAN_NMR_STRU           UtranNmr;
}SI_STK_PRIVIDE_LOCAL_INFO_STRU;


typedef struct
{
    VOS_UINT32                      OP_List:1;
    VOS_UINT32                      OP_Reserved:31;

    SI_STK_EVENT_LIST_STRU          EventList;
}SI_STK_SET_UP_EVENT_LIST_STRU;

typedef struct
{
    VOS_UINT32                      OP_CAPDU:1;
    VOS_UINT32                      OP_Reserved:31;

    SI_STK_C_APDU_STRU              CAPDU;
}SI_STK_PERFORM_CARD_APDU_STRU;

typedef struct
{
    VOS_UINT32                      OP_TimerID:1;
    VOS_UINT32                      OP_TimerValue:1;
    VOS_UINT32                      OP_Reserved:30;

    SI_STK_TIMER_IDENTIFIER_STRU    TimerID;
    SI_STK_TIMER_VALUE_STRU         TimerValue;
}SI_STK_TIMERMANAGE_STRU;

typedef struct
{
    VOS_UINT32                      OP_Text:1;
    VOS_UINT32                      OP_IconId:1;
    VOS_UINT32                      OP_TextAttr:1;
    VOS_UINT32                      OP_FrameId:1;
    VOS_UINT32                      OP_Reserved:28;

    SI_STK_TEXT_STRING_STRU         TextStr;
    SI_STK_ICON_IDENTIFIER_STRU     IconId;
    SI_STK_TEXT_ATTRIBUTE_STRU      TextAttr;
    VOS_UINT32                      FrameId;
}SI_STK_SET_UP_IDLE_MODE_TEXT_STRU;

typedef struct
{
    VOS_UINT32                      OP_AlphaId:1;
    VOS_UINT32                      OP_ATCmd:1;
    VOS_UINT32                      OP_IconId:1;
    VOS_UINT32                      OP_TextAttr:1;
    VOS_UINT32                      OP_FrameId:1;
    VOS_UINT32                      OP_Reserved:27;

    SI_STK_ALPHA_IDENTIFIER_STRU    AlphaId;
    SI_STK_AT_COMMAND_STRU          ATCmd;
    SI_STK_ICON_IDENTIFIER_STRU     IconId;
    SI_STK_TEXT_ATTRIBUTE_STRU      TextAttr;
    VOS_UINT32                      FrameId;
}SI_STK_RUN_AT_COMMAND_STRU;

typedef struct
{
    VOS_UINT32                      OP_AlphaId:1;
    VOS_UINT32                      OP_DTMF:1;
    VOS_UINT32                      OP_IconId:1;
    VOS_UINT32                      OP_TextAttr:1;
    VOS_UINT32                      OP_FrameId:1;
    VOS_UINT32                      OP_Reserved:27;

    SI_STK_ALPHA_IDENTIFIER_STRU    AlphaId;
    SI_STK_DTMF_STRING_STRU         DTMFStr;
    SI_STK_ICON_IDENTIFIER_STRU     IconId;
    SI_STK_TEXT_ATTRIBUTE_STRU      TextAttr;
    VOS_UINT32                      FrameId;
}SI_STK_SEND_DTMF_STRU;

typedef struct
{
    VOS_UINT32                       OP_Language:1;
    VOS_UINT32                       OP_Reserved:31;

    SI_STK_LANGUAGE_STRU            Language;
}SI_STK_LANGUAGE_NOTIFICATION_STRU;

typedef struct
{
    VOS_UINT32                      OP_BrowserId:1;
    VOS_UINT32                      OP_URL:1;
    VOS_UINT32                      OP_Bearer:1;
    VOS_UINT32                      OP_Texstr:1;
    VOS_UINT32                      OP_AlphaId:1;
    VOS_UINT32                      OP_IconId:1;
    VOS_UINT32                      OP_TextAttr:1;
    VOS_UINT32                      OP_FrameId:1;
    VOS_UINT32                      OP_PFRef:1;
    VOS_UINT32                      OP_Reserved:23;

    SI_STK_BROWSER_IDENTITY_STRU    BrowserId;
    SI_STK_URL_STRU                 URL;
    SI_STK_BEARER_STRU              Bearer;
    SI_STK_TEXT_STRING_STRU         TextStr;
    SI_STK_ALPHA_IDENTIFIER_STRU    AlphaId;
    SI_STK_ICON_IDENTIFIER_STRU     IconId;
    SI_STK_TEXT_ATTRIBUTE_STRU      TextAttr;
    VOS_UINT32                      FrameId;
    VOS_UINT32                      PfNumber;
    SI_STK_PRO_REFERENCE_FILE_STRU  PFRef[ITEMNUMMAX];
}SI_STK_LAUNCH_BROWSER_STRU;

typedef struct
{
    VOS_UINT32                          OP_AlphaId:1;
    VOS_UINT32                          OP_IconId:1;
    VOS_UINT32                          OP_Addr:1;
    VOS_UINT32                          OP_Subaddr:1;
    VOS_UINT32                          OP_Duration1:1;
    VOS_UINT32                          OP_BearerDesp:1;
    VOS_UINT32                          OP_BufSize:1;
    VOS_UINT32                          OP_NetworkAccName:1;
    VOS_UINT32                          OP_Textstr1:1;
    VOS_UINT32                          OP_UTITLevel:1;
    VOS_UINT32                          OP_TextAttr:1;
    VOS_UINT32                          OP_OtherAddr1:1;
    VOS_UINT32                          OP_FrameId:1;
    VOS_UINT32                          OP_Duration2:1;
    VOS_UINT32                          OP_Textstr2:1;
    VOS_UINT32                          OP_OtherAddr2:1;
    VOS_UINT32                          OP_Reserved:16;

    SI_STK_ALPHA_IDENTIFIER_STRU        AlphaId;
    SI_STK_ICON_IDENTIFIER_STRU         IconId;
    SI_STK_ADDRESS_STRU                 Addr;
    SI_STK_SUBADDRESS_STRU              Subaddr;
    SI_STK_DURATION_STRU                Duration1;
    SI_STK_BEARER_DESCRIPTION_STRU      BearerDesp;
    SI_STK_BUFFER_SIZE_STRU             BufSize;
    SI_STK_NETWORK_ACCESS_ANME_STRU     NetworkAccName;
    SI_STK_TEXT_STRING_STRU             TextStr1;
    SI_STK_UICC_TERMINAL_TRANLEVEL_STRU UTITLevel;
    SI_STK_TEXT_ATTRIBUTE_STRU          TextAttr;
    SI_STK_ADDRESS_STRU                 OtherAddr1;
    VOS_UINT32                          FrameId;
    SI_STK_DURATION_STRU                Duration2;
    SI_STK_TEXT_STRING_STRU             TextStr2;
    SI_STK_ADDRESS_STRU                 OtherAddr2;
}SI_STK_OPEN_CHANNEL_STRU;

typedef struct
{
    VOS_UINT32                      OP_AlphaId:1;
    VOS_UINT32                      OP_IconId:1;
    VOS_UINT32                      OP_TextAttr:1;
    VOS_UINT32                      OP_FrameId:1;
    VOS_UINT32                      OP_Reserved:28;

    SI_STK_ALPHA_IDENTIFIER_STRU    AlphaId;
    SI_STK_ICON_IDENTIFIER_STRU     IconId;
    SI_STK_TEXT_ATTRIBUTE_STRU      TextAttr;
    VOS_UINT32                      FrameId;
}SI_STK_CLOSE_CHANNEL_STRU;

typedef struct
{
    VOS_UINT32                      OP_AlphaId:1;
    VOS_UINT32                      OP_IconId:1;
    VOS_UINT32                      OP_TextAttr:1;
    VOS_UINT32                      OP_ChannleDataLen:1;
    VOS_UINT32                      OP_FrameId:1;
    VOS_UINT32                      OP_Reserved:27;

    SI_STK_ALPHA_IDENTIFIER_STRU    AlphaId;
    SI_STK_ICON_IDENTIFIER_STRU     IconId;
    SI_STK_TEXT_ATTRIBUTE_STRU      TextAttr;
    SI_STK_CHANNEL_DATA_LENGTH_STRU ChannleDataLen;
    VOS_UINT32                      FrameId;
}SI_STK_RECEIVE_DATA_STRU;

typedef struct
{
    VOS_UINT32                      OP_AlphaId:1;
    VOS_UINT32                      OP_IconId:1;
    VOS_UINT32                      OP_ChannelData:1;
    VOS_UINT32                      OP_TextAttr:1;
    VOS_UINT32                      OP_FrameId:1;
    VOS_UINT32                      OP_Reserved:27;

    SI_STK_ALPHA_IDENTIFIER_STRU    AlphaId;
    SI_STK_ICON_IDENTIFIER_STRU     IconId;
    SI_STK_CHANNEL_DATA_STRU        ChannelData;
    SI_STK_TEXT_ATTRIBUTE_STRU      TextAttr;
    VOS_UINT32                      FrameId;
}SI_STK_SEND_DATA_STRU;

typedef struct
{
    VOS_UINT32                      OP_AlphaId:1;
    VOS_UINT32                      OP_IconId:1;
    VOS_UINT32                      OP_Service:1;
    VOS_UINT32                      OP_DeviceFilter:1;
    VOS_UINT32                      OP_TextAttr:1;
    VOS_UINT32                      OP_FrameId:1;
    VOS_UINT32                      OP_Reserved:26;

    SI_STK_ALPHA_IDENTIFIER_STRU    AlphaId;
    SI_STK_ICON_IDENTIFIER_STRU     IconId;
    SI_STK_SERVICE_SEARCH_STRU      ServiceSearch;
    SI_STK_DEVICE_FILTER_STRU       DeviceFilter;
    SI_STK_TEXT_ATTRIBUTE_STRU      TextAttr;
    VOS_UINT32                      FrameId;
}SI_STK_SERVICE_SEARCH_PROACTIVE_STRU;

typedef struct
{
    VOS_UINT32                          OP_AlphaId:1;
    VOS_UINT32                          OP_IconId:1;
    VOS_UINT32                          OP_AttInfo:1;
    VOS_UINT32                          OP_TextAttr:1;
    VOS_UINT32                          OP_FrameId:1;
    VOS_UINT32                          OP_Reserved:27;

    SI_STK_ALPHA_IDENTIFIER_STRU        AlphaId;
    SI_STK_ICON_IDENTIFIER_STRU         IconId;
    SI_STK_ATTRIBUTE_INFORMATION_STRU   AttrInfo;
    SI_STK_TEXT_ATTRIBUTE_STRU          TextAttr;
    VOS_UINT32                          FrameId;
}SI_STK_GET_SERVICE_INFORMATION_STRU;

typedef struct
{
    VOS_UINT32                          OP_ServSRec:1;
    VOS_UINT32                          OP_UTITLevel:1;
    VOS_UINT32                          OP_Reserved:30;

    SI_STK_SERVICE_RECORD_STRU          ServiceRecord;
    SI_STK_UICC_TERMINAL_TRANLEVEL_STRU UTITLevel;
}SI_STK_DECLARE_SERVICE_STRU;

typedef struct
{
    VOS_UINT32                          OP_FrameLayout:1;
    VOS_UINT32                          OP_FrameId1:1;
    VOS_UINT32                          OP_FrameId2:1;
    VOS_UINT32                          OP_Reserved:29;

    SI_STK_FRAME_LAYOUT_STRU            FrameLayout;
    VOS_UINT32                          FrameId1;
    VOS_UINT32                          FrameId2;
}SI_STK_SET_FRAMES_STRU;

typedef struct
{
    VOS_UINT32                          OP_AlphaId:1;
    VOS_UINT32                          OP_IconId:1;
    VOS_UINT32                          OP_MMRef:1;
    VOS_UINT32                          OP_FileList:1;
    VOS_UINT32                          OP_MMCId:1;
    VOS_UINT32                          OP_MMId:1;
    VOS_UINT32                          OP_TextAttr:1;
    VOS_UINT32                          OP_Reserved:25;

    SI_STK_ALPHA_IDENTIFIER_STRU        AlphaId;
    SI_STK_ICON_IDENTIFIER_STRU         IconId;
    SI_STK_MM_MESSAGE_REFERENCE_STRU    MMReference;
    SI_STK_FILE_LIST_STRU               FileList;
    SI_STK_MM_MESSAGE_CONTENT_ID_STRU   MMCId;
    SI_STK_MM_MESSAGE_IDENTIFIER_STRU   MMId;
    SI_STK_TEXT_ATTRIBUTE_STRU          TextAttr;
}SI_STK_RETRIEVE_MM_MESSAGE_STRU;

typedef struct
{
    VOS_UINT32                          OP_AlphaId:1;
    VOS_UINT32                          OP_IconId:1;
    VOS_UINT32                          OP_FileList:1;
    VOS_UINT32                          OP_MMId:1;
    VOS_UINT32                          OP_TextAttr:1;
    VOS_UINT32                          OP_Reserved:27;

    SI_STK_ALPHA_IDENTIFIER_STRU        AlphaId;
    SI_STK_ICON_IDENTIFIER_STRU         IconId;
    SI_STK_FILE_LIST_STRU               FileList;
    SI_STK_MM_MESSAGE_IDENTIFIER_STRU   MMId;
    SI_STK_TEXT_ATTRIBUTE_STRU          TextAttr;
}SI_STK_SUBMIT_MM_MESSAGE_STRU;

typedef struct
{
    VOS_UINT32                          OP_FileList:1;
    VOS_UINT32                          OP_ImmediateRsp:1;
    VOS_UINT32                          OP_Reserved:30;

    SI_STK_FILE_LIST_STRU               FileList;
    SI_STK_MM_MESSAGE_IDENTIFIER_STRU   MMId;
}SI_STK_DISPLAY_MM_MESSAGE_STRU;


/*****************************************************************************
  6 STK命令回复数据结构定义
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  OP_TextStr:1;
    VOS_UINT32                  OP_Reserved:31;

    SI_STK_TEXT_STRING_STRU     TextStr;
}SI_STK_GET_INKEY_RSP_STRU;

typedef struct
{
    VOS_UINT32                  OP_TextStr:1;
    VOS_UINT32                  OP_Reserved:31;

    SI_STK_TEXT_STRING_STRU     TextStr;
}SI_STK_GET_INPUT_RSP_STRU;

typedef struct
{
    VOS_UINT32                  OP_ItemID:1;
    VOS_UINT32                  OP_Reserved:31;

    SI_STK_ITEM_IDENTIFIER_STRU ItemId;
}SI_STK_SELECT_ITEM_RSP_STRU;

typedef struct
{
    VOS_UINT32                      OP_LocInfo:1;
    VOS_UINT32                      OP_IMEI:1;
    VOS_UINT32                      OP_NMResults:1;
    VOS_UINT32                      OP_DTTZone:1;
    VOS_UINT32                      OP_Language:1;
    VOS_UINT32                      OP_AccessTech:1;
    VOS_UINT32                      OP_ESN:1;
    VOS_UINT32                      OP_IMEISV:1;
    VOS_UINT32                      OP_NSMode:1;
    VOS_UINT32                      OP_BatteryState:1;
    VOS_UINT32                      OP_Reserved:22;

    SI_STK_LOCATION_INFO_STRU       LocInfo;
    SI_STK_IMEI_STRU                IMEI;
    SI_STK_NET_MEASUREMENT_STRU     NMResults;
    SI_STK_DATE_TIME_ZONE_STRU      DTTZone;
    SI_STK_LANGUAGE_STRU            Language;
    SI_STK_ACCESS_TECHNOLOGY_STRU   AccessTech;
    SI_STK_ESN_STRU                 ESN;
    SI_STK_IMEISV_STRU              IMEISV;
    SI_STK_NETWORK_SEARCH_MODE_STRU NSMode;
    SI_STK_BATTERY_STATE_STRU       BatteryState;
}SI_STK_PROVIDE_LOCAL_INFORMATION_RSP_STRU;

typedef struct
{
    VOS_UINT32                                OP_CCRAction:1;
    VOS_UINT32                                OP_Result2:1;
    VOS_UINT32                                OP_TestStr2:1;
    VOS_UINT32                                OP_Reserved:29;

    SI_STK_CALL_CONTROL_REQUESTED_ACTION_STRU CCRAction;
    SI_STK_RESULT_STRU                        Result2;
    SI_STK_TEXT_STRING_STRU                   TextStr;
}SI_STK_SET_UP_CALL_RSP_STRU;

typedef struct
{
    VOS_UINT32                                OP_ReadStatus:1;
    VOS_UINT32                                OP_ReadId:1;
    VOS_UINT32                                OP_Reserved:30;

    SI_STK_CARD_READER_STATUS_STRU            ReadStatus;
    SI_STK_BUFFER_CARD_READER_IDENTIFIER_STRU ReadId;
}SI_STK_GET_READER_STATUS_RSP_STRU;

typedef struct
{
    VOS_UINT32                      OP_CardATR:1;
    VOS_UINT32                      OP_Reserved:31;

    SI_STK_CARD_ATR_STRU            CardATR;
}SI_STK_POWER_ON_CARD_RSP_STRU;

typedef struct
{
    VOS_UINT32                      OP_RAPDU:1;
    VOS_UINT32                      OP_Reserved:31;

    SI_STK_R_APDU_STRU              RAPDU;
}SI_STK_PERFORM_CARD_APDU_RSP_STRU;

typedef struct
{
    VOS_UINT32                      OP_ATRsp:1;
    VOS_UINT32                      OP_Reserved:31;

    SI_STK_AT_RESPONSE_STRU         ATRsp;
}SI_STK_RUN_AT_COMMAND_RSP_STRU;

typedef struct
{
    VOS_UINT32                          OP_ChannelStatus:1;
    VOS_UINT32                          OP_Reserved:31;

    SI_STK_CHANNEL_STATUS_STRU          ChannelStatus;
}SI_STK_GET_CHANNEL_STATUS_RSP_STRU;

typedef struct
{
    VOS_UINT32                          OP_ChannelStatus:1;
    VOS_UINT32                          OP_BearerDesp:1;
    VOS_UINT32                          OP_BufferSize:1;
    VOS_UINT32                          OP_OtherAddr:1;
    VOS_UINT32                          OP_Reserved:28;

    SI_STK_CHANNEL_STATUS_STRU          ChannelStatus;
    SI_STK_BEARER_DESCRIPTION_STRU      BearerDesp;
    SI_STK_BUFFER_SIZE_STRU             BufferSize;
    SI_STK_ADDRESS_STRU                 OtherAddr;
}SI_STK_OPEN_CHANNEL_RSP_STRU;

typedef struct
{
    VOS_UINT32                          OP_ServiceAvail:1;
    VOS_UINT32                          OP_Reserved:31;

    SI_STK_SERVICE_AVAILABILITY_STRU    ServiceAvail;
}SI_STK_SERVICE_SEARCH_PROACTIVE_RSP_STRU;

typedef struct
{
    VOS_UINT32                          OP_ServiceRecord:1;
    VOS_UINT32                          OP_Reserved:31;

    SI_STK_SERVICE_RECORD_STRU          ServiceRecord;
}SI_STK_GET_SERVICE_INFORMATION_RSP_STRU;

typedef struct
{
    VOS_UINT32                          OP_FrameInfo:1;
    VOS_UINT32                          OP_Reserved:31;

    SI_STK_FRAMES_INFORMATION_STRU      FrameInfo;
}SI_STK_SET_FRAMES_RSP_STRU;

typedef struct
{
    VOS_UINT32                          OP_FrameInfo:1;
    VOS_UINT32                          OP_Reserved:31;

    SI_STK_FRAMES_INFORMATION_STRU      FrameInfo;
}SI_STK_GET_FRAMES_STATUS_RSP_STRU;

/*****************************************************************************
  7 事件下发数据结构定义
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          OP_TransactionId:1;
    VOS_UINT32                          OP_Addr:1;
    VOS_UINT32                          OP_Subaddr:1;
    VOS_UINT32                          OP_Reserved:29;

    SI_STK_TRANSACTION_IDENTIFIER_STRU  TransactionId;
    SI_STK_ADDRESS_STRU                 Addr;
    SI_STK_SUBADDRESS_STRU              Subaddr;
}SI_STK_MT_CALL_EVENT_STRU;

typedef struct
{
    VOS_UINT32                          OP_TransactionId:1;
    VOS_UINT32                          OP_Reserved:31;

    SI_STK_TRANSACTION_IDENTIFIER_STRU  TransactionId;
}SI_STK_CALL_CONNECTED_EVENT_STRU;

typedef struct
{
    VOS_UINT32                          OP_TransactionId:1;
    VOS_UINT32                          OP_Cause:1;
    VOS_UINT32                          OP_Reserved:30;

    SI_STK_TRANSACTION_IDENTIFIER_STRU  TransactionId;
    SI_STK_CAUSE_STRU                   Cause;
}SI_STK_CALL_DISCONNECTED_EVENT_STRU;

typedef struct
{
    VOS_UINT32                          OP_LocStatus:1;
    VOS_UINT32                          OP_LocInfo:1;
    VOS_UINT32                          OP_Reserved:30;

    SI_STK_LOCATION_STATUS_STRU         LocStatus;
    SI_STK_LOCATION_INFO_STRU           LocInfo;
}SI_STK_LOCATION_STATUS_EVENT_STRU;

typedef struct
{
    VOS_UINT32                          OP_CRStatus:1;
    VOS_UINT32                          OP_Reserved:31;

    SI_STK_CARD_READER_STATUS_STRU      CRStatus;
}SI_STK_CARD_READER_STATUS_EVENT_STRU;

typedef struct
{
    VOS_UINT32                          OP_Language:1;
    VOS_UINT32                          OP_Reserved:31;

    SI_STK_LANGUAGE_STRU                Language;
}SI_STK_LANGUAGE_SELECTION_EVENT_STRU;

typedef struct
{
    VOS_UINT32                         OP_BTCause:1;
    VOS_UINT32                         OP_Reserved:31;

    SI_STK_BROWSER_TERMIN_CAUSE_STRU   BTCause;
}SI_STK_BROWSER_TERMINATION_EVENT_STRU;

typedef struct
{
    VOS_UINT32                          OP_ChannelStatus:1;
    VOS_UINT32                          OP_CDLen:1;
    VOS_UINT32                          OP_Reserved:30;

    SI_STK_CHANNEL_STATUS_STRU          ChannelStatus;
    SI_STK_CHANNEL_DATA_LENGTH_STRU     CDLen;
}SI_STK_DATA_AVAILABLE_EVENT_STRU;

typedef struct
{
    VOS_UINT32                          OP_ChannelStatus:1;
    VOS_UINT32                          OP_BearerDesp:1;
    VOS_UINT32                          OP_OtherAddr:1;
    VOS_UINT32                          OP_Reserved:29;

    SI_STK_CHANNEL_STATUS_STRU          ChannelStatus;
    SI_STK_BEARER_DESCRIPTION_STRU      BearerDesp;
    SI_STK_ADDRESS_STRU                 OtherAddr;
}SI_STK_CHANNEL_STATUS_EVENT_STRU;

typedef struct
{
    VOS_UINT32                          OP_AccessTech:1;
    VOS_UINT32                          OP_Reserved:31;

    SI_STK_ACCESS_TECHNOLOGY_STRU       AccessTech;
}SI_STK_ACCESS_TECHNOLOGY_CHANGE_EVENT_STRU;

typedef struct
{
    VOS_UINT32                          OP_DisplayPara:1;
    VOS_UINT32                          OP_Reserved:31;

    SI_STK_DISPLAY_PARAMETERS_STRU      DisplayPara;
}SI_STK_DISPLAY_PARAMETERS_CHANGED_EVENT_STRU;

typedef struct
{
    VOS_UINT32                          OP_ServiceRecord:1;
    VOS_UINT32                          OP_REAddr:1;
    VOS_UINT32                          OP_UTITlevel:1;
    VOS_UINT32                          OP_RETLAddr:1;
    VOS_UINT32                          OP_Reserved:28;

    SI_STK_SERVICE_RECORD_STRU          ServiceRecord;
    SI_STK_REMOTE_ENTITY_ADDRESS_STRU   REAddr;
    SI_STK_UICC_TERMINAL_TRANLEVEL_STRU UTITlevel;
    SI_STK_ADDRESS_STRU                 RETLAddr;
}SI_STK_LOCAL_CONNECTION_EVENT_STRU;

typedef struct
{
    VOS_UINT32                          OP_NSMode:1;
    VOS_UINT32                          OP_Reserved:31;

    SI_STK_NETWORK_SEARCH_MODE_STRU     NSMode;
}SI_STK_NETWORK_SEARCH_MODE_CHANGE_EVENT_STRU;

typedef struct
{
    VOS_UINT32                          OP_BrowseStatus:1;
    VOS_UINT32                          OP_Reserved:31;

    SI_STK_BROWSING_STATUS_STRU         BrowseStatus;
}SI_STK_BROWSING_STATUS_EVENT_STRU;

typedef struct
{
    VOS_UINT32                          OP_FrameInfo:1;
    VOS_UINT32                          OP_Reserved:31;

    SI_STK_FRAMES_INFORMATION_STRU      FrameInfo;
}SI_STK_FRAMES_INFORMATION_EVENT_STRU;

/*****************************************************************************
 结构名    : SI_STK_NETWORK_REJ_EVENT_STRU
 结构说明  : NETWORK REJECTION事件数据结构
 1.日    期: 2013年7月12日
   作    者: H59254
   修改内容: 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          OP_LocaInfo:1;
    VOS_UINT32                          OP_RauInfo:1;
    VOS_UINT32                          OP_TauInfo:1;
    VOS_UINT32                          OP_AccTech:1;
    VOS_UINT32                          OP_UpdateAttachType:1;
    VOS_UINT32                          OP_RejCauseCode:1;
    VOS_UINT32                          OP_Reserved:26;

    SI_STK_LOCATION_INFO_STRU           stLocaInfo;
    SI_STK_RAU_INFO_STRU                stRauInfo;
    SI_STK_TAU_INFO_STRU                stTauInfo;
    SI_STK_ACCESS_TECHNOLOGY_STRU       stAccTech;
    SI_STK_UPDTAT_ATTACH_TYPE_STRU      stUpdateAttachType;
    SI_STK_REJ_CAUSE_CODE_STRU          stRejCauseCode;
}SI_STK_NETWORK_REJ_EVENT_STRU;

/*****************************************************************************
  8 Envelope命令数据容器定义
*****************************************************************************/

typedef struct
{
    VOS_UINT32                      OP_ItemIp:1;
    VOS_UINT32                      OP_Help:1;
    VOS_UINT32                      OP_Reserved:30;

    SI_STK_ITEM_IDENTIFIER_STRU     ItemId;
    SI_STK_STKHELP_REQUEST_STRU     Help;
}SI_STK_MENU_SELECTION_STRU;

typedef struct
{
    VOS_UINT32                      OP_Capability1:1;
    VOS_UINT32                      OP_Subaddr:1;
    VOS_UINT32                      OP_LocInfo:1;
    VOS_UINT32                      OP_Capability2:1;
    VOS_UINT32                      OP_BCRepInd:1;
    VOS_UINT32                      OP_SepcialData:1;
    VOS_UINT32                      OP_Reserved:26;

    SI_STK_CAPABILITY_CFG_PARA_STRU Capability1;
    SI_STK_SUBADDRESS_STRU          Subaddr;
    SI_STK_LOCATION_INFO_STRU       LocInfo;
    SI_STK_CAPABILITY_CFG_PARA_STRU Capability2;
    SI_STK_BCREPIND_STRU            BCRepInd;
    SI_STK_CALLCTRL_SPECIAL_STRU    SpecialData;
}SI_STK_CALL_CONTROL_STRU;

typedef struct
{
    VOS_UINT32                      OP_Addr1:1;
    VOS_UINT32                      OP_Addr2:1;
    VOS_UINT32                      OP_Local:1;
    VOS_UINT32                      OP_Reserved:29;

    SI_STK_ADDRESS_STRU             Addr1;
    SI_STK_ADDRESS_STRU             Addr2;
    SI_STK_LOCATION_INFO_STRU       LocInfo;
}SI_STK_MOSMS_CONTROL_STRU;

typedef struct
{
    VOS_UINT32                      OP_Addr:1;
    VOS_UINT32                      OP_TPDU:1;
    VOS_UINT32                      OP_XTPDU:1;
    VOS_UINT32                      OP_Reserved:29;

    SI_STK_ADDRESS_STRU             Addr;
    SI_STK_SMS_TPDU_STRU            TPDU;
    SI_STK_CDMA_SMS_STRU            XTPDU;
}SI_STK_SMS_PP_DOWNLOAD_STRU;

typedef struct
{
    VOS_UINT32                          OP_CBPage:1;
    VOS_UINT32                          OP_Reserved:31;

    SI_STK_CELL_BROADCAST_PAGE_STRU     CBPage;
}SI_STK_CB_DOWNLOAD_STRU;

typedef struct
{
    VOS_UINT32                          OP_FileList:1;
    VOS_UINT32                          OP_MMId:1;
    VOS_UINT32                          OP_MMTStatus:1;
    VOS_UINT32                          OP_Reserved:29;

    SI_STK_FILE_LIST_STRU               FileList;
    SI_STK_MM_MESSAGE_IDENTIFIER_STRU   MMId;
    SI_STK_MM_MESSAGE_TRANSFER_STRU     MMTStatus;
}SI_STK_MMS_TRANSFER_STATUS_STRU;

typedef struct
{
    VOS_UINT32                          OP_MMSNotify:1;
    VOS_UINT32                          OP_LastEnvelope:1;
    VOS_UINT32                          OP_Reserved:30;

    SI_STK_MM_MESSAGE_NOTIFICATION_STRU MMSNotify;
    VOS_UINT8                            LEnvelope;
    VOS_UINT8                            Rsv[3];
}SI_STK_MMS_NOITFY_STRU;

/*****************************************************************************
  9 Envelope命令回复数据容器定义
*****************************************************************************/
/*****************************************************************************
结构名    : SI_STK_CTRL_DATA_STRU
结构说明  : CALL CONTROL结果数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           ucDataType;
    VOS_UINT8                           ucRsv;
    VOS_UINT8                           aucData[SI_STK_DATA_MAX_LEN];
}SI_STK_CTRL_DATA_STRU;

/*****************************************************************************
结构名    : SI_STK_ADDR_INFO_STRU
结构说明  : CALL CONTROL地址信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumType;
    VOS_UINT8                           ucAddrLen;
    VOS_UINT8                           aucAddr[SI_STK_ADDR_MAX_LEN];
}SI_STK_ADDR_INFO_STRU;

/*****************************************************************************
结构名    : SI_STK_MOSMSCTRL_INFO_STRU
结构说明  : MO SMS CONTROL结果上报信息结构
*****************************************************************************/
typedef struct
{
    SI_STK_ADDR_INFO_STRU               stDstAddrInfo;
    SI_STK_ADDR_INFO_STRU               stSerCenterAddrInfo;
}SI_STK_MOSMSCTRL_INFO_STRU;

/*****************************************************************************
结构名    : SI_STK_ALPHAID_INFO_STRU
结构说明  : ALPHAID结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulAlphaLen;
    VOS_UINT8                            aucAlphaId[SI_STK_DATA_MAX_LEN];
}SI_STK_ALPHAID_INFO_STRU;

/*****************************************************************************
结构名    : SI_STK_CC_IND_STRU
结构说明  : MO SMS CONTRL 或 MO CALL CONTROL结果上报结构
*****************************************************************************/
typedef struct
{
    union
    {
        SI_STK_CTRL_DATA_STRU           stCtrlDataInfo;
        SI_STK_MOSMSCTRL_INFO_STRU      stMoSmsCtrlInfo;
    }uInfo;

    VOS_UINT8                           ucType;
    VOS_UINT8                           ucResult;
    VOS_UINT16                          usRsv;
    SI_STK_ALPHAID_INFO_STRU            stAlphaIdInfo;
}SI_STK_CC_IND_STRU;

/*****************************************************************************
结构名    : SI_STK_SMS_PP_DL_DATA_INFO_STRU
结构说明  : 虚拟卡SMS PP DOWNLOAD数据上报结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLen;
    VOS_UINT8                           aucData[SI_STK_DATA_MAX_LEN - 1];
}SI_STK_SMS_PP_DL_DATA_INFO_STRU;


typedef struct
{
    VOS_UINT32                      OP_CCP1:1;
    VOS_UINT32                      OP_SubAddr:1;
    VOS_UINT32                      OP_Alaph:1;
    VOS_UINT32                      OP_BCRepInd:1;
    VOS_UINT32                      OP_CCP2:1;
    VOS_UINT32                      OP_SepcialData:1;
    VOS_UINT32                      OP_Reserved:26;

    SI_STK_CAPABILITY_CFG_PARA_STRU CCP1;
    SI_STK_SUBADDRESS_STRU          SubAddrStr;
    SI_STK_ALPHA_IDENTIFIER_STRU    AlphaId;
    SI_STK_BCREPIND_STRU            BCRepInd;
    SI_STK_CAPABILITY_CFG_PARA_STRU CCP2;
    SI_STK_CALLCTRL_SPECIAL_STRU    SpecialData;
}SI_STK_CALLCTRL_RSP_STRU;

typedef struct
{
    VOS_UINT32                      OP_Alaph:1;
    VOS_UINT32                      OP_Addr1:1;
    VOS_UINT32                      OP_Addr2:1;
    VOS_UINT32                      OP_Reserved:29;

    SI_STK_ALPHA_IDENTIFIER_STRU    AlphaId;
    SI_STK_ADDRESS_STRU             Addr1;
    SI_STK_ADDRESS_STRU             Addr2;
}SI_STK_MOSMSCTRL_RSP_STRU;

typedef struct
{
    union
    {
        SI_STK_CALLCTRL_RSP_STRU    CallCtrlRsp;
        SI_STK_MOSMSCTRL_RSP_STRU   MoSmsCtrlRsp;
    }uResp;

    SI_STK_ENVELOPE_TYPE_UINT32     EnvelopeType;
    VOS_UINT32                      Result;
}SI_STK_ENVELOPE_RSP_STRU;

/*****************************************************************************
  10 STK命令数据容器定义
*****************************************************************************/

typedef struct
{
    union
    {
        SI_STK_DISPLAY_TEXT_STRU               DisplayText;
        SI_STK_GET_INKEY_STRU                  GetInkey;
        SI_STK_GET_INPUT_STRU                  GetInput;
        SI_STK_PLAY_TONE_STRU                  PlayTone;
        SI_STK_POLLINTERVAL_STRU               PoolInterval;
        SI_STK_SET_UP_MENU_STRU                SetupMenu;
        SI_STK_SELECT_ITEM_STRU                SelectItem;
        SI_STK_SEND_SHORT_MESSAGE_STRU         SendSMS;
        SI_STK_SEND_SS_STRU                    SendSS;
        SI_STK_SEND_USSD_STRU                  SendSSD;
        SI_STK_SET_UP_CALL_STRU                SetupCall;
        SI_STK_REFRESH_STRU                    Refresh;
        SI_STK_PRIVIDE_LOCAL_INFO_STRU         PLocalInfo;
        SI_STK_SET_UP_EVENT_LIST_STRU          SEList;
        SI_STK_PERFORM_CARD_APDU_STRU          PCAPDU;
        SI_STK_TIMERMANAGE_STRU                TimerManage;
        SI_STK_SET_UP_IDLE_MODE_TEXT_STRU      IdleText;
        SI_STK_RUN_AT_COMMAND_STRU             AtCmd;
        SI_STK_SEND_DTMF_STRU                  DTMFCmd;
        SI_STK_LANGUAGE_NOTIFICATION_STRU      LangNotify;
        SI_STK_LAUNCH_BROWSER_STRU             LaunchBrowser;
        SI_STK_OPEN_CHANNEL_STRU               OpenChannel;
        SI_STK_CLOSE_CHANNEL_STRU              CloseChannel;
        SI_STK_SERVICE_SEARCH_PROACTIVE_STRU   ServiceSearch;
        SI_STK_GET_SERVICE_INFORMATION_STRU    ServiceInfo;
        SI_STK_DECLARE_SERVICE_STRU            DeclareService;
        SI_STK_SET_FRAMES_STRU                 SetFrames;
        SI_STK_RETRIEVE_MM_MESSAGE_STRU        RetMMMsg;
        SI_STK_SUBMIT_MM_MESSAGE_STRU          SubmitMMMsg;
        SI_STK_DISPLAY_MM_MESSAGE_STRU         DspMMMsg;
        SI_STK_CC_IND_STRU                     STKCcIndInfo;
        SI_STK_SMS_PP_DL_DATA_INFO_STRU        SmsPpDlDataInfo;
        VOS_UINT8                               aucPadding[115*8];
    }CmdStru;

    SI_STK_COMMAND_DETAILS_STRU     CmdDetail;
    SI_STK_DEVICE_IDENTITIES_STRU   CmdDevice;
    SI_STK_CMD_TYPE                 SatType;
    SI_STK_CMDDATA_STRU             SatCmd;
}SI_STK_DATA_INFO_STRU;

/*****************************************************************************
  11 STK命令回复数据容器定义
*****************************************************************************/

typedef struct
{
    union
    {
        SI_STK_GET_INKEY_RSP_STRU                  GetInkeyRsp;
        SI_STK_GET_INPUT_RSP_STRU                  GetInputRsp;
        SI_STK_SELECT_ITEM_RSP_STRU                SelectItemRsp;
        SI_STK_SET_UP_CALL_RSP_STRU                SetupCallRsp;
        SI_STK_SET_UP_CALL_RSP_STRU                SendSSRsp;
        SI_STK_SET_UP_CALL_RSP_STRU                SendUSSDRsp;
        SI_STK_GET_READER_STATUS_RSP_STRU          ReadStatusRsp;
        SI_STK_POWER_ON_CARD_RSP_STRU              PowerOnRsp;
        SI_STK_PERFORM_CARD_APDU_RSP_STRU          PerformAPDURsp;
        SI_STK_RUN_AT_COMMAND_RSP_STRU             ATCmdRsp;
        SI_STK_SERVICE_SEARCH_PROACTIVE_RSP_STRU   ServiceSearchRsp;
        SI_STK_GET_SERVICE_INFORMATION_RSP_STRU    ServiceInfoRsp;
        SI_STK_SET_FRAMES_RSP_STRU                 SetFrameRsp;
        SI_STK_GET_FRAMES_STATUS_RSP_STRU          GetFrameStatusRsp;
    }uResp;

    SI_STK_CMD_TYPE                     CmdType;
    SI_STK_COMMAND_DETAILS_STRU         CmdDetail;
    SI_STK_DEVICE_IDENTITIES_STRU       DeviceId;
    SI_STK_RESULT_STRU                  Result;
    VOS_UINT8                           aucData[SI_STK_DATA_MAX_LEN];
}SI_STK_TERMINAL_RSP_STRU;

/*****************************************************************************
  12 Envelope&Event数据结构声明
*****************************************************************************/

typedef struct
{
    union
    {
        SI_STK_MT_CALL_EVENT_STRU                    MCEvent;
        SI_STK_CALL_CONNECTED_EVENT_STRU             CCEvent;
        SI_STK_CALL_DISCONNECTED_EVENT_STRU          CDEvent;
        SI_STK_LOCATION_STATUS_EVENT_STRU            LSatusEvent;
        SI_STK_CARD_READER_STATUS_EVENT_STRU         CRSEvent;
        SI_STK_LANGUAGE_SELECTION_EVENT_STRU         LSelectEvent;
        SI_STK_BROWSER_TERMINATION_EVENT_STRU        BTEvent;
        SI_STK_DATA_AVAILABLE_EVENT_STRU             DAEvent;
        SI_STK_CHANNEL_STATUS_EVENT_STRU             CSEvent;
        SI_STK_ACCESS_TECHNOLOGY_CHANGE_EVENT_STRU   ATCEvent;
        SI_STK_DISPLAY_PARAMETERS_CHANGED_EVENT_STRU DPCEvent;
        SI_STK_LOCAL_CONNECTION_EVENT_STRU           LCEvent;
        SI_STK_NETWORK_SEARCH_MODE_CHANGE_EVENT_STRU NSMCEvent;
        SI_STK_BROWSING_STATUS_EVENT_STRU            BSEvent;
        SI_STK_FRAMES_INFORMATION_EVENT_STRU         FIEvent;
        SI_STK_NETWORK_REJ_EVENT_STRU                NREvent;
    }uEvent;

    SI_STK_EVENT_TYPE               EventDownTag;
    SI_STK_DEVICE_IDENTITIES_STRU   DeviceId;
    VOS_UINT8                       aucData[SI_STK_DATA_MAX_LEN];
}SI_STK_EVENTDOWN_STRU;

typedef struct
{
    union
    {
        SI_STK_SMS_PP_DOWNLOAD_STRU     PPDown;
        SI_STK_CB_DOWNLOAD_STRU         CBDown;
        SI_STK_MENU_SELECTION_STRU      MenuSelect;
        SI_STK_CALL_CONTROL_STRU        CallCtrl;
        SI_STK_MOSMS_CONTROL_STRU       MOSMSCtrl;
        SI_STK_MMS_TRANSFER_STATUS_STRU MMSTran;
        SI_STK_MMS_NOITFY_STRU          MMSNotify;
    }uEnvelope;

    SI_STK_ENVELOPE_TYPE_UINT32     enEnvelopeType;
    SI_STK_DEVICE_IDENTITIES_STRU   DeviceId;
    VOS_UINT8                       aucData[SI_STK_DATA_MAX_LEN];
}SI_STK_ENVELOPE_STRU;

/*****************************************************************************
  13 回调函数数据结构声明
*****************************************************************************/

typedef struct
{
    VOS_UINT8               SW1;
    VOS_UINT8               SW2;
    VOS_UINT8               Rev[2];
}SI_STK_SW_INFO_STRU;

typedef struct
{
    SI_CLIENT_ID_T          ClientId;
    VOS_UINT8               OpId;
    STK_CALLBACK_EVENT      STKCBEvent;
    VOS_UINT32              STKErrorNo;
    SI_STK_DATA_INFO_STRU   STKCmdStru;
    SI_STK_SW_INFO_STRU     STKSwStru;
}SI_STK_EVENT_INFO_STRU;

typedef struct
{
    SI_CLIENT_ID_T          ClientId;
    VOS_UINT8               OpId;
    VOS_UINT8               CmdQualify;
    VOS_UINT32              DataLen;
    VOS_UINT8               aucData[STK_PRINT_MAX_LEN];
}SI_STK_PRINTDATA_CNF_STRU;


/*****************************************************************************
  14 外部函数和结构声明
*****************************************************************************/
typedef TAF_VOID (*pfSTKCmdATPrint)(TAF_UINT16* pusDataLen, SI_STK_DATA_INFO_STRU * pEvent);


typedef struct
{
    SI_STK_CMD_TYPE         CmdType;
    pfSTKCmdATPrint         pfATPrint;
}SI_STK_ATPRINT_STRU;

typedef struct
{
    VOS_UINT32              Mcc;
    VOS_UINT32              Mnc;
}STK_PLMN_ID_STRU;

/*****************************************************************************
 结构名    : SI_STK_SYS_INFO_STRU
 结构说明  : STK模块维护的系统信息字段结构
*****************************************************************************/
typedef struct
{
    SI_STK_ACCESS_TECH_ENUM_UINT8       enCurRat;       /* 接入技术 */
    SI_STK_SEARCH_MODE_ENUM_UINT8       enSrchMode;     /* 搜网模式 */
    NAS_STK_UTRAN_MODE_ENUM_UINT8       enUtranMode;    /* TDD或FDD模式 */
    VOS_UINT8                           ucRsv;
    VOS_UINT32                          ulCellId;       /* 小区ID */
    STK_PLMN_ID_STRU                    stCurPlmnId;    /* PLMN */
    VOS_UINT16                          usLac;
}SI_STK_SYS_INFO_STRU;

/*****************************************************************************
 结构名    : SI_STK_NAS_INFO_STRU
 结构说明  : STK模块维护的NAS信息字段结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventMsgFlag;
    /* 使用STK自定义的服务状态，不使用NAS消息中的值，在更新时需要转换 */
    SI_STK_SERVICE_STATUS_ENUM_UINT32   enServiceStatus;
    SI_STK_SERVICE_STATUS_ENUM_UINT32   enCsServiceStatus;
    SI_STK_SYS_INFO_STRU                stSysInfo;
}SI_STK_NAS_INFO_STRU;

typedef struct
{
    /* 使用STK自定义的服务状态，不使用NAS消息中的值，在更新时需要转换 */
    SI_STK_SERVICE_STATUS_ENUM_UINT32   enServiceStatus;
    MMA_STK_1X_SYS_INFO_STRU            stSysInfo;
}SI_STK_CDMANAS_SYSINFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulQueryType;
}STK_AS_NMR_INFO_REQ_STRU;

/* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, begin */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
}STK_AS_TA_INFO_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucMEStatus;
    VOS_UINT8                           ucTAValue;
    VOS_UINT8                           ucReserved[2];
}STK_AS_TA_INFO_CNF_STRU;
/* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, end */

/*****************************************************************************
 结构名    : STK_LAS_CELL_FREQ_INFO_STRU
 结构说明  : LRRC给STK模块的小区频率信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usNmrLen;
    VOS_UINT8                           aucCellFreq[2];
    VOS_UINT8                           aucNmrData[100];
}STK_LAS_CELL_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : STK_LAS_NMR_INFO_STRU
 结构说明  : LRRC给STK模块的测量回复
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulResult;
    SI_STK_NMR_TYPE_ENUM_UINT32         enQueryType;
    VOS_UINT16                          usSecondCellFreq;
    VOS_UINT16                          usCellFreqInfoNum;
    STK_LAS_CELL_FREQ_INFO_STRU         astCellInfo[3];
}STK_LAS_NMR_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulQueryType;
    VOS_UINT32                          ulNmrLen;
    VOS_UINT8                           aucNmrData[4];
}STK_WAS_NMR_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulNmrLen;
    VOS_UINT8                           aucNmrData[16];
    VOS_UINT32                          ulBCCHLen;
    VOS_UINT8                           aucBCCHData[40];
}STK_GAS_NMR_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;      /* 消息名 */
    VOS_UINT16                          usOplmnListLen; /* Oplmn的列表长度*/
    VOS_UINT8                           aucOplmnList[6];/* Oplmn的列表内容*/
}STK_NAS_STEERING_OF_ROAMING_STRU;

/*****************************************************************************
  6 New STRUCT定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    SI_STK_REQMSG_ENUM_UINT32       enMsgName;
    VOS_UINT32                      ulSendPara;
    VOS_UINT16                      usATClient;
    VOS_UINT8                       ucOpID;
    VOS_UINT8                       ucRsv;
} SI_STK_REQMSGHEADER_STRU;

typedef struct
{
    VOS_UINT32                       OP_ItemIp:1;
    VOS_UINT32                       OP_Help:1;
    VOS_UINT32                       OP_Reserved:30;
} SI_STK_MENUSELECTION_FLAG_STRU;

typedef struct
{
    VOS_UINT32                       OP_Addr:1;
    VOS_UINT32                       OP_TPDU:1;
    VOS_UINT32                       OP_Reserved:30;
} SI_STK_SMSPP_FLAG_STRU;

typedef struct
{
    VOS_UINT32                       OP_CBPage:1;
    VOS_UINT32                       OP_Reserved:31;
} SI_STK_CBDOWNLOAD_FLAG_STRU;

typedef struct
{
    VOS_UINT32                       OP_Capability1:1;
    VOS_UINT32                       OP_Subaddr:1;
    VOS_UINT32                       OP_LocInfo:1;
    VOS_UINT32                       OP_Capability2:1;
    VOS_UINT32                       OP_BCRepInd:1;
    VOS_UINT32                       OP_SepcialData:1;
    VOS_UINT32                       OP_Reserved:26;
} SI_STK_CALLCTRL_FLAG_STRU;

typedef struct
{
    VOS_UINT32                       OP_Addr1:1;
    VOS_UINT32                       OP_Addr2:1;
    VOS_UINT32                       OP_Local:1;
    VOS_UINT32                       OP_Reserved:29;
} SI_STK_MOSMSCTRL_FLAG_STRU;

typedef struct
{
    union
    {
        SI_STK_SMSPP_FLAG_STRU      stSmsPPFlag;
        SI_STK_CBDOWNLOAD_FLAG_STRU stCBDownFlag;
        SI_STK_CALLCTRL_FLAG_STRU   stCallCtrlFlag;
        SI_STK_MOSMSCTRL_FLAG_STRU  stMoSmsCtrlFlag;
    }uReqFlag;

    VOS_UINT32                      ulDataLen;
    VOS_UINT8                       aucData[SI_STK_DATA_MAX_LEN];
}SI_STK_ENVELOPEDOWN_STRU;

typedef struct
{
    SI_STK_REQMSGHEADER_STRU        stMsgHeader;
    VOS_BOOL                        bTransFlag;
    SI_STK_ENVELOPE_TYPE_UINT32     enEnvelopeType;
    SI_STK_ENVELOPEDOWN_STRU        stEnvelopeData;
} SI_STK_ENVELOPEDOWN_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    SI_STK_CNFMSG_ENUM_UINT32       enMsgName;
    VOS_UINT32                      ulSendPara;
    VOS_UINT32                      ulResult;
    VOS_UINT32                      ulErrorNO;
    VOS_UINT16                      usATClientID;
    VOS_UINT8                       ucOpID;
    VOS_UINT8                       ucRsv;
    SI_STK_SW_INFO_STRU             stSWData;
} SI_STK_CNFMSGHEADER_STRU;

typedef struct
{
    VOS_UINT32                      OP_CCP1:1;
    VOS_UINT32                      OP_SubAddr:1;
    VOS_UINT32                      OP_Alaph:1;
    VOS_UINT32                      OP_BCRepInd:1;
    VOS_UINT32                      OP_CCP2:1;
    VOS_UINT32                      OP_SepcialData:1;
    VOS_UINT32                      OP_Reserved:26;
} SI_STK_CALLCTRL_CNFFLAG_STRU;

typedef struct
{
    VOS_UINT32                      OP_Alaph:1;
    VOS_UINT32                      OP_Addr1:1;
    VOS_UINT32                      OP_Addr2:1;
    VOS_UINT32                      OP_Reserved:29;
} SI_STK_MOSMSCTRL_CNFFLAG_STRU;

typedef struct
{
    union
    {
        SI_STK_CALLCTRL_CNFFLAG_STRU    stCallCtrlCnfFlag;
        SI_STK_MOSMSCTRL_CNFFLAG_STRU   stMoSmsCtrlCnfFlag;
    }uRespFlag;

    VOS_UINT32                      ulRspResult;
    VOS_UINT32                      ulRspDataLen;
    VOS_UINT8                       aucRspData[SI_STK_DATA_MAX_LEN];
}SI_STK_ENVELOPE_CNFDATA_STRU;

typedef struct
{
    SI_STK_CNFMSGHEADER_STRU        stCmdResult;
    SI_STK_ENVELOPE_TYPE_UINT32     enEnvelopeType;
    VOS_BOOL                        bTransFlag;
    SI_STK_ENVELOPE_CNFDATA_STRU    stCnfData;
}SI_STK_ENVELOPEDWON_CNF_STRU;

/*****************************************************************************
  15 函数声明
*****************************************************************************/
extern VOS_UINT32 SI_STK_EnvelopeData_Code(SI_STK_ENVELOPE_STRU *pstENStru,VOS_UINT32 *pulDataLen,VOS_UINT8 *pucData,VOS_UINT32 *pulDataOffset);

extern VOS_UINT32 SI_STK_EnvelopeRsp_Decode(SI_STK_ENVELOPE_TYPE_UINT32 enDataType,VOS_UINT32 ulDataLen,VOS_UINT8 *pucCmdData,SI_STK_ENVELOPE_RSP_STRU *pstRspData);

extern VOS_VOID SI_STK_EnvelopeRspDataFree(SI_STK_ENVELOPE_RSP_STRU *pstData);

extern VOS_UINT32 SI_STK_MenuSelection(MN_CLIENT_ID_T ClientId,MN_OPERATION_ID_T OpId,SI_STK_ENVELOPE_STRU *pstENStru);

extern VOS_UINT32 SI_STK_GetMainMenu(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId);

extern VOS_UINT32 SI_STK_GetSTKCommand(MN_CLIENT_ID_T ClientId,MN_OPERATION_ID_T OpId,SI_STK_CMD_TYPE CmdType);

extern VOS_UINT32 SI_STK_QuerySTKCommand(MN_CLIENT_ID_T ClientId,MN_OPERATION_ID_T OpId);

extern VOS_UINT32 SI_STK_TerminalResponse(MN_CLIENT_ID_T ClientId,MN_OPERATION_ID_T OpId,SI_STK_TERMINAL_RSP_STRU* pstTRStru);

extern VOS_UINT32 SI_STK_DataSendSimple(MN_CLIENT_ID_T ClientId,MN_OPERATION_ID_T OpId, SI_SEND_DATA_TYPE SendType,VOS_UINT32 ulDataLen,VOS_UINT8 *paucData);

extern VOS_UINT32 SI_STKDualIMSIChangeReq(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId);

extern VOS_VOID SI_STKGetCurImsiSign(VOS_UINT16 *pusDualIMSIEnable, VOS_UINT32 *pulCurImsiSign);

extern VOS_UINT32 SI_STKIsDualImsiSupport(VOS_VOID);

extern VOS_VOID SI_STK_PidMsgProc( PS_SI_MSG_STRU *pMsg );

extern VOS_UINT32 SI_STKEventCallback(SI_STK_EVENT_INFO_STRU *pEvent);

extern VOS_UINT32 SI_STKCallback(SI_STK_EVENT_INFO_STRU *pEvent);

extern VOS_VOID SI_STKCallBack_BroadCast(SI_STK_EVENT_INFO_STRU *pEvent);

extern VOS_UINT32 WuepsSTKPidInit(enum VOS_INIT_PHASE_DEFINE InitPhrase);

extern VOS_UINT32 SI_STK_CLSndTrMsg(VOS_UINT32 ulDataLen, VOS_UINT8 *pucData);

extern VOS_VOID SI_STK_CbpSetupEventListCmdSnd(VOS_VOID);

/*****************************************************************************
函 数 名  : SI_STK_SetUpCallConfirm
功能描述  : 用户回复是否允许发起呼叫
输入参数  : ulAction -- 用户回复结果
输出参数  : 无
返 回 值  : 执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2012年9月14日
  作    者  : j00168360
  修改内容  : Create
*****************************************************************************/
extern VOS_UINT32 SI_STK_SetUpCallConfirm(MN_CLIENT_ID_T ClientId, SI_STK_SETUPCALLCONFIRM_ENUM_UINT32 enAction);

/*****************************************************************************
函 数 名  : SI_STK_CCResultInd
功能描述  : 将MO CALL CONTROL的结果广播上报给AT
输入参数  : pstRspData--指向CALL CONTROL的解码后码流
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2012年09月14日
  作    者  : j00168360
  修改内容  : Create
*****************************************************************************/
extern VOS_VOID SI_STK_CCResultInd(SI_STK_ENVELOPE_RSP_STRU *pstRspData);

/*****************************************************************************
函 数 名  : SI_STK_SMSCtrlResultInd
功能描述  : 将MO SMS CONTROL的结果广播上报给AT
输入参数  : pstRspData--指向SMS CONTROL的解码后码流
输出参数  : 无
返 回 值  : 执行结果
History     :
1.日    期  : 2012年09月14日
  作    者  : j00168360
  修改内容  : Create
*****************************************************************************/
extern VOS_VOID SI_STK_SMSCtrlResultInd(SI_STK_ENVELOPE_RSP_STRU *pstRspData);

/*单编译接口声明*/
/*****************************************************************************
函 数 名  : SI_STK_EnvelopeRsp_Decode
功能描述  : STK功能ENVELOP回复数据解码
输入参数  : enModemID:Modem ID
            enDataType: 解码的信封命令数据类型
            ulDataLen:  需要解码的数据长度
            pucData:    需要解码的数据内容
输出参数  : pstRspData: 解码后的数据内容
返 回 值  : VOS_UINT32 函数执行结果
修订记录  :
1. 日    期   : 2013年5月27日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
extern VOS_UINT32 SI_STK_EnvelopeRsp_Decode_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    SI_STK_ENVELOPE_TYPE_UINT32         enDataType,
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucCmdData,
    SI_STK_ENVELOPE_RSP_STRU           *pstRspData);

/*****************************************************************************
函 数 名  : SI_STK_EnvelopeRspDataFree_Instance
功能描述  : STK功能ENVELOP回复数据解码数据内存释放函数
输入参数  : enModemID:Modem ID
输出参数  : pstRspData: 解码后的数据内容
返 回 值  : 无
修订记录  :
1. 日    期   : 2013年5月27日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
extern VOS_VOID SI_STK_EnvelopeRspDataFree_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    SI_STK_ENVELOPE_RSP_STRU           *pstData);

/*****************************************************************************
函 数 名  : SI_STK_CCResultInd_Instance
功能描述  : 将MO CALL CONTROL的结果广播上报给AT
输入参数  : enModemID --Modem ID
            pstRspData--指向CALL CONTROL的解码后码流
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年06月14日
  作    者  : zhuli
  修改内容  : Create
*****************************************************************************/
extern VOS_VOID SI_STK_CCResultInd_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    SI_STK_ENVELOPE_RSP_STRU           *pstRspData);

/*****************************************************************************
函 数 名  : SI_STK_SMSCtrlResultInd_Instance
功能描述  : 将MO SMS CONTROL的结果广播上报给AT
输入参数  : enModemID --Modem ID
            pstRspData--指向SMS CONTROL的解码后码流
输出参数  : 无
返 回 值  : 执行结果
History     :
1.日    期  : 2013年06月14日
  作    者  : zhuli
  修改内容  : Create
*****************************************************************************/
extern VOS_VOID SI_STK_SMSCtrlResultInd_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    SI_STK_ENVELOPE_RSP_STRU           *pstRspData);


#if ((TAF_OS_VER == TAF_WIN32) || (TAF_OS_VER == TAF_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of SiAppSim.h */





