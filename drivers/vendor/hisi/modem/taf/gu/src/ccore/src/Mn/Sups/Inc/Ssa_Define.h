/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : Ssa_Define.h
  Author      : ---
  Version     : V200R001
  Date        : 2005-08-16
  Description : 该头文件定义了SSA模块解码函数的接口
  History     :
  1. Date:2005-04-19
     Author: ---
     Modification:Create
  2. Date:2006-04-11
     Author: h44270
     Modification: 问题单号:A32D02911
  3.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
  4.日    期   : 2006年10月8日
    作    者   : luojian id:60022475
    修改内容   : 问题单号:A32D06583,修改SSA_TimeoutProc函数的参数定义
  5.日    期   : 2006年12月09日
    作    者   : h44270
    修改内容   : 问题单号:A32D07867，增加一个接口，用于判定字串的操作类型
  6.Date:2007-01-19
    Author: h44270
    Modification: 问题单号:A32D08448
  7.Date:2007-04-29
    Author: Li Jilin 60827
    Modification: 问题单号:A32D10708
  8.日    期   : 2007年05月09日
    作    者   : 罗建 id:60022475
    修改内容   : 问题单号:A32D10838
************************************************************************/
#ifndef _SSA_DEFINEa_H_
#define _SSA_DEFINEa_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#include "PsTypeDef.h"
#include "Ps.h"
/* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
#include "TafClientApi.h"
/* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */
#include "ExtAppCmInterface.h"
#include "TafAppSsa.h"

#include "MnComm.h"

#pragma pack(4)

/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
/* Deleted TAF_SS_ERRCODE_OFFSET */
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */

/************************错误码的偏移***********************************/
#define  TAF_SS_ERRCODE_OFFSET             TAF_ERR_SS_BASE

/*********************打印函数的封装************************/
#define SSA_LOG(level, string) \
    TAF_LOG(WUEPS_PID_TAF, TAF_SSA, level, string)
#define SSA_LOG1(level, string, para1) \
    TAF_LOG1(WUEPS_PID_TAF, TAF_SSA, level, string, para1)
#define SSA_LOG2(level, string, para2) \
    TAF_LOG2(WUEPS_PID_TAF, TAF_SSA, level, string, para2)

#define SSA_FALSE_LENGTH_FLAG                   (0x80)
#define SSA_LONG_LENGTH_FORMAT_MASK             (SSA_FALSE_LENGTH_FLAG - 1)
#define SSA_MAX_COMPONENT_LENGTH                (0xff)
/*********************操作需要密码的有效性************************/
#define     SSA_PASSWORD_VALID                  1
#define     SSA_PASSWORD_INVALID                0

/*********************表明当前是否有SS操作************************/
#define     SSA_IDLE                            (0)
#define     SSA_USED                            (1)
#define     SSA_FDN_CHECK                       (2)

/*********************Ti的最大值和中间值************************/
#define     TAF_MAX_SSA_TI                      14
#define     TAF_MIDDLE_SSA_TI                   7

/*************************Component ID tag**********************/
#define     INVOKE_ID_TAG                       0x02
#define     LINKED_ID_TAG                       0x80
#define     SSA_NULL_TAG                        0x03
/***************************************************************/

/************************Operation Code tag*********************/
#define     OPERATION_CODE_TAG                  0x02
/**************************************************************/

/************************Sequence and Set tags****************/
#define     TAG_SS_OF_SEQUENCE                  0x30
#define     TAG_SS_OF_SET                       0x31
/***************************************************************/

/************************Error Code tag****************/
#define     ERROR_CODE_TAG                      0x02
/***************************************************************/

/************************Problem Code tags****************/
#define     GENERAL_PROBLEM_TAG                 0x80
#define     INVOKE_PROBLEM_TAG                  0x81
#define     RETURN_RESULT_PROBLEM_TAG           0x82
#define     RETURN_ERROR_PROBLEM_TAG            0x83
/***************************************************************/

/***********************Reject code定义****************************/
/*通过高4位来区分不同Problem Code tags*/
typedef      VOS_UINT8          TAF_SS_REJECT;
/*********************** General Problem Codes ********************/
#define      TAF_SS_REJ_UNRECOGNIZED_COMPONENT                  0x10
#define      TAF_SS_REJ_MISTYPED_COMPONENT                      0x11
#define      TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT              0x12

