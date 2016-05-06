/************************************************************************
*                                                                      *
*                             Eap.c                                    *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2010/07/05                                      *
*  Author:             WANGYONG                                        *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP的EAP协议模块                                *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
* Copyright 2000-2010 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
*                     ALL RIGHTS RESERVED                              *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   这个文件定义了EAP协议模块的全部接口函数和内部处理函数              *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"
#include "pppc_md5.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_MD5_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : PPP_MD5Init
 功能描述  : MD5算法状态初始化.
 输入参数  : context     MD5实体
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-9
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPP_MD5Init(PPPC_MD5_CTX_STRU *pstContext)
{
    pstContext->count[0] = 0;
    pstContext->count[1] = 0;
    /* Load magic initialization constants. */
    pstContext->state[0] = 0x67452301;
    pstContext->state[1] = 0xefcdab89;
    pstContext->state[2] = 0x98badcfe;
    pstContext->state[3] = 0x10325476;

    return;
}

/*****************************************************************************
 函 数 名  : PPP_MD5_memset
 功能描述  : MD5算法内存设置.
 输入参数  : pucOutput     输出
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-9
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPP_MD5_memset
(
    VOS_UINT8                          *pucOutput,
    VOS_INT32                           lValue,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulIndex;


    for (ulIndex = 0; ulIndex < ulLen; ulIndex++)
    {
        ((VOS_INT8 *)pucOutput)[ulIndex] = (VOS_INT8)lValue;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_Decode
 功能描述  : 解码
 输入参数  : pucOutput     输出
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-9
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPP_Decode
(
    VOS_UINT32                         *pucOutput,
    VOS_UINT8                          *pucInput,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulIndexI;
    VOS_UINT32                          ulIndexJ;

    for (ulIndexI = 0, ulIndexJ = 0; ulIndexJ < ulLen; ulIndexI++, ulIndexJ += 4)
    {
        pucOutput[ulIndexI] = ((VOS_UINT32)pucInput[ulIndexJ])
                            | (((VOS_UINT32)pucInput[ulIndexJ+1]) << 8)
                            | (((VOS_UINT32)pucInput[ulIndexJ+2]) << 16)
                            | (((VOS_UINT32)pucInput[ulIndexJ+3]) << 24);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_MD5Transform
 功能描述  : 转换
 输入参数  : state     状态
             block     数据块
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-9
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPP_MD5Transform (VOS_UINT32 state[4], VOS_UINT8 block[64])
{
  VOS_UINT32 a = state[0], b = state[1], c = state[2], d = state[3], x[16];

  PS_MEM_SET ((VOS_VOID *)x, 0x0, sizeof(x));
  PPP_Decode (x, block, 64);

  /* Round 1 */
  FF (a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
  FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
  FF (c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
  FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
  FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
  FF (d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
  FF (c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
  FF (b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
  FF (a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
  FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
  FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
  FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
  FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
  FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
  FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
  FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

 /* Round 2 */
  GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
  GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
  GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
  GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
  GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
  GG (d, a, b, c, x[10], S22,  0x2441453); /* 22 */
  GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
  GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
  GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
  GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
  GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
  GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
  GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
  GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
  GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
  GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

  /* Round 3 */
  HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
  HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
  HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
  HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
  HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
  HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
  HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
  HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
  HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
  HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
  HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
  HH (b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
  HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
  HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
  HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
  HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */

  /* Round 4 */
  II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
  II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
  II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
  II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
  II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
  II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
  II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
  II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
  II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
  II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
  II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
  II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
  II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
  II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
  II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
  II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */

  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;

  /* Zeroize sensitive information.
 */
  PPP_MD5_memset ((UCHAR *)x, 0, sizeof (x));
}

/*****************************************************************************
 函 数 名  : PPP_MD5_memcpy
 功能描述  : MD5算法内存拷贝
 输入参数  : pucOutput      输出
             pucInput       输入
             ulLen          长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-9
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPP_MD5_memcpy
(
    VOS_UINT8                          *pucOutput,
    VOS_UINT8                          *pucInput,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = 0; ulIndex < ulLen; ulIndex++)
    {
        pucOutput[ulIndex] = pucInput[ulIndex];
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_MD5Update
 功能描述  : MD5算法更新
 输入参数  : context     MD5实体
             input       输入
             inputLen    长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-9
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPP_MD5Update
(
    PPPC_MD5_CTX_STRU                  *context,
    VOS_UINT8                          *input,
    VOS_UINT32                          inputLen
)
{
    VOS_UINT32                          ulIndexI;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulPartLen;


    /* Compute number of bytes mod 64 */
    ulIndex = (VOS_UINT32)((context->count[0] >> 3) & 0x3F);

    /* Update number of bits */
    if ((context->count[0] += ((VOS_UINT32)inputLen << 3))
        < ((VOS_UINT32)inputLen << 3))
    {
        context->count[1]++;
    }
    context->count[1] += ((VOS_UINT32)inputLen >> 29);

    ulPartLen = 64 - ulIndex;

    /* Transform as many times as possible.
    */
    if (inputLen >= ulPartLen)
    {
        PPP_MD5_memcpy((UCHAR *)&context->buffer[ulIndex], (UCHAR *)input, ulPartLen);
        PPP_MD5Transform (context->state, context->buffer);
        /*lint -e440*/
        for (ulIndexI = ulPartLen; ulIndexI + 63 < inputLen; ulIndexI += 64)
        {
            PPP_MD5Transform (context->state, &input[ulIndexI]);
        }
        /*lint +e440*/
        ulIndex = 0;
    }
    else
    {
        ulIndexI = 0;
    }

    /* Buffer remaining input */
    PPP_MD5_memcpy((UCHAR *)&context->buffer[ulIndex],
                (UCHAR *)&input[ulIndexI], inputLen-ulIndexI);

    return;
}

VOS_UINT8 PPP_PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*****************************************************************************
 函 数 名  : PPP_Encode
 功能描述  : 封装
 输入参数  : output      输出
             input       输入
             inputLen    长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-9
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPP_Encode
(
    VOS_UINT8                          *pucOutput,
    VOS_UINT32                         *pucInput,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulIndexI;
    VOS_UINT32                          ulIndexJ;


    for (ulIndexI = 0, ulIndexJ = 0; ulIndexJ < ulLen; ulIndexI++, ulIndexJ += 4)
    {
        pucOutput[ulIndexJ]   = (UCHAR)(pucInput[ulIndexI] & 0xff);
        pucOutput[ulIndexJ+1] = (UCHAR)((pucInput[ulIndexI] >> 8) & 0xff);
        pucOutput[ulIndexJ+2] = (UCHAR)((pucInput[ulIndexI] >> 16) & 0xff);
        pucOutput[ulIndexJ+3] = (UCHAR)((pucInput[ulIndexI] >> 24) & 0xff);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_MD5Final
 功能描述  : 计算结果
 输入参数  : digest      输出
             context     上下文
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-9
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
void PPP_MD5Final(VOS_UINT8 aucDigest[16], PPPC_MD5_CTX_STRU *pstContext)
{
    VOS_UINT8                           aucBits[8];
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulPadLen;

    /* Save number of bits */
    PPP_Encode (aucBits, pstContext->count, 8);

    /* Pad out to 56 mod 64.
    */
    ulIndex = (VOS_UINT32)((pstContext->count[0] >> 3) & 0x3f);
    ulPadLen = (ulIndex < 56) ? (56 - ulIndex) : (120 - ulIndex);
    PPP_MD5Update(pstContext, PPP_PADDING, ulPadLen);

    /* Append length (before padding) */
    PPP_MD5Update(pstContext, aucBits, 8);

    /* Store state in digest */
    PPP_Encode (aucDigest, pstContext->state, 16);

    /* Zeroize sensitive information.
    */
    PPP_MD5_memset ((VOS_UINT8 *)pstContext, 0, sizeof (*pstContext));

    return;
}

/*****************************************************************************
 函 数 名  : PPP_MD5Final
 功能描述  : 根据pstMsg中的信息，产生Response  放入pcResponse中
 输入参数  : pstMsg：验证信息块指针，所用各域意义:
             ucPktID     :Challenge Id
             szUsrName   :对端Hostname用于查找对应Secret
             ucUsrNameLen:对端Hostname长度
             szPwd       :Challenge
             ucPwdLen    :Challenge 长度
             szResponse  :本端Hostname(当无Secret表时使用此作为Secret)
             ucResponseLen:本端Hostname 长度
 输出参数  : 根据MD5 算法产生的pstMsg->szResponse
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-9
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_INT16 PPPC_MD5_GenResponse(PPPC_AUTH_MSG_STRU *pstMsg )
{
    PPPC_MD5_CTX_STRU                   mdContext;
    VOS_UINT8                           szResponse[PPP_MAXUSERPWDLEN + 1];

    PPP_MemSet(szResponse, 0, PPP_MAXUSERPWDLEN + 1);

    /* 根据pstMsg->szUsrName查找Secret.如果有替换szResponse?*/

    /*  根据预定算法产生Response */
    PPP_MD5Init(&mdContext);

    /*Challeng Id */
    PPP_MD5Update(&mdContext, &(pstMsg->ucPktID), 1);

    /*secret */
    PPP_MD5Update(&mdContext, (VOS_UINT8*)(pstMsg->szResponse), (VOS_UINT32)(pstMsg->ucResponseLen));

    /*Challenge */
    PPP_MD5Update(&mdContext, (VOS_UINT8*)(pstMsg->szPwd), (VOS_UINT32)(pstMsg->ucPwdLen));
    PPP_MD5Final(szResponse, &mdContext);

    /*返回response */
    (VOID)VOS_MemCpy((VOS_INT8 *)pstMsg->szResponse, szResponse, (VOS_UINT32 )MD5_SIGNATURE_SIZE);
    pstMsg->szResponse[MD5_SIGNATURE_SIZE] = 0;
    pstMsg->ucResponseLen = MD5_SIGNATURE_SIZE;

    return 1;
}

#endif

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
