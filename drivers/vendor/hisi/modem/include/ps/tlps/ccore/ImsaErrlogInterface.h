

#ifndef __IMSAERRLOGINTERFACE_H__
#define __IMSAERRLOGINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "omerrorlog.h"

#pragma  pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/
#define IMSA_ERR_LOG_IPV6_STRING_LEN                      (46)

#define IMSA_RING_BUFFER_SIZE                           (1024)              /* IMSA层的环形buffer的大小 */

#define IMSA_ERR_LOG_CTRL_LEVEL_NULL                     (0)                     /* ErrLog等级未定义*/
#define IMSA_ERR_LOG_CTRL_LEVEL_CRITICAL                 (1)                     /* ErrLog等级紧急 */
#define IMSA_ERR_LOG_CTRL_LEVEL_MAJOR                    (2)                     /* ErrLog等级重要 */
#define IMSA_ERR_LOG_CTRL_LEVEL_MINOR                    (3)                     /* ErrLog等级次要 */
#define IMSA_ERR_LOG_CTRL_LEVEL_WARNING                  (4)                     /* ErrLog等级提示 */



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum IMSA_USIM_STATUS_ENUM
{
    IMSA_USIM_STATUS_UNAVAILABLE        = 0x01,            /**< 卡不可用，包括读取必须卡参数失败、PS域卡无效等 */
    IMSA_USIM_STATUS_AVAILABLE          = 0x02,            /**< 卡有效可用 */

    IMSA_USIM_STATUS_BUTT
};
typedef VOS_UINT8  IMSA_USIM_STATUS_ENUM_UINT8;


enum IMSA_OM_ERR_LOG_MSG_TYPE_ENUM
{
    ID_IMSA_OM_REG_ERROR_LOG_IND                    = 0x01, /* _H2ASN_MsgChoice IMSA_REG_ERROR_LOG_INFO_STRU */
    ID_IMSA_OM_CALL_ERROR_LOG_IND                   = 0x02, /* _H2ASN_MsgChoice IMSA_CALL_ERROR_LOG_INFO_STRU */
    ID_IMSA_OM_NOT_INIT_REG_ERR_LOG_IND             = 0x03, /* _H2ASN_MsgChoice IMSA_NOT_INIT_REG_ERROR_LOG_INFO_STRU*/
    ID_IMSA_OM_NORM_PDN_CONN_REJ_ERR_LOG_IND        = 0x04, /* _H2ASN_MsgChoice IMSA_NORM_PDN_CONN_FAIL_ERROR_LOG_INFO_STRU*/
    ID_IMSA_OM_NORM_REG_FAIL_ERR_LOG_IND            = 0x05, /* _H2ASN_MsgChoice IMSA_NORM_REG_FAIL_ERROR_LOG_INFO_STRU*/
    ID_IMSA_OM_NORM_INIT_DEREG_ERR_LOG_IND          = 0x06, /* _H2ASN_MsgChoice IMSA_NORM_INIT_DEREG_ERROR_LOG_INFO_STRU*/
    ID_IMSA_OM_NORM_CALL_FAIL_ERR_LOG_IND           = 0x07, /* _H2ASN_MsgChoice IMSA_NORM_CALL_ERROR_LOG_INFO_STRU */
    ID_IMSA_OM_EMC_CALL_FAIL_ERR_LOG_IND            = 0x08, /* _H2ASN_MsgChoice IMSA_EMC_CALL_ERROR_LOG_INFO_STRU */
    ID_IMSA_OM_MODIFY_CALL_TYPE_FAIL_ERR_LOG_IND    = 0x09, /* _H2ASN_MsgChoice IMSA_MODIFY_CALL_TYPE_ERROR_LOG_INFO_STRU*/

    ID_IMSA_OM_ERR_LOG_MSG_TYPE_BUTT
};
typedef VOS_UINT32    IMSA_OM_ERR_LOG_MSG_TYPE_ENUM_UINT32;


enum IMSA_ERR_LOG_MSG_TYPE_ENUM
{
    IMSA_ERR_LOG_MSG_SET_ERR_REPORT = 0x01, /* 上层触发故障上报 */
    IMSA_ERR_LOG_MSG_ERR_REPORT_END = 0x02, /* 故障上报结束 */
    IMSA_ERR_LOG_MSG_ON_OFF         = 0x03, /* 控制上类型开关 */
    IMSA_ERR_LOG_MSG_ERR_REPORT     = 0x04, /* 故障上报 */
    IMSA_ERR_LOG_MSG_FTM_REPORT     = 0x05, /* 工程模式主动上报 */
    IMSA_ERR_LOG_MSG_RESULT         = 0x06, /* 上报Result */
    IMSA_ERR_LOG_MSG_FTM_REQ        = 0x07, /* 工程模式命令 */
    IMSA_ERR_LOG_MSG_FTM_CNF        = 0x08, /* 工程模式响应 */


    IMSA_ERR_LOG_MSG_TYPE_BUTT
};
typedef VOS_UINT32    IMSA_ERR_LOG_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : IMSA_ERR_LOG_ALARM_TYPE_ENUM_UINT16
 枚举说明  : 商用告警类型枚举定义
 修改历史  :

 1.日    期    : 2015年01月5日
   作    者    : W00209181
   修改内容    : 新建枚举类型
*****************************************************************************/
enum IMSA_ERR_LOG_ALARM_TYPE_ENUM
{
    IMSA_ERR_LOG_ALARM_TYPE_COMMUNICATION               = 0x01,         /* 表示通信 */
    IMSA_ERR_LOG_ALARM_TYPE_TRANSACTION_QULITY          = 0x02,         /* 表示业务质量 */
    IMSA_ERR_LOG_ALARM_TYPE_PROCESS_ERROR               = 0x03,         /* 表示处理出错 */
    IMSA_ERR_LOG_ALARM_TYPE_EQIPMENT_ERROR              = 0x04,         /* 表示设备故障 */
    IMSA_ERR_LOG_ALARM_TYPE_ENVIR_ERROR                 = 0x05,         /* 表示环境故障 */

    IMSA_ERR_LOG_ALARM_TYPE_BUTT
};
typedef VOS_UINT16  IMSA_ERR_LOG_ALARM_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    :   IMSA_ERR_LOG_ERRLOG_PROCESS_EVENT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :  表示当前IMSA具体是哪一个流程
*****************************************************************************/
enum IMSA_ERR_LOG_ALM_ID_ENUM
{
    IMSA_ERR_LOG_ALM_CALL_FAIL_EVENT        = 0x01,    /* volte呼叫流程 */
    IMSA_ERR_LOG_ALM_REG_FAIL_EVENT         = 0x02,    /* IMS注册失败 */
    IMSA_ERR_LOG_ALM_MNTN                   = 0x03,    /* 溢出计数 */