/************************Invoke Problem Codes***********************/
#define      TAF_SS_REJ_DUPLICATE_INVOKE_ID                     0x20
#define      TAF_SS_REJ_UNRECOGNIZED_OPERATION                  0x21
#define      TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER               0x22
#define      TAF_SS_REJ_RESOURCE_LIMITATION                     0x23
#define      TAF_SS_REJ_INITIATING_RELEASE                      0x24
#define      TAF_SS_REJ_UNRECOGNIZED_LINKED_ID                  0x25
#define      TAF_SS_REJ_LINKED_RESPONSE_UNEXPECTED              0x26
#define      TAF_SS_REJ_UNEXPECTED_LINKED_OPERATION             0x27
#define      TAF_SS_REJ_INVALID_MANDATORY_IE                    0x28

/**********************Return Result Problem Codes******************/
#define      TAF_SS_REJ_RETURN_RESULT_UNRECOGNIZED_INVOKE_ID    0x30
#define      TAF_SS_REJ_RETURN_RESULT_UNEXPECTED                0x31
#define      TAF_SS_REJ_RETURN_RESULT_MISTYPED_PARAMETER        0x32

/**********************Return Error Problem Codes********************/
#define      TAF_SS_REJ_RETURN_ERROR_UNRECOGNIZED_INVOKE_ID     0x40
#define      TAF_SS_REJ_RETURN_ERROR_UNEXPECTED                 0x41
#define      TAF_SS_REJ_UNRECOGNIZED_ERROR                      0x42
#define      TAF_SS_REJ_UNEXPECTED_ERROR                        0x43
#define      TAF_SS_REJ_RETURN_ERROR_MISTYPED_PARAMETER         0x44
/*************************Reject code定义完成*************************/


#define     SSA_MMI_SS_SC_NUM                   20
#define     SSA_MMI_NOTSS_SC_NUM                20
/*******************MMI定义的SS-Code***********************/
/**SS相关***/
#define     SSA_MMI_ALL_SS_CODE                      0
#define     SSA_MMI_SERVICECODE_CLIP                30
#define     SSA_MMI_SERVICECODE_CLIR                31
#define     SSA_MMI_SERVICECODE_COLP                76
#define     SSA_MMI_SERVICECODE_COLR                77

#define     SSA_MMI_SERVICECODE_CFU                 21
#define     SSA_MMI_SERVICECODE_CFB                 67
#define     SSA_MMI_SERVICECODE_CFNRy               61
#define     SSA_MMI_SERVICECODE_CFNYc               62
#define     SSA_MMI_SERVICECODE_ALLCF               2
#define     SSA_MMI_SERVICECODE_ALLCONDCF           4
#define     SSA_MMI_SERVICECODE_WAIT                43
#define     SSA_MMI_SERVICECODE_BAOC                33
#define     SSA_MMI_SERVICECODE_BAOIC               331
#define     SSA_MMI_SERVICECODE_BAOICExHc           332
#define     SSA_MMI_SERVICECODE_BAIC                35
#define     SSA_MMI_SERVICECODE_BAICROAM            351
#define     SSA_MMI_SERVICECODE_ALLBARRING          330
#define     SSA_MMI_SERVICECODE_OUTGBARR            333
#define     SSA_MMI_SERVICECODE_INCBARR             353

/***SS无关***/
#define     SSA_MMI_SERVICECODE_eMLPP               75
#define     SSA_MMI_SERVICECODE_eMLPP0              750
#define     SSA_MMI_SERVICECODE_eMLPP1              751
#define     SSA_MMI_SERVICECODE_eMLPP2              752
#define     SSA_MMI_SERVICECODE_eMLPP3              753
#define     SSA_MMI_SERVICECODE_eMLPP4              754
#define     SSA_MMI_SERVICECODE_CD                  66
#define     SSA_MMI_SERVICECODE_UUS1                361
#define     SSA_MMI_SERVICECODE_UUS2                362
#define     SSA_MMI_SERVICECODE_UUS3                363
#define     SSA_MMI_SERVICECODE_ALL_UUS             360
#define     SSA_MMI_SERVICECODE_ECT                 96
#define     SSA_MMI_SERVICECODE_CCBS                37
#define     SSA_MMI_SERVICECODE_FM                  214
#define     SSA_MMI_SERVICECODE_CNAP                300
#define     SSA_MMI_SERVICECODE_MSP1                591
#define     SSA_MMI_SERVICECODE_MSP2                592
#define     SSA_MMI_SERVICECODE_MSP3                593
#define     SSA_MMI_SERVICECODE_MSP4                594
#define     SSA_MMI_SERVICECODE_MC                  88
/*******************MMI定义的SS-Code完成*******************/

