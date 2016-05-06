/******************************************************************************

版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
文 件 名      : XMLDecode.c
版 本 号      : 初稿
作    者      : 郑继树 176513
生成日期      : 2010年12月20日
最近修改      :
功能描述      : 该头文件为XML相关操作c文件
函数列表      :
修改历史      :
1.日    期    : 2010年12月20日
作    者    : 郑继树 176513
修改内容    : 创建文件

******************************************************************************/
/*****************************************************************************
1 头文件包含
*****************************************************************************/
#include "SysNvId.h"
#include "nvim_internalfunc.h"
#include "nvim_fileoperateinterface.h"
#include "XMLDecode.h"
#include "mdrv.h"
#include "product_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_XML_C

/*****************************************************************************
2 全局变量定义
*****************************************************************************/
/* 当前xml文件在单板文件系统的路径  */
#if (VOS_OS_VER == VOS_WIN32)       /* PC Stub */
XML_PATH_STRU g_astXMLFilePath[2] = {{".\\yaffs0\\NvimUse\\xnv.xml",         ".\\yaffs0\\NvimUse\\cust.xml"},
                                    {".\\yaffs0\\NvimUse\\xnvnotexist.xml", ".\\yaffs0\\NvimUse\\xnvnotexist.xml"}};

XML_MAP_PATH_STRU g_astMapFilePath[2] = {{".\\yaffs0\\NvimUse\\xnv.map"}, {".\\yaffs0\\NvimUse\\xnv1.map"}};

#else
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )

XML_PATH_STRU g_astXMLFilePath[MODEM_ID_BUTT] = {{"/mnvm2:0/NvimUse/xnv.xml",    "/mnvm2:0/NvimUse/cust.xml"},
                                                {"/mnvm2:0/NvimUse/xnv1.xml",   "/mnvm2:0/NvimUse/cust1.xml"}};

XML_MAP_PATH_STRU  g_astMapFilePath[MODEM_ID_BUTT] = {{"/mnvm2:0/NvimUse/xnv.map"}, {"/mnvm2:0/NvimUse/xnv1.map"}};

#else   /*( FEATURE_MULTI_MODEM == FEATURE_OFF )*/


XML_PATH_STRU g_astXMLFilePath[MODEM_ID_BUTT] = {"/mnvm2:0/NvimUse/xnv.xml",  "/mnvm2:0/NvimUse/cust.xml"};
XML_MAP_PATH_STRU  g_astMapFilePath[MODEM_ID_BUTT] = {"/mnvm2:0/NvimUse/xnv.map"};

#endif  /*( FEATURE_MULTI_MODEM == FEATURE_ON )*/
#endif  /*OAM_UT_DEBUG*/

#define XML_NAME_MAX_LEN                (24)

/* 当前解析的Modem ID的值  */
VOS_UINT16 g_enXMLCurModemID;


/* 共通节点名称                         */
VOS_CHAR g_acNodeLabelCommon[]               = "common_NvInfo";

/* Product节点名称                      */
VOS_CHAR g_acNodeLabelProduct[]              = "product";

/* NV节点名称                           */
VOS_CHAR g_acNodeLabelNv[]                   = "nv";

/* Cust节点名称                         */
VOS_CHAR g_acNodeLabelCust[]                 = "cust";

/* 节点十六进制值之间的分隔符           */
VOS_CHAR g_cSeparator                        = ',';

/* XML文件解析时的状态                  */
XML_ANALYSE_STATUS_ENUM_UINT32 g_ulXMLStatus = XML_ANASTT_ORIGINAL;

/* 当前节点                             */
XML_NODE_STRU g_stXMLCurrentNode;

/* 记录有效的Product节点信息            */
XML_PRODUCT_STRU g_stXMLProductInfo;

/* 存放NV Item的值                      */
VOS_UINT8 *g_pucNVItem                       = VOS_NULL_PTR;

/* 读取文件数据的缓冲区                 */
VOS_CHAR  *g_pcFileReadBuff                  = VOS_NULL_PTR;

/* 记录读取XML文件的行数                */
VOS_UINT32 g_ulLineNo                        = VOS_NULL_LONG;

/*  xnv.xml文件描述符                   */
FILE*      g_lEnvFile                        = VOS_NULL_PTR;

/*  cust.xml文件描述符                  */
FILE*      g_lCustFile                       = VOS_NULL_PTR;

/* XML错误信息 */
XML_ERROR_INFO_STRU g_stXmlErrorInfo;

#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
/* 支持产品索引的xnv.xml解析状态 */
XML_PRODUCT_DECODE_STATUS_ENUM_UINT32 g_enProductDecodeStatus = XML_PRODUCT_ANALYZE_START;

/* Product节点名称                      */
VOS_CHAR g_acNodeLabelProductCat[]              = "product_NvInfo";
#endif

/* XML关键字,不包括0-9,a-z,A-Z */
VOS_CHAR   g_acXMLKeyWordTbl[] = { '<', '>', '/', '=', '"',
                                   ' ', '!', '?', '_', '-',
                                   ',' };

/*****************************************************************************
3 函数定义
*****************************************************************************/
#if (VOS_OS_VER == VOS_WIN32)
extern VOS_VOID XML_SendMsg(VOS_UINT32 ulRet);
#endif

/*****************************************************************************
函 数 名  : XML_WriteErrorLog
功能描述  : 记录错误信息到Log文件
输入参数  : ulErrLine 指出错时的代码行号
          : ulNvId    指出错时对应的NV ID
          : ulResult  指出错时函数对应的返回值
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : XML_CheckCharValidity
            XML_ProcXmlOrinigal
            XML_ProcXmlEnterLabel
            XML_ProcXmlIgnore
            XML_ProcXmlNodeLabel
            XML_ProcXmlSingleEndLabel
            XML_ProcXmlEndMustBeRight
            XML_ProcXmlPropertyStart
            XML_ProcXmlPropertyName
            XML_ProcXmlPropertyNameTail
            XML_ProcXmlValueStart
            XML_ProcXmlValueTail
            XML_Analyse
            XML_DecodeXMLFile
            XML_ProcInit
            XML_GetProductId
            XML_CheckXMLKeyWord
            XML_CheckCharValidity
            XML_WriteNVItem
            XML_StringToNvId
            XML_StringToNvValue
            XML_StringToHex
修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID XML_WriteErrorLog(VOS_UINT32 ulErrLine, VOS_UINT16 ulNvId,
                                VOS_UINT32 ulResult)
{
    g_stXmlErrorInfo.ulXMLLine  = g_ulLineNo;
    g_stXmlErrorInfo.ulStatus   = g_ulXMLStatus;
    g_stXmlErrorInfo.ulCodeLine = ulErrLine;
    g_stXmlErrorInfo.usNvId     = ulNvId;
    g_stXmlErrorInfo.ulResult   = ulResult;

    return ;
}

/*****************************************************************************
函 数 名  : XML_CheckXMLKeyWord
功能描述  : 检查当前字符的是否是XML关键字
输入参数  : cCurrentChar 指当前字符
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : 无
被调函数  : XML_CheckCharValidity

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_CheckXMLKeyWord(VOS_CHAR cCurrentChar)
{
    VOS_UINT32 lCount;

    if ((('0' <= cCurrentChar) && ('9' >= cCurrentChar))   /* 有效字符：0-9  */
        ||(('a' <= cCurrentChar) && ('z' >= cCurrentChar)) /* 有效字符：a-z  */
        ||(('A' <= cCurrentChar) && ('Z' >= cCurrentChar)))/* 有效字符：A-Z  */
    {
        return XML_RESULT_SUCCEED;
    }

    /* 除 0-9,a-z,A-Z 之外的 XML关键字 */
    for (lCount=0; lCount<sizeof(g_acXMLKeyWordTbl); lCount++)
    {
        if (cCurrentChar == g_acXMLKeyWordTbl[lCount])
        {
            return XML_RESULT_SUCCEED;
        }
    }

    return XML_RESULT_FALIED_BAD_CHAR;
}


/*****************************************************************************
函 数 名  : XML_CheckCharValidity
功能描述  : 检查当前字符的有效性
输入参数  : cCurrentChar 指当前字符
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_CheckXMLKeyWord
            XML_WriteErrorLog
被调函数  : XML_Analyse

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_CheckCharValidity(VOS_CHAR cCurrentChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal;

    if (('\r' == cCurrentChar)       /* 忽略回车   */
        || ('\t' == cCurrentChar))   /* 忽略制表符 */
    {
        return XML_RESULT_SUCCEED_IGNORE_CHAR;
    }

    if ('\n' == cCurrentChar)    /* 忽略换行   */
    {
        g_ulLineNo++;
        return XML_RESULT_SUCCEED_IGNORE_CHAR;
    }

    /* 在注释中的字符不做检查 */
    if ( XML_ANASTT_IGNORE == g_ulXMLStatus)
    {
        return XML_RESULT_SUCCEED;
    }

    /* 检查XML的关键字 */
    ulReturnVal = XML_CheckXMLKeyWord(cCurrentChar);
    if (XML_RESULT_SUCCEED != ulReturnVal)
    {
        XML_WriteErrorLog(__LINE__, 0, ulReturnVal);

        return ulReturnVal;
    }

    return XML_RESULT_SUCCEED;
}


/*****************************************************************************
函 数 名  : XML_StringToNvId
功能描述  : 把字符串转成十进制的格式
输入参数  : pcBuff 指字符串缓冲区
输出参数  : pusRetVal 指转换后的返回值
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_WriteErrorLog
被调函数  : XML_WriteNVItem

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_StringToNvId(VOS_CHAR  *pcBuff,
                                            VOS_UINT16 *pusRetVal)
{
    VOS_UINT32 ulTemp = 0;  /* 字符串转成整型时的中间变量 */
    VOS_CHAR   cCurrentChar;
    VOS_CHAR  *pcSrc;

    pcSrc = pcBuff;

    /* 如果NV ID是空的，则返回错误 */
    if (0 == *pcSrc)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_NV_ID_IS_NULL);

        return XML_RESULT_FALIED_NV_ID_IS_NULL;
    }

    /* 把字符串转成十进制的格式 */
    while (0 != *pcSrc)
    {
        cCurrentChar = *pcSrc;

        /* 对不在0－9之间的字符，按错误处理 */
        if ((cCurrentChar < '0') || (cCurrentChar > '9'))
        {
            XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_0_9);

            return XML_RESULT_FALIED_OUT_OF_0_9;
        }

        /* 转成十进制格式 */
        cCurrentChar -= '0';
        ulTemp = (ulTemp*10) + (VOS_UINT8)cCurrentChar;

        /* 超出NV ID的最大值 */
        if (VOS_NULL_WORD < ulTemp)
        {
            XML_WriteErrorLog(__LINE__, (VOS_UINT16)ulTemp, XML_RESULT_FALIED_OUT_OF_MAX_VALUE);

            return XML_RESULT_FALIED_OUT_OF_MAX_VALUE;
        }

        pcSrc++;
    }

    /* 输出 转换后的值 */
    *pusRetVal = (VOS_UINT16)ulTemp;

    return XML_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_StringToHex
