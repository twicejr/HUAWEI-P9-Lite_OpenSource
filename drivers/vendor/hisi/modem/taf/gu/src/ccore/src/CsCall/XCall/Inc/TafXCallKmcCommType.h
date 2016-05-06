
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallKmcCommType.h
  版 本 号   : 初稿
  作    者   : l00359089
  生成日期   : 2015年10月20日
  功能描述   : TAF X CALL 定义KMC 消息中USER DATA的结构
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月20日
    作    者   : l00359089
    修改内容   : 创建文件 for CDMA 1X Iteration 19
******************************************************************************/
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef __TAF_X_CALL_KMC_COMM_TYPE_H__
#define __TAF_X_CALL_KMC_COMM_TYPE_H__

#include "vos.h"
#include "PsLogdef.h"
#include "TafStdlib.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_XCALL_MAX_PLAIN_DATA_LEN                        (160)               /*最大明文数据长度*/

#define TAF_XCALL_KMC_MSG_MAX_SIGN_INFO_LEN                 (48)                /*最大签名信息长度*/

#define TAF_XCALL_KMC_MSG_MAX_SIGN_DATA_LEN                 (160)               /*最大签名数据长度*/

#define TAF_XCALL_KMC_MSG_MAX_CIPHER_LEN                    (160)               /*最大密文长度*/

#define TAF_XCALL_KMC_MSG_MAX_REMOTE_NUMBER_LEN             (6)                 /*最大号码长度*/

#define TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN               (48)                /*KMC公钥长度*/

#define TAF_XCALL_KMC_MSG_MAX_KMC_PRIV_KEY_LEN              (24)                /*KMC私钥长度*/

#define TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN                   (16)                /*随机数长度  128 bits */

#define TAF_XCALL_KMC_MSG_WMS_CDMA_USER_DATA_MAX            (160)               /* Maximum number of bytes for CDMA user data */

#define TAF_XCALL_KMC_MSG_HEADER_LEN                        (4)                 /*头部长度*/

#define TAF_XCALL_KMC_MSG_SPECIAL_SMS_ID                    (0x00)              /*特殊短信标识*/

#define TAF_XCALL_KMC_MSG_EXT_CTRL_FIELD1                   (0x00)              /*控制扩展字段1*/

#define TAF_XCALL_KMC_MSG_EXT_CTRL_FIELD2                   (0x00)              /*控制扩展字段2*/

/* header 4 bytes + KeyVersion 1 byte + TIME STAMP 7 bytes + RomoteCtrlCmdType 1 byte + SignInfoLen 1 byte = 14 bytes*/
#define TAF_XCALL_KMC_MSG_REMOTE_CTRL_HEADER_LEN            (14)                /*远程控制指令消息头长度*/

/* header 4 bytes + KeyVersion 1 byte + KeyLen 1 byte =6 byte*/
#define TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_REQ_HEADER_LEN     (6)                 /*公钥更新消息头长度*/

#define TAF_XCALL_KMC_MSG_EXT_CTRL_BYTES                    (2)                 /*控制扩展字段长度*/

#define TAF_XCALL_KMC_MSG_KEY_VESRION_MAX                   (255)               /*公钥版本号的最大值*/

#define TAF_XCALL_KMC_MSG_KEY_VESRION_MIN                   (1)                 /*公钥版本号的最小值*/

#define TAF_XCALL_KMC_MSG_TIME_STAMP_LEN                    (7)                 /*时间戳长度*/

#define TAF_XCALL_KMC_MSG_ADDITIONAL_INFO_LEN               (6)                 /*辅助信息长度*/

#define TAF_XCALL_KMC_MSG_ADDITIONAL_INFO_LEN_BYTES         (1)                 /*辅助信息长度标志位所占字节数*/

#define TAF_XCALL_KMC_MSG_RSVD1_BYTES                       (1)                 /*保留字段1所占字节数*/