#define    SSA_MMI_BS_NUM                           45
/**MMI定义的basic service code 的值*/
#define    SSA_MMI_BS_ALL_TELESERVICE               10
#define    SSA_MMI_BS_TELEPHONY                     11
#define    SSA_MMI_BS_ALL_DATA_TELESERVICE          12
#define    SSA_MMI_BS_ALL_FACSIMILE_TELESERVICE     13
#define    SSA_MMI_BS_ALL_SMS_TELESERVICE           16
#define    SSA_MMI_BS_ALL_EX_SMS_TELESERVICE        19
#define    SSA_MMI_BS_ALL_VGCS_TELESERVICE          17
#define    SSA_MMI_BS_ALL_VBS_TELESERVICE           18
#define    SSA_MMI_BS_ALL_BEARER_SERVICES           20
#define    SSA_MMI_BS_ALL_ASYNC_SERVICES            21
#define    SSA_MMI_BS_ALL_SYNC_SERVICES             22
#define    SSA_MMI_BS_ALL_DATA_CIRCUIT_SYNC         24
#define    SSA_MMI_BS_ALL_DATA_CIRCUIT_ASYNC        25
#define    SSA_MMI_BS_ALL_GPRS_BEARER_SERVICES      99
#define    SSA_MMI_BS_ALL_PLMN_SPECIFICTS_TS        50
#define    SSA_MMI_BS_PLMN_SPECIFICTS_1_TS          51
#define    SSA_MMI_BS_PLMN_SPECIFICTS_2_TS          52
#define    SSA_MMI_BS_PLMN_SPECIFICTS_3_TS          53
#define    SSA_MMI_BS_PLMN_SPECIFICTS_4_TS          54
#define    SSA_MMI_BS_PLMN_SPECIFICTS_5_TS          55
#define    SSA_MMI_BS_PLMN_SPECIFICTS_6_TS          56
#define    SSA_MMI_BS_PLMN_SPECIFICTS_7_TS          57
#define    SSA_MMI_BS_PLMN_SPECIFICTS_8_TS          58
#define    SSA_MMI_BS_PLMN_SPECIFICTS_9_TS          59
#define    SSA_MMI_BS_PLMN_SPECIFICTS_10_TS          60
#define    SSA_MMI_BS_PLMN_SPECIFICTS_11_TS          61
#define    SSA_MMI_BS_PLMN_SPECIFICTS_12_TS          62
#define    SSA_MMI_BS_PLMN_SPECIFICTS_13_TS          63
#define    SSA_MMI_BS_PLMN_SPECIFICTS_14_TS          64
#define    SSA_MMI_BS_PLMN_SPECIFICTS_15_TS          65
#define    SSA_MMI_BS_ALL_PLMN_SPECIFICTS_BS        70
#define    SSA_MMI_BS_PLMN_SPECIFICTS_1_BS          71
#define    SSA_MMI_BS_PLMN_SPECIFICTS_2_BS          72
#define    SSA_MMI_BS_PLMN_SPECIFICTS_3_BS          73
#define    SSA_MMI_BS_PLMN_SPECIFICTS_4_BS          74
#define    SSA_MMI_BS_PLMN_SPECIFICTS_5_BS          75
#define    SSA_MMI_BS_PLMN_SPECIFICTS_6_BS          76
#define    SSA_MMI_BS_PLMN_SPECIFICTS_7_BS          77
#define    SSA_MMI_BS_PLMN_SPECIFICTS_8_BS          78
#define    SSA_MMI_BS_PLMN_SPECIFICTS_9_BS          79
#define    SSA_MMI_BS_PLMN_SPECIFICTS_10_BS          80
#define    SSA_MMI_BS_PLMN_SPECIFICTS_11_BS          81
#define    SSA_MMI_BS_PLMN_SPECIFICTS_12_BS          82
#define    SSA_MMI_BS_PLMN_SPECIFICTS_13_BS          83
#define    SSA_MMI_BS_PLMN_SPECIFICTS_14_BS          84
#define    SSA_MMI_BS_PLMN_SPECIFICTS_15_BS          85
/**MMI定义basic service code 完成*/

/*定义每个操作的最大长度*/
#define     MAX_FACILITY_LEN                    255

/*BER编码TAG的类型定义*/
#define     BOOLEAN_TAG                         0x01
#define     INTEGER_TAG                         0x02
#define     BITSTRING_TAG                       0x03
#define     OCTETSTRING_TAG                     0x04
#define     NULL_TAG                            0x05
#define     ENUMERATED_TAG                      0x0A
#define     NUMERICSTRING_TAG                   0x12
#define     SEQUENCE_TAG                        0x10
#define     IA5STRING_TAG                       0x16
#define     SET_TAG                             0x31


