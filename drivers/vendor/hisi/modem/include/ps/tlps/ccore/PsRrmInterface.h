/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : PsRrmInterface.h
  版 本 号   : 初稿
  作    者   : L00128652
  生成日期   : 2014年01月09日
  最近修改   :
  功能描述   : 协议栈与RRM之间接口文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年01月09日
    作    者   : L00128652
    修改内容   : 创建文件

 ******************************************************************************/

#ifndef __PSRRMINTERFACE_H__
#define __PSRRMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"

#if (VOS_OS_VER != VOS_WIN32)
#include  "vos_Id.h"
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
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*******************************************************************************
 枚举名    : PS_RRM_MSG_TYPE_ENUM_UINT32
 结构说明  : 消息枚举
 1.日    期   : 2014年01月09日
   作    者   : l00128652
   修改内容   : Added for DSDS
*******************************************************************************/
enum PS_RRM_MSG_TYPE_ENUM
{
    ID_PS_RRM_RADIO_RESOURCE_APPLY_REQ                          = 0x0001,       /* _H2ASN_MsgChoice PS_RRM_RADIO_RESOURCE_APPLY_REQ_STRU */
    ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF                          = 0x0002,       /* _H2ASN_MsgChoice RRM_PS_RADIO_RESOURCE_APPLY_CNF_STRU */

    ID_PS_RRM_RADIO_RESOURCE_RELEASE_IND                        = 0x0003,       /* _H2ASN_MsgChoice PS_RRM_RADIO_RESOURCE_RELEASE_IND_STRU */

    ID_RRM_PS_RADIO_RESOURCE_OCCUPY_REQ                         = 0x0004,       /* _H2ASN_MsgChoice RRM_PS_RADIO_RESOURCE_OCCUPY_REQ_STRU */
    ID_PS_RRM_RADIO_RESOURCE_OCCUPY_CNF                         = 0x0005,       /* _H2ASN_MsgChoice PS_RRM_RADIO_RESOURCE_OCCUPY_CNF_STRU */

    ID_PS_RRM_PROTECT_PS_IND                                    = 0x0006,       /* _H2ASN_MsgChoice PS_RRM_PROTECT_PS_IND_STRU */
    ID_PS_RRM_DEPROTECT_PS_IND                                  = 0x0007,       /* _H2ASN_MsgChoice PS_RRM_DEPROTECT_PS_IND_STRU */

    ID_PS_RRM_REGISTER_IND                                      = 0x0008,       /* _H2ASN_MsgChoice PS_RRM_REGISTER_IND_STRU */
    ID_PS_RRM_DEREGISTER_IND                                    = 0x0009,       /* _H2ASN_MsgChoice PS_RRM_DEREGISTER_IND_STRU */

    ID_RRM_PS_STATUS_IND                                        = 0x000a,       /* _H2ASN_MsgChoice RRM_PS_STATUS_IND_STRU */

    ID_RRM_PS_ERROR_IND                                         = 0x000b,       /* _H2ASN_MsgChoice RRM_PS_ERROR_IND_STRU */

    ID_RRM_PS_ABNORMAL_STATUS_IND                               = 0x000c,       /* _H2ASN_MsgChoice RRM_PS_ABNORMAL_STATUS_IND_STRU */

    ID_PS_RRM_PROTECT_SIGNAL_IND                                = 0x000d,       /* _H2ASN_MsgChoice PS_RRM_PROTECT_SIGNAL_IND_STRU */
    ID_PS_RRM_DEPROTECT_SIGNAL_IND                              = 0x000e,       /* _H2ASN_MsgChoice PS_RRM_DEPROTECT_SIGNAL_IND_STRU */

    ID_RRM_PS_USED_TASK_STATUS_IND                              = 0x000f,       /* _H2ASN_MsgChoice RRM_PS_USED_TASK_STATUS_IND_STRU */

