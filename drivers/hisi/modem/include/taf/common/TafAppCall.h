/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafAppCall.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2015年10月22日
  最近修改   :
  功能描述   : AT/APP与CALL接口头文件定义
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月22日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_APP_CALL_H__
#define __TAF_APP_CALL_H__

#include "vos.h"
#include "MnCallApi.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/



/* 注: 这里临时定义一个消息基地址，等后续把所有AT与CALL模块其他消息都移到该头文
       件后，消息基地址需要重新调整。目前基地址参考TafInternalInterface.h中
       ID_TAF_CALL_INTERNAL_BASE地址定义!!!
 */
#define TAF_CALL_APP_MSG_START_BASE                         (0x3100)
#define TAF_XCALL_MAX_NUM                                   (2)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : TAF_CCA_MSG_TYPE_ENUM_UINT32
 枚举说明  : APP到TAF的消息类型定义
 1.日    期   : 2015年10月22日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum TAF_CCA_MSG_TYPE_ENUM
{
    ID_TAF_CALL_MSG_TYPE_BEGIN                              = TAF_CALL_APP_MSG_START_BASE,

    /* 自动/手动密话相关消息 */
    ID_TAF_CALL_APP_ENCRYPT_VOICE_REQ,                      /* _H2ASN_MsgChoice TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU *//**< @sa TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU */
    ID_TAF_CALL_APP_ENCRYPT_VOICE_CNF,                      /* _H2ASN_MsgChoice TAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU *//**< @sa TAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU */
    ID_TAF_CALL_APP_ENCRYPT_VOICE_IND,                      /* _H2ASN_MsgChoice TAF_CALL_APP_ENCRYPT_VOICE_IND_STRU *//**< @sa TAF_CALL_APP_ENCRYPT_VOICE_IND_STRU */

    /* KMC远程控制相关消息 */
    ID_TAF_CALL_APP_EC_REMOTE_CTRL_IND,                     /* _H2ASN_MsgChoice TAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU *//**< @sa TAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU */
    ID_TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ,                 /* _H2ASN_MsgChoice TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU *//**< @sa TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU */
    ID_TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF,                 /* _H2ASN_MsgChoice TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU *//**< @sa TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU */

    /* 密话业务能力配置与查询消息 */
    ID_TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ,                    /* _H2ASN_MsgChoice TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU *//**< @sa TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU */
    ID_TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF,                    /* _H2ASN_MsgChoice TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU *//**< @sa TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU */
    ID_TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ,                    /* _H2ASN_MsgChoice TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU *//**< @sa TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU */
    ID_TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF,                    /* _H2ASN_MsgChoice TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU *//**< @sa TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU */

    /* 密话测试模式设置消息 */
    ID_TAF_CALL_APP_SET_EC_TEST_MODE_REQ,                   /* _H2ASN_MsgChoice TAF_CALL_APP_SET_EC_TEST_MODE_REQ_STRU *//**< @sa TAF_CALL_APP_SET_EC_TEST_MODE_REQ_STRU */
    ID_TAF_CALL_APP_SET_EC_TEST_MODE_CNF,                   /* _H2ASN_MsgChoice TAF_CALL_APP_SET_EC_TEST_MODE_CNF_STRU *//**< @sa TAF_CALL_APP_SET_EC_TEST_MODE_CNF_STRU */
    ID_TAF_CALL_APP_GET_EC_TEST_MODE_REQ,                   /* _H2ASN_MsgChoice TAF_CALL_APP_GET_EC_TEST_MODE_REQ_STRU *//**< @sa TAF_CALL_APP_GET_EC_TEST_MODE_REQ_STRU */
    ID_TAF_CALL_APP_GET_EC_TEST_MODE_CNF,                   /* _H2ASN_MsgChoice TAF_CALL_APP_GET_EC_TEST_MODE_CNF_STRU *//**< @sa TAF_CALL_APP_GET_EC_TEST_MODE_CNF_STRU */

    /* 测试模式下随机数获取消息 */
    ID_TAF_CALL_APP_GET_EC_RANDOM_REQ,                      /* _H2ASN_MsgChoice TAF_CALL_APP_GET_EC_RANDOM_REQ_STRU *//**< @sa TAF_CALL_APP_GET_EC_RANDOM_REQ_STRU */
    ID_TAF_CALL_APP_GET_EC_RANDOM_CNF,                      /* _H2ASN_MsgChoice TAF_CALL_APP_GET_EC_RANDOM_CNF_STRU *//**< @sa TAF_CALL_APP_GET_EC_RANDOM_CNF_STRU */

    /* 测试模式下KMC公钥与公钥版本号获取消息 */
    ID_TAF_CALL_APP_GET_EC_KMC_REQ,                         /* _H2ASN_MsgChoice TAF_CALL_APP_GET_EC_KMC_REQ_STRU *//**< @sa TAF_CALL_APP_GET_EC_KMC_REQ_STRU */
    ID_TAF_CALL_APP_GET_EC_KMC_CNF,                         /* _H2ASN_MsgChoice TAF_CALL_APP_GET_EC_KMC_CNF_STRU *//**< @sa TAF_CALL_APP_GET_EC_KMC_CNF_STRU */

    /* 测试模式下KMC公钥与公钥版本号设置消息 */
    ID_TAF_CALL_APP_SET_EC_KMC_REQ,                         /* _H2ASN_MsgChoice TAF_CALL_APP_SET_EC_KMC_REQ_STRU *//**< @sa TAF_CALL_APP_SET_EC_KMC_REQ_STRU */
    ID_TAF_CALL_APP_SET_EC_KMC_CNF,                         /* _H2ASN_MsgChoice TAF_CALL_APP_SET_EC_KMC_CNF_STRU *//**< @sa TAF_CALL_APP_SET_EC_KMC_CNF_STRU */

    ID_TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND,               /* _H2ASN_MsgChoice TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND_STRU *//**< @sa TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND_STRU */

    ID_TAF_CALL_APP_PRIVACY_MODE_SET_REQ,                       /* _H2ASN_MsgChoice TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU *//**< @sa TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU */
    ID_TAF_CALL_APP_PRIVACY_MODE_SET_CNF,                       /* _H2ASN_MsgChoice TAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU *//**< @sa TAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU */
    ID_TAF_CALL_APP_PRIVACY_MODE_QRY_REQ,                       /* _H2ASN_MsgChoice TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU *//**< @sa TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU */
    ID_TAF_CALL_APP_PRIVACY_MODE_QRY_CNF,                       /* _H2ASN_MsgChoice TAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU *//**< @sa TAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU */
    ID_TAF_CALL_APP_PRIVACY_MODE_IND,                           /* _H2ASN_MsgChoice TAF_CALL_APP_PRIVACY_MODE_ACT_IND_STRU *//**< @sa TAF_CALL_APP_PRIVACY_MODE_IND_STRU */

    ID_TAF_CALL_APP_TYPE_BUTT
};
typedef VOS_UINT32 TAF_CCA_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
结构名      : TAF_CALL_REMOTE_CTRL_APP_TYPE_ENUM_UINT8
结构说明    : ECC远程控制类型枚举值
  1.日    期   : 2015年10月16日
    作    者   : y00322978
    修改内容   : 新生成函数