    IMSA_ERR_LOG_ALM_NORM_NOT_INIT_REG_EVENT    = 0x04, /* 未发起注册流程 */
    IMSA_ERR_LOG_ALM_NORM_PDN_CONN_REJ_EVENT    = 0x05, /* PND建链被拒流程 */
    IMSA_ERR_LOG_ALM_NORM_REG_FAIL_EVENT        = 0x06, /* 普通注册失败 */
    IMSA_ERR_LOG_ALM_NORM_INIT_DEREG_EVENT      = 0x07, /* 主动发起去注册流程 */
    IMSA_ERR_LOG_ALM_NORM_CALL_FAIL_EVENT       = 0x08, /* 普通呼叫失败流程 */
    IMSA_ERR_LOG_ALM_EMC_CALL_FAIL_EVENT        = 0x09, /* 紧急呼叫失败流程 */
    IMSA_ERR_LOG_ALM_MODIFY_CALL_TYPE_FAIL_EVENT= 0x0a, /* 切换呼叫类型失败流程 */

    IMSA_ERR_LOG_ALM_BUTT
};
typedef VOS_UINT16  IMSA_ERR_LOG_ALM_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    :   IMSA_ERR_LOG_VOPS_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :  网侧是否具备IMS over PS能力
*****************************************************************************/
enum IMSA_ERR_LOG_VOPS_STATUS_ENUM
{
    IMSA_ERR_LOG_VOPS_STATUS_NOT_SUPPORT            = 0x01,         /* 支持 */
    IMSA_ERR_LOG_VOPS_STATUS_SUPPORT                = 0x02,         /* 不支持 */
    IMSA_ERR_LOG_VOPS_STATUS_BUTT
};
typedef VOS_UINT8 IMSA_ERR_LOG_VOPS_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    :   IMSA_ERR_LOG_PS_SERVICE_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :  当前网络PS服务状态
*****************************************************************************/
enum IMSA_ERR_LOG_PS_SERVICE_STATUS_ENUM
{
    IMSA_ERR_LOG_PS_SERVICE_STATUS_NORMAL_SERVICE       = 0x01,     /* 正常服务 */
    IMSA_ERR_LOG_PS_SERVICE_STATUS_LIMITED_SERVICE      = 0x02,     /* 受限服务 */
    IMSA_ERR_LOG_PS_SERVICE_STATUS_NO_SERVICE           = 0x03,     /* 无服务 */
    IMSA_ERR_LOG_PS_SERVICE_STATUS_BUTT
};
typedef VOS_UINT8 IMSA_ERR_LOG_PS_SERVICE_STATUS_ENUM_UINT8;


/*****************************************************************************
 枚举名    :   IMSA_ERR_LOG_PDN_CONN_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :  PDN连接状态
*****************************************************************************/
enum IMSA_ERR_LOG_PDN_CONN_STATUS_ENUM
{
    IMSA_ERR_LOG_PDN_CONN_STATUS_IDLE               = 0x01,         /* 不存在连接 */
    IMSA_ERR_LOG_PDN_CONN_STATUS_CONNING            = 0x02,         /* 正在建立连接 */
    IMSA_ERR_LOG_PDN_CONN_STATUS_RELEASING          = 0x03,         /* 正在释放连接 */
    IMSA_ERR_LOG_PDN_CONN_STATUS_CONN               = 0x04,         /* 存在连接 */
    IMSA_ERR_LOG_PDN_CONN_STATUS_BUTT
};
typedef VOS_UINT8  IMSA_ERR_LOG_PDN_CONN_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    :   IMSA_ERR_LOG_REG_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :  IMS注册状态
*****************************************************************************/
enum IMSA_ERR_LOG_REG_STATUS_ENUM
{
    IMSA_ERR_LOG_REG_STATUS_NOT_REGISTER            = 0x01,     /* 未注册状态 */
    IMSA_ERR_LOG_REG_STATUS_REGISTERING             = 0x02,     /* 正在注册状态 */
    IMSA_ERR_LOG_REG_STATUS_REGISTERED              = 0x03,     /* 已注册状态 */
    IMSA_ERR_LOG_REG_STATUS_DEREGING                = 0x04,     /* 正在去注册状态 */
    IMSA_ERR_LOG_REG_STATUS_WAIT_RETRY              = 0x05,     /* 正在等待重新尝试状态 */
    IMSA_ERR_LOG_REG_STATUS_PENDING                 = 0x06,     /* PENDING状态 */
    IMSA_ERR_LOG_REG_STATUS_ROLLING_BACK            = 0x07,     /* ROLLINGBACK状态 */
    IMSA_ERR_LOG_REG_STATUS_BUTT
};
typedef VOS_UINT8 IMSA_ERR_LOG_REG_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : IMSA_ERR_LOG_SRV_STATUS_ENUM_UINT8
 结构说明  : service状态枚举
*****************************************************************************/
enum IMSA_ERR_LOG_SRV_STATUS_ENUM
{
   IMSA_ERR_LOG_SRV_STATUS_IDLE_DEREG           = 0x00,    /**< IDLE&DEREG */
   IMSA_ERR_LOG_SRV_STATUS_CONNING_DEREG        = 0x10,    /**< CONNING&DEREG */
   IMSA_ERR_LOG_SRV_STATUS_CONNING_REG          = 0x13,    /**< CONNING&REG */
   IMSA_ERR_LOG_SRV_STATUS_RELEASING_DEREG      = 0x20,    /**< RELEASING&DEREG */
   IMSA_ERR_LOG_SRV_STATUS_CONN_DEREG           = 0x30,    /**< CONN&DEREG */
   IMSA_ERR_LOG_SRV_STATUS_CONN_REGING          = 0x31,    /**< CONN&REGING */
   IMSA_ERR_LOG_SRV_STATUS_CONN_DEREGING        = 0x32,    /**< CONN&DEREGING */
   IMSA_ERR_LOG_SRV_STATUS_CONN_REG             = 0x33,    /**< CONN&REG */

   IMSA_ERR_LOG_SRV_STATUS_BUTT                 = 0xff
};
typedef VOS_UINT8   IMSA_ERR_LOG_SRV_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    :  IMSA_ERR_LOG_CALL_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :  呼叫状态
*****************************************************************************/
enum IMSA_ERR_LOG_CALL_STATUS_ENUM
{
    IMSA_ERR_LOG_CALL_STATUS_IDLE                   = 0x01,     /* IDLE状态     */
    IMSA_ERR_LOG_CALL_STATUS_DIALING                = 0x02,     /* DIALING状态  */
    IMSA_ERR_LOG_CALL_STATUS_TRYING                 = 0x03,     /* TRYING状态   */
    IMSA_ERR_LOG_CALL_STATUS_ALERTING               = 0x04,     /* ALERTING状态 */
    IMSA_ERR_LOG_CALL_STATUS_ACTIVE                 = 0x05,     /* ACTIVE状态   */
    IMSA_ERR_LOG_CALL_STATUS_INCOMING               = 0x06,     /* INCOMING状态 */
    IMSA_ERR_LOG_CALL_STATUS_HELD                   = 0x07,     /* HELD状态     */
    IMSA_ERR_LOG_CALL_STATUS_WAITING                = 0x08,     /* WAITING状态  */
    IMSA_ERR_LOG_CALL_STATUS_BUTT
};
typedef VOS_UINT8 IMSA_ERR_LOG_CALL_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    :  IMSA_ERR_LOG_MPTY_STATE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :  是否多方呼叫
*****************************************************************************/
enum IMSA_ERR_LOG_MPTY_STATE_ENUM
{
    IMSA_ERR_LOG_CALL_NOT_IN_MPTY                   = 0x01,     /* 不是多方呼叫 */
    IMSA_ERR_LOG_CALL_IN_MPTY                       = 0x02,     /* 是多方呼叫 */
    IMSA_ERR_LOG_CALL_MPYT_STATE_BUTT
};
typedef VOS_UINT8  IMSA_ERR_LOG_MPTY_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    :  IMSA_ERR_LOG_REGISTER_REASON_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :  是否多方呼叫
*****************************************************************************/
enum IMSA_ERR_LOG_REGISTER_REASON_ENUM
{
    IMSA_ERR_LOG_REGISTER_REASON_ADDR_PARAM_NEW         = 0x01,    /* 使用新的地址队发起注册 */
    IMSA_ERR_LOG_REGISTER_REASON_ADDR_PARAM_SAME        = 0x02,  /* 使用当前地址队发起注册 */
    IMSA_ERR_LOG_REGISTER_REASON_ADDR_PARAM_NEXT        = 0x03,    /* 使用下个地址队发起注册 */
    IMSA_ERR_LOG_REGISTER_REASON_ADDR_PARAM_RESTORATION = 0x04,  /* 如果有其他地址队，则使用其他地址对发起注册，否则使用当前地址对发起注册 */
    IMSA_ERR_LOG_REGISTER_REASON_BUTT
};
typedef VOS_UINT8  IMSA_ERR_LOG_REGISTER_REASON_ENUM_UINT8;

