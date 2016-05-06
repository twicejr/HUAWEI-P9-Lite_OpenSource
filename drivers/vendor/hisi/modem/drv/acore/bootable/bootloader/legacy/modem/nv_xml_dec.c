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

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif


/*****************************************************************************
1 头文件包含
*****************************************************************************/
/*lint -save -e537*/
#include "nv_xml_dec.h"
#include <nv_boot.h>
#include <bsp_version.h>
/*lint -restore +e537*/

extern int strcmp(const char *a, const char *b);
/*lint -save -e838 -e801*/
/*****************************************************************************
2 全局变量定义
*****************************************************************************/

/*lint -save -e958*/
/*xml decode info*/
static XML_DOCODE_INFO xml_ctrl;

/* XML关键字,不包括0-9,a-z,A-Z */
static s8   g_stlxmkeywordtbl[] = { '<', '>', '/', '=', '"',
                                   ' ', '!', '?', '_', '-',
                                   ',' };

/* XML文件解析时的状态                  */
static XML_ANALYSE_STATUS_ENUM_UINT32 g_stlxmlstatus = XML_ANASTT_ORIGINAL;

/* 共通节点名称                         */
static s8 g_aclnodelabelcommon[]               = "common_NvInfo";

/* Product节点名称                      */
static s8 g_aclnodelabelproduct[]              = "product";

/* Product_NvInfo节点名称                      */
static s8 g_aclnodelabelproductNvInfo[]          = "product_NvInfo";

/* NV节点名称                           */
static s8 g_aclnodelabelnv[]                   = "nv";

/* Cust节点名称                         */
static s8 g_aclnodelabelcust[]                 = "cust";

/* NV id属性名称                           */
static s8 g_aclpropertyId[]                   = "id";

/* NV 优先级属性名称                          */
static s8 g_aclpropertyWp[]                   = "wp";


/* 节点十六进制值之间的分隔符           */
static s8 g_separator                        = ',';

/*****************************************************************************
3 函数定义
*****************************************************************************/
/*****************************************************************************
函 数 名  : XML_WriteErrorLog
功能描述  : 记录错误信息到Log文件
输入参数  : ulErrLine 指出错时的代码行号
          : ulnvid    指出错时对应的NV ID
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
/*lint -save -e958*/
void xml_write_error_log(u32 ulerrorline, u16 ulnvid,
                                u32 ret)
{
    xml_ctrl.g_stlxmlerrorinfo.ulxmlline = xml_ctrl.g_stlxml_lineno;
    xml_ctrl.g_stlxmlerrorinfo.ulstatus  = g_stlxmlstatus;
    xml_ctrl.g_stlxmlerrorinfo.ulcodeline= ulerrorline;
    xml_ctrl.g_stlxmlerrorinfo.usnvid    = ulnvid;
    xml_ctrl.g_stlxmlerrorinfo.ulresult  = (u32)ret;

    return ;
}
/*lint -restore +e958*/

/*****************************************************************************
函 数 名  : XML_CheckXMLKeyWord
功能描述  : 检查当前字符的是否是XML关键字
输入参数  : currentchar 指当前字符
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : 无
被调函数  : XML_CheckCharValidity

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_checkxmlkeyword(s8 currentchar)
{
    u32 lcount;

    if ((('0' <= currentchar) && ('9' >= currentchar))   /* 有效字符：0-9  */
        ||(('a' <= currentchar) && ('z' >= currentchar)) /* 有效字符：a-z  */
        ||(('A' <= currentchar) && ('Z' >= currentchar)))/* 有效字符：A-Z  */
    {
        return XML_RESULT_SUCCEED;
    }
/*lint -save -e958*/
    /* 除 0-9,a-z,A-Z 之外的 XML关键字 */
    for (lcount=0; lcount<sizeof(g_stlxmkeywordtbl); lcount++)
    {
        if (currentchar == g_stlxmkeywordtbl[lcount])
        {
            return XML_RESULT_SUCCEED;
        }
    }
/*lint -restore +e958*/
    printf("<%s>: err char :%c\n",__func__,currentchar);
    return XML_RESULT_FALIED_BAD_CHAR;
}


/*****************************************************************************
函 数 名  : XML_CheckCharValidity
功能描述  : 检查当前字符的有效性
输入参数  : currentchar 指当前字符
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
/*lint -save -e958*/
XML_RESULT_ENUM_UINT32 xml_checkcharvalidity(s8 currentchar)
{
    XML_RESULT_ENUM_UINT32 returnval;

    if (('\r' == currentchar)       /* 忽略回车   */
        || ('\t' == currentchar))   /* 忽略制表符 */
    {
        return XML_RESULT_SUCCEED_IGNORE_CHAR;
    }

    if ('\n' == currentchar)    /* 忽略换行   */
    {
        xml_ctrl.g_stlxml_lineno++;
        return XML_RESULT_SUCCEED_IGNORE_CHAR;
    }

    /* 在注释中的字符不做检查 */
    if ( XML_ANASTT_IGNORE == g_stlxmlstatus)
    {
        return XML_RESULT_SUCCEED;
    }

    /* 检查XML的关键字 */
    returnval = xml_checkxmlkeyword(currentchar);
    if (XML_RESULT_SUCCEED != returnval)
    {
        printf("returnval = %d\n",returnval);
        xml_write_error_log(__LINE__, 0, returnval);

        return returnval;
    }

    return XML_RESULT_SUCCEED;
}
/*lint -restore +e958*/
/*****************************************************************************
函 数 名  : XML_StringToNvId
功能描述  : 把字符串转成十进制的格式
输入参数  : pcbuff 指字符串缓冲区
输出参数  : pusretval 指转换后的返回值
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_WriteErrorLog
被调函数  : XML_WriteNVItem

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_stringtou16(s8  *pcbuff,
                                            u16 *pusretval)
{
    u32 ultemp = 0;  /* 字符串转成整型时的中间变量 */
    s8   currentchar;
    s8  *pcsrc;

    pcsrc = pcbuff;

    /* 如果NV ID是空的，则返回错误 */
    if (0 == *pcsrc)
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_NV_ID_IS_NULL);

        return XML_RESULT_FALIED_NV_ID_IS_NULL;
    }

    /* 把字符串转成十进制的格式 */
    while (0 != *pcsrc)
    {
        currentchar = *pcsrc;

        /* 对不在0－9之间的字符，按错误处理 */
        if ((currentchar < '0') || (currentchar > '9'))
        {
            xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_0_9);
            return XML_RESULT_FALIED_OUT_OF_0_9;
        }

        /* 转成十进制格式 */
        currentchar -= '0';
        ultemp = (ultemp*10) + (u8)currentchar;

        /* 超出NV ID的最大值 */
        if (EN_NV_ID_END <= ultemp)
        {
            xml_write_error_log(__LINE__, (u16)ultemp, XML_RESULT_FALIED_OUT_OF_MAX_VALUE);

            return XML_RESULT_FALIED_OUT_OF_MAX_VALUE;
        }

        pcsrc++;
    }

    /* 输出 转换后的值 */
    *pusretval = (u16)ultemp;

    return XML_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_StringToHex
功能描述  : 把字符转成十六进制的格式
输入参数  : pucsrc 待转换的字符串
输出参数  : pucdest转换后的数据
          : pucdestLen 转换后的数据长度
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : XML_WriteErrorLog
被调函数  : XML_StringToNvValue

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_stringtohex(u8 *pucsrc, u8 *pucdest)
{
    u8  ucurrent;
    u8  uctemp  = 0;
    u16 uscount = 0;

    /* pucsrc的长度一定是偶数,由输入的参数保证 */
    while (0 != *pucsrc)
    {
        ucurrent = *pucsrc;

        if ((ucurrent >= 'a') && (ucurrent <= 'f'))
        {
            /* 将小写字符转成大写*/
            ucurrent -= 'a'-'A';
        }

        /* 转成十六进制格式 */
        if ((ucurrent >= 'A') && (ucurrent <= 'F'))
        {
            uscount++;
            uctemp = (u8)(uctemp * 16) + (u8)(ucurrent - 'A') + 10;
        }
        else if ((ucurrent >= '0') && (ucurrent <= '9'))
        {
            uscount++;
            uctemp = (u8)(uctemp * 16) + (u8)(ucurrent - '0');
        }
        else
        {
            /* 对不在0-9,a-f,A-F之间的字符，按错误处理 */
            xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_0_F);

            return XML_RESULT_FALIED_OUT_OF_0_F;
        } /* end of if ((ucurrent >= 'a') && (ucurrent <= 'f')) */

        /* 将2个字符转换成一个十六进制后,保存到目标缓冲区中 */
        if (2 == uscount)
        {
            *pucdest++ = uctemp;
            uctemp = 0;
            uscount = 0;
        }

        pucsrc++;
    }

    /* 加上字符串结束府'\0' */
    *pucdest = 0;

    return XML_RESULT_SUCCEED;
