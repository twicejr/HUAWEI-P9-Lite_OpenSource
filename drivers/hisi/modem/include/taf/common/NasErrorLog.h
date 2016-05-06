

#ifndef __NAS_ERRORLOG_H__
#define __NAS_ERRORLOG_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "errorlog.h"
#include "omerrorlog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define NAS_FTM_MAX_PTMSI_LEN                           (4)                     /* 最大的PTMSI的长度 */
#define NAS_FTM_MAX_TMSI_LEN                            (4)                     /* 最大的TMSI的长度 */

#define TAF_SDC_RING_BUFFER_SIZE                        (1024 * 2)              /* TAF层的环形共享缓存大小 */
#define NAS_MML_RING_BUFFER_SIZE                        (1024 * 6)              /* MM层的环形共享缓存大小 */
#define NAS_CC_RING_BUFFER_SIZE                         (1024 * 2)              /* CC层的环形共享缓存大小 */

#if (FEATURE_ON == FEATURE_LTE)
#define NAS_ERR_LOG_MML_MAX_RAT_NUM                     (3)                     /* 当前支持的接入技术个数 */
#else
#define NAS_ERR_LOG_MML_MAX_RAT_NUM                     (2)                     /* 当前支持的GU接入技术个数 */
#endif

#define NAS_ERR_LOG_CTRL_LEVEL_NULL                     (0)                     /* ErrLog等级未定义*/
#define NAS_ERR_LOG_CTRL_LEVEL_CRITICAL                 (1)                     /* ErrLog等级为紧急 */
#define NAS_ERR_LOG_CTRL_LEVEL_MAJOR                    (2)                     /* ErrLog等级为重要 */
#define NAS_ERR_LOG_CTRL_LEVEL_MINOR                    (3)                     /* ErrLog等级为次要 */
#define NAS_ERR_LOG_CTRL_LEVEL_WARNING                  (4)                     /* ErrLog等级为提示 */

#define NAS_ERR_LOG_MAX_RAT_SWITCH_RECORD_MUN           (20)                    /* 指定时间GUTL模式切换最大次数 */
#define NAS_ERR_LOG_MAX_RAT_SWITCH_STATISTIC_TIME       (172800)                /* GUTL模式最大统计时间，单位秒 */

#define NAS_ERR_LOG_ACTIVE_RPT_FLAG_OFFSET              (7)
#define NAS_ERR_LOG_RAT_SWITCH_RPT_FLAG_OFFSET          (2)

#define NAS_ERR_LOG_MAX_POSITION_RECORD_NUM             (8)                     /* 位置区记录的最大个数 */

#define NAS_ERR_LOG_MAX_CSFB_MT_STATE_RECORD_NUM        (32)                    /* CSFB MT记录的状态最大个数 */

#define NAS_INFO_CLT_MAX_PLMN_NUM                       (32)                    /* PLMN的最大个数 */

#define NAS_INFO_CLT_MAX_GSM_FREQ_NUM                   (60)                    /* GSM频点的最大个数 */

#define NAS_INFO_CLT_MAX_WCDMA_FREQ_NUM                 (16)                    /* WCDMA频点的最大个数 */

#define NAS_INFO_CLT_MAX_LTE_FREQ_NUM                   (16)                    /* LTE频点的最大个数 */

#define NAS_INFO_VERSION_INFO_LEN                       (9)                     /* DPLMN数据库版本号 */


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : NAS_ERR_LOG_NET_RAT_TYPE_ENUM
 结构说明  : 当前的接入技术
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
enum NAS_ERR_LOG_NET_RAT_TYPE_ENUM
{
    NAS_ERR_LOG_NET_RAT_TYPE_GSM,           /* GSM接入技术 */
    NAS_ERR_LOG_NET_RAT_TYPE_WCDMA,         /* WCDMA接入技术 */
    NAS_ERR_LOG_NET_RAT_TYPE_LTE,           /* LTE接入技术 */
    NAS_ERR_LOG_NET_RAT_TYPE_BUTT           /* 无效的接入技术 */
};
typedef VOS_UINT8 NAS_ERR_LOG_NET_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_ERR_LOG_PS_ACTION_TYPE_ENUM
 结构说明  : NAS_ERR_LOG_PS_REG_RESULT_EVENT_STRU消息中GMM操作类型
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
enum NAS_ERR_LOG_PS_ACTION_TYPE_ENUM
{
    NAS_ERR_LOG_GMM_ACTION_RAU                  = 0,
    NAS_ERR_LOG_GMM_ACTION_ATTACH               = 1,
    NAS_ERR_LOG_GMM_ACTION_COMBINED_RAU         = 2,
    NAS_ERR_LOG_GMM_ACTION_COMBINED_ATTACH      = 3,
    NAS_ERR_LOG_GMM_ACTION_PERIODC_RAU          = 4,
    NAS_ERR_LOG_GMM_ACTION_BUTT
};
typedef VOS_UINT32 NAS_ERR_LOG_GMM_ACTION_TYPE_ENUM_U32;

/*****************************************************************************
 枚举名    : NAS_ERR_LOG_REG_DOMAIN_ENUM
 枚举说明  : 注册的域信息
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
enum NAS_ERR_LOG_REG_DOMAIN_ENUM
{
    NAS_ERR_LOG_REG_DOMAIN_PS    = 0x00,                                        /* 注册结果域为PS域 */
    NAS_ERR_LOG_REG_DOMAIN_PS_CS = 0x01,                                        /* 注册结果域为CS+PS域 */
    NAS_ERR_LOG_REG_DOMAIN_BUTT
};
typedef VOS_UINT32 NAS_ERR_LOG_REG_DOMAIN_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_ERR_LOG_CALL_EX_STATE_ENUM
 枚举说明  : 呼叫状态
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
enum NAS_ERR_LOG_CALL_EX_STATE_ENUM
{
    NAS_ERR_LOG_CALL_S_ACTIVE,                                                  /* active */
    NAS_ERR_LOG_CALL_S_HELD,                                                    /* held */
    NAS_ERR_LOG_CALL_S_DIALING,                                                 /* dialing (MO call) */
    NAS_ERR_LOG_CALL_S_ALERTING,                                                /* alerting (MO call) */
    NAS_ERR_LOG_CALL_S_INCOMING,                                                /* incoming (MT call) */
    NAS_ERR_LOG_CALL_S_WAITING,                                                 /* waiting (MT call) */
    NAS_ERR_LOG_CALL_S_IDLE,                                                    /* idle */
    NAS_ERR_LOG_CALL_S_CCBS_WAITING_ACTIVE,                                     /* CCBS等待激活态 */
    NAS_ERR_LOG_CALL_S_CCBS_WAITING_RECALL,                                     /* CCBS等待回呼态 */
    NAS_ERR_LOG_CALL_S_UNKNOWN,                                                 /* unknown state */
    NAS_ERR_LOG_CALL_S_MO_FDN_CHECK,                                            /* FDN check */
    NAS_ERR_LOG_CALL_S_MO_CALL_CONTROL_CHECK,                                   /* CALL CONTROL check */
    NAS_ERR_LOG_CALL_S_BUTT
};
typedef VOS_UINT8  NAS_ERR_LOG_CALL_STATE_ENUM_U8;

/*****************************************************************************
 枚举名    : NAS_ERR_LOG_ALM_ID_ENUM
 枚举说明  : 故障告警ID
 1.日    期   : 2013年08月27日
   作    者   : f00179208
   修改内容   : 新建
 2.日    期   : 2014年09月16日
   作    者   : f00179208
   修改内容   : CS ERRLOG项目新增告警ID
*****************************************************************************/
enum NAS_ERR_LOG_ALM_ID_ENUM
{
    NAS_ERR_LOG_ALM_CS_REG_FAIL                             = 0x01,             /* CS域注册失败 */
    NAS_ERR_LOG_ALM_PS_REG_FAIL                             = 0x02,             /* PS域注册失败 */
    NAS_ERR_LOG_ALM_OOS_NW_SRCH_PROC_INFO                   = 0x03,             /* 出服务区的搜索过程信息 */
    NAS_ERR_LOG_ALM_CS_CALL_FAIL                            = 0x04,             /* CS呼叫失败及异常挂断 */
    NAS_ERR_LOG_ALM_PS_CALL_FAIL                            = 0x05,             /* PS呼叫失败及异常挂断 */
    NAS_ERR_LOG_ALM_SMS_FAIL                                = 0x06,             /* 短信失败 */
    NAS_ERR_LOG_ALM_VC_OPT_FAIL                             = 0x07,             /* VC操作失败 */
    NAS_ERR_LOG_ALM_CS_PAGING_FAIL                          = 0x08,             /* CS PAGING fail */
    NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL                         = 0x09,             /* CS MT fail */
    NAS_ERR_LOG_ALM_CSFB_MT_CALL_FAIL                       = 0x0a,             /* CSFB MT fail */
    NAS_ERR_LOG_ALM_MNTN                                    = 0x0b,             /* 故障告警的可维可测 */
    NAS_ERR_LOG_ALM_NW_DETACH_IND                           = 0x0c,             /* 网络发起的DETACH指示 */

    NAS_ERR_LOG_ALM_PS_SRV_REG_FAIL                         = 0x0d,             /* PS SERVICE被拒 */
    NAS_ERR_LOG_ALM_CM_SRV_REJ_IND                          = 0x0e,             /* CS SERVICE拒绝 */
    NAS_ERR_LOG_ALM_MO_DETACH_IND                           = 0x0f,             /* 本地发起的DETACH */
    NAS_ERR_LOG_ALM_RAT_FREQUENTLY_SWITCH                   = 0x10,             /* 4G与2/3G频繁切换 */

    NAS_ERR_LOG_ALM_OOS_BEGIN                               = 0x11,             /* 无服务开始 */
    NAS_ERR_LOG_ALM_OOS_END                                 = 0x12,             /* 无服务结束 */

    NAS_ERR_LOG_ALM_PORCESS_INFO_IND                        = 0x13,             /* 过程信息指示 */

