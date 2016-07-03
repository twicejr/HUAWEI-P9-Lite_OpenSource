

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "TafStdlib.h"
#include "MnErrorCode.h"
#include "MnMsgApi.h"
#include "MnCallApi.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_STD_LIB_C

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/
LOCAL VOS_UINT8 f_aucMsgAsciiSfxDefAlpha[TAF_STD_MAX_GSM7BITDEFALPHA_NUM] =
{
    '@',  163,   '$',  165,  232,  233,  249,  236,  242,  199,  0x0a, 216,  248,  0x0d, 197,  229,
    0xff, '_',   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 198,  230,  223,  201,
    ' ',  '!',   '"',  '#',  164,  '%',  '&',  0x27, '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
    '0',  '1',   '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
    161,  'A',   'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
    'P',  'Q',   'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  196,  214,  209,  220,  167,
    191,  'a',   'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'o',
    'p',  'q',   'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z',  228,  246,  241,  252,  224
};

/*lint -save -e958 */


/* 从1980年开始，以四年为单位，每年的天数 */
LOCAL VOS_UINT16 g_ausTafStdDaysElapsedOfALeapYearSetTab[] = {
  /* 年 0 (闰年) */  0,
  /* 年 1        */  366,
  /* 年 2        */  366+365,
  /* 年 3        */  366+365+365,
  /* 单元周期年  */  366+365+365+365
};

/* 平年中每月的天数 */
LOCAL VOS_UINT16 g_ausTafStdNormMonthTab[] = {
  /* ---    */ 0,
  /* 一月   */ 31,
  /* 二月   */ 31+28,
  /* 三月   */ 31+28+31,
  /* 四月   */ 31+28+31+30,
  /* 五月   */ 31+28+31+30+31,
  /* 六月   */ 31+28+31+30+31+30,
  /* 七月   */ 31+28+31+30+31+30+31,
  /* 八月   */ 31+28+31+30+31+30+31+31,
  /* 九月   */ 31+28+31+30+31+30+31+31+30,
  /* 十月   */ 31+28+31+30+31+30+31+31+30+31,
  /* 十一月 */ 31+28+31+30+31+30+31+31+30+31+30,
  /* 十二月 */ 31+28+31+30+31+30+31+31+30+31+30+31
};

/* 闰年中每月的天数 */
LOCAL VOS_UINT16 g_ausTafStdLeapMonthTab[] = {
  /* ---    */ 0,
  /* 一月   */ 31,
  /* 二月   */ 31+29,
  /* 三月   */ 31+29+31,
  /* 四月   */ 31+29+31+30,
  /* 五月   */ 31+29+31+30+31,
  /* 六月   */ 31+29+31+30+31+30,
  /* 七月   */ 31+29+31+30+31+30+31,
  /* 八月   */ 31+29+31+30+31+30+31+31,
  /* 九月   */ 31+29+31+30+31+30+31+31+30,
  /* 十月   */ 31+29+31+30+31+30+31+31+30+31,
  /* 十一月 */ 31+29+31+30+31+30+31+31+30+31+30,
  /* 十二月 */ 31+29+31+30+31+30+31+31+30+31+30+31
};


/*****************************************************************************
  6 函数定义
*****************************************************************************/

VOS_UINT32 TAF_STD_Itoa(
    VOS_UINT32                          ulDigit,
    VOS_CHAR                           *pcDigitStr,
    VOS_UINT32                         *pulDigitStrLength
)
{
    VOS_INT32                           lCharNum;

    lCharNum = sprintf(pcDigitStr, "%d", (VOS_INT)ulDigit);/*lint !e586*/

    *pulDigitStrLength = (VOS_UINT32)lCharNum;

    return VOS_TRUE;
}



VOS_UINT32 TAF_STD_AsciiNum2HexString(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                         *pusSrcLen
)
{
    VOS_UINT16                          usChkLen;
    VOS_UINT8                           ucTmp;
    VOS_UINT8                           ucLeft;
    VOS_UINT16                          usSrcLen;
    VOS_UINT8                          *pucDst = VOS_NULL_PTR;

    usChkLen        = 0;
    ucTmp           = 0;
    ucLeft          = 0;
    usSrcLen        = *pusSrcLen;
    pucDst          = pucSrc;

    /* 如果是奇数个半字节则返回错误 */
    if (0 != (usSrcLen % 2))
    {
        return VOS_FALSE;
    }

    while (usChkLen < usSrcLen)
    {
        /* the number is 0-9 */
        if(isdigit(pucSrc[usChkLen]))
        {
            ucLeft = pucSrc[usChkLen] - '0';
        }
        /* the number is a-f */
        else if( (pucSrc[usChkLen] >= 'a') && (pucSrc[usChkLen] <= 'f') )
        {
            ucLeft = (pucSrc[usChkLen] - 'a') + 0x0a;
        }
        /* the number is A-F */
        else if( (pucSrc[usChkLen] >= 'A') && (pucSrc[usChkLen] <= 'F') )
        {
            ucLeft = (pucSrc[usChkLen] - 'A') + 0x0a;
        }
        else
        {
            return VOS_FALSE;
        }

        pucDst[ucTmp] = 0xf0 & (ucLeft << 4);
        usChkLen += 1;

        /* the number is 0-9 */
        if(isdigit(pucSrc[usChkLen]))
        {
            pucDst[ucTmp] |= pucSrc[usChkLen] - '0';
        }
        /* the number is a-f */
        else if( (pucSrc[usChkLen] >= 'a') && (pucSrc[usChkLen] <= 'f') )
        {
            pucDst[ucTmp] |= (pucSrc[usChkLen] - 'a') + 0x0a;
        }
        /* the number is A-F */
        else if( (pucSrc[usChkLen] >= 'A') && (pucSrc[usChkLen] <= 'F') )
        {
            pucDst[ucTmp] |= (pucSrc[usChkLen] - 'A') + 0x0a;
        }
        else
        {
            return VOS_FALSE;
        }

        usChkLen += 1;
        ucTmp += 1;
    }

    *pusSrcLen = usSrcLen / 2;

    return VOS_TRUE;
}