    ID_PS_RRM_RAT_COMBINED_MODE_IND                             = 0x0010,       /* _H2ASN_MsgChoice PS_RRM_RAT_COMBINED_MODE_IND_STRU */
    ID_PS_RRM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 PS_RRM_MSG_TYPE_ENUM_UINT32;


/*******************************************************************************
 枚举名    : RRM_PS_URGENT_TYPE_ENUM_UINT8
 结构说明  : 抢占消息的紧急类型
 1.日    期   : 2014年03月28日
   作    者   : l00128652
   修改内容   : Added for DSDS
*******************************************************************************/
enum RRM_PS_URGENT_TYPE_ENUM
{
    RRM_PS_URGENT_TYPE_NO_URGENT                           = 0,                 /* 不紧急 */
    RRM_PS_URGENT_TYPE_SHORT_OCCUPY                        = 1,                 /* 短抢的紧急类型 */
    RRM_PS_URGENT_TYPE_URGENT                              = 2,                 /* 紧急类型 */
    RRM_PS_URGENT_TYPE_BUTT
};
typedef VOS_UINT8 RRM_PS_URGENT_TYPE_ENUM_UINT8;


/*******************************************************************************
 枚举名    : RRM_PS_TASK_TYPE_ENUM_UINT16
 结构说明  : 任务类型枚举
 1.日    期   : 2014年01月09日
   作    者   : l00128652
   修改内容   : Added for DSDS
备注说明  : 该枚举值跟RRM模块的g_astTaskTypeInfoTab表是一一对应关系，
            修改该枚举值时需要同步修改g_astTaskTypeInfoTab表
*******************************************************************************/
enum RRM_PS_TASK_TYPE_ENUM
{
    /* 初始状态无任务 */
    RRM_PS_TASK_TYPE_NONE                           = 0,

    /* 1-100用于定义NAS任务 */
    RRM_PS_TASK_TYPE_NAS_SEARCH                     = 1,

    /* 101-200用于定义GSM任务 */
    RRM_PS_TASK_TYPE_GSM_CS_NORMAL                  = 101,
    RRM_PS_TASK_TYPE_GSM_CS_MO_CALL                 = 102,
    RRM_PS_TASK_TYPE_GSM_CS_MT_CALL                 = 103,
    RRM_PS_TASK_TYPE_GSM_CS_EMERGENCY_CALL          = 104,
    RRM_PS_TASK_TYPE_GSM_CS_NAS_SESSION             = 105,
    RRM_PS_TASK_TYPE_GSM_ATTACH                     = 106,
    RRM_PS_TASK_TYPE_GSM_CS_DETACH                  = 107,
    RRM_PS_TASK_TYPE_GSM_LAU                        = 108,
    RRM_PS_TASK_TYPE_GSM_RAU                        = 109,
    RRM_PS_TASK_TYPE_GSM_SS                         = 110,
    RRM_PS_TASK_TYPE_GSM_SMS                        = 111,
    RRM_PS_TASK_TYPE_GSM_NAS_SPEC_SEARCH            = 112,
    RRM_PS_TASK_TYPE_GSM_NAS_LIST_SEARCH            = 113,
    RRM_PS_TASK_TYPE_GSM_AS_SEARCH                  = 114,
    RRM_PS_TASK_TYPE_GSM_PS_NORMAL                  = 115,
    RRM_PS_TASK_TYPE_GSM_PS_PAGE_RSP                = 116,
    RRM_PS_TASK_TYPE_GSM_PS_CELL_UPDT               = 117,
    RRM_PS_TASK_TYPE_GSM_PS_MM_PROC                 = 118,
    RRM_PS_TASK_TYPE_GSM_PS_DETACH                  = 119,
    RRM_PS_TASK_TYPE_GSM_NAS_FAST_SPEC_SEARCH       = 120,
    RRM_PS_TASK_TYPE_GSM_PS_SUBSCRIB_TRAFFIC_CALL   = 121,              /* PDP 激活任务 */

