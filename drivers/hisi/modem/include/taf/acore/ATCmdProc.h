

#ifndef _ATCMDPROC_H_
#define _ATCMDPROC_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "AtCtx.h"
#include "siapppb.h"
#include "MnErrorCode.h"
#include "TafAppPpp.h"
#include "TafDrvAgent.h"
#include "mdrv.h"

#include "cpm.h"
#include "dms.h"
#include "AtParse.h"
#include "AtAppVcomInterface.h"
#include "AtMuxInterface.h"
#include "AtDipcInterface.h"
#include "AtMntn.h"
#include "AtSndMsg.h"
#include "NasOmInterface.h"
#include "ImmInterface.h"
#include "msp_errno.h"
#include "SOCPInterface.h"

#include "AcpuReset.h"
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-5, begin */
#include "siapppih.h"
#include "TafAgentInterface.h"
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-5, end */
#include "TafAppXsmsInterface.h"

#include "AtXpdsInterface.h"

#include "AtMtaInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define AT_USBCOM_DISABLED              (0)                                     /* 串口去使能状态(suspend/disable)*/
#define AT_USBCOM_ENABLED               (1)                                     /* 串口使能状态(resume/enable)*/
#define AT_CC_CALSS_TYPE_INVALID       (255)

/* AT模块允许一次最大输入的XML码流长度 */
#define AT_XML_MAX_LEN               (1024)

#define AT_CUSD_M_NETWORK_TIMEOUT       (5)

#define AT_SFEATURE_DIV_STRING_LEN       (50)

#define AT_PB_IRA_MAX_NUM               (256)
#define AT_PB_GSM_MAX_NUM               (128)
#define AT_PB_GSM7EXT_MAX_NUM           (10)
#define AT_PB_GSM7EXT_SYMBOL            (0x1B)
#define AT_PB_81CODE_HEADER_LEN         (3)
#define AT_PB_82CODE_HEADER_LEN         (4)

 /* 81编码用第8到第15bit进行编码，即0hhh hhhh hXXX XXXX */
#define AT_PB_81_CODE_BASE_POINTER      (0x7f80)
/* GSM7Bit 编码的范围是0~127 */
#define AT_PB_GSM7_CODE_MAX_VALUE       (0x7f)
/* GSM7Bit 编码的第8bit必须为0 */
#define AT_PB_CODE_NO8_BIT              (0x80)



#define AT_ANTEN_LEV_MAX_NUM            (6)

#define AT_HEX_LEN_OF_ULONG_TYPE            (8)                                 /* Unsigned long类型对应十六进制数的位数 */
#define AT_ROAM_FEATURE_OFF_NOCHANGE        (2)                                 /* at^syscfg roam在漫游特性未激活情况为不改变 */
#define AT_SYSCFGEX_PARA_NUM                (7)                                 /* at^syscfgex设置命令的参数个数 */
#define AT_SYSCFGEX_RAT_MODE_STR_LEN        (2)                                 /* at^syscfgex查询上报接入模式字符串长度，如接入模式为G,上报01字符串长度为2 */
#define AT_SYSCFGEX_RAT_NO_CHANGE_HEX_VALUE (0x99)

#define AT_NETSCAN_PARA_MAX_NUM         (4)
#define AT_NETSCAN_PARA_MIN_NUM         (2)
#define AT_NETSCAN_POWER_PARA_MAX_LEN   (4)
#define AT_NETSCAN_POWER_PARA_MIN_LEN   (3)
#define AT_NETSCAN_POWER_MIN_VALUE      (-110)
#define AT_NETSCAN_POWER_MAX_VALUE      (-47)
#define AT_ALL_GU_BAND                  (0x3FFFFFFF)

#define TAF_SERIAL_NUM_LEN              (16)

#define TAF_SERIAL_NUM_NV_LEN           (TAF_SERIAL_NUM_LEN + 4)


#define MN_MSG_TP_MTI_MASK              (3)
#define MN_MSG_SMS_MAX_NUM              (255)

#define AT_INVALID_INDEX                (65535)
#define AT_AP_SPEED_STRLEN              (16)

#define AT_MAX_CREATION_TIME_LEN        (31)  /* 系统编译时间 */

/* AT^DISLOG操作输入255为切换PCUI服务到DIAG服务, 0为打开DIAG口, 1为关闭DIAG口  */
#define AT_DISLOG_PCUI_TO_DIAG          (255)
#define AT_DISLOG_DIAG_OPEN             (0)
#define AT_DISLOG_DIAG_CLOSE            (1)

/* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
#define AT_DISSD_OPEN             (0)
#define AT_DISSD_CLOSE            (1)

/* Add by w00199382 for V7代码同步, 2012-04-07, End   */


#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
/* AT^SHELL操作输入 , 0为WIFI使用SHELL口, 1为关闭SHELL口 , 2为打开SHELL口 */
#define AT_SHELL_WIFI_USE               (0)
#define AT_SHELL_CLOSE                  (1)
#define AT_SHELL_OPEN                   (2)

/* SHELL口密码校验错误最大次数 */
#define AT_SHELL_PWD_VERIFY_MAX_TIMES   (3)
#endif

#define AT_USB_ENABLE_EVENT             (3)
#define AT_USB_SUSPEND_EVENT            (5)

#define AT_MCC_LENGTH                   (3)                                     /* MCC长度 */
#define AT_MCC_PLUS_COMMA_LENGTH        (4)                                     /* MCC加逗号长度 */

#define AT_UART_MODE_ASHELL             (0)
#define AT_UART_MODE_CSHELL             (1)



#if (TAF_BYTE_ORDER == TAF_BIG_ENDIAN)
#define AT_GET_AUTH_LENGTH(pucData)   (((((TAF_UINT16)(*(pucData))) << 8) & 0xFF00) | (((TAF_UINT16)(*((pucData) + 1))) & 0x00FF))
#define AT_GET_IPCP_LENGTH(pucData)   (((((TAF_UINT16)(*(pucData))) << 8) & 0xFF00) | (((TAF_UINT16)(*((pucData) + 1))) & 0x00FF))
#else
#define AT_GET_AUTH_LENGTH(pucData)   ((((TAF_UINT16)(*(pucData))) & 0x00FF) | ((((TAF_UINT16)(*((pucData) + 1)) << 8)) & 0xFF00))
#define AT_GET_IPCP_LENGTH(pucData)   ((((TAF_UINT16)(*(pucData))) & 0x00FF) | ((((TAF_UINT16)(*((pucData) + 1)) << 8)) & 0xFF00))
#endif


#define AT_STOP_TIMER_CMD_READY(ucIndex)  {\
                                              AT_StopRelTimer(ucIndex, &gastAtClientTab[ucIndex].hTimer);\
                                              g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_READY;\
                                              gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CURRENT_OPT_BUTT;\
                                              gastAtClientTab[ucIndex].opId = 0;\
                                          }


#define AT_ADDR_TYPE_UNKNOWN_ISDN       (0x80| (MN_MSG_TON_UNKNOWN << 4) | MN_MSG_NPI_ISDN)
#define AT_ADDR_TYPE_INTERNATIONAL_ISDN (0x80| (MN_MSG_TON_INTERNATIONAL << 4) | MN_MSG_NPI_ISDN)
#define At_UpChar(Char)                 ((('a' <= (Char)) && ((Char) <= 'z'))?((Char) - 0x20):(Char))
#define At_GetCodeType(Char)            (('+' == Char)? (AT_ADDR_TYPE_INTERNATIONAL_ISDN) : (AT_ADDR_TYPE_UNKNOWN_ISDN))

#define At_GetSmsArea(SaveArea)        ((MN_MSG_MEM_STORE_SIM == SaveArea )?AT_STRING_SM:AT_STRING_ME)

#define At_CheckCmdSms(Char,Mode)    ((0 == (Mode))?((ucAtS3) == (Char)):((((ucAtS3) == (Char)) || (('\x1a') == (Char))) || (('\x1b') == (Char))))
#define At_CheckSplitChar(Char)      ((((ucAtS3) == (Char)) || (('\x1a') == (Char))) || (('\x1b') == (Char)))

#define AT_UNICODE2VALUE(x)    ((x) = ((((x) & 0x00ff) << 8) | (((x) & 0xff00) >> 8)))

#define AT_CMD_BUF_LEN                          12040
#define AT_CLIENT_NULL                          0         /*未使用状态*/
#define AT_CLIENT_USED                          1         /*占有状态*/

#define AT_UNICODE_SMS_MAX_LENGTH               140       /*短消息UNICODE码最大长度*/
#define AT_ASCII_SMS_MAX_LENGTH                 160       /*短消息ASCII码最大长度*/
#define AT_SMS_MAX_LENGTH                       160       /*短消息内容最大长度*/
#define AT_SMS_SEG_MAX_LENGTH                   800
#define AT_COM_BUFF_LEN                        1600
#define AT_MODEM_USER_DLCI                      64        /*usbmodem数传使用的链路号*/
#define AT_CALL_MAX_NUM                         7         /* 最多呼叫数目 */
#define AT_SMS_RP_ADDRESS_MAX_LEN               12

#define AT_PB_NAME_MAX_LENGTH                   AT_MSG_MAX_TPDU_LEN


#define AT_PCVOICE_SAMPLE_RATE                  (8000)
#define AT_PCVOICE_DATA_BIT                     (16)
#define AT_PCVOICE_FRAME_PERIOD                 (20)

/*DTMF相关*/
/* Modified by l00198894 for V9R1 STK升级, 2013/07/11, begin */
#define AT_DTMF_START                           (1)
#define AT_DTMF_STOP                            (0)
#define AT_VTS_DEFAULT_DTMF_LENGTH              (65)
#define AT_DTMF_DEFAULT_DTMF_LENGTH             (60000)
/* Modified by l00198894 for V9R1 STK升级, 2013/07/11, end */

#define AT_DTMF_MIN_DTMF_OFF_LENGTH             (10)                            /* osa能启动最小精度的定时器为10ms */

#define AT_QUICK_START_DISABLE    0x00000000
#define AT_QUICK_START_ENABLE     0x01000101

#define AT_CNMR_QRY_GAS_NMR_DATA        (1)         /* ^cnmr查询2g的nmr 数据*/
#define AT_CNMR_QRY_WAS_NMR_DATA        (2)         /* ^cnmr查询3g的nmr 数据*/
#define AT_CNMR_QRY_LTE_NMR_DATA        (3)         /* ^cnmr查询4g的nmr 数据*/

#define AT_CTRL_Z                       (0x1A)      /* CTRL-Z */
#define AT_ESC                          (0x1B)      /* ESC */
#define AT_CR                           (0x0D)      /* CR */

#define AT_NVIM_PARA_LEN    NV_ITEM_AT_PARA_SIZE

#define  AT_UPCASE( c ) ( (((c) >= 'a') && ((c) <= 'z')) ? ((c) - 0x20) : (c) )

#define AT_SMS_EVENT_TYPE                                   0
#define AT_CS_EVENT_TYPE                                    1
#define AT_PS_EVENT_TYPE                                    2
#define AT_PH_EVENT_TYPE                                    3
#define AT_PB_EVENT_TYPE                                    4
#define AT_SS_EVENT_TYPE                                    5
#define AT_DS_EVENT_TYPE                                    6
#define AT_SET_EVENT_TYPE                                   7
#define AT_QRY_EVENT_TYPE                                   8
#define AT_DATA_IND_EVENT_TYPE                              9
#define AT_DATA_STATUS_EVENT_TYPE                           10
#define AT_SAT_IND_EVENT_TYPE                               11
#define AT_SAT_RSP_EVENT_TYPE                               12
#define AT_SAT_DATA_EVENT_TYPE                              13

#define AT_BUTT_INDEX                                       0xFF
/*->f62575*/
#define AT_CNMI_STANDARD                                    0
#define AT_MSG_DELETE_SINGLE                                0x01
#define AT_MSG_DELETE_READ                                  0x02
#define AT_MSG_DELETE_UNREAD                                0x04
#define AT_MSG_DELETE_SENT                                  0x08
#define AT_MSG_DELETE_UNSENT                                0x10
#define AT_MSG_DELETE_ALL                                   0x20
typedef TAF_UINT8   AT_MSG_DELETE_ENUM_U8;

#define AT_SMS_NVIM_SUPPORT                                 0
#define AT_BUTT_CLIENT_ID                                   ((MN_CLIENT_ID_T)(-1))
#define AT_CSCA_CSMP_STORAGE_INDEX                          0

#define AT_MSG_MAX_TPDU_LEN                                 176
#define AT_MSG_INTERNAL_ISDN_ADDR_TYPE                      145

#define AT_MSG_MAX_MSG_SEGMENT_NUM                          2

#define MN_AT_INTERFACE_MSG_HEADER_LEN                      ((sizeof(MN_AT_IND_EVT_STRU) - VOS_MSG_HEAD_LENGTH) - 4)

#define AT_MN_MAX_SMS_TPDU_LEN                              164

/*Refer to 27005 <fo> SMS-DELIVER, SMS-SUBMIT (default 17)*/
#define AT_CSMP_FO_DEFAULT_VALUE1                           17
#define AT_CSMP_SUBMIT_VP_DEFAULT_VALUE                     (167)

/*Refer to 27005 <fo>  SMS-STATUS-REPORT, or SMS-COMMAND (default 2)*/
#define AT_CSMP_FO_DEFAULT_VALUE2                           2

/*23040 9.2.3.3 bit no 3 and 4 of the first octet of SMS SUBMIT*/
#define AT_GET_MSG_TP_VPF( ucVpf, ucFo)                     (ucVpf = (ucFo & 0x18) >> 3)
/*<-f62575*/

/* 将设置和查询时间缩短，特殊命令另外设置时间 */
#define AT_SET_CFUN_TIME   (75000)
#define AT_SET_PARA_TIME   (30000) /*<==A32D12591*/
#define AT_QRY_PARA_TIME   (30000) /*<==A32D12429*/
#define AT_TEST_PARA_TIME  (30000)

#define AT_SET_CGLA_PARA_TIME   (90000)

/* 解决2G语音和短信并发重传过程中AT命令提前结束问题: 75000 -> 105000 */
/* 解决DCM 461-0701-0202 461-0701-0203重传过程中AT命令提前结束问题 */
#define AT_SMS_SET_PARA_TIME   (105000) /*<==A32D12591*/

/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-12, begin */
#if (FEATURE_IMS == FEATURE_ON)
/* increase 15s for CMGS and CMSS set command */

/* Added by j00174725 for DTS2015051104404 DCM 短信测试(180修改为210( 短信时间4*(45+5) )), 2015-05-07, begin */
#define AT_SMS_CMGS_SET_PARA_TIME        (210000)
/* Added by j00174725 for DTS2015051104404 DCM 短信测试, 2015-05-07, begin */

#define AT_SMS_CMSS_SET_PARA_TIME        (180000)
/* increase 15s for SS service request command */
#define AT_SS_CUSD_SET_PARA_TIME         (45000)
#else
#define AT_SMS_CMGS_SET_PARA_TIME        (105000)
#define AT_SMS_CMSS_SET_PARA_TIME        (105000)
#define AT_SS_CUSD_SET_PARA_TIME         (30000)
#endif
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-12, end */


/* 将PDP激活和断开时AT起的TIMER的时长拉长 */
#define AT_ACT_PDP_TIME    (362000)    /* 362 秒, APS是360秒, 3380是30秒一次共5次150秒 */
#define AT_DETACT_PDP_TIME (50000)     /* 50秒, APS是48秒, 3390是8秒一次共5次40秒 */
#define AT_MOD_PDP_TIME    (170000)    /* 170秒, APS是168秒, 3381是8秒一共5次40秒 */

#define AT_NOT_SET_TIME  0

#define AT_COPS_SPEC_SRCH_TIME                             (120000)             /* COPS指定搜网时间 */
#define AT_COPS_LIST_SRCH_TIME                             (240000)             /* COPS列表搜网时间 */
#define AT_COPS_LIST_ABORT_TIME                            (15000)              /* COPS列表搜打断时间, 定15S是因为MMA的保护时长为10S */


#define AT_CSG_LIST_SRCH_TIME                             (220000)             /* CSG列表搜网时间 */
#define AT_CSG_LIST_ABORT_TIME                            (15000)             /* CSG列表搜打断时间, 定15S是因为MMA的保护时长为10S */

/* 定义AT模块等待SYSCFG/SYSCFGEX的回复时间定时器*/
#define AT_SYSCFG_SET_PARA_TIME                             (100000)            /* iteration 13修改为该时长为100S */

#define AT_NETSCAN_SET_PARA_TIME                            (120000)

#define AT_ABORT_NETSCAN_SET_PARA_TIME                      (15 * 1000)


#define AT_UPGRADE_TIME_5S      5000
#define AT_UPGRADE_TIME_50S     50000

#define AT_CGATT_SET_PARA_TIME                             (240000)

/* 补充业务启动150s定时器，at的保护定时器需要比ss启动的保护定时器长定位160s */
#define AT_SET_SS_PARA_TIME             (160000)
#define AT_QRY_SS_PARA_TIME             (160000)


#define AT_PPP_PROTOCOL_REL_TIME  5000   /*等待PPP回应AT_PPP_PROTOCOL_REL_IND_MSG的保护定时器时长*/
#define AT_HOLD_CMD_TIMER_LEN   (360000)    /*处理AT缓存命令的定时器时长，设置为最长AT处理定时器360000*/

#define AT_BCD_HEX(x) ((TAF_UINT8)((TAF_UINT8)(((x) & 0xF0)>>4) + (TAF_UINT8)(((x) & 0x0F)*0x0A)))

#define AT_BCD_REVERSE(x)   (TAF_UINT8)((((x) << 4) & 0xf0) + (((x) >> 4) & 0x0f))

/*PPP拨号时，若拨号命令中未指定CID(如*99#拨号命令)，则默认使用如下CID*/
#define AT_DIAL_DEFAULT_CID         1

#define AT_INVALID_TZ_VALUE         0x7F



/* AT命令允许设置的地址最大长度 */
#define AT_NDIS_ADDR_PARA_LEN           (15)
#define AT_NDIS_IPV4_ADDR_PARA_LEN      (15)
#define AT_NDIS_IPV6_ADDR_PARA_LEN      (63)

#define AT_SERVICE_CS_PS                        (2)     /*PS、CS业务都使能 */
#define AT_DEVICE_STATE_FROM_COFIGFILE          (0)     /*0:MDM+DIAG+PCUI*/
#define AT_DEVICE_STATE_FROM_UE                 (4372)  /*4372:CDROM/MDM+NDIS+DIAG+PCUI+CDROM+SD+BT*/
#define AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED   (2)     /*定制项被修改,不为可配置需求文档默认值*/
#define AT_CUSTOMIZE_ITEM_DEFAULT_VAL_UNCHANGE  (0)     /*定制项未修改,为可配置需求文档默认值*/
#define AT_HSUPA_ENABLE_STATE                   (1)     /*en_NV_Item_WAS_RadioAccess_Capa NV项中HSUPA为使能状态*/
#define AT_HSUPA_DISABLE_STATE                  (0)     /*en_NV_Item_WAS_RadioAccess_Capa NV项中HSUPA为未使能状态*/
#define AT_HSDPA_ENABLE_STATE                   (1)     /*en_NV_Item_WAS_RadioAccess_Capa NV项中HSDPA为使能状态*/
#define AT_HSDPA_DISABLE_STATE                  (0)     /*en_NV_Item_WAS_RadioAccess_Capa NV项中HSDPA为未使能状态*/
#define AT_HSDSCH_PHY_CATEGORY_DEFAULT_VAL      (10)     /*en_NV_Item_WAS_RadioAccess_Capa NV项中HSDPA能力等级默认值*/
#define AT_PS_PTL_VER_R7                        (4)     /*en_NV_Item_WAS_RadioAccess_Capa NV项中Access Stratum Release Indicator*/

#define AT_SIM_LOCK_MNC_NUM_DEFAULT_VAL         (0xaa)     /*en_NV_Item_CustomizeSimLockPlmnInfo NV项中mnc num的默认值*/
#define AT_SIM_LOCK_PLMN_RANGE_DEFAULT_VAL      (0xAAU)  /*en_NV_Item_CustomizeSimLockPlmnInfo NV中range_begin和range_end的默认值*/
#define AT_SIM_LOCK_MAXTIMES_DEFAULT_VAL        (10)    /*en_NV_Item_CustomizeSimLockMaxTimes NV中LockMaxTimes的默认值*/
#define AT_GPRS_ACT_TIMER_LEN_DEFAULT_VAL       (0)     /*en_NV_Item_GPRS_ActiveTimerLength NV项默认值为20s,单位:秒*/
#define AT_HSDSCH_PHY_CATEGORY_6                (6)     /*WAS_HSDSCH_PHY_CATEGORY_6*/
#define AT_HSDSCH_PHY_CATEGORY_8                (8)     /*WAS_HSDSCH_PHY_CATEGORY_8*/
#define AT_HSDSCH_PHY_CATEGORY_10               (10)
#define AT_HSDSCH_PHY_CATEGORY_11               (11)    /*WAS_HSDSCH_PHY_CATEGORY_11*/

#define AT_HSDSCH_PHY_CATEGORY_12               (12)    /*WAS_HSDSCH_PHY_CATEGORY_12*/
#define AT_HSDSCH_PHY_CATEGORY_14               (14)    /*WAS_HSDSCH_PHY_CATEGORY_14*/

/* enHSDSCHSupport */
#define AT_DEST_HSDPA_ENABLE                    (1)
#define AT_DEST_HSDPA_DISABLE                   (0)

/* enEDCHSupport */
#define AT_DEST_HSUPA_ENABLE                    (1)
#define AT_DEST_HSUPA_DISABLE                   (0)

/* Source WCDMA RRC Version */
#define AT_SRC_ONLY_WCDMA                       (0)
#define AT_SRC_NOT_SUPPORT_HSUPA                (1)
#define AT_SRC_ALL_SUPPORT                      (2)

/*用于设置号码类型的扩展位，由于底层解码函数统一剥离了ext位，在上报时统一加上*/
#define AT_NUMBER_TYPE_EXT                      (0x80)


#define AT_NUMBER_TYPE_UNKOWN           (128);


#define AT_AP_RATE_STRLEN                        (16)

#define AT_FASTDORM_DEFAULT_TIME_LEN            (5)

#define AT_FACTORY_INFO_LEN             (78)
#define AT_MMI_TEST_FLAG_OFFSET         (24)
#define AT_MMI_TEST_FLAG_LEN            (4)
#define AT_MMI_TEST_FLAG_SUCC           "ST P"

#define AT_HUK_PARA_LEN                                     (32)        /* ^HUK命令参数长度 */
#define AT_FACAUTHPUBKEY_PARA_LEN                           (1040)      /* ^FACAUTHPUBKEY命令公钥参数长度 */
#define AT_FACAUTHPUBKEY_SIGN_PARA_LEN                      (64)        /* ^FACAUTHPUBKEY命令公钥签名参数长度 */
#define AT_RSA_CIPHERTEXT_PARA_LEN                          (256)       /* RSA密文参数长度 */
#define AT_PORTCTRLTMP_PARA_LEN                             (16)        /* ^PORTCTRLTMP命令参数长度 */
#define AT_SIMLOCKDATAWRITE_PARA_LEN                        (1096)      /* 锁网锁卡改制命令参数结构体长度 */
#define AT_PORTATTRIBSET_PARA_ONOFF_LEN                     (1)         /* ^PORTATTRIBSET端口状态参数长度 */
#define AT_PERSONALIZATION_CODE_LEN                         (8)         /* 锁网锁卡通用锁网号段长度 */
#define AT_PERSONALIZATION_NET_CODE_LEN                     (6)         /* 锁网锁卡NET类型锁网号段长度 */
#define AT_PERSONALIZATION_NET_CODE_BCD_LEN                 (3)         /* 锁网锁卡NET类型锁网号段BCD编码的长度 */
#define AT_PERSONALIZATION_SUBNET_CODE_BCD_LEN              (4)         /* 锁网锁卡NETSUB类型锁网号段BCD编码的长度 */
#define AT_PERSONALIZATION_SP_CODE_BCD_LEN                  (4)         /* 锁网锁卡SP类型锁网号段BCD编码的长度 */
#define AT_PERSONALIZATION_CODE_FOURTH_CHAR_INDEX           (3)         /* 锁网锁卡号段第四个字符的索引 */
#define AT_NVWRSECCTRL_PARA_SECTYPE_LEN                     (1)         /* ^NVWRSECCTRL安全控制类型参数长度 */

#define AT_APSEC_CMD_MAX_LEN            (553)       /* "AT^APSEC=<SP_request>"(9+544) 命令最大长度 */
#define AT_APSEC_CMD_MIN_LEN            (21)        /* "AT^APSEC=<SP_request>"(9+12)  命令最小长度 */

#define AT_BODYSARWCDMA_MAX_PARA_NUM                        (16)
#define AT_BODYSARWCDMA_MAX_PARA_GROUP_NUM                  (8)
#define AT_BODYSARGSM_MAX_PARA_NUM                          (16)
#define AT_BODYSARGSM_MAX_PARA_GROUP_NUM                    (8)
#define AT_RF_BAND_ANY_STR                                  "3FFFFFFF"
#define AT_RF_BAND_ANY                                      (0x3FFFFFFF)
#define AT_WCDMA_BAND_DEFAULT_POWER                         (24)
#define AT_GSM_GPRS_850_DEFAULT_POWER                       (33)
#define AT_GSM_EDGE_850_DEFAULT_POWER                       (27)
#define AT_GSM_GPRS_900_DEFAULT_POWER                       (33)
#define AT_GSM_EDGE_900_DEFAULT_POWER                       (27)
#define AT_GSM_GPRS_1800_DEFAULT_POWER                      (30)
#define AT_GSM_EDGE_1800_DEFAULT_POWER                      (26)
#define AT_GSM_GPRS_1900_DEFAULT_POWER                      (30)
#define AT_GSM_EDGE_1900_DEFAULT_POWER                      (26)
#define AT_GSM_GPRS_BAND_OFFSET                             (0)
#define AT_GSM_EDGE_BAND_OFFSET                             (16)

#define  AT_CERSSI_MAX_TIMER_INTERVAL   (20)           // 信号质量上报的最长间隔时间20S


/* 输入数据不足3的倍数时 输出字符后面填充'='号 */
#define         AT_BASE64_PADDING      '='

/* 添加接入技术平衡和acting plmn文件ID宏 */
#define USIMM_ATT_RAT_BALANCING_FID     (0x4F36)
#define USIMM_ATT_ACTING_PLMN_FID       (0x4F34)

#define AT_MEID_OCTET_NUM               (7)

enum B64ReultType{
    b64Result_OK=0,
    b64Result_CODE_SIZE_ERROR,
    b64Result_DATA_SIZE_SMALLNESS,
    b64Result_CODE_ERROR
};

#define  AT_RSFR_RSFW_NAME_LEN      7           /* 目前NAME只支持(VERSION/SIMLOCK/vSIM) */
#define  AT_RSFR_RSFW_SUBNAME_LEN   7           /* SUBNAME长度不超过7 */

/* (TAF_PH_SIMLOCK_PLMN_STR_LEN*2+1)*TAF_MAX_SIM_LOCK_RANGE_NUM = 340 */
/* SIMLOCK的字符串最大340个字符，编码后也不会超过1024 */
#define  AT_RSFR_RSFW_MAX_LEN       1024

extern VOS_UINT32  At_SimlockPlmnNumToAscii(
    const VOS_UINT8                     *pucPlmnRange,
    VOS_UINT8                           ucPlmnRangeLen,
    VOS_UINT8                            *pucAsciiStr
);


/* Added by l60609 for AP适配项目 ，2012-09-10 Begin */
/* RNIC网卡名称最大长度 */
#define AT_RMNET_NAME_MAX_LENGTH        (8)

/* 多实例后最多支持三个RNIC网卡*/
#define AT_RMNET_MAX_COUNT              (3)
/* Added by l60609 for AP适配项目 ，2012-09-10 End */

#define AT_CFREQLOCK_PARA_NUM_MIN       (1)
#define AT_CFREQLOCK_PARA_NUM_MAX       (9)

#define AT_MBMS_SERVICE_ID_LENGTH           (6)
#define AT_MBMS_MCC_LENGTH                  (3)
#define AT_MBMS_MNC_MAX_LENGTH              (3)
#define AT_MBMS_SERVICE_ID_AND_MCC_LENGTH   (9)
#define AT_MBMS_TMGI_MAX_LENGTH             (12)

#define AT_MBMS_UTC_MAX_LENGTH              (12)

typedef VOS_UINT8 AT_MBMS_TYPE;
#define AT_MBMS_SERVICE_ENABLER_TYPE            0
#define AT_MBMS_ACTIVATE_TYPE                   1
#define AT_MBMS_DEACTIVATE_TYPE                 2
#define AT_MBMS_DEACTIVATE_ALL_TYPE             3
#define AT_MBMS_PREFERENCE_TYPE                 4
#define AT_MBMS_SIB16_GET_NETWORK_TIME_TYPE     5
#define AT_MBMS_BSSI_SIGNAL_LEVEL_TYPE          6
#define AT_MBMS_NETWORK_INFORMATION_TYPE        7
#define AT_MBMS_MODEM_STATUS_TYPE               8

typedef VOS_UINT8 AT_COEX_PARA_TYPE;
#define AT_COEX_PARA_COEX_ENABLE                0
#define AT_COEX_PARA_TX_BEGIN                   1
#define AT_COEX_PARA_TX_END                     2
#define AT_COEX_PARA_TX_POWER                   3
#define AT_COEX_PARA_RX_BEGIN                   4
#define AT_COEX_PARA_RX_END                     5

#define AT_COEX_PARA_COEX_ENABLE_MIN            0
#define AT_COEX_PARA_COEX_ENABLE_MAX            1
#define AT_COEX_PARA_TX_BEGIN_MIN               0
#define AT_COEX_PARA_TX_BEGIN_MAX               65535
#define AT_COEX_PARA_TX_END_MIN                 0
#define AT_COEX_PARA_TX_END_MAX                 65535
#define AT_COEX_PARA_TX_POWER_MIN               -32767
#define AT_COEX_PARA_TX_POWER_MAX               32767
#define AT_COEX_PARA_RX_BEGIN_MIN               0
#define AT_COEX_PARA_RX_BEGIN_MAX               65535
#define AT_COEX_PARA_RX_END_MIN                 0
#define AT_COEX_PARA_RX_END_MAX                 65535

/* 封装OSA申请消息接口 */
#define AT_ALLOC_MSG_WITH_HDR(ulMsgLen)\
            PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT, (ulMsgLen))

/* 封装OSA消息头 */
#define AT_CFG_MSG_HDR(pstMsg, ulRecvPid, ulMsgId)\
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderCpuId   = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderPid     = WUEPS_PID_AT;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverCpuId = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverPid   = (ulRecvPid);\
            ((MSG_HEADER_STRU *)(pstMsg))->ulMsgName       = (ulMsgId)

/* 封装OSA消息头(AT内部消息) */
#define AT_CFG_INTRA_MSG_HDR(pstMsg, ulMsgId)\
            AT_CFG_MSG_HDR(pstMsg, WUEPS_PID_AT, ulMsgId)

/* 获取OSA消息内容 */
#define AT_GET_MSG_ENTITY(pstMsg)\
            ((VOS_VOID *)&(((MSG_HEADER_STRU *)(pstMsg))->ulMsgName))

/* 获取OSA消息长度 */
#define AT_GET_MSG_LENGTH(pstMsg)\
            (((MSG_HEADER_STRU *)(pstMsg))->ulLength)

/* 封装OSA发送消息接口 */
#define AT_SEND_MSG(pstMsg)\
            if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))\
            {\
                AT_ERR_LOG("AT_SEND_MSG: Send message fail!\n");\
            }

#define AT_CGCATT_MODE_PS               (1)
#define AT_CGCATT_MODE_CS               (2)
#define AT_CGCATT_MODE_CS_PS            (3)


#define AT_COEX_INVALID                 (0x00ff0000)

#define AT_CCONTDTMF_PARA_NUM_MIN       (2)
#define AT_CCONTDTMF_PARA_NUM_MAX       (3)

#define AT_BODY_SAR_GBAND_GPRS_850_MASK    (0x00000001)
#define AT_BODY_SAR_GBAND_GPRS_900_MASK    (0x00000002)
#define AT_BODY_SAR_GBAND_GPRS_1800_MASK   (0x00000004)
#define AT_BODY_SAR_GBAND_GPRS_1900_MASK   (0x00000008)
#define AT_BODY_SAR_GBAND_EDGE_850_MASK    (0x00010000)
#define AT_BODY_SAR_GBAND_EDGE_900_MASK    (0x00020000)
#define AT_BODY_SAR_GBAND_EDGE_1800_MASK   (0x00040000)
#define AT_BODY_SAR_GBAND_EDGE_1900_MASK   (0x00080000)

#define AT_SPY_TEMP_THRESHOLD_PARA_CHANGE      1                                /* 需要更新该参数 */
#define AT_SPY_TEMP_THRESHOLD_PARA_UNCHANGE    0                                /* 无需更新该参数*/

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
/* Added by L60609 for AT Project，2011-10-10,  Begin*/
/*物理端口最大个数*/
#define AT_PHY_PORT_MAX                 (AT_PORT_BUTT)


/*提供给OM查询发送数据的函数接口*/

extern CPM_RCV_FUNC               g_apAtPortDataRcvFuncTab[AT_PHY_PORT_MAX];
/* Added by L60609 for AT Project，2011-10-10,  End*/

