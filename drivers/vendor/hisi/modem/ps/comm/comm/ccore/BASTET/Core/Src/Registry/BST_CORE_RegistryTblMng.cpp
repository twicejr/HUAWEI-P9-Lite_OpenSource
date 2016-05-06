/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_CORE_RegistryTblMng.cpp
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年4月16日
  最近修改   :
  功能描述   : 注册表输入数据检查表的处理函数定义文件
  函数列表   :

  修改历史   :
  1.日    期   : 2014年04月16日
    作    者   : d00173029
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_CORE_RegistryTblMng.h"
#include "BST_OS_Memory.h"
#include "BST_DRV_Net.h"
#include "BST_IP_Define.h"
#include "BST_APP_HeartBeat.h"
#include "BST_DBG_MemLeak.h"
#include "BST_APP_EmailPublic.h"
#ifdef   BST_SSL_SUPPORT
#include "BST_OS_Openssl_Rename.h"
#include  <openssl/evp.h>
#endif
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_CORE_REGISTRYTBLMNG_CPP
/*lint +e767*/
/*****************************************************************************
   2 函数声明
*****************************************************************************/

/******************************************************************************
   3 全局变量定义
******************************************************************************/
BST_CORE_PID_LUT_STRU       g_BstCorePidInputChkLut[]   = { BST_CORE_REGTABL_INIT };
#ifdef   BST_SSL_SUPPORT
static BST_UINT8            gs_BastetDsppKey[]          = "PkmJygVfrDxsDeeD";
BST_CORE_PID_ENUM_UINT16    g_enEncrypterParamTable[]   =
{
    BST_PID_EMAIL_ACCOUNT,
    BST_PID_EMAIL_PASSWORD,
    BST_PID_CIPHER_CODE,
};
#endif

/******************************************************************************
   4 函数实现
******************************************************************************/

/***************************************************************
 函 数 名  : BST_CORE_GetPidHandle
 功能描述  : 得到PID对应的检查表处理项句柄
 输入参数  : enPid
 输出参数  : BST_CORE_PID_LUT_STRU
 返 回 值  : BST_VOID
 修改历史  :
    1.日    期   : 2014/01/01
      作    者   : Davy
      修改内容   : 创建函数
***************************************************************/
BST_CORE_PID_LUT_STRU *BST_CORE_GetPidHandle ( BST_CORE_PID_ENUM_UINT16 enPid )
{
    if ( BST_CORE_IsPidValid ( enPid ) )
    {
        if ( g_BstCorePidInputChkLut[enPid].enPid != enPid )
        {
            return BST_NULL_PTR;
        }
        else
        {
            return &g_BstCorePidInputChkLut[enPid];
        }
    }
    else
    {
        return BST_NULL_PTR;
    }
}

#ifdef   BST_SSL_SUPPORT
/***************************************************************
 函 数 名  : EncryptInternal
 功能描述  : 对一个整数做加密
 输入参数  : pucIn
           : ulInLen
           : pucKey
 输出参数  : pucOut
           : pulOutLen
 返 回 值  : BST_ERR_ENUM_UINT8
 修改历史  :
    1.日    期   : 2014/01/01
      作    者   : LiQiLin
      修改内容   : 创建函数
***************************************************************/
BST_STATIC BST_ERR_ENUM_UINT8  EncryptInternal ( BST_UINT8     *pucIn,
                                             BST_UINT32     ulInLen,
                                             BST_UINT8     *pucOut,
                                             BST_UINT32    *pulOutLen,
                                             BST_UINT8     *pucKey )
{
    BST_INT32                           lLen;
    BST_UINT32                          ulLenTest;
    BST_INT32                           lRet;
    BST_UINT8                           aucValue[8];
    EVP_CIPHER_CTX                      Ctx;
    lLen                                = 0;
    ulLenTest                           = 0;
    lRet                                = 0;

    if ( ( BST_NULL_PTR == pucIn ) || ( BST_NULL_PTR == pucOut )
      || ( BST_NULL_PTR == pucKey) || ( BST_NULL_PTR == pulOutLen ) )
    {
        return BST_ERR_PARAM_ENCRYPTER;
    }

    EVP_CIPHER_CTX_init ( &Ctx );

    lRet = EVP_EncryptInit_ex ( &Ctx, EVP_aes_128_ecb (), NULL, pucKey, aucValue );

    if ( lRet != BST_CORE_OPENSSL_SUCCESS )
    {
        return BST_ERR_PARAM_ENCRYPTER;
    }

    *pulOutLen = 0;
    lRet = EVP_EncryptUpdate ( &Ctx, pucOut + *pulOutLen, &lLen, pucIn + *pulOutLen, ulInLen );

    if ( lRet != BST_CORE_OPENSSL_SUCCESS )
    {
        return BST_ERR_PARAM_ENCRYPTER;
    }

    *pulOutLen += lLen;

    ulLenTest = ulInLen >> 4;

    if ( ulInLen != ulLenTest << 4 )
    {
        lRet = EVP_EncryptFinal_ex ( &Ctx, pucOut + *pulOutLen, &lLen );

        if ( lRet != BST_CORE_OPENSSL_SUCCESS )
        {
            return BST_ERR_PARAM_ENCRYPTER;
        }

        *pulOutLen += lLen;
    }

    lRet = EVP_CIPHER_CTX_cleanup ( &Ctx );

    if ( lRet != BST_CORE_OPENSSL_SUCCESS )
    {
        return BST_ERR_PARAM_ENCRYPTER;
    }

    return BST_NO_ERROR_MSG;
}