/*****************************************************************************
 枚举名    :  IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  :  注册失败的原因值
*****************************************************************************/
enum IMSA_ERR_LOG_REG_FAIL_REASON_ENUM
{
    IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE                 = 0x01,     /**< 被服务器拒绝，具体拒绝原因值详见对应数据结构中的Status Code，根据不同的原因值可能会携带一些其它的头域 */
    IMSA_ERR_LOG_REG_FAIL_REASON_TIMEOUT                = 0x02,     /**< 发送或接收SIP报文超时，具体超时的定时器详见对应数据结构中的 Timer Id */
    IMSA_ERR_LOG_REG_FAIL_REASON_TRANSPORT              = 0x03,     /**< 发送或接收SIP报文时，底层传输发生错误 */
    IMSA_ERR_LOG_REG_FAIL_REASON_NO_ADDR_PAIR           = 0x04,     /**< 没有可以再使用的注册地址对 */
    IMSA_ERR_LOG_REG_FAIL_REASON_MOVE_TO_NOT_SUP_IMS_RAT= 0x05,     /**< 注册过程中移动到不支持VOLTE的接入技术下 */

    IMSA_ERR_LOG_REG_FAIL_REASON_BUTT
};
typedef VOS_UINT8  IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8;

/*****************************************************************************
 枚举名称: IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM
 枚举说明: PDN建链被拒原因值

 修改历史      :
  1.日    期   : 2015年01月06日
    作    者   : w00209181
    修改内容   : 新增枚举
*****************************************************************************/
enum IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM
{
    /* IMSA内部错误 */
    IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_PARA_ERR                              = 1,    /**< CONN模块命令执行失败，由于参数错误 */
    IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_TIMER_EXP                             = 2,    /**< CONN模块命令执行失败，由于定时器超时 */
    IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_CONN_RELEASING                        = 3,    /**< CONN模块命令执行失败，由于正在释放连接 */
    IMSA_ERR_LOG_PDNREJ_CAUSE_PDP_ACTIVATE_LIMIT                         = 4,    /**< CONN模块命令执行失败，由于正在释放连接 */
    IMSA_ERR_LOG_PDNREJ_CAUSE_SAME_APN_OPERATING                         = 5,    /**< CONN模块命令执行失败，由于正在释放连接 */
    IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_OTHERS                                = 6,    /**< CONN模块命令执行失败，由于其他原因 */

    /*----------------------------------------------------------------------
       TAF上报的SM网络原因值, 取值范围[0x0100, 0x01FF]
       由于3GPP协议已经定义了具体的(E)SM网络原因值, (E)SM上报的取值为协议
       定义的原因值加上偏移量(0x100)
       (1) SM Cause : Refer to TS 24.008 section 10.5.6.6
       (2) ESM Cause: Refer to TS 24.301 section 9.9.4.4
    *---------------------------------------------------------------------*/
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_OPERATOR_DETERMINED_BARRING          =  8,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MBMS_BC_INSUFFICIENT                 =  24,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE                 =  25,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_INSUFFICIENT_RESOURCES               =  26,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN                =  27,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE             =  28,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_USER_AUTHENTICATION_FAIL             =  29,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_ACTIVATION_REJECTED_BY_GGSN          =  30,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED      =  31,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SERVICE_OPTION_NOT_SUPPORTED         =  32,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED     =  33,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER        =  34,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_NSAPI_ALREADY_USED                   =  35,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_REGULAR_DEACTIVATION                 =  36,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_QOS_NOT_ACCEPTED                     =  37,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_NETWORK_FAILURE                      =  38,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_REACTIVATION_REQUESTED               =  39,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_FEATURE_NOT_SUPPORT                  =  40,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SEMANTIC_ERR_IN_TFT                  =  41,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SYNTACTIC_ERR_IN_TFT                 =  42,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_UKNOWN_PDP_CONTEXT                   =  43,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SEMANTIC_ERR_IN_PACKET_FILTER        =  44,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER      =  45,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED    =  46,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MULTICAST_GROUP_MEMBERHHSHIP_TIMEOUT =  47,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_REQUEST_REJECTED_BCM_VIOLATION       =  48,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_LAST_PDN_DISCONN_NOT_ALLOWED         =  49,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED           =  50,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED           =  51,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED     =  52,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_INFORMATION_NOT_RECEIVED             =  53,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PDN_CONNECTION_DOES_NOT_EXIST        =  54,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED =  55,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_COLLISION_WITH_NW_INITIATED_REQUEST  =  56,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_UNSUPPORTED_QCI_VALUE                =  59,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_BEARER_HANDLING_NOT_SUPPORTED        =  60,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_INVALID_TI                           =  81,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SEMANTICALLY_INCORRECT_MESSAGE       =  95,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_INVALID_MANDATORY_INFO               =  96,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MSG_TYPE_NON_EXISTENT                =  97,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MSG_TYPE_NOT_COMPATIBLE              =  98,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_IE_NON_EXISTENT                      =  99,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_CONDITIONAL_IE_ERR                   =  100,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MSG_NOT_COMPATIBLE                   =  101,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED             =  111,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_APN_RESTRICTION_INCOMPATIBLE         =  112,

    IMSA_ERR_LOG_PDNREJ_CAUSE_BUTT
};
typedef VOS_UINT32 IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32;
/*****************************************************************************
    枚举名    : IMSA_ERR_LOG_CALL_TYPE_ENUM_UINT8
    枚举说明  : 呼叫类型
*****************************************************************************/
enum    IMSA_ERR_LOG_CALL_TYPE_ENUM
{
    IMSA_ERR_LOG_CALL_TYPE_VOICE    = 0,      /* Voice only call */
    IMSA_ERR_LOG_CALL_TYPE_VIDEO_TX = 1,      /* PS Video telephony call: one way TX video,Two way audio */
    IMSA_ERR_LOG_CALL_TYPE_VIDEO_RX = 2,      /* Video telephony call: ony way RX video,two way audio */
    IMSA_ERR_LOG_CALL_TYPE_VIDEO    = 3,      /* video call */
    IMSA_ERR_LOG_CALL_TYPE_EMC      = 9,      /* emergency call */
    IMSA_ERR_LOG_CALL_TYPE_BUTT
};
typedef VOS_UINT8 IMSA_ERR_LOG_CALL_TYPE_ENUM_UINT8;