    /* 201-300用于定义WCDMA任务 */
    RRM_PS_TASK_TYPE_WCDMA_NAS_SPEC_SEARCH          = 201,
    RRM_PS_TASK_TYPE_WCDMA_NAS_LIST_SEARCH          = 202,
    RRM_PS_TASK_TYPE_WCDMA_AS_SEARCH                = 203,
    RRM_PS_TASK_TYPE_WCDMA_PS_RRC_NORMAL            = 204,
    RRM_PS_TASK_TYPE_WCDMA_CS_RRC_NORMAL            = 205,
    RRM_PS_TASK_TYPE_WCDMA_CS_RRC_HIGH              = 206,
    RRM_PS_TASK_TYPE_WCDMA_CS_MO_NORMAL_CALL        = 207,
    RRM_PS_TASK_TYPE_WCDMA_CS_MO_EMERGENCY_CALL     = 208,
    RRM_PS_TASK_TYPE_WCDMA_CS_MO_SS                 = 209,
    RRM_PS_TASK_TYPE_WCDMA_CS_MO_SMS                = 210,
    RRM_PS_TASK_TYPE_WCDMA_CS_MT_NORMAL_CALL        = 211,
    RRM_PS_TASK_TYPE_WCDMA_CS_MT_EMERGENCY_CALLBACK = 212,
    RRM_PS_TASK_TYPE_WCDMA_CS_MT_SS                 = 213,
    RRM_PS_TASK_TYPE_WCDMA_CS_MT_SMS                = 214,
    RRM_PS_TASK_TYPE_WCDMA_CS_LAU                   = 215,
    RRM_PS_TASK_TYPE_WCDMA_CS_DETACH                = 216,
    RRM_PS_TASK_TYPE_WCDMA_CS_MO_NORMAL_CSFB        = 217,
    RRM_PS_TASK_TYPE_WCDMA_CS_MO_EMERGENCY_CSFB     = 218,
    RRM_PS_TASK_TYPE_WCDMA_CS_MT_CSFB               = 219,
    RRM_PS_TASK_TYPE_WCDMA_PS_CONVERSAT_CALL        = 220,
    RRM_PS_TASK_TYPE_WCDMA_PS_STREAM_CALL           = 221,
    RRM_PS_TASK_TYPE_WCDMA_PS_INTERACT_CALL         = 222,
    RRM_PS_TASK_TYPE_WCDMA_PS_BACKGROUND_CALL       = 223,
    RRM_PS_TASK_TYPE_WCDMA_PS_SUBSCRIB_TRAFFIC_CALL = 224,
    RRM_PS_TASK_TYPE_WCDMA_PS_MO_SMS                = 225,
    RRM_PS_TASK_TYPE_WCDMA_PS_MT_SMS                = 226,
    RRM_PS_TASK_TYPE_WCDMA_PS_ATTACH                = 227,
    RRM_PS_TASK_TYPE_WCDMA_PS_RAU                   = 228,
    RRM_PS_TASK_TYPE_WCDMA_PS_DETACH                = 229,
    RRM_PS_TASK_TYPE_WCDMA_NAS_FAST_SPEC_SEARCH     = 230,

    /* 301-400用于定义TD-SCDMA任务 */
    RRM_PS_TASK_TYPE_TRRC_CS_PAGING                 = 301,
    RRM_PS_TASK_TYPE_TRRC_CS_CONNECTION             = 302,
    RRM_PS_TASK_TYPE_TRRC_PS_CONNECTION             = 303,
    RRM_PS_TASK_TYPE_TRRC_IRAT                      = 304,
    RRM_PS_TASK_TYPE_TDS_AS_SEARCH                  = 305,
    RRM_PS_TASK_TYPE_TDS_NAS_SPEC_SEARCH            = 306,
    RRM_PS_TASK_TYPE_TDS_NAS_FAST_SPEC_SEARCH       = 307,
    RRM_PS_TASK_TYPE_TDS_NAS_LIST_SEARCH            = 308,
    RRM_PS_TASK_TYPE_TDS_CS_MO_NORMAL_CALL          = 309,
    RRM_PS_TASK_TYPE_TDS_CS_MO_EMERGENCY_CALL       = 310,
    RRM_PS_TASK_TYPE_TDS_CS_MO_SS                   = 311,
    RRM_PS_TASK_TYPE_TDS_CS_MO_SMS                  = 312,
    RRM_PS_TASK_TYPE_TDS_CS_MT_NORMAL_CALL          = 313,
    RRM_PS_TASK_TYPE_TDS_CS_MT_EMERGENCY_CALLBACK   = 314,
    RRM_PS_TASK_TYPE_TDS_CS_MT_SS                   = 315,
    RRM_PS_TASK_TYPE_TDS_CS_MT_SMS                  = 316,
    RRM_PS_TASK_TYPE_TDS_CS_LAU                     = 317,
    RRM_PS_TASK_TYPE_TDS_CS_DETACH                  = 318,
    RRM_PS_TASK_TYPE_TDS_CS_MO_NORMAL_CSFB          = 319,
    RRM_PS_TASK_TYPE_TDS_CS_MO_EMERGENCY_CSFB       = 320,
    RRM_PS_TASK_TYPE_TDS_CS_MT_CSFB                 = 321,
    RRM_PS_TASK_TYPE_TDS_PS_CONVERSAT_CALL          = 322,
    RRM_PS_TASK_TYPE_TDS_PS_STREAM_CALL             = 323,
    RRM_PS_TASK_TYPE_TDS_PS_INTERACT_CALL           = 324,
    RRM_PS_TASK_TYPE_TDS_PS_BACKGROUND_CALL         = 325,
    RRM_PS_TASK_TYPE_TDS_PS_SUBSCRIB_TRAFFIC_CALL   = 326,
    RRM_PS_TASK_TYPE_TDS_PS_MO_SMS                  = 327,
    RRM_PS_TASK_TYPE_TDS_PS_MT_SMS                  = 328,
    RRM_PS_TASK_TYPE_TDS_PS_ATTACH                  = 329,
    RRM_PS_TASK_TYPE_TDS_PS_RAU                     = 330,
    RRM_PS_TASK_TYPE_TDS_PS_DETACH                  = 331,