/*lint -save -e818*/
}
/*lint -restore +e818*/

/*****************************************************************************
函 数 名  : XML_StringToNvValue
功能描述  : 把字符串转成十六进制的格式
输入参数  : pucbuff 指字符串缓冲区
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
XML_RESULT_ENUM_UINT32 xml_stringtovalue(u8  *pucbuff,
                                                 u8  *pucretbuff,
                                                 u32 *pretbufflen)
{
    XML_RESULT_ENUM_UINT32 returnval = 0;
    u32 ulcount = 0;    /* 判断是否保存当前转换后的值 */
    u8 *pcsrc;
    u8 *pcdest;
    pcsrc  = pucbuff;
    pcdest = pucbuff;

     /* 如果NV VALUE是空的，则返回错误 */
    if (0 == *pcsrc)
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_NV_VALUE_IS_NULL);
        return XML_RESULT_FALIED_NV_VALUE_IS_NULL;
    }


    /* 先把原字符串中的分隔符去掉 */
    while (0 != *pcsrc)
    {
        /* 如果当前字符是分隔符 */
        if (g_separator == *pcsrc)
        {
            /* 如果在2个分隔符之间只有一个字符,则需在前面插入一个'0' */
            if (1 == ulcount)
            {
                *pcdest = *(pcdest-1);
                *(pcdest-1) = '0';
                pcdest++;
            }

            ulcount = 0;
            pcsrc++;

            continue;
        }

        /* 如果有一个NV项超过2个字符,即出错.例<nv id="1">A3E</nv> */
        if (2 <= ulcount)
        {
            xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_2_CHAR);
            return XML_RESULT_FALIED_OUT_OF_2_CHAR;
        }

        *pcdest++ = *pcsrc++;
        ulcount++;    /* 记录分隔符之间字符的个数 */
    }


    /* 加上字符串结束府'\0' */
    *pcdest = '\0';


    /* 记录转换后的数据长度 */
    *pretbufflen = (u32)(pcdest - pucbuff)/2;

    /* 转成十六进制格式 */
    pcsrc  = pucbuff;
    pcdest = pucretbuff;

    returnval =  xml_stringtohex(pcsrc, pcdest);

    return returnval;
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
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_write_nv_data(void)
{
    XML_RESULT_ENUM_UINT32 returnval = NV_ERROR;
    u16 usnvitemid  = 0;
    u16 priority = 0xFFFF;
    u32 ulnvitemlen = 0;
    s32    lisnv       = 0;
    s32    liscust     = 0;
    struct nv_ref_data_info_stru ref_info = {0};
    struct nv_file_list_info_stru file_info = {0};
    u32 ulPropertyIndex = 0;
    u8* ref_offset = NULL;

    /* 如果当前节点不是有效的节点,则不做任何处理 */
    if (XML_PRODUCT_NODE_STATUS_INVALID == xml_ctrl.g_stlxmlproductinfo.envalidnode)
    {
        return XML_RESULT_SUCCEED;
    }

    /* 如果第一个属性值为空,而且节点值为空,则不做任何处理, 如<cust/> */
    xml_ctrl.g_stlxmlcurrentnode.stproperty[0].pcpropertyvalue[
                        xml_ctrl.g_stlxmlcurrentnode.stproperty[0].ulvaluelength] = '\0';

    xml_ctrl.g_stlxmlcurrentnode.pcnodevalue[xml_ctrl.g_stlxmlcurrentnode.ulvaluelength] = '\0';

    if ((0 == *xml_ctrl.g_stlxmlcurrentnode.stproperty[0].pcpropertyvalue)
        || (0 == *xml_ctrl.g_stlxmlcurrentnode.pcnodevalue))
    {
        return XML_RESULT_SUCCEED;
    }

    /* 只对nv，cust节点写到NV中 */
    xml_ctrl.g_stlxmlcurrentnode.pcnodelabel[xml_ctrl.g_stlxmlcurrentnode.ullabelendlength] = '\0';

    lisnv = strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.pcnodelabel, (char *)g_aclnodelabelnv);/*[false alarm]:屏蔽Fortify错误 */

    liscust = strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.pcnodelabel, (char *)g_aclnodelabelcust);/*[false alarm]:屏蔽Fortify错误 */

    if ((0 != lisnv) && (0 != liscust))
    {
        return XML_RESULT_SUCCEED;
    }
    for(ulPropertyIndex = 0; ulPropertyIndex <= xml_ctrl.g_stlxmlcurrentnode.ulPropertyIndex; ulPropertyIndex++)
    {
        xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyname[
                    xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].ulnamelength] = '\0';

        xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue[
                            xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].ulvaluelength] = '\0';

        if(!strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyname, (char *)g_aclpropertyId))/* [false alarm]:屏蔽Fortify错误 */
        {
            /* 把id 属性值转成NV ID */
            returnval = xml_stringtou16(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue,
                                        &usnvitemid);

            if (XML_RESULT_SUCCEED != returnval)
            {
                goto out;
            }
        }
        else if(!strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyname, (char *)g_aclpropertyWp))/* [false alarm]:屏蔽Fortify错误 */
        {
            /* 把wp属性值转成priority */
            returnval = xml_stringtou16(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue,
                                        &priority);

            if (XML_RESULT_SUCCEED != returnval)
            {
                goto out;
            }
        }
        else
        {
            xml_write_error_log(__LINE__, usnvitemid, returnval);
            printf("<%s>: pcpropertyvalue :%s\n",__func__, xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue);
        }

    }

    /* 把节点值转成NV Value */
    ulnvitemlen = 0;

    returnval = xml_stringtovalue((u8 *)xml_ctrl.g_stlxmlcurrentnode.pcnodevalue,
                                  xml_ctrl.g_puclnvitem,
                                  &ulnvitemlen);

    if (XML_RESULT_SUCCEED != returnval)
    {
        xml_write_error_log(__LINE__, usnvitemid, returnval);
        goto out;
    }


    /* 写到NV中 */
    /*如果xml中存在不存在的NV项，则不写入，继续解析*/
	/*lint -save -e835*/
    returnval = xml_nv_boot_search_byid((u32)usnvitemid,((u8*)NV_GLOBAL_CTRL_INFO_ADDR),&ref_info,&file_info, (u8**)&ref_offset);
    if(returnval)
    {
        return XML_RESULT_SUCCEED;
    }
	/*lint -restore +e835*/
	/*检查xml配置是否正确,例如:出现comm配置为支持1个modem,diff文件同时配置2个diff的情况*/
	if(xml_ctrl.card_type > ref_info.modem_num)
	{
        xml_write_error_log(__LINE__, usnvitemid, BSP_ERR_NV_XML_CFG_ERR);
		printf("nv:0x%x xml config error\n", usnvitemid);
		printf("comm xml modem = 0x%x, diff xml modem = 0x%x\n", ref_info.modem_num ,xml_ctrl.card_type);
		return BSP_ERR_NV_XML_CFG_ERR;
	}
    ref_info.nv_off += (xml_ctrl.card_type - NV_USIMM_CARD_1)*ref_info.nv_len;


    returnval = nv_boot_write_to_mem((const u8*)xml_ctrl.g_puclnvitem,ref_info.nv_len,file_info.file_id,ref_info.nv_off);
    if(returnval)
    {
        xml_write_error_log(__LINE__, usnvitemid, returnval);
        goto out;
    }

    if(0xFFFF != priority)
    {
        xml_nv_boot_write_priority(ref_offset, priority);
    }
    return XML_RESULT_SUCCEED;