/*****************************************************************************
 枚举名    : AT_VOICE_DOMAIN_TYPE_ENUM
 协议表格  :
 枚举说明  : 优选域类型
*****************************************************************************/
enum AT_VOICE_DOMAIN_TYPE_ENUM
{
    AT_VOICE_DOMAIN_TYPE_CS_ONLY            = 1,
    AT_VOICE_DOMAIN_TYPE_CS_PREFERRED       = 2,
    AT_VOICE_DOMAIN_TYPE_IMS_PS_PREFERRED   = 3,
    AT_VOICE_DOMAIN_TYPE_IMS_PS_ONLY        = 4,
    AT_VOICE_DOMAIN_TYPE_BUTT
};
typedef VOS_UINT32 AT_VOICE_DOMAIN_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : AT_TEMPPRT_STATUS_IND_ENUM
 结构说明  :
             0: AT_TEMPPRT_STATUS_IND_DISABLE  温保状态上报NV项关闭
             1: AT_TEMPPRT_STATUS_IND_ENABLE   温保状态上报NV项开启
*****************************************************************************/
enum AT_TEMPPRT_STATUS_IND_ENUM
{
    AT_TEMPPRT_STATUS_IND_DISABLE   = 0,
    AT_TEMPPRT_STATUS_IND_ENABLE,
    AT_TEMPPRT_STATUS_IND_BUTT
};
typedef VOS_UINT32 AT_TEMPPRT_STATUS_IND_ENUM_UINT32;

/*****************************************************************************
 枚举名    : AT_RSIM_STATUS_ENUM
 结构说明  : ^RSIM 命令查询结果列表
             0: 没有任何卡接触上；
             1: 已经接触上SIM/USIM/UIM；
             2:SIM/USIM/UIM繁忙需要等待；
*****************************************************************************/
enum AT_RSIM_STATUS_ENUM
{
    AT_RSIM_STATUS_USIMM_CARD_ABSENT            = 0x00,
    AT_RSIM_STATUS_USIMM_CARD_AVAILABLE       = 0x01,
    AT_RSIM_STATUS_USIMM_CARD_BUSY                 = 0x02,
    AT_RSIM_STATUS_USIMM_CARD_BUTT                 = 0xff
};
typedef VOS_UINT8  AT_RSIM_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AT_PHYNUM_TYPE_ENUM_UINT32
 协议表格  :
 枚举说明  : 物理号类型
*****************************************************************************/
enum AT_PHYNUM_TYPE_ENUM
{
    AT_PHYNUM_TYPE_IMEI,
    AT_PHYNUM_TYPE_MEID,
    AT_PHYNUM_TYPE_MAC,
    AT_PHYNUM_TYPE_ESN,
    AT_PHYNUM_TYPE_SVN,
    AT_PHYNUM_TYPE_UMID,
    AT_PHYNUM_TYPE_BUTT
};
typedef VOS_UINT32 AT_PHYNUM_TYPE_ENUM_UINT32;

/*->f62575*/
/*SMS version PHASE2版本 SMS PHASE2+版本*/
enum AT_CSMS_MSG_VERSION_ENUM
{
    AT_CSMS_MSG_VERSION_PHASE2,
    AT_CSMS_MSG_VERSION_PHASE2_PLUS
};
typedef TAF_UINT8 AT_CSMS_MSG_VERSION_ENUM_U8;

/* AT TIMER ID list*/
enum AT_TIMER_TYPE_ENUM
{
    AT_CMD_PROCESS_TYPE       = 0x0000,                                         /* 和命令相关的计时器，在处理AT命令时使用 */
    AT_INTERNAL_PROCESS_TYPE  = 0x0100                                          /* AT内部处理的计时器，不在和命令条件相关 */
};

/*<-f62575*/
enum AT_CLCC_MODE_ENUM
{
    AT_CLCC_MODE_VOICE,                                                         /* voice */
    AT_CLCC_MODE_DATA,                                                          /* data */
    AT_CLCC_MODE_FAX,                                                           /* fax */
    AT_CLCC_MODE_VFDV,                                                          /* voice followed by data, voice mode */
    AT_CLCC_MODE_AVDV,                                                          /* alternating voice/data, voice mode */
    AT_CLCC_MODE_AVFV,                                                          /* alternating voice/fax, voice mode */
    AT_CLCC_MODE_VFDD,                                                          /* voice followed by data, data mode */
    AT_CLCC_MODE_AVDD,                                                          /* alternating voice/data, data mode */
    AT_CLCC_MODE_AVFF,                                                          /* alternating voice/fax, fax mode */
    AT_CLCC_MODE_UNKNOWN                                                        /* unknown */
};
typedef TAF_UINT8 AT_CLCC_MODE_ENUM_U8;

enum AT_CPAS_STATUS_ENUM
{
    AT_CPAS_STATUS_READY,                                                       /* ready (MT allows commands from TA/TE) */
    AT_CPAS_STATUS_UNAVAILABLE,                                                 /* unavailable (MT does not allow commands from TA/TE */
    AT_CPAS_STATUS_UNKNOWN,                                                     /* unknown (MT is not guaranteed to respond to instructions) */
    AT_CPAS_STATUS_RING,                                                        /* ringing (MT is ready for commands from TA/TE, but the ringer is active) */
    AT_CPAS_STATUS_CALL_IN_PROGRESS,                                            /* call in progress (MT is ready for commands from TA/TE, but a call is in progress) */
    AT_CPAS_STATUS_ASLEEP                                                       /* asleep (MT is unable to process commands from TA/TE because it is in a low functionality state) */
};
typedef TAF_UINT8 AT_CPAS_STATUS_ENUM_U8;

enum AT_WIFI_MODE_ENUM
{
    AT_WIFI_MODE_ONLY_PA                = 0x00,                                 /* WIFI只支持PA模式 */
    AT_WIFI_MODE_ONLY_NOPA              = 0x01,                                 /* WIFI只支持NO PA模式 */
    AT_WIFI_MODE_PA_NOPA                = 0x02,                                 /* WIFI同时支持PA模式和NO PA模式 */

    AT_WIFI_MODE_BUTT                   = 0xFF
};
typedef VOS_UINT8 AT_WIFI_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AT_GSM_BAND_ENUM
 结构说明  : GSM频段定义
 1.日    期   : 2015年10月30日
   作    者   : w00316404
   修改内容   : 新增枚举(开源整改A、C核解耦)
*****************************************************************************/
enum AT_GSM_BAND_ENUM
{
    AT_GSM_850                         = 0,
    AT_GSM_900,
    AT_GSM_1800,
    AT_GSM_1900,
    AT_GSM_BAND_BUTT
};
typedef VOS_UINT16 AT_GSM_BAND_ENUM_UINT16;

typedef enum
{
    AT_CMD_BUTT,
    AT_CMD_APHPLMN,
    AT_CMD_ANQUERY,
    AT_CMD_CGDATA,
    AT_CMD_CGPADDR,
    AT_CMD_CGEQNEG, /*h41410 for CGEQNEG*/
    AT_CMD_CGDNS,
    AT_CMD_CEER,
    AT_CMD_CPAS,
    AT_CMD_CGMI,
    AT_CMD_CGMM,
    AT_CMD_GMM,
    AT_CMD_CGMR,
    AT_CMD_CGSN,
    AT_CMD_SN,
    AT_CMD_HWVER,
    AT_CMD_HVER,
    AT_CMD_FHVER,
    AT_CMD_PFVER,
    AT_CMD_CLAC,
    AT_CMD_GSN,
    AT_CMD_GCAP,
    AT_CMD_SRVST,
    AT_CMD_RSSI,
    AT_CMD_CERSSI,
    AT_CMD_CNMR,
    AT_CMD_CECELLID,
    AT_CMD_LFROMCONNTOIDLE,
    AT_CMD_LWTHRESHOLDCFG,
    AT_CMD_SYSMODE,
    AT_CMD_SIMST,
    AT_CMD_HS,
    AT_CMD_I,
    AT_CMD_T,
    AT_CMD_P,
    AT_CMD_X,
    AT_CMD_Z,
    AT_CMD_Q,
    AT_CMD_CIMI,
    AT_CMD_VTS,
    AT_CMD_DTMF,
    AT_CMD_CGANS,
    AT_CMD_CGANS_EXT,
    AT_CMD_APENDPPP,
    AT_CMD_CGCMOD,
    AT_CMD_CGACT,
    AT_CMD_CGDCONT,
    AT_CMD_CGDSCONT,
    AT_CMD_DSFLOWCLR,
    AT_CMD_DSFLOWQRY,
    AT_CMD_DSFLOWRPT,
    AT_CMD_CGTFT,
    AT_CMD_CGEQREQ,
    AT_CMD_CGEQMIN,
    AT_CMD_COPS,
    AT_CMD_CGAUTO,
    AT_CMD_CPBS,
    AT_CMD_CPBR,
    AT_CMD_CPBR2,
    AT_CMD_CPBF,
    AT_CMD_CPBW,
    AT_CMD_CPBW2,
    AT_CMD_SCPBW,
    AT_CMD_SCPBR,
    AT_CMD_CNUM,
    AT_CMD_CMEE,
    AT_CMD_CSCS,
    AT_CMD_CSIM,
    AT_CMD_CCHO,
    AT_CMD_CCHC,
    AT_CMD_CGLA,
    AT_CMD_CPIN,
    AT_CMD_CARDLOCK,
    AT_CMD_CARDATR,
    AT_CMD_CPIN_2,
    AT_CMD_CICCID,
    AT_CMD_CPWD,
    AT_CMD_CGCLASS,
    AT_CMD_CLIP,
    AT_CMD_CLIR,
    AT_CMD_COLP,
    AT_CMD_CLCC,
    AT_CMD_CLCK,
    AT_CMD_CTFR,
    AT_CMD_CMLCK,
    AT_CMD_CGSMS,
    AT_CMD_CGATT,
    AT_CMD_CGCATT,
    AT_CMD_CFUN,
    AT_CMD_CSQ,
    AT_CMD_CBC,
    AT_CMD_CBND,
    AT_CMD_CPDW,
    AT_CMD_NVIM,
    AT_CMD_DAM_PARASTUB,
    AT_CMD_ENOS_PARASTUB,
    AT_CMD_COMPARE_PLMN_SUPPORT_WILDCARD,
    AT_CMD_USIM_STUB,
    AT_CMD_REFRESH_STUB,
    AT_CMD_AUTO_RESEL_STUB,
    /* Modified by c00318887 for file refresh需要触发背景搜, 2015-3-27, begin */
    AT_CMD_DELAYBG_STUB,
    /* Modified by c00318887 for file refresh需要触发背景搜, 2015-3-27, end */
    AT_CMD_PIDREINIT,
    /* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-15, begin */
    AT_CMD_IMSRATSTUB,
    /* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-15, end */
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-10-23, begin */
    AT_CMD_IMSCAPSTUB,
    AT_CMD_DOMAINSTUB,
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-10-23, end */
    AT_CMD_USIM,
    AT_CMD_SIM,
    AT_CMD_PDPSTUB,
    AT_CMD_CSND,
    AT_CMD_CSTA,
    AT_CMD_CCUG,
    AT_CMD_CGREG,
    AT_CMD_CEREG,
    AT_CMD_CCWA,
    AT_CMD_CCFC,
    AT_CMD_CUSD,
    AT_CMD_CSSN,
    AT_CMD_CREG,
    AT_CMD_S0,
    AT_CMD_S3,
    AT_CMD_S4,
    AT_CMD_S5,
    AT_CMD_S6,
    AT_CMD_S7,
    AT_CMD_V,
    AT_CMD_E,
    AT_CMD_L,
    AT_CMD_M,
    AT_CMD_AMP_C,
    AT_CMD_AMP_D,
#if (FEATURE_ON == FEATURE_AT_HSUART)
    AT_CMD_AMP_S,
#endif
    AT_CMD_AMP_F,
    AT_CMD_CRC,
    AT_CMD_CMOD,
    AT_CMD_CMMI,
    AT_CMD_CBST,
    AT_CMD_CHUP,
    AT_CMD_D,
    AT_CMD_O,
    AT_CMD_H,
    AT_CMD_A,
    AT_CMD_CHLD,
    AT_CMD_ALS,
    AT_CMD_CUUS1,
    AT_CMD_CPAM,
    AT_CMD_CCIN,
    AT_CMD_TIME,
    AT_CMD_CTZR,

    AT_CMD_CPLS,
    AT_CMD_CPOL,
    AT_CMD_CSIN,
    AT_CMD_CSTR,
    AT_CMD_CSEN,
    AT_CMD_CSMN,
    AT_CMD_CSTC,
    AT_CMD_STSF,
    AT_CMD_STGI,
    AT_CMD_STGR,
    AT_CMD_IMSICHG,
    AT_CMD_TEST,
    AT_CMD_CWAS,
    AT_CMD_CGAS,
    AT_CMD_APPDIALMODE,
    AT_CMD_LCSTARTTIME,
    AT_CMD_MAXFREELOCKSIZE,
    AT_CMD_CPULOAD,
    AT_CMD_CELLINFO,
    AT_CMD_MEANRPT,
    AT_CMD_QCDMG,
    AT_CMD_AT2OM,
    AT_CMD_U2DIAG,
    AT_CMD_DWINS,
    AT_CMD_YJCX,
    AT_CMD_SETPID,
    AT_CMD_GETPORTMODE,
    AT_CMD_CVOICE,
    AT_CMD_DDSETEX,
    AT_CMD_NDISDUP,
    AT_CMD_AUTHDATA,
    AT_CMD_DHCP,
    AT_CMD_CRPN,
    AT_CMD_NDISSTATQRY,
    AT_CMD_NDISCONN,
    AT_CMD_NDISADD,
    AT_CMD_DNSPRIM,
    AT_CMD_DNSSND,
    AT_CMD_DLOADVER,
    AT_CMD_DLOADINFO,
    AT_CMD_NVBACKUP,
    AT_CMD_NVRESTORE,
    AT_CMD_AUTHORITYVER,
    AT_CMD_AUTHORITYID,
    AT_CMD_GODLOAD,
    AT_CMD_RESET,
    AT_CMD_NVRSTSTTS,
    AT_CMD_HWNATQRY,
    AT_CMD_FLASHINFO,
    AT_CMD_CMSR,
    AT_CMD_CMGI,
    AT_CMD_CMMT,
    AT_CMD_USSDMODE,
    AT_CMD_ADCTEMP,
    AT_CMD_COMM,
    AT_CMD_HSPA,
    AT_CMD_CSNR,
    AT_CMD_FREQLOCK,
    AT_CMD_CPSC,
    AT_CMD_CFRQ,
    AT_CMD_CFPLMN,
    AT_CMD_CQST,
    AT_CMD_CAATT,
    AT_CMD_SYSINFO,
    AT_CMD_SYSINFOEX,
    /* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
    AT_CMD_CEMODE,
    AT_CMD_LTECS,

    /* Add by w00199382 for V7代码同步, 2012-04-07, End   */
    AT_CMD_SYSCFG,
    AT_CMD_SYSCFGEX,
    AT_CMD_CMM,
    AT_CMD_SPN,
    AT_CMD_CARDMODE,
    AT_CMD_DIALMODE,
    AT_CMD_PORTSEL,
    AT_CMD_CURC,
    AT_CMD_BOOT,
    AT_CMD_CIMEI,
    AT_CMD_TRIG,
    AT_CMD_GCFIND,
    AT_CMD_MDATE,
    AT_CMD_FACINFO,
    AT_CMD_RXPRI,
    AT_CMD_SIMLOCK,
    AT_CMD_MAXLCK_TIMES,
    AT_CMD_PHYNUM,
    AT_CMD_RSIM,
    AT_CMD_GTIMER,
    AT_CMD_PLATFORM,
    AT_CMD_CSVER,
    AT_CMD_QOS,
    AT_CMD_SDOMAIN,
    AT_CMD_DPACAT,
    AT_CMD_HSSPT,
    AT_CMD_BSN,
    /* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
    AT_CMD_SFM,
    /* Add by w00199382 for V7代码同步, 2012-04-07, End   */
    AT_CMD_TMODE,
    AT_CMD_FCHAN,
    AT_CMD_FTXON,
    AT_CMD_FDAC,

    AT_CMD_SD,
    /* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
    AT_CMD_INFORRS,
    /* Add by w00199382 for V7代码同步, 2012-04-07, End   */
    AT_CMD_INFORBU,
    AT_CMD_DATALOCK,
    AT_CMD_GPIOPL,
    AT_CMD_VERSION,

    AT_CMD_FRXON,
    AT_CMD_FPA,
    AT_CMD_FLNA,
    AT_CMD_FRSSI,
    AT_CMD_RXDIV,
    AT_CMD_CALLSRV,
    AT_CMD_CSDFLT,
    AT_CMD_SECUBOOTFEATURE,
    AT_CMD_SECUBOOT,
    AT_CMD_WIENABLE,
    AT_CMD_WIMODE,
    AT_CMD_WIBAND,
    AT_CMD_WIFREQ,
    AT_CMD_WIRATE,
    AT_CMD_WIPOW,
    AT_CMD_WITX,
    AT_CMD_WIRX,
    AT_CMD_WIRPCKG,
    AT_CMD_TMMI,
    AT_CMD_TSELRF,
    AT_CMD_TCHRENABLE,
    AT_CMD_TCHRINFO,
    AT_CMD_CDUR,
    AT_CMD_TSCREEN,
    AT_CMD_SSID,
    AT_CMD_WIKEY,
    AT_CMD_WILOG,
    /* Added by L00171473 for DTS2012020106679,AT WT工位 2012-01-17  Begin */
    AT_CMD_WIPARANGE,
    AT_CMD_WIINFO,
    /* Added by L00171473 for DTS2012020106679,AT WT工位 2012-01-17  End */
    AT_CMD_WUPWD,
    AT_CMD_BATVOL,
    AT_CMD_PRODTYPE,
    AT_CMD_FEATURE,

    AT_CMD_CTA,

    AT_CMD_CGMTU,


    /* DEL by c64416 for V9R1/V7R1 AT, 2013/09/18 */

    AT_CMD_BANDSW,
    AT_CMD_F_FCHANS,
    AT_CMD_F_FSEGMENT,
    AT_CMD_F_FPOWS,
    AT_CMD_F_FPAS,
    AT_CMD_F_FLNAS,
    AT_CMD_F_FTXWAVE,
    AT_CMD_F_FSTART,
    AT_CMD_F_FRSSIS,
    AT_CMD_F_FCMTMS,

    AT_CMD_F_FBLK,
    AT_CMD_F_FIPSTART,

    AT_CMD_F_FMAXPOWER,
    AT_CMD_F_FPAPOWER,
    /* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
    AT_CMD_F_FPDMS,
    /* Add by w00199382 for V7代码同步, 2012-04-07, End   */
   AT_CMD_F_FCALIIP2S,
   AT_CMD_F_FCALIDCOCS,
   AT_CMD_F_FGAINSTATES,
   AT_CMD_F_FDBBATTS,
   AT_CMD_F_FBBATTS,
   AT_CMD_F_FCALITXIQS,
    /*装备 快速校准 end */

/*  AT_CMD_FCHAN, */
/*  AT_CMD_FTXON, */
/*  AT_CMD_FRXON, */
    AT_CMD_FVCTCXO,
    AT_CMD_FQPDDCRES,
    AT_CMD_FCALPDDCS,
    AT_CMD_FPDPOWS,
    AT_CMD_FANT,
    AT_CMD_FPOW,
/*  AT_CMD_FPA, */
/*  AT_CMD_FDAC, */
/*  AT_CMD_FLNA, */
/*  AT_CMD_FRSSI, */

    /*非信令综测start */
    AT_CMD_SSYNC,
    AT_CMD_STXBW,
    AT_CMD_STXCHAN,
    AT_CMD_SSUBFRAME,
    AT_CMD_SPARA,

    AT_CMD_SSEGNUM,
    AT_CMD_STXMODUS,
    AT_CMD_STXRBNUMS,
    AT_CMD_STXRBPOSS,
    AT_CMD_STXPOWS,
    AT_CMD_STXCHANTYPES,
    AT_CMD_SSEGLEN,
    AT_CMD_SRXSET,
    AT_CMD_SRXPOW,
    AT_CMD_SRXSUBFRA,
    AT_CMD_SRXBLER,
    AT_CMD_SSTART,
    AT_CMD_SSTOP,


    AT_CMD_SMS_BEGAIN,
    AT_CMD_CSMS,
    AT_CMD_CPMS,
    AT_CMD_CMSQ,
    AT_CMD_CMGF,
    AT_CMD_CSCA,
    AT_CMD_CSMP,
    AT_CMD_CSDH,
    AT_CMD_CNMI,
    AT_CMD_CMGL,
    AT_CMD_CMGR,
    AT_CMD_CMGS,
    AT_CMD_CMGW,
    AT_CMD_CMGD,
    AT_CMD_CSSM,
    AT_CMD_CMGC,
    AT_CMD_CMSS,
    AT_CMD_CMST,
    AT_CMD_CNMA,
    AT_CMD_CCNMA,
    AT_CMD_CMSTUB,
    AT_CMD_CMMS,
    AT_CMD_RSTRIGGER,
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    AT_CMD_CSCB,
#endif
    AT_CMD_CLVL,
    AT_CMD_VMSET,
    AT_CMD_CRSM,
    AT_CMD_PNN,
    AT_CMD_CPNN,
    AT_CMD_OPL,
    AT_CMD_GLASTERR,
    AT_CMD_PCSCINFO,
    AT_CMD_CELLSRCH,
    AT_CMD_CCC,
    AT_CMD_PORT,
    AT_CMD_APTHROUGHPUT,
    AT_CMD_APDIALMODE,
    AT_CMD_APCONNST,
    AT_CMD_APPWRONREG,
    AT_CMD_GMI,
    AT_CMD_GMR,
    AT_CMD_WIFIGLOBALMAC,
    AT_CMD_CSQLVL,
    AT_CMD_SCID,
    AT_CMD_CSQLVLEXT,
    AT_CMD_DISSD,
    AT_CMD_SDREBOOT,
    AT_CMD_DOCK,
    AT_CMD_APPDMVER,
    AT_CMD_OPWORD,
    AT_CMD_CPWORD,
    AT_CMD_DISLOG,
#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
    AT_CMD_SHELL,
    AT_CMD_SPWORD,
#endif
    /* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
    AT_CMD_RSRPCFG,
    AT_CMD_RSCPCFG,
    AT_CMD_ECIOCFG,
    AT_CMD_CELLROAM,
    AT_CMD_PDPROFMOD,
    AT_CMD_FRSTATUS,
    /* Add by w00199382 for V7代码同步, 2012-04-07, End   */
    /*DTS2012041801532 w00182550 NV归一化 start in 2012-04-12 */
    AT_CMD_GETEXBANDINFO,
    AT_CMD_GETEXBANDTESTINFO,
    /*DTS2012041801532 w00182550 NV归一化 end in 2012-04-12 */
    AT_CMD_APBATLVL,
    AT_CMD_OPENPORT,
    AT_CMD_SDLOAD,
    AT_CMD_AUTHVER,
#if (FEATURE_ON == FEATURE_IPV6)
    AT_CMD_IPV6CAP,
    AT_CMD_DHCPV6,
    AT_CMD_APRAINFO,
    AT_CMD_APLANADDR,
#endif
    AT_CMD_VERTIME,
    AT_CMD_PRODNAME,
    AT_CMD_FWAVE,
    AT_CMD_EQVER,
    AT_CMD_APRPTSRVURL,
    AT_CMD_APXMLINFOTYPE,
    AT_CMD_APXMLRPTFLAG,

    AT_CMD_FASTDORM,

    AT_CMD_CGTFTRDP,
    AT_CMD_CGEQOS,
    AT_CMD_CGEQOSRDP,
    AT_CMD_CGCONTRDP,
    AT_CMD_CGSCONTRDP,

    AT_CMD_APCRADWIFIBS,
    AT_CMD_APNDISCON,
    AT_CMD_APCRADETHSTA,
    AT_CMD_APFMCDHCPSTA,
    AT_CMD_APDIALM,
    AT_CMD_APWIFIBS,
    AT_CMD_APWIFISEC,
    AT_CMD_APDHCP,
    AT_CMD_APCURPROF,
    AT_CMD_APPROFRD,

    /* Added by l00171473 for 内存监控AT命令, 2011-11-29,  begin */
    AT_CMD_MEMQUERY,
    /* Added by l00171473 for 内存监控AT命令, 2011-11-29,  end */
    AT_CMD_TBAT,
    AT_CMD_PSTANDBY,
    AT_CMD_WIWEP,
    AT_CMD_CMDLEN,

    AT_CMD_LOCINFO,
    AT_CMD_CIPHERQRY,
    AT_CMD_QRYNVRESUME,

    AT_CMD_NVBACKUPSTAT,
    AT_CMD_NANDBBC,
    AT_CMD_NANDVER,
    AT_CMD_CHIPTEMP,

    AT_CMD_CPIN2,
    AT_CMD_CSASM,
    AT_CMD_DNSQUERY,

    AT_CMD_APRPTPORTSEL,
    AT_CMD_CHDATA,
    AT_CMD_GPIO,
    AT_CMD_USBSWITCH,

    AT_CMD_RSFR,
    AT_CMD_RSFW,
    AT_CMD_ANTSTATE,
    AT_CMD_SARREDUCTION,

    AT_CMD_HUK,
    AT_CMD_FACAUTHPUBKEY,
    AT_CMD_IDENTIFYSTART,
    AT_CMD_IDENTIFYEND,
    AT_CMD_SIMLOCKDATAWRITE,
    AT_CMD_PHONESIMLOCKINFO,
    AT_CMD_SIMLOCKDATAREAD,
    AT_CMD_PHONEPHYNUM,
    AT_CMD_PORTCTRLTMP,
    AT_CMD_PORTATTRIBSET,

    AT_CMD_APSIMST,

    AT_CMD_CPOS,
    AT_CMD_CPOSR,
    AT_CMD_XCPOSR,
    AT_CMD_CGPSCLOCK,

    AT_CMD_CGPSINFO,
    AT_CMD_LOGCFG,
    AT_CMD_LOGSAVE,
    AT_CMD_LOGNVE,

    AT_CMD_CCMGS,
    AT_CMD_CCMGW,
    AT_CMD_CCMGD,
    AT_CMD_CCSASM,


#if ( VOS_WIN32 == VOS_OS_VER )
    AT_CMD_SETRPLMN,
#endif

    /* DEL by c64416 for V9R1/V7R1 AT, 2013/09/18 */

    AT_CMD_NVM,

    AT_CMD_CMUT,

    #if(FEATURE_ON == FEATURE_UE_MODE_TDS)
    AT_CMD_SCELLINFO,
    AT_CMD_SCALIB,

    AT_CMD_CMTM,
    #endif

    AT_CMD_APSEC,
    AT_CMD_CISA,

    AT_CMD_SIMLOCKUNLOCK,

    AT_CMD_APDS,
    AT_CMD_CLPR,
    AT_CMD_CCSERR,
    AT_CMD_WLTHRESHOLDCFG,
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    AT_CMD_ACINFO,
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */
    AT_CMD_CLTEROAMALLOW,

    AT_CMD_SWVER,

    AT_CMD_CBG,

    AT_CMD_MMPLMNINFO,

    AT_CMD_EONSUCS2,

    AT_CMD_PLMN,
    AT_CMD_XLEMA,
    AT_CMD_COPN,
    AT_CMD_BODYSARON,

    AT_CMD_BODYSARWCDMA,
    AT_CMD_BODYSARGSM,

    AT_CMD_IMEIVERIFY,
    /* Modified by L60609 for add app vcom，2013-06-17,  Begin */
    AT_CMD_LOGPORT,
    /* Modified by L60609 for add app vcom，2013-06-17,  End */

    AT_CMD_NVRD,
    AT_CMD_NVWR,
    AT_CMD_NVRDLEN,
    AT_CMD_NVRDEX,
    AT_CMD_NVWREX,

    AT_CMD_NVWRPART,

    AT_CMD_STCFGDPCH,
    AT_CMD_STRXBER,

    AT_CMD_NCELLMONITOR,
    AT_CMD_USERSRVSTATE,

    AT_CMD_SIMSLOT,

    AT_CMD_SIMINSERT,

    AT_CMD_MODEMLOOP,

    AT_CMD_RELEASERRC,

    AT_CMD_REFCLKFREQ,

    AT_CMD_PULLOMLOG,

    AT_CMD_REJINFO,

    AT_CMD_PLMNSELEINFO,

    AT_CMD_DIESN,
    AT_CMD_CHIPSN,
    AT_CMD_HANDLEDECT,

    AT_CMD_HVSDH,
    AT_CMD_HVSST,
    AT_CMD_HVSCONT,
    AT_CMD_HVPDH,
    AT_CMD_SCICHG,
    AT_CMD_HVTEE,
    AT_CMD_HVCHECKCARD,

    AT_CMD_EOPLMN,

    AT_CMD_NETSCAN,

#if (FEATURE_ON == FEATURE_AT_HSUART)
    AT_CMD_IPR,
    AT_CMD_ICF,
    AT_CMD_IFC,
#endif

    AT_CMD_FPLLSTATUS,

    /* Added by l00198894 for 新增+ECID命令, 2013-12-09, begin */
    AT_CMD_ECID,
    /* Added by l00198894 for 新增+ECID命令, 2013-12-09, end */


    AT_CMD_SWITCH_UART,

    AT_CMD_MIPICLK,

    AT_CMD_CLCC_IMS,
#if (FEATURE_ON == FEATURE_IMS)
    AT_CMD_CIREG,
    AT_CMD_CIREP,
    AT_CMD_VOLTEIMPU,
    AT_CMD_CCWAI,
    AT_CMD_UICCAUTH,
    AT_CMD_CURSM,
    AT_CMD_KSNAFAUTH,
#endif

    AT_CMD_ANTSWITCH,
    /* GU模AT命令和公共命令的索引ID最大值，新增命令ID时要添加到此ID前 */

    AT_CMD_CIMSROAMINGSTUB,
    AT_CMD_CREDIALSTUB,
    AT_CMD_IMSVOICEINTERSYSLAUSTUB,
    AT_CMD_IMSVOICEMMENABLESTUB,

    AT_CMD_CIMSUSSDSTUB,

#if (FEATURE_ON == FEATURE_IMS)
    AT_CMD_CACMIMS,
#endif

    AT_CMD_DPDTTEST,
    AT_CMD_DPDT,
    AT_CMD_DPDTQRY,

    /* Added by n00269697 for V3R3C60_eCall项目, 2014-3-29, begin */
    AT_CMD_CECALL,
    AT_CMD_ECLSTART,
    AT_CMD_ECLSTOP,
    AT_CMD_ECLCFG,
    AT_CMD_ECLMSD,
    /* Added by n00269697 for V3R3C60_eCall项目, 2014-3-29, end */

#if (FEATURE_ON == FEATURE_DSDS)
    AT_CMD_PSPROTECTMODE,
#endif
    AT_CMD_PHYINIT,

    AT_CMD_FPOWDET,

    AT_CMD_JDETEX,

    AT_CMD_RATFREQLOCK,

#if (FEATURE_ON == FEATURE_IMS)
    AT_CMD_CALL_MODIFY_INIT,
    AT_CMD_CALL_MODIFY_ANS,
    AT_CMD_ECONFDIAL,
    AT_CMD_CLCCECONF,
    AT_CMD_ECONFERR,
#endif
    AT_CMD_CHLD_EX,

    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
    AT_CMD_CDMACONNST,
    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

    AT_CMD_GSMFREQLOCK,

    AT_CMD_ACTIVEMODEM,


    AT_CMD_CCLK,

    AT_CMD_CTZU,

    AT_CMD_CFSH,

    AT_CMD_CRM,

    AT_CMD_CARDTYPE,

    AT_CMD_CQOSPRI,

    AT_CMD_CBURSTDTMF,

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    AT_CMD_CLOCINFO,
    AT_CMD_CSID,
    AT_CMD_QCCB,
    AT_CMD_EMCCBM,
    AT_CMD_CSIDLIST,
    AT_CMD_ECCALL,
    AT_CMD_ECCTRL,
    AT_CMD_ECCAP,
    AT_CMD_ECRANDOM,
    AT_CMD_ECKMC,
    AT_CMD_ECCTEST,
#endif

    AT_CMD_CCLPR,


    AT_CMD_CDMACSQ,
    AT_CMD_CFREQLOCK,

    AT_CMD_HDRCSQ,

    AT_CMD_APDSFLOWRPTCFG,

    AT_CMD_IMSSWITCH,
    AT_CMD_CEVDP,

    AT_CMD_DSFLOWNVWRCFG,
#if (FEATURE_ON == FEATURE_HUAWEI_VP)
    AT_CMD_VOICEPREFER,
#endif

    AT_CMD_CUSTOMDIAL,

    AT_CMD_CDMAMODEMSWITCH,

    AT_CMD_TTYMODE,
    AT_CMD_FEMCTRL,

    AT_CMD_NVWRSECCTRL,

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
    AT_CMD_CRLA,
    AT_CMD_CARDSESSION,
    AT_CMD_PRFAPP,
    AT_CMD_CCIMI,
#endif

    AT_CMD_RATRFSWITCH,

    AT_CMD_1XCHAN,
    AT_CMD_CVER,
    AT_CMD_CCMGG,
    AT_CMD_GETSTA,
    AT_CMD_GETESN,
    AT_CMD_GETMEID,
    AT_CMD_CHIGHVER,

#if(FEATURE_ON == FEATURE_LTE)
#if(FEATURE_ON == FEATURE_LTE_MBMS)
    AT_CMD_MBMSCMD,
    AT_CMD_MBMSEV,
    AT_CMD_MBMSINTERESTLIST,
#endif
    AT_CMD_LTELOWPOWER,
    AT_CMD_ISMCOEX,
#endif
    AT_CMD_CAGPSCFGPOSMODE,
    AT_CMD_CAGPSSTART,
    AT_CMD_CAGPSSTOP,
    AT_CMD_CAGPSCFGMPCADDR,
    AT_CMD_CAGPSCFGPDEADDR,
    AT_CMD_CAGPSQRYREFLOC,
    AT_CMD_CAGPSQRYTIME,
    AT_CMD_CAGPSREPLYNIREQ,
    AT_CMD_CAGPSPRMINFO,
    AT_CMD_CAGPSDATACALLSTATUS,
    AT_CMD_CUPBINDSTATUS,
    AT_CMD_CAGPSFORWARDDATA,

    AT_CMD_CAGPSPOSINFO,
    AT_CMD_CGPSCONTROLSTART,
    AT_CMD_CGPSCONTROLSTOP,
    AT_CMD_MEID,

    AT_CMD_IMSPDPCFG,

    AT_CMD_TRANSMODE,

    AT_CMD_CCONTDTMF,

    AT_CMD_CDORMTIMER,
    AT_CMD_MCCFREQ,
    AT_CMD_HPLMN,
    AT_CMD_DPLMNLIST,
    AT_CMD_CSGIDSEARCH,
    AT_CMD_UE_CENTER,
    AT_CMD_MIPIWR,
    AT_CMD_MIPIRD,
    AT_CMD_SSIWR,
    AT_CMD_SSIRD,
    AT_CMD_LOGENALBE,

    AT_CMD_ACTPDPSTUB,

    AT_CMD_MONSC,
    AT_CMD_MONNC,
    AT_CMD_NVCHK,

    AT_CMD_PDMCTRL,

    AT_CMD_CSNID,

    AT_CMD_AFCCLKINFO,

    AT_CMD_CPMP,

    AT_CMD_SECURESTATE,
    AT_CMD_KCE,
    AT_CMD_SOCID,

    AT_CMD_COMM_BUTT,

}AT_CMD_INDEX_ENUM;