    NAS_ERR_LOG_ALM_FFT_SRCH_MCC_INFO                        = 0x14,             /* FFT搜索MCC的结果 */

    NAS_ERR_LOG_ALM_GET_CARD_IMSI_FAIL                       = 0x15,             /* 获取卡的IMSI时失败 */

    NAS_ERR_LOG_ALM_SRVCC_FAIL_INFO                         = 0x16,             /* FFT搜索MCC的结果 */

    NAS_ERR_LOG_ALM_ID_BUTT
};
typedef VOS_UINT16  NAS_ERR_LOG_ALM_ID_ENUM_U16;

/*****************************************************************************
 枚举名    : NAS_ERR_LOG_ALM_REPORT_TYPE_ENUM
 枚举说明  : err log主动上报类型
 1.日    期   : 2013年07月06日
   作    者   : n00269697
   修改内容   : 新建
*****************************************************************************/
enum NAS_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM
{
    NAS_ERR_LOG_FAULT_REPORT                                = 0x01,             /* 故障上报 */
    NAS_ERR_LOG_ALARM_REPORT                                = 0x02,             /* 告警上报 */

    NAS_ERR_LOG_REPORT_TYPE_BUTT
};
typedef VOS_UINT16  NAS_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_U16;

/*****************************************************************************
 枚举名    : NAS_ERR_LOG_ALM_TYPE_ENUM
 枚举说明  : 故障告警类型
 1.日    期   : 2013年08月27日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
enum NAS_ERR_LOG_ALM_TYPE_ENUM
{
    NAS_ERR_LOG_ALM_TYPE_COMMUNICATION    = 0x00,                               /* 通信 */
    NAS_ERR_LOG_ALM_TYPE_TRAFFIC_QUALITY  = 0x01,                               /* 业务质量 */
    NAS_ERR_LOG_ALM_TYPE_DEAL_WRONG       = 0x02,                               /* 处理出错 */
    NAS_ERR_LOG_ALM_TYPE_DEVICE_FAILURE   = 0x03,                               /* 设备故障 */
    NAS_ERR_LOG_ALM_TYPE_ENV_FAILURE      = 0x04,                               /* 环境故障 */
    NAS_ERR_LOG_ALM_TYPE_BUTT
};
typedef VOS_UINT16  NAS_ERR_LOG_ALM_TYPE_ENUM_U16;

/*****************************************************************************
 枚举名    : NAS_ERR_LOG_FTM_PROJECT_ID_ENUM
 枚举说明  : 工程模式上报的功能ID
 1.日    期   : 2013年08月27日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
enum NAS_ERR_LOG_FTM_PROJECT_ID_ENUM
{
    NAS_FTM_PROJECT_TMSI_RPT,
    NAS_FTM_PROJECT_PTMSI_RPT,

    NAS_FTM_PROJECT_ID_BUTT
};
typedef VOS_UINT16  NAS_ERR_LOG_FTM_PROJECT_ID_ENUM_U8;

/*****************************************************************************
 枚举名    : NAS_ERR_LOG_CS_PAGING_CAUSE_ENUM
 枚举说明  : cs paging故障主动上报的错误原因值
 1.日    期   : 2014年09月16日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
enum NAS_ERR_LOG_CS_PAGING_CAUSE_ENUM
{
    NAS_ERR_LOG_CS_PAGING_CAUSE_MM_STATE_ERR       = 1,                         /* MM状态不正确 */
    NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR      = 2,                         /* 寻呼受限 */
    NAS_ERR_LOG_CS_PAGING_CAUSE_EST_FAIL           = 3,                         /* 连接建立失败 */
    NAS_ERR_LOG_CS_PAGING_CAUSE_EST_TIMEOUT        = 4,                         /* 连接建立超时 */
    NAS_ERR_LOG_CS_PAGING_CAUSE_EST_RELEASED       = 5,                         /* 连接建立被释放 */
    NAS_ERR_LOG_CS_PAGING_CAUSE_CONN_RELEASED      = 6,                         /* 连接被释放 */
    NAS_ERR_LOG_CS_PAGING_CAUSE_CONN_ABORT         = 7,                         /* 业务被ABORT */

    NAS_ERR_LOG_CS_PAGING_CAUSE_BUTT
};
typedef VOS_UINT32  NAS_ERR_LOG_CS_PAGING_CAUSE_ENUM_U32;

/*****************************************************************************
 枚举名    : NAS_ERR_LOG_CS_MT_CALL_CAUSE_ENUM
 枚举说明  : cs mt call故障主动上报的错误原因值
 1.日    期   : 2014年09月16日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
enum NAS_ERR_LOG_CS_MT_CALL_CAUSE_ENUM
{
    /* CC的异常原因值 */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_TI_CODED_AS_111        = 1,                    /* TI值为7 */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_TI_INC_SET_TO_1        = 2,                    /* TI值错误置为1 */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_TI_IS_USED             = 3,                    /* TI被使用 */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_CC_CREATE_ENTYTY_FAIL  = 4,                    /* CC创建实体失败 */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_NEW_CALL_NOT_ALLOW     = 5,                    /* 不能再发起新的呼叫 */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_OPTIONAL_IE_ERR        = 6,                    /* SETUP中条件IE检查失败 */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_DECODE_FAIL            = 7,                    /* CC解码失败 */

    /* CALL的异常原因值 */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_CALL_STATE_CTRL_NOT_SUPPORT  = 8,              /* 语音呼叫不支持 */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_BC_CHECK_FAIL          = 9,                    /* BC检查失败 */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_MT_CALL_NOT_ALLOW      = 10,                   /* 不允许发起MT呼叫 */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_NE_GET_BC_FAIL         = 11,                   /* BC协商失败 */

    NAS_ERR_LOG_CS_MT_CALL_CAUSE_BUTT
};
typedef VOS_UINT32  NAS_ERR_LOG_CS_MT_CALL_CAUSE_ENUM_U32;

/*****************************************************************************
 枚举名    : NAS_ERR_BASE_LOG_STATE_ENUM
 枚举说明  : 基本状态枚举
 1.日    期   : 2015年07月23日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
enum NAS_ERR_BASE_LOG_STATE_ENUM
{
    NAS_ERR_LOG_BASE_STATE_NULL                                = 0x00,          /* 无效值 */
    NAS_ERR_LOG_BASE_STATE_LMM_CS_PAGING_RECEIVED              = 0x01,          /* LMM的CSFB PAGING已经接收 */
    NAS_ERR_LOG_BASE_STATE_TRAG_NW_SEARCH_FOR_RCV_LMM_SRV_RST  = 0x02,          /* 接收到LMM的Service Result指示,触发搜网 */
    NAS_ERR_LOG_BASE_STATE_END_IND_RECEIVED                    = 0x03,          /* 接收到LMM的Service End Ind指示 */
    NAS_ERR_LOG_BASE_STATE_SUSPEND_IND_RECEIVED                = 0x04,          /* 已收到异系统开始挂起指示 */
    NAS_ERR_LOG_BASE_STATE_LTE_RESUME_IND_RECEIVED             = 0x05,          /* 已收到LTE的恢复指示 */
    NAS_ERR_LOG_BASE_STATE_GU_RESUME_IND_RECEIVED              = 0x06,          /* 已收到异系统结束恢复指示 */
    NAS_ERR_LOG_BASE_STATE_RESUME_TO_GU_FAIL                   = 0x07,          /* 异系统恢复失败 */
    NAS_ERR_LOG_BASE_STATE_LTE_SYS_INFO_RECEIVED               = 0x08,          /* 已收到LTE的系统消息 */
    NAS_ERR_LOG_BASE_STATE_GU_SYS_INFO_RECEIVED                = 0x09,          /* 已收到GU的系统消息 */
    NAS_ERR_LOG_BASE_STATE_PAGING_RSP_SEND                     = 0x0a,          /* LAI未发生改变，发送paging response */
    NAS_ERR_LOG_BASE_STATE_TRAG_LAU                            = 0x0b,          /* LAI发生改变,触发LAU */
    NAS_ERR_LOG_BASE_STATE_EST_FAILED                          = 0x0c,          /* 业务建链失败，含LAU建链 */
    NAS_ERR_LOG_BASE_STATE_EST_SUCCESSED                       = 0x0d,          /* 业务建链成功，含LAU建链 */
    NAS_ERR_LOG_BASE_STATE_AUTH_REJ                            = 0x0e,          /* LAU鉴权被拒 */
    NAS_ERR_LOG_BASE_STATE_AUTH_FAIL                           = 0x0f,          /* LAU鉴权失败 */
    NAS_ERR_LOG_BASE_STATE_T3240_TIMEOUT                       = 0x10,          /* T3240定时器超时 */
    NAS_ERR_LOG_BASE_STATE_LAU_REJECT                          = 0x11,          /* LAU被拒 */
    NAS_ERR_LOG_BASE_STATE_LAU_ACCEPT                          = 0x12,          /* LAU成功 */
    NAS_ERR_LOG_BASE_STATE_RRC_REL_IND_RECEIVED                = 0x13,          /* 已收到RRC连接释放指示 */
    NAS_ERR_LOG_BASE_STATE_CSFB_MT_PROTECT_TI_TIME_OUT         = 0x14,          /* CSFB MT保护定时器超时 */
    NAS_ERR_LOG_BASE_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND     = 0x15,          /* CSFB MT保护定时器超时状态下收到网络的REL IND */
    NAS_ERR_LOG_BASE_STATE_CM_SERVICE_MSG_RECEIVED             = 0x16,          /* CSFB MT业务消息已经接收 */

    NAS_ERR_LOG_BASE_STATE_BUTT
};
typedef VOS_UINT32  NAS_ERR_LOG_BASE_STATE_ENUM_U32;

