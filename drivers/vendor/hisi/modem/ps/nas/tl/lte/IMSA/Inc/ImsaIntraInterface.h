/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : ImsaIntraInterface.h
    Description : 内部模块间接口头文件
    History     :
      1.sunbing 00049683    2013-05-28  Draft Enact


******************************************************************************/

#ifndef __IMSAINTRAINTERFACE_H__
#define __IMSAINTRAINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "PsRrmInterface.h"
#include    "SpmImsaInterface.h"
#include    "ImsaImsEvent.h"
#include    "MsgImsaInterface.h"
#include    "ImsaImsInterface.h"
#if (FEATURE_ON == FEATURE_PTM)
#include "ImsaErrlogInterface.h"
#endif
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


/* the size for intra msg queue */
#define IMSA_INTRA_MSG_MAX_NUM          (6)
#define IMSA_INTRA_MSG_MAX_SIZE         512

#define IMSA_START_SRV_RESULT_CAN_MAKE_CALL                 (0)
#define IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL              (1)
#define IMSA_START_SRV_RESULT_BUFFER_CALL_WAIT_INDICATION   (2)
#define IMSA_START_SRV_RESULT_APPLY_NOTNEED_WAIT_CNF        (3)
#define IMSA_START_SRV_RESULT_APPLY_WAIT_STATUS_IND         (4)
#define IMSA_START_SRV_RESULT_NO_RF                         (5)


#define IMSA_CONN_REG_PARA_INVALID      (0)
#define IMSA_CONN_REG_PARA_VALID        (1)

#define IMSA_IPV4_ADDR_LEN      (4)
#define IMSA_IPV6_ADDR_LEN      (16)

#define IMSA_IPV6_ADDR_PREFIX_LEN       (8)

#define IMSA_IPV6_ADDR_PREFIX_BIT_LEN       (64)

#define IMSA_IPV6_STRING_PREFIX_LEN     (46)
#define IMSA_IPV4_STRING_PREFIX_LEN     (15)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
 枚举名    : IMSA_CONTROL_CONN_MSG_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 内部消息ID定义
*****************************************************************************/
enum    IMSA_INTRA_MSG_ID_ENUM
{
    /* CONTROL发给REG的消息原语 */
    ID_IMSA_REG_REG_REQ                 = 0x000,                /* _H2ASN_MsgChoice IMSA_REG_REG_REQ_STRU */
    ID_IMSA_REG_DEREG_REQ               = 0x001,                /* _H2ASN_MsgChoice IMSA_REG_DEREG_REQ_STRU */

    /* REG发给CONTROL的消息原语 */
    ID_IMSA_REG_REG_IND                 = 0x010,                /* _H2ASN_MsgChoice IMSA_REG_REG_IND_STRU */
    ID_IMSA_REG_DEREG_IND               = 0x011,                /* _H2ASN_MsgChoice IMSA_REG_DEREG_IND_STRU */

    /* CONTROL发给CONN的消息原语 */
    ID_IMSA_CONN_SETUP_REQ              = 0x100,                /* _H2ASN_MsgChoice IMSA_CONN_SETUP_REQ_STRU */
    ID_IMSA_CONN_REL_REQ                = 0x101,                /* _H2ASN_MsgChoice IMSA_CONN_REL_REQ_STRU */

    /* CONN发给CONTROL的消息原语 */
    ID_IMSA_CONN_SETUP_IND              = 0x110,                /* _H2ASN_MsgChoice IMSA_CONN_SETUP_IND_STRU */
    ID_IMSA_CONN_REL_IND                = 0x111,                /* _H2ASN_MsgChoice IMSA_CONN_REL_IND_STRU */
    ID_IMSA_CONN_MODIFY_IND             = 0x112,                /* _H2ASN_MsgChoice IMSA_CONN_MODIFY_IND_STRU */


    /* CONTROL给CALL模块的消息*/
    ID_IMSA_NRM_CALL_SRV_STATUS_IND     = 0x200,                /* _H2ASN_MsgChoice IMSA_NRM_CALL_SRV_STATUS_IND_STRU */
    ID_IMSA_EMC_CALL_SRV_STATUS_IND     = 0x201,                /* _H2ASN_MsgChoice IMSA_EMC_CALL_SRV_STATUS_IND_STRU */

    /* CALL模块给CONTROL模块的消息 */
    ID_IMSA_CALL_RESULT_ACTION_IND      = 0x210,                /* _H2ASN_MsgChoice IMSA_CALL_RESULT_ACTION_IND_STRU */
    ID_IMSA_CALL_SRVCC_SUCC_IND         = 0x211,                /* _H2ASN_MsgChoice IMSA_CALL_SRVCC_SUCC_IND_STRU */

    /* 勾到HIDS上显示NIC PDP INFO */
    ID_IMSA_NIC_PDP_INFO_IND            = 0x220,                /* _H2ASN_MsgChoice IMSA_PRINT_NIC_PDP_INFO_STRU */

    /* 够到HIDS显示HIFI控制丢包情况 */
    ID_IMSA_HIFI_DATA_INFO_IND          = 0x221,                /* _H2ASN_MsgChoice IMSA_HIFI_DATA_INFO_IND_STRU */