    /* 401-500用于定义LTE任务 */
    RRM_PS_TASK_TYPE_LRRC_PS_PAGING                 = 401,
    RRM_PS_TASK_TYPE_LRRC_PS_CONNECTION             = 402,
    RRM_PS_TASK_TYPE_LRRC_IRAT                      = 403,
    RRM_PS_TASK_TYPE_LRRC_ETWS                      = 404,
    RRM_PS_TASK_TYPE_LRRC_CMAS                      = 405,
    RRM_PS_TASK_TYPE_LTE_AS_SEARCH                  = 406,
    RRM_PS_TASK_TYPE_LTE_NAS_SPEC_SEARCH            = 407,
    RRM_PS_TASK_TYPE_LTE_NAS_FAST_SPEC_SEARCH       = 408,
    RRM_PS_TASK_TYPE_LTE_NAS_LIST_SEARCH            = 409,
    RRM_PS_TASK_TYPE_LTE_MO_NORMAL_CALL             = 410,
    RRM_PS_TASK_TYPE_LTE_MT_NORMAL_CALL             = 411,
    RRM_PS_TASK_TYPE_LTE_MO_EMERGENCY_CALL          = 412,
    RRM_PS_TASK_TYPE_LTE_PS_MO_SS                   = 413,
    RRM_PS_TASK_TYPE_LTE_PS_MT_SS                   = 414,
    RRM_PS_TASK_TYPE_LTE_CS_MO_NORMAL_CSFB          = 415,
    RRM_PS_TASK_TYPE_LTE_CS_MO_EMERGENCY_CSFB       = 416,
    RRM_PS_TASK_TYPE_LTE_CS_MT_CSFB                 = 417,
    RRM_PS_TASK_TYPE_LTE_PS_CONVERSAT_CALL          = 418,
    RRM_PS_TASK_TYPE_LTE_PS_STREAM_CALL             = 419,
    RRM_PS_TASK_TYPE_LTE_PS_INTERACT_CALL           = 420,
    RRM_PS_TASK_TYPE_LTE_PS_BACKGROUND_CALL         = 421,
    RRM_PS_TASK_TYPE_LTE_PS_SUBSCRIB_TRAFFIC_CALL   = 422,
    RRM_PS_TASK_TYPE_LTE_PS_MO_SMS                  = 423,
    RRM_PS_TASK_TYPE_LTE_PS_MT_SMS                  = 424,
    RRM_PS_TASK_TYPE_LTE_PS_ATTACH                  = 425,
    RRM_PS_TASK_TYPE_LTE_PS_LOW_TAU                 = 426,
    RRM_PS_TASK_TYPE_LTE_PS_HIGH_TAU                = 427,
    RRM_PS_TASK_TYPE_LTE_PS_DETACH                  = 428,
    RRM_PS_TASK_TYPE_LTE_PS_ESM                     = 429,
    RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL         = 430,
    RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL         = 431,
    RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL         = 432,
    RRM_PS_TASK_TYPE_LTE_IMS_MO_SS                  = 433,
    RRM_PS_TASK_TYPE_LTE_IMS_MT_SS                  = 434,
    RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS                 = 435,
    RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS                 = 436,
    RRM_PS_TASK_TYPE_LTE_IMS_REGISTER               = 437,
    RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER             = 438,

    /* 501-600用于定义1x,HRPD任务 */
    RRM_PS_TASK_TYPE_1X_NETWORK_SEARCH              = 501,
    RRM_PS_TASK_TYPE_1X_REGISTER                    = 502,
    RRM_PS_TASK_TYPE_1X_CS_CALL                     = 503,
    RRM_PS_TASK_TYPE_1X_PS_CALL                     = 504,
    RRM_PS_TASK_TYPE_1X_SIGNAL                      = 505,
    RRM_PS_TASK_TYPE_1X_SMS                         = 506,
    RRM_PS_TASK_TYPE_1X_TCH_REL_NETWORK_SEARCH      = 507,