VOS_UINT16 TAF_STD_HexAlpha2AsciiString(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen,
    VOS_UINT8                          *pucDst
)
{
    VOS_UINT16                          usLen;
    VOS_UINT16                          usChkLen;
    VOS_UINT8                           ucHigh;
    VOS_UINT8                           ucLow;
    VOS_UINT8                          *pucWrite = VOS_NULL_PTR;
    VOS_UINT8                          *pucRead = VOS_NULL_PTR;

    pucWrite = pucDst;
    pucRead  = pucSrc;
    usLen    = 0;
    usChkLen = 0;
    ucHigh   = 0;
    ucLow    = 0;

    /* 扫完整个字串 */
    /*lint -e961*/
    while ( usChkLen++ < usSrcLen )
    {
        ucHigh = 0x0F & (*pucRead >> 4);
        ucLow  = 0x0F & *pucRead;

        usLen += 2;    /* 记录长度 */

        if (0x09 >= ucHigh)   /* 0-9 */
        {
            *pucWrite++ = ucHigh + 0x30;
        }
        else if (0x0A <= ucHigh)    /* A-F */
        {
            *pucWrite++ = ucHigh + 0x37;
        }
        else
        {

        }

        if (0x09 >= ucLow)   /* 0-9 */
        {
            *pucWrite++ = ucLow + 0x30;
        }
        else if (0x0A <= ucLow)    /* A-F */
        {
            *pucWrite++ = ucLow + 0x37;
        }
        else
        {

        }

        /* 下一个字符 */
        pucRead++;
    }
    /*lint +e961*/

    return usLen;
}

/* MN_UnPack7Bit从MnMsgDecode.c移到本文件，更名为TAF_STD_UnPack7Bit */
/* MN_Pack7Bit从MnMsgEncode.c移到本文件，更名为TAF_STD_Pack7Bit */


VOS_UINT32  TAF_STD_UnPack7Bit(
    const VOS_UINT8                     *pucOrgChar,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucFillBit,
    VOS_UINT8                           *pucUnPackedChar
)
{
    /*存放字节地址*/
    VOS_UINT32                          ulPos = 0;
     /*存放位偏移*/
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          ulLoop;

    if ((VOS_NULL_PTR == pucOrgChar)
     || (VOS_NULL_PTR == pucUnPackedChar))
    {
        return VOS_ERR;
    }

    /*根据协议23040 9.2.3.24 UDHL和UDH后面是Fill Bits和SM，去掉Fill Bits后就是SM(Unit: Septet),可以获得SM中包含字符个数*/
    ulOffset = ucFillBit % 8;

    /*第一步，移出当前无效的偏移位ulOffset，得到字符的低(8 - ulOffset)位，
      第二步，若(8 - ulOffset)小于7位，需要从下一个OCTET中获取高(7 - (8 - ulOffset))位
      第三步，获取下一个数据源的下标(ulPos)和需要去除的数据位(偏移位ulOffset)*/
    for (ulLoop = 0; ulLoop < ulLen; ulLoop++)
    {
        pucUnPackedChar[ulLoop] = (VOS_UINT8)(pucOrgChar[ulPos] >> ulOffset);
        if (ulOffset > 1)
        {
            /*lint -e701*/
            pucUnPackedChar[ulLoop] |= (VOS_UINT8)((pucOrgChar[ulPos + 1UL] << (8 - ulOffset)) & TAF_STD_7BIT_MASK);
            /*lint +e701*/
        }
        else
        {
            pucUnPackedChar[ulLoop] &= TAF_STD_7BIT_MASK;
        }

        ulPos   += (ulOffset + 7) / 8;
        ulOffset = (ulOffset + 7) % 8;
    }

    return VOS_OK;
}


