/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名      : ScFactory.c
  版 本 号      : 初稿
  作    者      : w00184875
  生成日期      : 2012年04月07日
  最近修改      :
  功能描述      : 该C文件给出了ScComm模块的实现
  函数列表      :
  修改历史      :
  1.日    期    : 2012年04月16日
    作    者    : w00184875
    修改内容    : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ScInterface.h"
#include "ScComm.h"
#include "ScCtx.h"
#include "ScFactory.h"
#include "TafDrvAgent.h"
#include "omnvinterface.h"
#include "NVIM_Interface.h"

#ifdef __cplusplus
  #if __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e767 修改人:王笑非 00184875;原因:Log打印 */
#define    THIS_FILE_ID        PS_FILE_ID_SC_FACTORY_C
/*lint +e767 修改人:王笑非 00184875;*/

/*****************************************************************************
  2 全局变量声明
*****************************************************************************/

/*****************************************************************************
  3 函数申明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : SC_FAC_RsaDecrypt
 功能描述  : RSA解密接口
 输入参数  : pucCipherData: 密文
             ulCipherLen: 密文长度

 输出参数  : pucRawData: 明文
             pulLen: 明文长度
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月07日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_FAC_RsaDecrypt(
    VOS_UINT8                          *pucCipherData,
    VOS_UINT32                          ulCipherLen,
    VOS_UINT8                          *pucRawData,
    VOS_UINT32                         *pulLen
)
{
    VOS_UINT32                          ulResult;

    /* 判断是否通过产线鉴权 */
    if (SC_AUTH_STATUS_UNDO == SC_CTX_GetFacAuthStatus())
    {
        SC_ERROR_LOG("SC_FAC_RsaDecrypt: SC_CTX_GetFacAuthStatus is not done.");

        return SC_ERROR_CODE_IDENTIFY_FAIL;
    }

    ulResult = SC_COMM_RsaDecrypt(pucCipherData, ulCipherLen, pucRawData, pulLen);

    SC_INFO1_LOG("SC_FAC_RsaDecrypt: The Result is:", ulResult);

    return ulResult;

}

