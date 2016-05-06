/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名      : ScComm.c
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
#include "pamom.h"

#ifdef __cplusplus
  #if __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e767 修改人:王笑非 00184875;原因:Log打印 */
#define    THIS_FILE_ID        PS_FILE_ID_SC_COMM_C
/*lint +e767 修改人:王笑非 00184875;*/

#if(VOS_WIN32 == VOS_OS_VER)
#define SC_IMEI_LOG_FILE_PATH           ".\\yaffs0\\OAM_IMEI_Log.bin"
#define SC_IMEI_UNITARY_LOG_FILE_PATH   ".\\yaffs0\\OAM_IMEI_Log.bin"
#else
#define SC_IMEI_LOG_FILE_PATH           "/mnvm3:0/OAM_IMEI_Log.bin"
#define SC_IMEI_UNITARY_LOG_FILE_PATH   "/modem_log/OAM_IMEI_Log.bin"
#endif

/*****************************************************************************
  2 全局变量声明
*****************************************************************************/

/*****************************************************************************
  3 函数申明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : SC_COMM_ReadFile
 功能描述  : 读取文件接口
 输入参数  : pcFilePath: 文件路径
             ulContentLen: 文件长度

 输出参数  : pucContent: 文件内容

 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月18日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_COMM_ReadFile(
    VOS_CHAR                           *pcFilePath,
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLen
)
{
    VOS_INT32                          lReadSize;
    FILE                               *pFile;

    /* 打开指定类型的签名文件 */
    pFile = mdrv_file_open(pcFilePath, "rb");

    if (VOS_NULL_PTR == pFile)
    {
        SC_ERROR_LOG("SC_COMM_ReadFile: mdrv_file_open is failed.");

        return SC_ERROR_CODE_OPEN_FILE_FAIL;
    }

    /* 读取文件内容 */
    lReadSize = mdrv_file_read((VOS_CHAR*)pucContent, sizeof(VOS_CHAR), ulContentLen, pFile);

    if ((VOS_INT32)ulContentLen != lReadSize)
    {
        /*lint -e534*/
        mdrv_file_close(pFile);
        /*lint +e534*/

        SC_ERROR_LOG("SC_COMM_ReadFile: mdrv_file_read is failed.");

        return SC_ERROR_CODE_READ_FILE_FAIL;
    }

    /* 关闭文件 */
    /*lint -e534*/
    mdrv_file_close(pFile);
    /*lint +e534*/

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : SC_COMM_WriteFile
 功能描述  : 读取文件接口
 输入参数  : pcFilePath: 文件路径
             ulContentLen: 文件长度

 输出参数  : pucContent: 文件内容

 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月18日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_COMM_WriteFile(
    VOS_CHAR                           *pcFilePath,
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLen
)
{
    VOS_INT32                           lWriteSize;
    FILE                               *pFile;

    /* 创建安全文件 */
    pFile = mdrv_file_open(pcFilePath, "wb+");

    /* 返回空指针，返回错误值 */
    if (VOS_NULL_PTR == pFile)
    {
        SC_ERROR_LOG("SC_COMM_WriteFile: mdrv_file_open is failed.");

        return SC_ERROR_CODE_OPEN_FILE_FAIL;
    }

    /* 写入安全文件码流，返回长度与实际长度不一致，返回错误值并关闭文件 */
    lWriteSize = mdrv_file_write_sync((VOS_CHAR*)pucContent, sizeof(VOS_CHAR), ulContentLen, pFile);

    if (lWriteSize != (VOS_INT32)ulContentLen)
    {
        /*lint -e534*/
        mdrv_file_close(pFile);

        SC_ERROR_LOG("SC_COMM_WriteFile: mdrv_file_write_sync is failed.");
        /*lint +e534*/

        return SC_ERROR_CODE_WRITE_FILE_FAIL;
    }

    /* 关闭文件 */
    /*lint -e534*/
    mdrv_file_close(pFile);
    /*lint +e534*/

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : SC_COMM_GenerateKey
 功能描述  : 生成IPK/SSK/DSSK
 输入参数  : pucData: 字符串
             ucLen: 字符串长度
             ulKeyLen: KEY长度

 输出参数  : pucKey: KEY内容

 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月09日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_COMM_GenerateKey(
    VOS_CHAR                           *pcData,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucKey,
    VOS_UINT32                          ulKeyLen
)
{
    VOS_INT32                           lResult;
    VOS_INT                             lNewKeyLen;

    lNewKeyLen = (VOS_INT)ulKeyLen;

    /* 调用底软接口生成 */
    lResult = mdrv_crypto_gen_key(pcData,
                                (VOS_INT)ulLen,
                                CREATE_CRYPTO_KEY_ALGORITHM_SHA256,
                                (VOS_CHAR*)pucKey,
                                &lNewKeyLen);

    /* 如果算法返回失败，回复错误码SC_ERROR_CODE_CREAT_KEY_FAIL */
    if ((VOS_OK != lResult) || ((VOS_INT)ulKeyLen != lNewKeyLen))
    {
        SC_ERROR2_LOG("SC_COMM_GenerateKey: mdrv_crypto_gen_key is failed.", lResult, lNewKeyLen);

        return SC_ERROR_CODE_CREATE_KEY_FAIL;
    }

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : SC_COMM_GenerateCryptoPwd
 功能描述  : 生成CK/UK/DK密码的密文
 输入参数  : enPwdType: 密码类型
             pucPwd: 密码为明文传送(密码为16个“0”-“9”字符组成)
             ucPwdLen: 密码长度
             ucCryptoPwdLen: 密码的密文长度

 输出参数  : pucCryptoPwd: 密码的密文

 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月09日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_COMM_GenerateCryptoPwd(
    SC_CRYPTO_PASSWORD_TYPE_ENUM_UINT8  enPwdType,
    VOS_UINT8                          *pucPwd,
    VOS_UINT8                           ucPwdLen,
    VOS_UINT8                          *pucCryptoPwd,
    VOS_UINT32                          ulCryptoPwdLen
)
{
    VOS_UINT8                           aucKey[SC_KEY_LEN];
    VOS_INT32                           lResult;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulKeyLen;
    VOS_INT                             lNewCryptoPwdLen;

    ulKeyLen = SC_KEY_LEN;

    /* 如果是CK/UK */
    if (SC_CRYPTO_PASSWORD_TYPE_CK == enPwdType)
    {
        /* 生成SSK */
        ulResult = SC_COMM_GenerateKey(SC_SSK_STRING, SC_SSK_STRLEN, aucKey, ulKeyLen);
    }
    /* 如果是DK */
    else if (SC_CRYPTO_PASSWORD_TYPE_DK == enPwdType)
    {
        /* 生成DSSK */
        ulResult = SC_COMM_GenerateKey(SC_DSSK_STRING, SC_DSSK_STRLEN, aucKey, ulKeyLen);
    }
    else
    {
        SC_WARNING1_LOG("SC_COMM_GenerateCryptoPwd: Password Type is not support.", enPwdType);

        return SC_ERROR_CODE_NO_ERROR;
    }

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR2_LOG("SC_COMM_GenerateCryptoPwd: SC_COMM_GenerateKey is failed.", enPwdType, ulResult);

        return ulResult;
    }

    lNewCryptoPwdLen = (VOS_INT)ulCryptoPwdLen;
    /* 调用底软接口加密密码 */
    lResult = mdrv_crypto_enc((VOS_CHAR*)pucPwd,
                             ucPwdLen,
                             CRYPTO_ENCRYPT_ALGORITHM_AES_ECB,
                             (VOS_CHAR*)aucKey,
                             (VOS_INT)ulKeyLen,
                             (VOS_CHAR*)pucCryptoPwd,
                             &lNewCryptoPwdLen);

    /* 如果返回失败 */
    if ((VOS_OK != lResult) || ((VOS_INT)ulCryptoPwdLen != lNewCryptoPwdLen))
    {
        SC_ERROR2_LOG("SC_COMM_GenerateCryptoPwd: mdrv_crypto_enc is failed.", lResult, lNewCryptoPwdLen);

        return SC_ERROR_CODE_AES_ECB_ENCRYPT_FAIL;
    }

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : SC_COMM_GenerateSignCode
 功能描述  : 文件签名的计算
 输入参数  : pucContent: 文件内容
             ucContentLen: 文件内容长度
             ucSignCodeLen: 文件签名长度

 输出参数  : pucSignCode: 文件签名码流

 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月07日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_COMM_GenerateSignCode(
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLen,
    VOS_UINT8                          *pucSignCode,
    VOS_UINT32                          ulSignCodeLen
)
{
    VOS_UINT8                           aucKey[SC_KEY_LEN];
    VOS_UINT8                           aucHashData[SC_HASH_LEN];
    VOS_INT                             lHashLen;
    VOS_UINT32                          ulKeyLen;
    VOS_UINT32                          ulResult;
    VOS_INT32                           lResult;
    VOS_INT                             lNewSignCodeLen;

    ulKeyLen  = SC_KEY_LEN;

    /* 生成IPK */
    ulResult = SC_COMM_GenerateKey(SC_IPK_STRING, SC_IPK_STRLEN, aucKey, ulKeyLen);
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_COMM_GenerateSignCode: SC_COMM_GenerateKey is failed.", ulResult);

        return ulResult;
    }

    /* SHA256(文件内容) */
    lHashLen = SC_HASH_LEN;

    lResult = mdrv_crypto_hash((VOS_CHAR*)pucContent,
                          (VOS_INT)ulContentLen,
                          CRYPTO_ALGORITHM_SHA256,
                          (VOS_CHAR*)aucHashData,
                          &lHashLen);

    /* 算法返回失败或长度不为32字节 */
    if ((VOS_OK != lResult) || (SC_HASH_LEN != lHashLen))
    {
        SC_ERROR2_LOG("SC_COMM_GenerateSignCode: mdrv_crypto_hash is failed.", lResult, lHashLen);

        return SC_ERROR_CODE_GENERATE_HASH_FAIL;
    }

    lNewSignCodeLen = (VOS_INT)ulSignCodeLen;
    /* AES_ECB(hash,IPK) */
    lResult = mdrv_crypto_enc((VOS_CHAR*)aucHashData,
                             lHashLen,
                             CRYPTO_ENCRYPT_ALGORITHM_AES_ECB,
                             (VOS_CHAR*)aucKey,
                             (VOS_INT)ulKeyLen,
                             (VOS_CHAR*)pucSignCode,
                             &lNewSignCodeLen);

    /* 算法返回失败或长度不为32字节 */
    if ((VOS_OK != lResult) || ((VOS_INT)ulSignCodeLen != lNewSignCodeLen))
    {
        SC_ERROR2_LOG("SC_COMM_GenerateSignCode: mdrv_crypto_enc is failed.", lResult, lNewSignCodeLen);

        return SC_ERROR_CODE_AES_ECB_ENCRYPT_FAIL;
    }

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : SC_COMM_CreateSignFile
 功能描述  : 创建签名文件
 输入参数  : enFileType: 文件类型
             pucContent: 文件内容
             ucContentLen: 文件内容长度

 输出参数  : NA
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月07日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_COMM_CreateSignFile(
    SC_SECRET_FILE_TYPE_ENUM_UINT8      enFileType,
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLen
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucSignCode[SC_HASH_LEN];
    SC_COMM_GLOBAL_STRU                *pstCommGlobal;

    /* 计算文件的签名 */
    ulResult = SC_COMM_GenerateSignCode(pucContent,
                                        ulContentLen,
                                        aucSignCode,
                                        SC_HASH_LEN);

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_COMM_CreateSignFile: SC_COMM_GenerateSignCode is failed.", ulResult);

        return ulResult;
    }

    pstCommGlobal = SC_CTX_GetCommGlobalVarAddr();

    ulResult = SC_COMM_WriteFile(pstCommGlobal->acSignFileName[enFileType],
                                 aucSignCode,
                                 SC_HASH_LEN);

    SC_INFO1_LOG("SC_COMM_CreateSignFile: SC_COMM_WriteFile result is", ulResult);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : SC_COMM_ReadSignFile
 功能描述  : 签名文件的读取
 输入参数  : enFileType: 文件类型

 输出参数  : pucContent: 签名文件内容
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月07日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_COMM_ReadSignFile(
    SC_SECRET_FILE_TYPE_ENUM_UINT8      enFileType,
    VOS_UINT8                          *pucContent
)
{
    VOS_UINT32                          ulResult;
    SC_COMM_GLOBAL_STRU                *pstCommGlobal;

    pstCommGlobal = SC_CTX_GetCommGlobalVarAddr();

    ulResult = SC_COMM_ReadFile(pstCommGlobal->acSignFileName[enFileType],
                                pucContent,
                                SC_SIGNATURE_LEN);

    SC_INFO1_LOG("SC_COMM_ReadSignFile: SC_COMM_ReadFile result is", ulResult);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : SC_COMM_WriteSecretFile
 功能描述  : 创建安全文件
 输入参数  : enFileType: 文件类型
             pucContent: 文件内容
             ucContentLen: 文件内容长度

 输出参数  : NA
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月07日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_COMM_WriteSecretFile(
    SC_SECRET_FILE_TYPE_ENUM_UINT8      enFileType,
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLen
)
{
    VOS_UINT32                          ulResult;
    SC_COMM_GLOBAL_STRU                *pstCommGlobal;

    pstCommGlobal = SC_CTX_GetCommGlobalVarAddr();

    ulResult = SC_COMM_WriteFile(pstCommGlobal->acSecretFileName[enFileType],
                                 pucContent,
                                 ulContentLen);

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_COMM_WriteSecretFile: SC_COMM_WriteFile is failed.", ulResult);

        return ulResult;
    }

    /* 创建文件对应的签名文件 */
    ulResult = SC_COMM_CreateSignFile(enFileType, pucContent, ulContentLen);

    SC_INFO1_LOG("SC_COMM_WriteSecretFile: SC_COMM_CreateSignFile result is", ulResult);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : SC_COMM_ReadSCFileAndCmpSign
 功能描述  : 读取锁网锁卡相关的安全文件并进行安全校验
 输入参数  : enFileType: 读取文件类型
             ulContentLen: 读取文件长度

 输出参数  : pucContent: 文件内容
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月07日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_COMM_ReadSCFileAndCmpSign(
    SC_SECRET_FILE_TYPE_ENUM_UINT8      enFileType,
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLen
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucSignCode[SC_SIGNATURE_LEN];
    SC_SIGN_FILE_STRU                   stSignFile;
    SC_COMM_GLOBAL_STRU                *pstCommGlobal;

    pstCommGlobal = SC_CTX_GetCommGlobalVarAddr();

    ulResult = SC_COMM_ReadFile(pstCommGlobal->acSecretFileName[enFileType],
                                pucContent,
                                ulContentLen);

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_COMM_ReadSCFileAndCmpSign: SC_COMM_ReadFile is failed.", ulResult);

        return ulResult;
    }

    /* 计算文件的签名码流 */
    ulResult = SC_COMM_GenerateSignCode(pucContent,
                                        ulContentLen,
                                        aucSignCode,
                                        SC_SIGNATURE_LEN);

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_COMM_ReadSCFileAndCmpSign: SC_COMM_GenerateSignCode is failed.", ulResult);

        return ulResult;
    }

    /* 读取签名文件 */
    ulResult = SC_COMM_ReadSignFile(enFileType, stSignFile.aucSignature);
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_COMM_ReadSCFileAndCmpSign: SC_COMM_ReadSignFile is failed.", ulResult);

        return ulResult;
    }

    /* 比较两个文件签名 */
    if (VOS_OK != VOS_MemCmp(aucSignCode, stSignFile.aucSignature, SC_SIGNATURE_LEN))
    {
        SC_ERROR_LOG("SC_COMM_ReadSCFileAndCmpSign: Signature compare is failed.");

        return SC_ERROR_CODE_VERIFY_SIGNATURE_FAIL;
    }

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : SC_COMM_RsaDecrypt
 功能描述  : RSA解密接口
 输入参数  : pucPwd: 密文
             ulCipherLen: 密文长度

 输出参数  : pucPubContent: 明文
             pulPubLen: 明文长度
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月07日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_COMM_RsaDecrypt(
    VOS_UINT8                          *pucPwd,
    VOS_UINT32                          ulCipherLen,
    VOS_UINT8                          *pucPubContent,
    VOS_UINT32                         *pulPubLen
)
{
    VOS_UINT32                          ulResult;
    VOS_INT32                           lResult;
    VOS_UINT32                          ulLen;
    SC_AK_FILE_STRU                    *pstAKFile;

    pstAKFile = (SC_AK_FILE_STRU*)VOS_MemAlloc(CCPU_PID_PAM_OM, DYNAMIC_MEM_PT, sizeof(SC_AK_FILE_STRU));

    if (VOS_NULL_PTR == pstAKFile)
    {
        SC_ERROR_LOG("SC_COMM_RsaDecrypt: VOS Alloc Memory is failed.");
        /* 返回内存申请失败 */
        return SC_ERROR_CODE_ALLOC_MEM_FAIL;
    }

    /* 读取AK-FILE并校验签名 */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_AK,
                                            pstAKFile->aucAuthPubKey,
                                            sizeof(SC_AK_FILE_STRU));

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_COMM_RsaDecrypt: SC_COMM_ReadSCFileAndCmpSign is failed.", ulResult);

        return ulResult;
    }

    ulLen = *pulPubLen;

    /* 对输入的密文进行RSA解密 */
    lResult = mdrv_crypto_dec_rsa((VOS_CHAR*)pucPwd,
                                 (VOS_INT)ulCipherLen,
                                 (VOS_CHAR*)pstAKFile->aucAuthPubKey,
                                 sizeof(SC_AK_FILE_STRU),
                                 (VOS_CHAR*)pucPubContent,
                                 (VOS_INT*)pulPubLen);

    /* 底软返回失败 */
    if ((VOS_OK != lResult) || (ulLen != *pulPubLen))
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        SC_ERROR2_LOG("SC_COMM_RsaDecrypt: mdrv_crypto_dec_rsa is failed.", lResult, *pulPubLen);

        return SC_ERROR_CODE_RSA_DECRYPT_FAIL;
    }

    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
    /*lint +e534*/

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : SC_COMM_RsaEncrypt
 功能描述  : NAS收到AT^PHONEPHYNUM?查询命令，通过该接口对物理号进行RSA加密
 输入参数  : pucRawData: 物理号，明文存储
             ulLen: 物理号长度
             pucCipherData: RSA加密后的密文
             pulCipherLen: RSA加密后的密文长度

 输出参数  : NA
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月3日
    作    者   : w00184875
    修改内容   : 初始生成

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_COMM_RsaEncrypt(
    VOS_UINT8                          *pucRawData,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucCipherData,
    VOS_UINT32                         *pulCipherLen
)
{
    VOS_UINT32                          ulResult;
    VOS_INT32                           lResult;
    SC_AK_FILE_STRU                    *pstAKFile;

    pstAKFile = (SC_AK_FILE_STRU*)VOS_MemAlloc(CCPU_PID_PAM_OM, DYNAMIC_MEM_PT, sizeof(SC_AK_FILE_STRU));

    if (VOS_NULL_PTR == pstAKFile)
    {
        SC_ERROR_LOG("SC_COMM_RsaDecrypt: VOS Alloc Memory is failed.");
        /* 返回内存申请失败 */
        return SC_ERROR_CODE_ALLOC_MEM_FAIL;
    }

    /* 读取AK-FILE并校验签名 */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_AK,
                                            pstAKFile->aucAuthPubKey,
                                            sizeof(SC_AK_FILE_STRU));

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_COMM_RsaEncrypt: SC_COMM_ReadSCFileAndCmpSign is failed.", ulResult);

        return ulResult;
    }

    *pulCipherLen = SC_RSA_ENCRYPT_LEN;

    /* 对输入的明文进行RSA加密 */
    lResult = mdrv_crypto_enc_rsa((VOS_CHAR*)pucRawData,
                                (VOS_INT)ulLen,
                                (VOS_CHAR*)pstAKFile->aucAuthPubKey,
                                sizeof(SC_AK_FILE_STRU),
                                (VOS_CHAR*)pucCipherData,
                                (VOS_INT*)pulCipherLen);

    /* 底软返回失败 */
    if ((VOS_OK != lResult) || (SC_RSA_ENCRYPT_LEN != *pulCipherLen))
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        SC_ERROR2_LOG("SC_COMM_RsaEncrypt: mdrv_crypto_enc_rsa is failed.", lResult, *pulCipherLen);

        return SC_ERROR_CODE_RSA_ENCRYPT_FAIL;
    }

    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
    /*lint +e534*/

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : SC_COMM_GetUsimmCachedFile
 功能描述  : SC模块读取USIMM模块缓存文件封装接口
 输入参数  :enModemID:Modem ID
 输出参数  :usFileID:读取的文件ID
            pulDataLen:返回文件的内容长度
            ppucData:返回文件内容的地址
            enAppType:应用类型
 返 回 值  : VOS_OK/VOS_ERR
 修改历史      :
  1.日    期   : 2013年8月15日
    作    者   : h59254
    修改内容   : 初始生成