    RRM_PS_TASK_TYPE_HRPD_NETWORK_SEARCH            = 521,
    RRM_PS_TASK_TYPE_HRPD_PS_NORMAL                 = 522,
    RRM_PS_TASK_TYPE_HRPD_LU                        = 523,
    RRM_PS_TASK_TYPE_HRPD_UATI                      = 524,
    RRM_PS_TASK_TYPE_HRPD_SESSION_CLOSE             = 525,
    RRM_PS_TASK_TYPE_HRPD_ATTACH                    = 526,
    RRM_PS_TASK_TYPE_HRPD_PDN_CONN                  = 527,
    RRM_PS_TASK_TYPE_HRPD_PDN_DISCONN               = 528,
    RRM_PS_TASK_TYPE_HRPD_DETACH                    = 529,
    RRM_PS_TASK_TYPE_HRPD_SESSION_NEG               = 530,
    RRM_PS_TASK_TYPE_HRPD_PS_CONNECTION             = 531,
    RRM_PS_TASK_TYPE_HRPD_SIGNAL                    = 532,
    RRM_PS_TASK_TYPE_HRPD_MO_KEEP_ALIVE             = 533,
    RRM_PS_TASK_TYPE_HRPD_MT_KEEP_ALIVE             = 534,
    RRM_PS_TASK_TYPE_HRPD_HARD_ID                   = 535,

    RRM_PS_TASK_TYPE_BUTT
};
typedef VOS_UINT16 RRM_PS_TASK_TYPE_ENUM_UINT16;

/*******************************************************************************
 枚举名    : PS_RRM_RESULT_ENUM_UINT8
 结构说明  : 申请的结果
 1.日    期   : 2014年01月09日
   作    者   : w00101153
   修改内容   : Added for DSDS
*******************************************************************************/
enum PS_RRM_RESULT_ENUM
{
    PS_RRM_RESULT_SUCCESS               = 0,
    PS_RRM_RESULT_FAIL_OTHER_ERROR      = 1,
    PS_RRM_RESULT_BUTT
};
typedef VOS_UINT8 PS_RRM_RESULT_ENUM_UINT8;


/*******************************************************************************
 枚举名    : RRM_PS_CHECK_MSG_RESULT_UINT8
 结构说明  : RRM检查MSG消息结果
 1.日    期   : 2014年02月25日
   作    者   : h00163499
   修改内容   : Added for DSDS
*******************************************************************************/
enum RRM_PS_CHECK_MSG_RESULT_ENUM
{
    RRM_PS_CHECK_MSG_RESULT_OK                       = 0,
    RRM_PS_CHECK_MSG_RESULT_DSDS_NOT_SUPPORT_ERROR   = 1,
    RRM_PS_CHECK_MSG_RESULT_PARA_ERROR               = 2,
    RRM_PS_CHECK_MSG_RESULT_RESOURCE_VALUE_ERROR     = 3,
    RRM_PS_CHECK_MSG_RESULT_BUTT
};
typedef VOS_UINT8 RRM_PS_CHECK_MSG_RESULT_ENUM_UINT8;

/*******************************************************************************
 枚举名    : PS_RRM_SIGNAL_READY_ENUM_UINT8
 结构说明  : 资源不可抢占回复结果
 1.日    期   : 2014年06月24日
   作    者   : g00260269
   修改内容   : Added for DSDS
*******************************************************************************/
enum PS_RRM_SIGNAL_READY_ENUM
{
    PS_RRM_SIGNAL_NOT_READY         = 0,
    PS_RRM_SIGNAL_READY             = 1,
    PS_RRM_SIGNAL_DSDS_NOT_SUPPROT  = 2,
    PS_RRM_SIGNAL_READY_BUTT
};
typedef VOS_UINT8 PS_RRM_SIGNAL_READY_ENUM_UINT8;

/*******************************************************************************
 枚举名    : PS_RRM_RF_SHARED_ENUM_UINT8
 结构说明  : 资源是否可争用结果
 1.日    期   : 2014年06月24日
   作    者   : g00260269
   修改内容   : Added for DSDS
*******************************************************************************/
enum PS_RRM_RF_SHARED_ENUM
{
    PS_RRM_RF_NOT_SHARED                = 0,
    PS_RRM_RF_SHARED                    = 1,
    PS_RRM_RF_SHARED_DSDS_NOT_SUPPROT   = 2,
    PS_RRM_RF_SHARED_BUTT
};
typedef VOS_UINT8 PS_RRM_RF_SHARED_ENUM_UINT8;

/*******************************************************************************
 枚举名    : PS_RRM_RF_AVAILABLE_ENUM_UINT8
 结构说明  : 资源是否可用结果
 1.日    期   : 2014年06月24日
   作    者   : g00260269
   修改内容   : Added for DSDS
*******************************************************************************/
enum PS_RRM_RF_AVAILABLE_ENUM
{
    PS_RRM_RF_NOT_AVAILABLE                 = 0,
    PS_RRM_RF_AVAILABLE                     = 1,
    PS_RRM_RF_AVAILABLE_DSDS_NOT_SUPPROT    = 2,
    PS_RRM_RF_AVAILABLE_BUTT
};
typedef VOS_UINT8 PS_RRM_RF_AVAILABLE_ENUM_UINT8;

/*******************************************************************************
 枚举名    : PS_RRM_RF_AVAILABLE_ENUM_UINT8
 结构说明  : 资源申请前试探结果
 1.日    期   : 2014年06月24日
   作    者   : g00260269
   修改内容   : Added for DSDS
*******************************************************************************/
enum PS_RRM_IS_PREEMPTED_ENUM
{
    PS_RRM_NOT_PREEMPTED                = 0,
    PS_RRM_COULD_PREEMPTED              = 1,
    PS_RRM_PREEMPTED_DSDS_NOT_SUPPROT   = 2,
    PS_RRM_PREEMPTED_BUTT
};
typedef VOS_UINT8 PS_RRM_IS_PREEMPTED_ENUM_UINT8;

/*******************************************************************************
 枚举名    : PS_RRM_RAT_COMBINED_MODE_ENUM
 结构说明  : 系统组合模式定义
 1.日    期   : 2015年06月17日
   作    者   : s00246516
   修改内容   : Added for DSDS
*******************************************************************************/
enum PS_RRM_RAT_COMBINED_MODE_ENUM
{
    PS_RRM_RAT_COMBINED_MODE_CL                 = 0, /* 当前支持1X或者EVDO */
    PS_RRM_RAT_COMBINED_MODE_GUL                = 1, /* 当前支持GUL,包含仅支持LTE的情况 */
    PS_RRM_RAT_COMBINED_MODE_BUTT
};
typedef VOS_UINT8 PS_RRM_RAT_COMBINED_MODE_ENUM_UINT8;


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
 结构名    : PS_RRM_RADIO_RESOURCE_APPLY_REQ_STRU
 结构说明  : PS发给RRM指示资源申请
 1.日    期   : 2014年01月09日
   作    者   : l00128652
   修改内容   : Added for DSDS
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头 */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16 enModemId; */
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType;
    VOS_RATMODE_ENUM_UINT32             enRatType;          /* 需要使用射频资源的模式，如果是异系统互操作，填写目标模式 */ /* _H2ASN_Replace VOS_UINT32 enRatType; */
}PS_RRM_RADIO_RESOURCE_APPLY_REQ_STRU;