*****************************************************************************/
enum TAF_CALL_REMOTE_CTRL_APP_TYPE_ENUM
{
    TAF_CALL_REMOTE_CTRL_SEC_INFO_ERASE = 0,
    TAF_CALL_REMOTE_CTRL_PASSWORD_RESET = 1,
    TAF_CALL_REMOTE_CTRL_OTHER          = 2,

    TAF_CALL_REMOTE_CTRL_APP_TYPE_BUTT
};
typedef VOS_UINT32   TAF_CALL_REMOTE_CTRL_APP_TYPE_ENUM_UINT32;

/*****************************************************************************
结构名      : TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_ENUM_UINT32
结构说明    : ECC远程控制类型枚举值
  1.日    期   : 2015年10月16日
    作    者   : y00322978
    修改内容   : 新生成函数
*****************************************************************************/
enum TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_ENUM
{
    TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_SUCC = 0,
    TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_FAIL,

    TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_BUTT

};
typedef VOS_UINT32   TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_ENUM_UINT32;

/*****************************************************************************
结构名      : TAF_CALL_REMOTE_CTRL_APP_RESULT_ENUM_UINT8
结构说明    : ECC远程控制类型枚举值
  1.日    期   : 2015年10月16日
    作    者   : y00322978
    修改内容   : 新生成函数
*****************************************************************************/
enum TAF_CALL_REMOTE_CTRL_APP_RESULT_ENUM
{
    TAF_CALL_REMOTE_CTRL_APP_SUCC = 0,
    TAF_CALL_REMOTE_CTRL_APP_FAIL,

