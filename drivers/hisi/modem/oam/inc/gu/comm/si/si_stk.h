

/************************************************************************
Copyright   : 2005-2008, Huawei Tech. Co., Ltd.
File name   : SI_SIM.h
Author      : H59254
Version     : V200R001
Date        : 2008-10-18
Description : SIM卡的头文件
History     :
History     :
1.日    期  : 2008年10月18日
  作    者  : H59254
  修改内容  : Create
************************************************************************/
#ifndef __SI_STK_H__
#define __SI_STK_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#include "pamom.h"
#include "UsimmApi.h"
#endif

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#include "pamappom.h"
#endif

#include "msp_nvim.h"
#include "TafOamInterface.h"
#include "omnvinterface.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "AtOamInterface.h"
#include "MnErrorCode.h"
#include "Taf_MmiStrParse.h"
#include "TafNvInterface.h"
#include "NasStkInterface.h"
#include "msp_diag_comm.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "TafXsmsStkInterface.h"
#include "TafXsmsDecode.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/

typedef VOS_UINT32 (*TLV2DS)(VOS_UINT8 *pDes,VOS_UINT8 *pSrc);

typedef VOS_UINT32 (*DS2TLV)(VOS_UINT8 Tag,VOS_UINT8 *pDes,VOS_UINT8 *pSrc,VOS_UINT8 len);

#define STK_GEN_LOG_MODULE(Level) (/*lint -e1011 -e778*/DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(MAPS_STK_PID), DIAG_MODE_COMM, Level)/*lint +e1011 +e778*/)

#define STK_INFO_LOG(string)            (VOS_VOID)DIAG_LogReport(STK_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_STK_PID, __FILE__, __LINE__, "%s", string)
#define STK_NORMAL_LOG(string)          (VOS_VOID)DIAG_LogReport(STK_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_STK_PID, __FILE__, __LINE__, "%s", string)
#define STK_WARNING_LOG(string)         (VOS_VOID)DIAG_LogReport(STK_GEN_LOG_MODULE(PS_LOG_LEVEL_WARNING),MAPS_STK_PID, __FILE__, __LINE__, "%s", string)
#define STK_ERROR_LOG(string)           (VOS_VOID)DIAG_LogReport(STK_GEN_LOG_MODULE(PS_LOG_LEVEL_ERROR),MAPS_STK_PID, __FILE__, __LINE__, "%s", string)

#define STK_INFO_LOG1(string, para1)    (VOS_VOID)DIAG_LogReport(STK_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_STK_PID, __FILE__, __LINE__, "%s,%d", string, para1)
#define STK_NORMAL_LOG1(string, para1)  (VOS_VOID)DIAG_LogReport(STK_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_STK_PID, __FILE__, __LINE__, "%s,%d", string, para1)
#define STK_WARNING_LOG1(string, para1) (VOS_VOID)DIAG_LogReport(STK_GEN_LOG_MODULE(PS_LOG_LEVEL_WARNING),MAPS_STK_PID, __FILE__, __LINE__, "%s,%d", string, para1)
#define STK_ERROR_LOG1(string, para1)   (VOS_VOID)DIAG_LogReport(STK_GEN_LOG_MODULE(PS_LOG_LEVEL_ERROR),MAPS_STK_PID, __FILE__, __LINE__, "%s,%d", string, para1)

#define SI_SAT_OFFSET(A,b)              ((VOS_UINT16)(&(((A*)0)->b)))

#define SI_STK_GET_MCC(NUM)             (100 * ((NUM  % 1000 / 100 + 9) % 10) \
                                        + 10* ((NUM % 100 / 10 + 9) % 10) \
                                        + (NUM % 10 + 9) %10)

#define SI_STK_GET_MNC(NUM)             (10* ((NUM % 100 / 10 + 9) % 10) \
                                        + (NUM % 10 + 9) %10)

#define SI_TAGNOTFOUND                          (0xFFFFFFFF)

#define STK_DATA_TAG_MASK                       (0x80) /*按照协议,Data Tag的最高bit可以是1*/

#define STK_POROTECT_TIME_LEN                   (20)  /*默认20秒超时*/

#define STK_IND_TIME_LEN                        (5000)

#define STK_DURATION_MIN                        (0x00)
#define STK_DURATION_SEC                        (0x01)
#define STK_DURATION_TENTH_SEC                  (0x02)

#define STK_TIME_MANAGEMENT_START               (0x00)
#define STK_TIME_MANAGEMENT_DEACTIVE            (0x01)
#define STK_TIME_MANAGEMENT_GET_VALUE           (0x02)

#define STK_TIMER_MAX_NUM                       (9)

/*返回的TR数据长度，按照结果只有一个字节计算*/
#define STK_TERMINAL_RSP_LEN                    (12)

#define STK_LOCAL_INFO_2G                       (9)

#define STK_ENVELOPE_MAX_LEN                    (256)

#define STK_SMS_MAX_MSG_SEGMENT_NUM             (2)

#define STK_TIMER_SECOND_VALUE_MAX              (60)
#define STK_TIMER_MINUTE_VALUE_MAX              (60)
#define STK_TIMER_HOUR_VALUE_MAX                (17)

#define STK_PROVIDE_LOCAL_INFO_NAA              (0x00)
#define STK_PROVIDE_LOCAL_INFO_IMEI             (0x01)
#define STK_PROVIDE_LOCAL_INFO_NMR              (0x02)
#define STK_PROVIDE_LOCAL_INFO_TIME             (0x03)
#define STK_PROVIDE_LOCAL_INFO_LANGUAGE         (0x04)
#define STK_PROVIDE_LOCAL_INFO_RES_GSM          (0x05)
#define STK_PROVIDE_LOCAL_INFO_ACCESS_TECH      (0x06)
#define STK_PROVIDE_LOCAL_INFO_ESN              (0x07)
#define STK_PROVIDE_LOCAL_INFO_IMEISV           (0x08)
#define STK_PROVIDE_LOCAL_INFO_SEARCH_MODE      (0x09)
#define STK_PROVIDE_LOCAL_INFO_BATTERY_STATE    (0x0A)
#define STK_PROVIDE_LOCAL_INFO_MEID             (0x0B)
#define STK_PROVIDE_LOCAL_INFO_RES_3GPP         (0x0C)

#define STK_IMEI_LEN                            (14)
#define STK_IMEISV_LEN                          (16)
#define STK_IMEI_TYPE                           (0x0A)
#define STK_IMEISV_TYPE                         (0x03)

#define STK_SEND_SMS_OP_ID                      (0x00)
#define STK_SEND_SS_OP_ID                       (0x01)
#define STK_SEND_USSD_OP_ID                     (0x02)
#define STK_SETUP_CALL_OP_ID                    (0x03)
#define STK_SETUP_CALL_DTMF_OP_ID               (0x04)
#define STK_SEND_DTMF_OP_ID                     (0x05)

#define STK_NV_ENABLED                          (0x0101)

/*profile 特别bit*/
#define SI_STK_LOCALINFO_NETINFO                (30)
#define SI_STK_LOCALINFO_NMR                    (31)
#define SI_STK_GET_READER_STATUS                (51)
#define SI_STK_GET_READER_ID                    (52)
#define SI_STK_TIMER_MM_START	                (56)
#define SI_STK_TIMER_MM_STOP                    (57)
#define SI_STK_LOCALINFO_TIME                   (58)
#define SI_STK_CALL_CONTROL                     (63)
#define SI_STK_LOCALINFO_LANGUAGE               (67)
#define SI_STK_LOCALINFO_TA                     (68)
#define SI_STK_LOCALINFO_ACCESS                 (71)

#define STK_OPID_VALUE                          STK_SEND_SMS_OP_ID

/* NAS支持最大呼叫数 */
#define STK_CALL_MAX_NUM                        (7)

/* 定义parse字符 */
#define STK_PAUSE_CHAR                          (0x0c)

/* 挂断所有呼叫的ID */
#define STK_ALL_CALL_ID                         (0)

/* DURATION定时器默认时长，等待NAS回复CONNECT消息 */
#define STK_SETUP_CALL_DURATION_DEFAULT         (60)

/* 发送DTMF时暂停的时间长度，单位为MS */
#define STK_SEND_DTMF_PAUSE_TIME                (3000)

/* STK重试呼叫的最大次数 */
#define STK_RECALL_TIME_MAX						(3)


#define STK_TIMER_MANAGEMENT_TIMER_START(TimerId,Length)    VOS_StopRelTimer(&gstSTKTimer[TimerId].stTimer);\
                                                            VOS_StartRelTimer(&gstSTKTimer[TimerId].stTimer, MAPS_STK_PID,\
                                                                            Length, TimerId, 0, VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_5)

#define STK_TIMER_MANAGEMENT_TIMER_STOP(TimerId)            VOS_StopRelTimer(&gstSTKTimer[TimerId].stTimer)


#define STK_PROTECT_TIMER_START(ulLength)                   VOS_StartRelTimer(&gstSTKProtectTimer, MAPS_STK_PID,\
                                                                            ulLength*1000, STK_PROTECT_TIMER_NAME, 0,VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_5)

#define STK_PROTECT_TIMER_STOP                              VOS_StopRelTimer(&gstSTKProtectTimer)

#define STK_NMR_TIMER_START(ulLength)                       VOS_StartRelTimer(&gstSTKNMRTimer, MAPS_STK_PID,\
                                                                            ulLength*1000, STK_NMR_TIMER_NAME, 0, VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_5)

#define STK_NMR_TIMER_STOP                                  VOS_StopRelTimer(&gstSTKNMRTimer)

/* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, begin */
#define STK_GETTA_TIMER_START                               VOS_StartRelTimer(&gstSTKGetTATimer, MAPS_STK_PID,\
                                                                            5000, STK_GETTA_TIMER_NAME, 0,VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_5)

#define STK_GETTA_TIMER_STOP                                VOS_StopRelTimer(&gstSTKGetTATimer)
/* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, end */

#define STK_IND_TIMER_START(ulLength)                       VOS_StartRelTimer(&gstSTKINDTimer, MAPS_STK_PID,\
                                                                            ulLength, STK_IND_TIMER_NAME, 0,VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_5)

#define STK_IND_TIMER_STOP                                  VOS_StopRelTimer(&gstSTKINDTimer)

#define STK_REFRESH_CNF_TIMER_START(ulLength)               VOS_StartRelTimer(&gstSTKRefreshCnfTimer, MAPS_STK_PID,\
                                                                            ulLength, STK_REFRESH_TIMER_NAME, 0,VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_5)

#define STK_REFRESH_CNF_TIMER_STOP                          VOS_StopRelTimer(&gstSTKRefreshCnfTimer)

#define STK_SETUP_CALL_DURATION_TIMER_START(ulLength)       VOS_StartRelTimer(&gstSTKSetupCallDurationTimer, MAPS_STK_PID,\
                                                                            ulLength, STK_SETUP_CALL_DURATION_TIMER_NAME, 0,VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_10)

#define STK_SETUP_CALL_DURATION_TIMER_STOP                  VOS_StopRelTimer(&gstSTKSetupCallDurationTimer)