    ID_IMSA_INTRA_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 IMSA_INTRA_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
    枚举名    : IMSA_REG_RESULT_ENUM
    枚举说明  : IMS注册结果
*****************************************************************************/
enum IMSA_REG_RESULT_ENUM
{
    IMSA_REG_RESULT_SUCCESS             = 0,    /**< 注册模块命令执行成功 */
    IMSA_REG_RESULT_FAIL                = 1,    /**< 注册模块命令执行失败 */
    IMSA_REG_RESULT_FAIL_REMOTE         = 2,    /**< 被服务器拒绝，具体拒绝原因值详见对应数据结构中的Status Code，根据不同的原因值可能会携带一些其它的头域 */
    IMSA_REG_RESULT_FAIL_TIMEOUT        = 3,    /**< 发送或接收SIP报文超时，具体超时的定时器详见对应数据结构中的 Timer Id */
    IMSA_REG_RESULT_FAIL_TRANSPORT      = 4,    /**< 发送或接收SIP报文时，底层传输发生错误 */
    IMSA_REG_RESULT_FAIL_SA             = 5,    /**< 注册成功后，安全联盟发生异常 */
    IMSA_REG_RESULT_FAIL_MT_DEREG       = 6,    /**< 注册成功后，网侧发起的去注册 */
    IMSA_REG_RESULT_FAIL_NO_ADDR_PAIR   = 7,    /**< 没有可以再使用的注册地址对 */
    IMSA_REG_RESULT_FAIL_LACK_PARAM     = 8,    /**< 注册所需参数没有准备完备 */
    IMSA_REG_RESULT_FAIL_FORBIDDEN      = 9,    /**< 注册被禁止 */
    IMSA_REG_RESULT_BUTT
};
typedef VOS_UINT32 IMSA_REG_RESULT_ENUM_UINT32;

/*****************************************************************************
    枚举名    : IMSA_REG_ADDR_PARAM_ENUM
    枚举说明  : IMS注册时使用的地址对信息
*****************************************************************************/
enum IMSA_REG_ADDR_PARAM_ENUM
{
    IMSA_REG_ADDR_PARAM_NEW,            /**< 注册地址使用地址对中的第一个 */
    IMSA_REG_ADDR_PARAM_SAME,           /**< 使用和当前相同的地址对，如果没有则注册返回失败 */
    IMSA_REG_ADDR_PARAM_NEXT,           /**< 使用下一个可用的地址对，如果没有则注册返回失败 */
    IMSA_REG_ADDR_PARAM_RESTORATION,    /**< 如果有其他P-CSCF地址，则使用其他P-CSCF地址；如果没有，则使用当前P-CSCF地址 */
    IMSA_REG_ADDR_PARAM_BUTT
};
typedef VOS_UINT32 IMSA_REG_ADDR_PARAM_ENUM_UINT32;

/*****************************************************************************
    枚举名    : IMSA_REG_TYPE_ENUM
    枚举说明  : IMS注册类型
*****************************************************************************/
enum    IMSA_REG_TYPE_ENUM
{
    IMSA_REG_TYPE_NORMAL                = 0,        /**< 普通注册 */
    IMSA_REG_TYPE_EMC                   = 1,        /**< 紧急注册 */
    IMSA_REG_TYPE_BUTT
};
typedef VOS_UINT8 IMSA_REG_TYPE_ENUM_UINT8;

/*****************************************************************************
    枚举名    : IMSA_REG_RETRY_POLICY_ENUM
    枚举说明  : IMS注册自动重试策略
*****************************************************************************/
enum    IMSA_REG_RETRY_POLICY_ENUM
{
    IMSA_REG_RETRY_POLICY_DISABLE,             /**< 不自动进行重新注册尝试 */
    IMSA_REG_RETRY_POLICY_PERIODIC,            /**< 周期性进行重新注册尝试 */
    IMSA_REG_RETRY_POLICY_RFC5626,             /**< 根据RFC5626进行重新注册尝试 */
    IMSA_REG_RETRY_POLICY_BUTT
};
typedef VOS_UINT32 IMSA_REG_RETRY_POLICY_ENUM_UINT32;

/*****************************************************************************
    枚举名    : IMSA_PDP_TYPE_ENUM
    枚举说明  : IMSA IP地址类型枚举
*****************************************************************************/
enum IMSA_IP_TYPE_ENUM
{
    IMSA_IP_TYPE_IPV4                   = 0x01,
    IMSA_IP_TYPE_IPV6                   = 0x02,
    IMSA_IP_TYPE_IPV4V6                 = 0x03,

    IMSA_IP_TYPE_BUTT                   = 0xFF
};
typedef VOS_UINT8 IMSA_IP_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名称: IMSA_PF_TRANS_DIRECTION_ENUM_UINT8
 结构说明: TFT过滤器方向
 1.日    期   : 2014年06月116日
   作    者   : W00209181
   修改内容   : Added for VTLTE
*****************************************************************************/
enum IMSA_PF_TRANS_DIRECTION_ENUM
{
    IMSA_PF_TRANS_DIRECTION_PRE_REL7     = 0x00,             /* 0 - Pre-Release 7 TFT filter (see 3GPP TS 24.008 [8], table 10.5.162) */
    IMSA_PF_TRANS_DIRECTION_UPLINK       = 0x01,             /* 1 - Uplink */
    IMSA_PF_TRANS_DIRECTION_DOWNLINK     = 0x02,             /* 2 - Downlink */
    IMSA_PF_TRANS_DIRECTION_BIDIRECTION  = 0x03,             /* 3 - Birectional (Up & Downlink) (default if omitted) */

