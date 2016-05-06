/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pppc_sha256.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年11月10日
  最近修改   :
  功能描述   : pppc_sha256.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月10日
    作    者   : 123
    修改内容   : 创建文件

******************************************************************************/


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "pppc_sha256.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_PPPC_UTIL_SHA256_C
/*lint +e767*/

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : PPPC_SHA256_RND
 功能描述  : SHA256算法函数
 输入参数  : pulS
             ulIndex
             ulW
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_SHA256_RND
(
    VOS_UINT32                         *pulS,
    VOS_UINT32                          ulIndex,
    VOS_UINT32                          ulW
)
{
    VOS_UINT32                          ulTemp;


    ulTemp  = pulS[7] + PPPC_SHA256_Sigma1(pulS[4]) + PPPC_SHA256_Ch(pulS[4], pulS[5], pulS[6]) +
                PPPC_GET_RND_K(ulIndex) + ulW;
    pulS[3] += ulTemp;
    pulS[7] =  ulTemp;
    ulTemp  = PPPC_SHA256_Sigma0(pulS[0]) + PPPC_SHA256_Maj(pulS[0], pulS[1], pulS[2]);
    pulS[7] += ulTemp;
}

/*****************************************************************************
 函 数 名  : PPPC_SHA256_GET_BE32
 功能描述  : SHA256 32位大小端转换
 输入参数  : pucArr     要转换的数据指针
 输出参数  :
 返 回 值  : VOS_UINT32 转换后的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
static VOS_UINT32 PPPC_SHA256_GET_BE32(const VOS_UINT8 *pucArr)
{
    return ((VOS_UINT32)(pucArr[0]) << 24) | ((VOS_UINT32)(pucArr[1]) << 16) | ((VOS_UINT32)(pucArr[2]) << 8) | (VOS_UINT32)pucArr[3];
}

/*****************************************************************************
 函 数 名  : PPPC_SHA256_Compress
 功能描述  : SHA256 算法函数
 输入参数  : pstMd
             pucBuf
 输出参数  :
 返 回 值  : 成功 VOS_OK  失败  VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_SHA256_Compress
(
    PPPC_SHA256_STATE_STRU             *pstMd,
    VOS_UINT8                          *pucBuf
)
{
    VOS_UINT32  aulS[8];
    VOS_UINT32  aulW[64];
    VOS_UINT32  ulTemp;
    VOS_UINT32  ulIndex;
    VOS_UINT8   ucIndex;

    /* copy state into S */
    for (ulIndex = 0; ulIndex < 8; ulIndex++)
    {
        aulS[ulIndex] = pstMd->aulState[ulIndex];
    }

    /* copy the state into 512-bits into W[0..15] */
    for (ulIndex = 0; ulIndex < 16; ulIndex++)
    {
        aulW[ulIndex] = PPPC_SHA256_GET_BE32(pucBuf + (4 * ulIndex));
    }

    /* fill W[16..63] */
    for (ulIndex = 16; ulIndex < 64; ulIndex++)
    {
        aulW[ulIndex] = PPPC_SHA256_Gamma1(aulW[ulIndex - 2]) + aulW[ulIndex - 7] +
                         PPPC_SHA256_Gamma0(aulW[ulIndex - 15]) + aulW[ulIndex - 16];
    }

    /* Compress */
    for (ulIndex = 0; ulIndex < 64; ++ulIndex)
    {
        PPPC_SHA256_RND(aulS, ulIndex, aulW[ulIndex]);
        ulTemp   = aulS[7];
        for (ucIndex = 7; ucIndex >0; ucIndex--)
        {
            aulS[ucIndex] = aulS[ucIndex - 1];
        }
        aulS[0]  = ulTemp;
    }

    /* feedback */
    for (ulIndex = 0; ulIndex < 8; ulIndex++)
    {
        pstMd->aulState[ulIndex] = pstMd->aulState[ulIndex] + aulS[ulIndex];
    }
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : PPPC_SHA256_Init
 功能描述  : SHA256 算法函数
 输入参数  : pstMd
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_SHA256_Init(PPPC_SHA256_STATE_STRU *pstMd)
{
    pstMd->ulCurLen = 0;
    pstMd->ullLength = 0;
    pstMd->aulState[0] = 0x6A09E667UL;
    pstMd->aulState[1] = 0xBB67AE85UL;
    pstMd->aulState[2] = 0x3C6EF372UL;
    pstMd->aulState[3] = 0xA54FF53AUL;
    pstMd->aulState[4] = 0x510E527FUL;
    pstMd->aulState[5] = 0x9B05688CUL;
    pstMd->aulState[6] = 0x1F83D9ABUL;
    pstMd->aulState[7] = 0x5BE0CD19UL;
}