#define     SSA_SUCCESS                         TAF_ERR_NO_ERROR
#define     SSA_FAILURE                         TAF_ERR_ERROR
#define     SSA_PARA_ERROR                      TAF_ERR_PARA_ERROR

/*位域存在标志*/
#define     SSA_FIELD_EXIST                     1
#define     SSA_FIELD_NOT_EXIST                 0

/*#define isdigit(c) ('0' <= (c) && (c)  <= '9')*/

/**定义标签结构(原子式还是构成式)**/
#define     PRIMITIVE_TAG                       0
#define     CONSTRUCTED_TAG                     1

/*定义标签类型*/
#define     UNIVERSAL_TAG_TYPE                  0
#define     APPLICATION_TAG_TYPE                1
#define     CONTEXT_SPECIFIC_TAG_TYPE           2
#define     PRIVATE_TAG_TYPE                    3

/*定义标签模式*/
typedef   VOS_UINT8   TAG_MODE;
#define     EXPLICIT_MODE                       1
#define     IMPLICIT_MODE                       0

/*定义新*/
#define     SSA_OP_REGISTER                     1
#define     SSA_OP_ERASE                        2
#define     SSA_OP_ACTIVATE                     3
#define     SSA_OP_DEACTIVATE                   4
#define     SSA_OP_INTERROGATE                  5
#define     SSA_OP_REGPASSWORD                  6
#define     SSA_OP_USSD                         7
#define     SSA_OP_ERROR                        8

/*==>A32D10708*/
#define SSA_NUM_TYPE_INT_E164                   145
#define SSA_NUM_TYPE_UNKNOWN_E164               129

/*<==A32D10708*/

#define TAF_SSA_ONE_THOUSAND_MILLISECOND       (1000)                                  /* 1000MS */
#define TAF_SSA_MAX_TIMER_NUM                  (3)
#define TAF_SSA_TIMER_TICK                     (10)


/*宏定义异常返回*/
#define SSA_ERRTRACE(a,b,c,d,e) \
    if (a != SSA_SUCCESS) \
    { \
		TAF_PRINT(b,c,d); \
		return e; \
    }

/* 原语GMMSM_SYS_INFO_IND的结构体 */
enum
{
    DEF_ALPHA_TO_ASCII_TABLE         = 0, /* 默认的字符表转换，*/
    TME_ALPHA_TO_ASCII_TABLE         = 1, /* TEM字符表转换*/
    ALPHA_TO_ASCII_TABLE_BUTT
};
typedef VOS_UINT8   ALPHA_TO_ASCII_TABLE_ENUM;

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-5-6, begin */
/* TAF_SSA_USSD_STATE的枚举 */
enum
{
    TAF_SSA_USSD_IDLE_STATE               = 0, /* IDLE态 */
    TAF_SSA_USSD_MO_CONN_STATE            = 1, /* UE主动发起的连接状态 */
    TAF_SSA_USSD_MT_CONN_STATE            = 2, /* 网侧主动发起的连接状态 */
    TAF_SSA_USSD_BUTT_STATE                    /* 无效值 */
};
typedef VOS_UINT8   TAF_SSA_USSD_STATE_ENUM_UINT8;
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-5-6, begin */


/*BER编码中TAG值的分解*/
typedef struct
{
    VOS_UINT8               ucClass;
    VOS_UINT8               ucStructed;
    VOS_INT32               iNumber;
}SSA_TAG_STRU;

/* SSA_TAG_STRU      gNullTag = { 0 , 0 , 0    }; */

/*用于提取MMI字串内容*/
typedef struct
 {
    VOS_UINT8               ucOpMode;
    VOS_UINT8               ucPwdFlg;
    VOS_UINT8               ucScFlg;
    VOS_UINT8               ucSiaFlg;
    VOS_UINT8               ucSibFlg;
    VOS_UINT8               ucSicFlg;
    VOS_UINT32              ulSc;
    VOS_UINT8               aucSia[30];
    VOS_UINT8               ucSiaLen;
    VOS_UINT8               ucSib;
    VOS_UINT8               ucSibLen;
    VOS_UINT8               ucSic;
    VOS_UINT8               aucOldPwd[4];
    VOS_UINT8               aucNewPwd[4];
    VOS_UINT8               aucNewPwdCnf[4];
}SSA_MMI_PARA_STRU;