/*******************************************************************************
 结构名    : RRM_PS_RADIO_RESOURCE_APPLY_CNF_STRU
 结构说明  : RRM发给PS指示资源申请结果
 1.日    期   : 2014年01月09日
   作    者   : l00128652
   修改内容   : Added for DSDS
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                    stMsgHeader;         /* 消息头 */ /*_H2ASN_Skip*/
    RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType;
    PS_RRM_RESULT_ENUM_UINT8           enResult;
    VOS_UINT8                          aucReserved[1];
} RRM_PS_RADIO_RESOURCE_APPLY_CNF_STRU;

/*******************************************************************************
 结构名    : PS_RRM_RADIO_RESOURCE_RELEASE_IND_STRU
 结构说明  : PS发给RRM指示资源释放
 1.日    期   : 2014年01月09日
   作    者   : l00128652
   修改内容   : Added for DSDS
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头 */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16 enModemId; */
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType;         /* 释放的任务资源类型 */
    PS_BOOL_ENUM_UINT8                  enRelAllFlag;       /* 释放本PID下所有申请的资源类型 */
    VOS_UINT8                           aucReserved[3];
    VOS_RATMODE_ENUM_UINT32             enRatType;          /* 释放射频资源的模式，如果是异系统互操作，填写目标模式 */ /* _H2ASN_Replace VOS_UINT32 enRatType; */
    VOS_UINT32                          ulRelDelaytimer;    /* 延迟释放射频资源的时间，单位:ms,
                                                               不延迟时该值设置为0，最大延迟值为10000ms(10s),
                                                               只针对具体任务，且当前资源正在被该任务使用，释放资源时该延迟时间才生效，
                                                               如果enRelAllFlag = PS_TRUE生效， 该延迟时间不生效 */
}PS_RRM_RADIO_RESOURCE_RELEASE_IND_STRU;

/*******************************************************************************
 结构名    : RRM_PS_RADIO_RESOURCE_OCCUPY_REQ_STRU
 结构说明  : RRM发给PS指示资源抢占
 1.日    期   : 2014年01月09日
   作    者   : l00128652
   修改内容   : Added for DSDS
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头 */ /*_H2ASN_Skip*/
    RRM_PS_URGENT_TYPE_ENUM_UINT8       enUrgentType;       /* 抢占的紧急类型 */
    VOS_UINT8                           aucReserved[3];
} RRM_PS_RADIO_RESOURCE_OCCUPY_REQ_STRU;