#define STK_DTMF_PAUSE_TIMER_START(ulLength)                VOS_StartRelTimer(&gstSTKDtmfPauseTimer, MAPS_STK_PID,\
                                                                            ulLength, STK_DTMF_PAUSE_TIMER_NAME, 0,VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_10)

#define STK_RESEND_TIMER_START(TimerId, TimerName, Length)  (VOS_VOID)VOS_StopRelTimer(TimerId);\
                                                            (VOS_VOID)VOS_StartRelTimer(TimerId, MAPS_STK_PID,\
                                                                            Length*1000, TimerName, 0, VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_5)

#define STK_RESEND_TIMER_STOP(TimerId)            VOS_StopRelTimer(TimerId)



#define STK_BCD2HEX(x) ((VOS_UINT8)((VOS_UINT8)(((x) & 0xF0)>>4) + (VOS_UINT8)(((x) & 0x0F)*0x0A)))

#define STK_HEX2BCD(x) (((x) < 10)?(VOS_UINT8)((x)<<4):((VOS_UINT8)((VOS_UINT8)(((x)/10) & 0x0F) + (VOS_UINT8)(((x)%10)<<4))))

#define STK_ARRAYSIZE(array)                (sizeof(array)/sizeof(array[0]))

/* 检查TAF回复的PS_USIM_ENVELOPE_CNF_STRU消息中，ucDataType的合法性 */
#define STK_IS_TAF_ENVELOPE_CNF_DATATYPE_VALID(ucDataType)   ( (SI_STK_ENVELOPE_PPDOWN == ucDataType)   \
                                                             ||(SI_STK_ENVELOPE_CBDOWN == ucDataType)   \
                                                             ||(SI_STK_ENVELOPE_CALLCRTL == ucDataType) \
                                                             ||(SI_STK_ENVELOPE_SMSCRTL == ucDataType)  \
                                                             ||(SI_STK_ENVELOPE_USSDDOWN == ucDataType)  )

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
enum SI_STK_TIMERNAME
{
    STK_PROTECT_TIMER_NAME                  = 0,
    STK_TIMER_MANAGEMENT_TIMER1             = 1,
    STK_TIMER_MANAGEMENT_TIMER2             = 2,
    STK_TIMER_MANAGEMENT_TIMER3             = 3,
    STK_TIMER_MANAGEMENT_TIMER4             = 4,
    STK_TIMER_MANAGEMENT_TIMER5             = 5,
    STK_TIMER_MANAGEMENT_TIMER6             = 6,
    STK_TIMER_MANAGEMENT_TIMER7             = 7,
    STK_TIMER_MANAGEMENT_TIMER8             = 8,
    STK_IND_TIMER_NAME                      = 9,
    STK_REFRESH_TIMER_NAME                  = 10,
    STK_GETTA_TIMER_NAME                    = 11,
    STK_SETUP_CALL_DURATION_TIMER_NAME      = 12,
    STK_DTMF_PAUSE_TIMER_NAME               = 13,
    STK_NMR_TIMER_NAME                      = 14,
    STK_LOCIEVENT_TIMER_NAME                = 15,
    STK_ACCEVENT_TIMER_NAME                 = 16,
    SI_STK_TIMERNAME_BUTT
};
typedef VOS_UINT32 SI_STK_TIMERNAME_UINT32;

enum SI_STK_CMD_PROC_STATUS
{
    SI_STK_NORMAL_CNF                = 0,   /*正常回复*/
    SI_STK_WAITING_CNF               = 1,   /*等待回复*/
    SI_STK_TIMEOUT_CNF               = 2,   /*超时回复*/
    SI_STK_BUTT
};
typedef VOS_UINT32 SI_STK_CMD_PROC_STATUS_UINT32;

enum SI_STK_TAG_TYPE
{
    SI_TAG_TYPE_NULL                = 0,   /*数据结构不确定*/
    SI_TAG_TYPE_LV                  = 1,   /*LV 数据结构*/
    SI_TAG_TYPE_TLV                 = 2,   /*TLV数据结构*/
    SI_TAG_TYPE_V                   = 3,   /*V 数据结构*/
    SI_TAG_BUTT
};
typedef VOS_UINT8 SI_STK_TAG_TYPE_UINT8;

enum SI_DECODE_RESULT
{
    SI_STK_OK                       = COMMAND_PERFORMED_SUCCESSFULLY,
    SI_STK_CMDEND                   = PROACTIVE_UICC_SESSION_TERMINATED_BY_THE_USER,
    SI_STK_HANDLEERROR              = TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND,
    SI_STK_NOTSUPPORT               = COMMAND_BEYOND_TERMINALS_CAPABILITIES,
    SI_STK_TYPE_ERROR               = COMMAND_TYPE_NOT_UNDERSTOOD_BY_TERMINAL,
    SI_STK_DATA_ERROR               = COMMAND_DATA_NOT_UNDERSTOOD_BY_TERMINAL,
    SI_STK_OK_WAITRP                = 0x40,
    SI_STK_NORP                     = 0x41,
    SI_DECODE_RESULT_BUTT
};

enum SI_CODEDATA_TYPE
{
    SI_CODE_TR_DATA                 = 0x00,
    SI_CODE_EVENT_DATA              = 0x01,
    SI_CODE_ENVELOPE_DATA           = 0x02,
    SI_CODE_DATA_BUTT
};
typedef VOS_UINT32 SI_CODEDATA_TYPE_UINT32;

enum SI_STK_DATA_TAG
{
    COMMAND_DETAILS_TAG             = 0x01,
    DEVICE_IDENTITY_TAG             = 0x02,
    RESULT_TAG                      = 0x03,
    DURATION_TAG                    = 0x04,
    ALPHA_IDENTIFIER_TAG            = 0x05,
    ADDRESS_TAG                     = 0x06,
    CAP_CFG_PARA_TAG                = 0x07,
    SUBADDRESS_TAG                  = 0x08,
    SS_STRING_TAG                   = 0x09,
    USSD_STRING_TAG                 = 0x0A,
    SMS_TPDU_TAG                    = 0x0B,
    CELL_BROADCAST_PAGE_TAG         = 0x0C,
    TEXT_STRING_TAG                 = 0x0D,
    TONE_TAG                        = 0x0E,
    ITEM_TAG                        = 0x0F,
    ITEM_IDENTIFIER_TAG             = 0x10,
    RESPONSE_LENGTH_TAG             = 0x11,
    FILE_LIST_TAG                   = 0x12,
    LOCATION_INFORMATION_TAG        = 0x13,
    IMEI_TAG                        = 0x14,
    HELP_REQUEST_TAG                = 0x15,
    NET_MEASUREMENT_RESULTS_TAG     = 0x16,
    DEFAULT_TEXT_TAG                = 0x17,
    MS_NEXTACTION_INDICATOR_TAG     = 0x18,
    EVENT_LIST_TAG                  = 0x19,
    CAUSE_TAG                       = 0x1A,
    LOCATION_STATUS_TAG             = 0x1B,
    TRANSACTION_IDENTIFIER_TAG      = 0x1C,
    BCCH_CHANNEL_LIST_TAG           = 0x1D,
    ICON_IDENTIFIER_TAG             = 0x1E,
    ITEM_ICONID_LIST_TAG            = 0x1F,
    CARD_READER_STATUS_TAG          = 0x20,
    CARD_ATR_TAG                    = 0x21,
    C_APDU_TAG                      = 0x22,
    R_APDU_TAG                      = 0x23,
    TIMER_IDENTIFIER_TAG            = 0x24,
    TIMER_VALUE_TAG                 = 0x25,
    DATETIME_AND_TIMEZONE_TAG       = 0x26,
    CALL_CONTROL_REQACTION_TAG      = 0x27,
    AT_COMMAND_TAG                  = 0x28,
    AT_RESPONSE_TAG                 = 0x29,
    BC_REPEAT_INDICATOR_TAG         = 0x2A,
    IMMEDIATE_RESPONSE_TAG          = 0x2B,
    DTMF_STRING_TAG                 = 0x2C,
    LANGUAGE_TAG                    = 0x2D,
    TIMING_ADVANCE_TAG              = 0x2E,
    AID_TAG                         = 0x2F,
    BROWSER_IDENTITY_TAG            = 0x30,
    URL_TAG                         = 0x31,
    BEARER_TAG                      = 0x32,
    PROVISIONING_REFFILE_TAG        = 0x33,
    BROWSER_TERMINATION_CAUSE_TAG   = 0x34,
    BEARER_DESCRIPTION_TAG          = 0x35,
    CHANNEL_DATA_TAG                = 0x36,
    CHANNEL_DATA_LENGTH_TAG         = 0x37,
    CHANNEL_STATUS_TAG              = 0x38,
    BUFFER_SIZE_TAG                 = 0x39,
    CARD_READER_IDENTIFIER_TAG      = 0x3A,
    RFU_3B                          = 0x3B,
    UICC_TERMINAL_TRAN_LEVEL_TAG    = 0x3C,
    RFU_3D                          = 0x3D,
    OTHER_ADDR_TAG                  = 0x3E,
    ACCESS_TECHNOLOGY_TAG           = 0x3F,
    DISPLAY_PARAMETERS_TAG          = 0x40,
    SERVICE_RECORD_TAG              = 0x41,
    DEVICE_FILTER_TAG               = 0x42,
    SERVICE_SEARCH_TAG              = 0x43,
    ATTRIBUTE_INFORMATION_TAG       = 0x44,
    SERVICE_AVAILABILITY_TAG        = 0x45,
    ESN_TAG                         = 0x46,
    NETWORK_ACCESS_NAME_TAG         = 0x47,
    CDMA_SMS_TPDU                   = 0x48,
    REMOTE_ENTITY_ADDRESS_TAG       = 0x49,
    I_WLAN_ID_TAG                   = 0x4A,
    I_WLAN_ACCESS_STATUS_TAG        = 0x4B,
    RFU_4C                          = 0x4C,
    RFU_4D                          = 0x4D,
    RFU_4E                          = 0x4E,
    RFU_4F                          = 0x4F,
    TEXT_ATTRIBUTE_TAG              = 0x50,
    ITEM_TEXT_ATTRIBUTE_LIST_TAG    = 0x51,
    PDP_CONTEXT_ACTIVATION_PAR_TAG  = 0x52,
    RFU_53                          = 0x53,
    RFU_54                          = 0x54,
    CSG_CELL_SELEC_STATUS_TAG       = 0x55,
    CSG_ID_TAG                      = 0x56,
    HNB_NAME_TAG                    = 0x57,
    RFU_58                          = 0x58,
    RFU_59                          = 0x59,
    RFU_5A                          = 0x5A,
    RFU_5B                          = 0x5B,
    RFU_5C                          = 0x5C,
    RFU_5D                          = 0x5D,
    RFU_5E                          = 0x5E,
    RFU_5F                          = 0x5F,
    RFU_60                          = 0x60,
    RFU_61                          = 0x61,
    IMEISV_TAG                      = 0x62,
    BATTERY_STATE_TAG               = 0x63,
    BROWSING_STATUS_TAG             = 0x64,
    NETWORK_SEARCH_MODE_TAG         = 0x65,
    FRAME_LAYOUT_TAG                = 0x66,
    FRAMES_INFORMATION_TAG          = 0x67,
    FRAME_IDENTIFIER_TAG            = 0x68,
    UTRAN_MEASUREMENT_TAG           = 0x69,
    MMS_REFERENCE_TAG               = 0x6A,
    MMS_IDENTIFIER_TAG              = 0x6B,
    MMS_TRANSFER_STATUS_TAG         = 0x6C,
    MEID_TAG                        = 0x6D,
    MMS_CONTENT_ID_TAG              = 0x6E,
    MMS_NOTIFICATION_TAG            = 0x6F,
    LAST_ENVELOPE_TAG               = 0x70,
    RFU_62                          = 0x71,
    PLMNWACT_LIST_TAG               = 0x72,
    ROUTING_AREA_INFO_TAG           = 0x73,
    ATTACH_TYPE_TAG                 = 0x74,
    REJETION_CAUSE_CODE_TAG         = 0x75,
    GEOGRAPH_LOCAL_PARA_TAG         = 0x76,
    GAD_SHAPES_TAG                  = 0x77,
    NMEA_SENTENCE_TAG               = 0x78,
    PLMN_LIST_TAG                   = 0x79,
    RFU_7A                          = 0x7A,
    RFU_7B                          = 0x7B,
    EPSPDN_ACTIVE_PARA_TAG          = 0x7C,
    TRACKING_AREA_ID_TAG            = 0x7D,
    CSG_ID_LIST_TAG                 = 0x7E,
    SI_STK_TAG_BUTT
};