typedef enum
{
    AT_CMD_CURRENT_OPT_BUTT                                 = 0,
    AT_CMD_D_GET_NUMBER_BEFORE_CALL,

    AT_CMD_D_CS_VOICE_CALL_SET,

    AT_CMD_D_CS_DATA_CALL_SET,

    AT_CMD_D_PPP_CALL_SET,
    AT_CMD_PPP_ORG_SET,

    AT_CMD_PS_DATA_CALL_END_SET,

    AT_CMD_WAIT_PPP_PROTOCOL_REL_SET,

    AT_CMD_D_IP_CALL_SET,
    AT_CMD_CGDATA_SET,

    AT_CMD_CGACT_ORG_SET,
    AT_CMD_CGACT_END_SET,
    AT_CMD_CGANS_ANS_SET,
    AT_CMD_CGANS_ANS_EXT_SET,

    AT_CMD_CMMI_SET,
    AT_CMD_CMMI_QUERY_CLIP,
    AT_CMD_CMMI_QUERY_CLIR,

    AT_CMD_H_SET,
    AT_CMD_END_SET,
    AT_CMD_CALL_END_SET,
    AT_CMD_H_PS_SET,

    AT_CMD_A_SET,

    AT_CMD_S0_SET,
    AT_CMD_S0_READ,

    AT_CMD_CGMI_READ,

    AT_CMD_CGMM_READ,

    AT_CMD_CGMR_READ,

    AT_CMD_CGSN_READ,

    AT_CMD_CIMI_READ,
    AT_CMD_ICCID_READ,
    AT_CMD_CSTA_SET,
    AT_CMD_CSTA_READ,

    AT_CMD_CHUP_SET,

    /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, begin */
    AT_CMD_DTMF_SET,
    AT_CMD_VTS_SET,
    /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, end */

    AT_CMD_CLIP_READ,

    AT_CMD_COLP_READ,
    AT_CMD_CLIR_SET,
    AT_CMD_CLIR_READ,
    AT_CMD_CLCC_SET,
    /* AT+CAPS命令实体的设置参数状态 */
    AT_CMD_CPAS_SET,

    AT_CMD_COPS_SET_AUTOMATIC,
    AT_CMD_COPS_SET_MANUAL,
    AT_CMD_COPS_SET_DEREGISTER,
    AT_CMD_COPS_SET_MANUAL_AUTOMATIC_MANUAL,
    AT_CMD_COPS_READ,
    AT_CMD_COPS_TEST,
    AT_CMD_COPS_ABORT_PLMN_LIST,

    AT_CMD_CPOL_SET,
    AT_CMD_CPOL_READ,
    AT_CMD_CPOL_TEST,

    AT_CMD_CFUN_SET,
    AT_CMD_CFUN_READ,

    AT_CMD_CBND_SET,
    AT_CMD_CBND_READ,

    AT_CMD_CSQ_SET,
    AT_CMD_CBC_SET,

    AT_CMD_CPBF_SET,
    AT_CMD_CPBR_SET,
    AT_CMD_CPBR2_SET,
    AT_CMD_SCPBR_SET,
    AT_CMD_CPBW_SET,
    AT_CMD_CNUM_READ,

    AT_CMD_CSIM_SET,
    AT_CMD_CCHO_SET,
    AT_CMD_CCHC_SET,
    AT_CMD_CGLA_SET,
    AT_CMD_CRSM_SET,
    AT_CMD_CPIN_VERIFY_SET,
    AT_CMD_CPIN_UNBLOCK_SET,
    AT_CMD_CPIN_READ,

    AT_CMD_CPWD_SET,
    AT_CMD_CPWD_CHANGE_PIN,

    AT_CMD_CLCK_PIN_HANDLE,
    AT_CMD_CARD_LOCK_SET,
    AT_CMD_CARD_LOCK_READ,
    AT_CMD_CARD_ATR_READ,
    AT_CMD_CLCK_UNLOCK,
    AT_CMD_CLCK_LOCK,
    AT_CMD_CLCK_QUERY,
    AT_CMD_CLCK_SIMLOCKUNLOCK,
    AT_CMD_CLCK_SIMLOCKDATAREAD,
    AT_CMD_CTFR_SET,

    AT_CMD_CGEQREQ_SET,
    AT_CMD_CGEQREQ_READ,

    AT_CMD_CGEQMIN_SET,
    AT_CMD_CGEQMIN_READ,

    AT_CMD_CGPADDR_SET,
    AT_CMD_CGEQNEG_SET,
    AT_CMD_CGEQNEG_TEST,

    AT_CMD_CGACT_READ,

    AT_CMD_CGCLASS_SET,
    AT_CMD_CGCLASS_READ,

    AT_CMD_CGATT_ATTACH_SET,
    AT_CMD_CGATT_DETAACH_SET,

    AT_CMD_CGCATT_PS_ATTACH_SET,
    AT_CMD_CGCATT_CS_ATTACH_SET,
    AT_CMD_CGCATT_PS_CS_ATTACH_SET,
    AT_CMD_CGCATT_PS_DETAACH_SET,
    AT_CMD_CGCATT_CS_DETAACH_SET,
    AT_CMD_CGCATT_PS_CS_DETAACH_SET,

    AT_CMD_CGDCONT_SET,
    AT_CMD_CGDCONT_READ,

    AT_CMD_CGREG_READ,

    AT_CMD_CEREG_READ,

    AT_CMD_CGDSCONT_SET,
    AT_CMD_CGDSCONT_READ,

    AT_CMD_CGTFT_SET,
    AT_CMD_CGTFT_READ,

    AT_CMD_CGDNS_SET,
    AT_CMD_CGDNS_READ,

    AT_CMD_CGCMOD_SET,

    AT_CMD_CGAUTO_SET,
    AT_CMD_CGAUTO_READ,

    AT_CMD_AUTHDATA_SET,
    AT_CMD_AUTHDATA_READ,
    /* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
    AT_CMD_PDPROFMOD_SET,
    /* Add by w00199382 for V7代码同步, 2012-04-07, End   */
    /* 异步消息实现增加的操作标记 */
    AT_CMD_D_GPRS_SET,
    AT_CMD_NDISCONN_SET,
    AT_CMD_DSFLOWCLR_SET,
    AT_CMD_DSFLOWQRY_SET,
    AT_CMD_DSFLOWRPT_SET,
    AT_CMD_DWINS_SET,
    AT_CMD_PDPSTUB_SET,
    AT_CMD_CGCONTRDP_SET,
    AT_CMD_CGSCONTRDP_SET,
    AT_CMD_CGTFTRDP_SET,
    AT_CMD_DHCP_READ,

    AT_CMD_CGEQOS_SET,
    AT_CMD_CGEQOS_READ,
    AT_CMD_CGEQOSRDP_SET,
    AT_CMD_NDISSTATQRY_READ,

    /* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
    AT_CMD_LTECS_READ,
    AT_CMD_CEMODE_SET,
    AT_CMD_CEMODE_READ,
    /* Add by w00199382 for V7代码同步, 2012-04-07, End   */
    AT_CMD_CREG_READ,

    AT_CMD_CCUG_SET,
    AT_CMD_CCUG_READ,

    AT_CMD_CCWA_DISABLE,
    AT_CMD_CCWA_ENABLE,
    AT_CMD_CCWA_QUERY,

    AT_CMD_CNMR_QUERY,
    AT_CMD_CECELLID_QUERY,

    AT_CMD_CCFC_DISABLE,
    AT_CMD_CCFC_ENABLE,
    AT_CMD_CCFC_QUERY,
    AT_CMD_CCFC_REGISTRATION,
    AT_CMD_CCFC_ERASURE,

    AT_CMD_CUSD_REQ,
    /* Deleted by s00217060 for 主动上报AT命令控制下移至C核, 2013-5-6, begin */
    /* Deleted by s00217060 for 主动上报AT命令控制下移至C核, 2013-5-6, end */

    AT_CMD_CHLD_SET,

    AT_CMD_CMOD_SET,
    AT_CMD_CMOD_READ,

    AT_CMD_CBST_SET,
    AT_CMD_CBST_READ,

    AT_CMD_CSMS_SET,
    AT_CMD_CSMS_READ,

    AT_CMD_CMSQ_SET,

    AT_CMD_CMGF_SET,
    AT_CMD_CMGF_READ,

    AT_CMD_CSCA_SET,
    AT_CMD_CSCA_READ,

    AT_CMD_CSMP_SET,
    AT_CMD_CSMP_READ,

    AT_CMD_CMGL_SET,

    AT_CMD_CMGR_SET,

    AT_CMD_CMGS_TEXT_SET,
    AT_CMD_CMGS_PDU_SET,

    AT_CMD_CNMA_TEXT_SET,
    AT_CMD_CNMA_PDU_SET,
    AT_CMD_CMSS_SET,
    AT_CMD_CMST_SET,

    AT_CMD_CMGW_TEXT_SET,
    AT_CMD_CMGW_PDU_SET,

    AT_CMD_CMGD_SET,
    AT_CMD_CMGD_TEST,

    AT_CMD_CMGI_SET,

    AT_CMD_CMGC_TEXT_SET,
    AT_CMD_CMGC_PDU_SET,

    AT_CMD_CGSMS_SET,
    AT_CMD_CGSMS_READ,

    AT_CMD_CMMT_SET,

    AT_CMD_CSCB_SET,
    AT_CMD_CSCB_READ,

    AT_CMD_CBMGR_SET,

    AT_CMD_CBMGL_SET,

    AT_CMD_CBMGD_SET,

    AT_CMD_CCNMA_SET,
    AT_CMD_CCNMA_READ,

    AT_CMD_CPBS_SET,
    AT_CMD_CPBS_READ,

    AT_CMD_CPAM_SET,
    AT_CMD_CPAM_READ,

    AT_CMD_CPIN2_VERIFY_SET,
    AT_CMD_CPIN2_UNBLOCK_SET,
    AT_CMD_CPIN2_READ,

    AT_CMD_CNMI_SET,

    AT_CMD_CSSM_SET,
    AT_CMD_CSSM_READ,

    AT_CMD_CPMS_SET,
    AT_CMD_CPMS_READ,

    AT_CMD_CMMS_SET,
    AT_CMD_CMMS_READ,

    /* Added by f62575 for AT Project，2011-10-03,  Begin*/
    AT_CMD_CMSTUB_SET,                                                          /* 标示命令^CMSTUB设置操作 */
    AT_CMD_DLOADINFO_READ,                                                      /* 标示命令^DLOADINFO查询操作 */
    AT_CMD_AUTHORITYVER_READ,                                                   /* 标示命令^AUTHORITYVER查询操作 */
    AT_CMD_AUTHORITYID_READ,                                                    /* 标示命令^AUTHORITYID查询操作 */
    AT_CMD_GODLOAD_SET,                                                         /* 标示命令^GODLOAD设置操作 */
    AT_CMD_SDLOAD_SET,                                                          /* 标示命令^SDLOAD设置操作 */

    AT_CMD_HWNATQRY_READ,                                                       /* 标示命令^HWNATQRY查询操作 */
    AT_CMD_FLASHINFO_READ,                                                      /* 标示命令^FLASHINFO查询操作 */
    AT_CMD_AUTHVER_READ,                                                        /* 标示命令^AUTHVER查询操作 */

    AT_CMD_CDUR_READ,                                                           /* 标示命令^CDUR查询操作 */
    AT_CMD_PFVER_READ,                                                          /* 标示命令^PFVER查询操作 */
    AT_CMD_DLOADVER_READ,                                                       /* 标示命令^DLOADVER查询操作 */
    /* Added by 傅映君/f62575 for CPULOAD&MFREELOCKSIZE处理过程移至C核, 2011/11/15, begin */
    AT_CMD_CPULOAD_READ,                                                        /* 标示命令^CPULOAD查询操作 */
    AT_CMD_MFREELOCKSIZE_READ,                                                  /* 标示命令^MFREELOCKSIZE查询操作 */
    /* Added by 傅映君/f62575 for CPULOAD&MFREELOCKSIZE处理过程移至C核, 2011/11/15, end */
    /* Added by f62575 for AT Project，2011-10-03,  End*/

    /* Added by l00171473 for 内存监控AT命令, 2011-11-29,  begin */
    AT_CMD_MEMINFO_READ,
    /* Added by l00171473 for 内存监控AT命令, 2011-11-29,  end */

    AT_CMD_STPD_SET,
    AT_CMD_CLVL_SET,
    AT_CMD_VMSET_SET,
    AT_CMD_F_SET,
    AT_CMD_VMSET_READ,                                                          /* AT^VMSET命令实体查询状态 */
    AT_CMD_CVOICE_READ,                                                         /* AT^CVOICE命令实体查询状态 */
    AT_CMD_DDSETEX_SET,                                                         /* AT^DDSETEX命令实体设置状态 */
    AT_CMD_DDSETEX_READ,                                                        /* AT^DDSETEX命令实体查询状态 */
    AT_CMD_NVRESTORE_READ,
    AT_CMD_NVRSTSTTS_READ,
    AT_CMD_CVOICE_SET,
    AT_CMD_STMN_SET,
    AT_CMD_STTR_SET,
    AT_CMD_STEN_SET,
    AT_CMD_STGI_SET,
    AT_CMD_STGR_SET,
    AT_CMD_IMSICHG_SET,
    AT_CMD_IMSICHG_READ,
    AT_CMD_INFORBU_SET,
    /* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
    AT_CMD_INFORRS_SET,
    /* Add by w00199382 for V7代码同步, 2012-04-07, End   */
    AT_CMD_CPNN_TEST,
    AT_CMD_CSEN_SET,
    AT_CMD_CSTR_SET,
    AT_CMD_CFRQ_SET,
    AT_CMD_CFRQ_READ,
    AT_CMD_CIMEI_SET,
    AT_CMD_CQST_SET,
    AT_CMD_CDEF_SET,
    AT_CMD_CQST_READ,
    AT_CMD_CAATT_SET,
    AT_CMD_CAATT_READ,
    AT_CMD_SYSINFO_READ,
    AT_CMD_SYSINFOEX_READ,
    AT_CMD_CFPLMN_SET,
    AT_CMD_CFPLMN_READ,
    AT_CMD_SYSCFG_SET,
    AT_CMD_SYSCFG_READ,
    AT_CMD_SYSCFG_TEST,
    AT_CMD_SYSCFGEX_READ,
    AT_CMD_SYSCFGEX_TEST,
    AT_CMD_PNN_READ,
    AT_CMD_CPNN_READ,
    AT_CMD_OPL_READ,
    AT_CMD_HS_READ,
    AT_CMD_SS_REGISTER,
    AT_CMD_SS_ERASE,
    AT_CMD_SS_ACTIVATE,
    AT_CMD_SS_DEACTIVATE,
    AT_CMD_SS_INTERROGATE,
    AT_CMD_SS_REGISTER_PSWD,
    /* Delete AT_CMD_SS_GET_PSWD */
    AT_CMD_SS_USSD,
    AT_CMD_SET_TMODE,
    AT_CMD_SET_FTXON,
    AT_CMD_SET_FRXON,
    AT_CMD_SET_FWAVE,                                                           /* 标示命令^FWAVE设置操作 */
    AT_CMD_QUERY_RSSI,
    AT_CMD_SET_RXDIV,
    AT_CMD_SET_RXPRI,
    AT_CMD_SS_DEACTIVE_CCBS,
    AT_CMD_SS_INTERROGATE_CCBS,
    AT_CMD_CSQLVLEXT_SET,
    AT_CMD_CSQLVL_SET,                                                          /* 标示命令^CSQLVL设置操作 */
    AT_CMD_APPDMVER_READ,                                                       /* 标示命令^APPDMVER查询操作 */
    AT_CMD_APBATLVL_READ,                                                       /* 标示命令^APBATLVL查询操作 */
    AT_CMD_MSID_READ,
    AT_CMD_CWAS_QUERY,
    AT_CMD_CGAS_QUERY,
    AT_CMD_CELLINFO_QUERY,
    AT_CMD_MEANRPT_QUERY,
    AT_CMD_REGISTER_TIME_READ,
    AT_CMD_ANQUERY_READ,
    AT_CMD_HOMEPLMN_READ,
    AT_CMD_VERSIONTIME_READ,
    AT_CMD_FREQLOCK_SET,
    AT_CMD_FREQLOCK_QUERY,
    AT_CMD_CSNR_QUERY,
    AT_CMD_RRC_VERSION_SET,
    AT_CMD_RRC_VERSION_QUERY,
    AT_CMD_YJCX_SET,
    AT_CMD_YJCX_QUERY,
    AT_CMD_CRPN_QUERY,
    AT_CMD_SPN_QUERY,
    AT_CMD_CC_STATE_QUERY,
    AT_CMD_MM_TEST_CMD_SET,


    AT_CMD_RSIM_READ,
    AT_CMD_GPIOPL_SET,
    AT_CMD_GPIOPL_QRY,
    AT_CMD_DATALOCK_SET,
    AT_CMD_TBATVOLT_QRY,
    AT_CMD_VERSION_QRY,
    AT_CMD_SECUBOOT_QRY,
    AT_CMD_SECUBOOT_SET,
    AT_CMD_SECUBOOTFEATURE_QRY,
    AT_CMD_PRODTYPE_QRY,
    AT_CMD_SFEATURE_QRY,
    AT_CMD_FCHAN_SET,
    AT_CMD_RXPRI_QRY,
    AT_CMD_TSELRF_SET,
    AT_CMD_TBAT_SET,
    AT_CMD_TBAT_QRY,
    /* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
    AT_CMD_STANDBY_SET,
    /* Add by w00199382 for V7代码同步, 2012-04-07, End   */
    AT_CMD_DRV_AGENT_HARDWARE_QRY,
    AT_CMD_DRV_AGENT_FULL_HARDWARE_QRY,
    AT_CMD_WAS_MNTN_SET_CELLSRH,
    AT_CMD_WAS_MNTN_QRY_CELLSRH,
    AT_CMD_DRV_AGENT_RXDIV_SET_REQ,
    AT_CMD_DRV_AGENT_RXDIV_QRY_REQ,
    AT_CMD_DRV_AGENT_SIMLOCK_SET_REQ,
    AT_CMD_MMA_GET_CURRENT_ATTACH_STATUS,
    AT_CMD_APP_QRY_ALS_REQ,
    AT_CMD_MMA_MT_POWER_DOWN,
    AT_CMD_MMA_SET_PREF_PLMN,
    AT_CMD_MMA_SET_PREF_PLMN_TYPE,
    AT_CMD_APP_SET_UUSINFO_REQ,
    AT_CMD_APP_SET_ALS_REQ,
    AT_CMD_MSG_MMA_SET_PIN,
    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    AT_CMD_CSSN_SET,
    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */


    /* 一键升级 lkf58113 @20111011 */
    AT_CMD_BOOTROMVER_READ,

    AT_CMD_NVBACKUP_SET,
    AT_CMD_NVRESTORE_SET,
    AT_CMD_RESET_SET,
    AT_CMD_NVRSTSTTS_SET,
    /* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
    AT_CMD_TBAT_READ,
    AT_CMD_SECUBOOTFEATURE_READ,
    /* Add by w00199382 for V7代码同步, 2012-04-07, End   */

    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    AT_CMD_CURC_READ,
    AT_CMD_UNSOLICITED_RPT_SET,
    AT_CMD_UNSOLICITED_RPT_READ,
    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-1, end */
    AT_CMD_NCELL_MONITOR_SET,
    AT_CMD_NCELL_MONITOR_READ,
    AT_CMD_USER_SRV_STATE_READ,

    /*装备 快速校准 c00172979 start 20110727 */
    AT_CMD_TMODE_SET,
    AT_CMD_TMODE_READ,
    AT_CMD_TMODE_TEST,

    AT_CMD_BANDSW_SET,
    AT_CMD_BANDSW_READ,

    AT_CMD_F_FCHANS_SET,
    AT_CMD_F_FCHANS_READ,

    AT_CMD_F_FSEGMENT_SET,
    AT_CMD_F_FSEGMENT_READ,

    AT_CMD_F_FPOWS_SET,
    AT_CMD_F_FPOWS_READ,

    AT_CMD_F_FPAS_SET,
    AT_CMD_F_FPAS_READ,

    AT_CMD_F_FLNAS_SET,
    AT_CMD_F_FLNAS_READ,

    AT_CMD_F_FTXWAVE_SET,
    AT_CMD_F_FTXWAVE_READ,

    AT_CMD_F_FSTART_SET,
    AT_CMD_F_FSTART_READ,

    AT_CMD_F_FRSSIS_SET,

    AT_CMD_F_FCMTMS_READ,

    AT_CMD_F_FBLK_SET,
    AT_CMD_F_FBLK_READ,

    AT_CMD_F_FIPSTART_SET,

    /* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
    AT_CMD_F_FPDMS_SET,
    /* Add by w00199382 for V7代码同步, 2012-04-07, End   */

    AT_CMD_F_FMAXPOWER_SET,
    AT_CMD_F_FMAXPOWER_READ,

    AT_CMD_F_FPAPOWER_SET,
    AT_CMD_F_FPAPOWER_READ,

    /* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
    AT_CMD_F_FPDMS_READ,
    /* Add by w00199382 for V7代码同步, 2012-04-07, End   */

    /*装备 快速校准 c00172979 end 20110727 */

    /*  AT_CMD_FCHAN_SET, */
    AT_CMD_FCHAN_READ,

    AT_CMD_FANT_SET,
    AT_CMD_FANT_READ,

    AT_CMD_FPOW_SET,

    AT_CMD_FPA_SET,
    AT_CMD_FDAC_SET,

    AT_CMD_FLNA_SET,
    AT_CMD_FLNA_READ,

    AT_CMD_FTXON_SET,
    AT_CMD_FTXON_READ,

    AT_CMD_FRXON_SET,
    AT_CMD_FRXON_READ,

    AT_CMD_FVCTCXO_SET,
    AT_CMD_FVCTCXO_READ,

    AT_CMD_FRSSI_READ,

    /*非信令综测start */
    AT_CMD_SSYNC_SET,
    AT_CMD_SSYNC_READ,

    AT_CMD_STXBW_SET,
    AT_CMD_STXBW_READ,

    AT_CMD_STXCHAN_SET,
    AT_CMD_STXCHAN_READ,

    AT_CMD_SSUBFRAME_SET,
    AT_CMD_SSUBFRAME_READ,

    AT_CMD_SPARA_SET,
    AT_CMD_SPARA_READ,

    AT_CMD_SSEGNUM_SET,
    AT_CMD_SSEGNUM_READ,

    AT_CMD_STXMODUS_SET,
    AT_CMD_STXMODUS_READ,

    AT_CMD_STXRBNUMS_SET,
    AT_CMD_STXRBNUMS_READ,

    AT_CMD_STXRBPOSS_SET,
    AT_CMD_STXRBPOSS_READ,

    AT_CMD_STXPOWS_SET,
    AT_CMD_STXPOWS_READ,

    AT_CMD_STXCHANTYPES_SET,
    AT_CMD_STXCHANTYPES_READ,

    AT_CMD_SSEGLEN_SET,
    AT_CMD_SSEGLEN_READ,

    AT_CMD_SRXSET_SET,
    AT_CMD_SRXSET_READ,

    AT_CMD_SRXPOW_SET,
    AT_CMD_SRXPOW_READ,

    AT_CMD_SRXSUBFRA_SET,
    AT_CMD_SRXSUBFRA_READ,

    AT_CMD_SRXBLER_READ,

    AT_CMD_SSTART_SET,
    AT_CMD_SSTART_READ,

    AT_CMD_SSTOP_SET,

    AT_CMD_CIPERQRY_READ,
    AT_CMD_LOCINFO_READ,
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    AT_CMD_ACINFO_READ,
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    AT_CMD_CERSSI_READ,

    //非信令综测end
    AT_CMD_ADC_SET,
    AT_CMD_FASTDORM_SET,
    AT_CMD_FASTDORM_READ,
    AT_CMD_APTHROUGH_PUT_READ,                                                  /* 标示命令^APTHROUGHPUT查询操作 */
    AT_CMD_APDIALMODE_READ,                                                     /* 标示命令^APDIALMODE查询操作 */

    AT_CMD_ACPUMEMINFO,
    AT_CMD_CCPUMEMINFO,
#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
    AT_CMD_SPWORD_SET,
#endif
    AT_CMD_SIMLOCKSTATUS_READ,
    AT_CMD_CSDFLT_READ,

    AT_CMD_CGPADDR_TEST,

    AT_CMD_NVBACKUPSTAT_READ,
    AT_CMD_NANDBBC_READ,
    AT_CMD_NANDVER_READ,
    AT_CMD_CHIPTEMP_READ,

    AT_CMD_CSASM_SET,
    AT_CMD_DNSQUERY_SET,
  /* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
    AT_CMD_CELLROAM_READ,

    AT_CMD_TCHRENABLE_SET,
    AT_CMD_TCHRENABLE_TEST,
  /* Add by w00199382 for V7代码同步, 2012-04-07, End   */
    AT_CMD_RSFR_VERSION_QRY,

    AT_CMD_MAXLCKTMS_SET,                                                       /* 标示命令^MAXLCKTMS设置操作 */

    AT_CMD_HUK_SET,
    AT_CMD_FACAUTHPUBKEY_SET,
    AT_CMD_IDENTIFYSTART_SET,
    AT_CMD_IDENTIFYEND_SET,
    AT_CMD_SIMLOCKDATAWRITE_SET,
    AT_CMD_PHONESIMLOCKINFO_READ,
    AT_CMD_SIMLOCKDATAREAD_READ,
    AT_CMD_PHONEPHYNUM_SET,
    AT_CMD_PHONEPHYNUM_READ,
    AT_CMD_PORTCTRLTMP_SET,
    AT_CMD_PORTCTRLTMP_READ,
    AT_CMD_PORTATTRIBSET_SET,
    AT_CMD_PORTATTRIBSET_READ,
    AT_CMD_OPWORD_SET,
    AT_CMD_CLVL_READ,

    AT_CMD_APSIMST_SET,

#if(FEATURE_ON == FEATURE_UE_MODE_TDS)
    AT_CMD_SCALIB_SET,
    AT_CMD_SCALIB_READ,
    AT_CMD_SCELLINFO_READ,

    AT_CMD_CMTM_READ,
#endif
/* Added by y00213812 for V7R1C50 A-GPS Project，2012-06-28,  begin*/
    AT_CMD_CPOS_SET,
    AT_CMD_CGPSCLOCK_SET,
/* Added by y00213812 for V7R1C50 A-GPS Project，2012-06-28,  end*/

    /* DEL by c64416 for V9R1/V7R1 AT, 2013/09/18 */

    AT_CMD_CERSSI_SET,
    AT_CMD_CNMR_READ,
    AT_CMD_CELL_ID_READ,
    AT_CMD_CPSERR_SET,

    AT_CMD_APSEC_SET,
    AT_CMD_CISA_SET,

    AT_CMD_CMUT_SET,
    AT_CMD_CMUT_READ,

    AT_CMD_SIMLOCKUNLOCK_SET,

    AT_CMD_CLPR_SET,
    AT_CMD_FWAVE_SET,
    AT_CMD_SWVER_SET,

    AT_CMD_CBG_SET,
    AT_CMD_CBG_READ,

    AT_CMD_MMPLMNINFO_QRY,

    AT_CMD_EONSUCS2_QRY,

    AT_CMD_PLMN_QRY,
    AT_CMD_XLEMA_QRY,

    AT_CMD_BODYSARON_SET,

    AT_CMD_FCALIIP2S_SET,
    AT_CMD_FCALIIP2S_READ,
    AT_CMD_FCALIDCOCS_SET,
    AT_CMD_FCALIDCOCS_READ,
    AT_CMD_FGAINSTATES_SET,
    AT_CMD_FGAINSTATES_READ,
    AT_CMD_FDBBATTS_SET,
    AT_CMD_FDBBATTS_READ,
    AT_CMD_FBBATTS_SET,
    AT_CMD_FBBATTS_READ,
    AT_CMD_FCALITXIQS_SET,
    AT_CMD_FCALITXIQS_READ,

    AT_CMD_F_FCALPDDCS_SET,
    AT_CMD_F_FCALPDDCS_RD,
    AT_CMD_F_FPDPOWS_SET,
    AT_CMD_F_FQPDDCRES_SET,
    AT_CMD_IMEI_VERIFY_READ,

    AT_CMD_COPN_QRY,
    AT_CMD_STCFGDPCH_SET,
    AT_CMD_STRXBER_SET,

    AT_CMD_SIMINSERT_SET,

    AT_CMD_RELEASE_RRC_SET,

    AT_CMD_REFCLKFREQ_SET,
    AT_CMD_REFCLKFREQ_READ,
    AT_CMD_RFICSSIRD_SET,

    AT_CMD_HANDLEDECT_SET,
    AT_CMD_HANDLEDECT_QRY,

    AT_CMD_HVSDH_SET,
    AT_CMD_HVSDH_READ,
    AT_CMD_HVSCONT_READ,
    AT_CMD_HVSST_SET,
    AT_CMD_HVSST_QRY,
    AT_CMD_HVPDH_SET,
    AT_CMD_SCICHG_SET,
    AT_CMD_SCICHG_QRY,

    AT_CMD_EOPLMN_SET,
    AT_CMD_EOPLMN_QRY,

    /* Added by d00212987 for BalongV9R1 NV备份数据丢失容错&恢复 项目 2013-10-24, begin */
    AT_CMD_NVMANUFACTUREEXT_SET,
    /* Added by d00212987 for BalongV9R1 NV备份数据丢失容错&恢复 项目 2013-10-24, end */
    AT_CMD_NETSCAN_SET,
    AT_CMD_ABORT_NETSCAN,

    AT_CMD_FPLLSTATUS_QRY,

    /* Added by l00198894 for 新增+ECID命令, 2013-12-09, begin */
    AT_CMD_ECID_SET,
    /* Added by l00198894 for 新增+ECID命令, 2013-12-09, end */

    AT_CMD_CLCC_QRY,
#if (FEATURE_ON == FEATURE_IMS)
    AT_CMD_CIREG_SET,
    AT_CMD_CIREG_QRY,
    AT_CMD_CIREP_SET,
    AT_CMD_CIREP_QRY,
    AT_CMD_IMPU_SET,
    AT_CMD_CCWAI_SET,
    AT_CMD_UICCAUTH_SET,
    AT_CMD_CURSM_SET,
    AT_CMD_KSNAFAUTH_SET,
#endif

    AT_CMD_ANTSWITCH_SET,
    AT_CMD_ANTSWITCH_QRY,
    AT_CMD_CACMIMS_SET,

    AT_CMD_MODEMSTATUS,
    AT_CMD_RATCOMBINEPRIO,

    AT_CMD_MIPI_CLK_QRY,

    AT_CMD_DPDTTEST_SET,
    AT_CMD_DPDT_SET,
    AT_CMD_DPDTQRY_SET,

#if (FEATURE_ON == FEATURE_DSDS)
    AT_CMD_PSPROTECTMODE_SET,
#endif
    AT_CMD_PHYINIT_SET,
    /* Added by n00269697 for V3R3C60_eCall项目, 2014-3-29, begin */
    AT_CMD_CECALL_SET,
    AT_CMD_CECALL_QRY,
    AT_CMD_ECLSTART_SET,
    AT_CMD_ECLSTOP_SET,
    AT_CMD_ECLCFG_SET,
    AT_CMD_ECLCFG_QRY,
    AT_CMD_ECLMSD_SET,
    AT_CMD_ECLMSD_QRY,
    /* Added by n00269697 for V3R3C60_eCall项目, 2014-3-29, end */
    AT_CMD_FPOWDET_QRY,

    AT_CMD_JDETEX_SET,

    AT_CMD_RATFREQLOCK_SET,

#if (FEATURE_ON == FEATURE_IMS)
    AT_CMD_CALL_MODIFY_INIT_SET,
    AT_CMD_CALL_MODIFY_ANS_SET,
    AT_CMD_ECONF_DIAL_SET,
    AT_CMD_CLCCECONF_QRY,
    AT_CMD_IMS_SWITCH_SET,
    AT_CMD_IMS_SWITCH_QRY,
    AT_CMD_VOICE_DOMAIN_SET,
    AT_CMD_VOICE_DOMAIN_QRY,
#endif
    AT_CMD_CHLD_EX_SET,
    AT_CMD_APDS_SET,

    AT_CMD_GSM_FREQLOCK_SET,

    AT_CMD_CARDTYPE_QUERY,

    AT_CMD_CRM_SET,

    AT_CMD_CQOSPRI_SET,

    /*下移到 FEATURE_UE_MODE_CDMA 宏中*/
#if (FEATURE_ON == FEATURE_LTE)
    AT_CMD_FRSTATUS_SET,
#endif

    AT_CMD_CFSH_SET,

    AT_CMD_CBURSTDTMF_SET,

    AT_CMD_CFREQLOCK_SET,
    AT_CMD_CFREQLOCK_QRY,

    AT_CMD_CCMGS_SET,
    AT_CMD_CCMGW_SET,
    AT_CMD_CCMGD_SET,

    AT_CMD_CCSASM_SET,

    AT_CMD_CDMACSQ_SET,
    AT_CMD_CDMACSQ_QRY,

    AT_CMD_HDR_CSQ_SET,
    AT_CMD_HDR_CSQ_QRY,

    AT_CMD_APDSFLOWRPTCFG_SET,
    AT_CMD_APDSFLOWRPTCFG_QRY,

    AT_CMD_DSFLOWNVWRCFG_SET,
    AT_CMD_DSFLOWNVWRCFG_QRY,

    AT_CMD_CTA_SET,
    AT_CMD_CTA_QRY,


#if (FEATURE_ON == FEATURE_HUAWEI_VP)
    AT_CMD_VOICEPREFER_SET,
    AT_CMD_VOICEPREFER_QRY,
#endif
    AT_CMD_CUSTOMDIAL_SET,

    AT_CMD_TTYMODE_SET,
    AT_CMD_TTYMODE_READ,
    AT_CMD_FEMCTRL_SET,
    AT_CMD_NVWRSECCTRL_SET,

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
    AT_CMD_CRLA_SET,
    AT_CMD_CARDSESSION_QRY,

    AT_CMD_CCIMI_SET,
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    AT_CMD_CLOCINFO_QRY,

    AT_CMD_CSID_QRY,

    AT_CMD_QCCB_SET,
    AT_CMD_CSIDLIST_SET,
    AT_CMD_CSID_SET,
    AT_CMD_EMCCBM_QRY,
    AT_CMD_CSNID_QRY,
    AT_CMD_ECCALL_SET,
    AT_CMD_ECCTRL_SET,
    AT_CMD_ECCAP_SET,
    AT_CMD_ECCAP_QRY,
    AT_CMD_ECCTEST_SET,
    AT_CMD_ECCTEST_QRY,
    AT_CMD_ECKMC_SET,
    AT_CMD_ECKMC_QRY,
    AT_CMD_ECRANDOM_QRY,
    AT_CMD_CLOCINFO_SET,
    AT_CMD_CPMP_SET,
    AT_CMD_CPMP_QRY,
#endif
    AT_CMD_AFCCLKINFO_QRY,

    AT_CMD_CCLPR_SET,


    AT_CMD_1XCHAN_SET,
    AT_CMD_1XCHAN_QRY,
    AT_CMD_CVER_QRY,
    AT_CMD_CCMGG_QRY,
    AT_CMD_GETSTA_QRY,
    AT_CMD_GETESN_QRY,
    AT_CMD_GETMEID_QRY,
    AT_CMD_CHIGHVER_QRY,
#if(FEATURE_ON == FEATURE_LTE)
#if(FEATURE_ON == FEATURE_LTE_MBMS)
    AT_CMD_MBMS_SERVICE_OPTION_SET,
    AT_CMD_MBMS_SERVICE_STATE_SET,
    AT_CMD_MBMS_PREFERENCE_SET,
    AT_CMD_MBMS_SIB16_NETWORK_TIME_QRY,
    AT_CMD_MBMS_BSSI_SIGNAL_LEVEL_QRY,
    AT_CMD_MBMS_NETWORK_INFO_QRY,
    AT_CMD_EMBMS_STATUS_QRY,
    AT_CMD_MBMS_UNSOLICITED_CFG_SET,
    AT_CMD_MBMS_INTERESTLIST_SET,
    AT_CMD_MBMS_AVL_SERVICE_LIST_QRY,
#endif
    AT_CMD_LTE_LOW_POWER_CONSUMPTION_SET,
    AT_CMD_LTE_WIFI_COEX_SET,
    AT_CMD_LTE_WIFI_COEX_QRY,
#endif

    AT_CMD_CGMTU_READ,

    AT_CMD_CAGPSCFGPOSMODE_SET,
    AT_CMD_CAGPSSTART_SET,
    AT_CMD_CAGPSSTOP_SET,
    AT_CMD_CAGPSCFGMPCADDR_SET,
    AT_CMD_CAGPSCFGPDEADDR_SET,

    AT_CMD_MEID_SET,
    AT_CMD_MEID_QRY,

    AT_CMD_IMSPDPCFG_SET,

    AT_CMD_CCONTDTMF_SET,

    AT_CMD_TRANSMODE_READ,

    AT_CMD_DORMTIMER_SET,
    AT_CMD_DORMTIMER_QRY,
    AT_CMD_EHPLMN_LIST_QRY,
    AT_CMD_DPLMNLIST_SET,
    AT_CMD_DPLMNLIST_QRY,

    AT_CMD_MCCFREQ_SET,
    AT_CMD_MCCFREQ_QRY,

    AT_CMD_CSG_LIST_SEARCH,
    AT_CMD_ABORT_CSG_LIST_SEARCH,
	
    AT_CMD_UE_CENTER_SET,
    AT_CMD_UE_CENTER_QRY,

    AT_CMD_MIPI_WR,
    AT_CMD_MIPI_RD,
    AT_CMD_SSI_WR,
    AT_CMD_SSI_RD,

    AT_CMD_MONSC_SET,
    AT_CMD_MONNC_SET,
	
    AT_CMD_PDM_CTRL,

    AT_CMD_INVALID,

    /* GU模AT命令和公共命令的当前处理ID，新增命令处理ID时要添加到此ID前 */
    AT_CMD_COMM_CURRENT_OPT

}AT_CMD_CURRENT_OPT_ENUM;