功能描述  : 把字符转成十六进制的格式
输入参数  : pucSrc 待转换的字符串
输出参数  : pucDest转换后的数据
          : pucDestLen 转换后的数据长度
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_WriteErrorLog
被调函数  : XML_StringToNvValue

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_StringToHex(VOS_UINT8 *pucSrc, VOS_UINT8 *pucDest)
{
    VOS_UINT8  ucCurrent;
    VOS_UINT8  ucTemp  = 0;
    VOS_UINT16 usCount = 0;

    /* pucSrc的长度一定是偶数,由输入的参数保证 */
    while (0 != *pucSrc)
    {
        ucCurrent = *pucSrc;

        if ((ucCurrent >= 'a') && (ucCurrent <= 'f'))
        {
            /* 将小写字符转成大写*/
            ucCurrent -= 'a'-'A';
        }

        /* 转成十六进制格式 */
        if ((ucCurrent >= 'A') && (ucCurrent <= 'F'))
        {
            usCount++;
            ucTemp = (VOS_UINT8)(ucTemp * 16) + (VOS_UINT8)(ucCurrent - 'A') + 10;
        }
        else if ((ucCurrent >= '0') && (ucCurrent <= '9'))
        {
            usCount++;
            ucTemp = (VOS_UINT8)(ucTemp * 16) + (VOS_UINT8)(ucCurrent - '0');
        }
        else
        {
            /* 对不在0-9,a-f,A-F之间的字符，按错误处理 */
            XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_0_F);

            return XML_RESULT_FALIED_OUT_OF_0_F;
        } /* end of if ((ucCurrent >= 'a') && (ucCurrent <= 'f')) */

        /* 将2个字符转换成一个十六进制后,保存到目标缓冲区中 */
        if (2 == usCount)
        {
            *pucDest++ = ucTemp;
            ucTemp = 0;
            usCount = 0;
        }

        pucSrc++;
    }

    /* 加上字符串结束府'\0' */
    *pucDest = 0;

    return XML_RESULT_SUCCEED;
}


/*****************************************************************************
函 数 名  : XML_StringToNvValue
功能描述  : 把字符串转成十六进制的格式
输入参数  : pucBuff 指字符串缓冲区
输出参数  : pucRetBuff转换后的数据
          : pucRetBuffLen转换后数据的长度
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_WriteErrorLog
            XML_StringToHex
被调函数  : XML_WriteNVItem

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_StringToNvValue(VOS_UINT8  *pucBuff,
                                                 VOS_UINT8  *pucRetBuff,
                                                 VOS_UINT32 *pulRetBuffLen)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal;
    VOS_UINT32 ulCount = 0;    /* 判断是否保存当前转换后的值 */
    VOS_UINT8 *pcSrc;
    VOS_UINT8 *pcDest;

    pcSrc  = pucBuff;
    pcDest = pucBuff;

     /* 如果NV VALUE是空的，则返回错误 */
    if (0 == *pcSrc)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_NV_VALUE_IS_NULL);

        return XML_RESULT_FALIED_NV_VALUE_IS_NULL;
    }

    /* 先把原字符串中的分隔符去掉 */
    while (0 != *pcSrc)
    {
        /* 如果当前字符是分隔符 */
        if (g_cSeparator == *pcSrc)
        {
            /* 如果在2个分隔符之间只有一个字符,则需在前面插入一个'0' */
            if (1 == ulCount)
            {
                *pcDest = *(pcDest-1);
                *(pcDest-1) = '0';
                pcDest++;
            }

            ulCount = 0;
            pcSrc++;

            continue;
        }

        /* 如果有一个NV项超过2个字符,即出错.例<nv id="1">A3E</nvs> */
        if (2 <= ulCount)
        {
            XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_2_CHAR);

            return XML_RESULT_FALIED_OUT_OF_2_CHAR;
        }

        *pcDest++ = *pcSrc++;
        ulCount++;    /* 记录分隔符之间字符的个数 */
    }

    /* 如果最后一个分隔符后只有一个字符,则需在前面插入一个'0' */
    if (1 == ulCount)
    {
        *pcDest = *(pcDest-1);
        *(pcDest-1) = '0';
        pcDest++;
    }

    /* 加上字符串结束府'\0' */
    *pcDest = 0;

    /* 记录转换后的数据长度 */
    *pulRetBuffLen = (VOS_UINT32)(pcDest - pucBuff)/2;

    /* 转成十六进制格式 */
    pcSrc  = pucBuff;
    pcDest = pucRetBuff;
    ulReturnVal =  XML_StringToHex(pcSrc, pcDest);

    return ulReturnVal;
}

/*****************************************************************************
函 数 名  : XML_WriteNVItem
功能描述  : 把节点信息写到NV中
输入参数  : 无
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : VOS_StrCmp
            XML_StringToNvId
            XML_StringToNvValue
            NV_Write
            XML_WriteErrorLog
被调函数  : XML_CheckNodeLabelValid
            XML_CheckNodeEndLabelValid
            XML_ProcXmlEnterLabel
修改历史
1.日    期 : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_WriteNVItem(VOS_VOID)
{
    XML_RESULT_ENUM_UINT32              ulReturnVal;
    VOS_UINT16                          usNVItemId  = 0;
    VOS_UINT32                          ulNVItemLen = 0;
    VOS_INT                             lIsNV       = 0;
    VOS_INT                             lIsCust     = 0;
    VOS_UINT32                          ulRet;

    /* 如果当前节点不是有效的节点,则不做任何处理 */
    if (XML_PRODUCT_NODE_STATUS_INVALID == g_stXMLProductInfo.enValidNode)
    {
        return XML_RESULT_SUCCEED;
    }

    /* 如果属性值为空,而且节点值为空,则不做任何处理, 如<cust/> */
    g_stXMLCurrentNode.stProperty.pcPropertyValue[
                        g_stXMLCurrentNode.stProperty.ulValueLength] = '\0';

    g_stXMLCurrentNode.pcNodeValue[g_stXMLCurrentNode.ulValueLength] = '\0';

    if ((0 == *g_stXMLCurrentNode.stProperty.pcPropertyValue)
        && (0 == *g_stXMLCurrentNode.pcNodeValue))
    {
        return XML_RESULT_SUCCEED;
    }

    /* 只对nv，cust节点写到NV中 */
    g_stXMLCurrentNode.pcNodeLabel[g_stXMLCurrentNode.ulLabelLength] = '\0';

    lIsNV   = VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel, g_acNodeLabelNv);

    lIsCust = VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel, g_acNodeLabelCust);

    if ((0 != lIsNV) && (0 != lIsCust))
    {
        return XML_RESULT_SUCCEED;
    }

    /* 把属性值转成NV ID */
    ulReturnVal = XML_StringToNvId(g_stXMLCurrentNode.stProperty.pcPropertyValue,
                                &usNVItemId);

    if (XML_RESULT_SUCCEED != ulReturnVal)
    {
        return ulReturnVal;
    }

    /* 把节点值转成NV Value */
    ulNVItemLen = 0;

    ulReturnVal = XML_StringToNvValue((VOS_UINT8 *)g_stXMLCurrentNode.pcNodeValue,
                                  g_pucNVItem,
                                  &ulNVItemLen);

    if (XML_RESULT_SUCCEED != ulReturnVal)
    {
        return ulReturnVal;
    }

    /* 写到NV中 */
    ulRet = NV_WriteDirect(g_enXMLCurModemID, usNVItemId,(VOS_VOID *)(g_pucNVItem),ulNVItemLen);
    if ((NV_OK != ulRet) && (NV_WRITE_SECURE_FAIL != ulRet))
    {
        /* 记录出错的NV ID */
        XML_WriteErrorLog(__LINE__, usNVItemId, ulRet);

        return XML_RESULT_FALIED_WRITE_NV;
    }

    return XML_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_NodeReset
功能描述  : 清空节点信息
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : XML_CheckNodeLabelValid
            XML_CheckNodeEndLabelValid
            XML_ProcXmlEnterLabel

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID XML_NodeReset(VOS_VOID)
{
    /* 节点标签复位,已使用的长度为0  */
    g_stXMLCurrentNode.ulLabelLength = 0;

    /* 节点值复位,已使用的长度为0 */
    g_stXMLCurrentNode.ulValueLength = 0;

    /* 节点独立标签复位,已使用的长度为0 */
    g_stXMLCurrentNode.ulLabelEndLength = 0;

    /* 节点属性名复位,已使用的长度为0 */
    g_stXMLCurrentNode.stProperty.ulNameLength = 0;

    /* 节点属性值复位,已使用的长度为0 */
    g_stXMLCurrentNode.stProperty.ulValueLength = 0;

    return ;
}


/*****************************************************************************
函 数 名  : XML_AddACharToBuff
功能描述  : 把字符添加进指定长度缓冲区
输入参数  : pcDestChar待添加的字符，
          : pcStrBuff被添加字符串指针的地址，
          : plBuffLength字符创当前长度的地址
          : ulIsNodeValue指pcStrBuff是否是指向Node Value
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_WriteErrorLog
被调函数  : XML_ProcXmlOrinigal
            XML_ProcXmlEnterLabel
            XML_ProcXmlNodeLabel
            XML_ProcXmlSingleEndLabel
            XML_ProcXmlPropertyStart
            XML_ProcXmlPropertyName
            XML_ProcXmlValueStart

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_AddACharToBuff(VOS_CHAR   cNowChar,
                                                 VOS_CHAR   *pcStrBuff,
                                                 VOS_UINT32 *plBuffLength,
                                                 VOS_BOOL   ulIsNodeValue)
{
    /* 忽略空格 */
    if (' ' == cNowChar)
    {
        return XML_RESULT_SUCCEED;
    }

    /* 如果达到了Node Value的最大长度 */
    if ((VOS_TRUE == ulIsNodeValue)
        && (*plBuffLength >= XML_NODE_VALUE_BUFF_LENGTH_ORIGINAL))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_BUFF_LEN);

        return XML_RESULT_FALIED_OUT_OF_BUFF_LEN;
    }

    /* 如果达到了Node Lable的最大长度 */
    if ((VOS_FALSE == ulIsNodeValue)
        && (*plBuffLength >= XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_BUFF_LEN);

        return XML_RESULT_FALIED_OUT_OF_BUFF_LEN;
    }

    /* 把新字符加进缓冲区 */
    *(pcStrBuff + *plBuffLength) = cNowChar;

    /* 缓冲区长度加1 */
    (*plBuffLength)++;

    return XML_RESULT_SUCCEED;
}


