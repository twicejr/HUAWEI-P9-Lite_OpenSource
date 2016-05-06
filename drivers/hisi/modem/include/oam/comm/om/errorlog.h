

#ifndef __ERRORLOG_H__
#define __ERRORLOG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "v_typdef.h"
#include "OmCodecInterface.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"

#pragma pack(4)

/*****************************************************************************
   宏定义
******************************************************************************/
#define MNTN_ERRLOG_DIR                     "/mnvm3:0/Errlog"
#define MNTN_ERRLOG0_PATH                   "/mnvm3:0/Errlog/Errorlog0.bin"  /*log文件0地址*/
#define MNTN_ERRLOG1_PATH                   "/mnvm3:0/Errlog/Errorlog1.bin"  /*log文件1地址*/
#define MNTN_ERRLOG_UNITARY_DIR             "/modem_log/Errlog"
#define MNTN_ERRLOG0_UNITARY_PATH           "/modem_log/Errlog/Errorlog0.bin"  /*log文件0地址*/
#define MNTN_ERRLOG1_UNITARY_PATH           "/modem_log/Errlog/Errorlog1.bin"  /*log文件1地址*/


#define MNTN_ERRLOG_IMEI_SIZE               (16)
#define MNTN_ERRLOG_HARDVERSION_SIZE        (32)
#define MNTN_ERRLOG_SOFTVERSION_SIZE        (32)
#define IMSI_RECORD_LEN						(9)

#define MNTN_ERRLOG_MAXSIZE                 (0x10000)

/* PC超时定时器计数上限2 */
#define NAS_MNTN_PC_ACTIVE_EXPIRE_TIMES     (2)

/* PDP激活失败原因值的默认值 */
#define NAS_MNTN_SM_REJ_CAUSE_INVALID       (0xff)
#define MNTN_RAC_INVALID_ID                 (0xffff)
#define NAS_MNTN_IMSI_LENGTH_IN_USIM        (9)
#define NAS_MNTN_CS_ATTEMPT_MAX             (4)
#define NAS_MNTN_PS_ATTEMPT_MAX             (5)
#define NAS_MNTN_MAX_ASCII_ADDRESS_NUM      (20)
#define NAS_MNTN_MAX_HIGH_PLMN_NUM          (16)                                    /* 高质量的PLMN的最大个数 RRC_MAX_HIGH_PLMN_NUM*/
#define NAS_MNTN_LOW_PLMN_NUM               (16)                                    /* 低质量的PLMN的最大个数 RRC_MAX_LOW_PLMN_NUM*/
/* ERROR LOG的搜网事件仅在搜网间隔定时器时长为5秒第5次启动时记录 */
/* 搜网间隔定时器时长为5秒，定时器时长INDEX为0 */
#define NAS_MNTN_AVAILABLE_PLMN_SRCH_TIMER_LENGTH_ZERO      (0)

/* 搜网间隔定时器第5次启动计数器定时器启动次数为5 */
#define NAS_MNTN_AVAILABLE_PLMN_SRCH_TIMER_COUNTER_TIMES    (5)

/* ERROR LOG事件业务不可用事件从单板上电到下电期间记录事件的最大次数 */
#define NAS_MNTN_ERRORLOG_SERVICE_UNAVAILABLE_EVENT_MAX     (10)

/* ERROR LOG事件搜网失败事件从单板上电到下电期间记录事件的最大次数 */
#define NAS_MNTN_ERRORLOG_PLMN_UNAVAILABLE_EVENT_MAX        (30)

/* ERROR LOG事件PDP激活失败事件从单板上电到下电期间记录事件的最大次数 */
#define NAS_MNTN_ERRORLOG_ACTIVATE_FAIL_EVENT_MAX           (15)

/* ERROR LOG事件短信发送失败事件从单板上电到下电期间记录事件的最大次数 */
#define NAS_MNTN_ERRORLOG_SMS_MO_FAILURE_MAX                (5)

/*30分钟内记录的弱信号发生的最大次数*/
#define GAS_MNTN_WEAK_SIGNAL_LIST_MAX_NUM                       (30)