/*****************************************************************************
 函 数 名  : SC_FAC_RsaEncrypt
 功能描述  : NAS收到AT^PHONEPHYNUM?查询命令，通过该接口对物理号进行RSA加密
 输入参数  : pcRawData: 物理号，明文存储
             ulLen: 物理号长度

 输出参数  : pcCipherData: RSA加密后的密文
             pulCipherLen: RSA加密后的密文长度

 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月3日
    作    者   : w00184875
    修改内容   : 初始生成

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_FAC_RsaEncrypt(
    VOS_UINT8                          *pucRawData,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucCipherData,
    VOS_UINT32                         *pulCipherLen
)
{
    VOS_UINT32                          ulResult;

    /* 判断是否通过产线鉴权 */
    if (SC_AUTH_STATUS_UNDO == SC_CTX_GetFacAuthStatus())
    {
        SC_ERROR_LOG("SC_FAC_RsaEncrypt: SC_CTX_GetFacAuthStatus is not done.");

        return SC_ERROR_CODE_IDENTIFY_FAIL;
    }

    ulResult = SC_COMM_RsaEncrypt(pucRawData, ulLen, pucCipherData, pulCipherLen);

    SC_INFO1_LOG("SC_FAC_RsaEncrypt: The Result is", ulResult);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : SC_FAC_SetFacAuthPubKey
 功能描述  : NAS收到AT^FACAUTHPUBKEY命令，调用该接口进行鉴权密钥的写入
 输入参数  : pstSetFacAuthPubKey: 写入鉴权公钥的数据结构
 输出参数  : NA
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32类型的SC错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月7日
    作    者   : h59254
    修改内容   : AP-Modem锁网锁卡项目新增函数
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_FAC_SetFacAuthPubKey(SC_SET_FAC_AUTH_PUB_KEY_STRU *pstSetFacAuthPubKey)
{
    VOS_UINT32                          ulResult;
    VOS_INT                             lResult;
    VOS_UINT8                           aucSsk[SC_KEY_LEN];
    VOS_UINT8                           aucHash[SC_HASH_LEN];
    VOS_INT                             lHashLen;
    VOS_INT                             lCipherLen;
    VOS_UINT8                           aucCipherData[SC_SIGNATURE_LEN];
    VOS_UINT32                          ulKeyLen;

    /* 推导SSK密钥 */
    ulKeyLen = SC_KEY_LEN;

    ulResult = SC_COMM_GenerateKey(SC_SSK_STRING, SC_SSK_STRLEN, aucSsk, ulKeyLen);

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_FAC_SetFacAuthPubKey: SC_COMM_GenerateKey SSK is Failed.", ulResult);

        return ulResult;
    }

    /* 用MD5算法来计算AK的摘要 */
    lHashLen = SC_HASH_LEN;

    lResult = mdrv_crypto_hash((VOS_CHAR*)pstSetFacAuthPubKey->aucAuthPubKey,
                          SC_AUTH_PUB_KEY_LEN,
                          CRYPTO_ALGORITHM_SHA256,
                          (VOS_CHAR*)aucHash,
                          &lHashLen);

    /* 如果DRV计算返回的结果不是OK或者DRV计算出来的HASH不是16字节 */
    if ((VOS_OK != lResult) || (SC_HASH_LEN != lHashLen))
    {
        SC_ERROR2_LOG("SC_FAC_SetFacAuthPubKey: mdrv_crypto_hash is Failed.", lResult, lHashLen);
        /* 返回HASH生成失败 */
        return SC_ERROR_CODE_GENERATE_HASH_FAIL;
    }

    /* 用AES_ECB算法计算加密摘要 */
    lCipherLen = SC_SIGNATURE_LEN;

    lResult = mdrv_crypto_enc((VOS_CHAR*)aucHash,
                             lHashLen,
                             CRYPTO_ENCRYPT_ALGORITHM_AES_ECB,
                             (VOS_CHAR*)aucSsk,
                             (VOS_INT)ulKeyLen,
                             (VOS_CHAR*)aucCipherData,
                             &lCipherLen);

    /* 如果DRV计算返回的结果不是OK或计算出来的加密摘要不是16字节 */
    if ((VOS_OK != lResult) || (SC_SIGNATURE_LEN != lCipherLen))
    {
        SC_ERROR2_LOG("SC_FAC_SetFacAuthPubKey: mdrv_crypto_enc is Failed.", lResult, lCipherLen);
        /* 返回AES_ECB加密失败 */
        return SC_ERROR_CODE_AES_ECB_ENCRYPT_FAIL;
    }

    /* 将AT命令输入的加密摘要与计算得到的摘要进行对比 */
    if (VOS_OK != VOS_MemCmp(aucCipherData,
                             pstSetFacAuthPubKey->aucSignature,
                             SC_SIGNATURE_LEN))
    {
        SC_ERROR_LOG("SC_FAC_SetFacAuthPubKey: signature compare is Failed.");
        /* 返回摘要签名验证失败 */
        return SC_ERROR_CODE_VERIFY_PUB_KEY_SIGNATURE_FAIL;
    }

    /* 将AK内容写入AKFile.bin文件中 */
    ulResult = SC_COMM_WriteSecretFile(SC_SECRET_FILE_TYPE_AK,
                                       pstSetFacAuthPubKey->aucAuthPubKey,
                                       SC_AUTH_PUB_KEY_LEN);

    SC_INFO1_LOG("SC_FAC_SetFacAuthPubKey: The Result is:", ulResult);

    return ulResult;
}


