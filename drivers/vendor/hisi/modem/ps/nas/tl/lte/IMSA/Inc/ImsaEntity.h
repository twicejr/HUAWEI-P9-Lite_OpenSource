/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : ImsaEntity.h
    Description : IMSA实体头文件
    History     :
      1.sunbing 00049683    2013-04-22  Draft Enact


******************************************************************************/

#ifndef __IMSAENTITY_H__
#define __IMSAENTITY_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "product_config.h"
#include "ImsaIntraInterface.h"
#include "ImsaMsccInterface.h"
#include "TafApsApi.h"
#include "SpmImsaInterface.h"
#include "ImsaInterface.h"
#include "ImsaImsEvent.h"
#include "AtImsaInterface.h"
#include "ImsaNvInterface.h"
#include "CallImsaInterface.h"
#include "TafNvInterface.h"
#include "MsgImsaInterface.h"
#include "ImsaImsInterface.h"
#include "ImsaMtcInterface.h"
#if (FEATURE_ON == FEATURE_PTM)
#include "ImsaErrlogInterface.h"
#include "omringbuffer.h"
#endif

#include "ImsCodecInterface.h"
/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define IMSA_CALL_MAX_NUM               (7)
#define IMSA_CALL_NUMBER_MAX_NUM        (MN_CALL_MAX_BCD_NUM_LEN * 2)
#define IMSA_CALLED_NUMBER_MAX_NUM      (MN_CALL_MAX_CALLED_ASCII_NUM_LEN)
#define IMSA_REG_ADDR_PAIR_MAX_NUM      (4)     /*2个不同类型UE IP地址对应2个PCSCF地址*/

#define IMSA_PCSCF_MAX_NUM              (6)

#define IMSA_IPV6_ADDR_STRING_LEN       (46)
#define IMSA_IPV4_ADDR_STRING_LEN       (15)

/* "a1.a2.a3.a4 " */
#define IMSA_IPV4_ADDR_LEN              (4)

/* "a1...a16" */
#define IMSA_IPV6_ADDR_LEN              (16)

#define IMSA_MAX_APN_LEN                (99)

#define IMSA_MAX_PF_NUM                 (16)

#define IMSA_CONN_MAX_NORMAL_SIP_SIGNAL_PDP_NUM (2)
#define IMSA_CONN_MAX_NORMAL_SIP_MEDIA_PDP_NUM  (4)
#define IMSA_CONN_MAX_EMC_SIP_MEDIA_PDP_NUM     (4)


#define IMSA_MAX_UEID_BUF_SIZE                  (10)
#define IMSA_MAX_HOME_NET_DOMAIN_NAME_LEN       (128)
#define IMSA_MAX_IMPI_LEN                       (128)
#define IMSA_MAX_TIMPU_LEN                      (128)
#define IMSA_CONN_ILLEGAL_OPID                  (0)
#define IMSA_CONN_NORMAL_CONN_MIN_OPID_VALUE    (1)
#define IMSA_CONN_NORMAL_CONN_MAX_OPID_VALUE    (200)
#define IMSA_CONN_EMC_CONN_MIN_OPID_VALUE       (201)
#define IMSA_CONN_EMC_CONN_MAX_OPID_VALUE       (255)
#define IMSA_MAX_SUBSCRIPTION_NUM               (6)
#define IMSA_MAX_PASSWORD_LEN                   (32)

#define IMSA_SMS_TRUE                           1
#define IMSA_SMS_FALSE                          0

/* retrans define */
#define IMSA_SMR_RETRANS_PERMIT                 0
#define IMSA_SMR_RETRANS_NO_PERMIT              1
#define IMSA_SMR_RETRANS_PROCESS                2
#define IMSA_SMR_RETRANS_ABORT                  3

/* RP ERROR CAUSE */
#define  IMSA_SMR_ERR_CAUSE_MTI_MO_RP_ERROR                     4
#define  IMSA_SMR_ERR_CAUSE_NET_OUT_OF_ORDER                    38
#define  IMSA_SMR_ERR_CAUSE_TEMP_FAILURE                        41
#define  IMSA_SMR_ERR_CAUSE_CONGESTION                          42
#define  IMSA_SMR_ERR_CAUSE_RES_UNAVAIL                         47
#define  IMSA_SMR_ERR_CAUSE_VALUE_INVALID_MR                    81
#define  IMSA_SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR              96
#define  IMSA_SMR_ERR_CAUSE_VALUE_MSG_TYPE_NON_EXIST            97
#define  IMSA_SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE           98
#define  IMSA_SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR                  111
#define  IMSA_SMR_MSG_CHK_SUCCESS                               255
#define  IMSA_SMR_MSG_TOO_SHORT_ERROR                           254
#define  IMSA_SMR_ERR_UPPER_ABORT                               253

#define  IMSA_CALL_DTMF_BUF_MAX_NUM            (16)        /* 最多缓存DTMF信息个数 */

#define  IMSA_CONN_MAX_NIC_PDP_NUM              (3)

#define IMSA_VOICE_QCI                          (1)
#define IMSA_VIDEO_QCI                          (2)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/* wangchen : v7r2 diff from v9r1 because struct is diff 2014-06-18 */
typedef MN_CALL_DIR_ENUM_U8 MN_CALL_DIR_ENUM_UINT8;
typedef MN_CALL_MPTY_STATE_ENUM_U8 MN_CALL_MPTY_STATE_ENUM_UINT8;
typedef MN_CALL_MODE_ENUM_U8 MN_CALL_MODE_ENUM_UINT8;
typedef MN_CALL_EVENT_ENUM_U32 MN_CALL_EVENT_ENUM_UINT32;
typedef MN_CALL_TYPE_ENUM_U8 MN_CALL_TYPE_ENUM_UINT8;
typedef MN_CALL_CLIR_CFG_ENUM_U8 MN_CALL_CLIR_CFG_ENUM_UINT8;


/*****************************************************************************
    枚举名    : IMSA_CALL_STATUS_ENUM
    枚举说明  : 呼叫状态
*****************************************************************************/
enum    IMSA_CALL_STATUS_ENUM
{
    IMSA_CALL_STATUS_IDLE,
    IMSA_CALL_STATUS_DIALING,
    IMSA_CALL_STATUS_TRYING,
    IMSA_CALL_STATUS_ALERTING,
    IMSA_CALL_STATUS_ACTIVE,
    IMSA_CALL_STATUS_INCOMING,
    IMSA_CALL_STATUS_HELD,
    IMSA_CALL_STATUS_WAITING,
    IMSA_CALL_STATUS_BUTT
};
typedef VOS_UINT8 IMSA_CALL_STATUS_ENUM_UINT8;

/*****************************************************************************
    枚举名    : IMSA_CALL_CALL_REASON_RESOURCE_RESULT_ENUM_UINT8
    枚举说明  : 资源预留状态
*****************************************************************************/
enum    IMSA_CALL_CALL_REASON_RESOURCE_RESULT_ENUM
{
    IMSA_CALL_CALL_REASON_RESOURCE_READY,
    IMSA_CALL_CALL_REASON_RESOURCE_ONLY_VOICE,
    IMSA_CALL_CALL_REASON_RESOURCE_FAILED,
    IMSA_CALL_CALL_REASON_RESOURCE_RESULT_BUTT
};
typedef VOS_UINT8 IMSA_CALL_CALL_REASON_RESOURCE_RESULT_ENUM_UINT8;


/*****************************************************************************
    枚举名    : IMSA_CALL_MODE_ENUM
    枚举说明  : 呼叫方向
*****************************************************************************/
enum    IMSA_CALL_MODE_ENUM
{
    IMSA_CALL_MODE_VOICE,
    IMSA_CALL_MODE_DATA,
    IMSA_CALL_MODE_BUTT
};
typedef VOS_UINT8 IMSA_CALL_MODE_ENUM_UINT8;

/*****************************************************************************
    枚举名    : IMSA_CALL_NUM_TYPE_ENUM
    枚举说明  : 呼叫号码类型
*****************************************************************************/
// TODO: 如果这个号码也是用于SMS/USSD，则这里去掉CALL这个前缀
enum    IMSA_CALL_NUM_TYPE_ENUM
{
    IMSA_CALL_NUM_NATIONAL,
    IMSA_CALL_NUM_INTERNATIONAL,
    IMSA_CALL_NUM_BUTT
};
typedef VOS_UINT8 IMSA_CALL_NUM_TYPE_ENUM_UINT8;

/*****************************************************************************
    枚举名    : IMSA_REG_STATUS_ENUM
    枚举说明  : IMS注册状态
*****************************************************************************/
enum    IMSA_REG_STAUTS_ENUM
{
    IMSA_REG_STATUS_NOT_REGISTER,       /**< 未注册状态 */
    IMSA_REG_STATUS_REGISTERING,        /**< 正在注册状态 */
    IMSA_REG_STATUS_REGISTERED,         /**< 已注册状态 */
    IMSA_REG_STATUS_DEREGING,           /**< 正在去注状态 */
    IMSA_REG_STATUS_WAIT_RETRY,         /**< 正在等待重新尝试注册 */
    IMSA_REG_STATUS_PENDING,
    IMSA_REG_STATUS_ROLLING_BACK,
    IMSA_REG_STATUS_BUTT
};
typedef VOS_UINT8 IMSA_REG_STAUTS_ENUM_UINT8;

/*****************************************************************************
    枚举名    : IMSA_CAMPED_RAT_TYPE_ENUM
    枚举说明  : UE驻留的网络类型
*****************************************************************************/
enum    IMSA_CAMPED_RAT_TYPE_ENUM
{
    IMSA_CAMPED_RAT_TYPE_NULL                   = 0,
    IMSA_CAMPED_RAT_TYPE_GSM,
    IMSA_CAMPED_RAT_TYPE_UTRAN,
    IMSA_CAMPED_RAT_TYPE_EUTRAN,
    IMSA_CAMPED_RAT_TYPE_BUTT
};
typedef VOS_UINT8 IMSA_CAMPED_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
    枚举名    : IMSA_PS_SERVICE_STATUS_ENUM
    枚举说明  : 当前驻留网络PS域服务状态
*****************************************************************************/
enum    IMSA_PS_SERVICE_STATUS_ENUM
{
    IMSA_PS_SERVICE_STATUS_NORMAL_SERVICE       = 0,
    IMSA_PS_SERVICE_STATUS_LIMITED_SERVICE,
    IMSA_PS_SERVICE_STATUS_NO_SERVICE,
    IMSA_PS_SERVICE_STATUS_BUTT
};
typedef VOS_UINT8 IMSA_PS_SERVICE_STATUS_ENUM_UINT8;

/*****************************************************************************
    枚举名    : IMSA_IMS_VOPS_STATUS_ENUM
    枚举说明  : 当前网络是否支持IMS voice over PS session
*****************************************************************************/
enum    IMSA_IMS_VOPS_STATUS_ENUM
{
    IMSA_IMS_VOPS_STATUS_NOT_SUPPORT            = 0,
    IMSA_IMS_VOPS_STATUS_SUPPORT,
    IMSA_IMS_VOPS_STATUS_BUTT
};
typedef VOS_UINT8 IMSA_IMS_VOPS_STATUS_ENUM_UINT8;

/*****************************************************************************
    枚举名    : IMSA_IMS_VOPS_STATUS_ENUM
    枚举说明  : 当前网络是否支持EMS
*****************************************************************************/
enum    IMSA_EMS_STAUTS_ENUM
{
    IMSA_EMS_STAUTS_NOT_SUPPORT                 = 0,
    IMSA_EMS_STAUTS_SUPPORT,
    IMSA_EMS_STAUTS_BUTT
};
typedef VOS_UINT8 IMSA_EMS_STAUTS_ENUM_UINT8;



