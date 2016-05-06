/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallCtx.h
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年9月3日
  最近修改   :
  功能描述   : TafXCallCtx.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年9月3日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_X_CALL_CTX_H__
#define __TAF_X_CALL_CTX_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#include "xcc_xcall_pif.h"
#include "TafCsCallCommDef.h"
#include "hi_list.h"
#include "TafXCallTimerMgmt.h"
#include "AtMnInterface.h"

#include "TafXCallKmcCommType.h"
#include "TafStdlib.h"
#include "TafAppCall.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* call id 从1开始 */

/* 1X CALL 最大呼叫个数 */
#define TAF_XCALL_CALL_ENTITY_MAX_NUM                       (2)

#define TAF_XCALL_MAX_SS_CMD_KEY_EVT_NUM                    (10)                /* 补充业务操作管理结构 */

#define TAF_XCALL_MIN(x, y)\
        (((x)<(y))?(x):(y))

#define TAF_XCALL_MAX(x, y)\
        (((x)>(y))?(x):(y))


#define TAF_XCALL_MAX_TIMER_ID_NUM                          (10)            /* XCALL的定时器最大个数 */
#define TAF_XCALL_INVAILD_CALL_ID                           (0)

#define TAF_XCALL_DTMF_BUF_MAX_CNT               (32)                            /* 最多缓存DTMF信息的个数 */

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
#define TAF_XCALL_ECC_KS_DATA_MAX_LEN                       (16)                /* ECC KS为128bit */
#define TAF_XCALL_MAX_OPID_NUM                              (3)                 /* 最大opId数目 */
#define TAF_XCALL_SIGN_DATA_INFO_LEN                        (13)
#define TAF_XCALL_SIGN_DATA_INFO_MAX_LEN                    (22)
#define TAF_XCALL_MEID_INFO_LEN                             (7)
#endif

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : TAF_XCALL_SO_TYPE_ENUM
 结构说明  : XCALL维护的SO
*****************************************************************************/
enum TAF_XCALL_SO_TYPE_ENUM
{
    TAF_XCALL_SO_3_EVRC                 = 0x0003,
    TAF_XCALL_SO_68_EVRC_B              = 0x0044,
    TAF_XCALL_SO_73_EVRC_NW             = 0x0049,

    TAF_XCALL_SO_BUTT                   = 0xFFFF
};
typedef VOS_UINT16 TAF_XCALL_SO_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : TAF_XCALL_CALL_SUB_STATE_ENUM
 结构说明  : 补充业务进展事件
*****************************************************************************/
enum TAF_XCALL_SS_PROGRESS_EVT_ENUM
{
    TAF_XCALL_SS_PROG_EVT_REL,                                                  /* 有呼叫被挂断 */

    TAF_XCALL_SS_PROG_EVT_ANS,                                                  /* 有呼叫在接听*/

    TAF_XCALL_SS_PROG_EVT_BUTT
};

typedef VOS_UINT8 TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_XCALL_CALL_SUB_STATE_ENUM
 结构说明  : 补充业务后续操作
*****************************************************************************/
enum TAF_XCALL_SS_SUBSEQ_OP_ENUM
{
    TAF_XCALL_SS_SUBSEQ_OP_RPT_SUCC,                                            /* 向应用层上报操作成功 */
    TAF_XCALL_SS_SUBSEQ_OP_RPT_FAIL,                                            /* 向应用层上报操作失败 */

    TAF_XCALL_SS_SUBSEQ_OP_BUTT
};

typedef VOS_UINT8 TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8;

/** ****************************************************************************
 枚举名    : TAF_XCALL_DIGIT_MODE_ENUM
 结构说明  : 号码编码模式
 *******************************************************************************/
enum TAF_XCALL_DIGIT_MODE_ENUM
{
    TAF_XCALL_DIGIT_MODE_DTMF           = 0x00,
    TAF_XCALL_DIGIT_MODE_ASCII          = 0x01,
    TAF_XCALL_DIGIT_MODE_BUTT           = 0x02
};
typedef VOS_UINT8 TAF_XCALL_DIGIT_MODE_ENUM_UINT8;

/** ****************************************************************************
 枚举名    : TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8
 结构说明  : 向xcc发送Burst DTMF或CONT DTMF后，设置等待标志，等待响应的类型
 *******************************************************************************/