/*****************************************************************************
 函 数 名  : SC_FAC_WriteHUK
 功能描述  : NAS收到AT^HUK命令，通过该SC封装的接口写入HUK
 输入参数  : pcHuk: HUK码流，128bit
             ucLen: HUK码流长度

 输出参数  : NA
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月9日
    作    者   : h59254
    修改内容   : AP-Modem锁网锁卡项目新增函数
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_FAC_WriteHUK(
    VOS_UINT8                          *pucHuk,
    VOS_UINT32                          ulLen
)
{
    VOS_INT                             lResult;

    /* 参数检查 */
    if ((SC_HUK_LEN != ulLen) || (VOS_NULL_PTR == pucHuk))
    {
        SC_ERROR_LOG("SC_FAC_WriteHUK: Para is wrong.");

        return SC_ERROR_CODE_WRITE_HUK_FAIL;
    }

    /* 通过底软接口写入HUK */
    lResult = mdrv_efuse_write_huk((VOS_CHAR*)pucHuk, (VOS_UINT)ulLen);

    if (VOS_OK != lResult)
    {
        SC_ERROR1_LOG("SC_FAC_WriteHUK: mdrv_efuse_write_huk is failed.", lResult);
        /* 返回HUK写入失败 */
        return SC_ERROR_CODE_WRITE_HUK_FAIL;
    }

    /* 返回操作成功 */
    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : SC_FAC_WriteIMEI
 功能描述  : NAS收到AT^PHONEPHYNUM令，通过该SC封装的接口把IMEI密文写入IMEIFile.bin并生成签名
 输入参数  : enModemID    : 卡0 或者卡1
             pucCipherData: IMEI密文码流
             ulCipherLen  : IMEI密文码流长度

 输出参数  : NA
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : d00212987
    修改内容   : IMEI验证
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_FAC_WriteIMEI(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT8                          *pucCipherData,
    VOS_UINT32                          ulCipherLen
)
{
    VOS_UINT32                          ulResult;

    /* 判断鉴权是否通过 */
    if (SC_AUTH_STATUS_DONE != SC_CTX_GetFacAuthStatus())
    {
        SC_ERROR_LOG("SC_FAC_WriteIMEI: SC_CTX_GetFacAuthStatus is not done.");

        return SC_ERROR_CODE_IDENTIFY_FAIL;
    }

    /* 参数检查 */
    if ((SC_RSA_ENCRYPT_LEN != ulCipherLen) || (VOS_NULL_PTR == pucCipherData))
    {
        SC_ERROR_LOG("SC_FAC_WriteIMEI: Para is wrong.");

        return SC_ERROR_CODE_PARA_FAIL;
    }

    /* 存入Flash 并生成签名 */
    SC_INFO1_LOG("#info:SC_FAC_WriteIMEI: modem id is: .", enModemID);
    if (MODEM_ID_0 == enModemID)
    {
        ulResult = SC_COMM_WriteSecretFile(SC_SECRET_FILE_TYPE_IMEI_I0,
                                           pucCipherData,
                                           ulCipherLen);
    }
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    else if (MODEM_ID_1 == enModemID)
    {
        ulResult = SC_COMM_WriteSecretFile(SC_SECRET_FILE_TYPE_IMEI_I1,
                                           pucCipherData,
                                           ulCipherLen);
    }
#if (3 == MULTI_MODEM_NUMBER)
    else if (MODEM_ID_2 == enModemID)
    {
        ulResult = SC_COMM_WriteSecretFile(SC_SECRET_FILE_TYPE_IMEI_I2,
                                           pucCipherData,
                                           ulCipherLen);
    }
#endif
#endif
    else
    {
        SC_ERROR_LOG("SC_FAC_WriteIMEI: modem id  error.");
        return SC_ERROR_CODE_MODEM_ID_FAIL;
    }

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_FAC_WriteIMEI: write IMEI is failed.", ulResult);

        /* 返回IMEI写入失败 */
        return SC_ERROR_CODE_WRITE_FILE_IMEI_FAIL;
    }

    /* 返回操作成功 */
    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : SC_FAC_StartIdentify
 功能描述  : NAS收到AT^IDENTIFYSTART后，通过该接口获取<identify_start_response>码流
 输入参数  : NA

 输出参数  : pstIdentifyStartRsp: 用于获取<identify_start_response>码流的数据结构，
             由调用者申请内存
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月07日
    作    者   : d00212987
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_FAC_StartIdentify(SC_IDENTIFY_START_RESPONSE_STRU *pstIdentifyStartRsp)
{
    VOS_UINT32                          ulResult;
    VOS_INT                             lResult;
    VOS_INT                             lIdentifyStartRspLen;
    SC_AK_FILE_STRU                    *pstAKFile;

    /* 清除鉴权状态全局变量 */
    SC_CTX_SetFacAuthStatus(SC_AUTH_STATUS_UNDO);

    /* 设置发起产线鉴权标志为VOS_FALSE */
    SC_CTX_SetIdentifyStartFlg(VOS_FALSE);

    /* 生成一个32位的随机数并保存到全局变量 */
    if (VOS_OK != mdrv_crypto_gen_rand((VOS_CHAR*)SC_CTX_GetFacRandDataAddr(),
                               SC_RAND_DATA_LEN))
    {
        SC_ERROR_LOG("SC_FAC_StartIdentify: mdrv_crypto_gen_rand is failed.");

        return SC_ERROR_CODE_GET_RAND_NUMBER_FAIL;
    }

    pstAKFile = (SC_AK_FILE_STRU*)VOS_MemAlloc(CCPU_PID_PAM_OM,
                                               DYNAMIC_MEM_PT,
                                               sizeof(SC_AK_FILE_STRU));

    if (VOS_NULL_PTR == pstAKFile)
    {
        SC_ERROR_LOG("SC_FAC_StartIdentify: VOS_MemAlloc is failed.");
        /* 返回内存申请失败 */
        return SC_ERROR_CODE_ALLOC_MEM_FAIL;
    }

    /* 读取AK-FILE并进行签名校验 */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_AK,
                                            pstAKFile->aucAuthPubKey,
                                            sizeof(SC_AK_FILE_STRU));

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_FAC_StartIdentify: SC_COMM_ReadSCFileAndCmpSign is failed.", ulResult);

        return ulResult;
    }

    /* 生成随机数的RSA密文 */
    lIdentifyStartRspLen = SC_RSA_ENCRYPT_LEN;

    lResult = mdrv_crypto_enc_rsa((VOS_CHAR*)SC_CTX_GetFacRandDataAddr(),
                                SC_RAND_DATA_LEN,
                                (VOS_CHAR*)pstAKFile->aucAuthPubKey,
                                SC_AUTH_PUB_KEY_LEN,
                                (VOS_CHAR*)pstIdentifyStartRsp->aucIdentifyStartRsp,
                                &lIdentifyStartRspLen);

    if ((VOS_OK != lResult) || (SC_RSA_ENCRYPT_LEN != lIdentifyStartRspLen))
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        SC_ERROR2_LOG("SC_FAC_StartIdentify: mdrv_crypto_enc_rsa is failed.", lResult, lIdentifyStartRspLen);

        return SC_ERROR_CODE_RSA_ENCRYPT_FAIL;
    }

    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
    /*lint +e534*/

    /* 设置发起产线鉴权标志为VOS_TRUE */
    SC_CTX_SetIdentifyStartFlg(VOS_TRUE);

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : SC_FAC_EndIdentify
 功能描述  : NAS收到AT^IDENTIFYEND命令后，通过该接口将<identify_end_request>码流提交给SC
 输入参数  : pstIdentifyEndReq: 用于存储<identify_end_request>码流的数据结构

 输出参数  : NA
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月3日
    作    者   : w00184875
    修改内容   : 初始生成

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_FAC_EndIdentify(SC_IDENTIFY_END_REQUEST_STRU *pstIdentifyEndReq)
{
    VOS_UINT32                          ulResult;
    VOS_INT                             lResult;
    VOS_UINT8                           aucRandData[SC_RAND_DATA_LEN];
    VOS_UINT8                           aucOldRandData[SC_RAND_DATA_LEN];
    VOS_INT                             lRandDataLen;
    SC_AK_FILE_STRU                    *pstAKFile;

    if ( VOS_TRUE != SC_CTX_GetIdentifyStartFlg())
    {
        SC_ERROR_LOG("SC_FAC_EndIdentify: Identify hasn't start!");
        return SC_ERROR_CODE_IDENTIFY_FAIL;
    }

    /*lint -e534*/
    VOS_MemCpy(aucOldRandData, SC_CTX_GetFacRandDataAddr(), SC_RAND_DATA_LEN);

    VOS_MemSet(SC_CTX_GetFacRandDataAddr(), 0, SC_RAND_DATA_LEN);
    /*lint +e534*/

    pstAKFile = (SC_AK_FILE_STRU*)VOS_MemAlloc(CCPU_PID_PAM_OM,
                                               DYNAMIC_MEM_PT,
                                               sizeof(SC_AK_FILE_STRU));

    if (VOS_NULL_PTR == pstAKFile)
    {
        SC_ERROR_LOG("SC_FAC_EndIdentify: VOS_MemAlloc is failed.");
        /* 返回内存申请失败 */
        return SC_ERROR_CODE_ALLOC_MEM_FAIL;
    }

    /* 读取AK-FILE并进行签名校验 */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_AK,
                                            pstAKFile->aucAuthPubKey,
                                            sizeof(SC_AK_FILE_STRU));

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_FAC_EndIdentify: SC_COMM_ReadSCFileAndCmpSign is failed.", ulResult);

        return ulResult;
    }

    /* 对输入的密文进行RSA解密 */
    lRandDataLen = SC_RAND_DATA_LEN;

    lResult = mdrv_crypto_dec_rsa((VOS_CHAR*)pstIdentifyEndReq->aucIdentifyEndReq,
                                 sizeof(SC_IDENTIFY_END_REQUEST_STRU),
                                 (VOS_CHAR*)pstAKFile->aucAuthPubKey,
                                 sizeof(pstAKFile->aucAuthPubKey),
                                 (VOS_CHAR*)aucRandData, &lRandDataLen);

    if ((VOS_OK != lResult) || (SC_RAND_DATA_LEN != lRandDataLen))
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        SC_ERROR2_LOG("SC_FAC_EndIdentify: mdrv_crypto_dec_rsa is failed.", lResult, lRandDataLen);

        return SC_ERROR_CODE_RSA_DECRYPT_FAIL;
    }

    /* 与SC_StartIdentify生成的随机数进行比对 */
    if (VOS_OK != VOS_MemCmp(aucRandData, aucOldRandData, SC_RAND_DATA_LEN))
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        SC_ERROR_LOG("SC_FAC_EndIdentify: VOS_MemCmp RandData is failed.");

        return SC_ERROR_CODE_IDENTIFY_FAIL;
    }

    /* 更新鉴权状态为通过 */
    SC_CTX_SetFacAuthStatus(SC_AUTH_STATUS_DONE);

    /* 设置发起产线鉴权标志为VOS_FALSE */
    SC_CTX_SetIdentifyStartFlg(VOS_FALSE);

    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
    /*lint +e534*/

    return SC_ERROR_CODE_NO_ERROR;
}