typedef enum
{
    AT_STRING_SM = 0,
    AT_STRING_ME,
    AT_STRING_ON,
    AT_STRING_EN,
    AT_STRING_FD,
    AT_STRING_BD,
    AT_STRING_REC_UNREAD_TEXT,
    AT_STRING_REC_READ_TEXT,
    AT_STRING_STO_UNSENT_TEXT,
    AT_STRING_STO_SENT_TEXT,
    AT_STRING_ALL_TEXT,
    AT_STRING_REC_UNREAD_PDU,
    AT_STRING_REC_READ_PDU,
    AT_STRING_STO_UNSENT_PDU,
    AT_STRING_STO_SENT_PDU,
    AT_STRING_ALL_PDU,
    AT_STRING_IP,
    AT_STRING_PPP,
#if (FEATURE_ON == FEATURE_IPV6)
    AT_STRING_IPV6,
    AT_STRING_IPV4V6,
#endif

    AT_STRING_0E0,
    AT_STRING_1E2,
    AT_STRING_7E3,
    AT_STRING_1E3,
    AT_STRING_1E4,
    AT_STRING_1E5,
    AT_STRING_1E6,
    AT_STRING_1E1,
    AT_STRING_5E2,
    AT_STRING_5E3,
    AT_STRING_4E3,
    AT_STRING_6E8,
    AT_STRING_CREG,
    AT_STRING_CGREG,
#if (FEATURE_ON == FEATURE_LTE)
    AT_STRING_CEREG,
#endif
    AT_STRING_SRVST,
    AT_STRING_MODE,
    AT_STRING_RSSI,
    AT_STRING_TIME,
    AT_STRING_CTZV,
    AT_STRING_CTZE,
    AT_STRING_ERRRPT,
    AT_STRING_CCALLSTATE,

    AT_STRING_CERSSI,

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-14, begin */
    AT_STRING_ACINFO,
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-14, end */

    /* Added by l00171473 for DTS2013010800120 语音带宽信息上报, 2013-1-5, begin */
    AT_STRING_CS_CHANNEL_INFO,
    /* Added by l00171473 for DTS2013010800120 语音带宽信息上报, 2013-1-5, end */

    AT_STRING_RESET,

    AT_STRING_REFCLKFREQ,

    AT_STRING_REJINFO,

    AT_STRING_PLMNSELEINFO,

    AT_STRING_NETSCAN,

#if (FEATURE_ON == FEATURE_IMS)
    AT_STRING_CIREPH,
    AT_STRING_CIREPI,
    AT_STRING_CIREGU,

    AT_STRING_CALL_MODIFY_IND,
    AT_STRING_CALL_MODIFY_BEG,
    AT_STRING_CALL_MODIFY_END,

    AT_STRING_ECONFSTATE,

#endif

    AT_STRING_CDISP,
    AT_STRING_CCONNNUM,
    AT_STRING_CCALLEDNUM,
    AT_STRING_CCALLINGNUM,
    AT_STRING_CREDIRNUM,
    AT_STRING_CSIGTONE,
    AT_STRING_CLCTR,
    AT_STRING_CCWAC,

    AT_STRING_FILECHANGE,

#if((FEATURE_ON == FEATURE_LTE) && (FEATURE_ON == FEATURE_LTE_MBMS))
    AT_STRING_MBMSEV,
#endif
    AT_STRING_SRCHEDPLMNINFO,

    AT_STRING_MCC,

    AT_STRING_BUTT
}AT_STRING_CONTENT_ENUM;


#define AT_CMD_CLVL_VAL_MAX             (5)
enum AT_CMD_CLVL_VALUE_ENUM
{
    AT_CMD_CLVL_LEV_0                 = 0,
    AT_CMD_CLVL_LEV_1                 = 50,
    AT_CMD_CLVL_LEV_2                 = 60,
    AT_CMD_CLVL_LEV_3                 = 68,
    AT_CMD_CLVL_LEV_4                 = 74,
    AT_CMD_CLVL_LEV_5                 = 80
};

typedef TAF_UINT8 AT_CMD_BLOCK_STATE_TYPE;
#define AT_CMD_READY            0
#define AT_CMD_PEND             1
#define AT_CMD_ABORT            2


typedef TAF_UINT8 AT_DATA_STATE_TYPE;
#define AT_DATA_STOP_STATE            0
#define AT_DATA_START_STATE            1

typedef TAF_UINT8 AT_CMD_MODE_TYPE;
#define AT_NORMAL_MODE          0
#define AT_SMS_MODE             1
#define AT_XML_MODE             2

typedef TAF_UINT8 AT_CHANNEL_TYPE;
#define AT_CMD_CHANNEL           0
#define AT_DATA_CHANNEL          1


typedef TAF_UINT8 AT_DATA_MODE_TYPE;
#define AT_DATA_BUTT_MODE           0
#define AT_PPP_DATA_MODE            1
#define AT_IP_DATA_MODE             2
#define AT_CSD_DATA_MODE            3
#define AT_DIAG_DATA_MODE           4
#define AT_OM_DATA_MODE             5
#define AT_AP_DATA_MODE            6

typedef TAF_UINT8 AT_V_TYPE;
#define AT_V_BREVITE_TYPE            0
#define AT_V_ENTIRE_TYPE            1


typedef TAF_UINT8 AT_CMD_ECHO_TYPE;
#define AT_E_NO_ECHO_CMD            0
#define AT_E_ECHO_CMD               1

typedef TAF_UINT8 AT_COPS_MODE_TYPE;
#define AT_COPS_AUTOMATIC_TYPE            0
#define AT_COPS_MANUAL_TYPE            1
#define AT_COPS_DEREGISTER_TYPE            2
#define AT_COPS_ONLY_SET_FORMAT_TYPE            3
#define AT_COPS_MANUAL_AUTOMATIC_TYPE            4

/*****************************************************************************
 枚举名    : AT_COPS_RAT_ENUM
 结构说明  : AT+COPS命令使用的接入技术模式
  1.日    期   : 2011年10月12日
    作    者   : l00130025
    修改内容   : 添加cops命令的定义 Ts27.007
    <AcT>: access technology selected
    0 GSM
    1 GSM Compact
    2 UTRAN
    3 GSM w/EGPRS (see NOTE 1)
    4 UTRAN w/HSDPA (see NOTE 2)
    5 UTRAN w/HSUPA (see NOTE 2)
    6 UTRAN w/HSDPA and HSUPA (see NOTE 2)
    7 E-UTRAN
*****************************************************************************/

enum AT_COPS_RAT_ENUM
{
    AT_COPS_RAT_GSM    = 0,
    AT_COPS_RAT_WCDMA  = 2,
    AT_COPS_RAT_LTE    = 7,
    AT_COPS_RAT_BUTT
};
typedef VOS_UINT8 AT_COPS_RAT_ENUM_UINT8;

typedef TAF_UINT8 AT_D_GPRS_ACTIVE_TYPE;
#define AT_IP_ACTIVE_TE_PPP_MT_PPP_TYPE            0
#define AT_PPP_ACTIVE_TE_PPP_MT_NOT_PPP_TYPE            1
#define AT_IP_ACTIVE_TE_NOT_PPP_MT_NOT_PPP_TYPE            2

typedef TAF_UINT8 AT_DATA_DOMAIN_TYPE;
#define AT_DATA_CS_DOMAIN                  0       /*CS域*/
#define AT_DATA_PS_DOMAIN                  1       /*PS域*/

typedef TAF_UINT8 AT_SMT_BUFFER_STATE;
#define AT_SMT_BUFFER_EMPTY                0
#define AT_SMT_BUFFER_USED                 1

/*需要快速处理命令在At_QuickHandleCmd中aucQuickCmd数组中的位置定义，*/
#define AT_QUICK_HANDLE_SYSINFO_CMD            0
#define AT_QUICK_HANDLE_COPS_QRY_CMD           1
#define AT_QUICK_HANDLE_COPS_SET_FORMAT_2_CMD  2
#define AT_QUICK_HANDLE_COPS_SET_FORMAT_0_CMD  3
#define AT_QUICK_HANDLE_CSQ_CMD                4
#define AT_QUICK_HANDLE_SPN_SIM                5
#define AT_QUICK_HANDLE_SPN_USIM               6
#define AT_QUICK_HANDLE_CPMS_SET_CMD           7

typedef enum
{
    AT_COM_CMD_SUB_PROC_CONTINUE = 0,        /* 继续后续命令的处理 */
    AT_COM_CMD_SUB_PROC_ABORT,               /* 终止后续命令的处理 */
    AT_COM_CMD_SUB_PROC_FINISH,              /* 结束所有命令的处理 */

    AT_COM_CMD_SUB_PROC_BUTT
}AT_COMBINE_CMD_SUBSEQUENT_PROCESS_ENUM;


typedef enum AT_NVIM_PARA_ENUM
{
    AT_NVIM_CPMS_TYPE = 0,

    AT_NVIM_BUTT_TYPE                   /* 结束 */
}AT_NVIM_PARA_ENUM;

/* Modified by L00171473 for V7R1 porting, 2011-04-23, begin，为兼容北京的TMODE命令，
   增加了MODE 4和5 */





/*****************************************************************************
 枚举名    : AT_CUSTOMIZE_ITEM_DEFAULT_VAL_ENUM
 协议表格  :
 枚举说明  : AT设置命令^CDSFLT设置定制项为默认值
*****************************************************************************/
enum AT_CUSTOMIZE_ITEM_DEFAULT_VAL_ENUM
{
    AT_CUSTOMIZE_ITEM_DEFAULT_VALUE_FROM_CFGFILE = 0,      /*定制项默认值为可配置需求文档中的值*/
    AT_CUSTOMIZE_ITEM_DEFAULT_VALUE_FROM_UE,               /*定制项中的值为单板自定义的默认值*/
    AT_CUSTOMIZE_ITEM_DEFAULT_VALUE_BUTT
};
typedef VOS_UINT8  AT_CUSTOMIZE_ITEM_DFLT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AT_SD_OPRT_ENUM_UINT32
 协议表格  :
 枚举说明  : SD卡操作类型
*****************************************************************************/
enum AT_SD_OPRT_ENUM
{
    AT_SD_OPRT_FORMAT = 0,      /* 格式化SD卡内容 */
    AT_SD_OPRT_ERASE,           /* 擦除SD卡内容 */
    AT_SD_OPRT_WRITE,           /* 写数据到SD卡的指定地址中 */
    AT_SD_OPRT_READ,            /* 读取SD卡指定地址的内容 */
    AT_SD_OPRT_QUERY_STATUS,    /* 查询SD卡操作状态 */
    AT_SD_OPRT_BUTT
};
typedef VOS_UINT32 AT_SD_OPRT_ENUM_UINT32;


/*****************************************************************************
 枚举名    : AT_SD_OPRT_RSLT_ENUM_UINT8
 协议表格  :
 枚举说明  : SD卡操作结果
*****************************************************************************/
enum AT_SD_OPRT_RSLT_ENUM
{
    AT_SD_OPRT_RSLT_FINISH = 0,     /* 上一次 SD操作已完成 */
    AT_SD_OPRT_RSLT_NOT_FINISH,     /* 上一个SD操作在进行中 */
    AT_SD_OPRT_RSLT_ERR,            /* 上一个SD操作发生错误*/
    AT_SD_OPRT_RSLT_BUTT,
};
typedef VOS_UINT8 AT_SD_OPRT_RSLT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AT_SD_STATUS_ENUM_UINT8
 协议表格  :
 枚举说明  : SD卡在位状态
*****************************************************************************/
enum AT_SD_EXIST_STATUS_ENUM
{
    AT_SD_STATUS_NOT_EXIST = 0,     /* SD不在位 */
    AT_SD_STATUS_EXIST,             /* SD在位 */
    AT_SD_STATUS_BUTT,
};
typedef VOS_UINT8 AT_SD_EXIST_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AT_SD_ERR_ENUM_UINT32
 协议表格  :
 枚举说明  : SD卡操作错误码
*****************************************************************************/
enum AT_SD_ERR_ENUM
{
    AT_SD_ERR_CRAD_NOT_EXIST = 0,      /* 表示SD卡不在位 */
    AT_SD_ERR_INIT_FAILED,             /* 表示SD卡初始化失败 */
    AT_SD_ERR_OPRT_NOT_ALLOWED,        /* 操作不允许 */
    AT_SD_ERR_ADDR_ERR,                /* 表示<address>地址非法 */
    AT_SD_ERR_OTHER_ERR,               /* 其他未知错误 */
    AT_SD_ERR_BUTT
};
typedef VOS_UINT32 AT_SD_ERR_ENUM_UINT32;


/*****************************************************************************
 枚举名    : AT_SIMLOCK_OPRT_ENUM_UINT8
 协议表格  :
 枚举说明  : SD卡操作类型
*****************************************************************************/
enum AT_SIMLOCK_OPRT_ENUM
{
    AT_SIMLOCK_OPRT_UNLOCK = 0,         /* Simlock 解锁操作 */
    AT_SIMLOCK_OPRT_SET_PLMN_INFO,      /* 设置锁卡号段 */
    AT_SIMLOCK_OPRT_QRY_STATUS,              /* 查询当前的锁卡状态 */
    AT_SIMLOCK_OPRT_BUTT
};
typedef VOS_UINT8 AT_SIMLOCK_OPRT_ENUM_UINT8;

/* Added by l60609 for AT Project，2011-10-03,  End*/

/*****************************************************************************
 结构名    : AT_NV_WCDMA_RRC_CONVERT_TBL_STRU
 结构说明  : Rrc版本结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8  ucSrcWcdmaRRC;                               /* 版本号 */
    VOS_UINT8  ucDestHSDPA;                                 /* 是否支持DPA */
    VOS_UINT8  ucDestHSUPA;                                 /* 是否支持UPA */
} AT_NV_WCDMA_RRC_CONVERT_TBL_STRU;


typedef TAF_UINT8 AT_CPMS_MEM_TYPE;
#define AT_CPMS_MEM_SM_TYPE            0
#define AT_CPMS_MEM_ME_TYPE             1

typedef TAF_UINT8 AT_CLCK_TYPE;
#define AT_CLCK_P2_TYPE            0
#define AT_CLCK_SC_TYPE            1
#define AT_CLCK_AO_TYPE            2
#define AT_CLCK_OI_TYPE            3
#define AT_CLCK_OX_TYPE            4
#define AT_CLCK_AI_TYPE            5
#define AT_CLCK_IR_TYPE            6
#define AT_CLCK_AB_TYPE            7
#define AT_CLCK_AG_TYPE            8
#define AT_CLCK_AC_TYPE            9
#define AT_CLCK_PS_TYPE            10
#define AT_CLCK_FD_TYPE            11
#define AT_CLCK_PN_TYPE            12
#define AT_CLCK_PU_TYPE            13
#define AT_CLCK_PP_TYPE            14

typedef TAF_UINT8 AT_CMLCK_TYPE;
#define AT_CMLCK_PS_TYPE            0
typedef TAF_UINT8 AT_SAT_ENVELOPE_TYPE;
#define AT_SAT_ENVELOPE_MENU        0xD3
#define AT_SAT_ENVELOPE_CALL        0xD4
#define AT_SAT_ENVELOPE_EVENT       0xD6
#define AT_SAT_ENVELOPE_TIMER       0xD7

/* NV项en_NV_Resume_Flag的有效值:0和1 */
#define AT_NV_RESUME_SUCC               (0)
#define AT_NV_RESUME_FAIL               (1)


/*DIALMODE*/
#define AT_DIALMODE_MODEM      (0)
#define AT_DIALMODE_NDIS       (1)
#define AT_DIALMODE_DUAL       (2)
#define AT_DIALMODE_ABNORMAL   (3)

/*下载类型，正常模式为0， 强制下载为1*/
#define AT_NOM_LOAD      (0)
#define AT_FORC_LOAD     (1)

#define AT_NV_RESTORE_SUCCESS                   0
#define AT_NV_RESTORE_FAIL                      1

#define AT_NV_RESTORE_RESULT_INIT  0x5A5A5A5A
#define AT_NV_RESTORE_RUNNING      0x5A5A55AA


#define AT_SIMLOCK_MAX_ERROR_TIMES  (3)  /* Simlock解锁最大失败次数 */

#define TAF_SW_VER_INFO_LEN         (31)
#define TAF_ISO_VER_INFO_LEN        (50)
#define TAF_PRODUCT_NAME_LEN        (50)
#define TAF_WEBUI_VER_LEN           (127)
#define TAF_FLASH_INFO_LEN          (100)
#define TAF_NET_MODE_LEN            (10)

/*WIFI打开模式*/
#define AT_WIFI_START_NORMAL         (0)
#define AT_WIFI_START_TEST           (1)
/*WIFI 的模式*/
#define AT_WIFI_SUPPORT_MODE_CW      (0)
#define AT_WIFI_SUPPORT_MODE_A       (1)
#define AT_WIFI_SUPPORT_MODE_B       (2)
#define AT_WIFI_SUPPORT_MODE_G       (3)
#define AT_WIFI_SUPPORT_MODE_N       (4)

/*WIFI带宽*/
#define AT_WIFI_BAND_20M             (0)
#define AT_WIFI_BAND_40M             (1)

/*WIFI发射机接收机模式*/
#define AT_WIFI_TX_MODE              (17)
#define AT_WIFI_RX_MODE              (18)

/*WIFI发射机状态*/
#define AT_WIFI_TX_ON                 (1)
#define AT_WIFI_TX_OFF                (0)

/*WIFI接收机状态*/
#define AT_WIFI_RX_ON                 (1)
#define AT_WIFI_RX_OFF                (0)

/*WIFI功率的上下限*/
#define AT_WIFI_POWER_MIN             (-15)
#define AT_WIFI_POWER_MAX             (30)

#define AT_FEATURE_EXIST              (1)
#define AT_FEATURE_MAX                (15)

/* AP-Modem 中，目前规格支持最大3个HSIC AT通道 */
#define AT_HSIC_AT_CHANNEL_INDEX_ONE    (0)
#define AT_HSIC_AT_CHANNEL_INDEX_TWO    (1)
#define AT_HSIC_AT_CHANNEL_INDEX_THREE  (2)
#define AT_HSIC_AT_CHANNEL_INDEX_FOUR   (3)

#define AT_HSIC_AT_CHANNEL_MAX          (4)

/* 供RIL使用的AT通道个数 */
#define AT_HSIC_AT_FOR_RIL_MAX          (2)

/* Modified by L60609 for add app vcom，2013-06-17,  Begin */
#if (FEATURE_ON == FEATURE_VCOM_EXT)
/* APPVCOM 最后 5 个端口为非AT 口*/
#define AT_VCOM_AT_CHANNEL_MAX          (APP_VCOM_DEV_INDEX_BUTT - 5)
#else
#define AT_VCOM_AT_CHANNEL_MAX          (APP_VCOM_DEV_INDEX_BUTT)
#endif
/* Modified by L60609 for add app vcom，2013-06-17,  End */

#define AT_SIMLOCKUNLOCK_PWD_PARA_LEN   (16)

enum AT_CUUSI_MSG_TYPE_ENUM
{
    AT_CUUSI_MSG_ANY,
    AT_CUUSI_MSG_ALERT,
    AT_CUUSI_MSG_PROGRESS,
    AT_CUUSI_MSG_CONNECT,
    AT_CUUSI_MSG_RELEASE,
    AT_CUUSI_MSG_BUTT
};
typedef VOS_UINT32 AT_CUUSI_MSG_TYPE_ENUM_U32;

enum AT_CUUSU_MSG_TYPE_ENUM
{
    AT_CUUSU_MSG_ANY,
    AT_CUUSU_MSG_SETUP,
    AT_CUUSU_MSG_DISCONNECT,
    AT_CUUSU_MSG_RELEASE_COMPLETE,
    AT_CUUSU_MSG_BUTT
};
typedef VOS_UINT32 AT_CUUSU_MSG_TYPE_ENUM_U32;

typedef struct
{
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enCallMsgType;
    AT_CUUSU_MSG_TYPE_ENUM_U32          enCuusuMsgType;
}AT_CALL_CUUSU_MSG_STRU;

typedef struct
{
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enCallMsgType;
    AT_CUUSI_MSG_TYPE_ENUM_U32          enCuusiMsgType;
}AT_CALL_CUUSI_MSG_STRU;

typedef TAF_UINT32 (*pAtSetParaFunc)(TAF_UINT8 ucIndex);
typedef TAF_UINT32 (*pAtQueryParaFunc)(TAF_UINT8 ucIndex);

typedef TAF_UINT32 (*pAtAppCBF)(TAF_UINT8 ucIndex,TAF_UINT8 ucType,TAF_UINT8* pData,TAF_UINT16 usLen);


/* DIAG口是否打开的枚举结构  */
enum  AT_DIAG_OPEN_FLAG_ENUM
{
    AT_DIAG_OPEN_FLAG_OPEN,             /* 0 为打开 */
    AT_DIAG_OPEN_FLAG_CLOSE,            /* 1 为关闭 */
    AT_DIAG_OPEN_FLAG_BUTT
};
typedef  VOS_UINT32  AT_DIAG_OPEN_FLAG_ENUM_U32;

#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
/*  SHELL口是否打开的枚举结构  */
enum  AT_SHELL_OPEN_FLAG_ENUM
{
    AT_SHELL_OPEN_FLAG_WIFI,
    AT_SHELL_OPEN_FLAG_CLOSE,
    AT_SHELL_OPEN_FLAG_OPEN,
    AT_SHELL_OPEN_FLAG_BUTT
};
typedef  VOS_UINT32  AT_SHELL_OPEN_FLAG_ENUM_U32;
#endif

/* 保存在NV中的权限密码的结构 */
#define AT_DISLOG_PWD_LEN               (16)                /*  DISLOG操作权限的密码长度  */

#define AT_SETZ_LEN                     (16)


/* 0 使能SD卡; 1 禁止SD卡 */
enum AT_SD_ENABLE_FLAG_ENUM
{
    AT_SD_ENABLE_FLAG_ENABLE,
    AT_SD_ENABLE_FLAG_DISABLE,
    AT_SD_ENABLE_FLAG_BUTT
};

enum  AT_CLCK_MODE_ENUM
{
    AT_CLCK_MODE_UNLOCK,                /* 0 去激活 */
    AT_CLCK_MODE_LOCK,                  /* 1 激活 */
    AT_CLCK_MODE_QUERY_STATUS,          /* 2 查询 */
    AT_CLCK_MODE_BUTT
};
typedef  VOS_UINT32  AT_CLCK_MODE_ENUM_U32;




/*****************************************************************************
  5 消息头定义
*****************************************************************************/
/*模块名＋意义＋HEADER */

/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/* A CONVERSION_TABLE is an array mapping 7 or 8 bit values to 16 bit values. */
typedef struct
{
    VOS_UINT8                           ucOctet;
    VOS_UINT8                           ucReserve;
    VOS_UINT16                          usUnicode;
}AT_PB_CONVERSION_TABLE_STRU;

/* AT归一化控制结构，用于记录当前使用哪个DSP及当前的TMODE值*/
typedef struct
{
    VOS_BOOL                            bDspLoadFlag;
    TAF_UINT8                           ucIndex;          /*AT设置命令的Index值*/
    TAF_PH_TMODE_ENUM_UINT8             ucCurrentTMode;
    AT_DEVICE_CMD_RAT_MODE_ENUM_UINT8   ucDeviceRatMode;
    AT_DEVICE_CMD_BAND_ENUM_UINT8       ucDeviceAtBand;
    AT_DSP_BAND_ARFCN_STRU              stDspBandArfcn;
    /*AT^FDAC设置的FDAC值和AT^FWAVE设置的power值表示的含义相同，取后设置的值*/
    VOS_BOOL                            bFdacFlag;       /* FDAC是否有效*/
    VOS_UINT16                          usFDAC;          /* 对应W下AGC,G下TxVpa*/
    VOS_UINT16                          usRxDiv;         /* 分集配置*/
    VOS_UINT16                          usRxPri;         /* 主集配置*/
    VOS_UINT16                          usOrigBand;      /* 记录格式转换后的主集或分集配置*/
    AT_DSP_RF_ON_OFF_ENUM_UINT8         ucRxOnOff;       /* Rx on off值*/
    VOS_UINT8                           ucPaLevel;       /* 发射机的PA等级*/
    VOS_UINT8                           ucLnaLevel;      /* 接收机LNA等级*/
    VOS_UINT8                           ucPriOrDiv;      /* 当前是主集配置还是分集配置*/
    AT_DSP_RF_ON_OFF_ENUM_UINT8         ucTxOnOff;       /* Tx On off值*/
    VOS_UINT8                           ucRxonOrTxon;    /* 记录最近一次执行的是打开接收机(RXON=1)操作还是打开发射机(TXON=1)操作*/




    VOS_UINT8                           aucReserved[2];
    VOS_BOOL                            bPowerFlag;      /* Power是否有效*/
    VOS_UINT16                          usPower;         /* AT^FWAVE设置的功率值*/
    VOS_UINT16                          usTxMode;        /* AT^FWAVE设置的<type>值转换为发送给物理层的值(该变量只在G物理层使用):
                                                                   <type>为0，代表连续波形，usTxMode置为1；<type>为其他值，usTxMode置为0 */
}AT_DEVICE_CMD_CTRL_STRU;


typedef struct
{
    MN_MSG_ASCII_ADDR_STRU              stAsciiAddr;                            /*<oa/da>[,<tooa/toda>*/
    TAF_UINT8                           aucBuffer[AT_SMS_SEG_MAX_LENGTH];       /*开始是SMSC的地址，之后是TPDU*/
    TAF_BOOL                            bWaitForNvStorageStatus;
    TAF_BOOL                            bWaitForUsimStorageStatus;
    TAF_BOOL                            bWaitForCpmsSetRsp;
    TAF_UINT8                           ucCnmaType;                             /*记录+CNMA[=<n>中的<n>*/
    TAF_UINT8                           ucPduLen;                               /*TPDU的字节数，不包括SMSC地址的字节数*/
    MN_MSG_COMMAND_TYPE_ENUM_U8         CommandType;
    TAF_UINT8                           ucMessageNumber;                        /*[1,3]或者绝对编号*/
    TAF_UINT8                           ucMessageNumberType;                    /*编号类型：绝对或者相对*/
    MN_MSG_STATUS_TYPE_ENUM_U8          SmState;
    MN_MSG_MEM_STORE_ENUM_U8            enSmMemStore;
    TAF_UINT8                           ucMsgDeleteTypes;
    TAF_UINT8                           ucMsgSentSmNum;
    TAF_UINT8                           ucFo;
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid;                                  /*TP-PID*/
    VOS_UINT8                           aucReserved[1];
}AT_SMS_STRU;