enum TAF_XCALL_WAIT_XCC_CNF_TYPE
{
    TAF_XCALL_WAIT_NO_XCC_CNF               = 0x00,     /* 初始态，不等待XCC回复 */
    TAF_XCALL_WAIT_XCC_CNF_BURST_DTMF       = 0x01,     /* 等待XCC回复BURST DTMF REQ的响应 */
    TAF_XCALL_WAIT_XCC_CNF_START_CONT_DTMF  = 0x02,     /* 等待XCC回复START CONT DTMF REQ的响应 */
    TAF_XCALL_WAIT_XCC_CNF_STOP_CONT_DTMF   = 0x03,     /* 等待XCC回复STOP CONT DTMF REQ的响应 */
    TAF_XCALL_WAIT_XCC_CNF_BUFF
};
typedef VOS_UINT8 TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8;


#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 枚举名    : TAF_XCALL_VOICE_ENCRYPT_STA_ENUM
 枚举说明  : 密话密钥请求协商阶段状态枚举类型
 1.日    期   : 2015年10月22日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum TAF_XCALL_VOICE_ENCRYPT_STA_ENUM
{
    TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE,                               /* 密话状态机初始状态      */
    TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ORIG_REQ,                       /* 等待用户的ORIG请求状态  */
    TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_AP_ENCRYPT_REQ,                 /* 等待用户的密话请求状态  */
    TAF_XCALL_VOICE_ENCRYPT_STA_WATIING_CALL_ACCEPT_REQ,                /* 等待用户呼叫接听状态    */
    TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_TCH_ASSIGN_CMPL,                /* 等待TCH信道指派完成状态 */
    TAF_XCALL_VOICE_ENCRYPT_STA_DELAY_SEND_ENCRYPT_REQ,                 /* 延时密话请求发送状态    */
    TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP,                    /* 等待KMC的密话响应状态   */
    TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ECC_SERVICE_CNF,                /* 等待密话的SO协商状态    */
    TAF_XCALL_VOICE_ENCRYPT_STA_ENCRYPT_ACTIVE,                         /* 密话激活状态            */

    TAF_XCALL_VOICE_ENCRYPT_STA_BUTT
};
typedef VOS_UINT32 TAF_XCALL_VOICE_ENCRYPT_STA_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TAF_XCALL_K0_UPATE_STA_ENUM
 枚举说明  : KMC公钥更新状态枚举表
 1.日    期   : 2015年10月22日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum TAF_XCALL_K0_UPATE_STA_ENUM
{
    TAF_XCALL_K0_UPATE_STA_INACTIVE,                                    /* KMC公钥更新初始状态     */
    TAF_XCALL_K0_UPATE_STA_WAIT_KMC_RSP,                                /* 等待KMC公钥更新响应状态 */

    TAF_XCALL_K0_UPATE_STA_BUTT
};
typedef VOS_UINT32 TAF_XCALL_K0_UPATE_STA_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TAF_XCALL_REMOTE_CTRL_STA_ENUM
 枚举说明  : KMC远程控制操作状态枚举表
 1.日    期   : 2015年10月22日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum TAF_XCALL_REMOTE_CTRL_STA_ENUM
{
    TAF_XCALL_REMOTE_CTRL_STA_INACTIVE,                                 /* 远程控制操作初始态             */
    TAF_XCALL_REMOTE_CTRL_STA_WAITING_AP_INFO_ERASE_RSP,                /* 等待用户的安全信息擦除响应状态 */
    TAF_XCALL_REMOTE_CTRL_STA_WAITING_AP_PASSWORD_RESET_RSP,            /* 等待用户的密码重置响应状态     */
    TAF_XCALL_REMOTE_CTRL_STA_WAITING_RSP_SENT_RSLT,                    /* 等待的远程控制响应发送结果状态 */

    TAF_XCALL_REMOTE_CTRL_STA_BUTT
};
typedef VOS_UINT32 TAF_XCALL_REMOTE_CTRL_STA_ENUM_UINT32;
#endif

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
/*****************************************************************************
 结构名    : TAF_XCALL_CLIENT_INFO_STRU
 结构说明  : X CALL发起/接听用户的信息
 1.日    期   : 2014年9月03日
   作    者   : y00213812
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulModuleId;                             /* 发起呼叫操作的模块AT/STK */
    VOS_UINT16                          usClientId;                             /* Client ID */
    VOS_UINT8                           ucOpId;                                 /* Op ID */
    VOS_UINT8                           ucReserved;
}TAF_XCALL_CLIENT_INFO_STRU;

