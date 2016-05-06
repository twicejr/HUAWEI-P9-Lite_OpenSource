

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "PsCommonDef.h"
#include  "MnErrorCode.h"
#include  "MnMsgApi.h"
#include  "MnMsgTs.h"
/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
#include "TafStdlib.h"
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

VOS_UINT32 MSG_EncodeUserData(
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding,
    MN_MSG_USER_DATA_STRU               *pstUserData,
    VOS_UINT8                           *pucUserData,
    VOS_UINT32                          *pucLen
);

/*****************************************************************************
  2 常量定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID                                        PS_FILE_ID_MNMSG_ENCODE_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */

/*****************************************************************************
  3 宏定义
*****************************************************************************/

/*****************************************************************************
  4 变量定义
*****************************************************************************/
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
/*lint -save -e958 */

/*****************************************************************************
  5 函数实现
*****************************************************************************/

/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */

/*****************************************************************************
 函 数 名  : MN_ChkNumType
 功能描述  : 同步函数,号码类型检查,参考协议23040 9.1.2.5
 输入参数  : enNumType      - 号码类型
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR号码类型检查通过 其他,号码类型检查失败
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年1月21日
    作    者   : fuyingjun
    修改内容   : 新生成函数
  2.日    期   : 2010年2月21日
    作    者   : f62575
    修改内容   : 问题单号：AT2D16979，UE侧不再检查地址的TON和NPI类型
*****************************************************************************/
TAF_UINT32 MN_ChkNumType(
    MN_MSG_TON_ENUM_U8                  enNumType
)
{
    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MN_ChkNumPlan
 功能描述  : 同步函数,拨号计划类型检查,参考协议23040 9.1.2.5
 输入参数  : enNumPlan - 拨号计划类型
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR拨号计划类型检查通过 其他,拨号计划类型检查失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月13日
    作    者   : fuyingjun
    修改内容   : 新生成函数
  2.日    期   : 2010年2月21日
    作    者   : f62575
    修改内容   : 问题单号：AT2D16717，UE侧不再检查地址的TON和NPI类型
*****************************************************************************/
TAF_UINT32 MN_ChkNumPlan(
    MN_MSG_NPI_ENUM_U8                  enNumPlan
)
{
    return MN_ERR_NO_ERROR;
}

/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */


/*****************************************************************************
 函 数 名  : MN_MSG_ChkDate
 功能描述  : 检查日期是否在有效范围内
 输入参数  : pstTimeStamp   - 绝对有效时间数据结构,其中的年月日都是用BCD码顺序表示的;
 输出参数  : pucInvalidType - 无效日期类型集合;
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月1日
    作    者   : fuyingjun
    修改内容   : 新生成函数
  2.日    期   : 2010年04月10日
    作    者   : f62575
    修改内容   : 问题单号AT2D18035
                 写PDU短信到SIM卡,BALONG对TP-SCTS的检查与标杆不一致；
  3.日    期   : 2013年12月24日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
VOS_UINT32 MN_MSG_ChkDate(
    const MN_MSG_TIMESTAMP_STRU         *pstTimeStamp,
    MN_MSG_DATE_INVALID_TYPE_ENUM_UINT8 *pucInvalidType
)
{
    VOS_UINT8                           ucYear;
    VOS_UINT8                           ucMonth;
    VOS_UINT8                           ucDay;
    VOS_UINT8                           ucHour;
    VOS_UINT8                           ucMinute;
    VOS_UINT8                           ucSecond;
    MN_MSG_DATE_INVALID_TYPE_ENUM_UINT8 ucInvalidType;
    VOS_UINT32                          ulRet;

    ucInvalidType = 0;

    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
    ulRet = TAF_STD_ConvertBcdToDeciDigit(pstTimeStamp->ucYear, VOS_FALSE, &ucYear);
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ChkDate: Month is invalid.");
        ucInvalidType |= MN_MSG_DATE_INVALID_YEAR;
    }

    /*将BCD码表示的月日小时分钟秒转换成十进制数进行有效性检查；*/
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
    ulRet = TAF_STD_ConvertBcdToDeciDigit(pstTimeStamp->ucMonth, VOS_FALSE, &ucMonth);
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
    if ((MN_ERR_NO_ERROR != ulRet)
     || (ucMonth > MN_MSG_MONTHS_IN_A_YEAR))
    {
        MN_WARN_LOG("MN_MSG_ChkDate: Month is invalid.");
        ucInvalidType |= MN_MSG_DATE_INVALID_MONTH;
    }

    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
    ulRet = TAF_STD_ConvertBcdToDeciDigit(pstTimeStamp->ucDay, VOS_FALSE, &ucDay);
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
    if ((MN_ERR_NO_ERROR != ulRet)
     || (ucDay > MN_MSG_MAX_DAYS_IN_A_MONTH))
    {
        MN_WARN_LOG("MN_MSG_ChkDate: Date is invalid.");
        ucInvalidType |= MN_MSG_DATE_INVALID_DAY;
    }

    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
    ulRet = TAF_STD_ConvertBcdToDeciDigit(pstTimeStamp->ucHour, VOS_FALSE, &ucHour);
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
    if ((MN_ERR_NO_ERROR != ulRet)
     || (ucHour > (MN_MSG_HOURS_IN_A_DAY - 1)))
    {
        MN_WARN_LOG("MN_MSG_ChkDate: Hour is invalid.");
        ucInvalidType |= MN_MSG_DATE_INVALID_HOUR;
    }

    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
    ulRet = TAF_STD_ConvertBcdToDeciDigit(pstTimeStamp->ucMinute, VOS_FALSE, &ucMinute);
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
    if ((MN_ERR_NO_ERROR != ulRet)
     || (ucMinute > (MN_MSG_MINUTES_IN_AN_HOUR - 1)))
    {
        MN_WARN_LOG("MN_MSG_ChkDate: Minute is invalid.");
        ucInvalidType |= MN_MSG_DATE_INVALID_MINUTE;
    }

    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
    ulRet = TAF_STD_ConvertBcdToDeciDigit(pstTimeStamp->ucSecond, VOS_FALSE, &ucSecond);
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
    if ((MN_ERR_NO_ERROR != ulRet)
     || (ucSecond > (MN_MSG_SECONDS_IN_A_MINUTE - 1)))
    {
        MN_WARN_LOG("MN_MSG_ChkDate: Second is invalid.");
        ucInvalidType |= MN_MSG_DATE_INVALID_SECOND;
    }

    *pucInvalidType = ucInvalidType;
    if (0 == ucInvalidType)
    {
        return MN_ERR_NO_ERROR;
    }
    else
    {
        return MN_ERR_CLASS_SMS_INVALID_DATE;
    }
}