/*****************************************************************************
 枚举名    : TAF_SSA_TIMER_STATUS_ENUM_UINT8
 结构说明  : ssa定时器状态,停止或运行
  1.日    期   : 2013年9月10日
    作    者   : z00161729
    修改内容   : 新建
*****************************************************************************/
enum TAF_SSA_TIMER_STATUS_ENUM
{
    TAF_SSA_TIMER_STATUS_STOP,              /* 定时器停止状态 */
    TAF_SSA_TIMER_STATUS_RUNING,            /* 定时器运行状态 */
    TAF_SSA_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 TAF_SSA_TIMER_STATUS_ENUM_UINT8;


/*****************************************************************************
 枚举名    : TAF_SSA_STATE_ENUM
 结构说明  : ssa状态
 1.日    期   : 2011年7月11日
   作    者   : zhoujun 40661
   修改内容   : 新建
*****************************************************************************/
enum TAF_SSA_STATE_ENUM
{
    TAF_SSA_STATE_IDLE,                                                         /* 空状态 */
    TAF_SSA_STATE_CONN_PENDING,                                                 /* 等待mm建联回复状态 */
    TAF_SSA_STATE_CONN_ESTED,                                                   /* 连接已建立 */
    TAF_SSA_STATE_BUTT
};
typedef VOS_UINT8 TAF_SSA_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SSA_TIMER_ID_ENUM_UINT8
 枚举说明  : SSA定时器的ID
 1.日    期   : 2013年9月10日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
enum TAF_SSA_TIMER_ID_ENUM
{
    TI_TAF_SSA_WAIT_NETWORK_RSP_TIMER,
    TI_TAF_SSA_WAIT_APP_RSP_TIMER,
    TI_TAF_SSA_RETRY_PERIOD_TIMER,
    TI_TAF_SSA_RETRY_INTERVAL_TIMER,
    TI_TAF_SSA_TIMER_BUTT
};
typedef VOS_UINT8  TAF_SSA_TIMER_ID_ENUM_UINT8;

/*****************************************************************************
 结构名    : TAF_SSA_MSG_BUFF_STRU
 结构说明  : 缓存ss D_SMC_BEGIN_REQ消息和D_SMC_END_IND消息
 1.日    期   : 2013年9月10日
   作    者   : z00161729
   修改内容   : 支持ss重发新增结构

****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpBufferedBeginReqMsg : 1;
    VOS_UINT32                          bitSpare : 31;
    ST_SSP_MSG                          stBufferedBeginReqMsg;
} TAF_SSA_MSG_BUFF_STRU;

/*****************************************************************************
 结构名    : TAF_SSA_TIMER_CXT_STRU
 结构说明  : SSA定时器运行上下文
 1.日    期   : 2013年9月10日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    HTIMER                              hTimer;                                 /* 定时器的运行指针 */
    TAF_SSA_TIMER_ID_ENUM_UINT8         enTimerId;                              /* 定时器的ID */
    TAF_SSA_TIMER_STATUS_ENUM_UINT8     enTimerStatus;                          /* 定时器的运行状态,启动或停止 */
    VOS_UINT8                           aucReserve[2];
} TAF_SSA_TIMER_CXT_STRU;

/*****************************************************************************
 结构名    : TAF_SSA_RETRY_CFG_STRU
 结构说明  : 记录ss重发配置信息
 1.日    期   : 2013年9月10日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2015年8月23日
   作    者   : n00355355
   修改内容   : User_Exp_Improve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsSsRetrySupportFlg;                  /* 是否支持ss重发功能，VOS_TRUE:支持；VOS_FALSE:不支持*/
    VOS_UINT8                           ucSsRetryCmSrvRejCauseNum;
    VOS_UINT8                           aucReserved1[2];
    VOS_UINT32                          ulSsRetryPeriod;                        /* ss重发特性打开时，ss重发最大时长，单位毫秒 */
    VOS_UINT32                          ulSsRetryInterval;                      /* ss重发特性打开时，ss重发间隔单位毫秒 */
    VOS_UINT8                           aucSsRetryCmSrvRejCause[TAF_NVIM_SS_RETRY_CAUSE_MAX_NUM];
}TAF_SSA_RETRY_CFG_STRU;