/*****************************************************************************
结构名    : TAF_XCALL_DTMF_BUFFER_STRU
结构说明  : XCALL模块用于保存BURST DTMF和CONT DTMF信息
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16 修改
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDtmfCnt;          /* 缓存的BURST DTMF和CONT DTMF消息数量 */
    VOS_UINT8                           aucReserved1[3];
    HI_LIST_S                           stList;
} TAF_XCALL_DTMF_BUFFER_STRU;


/*****************************************************************************
结构名    : TAF_XCALL_FLASH_INFO_STRU
结构说明  : XCALL模块用于保存flash信息
  1.日    期   : 2015年01月14日
    作    者   : m00312079
    修改内容   : 新生成
*****************************************************************************/
typedef struct
{
    TAF_XCALL_CLIENT_INFO_STRU          stClientInfo;
    MN_CALL_CALLED_NUM_STRU             stDialNumber;
    VOS_UINT8                           ucIsEmcCall;
    VOS_UINT8                           aucReserved[3];
} TAF_XCALL_FLASH_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_XCALL_CALL_ENTITY_STRU
 结构说明  : X CALL的呼叫实体信息
             为了便于以后整个CS CALL的优化，X CALL呼叫实体中的定义如果在MnCallApi.h中有定义，不再重新定义一套
 1.日    期   : 2014年9月03日
   作    者   : L60609
   修改内容   : 新增
 2.日    期   : 2015年8月18日
   作    者   : l00324781
   修改内容   : DTS2015081708770修改
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          ulUsed;                                 /* 是否已被使用 */
    TAF_XCALL_CLIENT_INFO_STRU          stClientInfo;                           /* 发起/接听用户的信息 */

    TAF_XCALL_SO_TYPE_ENUM_UINT16       enSo;
    VOS_UINT8                           ucIsAlertAnsByPass;                     /* MT */
    VOS_UINT8                           ucConRef;                               /* Connect Reference */
    VOS_UINT8                           ucConnectId;                            /* Connect Id */
    MN_CALL_STATE_ENUM_U8               enCallState;                            /* Call State */
    MN_CALL_TYPE_ENUM_U8                enCallType;                             /* Call Type */
    MN_CALL_DIR_ENUM_U8                 enCallDir;                              /* 发起呼叫的方向 */
    VOS_UINT8                           ucPi;
    VOS_UINT8                           ucSi;
    VOS_UINT8                           ucIsL2ErrReOrig;
    VOS_UINT8                           ucReOrigCount;
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                                /* Cause Value of the Call Control */

    MN_CALL_DISC_DIR                    stDiscDir;                              /* 挂断呼叫的方向 */

    MN_CALL_BCD_NUM_STRU                stCallNumber;                           /* Call Number 主叫号码 */
    MN_CALL_SUBADDR_STRU                stCallSubNumber;                        /* Call SubAddress */
    MN_CALL_CALLED_NUM_STRU             stCalledNumber;                         /* Called Number 被叫号码 */
    MN_CALL_SUBADDR_STRU                stCalledSubAddr;                        /* Called SubAddress */
    MN_CALL_BCD_NUM_STRU                stRedirectNumber;                       /* Redirect Number */
    MN_CALL_SUBADDR_STRU                stRedirectSubaddr;                      /* Redirect Call SubAddress */
    MN_CALL_BCD_NUM_STRU                stConnectNumber;                        /* Connect Number */
    TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8   enWaitForXCCDTMFCnfFlag;                /* 等待XCC的Burst DTMF或Cont Burst回复消息 */
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enLastReOrigErr;

    VOS_UINT8                           ucTchAssignInd;
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8    enPrivacyMode;                          /* 当前呼叫的privacy mode */

    TAF_XCALL_DTMF_BUFFER_STRU          stDtmfBuffer;                           /* BURST DTMF和CONT DTMF的缓存信息,公用一个缓存*/

    TAF_XCALL_FLASH_INFO_STRU           stFlashInfo;

    VOS_INT16                           sRssi;
    VOS_UINT16                          usReserved;
}TAF_XCALL_CALL_ENTITY_STRU;

/*****************************************************************************
 结构名    : TAF_XCALL_CS_ERR_CODE_MAP_STRU
 结构说明  : TAF XCAL与XCC原因值的对应结构
  1.日    期   : 2014年9月17日
    作    者   : L60609
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    TAF_CS_CAUSE_ENUM_UINT32            enCsCause;
    TAF_XCC_CAUSE_ENUM_UINT32           enXccCause;
}TAF_XCALL_CS_ERR_CODE_MAP_STRU;


/*****************************************************************************
 结构名    : MN_CALL_SUPS_CMD_ENUM_U8_KEY_EVT_STRU
 结构说明  : 被关注的补充业务操作事件 结构
 1.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : 新建

****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucCallId;           /* 产生事件的呼叫ID */
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt;              /* 事件的类型 */
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                       enSubseqOp;         /* 收到该事件的后续操作 */
    VOS_UINT8                                               ucRsved;
}TAF_XCALL_SUPS_CMD_KEY_EVT_STRU;

