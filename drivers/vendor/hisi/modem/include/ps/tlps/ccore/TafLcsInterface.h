/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafLcsInterface.h
  版 本 号   : 初稿
  作    者   : l00198894
  生成日期   : 2015年9月14日
  最近修改   :
  功能描述   : TafLcsInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年9月14日
    作    者   : l00198894
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFLCSINTERFACE_H__
#define __TAFLCSINTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "LcsCommInterface.h"
#include "LocCommonInterface.h"
#include "PsTypeDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_LCS_MSG_ID_BASE             0x0
#define LCS_TAF_MSG_ID_BASE             0x100

/* TAF和LCS之前原因值分段 */
#define TAF_LCS_CAUSE_INTER_ERR_BEGIN   0x00010000
#define TAF_LCS_CAUSE_INTER_ERR_END     0x0001FFFF
#define TAF_LCS_CAUSE_NW_SECTION_BEGIN  0x00020000
#define TAF_LCS_CAUSE_NW_SECTION_END    0x0002FFFF
#define TAF_LCS_CAUSE_MM_ERR_BEGIN      0x00030000
#define TAF_LCS_CAUSE_MM_ERR_END        0x0003FFFF
#define TAF_LCS_CAUSE_LMM_ERR_BEGIN     0x00040000
#define TAF_LCS_CAUSE_LMM_ERR_END       0x0004FFFF

/* MM原因值内部偏移,后16位与NAS_MMCM_REL_CAUSE_ENUM_UINT32中分段一致 */
#define TAF_LCS_CAUSE_MM_CM_SRV_REJ_BEGIN                (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x100)
#define TAF_LCS_CAUSE_MM_CM_SRV_REJ_END                  (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x1FF)
#define TAF_LCS_CAUSE_MM_CSFB_SRV_REJ_BEGIN              (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x200)
#define TAF_LCS_CAUSE_MM_CSFB_SRV_REJ_END                (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x2FF)
#define TAF_LCS_CAUSE_MM_SMS_CP_ERR_BEGIN                (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x300)
#define TAF_LCS_CAUSE_MM_SMS_CP_ERR_END                  (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x3FF)
#define TAF_LCS_CAUSE_MM_SMS_RP_ERR_BEGIN                (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x400)
#define TAF_LCS_CAUSE_MM_SMS_RP_ERR_END                  (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x4FF)
#define TAF_LCS_CAUSE_MM_SS_NW_REJ_BEGIN                 (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x500)
#define TAF_LCS_CAUSE_MM_SS_NW_REJ_END                   (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x5FF)
#define TAF_LCS_CAUSE_MM_RR_CONN_FAIL_BEGIN              (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x600)
#define TAF_LCS_CAUSE_MM_RR_CONN_FAIL_END                (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x6FF)
#define TAF_LCS_CAUSE_MM_RR_REL_BEGIN                    (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x700)
#define TAF_LCS_CAUSE_MM_RR_REL_END                      (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x7FF)
#define TAF_LCS_CAUSE_MM_CSFB_LMM_FAIL_BEGIN             (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x800)
#define TAF_LCS_CAUSE_MM_CSFB_LMM_FAIL_END               (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x8FF)
#define TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN              (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x900)
#define TAF_LCS_CAUSE_MM_MM_INTER_ERR_END                (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x9FF)

/* 网络原因值偏移, 后16位与网络原因值内部分段一致 */
#define TAF_LCS_CAUSE_NW_ERROR_BEGIN                     (TAF_LCS_CAUSE_NW_SECTION_BEGIN + 0x200)
#define TAF_LCS_NW_CAUSE_GENERAL_REJ_BEGIN               (TAF_LCS_CAUSE_NW_SECTION_BEGIN + 0x8000)
#define TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN                (TAF_LCS_CAUSE_NW_SECTION_BEGIN + 0x8100)
#define TAF_LCS_NW_CAUSE_RTRN_RSLT_REJ_BEGIN             (TAF_LCS_CAUSE_NW_SECTION_BEGIN + 0x8200)
#define TAF_LCS_NW_CAUSE_RTRN_ERR_REJ_BEGIN              (TAF_LCS_CAUSE_NW_SECTION_BEGIN + 0x8300)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*******************************************************************************
 枚举名    : TAF_LCS_CAUSE_ENUM
 结构说明  : LCS原因值类型枚举
  1.日    期   : 2015年8月25日
    作    者   : l00198894
    修改内容   : 新增枚举
