/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsDecode.h
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年10月31日
  功能描述   : TafXsmsDecode.c头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

#ifndef _TAF_XSMS_DECODE_H_
#define _TAF_XSMS_DECODE_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "TafAppXsmsInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define TAF_XSMS_MAX_DBM_SIZE                   (255)         /* DBM数据最大长度，不包括头 */
#define MAX_BD_BYTE_LENGTH                      (253)
#define TAF_XSMS_MAX_SUBADDRESS_PARAM_LEN       (38)
#define TAF_XSMS_BIT_NUMBER_OF_BYTE             (8)
#define TAF_XSMS_TPDU_LEN_MAX                   (253)
#define DBM_SMS_TYPE                            (3)
#define DIGITS_OF_AUTN                          (6)
#define TAF_XSMS_VOICE_NOTIFICATION             (0x1003)
#define TAF_XSMS_TELESERVICE_CATPT              (4103) /* TIA */
#define TAF_XSMS_TELESERVICE_AGPS_NI_SMS        (65001)
#define TAF_XSMS_BD_USER_DATA_MAX_LEN           (238)
#define TAF_XSMS_BD_PURE_CONTEXT_MAX_LEN_8      (140)
#define TAF_XSMS_BD_USER_DATA_ENCODE_BIT_7      (7)
#define TAF_XSMS_BD_USER_DATA_ENCODE_BIT_8      (8)
#define TAF_XSMS_BD_USER_DATA_ENCODE_BIT_16     (16)
#define TAF_XSMS_BD_LANGUAGE_INDICATOR_ENGLISH  (0x01)
#define TAF_XSMS_BD_LANGUAGE_INDICATOR_CHINESE  (0x06)

#define TAF_XSMS_TELESERVICE_CDMACMT            (0x1002) /* CMT */






/*****************************************************************************
  3 枚举定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 枚举名    : TAF_XSMS_TL_MSG_TYPE_ENUM8
 枚举说明  : 收到的短信的类型
*****************************************************************************/
enum TAF_XSMS_TL_MSG_TYPE_ENUM
{
    TAF_XSMS_TL_P2P_MSG            = 0,
    TAF_XSMS_TL_BROADCAST_MSG      = 1,
    TAF_XSMS_TL_ACK_MSG            = 2,
    TAF_XSMS_TL_MSG_TYPE_BUTT      = 3,
};

typedef VOS_UINT8 TAF_XSMS_TL_MSG_TYPE_ENUM8;

/*****************************************************************************
 枚举名    : TAF_XSMS_TL_PARAMETER_ID_ENUM32
 枚举说明  : TL层的Parameter ID
*****************************************************************************/
enum TAF_XSMS_TL_PARAMETER_ID_ENUM
{

    TAF_XSMS_TL_TELESERVICE_ID         = 0,
    TAF_XSMS_TL_SERVICR_CATEGORY       = 1,
    TAF_XSMS_TL_ORIGIN_ADDR            = 2,
    TAF_XSMS_TL_ORIGIN_SUBADDR         = 3,
    TAF_XSMS_TL_DEST_ADDR              = 4,
    TAF_XSMS_TL_DEST_SUBADDR           = 5,
    TAF_XSMS_TL_BEARER_REPLY_OPTION    = 6,
    TAF_XSMS_TL_CAUSE_CODE             = 7,
    TAF_XSMS_TL_BERAER_DATA            = 8,
    TAF_XSMS_TL_PARAMETER_MAX          = 9,
    TAF_XSMS_TL_PARAMETER_ID_BUTT         = 0xff,
};

typedef VOS_UINT32 TAF_XSMS_TL_PARAMETER_ID_ENUM32;

/*****************************************************************************
 枚举名    : TAF_XSMS_TL_ERROR_CLASS_ENUM8
 枚举说明  : TL层Cause code参数的Error Class
*****************************************************************************/
enum TAF_XSMS_TL_ERROR_CLASS_ENUM
{
    TAF_XSMS_TL_CAUSECODE_NONE         = 0,
    TAF_XSMS_TL_CAUSECODE_RESERVED     = 1,
    TAF_XSMS_TL_CAUSECODE_TMP          = 2,
    TAF_XSMS_TL_CAUSECODE_PERMANENT    = 3,
    TAF_XSMS_TL_CAUSECODE_BUTT         = 4,
};

typedef VOS_UINT8 TAF_XSMS_TL_ERROR_CLASS_ENUM8;