/*已发起的操作的状态值*/
typedef  struct
{
     VOS_UINT8                  ucState;                /*用于TI和ClientId、CallId间的映射*/
     VOS_UINT16                 ClientId;
     VOS_UINT8                  OpId;
     VOS_UINT8                  ucMsgType;
     VOS_UINT8                  ucInvokeId;             /*Invoke id的值*/
     VOS_UINT8                  ucLinkId;
     VOS_UINT8                  ucOperationCode;        /*操作码的值*/
     VOS_UINT8                  ucSsCode;               /*相应的SS业务*/
     VOS_UINT8                  uComponenttype;
     VOS_UINT8                  ucUssdFlag;             /*标明是否存在USSD操作*/
     VOS_UINT8                  ucPwdFlag;              /*当前状态表中的密码的有效性*/
     VOS_UINT8                  aucOldPwdStr[4];
     VOS_UINT8                  aucNewPwdStr[4];
     VOS_UINT8                  aucNewPwdStrCnf[4];
     TAF_SSA_TIMER_CXT_STRU             astSsaTimerCtx[TAF_SSA_MAX_TIMER_NUM];  /* SSA当前正在运行的定时器资源 */

     TAF_SS_DATA_CODING_SCHEME  DatacodingScheme;

     TAF_SSA_STATE_ENUM_UINT8   enSsaState;
     VOS_UINT8                  aucReserve[2];

     TAF_UINT32                              OP_AlertingPattern:1;
     TAF_UINT32                              OP_Msisdn:1;
     TAF_UINT32                              OP_Spare:30;

     TAF_SS_ALERTINGPATTERN                  AlertingPattern;
     TAF_UINT8                               aucMsisdn[TAF_SS_MAX_MSISDN_LEN + 1];
     TAF_SS_USSD_STRING_STRU    *pstUssdBuf;

     TAF_SSA_MSG_BUFF_STRU                    stSsaBufferedMsg;                 /* ss重建缓存的消息 */
} SSA_STATE_TABLE_STRU;

/*****************************************************************************
 结构名    : SSA_FDN_INFO_STRU
 结构说明  : SS业务模块FDN业务特性参数结构
             ulFdnStatus        (U)SIM的FDN业务使能状态
             stFdnConfig        ME的FDN业务NV配置
1.日    期   : 2012年02月23日
  作    者   : f62575
  修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFdnStatus;
    TAF_FDN_CONFIG_STRU                 stFdnConfig;
}SSA_FDN_INFO_STRU;

/* 补充业务处理函数结构 */
/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
typedef VOS_UINT32 (*TAF_SSA_SERV_REQ_PROC_FUNC)(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pContent
);

/*****************************************************************************
 结构名    : TAF_SSA_SERV_REQ_PROC_FUNC_MAP_STRU
 结构说明  : 消息与对应处理函数的结构
             VOS_UINT16 usMsgType                               - 业务请求消息；
             TAF_SSA_SERV_REQ_PROC_FUNC          pMsgProcFunc   - 编码处理函数

  1.日    期   : 2013年06月26日
    作    者   : 傅映君/62575
    修改内容   : V9R1 STK升级
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMsgType;
    VOS_UINT8                           aucReserved1[2];
    TAF_SSA_SERV_REQ_PROC_FUNC          pMsgProcFunc;
} TAF_SSA_SERV_REQ_PROC_FUNC_MAP_STRU;
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

extern VOS_UINT8                   gucCurrentTi;

extern VOS_UINT32                  gulCurStrMaxLen;        /*当前字串的最大长度*/

/*保存当前SS Version的值*/
extern ST_SSP_IES_SSPVERSION       gstSsVersion;

extern SSA_TAG_STRU      gSsTagValue;

/*编码时,用于存放编码后的内容*/
extern VOS_UINT8  *gpucSsEncodeEndLocation;  /*字串结束位置*/
extern VOS_UINT8   gucSsCurLen;              /*当前字串的长度*/
extern VOS_UINT8   gucSsCurInvokeId;         /*当前所使用的Invoke ID的值*/
extern VOS_UINT8  *gpucSsParaEndLocation;    /*当前Ss参数para部分的结束位置*/

/*SSA状态表*/
extern SSA_STATE_TABLE_STRU        gastSsaStatetable[TAF_MAX_SSA_TI + 1];