enum IMSA_PDP_TYPE_ENUM
{
    IMSA_PDP_TYPE_DEFAULT               = 0,                /**< 缺省承载 */
    IMSA_PDP_TYPE_DEDICATED             = 1,                /**< 专有承载 */
    IMSA_PDP_TYPE_EMERGENCY             = 2,                /**< 紧急承载 */

    IMSA_PDP_TYPE_BUTT
};
typedef VOS_UINT8  IMSA_PDP_TYPE_ENUM_UINT8;


enum IMSA_PDP_STATE_ENUM
{
    IMSA_PDP_STATE_INACTIVE  = 0,             /**< 上下文去激活态 */
    IMSA_PDP_STATE_ACTIVE,                    /**< 上下文激活状态 */

    IMSA_PDP_STATE_BUTT
};
typedef VOS_UINT8  IMSA_PDP_STATE_ENUM_UINT8;

enum IMSA_CONN_STATUS_ENUM
{
    IMSA_CONN_STATUS_IDLE               = 0,            /**< 不存在连接 */
    IMSA_CONN_STATUS_CONNING            = 1,            /**< 正在建立连接 */
    IMSA_CONN_STATUS_RELEASING          = 2,            /**< 正在释放连接 */
    IMSA_CONN_STATUS_CONN               = 3,            /**< 存在连接 */

    IMSA_CONN_STATUS_BUTT
};
typedef VOS_UINT8  IMSA_CONN_STATUS_ENUM_UINT8;


enum IMSA_STATUS_ENUM
{
    IMSA_STATUS_NULL                    = 0,            /**< 未开机 */
    IMSA_STATUS_STARTING                = 1,            /**< 开机中 */
    IMSA_STATUS_STOPING                 = 2,            /**< 关机中 */
    IMSA_STATUS_STARTED                 = 3,            /**< 已开机 */

    IMSA_STATUS_BUTT
};
typedef VOS_UINT8  IMSA_STATUS_ENUM_UINT8;

enum IMSA_ISIM_STATUS_ENUM
{
    IMSA_ISIM_STATUS_ABSENT             = 0,            /**< 无卡 */
    IMSA_ISIM_STATUS_UNAVAILABLE        = 1,            /**< 卡不可用，包括读取必须卡参数失败、PS域卡无效等 */
    IMSA_ISIM_STATUS_AVAILABLE          = 2,            /**< 卡有效可用 */

    IMSA_ISIM_STATUS_BUTT
};
typedef VOS_UINT8  IMSA_ISIM_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : IMSA_VOICE_DOMAIN_ENUM
 结构说明  : UE的Voice Domain类型
*****************************************************************************/
enum IMSA_VOICE_DOMAIN_ENUM
{
   IMSA_VOICE_DOMAIN_CS_ONLY         = 0,    /**< CS voice only */
   IMSA_VOICE_DOMAIN_IMS_PS_ONLY     = 1,    /**< IMS PS voice only */
   IMSA_VOICE_DOMAIN_CS_PREFERRED    = 2,    /**< CS voice preferred, IMS PS Voice as secondary */
   IMSA_VOICE_DOMAIN_IMS_PS_PREFERRED= 3,    /**< IMS PS voice preferred, CS Voice as secondary */

   IMSA_VOICE_DOMAIN_BUTT
};
typedef VOS_UINT32   IMSA_VOICE_DOMAIN_ENUM_UINT32;

/*****************************************************************************
 枚举名    : IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM
 结构说明  : 获取IMS普通服务的条件状况
*****************************************************************************/
enum IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM
{
   IMSA_NRM_SRV_CON_SAT_STATUE_SUCC                     = 0,    /**< 满足获取普通服务的条件 */
   IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_RAT_NOT_SUPPORT     = 1,    /**< 不满足获取普通服务的条件，原因为接入技术不支持 */
   IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_ROAM_NOT_SUPPORT    = 2,    /**< 不满足获取普通服务的条件，原因为不支持漫游注册 */
   IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_USIM_NOT_SUPPORT    = 3,    /**< 不满足获取普通服务的条件，原因为USIM卡不支持 */
   IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_VOICE_NOT_SUPPORT   = 4,    /**< 不满足获取普通服务的条件，原因为IMS语音不支持 */
   IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_REG_FORBIDDEN       = 5,    /**< 不满足获取普通服务的条件，原因为IMS注册被禁止 */
   IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_OTHERS              = 6,    /**< 不满足获取普通服务的条件，原因为其他 */

   IMSA_NRM_SRV_CON_SAT_STATUE_BUTT
};
typedef VOS_UINT32   IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM_UINT32;


/*****************************************************************************
 枚举名    : IMSA_SRV_STATUS_ENUM
 结构说明  : service状态枚举
*****************************************************************************/
enum IMSA_SRV_STATUS_ENUM
{
   IMSA_SRV_STATUS_IDLE_DEREG           = 0x00,    /**< IDLE&DEREG */
   IMSA_SRV_STATUS_CONNING_DEREG        = 0x10,    /**< CONNING&DEREG */
   IMSA_SRV_STATUS_CONNING_REG          = 0x13,    /**< CONNING&REG */
   IMSA_SRV_STATUS_RELEASING_DEREG      = 0x20,    /**< RELEASING&DEREG */
   IMSA_SRV_STATUS_CONN_DEREG           = 0x30,    /**< CONN&DEREG */
   IMSA_SRV_STATUS_CONN_REGING          = 0x31,    /**< CONN&REGING */
   IMSA_SRV_STATUS_CONN_DEREGING        = 0x32,    /**< CONN&DEREGING */
   IMSA_SRV_STATUS_CONN_REG             = 0x33,    /**< CONN&REG */

   IMSA_SRV_STATUS_BUTT                 = 0xff
};
typedef VOS_UINT8   IMSA_SRV_STATUS_ENUM_UINT8;

enum IMSA_SRV_DEREG_CAUSE_ENUM
{
    IMSA_SRV_DEREG_CAUSE_MSCC_DEREG_REQ      = 0x0000,

    IMSA_SRV_DEREG_CAUSE_BUTT
};
typedef VOS_UINT32  IMSA_SRV_DEREG_CAUSE_ENUM_UINT32;

enum IMSA_SMS_SMR_STATE_ENUM
{
    IMSA_SMS_SMR_STATE_IDLE,
    IMSA_SMS_SMR_STATE_WAIT_FOR_RP_ACK,
    IMSA_SMS_SMR_STATE_WAIT_TO_SND_RP_ACK,
    IMSA_SMS_SMR_STATE_WAIT_FOR_RETRANS_TIMER,
    IMSA_SMS_SMR_STATE_BUTT
};
typedef VOS_UINT8 IMSA_SMS_SMR_STATE_ENUM_UINT8;

enum IMSA_CALL_DTMF_STATE_ENUM
{
    IMSA_CALL_DTMF_IDLE                  = 0,                                    /* 当前DTMF空闲 */
    IMSA_CALL_DTMF_WAIT_START_CNF,                                               /* 发出了START请求后等待回复 */
    IMSA_CALL_DTMF_WAIT_STOP_CNF,                                                /* 发出了STOP请求后等待回复 */
    IMSA_CALL_DTMF_WAIT_AUTO_STOP_CNF,                                           /* 定时器超时自动发出STOP请求后等待回复 */
    IMSA_CALL_DTMF_WAIT_TIME_OUT,                                                /* 启动DTMF定时器后等待超时 */

    IMSA_CALL_DTMF_STATE_BUTT
};
typedef VOS_UINT8 IMSA_CALL_DTMF_STATE_ENUM_UINT8;

enum
{
    IMSA_USSD_IDLE_STATE               = 0, /* IDLE态 */
    IMSA_USSD_MO_CONN_STATE            = 1, /* UE主动发起的连接状态 */
    IMSA_USSD_MT_CONN_STATE            = 2, /* 网侧主动发起的连接状态 */

    IMSA_USSD_BUTT_STATE                    /* 无效值 */
};
typedef VOS_UINT8   IMSA_USSD_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : IMSA_OM_CONN_FORBIDDEN_CAUSE_ENUM
 结构说明  : CONN FORBIDDEN原因
*****************************************************************************/
enum IMSA_OM_CONN_FORBIDDEN_CAUSE_ENUM
{
    IMSA_OM_PDN_REJ_CAUSE_IN_TEMP_LIST  = 0,    /* PDN REJ原因值在临时列表中 */
    IMSA_OM_PDN_REJ_CAUSE_IN_PERM_LIST  = 1,    /* PDN REJ原因值在永久列表中 */
    IMSA_OM_PDN_TIMER_OUT_MAX_TIMES     = 2,    /* PDN建立超时 */

    IMSA_OM_CONN_FORBIDDEN_CAUSE_BUTT
};
typedef VOS_UINT32 IMSA_OM_CONN_FORBIDDEN_CAUSE_ENUM_UINT32;

typedef struct
{

    HTIMER                              phTimer;            /* Timer句柄 */
    VOS_UINT16                          usName;             /* 即 IMSA_TIMER_ID_ENUM_UINT16*/
    VOS_UINT16                          usPara;             /* 即 IMSA_TIMER_ID_ENUM_UINT16*/
    VOS_UINT8                           ucMode;             /* timer work mode
                                                               VOS_RELTIMER_LOOP   -- start periodically
                                                               VOS_RELTIMER_NOLOOP -- start once time */
    VOS_UINT8                           ucResv[3];
    VOS_UINT32                          ulTimerLen;         /* Timer时长(UNIT: ms) */
}IMSA_TIMER_STRU;

/*****************************************************************************
    枚举名    : IMSA_TIMER_RUN_STA_ENUM
    枚举说明  : 定时器的状态:正在运行,停止
*****************************************************************************/
enum    IMSA_TIMER_RUN_STA_ENUM
{
    IMSA_TIMER_RUNNING                = 0x00,
    IMSA_TIMER_STOPED,
    IMSA_TIMER_INVALID,

    IMSA_TIMER_BUTT
};
typedef VOS_UINT32   IMSA_TIMER_RUN_STA_ENUM_UINT32;


/*****************************************************************************
 结构名    : NAS_EMM_TIMER_INFO_STRU
 结构说明  : log出EMM定时器运行情况
 1.日    期   : 2012年12月03日
   作    者   : n00181501
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;
    IMSA_TIMER_RUN_STA_ENUM_UINT32          enTimerStatus;   /* 定时器状态*/

    VOS_UINT16                               usTimerId;       /* 定时器ID*/
    VOS_UINT16                               usRsv;
    VOS_UINT32                               ulTimerRemainLen;/* 定时器的时长 */
}IMSA_TIMER_INFO_STRU;

/*****************************************************************************
 结构名    : IMSA_REG_ADDR_PAIR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 地址对结构定义
*****************************************************************************/
typedef struct
{
    VOS_UINT8                   ucCid;                  /**< 存储释放承载的CID */
    IMSA_IP_TYPE_ENUM_UINT8     enIpType;               /**< 存储释放承载的PDN类型 */
    VOS_UINT8                   acRsv1[2];

    VOS_CHAR                    acUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1];        /**< UE地址 */
    VOS_UINT8                   ucRsv2;

    VOS_CHAR                    acPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1];     /**< P-CSCF地址 */
    VOS_UINT8                   ucRsv3;
}IMSA_REG_PARA_INFO_STRU;