*******************************************************************************/
enum TAF_LCS_CAUSE_ENUM
{
    TAF_LCS_CAUSE_SUCCESS                           = 0,

    /* 内部错误 */
    TAF_LCS_CAUSE_LCS_NOT_SUPPORT                                      = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 0),     /* MO-LR中一些命令LCS不支持 */
    TAF_LCS_CAUSE_LCS_USER_TIMER_OUT                                   = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 1),     /* LCS等待用戶回复保护定时器超时 */
    TAF_LCS_CAUSE_LCS_NW_TIMER_OUT                                     = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 2),     /* LCS等待网络回复保护定时器超时 */
    TAF_LCS_CASUE_MSG_PARA_INVAILD                                     = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 3),     /* TAF发给LCS消息内容无效 */
    TAF_LCS_CAUSE_MO_LR_ALREADY_EXISTED                                = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 4),     /* 正在MO-LR流程 */
    TAF_LCS_CAUSE_TAF_MOLR_DISABLE                                     = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 5),     /* 用户DIABLE MO-LR */
    TAF_LCS_CAUSE_EXIST_VOLTE_SER                                      = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 6),     /* 存在VOLTE业务 */
    TAF_LCS_CAUSE_NORAML_REL                                           = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 7),     /* LCS流程正常结束 */
    TAF_LCS_CAUSE_NOT_CAMP_ON                                          = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 8),     /* 未驻留 */
    TAF_LCS_CAUSE_CONN_REL                                             = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 9),     /* 链路释放 */
    TAF_LCS_CAUSE_OTHERS                                               = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 10),    /* 其他原因 */

    /* 网络相关错误 */
    /* Error Code原因值 */
    TAF_LCS_CAUSE_NW_ERR_SS_SUBVIOLATION                               = (TAF_LCS_CAUSE_NW_ERROR_BEGIN + 19),   /* 超过用户权限 */
    TAF_LCS_CAUSE_NW_ERR_FACILITY_NOT_SUPPORT                          = (TAF_LCS_CAUSE_NW_ERROR_BEGIN + 21),   /* Facility不支持 */
    TAF_LCS_CAUSE_NW_ERR_SYSTEM_FAIL                                   = (TAF_LCS_CAUSE_NW_ERROR_BEGIN + 34),   /* 网络异常 */
    TAF_LCS_CAUSE_NW_ERR_DATA_MISSING                                  = (TAF_LCS_CAUSE_NW_ERROR_BEGIN + 35),   /* 缺失数据 */
    TAF_LCS_CAUSE_NW_ERR_UNEXPECT_DATA_VALUE                           = (TAF_LCS_CAUSE_NW_ERROR_BEGIN + 36),   /* 非法数据 */
    TAF_LCS_CAUSE_NW_ERR_POSITION_METHOD_FAIL                          = (TAF_LCS_CAUSE_NW_ERROR_BEGIN + 54),   /* 定位方式错误 */

    /* Rej Compnent Problem原因值 */
    /*********************** General Problem Codes ********************/
    TAF_LCS_NW_CAUSE_UNRECOGNIZED_COMPONENT                            = TAF_LCS_NW_CAUSE_GENERAL_REJ_BEGIN + 0,
    TAF_LCS_NW_CAUSE_MISTYPED_COMPONENT                                = TAF_LCS_NW_CAUSE_GENERAL_REJ_BEGIN + 1,
    TAF_LCS_NW_CAUSE_BADLY_STRUCTURED_COMPONENT                        = TAF_LCS_NW_CAUSE_GENERAL_REJ_BEGIN + 2,

    /************************Invoke Problem Codes***********************/
    TAF_LCS_NW_CAUSE_DUPLICATE_INVOKE_ID                               = TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN + 0,
    TAF_LCS_NW_CAUSE_UNRECOGNIZED_OPERATION                            = TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN + 1,
    TAF_LCS_NW_CAUSE_INVOKE_MISTYPED_PARAMETER                         = TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN + 2,
    TAF_LCS_NW_CAUSE_RESOURCE_LIMITATION                               = TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN + 3,
    TAF_LCS_NW_CAUSE_INITIATING_RELEASE                                = TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN + 4,
    TAF_LCS_NW_CAUSE_UNRECOGNIZED_LINKED_ID                            = TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN + 5,
    TAF_LCS_NW_CAUSE_LINKED_RESPONSE_UNEXPECTED                        = TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN + 6,
    TAF_LCS_NW_CAUSE_UNEXPECTED_LINKED_OPERATION                       = TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN + 7,
    TAF_LCS_NW_CAUSE_INVALID_MANDATORY_IE                              = TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN + 8,

    /**********************Return Result Problem Codes******************/
    TAF_LCS_NW_CAUSE_RETURN_RSLT_UNRECOGNIZED_INVOKE_ID                = TAF_LCS_NW_CAUSE_RTRN_RSLT_REJ_BEGIN + 0,
    TAF_LCS_NW_CAUSE_RETURN_RSLT_UNEXPECTED                            = TAF_LCS_NW_CAUSE_RTRN_RSLT_REJ_BEGIN + 1,
    TAF_LCS_NW_CAUSE_RETURN_RSLT_MISTYPED_PARAMETER                    = TAF_LCS_NW_CAUSE_RTRN_RSLT_REJ_BEGIN + 3,

    /**********************Return Error Problem Codes********************/
    TAF_LCS_NW_CAUSE_RETURN_ERROR_UNRECOGNIZED_INVOKE_ID               = TAF_LCS_NW_CAUSE_RTRN_ERR_REJ_BEGIN + 0,
    TAF_LCS_NW_CAUSE_RETURN_ERROR_UNEXPECTED                           = TAF_LCS_NW_CAUSE_RTRN_ERR_REJ_BEGIN + 1,
    TAF_LCS_NW_CAUSE_RETURN_ERROR_UNRECOGNIZED_ERROR                   = TAF_LCS_NW_CAUSE_RTRN_ERR_REJ_BEGIN + 2,
    TAF_LCS_NW_CAUSE_RETURN_ERROR_UNEXPECTED_ERROR                     = TAF_LCS_NW_CAUSE_RTRN_ERR_REJ_BEGIN + 3,
    TAF_LCS_NW_CAUSE_RETURN_ERROR_MISTYPED_PARAMETER                   = TAF_LCS_NW_CAUSE_RTRN_ERR_REJ_BEGIN + 4,

    /* MM返回的错误 */
    /* MM Inter Error */
    TAF_LCS_CAUSE_MM_INTER_ERR_FORB_LA                                 = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 0,
    TAF_LCS_CAUSE_MM_INTER_ERR_FORB_OTHER                              = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 1,
    TAF_LCS_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR                           = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 2,
    TAF_LCS_CAUSE_MM_INTER_ERR_CS_DETACH                               = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 3,
    TAF_LCS_CAUSE_MM_INTER_ERR_CS_SIM_INVALID                          = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 4,
    TAF_LCS_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION                   = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 5,
    TAF_LCS_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT                         = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 6,
    TAF_LCS_CAUSE_MM_INTER_ERR_SEARCHING_NETWORK                       = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 7,
    TAF_LCS_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE                 = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 8,
    TAF_LCS_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY        = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 9,
    TAF_LCS_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE                         = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 10,
    TAF_LCS_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE                    = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 11,
    TAF_LCS_CAUSE_MM_INTER_ERR_CSFB_ALREADY_EXISTS                     = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 12,
    TAF_LCS_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL                       = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 13,
    TAF_LCS_CAUSE_MM_INTER_ERR_TI_INVALID                              = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 14,
    TAF_LCS_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT                   = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 15,   /* redial */
    TAF_LCS_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST                       = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 16,
    TAF_LCS_CAUSE_MM_INTER_ERR_UE_INVALID_STATE                        = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 17,
    TAF_LCS_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT                  = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 18,
    TAF_LCS_CAUSE_MM_INTER_ERR_BACK_TO_LTE                             = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 19,
    TAF_LCS_CAUSE_MM_INTER_ERR_RESUME_TO_EHRPD                         = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 20,
    TAF_LCS_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL                          = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 21,   /* 短信业务SAPI3发送失败,和GAS回复失败,不重拨 */
    TAF_LCS_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL                          = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 22,   /* 短信业务SAPI3建立时GAS回复失败,重拨 */
    TAF_LCS_CAUSE_MM_INTER_ERR_ECALL_INACTIVE                          = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 23,   /* eCall Inactive状态,不重拨 */
    TAF_LCS_CAUSE_MM_INTER_ERR_REEST_FAIL                              = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 24,   /* MM reest状态收到est_cnf(失败)或rel ind,不重拨 */
    TAF_LCS_CAUSE_MM_INTER_ERR_CC_REL_REQ                              = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 25,
    TAF_LCS_CAUSE_MM_INTER_ERR_LTE_LIMITED_SERVICE                     = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 26,

    /* LMM返回的错误 */
    TAF_LCS_CAUSE_LMM_PS_NOT_ATTACHED                                  = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 0),     /* PS域未注册 */
    TAF_LCS_CAUSE_LMM_PS_ATTACH_NOT_ALLOWED                            = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 1),     /* PS域不允许注册 */
    TAF_LCS_CAUSE_LMM_USIM_PS_INVAILD                                  = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 2),     /* USIM卡无效 */
    TAF_LCS_CAUSE_LMM_ACCESS_BARRED                                    = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 3),     /* 被BAR */
    TAF_LCS_CAUSE_LMM_STATE_CANNOT_SERVICE                             = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 4),     /* 当前状态不允许发起Service流程 */
    TAF_LCS_CAUSE_LMM_EPC_LCS_NOT_SUPPORT                              = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 5),     /* EPC-LCS不支持 */
    TAF_LCS_CAUSE_LMM_3411_RUNNING                                     = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 6),     /* 3411定时器正在运行 */
    TAF_LCS_CAUSE_LMM_SERVICE_FAIL                                     = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 7),     /* Service失败 */
    TAF_LCS_CAUSE_LMM_RRC_CONN_NOT_EXIST                               = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 8),     /* 链路不存在 */
    TAF_LCS_CAUSE_LMM_LOW_LAYER                                        = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 9),     /* 底层失败 */
    TAF_LCS_CAUSE_LMM_USER_INACTIVITY                                  = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 10),    /* 网侧不活动定时器超时导致的释放 */
    TAF_LCS_CAUSE_LMM_OTHERS                                           = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 11),    /* 其他原因值 */

    TAF_LCS_CAUSE_BUTT

};
typedef VOS_UINT32 TAF_LCS_CAUSE_ENUM_UINT32;

