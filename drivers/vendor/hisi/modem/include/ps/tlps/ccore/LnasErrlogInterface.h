/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LnasErrLogInterface.h
  Description     : LnasErrLogInterface.h header file
  History         :
     1.HANLUFENG 41410       2013-8-27     Draft Enact
     2.
******************************************************************************/

#ifndef __LNASERRLOGINTERFACE_H__
#define __LNASERRLOGINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "omerrorlog.h"
#include    "LnasFtmInterface.h"

#pragma  pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/
#define LNAS_OM_ERRLOG_ID_ESM_REJ_CN_CAUSE               (400)
#define LNAS_OM_ERRLOG_ID_EMM_FAIL_CAUSE                 (600)
#define LNAS_OM_ERRLOG_ID_EMM_REJ_CN_CAUSE               (800)
#define LNAS_ERR_LOG_CTRL_LEVEL_NULL                     (0)                     /* ErrLog等级未定义*/
#define LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL                 (1)                     /* ErrLog等级为紧急 */
#define LNAS_ERR_LOG_CTRL_LEVEL_MAJOR                    (2)                     /* ErrLog等级为重要 */
#define LNAS_ERR_LOG_CTRL_LEVEL_MINOR                    (3)                     /* ErrLog等级为次要 */
#define LNAS_ERR_LOG_CTRL_LEVEL_WARNING                  (4)                     /* ErrLog等级为提示 */
#define NAS_EMM_RING_BUFFER_SIZE                        (1024 * 2)               /* LNAS的环形共享缓存大小 */


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : EMM_OM_ERRLOG_ALM_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 告警故障类型
*****************************************************************************/
enum EMM_OM_ERRLOG_TYPE_ENUM
{
    EMM_OM_ERRLOG_TYPE_CN_REJ          = 1, /*CN REJ错误*/
    EMM_OM_ERRLOG_TYPE_TIMEOUT         = 2, /*定时器超时*/
    EMM_OM_ERRLOG_TYPE_LRRC_REL        = 3, /*收到LRRC释放*/
    EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL    = 4, /*建链失败*/
    EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL   = 5, /*data req失败*/
    EMM_OM_ERRLOG_TYPE_EPS_ONLY        = 6, /*联合注册，EPS ONLY成功*/

    EMM_OM_ERRLOG_TYPE_CN_BUTT
};
typedef VOS_UINT16 EMM_OM_ERRLOG_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : EMM_OM_ERRLOG_EST_RESULT_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  : 信令连接结果枚举类型
*****************************************************************************/
enum EMM_OM_ERRLOG_EST_RESULT_ENUM
{
    EMM_OM_ERRLOG_EST_DELING                          = 1,                                /* 该信令连接正在释放                   */
    EMM_OM_ERRLOG_EST_ACCESS_BARRED_MO_CALL           = 2,                                /* access barred when MO Call  */
    EMM_OM_ERRLOG_EST_ACCESS_BARRED_MO_SIGNAL         = 3,                                /* access barred When MO SIGNAL  */
    EMM_OM_ERRLOG_EST_ACCESS_BARRED_ALL               = 4,                                /* access barred When Rrc Con Rej */
    EMM_OM_ERRLOG_EST_EST_CONN_FAIL                   = 5,                                /* RR connection establish failure      */
    EMM_OM_ERRLOG_EST_CELL_SEARCHING                  = 6,                               /* RRC目前不能处理建链请求，NAS收到该原因值，                                                                                   直到收到RRC_MM_SYS_INFO_IND再发起建链*/
    EMM_OM_ERRLOG_EST_ACCESS_BARRED_MT_CALL           = 7,                               /* access barred when MT Call  */
    EMM_OM_ERRLOG_EST_ACCESS_BARRED_MO_CSFB           = 8,                               /* access barred when MO CSFB  */
    EMM_OM_ERRLOG_EST_ACCESS_BARRED_MO_CALL_AND_CSFB  = 9,                               /* access barred when MO Call AND MO CSFB  */
    EMM_OM_ERRLOG_EST_NO_RF                           = 10,                              /* DSDS NORF */

    EMM_OM_ERRLOG_EST_RESULT_BUTT
};
typedef VOS_UINT32 EMM_OM_ERRLOG_EST_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : EMM_OM_ERRLOG_SEND_RSLT_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  : MM直传消息确认结果
*****************************************************************************/
enum EMM_OM_ERRLOG_SEND_RSLT_ENUM
{
    EMM_OM_ERRLOG_SEND_RSLT_FAILURE_HO                  = 1,
    EMM_OM_ERRLOG_SEND_RSLT_FAILURE_CONN_REL            = 2,
    EMM_OM_ERRLOG_SEND_RSLT_FAILURE_CTRL_NOT_CONN       = 3,
    EMM_OM_ERRLOG_SEND_RSLT_FAILURE_TXN                 = 4,
    EMM_OM_ERRLOG_SEND_RSLT_FAILURE_RLF                 = 5,
    EMM_OM_ERRLOG_SEND_RSLT_NO_RF                       = 6,
    EMM_OM_ERRLOG_SEND_RSLT_BUTT
};
typedef VOS_UINT32 EMM_OM_ERRLOG_SEND_RSLT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : EMM_ERR_LOG_LOCAL_DETACH_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 本地DETACH类型
*****************************************************************************/
enum EMM_ERR_LOG_LOCAL_DETACH_TYPE_ENUM
{
    EMM_ERR_LOG_LOCAL_DETACH_TYPE_GU2L_NO_EPS_BEAR        = 1, /*GU2L没有EPS承载*/
    EMM_ERR_LOG_LOCAL_DETACH_TYPE_RADIO_CAP_CHANGE        = 2, /*无线能力发生变更*/
    EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER                   = 3, /*除开以上的其他原因*/
    EMM_ERR_LOG_LOCAL_DETACH_TYPE_BUTT
};
typedef VOS_UINT16 EMM_ERR_LOG_LOCAL_DETACH_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : ESM_OM_ERRLOG_TIMEOUT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : esm流程定时器超时
*****************************************************************************/
enum ESM_OM_ERRLOG_TIMEOUT_ENUM
{
    ESM_OM_ERRLOG_TIMEOUT_T3480  = 1,   /*3480超时*/
    ESM_OM_ERRLOG_TIMEOUT_T3481  = 2,   /*3481超时*/
    ESM_OM_ERRLOG_TIMEOUT_T3482  = 3,   /*3482超时*/
    ESM_OM_ERRLOG_TIMEOUT_T3492  = 4,   /*3492超时*/
    ESM_OM_ERRLOG_TIMEOUT_BUTT
};
typedef VOS_UINT16  ESM_OM_ERRLOG_TIMEOUT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : EMM_OM_ERRLOG_AUTH_FAIL_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : emm 鉴权fail枚举
*****************************************************************************/
enum EMM_OM_ERRLOG_AUTH_FAIL_ENUM
{
    EMM_OM_ERRLOG_AUTH_FAIL_CN_REJ  = 1,    /*鉴权CN REJ*/
    EMM_OM_ERRLOG_AUTH_FAIL_BUTT
};
typedef VOS_UINT16  EMM_OM_ERRLOG_AUTH_FAIL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : EMM_OM_ERRLOG_ALM_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 告警故障类型
*****************************************************************************/
enum EMM_OM_ERRLOG_ALM_TYPE_ENUM
{
    EMM_OM_ERRLOG_ALM_TYPE_COMMUNICATION    = 0x01,                               /* 通信 */
    EMM_OM_ERRLOG_ALM_TYPE_TRAFFIC_QUALITY  = 0x02,                               /* 业务质量 */
    EMM_OM_ERRLOG_ALM_TYPE_DEAL_WRONG       = 0x03,                               /* 处理出错 */
    EMM_OM_ERRLOG_ALM_TYPE_DEVICE_FAILURE   = 0x04,                               /* 设备故障 */
    EMM_OM_ERRLOG_ALM_TYPE_ENV_FAILURE      = 0x05,                               /* 环境故障 */
    EMM_OM_ERRLOG_ALM_TYPE_BUTT
};
typedef VOS_UINT16  EMM_OM_ERRLOG_ALM_TYPE_ENUM_U16;