/*****************************************************************************
 结构名    : IMSA_REG_ADDR_PAIR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 地址对结构定义
*****************************************************************************/
typedef struct tag_IMSA_REG_ADDR_PAIR_STRU
{
    struct tag_IMSA_REG_ADDR_PAIR_STRU *pstNext;

    VOS_UINT8                   ucPriority;                                     /**< 改地址对的优先级，插入时排序 */

    VOS_UINT8                   ucHasTryed;                                     /**< 该地址对是否被尝试过 */
    IMSA_IP_TYPE_ENUM_UINT8     enIpType;                                       /**< 地址类型， IPv4 或者 IPv6 */
    VOS_UINT8                   ucRsv1;

    VOS_CHAR                    acUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1];        /**< UE地址 */
    VOS_UINT8                   ucRsv2;

    VOS_CHAR                    acPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1];     /**< P-CSCF地址 */
    VOS_UINT8                   ucRsv3;
}IMSA_REG_ADDR_PAIR_STRU;

/*****************************************************************************
 结构名    : IMSA_REG_PCSCF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : P-CSCF地址结构定义
*****************************************************************************/
typedef struct
{
    IMSA_IP_TYPE_ENUM_UINT8     enIpType;                                       /**< P-CSCF地址类型，IPv4或者IPv6 */
    IMSA_PCSCF_SRC_TYPE_UINT8   enSrcType;                                      /**< P-CSCF地址来源 */
    VOS_UINT8                   aucRsv[2];

    VOS_CHAR                    acIpAddr[IMSA_IPV6_ADDR_STRING_LEN + 1];        /**< P-CSCF地址内容 */
    VOS_UINT8                   ucRsv;
}IMSA_REG_PCSCF_STRU;

/*****************************************************************************
 结构名    : IMSA_REG_ADDR_PAIR_MGR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 地址对管理模块结构定义
*****************************************************************************/
typedef struct
{
    VOS_CHAR                    acUeAddrIpv4[IMSA_IPV4_ADDR_STRING_LEN + 1];    /**< UE的IPv4地址 */

    VOS_CHAR                    acUeAddrIpv6[IMSA_IPV6_ADDR_STRING_LEN + 1];    /**< UE的IPv6地址 */
    VOS_UINT8                   ucRsv;

    IMSA_REG_PCSCF_STRU         astPcscfs[IMSA_PCSCF_MAX_NUM];                   /**< UE获取到的所有P-CSCF地址 */

    IMSA_REG_ADDR_PAIR_STRU    *pstCurrent;                                     /**< 当前地址对 */

    IMSA_REG_ADDR_PAIR_STRU    *pstIpv6List;                                    /**< IPv6地址对列表 */
    IMSA_REG_ADDR_PAIR_STRU    *pstIpv4List;                                    /**< IPv4地址对列表 */
}IMSA_REG_ADDR_PAIR_MGR_STRU;

/*****************************************************************************
 结构名    : IMSA_SAVED_IMS_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 呼叫或注册管理模块保存的当前正在执行的IMS命令
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpImsMsg:1;      /**< 是否有保存的IMS消息 */
    VOS_UINT32                          bitOpRsv   :31;

    VOS_UINT32                          ulCsmReason;        /**< 保存当前正在执行的D2 IMS指令 */
    VOS_UINT32                          ulCsmId;            /**< 保存当前正在执行的D2 IMS指令opid*/
}IMSA_SAVED_IMS_MSG_STRU;

typedef struct
{
    VOS_UINT8                               ucTempForbFeatureFlag;  /* 临时被禁特性控制开关 */
    VOS_UINT8                               ucPermForbFeatureFlag;  /* 永久被禁特性控制开关 */
    VOS_UINT8                               ucRsv[2];
    IMSA_NV_REG_TEMP_REJ_CAUSE_LIST_STRU    stRegTempRejCauseList;  /* 注册临时被拒原因值列表 */
    IMSA_NV_REG_PERM_REJ_CAUSE_LIST_STRU    stRegPermRejCauseList;  /* 注册永久被拒原因值列表 */
}IMSA_REG_REJ_FORBIDDEN_CTRL_STRU;


/*****************************************************************************
 结构名    : IMSA_REG_ENTITY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 注册实体结构定义
*****************************************************************************/
typedef struct
{
    IMSA_REG_STAUTS_ENUM_UINT8          enStatus;           /**< 注册状态 */
    VOS_UINT8                           ucRetryCnt;         /**< 失败重试次数 */
    IMSA_REG_TYPE_ENUM_UINT8            enRegType;          /**< 注册类型 */

    IMSA_REG_STAUTS_ENUM_UINT8          enExceptedStatus;

    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enPendingRegParam;

    VOS_UINT32                          ulPendingDeregParam;

    VOS_UINT32                          ulRetryTimes;       /**< 尝试次数 */

    IMSA_TIMER_STRU                     stRetryTimer;       /**< 失败重试定时器 */

    IMSA_TIMER_STRU                     stProtectTimer;     /**< 保护定时器 */

    IMSA_REG_ADDR_PAIR_MGR_STRU         stPairMgrCtx;       /**< 注册地址对信息 */
    VOS_UINT8                           ucImsaUsimNormOpid;
    VOS_UINT8                           ucImsaUsimEmcOpid;
    VOS_UINT8                           aucRsv[1];
    VOS_UINT8                           ucTryRegTimes;       /**< 周期尝试IMS注册次数 */
    IMSA_TIMER_STRU                     stPeriodTryRegTimer; /**< 新增周期尝试IMS注册定时器 */
    IMSA_TIMER_STRU                     stWaitResourceTimer;    /**< 等待资源申请结果定时器 */
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enAddrType;             /**< 再次发起注册时，使用的地址对类型 */

}IMSA_REG_ENTITY_STRU;

/*****************************************************************************
 结构名    : IMSA_REG_MANAGER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 注册管理信息上下文
*****************************************************************************/
typedef struct
{
    IMSA_REG_RETRY_POLICY_ENUM_UINT32   enRetryPolicy;      /**< 注册失败后的重试策略 */

    VOS_UINT32                          ulMaxTime;          /**< RFC5626计算重试时间时的maxtime，单位秒 */
    VOS_UINT32                          ulBaseTime;         /**< RFC5626计算重试时间时的basetime，单位秒 */
    VOS_UINT32                          ulReregPeriod;      /**< SIP刷新注册时间，单位秒 */
    VOS_UINT32                          ulRetryPeriod;      /**< 注册失败后周期性重试时间间隔，单位秒 */

    VOS_UINT32                          ulSaveRetryTimes;   /**< 保存NV配置的IMS注册失败重新尝试次数 */

    IMSA_REG_ENTITY_STRU                stNormalRegEntity;  /**< 普通注册实体 */
    IMSA_REG_ENTITY_STRU                stEmcRegEntity;     /**< 紧急注册实体 */

    IMSA_SAVED_IMS_MSG_STRU             stImsMsg;           /**< IMS正在执行消息 */

    IMSA_REG_REJ_FORBIDDEN_CTRL_STRU    stRegRejForbCtrl;
} IMSA_REG_MANAGER_STRU;


typedef struct
{
    VOS_UINT16                          usImsMinPort;           /* IMS端口号范围下限 */
    VOS_UINT16                          usImsMaxPort;           /* IMS端口号范围上限 */

}IMSA_IMS_PORT_CONFIG_STRU;


typedef IMSA_NV_IMS_REDIAL_CFG_STRU IMSA_IMS_REDIAL_CFG_STRU;

typedef IMSA_NV_CMCC_CUSTOM_REQ_STRU IMSA_CMCC_CUSTOM_REQ_STRU;

typedef struct
{
    VOS_UINT8                           ucGsmImsSupportFlag;    /**< GSM IMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucUtranImsSupportFlag; /**< UNTRAN IMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucLteImsSupportFlag;    /**< LTE IMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucGsmEmsSupportFlag;    /**< GSM EMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */

    VOS_UINT8                           ucRoamingImsNotSupportFlag; /**< 漫游网络下IMS使能项，VOS_TRUE:支持 VOS_FALSE:不支持 */
    VOS_UINT8                           aucReserved[3];

    VOS_UINT8                           ucUtranEmsSupportFlag; /**< UNTRAN EMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucLteEmsSupportFlag;    /**< LTE EMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucVoiceCallOnImsSupportFlag;    /**< IMS语音使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucVideoCallOnImsSupportFlag;        /**< IMS视频使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */

    VOS_UINT8                           ucSmsOnImsSupportFlag;          /**< IMS短信使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucSrvccOnImsSupportFlag;            /**< IMS Srvcc使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucSrvccMidCallOnImsSupportFlag;     /**< IMS SrvccMidCall使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucSrvccAlertingOnImsSupportFlag;    /**< IMS SrvccAlerting使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */

    VOS_UINT8                           ucSrvccPreAlertingOnImsSupportFlag; /**< IMS SrvccPreAlerting使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucSrvccTiFlag;                      /**< IMS SrvccPreAlerting,VOS_TRUE :0 R10版本,VOS_FALSE R11之后版本 */
    VOS_UINT8                           ucNoCardEmcCallSupportFlag;/**< 无卡紧急呼使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucUeRelMediaPdpFLag;    /**< UE主动释放媒体承载标识 */

    VOS_UINT8                           ucImsLocDeregSigPdpRelFlag;/**< IMS普通信令被动释放后本地IMS去注册标识 */
    VOS_UINT8                           ucAuthType;  /**< IMS ucAuthType,0 :AKA,1:DIGIST */
    VOS_CHAR                            aucPassWord[IMSA_PASSWORD_LEN]; /**< DIGIST鉴权时，使用的密码 */
    VOS_UINT8                           ucUserInfoFlag;/**< 0:从USIM读IMPI，IMPU,DOMAIN   1:从NV读取IMPI，IMPU,DOMAIN */

    IMSA_VOICE_DOMAIN_ENUM_UINT32       enVoiceDomain;          /**< voice domain preferrece */
    IMSA_IMS_PORT_CONFIG_STRU           stImsPortConfig;        /**< IMS 端口配置信息 */

    IMSA_IMS_REDIAL_CFG_STRU            stImsRedialCfg;         /**< IMS域内重播配置 */
    IMSA_CMCC_CUSTOM_REQ_STRU           stCMCCCustomReq;        /**< 中国移动定制需求 */
}IMSA_CONFIG_PARA_STRU;

typedef struct
{
    IMSA_CAMPED_RAT_TYPE_ENUM_UINT8     enImsaCampedRatType;        /**< 当前驻留网络,NULL,2G,3G,LTE */
    IMSA_IMS_VOPS_STATUS_ENUM_UINT8     enImsaImsVoPsStatus;        /**< 当前网络是否支持IMS voice over PS session */
    IMSA_EMS_STAUTS_ENUM_UINT8          enImsaEmsStatus;            /**< 当前网络是否支持EMS */
    IMSA_PS_SERVICE_STATUS_ENUM_UINT8   enImsaPsServiceStatus;      /**< 当前网络的PS服务状态:无服务,受限服务,正常服务 */
    VOS_UINT8                           ucImsaRoamingFlg;           /**< VOS_TRUE :漫游，VOS_FALSE :非漫游 */
    MSCC_IMSA_ACCESS_TYPE_ENUM_UINT8    enAccessType;
    VOS_UINT8                           aucReserved[2];
    VOS_UINT16                          usLac;
    VOS_UINT16                          usTac;
    MSCC_IMSA_PLMN_ID_STRU              stPlmnId;
    VOS_UINT32                          ulCellId;
}IMSA_NETWORK_INFO_STRU;

/*****************************************************************************
 结构名称: IMSA_IMPI_STRU
 结构说明: Private User Identity结构，参见23.003 13.3
           "<IMSI>@ims.mnc<MNC>.mcc<MCC>.3gppnetwork.org"
*****************************************************************************/
typedef struct
{
    VOS_CHAR                            acImpi[IMSA_MAX_IMPI_LEN + 1]; /**< 默认49字节 */
    VOS_UINT8                           aucReserved[3];
}IMSA_IMPI_STRU;