/*****************************************************************************
 函 数 名  : PPPC_SHA256_Process
 功能描述  : SHA256 算法函数 Process a block of memory though the hash
 输入参数  : pstMd      The hash state
             pucIn      The data to hash
             ulInLen    The length of the data (octets)
 输出参数  :
 返 回 值  : 成功 VOS_OK  失败  VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_SHA256_Process
(
    PPPC_SHA256_STATE_STRU             *pstMd,
    VOS_UINT8                          *pucIn,
    VOS_UINT32                          ulInLen
)
{
    VOS_UINT32                          ulNum;

    if (pstMd->ulCurLen >= sizeof(pstMd->aucBuf))
    {
        return VOS_ERR;
    }

    while (ulInLen > 0)
    {
        if (pstMd->ulCurLen == 0 && ulInLen >= PPPC_SHA256_BLOCK_SIZE)
        {
            if (VOS_OK != PPPC_SHA256_Compress(pstMd, (VOS_UINT8 *) pucIn))
            {
                return VOS_ERR;
            }
            pstMd->ullLength += PPPC_SHA256_BLOCK_SIZE * 8;
            pucIn += PPPC_SHA256_BLOCK_SIZE;
            ulInLen -= PPPC_SHA256_BLOCK_SIZE;
        }
        else
        {
            ulNum = PS_MIN(ulInLen, (PPPC_SHA256_BLOCK_SIZE - pstMd->ulCurLen));
            PS_MEM_CPY(pstMd->aucBuf + pstMd->ulCurLen, pucIn, ulNum);
            pstMd->ulCurLen += ulNum;
            pucIn += ulNum;
            ulInLen -= ulNum;
            if (pstMd->ulCurLen == PPPC_SHA256_BLOCK_SIZE)
            {
                if (VOS_OK != PPPC_SHA256_Compress(pstMd, pstMd->aucBuf))
                {
                    return VOS_ERR;
                }
                pstMd->ullLength += 8 * PPPC_SHA256_BLOCK_SIZE;
                pstMd->ulCurLen = 0;
            }
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_SHA256_PUT_BE64
 功能描述  : SHA256  64位大小端转换函数
 输入参数  : ullVal   要转换的数据
 输出参数  : pucA     转换后的数据
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_SHA256_PUT_BE64(VOS_UINT8 *pucA, VOS_UINT64 ullVal)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < 7; ucIndex++)
    {
       pucA[ucIndex] = (VOS_UINT8)(ullVal >> (56 - ucIndex * 8));
    }
    pucA[7] = (VOS_UINT8)(ullVal & 0xff);
}

/*****************************************************************************
 函 数 名  : PPPC_SHA256_PUT_BE32
 功能描述  : SHA256  32位大小端转换函数
 输入参数  : ullVal   要转换的数据
 输出参数  : pucA     转换后的数据
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
static VOS_VOID PPPC_SHA256_PUT_BE32(VOS_UINT8 *pucArr, VOS_UINT32 ulVal)
{
    pucArr[0] = (ulVal >> 24) & 0xff;
    pucArr[1] = (ulVal >> 16) & 0xff;
    pucArr[2] = (ulVal >> 8) & 0xff;
    pucArr[3] = ulVal & 0xff;
}

/*****************************************************************************
 函 数 名  : PPPC_SHA256_Done
 功能描述  : SHA256算法函数 Terminate the hash to get the digest
 输入参数  : pstMd      The hash state
 输出参数  : pucOut     The destination of the hash (32 bytes)
 返 回 值  : 成功  VOS_OK    失败  VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_SHA256_Done
(
    PPPC_SHA256_STATE_STRU             *pstMd,
    VOS_UINT8                          *pucOut
)
{
    VOS_UINT32                          ulIndex;

    if (pstMd->ulCurLen >= sizeof(pstMd->aucBuf))
    {
        return VOS_ERR;
    }

    /* increase the length of the message */
    pstMd->ullLength += (VOS_UINT64)(pstMd->ulCurLen) * 8;

    /* append the '1' bit */
    pstMd->aucBuf[pstMd->ulCurLen++] = (VOS_UINT8) 0x80;

    /* if the length is currently above 56 bytes we append zeros
     * then compress.  Then we can fall back to padding zeros and length
     * encoding like normal.
     */
    if (pstMd->ulCurLen > 56)
    {
        while (pstMd->ulCurLen < PPPC_SHA256_BLOCK_SIZE)
        {
            pstMd->aucBuf[pstMd->ulCurLen++] = (VOS_UINT8) 0;
        }
        PPPC_SHA256_Compress(pstMd, pstMd->aucBuf);
        pstMd->ulCurLen = 0;
    }

    /* pad up to 56 bytes of zeroes */
    while (pstMd->ulCurLen < 56)
    {
        pstMd->aucBuf[pstMd->ulCurLen++] = (VOS_UINT8) 0;
    }

    /* store length */
    PPPC_SHA256_PUT_BE64(pstMd->aucBuf + 56, pstMd->ullLength);
    PPPC_SHA256_Compress(pstMd, pstMd->aucBuf);

    /* copy output */
    for (ulIndex = 0; ulIndex < 8; ulIndex++)
    {
        PPPC_SHA256_PUT_BE32(pucOut + (4 * ulIndex), pstMd->aulState[ulIndex]);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_SHA256
 功能描述  : SHA256算法函数
 输入参数  : stPara      需要加密的数据
 输出参数  : pucMac      加密的结果
 返 回 值  : 成功  VOS_OK    失败  VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_SHA256
(
    PPPC_SHA256_PARA_STRU              *pstPara,
    VOS_UINT8                          *pucMac
)
{
    PPPC_SHA256_STATE_STRU              stCtx;
    VOS_UINT8                           ucIndex;

    PPPC_SHA256_Init(&stCtx);

    for (ucIndex = 0; ucIndex < pstPara->ucNum; ucIndex++)
    {
        if (VOS_OK != PPPC_SHA256_Process(&stCtx, pstPara->apucAdrr[ucIndex], pstPara->aulLen[ucIndex]))
        {
            PPPC_WARNING_LOG("Error When SHA256 Process!");
            return VOS_ERR;
        }
    }
    if (PPPC_SHA256_Done(&stCtx, pucMac))
    {
        PPPC_WARNING_LOG("Error When SHA256 Done!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_HMAC_SHA256
 功能描述  : HMAC_SHA256算法函数
 输入参数  : pucKey      加密使用的密钥Key
             ucKeyLen    密钥Key长度
             stPara      需要加密的数据
 输出参数  : pucMac      加密的结果
 返 回 值  : 成功  VOS_OK    失败  VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_HMAC_SHA256
(
    VOS_UINT8                          *pucKey,
    VOS_UINT8                           ucKeyLen,
    PPPC_SHA256_PARA_STRU              *pstPara,
    VOS_UINT8                          *pucMac
)
{
    VOS_UINT8                           aucTempKey[PPPC_SHA256_MAC_LEN];
    VOS_UINT8                           aucKeyXorPad[PPPC_SHA256_BLOCK_SIZE];
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucTempMac[PPPC_SHA256_MAC_LEN];
    PPPC_SHA256_PARA_STRU               stTempPara;

    /*
       the HMAC_SHA256 transform looks like:

       SHA256(K XOR opad, SHA256(K XOR ipad, text))

       where K is an n byte key
       ipad is the byte 0x36 repeated 64 times
       opad is the byte 0x5c repeated 64 times
       and text is the data being protected
    */

    /* if key is longer than 64 bytes reset it to key = SHA256(key) */
    PS_MEM_SET(aucTempKey, 0x00, sizeof(aucTempKey));

    stTempPara.ucNum = 1;
    stTempPara.apucAdrr[0] = pucKey;
    stTempPara.aulLen[0]  = ucKeyLen;
    if (ucKeyLen > PPPC_SHA256_BLOCK_SIZE)
    {
        if (VOS_OK != PPPC_SHA256(&stTempPara, aucTempKey))
        {
            PPPC_WARNING_LOG("Error When run HMAC_SHA256 in SHA256!");
            return VOS_ERR;
        }
        pucKey   = aucTempKey;
        ucKeyLen = PPPC_SHA256_MAC_LEN;
    }

    /* XOR key with ipad values */
    PS_MEM_SET(aucKeyXorPad, 0x00, sizeof(aucKeyXorPad));

    PS_MEM_CPY(aucKeyXorPad, pucKey, ucKeyLen);

    for (ucIndex = 0; ucIndex < PPPC_SHA256_BLOCK_SIZE; ucIndex++)
    {
        aucKeyXorPad[ucIndex] ^= 0x36;
    }

    /* SHA256(K XOR ipad | text) */
    stTempPara.ucNum       = pstPara->ucNum + 1;
    stTempPara.apucAdrr[0]  = aucKeyXorPad;
    stTempPara.aulLen[0]   = PPPC_SHA256_BLOCK_SIZE;
    for (ucIndex = 0; ucIndex < pstPara->ucNum; ucIndex++)
    {
        stTempPara.apucAdrr[ucIndex + 1] = pstPara->apucAdrr[ucIndex];
        stTempPara.aulLen[ucIndex + 1]  = pstPara->aulLen[ucIndex];
    }

    if (VOS_OK != PPPC_SHA256(&stTempPara, aucTempMac))
    {
        PPPC_WARNING_LOG("Error When sha256 in hmac!");
        return VOS_ERR;
    }

    /* XOR key with opad values */
    PS_MEM_SET(aucKeyXorPad, 0x00, sizeof(aucKeyXorPad));

    PS_MEM_CPY(aucKeyXorPad, pucKey, ucKeyLen);

    for (ucIndex = 0; ucIndex < PPPC_SHA256_BLOCK_SIZE; ucIndex++)
    {
        aucKeyXorPad[ucIndex] ^= 0x5c;
    }

    /*  SHA256(K XOR opad | aucTempMac) */

    stTempPara.ucNum        = 2;
    stTempPara.apucAdrr[0]  = aucKeyXorPad;
    stTempPara.aulLen[0]    = PPPC_SHA256_BLOCK_SIZE;
    stTempPara.apucAdrr[1]  = aucTempMac;
    stTempPara.aulLen[1]    = PPPC_SHA256_MAC_LEN;

    if (VOS_OK != PPPC_SHA256(&stTempPara, pucMac))
    {
        PPPC_WARNING_LOG("Error When sha256 in hmac!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_PRF_PRIME
 功能描述  : PRF'算法函数
 输入参数  : pucKey      加密使用的密钥Key
             stPara      需要加密的数据
             ucMKLen     加密结果的长度
 输出参数  : pucMK       加密的结果
 返 回 值  : 成功  VOS_OK    失败  VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_PRF_PRIME
(
    VOS_UINT8                          *pucKey,
    PPPC_SHA256_PARA_STRU              *pstPara,
    VOS_UINT8                          *pucMK,
    VOS_UINT8                           ucMKLen
)
{
    VOS_UINT8                           aucHash[PPPC_SHA256_MAC_LEN];
    VOS_UINT8                           ucIter;
    PPPC_SHA256_PARA_STRU               stTempPara;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucHashLen;

    /*
     * PRF'(K,S) = T1 | T2 | T3 | T4 | ...
     * T1 = HMAC-SHA-256 (K, S | 0x01)
     * T2 = HMAC-SHA-256 (K, T1 | S | 0x02)
     * T3 = HMAC-SHA-256 (K, T2 | S | 0x03)
     * T4 = HMAC-SHA-256 (K, T3 | S | 0x04)
     * ...
    */

    PS_MEM_SET(aucHash, 0x00, sizeof(aucHash));
    ucIter = 0;

    stTempPara.ucNum        = pstPara->ucNum + 2;
    stTempPara.apucAdrr[0]  = aucHash;
    stTempPara.aulLen[0]   = 0;
    for (ucIndex = 0; ucIndex < pstPara->ucNum; ucIndex++)
    {
        stTempPara.apucAdrr[ucIndex + 1]  = pstPara->apucAdrr[ucIndex];
        stTempPara.aulLen[ucIndex + 1]   = pstPara->aulLen[ucIndex];
    }
    stTempPara.apucAdrr[pstPara->ucNum + 1] = &ucIter;
    stTempPara.aulLen[pstPara->ucNum + 1]  = 1;

    ucIndex = ucMKLen;
    while (ucIndex > 0)
    {
        ucIter++;
        if (VOS_OK != PPPC_HMAC_SHA256(pucKey, 32, &stTempPara, aucHash))
        {
            PPPC_WARNING_LOG("Error When hmac in prf'!");
            return VOS_ERR;
        }
        stTempPara.aulLen[0] = (VOS_UINT8)PPPC_SHA256_MAC_LEN;
        ucHashLen = ucIndex > PPPC_SHA256_MAC_LEN ? PPPC_SHA256_MAC_LEN : ucIndex;
        PS_MEM_CPY(pucMK, aucHash, ucHashLen);
        pucMK += ucHashLen;
        ucIndex -= ucHashLen;
    }

    return VOS_OK;
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