enum SI_STK_LOCK_ENUM
{
    SI_STK_PROUNLOCK                = 0x00,
    SI_STK_PROLOCK                  = 0x01,
    SI_STK_LOCK_BUTT
};
typedef VOS_UINT32 SI_STK_LOCK_ENUM_UINT32;

enum SI_STK_TIMERSTATE_ENUM
{
    SI_STK_TIMERSTOP                = 0x00,
    SI_STK_TIMERRUN                 = 0x01,
    SI_STK_TIMERBUTT
};
typedef VOS_UINT32 SI_STK_TIMERSTATE_ENUM_UINT32;

enum SI_STK_STR_CHANGEMODE_ENUM
{
    SI_STK_STR_CHANGEBIG            = 0x00,
    SI_STK_STR_CHANGESMALL          = 0x01,
    SI_STK_STR_CHANGE_BUTT
};
typedef VOS_UINT32 SI_STK_STR_CHANGEMODE_ENUM_UINT32;


/* 沃达丰Dual IMSI 切换定制需求 */
enum SI_STK_IMSICHG_STATE_ENUM
{
    SI_STK_IMSICHG_NULL             = 0x00,
    SI_STK_IMSICHG_SELECT_ITEM      = 0x01,
    SI_STK_IMSICHG_REFRESH          = 0x02,
    SI_STK_IMSICHG_STATE_BUTT
};
typedef VOS_UINT32 SI_STK_IMSICHG_STATE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : SI_STK_DTMF_SEND_ENUM_UINT32
 枚举说明  : STK模块记录的DTMF SEND状态
*****************************************************************************/
enum SI_STK_DTMF_SEND_ENUM
{
    SI_STK_DTMF_SEND_OK             = 0,    /* 当前发送数据成功 */
    SI_STK_DTMF_SEND_ERR            = 1,    /* 当前发送数据失败 */
    SI_STK_DTMF_SEND_FINISH         = 2,    /* 当前发送数据完成 */
    SI_STK_DTMF_SEND_REJECT         = 3,    /* 当前发送数据被拒 */
    SI_STK_DTMF_SEND_BUTT,
};
typedef VOS_UINT32 SI_STK_DTMF_SEND_ENUM_UINT32;

/*****************************************************************************
 枚举名    : SI_STK_CALL_STATUS_ENUM
 枚举说明  : STK模块记录的当前呼叫状态
*****************************************************************************/
enum SI_STK_CALL_ID_STATUS_ENUM
{
    SI_STK_CALL_ID_STATUS_IDLE          =   0x5A,           /* 当前处于空闲状态 */
    SI_STK_CALL_ID_STATUS_BUSY          =   0xA5,           /* 当前处于呼叫状态(包括DTMF发送过程中) */
    SI_STK_CALL_ID_STATUS_BUTT,
};
typedef VOS_UINT8 SI_STK_CALL_ID_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : SI_STK_CALL_STATUS_ENUM
 枚举说明  : STK模块记录的当前呼叫状态
*****************************************************************************/
enum SI_STK_CALL_STATUS_ENUM
{
    SI_STK_CALL_STATUS_WAIT_IDLE        =   0,              /* 当前处于空闲状态,当前无SETUP CALL主动命令，不处理NAS消息 */
    SI_STK_CALL_STATUS_WAIT_CONNECT     =   1,              /* 当前处于等待CONNECT消息 */
    SI_STK_CALL_STATUS_WAIT_DISCONNECT  =   2,              /* 当前处于等待DISCONNECT消息 */
    SI_STK_CALL_STATUS_WAIT_HOLD        =   3,              /* 当前处于HOLD消息 */
    SI_STK_CALL_STATUS_SEND_DTMF        =   4,              /* 当前处于发送DTMF过程中 */
    SI_STK_CALL_STATUS_WAIT_DURTIMEROUT = 	5,              /* 当前处于等待Duration超时过程中 */
    SI_STK_CALL_STATUS_BUTT,
};
typedef VOS_UINT32 SI_STK_CALL_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : SI_STK_SETUP_CALL_COMMAND_QUALIFIER
 枚举说明  : SETUP CALL主动命令的CQ值
*****************************************************************************/
enum SI_STK_SETUP_CALL_COMMAND_QUALIFIER_ENUM
{
    SI_STK_SETUP_CALL_ONLY_NOT_BUSY_ON_ANOTHER_CALL         =   0,
    SI_STK_SETUP_CALL_ONLY_NOT_BUSY_ON_ANOTHER_CALL_REDIAL  =   1,
    SI_STK_SETUP_CALL_PUTTING_ALL_OTHER_CALL_ON_HOLD        =   2,
    SI_STK_SETUP_CALL_PUTTING_ALL_OTHER_CALL_ON_HOLD_REDIAL =   3,
    SI_STK_SETUP_CALL_DISCONNECT_ALL_OTHER_CALL             =   4,
    SI_STK_SETUP_CALL_DISCONNECT_ALL_OTHER_CALL_REDIAL      =   5,
    SI_STK_SETUP_CALL_BUTT,
};
typedef VOS_UINT8 SI_STK_SETUP_CALL_COMMAND_QUALIFIER_ENUM_UINT8;

/*****************************************************************************
 枚举名    : SI_STK_HOOK_MSG_NAME_ENUM_UINT32
 结构说明  : 钩包消息类型
 1.日    期: 2013年7月12日
   作    者: H59254
   修改内容: 新增
*****************************************************************************/
enum SI_STK_HOOK_MSG_NAME_ENUM
{
     STK_TAF_CS_SERVICE_STATUS          = 0xFF00,    /* CS服务状态勾包 */
     STK_TAF_CBS_DCS                    = 0xFF01,    /* USSD DCS编码钩包 */

};
typedef VOS_UINT32 SI_STK_HOOK_MSG_NAME_ENUM_UINT32;

/*****************************************************************************
 枚举名    : SI_STK_TEXT_STRING_DCS_ENUM_UINT8
 结构说明  : TEXT STRING数据结构的编码方式
 1.日    期: 2013年7月12日
   作    者: H59254
   修改内容: 新增
*****************************************************************************/
enum SI_STK_TEXT_STRING_DCS_ENUM
{
     SI_STK_TEXT_STRING_DCS_7BIT        = 0x00,
     SI_STK_TEXT_STRING_DCS_8BIT        = 0x04,
     SI_STK_TEXT_STRING_DCS_UCS         = 0x08,
     SI_STK_TEXT_STRING_DCS_BUTT
};
typedef VOS_UINT8 SI_STK_TEXT_STRING_DCS_ENUM_UINT8;

/*C+L新增，电信要求Event需要能够重发，仅为此项目专用，不能扩展 */
enum SI_STK_ENVELOPE_RESENT_FLAG
{
    SI_STK_ENVELOPE_SENT_ONETIME        = 0,
    SI_STK_ENVELOPE_LOCI_RESEND         = 1,    /*本地事件需要重发*/
    SI_STK_ENVELOPE_ACC_RESEND          = 2,    /*接入技术改变需要重发*/
    SI_STK_ENVELOPE_RESENT_BUTT
};
typedef VOS_UINT32 SI_STK_ENVELOPE_RESENT_FLAG_UINT32;

enum SI_STK_CALLSTATE_FLAG
{
    SI_STK_CALLSTATE_OFF                = 0x0,
    SI_STK_CALLSTATE_ON                 = 0xAA,
    SI_STK_CALLSTATE_BUTT
};
typedef VOS_UINT8 SI_STK_CALLSTATE_FLAG_UINT8;

/*****************************************************************************
  4 单一数据结构定义
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulLen;
    VOS_UINT8                       *pValue;
}SI_SAT_LV_STRU;

typedef struct
{
    VOS_UINT8                       ucTag;
    VOS_UINT8                       ucLen;
    VOS_UINT8                       aucRsv[2];
    VOS_UINT8                       *pValue;
}SI_SAT_TLV_STRU;

typedef struct
{
    VOS_UINT32                      ulOpInfo;
    VOS_UINT8                       aucDecode[500];
}SI_SAT_COMMDATA_STRU;

typedef struct
{
    VOS_UINT32                      ulSenderPID;
    SI_STK_REQMSG_ENUM_UINT32       enSTKEventType;
    SI_STK_LOCK_ENUM_UINT32         enSTKLock;
    VOS_UINT16                      usClientID;
    VOS_UINT8                       ucOpID;
    VOS_UINT8                       ucReserved;
}SI_STK_REQ_UINT_STRU;

typedef struct
{
    VOS_UINT8                       ucUsatTag;
    VOS_UINT8                       aucReserved[3];
    SI_STK_COMMAND_DETAILS_STRU     CmdDetail;
    SI_STK_DEVICE_IDENTITIES_STRU   CmdDevice;
    SI_STK_SET_UP_MENU_STRU         stSetUpMenu;
}SI_SAT_SetUpMenu_DATA_STRU;

typedef struct
{
    VOS_UINT8                       ucOpId;
    VOS_UINT8                       ucCallId;
    VOS_UINT8                       aucRsv[2];
    VOS_UINT32                      ulDtmfLen;
    VOS_UINT32                      ulCurDtmfPtr;
    SI_CHAR                         acDtfm[512];
}SI_SAT_DTMF_DATA_STRU;

typedef struct
{
    VOS_UINT16                       usCmdType;
    VOS_UINT16                       usBitNum;
}SI_STK_CMD_PROFILE_CFG_STRU;

typedef struct
{
    VOS_UINT8                       ucDataTag;  /*用于存放Tag的值*/
    SI_STK_TAG_TYPE_UINT8           ucTagType;  /*用于指示Tag的编解码类型*/
    VOS_UINT8                       ucSTRULen;  /*用于表明数据结构的大小*/
    VOS_UINT8                       ucValueLen; /*用于指明当前V型数据实际大小*/
}SI_STK_DATADECODE_STRU;