/*内部非编解码函数原型定义*/
VOS_VOID   SSA_DealMsgFromSS(ST_SSP_MSG  *pMsg);
VOS_VOID SSA_RegisterIndProc(ST_SSP_MSG  *pMsg);
VOS_VOID SSA_FacilityIndProc(ST_SSP_MSG  *pMsg);
VOS_VOID SSA_RelCompleteIndProc(ST_SSP_MSG  *pMsg);
VOS_VOID   TAF_SsEventReport(TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pEvent);
VOS_VOID   Taf_SsaProc(VOS_UINT16 usMsgType, VOS_UINT16 ClientId,VOS_UINT8 OpId, VOS_UINT8 *pMsg);
VOS_VOID   Taf_SsMsgReq(ST_SSP_MSG *pMsg);
VOS_UINT32 SSA_GetMmiPara(SSA_MMI_PARA_STRU *pstPara,  VOS_UINT8  *pMMIStr, VOS_UINT8  ucStrLen);
VOS_VOID SSA_ReturnError(VOS_UINT16 usErrCode, VOS_UINT8 ucTi, VOS_UINT8 ucMsgType, VOS_UINT8 ucCause);
VOS_VOID SSA_ReturnReject(VOS_UINT8 ucRejCode, VOS_UINT8 ucTi, VOS_UINT8 ucMsgType, VOS_UINT8 ucCause);
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
VOS_UINT32 SSA_RegisterSSReq(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pMsg
);
VOS_UINT32 SSA_EraseSSReq(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pMsg
);
VOS_UINT32 SSA_ActivateSSReq(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pMsg
);
VOS_UINT32 SSA_DeactivateSSReq(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pMsg
);
VOS_UINT32 SSA_InterrogateSSReq(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pMsg
);
VOS_UINT32 SSA_RegisterPasswordReq(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pMsg
);
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

VOS_VOID SSA_GetPasswordRsp (TAF_SS_GETPWD_RSP_STRU  *para, VOS_UINT8 ucTi);
VOS_UINT32 SSA_ProcessUnstructuredSSReq(VOS_UINT16  ClientId, TAF_SS_PROCESS_USS_REQ_STRU *para, VOS_UINT8 ucTi);
VOS_UINT32 SSA_ProcessUSSDataReq(TAF_SS_PROCESS_USSDATA_REQ_STRU *para, VOS_UINT8 ucTi);

/* Modified by z00161729 for V9R1 STK升级, 2013-7-25, begin */

VOS_UINT32 SSA_UnstructuredSSRsp(
    TAF_SS_USS_RSP_STRU                *para,
    VOS_UINT8                           ucTi,
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId
);
/* Modified by z00161729 for V9R1 STK升级, 2013-7-25, end */


VOS_VOID SSA_UssNotifyRsp(VOS_UINT8 ucTi);
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
VOS_UINT32 SSA_EraseCCEntryReq(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pMsg
);
/*VOS_UINT32 SSA_ProcessUSSDataReq(TAF_SS_PROCESS_USSDATA_REQ_STRU *para, VOS_UINT8 ucTi);*/
VOS_UINT32 SSA_ReleaseComplete(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pMsg
);
VOS_UINT32 TAF_SSA_ProcUssdUnstructuredMsg(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pMsg
);

VOS_UINT32 TAF_SSA_IsSsStateIdle(VOS_VOID);

/* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

VOS_UINT8  SSA_GetInvokeId(VOS_UINT8 ucTi);
VOS_UINT32 SSA_GetIdByTi(VOS_UINT16 *pClientId, VOS_UINT8 *pOpId, VOS_UINT8 ucTi);
/* Deleted by l00208543 for V9R1 STK升级, 2013-7-10, begin */
/*VOS_UINT32 SSA_GetTi(VOS_UINT16 ClientId, VOS_UINT8 OpId, VOS_UINT8 *pTi);*/
/* Deleted by l00208543 for V9R1 STK升级, 2013-7-10, end */

/* Added by l00208543 for V9R1 STK升级, 2013-07-10, begin */
VOS_UINT32 TAF_SSA_GetUssdTi(VOS_UINT8 *pucTi);
/* Added by l00208543 for V9R1 STK升级, 2013-07-10, end */

VOS_UINT32 SSA_TiAlloc(VOS_UINT16 ClientId, VOS_UINT8 OpId, VOS_UINT8 *pTi);
VOS_VOID   SSA_TiFree(VOS_UINT8 ucTi);

VOS_VOID   TAF_SSA_WaitNetworkRspTimerExpired(VOS_UINT8 ucTi);
VOS_VOID TAF_SSA_WaitAppRspTimerExpired(VOS_UINT8  ucTi);


VOS_UINT32 SSA_CheckInvokeId(VOS_UINT8 ucTi, VOS_UINT8  ucInvokeId);
VOS_UINT32 SSA_CheckOperationCode(VOS_UINT8 ucTi, VOS_UINT8  ucOperationCode);
VOS_UINT32 SSA_PackMsgHeader(ST_SSP_IES_FACILITY  *stFacility, TAF_SS_OPERATION ucOperationcode,
                             TAF_SS_MSGTYPE ucMsgType, VOS_UINT8 ucTi, TAF_SS_ERROR ucErrCode,
                             TAF_SS_REJECT ucProblemCode);