#define TAF_XCALL_KMC_MSG_RSVD2_BYTES                       (1)                 /*保留字段2所占字节数*/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*************************************
 枚举名：  TAF_XCALL_KMC_MSG_TRIGGER_MODE_ENUM
 枚举说明：触发密话模式
 1.日期:      20151021
   作者:      l00359089
   修改内容：新建
*************************************/
enum TAF_XCALL_KMC_MSG_TRIGGER_MODE_ENUM
{
    TAF_XCALL_KMC_MSG_TRIGGER_MODE_MANUAL                   = 0x00,             /*手动触发密话*/
    TAF_XCALL_KMC_MSG_TRIGGER_MODE_AUTO                     = 0x01,             /*自动触发密话 */
    TAF_XCALL_KMC_MSG_TRIGGER_MODE_BUTT                                         /*其他*/
};
typedef VOS_UINT8   TAF_XCALL_KMC_MSG_TRIGGER_MODE_ENUM_UINT8;

/*************************************
 枚举名：  TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_ENUM
 枚举说明：错误通知 消息 原因值
 1.日期:      20151021
   作者:      l00359089
   修改内容：新建
*************************************/
enum TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_ENUM
{
    TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_LOCAL_NO_PERMISSION     = 0x00,             /*本端用户无加密权限*/
    TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_REMOTE_NO_PERMISSION    = 0x01,             /*对端用户无加密权限 */
    TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_LOCAL_ILLEGAL           = 0x02,             /*本端终端非法*/
    TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_REMOTE_ILLEGAL          = 0x03,             /*对端终端非法*/
    TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_ESTABLISH_TIME_OUT      = 0x04,             /*密话建立超时*/
    TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_OTHERS                  = 0x05,             /*其他原因*/
    TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_BUTT
};
typedef VOS_UINT8   TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_ENUM_UINT8;

/*************************************
 枚举名：  TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM
 枚举说明：远程控制指令类型值
 1.日期:      20151021
   作者:      l00359089
   修改内容：新建
*************************************/
enum TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM
{
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_SECURE_INFO_ERASE                    =0x00,              /*安全信息擦除*/
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_PWD_RESET                            =0x01,              /*密码重置*/
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_BUTT
};
typedef VOS_UINT8   TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM_UINT8;

/*************************************
 枚举名：  TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_EXECUTE_RSLT_ENUM
 枚举说明：远程控制指令执行结果
 1.日期:      20151021
   作者:      l00359089
   修改内容：新建
*************************************/
enum TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_ENUM
{
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_SUCCESS                              = 0x00,  /* 成功 */
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_KEY_VERSION_MISMATCH_FAILURE         = 0x01,  /* KMC公钥版本不一致导致的失败 */
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_SIGN_VERIFY_FAILURE                  = 0x02,  /* 签名验证失败导致的失败 */
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_OTHER_FAILURE                        = 0x03,  /* 其他问题导致安全信息擦除失败 */
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_BUTT
};
typedef VOS_UINT8   TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_ENUM_UINT8;

/*************************************
 枚举名：  TAF_XCALL_KMC_MSG_TYPE_ENUM
 枚举说明：消息类型标志
 1.日期:      20151021
   作者:      l00359089
   修改内容：新建
*************************************/
enum TAF_XCALL_KMC_MSG_TYPE_ENUM
{
    TAF_XCALL_KMC_MSG_TYPE_MO_KEY_REQ                       =0x00,              /*主叫密钥请求*/
    TAF_XCALL_KMC_MSG_TYPE_MO_KEY_RSP                       =0x01,              /*主叫密钥响应*/
    TAF_XCALL_KMC_MSG_TYPE_MT_ENCRYPT_IND                   =0x02,              /*被叫加密通知消息*/
    TAF_XCALL_KMC_MSG_TYPE_MT_KEY_REQ                       =0x03,              /*被叫密钥请求*/
    TAF_XCALL_KMC_MSG_TYPE_MT_KEY_RSP                       =0x04,              /*被叫密钥响应 */
    TAF_XCALL_KMC_MSG_TYPE_ERR_IND                          =0x05,              /*错误通知*/
    TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_IND               =0x06,              /*KMC公钥更新*/
    TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_RSP               =0x07,              /*KMC公钥更新响应*/
    TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_ACK               =0x08,              /*KMC公钥更新确认*/
    TAF_XCALL_KMC_MSG_TYPE_ROMOTE_CTRL_CMD_IND              =0x09,              /*远程控制指令   */
    TAF_XCALL_KMC_MSG_TYPE_ROMOTE_CTRL_CMD_RSP              =0x0a,              /*远程控制响应   */
    TAF_XCALL_KMC_MSG_TYPE_UNKNOWN                          =0x0b,              /* 其他   */
    TAF_XCALL_KMC_MSG_TYPE_BUTT
};
typedef VOS_UINT8   TAF_XCALL_KMC_MSG_TYPE_ENUM_UINT8;

