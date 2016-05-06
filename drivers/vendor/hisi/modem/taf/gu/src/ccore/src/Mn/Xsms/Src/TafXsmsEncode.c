/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsEncode.c
  版 本 号   : 初稿
  作    者   : j00304117
  生成日期   : 2014年10月31日
  功能描述   : 1X SMS(Short Message Service)编码
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月31日
    作    者   : j00304117
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafXsmsEncode.h"
#include  "TafAppXsmsInterface.h"
#include  "TafXsmsCtx.h"
#include  "TafXsmsUimProc.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_ENCODE_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_XSMS_PackBitToByte
 功能描述  : 把少于8个bit的值写入指定数组的指定bit位置上去
 输入参数  : ucValue:      需要写入的值
             ucBitNum:     需要写入的bit数，1-8bit
             usBitPos:     写入bit处于数组中的位置
 输出参数  : pucBuffer:    需要写入的数组的地址
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : j00304117
    修改内容   : 新生成函数

***************************************************************6**************/
VOS_VOID TAF_XSMS_PackBitToByte(
    VOS_UINT8                          *pucBuffer,
    VOS_UINT8                           ucValue,
    VOS_UINT8                           ucBitNum,
    VOS_UINT16                          usBitPos
)
{
    VOS_UINT16                          usTmpPos;
    VOS_UINT16                          usBits;
    VOS_UINT16                          usTmpData      = 0;
    VOS_UINT16                          usTmpOffset    = 0;
    VOS_UINT8                           aucTmpData[2]  = {0};

    /* 计算Byte 位置 */
    usTmpOffset     = (usBitPos + ucBitNum - 1) / 8;

    /* 计算bit位置 */
    usTmpPos        = usBitPos % TAF_XSMS_BIT_NUMBER_OF_BYTE;
    usBits          = TAF_XSMS_BIT_NUMBER_OF_BYTE - usTmpPos;

    /* 读取数组中的值放到临时变量 */
    aucTmpData[0]   = *(pucBuffer + usTmpOffset - 1);
    aucTmpData[1]   = *(pucBuffer + usTmpOffset);

    /*lint -e701*/
    /* 判断是否在同一个字节 */
    if (usBits >= ucBitNum)
    {
        usTmpData        = (0xff >> usTmpPos) & (0xff << (TAF_XSMS_BIT_NUMBER_OF_BYTE - (usTmpPos + ucBitNum)));
        aucTmpData[1]   &= ~usTmpData;
        aucTmpData[1]   |= (VOS_UINT8)(usTmpData & (ucValue << (usBits - ucBitNum)));
        *(pucBuffer + usTmpOffset) = aucTmpData[1];
    }
    else
    {
        /* 不在同一个字节，分两个字节写入 */
        usTmpData        = (0xff >> usTmpPos) & (0xff << (TAF_XSMS_BIT_NUMBER_OF_BYTE - (usTmpPos + usBits)));
        aucTmpData[0]   &= ~usTmpData;
        aucTmpData[0]   |= (VOS_UINT8)(usTmpData & (ucValue >> (ucBitNum - usBits)));
        *(pucBuffer + usTmpOffset - 1) = aucTmpData[0];

        usTmpData        = (VOS_UINT16)(0xff << (TAF_XSMS_BIT_NUMBER_OF_BYTE - (ucBitNum - usBits)));
        aucTmpData[1]   &= ~usTmpData;
        aucTmpData[1]   |= (VOS_UINT8)(usTmpData & (ucValue << (TAF_XSMS_BIT_NUMBER_OF_BYTE - (ucBitNum - usBits))));
        *(pucBuffer + usTmpOffset) = aucTmpData[1];
    }
    /*lint +e701*/

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_ReplaceMessageID
 功能描述  : 替换MessageID
 输入参数  : usMessageId:      新的MessageID的值
 输出参数  : pucBDStru:        需要发送的短消息的Ril结构体
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XSMS_ReplaceMessageID(
    TAF_XSMS_MESSAGE_STRU              *pucBDStru,
    VOS_UINT16                          usMessageId
)
{
    VOS_UINT8                           ucMsgIdHi;
    VOS_UINT8                           ucMsgIdLo;

    ucMsgIdHi = (VOS_UINT8)((usMessageId >> 8) & 0xff);
    ucMsgIdLo = (VOS_UINT8)(usMessageId & 0xff);

    TAF_XSMS_PackBitToByte(pucBDStru->aucBearerData, ucMsgIdHi, 8, 20);
    TAF_XSMS_PackBitToByte(pucBDStru->aucBearerData, ucMsgIdLo, 8, 28);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_FillTeleserviceID
 功能描述  : 编码TeleserviceID参数
 输入参数  : pstBDStru:      包含短信信息的结构体指针
 输出参数  : pucPos:         码流的地址偏移值
             pucTLRawData:   码流的首地址
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XSMS_FillTeleserviceID(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos
)
{
    VOS_UINT8                           ucTmpPos;

    ucTmpPos                  = *pucPos;

    pucTLRawData[ucTmpPos++]  = TAF_XSMS_TL_TELESERVICE_ID;
    pucTLRawData[ucTmpPos++]  = 0x02;
    pucTLRawData[ucTmpPos++]  = (VOS_UINT8)((pstBDStru->ulTeleserviceID >> 8) & 0xff);
    pucTLRawData[ucTmpPos++]  = (VOS_UINT8)(pstBDStru->ulTeleserviceID & 0xff);
    *pucPos                   = ucTmpPos;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_FillServiceCategory
 功能描述  : 编码ServiceCategory参数
 输入参数  : pstBDStru:      包含短信信息的结构体指针
 输出参数  : pucPos:         码流的地址偏移值
             pucTLRawData:   码流的首地址
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XSMS_FillServiceCategory(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos
)
{
    VOS_UINT8                           ucTmpPos;

    ucTmpPos                  = *pucPos;

    pucTLRawData[ucTmpPos++]  = TAF_XSMS_TL_SERVICR_CATEGORY;
    pucTLRawData[ucTmpPos++]  = 0x02;
    pucTLRawData[ucTmpPos++]  = (VOS_UINT8)((pstBDStru->ulServiceCategory >> 8) & 0xff);
    pucTLRawData[ucTmpPos++]  = (VOS_UINT8)pstBDStru->ulServiceCategory;
    *pucPos                   = ucTmpPos;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_FillAddress
 功能描述  : 编码Address参数
 输入参数  : pstAddr:      包含地址信息的结构体指针
 输出参数  : pucLen:       Address参数的长度
             pucTLRawData: 码流的地址
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XSMS_FillAddress(
    TAF_XSMS_ADDR_STRU                 *pstAddr,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucLen
)
{
    VOS_UINT16                          ulBitPos = 0;
    VOS_UINT8                           ucDigitMode;
    VOS_UINT8                           ucReserveSize;
    VOS_UINT32                          i;

    /* 写入Digit mode字段 */
    TAF_XSMS_PackBitToByte(pucTLRawData, pstAddr->enDigitMode, 1, ulBitPos);
    ulBitPos++;

    /* 写入Number mode字段 */
    TAF_XSMS_PackBitToByte(pucTLRawData, pstAddr->enNumberMode, 1, ulBitPos);
    ulBitPos++;

    /* 写入Number type和Number plan字段 */
    if (TAF_XSMS_DIGIT_MODE_8_BIT == pstAddr->enDigitMode)
    {
        ucDigitMode = 8;

        TAF_XSMS_PackBitToByte(pucTLRawData, pstAddr->enNumberType, 3, ulBitPos);
        ulBitPos += 3;

        if (TAF_XSMS_NUMBER_MODE_NOT_DATA_NETWORK == pstAddr->enNumberMode)
        {
            TAF_XSMS_PackBitToByte(pucTLRawData, pstAddr->enNumberPlan, 4, ulBitPos);
            ulBitPos += 4;
        }
    }
    else
    {
        ucDigitMode = 4;
    }

    /* 写入Address numbers字段 */
    TAF_XSMS_PackBitToByte(pucTLRawData, (VOS_UINT8)pstAddr->ulNumberOfDigits, 8, ulBitPos);
    ulBitPos += 8;

    /* 写入Address digits字段 */
    for (i = 0; i < pstAddr->ulNumberOfDigits; i++)
    {
        TAF_XSMS_PackBitToByte(pucTLRawData, pstAddr->aucDigits[i],  ucDigitMode, ulBitPos);
        ulBitPos += ucDigitMode;
    }

    /* 补全字节 */
    if (0 != ulBitPos % 8)
    {
        ucReserveSize = (VOS_UINT8)(8 - (ulBitPos % 8));
        TAF_XSMS_PackBitToByte(pucTLRawData, 0, ucReserveSize, ulBitPos);
        ulBitPos += ucReserveSize;
    }

    /* 写入参数长度 */
    *pucLen = (VOS_UINT8)(ulBitPos / 8);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_FillSubAddress
 功能描述  : 编码SubAddress参数
 输入参数  : pstSubAddr      包含子地址信息的结构体指针
             enStates        发送还是接收的消息
 输出参数  : pucPos          码流的地址偏移值
             pucTLRawData    码流的首地址
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XSMS_FillSubAddress(
    TAF_XSMS_SUB_ADDR_STRU             *pstSubAddr,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos,
    VOS_UINT8                           enStates
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucTmpPos;
    VOS_UINT16                          usBitPos;

    ucTmpPos = *pucPos;

    /* 判断是写目的地址还是源地址 */
    if ((TAF_XSMS_STATUS_REC_UNREAD == enStates)
        || (TAF_XSMS_STATUS_REC_READ == enStates))
    {
        pucTLRawData[ucTmpPos++] = TAF_XSMS_TL_ORIGIN_SUBADDR;
    }
    else
    {
        pucTLRawData[ucTmpPos++] = TAF_XSMS_TL_DEST_SUBADDR;
    }
    pucTLRawData[ucTmpPos++]  = pstSubAddr->ucNumberOfDigits + 2;

    usBitPos  = 0;

    /* 写入SubAddress type字段 */
    TAF_XSMS_PackBitToByte(pucTLRawData + ucTmpPos, pstSubAddr->enSubAddrType, 3, usBitPos);
    usBitPos += 3;

    /* 写入Odd字段 */
    TAF_XSMS_PackBitToByte(pucTLRawData + ucTmpPos, pstSubAddr->ucOdd, 1, usBitPos);
    usBitPos += 1;

    /* 写入Address numbers字段 */
    TAF_XSMS_PackBitToByte(pucTLRawData + ucTmpPos, pstSubAddr->ucNumberOfDigits, 8, usBitPos);
    usBitPos += 8;

    /* 写入Address digits字段 */
    for (ucIndex = 0; ucIndex < pstSubAddr->ucNumberOfDigits; ucIndex++)
    {
        TAF_XSMS_PackBitToByte(pucTLRawData + ucTmpPos,
                                pstSubAddr->aucDigits[ucIndex], 8, usBitPos);
        usBitPos += 8;
    }

    /* 补全字节 */
    TAF_XSMS_PackBitToByte(pucTLRawData + ucTmpPos, 0, 4, usBitPos);

    *pucPos  = ucTmpPos + pstSubAddr->ucNumberOfDigits + 2;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_FillBearerReplyOpiton
 功能描述  : 编码BearerReplyOpiton参数
 输入参数  : ucBearReplySeqNum:               ReplyOpiton的值
 输出参数  : pucPos:                          码流的地址偏移值
             pucTLRawData:                    码流的首地址
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XSMS_FillBearerReplyOpiton(
    VOS_UINT8                           ucBearReplySeqNum,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos
)
{
    VOS_UINT8                           ucTmpPos;

    ucTmpPos                 = *pucPos;
    pucTLRawData[ucTmpPos++] = TAF_XSMS_TL_BEARER_REPLY_OPTION;
    pucTLRawData[ucTmpPos++] = 1;

    /* 写入BearReplySeqNum字段 */
    TAF_XSMS_PackBitToByte(pucTLRawData + ucTmpPos, ucBearReplySeqNum, 6, 0);
    TAF_XSMS_PackBitToByte(pucTLRawData + ucTmpPos, 0, 2, 6);
    *pucPos += 3;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_FillBearerData
 功能描述  : 编码BearerData参数
 输入参数  : pstBDStru:             包含短信信息的结构体指针
 输出参数  : pucPos:                码流的地址偏移值
             pucTLRawData:          码流的首地址
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XSMS_FillBearerData(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos
)
{
    VOS_UINT8                           ucTmpPos;

    ucTmpPos                 = *pucPos;
    pucTLRawData[ucTmpPos++] = TAF_XSMS_TL_BERAER_DATA;
    pucTLRawData[ucTmpPos++] = (VOS_UINT8)pstBDStru->ulBearerDataLen;

    PS_MEM_CPY(pucTLRawData + ucTmpPos, pstBDStru->aucBearerData, pstBDStru->ulBearerDataLen);
    *pucPos = (VOS_UINT8)(pstBDStru->ulBearerDataLen & 0xff) + ucTmpPos;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_GetP2PDBMStru
 功能描述  : 输入tpdu得到点对点DMB结构体(外部调用)
 输入参数  : pstBDStru:                 包含短信信息的结构体指针
             usMessageIdentifier:       需要写入DBM结构体Message Identifier
             ucBearerReplyOptionSeq:    需要写入DMB结构体的Bearer Reply OptionSeq
             enStates:                  发送还是接收的消息
 输出参数  : pstDBMStru:                需要输出的DBM结构体
 返 回 值  : VOS_ERR                    编码失败
             VOS_OK                     编码成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_GetP2PDBMStru(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT16                          usMessageIdentifier,
    VOS_UINT8                           ucBearerReplyOptionSeq,
    VOS_UINT8                           enStates,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDBMStru,
    VOS_UINT32                          ulIsReplySeqNeed
)
{
    VOS_UINT8                           aucTLRawBuffer[TAF_XSMS_MAX_DBM_SIZE];
    VOS_UINT8                           ucNumFields;

    TAF_XSMS_TranslatePlusToNum(&pstBDStru->stAddr);

    if (VOS_ERR == TAF_XSMS_EncodeBearDataStruToP2PRaw(pstBDStru,
                                                       aucTLRawBuffer,
                                                       &ucNumFields,
                                                       ucBearerReplyOptionSeq,
                                                       usMessageIdentifier,
                                                       enStates,
                                                       ulIsReplySeqNeed))
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_GetP2PDBMStru:Data Burst Message encode failed");

        return VOS_ERR;
    }


    pstDBMStru->ucBurstType = DBM_SMS_TYPE;
    pstDBMStru->ucMsgNum    = 1;
    pstDBMStru->ucNumMsgs   = 1;
    pstDBMStru->ucNumFields = ucNumFields;
    PS_MEM_CPY(pstDBMStru->aucData, aucTLRawBuffer, ucNumFields);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_GetAckDBMStru
 功能描述  : 输入目的地址和Cause Code得到DBM结构体(外部调用)
 输入参数  : pstAddrStru:           需要写入DBM结构体目的地址结构体
             pstCauseCodeStru:      需要写入DBM结构体的pstCauseCode结构体
 输出参数  : pstDBMStru:            需要输出的DBM结构体
 返 回 值  : VOS_ERR                编码失败
             VOS_OK                 编码成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_GetAckDBMStru(
    TAF_XSMS_ADDR_STRU                 *pstAddrStru,
    TAF_XSMS_CAUSE_CODE_STRU           *pstCauseCodeStru,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDBMStru
)
{
    VOS_UINT8                           aucTLRawBuffer[TAF_XSMS_MAX_DBM_SIZE];
    VOS_UINT8                           ucNumFields;

    if (VOS_ERR == TAF_XSMS_EncodeAckMsg(pstAddrStru,
                                         pstCauseCodeStru,
                                         aucTLRawBuffer,
                                         &ucNumFields))
    {

        TAF_XSMS_ERROR_LOG("TAF_XSMS_GetAckDBMStru:Ack message encode failed");

        return VOS_ERR;
    }

    pstDBMStru->ucBurstType = DBM_SMS_TYPE;
    pstDBMStru->ucMsgNum    = 1;
    pstDBMStru->ucNumMsgs   = 1;
    pstDBMStru->ucNumFields = ucNumFields;
    PS_MEM_CPY(pstDBMStru->aucData, aucTLRawBuffer, ucNumFields);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : TAF_XSMS_EncodeBearDataStruToP2PRaw
 功能描述  : 把RIL下发的结构体转换成点对点短信的码流(外部调用)
 输入参数  : pstBDStru:                    被编码成TL层码流的结构体
             ucBearerReplyOptionSeq:       短信中实际需要使用的Bearer Reply Option Sequence
             usMessageIdentifier:          短信中实际需要使用的Message Identifier
             enStates:                     发送还是接收的消息
 输出参数  : pucTLRawData:                 TL层码流指针，编码好的数据写入该数组
             pucEncodedLen:                码流长度
 返 回 值  : VOS_OK                        编码成功
             VOS_ERR                       编码失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_EncodeBearDataStruToP2PRaw(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucEncodedLen,
    VOS_UINT8                           ucBearerReplyOptionSeq,
    VOS_UINT16                          usMessageIdentifier,
    VOS_UINT8                           enStates,
    VOS_UINT32                          ulIsReplySeqNeeded
)
{
    VOS_UINT8                           ucPos;

    TAF_XSMS_ReplaceMessageID(pstBDStru, usMessageIdentifier);
    if (VOS_ERR == (TAF_XSMS_EncodeBearDataStruToSimRaw(pstBDStru,
                                                        pucTLRawData,
                                                        ucBearerReplyOptionSeq,
                                                        &ucPos,
                                                        enStates,
                                                        ulIsReplySeqNeeded)))
    {

        TAF_XSMS_ERROR_LOG("TAF_XSMS_EncodeBearDataStruToP2PRaw:Point to point message encode failed");

        return VOS_ERR;
    }

    *pucEncodedLen = ucPos;

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_EncodeBearDataStruToSimRaw
 功能描述  : 把RIL下发的结构体转换成需要写入UIM卡的点对点短信的码流(外部调用)
 输入参数  : pstBDStru:                   被编码成TL层码流的结构体
             ucBearerReplyOptionSeq:      短信中实际需要使用的Bearer Reply Option Sequence
             usMessageIdentifier:         短信中实际需要使用的Message Identifier
             enStates:                    发送还是接收的消息
 输出参数  : pucTLRawData:                TL层码流指针，编码好的数据写入该数组
             pucEncodedLen:               总共编码的了多少字节
 返 回 值  : VOS_OK                       编码成功
             VOS_ERR                      编码失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_EncodeBearDataStruToSimRaw(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                           ucBearerReplyOptionSeq,
    VOS_UINT8                          *pucEncodedLen,
    VOS_UINT8                           enStates,
    VOS_UINT32                          ulIsReplySeqNeeded
)
{
    VOS_UINT8                           ucPos;
    VOS_UINT8                           ucLen;

    ucPos  = 0;

    /* 写TELESERVICE_ID字段 */
    pucTLRawData[ucPos++] = TAF_XSMS_TL_P2P_MSG;

    /* 写TELESERVICE_ID字段 */
    TAF_XSMS_FillTeleserviceID(pstBDStru, pucTLRawData, &ucPos);

    /* 写ServiceCategory字段 */
    if (VOS_TRUE == pstBDStru->bIsServicePresent)
    {
        TAF_XSMS_FillServiceCategory(pstBDStru, pucTLRawData, &ucPos);
    }

    /* 写DstAddr字段 */
    if ((0 != pstBDStru->stAddr.ulNumberOfDigits)
    &&  (TAF_XSMS_ADDRESS_MAX > pstBDStru->stAddr.ulNumberOfDigits))
    {
        /* 判断是写目的地址还是源地址 */
        if ((TAF_XSMS_STATUS_REC_UNREAD == enStates)
            || (TAF_XSMS_STATUS_REC_READ == enStates))
        {
            pucTLRawData[ucPos++] = TAF_XSMS_TL_ORIGIN_ADDR;
        }
        else
        {
            pucTLRawData[ucPos++] = TAF_XSMS_TL_DEST_ADDR;
        }
        TAF_XSMS_FillAddress(&pstBDStru->stAddr, pucTLRawData + ucPos + 1, &ucLen);
        pucTLRawData[ucPos++] = ucLen;
        ucPos                += ucLen;
    }
    else
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_EncodeBearDataStruToSimRaw:Point to point message missing mandatory paramter");

        return VOS_ERR;
    }

    /* 写DstSubAddr字段 */
    if (TAF_XSMS_ADDRESS_MAX < pstBDStru->stSubAddr.ucNumberOfDigits)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_EncodeBearDataStruToSimRaw:stSubAddr.ucNumberOfDigits > 36");

        return VOS_ERR;
    }

    if (0 != pstBDStru->stSubAddr.ucNumberOfDigits)
    {
        TAF_XSMS_FillSubAddress(&pstBDStru->stSubAddr, pucTLRawData, &ucPos, enStates);
    }

    /* 写BearReplyOption字段 */
    if (VOS_TRUE == ulIsReplySeqNeeded)
    {
        TAF_XSMS_FillBearerReplyOpiton(ucBearerReplyOptionSeq, pucTLRawData, &ucPos);
    }

    /* 写BearData字段 */
    if (TAF_XSMS_TPDU_LEN_MAX < (ucPos + pstBDStru->ulBearerDataLen))
    {

        TAF_XSMS_ERROR_LOG("TAF_XSMS_EncodeBearDataStruToSimRaw:Point to point message Bear Data too long");

        return VOS_ERR;
    }

    /* 写BearData字段 */
    if (0 != pstBDStru->ulBearerDataLen)
    {
        TAF_XSMS_FillBearerData(pstBDStru, pucTLRawData, &ucPos);
    }

    *pucEncodedLen = ucPos;

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_EncodeAckMsg
 功能描述  : 编码TL层的ACK
 输入参数  : pstDestAddr:          包含目的地址信息的结构体指针
             pstCauseCode:         包含CauseCode信息的结构体指针
 输出参数  : pucTLRawData:         码流的地址
             pucCodedLen:          码流的长度
 返 回 值  : VOS_OK                编码成功
             VOS_ERR               编码失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_EncodeAckMsg(
    TAF_XSMS_ADDR_STRU                 *pstDestAddr,
    TAF_XSMS_CAUSE_CODE_STRU           *pstCauseCode,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucCodedLen
)
{
    VOS_UINT8                           ucPos = 0;
    VOS_UINT8                           ucLen;

    /* 写入SMS ID字段 */
    pucTLRawData[ucPos++] = TAF_XSMS_TL_ACK_MSG;

    /* 写入DestAddr字段 */
    if ((0 != pstDestAddr->ulNumberOfDigits)
    &&  (TAF_XSMS_ADDRESS_MAX > pstDestAddr->ulNumberOfDigits))
    {
        pucTLRawData[ucPos++] = TAF_XSMS_TL_DEST_ADDR;
        TAF_XSMS_FillAddress(pstDestAddr, pucTLRawData + ucPos + 1, &ucLen);
        pucTLRawData[ucPos++] = ucLen;
        ucPos                += ucLen;
    }
    else
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_EncodeAckMsg:Ack message missing mandatory paramter");

        return VOS_ERR;
    }

    /* 写入Cause code字段 */
    pucTLRawData[ucPos++] = TAF_XSMS_TL_CAUSE_CODE;
    if (TAF_XSMS_TL_CAUSECODE_NONE != pstCauseCode->enErrorClass)
    {
        pucTLRawData[ucPos++] = 2;
    }
    else
    {
        pucTLRawData[ucPos++] = 1;
    }

    pucTLRawData[ucPos++] = ((pstCauseCode->ucReplySeq << 2) & 0xfc) | ((pstCauseCode->enErrorClass & 0x03));

    if (TAF_XSMS_TL_CAUSECODE_NONE != pstCauseCode->enErrorClass)
    {
        pucTLRawData[ucPos++] = pstCauseCode->enCauseCode;
    }

    /* 写入码流长度 */
    *pucCodedLen = ucPos;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_EncodeAuth
 功能描述  : 编码鉴权数组
 输入参数  : pstDestinationAddr:    需要发送消息的设备的目的地址
 输出参数  : pucAuthData:           输出的鉴权数组
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XSMS_EncodeAuth(
    TAF_XSMS_ADDR_STRU                 *pstDestinationAddr,
    VOS_UINT8                          *pucAuthData
)
{
    VOS_UINT8                           aucISMS_S1[3] = {0};
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucTmp;
    VOS_UINT8                           aucNum[6] = {0};
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAuth;


    pstInitCtrlInfoAuth = TAF_XSMS_GetInitCtrlInfoAddr();
    PS_MEM_CPY(aucISMS_S1, pstInitCtrlInfoAuth->aucImsi + 2, 3);

    for (ucIndex = 0; ucIndex < DIGITS_OF_AUTN; ucIndex++)
    {
        TAF_XSMS_TL_UnpackByteToBit(aucISMS_S1, aucNum + ucIndex, ucIndex * 4, 4);
    }

    /* 先把ISMI_S1赋值给pucAuthData */
    ucTmp = (VOS_UINT8)pstDestinationAddr->ulNumberOfDigits;

    /* 根据号码的编码方式写临时数组的值 */
    for (ucIndex = DIGITS_OF_AUTN; ucIndex != 0; ucIndex--)
    {
        /* 8bit编码方式 */
        if (TAF_XSMS_DIGIT_MODE_8_BIT == pstDestinationAddr->enDigitMode)
        {
            /* 8bit编码方式把值看成无符号数，取16余，然后按照DTMF编码 */
            if (0 != (--ucTmp))
            {
                aucNum[ucIndex - 1] = pstDestinationAddr->aucDigits[ucTmp] % 16;
                if (0 == aucNum[ucIndex - 1])
                {
                    aucNum[ucIndex - 1] = 0x0a;
                }
            }
            else
            {
                aucNum[ucIndex - 1] = pstDestinationAddr->aucDigits[ucTmp] % 16;
                if (0 == aucNum[ucIndex - 1])
                {
                    aucNum[ucIndex - 1] = 0x0a;
                }
                break;

            }
        }
        else
        {
            /* 4bit  DTMF 编码方式 */
            if (0 != (--ucTmp))
            {
                aucNum[ucIndex - 1] = pstDestinationAddr->aucDigits[ucTmp];
            }
            else
            {
                aucNum[ucIndex - 1] = pstDestinationAddr->aucDigits[ucTmp];
                break;
            }
        }
    }

    /* 把鉴权内容写入鉴权数组中 */
    for (ucIndex = 0; ucIndex < DIGITS_OF_AUTN; ucIndex++)
    {
        TAF_XSMS_PackBitToByte(pucAuthData, aucNum[ucIndex], 4, ucIndex * 4);
    }

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_EncodeRelativeValidPeriod
 功能描述  : 编码ValidPeriod
 输入参数  :
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月14日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XSMS_EncodeRelativeValidPeriod
(
    VOS_UINT8                           ucTimeValue, /* timeLen = (ucTimeValue+1)*5 */
    VOS_UINT8                          *pucEncodeLen,
    VOS_UINT8                          *pucData
)
{
    *pucEncodeLen = 3;

    /*  para_id     8 bits
        para_len    8 bits
        valid_pro
    */

    /* timeLen = (ucTimeValue+1)*5 */

    pucData[0] = TAF_XSMS_BD_VALIDITY_PERIOD_RELATIVE;
    pucData[1] = 0x01;
    pucData[2] = ucTimeValue;

    return;

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_EncodeRelativeValidPeriod
 功能描述  : 编码ValidPeriod
 输入参数  :
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月14日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XSMS_EncodePrioIndicator
(
    TAF_XSMS_BD_SMS_PRIO_ENUM_UINT8     enPrio,
    VOS_UINT8                          *pucEncodeLen,
    VOS_UINT8                          *pucData
)
{
    *pucEncodeLen = 3;

    /*  para_id     8 bits
        para_len    8 bits
        prio        2 bits
    */

    /* timeLen = (ucTimeValue+1)*5 */

    pucData[0] = TAF_XSMS_BD_PRIORITY_INDICATOR;
    pucData[1] = 0x01;
    pucData[2] = (enPrio << 6) & 0xC0;

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_EncodeXcallMsgBearDataByContext
 功能描述  : MO Idle状态下收到XCALL下发的命令发送短信的处理流程
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_EncodeXcallMsgBearDataByContext
(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usDataLen,
    TAF_XSMS_MESSAGE_STRU              *pstXsmsMsg
)
{
    TAF_XSMS_BD_MSG_USER_DATA_STRU      stUserData;
    VOS_UINT8                           aucEncodedData[256] = {0};
    VOS_UINT8                           ucEncodeDataLen     = 0;
    TAF_XSMS_MSG_ID_STRU                stMsgId;

    /* 标准的MSG_ID 结构体 */
    stMsgId.enMsgType           = TAF_XSMS_BD_MSG_TYPE_SUBMIT;
    stMsgId.ucIsHeadIndExist    = VOS_FALSE;
    stMsgId.usMsgID             = 0;

    /* 组成标准USER DATA 结构 */
    PS_MEM_SET(&stUserData, 0, sizeof(TAF_XSMS_BD_MSG_USER_DATA_STRU));

    stUserData.enMsgCodeType = TAF_XSMS_USER_DATA_MSG_ENCODE_OCTET;

    if (TAF_XSMS_BD_PURE_CONTEXT_MAX_LEN_8 < usDataLen)
    {
        return VOS_ERR;
    }

    stUserData.ucNumFields  = (VOS_UINT8)usDataLen;

    PS_MEM_CPY(stUserData.aucUserData, pucData, usDataLen);

    /* 生成BEAR DATA */
    /* 生成MSG ID */
    TAF_XSMS_EncodeMsgID(&stMsgId,
                         &ucEncodeDataLen,
                         aucEncodedData);

    PS_MEM_CPY(pstXsmsMsg->aucBearerData + pstXsmsMsg->ulBearerDataLen,
               aucEncodedData,
               ucEncodeDataLen);

    pstXsmsMsg->ulBearerDataLen += ucEncodeDataLen;

    /* 生成USER DATA */
    TAF_XSMS_EncodeUserData(&stUserData,
                            &ucEncodeDataLen,
                            aucEncodedData);

    PS_MEM_CPY(pstXsmsMsg->aucBearerData + pstXsmsMsg->ulBearerDataLen,
               aucEncodedData,
               ucEncodeDataLen);

    pstXsmsMsg->ulBearerDataLen += ucEncodeDataLen;

    /* ENCODE RELATIVE VALID PERIOD */
    TAF_XSMS_EncodeRelativeValidPeriod(0, &ucEncodeDataLen, aucEncodedData);

    PS_MEM_CPY(pstXsmsMsg->aucBearerData + pstXsmsMsg->ulBearerDataLen,
               aucEncodedData,
               ucEncodeDataLen);

    pstXsmsMsg->ulBearerDataLen += ucEncodeDataLen;

    /* ENCODE prio */
    TAF_XSMS_EncodePrioIndicator(TAF_XSMS_BD_SMS_PRIO_EMERGENCY,
                                 &ucEncodeDataLen,
                                 aucEncodedData);

    PS_MEM_CPY(pstXsmsMsg->aucBearerData + pstXsmsMsg->ulBearerDataLen,
               aucEncodedData,
               ucEncodeDataLen);

    pstXsmsMsg->ulBearerDataLen += ucEncodeDataLen;

    return VOS_OK;

}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