VOS_UINT32  TAF_STD_Pack7Bit(
    const VOS_UINT8                     *pucOrgChar,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucFillBit,
    VOS_UINT8                           *pucPackedChar,
    VOS_UINT32                          *pulLen
)
{
    /*存放字节地址*/
    VOS_UINT32                          ulPos = 0;
    /*存放位偏移*/
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          ulLoop;

    if ((VOS_NULL_PTR == pucOrgChar)
     || (VOS_NULL_PTR == pucPackedChar)
     || (VOS_NULL_PTR == pulLen))
    {
        return VOS_ERR;
    }

    *pulLen = (VOS_UINT32)((((ulLen * 7) + ucFillBit) + 7) / 8);

    ulOffset = ucFillBit % 8;

    /*bit 7   6   5   4   3   2   1   0 */
    /*    |digit1L|   |---ulOffset1---| */ /*左移ulOffset1位*/
    /*                |(0)  digit1H   | */ /*右移(8-ulOffset1位)*/
    /*    |-digit2L-  |   |-ulOffset2-| */ /*偏移量为(8-1+ulOffset1)%8*/

    /*第一步，空出当前已经填充的偏移位ulOffset，并从数据源中取出一个OCTET填充高(8 - ulOffset)位，
      第二步，若(8 - ulOffset)小于7位，需要将当前数据源字符余下高(7 - (8 - ulOffset))位填充到目的数据的下一个OCTET中
      第三步，获取下一个目标数据的下标(ulPos)和已经填充的数据位(偏移位ulOffset)*/
    for (ulLoop = 0; ulLoop < ulLen; ulLoop++)
    {
        if ((pucOrgChar[ulLoop] & (~TAF_STD_7BIT_MASK)) != 0)
        {
            return VOS_ERR;
        }

        pucPackedChar[ulPos] |= (VOS_UINT8)((VOS_UINT32)(pucOrgChar[ulLoop] & TAF_STD_7BIT_MASK) << ulOffset);
        if (ulOffset > 1)
        {
            pucPackedChar[ulPos + 1UL] = (VOS_UINT8)((pucOrgChar[ulLoop] & TAF_STD_7BIT_MASK) >> (8 - ulOffset));
        }

        ulPos   += (ulOffset + 7) / 8;
        ulOffset = (ulOffset + 7) % 8;
    }

    return VOS_OK;
}



VOS_UINT32  TAF_STD_ConvertBcdNumberToAscii(
    const VOS_UINT8                    *pucBcdNumber,
    VOS_UINT8                           ucBcdLen,
    VOS_CHAR                           *pcAsciiNumber
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucBcdCode;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pucBcdNumber)
     || (VOS_NULL_PTR == pcAsciiNumber))
    {
        return MN_ERR_NULLPTR;
    }

    /*整理号码字符串，去除无效的0XFF数据*/
    while (ucBcdLen > 1)
    {
        if (0xFF == pucBcdNumber[ucBcdLen - 1])
        {
            ucBcdLen--;
        }
        else
        {
            break;
        }
    }

    /*判断pucBcdAddress所指向的字符串的最后一个字节的高位是否为1111，
    如果是，说明号码位数为奇数，否则为偶数*/
    if ((pucBcdNumber[ucBcdLen - 1] & 0xF0) == 0xF0)
    {
        ucLen = (VOS_UINT8)((ucBcdLen * 2) - 1);
    }
    else
    {
        ucLen = (VOS_UINT8)(ucBcdLen * 2);
    }

    /*解析号码*/
    for (ucLoop = 0; ucLoop < ucLen; ucLoop++)
    {
        /*判断当前解码的是奇数位号码还是偶数位号码，从0开始，是偶数*/
        if (1 == (ucLoop % 2))
        {
            /*如果是奇数位号码，则取高4位的值*/
            ucBcdCode = ((pucBcdNumber[(ucLoop / 2)] >> 4) & 0x0F);
        }
        else
        {
            /*如果是偶数位号码，则取低4位的值*/
            ucBcdCode = (pucBcdNumber[(ucLoop / 2)] & 0x0F);
        }

        /*将二进制数字转换成Ascii码形式*/
        ulRet = TAF_STD_ConvertBcdCodeToAscii(ucBcdCode, &(pcAsciiNumber[ucLoop]));
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
    }

    pcAsciiNumber[ucLoop] = '\0';      /*字符串末尾为0*/

    return MN_ERR_NO_ERROR;
}


VOS_UINT32  TAF_STD_ConvertBcdCodeToAscii(
    VOS_UINT8                           ucBcdCode,
    VOS_CHAR                           *pcAsciiCode
)
{
    VOS_CHAR                            cAsciiCode;

    if (VOS_NULL_PTR == pcAsciiCode)
    {
        return MN_ERR_NULLPTR;
    }

    if (ucBcdCode <= 0x09)
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x30);
    }
    else if (0x0A == ucBcdCode)
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x20);    /*字符'*'*/
    }
    else if (0x0B == ucBcdCode)
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x18);    /*字符'#'*/
    }
    else if ((0x0C == ucBcdCode)
          || (0x0D == ucBcdCode)
          || (0x0E == ucBcdCode))
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x55);    /*字符'a', 'b', 'c'*/
    }
    else
    {
        return MN_ERR_INVALID_BCD;
    }

    *pcAsciiCode = cAsciiCode;

    return MN_ERR_NO_ERROR;
}