/*************************************
 枚举名：  TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM
 枚举说明：KMC MSG 编解码处理结果
 1.日期:      20151023
   作者:      l00359089
   修改内容：新建
*************************************/
enum TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM
{
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS                  =0,
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_MSG_TYPE_UNKNOWN,                            /*消息类型错误*/
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_MSG_NOT_ENOUGH,                              /*消息内容不足*/
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_SIGN_INFO_LEN_ERR,                           /*签名信息长度为0*/
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_CIPHER_LEN_ERR,                              /*密文信息长度为0*/
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_REMOTE_NUMBER_LEN_ERR,                       /*主叫电话号码长度为0*/
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_PUB_KEY_LEN_ERR,                             /*公钥长度不对 */
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENC_LEN_OVER_MAX_ERR,                        /*编码长度超过最大值*/
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_TIME_STAMP_ERR,                              /*时间戳有错*/
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ROMOTE_CTRL_CMD_TYPE_ERR,                    /*远程控制指令类型错误*/
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ERR_IND_CAUSE_ERR,                           /*错误通知原因值错误*/
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_BUTT
};
typedef VOS_UINT32   TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32;

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
/*************************************
 结构名：  TAF_XCALL_KMC_MSG_ADDITIONAL_INFO_STRU
 结构说明：辅助信息字段
 1.日期:      20151021
   作者:      l00359089
   修改内容：新建
*************************************/
typedef struct
{
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    VOS_UINT16                          usBsid;
    VOS_UINT8                           aucReserved[2];
}TAF_XCALL_KMC_MSG_ADDITIONAL_INFO_STRU;

/*************************************
 结构名：  TAF_XCALL_KMC_MSG_SIGN_INFO_STRU
 结构说明：签名信息字段
 1.日期:      20151023
   作者:      l00359089
   修改内容：新建
*************************************/
typedef struct
{
    /*KMC签名信息长度*/
    VOS_UINT8                           ucSignInfoLen;
    VOS_UINT8                           aucReserved[3];

    /*KMC签名信息*/
    VOS_UINT8                           aucSignInfo[TAF_XCALL_KMC_MSG_MAX_SIGN_INFO_LEN];
}TAF_XCALL_KMC_MSG_SIGN_INFO_STRU;

/*************************************
 结构名：  TAF_XCALL_KMC_PUB_KEY_STRU
 结构说明：公钥字段
 1.日期:      20151023
   作者:      l00359089
   修改内容：新建
*************************************/
typedef struct
{
    /*KMC公钥长度*/
    VOS_UINT8                           ucKeyLen;
    VOS_UINT8                           aucReserved[3];

    /*KMC公钥*/
    VOS_UINT8                           aucKey[TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN];
}TAF_XCALL_KMC_PUB_KEY_STRU;

