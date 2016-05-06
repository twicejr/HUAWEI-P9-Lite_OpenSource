/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsmsDecode.c
  版 本 号   : 初稿
  作    者   : j00304117
  生成日期   : 2014年10月31日
  功能描述   : 1X SMS(Short Message Service)解码
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月31日
    作    者   : j00304117
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXsmsDecode.h"
#include "TafXsmsCtx.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_DECODE_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/*需要重新定义*/

/*不同的TL层 parameter ID 对应不同的函数接口*/
TAF_XSMS_PARM_DECODE_FUNC_STRU   g_astTLParmDecodeFuncList[] =
{
    { TAF_XSMS_TL_TELESERVICE_ID,       TAF_XSMS_TL_DecodeTeleSrvId        },
    { TAF_XSMS_TL_SERVICR_CATEGORY,     TAF_XSMS_TL_DecodeSrvCategory      },
    { TAF_XSMS_TL_ORIGIN_ADDR,          TAF_XSMS_TL_DecodeAddr             },
    { TAF_XSMS_TL_ORIGIN_SUBADDR,       TAF_XSMS_TL_DecodeSubAddr          },
    { TAF_XSMS_TL_DEST_ADDR,            TAF_XSMS_TL_DecodeAddr             },
    { TAF_XSMS_TL_DEST_SUBADDR,         TAF_XSMS_TL_DecodeSubAddr          },
    { TAF_XSMS_TL_BEARER_REPLY_OPTION,  TAF_XSMS_TL_DecodeBearReplyOption  },
    { TAF_XSMS_TL_CAUSE_CODE,           TAF_XSMS_TL_DecodeCauseCode        },
    { TAF_XSMS_TL_BERAER_DATA,          TAF_XSMS_TL_DecodeBearData         },
};
/*****************************************************************************
  3 函数定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_XSMS_TL_UnpackByteToBit
 功能描述  : 从指定的VOS_UINT8类型的数组中的取出指定位置的指定bit数。
 输入参数  : pucBuffer         VOS_UINT8类型的数组指针
             usBitPos          需要取出的BIT在数组中的bit 的位置
             ucBitNum          需要取出的bit数
 输出参数  : *pucValue         读取到的值
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   :j00304117
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_TL_UnpackByteToBit (
    VOS_UINT8                          *pucBuffer,
    VOS_UINT8                          *pucValue,
    VOS_UINT16                          usBitPos,
    VOS_UINT8                           ucBitNum
)
{
    VOS_UINT8                           ucResult;
    VOS_UINT8                           ucBytePos;
    VOS_UINT16                          usPosInByte;
    VOS_INT8                            cShiftSt;
    VOS_UINT8                           ucMask;
    VOS_UINT16                          usTmpResult;

    /* 计算所取的bit在第几个字节，第几个字节的第几个Bit */
    ucBytePos     = (VOS_UINT8)(usBitPos / TAF_XSMS_BIT_NUMBER_OF_BYTE);
    usPosInByte   = (VOS_UINT16)(usBitPos % TAF_XSMS_BIT_NUMBER_OF_BYTE);
    cShiftSt      = (VOS_INT8)(TAF_XSMS_BIT_NUMBER_OF_BYTE - (usPosInByte + ucBitNum));

    /* 所需取得的数据是否是在一个字节里面 */
    if (cShiftSt > 0)
    {
        /* 所取的bit在同一个字节里 */
        ucMask    = 0xff >> (TAF_XSMS_BIT_NUMBER_OF_BYTE - ucBitNum);
        ucResult  = (VOS_INT8)((pucBuffer[ucBytePos] >> cShiftSt) & ucMask);
    }
    else
    {
        /* 所取的bit在两个字节里 */
        usTmpResult = (pucBuffer[ucBytePos] << 8) | (pucBuffer[ucBytePos + 1]);
        ucMask      = (VOS_UINT8)(0xff >> (TAF_XSMS_BIT_NUMBER_OF_BYTE - ucBitNum));
        ucResult    = (VOS_UINT8)(usTmpResult >> (8 + cShiftSt));
        ucResult   &= ucMask;
    }

    *pucValue     = ucResult;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_TL_FillCauseCode
 功能描述  : 把错误代码参数填写到TL层结构体的Cause Code字段
 输入参数  : enErrorClass       发生的错误类型
             enCauseCode        发生错误的原因
             ucReplySeq         回复时需要的Reply SEQ
 输出参数  : pstTLStru          TL层结构体
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
  1.日    期   : 2014年10月31日
    作    者   :j00304117
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_TL_FillCauseCode(
    TAF_XSMS_TL_ERROR_CLASS_ENUM8       enErrorClass,
    TAF_XSMS_TL_CAUSE_CODE_ENUM8        enCauseCode,
    VOS_UINT8                           ucReplySeq,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru

)
{
    /* 判断入参中的ErrorClass看短信是否有错 */
    if (TAF_XSMS_TL_CAUSECODE_NONE == enErrorClass)
    {
        /* 没有出错，参数长度为1 */
        pstTLStru->stCauseCode.ucParameterLen                               = 1;
        pstTLStru->stCauseCode.ucReplySeq                                   = ucReplySeq;
        pstTLStru->stCauseCode.enErrorClass                                 = enErrorClass;
        pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent   = VOS_FALSE;
    }
    else
    {
        /* 出错，参数长度为2 */
        if (TAF_XSMS_TL_CAUSECODE_RESERVED != enErrorClass)
        {
            pstTLStru->stCauseCode.ucParameterLen                             = 2;
            pstTLStru->stCauseCode.ucReplySeq                                 = ucReplySeq;
            pstTLStru->stCauseCode.enErrorClass                               = enErrorClass;
            pstTLStru->stCauseCode.enCauseCode                                = enCauseCode;
            pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent = VOS_TRUE;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_TL_FillCauseCodeSeq
 功能描述  : 由于解码时可能发生Bearer Reply Option字段的ReplySEQ还没解出来就出错
             的情况，之前填写的值可能是错误的，需重新填一次
 输入参数  : pstTLStru         TL层结构体
 输出参数  : pstTLStru         TL层结构体
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : j00304117
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_TL_FillCauseCodeSeq(
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru

)
{

    /* 如果有解码出有Bear Reply Option，则写入Cause Code字段 */
    if (VOS_TRUE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpBearReplyOpPresent)
    {
        pstTLStru->stCauseCode.ucReplySeq = pstTLStru->ucBearReplySeqNum;
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_TL_DecodeTeleSrvId
 功能描述  : 找到tpdu 中的Teleservice ID并写入TL层结构体中
 输入参数  : pucData        TL层码流
             pucBytePos     本参数在码流中的位置
 输出参数  : pstTLStru      TL层结构体
 返 回 值  : VOS_OK -- 解码成功
             VOS_ERR -- 解码失败
 调用函数  :
 被调函数  :
 其    他  :
                    结构
      -----------------------------------------------
     |       Field       |   Length (bits)          |
     |   PARAMETER_ID    |       8                  |
     |   PARAMETER_LEN   |       8                  |
     |   IDENTIFIER      |       16                 |
      ----------------------------------------------

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   :j00304117
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TL_DecodeTeleSrvId(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
)
{
    VOS_UINT16                          usTeleSrvIdHighByte = 0;
    VOS_UINT16                          usTeleSrvIdLowByte  = 0;
    VOS_UINT16                          usTmp               = 0;

    usTmp = *pucBytePos;

    /* 如果此数据已经存在 需要跳过 */
    if (VOS_TRUE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsTelesrvIdPresent)
    {
        *pucBytePos += pucData[usTmp + 1] + 2;

        TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeTeleSrvId:Parameter Teleservice ID is repeated");

        return VOS_OK;
    }

    /* 如果长度不对返回错误 */
    if (2 != pucData[usTmp + 1])
    {
        if (VOS_FALSE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent)
        {
            TAF_XSMS_TL_FillCauseCode(TAF_XSMS_TL_CAUSECODE_TMP,
                                      TAF_XSMS_TL_UNEXPECTED_PARM_SIZE,
                                      pstTLStru->ucBearReplySeqNum,
                                      pstTLStru );
        }

        *pucBytePos += pucData[usTmp + 1] + 2;

        TAF_XSMS_ERROR_LOG("TAF_XSMS_TL_DecodeTeleSrvId:Parameter length of Teleservice ID is invalid");

        return VOS_ERR;
    }

    /* 解码开始参考协议C.S0015 章节3.4.3.1 */

    usTeleSrvIdHighByte = pucData[usTmp + 2];
    usTeleSrvIdHighByte = (VOS_UINT16)(usTeleSrvIdHighByte << 8);
    usTeleSrvIdLowByte  = pucData[usTmp + 3];
    pstTLStru->stMessage.ulTeleserviceID = usTeleSrvIdHighByte + usTeleSrvIdLowByte;

    /* 该参数字段在TL层码流中占4个byte，故字节增量为4 */
    *pucBytePos += 4;

    pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsTelesrvIdPresent = VOS_TRUE;

    TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeTeleSrvId: Decode successed");

    return VOS_OK;

}


/*****************************************************************************
 函 数 名  : TAF_XSMS_TL_DecodeSrvCategory
 功能描述  : 将tpdu 转化成内部应用的传输层数据SrvCategory
 输入参数  : pucData        TL层码流
             pucBytePos     本参数在码流中的位置
 输出参数  : pstTLStru      TL层结构体
 返 回 值  : VOS_OK -- 解码成功
             VOS_ERR -- 解码失败
 调用函数  :
 被调函数  :
 其    他  :
                    结构
      ----------------------------------------------
     |       Field       |   Length (bits)          |
     |   PARAMETER_ID    |       8                  |
     |   PARAMETER_LEN   |       8                  |
     |   IDENTIFIER      |       16                 |
      ----------------------------------------------
 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   :j00304117
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TL_DecodeSrvCategory(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
)
{
    VOS_UINT16                          usSrvCateHighByte = 0;
    VOS_UINT16                          usSrvCateLowByte  = 0;
    VOS_UINT16                          usTmp             = 0;

    usTmp = *pucBytePos;

    /* 如果此参数重复出现，需要跳过 */
    if (VOS_TRUE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIspSrvCategoryPresent)
    {
        *pucBytePos += pucData[usTmp + 1] + 2;

        TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeSrvCategory:Parameter ServiceCategory is repeated");

        return VOS_OK;
    }

    /* 如果长度不对返回错误 */
    if (2 != pucData[usTmp + 1])
    {
        /* 如果之前解码的过程中没有发生过错误 */
        if (VOS_FALSE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent)
        {
            /* 填写 cause code 字段 */
            TAF_XSMS_TL_FillCauseCode(TAF_XSMS_TL_CAUSECODE_TMP,
                                      TAF_XSMS_TL_UNEXPECTED_PARM_SIZE,
                                      pstTLStru->ucBearReplySeqNum,
                                      pstTLStru);
        }

        *pucBytePos += pucData[usTmp + 1] + 2;

        TAF_XSMS_ERROR_LOG("TAF_XSMS_TL_DecodeSrvCategory:Parameter length of ServiceCategory is invalid");

        return VOS_ERR;
    }

    /* 解码开始参考协议C.S0015 章节3.4.3.2 */
    usSrvCateHighByte = pucData[usTmp + 2];
    usSrvCateHighByte = (VOS_UINT16)(usSrvCateHighByte << 8);
    usSrvCateLowByte  = pucData[usTmp + 3];
    pstTLStru->stMessage.ulServiceCategory = usSrvCateHighByte | usSrvCateLowByte;
    pstTLStru->stMessage.bIsServicePresent = 1;

    /* 该参数字段在TL层码流中占4个byte，故字节增量为4 */
    *pucBytePos += 4;

    /* 置位字段存在标志位 */
    pstTLStru->unPresentFlag.stTLBitPresentFlag.bIspSrvCategoryPresent = VOS_TRUE;

    TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeSrvCategory: Decode successed");

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_TL_DecodeAddr
 功能描述  : 将tpdu转化成内部应用的传输层数据的地址信息
 输入参数  : pucData        TL层码流
             pucBytePos     本参数在码流中的位置
 输出参数  : pstTLStru      TL层结构体
 返 回 值  : VOS_OK -- 解码成功
             VOS_ERR -- 解码失败
 调用函数  :
 被调函数  :
 其    他  :
                    地址参数的结构
     -------------------------------------------
    |    Field          |   Length (bits)       |
    |    PARAMETER_ID   |       8               |
    |    PARAMETER_LEN  |       8               |
    |    DIGIT_MODE     |       1               |
    |    NUMBER_MODE    |       1               |
    |    NUMBER_TYPE    |     0 or 3            |
    |    NUMBER_PLAN    |     0 or 4            |
    |    NUM_FIELDS     |       8               |
     -------------------------------------------
        NUM_FIELDS occurrences of the following field:
     ------------------------------------------
    |    CHARi          |     4 or 8            |
     ------------------------------------------
        The parameter ends with the following field:
     -------------------------------------------
    |    RESERVED       |     0-7               |
     -------------------------------------------
 修改历史      :
  1.日    期   : 2014年11月05日
    作    者   : x00306642
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TL_DecodeAddr(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          usBitPos = 0;
    VOS_UINT8                           ucDigitMode;
    VOS_UINT8                           ucAddrLen;
    VOS_UINT8                           ucTmp;
    VOS_UINT8                           ucOffset;
    TAF_XSMS_ADDR_STRU                 *pstAddr;

    pstAddr = &pstTLStru->stMessage.stAddr;
    ucOffset = *pucBytePos;

   /* 如果此数据已经存在 , 跳过本段参数 */
    if (VOS_TRUE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpOrigAddrPresent)
    {
        *pucBytePos += pucData[ucOffset + 1] + 2;
        TAF_XSMS_ERROR_LOG("TAF_XSMS_TL_DecodeAddr:Parameter Address is repeated");

        return VOS_OK;
    }

    ucAddrLen = pucData[ucOffset + 1];

    usBitPos  = 2 * TAF_XSMS_BIT_NUMBER_OF_BYTE;

    /* 解码digit mode字段 */
    TAF_XSMS_TL_UnpackByteToBit(pucData + ucOffset, &pstAddr->enDigitMode, usBitPos, 1);
    usBitPos++;

    /* 解码number mode字段 */
    TAF_XSMS_TL_UnpackByteToBit(pucData + ucOffset, &pstAddr->enNumberMode, usBitPos, 1);
    usBitPos++;

    /* 解码number type和number plan字段 */
    if (TAF_XSMS_DIGIT_MODE_8_BIT == pstAddr->enDigitMode)
    {
        ucDigitMode = 8;

        TAF_XSMS_TL_UnpackByteToBit(pucData + ucOffset, &pstAddr->enNumberType, usBitPos, 3);
        usBitPos += 3;

        if(TAF_XSMS_NUMBER_MODE_NOT_DATA_NETWORK == pstAddr->enNumberMode)
        {
            TAF_XSMS_TL_UnpackByteToBit(pucData + ucOffset, &pstAddr->enNumberPlan, usBitPos, 4);
            usBitPos += 4;
        }
        else
        {
            pstAddr->enNumberPlan = TAF_XSMS_NUMBER_PLAN_UNKNOWN;
        }
    }
    else
    {
        ucDigitMode = 4;
        pstAddr->enNumberType = TAF_XSMS_NUMBER_TYPE_UNKNOWN;
        pstAddr->enNumberPlan = TAF_XSMS_NUMBER_PLAN_UNKNOWN;
    }

    /* 解码address numbers字段 */
    TAF_XSMS_TL_UnpackByteToBit(pucData + ucOffset, &ucTmp, usBitPos, 8);
    pstAddr->ulNumberOfDigits = ucTmp;
    usBitPos += 8;

    /* 解码address digits字段 */
    for (i = 0; i < pstAddr->ulNumberOfDigits; i++)
    {
        TAF_XSMS_TL_UnpackByteToBit(pucData + ucOffset, &pstAddr->aucDigits[i], usBitPos, ucDigitMode);
        usBitPos += ucDigitMode;
    }

    if (usBitPos > (VOS_UINT32)((ucAddrLen + 2) * TAF_XSMS_BIT_NUMBER_OF_BYTE))
    {
        *pucBytePos = ucOffset + ucAddrLen + 2;
        return VOS_ERR;
    }

    *pucBytePos = ucOffset + ucAddrLen + 2;

    /* 置位字段存在标志位 */
    pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpOrigAddrPresent = VOS_TRUE;

    TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeAddr:Decode successed");

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_TL_DecodeSubAddr
 功能描述  : 将TPDU 转化成内部应用的传输层数据的子地址信息
 输入参数  : pucData        TL层码流
             pucBytePos     本参数在码流中的位置
 输出参数  : pstTLStru      TL层结构体
 返 回 值  : VOS_OK -- 解码成功
             VOS_ERR -- 解码失败
 调用函数  :
 被调函数  :
 其    他  :
                    子地址参数的结构
      -----------------------------------------------
     |       Field       |   Length (bits)          |
     |   PARAMETER_ID    |       8                  |
     |   PARAMETER_LEN   |       8                  |
     |   TYPE            |       3                  |
     |   ODD             |       1                  |
     |   NUM_FIELDS      |       8                  |
      -----------------------------------------------
        NUM_FIELDS instances of the following field:
      ----------------------------------------------
     |   CHARi           |       8                  |
      ----------------------------------------------
         The parameter ends with the following field:
      ----------------------------------------------
     |   RESERVED        |       4                  |
      ----------------------------------------------
 修改历史      :
  1.日    期   : 2014年11月05日
    作    者   : j00304117
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TL_DecodeSubAddr(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usTmp;
    VOS_UINT16                          usBitPos;

    usTmp       = 0;
    usBitPos    = 0;
    usTmp       = *pucBytePos;

    /* 如果此数据已经存在 , 跳过本段参数 */
    if (VOS_TRUE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpOrigSubAddrPresent)
    {
        *pucBytePos += pucData[usTmp + 1] + 2;
        TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeSubAddr:Parameter SubAddress is repeated");

        return VOS_OK;
    }

    /* 如果长度不对返回错误 */
    if ((0 == pucData[usTmp + 1])
        || (TAF_XSMS_MAX_SUBADDRESS_PARAM_LEN < pucData[usTmp + 1]))
    {
        if (VOS_FALSE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent)
        {
            TAF_XSMS_TL_FillCauseCode(TAF_XSMS_TL_CAUSECODE_TMP,
                                      TAF_XSMS_TL_UNEXPECTED_PARM_SIZE,
                                      pstTLStru->ucBearReplySeqNum,
                                      pstTLStru);
        }

        *pucBytePos += pucData[usTmp + 1] + 2;
        TAF_XSMS_ERROR_LOG("TAF_XSMS_TL_DecodeSubAddr:Parameter length of SubAddress is invalid");

        return VOS_ERR;
    }

    /*根据协议 C.S0015 章节3.4.3.3 */
    usBitPos        = 2 * TAF_XSMS_BIT_NUMBER_OF_BYTE;
    TAF_XSMS_TL_UnpackByteToBit(pucData + usTmp,
                                &pstTLStru->stMessage.stSubAddr.enSubAddrType,
                                usBitPos,  /* Type在第三个字节bit7开始到bit5结束 */
                                3);

    usBitPos += 3;
    TAF_XSMS_TL_UnpackByteToBit(pucData + usTmp,
                                &pstTLStru->stMessage.stSubAddr.ucOdd,
                                usBitPos,      /* Type在第三个字节bit4 */
                                1);
    usBitPos += 1;

    TAF_XSMS_TL_UnpackByteToBit(pucData + usTmp,
                                &pstTLStru->stMessage.stSubAddr.ucNumberOfDigits,
                                usBitPos,     /* Type在第三个字节bit3 */
                                8);
    usBitPos += 8;

    ucIndex = 0;
    while(ucIndex < pstTLStru->stMessage.stSubAddr.ucNumberOfDigits)
    {
        /* 把号码填到数组中去 */
        TAF_XSMS_TL_UnpackByteToBit(pucData + usTmp,
                                    &pstTLStru->stMessage.stSubAddr.aucDigits[ucIndex++],
                                    usBitPos,
                                    8);
        usBitPos += 8;
    }
    *pucBytePos += pucData[usTmp + 1] + 2;

    TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeSubAddr:Decode successed");

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_TL_DecodeBearReplyOption
 功能描述  : 将tpdu 转化成内部应用的传输层数据BearReplyOption
 输入参数  : pucData        TL层码流
             pucBytePos     本参数在码流中的位置
 输出参数  : pstTLStru      TL层结构体
 返 回 值  : VOS_OK -- 解码成功
             VOS_ERR -- 解码失败
 调用函数  :
 被调函数  :
 其    他  :
               Bearer Reply Option 结构
         ---------------------------------------
        |   Field           |    Length (bits)  |
        |   PARAMETER_ID    |       8           |
        |   PARAMETER_LEN   |       8           |
        |   REPLY_SEQ       |       6           |
        |   RESERVED        |       2           |
         ---------------------------------------

 修改历史      :
  1.日    期   : 2014年11月05日
    作    者   : j00304117
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TL_DecodeBearReplyOption(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
)
{
    VOS_UINT16                          usTmp = 0;

    usTmp = *pucBytePos;

    /* 如果此数据已经存在 , 跳过本段参数 */
    if (VOS_TRUE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpBearReplyOpPresent)
    {
        *pucBytePos += pucData[usTmp + 1] + 2;
        TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeBearReplyOption:Parameter Bear Reply Option is repeated");

        return VOS_OK;
    }

    /* 如果长度不对返回错误 */
    if (1 != pucData[usTmp + 1])
    {
        /* 如果之前解码的过程中没有发生过错误 */
        if (VOS_FALSE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent)
        {
            TAF_XSMS_TL_FillCauseCode(TAF_XSMS_TL_CAUSECODE_TMP,
                                      TAF_XSMS_TL_UNEXPECTED_PARM_SIZE,
                                      pstTLStru->ucBearReplySeqNum,
                                      pstTLStru);
        }

        *pucBytePos += pucData[usTmp + 1] + 2;
        TAF_XSMS_ERROR_LOG("TAF_XSMS_TL_DecodeBearReplyOption:Parameter length of Bear Reply Option is invalid");

        return VOS_ERR;
    }

    pstTLStru->ucBearReplySeqNum = (pucData[usTmp + 2] >> 2) & 0x3f;
    pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpBearReplyOpPresent = 1;
    *pucBytePos += 3;

    TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeBearReplyOption:Decode Parameter Bear Reply Option successed");

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_TL_DecodeCauseCode
 功能描述  : 将TPDU 中数据转化成内部应用的传输层数据的CauseCode
 输入参数  : pucData        TL层码流
             pucBytePos     本参数在码流中的位置
 输出参数  : pstTLStru      TL层结构体
 返 回 值  : VOS_OK -- 解码成功
             VOS_ERR -- 解码失败
 调用函数  :
 被调函数  :
 其    他  :
               Cause Code 结构
         ---------------------------------------
        |   Field           |    Length (bits)  |
        |   PARAMETER_ID    |       8           |
        |   PARAMETER_LEN   |       8           |
        |   REPLY_SEQ       |       6           |
        |   ERROR_CLASS     |       2           |
        |   CAUSE_CODE      |     0 or 8        |
         ---------------------------------------

 修改历史      :
  1.日    期   : 2014年11月05日
    作    者   : j00304117
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TL_DecodeCauseCode(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
)
{
    VOS_UINT16                          usTmp = 0;

    /* CauseCode已经存在 */
    if ((VOS_TRUE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent)
        && (TAF_XSMS_TL_ACK_MSG == pstTLStru->enMessageType))
    {
        /* 跳过 */
        *pucBytePos += 3;

        TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeCauseCode:Parameter Cause Code is repeated");

        return VOS_ERR;
    }

    usTmp = *pucBytePos;

    /* 如果长度不对返回错误 */
    if ((1 != pucData[usTmp + 1])
        && (2 != pucData[usTmp + 1]))
    {
        /* 如果之前解码的过程中没有发生过错误 */
        if (VOS_FALSE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent)
        {
            TAF_XSMS_TL_FillCauseCode(TAF_XSMS_TL_CAUSECODE_TMP,
                                      TAF_XSMS_TL_UNEXPECTED_PARM_SIZE,
                                      pstTLStru->ucBearReplySeqNum,
                                      pstTLStru);
        }

        TAF_XSMS_ERROR_LOG("TAF_XSMS_TL_DecodeCauseCode:Parameter length of Cause Code is invalid");

        return VOS_ERR;

    }

    /* 填写CauseCode字段 */
    pstTLStru->stCauseCode.ucParameterLen   = pucData[usTmp + 1];
    pstTLStru->stCauseCode.ucReplySeq       = (pucData[usTmp + 2] >> 2) & 0x3f;
    pstTLStru->stCauseCode.enErrorClass     = pucData[usTmp + 2] & 0x03;

    /* 是否有错，有错则填写 */
    if (pstTLStru->stCauseCode.ucParameterLen == 2)
    {
        pstTLStru->stCauseCode.enCauseCode  = pucData[usTmp + 3];
    }

    /*  解码出实际的Bear Data了，替换掉可能错误的Bear Data */
    TAF_XSMS_TL_FillCauseCodeSeq(pstTLStru);
    pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent = 1;
    *pucBytePos += pstTLStru->stCauseCode.ucParameterLen + 2;

    TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeCauseCode:Decode Parameter Cause Code successed");

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_TL_DecodeBearData
 功能描述  : 将TPDU 中数据转化成内部应用的传输层数据BearData
 输入参数  : pucData

 输出参数  : 无
 返 回 值  :Error_type
 调用函数  :
 被调函数  :
 其    他  :
                Bearer  Data 结构
         ---------------------------------------
        |   Field           |    Length (bits)  |
        |   PARAMETER_ID    |       8           |
        |   PARAMETER_LEN   |       8           |
         ---------------------------------------
         One or more occurrences of the following subparameter record:
         ---------------------------------------
        |   SUBPARAMETER_ID |       8           |
        |   SUBPARAM_LEN    |       8           |
        | Subparameter Data |  8*SUBPARAM_LEN   |
         ---------------------------------------

 修改历史      :
  1.日    期   : 2014年11月05日
    作    者   : j00304117
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TL_DecodeBearData(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
)
{
    VOS_UINT16                          usTmp             = 0;

    usTmp = *pucBytePos;

    /* 如果此数据已经存在 , 跳过本段参数 */
    if (VOS_TRUE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpBearDataPresent)
    {
        *pucBytePos += pucData[usTmp + 1] + 2;

        TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeBearData:Parameter Bear Data is repeated");

        return VOS_OK;
    }

    /* 判断参数长度是否正确 */
    if (0 == pucData[usTmp + 1])
    {
        /* 如果之前解码的过程中没有发生过错误 */
        if (VOS_FALSE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent)
        {
            TAF_XSMS_TL_FillCauseCode(TAF_XSMS_TL_CAUSECODE_TMP,
                                      TAF_XSMS_TL_UNEXPECTED_PARM_SIZE,
                                      pstTLStru->ucBearReplySeqNum,
                                      pstTLStru);
        }

        TAF_XSMS_ERROR_LOG("TAF_XSMS_TL_DecodeBearData:Parameter length of Bear Data is invalid");

        return VOS_ERR;

    }

    /* 拷贝Bearer Data数据到结构体中 */
    PS_MEM_CPY(pstTLStru->stMessage.aucBearerData, pucData + usTmp + 2, pucData[usTmp + 1]);

    pstTLStru->stMessage.ulBearerDataLen = pucData[usTmp + 1];

    pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpBearDataPresent = 1;
    *pucBytePos += pucData[usTmp + 1] + 2;

    TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeBearData:Decode Parameter Bear Data successed");

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_DecodeTLRawToTLStru
 功能描述  : Transport Layer码流转换成TL层结构体，如果是PRL短信，调整Bear Data参数
             数据位置
 输入参数  : ucTLRawLen           TL层码流长度
            *pucTLRaw             TL层码流
 输出参数  : *pstTLMsg             TL层结构体
 返 回 值  : VOS_OK -- 解码成功
             VOS_ERR -- 解码失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_DecodeTLRawToTLStru(
    VOS_UINT8                           ucTLRawLen,
    VOS_UINT8                          *pucTLRaw,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLMsg
)
{
    VOS_UINT8                          *pucBuffer;
    VOS_UINT8                           ucBytePos;
    VOS_UINT8                           ucErrCnt;
    VOS_UINT8                           i;
    VOS_UINT32                          ulResult;

    ucErrCnt    = 0;
    ucBytePos   = 1;
    pucBuffer   = pucTLRaw;


    /* 清参数存在标志位 */
    pstTLMsg->unPresentFlag.ausValue[0] = 0;

    /* 获取消息类型 */
    pstTLMsg->enMessageType = pucBuffer[0];

    /* 消息类型不正确，返回失败 */
    if (pstTLMsg->enMessageType >= TAF_XSMS_TL_MSG_TYPE_BUTT)
    {
        pstTLMsg->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent = VOS_TRUE;
        TAF_XSMS_TL_FillCauseCode(TAF_XSMS_TL_CAUSECODE_TMP,
                                  TAF_XSMS_TL_UNRECOGNIZED_PARM_VALUE,
                                  pstTLMsg->ucBearReplySeqNum,
                                  pstTLMsg);

        TAF_XSMS_ERROR_LOG("TAF_XSMS_DecodeTLRawToTLStru:Unsupported message type");

        return VOS_ERR;
    }

    /* 根据码流里不同的Parameter ID进入不同的处理程序 */
    while (ucBytePos < ucTLRawLen)
    {
        for (i = 0; i < TAF_XSMS_TL_PARAMETER_MAX; i++)
        {
            if (pucBuffer[ucBytePos] == g_astTLParmDecodeFuncList[i].enParaId)
            {
                /* 判断解码过程是否出错 */
                if (VOS_OK != g_astTLParmDecodeFuncList[i].pstParaDecodeFunc(pucBuffer, &ucBytePos, pstTLMsg))
                {
                    ucErrCnt++;
                }
                break;
            }
        }

        if (TAF_XSMS_TL_PARAMETER_MAX == i)
        {
            ucBytePos += pucBuffer[ucBytePos + 1] + 2;
        }
    }

    /* 判断解码的码流长度是否正好等于已知的码流长度，如果不是，返回解码错误 */
    if (ucBytePos != ucTLRawLen)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_DecodeTLRawToTLStru:Decode failed");

        return VOS_ERR;
    }

    /* 判断出已经出错 */
    if (0 != ucErrCnt)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_DecodeTLRawToTLStru:Decode failed");

        return VOS_ERR;
    }

    ulResult = TAF_XSMS_CheckFields(pstTLMsg);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_CheckFields
 功能描述  : 判断必要参数是否缺失
 输入参数  : pstTLMsg:TL层结构体
 输出参数  : 无
 返 回 值  : VOS_ERR:缺失必要参数，返回错误
             VOS_OK:不缺失必要参数，返回正确
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月05日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_XSMS_CheckFields(TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLMsg)
{
    /* 根据协议检查必要参数是否缺失，缺失则解码失败 */
    switch(pstTLMsg->enMessageType)
    {
        case TAF_XSMS_TL_P2P_MSG:

            /* 判断如果缺少Teleservice ID或者 */
            if ((VOS_FALSE == pstTLMsg->unPresentFlag.stTLBitPresentFlag.bIsTelesrvIdPresent)
                || (VOS_FALSE == pstTLMsg->unPresentFlag.stTLBitPresentFlag.bIsOpOrigAddrPresent))
            {
                /* 之前解码的过程中没有发生过错误 */
                pstTLMsg->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent = VOS_TRUE;
                TAF_XSMS_TL_FillCauseCode(TAF_XSMS_TL_CAUSECODE_TMP,
                                          TAF_XSMS_TL_MISSING_MANDATORY_PARM,
                                          pstTLMsg->ucBearReplySeqNum,
                                          pstTLMsg);

                TAF_XSMS_ERROR_LOG("TAF_XSMS_CheckFields:Point to point message missing mandatory paramter");

                return VOS_ERR;

            }
            else
            {
                /* 解码成功，判断是否为PRL短信，如果是PRL，调整Bear Data内容顺序 */
                TAF_XSMS_IsPRL(pstTLMsg);

            }
            break;


        case TAF_XSMS_TL_ACK_MSG:
            if (VOS_FALSE == pstTLMsg->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent)
            {
                pstTLMsg->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent = VOS_TRUE;
                TAF_XSMS_TL_FillCauseCode(TAF_XSMS_TL_CAUSECODE_TMP,
                                          TAF_XSMS_TL_MISSING_MANDATORY_PARM,
                                          pstTLMsg->ucBearReplySeqNum,
                                          pstTLMsg);

                TAF_XSMS_ERROR_LOG("TAF_XSMS_CheckFields:Ack message missing mandatory paramter");

                return VOS_ERR;
            }

            break;

        default:

            TAF_XSMS_ERROR_LOG("TAF_XSMS_CheckFields:Unsopported message type");

            return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_FillBDShortStru
 功能描述  : 把BearerDate里的子参数填写到自定结构体中
 输入参数  : pucBuffer              Bearer Data层码流
             pucBytePos             Bearer Data层某一个子参数起始位置
 输出参数  : pstBDParamStru         临时结构体
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月05日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID TAF_XSMS_FillBDShortStru(
    VOS_UINT8                                              *pucBuffer,
    VOS_UINT8                                              *pucBytePos,
    TAF_XSMS_BD_GENERAL_PARAMETER_8B_STRU                  *pstBDParamStru
)
{
    VOS_UINT8                           ucOffset;

    ucOffset                        = *pucBytePos;
    pstBDParamStru->enParamHeader   = pucBuffer[ucOffset];
    pstBDParamStru->ucLen           = pucBuffer[ucOffset + 1];
    pstBDParamStru->ucBytePos       = *pucBytePos;
    ucOffset                       += (pstBDParamStru->ucLen + 2);
    *pucBytePos                     = ucOffset;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_IsPRL
 功能描述  : 判断是否为PRL更新短信，如果是，解释调整Bear Data参数中子参数的位置
 输入参数  : ucBDRawLen            TL层码流长度
             *pstTLMsg             TL层结构体
 输出参数  : *pstTLMsg             TL层结构体
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : j00304117
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_IsPRL(TAF_XSMS_TRANSPORT_MESSAGE_STRU *pstTLMsg)
{
    VOS_UINT32                                              ulPresentFlag;
    VOS_UINT8                                               ucBDRaw[MAX_BD_BYTE_LENGTH] = {0};
    VOS_UINT8                                               ucBytePos;
    VOS_UINT8                                               ucIndex;
    TAF_XSMS_BD_GENERAL_PARAMETER_8B_STRU                   astBDParamShort[20];
    TAF_XSMS_BD_MSG_DISPLAY_MODE_STRU                       stBDDisplayMode;

    ucBytePos           = 0;
    ucIndex             = 0;
    ulPresentFlag       = 0;
    PS_MEM_SET(astBDParamShort, 0, 20 * sizeof(TAF_XSMS_BD_GENERAL_PARAMETER_8B_STRU));

    /* 拷贝数据 */
    PS_MEM_CPY(ucBDRaw, pstTLMsg->stMessage.aucBearerData, pstTLMsg->stMessage.ulBearerDataLen);

    /* 根据Bearer Data的子参数进入不同的处理程序 */
    while (ucBytePos < pstTLMsg->stMessage.ulBearerDataLen)
    {
        /* 判断是否为Display Mode字段 */
        if (TAF_XSMS_BD_MESSAGE_DISPLAY_MODE == ucBDRaw[ucBytePos])
        {
            stBDDisplayMode.enParamHeader           = TAF_XSMS_BD_MESSAGE_DISPLAY_MODE;
            stBDDisplayMode.ucLen                   = ucBDRaw[ucBytePos + 1];
            stBDDisplayMode.ucMsgDisplayMode        = ucBDRaw[ucBytePos + 2] >> 6;
            stBDDisplayMode.ucMsgReserverd          = ucBDRaw[ucBytePos + 2] & 0x3f;

            /* 判断是否为PRL更新短信 */
            if ((0x03 == stBDDisplayMode.ucMsgDisplayMode)
                && (0x10 == stBDDisplayMode.ucMsgReserverd))
            {
                pstTLMsg->unPresentFlag.stTLBitPresentFlag.bIsOpIsPRL = VOS_TRUE;
            }
            /* 判断是否为PP DOWNLOAD更新短信 */
            if ((0x03 == stBDDisplayMode.ucMsgDisplayMode)
             && (0x20 == stBDDisplayMode.ucMsgReserverd))
            {
                pstTLMsg->unPresentFlag.stTLBitPresentFlag.bIsOpIsPPDownload = VOS_TRUE;
            }
        }

        /* 判断是否参数是否不合法 */
        if (ucBDRaw[ucBytePos] > TAF_XSMS_BD_MESSAGE_STATUS)
        {
            ucBytePos += (ucBDRaw[ucBytePos + 1] + 2);
            continue;
        }

        /*lint -e701*/
        ulPresentFlag |= (1 << ucBDRaw[ucBytePos]);
        /*lint +e701*/

        TAF_XSMS_FillBDShortStru(ucBDRaw, &ucBytePos, &astBDParamShort[ucBDRaw[ucBytePos]]);


    }

    if (VOS_TRUE == pstTLMsg->unPresentFlag.stTLBitPresentFlag.bIsOpIsPRL)
    {
        /* 调整BD层参数的位置 */
        ucBytePos = 0;

        /* 写Message字段 */
        PS_MEM_CPY(pstTLMsg->stMessage.aucBearerData,
                   ucBDRaw+astBDParamShort[TAF_XSMS_BD_MESSAGE_IDENTIFIER].ucBytePos,
                   astBDParamShort[TAF_XSMS_BD_MESSAGE_IDENTIFIER].ucLen + 2);
        ucBytePos += astBDParamShort[TAF_XSMS_BD_MESSAGE_IDENTIFIER].ucLen + 2;

        /* 写Display Mode字段 */
        PS_MEM_CPY(pstTLMsg->stMessage.aucBearerData+ucBytePos,
                   ucBDRaw+astBDParamShort[TAF_XSMS_BD_MESSAGE_DISPLAY_MODE].ucBytePos,
                   astBDParamShort[TAF_XSMS_BD_MESSAGE_DISPLAY_MODE].ucLen + 2);
        ucBytePos += astBDParamShort[TAF_XSMS_BD_MESSAGE_DISPLAY_MODE].ucLen + 2;

        for (ucIndex = 1;ucIndex<20;ucIndex++)
        {
            /* 跳过Display Mode字段 */
            if (TAF_XSMS_BD_MESSAGE_DISPLAY_MODE == ucIndex)
            {
                continue;
            }

            /*lint -e701*/
            if ((ulPresentFlag & (1 << ucIndex)) == (1 << ucIndex))
            {
                PS_MEM_CPY(pstTLMsg->stMessage.aucBearerData + ucBytePos,
                           ucBDRaw+astBDParamShort[ucIndex].ucBytePos,
                           astBDParamShort[ucIndex].ucLen + 2);
                ucBytePos += astBDParamShort[ucIndex].ucLen + 2;
                continue;
            }
            /*lint +e701*/
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_DecodeUserDataInBearerData
 功能描述  : 解析BEARER DATA里面的USER DATA
 输入参数  : ulBearDataLen                  BEARER DATA 长度
             *pucBearerData                 BEARER DATA 数据
 输出参数  : *pusUserDataStartByte          USER DATA  在BEARER DATA的开始位置
             *pusUserDataLen                USER DATA TLV长度
             *pstUserData                   TL层结构体
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_DecodeUserDataInBearerData(
    VOS_UINT32                          ulBearDataLen,  /* in */
    VOS_UINT8                          *pucBearerData,  /* in */
    VOS_UINT16                         *pusUserDataStartByte,   /* out */
    VOS_UINT16                         *pusUserDataLen, /* out 在BearerData中的长度，不是数据实际长度 */
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstUserData     /* out */
)
{
    VOS_UINT16                          usBytePos = 0;
    VOS_UINT16                          usParaLen = 0;
    VOS_UINT32                          ulBitPos  = 0;
    VOS_UINT32                          ulIndex   = 0;
    VOS_UINT32                          ulRet     = 0;
    VOS_UINT8                           ucBitsNumOfChari = 0;

    *pusUserDataLen = 0;

    /* 根据Bearer Data的子参数进入不同的处理程序 */
    while (usBytePos < ulBearDataLen)
    {
        usParaLen   =  pucBearerData[usBytePos + 1];
        ulBitPos    =  8 * (usBytePos + 2);

        if (TAF_XSMS_BD_USER_DATA == pucBearerData[usBytePos])
        {
            /* PARA ID      8BITS
               PARA LEN     8BITS
               MSG_ENCODING 5BITS
               MSG_TYPE     0 OR 8BITS
               NUM_FIELD    8 BITS */

            *pusUserDataStartByte = usBytePos;
            *pusUserDataLen       = pucBearerData[usBytePos + 1] + 2;

            pstUserData->enMsgCodeType = (pucBearerData[usBytePos + 2] & 0xF8) >> 3 ;

            ulBitPos += 5;

            if (TAF_XSMS_USER_DATA_MSG_ENCODE_EPM == pstUserData->enMsgCodeType)
            {
                TAF_XSMS_TL_UnpackByteToBit(pucBearerData,
                                            &pstUserData->ucMsgType,
                                            (VOS_UINT16)ulBitPos,
                                            8);
                ulBitPos  += 8;
            }

            TAF_XSMS_TL_UnpackByteToBit(pucBearerData,
                                        &pstUserData->ucNumFields,
                                        (VOS_UINT16)ulBitPos,
                                        8);
            ulBitPos  += 8;

            /* 根据编码格式，得到每个数据的bit长度 7,8 还是16bit */
            ulRet = TAF_XSMS_GetUserDataCodeBitsByMsgCode(pstUserData->enMsgCodeType,
                                                          &ucBitsNumOfChari);

            ucBitsNumOfChari = 8;

            /* 默认全是8BITS */
            if (VOS_OK == ulRet)
            {
                /* 在USER DATA的 data字段 NUM_FIELDS有时候不发挥作用 */
                for (ulIndex = 0;
                      (((ulBitPos < (usBytePos + usParaLen + 2) * 8)) && (TAF_XSMS_BD_USER_DATA_MAX_LEN > ulIndex));
                       ulIndex++)
                {

                    TAF_XSMS_TL_UnpackByteToBit(pucBearerData,
                                                &pstUserData->aucUserData[ulIndex],
                                                (VOS_UINT16)(ulBitPos),
                                                ucBitsNumOfChari);
                    ulBitPos  += ucBitsNumOfChari;

                }

            }

            /* 要不要退出循环  */
            break;
        }

        /* 判断是否参数是否不合法 */
        if (pucBearerData[usBytePos] > TAF_XSMS_BD_MESSAGE_STATUS)
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_DecodeUserDataInBearerData : ERROR PARA ID");
        }

        usBytePos += (usParaLen + 2);
        ulBitPos   = 0;
    }

    return;

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_GetUserDataCodeBitsByMsgCode
 功能描述  : 得到每种编码方式的bit个数
 输入参数  : enMsgCodeType  编码格式
 输出参数  : *pucBitNum  bit个数
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_GetUserDataCodeBitsByMsgCode(
    TAF_XSMS_USER_DATA_MSG_ENCODE_ENUM8 enMsgCodeType,
    VOS_UINT8                          *pucBitNum
)
{
    switch (enMsgCodeType)
    {
        case    TAF_XSMS_USER_DATA_MSG_ENCODE_ASCII_7:
        case    TAF_XSMS_USER_DATA_MSG_ENCODE_IA5:
        case    TAF_XSMS_USER_DATA_MSG_ENCODE_GSM_7:
            *pucBitNum = 7;
            return VOS_OK;

        case    TAF_XSMS_USER_DATA_MSG_ENCODE_OCTET:
        case    TAF_XSMS_USER_DATA_MSG_ENCODE_HEBREW:
        case    TAF_XSMS_USER_DATA_MSG_ENCODE_LATIN:
            *pucBitNum = 8;
            return VOS_OK;

        case    TAF_XSMS_USER_DATA_MSG_ENCODE_UNICODE:
            *pucBitNum = 16;
            return VOS_OK;

        default:
            /* 其他解码方式中国电信不支持 */
            TAF_XSMS_ERROR_LOG("TAF_XSMS_GetUserDataCodeBitsByMsgCode : MSG_CODE NOT RIGHT");
            *pucBitNum = 0;
            return VOS_ERR;

    }

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_PressUserData
 功能描述  : 压缩USER DATA
 输入参数  : pstUserData  USER_DATA
 输出参数  : pstUserData  USER_DATA
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_PressUserData(
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstUserData
)
{
    VOS_UINT32                          ulIndex     = 0;
    VOS_UINT8                           aucUserData[256] = {0};
    VOS_UINT8                           ucNumOfFields = 0;
    VOS_UINT8                           ucOffset = 0;
    VOS_UINT8                           ucIndexInOldUserData = 0;
    VOS_UINT8                           ucNumOfLowBits = 0;

    //pstUserData->enMsgCodeType = TAF_XSMS_USER_DATA_MSG_ENCODE_ASCII_7; /* 需要确定 */
    ucNumOfFields    =  (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstUserData->aucUserData);

    if ((pstUserData->ucNumFields > ucNumOfFields)
     || (0 == pstUserData->ucNumFields))
    {
        pstUserData->ucNumFields = ucNumOfFields;
    }

    for (ulIndex = 0; ulIndex <  (pstUserData->ucNumFields / 8 * 7 + pstUserData->ucNumFields % 8); ulIndex++)
    {
       ucOffset = ulIndex % 7 + 1;
       /* 第一个byte 是 第二个byte  最低一位 + 第一个byte的 最低 7位
          第二个byte 是 第三个byte  最低2位 + 第2个byte的   最低 6位
       */

       ucIndexInOldUserData = (VOS_UINT8)((ulIndex / 7) * 8 + ulIndex % 7);

       if (ucIndexInOldUserData + 1 >= ucNumOfFields)
       {
            break;
       }

       ucNumOfLowBits       = TAF_XSMS_GetLowBits(8 - ucOffset);

       /*lint -e701*/
       aucUserData[ulIndex] = (pstUserData->aucUserData[ucIndexInOldUserData] & ucNumOfLowBits)
                               + (VOS_UINT8)(pstUserData->aucUserData[ucIndexInOldUserData + 1] << (8 - ucOffset));

       pstUserData->aucUserData[ucIndexInOldUserData + 1] = pstUserData->aucUserData[ucIndexInOldUserData + 1] >> ucOffset;
       /*lint +e701*/
    }

    PS_MEM_CPY(pstUserData->aucUserData, aucUserData, 256);

    return;
}

VOS_UINT8 TAF_XSMS_GetLowBits(VOS_UINT8 ucOffset)
{
    VOS_UINT8               ucOutPut = 0;
    VOS_UINT8               ucIndex  = 0;

    if (8  < ucOffset)
    {
        return 0;
    }

    for (ucIndex = 1; ucIndex <= ucOffset; ucIndex++)
    {
        /*lint -e701*/
        ucOutPut += (VOS_UINT8)(0x01 << (ucIndex - 1));
        /*lint +e701*/
    }

    return ucOutPut;

}
/*****************************************************************************
 函 数 名  : TAF_XSMS_EncodeUserData
 功能描述  : ENCODE USER DATA
 输入参数  : pstUserData  USER_DATA STRU
 输出参数  : pucUserDataLen 数组长度
             paucUserData   数组内容
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_EncodeUserData(
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstUserData,    /* in */
    VOS_UINT8                          *pucUserDataLen, /* out */
    VOS_UINT8                          *paucUserData    /* out */
)
{
    VOS_UINT8                           ucIndex     = 0;
    VOS_UINT16                          usBitpos    = 0;
    VOS_UINT8                           ucBitNumInChar = 0;

    /* PARA ID      8BITS
    PARA LEN     8BITS
    MSG_ENCODING 5BITS
    MSG_TYPE     0 OR 8BITS
    NUM_FIELD    8 BITS */
    TAF_XSMS_PackBitToByte(paucUserData,
                           TAF_XSMS_BD_USER_DATA,
                           8,
                           (VOS_UINT16)usBitpos);

    usBitpos += 8;

    /* PARA LEN 先不填写 */
    usBitpos += 8;

    /* MSG_CODE */
    TAF_XSMS_PackBitToByte(paucUserData,
                           pstUserData->enMsgCodeType,
                           5,
                           (VOS_UINT16)usBitpos);

    usBitpos += 5;

    /* MSG_TYPE */
    if (TAF_XSMS_USER_DATA_MSG_ENCODE_EPM == pstUserData->enMsgCodeType)
    {
        TAF_XSMS_PackBitToByte(paucUserData,
                       pstUserData->ucMsgType,
                       8,
                       (VOS_UINT16)usBitpos);

        usBitpos += 8;
    }

    /* NUM FIELDS  */
    TAF_XSMS_PackBitToByte(paucUserData,
                           pstUserData->ucNumFields,
                           8,
                           (VOS_UINT16)usBitpos);

    usBitpos += 8;

    if (VOS_OK != TAF_XSMS_GetUserDataCodeBitsByMsgCode(pstUserData->enMsgCodeType,
                                                        &ucBitNumInChar))
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_EncodeUserData: unkown msg_code ");
        return;
    }
    /* CHAR I */
    if (16 == ucBitNumInChar)
    {
        for (ucIndex = 0; ucIndex < pstUserData->ucNumFields; ucIndex++)
        {
            TAF_XSMS_PackBitToByte(paucUserData,
                                   pstUserData->aucUserData[2 * ucIndex],
                                   8,
                                   (VOS_UINT16)usBitpos);
            usBitpos += 8;

            TAF_XSMS_PackBitToByte(paucUserData,
                                   pstUserData->aucUserData[2 * ucIndex + 1],
                                   8,
                                   (VOS_UINT16)usBitpos);
            usBitpos += 8;


        }
    }
    else
    {
        for (ucIndex = 0; (ucIndex < (pstUserData->ucNumFields * ucBitNumInChar + 7) / 8) && (ucIndex < 255) ; ucIndex++)
        {

            TAF_XSMS_PackBitToByte(paucUserData,
                                   pstUserData->aucUserData[ucIndex],
                                   8,
                                   (VOS_UINT16)usBitpos);
            usBitpos += 8;
        }

    }

    *pucUserDataLen = (VOS_UINT8)((usBitpos + 7) / 8);

    /* PARA LEN = 总长度 - (PARA ID + PARA LEN 占用的字节) */
    paucUserData[1] = *pucUserDataLen - 2;

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_ReplaceUserData
 功能描述  : 替换短信中老的 USER DATA
 输入参数  :    pstMessage,
                paucPressedUserData,
                ulPressedUserDataLen,
                usOldUserDataStartByte,
                usOldUserDataLen
 输出参数  :
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_ReplaceUserData(
    TAF_XSMS_MESSAGE_STRU              *pstMessage,
    VOS_UINT8                          *paucPressedUserData,
    VOS_UINT32                          ulPressedUserDataLen,
    VOS_UINT16                          usOldUserDataStartByte,
    VOS_UINT16                          usOldUserDataLen
)
{
    if (usOldUserDataLen < ulPressedUserDataLen)
    {
        return;
    }

    PS_MEM_CPY(pstMessage->aucBearerData + usOldUserDataStartByte,
               paucPressedUserData,
               ulPressedUserDataLen);

    PS_MEM_SET(pstMessage->aucBearerData + usOldUserDataStartByte + ulPressedUserDataLen,
               0,
               usOldUserDataLen - ulPressedUserDataLen);

    if (usOldUserDataStartByte + usOldUserDataLen < pstMessage->ulBearerDataLen)
    {

        VOS_MemMove(pstMessage->aucBearerData   + usOldUserDataStartByte    + ulPressedUserDataLen,/* 当前USER DATA 的结尾 */
                    pstMessage->aucBearerData   + usOldUserDataStartByte    + usOldUserDataStartByte,/* 原来USER DATA 的结尾 */
                    pstMessage->ulBearerDataLen - (usOldUserDataStartByte   + usOldUserDataLen));/* USER DATA之后的数据长度 */
    }

    pstMessage->ulBearerDataLen = pstMessage->ulBearerDataLen - (usOldUserDataLen - ulPressedUserDataLen);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_DevideLongCdmaSms
 功能描述  : 将长短信分成2条短信
 输入参数  :
            *pstUserData,        USER DATA
             usUserDataStartByte,在原来的BEARER DATA 中开始位置
 输出参数  :
            pstFirstMessage
            pstSecondMessage
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_DevideLongCdmaSms(
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstUserData,         /* USER DATA */
    VOS_UINT16                          usUserDataStartByte, /* in 在原来的BEARER DATA 中开始位置 */
    VOS_UINT16                          usUserDataLen,       /* in 在原来的BEARER DATA 中长度*/
    TAF_XSMS_MESSAGE_STRU              *pstFirstMessage,     /* 第一条消息*/
    TAF_XSMS_MESSAGE_STRU              *pstSecondMessage    /* 第二条消息 */
)
{
    TAF_XSMS_BD_MSG_USER_DATA_STRU      stSecondUserData;
    VOS_UINT8                           ucFirstUserDataLenInBearData    = 0;
    VOS_UINT8                           ucSecondUserDataLenInBearData   = 0;
    VOS_UINT8                           aucFirstUserData[200]   = {0};
    VOS_UINT8                           aucSecondUserData[200]  = {0};

    PS_MEM_SET(&stSecondUserData, 0, sizeof(stSecondUserData));

    /* USER DATA 拆分成两个 */
    TAF_XSMS_DevideUserData(pstUserData,
                            &stSecondUserData);
    /* ENCODE USER DATA */
    TAF_XSMS_EncodeUserData(pstUserData,
                            &ucFirstUserDataLenInBearData,
                            aucFirstUserData);

    TAF_XSMS_EncodeUserData(&stSecondUserData,
                            &ucSecondUserDataLenInBearData,
                            aucSecondUserData);

    /* REPLACE每一个的USER DATA 字段 (需要确认是否需要设置1/2 2/2这种短信次序) */

    TAF_XSMS_ReplaceUserData(pstFirstMessage,
                             aucFirstUserData,
                             ucFirstUserDataLenInBearData,
                             usUserDataStartByte,
                             usUserDataLen);

    TAF_XSMS_ReplaceUserData(pstSecondMessage,
                             aucSecondUserData,
                             ucSecondUserDataLenInBearData,
                             usUserDataStartByte,
                             usUserDataLen);

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_DevideUserData
 功能描述  : 将长短信分成2条短信
 输入参数  :
            *pstFirstUserData,        USER DATA
 输出参数  :
            pstFirstUserData
            pstSecondUserData
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_DevideUserData(
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstFirstUserData,         /* USER DATA in and out */
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstSecondUserData        /* USER DATA out*/
)
{
    TAF_XSMS_BD_MSG_USER_DATA_STRU      stFirstUserData;
    VOS_UINT16                          usLenLimit      = 0;
    VOS_UINT8                           ucBitsInChari   = 0;

    PS_MEM_CPY(&stFirstUserData,    pstFirstUserData, sizeof(TAF_XSMS_BD_MSG_USER_DATA_STRU));
    PS_MEM_CPY(pstSecondUserData,   pstFirstUserData, sizeof(TAF_XSMS_BD_MSG_USER_DATA_STRU));

    /* 确认编码格式 确认分包上限 */
    TAF_XSMS_GetXsmsLimitLen(pstFirstUserData->enMsgCodeType,
                             &usLenLimit);

    if (0 == usLenLimit)
    {
        return;
    }

    if (VOS_ERR == TAF_XSMS_GetUserDataCodeBitsByMsgCode(pstFirstUserData->enMsgCodeType,
                                                      &ucBitsInChari))
    {
        return;
    }

    if (usLenLimit >= pstFirstUserData->ucNumFields)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_DevideUserData:ucNumFields < limit");
        return;
    }

    stFirstUserData.ucNumFields = (VOS_UINT8)usLenLimit;

    /* 第一条BIT 总数 160 * 7 */
    PS_MEM_CPY(stFirstUserData.aucUserData,
               pstFirstUserData->aucUserData,
               140);

    pstSecondUserData->ucNumFields = pstFirstUserData->ucNumFields - (VOS_UINT8)usLenLimit;

    /* 第二条BIT 总数 总BIT - 160 * 7 */
    PS_MEM_CPY(pstSecondUserData->aucUserData,
               &pstFirstUserData->aucUserData[140],
               ((pstFirstUserData->ucNumFields - usLenLimit) * ucBitsInChari + 7) / 8);


    PS_MEM_CPY(pstFirstUserData, &stFirstUserData, sizeof(TAF_XSMS_BD_MSG_USER_DATA_STRU));

    return;

}


/*****************************************************************************
 函 数 名  : TAF_XSMS_GetXsmsLimitLen
 功能描述  : 得到不同编码方式的USER DATA上限
 输入参数  :
            enMsgCodeType
 输出参数  :
            pusLenLimit

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_GetXsmsLimitLen(
    TAF_XSMS_USER_DATA_MSG_ENCODE_ENUM8 enMsgCodeType,
    VOS_UINT16                         *pusLenLimit
)
{
    VOS_UINT8                           ucBitNumInChari = 0;

    if (VOS_ERR == TAF_XSMS_GetUserDataCodeBitsByMsgCode(
                                        enMsgCodeType,
                                        &ucBitNumInChari))
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_GetXsmsLimitLen : Wrong enMsgCodeType");
        return;
    }

    if (8 == ucBitNumInChari)
    {
        *pusLenLimit    = 140;
    }
    else if (16 == ucBitNumInChari)
    {
        *pusLenLimit    = 70;
    }
    else
    {
        *pusLenLimit    = 160;
    }

    return;

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_EncodeMsgID
 功能描述  : encode MSG ID
 输入参数  :
            pstMsgId    : MSG_ID STRU
 输出参数  :
            pucMsgIdLen : 生成数据长度
            paucMsfIdData  : 生成数据内容

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_EncodeMsgID(
    TAF_XSMS_MSG_ID_STRU               *pstMsgId,           /* in */
    VOS_UINT8                          *pucMsgIdLen,        /* out */
    VOS_UINT8                          *paucMsfIdData       /* out */
)
{
    VOS_UINT8                           ucBitPos = 0;

    *pucMsgIdLen        = 5;

    paucMsfIdData[0]    = TAF_XSMS_BD_MESSAGE_IDENTIFIER;
    ucBitPos           += 8;

    paucMsfIdData[1]    = 3;
    ucBitPos           += 8;

    TAF_XSMS_PackBitToByte(paucMsfIdData,
                           pstMsgId->enMsgType,
                           4,
                           ucBitPos);

    ucBitPos           += 4;

    TAF_XSMS_PackBitToByte(paucMsfIdData,
                           pstMsgId->usMsgID & 0x00FF,
                           8,
                           ucBitPos);
    ucBitPos           += 8;

    TAF_XSMS_PackBitToByte(paucMsfIdData,
                           (pstMsgId->usMsgID & 0xFF00)>>8,
                           8,
                           ucBitPos);
    ucBitPos           += 8;

    TAF_XSMS_PackBitToByte(paucMsfIdData,
                           pstMsgId->ucIsHeadIndExist,
                           1,
                           ucBitPos);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_EncodeUserRspCode
 功能描述  : encode user response code
 输入参数  :
            ucUserResponseCode    : 失败原因值
 输出参数  :
            pucMsgIdLen : 生成数据长度
            paucMsfIdData  : 生成数据内容

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_EncodeUserRspCode(
    VOS_UINT8                           ucUserResponseCode, /* in */
    VOS_UINT8                          *pucRepCodeLen,      /* out */
    VOS_UINT8                          *pucRepCodeData      /* out */
)
{
    *pucRepCodeLen = 3;

    pucRepCodeData[0]   = TAF_XSMS_BD_USER_RESPONESE_CODE;
    pucRepCodeData[1]   = 1;
    pucRepCodeData[2]   = ucUserResponseCode;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_DecodeMsgId
 功能描述  : decode msg id
 输入参数  :

 输出参数  :


 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月4日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_DecodeMsgId(
    VOS_UINT32                          ulBearDataLen,
    VOS_UINT8                          *pucBearData,
    TAF_XSMS_MSG_ID_STRU               *pstMsgId
)
{
    /*
    para_id     8 bits
    para_len    8 bits
    msg_type    4 bits
    msg_id      16bits
    header_ind  1 bits
    rsv         3 bits
    */

    pstMsgId->enMsgType         = (TAF_XSMS_BD_MSG_TYPE_ENUM8)((pucBearData[2] & 0xf0) >> 4);
    pstMsgId->ucIsHeadIndExist  = VOS_FALSE;
    pstMsgId->usMsgID           = 0;
    pstMsgId->usMsgID          += ((pucBearData[2] & 0x0f) << 12);
    pstMsgId->usMsgID          += ( pucBearData[3]  << 4);
    pstMsgId->usMsgID          += ((pucBearData[4] & 0xf0) >> 4);

    return;
}



/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