VOS_UINT32  TAF_STD_ConvertAsciiNumberToBcd(
    const VOS_CHAR                     *pcAsciiNumber,
    VOS_UINT8                          *pucBcdNumber,
    VOS_UINT8                          *pucBcdLen
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucBcdCode;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pcAsciiNumber)
     || (VOS_NULL_PTR == pucBcdNumber)
     || (VOS_NULL_PTR == pucBcdLen))
    {
        return MN_ERR_NULLPTR;
    }

    for (ucLoop = 0; pcAsciiNumber[ucLoop] != '\0'; ucLoop++)
    {
        ulRet = TAF_STD_ConvertAsciiCodeToBcd(pcAsciiNumber[ucLoop], &ucBcdCode);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }

        /*将当前需要填入的空间清0*/
        pucBcdNumber[(ucLoop / 2)] &= ((ucLoop % 2) == 1) ? 0x0F : 0xF0;

        /*将数字填入相应的空间*/
        pucBcdNumber[(ucLoop / 2)] |= (((ucLoop % 2) == 1) ? ((ucBcdCode << 4) & 0xF0) : (ucBcdCode & 0x0F));
    }

    /*如果长度为奇数，则最后一个字符需要填 F */
    if (1 == (ucLoop % 2))
    {
        pucBcdNumber[(ucLoop / 2)] |= 0xF0;
    }

    *pucBcdLen = (ucLoop + 1) / 2;

    return MN_ERR_NO_ERROR;
}


VOS_UINT32 TAF_STD_ConvertAsciiAddrToBcd(
    MN_MSG_ASCII_ADDR_STRU             *pstAsciiAddr,
    MN_MSG_BCD_ADDR_STRU               *pstBcdAddr
)
{
    VOS_UINT32 ulRet;

    if ((VOS_NULL_PTR == pstAsciiAddr)
     || (VOS_NULL_PTR == pstBcdAddr))
    {
        return MN_ERR_NULLPTR;
    }

    MN_GET_ADDRTYPE(pstBcdAddr->addrType,
                    pstAsciiAddr->enNumType,
                    pstAsciiAddr->enNumPlan);

    ulRet = TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR *)(pstAsciiAddr->aucAsciiNum),
                              pstBcdAddr->aucBcdNum,
                              &pstBcdAddr->ucBcdLen);

    return ulRet;
}


VOS_UINT32  TAF_STD_ConvertAsciiCodeToBcd(
    VOS_CHAR                            cAsciiCode,
    VOS_UINT8                          *pucBcdCode
)
{
    if (VOS_NULL_PTR == pucBcdCode)
    {
        return MN_ERR_NULLPTR;
    }

    if ((cAsciiCode >= '0')
     && (cAsciiCode <= '9'))
    {
        *pucBcdCode = (VOS_UINT8)(cAsciiCode - '0');
    }
    else if ('*' == cAsciiCode)
    {
        *pucBcdCode = 0x0a;
    }
    else if ('#' == cAsciiCode)
    {
        *pucBcdCode = 0x0b;
    }
    else if (('a' == cAsciiCode)
          || ('b' == cAsciiCode)
          || ('c' == cAsciiCode))
    {
        *pucBcdCode = (VOS_UINT8)((cAsciiCode - 'a') + 0x0c);
    }
    else
    {
        return MN_ERR_INVALID_ASCII;
    }

    return MN_ERR_NO_ERROR;
}


VOS_UINT8 TAF_STD_ConvertDeciDigitToBcd(
    VOS_UINT8                           ucDeciDigit,
    VOS_BOOL                            bReverseOrder
)
{
    VOS_UINT8 ucBcd;

    if (VOS_TRUE == bReverseOrder)
    {
        /*低4BIT存储十进制数的高位*/
        ucBcd  = ucDeciDigit / 10;
        /*高4BIT存储十进制数的低位*/
        ucBcd |= (ucDeciDigit % 10) << 4;
    }
    else
    {
        /*低4BIT存储十进制数的地位*/
        ucBcd  = ucDeciDigit % 10;
        /*高4BIT存储十进制数的高位*/
        ucBcd |= (VOS_UINT8)((ucDeciDigit / 10) << 4);
    }

    return ucBcd;
}