/*************************************
 结构名：  TAF_XCALL_KMC_PRIV_KEY_STRU
 结构说明：私钥字段
 1.日期:      20151026
   作者:      y00245242
   修改内容：新建
*************************************/
typedef struct
{
    /*KMC私钥长度*/
    VOS_UINT8                           ucKeyLen;
    VOS_UINT8                           aucReserved[3];

    /*KMC私钥*/
    VOS_UINT8                           aucKey[TAF_XCALL_KMC_MSG_MAX_KMC_PRIV_KEY_LEN];
}TAF_XCALL_KMC_PRIV_KEY_STRU;

/*************************************
 结构名：  TAF_XCALL_KMC_PRIV_KEY_STRU
 结构说明：密文字段
 1.日期:      20151102
   作者:      l00359089
   修改内容：新建
*************************************/
typedef struct
{
    VOS_UINT16                          usCipherLen;        /*密文长度，2bytes*/
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucCipher[TAF_XCALL_KMC_MSG_MAX_CIPHER_LEN]; /*密文*/
}TAF_XCALL_KMC_MSG_CIPHER_STRU;

/*************************************
 结构名：  TAF_XCALL_KMC_MSG_KEY_REQ_STRU
 结构说明：密钥请求消息
 1.日期:      20151021
   作者:      l00359089
   修改内容：新建
*************************************/
typedef struct
{
    TAF_XCALL_KMC_MSG_TRIGGER_MODE_ENUM_UINT8               enTriggerMode;      /*触发密话模式*/
    VOS_UINT8                                               ucKeyVersion;       /*KMC公钥版本*/
    VOS_UINT8                                               aucReserved[2];
    TAF_XCALL_KMC_PUB_KEY_STRU                              stTmpPubKey;        /*临时公钥*/
    TAF_XCALL_KMC_MSG_CIPHER_STRU                           stCipher;           /*密文字段*/
    TAF_XCALL_KMC_MSG_ADDITIONAL_INFO_STRU                  stAdditionalInfo;   /*辅助信息字段*/
}TAF_XCALL_KMC_MSG_KEY_REQ_STRU;

/*************************************
 结构名：  TAF_XCALL_KMC_MSG_KEY_RSP_STRU
 结构说明：密钥响应消息
 1.日期:      20151021
   作者:      l00359089
   修改内容：新建
*************************************/
typedef struct
{
    TAF_XCALL_KMC_MSG_CIPHER_STRU                           stCipher;           /*密文字段*/
    TAF_XCALL_KMC_MSG_SIGN_INFO_STRU                        stSignInfo;         /*签名信息*/
}TAF_XCALL_KMC_MSG_KEY_RSP_STRU;

/*************************************
 结构名：  TAF_XCALL_KMC_MSG_MT_ENCRYPT_IND_STRU
 结构说明：被叫加密通知消息
 1.日期:      20151021
   作者:      l00359089
   修改内容：新建
*************************************/
typedef struct
{
    /*主叫号码长度*/
    VOS_UINT8                           ucRemoteNumberLen;

    VOS_UINT8                           aucReserved[1];

    /*主叫号码*/
    VOS_UINT8                           aucRemoteNumber[TAF_XCALL_KMC_MSG_MAX_REMOTE_NUMBER_LEN];
}TAF_XCALL_KMC_MSG_MT_ENCRYPT_IND_STRU;

/*************************************
 结构名：  TAF_XCALL_KMC_MSG_ERR_IND_STRU
 结构说明：错误通知 消息
 1.日期:      20151021
   作者:      l00359089
   修改内容：新建
*************************************/

typedef struct
{
    TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_ENUM_UINT8              enErrCause;         /*原因值*/
    VOS_UINT8                                               aucReserved[3];     /*保留字段*/
}TAF_XCALL_KMC_MSG_ERR_IND_STRU;

/*************************************
 结构名：  TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_IND_STRU
 结构说明：KMC公钥更新 消息
 1.日期:      20151021
   作者:      l00359089
   修改内容：新建
*************************************/
typedef struct
{

    VOS_UINT8                                               ucKeyVersion;       /*KMC公钥版本*/
    VOS_UINT8                                               aucReserved[3];     /*保留字段*/
    TAF_XCALL_KMC_PUB_KEY_STRU                              stPubKey;           /*KMC公钥*/
    TAF_XCALL_KMC_MSG_SIGN_INFO_STRU                        stSignInfo;         /*KMC签名信息*/
}TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_IND_STRU;