    TAF_CALL_REMOTE_CTRL_APP_RESULT_BUTT
};
typedef VOS_UINT32 TAF_CALL_REMOTE_CTRL_APP_RESULT_ENUM_UINT32;

/*****************************************************************************
结构名      : TAF_CALL_REMOTE_CTRL_OPER_RESULT_ENUM_UINT32
结构说明    : ECC远程控制操作结果类型
  1.日    期   : 2015年10月26日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
enum TAF_CALL_REMOTE_CTRL_OPER_RESULT_ENUM
{
    TAF_CALL_SEND_RESULT_SUCC               = 0x00,
    TAF_CALL_SEND_RESULT_FAIL               = 0x01,
    TAF_CALL_SEND_RESULT_XSMS_POOL_FULL     = 0x02,
    TAF_CALL_SEND_RESULT_XSMS_LINK_ERR      = 0x03,
    TAF_CALL_SEND_RESULT_XSMS_NO_TL_ACK     = 0x04,
    TAF_CALL_SEND_RESULT_XSMS_ENCODE_ERR    = 0x05,
    TAF_CALL_SEND_RESULT_OPER_NOT_ALLOWED   = 0x06,
    TAF_CALL_SEND_RESULT_OPER_TYPE_ERROR    = 0x07,
    TAF_CALL_SEND_RESULT_INT_ERRROR         = 0x08,

    TAF_CALL_REMOTE_CTRL_OPER_RESULT_BUTT
};
typedef VOS_UINT32 TAF_CALL_REMOTE_CTRL_OPER_RESULT_ENUM_UINT32;

/*****************************************************************************
结构名      : TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT8
结构说明    : ECC平台能力枚举
  1.日    期   : 2015年10月16日
    作    者   : y00322978
    修改内容   : 新生成函数
*****************************************************************************/
enum TAF_CALL_APP_ECC_SRV_CAP_ENUM
{
    TAF_CALL_APP_ECC_SRV_CAP_DISABLE = 0,
    TAF_CALL_APP_ECC_SRV_CAP_NO_CHANGE,
    TAF_CALL_APP_ECC_SRV_CAP_ENABLE,

    TAF_CALL_APP_ECC_SRV_CAP_BUTT
};
typedef VOS_UINT32   TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT32;
/*****************************************************************************
结构名      : TAF_CALL_APP_ECC_SRV_STATUS_ENUM_UINT8
结构说明    : ECC平台能力枚举
  1.日    期   : 2015年10月16日
    作    者   : y00322978
    修改内容   : 新生成函数
*****************************************************************************/
enum TAF_CALL_APP_ECC_SRV_STATUS_ENUM
{
    TAF_CALL_APP_ECC_SRV_STATUS_CLOSE = 0,
    TAF_CALL_APP_ECC_SRV_STATUS_OPEN,

    TAF_CALL_APP_ECC_SRV_STATUS_BUTT
};
typedef VOS_UINT32   TAF_CALL_APP_ECC_SRV_STATUS_ENUM_UINT32;

/*****************************************************************************
结构名      : TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT8
结构说明    : ECC测试模式状态值
  1.日    期   : 2015年10月16日
    作    者   : y00322978
    修改内容   : 新生成函数
*****************************************************************************/
enum TAF_CALL_APP_SET_EC_TEST_MODE_ENUM
{
    TAF_CALL_APP_SET_EC_TEST_MODE_DISABLE = 0,
    TAF_CALL_APP_SET_EC_TEST_MODE_ENABLE,