VOS_UINT32 TAF_STD_ConvertBcdToDeciDigit(
    VOS_UINT8                           ucBcdDigit,
    VOS_BOOL                            bReverseOrder,
    VOS_UINT8                          *pucDigit
)
{
    VOS_UINT8                           ucHigher;
    VOS_UINT8                           ucLower;
    VOS_UINT32                          ulRet;

    ucHigher = (ucBcdDigit >> 4) & 0x0f;
    ucLower  = ucBcdDigit & 0x0f;
    if ((ucHigher > 9) || (ucLower > 9))
    {
        ulRet = MN_ERR_INVALIDPARM;
    }
    else
    {
        ulRet = MN_ERR_NO_ERROR;
    }

    if (VOS_TRUE == bReverseOrder)
    {
        *pucDigit  = (VOS_UINT8)((VOS_UINT8)(ucLower * 10) + ucHigher);
    }
    else
    {
        *pucDigit  = (VOS_UINT8)((VOS_UINT8)ucHigher * 10) + ucLower;
    }

    return ulRet;
}


VOS_UINT32  TAF_STD_ConvertAsciiToDefAlpha(
    const VOS_UINT8                    *pucAsciiChar,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucDefAlpha
)
{
    VOS_UINT8                           ucLoop1;
    VOS_UINT32                          ulLoop2;
    VOS_BOOL                            bMatched;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pucAsciiChar)
     || (VOS_NULL_PTR == pucDefAlpha))
    {
        return MN_ERR_NULLPTR;
    }

    ulRet = MN_ERR_NO_ERROR;
    /*
    目前参考其他平台仅支持23038 6.2.1 GSM 7 bit Default Alphabet表中存在的字符集，
    不支持扩展表中的字符；
    ASCII表与GSM 7 bit Default Alphabet交集部分的标准ASCII码可以转换为GSM 7 bit Default Alphabet；
    键盘能够输入的字符已测试通过，其他未测试；
    ASCII表中其他字符，如{，则记录为00，回读出来是@，其他则失败；
    键盘能够输入的字符已测试通过，其他未测试；
    需要参考其他平台的处理；
    */
    for (ulLoop2 = 0; ulLoop2 < ulLen; ulLoop2++)
    {
        bMatched = VOS_FALSE;
        /*7BIT convert into ASCII ,consider later!!!!!*/
        for (ucLoop1 = 0 ; ucLoop1 < TAF_STD_MAX_GSM7BITDEFALPHA_NUM ; ucLoop1++)
        {
            if (f_aucMsgAsciiSfxDefAlpha[ucLoop1] == (*pucAsciiChar))
            {
                *pucDefAlpha = ucLoop1;
                pucDefAlpha++;
                bMatched = VOS_TRUE;
                break;
            }
        }

        if (VOS_TRUE != bMatched)
        {
            ulRet = MN_ERR_INVALIDPARM;
        }

        pucAsciiChar++;
    }

    return ulRet;
}


VOS_VOID  TAF_STD_ConvertDefAlphaToAscii(
    const VOS_UINT8                     *pucDefAlpha,
    VOS_UINT32                          ulDefAlphaLen,
    VOS_UINT8                           *pucAsciiChar,
    VOS_UINT32                          *pulAsciiCharLen
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           ucPos;
    VOS_UINT32                          ulValidLen = 0;

    if ((VOS_NULL_PTR == pucDefAlpha)
     || (VOS_NULL_PTR == pucAsciiChar))
    {
        return;
    }

    /*
    目前参考其他平台仅支持23038 6.2.1 GSM 7 bit Default Alphabet表中存在的字符集，
    不支持扩展表中的字符；
    与ASCII表交集部分的GSM 7 bit Default Alphabet可以转换为标准ASCII码供显示用；
    扩展字符标记转换为0XFE，不同设备上对其有私有解释；
    其他非标准字符转换为0XFF，不同设备上对其有私有解释；
    需要参考其他平台的处理；
    */
    for (ulLoop = 0; ulLoop < ulDefAlphaLen; ulLoop++)
    {
        ucPos           = TAF_STD_7BIT_MASK & pucDefAlpha[ulLoop];
        *pucAsciiChar   = f_aucMsgAsciiSfxDefAlpha[ucPos];
        if (TAF_STD_NOSTANDARD_ASCII_CODE == (*pucAsciiChar))
        {
            /* 对比标杆,对无法显示的字符使用空格替换 */
            (*pucAsciiChar) = ' ';
            pucAsciiChar++;
            ulValidLen++;
        }
        else if (TAF_STD_GSM_7BIT_EXTENSION_FLAG == (*pucAsciiChar) )
        {
            (*pucAsciiChar) = ' ';
            pucAsciiChar++;
            ulValidLen++;
        }
        else
        {
            pucAsciiChar++;
            ulValidLen++;
        }
    }

    if (ulValidLen < ulDefAlphaLen)
    {
        *pucAsciiChar = 0;
    }
    *pulAsciiCharLen = ulValidLen;

    return;
}