/*************************************
 结构名：  TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU
 结构说明：KMC公钥更新响应消息
 1.日期:      20151021
   作者:      l00359089
   修改内容：新建
*************************************/
typedef struct
{
    /*随机数*/
    VOS_UINT8                           aucRandomData[TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN];
}TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU;

/*************************************
 结构名：  TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU
 结构说明：KMC公钥更新确认 消息
 1.日期:      20151021
   作者:      l00359089
   修改内容：新建
*************************************/
typedef struct
{
    /*随机数*/
    VOS_UINT8                           aucRandomData[TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN];
} TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU;

/*************************************
 结构名：  TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU
 结构说明：远程控制指令
 1.日期:      20151021
   作者:      l00359089
   修改内容：新建
*************************************/
typedef struct
{
    /*KMC公钥版本*/
    VOS_UINT8                                               ucKeyVersion;
    VOS_UINT8                                               aucReserved1[3];     /*保留字段*/
    /*时间戳*/
    TAF_STD_TIME_ZONE_TYPE_STRU                             stTimeStamp;

    /*远程控制指令类型*/
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM_UINT8       enRomoteCtrlCmdType;
    VOS_UINT8                                               aucReserved2[3];     /*保留字段*/

    /*KMC签名信息*/
    TAF_XCALL_KMC_MSG_SIGN_INFO_STRU                        stSignInfo;

}TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU;

/*************************************
 结构名：  TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU
 结构说明：远程控制指令响应
 1.日期:      20151021
   作者:      l00359089
   修改内容：新建
*************************************/
typedef struct
{
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM_UINT8       enRomoteCtrlCmdType;                            /*远程控制指令类型*/
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_ENUM_UINT8       enExecuteRslt;                                  /*指令执行结果*/
    VOS_UINT8                                               ucKeyVersion;                                   /*终端存储的KMC公钥版本号*/
    VOS_UINT8                                               ucReserved;                                    /*保留字段*/
}TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU;

/*************************************
 结构名：  TAF_XCALL_KMC_MSG_INFO_STRU
 结构说明：终端与KMC交互消息
 1.日期:      20151021
   作者:      l00359089
   修改内容：新建
*************************************/
typedef struct
{
    VOS_UINT8                                               ucSpecSmsID;        /*特殊短信标识*/
    VOS_UINT8                                               aucExtCtrlField[TAF_XCALL_KMC_MSG_EXT_CTRL_BYTES];  /*控制扩展字段*/
    TAF_XCALL_KMC_MSG_TYPE_ENUM_UINT8                       enSmsType;          /*消息类型*/
    union
    {
        TAF_XCALL_KMC_MSG_KEY_REQ_STRU                      stKeyReq;           /*密钥请求*/
        TAF_XCALL_KMC_MSG_KEY_RSP_STRU                      stKeyRsp;           /*密钥响应*/
        TAF_XCALL_KMC_MSG_MT_ENCRYPT_IND_STRU               stMtEncryptInd;     /*被叫加密通知消息*/
        TAF_XCALL_KMC_MSG_ERR_IND_STRU                      stErrInd;           /*错误通知*/
        TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_IND_STRU           stPubKeyUpdateInd;  /*KMC公钥更新*/
        TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU           stPubKeyUpdateRsp;  /*KMC公钥更新响应*/
        TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU           stPubKeyUpdateAck;  /*KMC公钥更新确认*/
        TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU          stRemoteCtrlInd;    /*远程控制指令   */
        TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU          stRemoteCtrlRsp;    /*远程控制指令响应*/
                                                                                /*其他*/

    }u;
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt;             /*编解码结果*/
}TAF_XCALL_KMC_MSG_STRU;

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

#endif /* end of TafXCallKmcCommType.h */
