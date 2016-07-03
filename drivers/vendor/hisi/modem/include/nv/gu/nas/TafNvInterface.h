/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.
 
 ******************************************************************************
  File Name       : NasNvInterface.h
  Description     : NasNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __TAFNVINTERFACE_H__
#define __TAFNVINTERFACE_H__

#include "vos.h"
#include "product_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/

#define AT_NVIM_SETZ_LEN                (16)
#define AT_NOTSUPPORT_STR_LEN           (16)

/* 优先级级别最大数 */
#define ADS_UL_QUEUE_SCHEDULER_PRI_MAX  (9)

/*WIFI 相关 NV长度*/
#define AT_WIFI_BASIC_NV_LEN            (116)
#define AT_WIFI_SEC_NV_LEN              (205)

/*WIFI SSID KEY最大长度*/
#define AT_WIFI_SSID_LEN_MAX            (33)
#define AT_WIFI_KEY_LEN_MAX             (27)

/* 鉴权模式字符串长度 */
#define AT_WIFI_WLAUTHMODE_LEN          (16)

/* 加密模式字符串长度 */
#define AT_WIFI_ENCRYPTIONMODES_LEN     (5)

/* WPA的密码字符串长度 */
#define AT_WIFI_WLWPAPSK_LEN            (65)

/* 最多支持4组SSID */
#define AT_WIFI_MAX_SSID_NUM            (4)

#define AT_WIFI_KEY_NUM                 (AT_WIFI_MAX_SSID_NUM)

#define TAF_CBA_NVIM_MAX_ETWS_DUP_DETECT_SPEC_MCC_NUM            (5)                 /* 有效时长定制特性中最大指定MCC个数 */
#define TAF_CBA_NV_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM            (2)

/* 9130扩展IPv6回退处理扩展原因值最大个数 */
#define TAF_NV_IPV6_FALLBACK_EXT_CAUSE_MAX_NUM      (20)

#define AT_AP_NVIM_XML_RPT_SRV_URL_LEN              (127)
#define AT_AP_XML_RPT_SRV_URL_LEN                   (127)
#define AT_AP_XML_RPT_SRV_URL_STR_LEN               (AT_AP_XML_RPT_SRV_URL_LEN + 1)
#define AT_AP_XML_RPT_INFO_TYPE_LEN                 (127)

/*WEB UI 密码最大长度*/
#define AT_WEBUI_PWD_MAX                            (16)
#define AT_WEBUI_PWD_MAX_SET                        (0)
#define AT_WEBUI_PWD_VERIFY                         (1)

#define AT_AP_NVIM_XML_RPT_INFO_TYPE_LEN            (127)
#define AT_AP_NVIM_XML_RPT_INFO_TYPE_STR_LEN        (AT_AP_NVIM_XML_RPT_INFO_TYPE_LEN + 1)
/* PRODUCT NAME*/
#define AT_PRODUCT_NAME_MAX_NUM                     (29)
#define AT_PRODUCT_NAME_LENGHT                      (AT_PRODUCT_NAME_MAX_NUM + 1)

#define TAF_NVIM_DFS_MAX_PROFILE_NUM                (8)

#define TAF_NVIM_DIFF_DFS_NUM                       (8)

#define TAF_NVIM_MAX_APN_LEN                        (99)
#define TAF_NVIM_MAX_APN_STR_LEN                    (TAF_NVIM_MAX_APN_LEN + 1)

#define AT_MAX_ABORT_CMD_STR_LEN                    (16)
#define AT_MAX_ABORT_RSP_STR_LEN                    (16)

#define AT_NVIM_BODYSARGSM_MAX_PARA_GROUP_NUM       (8)

#define AT_NVIM_RIGHT_PWD_LEN                       (16)

#define TAF_PH_NVIM_MAX_GUL_RAT_NUM                 (3)                 /*AT^syscfgex中acqorder代表的接入技术个数 */

#define TAF_NVIM_ITEM_IMEI_SIZE                     (16)

#define AT_DISSD_PWD_LEN                            (16)

#define AT_OPWORD_PWD_LEN                           (16)

#define AT_FACINFO_INFO1_LENGTH                     (128)
#define AT_FACINFO_INFO2_LENGTH                     (128)
#define AT_FACINFO_STRING_LENGTH        \
((AT_FACINFO_INFO1_LENGTH + 1) + (AT_FACINFO_INFO2_LENGTH + 1))

#define AT_FACINFO_INFO1_STR_LENGTH                 (AT_FACINFO_INFO1_LENGTH + 1)
#define AT_FACINFO_INFO2_STR_LENGTH                 (AT_FACINFO_INFO2_LENGTH + 1)

#define AT_MDATE_STRING_LENGTH                      (20)

#define MMA_FORB_BAND_NV_MAX_SIZE                   (10)     /* FobBand的NV长度 */

#define MMA_OPERTOR_NAME_MAX_SIZE                   (256)

#define TAF_PH_WCDMA_CLASSMAEK1_LEN                         (2)
#define TAF_PH_WCDMA_CLASSMAEK2_LEN                         (4)
#define TAF_PH_WCDMA_CLASSMAEK3_LEN                         (16)

#define TAF_MAX_MFR_ID_LEN                                  (31)
#define TAF_MAX_MFR_ID_STR_LEN                              (TAF_MAX_MFR_ID_LEN + 1)

#define NAS_MMA_NVIM_OPERATOR_NAME_LEN                      (360)

#define TAF_NVIM_ME_PERSONALISATION_PWD_LEN_MAX             (8)

#define TAF_NVIM_MAX_IMSI_LEN                               (15)
#define TAF_NVIM_MAX_IMSI_STR_LEN                           (TAF_NVIM_MAX_IMSI_LEN + 1)

#define TAF_NVIM_MSG_ACTIVE_MESSAGE_MAX_URL_LEN             (160)

/*^AUTHDATA命令中用户名和密码的最大长度*/
#define TAF_NVIM_MAX_NDIS_USERNAME_LEN_OF_AUTHDATA          (128)                            /* USERNAME 为127 */
#define TAF_NVIM_MAX_NDIS_PASSWORD_LEN_OF_AUTHDATA          (128)                            /* PASSWORD 为127 */

/*^AUTHDATA命令中<PLMN>参数的最大长度*/
#define TAF_NVIM_MAX_NDIS_PLMN_LEN                          (7)

#define TAF_NVIM_PDP_PARA_LEN                               (1952)

#define TAF_PH_PRODUCT_NAME_LEN                             (15)
#define TAF_PH_PRODUCT_NAME_STR_LEN                         (TAF_PH_PRODUCT_NAME_LEN + 1)

/* 短信业务参数结构与NV项中存储的位置 */
#define MN_MSG_SRV_PARAM_LEN                                (8)                 /* 短信业务参数结构与NV项中存储的长度 */
#define MN_MSG_SRV_RCV_SM_ACT_OFFSET                        (0)                 /* 短信接收上报方式在NV项中存储的偏移 */
#define MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET                  (1)                 /* 短信接收存储介质在NV项中存储的偏移 */
#define MN_MSG_SRV_RCV_STARPT_ACT_OFFSET                    (2)                 /* 短信状态报告接收上报方式c */
#define MN_MSG_SRV_RCV_STARPT_MEM_STORE_OFFSET              (3)                 /* 短信状态报告接收存储介质在NV项中存储的偏移 */
#define MN_MSG_SRV_CBM_MEM_STORE_OFFSET                     (4)                 /* 广播短信接收存储介质在NV项中存储的偏移 */
#define MN_MSG_SRV_APP_MEM_STATUS_OFFSET                    (5)                 /* APP短信接收存储介质可用标志在NV项中存储的偏移，对应字节取值含义0:存储满存储介质不可用 1:存储空闲存储介质可用 */
#define MN_MSG_SRV_SM_MEM_ENABLE_OFFSET                     (6)                 /* 短信接收存储介质在NV项中存储标志在NV项中存储的偏移，对应字节取值含义0:不使能 1:使能 */
#define MN_MSG_SRV_MO_DOMAIN_PROTOCOL_OFFSET                (7)                 /* 短信发送域按协议要求实现的偏移，对应字节取值含义0:不使能 1:使能 */

#define MN_MSG_MAX_EF_LEN                                   (255)
#define MN_MSG_EFSMSS_PARA_LEN                              (256)
#define MN_MSG_EFSMSP_PARA_LEN                              (256)

#define TAF_PH_SIMLOCK_PLMN_STR_LEN                         (8)                 /* Plmn 号段长度 */
#define TAF_MAX_SIM_LOCK_RANGE_NUM                          (20)

/* WINS可配置NV项的结构体 */
#define WINS_CONFIG_DISABLE                                 (0)                 /* WINS不使能 */
#define WINS_CONFIG_ENABLE                                  (1)                 /* WINS使能 */

#define TAF_CBA_NVIM_MAX_CBMID_RANGE_NUM                    (100)               /* 用户最多可输入的消息ID范围个数，在接受模式下还要受到CBMIR文件大小限制 */
#define TAF_CBA_NVIM_MAX_LABEL_NUM                          (16)                /* 用户最多可输入的描述信息的长度，单位BYTE */

#define TAF_SVN_DATA_LENGTH                                 (2)                 /* SVN有效数据长度 */

/*  当前支持的UMTS的codec类型仅存在3种,但协议中还有扩展，因此此处预留扩展的字段 */
#define MN_CALL_MAX_UMTS_CODEC_TYPE_NUM                     (7)

#define MN_CALL_NVIM_BC_MAX_SPH_VER_NUM                     (6)
#define MN_CALL_NVIM_MAX_CUSTOM_ECC_NUM                     (20)                /* 用户定制的紧急呼号码最大条数 */

#define MN_CALL_NVIM_MAX_BCD_NUM_LEN                        (20)

#define TAF_AT_NVIM_CLIENT_CONFIG_LEN                       (64)

#define TAF_NVIM_CBA_MAX_LABEL_NUM                          (16)

#define MTA_BODY_SAR_WBAND_MAX_NUM                          (5)
#define MTA_BODY_SAR_GBAND_MAX_NUM                          (4)

#define MTC_RF_LCD_MIPICLK_MAX_NUM                          (8)                 /* MIPICLK最大个数 */
#define MTC_RF_LCD_MIPICLK_FREQ_MAX_NUM                     (8)                 /* 每个MIPICLK影响的最大频率个数 */

#define TAF_NV_BLACK_LIST_MAX_NUM                           (51)


#define TAF_NVIM_MAX_OPER_NAME_SERVICE_PRIO_NUM              (4)
#define TAF_NVIM_STORED_OPER_NAME_NUM                        (3)

#define TAF_NVIM_IMS2CS_CALL_REDIAL_CAUSE_MAX_NUM     (128)       /* IMS --> CS 需要重播的原因值最大个数为128 */
#define TAF_NVIM_IMSA2CS_CALL_REDIAL_CAUSE_MAX_NUM    (64)        /* IMSA --> CS 需要重播的原因值最大个数为128 */


#define TAF_NVIM_CALL_REDIAL_CAUSE_MAX_NUM            (32)
#define TAF_NVIM_SS_RETRY_CAUSE_MAX_NUM               (32)
#define TAF_NVIM_SMS_RETRY_CAUSE_MAX_NUM              (32)

#define TAF_NVIM_KMC_MSG_MAX_KMC_PUB_KEY_LEN          (48)

typedef VOS_UINT8  MN_CALL_STATE_ENUM_UINT8;

typedef VOS_UINT32  MMA_QUICK_START_STA_UINT32;
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/* ME Storage Function On or Off*/
enum MN_MSG_ME_STORAGE_STATUS_ENUM
{
    MN_MSG_ME_STORAGE_DISABLE           = 0x00,
    MN_MSG_ME_STORAGE_ENABLE            = 0x01,
    MN_MSG_ME_STORAGE_BUTT
};
typedef VOS_UINT8 MN_MSG_ME_STORAGE_STATUS_ENUM_UINT8;

enum AT_UART_LINK_TYPE_ENUM
{
    AT_UART_LINK_TYPE_OM        = 1,          /* OM模式 */
    AT_UART_LINK_TYPE_AT        = 2,          /* AT模式 */
    AT_UART_LINK_TYPE_BUTT
};
typedef VOS_UINT16 AT_UART_LINK_TYPE_ENUM_UINT16;