/*****************************************************************************
 枚举名    : EMM_OM_ERRLOG_PAGING_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : EMM_OM_ERRLOG_PAGING_ENUM enPagingUeId取值
*****************************************************************************/
enum EMM_OM_ERRLOG_PAGING_ENUM
{
    EMM_OM_ERRLOG_PAGING_PS_IMSI            = 1, /*IMSI PAGING*/

    EMM_OM_ERRLOG_PAGING_CS                 = 2, /* CS PAGING lost*/
    EMM_OM_ERRLOG_PAGING_PS                 = 3, /* PS PAGING lost*/

    EMM_OM_ERRLOG_PAGING_UE_ID_BUTT
};
typedef VOS_UINT16 EMM_OM_ERRLOG_PAGING_ENUM_UINT16;

/*****************************************************************************
 枚举名    : EMM_OM_LMM_PAGING_FAIL_CAUSE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 表示寻呼异常原因
*****************************************************************************/
enum EMM_OM_LMM_PAGING_FAIL_CAUSE_ENUM
{
   EMM_OM_LMM_PAGING_FAIL_CAUSE_NULL                = 0,    /* 空原因值 */
   EMM_OM_LMM_PAGING_FAIL_CAUSE_ABNORMAL_STATUS     = 1,    /* 异常状态下收到寻呼 */

   EMM_OM_LMM_PAGING_FAIL_CAUSE_BUTT
};
typedef VOS_UINT8 EMM_OM_LMM_PAGING_FAIL_CAUSE_ENUM_UINT8;
/*****************************************************************************
 枚举名    : EMM_OM_ERRLOG_IMPROVEMENT_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 体验提升项目枚举
*****************************************************************************/
enum EMM_OM_ERRLOG_IMPROVEMENT_TYPE_ENUM
{
   EMM_OM_ERRLOG_IMPROVEMENT_TYPE_LTE_NO_SUBSCRIBE      = 1,    /* 4G未开户 */
   EMM_OM_ERRLOG_IMPROVEMENT_TYPE_HO_TO_FORBIDDEN_TA    = 2,    /* 切换到被禁TA */
   EMM_OM_ERRLOG_IMPROVEMENT_TYPE_ESR_RESEND_FOR_HO     = 3,    /* 切换场景SER重传 */
   EMM_OM_ERRLOG_IMPROVEMENT_TYPE_FORBIDDEN_TA          = 4,    /* 步进被禁TA优化 */
   EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MO_CALL            = 5,    /* CS主叫优化 */
   EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MT_CALL            = 6,    /* CS被叫优化 */

   EMM_OM_ERRLOG_IMPROVEMENT_TYPE_BUTT
};
typedef VOS_UINT8 EMM_OM_ERRLOG_IMPROVEMENT_TYPE_ENUM_UINT16;



/*****************************************************************************
 枚举名    :  EMM_OM_ERRLOG_RAT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 具体的某一异系统场景，目前只用到W2L回退等系统消息超时
*****************************************************************************/
enum EMM_OM_ERRLOG_RAT_ENUM
{
    EMM_OM_ERRLOG_REVERSE_WAIT_SYSINFO_TIMEOUT_PROCEDURE    = 1,     /*异系统回退等待定时器超时*/

    EMM_OM_ERRLOG_INFO_TYPE_BUTT
};
typedef VOS_UINT16  EMM_OM_ERRLOG_RAT_ENUM_UINT16;