    TAF_CALL_APP_SET_EC_TEST_MODE_BUTT
};
typedef VOS_UINT32   TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT32;

/*****************************************************************************
结构名      : TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32
结构说明    : ecc密话建立结果
  1.日    期   : 2015年10月16日
    作    者   : y00322978
    修改内容   : 新生成函数
*****************************************************************************/
enum TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM
{
    TAF_CALL_APP_ENCRYPT_VOICE_SUCC                     = 0x0000,

    /* KMC错误通知起始原因值 */
    TAF_CALL_APP_ENCRYPT_VOICE_TIMEOUT,
    TAF_CALL_APP_ENCRYPT_VOICE_LOCAL_TERMINAL_NO_AUTHORITY,
    TAF_CALL_APP_ENCRYPT_VOICE_REMOTE_TERMINAL_NO_AUTHORITY,
    TAF_CALL_APP_ENCRYPT_VOICE_LOCAL_TERMINAL_ILLEGAL,
    TAF_CALL_APP_ENCRYPT_VOICE_REMOTE_TERMINAL_ILLEGAL,
    TAF_CALL_APP_ENCRYPT_VOICE_UNKNOWN_ERROR,

    /* 签名验证失败 */
    TAF_CALL_APP_ENCRYPT_VOICE_SIGNTURE_VERIFY_FAILURE,

    /* 被叫密话指示 */
    TAF_CALL_APP_ENCRYPT_VOICE_MT_CALL_NOTIFICATION,

    /***********************************************************************************************
     * 以下统一归为内部错误
     **********************************************************************************************/
    /* XSMS的起始原因值 */
    TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_FAIL     = 0x1000,
    TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_POOL_FULL,
    TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_LINK_ERR,
    TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_NO_TL_ACK,
    TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_ENCODE_ERR,
    TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_UNKNOWN,

    /* 其他XCALL内部原因值 */
    TAF_CALL_APP_ENCRYPT_VOICE_SO_NEGO_FAILURE           = 0x2000,
    TAT_CALL_APP_ENCRYPT_VOICE_TWO_CALL_ENTITY_EXIST,
    TAF_CALL_APP_ENCRYPT_VOICE_NO_MO_CALL,
    TAF_CALL_APP_ENCRYPT_VOICE_NO_MT_CALL,
    TAF_CALL_APP_ENCRYPT_VOICE_NO_CALL_EXIST,
    TAF_CALL_APP_ENCRYPT_VOICE_CALL_STATE_NOT_ALLOWED,
    TAF_CALL_APP_ENCRYPT_VOICE_CALL_NUM_MISMATCH,
    TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_STATE_MISMATCH,
    TAF_CALL_APP_ENCRYPT_VOICE_MSG_ENCODE_FAILUE,
    TAF_CALL_APP_ENCRYPT_VOICE_MSG_DECODE_FAILUE,
    TAF_CALL_APP_ENCRYPT_VOICE_GET_TEMP_PUB_PIVA_KEY_FAILURE,
    TAF_CALL_APP_ENCRYPT_VOICE_FILL_CIPHER_TEXT_FAILURE,
    TAF_CALL_APP_ENCRYPT_VOICE_ECC_CAP_NOT_SUPPORTED,
    TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_MODE_UNKNOWN,
    TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_MODE_MIMATCH,
    TAF_CALL_APP_ENCRYPT_VOICE_CALL_RELEASED,
    TAF_CALL_APP_ENCRYPT_VOICE_CALL_ANSWER_REQ_FAILURE,
    TAF_CALL_APP_ENCRYPT_VOICE_DECRYPT_KS_FAILURE,
    TAF_CALL_APP_ENCRYPT_VOICE_FAILURE_CAUSED_BY_INCOMING_CALL,
    TAF_CALL_APP_ENCRYPT_VOICE_INIT_VOICE_FUNC_FAILURE,
    TAF_CALL_APP_ENCRYPT_VOICE_TX01_TIMEOUT,
    TAF_CALL_APP_ENCRYPT_VOICE_TX02_TIMEOUT,


    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_BUTT
};
typedef VOS_UINT32  TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32;