/*****************************************************************************
 枚举名    : TAF_XSMS_BD_MSG_TYPE_ENUM8
 枚举说明  : BEARER DATA里面的MSG_TYPE
*****************************************************************************/
enum TAF_XSMS_BD_MSG_TYPE_ENUM
{
    TAF_XSMS_BD_MSG_TYPE_DELIVER            = 1,
    TAF_XSMS_BD_MSG_TYPE_SUBMIT             = 2,
    TAF_XSMS_BD_MSG_TYPE_CANCELL            = 3,
    TAF_XSMS_BD_MSG_TYPE_DELIBER_ACK        = 4,
    TAF_XSMS_BD_MSG_TYPE_USER_ACK           = 5,
    TAF_XSMS_BD_MSG_TYPE_READ_ACK           = 6,

    TAF_XSMS_BD_MSG_TYPE_BUTTS
};

typedef VOS_UINT8 TAF_XSMS_BD_MSG_TYPE_ENUM8;


/*****************************************************************************
 枚举名    : TAF_XSMS_TL_CAUSE_CODE_ENUM8
 枚举说明  :  TL层Cause code参数的发生的错误的原因代码
*****************************************************************************/
enum TAF_XSMS_TL_CAUSE_CODE_ENUM
{
  /* 1.网络问题:  */
    TAF_XSMS_TL_ADDRESS_VACANT                        = 0, /* 网络问题，少地址.        */
    TAF_XSMS_TL_ADDRESS_TRANSLATION_FAILURE           = 1, /* 网络问题，地址翻译错误   */
    TAF_XSMS_TL_NETWORK_RESOURCE_SHORTAGE             = 2, /* 网络问题，网络资源短缺   */
    TAF_XSMS_TL_NETWORK_FAILURE                       = 3, /* 网络问题，网络失败       */
    TAF_XSMS_TL_INVALID_TELESERVICE_ID                = 4, /* 网络问题，不正确的Teleservice ID*/
    TAF_XSMS_TL_OTHER_NETWORK_PROBLEM                 = 5, /* 其他网络问题.            */
    TAF_XSMS_TL_OTHER_NETWORK_PROBLEM_MORE_FIRST      = 6, /* 其他网络问题起始值.      */


  /* 6 到 31 之间的值都看成 TAF_XSMS_TL_OTHER_NETWORK_PROBLEM. */

    TAF_XSMS_TL_OTHER_NETWORK_PROBLEM_MORE_LAST       = 31, /* 其他网络问题起始值结束值. */

  /* 2. 终端问题:  */
    TAF_XSMS_TL_NO_PAGE_RESPONSE                      = 32, /* 终端问题，寻呼没有应答      */
    TAF_XSMS_TL_DESTINATION_BUSY                      = 33, /* 终端问题, 目标忙            */
    TAF_XSMS_TL_NO_ACK                                = 34, /* 终端问题, 没有ACK           */
    TAF_XSMS_TL_DESTINATION_RESOURCE_SHORTAGE         = 35, /* 终端问题, 目标资源短缺      */
    TAF_XSMS_TL_SMS_DELIVERY_POSTPONED                = 36, /* 终端问题, 短信延迟投递      */
    TAF_XSMS_TL_DESTINATION_OUT_OF_SERVICE            = 37, /* 终端问题, 目标无服务        */
    TAF_XSMS_TL_DESTINATION_NO_LONGER_AT_THIS_ADDRESS = 38, /* 终端问题, 目标终端是空号?  */
    TAF_XSMS_TL_OTHER_TERMINAL_PROBLEM                = 39, /* 终端问题, 其他              */
    TAF_XSMS_TL_OTHER_TERMINAL_PROBLEM_MORE_FIRST     = 40, /* 终端问题, 其他起始值        */

  /* 40到47之间的值都看成 TAF_XSMS_TL_OTHER_TERMINAL_PROBLEM. */

    TAF_XSMS_TL_OTHER_TERMINAL_PROBLEM_MORE_LAST      = 47, /* 终端问题, 其他结束值        */
    TAF_XSMS_TL_SMS_DELIVERY_POSTPONED_MORE_FIRST     = 48, /* 终端问题, 延迟投递起始值    */
    TAF_XSMS_TL_SMS_DELIVERY_POSTPONED_MORE_LAST      = 63, /* 终端问题, 延迟投递结束值    */