/*****************************************************************************
 结构名称   :ESM_OM_ERRLOG_ID_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   :ESM相关原因值
*****************************************************************************/
enum ESM_OM_ERRLOG_ID_ENUM
{
    /*ESM模块失败拒绝*/
    ESM_OM_ERRLOG_CAUSE_OPERATOR_DETERMINE_BARRING = LNAS_OM_ERRLOG_ID_ESM_REJ_CN_CAUSE, /* 网侧拒绝，提示操作被阻止 */
    ESM_OM_ERRLOG_CAUSE_INSUFFICIENT_RESOURCES,             /* 网侧拒绝,提示资源不足        */
    ESM_OM_ERRLOG_CAUSE_UNKNOWN_OR_MISSING_APN,             /* 网侧拒绝,提示APN无法识别     */
    ESM_OM_ERRLOG_CAUSE_UNKNOWN_PDN_TYPE,                   /* 网侧拒绝，提示PDN类型无法识别*/
    ESM_OM_ERRLOG_CAUSE_USER_AUTH_FAIL,                     /* 网侧拒绝，提示用户鉴权失败   */
    ESM_OM_ERRLOG_CAUSE_REQ_REJ_BY_SGW_OR_PGW,              /* 网侧拒绝，提示SGW或者PGW拒绝用户请求 */
    ESM_OM_ERRLOG_CAUSE_REQ_REJ_UNSPECITY,                  /* 网侧拒绝，原因不明 */
    ESM_OM_ERRLOG_CAUSE_SERVICE_OPTION_NOT_SUPPORT,         /* 网侧拒绝，提示请求选项不支持 */
    ESM_OM_ERRLOG_CAUSE_REQ_SERVICE_NOT_SUBSCRIBED,         /* 网侧拒绝，提示请求选项没有签约 */
    ESM_OM_ERRLOG_CAUSE_SERVICE_OPTION_TEMP_OUT_ORDER,      /* 网侧拒绝，提示服务选项临时性不支持*/
    ESM_OM_ERRLOG_CAUSE_PTI_ALREADY_IN_USED,                /* 网侧拒绝，提示PTI已使用*/
    ESM_OM_ERRLOG_CAUSE_REGULAR_DEACTIVATION,               /* 网侧拒绝，提示承载去激活*/
    ESM_OM_ERRLOG_CAUSE_EPS_QOS_NOT_ACCEPT,                 /* 网侧拒绝，提示Qos未被接受*/
    ESM_OM_ERRLOG_CAUSE_NETWORK_FAILURE,                    /* 网侧拒绝，提示网络错误*/
    ESM_OM_ERRLOG_CAUSE_REACTIVATION_REQUESTED,             /* 网侧拒绝，提示需要重新激活*/
    ESM_OM_ERRLOG_CAUSE_SEMANTIC_ERR_IN_TFT,                /* 网侧拒绝，提示TFT语义错误*/
    ESM_OM_ERRLOG_CAUSE_SYNTACTIC_ERR_IN_TFT,               /* 网侧拒绝，提示TFT语法错误*/
    ESM_OM_ERRLOG_CAUSE_INVALID_EPS_BEARER_IDENTITY,        /* 网侧拒绝，提示非法的承载标识*/
    ESM_OM_ERRLOG_CAUSE_SEMANTIC_ERR_IN_PACKET_FILTER,      /* 网侧拒绝，提示PacketFilter语义错误*/
    ESM_OM_ERRLOG_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER,    /* 网侧拒绝，提示PacketFilter语法错误*/
    ESM_OM_ERRLOG_CAUSE_BEARER_WITHOUT_TFT_ACT,             /* 网侧拒绝，提示激活的上下文没有TFT的承载*/
    ESM_OM_ERRLOG_CAUSE_PTI_MISMATCH,                       /* 网侧拒绝，提示PTI不匹配*/
    ESM_OM_ERRLOG_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED,       /* 网侧拒绝，提示最后的PDN不允许释放*/
    ESM_OM_ERRLOG_CAUSE_PDNTYPE_IPV4_ONLY_ALLOWED,          /* 网侧拒绝，提示PDN类型只允许IpV4*/
    ESM_OM_ERRLOG_CAUSE_PDNTYPE_IPV6_ONLY_ALLOWED,          /* 网侧拒绝，提示PDN类型只允许IpV6*/
    ESM_OM_ERRLOG_CAUSE_SINGLE_ADDR_BEARER_ONLY_ALLOWED,    /* 网侧拒绝，提示PDN只允许单个IP地址*/
    ESM_OM_ERRLOG_CAUSE_ESM_INFORMATION_NOT_RECEIVED,       /* 网侧拒绝，提示ESM Info消息没有收到*/
    ESM_OM_ERRLOG_CAUSE_PDN_CONNECTION_DOES_NOT_EXIST,      /* 网侧拒绝，提示PDN链接不存在*/
    ESM_OM_ERRLOG_CAUSE_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED, /* 网侧拒绝，提示多PDN不允许对应同一个APN*/
    ESM_OM_ERRLOG_CAUSE_COLLISION_WITH_NETWORK_INITIATED_REQUEST,  /* 网侧拒绝，提示与网络触发的请求冲突*/
    ESM_OM_ERRLOG_CAUSE_UNSUPPORTED_QCI_VALUE,              /* 网侧拒绝，提示QCI的值无法支持*/
    ESM_OM_ERRLOG_CAUSE_INVALID_PTI_VALUE,                  /* 网侧拒绝，提示PTI的值不可用*/
    ESM_OM_ERRLOG_CAUSE_SEMANTICALLY_INCORRECT_MESSAGE,     /* 网侧拒绝，提示消息语义不正确*/
    ESM_OM_ERRLOG_CAUSE_INVALID_MANDATORY_INFORMATION,      /* 网侧拒绝，提示必选信元不正确*/
    ESM_OM_ERRLOG_CAUSE_MESSAGE_TYPE_NON_EXIST_OR_NOT_IMPLEMENTED, /* 网侧拒绝，提示消息类型不存在或不可用*/
    ESM_OM_ERRLOG_CAUSE_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_PROT_STA, /* 网侧拒绝，提示消息类型与协议不一致*/
    ESM_OM_ERRLOG_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENTED, /* 网侧拒绝，提示信元不存在或不可用*/
    ESM_OM_ERRLOG_CAUSE_CONDITIONAL_IE_ERROR,               /* 网侧拒绝，提示条件信元错误*/
    ESM_OM_ERRLOG_CAUSE_MESSAGE_NOT_COMPATIBLE_WITH_PROT_STA, /* 网侧拒绝，提示消息与协议规定不一致*/
    ESM_OM_ERRLOG_CAUSE_PROTOCOL_ERROR,                     /* 网侧拒绝，提示不指定的协议错误*/
    ESM_OM_ERRLOG_CAUSE_APN_RESTRICTION_VAL_INCOMPATIBLE_WITH_ACT_BEARER, /* 网侧拒绝，提示apn约束条件与激活承载上下文不符*/
    ESM_OM_ERRLOG_CAUSE_OTHERS
};
typedef VOS_UINT16  ESM_OM_ERRLOG_ID_ENUM_UINT16;

