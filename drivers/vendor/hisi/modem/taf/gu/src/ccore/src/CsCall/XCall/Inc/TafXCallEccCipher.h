
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallEccCipher.h
  版 本 号   : 初稿
  作    者   : c00177591
  生成日期   : 2015年10月22日
  功能描述   : TafXCallEccCipher.c的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月22日
    作    者   : c00177591
    修改内容   : 创建文件 for CDMA 1X Iteration 19
******************************************************************************/

#ifndef __TAF_X_CALL_ECC_CIPHER_H__
#define __TAF_X_CALL_ECC_CIPHER_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafXCallKmcCommType.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_XCALL_ECC_CIPHER_OK                   (0)
#define TAF_XCALL_ECC_VERIFY_OK                   (1)

#define TAF_XCALL_ECC_MAX_SLICE_VALUE                       (0xFFFFFFFF)


#define TAF_XCALL_ECC_PUBLIC_KEY_LEN                        (48)
#define TAF_XCALL_ECC_PRIVAE_KEY_LEN                        (24)
#define TAF_XCALL_ECC_NIBBLE_NUM_OF_CHAR                    (2)
#define TAF_XCALL_ECC_TEN                                   (10)
#define TAF_XCALL_ECC_ASCII_OF_ZERO                         ('0')
#define TAF_XCALL_ECC_ASCII_OF_LETTER                       ('A')
#define TAF_XCALL_ECC_MAX_ASCII_OUTPUT_LEN                  (256)
#define TAF_XCALL_ECC_MAX_LOG_OUTPUT_LEN                    (512)
#define TAF_XCALL_GET_DATA                                  VOS_nsprintf

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


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
结构名      : TAF_XCALL_CIPHER_ENCRYPTION_STRU
结构说明    : 加解密数据及密钥信息
  1.日    期   : 2015年10月23日
    作    者   : c00177591
    修改内容   : 新生成
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPubKeyLen;        /*公钥长度*/
    VOS_UINT8                           ucPlainDataLen;     /*明文数据长度*/
    VOS_UINT8                           ucCipherDataLen;    /*密文数据长度*/
    VOS_UINT8                           aucReserved1[1];

    VOS_UINT16                          ucEncrptionLen;     /*返回数据长度*/
    VOS_UINT8                           aucReserved2[2];

    VOS_UINT8                           aucPubKey[TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN];     /*公钥*/
    VOS_UINT8                           aucPlainData[TAF_XCALL_MAX_PLAIN_DATA_LEN];           /*明文数据*/
    VOS_UINT8                          *pucCipherData;                                        /*密文数据*/
}TAF_XCALL_CIPHER_ENCRYPTION_STRU;

/*****************************************************************************
结构名      : TAF_XCALL_CIPHER_ENCRYPTION_STRU
结构说明    : 加解密数据及密钥信息
  1.日    期   : 2015年10月23日
    作    者   : c00177591
    修改内容   : 新生成
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCipherKeyLen;     /*密钥长度*/
    VOS_UINT8                           ucPlainDataLen;     /*明文数据长度*/
    VOS_UINT8                           ucCipherDataLen;    /*密文数据长度*/
    VOS_UINT8                           ucEncrptionLen;     /*返回数据长度*/

    VOS_UINT8                           aucCipherKey[TAF_XCALL_KMC_MSG_MAX_KMC_PRIV_KEY_LEN]; /*密钥*/
    VOS_UINT8                           aucCipherData[TAF_XCALL_KMC_MSG_MAX_CIPHER_LEN];      /*密文数据*/
    VOS_UINT8                          *pucPlainData;                                           /*明文数据*/
}TAF_XCALL_CIPHER_DECRYPTION_STRU;

/*****************************************************************************
结构名      : TAF_XCALL_CIPHER_VERIFY_STRU
结构说明    : 签名数据及密钥信息
  1.日    期   : 2015年10月23日
    作    者   : c00177591
    修改内容   : 新生成
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPubKeyLen;        /*密钥长度*/
    VOS_UINT8                           ucSigntureDataLen;  /*签名长度*/
    VOS_UINT8                           ucSigntureInfoLen;  /*签名信息长度*/

    VOS_UINT8                           aucReserved[1];

    VOS_UINT8                           aucPubKey[TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN];        /*密钥*/
    VOS_UINT8                           auSigntureData[TAF_XCALL_KMC_MSG_MAX_SIGN_DATA_LEN];     /*签名*/
    VOS_UINT8                           auSigntureInfo[TAF_XCALL_KMC_MSG_MAX_SIGN_INFO_LEN];     /*签名信息*/
}TAF_XCALL_CIPHER_VERIFY_STRU;

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
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_UINT32 TAF_XCALL_CipherInitVoice(
    VOS_UINT8                          *pucKs,
    VOS_UINT32                          ulCallDir
);

VOS_VOID TAF_XCALL_CipherEccInit(VOS_VOID);

VOS_UINT32 TAF_XCALL_CipherGenTmpKey(
    TAF_XCALL_KMC_PUB_KEY_STRU         *pstTmpPubKey,
    TAF_XCALL_KMC_PRIV_KEY_STRU        *pstTmpPrivKey
);

VOS_UINT32 TAF_XCALL_CipherEncrypt(
    TAF_XCALL_CIPHER_ENCRYPTION_STRU    *pstEncryptionDta
);

VOS_UINT32 TAF_XCALL_CipherDecrypt(
    TAF_XCALL_CIPHER_DECRYPTION_STRU    *pstEncryptionData
);

VOS_UINT32 TAF_XCALL_CipherVerify(
    TAF_XCALL_CIPHER_VERIFY_STRU        *pstVerifyData
);

VOS_UINT32 TAF_XCALL_CipherGetRandom(
    VOS_UINT32                          ulRandomLen,
    VOS_UINT8                          *pucRandom
);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
VOS_FLOAT TAF_XCALL_CipherGetInterValSecond(
    VOS_UINT32                          ulStartSlice,
    VOS_UINT32                          ulCurSlice
);

VOS_INT8 *TAF_XCALL_CipherHex2Ascii(
    VOS_UINT8                          *pucInput,
    VOS_UINT32                          ulInputLen,
    VOS_INT8                           *pscOutput,
    VOS_UINT32                          ulOutptuLen
);
#endif

#endif /*FEATURE_CHINA_TELECOM_VOICE_ENCRYPT*/
#endif /*FEATURE_UE_MODE_CDMA*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __TAF_X_CALL_ECC_CIPHER_H__ */
