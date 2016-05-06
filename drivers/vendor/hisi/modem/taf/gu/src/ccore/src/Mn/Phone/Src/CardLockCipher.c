/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CardLockCipher.c
  版 本 号   : 初稿
  作    者   : luojian id:107747
  生成日期   : 2008年4月8日
  最近修改   :
  功能描述   :Operator card lock password generator
  函数列表   :
              CardLockCipher
              CardLockCipher_Finish
              CardLockCipher_Hmac
              CardLockCipher_Hmac_Finish
              CardLockCipher_Hmac_Starts
              CardLockCipher_Hmac_Update
              CardLockCipher_Process
              CardLockCipher_Self_Test
              CardLockCipher_Starts
              CardLockCipher_Update
  修改历史   :
  1.日    期   : 2008年4月8日
    作    者   : luojian id:107747
    修改内容   : 创建文件

******************************************************************************/
#if 0


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CardLockCipher.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_CARDLOCKCIPHER_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*
 * 32-bit integer manipulation macros (little endian)
 */
#ifndef GET_ULONG_LE
#define GET_ULONG_LE(n,b,i)                             \
    {                                                       \
        (n) = ( (VOS_UINT32) (b)[(i)    ]       )        \
            | ( (VOS_UINT32) (b)[(i) + 1] <<  8 )        \
            | ( (VOS_UINT32) (b)[(i) + 2] << 16 )        \
            | ( (VOS_UINT32) (b)[(i) + 3] << 24 );       \
    }
#endif

#ifndef PUT_ULONG_LE
#define PUT_ULONG_LE(n,b,i)                             \
    {                                                       \
        (b)[(i)    ] = (VOS_UINT8) ( (n)       );       \
        (b)[(i) + 1] = (VOS_UINT8) ( (n) >>  8 );       \
        (b)[(i) + 2] = (VOS_UINT8) ( (n) >> 16 );       \
        (b)[(i) + 3] = (VOS_UINT8) ( (n) >> 24 );       \
    }
#endif