  /* 3. 射频接口问题  */
    TAF_XSMS_TL_RADIO_IF_RESOURCE_SHORTAGE            = 64, /* 射频接口问题，接口资源短缺  */
    TAF_XSMS_TL_RADIO_IF_INCOMPATIBLE                 = 65, /* 射频接口问题，不匹配        */
    TAF_XSMS_TL_OTHER_RADIO_IF_PROBLEM                = 66, /* 射频接口问题，其他          */
    TAF_XSMS_TL_OTHER_RADIO_IF_PROBLEM_MORE_FIRST     = 67, /* 射频接口问题，其他起始值    */

  /* 67 到 95 都看成 TAF_XSMS_TL_OTHER_RADIO_IF_PROBLEM. */

    TAF_XSMS_TL_OTHER_RADIO_IF_PROBLEM_MORE_LAST      = 95, /* 射频接口问题，其他结束值    */

  /* D. 一般问题  */
    TAF_XSMS_TL_UNEXPECTED_PARM_SIZE                  = 96,  /* 参数大小不对               */
    TAF_XSMS_TL_SMS_ORIGINATION_DENIED                = 97,  /* 短信源地址拒绝             */
    TAF_XSMS_TL_SMS_TERMINATION_DENIED                = 98,  /* 短信终端拒绝               */
    TAF_XSMS_TL_SUPPL_SERVICE_NOT_SUPPORTED           = 99,  /* 服务不支持?               */
    TAF_XSMS_TL_SMS_NOT_SUPPORTED                     = 100, /* 不支持短信                 */
    TAF_XSMS_TL_RESERVED_101                          = 101, /* 保留，值为101              */
    TAF_XSMS_TL_MISSING_EXPECTED_PARM                 = 102, /* 缺少希望有的参数           */
    TAF_XSMS_TL_MISSING_MANDATORY_PARM                = 103, /* 缺少必须有的参数           */
    TAF_XSMS_TL_UNRECOGNIZED_PARM_VALUE               = 104, /* 无法识别的参数值           */
    TAF_XSMS_TL_UNEXPECTED_PARM_VALUE                 = 105, /* 参数值不正确               */
    TAF_XSMS_TL_USER_DATA_SIZE_ERROR                  = 106, /* User Data 参数不正确       */
    TAF_XSMS_TL_OTHER_GENERAL_PROBLEMS                = 107, /* 其他一般问题               */
    TAF_XSMS_TL_OTHER_GENERAL_PROBLEMS_MORE_FIRST     = 108, /* 其他一般问题，起始值       */

  /* 108 到 255 都看成 TAF_XSMS_TL_OTHER_GENERAL_PROBLEMS */

    TAF_XSMS_TL_OTHER_GENERAL_PROBLEMS_MORE_LAST      = 255, /* 其他一般问题，结束值       */

} ;

typedef VOS_UINT8 TAF_XSMS_TL_CAUSE_CODE_ENUM8;

/*****************************************************************************
 枚举名    : TAF_XSMS_BD_PARAMETER_ID_ENUM8
 枚举说明  :  Bearer Data层 SubParameter ID
*****************************************************************************/
enum TAF_XSMS_BD_PARAMETER_ID_ENUM
{

    TAF_XSMS_BD_MESSAGE_IDENTIFIER                 = 0,
    TAF_XSMS_BD_USER_DATA                          = 1,
    TAF_XSMS_BD_USER_RESPONESE_CODE                = 2,
    TAF_XSMS_BD_MESSAGE_CENTER_TIME_STAMP          = 3,
    TAF_XSMS_BD_VALIDITY_PERIOD_ABSOLUTE           = 4,
    TAF_XSMS_BD_VALIDITY_PERIOD_RELATIVE           = 5,
    TAF_XSMS_BD_DEFERRED_DELIVERY_TIME_ABSOLUTE    = 6,
    TAF_XSMS_BD_DEFERRED_DELIVERY_TIME_RELATIVE    = 7,
    TAF_XSMS_BD_PRIORITY_INDICATOR                 = 8,
    TAF_XSMS_BD_PRIVACY_INDICATOR                  = 9,
    TAF_XSMS_BD_REPLY_OPTION                       = 10,
    TAF_XSMS_BD_NUMBER_OF_MESSAGE                  = 11,
    TAF_XSMS_BD_ALERT_ON_MESSAGE_DELIVERY          = 12,
    TAF_XSMS_BD_LANGUAGE_INDICATOR                 = 13,
    TAF_XSMS_BD_CALL_BACK_NUMBER                   = 14,
    TAF_XSMS_BD_MESSAGE_DISPLAY_MODE               = 15,
    TAF_XSMS_BD_MULTIPLE_ENCODING_USER_DTAT        = 16,
    TAF_XSMS_BD_SERVICE_CATEFORY_PROGRAM_DATA      = 17,
    TAF_XSMS_BD_SERVICE_CATEFORY_PROGRAM_RESULTS   = 18,
    TAF_XSMS_BD_MESSAGE_STATUS                     = 19,
    TAF_XSMS_BD_PARAMETER_VALUE_MAX                = 19,
    TAF_XSMS_TL_PARAMETER_BUTT                     = 0xFF,
};