/*****************************************************************************
 枚举名    : NAS_ERR_LOG_CSFB_MT_STATE_ENUM
 枚举说明  : csfb mt的状态
 1.日    期   : 2014年09月16日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
enum NAS_ERR_LOG_CSFB_MT_STATE_ENUM
{
    NAS_ERR_LOG_CSFB_MT_STATE_NULL                                = 0x00,       /* 无效值 */
    NAS_ERR_LOG_CSFB_MT_STATE_LMM_CS_PAGING_RECEIVED              = 0x01,       /* LMM的CSFB PAGING已经接收 */
    NAS_ERR_LOG_CSFB_MT_STATE_TRAG_NW_SEARCH_FOR_RCV_LMM_SRV_RST  = 0x02,       /* 接收到LMM的Service Result指示,触发搜网 */
    NAS_ERR_LOG_CSFB_MT_STATE_END_IND_RECEIVED                    = 0x03,       /* 接收到LMM的Service End Ind指示 */
    NAS_ERR_LOG_CSFB_MT_STATE_SUSPEND_IND_RECEIVED                = 0x04,       /* 已收到异系统开始挂起指示 */
    NAS_ERR_LOG_CSFB_MT_STATE_LTE_RESUME_IND_RECEIVED             = 0x05,       /* 已收到LTE的恢复指示 */
    NAS_ERR_LOG_CSFB_MT_STATE_GU_RESUME_IND_RECEIVED              = 0x06,       /* 已收到异系统结束恢复指示 */
    NAS_ERR_LOG_CSFB_MT_STATE_RESUME_TO_GU_FAIL                   = 0x07,       /* 异系统恢复失败 */
    NAS_ERR_LOG_CSFB_MT_STATE_LTE_SYS_INFO_RECEIVED               = 0x08,       /* 已收到LTE的系统消息 */
    NAS_ERR_LOG_CSFB_MT_STATE_GU_SYS_INFO_RECEIVED                = 0x09,       /* 已收到GU的系统消息 */
    NAS_ERR_LOG_CSFB_MT_STATE_PAGING_RSP_SEND                     = 0x0a,       /* LAI未发生改变，发送paging response */
    NAS_ERR_LOG_CSFB_MT_STATE_TRAG_LAU                            = 0x0b,       /* LAI发生改变,触发LAU */
    NAS_ERR_LOG_CSFB_MT_STATE_EST_FAILED                          = 0x0c,       /* 业务建链失败，含LAU建链 */
    NAS_ERR_LOG_CSFB_MT_STATE_EST_SUCCESSED                       = 0x0d,       /* 业务建链成功，含LAU建链 */
    NAS_ERR_LOG_CSFB_MT_STATE_AUTH_REJ                            = 0x0e,       /* LAU鉴权被拒 */
    NAS_ERR_LOG_CSFB_MT_STATE_AUTH_FAIL                           = 0x0f,       /* LAU鉴权失败 */
    NAS_ERR_LOG_CSFB_MT_STATE_T3240_TIMEOUT                       = 0x10,       /* T3240定时器超时 */
    NAS_ERR_LOG_CSFB_MT_STATE_LAU_REJECT                          = 0x11,       /* LAU被拒 */
    NAS_ERR_LOG_CSFB_MT_STATE_LAU_ACCEPT                          = 0x12,       /* LAU成功 */
    NAS_ERR_LOG_CSFB_MT_STATE_RRC_REL_IND_RECEIVED                = 0x13,       /* 已收到RRC连接释放指示 */
    NAS_ERR_LOG_CSFB_MT_STATE_CSFB_MT_PROTECT_TI_TIME_OUT         = 0x14,       /* CSFB MT保护定时器超时 */
    NAS_ERR_LOG_CSFB_MT_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND     = 0x15,       /* CSFB MT保护定时器超时状态下收到网络的REL IND */
    NAS_ERR_LOG_CSFB_MT_STATE_CM_SERVICE_MSG_RECEIVED             = 0x16,       /* CSFB MT业务消息已经接收 */

    NAS_ERR_LOG_CSFB_MT_CALL_CAUSE_BUTT
};
typedef VOS_UINT32  NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32;

/*****************************************************************************
枚举名    :  NAS_ERR_LOG_MO_DETACH_TYPE_ENUM
结构说明  :  MO DETACH类型枚举
1.日    期   : 2015年3月10日
  作    者   : n00269697
  修改内容   : 新增
*****************************************************************************/
enum NAS_ERR_LOG_MO_DETACH_TYPE_ENUM
{
    NAS_ERR_LOG_MO_DETACH_NULL          = 0,
    NAS_ERR_LOG_MO_DETACH_PS            = 1,
    NAS_ERR_LOG_MO_DETACH_CS            = 2,
    NAS_ERR_LOG_MO_DETACH_CS_PS         = 3,

    NAS_ERR_LOG_MO_DETACH_BUTT
};

typedef VOS_UINT32 NAS_ERR_LOG_MO_DETACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_INFO_CLT_BAND_IND_ENUM
 结构说明  : 频段枚举

 1.日    期   : 2015年07月08日
   作    者   : f00179208
   修改内容   : 新增
*****************************************************************************/
enum NAS_INFO_CLT_BAND_IND_ENUM
{
    NAS_INFO_CLT_BAND_IND_NONE               = 0,
    NAS_INFO_CLT_BAND_IND_1                  = 1,
    NAS_INFO_CLT_BAND_IND_2                  = 2,
    NAS_INFO_CLT_BAND_IND_3                  = 3,
    NAS_INFO_CLT_BAND_IND_4                  = 4,
    NAS_INFO_CLT_BAND_IND_5                  = 5,
    NAS_INFO_CLT_BAND_IND_6                  = 6,
    NAS_INFO_CLT_BAND_IND_7                  = 7,
    NAS_INFO_CLT_BAND_IND_8                  = 8,
    NAS_INFO_CLT_BAND_IND_9                  = 9,
    NAS_INFO_CLT_BAND_IND_10                 = 10,
    NAS_INFO_CLT_BAND_IND_11                 = 11,
    NAS_INFO_CLT_BAND_IND_12                 = 12,
    NAS_INFO_CLT_BAND_IND_13                 = 13,
    NAS_INFO_CLT_BAND_IND_14                 = 14,
    NAS_INFO_CLT_BAND_IND_15                 = 15,
    NAS_INFO_CLT_BAND_IND_16                 = 16,
    NAS_INFO_CLT_BAND_IND_17                 = 17,
    NAS_INFO_CLT_BAND_IND_18                 = 18,
    NAS_INFO_CLT_BAND_IND_19                 = 19,
    NAS_INFO_CLT_BAND_IND_20                 = 20,
    NAS_INFO_CLT_BAND_IND_21                 = 21,
    NAS_INFO_CLT_BAND_IND_22                 = 22,
    NAS_INFO_CLT_BAND_IND_23                 = 23,
    NAS_INFO_CLT_BAND_IND_24                 = 24,
    NAS_INFO_CLT_BAND_IND_25                 = 25,
    NAS_INFO_CLT_BAND_IND_26                 = 26,
    NAS_INFO_CLT_BAND_IND_27                 = 27,
    NAS_INFO_CLT_BAND_IND_28                 = 28,
    NAS_INFO_CLT_BAND_IND_29                 = 29,
    NAS_INFO_CLT_BAND_IND_30                 = 30,
    NAS_INFO_CLT_BAND_IND_31                 = 31,
    NAS_INFO_CLT_BAND_IND_32                 = 32,
    NAS_INFO_CLT_BAND_IND_33                 = 33,
    NAS_INFO_CLT_BAND_IND_34                 = 34,
    NAS_INFO_CLT_BAND_IND_35                 = 35,
    NAS_INFO_CLT_BAND_IND_36                 = 36,
    NAS_INFO_CLT_BAND_IND_37                 = 37,
    NAS_INFO_CLT_BAND_IND_38                 = 38,
    NAS_INFO_CLT_BAND_IND_39                 = 39,
    NAS_INFO_CLT_BAND_IND_40                 = 40,
    NAS_INFO_CLT_BAND_IND_41                 = 41,
    NAS_INFO_CLT_BAND_IND_42                 = 42,
    NAS_INFO_CLT_BAND_IND_43                 = 43,
    NAS_INFO_CLT_BAND_IND_44                 = 44,

    NAS_INFO_CLT_BAND_IND_BUTT
};
typedef VOS_UINT16 NAS_INFO_CLT_BAND_IND_ENUM_UINT16;

/*****************************************************************************
枚举名    :  NAS_INFO_CLT_SCENE_TYPE_ENUM
结构说明  :  信息收集的场景ID
1.日    期   : 2015年07月08日
  作    者   : f00179208
  修改内容   : 新增
*****************************************************************************/
enum NAS_INFO_CLT_INFO_ID_ENUM
{
    NAS_INFO_CLT_SCENE_TYPE_FREQ_BAND            = 1,                           /* 云端频点频点信息收集 */
    NAS_INFO_CLT_SCENE_TYPE_BUTT
};
typedef VOS_UINT32 NAS_INFO_CLT_SCENE_TYPE_ENUM_UINT32;

/*****************************************************************************
枚举名    :  NAS_INFO_CLT_RATMODE_ENUM
结构说明  :  接入模式
1.日    期   : 2015年07月08日
  作    者   : f00179208
  修改内容   : 新增
*****************************************************************************/
enum NAS_INFO_CLT_RATMODE_ENUM
{
    NAS_INFO_CLT_RATMODE_GSM                         = 0,
    NAS_INFO_CLT_RATMODE_WCDMA                       = 1,
    NAS_INFO_CLT_RATMODE_LTE                         = 2,
    NAS_INFO_CLT_RATMODE_TDS                         = 3,
    NAS_INFO_CLT_RATMODE_BUTT
};
typedef VOS_UINT8 NAS_INFO_CLT_RATMODE_ENUM_UINT8;

/*****************************************************************************
枚举名    :  NAS_ERR_LOG_OOS_EVENT_ENUM
结构说明  :  导致无服务的事件枚举
1.日    期   : 2015年08月13日
  作    者   : f00179208
  修改内容   : 新增
*****************************************************************************/
enum NAS_ERR_LOG_OOS_EVENT_ENUM
{
    NAS_ERR_LOG_OOS_EVENT_NULL                                           = 0x0,