/*****************************************************************************
结构名      : TAF_CALL_APP_ENCRYPT_VOICE_TYPE_ENUM_UINT32
结构说明    : ECC呼叫模式
  1.日    期   : 2015年10月16日
    作    者   : y00322978
    修改内容   : 新生成函数
*****************************************************************************/
enum TAF_CALL_APP_ENCRYPT_VOICE_TYPE_ENUM
{
    TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_MUNAUL_MODE = 0,
    TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_AUTO_MODE,
    TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MT_MUNAUL_MODE,
    TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MT_AUTO_MODE,

    TAF_CALL_APP_ENCRYPT_VOICE_TYPE_BUTT
};
typedef VOS_UINT32 TAF_CALL_APP_ENCRYPT_VOICE_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TAF_CALL_PRIVACY_MODE_ENUM
 枚举说明  : Privary mode
 1.日    期   : 2014年09月04日
   作    者   : l60609
   修改内容   : 新增
*****************************************************************************/
enum TAF_CALL_PRIVACY_MODE_ENUM
{
    TAF_CALL_PRIVACY_MODE_PUBLIC        = 0x00,

    TAF_CALL_PRIVACY_MODE_PRIVATE       = 0x01,

    TAF_CALL_PRIVACY_MODE_BUTT          = 0x02
};
typedef VOS_UINT8 TAF_CALL_PRIVACY_MODE_ENUM_UINT8;