/*****************************************************************************
 结构名称: IMSA_TIMPU_STRU
 结构说明: Tempory Public User Identity结构，参见23.003 13.4B
           "sip:<IMSI>@ims.mnc<MNC>.mcc<MCC>.3gppnetwork.org"
*****************************************************************************/
typedef struct
{
    VOS_CHAR                            acTImpu[IMSA_MAX_TIMPU_LEN + 1]; /**< 默认53字节 */
    VOS_UINT8                           aucReserved[3];
}IMSA_TIMPU_STRU;


/*==============================================================================
结构名称    : IMSA_UEID_STRU
使用说明    :
              1)IMEI, IMEISV的存放格式按照 31.102 4.2.2执行
              2)IMPI,IMPU按照23.003 13.3和12.4B
==============================================================================*/
typedef struct
{
    VOS_UINT32                          bitOpImei     :1;
    VOS_UINT32                          bitOpImpi     :1;
    VOS_UINT32                          bitOpTImpu    :1;
    VOS_UINT32                          bitOpRsv      :29;

    VOS_CHAR                            acImei[IMSA_IMS_IMEI_LEN + 1];          /**< IMEI */
    IMSA_IMPI_STRU                      stImpi;                                 /**< IMPI */
    IMSA_TIMPU_STRU                     stTImpu;
}IMSA_UEID_STRU;


/*****************************************************************************
 结构名称: IMSA_HOME_NET_DOMAIN_NAME_STRU
 结构说明: Home network domain name结构，参见23.003 13.2
           "ims.mnc<MNC>.mcc<MCC>.3gppnetwork.org"
*****************************************************************************/
typedef struct
{
    VOS_CHAR                            acHomeNetDomainName[IMSA_MAX_HOME_NET_DOMAIN_NAME_LEN + 1]; /**< 默认33字节 */
    VOS_UINT8                           aucReserved[3];
}IMSA_HOME_NET_DOMAIN_NAME_STRU;

typedef struct
{
    VOS_UINT32                          bitOpHomeNetDomainName  :1;
    VOS_UINT32                          bitOpRsv                :31;

    IMSA_UEID_STRU                      stImsaUeId;                 /**< ue id */
    IMSA_HOME_NET_DOMAIN_NAME_STRU      stHomeNetDomainName;        /**< Home network domain name */
}IMSA_COMMON_INFO_STRU;
/*****************************************************************************
 结构名    : IMSA_CALL_SPM_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 呼叫模块保存的当前正在处理的SPM发送过来的呼叫相关的命令
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpSpmMsg:1;      /**< 是否有保存的SPM命令 */
    VOS_UINT32                          bitOpRsv:31;

    VOS_UINT32                          ulSpmMsgId;         /**< SPM命令 */

    VOS_UINT16                          usClientId;         /**< Client Id */
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulOpId;             /**< SPM命令的opid */
    VOS_UINT32                          ulCallId;           /**< 呼叫Id */

    union
    {
        MN_CALL_ORIG_PARAM_STRU         stOrigParam;        /**< 呼叫建立命令的参数 */
        MN_CALL_SUPS_PARAM_STRU         stSupsParam;        /**< 增值服务命令的参数 */
        TAF_CALL_ECONF_DIAL_REQ_STRU     stEconfDialParam;   /**< 增强型多方通话的参数 */
        TAF_CALL_ECONF_CALL_LIST_STRU    stEconfAddParam;    /**< 增强多方通话添加用户的参数*/
    } stParam;                                              /**< SPM命令对应的参数 */
}IMSA_CALL_SPM_MSG_STRU;
/*****************************************************************************
 结构名    : IMSA_CALL_NUMBER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 呼叫实体定义
*****************************************************************************/
typedef struct
{
    IMSA_CALL_NUM_TYPE_ENUM_UINT8       enNumType;                             /**< 呼叫号码类型 */
    VOS_UINT8                           aucRsv[2];
    VOS_CHAR                            aucNumber[IMSA_CALL_NUMBER_MAX_NUM + 1];   /**< 实际号码 *//* FOR OVERFLOW 0831 */
}IMSA_CALL_NUMBER_STRU;

/*****************************************************************************
 结构名    : IMSA_CALLED_NUMBER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 呼叫实体定义
*****************************************************************************/
typedef struct
{
    IMSA_CALL_NUM_TYPE_ENUM_UINT8       enNumType;                             /**< 呼叫号码类型 */
    VOS_UINT8                           aucRsv[2];
    VOS_CHAR                            aucNumber[IMSA_CALLED_NUMBER_MAX_NUM+1]; /**< 实际号码 *//* FOR OVERFLOW 0831 */
}IMSA_CALLED_NUMBER_STRU;
typedef struct {
    VOS_UINT32                              bitOpIsUsed      :1;
    VOS_UINT32                              bitOpErrorInfo   :1;    /**< 是否包含错误信息 */
    VOS_UINT32                              bitOpRsv         :30;

    IMSA_IMS_ECONF_CALLER_STATE_ENUM_UINT8  enCallState;
    VOS_UINT8                               ucTi;
    VOS_CHAR                                acAlpha[IMSA_IMS_ALPHA_STRING_SZ + 1];
    VOS_UINT8                               aucRsv;
    IMSA_CALL_NUMBER_STRU                   stCallNumber;   /**< 主叫号码 */
    IMSA_CALLED_NUMBER_STRU                 stCalledNumber; /**< 被叫号码 */
    IMSA_CALL_NUMBER_STRU                   stConnectNumber;   /**< 连接号码 */
    IMSA_CALL_NUMBER_STRU                   stRedirectNumber;   /**< 连接号码 */
    IMSA_IMS_OUTPUT_ERROR_STRU              stErrorCode;
}IMSA_CALL_ECONF_SUMMARY_STRU;

/*****************************************************************************
 结构名    : IMSA_CALL_ENTITY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 呼叫实体定义
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpIsUsed             :1;    /**< 呼叫实体是否被使用 */
    VOS_UINT32                          bitOpRetryCsCall        :1;    /**< CS域是否可以再尝试 */
    VOS_UINT32                          bitOpLocalAlerting      :1;    /**< 是否使用本地振铃 */
    VOS_UINT32                          bitOpNeedSendResResult  :1;    /**< 是否需要给IMS发送资源预留结果, 1 为需要， 0 不需要 */
    VOS_UINT32                          bitOpErrorInfo          :1;    /**< 是否包含错误信息 */
    VOS_UINT32                          bitOpTransToCs          :1;    /**< 该路电话是否转入CS域 */
    VOS_UINT32                          bitOpRsv                :26;

    VOS_UINT8                           ucSpmcallId;           /**< IMSA和SPM间交互的呼叫id */
    IMSA_CALL_STATUS_ENUM_UINT8         enStatus;       /**< 呼叫状态 */
    IMSA_CALL_TYPE_ENUM_UINT8           enType;         /**< 呼叫类型 */

    MN_CALL_DIR_ENUM_UINT8              enDir;          /**< 呼叫方向 */
    MN_CALL_MPTY_STATE_ENUM_UINT8       enMpty;         /**< 是否多方呼叫  */
    MN_CALL_MODE_ENUM_UINT8             enMode;         /**< 呼叫模式 */

    VOS_UINT16                          usClientId;         /**< Client Id */
    VOS_UINT32                          ulOpId;             /**< SPM命令的opid */

    IMSA_EMC_CALL_TYPE_ENUM_UINT32      enEmcType;      /**< 紧急呼类型 */

    IMSA_CALL_NUMBER_STRU               stCallNumber;   /**< 主叫号码 */
    IMSA_CALLED_NUMBER_STRU             stCalledNumber; /**< 被叫号码 */

    IMSA_CALL_NUMBER_STRU               stConnectNumber;   /**< 连接号码 */
    IMSA_CALL_NUMBER_STRU               stRedirectNumber;   /**< 连接号码 */

    VOS_UINT32                          ulResRspOpId;   /**< 等待资源结果的opid，由IMS分配 */
    IMSA_CALL_SPM_MSG_STRU              stSpmMsg;       /**< MO时触发此呼叫的SPM消息，如果呼叫被网侧380拒绝，需要重新发起紧急类型呼叫时用到 */
    IMSA_IMS_CALL_ERROR_STRU            stImsError;
    MN_CALL_DISC_DIR                    stDiscDir;      /* 挂断电话的方向 */

    VOS_UINT8                           ucRedialTimes;  /* 重播次数 */
    VOS_UINT8                           ucCallEntityIndex;      /* 实体索引号 */
    VOS_UINT8                           ucImscallId;           /**< IMSA和IMS间交互的呼叫id */
    VOS_UINT8                           ucIsEconfFlag;  /**< 是否是增强多方通话的标识 */
    VOS_UINT8                           ucMaxUserNum;
    VOS_UINT8                           ucCurUserNum;
    VOS_UINT8                           ucTqosExpFlag;
    VOS_UINT8                           ucIsImsaRelCallFlag;    /**< 是否是IMSA主动挂断的电话 */

    IMSA_CALL_ECONF_SUMMARY_STRU        stEconfCalllist[IMSA_IMS_ECONF_CALLED_MAX_NUM];    /* 增强多方通话的成员列表 */
}IMSA_CALL_ENTITY_STRU;

/*****************************************************************************
 结构名    : IMSA_CALL_DTMF_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DTMF信息结果
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallId;
    VOS_CHAR                            cKey;                                   /* DTMF Key */
    VOS_UINT16                          usOnLength;                             /* DTMF持续时间，0: 代表停止DTMF */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucSpmOpId;
    VOS_UINT8                           ucRsv;
    VOS_UINT32                          ulImsOpid;
} IMSA_CALL_DTMF_INFO_STRU;


/*****************************************************************************
 结构名    : IMSA_CALL_DTMF_CTX_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DTMF上下文
*****************************************************************************/
typedef struct
{
    IMSA_CALL_DTMF_STATE_ENUM_UINT8     enDtmfState;                            /**< dmtf 状态 */
    VOS_UINT8                           ucDtmfCnt;                              /**< dtmf缓存个数 */
    VOS_UINT8                           aucRsv[2];
    IMSA_TIMER_STRU                     stDtmfDurationTimer;                    /**< dmtf duration定时器 */
    IMSA_TIMER_STRU                     stDtmfProtectTimer;                     /**< dmtf 保护定时器 */
    IMSA_CALL_DTMF_INFO_STRU            stCurrentDtmf;                          /**< 为了防止CALL和DTMF操作同时进行，因此分开存储
                                                                                     例如DTMF duration定时器操作IMSA发stop dtmf之后，为收到IMS响应之前，下SWAP操作等 */

    IMSA_CALL_DTMF_INFO_STRU            stDtmfBufList[IMSA_CALL_DTMF_BUF_MAX_NUM];  /**< dtmf缓存数组 */
}IMSA_CALL_DTMF_CTX_STRU;