/*****************************************************************************
 函 数 名  : SC_FAC_SetPortAttrib
 功能描述  : NAS收到AT^PORTATTRIBSET设置命令后，通过该接口将端口锁属性信息提交给SC
 输入参数  : pstSetPortAttrib: 端口锁属性相关信息

 输出参数  : NA
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月09日
    作    者   : d00212987
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_FAC_SetPortAttrib(SC_SET_PORT_ATTRIBUTE_STRU *pstSetPortAttrib)
{
    VOS_UINT32                          ulResult;
    VOS_INT                             lResult;
    VOS_INT                             lDKPwdDataLen;
    VOS_UINT8                           aucDKPwd[SC_PERS_PWD_LEN];
    SC_AK_FILE_STRU                    *pstAKFile;
    SC_DK_FILE_STRU                     stDKFileContent;
    VOS_UINT8                           ucLoop;

    /* 判断鉴权是否通过 */
    if (SC_AUTH_STATUS_DONE != SC_CTX_GetFacAuthStatus())
    {
        SC_ERROR_LOG("SC_FAC_SetPortAttrib: SC_CTX_GetFacAuthStatus is not done.");

        return SC_ERROR_CODE_IDENTIFY_FAIL;
    }

    /* 申请AK文件的内存 */
    pstAKFile = (SC_AK_FILE_STRU*)VOS_MemAlloc(CCPU_PID_PAM_OM,
                                               DYNAMIC_MEM_PT,
                                               sizeof(SC_AK_FILE_STRU));

    if (VOS_NULL_PTR == pstAKFile)
    {
        SC_ERROR_LOG("SC_FAC_SetPortAttrib: VOS_MemAlloc is failed.");
        /* 返回内存申请失败 */
        return SC_ERROR_CODE_ALLOC_MEM_FAIL;
    }

    /* 读取AK-FILE并进行签名校验 */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_AK,
                                            pstAKFile->aucAuthPubKey,
                                            sizeof(SC_AK_FILE_STRU));

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_FAC_SetPortAttrib: SC_COMM_ReadSCFileAndCmpSign is failed.", ulResult);

        return ulResult;
    }

    /* 对输入的密文进行RSA解密 */
    lDKPwdDataLen = SC_PERS_PWD_LEN;

    lResult = mdrv_crypto_dec_rsa((VOS_CHAR*)pstSetPortAttrib->aucRsaPwd,
                                 sizeof(pstSetPortAttrib->aucRsaPwd),
                                 (VOS_CHAR*)pstAKFile->aucAuthPubKey,
                                 sizeof(pstAKFile->aucAuthPubKey),
                                 (VOS_CHAR*)aucDKPwd, &lDKPwdDataLen);

    if ((VOS_OK != lResult) || (SC_PERS_PWD_LEN != lDKPwdDataLen))
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        return SC_ERROR_CODE_RSA_DECRYPT_FAIL;
    }

    /* 判断解密后的DK密码明文是否为数值为"0"~"9"的数字 */
    for (ucLoop = 0; ucLoop < SC_PERS_PWD_LEN; ucLoop++)
    {
        if (0x09 < aucDKPwd[ucLoop])
        {
            /*lint -e534*/
            VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
            /*lint +e534*/

            SC_ERROR_LOG("SC_FAC_SetPortAttrib: aucDKPwd is incorrect!");

            return SC_ERROR_CODE_OTHER_ERROR;
        }
    }

    /* 生成DK密文 */
    ulResult = SC_COMM_GenerateCryptoPwd(SC_CRYPTO_PASSWORD_TYPE_DK,
                                         aucDKPwd,
                                         SC_PERS_PWD_LEN,
                                         stDKFileContent.aucDKCryptoPwd,
                                         SC_CRYPTO_PWD_LEN);

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_FAC_SetPortAttrib: SC_COMM_GenerateCryptoPwd is failed.", ulResult);

        return ulResult;
    }

    /* 生成DKFile.bin文件 */
    stDKFileContent.enPortStatus = pstSetPortAttrib->enStatus;

    ulResult = SC_COMM_WriteSecretFile(SC_SECRET_FILE_TYPE_DK,
                                       (VOS_UINT8*)&stDKFileContent,
                                       sizeof(SC_DK_FILE_STRU));

    SC_INFO1_LOG("SC_FAC_SetPortAttrib: The result is:", ulResult);

    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
    /*lint +e534*/

    return ulResult;
}