/*****************************************************************************
 结构名称   :EMM_OM_ERRLOG_ID_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   :EMM相关原因值
*****************************************************************************/
enum EMM_OM_ERRLOG_ID_ENUM
{
    EMM_OM_ERRLOG_CN_CAUSE_NULL                = 0,                         /* 空原因值*/
    EMM_OM_ERRLOG_CN_CAUSE_IMSI_UNKNOWN_IN_HSS = LNAS_OM_ERRLOG_ID_EMM_REJ_CN_CAUSE,  /*网侧拒绝， 提示IMSI在HSS中找不到*/
    EMM_OM_ERRLOG_CN_CAUSE_ILLEGAL_UE,                                      /* 网侧拒绝,提示非法UE*/
    EMM_OM_ERRLOG_CN_CAUSE_IMEI_NOT_ACCEPTED,                               /* 网络拒绝,提示IMEI不被接受*/
    EMM_OM_ERRLOG_CN_CAUSE_ILLEGAL_ME,                                      /* 网侧拒绝,提示非法ME*/
    EMM_OM_ERRLOG_CN_CAUSE_EPS_SERV_NOT_ALLOW,                              /* 网侧拒绝,提示EPS业务不允许*/
    EMM_OM_ERRLOG_CN_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,             /* 网侧拒绝,提示EPS和非EPS业务不允许*/
    EMM_OM_ERRLOG_CN_CAUSE_UE_ID_NOT_DERIVED,                               /* 网络拒绝,提示UE ID不被识别*/
    EMM_OM_ERRLOG_CN_CAUSE_IMPLICIT_DETACHED,                               /* 网络拒绝,提示隐式DETTACH*/
    EMM_OM_ERRLOG_CN_CAUSE_PLMN_NOT_ALLOW,                                  /* 网侧拒绝,提示PLMN不可用*/
    EMM_OM_ERRLOG_CN_CAUSE_TA_NOT_ALLOW,                                    /* 网侧拒绝,提示当前TA不可用*/
    EMM_OM_ERRLOG_CN_CAUSE_ROAM_NOT_ALLOW,                                  /* 网侧拒绝,提示当前TA中不能漫游*/
    EMM_OM_ERRLOG_CN_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,                      /* 网络拒绝,提示当前PLMN中EPS业务不允许*/
    EMM_OM_ERRLOG_CN_CAUSE_NO_SUITABL_CELL,                                 /* 网络拒绝,提示当前TA中没有可用的小区*/
    EMM_OM_ERRLOG_CN_CAUSE_MSC_UNREACHABLE,                                 /* 网络拒绝,提示当前MSC不可达*/
    EMM_OM_ERRLOG_CN_CAUSE_NETWORK_FAILURE,                                 /* 网络拒绝,提示当前网络错误*/
    EMM_OM_ERRLOG_CN_CAUSE_CS_NOT_AVAIL,                                    /* 网络拒绝,提示CS不可用*/
    EMM_OM_ERRLOG_CN_CAUSE_ESM_FAILURE,                                     /* 网络拒绝,提示ESM错误*/
    EMM_OM_ERRLOG_CN_CAUSE_MAC_FAILURE,                                     /* 网络拒绝,提示MAC错误*/
    EMM_OM_ERRLOG_CN_CAUSE_SYNCH_FAILURE,                                   /* 网络拒绝,提示SYNCH错误*/
    EMM_OM_ERRLOG_CN_CAUSE_PROCEDURE_CONGESTION,                            /* 网络拒绝,提示流程拥塞*/
    EMM_OM_ERRLOG_CN_CAUSE_UE_SECU_CAP_MISMATCH,                            /* 网络拒绝,提示安全能力不匹配*/
    EMM_OM_ERRLOG_CN_CAUSE_SECU_MODE_REJECTED_UNSPECIFIED,                  /* 网络拒绝,提示安全模式拒绝未指定*/
    EMM_OM_ERRLOG_CN_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG,                     /* 网络拒绝,提示当前用户没有CSG授权*/
    EMM_OM_ERRLOG_CN_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN,     /* 网络拒绝,提示请求服务未授权在这个PLMN*/
    EMM_OM_ERRLOG_CN_CAUSE_CS_FALLBACK_CALL_EST_NOT_ALLOWED,                /* 网络拒绝,提示CSFB建链不允许*/
    EMM_OM_ERRLOG_CN_CAUSE_CS_DOMAIN_TMP_NOT_ALLOWED,                       /* 网络拒绝,提示CS DOMAIN 暂时不允许使用*/
    EMM_OM_ERRLOG_CN_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED,                 /* 网络拒绝,提示没有承载上下文激活*/
    EMM_OM_ERRLOG_CN_CAUSE_SERVER_NETWORK_FAILURE,                          /* 网络拒绝,提示服务网络错误*/
    EMM_OM_ERRLOG_CN_CAUSE_SEMANTICALLY_INCORRECT_MSG,                      /* 网络拒绝,提示消息语法不正确*/
    EMM_OM_ERRLOG_CN_CAUSE_INVALID_MANDATORY_INFORMATION,                   /* 网络拒绝,提示必选信元非法*/
    EMM_OM_ERRLOG_CN_CAUSE_MSG_TYPE_NON_EXIST_OR_IMPLEMENT,                 /* 网络拒绝,提示不存在或不支持的消息*/
    EMM_OM_ERRLOG_CN_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENT,         /* 网络拒绝,提示消息信元不存在或不支持*/
    EMM_OM_ERRLOG_CN_CAUSE_MSG_TYPE_NOT_COMPATIBLE,                         /* 网络拒绝,提示消息类型不兼容*/
    EMM_OM_ERRLOG_CN_CAUSE_CONDITIONAL_IE_ERROR,                            /* 网络拒绝,提示CONDITIONAL_IE错误*/
    EMM_OM_ERRLOG_CN_CAUSE_MSG_NOT_COMPATIBLE,                              /* 网络拒绝,提示MSG不兼容*/
    EMM_OM_ERRLOG_CN_CAUSE_PROTOCOL_ERROR,                                  /* 网络拒绝，提示协议错误*/
    EMM_OM_ERRLOG_CN_CAUSE_OTHERS                                           /* 网络以其他原因拒绝*/
};
typedef VOS_UINT16  EMM_OM_ERRLOG_CN_REJ_ENUM_UINT16;
typedef VOS_UINT16  EMM_OM_ERRLOG_CN_CAUSE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : LNAS_OM_ERRLOG_ALM_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LNAS上报给OM模块的商用log的ALM ID类型
*****************************************************************************/
enum LNAS_OM_ERRLOG_ALM_ID_ENUM
{
    LNAS_OM_ERRLOG_ALM_ID_ATTACH_FAIL           = 1,         /* attach失败*/
    LNAS_OM_ERRLOG_ALM_ID_TAU_FAIL              = 2,         /* TAU失败 */
    LNAS_OM_ERRLOG_ALM_ID_DETACH_FAIL           = 3,         /* DETACH失败 */
    LNAS_OM_ERRLOG_ALM_ID_NOR_SERVICE_FAIL      = 4,         /* 普通SERVICE失败 */
    LNAS_OM_ERRLOG_ALM_ID_EXT_SERVICE_FAIL      = 5,         /* 扩展SERVICE失败*/
    LNAS_OM_ERRLOG_ALM_ID_PAGING_FAIL           = 6,         /* PAGING流程导致的丢网，目前只涉及IMSI PAGING的场景 */
    LNAS_OM_ERRLOG_ALM_ID_RAT_FAIL              = 7,         /* 异系统导致的丢网，目前只涉及W2L等系统消息超时导致的丢网场景*/
    LNAS_OM_ERRLOG_ALM_ID_ESM_PDN_CONN_FAIL     = 8,         /* PDN CONN REJ流程失败*/
    LNAS_OM_ERRLOG_ALM_ID_ESM_PDN_DISCONN_FAIL  = 9,         /* PDN DISCONN REJ流程失败*/
    LNAS_OM_ERRLOG_ALM_ID_ESM_RES_MOD_FAIL      = 10,        /* 资源修改流程失败*/
    LNAS_OM_ERRLOG_ALM_ID_ESM_RES_ALLOC_FAIL    = 11,        /* 资源分配流程失败*/
    LNAS_OM_ERRLOG_ALM_ID_OVERFLOW_FAIL         = 12,        /* 环形buffer溢出计数*/
    LNAS_OM_ERRLOG_ALM_ID_LOCAL_DETACH_FAIL     = 13,        /* local detach流程失败*/
    LNAS_OM_ERRLOG_ALM_ID_AUTH_REJ              = 14,        /* 鉴权被拒*/
    LNAS_OM_ERRLOG_ALM_ID_IMPROVE_PERFORMCE     = 15,        /* 体验提升统计 */

    LNAS_OM_ERRLOG_ALM_ID_BUTT
};
typedef VOS_UINT16  LNAS_OM_ERRLOG_ALM_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LMM_ERR_LOG_ATTACH_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : UE触发的ATTACH TYPE
*****************************************************************************/
enum LMM_ERR_LOG_ATTACH_TYPE_ENUM
{
    EMM_ERR_LOG_ATT_TYPE_EPS_ONLY                = 1, /* EPS注册 */
    EMM_ERR_LOG_ATT_TYPE_COMBINED_EPS_IMSI       = 2, /* 联合注册 */
    EMM_ERR_LOG_ATT_TYPE_EPS_EMERGENCY           = 6, /* 紧急注册 */
    EMM_ERR_LOG_ATT_TYPE_BUTT
};
typedef VOS_UINT16 EMM_ERR_LOG_ATTACH_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : EMM_ERR_LOG_TAU_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : UE触发的TAU类型
*****************************************************************************/
enum EMM_ERR_LOG_TAU_TYPE_ENUM
{
    EMM_ERR_LOG_TA_UPDATING                     = 1,  /*PS UPDATE*/
    EMM_ERR_LOG_COMBINED_TA_LA_UPDATING         = 2,  /*联合TA-LA UPDATE*/
    EMM_ERR_LOG_COMBINED_TA_LA_WITH_IMSI        = 3,  /*联合TA-LA UPDATE WITH IMSI*/
    EMM_ERR_LOG_PS_PERIODIC_UPDATING            = 4,  /*PS 周期性更新*/
    EMM_ERR_LOG_CS_PS_PERIODIC_UPDATING         = 5,  /*PS 联合的周期性更新*/
    EMM_ERR_LOG_TAU_TYPE_BUTT
};
typedef VOS_UINT16 EMM_ERR_LOG_TAU_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : EMM_ERR_LOG_MT_DETACH_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 网侧触发的DETACH类型
*****************************************************************************/
enum EMM_ERR_LOG_MT_DETACH_TYPE_ENUM
{
    EMM_ERR_LOG_MT_DET_REATTACH_REQUIRED            = 1, /*REATTACH 需要*/
    EMM_ERR_LOG_MT_DET_REATTACH_NOT_REQUIRED        = 2, /*REATTACH 不需要*/
    EMM_ERR_LOG_MT_DET_IMSI                         = 3, /*IMSI DETACH*/
    EMM_ERR_LOG_MT_DETACH_TYPE_BUTT
};
typedef VOS_UINT16 EMM_ERR_LOG_MT_DETACH_TYPE_ENUM_UINT16;