    IMSA_PF_TRANS_DIRECTION_BUTT         = 0xFF
};
typedef VOS_UINT8 IMSA_PF_TRANS_DIRECTION_ENUM_UINT8;


enum IMSA_CONN_TYPE_ENUM
{
    IMSA_CONN_TYPE_NORMAL               = 0,    /* 正常连接 */
    IMSA_CONN_TYPE_EMC                  = 1,    /* 紧急连接 */
    IMSA_CONN_TYPE_BUTT
};
typedef VOS_UINT32 IMSA_CONN_TYPE_ENUM_UINT32;

enum IMSA_CALL_SERVICE_STATUS_ENUM
{
    IMSA_CALL_SERVICE_STATUS_NORMAL_SERVICE    = 0,
    IMSA_CALL_SERVICE_STATUS_NO_SERVICE     = 1,
    IMSA_CALL_SERVICE_STATUS_BUTT
};
typedef VOS_UINT32 IMSA_CALL_SERVICE_STATUS_ENUM_UINT32;

/*****************************************************************************
    枚举名    : IMSA_CALL_RESULT_ENUM
    枚举说明  : IMS呼叫结果
*****************************************************************************/
enum IMSA_CALL_RESULT_ENUM
{
    IMSA_CALL_RESULT_SUCCESS             = 0,    /**< 呼叫命令执行成功 */
    IMSA_CALL_RESULT_FAIL                = 1,    /**< 注册模块命令执行失败 */
    IMSA_CALL_RESULT_FAIL_REMOTE         = 2,    /**< 被服务器拒绝，具体拒绝原因值详见对应数据结构中的Status Code，根据不同的原因值可能会携带一些其它的头域 */
    IMSA_CALL_RESULT_FAIL_TIMEOUT        = 3,    /**< 发送或接收SIP报文超时，具体超时的定时器详见对应数据结构中的 Timer Id */
    IMSA_CALL_RESULT_NO_SERVICE          = 4,    /**< 没有服务导致失败 */
    IMSA_CALL_RESULT_BUTT
};
typedef VOS_UINT32 IMSA_CALL_RESULT_ENUM_UINT32;

/*****************************************************************************
    枚举名    : IMSA_RESULT_ACTION_ENUM
    枚举说明  : 注册或呼叫失败后，需要主控模块要进行的操作
*****************************************************************************/
enum    IMSA_RESULT_ACTION_ENUM
{
    IMSA_RESULT_ACTION_NULL,                            /**< 不需要进行其他操作 */
    IMSA_RESULT_ACTION_REG_WITH_FIRST_ADDR_PAIR,        /**< 发起注册并从地址对列表中的第一个开始尝试 */
    IMSA_RESULT_ACTION_REG_WITH_CURRENT_ADDR_PAIR,      /**< 发起注册并使用当前地址 */
    IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR,         /**< 发起注册并使用下一组未使用地址对 */
    IMSA_RESULT_ACTION_REG_RESTORATION,                 /**< 需要主控模块进行restoration流程 */
    IMSA_RESULT_ACTION_REG_LOCAL_DEREG,                 /**< 仅修改注册状态为DEREG */
    IMSA_RESULT_ACTION_REG_NORF,                        /**< 需要先注册资源，然后用当前地址对注册 */
    IMSA_RESULT_ACTION_WAIT_RETRY_TIME_OUT,             /**< 等待retry after超时 */
    IMSA_RESULT_ACTION_BUTT
};
typedef VOS_UINT32 IMSA_RESULT_ACTION_ENUM_UINT32;

/*****************************************************************************
    枚举名    : IMSA_CONN_RESULT_ENUM
    枚举说明  : IMS连接结果
*****************************************************************************/
enum IMSA_CONN_RESULT_ENUM
{
    IMSA_CONN_RESULT_SUCCESS                    = 0,    /**< CONN模块命令执行成功 */
    IMSA_CONN_RESULT_FAIL_PARA_ERR              = 1,    /**< CONN模块命令执行失败，由于参数错误 */
    IMSA_CONN_RESULT_FAIL_CN_REJ                = 2,    /**< CONN模块命令执行失败，由于被网侧拒绝 */
    IMSA_CONN_RESULT_FAIL_TIMER_EXP             = 3,    /**< CONN模块命令执行失败，由于定时器超时 */
    IMSA_CONN_RESULT_FAIL_CONN_RELEASING        = 4,    /**< CONN模块命令执行失败，由于正在释放连接 */
    IMSA_CONN_RESULT_FAIL_PDP_ACTIVATE_LIMIT    = 5,    /**< CONN模块命令执行失败，由于激活的承载数限制 */
    IMSA_CONN_RESULT_FAIL_SAME_APN_OPERATING    = 6,    /**< CONN模块命令执行失败，由于APS正在执行操作 */
    IMSA_CONN_RESULT_FAIL_TEMP_FORBIDDEN        = 7,    /**< CONN模块命令执行失败，收到临时被拒原因值或者网侧不响应 */
    IMSA_CONN_RESULT_FAIL_PERM_FORBIDDEN        = 8,    /**< CONN模块命令执行失败，收到永久被拒原因值 */
    IMSA_CONN_RESULT_FAIL_OHTERS                = 9,    /**< CONN模块命令执行失败，由于其他原因 */

    IMSA_CONN_RESULT_BUTT
};
typedef VOS_UINT32 IMSA_CONN_RESULT_ENUM_UINT32;

/*****************************************************************************
    枚举名    : IMSA_SIP_PDP_TYPE_ENUM
    枚举说明  : SIP承载类型
*****************************************************************************/
enum IMSA_CONN_SIP_PDP_TYPE_ENUM
{
    IMSA_CONN_SIP_PDP_TYPE_SIGNAL               = 0,                /**< SIP信令承载 */
    IMSA_CONN_SIP_PDP_TYPE_MEDIA                = 1,                /**< SIP媒体承载 */

    IMSA_CONN_SIP_PDP_TYPE_BUTT
};
typedef VOS_UINT32  IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32;

/*****************************************************************************
    枚举名    : IMSA_CONN_MEDIA_PDP_TYPE_ENUM
    枚举说明  : 媒体承载类型
*****************************************************************************/
enum IMSA_CONN_MEDIA_PDP_TYPE_ENUM
{
    IMSA_CONN_MEDIA_PDP_TYPE_VOICE               = 0,                /**< 语音承载 */
    IMSA_CONN_MEDIA_PDP_TYPE_VIDEO               = 1,                /**< 视频承载 */
    IMSA_CONN_MEDIA_PDP_TYPE_OTHERS              = 2,

    IMSA_CONN_MEDIA_PDP_TYPE_BUTT
};
typedef VOS_UINT32  IMSA_CONN_MEDIA_PDP_TYPE_ENUM_UINT32;


/*****************************************************************************
    枚举名    : IMSA_CONN_MODIFY_TYPE_ENUM
    枚举说明  : 承载MODIFY类型
*****************************************************************************/
enum IMSA_CONN_MODIFY_TYPE_ENUM
{
    IMSA_CONN_MODIFY_TYPE_REG_PARA_INVALID  = 0,                /**< 注册参数失效 */
    IMSA_CONN_MODIFY_TYPE_PCSCF_INVALID     = 1,                /**< P-CSCF地址失效 */

    IMSA_CONN_MODIFY_TYPE_BUTT
};
typedef VOS_UINT32  IMSA_CONN_MODIFY_TYPE_ENUM_UINT32;

/*****************************************************************************
    枚举名    : IMSA_PCSCF_SRC_TYPE
    枚举说明  : PCSCF地址来源类型
*****************************************************************************/
enum IMSA_PCSCF_SRC_TYPE
{
    IMSA_PCSCF_SRC_TYPE_PDN,            /**< P-CSCF地址来源于PDN连接建立过程 */
    IMSA_PCSCF_SRC_TYPE_CARD,           /**< P-CSCF地址来源于USIM/ISIM */
    IMSA_PCSCF_SRC_TYPE_DISCOVERY       /**< P-CSCF地址来源于P-CSCF发现流程 */
};
typedef VOS_UINT8 IMSA_PCSCF_SRC_TYPE_UINT8;

/*****************************************************************************
    枚举名    : IMSA_SRV_TYPE_ENUM
    枚举说明  : IMSA SERVICE 类型枚举
*****************************************************************************/
enum IMSA_SRV_TYPE_ENUM
{
    IMSA_SRV_TYPE_NORMAL                = 0,
    IMSA_SRV_TYPE_EMC                   = 1,