/* ERROR LOG事件ME文件操作失败事件从单板上电到下电期间记录事件的最大次数 */
#define NAS_MNTN_ERRORLOG_ME_FILE_ERROR_MAX                 (1)
/*******************************************************************************
   枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : MNTN_WRITEFLASH_EVENT_ENUM
 结构说明  : 原语的ulMsgName
*****************************************************************************/
enum MNTN_WRITEFLASH_EVENT_ENUM
{
    /* 消息名称 */                              /*消息ID*/              /* 备注 */
    MNTN_VERSION_INFO_EVENT                     = 0x00000000,           /* _H2ASN_MsgChoice MNTN_VERSION_INFO_EVENT_STRU */
    MNTN_NAS_ERRORLOG_ACTIVATE_FAIL_EVENT       = 0x00000001,           /* _H2ASN_MsgChoice NAS_MNTN_ACTIVE_FAIL_EVENT_STRU */
    MNTN_NAS_ERRORLOG_PLMN_UNAVAILABLE_EVENT    = 0x00000002,           /* _H2ASN_MsgChoice NAS_MNTN_PLMN_UNAVAILABLE_EVENT_STRU */
    MNTN_NAS_ERRORLOG_SERVICE_UNAVAILABLE_EVENT = 0x00000003,           /* _H2ASN_MsgChoice NAS_MNTN_SERVICE_UNAVAILABLE_EVENT_STRU */
    MNTN_NAS_ERRORLOG_SMS_MO_FAILURE            = 0x00000004,           /* _H2ASN_MsgChoice NAS_MNTN_SMS_MO_FAIL_EVENT_STRU */
    MNTN_NAS_ERRORLOG_CS_CHANNEL_OPEN_FAILURE   = 0x00000005,           /* _H2ASN_MsgChoice NAS_MNTN_CS_CHANNEL_OPEN_FAILURE_EVENT_STRU */
    MNTN_NAS_ERRORLOG_CS_MED_TIMEOUT            = 0x00000006,           /* _H2ASN_MsgChoice NAS_MNTN_CS_MED_TIMEOUT_EVENT_STRU */
    MNTN_NAS_ERRORLOG_SMS_ME_ERROR              = 0x00000007,           /* _H2ASN_MsgChoice NAS_MNTN_SMS_ME_ERROR_EVENT_STRU */

    MNTN_GAS_INIT_WEAK_SIGNAL_EVENT             = 0x00000201,           /* _H2ASN_MsgChoice GAS_MNTN_INIT_WEAK_SIGNAL_EVT_STRU */

    MNTN_GAS_PERIOD_WEAK_SIGNAL_LIST_EVENT      = 0x00000202,            /* _H2ASN_MsgChoice GAS_MNTN_PERIOD_WEAK_SIGNAL_LIST_EVT_STRU */

    MNTN_WAS_NO_SIGNAL_EVENT                    = 0x00000301,           /* _H2ASN_MsgChoice WAS_MNTN_NO_SIGNAL_EVENT_STRU*/
    MNTN_WAS_WEAK_SIGNAL_SAMPLE_EVENT           = 0x00000302,           /* _H2ASN_MsgChoice WAS_MNTN_WEAK_SIGNAL_SAMPLE_EVENT_STRU*/
    MNTN_OAM_NO_SIM_CARD_EVENT                  = 0x00000401,           /* _H2ASN_MsgChoice OAM_MNTN_NO_SIM_CARD_EVENT_STRU */
    MNTN_OAM_SIM_CARD_LOST_EVENT                = 0x00000402,           /* _H2ASN_MsgChoice OAM_MNTN_SIM_CARD_LOST_EVENT_STRU */
    MNTN_OAM_PCV_QUNUE_FULL_EVENT               = 0x00000403,           /* _H2ASN_MsgChoice OAM_MNTN_PCV_ERRLOG_EVENT_STRU */
    MNTN_OAM_PCV_DATA_EXCEPTION_EVENT           = 0x00000404,           /* _H2ASN_MsgChoice OAM_MNTN_PCV_ERRLOG_EVENT_STRU */
    MNTN_OAM_MNTN_NV_ERRLOG_EVENT               = 0x00000405,           /* _H2ASN_MsgChoice OAM_MNTN_NV_ERRLOG_EVENT_STRU */
    MNTN_OAM_MNTN_WD_COUNT_ERRLOG_EVENT         = 0x00000406,           /* _H2ASN_MsgChoice OAM_MNTN_WD_COUNT_ERRLOG_EVENT_STRU */
    MNTN_OAM_PORT_NUM_ERRLOG_EVENT              = 0x00000407,           /* _H2ASN_MsgChoice OAM_MNTN_PORT_ERRLOG_EVENT_STRU */
    MNTN_USB_ENUMERATE_STATUS_EVENT             = 0x00000501,           /* _H2ASN_MsgChoice USB_MNTN_ENUMERATE_STATUS_EVENT_STRU */
    MNTN_USB_INSTALL_SUCCESS_EVENT              = 0x00000502,           /* _H2ASN_MsgChoice USB_MNTN_INSTALL_SUCCESS_EVENT_STRU */
    MNTN_USB_RESET_ABNORMAL_EVENT               = 0x00000503,           /* _H2ASN_MsgChoice USB_MNTN_RESET_ABNORMAL_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_DMA_MIC_RESET     = 0x00000601,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_DMA_SPK_RESET     = 0x00000602,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_W_DEC_INT_LOST    = 0x00000603,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_WBBP_DATA_NONE    = 0x00000604,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_WBBP_DATA_BAD     = 0x00000605,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_W_DECIPHER_LOST   = 0x00000606,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_GSM_BFI_FRAME     = 0x00000607,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_CODEC_SID_FRAME   = 0x00000608,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_PCV_INTERPOLATE   = 0x00000609,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_PCV_RINGBUF_FULL  = 0x0000060A,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_DRV_HIGH_STACK_RECORD                  = 0x00000701,           /* _H2ASN_MsgChoice HIGH_STACK_TASK_STR */
    MNTN_DRV_SD_ERRLOG_RECORD                   = 0x00000702,           /* _H2ASN_MsgChoice SD_TRANSFER_ERROR_ST */
    MNTN_DRV_WIFI_ERRLOG_RECORD                 = 0x00000703,           /* _H2ASN_MsgChoice WIFI_TARGET_ASSERT_ERROR_ST */
    MNTN_DRV_PMU_WRNLOG_RECORD                  = 0x00000704,           /* _H2ASN_MsgChoice MNTN_DRV_PMU_ERROR_ST */
    MNTN_DRV_PMU_ERRLOG_RECORD                  = 0x00000705,           /* _H2ASN_MsgChoice MNTN_DRV_PMU_ERROR_ST */
    MNTN_DRV_SYSTEM_RESET_RECORD                = 0x00000706,           /* _H2ASN_MsgChoice DRV_MNTN_SYSTEM_RESET_STRU */