/*****************************************************************************
函 数 名  : XML_CheckNodeLabelValid
功能描述  : 检查当前标签是否是有效标签
输入参数  : 无
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : VOS_StrCmp
被调函数  : XML_ProcXmlNodeLabel
            XML_ProcXmlPropertyStart
            XML_ProcXmlValueTail
修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_CheckNodeLabelValid(VOS_VOID)
{
    /* 判断该标签是否有效 */
    g_stXMLCurrentNode.pcNodeLabel[g_stXMLCurrentNode.ulLabelLength] = '\0';

    if (XML_PRODUCT_NODE_STATUS_VALID == g_stXMLProductInfo.enValidNode)
    {
        /* 在节点为有效状态下，对Product节点，要记录<product>节点出现的次数 */
        if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel,
                            g_acNodeLabelProduct))
        {
#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
            /* 支持产品集时，product cat公共部分nv解析完置特殊标记 */
            if (XML_PRODUCT_CAT_ANALYZE_START == g_enProductDecodeStatus)
            {
                g_enProductDecodeStatus = XML_PRODUCT_CAT_ANALYZE_FINISH;
                g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_INVALID;
            }
#endif
            g_stXMLProductInfo.ulNodeLevel++;
        }

        return XML_RESULT_SUCCEED;
    }

    /* 如果当前节点为无效状态,需要检查标签是否为有效节点 */
    if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel,
                        g_acNodeLabelCommon))
    {
        /* 如果是<Common_NvInfo>标签,则设置节点为有效状态 */
        g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_VALID;

        return XML_RESULT_SUCCEED;
    }

    /* 如果是<Cust>标签,则设置节点为有效状态 */
    if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel,
                             g_acNodeLabelCust))
    {
        g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_VALID;

        return XML_RESULT_SUCCEED;
    }

    /* 如果是<product>标签且Product id与当前单板相同,则设置节点为有效状态 */
    if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel,
                             g_acNodeLabelProduct))
    {
        g_stXMLCurrentNode.stProperty.pcPropertyValue[
                      g_stXMLCurrentNode.stProperty.ulValueLength] = '\0';

        if (0 == VOS_StrCmp(g_stXMLCurrentNode.stProperty.pcPropertyValue,
                            g_stXMLProductInfo.acProductId))
        {
            g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_VALID;
            g_stXMLProductInfo.ulNodeLevel++;
        }
    }

#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
    /* 检查product cat起始标签是否正确 */
    if (XML_PRODUCT_CAT_ANALYZE_START == g_enProductDecodeStatus)
    {
        if (0 != VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel,
                                 g_acNodeLabelProductCat))
        {
            XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_FILE);

            return XML_RESULT_FALIED_BAD_FILE;
        }

        g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_VALID;
    }
#endif

    return XML_RESULT_SUCCEED;
}


/*****************************************************************************
函 数 名  : XML_CheckNodeEndLabelValid
功能描述  : 检查当前独立标签是否是有效节点的结束标签
输入参数  : 无
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_WriteNVItem
            VOS_StrCmp
            XML_NodeReset
被调函数  : XML_ProcXmlSingleEndLabel

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_CheckNodeEndLabelValid(VOS_VOID)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal;

    if (XML_PRODUCT_NODE_STATUS_VALID != g_stXMLProductInfo.enValidNode)
    {
        /* 如果当前节点为无效状态，不做任何处理 */
        return XML_RESULT_SUCCEED;
    }

    /* 写节点信息到NV中 */
    ulReturnVal = XML_WriteNVItem();

    if (XML_RESULT_SUCCEED != ulReturnVal)
    {
        return ulReturnVal;
    }

    g_stXMLCurrentNode.pcNodeLabelEnd[g_stXMLCurrentNode.ulLabelEndLength]='\0';

    if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabelEnd,
                        g_acNodeLabelProduct))
    {
        g_stXMLProductInfo.ulNodeLevel--;

        if (0 == g_stXMLProductInfo.ulNodeLevel)
        {
            /* 最后一个有效的</product>标签出现时，结束整个XML文件的解析 */
            g_stXMLProductInfo.enXMLDecodeState=XML_DECODE_STATUS_FINISHED;
            g_stXMLProductInfo.enValidNode=XML_PRODUCT_NODE_STATUS_INVALID;
        }
#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
        /* 最后一个有效的</product>标签出现时，结束整个XML文件的解析 */
        g_stXMLProductInfo.enXMLDecodeState=XML_DECODE_STATUS_FINISHED;
        g_stXMLProductInfo.enValidNode=XML_PRODUCT_NODE_STATUS_INVALID;
        g_enProductDecodeStatus = XML_PRODUCT_ID_ANALYZE_FINISH;
#endif
    }
    else if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabelEnd,
                             g_acNodeLabelCommon))
    {
        /* </Common_NvInfo>标签出现时,把节点状态置为无效 */
        g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_INVALID;
#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
        /* 支持产品集时，common nv解析完置特殊标记 */
        g_enProductDecodeStatus = XML_PRODUCT_COMMON_ANALYZE_FINISH;
#endif
    }
    else if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabelEnd,
                             g_acNodeLabelCust))
    {
        /* </Cust>标签出现时,把节点状态置为无效 */
        g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_INVALID;
    }
    else
    {
        /* Do nothing */

    } /* end of if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabelEnd, */

    /* </xx>标签结束时，清空节点信息 */
    XML_NodeReset();

    return XML_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_CreateAProperty
功能描述  : 在内存中创建一个属性并初始化
输入参数  : 无
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : VOS_MemAlloc
            XML_WriteErrorLogs
被调函数  : XML_CreateANode

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_CreateAProperty( VOS_VOID )
{
    /* 分配属性名内存,+1为保留字符串结束符用 */
    g_stXMLCurrentNode.stProperty.ulNameLength = 0; /* 已使用的长度 */

    g_stXMLCurrentNode.stProperty.pcPropertyName
                                = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_OM,
                                   DYNAMIC_MEM_PT,
                                   XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL+1);

    if (VOS_NULL_PTR == g_stXMLCurrentNode.stProperty.pcPropertyName)
    {
         XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    /* 分配属性值内存,+1为保留字符串结束符用 */
    g_stXMLCurrentNode.stProperty.ulValueLength = 0; /* 已使用的长度 */

    g_stXMLCurrentNode.stProperty.pcPropertyValue
                                = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_OM,
                                   DYNAMIC_MEM_PT,
                                   XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL+1);

    if (VOS_NULL_PTR == g_stXMLCurrentNode.stProperty.pcPropertyValue)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    return XML_RESULT_SUCCEED;
}


/*****************************************************************************
函 数 名  : XML_CreateANode
功能描述  : 创建一个新节点
输入参数  : 无
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : VOS_MemAlloc
            XML_CreateAProperty
            XML_WriteErrorLog
被调函数  : XML_ProcInit

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_CreateANode(VOS_VOID)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal = XML_RESULT_SUCCEED;

    /* 创建一个新属性 */
    ulReturnVal = XML_CreateAProperty();

    if(XML_RESULT_SUCCEED != ulReturnVal)
    {
        return ulReturnVal;
    }

    /* 分配节点标签内存,+1为保留字符串结束符用*/
    g_stXMLCurrentNode.ulLabelLength = 0; /* 已使用的长度 */

    g_stXMLCurrentNode.pcNodeLabel = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_OM,
                                      DYNAMIC_MEM_PT,
                                      XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL+1);

    if (VOS_NULL_PTR ==  g_stXMLCurrentNode.pcNodeLabel)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    /* 分配节点结尾独立标签内存,+1为保留字符串结束符用 */
    g_stXMLCurrentNode.ulLabelEndLength = 0; /* 已使用的长度 */

    g_stXMLCurrentNode.pcNodeLabelEnd = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_OM,
                                        DYNAMIC_MEM_PT,
                                        XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL+1);

    if (VOS_NULL_PTR ==  g_stXMLCurrentNode.pcNodeLabelEnd)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    /* 分配节点值内存,+1为保留字符串结束符用 */
    g_stXMLCurrentNode.ulValueLength = 0; /* 已使用的长度 */

    g_stXMLCurrentNode.pcNodeValue = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_OM,
                                      DYNAMIC_MEM_PT,
                                      XML_NODE_VALUE_BUFF_LENGTH_ORIGINAL+1);

    if (VOS_NULL_PTR == g_stXMLCurrentNode.pcNodeValue)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    return ulReturnVal;
}


/*****************************************************************************
函 数 名  : XML_ProcXmlOrinigal
功能描述  : 状态机处理函数，初始状态的处理函数
输入参数  : 当前处理的字符
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_AddACharToBuff
            XML_WriteErrorLog
被调函数  : XML_Analyse

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_ProcXmlOrinigal(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal = XML_RESULT_SUCCEED;

    /* 遇到<则更改状态 */
    if ('<' == cNowChar)
    {
        g_ulXMLStatus = XML_ANASTT_ENTER_LABLE;
        return XML_RESULT_SUCCEED;
    }

    /* 遇到>,/,",=则表示XML语法错误 */
    if (('>' == cNowChar)
         ||('/' == cNowChar)
         ||('"' == cNowChar)
         ||('=' == cNowChar))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    if (XML_PRODUCT_NODE_STATUS_VALID == g_stXMLProductInfo.enValidNode)
    {
        /* 把这个字节放进当前节点值的缓冲区内 */
        ulReturnVal = XML_AddACharToBuff(cNowChar,
                                     g_stXMLCurrentNode.pcNodeValue,
                                     &(g_stXMLCurrentNode.ulValueLength),
                                     VOS_TRUE);
    }

    return ulReturnVal;
}


/*****************************************************************************
函 数 名  : XML_ProcXmlIgnore
功能描述  : 状态机处理函数，序言处理函数
输入参数  : 当前处理的字符
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : 无
被调函数  : XML_Analyse

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_ProcXmlIgnore(VOS_CHAR cNowChar)
{
    /* 直到遇到标签结尾，否则一直忽略 */
    if ('>' == cNowChar)
    {
        g_ulXMLStatus = XML_ANASTT_ORIGINAL;
    }

    return XML_RESULT_SUCCEED;
}