/*****************************************************************************
    枚举名    : IMSA_CAMPED_RAT_TYPE_ENUM
    枚举说明  : UE驻留的网络类型
*****************************************************************************/
enum    IMSA_ERR_LOG_CAMPED_RAT_TYPE_ENUM
{
    IMSA_ERR_LOG_CAMPED_RAT_TYPE_NULL                   = 0,
    IMSA_ERR_LOG_CAMPED_RAT_TYPE_GSM,
    IMSA_ERR_LOG_CAMPED_RAT_TYPE_UTRAN,
    IMSA_ERR_LOG_CAMPED_RAT_TYPE_EUTRAN,
    IMSA_ERR_LOG_CAMPED_RAT_TYPE_BUTT
};
typedef VOS_UINT8 IMSA_ERR_LOG_CAMPED_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名称: IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ENUM_UINT32
 枚举说明: PDN建链被拒原因值

 修改历史      :
  1.日    期   : 2015年01月06日
    作    者   : w00209181
    修改内容   : 新增枚举
*****************************************************************************/
enum IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ENUM
{
    /* IMSA内部错误 */
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_PARA_ERR                = 1,    /**< CONN模块命令执行失败，由于参数错误 */
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_TIMER_EXP               = 2,    /**< CONN模块命令执行失败，由于定时器超时 */
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_CONN_RELEASING          = 3,    /**< CONN模块命令执行失败，由于正在释放连接 */
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_PDP_ACTIVATE_LIMIT           = 4,    /**< CONN模块命令执行失败，由于正在释放连接 */
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_SAME_APN_OPERATING           = 5,    /**< CONN模块命令执行失败，由于正在释放连接 */
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_OTHERS                  = 6,    /**< CONN模块命令执行失败，由于其他原因 */
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_CONNING                 = 7,
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_NO_IMS_PDP_CONTXT            = 8,
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_CONN_STATE_MISMATCH          = 9,
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_TIMER_WAIT_IPV6_INFO_EXP     = 10,   /**< 等待IPV6定时器超时 */
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_NW_REJ                       = 11,   /**< PDN建链被网侧拒绝 */
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ORIG_TIMER_EXP               = 12,   /**< 等待SPM拨号超时 */

    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_BUTT
};
typedef VOS_UINT32 IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ENUM_UINT32;

/*****************************************************************************
 枚举名称: IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM
 枚举说明: PDN建链被网侧拒原因值

 修改历史      :
  1.日    期   : 2015年07月31日
    作    者   : w00209181
    修改内容   : 新增枚举
*****************************************************************************/
enum IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM
{
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE                                 = 0,
    /*----------------------------------------------------------------------
       TAF上报的SM网络原因值, 取值范围[0x0100, 0x01FF]
       由于3GPP协议已经定义了具体的(E)SM网络原因值, (E)SM上报的取值为协议
       定义的原因值加上偏移量(0x100)
       (1) SM Cause : Refer to TS 24.008 section 10.5.6.6
       (2) ESM Cause: Refer to TS 24.301 section 9.9.4.4
    *---------------------------------------------------------------------*/
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_OPERATOR_DETERMINED_BARRING          =  8,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_MBMS_BC_INSUFFICIENT                 =  24,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_LLC_OR_SNDCP_FAILURE                 =  25,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_INSUFFICIENT_RESOURCES               =  26,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_MISSING_OR_UKNOWN_APN                =  27,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_UNKNOWN_PDP_ADDR_OR_TYPE             =  28,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_USER_AUTHENTICATION_FAIL             =  29,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ACTIVATION_REJECTED_BY_GGSN          =  30,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ACTIVATION_REJECTED_UNSPECIFIED      =  31,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_SERVICE_OPTION_NOT_SUPPORTED         =  32,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_REQUESTED_SERVICE_NOT_SUBSCRIBED     =  33,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_SERVICE_OPTION_TEMP_OUT_ORDER        =  34,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NSAPI_ALREADY_USED                   =  35,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_REGULAR_DEACTIVATION                 =  36,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_QOS_NOT_ACCEPTED                     =  37,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NETWORK_FAILURE                      =  38,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_REACTIVATION_REQUESTED               =  39,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_FEATURE_NOT_SUPPORT                  =  40,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_SEMANTIC_ERR_IN_TFT                  =  41,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_SYNTACTIC_ERR_IN_TFT                 =  42,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_UKNOWN_PDP_CONTEXT                   =  43,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_SEMANTIC_ERR_IN_PACKET_FILTER        =  44,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER      =  45,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED    =  46,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_MULTICAST_GROUP_MEMBERHHSHIP_TIMEOUT =  47,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_REQUEST_REJECTED_BCM_VIOLATION       =  48,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED         =  49,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_PDP_TYPE_IPV4_ONLY_ALLOWED           =  50,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_PDP_TYPE_IPV6_ONLY_ALLOWED           =  51,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_SINGLE_ADDR_BEARERS_ONLY_ALLOWED     =  52,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_INFORMATION_NOT_RECEIVED             =  53,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_PDN_CONNECTION_DOES_NOT_EXIST        =  54,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED =  55,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_COLLISION_WITH_NW_INITIATED_REQUEST  =  56,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_UNSUPPORTED_QCI_VALUE                =  59,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_BEARER_HANDLING_NOT_SUPPORTED        =  60,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_INVALID_TI                           =  81,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_SEMANTICALLY_INCORRECT_MESSAGE       =  95,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_INVALID_MANDATORY_INFO               =  96,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_MSG_TYPE_NON_EXISTENT                =  97,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_MSG_TYPE_NOT_COMPATIBLE              =  98,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_IE_NON_EXISTENT                      =  99,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_CONDITIONAL_IE_ERR                   =  100,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_MSG_NOT_COMPATIBLE                   =  101,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_PROTOCOL_ERR_UNSPECIFIED             =  111,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_APN_RESTRICTION_INCOMPATIBLE         =  112,

    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_BUTT
};
typedef VOS_UINT16 IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16;

/*****************************************************************************
 枚举名    :  IMSA_ERR_LOG_INIT_DEREG_REASON_ENUM_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  :  UE主动发起去注册的原因
*****************************************************************************/
enum IMSA_ERR_LOG_INIT_DEREG_REASON_ENUM
{
    IMSA_ERR_LOG_INIT_DEREG_REASON_PDN_LOST                 = 1,    /* PDN LOST重建失败触发的去注册 */
    IMSA_ERR_LOG_INIT_DEREG_REASON_RAT_OR_VOICE_NOT_SUPPORT = 2,    /* 移动到不支持VOLTE的接入技术下 */
    IMSA_ERR_LOG_INIT_DEREG_REASON_ROAMING_NOT_SUPPORT_REG  = 3,    /* 移动到漫游网络下，且不支持漫游注册 */
    IMSA_ERR_LOG_INIT_DEREG_REASON_NW_INIT                  = 4,    /* 网侧去激活IMS */