    /* 用户配置的场景 */
    NAS_ERR_LOG_OOS_EVENT_USER_SYSCFG                                    = 0x001,
    NAS_ERR_LOG_OOS_EVENT_USER_LIST_SRCH                                 = 0x002,
    NAS_ERR_LOG_OOS_EVENT_USER_SPEC_SRCH                                 = 0x003,
    NAS_ERR_LOG_OOS_EVENT_USER_AUTO_SEL                                  = 0x004,
    NAS_ERR_LOG_OOS_EVENT_USER_POWER_ON                                  = 0x005,
    NAS_ERR_LOG_OOS_EVENT_USER_POWER_OFF                                 = 0x006,
    NAS_ERR_LOG_OOS_EVENT_USER_DETACH                                    = 0x007,

    /* 接入层丢网的场景 */
    NAS_ERR_LOG_OOS_EVENT_GAS_NORMAL_AREA_LOST                           = 0x100,
    NAS_ERR_LOG_OOS_EVENT_WAS_NORMAL_AREA_LOST                           = 0x101,
    NAS_ERR_LOG_OOS_EVENT_TAS_NORMAL_AREA_LOST                           = 0x102,
    NAS_ERR_LOG_OOS_EVENT_LMM_NORMAL_AREA_LOST                           = 0x103,
    NAS_ERR_LOG_OOS_EVENT_GAS_NO_RF_AREA_LOST                            = 0x104,
    NAS_ERR_LOG_OOS_EVENT_WAS_NO_RF_AREA_LOST                            = 0x105,
    NAS_ERR_LOG_OOS_EVENT_TAS_NO_RF_AREA_LOST                            = 0x106,
    NAS_ERR_LOG_OOS_EVENT_LMM_NO_RF_AREA_LOST                            = 0x107,
    NAS_ERR_LOG_OOS_EVENT_WAS_LIMITED_CAMP                               = 0x108,
    NAS_ERR_LOG_OOS_EVENT_TAS_LIMITED_CAMP                               = 0x109,
    NAS_ERR_LOG_OOS_EVENT_GAS_AC_INFO_CHANGE                             = 0x10a,
    NAS_ERR_LOG_OOS_EVENT_WAS_AC_INFO_CHANGE                             = 0x10b,
    NAS_ERR_LOG_OOS_EVENT_TAS_AC_INFO_CHANGE                             = 0x10c,

    /* 注册失败的场景 */
    NAS_ERR_LOG_OOS_EVENT_CS_REG_FAIL                                    = 0x200,
    NAS_ERR_LOG_OOS_EVENT_PS_REG_FAIL                                    = 0x201,
    NAS_ERR_LOG_OOS_EVENT_COMBINE_EPS_REG_ATTACH_FAIL                    = 0x202,
    NAS_ERR_LOG_OOS_EVENT_COMBINE_EPS_REG_TAU_FAIL                       = 0x203,
    NAS_ERR_LOG_OOS_EVENT_COMBINE_EPS_REG_ONLY_EPS_SUCC                  = 0x204,
    NAS_ERR_LOG_OOS_EVENT_EPS_REG_ATTACH_FAIL                            = 0x205,
    NAS_ERR_LOG_OOS_EVENT_EPS_REG_TAU_FAIL                               = 0x206,
    NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH                                = 0x207,
    NAS_ERR_LOG_OOS_EVENT_ATTACH_AUTH_REJ                                = 0x208,

    /* 服务被拒的场景 */
    NAS_ERR_LOG_OOS_EVENT_CM_SERVICE_REJ                                 = 0x300,
    NAS_ERR_LOG_OOS_EVENT_PS_SERVICE_REG_FAIL                            = 0x301,
    NAS_ERR_LOG_OOS_EVENT_EPS_SERVICE_REQ_FAIL                           = 0x302,

    /* 网络DETACH的场景 */
    NAS_ERR_LOG_OOS_EVENT_GUT_NW_DETACH                                  = 0x400,
    NAS_ERR_LOG_OOS_EVENT_LTE_NW_DETACH                                  = 0x401,

    /* 本地DETACH的场景 */
    NAS_ERR_LOG_OOS_EVENT_GUT_LOCAL_DETACH                               = 0x500,
    NAS_ERR_LOG_OOS_EVENT_LTE_LOCAL_DETACH                               = 0x501,

    /* 内部触发的场景 */
    NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_GAS_SYS_INFO_EXP  = 0x600,
    NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_WAS_SYS_INFO_EXP  = 0x601,
    NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_TAS_SYS_INFO_EXP  = 0x602,
    NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_LNAS_SYS_INFO_EXP = 0x603,
    NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_GAS_SYS_INFO_EXP         = 0x604,
    NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_WAS_SYS_INFO_EXP         = 0x605,
    NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_TAS_SYS_INFO_EXP         = 0x606,
    NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_LNAS_SYS_INFO_EXP        = 0x607,
    NAS_ERR_LOG_OOS_EVENT_HIGH_PRO_PLMN_SRCH_BACK_TO_ORIG_PLMN_FAIL      = 0x608,
    NAS_ERR_LOG_OOS_EVENT_DISABLE_LTE                                    = 0x609,
    NAS_ERR_LOG_OOS_EVENT_ENABLE_LTE                                     = 0x60a,

    NAS_ERR_LOG_OOS_EVENT_BUTT                                           = 0xFFFFFFFF
};
typedef VOS_UINT32 NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32;

/*****************************************************************************
枚举名    :  NAS_ERR_LOG_OOS_CAUSE_ENUM
结构说明  :  导致无服务的原因值枚举
1.日    期   : 2015年08月13日
  作    者   : f00179208
  修改内容   : 新增
*****************************************************************************/
enum NAS_ERR_LOG_OOS_CAUSE_ENUM
{
    NAS_ERR_LOG_OOS_CAUSE_NULL                                           = 0x0,

    /* 用户配置的场景 */
    NAS_ERR_LOG_OOS_CAUSE_USER_SYSCFG                                    = 0x001,
    NAS_ERR_LOG_OOS_CAUSE_USER_LIST_SRCH                                 = 0x002,
    NAS_ERR_LOG_OOS_CAUSE_USER_SPEC_SRCH                                 = 0x003,
    NAS_ERR_LOG_OOS_CAUSE_USER_AUTO_SEL                                  = 0x004,
    NAS_ERR_LOG_OOS_CAUSE_USER_POWER_ON                                  = 0x005,
    NAS_ERR_LOG_OOS_CAUSE_USER_POWER_OFF                                 = 0x006,
    NAS_ERR_LOG_OOS_CAUSE_USER_DETACH                                    = 0x007,

    /* 接入层丢网的场景 */
    NAS_ERR_LOG_OOS_CAUSE_GAS_NORMAL_AREA_LOST                           = 0x100,
    NAS_ERR_LOG_OOS_CAUSE_WAS_NORMAL_AREA_LOST                           = 0x101,
    NAS_ERR_LOG_OOS_CAUSE_TAS_NORMAL_AREA_LOST                           = 0x102,
    NAS_ERR_LOG_OOS_CAUSE_LMM_NORMAL_AREA_LOST                           = 0x103,
    NAS_ERR_LOG_OOS_CAUSE_GAS_NO_RF_AREA_LOST                            = 0x104,
    NAS_ERR_LOG_OOS_CAUSE_WAS_NO_RF_AREA_LOST                            = 0x105,
    NAS_ERR_LOG_OOS_CAUSE_TAS_NO_RF_AREA_LOST                            = 0x106,
    NAS_ERR_LOG_OOS_CAUSE_LMM_NO_RF_AREA_LOST                            = 0x107,
    NAS_ERR_LOG_OOS_CAUSE_WAS_LIMITED_CAMP                               = 0x108,
    NAS_ERR_LOG_OOS_CAUSE_TAS_LIMITED_CAMP                               = 0x109,
    NAS_ERR_LOG_OOS_CAUSE_GAS_AC_INFO_CHANGE                             = 0x10a,
    NAS_ERR_LOG_OOS_CAUSE_WAS_AC_INFO_CHANGE                             = 0x10b,
    NAS_ERR_LOG_OOS_CAUSE_TAS_AC_INFO_CHANGE                             = 0x10c,

    /* 注册失败的场景 */
    NAS_ERR_LOG_OOS_CAUSE_CS_REG_FAIL                                    = 0x200,
    NAS_ERR_LOG_OOS_CAUSE_PS_REG_FAIL                                    = 0x201,
    NAS_ERR_LOG_OOS_CAUSE_COMBINE_EPS_REG_ATTACH_FAIL                    = 0x202,
    NAS_ERR_LOG_OOS_CAUSE_COMBINE_EPS_REG_TAU_FAIL                       = 0x203,
    NAS_ERR_LOG_OOS_CAUSE_COMBINE_EPS_REG_ONLY_EPS_SUCC                  = 0x204,
    NAS_ERR_LOG_OOS_CAUSE_EPS_REG_ATTACH_FAIL                            = 0x205,
    NAS_ERR_LOG_OOS_CAUSE_EPS_REG_TAU_FAIL                               = 0x206,
    NAS_ERR_LOG_OOS_CAUSE_EPS_ONLY_ATTACH                                = 0x207,
    NAS_ERR_LOG_OOS_CAUSE_ATTACH_AUTH_REJ                                = 0x208,

    /* 服务被拒的场景 */
    NAS_ERR_LOG_OOS_CAUSE_CM_SERVICE_REJ                                 = 0x300,
    NAS_ERR_LOG_OOS_CAUSE_PS_SERVICE_REG_FAIL                            = 0x301,
    NAS_ERR_LOG_OOS_CAUSE_EPS_SERVICE_REQ_FAIL                           = 0x302,