/*****************************************************************************
函 数 名  : XML_ProcXmlSingleEndLabel
功能描述  : 状态机处理函数，进入独立的结尾标签的处理
输入参数  : 当前处理的字符
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_AddACharToBuff
            XML_CheckNodeEndLabelValid
            XML_WriteErrorLog
被调函数  : XML_Analyse

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_ProcXmlSingleEndLabel(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal;

    ulReturnVal = XML_RESULT_SUCCEED;

    /* 遇到<则更改状态 */
    if ('>' == cNowChar)
    {
        /* 变更状态 */
        g_ulXMLStatus = XML_ANASTT_ORIGINAL;

        /* 检查独立结束标签是否有效 */
        ulReturnVal = XML_CheckNodeEndLabelValid();

        return ulReturnVal;
    }

    /* 遇到<,/,",=则表示XML语法错误 */
    if (('<' == cNowChar)
         ||('"' == cNowChar)
         ||('/' == cNowChar)
         ||('=' == cNowChar))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    if(XML_PRODUCT_NODE_STATUS_VALID == g_stXMLProductInfo.enValidNode)
    {
        /* 把这个字节放进当前节点值的缓冲区内 */
        ulReturnVal = XML_AddACharToBuff(cNowChar,
                                      g_stXMLCurrentNode.pcNodeLabelEnd,
                                      &(g_stXMLCurrentNode.ulLabelEndLength),
                                      VOS_FALSE);
    }

    return ulReturnVal;
}

#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
/*****************************************************************************
函 数 名  : XML_ProductCatNullNodeProc
功能描述  : 支持产品集的XML解析过程中空节点处理
输入参数  : 当前处理的字符
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
修改历史
1.日    期   : 2014年03月25日
作    者   : jinni 00168360
修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID XML_ProductCatNullNodeProc(VOS_VOID)
{
    g_stXMLCurrentNode.pcNodeLabel[g_stXMLCurrentNode.ulLabelLength] = '\0';

    if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel,
                        g_acNodeLabelCommon))
    {
        g_enProductDecodeStatus = XML_PRODUCT_COMMON_ANALYZE_FINISH;
        g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_INVALID;
    }

    if (XML_PRODUCT_CAT_ANALYZE_START == g_enProductDecodeStatus)
    {
        if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel,
                            g_acNodeLabelProduct))
        {
            g_enProductDecodeStatus = XML_PRODUCT_CAT_ANALYZE_FINISH;
            g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_INVALID;
        }
    }

    if (XML_PRODUCT_ID_ANALYZE_START == g_enProductDecodeStatus)
    {
        if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel,
                            g_acNodeLabelProduct))
        {
            g_enProductDecodeStatus = XML_PRODUCT_ID_ANALYZE_FINISH;
            g_stXMLProductInfo.enXMLDecodeState = XML_DECODE_STATUS_FINISHED;
            g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_INVALID;
        }
    }

    return;
}
#endif

/*****************************************************************************
函 数 名  : XML_ProcXmlEndMustBeRight
功能描述  : 状态机处理函数，进入Lable/等待>
输入参数  : 当前处理的字符
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_WriteNVItem
            XML_NodeReset
            XML_WriteErrorLog
被调函数  : XML_Analyse

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_ProcXmlEndMustBeRight(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal;

    /* 忽略空格 */
    if (' ' == cNowChar)
    {
        return XML_RESULT_SUCCEED;
    }

    /* 遇到不是>,则表示XML语法错误 */
    if ('>' != cNowChar)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
    XML_ProductCatNullNodeProc();
#endif

    /* 变更状态 */
    g_ulXMLStatus = XML_ANASTT_ORIGINAL;

    if (XML_PRODUCT_NODE_STATUS_VALID == g_stXMLProductInfo.enValidNode)
    {
        /* 写节点信息到NV中 */
        ulReturnVal = XML_WriteNVItem();

        if (XML_RESULT_SUCCEED != ulReturnVal)
        {
            return ulReturnVal;
        }

        /* <xx/>标签结束时，清空节点信息 */
        XML_NodeReset();
    }

    return XML_RESULT_SUCCEED;
}


/*****************************************************************************
函 数 名  : XML_ProcXmlEnterLabel
功能描述  : 状态机处理函数，进入节点后的处理
输入参数  : 当前处理的字符
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_CheckNodeLabelValid
            XML_AddACharToBuff
            XML_WriteErrorLog
被调函数  : XML_Analyse

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_ProcXmlNodeLabel(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal;

    /* 遇到/或者>或者空格说明Node的名字结束了 */
    if ('/' == cNowChar)
    {
        /* 结束并收尾整个节点,下个字节一定是> */
        g_ulXMLStatus = XML_ANASTT_LABLE_END_MUST_RIGHT;

        return XML_RESULT_SUCCEED;
    }

    /* 标签结束 */
    if ('>' == cNowChar)
    {
        /* 变更状态 */
        g_ulXMLStatus = XML_ANASTT_ORIGINAL;

        /* 检查当前节点是有效节点 */
        ulReturnVal = XML_CheckNodeLabelValid();

        return ulReturnVal;
    }

    /* 标签名字结束,进入属性解析状态 */
    if (' ' == cNowChar)
    {
        /* 变更状态 */
        g_ulXMLStatus = XML_ANASTT_PROPERTY_START;

        return XML_RESULT_SUCCEED;
    }

    /* 遇到<,",=则表示XML语法错误 */
    if (('<' == cNowChar)
         ||('"' == cNowChar)
         ||('=' == cNowChar))
    {
        XML_WriteErrorLog(__LINE__, 0,XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    /* 把这个字节放进当前节点值的缓冲区内 */
    ulReturnVal = XML_AddACharToBuff(cNowChar,
                                     g_stXMLCurrentNode.pcNodeLabel,
                                     &(g_stXMLCurrentNode.ulLabelLength),
                                     VOS_FALSE);

    return ulReturnVal;
}


/*****************************************************************************
函 数 名  : XML_ProcXmlEnterLabel
功能描述  : 状态机处理函数，进入Label后的处理
输入参数  : 当前处理的字符
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_WriteNVItem
            XML_NodeReset
            XML_AddACharToBuff
            XML_WriteErrorLog
被调函数  : XML_Analyse

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_ProcXmlEnterLabel(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal = XML_RESULT_SUCCEED;

    /* 遇到首行版本信息 */
    if ('?' == cNowChar)
    {
        g_ulXMLStatus = XML_ANASTT_IGNORE;

        return XML_RESULT_SUCCEED;
    }

    /* 遇到序言 */
    if ('!' == cNowChar)
    {
        g_ulXMLStatus = XML_ANASTT_IGNORE;

        return XML_RESULT_SUCCEED;
    }

    /* 遇到尾节点标签 */
    if ('/' == cNowChar)
    {
        g_ulXMLStatus = XML_ANASTT_SINGLE_ENDS_LABLE;

        return XML_RESULT_SUCCEED;
    }

    /* 遇到标签结束 */
    if ('>' == cNowChar)
    {
        g_ulXMLStatus = XML_ANASTT_ORIGINAL;

        return XML_RESULT_SUCCEED;
    }

    /* 遇到<,",=则表示XML语法错误 */
    if (('<' == cNowChar)
         ||('"' == cNowChar)
         ||('=' == cNowChar))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    /* 跳过空格 */
    if (' ' != cNowChar)
    {
        /* 写节点信息到NV中 */
        ulReturnVal = XML_WriteNVItem();

        if (XML_RESULT_SUCCEED != ulReturnVal)
        {
            return ulReturnVal;
        }

        /* 进入一个新节点时，先清空节点信息 */
        XML_NodeReset();

        /* 变更状态，表示进入一个新节点 */
        g_ulXMLStatus = XML_ANASTT_NODE_LABLE;

        /* 把这个字节放进当前节点值的缓冲区内 */
        ulReturnVal = XML_AddACharToBuff(cNowChar,
                                         g_stXMLCurrentNode.pcNodeLabel,
                                         &(g_stXMLCurrentNode.ulLabelLength),
                                         VOS_FALSE);
    }

    return ulReturnVal;
}


/*****************************************************************************
函 数 名  : XML_ProcXmlPropertyStart
功能描述  : 状态机处理函数，进入属性的解析
输入参数  : 当前处理的字符
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_CheckNodeLabelValid
            XML_AddACharToBuff
            XML_WriteErrorLog
被调函数  : XML_Analyse

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_ProcXmlPropertyStart(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal = XML_RESULT_SUCCEED;

    /* 遇到尾节点标签 */
    if ('/' == cNowChar)
    {
        /* 变更状态 */
        g_ulXMLStatus = XML_ANASTT_LABLE_END_MUST_RIGHT;

        return XML_RESULT_SUCCEED;
    }

    /* 标签结束 */
    if ('>' == cNowChar)
    {
        /* 变更状态 */
        g_ulXMLStatus = XML_ANASTT_ORIGINAL;

        /* 检查当前节点有效 */
        ulReturnVal = XML_CheckNodeLabelValid();

        return ulReturnVal;
    }

    /* 遇到<,",=则表示XML语法错误 */
    if (('<' == cNowChar)
         ||('"' == cNowChar)
         ||('=' == cNowChar))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    /* 更改状态 */
    g_ulXMLStatus = XML_ANASTT_PROPERTY_NAME_START;

    ulReturnVal = XML_AddACharToBuff(cNowChar,
                  g_stXMLCurrentNode.stProperty.pcPropertyName,
                  &(g_stXMLCurrentNode.stProperty.ulNameLength),
                  VOS_FALSE);

    return ulReturnVal;
}


/*****************************************************************************
函 数 名  : XML_ProcXmlPropertyName
功能描述  : 状态机处理函数，属性名字的解析
输入参数  : 当前处理的字符
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_AddACharToBuff
            XML_WriteErrorLog
被调函数  : XML_Analyse

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_ProcXmlPropertyName(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal = XML_RESULT_SUCCEED;

    /* 等待=进入属性值解析 */
    if ('=' == cNowChar)
    {
        /* 翻状态 */
        g_ulXMLStatus = XML_ANASTT_PROPERTY_NAME_END;

        return XML_RESULT_SUCCEED;
    }

    /* 遇到<,>,/,"则表示XML语法错误 */
    if (('<' == cNowChar)||('>' == cNowChar)
        ||('/' == cNowChar)||('"' == cNowChar))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    /* 容许属性名中的空格错误, 如 <nv i d="123"> */
    ulReturnVal = XML_AddACharToBuff(cNowChar,
                  g_stXMLCurrentNode.stProperty.pcPropertyName,
                  &(g_stXMLCurrentNode.stProperty.ulNameLength),
                  VOS_FALSE);

    return ulReturnVal;
}


/*****************************************************************************
函 数 名  : XML_ProcXmlPropertyNameTail
功能描述  : 状态机处理函数，属性名字结束，等待"即属性值开始
输入参数  : 当前处理的字符
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_WriteErrorLog
被调函数  : XML_Analyse

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_ProcXmlPropertyNameTail(VOS_CHAR cNowChar)
{
    /* 跳过空格 */
    if ( ' ' == cNowChar)
    {
        return XML_RESULT_SUCCEED;
    }

    /* 等待" */
    if ('"' == cNowChar)
    {
        /* 更改状态 */
        g_ulXMLStatus = XML_ANASTT_PROPERTY_VALUE_START;

        return XML_RESULT_SUCCEED;
    }

    /* 遇到不是"，则表示XML语法错误 */
    XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

    return XML_RESULT_FALIED_BAD_SYNTAX;
}