out:
    /* 记录出错的NV ID */
    return XML_RESULT_FALIED_WRITE_NV;
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
void xml_nodereset(void)
{
    u32 ulPropertyIndex = 0;

    /* 节点标签复位,已使用的长度为0  */
    xml_ctrl.g_stlxmlcurrentnode.ullabellength= 0;

    /* 节点值复位,已使用的长度为0 */
    xml_ctrl.g_stlxmlcurrentnode.ulvaluelength= 0;

    /* 节点独立标签复位,已使用的长度为0 */
    xml_ctrl.g_stlxmlcurrentnode.ullabelendlength= 0;
    /*xml_ctrl.g_stlxmlcurrentnode.stproperty的下标索引归0*/
    xml_ctrl.g_stlxmlcurrentnode.ulPropertyIndex = 0;
    for(ulPropertyIndex = 0; ulPropertyIndex < XML_NODE_PROPERTY_NUM; ulPropertyIndex++)
    {
        /* 节点属性名复位,已使用的长度为0 */
        xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].ulnamelength= 0;

        /* 节点属性值复位,已使用的长度为0 */
        xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].ulvaluelength= 0;
    }
    /*lint -save -e665*/
    memset(xml_ctrl.g_stlxmlcurrentnode.pcnodevalue,0,XML_NODE_VALUE_BUFF_LENGTH_ORIGINAL+1);
    /*lint -restore +e665*/

    return ;
}


/*****************************************************************************
函 数 名  : xml_write_char_to_buff
功能描述  : 把字符添加进指定长度缓冲区
输入参数  : pcdestChar待添加的字符，
          : pcstrbuff被添加字符串指针的地址，
          : plbufflength字符创当前长度的地址
          : ulisnodevalue指pcstrbuff是否是指向Node Value
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
XML_RESULT_ENUM_UINT32 xml_write_char_to_buff(s8   cnowchar,
                                                 s8   *pcstrbuff,
                                                 u32 *plbufflength,
                                                 bool   ulisnodevalue)
{
    /* 忽略空格 */
    if (' ' == cnowchar)
    {
        return XML_RESULT_SUCCEED;
    }
/*lint -save -e731*/
    /* 如果达到了Node Value的最大长度 */
    if ((TRUE == ulisnodevalue)
        && (*plbufflength >= XML_NODE_VALUE_BUFF_LENGTH_ORIGINAL))
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_BUFF_LEN);

        return XML_RESULT_FALIED_OUT_OF_BUFF_LEN;
    }


    /* 如果达到了Node Lable的最大长度 */
    if ((FALSE == ulisnodevalue)
        && (*plbufflength >= XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL))
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_BUFF_LEN);

        return XML_RESULT_FALIED_OUT_OF_BUFF_LEN;
    }
/*lint -restore +e731*/
    /* 把新字符加进缓冲区 */
    *(pcstrbuff + *plbufflength) = cnowchar;

    /* 缓冲区长度加1 */
    (*plbufflength)++;

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
XML_RESULT_ENUM_UINT32 xml_checknodelabelvalid(void)
{
    u32 ulPropertyIndex = 0;

    /* 判断该标签是否有效 */
    xml_ctrl.g_stlxmlcurrentnode.pcnodelabel[xml_ctrl.g_stlxmlcurrentnode.ullabellength] = '\0';

    /* 如果当前节点为无效状态,需要检查标签是否为有效节点 */
    if (0 == strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                        (char *)g_aclnodelabelcommon))/* [false alarm]:屏蔽Fortify错误 */
    {
        /* 如果是<Common_NvInfo>标签,则设置节点为有效状态 */
        xml_ctrl.g_stlxmlproductinfo.envalidnode= XML_PRODUCT_NODE_STATUS_VALID;

        return XML_RESULT_SUCCEED;
    }
    /* 如果是<Cust>标签,则设置节点为有效状态 */
    if (0 == strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                             (char *)g_aclnodelabelcust))/* [false alarm]:屏蔽Fortify错误 */
    {
        xml_ctrl.g_stlxmlproductinfo.envalidnode= XML_PRODUCT_NODE_STATUS_VALID;

        return XML_RESULT_SUCCEED;
    }
    /* 如果当前节点为无效状态,需要检查标签是否为有效节点 */
    if (0 == strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                        (char *)g_aclnodelabelproductNvInfo))/* [false alarm]:屏蔽Fortify错误 */
    {
        /* 如果是<product_NvInfo>标签,则设置节点为有效状态 */
        xml_ctrl.g_stlxmlproductinfo.envalidnode= XML_PRODUCT_NODE_STATUS_VALID;

        return XML_RESULT_SUCCEED;
    }


    if (0 == strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                             (char *)g_aclnodelabelproduct))/* [false alarm]:屏蔽Fortify错误 */
    {

        ulPropertyIndex = xml_ctrl.g_stlxmlcurrentnode.ulPropertyIndex;

        xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue[
                      xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].ulvaluelength] = '\0';

        /*第一次碰到product节点设置为无效节点*/
        /* 如果是<product>标签且Product id与当前单板相同,则设置节点为有效状态 */
        xml_ctrl.g_stlxmlproductinfo.envalidnode= XML_PRODUCT_NODE_STATUS_INVALID;

        if (0 == strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue,
                            (char *)xml_ctrl.g_stlxmlproductinfo.acproductid))/* [false alarm]:屏蔽Fortify错误 */
        {
            xml_ctrl.g_stlxmlproductinfo.envalidnode= XML_PRODUCT_NODE_STATUS_VALID;
            xml_ctrl.g_stlxmlproductinfo.ulnodelevel++;
        }
        else/*product 属性节点跳转*/
        {
            xml_ctrl.g_stlxmlproductinfo.envalidnode     = XML_PRODUCT_NODE_STATUS_INVALID;
            xml_ctrl.g_stlxmlproductinfo.enxmldecodejump = XML_DECODE_STATUS_2JUMP;
        }
        return XML_RESULT_SUCCEED;
    }

    if (XML_PRODUCT_NODE_STATUS_VALID == xml_ctrl.g_stlxmlproductinfo.envalidnode)
    {
        /* 在节点为有效状态下，对Product节点，要记录<product>节点出现的次数 */
        if (0 == strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                            (char *)g_aclnodelabelproduct))/* [false alarm]:屏蔽Fortify错误 */
        {
            xml_ctrl.g_stlxmlproductinfo.ulnodelevel++;
        }

        return XML_RESULT_SUCCEED;
    }

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
XML_RESULT_ENUM_UINT32 xml_checknodeendlabelvalid(void)
{
    XML_RESULT_ENUM_UINT32 returnval;

    /* 写节点信息到NV中 */
    returnval = xml_write_nv_data();

    if (XML_RESULT_SUCCEED != returnval)
    {
        return returnval;
    }

    xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend[xml_ctrl.g_stlxmlcurrentnode.ullabelendlength]='\0';

    if (0 == strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend,
                        (char *)g_aclnodelabelproduct))/* [false alarm]:屏蔽Fortify错误 */
    {
        if (XML_PRODUCT_NODE_STATUS_VALID == xml_ctrl.g_stlxmlproductinfo.envalidnode)
        {
            xml_ctrl.g_stlxmlproductinfo.ulnodelevel--;

            if (0 == xml_ctrl.g_stlxmlproductinfo.ulnodelevel)
            {
                /* 最后一个有效的</product>标签出现时，结束整个XML文件的解析 */
                xml_ctrl.g_stlxmlproductinfo.enxmldecodestate = XML_DECODE_STATUS_FINISHED;
                xml_ctrl.g_stlxmlproductinfo.envalidnode      = XML_PRODUCT_NODE_STATUS_INVALID;
            }
        }
    }
    else if (0 == strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend,
                             (char *)g_aclnodelabelcommon))/* [false alarm]:屏蔽Fortify错误 */
    {
        /* </Common_NvInfo>标签出现时,把节点状态只为无效 ,同时置为可跳转状态*/
        xml_ctrl.g_stlxmlproductinfo.envalidnode     = XML_PRODUCT_NODE_STATUS_INVALID;
        xml_ctrl.g_stlxmlproductinfo.enxmldecodejump = XML_DECODE_STATUS_JUMP;
    }
    else if (0 == strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend,
                             (char *)g_aclnodelabelcust))/* [false alarm]:屏蔽Fortify错误 */
    {
        /* </Cust>标签出现时,把节点状态只为无效 */
        xml_ctrl.g_stlxmlproductinfo.envalidnode = XML_PRODUCT_NODE_STATUS_INVALID;
    }
    else if (0 == strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend,
                             (char *)g_aclnodelabelproductNvInfo))/* [false alarm]:屏蔽Fortify错误 */
    {
        /* 第一个</product_NvInfo>标签出现时,同样需要结束整个XML文件的解析*/
        xml_ctrl.g_stlxmlproductinfo.enxmldecodestate = XML_DECODE_STATUS_FINISHED;
        xml_ctrl.g_stlxmlproductinfo.envalidnode      = XML_PRODUCT_NODE_STATUS_INVALID;
    }
    else
    {
        /* Do nothing */

    } /* end of if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcnodelabelend, */

    /* </xx>标签结束时，清空节点信息 */
    xml_nodereset();

    return XML_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : xml_checknode_rightlabel