    IMSA_ERR_LOG_INIT_DEREG_REASON_BUTT
};
typedef VOS_UINT32 IMSA_ERR_LOG_INIT_DEREG_REASON_ENUM_UINT32;

/*****************************************************************************
    枚举名    : IMSA_CALL_CALL_REASON_RESOURCE_RESULT_ENUM_UINT8
    枚举说明  : 资源预留状态
*****************************************************************************/
enum    IMSA_ERR_LOG_CALL_REASON_RESOURCE_RESULT_ENUM
{
    IMSA_ERR_LOG_CALL_REASON_RESOURCE_READY,
    IMSA_ERR_LOG_CALL_REASON_RESOURCE_ONLY_VOICE,
    IMSA_ERR_LOG_CALL_REASON_RESOURCE_FAILED,
    IMSA_ERR_LOG_CALL_REASON_RESOURCE_RESULT_BUTT
};
typedef VOS_UINT8 IMSA_ERR_LOG_CALL_REASON_RESOURCE_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名    :  IMSA_ERR_LOG_CALL_FAIL_REASON_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  :  呼叫失败的原因值
*****************************************************************************/
enum IMSA_ERR_LOG_CALL_FAIL_REASON_ENUM
{
    IMSA_ERR_LOG_CALL_FAIL_REASON_REMOTE                                             = 1,     /**< 被服务器拒绝，具体拒绝原因值详见对应数据结构中的Status Code，根据不同的原因值可能会携带一些其它的头域 */
    IMSA_ERR_LOG_CALL_FAIL_REASON_TIMEOUT                                            = 2,     /**< 发送或接收SIP报文超时，具体超时的定时器详见对应数据结构中的 Timer Id */
    IMSA_ERR_LOG_CALL_FAIL_REASON_NOT_SUPPORTED_CALL_TYPE                            = 3,     /**< 呼叫类型不支持 */
    IMSA_ERR_LOG_CALL_FAIL_REASON_NOT_ALLOW_NEW_CALL                                 = 4,     /**< 不允许发起新的呼叫 */
    IMSA_ERR_LOG_CALL_FAIL_REASON_SERVICE_NOT_AVAILABLE                              = 5,     /**< 对应的服务不可用 */
    IMSA_ERR_LOG_CALL_FAIL_REASON_RES_READY_FAIL                                     = 6,     /**< 资源预留失败 */

    /* IMS上报的错误*/
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_MULTIPLE_CHOICES                               = 300,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_MOVED_PERMANENTLY                              = 301,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_MOVED_TEMPORARILY                              = 302,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_USE_PROXY                                      = 305,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_ALTERNATIVE_SERVICE                            = 380,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_BAD_REQUEST                                    = 400,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_UNAUTHORIZED                                   = 401,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_PAYMENT_REQUIRED                               = 402,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_FORBIDDEN                                      = 403,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_NOT_FOUND                                      = 404,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_METHOD_NOT_ALLOWED                             = 405,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_NOT_ACCEPTABLE                                 = 406,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_PROXY_AUTHENTICATION_REQUIRED                  = 407,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_REQUEST_TIMEOUT                                = 408,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_CONFLICT_DEPRECATED                            = 409,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_GONE                                           = 410,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_CONDITIONAL_REQUEST_FAILED                     = 412,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_REQUEST_ENTITY_TOO_LARGE                       = 413,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_REQUEST_URI_TOO_LONG                           = 414,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_UNSUPPORTED_MEDIA_TYPE                         = 415,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_UNSUPPORTED_URI_SCHEME                         = 416,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_UNKNOWN_RESOURCE_PRIORITY                      = 417,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_BAD_EXTENSION                                  = 420,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_EXTENSION_REQUIRED                             = 421,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_SESSION_INTERVAL_TOO_SMALL                     = 422,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_INTERVAL_TOO_BRIEF                             = 423,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_BAD_LOCATION_INFORMATION                       = 424,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_USE_IDENTITY_HEADER                            = 428,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_PROVIDE_REFERRER_IDENTITY                      = 429,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_FLOW_FAILED                                    = 430,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_ANONYMITY_DISALLOWED                           = 433,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_BAD_IDENTITY_INFO                              = 436,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_UNSUPPORTED_CERTIFICATE                        = 437,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_INVALID_IDENTITY_HEADER                        = 438,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_FIRST_HOP_LACKS_OUTBOUND_SUPPORT               = 439,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_MAX_BREADTH_EXCEEDED                           = 440,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_BAD_INFO_PACKEAGE                              = 469,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_CONSENT_NEEDED                                 = 470,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_TEMPORARILY_UNAVAILABLE                        = 480,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_CALL_TRANSACTION_DOES_NOT_EXIST                = 481,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_LOOP_DETECTED                                  = 482,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_TOO_MANY_HOPS                                  = 483,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_ADDRESS_INCOMPLETE                             = 484,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_AMBIGUOUS                                      = 485,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_BUSY_HERE                                      = 486,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_REQUEST_TERMINATED                             = 487,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_NOT_ACCEPTABLE_HERE                            = 488,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_BAD_EVENT                                      = 489,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_REQUEST_PENDING                                = 491,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_UNDECIPHERABLE                                 = 493,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_SECURITY_AGREEMENT_REQUIRED                    = 494,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_SERVER_INTERNAL_ERROR                          = 500,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_NOT_IMPLEMENTED                                = 501,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_BAD_GATEWAY                                    = 502,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_SERVICE_UNAVAILABLE                            = 503,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_SERVER_TIME_OUT                                = 504,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_VERSION_NOT_SUPPORTED                          = 505,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_MESSAGE_TOO_LARGE                              = 513,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_PRECONDITION_FAILURE                           = 580,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_BUSY_EVERYWHERE                                = 600,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_DECLINE                                        = 603,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_DOES_NOT_EXIST_ANYWHERE                        = 604,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_GLOBAL_NOT_ACCEPTABLE                          = 606,

    IMSA_ERR_LOG_CALL_FAIL_REASON_BUTT
};
typedef VOS_UINT16  IMSA_ERR_LOG_CALL_FAIL_REASON_ENUM_UINT16;
/*****************************************************************************
 枚举名    :  IMSA_ERR_LOG_CALL_FAIL_REASON_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  :  呼叫失败的原因值
*****************************************************************************/
enum IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_ENUM
{
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE,
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_REMOTE                        = 1,     /**< 被服务器拒绝，具体拒绝原因值详见对应数据结构中的Status Code，根据不同的原因值可能会携带一些其它的头域 */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_TIMEOUT                       = 2,     /**< 发送或接收SIP报文超时，具体超时的定时器详见对应数据结构中的 Timer Id */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NOT_SUPPORTED_CALL_TYPE       = 3,     /**< 呼叫类型不支持 */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NOT_ALLOW_NEW_CALL            = 4,     /**< 不允许发起新的呼叫 */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_SERVICE_NOT_AVAILABLE         = 5,     /**< 对应的服务不可用 */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_RES_READY_FAIL                = 6,     /**< 资源预留失败 */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_CANNOT_FIND_CALLENTITY        = 7,
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NORM_SER_NOT_CONN_REG         = 8,    /**< 普通服务状态不是CONN+REG */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_VOICE_DOMAIN_CS_ONLY          = 9,    /**< 语音域是CS ONLY */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_IMS_VOPS_STATUS_NOT_SUPPORT   = 10,   /**< 网侧不支持VOPS */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_HIFI_START_ABNORMAL           = 11,   /**< HIFI启动异常 */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_VOICE_CALL = 12,   /**< UE能力配置为不支持VOICE CALL */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_VIDEO_CALL = 13,   /**< UE能力配置为不支持VIDEO CALL */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_SSAC_BAR_FOR_VOICE_CALL       = 14,   /**< SSAC,不允许语音呼叫 */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_SSAC_BAR_FOR_VIDEO_CALL       = 15,   /**< SSAC,不允许视频呼叫 */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_TCALL_TIMEOUT                 = 16,   /**< TCALL超时 */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_TQOS_TIMEOUT                  = 17,   /**< TQOS超时 */

    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_CALL_TYPE_MODIFY_FAIL         = 18,   /**< 音频切换失败，具体原因值见usSipStatusCode */

    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_HIFI_EXCEPTION,
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NON_SRVCC_RAT_CHANGE,
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_MEDIA_PDP_RELEASE,
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_SIP_PDP_ERR,
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_REG_ERR,

    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_BUTT
};
typedef VOS_UINT16  IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_ENUM_UINT16;