typedef VOS_UINT8 TAF_XSMS_BD_PARAMETER_ID_ENUM8;


/*****************************************************************************
 枚举名    : TAF_XSMS_USER_DATA_MSG_ENCODE_ENUM
 枚举说明  : MSG_ENCODE 类型 CR1001 Table 9.1-1
*****************************************************************************/
enum TAF_XSMS_USER_DATA_MSG_ENCODE_ENUM
{
    TAF_XSMS_USER_DATA_MSG_ENCODE_OCTET             = 0,
    TAF_XSMS_USER_DATA_MSG_ENCODE_EPM               = 1,
    TAF_XSMS_USER_DATA_MSG_ENCODE_ASCII_7           = 2,    /* 7 BITS*/
    TAF_XSMS_USER_DATA_MSG_ENCODE_IA5               = 3,    /* 7 BITS*/
    TAF_XSMS_USER_DATA_MSG_ENCODE_UNICODE           = 4,
    TAF_XSMS_USER_DATA_MSG_ENCODE_JIS               = 5,
    TAF_XSMS_USER_DATA_MSG_ENCODE_KOREAN            = 6,
    TAF_XSMS_USER_DATA_MSG_ENCODE_HEBREW            = 7,
    TAF_XSMS_USER_DATA_MSG_ENCODE_LATIN             = 8,
    TAF_XSMS_USER_DATA_MSG_ENCODE_GSM_7             = 9,    /* 7 BITS*/
    TAF_XSMS_USER_DATA_MSG_ENCODE_GSM_DCS           = 10,
    TAF_XSMS_USER_DATA_MSG_ENCODE_BUTT
};

typedef VOS_UINT8 TAF_XSMS_USER_DATA_MSG_ENCODE_ENUM8;

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
 结构名    :TAF_XSMS_CAUSE_CODE_STRU
 结构说明  :TL层Cause Code结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucParameterLen;
    VOS_UINT8                           ucReplySeq;
    TAF_XSMS_TL_ERROR_CLASS_ENUM8      enErrorClass;
    TAF_XSMS_TL_CAUSE_CODE_ENUM8       enCauseCode;
}TAF_XSMS_CAUSE_CODE_STRU;

/*****************************************************************************
 结构名    :TAF_XSMS_MSG_ID_STRU
 结构说明  :MSG_ID结构体
*****************************************************************************/
typedef struct
{
    TAF_XSMS_BD_MSG_TYPE_ENUM8          enMsgType;
    VOS_UINT8                           ucIsHeadIndExist;
    VOS_UINT16                          usMsgID;
}TAF_XSMS_MSG_ID_STRU;


/*****************************************************************************
 结构名    :TAF_XSMS_TL_FLAG_BIT_STRU
 结构说明  :TL层参数存在标志位，位域表示
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          bIsTelesrvIdPresent:1;
    VOS_UINT16                          bIspSrvCategoryPresent:1;
    VOS_UINT16                          bIsOpOrigAddrPresent:1;
    VOS_UINT16                          bIsOpOrigSubAddrPresent:1;
    VOS_UINT16                          bIsOpDstAddrPresent:1;
    VOS_UINT16                          bIsOpDstSubAddrPresent:1;
    VOS_UINT16                          bIsOpBearReplyOpPresent:1;
    VOS_UINT16                          bIsOpBearDataPresent:1;
    VOS_UINT16                          bIsOpCauseCodePresent:1;
    VOS_UINT16                          bIsOpIsPRL:1;
    VOS_UINT16                          bIsOpIsPPDownload:1;
    VOS_UINT16                          bIsOp_Reserved:5;
}TAF_XSMS_TL_FLAG_BIT_STRU;

/*****************************************************************************
 结构名    :TAF_XSMS_DATA_BURST_MSG_STRU
 结构说明  :Data Burst Message 结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBurstType;
    VOS_UINT8                           ucMsgNum;
    VOS_UINT8                           ucNumFields;
    VOS_UINT8                           ucNumMsgs;
    VOS_UINT8                           aucData[255];
    VOS_UINT8                           ucRsv;
}TAF_XSMS_DATA_BURST_MSG_STRU;

/*****************************************************************************
 结构名    :TAF_XSMS_TRANSPORT_MESSAGE_STRU
 结构说明  :Transport Layer结构体
*****************************************************************************/
typedef struct
{

    union
    {
        VOS_UINT16                      ausValue[1];
        TAF_XSMS_TL_FLAG_BIT_STRU      stTLBitPresentFlag;
    }unPresentFlag;
    VOS_UINT8                           ucBearReplySeqNum;
    TAF_XSMS_TL_MSG_TYPE_ENUM8         enMessageType;
    TAF_XSMS_MESSAGE_STRU              stMessage;
    TAF_XSMS_CAUSE_CODE_STRU           stCauseCode;

}TAF_XSMS_TRANSPORT_MESSAGE_STRU;