typedef struct
{
    MN_CALL_CUG_CFG_STRU        CugMode;
    MN_CALL_CLIR_CFG_ENUM_U8    ClirInfo;
    MN_CALL_TYPE_ENUM_U8        CallType;
    MN_CALL_ID_T                CallId;
    VOS_UINT8                   aucReserved[5];
}AT_CALL_INFO_STRU;


typedef struct
{
    MN_CLIENT_ID_T          usClientId;                                         /* 指示当前用户的 */
    MN_OPERATION_ID_T       opId;                                               /* Operation ID, 标识本次操作 */
    TAF_UINT8               ucUsed;                                             /* 指示当前索引是否已被使用 */

    AT_USER_TYPE            UserType;                                           /* 指示当前用户类型 */
    TAF_UINT8               ucPortType;                                         /* 指示当前端口类型 */
    AT_PORT_NO              ucPortNo;                                           /* 指示当前USB COM串口号 */
    TAF_UINT8               ucDlci;                                             /* 指示当前链路号 */
    AT_MODE_TYPE            Mode;                                               /* 指示当前命令模式，只针对MUX和APP */
    AT_DATA_MODE_TYPE       DataMode;                                           /* 指示当前数据模式，只针对MUX和APP */
    TAF_UINT8               ModemStatus;                                        /* Modem 状态 */
    AT_IND_MODE_TYPE        IndMode;                                            /* 指示当前命令模式，只针对MUX和APP */
    AT_DATA_STATE_TYPE      DataState;                                          /* 指示当前数据模式，只针对MUX和APP */

    TAF_UINT8               ucCsRabId;
    TAF_UINT8               ucPsRabId;
    TAF_UINT8               ucCid;

    AT_CMD_CURRENT_OPT_ENUM CmdCurrentOpt;                                      /* 指示当前用户的命令操作类型 */

    TAF_UINT32              ulCause;                                            /* 指示当前Cause值 */

    pAtAppCBF               pAppCallBack;

    AT_CALL_INFO_STRU       AtCallInfo;

    TAF_UINT16              usPppId;

    TAF_UINT16              usSmsTxtLen;                                        /* 指示当前短信文本长度 */
    TAF_UINT16              usAsyRtnNum;                                        /* 指示当前挂起命令个数 */

    VOS_UINT8               aucReserved[2];

    HTIMER                  hTimer;                                             /* 对应的定时器 */
    TAF_UINT32              ulTemp;

    AT_CMD_INDEX_ENUM       CmdIndex;                                           /* 指示当前用户的命令索引 */

    AT_SMS_STRU             AtSmsData;
} AT_CLIENT_MANAGE_STRU;


typedef struct
{
    TAF_UINT8   aucBuffer[AT_CMD_MAX_LEN + 20];    /* 用来放置解析出的参数字符串 */
    TAF_UINT16  usBufLen;                      /* 用来标识参数字符串长度 */
}AT_SEND_DATA_BUFFER_STRU;

/*lint -e958 -e959 修改人:l60609;原因:64bit*/
typedef struct
{
    AT_RRETURN_CODE_ENUM_UINT32 ucIndex;
    TAF_UINT8  *Result[2];
}AT_RETURN_TAB_TYPE_STRU;
/*lint +e958 +e959 修改人:l60609;原因:64bit*/

typedef struct
{
    AT_CPMS_MEM_TYPE ReadMem1;
    AT_CPMS_MEM_TYPE DeleteMem2;
    AT_CPMS_MEM_TYPE WriteMem3;
    AT_CPMS_MEM_TYPE SendMem4;
}AT_CPMS_TYPE_STRU;

/*lint -e958 -e959 修改人:l60609;原因:64bit*/
typedef struct
{
    AT_STRING_CONTENT_ENUM   StrType;
    TAF_UINT8 *pucText;
}AT_STRING_TYPE_STRU;
/*lint +e958 +e959 修改人:l60609;原因:64bit*/

typedef TAF_INT (*USB_SERIAL_SEND_DATA)
(
    TAF_UINT8 *pData,               /*数据指针*/
    TAF_UINT16 usLen                /*数据长度*/
);

/*->f62575*/
#define AT_MSG_BUFFER_USED                                  1
#define AT_MSG_BUFFER_FREE                                  0

typedef struct
{
    TAF_UINT8                           ucIndex;
    TAF_UINT8                           aucReserve1[5];
    TAF_UINT16                          usDataLen;
    TAF_UINT8                           *pData;
}AT_PS_MODEM_DATA_IND_STRU;


/*Taf_DefCsAutoAnswerInfo函数的参数类型*/
typedef TAF_UINT32 TAF_CS_AUTO_ANSWER_INFO; /* 设置CS域自动应答时间，单位为秒，
                                               如果是0，表示不支持自动应答 */


typedef struct
{
    TAF_UINT16  usUsed;                                       /*已使用记录数 */
    TAF_UINT16  usTotal;                                      /* 最大记录数 */
    TAF_UINT16  usNameMaxLen;                                 /* 姓名最大长度 */
    TAF_UINT16  usNumMaxLen;                                  /* 号码最大长度 */
    TAF_UINT16  usAnrNumLen;                                  /*  ANR号码最大长度 */
    TAF_UINT16  usEmailLen;                                   /*  Email最大长度 */
}AT_PB_INFO_STRU;


typedef MN_CALL_NUM_TYPE_ENUM_U8 AT_CSTA_NUM_TYPE_ENUM_U8;

/* USB设备形态NV项的结构体 */
typedef struct
{
    TAF_UINT32  ulStatus;     /* 1: NV有效标志位，0：无效 */
    TAF_UINT32  ulValue;      /* 设备形态index */
    TAF_UINT32  ulReserve1;   /* 保留 */
    TAF_UINT32  ulReserve2;   /* 保留 */
}AT_USB_ENUM_STATUS_STRU;

/*****************************************************************************
 结构名    : AT_WIFI_SSID_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : en_NV_Item_WIFI_KEY NV项对应的结构，
             用于保存wifi 安全信息
*****************************************************************************/
typedef struct
{

    VOS_UINT8    aucWifiSsid[AT_WIFI_SSID_LEN_MAX];
    VOS_UINT8    aucReserved[83];
}AT_WIFI_SSID_STRU;

/*****************************************************************************
 结构名    : AT_WIFI_SEC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : en_NV_Item_WIFI_KEY NV项对应的结构，
             用于保存wifi 安全信息
             nv_wifisec_type结构的副本必须与NV项50012的数据结构nv_wifisec_type保持一致
             aucwlAuthMode              鉴权模式
             aucBasicEncryptionModes    基本加密模式
             aucWPAEncryptionModes      WPA加密模式
             aucWifiWepKey1...aucWifiWepKey4               WIFI KEY
             ulKeyIndex                 使用的WIFI KEY index,例如，1代表使用wlKeys1
             aucWpaPsk                  WPA的密码
             ucWpsEnable                wps是否使能开关
             ucWpsCfg                   是否允许register来改变enrollee的参数,  0:不允许(默认);  1:允许

  1.日    期   : 2012年4月6日
    作    者   : l60609
    修改内容   : DTS201203307015:结构体未四字节对齐
*****************************************************************************/
typedef struct
{
    VOS_UINT8    aucWifiAuthmode[16];
    VOS_UINT8    aucWifiBasicencryptionmodes[5];
    VOS_UINT8    aucWifiWpaencryptionmodes[5];
    VOS_UINT8    aucWifiWepKey1[27];
    VOS_UINT8    aucWifiWepKey2[27];
    VOS_UINT8    aucWifiWepKey3[27];
    VOS_UINT8    aucWifiWepKey4[27];
    VOS_UINT8    aucWifiWepKeyIndex[4];
    VOS_UINT8    aucWifiWpapsk[65];
    VOS_UINT8    ucWifiWpsenbl;
    VOS_UINT8    ucWifiWpscfg;
    VOS_UINT8    ucreserve;
}AT_WIFI_SEC_STRU;

/*****************************************************************************
 结构名    : AT_WIFI_INFO_STRU
 结构说明  : 用于从NV项读取WIFI相关信息
 修改记录  :
 1.日    期   : 2012年02月02日
   作    者   : l00198894
   修改内容   : B050 Project, 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32      bitOpbSupport       : 1;
    VOS_UINT32      bitOpgSupport       : 1;
    VOS_UINT32      bitOpnSupport       : 1;
    VOS_UINT32      bitOpSpare          : 29;

    VOS_UINT8       usbHighChannel;                                             /* 802.11b制式最大信道号 */
    VOS_UINT8       usbLowChannel;                                              /* 802.11b制式最小信道号 */
    VOS_UINT8       aucRsv1[2];
    VOS_UINT16      ausbPower[2];                                               /* 802.11b制式的期望功率 */

    VOS_UINT8       usgHighChannel;                                             /* 802.11g制式最大信道号 */
    VOS_UINT8       usgLowChannel;                                              /* 802.11g制式最小信道号 */
    VOS_UINT8       aucRsv2[2];
    VOS_UINT16      ausgPower[2];                                               /* 802.11g制式的期望功率 */

    VOS_UINT8       usnHighChannel;                                             /* 802.11n制式最大信道号 */
    VOS_UINT8       usnLowChannel;                                              /* 802.11n制式最小信道号 */
    VOS_UINT8       aucRsv3[2];
    VOS_UINT16      ausnPower[2];                                               /* 802.11n制式的期望功率 */
}AT_WIFI_INFO_STRU;


/* 设备形态的个数:A1,A2,A,B,D,E,1,2,3,4,5,6,16 */
/* Modify by f62575 for V7代码同步, 2012-04-07, Begin   */
#define AT_SETPORT_DEV_LEN              (21)
/* Modify by f62575 for V7代码同步, 2012-04-07, End   */

/* 设备形态对应表长度 */
#define AT_SETPORT_DEV_MAP_LEN          (AT_SETPORT_DEV_LEN + 1)

/* 设备形态最多17个组合 */
#define AT_SETPORT_PARA_MAX_LEN 17

/* 设备形态组合参数最大字符数，最多17个设备形态，最大2个字符，16个逗号 */
#define AT_SETPORT_PARA_MAX_CHAR_LEN ((17*2) + 16)

/* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */

typedef enum tagAT_DEV__PID_UNIFY_IF_PROT
{
    AT_DEV_VOID             = 0x00,
    AT_DEV_MODEM            = 0x01,
    AT_DEV_PCUI             = 0x02,
    AT_DEV_DIAG             = 0x03,
    AT_DEV_PCSC             = 0x04,
    AT_DEV_GPS              = 0x05,
    AT_DEV_GPS_CONTROL      = 0x06,
    AT_DEV_NDIS             = 0x07,
    AT_DEV_NDISDATA         = 0x08,
    AT_DEV_NDISCTRL         = 0x09,
    AT_DEV_BLUE_TOOTH       = 0x0A,
    AT_DEV_FINGER_PRINT     = 0x0B,
    AT_DEV_ACMCTRL          = 0x0C,
    AT_DEV_MMS              = 0x0D,
    AT_DEV_PC_VOICE         = 0x0E,
    AT_DEV_DVB              = 0x0F,
    AT_DEV_4G_MODEM         = 0x10,
    AT_DEV_4G_NDIS          = 0x11,
    AT_DEV_4G_PCUI          = 0x12,
    AT_DEV_4G_DIAG          = 0x13,
    AT_DEV_4G_GPS           = 0x14,
    AT_DEV_4G_PCVOICE       = 0x15,
    AT_DEV_NCM              = 0x16,
    AT_DEV_LTE_DIAG         = 0x17,
    AT_DEV_CDROM            = 0xA1,
    AT_DEV_SD               = 0xA2,
    AT_DEV_RNDIS            = 0xA3,
    AT_DEV_NONE             = 0xFF
} AT_DEV_PID_UNIFY_IF_PROT;
/* Add by w00199382 for V7代码同步, 2012-04-07, End   */
/* PORT */
typedef struct
{
    VOS_UINT8   aucAtSetPara[3];
    VOS_UINT8   ucDrvPara;
    VOS_UINT8   aucAtDispPara[15];
}AT_SET_PORT_PARA_MAP_STRU;

typedef struct
{
    VOS_UINT32  ulPidEnabled;
}AT_PID_ENABLE_TYPE_STRU;

/* AT组合命令解析相关数据结构 */

/* 组合命令相关规格的定义(仅是目前根据需求所定的规格) */
#define AT_COMBINE_MAX_SEMICOLON    40   /* 一个AT码流中最多支持40个分号(refer to Q) */
#define AT_COMBINE_MAX_COMBINE_CMD  40   /* 一个AT码流最多可分解为40个组合命令(refer to Q) */
#define AT_COMBINE_MAX_LEN          545  /* 一条组合命令最多包含545个字节(refer to Q) */
#define AT_COMBINE_MAX_SUB_CMD      40   /* 一条组合命令最多可分解为40个独立AT命令(refer to Q) */
#define AT_INDEPENDENT_CMD_MAX_LEN  545  /* 一条组合命令中所分解的独立AT命令最长为545个字节(refer to Q) */

/* 解析AT组合命令中的';'号所使用的结构体 */
typedef struct
{
    VOS_UINT32  ulCount;                                    /* AT组合命令中';'号出现的次数 */
    VOS_UINT16  ausSCPosition[AT_COMBINE_MAX_SEMICOLON];    /* AT组合命令中';'号出现的位置(数组索引) */
}AT_COMBINE_CMD_SEMICOLON_PARSE_STRU;



typedef struct
{
    VOS_UINT32  ulCount;                                    /* AT码流被分号所分隔的组合命令个数 */
    struct
    {
        VOS_UINT32  ulLen;
        VOS_UINT8   aucCombineCmd[AT_COMBINE_MAX_LEN];
        VOS_UINT8   aucReserved[3];
    }stCombineCmd[AT_COMBINE_MAX_COMBINE_CMD];
}AT_COMBINE_CMD_SPLIT_STRU;   /* 根据分号进行AT码流的分隔，将AT码流分隔为若干个组合AT命令 */


typedef struct
{
    VOS_UINT32      ulTotalCnt;                             /* 独立AT命令的个数 */
    VOS_UINT32      ulProcCnt;                              /* 已经处理完毕的独立AT命令个数 */
    struct
    {
        VOS_UINT32  ulLen;
        VOS_UINT8   aucATCmd[AT_INDEPENDENT_CMD_MAX_LEN];
        VOS_UINT8   aucReserved[3];                         /*四字节对齐*/
    }stATCmd[AT_COMBINE_MAX_SUB_CMD];
}AT_COMBINE_CMD_PARSE_RSLT_STRU;    /* 组合AT命令解析结果 */


typedef struct
{
    TAF_UINT32          ulBuffLen;                     /* 缓存码流的长度 */
    TAF_UINT8           aucDataBuff[AT_COM_BUFF_LEN];  /* 缓存码流 */
}AT_DATA_STREAM_BUFFER_STRU;           /* AT码流缓存结构体 */

/*lint -e958 -e959 修改人:l60609;原因:64bit*/
typedef struct
{
    MN_PH_SYS_MODE_EX_ENUM_U8           enSysMode;
    VOS_CHAR                           *pcStrSysModeName ;
}AT_PH_SYS_MODE_TBL_STRU;

typedef struct
{
    MN_PH_SUB_SYS_MODE_EX_ENUM_U8       enSubSysMode;
    VOS_CHAR                           *pcStrSubSysModeName ;
}AT_PH_SUB_SYS_MODE_TBL_STRU;
/*lint +e958 +e959 修改人:l60609;原因:64bit*/



/*****************************************************************************
 枚举名    : AT_RRC_VERSION_ENUM
 枚举说明  : 标识RRC版本类型
1.日    期   : 2012年04月21日
  作    者   : l60609
   修改内容   : 创建
*****************************************************************************/
enum AT_RRC_VERSION_ENUM
{
    AT_RRC_VERSION_WCDMA                = 0,
    AT_RRC_VERSION_DPA                  = 1,
    AT_RRC_VERSION_DPA_AND_UPA          = 2,
    AT_RRC_VERSION_HSPA_PLUNS           = 6,
    AT_RRC_VERSION_BUTT
};
typedef VOS_UINT8 AT_RRC_VERSION_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AT_PTL_VER_TYPE_ENUM_UINT8
 枚举说明  : 标识协议版本类型
1.日    期   : 2012年04月21日
  作    者   : l60609
   修改内容   : 创建
*****************************************************************************/
enum AT_PTL_VER_TYPE_ENUM
{
    AT_PTL_VER_ENUM_R3,
    AT_PTL_VER_ENUM_R4,
    AT_PTL_VER_ENUM_R5,
    AT_PTL_VER_ENUM_R6,
    AT_PTL_VER_ENUM_R7,
    AT_PTL_VER_ENUM_R8,
    AT_PTL_VER_ENUM_R9,
    AT_PTL_VER_ENUM_BUTT
};
typedef VOS_UINT8 AT_PTL_VER_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AT_DPACAT_CATEGORY_TYPE_ENUM
 结构说明  : DPACAT命令参数HSDPA速率等级
                           0: 支持速率等级3.6M
                           1: 支持速率等级7.2M
                           2: 支持速率等级1.8M
                           3: 支持速率等级14.4M
                           4: 支持速率等级21M
*****************************************************************************/
enum AT_DPACAT_CATEGORY_TYPE_ENUM
{
    AT_DPACAT_CATEGORY_TYPE_3600K                 = 0,
    AT_DPACAT_CATEGORY_TYPE_7200K                 = 1,
    AT_DPACAT_CATEGORY_TYPE_1800K                 = 2,
    AT_DPACAT_CATEGORY_TYPE_14400K               = 3,
    AT_DPACAT_CATEGORY_TYPE_21000K               = 4,
    AT_DPACAT_CATEGORY_TYPE_BUTT
};
typedef VOS_UINT32 AT_DPACAT_CATEGORY_TYPE_ENUM_U32;

/*****************************************************************************
结构名    : AT_DPACAT_PARA_STRU
结构说明  : AT定义DPACAT命令关注的参数结构
1.日    期   : 2012年05月21日
  作    者   : f62575
  修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enHSDSCHSupport;                        /* 是否支持enHSDSCHSupport的标志                */
    VOS_UINT8                           ucHSDSCHPhyCategory;                    /* R6版本支持HS-DSCH物理层的类型标志                  */
    PS_BOOL_ENUM_UINT8                  enMacEhsSupport;                        /* 是否支持增强的HSDPA的标志                */
    VOS_UINT8                           ucHSDSCHPhyCategoryExt;                 /* R6版本及以上版本支持HS-DSCH物理层的类型标志    */
    PS_BOOL_ENUM_UINT8                  enMultiCellSupport;                     /* 是否支持 Multi cell support,如果支持MultiCell,Ex2存在 */

}AT_DPACAT_PARA_STRU;

/*****************************************************************************
结构名    : AT_NVIM_UE_CAPA_STRU
结构说明  : AT定义NV9008的结构
1.日    期   : 2012年04月21日
  作    者   : l60609
  修改内容   : 新增结构
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          ulHspaStatus;                           /* 0表示未激活,那么DPA和UPA都支持;1表示激活 */

    VOS_UINT8                           aucRsv1[4];                             /* RF 能力信息                                  */

    PS_BOOL_ENUM_UINT8                  enSupportPwrBoosting;                   /* 16QAM特性相关，是否支持E-DPCCH Power Boosting*/
    PS_BOOL_ENUM_UINT8                  enSf4Support;                           /* 是否支持ul dpcch 使用 slotFormat4 */

    VOS_UINT8                           aucRsv2[1];                             /* ENUMERATED  OPTIONAL                         */
    AT_PTL_VER_TYPE_ENUM_UINT8          enAsRelIndicator;                       /* Access Stratum Release Indicator             */

    PS_BOOL_ENUM_UINT8                  enHSDSCHSupport;                        /* 是否支持enHSDSCHSupport的标志                */
    VOS_UINT8                           ucHSDSCHPhyCategory;                    /* 支持HS-DSCH物理层的类型标志                  */

    PS_BOOL_ENUM_UINT8                  enMacEhsSupport;
    VOS_UINT8                           ucHSDSCHPhyCategoryExt;
    PS_BOOL_ENUM_UINT8                  enMultiCellSupport;                     /* 是否支持 Multi cell support,如果支持MultiCell,Ex2存在 */
    VOS_UINT8                           ucHSDSCHPhyCategoryExt2;                /* HS-DSCH physical layer category extension 2 */

    PS_BOOL_ENUM_UINT8                  enCellSpecTxDiversityForDc;             /*  This IE is optionally present if Dual-Cell HSDPA is supported. Otherwise it is not needed.
                                                                                    The IE is not needed in the INTER RAT HANDOVER INFO message. Otherwise, it is optional*/
    VOS_UINT8                           aucRsv3[1];                             /* 留作以后扩展HS-DSCH physical layer category extension 3 */

    PS_BOOL_ENUM_UINT8                  enEDCHSupport;                          /* 是否支持EDCH的标志                           */
    VOS_UINT8                           ucEDCHPhyCategory;                      /* 支持UPA的等级                                */
    PS_BOOL_ENUM_UINT8                  enSuppUl16QAM;                          /* 是否支持上行16QAM，当支持时ucEDCHPhyCategoryExt才有效 */
    VOS_UINT8                           ucEDCHPhyCategoryExt;                   /* 上行单载波支持16QAM时，填写7 */
    PS_BOOL_ENUM_UINT8                  enSuppEDpdchInterpolationFormula;       /* 16QAM特性相关，是否支持E-DPDCH power interpolation formula */
    PS_BOOL_ENUM_UINT8                  enSuppHsdpaInFach;                      /* 支持CELL_FACH下HS-DSCH的接收 */
    PS_BOOL_ENUM_UINT8                  enSuppHsdpaInPch;                       /* 支持CELL_PCH或URA_PCH下HS-DSCH的接收 */

    PS_BOOL_ENUM_UINT8                  enMacIsSupport;                         /* 是否支持MAC_I/MAC_Is */

    PS_BOOL_ENUM_UINT8                  enFDPCHSupport;                         /* 是否支持FDPCH的标志                          */

    PS_BOOL_ENUM_UINT8                  enHsscchLessSupport;                    /* 是否支持 hsscchlessHsdschOperation           */
    PS_BOOL_ENUM_UINT8                  enUlDpcchDtxSupport;                    /* 是否支持 discontinuousDpcchTransmission      */

    PS_BOOL_ENUM_UINT8                  enAdjFreqMeasWithoutCmprMode;           /* 是否支持 Adjacent Frequency measurements without compressed mode */

    PS_BOOL_ENUM_UINT8                  enMimoSingleStreamStrict;               /* 是否限制只能使用单流MIMO */
    PS_BOOL_ENUM_UINT8                  enMimoWithDlTxDiversity;                /* R9特性，在MIMO激活时，下行控制信道是否允许使用分集 */

    /* V7r1 双模增加NV项 LTE能力 */
    PS_BOOL_ENUM_UINT8                  enSptAbsPriBasedReselInUtra;            /* 支持UTRA中的优先级重选，默认为0，1为支持，0为不支持 */

    VOS_UINT8                           ucHSDSCHPhyCategoryExt3;                /* HS-DSCH physical layer category extension 3 */
    PS_BOOL_ENUM_UINT8                  enDcMimoSupport;                        /* 是否支持DC+MIMO */
    PS_BOOL_ENUM_UINT8                  enSuppCommEDCH;                         /* E-RACH新增特性 */

    PS_BOOL_ENUM_UINT8                  enDcUpaSupport;                         /* 是否支持DC UPA的标志 */
    VOS_UINT8                           ucEDCHPhyCategoryExt2;                  /* EDCH  category extension 2*/
    PS_BOOL_ENUM_UINT8                  enEdpdchGainFactorFlg;                  /* E-DPDCH功率回退因子使能标志位 */
    VOS_UINT8                           aucRsv4[7];
}AT_NVIM_UE_CAPA_STRU;

/*****************************************************************************
 枚举名    : AT_NVWR_SEC_TYPE_ENUM
 结构说明  : ^NVWR命令安全控制类型枚举
  1.日    期  : 2015年04月04日
    作    者  : l00198894
    修改内容  : 新增结构
*****************************************************************************/
enum AT_NVWR_SEC_TYPE_ENUM
{
    AT_NVWR_SEC_TYPE_OFF = 0,                                                   /* 安全控制关闭 */
    AT_NVWR_SEC_TYPE_ON,                                                        /* 安全控制开启 */
    AT_NVWR_SEC_TYPE_BLACKLIST,                                                 /* 安全控制黑名单模式 */
    AT_NVWR_SEC_TYPE_BUTT
};
typedef VOS_UINT8 AT_NVWR_SEC_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : AT_SYSCFGEX_RAT_TYPE_ENUM
 结构说明  : AT^syscfgex 中acqorder接入技术类型
1.日    期  : 2011年07月15日
  作    者  : z00161729
  修改内容  : 新增结构
*****************************************************************************/
enum AT_SYSCFGEX_RAT_TYPE_ENUM
{
    AT_SYSCFGEX_RAT_AUTO = 0,              /* 接入技术为自动模式 */
    AT_SYSCFGEX_RAT_GSM,                   /* GSM接入技术 */
    AT_SYSCFGEX_RAT_WCDMA,                 /* WCDMA接入技术 */
    AT_SYSCFGEX_RAT_LTE,                   /* LTE接入技术 */
    AT_SYSCFGEX_RAT_1X,                    /* 1X接入技术 */
    AT_SYSCFGEX_RAT_DO   = 7,              /* DO接入技术 */
    AT_SYSCFGEX_RAT_NO_CHANGE = 99,        /* 接入技术无变化 */
    AT_SYSCFGEX_RAT_BUTT
};
typedef VOS_UINT8 AT_SYSCFGEX_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : AT_SYSCFGEX_RAT_ORDER_STRU
 结构说明  : AT^syscfgex中设置的acqorder接入技术个数和优先级
 1.日    期  : 2011年07月15日
   作    者  : z00161729
   修改内容  : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRatOrderNum;                          /* syscfgex中设置的acqoder中的指示接入技术的个数 */
    AT_SYSCFGEX_RAT_TYPE_ENUM_UINT8     aenRatOrder[TAF_PH_MAX_GUL_RAT_NUM];    /* at^syscfgex中设置的acqoder接入优先级 */
}AT_SYSCFGEX_RAT_ORDER_STRU;

/*****************************************************************************
 枚举名    : AT_SYSCFG_RAT_TYPE_ENUM
 结构说明  : AT^syscfg 中mode接入技术的类型
1.日    期  : 2011年07月15日
  作    者  : z00161729
  修改内容  : 新增结构
*****************************************************************************/
enum AT_SYSCFG_RAT_TYPE_ENUM
{
    AT_SYSCFG_RAT_AUTO          = 2,                                                /* 接入技术为自动模式 */
    AT_SYSCFG_RAT_1X            = 3,                                                /* 1X 模式 */
    AT_SYSCFG_RAT_HRPD          = 4,                                                /* HRDP 模式 */
    AT_SYSCFG_RAT_1X_AND_HRPD   = 8,                                                /* 1X&HRPD 模式 */
    AT_SYSCFG_RAT_GSM           = 13,                                               /* GGSM接入技术 */
    AT_SYSCFG_RAT_WCDMA         = 14,                                               /* WCDMA接入技术 */
    AT_SYSCFG_RAT_NO_CHANGE     = 16,                                               /* 接入技术无变化 */
    AT_SYSCFG_RAT_BUTT
};
typedef VOS_UINT8 AT_SYSCFG_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AT_SYSCFG_RAT_PRIO_ENUM
 结构说明  : AT^syscfg 中acqorder接入优先级的取值
1.日    期  : 2011年07月15日
  作    者  : z00161729
  修改内容  : 新增结构
*****************************************************************************/
enum AT_SYSCFG_RAT_PRIO_ENUM
{
    AT_SYSCFG_RAT_PRIO_AUTO = 0,                                                /* 接入优先级参数为自动 */
    AT_SYSCFG_RAT_PRIO_GSM,                                                     /* 接入优先级参数为GSM优先  */
    AT_SYSCFG_RAT_PRIO_WCDMA,                                                   /* 接入优先级参数为WCDMA优先 */
    AT_SYSCFG_RAT_PRIO_NO_CHANGE,                                               /* 接入优先级为不改变 */
    AT_SYSCFG_RAT_PRIO_BUTT
};
typedef VOS_UINT8 AT_SYSCFG_RAT_PRIO_ENUM_UINT8;


typedef VOS_UINT32 (*MN_PS_EVT_FUNC)(VOS_UINT8 ucIndex, VOS_VOID *pEvtInfo);

/*****************************************************************************
 结构名    : AT_PS_EVT_FUNC_TBL_STRU
 结构说明  : PS域事件处理函数表结构
*****************************************************************************/
/*lint -e958 -e959 修改人:l60609;原因:64bit*/
typedef struct
{
    VOS_UINT32                          ulEvtId;
    MN_PS_EVT_FUNC                      pEvtFunc;
} AT_PS_EVT_FUNC_TBL_STRU;
/*lint +e958 +e959 修改人:l60609;原因:64bit*/

/* Deleted by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
/* Deleted by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
typedef struct
{
    VOS_UINT8                           ucShellPwdCheckFlag;                    /* VOS_TRUE:密码已校验，VOS_FALSE:密码未校验*/
    VOS_UINT8                           ucErrTimes;                             /* 记录密码输入错误的次数 */
    VOS_UINT8                           aucRsv[2];
}AT_SP_WORD_CTX_STRU;
#endif

/*****************************************************************************
 结构名    : AT_FACAUTHPUBKEY_SET_REQ_STRU
 结构说明  : AT解析AT^FACAUTHPUBKEY命令后存储参数的结构体(未做half-byte解析)

  1.日    期   : 2012年04月18日
    作    者   : L47619
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    /* 鉴权公钥码流(未做half-byte解析) */
    VOS_UINT8                           aucPubKey[AT_FACAUTHPUBKEY_PARA_LEN];
    /* 鉴权公钥SSK签名码流(未做half-byte解析) */
    VOS_UINT8                           aucPubKeySign[AT_FACAUTHPUBKEY_SIGN_PARA_LEN];
}AT_FACAUTHPUBKEY_SET_REQ_STRU;

/*****************************************************************************
 结构名    : AT_SIMLOCKDATAWRITE_SET_REQ_STRU
 结构说明  : AT解析AT^SIMLOCKDATAWRITE命令后存储参数的结构体(未做half-byte解析)

  1.日    期   : 2012年04月18日
    作    者   : L47619
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    /* 结构体码流, 包含该锁网锁卡类型的包括状态, 锁网号段, CK, UK等所有信息(未做half-byte解析) */
    VOS_UINT8       aucCategoryData[AT_SIMLOCKDATAWRITE_PARA_LEN];
}AT_SIMLOCKDATAWRITE_SET_REQ_STRU;


typedef struct
{
    TAF_UINT8                           aucSerialNum[TAF_SERIAL_NUM_NV_LEN];
}TAF_PH_SERIAL_NUM_STRU;
/*****************************************************************************
结构名    : AT_NV_WG_RF_MAIN_BAND_STRU
结构说明  : AT^APSEC的请求消息结构
1.日    期  : 2013年01月18日
  作    者  : l00198894
  修改内容  : Body SAR项目新增
*****************************************************************************/
typedef struct
{
    AT_WCDMA_BAND_SET_UN        unWcdmaBand;                    /* 记录W频段信息 */
    VOS_UINT32                  ulRsv;
    AT_GSM_BAND_SET_UN          unGsmBand;                      /* 记录G频段信息 */
}AT_NV_WG_RF_MAIN_BAND_STRU;

/*****************************************************************************
结构名    : AT_BODYSARWCDMA_SET_PARA_STRU
结构说明  : Body SAR设置命令参数结构体
1.日    期  : 2013年03月12日
  作    者  : l00198894
  修改内容  : Body SAR项目新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                   ucParaNum;                                      /* 设置命令参数组数 */
    VOS_UINT8                   ucRsv[3];                                       /* 保留位 */
    VOS_INT16                   asPower[AT_BODYSARWCDMA_MAX_PARA_GROUP_NUM];    /* W频段功率门限值 */
    VOS_UINT32                  aulBand[AT_BODYSARWCDMA_MAX_PARA_GROUP_NUM];    /* W频段位域 */
}AT_BODYSARWCDMA_SET_PARA_STRU;



/* 删除解析AT^EOPLMN命令后存储参数的结构体AT_EOPLMN_SET_REQ_STRU */


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/* Deleted by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
/* Deleted by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

/* Added by l60609 for AT Project，2011-10-12,  Begin*/
extern AT_PB_CONVERSION_TABLE_STRU  g_astIraToUnicode[AT_PB_IRA_MAX_NUM];
extern AT_PB_CONVERSION_TABLE_STRU  g_astGsmToUnicode[AT_PB_GSM_MAX_NUM];
extern AT_PB_CONVERSION_TABLE_STRU  g_astGsm7extToUnicode[AT_PB_GSM7EXT_MAX_NUM];

/* Added by l60609 for AT Project，2011-10-12,  End*/