enum MMA_CUSTOM_CARDLOCK_OPERATOR_ENUM
{
    MMA_CUSTOM_CARDLOCK_NO_AVAILABLE   = 0,                                     /* 0：默认不打开，使用可配置写入的SIMLOCK */
    MMA_CUSTOM_CARDLOCK_EGYPT_VDF,                                              /* 1：打开埃及VDF定制的37组SIMLOCK */
    MMA_CUSTOM_CARDLOCK_NORWAY_NETCOM,                                          /* 2：打开挪威Netcomm的SIMLOCK */
    MMA_CUSTOM_CARDLOCK_MEXICO_TELCEL,                                          /* 3：打开墨西哥TELCEL的永久锁卡号段334020 */
    MMA_CUSTOM_CARDLOCK_DOMINICA_TELCEL,                                        /* 4：打开多米尼加TELCEL的永久锁卡号段37002，33870，42502 */
    MMA_CUSTOM_CARDLOCK_BUTT
};



enum MTA_WCDMA_BAND_ENUM
{
    MTA_WCDMA_I_2100                    = 0x0001,
    MTA_WCDMA_II_1900,
    MTA_WCDMA_III_1800,
    MTA_WCDMA_IV_1700,
    MTA_WCDMA_V_850,
    MTA_WCDMA_VI_800,
    MTA_WCDMA_VII_2600,
    MTA_WCDMA_VIII_900,
    MTA_WCDMA_IX_J1700,
    /* 频段暂不支持
    MTA_WCDMA_X,
    */
    MTA_WCDMA_XI_1500                   = 0x000B,
    /* 以下频段暂不支持
    MTA_WCDMA_XII,
    MTA_WCDMA_XIII,
    MTA_WCDMA_XIV,
    MTA_WCDMA_XV,
    MTA_WCDMA_XVI,
    MTA_WCDMA_XVII,
    MTA_WCDMA_XVIII,
    */
    MTA_WCDMA_XIX_850                   = 0x0013,

    MTA_WCDMA_BAND_BUTT
};
typedef VOS_UINT16 MTA_WCDMA_BAND_ENUM_UINT16;


enum TAF_NVIM_LC_WORK_CFG_ENUM
{
    TAF_NVIM_LC_INDEPENT_WORK = 0,
    TAF_NVIM_LC_INTER_WORK    = 1,
    TAF_NVIM_LC_WORK_CFG_BUTT
};
typedef VOS_UINT8 TAF_NVIM_LC_WORK_CFG_ENUM_UINT8;


enum TAF_NVIM_LC_RAT_COMBINED_ENUM
{
    TAF_NVIM_LC_RAT_COMBINED_GUL  = 0x55,
    TAF_NVIM_LC_RAT_COMBINED_CL   = 0xAA,
    TAF_NVIM_LC_RAT_COMBINED_BUTT
};
typedef VOS_UINT8 TAF_NVIM_LC_RAT_COMBINED_ENUM_UINT8;


enum MTC_PS_TRANSFER_ENUM
{
    MTC_PS_TRANSFER_NONE                = 0x00,                                 /* 无PS域迁移策略 */
    MTC_PS_TRANSFER_LOST_AREA           = 0x01,                                 /* 脱网重选策略 */
    MTC_PS_TRANSFER_OFF_AREA            = 0x02,                                 /* 离网重选策略 */

    MTC_PS_TRANSFER_SOLUTION_BUTT
};
typedef VOS_UINT8 MTC_PS_TRANSFER_ENUM_UINT8;


enum TAF_NV_CLIENT_CFG_ENUM
{
    TAF_NV_CLIENT_CFG_PCUI              = 0,
    TAF_NV_CLIENT_CFG_CTRL              = 1,
    TAF_NV_CLIENT_CFG_MODEM             = 2,
    TAF_NV_CLIENT_CFG_NDIS              = 3,
    TAF_NV_CLIENT_CFG_UART              = 4,
    TAF_NV_CLIENT_CFG_SOCK              = 5,
    TAF_NV_CLIENT_CFG_APPSOCK           = 6,
    TAF_NV_CLIENT_CFG_HSIC1             = 7,
    TAF_NV_CLIENT_CFG_HSIC2             = 8,
    TAF_NV_CLIENT_CFG_HSIC3             = 9,
    TAF_NV_CLIENT_CFG_HSIC4             = 10,
    TAF_NV_CLIENT_CFG_MUX1              = 11,
    TAF_NV_CLIENT_CFG_MUX2              = 12,
    TAF_NV_CLIENT_CFG_MUX3              = 13,
    TAF_NV_CLIENT_CFG_MUX4              = 14,
    TAF_NV_CLIENT_CFG_MUX5              = 15,
    TAF_NV_CLIENT_CFG_MUX6              = 16,
    TAF_NV_CLIENT_CFG_MUX7              = 17,
    TAF_NV_CLIENT_CFG_MUX8              = 18,
    TAF_NV_CLIENT_CFG_APP               = 19,
    TAF_NV_CLIENT_CFG_APP1              = 20,
    TAF_NV_CLIENT_CFG_APP2              = 21,
    TAF_NV_CLIENT_CFG_APP3              = 22,
    TAF_NV_CLIENT_CFG_APP4              = 23,
    TAF_NV_CLIENT_CFG_APP5              = 24,
    TAF_NV_CLIENT_CFG_APP6              = 25,
    TAF_NV_CLIENT_CFG_APP7              = 26,
    TAF_NV_CLIENT_CFG_APP8              = 27,
    TAF_NV_CLIENT_CFG_APP9              = 28,
    TAF_NV_CLIENT_CFG_APP10             = 29,
    TAF_NV_CLIENT_CFG_APP11             = 30,
    TAF_NV_CLIENT_CFG_APP12             = 31,
    TAF_NV_CLIENT_CFG_APP13             = 32,
    TAF_NV_CLIENT_CFG_APP14             = 33,
    TAF_NV_CLIENT_CFG_APP15             = 34,
    TAF_NV_CLIENT_CFG_APP16             = 35,
    TAF_NV_CLIENT_CFG_APP17             = 36,
    TAF_NV_CLIENT_CFG_APP18             = 37,
    TAF_NV_CLIENT_CFG_APP19             = 38,
    TAF_NV_CLIENT_CFG_APP20             = 39,
    TAF_NV_CLIENT_CFG_APP21             = 40,
    TAF_NV_CLIENT_CFG_APP22             = 41,
    TAF_NV_CLIENT_CFG_APP23             = 42,
    TAF_NV_CLIENT_CFG_APP24             = 43,
    TAF_NV_CLIENT_CFG_APP25             = 44,
    TAF_NV_CLIENT_CFG_APP26             = 45,
    TAF_NV_CLIENT_CFG_HSIC_MODEM        = 46,
    TAF_NV_CLIENT_CFG_HSUART            = 47,
    TAF_NV_CLIENT_CFG_PCUI2             = 48,

    TAF_NV_CLIENT_CFG_MAX               = TAF_AT_NVIM_CLIENT_CONFIG_LEN
};
typedef VOS_UINT16 TAF_NV_CLIENT_CFG_ENUM_UINT16;

enum TAF_FLASH_DIRECTORY_TYPE_ENUM
{

    /* V3R3版本的E5和STICK */
    TAF_FLASH_DIRECTORY_TYPE_V3R3E5_V3R3STICK               = 0x00,

    /* V7R2版本和V3R3版本的M2M产品形态 */
    TAF_FLASH_DIRECTORY_TYPE_V7R2_V3R3M2M                   = 0x01,

    /* V9R1手机 */
    TAF_FLASH_DIRECTORY_TYPE_V9R1PHONE                      = 0x02,

    /* FLASH文件存储归一路径，当前仅适用于K3V3V8R1版本 */
    TAF_FLASH_DIRECTORY_TYPE_K3V3V8R1                       = 0x03,

    TAF_FLASH_DIRECTORY_TYPE_BUTT
};
typedef VOS_UINT8 TAF_FLASH_DIRECTORY_TYPE_ENUM_UINT16;


enum TAF_NVIM_RAT_MODE_ENUM
{
    TAF_NVIM_RAT_MODE_GSM               = 0x01,
    TAF_NVIM_RAT_MODE_WCDMA,
    TAF_NVIM_RAT_MODE_LTE,
    TAF_NVIM_RAT_MODE_CDMA1X,
    TAF_NVIM_RAT_MODE_TDSCDMA,
    TAF_NVIM_RAT_MODE_WIMAX,
    TAF_NVIM_RAT_MODE_EVDO,

    TAF_NVIM_RAT_MODE_BUTT
};
typedef VOS_UINT8 TAF_NVIM_RAT_MODE_ENUM_UINT8;


enum TAF_NVIM_GSM_BAND_ENUM
{
    TAF_NVIM_GSM_BAND_850               = 0,
    TAF_NVIM_GSM_BAND_900,
    TAF_NVIM_GSM_BAND_1800,
    TAF_NVIM_GSM_BAND_1900,

    TAF_NVIM_GSM_BAND_BUTT
};
typedef VOS_UINT16 TAF_NVIM_GSM_BAND_ENUM_UINT16;


enum TAF_NV_ACTIVE_MODEM_MODE_ENUM
{
    TAF_NV_ACTIVE_SINGLE_MODEM              = 0x00,
    TAF_NV_ACTIVE_MULTI_MODEM               = 0x01,

    TAF_NV_ACTIVE_MODEM_MODE_BUTT
};
typedef VOS_UINT8 TAF_NV_ACTIVE_MODEM_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_XSMS_DATA_REQ_SEND_CHAN_ENUM
 枚举说明  : 短信发送的信道指示
*****************************************************************************/
enum TAF_XSMS_DATA_REQ_SEND_CHAN_ENUM
{
    TAF_XSMS_DATA_REQ_SEND_CHAN_TRAFFIC_CHAN   = 0x0,
    TAF_XSMS_DATA_REQ_SEND_CHAN_ACCESS_CHAN    = 0x1,
    TAF_XSMS_DATA_REQ_SEND_CHAN_BOTH           = 0x2,
    TAF_XSMS_DATA_REQ_SEND_CHAN_BUTT
};

typedef VOS_UINT8 TAF_XSMS_DATA_REQ_SEND_CHAN_ENUM_UINT8;

/** ****************************************************************************
 * Name        : TAF_MMA_CFREQ_LOCK_MODE_TYPE_ENUM
 *
 * Description :
 *******************************************************************************/
enum TAF_MMA_CFREQ_LOCK_MODE_TYPE_ENUM
{
    TAF_MMA_CFREQ_LOCK_MODE_OFF         = 0x00,     /* 禁止锁频功能 */
    TAF_MMA_CFREQ_LOCK_MODE_ON          = 0x01,     /* 启动锁频功能 */
    TAF_MMA_CFREQ_LOCK_MODE_BUTT        = 0x02
};
typedef VOS_UINT8 TAF_MMA_CFREQ_LOCK_MODE_TYPE_ENUM_UINT8;


enum TAF_VC_TTYMODE_ENUM
{
    TAF_VC_TTY_OFF                      = 0,
    TAF_VC_TTY_FULL                     = 1,
    TAF_VC_TTY_VCO                      = 2,
    TAF_VC_TTY_HCO                      = 3,
    TAF_VC_TTYMODE_BUTT
};
typedef VOS_UINT8 TAF_VC_TTYMODE_ENUM_UINT8;


enum TAF_CALL_CCWA_CTRL_MODE_ENUM
{
    TAF_CALL_CCWA_CTRL_BY_NW          = 0,
    TAF_CALL_CCWA_CTRL_BY_UE            = 1,

    TAF_CALL_CCWA_CTRL_MODE_BUTT
};
typedef VOS_UINT8   TAF_CALL_CCWA_CTRL_MODE_ENUM_U8;


enum TAF_CALL_CCWAI_MODE_ENUM
{
    TAF_CALL_CCWAI_MODE_DISABLE               = 0,
    TAF_CALL_CCWAI_MODE_ENABLE                = 1,

    TAF_CALL_CCWAI_MODE_BUTT
};
typedef  VOS_UINT8  TAF_CALL_CCWAI_MODE_ENUM_UINT8;


enum TAF_XSMS_TL_ACK_NEED_LEVEL_ENUM
{
    TAF_XSMS_TL_ACK_NEED_LEVEL_ALWAYS_NEEDED                    = 0,
    TAF_XSMS_TL_ACK_NEED_LEVEL_NOT_NEEDED_WHEN_RCV_SMS          = 1,  /* 当发送短信过程中，收到短信的时候，可以不判断TL_ACK */
    TAF_XSMS_TL_ACK_NEED_LEVEL_ALWAYS_NOT_NEEDED                = 2,  /* 当发送短信过程中，不需要判断TL_ACK */