typedef VOS_UINT32 TAF_XSMS_PARAMETER_DECODE_FUNC(VOS_UINT8 *pucData, VOS_UINT8 *pucBytePos,TAF_XSMS_TRANSPORT_MESSAGE_STRU *pstTLStru);

/*参数ID 对应不同的函数指针*/
typedef struct
{
    TAF_XSMS_TL_PARAMETER_ID_ENUM32     enParaId;           /*参数类型的值*/
    TAF_XSMS_PARAMETER_DECODE_FUNC     *pstParaDecodeFunc;  /*参数类型的解码函数指针*/
}TAF_XSMS_PARM_DECODE_FUNC_STRU;


/*****************************************************************************
 结构名    :TAF_XSMS_BD_GENERAL_PARAMETER_8B_STRU
 结构说明  :Bearer data 参数结构体，用于调整Bear Date子参数位置
*****************************************************************************/
typedef struct
{
    TAF_XSMS_BD_PARAMETER_ID_ENUM8      enParamHeader;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucBytePos;
}TAF_XSMS_BD_GENERAL_PARAMETER_8B_STRU;


/*****************************************************************************
 结构名    :TAF_XSMS_BD_MSG_DISPLAY_MODE_STRU
 结构说明  :Bearer data 子参数Message Display Mode的结构体
*****************************************************************************/
typedef struct
{
    TAF_XSMS_BD_PARAMETER_ID_ENUM8      enParamHeader;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucMsgDisplayMode;
    VOS_UINT8                           ucMsgReserverd;
}TAF_XSMS_BD_MSG_DISPLAY_MODE_STRU;

/*****************************************************************************
 结构名    :TAF_XSMS_BD_MSG_USER_DATA_STRU
 结构说明  :Bearer data 子参数user data的结构体
*****************************************************************************/
typedef struct
{
    TAF_XSMS_USER_DATA_MSG_ENCODE_ENUM8 enMsgCodeType;
    VOS_UINT8                           ucMsgType;
    VOS_UINT8                           ucNumFields;
    VOS_UINT8                           ucRcv;
    VOS_UINT8                           aucUserData[256];
}TAF_XSMS_BD_MSG_USER_DATA_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_VOID TAF_XSMS_TL_UnpackByteToBit (
    VOS_UINT8                          *pucBuffer,
    VOS_UINT8                          *pucValue,
    VOS_UINT16                          usBitPos,
    VOS_UINT8                           ucBitNum
);

extern VOS_VOID TAF_XSMS_TL_FillCauseCode(
    TAF_XSMS_TL_ERROR_CLASS_ENUM8       enErrorClass,
    TAF_XSMS_TL_CAUSE_CODE_ENUM8        enCauseCode,
    VOS_UINT8                           ucReplySeq,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru

);

extern VOS_VOID TAF_XSMS_TL_FillCauseCodeSeq(
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru

);

extern VOS_UINT32 TAF_XSMS_TL_DecodeTeleSrvId(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
);

extern VOS_UINT32 TAF_XSMS_TL_DecodeSrvCategory(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU   *pstTLStru
);

extern VOS_UINT32 TAF_XSMS_TL_DecodeAddr(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
);

extern VOS_UINT32 TAF_XSMS_TL_DecodeSubAddr(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU   *pstTLStru
);

extern VOS_UINT32 TAF_XSMS_TL_DecodeBearReplyOption(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
);