/*****************************************************************************
 结构名称   :EMM_OM_LMM_CSFB_FAIL_CAUSE_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   :表示csfb流程失败原因
*****************************************************************************/
enum   EMM_OM_LMM_CSFB_FAIL_CAUSE_ENUM
{
    EMM_OM_LMM_CSFB_FAIL_CAUSE_NULL                     = 0,   /* 空原因值                                  */
    EMM_OM_LMM_CSFB_FAIL_CAUSE_RRC_EST_FAIL             = 1,   /* EXT SERVICE过程中RRC建链失败              */
    EMM_OM_LMM_CSFB_FAIL_CAUSE_RRC_EST_ACCESS_BAR       = 2,   /* EXT SERVICE过程中RRC接入被BAR             */
    EMM_OM_LMM_CSFB_FAIL_CAUSE_RRC_REL_OTHER            = 3,   /* EXT SERVICE过程中RRC连接释放，原因为OTHER */
    EMM_OM_LMM_CSFB_FAIL_CAUSE_EXT3417_EXP              = 4,   /* EXT T3417定时器超时                       */
    EMM_OM_LMM_CSFB_FAIL_CAUSE_DELAY_TIMER_EXP          = 5,   /* CSFB延时定时器超时                        */
    EMM_OM_LMM_CSFB_FAIL_CAUSE_CN_REJ                   = 6,   /* EXT SERVICE 被网络侧拒绝                  */

    EMM_OM_LMM_CSFB_FAIL_CAUSE_BUTT
};
typedef  VOS_UINT8 EMM_OM_LMM_CSFB_FAIL_CAUSE_ENUM_UINT8;

/*****************************************************************************
 结构名    : EMM_OM_ERRLOG_MS_STATE_ENUM_UINT16
 结构说明  : MM层所有并行状态机的主状态的枚举定义
*****************************************************************************/
enum    EMM_OM_ERRLOG_MS_STATE_ENUM
{
    /*=================== EMM_OM_ERRLOG的主状态 ===================*/
    EMM_OM_ERRLOG_MS_NULL                         = 0x0000,
    EMM_OM_ERRLOG_MS_DEREG                                ,
    EMM_OM_ERRLOG_MS_REG_INIT                             ,           /*ATTACH过程中状态*/
    EMM_OM_ERRLOG_MS_REG                                  ,
    EMM_OM_ERRLOG_MS_TAU_INIT                             ,           /*TAU过程中状态*/
    EMM_OM_ERRLOG_MS_SER_INIT                             ,           /*SERVICE过程中状态*/
    EMM_OM_ERRLOG_MS_DEREG_INIT                           ,           /*DETACH过程中状态*/

    EMM_OM_ERRLOG_MS_RRC_CONN_EST_INIT                    ,           /*建立RRC连接的过程*/
    EMM_OM_ERRLOG_MS_RRC_CONN_REL_INIT                    ,           /*释放RRC连接的过程*/
    EMM_OM_ERRLOG_MS_AUTH_INIT                            ,           /*AUTH过程*/

    EMM_OM_ERRLOG_MS_SUSPEND                              ,           /*挂起过程*/
    EMM_OM_ERRLOG_MS_RESUME                               ,           /*解挂过程*/


    EMM_OM_ERRLOG_MS_BUTT
};
typedef VOS_UINT16 EMM_OM_ERRLOG_MS_STATE_ENUM_UINT16;

/*****************************************************************************
 结构名    : NAS_LMM_SUB_STATE_ENUM
 结构说明  : MM层所有并行状态机的子状态的枚举定义
*****************************************************************************/
enum    EMM_OM_ERRLOG_SS_STATE_ENUM
{

    /*=================== EMM_OM_ERRLOG的子状态 ===================*/

    /*========== NULL下的子状态 ===============*/
    EMM_OM_ERRLOG_SS_NULL_WAIT_APP_START_REQ      = 0x0000,           /*此状态下只处理APP_START_REQ消息*/
    EMM_OM_ERRLOG_SS_NULL_WAIT_READING_USIM               ,
    EMM_OM_ERRLOG_SS_NULL_WAIT_MMC_START_CNF              ,
    EMM_OM_ERRLOG_SS_NULL_WAIT_RRC_START_CNF              ,
    EMM_OM_ERRLOG_SS_NULL_WAIT_SWITCH_OFF                 ,
    EMM_OM_ERRLOG_SS_NULL_WAIT_MMC_STOP_CNF               ,
    EMM_OM_ERRLOG_SS_NULL_WAIT_RRC_STOP_CNF               ,


    /*========== DEREG下的子状态 ==============*/
    EMM_OM_ERRLOG_SS_DEREG_NORMAL_SERVICE                 ,   /*0x0009*/
    EMM_OM_ERRLOG_SS_DEREG_LIMITED_SERVICE                ,
    EMM_OM_ERRLOG_SS_DEREG_ATTEMPTING_TO_ATTACH           ,
    EMM_OM_ERRLOG_SS_DEREG_PLMN_SEARCH                    ,
    EMM_OM_ERRLOG_SS_DEREG_NO_IMSI                        ,
    EMM_OM_ERRLOG_SS_DEREG_ATTACH_NEEDED                  ,
    EMM_OM_ERRLOG_SS_DEREG_NO_CELL_AVAILABLE              ,

    /*========== ATTACH_INIT的子状态 ==========*/
    EMM_OM_ERRLOG_SS_ATTACH_WAIT_ESM_PDN_RSP              ,  /*0x0011*/
    EMM_OM_ERRLOG_SS_ATTACH_WAIT_CN_ATTACH_CNF            ,
    EMM_OM_ERRLOG_SS_ATTACH_WAIT_MRRC_REL_CNF             ,
    EMM_OM_ERRLOG_SS_ATTACH_WAIT_ESM_BEARER_CNF           ,
    EMM_OM_ERRLOG_SS_ATTACH_WAIT_RRC_DATA_CNF             ,


    /*========== REG下的子状态 ================*/
    EMM_OM_ERRLOG_SS_REG_NORMAL_SERVICE                   ,   /*0x0017*/
    EMM_OM_ERRLOG_SS_REG_ATTEMPTING_TO_UPDATE             ,
    EMM_OM_ERRLOG_SS_REG_LIMITED_SERVICE                  ,
    EMM_OM_ERRLOG_SS_REG_PLMN_SEARCH                      ,
    EMM_OM_ERRLOG_SS_REG_WAIT_ACCESS_GRANT_IND            ,
    EMM_OM_ERRLOG_SS_REG_NO_CELL_AVAILABLE                ,
    EMM_OM_ERRLOG_SS_REG_ATTEMPTING_TO_UPDATE_MM          ,
    EMM_OM_ERRLOG_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF   ,


    /*========== TAU_INIT的子状态  ============*/
    EMM_OM_ERRLOG_SS_TAU_WAIT_CN_TAU_CNF                  ,   /*0x0021*/

    /*========== SER_INIT的子状态 =============*/
    EMM_OM_ERRLOG_SS_SER_WAIT_CN_SER_CNF                  ,   /*0x0024*/