/*****************************************************************************
函 数 名  : XML_ProcXmlValueStart
功能描述  : 状态机处理函数，属性名字结束，等待"即属性值结束
输入参数  : 当前处理的字符
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_AddACharToBuff
            XML_WriteErrorLog
被调函数  : XML_Analyse
被调函数  :

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_ProcXmlValueStart(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal = XML_RESULT_SUCCEED;

    /* 遇到" */
    if ('"' == cNowChar)
    {
        /* 翻状态,返回开始解析属性的状态 */
        g_ulXMLStatus = XML_ANASTT_PROPERTY_VALUE_END;

        return XML_RESULT_SUCCEED;
    }

    /* 遇到<,>,/,=则表示XML语法错误 */
    if (('<' == cNowChar)
         ||('>' == cNowChar)
         ||('/' == cNowChar)
         ||('=' == cNowChar))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    /* 把当前字符加到属性值中 */
    ulReturnVal = XML_AddACharToBuff(cNowChar,
                  g_stXMLCurrentNode.stProperty.pcPropertyValue,
                  &(g_stXMLCurrentNode.stProperty.ulValueLength),
                  VOS_FALSE);

    return ulReturnVal;
}


/*****************************************************************************
函 数 名  : XML_ProcXmlValueTail
功能描述  : 状态机处理函数，属性名字结束，等待"即属性值结束
输入参数  : 当前处理的字符
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_CheckNodeLabelValid
            XML_WriteErrorLog
被调函数  : XML_Analyse
被调函数  :

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_ProcXmlValueTail(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal;

    /* 忽略空格 */
    if (' ' == cNowChar)
    {
        return XML_RESULT_SUCCEED;
    }

    /* 遇到'/' */
    if ('/' == cNowChar)
    {
        /* 变更状态 */
        g_ulXMLStatus = XML_ANASTT_LABLE_END_MUST_RIGHT;

        return XML_RESULT_SUCCEED;
    }

    /* 遇到'>' */
    if ('>' == cNowChar)
    {
        /* 变更状态,返回开始解析属性的状态 */
        g_ulXMLStatus = XML_ANASTT_ORIGINAL;

        /* 检查当前节点有效 */
        ulReturnVal = XML_CheckNodeLabelValid();

        return ulReturnVal;
    }

    /* 遇到不是>,/则表示XML语法错误 */
    XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

    return XML_RESULT_FALIED_BAD_SYNTAX;
}

/*****************************************************************************
函 数 名  : XML_Analyse
功能描述  : 主状态机
输入参数  : 当前解析的字符
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_CheckCharValidity
            XML_ProcXmlOrinigal
            XML_ProcXmlEnterLabel
            XML_ProcXmlIgnore
            XML_ProcXmlNodeLabel
            XML_ProcXmlSingleEndLabel
            XML_ProcXmlEndMustBeRight
            XML_ProcXmlPropertyStart
            XML_ProcXmlPropertyName
            XML_ProcXmlPropertyNameTail
            XML_ProcXmlValueStart
            XML_ProcXmlValueTail
被调函数  : XML_DecodeXMLFile

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
/*Global map table used to find the function according the xml analyse status.*/
XML_FUN g_ulXmlAnalyseFunTbl[] =
{
    XML_ProcXmlOrinigal,         /* 初始状态下的处理                  */
    XML_ProcXmlEnterLabel,       /* 进入Lable后的处理                 */
    XML_ProcXmlIgnore,           /* 序言或注释状态下直到遇到">"结束   */
    XML_ProcXmlNodeLabel,        /* 标签名字开始                      */
    XML_ProcXmlSingleEndLabel,   /* 标准的结尾标签</XXX>              */
    XML_ProcXmlEndMustBeRight,   /* 形如 <XXX/>的标签,在解析完/的状态 */
    XML_ProcXmlPropertyStart,    /* 开始解析属性                      */
    XML_ProcXmlPropertyName,     /* 开始解析属性名字                  */
    XML_ProcXmlPropertyNameTail, /* 属性名字结束，等待"即属性值开始   */
    XML_ProcXmlValueStart,       /* 属性值开始                        */
    XML_ProcXmlValueTail,        /* 属性值结束                        */
};

XML_RESULT_ENUM_UINT32 XML_Analyse(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal;

    /* 检查当前字符的有效性 */
    ulReturnVal = XML_CheckCharValidity(cNowChar);

    if (XML_RESULT_SUCCEED_IGNORE_CHAR == ulReturnVal)
    {
        /* 如果遇到序言，则跳过该字符 */
        return XML_RESULT_SUCCEED;
    }

    if (XML_RESULT_FALIED_BAD_CHAR == ulReturnVal)
    {
        /* 如果遇到非法字符，则停止解析 */
        return XML_RESULT_FALIED_BAD_CHAR;
    }

    /* 调用XML解析时，相应状态的对应函数 */
    ulReturnVal = g_ulXmlAnalyseFunTbl[g_ulXMLStatus](cNowChar);

    return ulReturnVal;
}

#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
/*****************************************************************************
函 数 名  : XML_CalcXmlMd5Value
功能描述  : 计算xml文件的MD5校验值
输入参数  : pfXmlFile -- XML文件指针
            pcXmlFileReadBuf -- 指向读XML文件的buff
            pcSaveHashValueBuf -- 指向存储xml分段计算的MD5校验值
输出参数  : pucHash -- 指向输出校验值的buff
            plHlen -- 校验值长度
返 回 值  : XML_RESULT_ENUM_UINT32

修改历史
1.日    期   : 2014年3月13日
  作    者   : 靳妮 00168360
  修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_CalcXmlMd5Value(VOS_CHAR *pcXmlFileReadBuf, VOS_CHAR *pcSaveHashValueBuf, FILE *pfXmlFile, VOS_CHAR *pucHash, VOS_INT32 *plHlen)
{
    VOS_INT32           lReaded = 0;       /* 读出的字节数 */
    VOS_INT32           lHlen = XML_MAP_MD5_HASH_LEN;
    VOS_INT32           lHashBufLen = 0;

    /* 读32K数据到缓冲区 */
    lReaded = (VOS_INT32)NV_File_Read((VOS_VOID *)pcXmlFileReadBuf, sizeof(VOS_CHAR), XML_CHECK_BUFF_SIZE, pfXmlFile);

    /*读取文件出现错误*/
    if (MDRV_ERROR == lReaded)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_READ_FILE);

        return XML_RESULT_FALIED_READ_FILE;
    }

    while (0 != lReaded)    /* 读出的字节数不是 0 */
    {
        lHlen = XML_MAP_MD5_HASH_LEN;

        /* 调用底软的函数计算分段hash值 */
        if (MDRV_OK != mdrv_crypto_hash(pcXmlFileReadBuf, lReaded, CRYPTO_ALGORITHM_MD5, pcSaveHashValueBuf + lHashBufLen, (VOS_INT *)&lHlen))
        {
            XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_FILE);

            return XML_RESULT_FALIED_BAD_FILE;
        }

        lHashBufLen += lHlen;

        /* 读32K数据到缓冲区 */
        lReaded = (VOS_INT32)NV_File_Read((VOS_VOID *)pcXmlFileReadBuf, sizeof(VOS_CHAR), XML_CHECK_BUFF_SIZE, pfXmlFile);

        /*读取文件出现错误*/
        if (MDRV_ERROR == lReaded)
        {
            XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_READ_FILE);

            return XML_RESULT_FALIED_READ_FILE;
        }
    }

    /* 调用底软的函数计算最后的hash值 */
    if (MDRV_OK != mdrv_crypto_hash(pcSaveHashValueBuf, lHashBufLen, CRYPTO_ALGORITHM_MD5, pucHash, (VOS_INT *)plHlen))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_FILE);

        return XML_RESULT_FALIED_BAD_FILE;
    }

    return XML_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_CalcXmlCheckValue
功能描述  : 计算xml文件的MD5校验值
输入参数  : pfXmlFile -- XML文件指针
输出参数  : pucHash -- 指向输出校验值的buff
            plHlen -- 校验值长度
返 回 值  : XML_RESULT_ENUM_UINT32

修改历史
1.日    期   : 2014年3月13日
  作    者   : 靳妮 00168360
  修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_CalcXmlCheckValue(VOS_CHAR *pcXmlFilePath, VOS_CHAR *pucHash, VOS_INT32 *plHlen)
{
    VOS_CHAR                    *pcXmlFileReadBuf = VOS_NULL_PTR;
    VOS_CHAR                    *pcSaveHashValueBuf = VOS_NULL_PTR;
    VOS_INT32                   lFileSize;
    FILE                        *pfXmlFile = VOS_NULL_PTR;
    XML_RESULT_ENUM_UINT32      ulReturnVal;

    /* 判断xnv.xml文件是否存在 */
    pfXmlFile = NV_File_Open(pcXmlFilePath, NV_FILE_OPEN_MODE_R);

    if (VOS_NULL_PTR == pfXmlFile)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_OPEN_FILE);

        return XML_RESULT_FALIED_OPEN_FILE;
    }

    NV_File_Seek(pfXmlFile, 0, NV_FILE_SEEK_END);

    lFileSize = NV_File_Tell(pfXmlFile);

    NV_File_Seek(pfXmlFile, 0, NV_FILE_SEEK_SET);

    if (lFileSize > XML_MAX_FILE_SIZE)
    {
        NV_File_Close(pfXmlFile);

        /* xml文件过大，大于64M */
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_FILE_TOO_BIG);

        return XML_RESULT_FALIED_FILE_TOO_BIG;
    }

    /* 申请读取文件数据的缓冲区 */
    pcXmlFileReadBuf = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_OM,
                                         DYNAMIC_MEM_PT, XML_CHECK_BUFF_SIZE);

    if (VOS_NULL_PTR == pcXmlFileReadBuf)
    {
        NV_File_Close(pfXmlFile);

        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    /* 申请存储分段的xml校验hash值的缓冲区 */
    pcSaveHashValueBuf = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_OM,
                                         DYNAMIC_MEM_PT, XML_CHECK_BUFF_SIZE);

    if (VOS_NULL_PTR == pcSaveHashValueBuf)
    {
        NV_File_Close(pfXmlFile);

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_OM, pcXmlFileReadBuf);
        /*lint +e534*/

        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    ulReturnVal = XML_CalcXmlMd5Value(pcXmlFileReadBuf, pcSaveHashValueBuf, pfXmlFile, pucHash, plHlen);

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_OM, pcSaveHashValueBuf);

    VOS_MemFree(WUEPS_PID_OM, pcXmlFileReadBuf);
    /*lint +e534*/

    NV_File_Close(pfXmlFile);

    return  ulReturnVal;
}