/*****************************************************************************
 结构名    : TAF_XCALL_SUPS_CMD_MGMT_STRU
 结构说明  : 补充业务管理结构
 1.日    期   : 2014年9月20日
   作    者   : L60609
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucNumOfKeyEvt;                      /* 关注的事件个数 */
    VOS_UINT8                               aucRsved[3];
    TAF_XCALL_SUPS_CMD_KEY_EVT_STRU         astKeyEvts[TAF_XCALL_MAX_SS_CMD_KEY_EVT_NUM];  /* 关注的事件 */
}TAF_XCALL_SUPS_CMD_MGMT_STRU;

/*****************************************************************************
 结构名    : TAF_XCALL_CONFIG_STRU
 结构说明  : 用户配置信息结构
 1.日    期   : 2014年9月20日
   作    者   : Y00213812
   修改内容   : 新增
 2.日    期   : 2015年8月18日
   作    者   : l00324781
   修改内容   : DTS2015081708770增加NV配置项
*****************************************************************************/
typedef struct
{
    TAF_XCALL_DIGIT_MODE_ENUM_UINT8     enDigitMode;

    VOS_UINT8                           ucRsved;

    TAF_XCALL_SO_TYPE_ENUM_UINT16       enSoInitType;

    VOS_UINT32                          ulEmcRedialPeriod;      /* 紧急呼重播定时器时长 */
    VOS_UINT32                          ulStartAndStopContDtmfIntervalLen;  /* Stop Cont DTMF和Start Cont DTMF命令发送时间间隔定时器时长，单位:ms */
    VOS_UINT32                          ulCallBackEnableFlg;
}TAF_XCALL_CONFIG_STRU;

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 结构名    : TAF_XCALL_ECC_SRV_CAP_STRU
 结构说明  : ECC服务能力参数信息。
             注: ECC业务状态仅在ECC业务能力支持的情况下，才有效。

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEccSrvCap;        /* ECC服务能力: TRUE -- 支持ECC服务，FALSE -- 不支持ECC服务 */
    VOS_UINT8                           ucEccSrvStatus;     /* ECC服务状态: TRUE -- ECC服务打开，FALSE -- ECC服务关闭 */
    VOS_UINT8                           aucReserved[2];
}TAF_XCALL_ECC_SRV_CAP_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_XCALL_ECC_PUB_KEY_INFO_STRU
 结构说明  : ECC公钥信息，包含公钥K0以及对应的版本号

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucVerNum;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucPubKey[TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN];
}TAF_XCALL_ECC_PUB_KEY_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_XCALL_KS_INFO_STRU
 结构说明  : KS信息，包含公钥KS以及KS长度

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucKsLen;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucKs[TAF_XCALL_ECC_KS_DATA_MAX_LEN];
}TAF_XCALL_KS_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_XCALL_ENCRYPT_VOICE_DATA_CTX
 结构说明  : 密话相关的数据上下文结构定义

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : y00245242
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usDelayEncVoiceReqTimerLen;             /* 延时密话请求发送时长 */
    VOS_UINT16                                              usRemoteCtrlAnswerTimerLen;             /* 远程控制应答时长 */
    TAF_XCALL_ECC_SRV_CAP_INFO_STRU                         stEccSrvCapInfo;                        /* ECC服务能力信息 */
    TAF_XCALL_ECC_PUB_KEY_INFO_STRU                         stEccPubKeyInfo;                        /* ECC公钥信息 */
    TAF_STD_TIME_ZONE_TYPE_STRU                             stLastInfoEraseTime;                    /* ECC安全信息擦除时间 */
    TAF_STD_TIME_ZONE_TYPE_STRU                             stLastPassworResetTime;                 /* ECC密码重置擦除时间 */
    TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT32               enTestMode;                             /* 当前测试模式*/
}TAF_XCALL_ENCRYPT_VOICE_PARA_INFO_CTX;