    /*========== DETACH_INIT的子状态 ==========*/
    EMM_OM_ERRLOG_SS_DETACH_WAIT_CN_DETACH_CNF            ,
    EMM_OM_ERRLOG_SS_DETACH_WAIT_MRRC_REL_CNF             ,


    /*========== EMM_OM_ERRLOG_MS_RRC_CONN_INIT的子状态 =*/
    EMM_OM_ERRLOG_SS_RRC_CONN_WAIT_EST_CNF                ,
    EMM_OM_ERRLOG_SS_RRC_CONN_WAIT_REL_CNF                ,


    /*========== AUTH过程中的子状态 ===========*/
    EMM_OM_ERRLOG_SS_AUTH_WAIT_CN_AUTH,

    /*========== SUSPEND过程中的子状态 ========*/
    EMM_OM_ERRLOG_SS_SUSPEND_RRCORI_WAIT_MMC_SUSPEND,
    EMM_OM_ERRLOG_SS_SUSPEND_RRCORI_WAIT_OTHER_SUSPEND,
    EMM_OM_ERRLOG_SS_SUSPEND_WAIT_END,
    EMM_OM_ERRLOG_SS_SUSPEND_MMCORI_WAIT_OTHER_SUSPEND,
    EMM_OM_ERRLOG_SS_SUSPEND_SYSCFGORI_WAIT_OTHER_SUSPEND,

    /*========== RESUME过程中的子状态 ========*/
    EMM_OM_ERRLOG_SS_RESUME_RRCRSM_WAIT_OTHER_RESUME,
    EMM_OM_ERRLOG_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND,
    EMM_OM_ERRLOG_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND,

    EMM_OM_ERRLOG_SS_BUTT
};
typedef VOS_UINT16  EMM_OM_ERRLOG_SS_STATE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : EMM_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_U16
 枚举说明  : err log主动上报类型
 1.日    期   : 2015年08月05日
   作    者   : wangchen 00209181
   修改内容   : 新建
*****************************************************************************/
enum EMM_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM
{
    EMM_ERR_LOG_FAULT_REPORT                                = 0x01,             /* 故障上报 */
    EMM_ERR_LOG_ALARM_REPORT                                = 0x02,             /* 告警上报 */

    EMM_ERR_LOG_REPORT_TYPE_BUTT
};
typedef VOS_UINT16  EMM_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_UINT16;

/*****************************************************************************
 结构名称   :OM_LNAS_MSG_ID_ENUM_UINT32
 协议表格   :
 ASN.1 描述 :
 结构说明   :Om与LNAS交互消息
*****************************************************************************/
enum   OM_LNAS_MSG_ID_ENUM
{
    /* OM发给LNAS的原语 */
    ID_OM_LNAS_ERR_LOG_CTRL_IND                = (0x9001),   /* _H2ASN_MsgChoice LNAS_OM_ERROR_LOG_CTRL_IND_STRU */
    ID_OM_LNAS_ERR_LOG_REPORT_REQ              = (0x9002),   /* _H2ASN_MsgChoice LNAS_OM_ERR_LOG_REPORT_REQ_STRU */

    /*LNAS 发给OM的原语*/
    ID_LNAS_OM_ERR_LOG_REPORT_CNF              = (0x9003),   /* _H2ASN_MsgChoice LNAS_OM_ERR_LOG_REPORT_CNF_STRU */
};
typedef VOS_UINT32   OM_LNAS_MSG_ID_ENUM_UINT32;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*******************************************************************************
 结构名    : LNAS_OM_ERRLOG_PLMN_ID_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[3];
    VOS_UINT8                           ucRsv;
}LNAS_OM_ERRLOG_PLMN_ID_STRU;


/*******************************************************************************
 结构名    : LNAS_OM_ERRLOG_TAC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*******************************************************************************/

typedef struct
{
    VOS_UINT8                           ucTac;
    VOS_UINT8                           ucTacCnt;
    VOS_UINT8                           aucRsv[2];
}LNAS_OM_ERRLOG_TAC_STRU;

/*******************************************************************************
结构名    : NAS_MNTN_POSITION_INFO_STRU
协议表格  :
ASN.1描述 :
结构说明  : 位置信息，包括如下内容PLMN
         跟踪区信息，小区ID
*******************************************************************************/
typedef struct
{
    LNAS_OM_ERRLOG_PLMN_ID_STRU         stPlmnId;
    LNAS_OM_ERRLOG_TAC_STRU             stTac;
    VOS_UINT32                          ulCellId;
    VOS_UINT32                          ulArfcn;                                /* 驻留频点信息 */
    VOS_UINT32                          aulLteBand[2];                          /* L模当前驻留的频段信息 */
}LNAS_OM_ERRLOG_POSITION_INFO_STRU;

/*****************************************************************************
 结构名称   : LNAS_ERR_INFO_OVERFLOW_COUNT_EVENT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LNAS 环形buffer溢出计数向OM上报的ERRLOG事件结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgModuleId;
    VOS_UINT16                          usModemId;
    VOS_UINT16                          usAlmId;
    VOS_UINT16                          usAlmLevel;
    VOS_UINT16                          usAlmType;
    VOS_UINT32                          ulAlmLowSlice;
    VOS_UINT32                          ulAlmHighSlice;
    VOS_UINT32                          ulAlmLength;
}LNAS_OM_ERR_LOG_HEADER_STRU;

/*****************************************************************************
 结构名称   : LNAS_ERR_INFO_OVERFLOW_COUNT_EVENT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LNAS 环形buffer溢出计数向OM上报的ERRLOG事件结构
*****************************************************************************/
typedef struct
{
    LNAS_OM_ERR_LOG_HEADER_STRU                     stHeader;           /*消息头*/

    VOS_UINT32                                      ulOverflowCount;    /*溢出计数*/
}LNAS_ERR_INFO_OVERFLOW_COUNT_EVENT_STRU;

/*****************************************************************************
 结构名称   : EMM_OM_ERRLOG_ATTACH_CN_REJ_RESULT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : ATTACH CN拒绝时需要上报的信息
*****************************************************************************/
typedef struct
{
    EMM_OM_ERRLOG_CN_REJ_ENUM_UINT16        enCnRejCause;    /*ATTACH拒绝原因值*/
    EMM_ERR_LOG_ATTACH_TYPE_ENUM_UINT16     enReqType;       /*ATTACH发起时的类型 */
    EMM_OM_ERRLOG_CN_REJ_ENUM_UINT16        enOriginalRejectCause;
    VOS_UINT8                               aucReserved[2];
}EMM_OM_ERRLOG_ATTACH_CN_REJ_RESULT_STRU;

/*****************************************************************************
 结构名称   : LMM_ERR_INFO_ATTACH_RESULT_EVENT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LNAS ATTACH流程向OM上报的ERRLOG事件结构
*****************************************************************************/
typedef struct
{
    LNAS_OM_ERR_LOG_HEADER_STRU                     stHeader;       /*消息头*/

    EMM_OM_ERRLOG_TYPE_ENUM_UINT16                  enErrType;      /*错误类型*/
    VOS_UINT16                                      usRsv;

    EMM_OM_ERRLOG_ATTACH_CN_REJ_RESULT_STRU         stAttachCnRej;  /*ATTACH CN拒绝相关结构*/
    EMM_OM_ERRLOG_EST_RESULT_ENUM_UINT32            enEstCnfRslt;   /*建链结果*/
    EMM_OM_ERRLOG_SEND_RSLT_ENUM_UINT32             enDataCnfRslt;  /*直传消息结果*/
    LNAS_OM_ERRLOG_POSITION_INFO_STRU               stPositionInfo;
}EMM_ERR_INFO_ATTACH_RESULT_EVENT_STRU;