    MNTN_SPY_QOS_LIMIT_EVENT                    = 0x00000801,           /* _H2ASN_MsgChoice OAM_MNTN_SPY_ERROR_EVENT_STRU */
    MNTN_SPY_SOFTOFF_EVENT                      = 0x00000802,           /* _H2ASN_MsgChoice OAM_MNTN_SPY_ERROR_EVENT_STRU */
    MNTN_SPY_PWOER_DOWN_EVENT                   = 0x00000803,           /* _H2ASN_MsgChoice OAM_MNTN_SPY_ERROR_EVENT_STRU */
    MNTN_OAM_SOCP_ERROR_EVENT                   = 0x00000A01,
    MNTN_OAM_ICC_ERROR_EVENT                    = 0x00000B01,
    MNTN_ERRLOG_BUTT                            = 0xFFFFFFFF
};
typedef VOS_INT32 MNTN_WRITEFLASH_EVENT_ENUM_UINT32;

typedef struct
{
    MNTN_HEAD_INFO_STRU    stRecordHead;
    VOS_UINT32             ulStatusReg;
}MNTN_DRV_PMU_ERROR_ST;

/*****************************************************************************
 枚举名    : MNTN_ME_OPERATION_ENUM
 结构说明  : 短信ME存储区操作类型，包括读和写两种操作
*****************************************************************************/
enum MNTN_ME_OPERATION_ENUM
{
    MNTN_ME_OPERATION_READ,
    MNTN_ME_OPERATION_WRITE,
    MNTN_ME_OPERATION_BUTT
};
typedef VOS_INT32 MNTN_ME_OPERATION_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_MNTN_ACTIVE_FAIL_TYPE_ENUM
 结构说明  : PDP激活失败类型，包括PS域服务不可用，等待网络响应超时和被网络拒绝
*****************************************************************************/
enum NAS_MNTN_ACTIVE_FAIL_TYPE_ENUM
{
    NAS_MNTN_ACTIVE_FAIL_TYPE_PS_SERVICE_UNAVAILABLE = 0,
    NAS_MNTN_ACTIVE_FAIL_TYPE_ACTIVE_TIMEOUT,
    NAS_MNTN_ACTIVE_FAIL_TYPE_ACTIVE_REJECT,
    NAS_MNTN_ACTIVE_FAIL_TYPE_BUTT
};
typedef VOS_UINT32 NAS_MNTN_ACTIVE_FAIL_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MNTN_SYS_SUBMODE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 驻留网络的接入技术枚举
*****************************************************************************/
enum NAS_MNTN_SYS_SUBMODE_ENUM
{
    NAS_MNTN_SYS_SUBMODE_NULL                  = 0,                /* 无服务 */
    NAS_MNTN_SYS_SUBMODE_GSM                   = 1,                /* GSM模式 */
    NAS_MNTN_SYS_SUBMODE_GPRS                  = 2,                /* GPRS模式 */
    NAS_MNTN_SYS_SUBMODE_EDGE                  = 3,                /* EDGE模式 */
    NAS_MNTN_SYS_SUBMODE_WCDMA                 = 4,                /* WCDMA模式 */
    NAS_MNTN_SYS_SUBMODE_HSDPA                 = 5,                /* HSDPA模式 */
    NAS_MNTN_SYS_SUBMODE_HSUPA                 = 6,                /* HSUPA模式 */
    NAS_MNTN_SYS_SUBMODE_HSDPA_HSUPA           = 7,                /* HSDPA+HSUPA模式 */
    NAS_MNTN_SYS_SUBMODE_BUTT
};
typedef VOS_UINT8  NAS_MNTN_SYS_SUBMODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MNTN_SEND_DOMAIN_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 发送域可用状态
*****************************************************************************/
enum NAS_MNTN_SEND_DOMAIN_STATUS_ENUM
{
    NAS_MNTN_SEND_DOMAIN_STATUS_UNAVAILABLE,
    NAS_MNTN_SEND_DOMAIN_STATUS_AVAILABLE
};
typedef VOS_UINT32 NAS_MNTN_SEND_DOMAIN_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : OSA_MNTN_WD_COUNT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :资源使用状态
*****************************************************************************/
enum OSA_MNTN_WD_COUNT_ENUM
{
    OSA_MNTN_WD_COUNT_TIMER         = 0,
    OSA_MNTN_WD_COUNT_RTC_TIMER,
    OSA_MNTN_WD_COUNT_MESSAGE,
    OSA_MNTN_WD_COUNT_PS_MEMORY,
    OSA_MNTN_WD_COUNT_APP_MEMORY,
    OSA_MNTN_WD_COUNT_BUTT
};
typedef VOS_UINT32 OSA_MNTN_WD_COUNT_ENUM_UINT32;
/*****************************************************************************
   STRUCT定义
*****************************************************************************/