/*****************************************************************************
 函 数 名  : SC_FAC_GetPortAttrib
 功能描述  : 获取端口状态
 输入参数  : 无

 输出参数  : penStatus: 端口状态
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月07日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_FAC_GetPortAttrib(
    SC_PORT_STATUS_ENUM_UINT32         *penStatus
)
{
    SC_DK_FILE_STRU                     stDKFile;
    VOS_UINT32                          ulResult;

    /* 若HUK未写入，无效时，则默认HSIC的OM口打开 */
    if (VOS_FALSE == mdrv_efuse_check_huk_valid())
    {
        *penStatus = SC_PORT_STATUS_ON;

        SC_ERROR_LOG("#info:SC_FAC_GetPortAttrib:huk not valid");

        return SC_ERROR_CODE_NO_ERROR;
    }

    /* 读取DK-FILE并校验签名 */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_DK,
                                            (VOS_UINT8*)&stDKFile,
                                            sizeof(SC_DK_FILE_STRU));

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_FAC_GetPortAttrib: SC_COMM_ReadSCFileAndCmpSign is failed.", ulResult);

        return ulResult;
    }

    /* 返回端口状态 */
    *penStatus = stDKFile.enPortStatus;

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : SC_FAC_VerifyPortPassword
 功能描述  : NAS收到AT^PORTCTRLTMP命令，调用该接口进行端口锁密码校验
 输入参数  : pcPwd: 端口锁密码，密码为明文传送(密码为16个“0”-“9”字符组成)
             ucLen: 端口锁密码长度

 输出参数  : NA
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月7日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_FAC_VerifyPortPassword(
    VOS_UINT8                          *pucPwd,
    VOS_UINT8                           ucLen
)
{
    VOS_UINT32                          ulResult;
    VOS_INT32                           lResult;
    VOS_UINT8                           aucCryptoPwd[SC_CRYPTO_PWD_LEN];
    SC_DK_FILE_STRU                     stDKFile;

    ulResult = SC_ERROR_CODE_BUTT;

    /* 若HUK未写入，无效时，则默认密码校验通过 */
    if (VOS_FALSE == mdrv_efuse_check_huk_valid())
    {
        SC_ERROR_LOG("#info:SC_FAC_VerifyPortPassword:huk not valid.");

        return SC_ERROR_CODE_NO_ERROR;
    }

    /* 参数检查 */
    if ((VOS_NULL_PTR == pucPwd) || (SC_CRYPTO_PWD_LEN != ucLen))
    {
        return ulResult;
    }

    /* 读取DK-FILE并进行校验 */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_DK,
                                            (VOS_UINT8*)&stDKFile,
                                            sizeof(SC_DK_FILE_STRU));

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_FAC_VerifyPortPassword: SC_COMM_ReadSCFileAndCmpSign is failed.", ulResult);

        return ulResult;
    }

    /* 生成DK密文 */
    ulResult = SC_COMM_GenerateCryptoPwd(SC_CRYPTO_PASSWORD_TYPE_DK,
                                         pucPwd, ucLen, aucCryptoPwd,
                                         SC_CRYPTO_PWD_LEN);

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_FAC_VerifyPortPassword: SC_COMM_GenerateCryptoPwd is failed.", ulResult);

        return ulResult;
    }

    /* 比对DK密文 */
    lResult = VOS_MemCmp(aucCryptoPwd, stDKFile.aucDKCryptoPwd, SC_CRYPTO_PWD_LEN);
    if (VOS_OK != lResult)
    {
        SC_ERROR_LOG("SC_FAC_VerifyPortPassword: VOS_MemCmp DK is failed.");

        return SC_ERROR_CODE_DK_INCORRECT;
    }

    return SC_ERROR_CODE_NO_ERROR;
}