/*******************************************************************************
 结构名    : PS_RRM_RADIO_RESOURCE_OCCUPY_CNF_STRU
 结构说明  : PS发给RRM指示资源抢占结果
 1.日    期   : 2014年01月09日
   作    者   : l00128652
   修改内容   : Added for DSDS
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserved[4];
} PS_RRM_RADIO_RESOURCE_OCCUPY_CNF_STRU;

/*******************************************************************************
 结构名    : PS_RRM_PROTECT_PS_IND_STRU
 结构说明  : PS发给RRM指示PS业务需要保护
 1.日    期   : 2014年01月09日
   作    者   : l00128652
   修改内容   : Added for DSDS
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头 */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16 enModemId; */
    VOS_UINT8                           aucReserved[2];
} PS_RRM_PROTECT_PS_IND_STRU;

/*******************************************************************************
 结构名    : PS_RRM_DEPROTECT_PS_IND_STRU
 结构说明  : PS发给RRM指示PS业务去保护
 1.日    期   : 2014年01月09日
   作    者   : l00128652
   修改内容   : Added for DSDS
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头 */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16 enModemId; */
    VOS_UINT8                           aucReserved[2];
} PS_RRM_DEPROTECT_PS_IND_STRU;

/*******************************************************************************
 结构名    : PS_RRM_REGISTER_IND_STRU
 结构说明  : PS发给RRM指示注册某种类型的业务通知消息
 1.日    期   : 2014年01月09日
   作    者   : l00128652
   修改内容   : Added for DSDS
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头 */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16 enModemId; */
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType;         /* 有效任务则注册 */
    VOS_RATMODE_ENUM_UINT32             enRatType;          /* _H2ASN_Replace VOS_UINT32 enRatType; */
} PS_RRM_REGISTER_IND_STRU;

/*******************************************************************************
 结构名    : PS_RRM_DEREGISTER_IND_STRU
 结构说明  : PS发给RRM指示去注册某种类型的业务通知消息
 1.日    期   : 2014年01月09日
   作    者   : l00128652
   修改内容   : Added for DSDS
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头 */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16 enModemId; */
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType;         /* 有效任务去注册 */
    VOS_RATMODE_ENUM_UINT32             enRatType;          /* _H2ASN_Replace VOS_UINT32 enRatType; */
} PS_RRM_DEREGISTER_IND_STRU;


/*******************************************************************************
 结构名    : RRM_PS_STATUS_IND_STRU
 结构说明  : RRM通知PS当前的状态，针对任务进行通知
 1.日    期   : 2014年01月09日
   作    者   : l00128652
   修改内容   : Added for DSDS
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头 */ /*_H2ASN_Skip*/
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType;
    VOS_UINT8                           aucReserved[2];
    VOS_RATMODE_ENUM_UINT32             enRatType;          /* _H2ASN_Replace VOS_UINT32 enRatType; */
} RRM_PS_STATUS_IND_STRU;


/*******************************************************************************
 结构名    : RRM_PS_ERR_IND_STRU
 结构说明  : RRM发给PS指示错误信息
 1.日    期   : 2014年02月25日
   作    者   : h00163499
   修改内容   : Added for DSDS
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头 */ /*_H2ASN_Skip*/
    RRM_PS_CHECK_MSG_RESULT_ENUM_UINT8  enCheckMsgRlst;
    VOS_UINT8                           aucReserved[3];
} RRM_PS_ERROR_IND_STRU;


/*******************************************************************************
 结构名    : RRM_PS_ABNORMAL_STATUS_IND_STRU
 结构说明  : RRM发给PS指示异常状态指示
 1.日    期   : 2014年04月22日
   作    者   : h00163499
   修改内容   : Added for DSDS
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserved[4];
} RRM_PS_ABNORMAL_STATUS_IND_STRU;


/*******************************************************************************
 结构名    : PS_RRM_PROTECT_SIGNAL_IND_STRU
 结构说明  : PS发给RRM指示SIGNAL业务需要保护
 1.日    期   : 2014年06月23日
   作    者   : h00163499
   修改内容   : Added for DSDS
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头 */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16 enModemId; */
    VOS_UINT8                           aucReserved[2];
    VOS_RATMODE_ENUM_UINT32             enRatType;          /* 需要使用射频资源的模式，如果是异系统互操作，填写目标模式 */ /* _H2ASN_Replace VOS_UINT32 enRatType; */
} PS_RRM_PROTECT_SIGNAL_IND_STRU;