/*****************************************************************************
 函 数 名  : MSG_EncodeTimeStamp
 功能描述  : 同步函数,根据绝对有效时间数据结构构造TPDU格式的VP单元
 输入参数  : pstTimeStamp   - 绝对有效时间数据结构,其中的年月日都是用BCD码顺序表示的;
 输出参数  : pucValidPeriod - TPDU格式的绝对有效期VP单元
             pulLen         - TPDU格式的VP单元长度
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年1月7日
    作    者   : fuyingjun
    修改内容   : 新生成函数
  2.日    期   : 2010年04月10日
    作    者   : f62575
    修改内容   : 问题单号AT2D18035
                 写PDU短信到SIM卡,BALONG对TP-SCTS的检查与标杆不一致；
  3.日    期   : 2013年12月24日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
LOCAL VOS_UINT32 MSG_EncodeTimeStamp(
    const MN_MSG_TIMESTAMP_STRU         *pstTimeStamp,
    VOS_UINT8                           *pucValidPeriod,
    VOS_UINT32                          *pulLen
)
{
    VOS_UINT8                           ucAbsTimeZone;
    VOS_UINT8                           ucAlgebraicSign;
    VOS_UINT8                           ucDateInvalidType;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pstTimeStamp)
     || (VOS_NULL_PTR == pucValidPeriod)
     || (VOS_NULL_PTR == pulLen))
    {
        MN_ERR_LOG("MSG_EncodeTimeStamp: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    ulRet = MN_MSG_ChkDate(pstTimeStamp, &ucDateInvalidType);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_EncodeTimeStamp: Date is invalid.");
    }

    /*时区有效性检查，根据协议27005 <dt>示例可知(1hour <-> 4)必须在-48-48之间；*/
    if ((pstTimeStamp->cTimezone > MN_MSG_MAX_TIMEZONE_VALUE)
     || (pstTimeStamp->cTimezone < ((-1)*MN_MSG_MAX_TIMEZONE_VALUE)))
    {
        MN_WARN_LOG("MSG_EncodeTimeStamp: Time zone is invalid.");
    }

    /*根据协议23040 9.2.3.11和9.1.2.3 在VP中BCD码是反序放置的，
      所以将结构中BCD码反序后赋给输出 */
    MN_MSG_REVERSE_BCD(pucValidPeriod[0], pstTimeStamp->ucYear);
    MN_MSG_REVERSE_BCD(pucValidPeriod[1], pstTimeStamp->ucMonth);
    MN_MSG_REVERSE_BCD(pucValidPeriod[2], pstTimeStamp->ucDay);
    MN_MSG_REVERSE_BCD(pucValidPeriod[3], pstTimeStamp->ucHour);
    MN_MSG_REVERSE_BCD(pucValidPeriod[4], pstTimeStamp->ucMinute);
    MN_MSG_REVERSE_BCD(pucValidPeriod[5], pstTimeStamp->ucSecond);

    /*时区在协议23040 9.2.3.11中需要将绝对值转换成反序BCD码再或上表示负数的符号*/
    if (pstTimeStamp->cTimezone < 0)
    {
        ucAbsTimeZone = (VOS_UINT8)((-1)*pstTimeStamp->cTimezone);
        ucAlgebraicSign = MN_MSG_NEGATIVE_ALGEBRAICSIGN;
    }
    else
    {
        ucAbsTimeZone = (VOS_UINT8)pstTimeStamp->cTimezone;
        ucAlgebraicSign = 0x00;
    }
    pucValidPeriod[6]  = ucAlgebraicSign;
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
    pucValidPeriod[6] |= TAF_STD_ConvertDeciDigitToBcd(ucAbsTimeZone, VOS_TRUE);
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */

    *pulLen = MN_MSG_ABSOLUTE_TIMESTAMP_LEN;
    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeValidPeriod
 功能描述  : 同步函数,根据有效时间数据结构构造TPDU格式的VP单元，
             参考协议23040 9.2.3.12
 输入参数  : pstValidPeriod - 用户输入的有效时间数据结构
 输出参数  : pucValidPeriod - TPDU的VP单元
             pulLen         - TPDU的VP单元长度
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月7日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT32 MSG_EncodeValidPeriod(
    const MN_MSG_VALID_PERIOD_STRU      *pstValidPeriod,
    VOS_UINT8                           *pucValidPeriod,
    VOS_UINT32                          *pulLen
)
{
    VOS_UINT32                          ulRet               = MN_ERR_NO_ERROR;

    if ((VOS_NULL_PTR == pstValidPeriod)
     || (VOS_NULL_PTR == pucValidPeriod)
     || (VOS_NULL_PTR == pulLen))
    {
        MN_ERR_LOG("MSG_EncodeValidPeriod: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    switch (pstValidPeriod->enValidPeriod)
    {
        case MN_MSG_VALID_PERIOD_NONE:
            *pulLen = 0;
            break;
        case MN_MSG_VALID_PERIOD_RELATIVE:
            *pulLen = 1;
            *pucValidPeriod = pstValidPeriod->u.ucOtherTime;
            break;
        case MN_MSG_VALID_PERIOD_ABSOLUTE:
            ulRet = MSG_EncodeTimeStamp((MN_MSG_TIMESTAMP_STRU *)&(pstValidPeriod->u.stAbsoluteTime),
                                         pucValidPeriod,
                                         pulLen);
            break;
        default:
            MN_WARN_LOG("MSG_EncodeValidPeriod: The type of valid period is not supported!");
            return MN_ERR_CLASS_SMS_INVALID_VPF;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : MN_MSG_EncodeRelatTime
 功能描述  : 同步函数,根据绝对有效时间数据结构获得相对有效时间VP值，
             参考协议23040 9.2.3.12.1
 输入参数  : pstRelatTime      - 绝对有效时间数据结构
 输出参数  : pucRelatTime      - 指向23040协议规定的相对有效时间VP值
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月8日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_MSG_EncodeRelatTime(
    const MN_MSG_TIMESTAMP_STRU         *pstRelatTime,
    VOS_UINT8                           *pucRelatTime
)
{
    VOS_UINT16                          usTotalDay;
    VOS_UINT32                          ulTotalHour;
    VOS_UINT32                          ulTotalMinute;
    VOS_UINT8                           ucDateInvalidType;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pstRelatTime)
     || (VOS_NULL_PTR == pucRelatTime))
    {
        MN_ERR_LOG("MN_MSG_EncodeRelatTime: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    /*将BCD码表示的月日小时分钟秒转换成十进制数进行有效性检查；*/
    ulRet = MN_MSG_ChkDate(pstRelatTime, &ucDateInvalidType);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }

    /*将pstRelatTime转换成usTotalDay和ucTotalMinute*/
    usTotalDay      = (VOS_UINT16)(MN_MSG_DAYS_IN_A_YEAR * pstRelatTime->ucYear);
    usTotalDay     += (VOS_UINT16)(MN_MSG_DAYS_IN_A_MONTH * pstRelatTime->ucMonth);
    usTotalDay     += pstRelatTime->ucDay;

    /*TP-VP最多只能表示441天的有效期*/
    if (usTotalDay > MN_MSG_MAX_RELAT_VP_DAYS)
    {
        MN_WARN_LOG("MN_MSG_EncodeRelatTime: Parameter of the function is invalid.");
        return MN_ERR_CLASS_SMS_INVALID_RELATTTIME;
    }

    /*197～255：（VP–192）*1 周，表示时间范围为31天(约为5周) － 441天(196-166)*/
    if (usTotalDay > MN_MSG_DAYS_IN_A_MONTH)
    {
        *pucRelatTime = (VOS_UINT8)(((usTotalDay + 6)/7) + 192);
        return MN_ERR_NO_ERROR;
    }

    /*168～196：（VP–166）*1 日,表示时间范围为2(168-166)天 － 30天(196-166)*/
    if (usTotalDay > 1)
    {
        *pucRelatTime = (VOS_UINT8)(usTotalDay + 166);
        return MN_ERR_NO_ERROR;
    }

    ulTotalHour   = (MN_MSG_HOURS_IN_A_DAY * usTotalDay) + pstRelatTime->ucHour;
    ulTotalMinute = MN_MSG_MINUTES_IN_AN_HOUR * ulTotalHour;
    ulTotalMinute+= pstRelatTime->ucMinute;

    if (ulTotalMinute < 1)
    {
        *pucRelatTime = 0;
        return MN_ERR_NO_ERROR;
    }

    /*144～167：12 小时+（VP–143）*30 分钟,表示时间范围为12小时 -> 1天*/
    if (ulTotalMinute > (12 * MN_MSG_MINUTES_IN_AN_HOUR))
    {
        *pucRelatTime = (VOS_UINT8)((((ulTotalMinute - (12 * MN_MSG_MINUTES_IN_AN_HOUR)) + 29)/30) + 143);
        return MN_ERR_NO_ERROR;
    }

    /* 0～143：（VP+1）* 5 分钟,表示时间范围为5分钟 － 12小时*/
    *pucRelatTime = (VOS_UINT8)(((ulTotalMinute + 4)/5) - 1);
    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MN_MSG_EncodeAddress
 功能描述  : 同步函数,
             根据MN_MSG_ASCII_ADDR_STRU地址数据结构生成TP层地址信息单元，
             参考协议23040 9.1.2.5
             或
             根据MN_MSG_ASCII_ADDR_STRU地址数据结构生成RP层地址信息单元，
             参考协议24011 8.2.5.1
 输入参数  : pstAsciiAddr - MN_MSG_ASCII_ADDR_STRU结构表示的地址
             bRpAddr      - 是否编码成RP层地址单元
 输出参数  : pucAddr      - TP层的TPDU格式的地址/RP层地址信息单元
             pulLen       - TPDU格式的地址长度/RP层地址信息单元长度
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月21日
    作    者   : fuyingjun
    修改内容   : 新生成函数
  2.日    期   : 2012年6月26日
    作    者   : 傅映君 62575
    修改内容   : DTS2012062202118，RP层地址的所有编码类型都按BCD编码，仅TP层地址
                 支持7BIT编码地址；
  3.日    期   : 2013年12月24日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目

*****************************************************************************/
VOS_UINT32 MN_MSG_EncodeAddress(
    const MN_MSG_ASCII_ADDR_STRU        *pstAsciiAddr,
    VOS_BOOL                            bRpAddr,
    VOS_UINT8                           *pucAddr,
    VOS_UINT32                          *pulLen
)
{
    VOS_UINT32                          ulNumLen;                               /*号码长度*/
    VOS_UINT8                           *pucNum;                                /*指向实际号码（不包括+号）的指针*/
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT8                           ucAddrBcdLen;
    VOS_UINT32                          ulAlphaNumLen;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pstAsciiAddr)
     || (VOS_NULL_PTR == pucAddr)
     || (VOS_NULL_PTR == pulLen))
    {
        MN_ERR_LOG("MN_MSG_EncodeAddress: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    if (0 == pstAsciiAddr->ulLen)
    {
        if (VOS_TRUE == bRpAddr)
        {
            *pucAddr = 0;
            *pulLen = 1;
        }
        else
        {
            *pucAddr = 0;
            *(pucAddr + 1) = 0;
            *pulLen = 2;
        }
        return MN_ERR_NO_ERROR;
    }

    /*如果号码的首字符是'+'号，表示国际号码*/
    if ('+' == pstAsciiAddr->aucAsciiNum[0])
    {
        if (MN_MSG_TON_INTERNATIONAL != pstAsciiAddr->enNumType)
        {
            MN_WARN_LOG("MN_MSG_EncodeAddress: The address string begins with '+'"
                       "while number type indicates non-international number type");
            return MN_ERR_CLASS_SMS_INVALID_NUMTYPE;
        }
        pucNum = (VOS_UINT8 *)&(pstAsciiAddr->aucAsciiNum[1]);
        ulNumLen = pstAsciiAddr->ulLen - 1;
    }
    else
    {
        pucNum = (VOS_UINT8 *)pstAsciiAddr->aucAsciiNum;
        ulNumLen = pstAsciiAddr->ulLen;
    }

    /*号码长度应该在范围1 - 20之间，参考协议24011 8.2.5.1和8.2.5.2
                                            23040 9.2.2 和 9.1.2.5*/
    if ((ulNumLen > MN_MSG_MAX_ADDR_LEN)
     || (ulNumLen < MN_MSG_MIN_ADDR_LEN))
    {
        MN_WARN_LOG("MN_MSG_EncodeAddress: The length of address is invalid.");
        return MN_ERR_CLASS_SMS_INVALID_ADDRLEN;
    }

    /*号码类型,拨号计划类型有效性检查*/
    ulRet = MN_ChkNumPlan(pstAsciiAddr->enNumPlan);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_EncodeAddress: Numbering plan is invalid");
        return ulRet;
    }
    ulRet = MN_ChkNumType(pstAsciiAddr->enNumType);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_EncodeAddress: Number type is invalid");
        return ulRet;
    }
    /*lint -e961*/
    /*第0个字节为号码（包括号码类型）的字节长度:
    根据协议24011 8.2.5.1 8.2.5.2 和24008 10.5.4.9 RP层的地址IE中长度指BCD号码长度，包含地址类型的占位
    根据协议23040 9.1.2.5 TP层的地址长度为有效号码字符个数*/
    if (VOS_TRUE == bRpAddr)
    {
        pucAddr[ulPos++] = (VOS_UINT8)(((ulNumLen + 1)/2) + 1);
    }
    else
    {
        if (MN_MSG_TON_ALPHANUMERIC == pstAsciiAddr->enNumType)
        {
            pucAddr[ulPos++] = (VOS_UINT8)(((ulNumLen * 7) + 3)/4);
        }
        else
        {
            pucAddr[ulPos++] = (VOS_UINT8)ulNumLen;
        }
    }
    /*lint +e961*/

    /* 根据协议23040 9.1.2.5 地址类型域格式如下所示
        bit7   bit6    -   bit4             bit3    -   bit0
         1      type of number      Numbering-plan-identification */
    pucAddr[ulPos]      = 0x80;
    pucAddr[ulPos]     |= (pstAsciiAddr->enNumPlan & 0x0f);
    pucAddr[ulPos]     |= (VOS_UINT8)((pstAsciiAddr->enNumType << 4) & 0x70);
    ulPos++;

    if ((VOS_TRUE != bRpAddr)
     && (MN_MSG_TON_ALPHANUMERIC == pstAsciiAddr->enNumType))
    {
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
        ulRet = TAF_STD_Pack7Bit(pstAsciiAddr->aucAsciiNum,
                                 pstAsciiAddr->ulLen,
                                 0,
                                 &(pucAddr[ulPos]),
                                 &ulAlphaNumLen);
        if (VOS_OK != ulRet)
        {
            return MN_ERR_CLASS_INVALID_TP_ADDRESS;
        }
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
        ucAddrBcdLen = (VOS_UINT8)ulAlphaNumLen;
    }
    else
    {
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
        ulRet = TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR *)pucNum,
                                    &(pucAddr[ulPos]),
                                    &ucAddrBcdLen);
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
    }
    *pulLen = ulPos + ucAddrBcdLen;
    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeUdhConcat8
 功能描述  : 编码参考编号为8BIT的连续短消息IEI，Refer to 23040 9.2.3.24.1
 输入参数  : pstConcatenatedSms - 参考编号为8BIT的连续短消息IEI的数据结构
 输出参数  : pucUdh             - 参考编号为8BIT的连续短消息IEI
 返 回 值  : 参考编号为8BIT的连续短消息IEI长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月12日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8  MSG_EncodeUdhConcat8(
    const MN_MSG_UDH_CONCAT_8_STRU      *pstConcatenatedSms,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstConcatenatedSms)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeUdhConcat8: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    if (pstConcatenatedSms->ucSeqNum > pstConcatenatedSms->ucTotalNum)
    {
        MN_WARN_LOG("MSG_EncodeUdhConcat8: Sequence number is bigger than total number.");
        return 0;
    }

    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_CONCAT_8;
    pucUdh[ucLen++] = MN_MSG_UDH_CONCAT_8_IEL;
    pucUdh[ucLen++] = pstConcatenatedSms->ucMr;
    pucUdh[ucLen++] = pstConcatenatedSms->ucTotalNum;
    pucUdh[ucLen++] = pstConcatenatedSms->ucSeqNum;
    /*lint +e961*/
    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeUdhConcat16
 功能描述  : 编码参考编号为16BIT的连续短消息IEI，Refer to 23040 9.2.3.24.8
 输入参数  : pstConcatenatedSms - 参考编号为16BIT的连续短消息UDH IEI数据结构
 输出参数  : pucUdh             - 参考编号为16BIT的连续短消息UDH IEI
 返 回 值  : 参考编号为16BIT的连续短消息UDH IEI长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月12日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8  MSG_EncodeUdhConcat16(
    const MN_MSG_UDH_CONCAT_16_STRU     *pstConcatenatedSms,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8 ucLen = 0;

    if ((VOS_NULL_PTR == pstConcatenatedSms)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeUdhConcat16: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    if (pstConcatenatedSms->ucSeqNum > pstConcatenatedSms->ucTotalNum)
    {
        MN_WARN_LOG("MSG_EncodeUdhConcat16: Sequence number is bigger than total number.");
        return 0;
    }
    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_CONCAT_16;
    pucUdh[ucLen++] = MN_MSG_UDH_CONCAT_16_IEL;
    pucUdh[ucLen++] = (VOS_UINT8)((pstConcatenatedSms->usMr >> 8) & 0xff);
    pucUdh[ucLen++] = (VOS_UINT8) (pstConcatenatedSms->usMr & 0xff);
    pucUdh[ucLen++] = pstConcatenatedSms->ucTotalNum;
    pucUdh[ucLen++] = pstConcatenatedSms->ucSeqNum;
    /*lint +e961*/

    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeUdhSpecialSm
 功能描述  : 编码特殊短消息指示IEI，Refer to 23040 9.2.3.24.2
 输入参数  : pstSpecialSm - 特殊短消息指示IEI数据结构
 输出参数  : pucUdh       - 特殊短消息指示IEI
 返 回 值  : 特殊短消息指示IEI长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月12日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeUdhSpecialSm(
    const MN_MSG_UDH_SPECIAL_SMS_STRU   *pstSpecialSm,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstSpecialSm)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeUdhSpecialSm: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_SPECIAL_SM;
    pucUdh[ucLen++] = MN_MSG_UDH_SPECIAL_SM_IEL;
    /*lint +e961*/

    /*Octet 1 Message Indication type and Storage.*/
    /*Bit 7 Indicates whether or not the message shall be stored.*/
    /*Bits 6 and 5 indicate the profile ID of the Multiple Subscriber Profile (see 3GPP TS 23.097 [41]).*/
    /*Bits 432 indicate the extended message indication type.*/
    /*Bits 0 and 1 indicate the basic message indication type.*/
    if (MN_MSG_MSG_WAITING_STORE == pstSpecialSm->enMsgWaiting)
    {
        pucUdh[ucLen] = 0x80;
    }
    else
    {
        pucUdh[ucLen] = 0x00;
    }
    pucUdh[ucLen] |= (pstSpecialSm->enProfileId << 5) & 0x60;
    pucUdh[ucLen] |= (pstSpecialSm->enExtMsgInd << 2) & 0x1c;
    pucUdh[ucLen] |= pstSpecialSm->enMsgWaitingKind   & 0x03;
    ucLen++;

    /*Octet 2 Message Count.*/
    /*lint -e961*/
    pucUdh[ucLen++] = pstSpecialSm->ucMsgCount;
    /*lint +e961*/

    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeUdhAppPort_8
 功能描述  : 编码8BIT应用端口IEI，Refer to 23040 9.2.3.24.3
 输入参数  : pstAppPort - 8BIT应用端口IEI数据结构
 输出参数  : pucUdh     - 8BIT应用端口IEI
 返 回 值  : 8BIT应用端口IEI长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月12日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeUdhAppPort_8(
    const MN_MSG_UDH_APPPORT_8_STRU     *pstAppPort,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstAppPort)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeUdhAppPort_8: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_PORT_8;
    pucUdh[ucLen++] = MN_MSG_UDH_APPPORT_8_IEL;
    pucUdh[ucLen++] = pstAppPort->ucDestPort;
    pucUdh[ucLen++] = pstAppPort->ucOrigPort;
    /*lint +e961*/
    return ucLen;

}

/*****************************************************************************
 函 数 名  : MSG_EncodeUdhAppPort_16
 功能描述  : 编码8BIT应用端口IEI，Refer to 23040 9.2.3.24.4
 输入参数  : pstAppPort - 16BIT应用端口IEI数据结构
 输出参数  : pucUdh     - 16BIT应用端口IEI
 返 回 值  : 16BIT应用端口IEI长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月12日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeUdhAppPort_16(
    const MN_MSG_UDH_APPPORT_16_STRU    *pstAppPort,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstAppPort)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeUdhAppPort_16: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_PORT_16;
    pucUdh[ucLen++] = MN_MSG_UDH_APPPORT_16_IEL;
    pucUdh[ucLen++] = (pstAppPort->usDestPort >> 8) & 0xff;
    pucUdh[ucLen++] =  pstAppPort->usDestPort       & 0xff;
    pucUdh[ucLen++] = (pstAppPort->usOrigPort >> 8) & 0xff;
    pucUdh[ucLen++] =  pstAppPort->usOrigPort       & 0xff;
    /*lint +e961*/
    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeUdhSmscCtrl
 功能描述  : 编码SMSC控制参数IEI, Refer to23040 9.2.3.24.5
 输入参数  : pstSmscCtrl    - SMSC控制参数IEI数据结构
 输出参数  : pucUdh         - SMSC控制参数IEI
 返 回 值  : SMSC控制参数IEI长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeUdhSmscCtrl(
    const MN_MSG_UDH_SMSC_CTRL_STRU     *pstSmscCtrl,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;
    MN_MSG_SELSTATUS_REPORT_STRU        *pstSelStatusReport;

    if ((VOS_NULL_PTR == pstSmscCtrl)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeUdhSmscCtrl: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_SMSC_CTRL;
    pucUdh[ucLen++] = MN_MSG_UDH_SMSCCTRL_IEL;
    /*lint +e961*/
    pstSelStatusReport = (MN_MSG_SELSTATUS_REPORT_STRU *)&(pstSmscCtrl->stSelectiveStatusReport);
    pucUdh[ucLen]            = 0x00;
    if (VOS_TRUE ==  pstSelStatusReport->bCompletionReport)
    {
        pucUdh[ucLen]  |= MN_MSG_SMSCCTRL_TRANSACTION_CMPL_REPORT_MASK;
    }
    if (VOS_TRUE == pstSelStatusReport->bPermErrReport)
    {
        pucUdh[ucLen]  |= MN_MSG_SMSCCTRL_PERMANENT_ERR_REPORT_MASK;
    }
    if (VOS_TRUE == pstSelStatusReport->bTempErrNoneAttemptReport)
    {
        pucUdh[ucLen]  |= MN_MSG_SMSCCTRL_TEMP_ERR_NOT_ATTEMPT_REPORT_MASK;
    }
    if (VOS_TRUE == pstSelStatusReport->bTempErrWithAttemptReport)
    {
        pucUdh[ucLen]  |= MN_MSG_SMSCCTRL_TEMP_ERR_ATTEMPT_REPORT_MASK;
    }
    if (VOS_TRUE == pstSelStatusReport->bActivation)
    {
        pucUdh[ucLen]  |= MN_MSG_SMSCCTRL_DEACT_STATUS_REPORT_MASK;
    }
    if (VOS_TRUE == pstSelStatusReport->bOrigUdhInclude)
    {
        pucUdh[ucLen]  |= MN_MSG_SMSCCTRL_ORIGUDH_INCLUDE_MASK;
    }

    ucLen++;
    return ucLen;
}


/*****************************************************************************
 函 数 名  : MSG_EncodeUdhSourceInd
 功能描述  : 编码UDH源指示IEI,Refer to 23040 9.2.3.24.6
 输入参数  : pstSrcInd UDH源指示IEI数据结构
 输出参数  : pucUdh UDH源指示IEI
 返 回 值  : UDH源指示IEI长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月12日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeUdhSourceInd(
    const MN_MSG_UDH_SOURCE_IND_STRU    *pstSrcInd,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstSrcInd)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeUdhSourceInd: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_SOURCE;
    pucUdh[ucLen++] = MN_MSG_UDH_SOURCE_IEL;
    pucUdh[ucLen++] = pstSrcInd->enOrgEntity;
    /*lint +e961*/

    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeUdhTextFormat
 功能描述  : 编码增强短信服务EMS编码文本格式IEI
 输入参数  : pstTextFormat  - 文本格式IEI数据结构
 输出参数  : pucUdh         - 文本格式IEI
 返 回 值  : 文本格式IEI长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月12日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeUdhTextFormat(
    const MN_MSG_UDH_TEXT_FORMAT_STRU   *pstTextFormat,
    VOS_UINT8                           *pucUdh
)
{
    /*Refer to 23040 9.2.3.24.10.1.1*/
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstTextFormat)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeUdhTextFormat: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/    
    pucUdh[ucLen++] = MN_MSG_UDH_TEXT_FORMATING;
    pucUdh[ucLen++] = MN_MSG_UDH_TEXT_FORMATING_IEL;
    pucUdh[ucLen++] = pstTextFormat->ucStartPos;
    pucUdh[ucLen++] = pstTextFormat->ucLen;
    /*lint +e961*/
    pucUdh[ucLen]   = (VOS_UINT8)(pstTextFormat->enAlign & 0x03);
    pucUdh[ucLen]  |= (VOS_UINT8)((pstTextFormat->enFontSize << 2) & 0x0c);
    if (VOS_TRUE == pstTextFormat->bStyleBold)
    {
        pucUdh[ucLen] |= 0x10;
    }
    if (VOS_TRUE == pstTextFormat->bStyleItalic)
    {
        pucUdh[ucLen] |= 0x20;
    }
    if (VOS_TRUE == pstTextFormat->bStyleUnderlined)
    {
        pucUdh[ucLen] |= 0x40;
    }
    if (VOS_TRUE == pstTextFormat->bStyleStrkthrgh)
    {
        pucUdh[ucLen] |= 0x80;
    }
    ucLen++;

    if (VOS_TRUE == pstTextFormat->stColor.bColor)
    {
        pucUdh[ucLen]  = (VOS_UINT8)(pstTextFormat->stColor.enForegroundColor & 0x0f);
        pucUdh[ucLen] |= (VOS_UINT8)((pstTextFormat->stColor.enBackgroundColor << 4) & 0xf0);
        ucLen++;
    }

    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeUdhPreDefSound
 功能描述  : Encode Predefined Sound IEI, Refer to 23040  9.2.3.24.10.1.2
 输入参数  : pstPreDftSound     - Predefined Sound IEI parameter
 输出参数  : pucUdh             - Predefined Sound IEI
 返 回 值  : Predefined Sound IEI length
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月12日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeUdhPreDefSound(
    const MN_MSG_UDH_PRE_DEF_SOUND_STRU *pstPreDefSound,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    /*Refer to 9.2.3.24.10.1.2*/
    if ((VOS_NULL_PTR == pstPreDefSound)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeUdhPreDefSound: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_PRE_DEF_SOUND;
    pucUdh[ucLen++] = MN_MSG_UDH_PRE_DEF_SOUND_IEL;
    pucUdh[ucLen++] = pstPreDefSound->ucPos;
    pucUdh[ucLen++] = pstPreDefSound->ucdNumofSound;
    /*lint +e961*/

    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeUdhUserDefSound
 功能描述  : Encode User Defined Sound IEI,Refer to 23040 9.2.3.24.10.1.3
 输入参数  : pstUserDftSound    - User Defined Sound IEI parameter
 输出参数  : pucUdh             - User Defined Sound IEI
 返 回 值  : User Defined Sound IEI length
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeUdhUserDefSound(
    const MN_MSG_UDH_USER_DEF_SOUND_STRU *pstUserDefSound,
    VOS_UINT8                            *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstUserDefSound)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeUdhUserDefSound: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_USER_DEF_SOUND;
    pucUdh[ucLen++] = pstUserDefSound->ucSizeofSound + MN_MSG_UDH_USER_DEF_SOUND_HEADER_LEN;
    pucUdh[ucLen++] = pstUserDefSound->ucPos;
    /*lint +e961*/

    PS_MEM_CPY(&(pucUdh[ucLen]),
               pstUserDefSound->aucDefSound,
               pstUserDefSound->ucSizeofSound);
    ucLen += pstUserDefSound->ucSizeofSound;

    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeUdhPreDefAnim
 功能描述  : Encode Predefined Animation IEI, Refer to 23040 9.2.3.24.10.1.4
 输入参数  : pstPreDftAnim  - Encode Predefined Animation IEI parameter
 输出参数  : pucUdh         - Encode Predefined Animation IEI
 返 回 值  : Encode Predefined Animation IEI length
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeUdhPreDefAnim(
    const MN_MSG_UDH_PRE_DEF_ANIM_STRU  *pstPreDefAnim,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstPreDefAnim)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeUdhPreDefAnim: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_PRE_DEF_ANIM;
    pucUdh[ucLen++] = MN_MSG_UDH_PRE_DEF_ANIM_IEL;
    /*position indicating in the SM data the instant the animation shall be displayed*/
    pucUdh[ucLen++] = pstPreDefAnim->ucPos;
    pucUdh[ucLen++] = pstPreDefAnim->ucNumofAnim;
    /*lint +e961*/

    return ucLen;
}
/*****************************************************************************
 函 数 名  : MSG_EncodeUdhLargeAnim
 功能描述  : Encode Large Animation IEI, Refer to 23040 9.2.3.24.10.1.5
 输入参数  : pstLargeAnim   - Large Animation IEI parameter
 输出参数  : pucUdh         - Large Animation IEI
 返 回 值  : Large Animation IEI length
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeUdhLargeAnim(
    const MN_MSG_UDH_LARGE_ANIM_STRU    *pstLargeAnim,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstLargeAnim)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeUdhLargeAnim: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_LARGE_ANIM;
    pucUdh[ucLen++] = MN_MSG_UDH_LARGE_ANIM_IEL;
    /*position indicating the instant the animation shall be displayed in the SM data*/
    pucUdh[ucLen++] = pstLargeAnim->ucPos;
    /*lint +e961*/

    /*Protocol Data Unit as described in clause 9.2.3.24.10.3.3*/
    PS_MEM_CPY(&(pucUdh[ucLen]), pstLargeAnim->aucData, MN_MSG_UDH_LARGE_ANIM_SIZE);
    ucLen += MN_MSG_UDH_LARGE_ANIM_SIZE;
    return ucLen;
}
/*****************************************************************************
 函 数 名  : MSG_EncodeUdhSmallAnim
 功能描述  : Encode Small Animation IEI, Refer to 23040 9.2.3.24.10.1.6
 输入参数  : pstSmallAnim   - Small Animation IEI parameter
 输出参数  : pucUdh         - Small Animation IEI
 返 回 值  : Small Animation IEI length
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeUdhSmallAnim(
    const MN_MSG_UDH_SMALL_ANIM_STRU    *pstSmallAnim,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstSmallAnim)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeUdhSmallAnim: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_SMALL_ANIM;
    pucUdh[ucLen++] = MN_MSG_UDH_SMALL_ANIM_IEL;
    /*position indicating the instant the animation shall be displayed in the SM data*/
    pucUdh[ucLen++] = pstSmallAnim->ucPos;
    /*lint +e961*/

    /*Protocol Data Unit as described in clause 9.2.3.24.10.3.3.*/
    PS_MEM_CPY(&(pucUdh[ucLen]), pstSmallAnim->aucData, MN_MSG_UDH_SMALL_ANIM_SIZE);
    ucLen += MN_MSG_UDH_SMALL_ANIM_SIZE;
    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeUdhLargePic
 功能描述  : Encode Large Picture IEI, Refer to 23040 9.2.3.24.10.1.7
 输入参数  : pstLargePic    - Large Picture IEI parameter
 输出参数  : pucUdh         - Large Picture IEI
 返 回 值  : Large Picture IEI parameter length
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeUdhLargePic(
    const MN_MSG_UDH_LARGE_PIC_STRU     *pstLargePic,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstLargePic)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeUdhLargePic: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_LARGE_PIC;
    pucUdh[ucLen++] = MN_MSG_UDH_LARGE_PIC_IEL;
    /*position indicating in the SM data the instant the picture shall be displayed. */
    pucUdh[ucLen++] = pstLargePic->ucPos;
    /*lint +e961*/

    /*Protocol Data Unit as described in 9.2.3.24.10.3.2*/
    PS_MEM_CPY(&(pucUdh[ucLen]), pstLargePic->aucData, MN_MSG_UDH_LARGE_PIC_SIZE);
    ucLen += MN_MSG_UDH_LARGE_PIC_SIZE;

    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeUdhSmallPic
 功能描述  : Encode Small Picture IEI , Refer to 23040 9.2.3.24.10.1.8
 输入参数  : pstSmallPic    - Small Picture IEI parameter
 输出参数  : pucUdh         - Small Picture IEI
 返 回 值  : Small Picture IEI length
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeUdhSmallPic(
    const MN_MSG_UDH_SMALL_PIC_STRU     *pstSmallPic,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstSmallPic)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeUdhSmallPic: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_SMALL_PIC;
    pucUdh[ucLen++] = MN_MSG_UDH_SMALL_PIC_IEL;
    /*position indicating in the SM data the instant the picture shall be displayed in the SM data*/
    pucUdh[ucLen++] = pstSmallPic->ucPos;
    /*lint +e961*/

    /*Protocol Data Unit as described in clause 9.2.3.24.10.3.2.*/
    PS_MEM_CPY(&(pucUdh[ucLen]), pstSmallPic->aucData, MN_MSG_UDH_SMALL_PIC_SIZE);
    ucLen += MN_MSG_UDH_SMALL_PIC_SIZE;

    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeUdhVarPic
 功能描述  : Encode Variable Picture IEI, Refer to 23040 9.2.3.24.10.1.9
 输入参数  : pstVariablePic - Variable Picture IEI parameter
 输出参数  : pucUdh         - Variable Picture IEI
 返 回 值  : Variable Picture IEI length
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeUdhVarPic(
    const MN_MSG_UDH_VAR_PIC_STRU       *pstVarPic,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;
    VOS_UINT8                           ucPduNum;

    if ((VOS_NULL_PTR == pstVarPic)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeUdhVarPic: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_VAR_PIC;
    ucPduNum = (VOS_UINT8)((pstVarPic->ucHorDim/MN_MSG_PIXELS_IN_A_OCTET) * pstVarPic->ucVertDim);
    if (ucPduNum > MN_MSG_UDH_VAR_PIC_SIZE)
    {
        MN_WARN_LOG("MSG_EncodeUdhVarPic: the number of PDU is invalid.");
        return 0;
    }

    pucUdh[ucLen++] = (VOS_UINT8)(ucPduNum + 3);
    /*position indicating in the SM data the instant the picture shall be displayed in the SM data*/
    pucUdh[ucLen++] = pstVarPic->ucPos;
    /*Horizontal dimension of the picture: 一行中象素个数需要转换成占用OCTET数，1OCTET可表示8个象素*/
    pucUdh[ucLen++] = pstVarPic->ucHorDim/MN_MSG_PIXELS_IN_A_OCTET;
    /*Vertical dimension of the picture*/
    pucUdh[ucLen++] = pstVarPic->ucVertDim;
    /*lint +e961*/

    /*Protocol Data Unit as described in clause 9.2.3.24.10.3.2*/
    PS_MEM_CPY(&(pucUdh[ucLen]), pstVarPic->aucData, ucPduNum);
    ucLen += ucPduNum;
    return ucLen;
}

/*****************************************************************************
 函 数 名  : MN_MSG_EncodeUdhUserPromt
 功能描述  : Encode User Prompt Indicator IEI, Refer to 23040 9.2.3.24.10.1.10
 输入参数  : pstUserPrompt  - User Prompt Indicator IEI parameter
 输出参数  : pucUdh         - User Prompt Indicator IEI
 返 回 值  : User Prompt Indicator IEI length
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MN_MSG_EncodeUdhUserPrompt(
    const MN_MSG_UDH_USER_PROMPT_STRU   *pstUserPrompt,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstUserPrompt)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MN_MSG_EncodeUdhUserPrompt: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    
    /*lint -e961*/

    pucUdh[ucLen++] = MN_MSG_UDH_USER_PROMPT;
    pucUdh[ucLen++] = MN_MSG_UDH_USER_PROMPT_IEL;
    pucUdh[ucLen++] = pstUserPrompt->ucNumofObjects;
    /*lint +e961*/

    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeUdhRfc822
 功能描述  : 编码User Prompt Indicator IEI , Refer to 23040 9.2.3.24.11
 输入参数  : pstRfc822  - User Prompt Indicator IEI parameter
 输出参数  : pucUdh     - User Prompt Indicator IEI
 返 回 值  : User Prompt Indicator IEI length
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeUdhRfc822(
    const MN_MSG_UDH_RFC822_STRU        *pstRfc822,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstRfc822)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeUdhRfc822: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_RFC822;
    pucUdh[ucLen++] = MN_MSG_UDH_RFC822_IEL;
    pucUdh[ucLen++] = pstRfc822->ucLen;
    /*lint +e961*/

    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeEo
 功能描述  : 编码扩展对象IE
 输入参数  : pstEo      - 扩展对象IE结构数据
 输出参数  : pucUdh     - TPDU格式的扩展对象IE
 返 回 值  : TPDU格式的扩展对象IE占用的字节数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月11日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeEo(
    const MN_MSG_UDH_EO_STRU            *pstEo,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstEo)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeEo: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    /*lint -e961*/

    pucUdh[ucLen++] = MN_MSG_UDH_EO;
    pucUdh[ucLen] = (VOS_UINT8)pstEo->usDataLen;
    if (VOS_TRUE == pstEo->bFirstSegment)
    {
        pucUdh[ucLen++] += MN_MSG_UDH_EO_HEADER_LEN;
        pucUdh[ucLen++] = pstEo->ucRefNum;
        pucUdh[ucLen++] = (VOS_UINT8)(pstEo->usTotalLen  >> 8);
        pucUdh[ucLen++] = (VOS_UINT8)(pstEo->usTotalLen & 0xff);
        MSG_SetObjForwardedFlag(pucUdh[ucLen], pstEo->bObjNotFowarded);
        MSG_SetUserPromptInd(pucUdh[ucLen], pstEo->bObjHandledAsUserPrompt);
        ucLen++;
        pucUdh[ucLen++] = pstEo->enType;
        pucUdh[ucLen++] = (VOS_UINT8)(pstEo->usPos >> 8);
        pucUdh[ucLen++] = (VOS_UINT8)(pstEo->usPos & 0xff);
    }
    else
    {
        ucLen++;
    }
    /*lint +e961*/
    PS_MEM_CPY(&pucUdh[ucLen], pstEo->aucData, pstEo->usDataLen);
    ucLen += (VOS_UINT8)pstEo->usDataLen;
    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeReo
 功能描述  : 编码重用扩展对象IE
 输入参数  : pstReo -   重用扩展对象IE数据结构
 输出参数  : pucUdh -   TPDU格式的重用扩展对象IE
 返 回 值  : TPDU格式的重用扩展对象IE占用的字节数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月11日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeReo(
    const MN_MSG_UDH_REO_STRU           *pstReo,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstReo)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeReo: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_REO;
    pucUdh[ucLen++] = MN_MSG_UDH_REO_IEL;
    pucUdh[ucLen++] = pstReo->ucRefNum;
    pucUdh[ucLen++] = (VOS_UINT8)(pstReo->usPos >> 8);
    pucUdh[ucLen++] = (VOS_UINT8)(pstReo->usPos & 0xff);
    /*lint +e961*/

    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeCc
 功能描述  : 编码压缩控制IE
 输入参数  : pstCc  - 压缩控制IE数据结构
 输出参数  : pucUdh - TPDU格式的压缩控制IE
 返 回 值  : TPDU格式的压缩控制IE占用的字节数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月11日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeCc(
    const MN_MSG_UDH_CC_STRU            *pstCc,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstCc)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeCc: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_CC;
    pucUdh[ucLen++] = MN_MSG_UDH_CC_HEADER_LEN + (VOS_UINT8)pstCc->usDataLen;
    pucUdh[ucLen++] = pstCc->enCompressionAlgorithm & 0x0f;
    pucUdh[ucLen++] = (VOS_UINT8)(pstCc->usTotalLen >> 8);
    pucUdh[ucLen++] = (VOS_UINT8)(pstCc->usTotalLen & 0xff);
    /*lint +e961*/
    PS_MEM_CPY(&pucUdh[ucLen], pstCc->aucData, pstCc->usDataLen);
    ucLen += (VOS_UINT8)pstCc->usDataLen;
    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeObjDistrInd
 功能描述  : 编码对象分发指示IE
 输入参数  : pstObjDistr    - 对象分发指示IE数据结构
 输出参数  : pucUdh - TPDU格式的对象分发指示IE数据结构
 返 回 值  : TPDU格式的对象分发指示IE数据结构占用的字节数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月11日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeObjDistrInd(
    const MN_MSG_UDH_OBJ_DISTR_STRU     *pstObjDistr,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstObjDistr)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeObjDistrInd: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_OBJ_DISTR_IND;
    pucUdh[ucLen++] = MN_MSG_UDH_OBJ_DISTR_IND_IEL;
    pucUdh[ucLen++] = pstObjDistr->ucIeNum;
    /*lint +e961*/
    MSG_SetObjForwardedFlag(pucUdh[ucLen], pstObjDistr->bObjNotFowarded);
    ucLen++;
    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeHyperLinkFormat
 功能描述  : 编码超级链接格式IE
 输入参数  : pstHyperLinkFormat - 超级链接格式IE数据结构
 输出参数  : pucUdh - TPDU格式的超级链接格式IE
 返 回 值  : TPDU格式的超级链接格式IE占用的字节数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月11日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeHyperLinkFormat(
    const MN_MSG_HYPERLINK_FORMAT_STRU  *pstHyperLinkFormat,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstHyperLinkFormat)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeHyperLinkFormat: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_HYPERLINK_FORMAT;
    pucUdh[ucLen++] = MN_MSG_UDH_HYPERLINK_FORMAT_IEL;
    pucUdh[ucLen++] = (VOS_UINT8)(pstHyperLinkFormat->usPos >> 8);
    pucUdh[ucLen++] = (VOS_UINT8)(pstHyperLinkFormat->usPos & 0xff);
    pucUdh[ucLen++] = pstHyperLinkFormat->ucHyperLinkTitleLen;
    pucUdh[ucLen++] = pstHyperLinkFormat->ucUrlLen;
    /*lint +e961*/

    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeReplyAddr
 功能描述  : 编码回复地址IE
 输入参数  : pstReplyAddr   - 回复地址IE数据结构
 输出参数  : pucUdh - TPDU格式的回复地址IE
 返 回 值  : TPDU格式的回复地址IE占用的字节数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月11日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeReplyAddr(
    const MN_MSG_UDH_REPLY_ADDR_STRU    *pstReplyAddr,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulAddrLen;

    if ((VOS_NULL_PTR == pstReplyAddr)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeReplyAddr: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    pucUdh[ucLen++] = MN_MSG_UDH_REPLY_ADDR;
    ulRet = MN_MSG_EncodeAddress(&pstReplyAddr->stReplyAddr, VOS_FALSE, &pucUdh[ucLen + 1], &ulAddrLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_EncodeReplyAddr: fail to encode address.");
        return 0;
    }
    pucUdh[ucLen++] = (VOS_UINT8)ulAddrLen;
    ucLen += (VOS_UINT8)ulAddrLen;
    /*lint +e961*/

    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeWvgObj
 功能描述  : 编码无线矢量图形IE
 输入参数  : enHeaderId - 无线矢量图形IE名称，只能是标准无线矢量图形IE或字符尺寸的无线矢量图形IE
             pstWvgObj  - 无线矢量图形IE数据结构
 输出参数  : pucUdh - TPDU格式的无线矢量图形IE
 返 回 值  : TPDU格式的无线矢量图形IE占用的字节数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月11日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeWvgObj(
    MN_MSG_UDH_TYPE_ENUM_U8             enHeaderId,
    const MN_MSG_UDH_WVG_OBJ_STRU       *pstWvgObj,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstWvgObj)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeWvgObj: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_UDH_STD_WVG_OBJ != enHeaderId)
     && (MN_MSG_UDH_CHAR_SIZE_WVG_OBJ != enHeaderId))
    {
        MN_WARN_LOG("MSG_EncodeWvgObj: invalid IEI. ");
        return 0;
    }
    /*lint -e961*/
    pucUdh[ucLen++] = enHeaderId;
    pucUdh[ucLen++] = pstWvgObj->ucLen + MN_MSG_UDH_WVG_HEADER_LEN;
    pucUdh[ucLen++] = pstWvgObj->ucPos;
    /*lint +e961*/

    PS_MEM_CPY(&pucUdh[ucLen], pstWvgObj->aucData, pstWvgObj->ucLen);
    ucLen += pstWvgObj->ucLen;
    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeUdhOther
 功能描述  : 编码用户自定义的消息头部
 输入参数  : pstOther   - 用户自定义消息头部参数
 输出参数  : pucUdh     - TPDU格式的消息头部
 返 回 值  : TPDU格式的用户自定义消息头部长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT8 MSG_EncodeUdhOther(
    MN_MSG_UDH_TYPE_ENUM_U8             enUdhType,
    const MN_MSG_UDH_OTHER_STRU         *pstOther,
    VOS_UINT8                           *pucUdh
)
{
    VOS_UINT8                           ucLen               = 0;

    if ((VOS_NULL_PTR == pstOther)
     || (VOS_NULL_PTR == pucUdh))
    {
        MN_ERR_LOG("MSG_EncodeUdhOther: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    if (pstOther->ucLen > MN_MSG_UDH_OTHER_SIZE)
    {
        MN_WARN_LOG("MSG_EncodeUdhOther: the length of IEI is invalid.");
        return 0;
    }
    /*lint -e961*/
    pucUdh[ucLen++] = enUdhType;
    pucUdh[ucLen++] = pstOther->ucLen;
    PS_MEM_CPY(&pucUdh[ucLen], pstOther->aucData, pstOther->ucLen);
    ucLen += pstOther->ucLen;
    /*lint +e961*/

    return ucLen;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeUdh
 功能描述  : 编码用户消息头部,输出UDHL和UDH
 输入参数  : ucNumofHeaders     - 消息头部参数数组有效元素个数
             pstUserDataHeader  - 消息头部参数数组
 输出参数  : pucUdh             - TPDU格式的消息头部
             pucUdhl            - TPDU格式的消息头部长度
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月12日
    作    者   : fuyingjun
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT32  MSG_EncodeUdh(
    VOS_UINT8                           ucNumofHeaders,
    const MN_MSG_USER_HEADER_TYPE_STRU  *pstUserDataHeader,
    VOS_UINT8                           *pucUdh,
    VOS_UINT8                           *pucUdhl
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucIeiLen;
    VOS_UINT8                           ucPos = 1;

    if ((VOS_NULL_PTR == pstUserDataHeader)
     || (VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pucUdhl))
    {
        MN_ERR_LOG("MSG_EncodeUdh: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    for (ucLoop = 0; ucLoop < ucNumofHeaders; ucLoop++)
    {
        switch (pstUserDataHeader->enHeaderID)
        {
            case MN_MSG_UDH_CONCAT_8:
                ucIeiLen = MSG_EncodeUdhConcat8((MN_MSG_UDH_CONCAT_8_STRU *)&(pstUserDataHeader->u.stConcat_8),
                                                &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_SPECIAL_SM:
                ucIeiLen = MSG_EncodeUdhSpecialSm((MN_MSG_UDH_SPECIAL_SMS_STRU *)&(pstUserDataHeader->u.stSpecial_Sms),
                                                  &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_PORT_8:
                ucIeiLen = MSG_EncodeUdhAppPort_8((MN_MSG_UDH_APPPORT_8_STRU *)&(pstUserDataHeader->u.stAppPort_8),
                                                  &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_PORT_16:
                ucIeiLen = MSG_EncodeUdhAppPort_16((MN_MSG_UDH_APPPORT_16_STRU *)&(pstUserDataHeader->u.stAppPort_16),
                                                   &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_SMSC_CTRL:
                ucIeiLen = MSG_EncodeUdhSmscCtrl((MN_MSG_UDH_SMSC_CTRL_STRU *)&(pstUserDataHeader->u.stSmscCtrl),
                                                 &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_SOURCE:
                ucIeiLen = MSG_EncodeUdhSourceInd((MN_MSG_UDH_SOURCE_IND_STRU *)&(pstUserDataHeader->u.stSrcInd),
                                                  &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_CONCAT_16:
                ucIeiLen = MSG_EncodeUdhConcat16((MN_MSG_UDH_CONCAT_16_STRU *)&(pstUserDataHeader->u.stAppPort_16),
                                                 &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_TEXT_FORMATING:
                ucIeiLen = MSG_EncodeUdhTextFormat((MN_MSG_UDH_TEXT_FORMAT_STRU *)&(pstUserDataHeader->u.stText_Format),
                                                   &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_PRE_DEF_SOUND:
                ucIeiLen = MSG_EncodeUdhPreDefSound((MN_MSG_UDH_PRE_DEF_SOUND_STRU *)&(pstUserDataHeader->u.stPreDef_Sound),
                                                    &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_USER_DEF_SOUND:
                ucIeiLen = MSG_EncodeUdhUserDefSound((MN_MSG_UDH_USER_DEF_SOUND_STRU *)&(pstUserDataHeader->u.stUserDef_Sound),
                                                     &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_PRE_DEF_ANIM:
                ucIeiLen = MSG_EncodeUdhPreDefAnim((MN_MSG_UDH_PRE_DEF_ANIM_STRU *)&(pstUserDataHeader->u.stPreDef_Anim),
                                                   &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_LARGE_ANIM:
                ucIeiLen = MSG_EncodeUdhLargeAnim((MN_MSG_UDH_LARGE_ANIM_STRU *)&(pstUserDataHeader->u.stLarge_Anim),
                                                  &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_SMALL_ANIM:
                ucIeiLen = MSG_EncodeUdhSmallAnim((MN_MSG_UDH_SMALL_ANIM_STRU *)&(pstUserDataHeader->u.stSmall_Anim),
                                                  &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_LARGE_PIC:
                ucIeiLen = MSG_EncodeUdhLargePic((MN_MSG_UDH_LARGE_PIC_STRU *)&(pstUserDataHeader->u.stLarge_Pic),
                                                 &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_SMALL_PIC:
                ucIeiLen = MSG_EncodeUdhSmallPic((MN_MSG_UDH_SMALL_PIC_STRU *)&(pstUserDataHeader->u.stSmall_Pic),
                                                 &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_VAR_PIC:
                ucIeiLen = MSG_EncodeUdhVarPic((MN_MSG_UDH_VAR_PIC_STRU *)&(pstUserDataHeader->u.stVar_Pic),
                                               &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_USER_PROMPT:
                ucIeiLen = MN_MSG_EncodeUdhUserPrompt((MN_MSG_UDH_USER_PROMPT_STRU *)&(pstUserDataHeader->u.stUser_Prompt),
                                                      &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_EO:
                ucIeiLen = MSG_EncodeEo((MN_MSG_UDH_EO_STRU *)&(pstUserDataHeader->u.stEo),
                                        &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_REO:
                ucIeiLen = MSG_EncodeReo((MN_MSG_UDH_REO_STRU *)&(pstUserDataHeader->u.stReo),
                                         &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_CC:
                ucIeiLen = MSG_EncodeCc((MN_MSG_UDH_CC_STRU *)&(pstUserDataHeader->u.stCc),
                                        &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_OBJ_DISTR_IND:
                ucIeiLen = MSG_EncodeObjDistrInd((MN_MSG_UDH_OBJ_DISTR_STRU *)&(pstUserDataHeader->u.stObjDistr),
                                                 &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_STD_WVG_OBJ:
            case MN_MSG_UDH_CHAR_SIZE_WVG_OBJ:
                ucIeiLen = MSG_EncodeWvgObj(pstUserDataHeader->enHeaderID,
                                            (MN_MSG_UDH_WVG_OBJ_STRU *)&pstUserDataHeader->u.stWvgObj,
                                            &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_RFC822:
                ucIeiLen = MSG_EncodeUdhRfc822((MN_MSG_UDH_RFC822_STRU *)&(pstUserDataHeader->u.stRfc822),
                                               &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_HYPERLINK_FORMAT:
                ucIeiLen = MSG_EncodeHyperLinkFormat((MN_MSG_HYPERLINK_FORMAT_STRU *)&(pstUserDataHeader->u.stHyperLinkFormat),
                                                     &(pucUdh[ucPos]));
                break;
            case MN_MSG_UDH_REPLY_ADDR:
                ucIeiLen = MSG_EncodeReplyAddr((MN_MSG_UDH_REPLY_ADDR_STRU *)&(pstUserDataHeader->u.stReplyAddr),
                                               &(pucUdh[ucPos]));
                break;
            default:
                ucIeiLen = MSG_EncodeUdhOther(pstUserDataHeader->enHeaderID,
                                              (MN_MSG_UDH_OTHER_STRU *)&(pstUserDataHeader->u.stOther),
                                              &(pucUdh[ucPos]));
                break;
        }

        ucPos += ucIeiLen;
        if (ucPos >= MN_MSG_MAX_8_BIT_LEN)
        {
            return MN_ERR_CLASS_SMS_MSGLEN_OVERFLOW;
        }
        pstUserDataHeader++;
    }

    pucUdh[0]   = (VOS_UINT8)(ucPos - 1);/*UDHL*/
    *pucUdhl    = pucUdh[0];

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MSG_GetUdhl
 功能描述  : 计算UDH长度
 输入参数  : ucNumofHeaders - 短消息中包含消息头部IEI的个数
             pstUserHeader  - 短消息中包含消息头部IEI的数据结构数组首指针
 输出参数  : pulUdhl        - 编码后短消息中包含消息头部的总长度，单位OCTET
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : fuyingjun 62575
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_VOID  MSG_GetUdhl(
    VOS_UINT8                           ucNumofHeaders,
    const MN_MSG_USER_HEADER_TYPE_STRU  *pstUserHeader,
    VOS_UINT32                          *pulUdhl
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT32                          ulUdhl = 0;
    MN_MSG_UDH_OTHER_STRU               *pstOther;
    MN_MSG_UDH_VAR_PIC_STRU             *pstVarPic;
    MN_MSG_UDH_USER_DEF_SOUND_STRU      *pstUserDef_Sound;
    MN_MSG_UDH_EO_STRU                  *pstEo;
    MN_MSG_UDH_CC_STRU                  *pstCc;
    MN_MSG_UDH_REPLY_ADDR_STRU          *pstReplyAddr;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucBcdAddr[MN_MSG_MAX_BCD_NUM_LEN + 2];
    VOS_UINT32                          ulAddrLen;

    if ((VOS_NULL_PTR == pstUserHeader)
     || (VOS_NULL_PTR == pulUdhl))
    {
        MN_ERR_LOG("MSG_GetUdhl: Parameter of the function is null.");
        return;
    }

    for (ucLoop = 0; ucLoop < ucNumofHeaders; ucLoop++)
    {
        switch (pstUserHeader->enHeaderID)
        {
            case MN_MSG_UDH_CONCAT_8:
                ulUdhl += (MN_MSG_UDH_CONCAT_8_IEL + 2);
                break;
            case MN_MSG_UDH_SPECIAL_SM:
                ulUdhl += (MN_MSG_UDH_SPECIAL_SM_IEL + 2);
                break;
            case MN_MSG_UDH_PORT_8:
                ulUdhl += (MN_MSG_UDH_APPPORT_8_IEL + 2);
                break;
            case MN_MSG_UDH_PORT_16:
                ulUdhl += (MN_MSG_UDH_APPPORT_16_IEL + 2);
                break;
            case MN_MSG_UDH_SMSC_CTRL:
                ulUdhl += (MN_MSG_UDH_SMSCCTRL_IEL + 2);
                break;
            case MN_MSG_UDH_SOURCE:
                ulUdhl += (MN_MSG_UDH_SOURCE_IEL + 2);
                break;
            case MN_MSG_UDH_CONCAT_16:
                ulUdhl += (MN_MSG_UDH_CONCAT_16_IEL + 2);
                break;
            case MN_MSG_UDH_TEXT_FORMATING:
                ulUdhl += (MN_MSG_UDH_TEXT_FORMATING_IEL + 2);
                break;
            case MN_MSG_UDH_PRE_DEF_SOUND:
                ulUdhl += (MN_MSG_UDH_PRE_DEF_SOUND_IEL + 2);
                break;
            case MN_MSG_UDH_USER_DEF_SOUND:
                pstUserDef_Sound = (MN_MSG_UDH_USER_DEF_SOUND_STRU *)&pstUserHeader->u.stUserDef_Sound;
                ulUdhl += (VOS_UINT8)(pstUserDef_Sound->ucSizeofSound + 3);
                break;
            case MN_MSG_UDH_PRE_DEF_ANIM:
                ulUdhl += (MN_MSG_UDH_PRE_DEF_ANIM_IEL + 2);
                break;
            case MN_MSG_UDH_LARGE_ANIM:
                ulUdhl += (MN_MSG_UDH_LARGE_ANIM_IEL + 2);
                break;
            case MN_MSG_UDH_SMALL_ANIM:
                ulUdhl += (MN_MSG_UDH_SMALL_ANIM_IEL + 2);
                break;
            case MN_MSG_UDH_LARGE_PIC:
                ulUdhl += (MN_MSG_UDH_LARGE_PIC_IEL + 2);
                break;
            case MN_MSG_UDH_SMALL_PIC:
                ulUdhl += (MN_MSG_UDH_SMALL_PIC_IEL + 2);
                break;
            case MN_MSG_UDH_VAR_PIC:
                pstVarPic = (MN_MSG_UDH_VAR_PIC_STRU *)&pstUserHeader->u.stVar_Pic;
                ulUdhl += (VOS_UINT8)((pstVarPic->ucHorDim * pstVarPic->ucVertDim) + 3);
                break;
            case MN_MSG_UDH_USER_PROMPT:
                ulUdhl += (MN_MSG_UDH_USER_PROMPT_IEL + 2);
                break;
            case MN_MSG_UDH_EO:
                pstEo = (MN_MSG_UDH_EO_STRU *)&pstUserHeader->u.stEo;
                if (VOS_TRUE == pstEo->bFirstSegment)
                {
                    ulUdhl += MN_MSG_UDH_EO_HEADER_LEN;
                }
                ulUdhl += (pstEo->usDataLen + 2);
                break;
            case MN_MSG_UDH_REO:
                ulUdhl += (MN_MSG_UDH_REO_IEL + 2);
                break;
            case MN_MSG_UDH_CC:
                pstCc = (MN_MSG_UDH_CC_STRU *)&pstUserHeader->u.stCc;
                ulUdhl += (MN_MSG_UDH_CC_HEADER_LEN + pstCc->usDataLen + 2);
                break;
            case MN_MSG_UDH_OBJ_DISTR_IND:
                ulUdhl += (MN_MSG_UDH_OBJ_DISTR_IND_IEL + 2);
                break;
            case MN_MSG_UDH_STD_WVG_OBJ:
            case MN_MSG_UDH_CHAR_SIZE_WVG_OBJ:
                ulUdhl += (pstUserHeader->u.stWvgObj.ucLen + 3);
                break;
            case MN_MSG_UDH_RFC822:
                ulUdhl += (MN_MSG_UDH_RFC822_IEL + 2);
                break;
            case MN_MSG_UDH_HYPERLINK_FORMAT:
                ulUdhl += (MN_MSG_UDH_HYPERLINK_FORMAT_IEL + 2);
                break;
            case MN_MSG_UDH_REPLY_ADDR:
                pstReplyAddr = (MN_MSG_UDH_REPLY_ADDR_STRU *)&pstUserHeader->u.stReplyAddr;
                ulRet = MN_MSG_EncodeAddress(&pstReplyAddr->stReplyAddr, VOS_FALSE, aucBcdAddr, &ulAddrLen);
                if (MN_ERR_NO_ERROR != ulRet)
                {
                    MN_WARN_LOG("MSG_GetUdhl: fail to encode address.");
                    return;
                }
                break;
            default:
                pstOther  = (MN_MSG_UDH_OTHER_STRU *)&(pstUserHeader->u.stOther);
                ulUdhl += (pstOther->ucLen + 2);
                break;
        }
        pstUserHeader++;
    }

    *pulUdhl = ulUdhl;
    return;

}

/*****************************************************************************
 函 数 名  : MSG_EncodeUserData
 功能描述  : 编码用户数据部分(包括UDL UDHL UDH FILLBIT SM)；
 输入参数  : enMsgCoding - 填充位和短消息内容的编码类型
             pstUserData - 用户数据结构
 输出参数  : pucUserData - TPDU格式的用户数据
             pucLen      - TPDU格式的用户数据占用OCTET长度,包括填充位，包括UDL位
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月16日
    作    者   : fuyingjun 62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MSG_EncodeUserData(
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding,
    MN_MSG_USER_DATA_STRU               *pstUserData,
    VOS_UINT8                           *pucUserData,
    VOS_UINT32                          *pucLen
)
{
    VOS_UINT32                          ulPos               = 1;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucUdhl;
    VOS_UINT8                           ucFillBit           = 0;
    VOS_UINT32                          ulLen;

    if ((VOS_NULL_PTR == pstUserData)
     || (VOS_NULL_PTR == pucUserData)
     || (VOS_NULL_PTR == pucLen))
    {
        MN_ERR_LOG("MSG_EncodeUserData: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    /*TP UDL UD */
    if (MN_MSG_MSG_CODING_7_BIT == enMsgCoding)
    {
        if (0 != pstUserData->ucNumofHeaders)
        {
            /*填充UDHL和UDH数据区并输出UDHL数值*/
            ulRet = MSG_EncodeUdh(pstUserData->ucNumofHeaders,
                                  pstUserData->astUserDataHeader,
                                  &(pucUserData[ulPos]),
                                  &ucUdhl);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                return ulRet;
            }
            ucFillBit      = (7 - (((ucUdhl + 1) * 8) % 7)) % 7;

            /*pucUserData[0]存储UDL*/
            pucUserData[0] = (VOS_UINT8)(pstUserData->ulLen + ((((ucUdhl + 1) * 8) + ucFillBit)/7));

            /*将数据区数组下标移至UDHL UDH之后 */
            ulPos         += (ucUdhl + 1);
        }
        else
        {
            pucUserData[0] = (VOS_UINT8)pstUserData->ulLen;
            if (0 == pstUserData->ulLen)
            {
                *pucLen = 1;
                return MN_ERR_NO_ERROR;
            }
        }

        /*用户数据越界检查*/
        if (pucUserData[0] > MN_MSG_MAX_7_BIT_LEN)
        {
            MN_WARN_LOG("MSG_EncodeUserData: The length of 7 bit encoded user data is overflow.");
            return MN_ERR_CLASS_SMS_MSGLEN_OVERFLOW;
        }

        /*字符转换为GSM 7 bit default alphabet，填充UD中的FillBit SM数据区，并输出FillBit SM占用的字节数*/
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
        ulRet   = TAF_STD_Pack7Bit(pstUserData->aucOrgData,
                                   pstUserData->ulLen,
                                   ucFillBit,
                                   &(pucUserData[ulPos]),
                                   &ulLen);
        if (VOS_OK != ulRet)
        {
            return MN_ERR_CLASS_INVALID_TP_UD;
        }
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

        /*计算UDL UD总共占用的字节数*/
        *pucLen = 1 + (((pucUserData[0] * 7) + 7)/8);
    }
    else
    {
        if (0 != pstUserData->ucNumofHeaders)
        {
            /*填充UDHL和UDH数据区并输出UDHL数值*/
            ulRet = MSG_EncodeUdh(pstUserData->ucNumofHeaders,
                                  pstUserData->astUserDataHeader,
                                  &(pucUserData[ulPos]),
                                  &ucUdhl);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                return ulRet;
            }

            /*pucUserData[0]存储UDL*/
            pucUserData[0] = (VOS_UINT8)((ucUdhl + 1) + pstUserData->ulLen);
            /*将数据区数组下标移至UDHL UDH之后 */
            ulPos         += (ucUdhl + 1);
        }
        else
        {
            /*pucUserData[0]存储UDL*/
            pucUserData[0]     = (VOS_UINT8)pstUserData->ulLen;/*UDL*/
        }

        /*用户数据越界检查*/
        if (pucUserData[0] > MN_MSG_MAX_8_BIT_LEN)
        {
            MN_WARN_LOG("MSG_EncodeUserData: The length of 8 bit encoded user data is overflow.");
            return MN_ERR_CLASS_SMS_MSGLEN_OVERFLOW;
        }
        PS_MEM_CPY(&(pucUserData[ulPos]), pstUserData->aucOrgData, pstUserData->ulLen);

        /*计算UDL UD总共占用的字节数*/
        *pucLen = 1 + pucUserData[0];
    }

    return MN_ERR_NO_ERROR;

}

/*****************************************************************************
 函 数 名  : MSG_EncodeDeliver
 功能描述  : 同步函数,将具体的Deliver短信数据编码为TPDU格式,
             参考协议23040 9.2.2.1
 输入参数  : pstSmsDeliverInfo  - Deliver短信的TEXT格式
 输出参数  : pstSmsRawDataInfo  - 短信的TPDU格式
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32   MSG_EncodeDeliver(
    const MN_MSG_DELIVER_STRU           *pstSmsDeliverInfo,
    MN_MSG_RAW_TS_DATA_STRU             *pstSmsRawDataInfo
)
{
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT32                          ulAddrLen;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSctsLen;
    VOS_UINT32                          ulLen;
    MN_MSG_ASCII_ADDR_STRU              *pstAddr;
    MN_MSG_USER_DATA_STRU               *pstUserData;

    if ((VOS_NULL_PTR == pstSmsRawDataInfo)
     || (VOS_NULL_PTR == pstSmsDeliverInfo))
    {
        MN_ERR_LOG("MSG_EncodeDeliver: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    PS_MEM_SET(pstSmsRawDataInfo, 0x00, sizeof(MN_MSG_RAW_TS_DATA_STRU));
    pstSmsRawDataInfo->enTpduType = MN_MSG_TPDU_DELIVER;

    /* TP-MTI, TP-MMS, TP-RP, TP_UDHI, TP-SRI:*/
    MSG_SET_TP_MTI(pstSmsRawDataInfo->aucData[ulPos], MN_MSG_TP_MTI_DELIVER);
    MSG_SET_TP_MMS(pstSmsRawDataInfo->aucData[ulPos], pstSmsDeliverInfo->bMoreMsg);
    MSG_SET_TP_RP(pstSmsRawDataInfo->aucData[ulPos], pstSmsDeliverInfo->bReplayPath);
    MSG_SET_TP_UDHI(pstSmsRawDataInfo->aucData[ulPos], pstSmsDeliverInfo->bUserDataHeaderInd);
    MSG_SET_TP_SRI(pstSmsRawDataInfo->aucData[ulPos], pstSmsDeliverInfo->bStaRptInd);
    ulPos ++;

    /* TP-OA:2 - 12o*/
    pstAddr = (MN_MSG_ASCII_ADDR_STRU *)&pstSmsDeliverInfo->stOrigAddr;
    ulRet   = MN_MSG_EncodeAddress(pstAddr,
                                VOS_FALSE,
                                &(pstSmsRawDataInfo->aucData[ulPos]),
                                &ulAddrLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulAddrLen;

    /* TP-PID*/
    /*lint -e961*/
    pstSmsRawDataInfo->aucData[ulPos++] = pstSmsDeliverInfo->enPid;
    /*lint +e961*/

    /* TP-DCS */
    ulRet = MN_MSG_EncodeDcs(&(pstSmsDeliverInfo->stDcs),
                             &(pstSmsRawDataInfo->aucData[ulPos]));
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos++;

    /* TP-SCTS:7o*/
    ulRet = MSG_EncodeTimeStamp((MN_MSG_TIMESTAMP_STRU *)&(pstSmsDeliverInfo->stTimeStamp),
                                &(pstSmsRawDataInfo->aucData[ulPos]),
                                &ulSctsLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulSctsLen;

    /* TP-UDL TP-UD, Refer to 23040 9.2.3.24 TP User Data (TP UD) */
    pstUserData = (MN_MSG_USER_DATA_STRU *)&(pstSmsDeliverInfo->stUserData);
    ulRet = MSG_EncodeUserData(pstSmsDeliverInfo->stDcs.enMsgCoding,
                               pstUserData,
                               &(pstSmsRawDataInfo->aucData[ulPos]),
                               &ulLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }

    pstSmsRawDataInfo->ulLen = ulPos + ulLen;
    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeDeliverRptAck
 功能描述  : 同步函数,将具体的Deliver Report Ack短信数据编码为TPDU格式,
             参考协议 23040 9.2.2.1a
 输入参数  : pstSmsDeliverReportAckInfo  - Deliver Report Ack短信的TEXT格式
 输出参数  : pstSmsRawDataInfo           - 短信的TPDU格式
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32   MSG_EncodeDeliverRptAck(
    const MN_MSG_DELIVER_RPT_ACK_STRU   *pstSmsDeliverReportAckInfo,
    MN_MSG_RAW_TS_DATA_STRU             *pstSmsRawDataInfo
)
{
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT32                          ulRet               = MN_ERR_NO_ERROR;
    VOS_UINT32                          ulLen;
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding         = MN_MSG_MSG_CODING_7_BIT;
    MN_MSG_USER_DATA_STRU               *pstUserData;

    if ((VOS_NULL_PTR == pstSmsRawDataInfo)
     || (VOS_NULL_PTR == pstSmsDeliverReportAckInfo))
    {
        MN_ERR_LOG("MSG_EncodeDeliverRptAck: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    PS_MEM_SET(pstSmsRawDataInfo, 0x00, sizeof(MN_MSG_RAW_TS_DATA_STRU));
    pstSmsRawDataInfo->enTpduType = MN_MSG_TPDU_DELIVER_RPT_ACK;

    /*TP MTI  TP-UDHI  */
    MSG_SET_TP_MTI(pstSmsRawDataInfo->aucData[ulPos], MN_MSG_TP_MTI_DELIVER_REPORT);
    MSG_SET_TP_UDHI(pstSmsRawDataInfo->aucData[ulPos], pstSmsDeliverReportAckInfo->bUserDataHeaderInd);
    ulPos++;

    /*    TP PI  9.2.3.27 BIT   2       1       0
                                TP UDL  TP DCS  TP PID        */
    /*lint -e961*/
    pstSmsRawDataInfo->aucData[ulPos++] = pstSmsDeliverReportAckInfo->ucParaInd;
    /*lint +e961*/

    /*TP PID*/
    if (0 != (pstSmsDeliverReportAckInfo->ucParaInd & MN_MSG_TP_PID_MASK))
    {
        /*lint -e961*/
        pstSmsRawDataInfo->aucData[ulPos++] = pstSmsDeliverReportAckInfo->enPid;
        /*lint +e961*/
    }

    /*TP DCS*/
    if (0 != (pstSmsDeliverReportAckInfo->ucParaInd & MN_MSG_TP_DCS_MASK))
    {
        ulRet = MN_MSG_EncodeDcs(&(pstSmsDeliverReportAckInfo->stDcs),
                                 &(pstSmsRawDataInfo->aucData[ulPos]));
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        enMsgCoding = pstSmsDeliverReportAckInfo->stDcs.enMsgCoding;
        ulPos++;
    }

    /*TP UD TP UDL;*/
    pstSmsRawDataInfo->ulLen = ulPos;
    if (0 != (pstSmsDeliverReportAckInfo->ucParaInd & MN_MSG_TP_UDL_MASK))
    {
        pstUserData = (MN_MSG_USER_DATA_STRU *)&(pstSmsDeliverReportAckInfo->stUserData);
        ulRet = MSG_EncodeUserData(enMsgCoding,
                                   pstUserData,
                                   &(pstSmsRawDataInfo->aucData[ulPos]),
                                   &ulLen);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        pstSmsRawDataInfo->ulLen += ulLen;
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeDeliverRptErr
 功能描述  : 同步函数,将具体的Deliver Report Error短信数据编码为TPDU格式,
             参考协议23040 9.2.2.1a
 输入参数  : pstSmsDeliverReportErrorInfo  - Deliver Report Error短信的TEXT格式
 输出参数  : pstSmsRawDataInfo             - 短信的TPDU格式
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32   MSG_EncodeDeliverRptErr(
    const MN_MSG_DELIVER_RPT_ERR_STRU   *pstSmsDeliverReportErrorInfo,
    MN_MSG_RAW_TS_DATA_STRU             *pstSmsRawDataInfo
)
{
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT32                          ulRet               = MN_ERR_NO_ERROR;
    VOS_UINT32                          ulLen;
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding         = MN_MSG_MSG_CODING_7_BIT;
    MN_MSG_USER_DATA_STRU               *pstUserData;

    if ((VOS_NULL_PTR == pstSmsRawDataInfo)
     || (VOS_NULL_PTR == pstSmsDeliverReportErrorInfo))
    {
        MN_ERR_LOG("MSG_EncodeDeliverRptErr: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    PS_MEM_SET(pstSmsRawDataInfo, 0x00, sizeof(MN_MSG_RAW_TS_DATA_STRU));
    pstSmsRawDataInfo->enTpduType = MN_MSG_TPDU_DELIVER_RPT_ERR;

    /*TP MTI  TP-UDHI  */
    MSG_SET_TP_MTI(pstSmsRawDataInfo->aucData[ulPos], MN_MSG_TP_MTI_DELIVER_REPORT);
    MSG_SET_TP_UDHI(pstSmsRawDataInfo->aucData[ulPos], pstSmsDeliverReportErrorInfo->bUserDataHeaderInd);
    ulPos++;

    /*TP FCS*/
    /*lint -e961*/
    pstSmsRawDataInfo->aucData[ulPos++] = pstSmsDeliverReportErrorInfo->enFailCause;
    /*    TP PI  9.2.3.27 BIT   2       1       0
                                TP UDL  TP DCS  TP PID        */
    pstSmsRawDataInfo->aucData[ulPos++] = pstSmsDeliverReportErrorInfo->ucParaInd;
    /*lint +e961*/

    /*TP PID*/
    if (0 != (pstSmsDeliverReportErrorInfo->ucParaInd & MN_MSG_TP_PID_MASK))
    {
        /*lint -e961*/
        pstSmsRawDataInfo->aucData[ulPos++] = pstSmsDeliverReportErrorInfo->enPid;
        /*lint +e961*/
    }

    /*  TP DCS*/
    if (0 != (pstSmsDeliverReportErrorInfo->ucParaInd & MN_MSG_TP_DCS_MASK))
    {
        ulRet = MN_MSG_EncodeDcs(&(pstSmsDeliverReportErrorInfo->stDcs),
                                 &(pstSmsRawDataInfo->aucData[ulPos]));
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        enMsgCoding = pstSmsDeliverReportErrorInfo->stDcs.enMsgCoding;
        ulPos++;
    }

    /*TP UD TP UDL;*/
    pstSmsRawDataInfo->ulLen = ulPos;
    if (0 != (pstSmsDeliverReportErrorInfo->ucParaInd & MN_MSG_TP_UDL_MASK))
    {
        pstUserData = (MN_MSG_USER_DATA_STRU *)&(pstSmsDeliverReportErrorInfo->stUserData);
        ulRet = MSG_EncodeUserData(enMsgCoding,
                                   pstUserData,
                                   &(pstSmsRawDataInfo->aucData[ulPos]),
                                   &ulLen);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        pstSmsRawDataInfo->ulLen += ulLen;
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeStaRpt
 功能描述  : 同步函数,将具体的Status Report短信数据编码为TPDU格式,
             参考协议23040 9.2.2.3
 输入参数  : pstSmsStatusReportInfo  - Status Report短信的TEXT格式
 输出参数  : pstSmsRawDataInfo       - 短信的TPDU格式
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32   MSG_EncodeStaRpt(
    const MN_MSG_STA_RPT_STRU           *pstSmsStatusReportInfo,
    MN_MSG_RAW_TS_DATA_STRU             *pstSmsRawDataInfo
)
{
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulAddrLen;
    VOS_UINT32                          ulSctsLen;
    VOS_UINT32                          ulDtLen;
    VOS_UINT32                          ulLen;
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding         = MN_MSG_MSG_CODING_7_BIT;
    MN_MSG_USER_DATA_STRU               *pstUserData;
    MN_MSG_ASCII_ADDR_STRU              *pstAddr;

    if ((VOS_NULL_PTR == pstSmsRawDataInfo)
     || (VOS_NULL_PTR == pstSmsStatusReportInfo))
    {
        MN_ERR_LOG("MSG_EncodeStaRpt: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    PS_MEM_SET(pstSmsRawDataInfo, 0x00, sizeof(MN_MSG_RAW_TS_DATA_STRU));
    pstSmsRawDataInfo->enTpduType = MN_MSG_TPDU_STARPT;

    /*TP MTI TP UDHI TP MMS TP SRQ*/
    MSG_SET_TP_MTI(pstSmsRawDataInfo->aucData[ulPos], MN_MSG_TP_MTI_STATUS_REPORT);
    MSG_SET_TP_UDHI(pstSmsRawDataInfo->aucData[ulPos], pstSmsStatusReportInfo->bUserDataHeaderInd);
    MSG_SET_TP_MMS(pstSmsRawDataInfo->aucData[ulPos], pstSmsStatusReportInfo->bMoreMsg);
    MSG_SET_TP_SRQ(pstSmsRawDataInfo->aucData[ulPos], pstSmsStatusReportInfo->bStaRptQualCommand);/*??*/
    ulPos++;

    /*TP MR*/
    /*lint -e961*/
    pstSmsRawDataInfo->aucData[ulPos++] = pstSmsStatusReportInfo->ucMr;
    /*lint +e961*/

    /*TP RA 2 12o*/
    pstAddr = (MN_MSG_ASCII_ADDR_STRU *)&pstSmsStatusReportInfo->stRecipientAddr;
    ulRet   = MN_MSG_EncodeAddress(pstAddr,
                                VOS_FALSE,
                                &(pstSmsRawDataInfo->aucData[ulPos]),
                                &ulAddrLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulAddrLen;

    /*TP SCTS 7o Parameter identifying time when the SC received the previously sent SMS SUBMIT*/
    ulRet = MSG_EncodeTimeStamp((MN_MSG_TIMESTAMP_STRU *)&(pstSmsStatusReportInfo->stTimeStamp),
                                &(pstSmsRawDataInfo->aucData[ulPos]),
                                &ulSctsLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulSctsLen;

    /*TP DT Parameter identifying the time associated with a particular TP ST outcome*/
    ulRet = MSG_EncodeTimeStamp((MN_MSG_TIMESTAMP_STRU *)&(pstSmsStatusReportInfo->stDischargeTime),
                                &(pstSmsRawDataInfo->aucData[ulPos]),
                                &ulDtLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulDtLen;

    /*TP ST*/
    /*lint -e961*/
    pstSmsRawDataInfo->aucData[ulPos++] = pstSmsStatusReportInfo->enStatus;
    /*lint +e961*/

    if (0 == pstSmsStatusReportInfo->ucParaInd)
    {
        pstSmsRawDataInfo->ulLen = ulPos;
        return MN_ERR_NO_ERROR;
    }

    /*    TP PI  9.2.3.27 BIT   2       1       0
                                TP UDL  TP DCS  TP PID        */
    /*lint -e961*/
    pstSmsRawDataInfo->aucData[ulPos++] = pstSmsStatusReportInfo->ucParaInd;
    /*lint +e961*/

    /*TP PID*/
    if (0 != (pstSmsStatusReportInfo->ucParaInd & MN_MSG_TP_PID_MASK))
    {
        /*lint -e961*/
        pstSmsRawDataInfo->aucData[ulPos++] = pstSmsStatusReportInfo->enPid;
        /*lint +e961*/
    }

    /*  TP DCS*/
    if (0 != (pstSmsStatusReportInfo->ucParaInd & MN_MSG_TP_DCS_MASK))
    {
        ulRet = MN_MSG_EncodeDcs(&(pstSmsStatusReportInfo->stDcs),
                                 &(pstSmsRawDataInfo->aucData[ulPos]));
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        enMsgCoding = pstSmsStatusReportInfo->stDcs.enMsgCoding;
        ulPos++;
    }

    /*TP UD TP UDL;*/
    if (0 != (pstSmsStatusReportInfo->ucParaInd & MN_MSG_TP_UDL_MASK))
    {
        pstUserData = (MN_MSG_USER_DATA_STRU *)&(pstSmsStatusReportInfo->stUserData);
        ulRet = MSG_EncodeUserData(enMsgCoding,
                                   pstUserData,
                                   &(pstSmsRawDataInfo->aucData[ulPos]),
                                   &ulLen);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        ulPos += ulLen;
    }
    pstSmsRawDataInfo->ulLen = ulPos;

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeCommand
 功能描述  : 同步函数,将具体Command短信数据编码为TPDU格式，
             参考协议23040 9.2.2.4
 输入参数  : pstSmsCommandInfo  - Command短信的TEXT格式
 输出参数  : pstSmsRawDataInfo  - 短信的TPDU格式
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32   MSG_EncodeCommand(
    const MN_MSG_COMMAND_STRU           *pstSmsCommandInfo,
    MN_MSG_RAW_TS_DATA_STRU             *pstSmsRawDataInfo
)
{
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulAddrLen;
    MN_MSG_ASCII_ADDR_STRU              *pstAddr;

    if ((VOS_NULL_PTR == pstSmsRawDataInfo)
     || (VOS_NULL_PTR == pstSmsCommandInfo))
    {
        MN_ERR_LOG("MSG_EncodeCommand: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    PS_MEM_SET(pstSmsRawDataInfo, 0x00, sizeof(MN_MSG_RAW_TS_DATA_STRU));
    pstSmsRawDataInfo->enTpduType = MN_MSG_TPDU_COMMAND;

    /*TP MTI TP UDHI TP SRR */
    MSG_SET_TP_MTI(pstSmsRawDataInfo->aucData[ulPos], MN_MSG_TP_MTI_COMMAND);
    MSG_SET_TP_UDHI(pstSmsRawDataInfo->aucData[ulPos], pstSmsCommandInfo->bUserDataHeaderInd);
    MSG_SET_TP_SRR(pstSmsRawDataInfo->aucData[ulPos], pstSmsCommandInfo->bStaRptReq);
    ulPos++;

    /*TP MR*/
    /*lint -e961*/
    pstSmsRawDataInfo->aucData[ulPos++] = pstSmsCommandInfo->ucMr;

    /*TP PID*/
    pstSmsRawDataInfo->aucData[ulPos++] = pstSmsCommandInfo->enPid;

    /*TP CT*/
    pstSmsRawDataInfo->aucData[ulPos++] = pstSmsCommandInfo->enCmdType;

    /*TP MN*/
    pstSmsRawDataInfo->aucData[ulPos++] = pstSmsCommandInfo->ucMsgNumber;
    /*lint +e961*/

    /*TP DA*/
    pstAddr = (MN_MSG_ASCII_ADDR_STRU *)&pstSmsCommandInfo->stDestAddr;
    ulRet   = MN_MSG_EncodeAddress(pstAddr,
                                VOS_FALSE,
                                &(pstSmsRawDataInfo->aucData[ulPos]),
                                &ulAddrLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulAddrLen;

    /*TP CDL*/
    /*lint -e961*/
    pstSmsRawDataInfo->aucData[ulPos++] = pstSmsCommandInfo->ucCommandDataLen;
    /*lint +e961*/
    pstSmsRawDataInfo->ulLen = ulPos;

    /*TP CD*/
    if (0 == pstSmsCommandInfo->ucCommandDataLen)
    {
        return MN_ERR_NO_ERROR;
    }

    if (pstSmsCommandInfo->ucCommandDataLen > MN_MSG_MAX_COMMAND_DATA_LEN)
    {
        return MN_ERR_CLASS_SMS_MSGLEN_OVERFLOW;
    }
    PS_MEM_CPY(&pstSmsRawDataInfo->aucData[ulPos],
               pstSmsCommandInfo->aucCmdData,
               pstSmsCommandInfo->ucCommandDataLen);
    pstSmsRawDataInfo->ulLen += pstSmsCommandInfo->ucCommandDataLen;

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeSubmit
 功能描述  : 同步函数,将具体Submit短信数据编码为TPDU格式
             参考协议23040 9.2.2.2
 输入参数  : pstSmsSubmitInfo        - Submit短信的TEXT格式
 输出参数  : pstSmsRawDataInfo       - 短信的TPDU格式
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32   MSG_EncodeSubmit(
    const MN_MSG_SUBMIT_STRU            *pstSmsSubmitInfo,
    MN_MSG_RAW_TS_DATA_STRU             *pstSmsRawDataInfo
)
{
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT32                          ulVpLen;
    VOS_UINT32                          ulAddrLen;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLen;
    MN_MSG_USER_DATA_STRU               *pstUserData;
    MN_MSG_ASCII_ADDR_STRU              *pstAddr;

    if ((VOS_NULL_PTR == pstSmsRawDataInfo)
     || (VOS_NULL_PTR == pstSmsSubmitInfo))
    {
        MN_ERR_LOG("MSG_EncodeSubmit: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    PS_MEM_SET(pstSmsRawDataInfo, 0x00, sizeof(MN_MSG_RAW_TS_DATA_STRU));
    pstSmsRawDataInfo->enTpduType = MN_MSG_TPDU_SUBMIT;

    /*b7  b6   b5   b4   b3  b2  b1  b0
      RP  UDHI SRR  VPF      RD  MTI
      0   0    0    2        1   2
      TP MTI TP RD TP VPF TP RP TP UDHI TP SRR*/
    /*TP MTI 23040 9.2.3.1 填写bit0bit1:MIT     0011 0001 */
    /*TP RD  23040 9.2.3.25*/
    /*TP VPF 23040 9.2.3.3*/
    /*TP SRR 23040 9.2.3.5*/
    /*TP UDHI23040 9.2.3.23*/
    /*TP RP  23040 9.2.3.17*/
    MSG_SET_TP_MTI(pstSmsRawDataInfo->aucData[ulPos], MN_MSG_TP_MTI_SUBMIT);
    MSG_SET_TP_RD(pstSmsRawDataInfo->aucData[ulPos], pstSmsSubmitInfo->bRejectDuplicates);
    MSG_SET_TP_VPF(pstSmsRawDataInfo->aucData[ulPos], pstSmsSubmitInfo->stValidPeriod.enValidPeriod);
    MSG_SET_TP_RP(pstSmsRawDataInfo->aucData[ulPos], pstSmsSubmitInfo->bReplayPath);
    MSG_SET_TP_UDHI(pstSmsRawDataInfo->aucData[ulPos], pstSmsSubmitInfo->bUserDataHeaderInd);
    MSG_SET_TP_SRR(pstSmsRawDataInfo->aucData[ulPos], pstSmsSubmitInfo->bStaRptReq);
    ulPos++;

    /*TP MR*/
    /*lint -e961*/
    pstSmsRawDataInfo->aucData[ulPos++] = pstSmsSubmitInfo->ucMr;
    /*lint +e961*/

    /*TP DA* Refer to 9.1.2.5*/
    pstAddr = (MN_MSG_ASCII_ADDR_STRU *)&pstSmsSubmitInfo->stDestAddr;
    ulRet   = MN_MSG_EncodeAddress(pstAddr,
                                VOS_FALSE,
                                &(pstSmsRawDataInfo->aucData[ulPos]),
                                &ulAddrLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulAddrLen;

    /*TP PID*/
    /*lint -e961*/
    pstSmsRawDataInfo->aucData[ulPos++] = pstSmsSubmitInfo->enPid;
    /*lint +e961*/

    /*TP DCS 23038 4 */
    ulRet = MN_MSG_EncodeDcs(&(pstSmsSubmitInfo->stDcs),
                             &(pstSmsRawDataInfo->aucData[ulPos]));
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos++;

    /*TP VP*/
    ulRet = MSG_EncodeValidPeriod(&(pstSmsSubmitInfo->stValidPeriod),
                                  &(pstSmsRawDataInfo->aucData[ulPos]),
                                  &ulVpLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulVpLen;

    /*UDL UD*/
    pstUserData = (MN_MSG_USER_DATA_STRU *)&(pstSmsSubmitInfo->stUserData);
    ulRet = MSG_EncodeUserData(pstSmsSubmitInfo->stDcs.enMsgCoding,
                               pstUserData,
                               &(pstSmsRawDataInfo->aucData[ulPos]),
                               &ulLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }

    pstSmsRawDataInfo->ulLen = ulPos + ulLen;

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeSubmitRptAck
 功能描述  : 同步函数,将具体Submit Report Ack短信数据编码为TPDU格式，
             参考协议23040 9.2.2.2a
 输入参数  : pstSmsSubmitReportAckInfo   - Submit Report Ack短信的TEXT格式
 输出参数  : pstSmsRawDataInfo           - 短信的TPDU格式
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32   MSG_EncodeSubmitRptAck(
    const MN_MSG_SUBMIT_RPT_ACK_STRU    *pstSmsSubmitReportAckInfo,
    MN_MSG_RAW_TS_DATA_STRU             *pstSmsRawDataInfo
)
{
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulSctsLen;
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding         = MN_MSG_MSG_CODING_7_BIT;
    MN_MSG_USER_DATA_STRU               *pstUserData;

    if ((VOS_NULL_PTR == pstSmsRawDataInfo)
     || (VOS_NULL_PTR == pstSmsSubmitReportAckInfo))
    {
        MN_ERR_LOG("MSG_EncodeSubmitRptAck: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    PS_MEM_SET(pstSmsRawDataInfo, 0x00, sizeof(MN_MSG_RAW_TS_DATA_STRU));
    pstSmsRawDataInfo->enTpduType = MN_MSG_TPDU_SUBMIT_RPT_ACK;

    /*TP MTI  TP-UDHI  */
    MSG_SET_TP_MTI(pstSmsRawDataInfo->aucData[ulPos], MN_MSG_TP_MTI_SUBMIT_REPORT);
    MSG_SET_TP_UDHI(pstSmsRawDataInfo->aucData[ulPos], pstSmsSubmitReportAckInfo->bUserDataHeaderInd);
    ulPos++;

    /*lint -e961*/
    /*    TP PI  9.2.3.27 BIT   2       1       0             */
    /*                          TP UDL  TP DCS  TP PID        */
    pstSmsRawDataInfo->aucData[ulPos++] = pstSmsSubmitReportAckInfo->ucParaInd;
    /*lint +e961*/

    /*TP SCTS*/
    ulRet = MSG_EncodeTimeStamp((MN_MSG_TIMESTAMP_STRU *)&(pstSmsSubmitReportAckInfo->stTimeStamp),
                                &(pstSmsRawDataInfo->aucData[ulPos]),
                                &ulSctsLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulSctsLen;

    /*TP PID*/
    if (0 != (pstSmsSubmitReportAckInfo->ucParaInd & MN_MSG_TP_PID_MASK))
    {
        /*lint -e961*/
        pstSmsRawDataInfo->aucData[ulPos++] = pstSmsSubmitReportAckInfo->enPid;
        /*lint +e961*/
    }

    /*  TP DCS*/
    if (0 != (pstSmsSubmitReportAckInfo->ucParaInd & MN_MSG_TP_DCS_MASK))
    {
        ulRet = MN_MSG_EncodeDcs(&(pstSmsSubmitReportAckInfo->stDcs),
                                 &(pstSmsRawDataInfo->aucData[ulPos]));
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        enMsgCoding = pstSmsSubmitReportAckInfo->stDcs.enMsgCoding;
        ulPos++;
    }

    /*TP UD TP UDL;*/
    if (0 != (pstSmsSubmitReportAckInfo->ucParaInd & MN_MSG_TP_UDL_MASK))
    {
        pstUserData = (MN_MSG_USER_DATA_STRU *)&(pstSmsSubmitReportAckInfo->stUserData);
        ulRet = MSG_EncodeUserData(enMsgCoding,
                                   pstUserData,
                                   &(pstSmsRawDataInfo->aucData[ulPos]),
                                   &ulLen);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        ulPos += ulLen;
    }
    pstSmsRawDataInfo->ulLen = ulPos;

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MSG_EncodeSubmitRptErr
 功能描述  : 同步函数,将具体Submit Report Error短信数据编码为TPDU格式
 输入参数  : pstSmsSubmitReportErrorInfo - Submit Report Error短信的TEXT格式
 输出参数  : pstSmsRawDataInfo           - 短信的TPDU格式
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32   MSG_EncodeSubmitRptErr(
    const MN_MSG_SUBMIT_RPT_ERR_STRU    *pstSmsSubmitReportErrorInfo,
    MN_MSG_RAW_TS_DATA_STRU             *pstSmsRawDataInfo
)
{
    /* 根据23040 9.2.2.2a SMS SUBMIT REPORT type对SMS SUBMIT REPORT for RP ERROR的短信进行编码*/
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulSctsLen;
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding         = MN_MSG_MSG_CODING_7_BIT;
    MN_MSG_USER_DATA_STRU               *pstUserData;

    if ((VOS_NULL_PTR == pstSmsRawDataInfo)
     || (VOS_NULL_PTR == pstSmsSubmitReportErrorInfo))
    {
        MN_ERR_LOG("MSG_EncodeSubmitRptErr: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    PS_MEM_SET(pstSmsRawDataInfo, 0x00, sizeof(MN_MSG_RAW_TS_DATA_STRU));
    pstSmsRawDataInfo->enTpduType = MN_MSG_TPDU_SUBMIT_RPT_ERR;

    /*TP MTI  TP-UDHI  */
    MSG_SET_TP_MTI(pstSmsRawDataInfo->aucData[ulPos], MN_MSG_TP_MTI_SUBMIT_REPORT);
    MSG_SET_TP_UDHI(pstSmsRawDataInfo->aucData[ulPos], pstSmsSubmitReportErrorInfo->bUserDataHeaderInd);
    ulPos++;

    /*lint -e961*/

    /*TP FCS*/
    pstSmsRawDataInfo->aucData[ulPos++] = pstSmsSubmitReportErrorInfo->enFailCause;

    /*    TP PI  9.2.3.27 BIT   2       1       0             */
    /*                          TP UDL  TP DCS  TP PID        */
    pstSmsRawDataInfo->aucData[ulPos++] = pstSmsSubmitReportErrorInfo->ucParaInd;
    /*lint +e961*/

    /*TP SCTS*/
    ulRet = MSG_EncodeTimeStamp((MN_MSG_TIMESTAMP_STRU *)&(pstSmsSubmitReportErrorInfo->stTimeStamp),
                                &(pstSmsRawDataInfo->aucData[ulPos]),
                                &ulSctsLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulSctsLen;

    /*TP PID*/
    if (0 != (pstSmsSubmitReportErrorInfo->ucParaInd & MN_MSG_TP_PID_MASK))
    {
        /*lint -e961*/
        pstSmsRawDataInfo->aucData[ulPos++] = pstSmsSubmitReportErrorInfo->enPid;
        /*lint +e961*/
    }

    /*  TP DCS*/
    if (0 != (pstSmsSubmitReportErrorInfo->ucParaInd & MN_MSG_TP_DCS_MASK))
    {
        ulRet = MN_MSG_EncodeDcs(&(pstSmsSubmitReportErrorInfo->stDcs),
                                 &(pstSmsRawDataInfo->aucData[ulPos]));
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        enMsgCoding = pstSmsSubmitReportErrorInfo->stDcs.enMsgCoding;
        ulPos++;
    }

    /*TP UD TP UDL;*/
    if (0 != (pstSmsSubmitReportErrorInfo->ucParaInd & MN_MSG_TP_UDL_MASK))
    {
        pstUserData = (MN_MSG_USER_DATA_STRU *)&(pstSmsSubmitReportErrorInfo->stUserData);
        ulRet = MSG_EncodeUserData(enMsgCoding,
                                   pstUserData,
                                   &(pstSmsRawDataInfo->aucData[ulPos]),
                                   &ulLen);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        ulPos += ulLen;
    }
    pstSmsRawDataInfo->ulLen = ulPos;

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MN_MSG_EncodeDcs
 功能描述  : 同步函数,将23038协议规定的数据编码为Dcs原始数据
 输入参数  : pstDcs                - 指向23038协议规定的数据
 输出参数  : pucDcsData            - DCS的原始数据
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月8日
    作    者   : z40661
    修改内容   : 新生成函数
 2.日    期   : 2009-10-28
    作    者   : F62575
    修改内容   : 问题单号AT2D15641:DCS数据解码后再编码数据被修改；
*****************************************************************************/
VOS_UINT32  MN_MSG_EncodeDcs(
    const MN_MSG_DCS_CODE_STRU          *pstDcs,
    VOS_UINT8                           *pucDcsData
)
{
    VOS_UINT8                           ucDcs = 0;

    if ((VOS_NULL_PTR == pstDcs)
     || (VOS_NULL_PTR == pucDcsData))
    {
        MN_ERR_LOG("MN_MSG_EncodeDcs: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    if (VOS_TRUE == pstDcs->bRawDcsValid)
    {
        *pucDcsData = pstDcs->ucRawDcsData;
        return MN_ERR_NO_ERROR;
    }

    switch (pstDcs->enMsgWaiting)
    {
        case MN_MSG_MSG_WAITING_AUTO_DELETE:
            /*bit7 bit6*/
            ucDcs = 0x40;
            /* fall through */
        case MN_MSG_MSG_WAITING_NONE:/*00xx 01xx*/
            /* Bit 5  if set to 0, indicates the text is uncompressed */
            MSG_SET_COMPRESSED(ucDcs, pstDcs->bCompressed);
            /* Bit 3 Bit2 Character set:*/
            MSG_SET_CHARSET(ucDcs, pstDcs->enMsgCoding);
            /* Bit 1 Bit 0 Message Class 数据损失引入点*/
            if (MN_MSG_MSG_CLASS_NONE != pstDcs->enMsgClass)
            {
                /* Bit 4, if set to 0, indicates that bits 1 to 0 are reserved and have no message class*/
                MSG_SET_CLASSFLAG(ucDcs, pstDcs->enMsgClass);
                MSG_SET_MSGCLASS(ucDcs, pstDcs->enMsgClass);
            }
            break;
        case MN_MSG_MSG_WAITING_DISCARD:/*1100*/
            /*bit7 bit6 bit5 bit4*/
            ucDcs = 0xc0;

            /*Bits 3 indicates Indication Sense*/
            MSG_SET_INDSENSE(ucDcs, pstDcs->bWaitingIndiActive);
            /*Bits 2 默认为0,数据损失引入点*/
            /*Bit 1 Bit 0 Indication Type*/
            MSG_SET_INDTYPE(ucDcs, pstDcs->enMsgWaitingKind);
            break;
        case MN_MSG_MSG_WAITING_STORE:/*1101 1110 */
            /*bit7 bit6 bit5 bit4*/
            if (MN_MSG_MSG_CODING_UCS2 == pstDcs->enMsgCoding)
            {
                ucDcs = 0xe0;/*1110*/
            }
            else
            {
                ucDcs = 0xd0;/*1101*/
            }

            /*Bits 3 indicates Indication Sense*/
            MSG_SET_INDSENSE(ucDcs, pstDcs->bWaitingIndiActive);
            /*Bits 2 默认为0,数据损失引入点*/
            /*Bit 1 Bit 0 Indication Type*/
            MSG_SET_INDTYPE(ucDcs, pstDcs->enMsgWaitingKind);
            break;
        case MN_MSG_MSG_WAITING_NONE_1111:/*1111 */
            /*bit7 bit6 bit5 bit4*/
            ucDcs = 0xf0;
            /*Bits 3 默认为0，数据损失引入点*/
            /*Bits 2 message coding , only be 7bit or 8bit*/
            if (MN_MSG_MSG_CODING_UCS2 == pstDcs->enMsgCoding)
            {
                MN_WARN_LOG("MN_MSG_EncodeDcs: invalid message waiting type.");
                return MN_ERR_CLASS_SMS_INVALID_CODING_GRP;
            }
            MSG_SET_MSGCODING(ucDcs, pstDcs->enMsgCoding);

            /* Bit 1 Bit 0 Message Class */
            MSG_SET_MSGCLASS(ucDcs, pstDcs->enMsgClass);
            break;
        default:
            MN_WARN_LOG("MN_MSG_EncodeDcs: invalid message waiting type.");
            return MN_ERR_CLASS_SMS_INVALID_CODING_GRP;
    }

    *pucDcsData = ucDcs;

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MN_MSG_Encode
 功能描述  : 同步函数,将具体短信数据编码为TPDU格式
 输入参数  : pstTsDataInfo   - 短信的TEXT格式
 输出参数  : pstRawData      - 短信的TPDU格式
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
 2.日    期   : 2009年10月28日
    作    者   : f62575
    修改内容   : AT2D15641, STK短信发送需要支持长短信的分段发送功能
*****************************************************************************/

VOS_UINT32  MN_MSG_Encode(
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsDataInfo,
    MN_MSG_RAW_TS_DATA_STRU             *pstRawData
)
{
    VOS_UINT32                          ulRet;

    MN_INFO_LOG("MN_MSG_Encode: Step into MN_MSG_Encode.");

    if ((VOS_NULL_PTR == pstTsDataInfo)
     || (VOS_NULL_PTR == pstRawData))
    {
        MN_ERR_LOG("MN_MSG_Encode: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    else
    {
        PS_MEM_SET(pstRawData, 0x00, sizeof(MN_MSG_RAW_TS_DATA_STRU));
    }

    switch (pstTsDataInfo->enTpduType)
    {
        case MN_MSG_TPDU_DELIVER:
            ulRet = MSG_EncodeDeliver((MN_MSG_DELIVER_STRU *)&(pstTsDataInfo->u.stDeliver),
                                      pstRawData);
            break;
        case MN_MSG_TPDU_DELIVER_RPT_ACK:
            ulRet = MSG_EncodeDeliverRptAck((MN_MSG_DELIVER_RPT_ACK_STRU *)&(pstTsDataInfo->u.stDeliverRptAck),
                                            pstRawData);
            break;
        case MN_MSG_TPDU_DELIVER_RPT_ERR:
            ulRet = MSG_EncodeDeliverRptErr((MN_MSG_DELIVER_RPT_ERR_STRU *)&(pstTsDataInfo->u.stDeliverRptErr),
                                            pstRawData);
            break;
        case MN_MSG_TPDU_STARPT:
            ulRet = MSG_EncodeStaRpt((MN_MSG_STA_RPT_STRU *)&(pstTsDataInfo->u.stStaRpt),
                                        pstRawData);
            break;
        case MN_MSG_TPDU_COMMAND:
            ulRet = MSG_EncodeCommand((MN_MSG_COMMAND_STRU *)&(pstTsDataInfo->u.stCommand),
                                      pstRawData);
            break;
        case MN_MSG_TPDU_SUBMIT:
            ulRet = MSG_EncodeSubmit((MN_MSG_SUBMIT_STRU *)&(pstTsDataInfo->u.stSubmit),
                                     pstRawData);
            break;
        case MN_MSG_TPDU_SUBMIT_RPT_ACK:
            ulRet = MSG_EncodeSubmitRptAck((MN_MSG_SUBMIT_RPT_ACK_STRU *)&(pstTsDataInfo->u.stSubmitRptAck),
                                           pstRawData);
            break;
        case MN_MSG_TPDU_SUBMIT_RPT_ERR:
            ulRet = MSG_EncodeSubmitRptErr((MN_MSG_SUBMIT_RPT_ERR_STRU *)&(pstTsDataInfo->u.stSubmitRptErr),
                                           pstRawData);
            break;
        default:
            MN_WARN_LOG("MN_MSG_Encode: TPDU type is invalid.");
            ulRet = MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
            break;
    }
    return ulRet;
}

/*****************************************************************************
 函 数 名  : MSG_RequireSegment
 功能描述  : 判断当前消息是否需要分段
 输入参数  : pstLongSubmit    - 用户输入的超长短信
 输出参数  : 无
 返 回 值  : VOS_FALSE  -无需分段
             VOS_TRUE   -需要分段
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月19日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32   MSG_RequireSegment(
    const MN_MSG_SUBMIT_LONG_STRU       *pstLongSubmit
)
{
    VOS_BOOL                            bSegmentFlag        =  VOS_FALSE;
    VOS_UINT32                          ulTotalLen;
    VOS_UINT32                          ulUdhl              = 0;

    ulTotalLen = pstLongSubmit->stLongUserData.ulLen;
    if (MN_MSG_MSG_CODING_7_BIT == pstLongSubmit->stDcs.enMsgCoding)
    {
        if (VOS_TRUE == pstLongSubmit->bUserDataHeaderInd)
        {
            /*计算初始消息包头长度*/
            MSG_GetUdhl(pstLongSubmit->stLongUserData.ucNumofHeaders,
                        pstLongSubmit->stLongUserData.astUserDataHeader,
                        &ulUdhl);
            ulTotalLen += (((ulUdhl + 1) * 8) + 6)/7;
        }

        if (ulTotalLen > MN_MSG_MAX_7_BIT_LEN)
        {
            bSegmentFlag = VOS_TRUE;
        }
    }
    else
    {
        if (VOS_TRUE == pstLongSubmit->bUserDataHeaderInd)
        {
            /*计算初始消息包头长度*/
            MSG_GetUdhl(pstLongSubmit->stLongUserData.ucNumofHeaders,
                        pstLongSubmit->stLongUserData.astUserDataHeader,
                        &ulUdhl);
            ulTotalLen += (ulUdhl + 1);
        }

        if (ulTotalLen > MN_MSG_MAX_8_BIT_LEN)
        {
            bSegmentFlag = VOS_TRUE;
        }
    }

    return bSegmentFlag;
}

/*****************************************************************************
 函 数 名  : MN_MSG_Segment
 功能描述  : 同步函数,将一条超长短信分段为合适长度的短信
 输入参数  : pstLongSubmit    - 用户输入的超长短信
 输出参数  : pucNum       - 分段的个数
             pstRawData   - 指向具体分段后的短信
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月19日
    作    者   : z40661
    修改内容   : 新生成函数
 2.日    期   : 2009年10月28日
    作    者   : f62575
    修改内容   : AT2D15641, STK短信发送需要支持长短信的分段发送功能
*****************************************************************************/
VOS_UINT32   MN_MSG_Segment(
    const MN_MSG_SUBMIT_LONG_STRU       *pstLongSubmit,
    VOS_UINT8                           *pucNum,
    MN_MSG_RAW_TS_DATA_STRU             *pstRawData
)
{
    VOS_UINT32                          ulUdhl              = 0;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulConcatUdhPos;
    VOS_BOOL                            bSegmentFlag        =  VOS_FALSE;
    MN_MSG_SUBMIT_STRU                  *pstSubmit;
    MN_MSG_UDH_CONCAT_8_STRU            *pstConcat_8;
    MN_MSG_USER_HEADER_TYPE_STRU        *pstUserHeader;

    if ((VOS_NULL_PTR == pstLongSubmit)
     || (VOS_NULL_PTR == pucNum)
     || (VOS_NULL_PTR == pstRawData))
    {
        MN_ERR_LOG("MN_MSG_Segment: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    /*分段消息的属性填充并根据分段属性按submit TPDU格式编码*/
    pstSubmit = (MN_MSG_SUBMIT_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_MSG_SUBMIT_STRU));
    if (VOS_NULL_PTR == pstSubmit)
    {
        MN_ERR_LOG("MN_MSG_Segment: Fail to Alloc memory.");
        return MN_ERR_NOMEM;
    }
    pstSubmit->bRejectDuplicates    = pstLongSubmit->bRejectDuplicates;
    pstSubmit->bReplayPath          = pstLongSubmit->bReplayPath;
    pstSubmit->bUserDataHeaderInd   = pstLongSubmit->bUserDataHeaderInd;
    pstSubmit->bStaRptReq           = pstLongSubmit->bStaRptReq;
    pstSubmit->ucMr                 = pstLongSubmit->ucMr;
    pstSubmit->enPid                = pstLongSubmit->enPid;
    PS_MEM_CPY(&(pstSubmit->stDestAddr),
               &(pstLongSubmit->stDestAddr),
               sizeof(pstSubmit->stDestAddr));
    PS_MEM_CPY(&(pstSubmit->stDcs),
               &(pstLongSubmit->stDcs),
               sizeof(pstSubmit->stDcs));
    PS_MEM_CPY(&(pstSubmit->stValidPeriod),
               &(pstLongSubmit->stValidPeriod),
               sizeof(pstSubmit->stValidPeriod));
    pstSubmit->stUserData.ucNumofHeaders = pstLongSubmit->stLongUserData.ucNumofHeaders;
    PS_MEM_CPY(pstSubmit->stUserData.astUserDataHeader,
               pstLongSubmit->stLongUserData.astUserDataHeader,
               MN_MSG_MAX_UDH_NUM * sizeof(MN_MSG_USER_HEADER_TYPE_STRU));

    bSegmentFlag = MSG_RequireSegment(pstLongSubmit);
    /*对于不需要分段的消息，直接编码退出流程*/
    if (VOS_TRUE != bSegmentFlag)
    {
        *pucNum = 1;
        pstSubmit->stUserData.ulLen = pstLongSubmit->stLongUserData.ulLen;
        PS_MEM_CPY(pstSubmit->stUserData.aucOrgData,
                   pstLongSubmit->stLongUserData.pucOrgData,
                   pstSubmit->stUserData.ulLen);
        ulRet = MSG_EncodeSubmit(pstSubmit, pstRawData);
        PS_MEM_FREE(WUEPS_PID_TAF, pstSubmit);
        return ulRet;
    }

    /*对于需要分段的消息，*/
    /*1.直接编码填充Concatenated short messages消息头部*/
    ulConcatUdhPos              = pstLongSubmit->stLongUserData.ucNumofHeaders;
    pstUserHeader               = &pstSubmit->stUserData.astUserDataHeader[ulConcatUdhPos];
    pstUserHeader->enHeaderID   = MN_MSG_UDH_CONCAT_8;/*存在Extended Object IE时用MN_MSG_UDH_CONCAT_16*/
    pstConcat_8                 = (MN_MSG_UDH_CONCAT_8_STRU *)&(pstUserHeader->u.stConcat_8);
    pstConcat_8->ucSeqNum       = 1;
    pstConcat_8->ucMr           = pstLongSubmit->ucMr;
    pstSubmit->stUserData.ucNumofHeaders++;
    pstSubmit->bUserDataHeaderInd   = VOS_TRUE;

    /*2.计算分段后消息包头长度*/
    MSG_GetUdhl(pstSubmit->stUserData.ucNumofHeaders,
                pstSubmit->stUserData.astUserDataHeader,
                &ulUdhl);
    if (ulUdhl >= (MN_MSG_MAX_8_BIT_LEN - 1))
    {
        MN_WARN_LOG("MN_MSG_Segment: the length of message is invalid.");
        PS_MEM_FREE(WUEPS_PID_TAF, pstSubmit);
        return MN_ERR_CLASS_SMS_MSGLEN_OVERFLOW;
    }

    /*3.计算分段后每个消息段中SM的长度: UDL最大长度去除UDHL和UDH的长度*/
    if (MN_MSG_MSG_CODING_7_BIT == pstLongSubmit->stDcs.enMsgCoding)
    {
        ulLen = MN_MSG_MAX_7_BIT_LEN - ((((ulUdhl + 1) * 8) + 6)/7);
    }
    else
    {
        ulLen = MN_MSG_MAX_8_BIT_LEN - (ulUdhl + 1);
    }

    /*计算分段后分段的个数并填充各分段的MN_MSG_SUBMIT_STRU结构数据*/
    *pucNum = (VOS_UINT8)((pstLongSubmit->stLongUserData.ulLen + (ulLen - 1))/ulLen);
    pstConcat_8->ucTotalNum     = (*pucNum);
    for (ulLoop = 0; ulLoop < (*pucNum); ulLoop++)
    {
        if (pstConcat_8->ucSeqNum == (*pucNum))
        {
            pstSubmit->stUserData.ulLen = pstLongSubmit->stLongUserData.ulLen - (ulLen * ulLoop);
        }
        else
        {
            pstSubmit->stUserData.ulLen = ulLen;
        }
        PS_MEM_CPY(pstSubmit->stUserData.aucOrgData,
                   &(pstLongSubmit->stLongUserData.pucOrgData[((VOS_ULONG)ulLen * ulLoop)]),
                   pstSubmit->stUserData.ulLen);
        ulRet = MSG_EncodeSubmit(pstSubmit, pstRawData);
        if ( MN_ERR_NO_ERROR != ulRet )
        {
            PS_MEM_FREE(WUEPS_PID_TAF, pstSubmit);
            return ulRet;
        }
        pstConcat_8->ucSeqNum++;
        pstRawData++;
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstSubmit);
    return MN_ERR_NO_ERROR;
}

/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */

/*****************************************************************************
 函 数 名  : MN_MSG_BuildDefSubmitMsg
 功能描述  : 同步函数,根据设置的短信服务参数和用户输入的内容编码为TPDU格式的短信
 输入参数  : pstDefSubmit      - 输入短信相关内容
             pstSrvPara       - 需要使用的短信参数
 输出参数  : pstRawData        - 编码后TPDU格式的短信
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32   MN_MSG_BuildDefSubmitMsg(
    const MN_MSG_SUBMIT_DEF_PARM_STRU   *pstDefSubmit,
    const MN_MSG_SRV_PARAM_STRU         *pstSrvPara,
    MN_MSG_RAW_TS_DATA_STRU             *pstRawData
)
{
    MN_MSG_SUBMIT_STRU                  *pstSubmit;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pstDefSubmit)
     || (VOS_NULL_PTR == pstSrvPara)
     || (VOS_NULL_PTR == pstRawData))
    {
        MN_ERR_LOG("MN_MSG_BuildDefSubmitMsg: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    pstSubmit = (MN_MSG_SUBMIT_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_MSG_SUBMIT_STRU));
    if (VOS_NULL_PTR == pstSubmit)
    {
        MN_ERR_LOG("MN_MSG_BuildDefSubmitMsg: Fail to Alloc memory.");
        return MN_ERR_NOMEM;
    }
    pstSubmit->bRejectDuplicates = VOS_FALSE;
    /*pstServPara->stAlphaIdInfo对应手机上的预置模式,此处因为结构中已经是用户指定数据,所以不使用*/
    pstSubmit->bReplayPath       = pstDefSubmit->bReplayPath;
    pstSubmit->bStaRptReq        = pstDefSubmit->bStaRptReq;
    pstSubmit->bUserDataHeaderInd= pstDefSubmit->bUserDataHeaderInd;
    pstSubmit->enPid             = pstSrvPara->ucPid;
    ulRet = MN_MSG_DecodeDcs(pstSrvPara->ucDcs, &(pstSubmit->stDcs));
    if (MN_ERR_NO_ERROR != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstSubmit);
        return ulRet;
    }

    pstSubmit->stDestAddr                  = pstDefSubmit->stDestAddr;
    pstSubmit->stUserData                  = pstDefSubmit->stUserData;
    pstSubmit->stValidPeriod.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;
    pstSubmit->stValidPeriod.u.ucOtherTime = pstSrvPara->ucValidPeriod;
    pstSubmit->ucMr                        = pstDefSubmit->ucMr;
    ulRet = MSG_EncodeSubmit(pstSubmit, pstRawData);
    PS_MEM_FREE(WUEPS_PID_TAF, pstSubmit);
    return ulRet;
}

/*****************************************************************************
 函 数 名  : MN_MSG_EncodeTpRd
 功能描述  : 编码TP-RD参数到TP-FO
 输入参数  : VOS_BOOL                            bRejectDuplicates  TP-RD标志
 输出参数  : VOS_UINT8                          *pucTpFo            TP-FO
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月8日
    作    者   : f62575
    修改内容   : DTS2012110604069 新生成函数

*****************************************************************************/
VOS_VOID MN_MSG_EncodeTpRd(
    VOS_BOOL                            bRejectDuplicates,
    VOS_UINT8                          *pucTpFo
)
{
    /* 设置TP-RD为入参中的bRejectDuplicates */
    MSG_SET_TP_RD(*pucTpFo, bRejectDuplicates);

    return;
}
/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