VOS_UINT32 SSA_TiIdle(VOS_VOID);
VOS_UINT8  SSA_GetRepEvtFromOpCode(VOS_UINT8  ucOprationCode);

VOS_UINT16  SSA_GetUssdTransMode(VOS_VOID);
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-5-6, Begin */
VOS_VOID  TAF_SSA_UpdateUssdRptStatus(
    TAF_SS_PROCESS_USS_REQ_STRU        *pstSsReqMsg
);
VOS_UINT32 TAF_SSA_IsUssdStateIdle(VOS_VOID);
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
/* MOVE TAF_SSA_ProcUssdUnstructuredMsg */
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-5-6, End */

VOS_VOID TAF_SSA_SetSsRetrySupportFlg(VOS_UINT8 ucIsSsRetrySupportFlg);
VOS_UINT8 TAF_SSA_GetSsRetrySupportFlg(VOS_VOID);
VOS_UINT32 TAF_SSA_GetSsRetryIntervalTimerLen(VOS_VOID);
VOS_VOID TAF_SSA_SetSsRetryIntervalTimerLen(VOS_UINT32 ulSsRetryInterval);
VOS_UINT32 TAF_SSA_GetSsRetryPeriodTimerLen(VOS_VOID);
VOS_VOID TAF_SSA_SetSsRetryPeriodTimerLen(VOS_UINT32 ulSsRetryPeriod);

VOS_VOID  TAF_SSA_ReadSsRetryCfgNvim( VOS_VOID );
VOS_VOID  TAF_SSA_ReadSsRetryCmSrvRejCfgNvim( VOS_VOID );
VOS_VOID TAF_SSA_ClearBufferedMsg(VOS_UINT8 ucTi);
TAF_SSA_MSG_BUFF_STRU*  TAF_SSA_GetBufferedMsg(VOS_UINT8 ucTi);
VOS_UINT32  TAF_SSA_GetTimerRemainLen(
    TAF_SSA_TIMER_ID_ENUM_UINT8         enTimerId,
    VOS_UINT8                           ucTi
);
TAF_SSA_TIMER_STATUS_ENUM_UINT8  TAF_SSA_GetTimerStatus(
    TAF_SSA_TIMER_ID_ENUM_UINT8         enTimerId,
    VOS_UINT8                           ucTi
);

VOS_VOID  TAF_SSA_StopTimer(
    TAF_SSA_TIMER_ID_ENUM_UINT8         enTimerId,
    VOS_UINT8                           ucTi
);

VOS_UINT32  TAF_SSA_StartTimer(
    TAF_SSA_TIMER_ID_ENUM_UINT8         enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucTi
);


VOS_VOID TAF_SSA_RcvSsCsConnInd(ST_SSP_MSG  *pstMsg);

VOS_UINT32 TAF_SSA_IsNeedSsRetry(
    VOS_UINT8                           ucTi,
    SSA_SS_REL_CAUSE_ENUM_UINT32        enRelCause
);

VOS_VOID  TAF_SSA_StopAllTimer(VOS_UINT8 ucTi);
VOS_VOID  TAF_SSA_RcvTimerExpired(
    TAF_SSA_TIMER_ID_ENUM_UINT8         enTimerId,
    VOS_UINT8                           ucTi
);

VOS_VOID TAF_SSA_RcvMmaMsg(VOS_VOID *pMsg);
VOS_VOID  TAF_SSA_InitAllTimers(
    TAF_SSA_TIMER_CXT_STRU              *pstSsaTimerCtx
);
VOS_VOID TAF_SSA_RetryPeriodTimerExpired(VOS_UINT8 ucTi);
VOS_VOID TAF_SSA_RetryIntervalTimerExpired(VOS_UINT8 ucTi);
VOS_UINT32  TAF_SSA_IsTiValid(VOS_UINT8   ucTi);
VOS_VOID  Taf_SSA_ProcBufferedBeginReqMsg(ST_SSP_MSG *pMsg);


VOS_UINT32 SSA_IsSsRetryCause(
    SSA_SS_REL_CAUSE_ENUM_UINT32        enCause
);

TAF_SSA_RETRY_CFG_STRU* TAF_SSA_GetSsaRetryCfgInfo(VOS_VOID);


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

#endif /* end of SSA_Define.h*/