/*******************************************************************************
 结构名    : MNTN_VERSION_INFO_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 版本信息结构
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stRecordHead;
    IMEI_STRU                           stIMEI;
    VOS_CHAR                            acHardVersion[MNTN_ERRLOG_HARDVERSION_SIZE];
    VOS_CHAR                            acSoftVersion[MNTN_ERRLOG_SOFTVERSION_SIZE];
}MNTN_VERSION_INFO_EVENT_STRU;

/*******************************************************************************
 结构名    : USB_MNTN_INSTALL_SUCCESS_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 安装信息的结构
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU              stRecordHead;
    VOS_UINT32                       ulRewindCommand;
    VOS_UINT32                       ulU2diag;
}USB_MNTN_INSTALL_SUCCESS_EVENT_STRU;

/*******************************************************************************
 结构名    : USB_MNTN_ENUMERATE_STATUS_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 枚举信息的结构
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU             stRecordHead;
    VOS_UINT32                      ulU2diag;
    VOS_UINT8                       ucFlag;      /*differentiate rewind and timeout*/
    VOS_UINT8                       ucUsbSpeed;
    VOS_UINT8                       ucUsbStatus;
    VOS_UINT8                       ucReserved;
}USB_MNTN_ENUMERATE_STATUS_EVENT_STRU;

/*******************************************************************************
 结构名    : USB_MNTN_RESET_ABNORMAL_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : usb总线异常复位信息的结构
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU             stRecordHead;
    VOS_UINT32                      ulU2diag;
    VOS_UINT8                       ucUsbStatus;
    VOS_UINT8                       ucUsbSpeed;
    VOS_UINT8                       ucSCSITimeoutFlag;
    VOS_UINT8                       ucSCSICommand;
    VOS_UINT8                       ucLastIntrIndex;
    VOS_UINT8                       aucReserve[3];
    VOS_UINT32                      ulLedStatus;
}USB_MNTN_RESET_ABNORMAL_EVENT_STRU;

/*******************************************************************************
 结构名    : DRV_MNTN_SYSTEM_RESET_STR
 协议表格  :
 ASN.1描述 :
 结构说明  : 记录系统复位结构的结构
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                    stRecordHead;
    VOS_UINT32                             ulRebootReason ;
    VOS_UINT32                             ulModeId;
    VOS_UINT32                             ulArg1;
    VOS_UINT32                             ulArg2;
    VOS_UINT8                              Imsi[IMSI_RECORD_LEN];
    VOS_UINT8                              ImsiStatus;
    VOS_UINT8                              reserv[2];
}DRV_MNTN_SYSTEM_RESET_STRU;

/*****************************************************************************
结构名     : NAS_MNTN_SMS_ME_ERROR_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :ME文件操作错误，包括如下内容
             事件头部，文件操作错误码
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    MNTN_ME_OPERATION_ENUM_UINT32       enOperation;
    VOS_UINT32                          ulErrorNo;
} NAS_MNTN_SMS_ME_ERROR_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_MNTN_PDP_ACTIVE_FAIL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 拨号失败原因，包括如下内容:
             拨号失败类型 支持拨号被网络拒绝，拨号请求等待网络响应超时和PS域无服务
             网络拒绝原因值
             GMM的PS域是否注册标志
*******************************************************************************/
typedef struct
{
    NAS_MNTN_ACTIVE_FAIL_TYPE_ENUM_UINT32                   enFailType;
    VOS_UINT8                                               ucSmCause;
    /* 超时次数从3380定时器计数器中获取无需另外记录 */
    VOS_UINT8                                               ucRegisterFlg;
    VOS_UINT8                                               aucReserved1[2];
}NAS_MNTN_PDP_ACTIVE_FAIL_STRU;

/*******************************************************************************
 结构名    : MNTN_PLMN_ID_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PLMN的结构
*******************************************************************************/
typedef struct
{
    VOS_UINT32                        ulMcc;
    VOS_UINT32                        ulMnc;
}MNTN_PLMN_ID_STRU;/* MMC_PLMN_ID_STRU结构的同步结构 */

/*******************************************************************************
 结构名    : MNTN_RAI_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 位置区或路由区信息
*******************************************************************************/
typedef struct
{
    MNTN_PLMN_ID_STRU                   stPlmn;
    VOS_UINT16                          usLac;
    VOS_UINT16                          usRac;
}MNTN_RAI_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_MNTN_USIM_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : NAS相关的(U)SIM卡信息，包括如下内容:
             卡存在状态，卡类型(区分SIM卡，USIM卡和快速开机)，卡的PIN码开启状态
             (U)SIM卡的IMSI
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCardStatus;                           /* 卡状态: 无卡；有卡 */
    VOS_UINT8                           ucCardType;                             /* 卡类型: SIM卡；USIM卡；快速开机 */
    VOS_UINT8                           ucPinStatus;                            /* 卡PIN码状态: READY；*/
    VOS_UINT8                           aucImsi[NAS_MNTN_IMSI_LENGTH_IN_USIM];  /* IMSI号码 */
    MNTN_PLMN_ID_STRU                   stRplmn;
}NAS_MNTN_USIM_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_MNTN_POSITION_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 位置信息，包括如下内容
             位置和路由区信息，小区ID，CS域接入受限标志，PS域接入受限标志，
             系统子模式，接入技术，网络模式