*****************************************************************************/
VOS_UINT32 SC_COMM_GetUsimmCachedFile(
    VOS_CHAR                           *pucFilePath,
    VOS_UINT32                         *pulDataLen,
    VOS_UINT8                         **ppucData,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    MODEM_ID_ENUM_UINT16                enModemID)
{
    if (VOS_TRUE == USIMM_IsSvlte())
    {
        return USIMM_GetCachedFile_Instance(MODEM_ID_0, pucFilePath, pulDataLen, ppucData, enAppType);
    }

    return USIMM_GetCachedFile_Instance(enModemID, pucFilePath, pulDataLen, ppucData, enAppType);
}

/*****************************************************************************
函 数 名  :SC_COMM_IsUsimServiceAvailable
功能描述  :获取卡服务状态　
输入参数  :enModemID:Modem ID
           enService:服务ID
输出参数  :无
返 回 值  :PS_USIM_SERVICE_NOT_AVAILIABLE
           PS_USIM_SERVICE_NOT_AVAILIABLE
被调函数  :
修订记录  :
1.日    期   : 2013年8月15日
  作    者   : h59254
  修改内容   : 初始生成
*****************************************************************************/
VOS_UINT32 SC_COMM_IsUsimServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32  enService,
    MODEM_ID_ENUM_UINT16            enModemID)
{
    if (VOS_TRUE == USIMM_IsSvlte())
    {
        return USIMM_IsServiceAvailable_Instance(MODEM_ID_0, enService);
    }

    return USIMM_IsServiceAvailable_Instance(enModemID, enService);
}

