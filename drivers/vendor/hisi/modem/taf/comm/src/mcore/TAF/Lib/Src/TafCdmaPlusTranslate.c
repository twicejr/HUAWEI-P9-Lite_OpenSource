

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "TafCdmaPlusTranslate.h"
#include "PsCommonDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID PS_FILE_ID_TAF_CDMA_PLUS_TRANSLATE_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* 添加电信物联网号码10649 */
TAF_COUNTRY_DIAL_CODE_INFO g_astTafCountryList[] =
{
    {13568, 14335, 86, 460, "00", "13", "0", VOS_FALSE, ""},/* China 13568*/

    {25600, 26111, 86, 460, "00", "13", "0", VOS_FALSE, ""},/* China 25600*/

    {13568, 14335, 86, 460, "00", "14", "0", VOS_FALSE, ""},/* China 13568*/

    {25600, 26111, 86, 460, "00", "14", "0", VOS_FALSE, ""},/* China 25600*/

    {13568, 14335, 86, 460, "00", "15", "0", VOS_FALSE, ""},/* China 13568*/

    {25600, 26111, 86, 460, "00", "15", "0", VOS_FALSE, ""},/* China 25600*/

    {13568, 14335, 86, 460, "00", "17", "0", VOS_FALSE, ""},/* China 13568*/

    {25600, 26111, 86, 460, "00", "17", "0", VOS_FALSE, ""},/* China 25600*/

    {13568, 14335, 86, 460, "00", "18", "0", VOS_FALSE, ""},/* China 13568*/

    {25600, 26111, 86, 460, "00", "18", "0", VOS_FALSE, ""},/* China 25600*/

    {13568, 14335, 86, 460, "00", "10649", "0", VOS_FALSE, ""},/* China 13568*/

    {25600, 26111, 86, 460, "00", "10649", "0", VOS_FALSE, ""},/* China 25600*/

    {12288, 13311, 81, 440, "010", "", "0", VOS_FALSE, ""}, /* Japan 12288*/

    {12288, 13311, 81, 441, "010", "", "0", VOS_FALSE, ""}, /* Japan */

    {2176, 2303, 82, 450, "00700", "", "0", VOS_FALSE, ""}, /* Korea (South) */

    {11296, 11311, 853, 455, "00", "", "0", VOS_FALSE, ""}, /* Macao/Macau : 11296 */
};



/*****************************************************************************
  3 函数实现
*****************************************************************************/


TAF_COUNTRY_DIAL_CODE_INFO* TAF_GetCountryListAddr(
    VOS_VOID
)
{
    return (g_astTafCountryList);
}


VOS_INT32 TAF_ConvertHomeMccToSidRange(
    VOS_UINT16                          usHomeMcc
)
{
    VOS_INT32                           lSid;
    VOS_UINT32                          i;
    TAF_COUNTRY_DIAL_CODE_INFO         *pstCountryDailCodeInfo  = VOS_NULL_PTR;

    lSid                                = TAF_INVALID_SID;
    pstCountryDailCodeInfo = TAF_GetCountryListAddr();

    for (i = 0; i < TAF_COUNTRY_LIST_LEN; i++)
    {
        if (usHomeMcc == pstCountryDailCodeInfo[i].usMcc)
        {
            lSid    = (VOS_INT32)pstCountryDailCodeInfo[i].usSidRangeStart;

            return lSid;
        }
    }

    return lSid;
}

VOS_UINT16 TAF_GetMccOfCountryList(
    VOS_UINT16                         Index
)
{
    return (g_astTafCountryList[Index].usMcc);
}


VOS_UINT16 TAF_GetCcOfCountryList(
    VOS_UINT16                         Index
)
{
    return (g_astTafCountryList[Index].usCc);
}



VOS_UINT8* TAF_GetIpcOfCountryList(
    VOS_UINT16                         Index
)
{
    return (VOS_UINT8*)(g_astTafCountryList[Index].acInterPrefixCode);
}


VOS_UINT8* TAF_GetDpcOfCountryList(
    VOS_UINT16                         Index
)
{
    return (VOS_UINT8*)(g_astTafCountryList[Index].acDialPrefixCode);
}


VOS_UINT8* TAF_GetNehOfCountryList(
    VOS_UINT16                         Index
)
{
    return (VOS_UINT8*)(g_astTafCountryList[Index].acNumEntityHeader);
}