    IMSA_SRV_TYPE_BUTT
};
typedef VOS_UINT8  IMSA_SRV_TYPE_ENUM_UINT8;

/*****************************************************************************
    枚举名    : IMSA_CALL_TYPE_ENUM
    枚举说明  : 呼叫类型
*****************************************************************************/
enum    IMSA_CALL_TYPE_ENUM
{
    IMSA_CALL_TYPE_VOICE    = 0,      /* Voice only call */
    IMSA_CALL_TYPE_VIDEO_TX = 1,      /* PS Video telephony call: one way TX video,Two way audio */
    IMSA_CALL_TYPE_VIDEO_RX = 2,      /* Video telephony call: ony way RX video,two way audio */
    IMSA_CALL_TYPE_VIDEO    = 3,      /* video call */
    IMSA_CALL_TYPE_EMC      = 9,      /* emergency call */
    IMSA_CALL_TYPE_BUTT
};
typedef VOS_UINT8 IMSA_CALL_TYPE_ENUM_UINT8;

/*****************************************************************************
    枚举名    : IMSA_EMC_CALL_TYPE_ENUM
    枚举说明  : 紧急呼叫类型
*****************************************************************************/
enum    IMSA_EMC_CALL_TYPE_ENUM
{
    IMSA_EMC_CALL_TYPE_IN_NORMAL_SRV    = 0,                        /**< 在普通服务上发起紧急呼 */
    IMSA_EMC_CALL_TYPE_NO_CARD          = 1,                        /**< 无卡紧急呼 */
    IMSA_EMC_CALL_TYPE_EMC_CONN_EMC_REG = 2,                        /**< 有紧急注册的紧急呼 */
    IMSA_EMC_CALL_TYPE_BUTT
};
typedef VOS_UINT32 IMSA_EMC_CALL_TYPE_ENUM_UINT32;

/*****************************************************************************
    枚举名    : IMSA_CALL_NO_SRV_CAUSE_ENUM
    枚举说明  : IMSA CALL无服务促使原因值
*****************************************************************************/
enum    IMSA_CALL_NO_SRV_CAUSE_ENUM
{
    IMSA_CALL_NO_SRV_CAUSE_HIFI_EXCEPTION           = 0,
    IMSA_CALL_NO_SRV_CAUSE_NON_SRVCC_RAT_CHANGE,
    IMSA_CALL_NO_SRV_CAUSE_NW_NOT_SUPPORT_IMS_VOICE,
    IMSA_CALL_NO_SRV_CAUSE_MEDIA_PDP_RELEASE,
    IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR,
    IMSA_CALL_NO_SRV_CAUSE_REG_ERR,

    IMSA_CALL_NO_SRV_CAUSE_PORT_CFG_FAIL,                                      /* 端口配置 */
    IMSA_CALL_NO_SRV_CAUSE_SET_DEVICE_FAIL,                                    /* 设置Device失败 */
    IMSA_CALL_NO_SRV_CAUSE_SET_START_FAIL,                                     /* start失败 */
    IMSA_CALL_NO_SRV_CAUSE_SET_VOLUME_FAIL,                                    /* 设置音量失败 */
    IMSA_CALL_NO_SRV_CAUSE_SAMPLE_RATE_FAIL,                                   /* 频率采样失败 */
    IMSA_CALL_NO_SRV_CAUSE_TI_START_EXPIRED,                                   /* start保护定时器超时 */

    IMSA_CALL_NO_SRV_CAUSE_BUTT
};
typedef VOS_UINT32 IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : RF资源申请触发源枚举
*****************************************************************************/
enum IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM
{
    IMSA_RF_RES_APPLY_TRIGER_SRC_MO_CALL                = 0,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENHANCED_CONFERRENCE   = 1,
    IMSA_RF_RES_APPLY_TRIGER_SRC_MT_CALL                = 2,
    IMSA_RF_RES_APPLY_TRIGER_SRC_EMC_CALL               = 3,
    IMSA_RF_RES_APPLY_TRIGER_SRC_MO_SMS                 = 4,
    IMSA_RF_RES_APPLY_TRIGER_SRC_MT_SMS                 = 5,
    IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV            = 6,
    IMSA_RF_RES_APPLY_TRIGER_SRC_REG_RETRY_EXP          = 7,
    IMSA_RF_RES_APPLY_TRIGER_SRC_REREGISTER_FAIL        = 8,
    IMSA_RF_RES_APPLY_TRIGER_SRC_POWER_OFF              = 9,
    IMSA_RF_RES_APPLY_TRIGER_SRC_MO_SS                  = 10,
    IMSA_RF_RES_APPLY_TRIGER_SRC_MT_SS                  = 11,
    IMSA_RF_RES_APPLY_TRIGER_SRC_MO_SMMA                = 12,
    IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG                  = 13,
    IMSA_RF_RES_APPLY_TRIGER_SRC_SMMA_RETRANS           = 14,
    IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,

};
typedef VOS_UINT8 IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8;

/*****************************************************************************
 枚举名    : IMSA_TASKTYPE_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : DSDS TASK Type状态枚举
*****************************************************************************/
enum IMSA_TASKTYPE_STATUS_ENUM
{
    IMSA_TASKTYPE_STATUS_NULL           = 0,        /*未申请状态，即初始状态*/
    IMSA_TASKTYPE_STATUS_PENDING        = 1,        /*申请失败或者超时过，需要等待一定时间再去申请，处于等待申请的状态*/
    IMSA_TASKTYPE_STATUS_APPLYING       = 2,        /*正在申请，已经发申请消息给RRM*/
    IMSA_TASKTYPE_STATUS_ACTIVE         = 3,        /*已经申请到资源*/
    IMSA_TASKTYPE_STATUS_BUTT,
};
typedef VOS_UINT8 IMSA_TASKTYPE_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : IMSA_TASKTYPE_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : DSDS TASK Type状态枚举
*****************************************************************************/
enum IMSA_RESOURCE_STATUS_ENUM
{
    IMSA_RESOURCE_STATUS_NULL,
    IMSA_RESOURCE_STATUS_APPLYING,
    IMSA_RESOURCE_STATUS_WAIT_STATUS_IND,
    IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF,
    IMSA_RESOURCE_STATUS_ACTIVE,
    IMSA_RESOURCE_STATUS_BUTT,
};
typedef VOS_UINT8 IMSA_RESOURCE_STATUS_ENUM_UINT8;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/

typedef struct
{
    VOS_UINT32                              ulStatusCode;   /**< SIP服务器返回的状态值 */

    // TODO:
    // 1. Retry-After structure
    // 2. ims-3gpp structure
} IMSA_SIP_SERVER_RESULT_STRU;

/*****************************************************************************
 结构名    : IMSA_REG_REG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_REG_REG_REQ_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                      ulMsgId;
    IMSA_REG_TYPE_ENUM_UINT8                        enRegType;          /**< 注册类型 */
    VOS_UINT8                                       aucRsv[3];
    IMSA_REG_ADDR_PARAM_ENUM_UINT32                 enAddrType;         /**< 注册使用的地址参数 */
    //IMSA_REG_RETRY_POLICY_ENUM_UINT32               enRetryPolicy;      /**< 初始注册时指定重试策略 */
} IMSA_REG_REG_REQ_STRU;