#if (FEATURE_ON == FEATURE_VSIM)
/*****************************************************************************
 函 数 名  : SC_FAC_SetDhKey
 功能描述  : NAS收到AT^HVPDH设置命令后，通过该接口将DH KEY提交给SC
 输入参数  : MODEM_ID_ENUM_UINT16         enModemID,
             SC_DH_KEY_TYPE_ENUM_UINT32   enKeyType,
             VOS_UINT32                   ulKeyLen,
             VOS_UINT8                   *pucKey

 输出参数  : NA
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月27日
    作    者   : L47619
    修改内容   : V9R1 vSIM项目修改

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_FAC_SetDhKey(
    MODEM_ID_ENUM_UINT16                enModemID,
    SC_DH_KEY_TYPE_ENUM_UINT32          enKeyType,
    VOS_UINT32                          ulKeyLen,
    VOS_UINT8                          *pucKey
)
{
    VOS_UINT32                          ulResult;
    NVIM_VSIM_HVSDH_NV_STRU             stDhNv;

    /* 判断鉴权是否通过 */
    if (SC_AUTH_STATUS_DONE != SC_CTX_GetFacAuthStatus())
    {
        SC_ERROR_LOG("SC_FAC_SetDhKey: SC_CTX_GetFacAuthStatus is not done.");

        return SC_ERROR_CODE_IDENTIFY_NOT_FINISH;
    }

    /* 从NV项中读出密钥信息 */
    ulResult = NV_ReadEx(enModemID, en_NV_Item_VSIM_HVSDH_INFO, &stDhNv, sizeof(stDhNv));
    if (NV_OK != ulResult)
    {
        SC_ERROR_LOG("SC_FAC_SetDhKey: NV_Read fail.");
        return SC_ERROR_CODE_NV_READ_FAIL;
    }

    if (SC_DH_KEY_SERVER_PUBLIC_KEY == enKeyType)
    {
        /*lint -e534*/
        VOS_MemCpy(stDhNv.stSPublicKey.aucKey, pucKey, ulKeyLen);
        /*lint +e534*/
        stDhNv.stSPublicKey.ulKeyLen = ulKeyLen;
    }
    else if (SC_DH_KEY_MODEM_PUBLIC_KEY == enKeyType)
    {
        /*lint -e534*/
        VOS_MemCpy(stDhNv.stCPublicKey.aucKey, pucKey, ulKeyLen);
        /*lint +e534*/
        stDhNv.stCPublicKey.ulKeyLen = ulKeyLen;
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(stDhNv.stCPrivateKey.aucKey, pucKey, ulKeyLen);
        /*lint +e534*/
        stDhNv.stCPrivateKey.ulKeyLen = ulKeyLen;
    }

    /* 将服务器公钥写入NV项中 */
    ulResult = NV_WriteEx(enModemID, en_NV_Item_VSIM_HVSDH_INFO, &stDhNv, sizeof(stDhNv));
    if (NV_OK != ulResult)
    {
        SC_ERROR_LOG("SC_FAC_SetDhKey: NV_Write fail.");

        return SC_ERROR_CODE_NV_WRITE_FAIL;
    }

    return SC_ERROR_CODE_NO_ERROR;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