extern VOS_UINT32 TAF_XSMS_TL_DecodeCauseCode(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
);

extern VOS_UINT32 TAF_XSMS_TL_DecodeBearData(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
);

extern VOS_UINT32 TAF_XSMS_DecodeTLRawToTLStru(
    VOS_UINT8                           ucTLRawLen,
    VOS_UINT8                          *pucTLRaw,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLMsg
);

extern VOS_UINT32  TAF_XSMS_CheckFields(TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLMsg);

extern VOS_VOID TAF_XSMS_FillBDShortStru(
    VOS_UINT8                                              *pucBuffer,
    VOS_UINT8                                              *pucBytePos,
    TAF_XSMS_BD_GENERAL_PARAMETER_8B_STRU                  *pstBDParamStru
);

extern VOS_VOID TAF_XSMS_IsPRL(TAF_XSMS_TRANSPORT_MESSAGE_STRU *pstTLMsg);

extern VOS_VOID TAF_XSMS_DecodeUserDataInBearerData(
    VOS_UINT32                          ulBearDataLen,  /* in */
    VOS_UINT8                          *pucBearerData,  /* in */
    VOS_UINT16                         *pusUserDataStartByte,   /* out */
    VOS_UINT16                         *pusUserDataLen, /* out 在BearerData中的长度，不是数据实际长度 */
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstUserData     /* out */
);
extern VOS_UINT8 TAF_XSMS_GetLowBits(VOS_UINT8 ucOffset);

extern VOS_UINT32 TAF_XSMS_GetUserDataCodeBitsByMsgCode(
    TAF_XSMS_USER_DATA_MSG_ENCODE_ENUM8 enMsgCodeType,
    VOS_UINT8                          *pucBitNum
);

extern VOS_VOID TAF_XSMS_PressUserData(
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstUserData
);

extern VOS_VOID TAF_XSMS_DevideLongCdmaSms(
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstUserData,         /* USER DATA */
    VOS_UINT16                          usUserDataStartByte, /* in 在原来的BEARER DATA 中开始位置 */
    VOS_UINT16                          usUserDataLen,       /* in 在原来的BEARER DATA 中长度*/
    TAF_XSMS_MESSAGE_STRU              *pstFirstMessage,     /* 第一条消息*/
    TAF_XSMS_MESSAGE_STRU              *pstSecondMessage    /* 第二条消息 */
);

extern VOS_VOID TAF_XSMS_DevideUserData(
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstFirstUserData,         /* USER DATA in and out */
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstSecondUserData        /* USER DATA out*/
);

extern VOS_VOID TAF_XSMS_ReplaceUserData(
    TAF_XSMS_MESSAGE_STRU              *pstMessage,
    VOS_UINT8                          *pucPressedUserData,
    VOS_UINT32                          ulPressedUserDataLen,
    VOS_UINT16                          usOldUserDataStartByte,
    VOS_UINT16                          usOldUserDataLen
);

extern VOS_VOID TAF_XSMS_GetXsmsLimitLen(
    TAF_XSMS_USER_DATA_MSG_ENCODE_ENUM8 enMsgCodeType,
    VOS_UINT16                         *pusLenLimit
);

extern VOS_VOID TAF_XSMS_EncodeMsgID(
    TAF_XSMS_MSG_ID_STRU               *pstMsgId,           /* in */
    VOS_UINT8                          *pucMsgIdLen,        /* out */
    VOS_UINT8                          *paucMsfIdData       /* out */
);

extern VOS_VOID TAF_XSMS_EncodeUserRspCode(
    VOS_UINT8                           ucUserResponseCode, /* in */
    VOS_UINT8                          *pucRepCodeLen,      /* out */
    VOS_UINT8                          *pucRepCodeData      /* out */
);

extern VOS_VOID TAF_XSMS_EncodeUserData(
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstUserData,    /* in */
    VOS_UINT8                          *pucUserDataLen, /* out */
    VOS_UINT8                          *paucUserData    /* out */
);

extern VOS_VOID TAF_XSMS_PackBitToByte(
    VOS_UINT8                          *pucBuffer,
    VOS_UINT8                           ucValue,
    VOS_UINT8                           ucBitNum,
    VOS_UINT16                          usBitPos
);

VOS_VOID TAF_XSMS_DecodeMsgId(
    VOS_UINT32                          ulBearDataLen,
    VOS_UINT8                          *pucBearData,
    TAF_XSMS_MSG_ID_STRU               *pstMsgId
);

#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