VOS_UINT8 TAF_GetNehLenOfCountryList(
    VOS_UINT16                         Index
)
{
    return (VOS_UINT8)VOS_StrLen((VOS_CHAR*)g_astTafCountryList[Index].acNumEntityHeader);
}


VOS_UINT8 TAF_GetIpcLenOfCountryList(
    VOS_UINT16                         Index
)
{
    return (VOS_UINT8)VOS_StrLen((VOS_CHAR*)g_astTafCountryList[Index].acInterPrefixCode);
}


VOS_UINT8 TAF_GetDpcLenOfCountryList(
    VOS_UINT16                         Index
)
{
    return (VOS_UINT8)VOS_StrLen((VOS_CHAR*)g_astTafCountryList[Index].acDialPrefixCode);
}


VOS_UINT8 TAF_GetCcLenOfCountryList(
    VOS_UINT16                         Index
)
{
    VOS_UINT8                           ucCcLen;
    VOS_UINT16                          usCountryListCc;
    VOS_INT8                            acCountryListCc[TAF_COUNTRY_CODE_MAX_LEN];

    usCountryListCc  =TAF_GetCcOfCountryList(Index);

    PS_MEM_SET(acCountryListCc, 0, sizeof(acCountryListCc));
    VOS_sprintf((VOS_CHAR*)acCountryListCc, "%d", usCountryListCc);
    ucCcLen          = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)acCountryListCc);

    return ucCcLen;
}



VOS_VOID TAF_GetInfoInCountryList(
    VOS_INT32                           lSid,
    VOS_UINT16                         *pusMccFirstMatchEntryIndex,
    VOS_UINT16                         *pusMccMatchEntryNum
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usFirstMatchEntryIndex;
    VOS_UINT16                          usMatchEntryNum;
    TAF_COUNTRY_DIAL_CODE_INFO         *pstCountryDailCodeInfo  = VOS_NULL_PTR;

    usFirstMatchEntryIndex = 0;
    usMatchEntryNum        = 0;
    pstCountryDailCodeInfo = TAF_GetCountryListAddr();

    for (i = 0; i < TAF_COUNTRY_LIST_LEN; i++)
    {
        if ((lSid >= (VOS_INT32)pstCountryDailCodeInfo[i].usSidRangeStart)
         && (lSid <= (VOS_INT32)pstCountryDailCodeInfo[i].usSidRangeEnd))
        {
            if (0 == usMatchEntryNum)
            {
                usFirstMatchEntryIndex = i;
            }

            usMatchEntryNum = i - usFirstMatchEntryIndex + 1;
        }
    }

    if (0 != usMatchEntryNum)
    {
        *pusMccFirstMatchEntryIndex = usFirstMatchEntryIndex;
        *pusMccMatchEntryNum        = usMatchEntryNum;

    }

    return;
}


VOS_UINT32 TAF_ConvertASCIINumToUint(
    VOS_UINT8                           ucstartDigit,
    VOS_UINT8                           ucDigitsLen,
    VOS_UINT8                          *pucAsciiNum
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucDigit;
    VOS_UINT32                          ulValue;

    ulValue = 0;
    ucDigit = 0;

    for (i = ucstartDigit; i < ucDigitsLen; i++)
    {
        ucDigit = (VOS_UINT8)(pucAsciiNum[i] - '0');

        ulValue = ulValue*10 + ucDigit;
    }

    return ulValue;

}


VOS_VOID TAF_InsertDigitsInNumHeader(
    VOS_UINT8                          *pucInsertDigits,
    VOS_UINT8                           ucInsertDigitsLen,
    VOS_UINT8                          *pucAsciiNum,
    VOS_UINT8                          *pucNumLen
)
{
    VOS_UINT8                          ucNumLen;

    ucNumLen    = *pucNumLen;

    if ((ucInsertDigitsLen + ucNumLen) > (TAF_MO_MAX_ASCII_NUM_LEN + 1))
    {
        return;
    }

    /*号码后移 */
    PS_MEM_MOVE(&(pucAsciiNum[ucInsertDigitsLen]),
                &(pucAsciiNum[0]),
                (ucNumLen * sizeof(VOS_UINT8)));

    /*插入号码 */
    PS_MEM_CPY(pucAsciiNum, pucInsertDigits, ucInsertDigitsLen);

    /*更新号码长度 */
    ucNumLen  += ucInsertDigitsLen;

    *pucNumLen = ucNumLen;

    return;
}