typedef struct
{
    VOS_UINT32                      ulCmdType;   /*存放STK命令的类型*/
    VOS_UINT32                      ulTagLen;    /*存放编解码的列表长度*/
    VOS_UINT8                       *pucTagList; /*存放编解码列表地址*/
}SI_STK_TAGLIST_STRU;

/*****************************************************************************
 结构名    : SI_STK_CALL_STATUS_STRU
 结构说明  : STK模块呼叫状态表结构
*****************************************************************************/
typedef struct
{
    MN_CALL_ID_T                        callId;     /* 呼叫ID */
    SI_STK_CALL_ID_STATUS_ENUM_UINT8    enStatus;   /* 呼叫状态 */
}SI_STK_CALL_STATUS_STRU;

/*****************************************************************************
 结构名    : SI_STK_SETUP_CALL_DTMF_INFO_STRU
 结构说明  : STK模块SETUP CALL中DTMF控制结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          *pucDtmfCharacter;           /* DTMF字符串 */
    VOS_UINT32                          ulDtmfCharacterRemain;      /* 待发送的DTMF字符串 */
    VOS_UINT32                          ulDtmfCharacterCurrSnd;     /* 当前发送DTMF字符 */
}SI_STK_SETUP_CALL_DTMF_INFO_STRU;

/*****************************************************************************
 结构名    : SI_STK_SETUP_CALL_CTRL_STRU
 结构说明  : STK模块呼叫控制结构
*****************************************************************************/
typedef struct
{
    SI_STK_CALL_STATUS_ENUM_UINT32      enCallStatus;                                       /* SETUP CALL主动命令处理状态 */
    SI_STK_CALL_STATUS_STRU             astStkCallStatusTable[STK_CALL_MAX_NUM];            /* STK模块呼叫状态表 */
    MN_CALL_ID_T                        ucSetupCallId;                                      /* SETUP CALL发起呼叫的ID，由NAS分配 */
    VOS_UINT8                           ucRecallTime;                                       /* 重新呼叫的次数 */
}SI_STK_SETUP_CALL_CTRL_STRU;

/*****************************************************************************
 结构名    : SI_STK_CBP_SETUP_EVENT_LIST_STRU
 结构说明  : L+C共SIM卡功能保存EVENT LIST
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulProactiveCmdLen;
    VOS_UINT8                          *pucCmd;
}SI_STK_CBP_SETUP_EVENT_LIST_STRU;

typedef VOS_UINT32 (*pfSATCmdDecode)(VOS_UINT8  *pucCmd, VOS_UINT32 ulCmdType, SI_SAT_COMMDATA_STRU* pstResult);

typedef VOS_UINT32 (*pfSATCmdPro)(SI_STK_DATA_INFO_STRU *pEvent);

typedef struct
{
    SI_STK_CMD_TYPE                 ulCmdType;  /*处理消息类型*/
    pfSATCmdDecode                  pfDecodeFun;/*对应解码函数*/
    pfSATCmdPro                     pfProcFun;  /*对应处理函数*/
}SI_STK_CMDHANDLE_LIST_STRU;

typedef struct
{
    SI_STK_TIMERSTATE_ENUM_UINT32   enTimerState;
    HTIMER                          stTimer;
    VOS_UINT8                       ucHour;
    VOS_UINT8                       ucMin;
    VOS_UINT8                       ucSec;
    VOS_UINT8                       Reserve;
}SI_STK_TIMER_STRU;


typedef struct
{
    SI_STK_COMMAND_DETAILS_STRU     stCmdDetail;
    SI_STK_DEVICE_IDENTITIES_STRU   CmdDevice;
}SI_STK_PROACTIVE_CMD_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                      MsgName;
    SI_CLIENT_ID_T                  ClientId;
    VOS_UINT8                       OpId;
    VOS_UINT8                       Rsv;
    SI_STK_CMD_TYPE                 SatType;
    VOS_UINT32                      Datalen;
    VOS_UINT8                       Data[8];
}SI_STK_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                      ulMsgName;
    VOS_UINT8                       aucPWD[4];
}SI_STK_SS_PWD_REQ_STRU;

/* 沃达丰Dual IMSI 切换定制需求 */
typedef struct
{
    SI_STK_IMSICHG_STATE_ENUM_UINT32 enIMSIChgState;   /* 沃达丰IMSI切换定制需求状态记录 */
    VOS_UINT32                       ulCurImsiSign;    /* 取值0,1，与两个IMSI相对应 */
    VOS_UINT8                        aucOldImsi[9];    /* 切换前的IMSI */
    VOS_UINT8                        ucOldItemId;      /* 上一次选择的ITEM ID */
    VOS_UINT8                        ucTryFlag;        /* 记录是否已尝试过一次切换 */
    VOS_UINT8                        ucCycleFlag;      /* 标记是否在状态机中轮转 */
}SI_STK_IMSICHG_CTRL_STRU;

typedef  VOS_UINT32 (*STKIMSIPROC)(PS_SI_MSG_STRU *pMsg);

/* IMSI 切换定制需求状态机结构 */
typedef struct
{
    SI_STK_IMSICHG_STATE_ENUM_UINT32 enIMSIChgState;   /* 沃达丰IMSI切换定制需求状态记录 */
    STKIMSIPROC                      pIMSIChgProc;     /* 沃达丰IMSI切换定制需求对应状态处理函数 */
}SI_STK_IMSICHG_PROC_STRU;

/* 缓存下发的Envelope命令 */
typedef struct
{
    VOS_UINT32                       ulCmdLen;        /* Envelope命令长度 */
    VOS_UINT8                        aucCmdData[SI_STK_DATA_MAX_LEN]; /* Envelope命令内容 */
}SI_STK_ENVELOPE_CMD_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                      ulMsgName;
    VOS_UINT8                       aucData[4];
}SI_STK_ATCNF_MSG_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                      ulMsgName;
    VOS_UINT16                       usClientId;
    VOS_UINT8                       ucOpId;
    VOS_UINT8                       ucValue;
    VOS_UINT8                       aucData[4];
}SI_STK_TAF_SENDMSG_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                      ulMsgId;
    MN_MSG_EVENT_ENUM_U32           enEventType;
    VOS_UINT8                       aucEvent[4];
}SI_STK_TAFCNF_MSG_STRU;

/* 内部事件记录结构声明*/
typedef struct
{
    VOS_UINT32                      OP_MTCall:1;
    VOS_UINT32                      OP_CallConnect:1;
    VOS_UINT32                      OP_CallDisconnet:1;
    VOS_UINT32                      OP_LociStatus:1;
    VOS_UINT32                      OP_AccChange:1;
    VOS_UINT32                      OP_NetSearchChg:1;
    VOS_UINT32                      OP_NetRej:1;
    VOS_UINT32                      OP_Reserved:25;
}SI_STK_EVENT_STATE_STRU;

typedef struct
{
    MSG_HEADER_STRU                  MsgHeader;
    VOS_UINT32                       ulCsServiceStatus;
}STK_CS_SERVICE_STRU;

/*****************************************************************************
 枚举名    : STK_CBS_DCS_STRU
 结构说明  : NAS DCS解码函数钩包函数
 1.日    期: 2013年7月12日
   作    者: H59254
   修改内容: 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucInputDcs;
    VOS_UINT8                           ucRsv;
    VOS_UINT16                          usStringLen;
    MN_MSG_CBDCS_CODE_STRU              stCbDcs;
    VOS_UINT8                           aucString[4];
}STK_CBS_DCS_STRU;

typedef struct
{
    NAS_STK_UPDATE_TYPE_ENUM_UINT8          enOrigType;     /* MM子层传递给STK的原始type */
    SI_STK_UPDATE_ATTACH_TYPE_ENUM_UINT8    enDestType;     /* 根据31111 8.92  Update/Attach Type，原始type所映射到的目的type */
    VOS_UINT16                              usRsv;
}STK_UPDATA_ATTACH_TYPE_TRANSFER_STRU;

typedef struct
{
    HTIMER                                  stSTKResendTimer;
    VOS_UINT32                              ulSTKResendCounter;
    VOS_UINT32                              ulDataLen;
    VOS_UINT8                               aucData[STK_ENVELOPE_MAX_LEN];
}STK_EVENTDATA_RESEND_STRU;

/*****************************************************************************
 结构名    : SI_STK_CARDINFO_STRU
 结构说明  : STK模块保存USIM卡信息数据结构
*****************************************************************************/
typedef struct
{
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enPhyType;
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType;
    USIMM_CARD_SERVIC_ENUM_UINT32       enSvcStatus;
}SI_STK_CARDINFO_STRU;

typedef struct
{
    VOS_UINT32                          ulReqFlag;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           aucData[SI_STK_DATA_MAX_LEN];
}SI_STK_FLAGLVDATA_STRU;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
typedef struct
{
    VOS_UINT32                          ulIsPressNeed;
    VOS_UINT32                          ulSmsNum;
    VOS_UINT16                          usUserDataStartByte;
    VOS_UINT16                          usUserDataLen;
    TAF_XSMS_BD_MSG_USER_DATA_STRU      stUserData;
}SI_STK_CDMA_SMS_CTRL_PARA_STRU;
#endif

typedef struct
{
    SI_STK_CALLSTATE_FLAG_UINT8         enCSCallState;
    SI_STK_CALLSTATE_FLAG_UINT8         enPSCallState;
    VOS_UINT16                          usRsv;
}SI_STK_CALLSTATE_STRU;

/*****************************************************************************
  6 全局变量声明
*****************************************************************************/
extern VOS_UINT8                        g_ucSendSSType;

extern VOS_UINT8                        g_ucSendMsgNum;

extern VOS_UINT8                        g_ucReceCBNum;

extern SI_STK_DATA_INFO_STRU            gstUsatCmdDecode;

extern HTIMER                           gstSTKProtectTimer;

/* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, begin */
extern HTIMER                           gstSTKGetTATimer;
/* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, end */

extern HTIMER                           gstSTKINDTimer;

extern HTIMER                           gstSTKRefreshCnfTimer;

extern HTIMER                           gstSTKSetupCallDurationTimer;

extern HTIMER                           gstSTKDtmfPauseTimer;

extern HTIMER                           gstSTKNMRTimer;

extern VOS_UINT8                        gucSTKRefreshQua;

extern USIMM_STK_CFG_STRU               g_stSTKProfileContent;

extern SI_STK_REQ_UINT_STRU             gstSTKCtrlStru;

extern SI_STK_TIMER_STRU                gstSTKTimer[STK_TIMER_MAX_NUM];

extern SI_SAT_SetUpMenu_DATA_STRU       gstSetUpMenuData;

extern SI_STK_IMSICHG_CTRL_STRU         gstSTKIMSIChgCtrl;/* IMSI切换控制变量 */