    /* 网络DETACH的场景 */
    NAS_ERR_LOG_OOS_CAUSE_GUT_NW_DETACH                                  = 0x400,
    NAS_ERR_LOG_OOS_CAUSE_LTE_NW_DETACH                                  = 0x401,

    /* 本地DETACH的场景 */
    NAS_ERR_LOG_OOS_CAUSE_GUT_LOCAL_DETACH                               = 0x500,
    NAS_ERR_LOG_OOS_CAUSE_LTE_LOCAL_DETACH                               = 0x501,

    /* 内部触发的场景 */
    NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CELL_RESEL_TI_WAIT_GAS_SYS_INFO_EXP  = 0x600,
    NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CELL_RESEL_TI_WAIT_WAS_SYS_INFO_EXP  = 0x601,
    NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CELL_RESEL_TI_WAIT_TAS_SYS_INFO_EXP  = 0x602,
    NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CELL_RESEL_TI_WAIT_LNAS_SYS_INFO_EXP = 0x603,
    NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CCO_TI_WAIT_GAS_SYS_INFO_EXP         = 0x604,
    NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CCO_TI_WAIT_WAS_SYS_INFO_EXP         = 0x605,
    NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CCO_TI_WAIT_TAS_SYS_INFO_EXP         = 0x606,
    NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CCO_TI_WAIT_LNAS_SYS_INFO_EXP        = 0x607,
    NAS_ERR_LOG_OOS_CAUSE_HIGH_PRO_PLMN_SRCH_BACK_TO_ORIG_PLMN_FAIL      = 0x608,
    NAS_ERR_LOG_OOS_CAUSE_DISABLE_LTE                                    = 0x609,
    NAS_ERR_LOG_OOS_CAUSE_ENABLE_LTE                                     = 0x60a,

    NAS_ERR_LOG_OOS_CAUSE_BUTT                                           = 0xFFFFFFFF
};
typedef VOS_UINT32 NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32;

/*****************************************************************************
枚举名    :  NAS_ERR_LOG_RATMODE_ENUM
结构说明  :  接入模式
1.日    期   : 2015年08月13日
  作    者   : f00179208
  修改内容   : 新增
*****************************************************************************/
enum NAS_ERR_LOG_RATMODE_ENUM
{
    NAS_ERR_LOG_RATMODE_GSM                         = 0,
    NAS_ERR_LOG_RATMODE_WCDMA                       = 1,
    NAS_ERR_LOG_RATMODE_LTE                         = 2,
    NAS_ERR_LOG_RATMODE_TDS                         = 3,
    NAS_ERR_LOG_RATMODE_BUTT
};
typedef VOS_UINT8 NAS_ERR_LOG_RATMODE_ENUM_UINT8;

/*****************************************************************************
枚举名    :  NAS_ERR_LOG_OOS_DOMAIN_ENUM
结构说明  :  无服务域
1.日    期   : 2015年08月13日
  作    者   : f00179208
  修改内容   : 新增
*****************************************************************************/
enum NAS_ERR_LOG_OOS_DOMAIN_ENUM
{
    NAS_ERR_LOG_OOS_NO_DOMAIN                       = 0,
    NAS_ERR_LOG_OOS_DOMAIN_CS                       = 1,
    NAS_ERR_LOG_OOS_DOMAIN_PS                       = 2,
    NAS_ERR_LOG_OOS_DOMAIN_BUTT
};
typedef VOS_UINT32 NAS_ERR_LOG_OOS_DOMAIN_ENUM_UINT32;


enum NAS_ERR_LOG_PROCESS_INFO_TYPE_ENUM
{
    NAS_ERR_LOG_PROCESS_INFO_TYPE_NULL              = 0,
    NAS_ERR_LOG_PROCESS_INFO_TYPE_CS_CALL_DISC      = 1,
    NAS_ERR_LOG_PROCESS_INFO_TYPE_ID_RES            = 2,
    NAS_ERR_LOG_PROCESS_INFO_TYPE_BUTT
};
typedef VOS_UINT32 NAS_ERR_LOG_PROCESS_INFO_TYPE_ENUM_UINT32;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*******************************************************************************
 结构名    : NAS_ERR_LOG_LAI_INFO_STRU
 结构说明  : 位置区信息的结构体
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    MNTN_PLMN_ID_STRU                   stPlmn;
    VOS_UINT32                          ulLac;
}NAS_ERR_LOG_LAI_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_CS_REG_RESULT_EVENT_STRU
 结构说明  : MM的LAU结果消息结构体
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;
    VOS_UINT32                          ulLuResult;                             /* LU结果            */
    NAS_ERR_LOG_NET_RAT_TYPE_ENUM_UINT8 enNetType;                              /* 当前注册的网络类型 */
    VOS_UINT8                           ucIsComBined;                           /* 是否为联合注册   */
    VOS_UINT16                          usRegFailCause;                         /* 操作失败原因     */
    VOS_UINT32                          ulServiceStatus;                        /* 服务状态          */
    VOS_UINT32                          ulCsUpdateStatus;                       /* CS 域更新状态     */
    VOS_UINT32                          ulLuAttemptCnt;                         /* LU Attempt counter */
    NAS_ERR_LOG_LAI_INFO_STRU           stOldLai;                               /* 旧LAI              */
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;                         /* 位置信息 */
    VOS_UINT8                           ucRegFailOriginalCause;                 /* 操作失败原因     */
    VOS_UINT8                           aucReserved[3];                         /* 保留域 */
}NAS_ERR_LOG_CS_REG_RESULT_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_PS_REG_RESULT_EVENT_STRU
 结构说明  : GMM的Attach/RAU结果消息结构体
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
 *******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                    stHeader;
    NAS_ERR_LOG_GMM_ACTION_TYPE_ENUM_U32      enGmmActionType;                  /* GMM的操作类型 */
    VOS_UINT32                                ulActionResult;                   /* 注册结果 */
    NAS_ERR_LOG_REG_DOMAIN_ENUM_UINT32        enReqDomain;                      /* 当前注册的结果域，Ps Only或CS_PS */
    NAS_ERR_LOG_REG_DOMAIN_ENUM_UINT32        enRsltDomain;                     /* 当前注册的结果域，Ps Only或CS_PS */
    VOS_UINT16                                usRegFailCause;                   /* 操作失败原因 */
    NAS_ERR_LOG_NET_RAT_TYPE_ENUM_UINT8       enNetType;                        /* 当前注册的网络类型 */
    VOS_UINT8                                 ucRegFailOriginalCause;                 /* 收到网络原始拒绝原因 */
    VOS_UINT32                                ulRegCounter;                     /* Attach attempt counter */
    VOS_UINT32                                ulServiceStatus;                  /* 服务状态 */
    NAS_MNTN_POSITION_INFO_STRU               stPositionInfo;                   /* 位置信息 */
}NAS_ERR_LOG_PS_REG_RESULT_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_PS_SRV_REG_RESULT_EVENT_STRU
 结构说明  : GMM的PS SERVICE 注册结果消息结构体
 1.日    期   : 2014年10月28日
   作    者   : n00269697
   修改内容   : 新建
 *******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                    stHeader;
    VOS_UINT32                                enActionResult;                   /* 操作的结果 */
    VOS_UINT16                                enRegFailCause;                   /* 操作失败原因 */
    VOS_UINT8                                 ucRegFailOriginalCause;           /* 收到网络原始拒绝原因 */
    VOS_UINT8                                 ucReserved;
    VOS_UINT32                                ulServiceSts;                     /* 服务状态 */
    NAS_MNTN_POSITION_INFO_STRU               stPositionInfo;                   /* 位置信息 */
}NAS_ERR_LOG_PS_SRV_REG_RESULT_EVENT_STRU;


/*****************************************************************************
 结构名    : NAS_ERR_LOG_MN_CALL_DISC_DIR_STRU
 结构说明  : 被叫号码结构体
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsUser;
    VOS_UINT8                           ucDiscCallFlag;
    VOS_UINT8                           aucReserved[2];
}NAS_ERR_LOG_MN_CALL_DISC_DIR_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_CS_CALL_FAIL_EVENT_STRU
 结构说明  : 呼叫掉话相关的消息结构体
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT8                                               ucCallId;           /* call id */
    NAS_ERR_LOG_CALL_STATE_ENUM_U8                          enCallState;        /* Call State */
    VOS_UINT8                                               enRat;
    VOS_UINT8                                               aucReserved[1];     /* 保留域 */
    NAS_ERR_LOG_MN_CALL_DISC_DIR_STRU                       stDiscDir;          /* 挂断电话的方向 */
    VOS_UINT32                                              ulCcCause;          /* 失败原因值 */
    NAS_MNTN_USIM_INFO_STRU                                 stUsimInfo;         /* 卡信息 */
    NAS_MNTN_POSITION_INFO_STRU                             stPositionInfo;     /* 位置信息 */
    VOS_UINT16                                              usCellDlFreq;       /*小区频点(下行)*/
    VOS_UINT16                                              usCellUlFreq;       /*当前频点(上行)*/
}NAS_ERR_LOG_CS_CALL_FAIL_EVENT_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_APS_FSM_CTX_STRU
 结构说明  : 状态机状态描述结构
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFsmId;                                /* 当前状态机标识 */
    VOS_UINT32                          ulState;                                /* 当前状态 */
}NAS_ERR_LOG_APS_FSM_CTX_STRU;