*******************************************************************************/
typedef struct
{
    MNTN_RAI_INFO_STRU                      stRai;                                  /* LAC: g_MmcGlobalCtrl.CurLai.ulLac */
    VOS_UINT32                              ulCellId;                               /* CELL ID: gstMmcCellInfo.aulCellId[0]*/
    NAS_MNTN_SYS_SUBMODE_ENUM_UINT8         enSysSubMode;                           /* 当前小区的系统子模式，系统消息结构RRMM_SYS_INFO_IND_STRU中数据 */
    VOS_UINT8                               ucRat;
    VOS_UINT8                               ucNetworkMode;                          /* NETWORK MODE: g_MmcGlobalCtrl.ucNwMode */
    VOS_UINT8                               aucReserved[1];
}NAS_MNTN_POSITION_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_MNTN_CS_UNAVAILABLE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CS域注册失败原因列表，包括如下内容
             注册失败次数，注册失败原因值列表和要求立即记录事件标志；
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTimes;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          aulCause[NAS_MNTN_CS_ATTEMPT_MAX];                                             /* 更新失败原因                             */
    VOS_BOOL                            bRecordRequired;
}NAS_MNTN_CS_UNAVAILABLE_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_MNTN_PS_UNAVAILABLE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PS域注册失败原因列表，包括如下内容
             注册失败次数，注册失败原因值列表和要求立即记录事件标志；
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTimes;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          aulCause[NAS_MNTN_PS_ATTEMPT_MAX];                                             /* 更新失败原因                             */
    VOS_BOOL                            bRecordRequired;
}NAS_MNTN_PS_UNAVAILABLE_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_MNTN_SERVICE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 服务域注册失败原因列表，包括如下内容
             CS域和PS域注册状态
*******************************************************************************/
typedef struct
{
    NAS_MNTN_CS_UNAVAILABLE_INFO_STRU   stCsUnavailable;
    NAS_MNTN_PS_UNAVAILABLE_INFO_STRU   stPsUnavailable;
}NAS_MNTN_SERVICE_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_MNTN_MO_SERVICE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 短信功能相关的UST文件信息，包括如下内容
             (U)SIM卡中的SMSS,SMS,SMSR,SMSP文件的存在状态
             是否支持MO-SMS Control by USIM
*******************************************************************************/
typedef struct
{
    VOS_BOOL                            bEfSmssFlag;                            /*是否支持EFSMSS文件*/
    VOS_BOOL                            bEfSmsFlag;                             /*SMS Storage 存在与否*/
    VOS_BOOL                            bEfSmsrFlag;                            /*SMSR Storage 存在与否*/
    VOS_BOOL                            bEfSmspFlag;                            /*SMSP 存在与否*/
    VOS_BOOL                            bMoSmsCtrlFlag;                         /*是否支持MO-SMS Control by USIM*/
}NAS_MNTN_MO_SERVICE_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_MNTN_USIM_STATUS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 短信功能初始化信息，包括如下内容
             短信模块记录的(U)SIM卡存在状态，短信TAF层的初始化状态
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsimStatus;                           /*SIM卡状态*/
    VOS_UINT8                           ucPowerState;                           /*标识是否在上电过程中*/
    VOS_UINT8                           aucReserved[2];
} NAS_MNTN_USIM_STATUS_INFO_STRU;/*MN_MSG_USIM_STATUS_INFO_STRU*/

/*******************************************************************************
 结构名    : NAS_MNTN_ASCII_ADDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 短信功能地址信息数据结构，包括如下内容
             号码类型，拨号计划，号码长度，ASCII码编码的号码
*******************************************************************************/
/*Content of Sms BCD Address*/
typedef struct
{
    VOS_UINT8                           ucNumType;                              /*type of number*/
    VOS_UINT8                           ucNumPlan;                              /*Numbering plan identification*/
    VOS_UINT8                           aucReserve1[2];
    VOS_UINT32                          ulLen;                                  /*Length of AsicNum*/
    VOS_UINT8                           aucAsciiNum[NAS_MNTN_MAX_ASCII_ADDRESS_NUM + 1];   /*array  of ASCII Num*/
    VOS_UINT8                           aucReserve2[3];
} NAS_MNTN_ASCII_ADDR_STRU;/*MN_MSG_ASCII_ADDR_STRU*/

/*******************************************************************************
 结构名    : NAS_MNTN_SMS_MO_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 短信发送功能信息数据结构，包括如下内容
             短信功能相关的UST文件信息，短信功能初始化信息，短信中心号码，
             短信发送目的号码，RP-ERROR消息中的RP-Cause
1.日    期   : 2013年6月26日
  作    者   : f62575
  修改内容   : V9R1 STK升级 ucRpCause-> ulMoFailCause
*******************************************************************************/
typedef struct
{
    NAS_MNTN_MO_SERVICE_INFO_STRU       stUstInfo;
    NAS_MNTN_USIM_STATUS_INFO_STRU      stMsgStatus;
    NAS_MNTN_ASCII_ADDR_STRU            stScAddr;                               /*destination addr of sms*/
    NAS_MNTN_ASCII_ADDR_STRU            stDestAddr;                             /*destination addr of sms*/
    VOS_UINT32                          ulMoFailCause;
}NAS_MNTN_SMS_MO_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_MNTN_LOW_PLMN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 低质量的PLMN信息数据结构，包括如下内容
             PLMN信息，RSCP测量值