/*******************************************************************************
 枚举名    : TAF_LCS_LR_TYPE_EUNM
 结构说明  : LCS特性Location Request类型枚举
  1.日    期   : 2015年8月25日
    作    者   : l00198894
    修改内容   : 新增枚举
*******************************************************************************/
enum TAF_LCS_LR_TYPE_EUNM
{
    TAF_LCS_LR_TYPE_MO                  = 0,                                    /* MO-LR */
    TAF_LCS_LR_TYPE_MT                  = 1,                                    /* MT-LR */

    TAF_LCS_LR_TYPE_BUTT
};
typedef VOS_UINT8 TAF_LCS_LR_TYPE_EUNM_UINT8;

/*******************************************************************************
 枚举名    : TAF_LCS_POWER_STATUS_EUNM
 结构说明  : 开关机状态枚举
  1.日    期   : 2015年8月25日
    作    者   : l00198894
    修改内容   : 新增枚举
*******************************************************************************/
enum TAF_LCS_POWER_STATUS_EUNM
{
    TAF_LCS_POWER_STATUS_OFF            = 0,                                    /* Power Off */
    TAF_LCS_POWER_STATUS_ON             = 1,                                    /* Power On */

    TAF_LCS_POWER_STATUS_BUTT
};
typedef VOS_UINT8 TAF_LCS_POWER_STATUS_EUNM_UINT8;

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
 枚举名称: TAF_LCS_MSG_ID_ENUM
 枚举说明: TAF层与LCS模块间的接口消息ID

 修改历史      :
  1.日    期   : 2015年09月09日
    作    者   : l00198894
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_LCS_MSG_ID_ENUM
{
    /* TAF发送给LCS的消息原语 */
    ID_TAF_LCS_BEGIN_REQ                = TAF_LCS_MSG_ID_BASE + 0x1,            /* _H2ASN_MsgChoice TAF_LCS_BEGIN_REQ_STRU */
    ID_TAF_LCS_END_REQ                  = TAF_LCS_MSG_ID_BASE + 0x2,            /* _H2ASN_MsgChoice TAF_LCS_END_REQ_STRU */
    ID_TAF_LCS_POWER_STATUS_NTF         = TAF_LCS_MSG_ID_BASE + 0x3,            /* _H2ASN_MsgChoice TAF_LCS_POWER_STATUS_NTF_STRU */

    /* LCS发送给TAF的消息原语 */
    ID_LCS_TAF_BEGIN_IND                = LCS_TAF_MSG_ID_BASE + 0x1,            /* _H2ASN_MsgChoice LCS_TAF_BEGIN_IND_STRU */
    ID_LCS_TAF_FACILITY_IND             = LCS_TAF_MSG_ID_BASE + 0x2,            /* _H2ASN_MsgChoice LCS_TAF_FACILITY_IND_STRU */
    ID_LCS_TAF_END_IND                  = LCS_TAF_MSG_ID_BASE + 0x3,            /* _H2ASN_MsgChoice LCS_TAF_END_IND_STRU */

    ID_TAF_LCS_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 TAF_LCS_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名称: LCS_TAF_LOCATION_INFO_STRU
 协议表格:
 ASN.1 描述:
 结构说明: MO-LR流程,网侧回复的Location信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpLocationEstimate   :1;
    VOS_UINT32                          bitOpVelocityEstimate   :1;
    VOS_UINT32                          bitOpSpare              :30;
    LOC_COM_COORDINATE_STRU             stLocationEstimate;             /* 位置信息 */
    LOC_COM_VELOCITY_STRU               stVelocityEstimate;             /* 速度信息 */
}LCS_TAF_LOCATION_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_LCS_BEGIN_REQ_STRU
 结构说明  : TAF SSA模块发给LCS模块消息ID_TAF_LCS_BEGIN_REQ对应结构体
  1.日    期   : 2015年9月14日
    作    者   : l00198894
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    LCS_MOLR_PARA_STRU                  stMolrPara;
}TAF_LCS_BEGIN_REQ_STRU;