/*****************************************************************************
 结构名    : IMSA_CALL_MANAGER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 呼叫管理模块上下文
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallNum;              /**< 呼叫个数 */
    VOS_UINT8                           aucRsv[3];
    IMSA_CALL_ENTITY_STRU               astCallEntity[IMSA_CALL_MAX_NUM];   /**< 所有呼叫实体 */

    IMSA_CALL_SPM_MSG_STRU              stSpmMsg;               /**< 保存当前正在执行的SPM消息 */
    IMSA_SAVED_IMS_MSG_STRU             stImsMsg;               /**< IMS正在执行消息 */

    IMSA_TIMER_STRU                     stProctectTimer;        /**< 保护定时器 */
    IMSA_TIMER_STRU                     stResReadyTimer;        /**< 等待资源Ready的定时器 */



    VOS_UINT8                           ucVoiceBearExistFlag;    /**< 记录语音媒体承载是否存在 */
    VOS_UINT8                           ucVideoBearExistFlag;    /**< 记录视频媒体承载是否存在 */
    VOS_UINT8                           aucRsv2[2];

    VOS_UINT8                           ucRetryEmcRegFlag;      /**< 紧急呼叫收到#380，重新发起注册的标识 */
    VOS_UINT8                           ucCallEntityIndex;      /**< 第一次紧急呼叫，使用的呼叫实体的ID */
    VOS_UINT8                           ucId;                   /**< 第一次紧急呼叫，使用的CALL ID */
    VOS_UINT8                           ucRsv2;

    VOS_UINT32                          ulLastResult;           /**< 最后失败原因 */
    VOS_UINT32                          ulLastStatusCode;       /**< 最后失败时服务器的原因值 */

    VOS_UINT8                           ucIsTcallTimeOutProc;   /**< 记录Tcall定时器超时处理 */
    VOS_UINT8                           aucReserve[3];

    VOS_UINT32                          ulSrvccFlag;            /**< 标记是否在SRVCC过程中 */
    VOS_UINT32                          ulNotReprotAllReleasedFlag;  /**< 标记不能上报ALL RELEASED事件 */
    IMSA_CALL_DTMF_CTX_STRU             stDtmfCtx;              /**< DTMF上下文 */

    IMSA_TIMER_STRU                     stBackOffTxTimer;       /*SSAC Tx定时器*/
    IMSA_TIMER_STRU                     stBackOffTyTimer;       /*SSAC Ty定时器*/

    IMSA_TIMER_STRU                     stRedialMaxTimer;       /* IMS域内重播最大时长定时器 */
    IMSA_TIMER_STRU                     stRedialIntervelTimer;  /* IMS域内重播间隔定时器 */

    IMSA_TIMER_STRU                     stNormalTcallTimer;     /* 普通呼叫Tcall定时器，用于语音和视频呼叫 */
    IMSA_TIMER_STRU                     stEmcTcallTimer;        /* 紧急呼叫Tcall定时器 */
}IMSA_CALL_MANAGER_STRU;



typedef struct
{
                                        /*保存SPM消息*/
    VOS_UINT32                          ulSpmOpId;/*SPM */
    /*保存发送给IMS的消息*/
    VOS_UINT32                          ulImsOpId;
}IMSA_MSG_MANAGER_STRU;

typedef struct
{
    AT_IMSA_IMS_REG_STATE_REPORT_ENUM_UINT32        enCireg;
    AT_IMSA_IMSVOPS_CAPABILITY_ENUM_UINT32          enReport;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           enMode;

}IMSA_AT_CONTROL_STRU;
typedef union
{
    SPM_IMSA_CALL_ORIG_REQ_STRU         stOrigReq;
    SPM_IMSA_CALL_SUPS_CMD_REQ_STRU     stSupsCmdReq;
    SPM_IMSA_CALL_START_DTMF_REQ_STRU   stStartDtmfReq;
    SPM_IMSA_CALL_STOP_DTMF_REQ_STRU    stStopDtmfReq;
    SPM_IMSA_PROCESS_USSD_REQ_STRU      stProcUssdReq;
} IMSA_SRVCC_BUFF_MSG_UNION;

typedef struct
{
    VOS_UINT8                           ucBuffMsgNum;
    VOS_UINT8                           aucReserved[3];
    IMSA_SRVCC_BUFF_MSG_UNION           aucBuffMsgArray[IMSA_CALL_MSG_SYNC_MAX_NUM];
}IMSA_SRVCC_BUFFER_STRU;

typedef IMSA_NV_PCSCF_DISCOVERY_POLICY_STRU IMSA_PCSCF_DISCOVERY_POLICY_INFO_STRU;


typedef struct
{
    IMSA_STATUS_ENUM_UINT8              enImsaStatus;       /**< IMSA状态:未开机、开机过程中、已开机、关机过程中*/
    IMSA_ISIM_STATUS_ENUM_UINT8         enImsaIsimStatus;   /**< ISIM卡状态 */
    VOS_UINT8                           ucImsaUsimStatus;   /**< USIM卡状态 */
    IMSA_SRV_CONN_STATUS_EXIST_ENUM_UINT8  enIsImsSrvExist;    /**< 是否IMS业务存在: 0表示不存在，1表示存在*/
    IMSA_TIMER_STRU                     stProtectTimer;     /**< 开关机保护定时器 */
    IMSA_CONFIG_PARA_STRU               stImsaConfigPara;   /**< IMS配置参数 */
    IMSA_NETWORK_INFO_STRU              stImsaNetworkInfo;  /**< 网络环境参数 */
    IMSA_COMMON_INFO_STRU               stImsaCommonInfo;   /**< IMSA公共信息 */
    IMSA_TIMER_STRU                     stPeriodImsSrvTryTimer;/**< 周期性尝试IMS服务定时器 */
    IMSA_TIMER_STRU                     stTempForbiddenTimer;/**< Pnd临时被拒惩罚定时器 */

    /* delete PeriodImsEmcSrvTryTimer */
    IMSA_SRV_STATUS_ENUM_UINT8          enNrmSrvStatus;     /**< 普通service状态 */
    IMSA_SRV_STATUS_ENUM_UINT8          enEmcSrvStatus;     /**< 紧急service状态 */

    MTC_IMSA_MODEM_POWER_STATE_ENUM_UINT8  enPowerState;    /**< Modem1开关机状态 */
    MSCC_IMSA_STOP_TYPE_ENUM_UINT32     enStopType;         /**< 关机请求的类型 */
    VOS_UINT8                           ucIsCardLocked;     /**< SIM卡是否被锁: 0表示没有被锁，1表示被锁 */

    IMSA_SRV_DEREG_CAUSE_ENUM_UINT32    enDeregCause;           /**< 去注册起因*/
    IMSA_INTRA_MSG_QUEUE_STRU           stImsaIntraMsgQueue;    /**< 内部消息队列 */

    IMSA_AT_CONTROL_STRU                stAtControl;
    IMSA_SRVCC_BUFFER_STRU              stSrvccBuffer;          /**< SRVCC过程缓存 */
    IMSA_SAVED_IMS_MSG_STRU             stImsMsg;               /**< IMS正在执行消息 */

    IMSA_REG_PARA_INFO_STRU             stNrmRegParaInfo;          /**< 存储当前普通注册信息 */
    IMSA_REG_PARA_INFO_STRU             stEmcRegParaInfo;          /**< 存储当前紧急注册信息 */

    IMSA_PCSCF_DISCOVERY_POLICY_INFO_STRU    stPcscfDiscoveryPolicyInfo;/**< 存储P-CSCF获取策略及相应的地址 */

    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enNrmAddrType;  /**< 注册时使用的地址队类型 */
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enEmcAddrType;  /**< 注册时使用的地址队类型 */
    IMSA_ERR_LOG_REG_CONDITION_STATUS_STRU  stRegConditionStatus;
    #endif
    VOS_UINT8                          ucIsImsRegForbidden;    /**< 用于记录IMS注册是否被禁止，0:不禁止；1:禁止 */
    VOS_UINT8                          aucRsv[3];
    IMSA_TIMER_STRU                     stGetSerProtectTimer;/**< 获取IMS服务时长保护定时器 */
    IMSA_TIMER_STRU                     stDeregSerProtectTimer;/**< 获取IMS服务时长保护定时器 */

    VOS_UINT8                           ucDsdsNvCfgStatus;        /**< VOS_TRUE: 控制DSDS的NV打开；*/
    VOS_UINT8                           aucRsv2[3];
}IMSA_CONTROL_MANAGER_STRU;

/*****************************************************************************
 结构名称: IMSA_PDP_IPV4_DNS_STRU
 结构说明: IPv4 DNS地址结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPriDns   : 1;
    VOS_UINT32                          bitOpSecDns   : 1;
    VOS_UINT32                          bitOpSpare    : 30;

    VOS_UINT8                           aucPriDns[IMSA_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecDns[IMSA_IPV4_ADDR_LEN];
}IMSA_PDP_IPV4_DNS_STRU;

/*****************************************************************************
 结构名称: IMSA_PDP_IPV4_PCSCF_STRU
 结构说明: IPv4 P-CSCF地址结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimPcscfAddr  : 1;
    VOS_UINT32                          bitOpSecPcscfAddr   : 1;
    VOS_UINT32                          bitOpThiPcscfAddr   : 1;
    VOS_UINT32                          bitOpSpare          : 29;

    VOS_UINT8                           aucPrimPcscfAddr[IMSA_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecPcscfAddr[IMSA_IPV4_ADDR_LEN];
    VOS_UINT8                           aucThiPcscfAddr[IMSA_IPV4_ADDR_LEN];
} IMSA_PDP_IPV4_PCSCF_STRU;

/*****************************************************************************
 结构名称: IMSA_PDP_IPV6_PCSCF_STRU
 结构说明: IPv6 P-CSCF地址结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimPcscfAddr  : 1;
    VOS_UINT32                          bitOpSecPcscfAddr   : 1;
    VOS_UINT32                          bitOpThiPcscfAddr   : 1;
    VOS_UINT32                          bitOpSpare          : 29;

    VOS_UINT8                           aucPrimPcscfAddr[IMSA_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecPcscfAddr[IMSA_IPV6_ADDR_LEN];
    VOS_UINT8                           aucThiPcscfAddr[IMSA_IPV6_ADDR_LEN];
} IMSA_PDP_IPV6_PCSCF_STRU;

/*****************************************************************************
 结构名称   : IMSA_PDP_IPV6_DNS_STRU
 结构说明   : IPv6 DNS地址结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPriDns     : 1;
    VOS_UINT32                          bitOpSecDns     : 1;
    VOS_UINT32                          bitOpSpare      : 30;

    VOS_UINT8                           aucPriDns[IMSA_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecDns[IMSA_IPV6_ADDR_LEN];
} IMSA_PDP_IPV6_DNS_STRU;

/*****************************************************************************
 结构名    : IMSA_IP_ADDRESS_STRU
 结构说明  : IP地址的结构体
*****************************************************************************/
typedef struct
{
    IMSA_IP_TYPE_ENUM_UINT8             enIpType;
    VOS_UINT8                           ucReserved[3];
    VOS_UINT8                           aucIpV4Addr[IMSA_IPV4_ADDR_LEN];
    VOS_UINT8                           aucIpV6Addr[IMSA_IPV6_ADDR_LEN];
}IMSA_IP_ADDRESS_STRU;