VOS_VOID TAF_SkipDigitsOfNumHeader(
    VOS_UINT8                          *pucAsciiNum,
    VOS_UINT8                          *pucNumLen,
    VOS_UINT8                           ucSkipDigitsLen
)
{
    VOS_UINT8                           ucNumLen;

    ucNumLen    = *pucNumLen;

    PS_MEM_MOVE(&(pucAsciiNum[0]),
                &(pucAsciiNum[ucSkipDigitsLen]),
                (ucNumLen - ucSkipDigitsLen) * sizeof(VOS_UINT8));

    /*剩余位清零 */
    PS_MEM_SET(&(pucAsciiNum[ucNumLen - ucSkipDigitsLen]), 0, ucSkipDigitsLen);

    /*更新号码长度 */
    ucNumLen   -= ucSkipDigitsLen;

    *pucNumLen  = ucNumLen;

    return;
}



VOS_UINT8 TAF_IsNumEntityHeaderInCountryList(
    VOS_UINT16                          usMccFirstMatchEntryIndex,
    VOS_UINT16                          usMccMatchEntryNum,
    VOS_UINT8                          *pucAsciiNum
)
{
    VOS_UINT16                          i;
    VOS_UINT32                          ulCalledNumEntityHeader;
    VOS_UINT32                          ulCountryListNumEntityHeader;
    VOS_UINT8                           ucNumEntityHeaderLen;
    VOS_UINT8                          *pucNumEntityHeader = VOS_NULL_PTR;

    /*在country list 中，一个mcc只会对应一个 ipc 和 dpc ，但可能对应多个号码实体头  */

    /*检测 号码实体头部是否在country list 中*/
    for (i = usMccFirstMatchEntryIndex; i < (usMccFirstMatchEntryIndex + usMccMatchEntryNum); i++)
    {
        /*获取 号码实体头部 所应占据的长度 */
        pucNumEntityHeader    = TAF_GetNehOfCountryList(i);

        ucNumEntityHeaderLen  = TAF_GetNehLenOfCountryList(i);

        if (0 == ucNumEntityHeaderLen)
        {
            return VOS_FALSE;
        }

        /*获取country list中，匹配MCC的记录中， 号码实体头部 的值 */
        ulCountryListNumEntityHeader = TAF_ConvertASCIINumToUint(0, ucNumEntityHeaderLen, (VOS_UINT8 *)pucNumEntityHeader);

        /*依据号码实体头部的位数，求出呼叫号码中该值 */
        ulCalledNumEntityHeader      = TAF_ConvertASCIINumToUint(0, ucNumEntityHeaderLen, pucAsciiNum);

        if (ulCountryListNumEntityHeader == ulCalledNumEntityHeader)
        {

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}




VOS_UINT8 TAF_IsIpcAndCcInCountryList(
    VOS_UINT16                          usMccFirstMatchEntryIndex,
    VOS_UINT8                          *pucAsciiNum
)
{
    VOS_UINT32                          ulNumIpc;
    VOS_UINT16                          usNumCc;
    VOS_UINT32                          ulCountryListIpc;
    VOS_UINT8                           ucIpcLen;
    VOS_UINT16                          usCountryListCc;
    VOS_UINT8                           ucCcLen;

    VOS_UINT8                          *pucCountryListIpc = VOS_NULL_PTR;

    /*如果匹配，则呼叫号码的构成为: ipc + cc + 剩余号码 ,
      country list中，一个mcc 只会对应一组 ipp + cc   */

    /*获取country list中， cc 的值 */
    usCountryListCc  =TAF_GetCcOfCountryList(usMccFirstMatchEntryIndex);

    /*依据country list中，ipc 和 cc 的值的长度，判断呼叫号码中，
      如果号码开头也由ipc + cc 组成，ipc 和 cc 应该占据的位数    */
    ucIpcLen         = TAF_GetIpcLenOfCountryList(usMccFirstMatchEntryIndex);

    ucCcLen          = TAF_GetCcLenOfCountryList(usMccFirstMatchEntryIndex);

    pucCountryListIpc = TAF_GetIpcOfCountryList(usMccFirstMatchEntryIndex);

    /*获取country list中，ipc 的值 */
    ulCountryListIpc = TAF_ConvertASCIINumToUint(0, ucIpcLen, pucCountryListIpc);


    /* 依据ipc、cc占据的位数，求出呼叫号码中该值 */
    ulNumIpc         = TAF_ConvertASCIINumToUint(0, ucIpcLen, pucAsciiNum);
    usNumCc          = (VOS_UINT16)TAF_ConvertASCIINumToUint(ucIpcLen, (ucCcLen + ucIpcLen), pucAsciiNum);

    /* ipc + cc 匹配， */
    if ((ulNumIpc == ulCountryListIpc)
     && (usNumCc  == usCountryListCc))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}


VOS_UINT8 TAF_IsCcInCountryList(
    VOS_UINT16                          usMccFirstMatchEntryIndex,
    VOS_UINT8                          *pucAsciiNum
)
{
    VOS_UINT16                          usNumCc;
    VOS_UINT16                          usCountryListCc;
    VOS_UINT8                           ucCcLen;

    usCountryListCc     = TAF_GetCcOfCountryList(usMccFirstMatchEntryIndex);

    ucCcLen             = TAF_GetCcLenOfCountryList(usMccFirstMatchEntryIndex);

    usNumCc             = (VOS_UINT16)TAF_ConvertASCIINumToUint(0, ucCcLen, pucAsciiNum);

    if (usCountryListCc == usNumCc)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}



VOS_UINT8 TAF_TranslatePlusToNationalNum(
    VOS_UINT16                          usMccFirstMatchEntryIndex,
    VOS_UINT16                          usMccMatchEntryNum,
    VOS_UINT8                          *pucCurASCIINum,
    VOS_UINT8                          *pucCurNumLen
)
{

    VOS_UINT8                           ucIpcLen;
    VOS_UINT8                           ucCcLen;
    VOS_UINT8                          *pucNumDpc = VOS_NULL_PTR;
    VOS_UINT8                           ucDpcLen;

    /*检测开头的号码是否是IPC+CC,如果是，直接跳过IPC + CC，返回真，如果不是，退出，号码不做修改 */
    if (VOS_TRUE == TAF_IsIpcAndCcInCountryList(usMccFirstMatchEntryIndex, pucCurASCIINum))
    {
        /*跳过 ipc + cc 位 */
        ucIpcLen         = TAF_GetIpcLenOfCountryList(usMccFirstMatchEntryIndex);
        ucCcLen          = TAF_GetCcLenOfCountryList(usMccFirstMatchEntryIndex);

        TAF_SkipDigitsOfNumHeader(pucCurASCIINum, pucCurNumLen, (VOS_UINT8)(ucIpcLen + ucCcLen));

    }
    else
    {
        return VOS_FALSE;
    }

    /*检测号码实体的头部是否在国家列表中 */
    if (VOS_FALSE == TAF_IsNumEntityHeaderInCountryList(usMccFirstMatchEntryIndex, usMccMatchEntryNum, pucCurASCIINum))
    {

         /*号码实体头部不在country list 中，将dpc插入到号码头部 */
         pucNumDpc   = TAF_GetDpcOfCountryList(usMccFirstMatchEntryIndex);
         ucDpcLen    = TAF_GetDpcLenOfCountryList(usMccFirstMatchEntryIndex);

         TAF_InsertDigitsInNumHeader(pucNumDpc, ucDpcLen, pucCurASCIINum, pucCurNumLen);
    }

    return VOS_TRUE;

}


VOS_VOID TAF_TranslatePlusToInternationalNum(
    VOS_UINT16                          usMccFirstMatchEntryIndex,
    VOS_UINT16                          usMccMatchEntryNum,
    VOS_UINT8                          *pucCurASCIINum,
    VOS_UINT8                          *pucCurNumLen
)
{
    VOS_UINT8                           ucCcLen;
    VOS_UINT8                          *pucNumIpc = VOS_NULL_PTR;
    VOS_UINT8                           ucIpcLen;
    VOS_UINT8                          *pucNumDpc = VOS_NULL_PTR;
    VOS_UINT8                           ucDpcLen;

    if (VOS_TRUE == TAF_IsCcInCountryList(usMccFirstMatchEntryIndex, pucCurASCIINum))
    {
        /*相等, 带加号的国内呼叫，跳过国家码 */
        ucCcLen = TAF_GetCcLenOfCountryList(usMccFirstMatchEntryIndex);

        TAF_SkipDigitsOfNumHeader(pucCurASCIINum, pucCurNumLen, ucCcLen);

        /*继续按国内呼叫流程执行*/
        if (VOS_FALSE == TAF_IsNumEntityHeaderInCountryList(usMccFirstMatchEntryIndex, usMccMatchEntryNum, pucCurASCIINum))
        {
             /*号码实体头部不在country list 中，将dpc插入到号码头部 */
             pucNumDpc   = TAF_GetDpcOfCountryList(usMccFirstMatchEntryIndex);
             ucDpcLen    = TAF_GetDpcLenOfCountryList(usMccFirstMatchEntryIndex);

             TAF_InsertDigitsInNumHeader(pucNumDpc, ucDpcLen, pucCurASCIINum, pucCurNumLen);
        }
    }
    else
    {
        /*不同，带加号的国际呼 ，加上IPC，最终号码格式即 ipc + cc + 号码实体 */
        pucNumIpc   = TAF_GetIpcOfCountryList(usMccFirstMatchEntryIndex);
        ucIpcLen    = TAF_GetIpcLenOfCountryList(usMccFirstMatchEntryIndex);

        TAF_InsertDigitsInNumHeader(pucNumIpc, ucIpcLen, pucCurASCIINum, pucCurNumLen);
    }

    return;
}


VOS_VOID TAF_TranslatePlusToNum(
    VOS_INT32                                               lSid,
    TAF_PLUS_TRANSLATE_DIAL_TYPE_ENUM_U8                    enDialType,
    TAF_PLUS_TRANSLATE_NUM_TYPE_ENUM_U8                    *penNumType,
    VOS_UINT8                                              *pucAsciiNum,
    VOS_UINT8                                              *pucNumLen
)
{
    /**************************************************************************************************

    1、主叫过程中，无论是语音业务还是短信业务，在前一阶段的处理过程中，如果带加号，都将加号去掉，
    通过将号码类型改为国际类型来标示之前号码带有加号；

    2、国际呼叫类型处理:
    2.1、如果呼叫号码中的Cc与国际列表中，Mcc对应的CC相同，即带加号的国内呼叫,去掉CC，再根据neh
    是否与国家列表中Mcc对应的相匹配，如果存在不匹配，需要加上npc
    (exp +8613888888888 转换为 13888888888；+86 21 888888888 转换为 021 888888888)

    2.2、如果呼叫号码中的Cc与国际列表中，Mcc对应的CC相同，即国际呼叫，最终呼叫号码结构:"ipc" + "cc" + "neh" + "剩余号码"
    (exp 国内用户呼叫日本用户 +81xxxxxxx 转换为 0081xxxxxxx)

    3、国内呼叫类型处理
    3.1、如果呼叫类型为"ipc" + "cc" + "neh" + "剩余号码"，转换为"ipc/npc(判断同2.1)"+"neh" + "剩余号码"
    (exp 008613888888888 转换为 0013888888888；008614888888888 转换为 014888888888)

    3.2、其他号码不做改变
    ****************************************************************************************************/


    VOS_UINT16                                              usMccFirstMatchEntryIndex;
    VOS_UINT16                                              usMccMatchEntryNum;
    VOS_UINT8                                               aucAsciiNum[TAF_MO_MAX_ASCII_NUM_LEN + 1];
    VOS_UINT8                                               ucNumLen;
    TAF_PLUS_TRANSLATE_NUM_TYPE_ENUM_U8                     enNumType;

    /*检测mcc 是否在 countrylist,返回匹配的记录数量，以及第一条记录的索引 */
    usMccFirstMatchEntryIndex = 0;
    usMccMatchEntryNum        = 0;

    /*获取匹配的Sid信息 */
    TAF_GetInfoInCountryList(lSid, &usMccFirstMatchEntryIndex, &usMccMatchEntryNum);

    /*没有匹配记录 */
    if (0 == usMccMatchEntryNum)
    {
        return;
    }


    /* 获取呼叫号码长度 */
    ucNumLen                  = *pucNumLen;

    /* 获取号码类型*/
    enNumType                 = *penNumType;

    /*获取呼叫号码 */
    PS_MEM_SET(aucAsciiNum, 0, sizeof(aucAsciiNum));
    PS_MEM_CPY(aucAsciiNum, pucAsciiNum, sizeof(aucAsciiNum));

    if (TAF_PLUS_TRANSLATE_NUM_INTERNATIONAL == enNumType)
    {

        /*国际呼叫处理 */
        TAF_TranslatePlusToInternationalNum(usMccFirstMatchEntryIndex, usMccMatchEntryNum, aucAsciiNum, &ucNumLen);
    }
    else
    {
        if (VOS_FALSE == TAF_TranslatePlusToNationalNum(usMccFirstMatchEntryIndex, usMccMatchEntryNum, aucAsciiNum, &ucNumLen))
        {
            return;
        }
    }

    /*如果完成加号转换，即加号已经被去掉，所有呼叫类型更新为国内呼叫类型 */
    enNumType                 = TAF_PLUS_TRANSLATE_NUM_NATIONAL;

    /*将转换后的号码信息写回 */
    PS_MEM_CPY(pucAsciiNum, aucAsciiNum, sizeof(aucAsciiNum));
    *pucNumLen                = ucNumLen;
    *penNumType               = enNumType;

    return;

}

#if 0

VOS_UINT8 TAF_IsIpcInCountryList(
    VOS_UINT16                          usMccFirstMatchEntryIndex,
    VOS_UINT8                          *pucAsciiNum
)
{
    VOS_UINT32                          ulNumIpc;
    VOS_UINT32                          ulCountryListIpc;
    VOS_UINT8                           ucIpcLen;
    VOS_UINT8                          *pucCountryListIpc = VOS_NULL_PTR;

    pucCountryListIpc = TAF_GetIpcOfCountryList(usMccFirstMatchEntryIndex);

    ucIpcLen          = TAF_GetIpcLenOfCountryList(usMccFirstMatchEntryIndex);

    ulCountryListIpc  = TAF_ConvertASCIINumToUint(0, ucIpcLen, pucCountryListIpc);

    ulNumIpc          = TAF_ConvertASCIINumToUint(0, ucIpcLen, pucAsciiNum);

    if (ulCountryListIpc == ulNumIpc)
    {

        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}

VOS_UINT8 TAF_TranslateInternationalNumToPlus(
    VOS_UINT16                                              usMccFirstMatchEntryIndex,
    VOS_UINT8                                              *pucAsciiNum,
    VOS_UINT8                                              *pucNumLen,
    TAF_PLUS_TRANSLATE_DIAL_TYPE_ENUM_U8                    enDialType
)
{
    VOS_UINT8                                               ucIpcLen;
    VOS_UINT8                                               ucNumLen;

    /*匹配号码开头的ipc是否在国家列表中 */
    if (VOS_TRUE == TAF_IsIpcInCountryList(usMccFirstMatchEntryIndex, pucAsciiNum))
    {
        /*ipc 匹配，跳过ipc位 */
        ucIpcLen = TAF_GetIpcLenOfCountryList(usMccFirstMatchEntryIndex);

        TAF_SkipDigitsOfNumHeader(pucAsciiNum, pucNumLen, ucIpcLen);
    }

    /*短信呼叫 */
    if (TAF_PLUS_TRANSLATE_DIAL_TYPE_SMS == enDialType)
    {
        /*插入加号在号码头部 */
        if ((*pucNumLen) >= (TAF_MT_MAX_ASCII_NUM_LEN + 1))
        {
            return VOS_FALSE;
        }

        ucNumLen = *pucNumLen;

        /*号码后移 */
        PS_MEM_MOVE(&(pucAsciiNum[1]),
                    &(pucAsciiNum[0]),
                    (ucNumLen * sizeof(VOS_UINT8)));

        pucAsciiNum[0] = '+';

        ucNumLen++;

        *pucNumLen = ucNumLen;

        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}


VOS_UINT8 TAF_TranslateNationalNumToPlus(
    VOS_UINT16                                              usMccFirstMatchEntryIndex,
    VOS_UINT8                                              *pucAsciiNum,
    VOS_UINT8                                              *pucNumLen,
    TAF_PLUS_TRANSLATE_NUM_TYPE_ENUM_U8                    *penNumType
)
{
    VOS_UINT8                                               ucIpcLen;

    if (VOS_TRUE == TAF_IsIpcInCountryList(usMccFirstMatchEntryIndex, pucAsciiNum))
    {
        /*ipc 匹配，跳过ipc位 */
        ucIpcLen          = TAF_GetIpcLenOfCountryList(usMccFirstMatchEntryIndex);

        TAF_SkipDigitsOfNumHeader(pucAsciiNum, pucNumLen, ucIpcLen);

        /*更新号码类型为国际呼叫 */
        *penNumType = TAF_PLUS_TRANSLATE_NUM_INTERNATIONAL;

        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}


VOS_VOID TAF_TranslateNumToPlus(
    VOS_UINT16                                              usCurMcc,
    TAF_PLUS_TRANSLATE_DIAL_TYPE_ENUM_U8                    enDialType,
    TAF_PLUS_TRANSLATE_NUM_TYPE_ENUM_U8                    *penNumType,
    VOS_UINT8                                              *pucAsciiNum,
    VOS_UINT8                                              *pucNumLen
)
{
    /**************************************************************************************************

    1、国际呼叫类型处理:
    1.1、"ipc" + "cc" +号码,语音业务，转换为"cc" +号码
    1.2、"ipc" + "cc" +号码,短信业务，转换为"+" + "cc" + 号码
    2、国内呼叫类型处理:
    任何业务，"ipc" + "cc" +号码,语音业务，转换为"cc" +号码
    3、其他号码不做修改
    ****************************************************************************************************/

    VOS_UINT16                                              usMccFirstMatchEntryIndex;
    VOS_UINT16                                              usMccMatchEntryNum;
    VOS_UINT8                                               aucAsciiNum[TAF_MT_MAX_ASCII_NUM_LEN + 1];
    VOS_UINT8                                               ucNumLen;
    TAF_PLUS_TRANSLATE_NUM_TYPE_ENUM_U8                     enNumType;

    /*检测mcc 是否在 countrylist,返回匹配的记录数量，以及第一条记录的索引 */
    usMccFirstMatchEntryIndex = 0;
    usMccMatchEntryNum        = 0;

    /*获取匹配的MCC信息 */
    TAF_GetMccInfoInCountryList(usCurMcc, &usMccFirstMatchEntryIndex, &usMccMatchEntryNum);

    /*没有匹配记录 */
    if (0 == usMccMatchEntryNum)
    {
        return;
    }

    /* 获取呼叫号码长度 */
    ucNumLen  = *pucNumLen;

    /* 获取号码类型*/
    enNumType = *penNumType;

    /*获取呼叫号码 */
    PS_MEM_SET(aucAsciiNum, 0, sizeof(aucAsciiNum));
    PS_MEM_CPY(aucAsciiNum, pucAsciiNum, sizeof(aucAsciiNum));

    if (TAF_PLUS_TRANSLATE_NUM_INTERNATIONAL == enNumType)
    {
        /*国际业务 */
        if (VOS_FALSE == TAF_TranslateInternationalNumToPlus(usMccFirstMatchEntryIndex, aucAsciiNum, &ucNumLen, enDialType))
        {
            return;
        }
    }
    else
    {
        /*国内业务 */
        if (VOS_FALSE == TAF_TranslateNationalNumToPlus(usMccFirstMatchEntryIndex, aucAsciiNum, &ucNumLen, &enNumType))
        {
            return;
        }
    }

    /*将转换后的号码信息写回 */
    PS_MEM_CPY(pucAsciiNum, aucAsciiNum, sizeof(aucAsciiNum));
    *pucNumLen   = ucNumLen;
    *penNumType  = enNumType;

    return;
}


#endif


VOS_UINT32 TAF_QueryMccWithSid(
    VOS_INT32       lSid
)
{
    VOS_UINT32                          i;

    for (i = 0; i < TAF_COUNTRY_LIST_LEN; i++)
    {
        if ((lSid >= g_astTafCountryList[i].usSidRangeStart)
         && (lSid <= g_astTafCountryList[i].usSidRangeEnd))
        {
            return (VOS_UINT32)g_astTafCountryList[i].usMcc;
        }
    }

    return TAF_MCORE_INVALID_MCC;
}


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