/*****************************************************************************
 结构名    : NAS_MNTN_APS_FSM_INFO_STRU
 结构说明  : APS状态机信息
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_ERR_LOG_APS_FSM_CTX_STRU        stMainFsm;                              /* 主状态机 */
    NAS_ERR_LOG_APS_FSM_CTX_STRU        stSubFsm;                               /* 子状态机 */
    VOS_UINT8                           ucPdpId;                                /* 当前状态机所对应的PDP ID */
    VOS_UINT8                           aucReserve[3];
}NAS_ERR_LOG_APS_PDP_ENTITY_FSM_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_PS_CALL_FAIL_EVENT_STRU
 结构说明  : PS域呼叫相关错误的消息结构体
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                      stHeader;
    NAS_MNTN_USIM_INFO_STRU                     stUsimInfo;                     /* 卡信息 */
    NAS_MNTN_POSITION_INFO_STRU                 stPositionInfo;                 /* 位置信息 */
    VOS_UINT32                                  ulPsRegState;                   /* PS注册状态 */
    NAS_ERR_LOG_APS_PDP_ENTITY_FSM_INFO_STRU    stApsFsmInfo;                   /* 状态机信息 */
    VOS_UINT32                                  ulPsCause;                      /* 失败原因 */
}NAS_ERR_LOG_PS_CALL_FAIL_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_SMS_MO_FAIL_EVENT_STRU
 结构说明  : 短信发送失败相关错误的消息结构体
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    NAS_MNTN_USIM_INFO_STRU                                 stUsimInfo;
    NAS_MNTN_POSITION_INFO_STRU                             stPositionInfo;
    NAS_MNTN_SMS_MO_INFO_STRU                               stMoFail;
    NAS_MNTN_SEND_DOMAIN_STATUS_ENUM_UINT32                 enCsStatus;
    NAS_MNTN_SEND_DOMAIN_STATUS_ENUM_UINT32                 enPsStatus;
}NAS_ERR_LOG_SMS_MO_FAIL_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_VC_FAILURE_EVENT_STRU
 结构说明  : VC模块相关错误的消息结构体
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    VOS_UINT32                              ulOptState;                         /* 操作类型 */
    VOS_UINT32                              ulCasue;                            /* 操作结果 */
    VOS_UINT32                              ulName;                             /* 消息名称 */
}NAS_ERR_LOG_VC_FAILURE_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_CS_PAGING_FAIL_EVENT_STRU
 结构说明  : 收到paging时的相关错误的消息结构体
 1.日    期   : 2014年09月16日
   作    者   : f00179208
   修改内容   : CS ERRLOG项目新增
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    NAS_MNTN_POSITION_INFO_STRU             stPositionInfo;                     /* 位置信息 */
    NAS_ERR_LOG_CS_PAGING_CAUSE_ENUM_U32    enCause;

    VOS_UINT8                               ucGMsIdType;                        /* TMSI or IMSI or PTMSI */
    VOS_UINT8                               ucGPagingType;                      /* CS or PS */
    VOS_UINT8                               aucReserve1[2];
    VOS_UINT32                              ulWCnDomainId;                      /* CS DOMAIN、PS DOMAIN、INVALID DOMAIN */
    VOS_UINT32                              ulWPagingType;                      /* 寻呼消息类型:paging type1、paging type2 */
    VOS_UINT32                              ulWPagingCause;                     /* paging原因值 */
    VOS_UINT32                              ulWPagingUeId;                      /* Paging Recorder Id */

    /* 参数的使用说明:
       1. 如果当前处于位置区更新则通过ucCurrProcType来判断
       2. 如果主叫建链过程中则通过ucCurrProcType,ucLastEstType来判断
       3. 如果被叫建链过程中则通过ucCurrProcType,ucLastEstType,ucLastPagingCause来判断
    */
    VOS_UINT8                               ucCurrMmState;                      /* MM的当前状态 */
    VOS_UINT8                               ucCurrProcType;                     /* MM的当前流程类型 */
    VOS_UINT8                               ucLastEstType;                      /* 最近一次的建链类型，MO OR MT */
    VOS_UINT8                               ucLastPagingCause;                  /* 最近一次的paging原因值 */
}NAS_ERR_LOG_CS_PAGING_FAIL_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_CS_MT_CALL_FAIL_EVENT_STRU
 结构说明  : CS MT时的相关错误的消息结构体
 1.日    期   : 2014年09月16日
   作    者   : f00179208
   修改内容   : CS ERRLOG项目新增
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    NAS_MNTN_POSITION_INFO_STRU             stPositionInfo;                     /* 位置信息 */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_ENUM_U32   enCause;
}NAS_ERR_LOG_CS_MT_CALL_FAIL_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_BAST_STATE_TO_CSFB_MT_STATE_STRU
 结构说明  : 基本状态转换为CSFB MT的过程状态结构
 1.日    期   : 2015年07月23日
   作    者   : f00179208
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    NAS_ERR_LOG_BASE_STATE_ENUM_U32     enBaseState;                            /* 基本过程状态 */
    NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32  enCsfbMtState;                          /* CSFB MT的过程状态 */
}NAS_ERR_LOG_BAST_STATE_TO_CSFB_MT_STATE_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_CSFB_MT_STATE_INFO_STRU
 结构说明  : CSFB MT时的过程状态信息结构
 1.日    期   : 2015年07月13日
   作    者   : f00179208
   修改内容   : 新增
*******************************************************************************/
typedef struct
{
    NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32  enCsfbMtState;                          /* 过程状态 */
    VOS_UINT32                          ulMmState;
    VOS_UINT32                          ulCause;                                /* 原因值 */
    VOS_UINT32                          ulTick;                                 /* 状态对应Tick */
}NAS_ERR_LOG_CSFB_MT_STATE_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_CSFB_MT_CALL_FAIL_EVENT_STRU
 结构说明  : CSFB MT时的相关错误的消息结构体
 1.日    期   : 2014年09月16日
   作    者   : f00179208
   修改内容   : CS ERRLOG项目新增
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32      enCurrState;                        /* 当前的过程状态 */
    VOS_UINT32                              ulPositionNum;
    NAS_MNTN_POSITION_INFO_STRU             stPositionInfo[NAS_ERR_LOG_MAX_POSITION_RECORD_NUM];
    VOS_UINT32                              ulStateNum;
    NAS_ERR_LOG_CSFB_MT_STATE_INFO_STRU     astStateInfo[NAS_ERR_LOG_MAX_CSFB_MT_STATE_RECORD_NUM];
}NAS_ERR_LOG_CSFB_MT_CALL_FAIL_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_MNTN_EVENT_STRU
 结构说明  : 故障告警的可维可测消息结构体
 1.日    期   : 2014年09月16日
   作    者   : f00179208
   修改内容   : CS ERRLOG项目新增
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    VOS_UINT32                              ulCount;                            /* 缓存区溢出计数 */
}NAS_ERR_LOG_MNTN_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_NW_DETACH_IND_EVENT_STRU
 结构说明  : 网络Detach指示的消息结构体
 1.日    期   : 2014年09月16日
   作    者   : f00179208
   修改内容   : CS ERRLOG项目新增
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    NAS_MNTN_POSITION_INFO_STRU             stPositionInfo;                     /* 位置信息 */
    VOS_UINT8                               ucDetachType;                       /* detach类型 */
    VOS_UINT8                               ucGmmCause;                         /* detach原因 */
    VOS_UINT8                               ucForceToStandby;
    VOS_UINT8                               ucCurrNetRat;
    VOS_UINT8                               ucOriginalGmmCause ;               /* 收到网络原始拒绝原因 */
    VOS_UINT8                               aucReserved[3];
}NAS_ERR_LOG_NW_DETACH_IND_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_CM_SRV_REJ_IND_EVENT_STRU
 结构说明  : CM SERVICE REJ的消息结构体
 1.日    期   : 2015年03月10日
   作    者   : f00179208
   修改内容   : 新建
 *******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;                         /* 位置信息 */
    VOS_UINT32                          ulCause;                                /* 失败原因                                 */
    VOS_UINT32                          ulServiceStatus ;                       /* 服务状态 */
    VOS_UINT8                           ucOriginalCause;                        /* 收到网络原始拒绝原因 */
    VOS_UINT8                           aucReserved[3];
}NAS_ERR_LOG_CM_SRV_REJ_IND_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_MO_DETACH_IND_EVENT_STRU
 结构说明  : 主动detach的消息结构体
 1.日    期   : 2015年03月10日
   作    者   : f00179208
   修改内容   : 新建
 *******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    NAS_MNTN_POSITION_INFO_STRU             stPositionInfo;                     /* 位置信息 */
    NAS_ERR_LOG_MO_DETACH_TYPE_ENUM_UINT32  enDetachType;                       /* detach类型 */
}NAS_ERR_LOG_MO_DETACH_IND_EVENT_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU
 结构说明  : RAT切换时需要记录的信息
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;
    VOS_UINT8                           ucRatType;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulSystemTick;
}NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_RAT_FREQUENTLY_SWITCH_EVENT_STRU
 结构说明  : 2G/3G/4G间频繁切换的消息结构体
 1.日    期   : 2015年03月10日
   作    者   : f00179208
   修改内容   : 新建
 *******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;
    NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU  astRatSwitchInfo[NAS_ERR_LOG_MAX_RAT_SWITCH_RECORD_MUN];/* RAT切换信息 */
    VOS_UINT32                          ulStatisticTime;                        /* 统计时间 */
    VOS_UINT32                          ulSwitchNum;                            /* 切换次数 */
}NAS_ERR_LOG_RAT_FREQUENTLY_SWITCH_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_OOS_EVENT_TO_OOS_CAUSE_STRU
 结构说明  : 无服务事件转换为无服务原因值
 1.日    期   : 2015年08月21日
   作    者   : f00179208
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32   enOosEvent;                             /* 丢网事件 */
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32   enOosCause;                             /* 丢网原因 */
}NAS_ERR_LOG_OOS_EVENT_TO_OOS_CAUSE_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_OOS_BEGIN_STRU
 结构说明  : 丢网开始的信息结构

 修改记录  :
 1.日    期   : 2015年08月11日
   作    者   : f00179208
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32   enOosCause;                             /* 丢网原因 */
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;                         /* 位置信息 */
    MNTN_PLMN_ID_STRU                   stHomePlmnId;                           /* HPLMN */
    NAS_ERR_LOG_OOS_DOMAIN_ENUM_UINT32  enLostDomain;                           /* 丢网域 */
    VOS_UINT16                          usGUTCellDlFreq;                        /* GUT的小区频点(下行) */
    VOS_UINT16                          usGUTCellUlFreq;                        /* GUT的当前频点(上行) */
    VOS_UINT32                          ulLteArfcn;                             /* LTE驻留频点信息 */
    VOS_UINT8                           ucRssiValue;                            /* 信号强度 */
    VOS_UINT8                           aucReserved[3];                         /* 保留域 */
}NAS_ERR_LOG_OOS_BEGIN_STRU;