/*****************************************************************************
 结构名    : TAF_XCALL_KS_NEGOTIATE_CTX
 结构说明  : 密话的KS协商过程中的上下文数据定义

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : y00245242
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    TAF_XCALL_VOICE_ENCRYPT_STA_ENUM_UINT32                 enVoiceEncState;                        /* 密话中密钥协商过程中的状态 */
    TAF_XCALL_KMC_PUB_KEY_STRU                              stTmpPubKey;                            /* 临时公钥 */
    TAF_XCALL_KMC_PRIV_KEY_STRU                             stTmpPrivKey;                           /* 临时私钥 */
    TAF_ECC_CALL_BCD_NUM_STRU                               stCallNum;
    TAF_CALL_APP_ENCRYPT_VOICE_TYPE_ENUM_UINT32             enEccVoiceType;
    TAF_XCALL_KS_INFO_STRU                                  stKsInfo;                               /* KS数据 */
    VOS_UINT16                                              usWaitXsmsCnfOpId;
    VOS_UINT8                                               ucCallId;                               /* 记录当前激活call id标识 */
    VOS_UINT8                                               aucReserved[1];
    TAF_CCA_CTRL_STRU                                       stCcaCtrl;
}TAF_XCALL_KS_NEGOTIATE_CTX;


/*****************************************************************************
 结构名    : TAF_XCALL_REMOTE_CTRL_CTX
 结构说明  : KMC远程控制流程中的上下文定义

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : y00245242
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    TAF_XCALL_REMOTE_CTRL_STA_ENUM_UINT32                   enRemoteCtrlState;
    VOS_UINT16                                              usWaitXsmsCnfOpId;
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM_UINT8       enRemoteCtrlCmdType;
    VOS_UINT8                                               ucReserved;
    TAF_STD_TIME_ZONE_TYPE_STRU                             stTimeStamp;
    TAF_CCA_CTRL_STRU                                       stCcaCtrl;
}TAF_XCALL_REMOTE_CTRL_CTX;

/*****************************************************************************
 结构名    : TAF_XCALL_PUBLIC_KEY_UPDATE_CTX
 结构说明  : KMC公钥更新流程中的上下文定义
 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : y00245242
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    TAF_XCALL_K0_UPATE_STA_ENUM_UINT32                      enK0UpdateState;    /*  */
    VOS_UINT16                                              usWaitXsmsCnfOpId;
    VOS_UINT8                                               ucPubKeyVerNum;
    VOS_UINT8                                               aucPubKey[TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN];
    VOS_UINT8                                               aucRandomData[TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN];
    VOS_UINT8                                               ucReserved;
}TAF_XCALL_PUBLIC_KEY_UPDATE_CTX;


/*****************************************************************************
 结构名    : TAF_XCALL_XSMS_SEND_REQ_OPID_MGMT_CTX_STRU
 结构说明  : 短信发送请求OPID管理上下文信息

 修改历史      :
  1.日    期   : 2015年10月27日
    作    者   : y00245242
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usOpIdSeqNum;                         /* opId序列号 */
    VOS_UINT8                           aucReserved[2];
}TAF_XCALL_XSMS_SEND_REQ_OPID_MGMT_CTX;

/*****************************************************************************
 结构名    : TAF_XCALL_ENC_VOICE_CTX_STRU
 结构说明  : 语音加密上下文数据结构

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : y00245242
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    TAF_XCALL_XSMS_SEND_REQ_OPID_MGMT_CTX                   stOpIdMgmtCtx;      /* OPID管理上下文定义 */
    TAF_XCALL_ENCRYPT_VOICE_PARA_INFO_CTX                   stEncVoiceInfoCtx;  /* 密话参数信息上下文定义 */
    TAF_XCALL_KS_NEGOTIATE_CTX                              stNegotiateCtx;     /* 密话KS协商流程中的上下文 */
    TAF_XCALL_REMOTE_CTRL_CTX                               stRemoteCtrlCtx;    /* KMC远程控制流程中的上下文 */
    TAF_XCALL_PUBLIC_KEY_UPDATE_CTX                         stPubKeyUpdateCtx;  /* 公钥更新流程中的上下文 */
}TAF_XCALL_ENCRYPT_VOICE_CTX_STRU;
#endif