*******************************************************************************/
typedef struct
{
    MNTN_PLMN_ID_STRU                   stPlmnId;                               /* PLMN ID    */
    VOS_INT32                           lRscp;                                  /* RSCP测量值 */
}NAS_MNTN_LOW_PLMN_INFO_STRU;/*RRC_LOW_PLMN_INFO_STRU*/

/*******************************************************************************
 结构名    : NAS_MNTN_PLMN_AVAILABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 可用PLMN信息数据结构，包括如下内容
             高质量PLMN的个数，低质量PLMN的个数，高质量PLMN信息列表，低质量PLMN信息列表
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHighPlmnNum;                          /* 高质量PLMN的个数 */
    MNTN_PLMN_ID_STRU                   astHighPlmnList[NAS_MNTN_MAX_HIGH_PLMN_NUM];   /* 高质量PLMN列表   */
    VOS_UINT32                          ulLowPlmnNum;                           /* 低质量PLMN的个数 */
    NAS_MNTN_LOW_PLMN_INFO_STRU         astLowPlmnList[NAS_MNTN_LOW_PLMN_NUM];     /* 低质量PLMN列表   */
}NAS_MNTN_PLMN_AVAILABLE_STRU;/*RRC_PLMN_ID_LIST_STRU*/

/*******************************************************************************
 结构名    : NAS_MNTN_SERVICE_UNAVAILABLE_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UE服务域不可用事件，包括如下内容
             事件头部，NAS相关的SIM卡信息，位置信息，尝试搜网信息
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;
    VOS_UINT32                          ulBand;
    /* 变长度的可用PLMN列表，详细信息直接在ASN中定义， */
    VOS_UINT8                           aucPlmnAttempt[4];
}NAS_MNTN_PLMN_UNAVAILABLE_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_MNTN_SERVICE_UNAVAILABLE_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UE服务域不可用事件，包括如下内容
             事件头部，NAS相关的SIM卡信息，位置信息，UE注册状态
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;
    NAS_MNTN_SERVICE_INFO_STRU          stServiceInfo;
}NAS_MNTN_SERVICE_UNAVAILABLE_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_MNTN_SMS_MO_FAIL_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 短信发送失败事件，包括如下内容
             事件头部，NAS相关的(U)SIM卡信息，位置信息，短信发送功能相关信息
             CS域服务状态，PS域服务状态，
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;
    NAS_MNTN_SMS_MO_INFO_STRU           stMoFail;
    NAS_MNTN_SEND_DOMAIN_STATUS_ENUM_UINT32                 enCsStatus;
    NAS_MNTN_SEND_DOMAIN_STATUS_ENUM_UINT32                 enPsStatus;
}NAS_MNTN_SMS_MO_FAIL_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_MNTN_ACTIVE_FAIL_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 拨号失败事件，包括如下内容
             事件头部，NAS相关的SIM卡信息，位置信息，PDP激活失败原因，PS域注册状态
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;
    NAS_MNTN_PDP_ACTIVE_FAIL_STRU       stPsActiveFail;
}NAS_MNTN_ACTIVE_FAIL_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_MNTN_MSG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 短信相关ERROR LOG信息，包括MO短信失败计数器
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMoFailureCounter;
    VOS_UINT8                           ucMeFileErrorCounter;
    VOS_UINT8                           aucReserved1[2];
}NAS_MNTN_MSG_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_MNTN_SM_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SM相关ERROR LOG信息，包括PDP激活失败计数器
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPdpActiveFailureCounter;
    VOS_UINT8                           aucReserved1[3];
}NAS_MNTN_SM_INFO_STRU;

typedef struct
{
    NAS_MNTN_CS_UNAVAILABLE_INFO_STRU   stCsUnavailableInfo;
    NAS_MNTN_PS_UNAVAILABLE_INFO_STRU   stPsUnavailableInfo;
    NAS_MNTN_PLMN_AVAILABLE_STRU        stPlmnAvailableList;
    VOS_UINT8                           ucServiceUnavailableCounter;
    VOS_UINT8                           ucPlmnUnavailableCounter;
    VOS_UINT8                           aucReserved1[2];
}NAS_MNTN_MM_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_MNTN_CS_CHANNEL_OPEN_FAILURE_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CS域语音通道打开失败事件ERROR LOG信息，
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;                             /* NAS关心的SIM卡信息； */
    VOS_UINT16                          usPort;                                 /* 语音通道端口 */
    VOS_UINT8                           aucReserved1[2];                        /* 四字节对齐填充字段 */
    VOS_UINT32                          ulOmOperResult;                         /* OM打开的语音通道端口执行结果； */
}NAS_MNTN_CS_CHANNEL_OPEN_FAILURE_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_MNTN_CS_CHANNEL_OPEN_FAILURE_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : VC与MED握手超时事件ERROR LOG信息，
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;                             /* NAS关心的SIM卡信息； */
    VOS_UINT32                          ulTimerId;                              /* 定时器超时事件 */
} NAS_MNTN_CS_MED_TIMEOUT_EVENT_STRU;