/***************************************************************
 函 数 名  : DecryptInternal
 功能描述  : 对一个整数做解密
 输入参数  : pucIn
           : ulInLen
           : pucKey
 输出参数  : pucOut
           : pulOutLen
 返 回 值  : BST_ERR_ENUM_UINT8
 修改历史  :
    1.日    期   : 2014/01/01
      作    者   : LiQiLin
      修改内容   : 创建函数
***************************************************************/
BST_STATIC BST_ERR_ENUM_UINT8  DecryptInternal ( BST_UINT8     *pucIn,
                                             BST_UINT32     ulInLen,
                                             BST_UINT8     *pucOut,
                                             BST_UINT32    *pulOutLen,
                                             BST_UINT8     *pucKey )
{
    BST_INT32                   lLen;
    BST_INT32                   lRet;
    BST_INT32                   lTmpLen;
    BST_UINT8                   aucValue[8];
    EVP_CIPHER_CTX              Ctx;

    lLen                        = 0;
    lRet                        = 0;
    lTmpLen                     = 0;
    if ( ( BST_NULL_PTR == pucIn ) || ( BST_NULL_PTR == pucOut )
      || ( BST_NULL_PTR == pucKey) || ( BST_NULL_PTR == pulOutLen ) )
    {
        return BST_ERR_PARAM_DECRYPTER;
    }

    EVP_CIPHER_CTX_init ( &Ctx );

    lRet                    = EVP_DecryptInit_ex ( &Ctx,
                                                    EVP_aes_128_ecb(),
                                                    BST_NULL_PTR,
                                                    pucKey,
                                                    aucValue );

    if ( lRet != BST_CORE_OPENSSL_SUCCESS )
    {
        return BST_ERR_PARAM_DECRYPTER;
    }

    lRet                    = EVP_DecryptUpdate ( &Ctx,
                                                   pucOut + lLen,
                                                  &lTmpLen,
                                                   pucIn + lLen,
                                                   ulInLen );

    if ( lRet != BST_CORE_OPENSSL_SUCCESS )
    {
        return BST_ERR_PARAM_DECRYPTER;
    }

    lLen                   += lTmpLen;
    lRet                    = EVP_DecryptFinal_ex ( &Ctx,
                                                     pucOut + lLen,
                                                    &lTmpLen );
    if ( lRet != BST_CORE_OPENSSL_SUCCESS )
    {
        return BST_ERR_PARAM_DECRYPTER;
    }

    lLen                   += lTmpLen;
    pucOut[lLen]            = 0;
   *pulOutLen               = lLen;
    lRet                    = EVP_CIPHER_CTX_cleanup ( &Ctx );
    if ( lRet != BST_CORE_OPENSSL_SUCCESS )
    {
        return BST_ERR_PARAM_DECRYPTER;
    }

    return BST_NO_ERROR_MSG;
}