/*****************************************************************************
函 数 名  : XML_GetProductOffset
功能描述  : 获取产品在xnv.xml中对应的product cat偏移和product id偏移
输入参数  : pstOffset -- 指向map文件的数据部分
            ulNum -- 当前buffer中的产品数目
输出参数  : pstPrdtOffset--输出当前产品的偏移量
返 回 值  : XML_RESULT_ENUM_UINT32

修改历史
1.日    期   : 2014年3月13日
  作    者   : 靳妮 00168360
  修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_GetProductOffset(XML_XNV_PRDT_OFFSET_STRU *pstOffset, VOS_UINT32 ulNum, XML_XNV_PRDT_OFFSET_STRU *pstPrdtOffset)
{
    VOS_UINT32                          ulLow;
    VOS_UINT32                          ulHigh;
    VOS_UINT32                          ulMid;
    VOS_UINT32                          ulOffset;
    XML_XNV_PRDT_OFFSET_STRU            *pstTempOffset;

    ulHigh = ulNum;
    ulLow  = 1;

    /* Binary Search */
    while(ulLow <= ulHigh)
    {
        ulMid = (ulLow + ulHigh)/2;

        ulOffset = ulMid-1;

        pstTempOffset = pstOffset + ulOffset;

        if(pstPrdtOffset->ulPrdtID < pstTempOffset->ulPrdtID)
        {
            ulHigh = ulMid - 1;
        }
        else if(pstPrdtOffset->ulPrdtID > pstTempOffset->ulPrdtID)
        {
            ulLow = ulMid + 1;
        }
        else
        {
            /* 找到了产品ID，获取对应偏移量 */
            pstPrdtOffset->ulCatNodeOffset  = pstTempOffset->ulCatNodeOffset;
            pstPrdtOffset->ulPrdtNodeOffset = pstTempOffset->ulPrdtNodeOffset;

            return XML_RESULT_SUCCEED;
        }
    }

    pstPrdtOffset->ulCatNodeOffset  = VOS_NULL_DWORD;
    pstPrdtOffset->ulPrdtNodeOffset = VOS_NULL_DWORD;

    return XML_RESULT_FALIED_GET_PRODUCT_OFFSET;
}

/*****************************************************************************
函 数 名  : XML_SearchProductInfo
功能描述  : 查找当前产品在xnv.xml中对应的product cat偏移和product id偏移
输入参数  : pfMapFile -- 指向map文件
输出参数  : pstPrdtOffset--指向产品信息结构
返 回 值  : XML_RESULT_ENUM_UINT32

修改历史
1.日    期   : 2014年3月13日
  作    者   : 靳妮 00168360
  修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_SearchProductInfo(FILE* pfMapFile, XML_XNV_PRDT_OFFSET_STRU *pstPrdtOffset)
{
    VOS_INT32                   lReaded = 0;       /* 读出的字节数 */
    VOS_UINT32                  ulNum;
    VOS_INT                     lProductId;
    XML_XNV_PRDT_OFFSET_STRU    *pstOffset = VOS_NULL_PTR;
    XML_RESULT_ENUM_UINT32      ulReturnVal;

    /* 取得当前单板的Product id */
    lProductId = (mdrv_ver_get_info()->sthwverinfo).hwindex;

    if(VOS_ERROR == lProductId)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_GET_PRODUCTID);

        return XML_RESULT_FALIED_GET_PRODUCTID;
    }

    /* 保存产品ID */
    pstPrdtOffset->ulPrdtID = (VOS_UINT32)lProductId;

    if(VOS_OK != NV_File_Seek(pfMapFile, sizeof(XML_XNV_MAP_HEAD_STRU), NV_FILE_SEEK_SET))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_SEEK_FILE);

        return XML_RESULT_FALIED_SEEK_FILE;
    }

    lReaded = (VOS_INT32)NV_File_Read((VOS_VOID *)g_pcFileReadBuff,
                                      sizeof(VOS_CHAR),
                                     (XML_FILE_READ_BUFF_SIZE / sizeof(XML_XNV_PRDT_OFFSET_STRU)) * sizeof(XML_XNV_PRDT_OFFSET_STRU),
                                      pfMapFile);

    /*读取文件出现错误*/
    if (MDRV_ERROR == lReaded)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_READ_FILE);

        return XML_RESULT_FALIED_READ_FILE;
    }

    while(0 != lReaded)
    {
        ulNum = (VOS_UINT32)lReaded / sizeof(XML_XNV_PRDT_OFFSET_STRU);

        pstOffset = (XML_XNV_PRDT_OFFSET_STRU *)g_pcFileReadBuff;

        /* 当前产品ID比读到缓冲区中的id最小值还小，则查找失败 */
        if (pstPrdtOffset->ulPrdtID < pstOffset->ulPrdtID)
        {
            pstPrdtOffset->ulCatNodeOffset  = VOS_NULL_DWORD;
            pstPrdtOffset->ulPrdtNodeOffset = VOS_NULL_DWORD;

            return XML_RESULT_FALIED_GET_PRODUCT_OFFSET;
        }

        /* 当前产品ID比读到缓冲区中的id最大值小，则在本次读到的数据中二分法查找 */
        if (pstPrdtOffset->ulPrdtID <= (pstOffset + (ulNum -1))->ulPrdtID)
        {
            /* 二分法查找 */
            ulReturnVal = XML_GetProductOffset(pstOffset, ulNum, pstPrdtOffset);

            return ulReturnVal;
        }

        /* 本次读到的数据中没有当前产品信息，继续读 */
        lReaded = (VOS_INT32)NV_File_Read((VOS_VOID *)g_pcFileReadBuff,
                                          sizeof(VOS_CHAR),
                                         (XML_FILE_READ_BUFF_SIZE / sizeof(XML_XNV_PRDT_OFFSET_STRU)) * sizeof(XML_XNV_PRDT_OFFSET_STRU),
                                          pfMapFile);


        /*读取文件出现错误*/
        if (MDRV_ERROR == lReaded)
        {
            XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_READ_FILE);

            return XML_RESULT_FALIED_READ_FILE;
        }
    }

    /* 该情况也属于没找到对应的product id */
    pstPrdtOffset->ulCatNodeOffset  = VOS_NULL_DWORD;
    pstPrdtOffset->ulPrdtNodeOffset = VOS_NULL_DWORD;

    return XML_RESULT_FALIED_GET_PRODUCT_OFFSET;
}

/*****************************************************************************
函 数 名  : XML_DecodeMapFile
功能描述  : 解析产品索引文件，获取产品在xnv.xml中对应的product cat偏移和product id偏移
输入参数  : pcMapFilePath -- 指向要解析的map文件路径
            pcXmlFilePath -- 指向要解析的xml文件路径
输出参数  : pstPrdtOffset -- 指向产品信息结构
            pulProductNum -- 指向当前产品数
返 回 值  : XML_RESULT_ENUM_UINT32

修改历史
1.日    期   : 2014年3月13日
  作    者   : 靳妮 00168360
  修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_DecodeMapFile(VOS_CHAR *pcMapFilePath, VOS_CHAR *pcXmlFilePath, VOS_UINT32  *pulProductNum, XML_XNV_PRDT_OFFSET_STRU *pstPrdtOffset)
{
    XML_RESULT_ENUM_UINT32      ulReturnVal;
    XML_XNV_MAP_HEAD_STRU       stMapHeader;
    VOS_INT32                   lReaded = 0;       /* 读出的字节数 */
#ifdef XML_CHECK_MD5
    VOS_CHAR                    aucHash[XML_MAP_MD5_HASH_LEN] = {0};
    VOS_INT32                   lHlen = XML_MAP_MD5_HASH_LEN;
#endif
    FILE                        *pfMapFile = VOS_NULL_PTR;
    VOS_UINT32                  ulFileLen;

    /*lint -e534*/
    VOS_MemSet(&stMapHeader, 0, sizeof(stMapHeader));
    /*lint +e534*/

    /* 打开索引文件 */
    /* 判断xnv.map文件是否存在 */
    pfMapFile = NV_File_Open(pcMapFilePath, NV_FILE_OPEN_MODE_R);

    if (VOS_NULL_PTR == pfMapFile)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_OPEN_FILE);

        return XML_RESULT_FALIED_OPEN_FILE;
    }

    /* 获取文件大小 */
    NV_File_Seek(pfMapFile, 0, NV_FILE_SEEK_END);

    ulFileLen = (VOS_UINT32)NV_File_Tell(pfMapFile);

    NV_File_Seek(pfMapFile, 0, NV_FILE_SEEK_SET);

    /* 读MAP文件头24个字节数据到缓冲区 */
    lReaded = (VOS_INT32)NV_File_Read((VOS_VOID *)&stMapHeader, sizeof(VOS_CHAR), sizeof(XML_XNV_MAP_HEAD_STRU), pfMapFile);

    /*读取文件出现错误*/
    if (MDRV_ERROR == lReaded)
    {
        NV_File_Close(pfMapFile);

        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_READ_FILE);

        return XML_RESULT_FALIED_READ_FILE;
    }

    /* 判断文件标识码 */
    if (XML_MAP_FILE_MAGIC_NUM != stMapHeader.ulMagNumber)
    {
        NV_File_Close(pfMapFile);

        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_MAGIC_NUM);

        return XML_RESULT_FALIED_BAD_MAGIC_NUM;
    }

    /* 判断文件大小与product id个数是否匹配 */
    if (sizeof(XML_XNV_MAP_HEAD_STRU) + stMapHeader.ulProductNum * sizeof(XML_XNV_PRDT_OFFSET_STRU) != ulFileLen)
    {
        NV_File_Close(pfMapFile);

        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_FILE);

        return XML_RESULT_FALIED_BAD_FILE;
    }

/* 是否要进行MD5校验 */
#ifdef XML_CHECK_MD5
    /* 判断xnv.xml校验是否ok */
    if (XML_RESULT_SUCCEED != XML_CalcXmlCheckValue(pcXmlFilePath, aucHash, &lHlen))
    {
        NV_File_Close(pfMapFile);

        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_FILE);

        return XML_RESULT_FALIED_BAD_FILE;
    }

    /* 比较校验值 */
    if (VOS_OK != VOS_MemCmp(aucHash, (VOS_CHAR *)stMapHeader.aulXnvMD5, (VOS_UINT32)lHlen))
    {
        NV_File_Close(pfMapFile);

        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_FILE);

        return XML_RESULT_FALIED_BAD_FILE;
    }
#endif

    *pulProductNum = stMapHeader.ulProductNum;

    /* 查找产品在xml文件中的偏移量 */
    ulReturnVal = XML_SearchProductInfo(pfMapFile, pstPrdtOffset);

    NV_File_Close(pfMapFile);

    return ulReturnVal;
}