#define MNTN_WAS_WEAK_SIGNAL_SAMPLE_NUMBER    (30)  /*Error LOG上报的间隔时间，30分钟报一次*/

/*****************************************************************************
 消息名称  : WAS_MNTN_FREQ_INFO_STRU
 功能描述  : 频率信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usUlUarfcn;   /* 上行频点 Integer(0 .. 16383),无效值0xFFFF */
    VOS_UINT16                          usDlUarfcn;   /* 下行频点,无效值0xFFFF                     */
} WAS_MNTN_FREQ_INFO_STRU;

/*****************************************************************************
 消息名称  : WAS_MNTN_NO_SIGNAL_EVENT_STRU
 功能描述  : 记录开机处于弱信号的信息结构
*****************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                  stHeader;
    MNTN_RAI_INFO_STRU                   stRai;
    WAS_MNTN_FREQ_INFO_STRU              stFreqInfo;
    VOS_UINT16                           usPSC;       /* 扰码 Integer(0..511) */
    VOS_INT16                            sRscp;
    VOS_INT16                            sECN0;
    VOS_UINT8                            aucReserve1[2];     /* 保留 */
}WAS_MNTN_NO_SIGNAL_EVENT_STRU;

/*****************************************************************************
 消息名称  : WAS_MNTN_WEAK_SIGNAL_SAMPLE_EVENT_STRU
 功能描述  : WAS发生弱信号时需要上报的小区信息结构
*****************************************************************************/
typedef struct
{
    MNTN_RAI_INFO_STRU                   stRai;       /*位置区或路由区信息 */
    WAS_MNTN_FREQ_INFO_STRU              stFreqInfo;  /* 上下行频点信息 */
    VOS_UINT16                           usPSC;       /* 扰码 Integer(0..511) */
    VOS_INT16                            sRscp;
    VOS_INT16                            sECN0;
    VOS_UINT16                           usErrlogIndex;/*弱信号发生在30分钟的第几分钟  */
}WAS_MNTN_WEAK_SIGNAL_CELL_INFO_STRU;

/*****************************************************************************
 消息名称  : WAS_MNTN_WEAK_SIGNAL_SAMPLE_EVENT_STRU
 功能描述  : WAS弱信号采样上报信息结构,30分钟报一次，
*****************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                  stHeader;
    VOS_UINT16                           usWeakSignalNum;    /* 30分钟内弱信号发生次数 */
    VOS_UINT8                            aucReserve2[2];     /* 保留 */
    WAS_MNTN_WEAK_SIGNAL_CELL_INFO_STRU  astWeakSignalCellInfo[MNTN_WAS_WEAK_SIGNAL_SAMPLE_NUMBER];/*发生弱信号时需要上报的小区信息*/
}WAS_MNTN_WEAK_SIGNAL_SAMPLE_EVENT_STRU;
/*****************************************************************************
 消息名称  : GAS_MNTN_INIT_WEAK_SIGNAL_EVT_STRU
 功能描述  : GAS开机后弱信号事件结构
*****************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    MNTN_RAI_INFO_STRU                  stRai;
    VOS_UINT16                          usArfcn;
    VOS_INT16                           sRxlev;
}GAS_MNTN_INIT_WEAK_SIGNAL_EVT_STRU;

/*****************************************************************************
 消息名称  : GAS_MNTN_WEAK_SIGNAL_INFO_STRU
 功能描述  : GAS弱信号相关信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucWeakSignalIndex;      /*弱信号发生在30分钟的第几分钟*/
    VOS_UINT8                           aucReserve1[3];
    MNTN_RAI_INFO_STRU                  stRai;                  /*弱信号发生小区相关信息:PLMN、LAC区、RAC区*/
    VOS_UINT16                          usArfcn;                /*频点号*/
    VOS_INT16                           sRxlev;                 /*信号强度，以dBm为单位*/
}GAS_MNTN_WEAK_SIGNAL_INFO_STRU;

/*****************************************************************************
 消息名称  : GAS_MNTN_PERIOD_WEAK_SIGNAL_LIST_EVT_STRU
 功能描述  : G模弱信号事件上报结构
*****************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                  stHeader;
    VOS_UINT8                            ucWeakSignalNum;                                       /*弱信号发生的次数*/
    VOS_UINT8                            aucReserve1[3];
    GAS_MNTN_WEAK_SIGNAL_INFO_STRU       astWeakSignalInfo[GAS_MNTN_WEAK_SIGNAL_LIST_MAX_NUM];  /*30分钟每分钟发生的弱信号及相关信息*/
} GAS_MNTN_PERIOD_WEAK_SIGNAL_LIST_EVT_STRU;