/*****************************************************************************
 函 数 名  : CardLockCipher_starts
 功能描述  : CardLockCipher_starts
 输入参数  : CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年4月8日
    作    者   : luojian id:107747
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CardLockCipher_Starts( CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx )
{
    pstCtx->aulTotal[0] = 0;
    pstCtx->aulTotal[1] = 0;

    pstCtx->aulState[0] = 0x67452301;
    pstCtx->aulState[1] = 0xEFCDAB89;
    pstCtx->aulState[2] = 0x98BADCFE;
    pstCtx->aulState[3] = 0x10325476;
}

/*****************************************************************************
 函 数 名  : CardLockCipher_process
 功能描述  :
 输入参数  : CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx
             VOS_UINT8 aucData[64]
 输出参数  : 无
 返 回 值  : static VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年4月8日
    作    者   : luojian id:107747
    修改内容   : 新生成函数

*****************************************************************************/
/*lint -esym(960,91) 修改人：luojian 107747；检视人：sunshaohua 62952；原因简述：成熟专用算法*/
/*lint -esym(961,92) 修改人：luojian 107747；检视人：sunshaohua 62952；原因简述：成熟专用算法*/
static VOS_VOID CardLockCipher_Process( CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx, VOS_UINT8 aucData[64] )
{
    VOS_UINT32                          ulX[16];
    VOS_UINT32                          ulA;
    VOS_UINT32                          ulB;
    VOS_UINT32                          ulC;
    VOS_UINT32                          ulD;

    GET_ULONG_LE( ulX[ 0], aucData,  0 );
    GET_ULONG_LE( ulX[ 1], aucData,  4 );
    GET_ULONG_LE( ulX[ 2], aucData,  8 );
    GET_ULONG_LE( ulX[ 3], aucData, 12 );
    GET_ULONG_LE( ulX[ 4], aucData, 16 );
    GET_ULONG_LE( ulX[ 5], aucData, 20 );
    GET_ULONG_LE( ulX[ 6], aucData, 24 );
    GET_ULONG_LE( ulX[ 7], aucData, 28 );
    GET_ULONG_LE( ulX[ 8], aucData, 32 );
    GET_ULONG_LE( ulX[ 9], aucData, 36 );
    GET_ULONG_LE( ulX[10], aucData, 40 );
    GET_ULONG_LE( ulX[11], aucData, 44 );
    GET_ULONG_LE( ulX[12], aucData, 48 );
    GET_ULONG_LE( ulX[13], aucData, 52 );
    GET_ULONG_LE( ulX[14], aucData, 56 );
    GET_ULONG_LE( ulX[15], aucData, 60 );

#define S(x,n) (((x) << (n)) | (((x) & 0xFFFFFFFF) >> (32 - (n))))

#define P(a,b,c,d,k,s,t)                                \
{                                                       \
    a += F(b,c,d) + ulX[k] + t;                         \
    a = S(a,s) + b;                                     \
}

    ulA = pstCtx->aulState[0];
    ulB = pstCtx->aulState[1];
    ulC = pstCtx->aulState[2];
    ulD = pstCtx->aulState[3];

#define F(x,y,z) (z ^ (x & (y ^ z)))

    P( ulA, ulB, ulC, ulD,  0,  7, 0xD76AA478 );
    P( ulD, ulA, ulB, ulC,  1, 12, 0xE8C7B756 );
    P( ulC, ulD, ulA, ulB,  2, 17, 0x242070DB );
    P( ulB, ulC, ulD, ulA,  3, 22, 0xC1BDCEEE );
    P( ulA, ulB, ulC, ulD,  4,  7, 0xF57C0FAF );
    P( ulD, ulA, ulB, ulC,  5, 12, 0x4787C62A );
    P( ulC, ulD, ulA, ulB,  6, 17, 0xA8304613 );
    P( ulB, ulC, ulD, ulA,  7, 22, 0xFD469501 );
    P( ulA, ulB, ulC, ulD,  8,  7, 0x698098D8 );
    P( ulD, ulA, ulB, ulC,  9, 12, 0x8B44F7AF );
    P( ulC, ulD, ulA, ulB, 10, 17, 0xFFFF5BB1 );
    P( ulB, ulC, ulD, ulA, 11, 22, 0x895CD7BE );
    P( ulA, ulB, ulC, ulD, 12,  7, 0x6B901122 );
    P( ulD, ulA, ulB, ulC, 13, 12, 0xFD987193 );
    P( ulC, ulD, ulA, ulB, 14, 17, 0xA679438E );
    P( ulB, ulC, ulD, ulA, 15, 22, 0x49B40821 );

#undef F


#define F(x,y,z) (y ^ (z & (x^ y)))

    P( ulA, ulB, ulC, ulD,  1,  5, 0xF61E2562 );
    P( ulD, ulA, ulB, ulC,  6,  9, 0xC040B340 );
    P( ulC, ulD, ulA, ulB, 11, 14, 0x265E5A51 );
    P( ulB, ulC, ulD, ulA,  0, 20, 0xE9B6C7AA );
    P( ulA, ulB, ulC, ulD,  5,  5, 0xD62F105D );
    P( ulD, ulA, ulB, ulC, 10,  9, 0x02441453 );
    P( ulC, ulD, ulA, ulB, 15, 14, 0xD8A1E681 );
    P( ulB, ulC, ulD, ulA,  4, 20, 0xE7D3FBC8 );
    P( ulA, ulB, ulC, ulD,  9,  5, 0x21E1CDE6 );
    P( ulD, ulA, ulB, ulC, 14,  9, 0xC33707D6 );
    P( ulC, ulD, ulA, ulB,  3, 14, 0xF4D50D87 );
    P( ulB, ulC, ulD, ulA,  8, 20, 0x455A14ED );
    P( ulA, ulB, ulC, ulD, 13,  5, 0xA9E3E905 );
    P( ulD, ulA, ulB, ulC,  2,  9, 0xFCEFA3F8 );
    P( ulC, ulD, ulA, ulB,  7, 14, 0x676F02D9 );
    P( ulB, ulC, ulD, ulA, 12, 20, 0x8D2A4C8A );

#undef F

#define F(x,y,z) (x ^ y ^ z)

    P( ulA, ulB, ulC, ulD,  5,  4, 0xFFFA3942 );
    P( ulD, ulA, ulB, ulC,  8, 11, 0x8771F681 );
    P( ulC, ulD, ulA, ulB, 11, 16, 0x6D9D6122 );
    P( ulB, ulC, ulD, ulA, 14, 23, 0xFDE5380C );
    P( ulA, ulB, ulC, ulD,  1,  4, 0xA4BEEA44 );
    P( ulD, ulA, ulB, ulC,  4, 11, 0x4BDECFA9 );
    P( ulC, ulD, ulA, ulB,  7, 16, 0xF6BB4B60 );
    P( ulB, ulC, ulD, ulA, 10, 23, 0xBEBFBC70 );
    P( ulA, ulB, ulC, ulD, 13,  4, 0x289B7EC6 );
    P( ulD, ulA, ulB, ulC,  0, 11, 0xEAA127FA );
    P( ulC, ulD, ulA, ulB,  3, 16, 0xD4EF3085 );
    P( ulB, ulC, ulD, ulA,  6, 23, 0x04881D05 );
    P( ulA, ulB, ulC, ulD,  9,  4, 0xD9D4D039 );
    P( ulD, ulA, ulB, ulC, 12, 11, 0xE6DB99E5 );
    P( ulC, ulD, ulA, ulB, 15, 16, 0x1FA27CF8 );
    P( ulB, ulC, ulD, ulA,  2, 23, 0xC4AC5665 );

#undef F

#define F(x,y,z) (y ^ (x | ~z))

    P( ulA, ulB, ulC, ulD,  0,  6, 0xF4292244 );
    P( ulD, ulA, ulB, ulC,  7, 10, 0x432AFF97 );
    P( ulC, ulD, ulA, ulB, 14, 15, 0xAB9423A7 );
    P( ulB, ulC, ulD, ulA,  5, 21, 0xFC93A039 );
    P( ulA, ulB, ulC, ulD, 12,  6, 0x655B59C3 );
    P( ulD, ulA, ulB, ulC,  3, 10, 0x8F0CCC92 );
    P( ulC, ulD, ulA, ulB, 10, 15, 0xFFEFF47D );
    P( ulB, ulC, ulD, ulA,  1, 21, 0x85845DD1 );
    P( ulA, ulB, ulC, ulD,  8,  6, 0x6FA87E4F );
    P( ulD, ulA, ulB, ulC, 15, 10, 0xFE2CE6E0 );
    P( ulC, ulD, ulA, ulB,  6, 15, 0xA3014314 );
    P( ulB, ulC, ulD, ulA, 13, 21, 0x4E0811A1 );
    P( ulA, ulB, ulC, ulD,  4,  6, 0xF7537E82 );
    P( ulD, ulA, ulB, ulC, 11, 10, 0xBD3AF235 );
    P( ulC, ulD, ulA, ulB,  2, 15, 0x2AD7D2BB );
    P( ulB, ulC, ulD, ulA,  9, 21, 0xEB86D391 );

#undef F
#undef P
#undef S

    pstCtx->aulState[0] += ulA;
    pstCtx->aulState[1] += ulB;
    pstCtx->aulState[2] += ulC;
    pstCtx->aulState[3] += ulD;
}
/*lint -esym(960,91)修改人：luojian 107747；检视人：sunshaohua */
/*lint -esym(961,92)修改人：luojian 107747；检视人：sunshaohua */
/*****************************************************************************
 函 数 名  : CardLockCipher_update
 功能描述  :
 输入参数  : CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx
             VOS_UINT8 *pucInput
             VOS_INT32 ulInputLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年4月8日
    作    者   : luojian id:107747
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CardLockCipher_Update( CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx, VOS_UINT8 *pucInput, VOS_INT32 lInputLen )
{
    VOS_INT32                           lFill;
    VOS_UINT32                          ulLeft;

    if( lInputLen <= 0 )
    {
        return;
    }

    ulLeft = pstCtx->aulTotal[0] & 0x3F;
    lFill = 64 - (VOS_INT32)ulLeft;

    pstCtx->aulTotal[0] += lInputLen;
    pstCtx->aulTotal[0] &= 0xFFFFFFFF;

    if( pstCtx->aulTotal[0] < (VOS_UINT32) lInputLen )
    {
        pstCtx->aulTotal[1]++;
    }
    if( ulLeft && (lInputLen >= lFill) )
    {
        PS_MEM_CPY( (VOS_VOID *) (pstCtx->aucBuffer + ulLeft),
                (VOS_VOID *) pucInput, (VOS_UINT32)lFill );
        CardLockCipher_Process( pstCtx, pstCtx->aucBuffer );
        pucInput += lFill;
        lInputLen  -= lFill;
        ulLeft = 0;
    }

    while( lInputLen >= 64 )
    {
        CardLockCipher_Process( pstCtx, pucInput );
        pucInput += 64;
        lInputLen  -= 64;
    }

    if( lInputLen > 0 )
    {
        PS_MEM_CPY( (VOS_VOID *) (pstCtx->aucBuffer + ulLeft),
                (VOS_VOID *) pucInput, (VOS_UINT32)lInputLen );
    }
}

static const VOS_UINT8 gaucCardLockCipher_Padding[64] =
{
 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*****************************************************************************
 函 数 名  : CardLockCipher_finish
 功能描述  :
 输入参数  : CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx
             VOS_UINT8 aucOutput[16]
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年4月8日
    作    者   : luojian id:107747
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CardLockCipher_Finish( CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx, VOS_UINT8 aucOutput[16] )
{
    VOS_UINT32                          ulLast;
    VOS_UINT32                          ulPadn;
    VOS_UINT32                          ulHigh;
    VOS_UINT32                          ulLow;
    VOS_UINT8                           aucMsglen[8];

    ulHigh = ( pstCtx->aulTotal[0] >> 29 )
         | ( pstCtx->aulTotal[1] <<  3 );
    ulLow  = ( pstCtx->aulTotal[0] <<  3 );

    PUT_ULONG_LE( ulLow,  aucMsglen, 0 );
    PUT_ULONG_LE( ulHigh, aucMsglen, 4 );

    ulLast = pstCtx->aulTotal[0] & 0x3F;
    ulPadn = ( ulLast < 56 ) ? ( 56 - ulLast ) : ( 120 - ulLast );

    CardLockCipher_Update( pstCtx, (VOS_UINT8 *) gaucCardLockCipher_Padding, (VOS_INT32)ulPadn );
    CardLockCipher_Update( pstCtx, aucMsglen, 8 );

    PUT_ULONG_LE( pstCtx->aulState[0], aucOutput,  0 );
    PUT_ULONG_LE( pstCtx->aulState[1], aucOutput,  4 );
    PUT_ULONG_LE( pstCtx->aulState[2], aucOutput,  8 );
    PUT_ULONG_LE( pstCtx->aulState[3], aucOutput, 12 );
}

/*****************************************************************************
 函 数 名  : CardLockCipher
 功能描述  :
 输入参数  : VOS_UINT8 *pucInput
             VOS_INT32 ulInputLen
             VOS_UINT8 aucOutput[16]
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年4月8日
    作    者   : luojian id:107747
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CardLockCipher( VOS_UINT8 *pucInput, VOS_INT32 ulInputLen, VOS_UINT8 aucOutput[16] )
{
    CARDLOCK_CIPHER_CONTEXT_STRU        stCtx;

    CardLockCipher_Starts( &stCtx );
    CardLockCipher_Update( &stCtx, pucInput, ulInputLen );
    CardLockCipher_Finish( &stCtx, aucOutput );
}

/*****************************************************************************
 函 数 名  : CardLockCipher_hmac_starts
 功能描述  :
 输入参数  : CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx
             VOS_UINT8 *key
             VOS_INT32 keylen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年4月8日
    作    者   : luojian id:107747
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CardLockCipher_Hmac_Starts( CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx, VOS_UINT8 *pucKey, VOS_INT32 lKeylen )
{
    VOS_INT32                           i;
    VOS_UINT8                           aucSum[16];

    if( lKeylen > 64 )
    {
        CardLockCipher( pucKey, lKeylen, aucSum );
        lKeylen = 16;
        pucKey = aucSum;
    }

    PS_MEM_SET( pstCtx->aucIpad, 0x36, CARDLOCK_CIPHER_CONTEXT_INNER_NUM );
    PS_MEM_SET( pstCtx->aucOpad, 0x5C, CARDLOCK_CIPHER_CONTEXT_OUTER_NUM );

    for( i = 0; i < lKeylen; i++ )
    {
        pstCtx->aucIpad[i] = (VOS_UINT8)( pstCtx->aucIpad[i] ^ pucKey[i] );
        pstCtx->aucOpad[i] = (VOS_UINT8)( pstCtx->aucOpad[i] ^ pucKey[i] );
    }

    CardLockCipher_Starts( pstCtx );
    CardLockCipher_Update( pstCtx, pstCtx->aucIpad, 64 );

}

/*****************************************************************************
 函 数 名  : CardLockCipher_hmac_update
 功能描述  :
 输入参数  : CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx
             VOS_UINT8 *pucInput
             VOS_INT32 ulInputLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年4月8日
    作    者   : luojian id:107747
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CardLockCipher_Hmac_Update( CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx, VOS_UINT8 *pucInput, VOS_INT32 lInputLen )
{
    CardLockCipher_Update( pstCtx, pucInput, lInputLen );
}

/*****************************************************************************
 函 数 名  : CardLockCipher_hmac_finish
 功能描述  :
 输入参数  : CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx
             VOS_UINT8 aucOutput[16]
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1. 日    期   : 2008年4月8日
     作    者   : luojian id:107747
     修改内容   : 新生成函数
  2. 日    期   : 2013年07月222日
     作    者   : j00177245
     修改内容   : 清理Coverity

*****************************************************************************/
VOS_VOID CardLockCipher_Hmac_Finish( CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx, VOS_UINT8 aucOutput[16] )
{
    VOS_UINT8                           aucTmpbuf[64];

    CardLockCipher_Finish( pstCtx, aucTmpbuf );
    CardLockCipher_Starts( pstCtx );
    CardLockCipher_Update( pstCtx, pstCtx->aucOpad, 64 );
    CardLockCipher_Update( pstCtx, aucTmpbuf, 16 );
    CardLockCipher_Finish( pstCtx, aucOutput );
}

/*****************************************************************************
 函 数 名  : CardLockCipher_hmac
 功能描述  :
 输入参数  : VOS_UINT8 *key
             VOS_INT32 keylen
             VOS_UINT8 *pucInput
             VOS_INT32 ulInputLen
             VOS_UINT8 aucOutput[16]
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年4月8日
    作    者   : luojian id:107747
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CardLockCipher_Hmac(
VOS_UINT8 *pucKey,
VOS_INT32 lKeylen,
VOS_UINT8 *pucInput,
VOS_UINT32 ulInputLen,
VOS_UINT8 aucOutput[16] )

{
    CARDLOCK_CIPHER_CONTEXT_STRU        stCtx;
    CardLockCipher_Hmac_Starts( &stCtx, pucKey, lKeylen );
    CardLockCipher_Hmac_Update( &stCtx, pucInput, (VOS_INT32)ulInputLen );
    CardLockCipher_Hmac_Finish( &stCtx, aucOutput );
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



#endif