VOS_UINT32  TAF_STD_ConvertBcdCodeToDtmf(
    VOS_UINT8                           ucBcdCode,
    VOS_UINT8                          *pucDtmfCode
)
{
    VOS_UINT8                            ucDtmfCode;

    if (VOS_NULL_PTR == pucDtmfCode)
    {
        return MN_ERR_NULLPTR;
    }

    /*数字'0' BCD:0x00, DTMF:0x0A*/
    /*字符'*' BCD:0x0A, DTMF:0x0B*/
    /*字符'#' BCD:0x0B, DTMF:0x0C*/

    if (ucBcdCode == 0x00)
    {
        ucDtmfCode = 0x0A;
    }
    else if (ucBcdCode <= 0x09)
    {
        ucDtmfCode = ucBcdCode;
    }
    else if (0x0A == ucBcdCode)         /*字符'*'*/
    {
        ucDtmfCode = ucBcdCode + 1;
    }
    else if (0x0B == ucBcdCode)
    {
        ucDtmfCode = ucBcdCode + 1;     /*字符'#'*/
    }
    else
    {
        return MN_ERR_INVALID_BCD;
    }

    *pucDtmfCode = ucDtmfCode;

    return MN_ERR_NO_ERROR;
}


VOS_UINT32  TAF_STD_ConvertBcdNumberToDtmf(
    const VOS_UINT8                    *pucBcdNumber,
    VOS_UINT8                           ucBcdLen,
    VOS_UINT8                          *pucDtmfNumber
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucBcdCode;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pucBcdNumber)
     || (VOS_NULL_PTR == pucDtmfNumber))
    {
        return MN_ERR_NULLPTR;
    }

    /*整理号码字符串，去除无效的0XFF数据*/
    while (ucBcdLen > 1)
    {
        if (0xFF == pucBcdNumber[ucBcdLen - 1])
        {
            ucBcdLen--;
        }
        else
        {
            break;
        }
    }

    /*判断pucBcdAddress所指向的字符串的最后一个字节的高位是否为1111，
    如果是，说明号码位数为奇数，否则为偶数*/
    if ((pucBcdNumber[ucBcdLen - 1] & 0xF0) == 0xF0)
    {
        ucLen = (VOS_UINT8)((ucBcdLen * 2) - 1);
    }
    else
    {
        ucLen = (VOS_UINT8)(ucBcdLen * 2);
    }

    /*解析号码*/
    for (ucLoop = 0; ucLoop < ucLen; ucLoop++)
    {
        /*判断当前解码的是奇数位号码还是偶数位号码，从0开始，是偶数*/
        if (1 == (ucLoop % 2))
        {
            /*如果是奇数位号码，则取高4位的值*/
            ucBcdCode = ((pucBcdNumber[(ucLoop / 2)] >> 4) & 0x0F);
        }
        else
        {
            /*如果是偶数位号码，则取低4位的值*/
            ucBcdCode = (pucBcdNumber[(ucLoop / 2)] & 0x0F);
        }

        /*将二进制数字转换成DTMF码形式*/
        ulRet = TAF_STD_ConvertBcdCodeToDtmf(ucBcdCode, pucDtmfNumber);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }

        pucDtmfNumber++;
    }

    return MN_ERR_NO_ERROR;
}




LOCAL VOS_UINT16* TAF_STD_GetDaysOfLeapMonthTabAddr(VOS_VOID)
{
    return g_ausTafStdLeapMonthTab;
}


LOCAL VOS_UINT16* TAF_STD_GetDaysOfNormalMonthTabAddr(VOS_VOID)
{
    return g_ausTafStdNormMonthTab;
}


LOCAL VOS_UINT16* TAF_STD_GetDaysElapsedOfALeapYearSet(VOS_VOID)
{
    return g_ausTafStdDaysElapsedOfALeapYearSetTab;
}