/*****************************************************************************
 结构名    : NAS_INFO_CLT_OOS_INFO_STRU
 结构说明  : OOS状态下搜网信息结构

 修改记录  :
 1. 日    期   : 2015年12月1日
    作    者   : n00355355
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCurHistoryTimerCount;                         /* 当前History Timer次数 */
    VOS_UINT32                          ulCurPrefBandTimerCount;                        /* 当前PrefBand Timer次数 */
    VOS_UINT32                          ulCurFullBandTimerCount;                        /* 当前FullBand Timer次数 */
    VOS_UINT8                           ucCurOosPhaseNum;                               /* OOS搜网阶段 */
    VOS_UINT8                           aucReserved[3];
}NAS_INFO_CLT_OOS_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_ERR_LOG_OOS_NW_SRCH_PROC_INFO_STRU
 结构说明  : 丢网恢复过程记录信息

 修改记录  :
 1.日    期   : 2015年08月11日
   作    者   : f00179208
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    MNTN_PLMN_ID_STRU                       stPlmnId;                                       /* 搜索的PLMN */
    NAS_ERR_LOG_RATMODE_ENUM_UINT8          enSrchRat;                                      /* 搜索的接入技术 */
    VOS_UINT8                               ucSearchType;                                   /* 搜索的类型 */
    VOS_UINT8                               ucResult;                                       /* 搜索的结果 */
    VOS_UINT8                               ucCoverageType;                                 /* 覆盖类型 */
    VOS_UINT32                              ulPlmnSrchReqSlice;                             /* 请求时间戳 */
    VOS_UINT32                              ulCurPlmnSelectionScene;                        /* 当前的选网场景 */
    NAS_INFO_CLT_OOS_INFO_STRU              stOosInfo;                                      /* OOS搜网相关信息 */
    VOS_UINT8                               aucDplmnVersionId[NAS_INFO_VERSION_INFO_LEN];   /* Dplmn数据库版本号 */
    VOS_UINT8                               aucMccFreqVersion[NAS_INFO_VERSION_INFO_LEN];   /* 预置频点版本号 */
    VOS_UINT8                               aucReserved[2];
}NAS_ERR_LOG_OOS_NW_SRCH_PROC_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_OOS_END_STRU
 结构说明  : 丢网结束的信息结构

 修改记录  :
 1.日    期   : 2015年08月11日
   作    者   : f00179208
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;                         /* 位置信息 */
    NAS_ERR_LOG_OOS_DOMAIN_ENUM_UINT32  enResumeDomain;                         /* 恢复域 */
    VOS_UINT16                          usGUTCellDlFreq;                        /* GUT的小区频点(下行) */
    VOS_UINT16                          usGUTCellUlFreq;                        /* GUT的当前频点(上行) */
    VOS_UINT32                          ulLteArfcn;                             /* LTE驻留频点信息 */
    VOS_UINT8                           ucRssiValue;                            /* 信号强度 */
    VOS_UINT8                           ucReportFlag;                           /* 是否上报过丢网标记 */
    VOS_UINT8                           aucReserved[2];                         /* 保留域 */
}NAS_ERR_LOG_OOS_END_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_SRVCC_FAIL_CAUSE_ENUM
 结构说明  : SRVCC失败的原因枚举

 修改记录  :
 1.日    期   : 2015年12月5日
   作    者   : n00269697
   修改内容   : 新增

*****************************************************************************/
enum NAS_ERR_LOG_SRVCC_FAIL_CAUSE_ENUM
{
    NAS_ERR_LOG_SRVCC_FAIL_NULL                             = 0,
    NAS_ERR_LOG_SRVCC_FAIL_NO_CALL_NUM                      = 1,                /* bsrvcc时，IMSA会同步call num为0 */
    NAS_ERR_LOG_SRVCC_FAIL_RESUME_IND_BACK_TO_LTE           = 2,                /* SRVCC是handover失败，又回到LTE */
    NAS_ERR_LOG_SRVCC_FAIL_BUTT
};

typedef VOS_UINT8 NAS_ERR_LOG_SRVCC_FAIL_CAUSE_ENUM_UINT8;
/*****************************************************************************
 结构名    : NAS_ERR_LOG_SRVCC_FAIL_STRU
 结构说明  : SRVCC失败的信息结构

 修改记录  :
 1.日    期   : 2015年12月5日
   作    者   : n00269697
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    NAS_MNTN_POSITION_INFO_STRU                             stPositionInfo;     /* 位置信息 */
    NAS_ERR_LOG_SRVCC_FAIL_CAUSE_ENUM_UINT8                 enSrvccFailCause;   /* SRVCC失败原因 */
    VOS_UINT8                                               aucReserve[3];
}NAS_ERR_LOG_SRVCC_FAIL_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_CS_CALL_DISC_INFO_STRU
 结构说明  : 呼叫挂断的信息结构

 修改记录  :
 1.日    期   : 2015年09月17日
   作    者   : f00179208
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallId;                               /* call id */
    VOS_UINT8                           aucReserved[3];                         /* 保留域 */
    VOS_UINT32                          ulCause;                                /* 失败原因值 */
}NAS_ERR_LOG_CS_CALL_DISC_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_ID_RES_INFO_STRU
 结构说明  : 身份识别响应信息结构

 修改记录  :
 1.日    期   : 2015年09月17日
   作    者   : f00179208
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIDReqType;
    VOS_UINT8                           aucReserved[3];                         /* 保留域 */
}NAS_ERR_LOG_ID_RES_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_PROCESS_INFO_IND_EVENT_STRU
 结构说明  : 过程信息指示事件结构

 修改记录  :
 1.日    期   : 2015年09月17日
   作    者   : f00179208
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                      stHeader;
    NAS_ERR_LOG_PROCESS_INFO_TYPE_ENUM_UINT32   enInfoType;
    NAS_ERR_LOG_CS_CALL_DISC_INFO_STRU          stDiscInfo;
    NAS_ERR_LOG_ID_RES_INFO_STRU                stIDResInfo;
}NAS_ERR_LOG_PROCESS_INFO_IND_EVENT_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_MULTI_BAND_SCAN_PROC_INFO_STRU
 结构说明  : CSS Multi-Band SCAN过程记录信息

 修改记录  :
 1.日    期   : 2015年10月30日
   作    者   : h00279575
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                   ulBandScanStartSlice;   /* CSS Multi-Band SCAN的开始时间 */
    VOS_UINT32                   ulBandScanFinishSlice;  /* CSS Multi-Band SCAN的结束时间 */
    VOS_UINT8                    ucResult;                /* 扫描结果，如果没有扫到或者物理层异常时，携带的结果时失败 */
    VOS_UINT8                    ucGsmCoverageType;      /* 如果扫频请求中指示的是高能量搜索，上报的结果只有高能量覆盖或者无扫频结果 */
    VOS_UINT8                    ucUmtsFddCoverageType;  /* 同上*/
    VOS_UINT8                    ucLteCoverageType;      /* 同上*/
}NAS_ERR_LOG_MULTI_BAND_SCAN_PROC_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_FFT_SRCH_MCC_PROC_INFO_STRU
 结构说明  : 丢网恢复过程记录信息

 修改记录  :
 1.日    期   : 2015年10月30日
   作    者   : h00279575
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                      stHeader;
    VOS_UINT32                                  ulSrchStartSlice;       /* GET_GEO搜索MCC的开始时间点 */
    VOS_UINT32                                  ulSrchFinishSlice;      /* GET_GEO搜索MCC的结束时间点 */
    VOS_UINT8                                   ucSrchRslt;         /* Get_GEO找MCC的结果: VOS_TRUE-找到MCC; VOS_FALSE -没找到 */
    VOS_UINT8                                   ucFailCause;        /* Get_Geo没有找到MCC的原因.如果找到，此项值为0 */
    NAS_ERR_LOG_RATMODE_ENUM_UINT8              enMccRatType;       /* 搜索到MCC的接入技术 */
    VOS_UINT8                                   ucRsv;
    NAS_ERR_LOG_MULTI_BAND_SCAN_PROC_INFO_STRU  stMultiBandScanInfo;
}NAS_ERR_LOG_FFT_SRCH_MCC_PROC_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_FTM_TMSI_RPT_EVENT_STRU
 结构说明  : TMSI生成和更新后上报的消息结构体
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_FTM_HEADER_STRU                      stHeader;
    VOS_UINT8                               aucTmsi[NAS_FTM_MAX_TMSI_LEN];      /* tmsi的内容 */
}NAS_FTM_TMSI_RPT_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_FTM_PTMSI_RPT_EVENT_STRU
 结构说明  : PTMSI生成和更新后上报的消息结构体
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_FTM_HEADER_STRU                      stHeader;
    VOS_UINT8                               aucPtmsi[NAS_FTM_MAX_PTMSI_LEN];    /* ptmsi的内容 */
}NAS_FTM_PTMSI_RPT_EVENT_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_ALM_LEVEL_STRU
 结构说明  : Alm ID与log级别对应的结构体
 1.日    期   : 2013年08月12日
   作    者   : s00190137
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    NAS_ERR_LOG_ALM_ID_ENUM_U16             enAlmID;        /* 异常模块ID */
    VOS_UINT16                              usLogLevel;     /* 上报log等级 */
}NAS_ERR_LOG_ALM_LEVEL_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_ALM_REPORT_TYPE_STRU
 结构说明  : Alm ID与主动上报类型对应的结构体
 1.日    期   : 2015年07月06日
   作    者   : n00269697
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    NAS_ERR_LOG_ALM_ID_ENUM_U16                             enAlmID;            /* 异常模块ID */
    NAS_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_U16                 enReportType;       /* 上报log等级 */
}NAS_ERR_LOG_ALM_REPORT_TYPE_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_MNTN_PUT_BUF_INFO_STRU
 结构说明  : MM层ERRLOG故障告警发生时写环形缓存的勾包结构

 修改记录  :
 1.日    期   : 2013年09月10日
   作    者   : f00179208
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT8                           aucContent[4];                          /* 消息内容 */
}NAS_ERR_LOG_MNTN_PUT_BUF_INFO_STRU;