/*****************************************************************************
 结构名称   : EMM_OM_ERRLOG_TAU_CN_REJ_RESULT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : TAU CN拒绝时需要上报的信息
*****************************************************************************/
typedef struct
{
    EMM_OM_ERRLOG_CN_REJ_ENUM_UINT16        enCnRejCause;    /*TAU拒绝原因值*/
    EMM_ERR_LOG_TAU_TYPE_ENUM_UINT16        enReqType;       /*TAU发起业务时的类型*/
    EMM_OM_ERRLOG_CN_REJ_ENUM_UINT16        enOriginalRejectCause;
    VOS_UINT8                               aucReserved[2];
}EMM_OM_ERRLOG_TAU_CN_REJ_RESULT_STRU;

/*****************************************************************************
 结构名称   : LMM_ERR_INFO_TAU_RESULT_EVENT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LNAS TAU流程向OM上报的ERRLOG事件结构
*****************************************************************************/
typedef struct
{
    LNAS_OM_ERR_LOG_HEADER_STRU                     stHeader;       /*消息头*/

    EMM_OM_ERRLOG_TYPE_ENUM_UINT16                  enErrType;      /*错误类型*/
    VOS_UINT16                                      usRsv;

    EMM_OM_ERRLOG_TAU_CN_REJ_RESULT_STRU            stTauCnRej;     /*TAU CN拒绝相关结构*/
    EMM_OM_ERRLOG_EST_RESULT_ENUM_UINT32            enEstCnfRslt;   /*建链结果*/
    EMM_OM_ERRLOG_SEND_RSLT_ENUM_UINT32             enDataCnfRslt;  /*直传消息结果*/
    LNAS_OM_ERRLOG_POSITION_INFO_STRU               stPositionInfo;
}EMM_ERR_INFO_TAU_RESULT_EVENT_STRU;

/*****************************************************************************
 结构名称   : EMM_ERR_INFO_MT_DETACH_RESULT_EVENT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LNAS MT DETACH流程向OM上报的ERRLOG事件结构
*****************************************************************************/
typedef struct
{
    LNAS_OM_ERR_LOG_HEADER_STRU             stHeader;           /*消息头*/

    EMM_OM_ERRLOG_CN_CAUSE_ENUM_UINT16      enCnDetCause;       /*MT DETACH可能带原因值，如果不带，则置成无效值*/
    EMM_ERR_LOG_MT_DETACH_TYPE_ENUM_UINT16  enCnDetReqType;     /*网侧触发的DETACH类型*/
    EMM_ERR_LOG_MT_DETACH_TYPE_ENUM_UINT16  enOriginalRejectCause;
    VOS_UINT8                               aucReserved[2];
    LNAS_OM_ERRLOG_POSITION_INFO_STRU       stPositionInfo;
}EMM_ERR_INFO_MT_DETACH_RESULT_EVENT_STRU;

/*****************************************************************************
 结构名称   : EMM_ERR_INFO_LOCAL_DETACH_RESULT_EVENT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LNAS LOCAL DETACH流程向OM上报的ERRLOG事件结构
*****************************************************************************/
typedef struct
{
    LNAS_OM_ERR_LOG_HEADER_STRU                     stHeader;           /*消息头*/

    EMM_ERR_LOG_LOCAL_DETACH_TYPE_ENUM_UINT16       enLocalDetType;     /*本地detach类型*/
    VOS_UINT16                                      usRsv;
    LNAS_OM_ERRLOG_POSITION_INFO_STRU               stPositionInfo;
}EMM_ERR_INFO_LOCAL_DETACH_RESULT_EVENT_STRU;

/*****************************************************************************
 结构名称   : EMM_OM_ERRLOG_NOR_SERVICE_CN_REJ_RESULT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : NORMAL SERVICE相关的流程失败上报结构(普通数据流程)
*****************************************************************************/
typedef struct
{
    EMM_OM_ERRLOG_CN_REJ_ENUM_UINT16        enCnRejCause;    /*SERVICE拒绝原因值*/
    EMM_OM_ERRLOG_CN_REJ_ENUM_UINT16        enOriginalRejectCause;
}EMM_OM_ERRLOG_NOR_SERVICE_CN_REJ_RESULT_STRU;

/*****************************************************************************
 结构名称   : EMM_ERR_INFO_NOR_SERVICE_RESULT_EVENT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : NORMAL SERVICE相关的流程失败上报结构(普通数据业务流程)
*****************************************************************************/
typedef struct
{
    LNAS_OM_ERR_LOG_HEADER_STRU                      stHeader;           /*消息头*/

    EMM_OM_ERRLOG_TYPE_ENUM_UINT16                   enErrType;          /*错误类型*/
    VOS_UINT16                                       usRsv;

    EMM_OM_ERRLOG_NOR_SERVICE_CN_REJ_RESULT_STRU     stNorServiceCnRej;  /*普通Service CN拒绝相关结构*/
    EMM_OM_ERRLOG_EST_RESULT_ENUM_UINT32             enEstCnfRslt;       /*建链结果*/
    EMM_OM_ERRLOG_SEND_RSLT_ENUM_UINT32              enDataCnfRslt;      /*直传消息结果*/
    LNAS_OM_ERRLOG_POSITION_INFO_STRU                stPositionInfo;
}EMM_ERR_INFO_NOR_SERVICE_RESULT_EVENT_STRU;

/*****************************************************************************
 结构名称   : EMM_ERR_INFO_EXT_SERVICE_RESULT_EVENT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : EXT-SERVICE相关的流程失败上报结构(CSFB流程)
*****************************************************************************/
typedef struct
{
    LNAS_OM_ERR_LOG_HEADER_STRU                     stHeader;           /*消息头*/

    EMM_OM_LMM_CSFB_FAIL_CAUSE_ENUM_UINT8           enCsfbFailCause;    /* CSFB失败原因*/
    VOS_UINT8                                       ucRcv;
    EMM_OM_ERRLOG_CN_REJ_ENUM_UINT16                enCnRejCause;       /* 可能会导致丢网的原因值*/
    EMM_OM_ERRLOG_CN_REJ_ENUM_UINT16                enOriginalRejectCause;
    VOS_UINT16                                      usRsv;
    LNAS_OM_ERRLOG_POSITION_INFO_STRU               stPositionInfo;
}EMM_ERR_INFO_EXT_SERVICE_RESULT_EVENT_STRU;

/*****************************************************************************
 结构名称   : LMM_ERR_INFO_PAGING_RESULT_EVENT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LNAS PAGING流程向OM上报的ERRLOG事件结构，目前只关注PS IMSI PAGING
*****************************************************************************/
typedef struct
{
    LNAS_OM_ERR_LOG_HEADER_STRU             stHeader;           /*消息头*/

    EMM_OM_ERRLOG_PAGING_ENUM_UINT16        enPagingProcess;    /*对应某一具体的PAGING流程*/
    EMM_OM_LMM_PAGING_FAIL_CAUSE_ENUM_UINT8 enPagingFailCause;
    VOS_UINT8                               ucRsv;
    EMM_OM_ERRLOG_MS_STATE_ENUM_UINT16      enMainState;        /* 当前主状态 */
    EMM_OM_ERRLOG_SS_STATE_ENUM_UINT16      enSubState;         /* 当前子状态 */

    LNAS_OM_ERRLOG_POSITION_INFO_STRU       stPositionInfo;
}EMM_ERR_INFO_PAGING_RESULT_EVENT_STRU;