/*****************************************************************************
结构名      : TAF_CALL_APP_RESULT_TYPE_ENUM
结构说明    : ECC远程控制类型枚举值
  1.日    期   : 2015年12月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
enum TAF_CALL_APP_RESULT_TYPE_ENUM
{
    TAF_CALL_APP_RESULT_TYPE_SUCCESS,
    TAF_CALL_APP_RESULT_TYPE_FAILURE,

    TAF_CALL_APP_RESULT_TYPE_BUTT
};
typedef VOS_UINT32 TAF_CALL_APP_RESULT_TYPE_ENUM_UINT32;
/*****************************************************************************
  3 消息结构定义
*****************************************************************************/
/** ****************************************************************************
 * Name        : TAF_CALL_APP_EC_RANDOM_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_INT8                                                aucEccData[TAF_CALL_APP_EC_RANDOM_DATA_LENGTH];
    VOS_UINT8                                               aucReserved[3];
} TAF_CALL_APP_EC_RANDOM_DATA_STRU;

/*****************************************************************************
 结构名    : TAF_CCA_CTRL_STRU
 结构说明  : CCA控制结构体

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : y00245242
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulModuleId;         /* 填入PID */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
}TAF_CCA_CTRL_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_APP_ENCRYPT_VOICE_TYPE_ENUM_UINT32             enEccVoiceType;
    TAF_ECC_CALL_BCD_NUM_STRU                               stDialNumber;          /* Call Number */
} TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU;
/** ****************************************************************************
 * Name        : TAF_CALL_APP_SET_EC_TEST_MODE_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT32               enEccTestModeStatus;
} TAF_CALL_APP_SET_EC_TEST_MODE_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_GET_EC_TEST_MODE_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
} TAF_CALL_APP_GET_EC_TEST_MODE_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_REMOTE_CTRL_APP_TYPE_ENUM_UINT32               enRemoteCtrlEvtType;
    TAF_CALL_REMOTE_CTRL_APP_RESULT_ENUM_UINT32             enResult;
} TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_REMOTE_CTRL_OPER_RESULT_ENUM_UINT32            enResult;              /* 短信发送结果 */
} TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT32                    enEccSrvCap;
    TAF_CALL_APP_ECC_SRV_STATUS_ENUM_UINT32                 enEccSrvStatus;
} TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_ENUM_UINT32         enResult;
} TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU;
/** ****************************************************************************
 * Name        : TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
} TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT32                    enEccSrvCap;
    TAF_CALL_APP_ECC_SRV_STATUS_ENUM_UINT32                 enEccSrvStatus;
} TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_GET_EC_RANDOM_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
} TAF_CALL_APP_GET_EC_RANDOM_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_GET_EC_RANDOM_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    VOS_UINT32                                              ulResult;
    TAF_CALL_APP_EC_RANDOM_DATA_STRU                        stEccRandom[TAF_CALL_APP_EC_RANDOM_NUM];
} TAF_CALL_APP_GET_EC_RANDOM_CNF_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_GET_EC_KMC_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
} TAF_CALL_APP_GET_EC_KMC_REQ_STRU;


/** ****************************************************************************
 * Name        : TAF_CALL_APP_GET_EC_KMC_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    MN_CALL_APP_EC_KMC_DATA_STRU                            stKmcData;
    VOS_UINT32                                              ulResult;
} TAF_CALL_APP_GET_EC_KMC_CNF_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_SET_EC_KMC_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    MN_CALL_APP_EC_KMC_DATA_STRU                            stKmcData;

} TAF_CALL_APP_SET_EC_KMC_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_SET_EC_KMC_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    VOS_UINT32                                              ulResult;
} TAF_CALL_APP_SET_EC_KMC_CNF_STRU;


/** ****************************************************************************
 * Name        : TAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_REMOTE_CTRL_APP_TYPE_ENUM_UINT32               enRemoteCtrlType;
} TAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enEccVoiceStatus;
} TAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_ENCRYPT_VOICE_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enEccVoiceStatus;
    TAF_ECC_CALL_BCD_NUM_STRU                               stCallingNumber;          /* Call Number */
} TAF_CALL_APP_ENCRYPT_VOICE_IND_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    VOS_UINT16                                              usLength;
    VOS_UINT8                                               aucRsved[2];
    VOS_INT8                                                aucData[TAF_CALL_APP_ENCRYPTED_VOICE_DATA_MAX_LENGTH];
} TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_SET_EC_TEST_MODE_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    VOS_UINT32                                              ulResult;
} TAF_CALL_APP_SET_EC_TEST_MODE_CNF_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_GET_EC_TEST_MODE_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT32               enEccTestModeStatus;
    VOS_UINT32                                              ulResult;
} TAF_CALL_APP_GET_EC_TEST_MODE_CNF_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8                        enPrivacyMode;         /* privacy mode */
    VOS_UINT8                                               aucReserved[3];
} TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_APP_RESULT_TYPE_ENUM_UINT32                    enResult;
} TAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
} TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_CALL_PRIVACY_MODE_INFO_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucCallId;
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8                        enPrivacyMode;
    VOS_UINT8                                               aucReserved[2];
} TAF_CALL_CALL_PRIVACY_MODE_INFO_STRU;


/** ****************************************************************************
 * Name        : TAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8                        enPrivacyMode;         /* 当前privacy mode设置 */
    VOS_UINT8                                               ucCallNums;
    VOS_UINT8                                               aucReserved[2];
    TAF_CALL_CALL_PRIVACY_MODE_INFO_STRU                    astCallVoicePrivacyInfo[TAF_XCALL_MAX_NUM];
} TAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_PRIVACY_MODE_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8                        enPrivacyMode;         /* 当前privacy mode设置 */
    VOS_UINT8                                               aucReserved[2];
    TAF_CALL_CALL_PRIVACY_MODE_INFO_STRU                    stCallVoicePrivacyInfo; /* 当前呼叫的privacy mode信息 */
} TAF_CALL_APP_PRIVACY_MODE_IND_STRU;

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    TAF_CCA_MSG_TYPE_ENUM_UINT32        ulMsgId;                                /*_H2ASN_MsgChoice_Export TAF_PS_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_CCA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}TAF_APP_CALL_DATA_STRU;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_APP_CALL_DATA_STRU               stTafAppCall;
}TafAppCall_MSG;
#if ((VOS_OS_VER == VOS_WIN32) || (TAF_OS_VER == TAF_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafAppCall.h */