/******************************************************************************
结构名    : NAS_MNTN_SIM_STATUS_ENUM_UINT8
结构说明  : 卡状态
  1.日    期   : 2015年12月18日
    作    者   : s00217060
    修改内容   : 新建

******************************************************************************/
enum  NAS_MNTN_SIM_STATUS_ENUM
{
    NAS_MNTN_SIM_STATUS_UNVALID         = 0,                                    /* 初始化卡状态 */
    NAS_MNTN_SIM_STATUS_VALID           = 1,                                    /* 卡存在且CS/PS卡都有效 */
    NAS_MNTN_SIM_STATUS_CS_UNVALID      = 2,
    NAS_MNTN_SIM_STATUS_PS_UNVALID      = 3,
    NAS_MNTN_SIM_STATUS_CS_PS_UNVALID   = 4,
    NAS_MNTN_SIM_STATUS_SIM_PIN         = 5,                                    /* SIM卡服务由于PIN码原因不可用 */
    NAS_MNTN_SIM_STATUS_SIM_PUK         = 6,                                    /* SIM卡服务由于PUK码原因不可用 */
    NAS_MNTN_SIM_STATUS_NET_LCOK        = 7,                                    /* SIM卡服务由于网络锁定原因不可用 */
    NAS_MNTN_SIM_STATUS_IMSI_LCOK       = 8,                                    /* SIM卡服务由于IMSI锁定原因不可用 */
    NAS_MNTN_SIM_STATUS_READY_TIMEROUT  = 9,                                    /* 等待usim定时器超时原因不可用 */

    NAS_MNTN_SIM_STATUS_ROMSIM          = 240,
    NAS_MNTN_SIM_STATUS_NO_PRESENT      = 255,
    NAS_MNTN_SIM_STATUS_BUTT            = 254
};

typedef VOS_UINT8  NAS_MNTN_SIM_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MNTN_SIM_TYPE_ENUM_UINT8
 枚举说明  : 卡的类型
  1.日    期   : 2015年12月18日
    作    者   : s00217060
    修改内容   : 新建
*****************************************************************************/
enum NAS_MNTN_SIM_TYPE_ENUM
{
    NAS_MNTN_SIM_TYPE_SIM                ,                   /* SIM卡 */
    NAS_MNTN_SIM_TYPE_USIM               ,                   /* USIM卡 */
    NAS_MNTN_SIM_TYPE_ROM_SIM            ,
    NAS_MNTN_SIM_TYPE_UIM                ,                   /* UIM卡 */
    NAS_MNTN_SIM_TYPE_CSIM               ,                   /* CSIM卡 */
    NAS_MNTN_SIM_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MNTN_SIM_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_ERR_LOG_SIM_INFO
 枚举说明  : 卡相关的信息
  1.日    期   : 2015年12月18日
    作    者   : s00217060
    修改内容   : 新建
*****************************************************************************/

typedef struct
{
    NAS_MNTN_SIM_STATUS_ENUM_UINT8      enSimStatus;                            /* 卡状态 */
    NAS_MNTN_SIM_TYPE_ENUM_UINT8        enSimType;                              /* 卡类型 */
    VOS_UINT8                           aucRsv[2];
}NAS_ERR_LOG_SIM_INFO;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_GET_CARD_IMSI_FAIL_STRU
 结构说明  : 调用usim的API获取card imsi失败时的消息结构体
  1.日    期   : 2015年12月18日
    作    者   : s00217060
    修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;
    VOS_UINT32                          ulGetCardImsiRslt;                      /* 返回值 */
    VOS_UINT8                           aucImsi[NAS_MNTN_IMSI_LENGTH_IN_USIM];  /* IMSI号码 */
    VOS_UINT8                           aucReserve[3];
    NAS_ERR_LOG_SIM_INFO                stUsimInfo;
    NAS_ERR_LOG_SIM_INFO                stCsimInfo;
}NAS_ERR_LOG_GET_CARD_IMSI_FAIL_STRU;

/*****************************************************************************
 结构名    : NAS_INFO_CLT_GU_FREQ_INFO_STRU
 结构说明  : GU频点信息

 1.日    期   : 2015年07月08日
   作    者   : f00179208
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    NAS_INFO_CLT_BAND_IND_ENUM_UINT16   enBandInd;                              /* 频段指示 */
    VOS_UINT16                          usFreq;                                 /* 频点信息 */
}NAS_INFO_CLT_GU_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_INFO_CLT_LTE_FREQ_INFO_STRU
 结构说明  : LTE频点信息

 1.日    期   : 2015年07月08日
   作    者   : f00179208
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    NAS_INFO_CLT_BAND_IND_ENUM_UINT16   enBandInd;                              /* 频段指示 */
    VOS_UINT8                           aucRsv[2];                              /* 保留位 */
    VOS_UINT32                          ulFreq;                                 /* 频点信息 */
}NAS_INFO_CLT_LTE_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_INFO_CLT_GSM_FREQ_INFO_STRU
 结构说明  : GSM下的频点频段信息结构

 修改记录  :
 1.日    期   : 2015年07月08日
   作    者   : f00179208
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqNum;                              /* 频点数目 */
    VOS_UINT8                           aucRsv[2];                              /* 保留位 */
    MNTN_PLMN_ID_STRU                   stPlmnId;
    NAS_INFO_CLT_GU_FREQ_INFO_STRU      astFreqInfo[NAS_INFO_CLT_MAX_GSM_FREQ_NUM];  /* 频点信息列表 */
}NAS_INFO_CLT_GSM_FREQ_LIST_STRU;

/*****************************************************************************
 结构名    : NAS_INFO_CLT_WCDMA_FREQ_INFO_STRU
 结构说明  : WCDMA下的频点频段信息结构

 修改记录  :
 1.日    期   : 2015年07月08日
   作    者   : f00179208
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqNum;                              /* 频点数目 */
    VOS_UINT8                           aucRsv[2];                              /* 保留位 */
    MNTN_PLMN_ID_STRU                   stPlmnId;
    NAS_INFO_CLT_GU_FREQ_INFO_STRU      astFreqInfo[NAS_INFO_CLT_MAX_WCDMA_FREQ_NUM]; /* 频点信息列表 */
}NAS_INFO_CLT_WCDMA_FREQ_LIST_STRU;

/*****************************************************************************
 结构名    : NAS_INFO_CLT_LTE_FREQ_INFO_STRU
 结构说明  : LTE下的频点频段信息结构

 修改记录  :
 1.日    期   : 2015年07月08日
   作    者   : f00179208
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqNum;                              /* 频点数目 */
    VOS_UINT8                           aucRsv[2];                              /* 保留位 */
    MNTN_PLMN_ID_STRU                   stPlmnId;
    NAS_INFO_CLT_LTE_FREQ_INFO_STRU     astFreqInfo[NAS_INFO_CLT_MAX_LTE_FREQ_NUM];  /* 频点信息列表 */
}NAS_INFO_CLT_LTE_FREQ_LIST_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_CLOUD_BAND_INFO_STRU
 结构说明  : 云端频段搜集的信息结构

 修改记录  :
 1.日    期   : 2015年07月08日
   作    者   : f00179208
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    OM_INFO_CLT_HEADER_STRU             stHeader;
    MNTN_PLMN_ID_STRU                   stPlmn;                                 /* 当前驻留的PLMN */
    NAS_INFO_CLT_RATMODE_ENUM_UINT8     enNetMode;                              /* 当前注册的接入模式 */
    VOS_UINT8                           ucRac;                                  /* 路由区 */
    VOS_UINT16                          usLac;                                  /* 如果当前驻留是L则为TAC， 如果当前驻留是GU则为LAC*/
    VOS_UINT32                          ulCellId;                               /* 当前驻留的小区ID */
    NAS_INFO_CLT_GSM_FREQ_LIST_STRU     stGFreqList;
    NAS_INFO_CLT_WCDMA_FREQ_LIST_STRU   stWFreqList;
    NAS_INFO_CLT_LTE_FREQ_LIST_STRU     stLFreqList;
}NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU;


/*****************************************************************************
 结构名    : NAS_INFO_CLT_NETWORK_INFO_EVENT_STRU
 结构说明  : 网络信息采集信息

  1.日    期   : 2015年10月20日
    作    者   : 张义芳 z00328328
    修改内容   : 创建, for 上行发射功率收集
*****************************************************************************/
typedef struct
{
    OM_INFO_CLT_HEADER_STRU             stHeader;
    VOS_UINT16                          usCellid;        /* 小区id */
    VOS_UINT16                          usDlFreqInfo;    /* 下行频率 */
    VOS_UINT16                          usUlFreqInfo;    /* 上行频率 */
    VOS_UINT16                          usBandInfo;      /* BAND */
    VOS_INT16                           sRxPower;        /* Rxlev(GSM), RSCP(UMTS,TDS),Rsrp(LTE) */
    VOS_INT16                           sChanelQuality;   /* Rxqual(GSM), EcN0(UMTS), Scale(TDS),RsrQ(LTE) */
    VOS_UINT8                           ucIsExsitRrcConn;
    NAS_INFO_CLT_RATMODE_ENUM_UINT8     enNetMode;
    VOS_UINT8                           aucRsv[2];
    VOS_INT32                           lTxPwr;         /* 上行发射功率, 0.1dBm精度 */
    VOS_UINT32                          ulSavedSlice;    /* 当前上报时间 */
} NAS_INFO_CLT_NETWORK_INFO_EVENT_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
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

#endif /* end of NasErrorLog.h */