/*****************************************************************************
 结构名    : TAF_LCS_BEGIN_REQ_STRU
 结构说明  : TAF SSA模块发给LCS模块消息ID_TAF_LCS_BEGIN_REQ对应结构体
  1.日    期   : 2015年9月14日
    作    者   : l00198894
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    TAF_LCS_LR_TYPE_EUNM_UINT8          enLcsType;                              /* LR类型 */
    LCS_MTLRA_OP_ENUM_UINT8             enAllow;                                /* MT-LR时有效 */
    VOS_UINT8                           ucHandleId;                             /* MT-LR时有效 */
    VOS_UINT8                           aucReserved[1];
}TAF_LCS_END_REQ_STRU;

/*****************************************************************************
 结构名    : TAF_LCS_POWER_STATUS_NTF_STRU
 结构说明  : TAF SSA模块发给LCS模块消息ID_TAF_LCS_POWER_STATUS_NTF对应结构体
  1.日    期   : 2015年9月14日
    作    者   : l00198894
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    TAF_LCS_POWER_STATUS_EUNM_UINT8     enStatus;                               /* 开关机状态 */
    VOS_UINT8                           aucReserved[3];
}TAF_LCS_POWER_STATUS_NTF_STRU;

/*****************************************************************************
 结构名    : LCS_TAF_BEGIN_IND_STRU
 结构说明  : LCS模块发给TAF SSA模块消息ID_LCS_TAF_BEGIN_IND对应结构体
  1.日    期   : 2015年9月14日
    作    者   : l00198894
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    LCS_MTLR_PARA_STRU                  stMtlrPara;
}LCS_TAF_BEGIN_IND_STRU;

/*****************************************************************************
 结构名    : LCS_TAF_FACILITY_IND_STRU
 结构说明  : LCS模块发给TAF SSA模块消息ID_LCS_TAF_FACILITY_IND对应结构体
  1.日    期   : 2015年9月14日
    作    者   : l00198894
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    LCS_TAF_LOCATION_INFO_STRU          stLocationParam;
    TAF_LCS_CAUSE_ENUM_UINT32           enCause;                                /* 原因值 */
}LCS_TAF_FACILITY_IND_STRU;

/*****************************************************************************
 结构名    : LCS_TAF_END_IND_STRU
 结构说明  : LCS模块发给TAF SSA模块消息ID_LCS_TAF_END_IND对应结构体
  1.日    期   : 2015年9月14日
    作    者   : l00198894
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    TAF_LCS_LR_TYPE_EUNM_UINT8          enLcsType;                              /* LR类型 */
    VOS_UINT8                           ucHandleId;                             /* MT-LR时有效 */
    VOS_UINT8                           aucReserved[2];                         /* 保留位 */
    TAF_LCS_CAUSE_ENUM_UINT32           enCause;                                /* 原因值 */
}LCS_TAF_END_IND_STRU;




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

#endif /* end of TafLcsInterface.h */