extern AT_CMD_FORMAT_TYPE                   gucAtCmdFmtType;
extern pAtChkFuncType                       pgAtCheckFunc;
extern AT_V_TYPE                            gucAtVType;            /* 指示命令返回码类型 */
extern AT_CSCS_TYPE                         gucAtCscsType;
extern AT_CLIENT_MANAGE_STRU                gastAtClientTab[AT_MAX_CLIENT_NUM];
extern TAF_UINT8                            gaucAtCrLf[];               /*回车换行*/
extern const TAF_UINT8                      gaucAtCmeErrorStr[];        /*错误提示字串*/
extern const TAF_UINT8                      gaucAtCmsErrorStr[];        /*错误提示字串*/
extern const TAF_UINT8                      gaucAtTooManyParaStr[];     /*参数太多提示字串*/
extern AT_SEND_DATA_BUFFER_STRU             gstAtSendData;
extern AT_SEND_DATA_BUFFER_STRU             gstAtCombineSendData[];
extern const AT_SMS_CMD_TAB_STRU            gastAtSmsCmdTab[];
extern AT_CMD_ECHO_TYPE                     gucAtEType;
extern VOS_UINT32                           gucAtXType;
extern VOS_UINT32                           gucAtQType;
extern TAF_UINT8                            *pgucAtSndCrLfAddr;
extern TAF_UINT8                            *pgucAtSndCodeAddr;
extern TAF_UINT8                            gstAtSendDataBuffer[];
extern const AT_RETURN_TAB_TYPE_STRU        gastAtReturnCodeTab[];
extern const AT_STRING_TYPE_STRU            gastAtStringTab[];
extern TAF_UINT8                            gastAtPppIndexTab[AT_MAX_CLIENT_NUM];
extern TAF_UINT32                           gulPBPrintTag;
extern AT_PB_INFO_STRU                      gstPBATInfo;
extern VOS_UINT8                            g_ucXsmsRecNum;
extern TAF_UINT8                            gucAtPortSel;
/*->f62575*/

extern const TAF_UINT16 gusAtSmsCmdNum;

extern MN_OPERATION_ID_T                    g_OpId;
extern AT_CSTA_NUM_TYPE_ENUM_U8             g_enAtCstaNumType;

extern AT_COMBINE_CMD_SPLIT_STRU            g_stAtComCmdSplit[];
extern AT_COMBINE_CMD_PARSE_RSLT_STRU       g_stAtComCmdParseRslt[];
extern const TAF_UINT16                     gusAtBasicCmdNum;

extern AT_DATA_STREAM_BUFFER_STRU           g_aucAtDataBuff[];




extern TAF_UINT8                    gucAtOmIndex;
extern TAF_UINT8                    gucOmDiagIndex;

extern AT_SET_PORT_PARA_MAP_STRU            g_astSetPortParaMap[AT_SETPORT_DEV_MAP_LEN];
extern AT_DEVICE_CMD_CTRL_STRU              g_stAtDevCmdCtrl;
extern VOS_BOOL                             g_bAtDataLocked;
extern VOS_UINT8                            g_ucDtrDownFlag;

#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
extern AT_SP_WORD_CTX_STRU                  g_stSpWordCtx;
#endif

#if(FEATURE_ON == FEATURE_MULTI_MODEM)
/* AT与编译两次的PID对应表  */
extern AT_MODEM_PID_TAB_STRU                   g_astAtModemPidTab[];
#endif


extern AT_MTA_BODY_SAR_STATE_ENUM_UINT16       g_enAtBodySarState;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/
extern VOS_UINT32 At_ProcSimLockPara(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucData,
    VOS_UINT16                          usLen
);

/***All the following function are defined in AtSetParaCmd.c***/
extern VOS_UINT32 AT_SetMDatePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetFacInfoPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetPhyNumPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetGTimerPara(VOS_UINT8 ucIndex);

/***All the following function are defined in AtQueryParaCmd.c***/
extern VOS_UINT32 AT_QryMDatePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryFacInfoPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryPhyNumPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryGTimerPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryRsimPara(VOS_UINT8 ucIndex);

extern TAF_UINT32   At_QryCmgdPara(TAF_UINT8 ucIndex);
extern TAF_VOID     At_TimeOutProc(REL_TIMER_MSG *pMsg);
extern TAF_UINT32   At_ClientIdToUserId (TAF_UINT16 usClientId, TAF_UINT8 *pucIndexId);