/*****************************************************************************
 结构名    : IMSA_REG_REG_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_REG_REG_IND_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;        /**< 消息Id */
    IMSA_REG_TYPE_ENUM_UINT8                enRegType;      /**< 注册类型 */
    VOS_UINT8                               aucRsv[3];
    IMSA_REG_RESULT_ENUM_UINT32             enResult;       /**< 注册结果 */

    IMSA_RESULT_ACTION_ENUM_UINT32          enResultAction; /**< 需要主控模块执行的动作 */
    // TODO: 上层模块可能不需要服务器返回的参数
    IMSA_SIP_SERVER_RESULT_STRU             stSipResult;    /**< 服务器返回的参数 */
} IMSA_REG_REG_IND_STRU;


/*****************************************************************************
 结构名    : IMSA_REG_DEREG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_REG_DEREG_REQ_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                           ulMsgId;           /**< 消息Id */
    IMSA_REG_TYPE_ENUM_UINT8             enDeRegType;       /**< 去注册的实体类型 */
    VOS_UINT8                            aucRsv[3];
    VOS_UINT32                           ulLocalFlag;       /**< 是否为本地去注册，0为需要发起dereg流程, 1为本地去注册 */
} IMSA_REG_DEREG_REQ_STRU;


/*****************************************************************************
 结构名    : IMSA_REG_DEREG_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_REG_DEREG_IND_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;        /**< 消息Id */
    IMSA_REG_TYPE_ENUM_UINT8            enRegType;      /**< 注册类型 */
    VOS_UINT8                           aucRsv[3];
    IMSA_REG_RESULT_ENUM_UINT32         enResult;       /**< 注册结果 */

    IMSA_RESULT_ACTION_ENUM_UINT32      enResultAction; /**< 需要主控模块执行的动作 */
    // TODO: 上层模块可能不需要服务器返回的参数
    IMSA_SIP_SERVER_RESULT_STRU         stSipResult;    /**< 服务器返回的参数 */
} IMSA_REG_DEREG_IND_STRU;


/*****************************************************************************
 结构名    : IMSA_CONN_SETUP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_CONN_SETUP_REQ_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;
    VOS_UINT32                              ulReEstablishFlag;  /* 重建立标识 VOS_TRUE:重建立 VOS_FALSE:初始建立 */
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType;
} IMSA_CONN_SETUP_REQ_STRU;

/*****************************************************************************
 结构名    : IMSA_CONN_SETUP_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_CONN_SETUP_IND_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;
    IMSA_CONN_RESULT_ENUM_UINT32            enResult;

    IMSA_CONN_TYPE_ENUM_UINT32              enConnType;
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType;   /*0信令，1数据*/
    IMSA_CONN_MEDIA_PDP_TYPE_ENUM_UINT32    enMediaPdpType; /* 媒体承载的类型 */

} IMSA_CONN_SETUP_IND_STRU;

/*****************************************************************************
 结构名    : IMSA_CONN_REL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_CONN_REL_REQ_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType;
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType;/*0信令，1数据*//* 暂不支持媒体承载的主动释放 */
} IMSA_CONN_REL_REQ_STRU;


/*****************************************************************************
 结构名    : IMSA_CONN_REL_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_CONN_REL_IND_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType;
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType;/*0信令，1数据*/
} IMSA_CONN_REL_IND_STRU;

/*****************************************************************************
 结构名    : IMSA_CONN_MODIFY_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_CONN_MODIFY_IND_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;

    VOS_UINT32                              bitOpModifyType         : 1;
    VOS_UINT32                              bitOpMediaModifyType    :1;
    VOS_UINT32                              bitSpare                : 30;

    IMSA_CONN_TYPE_ENUM_UINT32              enConnType;
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType;/*0信令，1数据*/
    IMSA_CONN_MEDIA_PDP_TYPE_ENUM_UINT32    enMediaPdpType; /* 媒体承载的类型 */
    IMSA_CONN_MODIFY_TYPE_ENUM_UINT32       enModifyType;
} IMSA_CONN_MODIFY_IND_STRU;


/*****************************************************************************
 结构名    : IMSA_NORMAL_SERVICE_STATUS_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_NORMAL_SERVICE_STATUS_IND_STRU消息结构定义
*****************************************************************************/
/**
 *
 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                  ulMsgId;            /**< 消息Id */
    IMSA_CALL_SERVICE_STATUS_ENUM_UINT32        enCallSrvStatus;    /**< 呼叫服务类型 */
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32          enNoSrvCause;       /**< 通知无服务时指示原因  */
} IMSA_NRM_CALL_SRV_STATUS_IND_STRU;


/*****************************************************************************
 结构名    : IMSA_EMERG_SERVICE_STATUS_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_EMERG_SERVICE_STATUS_IND_STRU消息结构定义
*****************************************************************************/
/**
 *
 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                  ulMsgId;            /**< 消息Id */
    IMSA_CALL_SERVICE_STATUS_ENUM_UINT32        enCallSrvStatus;    /**< 呼叫服务类型 */
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32          enNoSrvCause;       /**< 通知无服务时指示原因  */
} IMSA_EMC_CALL_SRV_STATUS_IND_STRU;


/*****************************************************************************
 结构名    : IMSA_CALL_RESULT_ACTION_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_CALL_RESULT_ACTION_IND_STRU消息结构定义
*****************************************************************************/
/**
 * \brief 呼叫失败且需要主控模块进行其它操作时，通过此结构传递需要进行的操作
 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;            /**< 消息Id */

    IMSA_CALL_TYPE_ENUM_UINT8               enCallType;         /**< 服务类型 */
    VOS_UINT8                               aucReserved[3];

    IMSA_RESULT_ACTION_ENUM_UINT32          enResultAction;     /**< 呼叫失败后请求主控模块执行的操作 */
    // TODO: other param
} IMSA_CALL_RESULT_ACTION_IND_STRU;