/*****************************************************************************
 结构名    : TAF_XCALL_CTX_STRU
 结构说明  : X CALL的上下文信息
 1.日    期   : 2014年9月09日
   作    者   : L60609
   修改内容   : 新增
 2.日    期   : 2014年11月17日
   作    者   : w00176964
   修改内容   : 1X迭代5增加
 3.日    期   : 2015年10月22日
   作    者   : y00245242
   修改内容   : 1X迭代19增加
*****************************************************************************/
typedef struct
{
    TAF_XCALL_CALL_ENTITY_STRU          astCallEntity[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    TAF_XCALL_SUPS_CMD_MGMT_STRU        stSupsCmdMgmt;
    TAF_XCALL_CONFIG_STRU               stConfig;
    TAF_XCALL_TIMER_CTX_STRU            astTimerCtx[TAF_XCALL_MAX_TIMER_ID_NUM];

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    TAF_XCALL_ENCRYPT_VOICE_CTX_STRU    stEncVoiceCtx;
#endif
}TAF_XCALL_CTX_STRU;


/*****************************************************************************
结构名    : TAF_XCALL_DTMF_NODE_UNION
结构说明  : CALL模块DTMF缓存消息内容结构，缓存Cont DTMF和Burst DTMF
1.日    期   : 2015年7月29日
  作    者   : l00324781
  修改内容   : Iter16新增

*****************************************************************************/
typedef union
{
    TAF_CALL_BURST_DTMF_PARA_STRU   stBurstDtmf;
    TAF_CALL_CONT_DTMF_PARA_STRU    stContDtmf;
}TAF_XCALL_DTMF_NODE_UNION;

/*****************************************************************************
结构名    : TAF_XCALL_DTMF_NODE_STRU
结构说明  : CALL模块DTMF缓存链表节点结构，缓存Cont DTMF和Burst DTMF
1.日    期   : 2015年7月29日
  作    者   : l00324781
  修改内容   : Iter16新增

*****************************************************************************/
typedef struct
{
    TAF_XCALL_DTMF_NODE_UNION                    unDtmf;        /* 缓存Buffer,Burst DTMF或CONT DTMF */
    AT_MN_MSGTYPE_ENUM_UINT16                    enMsgType;     /* 缓存的消息类型 */
    VOS_UINT8                                    aucRsved[2];
    HI_LIST_S                                    stList;
} TAF_XCALL_DTMF_NODE_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
TAF_XCALL_CTX_STRU* TAF_XCALL_GetCtxAddr(VOS_VOID);

VOS_VOID TAF_XCALL_InitCtx(VOS_VOID);

VOS_UINT32 TAF_XCALL_AllocCallId(
    VOS_UINT8                      *pucCallId
);

VOS_UINT32 TAF_XCALL_IsAllowMoCallInCurrentStatus(
    MN_CALL_TYPE_ENUM_U8                enCallType
);


VOS_VOID TAF_XCALL_CreateMoCallEntity(
    VOS_UINT8                           ucCallId,
    MN_CALL_APP_REQ_MSG_STRU           *pstOrigPara
);

VOS_VOID TAF_XCALL_CreateMtCallEntity(
    VOS_UINT8                           ucCallId,
    VOS_UINT32                          ulModuleId,
    XCC_XCALL_INCOMING_CALL_IND_STRU   *pstIncomingCallInd
);

VOS_VOID TAF_XCALL_FreeCallEntity(
    VOS_UINT8                           ucCallId
);

VOS_UINT32 TAF_XCALL_IsAvailCallId(
    VOS_UINT8                           ucCallId
);

VOS_UINT32 TAF_XCALL_IsAvailVoiceCallSo(
    VOS_UINT16                          usSo
);

VOS_VOID TAF_XCALL_UpdateCallState(
    VOS_UINT8                           ucCallId,
    MN_CALL_STATE_ENUM_U8               enCallState
);

VOS_VOID TAF_XCALL_UpdateCallType(
    VOS_UINT8                           ucCallId,
    MN_CALL_TYPE_ENUM_U8                enCallType
);

VOS_VOID TAF_XCALL_UpdateCallDir(
    VOS_UINT8                           ucCallId,
    MN_CALL_DIR_ENUM_U8                 enCallDir
);

VOS_VOID TAF_XCALL_UpdateSo(
    VOS_UINT8                           ucCallId,
    TAF_XCALL_SO_TYPE_ENUM_UINT16       enSo
);

VOS_VOID TAF_XCALL_UpdateConnectId(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConnectId
);

VOS_VOID TAF_XCALL_UpdateConnectRef(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConRef
);

VOS_VOID TAF_XCALL_UpdateAlertAnsByPassFlg(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucIsAlertAnsByPass
);

VOS_VOID TAF_XCALL_UpdateCcCause(
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCcCause
);

VOS_VOID TAF_XCALL_UpdateDiscCallDir(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucIsUser
);

VOS_VOID TAF_XCALL_UpdateCallingNum(
    VOS_UINT8                                               ucCallId,
    XCC_XCALL_CALLING_PARTY_NUM_INFO_STRU                  *pstXccCallNum
);

TAF_XCALL_SUPS_CMD_MGMT_STRU* TAF_XCALL_GetSupsCmdMgmt(VOS_VOID);

TAF_XCALL_CLIENT_INFO_STRU* TAF_XCALL_GetClientInfo(
    VOS_UINT8                           ucCallId
);

TAF_XCALL_SO_TYPE_ENUM_UINT16 TAF_XCALL_GetSo(
    VOS_UINT8                           ucCallId
);

MN_CALL_STATE_ENUM_U8 TAF_XCALL_GetCallState(
    VOS_UINT8                           ucCallId
);

MN_CALL_TYPE_ENUM_U8 TAF_XCALL_GetCallType(
    VOS_UINT8                           ucCallId
);

VOS_UINT8 TAF_XCALL_GetAlertAnsByPassFlg(
    VOS_UINT8                           ucCallId
);

TAF_CS_CAUSE_ENUM_UINT32 TAF_XCALL_GetCcCause(
    VOS_UINT8                           ucCallId
);

VOS_UINT32 TAF_XCALL_GetCallIdFromConnectId(
    VOS_UINT8                           ucConnectId,
    VOS_UINT8                          *pucCallId
);

VOS_VOID TAF_XCALL_GetCallsByState(
    MN_CALL_STATE_ENUM_U8               enCallState,
    VOS_UINT32                         *pulNumOfCalls,
    VOS_UINT8                          *pucCallIds
);

VOS_VOID TAF_XCALL_GetNotIdleStateCalls(
    VOS_UINT32                         *pulNumOfCalls,
    VOS_UINT8                          *pucCallIds
);

VOS_VOID TAF_XCALL_UpdateClientInfo(
    VOS_UINT8                           ucCallId,
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

TAF_XCALL_CALL_ENTITY_STRU* TAF_XCALL_GetCallEntityAddr(
    VOS_UINT8                           ucCallId
);

TAF_CS_CAUSE_ENUM_UINT32 TAF_XCALL_MapXccCauseToCsCause(
    TAF_XCC_CAUSE_ENUM_UINT32           enXccCause
);

VOS_UINT32 TAF_XCALL_ExistCallInstance(VOS_VOID);

VOS_VOID TAF_XCALL_RegSsKeyEvent(
    VOS_UINT8                                               ucCallId,
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt,
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                       enSubseqOp
);

VOS_VOID TAF_XCALL_DeRegSsKeyEvent(
    VOS_UINT8                                               ucCallId,
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt
);


VOS_VOID TAF_XCALL_GetSsKeyEvent(
    VOS_UINT8                                               ucCallId,
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                   *penEvt,
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                      *penSubseqOp
);

VOS_VOID TAF_XCALL_UpdateDigitMode(
    TAF_XCALL_DIGIT_MODE_ENUM_UINT8     enDigitMode
);

TAF_XCALL_CONFIG_STRU* TAF_XCALL_GetConfigInfo(VOS_VOID);

VOS_VOID TAF_XCALL_SetWaitForXCCDTMFCnfFlag(
    VOS_UINT8                           ucCallId,
    TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8   enWaitForXCCDTMFCnfFlag
);

TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8 TAF_XCALL_GetWaitForXCCDTMFCnfFlag(
    VOS_UINT8       ucCallId
);

VOS_UINT32 TAF_XCALL_IsMtCallInstanceExist(VOS_VOID);

TAF_XCALL_TIMER_CTX_STRU*  TAF_XCALL_GetTimerCtxAddr( VOS_VOID );

MN_CALL_DIR_ENUM_U8 TAF_XCALL_GetCallDir(
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_TranlatePlusToCallNum(
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity
);

#if 0
VOS_VOID TAF_XCALL_TranlateCallNumToPlus(
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity
);
#endif


VOS_VOID TAF_XCALL_GetEccNumList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
);

/*  修改内容:
   1. Buffer操作函数从XCallProcApp挪到XCallCtx.c中
   2. Cont DTMF和Burst DTMF公用一个缓存
*/

extern TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_AddBurstDtmfInfo(
    TAF_CALL_BURST_DTMF_REQ_MSG_STRU   *pstBurstDtmfInfo
);

extern TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SaveBurstDtmfInfo(
    TAF_CALL_BURST_DTMF_REQ_MSG_STRU   *pstBurstDtmfInfo
);

extern VOS_VOID TAF_XCALL_ProcDtmfBuffer(VOS_UINT8 ucCallId);

extern VOS_VOID TAF_XCALL_CleanDtmfBuff(VOS_UINT8   ucCallId);

extern VOS_VOID TAF_XCALL_DelDtmfNode(
    TAF_XCALL_DTMF_NODE_STRU     *pstNode,
    VOS_UINT8                     ucCallId
);

extern HI_LIST_S* TAF_XCALL_GetDtmfBuffListHead(VOS_UINT8   ucCallId);

extern VOS_VOID TAF_XCALL_IncrementDtmfBufCnt(VOS_UINT8   ucCallId);

extern VOS_VOID TAF_XCALL_DecrementDtmfBufCnt(VOS_UINT8   ucCallId);

extern VOS_UINT8 TAF_XCALL_GetDtmfBufCnt(VOS_UINT8   ucCallId);





TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_AddContDtmfInfo(
    TAF_CALL_CONT_DTMF_REQ_MSG_STRU    *pstContDtmfInfo
);

TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SaveContDtmfInfo(
    TAF_CALL_CONT_DTMF_REQ_MSG_STRU    *pstContDtmfInfo
);


VOS_UINT32 TAF_XCALL_GetStartAndStopContDtmfIntervalLen(VOS_VOID);

VOS_UINT32 TAF_XCALL_GetAllUsedCallId(
    VOS_UINT8                          *pucCallIds
);

VOS_VOID TAF_XCALL_SetCsCallExistFlg(
    VOS_UINT8                           ucCallExitFlg,
    MN_CALL_TYPE_ENUM_U8                enCallType
);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_VOID TAF_XCALL_InitEncVoiceCtx(VOS_VOID);

VOS_VOID TAF_XCALL_InitEncVoiceKeyNegotiateCtx(VOS_VOID);

VOS_VOID TAF_XCALL_InitEncVoiceRemoteCtrlCtx(VOS_VOID);

VOS_VOID TAF_XCALL_InitEncVoiceOpIdMgmtCtx(VOS_VOID);

VOS_VOID TAF_XCALL_InitEncVoiceParaInfoCtx(VOS_VOID);

TAF_XCALL_ENCRYPT_VOICE_PARA_INFO_CTX* TAF_XCALL_GetEncVoiceInfoCtxAddr(VOS_VOID);

TAF_XCALL_ENCRYPT_VOICE_CTX_STRU* TAF_XCALL_GetVoiceEncryptCtxAddr(VOS_VOID);

TAF_XCALL_XSMS_SEND_REQ_OPID_MGMT_CTX* TAF_XCALL_GetOpIdMgmtCtxAddr(VOS_VOID);

TAF_XCALL_REMOTE_CTRL_CTX* TAF_XCALL_GetRemoteCtrlCtxAddr(VOS_VOID);

TAF_XCALL_KS_NEGOTIATE_CTX* TAF_XCALL_GetKsNegotiateCtxAddr(VOS_VOID);

TAF_XCALL_VOICE_ENCRYPT_STA_ENUM_UINT32 TAF_XCALL_GetVoiceEncryptNegotiateState(VOS_VOID);

TAF_XCALL_ECC_PUB_KEY_INFO_STRU* TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber( VOS_VOID );

TAF_XCALL_ECC_SRV_CAP_INFO_STRU* TAF_XCALL_GetVoiceEncryptCapCfgPara( VOS_VOID );

TAF_STD_TIME_ZONE_TYPE_STRU* TAF_XCALL_GetVoiceEncryptSecInfoEraseSysTime( VOS_VOID );

TAF_STD_TIME_ZONE_TYPE_STRU* TAF_XCALL_GetVoiceEncryptPassWordResetSysTime( VOS_VOID );

VOS_UINT16 TAF_XCALL_GetVoiceEncryptReqDelaySendTimerLen( VOS_VOID );

VOS_UINT16 TAF_XCALL_GetRemoteCtrlWaitApAnswerTimerLen(VOS_VOID);

TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT32 TAF_XCALL_GetVoiceEncryptTestMode( VOS_VOID );

TAF_XCALL_PUBLIC_KEY_UPDATE_CTX* TAF_XCALL_GetPubKeyUpdateCtxAddr( VOS_VOID );

VOS_VOID TAF_XCALL_InitEncVoiceKmcUpdateCtx(VOS_VOID);
#endif
VOS_VOID TAF_XCALL_UpdatePrivacyMode(
    VOS_UINT8                           ucCallId,
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8    enPrivacyMode
);
#endif


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

#endif /* end of TafXCallCtx.h */