/*******************************************************************************
 结构名    : PS_RRM_DEPROTECT_SIGNAL_IND_STRU
 结构说明  : PS发给RRM指示SIGNAL业务需要去保护
 1.日    期   : 2014年06月23日
   作    者   : h00163499
   修改内容   : Added for DSDS
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;         /* 消息头 */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;           /* _H2ASN_Replace VOS_UINT16 enModemId; */
    VOS_UINT8                           aucReserved[2];
    VOS_RATMODE_ENUM_UINT32             enRatType;           /* 需要使用射频资源的模式，如果是异系统互操作，填写目标模式 */ /* _H2ASN_Replace VOS_UINT32 enRatType; */
} PS_RRM_DEPROTECT_SIGNAL_IND_STRU;

/*******************************************************************************
 结构名    : RRM_PS_USED_TASK_STATUS_IND_STRU
 结构说明  : RRM通知PS当前正在使用资源的任务状态

 1.日    期   : 2015年01月15日
   作    者   : y00142674
   修改内容   : Added for DSDS

*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头 */ /*_H2ASN_Skip*/
    PS_BOOL_ENUM_UINT8                  enResourceUsedFlag; /* 资源是否正在使用 */
    PS_BOOL_ENUM_UINT8                  enNotStealFlag;     /* 当前正在使用资源的任务中是否存在不允许偷帧的任务 */
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16 enModemId; */
} RRM_PS_USED_TASK_STATUS_IND_STRU;

/*******************************************************************************
 结构名    : PS_RRM_RAT_COMBINED_MODE_IND_STRU
 结构说明  : 通知RRM当前系统组合模式结构体

 1.日    期   : 2015年06月17日
   作    者   : s00246516
   修改内容   : Added for DSDS

*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头 */ /*_H2ASN_Skip*/
    PS_RRM_RAT_COMBINED_MODE_ENUM_UINT8 enRatCombMode;
    VOS_UINT8                           aucReserved[1];
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16 enModemId; */
} PS_RRM_RAT_COMBINED_MODE_IND_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/

/*****************************************************************************
 结构名    : PS_RRM_MSG_DATA
 协议表格  :
 ASN.1描述 :
 结构说明  : PS_RRM_MSG_DATA数据结构，用于生成ASN文件
*****************************************************************************/
typedef struct
{
    PS_RRM_MSG_TYPE_ENUM_UINT32         enMsgId;            /*_H2ASN_MsgChoice_Export PS_RRM_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          PS_RRM_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}PS_RRM_MSG_DATA;

/*_H2ASN_Length UINT32*/

/*****************************************************************************
 结构名    : PsRrmInterface_MSG
 协议表格  :
 ASN.1描述 :
 结构说明  : PsRrmInterface_MSG数据结构,用于生成ASN文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    PS_RRM_MSG_DATA                     stMsgData;
}PsRrmInterface_MSG;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
/* 设置资源不可被抢占 */
extern PS_RRM_SIGNAL_READY_ENUM_UINT8 RRM_DisableRfResourceOccupy
(
   VOS_UINT32                           ulPidValue,
   MODEM_ID_ENUM_UINT16                 enModemId,
   VOS_RATMODE_ENUM_UINT32              enRatType
);

/* 设置资源可以被抢占 */
extern VOS_VOID RRM_EnableRfResourceOccupy
(
   VOS_UINT32                           ulPidValue,
   MODEM_ID_ENUM_UINT16                 enModemId,
   VOS_RATMODE_ENUM_UINT32              enRatType
);


/* 资源是否可用 */
extern PS_RRM_RF_AVAILABLE_ENUM_UINT8 RRM_RfResourceIsAvailable
(
   MODEM_ID_ENUM_UINT16                 enModemId,
   VOS_RATMODE_ENUM_UINT32              enRatType,
   VOS_UINT32                          *pulStartingTimer
);


/* 试探下看资源是否可得到 */
extern PS_RRM_IS_PREEMPTED_ENUM_UINT8 RRM_RfResourceIsPreempted
(
   MODEM_ID_ENUM_UINT16                 enModemId,
   VOS_RATMODE_ENUM_UINT32              enRatType,
   RRM_PS_TASK_TYPE_ENUM_UINT16         enTaskType
);


/* 资源是否是共享的 */
extern PS_RRM_RF_SHARED_ENUM_UINT8 RRM_RfResourceIsShared
(
   MODEM_ID_ENUM_UINT16                 enModemId,
   VOS_RATMODE_ENUM_UINT32              enRatType
);

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/
//#endif




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

#endif /* end of PsRrmInterface.h */