/*****************************************************************************
 结构名    : IMSA_CALL_SRVCC_SUCC_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_CALL_SRVCC_SUCC_IND_STRU消息结构定义
*****************************************************************************/
/**
 * \brief SRVCC成功后，CALL模块通知SERVICE模块，由SERVICE模块通知TAF当前IMS处于未注册状态
 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;            /**< 消息Id */
} IMSA_CALL_SRVCC_SUCC_IND_STRU;

/*****************************************************************************
 结构名    : IMSA_INTRA_MSG_QUEUE_STRU
 结构说明  : 内部消息队列结构
             usHeader   : 指向下一个出队的消息
             usTail     : 指向下一个入队的消息将被放入的位置，该位置当前为空
                          即aucMsgBuff[usTail]，当前为空
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usHeader;                                   /* 队头 */
    VOS_UINT16                      usTail;                                     /* 队尾 */
    VOS_UINT8                       aucMsgBuff[IMSA_INTRA_MSG_MAX_NUM][IMSA_INTRA_MSG_MAX_SIZE];    /* 消息存放区域 */
}IMSA_INTRA_MSG_QUEUE_STRU;


typedef struct
{
    VOS_UINT32                          ulMsgId;            /*_H2ASN_MsgChoice_Export IMSA_INTRA_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          IMSA_INTRA_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}IMSA_INTRA_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    IMSA_INTRA_MSG_DATA                     stMsgData;
}IMSA_INTRA_MSG;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulDataLoseNum;
    VOS_UINT32                          ulTotalDataLoseNum;
    VOS_UINT32                          ulDataBufferNum;
    VOS_UINT32                          ulTotalDataBufferNum;

}IMSA_HIFI_DATA_INFO_IND_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
/**
 * \brief 控制管理模块提供给呼叫模块的API, Call模块在打普通电话时调用
 *
 * @retval 返回结果是0，表示Control可以提供正常服务，Call可以直接打电话
 * @retval 返回结果是1，表示不能提供正常服务，打电话失败
 */
extern VOS_UINT32 IMSA_StartImsNormalService
(
    IMSA_CALL_TYPE_ENUM_UINT8               enCallType
);

/**
 * \brief 控制管理模块提供给呼叫模块的API, Call模块在打紧急电话时调用
 *
 *
 * @param[out]   penEmcCallType                  紧急呼类型
 *
 * @retval 返回结果是0，表示Control可以提供紧急服务，Call可以直接打电话
 * @retval 返回结果是1，表示不能提供紧急服务，打紧急电话失败
 * @retval 返回结果是2，表示暂时不能提供紧急服务，正在建立紧急服务，Call模块需要缓存电话
 */
extern VOS_UINT32 IMSA_StartImsEmergService
(
    IMSA_EMC_CALL_TYPE_ENUM_UINT32     *penEmcCallType
);

/**
 * \brief 呼叫模块提供给控制模块的API, 控制模块在收到连接模块数据连接激活
 *        或修改时调用
 */
extern VOS_VOID IMSA_ProcCallResourceIsReady
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_MEDIA_PDP_TYPE_ENUM_UINT32    enMediaPdpType
);

/**
 * \brief 呼叫模块提供给控制模块的API, 控制模块在收到连接模块数据连接释放时调用
 *
 */
extern VOS_VOID IMSA_ProcCallResourceIsNotReady
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType
);


/**
 * \brief 分配内部消息空间
 *
 *
 * @param[in]   ulBuffSize                  分配消息的空间
 *
 * @retval      VOS_VOID *                  获取到的内部消息空间地址
 */
extern VOS_VOID *IMSA_GetIntraMsgBuffAddr( VOS_UINT32 ulBuffSize );

/**
 * \brief 发送内部消息
 *
 *
 * @param[in]   pIntraMsg                   待发送消息
 *
 * @retval      VOS_UINT32                  发送结果
 */
extern VOS_UINT32 IMSA_SndIntraMsg(VOS_VOID* pIntraMsg);


/**
 * \brief 向地址对管理模块新增可用的P-CSCF地址
 *
 * 此函数由其它模块进行调用，地址对管理模块会根据设定值及
 * 之前已经有的UE地址信息按照一定的规则更新地址对列表
 *
 * 地址对列表生成规则如下:
 *   -# 既有IPv4又有IPv6类型地址时，则优先选择IPv6类型的IP地址
 *   -# UE IP地址类型和P-CSCF地址类型相同
 *   -# 如果选定的IP类型的P-CSCF地址有多个，则根据存储顺序取P-CSCF地址
 *
 * @param[in]   ulRegType       注册类型
 * @param[in]   enIpType        新增的P-CSCF地址类型
 * @param[in]   enSrcType       新增的P-CSCF地址来源类型
 * @param[in]   paucIpAddr      新增的P-CSCF地址
 *
 * @retval      VOS_TRUE        新增P-CSCF成功，并根据规则刷新了地址对列表
 * @retval      VOS_FALSE       新增P-CSCF失败
 */
extern VOS_UINT32 IMSA_RegAddrPairMgrAddPcscfAddr(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                                  IMSA_IP_TYPE_ENUM_UINT8 enIpType,
                                                  IMSA_PCSCF_SRC_TYPE_UINT8 enSrcType,
                                                  const VOS_CHAR *pacIpAddr);

/**
 * \brief 从地址对管理模块删除一个P-CSCF地址
 *
 * 此函数由其它模块进行调用，地址对管理模块会根据设定值及
 * 之前已经有的UE地址信息按照一定的规则更新地址对列表
 *
 * @param[in]   ulRegType       注册类型
 * @param[in]   enIpType        删除的P-CSCF地址类型
 * @param[in]   paucIpAddr      删除的P-CSCF地址
 *
 * @retval      VOS_TRUE        删除P-CSCF成功，并根据规则刷新了地址对列表
 */
extern VOS_UINT32 IMSA_RegAddrPairMgrRmvPcscfAddr(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                                  IMSA_IP_TYPE_ENUM_UINT8 enIpType,
                                                  VOS_CHAR *pacIpAddr);