typedef struct
{
    VOS_UINT32                          bitOpRmtIpv4AddrAndMask     : 1;
    VOS_UINT32                          bitOpRmtIpv6AddrAndMask     : 1;
    VOS_UINT32                          bitOpProtocolId             : 1;
    VOS_UINT32                          bitOpSingleLocalPort        : 1;
    VOS_UINT32                          bitOpLocalPortRange         : 1;
    VOS_UINT32                          bitOpSingleRemotePort       : 1;
    VOS_UINT32                          bitOpRemotePortRange        : 1;
    VOS_UINT32                          bitOpSecuParaIndex          : 1;
    VOS_UINT32                          bitOpTypeOfService          : 1;
    VOS_UINT32                          bitOpFlowLabelType          : 1;
    VOS_UINT32                          bitOpSpare                  : 22;

    VOS_UINT8                           ucPacketFilterId;
    VOS_UINT8                           ucNwPacketFilterId;
    IMSA_PF_TRANS_DIRECTION_ENUM_UINT8  enDirection;
    VOS_UINT8                           ucPrecedence;                           /* packet filter evaluation precedence */

    VOS_UINT32                          ulSecuParaIndex;                        /* SPI */
    VOS_UINT16                          usSingleLcPort;
    VOS_UINT16                          usLcPortHighLimit;
    VOS_UINT16                          usLcPortLowLimit;
    VOS_UINT16                          usSingleRmtPort;
    VOS_UINT16                          usRmtPortHighLimit;
    VOS_UINT16                          usRmtPortLowLimit;
    VOS_UINT8                           ucProtocolId;                           /* 协议号 */
    VOS_UINT8                           ucTypeOfService;                        /* TOS */
    VOS_UINT8                           ucTypeOfServiceMask;                    /* TOS Mask */
    VOS_UINT8                           aucReserved[1];

    /* aucRmtIpv4Address[0]为IP地址高字节位
       aucRmtIpv4Address[3]为低字节位 */
    VOS_UINT8                           aucRmtIpv4Address[IMSA_IPV4_ADDR_LEN];

    /* aucRmtIpv4Mask[0]为IP地址高字节位 ,
       aucRmtIpv4Mask[3]为低字节位*/
    VOS_UINT8                           aucRmtIpv4Mask[IMSA_IPV4_ADDR_LEN];

    /* ucRmtIpv6Address[0]为IPv6接口标识高字节位
       ucRmtIpv6Address[7]为IPv6接口标识低字节位 */
    VOS_UINT8                           aucRmtIpv6Address[IMSA_IPV6_ADDR_LEN];

    /* ucRmtIpv6Mask[0]为高字节位
       ucRmtIpv6Mask[7]为低字节位*/
    VOS_UINT8                           aucRmtIpv6Mask[IMSA_IPV6_ADDR_LEN];

    VOS_UINT32                          ulFlowLabelType;                        /*FlowLabelType*/
}IMSA_PDP_TFT_STRU;
typedef struct
{
    VOS_UINT32                          ulPfNum;            /**< 承载过滤器数 */
    IMSA_PDP_TFT_STRU                   astTftInfo[IMSA_MAX_PF_NUM];    /**< 承载过滤器信息 */
}IMSA_PDP_TFT_INFO_STRU;

typedef struct
{
    VOS_UINT8               ucTrafficClass;                                     /**< UMTS承载服务优化类型 */
    VOS_UINT8               ucDeliverOrder;                                     /**< SDU队列是否发送UMTS承载 */
    VOS_UINT8               ucDeliverErrSdu;                                    /**< SDU错误是否发送 */
    VOS_UINT8               aucRsv1[1];
    VOS_UINT16              usMaxSduSize;                                       /**< SDU大小最大值 */
    VOS_UINT8               aucRsv2[2];
    VOS_UINT32              ulMaxBitUl;                                         /**< 上行最大速率 kbits/s */
    VOS_UINT32              ulMaxBitDl;                                         /**< 下行最大速率 kbits/s */
    VOS_UINT8               ucResidualBer;
    VOS_UINT8               ucSduErrRatio;                                      /**< SDU误码率 */
    VOS_UINT16              usTransDelay;                                       /**< 传输延时, 单位毫秒 */
    VOS_UINT8               ucTraffHandlePrior;                                 /**< 处理UMTS承载的SDU对比其他承载的SDU */
    VOS_UINT8               aucRsv3[1];
    VOS_UINT8               ucSrcStatisticsDescriptor;
    VOS_UINT8               ucSignallingIndication;
    VOS_UINT32              ulGuarantBitUl;                                     /**< 保证上行传输速率 kbits/s */
    VOS_UINT32              ulGuarantBitDl;                                     /**< 保证下行传输速率 kbits/s */
}IMSA_PDP_UMTS_QOS_STRU;

typedef struct
{
    /* 0 QCI is selected by network
       [1 - 4]value range for guranteed bit rate Traffic Flows
       [5 - 9]value range for non-guarenteed bit rate Traffic Flows */
    VOS_UINT8                           ucQCI;

    VOS_UINT8                           aucReserved[3];

    /* DL GBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulDLGBR;

    /* UL GBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulULGBR;

    /* DL MBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulDLMBR;

    /* UL MBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulULMBR;
}IMSA_PDP_EPS_QOS_STRU;


/*****************************************************************************
 结构名称: IMSA_PDP_APN_STRU
 结构说明: APN结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;
    VOS_UINT8                           aucValue[IMSA_MAX_APN_LEN];
} IMSA_PDP_APN_STRU;


typedef struct
{
    VOS_UINT32                          bitOpLinkedPdpId    : 1;
    VOS_UINT32                          bitOpPdpAddr        : 1;
    VOS_UINT32                          bitOpTft            : 1;
    /*VOS_UINT32                          bitOpApn            : 1;*/
    VOS_UINT32                          bitOpSpare          : 29;


    VOS_UINT8                           ucPdpId;            /**< 承载号 */
    VOS_UINT8                           ucLinkedPdpId;      /**< 与此承载关联的缺省承载号 承载类型为专有时生效 */
    VOS_UINT8                           ucCid;              /**< 此承载对应的CID */
    VOS_UINT8                           ucReserved1;

    IMSA_PDP_STATE_ENUM_UINT8           enPdpState;         /**< 承载状态 */
    IMSA_PDP_TYPE_ENUM_UINT8            enPdpType;          /**< 承载类型 */
    VOS_UINT8                           aucReserved2[2];
    IMSA_IP_ADDRESS_STRU                stPdpAddr;          /**< 承载IP地址 */
    /*IMSA_PDP_APN_STRU                   stApn;*/              /**< 承载APN信息 */

    IMSA_PDP_IPV4_DNS_STRU              stPdpIpv4Dns;       /**< 承载IPV4 DNS信息 */
    IMSA_PDP_IPV4_PCSCF_STRU            stPdpIpv4Pcscf;     /**< 承载IPV4 P-CSCF信息 */
    IMSA_PDP_IPV6_DNS_STRU              stPdpIpv6Dns;       /**< 承载IPV6 DNS信息 */
    IMSA_PDP_IPV6_PCSCF_STRU            stPdpIpv6Pcscf;     /**< 承载IPV6 P-CSCF信息 */

    IMSA_PDP_EPS_QOS_STRU               stEpsQos;           /**< 承载EPS QOS信息 */
    IMSA_PDP_TFT_INFO_STRU              stTft;              /**< 承载TFT信息 */
}IMSA_PDP_CNTXT_INFO_STRU;

typedef struct
{
    VOS_UINT32                          bitOpLinkdCid       : 1;
    VOS_UINT32                          bitOpPdnType        : 1;
    VOS_UINT32                          bitOpApn            : 1;
    VOS_UINT32                          bitOpGwAuthInfo     : 1;
    VOS_UINT32                          bitOpEmergencyInd   : 1;
    VOS_UINT32                          bitOpIpv4AddrAllocType: 1;
    VOS_UINT32                          bitOpPcscfDiscovery : 1;
    VOS_UINT32                          bitOpImCnSignalFlg  : 1;
    VOS_UINT32                          bitOpImsSuppFlg     : 1;
    VOS_UINT32                          bitOpSpare          : 23;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucLinkdCid;
    TAF_PDP_TYPE_ENUM_UINT8             enPdnType;
    TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8 enIpv4AddrAllocType;

    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyInd;
    TAF_PDP_PCSCF_DISCOVERY_ENUM_UINT8  enPcscfDiscovery;
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;
    VOS_UINT8                           ucImsSuppFlg;
    VOS_UINT8                           ucReserved;

    TAF_PDP_APN_STRU                    stApnInfo;
    TAF_GW_AUTH_STRU                    stGwAuthInfo;
}IMSA_SEL_SDF_PARA_STRU;

typedef struct
{
    IMSA_CONN_STATUS_ENUM_UINT8         enImsaConnStatus;   /**< 连接状态 */
    IMSA_IP_TYPE_ENUM_UINT8             enFirstReqPdnType;  /**< 最初请求的PDN类型 */
    IMSA_IP_TYPE_ENUM_UINT8             enCurReqPdnType;    /**< 当前请求的PDN类型 */
    VOS_UINT8                           ucIsApnChanged;     /**< 请求的APN和承载激活消息中的APN是否发生变化 */


    IMSA_TIMER_STRU                     stProtectTimer;     /**< 保护定时器,IMS拨号和去拨号定时器 */
    VOS_UINT8                           ucOpid;             /**< 标识流程 */
    VOS_UINT8                           ucCurMaxOpid;       /**< 当前分配出去的最大OPID */

    IMSA_SEL_SDF_PARA_STRU              stSelSdfPara;       /**< 选中拨号的SDF信息 */

    VOS_UINT32                          ulSipSignalPdpNum;  /**< SIP信令承载数 */
    IMSA_PDP_CNTXT_INFO_STRU            astSipSignalPdpArray[IMSA_CONN_MAX_NORMAL_SIP_SIGNAL_PDP_NUM];  /**< SIP信令承载信息 */

    VOS_UINT32                          ulSipMediaPdpNum;   /**< SIP媒体承载数 */
    IMSA_PDP_CNTXT_INFO_STRU            astSipMediaPdpArray[IMSA_CONN_MAX_NORMAL_SIP_MEDIA_PDP_NUM];    /**< SIP媒体承载信息 */
}IMSA_NORMAL_CONN_STRU;

typedef struct
{
    IMSA_CONN_STATUS_ENUM_UINT8         enImsaConnStatus;   /**< 连接状态 */
    IMSA_IP_TYPE_ENUM_UINT8             enFirstReqPdnType;  /**< 最初请求的PDN类型 */
    IMSA_IP_TYPE_ENUM_UINT8             enCurReqPdnType;    /**< 当前请求的PDN类型 */
    VOS_UINT8                           ucIsApnChanged;     /**< 请求的APN和承载激活消息中的APN是否发生变化 */

    IMSA_TIMER_STRU                     stProtectTimer;     /**< 保护定时器,IMS拨号和去拨号定时器 */
    VOS_UINT8                           ucOpid;             /**< 标识流程 */
    VOS_UINT8                           ucCurMaxOpid;       /**< 当前分配出去的最大OPID */

    IMSA_SEL_SDF_PARA_STRU              stSelSdfPara;       /**< 选中拨号的SDF信息 */

    IMSA_PDP_CNTXT_INFO_STRU            stSipSignalPdp;     /**< SIP信令承载信息 */

    VOS_UINT32                          ulSipMediaPdpNum;   /**< SIP媒体承载数 */
    IMSA_PDP_CNTXT_INFO_STRU            astSipMediaPdpArray[IMSA_CONN_MAX_EMC_SIP_MEDIA_PDP_NUM];/**< SIP媒体承载信息 */
}IMSA_EMC_CONN_STRU;

typedef struct
{
    VOS_UINT8                           ucPdpId;            /**< 承载号 */
    VOS_UINT8                           ucIsUsed;           /**< 使用标识 1:使用  0:未使用 */
    VOS_UINT8                           ucIsEmc;            /**< 紧急标识 1:紧急  0:非紧急 */
    VOS_UINT8                           ucResv;
    IMSA_IP_ADDRESS_STRU                stPdpAddr;          /**< 承载IP地址 */
}IMSA_CONN_NIC_PDP_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    IMSA_CONN_NIC_PDP_INFO_STRU         astNicPdpInfoArray[IMSA_CONN_MAX_NIC_PDP_NUM]; /* 配置给NIC的PDP信息 */

}IMSA_PRINT_NIC_PDP_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulCauseNum;
    TAF_PS_CAUSE_ENUM_UINT32            aenPsCause[TAF_NV_IPV6_FALLBACK_EXT_CAUSE_MAX_NUM];
}IMSA_IPV6_FALLBACK_EXT_CAUSE_STRU;