VOS_UINT32 TAF_STD_64Add32
(
    VOS_UINT32                          ulHighAddend,
    VOS_UINT32                          ulLowAddend,
    VOS_UINT32                          ulAddFactor,
    VOS_UINT32                         *pulHighRslt,
    VOS_UINT32                         *pulLowRslt
)
{
    if (0xFFFFFFFF - ulLowAddend >= ulAddFactor)
    {
        *pulLowRslt  = ulLowAddend + ulAddFactor;
        *pulHighRslt = ulHighAddend;
    }
    else
    {
        if (0xFFFFFFFF == ulHighAddend)
        {
            return VOS_ERR;
        }

        *pulHighRslt = ulHighAddend + 1;
        *pulLowRslt = ulAddFactor - (0xFFFFFFFF - ulLowAddend) - 1;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_STD_64Sub32
(
    VOS_UINT32                          ulHighMinuend,
    VOS_UINT32                          ulLowMinuend,
    VOS_UINT32                          ulSubFactor,
    VOS_UINT32                         *pulHighRslt,
    VOS_UINT32                         *pulLowRslt
)
{
    if(ulLowMinuend  >= ulSubFactor)
    {
        *pulHighRslt = ulHighMinuend;
        *pulLowRslt = ulLowMinuend - ulSubFactor;
    }
    else if (ulHighMinuend >= 1)
    {
        *pulHighRslt = ulHighMinuend - 1;
        *pulLowRslt  = ulLowMinuend + (0xFFFFFFFF - ulSubFactor) + 1;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

VOS_UINT32 TAF_STD_ConvertTimeFromSecsToTimeZone
(
    VOS_UINT32                          ulHighSystemTime,
    VOS_UINT32                          ulLowSystemTime,
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstUniversalTimeandLocalTimeZone
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usDays;
    VOS_UINT32                          ulQuadYyears;
    VOS_UINT16                         *pusMonthTable = VOS_NULL_PTR;
    VOS_UINT16                         *pusLeapMonthTable = VOS_NULL_PTR;
    VOS_UINT16                         *pusNormalMonthTable = VOS_NULL_PTR;
    VOS_UINT16                         *pusDaysElapsedTable = VOS_NULL_PTR;
    VOS_UINT32                          ulHighTmp;
    VOS_UINT32                          ulLowTmp;
    VOS_UINT32                          ulQuotientHigh;
    VOS_UINT32                          ulQuotientLow;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulRemainder;

    pusLeapMonthTable                 = TAF_STD_GetDaysOfLeapMonthTabAddr();

    pusNormalMonthTable               = TAF_STD_GetDaysOfNormalMonthTabAddr();

    pusDaysElapsedTable               = TAF_STD_GetDaysElapsedOfALeapYearSet();

    ulHighTmp      = 0;
    ulLowTmp       = 0;
    ulQuotientHigh = 0;
    ulQuotientLow  = 0;
    ulRemainder    = 0;
     /* 时间换算成从1980.1.1 开始的秒数 */
    ulResult = TAF_STD_64Add32(ulHighSystemTime, ulLowSystemTime, (VOS_UINT32)TAF_STD_TIME_ZONE_OFFSET_S, &ulHighTmp, &ulLowTmp);
    if ( VOS_OK != ulResult )
    {
        return VOS_ERR;
    }

     /* 根据系统时间的秒数计算当前时间的秒数 */
    ulResult = VOS_64Div32(ulHighTmp, ulLowTmp, TAF_STD_SECONDS_PER_MINUTE, &ulQuotientHigh, &ulQuotientLow, &ulRemainder);
    if ( VOS_OK != ulResult )
    {
        return VOS_ERR;
    }
    pstUniversalTimeandLocalTimeZone->usSecond = (VOS_UINT16)ulRemainder;

    /* 根据系统时间的秒数计算当前时间的分钟数 */
    ulResult = VOS_64Div32(ulQuotientHigh, ulQuotientLow, TAF_STD_MINUTES_PER_HOUR, &ulHighTmp, &ulLowTmp, &ulRemainder);
    if ( VOS_OK != ulResult )
    {
        return VOS_ERR;
    }
    pstUniversalTimeandLocalTimeZone->usMinute = (VOS_UINT16)ulRemainder;

    /* 根据系统时间的秒数计算当前时间的小时 */
    ulResult = VOS_64Div32(ulHighTmp, ulLowTmp, TAF_STD_HOURS_PER_DAY, &ulQuotientHigh, &ulQuotientLow, &ulRemainder);
    if ( VOS_OK != ulResult )
    {
        return VOS_ERR;
    }
    pstUniversalTimeandLocalTimeZone->usHour = (VOS_UINT16)ulRemainder;

    /* 计算自1980开始过去了多少闰年 */
    ulResult = VOS_64Div32(ulQuotientHigh, ulQuotientLow, TAF_STD_TIME_ZONE_QUAD_YEAR, &ulHighTmp, &ulLowTmp, &ulRemainder);
    if ( VOS_OK != ulResult )
    {
        return VOS_ERR;
    }
    usDays = (VOS_UINT16)ulRemainder;

    ulQuadYyears = ulLowTmp;

    pstUniversalTimeandLocalTimeZone->usYear = (VOS_UINT16)(TAF_STD_TIME_ZONE_BASE_YEAR + (4 * ulQuadYyears));

    /* 计算当前年处在哪个闰年中 */
    for ( i = 0; i < TAF_STD_DAYS_ELAPSED_OF_A_LEAP_YEAR_SET_TAB_COUNT - 1; i++ )
    {
        if (usDays < pusDaysElapsedTable[i + 1])
        {
            break;
        }
    }

    /* 获取当前年过去的天数 */
    usDays -= pusDaysElapsedTable[i];

    /* 计算是哪一年 */
    pstUniversalTimeandLocalTimeZone->usYear += (VOS_UINT16)i;

    /* 下面计算月份和哪一天 */

    /* 获取月份表 */
    pusMonthTable = (i == 0) ? pusLeapMonthTable : pusNormalMonthTable;

    /* 查找月份表 */
    for ( i = 0; i < TAF_STD_NORMAL_MONTH_TAB_COUNT - 1; i++ )
    {
        if (usDays < pusMonthTable[i + 1])
        {
            break;
        }
    }

    /* 计算出当前是哪一个天.*/
    pstUniversalTimeandLocalTimeZone->usDay = usDays - pusMonthTable[i] + 1;

    /* 计算出月份 */
    pstUniversalTimeandLocalTimeZone->usMonth = (VOS_UINT16)i + 1;

    return VOS_OK;
}


VOS_VOID TAF_STD_ConvertSystemTimeToHighLow(
    VOS_UINT8                          *pucSysTimeByte,
    VOS_UINT32                         *pulHighSystemTime,
    VOS_UINT32                         *pulLowSystemTime
)
{
    VOS_UINT32                          ulTmp;
    VOS_UINT8                          *pucAddr = VOS_NULL_PTR;

    pucAddr = pucSysTimeByte + 1;

    ulTmp = *pucAddr++;
    ulTmp <<= 8;
    ulTmp |= *pucAddr++;
    ulTmp <<= 8;
    ulTmp |= *pucAddr++;
    ulTmp <<= 8;
    ulTmp |= *pucAddr;

    /* 取systemtime的高四位 */
    *pulHighSystemTime = (VOS_UINT32)((pucSysTimeByte[0] & 0xF0) >> 4);

    /* 取systemtime的低四位 */
    *pulLowSystemTime  = ((((VOS_UINT32)(((VOS_UINT32)(pucSysTimeByte[0] & 0x0F)) << 28)) & 0xF0000000)
                       | ((VOS_UINT32)(ulTmp >> 4) & 0x0FFFFFFF));

}



VOS_UINT32 TAF_STD_IsValidEmerCategory(
    VOS_UINT8                           ucEmerCategory
)
{
    VOS_UINT32                          ulRet;

    if (ucEmerCategory > MN_CALL_EMER_CATEGORG_VAL_MAX)
    {
        return VOS_FALSE;
    }

    if (ucEmerCategory & MN_CALL_EMER_CATEGORG_POLICE)
    {
        ulRet = VOS_TRUE;
    }
    else if (ucEmerCategory & MN_CALL_EMER_CATEGORG_AMBULANCE)
    {
        ulRet = VOS_TRUE;
    }
    else if (ucEmerCategory & MN_CALL_EMER_CATEGORG_FIRE_BRIGADE)
    {
        ulRet = VOS_TRUE;
    }
    else if (ucEmerCategory & MN_CALL_EMER_CATEGORG_MARINE_GUARD)
    {
        ulRet = VOS_TRUE;
    }
    else if (ucEmerCategory & MN_CALL_EMER_CATEGORG_MOUNTAIN_RESCUE)
    {
        ulRet = VOS_TRUE;
    }
    else
    {
        ulRet = VOS_FALSE;
    }

    return ulRet;
}


VOS_UINT16 TAF_STD_TransformBcdMccToDeciDigit(
    VOS_UINT32                          ulBcdMcc
)
{
    /*0x00 06 04 --> 460 */
    VOS_UINT16                          usMcc;

    usMcc = (ulBcdMcc & 0xff) * 100 + ((ulBcdMcc >> 8) & 0xff) * 10 + ((ulBcdMcc >> 16) & 0xff);

    if ( 1000 < usMcc )
    {
        usMcc = 0xffff;
    }

    return usMcc;
}

VOS_UINT8 TAF_STD_TransformBcdImsi1112ToDeciDigit(
    VOS_UINT16                          usBcdImsi1112
)
{
    /*0x03 00 --> 3 */
    VOS_UINT16                          usImsi1112;

    usImsi1112 = ((usBcdImsi1112 ) & 0xff) * 10 + ((usBcdImsi1112 >> 8) & 0xff);

    if ( 100 < usImsi1112 )
    {
        usImsi1112 = 0xffff;
    }

    return (VOS_UINT8)usImsi1112;
}



VOS_UINT16 TAF_STD_TransformBcdMncToDeciDigit(
    VOS_UINT16                          usBcdMnc
)
{
    /*0x03 00 --> 03 */
    VOS_UINT16                          usMnc;

    usMnc = (usBcdMnc & 0xff) * 10 + ((usBcdMnc >> 8) & 0xff);

    if ( 100 < usMnc )
    {
        usMnc = 0xffff;
    }

    return usMnc;
}



VOS_UINT32 TAF_STD_TransformDeciDigitToBcdMcc(
    VOS_UINT32                          ulDeciDigitMcc
)
{
    /*460 --->0x00 06 04 */
    VOS_UINT32                          ulBcdMcc;

    if (TAF_STD_INVALID_MCC != ulDeciDigitMcc)
    {
        ulBcdMcc  = (ulDeciDigitMcc % 1000) / 100;

        ulBcdMcc += (ulDeciDigitMcc % 10) << 16;

        ulBcdMcc += ((ulDeciDigitMcc % 100) / 10) << 8;

        return ulBcdMcc;
    }
    else
    {
        return TAF_STD_INVALID_MCC;
    }
}

/*lint -restore */

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