/**
 * \brief 向地址对管理模块新增可用的UE地址
 *
 * 此函数由其它模块进行调用，地址对管理模块会根据设定值及
 * 之前已经有的P-CSCF地址信息按照一定的规则更新地址对列表
 *
 * 地址对列表生成规则参考 #IMSA_RegAddrPairMgrAddPcscfAddr
 *
 * @param[in]   ulRegType       注册类型
 * @param[in]   enIpType        新增的UE地址类型
 * @param[in]   paucIpAddr      新增的UE地址
 *
 * @retval      VOS_TRUE        新增UE成功，并根据规则刷新了地址对列表
 */
extern VOS_UINT32 IMSA_RegAddrPairMgrAddUeAddr(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                               IMSA_IP_TYPE_ENUM_UINT8 enIpType,
                                               const VOS_CHAR *pacIpAddr);

/**
 * \brief 从地址对管理模块删除一个UE地址
 *
 * 此函数由其它模块进行调用，地址对管理模块会根据设定值及
 * 之前已经有的P-CSCF地址信息按照一定的规则更新地址对列表
 *
 * @param[in]   ulRegType       注册类型
 * @param[in]   enIpType        删除的UE地址类型
 * @param[in]   paucIpAddr      删除的UE地址
 *
 * @retval      VOS_TRUE        删除UE成功，并根据规则刷新了地址对列表
 */
extern VOS_UINT32 IMSA_RegAddrPairMgrRmvUeAddr(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                               IMSA_IP_TYPE_ENUM_UINT8 enIpType,
                                               VOS_CHAR *pacIpAddr);

/**
 * \brief 获取注册上的参数
 *
 * @param[in]   ulRegType       注册类型
 * @param[out]  paucUeAddr      存放返回的UE地址
 * @param[in]   paucPcscfAddr   存放返回的P-CSCF地址
 *
 * @retval      VOS_TRUE        获取当前正在使用的地址对信息成功
 */
extern VOS_UINT32 IMSA_RegGetRegedPara
(
    IMSA_REG_TYPE_ENUM_UINT8            ulRegType,
    VOS_CHAR                           *pacUeAddr,
    VOS_CHAR                           *pacPcscfAddr,
    IMSA_IP_TYPE_ENUM_UINT8            *penIptype
);


/**
 * \brief 是否定义了EMC承载的NV项
 * @retval      IMSA_TRUE        定义了紧急呼承载
 * @retval      IMSA_FALSE       没有定义紧急呼承载
 */
extern VOS_UINT32 IMSA_CONN_IsEmcPdpDefined( VOS_VOID );

/**
 * \brief 设置SRVCC标识
 * @param[in]   ulSrvccFlag       SRVCC标识
 */
extern VOS_VOID IMSA_CallSetSrvccFlag
(
    VOS_UINT32                          ulSrvccFlag
);

/**
 * \brief 获取SRVCC标识
 * @retval      IMSA_TRUE        在SRVCC过程中
 * @retval      IMSA_FALSE       不在SRVCC过程中
 */
extern VOS_UINT32 IMSA_CallGetSrvccFlag( VOS_VOID );

/**
 * \brief 设置不上报ALL RELEASD事件标识
 * @param[in]   ulNotReportAllReleasdFlag       不上报ALL RELEASD事件标识
 */
extern VOS_VOID IMSA_CallSetNotReportAllReleasedFlag
(
    VOS_UINT32                          ulNotReportAllReleasdFlag
);

/**
 * \brief 获取不上报ALL RELEASD事件标识
 * @retval      IMSA_TRUE        不能上报ALL RELEASED事件
 * @retval      IMSA_FALSE       可以上报ALL RELEASED事件
 */
extern VOS_UINT32 IMSA_CallGetNotReportAllReleasedFlag( VOS_VOID );

extern VOS_UINT32 IMSA_SRV_IsConningRegState(VOS_UINT8 ucIsEmc);
extern VOS_VOID IMSA_CONN_UpdateNicPdpInfo( VOS_VOID );


extern VOS_UINT32 IMSA_CONN_HasActiveVoicePdp
(
    VOS_VOID
);
extern VOS_UINT32 IMSA_CONN_HasActiveVideoPdp
(
    VOS_VOID
);


extern VOS_UINT32 IMSA_IsCallConnExist(VOS_VOID);
extern VOS_UINT32 IMSA_IsSmsConnExist(VOS_VOID);
extern VOS_UINT32 IMSA_IsSsConnExist(VOS_VOID);

extern VOS_VOID IMSA_CMCCDeregProc(VOS_VOID);

VOS_VOID IMSA_CommonDeregProc(VOS_VOID);

extern VOS_UINT32 IMSA_CONN_IsExitPersistentBearer
(
    VOS_VOID
);
extern VOS_UINT32 IMSA_RegAddrPairMgrGetCurrent(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                             VOS_CHAR  *pacUeAddr,
                                             VOS_CHAR  *pacPcscfAddr);
extern VOS_UINT32 IMSA_SRV_IsCurRatSupportIms( VOS_VOID );

#if (FEATURE_ON == FEATURE_PTM)
extern VOS_VOID IMSA_RegErrRecord
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8 enRegFailReason
);
extern VOS_VOID IMSA_PdnRejErrRecord
(
    IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32   enPdnConnRejCause
);
extern VOS_VOID IMSA_EmcCallErrRecord
(
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_ENUM_UINT16   enCallFailReason,
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ENUM_UINT16    enRegFailReason,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16  enPdnConnNwRej,
    VOS_UINT16                                      usCallSipStatusCode,
    VOS_UINT16                                      usEmcRegSipStatusCode,
    IMSA_ERR_LOG_CALL_STATUS_ENUM_UINT8             enCallStatus
);
extern VOS_VOID IMSA_NormInitDeregErrRecord
(
    IMSA_ERR_LOG_INIT_DEREG_REASON_ENUM_UINT32  enInitDeregCause
);
extern VOS_VOID IMSA_NotInitRegErrRecord
(
    VOS_VOID
);
#endif
extern VOS_UINT32 IMSA_IsImsEmcServiceEstablishSucc(VOS_VOID);
extern VOS_VOID IMSA_StopImsEmcService(VOS_VOID);
extern VOS_UINT32 IMSA_SRV_IsNotNeedNwDereg
(
    VOS_VOID
);

extern PS_RRM_RF_SHARED_ENUM_UINT8 IMSA_Dsds_RRM_RfResourceIsShared(VOS_VOID);
extern VOS_VOID  IMSA_DsdsProcResourceApplyReq
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc,
    VOS_UINT32                              ulPara,
    VOS_UINT8                               ucHasBuffer
);