typedef struct
{
    VOS_UINT32                              ulTempForbFeatureFlag;  /* 临时被禁特性控制开关 */
    VOS_UINT32                              ulPermForbFeatureFlag;  /* 永久被禁特性控制开关 */
    IMSA_NV_PDN_TEMP_REJ_CAUSE_LIST_STRU    stPdnTempRejCauseList;  /* PDN临时被拒原因值列表 */
    IMSA_NV_PDN_PERM_REJ_CAUSE_LIST_STRU    stPdnPermRejCauseList;  /* PDN永久被拒原因值列表 */
}IMSA_PDN_REJ_FORBIDDEN_CTRL_STRU;

typedef struct
{
    IMSA_NORMAL_CONN_STRU               stNormalConn;       /**< 普通连接 */
    IMSA_EMC_CONN_STRU                  stEmcConn;          /**< 紧急连接 */

    IMSA_CONN_NIC_PDP_INFO_STRU         astNicPdpInfoArray[IMSA_CONN_MAX_NIC_PDP_NUM]; /* 配置给NIC的PDP信息 */

    IMSA_IPV6_FALLBACK_EXT_CAUSE_STRU   stIpv6FallBackExtCause;

    IMSA_PDN_REJ_FORBIDDEN_CTRL_STRU        stPdnRejForbCtrl;
}IMSA_CONN_MANAGER_STRU;

typedef struct
{
    IMSA_SMS_SMR_STATE_ENUM_UINT8       enState;                /* SMR实体状态                              */
    VOS_UINT8                           ucMessageReference;     /* Message Reference                        */
    VOS_UINT8                           ucMemAvailFlg;          /* 标志是否是通知过程                       */
    VOS_UINT8                           ucRetransFlg;           /* 是否重传标志                             */
    IMSA_TIMER_STRU                     stTR1MTimer;            /* TR1M TIMER信息                                */
    IMSA_TIMER_STRU                     stTRAMTimer;            /* TRAM TIMER信息                                */
}IMSA_SMS_SMR_MO_STRU;

typedef struct
{
    IMSA_SMS_SMR_STATE_ENUM_UINT8       enState;                                /* SMR MT实体状态                              */
    VOS_UINT8                           ucMessageReference;                     /* Message Reference                        */
    VOS_UINT8                           aucReserved2[2];
    IMSA_TIMER_STRU                     stTimerInfo;                              /* TIMER信息                                */
}IMSA_SMS_SMR_MT_STRU;

typedef struct
{
    IMSA_SMS_SMR_MO_STRU                stImsaSmrMo;
    IMSA_SMS_SMR_MT_STRU                stImsaSmrMt;
}IMSA_SMS_MANAGER_STRU;


typedef struct
{
    AT_IMSA_IMS_REG_STATE_REPORT_ENUM_UINT32        enCireg;
    AT_IMSA_IMSVOPS_CAPABILITY_ENUM_UINT32          enReport;

}IMSA_AT_MANAGER_STRU;

typedef struct
{
    IMSA_USSD_STATE_ENUM_UINT8          enUssdState;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    IMSA_TIMER_STRU                     stUssdWaitNetRspTimer;
    IMSA_TIMER_STRU                     stUssdWaitAppRspTimer;
}IMSA_USSD_MANAGER_STRU;

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 结构名称   :IMSA_ERRLOG_CTRL_INFO_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : IMSA_ERRLOG_CTRL_INFO_STRU信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucErrLogCtrlFlag;   /* ERRLOG开关标识 */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usAlmLevel;       /* 等级 */
}IMSA_ERRLOG_CTRL_INFO_STRU;
/*****************************************************************************
 结构名称   :IMSA_ERRLOG_BUFF_INFO_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : IMSA_ERRLOG_BUFF_INFO_STRU信息
*****************************************************************************/
typedef struct
{
    OM_RING_ID                          pstRingBuffer;  /* IMSA层buffer的地址 */
    VOS_UINT32                          ulOverflowCnt;  /* Ringbuf溢出的次数 */
}IMSA_ERRLOG_BUFF_INFO_STRU;
/*****************************************************************************
 结构名称   :IMSA_ERRORLOG_MANAGER_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : ERROR LOG的控制信息
*****************************************************************************/
typedef struct
{
    IMSA_ERRLOG_CTRL_INFO_STRU       stCtrlInfo;
    IMSA_ERRLOG_BUFF_INFO_STRU       stBuffInfo;
}IMSA_ERRORLOG_MANAGER_STRU;
#endif

/*****************************************************************************
 结构名称   :IMSA_HIFI_DATA_BUFFER_NODE_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : HIFI语音包的缓存信息
*****************************************************************************/
typedef struct tagIMSA_HIFI_DATA_BUFFER_NODE_STRU
{
    IMSA_VOICE_RX_DATA_IND_STRU               *pstRxDataInd;           /* 缓存的发送给HIFI的语音包 */
    struct tagIMSA_HIFI_DATA_BUFFER_NODE_STRU *pstNextBufferData;      /* 链表的下一个节点 */
}IMSA_HIFI_DATA_BUFFER_NODE_STRU;
/*****************************************************************************
 结构名称   :IMSA_HIFI_DATA_MANAGER_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : HIFI语音包的控制信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHifiDataControlFlag;  /* 是否开启Hifi消息控制: TRUE:开启；FALSE:关闭 */
    VOS_UINT8                           ucSentDataNum;          /* 给HIFI发送的数据包数量 */
    VOS_UINT8                           ucBufferDataNum;        /* 本地缓存的数据包数量 */
    VOS_UINT8                           ucHifiDataNeedAckNum;   /* 连发多少条消息后需要Hifi回复 */
    VOS_UINT8                           ucHifiDatMaxBufferNum;  /* 最大缓存消息条数 */
    VOS_UINT8                           ucRsv[3];               /* 保留 */
    VOS_UINT32                          ulOpid;                 /* Opid值，用来同步消息 */
    VOS_UINT32                          ulDataLoseNum;
    VOS_UINT32                          ulTotalDataLoseNum;
    VOS_UINT32                          ulDataBufferNum;
    VOS_UINT32                          ulTotalDataBufferNum;

    IMSA_HIFI_DATA_BUFFER_NODE_STRU    *pstBufferDataHead;      /* 缓存消息的链表头 */
    IMSA_HIFI_DATA_BUFFER_NODE_STRU    *pstBufferDataTail;      /* 当前缓存消息的节点 */
    IMSA_TIMER_STRU                     stHifiAckProtectTimer;  /* 等待HIFI回执的保护定时器 */
}IMSA_HIFI_DATA_MANAGER_STRU;
typedef struct
{
    IMSA_CONTROL_MANAGER_STRU           stImsaControlManager;   /**< 控制中心管理信息 */
    IMSA_REG_MANAGER_STRU               stImsaRegManager;       /**< 注册管理信息 */
    IMSA_CONN_MANAGER_STRU              stImsaConnManager;      /**< 连接管理信息 */
    IMSA_CALL_MANAGER_STRU              stImsaCallManager;      /**< 呼叫管理信息 */
    IMSA_SMS_MANAGER_STRU               stImsaSmsManager;       /**< SMS控制实体*/
    IMSA_USSD_MANAGER_STRU              stImsaUssdManager;
    /*USSD/SS控制实体*/
    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_ERRORLOG_MANAGER_STRU          stImsaErrorlogManager;  /**< ERROR LOG管理信息 */
    #endif
    IMSA_HIFI_DATA_MANAGER_STRU         stImsaHifiDataManager;  /**< HIFI语音包的控制信息*/

} IMSA_ENTITY_STRU;

#if (FEATURE_ON == FEATURE_PTM)
typedef struct
{
    TAF_PS_CAUSE_ENUM_UINT32                enCause;    /* TAF REJ CAUSE */
    IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32   enImsaCnRejCause; /* IMSA REJ CAUSE */
}IMSA_CN_CAUSE_TRANS_STRU;
#endif

/*****************************************************************************
 结构名称   :IMSA_PDN_REJ_FORB_NV_INFO_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   :Pdn Rej NV配置可维可测
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;

    IMSA_PDN_REJ_FORBIDDEN_CTRL_STRU        stPdnRejForbCtrl;
}IMSA_PDN_REJ_FORB_NV_INFO_STRU;

/*****************************************************************************
 结构名称   :IMSA_OM_CONN_FORBIDDEN_INFO
 协议表格   :
 ASN.1 描述 :
 结构说明   :信令连接建立被禁可维可测
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                  ulMsgId;
    IMSA_OM_CONN_FORBIDDEN_CAUSE_ENUM_UINT32    enCause;
    IMSA_NV_PDN_TEMP_REJ_CAUSE_LIST_STRU        stPdnTempRejCauseList;  /* PDN临时被拒原因值列表 */
    IMSA_NV_PDN_PERM_REJ_CAUSE_LIST_STRU        stPdnPermRejCauseList;  /* PDN永久被拒原因值列表 */
}IMSA_OM_CONN_FORBIDDEN_INFO;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern    IMSA_ENTITY_STRU     *pgstImsaEntity;
extern    IMSA_ENTITY_STRU      g_stImsaEntity;

/* CONN实体的相关宏 */
#define IMSA_CONN_GetConnManagerAddr()      (&pgstImsaEntity->stImsaConnManager)
#define IMSA_CONN_GetNormalConnAddr()       (&pgstImsaEntity->stImsaConnManager.stNormalConn)
#define IMSA_CONN_GetEmcConnAddr()          (&pgstImsaEntity->stImsaConnManager.stEmcConn)
#define IMSA_CONN_GetNormalConnOpid()       (IMSA_CONN_GetNormalConnAddr()->ucOpid)
#define IMSA_CONN_GetEmcConnOpid()          (IMSA_CONN_GetEmcConnAddr()->ucOpid)
#define IMSA_CONN_SetNormalConnOpid(ucOpid) (IMSA_CONN_GetNormalConnOpid() = (ucOpid))
#define IMSA_CONN_SetEmcConnOpid(ucOpid)    (IMSA_CONN_GetEmcConnOpid() = (ucOpid))
#define IMSA_CONN_GetNormalConnCurMaxOpid() (IMSA_CONN_GetNormalConnAddr()->ucCurMaxOpid)
#define IMSA_CONN_GetEmcConnCurMaxOpid()    (IMSA_CONN_GetEmcConnAddr()->ucCurMaxOpid)
#define IMSA_CONN_SetNormalConnCurMaxOpid(ucCurMaxOpid) (IMSA_CONN_GetNormalConnCurMaxOpid() = (ucCurMaxOpid))
#define IMSA_CONN_SetEmcConnCurMaxOpid(ucCurMaxOpid)    (IMSA_CONN_GetEmcConnCurMaxOpid() = (ucCurMaxOpid))
#define IMSA_CONN_GetNormalConnStatus()     (IMSA_CONN_GetNormalConnAddr()->enImsaConnStatus)
#define IMSA_CONN_GetEmcConnStatus()        (IMSA_CONN_GetEmcConnAddr()->enImsaConnStatus)
#define IMSA_CONN_GetNormalConnSelSdfParaAddr()         (&(IMSA_CONN_GetNormalConnAddr()->stSelSdfPara))
#define IMSA_CONN_GetEmcConnSelSdfParaAddr()            (&(IMSA_CONN_GetEmcConnAddr()->stSelSdfPara))
#define IMSA_CONN_GetNormalConnProtectTimerAddr()       (&(IMSA_CONN_GetNormalConnAddr()->stProtectTimer))
#define IMSA_CONN_GetEmcConnProtectTimerAddr()          (&(IMSA_CONN_GetEmcConnAddr()->stProtectTimer))
#define IMSA_CONN_GetNormalConnFirstReqPdnType()        (IMSA_CONN_GetNormalConnAddr()->enFirstReqPdnType)
#define IMSA_CONN_GetEmcConnFirstReqPdnType()           (IMSA_CONN_GetEmcConnAddr()->enFirstReqPdnType)
#define IMSA_CONN_GetNormalConnCurReqPdnType()          (IMSA_CONN_GetNormalConnAddr()->enCurReqPdnType)
#define IMSA_CONN_GetEmcConnCurReqPdnType()             (IMSA_CONN_GetEmcConnAddr()->enCurReqPdnType)
#define IMSA_CONN_GetPdnRejForbCtrlAddr()               (&pgstImsaEntity->stImsaConnManager.stPdnRejForbCtrl)
#define IMSA_CONN_GetPdnTempRejCauseListAddr()          (&pgstImsaEntity->stImsaConnManager.stPdnRejForbCtrl.stPdnTempRejCauseList)
#define IMSA_CONN_GetPdnPermRejCauseListAddr()          (&pgstImsaEntity->stImsaConnManager.stPdnRejForbCtrl.stPdnPermRejCauseList)