/*****************************************************************************
函 数 名  : SC_COMM_Backup
功能描述  : SC文件备份到底软SC备份区
输入参数  :

输出参数  : 无
返 回 值  : VOS_UINT32

被调函数  :
修订记录  :
1.日    期   : 2014年6月27日
  作    者   : d00212987
  修改内容   : SC备份到底软NV备份的扩展分区
*****************************************************************************/
VOS_UINT32 SC_COMM_Backup(VOS_VOID)
{
    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
函 数 名  :SC_Printf
功能描述  :Log打印,可变参数
*****************************************************************************/
/*lint -e960 */
VOS_VOID SC_Printf(const VOS_CHAR *pcformat, ...)
/*lint +e960 */
{
    VOS_CHAR                            aucIMEILogFilePath[100];
    VOS_CHAR                            acOutput[SC_LOG_MAX_LEN];
    /*lint -e530 -e830 */
    va_list                             argument;
    /*lint +e530 +e830 */
    VOS_UINT32                          ulRetLen;
    FILE                               *fp;
    VOS_UINT32                          ulFileSize;

    /*lint -e530 -e830 -e586*/
    /* 将格式化字符串和可变参数转换为字符串 */
    va_start(argument, pcformat);
    /*lint -e64 */
    ulRetLen = (VOS_UINT32)vsnprintf(acOutput, SC_LOG_MAX_LEN, pcformat, argument);
    /*lint +e64 */
    va_end(argument);
    /*lint +e530 +e830 +e586*/

    if ((SC_LOG_MAX_LEN < ulRetLen) || (0 == ulRetLen))
    {
        return ;
    }

    if (VOS_OK != OM_GetLogPath(aucIMEILogFilePath, SC_IMEI_LOG_FILE_PATH, SC_IMEI_UNITARY_LOG_FILE_PATH))
    {
        return;
    }

#if ((VOS_WIN32 == VOS_OS_VER)||(VOS_VXWORKS == VOS_OS_VER)||(VOS_RTOSCK == VOS_OS_VER))
    fp = mdrv_file_open(aucIMEILogFilePath, "a");

    if (VOS_NULL_PTR == fp)
    {
        return ;
    }

    if (VOS_OK != mdrv_file_seek(fp, 0, SC_FILE_SEEK_END))
    {
        return;
    }

    ulFileSize = (VOS_UINT32)mdrv_file_tell(fp);

    /* If the log file is too large, we need empty it. */
    if (ulFileSize > SC_LOG_FILE_MAX_SIZE)
    {
        /*lint -e534*/
        mdrv_file_close(fp);
        /*lint +e534*/
        fp = mdrv_file_open(aucIMEILogFilePath, "w");

        if (VOS_NULL_PTR == fp)
        {
            return ;
        }
    }

    /*lint -e534*/
    mdrv_file_write(acOutput, ulRetLen, 1, fp);

    mdrv_file_close(fp);
    /*lint +e534*/

#endif

    return ;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