extern TAF_UINT32   At_CheckPbSpecialCmd (TAF_UINT8* pData, TAF_UINT16 ulLen);
extern TAF_VOID     At_FormatResultData(TAF_UINT8 ucIndex,TAF_UINT32 ReturnCode);
extern TAF_UINT32   At_ParseExtendCmd(TAF_UINT8 * pData, TAF_UINT16 usLen);
extern TAF_UINT32   At_ParseDCmd(TAF_UINT8 * pData, TAF_UINT16 usLen);
extern TAF_UINT32   At_ParseSCmd(TAF_UINT8 * pData, TAF_UINT16 usLen);
extern TAF_UINT32   At_ParseDMCmd(TAF_UINT8 * pData, TAF_UINT16 usLen);
extern TAF_UINT32   At_ParseBasicCmd(TAF_UINT8 * pData, TAF_UINT16 usLen);
extern TAF_VOID     At_SetMode(TAF_UINT8 ucIndex,AT_MODE_TYPE Mode,TAF_UINT8 ucSubMode);
extern TAF_UINT32   At_ParsePara(TAF_UINT8 * pData, TAF_UINT16 usLen);
extern TAF_UINT32   At_SetParaCmd(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryParaCmd(TAF_UINT8 ucIndex);
extern TAF_VOID     At_SendResultData(TAF_UINT8 ucIndex, TAF_UINT8* pData, TAF_UINT16 usLen );
extern VOS_VOID     AT_DisplayResultData (VOS_UINT8 ucIndex,VOS_UINT16 usLen);
extern VOS_VOID     AT_DisplaySelResultData(VOS_UINT16 usLen,VOS_UINT8 ucCount);
extern VOS_VOID     At_ProcHoldAtCmd (VOS_UINT8 ucIndex);
/* Modefied by c64416 for AT Project，2011-10-10,  Begin */
extern TAF_UINT32   At_CheckUsimStatus (
    TAF_UINT8                          *pucCmdName,
    VOS_UINT8                           ucIndex);
/* Modefied by c64416 for AT Project，2011-10-10,  End*/
extern TAF_UINT32   At_AsciiNum2BcdNum (TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen);
extern TAF_UINT32   At_AtioRcvDataInd (TAF_UINT8 ucIndex,TAF_UINT8* pData,TAF_UINT16 usLen);
extern TAF_UINT32   At_UnicodePrint2Unicode(TAF_UINT8 *pData,TAF_UINT16 *pLen);
extern TAF_UINT32 At_UnicodePrintToAscii(TAF_UINT8 *pData,TAF_UINT16 *pLen);
extern TAF_VOID     At_PbAscii2Gsm7BitTransfer(TAF_UINT8 *pData, TAF_UINT16 *pLen);
extern TAF_VOID     At_PbGsm7bit2AsciiTransfer(TAF_UINT8 *pucAlphaTag, TAF_UINT8 *pulAlphaTagLen);
extern TAF_UINT32   At_UnicodeTranserToAscii(TAF_UINT8 *pData,TAF_UINT16 *pLen);
extern TAF_UINT32   At_FindMinCodeOffset(const TAF_UINT8 *pData, TAF_UINT16 usLen);
extern TAF_UINT32 At_UnicodeTransferTo81CalcLength(const TAF_UINT8 *pucData,
                                            TAF_UINT16      usLen,
                                            TAF_UINT16      *pusBaseCode,
                                            TAF_UINT16      *pusDstLen);
extern TAF_UINT32 At_UnicodeTransferTo82CalcLength(const TAF_UINT8 *pucData,
                                            TAF_UINT16      usLen,
                                            TAF_UINT16      *pusBaseCode,
                                            TAF_UINT16      *pusDstLen);
extern TAF_UINT32 At_UnicodeTransferTo81(const TAF_UINT8 *pucData,
                                      TAF_UINT16      usLen,
                                      TAF_UINT16      usCodeBase,
                                      TAF_UINT8       *pucDest);
extern TAF_UINT32 At_UnicodeTransferTo82(const TAF_UINT8 *pucData,
                                  TAF_UINT16      usLen,
                                  TAF_UINT16      usCodeBase,
                                  TAF_UINT8       *pucDest);
extern TAF_UINT32   At_UnicodeTransfer(TAF_UINT8 *pData, TAF_UINT16 *pLen, TAF_UINT32 ulMaxLength);
extern TAF_UINT32 At_OneUnicodeToGsm(TAF_UINT16 usSrc, TAF_UINT8 *pucDst, TAF_UINT16 *pusDstLen);
extern TAF_VOID At_PbGsmToUnicode(TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen, TAF_UINT8 *pucDst, TAF_UINT16 *pusDstLen);
extern TAF_UINT8*   At_GetStrContent(TAF_UINT32 ulType);
extern TAF_UINT32 At_SendRxOnOffToHPA( VOS_UINT32 ulRxSwitch );
extern TAF_UINT32 At_SendTxOnOffToHPA( TAF_UINT8 ucRxSwitch );
extern VOS_UINT32 At_SendRxOnOffToGHPA( VOS_UINT8 ucIndex, VOS_UINT32 ulRxSwitch );
extern VOS_UINT32 At_SendTxOnOffToGHPA( VOS_UINT8 ucIndex, VOS_UINT8 ucSwitch );
extern TAF_UINT32   At_String2Hex(TAF_UINT8 *nptr,TAF_UINT16 usLen,TAF_UINT32 *pRtn);
extern TAF_UINT32   AT_CountDigit(TAF_UINT8 *pData,TAF_UINT32 ulLen,TAF_UINT8 Char,TAF_UINT32 ulIndex);
extern TAF_UINT16   At_UnicodeFormatPrint(const TAF_UINT8 *pSrc, TAF_UINT8 *pDest, TAF_UINT32 Dcs);
extern TAF_UINT32   At_Ascii2UnicodePrint(TAF_UINT32 MaxLength,TAF_INT8 *headaddr,TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen);
extern TAF_UINT16   At_PrintReportData(TAF_UINT32 MaxLength,TAF_INT8 *headaddr,TAF_UINT8 ucDataCodeType,TAF_UINT8 *pucDst,TAF_UINT8 *pucSrc,TAF_UINT16 usSrcLen);
extern TAF_UINT32   At_ChgTafErrorCode(TAF_UINT8 ucIndex,TAF_ERROR_CODE_ENUM_UINT32 enTafErrorCode);
/* Del At_AbortCmdProc */
extern TAF_UINT32   At_CheckCharWcmd(TAF_UINT8 * pData, TAF_UINT16 usLen);
extern TAF_UINT32   At_ParseWCmd(TAF_UINT8 * pData, TAF_UINT16 usLen);
extern TAF_UINT32   At_Unicode2UnicodePrint(TAF_UINT32 MaxLength,TAF_INT8 *headaddr,TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen);
extern TAF_VOID     At_UsimGsm7bit2AsciiTransfer(TAF_UINT8 *pucData, TAF_UINT32 *pulDataLen);
extern TAF_UINT32   At_HexString2AsciiNumPrint(TAF_UINT32 MaxLength,TAF_INT8 *headaddr,TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen);
extern TAF_UINT32   At_MuxCmdProc (TAF_UINT8 ucIndex, TAF_UINT8* pData, TAF_UINT16 usLen);
extern TAF_UINT32   At_CheckMuxCmd(TAF_UINT8 *pData,TAF_UINT16 usLen );
extern TAF_VOID     At_SendReportMsg(TAF_UINT8 ucType,TAF_UINT8* pData,TAF_UINT16 usLen);
extern TAF_VOID     At_SmsMsgProc(MN_AT_IND_EVT_STRU *pstData,TAF_UINT16 usLen);
extern TAF_VOID     At_SetMsgProc(TAF_UINT8* pData,TAF_UINT16 usLen);
extern TAF_VOID     At_QryMsgProc(TAF_UINT8* pData,TAF_UINT16 usLen);
extern TAF_VOID     At_CsMsgProc(MN_AT_IND_EVT_STRU *pstData,TAF_UINT16 usLen);
extern TAF_VOID     At_PppReleaseIndProc(TAF_UINT8 ucIndex);
extern TAF_VOID     At_PhMsgProc(TAF_UINT8* pData,TAF_UINT16 usLen);
extern TAF_VOID     At_SsMsgProc(TAF_UINT8* pData,TAF_UINT16 usLen);
extern TAF_VOID     At_DataStatusMsgProc(TAF_UINT8* pData,TAF_UINT16 usLen);
extern TAF_UINT32   At_PrintfString(TAF_UINT8 *pStr1,TAF_UINT8 *pStr2);
extern TAF_VOID     At_SendDataProc(TAF_UINT8* pData,TAF_UINT16 usLen);
extern TAF_VOID     At_CmdCnfMsgProc(TAF_UINT8* pData,TAF_UINT16 usLen);
extern TAF_VOID     At_VcMsgProc(MN_AT_IND_EVT_STRU *pstData,TAF_UINT16 usLen);
/*lint -e960 修改人:l60609;原因:64bit*/
extern TAF_INT32    At_sprintf(TAF_INT32 MaxLength,TAF_CHAR *headaddr,TAF_CHAR *curraddr,const TAF_CHAR *fmt,...);
/*lint +e960 修改人:l60609;原因:64bit*/
extern TAF_VOID     At_PIHMsgProc(MsgBlock* pMsg);
extern TAF_VOID     At_STKMsgProc(MsgBlock* pMsg);
extern TAF_VOID     At_PbMsgProc(MsgBlock* pMsg);
extern TAF_VOID     At_TAFPbMsgProc(TAF_UINT8* pData,TAF_UINT16 usLen);


/* Modified by L60609 for AT Project，2011-10-17,  Begin*/
/*************各端口初始化函数****************/
extern VOS_UINT32 At_UsbModemRelInd(
    VOS_UINT8                           ucPortType,
    VOS_UINT8                           ucDlci
);


/* Modified by L60609 for AT Project，2011-10-17,  End*/

extern TAF_UINT32   At_SendData(TAF_UINT8 ucIndex,TAF_UINT8 ucType,TAF_UINT8* pData,TAF_UINT16 usLen);
extern TAF_UINT32   At_HexAlpha2AsciiString(TAF_UINT32 MaxLength,TAF_INT8 *headaddr,TAF_UINT8 *pucDst,TAF_UINT8 *pucSrc,TAF_UINT16 usSrcLen);

extern TAF_VOID     AT_MapCallTypeModeToClccMode(MN_CALL_TYPE_ENUM_U8 enCallType, VOS_UINT8 *penClccMode);
extern AT_CMD_CURRENT_OPT_ENUM  At_GetMnOptType(TAF_UINT8 ucType);

extern VOS_UINT32 At_SetSecuBootPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QrySecuBootPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetWiFiEnablePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiEnablePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiModePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiModePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiBandPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiBandPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiFreqPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiFreqPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiRatePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiRatePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiPowerPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiPowerPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiTxPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiTxPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiRxPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiRxPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiPacketPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiPacketPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiSsidPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiSsidPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiKeyPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiKeyPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiLogPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiLogPara(VOS_UINT8 ucIndex);
/* Added by L00171473 for DTS2012020106679,AT WT工位 2012-01-17  Begin */
extern VOS_UINT32 AT_SetWifiInfoPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWifiPaRangePara (VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWifiPaRangePara (VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestWifiPaRangePara (VOS_UINT8 ucIndex);
/* Added by L00171473 for DTS2012020106679,AT WT工位 2012-01-17  End */


/* Add by c00172979 for V7代码同步, 2012-04-13, Begin   */
#if (FEATURE_ON==FEATURE_LTE)
/* Add by c00172979 for V7代码同步, 2012-04-13, End   */
extern TAF_UINT32 At_SetSfm(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_QrySfm(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetFrStatus(VOS_UINT8 ucIndex);
#endif
#if (FEATURE_LTE==FEATURE_ON)
extern VOS_UINT32 AT_GetLteFeatureInfo(AT_FEATURE_SUPPORT_ST  *pstFeATure);
#endif
/* Add by c00172979 for V7代码同步, 2012-04-13, End   */
extern VOS_UINT32 AT_SetTmmiPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryTmmiPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetChrgEnablePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryChrgEnablePara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_QryChrgInfoPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetTestScreenPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryBatVolPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetSelRfPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QrySelRfPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWebPwdPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWebPwdPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryProdTypePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryFeaturePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QrySecuBootFeaturePara(VOS_UINT8 ucIndex);
extern TAF_UINT32   At_SetCmgfPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCmgsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCmglPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCmgcPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCmstPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCmssPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCmgwPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCmgrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetDPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetAPara(TAF_UINT8 ucIndex);
extern VOS_UINT32   At_SetHPara(VOS_UINT8 ucIndex);
extern TAF_UINT32   At_SetEPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetVPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetTPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetPPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetXPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetZPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetQPara(TAF_UINT8 ucIndex);
extern VOS_UINT32   At_SetAmpCPara(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_SetAmpDPara(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_SetAmpSPara(VOS_UINT8 ucIndex);
extern VOS_UINT32   AT_SetLPara(VOS_UINT8 ucIndex);
extern VOS_UINT32   AT_SetMPara(VOS_UINT8 ucIndex);
extern TAF_UINT32   At_SetFPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetMsIdInfo(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetS0Para(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetS3Para(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetS4Para(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetS5Para(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetS6Para(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetS7Para(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetClipPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetClirPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetColpPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCscsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCmeePara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCeerPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCregPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCsdhPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCnmiPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCnmaPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCcnmaPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCgregPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCgsmsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCscaPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCsmsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCsmpPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCpmsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCmsqPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCssmPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCmgdPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCstaPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCcugPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCssnPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetChldPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetVtsPara(TAF_UINT8 ucIndex);
extern VOS_UINT32   At_SetClccPara(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_SetCpasPara(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_SetDtmfPara(VOS_UINT8 ucIndex);
extern VOS_UINT32   AT_SetCdurPara(VOS_UINT8 ucIndex);

extern TAF_UINT32   At_SetCrcPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCbstPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCmodPara(TAF_UINT8 ucIndex);
extern VOS_UINT32   At_SetChupPara(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_SetCmmiPara(VOS_UINT8 ucIndex);
extern VOS_UINT32   AT_SetCgdscontPara(VOS_UINT8 ucIndex);
extern VOS_UINT32   AT_SetCgdcontPara(VOS_UINT8 ucIndex);
extern TAF_UINT32   AT_SetCgeqreqPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetPfverPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_SetCgeqminPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_SetCgpaddrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_SetCgcmodPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_SetCgactPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_SetCgansPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_SetCgtftPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_SetCgautoPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 atSetCgeqosPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 atQryCgeqosPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 atSetCgeqosrdpPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 atSetCgcontrdpPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 atSetCgscontrdpPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 atSetCgtftrdpPara(VOS_UINT8 ucIndex);
extern TAF_UINT32   At_SetCgdataPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCsndPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCgattPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCgcattPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCopsPara(TAF_UINT8 ucIndex);

#if (FEATURE_ON == FEATURE_CSG)
extern VOS_UINT32 AT_SetCsgIdSearchPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_AbortCsgIdSearchPara(
    VOS_UINT8                           ucIndex
);
#endif

extern TAF_UINT32   At_SetCgclassPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCfunPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCgmiPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCgmmPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCgmrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCgsnPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCimiPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCsqPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCbcPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCpdwPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_WriteSnPara(VOS_UINT8 ucIndex);
extern TAF_UINT32   At_SetSnPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetHwVerPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetFHVerPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCLACPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetGcapPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetSrvstPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetRssiPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetTimePara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCtzrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetModePara(TAF_UINT8 ucIndex);
extern VOS_UINT32   At_SetSimstPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetHSPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCpbsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCpbrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCpbr2Para(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCpbfPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCpbwPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCpbwPara2(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetScpbwPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetScpbrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCnumPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCsimPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCchoPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCchcPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCglaPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCrsmPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCpinPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCardlockPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCpin2Para(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCcwaPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCcfcPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetClckPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCtfrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCmlckPara (TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCusdPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCpwdPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_SetDsFlowClrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_SetDsFlowQryPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_SetDsFlowRptPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_SetCgdnsPara(TAF_UINT8 ucIndex);
extern VOS_UINT32   At_SetCpamPara(VOS_UINT8 ucIndex);
extern TAF_UINT32   At_SetCcinPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetStpdPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetStmnPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetSttrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetStenPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_ChangeSATCmdType(TAF_UINT32 cmdNo, TAF_UINT32 *CmdType);
extern TAF_UINT32   At_SetStgiPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryStsfPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryStgiPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryImsichgPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetStsfPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetStgrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCstrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCsinPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCsenPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCsmnPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCstcPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetImsichgPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetTestPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetFPlmnPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetQuickStart(TAF_UINT8 ucIndex);
/* <==l00107747 快速开机 */
extern TAF_UINT32   At_SetAutoAttach(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetSystemInfo(TAF_UINT8 ucIndex);
extern VOS_UINT32   At_SetSystemInfoEx(TAF_UINT8 ucIndex);
/*DTS2012041102190 : h00135900 start in 2011-04-11 AT代码融合*/
extern TAF_UINT32 At_QryLtecsInfo(TAF_UINT8 ucIndex);

extern TAF_UINT32 At_QryCemode(TAF_UINT8 ucIndex);
/*DTS2012041102190 : h00135900 end in 2011-04-11 AT代码融合*/
/* ==> x68770 For WAS AutoTest */
extern TAF_UINT32   At_SetCwasPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCellSearch(TAF_UINT8 ucIndex);
/*w101153*/
extern TAF_UINT32   At_SetCGasPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetAppDialModePara(VOS_UINT8 ucIndex);

extern TAF_UINT32   At_SetCpolPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCplsPara(TAF_UINT8 ucIndex);

extern TAF_UINT32   At_SetCmmPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetSPNPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCardModePara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetDialModePara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetPortSelPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryPortSelPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCurcPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCurcPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryTimePara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCtzrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetBOOTPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCellInfoPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_GetMeanRpt( TAF_UINT8 ucIndex );
/* <== x68770 For WAS AutoTest */

extern TAF_UINT32   At_SetQcdmgPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetU2DiagPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetPcscInfo(TAF_UINT8 ucIndex);
extern VOS_UINT32   At_SetPort(VOS_UINT8 ucIndex);
extern TAF_UINT32   At_SetGetportmodePara(TAF_UINT8 ucIndex);
extern VOS_UINT32   At_SetCvoicePara(TAF_UINT8 ucIndex);
extern VOS_UINT32   At_SetDdsetexPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetUssdModePara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetAdcTempPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCommDebugPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 AT_SetNvRststtsPara(VOS_UINT8 ucIndex);

extern TAF_UINT32   At_SetCmsrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCmgiPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCmmtPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetAt2OmPara(TAF_UINT8 ucIndex);

extern TAF_UINT32   At_QryU2DiagPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryPcscInfo(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCellSearch(TAF_UINT8 ucIndex);
extern VOS_UINT32   At_QryPort(VOS_UINT8 ucIndex);
extern TAF_UINT32   AT_SetDwinsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetYjcxPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetpidPara(TAF_UINT8 ucIndex);
extern VOS_UINT32   AT_SetNdisdupPara (VOS_UINT8 ucIndex);
extern TAF_UINT32   At_SetAuthdataPara (TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCrpnPara (TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetRxDiv(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetCallSrvPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetCsdfltPara(VOS_UINT8 ucIndex);

extern TAF_UINT32  At_SetTModePara(TAF_UINT8 ucIndex );
extern TAF_UINT32  At_SetFChanPara(TAF_UINT8 ucIndex );
extern TAF_UINT32  At_SetFTxonPara(TAF_UINT8 ucIndex );
extern TAF_UINT32  AT_SetFDac(TAF_UINT8 ucIndex );
extern TAF_UINT32  At_SetFRxonPara(VOS_UINT8 ucIndex );
extern TAF_UINT32  At_SetFpaPara(VOS_UINT8 ucIndex );
extern TAF_UINT32  At_SetFlnaPara(VOS_UINT8 ucIndex );
extern VOS_UINT32  At_SetDataLock(VOS_UINT8 ucIndex );
extern VOS_UINT32  At_SetSD(VOS_UINT8 ucIndex );
extern VOS_UINT32  At_SetGPIOPL(VOS_UINT8 ucIndex );
/* Add by c00172979 for V7代码同步, 2012-04-13, Begin   */
#if (FEATURE_ON==FEATURE_LTE)
/* Add by c00172979 for V7代码同步, 2012-04-13, End   */
VOS_UINT32  At_SetInfoRRS(VOS_UINT8 ucIndex );
#endif
extern VOS_UINT32  At_SetInfoRBU(VOS_UINT8 ucIndex );
extern VOS_UINT32 At_SaveRxDivPara(VOS_UINT16  usSetDivBands,VOS_UINT8 ucRxDivCfg);


extern VOS_UINT32   At_SetBsn(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_SetDpaCat(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_QryDpaCat(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_SetHspaSpt(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_ReadDpaCatFromNV(VOS_UINT8 *pucDpaRate);
extern VOS_UINT32   AT_ReadRrcVerFromNV(VOS_UINT8 *pucRrcVer);
extern VOS_UINT32   At_WriteDpaCatToNV(VOS_UINT8 ucDpaRate);
extern VOS_UINT32   AT_WriteRrcVerToNV(VOS_UINT8 ucSrcWcdmaRRC);

extern VOS_UINT32   AT_QryHspaSpt(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_SetQosPara(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_SetSDomainPara(VOS_UINT8 ucIndex);

extern TAF_UINT32  At_QryTModePara(TAF_UINT8 ucIndex );
extern TAF_UINT32  At_QryFChanPara(TAF_UINT8 ucIndex );
extern TAF_UINT32  At_QryFTxonPara(TAF_UINT8 ucIndex );
extern TAF_UINT32  AT_QryFDac(TAF_UINT8 ucIndex );

extern VOS_UINT32   At_QryPlatForm(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_QryBsn(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_QryCsVer(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_QryQosPara(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_QrySDomainPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QrySimLockPlmnInfo(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_UnlockSimLock(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulParaCnt,
    AT_PARSE_PARA_TYPE_STRU             *pstParalist
);

extern VOS_UINT32 AT_ConvertCharToHex(
        VOS_UINT8                           ucChar,
        VOS_UINT8                          *pucHexValue
    );
extern VOS_UINT32 At_SetSimLockPlmnInfo(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulParaCnt,
    AT_PARSE_PARA_TYPE_STRU             *pstParalist
);
extern VOS_UINT32 At_CovertAtParaToSimlockPlmnInfo(
    VOS_UINT32                          ulParaCnt,
    AT_PARSE_PARA_TYPE_STRU             *pstParalist,
    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU  *pstSimLockPlmnInfo
);
extern VOS_UINT32 At_SetMaxLockTimes(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QryMaxLockTimes(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_QryDataLock(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_QrySD(VOS_UINT8 ucIndex );
extern VOS_UINT32   At_QryGPIOPL(VOS_UINT8 ucIndex );
extern VOS_UINT32   At_QryVersion(VOS_UINT8 ucIndex );

/*新增的hspa AT命令设置函数*/
extern TAF_UINT32   At_SetRRCVersion(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCSNR(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetFreqLock(TAF_UINT8 ucIndex);

extern VOS_UINT32   At_SetSysCfgPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetSysCfgExPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_IsSupportGMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
);
extern VOS_UINT32 AT_IsSupportWMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
);
extern VOS_UINT32 AT_IsSupportLMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 AT_IsSupport1XMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
);

VOS_UINT32 AT_IsSupportHrpdMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
);

VOS_UINT32 AT_SetQuitCallBack( VOS_UINT8 ucIndex  );
VOS_UINT32 AT_SetCSidList( VOS_UINT8 ucIndex   );
VOS_UINT32 AT_ConvertCSidListMcc(
    VOS_UINT8                          *pucPara,
    VOS_UINT16                          usLen,
    VOS_UINT32                         *pstMcc
);
VOS_UINT32 AT_SetCSidEnable(VOS_UINT8 ucIndex );
VOS_UINT32 AT_SetEncryptCall(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetEncryptCallRemoteCtrl(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetEncryptCallCap( VOS_UINT8 ucIndex );
VOS_UINT32 AT_SetEncryptCallKmc( VOS_UINT8 ucIndex );
VOS_UINT32 AT_SetEccTestMode( VOS_UINT8 ucIndex );

VOS_UINT32 AT_SetClocinfoEnable(VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_QryCLocInfo(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetPrivacyModePreferred(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryPrivacyModePreferred(VOS_UINT8 ucIndex);

#endif

VOS_UINT32 AT_SetCclprPara(VOS_UINT8 ucIndex);


VOS_UINT32 AT_SetNetScan(
    VOS_UINT8                           ucIndex
);

VOS_UINT32 AT_AbortNetScan(
    VOS_UINT8                           ucIndex
);

extern TAF_UINT32   At_SetImeiPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetTrigPara(TAF_UINT8 ucIndex);

#ifndef _PS_COMPILE_EDGE_ADAPT_MOIRI_B073_
extern TAF_UINT32   At_SetGcfIndPara(TAF_UINT8 ucIndex);
#endif
extern VOS_UINT32  At_SetGlastErrPara(TAF_UINT8 ucIndex);
extern VOS_UINT32   At_SetClvlPara(VOS_UINT8 ucIndex);

extern VOS_UINT32   At_SetVMSETPara(VOS_UINT8 ucIndex);
extern TAF_UINT32   At_SetCmgsSegmentPara(TAF_UINT8 ucIndex);

extern VOS_UINT32   AT_SetVertime ( VOS_UINT8 ucIndex );

/*内部设置和查询NV项命令*/
#if ( VOS_WIN32 == VOS_OS_VER )
extern VOS_UINT32   AT_SetNvimPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_ResetNplmn ( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_SetNplmn ( VOS_UINT8 ucIndex );
extern VOS_UINT32 At_SetReadUsimStub( VOS_UINT8 ucIndex );

extern VOS_UINT32 AT_SetPidReinitPara ( VOS_UINT8 ucIndex );
extern VOS_UINT32   AT_SetRplmnStub( VOS_UINT8 ucIndex );

VOS_UINT32  AT_SetDamParaStub( VOS_UINT8 ucIndex );

VOS_UINT32  AT_SetCsgStub( VOS_UINT8 ucIndex );

VOS_UINT32  AT_SetEonsParaStub( VOS_UINT8 ucIndex );
VOS_UINT32  AT_SetWildCardParaStub( VOS_UINT8 ucIndex );
extern TAF_UINT32 AT_SetUSIMPara(TAF_UINT8 ucIndex);

extern TAF_UINT32 AT_SetSIMPara(TAF_UINT8 ucIndex);


extern VOS_UINT32 AT_RefreshUSIMPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetSTKParaStub(VOS_UINT8 ucIndex);

extern VOS_UINT32   AT_SetTinTypeStub( VOS_UINT8 ucIndex );
extern  VOS_UINT32  AT_SetPsBearIsrFlgStub( VOS_UINT8 ucIndex );
extern VOS_UINT32 At_QryTinTypeStub(VOS_UINT8 ucIndex);

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-30, begin */

extern VOS_UINT32  AT_SetPsRegisterContainDrxStub( VOS_UINT8 ucIndex );
extern  VOS_UINT32 AT_QryPsRegisterContainDrxStub(VOS_UINT8 ucIndex);
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-30, end */

extern VOS_UINT32 AT_SetCsUnAvailPlmnStub( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_SetForbRoamTaStub( VOS_UINT8 ucIndex );

VOS_UINT32 AT_SetDisableRatPlmnStub( VOS_UINT8 ucIndex );

/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-15, begin */
extern VOS_UINT32 AT_SetImsRatStub(VOS_UINT8 ucIndex);
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-15, end */
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-10-23, begin */
extern VOS_UINT32 AT_SetImsCapabilityStub(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetDomainStub(VOS_UINT8 ucIndex);
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-10-23, end */
extern VOS_UINT32 AT_SetCmdImsRoamingStub(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetCmdRedailStub(VOS_UINT8 ucIndex);
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-16, begin */
extern VOS_UINT32 AT_SetImsVoiceInterSysLauEnableStub(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetImsVoiceMMEnableStub(VOS_UINT8 ucIndex);
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-16, end */
extern VOS_UINT32 AT_SetCmdImsUssdStub(VOS_UINT8 ucIndex);
#endif

/*测试用PDP打桩命令*/
/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-08-22, begin */
/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-08-22, end */
extern VOS_UINT32 At_SetNdisAddPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetDnsPrim(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetDnsSnd(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_GetSimLockStatus(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetGodloadPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetResetPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetNvBackUpPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetNvRestorePara(VOS_UINT8 ucIndex);

/* Added by d00212987 for BalongV9R1 NV备份数据丢失容错&恢复 项目 2013-10-24, begin */
extern VOS_UINT32 AT_SetNvManufactureExtPara( VOS_UINT8 ucIndex );
/* Added by d00212987 for BalongV9R1 NV备份数据丢失容错&恢复 2013-10-24, end */

extern TAF_UINT32   At_QryApDialModePara(TAF_UINT8 ucIndex);
extern VOS_UINT32   AT_SetWifiGlobalMacPara(VOS_UINT8 ucIndex);
extern VOS_UINT32   AT_QryWifiGlobalMacPara(VOS_UINT8 ucIndex);
extern VOS_UINT32   AT_SetCsqlvlPara(VOS_UINT8 ucIndex);

VOS_UINT32 At_QryCpuLoadPara(VOS_UINT8 ucIndex);

extern VOS_UINT32   AT_SetDockPara (VOS_UINT8 ucIndex);
extern VOS_UINT32   AT_QryAppdmverPara ( VOS_UINT8 ucIndex );
extern VOS_UINT32   AT_QryDislogPara ( VOS_UINT8 ucIndex );
extern VOS_UINT32   AT_SetOpwordPara ( VOS_UINT8  ucIndex );
extern VOS_UINT32   AT_SetCpwordPara ( VOS_UINT8  ucIndex );
extern VOS_UINT32   AT_SetDislogPara ( VOS_UINT8 ucIndex );
#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
extern VOS_UINT32 AT_SetSpwordPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetShellPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryShellPara(VOS_UINT8 ucIndex);

#endif
 /* Add by c00172979 for V7代码同步, 2012-04-07, Begin   */
#if (FEATURE_ON==FEATURE_LTE)
 /* Modify by c00172979 for V7代码同步, 2012-04-07, End   */

extern VOS_UINT32 AT_SetRsrpCfgPara ( VOS_UINT8 ucIndex );
extern VOS_UINT32  AT_QryRsrpCfgPara ( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_SetRscpCfgPara ( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_SetEcioCfgPara ( VOS_UINT8 ucIndex );
extern VOS_UINT32  AT_QryRscpCfgPara ( VOS_UINT8 ucIndex );
extern VOS_UINT32  AT_QryEcioCfgPara ( VOS_UINT8 ucIndex );
/* 删除AT_QryCellRoamPara */

extern VOS_UINT32 AT_SetPdprofmodPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryPdprofmodPara(VOS_UINT8 ucIndex);


/*DTS2012041801532 w00182550 NV归一化 start in 2012-04-12 */
extern VOS_UINT32 AT_SetExbandInfoPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetExbandTestInfoPara(VOS_UINT8 ucIndex);
/*DTS2012041801532 w00182550 NV归一化 end in 2012-04-12 */

#endif
extern VOS_UINT32   AT_SetApbatlvlPara( VOS_UINT8 ucIndex );
#if (FEATURE_ON == FEATURE_LTE)
extern  VOS_UINT32 AT_SetCeregPara(VOS_UINT8 ucIndex);
extern  VOS_UINT32 At_QryCeregPara(VOS_UINT8 ucIndex);
#endif
extern VOS_UINT32 AT_SetOpenportPara( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_SetSdloadPara(VOS_UINT8 ucIndex);

extern TAF_UINT32   At_QryS0Para(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryS3Para(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryS4Para(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryS5Para(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryS6Para(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryS7Para(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCmgfPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCcnmaPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryClipPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryColpPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryClirPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCusdPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCcwaPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCpinPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryIccidPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryPNNPara (TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCPNNPara (TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryOPLPara (TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCpin2Para(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCpinStatus(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCardlockPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCardATRPara(TAF_UINT8 ucIndex);

VOS_UINT32 At_SetUsimStub(VOS_UINT8 ucIndex);
VOS_UINT32 At_SetRefreshStub(VOS_UINT8 ucIndex);
VOS_UINT32 At_SetAutoReselStub(VOS_UINT8 ucIndex);

/* Modified by c00318887 for file refresh需要触发背景搜, 2015-3-31, begin */
#if ( VOS_WIN32 == VOS_OS_VER )
VOS_UINT32 At_SetDelayBgStub(VOS_UINT8 ucIndex);
#endif
/* Modified by c00318887 for file refresh需要触发背景搜, 2015-3-31, end */
extern TAF_UINT32   At_QryCpbsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCfunPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCpamPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCgclassPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCopsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCgcattPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCgattPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_QryCgautoPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_QryCgtftPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_QryCgactPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_QryCgdcontPara(VOS_UINT8 ucIndex);
extern TAF_UINT32   AT_QryCgeqreqPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCgeqminPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_QryCgdscontPara(VOS_UINT8 ucIndex);
extern TAF_UINT32   At_QryCrcPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCbstPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCmodPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCstaPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCcugPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCssnPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCscaPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCsmsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCsmpPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCpmsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCgsmsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCgregPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCregPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCsdhPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_QryMaxFreelockSizePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QryLcStartTimePara(VOS_UINT8 ucIndex);
extern TAF_UINT32   At_QryCnmiPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCscsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCmeePara(TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_QryCgdnsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryFrqPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryFPlmnPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryDialModePara(TAF_UINT8 ucIndex);
/* ==>l00107747 快速开机 */
extern TAF_UINT32   At_QryQuickStart(TAF_UINT8 ucIndex);
/* <==l00107747 快速开机 */
extern TAF_UINT32   At_QryAutoAttach(TAF_UINT8 ucIndex);

VOS_UINT32 AT_QrySysCfgExPara(VOS_UINT8 ucIndex);
extern TAF_UINT32   At_QrySysCfgPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryGetportmodePara(TAF_UINT8 ucIndex);
extern VOS_UINT32   At_QryVMSETPara(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_QryClvlPara(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_QryCvoicePara (VOS_UINT8 ucIndex);
extern VOS_UINT32   At_QryDdsetexPara(VOS_UINT8 ucIndex);
extern TAF_UINT32   At_QryCmsrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryUssdModePara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryAdcTempPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCommDebugPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryDwinsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryYjcxPara(TAF_UINT8 ucIndex);
extern VOS_UINT32   At_QryCplsPara(VOS_UINT8 ucIndex);
extern TAF_UINT32   At_QryCpolPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryNdisdupPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_QryAuthdataPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCrpnPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_QryNdisStatPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryNdisConnPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryRxDiv(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_QryCallSrvPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QryCsdfltPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_OutputCsdfltDefault(
    VOS_UINT8                           ucIndex,
    VOS_BOOL                            bSimlockEnableFlg
);

extern VOS_UINT32 At_QryFrssiPara(VOS_UINT8 ucIndex);
extern VOS_UINT32  At_QryFpaPara(VOS_UINT8 ucIndex);
extern VOS_UINT32  At_QryFlnaPara(VOS_UINT8 ucIndex);
extern VOS_UINT32  At_QryFRxonPara(VOS_UINT8 ucIndex);
extern TAF_UINT32   AT_QryAlsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_SetAlsPara(TAF_UINT8 ucIndex);
/*新增的AT命令查询函数*/
extern TAF_UINT32   At_QryRRCVersion(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryCSNR(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_QryFreqLock(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryGlastErrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetIccidPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetPNNPara (TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCPNNPara (TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetOPLPara (TAF_UINT8 ucIndex);
extern TAF_UINT32   AT_SetCgeqnegPara( TAF_UINT8 ucIndex);

extern TAF_UINT32   At_ReadNumTypePara(TAF_UINT8 *pucDst,TAF_UINT8 *pucSrc);

extern TAF_UINT32   At_ChgMnErrCodeToAt(TAF_UINT8 ucIndex,TAF_UINT32 ulMnErrorCode);
/*->f62575*/
extern TAF_UINT32   At_PrintListMsg(
    VOS_UINT8                            ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent,
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo,
    TAF_UINT8                           *pucDst
);

extern TAF_VOID     At_PrintCsmsInfo(
    TAF_UINT8                           ucIndex
);

extern MN_OPERATION_ID_T  At_GetOpId(
    VOS_VOID
);

extern TAF_VOID     At_HandleSmtBuffer(
    VOS_UINT8                           ucIndex,
    AT_CNMI_BFR_TYPE                    ucBfrType
);

extern TAF_UINT16   At_PrintAsciiAddr(
    MN_MSG_ASCII_ADDR_STRU              *pstAddr,
    TAF_UINT8                           *pDst
);

extern TAF_UINT32   At_GetScaFromInputStr(
    const TAF_UINT8                     *pucAddr,
    MN_MSG_BCD_ADDR_STRU                *pstBcdAddr,
    TAF_UINT32                          *pulLen
);

extern MN_MSG_TS_DATA_INFO_STRU * At_GetMsgMem(
    VOS_VOID
);

extern TAF_UINT16   At_PrintMsgFo(
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo,
    TAF_UINT8                           *pDst
);

extern TAF_UINT16   At_PrintAddrType(
    MN_MSG_ASCII_ADDR_STRU              *pstAddr,
    TAF_UINT8                           *pDst
);

extern TAF_UINT32   At_SetNumTypePara(
    TAF_UINT8                           *pucDst,
    TAF_UINT8                           *pucSrc,
    TAF_UINT16                          usSrcLen
);

extern VOS_VOID AT_PhSendRestoreFactParm( VOS_VOID );

extern TAF_UINT32   At_GetAsciiOrBcdAddr(
    TAF_UINT8                           *pucAddr,
    TAF_UINT16                          usAddrLen,
    TAF_UINT8                           ucAddrType,
    TAF_UINT16                          usNumTypeLen,
    MN_MSG_ASCII_ADDR_STRU              *pstAsciiAddr,
    MN_MSG_BCD_ADDR_STRU                *pstBcdAddr
);

extern TAF_VOID     At_SmsModSmStatusRspProc(
        TAF_UINT8                           ucIndex,
        MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern TAF_VOID     At_SmsInitResultProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pEvent
);

extern VOS_VOID     At_SmsDeliverErrProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern VOS_VOID     At_SmsInitSmspResultProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern VOS_VOID     At_SmsSrvParmChangeProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern VOS_VOID     At_SmsRcvMsgPathChangeProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern VOS_VOID     At_SmsStorageListProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern VOS_VOID     At_SmsStorageExceedProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern TAF_VOID     At_PrintSetCpmsRsp(
    TAF_UINT8                           ucIndex
);

extern TAF_VOID At_ZeroReplaceBlankInString(
    VOS_UINT8                           *pData,
    VOS_UINT32                           ulLen
);

extern VOS_UINT32  AT_PhyNumIsNull(
    MODEM_ID_ENUM_UINT16                enModemId,
    AT_PHYNUM_TYPE_ENUM_UINT32           enSetType,
    VOS_BOOL                            *pbPhyNumIsNull
);

extern TAF_UINT16   At_PrintBcdAddr(
    MN_MSG_BCD_ADDR_STRU                *pstBcdAddr,
    TAF_UINT8                           *pDst
);

extern VOS_VOID     At_PrintGetCpmsRsp(
    VOS_UINT8                           ucIndex
);

extern TAF_UINT32   At_CheckNumLen(
    TAF_UINT16                          usMax,
    TAF_UINT16                          usLen
);

extern TAF_UINT32  At_CheckUssdNumLen(
    VOS_UINT8                           ucIndex,
    TAF_SS_DATA_CODING_SCHEME           dcs,
    TAF_UINT16                          usLen
);

extern TAF_UINT32   At_SmsPrintScts(
    const MN_MSG_TIMESTAMP_STRU         *pstTimeStamp,
    TAF_UINT8                           *pDst
);

extern TAF_UINT16   At_MsgPrintVp(
    MN_MSG_VALID_PERIOD_STRU            *pstValidPeriod,
    TAF_UINT8 *pDst
);

extern TAF_UINT32   At_SmsPrintState(
    AT_CMGF_MSG_FORMAT_ENUM_U8          enSmsFormat,
    MN_MSG_STATUS_TYPE_ENUM_U8          enStatus,
    TAF_UINT8                           *pDst
);

extern MN_MSG_SEND_ACK_PARM_STRU * At_GetAckMsgMem(
    VOS_VOID
);

extern TAF_VOID     At_MsgResultCodeFormat(
    TAF_UINT8                           ucIndex,
    TAF_UINT16                          usLength
);

extern VOS_VOID     At_SmsDeliverProc(
        TAF_UINT8                           ucIndex,
        MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern TAF_VOID     At_SetRcvPathRspProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern TAF_VOID     At_SetCscaCsmpRspProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

/* Added by f62575 for AT Project，2011-10-03,  Begin */

extern VOS_UINT32 AT_TestSetPort(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_TestRstriggerPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_TestStsfPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_TestCpnnPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_TestOplPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_TestPnnPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_TestStgiPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_TestStgrPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_TestImsichgPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_TestSsidPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_TestWikeyPara(VOS_UINT8 ucIndex);

extern VOS_UINT32  AT_SetDissdCmd(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetSdrebootCmd(VOS_UINT8 ucIndex);

extern TAF_VOID     At_DeleteTestRspProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern TAF_VOID     At_ReadRspProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern TAF_VOID     At_ListRspProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern TAF_VOID     At_WriteSmRspProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern TAF_VOID  At_DeleteRspProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern TAF_VOID     At_SetCnmaRspProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern TAF_VOID     At_SendSmRspProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern TAF_UINT32   At_CheckDigit( TAF_UINT8 Char );
extern TAF_UINT32   At_CheckColon( TAF_UINT8 Char );

extern TAF_UINT32   At_SetCmStubPara(TAF_UINT8 ucIndex);

extern TAF_UINT32   At_SetCmmsPara(
    TAF_UINT8                           ucIndex
);

extern TAF_UINT32   At_QryCmmsPara(
    TAF_UINT8                           ucIndex
);

extern TAF_VOID     At_SetCmmsRspProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern TAF_VOID     At_GetCmmsRspProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern VOS_VOID AT_QryCscaRspProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU             *pstEvent
);

extern VOS_VOID At_SmsStubRspProc(
    VOS_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU             *pstEvent
);

extern TAF_VOID     At_SmsRspNop(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);
extern TAF_UINT32   At_MsgDeleteCmdProc(
    TAF_UINT8                           ucIndex,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_DELETE_PARAM_STRU            stDelete,
    TAF_UINT32                          ulDeleteTypes
);

extern VOS_UINT32 At_GetSmsStorage(
    VOS_UINT8                           ucIndex,
    MN_MSG_MEM_STORE_ENUM_U8            enMemReadorDelete,
    MN_MSG_MEM_STORE_ENUM_U8            enMemSendorWrite,
    MN_MSG_MEM_STORE_ENUM_U8            enMemRcv
);

extern VOS_VOID At_QryParaRspCopsProc(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           OpId,
    VOS_VOID                            *pPara
);



extern TAF_VOID     At_QryParaRspSysinfoProc(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           OpId,
    TAF_VOID                            *pPara
);

extern VOS_VOID  AT_QryParaRspSysinfoExProc(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           OpId,
    VOS_VOID                           *pPara
);

extern TAF_VOID     At_QryParaRspCimiProc(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           OpId,
    TAF_VOID                            *pPara
);

extern TAF_VOID     At_QryParaRspCgclassProc(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           OpId,
    TAF_VOID                            *pPara
);

extern VOS_VOID     At_QryParaRspCregProc(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           OpId,
    VOS_VOID                            *pPara
);

extern VOS_VOID     At_QryParaRspCgregProc(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           OpId,
    VOS_VOID                            *pPara
);


extern TAF_VOID     At_QryParaRspIccidProc(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           OpId,
    TAF_VOID                            *pPara
);

extern TAF_VOID     At_QryParaRspPnnProc(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           OpId,
    TAF_VOID                            *pPara
);
extern TAF_VOID     At_QryParaRspCPnnProc(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           OpId,
    TAF_VOID                            *pPara
);

/* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
#if(FEATURE_ON == FEATURE_LTE)

TAF_VOID At_QryParaRspCellRoamProc(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           OpId,
    TAF_VOID                            *pPara
);
#endif
/* Add by w00199382 for V7代码同步, 2012-04-07, End   */

extern TAF_VOID     At_QryParaRspOplProc(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           OpId,
    TAF_VOID                            *pPara
);

extern TAF_VOID     At_QryParaRspCfplmnProc(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           OpId,
    TAF_VOID                            *pPara
);



/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
extern TAF_VOID     At_QryParaRspCgdnsProc(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           OpId,
    TAF_VOID                            *pPara
);

extern TAF_VOID     At_QryParaRspAuthdataProc(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           OpId,
    TAF_VOID                            *pPara
);

extern TAF_VOID     At_QryRspUsimRangeProc(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           OpId,
    TAF_VOID                            *pPara
);
extern TAF_UINT32 At_QryNdisAddPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryDnsPrim(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryDnsSnd(VOS_UINT8 ucIndex);
extern TAF_UINT32 AT_QryDloadVerPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 AT_QryDloadInfoPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 AT_QryAuthorityIdPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryAuthorityVerPara( VOS_UINT8 ucIndex );
extern TAF_UINT32 AT_QryNvRststtsPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 AT_QryFlashInfoPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryAuthverPara(VOS_UINT8 ucIndex);

#if (FEATURE_ON == FEATURE_IPV6)
extern VOS_UINT32 AT_TestIpv6capPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryIpv6CapPara(VOS_UINT8 ucIndex);
#endif
extern VOS_UINT32 At_DialNumByIndexFromPb(VOS_UINT8  ucIndex,SI_PB_EVENT_INFO_STRU  *pEvent);
extern TAF_UINT32   At_PbReadCnfProc(VOS_UINT8 ucIndex,SI_PB_EVENT_INFO_STRU  *pEvent);

extern TAF_UINT32   At_PbCPBRCmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,TAF_UINT8 *pucData,SI_PB_EVENT_INFO_STRU *pEvent);

extern TAF_UINT32   At_PbCPBR2CmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,TAF_UINT8 *pucData,SI_PB_EVENT_INFO_STRU *pEvent);

extern TAF_UINT32   At_PbCNUMCmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,TAF_UINT8 *pucData,SI_PB_EVENT_INFO_STRU *pEvent);

extern TAF_UINT32   At_PbSCPBRCmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,SI_PB_EVENT_INFO_STRU *pEvent);

extern TAF_VOID     At_PbSearchCnfProc(VOS_UINT8 ucIndex,SI_PB_EVENT_INFO_STRU  *pEvent);


extern  TAF_VOID    At_CombineCmdStruInit(VOS_VOID);
extern  TAF_VOID    At_ResetCombineCmdStru(TAF_UINT8    ucIndex);
extern  TAF_UINT32  At_FormatCmdStr ( TAF_UINT8 *pData, TAF_UINT16 *pLen);
extern  TAF_UINT32  At_ScanDelChar( TAF_UINT8 *pData, TAF_UINT16 *pLen);
extern  TAF_UINT32  At_ScanCtlChar( TAF_UINT8 *pData, TAF_UINT16 *pLen);
extern  TAF_UINT32  At_ScanQuoteChar( TAF_UINT8 *pData, TAF_UINT16 *pLen);
extern  TAF_UINT32  At_ScanBlankChar( TAF_UINT8 *pData, TAF_UINT16 *pLen);
/*extern  TAF_UINT32  At_ScanLowerChar(TAF_UINT8* pData, TAF_UINT16 usLen); */
extern  TAF_UINT32  At_ScanSemicolonChar( TAF_UINT8 *pData,
                                           TAF_UINT16 usLen,
                                           AT_COMBINE_CMD_SEMICOLON_PARSE_STRU *pstComCmdSCParse);
extern  TAF_UINT32  At_CheckCharA( TAF_UINT8 Char );
extern  TAF_UINT32  At_CheckCharT( TAF_UINT8 Char );
extern  VOS_UINT32  At_CmdDataPreProc(
    VOS_UINT8                               *pData,
    VOS_UINT16                              *pusCmdLen
);
/*extern TAF_VOID     At_CmdMsgPreProc(TAF_UINT8 ucIndex, TAF_UINT8* pData, TAF_UINT16 usLen); */
/*extern VOS_UINT32   At_HoldAtCmd (VOS_UINT8   ucIndex, VOS_UINT8   *pData, VOS_UINT16  usLen); */
extern VOS_UINT32   At_FindPendAtChannelOrSmsEditMode(AT_USER_TYPE UserType);



#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

#define AT_MAX_CBS_MSGID_NUM            50

extern TAF_UINT32   At_QryCscbPara(
    TAF_UINT8                           ucIndex
);

extern TAF_UINT32 At_SetCscbPara(
    TAF_UINT8                           ucIndex
);

extern VOS_VOID At_SmsDeliverCbmProc(
        TAF_UINT8                           ucIndex,
        MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern VOS_VOID At_GetCbActiveMidsRspProc(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

extern VOS_VOID AT_ChangeCbMidsRsp(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);


#if (FEATURE_ON == FEATURE_ETWS)
VOS_VOID  At_ProcDeliverEtwsPrimNotify(
    VOS_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU             *pstEvent
);
#endif  /* (FEATURE_ON == FEATURE_ETWS) */


#endif

/*<-f62575*/
extern TAF_UINT32   Ppp_ReleasePppReq ( TAF_UINT16 usPppId);
extern TAF_UINT8    Cca_CurState(VOS_VOID);
extern TAF_VOID     SysCtrl_RFLdoDown(VOS_VOID);

extern TAF_UINT32   At_SetCdtmfsPara(
    TAF_UINT8                           ucIndex
);
extern TAF_UINT32   At_SetCdtmfePara(
    TAF_UINT8                           ucIndex
);

extern VOS_INT      UdiagValueCheck(VOS_UINT32 DiagValue);
extern VOS_UINT32   GetU2diagDefaultValue(VOS_VOID);
extern VOS_VOID     MMA_CardType(VOS_CHAR *pcDest);
TAF_UINT32          At_GetBandPara(TAF_UINT8 *nptr,TAF_UINT16 usLen,TAF_USER_SET_PREF_BAND64 * pStBand);

/*为了规避Linux后台二次拨号失败问题，需采取规避方案，规避方案中，底软需新增一个判断是否
  为LINUX操作系统的API*/
extern VOS_INT      GetLinuxSysType(VOS_VOID);

extern VOS_VOID     CheckCurrentModemStatus(VOS_INT status);

extern TAF_VOID     AT_StubTriggerAutoReply(
    VOS_UINT8                           ucIndex,
    TAF_UINT8                           ucCfgValue
);

extern TAF_VOID     AT_StubSaveAutoReplyData(
    VOS_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent,
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo
);

extern TAF_UINT32   AT_StubSendAutoReplyMsg(
    VOS_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent,
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo
);
extern VOS_UINT32 AT_SetCsqlvlExtPara(VOS_UINT8 ucIndex);




VOS_VOID AT_CsUus1InfoEvtIndProc(
    VOS_UINT8                           ucIndex,
    MN_CALL_EVENT_ENUM_U32              enEvent,
    MN_CALL_INFO_STRU                   *pstCallInfo
);

#if ( VOS_WIN32 == VOS_OS_VER )
extern VOS_VOID     USIMM_SendSMSDataInd1(VOS_VOID);
extern VOS_VOID     USIMM_SendSMSDataInd2(VOS_VOID);
extern VOS_VOID     MN_MSG_SetClass0Tailor(MN_MSG_CLASS0_TAILOR_U8                 enClass0Tailor);
#endif

extern VOS_UINT32   MMA_PhoneFindNtwkNameByPlmnId( TAF_PH_OPERATOR_NAME_STRU   *pstOperName);
extern VOS_UINT32   MMA_PhoneGetAllOperNumByLongNameFromOperTbl( TAF_PH_OPERATOR_NAME_STRU   *pstOperName,
                                                                                        VOS_UINT8 *pucMaxMncLen);
extern VOS_UINT32   MMA_PhoneGetAllOperNumByShortNameFromOperTbl( TAF_PH_OPERATOR_NAME_STRU   *pstOperName,
                                                                                        VOS_UINT8 *pucMaxMncLen);
extern VOS_VOID   MMA_PhoneGetAllOperInfoByLongNameFromOperTbl( TAF_PH_OPERATOR_NAME_STRU   *pstOrigOperName,
                                                                                       TAF_PH_OPERATOR_NAME_STRU   *pstOperName);
extern VOS_VOID   MMA_PhoneGetAllOperInfoByShortNameFromOperTbl( TAF_PH_OPERATOR_NAME_STRU   *pstOrigOperName,
                                                                                      TAF_PH_OPERATOR_NAME_STRU   *pstOperName);

extern VOS_BOOL AT_PH_IsPlmnValid(TAF_PLMN_ID_STRU *pstPlmnId);
extern VOS_BOOL MN_PH_IsUsingPlmnSel(VOS_VOID);


extern VOS_UINT32   AT_SetCccPara( TAF_UINT8 ucIndex );

/***All the following function are defined in AtSetParaCmd.c***/
extern TAF_UINT32 AT_SetRstriggerPara(
        TAF_UINT8                           ucIndex
);

/***All the following function are defined in AtQueryParaCmd.c***/
extern TAF_UINT32 AT_QryRstriggerPara(
    TAF_UINT8                           ucIndex
);

extern VOS_UINT32 At_QryApHplmn(VOS_UINT8  ucIndex);
extern VOS_UINT32 AT_QryAnQuery( VOS_UINT8 ucIndex );


/***All the following function are defined in MnMsgSmsProc.c***/
extern VOS_UINT32 AT_ReadActiveMessage(
        MODEM_ID_ENUM_UINT16                enModemId,
        MN_MSG_ACTIVE_MESSAGE_STRU         *pstActiveMessage
);

extern VOS_UINT32 AT_WriteActiveMessage(
    MODEM_ID_ENUM_UINT16                enModemId,
    MN_MSG_ACTIVE_MESSAGE_STRU         *pstOrgActiveMessageInfo,
    MN_MSG_ACTIVE_MESSAGE_STRU         *pstActiveMessageInfo
);
extern VOS_VOID At_BufferorSendResultData(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLength
);

extern TAF_UINT32 At_PrintMmTimeInfo(
    VOS_UINT8                           ucIndex,
    TAF_MMA_TIME_CHANGE_IND_STRU       *pMsg,
    TAF_UINT8                          *pDst
);

extern  TAF_UINT32  At_PrintTimeZoneInfo(
    NAS_MM_INFO_IND_STRU                *pstMmInfo,
    TAF_UINT8                           *pDst
);

/*****************************************************************************
 函 数 名  : AT_PrintTimeZoneInfoNoAdjustment
 功能描述  : 显示当前时区信息(网络时区信息)
 输入参数  : pstMmInfo - MM INFO结构指针
             pDst      - 显示数据地址
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_PrintTimeZoneInfoNoAdjustment(
    NAS_MM_INFO_IND_STRU               *pstMmInfo,
    VOS_UINT8                          *pucDst
);

VOS_UINT32 AT_PrintTimeZoneInfoWithCtzeType(
    TAF_MMA_TIME_CHANGE_IND_STRU       *pstMmInfo,
    VOS_UINT8                          *pucDst
);
extern  TAF_VOID    At_PhIndProc(
    TAF_UINT8                           ucIndex,
    TAF_PHONE_EVENT_INFO_STRU           *pEvent
);

extern  VOS_UINT32 MN_PH_QryApHplmn(
    VOS_UINT32                          *pulMcc,
    VOS_UINT32                          *pulMnc
);

extern VOS_UINT32 MN_PH_QryAnQuery(
    VOS_INT16                           *psCpichRscp,
    VOS_INT16                           *psCpichEcNo,
    VOS_UINT8                           *pucRssi,
    VOS_UINT32                          *pulCellId
);
extern AT_CMD_ANTENNA_LEVEL_ENUM_UINT8 AT_CalculateAntennaLevel(
    VOS_INT16                           sRscp,
    VOS_INT16                           sEcio
);
#if (FEATURE_ON == FEATURE_LTE)
extern VOS_UINT8 AT_CalculateLTEAntennaLevel(
    VOS_INT16 usRsrp
);

extern TAF_VOID AT_CalculateLTESignalValue(
    VOS_INT16    *psRssi,
    VOS_UINT8    *pusLevel,
    VOS_INT16    *pusRsrp,
    VOS_INT16    *pusRsrq
);
#endif

extern VOS_UINT8 AT_GetSmoothLTEAntennaLevel(
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enLevel
);

extern VOS_VOID AT_GetSmoothAntennaLevel(
           VOS_UINT8                           ucIndex,
           AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enLevel );
extern VOS_UINT32  At_QryAppWronReg( VOS_UINT8 ucIndex );

extern  VOS_UINT32 At_SetCuus1Para(
    VOS_UINT8                           ucIndex
);

extern  VOS_UINT32 At_QryCuus1Para(
    VOS_UINT8                           ucIndex
);

VOS_VOID AT_GetOnlyGURatOrder(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
);
VOS_VOID AT_GetRatOrderNvim(
    MODEM_ID_ENUM_UINT16                enModemId,
    TAF_MMA_RAT_ORDER_STRU             *pstSysCfgRatOrder,
    VOS_UINT8                           ucUserSptLteFlag
);
VOS_UINT32 AT_ConvertSysCfgExBandPara(
    VOS_UINT8                          *pucPara,
    VOS_UINT16                          usLen,
    TAF_USER_SET_PREF_BAND64           *pstPrefBandPara
);

VOS_UINT32 At_CheckSysCfgExRatTypeValid(
    VOS_UINT8                           ucRatOrder
);
VOS_UINT32 At_CheckRepeatedRatOrder(
    AT_SYSCFGEX_RAT_ORDER_STRU         *pstSyscfgExRatOrder
);

TAF_VOID At_ResetGlobalVariable( VOS_VOID);




VOS_VOID AT_GetGuAccessPrioNvim (
    MODEM_ID_ENUM_UINT16                enModemId,
    AT_SYSCFG_RAT_PRIO_ENUM_UINT8      *penAcqorder
);

extern VOS_UINT32 AT_ParseSetDockCmd(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
);

extern VOS_UINT32 AT_HandleDockSetCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
);

extern VOS_UINT32 AT_DockHandleCmd(
        VOS_UINT8                       ucIndex,
        VOS_UINT8                      *pucData,
        VOS_UINT16                      usLen
);

extern VOS_BOOL AT_CheckDockName(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
);
/*****************************************************************************
 函 数 名  : AT_GetRateDisplayIndexForGsm
 功能描述  : 获取GSM模式下行能力等级在速率显示表中的索引
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_GetRateDisplayIndexForGsm(
    TAF_AGENT_SYS_MODE_STRU            *pstSysMode
);

/*****************************************************************************
 函 数 名  : AT_GetRateDisplayIndexForWcdma
 功能描述  : 获取WCDMA模式下行能力等级在速率显示表中的索引
 输入参数  : pstDlRateCategory - UE下行能力
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_GetRateDisplayIndexForWcdma(
    AT_DOWNLINK_RATE_CATEGORY_STRU     *pstDlRateCategory
);

#if(FEATURE_ON == FEATURE_LTE)
VOS_UINT32 AT_GetRateDisplayIndexForLTE(
    AT_DOWNLINK_RATE_CATEGORY_STRU     *pstDlRateCategory
);
#endif

VOS_VOID At_SendMsgFoAttr(
    VOS_UINT8                           ucIndex,
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo
);

VOS_VOID AT_SetDefaultRatPrioList(
    MODEM_ID_ENUM_UINT16                enModemId,
    TAF_MMA_RAT_ORDER_STRU             *pstSysCfgRatOrder,
    VOS_UINT8                           ucUserSptLteFlag
);

extern VOS_VOID  AT_QryParaAnQueryProc(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           OpId,
    VOS_VOID                           *pPara
);

extern VOS_VOID  AT_QryParaHomePlmnProc(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           OpId,
    VOS_VOID                           *pPara
);


extern VOS_UINT32 AT_SetFwavePara(
    VOS_UINT8 ucIndex
);



/* Modified by w00167002 for L-C互操作项目, 2014-2-21, begin */
VOS_UINT32 AT_RcvSimLockQryRsp(VOS_VOID *pMsg);
/* Modified by w00167002 for L-C互操作项目, 2014-2-21, end */


extern VOS_UINT32 OM_AcpuTraceMsgHook(VOS_VOID *pMsg);

VOS_VOID AT_ShowCccRst(
    NAS_CC_STATE_INFO_STRU              *pstCcState,
    VOS_UINT16                          *pusLength
);



VOS_UINT32 AT_RcvDrvAgentAuthVerQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentGodloadSetRsp(VOS_VOID *pMsg);



VOS_VOID AT_RcvCdurQryRsp(
    VOS_UINT8                           ucIndex,
    MN_CALL_EVENT_ENUM_U32              enEvent,
    MN_CALL_INFO_STRU                   *pstCallInfo
);

VOS_UINT32 AT_RcvDrvAgentAppdmverQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentDloadverQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentDloadInfoQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentFlashInfoQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentAuthorityVerQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentAuthorityIdQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentUsimWriteStubSetRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentPfverQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentHwnatQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentSdloadSetRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentImsiChgQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentInfoRbuSetRsp(VOS_VOID *pMsg);
/* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
#if(FEATURE_ON == FEATURE_LTE)
VOS_UINT32 AT_RcvDrvAgentInfoRrsSetRsp(VOS_VOID *pMsg);
#endif
/* Add by w00199382 for V7代码同步, 2012-04-07, End   */


VOS_UINT32 AT_RcvDrvAgentCpnnQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentCpnnTestRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentNvBackupSetRsp(VOS_VOID *pMsg);

VOS_VOID AT_EventReport(
    VOS_UINT32                          ulPid,
    NAS_OM_EVENT_ID_ENUM_UINT16         enEventId,
    VOS_VOID                           *pPara,
    VOS_UINT32                          ulLen
);

/* Added by 傅映君/f62575 for CPULOAD&MFREELOCKSIZE处理过程移至C核, 2011/11/15, begin */
VOS_UINT32 AT_RcvDrvAgentCpuloadQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentMfreelocksizeQryRsp(VOS_VOID *pMsg);
/* Added by 傅映君/f62575 for CPULOAD&MFREELOCKSIZE处理过程移至C核, 2011/11/15, end */


VOS_UINT32 AT_RcvDrvAgentMemInfoQryRsp(VOS_VOID *pMsg);
VOS_UINT32 At_TestTmodePara(VOS_UINT8 ucIndex);

VOS_UINT32 At_TestFdacPara(VOS_UINT8 ucIndex);

/* 此函数在 AtCmdMsgProc.c 中 */
VOS_UINT32 AT_SetGlobalFchan(VOS_UINT8 ucRatMode);

VOS_UINT32 AT_ProcTestError(VOS_UINT8 ucIndex);




/*装备快速校准c00172979 20110730 start */
extern VOS_UINT32 atSetTmodePara(VOS_UINT8 ucClientId, VOS_UINT32 usTmode);
extern VOS_UINT32 atSetTmodeParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetBandSWPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetBandSWParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryBandSWPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryBandSWParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetFFCHANSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFFCHANSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFFCHANSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFFCHANSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetFFSEGMENTPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFFSEGMENTParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFFSEGMENTPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFFSEGMENTParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetFFPOWSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFFPOWSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFFPOWSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFFPOWSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetFFPASPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFFPASParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFFPASPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFFPASParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetFFLNASPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFFLNASParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFFLNASPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFFLNASParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetFFTXWAVEPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFFTXWAVEParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFFTXWAVEPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFFTXWAVEParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetFFSTARTPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFFSTARTParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFFSTARTPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFFSTARTParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetFFRSSISPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFFRSSISParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetFFCMTMSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFFCMTMSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetFMAXPOWERPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFMAXPOWERParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFMAXPOWERPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFMAXPOWERParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetFPAPOWERPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFPAPOWERParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFPAPOWERPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFPAPOWERParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetFBLKPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFBLKParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFBLKPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFBLKParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetFIPSTARTPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFIPSTARTParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

/* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
#if(FEATURE_ON == FEATURE_LTE)
extern VOS_UINT32 atSetFPDMSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFPDMSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFPDMSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFPDMSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

/*装备快速校准c00172979 20110730 end */
extern VOS_UINT32 atSetFCHANPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFCHANParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atQryFCHANPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFCHANParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
#endif
/* Add by w00199382 for V7代码同步, 2012-04-07, End   */

extern VOS_UINT32 atSetVCTCXOPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetVCTCXOParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryVCTCXOPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryVCTCXOParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetNVRDLenPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetNVRDExPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetNVWRExPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFCALPDDCSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFCALPDDCSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetFCALPDDCSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFCALPDDCSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFPDPOWSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFPDPOWSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetFQPDDCRESPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFQPDDCRESParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 AT_SetNVWRPartPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atSetFTXONPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFTXONParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFTXONPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFTXONParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetFRXONPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFRXONParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFRXONPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFRXONParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetFLNAPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFLNAParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFLNAPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFLNAParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

/*DTS2012041102190 : h00135900 start in 2011-04-11 AT代码融合*/

extern VOS_UINT32 atQryTselrfPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetTselrfPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetTselrfParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
/*DTS2012041102190 : h00135900 end in 2011-04-11 AT代码融合*/

extern VOS_UINT32 atQryFRSSIPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFRSSIParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetBsnPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryBsnPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atSetGpioplPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryGpioplPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atQryRSimPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atQrySfeaturePara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFWAVEPara(VOS_UINT8 ucClientId);


/*非信令综测start */
extern VOS_UINT32 atSetSSYNCPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetSSYNCParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQrySSYNCPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQrySSYNCParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetSTXBWPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetSTXBWParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQrySTXBWPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQrySTXBWParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetSTXCHANPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetSTXCHANParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQrySTXCHANPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQrySTXCHANParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetSSUBFRAMEPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetSSUBFRAMEParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQrySSUBFRAMEPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQrySSUBFRAMEParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetSPARAParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQrySPARAParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetSSEGNUMParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQrySSEGNUMParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetSTXMODUSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQrySTXMODUSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetSTXRBNUMSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQrySTXRBNUMSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetSTXRBPOSSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQrySTXRBPOSSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetSTXPOWSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQrySTXPOWSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetSTXCHANTYPESParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQrySTXCHANTYPESParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetSSEGLENParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQrySSEGLENParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetSRXSETParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQrySRXSETParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetSRXSUBFRAParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQrySRXSUBFRAParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQrySRXBLERParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetSSTARTParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQrySSTARTParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetSSTOPParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetSPARAPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQrySPARAPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atSetSSEGNUMPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQrySSEGNUMPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atSetSTXMODUSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQrySTXMODUSPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atSetSTXRBNUMSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQrySTXRBNUMSPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atSetSTXRBPOSSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQrySTXRBPOSSPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atSetSTXPOWSPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atQrySTXPOWSPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atSetSTXCHANTYPESPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atQrySTXCHANTYPESPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atSetSSEGLENPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atQrySSEGLENPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atSetSRXSETPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atQrySRXSETPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atSetSRXSUBFRAPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atQrySRXSUBFRAPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atQrySRXBLERPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atSetSSTARTPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atQrySSTARTPara(VOS_UINT8 ucClientId);

extern VOS_UINT32 atSetSSTOPPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetSTCFGDPCHPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetSTCFGDPCHParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atSetFPOWPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFPOWParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQrySTRXBERPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQrySTRXBERParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);



/*一键式升级-c00172979 start */
extern VOS_UINT32 atQryDLoadVer(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryDLoadVerCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atQryDLoadInfo(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryDLoadInfoCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atQryAuthorityVer(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryAuthorityVerCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atQryAuthorityID(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryAuthorityIDCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetNVBackup(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetNVBackupCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetNVRestore(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetNVRestoreCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetGodLoad(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetGodLoadCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetReset(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetResetCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetNVRstSTTS(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetNVRstSTTSCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetTBATPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetTbatCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atRdTbatCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32  AT_SetLteSdloadPara(VOS_UINT8 ucClientId);

/*一键式升级-c00172979 end */

extern VOS_UINT32 AT_ParseSetAnyStrCmd(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
);

extern VOS_UINT32 AT_HandleAnyStrSetCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
);


extern VOS_UINT32 AT_HandleFacAuthPubKeyCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
);

extern VOS_UINT32 AT_HandleSimLockDataWriteCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucData,
    VOS_UINT16                          usLen
);

extern VOS_UINT32 At_HandleApModemSpecialCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
);

extern VOS_UINT32 AT_SetApRptSrvUrlPara(
    VOS_UINT8 ucIndex
);

extern VOS_UINT32 AT_SetApXmlInfoTypePara(
    VOS_UINT8 ucIndex
);

extern VOS_UINT32 AT_SetApXmlRptFlagPara(
    VOS_UINT8 ucIndex
);

extern VOS_UINT32 AT_QryApRptSrvUrlPara(
    VOS_UINT8 ucIndex
);

extern VOS_UINT32 AT_QryApXmlInfoTypePara(
    VOS_UINT8 ucIndex
);

extern VOS_UINT32 AT_QryApXmlRptFlagPara(
    VOS_UINT8 ucIndex
);
extern VOS_UINT32 AT_QryEqverPara(
    VOS_UINT8                           ucIndex
);

extern VOS_UINT32 AT_SetProdNamePara(
    VOS_UINT8 ucIndex
);

extern VOS_UINT32 AT_QryProdNamePara(
    VOS_UINT8                           ucIndex
);



extern VOS_UINT32 AT_QryCipherPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryLocinfoPara(VOS_UINT8 ucIndex);
/* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
extern VOS_UINT32 AT_QryAcInfoPara(VOS_UINT8 ucIndex);
/* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

extern VOS_UINT32 At_SmsProc ( VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen);
extern VOS_VOID AT_DiscardInvalidCharForSms(TAF_UINT8* pData, TAF_UINT16 *pusLen);

extern VOS_UINT32 At_TestCmlckPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestCpasPara(VOS_UINT8 ucIndex);


VOS_UINT32 AT_TestSyscfg(VOS_UINT8 ucIndex);
VOS_UINT32 AT_TestSyscfgEx(VOS_UINT8 ucIndex);
VOS_VOID AT_ClacCmdProc(VOS_VOID);
VOS_VOID At_CovertMsInternalRxDivParaToUserSet2(
    VOS_UINT16                          usCurBandSwitch,
    VOS_UINT32                         *pulUserDivBandsLow,
    VOS_UINT32                         *pulUserDivBandsHigh
);
VOS_UINT32 AT_GetOperatorNameFromParam(
    VOS_UINT16                         *usOperNameLen,
    VOS_CHAR                           *pucOperName,
    VOS_UINT16                          usBufSize,
    VOS_UINT32                          ulFormatType
);


/* Added by L60609 for AT Project，2011-10-21,  Begin*/
extern VOS_UINT32 At_RegisterBasicCmdTable(VOS_VOID);
extern VOS_UINT32 At_RegisterExCmdTable(VOS_VOID);
extern VOS_UINT32 At_RegisterDeviceCmdTable(VOS_VOID);
extern VOS_UINT32 At_RegisterDeviceCmdTLTable(VOS_VOID);
extern VOS_UINT32 At_RegisterExPrivateCmdTable(VOS_VOID);

extern VOS_VOID At_InitUsimStatus(VOS_VOID);

/* 接收L4A的CNF，IND消息，并查找对应函数进行处理 */
VOS_UINT32 at_L4aCnfProc(MsgBlock* pMsgBlockTmp);

/* AT处理LTE装备FTM回复消息入口 */
VOS_UINT32 At_FtmEventMsgProc(VOS_VOID *pMsg);

VOS_UINT32 At_TestCgatt(VOS_UINT8 ucIndex);

VOS_UINT32 At_TestNdisAdd(VOS_UINT8 ucIndex);


/* Added by L60609 for AT Project，2011-10-21,  End*/

/* Added by A00165503 for AT Project，2011-10-21, begin */
TAF_UINT32 At_SetDialGprsPara(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           ucCid,
    TAF_GPRS_ACTIVE_TYPE_UINT8          enActiveType
);
/* Added by A00165503 for AT Project，2011-10-21, end */
VOS_UINT32 AT_SetFastDormPara(TAF_UINT8 ucIndex);
VOS_UINT32 AT_QryFastDormPara(TAF_UINT8 ucIndex);
VOS_UINT32 AT_QryAcpuMemInfoPara(TAF_UINT8 ucIndex);
VOS_UINT32 AT_QryCcpuMemInfoPara(TAF_UINT8 ucIndex);

extern VOS_UINT32 AT_SetMemInfoPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 At_ReadCustomizeServiceNV(
    NAS_NVIM_CUSTOMIZE_SERVICE_STRU              *pstCustSrv,
    VOS_UINT16                          *pusValueInfo
);

extern VOS_UINT32 At_ReadGprsActiveTimerLenNV(
    VOS_UINT32                          *pulGprsActiveTimerLen,
    VOS_UINT16                          *pusValueInfo
);



extern VOS_UINT32 AT_QryNvResumePara(VOS_UINT8 ucIndex);

extern VOS_VOID AT_GetSpecificPort(
    VOS_UINT8                           ucPortType,
    VOS_UINT8                           aucRewindPortStyle[],
    VOS_UINT32                         *pulPortPos,
    VOS_UINT32                         *pulPortNum
);
/* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */

extern VOS_UINT32 AT_OpenSpecificPort(VOS_UINT8 ucPort);
extern VOS_UINT32 AT_CloseSpecificPort(VOS_UINT8 ucPort);
/* Add by w00199382 for V7代码同步, 2012-04-07, End   */
VOS_UINT32 AT_QryNvBackupStatusPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryNandBadBlockPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryNandDevInfoPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryChipTempPara(VOS_UINT8 ucIndex);
VOS_VOID AT_SetMemStatusRspProc(
    VOS_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU             *pstEvent
);
VOS_UINT32 AT_SetDnsQueryPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetMemStatusPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetApRptPortSelectPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryApRptPortSelectPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestApRptPortSelectPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetChdataPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryChdataPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestChdataPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetGpioPara (VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestGpioPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetUsbSwitchPara (VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QryUsbSwitchPara (VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestUsbSwitchPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetHsspt(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryHsspt(VOS_UINT8 ucIndex);

extern TAF_UINT32 At_SetScidPara(TAF_UINT8 ucIndex);

extern VOS_UINT32 AT_SetRsfrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestRsfrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetRsfwPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestRsfwPara(VOS_UINT8 ucIndex);
extern VOS_VOID AT_SetRsfrVersionCnf(VOS_UINT8 ucIndex, VOS_UINT8* pucData, VOS_UINT32 ulLen);
extern VOS_UINT32 AT_SpyMsgProc(VOS_VOID* pstMsg);

extern TAF_UINT32 At_PortSwitchSndMsg (TAF_UINT32 ulSwitchMode);
extern VOS_UINT32 AT_QryAntState(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QrySARReduction(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetSARReduction(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetHukPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetFacAuthPubkeyPara(
    VOS_UINT8                           ucIndex,
    AT_FACAUTHPUBKEY_SET_REQ_STRU      *pstFacAuthPubKey
);
extern VOS_UINT32 AT_SetIdentifyStartPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetIdentifyEndPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetSimlockDataWritePara(
    VOS_UINT8                           ucIndex,
    AT_SIMLOCKDATAWRITE_SET_REQ_STRU   *pstSimlockDataWrite
);
extern VOS_UINT32 AT_QryPhoneSimlockInfoPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QrySimlockDataReadPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetPhonePhynumPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryPhonePhynumPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetPortCtrlTmpPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryPortCtrlTmpPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetPortAttribSetPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryPortAttribSetPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetOpwordParaForApModem (VOS_UINT8 ucIndex);
extern VOS_VOID AT_PhSendRestoreFactParmNoReset( VOS_VOID );
VOS_UINT32 AT_GetWcdmaDivBandStr(VOS_UINT8 *pucGsmBandstr);

VOS_UINT32 AT_SetApSimStPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_TestApSimStPara(VOS_UINT8 ucIndex);

#if(FEATURE_ON == FEATURE_UE_MODE_TDS)
extern VOS_UINT32 At_SetTdsScalibPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 atSetSCALIBParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 At_QryTdsScalibPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 atQrySCALIBParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 At_QryTdsScellinfoPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 atQryScellinfoParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 At_QryCmtm(VOS_UINT8 ucIndex);
extern VOS_UINT32 atQryCmtmCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 AT_GetTdsFeatureInfo(AT_FEATURE_SUPPORT_ST * pstFeATure);
#endif
extern  VOS_UINT32 atSetTdsParaCnfProc(VOS_UINT16 ucClientId, VOS_VOID *pMsgBlock);
extern  VOS_UINT32 atQryTdsFRSSIParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern  VOS_UINT32 atQryTdsTSELRFParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern  VOS_UINT32 atQryTdsFCHANParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern  VOS_UINT32 atQryTdsFTXONParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern  VOS_UINT32 atQryTdsFRXONParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atLcacellCnfProc(VOS_VOID *pMsgBlock);
extern VOS_VOID atLcacellInd(VOS_VOID *pMsgBlock);


VOS_UINT32 AT_SetNvmEccNumPara(VOS_UINT8 ucIndex);
VOS_VOID AT_ConvertMccToNasType(
    VOS_UINT32                          ulMcc,
    VOS_UINT32                         *pulNasMcc
);

extern VOS_UINT32 AT_SetCposPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetCposrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetXcposrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetCgpsClockPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryCposrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryXcposrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestXcposrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestCgpsClockPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_ProcXmlText ( TAF_UINT8 ucIndex, TAF_UINT8 *pData, TAF_UINT16 usLen);

VOS_UINT32 AT_SetGpsInfoPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetLogCfgPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetLogNvePara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryLogNvePara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetLogSavePara(VOS_UINT8 ucIndex);

/* DEL by c64416 for V9R1/V7R1 AT, 2013/09/18 */

/*****************************************************************************
 函 数 名  : AT_QryCPsErrPara
 功能描述  : 查询PS域呼叫错误码
 输入参数  : ucIndex --- 用户索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_QryCPsErrPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_HandleApSndApduCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
);

extern VOS_UINT32 AT_SetCISAPara(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulLengthValue,
    VOS_UINT8                          *pucCommand,
    VOS_UINT16                          usCommandLength);

VOS_UINT32 AT_HandleApSecCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen);
extern VOS_UINT32 AT_SetApSecPara(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pcCmdPara,
    VOS_UINT16                          usParaLen );
extern VOS_UINT32 AT_TestApSecPara( VOS_UINT8 ucIndex );

/*****************************************************************************
 函 数 名  : AT_QryCmutPara
 功能描述  : ^CMUT=<n> 查询静音状态
 输入参数  : ucIndex --- 用户索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_SetCmutPara(VOS_UINT8 ucIndex);


/*****************************************************************************
 函 数 名  : AT_QryCmutPara
 功能描述  : ^CMUT? 查询静音状态
 输入参数  : ucIndex --- 用户索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_QryCmutPara(VOS_UINT8 ucIndex);



VOS_UINT32 At_AbortCopsPara(
    VOS_UINT8                           ucIndex
);


VOS_UINT32 AT_SetSimlockUnlockPara( VOS_UINT8 ucIndex );

/*****************************************************************************
 函 数 名  : AT_SetApdsPara
 功能描述  : ^APDS=<dial_string>,<sub_string>,<I>,<G>,<call_type>设置命令处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 AT_SetApdsPara(VOS_UINT8 ucIndex);

/*****************************************************************************
 函 数 名  : AT_SetClprPara
 功能描述  : ^CLPR=<call_id>设置命令处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 AT_SetClprPara(VOS_UINT8 ucIndex);

/*****************************************************************************
 函 数 名  : AT_TestClprPara
 功能描述  : 设置命令处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 AT_TestClprPara(VOS_UINT8 ucIndex);

/*****************************************************************************
 函 数 名  : AT_QryCCsErrPara
 功能描述  : ^CCSERR设置命令处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 AT_QryCCsErrPara(VOS_UINT8 ucIndex);


VOS_UINT32 At_SetCerssiPara(VOS_UINT8 ucIndex);
VOS_UINT32 At_QryCerssiPara(VOS_UINT8 ucIndex);
VOS_UINT32 At_SetCnmrPara(VOS_UINT8 ucIndex);
VOS_UINT32 At_QryCecellidPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QryCnmrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QryCellIdPara(VOS_UINT8 ucIndex);
/* Deleted by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
/* Deleted by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

VOS_UINT32 At_SetWlthresholdcfgPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 At_SetLWThresholdCfgPara(VOS_UINT8 ucIndex);

/* DEL by c64416 for V9R1/V7R1 AT, 2013/09/18 */


VOS_UINT32 AT_SetCLteRoamAllowPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryCLteRoamAllowPara(VOS_UINT8 ucIndex);

/* DEL by c64416 for V9R1/V7R1 AT, 2013/09/18 */

VOS_UINT32 At_SetSwverPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvDrvAgentSwverSetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_SetCbgPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_QryCbgPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetCopnPara(VOS_UINT8 ucIndex);


/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-10, begin */
VOS_VOID At_RcvMnCallSetCssnCnf(MN_AT_IND_EVT_STRU *pstData);
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-10, end */
VOS_UINT32 AT_FillSsBsService(
    TAF_SS_ERASESS_REQ_STRU            *pstSSPara,
    AT_PARSE_PARA_TYPE_STRU            *pstAtPara
);

VOS_UINT32 AT_FillSsNoRepCondTime(
    VOS_UINT8                           ucSsCode,
    AT_PARSE_PARA_TYPE_STRU            *pstAtPara,
    TAF_SS_REGISTERSS_REQ_STRU         *pstSSPara
);

/* Deleted by l00198894 for V9R1 STK升级, 2013/07/11 */

VOS_VOID At_QryMmPlmnInfoRspProc(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           OpId,
    VOS_VOID                            *pPara
);
VOS_UINT32 At_QryMmPlmnInfoPara(VOS_UINT8 ucIndex);

VOS_UINT32 At_QryEonsUcs2Para(VOS_UINT8 ucIndex);

/*****************************************************************************
 函 数 名  : At_QryPlmnPara
 功能描述  : 查询PLMN的mcc mnc
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : AT_ERROR或AT_WAIT_ASYNC_RETURN

*****************************************************************************/
VOS_UINT32 At_QryPlmnPara(VOS_UINT8 ucIndex);

/*****************************************************************************
 函 数 名  : At_QryXlemaPara
 功能描述  : 查询^XLEMA的处理
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : AT_ERROR或AT_OK
*****************************************************************************/
VOS_UINT32 At_QryXlemaPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetBodySarOnPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryBodySarOnPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_GetGsmBandCapa(VOS_UINT32 *pulGBand);
VOS_UINT32 AT_SndMtaBodySarPara(
    VOS_UINT8                           ucIndex,
    AT_MTA_BODY_SAR_STATE_ENUM_UINT16   enBodySarState,
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara);
VOS_UINT32 AT_SetBodySarWcdmaPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryBodySarWcdmaPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_TestBodySarWcdmaPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetBodySarGsmPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryBodySarGsmPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_TestBodySarGsmPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_CheckHsicUser(VOS_UINT8 ucIndex);

VOS_INT AT_CCpuResetCallback(
    DRV_RESET_CB_MOMENT_E               eparam,
    VOS_INT                             iUserData
);
VOS_INT AT_HifiResetCallback(
    DRV_RESET_CB_MOMENT_E               eparam,
    VOS_INT                             iUserData
);

VOS_UINT32 AT_RcvTempprtStatusInd(VOS_VOID *pMsg);


/*****************************************************************************
 函 数 名  : At_QryIMEIVerifyPara
 功能描述  : 查询IMEI安全校验的结果
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : AT_ERROR或AT_WAIT_ASYNC_RETURN

*****************************************************************************/
VOS_UINT32 At_QryIMEIVerifyPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetNCellMonitorPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryNCellMonitorPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryUserSrvStatePara(VOS_UINT8 ucIndex);


VOS_UINT32 At_SetSIMSlotPara(VOS_UINT8 ucIndex);
VOS_UINT32 At_QrySIMSlotPara(VOS_UINT8 ucIndex);

VOS_UINT32 At_SetSimInsertPara(VOS_UINT8 ucIndex);

VOS_UINT32 At_SetModemLoopPara(VOS_UINT8 ucIndex);

VOS_UINT32 At_SetReleaseRrc(VOS_UINT8 ucIndex);

VOS_UINT32 AT_String2Hex( VOS_UINT8 *nptr,VOS_UINT16 usLen, VOS_UINT32 *pRtn);


VOS_UINT32 AT_SetRefclkfreqPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_QryRefclkfreqPara(VOS_UINT8 ucIndex);


VOS_UINT32 AT_SetTlRficSsiRdPara(VOS_UINT8 ucIndex);

VOS_UINT32 At_SetPullomlogrrcPara(VOS_UINT8 ucIndex);
VOS_UINT32 At_SetDieSNPara(VOS_UINT8 ucIndex);
VOS_UINT32 At_SetChipSNPara(VOS_UINT8 ucIndex);
VOS_UINT32 At_QryHandleDect(VOS_UINT8 ucIndex);

VOS_UINT32 At_SetHandleDect(VOS_UINT8 ucIndex);

/*vSIM Project Begin*/
extern VOS_UINT32 AT_RcvDrvAgentHvpdhSetCnf(VOS_VOID *pMsg);
extern unsigned int AtBase64Decode(const void* pcode,const unsigned int code_size,void* out_pdata,
                                const unsigned int data_size,unsigned int* out_pwrited_data_size);
extern TAF_VOID At_PIHIndProc(TAF_UINT8 ucIndex, SI_PIH_EVENT_INFO_STRU *pEvent);
/*vSIM Project Begin*/

/* DEL by c64416 for V9R1/V7R1 AT, 2013/09/18 */


extern VOS_UINT32 AT_SetUserCfgOPlmnPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_QryUserCfgOPlmnPara(VOS_UINT8 ucIndex);

/* Added by d00212987 for BalongV9R1 NV备份数据丢失容错&恢复 项目 2013-10-24, begin */
extern VOS_UINT32 AT_RcvNvManufactureExtSetCnf(VOS_VOID *pMsg);
/* Added by d00212987 for BalongV9R1 NV备份数据丢失容错&恢复 项目 2013-10-24, end */

VOS_UINT32 AT_TestNetScan( VOS_UINT8 ucIndex );


#if (FEATURE_ON == FEATURE_AT_HSUART)
VOS_VOID AT_UpdateUartCfgNV(VOS_VOID);
VOS_UINT32 AT_SetIprPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryIprPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetIcfPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryIcfPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetIfcPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryIfcPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetOPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetSwitchUart(VOS_UINT8 ucIndex);
#endif

/* Added by l00198894 for 新增+ECID命令, 2013-12-09, begin */
VOS_UINT32 AT_SetEcidPara(VOS_UINT8 ucIndex);
/* Added by l00198894 for 新增+ECID命令, 2013-12-09, end */

VOS_UINT32 AT_QryClccPara(VOS_UINT8 ucIndex);

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : AT_QryCiregPara
 功能描述  : +CIREG?查询命令处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 AT_QryCiregPara(VOS_UINT8 ucIndex);


/*****************************************************************************
 函 数 名  : AT_QryCirepPara
 功能描述  : +CIREP?查询命令处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 AT_QryCirepPara(VOS_UINT8 ucIndex);

/*****************************************************************************
 函 数 名  : AT_SetCiregPara
 功能描述  : +CIREG=<n>设置命令处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32

*****************************************************************************/
TAF_UINT32 AT_SetCiregPara(TAF_UINT8 ucIndex);

/*****************************************************************************
 函 数 名  : AT_SetCirepPara
 功能描述  : +CIREP=<reporting>设置命令处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32

*****************************************************************************/
TAF_UINT32 AT_SetCirepPara(TAF_UINT8 ucIndex);


VOS_UINT32 AT_SetVolteimpuPara(VOS_UINT8 ucIndex);

TAF_UINT32 AT_SetCacmimsPara(TAF_UINT8 ucIndex);

VOS_UINT32 AT_SetCcwaiPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetUiccAuthPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetURSMPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetKsNafAuthPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetCallModifyInitPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetCallModifyAnsPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetEconfDialPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryClccEconfInfo(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryEconfErrPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetImsSwitchPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryImsSwitchPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetCevdpPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryCevdpPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_InputValueTransToVoiceDomain(
    VOS_UINT32                          ulValue,
    TAF_MMA_VOICE_DOMAIN_ENUM_UINT32   *penVoiceDomain
);

#endif

VOS_UINT32 At_SetChldExPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 At_SetAntSwitchPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryAntSwitchPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_RcvDrvAgentAntSwitchSetCnf(VOS_VOID *pstData);
extern VOS_UINT32 AT_RcvDrvAgentAntSwitchQryCnf(VOS_VOID *pstData);



extern VOS_UINT32 AT_QryModemStatusPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetModemStatusPara( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_SetRATCombinePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryRATCombinePara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_QryMipiClkValue(VOS_UINT8 ucIndex);

#if (FEATURE_ON == FEATURE_DSDS)
extern VOS_UINT32 At_SetPsProtectModePara (VOS_UINT8 ucIndex);
#endif
extern VOS_UINT32 At_SetPhyInitPara (VOS_UINT8 ucIndex);

/* Added by w00167002 for L-C互操作项目, 2014-2-22, begin */
TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8 At_ConvertDetachTypeToServiceDomain(
    VOS_UINT32                          ulCgcattMode
);
/* Added by w00167002 for L-C互操作项目, 2014-2-22, end */

TAF_MMA_ATTACH_TYPE_ENUM_UINT8 At_ConvertCgcattModeToAttachType(
    VOS_UINT32                          ulCgcattMode
);

/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, begin */
extern VOS_UINT32 AT_FillCalledNumPara(
    VOS_UINT8                          *pucAtPara,
    VOS_UINT16                          usLen,
    MN_CALL_CALLED_NUM_STRU            *pstCalledNum
);

extern TAF_UINT32 At_AsciiString2HexSimple(TAF_UINT8 *pTextStr,TAF_UINT8 *pucSrc,TAF_UINT16 usSrcLen);
/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, end */

extern VOS_UINT32 AT_QryCclkPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetCclkPara(VOS_UINT8 ucIndex);

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
VOS_UINT32 AT_SetVoicePreferPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryVoicePreferPara(VOS_UINT8 ucIndex);
#endif

extern TAF_UINT32 At_QryCardTypePara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetCcmgsPara(VOS_UINT8 ucIndex, VOS_UINT32 ulLengthValue, VOS_UINT8 *pucCommand, VOS_UINT16 usCommandLength);

extern VOS_UINT32 AT_SetCcmgwPara(VOS_UINT8 ucIndex, VOS_UINT32 ulLengthValue, VOS_UINT32 ulStatValue, VOS_UINT8 *pucCommand, VOS_UINT16 usCommandLength);

extern VOS_UINT32 AT_SetCcmgdPara(VOS_UINT8 ucIndex);

extern VOS_VOID At_XsmsIndProc(VOS_UINT8 ucIndex, TAF_XSMS_APP_MSG_TYPE_ENUM_UINT32  enEventType, TAF_XSMS_APP_AT_EVENT_INFO_STRU *pstEvent);

extern VOS_VOID At_XsmsCnfProc(VOS_UINT8 ucIndex, TAF_XSMS_APP_MSG_TYPE_ENUM_UINT32 enEventType, TAF_XSMS_APP_AT_EVENT_INFO_STRU *pstEvent);

extern VOS_VOID AT_ProcXsmsMsg(TAF_XSMS_APP_AT_CNF_STRU *pstMsg);

VOS_VOID AT_ProcXpdsMsg(AT_XPDS_MSG_STRU *pstMsg);

extern VOS_UINT32 AT_SetCdmaMemStatusPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_HandleApXsmsSndCmd(VOS_UINT8 ucIndex, VOS_UINT8 *pucData, VOS_UINT16 usLen);

extern VOS_UINT32 AT_HandleApXsmsWriteCmd(VOS_UINT8 ucIndex, VOS_UINT8 *pucData, VOS_UINT16 usLen);

extern VOS_UINT32 AT_SetCrmPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetCqosPriPara(VOS_UINT8 ucIndex);
/* 移到 FEATURE_UE_MODE_CDMA 宏中 */

extern VOS_UINT32 AT_SetCBurstDTMFPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetCfshPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_CheckCfshNumber(
    VOS_UINT8                          *pucAtPara,
    VOS_UINT16                          usLen
);

extern VOS_UINT32 AT_CheckCFreqLockEnablePara(VOS_VOID);
extern VOS_UINT32 AT_SetCFreqLockPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryCFreqLockInfo(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetCdmaCsqPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryCdmaCsqPara(VOS_UINT8 ucIndex);

VOS_UINT32 At_SetCustomDial(VOS_UINT8 ucIndex);

VOS_UINT32 At_SetCdmaModemSwitch(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetTTYModePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryTTYModePara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetCtaPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryCtaPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_QryCgmtuPara(VOS_UINT8 ucIndex);

VOS_UINT32 At_SetFemCtrl(VOS_UINT8 ucIndex);

extern TAF_UINT32 At_AsciiNum2HexString(TAF_UINT8 *pucSrc, TAF_UINT16 *pusSrcLen);

TAF_UINT32 AT_HexToAsciiString(
    TAF_UINT8                          *pSrcStr,
    TAF_UINT8                          *pucDstStr,
    TAF_UINT16                          usSrcLen
);

extern VOS_UINT32 At_SetRatRfSwitch(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QryRatRfSwitch(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_Set1xChanPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_Qry1xChanPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_QryProRevInUse(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_QryCasState(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_QryProGetEsn(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_QryProGetMeid(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_QryHighVer(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetMccFreqPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryMccFreqPara(VOS_UINT8 ucIndex);
VOS_UINT32 At_QryHplmnPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetDplmnListPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryDplmnListPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_ParseDplmnStringList(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucDplmnString,
    TAF_MMA_DPLMN_INFO_SET_STRU        *pstDplmnInfoSet
);

VOS_UINT32 AT_ParseEhplmnStringList(
    VOS_UINT8                           ucIndex,
    TAF_MMA_DPLMN_INFO_SET_STRU        *pstDplmnInfoSet
);

extern VOS_UINT32 AT_QryTransModePara(VOS_UINT8 ucIndex);
/* Added by wx270776 for OM融合, 2015-7-25, begin */
extern VOS_VOID DIAG_LogShowToFile(VOS_BOOL bIsSendMsg);
/* Added by wx270776 for OM融合, 2015-7-25, end */
extern VOS_UINT32 AT_QryEmcCallBack( VOS_UINT8 ucIndex  );

extern VOS_UINT32 AT_QryCdmaDormTimerVal(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetCdmaDormantTimer(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_QryUECenterPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetUECenterPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_TestUECenterPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetHdrCsqPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryHdrCsqPara(VOS_UINT8 ucIndex);


extern VOS_UINT32 AT_QryEncryptCallCap( VOS_UINT8 ulIndex );
extern VOS_UINT32 AT_QryEncryptCallRandom( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_QryEncryptCallKmc( VOS_UINT8 ucIndex );
extern VOS_UINT32  AT_QryEccTestMode( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_QryCurrSidNid(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryAfcClkInfo(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetSecureStatePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetKcePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QrySecureStatePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QrySocidPara(VOS_UINT8 ucIndex);


TAF_UINT32 At_CheckCurrRatModeIsCL(
    VOS_UINT8                           ucIndex
);
VOS_UINT32 AT_SetCtzuPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryCtzuPara(VOS_UINT8 ucIndex);

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

#endif /* end of MapsTemplate.h*/