/***************************************************************
 函 数 名  : CheckIfEcryOrDecry
 功能描述  : 检查数据是要加密还是解密
 输入参数  : enPid
 输出参数  : BST_VOID
 返 回 值  : BST_BOOL
 修改历史  :
    1.日    期   : 2014/01/01
      作    者   : Davy
      修改内容   : 创建函数
***************************************************************/
inline BST_BOOL CheckIfEcryOrDecry ( BST_CORE_PID_ENUM_UINT16 enPid )
{
    BST_UINT32              i;
    for ( i = 0; i < BST_OS_SIZEOF ( g_enEncrypterParamTable ); i++ )
    {
        if ( enPid ==  g_enEncrypterParamTable[i] )
        {
            return BST_TRUE;
        }
    }

    return BST_FALSE;
}

/***************************************************************
 函 数 名  : BST_CORE_EncryptChk
 功能描述  : 加密检查
 输入参数  : enPid
           : pvData
           : usLen
 输出参数  : ppOutData
           : pusOutLen
 返 回 值  : BST_ERR_ENUM_UINT8
 修改历史  :
    1.日    期   : 2014/01/01
      作    者   : LiQiLin
      修改内容   : 创建函数
***************************************************************/
BST_ERR_ENUM_UINT8  BST_CORE_EncryptChk ( BST_CORE_PID_ENUM_UINT16  enPid,
                                          const BST_VOID           *pvData,
                                          BST_UINT16                usLen,
                                          BST_VOID                **ppOutData,
                                          BST_UINT16               *pusOutLen )
{
    BST_ERR_ENUM_UINT8                  enRet;
    BST_UINT32                          ulInLen;
    BST_UINT32                          ulOutLen;
    BST_UINT32                          ulBase64DataLen;
    BST_UINT8                          *pucIn;
    BST_UINT8                          *pucOut;
    BST_UINT8                          *pucBase64Data;
    ulInLen                             = 0;
    ulOutLen                            = 0;
    ulBase64DataLen                     = 0;
    pucIn                               = BST_NULL_PTR;
    pucOut                              = BST_NULL_PTR;
    pucBase64Data                       = BST_NULL_PTR;
    enRet                               = BST_NO_ERROR_MSG;

    if ( ( BST_NULL_PTR == pvData )
      || ( BST_NULL_PTR == pusOutLen )
      || ( BST_NULL_PTR == ppOutData) )
    {
        return BST_ERR_INVALID_PTR;
    }

    if ( 0 == usLen )
    {
        return BST_ERR_PAR_LEN;
    }

    if ( CheckIfEcryOrDecry ( enPid ) )
    {

        pucIn                           = ( BST_UINT8 * )BST_OS_MALLOC ( usLen );

        if ( BST_NULL_PTR == pucIn )
        {
            return BST_ERR_NO_MEMORY;
        }

        BST_OS_MEMCPY ( pucIn, pvData, usLen );
        ulInLen                          = usLen;

        pucOut                           = ( BST_UINT8 * )BST_OS_MALLOC ( ulInLen + EVP_MAX_IV_LENGTH );

        if ( BST_NULL_PTR == pucOut )
        {
            BST_OS_FREE ( pucIn );
            pucIn = BST_NULL_PTR;
            return BST_ERR_NO_MEMORY;
        }

        enRet                           = EncryptInternal ( ( BST_UINT8 * )pucIn,
                                                            ulInLen,
                                                            pucOut,
                                                            &ulOutLen,
                                                            gs_BastetDsppKey );

        if ( BST_NO_ERROR_MSG == enRet )
        {
            pucBase64Data = ( BST_UINT8 * )BST_OS_MALLOC ( ulOutLen * 2 );

            if ( BST_NULL_PTR == pucBase64Data )
            {
                BST_OS_FREE ( pucIn );
                pucIn = BST_NULL_PTR;
                BST_OS_FREE ( pucOut );
                pucOut = BST_NULL_PTR;
                return BST_ERR_NO_MEMORY;
            }

            ulBase64DataLen = EVP_EncodeBlock ( pucBase64Data, pucOut, ulOutLen );
            *ppOutData = pucBase64Data;
            *pusOutLen = ulBase64DataLen;
        }

        BST_OS_FREE ( pucIn );
        pucIn = BST_NULL_PTR;
        BST_OS_FREE ( pucOut );
        pucOut = BST_NULL_PTR;

        return enRet;
    }

    return BST_NO_ERROR_MSG;
}