/*****************************************************************************
 枚举名    : IMSA_VOICE_DOMAIN_ENUM
 结构说明  : UE的Voice Domain类型
*****************************************************************************/
enum IMSA_ERR_LOG_VOICE_DOMAIN_ENUM
{
   IMSA_ERR_LOG_VOICE_DOMAIN_CS_ONLY         = 0,    /**< CS voice only */
   IMSA_ERR_LOG_VOICE_DOMAIN_IMS_PS_ONLY     = 1,    /**< IMS PS voice only */
   IMSA_ERR_LOG_VOICE_DOMAIN_CS_PREFERRED    = 2,    /**< CS voice preferred, IMS PS Voice as secondary */
   IMSA_ERR_LOG_VOICE_DOMAIN_IMS_PS_PREFERRED= 3,    /**< IMS PS voice preferred, CS Voice as secondary */

   IMSA_ERR_LOG_VOICE_DOMAIN_BUTT
};
typedef VOS_UINT8   IMSA_ERR_LOG_VOICE_DOMAIN_ENUM_UINT8;


/*****************************************************************************
 枚举名    :  IMSA_ERR_LOG_REGISTER_ADDR_TYPE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  :  注册地址对类型
*****************************************************************************/
enum IMSA_ERR_LOG_REGISTER_ADDR_TYPE_ENUM
{
    IMSA_ERR_LOG_REGISTER_ADDR_TYPE_ADDR_PARAM_NEW         = 0x01,  /* 使用新的地址队发起注册 */
    IMSA_ERR_LOG_REGISTER_ADDR_TYPE_ADDR_PARAM_SAME        = 0x02,  /* 使用当前地址队发起注册 */
    IMSA_ERR_LOG_REGISTER_ADDR_TYPE_ADDR_PARAM_NEXT        = 0x03,  /* 使用下个地址队发起注册 */
    IMSA_ERR_LOG_REGISTER_ADDR_TYPE_ADDR_PARAM_RESTORATION = 0x04,  /* 如果有其他地址队，则使用其他地址对发起注册，否则使用当前地址对发起注册 */
    IMSA_ERR_LOG_REGISTER_ADDR_TYPE_BUTT
};
typedef VOS_UINT8  IMSA_ERR_LOG_REGISTER_ADDR_TYPE_ENUM_UINT8;


/*****************************************************************************
    枚举名    : IMSA_ERR_LOG_EMC_CALL_TYPE_ENUM_UINT32
    枚举说明  : 紧急呼叫类型
*****************************************************************************/
enum    IMSA_ERR_LOG_EMC_CALL_TYPE_ENUM
{
    IMSA_ERR_LOG_EMC_CALL_TYPE_IN_NORMAL_SRV    = 0,                        /**< 在普通服务上发起紧急呼 */
    IMSA_ERR_LOG_EMC_CALL_TYPE_NO_CARD          = 1,                        /**< 无卡紧急呼 */
    IMSA_ERR_LOG_EMC_CALL_TYPE_EMC_CONN_EMC_REG = 2,                        /**< 有紧急注册的紧急呼 */
    IMSA_ERR_LOG_EMC_CALL_TYPE_BUTT
};
typedef VOS_UINT32 IMSA_ERR_LOG_EMC_CALL_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    :  IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :  紧急注册失败的原因值
*****************************************************************************/
enum IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ENUM
{
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_NONE,
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_NO_EMC_PDP_CONTEXT,                /**< 没有紧急的PDP上下文 */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ORIG_REQ_FAIL,                     /**< 调用TAF的ORIG_REQ API失败 */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_PDP_ACTIVATE_LIMIT,
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_SAME_APN_OPERATING,                /**< 相同的APN正在操作 */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_PDP_CONTEXT_PARA_ERR,              /**< 参数错误 */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_PDN_CONNECT_NW_REJ,                /**< 建链被网侧拒绝 */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_NO_REG_ADDR_PAIR,                  /**< 没有发起注册的地址对 */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_TRANSPORT,                         /**< 发送或接收SIP报文时，底层传输发生错误*/
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_REMOTE,                            /**< 注册被网侧拒绝 */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_SIP_SIGAL_PDP_ORIG_TIMER_EXP,      /**< 拨号定时器超时 */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_WAIT_IPV6_INFO_TIMER_EXP,          /**< 等IPV6前缀定时器超时 */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_REG_PROTECT_TIMER_EXP,             /**< 等待注册保护定时器超时 */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_SERVICE_STATUS_ERROR,              /**< 服务状态不正确 */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_MOVE_TO_NOT_SUP_IMS_RAT,           /**< 注册过程中移动到了不支持IMS的接入技术下 */

    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_BUTT
};
typedef VOS_UINT16  IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ENUM_UINT16;

/*****************************************************************************
 枚举名    :  IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :  紧急呼叫失败的原因值
*****************************************************************************/
enum IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_ENUM
{
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_IMS        = 1,    /**< 当前接入技术不支持IMS特性 */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_EMC_IMS    = 2,    /**< UE不支持紧急的VOLTE */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NOT_ALLOW_NEW_CALL,                   /**< 不允许发起新的呼叫 */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_VOICE_CALL,        /**< UE不支持VOICE CALL */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_CANNOT_MAKE_NOCAR_EMC_CALL,           /**< 不能打无卡紧急呼叫 */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NW_NOT_SUPPORT_EMC_BEAR,              /**< 网侧不支持建立紧急承载 */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_REMOTE,                               /**< 被服务器拒绝，具体拒绝原因值详见对应数据结构中的Status Code，根据不同的原因值可能会携带一些其它的头域 */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_TIMEOUT,                              /**< 发送或接收SIP报文超时，具体超时的定时器详见对应数据结构中的 Timer Id */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_EMC_REG_FAIL,                         /**< 紧急注册失败 */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_CUR_RAT_NOT_SUPPORT_IMS,              /**< 当前接入技术不支持IMS */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_CUR_RAT_NOT_SUPPORT_EMC_IMS,          /**< 当前接入技术不支持紧急IMS */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_TCALL_TIMEOUT,                        /**< TCALL超时 */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_TQOS_TIMEOUT ,                        /**< TQOS超时 */

    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_HIFI_EXCEPTION,
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NON_SRVCC_RAT_CHANGE,
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_MEDIA_PDP_RELEASE,
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_SIP_PDP_ERR,
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_REG_ERR,
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NOT_SUPPORTED_CALL_TYPE,

    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_BUTT
};
typedef VOS_UINT16  IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_ENUM_UINT16;