extern SI_STK_IMSICHG_MATCH_STRU        gstSTKIMSIMatch; /* NV项读出的IMSI切换匹配码流 */

extern SI_STK_ENVELOPE_CMD_STRU         gstSTKEnvelopeCmd; /* 缓存Envelope命令 */

extern VOS_SEM                          gulSTKApiSmId;

extern SI_STK_TAGLIST_STRU              gastSTKDecodeList[24];

extern SI_STK_TAGLIST_STRU              gastRespCodeList[8];

extern SI_STK_TAGLIST_STRU              gastEventCodeList[16];

extern SI_STK_TAGLIST_STRU              gastEnvelopeList[7];

extern SI_STK_TAGLIST_STRU              gastEnvelopeDecodeList[2];

extern SI_STK_CMD_PROFILE_CFG_STRU      gastSTKCmdProfileCfg[31];

extern SI_STK_CMD_PROFILE_CFG_STRU      gastSTKEventProfileCfg[15];

extern VOS_UINT16                       gusSTKSMSIndEnable;

extern VOS_UINT8                        *g_pucSTKSndCodeAddr;

/* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, begin */
extern SI_STK_CMD_PROC_STATUS_UINT32    g_enTACmdStatus;
/* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, end */

extern SI_STK_SETUP_CALL_CTRL_STRU      g_stStkSetupCallCtrl;

extern SI_SAT_DTMF_DATA_STRU            g_stSTKDtmfData;

extern VOS_UINT8                        g_ucCsinCurcRptCfg;

extern SI_STK_EVENT_STATE_STRU          g_stSTKEventState;

extern MODEM_ID_ENUM_UINT16             g_enSTKCurCSModem;

extern SI_STK_NAS_INFO_STRU             g_stStkSysInfo;

extern SI_STK_CBP_SETUP_EVENT_LIST_STRU g_stCbpEventList;

extern SI_STK_CARDINFO_STRU             g_stStkCardInfo;

extern VOS_BOOL                         g_bSTKAttResetFlag;

extern SI_STK_CALLSTATE_STRU            g_stSTKCallState;

#if (VOS_WIN32 == VOS_OS_VER) /* UT工程编译不过,通过编译宏区分 */
extern MN_MSG_RAW_TS_DATA_STRU            *f_pstStkMsgRawTsDataInfo;
extern MN_MSG_SEND_PARM_STRU              *f_pstSendDirectParm;
#endif

extern SI_STK_CMD_PROC_STATUS_UINT32       g_enNMRCmdStatus;

extern TAF_NV_LC_CTRL_PARA_STRU            g_stLCEnableCfg;

extern STK_EVENTDATA_RESEND_STRU           g_astEventResend[2];

extern STK_FEATURE_CFG_STRU                g_stSTKFeatureCnf;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_UINT8                           g_ucIsXsmsInBuffFlag;   /* FALSE: NO IN BUFF
                                                           TRUR : ONE IN BUFF*/
extern TAF_XSMS_MESSAGE_STRU              *g_pstStkSendXsmsBuff;

extern TAF_XSMS_MESSAGE_STRU              *g_pstStkRcvXsmsBuff;

extern SI_STK_CDMANAS_SYSINFO_STRU         g_stStkCdmaSysInfo;

extern VOS_UINT8                           g_ucIsRatCdma;
#endif

/*****************************************************************************
  6 函数声明
*****************************************************************************/

/* STKComm.c */
extern SI_VOID SI_STK_EventDownload(VOS_VOID *pEventData, VOS_UINT32 ulEventLen, SI_STK_EVENT_TYPE ulEventDownTag, VOS_UINT32 ucSDId);

extern VOS_VOID SI_STK_SndProactiveCmd2CBP(VOS_UINT32 ulCmdLen, VOS_UINT8 *pucCmd);

extern VOS_UINT32 SI_STK_SendTerminalResponseReqMsg(VOS_UINT8 ucLen,VOS_UINT8 *pucRsp, USIMM_TR_PARA_ENUM_32 ulPara);

extern VOS_UINT32 SI_STK_EnvelopeDownHandle(SI_STK_ENVELOPEDOWN_REQ_STRU *pstReq);

extern VOS_UINT32 SI_STK_SendResetReqMsg(USIMM_STK_COMMAND_DETAILS_STRU  *pstCMDDetail,  USIMM_RESET_INFO_STRU *pstRstInfo);

extern VOS_UINT32 SI_STK_SendEnvelopeReqMsg(VOS_UINT32 ulSendPara, USIMM_CARDAPP_ENUM_UINT32 enAppType, VOS_UINT8 ucLen, VOS_UINT8 *pucEnvelope);

extern VOS_UINT32 SI_STKGetBitFromBuf(VOS_UINT8 *pucDataBuf, VOS_UINT32 ulBitNo,VOS_UINT32 ulBufLen);

extern VOS_UINT32 SI_STKFindTag(VOS_UINT8 ucTag, VOS_UINT8 *pucData, VOS_UINT32 ulDataLen,VOS_UINT32 ulFindNum);

extern VOS_UINT32 SI_STKGetBit32(VOS_UINT32 ulValue, VOS_UINT32 ulBitNo);

extern VOS_VOID SI_STKDecodeTagList(VOS_UINT8 *pucCmdData,VOS_UINT8 *pucTagList,VOS_UINT32 ulListLen, SI_SAT_COMMDATA_STRU *pstDec);

extern VOS_UINT32 SI_STKDecodeTagData(VOS_UINT8 *pucCmdData, VOS_UINT8 ucTag, VOS_VOID *pDec);

extern VOS_VOID SI_STKSendTRWithData(SI_STK_COMMAND_DETAILS_STRU *pstCMDInfo, VOS_UINT32 ulResultLen, VOS_UINT8 *pucResult, VOS_UINT32 ulDataLen, VOS_UINT8 *pucData);

extern VOS_VOID SI_STKSimpleResponseData(SI_STK_COMMAND_DETAILS_STRU *pstCMDInfo, VOS_UINT32 ulDataLen, VOS_UINT8 *pucData);

extern VOS_VOID SI_STKSimpleResponse(SI_STK_COMMAND_DETAILS_STRU *pstCMDInfo, VOS_UINT8 ucResult);

extern VOS_VOID SI_STK_InitTResponse(VOS_UINT8 *pTRdata, SI_STK_COMMAND_DETAILS_STRU *pstCMDInfo, SI_STK_RESULT_STRU *pstResult);

extern VOS_VOID SI_STK_InitEnvelope(VOS_UINT8 *pCmdData, SI_STK_DEVICE_IDENTITIES_STRU *pstDiInfo, VOS_UINT8 ucCmdType);

extern VOS_VOID SI_STK_InitEventDown(VOS_UINT8 *pCmdData, SI_STK_DEVICE_IDENTITIES_STRU *pstDiInfo, VOS_UINT8 ucEventType);

extern VOS_UINT32 SI_STKCommDecodeData(VOS_UINT8 *pucCmdData,VOS_UINT32 ulCmdType, SI_SAT_COMMDATA_STRU *pstDec);

extern VOS_UINT32 SI_STKCommCodeData(VOS_UINT8 *pucCmdData,SI_CODEDATA_TYPE_UINT32 enDataType, VOS_UINT32 ulCmdType, SI_SAT_COMMDATA_STRU *pstSrc);

extern VOS_VOID SI_STKCommDataFree(VOS_UINT32 ulCmdType, SI_SAT_COMMDATA_STRU *pstData);

extern VOS_UINT32 SI_STKCheckCardState(VOS_VOID);

extern VOS_UINT32 SI_STKErrorProc(VOS_VOID);

extern VOS_VOID SI_STK_SsStr2ASCII(const VOS_UINT8 *pucSrc, VOS_UINT8 *pucDest, VOS_UINT32 ulLength);

extern VOS_UINT32 SI_STK_StrStr(VOS_UINT8 *pucStr1, VOS_UINT8 *pucStr2 , VOS_UINT32 ulStrlen1, VOS_UINT32 ulStrlen2);

extern VOS_VOID SI_STK_SaveEnvelopeCmd(VOS_UINT32 ulCmdLen, VOS_UINT8 *pucCmdData);

extern VOS_VOID SI_STK_ClearEnvelopeCmd(VOS_VOID);

extern VOS_UINT32 SI_STK_CheckProfileCfg(VOS_UINT32 ulCmdType, SI_STK_CMD_PROFILE_CFG_STRU *pstCfgTbl, VOS_UINT32 ulTblSize);

extern VOS_VOID SI_STK_Num2BCD(const VOS_UINT8 *pucSrc, VOS_UINT8 *pucDest, VOS_UINT32 ulLength);

extern VOS_UINT32 SI_STKTagDataFree(VOS_UINT8 ucTag, VOS_VOID *pData);



/* STKGobal.c */
extern VOS_VOID STK_InitGobal(VOS_VOID);

extern VOS_VOID STK_ResetGlobalValue(VOS_VOID);