/***************************************************************
 函 数 名  : BST_CORE_DencryptChk
 功能描述  : 解密检查
 输入参数  : enPid
           : pvData
           : usLen
 输出参数  : ppOutData
           : pusOutLen
 返 回 值  : BST_ERR_ENUM_UINT8
 修改历史  :
    1.日    期   : 2014/01/01
      作    者   : LiQiLin
      修改内容   : 创建函数
***************************************************************/
BST_ERR_ENUM_UINT8  BST_CORE_DencryptChk ( BST_CORE_PID_ENUM_UINT16     enPid,
                                           const BST_VOID              *pvData,
                                           BST_UINT16                   usLen,
                                           BST_VOID                   **ppOutData,
                                           BST_UINT16                  *pusOutLen )
{
    BST_ERR_ENUM_UINT8                  enRet;
    BST_UINT32                          ulInLen;
    BST_UINT32                          ulOutLen;
    BST_UINT32                          ulBase64DataLen;
    BST_UINT8                          *pucIn;
    BST_UINT8                          *pucOut;
    BST_UINT8                          *pucBase64Data;
    ulInLen                             = 0;
    ulOutLen                            = 0;
    ulBase64DataLen                     = 0;
    pucIn                               = BST_NULL_PTR;
    pucOut                              = BST_NULL_PTR;
    pucBase64Data                       = BST_NULL_PTR;
    enRet                               = BST_NO_ERROR_MSG;

    if ( ( BST_NULL_PTR == pvData )
      || ( BST_NULL_PTR == pusOutLen )
      || ( BST_NULL_PTR == ppOutData) )
    {
        return BST_ERR_INVALID_PTR;
    }

    if ( 0 == usLen )
    {
        return BST_ERR_PAR_LEN;
    }

    if ( CheckIfEcryOrDecry ( enPid ) )
    {
        pucIn = ( BST_UINT8 * )BST_OS_MALLOC ( usLen );

        if ( BST_NULL_PTR == pucIn )
        {
            return BST_ERR_NO_MEMORY;
        }

        BST_OS_MEMCPY ( pucIn, pvData, usLen );
        ulInLen = usLen;

        pucBase64Data = ( BST_UINT8 * )BST_OS_MALLOC ( ulInLen );

        if ( BST_NULL_PTR == pucBase64Data )
        {
            BST_OS_FREE ( pucIn );
            pucIn = BST_NULL_PTR;
            return BST_ERR_NO_MEMORY;
        }

        ulBase64DataLen = EVP_DecodeBlock ( pucBase64Data, pucIn, ulInLen );

        while ( pucIn[--ulInLen] == '=' ) // Ecrypter string end is '='
        {
            ulBase64DataLen--;
        }

        pucOut = ( BST_UINT8 * )BST_OS_MALLOC ( ulInLen );

        if ( BST_NULL_PTR == pucOut )
        {
            BST_OS_FREE ( pucIn );
            pucIn = BST_NULL_PTR;
            BST_OS_FREE ( pucBase64Data );
            pucBase64Data = BST_NULL_PTR;
            return BST_ERR_NO_MEMORY;
        }

        BST_OS_MEMSET ( pucOut, 0, ulInLen );

        enRet = DecryptInternal ( pucBase64Data,
                                  ulBase64DataLen,
                                  pucOut,
                                 &ulOutLen,
                                  gs_BastetDsppKey );

        if ( BST_NO_ERROR_MSG == enRet )
        {
            *ppOutData = ( BST_VOID * )pucOut;
            *pusOutLen = ( BST_UINT16 )ulOutLen;
        }

        BST_OS_FREE ( pucIn );
        pucIn = BST_NULL_PTR;
        BST_OS_FREE ( pucBase64Data );
        pucBase64Data = BST_NULL_PTR;

        return enRet;
    }

    return BST_NO_ERROR_MSG;
}
#endif