/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*****************************************************************************
 结构名称   :IMSA_ERR_LOG_CALL_FAIL_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : volte呼叫失败信息结构
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;               /*消息头*/
    IMSA_ERR_LOG_REG_STATUS_ENUM_UINT8              enNormRegStatus;        /* IMS普通注册注册状态 */
    IMSA_ERR_LOG_REG_STATUS_ENUM_UINT8              enEmcRegStatus;         /* IMS紧急注册状态 */
    IMSA_ERR_LOG_VOPS_STATUS_ENUM_UINT8             enVopsStatus;           /* 网侧是否具备IMS over PS能力 */
    IMSA_ERR_LOG_CALL_STATUS_ENUM_UINT8             enCallStatus;           /* 呼叫状态 */
    IMSA_ERR_LOG_CALL_FAIL_REASON_ENUM_UINT16       enCallFailReason;       /* 呼叫失败原因值 */
    VOS_UINT8                                       ucIsVoiceMediaExist;    /* 网侧是否建立专有承载 */
    VOS_UINT8                                       ucIsVideoMediaExist;    /* 网侧是否建立专有承载 */
    IMSA_ERR_LOG_MPTY_STATE_ENUM_UINT8              enMpty;                 /* 是否MPTY */
    IMSA_ERR_LOG_PDN_CONN_STATUS_ENUM_UINT8         enPdnConnStatus;        /* PDN连接状态 */
    VOS_CHAR                                        aucPcscfAddr[IMSA_ERR_LOG_IPV6_STRING_LEN+1];
    VOS_UINT8                                       aucRsv[3];
} IMSA_ERR_LOG_CALL_FAIL_STRU;

/*****************************************************************************
 结构名称   :IMSA_ERR_LOG_NORM_CALL_FAIL_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : volte呼叫失败信息结构
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;               /*消息头*/
    IMSA_ERR_LOG_REG_STATUS_ENUM_UINT8              enNormRegStatus;        /* IMS普通注册注册状态 */
    IMSA_ERR_LOG_VOPS_STATUS_ENUM_UINT8             enVopsStatus;           /* 网侧是否具备IMS over PS能力 */
    IMSA_ERR_LOG_CALL_TYPE_ENUM_UINT8               enCallType;             /* 呼叫类型，区分是语音还是视频 */
    IMSA_ERR_LOG_CALL_STATUS_ENUM_UINT8             enCallStatus;           /* 呼叫状态 */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_ENUM_UINT16  enCallFailReason;       /* 呼叫失败原因值 */
    VOS_UINT16                                      usSipStatusCode;        /* IMS带的错误原因值，仅在enCallFailReason为remote时有效 */
    VOS_UINT8                                       ucIsVoiceMediaExist;    /* 网侧是否建立专有承载 */
    VOS_UINT8                                       ucIsVideoMediaExist;    /* 网侧是否建立专有承载 */
    IMSA_ERR_LOG_MPTY_STATE_ENUM_UINT8              enMpty;                 /* 是否MPTY */
    IMSA_ERR_LOG_PDN_CONN_STATUS_ENUM_UINT8         enPdnConnStatus;        /* PDN连接状态 */
    VOS_CHAR                                        aucPcscfAddr[IMSA_ERR_LOG_IPV6_STRING_LEN+1];
    VOS_UINT8                                       ucRsv;
} IMSA_ERR_LOG_NORM_CALL_FAIL_STRU;

/*****************************************************************************
 结构名称   :IMSA_ERR_LOG_EMC_CALL_FAIL_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : volte呼叫失败信息结构
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;               /*消息头*/
    IMSA_ERR_LOG_SRV_STATUS_ENUM_UINT8              enNormSrvStatus;        /* IMS普通注册注册状态 */
    IMSA_ERR_LOG_SRV_STATUS_ENUM_UINT8              enEmcSrvStatus;         /* IMS紧急注册状态 */
    IMSA_ERR_LOG_VOPS_STATUS_ENUM_UINT8             enVopsStatus;           /* 网侧是否具备IMS over PS能力 */
    IMSA_ERR_LOG_CALL_STATUS_ENUM_UINT8             enCallStatus;           /* 呼叫状态 */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_ENUM_UINT16   enCallFailReason;       /* 呼叫失败原因值 */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ENUM_UINT16    enRegFailReason;        /* 注册失败原因值 */
    IMSA_ERR_LOG_REGISTER_ADDR_TYPE_ENUM_UINT8      enRegisterAddrType;     /* 注册使用的地址对类型 */
    VOS_UINT8                                       ucRsv;
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16  enPdnConnNwRej;         /* 建链被网侧拒绝 */
    VOS_UINT16                                      usCallSipStatusCode;    /* IMS带的错误原因值，仅在enCallFailReason为remote时有效 */
    VOS_UINT16                                      usEmcRegSipStatusCode;  /* IMS带的错误原因值，仅在enCallFailReason为remote时有效 */

} IMSA_ERR_LOG_EMC_CALL_FAIL_STRU;

/*****************************************************************************
 结构名称   :IMSA_ERR_LOG_NOT_INIT_REG_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : IMS不能发起注册的原因值
*****************************************************************************/
typedef struct
{
    IMSA_ERR_LOG_VOPS_STATUS_ENUM_UINT8             enVopsStatus;           /* 网侧是否具备IMS over PS能力 */
    IMSA_ERR_LOG_PS_SERVICE_STATUS_ENUM_UINT8       enPsServiceStatus;      /* 当前网络PS服务状态 */
    IMSA_ERR_LOG_VOICE_DOMAIN_ENUM_UINT8            enVoiceDomain;          /* UE配置的语音能力 */
    VOS_UINT8                                       ucImsSupportFlag;       /* 当前接入技术下是否支持IMS */
    VOS_UINT8                                       ucIsRoamingFlag;        /* 当前是否是漫游网络 */
    VOS_UINT8                                       ucIsSupportRoamNotRegFlag; /* 漫游网络下不允许IMS注册开关是否打开 */
    IMSA_USIM_STATUS_ENUM_UINT8                     enUsimStatus;           /* 卡是否有效 */
    VOS_UINT8                                       ucHomeNetDomainNameValid;   /* 域名是否有效 */
    VOS_UINT8                                       ucImpiValid;                /* IMPI是否有效 */
    VOS_UINT8                                       ucImpuValid;                /* IMPU是否有效 */
    IMSA_ERR_LOG_CAMPED_RAT_TYPE_ENUM_UINT8         enImsaCampedRatType;        /**< 当前驻留网络,NULL,2G,3G,LTE */
    VOS_UINT8                                       ucIsImsRegForbidden;    /* IMS注册是否被禁止 */
} IMSA_ERR_LOG_REG_CONDITION_STATUS_STRU;