#define IMSA_CONN_GetConnFirstReqPdnType(enConnType, enFirstReqPdnType)\
        {\
            if (IMSA_CONN_TYPE_NORMAL == (enConnType))\
            {\
                (enFirstReqPdnType) = IMSA_CONN_GetNormalConnFirstReqPdnType();\
            }\
            else\
            {\
                (enFirstReqPdnType) = IMSA_CONN_GetEmcConnFirstReqPdnType();\
            }\
        }

#define IMSA_CONN_GetConnCurReqPdnType(enConnType, enCurReqPdnType)\
        {\
            if (IMSA_CONN_TYPE_NORMAL == (enConnType))\
            {\
                (enCurReqPdnType) = IMSA_CONN_GetNormalConnCurReqPdnType();\
            }\
            else\
            {\
                (enCurReqPdnType) = IMSA_CONN_GetEmcConnCurReqPdnType();\
            }\
        }

#define IMSA_CONN_GetConnSelectedCid(enConnType, ucCid)\
        {\
            if (IMSA_CONN_TYPE_NORMAL == (enConnType))\
            {\
                (ucCid) = IMSA_CONN_GetNormalConnSelSdfParaAddr()->ucCid;\
            }\
            else\
            {\
                (ucCid) = IMSA_CONN_GetEmcConnSelSdfParaAddr()->ucCid;\
            }\
        }

#define IMSA_CONN_SetOpid(enConnType, ucOpid)\
        {\
            if (IMSA_CONN_TYPE_NORMAL == (enConnType))\
            {\
                IMSA_CONN_SetNormalConnOpid((ucOpid));\
            }\
            else\
            {\
                IMSA_CONN_SetEmcConnOpid((ucOpid));\
            }\
        }

/* Control模块相关宏 */
#define IMSA_GetControlManagerAddress()     (&pgstImsaEntity->stImsaControlManager)
#define IMSA_GetIntraMsgQueueAddress()      (&pgstImsaEntity->stImsaControlManager.stImsaIntraMsgQueue)
#define IMSA_GetCommonInfoAddress()         (&pgstImsaEntity->stImsaControlManager.stImsaCommonInfo)
#define IMSA_GetNetInfoAddress()            (&pgstImsaEntity->stImsaControlManager.stImsaNetworkInfo)
#define IMSA_SRV_GetNormalSrvStatus()       (pgstImsaEntity->stImsaControlManager.enNrmSrvStatus)
#define IMSA_SRV_GetEmcSrvStatus()          (pgstImsaEntity->stImsaControlManager.enEmcSrvStatus)
#define IMSA_GetConfigParaAddress()         (&pgstImsaEntity->stImsaControlManager.stImsaConfigPara)
#define IMSA_GetCampedRat()                 (pgstImsaEntity->stImsaControlManager.stImsaNetworkInfo.enImsaCampedRatType)
#define IMSA_GetVoiceDomain()               (pgstImsaEntity->stImsaControlManager.stImsaConfigPara.enVoiceDomain)
#define IMSA_GetUeImsVoiceCap()             (pgstImsaEntity->stImsaControlManager.stImsaConfigPara.ucVoiceCallOnImsSupportFlag)
#define IMSA_GetUeImsVideoCap()             (pgstImsaEntity->stImsaControlManager.stImsaConfigPara.ucVideoCallOnImsSupportFlag)
#define IMSA_GetUeImsSmsCap()               (pgstImsaEntity->stImsaControlManager.stImsaConfigPara.ucSmsOnImsSupportFlag)
#define IMSA_GetNwImsVoiceCap()             (pgstImsaEntity->stImsaControlManager.stImsaNetworkInfo.enImsaImsVoPsStatus)
#define IMSA_GetPsServiceStatus()           (pgstImsaEntity->stImsaControlManager.stImsaNetworkInfo.enImsaPsServiceStatus)
#define IMSA_GetIsimStatus()                (pgstImsaEntity->stImsaControlManager.enImsaIsimStatus)
#define IMSA_SetDeregCause(enDeregCause)    (pgstImsaEntity->stImsaControlManager.enDeregCause = (enDeregCause))
#define IMSA_GetDeregCause()                (pgstImsaEntity->stImsaControlManager.enDeregCause)
#define IMSA_GetAtControlAddress()          (&pgstImsaEntity->stImsaControlManager.stAtControl)
#define IMSA_GetSrvccBuffAddress()          (&pgstImsaEntity->stImsaControlManager.stSrvccBuffer)
#define IMSA_GetImsRedialCfgAddress()       (&pgstImsaEntity->stImsaControlManager.stImsaConfigPara.stImsRedialCfg)

#define IMSA_SetIsImsRegForbidden(ucIsRegForbidden)  (pgstImsaEntity->stImsaControlManager.ucIsImsRegForbidden = (ucIsRegForbidden))
#define IMSA_GetIsImsRegForbidden()                  (pgstImsaEntity->stImsaControlManager.ucIsImsRegForbidden)

#define IMSA_GetPowerState()                (pgstImsaEntity->stImsaControlManager.enPowerState)

#define IMSA_SetUsimNormOpid(ucOpid)        (pgstImsaEntity->stImsaRegManager.stNormalRegEntity.ucImsaUsimNormOpid = (ucOpid))
#define IMSA_GetUsimNormOpid()              (pgstImsaEntity->stImsaRegManager.stNormalRegEntity.ucImsaUsimNormOpid)
/* 用OPID的第八位区分当前是紧急鉴权还是普通鉴权 */
#define IMSA_SetUsimEmcOpid(ucOpid)         (pgstImsaEntity->stImsaRegManager.stEmcRegEntity.ucImsaUsimEmcOpid = (ucOpid | 0x80))
#define IMSA_GetUsimEmcOpid()               (pgstImsaEntity->stImsaRegManager.stEmcRegEntity.ucImsaUsimEmcOpid)


#define IMSA_SRV_SndCallSrvStatusInd(enSrvType, enCallSrvStatus,enNoSrvCause)\
    {\
        if (IMSA_SRV_TYPE_NORMAL == (enSrvType))\
        {\
            IMSA_SRV_SndNrmCallSrvStatusInd((enCallSrvStatus),(enNoSrvCause));\
        }\
        else\
        {\
            IMSA_SRV_SndEmcCallSrvStatusInd((enCallSrvStatus),(enNoSrvCause));\
        }\
    }

#define IMSA_SMS_GetSmrMoEntityAddress()    (&pgstImsaEntity->stImsaSmsManager.stImsaSmrMo)
#define IMSA_SMS_GetSmrMtEntityAddress()    (&pgstImsaEntity->stImsaSmsManager.stImsaSmrMt)

#define IMSA_USSD_GetEntityAddress()        (&pgstImsaEntity->stImsaUssdManager)


/* error log 控制信息 */
#if (FEATURE_ON == FEATURE_PTM)
#define IMSA_GetErrorlogManagerAddress()        (&pgstImsaEntity->stImsaErrorlogManager)
#define IMSA_GetErrorLogRingBufAddr()           (pgstImsaEntity->stImsaErrorlogManager.stBuffInfo.pstRingBuffer)
#define IMSA_GetErrlogOverflowCnt()             (pgstImsaEntity->stImsaErrorlogManager.stBuffInfo.ulOverflowCnt)
#define IMSA_GetErrlogCtrlFlag()                (pgstImsaEntity->stImsaErrorlogManager.stCtrlInfo.ucErrLogCtrlFlag)
#define IMSA_GetErrlogAlmLevel()                (pgstImsaEntity->stImsaErrorlogManager.stCtrlInfo.usAlmLevel)

#define IMSA_SetErrorLogRingBufAddr(pRingBuffer)        (IMSA_GetErrorLogRingBufAddr() = pRingBuffer)
#define IMSA_SetErrlogOverflowCnt(ulOverflowCnt)        (IMSA_GetErrlogOverflowCnt() = ulOverflowCnt)
#define IMSA_SetErrlogCtrlFlag(ucFlag)                  (IMSA_GetErrlogCtrlFlag() = ucFlag)
#define IMSA_SetErrlogAlmLevel(usAlmLevel)              (IMSA_GetErrlogAlmLevel() = usAlmLevel)
#endif

/* HIFI缓存消息控制信息 */
#define IMSA_GetHifiDataManagerAddress()        (&pgstImsaEntity->stImsaHifiDataManager)
#define IMSA_GetHifiDataBufferDataHead()        (pgstImsaEntity->stImsaHifiDataManager.pstBufferDataHead)
#define IMSA_GetHifiDataBufferDataTail()        (pgstImsaEntity->stImsaHifiDataManager.pstBufferDataTail)
#define IMSA_GetHifiDataBufferDataNum()         (pgstImsaEntity->stImsaHifiDataManager.ucBufferDataNum)
#define IMSA_GetHifiDataSentDataNum()           (pgstImsaEntity->stImsaHifiDataManager.ucSentDataNum)
#define IMSA_GetHifiDataOpid()                  (pgstImsaEntity->stImsaHifiDataManager.ulOpid)
#define IMSA_GetHifiDataAckProtectTimer()       (pgstImsaEntity->stImsaHifiDataManager.stHifiAckProtectTimer)
#define IMSA_GetHifiDataControlFlag()           (pgstImsaEntity->stImsaHifiDataManager.ucHifiDataControlFlag)
#define IMSA_GetHifiDataNeedAckNum()            (pgstImsaEntity->stImsaHifiDataManager.ucHifiDataNeedAckNum)
#define IMSA_GetHifiDataMaxBufferNum()          (pgstImsaEntity->stImsaHifiDataManager.ucHifiDatMaxBufferNum)
#define IMSA_GetHifiDataDataLoseNum()           (pgstImsaEntity->stImsaHifiDataManager.ulDataLoseNum)
#define IMSA_GetHifiDataTotalDataLoseNum()      (pgstImsaEntity->stImsaHifiDataManager.ulTotalDataLoseNum)
#define IMSA_GetHifiDataDataBufferNum()         (pgstImsaEntity->stImsaHifiDataManager.ulDataBufferNum)
#define IMSA_GetHifiDataTotalDataBufferNum()    (pgstImsaEntity->stImsaHifiDataManager.ulTotalDataBufferNum)
/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/



/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of ImsaEntity.h */