功能描述  : must be right错误格式节点处理
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
XML_RESULT_ENUM_UINT32 xml_checknode_rightlabel(void)
{
    u32 ulPropertyIndex = 0;

    /* 判断该标签是否有效 */
    xml_ctrl.g_stlxmlcurrentnode.pcnodelabel[xml_ctrl.g_stlxmlcurrentnode.ullabellength] = '\0';

    if (0 == strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                        (char *)g_aclnodelabelproduct))/* [false alarm]:屏蔽Fortify错误 */
    {
        ulPropertyIndex = xml_ctrl.g_stlxmlcurrentnode.ulPropertyIndex;

        xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue[
                      xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].ulvaluelength] = '\0';

        /* 格式<product product_id="123456"/>，且product id与单板product id相同结束整个XML文件的解析 */
        if (0 == strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue,
                            (char *)xml_ctrl.g_stlxmlproductinfo.acproductid))/* [false alarm]:屏蔽Fortify错误 */
        {
            xml_ctrl.g_stlxmlproductinfo.enxmldecodestate = XML_DECODE_STATUS_FINISHED;
            xml_ctrl.g_stlxmlproductinfo.envalidnode      = XML_PRODUCT_NODE_STATUS_INVALID;
        }
        else
        {
            xml_ctrl.g_stlxmlproductinfo.envalidnode      = XML_PRODUCT_NODE_STATUS_INVALID;
        }
    }
    else if (0 == strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                             (char *)g_aclnodelabelcommon))/* [false alarm]:屏蔽Fortify错误 */
    {
        /* <Common_NvInfo/>标签出现时,把节点状态只为无效 ,同时置为可跳转状态*/
        xml_ctrl.g_stlxmlproductinfo.envalidnode     = XML_PRODUCT_NODE_STATUS_INVALID;
        xml_ctrl.g_stlxmlproductinfo.enxmldecodejump = XML_DECODE_STATUS_JUMP;
    }
    else if (0 == strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                             (char *)g_aclnodelabelcust))/* [false alarm]:屏蔽Fortify错误 */
    {
        /* <Cust/>标签出现时,把节点状态只为无效 */
        xml_ctrl.g_stlxmlproductinfo.envalidnode = XML_PRODUCT_NODE_STATUS_INVALID;
    }
    else if (0 == strcmp((char *)xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                             (char *)g_aclnodelabelproductNvInfo))/* [false alarm]:屏蔽Fortify错误 */
    {
        /* <product_NvInfo/>标签出现时,同样需要结束整个XML文件的解析*/
        xml_ctrl.g_stlxmlproductinfo.enxmldecodestate = XML_DECODE_STATUS_FINISHED;
        xml_ctrl.g_stlxmlproductinfo.envalidnode      = XML_PRODUCT_NODE_STATUS_INVALID;
    }
    else
    {
        /* Do nothing */

    }

    /* <xx/>标签结束时，清空节点信息 */
    xml_nodereset();

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
XML_RESULT_ENUM_UINT32 xml_createaproperty( void )
{
    u32 propertyIndex = 0;

    for(propertyIndex = 0;propertyIndex < XML_NODE_PROPERTY_NUM; propertyIndex++)
    {
        /* 分配属性名内存,+1为保留字符串结束符用 */
        xml_ctrl.g_stlxmlcurrentnode.stproperty[propertyIndex].ulnamelength = 0; /* 已使用的长度 */

        xml_ctrl.g_stlxmlcurrentnode.stproperty[propertyIndex].pcpropertyname
                                    = (s8*)nv_malloc(
                                       XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL+1);

        if (NULL == xml_ctrl.g_stlxmlcurrentnode.stproperty[propertyIndex].pcpropertyname)
        {
             xml_write_error_log(__LINE__, (u16)propertyIndex, XML_RESULT_FALIED_MALLOC);

            return XML_RESULT_FALIED_MALLOC;
        }

        /* 分配属性值内存,+1为保留字符串结束符用 */
        xml_ctrl.g_stlxmlcurrentnode.stproperty[propertyIndex].ulvaluelength = 0; /* 已使用的长度 */


        xml_ctrl.g_stlxmlcurrentnode.stproperty[propertyIndex].pcpropertyvalue
                                    = (s8*)nv_malloc(
                                       XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL+1);
        if (NULL == xml_ctrl.g_stlxmlcurrentnode.stproperty[propertyIndex].pcpropertyvalue)
        {
            xml_write_error_log(__LINE__, (u16)propertyIndex, XML_RESULT_FALIED_MALLOC);

            return XML_RESULT_FALIED_MALLOC;
        }
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
XML_RESULT_ENUM_UINT32 xml_createanode(void)
{
    XML_RESULT_ENUM_UINT32 returnval = XML_RESULT_SUCCEED;


    /* 创建一个新属性 */
    returnval = xml_createaproperty();

    if(XML_RESULT_SUCCEED != returnval)
    {
        return returnval;
    }

    /* 分配节点标签内存,+1为保留字符串结束符用*/
    xml_ctrl.g_stlxmlcurrentnode.ullabellength = 0; /* 已使用的长度 */



    xml_ctrl.g_stlxmlcurrentnode.pcnodelabel = (s8*)nv_malloc(
                                      XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL+1);

    if (NULL ==  xml_ctrl.g_stlxmlcurrentnode.pcnodelabel)
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    /* 分配节点结尾独立标签内存,+1为保留字符串结束符用 */
    xml_ctrl.g_stlxmlcurrentnode.ullabelendlength = 0; /* 已使用的长度 */

    xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend = (s8*)nv_malloc(
                                        XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL+1);

    if (NULL ==  xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend)
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    /* 分配节点值内存,+1为保留字符串结束符用 */
    xml_ctrl.g_stlxmlcurrentnode.ulvaluelength = 0; /* 已使用的长度 */

    xml_ctrl.g_stlxmlcurrentnode.pcnodevalue = (s8*)nv_malloc(
                                      XML_NODE_VALUE_BUFF_LENGTH_ORIGINAL+1);

    if (NULL == xml_ctrl.g_stlxmlcurrentnode.pcnodevalue)
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    return returnval;
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
XML_RESULT_ENUM_UINT32 xml_procxmlorginal(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval = XML_RESULT_SUCCEED;

    /* 遇到<则更改状态 */
    if ('<' == cnowchar)
    {
        g_stlxmlstatus = XML_ANASTT_ENTER_LABLE;
        return XML_RESULT_SUCCEED;
    }

    /* 遇到>,/,",=则表示XML语法错误 */
    if (('>' == cnowchar)
         ||('/' == cnowchar)
         ||('"' == cnowchar)
         ||('=' == cnowchar))
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);
        printf("%s  err char %c \n",__func__,cnowchar);
        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

/*lint -save -e747*/
    if (XML_PRODUCT_NODE_STATUS_VALID == xml_ctrl.g_stlxmlproductinfo.envalidnode)
    {
        /* 把这个字节放进当前节点值的缓冲区内 */
        returnval = xml_write_char_to_buff(cnowchar,
                                     xml_ctrl.g_stlxmlcurrentnode.pcnodevalue,
                                     &(xml_ctrl.g_stlxmlcurrentnode.ulvaluelength),
                                     TRUE);
    }
/*lint -restore +e747*/

    return returnval;
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
XML_RESULT_ENUM_UINT32 xml_procxmlignore(s8 cnowchar)
{

    /* 直到遇到标签结尾，否则一直忽略 */
    if ('>' == cnowchar)
    {
        g_stlxmlstatus = XML_ANASTT_ORIGINAL;
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
XML_RESULT_ENUM_UINT32 xml_proc_xmlsingle_endlabel(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval;

    returnval = XML_RESULT_SUCCEED;

    /* 遇到<则更改状态 */
    if ('>' == cnowchar)
    {
        /* 变更状态 */
        g_stlxmlstatus = XML_ANASTT_ORIGINAL;

        /* 检查独立结束标签是否有效 */
        returnval = xml_checknodeendlabelvalid();

        return returnval;
    }

    /* 遇到<,/,",=则表示XML语法错误 */
    if (('<' == cnowchar)
         ||('"' == cnowchar)
         ||('/' == cnowchar)
         ||('=' == cnowchar))
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }
/*lint -save -e747*/
    /* 把这个字节放进当前节点值的缓冲区内 */
    returnval = xml_write_char_to_buff(cnowchar,
                                  xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend,
                                  &(xml_ctrl.g_stlxmlcurrentnode.ullabelendlength),
                                  FALSE);
/*lint -restore +e747*/
    return returnval;
}


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
XML_RESULT_ENUM_UINT32 xml_procxmlend_mustberight(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval;

    /* 忽略空格 */
    if (' ' == cnowchar)
    {
        return XML_RESULT_SUCCEED;
    }

    /* 遇到不是>,则表示XML语法错误 */
    if ('>' != cnowchar)
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    /* 变更状态 */
    g_stlxmlstatus = XML_ANASTT_ORIGINAL;

    /*must be right need to check label*/
    returnval = xml_checknode_rightlabel();

    if (XML_RESULT_SUCCEED != returnval)
    {
        return returnval;
    }

    if (XML_PRODUCT_NODE_STATUS_VALID == xml_ctrl.g_stlxmlproductinfo.envalidnode)
    {
        /* 写节点信息到NV中 */
        returnval = xml_write_nv_data();

        if (XML_RESULT_SUCCEED != returnval)
        {
            return returnval;
        }

        /* <xx/>标签结束时，清空节点信息 */
        xml_nodereset();
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
XML_RESULT_ENUM_UINT32 xml_proc_xml_node_label(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval;

    /* 遇到/或者>或者空格说明Node的名字结束了 */
    if ('/' == cnowchar)
    {
        /* 结束并收尾整个节点,下个字节一定是> */
        g_stlxmlstatus = XML_ANASTT_LABLE_END_MUST_RIGHT;

        return XML_RESULT_SUCCEED;
    }

    /* 标签结束 */
    if ('>' == cnowchar)
    {
        /* 变更状态 */
        g_stlxmlstatus = XML_ANASTT_ORIGINAL;

        /* 检查当前节点是有效节点 */
        returnval = xml_checknodelabelvalid();

        return returnval;
    }

    /* 标签名字结束,进入属性解析状态 */
    if (' ' == cnowchar)
    {
        /* 变更状态 */
        g_stlxmlstatus = XML_ANASTT_PROPERTY_START;

        return XML_RESULT_SUCCEED;
    }

    /* 遇到<,",=则表示XML语法错误 */
    if (('<' == cnowchar)
         ||('"' == cnowchar)
         ||('=' == cnowchar))
    {
        xml_write_error_log(__LINE__, 0,XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }
/*lint -save -e747*/
    /* 把这个字节放进当前节点值的缓冲区内 */
    returnval = xml_write_char_to_buff(cnowchar,
                                     xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                                     &(xml_ctrl.g_stlxmlcurrentnode.ullabellength),
                                     FALSE);
/*lint -restore +e747*/
    return returnval;
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
XML_RESULT_ENUM_UINT32 xml_proc_xml_enter_label(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval = XML_RESULT_SUCCEED;

    /* 遇到首行版本信息 */
    if ('?' == cnowchar)
    {
        g_stlxmlstatus = XML_ANASTT_IGNORE;

        return XML_RESULT_SUCCEED;
    }

    /* 遇到序言 */
    if ('!' == cnowchar)
    {
        g_stlxmlstatus = XML_ANASTT_IGNORE;

        return XML_RESULT_SUCCEED;
    }

    /* 遇到尾节点标签 */
    if ('/' == cnowchar)
    {
        g_stlxmlstatus = XML_ANASTT_SINGLE_ENDS_LABLE;

        return XML_RESULT_SUCCEED;
    }

    /* 遇到标签结束 */
    if ('>' == cnowchar)
    {
        g_stlxmlstatus = XML_ANASTT_ORIGINAL;

        return XML_RESULT_SUCCEED;
    }

    /* 遇到<,",=则表示XML语法错误 */
    if (('<' == cnowchar)
         ||('"' == cnowchar)
         ||('=' == cnowchar))
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);
        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    /* 跳过空格 */
    if (' ' != cnowchar)
    {
        /* 写节点信息到NV中 */
        returnval = xml_write_nv_data();

        if (XML_RESULT_SUCCEED != returnval)
        {
            return returnval;
        }

        /* 进入一个新节点时，先清空节点信息 */
        xml_nodereset();

        /* 变更状态，表示进入一个新节点 */
        g_stlxmlstatus = XML_ANASTT_NODE_LABLE;
/*lint -save -e747*/
        /* 把这个字节放进当前节点值的缓冲区内 */
        returnval = xml_write_char_to_buff(cnowchar,
                                         (s8 *)xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                                         &(xml_ctrl.g_stlxmlcurrentnode.ullabellength),
                                         FALSE);
/*lint -restore +e747*/
    }

    return returnval;
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
XML_RESULT_ENUM_UINT32 xml_proc_xml_propertystart(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval = XML_RESULT_SUCCEED;
    u32 ulPropertyIndex = 0;


    /* 遇到尾节点标签 */
    if ('/' == cnowchar)
    {
        /* 变更状态 */
        g_stlxmlstatus = XML_ANASTT_LABLE_END_MUST_RIGHT;

        return XML_RESULT_SUCCEED;
    }

    /* 标签结束 */
    if ('>' == cnowchar)
    {
        /* 变更状态 */
        g_stlxmlstatus = XML_ANASTT_ORIGINAL;

        /* 检查当前节点有效 */
        returnval = xml_checknodelabelvalid();

        return returnval;
    }

    /* 遇到<,",=则表示XML语法错误 */
    if (('<' == cnowchar)
         ||('"' == cnowchar)
         ||('=' == cnowchar))
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    /* 更改状态 */
    g_stlxmlstatus = XML_ANASTT_PROPERTY_NAME_START;

    ulPropertyIndex = xml_ctrl.g_stlxmlcurrentnode.ulPropertyIndex;
/*lint -save -e747*/
    returnval = xml_write_char_to_buff(cnowchar,
                  xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyname,
                  &(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].ulnamelength),
                  FALSE);
/*lint -restore +e747*/

    return returnval;
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
XML_RESULT_ENUM_UINT32 xml_proc_xml_propertyname(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval = XML_RESULT_SUCCEED;
    u32 ulPropertyIndex = 0;

    /* 等待=进入属性值解析 */
    if ('=' == cnowchar)
    {
        /* 翻状态 */
        g_stlxmlstatus = XML_ANASTT_PROPERTY_NAME_END;

        return XML_RESULT_SUCCEED;
    }

    /* 遇到<,>,/,"则表示XML语法错误 */
    if (('<' == cnowchar)||('>' == cnowchar)
        ||('/' == cnowchar)||('"' == cnowchar))
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    ulPropertyIndex = xml_ctrl.g_stlxmlcurrentnode.ulPropertyIndex;
/*lint -save -e747*/
    /* 容许属性名中的空格错误, 如 <nv i d="123"> */
    returnval = xml_write_char_to_buff(cnowchar,
                  xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyname,
                  &(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].ulnamelength),
                  FALSE);
/*lint -restore +e747*/

    return returnval;
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
XML_RESULT_ENUM_UINT32 xml_proc_xml_propertyname_tail(s8 cnowchar)
{

    /* 跳过空格 */
    if ( ' ' == cnowchar)
    {
        return XML_RESULT_SUCCEED;
    }

    /* 等待" */
    if ('"' == cnowchar)
    {
        /* 更改状态 */
        g_stlxmlstatus = XML_ANASTT_PROPERTY_VALUE_START;

        return XML_RESULT_SUCCEED;
    }

    /* 遇到不是"，则表示XML语法错误 */
    xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

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
XML_RESULT_ENUM_UINT32 xml_proc_xml_valuestart(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval = XML_RESULT_SUCCEED;
    u32 ulPropertyIndex = 0;

    /* 遇到" */
    if ('"' == cnowchar)
    {
        /* 翻状态,返回开始解析属性的状态 */
        g_stlxmlstatus = XML_ANASTT_PROPERTY_VALUE_END;

        return XML_RESULT_SUCCEED;
    }

    /* 遇到<,>,/,=则表示XML语法错误 */
    if (('<' == cnowchar)
         ||('>' == cnowchar)
         ||('/' == cnowchar)
         ||('=' == cnowchar))
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    ulPropertyIndex = xml_ctrl.g_stlxmlcurrentnode.ulPropertyIndex;
/*lint -save -e747*/
    /* 把当前字符加到属性值中 */
    returnval = xml_write_char_to_buff(cnowchar,
                  xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue,
                  &(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].ulvaluelength),
                  FALSE);
/*lint -restore +e747*/
    return returnval;
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
XML_RESULT_ENUM_UINT32 xml_proc_xml_valuetail(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval;

    /* 空格下一个属性解析开始 */
    if (' ' == cnowchar)
    {
        /* 变更状态,返回开始解析属性的状态 */
        g_stlxmlstatus = XML_ANASTT_PROPERTY_START;
        xml_ctrl.g_stlxmlcurrentnode.ulPropertyIndex++;
        return XML_RESULT_SUCCEED;
    }

    /* 遇到'/' */
    if ('/' == cnowchar)
    {
        /* 变更状态 */
        g_stlxmlstatus = XML_ANASTT_LABLE_END_MUST_RIGHT;

        return XML_RESULT_SUCCEED;
    }

    /* 遇到'>' */
    if ('>' == cnowchar)
    {
        /* 变更状态,返回开始解析属性的状态 */
        g_stlxmlstatus = XML_ANASTT_ORIGINAL;

        /* 检查当前节点有效 */
        returnval = xml_checknodelabelvalid();

        return returnval;
    }

    /* 遇到不是>,/则表示XML语法错误 */
    xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

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
XML_FUN g_uslxmlanalysefuntbl[] =
{
    xml_procxmlorginal,         /* 初始状态下的处理                  */
    xml_proc_xml_enter_label,       /* 进入Lable后的处理                 */
    xml_procxmlignore,           /* 序言或注释状态下直到遇到">"结束   */
    xml_proc_xml_node_label,        /* 标签名字开始                      */
    xml_proc_xmlsingle_endlabel,   /* 标准的结尾标签</XXX>              */
    xml_procxmlend_mustberight,   /* 形如 <XXX/>的标签,在解析完/的状态 */
    xml_proc_xml_propertystart,    /* 开始解析属性                      */
    xml_proc_xml_propertyname,     /* 开始解析属性名字                  */
    xml_proc_xml_propertyname_tail, /* 属性名字结束，等待"即属性值开始   */
    xml_proc_xml_valuestart,       /* 属性值开始                        */
    xml_proc_xml_valuetail,        /* 属性值结束                        */
};

XML_RESULT_ENUM_UINT32 xml_analyse(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval;

    /* 检查当前字符的有效性 */
    returnval = xml_checkcharvalidity(cnowchar);

    if (XML_RESULT_SUCCEED_IGNORE_CHAR == returnval)
    {
        /* 如果遇到序言，则跳过该字符 */
        return XML_RESULT_SUCCEED;
    }

    if (XML_RESULT_FALIED_BAD_CHAR == returnval)
    {
        /* 如果遇到非法字符，则停止解析 */
        return XML_RESULT_FALIED_BAD_CHAR;
    }
    /* 调用XML解析时，相应状态的对应函数 */
    returnval = g_uslxmlanalysefuntbl[g_stlxmlstatus](cnowchar);

    return returnval;
}

/*****************************************************************************
函 数 名  : XML_DecodeXMLFile
功能描述  : 读取XML文件数据，进行解析
输入参数  : lFile指打开的文件描述符
输出参数  : 无
返 回 值  : XML_RESULT_ENUM_UINT32
调用函数  : DRV_FILE_READ
            DRV_FILE_CLOSE
            XML_Analyse
            XML_WriteErrorLog
被调函数  : XML_DecodeMain

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_decode_xml_file(FILE* pfile)
{
    s32               lreaded = 0;       /* 读出的字节数 */
    s32               lcount;            /* 遍历缓冲区用 */
    XML_RESULT_ENUM_UINT32  returnval;


    /*read 4k*/
    lreaded = nv_file_read((u8*)(xml_ctrl.g_pclfilereadbuff),1,XML_FILE_READ_BUFF_SIZE,pfile);
    if((0 == lreaded)||(lreaded > XML_FILE_READ_BUFF_SIZE)||(lreaded < 0))
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_READ_FILE);
        return XML_RESULT_FALIED_READ_FILE;
    }


    while(0 != lreaded)
    {
        for(lcount = 0;lcount < lreaded; lcount++)
        {
            returnval = xml_analyse(*(xml_ctrl.g_pclfilereadbuff + lcount));
            if(XML_RESULT_SUCCEED != returnval)
            {
                /* 遇到解析错误，则停止解析 */
                return returnval;
            }

            /* 判断是否解析完成 */
            if (XML_DECODE_STATUS_FINISHED
                == xml_ctrl.g_stlxmlproductinfo.enxmldecodestate)
            {
                printf("%s: xml decode success !\n",__func__);
                return XML_RESULT_SUCCEED;
            }

            /*解析完common节点之后判断是否需要跳转*/
            if((XML_DECODE_STATUS_JUMP == xml_ctrl.g_stlxmlproductinfo.enxmldecodejump) &&
               (XML_DECODE_STATUS_JUMP == xml_ctrl.g_stlxmljumpflag))
            {
                printf("%s: product info decode jump  0x%x!\n",__func__,xml_ctrl.g_stlxmljumpinfo.productCatOff);
                nv_file_seek(pfile,(s32)(xml_ctrl.g_stlxmljumpinfo.productCatOff),SEEK_SET);
                xml_ctrl.g_stlxmlproductinfo.enxmldecodejump= XML_DECODE_STATUS_NOJUMP;
                g_stlxmlstatus = XML_ANASTT_ORIGINAL;
                break;
            }

            /*product 节点二次跳转*/
            if((XML_DECODE_STATUS_2JUMP == xml_ctrl.g_stlxmlproductinfo.enxmldecodejump) &&
               (XML_DECODE_STATUS_JUMP == xml_ctrl.g_stlxmljumpflag))
            {
                printf("%s: product id decode jump  0x%x!\n",__func__,xml_ctrl.g_stlxmljumpinfo.productIdOff);
                nv_file_seek(pfile,(s32)(xml_ctrl.g_stlxmljumpinfo.productIdOff),SEEK_SET);
                xml_ctrl.g_stlxmljumpflag = XML_DECODE_STATUS_NOJUMP;
                xml_ctrl.g_stlxmlproductinfo.enxmldecodejump = XML_DECODE_STATUS_NOJUMP;
                g_stlxmlstatus = XML_ANASTT_ORIGINAL;
                break;
            }
        }

        memset(xml_ctrl.g_pclfilereadbuff,0,XML_FILE_READ_BUFF_SIZE);

        lreaded = nv_file_read((u8*)(xml_ctrl.g_pclfilereadbuff),1,XML_FILE_READ_BUFF_SIZE,pfile);
        if((lreaded > XML_FILE_READ_BUFF_SIZE)||(lreaded < 0))
        {
            xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_READ_FILE);
            return XML_RESULT_FALIED_READ_FILE;
        }
    }

    /* 如果ulnodelevel不为0，说明<product>没有正常结束 */
    if (0 != xml_ctrl.g_stlxmlproductinfo.ulnodelevel)
    {
        xml_write_error_log(__LINE__,0,XML_RESULT_FALIED_PRODUCT_MATCH);
        return XML_RESULT_FALIED_PRODUCT_MATCH;
    }

    return XML_RESULT_SUCCEED;
}

void xml_productid_format(u32 product_id)
{
    u32 i = 0;
    u32 len = 0;
    s8 temp;

    for(i = 0;i<XML_MAX_HARDWARE_LEN;i++)
    {
        if(!product_id)
            break;
        xml_ctrl.g_stlxmlproductinfo.acproductid[i] = product_id % 10 + '0';
        product_id /= 10;
        len ++;
    }
    /*lint -save -e737 -e574*/
    for(i = 0;i<len/2;i++)
    /*lint -restore +e737 +e574*/
    {
	    /*lint -save -e679 -e834 -e737 -e676*/
        temp = xml_ctrl.g_stlxmlproductinfo.acproductid[i];
        xml_ctrl.g_stlxmlproductinfo.acproductid[i] = xml_ctrl.g_stlxmlproductinfo.acproductid[len-i-1];
        xml_ctrl.g_stlxmlproductinfo.acproductid[len-i-1] = temp;
	    /*lint -restore +e679 +e834 +e737 +e676*/
    }
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
XML_RESULT_ENUM_UINT32 xml_getproductid(void)
{
	s32    lproductid;

	/* 清空内存 */
	memset(xml_ctrl.g_stlxmlproductinfo.acproductid, 0, XML_MAX_HARDWARE_LEN);

	/* 取得当前单板的Product id */
	lproductid = (s32)bsp_get_version_info()->board_id;/*get hardware version*/

	xml_ctrl.g_stlxmlproductid = lproductid;

    /* coverity[secure_coding] */
    /*sprintf(xml_ctrl.g_stlxmlproductinfo.acproductid,"%d",lproductid);*/
    /*fastboot 无字符串格式化接口*/
    xml_productid_format((u32)lproductid);
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
void xml_initglobal(void)
{
    /* 初始化Product节点信息 */
    xml_ctrl.g_stlxmlproductinfo.envalidnode      = XML_PRODUCT_NODE_STATUS_INVALID;
    xml_ctrl.g_stlxmlproductinfo.enxmldecodestate = XML_DECODE_STATUS_DECODING;
    xml_ctrl.g_stlxmlproductinfo.enxmldecodejump  = XML_DECODE_STATUS_JUMP_BUTT;
    xml_ctrl.g_stlxmlproductinfo.ulnodelevel      = 0; /* 记录product节点出现的次数 */

    /* 初始化当前状态 */
    g_stlxmlstatus = XML_ANASTT_ORIGINAL;

    /* 用于记录读取XML文件的行数 */
    xml_ctrl.g_stlxml_lineno    = 1;

    /*用于记录能否跳转标志*/
    xml_ctrl.g_stlxmljumpflag   = XML_DECODE_STATUS_JUMP_BUTT;
    /*用于记录跳转偏移 跳转时偏移为0则保持当前偏移*/
    memset(&xml_ctrl.g_stlxmljumpinfo,0,(u32)sizeof(xml_ctrl.g_stlxmljumpinfo));

    return ;
}


/*
 * search product info through product id
 */
s32  xml_search_productinfo(u32 product_id,u8* pdata,XNV_MAP_PRODUCT_INFO* product_info)
{
    u32 low;
    u32 high;
    u32 mid;
    u32 offset;
    XNV_MAP_HEAD_STRU * map_file = (XNV_MAP_HEAD_STRU*)(unsigned long)pdata;

    low  = 1;
    high = map_file->product_num;

    while(low <= high)
    {
        mid = (low+high)/2;
        offset = (u32)sizeof(XNV_MAP_HEAD_STRU)+(u32)((mid-1)*sizeof(XNV_MAP_PRODUCT_INFO));

        memcpy((u8*)product_info,(u8*)pdata+offset,(u32)sizeof(XNV_MAP_PRODUCT_INFO));

        if(product_id < product_info->product_id)
        {
            high = mid - 1;
        }
        else if(product_id > product_info->product_id)
        {
            low = mid + 1;
        }
        else
        {
            return 0;
        }
    }
    return -1;
}
/*lint -save -e438*/
void xml_getjumpinfo(const s8* map_path)
{
    FILE* fp = NULL;
    s32 ret = 0;
    u32 file_len;
    XNV_MAP_HEAD_STRU* map_file = NULL;
    XNV_MAP_PRODUCT_INFO product_info = {0};

    if(!map_path)
        return;
    fp = nv_file_open(map_path,(s8*)NV_FILE_READ);
    if(!fp)
        return;
    file_len = nv_boot_get_file_len(fp);

    /* coverity[negative_returns] */
    map_file = (XNV_MAP_HEAD_STRU*)nv_malloc(file_len);
    if(!map_file)
    {
        nv_file_close(fp);
        return;
    }

    ret = nv_file_read((u8*)map_file,1,file_len,fp);
/*lint -save -e737*/
    if((u32)ret != file_len)
    {
        printf("%s  ret :%d,file_len :0x%x\n",__func__,ret,file_len);
        goto out;
    }
/*lint -restore +e737*/
    ret = xml_search_productinfo((u32)(xml_ctrl.g_stlxmlproductid),(u8*)map_file,&product_info);
    if(ret)
        goto out;

    memcpy(&xml_ctrl.g_stlxmljumpinfo,&product_info,(u32)sizeof(product_info));
    xml_ctrl.g_stlxmljumpflag = XML_DECODE_STATUS_JUMP;
    nv_file_close(fp);
    nv_free(map_file);
    return;

out:
    nv_file_close(fp);
    nv_free(map_file);
    memset(&xml_ctrl.g_stlxmljumpinfo,0,(u32)sizeof(xml_ctrl.g_stlxmljumpinfo));
    xml_ctrl.g_stlxmljumpflag = XML_DECODE_STATUS_NOJUMP;
    return;
}
/*lint -restore +e438*/

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
XML_RESULT_ENUM_UINT32 xml_procinit(s8* map_path)
{
    XML_RESULT_ENUM_UINT32 returnval;

    /* 初始化全局变量 */
    xml_initglobal();

    /* 获得当前单板的product id*/   /*? UDP*/
    xml_getproductid();

    /*获取当前跳转信息*/
    xml_getjumpinfo(map_path);

    /* 创建节点信息 */
    returnval = xml_createanode();

    if (XML_RESULT_SUCCEED != returnval)
    {
        return returnval;
    }

    /* 申请存放NV Item的值的缓冲区,+1为保留字符串结束符用 */  /*分配固定空间*/
    xml_ctrl.g_puclnvitem = (u8 *)nv_malloc(
                                         XML_NODE_VALUE_BUFF_LENGTH_ORIGINAL+1);
    if (NULL == xml_ctrl.g_puclnvitem)
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_MALLOC);
        return XML_RESULT_FALIED_MALLOC;
    }

    /* 申请读取文件数据的缓冲区,+1为保留字符串结束符用 */ /*是否分配空间?*/
    xml_ctrl.g_pclfilereadbuff = (s8*)nv_malloc(
                                                XML_FILE_READ_BUFF_SIZE+1);
    if (NULL == xml_ctrl.g_pclfilereadbuff)
    {
        nv_free(xml_ctrl.g_puclnvitem);
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_MALLOC);
        return XML_RESULT_FALIED_MALLOC;
    }

    return XML_RESULT_SUCCEED;
/*lint -save -e818*/
}
/*lint -restore +e818*/
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
void xml_freemem(void)
{
    u32 ulPropertyIndex = 0;

    for(ulPropertyIndex = 0; ulPropertyIndex < XML_NODE_PROPERTY_NUM; ulPropertyIndex++)
    {
        nv_free(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyname);

        nv_free(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue);
    }
    nv_free(xml_ctrl.g_stlxmlcurrentnode.pcnodelabel);

    nv_free(xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend);

    nv_free(xml_ctrl.g_stlxmlcurrentnode.pcnodevalue);

    nv_free(xml_ctrl.g_puclnvitem);

    nv_free(xml_ctrl.g_pclfilereadbuff);
}

void xml_decodefail_freemem(void)
{
    u32 ulPropertyIndex = 0;

    for(ulPropertyIndex = 0; ulPropertyIndex < XML_NODE_PROPERTY_NUM; ulPropertyIndex++)
    {
    	if(NULL != xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyname)
    	{
    		nv_free(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyname);
    		xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyname = NULL;
    	}
    }

	if(NULL != xml_ctrl.g_stlxmlcurrentnode.pcnodelabel)
	{
	nv_free(xml_ctrl.g_stlxmlcurrentnode.pcnodelabel);
		xml_ctrl.g_stlxmlcurrentnode.pcnodelabel = NULL;
	}

	if(NULL != xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend)
	{
		nv_free(xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend);
		xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend = NULL;
	}

	if(NULL != xml_ctrl.g_stlxmlcurrentnode.pcnodevalue)
	{
	nv_free(xml_ctrl.g_stlxmlcurrentnode.pcnodevalue);
		xml_ctrl.g_stlxmlcurrentnode.pcnodevalue = NULL;
	}

	if(NULL != xml_ctrl.g_puclnvitem)
	{
	nv_free(xml_ctrl.g_puclnvitem);
		xml_ctrl.g_puclnvitem = NULL;
	}

	if(NULL != xml_ctrl.g_pclfilereadbuff)
	{
	nv_free(xml_ctrl.g_pclfilereadbuff);
		xml_ctrl.g_pclfilereadbuff = NULL;
	}

}

/*****************************************************************************
函 数 名  : XML_DecodeMain
功能描述  : XML处理主调函数
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  : DRV_FILE_OPEN
            DRV_FILE_CLOSE
            DRV_FILE_RMFILE
            DRV_SYSTEM_ERROR
            VOS_FlowReboot
            XML_ProcInit
            XML_InitGlobal
            XML_DecodeXMLFile
            XML_WriteErrorLog
被调函数  : VOS_Startup

修改历史
1.日    期   : 2010年12月20日
作    者   : 郑继树 176513
修改内容   : 新生成函数
*****************************************************************************/
u32 xml_decode_main(FILE* fp,s8* map_path,u32 card_type)
{
    XML_RESULT_ENUM_UINT32 returnval;

    /* 初时化本模块全部变量内容 */
    returnval = xml_procinit(map_path);
    xml_ctrl.card_type = card_type;

    if (XML_RESULT_SUCCEED != returnval)
    {
        printf("xml_procinit error! returnval = %d\n",returnval);
        goto out;
    }

    /* 解析xnv.xml文件  */
    returnval = xml_decode_xml_file(fp);

    if (XML_RESULT_SUCCEED != returnval)
    {
        printf(" xml_decode_xml_file: returnval = %d!\n",returnval);
        goto out;
    }
    /* 释放已分配的内存 */
    xml_freemem();
    /*解析完成之后将卡类型修改为卡1*/
    xml_ctrl.card_type = NV_USIMM_CARD_1;
    return NV_OK;
out:
    xml_help();
	xml_decodefail_freemem();
    return returnval;
}


/*****************************************************************************
* 函 数 名  : xml_nv_boot_search_byid
*
* 功能描述  : 查找id 为itemid的NV的相关信息
*
* 输入参数  : itemid: NV id
*           : pdata :
* 输出参数  : ref_info  : NV信息
*           : file_info : NV所在的文件信息
*           : ref_offset: ref_info所在的内存
* 返 回 值  : void
*****************************************************************************/
u32 xml_nv_boot_search_byid(u32 itemid,u8* pdata,struct nv_ref_data_info_stru* ref_info,struct nv_file_list_info_stru* file_info, u8** ref_offset)
{
    u32 low;
    u32 high;
    u32 mid;
    u32 offset;
    struct nv_ctrl_file_info_stru* ctrl_info = (struct nv_ctrl_file_info_stru*)(unsigned long)pdata;

    high = ctrl_info->ref_count;
    low  = 1;
    while(low <= high)
    {
        mid = (low+high)/2;

        offset =(u32)NV_GLOBAL_CTRL_INFO_SIZE +(u32)NV_GLOBAL_FILE_ELEMENT_SIZE*ctrl_info->file_num + (u32)((mid -1)*NV_REF_LIST_ITEM_SIZE);
        memcpy((u8*)ref_info,(u8*)ctrl_info+offset,(u32)NV_REF_LIST_ITEM_SIZE);
        if(itemid < ref_info->itemid)
        {
            high = mid-1;
        }
        else if(itemid > ref_info->itemid)
        {
            low = mid+1;
        }
        else
        {
            *ref_offset = (u8*)ctrl_info + offset;
            offset = NV_GLOBAL_CTRL_INFO_SIZE + NV_GLOBAL_FILE_ELEMENT_SIZE*(ref_info->file_id -1);
            memcpy((u8*)file_info,(u8*)ctrl_info+offset,(u32)NV_GLOBAL_FILE_ELEMENT_SIZE);
            return NV_OK;
        }
    }
    return BSP_ERR_NV_NO_THIS_ID;

}
/*****************************************************************************
* 函 数 名  : xml_nv_boot_write_priority
*
* 功能描述  : 将priority优先级写入到ref_offset指向的内存中
*
* 输入参数  : ref_offset:待写入优先级的nv信息的指针
*           : priority  :调整后的优先级
*
* 输出参数  : 无
*
* 返 回 值  : void
*****************************************************************************/
void xml_nv_boot_write_priority(u8* ref_offset , u16 priority)
{
    struct nv_ref_data_info_stru *ref_info = NULL;
    ref_info = (struct nv_ref_data_info_stru *)(unsigned long)ref_offset;
    ref_info->priority = priority;
    return;
}

void xml_help(void)
{
	printf("xml_ctrl.g_stlxmlerrorinfo.ulxmlline  =  %d\n",xml_ctrl.g_stlxmlerrorinfo.ulxmlline);
	printf("xml_ctrl.g_stlxmlerrorinfo.ulstatus   =  %d\n",xml_ctrl.g_stlxmlerrorinfo.ulstatus);
	printf("xml_ctrl.g_stlxmlerrorinfo.ulcodeline =  %d\n",xml_ctrl.g_stlxmlerrorinfo.ulcodeline);
	printf("xml_ctrl.g_stlxmlerrorinfo.usnvid     =  %d\n",xml_ctrl.g_stlxmlerrorinfo.usnvid);
	printf("xml_ctrl.g_stlxmlerrorinfo.ulresult   =  %d\n",xml_ctrl.g_stlxmlerrorinfo.ulresult);
	printf("\n");
	printf("g_stlxmlstatus                        = %d\n",g_stlxmlstatus);
	printf("xml_ctrl.g_stlxml_lineno              = %d\n",xml_ctrl.g_stlxml_lineno);
	printf("acProductId                           = %d\n",xml_ctrl.g_stlxmlproductid);
    printf("xml_ctrl.g_stlxmlproductinfo.envalidnode   =  %d\n",xml_ctrl.g_stlxmlproductinfo.envalidnode);
}
/*lint -restore +e958*/
/*lint -restore +e838 +e801*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
