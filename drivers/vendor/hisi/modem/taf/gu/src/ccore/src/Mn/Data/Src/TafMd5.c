/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TAfMd5.c
  版 本 号   : 初稿
  作    者       : s62952
  生成日期   : 2009年8月3日
  最近修改   :
  功能描述   : Md5算法，

******************************************************************************/
/********************头文件****************************************************/
#include "TafMd5.h"
#include "TafTypeDef.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_TAF_MD5_C
/*lint -e767 */

/*****************************************************************************
  3 全局变量声明
*****************************************************************************/


/**************私有声明****************************************************/
static VOS_VOID TAF_TransformMsgDigestFive (
    VOS_UINT32                         *pulBuf,
    VOS_UINT32                         *pulIn
);

static VOS_UINT8 TAF_MSG_DIGEST_FIVE_PADDING[64] = {
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



/*****************************************************************************
  3 函数实现
*****************************************************************************/
/* F, G, H and I are basic MD5 functions */
/*lint -e961*/
#define TAF_F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define TAF_G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define TAF_H(x, y, z) ((x) ^ (y) ^ (z))
#define TAF_I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits */
#define TAF_ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4 */
/* Rotation is separate from addition to prevent recomputation */
#define TAF_FF(a, b, c, d, x, s, ac) \
  {(a) += TAF_F ((b), (c), (d)) + (x) + (VOS_UINT32)(ac); \
   (a) = TAF_ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
#define TAF_GG(a, b, c, d, x, s, ac) \
  {(a) += TAF_G ((b), (c), (d)) + (x) + (VOS_UINT32)(ac); \
   (a) = TAF_ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
#define TAF_HH(a, b, c, d, x, s, ac) \
  {(a) += TAF_H ((b), (c), (d)) + (x) + (VOS_UINT32)(ac); \
   (a) = TAF_ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
#define TAF_II(a, b, c, d, x, s, ac) \
  {(a) += TAF_I ((b), (c), (d)) + (x) + (VOS_UINT32)(ac); \
   (a) = TAF_ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
/*lint +e961*/

/* Round 1 */
#define TAF_S11                         (7)
#define TAF_S12                         (12)
#define TAF_S13                         (17)
#define TAF_S14                         (22)

/* Round 2 */
#define TAF_S21                         (5)
#define TAF_S22                         (9)
#define TAF_S23                         (14)
#define TAF_S24                         (20)

/* Round 3 */
#define TAF_S31                         (4)
#define TAF_S32                         (11)
#define TAF_S33                         (16)
#define TAF_S34                         (23)

/* Round 4 */
#define TAF_S41                         (6)
#define TAF_S42                         (10)
#define TAF_S43                         (15)
#define TAF_S44                         (21)

#ifdef __STDC__
/*lint -e961*/
#define TAF_UL(x)                       (x##U)
/*lint +e961*/
#else
#define TAF_UL(x)                       (x)
#endif

/*****************************************************************************
 函 数 名  : TAF_InitMsgDigestFiveCtxt
 功能描述  : 初始化上下文
 输入参数  : TAF_MSG_DIGEST_FIVE_CTX *pstMdCtxt
 输出参数  : 无
 返 回 值  : TAF_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月22日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
TAF_VOID TAF_InitMsgDigestFiveCtxt(TAF_MSG_DIGEST_FIVE_CTX *pstMdCtxt)
{
    pstMdCtxt->aulIndex[0] = (VOS_UINT32)0;
    pstMdCtxt->aulIndex[1] = (VOS_UINT32)0;

    pstMdCtxt->aulScrBuf[0] = (VOS_UINT32)0x67452301;
    pstMdCtxt->aulScrBuf[1] = (VOS_UINT32)0xefcdab89;
    pstMdCtxt->aulScrBuf[2] = (VOS_UINT32)0x98badcfe;
    pstMdCtxt->aulScrBuf[3] = (VOS_UINT32)0x10325476;
}

/*****************************************************************************
 函 数 名  : TAF_UpdateMsgDigestFiveCtxt
 功能描述  : 更新上下文
             in the message whose digest is being computed.
 输入参数  : TAF_MSG_DIGEST_FIVE_CTX            *pstMdContext
             VOS_UINT8                          *pucInBuf
             VOS_UINT32                          ulInLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月22日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_UpdateMsgDigestFiveCtxt(
    TAF_MSG_DIGEST_FIVE_CTX            *pstMdCtxt,
    VOS_UINT8                          *pucInBuf,
    VOS_UINT32                          ulInLen
)
{
    VOS_UINT32                          aulIn[16];
    VOS_UINT32                          ulMdi;
    VOS_UINT32                          i;
    VOS_UINT32                          ii;

    ulMdi = (VOS_UINT32)((pstMdCtxt->aulIndex[0] >> 3) & 0x3F);

    if ((pstMdCtxt->aulIndex[0] + ((VOS_UINT32)ulInLen << 3)) < pstMdCtxt->aulIndex[0])
    {
        pstMdCtxt->aulIndex[1]++;
    }
    pstMdCtxt->aulIndex[0] += ((VOS_UINT32)ulInLen << 3);
    pstMdCtxt->aulIndex[1] += ((VOS_UINT32)ulInLen >> 29);

    while (ulInLen--)
    {
        /*lint -e961*/
        pstMdCtxt->aucInBuf[ulMdi++] = *pucInBuf++;
        /*lint +e961*/

        if (0x40 == ulMdi)
        {
            /*lint -e961 */
            for (i = 0, ii = 0; i < 16; i++, ii += 4)
            /*lint -e961 */
            {
                aulIn[i] = (((VOS_UINT32)pstMdCtxt->aucInBuf[ii+3]) << 24)
                         | (((VOS_UINT32)pstMdCtxt->aucInBuf[ii+2]) << 16)
                         | (((VOS_UINT32)pstMdCtxt->aucInBuf[ii+1]) << 8)
                         | ((VOS_UINT32)pstMdCtxt->aucInBuf[ii]);
            }
            TAF_TransformMsgDigestFive(pstMdCtxt->aulScrBuf, aulIn);
            ulMdi = 0;
        }
    }
}

/*****************************************************************************
 函 数 名  : TAF_EndMsgDigestFive
 功能描述  : 终止
 输入参数  : VOS_UINT8                           hash[]
             TAF_MSG_DIGEST_FIVE_CTX            *pstMdCtxt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月22日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_EndMsgDigestFive(
    VOS_UINT8                           hash[],
    TAF_MSG_DIGEST_FIVE_CTX            *pstMdCtxt
)
{
    VOS_UINT32                          aulIn[16];
    VOS_UINT32                          ulmdi;
    VOS_UINT32                          i;
    VOS_UINT32                          ii;
    VOS_UINT32                          ulPadLen;

    aulIn[14] = pstMdCtxt->aulIndex[0];
    aulIn[15] = pstMdCtxt->aulIndex[1];

    /* compute number of bytes mod 64 */
    ulmdi = (VOS_UINT32)((pstMdCtxt->aulIndex[0] >> 3) & 0x3F);

    /* pad out to 56 mod 64 */
    ulPadLen = (VOS_UINT32)((ulmdi < 56) ? (56 - ulmdi) : (120 - ulmdi));
    TAF_UpdateMsgDigestFiveCtxt (pstMdCtxt, TAF_MSG_DIGEST_FIVE_PADDING, ulPadLen);

    /* append length in bits and transform */
    /*lint -e961 */
    for (i = 0, ii = 0; i < 14; i++, ii += 4)
    /*lint -e961 */
    {
        aulIn[i] = (((VOS_UINT32)pstMdCtxt->aucInBuf[ii+3]) << 24) |
                   (((VOS_UINT32)pstMdCtxt->aucInBuf[ii+2]) << 16) |
                   (((VOS_UINT32)pstMdCtxt->aucInBuf[ii+1]) << 8) |
                   ((VOS_UINT32)pstMdCtxt->aucInBuf[ii]);
    }

    TAF_TransformMsgDigestFive(pstMdCtxt->aulScrBuf, aulIn);

    /* store buffer in digest */
    /*lint -e961 */
    for (i = 0, ii = 0; i < 4; i++, ii += 4)
    /*lint -e961 */
    {
        pstMdCtxt->aucDigest[ii] = (VOS_UINT8)(pstMdCtxt->aulScrBuf[i] & 0xFF);
        pstMdCtxt->aucDigest[ii+1] =
            (VOS_UINT8)((pstMdCtxt->aulScrBuf[i] >> 8) & 0xFF);
        pstMdCtxt->aucDigest[ii+2] =
            (VOS_UINT8)((pstMdCtxt->aulScrBuf[i] >> 16) & 0xFF);
        pstMdCtxt->aucDigest[ii+3] =
            (VOS_UINT8)((pstMdCtxt->aulScrBuf[i] >> 24) & 0xFF);
    }

    (VOS_VOID)VOS_MemCpy(hash, pstMdCtxt->aucDigest, 16);
}

/*****************************************************************************
 函 数 名  : TAF_TransformMsgDigestFive
 功能描述  :
 输入参数  : VOS_UINT32                         *pulBuf
             VOS_UINT32                         *pulIn
 输出参数  : 无
 返 回 值  : static VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月22日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年4月18日
    作    者   : A00165503
    修改内容   : DTS2012041705190: 鉴权类型为CHAP的PDP激活失败
*****************************************************************************/
static VOS_VOID TAF_TransformMsgDigestFive (
    VOS_UINT32                         *pulBuf,
    VOS_UINT32                         *pulIn
)
{
    VOS_UINT32                            ulA;
    VOS_UINT32                            ulB;
    VOS_UINT32                            ulC;
    VOS_UINT32                            ulD;

    ulA = pulBuf[0];
    ulB = pulBuf[1];
    ulC = pulBuf[2];
    ulD = pulBuf[3];

    /* RounulD 1 */
    TAF_FF ( ulA, ulB, ulC, ulD, pulIn[ 0], TAF_S11, TAF_UL(3614090360)); /* 1 */
    TAF_FF ( ulD, ulA, ulB, ulC, pulIn[ 1], TAF_S12, TAF_UL(3905402710)); /* 2 */
    TAF_FF ( ulC, ulD, ulA, ulB, pulIn[ 2], TAF_S13, TAF_UL( 606105819)); /* 3 */
    TAF_FF ( ulB, ulC, ulD, ulA, pulIn[ 3], TAF_S14, TAF_UL(3250441966)); /* 4 */
    TAF_FF ( ulA, ulB, ulC, ulD, pulIn[ 4], TAF_S11, TAF_UL(4118548399)); /* 5 */
    TAF_FF ( ulD, ulA, ulB, ulC, pulIn[ 5], TAF_S12, TAF_UL(1200080426)); /* 6 */
    TAF_FF ( ulC, ulD, ulA, ulB, pulIn[ 6], TAF_S13, TAF_UL(2821735955)); /* 7 */
    TAF_FF ( ulB, ulC, ulD, ulA, pulIn[ 7], TAF_S14, TAF_UL(4249261313)); /* 8 */
    TAF_FF ( ulA, ulB, ulC, ulD, pulIn[ 8], TAF_S11, TAF_UL(1770035416)); /* 9 */
    TAF_FF ( ulD, ulA, ulB, ulC, pulIn[ 9], TAF_S12, TAF_UL(2336552879)); /* 10 */
    TAF_FF ( ulC, ulD, ulA, ulB, pulIn[10], TAF_S13, TAF_UL(4294925233)); /* 11 */
    TAF_FF ( ulB, ulC, ulD, ulA, pulIn[11], TAF_S14, TAF_UL(2304563134)); /* 12 */
    TAF_FF ( ulA, ulB, ulC, ulD, pulIn[12], TAF_S11, TAF_UL(1804603682)); /* 13 */
    TAF_FF ( ulD, ulA, ulB, ulC, pulIn[13], TAF_S12, TAF_UL(4254626195)); /* 14 */
    TAF_FF ( ulC, ulD, ulA, ulB, pulIn[14], TAF_S13, TAF_UL(2792965006)); /* 15 */
    TAF_FF ( ulB, ulC, ulD, ulA, pulIn[15], TAF_S14, TAF_UL(1236535329)); /* 16 */

    /* RounulD 2 */
    TAF_GG ( ulA, ulB, ulC, ulD, pulIn[ 1], TAF_S21, TAF_UL(4129170786)); /* 17 */
    TAF_GG ( ulD, ulA, ulB, ulC, pulIn[ 6], TAF_S22, TAF_UL(3225465664)); /* 18 */
    TAF_GG ( ulC, ulD, ulA, ulB, pulIn[11], TAF_S23, TAF_UL( 643717713)); /* 19 */
    TAF_GG ( ulB, ulC, ulD, ulA, pulIn[ 0], TAF_S24, TAF_UL(3921069994)); /* 20 */
    TAF_GG ( ulA, ulB, ulC, ulD, pulIn[ 5], TAF_S21, TAF_UL(3593408605)); /* 21 */
    TAF_GG ( ulD, ulA, ulB, ulC, pulIn[10], TAF_S22, TAF_UL(  38016083)); /* 22 */
    TAF_GG ( ulC, ulD, ulA, ulB, pulIn[15], TAF_S23, TAF_UL(3634488961)); /* 23 */
    TAF_GG ( ulB, ulC, ulD, ulA, pulIn[ 4], TAF_S24, TAF_UL(3889429448)); /* 24 */
    TAF_GG ( ulA, ulB, ulC, ulD, pulIn[ 9], TAF_S21, TAF_UL( 568446438)); /* 25 */
    TAF_GG ( ulD, ulA, ulB, ulC, pulIn[14], TAF_S22, TAF_UL(3275163606)); /* 26 */
    TAF_GG ( ulC, ulD, ulA, ulB, pulIn[ 3], TAF_S23, TAF_UL(4107603335)); /* 27 */
    TAF_GG ( ulB, ulC, ulD, ulA, pulIn[ 8], TAF_S24, TAF_UL(1163531501)); /* 28 */
    TAF_GG ( ulA, ulB, ulC, ulD, pulIn[13], TAF_S21, TAF_UL(2850285829)); /* 29 */
    TAF_GG ( ulD, ulA, ulB, ulC, pulIn[ 2], TAF_S22, TAF_UL(4243563512)); /* 30 */
    TAF_GG ( ulC, ulD, ulA, ulB, pulIn[ 7], TAF_S23, TAF_UL(1735328473)); /* 31 */
    TAF_GG ( ulB, ulC, ulD, ulA, pulIn[12], TAF_S24, TAF_UL(2368359562)); /* 32 */

    /* RounulD 3 */
    TAF_HH ( ulA, ulB, ulC, ulD, pulIn[ 5], TAF_S31, TAF_UL(4294588738)); /* 33 */
    TAF_HH ( ulD, ulA, ulB, ulC, pulIn[ 8], TAF_S32, TAF_UL(2272392833)); /* 34 */
    TAF_HH ( ulC, ulD, ulA, ulB, pulIn[11], TAF_S33, TAF_UL(1839030562)); /* 35 */
    TAF_HH ( ulB, ulC, ulD, ulA, pulIn[14], TAF_S34, TAF_UL(4259657740)); /* 36 */
    TAF_HH ( ulA, ulB, ulC, ulD, pulIn[ 1], TAF_S31, TAF_UL(2763975236)); /* 37 */
    TAF_HH ( ulD, ulA, ulB, ulC, pulIn[ 4], TAF_S32, TAF_UL(1272893353)); /* 38 */
    TAF_HH ( ulC, ulD, ulA, ulB, pulIn[ 7], TAF_S33, TAF_UL(4139469664)); /* 39 */
    TAF_HH ( ulB, ulC, ulD, ulA, pulIn[10], TAF_S34, TAF_UL(3200236656)); /* 40 */
    TAF_HH ( ulA, ulB, ulC, ulD, pulIn[13], TAF_S31, TAF_UL( 681279174)); /* 41 */
    TAF_HH ( ulD, ulA, ulB, ulC, pulIn[ 0], TAF_S32, TAF_UL(3936430074)); /* 42 */
    TAF_HH ( ulC, ulD, ulA, ulB, pulIn[ 3], TAF_S33, TAF_UL(3572445317)); /* 43 */
    TAF_HH ( ulB, ulC, ulD, ulA, pulIn[ 6], TAF_S34, TAF_UL(  76029189)); /* 44 */
    TAF_HH ( ulA, ulB, ulC, ulD, pulIn[ 9], TAF_S31, TAF_UL(3654602809)); /* 45 */
    TAF_HH ( ulD, ulA, ulB, ulC, pulIn[12], TAF_S32, TAF_UL(3873151461)); /* 46 */
    TAF_HH ( ulC, ulD, ulA, ulB, pulIn[15], TAF_S33, TAF_UL( 530742520)); /* 47 */
    TAF_HH ( ulB, ulC, ulD, ulA, pulIn[ 2], TAF_S34, TAF_UL(3299628645)); /* 48 */

    /* RounulD 4 */
    TAF_II ( ulA, ulB, ulC, ulD, pulIn[ 0], TAF_S41, TAF_UL(4096336452)); /* 49 */
    TAF_II ( ulD, ulA, ulB, ulC, pulIn[ 7], TAF_S42, TAF_UL(1126891415)); /* 50 */
    TAF_II ( ulC, ulD, ulA, ulB, pulIn[14], TAF_S43, TAF_UL(2878612391)); /* 51 */
    TAF_II ( ulB, ulC, ulD, ulA, pulIn[ 5], TAF_S44, TAF_UL(4237533241)); /* 52 */
    TAF_II ( ulA, ulB, ulC, ulD, pulIn[12], TAF_S41, TAF_UL(1700485571)); /* 53 */
    TAF_II ( ulD, ulA, ulB, ulC, pulIn[ 3], TAF_S42, TAF_UL(2399980690)); /* 54 */
    TAF_II ( ulC, ulD, ulA, ulB, pulIn[10], TAF_S43, TAF_UL(4293915773)); /* 55 */
    TAF_II ( ulB, ulC, ulD, ulA, pulIn[ 1], TAF_S44, TAF_UL(2240044497)); /* 56 */
    TAF_II ( ulA, ulB, ulC, ulD, pulIn[ 8], TAF_S41, TAF_UL(1873313359)); /* 57 */
    TAF_II ( ulD, ulA, ulB, ulC, pulIn[15], TAF_S42, TAF_UL(4264355552)); /* 58 */
    TAF_II ( ulC, ulD, ulA, ulB, pulIn[ 6], TAF_S43, TAF_UL(2734768916)); /* 59 */
    TAF_II ( ulB, ulC, ulD, ulA, pulIn[13], TAF_S44, TAF_UL(1309151649)); /* 60 */
    TAF_II ( ulA, ulB, ulC, ulD, pulIn[ 4], TAF_S41, TAF_UL(4149444226)); /* 61 */
    TAF_II ( ulD, ulA, ulB, ulC, pulIn[11], TAF_S42, TAF_UL(3174756917)); /* 62 */
    TAF_II ( ulC, ulD, ulA, ulB, pulIn[ 2], TAF_S43, TAF_UL( 718787259)); /* 63 */
    TAF_II ( ulB, ulC, ulD, ulA, pulIn[ 9], TAF_S44, TAF_UL(3951481745)); /* 64 */

    pulBuf[0] = pulBuf[0] + ulA;
    pulBuf[1] = pulBuf[1] + ulB;
    pulBuf[2] = pulBuf[2] + ulC;
    pulBuf[3] = pulBuf[3] + ulD;
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