/*****************************************************************************
 结构名称   : LMM_ERR_INFO_RAT_RESULT_EVENT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LNAS RAT流程向OM上报的ERRLOG事件结构，目前只关心等系统消息超时的场景
*****************************************************************************/
typedef struct
{
    LNAS_OM_ERR_LOG_HEADER_STRU             stHeader;       /*消息头*/

    EMM_OM_ERRLOG_RAT_ENUM_UINT16           enRatProcess;   /*对应某一具体的异系统场景*/
    VOS_UINT16                              usRsv;
    LNAS_OM_ERRLOG_POSITION_INFO_STRU       stPositionInfo;
}EMM_ERR_INFO_RAT_RESULT_EVENT_STRU;

/*****************************************************************************
 结构名称   :ESM_OM_ERRLOG_PDN_CONN_REJ_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : PDN CONN REJ上报结构, 为了区分是哪种类型失败，跟产品线约定，
 默认值是0，如果对应的项大于等于1，则认为该错误类型有效
*****************************************************************************/
typedef struct
{
    LNAS_OM_ERR_LOG_HEADER_STRU             stHeader;       /*消息头*/

    ESM_OM_ERRLOG_ID_ENUM_UINT16            enFailCause;    /*ESM相关拒绝原因值*/
    ESM_OM_ERRLOG_TIMEOUT_ENUM_UINT16       enEsmTimeout;   /*定时器超时*/
    LNAS_OM_ERRLOG_POSITION_INFO_STRU       stPositionInfo;
} ESM_ERR_INFO_PDN_CONN_REJ_RESULT_EVENT_STRU;

/*****************************************************************************
 结构名称   :ESM_OM_ERRLOG_PDN_DISCONN_REJ_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : PDN DISCONN REJ上报结构，为了区分是哪种类型失败，跟产品线约定，
 默认值是0，如果对应的项大于等于1，则认为该错误类型有效
*****************************************************************************/
typedef struct
{
    LNAS_OM_ERR_LOG_HEADER_STRU             stHeader;       /*消息头*/

    ESM_OM_ERRLOG_ID_ENUM_UINT16            enFailCause;    /*ESM相关拒绝原因值*/
    ESM_OM_ERRLOG_TIMEOUT_ENUM_UINT16       enEsmTimeout;   /*定时器超时*/
    LNAS_OM_ERRLOG_POSITION_INFO_STRU       stPositionInfo;
} ESM_ERR_INFO_PDN_DISCONN_REJ_RESULT_EVENT_STRU;

/*****************************************************************************
 结构名称   :ESM_ERR_INFO_RES_MOD_REJ_RESULT_EVENT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : RES MOD REJ上报结构，为了区分是哪种类型失败，跟产品线约定，
 默认值是0，如果对应的项大于等于1，则认为该错误类型有效
*****************************************************************************/
typedef struct
{
    LNAS_OM_ERR_LOG_HEADER_STRU             stHeader;       /*消息头*/

    ESM_OM_ERRLOG_ID_ENUM_UINT16            enFailCause;    /*ESM相关拒绝原因值*/
    ESM_OM_ERRLOG_TIMEOUT_ENUM_UINT16       enEsmTimeout;   /*定时器超时*/
    LNAS_OM_ERRLOG_POSITION_INFO_STRU       stPositionInfo;
} ESM_ERR_INFO_RES_MOD_REJ_RESULT_EVENT_STRU;

/*****************************************************************************
 结构名称   :ESM_ERR_INFO_RES_ALLOC_REJ_RESULT_EVENT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : RES ALLOC REJ上报结构，为了区分是哪种类型失败，跟产品线约定，
 默认值是0，如果对应的项大于等于1，则认为该错误类型有效
*****************************************************************************/
typedef struct
{
    LNAS_OM_ERR_LOG_HEADER_STRU             stHeader;       /*消息头*/

    ESM_OM_ERRLOG_ID_ENUM_UINT16            enFailCause;    /*ESM相关拒绝原因值*/
    ESM_OM_ERRLOG_TIMEOUT_ENUM_UINT16       enEsmTimeout;   /*定时器超时*/
    LNAS_OM_ERRLOG_POSITION_INFO_STRU       stPositionInfo;
} ESM_ERR_INFO_RES_ALLOC_REJ_RESULT_EVENT_STRU;

/*****************************************************************************
 结构名称   :EMM_ERR_INFO_AUTH_FAIL_RESULT_EVENT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 鉴权fail导致的丢网原因上报
*****************************************************************************/
typedef struct
{
    LNAS_OM_ERR_LOG_HEADER_STRU             stHeader;       /*消息头*/

    EMM_OM_ERRLOG_AUTH_FAIL_ENUM_UINT16     enAuthFail;     /*鉴权fail原因*/
    VOS_UINT16                              usRsv;
    LNAS_OM_ERRLOG_POSITION_INFO_STRU       stPositionInfo;
} EMM_ERR_INFO_AUTH_FAIL_RESULT_EVENT_STRU;
/*****************************************************************************
 结构名称   : EMM_ERR_INFO_IMPROVEMENT_EVENT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 优化项目生效上报
*****************************************************************************/
typedef struct
{
    LNAS_OM_ERR_LOG_HEADER_STRU                 stHeader;       /*消息头*/

    EMM_OM_ERRLOG_IMPROVEMENT_TYPE_ENUM_UINT16  enImproveType;   /* 优化项目类别 */
    VOS_UINT16                                  usRsv;
}EMM_ERR_INFO_IMPROVEMENT_EVENT_STRU;
/*****************************************************************************
 结构名称   : LNAS_OM_ERR_LOG_REPORT_CNF_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LNAS向OM回复ERRLOG应答数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                     /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;     /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* 故障内容长度,如果ulRptlen为0,aucContent内容长度也为0 */
    VOS_UINT8                           aucContent[4]; /* 故障内容 */
    /*************************************************************************
        _H2ASN_Array2String
    *************************************************************************/
} LNAS_OM_ERR_LOG_REPORT_CNF_STRU;

/*****************************************************************************
 结构名称   : LNAS_OM_ERROR_LOG_CTRL_IND_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : ERRLOG 控制消息IND
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                    /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;    /*_H2ASN_Skip*/
    VOS_UINT16                          usModemID;
    VOS_UINT8                           ucAlmStatus;  /* 打开或者关闭ERRLOG上报功能 0:close 1:open */
    VOS_UINT8                           ucAlmLevel;   /* 上报级别 */
}LNAS_OM_ERROR_LOG_CTRL_IND_STRU;

/*****************************************************************************
 结构名称   : LNAS_OM_ERR_LOG_REPORT_REQ_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : ERRLOG请求消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;  /*_H2ASN_Skip*/
    VOS_UINT16                          usModemID;
    VOS_UINT8                           aucRsv[2];
}LNAS_OM_ERR_LOG_REPORT_REQ_STRU;


typedef struct
{
    OM_LNAS_MSG_ID_ENUM_UINT32          enMsgID;            /*_H2ASN_MsgChoice_Export OM_LNAS_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          OM_LNAS_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}OM_LNAS_MSG_DATA;

typedef struct
{
    VOS_MSG_HEADER
    OM_LNAS_MSG_DATA                    stMsgData;
}OmLnasInterface_MSG;

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