/*****************************************************************************
函 数 名  : STK_InitCallGobal
功能描述  : 初时化与呼叫相关的全局变量的内容
输入参数  : 无
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2012年9月13日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
extern VOS_VOID STK_InitCallGobal(VOS_VOID);

/*****************************************************************************
函 数 名  : STK_GetCsSvcStatus
功能描述  : 获取当前CS域服务状态
输入参数  : 无
输出参数  : 无
返 回 值  : 当前服务状态
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
extern VOS_UINT32 STK_GetCsSvcStatus(VOS_VOID);

/*****************************************************************************
函 数 名  : STK_GetSvcStatus
功能描述  : 获取当前服务状态
输入参数  : 无
输出参数  : 无
返 回 值  : 服务状态
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
extern VOS_UINT32 STK_GetSvcStatus(VOS_VOID);

/*****************************************************************************
函 数 名  : STK_UpdateCsSvcStatus
功能描述  : 更新当前CS域服务状态
输入参数  : enCsServiceStatus:CS域服务状态
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
extern VOS_VOID STK_UpdateCsSvcStatus(NAS_STK_SERVICE_STATUS_ENUM_UINT8 enCsServiceStatus);

/*****************************************************************************
函 数 名  : STK_UpdateSvcStatus
功能描述  : 更新当前服务状态
输入参数  : enServiceStatus:服务状态
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2014年01月15日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
extern VOS_VOID STK_UpdateSvcStatus(NAS_STK_SERVICE_STATUS_ENUM_UINT8 enServiceStatus);

/*****************************************************************************
函 数 名  : STK_GetSysInfo
功能描述  : 更新当前系统状态
输入参数  : pstSysInfo:CS域系统信息
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
extern VOS_VOID STK_GetSysInfo(SI_STK_SYS_INFO_STRU *pstSysInfo);

/*****************************************************************************
函 数 名  : STK_UpdateSysInfo
功能描述  : 更新当前系统状态
输入参数  : pstSysInfo:CS域系统信息
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
extern VOS_VOID STK_UpdateSysInfo(NAS_STK_SYS_INFO_STRU *pstSysInfo);

/*****************************************************************************
函 数 名  : STK_GetCurRat
功能描述  : 获取当前接入技术
输入参数  : 无
输出参数  : 无
返 回 值  : 接入技术
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
extern VOS_UINT8 STK_GetCurRat(VOS_VOID);

/*****************************************************************************
函 数 名  : STK_UpdateCurRat
功能描述  : 更新当前接入技术
输入参数  : 无
输出参数  : 无
返 回 值  : 接入技术
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
extern VOS_VOID STK_UpdateCurRat(TAF_MMA_RAT_TYPE_ENUM_UINT8 ucRat);

/*****************************************************************************
函 数 名  : STK_GetSearchMode
功能描述  : 获取当前搜网模式
输入参数  : 无
输出参数  : 无
返 回 值  : 搜网模式
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
extern VOS_UINT8 STK_GetSearchMode(VOS_VOID);

/*****************************************************************************
函 数 名  : STK_UpdateSearchMode
功能描述  : 更新当前搜网模式
输入参数  : 当前搜网模式
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
extern VOS_VOID STK_UpdateSearchMode(VOS_UINT8 ucSearchMode);

/*****************************************************************************
函 数 名  : STK_ProfileInit
功能描述  : 初始化时PROFILE内容初始化
输入参数  : 无
输出参数  : ppucProfile:Profile内容
            pucProfileLen:Profile长度
返 回 值  : 无
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
extern VOS_VOID STK_GetProfileInfo(VOS_UINT8 **ppucProfile, VOS_UINT8 *pucProfileLen);

/*****************************************************************************
函 数 名  : STK_ProfileInit
功能描述  : 初始化时PROFILE内容初始化
输入参数  : pstSTKProfileContent:Profile全局结构指针
            enPhyType:卡物理类型
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
extern VOS_VOID STK_ProfileInit(USIMM_STK_CFG_STRU *pstSTKProfileContent, USIMM_PHYCARD_TYPE_ENUM_UINT32 enPhyType);

/*****************************************************************************
函 数 名  : STK_ClearPauseCharGobal
功能描述  : 清除pause字符相关全局变量
输入参数  : 无
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2012年9月19日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
extern VOS_VOID STK_ClearPauseCharGobal(VOS_VOID);

/*****************************************************************************
函 数 名  : STK_ClearPauseCharGobal
功能描述  : SETUP CALL全局变量中呼叫状态机设置
输入参数  : enCallStatus:重置的呼叫状态
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2012年9月19日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
extern VOS_VOID STK_CallStateMachineSet(SI_STK_CALL_STATUS_ENUM_UINT32 enCallStatus);

/*****************************************************************************
函 数 名  : STK_SetCallCleanGobal
功能描述  : SETUP CALL全局变量清除
输入参数  : 无
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2012年9月19日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
extern VOS_VOID STK_SetCallCleanGobal(VOS_VOID);

/*****************************************************************************
函 数 名  : STK_CLCfgInit
功能描述  : L+C共SIM卡功能状态初始化
输入参数  : 无
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年12月19日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
extern VOS_VOID STK_CLCfgInit(VOS_VOID);

/* STKPro.c */
extern VOS_BOOL SI_STK_CheckSupportAP(VOS_VOID);

extern VOS_BOOL SI_STK_CheckCardStatus(VOS_VOID);

extern VOS_BOOL SI_STK_IsProactiveCmdNeedSnd2Csima(VOS_VOID);

extern VOS_BOOL SI_STK_IsCbpMainCtrlProactiveCmd(VOS_VOID);

extern VOS_UINT32 SI_STK_MoreTimeProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_RefreshProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_PollIntervalProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_PollingOFFProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_SetUpEeventListProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_SetUpEeventListSpecialProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_SetUpEeventListCbpProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_SendSSProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_SetCallSpecialProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_SendUSSDProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_SendSMSProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_SendDTMFProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_DisplayTextProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_SetUpMenuProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_ProvideLocIProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_TimerManageProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_SetUpIdleTextProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_VOID SI_STK_TimeOutMsgProc(REL_TIMER_MSG *pRelTimerMsg);

extern VOS_VOID SI_STK_ProactiveCmdTimeOutProc(VOS_VOID);

extern VOS_VOID SI_STK_TimerManagement(VOS_UINT32 ulTimerId);

extern VOS_UINT32 SI_STKCommDecode(VOS_UINT8* pucCmdData, VOS_UINT32 ulCmdType,SI_SAT_COMMDATA_STRU *pstResult);

extern VOS_UINT32 SI_STKNoNeedDecode(VOS_UINT8* pucCmdData, VOS_UINT32 ulCmdType, SI_SAT_COMMDATA_STRU *pstResult);

extern VOS_UINT32 SI_STK_LaunchBrowser_Decode(VOS_UINT8* pucCmdData, VOS_UINT32 ulCmdType, SI_SAT_COMMDATA_STRU *pstResult);

extern VOS_UINT32 SI_STK_SelectItem_Decode(VOS_UINT8* pucCmdData, VOS_UINT32 ulCmdType, SI_SAT_COMMDATA_STRU *pstResult);

extern VOS_UINT32 SI_STK_SetUpMenu_Decode(VOS_UINT8* pucCmdData, VOS_UINT32 ulCmdType, SI_SAT_COMMDATA_STRU*pstResult);

extern VOS_UINT32 SI_STKSetUpCall_Decode(VOS_UINT8* pucCmdData, VOS_UINT32 ulCmdType, SI_SAT_COMMDATA_STRU*pstResult);

extern VOS_UINT32 SI_STKOpenChannel_Decode(VOS_UINT8* pucCmdData, VOS_UINT32 ulCmdType, SI_SAT_COMMDATA_STRU*pstResult);

extern VOS_UINT32 SI_STKSetFrame_Decode(VOS_UINT8* pucCmdData, VOS_UINT32 ulCmdType,SI_SAT_COMMDATA_STRU*pstResult);