/*****************************************************************************
函 数 名  : XML_DecodeProductCatXMLFile
功能描述  : 解析支持PRODUCT CAT的xml文件
输入参数  : lFile -- 指向打开的文件描述符
            ulProductNum -- 当前map文件中支持的产品数
            pstPrdtOffset -- 指向当前产品的偏移量
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32

修改历史
1.日    期   : 2014年3月13日
  作    者   : 靳妮 00168360
  修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_DecodeProductCatXMLFile(FILE* pfFile, VOS_UINT32 ulProductNum, XML_XNV_PRDT_OFFSET_STRU *pstPrdtOffset)
{
    VOS_INT32                   lReaded = 0;       /* 读出的字节数 */
    VOS_INT32                   lCount;            /* 遍历缓冲区用 */
    XML_RESULT_ENUM_UINT32      ulReturnVal;

    /* 读4K数据到缓冲区 */
    lReaded = (VOS_INT32)NV_File_Read((VOS_VOID *)g_pcFileReadBuff, sizeof(VOS_CHAR), XML_FILE_READ_BUFF_SIZE, pfFile);

    /*读取文件出现错误*/
    if (MDRV_ERROR == lReaded)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_READ_FILE);

        return XML_RESULT_FALIED_READ_FILE;
    }

    while (0 != lReaded)    /* 读出的字节数不是 0 */
    {
        /* 逐个字符进行处理 */
        for (lCount = 0; lCount < lReaded; lCount++)
        {
            /* 开始解析 */
            ulReturnVal = XML_Analyse(*(g_pcFileReadBuff + lCount));

            if(XML_RESULT_SUCCEED != ulReturnVal)
            {
                /* 遇到解析错误，则停止解析 */
                return ulReturnVal;
            }

            /* 公共部分解析完成后跳出循环 */
            if (XML_PRODUCT_COMMON_ANALYZE_FINISH == g_enProductDecodeStatus)
            {
                if((0 == ulProductNum) || (VOS_NULL_DWORD == pstPrdtOffset->ulCatNodeOffset))
                {
                    g_stXMLProductInfo.enXMLDecodeState = XML_DECODE_STATUS_FINISHED;

                    return XML_RESULT_SUCCEED;
                }

                if(VOS_OK != NV_File_Seek(pfFile, (VOS_INT32)pstPrdtOffset->ulCatNodeOffset, NV_FILE_SEEK_SET))
                {
                    XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_SEEK_FILE);

                    return XML_RESULT_FALIED_SEEK_FILE;
                }

                g_enProductDecodeStatus = XML_PRODUCT_CAT_ANALYZE_START;

                break;
            }

            if (XML_PRODUCT_CAT_ANALYZE_FINISH == g_enProductDecodeStatus)
            {
                if(VOS_NULL_DWORD == pstPrdtOffset->ulPrdtNodeOffset)
                {
                    g_stXMLProductInfo.enXMLDecodeState = XML_DECODE_STATUS_FINISHED;

                    return XML_RESULT_SUCCEED;
                }

                if(VOS_OK != NV_File_Seek(pfFile, (VOS_INT32)pstPrdtOffset->ulPrdtNodeOffset, NV_FILE_SEEK_SET))
                {
                    XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_SEEK_FILE);

                    return XML_RESULT_FALIED_SEEK_FILE;
                }

                g_enProductDecodeStatus = XML_PRODUCT_ID_ANALYZE_START;

                break;
            }

            /* 判断是否解析完成 */
            if (XML_DECODE_STATUS_FINISHED == g_stXMLProductInfo.enXMLDecodeState)
            {
                return XML_RESULT_SUCCEED;
            }
        }

        /* 读下一批数据 */
        lReaded = (VOS_INT32)NV_File_Read((VOS_VOID *)g_pcFileReadBuff, sizeof(VOS_CHAR),
                                XML_FILE_READ_BUFF_SIZE, pfFile);

        /*读取文件出现错误*/
        if (MDRV_ERROR == lReaded)
        {
            XML_WriteErrorLog(__LINE__,0,XML_RESULT_FALIED_READ_FILE);

            return XML_RESULT_FALIED_READ_FILE;
        }
    }/* end of while (0 != lReaded) */

    return XML_RESULT_FALIED_BAD_FILE;
}
#endif

/*****************************************************************************
函 数 名  : XML_DecodeXMLFile
功能描述  : 读取XML文件数据，进行解析
输入参数  : lFile指打开的文件描述符
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : mdrv_file_read
            mdrv_file_close
            XML_Analyse
            XML_WriteErrorLog
被调函数  : XML_DecodeMain

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_DecodeXMLFile(FILE* pfFile)
{
    VOS_INT32               lReaded = 0;       /* 读出的字节数 */
    VOS_INT32               lCount;            /* 遍历缓冲区用 */
    XML_RESULT_ENUM_UINT32  ulReturnVal;

    /* 读4K数据到缓冲区 */
    lReaded = (VOS_INT32)NV_File_Read((VOS_VOID *)g_pcFileReadBuff, sizeof(VOS_CHAR), XML_FILE_READ_BUFF_SIZE, pfFile);

    /*读取文件出现错误*/
    if (MDRV_ERROR == lReaded)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_READ_FILE);

        return XML_RESULT_FALIED_READ_FILE;
    }

    while (0 != lReaded)    /* 读出的字节数不是 0 */
    {
        /* 逐个字符进行处理 */
        for (lCount = 0; lCount < lReaded; lCount++)
        {
            /* 开始解析 */
            ulReturnVal = XML_Analyse(*(g_pcFileReadBuff + lCount));

            if(XML_RESULT_SUCCEED != ulReturnVal)
            {
                /* 遇到解析错误，则停止解析 */
                return ulReturnVal;
            }

            /* 判断是否解析完成 */
            if (XML_DECODE_STATUS_FINISHED
                == g_stXMLProductInfo.enXMLDecodeState)
            {
                return XML_RESULT_SUCCEED;
            }
        }

        /* 读下一批数据 */
        lReaded = (VOS_INT32)NV_File_Read((VOS_VOID *)g_pcFileReadBuff, sizeof(VOS_CHAR),
                                XML_FILE_READ_BUFF_SIZE, pfFile);

        /*读取文件出现错误*/
        if (MDRV_ERROR == lReaded)
        {
            XML_WriteErrorLog(__LINE__,0,XML_RESULT_FALIED_READ_FILE);

            return XML_RESULT_FALIED_READ_FILE;
        }
    }/* end of while (0 != lReaded) */

    /* 如果ulNodeLevel不为0，说明<product>没有正常结束 */
    if (0 != g_stXMLProductInfo.ulNodeLevel)
    {
        XML_WriteErrorLog(__LINE__,0,XML_RESULT_FALIED_PRODUCT_MATCH);

        return XML_RESULT_FALIED_PRODUCT_MATCH;
    }

    return XML_RESULT_SUCCEED;
}


/*****************************************************************************
函 数 名  : XML_GetProductId
功能描述  : 获得当前单板的product id
输入参数  : 无
输出参数  : pcProductId 获得当前单板的product ids
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : VOS_MemSet
            DRV_MEM_VERCTRL
            XML_WriteErrorLog
被调函数  : XML_ProcInit

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_GetProductId(VOS_VOID)
{
    VOS_INT                             lProductId;

    /* 清空内存 */
    /*lint -e534*/
    VOS_MemSet(g_stXMLProductInfo.acProductId, 0, XML_MAX_HARDWARE_LEN);
    /*lint +e534*/

    /* 取得当前单板的Product id */
    lProductId = (mdrv_ver_get_info()->sthwverinfo).hwindex;

#if (VOS_OS_VER == VOS_WIN32)
    /*lint -e534*/
    /* 因snprintf 在 windows 上区别，windows 不带 "\0" 所以 少打印一位。*/
    _snprintf(g_stXMLProductInfo.acProductId, (sizeof(g_stXMLProductInfo.acProductId) - 1), "%d", lProductId);
    /*lint +e534*/

#else
    /*lint -e534*/
    snprintf(g_stXMLProductInfo.acProductId, sizeof(g_stXMLProductInfo.acProductId), "%d", lProductId);
    /*lint +e534*/
#endif

    NV_Printf("XML_GetProductId: Product id is :%s\r\n", g_stXMLProductInfo.acProductId);

    return XML_RESULT_SUCCEED;
}


/*****************************************************************************
函 数 名  : XML_InitGlobal
功能描述  : 初始化全局变量
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : XML_ProcInit

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID XML_InitGlobal(VOS_VOID)
{
    /* 初始化Product节点信息 */
    g_stXMLProductInfo.enValidNode      = XML_PRODUCT_NODE_STATUS_INVALID;
    g_stXMLProductInfo.enXMLDecodeState = XML_DECODE_STATUS_DECODING;
    g_stXMLProductInfo.ulNodeLevel      = 0; /* 记录product节点出现的次数 */

    /* 初始化当前状态 */
    g_ulXMLStatus = XML_ANASTT_ORIGINAL;

    /* 用于记录读取XML文件的行数 */
    g_ulLineNo    = 1;

#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
    g_enProductDecodeStatus = XML_PRODUCT_ANALYZE_START;
#endif

    return ;
}


/*****************************************************************************
函 数 名  : XML_ProcInit
功能描述  : 初时化本模块全部变量内容
输入参数  : 无
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_InitGlobal
            XML_GetProductId
            XML_CreateANode
            VOS_MemAlloc
            XML_WriteErrorLogs
被调函数  : XML_DecodeMain

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_ProcInit(VOS_VOID)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal;

    /* 初始化全局变量 */
    XML_InitGlobal();

    /* 获得当前单板的product id*/
    ulReturnVal = XML_GetProductId();

    if (XML_RESULT_SUCCEED != ulReturnVal)
    {
        return ulReturnVal;
    }

    /* 创建节点信息 */
    ulReturnVal = XML_CreateANode();

    if (XML_RESULT_SUCCEED != ulReturnVal)
    {
        return ulReturnVal;
    }

    /* 申请存放NV Item的值的缓冲区,+1为保留字符串结束符用 */
    g_pucNVItem = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_OM,
                                         DYNAMIC_MEM_PT,
                                         XML_NODE_VALUE_BUFF_LENGTH_ORIGINAL+1);
    if (VOS_NULL_PTR == g_pucNVItem)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    /* 申请读取文件数据的缓冲区,+1为保留字符串结束符用 */
    g_pcFileReadBuff = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_OM,
                                                DYNAMIC_MEM_PT,
                                                XML_FILE_READ_BUFF_SIZE+1);
    if (VOS_NULL_PTR == g_pcFileReadBuff)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    g_stXmlErrorInfo.ulResult = XML_RESULT_SUCCEED;

    return XML_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_FreeMem
功能描述  : XML 释放内存函数
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : XML_DecodeMain

