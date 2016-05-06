/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMtaComm.c
  版 本 号   : 初稿
  作    者   : 闫志吉
  生成日期   : 2012年6月27日
  最近修改   :
  功能描述   : MTA模块公共函数实现定义
  函数列表   :
  修改历史   :
  1.日    期   : 2012年6月27日
    作    者   : Y00213812
    修改内容   : A-GPS项目新增

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MTA_COMM_C


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafMtaComm.h"
/*****************************************************************************
  2 全局变量声明
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/

/*****************************************************************************
函 数 名  : TAF_MTA_Ac2ul
功能描述  : 把字符串转成无符号32位整型值
输入参数  : pcStr       待转换的字符串首地址
            ulLen       待转换的字符串长度
            pulRtn      转换后的无符号整型值
输出参数  : 无
返 回 值  : VOS_OK      转换成功
            VOS_ERR     转换失败
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_Ac2ul(
    VOS_CHAR                           *pcStr,
    VOS_UINT32                          ulLen,
    VOS_UINT32                         *pulRtn
)
{
    VOS_UINT32                          ulTotal;            /* current Total */
    VOS_UINT32                          ulLength;           /* current Length */
    VOS_CHAR                            cCur;               /* current Char */

    /* 入口指针不能为空指针 */
    if ((VOS_NULL_PTR == pcStr) || (VOS_NULL_PTR == pulRtn))
    {
        return VOS_ERR;
    }

    /* ulLen不能为0 */
    if (0 == ulLen)
    {
        return VOS_ERR;
    }

    cCur        = *(pcStr++);
    ulLength    = 0;
    ulTotal     = 0;
    while(ulLength++ < ulLen)
    {
        if ((cCur >= '0') && (cCur <= '9'))
        {
            /* 0xFFFFFFFF = 4294967295 */
            if ( ((ulTotal == MTA_UNSIGNED_LONG_FORMER_NINE_DIGIT) && (cCur > MTA_UNSIGNED_LONG_LAST_DIGIT))
              || (ulTotal > MTA_UNSIGNED_LONG_FORMER_NINE_DIGIT) )
            {
                /* 超过了数据类型支持的最大值 */
                return VOS_ERR;
            }
            ulTotal = (ulTotal * 10) + (cCur - '0');
            cCur    = *(pcStr++);
        }
        else
        {
            return VOS_ERR;
        }
    }

    *pulRtn = ulTotal;
    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_Ac2us
功能描述  : 把字符串转成无符号16位整型值
输入参数  : pcStr       待转换的字符串首地址
            ulLen       待转换的字符串长度
            pusRtn      转换后的无符号整型值
输出参数  : 无
返 回 值  : VOS_OK      转换成功
            VOS_ERR     转换失败
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_Ac2us(
    VOS_CHAR                           *pcStr,
    VOS_UINT32                          ulLen,
    VOS_UINT16                         *pusRtn
)
{
    VOS_UINT32                          ulLength;           /* current Length */
    VOS_UINT16                          usTotal;            /* current Total */
    VOS_CHAR                            cCur;               /* current Char */

    /* 入口指针不能为空指针 */
    if ((VOS_NULL_PTR == pcStr) || (VOS_NULL_PTR == pusRtn))
    {
        return VOS_ERR;
    }

    /* ulLen不能为0 */
    if (0 == ulLen)
    {
        return VOS_ERR;
    }

    cCur        = *(pcStr++);
    ulLength    = 0;
    usTotal     = 0;
    while(ulLength++ < ulLen)
    {
        if ((cCur >= '0') && (cCur <= '9'))
        {
            /* 0xFFFF = 65535 */
            if ( ((usTotal == MTA_UNSIGNED_SHORT_FORMER_FOUR_DIGIT) && (cCur > MTA_UNSIGNED_SHORT_LAST_DIGIT))
              || (usTotal > MTA_UNSIGNED_SHORT_FORMER_FOUR_DIGIT) )
            {
                /* 超过了数据类型支持的最大值 */
                return VOS_ERR;
            }
            usTotal = (VOS_UINT16)((usTotal * 10) + (cCur - '0'));
            cCur    = *(pcStr++);
        }
        else
        {
            return VOS_ERR;
        }
    }

    *pusRtn = usTotal;
    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_Ac2uc
功能描述  : 把字符串转成无符号8位整型值
输入参数  : pcStr       待转换的字符串首地址
            ulLen       待转换的字符串长度
            pucRtn      转换后的无符号整型值
输出参数  : 无
返 回 值  : VOS_OK      转换成功
            VOS_ERR     转换失败
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_Ac2uc(
    VOS_CHAR                           *pcStr,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucRtn
)
{
    VOS_UINT32                          ulLength;           /* current Length */
    VOS_UINT8                           ucTotal;            /* current Total */
    VOS_CHAR                            cCur;               /* current Char */

    /* 入口指针不能为空指针 */
    if ((VOS_NULL_PTR == pcStr) || (VOS_NULL_PTR == pucRtn))
    {
        return VOS_ERR;
    }

    /* ulLen不能为0 */
    if (0 == ulLen)
    {
        return VOS_ERR;
    }

    cCur        = *(pcStr++);
    ulLength    = 0;
    ucTotal     = 0;
    while(ulLength++ < ulLen)
    {
        if ((cCur >= '0') && (cCur <= '9'))
        {
            /* 0xFF = 255 */
            if ( ((ucTotal == MTA_UNSIGNED_CHAR_FORMER_TWO_DIGIT) && (cCur > MTA_UNSIGNED_CHAR_LAST_DIGIT))
              || (ucTotal > MTA_UNSIGNED_CHAR_FORMER_TWO_DIGIT) )
            {
                /* 超过了数据类型支持的最大值 */
                return VOS_ERR;
            }
            ucTotal = (VOS_UINT8)((ucTotal * 10) + (cCur - '0'));
            cCur    = *(pcStr++);
        }
        else
        {
            return VOS_ERR;
        }
    }

    *pucRtn = ucTotal;
    return VOS_OK;
}


/*****************************************************************************
函 数 名  : TAF_MTA_Ac2sl
功能描述  : 把字符串转成有符号32位整型值
输入参数  : pcStr      待转换的字符串首地址
            ulLen       待转换的字符串长度
            plRtn       转换后的有符号整型值
输出参数  : 无
返 回 值  : VOS_OK      转换成功
            VOS_ERR     转换失败
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_Ac2sl(
    VOS_CHAR                           *pcStr,
    VOS_UINT32                          ulLen,
    VOS_INT32                          *plRtn
)
{
    VOS_INT32                           lSign;
    VOS_INT32                           lTotal;             /* current Total */
    VOS_UINT32                          ulLength;           /* current Length */
    VOS_CHAR                            cCur;               /* current Char */
    VOS_CHAR                            cTmp;

    /* 入口指针不能为空指针 */
    if ((VOS_NULL_PTR == pcStr) || (VOS_NULL_PTR == plRtn))
    {
        return VOS_ERR;
    }

    /* ulLen不能为0 */
    if (0 == ulLen)
    {
        return VOS_ERR;
    }

    cCur        = *(pcStr++);
    ulLength    = 0;
    lTotal      = 0;

    /* 判断符号位 */
    if ('-' == cCur )
    {
        lSign = MTA_NEGATIVE;
        cCur  = *(pcStr++);
        cTmp  = MTA_SIGNED_LONG_NEGATIVE_LAST_DIGIT;
        ulLength++;
    }
    else if ('+' == cCur )
    {
        lSign = MTA_POSITIVE;
        cCur  = *(pcStr++);
        cTmp  = MTA_SIGNED_LONG_POSITIVE_LAST_DIGIT;
        ulLength++;
    }
    else
    {
        /* 无"+"、"-"符号，则按照正数处理 */
        lSign = MTA_POSITIVE;
        cTmp  = MTA_SIGNED_LONG_POSITIVE_LAST_DIGIT;
    }

    while(ulLength++ < ulLen)
    {
        if ((cCur >= '0') && (cCur <= '9'))
        {
            /* 0x7FFFFFFF = 2147483647 */
            if ( ((lTotal == MTA_SIGNED_LONG_FORMER_NINE_DIGIT) && (cCur > cTmp))
              || (lTotal > MTA_SIGNED_LONG_FORMER_NINE_DIGIT) )
            {
                /* 超过了数据类型支持的最大值 */
                return VOS_ERR;
            }
            lTotal  = (10 * lTotal) + (cCur - '0');
            cCur    = *(pcStr++);
        }
        else
        {
            return VOS_ERR;
        }
    }

    *plRtn = lTotal * lSign;
    return VOS_OK;
}