/*****************************************************************************
 结构名称   :IMSA_ERR_LOG_NOT_INIT_REG_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : IMS不能发起注册的原因值
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;               /* 消息头*/
    IMSA_ERR_LOG_REG_CONDITION_STATUS_STRU          stRegConditionStatus;   /* 发起注册需要满足的条件的状态 */
} IMSA_ERR_LOG_NOT_INIT_REG_STRU;

/*****************************************************************************
 结构名称   :IMSA_ERR_LOG_PDN_CONN_FAIL_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 发起PDN建链请求失败的结构体
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;            /*消息头*/
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ENUM_UINT32      enPdnConnRejCause;  /* IMS PDN连接被拒原因值 */
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16  enNwRejCause;       /* PDN被网侧拒绝的原因值，只有在enPdnConnRejCause为CN REJ时有效 */
    VOS_UINT8                                       aucRsv[2];
} IMSA_ERR_LOG_PDN_CONN_FAIL_STRU;

/*****************************************************************************
 结构名称   :IMSA_ERR_LOG_REG_FAIL_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : IMS注册失败结构
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;           /*消息头*/
    IMSA_ERR_LOG_VOPS_STATUS_ENUM_UINT8             enVopsStatus;       /* 网侧是否具备IMS over PS能力 */
    IMSA_ERR_LOG_PS_SERVICE_STATUS_ENUM_UINT8       enPsServiceStatus;  /* 当前网络PS服务状态 */
    IMSA_ERR_LOG_PDN_CONN_STATUS_ENUM_UINT8         enPdnConnStatus;    /* PDN连接状态 */
    IMSA_ERR_LOG_REGISTER_REASON_ENUM_UINT8         enRegisterReason;   /* 注册发起的原因 */
    IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8         enRegFailReason;    /* 注册失败的原因 */
    VOS_CHAR                                        aucPcscfAddr[IMSA_ERR_LOG_IPV6_STRING_LEN+1];
    IMSA_USIM_STATUS_ENUM_UINT8                     enUsimStatus;       /* 卡是否有效 */
    VOS_UINT8                                       ausRsv[3];
    IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32           enPdnConnRejCause;  /* IMS PDN连接被拒原因值 */
} IMSA_ERR_LOG_REG_FAIL_STRU;

/*****************************************************************************
 结构名称   :IMSA_ERR_LOG_REG_FAIL_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : IMS注册失败结构
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;           /*消息头*/
    IMSA_ERR_LOG_REGISTER_ADDR_TYPE_ENUM_UINT8      enRegisterAddrType; /* 注册使用的地址对类型 */
    IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8         enRegFailReason;    /* 注册失败的原因 */
    VOS_UINT16                                      usSipStatusCode;    /* IMS上报的注册异常原因值 */
    VOS_CHAR                                        aucPcscfAddr[IMSA_ERR_LOG_IPV6_STRING_LEN+1];
    IMSA_ERR_LOG_CAMPED_RAT_TYPE_ENUM_UINT8         enImsaCampedRatType;/**< 当前驻留网络,NULL,2G,3G,LTE */
    VOS_UINT32                                      ulRetryTimerLen;    /* 注册失败重试间隔时长 */
    VOS_UINT8                                       ucIsApnChangeFlag;  /* APN是否发生改变 */
    VOS_UINT8                                       aucRsv[3];
} IMSA_ERR_LOG_NORM_REG_FAIL_STRU;

/*****************************************************************************
 结构名称   :IMSA_ERR_LOG_INIT_DEREG_CAUSE_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 仅上报普通的去注册的原因值，紧急的没有意义
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                              stHeader;           /*消息头*/
    IMSA_ERR_LOG_INIT_DEREG_REASON_ENUM_UINT32          enInitDeregCause;   /*  */
    IMSA_ERR_LOG_CAMPED_RAT_TYPE_ENUM_UINT8             enImsaCampedRatType;/**< 当前驻留网络,NULL,2G,3G,LTE */
    VOS_UINT8                                           aucRsv[3];
} IMSA_ERR_LOG_INIT_DEREG_CAUSE_STRU;


/*****************************************************************************
 结构名称   :IMSA_ERR_LOG_INIT_DEREG_CAUSE_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 切换失败，上报当前呼叫类型和错误原因值
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                              stHeader;           /*消息头*/
    IMSA_ERR_LOG_CALL_TYPE_ENUM_UINT8                   enCurCallType;      /* 当前呼叫类型 */
    IMSA_ERR_LOG_CALL_REASON_RESOURCE_RESULT_ENUM_UINT8 enResStatus;        /* 资源预留承载状态，接口遗留 */
    VOS_UINT16                                          usSipStatusCode;    /* 错误原因值 */
} IMSA_ERR_LOG_MODIFY_CALL_TYPE_FAIL_STRU;


/*****************************************************************************
 结构名称   :IMSA_ERR_LOG_ERRLOG_IMS_REGISTER_FAILURE_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : IMS注册失败结构
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                      stHeader;           /*消息头*/
    VOS_UINT32                                  ulCount;                            /* 缓存区溢出计数 */
} IMSA_ERR_LOG_MNTN_EVENT_STRU;

/*****************************************************************************
 结构名称   : IMSA_ERR_LOG_REPORT_REQ_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : OM发送给IMSA的ERROR REQ消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usModemID;
    VOS_UINT8                           aucRsv[2];
}IMSA_ERR_LOG_REPORT_REQ_STRU;

/*****************************************************************************
 结构名称   : IMSA_ERR_LOG_ERR_LOG_REPORT_CNF_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : IMSA回复ERRLOG应答数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* 故障内容长度,如果ulRptlen为0,aucContent内容长度也为0 */
    VOS_UINT8                           aucContent[4]; /* 故障内容 */
} IMSA_ERR_LOG_REPORT_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    IMSA_ERR_LOG_REG_FAIL_STRU          stImsaRegErrlog;
}IMSA_REG_ERROR_LOG_INFO_STRU;
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    IMSA_ERR_LOG_CALL_FAIL_STRU         stImsaCallErrlog;
}IMSA_CALL_ERROR_LOG_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    IMSA_ERR_LOG_NOT_INIT_REG_STRU      stImsaNotInitReg;
}IMSA_NOT_INIT_REG_ERROR_LOG_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    IMSA_ERR_LOG_PDN_CONN_FAIL_STRU     stImsaPdnConnFail;
}IMSA_NORM_PDN_CONN_FAIL_ERROR_LOG_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    IMSA_ERR_LOG_NORM_REG_FAIL_STRU     stImsaNormRegFail;
}IMSA_NORM_REG_FAIL_ERROR_LOG_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    IMSA_ERR_LOG_INIT_DEREG_CAUSE_STRU  stImsaInitDereg;
}IMSA_NORM_INIT_DEREG_ERROR_LOG_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    IMSA_ERR_LOG_NORM_CALL_FAIL_STRU    stImsaCallErrlog;
}IMSA_NORM_CALL_ERROR_LOG_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    IMSA_ERR_LOG_EMC_CALL_FAIL_STRU     stImsaEmcCallErrlog;
}IMSA_EMC_CALL_ERROR_LOG_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;
    IMSA_ERR_LOG_MODIFY_CALL_TYPE_FAIL_STRU stImsaModCallTypeFail;
}IMSA_MODIFY_CALL_TYPE_ERROR_LOG_INFO_STRU;


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/










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

#endif /* end of LnasErrlogInterface.h */