extern VOS_VOID IMSA_RegFsmProcWaitRetryResourceApplyExp( VOS_VOID );
extern VOS_VOID IMSA_CallProcMoOrEmcResourceApplyTimerExp
(
    VOS_VOID
);
extern VOS_VOID IMSA_CallProcMtResourceApplyTimerExp
(
    IMSA_IMS_CALL_STATE_ENUM_UINT8         enCallState
);
extern VOS_VOID IMSA_ProcStopResourceApplyTimerExp
(
    VOS_VOID
);
extern VOS_UINT32 IMSA_SRV_ProcDeRegResourceApplyTimerExp
(
    VOS_VOID
);
extern VOS_VOID IMSA_SMSProcMoResourceApplyTimerExp
(
    VOS_VOID
);
extern VOS_VOID IMSA_SMSProcMtResourceApplyTimerExp
(
    VOS_VOID
);

extern VOS_VOID IMSA_ProcStopResourceApplyCnf
(
    VOS_VOID
);
extern VOS_UINT32 IMSA_SRV_ProcDeRegResourceApplyCnf
(
    VOS_VOID
);

extern VOS_VOID IMSA_DsdsSndRrmReleaseInd
(
    RRM_PS_TASK_TYPE_ENUM_UINT16    enTaskType,
    PS_BOOL_ENUM_UINT8              enRelAllFlg,
    VOS_UINT32                      ulDelayTime
);
extern VOS_VOID IMSA_DsdsSaveMoCallMsg
(
    SPM_IMSA_CALL_ORIG_REQ_STRU             *pstMoCall
);
extern VOS_VOID IMSA_DsdsSaveMoEmcCallMsg
(
    SPM_IMSA_CALL_ORIG_REQ_STRU             *pstEmcCall
);

extern VOS_VOID IMSA_DsdsSaveEconfCallMsg
(
    SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU       *pstEnhancedConferrence
);
extern VOS_VOID IMSA_DsdsSaveMoSmsMsg
(
    const MSG_IMSA_RP_DATA_REQ_STRU               *pstMoSms
);
extern VOS_VOID IMSA_DsdsSaveMtSmsMsg
(
    const IMSA_IMS_OUTPUT_SMS_EVENT_STRU            *pstMtSms
);
extern VOS_VOID IMSA_DsdsSaveMoSmmaMsg
(
    const MSG_IMSA_SMMA_REQ_STRU                  *pstSmma
);
extern IMSA_TASKTYPE_STATUS_ENUM_UINT8 IMSA_DsdsGetTaskStatusByTaskType
(
    RRM_PS_TASK_TYPE_ENUM_UINT16 enTaskType
);
extern VOS_VOID IMSA_SRV_ProcOccupyDeregResDelayTimerExp( VOS_VOID );
extern VOS_VOID IMSA_SMSProcMoSmsRfOccupiedDelayTimerExp
(
    VOS_VOID
);
extern VOS_VOID IMSA_SMSProcMtSmsRfOccupiedDelayTimerExp
(
    VOS_VOID
);
extern VOS_VOID  IMSA_SRV_ProcGetNorServiceResourceApplyExp
(
    VOS_VOID
);
extern VOS_UINT32 IMSA_SRV_ProcPeriodRegResourceApplyExp
(
    VOS_VOID
);
extern VOS_VOID IMSA_SMSProcSmmaResourceApplyTimerExp
(
    VOS_VOID
);
extern VOS_UINT32 IMSA_RegFsmProcWaitRetryResourceApplyCnf
(
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enParamType
);
extern VOS_UINT32 IMSA_SRV_ProcPeriodRegResourceApplyCnf
(
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enAddrType
);
extern VOS_UINT32 IMSA_SRV_ProcGetNormSevResourceApplyCnf
(
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enAddrType
);
extern VOS_VOID IMSA_CallProcMoCallResourceApplyCnf
(
    const SPM_IMSA_CALL_ORIG_REQ_STRU *pstAppReq
);
extern VOS_VOID IMSA_CallProcEconfResourceApplyCnf
(
    const SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU *pstAppReq
);
extern VOS_VOID IMSA_CallProcEmcResourceApplyCnf
(
    const SPM_IMSA_CALL_ORIG_REQ_STRU *pstAppReq
);
extern VOS_UINT32 IMSA_CallProcMtResourceApplyCnf
(
    IMSA_IMS_CALL_STATE_ENUM_UINT8         enCallState
);
extern VOS_VOID IMSA_SMSProcMoResourceApplyCnf
(
    const MSG_IMSA_RP_DATA_REQ_STRU *pstRpDataReq
);
extern VOS_VOID IMSA_SMSProcSmmaRetransResourceApplyCnf
(
    VOS_VOID
);
extern VOS_VOID IMSA_SMSProcMtResourceApplyCnf
(
    const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms
);
extern VOS_VOID IMSA_DsdsModifyTaskSrcByTaskType
(
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc,
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType
);
extern VOS_VOID IMSA_DsdsSndRrmDeRegisterInd
(
    RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType
);
extern VOS_UINT32  IMSA_DsdsProcResourceRegisterInd
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc,
    VOS_UINT32                              ulPara
);
extern VOS_VOID IMSA_DsdsProcResourceRelease
(
    RRM_PS_TASK_TYPE_ENUM_UINT16 enTaskType
);
extern VOS_VOID IMSA_SMSProcSmmaResourceApplyCnf
(
    const MSG_IMSA_SMMA_REQ_STRU *pstSmmaReq
);
extern VOS_VOID  IMSA_DsdsProcResourceOccupyCnf
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType
);

extern IMSA_RESOURCE_STATUS_ENUM_UINT8  IMSA_DsdsGetResourceStatus
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType
);
extern VOS_UINT32 IMSA_StartImsEmergServiceAbilityCheck
(
    IMSA_EMC_CALL_TYPE_ENUM_UINT32     *penEmcCallType
);
extern VOS_VOID IMSA_StartImsEmcService
(
    VOS_VOID
);
extern VOS_VOID IMSA_SRV_ProcStopMsgWhenNoRf
(
    VOS_VOID
);
extern VOS_VOID IMSA_RegNotifyImsLocalDereg
(
    VOS_VOID
);

extern VOS_VOID IMSA_SRV_ProcReceivedUsimReadfileCnf
(
    VOS_VOID
);
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

#endif /* end of ImsaIntraInterface.h */