    TAF_XSMS_TL_ACK_NEED_LEVEL_BUTT
};
typedef VOS_UINT8 TAF_XSMS_TL_ACK_NEED_LEVEL_ENUM_UINT8;





/*****************************************************************************
  5 STRUCT
*****************************************************************************/

typedef struct
{
    VOS_CHAR    acTz[AT_NVIM_SETZ_LEN];
}TAF_AT_TZ_STRU;


typedef struct
{
    VOS_CHAR    acErrorText[AT_NOTSUPPORT_STR_LEN];
}TAF_AT_NOT_SUPPORT_CMD_ERROR_TEXT_STRU;


typedef struct
{
    /* 该NV项的状态 0:未使能，表示不采用优先级，先激活先处理 1:使能，采用优先级算法 */
    VOS_UINT32                              ulStatus;

    /* 上行队列优先级的加权数 */
    VOS_UINT16                              ausPriWeightedNum[ADS_UL_QUEUE_SCHEDULER_PRI_MAX];
    VOS_UINT8                               aucRsv[2];
}ADS_UL_QUEUE_SCHEDULER_PRI_NV_STRU;



typedef struct
{

    VOS_UINT8    aucWifiSsid[AT_WIFI_MAX_SSID_NUM][AT_WIFI_SSID_LEN_MAX];
    VOS_UINT8    aucReserved[84];
}TAF_AT_MULTI_WIFI_SSID_STRU;


typedef struct
{
    VOS_UINT8    aucWifiAuthmode[AT_WIFI_WLAUTHMODE_LEN];
    VOS_UINT8    aucWifiBasicencryptionmodes[AT_WIFI_ENCRYPTIONMODES_LEN];
    VOS_UINT8    aucWifiWpaencryptionmodes[AT_WIFI_ENCRYPTIONMODES_LEN];
    VOS_UINT8    aucWifiWepKey1[AT_WIFI_MAX_SSID_NUM][AT_WIFI_KEY_LEN_MAX];
    VOS_UINT8    aucWifiWepKey2[AT_WIFI_MAX_SSID_NUM][AT_WIFI_KEY_LEN_MAX];
    VOS_UINT8    aucWifiWepKey3[AT_WIFI_MAX_SSID_NUM][AT_WIFI_KEY_LEN_MAX];
    VOS_UINT8    aucWifiWepKey4[AT_WIFI_MAX_SSID_NUM][AT_WIFI_KEY_LEN_MAX];
    VOS_UINT8    ucWifiWepKeyIndex[AT_WIFI_MAX_SSID_NUM];
    VOS_UINT8    aucWifiWpapsk[AT_WIFI_MAX_SSID_NUM][AT_WIFI_WLWPAPSK_LEN];
    VOS_UINT8    ucWifiWpsenbl;
    VOS_UINT8    ucWifiWpscfg;
}TAF_AT_MULTI_WIFI_SEC_STRU;


typedef struct
{
    VOS_UINT8 aucApRptSrvUrl[AT_AP_XML_RPT_SRV_URL_STR_LEN];
}TAF_AT_NVIM_AP_RPT_SRV_URL_STRU;


typedef struct
{
    VOS_UINT8 aucWebPwd[AT_WEBUI_PWD_MAX];
}TAF_AT_NVIM_WEB_ADMIN_PASSWORD_STRU;


typedef struct
{
    VOS_UINT8 aucApXmlInfoType[AT_AP_NVIM_XML_RPT_INFO_TYPE_STR_LEN];
}TAF_AT_NVIM_AP_XML_INFO_TYPE_STRU;