extern VOS_UINT32 SI_STKDataIndCallback(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_VOID SI_STK_ATEnvelopeCnf(USIMM_STKENVELOPE_CNF_STRU *pstMsg);

extern VOS_VOID SI_STK_MenuSelectionCnf(USIMM_STKENVELOPE_CNF_STRU *pstMsg);

extern VOS_VOID SI_STK_TAFEnvelopeCnf(USIMM_STKENVELOPE_CNF_STRU *pstMsg);

extern VOS_VOID SI_STK_EnvelopeCnfMsgProc(PS_SI_MSG_STRU *pstMsg);

extern VOS_VOID SI_STK_RcvSmsEnvelopeCnfDispatchHandle(
    USIMM_STKENVELOPE_CNF_STRU             *pstUsimmMsg
);
extern VOS_VOID SI_STK_MmMsgProc(NAS_STK_EVENT_MSG_HEADER_STRU *pMsg);

extern VOS_VOID SI_STK_GmmMsgProc(NAS_STK_EVENT_MSG_HEADER_STRU *pMsg);

extern VOS_VOID SI_STK_MmaMsgProc(NAS_STK_EVENT_MSG_HEADER_STRU *pMsg);

extern VOS_VOID SI_STK_MmcMsgProc(NAS_STK_EVENT_MSG_HEADER_STRU *pMsg);

extern VOS_VOID SI_STK_PIHMsgProc(PS_SI_MSG_STRU *pMsg);

extern VOS_VOID SI_STK_UsimmMsgProc(PS_SI_MSG_STRU *pMsg);

extern VOS_VOID SI_STK_ProactiveCmdProc(PS_SI_MSG_STRU *pMsg);

extern VOS_VOID SI_STK_StkMsgProc(SI_STK_REQ_STRU *pMsg);

extern VOS_UINT32 SI_STK_GetRecMMCPID(VOS_UINT32 *pulTAFPid);

extern VOS_VOID SI_STK_EventDownComptiable(VOS_VOID);

/*****************************************************************************
函 数 名  : SI_STK_TRCnfMsgProc
功能描述  : 用于处理回复的 Terminal Response 消息
输入参数  : pMsg:消息内容
输出参数  : 无
返 回 值  : 无
*****************************************************************************/
extern VOS_VOID SI_STK_TRCnfMsgProc(PS_SI_MSG_STRU *pMsg);

/*****************************************************************************
函 数 名  : SI_STK_TerminalResponseCnfProc
功能描述  : 用于处理回复的 Terminal Response 消息
输入参数  : pMsg:消息内容
输出参数  : 无
返 回 值  : 无
*****************************************************************************/
extern VOS_VOID SI_STK_TerminalResponseCnfProc(PS_SI_MSG_STRU *pMsg);

/*****************************************************************************
函 数 名  : SI_STK_CbpTrCnfMsgProc
功能描述  : 用于处理VIA下发的Terminal Response消息的CNF消息
输入参数  : pMsg:消息内容
输出参数  : 无
返 回 值  : 无
*****************************************************************************/
extern VOS_VOID SI_STK_CbpTrCnfMsgProc(PS_SI_MSG_STRU *pMsg);

/*****************************************************************************
函 数 名  : SI_STK_CbpTRDataReqProc
功能描述  : 透传VIA下发的Terminal Response数据
输入参数  : STKReqMsg:外部下发的消息请求
输出参数  : 无
返 回 值  : 无
*****************************************************************************/
extern VOS_VOID SI_STK_CbpTRDataReqProc(SI_STK_REQ_STRU *STKReqMsg);

/*****************************************************************************
函 数 名  : SI_STK_ViaTRCnfProc
功能描述  : 将VIA下发Terminal Response的处理结果回复给CSIM Agent
输入参数  : ulErrorCode:TR下发的处理结果
            ucSW1:状态字1
            ucSW2:状态字2
输出参数  : 无
返 回 值  : 无
*****************************************************************************/
extern VOS_VOID SI_STK_CbpTRCnfProc(VOS_UINT32 ulErrorCode, VOS_UINT8 ucSW1, VOS_UINT8 ucSW2);

/*****************************************************************************
函 数 名  :SI_STK_RefreshCallInServiceProc
功能描述  :Refresh命令当UE在呼叫状态的处理函数
输入参数  :pCmdData:主动命令内容
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2012年09月13日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
extern VOS_UINT32 SI_STK_RefreshCallInServiceProc(SI_STK_DATA_INFO_STRU *pCmdData);

/*****************************************************************************
函 数 名  : SI_STK_CmdIndTimeOutProc
功能描述  : 主动命令上报超时处理函数
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_UINT32函数执行结果
 调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月10日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
extern VOS_VOID SI_STK_CmdIndTimeOutProc(VOS_VOID);

extern VOS_VOID SI_STK_MenuSelectionProc(SI_STK_REQ_STRU *STKReqMsg);

/* STKSpecialProc.c */
extern VOS_VOID SI_STK_HookData(VOS_UINT32 ulHookName, VOS_UINT32 ulDataLen, VOS_UINT8 *pucData);

extern VOS_VOID SI_STK_SMSCallBackFunc(MN_CLIENT_ID_T  clientId, MN_MSG_EVENT_ENUM_U32 enEventType, MN_MSG_EVENT_INFO_STRU *pstEvent);

extern VOS_UINT32 SI_STK_SendSMSSpecialProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_SendSSSpecialProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_SendUSSDSpecialProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_SendDTMFSpecialProc(SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_UINT32 SI_STK_EncodeUssdString(SI_STK_USSD_STRING_STRU *pstSrcUssdString, TAF_SS_USSD_STRING_STRU  *pstDestUssdString);

extern VOS_VOID SI_STK_SS_GetPasswordReqProc(VOS_UINT8  *pucPWD);

extern VOS_VOID SI_STK_IMSIChgBegin(SI_STK_REQ_STRU *STKReqMsg);

extern VOS_VOID SI_STK_IMSIChgProc(PS_SI_MSG_STRU *pMsg);

extern VOS_UINT32 SI_STK_ProvideLocalInfo_NAA(VOS_UINT8 *pTrData, SI_STK_NAS_INFO_STRU *pstMmaInfo);

extern VOS_VOID SI_STK_TAFMsgProc(PS_SI_MSG_STRU *pMsg);

/*****************************************************************************
 Prototype      : SI_STK_MtCallEventDownload
 Description    : TAF发送给STK的MT消息处理函数
 Input          : pstMsg:接收消息
 Output         : 无
 Return Value   : 无
 History        : ---
  1.Date        : 2013-07-12
    Author      : H59254
    Modification: Created function
*****************************************************************************/
extern VOS_VOID SI_STK_MtCallEventDownload(NAS_STK_MT_CALL_EVENT_STRU *pstMsg);

/*****************************************************************************
 Prototype      : SI_STK_CallConnectEventDownload
 Description    : TAF发送给STK的Call Connect消息处理函数
 Input          : pstMsg:接收消息
 Output         : 无
 Return Value   : 无
 History        : ---
  1.Date        : 2013-07-12
    Author      : H59254
    Modification: Created function
*****************************************************************************/
extern VOS_VOID SI_STK_CallConnectEventDownload(NAS_STK_CALL_CONNECT_EVENT_STRU *pstMsg);

/*****************************************************************************
 Prototype      : SI_STK_CallDisconnectEventDownload
 Description    : TAF发送给STK的Call Disconnect消息处理函数
 Input          : pstMsg:接收消息
 Output         : 无
 Return Value   : 无
 History        : ---
  1.Date        : 2013-07-12
    Author      : H59254
    Modification: Created function
*****************************************************************************/
extern VOS_VOID SI_STK_CallDisconnectEventDownload(NAS_STK_CALL_DISC_EVENT_STRU *pstMsg);

/*****************************************************************************
 Prototype      : SI_STK_LocationStatusEventDownload
 Description    : TAF发送给STK的Location Status事件下载处理函数
 Input          : 无
 Output         : 无
 Return Value   : 无
 History        : ---
  1.Date        : 2013-07-12
    Author      : H59254
    Modification: Created function
*****************************************************************************/
extern VOS_VOID SI_STK_LocationStatusEventDownload(VOS_VOID);

/*****************************************************************************
 Prototype      : SI_STK_AccessTechChangeEventDownload
 Description    : TAF发送给STK的Access Technology Change消息处理函数
 Input          : 无
 Output         : 无
 Return Value   : 无
 History        : ---
  1.Date        : 2013-07-12
    Author      : H59254
    Modification: Created function
*****************************************************************************/
extern VOS_VOID SI_STK_AccessTechChangeEventDownload(VOS_VOID);

/*****************************************************************************
 Prototype      : SI_STK_NetworkSearchModeChangeEventDownload
 Description    : TAF发送给STK的Network Search Mode Change消息处理函数
 Input          : 无
 Output         : 无
 Return Value   : 无
 History        : ---
  1.Date        : 2013-07-12
    Author      : H59254
    Modification: Created function
*****************************************************************************/
extern VOS_VOID SI_STK_NetworkSearchModeChangeEventDownload(VOS_VOID);

extern VOS_VOID SI_STK_NetworkRejectionEventDownload(NAS_STK_NETWORK_REJECTION_EVENT_STRU *pstMsg);

/*****************************************************************************
 Prototype      : SI_STK_UpdateLocationInfo
 Description    : NAS发送location status消息后同步更新系统信息
 Input          : pstLocStatusEvent:接收消息
 Output         : 无
 Return Value   : 无
 History        : ---
  1.Date        : 2013-07-12
    Author      : H59254
    Modification: Created function
*****************************************************************************/
extern VOS_VOID SI_STK_UpdateLocationInfo(NAS_STK_LOC_STATUS_EVENT_INFO_STRU   *pstLocStatusEvent);

/*****************************************************************************
 Prototype      : SI_STK_TransferUpdateAttachType
 Description    : 将GMM MM被拒原因值转换成STK事件下载需要的原因值
 Input          : ucNasType:GMM MM被拒原因值
 Output         : pucType:STK事件下载需要的原因值
 Return Value   : 无
 History        : ---
  1.Date        : 2013-07-12
    Author      : H59254
    Modification: Created function
*****************************************************************************/
extern VOS_VOID SI_STK_TransferUpdateAttachType(VOS_UINT8 *pucType, NAS_STK_UPDATE_TYPE_ENUM_UINT8 ucNasType);

/*****************************************************************************
 Prototype      : SI_STK_LociInfoIndMsgProc
 Description    : ID_NAS_STK_LOCATION_INFO_IND消息的处理
 Input          : pstLociInfo:消息内容的指针
 Output         : 无
 Return Value   : 无
 History        : ---
  1.Date        : 2013-07-25
    Author      : H59254
    Modification: Created function
*****************************************************************************/
extern VOS_VOID SI_STK_LociInfoIndMsgProc(NAS_STK_LOCATION_INFO_IND_STRU *pstLociInfo);

extern VOS_BOOL SI_STK_IsGULRATMode(VOS_VOID);

extern VOS_VOID SI_STK_CSServiceHook(VOS_VOID);

extern VOS_VOID SI_STK_UssdDcsHook(VOS_UINT8 ucInputDcs, VOS_UINT8 *pUssdString, VOS_UINT16 usStringLen, MN_MSG_CBDCS_CODE_STRU *pstCbDcs);

extern VOS_UINT32 SI_STK_SendSmsSimple(MN_MSG_TPDU_TYPE_ENUM_U8 enTpduType, SI_STK_SEND_SHORT_MESSAGE_STRU *pstSendSMS);

extern VOS_VOID SI_STK_SmsGobleInit(VOS_VOID);

extern VOS_VOID SI_STK_FillSmsPara(SI_STK_SEND_SHORT_MESSAGE_STRU *pstSendSMS);

extern VOS_UINT32 SI_STK_ProvideLocalInfo_IMEI(VOS_UINT8 *pTrData);

extern VOS_UINT32 SI_STK_ProvideLocalInfo_IMEISV(VOS_UINT8 *pTrData);

extern VOS_UINT32 SI_STK_ProvideLocalInfo_ACCESS(VOS_UINT8 *pTrData, SI_STK_ACCESS_TECH_ENUM_UINT8 ucAccessTech);

extern VOS_UINT32 SI_STK_ProvideLocalInfo_SearchMode(VOS_UINT8 *pTrData);

extern VOS_VOID SI_STK_ProvideLocalInfo_Nmr(VOS_UINT32 ulNetType, NAS_STK_UTRAN_MODE_ENUM_UINT8 enUtranMode, SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_VOID SI_STK_ProvideLocalINfo_TA(VOS_UINT32 ulNetType, SI_STK_DATA_INFO_STRU *pCmdData);

extern VOS_VOID SI_STK_TACnfProc(PS_SI_MSG_STRU *pstMsg);

extern VOS_VOID SI_STK_BcdByteToAscii(VOS_UINT8 ucBcdByte,VOS_UINT8*pucAsciiByte,SI_STK_STR_CHANGEMODE_ENUM_UINT32 enChangeMode);

extern VOS_UINT32 SI_STK_CheckSmsPara(SI_STK_SMS_TPDU_STRU *pstTPDU,SI_STK_COMMAND_DETAILS_STRU *pstCmdDetail,VOS_UINT32 *pulMsgNeedPress,VOS_UINT32 *pulSmsNumber);

extern VOS_UINT32 SI_STK_SendSubmitSms(SI_STK_SEND_SHORT_MESSAGE_STRU *pstSendSMS, SI_STK_COMMAND_DETAILS_STRU *pstCmdDetail);

extern VOS_UINT32 SI_STK_IMSIChgSelItemProc(PS_SI_MSG_STRU *pMsg);

extern VOS_UINT32 SI_STK_IMSIChgRefreshProc(PS_SI_MSG_STRU *pMsg);

extern VOS_VOID SI_STK_CardStatusMsgProc(PS_SI_MSG_STRU *pMsg);

extern VOS_UINT32 SI_STK_GetGasTAReq(VOS_VOID);

extern VOS_UINT32 SI_STK_GetGasNmrReq(VOS_VOID);

extern VOS_UINT32 SI_STK_SendNmrReq(VOS_UINT32 ulReceiverPid, VOS_UINT32 ulQueryType);

extern VOS_VOID SI_STK_GasMsgProc(PS_SI_MSG_STRU *pMsg);

extern VOS_VOID SI_STK_UtranMsgProc(PS_SI_MSG_STRU *pMsg);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_VOID SI_STK_XsmsMsgProc(
    PS_SI_MSG_STRU                      *pMsg);

extern VOS_VOID SI_STK_XsmsRcvSendSmsCnf(
    PS_SI_MSG_STRU                      *pMsg);

extern VOS_VOID SI_STK_XsmsRcvSendSmsRsltInd(
    PS_SI_MSG_STRU                      *pMsg);

extern VOS_VOID SI_STK_XsmsRcvSmsPPDownLoadReq(
    PS_SI_MSG_STRU                      *pMsg);

extern VOS_VOID SI_STK_RcvXsmsEnvelopeHandle(USIMM_STKENVELOPE_CNF_STRU *pstMsg);

extern VOS_VOID SI_STK_SendXsmsPPDownLoadCnf(
    VOS_UINT32                          ulEnvelopeRslt,
    VOS_UINT32                          ulRspCode,
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData
);

#endif

extern VOS_UINT32 SI_STK_SteeringRoamingInd(VOS_UINT32 ulLen, VOS_UINT8 *pucOplmnList);

extern VOS_UINT32 SI_STK_SendTAFMsg(VOS_UINT32 ulMsgName,VOS_UINT8 ucOpID,VOS_UINT8 ucValue,VOS_UINT8* pucData,VOS_UINT32 ulLen);

extern VOS_VOID SI_STK_SendChangePollTimerLenMsg(
    VOS_UINT32                          ulTimerLen);

extern VOS_VOID SI_STK_SendChangeCallTimerMsg(
    SI_STK_CALLSTATE_FLAG_UINT8         enCSState,
    SI_STK_CALLSTATE_FLAG_UINT8         enPSState);

extern VOS_VOID SI_STK_PsCallStateEvent(
    NAS_STK_PS_CALLINFO_EVENT_STRU      *pstMsg);

extern VOS_UINT32 SI_STK_IsMeidValid(
    NV_MEID_STRU                       *pstMeid);

extern VOS_UINT32 SI_STK_IsPesnValid(
    NV_PESN_STRU                       *pstPesn);

extern VOS_VOID SI_STK_ATTResetReSend(VOS_VOID);

extern VOS_VOID SI_STK_BcdStrToAscii(VOS_UINT8 ucBcdNumLen,VOS_UINT8 *pucBcdNum,VOS_UINT8 *pucAsciiNum,VOS_UINT32 *pulLen,SI_STK_STR_CHANGEMODE_ENUM_UINT32 enChangeMode);

extern VOS_UINT32 SI_STK_GetRecGASPID(VOS_UINT32 *pulGasPid);

extern VOS_UINT32 SI_STK_GetRecTAFPID(VOS_UINT32 *pulTAFPid);

extern VOS_VOID SI_STK_GetCSModemFunc(TAF_STK_CS_SERVICE_IND *pstMsg);

extern VOS_UINT32 SI_STK_SVLTECheckMsgPID(PS_SI_MSG_STRU *pMsg, VOS_UINT32 ulPid);

extern VOS_UINT32 SI_STK_SVLTECheckCsDomainAndMsgPID(PS_SI_MSG_STRU *pMsg, VOS_UINT32 ulExpectPid);

extern VOS_VOID SI_STK_MnCmdCnfProcFunc(MN_CLIENT_ID_T  clientId,MN_OPERATION_ID_T opId,TAF_UINT32 ulErrorCode);

extern VOS_VOID SI_STK_SsCnfProcFunc(MN_CLIENT_ID_T clientId,MN_CALL_EVENT_ENUM_U32 enEventType,TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent);

extern VOS_VOID SI_STK_CsCallBackFunc(MN_CALL_EVENT_ENUM_U32 enEventType, MN_CALL_INFO_STRU *pstEvent);

extern VOS_VOID SI_STK_CallCBProc(MN_CALL_EVENT_ENUM_U32 enEventType,MN_CALL_INFO_STRU *pstEvent);

extern VOS_BOOL STK_IsCallInService(VOS_VOID);

extern VOS_BOOL STK_IsCPBCsimRefreshCmd(SI_STK_DATA_INFO_STRU *pCmdData);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_VOID SI_STK_InitXsmsGlobal(VOS_VOID);
extern VOS_UINT32 SI_STK_SendCdmaSMSHandle(
    SI_STK_SEND_SHORT_MESSAGE_STRU     *pstSendSMS,
    SI_STK_COMMAND_DETAILS_STRU        *pstCmdDetail
);
extern VOS_UINT32  SI_STK_CheckCdmaSmsPara(
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLMsg,
    SI_STK_COMMAND_DETAILS_STRU        *pstCmdDetail,
    SI_STK_CDMA_SMS_CTRL_PARA_STRU     *pstCdmaSmsPara
);

extern VOS_VOID SI_STK_SendXsmsReq(
    TAF_XSMS_MESSAGE_STRU   *pstMessage,
    VOS_UINT16               usIsUserAckMsg
);

extern VOS_VOID SI_STK_ServiceInfoInd(
    MMA_STK_SERVICE_INFO_IND_STRU       *pstMsg);

extern VOS_UINT32 SI_STK_ProvideMEID(
    VOS_UINT8                           *pTrData);

extern VOS_UINT32 SI_STK_ProvideESN(
    VOS_UINT8                           *pTrData);

extern VOS_UINT32 SI_STK_CdmaProvideLocalInfo(
    VOS_UINT8                           *pTrData);

extern VOS_VOID SI_STK_CdmaLocStatusEventDownload(VOS_VOID);

#endif

#if (FEATURE_VSIM == FEATURE_ON)
extern VOS_VOID SI_STK_VsimSmsPpDownloadProc(
    VOS_UINT32                          ulRcvPid,
    VOS_UINT32                          ulSendPara,
    SI_STK_SMS_PP_DOWNLOAD_STRU        *pstSmsPpDlData);
#endif

extern VOS_VOID SI_STK_SetupCallStatusTable(MN_CALL_EVENT_ENUM_U32 enEventType, MN_CALL_INFO_STRU *pstEvent);

extern VOS_VOID SI_STK_SetUpCallAllow(SI_STK_SETUPCALLCONFIRM_ENUM_UINT32 enAction);

extern VOS_UINT32 SI_STK_SetUpCallOnlyNotBusyOnCall(VOS_VOID);

extern VOS_UINT32 SI_STK_SetUpCallDisconnectBusyCall(VOS_VOID);

extern VOS_UINT32 SI_STK_SetUpCallHoldBusyCall(VOS_VOID);

extern VOS_VOID SI_STK_SetUpCallStartDurationTimer(VOS_UINT32 ulFlg, SI_STK_DURATION_STRU *pstDuration);

extern VOS_VOID SI_STK_SetUpCallStopDurationTimer(VOS_UINT32 ulFlg);

extern VOS_UINT32 SI_STK_SetUpCall(VOS_BOOL bNeedDurTimer);

extern VOS_UINT32 SI_STK_HoldCall(VOS_VOID);

extern VOS_UINT32 SI_STK_DisconnectCall(MN_CALL_ID_T ucCallId);

extern VOS_UINT32 SI_STK_DisconnectAllCall(VOS_VOID);

extern VOS_UINT32 SI_STK_DisconnectStkCall(VOS_VOID);

extern VOS_UINT32 SI_STK_SendCallSupsMsg(MN_CALL_SUPS_CMD_ENUM_U8 enSupsCmd, MN_CALL_ID_T ucCallId);

extern VOS_UINT32 SI_STK_GetPauseCharFromBCD(SI_STK_ADDRESS_STRU  *pstAddr);

extern VOS_VOID SI_STK_SuspendCnfMsgProc(MN_CALL_INFO_STRU *pstEvent);

extern VOS_UINT32  SI_STK_SendStartDtmfMsg(VOS_CHAR cDtmf, VOS_UINT8 ucOpId, VOS_UINT8 ucCallId);

extern SI_STK_DTMF_SEND_ENUM_UINT32  SI_STK_SendStopDtmfMsg(VOS_UINT8 ucopID);

extern SI_STK_DTMF_SEND_ENUM_UINT32  SI_STK_SendDtmfToTAF(VOS_UINT8 ucOpId, VOS_UINT8 ucCallId);

extern VOS_VOID SI_STK_SendDtmfCBProc(MN_CALL_EVENT_ENUM_U32 enEventType,MN_CALL_INFO_STRU *pstEvent);

extern VOS_VOID SI_STK_SendDTMFResultProc(MN_CALL_EVENT_ENUM_U32  enEventType,TAF_CALL_EVT_DTMF_CNF_STRU *pstEvent);

extern VOS_VOID SI_STK_SendSmsMnCmdCnfProcFunc(MN_CLIENT_ID_T clientId,MN_OPERATION_ID_T opId,TAF_UINT32 ulErrorCode);

extern VOS_VOID SI_STK_SendSsOrUssdMnCmdCnfProcFunc(MN_CLIENT_ID_T clientId,MN_OPERATION_ID_T opId,TAF_UINT32 ulErrorCode);

extern VOS_VOID SI_STK_SendDTMFCnfProc(TAF_CALL_EVT_DTMF_CNF_STRU *pstEvent);

extern VOS_VOID SI_STK_SetupCallSsMnCmdCnfProcFunc(TAF_UINT32 ulErrorCode);

extern VOS_VOID SI_STK_SaveCallId(MN_CALL_ID_T ucCallId, MN_CLIENT_ID_T usClientId);

extern VOS_VOID SI_STK_CallReleasedProc(MN_CALL_EVENT_ENUM_U32 enEventType, MN_CALL_ID_T ucCallId, VOS_UINT8 ucIsUser);

extern VOS_VOID SI_STK_CallConnectProc(MN_CALL_EVENT_ENUM_U32 enEventType, MN_CALL_ID_T ucCallId);

extern VOS_VOID SI_STK_SmsCBSendContinue(VOS_VOID);

extern VOS_VOID SI_STK_SendSsCnfProc(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent);

extern VOS_VOID SI_STK_SsEvtCnfProc(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent, VOS_UINT8 aucTr[], VOS_UINT8 *pucLen);

extern VOS_VOID SI_STK_SsEvtCauseProc(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent, VOS_UINT8 aucTr[], VOS_UINT8 *pucLen);

extern VOS_VOID SI_STK_SsEvtProblemProc(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent, VOS_UINT8 aucTr[], VOS_UINT8 *pucLen);

extern VOS_VOID SI_STK_SsEvtErrProc(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent, VOS_UINT8 aucTr[], VOS_UINT8 *pucLen);

extern VOS_VOID SI_STK_SsOrUssdEvtUssReqCnfProc(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent, VOS_UINT8 aucTr[], VOS_UINT8 *pucLen);

extern VOS_VOID SI_STK_SendUssdCnfProc(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent);

extern VOS_VOID SI_STK_SmsGlobalClear(VOS_VOID);

extern VOS_VOID SI_STK_UssdEvtCauseProc(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent, VOS_UINT8 aucTr[], VOS_UINT8 *pucLen);

extern VOS_VOID SI_STK_UssdEvtProblemProc(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent, VOS_UINT8 aucTr[], VOS_UINT8 *pucLen);

extern VOS_VOID SI_STK_UssdEvtErrProc(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent, VOS_UINT8 aucTr[], VOS_UINT8 *pucLen);

extern VOS_UINT32 MN_MSG_DecodeCbsDcs(
    VOS_UINT8                           ucDcs,
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLength,
    MN_MSG_CBDCS_CODE_STRU             *pstDcsInfo
);

extern VOS_UINT32  TAF_STD_UnPack7Bit(
    const VOS_UINT8                     *pucOrgChar,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucFillBit,
    VOS_UINT8                           *pucUnPackedChar
);

extern VOS_UINT32  TAF_STD_Pack7Bit(
    const VOS_UINT8                     *pucOrgChar,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucFillBit,
    VOS_UINT8                           *pucPackedChar,
    VOS_UINT32                          *pulLen
);

extern VOS_UINT8 SI_STK_SsOrUssdEvtUssReqCnfDataProc(
    VOS_UINT8                          *pucText,
    VOS_UINT8                           ucDcs,
    VOS_UINT8                           ucDateLen,
    VOS_UINT8                          *pucDate);

extern VOS_VOID SI_STK_EventResendSave(SI_STK_ENVELOPE_RESENT_FLAG_UINT32 enDataType, VOS_UINT32 ulEventLen, VOS_UINT8 *pucData);

extern VOS_VOID SI_STK_EventResendClean(SI_STK_ENVELOPE_RESENT_FLAG_UINT32 enDataType);

extern VOS_VOID SI_STK_ResendTimerMsgHandle(REL_TIMER_MSG *pstMsg);

extern VOS_UINT32 SI_STK_GetResendCfg(NV_EVENT_RESEND_CFG_STRU *pstNVCfg);

/* STKAtPrintf.c */
extern VOS_VOID At_STKCallBackFunc(SI_STK_EVENT_INFO_STRU *pstEvent);


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

#endif