修改历史
1.日    期   : 2011年04月14日
作    者   : x51137
修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID XML_FreeMem(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_OM, g_stXMLCurrentNode.stProperty.pcPropertyName);

    VOS_MemFree(WUEPS_PID_OM, g_stXMLCurrentNode.stProperty.pcPropertyValue);

    VOS_MemFree(WUEPS_PID_OM, g_stXMLCurrentNode.pcNodeLabel);

    VOS_MemFree(WUEPS_PID_OM, g_stXMLCurrentNode.pcNodeLabelEnd);

    VOS_MemFree(WUEPS_PID_OM, g_stXMLCurrentNode.pcNodeValue);

    VOS_MemFree(WUEPS_PID_OM, g_pucNVItem);

    VOS_MemFree(WUEPS_PID_OM, g_pcFileReadBuff);
    /*lint +e534*/
}

/*****************************************************************************
 函 数 名  : XML_OpenAndDecodeXMLFile
 功能描述  : 打开并解析xml文件
 输入参数  : 需要打开XML的文件路径

 输出参数  : 无

 返 回 值  : XML_RESULT_ENUM_UINT32

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : V9R1 XML扩展
*****************************************************************************/
XML_RESULT_ENUM_UINT32 XML_OpenAndDecodeXMLFile(VOS_CHAR *pcFilePath)
{
    FILE                               *pFile  = VOS_NULL_PTR;
    XML_RESULT_ENUM_UINT32              ulReturnVal;

    pFile = NV_File_Open(pcFilePath, NV_FILE_OPEN_MODE_R);

    if (VOS_NULL_PTR == pFile)
    {
        NV_Printf("XML_OpenAndDecodeXMLFile: Open %s fail：\r\n ", pcFilePath);

        return XML_RESULT_FALIED_FILE_OPERATE;
    }

    /* 进行下一个XML文件解析时，重置全局变量的状态 */
    XML_InitGlobal();

    ulReturnVal = XML_DecodeXMLFile(pFile);

    /* 关闭文件 */
    /*lint -e534*/
    mdrv_file_close(pFile);
    /*lint +e534*/

    if (XML_RESULT_SUCCEED != ulReturnVal)
    {
        /* 如果解析失败,则单板异常重启 */
        mdrv_om_system_error(FAIL_TO_DECODE_XML, VOS_FILE_ID, __LINE__,
                             (VOS_CHAR *)&g_stXmlErrorInfo,
                             sizeof(g_stXmlErrorInfo));
        NV_Printf("XML_OpenAndDecodeXMLFile: Decode  %s fail.\r\n", pcFilePath);

        return ulReturnVal;
    }

    return XML_RESULT_SUCCEED;
}

/*****************************************************************************
 函 数 名  : XML_DecodeOperator
 功能描述  : operator.xml 解析写入NV 内存
 输入参数  : pbIsDecodeXml 是否有XML需解析

 输出参数  : 无

 返 回 值  : VOS_VOID

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : V9R1 XML扩展
*****************************************************************************/
VOS_VOID XML_DecodeOperator(VOS_BOOL *pbIsDecodeXml)
{
#if (FEATURE_ON == FEATURE_S_SKU_M_OPERATORS)
    VOS_CHAR                            acFilePath[NV_MAX_PATH_SIZE] = {0};
    XML_RESULT_ENUM_UINT32              ulReturnVal;

    /* 获取operator.xml全路径 */
    if (VOS_OK != NV_SkuGetOperatorPath(acFilePath))
    {
        NV_Printf("XML_DecodeOperator: Get operator.xml file path fail.\r\n");
        return;
    }

    ulReturnVal = XML_OpenAndDecodeXMLFile(acFilePath);

    if((XML_RESULT_SUCCEED != ulReturnVal) && (XML_RESULT_FALIED_FILE_OPERATE != ulReturnVal))
    {
        NV_Printf("XML_DecodeOperator: xml decode fail %d", ulReturnVal);
        return;
    }

    *pbIsDecodeXml = VOS_TRUE;

#endif

    return;
}

/*****************************************************************************
函 数 名  : XML_DecodeMain
功能描述  : XML处理主调函数
输入参数  : pbIsDecodeXml 是否有XML需解析
输出参数  : pbIsDecodeXml
返 回 值  : 无
调用函数  : mdrv_file_open
            mdrv_file_close
            mdrv_file_remove
            mdrv_om_system_error
            VOS_FlowReboot
            XML_ProcInit
            XML_InitGlobal
            XML_DecodeXMLFile
            XML_WriteErrorLog
被调函数  : NV_UpdateProc()/NV_RestoreManufactureProc()

修改历史
1.日    期   : 2010年12月20日
作    者     : 郑继树 176513
修改内容     : 新生成函数
*****************************************************************************/
VOS_VOID XML_DecodeMain(VOS_BOOL *pbIsDecodeXml)
{
    VOS_INT32                   lExistXNVFile  = VOS_FALSE;
    VOS_INT32                   lExistCUSTFile = VOS_FALSE;
    XML_RESULT_ENUM_UINT32      ulReturnVal;
    VOS_UINT32                  i;
#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
    XML_XNV_PRDT_OFFSET_STRU    stPrdtOfffset;
    VOS_UINT32                  ulProductNum;
#endif

    /* 初时化本模块全部变量内容 */
    ulReturnVal = XML_ProcInit();

    if (XML_RESULT_SUCCEED != ulReturnVal)
    {
        /* 如果初始化失败,则单板异常重启 */
        mdrv_om_system_error(FAIL_TO_DECODE_XML, VOS_FILE_ID, __LINE__,
                             (VOS_CHAR *)&g_stXmlErrorInfo,
                             sizeof(g_stXmlErrorInfo));

        return;
    }

    for (i=0; i<(sizeof(g_astXMLFilePath)/sizeof(g_astXMLFilePath[0])); i++)
    {
#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
        /*lint -e534*/
        VOS_MemSet(&stPrdtOfffset, 0, sizeof(stPrdtOfffset));
        /*lint +e534*/

        ulReturnVal = XML_DecodeMapFile(g_astMapFilePath[i].pcMapPath, g_astXMLFilePath[i].pcXNVPath, &ulProductNum, &stPrdtOfffset);

        if ((XML_RESULT_SUCCEED != ulReturnVal) && (XML_RESULT_FALIED_GET_PRODUCT_OFFSET != ulReturnVal))
        {
            continue;
        }
#endif
        lExistXNVFile  = VOS_FALSE;
        lExistCUSTFile = VOS_FALSE;

        /* 判断xnv.XML文件是否存在 */
        g_lEnvFile = mdrv_file_open(g_astXMLFilePath[i].pcXNVPath, NV_FILE_OPEN_MODE_R);

        if (VOS_NULL_PTR != g_lEnvFile)
        {
            lExistXNVFile = VOS_TRUE;
        }

        /* 判断CUST.XML文件是否存在 */
        g_lCustFile = mdrv_file_open(g_astXMLFilePath[i].pcCUSTPath, NV_FILE_OPEN_MODE_R);

        if (VOS_NULL_PTR != g_lCustFile)
        {
            lExistCUSTFile = VOS_TRUE;
        }

        /* 如果ENV.xml和cust.xml都不存在,则直接返回 */
        if ((VOS_FALSE == lExistXNVFile) && (VOS_FALSE == lExistCUSTFile))
        {
            continue;
        }

        /* 保存当前操作的modem ID */
        g_enXMLCurModemID   = (VOS_UINT16)i;

        /* 解析xnv.xml文件  */
        if (VOS_TRUE == lExistXNVFile)
        {
#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
            /* 解析支持产品cat的xnv.xml*/
            ulReturnVal = XML_DecodeProductCatXMLFile(g_lEnvFile, ulProductNum, &stPrdtOfffset);
#else
            ulReturnVal = XML_DecodeXMLFile(g_lEnvFile);
#endif
            /* 关闭文件 */
            /*lint -e534*/
            mdrv_file_close(g_lEnvFile);
            /*lint +e534*/

            g_lEnvFile = VOS_NULL_PTR;

            if (XML_RESULT_SUCCEED != ulReturnVal)
            {
                /* 释放已分配的内存 */
                XML_FreeMem();

                /* 如果解析失败,则单板异常重启 */
                mdrv_om_system_error(FAIL_TO_DECODE_XML, VOS_FILE_ID, __LINE__,
                                     (VOS_CHAR *)&g_stXmlErrorInfo,
                                     sizeof(g_stXmlErrorInfo));

                return;
            }

            *pbIsDecodeXml = VOS_TRUE;

        }

        /* 解析cust.xml文件 */
        if (VOS_TRUE == lExistCUSTFile)
        {
            /* 进行下一个XML文件解析时，重置全局变量的状态 */
            XML_InitGlobal();

            ulReturnVal = XML_DecodeXMLFile(g_lCustFile);

            /* 关闭文件 */
            /*lint -e534*/
            mdrv_file_close(g_lCustFile);
            /*lint +e534*/

            g_lCustFile = VOS_NULL_PTR;

            if (XML_RESULT_SUCCEED != ulReturnVal)
            {
                /* 释放已分配的内存 */
                XML_FreeMem();

                /* 如果解析失败,则单板异常重启 */
                mdrv_om_system_error(FAIL_TO_DECODE_XML, VOS_FILE_ID, __LINE__,
                                     (VOS_CHAR *)&g_stXmlErrorInfo,
                                     sizeof(g_stXmlErrorInfo));

                return;
            }

            *pbIsDecodeXml = VOS_TRUE;

        }

        /* 进行下一个XML文件解析时，重置全局变量的状态 */
        XML_InitGlobal();
    }

    /* operator.xml 文件解析 */
    XML_DecodeOperator(pbIsDecodeXml);

    /* 释放已分配的内存 */
    XML_FreeMem();

    return;
}

/*****************************************************************************
 函 数 名  : XML_DeleteFile
 功能描述  : xml 文件删除
 输入参数  : 无

 输出参数  : 无

 返 回 值  : VOS_VOID

 修改历史      :
  1.日    期   : 2013年8月12日
    作    者   : d00212987
    修改内容   : 新增
*****************************************************************************/
VOS_VOID XML_DeleteFile(VOS_VOID)
{
    VOS_UINT32              i;

    if(XML_RESULT_SUCCEED != g_stXmlErrorInfo.ulResult)
    {
        /* xml解析异常 */
        return;
    }

    for(i=0; i<(sizeof(g_astXMLFilePath)/sizeof(g_astXMLFilePath[0])); i++)
    {
        /* 删除xnv文件 */
        mdrv_file_remove(g_astXMLFilePath[i].pcXNVPath);

        /* 删除cust文件 */
        mdrv_file_remove(g_astXMLFilePath[i].pcCUSTPath);

#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
        /* 删除map文件 */
        mdrv_file_remove(g_astMapFilePath[i].pcMapPath);
#endif
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