/*lint -e958 -e959 修改人:l60609;原因:64bit*/
typedef struct
{
    VOS_UINT32                          ulNvStatus;
    VOS_UINT8                           aucProductId[AT_PRODUCT_NAME_LENGHT];   /* product id */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_PRODUCT_ID_STRU;
/*lint +e958 +e959 修改人:l60609;原因:64bit*/

/* 巴西TIM拨号错误码NV项结构体 */

typedef struct
{
    VOS_UINT8                           ucStatus;                               /* 1: NV有效标志位，0：无效 */
    VOS_UINT8                           ucErrCodeRpt;                           /*错误码上报标志1: 0：不上报,  1：上报*/
}NAS_NV_PPP_DIAL_ERR_CODE_STRU;


typedef struct
{
    VOS_UINT8                           ucAbortEnableFlg;                           /* AT打断开关标志 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           aucAbortAtCmdStr[AT_MAX_ABORT_CMD_STR_LEN]; /* 打断AT命令名 */
    VOS_UINT8                           aucAbortAtRspStr[AT_MAX_ABORT_RSP_STR_LEN]; /* 打断命令的返回结果 */
}AT_NVIM_ABORT_CMD_PARA_STRU;


typedef struct
{
    VOS_UINT8                   ucParaNum;                                      /* 设置命令参数组数 */
    VOS_UINT8                   ucRsv[3];                                       /* 保留位 */
    VOS_INT16                   asPower[AT_NVIM_BODYSARGSM_MAX_PARA_GROUP_NUM];      /* G频段功率门限值 */
    VOS_UINT32                  aulBand[AT_NVIM_BODYSARGSM_MAX_PARA_GROUP_NUM];      /* G频段位域 */
}AT_BODYSARGSM_SET_PARA_STRU;


typedef struct
{
    VOS_UINT32                          enRightOpenFlg;
    VOS_INT8                            acPassword[AT_NVIM_RIGHT_PWD_LEN];
}TAF_AT_NVIM_RIGHT_OPEN_FLAG_STRU;


typedef struct
{
    VOS_UINT32 ulDSTotalSendFluxLow;
    VOS_UINT32 ulDSTotalSendFluxHigh;
    VOS_UINT32 ulDSTotalReceiveFluxLow;
    VOS_UINT32 ulDSTotalReceiveFluxHigh;
    TAF_AT_NVIM_RIGHT_OPEN_FLAG_STRU stRightPwd;
}NAS_NV_RABM_TOTAL_RX_BYTES_STRU;


typedef struct
{
    VOS_UINT8                          aucImei[TAF_NVIM_ITEM_IMEI_SIZE];
}IMEI_STRU;


typedef struct
{
    VOS_INT8                           acATE5DissdPwd[AT_DISSD_PWD_LEN];
}TAF_AT_NVIM_DISSD_PWD_STRU;


typedef struct
{
    VOS_INT8                           acATOpwordPwd[AT_OPWORD_PWD_LEN];
}TAF_AT_NVIM_DISLOG_PWD_NEW_STRU;


typedef struct
{
    VOS_UINT16                          usEqver;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_EQ_VER_STRU;


typedef struct
{
    VOS_UINT16                          usCsver;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_NVIM_CS_VER_STRU;


typedef struct
{
    VOS_UINT8   ucEnableFlag;
    VOS_UINT8   ucReserve;
}NAS_RABM_NVIM_FASTDORM_ENABLE_FLG_STRU;

/*****************************************************************************
 结构名称   : AT_IPV6_CAPABILITY_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : IPV6能力NV项控制结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;           /* NV有效标志, 1: 有效，0：无效 */
    VOS_UINT8                           ucIpv6Capablity;    /* IPV6能力 */
    VOS_UINT8                           aucReversed[2];     /* 四字节对齐 */

} AT_NV_IPV6_CAPABILITY_STRU;


typedef struct
{

    VOS_UINT8   ucGsmConnectRate;
    VOS_UINT8   ucGprsConnectRate;
    VOS_UINT8   ucEdgeConnectRate;
    VOS_UINT8   ucWcdmaConnectRate;
    VOS_UINT8   ucDpaConnectRate;
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   ucReserve3;
}AT_NVIM_DIAL_CONNECT_DISPLAY_RATE_STRU;

/*****************************************************************************
 结构名    : AT_TRAFFIC_CLASS_CUSTOMIZE_STRU
 结构说明  : 用于定制PDP激活请求中QoS中 Traffic Class的值的结构体
*****************************************************************************/

typedef struct
{
    VOS_UINT8                          ucStatus;                         /* 1: NV有效标志位，0：无效 */
    VOS_UINT8                          ucTrafficClass;                   /* Traffic Class的值 */
    VOS_UINT8                          ucReserve1;
    VOS_UINT8                          ucReserve2;
}AT_TRAFFIC_CLASS_CUSTOMIZE_STRU;


typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV是否激活标志,  */
    VOS_UINT8                           ucSsCmdCustomize;
    VOS_UINT8                           aucReserved1[2];
} AT_SS_CUSTOMIZE_PARA_STRU;


typedef struct
{
    VOS_UINT32 ulCimiPortCfg;
}TAF_AT_NVIM_CIMI_PORT_CFG_STRU;


typedef struct
{
    VOS_UINT32 ulMuxReportCfg;
}TAF_AT_NVIM_MUX_REPORT_CFG_STRU;


typedef struct
{
    VOS_UINT32 ulTotalMsg;
}NAS_MN_NVIM_TOTAL_MSG_STRU;


typedef struct
{
    VOS_UINT8   ucApXmlRptFlg;
    VOS_UINT8   ucReserve[3];
}TAF_AT_NVIM_AP_XML_RPT_FLG_STRU;



typedef struct
{
    VOS_UINT16                          usModemId;                              /* 该端口属于哪个modem */
    VOS_UINT8                           ucReportFlg;                            /* 该端口是否允许主动上报，VOS_TRUE为允许，VOS_FALSE为不允许，默认允许 */
    VOS_UINT8                           aucRsv[1];
}AT_NVIM_CLIENT_CONFIGURATION_STRU;


typedef struct
{
    VOS_UINT8                           aucForband[MMA_FORB_BAND_NV_MAX_SIZE];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMA_NVIM_FORBAND_STRU;



typedef struct
{
    VOS_UINT8 aucRcvData[MMA_OPERTOR_NAME_MAX_SIZE];
}NAS_MMA_NVIM_OPERATOR_NAME_STRU;


typedef struct
{
    MMA_QUICK_START_STA_UINT32          ulQuickStartSta;
}NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU;


typedef struct
{
    VOS_UINT8                           aucClassmark1[TAF_PH_WCDMA_CLASSMAEK1_LEN];
}NAS_MMA_NVIM_CLASSMARK1_STRU;


typedef struct
{
    VOS_UINT8 aucClassmark2[TAF_PH_WCDMA_CLASSMAEK2_LEN];
}NAS_MMA_NVIM_CLASSMARK2_STRU;


typedef struct
{
    VOS_UINT8 aucClassmark3[TAF_PH_WCDMA_CLASSMAEK3_LEN];
}NAS_MMA_NVIM_CLASSMARK3_STRU;


typedef struct
{
    VOS_UINT8   aucSmsServicePara[MN_MSG_SRV_PARAM_LEN];
}TAF_NVIM_SMS_SERVICE_PARA_STRU;


typedef struct
{
    VOS_UINT8   aucSmsEfsmssPara[MN_MSG_EFSMSS_PARA_LEN];
}TAF_MMA_NVIM_SMS_EFSMSS_PARA_STRU;


typedef struct
{
    VOS_UINT8   aucSmsEfsmspPara[MN_MSG_EFSMSP_PARA_LEN];
}TAF_MMA_NVIM_SMS_EFSMSP_PARA_STRU;


typedef struct
{
    VOS_UINT8  aucPwd[TAF_NVIM_ME_PERSONALISATION_PWD_LEN_MAX];
}TAF_MMA_SIM_PERSONAL_PWD_STRU;


typedef struct
{
    VOS_UINT8  aucImsiStr[TAF_NVIM_MAX_IMSI_STR_LEN];
}NAS_MMA_SIM_PERSONAL_IMST_STRU;


typedef struct
{
    VOS_UINT8                           aucDisplaySpnFlag[2];
}NAS_MMA_NVIM_DISPLAY_SPN_FLAG_STRU;


typedef struct
{
    VOS_UINT8   ucVaild;
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
    VOS_UINT8   ucReserved3;
}TAF_AT_NVIM_RXDIV_CONFIG_STRU;


/*lint -e958 -e959 修改人:l60609;原因:64bit*/
typedef struct
{
    VOS_INT8    cStatus;
    VOS_UINT8   ucEncodeType;
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
    VOS_UINT32  ulLength;
    VOS_UINT8   ucData[TAF_NVIM_MSG_ACTIVE_MESSAGE_MAX_URL_LEN];
}TAF_AT_NVIM_SMS_ACTIVE_MESSAGE_STRU;
/*lint +e958 +e959 修改人:l60609;原因:64bit*/

/*8301-8312共用结构体*/

typedef struct
{
    VOS_UINT8                           ucAuthType;
    VOS_UINT8                           aucPlmn[TAF_NVIM_MAX_NDIS_PLMN_LEN];
    VOS_UINT8                           aucPassword[TAF_NVIM_MAX_NDIS_PASSWORD_LEN_OF_AUTHDATA];
    VOS_UINT8                           aucUsername[TAF_NVIM_MAX_NDIS_USERNAME_LEN_OF_AUTHDATA];
}TAF_NVIM_NDIS_AUTHDATA_STRU;


typedef struct
{
    VOS_UINT8                           ucUsed;                                             /*0：未使用，1：使用*/
    VOS_UINT8                           aucRsv[3];
    TAF_NVIM_NDIS_AUTHDATA_STRU         stAuthData;                                         /*鉴权参数*/
}TAF_NVIM_NDIS_AUTHDATA_TABLE_STRU;

/*8451-8462共用结构体 en_NV_Item_Taf_PdpPara_0*/

typedef struct
{
    VOS_UINT8          aucPdpPara[TAF_NVIM_PDP_PARA_LEN];
}TAF_NVIM_PDP_PARA_STRU;

/* en_NV_Item_ProductName 8205 */

typedef struct
{
    VOS_UINT8          aucProductName[TAF_PH_PRODUCT_NAME_STR_LEN];
}TAF_PH_PRODUCT_NAME_STRU;

/*en_NV_Item_Imei_Svn 8337*/

typedef struct
{
    VOS_UINT8                           ucActiveFlag;
    VOS_UINT8                           aucSvn[TAF_SVN_DATA_LENGTH];
    VOS_UINT8                           aucReserve[1];
}TAF_SVN_DATA_STRU;

/*en_NV_Item_SMS_MO_RETRY_PERIOD 8293*/

typedef struct
{
    VOS_UINT8                           ucActFlg;                                           /* NVIM中该项是否激活 */
    VOS_UINT8                           ucReserved[3];
    VOS_UINT32                          ulRetryPeriod;                                      /*短信重发的周期*/
}MN_MSG_NVIM_RETRY_PERIOD_STRU;

/*en_NV_Item_SMS_MO_RETRY_INTERVAL 8294*/

typedef struct
{
    VOS_UINT8                           ucActFlg;                               /* NVIM中该项是否激活 */
    VOS_UINT8                           ucReserved[3];
    VOS_UINT32                          ulRetryInterval;                        /*短信重发的时间间隔*/
}MN_MSG_NVIM_RETRY_INTERVAL_STRU;

typedef struct
{
    VOS_UINT8                           ucSmsRetryCmSrvRejCauseNum;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucSmsRetryCmSrvRejCause[TAF_NVIM_SMS_RETRY_CAUSE_MAX_NUM];
}TAF_MSG_NVIM_RETRY_CM_SRV_REJ_CFG_STRU;


/*en_NV_Item_SMS_SEND_DOMAIN 8295*/
/* NVIM项中短信发送域的结构 */

typedef struct
{
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           ucSendDomain;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}AT_NVIM_SEND_DOMAIN_STRU;

/*en_NV_Item_WINS_Config 8297*/

typedef struct
{
    VOS_UINT8                           ucStatus;        /* 1: NV有效标志位，0：无效 */
    VOS_UINT8                           ucWins;          /* WINS使能标记: 0：Disable,  1：Enable */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}WINS_CONFIG_STRU;

/*en_NV_Item_CustomizeSimLockPlmnInfo 8267*/

typedef struct
{
    VOS_UINT8                           ucMncNum;
    VOS_UINT8                           aucRangeBegin[TAF_PH_SIMLOCK_PLMN_STR_LEN];
    VOS_UINT8                           aucRangeEnd[TAF_PH_SIMLOCK_PLMN_STR_LEN];
}TAF_CUSTOM_SIM_LOCK_PLMN_RANGE_STRU;


typedef struct
{
    VOS_UINT32                          ulStatus;/*是否激活，0不激活，1激活 */
    TAF_CUSTOM_SIM_LOCK_PLMN_RANGE_STRU astSimLockPlmnRange[TAF_MAX_SIM_LOCK_RANGE_NUM];
}TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU;

/* en_NV_Item_CardlockStatus 8268 */

typedef struct
{
    VOS_UINT32                          ulStatus;            /*是否激活，0不激活，1激活 */
    VOS_UINT32                          ulCardlockStatus;    /**/
    VOS_UINT32                          ulRemainUnlockTimes; /*解锁剩余次数*/
}TAF_NVIM_CUSTOM_CARDLOCK_STATUS_STRU;

/*en_NV_Item_CustomizeSimLockMaxTimes 8269*/

typedef struct
{
    VOS_UINT32                          ulStatus;            /*是否激活，0不激活，1激活 */
    VOS_UINT32                          ulLockMaxTimes;
}TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU;

/*en_NV_Item_CCA_TelePara 8230*/

/*为了与V1R1NV配匹，前15个字节保留*/
typedef struct
{
    VOS_UINT8               aucRsv[15];              /*NV项的结构中，4字节对齐方式下有空洞要手动补齐*/
    VOS_UINT8               ucS0TimerLen;
} TAF_CCA_TELE_PARA_STRU;

/*en_NV_Item_PS_TelePara 8231*/

typedef struct
{
    VOS_UINT8         AnsMode;
    VOS_UINT8         AnsType;
    VOS_UINT16        ClientId;
}TAF_APS_NVIM_PS_ANS_MODE_STRU;

/*en_NV_Item_User_Set_Freqbands 8265*/
/*获取band值，从MS的RACIEZ中获得*/
/*
  80（CM_BAND_PREF_GSM_DCS_1800）              GSM DCS systems
  100（CM_BAND_PREF_GSM_EGSM_900）             Extended GSM 900
  200（CM_BAND_PREF_GSM_PGSM_900）             Primary GSM 900
  100000（CM_BAND_PREF_GSM_RGSM_900）          GSM Railway GSM 900
  200000（CM_BAND_PREF_GSM_PCS_1900）          GSM PCS
  400000（CM_BAND_PREF_WCDMA_I_IMT_2000）      WCDMA IMT 2000
  3FFFFFFF（CM_BAND_PREF_ANY）                 任何频带
  40000000（CM_BAND_PREF_NO_CHANGE）           频带不变化
*/

typedef struct
{
    VOS_UINT32 ulBandLow; /*低32位*/
    VOS_UINT32 ulBandHigh;/*高32位*/
} TAF_MMA_NVIM_USER_SET_PREF_BAND64;


typedef struct
{
    VOS_UINT16                          usReportRegActFlg;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NVIM_REPORT_REG_ACT_FLG_STRU;


typedef struct
{
    VOS_UINT16                          usMePersonalActFlag;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMA_ME_PERSONAL_ACT_FLAG_STRU;


typedef struct
{
    VOS_UINT8                           ucCbStatus;         /* CBS业务是否启用标志*/

    VOS_UINT8                           ucDupDetectCfg;     /* 重复过滤配置 */

    VOS_UINT8                           ucRptAppFullPageFlg; /* VOS_TRUE: 上报整页共88个字节; VOS_FALSE: 上报实际有效字节 */

    VOS_UINT8                           ucRsv;              /* NV项相关的结构体，在4字节方式下，需手动补齐空洞 */
}TAF_CBA_NVIM_CBS_SERVICE_PARM_STRU;


typedef struct
{
    VOS_UINT32                          ulCommDebugFlag;
}TAF_AT_NVIM_COMMDEGBUG_CFG_STRU;


typedef struct
{
    AT_UART_LINK_TYPE_ENUM_UINT16       enUartLinkType;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NVIM_DEFAULT_LINK_OF_UART_STRU;


typedef struct
{
    VOS_UINT8 aucMfrId[TAF_MAX_MFR_ID_STR_LEN];
}TAF_PH_FMR_ID_STRU;


typedef struct
{
    VOS_UINT8 aucOperatorName[NAS_MMA_NVIM_OPERATOR_NAME_LEN];
}NAS_MMA_OPERATOR_NAME_STRU;


typedef struct
{
    VOS_UINT8                           aucFactInfo1[AT_FACINFO_INFO1_STR_LENGTH];
    VOS_UINT8                           aucFactInfo2[AT_FACINFO_INFO2_STR_LENGTH];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NVIM_FACTORY_INFO_STRU;


typedef struct
{
    VOS_UINT8                           aucMDate[AT_MDATE_STRING_LENGTH];
}TAF_AT_NVIM_MANUFACTURE_DATE_STRU;


typedef struct
{
    VOS_UINT16                          usPcVoiceSupportFlag; /*Range:[0,1]*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}APP_VC_NVIM_PC_VOICE_SUPPORT_FLAG_STRU;




typedef struct
{
    MN_MSG_ME_STORAGE_STATUS_ENUM_UINT8 enMeStorageStatus;                      /* ME存储短信功能是否启用标志*/
    VOS_UINT8                           aucReserve[1];                          /* NV项相关的结构体，在4字节方式下，需手动补齐空洞 */
    VOS_UINT16                          usMeStorageNum;                         /* ME存储短信容量 */
}MN_MSG_ME_STORAGE_PARM_STRU;

typedef struct
{
    VOS_UINT32      ulDSLastLinkTime;                       /*DS最近一次连接时间*/
    VOS_UINT32      ulDSTotalSendFluxLow;                   /*DS累计发送流量低四个字节*/
    VOS_UINT32      ulDSTotalSendFluxHigh;                  /*DS累计发送流量高四个字节*/
    VOS_UINT32      ulDSTotalLinkTime;                      /*DS累计连接时间*/
    VOS_UINT32      ulDSTotalReceiveFluxLow;                /*DS累计接收流量低四个字节*/
    VOS_UINT32      ulDSTotalReceiveFluxHigh;               /*DS累计接收流量高四个字节*/

} TAF_APS_DSFLOW_NV_STRU;


typedef struct
{
    VOS_UINT8                           ucActFlg;/* MN_MSG_NVIM_ITEM_ACTIVE */
    VOS_UINT8                           aucReserved[3];
}MN_MSG_DISCARD_DELIVER_MSG_STRU;

typedef struct
{
    VOS_UINT8                           ucActFlg;/* MN_MSG_NVIM_ITEM_ACTIVE */
    VOS_UINT8                           aucReserved[3];
}MN_MSG_REPLACE_DELIVER_MSG_STRU;


typedef struct
{
    VOS_UINT8       ucDsFlowStatsRptCtrl;                   /* 标识是否进行流量上报 */
    VOS_UINT8       ucDsFlowStatsSave2NvCtrl;               /* 标识是否需要保存历史流量信息到NV中 */
    VOS_UINT8       ucDsFlowSavePeriod;                     /* 流量写NV的周期 */
    VOS_UINT8       aucReserve[1];                          /* 保留位*/
} TAF_APS_DSFLOW_STATS_CTRL_NV_STRU;


typedef struct
{
    VOS_UINT8                           ucRatOrderNum;                          /* syscfgex中设置的acqoder中的指示个数 */
    VOS_UINT8                           aenRatOrder[TAF_PH_NVIM_MAX_GUL_RAT_NUM];    /* at^syscfgex中设置的acqoder的顺序 */
}TAF_PH_NVIM_RAT_ORDER_STRU;


typedef struct
{
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           aucReserved[3];
}MN_MSG_NVIM_MO_SMS_CTRL_STRU;



typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;                        /* en_NV_Item_PDP_Actving_Limit NV项是否激活，VOS_TRUE:激活；VOS_FALSE:未激活 */
    VOS_UINT8                           ucReserved1;                            /* 保留 */
    VOS_UINT8                           ucReserved2;                            /* 保留 */
    VOS_UINT8                           ucReserved3;                            /* 保留 */
}TAF_APS_NVIM_PDP_ACT_LIMIT_STRU;

typedef struct
{
    VOS_UINT8                           ucCategory;                             /* 紧急呼号码类型 */
    VOS_UINT8                           ucValidSimPresent;                      /* 紧急呼号码是有卡时有效还是无卡时有效，1有卡时有效，0无卡时有效 */
    VOS_UINT8                           ucAbnormalServiceFlg;                   /* 紧急呼号码有卡时是否仅在非正常服务时有效，0:任何服务时均有效，1:仅非正常服务时有效 */
    VOS_UINT8                           ucEccNumLen;
    VOS_UINT8                           aucEccNum[MN_CALL_NVIM_MAX_BCD_NUM_LEN];
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
} MN_CALL_NVIM_CUSTOM_ECC_NUM_STRU;



typedef struct
{
    VOS_UINT8                           ucEccNumCount;
    VOS_UINT8                           aucReserve[3];
    MN_CALL_NVIM_CUSTOM_ECC_NUM_STRU    astCustomEccNumList[MN_CALL_NVIM_MAX_CUSTOM_ECC_NUM];
} MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU;


typedef struct
{
    VOS_UINT8                           ucBufferCcProtectTimerLen;              /* 0: 域选择时不进行缓存；大于0: 缓存CC服务的保护定时器时长，单位 秒 */
    VOS_UINT8                           ucBufferSmsProtectTimerLen;             /* 0: 域选择时不进行缓存；大于0: 缓存SMS服务的保护定时器时长，单位 秒 */
    VOS_UINT8                           ucBufferSsProtectTimerLen;              /* 0: 域选择时不进行缓存；大于0: 缓存SS服务的保护定时器时长，单位 秒 */
    VOS_UINT8                           ucReserve1;
}TAF_NVIM_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG_STRU;




typedef struct
{
    VOS_UINT8                           ucSimCallCtrlSupportFlg;                /* SIM卡Call Control业务*/
    VOS_UINT8                           ucReserved1;                            /* 保留*/
    VOS_UINT8                           ucReserved2;                            /* 保留*/
    VOS_UINT8                           ucReserved3;                            /* 保留*/
}MN_CALL_NVIM_SIM_CALL_CONTROL_FLG_STRU;

typedef struct
{
    VOS_UINT8                           ucCallDeflectionSupportFlg;             /* 支持呼叫偏转业务*/
    VOS_UINT8                           ucReserved1;                            /* 保留*/
    VOS_UINT8                           ucReserved2;                            /* 保留*/
    VOS_UINT8                           ucReserved3;                            /* 保留*/
}MN_CALL_NVIM_CALL_DEFLECTION_SUPPORT_FLG_STRU;

typedef struct
{
    VOS_UINT8                           ucAlsSupportFlg;                        /* 支持线路切换业务*/
    VOS_UINT8                           ucReserved1;                            /* 保留*/
    VOS_UINT8                           ucReserved2;                            /* 保留*/
    VOS_UINT8                           ucReserved3;                            /* 保留*/
}MN_CALL_NVIM_ALS_SUPPORT_FLG_STRU;

typedef struct
{
    VOS_UINT8                           ucGetCsmpParaFromUsimSupportFlg;        /*从(U)SIM卡中读取CSMP参数*/

    VOS_UINT8                           ucGetScAddrIgnoreScIndication; /* 0x6f42文件中sc indication指示不存在短信中心号码时，如果短信中心号码合法是否读取，
                                                                       VOS_FALSE:sc indication指示短信中心号码不存在则不读取短信中心号码；
                                                                       VOS_TRUE: sc indication指示短信中心号码不存在读取短信中心号码 */
}MN_MSG_GET_CSMP_PARA_FROM_USIM_SUPPORT_FLG_STRU;

typedef struct
{
    VOS_UINT8                           ucSmsPpDownlodSupportFlg;               /*表明是否支持短信的PP-DOWNLOAD功能*/
    VOS_UINT8                           ucReserved1;                            /* 保留*/
    VOS_UINT8                           ucReserved2;                            /* 保留*/
    VOS_UINT8                           ucReserved3;                            /* 保留*/
}MN_MSG_SMS_PP_DOWNLOAD_SUPPORT_FLG_STRU;

typedef struct
{
    VOS_UINT8                           ucSmsNvSmsRexitSupportFlg;              /*服务域设置为PS ONLY时，是否支持CS域短信和呼叫业务(紧急呼叫除外) */
    VOS_UINT8                           ucReserved1;                            /* 保留*/
    VOS_UINT8                           ucReserved2;                            /* 保留*/
    VOS_UINT8                           ucReserved3;                            /* 保留*/
}MN_MSG_SMS_NVIM_SMSREXIST_SUPPORT_FLG_STRU;


typedef struct
{
    VOS_UINT8                           ucSmsStatusInEfsmsSupportFlg;           /* 表明NVIM中是否能保存短信状态报告*/
    VOS_UINT8                           ucReserved1;                            /* 保留*/
    VOS_UINT8                           ucReserved2;                            /* 保留*/
    VOS_UINT8                           ucReserved3;                            /* 保留*/
}MN_MSG_SMS_STATUS_IN_EFSMS_SUPPORT_FLG_STRU;





typedef struct
{
    VOS_UINT8                           ucCodecTypeNum;
    VOS_UINT8                           aucCodecType[MN_CALL_NVIM_BC_MAX_SPH_VER_NUM];
    VOS_UINT8                           ucReserve;
}MN_CALL_NIMV_ITEM_CODEC_TYPE_STRU;



typedef struct
{
    VOS_UINT32       ulMeStatus;
}TAF_FDN_NVIM_CONFIG_STRU;


typedef struct
{
    VOS_UINT8                           ucVoiceCallNotSupportedCause;
    VOS_UINT8                           ucVideoCallNotSupportedCause;
    VOS_UINT8                           aucReserved1[2];
}TAF_CALL_NVIM_CALL_NOT_SUPPORTED_CAUSE_STRU;



typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;                        /* en_NV_Item_Network_Selection_Menu_Ctrl_Para NV项是否激活，VOS_TRUE:激活；VOS_FALSE:未激活 */
    VOS_UINT8                           ucReserved;                             /* 保留 */
}TAF_MMA_NVIM_REPORT_PLMN_SUPPORT_FLG_STRU;

	
typedef struct
{
    VOS_UINT8                           ucNotDisplayLocalNetworkNameFlg;
    VOS_UINT8                           ucReserved;
}TAF_MMA_NOT_DISPLAY_LOCAL_NETWORKNAME_NVIM_STRU;


typedef struct
{
    VOS_UINT8                           ucActFlag;
    VOS_UINT8                           enMtCustomize;
    VOS_UINT8                           aucReserved1[2];
}MN_MSG_MT_CUSTOMIZE_INFO_STRU;



typedef struct
{
    VOS_UINT8  ucCnt;
    VOS_UINT8  aucUmtsCodec[MN_CALL_MAX_UMTS_CODEC_TYPE_NUM];
} MN_CALL_UMTS_CODEC_TYPE_STRU;

typedef struct
{
    VOS_UINT8                           ucStatus;/*是否激活，0不激活，1激活 */
    VOS_UINT8                           ucCardLockPerm;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}MMA_CUSTOM_CARDLOCK_PERM_STRU;


typedef struct
{
    VOS_UINT16                          usMsgIdFrom;                            /*Cell broadcast message id value range from  */
    VOS_UINT16                          usMsgIdTo;                              /*Cell broadcast message id value range to    */
}TAF_CBA_NVIM_ETWS_MSGID_RANGE_STRU;

typedef struct
{
    VOS_UINT8                                               ucEnhDupDetcFlg;    /* DoCoMo增强的重复检测定制特性，对ETWS主从通知的增强的重复检测特性是否激活, VOS_TRUE:激活,VOS_FALSE:未激活.
                                                                                        1. 主从通知,包括普通CBS消息, 重复检测时需要判断PLMN
                                                                                        2. 主从通知,包括普通CBS消息, 重复检测的时长需根据当前PLMN的MCC进行推算
                                                                                        3. ETWS消息和普通CBS消息按相同的规则做重复过滤和时效检测 */
    VOS_UINT8                                               ucRsv;

    VOS_UINT16                                              usNormalTimeLen;   /* 单位:分钟, 定制特性未激活时使用此有效时长 */

    VOS_UINT16                                              usSpecMccTimeLen;  /* 单位:分钟, 增强的重复检测定制特性激活时主/从通知/CBS的MCC在指定Mcc中则使用此有效时长 */
    VOS_UINT16                                              usOtherMccTimeLen; /* 单位:分钟, 增强的重复检测定制特性激活时主/从通知/CBS的MCC不在指定Mcc中则使用此有效时长 */
    VOS_UINT32                                              aulSpecMcc[TAF_CBA_NVIM_MAX_ETWS_DUP_DETECT_SPEC_MCC_NUM];  /* 增强的重复检测定制特性相关的MCC */
}TAF_CBA_NVIM_ETWS_DUP_DETC_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucReportEccNumFlg;                      /* 1:支持向APP上报紧急呼号码, 0:不支持向APP上报紧急呼号码*/
    VOS_UINT8                           ucReserved1;                            /* 保留*/
    VOS_UINT8                           ucReserved2;                            /* 保留*/
    VOS_UINT8                           ucReserved3;                            /* 保留*/
}MN_CALL_NVIM_REPORT_ECC_NUM_SUPPORT_FLG_STRU;



typedef struct
{
    VOS_UINT8                           ucStatus;/*是否激活，0不激活，1激活 */
    MN_CALL_STATE_ENUM_UINT8            enCardLockOperator;
    VOS_UINT8                           ucReserved1;                            /* 保留*/
    VOS_UINT8                           ucReserved2;                            /* 保留*/
}MMA_CUSTOM_CARDLOCK_OPERATOR_STRU;


typedef struct
{
    VOS_UINT8                           ucStatus;                               /* 1: NV有效标志位，0：无效 */
    VOS_UINT8                           ucVpCfgState;                           /* 当前NV配置值 */
}MN_CALL_NV_ITEM_VIDEO_CALL_STRU;


typedef struct
{
    VOS_UINT8                           ucActFlg;                               /* NVIM中该项是否激活 */
    VOS_UINT8                           enClass0Tailor;
}MN_MSG_NVIM_CLASS0_TAILOR_STRU;
/* 终端可配置需求: 2G拨号请求禁止Spare_bit3等参数 */
typedef struct
{
    VOS_UINT8                           ucStatus;       /* 1: NV有效标志位，0：无效 */
    VOS_UINT8                           ucDisable2GBit3;
    VOS_UINT8                           ucReserved1;                            /* 保留*/
    VOS_UINT8                           ucReserved2;                            /* 保留*/
}APS_2G_DISABLE_BIT3_CUSTOMIZE_STRU;


typedef struct
{
    VOS_UINT16                          usMultiSimCallConf;                             /*o为语音被叫时上报，1语音被叫时不上报*/
    VOS_UINT8                           ucReserved1;                            /* 保留*/
    VOS_UINT8                           ucReserved2;                            /* 保留*/
}MN_CALL_NV_ITEM_MULTISIM_CALLCON_STRU;



typedef struct
{
    VOS_UINT8                           ucStatus;        /* 1: NV有效标志位，0：无效 */
    VOS_UINT8                           ucUssdTransMode;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_USSD_NVIM_TRANS_MODE_STRU;


typedef struct
{
    VOS_UINT8                           ucCallRedialCmSrvRejCauseNum;                                   /* 重拨原因值个数 */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucCallRedialCmSrvRejCause[TAF_NVIM_CALL_REDIAL_CAUSE_MAX_NUM]; /* 重拨原因值 */
}TAF_CALL_REDIAL_CM_SRV_REJ_CFG_STRU;



typedef struct
{
    VOS_UINT8                           ucCallRedialSupportFlg;     /* 支持呼叫重建功能标志，VOS_TRUE:支持；VOS_FALSE:不支持*/
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT32                          ulCallRedialPeriod;         /* 呼叫重建特性打开时，呼叫重建最大时长，单位毫秒 */
    VOS_UINT32                          ulCallRedialInterval;       /* 呼叫重建特性打开时，呼叫重拨间隔单位毫秒 */
}MN_CALL_REDIAL_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucEcallT9Len;                /* T9时长定时器时长，单位为小时，1~12小时 */
    VOS_UINT8                           ucEcallRedialSupportFlg;   /* 支持eCall重建功能标志，VOS_TRUE:支持；VOS_FALSE:不支持*/
    VOS_UINT8                           aucReserved1[2];
    VOS_UINT16                          usEcallRedialPeriod;         /* eCall重建特性打开时，eCall重建最大时长，单位毫秒 */
    VOS_UINT16                          usEcallRedialInterval;       /* eCall重建特性打开时，eCall重拨间隔单位毫秒 */
}TAF_CALL_NVIM_ECALL_CFG_STRU;



typedef struct
{
    VOS_INT16                           sHandSetVolValue;
    VOS_INT16                           sHandsFreeVolValue;
    VOS_INT16                           sCarFreeVolValue;
    VOS_INT16                           sEarphoneVolValue;
    VOS_INT16                           sBlueToothVolValue;
    VOS_INT16                           sPcVoiceVolValue;
    VOS_INT16                           sHeadPhoneVolValue;
    VOS_INT16                           sSuperFreeVolValue;
    VOS_INT16                           sSmartTalkVolValue;
    VOS_INT16                           sPreVolume;
    VOS_UINT16                          usCurrDevMode;
    VOS_UINT16                          usPreDevMode;
    VOS_UINT16                          usSetVoiceFlg;                          /*设置DEV或Vol的过程中flag，确保多modem只有一个在设置过程中*/
    VOS_INT16                           sRsv[3];
} APP_VC_NV_CLVL_VOLUME_STRU;

/* 终端可配置需求: 单板默认APN设置 */
typedef struct
{
    VOS_UINT8   ucStatus;       /* 1: NV有效标志位，0：无效 */
    VOS_UINT8   aucApn[TAF_NVIM_MAX_APN_STR_LEN];       /* APN从该数组的第一个字节开始写入，并且以'\0'作为结尾 */
    VOS_UINT8   aucRsv[3];
}APS_APN_CUSTOMIZE_STRU;


typedef struct
{
    VOS_UINT8                                               ucEtwsEnableFlg;    /* ETWS特性开关, VOS_TRUE:开启, VOS_FALSE:未开启 */
    VOS_UINT8                                               ucRsv;
    VOS_UINT16                                              usTempEnableCbsTimeLen; /* 单位:分钟, CBS功能未开启时,收到主通知后临时使能CBS以接收从通知的时长 */

    TAF_CBA_NVIM_ETWS_DUP_DETC_CFG_STRU                     stDupDetcCfg;       /* TAF_CBA_NV_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM Duplication Detection Time 配置项 */
    TAF_CBA_NVIM_ETWS_MSGID_RANGE_STRU                      astSpecEtwsMsgIdList[TAF_CBA_NV_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM];   /* 用户定制的ETWS消息ID范围 */
}TAF_CBA_NVIM_ETWS_CFG_STRU;


typedef struct
{
    VOS_UINT8                           enAlsLine;
    VOS_UINT8                           aucMmaImsi[9];
}MN_CALL_ALS_LINE_INFO_STRU;


typedef struct
{
    VOS_UINT8                          aucAtClientConfig[TAF_AT_NVIM_CLIENT_CONFIG_LEN];
}TAF_AT_NVIM_AT_CLIENT_CONFIG_STRU;


typedef struct
{
    VOS_UINT8                           ucECallNotifySupport;                   /* 紧急呼叫与温度保护交互NV项 */
    VOS_UINT8                           ucSpyStatusIndSupport;                  /* 温保状态上报使能NV项 */
    VOS_UINT8                           aucReserved[2];                          /* 保留项 */
}TAF_TEMP_PROTECT_CONFIG_STRU;


typedef struct
{
    VOS_UINT8                           ucNetSelMenuFlg;                        /* 网络选择菜单控制，VOS_TRUE:激活；VOS_FALSE:未激活 */
    VOS_UINT8                           ucRatBalancingFlg;                      /* 接入技术平衡控制，VOS_TRUE:激活；VOS_FALSE:未激活 */
    VOS_UINT8                           aucReserved[2];                         /* 保留 */
}NVIM_ATT_ENS_CTRL_STRU;


typedef struct
{
    VOS_UINT32                          aulUserSetLtebands[2];
}TAF_NVIM_USER_SET_LTEBANDS_STRU;


typedef struct
{
    VOS_UINT32                          ulDSTotalSendFluxLow;
    VOS_UINT32                          ulDSTotalSendFluxHigh;
    VOS_UINT32                          ulDSTotalReceiveFluxLow;
    VOS_UINT32                          ulDSTotalReceiveFluxHig;
}TAF_NVIM_RABM_TOTAL_RX_BYTES_STRU;


typedef struct
{
    VOS_UINT8                           aucRoamWhiteListFlag[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_NVIM_E5_ROAM_WHITE_LIST_SUPPORT_FLG_STRU;


typedef struct
{
    VOS_UINT32                         ulNdisDialUpAdd;
}TAF_NVIM_NDIS_DIALUP_ADDRESS_STRU;

/*nv 9130, 为ipv6项目新增nv预留*/

typedef struct
{
    VOS_UINT32                          ulActiveFlag;
    VOS_UINT8                           aucSmCause[TAF_NV_IPV6_FALLBACK_EXT_CAUSE_MAX_NUM];

} TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU;


typedef struct
{
    VOS_UINT32                          ulIpv6RouterMtu;
}TAF_NDIS_NV_IPV6_ROUTER_MTU_STRU;


typedef struct
{
    VOS_INT32                           lValue;
    VOS_INT8                            acPassword[16];
}TAF_AT_NV_DISLOG_PWD_STRU;


typedef struct
{
    VOS_UINT32                          ulE5RightFlag;
}TAF_AT_NV_E5_RIGHT_FLAG_STRU;


typedef struct
{
    VOS_UINT32                          ulDissdFlag;
}TAF_AT_NV_DISSD_FLAG_STRU;


typedef struct
{
    VOS_UINT32                          ulOmPortNum;
}TAF_AT_NV_OM_PORT_NUM_STRU;


typedef struct
{
    VOS_UINT8                           ucLength;
    VOS_UINT8                           aucData[53];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_RA_CAPABILITY_STRU;


typedef struct
{
    VOS_UINT8                           aucUmtsAuth[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_UMTS_AUTH_STRU;


typedef struct
{
    VOS_UINT8                           aucGmmInfo[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_GMM_INFO_STRU;


typedef struct
{
    VOS_UINT8                           aucMmInfo[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_MM_INFO_STRU;


typedef struct
{
    VOS_UINT8                           aucSmsText[16];
}TAF_AT_NV_SMS_TEXT_STRU;


typedef struct
{
    VOS_UINT32                          ulStatus;
    VOS_UINT32                          ulGprsRecentActTime;
}TAF_AT_NV_CUSTOM_GPRS_RECENT_ACT_TIMER_STRU;


typedef struct
{
    VOS_UINT16                          usPsDelayFlag;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_PS_DELAY_FLAG_STRU;


typedef struct
{
    VOS_UINT8                           aucEhplmnSupportFlag[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_EHPLMN_SUPPORT_FLAG_STRU;


typedef struct
{
    VOS_UINT8                          aucBgFsFbsRatio[4];
}TAF_AT_NV_BG_FS_FBS_RATIO_STRU;


typedef struct
{
    VOS_UINT16                          usEplmnUseRatFlag;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_EPLMN_USE_RAT_FLAG_STRU;

typedef struct
{
    VOS_UINT8                                               ucLabel[TAF_NVIM_CBA_MAX_LABEL_NUM]; /* 小区广播消息id范围标签 */
    VOS_UINT16                                              usMsgIdFrom;                    /* 小区广播消息ID的开始序号  */
    VOS_UINT16                                              usMsgIdTo;                      /* 小区广播消息ID的结束序号 */
    VOS_UINT32                                              ulRcvMode;                      /* 每个CBMI RANGE 的接收模式, 目前仅支持 ACCEPT的模式 */
}TAF_CBA_NVIM_CBMI_RANGE_STRU;

typedef struct
{
    VOS_UINT32                          ulCbmirNum;                             /* 小区广播消息的ID个数 */
    TAF_CBA_NVIM_CBMI_RANGE_STRU        astCbmiRangeInfo[TAF_CBA_NVIM_MAX_CBMID_RANGE_NUM]; /* 小区广播消息的范围信息 */
}TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU;



typedef struct
{
    VOS_UINT16                          usPlatform;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NVIM_PLATFORM_STRU;


typedef struct
{
    VOS_UINT8                           ucMuxSupportFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_AT_NVIM_MUX_SUPPORT_FLG_STRU;

/*控制USSD转换字符表*/
typedef struct
{
    VOS_UINT8                           ucStatus;            /*是否激活，0不激活，1激活 */
    VOS_UINT8                           ucAlphaTransMode;    /* 字符表转换*/
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}SSA_NV_ITEM_ALPHA_to_ASCII_STRU;


typedef struct
{
    VOS_UINT8                           ucCbStatus;         /* CBS业务是否启用标志*/

    VOS_UINT8                           ucDupDetectCfg;     /* 重复过滤配置 */


    VOS_UINT8                           ucRptAppFullPageFlg; /* VOS_TRUE: 上报整页共88个字节; VOS_FALSE: 上报实际有效字节 */

    VOS_UINT8                           ucRsv;              /* NV项相关的结构体，在4字节方式下，需手动补齐空洞 */
}TAF_CBA_CBS_SERVICE_PARM_STRU;


typedef struct
{
    MTA_WCDMA_BAND_ENUM_UINT16          enBand;                     /* WCDMA频段 */
    VOS_INT16                           sPower;                     /* 功率门限值 */
}MTA_BODY_SAR_W_PARA_STRU;


typedef struct
{
    VOS_INT16                           sGPRSPower;                 /* GPRS功率门限值 */
    VOS_INT16                           sEDGEPower;                 /* EDGE功率门限值 */
}MTA_BODY_SAR_G_PARA_STRU;


typedef struct
{
    VOS_UINT32                          ulGBandMask;                                /* GSM Band的Mask位 */
    VOS_UINT16                          usWBandNum;                                 /* WCDMA的Band个数 */
    VOS_UINT16                          ausReserved1[1];                            /* 保留位 */
    MTA_BODY_SAR_G_PARA_STRU            astGBandPara[MTA_BODY_SAR_GBAND_MAX_NUM];   /* GSM功率门限值 */
    MTA_BODY_SAR_W_PARA_STRU            astWBandPara[MTA_BODY_SAR_WBAND_MAX_NUM];   /* WCDMA功率门限值 */
}MTA_BODY_SAR_PARA_STRU;

typedef struct
{
    VOS_UINT32  ulNvStatus;
    VOS_UINT8   aucFirstPortStyle[17];   /* 设备切换前端口形态 */
    VOS_UINT8   aucRewindPortStyle[17];  /* 设备切换后端口形态 */
    VOS_UINT8   aucReserved[22];         /* 保留 */
}AT_DYNAMIC_PID_TYPE_STRU;


typedef struct
{
    VOS_UINT8                           ucEnableFlag;       /* 是否使能Share PDP特性, 0 - 禁止;  1 - 使能 */
    VOS_UINT8                           ucReserved;         /* 保留 */
    VOS_UINT16                          usAgingTimeLen;     /* 老化时间，单位为秒 */

} TAF_NVIM_SHARE_PDP_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucEnableFlag;  /* AT+CFUN=0软关机，去激活(U)SIM卡功能使能标识, 0 - 禁止, 1 - 使能*/
    VOS_UINT8                           aucReserved[3];
} TAF_NVIM_DEACT_SIM_WHEN_POWEROFF_STRU;

/* 下移到MSCC module */


typedef struct
{
    VOS_UINT32                          bitCardNum      : 3;
    VOS_UINT32                          bitReserved0    : 5;
    VOS_UINT32                          bitCard0        : 3;
    VOS_UINT32                          bitCard1        : 3;
    VOS_UINT32                          bitCard2        : 3;
    VOS_UINT32                          bitReserved1    : 15;
} TAF_NV_SCI_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucNvimValid;
    VOS_UINT8                           ucSmsClosePathFlg;
} TAF_NVIM_SMS_CLOSE_PATH_CFG_STRU;



typedef struct
{
    /* 位操作 :0不激活；1:激活
    bit0：中移动双待下B39/B3干扰冲突策略
    bit1：Notch Bypass特性开关
    bit2: NarrowBand Dcs 控制(V9 not support)
    bit3: B39/B3 干扰冲突策略2(G射频优先模式)
    bit4: RES 使能开关，1表示支持RSE特性，0表示不支持RSE特性
    */
    VOS_UINT8                          ucSolutionMask;
    VOS_UINT8                          aucAdditonCfg[3];
} MTC_NV_RF_INTRUSION_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucVsimCtrlFlg;
    VOS_UINT8                           aucReserved1;
    VOS_UINT8                           aucReserved2;
    VOS_UINT8                           aucReserved3;
} TAF_NVIM_VSIM_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucIsSsRetrySupportFlg;                  /* 是否支持ss重发功能，VOS_TRUE:支持；VOS_FALSE:不支持*/
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT32                          ulSsRetryPeriod;                        /* ss重发特性打开时，ss重发最大时长，单位秒,默认30s */
    VOS_UINT32                          ulSsRetryInterval;                      /* ss重发特性打开时，ss重发间隔单位秒，默认5s */
}TAF_SSA_NVIM_RETRY_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucSsRetryCmSrvRejCauseNum;                                      /* ss重发原因值个数*/
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT8                           aucSsRetryCmSrvRejCause[TAF_NVIM_SS_RETRY_CAUSE_MAX_NUM];       /* ss重发原因 */
}TAF_SSA_NVIM_RETRY_CM_SRV_REJ_CFG_STRU;



typedef struct
{
    VOS_UINT32                          ulSmsRiOnInterval;      /* 短信RI高电平持续时间(ms) */
    VOS_UINT32                          ulSmsRiOffInterval;     /* 短信RI低电平持续时间(ms) */

    VOS_UINT32                          ulVoiceRiOnInterval;    /* 语音RI高电平持续时间(ms) */
    VOS_UINT32                          ulVoiceRiOffInterval;   /* 语音RI低电平持续时间(ms) */
    VOS_UINT8                           ucVoiceRiCycleTimes;    /* 语音RI波形周期次数     */
    VOS_UINT8                           aucReserved[3];

} TAF_NV_UART_RI_STRU;


typedef struct
{
    VOS_UINT8                           ucFormat;               /* UART 数据位停止位位宽 */
    VOS_UINT8                           ucParity;               /* UART校验方式 */
    VOS_UINT8                           aucReserved[2];

} TAF_NV_UART_FRAME_STRU;


typedef struct
{
    VOS_UINT32                          ulBaudRate;             /* UART波特率 */
    TAF_NV_UART_FRAME_STRU              stFrame;                /* UART帧格式 */
    TAF_NV_UART_RI_STRU                 stRiConfig;             /* UART Ring脚配置 */

} TAF_NV_UART_CFG_STRU;


typedef struct
{
    VOS_UINT32                          ulDlRate;
    VOS_UINT32                          ulUlRate;
    VOS_UINT32                          ulDdrBand;
} TAF_NV_DFS_RATE_BAND_STRU;


typedef struct
{
    VOS_UINT32                          ulProfileNum;
    TAF_NV_DFS_RATE_BAND_STRU           astProfile[TAF_NVIM_DFS_MAX_PROFILE_NUM];
} TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU;

typedef struct
{
    TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU          astDfsConfig[TAF_NVIM_DIFF_DFS_NUM];
} TAF_NV_MULTI_DFS_DSFLOW_RATE_CONFIG_STRU;


typedef struct
{
    VOS_UINT32                          ulFlagValue;
    VOS_UINT32                          ulReserved;
} TAF_NV_VOICE_TEST_FLAG_STRU;


typedef struct
{
    VOS_UINT8                          ucSmsDomain;
    VOS_UINT8                          aucReserved[3];
} TAF_NVIM_SMS_DOMAIN_STRU;



typedef struct
{
    VOS_UINT8                           ucEnableFlg;
    VOS_UINT8                           aucReserved[3];
} TAF_NV_PORT_BUFF_CFG_STRU;



typedef struct
{
    VOS_UINT8                                     ucLCEnableFlg;
    TAF_NVIM_LC_RAT_COMBINED_ENUM_UINT8           enRatCombined;
    TAF_NVIM_LC_WORK_CFG_ENUM_UINT8               enLCWorkCfg;
    VOS_UINT8                                     aucReserved[1];
}TAF_NV_LC_CTRL_PARA_STRU;


typedef struct
{
    VOS_UINT8                 ucImsRedialCauseNum;                                                  /* IMS call重拨原因值个数 */
    VOS_UINT8                 ucImsaRedialCauseNum;                                                 /* IMSA call重拨原因值个数 */
    VOS_UINT8                 aucReserve[2];
    VOS_UINT16                ausImsRedialCause[TAF_NVIM_IMS2CS_CALL_REDIAL_CAUSE_MAX_NUM];
    VOS_UINT16                ausImsaRedialCause[TAF_NVIM_IMSA2CS_CALL_REDIAL_CAUSE_MAX_NUM];
}TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU;


typedef struct
{
    VOS_UINT8                                               ucCallRedial;                           /* call重拨flag */
    VOS_UINT8                                               ucSmsRedial;                            /* SMS 重拨flag */
    VOS_UINT8                                               ucSsRedial;                             /* SS  重拨flag */
    VOS_UINT8                                               aucReserve[1];
    TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU        stCallRedialCauseCfg;
}TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU;


typedef struct
{
    VOS_UINT8                                              ucCallRedial;
    VOS_UINT8                                              ucSmsRedial;
    VOS_UINT8                                              ucSsRedial;
    VOS_UINT8                                              aucReserve[1];
}TAF_NV_SWITCH_CS_TO_IMS_REDIAL_CONFIG_STRU;


typedef struct
{
    VOS_UINT8                           ucCallRedial;
    VOS_UINT8                           ucSmsRedial;
    VOS_UINT8                           ucSsRedial;
    VOS_UINT8                           aucReserve[1];
}TAF_NV_SWITCH_DOMAIN_REDIAL_CONFIG_STRU;


typedef struct
{
    VOS_UINT8                           ucImsRoamingFlg;
    VOS_UINT8                           aucReserve[3];
}TAF_NV_IMS_ROAMING_SUPPORT_STRU;


typedef struct
{
    VOS_UINT8                           ucUssdOnImsSupportFlag;
    VOS_UINT8                           aucReserve[3];
}TAF_NV_IMS_USSD_SUPPORT_STRU;


typedef struct
{
    MTC_PS_TRANSFER_ENUM_UINT8         enSolutionCfg;
    VOS_UINT8                          aucAdditonCfg[3];
} MTC_NV_PS_TRANSFER_CFG_STRU;


typedef struct
{
    TAF_FLASH_DIRECTORY_TYPE_ENUM_UINT16                     enFlashDirectoryType;
    VOS_UINT8                                                aucReserved1[2];
}TAF_NV_FLASH_DIRECTORY_TYPE_STRU;


typedef struct
{
    VOS_UINT32                          ulTimerInterval;                        /* 时间间隔值,单位秒 */
}MTC_RF_LCD_TIMER_INTERVAL_STRU;


typedef struct
{
    VOS_UINT32                          ulMipiClk;                              /* MipiClk值 */
    VOS_UINT32                          aulFreq[MTC_RF_LCD_MIPICLK_FREQ_MAX_NUM];/* ulMipiClk值影响的频率表 */
}MTC_NVIM_RF_LCD_MIPICLK_FREQ_STRU;


typedef struct
{
    VOS_UINT16                          usEnableBitMap;                         /* 使能开关，每个bit代表不同的算法，非0代表使能 */
    VOS_UINT16                          usFreqWidth;                            /* 带宽 单位100KHZ */
    MTC_NVIM_RF_LCD_MIPICLK_FREQ_STRU   astRfMipiClkFreqList[MTC_RF_LCD_MIPICLK_MAX_NUM]; /* 单位100KHZ */
} MTC_NVIM_RF_LCD_CFG_STRU;


typedef struct
{
    VOS_UINT32                          ulWaterLevel1;                          /* 水线界别1 */
    VOS_UINT32                          ulWaterLevel2;                          /* 水线界别2 */
    VOS_UINT32                          ulWaterLevel3;                          /* 水线界别3 */
    VOS_UINT32                          ulWaterLevel4;                          /* 水线界别4,预留 */
} ADS_UL_WATER_MARK_LEVEL_STRU;


typedef struct
{
    VOS_UINT32                          ulThreshold1;                           /* 赞包门限1 */
    VOS_UINT32                          ulThreshold2;                           /* 赞包门限2 */
    VOS_UINT32                          ulThreshold3;                           /* 赞包门限3 */
    VOS_UINT32                          ulThreshold4;                           /* 赞包门限4 */
} ADS_UL_THRESHOLD_LEVEL_STRU;


typedef struct
{
    VOS_UINT32                          ulActiveFlag;                           /* 使能标识: 0表示去使能,1表示使能 */
    VOS_UINT32                          ulProtectTmrExpCnt;                     /* 保护定时器超时计数时长 */
    ADS_UL_WATER_MARK_LEVEL_STRU        stWaterMarkLevel;
    ADS_UL_THRESHOLD_LEVEL_STRU         stThresholdLevel;
    VOS_UINT32                          aulReserved[6];
} ADS_NV_DYNAMIC_THRESHOLD_STRU;


typedef struct
{
    /* VOS_TRUE:激活，ata异步上报ok，发送connect后即上报ok，不等网络connect ack；
       VOS_FALSE:未激活,ata同步上报，发送connect后等收到网络connect ack后再上报ok */
    VOS_UINT8                           ucAtaReportOkAsyncFlag;
    VOS_UINT8                           aucReserved1[3];
}TAF_CALL_NVIM_ATA_REPORT_OK_ASYNC_CFG_STRU;




typedef struct
{
    VOS_UINT8                           ucMode;                                 /* JAM设置的模式，0:关闭, 1:打开 */
    VOS_UINT8                           ucMethod;                               /* JAM检测使用的方案，1:方案1；2:方案2,目前只支持2 */
    VOS_UINT8                           ucFreqNum;                              /* 检测需要达到的频点个数，取值范围:[0,255] */
    VOS_UINT8                           ucThreshold;                            /* 检测需要达到的频点测量值，取值范围:[0,70] */
    VOS_UINT8                           ucJamDetectingTmrLen;                   /* 强信号频点个数满足门限后，检查同步结果的定时器时长(s) */
    VOS_UINT8                           ucJamDetectedTmrLen;                    /* 检测到干扰后，等待搜网结果的最长时间(s) */
    VOS_UINT8                           ucFastReportFlag;                       /* 搜网过程中是否需要快速上报 */
    VOS_UINT8                           aucRsv[1];
}NV_NAS_JAM_DETECT_CFG_STRU;

typedef struct
{
    VOS_UINT8                           ucMode;                                 /* JAM设置的模式，0:关闭, 1:打开 */
    VOS_UINT8                           ucMethod;                               /* JAM检测使用的方案，1:方案1；2:方案2,目前只支持2 */
    VOS_UINT8                           ucJamBandWidth;                         /* 干扰仪信号带宽，默认30M */
    VOS_UINT8                           ucFastReportFlag;                       /* 搜网过程中是否需要快速上报 */
    VOS_UINT8                           ucRssiSrhThreshold;                     /* 测量RSSI时检测需要达到的频点测量值，取值范围:[0,70]，实际用的时候减70使用 */
    VOS_UINT8                           ucRssiSrhFreqPercent;                   /* 测量RSSI时检测需要达到的频点个数占频点总数(BAND和干扰信号取交集)的百分比，取值范围:[0,100] */
    VOS_UINT16                          usPschSrhThreshold;                     /* 测量PSCH时检测需要小于等于的频点测量值，取值范围:[0,65535] */
    VOS_UINT8                           ucPschSrhFreqPercent;                   /* 测量PSCH时检测需要达到的频点个数占频点总数(BAND和干扰信号取交集)的百分比，取值范围:[0,100] */
    VOS_UINT8                           ucJamDetectingTmrLen;                   /* 强信号频点个数满足门限后，检查同步结果的定时器时长(s) */
    VOS_UINT8                           ucJamDetectedTmrLen;                    /* 检测到干扰后，等待搜网结果的最长时间(s) */
    VOS_UINT8                           aucRsv[1];
}NV_NAS_WCDMA_JAM_DETECT_CFG_STRU;

typedef struct
{
    VOS_UINT32                          ulDebugLevel;                           /* VCOM DEBUG级别:ERR,NORMAL,INFO,DEBUG */
    VOS_UINT32                          ulAppVcomPortIdMask;                    /* VCOM端口ID掩码 */
    VOS_UINT32                          ulReserved[4];                          /* 预留 */
} TAF_NV_PORT_DEBUG_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* 1:锁频功能打开，0:功能关闭 */
    TAF_NVIM_RAT_MODE_ENUM_UINT8        enRatMode;
    VOS_UINT16                          usLockedFreq;
    TAF_NVIM_GSM_BAND_ENUM_UINT16       enBand;
    VOS_UINT8                           aucReserved[2];
} TAF_NVIM_FREQ_LOCK_CFG_STRU;


typedef struct
{
    TAF_NV_ACTIVE_MODEM_MODE_ENUM_UINT8 enActiveModem;
    VOS_UINT8                           aucReserve[3];
}TAF_NV_DSDS_ACTIVE_MODEM_MODE_STRU;


typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* 1:功能打开，0:功能关闭 */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usMcc;                                  /* 国家码，格式示例: 0x0460(中国大陆) */
} TAF_NVIM_ECID_TL2GSM_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucOperNameServicePrioNum;

    /* 1代表支持PNN，cosp或^eonsucs2查询时检查PNN文件查找匹配的运营商名称;
       2代表支持CPHS,cops或^eonsucs2查询时检查CPHS文件查找匹配的运营商名称;
       3代表支持MM INFO,cops或^eonsucs2查询时从mm/gmm/emm information中查找匹配的运营商名称;
       4代表支持SPN,cops或^eonsucs2查询时检查SPN文件查找匹配的运营商名称*/
    VOS_UINT8                           aucOperNameSerivcePrio[TAF_NVIM_MAX_OPER_NAME_SERVICE_PRIO_NUM];
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    VOS_UINT8                           ucPlmnCompareSupportWildCardFlag; /* plmn比较时是否支持通配符 */
    VOS_UINT8                           ucWildCard;                       /* 通配符,取值a-f,可代表0-9任意数字 */
    VOS_UINT8                           ucReserved4;
    VOS_UINT8                           ucReserved5;                      /* 控制内部测试命令^usimstub和^refreshstub命令是否可用*/
}TAF_NVIM_ENHANCED_OPER_NAME_SERVICE_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucRefreshAllFileRestartFlag;  /* 0: mma收到pih的refresh指示所有文件变更时不重启modem; 1:mma收到pih的refresh指示所有文件变更时无cs业务时重启modem*/
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_REFRESH_ALL_FILE_RESTART_CFG_STRU;



typedef struct
{
    VOS_UINT8                           ucAllowDefPdnTeardownFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;

} TAF_NV_PDN_TEARDOWN_POLICY_STRU;

typedef struct
{
    TAF_XSMS_DATA_REQ_SEND_CHAN_ENUM_UINT8                  enXsmsChannelOption;    /* 公共信道或专用信道 */
    VOS_UINT8                                               ucResendMax;            /* 重试最大次数，最大5次 */
    VOS_UINT8                                               ucResendInterval;       /* 重新发送数据到接入层的等待时间，1秒 */
    VOS_UINT8                                               ucReconnectInterval;    /* 重新建立连接的等待时间，5秒 */
}TAF_NVIM_1X_XSMS_CFG_STRU;


typedef struct
{
    TAF_MMA_CFREQ_LOCK_MODE_TYPE_ENUM_UINT8                 enFreqLockMode;
    VOS_UINT8                                               aucReserve[3];
    VOS_UINT16                                              usSid;
    VOS_UINT16                                              usNid;
    VOS_UINT16                                              usCdmaBandClass;
    VOS_UINT16                                              usCdmaFreq;
    VOS_UINT16                                              usCdmaPn;
    VOS_UINT16                                              usEvdoBandClass;
    VOS_UINT16                                              usEvdoFreq;
    VOS_UINT16                                              usEvdoPn;
}TAF_NVIM_CFREQ_LOCK_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucTTYMode;/*TTY模式值，0-3，default:0*/
    VOS_UINT8                           ucReserved0;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;

} TAF_NV_TTY_CFG_STRU;


typedef struct
{
    VOS_UINT32                          ulStatisticTime;                        /* 统计时间，单位为秒 */
    VOS_UINT32                          ulSwitchNum;                            /* gutl频繁切换的次数 */
} TAF_NV_RAT_FREQUENTLY_SWITCH_CHR_RPT_CFG_STRU;


typedef struct
{
    /* 此NV 用来设置呼叫等待的控制模式，ulCcwaCtrlMode为0，则呼叫等待由3gpp网络控制；
       ulCcwaCtrlMode为1，则呼叫等待由UE控制，用于VOLTE的网络。
      （在VoLTE的网络上，AP配置CCWA支持时，IMS并没有和网络交互，VoLTE的电话的CCWA由UE控制）。
       支持VOLTE的终端，不管VOLTE开关有没有打开，都是下发CCWAI来设置呼叫等待。
    */
    TAF_CALL_CCWA_CTRL_MODE_ENUM_U8     enCcwaCtrlMode;
    TAF_CALL_CCWAI_MODE_ENUM_UINT8      enCcwaiMode;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
} TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU;



typedef struct
{
    VOS_UINT8                           ucCcpuResetFlag;                        /* 0:不是C核单独复位，而是上电 ;
                                                                                   1:是C核单独复位*/
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_CCPU_RESET_RECORD_STRU;



typedef struct
{
    VOS_UINT16                          usSo;
    VOS_UINT8                           aucReserved[2];
}TAF_NVIM_1X_DATA_SO_CFG;




typedef struct
{
    VOS_UINT8                           ucPktCdataInactivityTmrLen;

    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_CDATA_GENERIC_CONFIG_STRU;



typedef struct
{
    VOS_UINT8                           ucRnicNetifRxType;    /* 0:netif_rx，1:netif_rx_ni，default:0 */
    VOS_UINT8                           ucReserved0;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
} TAF_NV_RNIC_NETIF_RX_TYPE_STRU;


typedef struct
{
    VOS_UINT32                          ulEnable;           /* 使能标识 */
    VOS_UINT32                          ulTxWakeTimeout;    /* 上行发送唤醒超时保护 */
    VOS_UINT32                          ulRxWakeTimeout;    /* 下行接收唤醒超时保护 */
    VOS_UINT32                          ulReserved;

} TAF_NV_ADS_WAKE_LOCK_CFG_STRU;


typedef struct
{
    VOS_UINT16                          usBlkNum;
    VOS_UINT16                          usReserved0;
    VOS_UINT16                          usReserved1;
    VOS_UINT16                          usReserved2;

} TAF_NV_ADS_MEM_CFG_STRU;


typedef struct
{
    VOS_UINT32                          ulEnable;
    TAF_NV_ADS_MEM_CFG_STRU             astMemCfg[2];

} TAF_NV_ADS_MEM_POOL_CFG_STRU;



typedef struct
{
    VOS_UINT32                                              ulEmcCallRedialPeriod;  /* 紧急呼重拨定时器时长 */
} TAF_XCALL_NVIM_1X_EMC_CALL_REDIAL_PERIOD_STRU;


typedef struct
{
    VOS_UINT16                          usSo;
    VOS_UINT8                           aucReserved[2];
}TAF_NVIM_1X_VOICE_SO_CFG;




typedef struct
{
    VOS_UINT8                           ucSecType;
    VOS_UINT8                           ucBlackListNum;
    VOS_UINT16                          ausBlackList[TAF_NV_BLACK_LIST_MAX_NUM];
} TAF_NV_NVWR_SEC_CTRL_STRU;


typedef struct
{
    VOS_UINT32                           ulIpv6AddrTestModeCfg;                 /* 0x55aa55aa是测试模式，其他值为正常模式 */
}TAF_NVIM_IPV6_ADDR_TEST_MODE_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucEnable;                               /* 0:NV 未激活; 1:NV 激活 */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulRptSrvStaDelayTimerValue;             /*延时上报定时器时长,单位:秒 */
}TAF_MMA_NVIM_DELAY_REPORT_SERVICE_STATUS_STRU;


typedef struct
{
    VOS_UINT8   ucCLDelayTimerLen;                                              /* DO+LTE延迟上报无服务定时器时长: 0:不延迟上报，其他按照时长延迟后上报 */
    VOS_UINT8   ucDoDelayTimerLen;                                              /* DO延迟上报无服务定时器时长: 0:不延迟上报，其他按照时长延迟后上报 */
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
}TAF_MMA_NVIM_DELAY_RPT_CLNOSERVICE_STRU;


typedef struct
{
    VOS_UINT32                          ulStartAndStopContDtmfIntervalLen;  /* 定时器时长，单位:ms  */
}TAF_XCALL_NVIM_START_AND_STOP_CONT_DTMF_INTERVAL_STRU;


typedef struct
{
    VOS_UINT8                           ucPrintModemLogType;                    /* 0:输出modem log，1:不输出modem log，default:0 */
    VOS_UINT8                           ucReserved0;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
} TAF_NV_PRINT_MODEM_LOG_TYPE_STRU;


typedef struct
{
    VOS_UINT8                           ucCLDelayRptEnable;
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT32                          ulCLRptSrvStaDelayTimerLen;
    VOS_UINT8                           aucReserved2[12];
}TAF_MMA_NVIM_CL_DELAY_REPORT_SERVICE_STATUS_STRU;



typedef struct
{
    VOS_UINT8                           ucMergeFlg;                             /* 非正常服务下是否合并注册状态上报 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_NONNORMAL_REG_STATUS_MERGE_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucEccSrvCap;        /* ECC服务能力: TRUE -- 支持ECC服务，FALSE -- 不支持ECC服务 */
    VOS_UINT8                           ucEccSrvStatus;     /* ECC服务状态: TRUE -- ECC服务打开，FALSE -- ECC服务关闭 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
} TAF_NVIM_ENCVOICE_ECC_SRV_CAP_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucVerNum;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    VOS_UINT8                           aucPubKey[TAF_NVIM_KMC_MSG_MAX_KMC_PUB_KEY_LEN];
} TAF_NVIM_ENCVOICE_ECC_PUB_KEY_INFO_STRU;


typedef struct
{
    VOS_UINT16                          usYear;     /* Year [1980..2100) */
    VOS_UINT16                          usMonth;    /* Month of year [1..12] */
    VOS_UINT16                          usDay;      /* Day of month [1..31] */
    VOS_UINT16                          usHour;     /* Hour of day [0..23] */
    VOS_UINT16                          usMinute;   /* Minute of hour [0..59] */
    VOS_UINT16                          usSecond;   /* Second of minute [0..59] */
} TAF_NVIM_ENCVOICE_SECINFO_ERASE_SYSTIME_INFO_STRU;


typedef struct
{
    VOS_UINT16                          usYear;     /* Year [1980..2100) */
    VOS_UINT16                          usMonth;    /* Month of year [1..12] */
    VOS_UINT16                          usDay;      /* Day of month [1..31] */
    VOS_UINT16                          usHour;     /* Hour of day [0..23] */
    VOS_UINT16                          usMinute;   /* Minute of hour [0..59] */
    VOS_UINT16                          usSecond;   /* Second of minute [0..59] */
} TAF_NVIM_ENCVOICE_PASSWD_RESET_SYSTIME_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucDelayEncVoiceReqTimerLen;
    VOS_UINT8                           ucReserved1;
    VOS_UINT16                          usRemoteCtrlAnswerTimerLen;
} TAF_NVIM_ENCVOICE_TIMER_CFG_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulCallBackEnableFlg;
    VOS_UINT32                          ulCallBackModeTimerLen;
} TAF_NVIM_1X_CALLBACK_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucEnableFlag;                           /* VOS_TRUE:配置Filter过滤规则；VOS_FALSE:不配置过滤规则 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_NDIS_FILTER_ENABLE_FLAG_CFG_STRU;


typedef struct
{
    VOS_UINT8                                               ucIsCfgEnable;  /* VOS_TRUE: 使能 VOS_FALSE:不使能 */
    TAF_XSMS_TL_ACK_NEED_LEVEL_ENUM_UINT8                   enTlAckNeedLevel;
    VOS_UINT8                                               aucRsv[2];
}TAF_XSMS_MO_TL_ACK_TIME_OUT_CFG_STRU;


typedef struct
{
    VOS_UINT16                          usNumOfDigits;
    VOS_UINT8                           aucDigits[38]; /* DTMF号码 */
}TAF_XSMS_KMC_DEF_ADDRESS_STRU;
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasNvInterface.h */