/*******************************************************************************
 结构名    : OAM_MNTN_NO_SIM_CARD_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 探测到无SIM卡事件，包括如下内容
             事件头部
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
}OAM_MNTN_NO_SIM_CARD_EVENT_STRU;

/*******************************************************************************
 结构名    : OAM_MNTN_SIM_CARD_LOST_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 探测到SIM卡掉卡事件，包括如下内容
             事件头部
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
}OAM_MNTN_SIM_CARD_LOST_EVENT_STRU;

/*******************************************************************************
 结构名    : OAM_MNTN_PCV_ERRLOG_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PC voice 异常
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
}OAM_MNTN_PCV_ERRLOG_EVENT_STRU;

/*******************************************************************************
 结构名    : OAM_MNTN_NV_ERRLOG_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : NV恢复 异常
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
}OAM_MNTN_NV_ERRLOG_EVENT_STRU;

/*******************************************************************************
 结构名    : OAM_MNTN_PORT_ERRLOG_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OM端口配置
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    VOS_UINT16                          usLineNum;
    VOS_UINT16                          usPortNum;
}OAM_MNTN_PORT_ERRLOG_EVENT_STRU;

/*******************************************************************************
 结构名    : MED_MNTN_CS_ERR_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MED ERR LOG EVENT
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    CODEC_OM_ERRLOG_EVENT_RPT_STRU      stMedErrLog;
}MED_MNTN_CS_ERR_EVENT_STRU;

/*******************************************************************************
 结构名    : HIGH_STACK_TASK_STR
 协议表格  :
 ASN.1描述 :
 结构说明  : DRV HIGH STACK EVENT
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU     stRecordHead;
    VOS_INT8                taskName[16] ;
    VOS_INT32               taskId;
    VOS_INT32               highStackSize;
    VOS_INT32               taskStackSize;
}HIGH_STACK_TASK_STR;

/*******************************************************************************
 结构名    : SD_TRANSFER_ERROR_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : 记录SD卡传输异常结构体
*******************************************************************************/
typedef struct
{
   VOS_UINT32 Ebe_int;
   VOS_UINT32 Ccd_int;
   VOS_UINT32 Sbe_int;
   VOS_UINT32 Hle_int;
   VOS_UINT32 Frun_int;
   VOS_UINT32 Hto_int;
   VOS_UINT32 Drto_int;
   VOS_UINT32 Rto_int;
   VOS_UINT32 Dcrc_int;
   VOS_UINT32 Rcrc_int;
   VOS_UINT32 Rxdr_int;
   VOS_UINT32 Txdr_int;
   VOS_UINT32 Dto_int;
   VOS_UINT32 Cd_int;
   VOS_UINT32 Re_int;
}SD_ERROR_REG_BIT_ST;

typedef struct
{
    MNTN_HEAD_INFO_STRU                  stRecordHead;
    SD_ERROR_REG_BIT_ST                  stSdErrLogGetFromInt;
}SD_TRANSFER_ERROR_ST;

/*******************************************************************************
 结构名    : OAM_MNTN_WD_COUNT_ERRLOG_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 计算资源使用情况
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    OSA_MNTN_WD_COUNT_ENUM_UINT32       enReason;
}OAM_MNTN_WD_COUNT_ERRLOG_EVENT_STRU;

/*******************************************************************************
 结构名    : OAM_MNTN_SOCP_ERROR_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 探测到SOCP通道错误事件，包括如下内容
             事件头部
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    VOS_UINT32                          ulChannelID;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          ulData;
}OAM_MNTN_SOCP_ERROR_EVENT_STRU;

/*******************************************************************************
 结构名    : OAM_MNTN_ICC_ERROR_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 探测到ICC通道错误事件，包括如下内容
             事件头部
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    VOS_UINT32                          ulChannelID;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          ulData;
}OAM_MNTN_ICC_ERROR_EVENT_STRU;

/*******************************************************************************
 结构名    : OAM_MNTN_SPY_ERROR_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 探测到高温保护事件，包括如下内容
             事件头部
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
}OAM_MNTN_SPY_ERROR_EVENT_STRU;


/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    MNTN_WRITEFLASH_EVENT_ENUM_UINT32   enMsgID;    /*_H2ASN_MsgChoice_Export MNTN_WRITEFLASH_EVENT_ENUM_UINT32*/
                                                    /* 为了兼容NAS的消息头定义，所以转换ASN.1使用MNTN_WRITEFLASH_EVENT_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MNTN_WRITEFLASH_EVENT_ENUM_UINT32
    ****************************************************************************/
}ERR_LOG_MSG_DATA;
/*_H2ASN_Length UINT32*/

/* 下面的数据结构请不要随意命名, 跟ASN生成dll相关 */
typedef struct
{
    VOS_UINT32                          ulInfoLen; /* _H2ASN_Skip */
    ERR_LOG_MSG_DATA                    stMsgData;
}ErrorLog_MSG;

/*****************************************************************************
  外部接口定义
*****************************************************************************/
extern VOS_UINT32 DIAG_ErrorLog(VOS_CHAR * cFileName,VOS_UINT32 ulFileId, VOS_UINT32 ulLine,
                VOS_UINT32 ulErrNo, VOS_VOID * pBuf, VOS_UINT32 ulLen);
#define MNTN_RecordErrorLog(ulErrNo,pBuf,ulLen) \
    DIAG_ErrorLog(__FILE__,THIS_FILE_ID,__LINE__,ulErrNo,pBuf,ulLen)

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

#endif/* end of ErrorLog.h */