/*lint +e958*/

/*****************************************************************************
 函 数 名  : TAF_MTA_AcNums2DecNums
 功能描述  : MTA模块数字字符串转换为十进制数字串
 输入参数  : VOS_UINT8     *pucAsciiNum -- 待转换字符数组
             VOS_UINT32     ulLen       -- 字符数组长度
 输出参数  : VOS_UINT8     *pucDecNum   -- 转转换后的十进制数字串
 返 回 值  : VOS_OK         -- 转换成功
             VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月04日
    作    者   : l00198894
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 TAF_MTA_AcNums2DecNums(
    VOS_UINT8                          *pucAsciiNum,
    VOS_UINT8                          *pucDecNum,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulIndex         = 0;

    /* 参数指针由调用者保证不为NULL, 该处不做判断 */

    for (ulIndex = 0; ulIndex < ulLen; ulIndex++)
    {
        /* 判断是否是数字 */
        if ( ('0' <= pucAsciiNum[ulIndex]) && ('9' >= pucAsciiNum[ulIndex]) )
        {
            pucDecNum[ulIndex] = pucAsciiNum[ulIndex] - '0';
        }
        else
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 函 数 名  : TAF_MTA_GetNetMode
 功能描述  : 获得当前制式
 输入参数  :
 输出参数  : NAS_INFO_CLT_RATMODE_ENUM_UINT8     *penNetMode
                -- 当前制式
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月01日
    作    者   : g00322017
    修改内容   : 新增函数

*****************************************************************************/
NAS_INFO_CLT_RATMODE_ENUM_UINT8 TAF_MTA_GetNetMode(VOS_VOID)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8         enRatType;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranctrlMode;
    NAS_INFO_CLT_RATMODE_ENUM_UINT8     enNetMode;

    /* 获取当前接入技术 */
    enRatType                           = TAF_SDC_GetSysMode();
    enUtranctrlMode                     = NAS_UTRANCTRL_GetCurrUtranMode();

    if (TAF_SDC_SYS_MODE_GSM == enRatType)
    {
        enNetMode = NAS_INFO_CLT_RATMODE_GSM;
    }
    else if ((TAF_SDC_SYS_MODE_WCDMA       == enRatType)
         && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enUtranctrlMode))
    {
        enNetMode = NAS_INFO_CLT_RATMODE_WCDMA;
    }
    else if (TAF_SDC_SYS_MODE_LTE == enRatType)
    {
        enNetMode = NAS_INFO_CLT_RATMODE_LTE;
    }
    else if ((TAF_SDC_SYS_MODE_WCDMA == enRatType)
         && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranctrlMode))
    {
        enNetMode = NAS_INFO_CLT_RATMODE_TDS;
    }
    else
    {
        enNetMode = NAS_INFO_CLT_RATMODE_BUTT;
    }

    return enNetMode;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
