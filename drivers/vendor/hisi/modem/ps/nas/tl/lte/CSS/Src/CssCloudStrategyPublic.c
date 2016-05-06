/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : CssCloudStrategyPublic.c
  Description     : CSS云端频点频段特性公共功能的实现
  History         :
     1.chengmin 00285307    2015-10-12  Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "CssCloudStrategyPublic.h"
#include "NasMmlLib.h"
#include "CssProcAtMsg.h"
#include "MnClient.h"


#define    THIS_FILE_ID        PS_FILE_ID_CSSCLOUDSTRATEGYPUBLIC_C


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif


/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
VOS_UINT32 g_aulCssUSAMcc[]       = {0x00000103, 0x00010103, 0x00020103, 0x00030103, 0x00040103, 0x00050103, 0x00060103};
VOS_UINT32 g_aulCssUKMcc[]        = {0x00040302, 0x00050302};
VOS_UINT32 g_aulCssIndianMcc[]    = {0x00040004, 0x00050004, 0x00060004};
VOS_UINT32 g_aulCssJapanMcc[]     = {0x00000404, 0x00010404};
VOS_UINT32 g_aulCssSudanMcc[]     = {0x00040306, 0x00090506};

CSS_COUNTY_MCC_DESC_STRU g_astCountryMccList[] =
{
    {sizeof(g_aulCssUSAMcc)/sizeof(VOS_UINT32), g_aulCssUSAMcc},
    {sizeof(g_aulCssUKMcc)/sizeof(VOS_UINT32), g_aulCssUKMcc},
    {sizeof(g_aulCssIndianMcc)/sizeof(VOS_UINT32), g_aulCssIndianMcc},
    {sizeof(g_aulCssJapanMcc)/sizeof(VOS_UINT32), g_aulCssJapanMcc},
    {sizeof(g_aulCssSudanMcc)/sizeof(VOS_UINT32), g_aulCssSudanMcc},
};

#define  CSS_MCC_COUNTY_NUM (sizeof(g_astCountryMccList)/sizeof(CSS_COUNTY_MCC_DESC_STRU))



/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name  : CSS_ConvertSimPlmnToGuPlmn
 Description    : 将Sim中存储PLMN的格式转化为GU存储PLMN的格式
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ConvertSimPlmnToGuPlmn
(
    VOS_UINT8                           aucPlmn[CSS_PLMN_ID_LEN],
    VOS_UINT32                         *pulMcc,
    VOS_UINT32                         *pulMnc

)
{
    VOS_UINT32                          ulTempData;

    ulTempData = CSS_OCTET_LOW_4_BITS & (aucPlmn[0]);
    *pulMcc = ulTempData;
    ulTempData = (CSS_OCTET_HIGH_4_BITS & (aucPlmn[0])) >> CSS_OCTET_MOVE_4_BITS;
    *pulMcc |= ulTempData << CSS_OCTET_MOVE_8_BITS;
    ulTempData = CSS_OCTET_LOW_4_BITS & (aucPlmn[1]);
    *pulMcc |= ulTempData << CSS_OCTET_MOVE_16_BITS;

    ulTempData = (CSS_OCTET_HIGH_4_BITS & (aucPlmn[1])) >> CSS_OCTET_MOVE_4_BITS;
    *pulMnc = ulTempData << CSS_OCTET_MOVE_16_BITS;
    ulTempData = CSS_OCTET_LOW_4_BITS & (aucPlmn[2]);
    *pulMnc |= ulTempData;
    ulTempData = (CSS_OCTET_HIGH_4_BITS & (aucPlmn[2])) >> CSS_OCTET_MOVE_4_BITS;
    *pulMnc |= ulTempData << CSS_OCTET_MOVE_8_BITS;
}


/*****************************************************************************
 Function Name  : CSS_ConvertSimMccToGuMcc
 Description    : 将Sim中存储MCC的格式转化为GU存储MCC的格式
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ConvertSimMccToGuMcc
(
    VOS_UINT8                           aucMcc[2],
    VOS_UINT32                         *pulMcc
)
{
    VOS_UINT32                          ulTempData;

    ulTempData = CSS_OCTET_LOW_4_BITS & (aucMcc[0]);
    *pulMcc = ulTempData;
    ulTempData = (CSS_OCTET_HIGH_4_BITS & (aucMcc[0])) >> CSS_OCTET_MOVE_4_BITS;
    *pulMcc |= ulTempData << CSS_OCTET_MOVE_8_BITS;
    ulTempData = CSS_OCTET_LOW_4_BITS & (aucMcc[1]);
    *pulMcc |= ulTempData << CSS_OCTET_MOVE_16_BITS;
}

/*****************************************************************************
 Function Name  : CSS_ConvertSimMncToGuMnc
 Description    : 将Sim中存储MNC的格式转化为GU存储MNC的格式
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ConvertSimMncToGuMnc
(
    VOS_UINT8                           aucMnc[2],
    VOS_UINT32                         *pulMnc
)
{
    VOS_UINT32                          ulTempData;

    ulTempData = (CSS_OCTET_HIGH_4_BITS & (aucMnc[0])) >> CSS_OCTET_MOVE_4_BITS;
    *pulMnc = ulTempData << CSS_OCTET_MOVE_16_BITS;
    ulTempData = CSS_OCTET_LOW_4_BITS & (aucMnc[1]);
    *pulMnc |= ulTempData;
    ulTempData = (CSS_OCTET_HIGH_4_BITS & (aucMnc[1])) >> CSS_OCTET_MOVE_4_BITS;
    *pulMnc |= ulTempData << CSS_OCTET_MOVE_8_BITS;
}


/*****************************************************************************
 Function Name  : CSS_ConvertGuMccToSimMcc
 Description    : 将GU存储MCC的格式转化为Sim中存储MCC的格式
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ConvertGuMccToSimMcc
(
    VOS_UINT32                          ulMcc,
    VOS_UINT8                           aucMcc[2]
)
{
    aucMcc[0] = (((ulMcc >> CSS_OCTET_MOVE_8_BITS) & CSS_OCTET_LOW_4_BITS ) << CSS_OCTET_MOVE_4_BITS)
                | (ulMcc & CSS_OCTET_LOW_4_BITS);
    aucMcc[1] = (ulMcc >> CSS_OCTET_MOVE_16_BITS) & CSS_OCTET_LOW_4_BITS;
}


/*****************************************************************************
 Function Name  : CSS_ConvertGuMncToSimMnc
 Description    : 将GU存储MNC的格式转化为Sim中存储MNC的格式
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ConvertGuMncToSimMnc
(
    VOS_UINT32                          ulMnc,
    VOS_UINT8                           aucMnc[2]
)
{
    aucMnc[0] = ((ulMnc >> CSS_OCTET_MOVE_16_BITS) & CSS_OCTET_LOW_4_BITS) << CSS_OCTET_MOVE_4_BITS;
    aucMnc[1] = (((ulMnc >> CSS_OCTET_MOVE_8_BITS) & CSS_OCTET_LOW_4_BITS) << CSS_OCTET_MOVE_4_BITS)
                | (ulMnc & CSS_OCTET_LOW_4_BITS);
}


/*****************************************************************************
 Function Name  : CSS_ConvertMccDigitToSimMcc
 Description    : 将MCC1/MCC2/MCC3的格式转化为Sim中存储MCC的格式
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ConvertMccDigitToSimMcc
(
    VOS_UINT8                           ucMccDigit1,
    VOS_UINT8                           ucMccDigit2,
    VOS_UINT8                           ucMccDigit3,
    VOS_UINT8                           aucMcc[2]
)
{
    aucMcc[0] = (((ucMccDigit2 & CSS_OCTET_LOW_4_BITS) << CSS_OCTET_MOVE_4_BITS) | (ucMccDigit1 & CSS_OCTET_LOW_4_BITS));
    aucMcc[1] = (ucMccDigit3 & CSS_OCTET_LOW_4_BITS);
}

/*****************************************************************************
 Function Name  : CSS_ConvertMncDigitToSimMnc
 Description    : 将MNC1/MNC2/MNC3的格式转化为Sim中存储MNC的格式
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ConvertMncDigitToSimMnc
(
    VOS_UINT8                           ucMncDigit1,
    VOS_UINT8                           ucMncDigit2,
    VOS_UINT8                           ucMncDigit3,
    VOS_UINT8                           aucMnc[2]
)
{
    aucMnc[0] = ((ucMncDigit3 & CSS_OCTET_LOW_4_BITS) << CSS_OCTET_MOVE_4_BITS);
    aucMnc[1] = (((ucMncDigit2 & CSS_OCTET_LOW_4_BITS) << CSS_OCTET_MOVE_4_BITS) | (ucMncDigit1 & CSS_OCTET_LOW_4_BITS));
}

/*****************************************************************************
 Function Name  : CSS_HasGetMccVersionFromAp
 Description    : 是否从云端获取过版本
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_HasGetMccVersionFromAp(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           aucVersion[MCC_INFO_VERSION_LEN];

    aucVersion[0] = '0';
    aucVersion[1] = '0';
    aucVersion[2] = '.';
    aucVersion[3] = '0';
    aucVersion[4] = '0';
    aucVersion[5] = '.';
    aucVersion[6] = '0';
    aucVersion[7] = '0';
    aucVersion[8] = '0';

    for (ulLoop = 0; ulLoop < MCC_INFO_VERSION_LEN; ++ulLoop)
    {
        if (g_stCloudContrl.aucVersion[ulLoop] != aucVersion[ulLoop])
        {
            return CSS_TRUE;
        }
    }
    return CSS_FALSE;
}

/*****************************************************************************
 Function Name  : CSS_GetLocalMccFreqVersion
 Description    : 从本地获取预置频点的版本号，供NAS在CHR上报时调用
 Input          : VOS_UINT8
 Output         : VOS_UINT8
 Return Value   : VOS_UINT32

 History        :
      1.qinxuying 00355475   2016-01-07  Draft Enact
*****************************************************************************/
CSS_RESULT_ENUM_UINT32 CSS_GetLocalMccFreqVersion(VOS_UINT8 aucVersion[CSS_MCC_VERSION_INFO_LEN])
{
    VOS_UINT32                          ulLoop = 0;
    
    if (CSS_NULL_PTR == aucVersion)
    {
        return CSS_RESULT_FAIL;
    }

    for (ulLoop = 0; ulLoop < CSS_MCC_VERSION_INFO_LEN; ++ulLoop)
    {
        aucVersion[ulLoop] = g_stCloudContrl.aucVersion[ulLoop];
        TLPS_PRINT2LAYER_INFO1(CSS_GetPreferMccFreqFromLocal_ENUM,LNAS_CSS_GetPrefMccVersionInfo,aucVersion[ulLoop]);
    }

    return CSS_RESULT_SUCC;
}

/*****************************************************************************
 Function Name  : CSS_InitMccVersion
 Description    : 初始化版本号
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_InitMccVersion(VOS_VOID)
{
    g_stCloudContrl.aucVersion[0] = '0';
    g_stCloudContrl.aucVersion[1] = '0';
    g_stCloudContrl.aucVersion[2] = '.';
    g_stCloudContrl.aucVersion[3] = '0';
    g_stCloudContrl.aucVersion[4] = '0';
    g_stCloudContrl.aucVersion[5] = '.';
    g_stCloudContrl.aucVersion[6] = '0';
    g_stCloudContrl.aucVersion[7] = '0';
    g_stCloudContrl.aucVersion[8] = '0';
}

/*****************************************************************************
 Function Name  : CSS_IsMccBelongToCountry
 Description    : 判断某个MCC是否属于某个CSS预定义的多MCC国家
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsMccBelongToCountry
(
    VOS_UINT32                          ulMcc,
    CSS_COUNTY_MCC_DESC_STRU           *pstMccDesc
)
{
    VOS_UINT32                          i;
    for (i = 0; i < pstMccDesc->ulMccNum; ++i)
    {
        if (ulMcc == pstMccDesc->pulMccListAddr[i])
        {
            return CSS_TRUE;
        }
    }
    return CSS_FALSE;
}

/*****************************************************************************
 Function Name  : CSS_IsMccBelongToMultiCountry
 Description    : 判断某个MCC是否属于CSS预定义的多MCC国家
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsMccBelongToMultiCountry(VOS_UINT32 ulMcc)
{
    VOS_UINT32                          i;

    for (i = 0; i < CSS_MCC_COUNTY_NUM; ++i)
    {
        if (CSS_TRUE == CSS_IsMccBelongToCountry(ulMcc, &(g_astCountryMccList[i])))
        {
            return CSS_TRUE;
        }
    }
    return CSS_FALSE;
}


/*****************************************************************************
 Function Name  : CSS_IsTwoMccBelongToOneCountry
 Description    : 判断两个MCC是否属于同一个国家
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsTwoMccBelongToOneCountry
(
    VOS_UINT32                          ulMcc1,
    VOS_UINT32                          ulMcc2
)
{
    VOS_UINT32                          i;

    for (i = 0; i < CSS_MCC_COUNTY_NUM; ++i)
    {
        if ((CSS_TRUE == CSS_IsMccBelongToCountry(ulMcc1, &(g_astCountryMccList[i])))
            && (CSS_TRUE == CSS_IsMccBelongToCountry(ulMcc2, &(g_astCountryMccList[i]))))
        {
            return CSS_TRUE;
        }
    }
    return CSS_FALSE;
}


/*****************************************************************************
 Function Name  : CSS_AddAllMccBelongToCountry
 Description    : 初始化版本号
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddAllMccBelongToCountry
(
    VOS_UINT32                         *pulOutNum,
    CSS_PLMN_ID_STRU                    astOutPlmn[CSS_MAX_PREF_PLMN_NUM],
    CSS_COUNTY_MCC_DESC_STRU           *pstMccDesc
)
{
    VOS_UINT32                          i;
    for (i = 0; i < pstMccDesc->ulMccNum; ++i)
    {
        if (*pulOutNum < CSS_MAX_PREF_PLMN_NUM)
        {
            astOutPlmn[*pulOutNum].ulMcc = pstMccDesc->pulMccListAddr[i];
            astOutPlmn[*pulOutNum].ulMnc = CSS_INVALID_MNC;
            (*pulOutNum) ++;
        }
    }
}



VOS_VOID CSS_GetAllMccBelongToOneCountry
(
    VOS_UINT32                                    ulInNum,
    CSS_PLMN_ID_STRU                              astInPlmn[CSS_MAX_PREF_PLMN_NUM],
    VOS_UINT32                                   *pulOutNum,
    CSS_PLMN_ID_STRU                              astOutPlmn[CSS_MAX_PREF_PLMN_NUM]
)
{
    VOS_UINT32                          aulMcc[CSS_MAX_PREF_PLMN_NUM] = {0};/* 保存获取MCC的 */
    VOS_UINT32                          ulMccNum = 0;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          i;
    VOS_UINT8                           aucMccAdded[CSS_MCC_COUNTY_NUM] = {0};
    VOS_UINT32                          ulExist = CSS_FALSE;

    *pulOutNum = 0;

    /* 把那些MNC有效的PLMN找出来，放入结果数组中
       MNC无效的PLMN找出来，放入临时变量里*/
    for (ulLoop = 0; ulLoop < ulInNum; ++ulLoop)
    {
        if (CSS_INVALID_MNC == astInPlmn[ulLoop].ulMnc)
        {
            aulMcc[ulMccNum++] = astInPlmn[ulLoop].ulMcc;
        }
        else
        {
            astOutPlmn[*pulOutNum].ulMcc = astInPlmn[ulLoop].ulMcc;
            astOutPlmn[*pulOutNum].ulMnc = astInPlmn[ulLoop].ulMnc;
            (*pulOutNum) ++;
        }
    }

    /* 对临时变量中找出的MCC进行遍历，看是否属于一个多MCC国家 */
    for (ulLoop = 0; ulLoop < ulMccNum; ++ulLoop)
    {
        ulExist = CSS_FALSE;
        for (i = 0; i < CSS_MCC_COUNTY_NUM; ++i)
        {
            if (CSS_TRUE == CSS_IsMccBelongToCountry(aulMcc[ulLoop], &(g_astCountryMccList[i])))
            {
                /* 若该MCC属于多MCC国家，并且这个多MCC国家的所有MCC没有被加入过，则将所有该国家的MCC加入到结果中
                   ，并将是否加入过置为true*/
                if (CSS_FALSE == aucMccAdded[i])
                {
                    CSS_AddAllMccBelongToCountry(pulOutNum, astOutPlmn, &(g_astCountryMccList[i]));
                    aucMccAdded[i] = CSS_TRUE;
                }
                ulExist = CSS_TRUE;
                break;
            }
        }
        /* 若mCC不属于任何一个多MCC国家，则加入结果数组 */
        if (*pulOutNum < CSS_MAX_PREF_PLMN_NUM && CSS_FALSE == ulExist)
        {
            astOutPlmn[*pulOutNum].ulMcc = aulMcc[ulLoop];
            astOutPlmn[*pulOutNum].ulMnc = CSS_INVALID_MNC;
            (*pulOutNum) ++;
        }
    }
}




/*****************************************************************************
 Function Name  : CSS_isMncMatch
 Description    : MNC是否一致
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_isMncMatch(VOS_UINT8 aucMnc1[2], VOS_UINT8 aucMnc2[2])
{
    VOS_UINT32                          ulTmp1;
    VOS_UINT32                          ulTmp2;

    ulTmp1 = (CSS_OCTET_HIGH_4_BITS & (aucMnc1[0]));
    ulTmp2 = (CSS_OCTET_HIGH_4_BITS & (aucMnc2[0]));

    if (ulTmp1 == ulTmp2
        && aucMnc1[1] == aucMnc2[1])
    {
        return CSS_TRUE;
    }
    return CSS_FALSE;
}

/*****************************************************************************
 Function Name  : CSS_isMccMatch
 Description    : MCC是否一致
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_isMccMatch(VOS_UINT8 aucMcc1[2], VOS_UINT8 aucMcc2[2])
{
    VOS_UINT32                          ulTmp1;
    VOS_UINT32                          ulTmp2;

    ulTmp1 = (CSS_OCTET_LOW_4_BITS & (aucMcc1[1]));
    ulTmp2 = (CSS_OCTET_LOW_4_BITS & (aucMcc2[1]));

    if (ulTmp1 == ulTmp2
        && aucMcc1[0] == aucMcc2[0])
    {
        return CSS_TRUE;
    }
    return CSS_FALSE;
}

/*****************************************************************************
 Function Name  : CSS_IsRatSupportInFlag
 Description    : 在supportFlag中是否支持某制式
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsRatSupportInFlag(CSS_RAT_TYPE_ENUM_UINT8 ucRat, VOS_UINT8 ucSupportFlag)
{
    if (CSS_RAT_GSM == ucRat
        && (CSS_FALSE != (ucSupportFlag & CSS_GSM_SUPORT_OP)))
    {
        return CSS_TRUE;
    }

    if (CSS_RAT_UMTS_FDD == ucRat
        && (CSS_FALSE != (ucSupportFlag & CSS_WCDMA_SUPORT_OP)))
    {
        return CSS_TRUE;
    }

    if (CSS_RAT_LTE == ucRat
        && (CSS_FALSE != (ucSupportFlag & CSS_LTE_SUPORT_OP)))
    {
        return CSS_TRUE;
    }

    return CSS_FALSE;

}



VOS_VOID CSS_DeleteAllFreq(CSS_PUB_PREF_BAND_STRU *pBand)
{
    CSS_PUB_PREF_FREQ_STRU             *pFreqNode;
    CSS_PUB_PREF_FREQ_STRU             *pFreqNodeTmp;

    pFreqNode = pBand->pstFreqHead;
    /* 循环删除所有FREQ节点 */
    while (CSS_NULL_PTR != pFreqNode)
    {
        pFreqNodeTmp = pFreqNode->pstNext;

        /* 释放节点指针 */
        CSS_FreeCloudPreferNode(pFreqNode);

        /* 指向下一节点 */
        pFreqNode = pFreqNodeTmp;
    }
    pBand->ucFreqNum = CSS_NULL;
}



VOS_VOID CSS_DeleteAllBand(CSS_PUB_PREF_MNC_STRU *pMnc)
{
    CSS_PUB_PREF_BAND_STRU             *pBandNode;
    CSS_PUB_PREF_BAND_STRU             *pBandNodeTmp;

    pBandNode = pMnc->pstBandHead;
    /* 循环删除所有BAND节点 */
    while (CSS_NULL_PTR != pBandNode)
    {
        pBandNodeTmp = pBandNode->pstNext;

        /* 删除该MNC节点下的所有FREQ节点 */
        CSS_DeleteAllFreq(pBandNode);

        /* 释放节点指针 */
        CSS_FreeCloudPreferNode(pBandNode);

        /* 指向下一节点 */
        pBandNode = pBandNodeTmp;
    }
    pMnc->ucBandNum = CSS_NULL;
}




VOS_VOID CSS_DeleteAllMnc(CSS_PUB_PREF_MCC_STRU *pMcc)
{
    CSS_PUB_PREF_MNC_STRU              *pMncNode;
    CSS_PUB_PREF_MNC_STRU              *pMncNodeTmp;

    pMncNode = pMcc->pstMncHead;
    /* 循环删除所有MNC节点 */
    while (CSS_NULL_PTR != pMncNode)
    {
        pMncNodeTmp = pMncNode->pstNext;

        /* 删除该MNC节点下的所有BAND节点 */
        CSS_DeleteAllBand(pMncNode);

        /* 释放节点指针 */
        CSS_FreeCloudPreferNode(pMncNode);

        /* 指向下一节点 */
        pMncNode = pMncNodeTmp;
    }
    pMcc->ucMncNum = CSS_NULL;
}


VOS_VOID CSS_DeleteAllMcc(VOS_VOID)
{
    CSS_PUB_PREF_MCC_STRU              *pMccNode;
    CSS_PUB_PREF_MCC_STRU              *pMccNodeTmp;

    pMccNode = CSS_GetPrefMccHeadNode();
    /* 循环删除所有MCC节点 */
    while (CSS_NULL_PTR != pMccNode)
    {
        pMccNodeTmp = pMccNode->pstNext;

        /* 删除该MCC节点下的所有MNC节点 */
        CSS_DeleteAllMnc(pMccNode);

        /* 释放节点指针 */
        CSS_FreeCloudPreferNode(pMccNode);
        pMccNode = CSS_NULL_PTR;

        /* 指向下一节点 */
        pMccNode = pMccNodeTmp;
    }

    CSS_GetPrefMccHeadNode() = CSS_NULL_PTR;
    CSS_GetPrefMccTailNode() = CSS_NULL_PTR;
    CSS_GetPrefMccNodeNum()  = 0;

}

/*****************************************************************************
 Function Name  : CSS_DeleteOneMcc
 Description    : 从内存中删除某个MCC
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_DeleteOneMcc(VOS_UINT8 aucMccId[2])
{
    CSS_PUB_PREF_MCC_STRU              *pMccNode;
    CSS_PUB_PREF_MCC_STRU              *pMccNodePrev = CSS_NULL_PTR;

    /* 直接删除该MCC节点 */
    pMccNode = CSS_GetPrefMccHeadNode();
    while (CSS_NULL_PTR != pMccNode)
    {
        if (CSS_TRUE == CSS_isMccMatch(aucMccId, pMccNode->aucMccId))
        {
            CSS_DeleteAllMnc(pMccNode);

            if (CSS_NULL_PTR == pMccNodePrev)
            {
                CSS_GetPrefMccHeadNode() = pMccNode->pstNext;
            }
            else
            {
                pMccNodePrev->pstNext = pMccNode->pstNext;
            }

            if (CSS_GetPrefMccTailNode() == pMccNode)
            {
                CSS_GetPrefMccTailNode() = pMccNodePrev;
            }
            CSS_FreeCloudPreferNode(pMccNode);

            CSS_GetPrefMccNodeNum()--;
            return;
        }
        pMccNodePrev = pMccNode;
        pMccNode = pMccNode->pstNext;
    }
}

/*****************************************************************************
 Function Name  : CSS_IsMccExistInLocal
 Description    : 本地是否存在某个MCC
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsMccExistInLocal(VOS_UINT8 aucMccId[2])
{
    CSS_PUB_PREF_MCC_STRU              *pMccNode;

    /* 从头结点开始遍历 */
    pMccNode = CSS_GetPrefMccHeadNode();
    while (CSS_NULL_PTR != pMccNode)
    {
        if (CSS_TRUE == CSS_isMccMatch(aucMccId, pMccNode->aucMccId))
        {
            return CSS_TRUE;
        }
        pMccNode = pMccNode->pstNext;
    }
    return CSS_FALSE;
}


/*****************************************************************************
 Function Name  : CSS_IsMccUpdatedAccordToUpdateStateTable
 Description    : 某个MCC是否在动态表中已经更新了
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsMccUpdatedAccordToUpdateStateTable(VOS_UINT8 aucMccId[2])
{
    VOS_UINT32                          ulLoop1;
    VOS_UINT32                          ulLoop2;
    CSS_CLOUD_PUB_CONTROL_STRU         *pstCloudContrl;
    CSS_MCC_UPDATE_STRU                *pstUpdate;

    pstCloudContrl = CSS_GetCloudContrlAddr();

    /* 遍历所有状态表，找到正在更新的PID */
    for (ulLoop1 = 0; ulLoop1 < CSS_MAX_PID_NUM; ++ulLoop1)
    {
        pstUpdate = &(pstCloudContrl->astMccUpdate[ulLoop1]);
        /* 如果正在更新 */
        if (CSS_TRUE == pstUpdate->ucIsUpdating)
        {
            for (ulLoop2 = 0; ulLoop2 < pstUpdate->usMccNum; ++ulLoop2)
            {
                if ((CSS_TRUE == CSS_isMccMatch(pstUpdate->astMcc[ulLoop2].aucMccId, aucMccId))
                    && (CSS_TRUE == pstUpdate->aucUpdated[ulLoop2]))
                {
                    return CSS_TRUE;
                }
            }

        }
    }
    return CSS_FALSE;
}


VOS_VOID CSS_StartApMccUpdateProcedure
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                          ulMccNum,
    VOS_UINT16                          usClientId
)
{
    CSS_MCC_UPDATE_STRU                *pstUpdate = CSS_NULL_PTR;

    pstUpdate = &(CSS_GetCloudContrlAddr()->stApMccUpdate);
    pstUpdate->ucIsUpdating = CSS_TRUE;
    pstUpdate->usMccNum = (VOS_UINT16)ulMccNum;

    CSS_MEM_CPY_S(  pstUpdate->astMcc,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_UPDATE_MCC_NUM,
                    astMccID,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_UPDATE_MCC_NUM);
    CSS_MEM_SET_S(  pstUpdate->aucUpdated,
                    CSS_MAX_UPDATE_MCC_NUM,
                    0,
                    sizeof(VOS_UINT8)*CSS_MAX_UPDATE_MCC_NUM);

    /* 停止定时器 */
    CSS_StopTimer(&(pstUpdate->stTimer));

    /* 向AP发送MCC更新请求 */
    CSS_SendAtQueryMccNotifyByMccList(astMccID, ulMccNum, usClientId);

    /* 启动定时器 */
    pstUpdate->stTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstUpdate->stTimer.usName      = TI_CSS_WAIT_AP_UPDATE_MCC_SET_REQ;
    pstUpdate->stTimer.ulTimerLen  = TI_CSS_WAIT_MCC_SET_ONE_MCC_LEN*ulMccNum;
    CSS_StartTimer(&(pstUpdate->stTimer));
}


/*****************************************************************************
 Function Name   : CSS_StartMmcOrAsMccUpdateProcedure
 Description     : 启动MMC或AS侧的MCC更新过程
 Input           : astMccID
                   ulMccNum
                   astMccToSend
                   ulMccNumToSend
                   ulPId
 Output          : VOS_VOID
 Return          : VOS_VOID
 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_StartMmcOrAsMccUpdateProcedure
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                          ulMccNum,
    CSS_MCC_ID_STRU                     astMccToSend[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                          ulMccNumToSend,
    VOS_UINT32                          ulPId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulLoop1;
    CSS_CLOUD_PUB_CONTROL_STRU         *pstCloudContrl;
    CSS_MCC_UPDATE_STRU                *pstUpdate = CSS_NULL_PTR;
    VOS_UINT8                           ucIsExist;
    VOS_UINT32                          ulLoop2;
    VOS_UINT16                          usClientId;

    pstCloudContrl = CSS_GetCloudContrlAddr();

    /* 遍历所有状态表，找到正在更新的PID */
    for (ulLoop = 0; ulLoop < CSS_MAX_PID_NUM; ++ulLoop)
    {
        /* 如果传入的PID正在更新 */
        if ((CSS_TRUE == pstCloudContrl->astMccUpdate[ulLoop].ucIsUpdating)
            &&(pstCloudContrl->astMccUpdate[ulLoop].ulPid == ulPId))
        {
            pstUpdate = &(pstCloudContrl->astMccUpdate[ulLoop]);
            break;
        }
    }

    /* 若在动态表中没有找到相同的PID在更新，则新增一个 */
    if (CSS_NULL_PTR == pstUpdate)
    {
        for (ulLoop = 0; ulLoop < CSS_MAX_PID_NUM; ++ulLoop)
        {
            if (CSS_FALSE == pstCloudContrl->astMccUpdate[ulLoop].ucIsUpdating)
            {
                pstUpdate = &(pstCloudContrl->astMccUpdate[ulLoop]);
                break;
            }
        }
    }

    /* 若动态表已经满了 */
    if (CSS_NULL_PTR == pstUpdate)
    {
        return;
    }

    /* 赋值更新状态 */

    CSS_MEM_SET_S(  pstUpdate->aucUpdated,
                    sizeof(VOS_UINT8)*CSS_MAX_UPDATE_MCC_NUM,
                    0,
                    sizeof(VOS_UINT8)*CSS_MAX_UPDATE_MCC_NUM);

    for (ulLoop1 = 0; ulLoop1 < ulMccNum; ++ulLoop1)
    {
        /* 遍历所有状态表，看看MCC在动态表中是否已经更新 */
        if (CSS_TRUE == CSS_IsMccUpdatedAccordToUpdateStateTable(astMccID[ulLoop1].aucMccId))
        {
            pstUpdate->aucUpdated[ulLoop1] = CSS_TRUE;
            continue;
        }

        /* 如果不在toSend列表里，也更新 */
        ucIsExist = CSS_FALSE;
        for (ulLoop2 = 0; ulLoop2 < ulMccNumToSend; ++ulLoop2)
        {
            if (CSS_TRUE == CSS_isMccMatch(astMccID[ulLoop1].aucMccId, astMccToSend[ulLoop2].aucMccId))
            {
                ucIsExist = CSS_TRUE;
                break;
            }
        }
        if (CSS_FALSE == ucIsExist)
        {
            pstUpdate->aucUpdated[ulLoop1] = CSS_TRUE;
        }
    }

    pstUpdate->ucIsUpdating = CSS_TRUE;
    pstUpdate->ulPid = ulPId;
    pstUpdate->usMccNum = (VOS_UINT16)ulMccNum;

    CSS_MEM_CPY_S(  pstUpdate->astMcc,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_UPDATE_MCC_NUM,
                    astMccID,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_UPDATE_MCC_NUM);

    /* 停止定时器 */
    CSS_StopTimer(&(pstUpdate->stTimer));

    if (I1_UEPS_PID_GAS == ulPId || I1_WUEPS_PID_MMC == ulPId)
    {
        usClientId = AT_BROADCAST_CLIENT_ID_MODEM_1;
    }
    else
    {
        usClientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    }

    if (0 < ulMccNumToSend)
    {
        /* 向AP发送MCC更新请求 */
        CSS_SendAtQueryMccNotifyByMccList(astMccToSend, ulMccNumToSend, usClientId);
    }

    /* 启动定时器 */
    pstUpdate->stTimer.usPara = (VOS_UINT16)ulPId;
    pstUpdate->stTimer.ulTimerLen = TI_CSS_WAIT_MCC_SET_ONE_MCC_LEN * pstUpdate->usMccNum;
    CSS_StartTimer(&(pstUpdate->stTimer));
}


/*****************************************************************************
 Function Name  : CSS_EndApUpdateProcedure
 Description    : 终止AP的更新流程
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_EndApUpdateProcedure(VOS_VOID)
{
    CSS_CLOUD_PUB_CONTROL_STRU         *pstCssCloudContrl;

    pstCssCloudContrl = CSS_GetCloudContrlAddr();

    /* 初始化参数 */
    pstCssCloudContrl->stApMccUpdate.ulPid = 0;
    pstCssCloudContrl->stApMccUpdate.ucIsUpdating = CSS_FALSE;
    pstCssCloudContrl->stApMccUpdate.usMccNum = CSS_FALSE;

    CSS_MEM_SET_S(  pstCssCloudContrl->stApMccUpdate.astMcc,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_UPDATE_MCC_NUM,
                    0,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_UPDATE_MCC_NUM);
    CSS_MEM_SET_S(  pstCssCloudContrl->stApMccUpdate.aucUpdated,
                    sizeof(VOS_UINT8)*CSS_MAX_UPDATE_MCC_NUM,
                    0,
                    sizeof(VOS_UINT8)*CSS_MAX_UPDATE_MCC_NUM);

    /* 停止定时器 */
    CSS_StopTimer(&(pstCssCloudContrl->stApMccUpdate.stTimer));
}

/*****************************************************************************
 Function Name  : CSS_EndMmcOrAsUpdateProcedure
 Description    : 终止MMC或AS的更新流程
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_EndMmcOrAsUpdateProcedure(CSS_MCC_UPDATE_STRU *pstUpdate)
{
    /* 初始化参数 */
    pstUpdate->ulPid = 0;
    pstUpdate->ucIsUpdating = CSS_FALSE;
    pstUpdate->usMccNum = CSS_FALSE;

    CSS_MEM_SET_S(  pstUpdate->astMcc,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_UPDATE_MCC_NUM,
                    0,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_UPDATE_MCC_NUM);
    CSS_MEM_SET_S(  pstUpdate->aucUpdated,
                    sizeof(VOS_UINT8)*CSS_MAX_UPDATE_MCC_NUM,
                    0,
                    sizeof(VOS_UINT8)*CSS_MAX_UPDATE_MCC_NUM);

    /* 停止定时器 */
    CSS_StopTimer(&(pstUpdate->stTimer));
}




VOS_VOID CSS_CloudContrlTimerInit(VOS_VOID)
{
    CSS_CLOUD_PUB_CONTROL_STRU         *pstCssCloudContrl;
    VOS_UINT32                          ulLoop;
    CSS_MCC_UPDATE_STRU                *pstUpdate;

    pstCssCloudContrl = CSS_GetCloudContrlAddr();

    pstCssCloudContrl->stApMccUpdate.stTimer.phTimer     = VOS_NULL_PTR;
    pstCssCloudContrl->stApMccUpdate.stTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstCssCloudContrl->stApMccUpdate.stTimer.usName      = TI_CSS_WAIT_AP_UPDATE_MCC_SET_REQ;
    pstCssCloudContrl->stApMccUpdate.stTimer.ulTimerLen  = TI_CSS_WAIT_MCC_SET_ONE_MCC_LEN;

    for (ulLoop = 0; ulLoop < CSS_MAX_PID_NUM; ++ulLoop)
    {
        pstUpdate = &(pstCssCloudContrl->astMccUpdate[ulLoop]);
        pstUpdate->stTimer.phTimer    = VOS_NULL_PTR;
        pstUpdate->stTimer.ucMode     = VOS_RELTIMER_NOLOOP;
        pstUpdate->stTimer.usName     = TI_CSS_WAIT_MMC_OR_AS_UPDATE_MCC_SET_REQ;
        pstUpdate->stTimer.ulTimerLen = TI_CSS_WAIT_MCC_SET_ONE_MCC_LEN;

    }
}


/*****************************************************************************
 Function Name   : CSS_ReadNvCloudStrategy
 Description     : 读取云通信使能NV
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    chengmin 00285307      2015-10-15  Draft Enact
*****************************************************************************/
VOS_UINT32  CSS_ReadNvCloudStrategy(VOS_VOID)
{
    VOS_UINT32                          ulDataLen = 0;
    VOS_UINT32                          ulRslt    = CSS_FAIL;
    CSS_NV_CLOUD_STRATEGY_STRU          stCloudStrategy = {0};
    CSS_CLOUD_PUB_CONTROL_STRU         *pstCloudControl;

    pstCloudControl = CSS_GetCloudContrlAddr();

    /* 读NV */
    ulDataLen = sizeof(CSS_NV_CLOUD_STRATEGY_STRU);
    ulRslt = CSS_NV_Read(   EN_NV_ID_PS_CLOUD_FREQ_STRATEGY,
                            (VOS_VOID *)(&stCloudStrategy),
                            ulDataLen);

    if(CSS_RESULT_FAIL == ulRslt)
    {
        CSS_WARN_LOG("CSS_ReadNvCloudStrategy: read NV Fail.");
        TLPS_PRINT2LAYER_WARNING(CSS_ReadNvCloudStrategy_ENUM, LNAS_ReadNvFail);

        return CSS_FAIL;
    }

    pstCloudControl->ucCloudEnable    = stCloudStrategy.ucEnable;
    pstCloudControl->ucPrefFreqEnable = stCloudStrategy.ucCssPrefFreq;

    return CSS_SUCC;
}

/*****************************************************************************
 Function Name   : CSS_ReadNvCloudPrefArfcn
 Description     : 读取NV中预置频点
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    chengmin 00285307      2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID  CSS_ReadNvCloudPrefArfcn(VOS_VOID)
{
    VOS_UINT32                          ulDataLen = 0;
    VOS_UINT32                          ulRslt    = CSS_FAIL;
    CSS_NV_PREF_MCC_STRU               *pstNvPerfFreq;

    CSS_INFO_LOG("CSS_ReadNvCloudPrefArfcn: enter");
    TLPS_PRINT2LAYER_INFO(CSS_ReadNvCloudPrefArfcn_ENUM, LNAS_ENTRY);


    pstNvPerfFreq = (CSS_NV_PREF_MCC_STRU*)CSS_MEM_ALLOC(sizeof(CSS_NV_PREF_MCC_STRU));
    if (CSS_NULL_PTR == pstNvPerfFreq)
    {
        return;
    }
    ulDataLen = sizeof(CSS_NV_PREF_MCC_STRU);

    /* 读MCC1 */
    CSS_MEM_SET_S(pstNvPerfFreq, sizeof(CSS_NV_PREF_MCC_STRU), 0, sizeof(CSS_NV_PREF_MCC_STRU));

    ulRslt = CSS_NV_Read(   EN_NV_ID_PS_CLOUD_PREFER_FREQ_MCC1,
                            (VOS_VOID *)(pstNvPerfFreq),
                            ulDataLen);
    if(CSS_RESULT_SUCC == ulRslt)
    {
        CSS_INFO_LOG("CSS_ReadNvCloudPrefArfcn: read NV1 SUCC.");
        TLPS_PRINT2LAYER_INFO(CSS_ReadNvCloudPrefArfcn_ENUM, LNAS_FUNCTION_LABEL1);
        CSS_AddNvOneMcc(pstNvPerfFreq, 0);
    }

    CSS_PrintLocalPrefFreqInfo();

    /* 读MCC2 */
    CSS_MEM_SET_S(pstNvPerfFreq, sizeof(CSS_NV_PREF_MCC_STRU), 0, sizeof(CSS_NV_PREF_MCC_STRU));

    ulRslt = CSS_NV_Read(   EN_NV_ID_PS_CLOUD_PREFER_FREQ_MCC2,
                            (VOS_VOID *)(pstNvPerfFreq),
                            ulDataLen);
    if(CSS_RESULT_SUCC == ulRslt)
    {
        CSS_INFO_LOG("CSS_ReadNvCloudPrefArfcn: read NV2 SUCC.");
        TLPS_PRINT2LAYER_INFO(CSS_ReadNvCloudPrefArfcn_ENUM, LNAS_FUNCTION_LABEL2);
        CSS_AddNvOneMcc(pstNvPerfFreq, 1);
    }

    CSS_PrintLocalPrefFreqInfo();

    /* 读MCC3 */
    CSS_MEM_SET_S(pstNvPerfFreq, sizeof(CSS_NV_PREF_MCC_STRU), 0, sizeof(CSS_NV_PREF_MCC_STRU));

    ulRslt = CSS_NV_Read(   EN_NV_ID_PS_CLOUD_PREFER_FREQ_MCC3,
                            (VOS_VOID *)(pstNvPerfFreq),
                            ulDataLen);
    if(CSS_RESULT_SUCC == ulRslt)
    {
        CSS_INFO_LOG("CSS_ReadNvCloudPrefArfcn: read NV3 SUCC.");
        TLPS_PRINT2LAYER_INFO(CSS_ReadNvCloudPrefArfcn_ENUM, LNAS_FUNCTION_LABEL3);
        CSS_AddNvOneMcc(pstNvPerfFreq, 2);
    }

    CSS_PrintLocalPrefFreqInfo();

    CSS_MEM_FREE(pstNvPerfFreq);

    return;
}


/*****************************************************************************
 Function Name   : CSS_AddNvRatSupport
 Description     : 将制式的支持加入freq节点中
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddNvRatSupport(VOS_UINT8 *pucRatSupport, CSS_RAT_TYPE_ENUM_UINT8 ucRat)
{
    VOS_UINT8                           ucRatFlagTmp = *pucRatSupport;
    /* 制式不支持，则把该制式加入 */
    if (CSS_FALSE == CSS_IsRatSupportInFlag(ucRat, ucRatFlagTmp))
    {
        if (CSS_RAT_GSM == ucRat)
        {
            ucRatFlagTmp |= CSS_GSM_SUPORT_OP;
        }
        if (CSS_RAT_UMTS_FDD== ucRat)
        {
            ucRatFlagTmp |= CSS_WCDMA_SUPORT_OP;
        }
        if (CSS_RAT_LTE == ucRat)
        {
            ucRatFlagTmp |= CSS_LTE_SUPORT_OP;
        }
    }
    *pucRatSupport = ucRatFlagTmp;
}



/*****************************************************************************
 Function Name   : CSS_AddNvOneFreq
 Description     : 将NV中一个预置频点加入到内存中BAND结构中
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddNvOneFreq(CSS_PUB_PREF_BAND_STRU *pstBand, CSS_NV_PREF_ARFCN_STRU *pNvFreq, CSS_RAT_TYPE_ENUM_UINT8 ucRat)
{
    CSS_PUB_PREF_FREQ_STRU             *pstFreqNode;

    pstFreqNode = pstBand->pstFreqHead;
    /* 循环遍历，看看频点是否已存在 */
    while (CSS_NULL_PTR != pstFreqNode)
    {
        if ((pNvFreq->ulArfcnBegin == pstFreqNode->ulFreqBegin)
             && (pNvFreq->ulArfcnEnd == pstFreqNode->ulFreqEnd))
        {
            CSS_AddNvRatSupport(&(pstFreqNode->ucRatSupport), ucRat);
            return;
        }
        pstFreqNode = pstFreqNode->pstNext;
    }

    /* 如果频点没有，则新申请节点加入 */
    pstFreqNode = (CSS_PUB_PREF_FREQ_STRU*)CSS_AllocCloudPreferNodeAndClearFullMemory(sizeof(CSS_PUB_PREF_FREQ_STRU));
    if (CSS_NULL_PTR == pstFreqNode)
    {
        return;
    }

    CSS_MEM_SET_S(pstFreqNode, sizeof(CSS_PUB_PREF_FREQ_STRU), 0, sizeof(CSS_PUB_PREF_FREQ_STRU));

    /* 赋值频点 */
    if (pNvFreq->ulArfcnBegin > pNvFreq->ulArfcnEnd)
    {
        pstFreqNode->ulFreqBegin  = pNvFreq->ulArfcnEnd;
        pstFreqNode->ulFreqEnd    = pNvFreq->ulArfcnBegin;
    }
    else
    {
        pstFreqNode->ulFreqBegin = pNvFreq->ulArfcnBegin;
        pstFreqNode->ulFreqEnd   = pNvFreq->ulArfcnEnd;
    }

    CSS_AddNvRatSupport(&(pstFreqNode->ucRatSupport), ucRat);

    /*往末尾添加节点*/
    if (CSS_NULL_PTR == pstBand->pstFreqHead)
    {
        pstBand->pstFreqHead          = pstFreqNode;
        pstBand->pstFreqTail          = pstFreqNode;
    }
    else
    {
        pstBand->pstFreqTail->pstNext = pstFreqNode;
        pstBand->pstFreqTail          = pstFreqNode;
    }
    pstBand->ucFreqNum++;
}


/*****************************************************************************
 Function Name   : CSS_AddNvOneBand
 Description     : 将NV中一个BAND的预置频点加入到内存中BAND结构中
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddNvOneBand(CSS_PUB_PREF_MNC_STRU *pstMnc, CSS_NV_PREF_MNC_STRU *pNvMnc)
{
    CSS_PUB_PREF_BAND_STRU             *pstBandNode;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           ucFreqNumTmp;

    ucFreqNumTmp = (pNvMnc->ucArfcnNum < CSS_NV_MAX_PREF_ARFCN_NUM) ? pNvMnc->ucArfcnNum : CSS_NV_MAX_PREF_ARFCN_NUM;

    pstBandNode = pstMnc->pstBandHead;

    /* 循环遍历，找到该BAND的节点指针 */
    while (CSS_NULL_PTR != pstBandNode)
    {
        if (pstBandNode->ucBandInd == pNvMnc->ucBandInd)
        {
            /* 如果freq个数为0，需要将制式支持加入BAND节点下 */
            if (0 == ucFreqNumTmp)
            {
                CSS_AddNvRatSupport(&(pstBandNode->ucRatSupport), (CSS_RAT_TYPE_ENUM_UINT8)(pNvMnc->bitRat));
            }
            /* 依次将各FREQ加入 */
            for (ulLoop = 0; ulLoop < ucFreqNumTmp; ++ulLoop)
            {
                CSS_AddNvOneFreq(pstBandNode, &(pNvMnc->astArfcn[ulLoop]), pNvMnc->bitRat);
            }
            return;
        }
        pstBandNode = pstBandNode->pstNext;
    }

    /* 若没有找到，则新增一个BAND节点 */
    pstBandNode = (CSS_PUB_PREF_BAND_STRU*)CSS_AllocCloudPreferNodeAndClearFullMemory(sizeof(CSS_PUB_PREF_BAND_STRU));
    if (CSS_NULL_PTR == pstBandNode)
    {
        return;
    }

    CSS_MEM_SET_S(pstBandNode, sizeof(CSS_PUB_PREF_BAND_STRU), 0, sizeof(CSS_PUB_PREF_BAND_STRU));

    pstBandNode->ucBandInd = pNvMnc->ucBandInd;

    /*往末尾添加节点*/
    if (CSS_NULL_PTR == pstMnc->pstBandHead)
    {
        pstMnc->pstBandHead          = pstBandNode;
        pstMnc->pstBandTail          = pstBandNode;
    }
    else
    {
        pstMnc->pstBandTail->pstNext = pstBandNode;
        pstMnc->pstBandTail          = pstBandNode;
    }

    /* 如果freq个数为0，需要将制式支持加入BAND节点下 */
    if (0 == ucFreqNumTmp)
    {
        CSS_AddNvRatSupport(&(pstBandNode->ucRatSupport), (CSS_RAT_TYPE_ENUM_UINT8)(pNvMnc->bitRat));
    }

    /* 依次将各FREQ加入 */
    for (ulLoop = 0; ulLoop < ucFreqNumTmp; ++ulLoop)
    {
        CSS_AddNvOneFreq(pstBandNode, &(pNvMnc->astArfcn[ulLoop]), pNvMnc->bitRat);
    }
    pstMnc->ucBandNum++;
}

/*****************************************************************************
 Function Name   : CSS_AddNvOneMnc
 Description     : 将NV中一个MNC的预置频点加入到内存中MNC结构中
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddNvOneMnc(CSS_PUB_PREF_MCC_STRU *pstMcc, CSS_NV_PREF_MNC_STRU *pstNvMnc)
{
    CSS_PUB_PREF_MNC_STRU              *pstMncNode;
    VOS_UINT8                           aucMnc[2] = {0};

    /* 获取MNC ID */
    CSS_ConvertMncDigitToSimMnc(pstNvMnc->bitMncDigit1, pstNvMnc->bitMncDigit2, pstNvMnc->bitMncDigit3, aucMnc);

    /* 循环遍历，找到该MNC的节点指针 */
    pstMncNode = pstMcc->pstMncHead;
    while (CSS_NULL_PTR != pstMncNode)
    {
        if (CSS_TRUE == CSS_isMncMatch(pstMncNode->aucMncId, aucMnc))
        {
            /* 将BAND加入 */
            CSS_AddNvOneBand(pstMncNode, pstNvMnc);
            return;
        }
        pstMncNode = pstMncNode->pstNext;
    }

    /* 若没有找到，则新增一个MNC节点 */
    pstMncNode = (CSS_PUB_PREF_MNC_STRU*)CSS_AllocCloudPreferNodeAndClearFullMemory(sizeof(CSS_PUB_PREF_MNC_STRU));
    if (CSS_NULL_PTR == pstMncNode)
    {
        return;
    }

    CSS_MEM_SET_S(pstMncNode, sizeof(CSS_PUB_PREF_MNC_STRU), 0, sizeof(CSS_PUB_PREF_MNC_STRU));

    /* 给MNC节点内容赋值 */
    pstMncNode->aucMncId[0] = aucMnc[0];
    pstMncNode->aucMncId[1] = aucMnc[1];

    /*往末尾添加节点*/
    if (CSS_NULL_PTR == pstMcc->pstMncHead)
    {
        pstMcc->pstMncHead          = pstMncNode;
        pstMcc->pstMncTail          = pstMncNode;
    }
    else
    {
        pstMcc->pstMncTail->pstNext = pstMncNode;
        pstMcc->pstMncTail          = pstMncNode;
    }
    /* 依次将BAND加入 */
    CSS_AddNvOneBand(pstMncNode, pstNvMnc);
    pstMcc->ucMncNum++;
}


/*****************************************************************************
 Function Name   : CSS_AddNvOneMcc
 Description     : 将NV中一个国家的预置频点加入内存中
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
/*lint -e429*/
VOS_VOID CSS_AddNvOneMcc(CSS_NV_PREF_MCC_STRU *pPrefMcc, VOS_UINT32 ulIndex)
{
    CSS_PUB_PREF_MCC_STRU              *pstMccNode;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           aucMcc[2] = {0};
    CSS_CLOUD_PUB_CONTROL_STRU         *pContrl = CSS_GetCloudContrlAddr();
    VOS_UINT16                          usMncNumTmp;


    /* 若指针为空则返回 */
    if (CSS_NULL_PTR == pPrefMcc)
    {
        return;
    }

    /* MCC无效则返回 */
    if ((0x0F == pPrefMcc->bitMccDigit1)
        || (0 == pPrefMcc->bitMccDigit1 && 0 == pPrefMcc->bitMccDigit2))
    {
        return;
    }

    /* 获取MCC ID */
    CSS_ConvertMccDigitToSimMcc(pPrefMcc->bitMccDigit1, pPrefMcc->bitMccDigit2, pPrefMcc->bitMccDigit3, aucMcc);

    usMncNumTmp = (pPrefMcc->usMncNum < CSS_NV_MAX_PREF_MNC_NUM) ? pPrefMcc->usMncNum : CSS_NV_MAX_PREF_MNC_NUM;

    /* 读取到的MCC ID保存在内存中 */
    pContrl->astNvMcc[ulIndex].aucMccId[0] = aucMcc[0];
    pContrl->astNvMcc[ulIndex].aucMccId[1] = aucMcc[1];

    /* 循环遍历，找到该MCC的节点指针 */
    pstMccNode = CSS_GetPrefMccHeadNode();
    while (CSS_NULL_PTR != pstMccNode)
    {
        if (CSS_TRUE == CSS_isMccMatch(pstMccNode->aucMccId, aucMcc))
        {
            /* 依次将各MNC加入 */
            for (ulLoop = 0; ulLoop < usMncNumTmp; ++ulLoop)
            {
                CSS_AddNvOneMnc(pstMccNode, &(pPrefMcc->astMnc[ulLoop]));
            }
            return;
        }
        pstMccNode = pstMccNode->pstNext;
    }

    /* 若没有找到，则新增一个MCC节点 */
    pstMccNode = (CSS_PUB_PREF_MCC_STRU*)CSS_AllocCloudPreferNodeAndClearFullMemory(sizeof(CSS_PUB_PREF_MCC_STRU));
    if (CSS_NULL_PTR == pstMccNode)
    {
        return;
    }

    CSS_MEM_SET_S(pstMccNode, sizeof(CSS_PUB_PREF_MCC_STRU), 0, sizeof(CSS_PUB_PREF_MCC_STRU));

    /* 给MCC节点内容赋值 */
    pstMccNode->aucMccId[0] = aucMcc[0];
    pstMccNode->aucMccId[1] = aucMcc[1];

    /*往末尾添加节点*/
    if (CSS_NULL_PTR == CSS_GetPrefMccHeadNode())
    {
        CSS_GetPrefMccHeadNode()          = pstMccNode;
        CSS_GetPrefMccTailNode()          = pstMccNode;
    }
    else
    {
        CSS_GetPrefMccTailNode()->pstNext = pstMccNode;
        CSS_GetPrefMccTailNode()          = pstMccNode;
    }

    /* 依次将各MNC加入 */
    for (ulLoop = 0; ulLoop < usMncNumTmp; ++ulLoop)
    {
        CSS_AddNvOneMnc(pstMccNode, &(pPrefMcc->astMnc[ulLoop]));
    }
    CSS_GetPrefMccNodeNum() ++;
}
/*lint +e429*/


VOS_UINT32 CSS_UpdateOneMcc(CSS_MCC_UPDATE_STRU *pMccUpdate, VOS_UINT8 aucMcc[2])
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < pMccUpdate->usMccNum; ++ulLoop)
    {
        if (CSS_TRUE == CSS_isMccMatch(aucMcc, pMccUpdate->astMcc[ulLoop].aucMccId))
        {
            pMccUpdate->aucUpdated[ulLoop] = CSS_TRUE;
            return CSS_TRUE;
        }
    }

    return CSS_FALSE;
}


VOS_UINT32 CSS_IsAllMccUpdated(CSS_MCC_UPDATE_STRU *pMccUpdate)
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < pMccUpdate->usMccNum; ++ulLoop)
    {
        if (CSS_FALSE == pMccUpdate->aucUpdated[ulLoop])
        {
            return CSS_FALSE;
        }
    }
    return CSS_TRUE;
}



VOS_UINT32 CSS_IsMmcOrAsUpdating(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    CSS_CLOUD_PUB_CONTROL_STRU         *pCloudContrl;

    pCloudContrl = CSS_GetCloudContrlAddr();

    for (ulLoop = 0; ulLoop < CSS_MAX_PID_NUM; ++ulLoop)
    {
        if (CSS_TRUE == pCloudContrl->astMccUpdate[ulLoop].ucIsUpdating)
        {
            return CSS_TRUE;
        }
    }
    return CSS_FALSE;
}



VOS_VOID CSS_GetMccListFromLocal
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_MEMORY_PERF_MCC_NUM],
    VOS_UINT32                         *pulMccNum
)
{
    CSS_PUB_PREF_MCC_STRU              *pMccNode;
    VOS_UINT32                          ulNum = 0;

    /* 从头结点开始遍历 */
    pMccNode = CSS_GetPrefMccHeadNode();
    while (CSS_NULL_PTR != pMccNode && ulNum < CSS_MAX_MEMORY_PERF_MCC_NUM)
    {
        astMccID[ulNum].aucMccId[0] = pMccNode->aucMccId[0];
        astMccID[ulNum].aucMccId[1] = pMccNode->aucMccId[1];
        ulNum++;
        pMccNode = pMccNode->pstNext;
    }
    *pulMccNum = ulNum;
}


/*****************************************************************************
 Function Name   : CSS_GetMccListFromLocal
 Description     : 判断某个MCC的云端预置频点和频段是否已经获取。
                   考虑云通信数据可能不全，即使获取过MCC的预置频点和频段，也有可能没有某些PLMN ID的预置频点
 Input           : ulPlmnNum      :MCC ID个数
                   astPlmn        :MCC ID列表，MNC填0xFF，表示MNC无效
 Output          :
 Return          : VOS_TRUE       :全部已获取
                   VOS_FALSE      :没有全部获取

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsMccFreqExist
(
    VOS_UINT32                                    ulPlmnNum,
    CSS_PLMN_ID_STRU                              astPlmn[CSS_MAX_PLMN_ID_NUM]
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           aucMcc[2] = {0};

    /* 合法性检测 */
    if (ulPlmnNum > CSS_MAX_PLMN_ID_NUM
        || CSS_NULL_PTR == astPlmn)
    {
        return VOS_FALSE;
    }

    /* 如果云通信特性不使用，直接返回成功 */
    if (CSS_FALSE == CSS_IsCloudStrategyEnable())
    {
        CSS_INFO_LOG("CSS_IsMccFreqExist: cloud strategy is not enabled");
        TLPS_PRINT2LAYER_INFO(CSS_IsMccFreqExist_ENUM, LNAS_FUNCTION_LABEL1);
        return VOS_TRUE;
    }

    /* 如果不从云端获取，也直接返回RSP成功 */
    if (CSS_FALSE == CSS_IsPrefFreqEnable())
    {
        CSS_INFO_LOG("CSS_IsMccFreqExist: cloud pref freq is not enabled");
        TLPS_PRINT2LAYER_INFO(CSS_IsMccFreqExist_ENUM, LNAS_FUNCTION_LABEL2);
        return VOS_TRUE;
    }

    /* 遍历所有MCC，看看是否本地是否已有该MCC数据 */
    for (ulLoop = 0; ulLoop < ulPlmnNum; ++ulLoop)
    {

        /* 转换MCC存储格式 */
        CSS_ConvertGuMccToSimMcc(astPlmn[ulLoop].ulMcc, aucMcc);

        /* 如果没有从云端更新过，则返回FALSE */
        if (CSS_FALSE == CSS_IsMccUpdatedFromAp(aucMcc))
        {
            /* Log */
            TLPS_PRINT2LAYER_INFO2(CSS_IsMccFreqExist_ENUM, LNAS_FUNCTION_LABEL3, astPlmn[ulLoop].ulMcc, astPlmn[ulLoop].ulMnc);

            return VOS_FALSE;
        }
    }
    return VOS_TRUE;
}



VOS_VOID CSS_GetPrefFreqFromBandNode
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PUB_PREF_BAND_STRU             *pBandNode,
    VOS_UINT32                         *pulOutNum,
    CSS_PREF_FREQ_INFO_STRU            *pstOut
)
{
    CSS_PUB_PREF_FREQ_STRU             *pFreqNode;
    VOS_UINT32                          ulNum = *pulOutNum;
    VOS_UINT8                           ucIsExist;
    VOS_UINT32                          i;

    pFreqNode = pBandNode->pstFreqHead;
    /* 循环遍历所有FREQ，如果支持制式则将频点加入 */
    while (CSS_NULL_PTR != pFreqNode)
    {
        if ((CSS_RAT_GSM == enRat && CSS_FALSE != (pFreqNode->ucRatSupport & CSS_GSM_SUPORT_OP))
             || (CSS_RAT_UMTS_FDD== enRat && CSS_FALSE != (pFreqNode->ucRatSupport & CSS_WCDMA_SUPORT_OP))
             || (CSS_RAT_LTE == enRat && CSS_FALSE != (pFreqNode->ucRatSupport & CSS_LTE_SUPORT_OP)))
        {
            /* 已达最大个数 */
            if (ulNum >= CSS_MAX_PREF_FREQ_NUM)
            {
                *pulOutNum = ulNum;
                return;
            }

            /* 判断重复 */
            ucIsExist = CSS_FALSE;
            for (i = 0; i < ulNum; ++i)
            {
                if ((pBandNode->ucBandInd == pstOut->astFreq[i].enBand)
                    && (pFreqNode->ulFreqBegin == pstOut->astFreq[i].ulFreqBegin)
                    && (pFreqNode->ulFreqEnd == pstOut->astFreq[i].ulFreqEnd))
                {
                    ucIsExist = CSS_TRUE;
                    break;
                }
            }
            if (CSS_FALSE == ucIsExist)
            {
                pstOut->astFreq[ulNum].enBand       = pBandNode->ucBandInd;
                pstOut->astFreq[ulNum].ulFreqBegin  = pFreqNode->ulFreqBegin;
                pstOut->astFreq[ulNum].ulFreqEnd    = pFreqNode->ulFreqEnd;
                ulNum++;
            }
        }

        pFreqNode = pFreqNode->pstNext;
    }
    *pulOutNum = ulNum;
}



VOS_VOID CSS_GetPrefFreqFromMncNode
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PUB_PREF_MNC_STRU              *pMncNode,
    VOS_UINT32                         *pulOutNum,
    CSS_PREF_FREQ_INFO_STRU            *pstOut
)
{
    CSS_PUB_PREF_BAND_STRU             *pBandNode;

    pBandNode = pMncNode->pstBandHead;
    /* 循环遍历所有BAND，依次将频点加入 */
    while (CSS_NULL_PTR != pBandNode)
    {
        CSS_GetPrefFreqFromBandNode(enRat, pBandNode, pulOutNum, pstOut);

        pBandNode = pBandNode->pstNext;
    }
}




VOS_VOID CSS_GetPrefFreqFromMccNode
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PLMN_ID_STRU                   *pstPlmn,
    CSS_PUB_PREF_MCC_STRU              *pMccNode,
    CSS_PREF_FREQ_INFO_STRU            *pstOut
)
{
    CSS_PUB_PREF_MNC_STRU              *pMncNode;
    VOS_UINT32                          ulFreqNum = 0;
    NAS_MML_PLMN_ID_STRU                stBccPlmnId = {0};
    NAS_MML_PLMN_ID_STRU                stSimPlmnId = {0};


    CSS_ConvertSimMccToGuMcc(pMccNode->aucMccId, &(stBccPlmnId.ulMcc));
    stSimPlmnId.ulMcc = pstPlmn->ulMcc;
    stSimPlmnId.ulMnc = pstPlmn->ulMnc;

    pMncNode = pMccNode->pstMncHead;
    while (CSS_NULL_PTR != pMncNode)
    {
        /* 如果MNC有效，表示获取该MNC的预置频点 */
        if (CSS_INVALID_MNC != pstPlmn->ulMnc)
        {
            CSS_ConvertSimMncToGuMnc(pMncNode->aucMncId, &(stBccPlmnId.ulMnc));

            /* 如果MNC匹配 */
            if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stBccPlmnId, &stSimPlmnId))
            {
                CSS_GetPrefFreqFromMncNode(enRat, pMncNode, &ulFreqNum, pstOut);
                break;
            }
        }
        else
        {
            CSS_GetPrefFreqFromMncNode(enRat, pMncNode, &ulFreqNum, pstOut);
        }
        pMncNode = pMncNode->pstNext;
    }

    /* 赋值参数 */
    pstOut->ulFreqNum    = ulFreqNum;
}



CSS_RESULT_ENUM_UINT32 CSS_GetPreferFreqInfo
(
    CSS_RAT_TYPE_ENUM_UINT8                       enRat,
    VOS_UINT32                                    ulPlmnIdNum,
    CSS_PLMN_ID_STRU                              astPlmn[CSS_MAX_PREF_PLMN_NUM],
    VOS_UINT32                                   *pulOutPlmnNum,
    CSS_PREF_FREQ_INFO_STRU                       astPrefFreq[CSS_MAX_PREF_PLMN_NUM]
)
{
    VOS_UINT32                          ulLoop;
    CSS_PUB_PREF_MCC_STRU              *pMccNode;
    VOS_UINT8                           aucMcc[2] = {0};
    VOS_UINT32                          ulTmpNum;
    CSS_PLMN_ID_STRU                    astTmpPlmn[CSS_MAX_PREF_PLMN_NUM] = {{0}};

    TLPS_PRINT2LAYER_INFO1(CSS_GetPreferFreqInfo_ENUM, LNAS_ENTRY, enRat);

    /* 合法性检测 */
    if (ulPlmnIdNum > CSS_MAX_PREF_PLMN_NUM
        || CSS_NULL_PTR == astPlmn
        || CSS_NULL_PTR == pulOutPlmnNum
        || CSS_NULL_PTR == astPrefFreq)
    {
        TLPS_PRINT2LAYER_INFO(CSS_GetPreferFreqInfo_ENUM, LNAS_NULL_PTR);
        return CSS_RESULT_FAIL;
    }

    /* 如果云通信特性不使用，直接返回操作失败 */
    if (CSS_FALSE == CSS_IsCloudStrategyEnable())
    {
        TLPS_PRINT2LAYER_INFO(CSS_GetPreferFreqInfo_ENUM, LNAS_FUNCTION_LABEL1);
        return CSS_RESULT_FAIL;
    }

    /* log 打印 */
    for (ulLoop = 0; ulLoop < ulPlmnIdNum; ++ulLoop)
    {
        TLPS_PRINT2LAYER_INFO2(CSS_GetPreferFreqInfo_ENUM, LNAS_FUNCTION_LABEL2, astPlmn[ulLoop].ulMcc, astPlmn[ulLoop].ulMnc);
    }

    /* 如果某个MCC属于多MCC国家，则将该国家所有MCC加入 */
    CSS_GetAllMccBelongToOneCountry(ulPlmnIdNum, astPlmn, &ulTmpNum, astTmpPlmn);
    *pulOutPlmnNum = ulTmpNum;

    /* log 打印 */
    for (ulLoop = 0; ulLoop < ulTmpNum; ++ulLoop)
    {
        TLPS_PRINT2LAYER_INFO2(CSS_GetPreferFreqInfo_ENUM, LNAS_FUNCTION_LABEL3, astTmpPlmn[ulLoop].ulMcc, astTmpPlmn[ulLoop].ulMnc);
    }

    for (ulLoop = 0; ulLoop < ulTmpNum; ++ulLoop)
    {
        /* 先给个数赋初值 */
        astPrefFreq[ulLoop].ulFreqNum = 0;

        /* 取出MCC */
        CSS_ConvertGuMccToSimMcc(astTmpPlmn[ulLoop].ulMcc, aucMcc);

        /* 赋值MCC */
        astPrefFreq[ulLoop].stPlmn.ulMcc = astTmpPlmn[ulLoop].ulMcc;
        astPrefFreq[ulLoop].stPlmn.ulMnc = astTmpPlmn[ulLoop].ulMnc;

        pMccNode = CSS_GetPrefMccHeadNode();
        while (CSS_NULL_PTR != pMccNode)
        {
            /* 若MCC ID匹配，则将MCC下的MNC加入 */
            if (CSS_TRUE == CSS_isMccMatch(pMccNode->aucMccId, aucMcc))
            {
                CSS_GetPrefFreqFromMccNode(enRat, &(astTmpPlmn[ulLoop]), pMccNode, &(astPrefFreq[ulLoop]));
            }
            pMccNode = pMccNode->pstNext;
        }
    }

    /* 消息勾出 */
    for (ulLoop = 0; ulLoop < ulTmpNum; ++ulLoop)
    {
        CSS_SendOmGetOnePlmnPrefFreqRslt(enRat, ulPlmnIdNum, astPlmn, CSS_RESULT_SUCC, &(astPrefFreq[ulLoop]));
    }
    return CSS_RESULT_SUCC;
}



VOS_UINT32 CSS_IsBandNodeSupportRat
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PUB_PREF_BAND_STRU             *pBandNode
)
{
    CSS_PUB_PREF_FREQ_STRU             *pFreqNode;

    /* 先判断BAND指针中的制式支持 */
    if ((CSS_RAT_GSM == enRat && CSS_FALSE != (pBandNode->ucRatSupport & CSS_GSM_SUPORT_OP))
         || (CSS_RAT_UMTS_FDD== enRat && CSS_FALSE != (pBandNode->ucRatSupport & CSS_WCDMA_SUPORT_OP))
         || (CSS_RAT_LTE == enRat && CSS_FALSE != (pBandNode->ucRatSupport & CSS_LTE_SUPORT_OP)))
    {
        return CSS_TRUE;
    }

    /* 如果FREQ个数不为0，则遍历每个FREQ，来判断是否支持 */
    pFreqNode = pBandNode->pstFreqHead;
    while (CSS_NULL_PTR != pFreqNode)
    {
        if ((CSS_RAT_GSM == enRat && CSS_FALSE != (pFreqNode->ucRatSupport & CSS_GSM_SUPORT_OP))
             || (CSS_RAT_UMTS_FDD== enRat && CSS_FALSE != (pFreqNode->ucRatSupport & CSS_WCDMA_SUPORT_OP))
             || (CSS_RAT_LTE == enRat && CSS_FALSE != (pFreqNode->ucRatSupport & CSS_LTE_SUPORT_OP)))
        {
            return CSS_TRUE;
        }

        pFreqNode = pFreqNode->pstNext;
    }
    return CSS_FALSE;
}




VOS_VOID CSS_GetPrefBandFromMncNode
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PUB_PREF_MNC_STRU              *pMncNode,
    VOS_UINT32                         *pulOutNum,
    CSS_PREF_BAND_INFO_STRU            *pstOut
)
{
    CSS_PUB_PREF_BAND_STRU             *pBandNode;
    VOS_UINT32                          ulBandNum = *pulOutNum;
    VOS_UINT8                           ucIsExist;
    VOS_UINT32                          i;

    pBandNode = pMncNode->pstBandHead;
    while (CSS_NULL_PTR != pBandNode)
    {
        if (CSS_TRUE == CSS_IsBandNodeSupportRat(enRat, pBandNode))
        {
            /* 已达最大个数 */
            if (ulBandNum >= CSS_MAX_PREF_BAND_NUM)
            {
                *pulOutNum = ulBandNum;
                return;
            }
            /* 判断重复 */
            ucIsExist = CSS_FALSE;
            for (i = 0; i < ulBandNum; ++i)
            {
                if (pBandNode->ucBandInd == pstOut->ausBand[i])
                {
                    ucIsExist = CSS_TRUE;
                    break;
                }
            }
            if (CSS_FALSE == ucIsExist)
            {
                pstOut->ausBand[ulBandNum] = pBandNode->ucBandInd;
                ulBandNum++;
            }
        }

        pBandNode = pBandNode->pstNext;
    }
    *pulOutNum = ulBandNum;
}

/*****************************************************************************
 Function Name   : CSS_IsRatHasNoPrefBand
 Description     : 判断某个制式的PLMN下是否没有云端BAND
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsRatHasNoPrefBand
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PUB_PREF_MNC_STRU              *pMncNode
)
{
    return CSS_IsRatSupportInFlag(enRat, pMncNode->ucNoPrefBandFlg);
}

/*****************************************************************************
 Function Name   : CSS_JudgeMultiMccCountryHasPrefBand
 Description     : 判断某个制式的PLMN下是否没有云端BAND,将个数为0的MCC删除，不为0的数据保留
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_JudgeMultiMccCountryHasPrefBand
(
    VOS_UINT32                         *pulNum,
    CSS_PREF_BAND_INFO_STRU             astPrefBand[CSS_MAX_PREF_PLMN_NUM],
    VOS_UINT32                          aulResult[CSS_MAX_PREF_PLMN_NUM]
)
{
    VOS_UINT32                          i,j;
    VOS_UINT8                           ucIsMccHasData;
    VOS_UINT8                           ucDeleteFlag[CSS_MAX_PREF_PLMN_NUM] = {0};
    VOS_UINT32                          ulNumCopy;
    CSS_PREF_BAND_INFO_STRU             *pastPrefBandCopy;

    pastPrefBandCopy = CSS_MEM_ALLOC(sizeof(CSS_PREF_BAND_INFO_STRU)*CSS_MAX_PREF_PLMN_NUM);
    if (CSS_NULL_PTR == pastPrefBandCopy)
    {
        return CSS_FAIL;
    }

    /* 拷贝原始数据 */
    ulNumCopy = *pulNum;

    CSS_MEM_CPY_S(  pastPrefBandCopy,
                    sizeof(CSS_PREF_BAND_INFO_STRU)*CSS_MAX_PREF_PLMN_NUM,
                    astPrefBand,
                    sizeof(CSS_PREF_BAND_INFO_STRU)*CSS_MAX_PREF_PLMN_NUM);

    /* 原始数据清空，后面会重新赋值 */
    *pulNum = 0;

    CSS_MEM_SET_S(  astPrefBand,
                    sizeof(CSS_PREF_BAND_INFO_STRU)*CSS_MAX_PREF_PLMN_NUM,
                    0,
                    sizeof(CSS_PREF_BAND_INFO_STRU)*CSS_MAX_PREF_PLMN_NUM);

    TLPS_PRINT2LAYER_INFO(CSS_JudgeMultiMccCountryHasPrefBand_ENUM, LNAS_ENTRY);

    /* 对数据中的MCC两两比较，如果二者属于同一个国家，并且其中一个MCC预置BAND个数为0，另一个不为0，则将为0的mCC删掉，返回成功 */
    for (i = 0; i < ulNumCopy; ++i)
    {
        if (CSS_FAIL == aulResult[i])
        {
            TLPS_PRINT2LAYER_INFO1(CSS_JudgeMultiMccCountryHasPrefBand_ENUM, LNAS_CSS_GetPrefBandFromMccNodeFail,CSS_FAIL);
            /* 如果是基于PLMN获取的直接返回失败 */
            if (CSS_INVALID_MNC != pastPrefBandCopy[i].stPlmn.ulMnc)
            {
                TLPS_PRINT2LAYER_INFO(CSS_JudgeMultiMccCountryHasPrefBand_ENUM, LNAS_CSS_GetPrefBandInfoFailAndPlmnWithInvalidMnc);
                CSS_MEM_FREE(pastPrefBandCopy);
                return CSS_FAIL;
            }

            /* 先把单MCC国家提出来 */
            if (CSS_FALSE == CSS_IsMccBelongToMultiCountry(pastPrefBandCopy[i].stPlmn.ulMcc))
            {
                TLPS_PRINT2LAYER_INFO1(CSS_JudgeMultiMccCountryHasPrefBand_ENUM, LNAS_CSS_GetPrefBandInfoFailAndMccNotBelongToMultiCountry,pastPrefBandCopy[i].stPlmn.ulMcc);
                CSS_MEM_FREE(pastPrefBandCopy);
                return CSS_FAIL;
            }


            /* 处理多MCC国家的MCC */
            ucIsMccHasData = CSS_FALSE;
            for(j = 0; j < ulNumCopy; ++j)
            {
                /* 二者属于同一国家，并且其中一个MCC的预置BAND不为0 */
                if ((CSS_TRUE == CSS_IsTwoMccBelongToOneCountry(pastPrefBandCopy[i].stPlmn.ulMcc, pastPrefBandCopy[j].stPlmn.ulMcc))
                     && (CSS_SUCC == aulResult[j]))
                {
                    ucDeleteFlag[i] = CSS_TRUE;
                    ucIsMccHasData = CSS_TRUE;
                    TLPS_PRINT2LAYER_INFO(CSS_JudgeMultiMccCountryHasPrefBand_ENUM, LNAS_CSS_TwoMccBelongToOneCountry);
                    break;
                }
            }
            if (CSS_FALSE == ucIsMccHasData)
            {
                TLPS_PRINT2LAYER_INFO(CSS_JudgeMultiMccCountryHasPrefBand_ENUM, LNAS_CSS_GetNoPrefBandInfoFromOtherMccBelongToOneCountry);
                CSS_MEM_FREE(pastPrefBandCopy);
                return CSS_FAIL;
            }
        }
    }

    /* 将flag置为1的MCC剔除，其他的MCC加入结果列表中 */
    for (i = 0; i < ulNumCopy; ++i)
    {
        if (CSS_TRUE != ucDeleteFlag[i])
        {
            CSS_MEM_CPY_S(  &(astPrefBand[*pulNum]),
                            sizeof(CSS_PREF_BAND_INFO_STRU),
                            &(pastPrefBandCopy[i]),
                            sizeof(CSS_PREF_BAND_INFO_STRU));

            (*pulNum)++;
            TLPS_PRINT2LAYER_INFO(CSS_JudgeMultiMccCountryHasPrefBand_ENUM, LNAS_CSS_SaveBandInfoForGetResult);
        }
    }

    /* 异常保护 */
    if (0 == *pulNum)
    {
        TLPS_PRINT2LAYER_INFO(CSS_JudgeMultiMccCountryHasPrefBand_ENUM, LNAS_CSS_GetPreferBandInfoFail);
        CSS_MEM_FREE(pastPrefBandCopy);
        return CSS_FAIL;
    }

    /* 当所有PLMN或MCC都没有数据时，个数置为0，返回成功 */
    ucIsMccHasData = CSS_FALSE;
    for (i = 0; i < *pulNum; ++i)
    {
        if (0 != astPrefBand[i].ulBandNum)
        {
            ucIsMccHasData = CSS_TRUE;
            break;
        }
    }
    if (CSS_FALSE == ucIsMccHasData)
    {
        *pulNum = 0;
    }
    TLPS_PRINT2LAYER_INFO(CSS_JudgeMultiMccCountryHasPrefBand_ENUM, LNAS_CSS_GetPreferBandInfoSucc);
    CSS_MEM_FREE(pastPrefBandCopy);
    return CSS_SUCC;
}


VOS_UINT32 CSS_GetPrefBandFromMccNode
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PLMN_ID_STRU                   *pstPlmn,
    CSS_PUB_PREF_MCC_STRU              *pMccNode,
    CSS_PREF_BAND_INFO_STRU            *pstOut
)
{
    CSS_PUB_PREF_MNC_STRU              *pMncNode;
    VOS_UINT32                          ulBandNum = 0;
    VOS_UINT8                           ucExistPrefBand = CSS_FALSE;/* 是否有一个MNC没有被云端明确指明没有预置BAND */
    NAS_MML_PLMN_ID_STRU                stBccPlmnId = {0};
    NAS_MML_PLMN_ID_STRU                stSimPlmnId = {0};


    CSS_ConvertSimMccToGuMcc(pMccNode->aucMccId, &(stBccPlmnId.ulMcc));
    stSimPlmnId.ulMcc = pstPlmn->ulMcc;
    stSimPlmnId.ulMnc = pstPlmn->ulMnc;

    pMncNode = pMccNode->pstMncHead;
    if (CSS_NULL_PTR == pMncNode)
    {
        TLPS_PRINT2LAYER_INFO1(CSS_GetPrefBandFromMccNode_ENUM, LNAS_CSS_MncNodeNull, enRat);
        return CSS_FAIL;
    }

    while (CSS_NULL_PTR != pMncNode)
    {
        if (CSS_INVALID_MNC != pstPlmn->ulMnc)
        {
            CSS_ConvertSimMncToGuMnc(pMncNode->aucMncId, &(stBccPlmnId.ulMnc));

            /* 如果MNC匹配 */
            if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stBccPlmnId, &stSimPlmnId))
            {
                /* 如果云端明确没有预置BAND，则直接返回成功，并且个数为0 */
                if (CSS_TRUE == CSS_IsRatHasNoPrefBand(enRat, pMncNode))
                {
                    TLPS_PRINT2LAYER_INFO2(CSS_GetPrefBandFromMccNode_ENUM, LNAS_FUNCTION_LABEL1, pstPlmn->ulMcc, pstPlmn->ulMnc);
                    pstOut->ulBandNum    = 0;
                    return CSS_SUCC;
                }
                CSS_GetPrefBandFromMncNode(enRat, pMncNode, &ulBandNum, pstOut);
                break;
            }
        }
        else
        {
            /* 如果云端明确没有预置BAND，则不获取 */
            if (CSS_TRUE == CSS_IsRatHasNoPrefBand(enRat, pMncNode))
            {
                TLPS_PRINT2LAYER_INFO2(CSS_GetPrefBandFromMccNode_ENUM, LNAS_FUNCTION_LABEL2, pstPlmn->ulMcc, pstPlmn->ulMnc);
            }
            else
            {
                CSS_GetPrefBandFromMncNode(enRat, pMncNode, &ulBandNum, pstOut);
                ucExistPrefBand = CSS_TRUE;
            }
        }
        pMncNode = pMncNode->pstNext;
    }

    /* 当以MCC获取预置BAND时，若所有MNC都明确没有预置BAND，则返回成功，个数为0 */
    if ((CSS_INVALID_MNC == pstPlmn->ulMnc) && (CSS_FALSE == ucExistPrefBand))
    {
        TLPS_PRINT2LAYER_INFO2(CSS_GetPrefBandFromMccNode_ENUM, LNAS_FUNCTION_LABEL3, pstPlmn->ulMcc, pstPlmn->ulMnc);
        pstOut->ulBandNum    = 0;
        return CSS_SUCC;
    }

    pstOut->ulBandNum    = ulBandNum;
    if (0 == ulBandNum)
    {
        TLPS_PRINT2LAYER_INFO2(CSS_GetPrefBandFromMccNode_ENUM, LNAS_CSS_GetNoPrefBandWithPlmn, pstPlmn->ulMcc, pstPlmn->ulMnc);
        return CSS_FAIL;
    }
    TLPS_PRINT2LAYER_INFO2(CSS_GetPrefBandFromMccNode_ENUM, LNAS_CSS_GetPrefBandSuccWithPlmn, pstPlmn->ulMcc, pstPlmn->ulMnc);
    return CSS_SUCC;
}



CSS_RESULT_ENUM_UINT32 CSS_GetPreferBandInfo
(
    CSS_RAT_TYPE_ENUM_UINT8                       enRat,
    VOS_UINT32                                    ulPlmnIdNum,
    CSS_PLMN_ID_STRU                              astPlmn[CSS_MAX_PREF_PLMN_NUM],
    VOS_UINT32                                   *pulOutPlmnNum,
    CSS_PREF_BAND_INFO_STRU                       astPrefBand[CSS_MAX_PREF_PLMN_NUM]
)
{
    VOS_UINT32                          ulLoop;
    CSS_PUB_PREF_MCC_STRU              *pMccNode;
    VOS_UINT8                           aucMcc[2] = {0};
    VOS_UINT32                          ulTmpNum;
    CSS_PLMN_ID_STRU                    astTmpPlmn[CSS_MAX_PREF_PLMN_NUM] = {{0}};
    VOS_UINT8                           ucTmpNodeNum = 0;
    VOS_UINT32                          aulResult[CSS_MAX_PREF_PLMN_NUM] = {0};

    TLPS_PRINT2LAYER_INFO1(CSS_GetPreferBandInfo_ENUM, LNAS_ENTRY, enRat);

    /* 合法性检测 */
    if (ulPlmnIdNum > CSS_MAX_PREF_PLMN_NUM
        || CSS_NULL_PTR == astPlmn
        || CSS_NULL_PTR == pulOutPlmnNum
        || CSS_NULL_PTR == astPrefBand)
    {
        TLPS_PRINT2LAYER_INFO(CSS_GetPreferBandInfo_ENUM, LNAS_NULL_PTR);
        return CSS_RESULT_FAIL;
    }

    /* 如果云通信特性不使用，直接返回操作失败 */
    if (CSS_FALSE == CSS_IsCloudStrategyEnable())
    {
        TLPS_PRINT2LAYER_INFO(CSS_GetPreferBandInfo_ENUM, LNAS_FUNCTION_LABEL1);
        return CSS_RESULT_FAIL;
    }

    /* log 打印 */
    for (ulLoop = 0; ulLoop < ulPlmnIdNum; ++ulLoop)
    {
        TLPS_PRINT2LAYER_INFO2(CSS_GetPreferBandInfo_ENUM, LNAS_FUNCTION_LABEL2, astPlmn[ulLoop].ulMcc, astPlmn[ulLoop].ulMnc);
    }

    /* 如果某个MCC属于多MCC国家，则将该国家所有MCC加入 */
    CSS_GetAllMccBelongToOneCountry(ulPlmnIdNum, astPlmn, &ulTmpNum, astTmpPlmn);
    *pulOutPlmnNum = ulTmpNum;

    /* log 打印 */
    for (ulLoop = 0; ulLoop < ulTmpNum; ++ulLoop)
    {
        TLPS_PRINT2LAYER_INFO2(CSS_GetPreferBandInfo_ENUM, LNAS_FUNCTION_LABEL3, astTmpPlmn[ulLoop].ulMcc, astTmpPlmn[ulLoop].ulMnc);
    }

    for (ulLoop = 0; ulLoop < ulTmpNum; ++ulLoop)
    {
        /* 默认值为FAIL */
        aulResult[ulLoop] = CSS_FAIL;

        /* 先给个数赋初值 */
        astPrefBand[ulLoop].ulBandNum = 0;

        ucTmpNodeNum = 0;

        /* 取出MCC */
        CSS_ConvertGuMccToSimMcc(astTmpPlmn[ulLoop].ulMcc, aucMcc);

        /* 赋值MCC */
        astPrefBand[ulLoop].stPlmn.ulMcc = astTmpPlmn[ulLoop].ulMcc;
        astPrefBand[ulLoop].stPlmn.ulMnc = astTmpPlmn[ulLoop].ulMnc;

        /* 查找本地内存的所有节点 */
        pMccNode = CSS_GetPrefMccHeadNode();
        /* 理论上，接入层调用接口前肯定已经过获取云端数据了此时MCC个数不可能为0。如果个数为0则代表出异常了。
           出于风险考虑，应该返回失败让接入层进行全BAND搜*/
        if (CSS_NULL_PTR == pMccNode)
        {
            TLPS_PRINT2LAYER_INFO1(CSS_GetPreferBandInfo_ENUM, LNAS_FUNCTION_LABEL4, ulLoop);
            return CSS_RESULT_FAIL;
        }
        while (CSS_NULL_PTR != pMccNode)
        {
            if (CSS_TRUE == CSS_isMccMatch(pMccNode->aucMccId, aucMcc))
            {
                /* 将结果存入数组中 */
                aulResult[ulLoop] = CSS_GetPrefBandFromMccNode(enRat, &(astTmpPlmn[ulLoop]), pMccNode, &(astPrefBand[ulLoop]));
                TLPS_PRINT2LAYER_INFO2(CSS_GetPreferBandInfo_ENUM, LNAS_FUNCTION_LABEL5, ulLoop, aulResult[ulLoop]);
                TLPS_PRINT2LAYER_INFO1(CSS_GetPreferBandInfo_ENUM, LNAS_FUNCTION_LABEL5, ucTmpNodeNum);
                break;
            }
            pMccNode = pMccNode->pstNext;
            ucTmpNodeNum ++;
        }
    }

    if (CSS_FAIL == CSS_JudgeMultiMccCountryHasPrefBand(pulOutPlmnNum, astPrefBand, aulResult))
    {
        /* add */
        TLPS_PRINT2LAYER_INFO(CSS_GetPreferBandInfo_ENUM, LNAS_CSS_GetPreferBandInfoFail);
        /* add */
        CSS_SendOmGetPrefBandRslt(enRat,ulPlmnIdNum,astPlmn,aulResult,CSS_RESULT_FAIL,*pulOutPlmnNum, astPrefBand);
        return CSS_RESULT_FAIL;
    }

    CSS_SendOmGetPrefBandRslt(enRat,ulPlmnIdNum,astPlmn,aulResult,CSS_RESULT_SUCC,*pulOutPlmnNum, astPrefBand);

    return CSS_RESULT_SUCC;
}

/*****************************************************************************
 Function Name   : CSS_GetMccFromPlmnArr
 Description     : 从PLMN数组中找出MCC
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_GetMccFromPlmnArr
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                         *pulMccNum,
    const CSS_PLMN_ID_STRU              astPlmnId[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                          ulPlmnNum
)
{
    VOS_UINT32                          ulLoop1,ulLoop2;
    VOS_UINT32                          ulMccNum = 0;
    VOS_UINT32                          ulIsExist = CSS_FALSE;
    VOS_UINT8                           aucMcc[2] = {0};

    CSS_MEM_SET_S(astMccID, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM, 0, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);

    /* 遍历所有PLMN ID，加入数组中 */
    for (ulLoop1 = 0; ulLoop1 < ulPlmnNum; ++ulLoop1)
    {
        ulIsExist = CSS_FALSE;

        CSS_ConvertGuMccToSimMcc(astPlmnId[ulLoop1].ulMcc, aucMcc);

        /* 查看数组中是否已经存在 */
        for (ulLoop2 = 0; ulLoop2 < ulMccNum; ++ulLoop2)
        {
            if (CSS_TRUE == CSS_isMccMatch(aucMcc, astMccID[ulLoop2].aucMccId))
            {
                ulIsExist = CSS_TRUE;
                break;
            }
        }
        /* 不存在则加入 */
        if (CSS_FALSE == ulIsExist)
        {
            astMccID[ulMccNum].aucMccId[0] = aucMcc[0];
            astMccID[ulMccNum].aucMccId[1] = aucMcc[1];
            ulMccNum++;
        }
    }
    *pulMccNum = ulMccNum;
}

/*****************************************************************************
 Function Name   : CSS_IsMccUpdatedFromAp
 Description     : 查看某mCC是否从云端更新过
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsMccUpdatedFromAp(VOS_UINT8 aucMcc[2])
{
    VOS_UINT32                          i,j;
    VOS_UINT32                          ulTmpMcc;
    VOS_UINT8                           aucTmpMcc[2] = {0};

    if (CSS_TRUE == CSS_IsMccExistInLocal(aucMcc))
    {
        return CSS_TRUE;
    }

    /* sim卡格式转换为GU的格式 */
    CSS_ConvertSimMccToGuMcc(aucMcc, &ulTmpMcc);

    for (i = 0; i < CSS_MCC_COUNTY_NUM; ++i)
    {
        if (CSS_TRUE == CSS_IsMccBelongToCountry(ulTmpMcc, &(g_astCountryMccList[i])))
        {
            for (j = 0; j < g_astCountryMccList[i].ulMccNum; ++j)
            {
                /* gu格式转换为sim卡格式  */
                CSS_ConvertGuMccToSimMcc(g_astCountryMccList[i].pulMccListAddr[j], aucTmpMcc);

                if (CSS_TRUE == CSS_IsMccExistInLocal(aucTmpMcc))
                {
                    return CSS_TRUE;
                }
            }
        }

    }
    return CSS_FALSE;
}



VOS_VOID CSS_DeleteSameMccAccordToLocal
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                         *pulMccNum
)
{
    CSS_MCC_ID_STRU                     astMccIDCopy[CSS_MAX_PLMN_ID_NUM];
    VOS_UINT32                          ulNumCopy;
    VOS_UINT8                           ucExistFlag[CSS_MAX_PLMN_ID_NUM] = {0};
    VOS_UINT32                          ulLoop;

    CSS_MEM_SET_S(astMccIDCopy, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM, 0, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);

    /* 先将原始MCC列表做一份拷贝 */
    CSS_MEM_CPY_S(astMccIDCopy, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM,
                            astMccID, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);
    ulNumCopy = *pulMccNum;

    /* 将原始的MCC列表的内容清除，下面要开始赋值 */
    CSS_MEM_SET_S(astMccID, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM, 0, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);
    *pulMccNum = 0;

    /* 对拷贝进行循环遍历，查找本地是否存在该MCC的预置频点 */
    for (ulLoop = 0; ulLoop < ulNumCopy; ++ulLoop)
    {
        if (CSS_TRUE == CSS_IsMccUpdatedFromAp(astMccIDCopy[ulLoop].aucMccId))
        {
            /* 本地已更新过该MCC的预置频点，则将待剔除的FLAG置为TRUE */
            ucExistFlag[ulLoop] = CSS_TRUE;
        }
    }

    /* 将拷贝的MCC中FALG置为TRUE的剔除掉，加入到原始MCC列表中 */
    for (ulLoop = 0; ulLoop < ulNumCopy; ++ulLoop)
    {
        if (CSS_FALSE == ucExistFlag[ulLoop])
        {
            astMccID[*pulMccNum].aucMccId[0] = astMccIDCopy[ulLoop].aucMccId[0];
            astMccID[*pulMccNum].aucMccId[1] = astMccIDCopy[ulLoop].aucMccId[1];
            (*pulMccNum) += 1;
        }
    }
}

/*****************************************************************************
 Function Name   : CSS_IsMccUpdatingInUpdateStateTable
 Description     : 如果MCC正在等待云端下发则删除
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsMccUpdatingInUpdateStateTable
(
    VOS_UINT8                           aucMccID[2]
)
{
    VOS_UINT32                          ulLoop2;
    VOS_UINT32                          ulLoop3;
    CSS_MCC_UPDATE_STRU                *pstUpdate;
    CSS_CLOUD_PUB_CONTROL_STRU         *pCloudContrl = CSS_GetCloudContrlAddr();

    /* 对每个MMC和AS状态表遍历 */
    for (ulLoop2 = 0; ulLoop2 < CSS_MAX_PID_NUM; ++ulLoop2)
    {
        pstUpdate = &(pCloudContrl->astMccUpdate[ulLoop2]);
        /* 该状态表正在更新状态中 */
        if (CSS_TRUE == pstUpdate->ucIsUpdating)
        {
            /* 遍历该状态表的每个MCC，看是否与拷贝中的MCC一样 */
            for (ulLoop3 = 0; ulLoop3 < pstUpdate->usMccNum; ++ulLoop3)
            {
                if (CSS_TRUE == CSS_isMccMatch(aucMccID, pstUpdate->astMcc[ulLoop3].aucMccId))
                {
                    return CSS_TRUE;
                }
            }
        }
    }

    /* 若AP的更新正在进行中 */
    if (CSS_TRUE == pCloudContrl->stApMccUpdate.ucIsUpdating)
    {
        /* 遍历该状态表的每个MCC，看是否与拷贝中的MCC一样 */
        for (ulLoop2 = 0; ulLoop2 < pCloudContrl->stApMccUpdate.usMccNum; ++ulLoop2)
        {
            if (CSS_TRUE == CSS_isMccMatch(aucMccID, pCloudContrl->stApMccUpdate.astMcc[ulLoop2].aucMccId))
            {
                return CSS_TRUE;
            }
        }
    }
    return CSS_FALSE;
}


/*****************************************************************************
 Function Name   : CSS_DeleteMccAlreadySndToAp
 Description     : 如果MCC正在等待云端下发则删除
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_DeleteMccAlreadySndToAp
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                         *pulMccNum
)
{
    VOS_UINT32                          ulLoop1;
    CSS_MCC_ID_STRU                     astMccIDCopy[CSS_MAX_PLMN_ID_NUM];
    VOS_UINT32                          ulNumCopy;
    VOS_UINT8                           ucExistFlag[CSS_MAX_PLMN_ID_NUM] = {0};

    CSS_MEM_SET_S(astMccIDCopy, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM, 0, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);

    /* 先将原始MCC列表做一份拷贝 */
    CSS_MEM_CPY_S(astMccIDCopy, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM,
                                astMccID, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);
    ulNumCopy = *pulMccNum;
    /* 将原始的MCC列表的内容清除，下面要开始赋值 */
    CSS_MEM_SET_S(astMccID, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM,
                                0, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);
    *pulMccNum = 0;

    /* 对拷贝中的每个MCC判断，看看是否该MCC正在更新过程中 */
    for (ulLoop1 = 0; ulLoop1 < ulNumCopy; ++ulLoop1)
    {
        if (CSS_TRUE == CSS_IsMccUpdatingInUpdateStateTable(astMccIDCopy[ulLoop1].aucMccId))
        {
            /* 若正在更新，则将待剔除的FLAG置为TRUE */
            ucExistFlag[ulLoop1] = CSS_TRUE;
        }

    }

    /* 将拷贝的MCC中FALG置为TRUE的剔除掉，加入到原始MCC列表中 */
    for (ulLoop1 = 0; ulLoop1 < ulNumCopy; ++ulLoop1)
    {
        if (CSS_FALSE == ucExistFlag[ulLoop1])
        {
            astMccID[*pulMccNum].aucMccId[0] = astMccIDCopy[ulLoop1].aucMccId[0];
            astMccID[*pulMccNum].aucMccId[1] = astMccIDCopy[ulLoop1].aucMccId[1];
            (*pulMccNum) += 1;
        }
    }

}





/*****************************************************************************
 Function Name   : CSS_DeleteLocalMccFromMccArray
 Description     : 根据传入的数组删除本地的这些MCC
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_DeleteLocalMccFromMccArray
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                          ulMccNum
)
{
    CSS_PUB_PREF_MCC_STRU              *pstMccNode;
    CSS_PUB_PREF_MCC_STRU              *pstMccNodePre;
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < ulMccNum; ++ulLoop)
    {
        /* 循环找到内存中该MCC的节点 */
        pstMccNode = CSS_GetPrefMccHeadNode();
        pstMccNodePre = CSS_NULL_PTR;
        while (CSS_NULL_PTR != pstMccNode)
        {
            if (CSS_TRUE == CSS_isMccMatch(pstMccNode->aucMccId, astMccID[ulLoop].aucMccId))
            {
                CSS_DeleteAllMnc(pstMccNode);

                if (CSS_NULL_PTR == pstMccNodePre)
                {
                    CSS_GetPrefMccHeadNode() = pstMccNode->pstNext;
                }
                else
                {
                    pstMccNodePre->pstNext = pstMccNode->pstNext;
                }

                if (CSS_GetPrefMccTailNode() == pstMccNode)
                {
                    CSS_GetPrefMccTailNode() = pstMccNodePre;
                }
                CSS_FreeCloudPreferNode(pstMccNode);
                CSS_GetPrefMccNodeNum() --;
                pstMccNode = CSS_NULL_PTR;
                break;
            }
            pstMccNodePre = pstMccNode;
            pstMccNode = pstMccNode->pstNext;
        }
    }


}


/*****************************************************************************
 Function Name  : CSS_ReadFreqFromAtMsg
 Description    : 从码流中读取频点数据
 Input          : pstBand : BAND节点
                  pAddr   : 码流首地址
                  pulSum  : 地址偏移量
 Output         : pstBand : BAND节点
                  pulSum  : 地址偏移量
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_ReadFreqFromAtMsg(CSS_PUB_PREF_BAND_STRU *pstBand, VOS_UINT8 *pAddr, VOS_UINT32 *pulSum, VOS_UINT32 ulRemainLen)
{
    CSS_PUB_PREF_FREQ_STRU             *pstFreqNode;
    VOS_UINT8                           ucSupportFlag;
    VOS_UINT32                          ulFreqBegin;
    VOS_UINT32                          ulFreqEnd;
    VOS_UINT32                          ulSumTmp = 0;
    VOS_UINT32                          ulFreqTmp;

    if (ulRemainLen < CSS_SIZEOF_AT_FREQ_RANGE_STRU)
    {
        return CSS_FAIL;
    }

    /* 读取制式支持flag */
    ucSupportFlag = pAddr[ulSumTmp];
    ulSumTmp += 1;

    /* 读取结束频点 */
    ulFreqEnd = (((VOS_UINT32)pAddr[ulSumTmp+3]) << 24)
                | (((VOS_UINT32)pAddr[ulSumTmp+2]) << 16)
                | (((VOS_UINT32)pAddr[ulSumTmp+1]) << 8)
                | ((VOS_UINT32)pAddr[ulSumTmp]);
    ulSumTmp += 4;

    /* 读取起始频点 */
    ulFreqBegin = (((VOS_UINT32)pAddr[ulSumTmp+3]) << 24)
                  | (((VOS_UINT32)pAddr[ulSumTmp+2]) << 16)
                  | (((VOS_UINT32)pAddr[ulSumTmp+1]) << 8)
                  | ((VOS_UINT32)pAddr[ulSumTmp]);
    ulSumTmp += 4;

    /* 若出现end和begin反了的情况，则颠倒一下 */
    if (ulFreqEnd < ulFreqBegin)
    {
        ulFreqTmp = ulFreqEnd;
        ulFreqEnd = ulFreqBegin;
        ulFreqBegin = ulFreqTmp;
    }

    /* 遍历所有频点节点指针，查找该频点是否存在 */
    pstFreqNode = pstBand->pstFreqHead;
    while (CSS_NULL_PTR != pstFreqNode)
    {
        /* 如果频点已存在，则将制式支持情况更新 */
        if ((ulFreqBegin == pstFreqNode->ulFreqBegin)
             && (ulFreqEnd == pstFreqNode->ulFreqEnd))
        {
            pstFreqNode->ucRatSupport |= ucSupportFlag;
            *pulSum += ulSumTmp;
            return CSS_SUCC;
        }
        pstFreqNode = pstFreqNode->pstNext;
    }

    /* 若该频点没有存过，则新增节点 */
    pstFreqNode = (CSS_PUB_PREF_FREQ_STRU*)CSS_AllocCloudPreferNodeAndClearFullMemory(sizeof(CSS_PUB_PREF_FREQ_STRU));
    if (CSS_NULL_PTR == pstFreqNode)
    {
        return CSS_CAUSE_NULL_PTR;
    }
    CSS_MEM_SET_S(pstFreqNode, sizeof(CSS_PUB_PREF_FREQ_STRU), 0, sizeof(CSS_PUB_PREF_FREQ_STRU));

    pstFreqNode->ulFreqBegin = ulFreqBegin;
    pstFreqNode->ulFreqEnd   = ulFreqEnd;
    pstFreqNode->ucRatSupport = ucSupportFlag;

    /*往末尾添加节点*/
    if (CSS_NULL_PTR == pstBand->pstFreqHead)
    {
        pstBand->pstFreqHead          = pstFreqNode;
        pstBand->pstFreqTail          = pstFreqNode;
    }
    else
    {
        pstBand->pstFreqTail->pstNext = pstFreqNode;
        pstBand->pstFreqTail          = pstFreqNode;
    }

    /* 个数加1 */
    pstBand->ucFreqNum ++;

    *pulSum += ulSumTmp;
    return CSS_SUCC;
}

/*****************************************************************************
 Function Name  : CSS_ReadBandRatSuppotFromAtMsg
 Description    : 从码流中读取BAND 的ratSupport数据
 Input          : pstMnc  : MNC节点
                  pAddr   : 码流首地址
                  pulSum  : 地址偏移量
 Output         : pstMnc  : MNC节点
                  pulSum  : 地址偏移量
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_ReadBandRatSuppotFromAtMsg(VOS_UINT8 *pucBandRatFlag, VOS_UINT8 *pAddr, VOS_UINT32 *pulSum, VOS_UINT32 ulRemainLen)
{
    VOS_UINT8                           ucFreqRangeNum;
    VOS_UINT32                          ulSumTmp = 0;
    VOS_UINT8                           ucFlagTmp = 0;

    /* 如果剩下的长度不足以解析，则返回失败 */
    if (ulRemainLen - ulSumTmp < 1)
    {
        return CSS_FAIL;
    }

    /* 读取预置频段个数 */
    ucFreqRangeNum = pAddr[ulSumTmp];
    ulSumTmp += 1;

    /* 如果剩下的长度不足以解析，则返回失败 */
    if (ulRemainLen - ulSumTmp < (ucFreqRangeNum*CSS_SIZEOF_AT_FREQ_RANGE_STRU))
    {
        return CSS_FAIL;
    }

    /* 如果个数不为0，说明有预置BAND */
    if (0 < ucFreqRangeNum)
    {
        ucFlagTmp = pAddr[ulSumTmp];
    }

    ulSumTmp += (ucFreqRangeNum*CSS_SIZEOF_AT_FREQ_RANGE_STRU);

    (*pulSum) += ulSumTmp;
    *pucBandRatFlag = ucFlagTmp;
    return CSS_SUCC;
}

/*****************************************************************************
 Function Name  : CSS_ReadNoPrefBandFlgFromAtMsg
 Description    : 从码流中读取BAND 的ratSupport数据
 Input          : pstMnc  : MNC节点
                  pAddr   : 码流首地址
                  pulSum  : 地址偏移量
 Output         : pstMnc  : MNC节点
                  pulSum  : 地址偏移量
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_ReadNoPrefBandFlgFromAtMsg(CSS_PUB_PREF_MNC_STRU *pstMnc, VOS_UINT8 *pAddr, VOS_UINT32 *pulSum, VOS_UINT32 ulRemainLen)
{
    VOS_UINT32                          ulSumTmp = 0;
    VOS_UINT8                           ucFreqRangeNum;
    VOS_UINT8                           ucSupportFlag;

    /* 如果剩下的长度不足以解析，则返回失败 */
    if (ulRemainLen - ulSumTmp < 1)
    {
        return CSS_FAIL;
    }

    /* 读取预置频段个数 */
    ucFreqRangeNum = pAddr[ulSumTmp];
    ulSumTmp += 1;

    if (0 == ucFreqRangeNum)
    {
        return CSS_FAIL;
    }

    if (ulRemainLen - ulSumTmp < 1)
    {
        return CSS_FAIL;
    }

    ucSupportFlag = pAddr[ulSumTmp];
    ulSumTmp += (ucFreqRangeNum*CSS_SIZEOF_AT_FREQ_RANGE_STRU);

    pstMnc->ucNoPrefBandFlg |= ucSupportFlag;

    (*pulSum) += ulSumTmp;

    return CSS_SUCC;
}




/*****************************************************************************
 Function Name  : CSS_AddBandFromAtMsg
 Description    : 从码流中读取BAND数据
 Input          : pstMnc  : MNC节点
                  pAddr   : 码流首地址
                  pulSum  : 地址偏移量
 Output         : pstMnc  : MNC节点
                  pulSum  : 地址偏移量
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_ReadBandFromAtMsg(CSS_PUB_PREF_MNC_STRU *pstMnc, VOS_UINT8 *pAddr, VOS_UINT32 *pulSum, VOS_UINT32 ulRemainLen)
{
    CSS_PUB_PREF_BAND_STRU             *pstBandNode;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           ucBandInd;
    VOS_UINT8                           ucFreqNum;
    VOS_UINT32                          ulSumTmp = 0;
    VOS_UINT8                           ucBandRatFlag = 0;
    VOS_UINT32                          ulRslt;

    pstBandNode = pstMnc->pstBandHead;

    if (ulRemainLen - ulSumTmp < 2)
    {
        return CSS_FAIL;
    }

    /* 读取BAND值 */
    ucBandInd = pAddr[ulSumTmp];
    ulSumTmp += 1;

    /* 如果BANDIND为0，则表示云端明确该PLMN下GSM/WCDMA/LTE没有网，要跳过GSM/WCDMA/LTE搜索 */
    if (CSS_NO_NETWORK_BAND_IND == ucBandInd)
    {
        if (CSS_SUCC != CSS_ReadNoPrefBandFlgFromAtMsg(pstMnc, &(pAddr[ulSumTmp]), &ulSumTmp, ulRemainLen-ulSumTmp))
        {
            return CSS_FAIL;
        }
    }
    else
    {
        /* 读取预置频段 */
        if (CSS_SUCC != CSS_ReadBandRatSuppotFromAtMsg(&ucBandRatFlag, &(pAddr[ulSumTmp]), &ulSumTmp, ulRemainLen-ulSumTmp))
        {
            return CSS_FAIL;
        }
    }

    if (ulRemainLen - ulSumTmp < 1)
    {
        return CSS_FAIL;
    }

    /* 读取预置频点个数 */
    ucFreqNum = pAddr[ulSumTmp];
    ulSumTmp += 1;

    /* 遍历所有BAND节点，查找是否该BAND已经有了 */
    while (CSS_NULL_PTR != pstBandNode)
    {
        if (pstBandNode->ucBandInd == ucBandInd)
        {
            /* 将BAND制式支持加入 */
            pstBandNode->ucRatSupport |= ucBandRatFlag;

            /* 将各个FREQ加入 */
            for (ulLoop = 0; ulLoop < ucFreqNum; ++ulLoop)
            {
                /* 一旦译码失败，原因只有可能是长度不对或者内存申请失败。
                  长度不对则认为整条码流都是不可信的，内存申请失败则是系统出现问题或内存申请过多。
                  所以失败则直接退出 */
                ulRslt = CSS_ReadFreqFromAtMsg(pstBandNode, &(pAddr[ulSumTmp]), &ulSumTmp, ulRemainLen-ulSumTmp);
                if (CSS_SUCC != ulRslt)
                {
                    return ulRslt;
                }
            }
            *pulSum += ulSumTmp;
            return CSS_SUCC;
        }
        pstBandNode = pstBandNode->pstNext;
    }

    /* 若内存中没有找到相同的BAND，则新增该BAND */
    pstBandNode = (CSS_PUB_PREF_BAND_STRU*)CSS_AllocCloudPreferNodeAndClearFullMemory(sizeof(CSS_PUB_PREF_BAND_STRU));
    if (CSS_NULL_PTR == pstBandNode)
    {
        return CSS_CAUSE_NULL_PTR;
    }
    CSS_MEM_SET_S(pstBandNode, sizeof(CSS_PUB_PREF_BAND_STRU), 0, sizeof(CSS_PUB_PREF_BAND_STRU));

    pstBandNode->ucBandInd = ucBandInd;
    pstBandNode->ucRatSupport |= ucBandRatFlag;

    /*往末尾添加节点*/
    if (CSS_NULL_PTR == pstMnc->pstBandHead)
    {
        pstMnc->pstBandHead          = pstBandNode;
        pstMnc->pstBandTail          = pstBandNode;
    }
    else
    {
        pstMnc->pstBandTail->pstNext = pstBandNode;
        pstMnc->pstBandTail          = pstBandNode;
    }

    /* 个数加1 */
    pstMnc->ucBandNum ++;

    /* 将各个FREQ加入 */
    for (ulLoop = 0; ulLoop < ucFreqNum; ++ulLoop)
    {
        /* 一旦译码失败，原因只有可能是长度不对或者内存申请失败。
           长度不对则认为整条码流都是不可信的，内存申请失败则是系统出现问题或内存申请过多。
           所以失败则直接退出*/
        ulRslt = CSS_ReadFreqFromAtMsg(pstBandNode, &(pAddr[ulSumTmp]), &ulSumTmp, ulRemainLen-ulSumTmp);
        if (CSS_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    *pulSum += ulSumTmp;
    return CSS_SUCC;
}


/*****************************************************************************
 Function Name  : CSS_ReadMncFromAtMsg
 Description    : 从码流中读取MNC数据
 Input          : pstMcc  : MCC节点
                  pAddr   : 码流首地址
                  pulSum  : 地址偏移量
 Output         : pstMcc  : MCC节点
                  pulSum  : 地址偏移量
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_ReadMncFromAtMsg(CSS_PUB_PREF_MCC_STRU *pstMcc, VOS_UINT8 *pAddr, VOS_UINT32 *pulSum, VOS_UINT32 ulRemainLen)
{
    CSS_PUB_PREF_MNC_STRU              *pstMncNode;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           aucMnc[2] = {0};
    VOS_UINT8                           ucBandNum;
    VOS_UINT32                          ulSumTmp = 0;
    VOS_UINT32                          ulRslt;

    pstMncNode = pstMcc->pstMncHead;

    if (ulRemainLen < 3)
    {
        return CSS_FAIL;
    }

    /* 读取MNCid */
    aucMnc[0] = pAddr[ulSumTmp];
    aucMnc[1] = pAddr[ulSumTmp+1];
    ulSumTmp += 2;

    /* 读取BAND个数 */
    ucBandNum = pAddr[ulSumTmp];
    ulSumTmp += 1;

    /* 如果BAND个数为0，则认为该MNC无数据，丢掉 */
    if (0 == ucBandNum)
    {
        return CSS_FAIL;
    }

    /* 遍历所有MNC节点，查找是否该MNC已经有了 */
    while (CSS_NULL_PTR != pstMncNode)
    {
        if (CSS_TRUE == CSS_isMncMatch(pstMncNode->aucMncId, aucMnc))
        {
            for (ulLoop = 0; ulLoop < ucBandNum; ++ulLoop)
            {
                /* 把各个BAND加入 */
                ulRslt = CSS_ReadBandFromAtMsg(pstMncNode, &(pAddr[ulSumTmp]), &ulSumTmp, ulRemainLen-ulSumTmp);
                if (CSS_SUCC != ulRslt)
                {
                    return ulRslt;
                }
            }
            *pulSum += ulSumTmp;
            return CSS_SUCC;
        }
        pstMncNode = pstMncNode->pstNext;
    }

    /* 若没有找到MNC节点，则新增 */
    pstMncNode = (CSS_PUB_PREF_MNC_STRU*)CSS_AllocCloudPreferNodeAndClearFullMemory(sizeof(CSS_PUB_PREF_MNC_STRU));
    if (CSS_NULL_PTR == pstMncNode)
    {
        return CSS_CAUSE_NULL_PTR;
    }
    CSS_MEM_SET_S(pstMncNode, sizeof(CSS_PUB_PREF_MNC_STRU), 0, sizeof(CSS_PUB_PREF_MNC_STRU));
    pstMncNode->aucMncId[0] = aucMnc[0];
    pstMncNode->aucMncId[1] = aucMnc[1];

    /*往末尾添加节点*/
    if (CSS_NULL_PTR == pstMcc->pstMncHead)
    {
        pstMcc->pstMncHead          = pstMncNode;
        pstMcc->pstMncTail          = pstMncNode;
    }
    else
    {
        pstMcc->pstMncTail->pstNext = pstMncNode;
        pstMcc->pstMncTail          = pstMncNode;
    }

    /* 个数加1 */
    pstMcc->ucMncNum ++;

    /* 把各个BAND加入 */
    for (ulLoop = 0; ulLoop < ucBandNum; ++ulLoop)
    {
        ulRslt = CSS_ReadBandFromAtMsg(pstMncNode, &(pAddr[ulSumTmp]), &ulSumTmp, ulRemainLen-ulSumTmp);
        if (CSS_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    *pulSum += ulSumTmp;
    return CSS_SUCC;
}


/*****************************************************************************
 Function Name  : CSS_ReadMccFromAtMsg
 Description    : 从码流中读取MCC数据
 Input          : pAddr         : 码流首地址
                  ulRemainLen   : 剩余字节数
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
/*lint -e429*/
VOS_UINT32 CSS_ReadMccFromAtMsg(VOS_UINT8 *pAddr, VOS_UINT32 ulRemainLen)
{
    CSS_PUB_PREF_MCC_STRU              *pstMccNode;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           aucMcc[2] = {0};
    VOS_UINT8                           ucMncNum;
    VOS_UINT32                          ulSumTmp = 0;
    VOS_UINT32                          ulRslt;

    if (CSS_NULL_PTR == pAddr)
    {
        return CSS_CAUSE_NULL_PTR;
    }

    /* 新增节点，用来保存码流中的信息 */
    pstMccNode = (CSS_PUB_PREF_MCC_STRU*)CSS_AllocCloudPreferNodeAndClearFullMemory(sizeof(CSS_PUB_PREF_MCC_STRU));

    /* 申请内存失败，直接返回 */
    if (CSS_NULL_PTR == pstMccNode)
    {
        return CSS_CAUSE_NULL_PTR;
    }

    /* 内存初始化 */
    CSS_MEM_SET_S(pstMccNode, sizeof(CSS_PUB_PREF_MCC_STRU), 0, sizeof(CSS_PUB_PREF_MCC_STRU));


    /* 读取MCCid */
    aucMcc[0] = pAddr[ulSumTmp];
    aucMcc[1] = pAddr[ulSumTmp+1];
    ulSumTmp += 2;

    /* 如果剩下的长度不够解析则返回失败 */
    if (ulRemainLen - ulSumTmp < 1)
    {
        /* 释放MCC节点内存 */
        CSS_FreeCloudPreferNode(pstMccNode);

        return CSS_FAIL;
    }

    /* 读取MNC个数 */
    ucMncNum  = pAddr[ulSumTmp];
    ulSumTmp += 1;

    pstMccNode->aucMccId[0] = aucMcc[0];
    pstMccNode->aucMccId[1] = aucMcc[1];

    /* 循环取出所有MNC，若有一个取出失败，则返回失败 */
    for (ulLoop = 0; ulLoop < ucMncNum; ++ulLoop)
    {
        ulRslt = CSS_ReadMncFromAtMsg(pstMccNode, &(pAddr[ulSumTmp]), &ulSumTmp, ulRemainLen-ulSumTmp);
        if (CSS_SUCC != ulRslt)
        {
            /* 读取MNC失败，认为整个码流不可信，删除所有读出来的 */
            CSS_DeleteAllMnc(pstMccNode);

            /* 释放MCC节点内存 */
            CSS_FreeCloudPreferNode(pstMccNode);
            return ulRslt;
        }
    }

    /* 将MCC节点读取到本地 */
    CSS_AddMccNodeToLocal(pstMccNode);

    return CSS_SUCC;
}
/*lint +e429*/

/*****************************************************************************
 Function Name  : CSS_AddFreqNodeToLocal
 Description    : 将一个FREQ节点加入到本地某个BAND节点下，加入原则:
                  若发现本地BAND节点下已经有了相同的频点数值，则更新制式支持flag，释放
                  传入的指针的内存;
                  若发现本地BAND节点下没有相同的频点数值，则直接将本地BAND中的FREQ尾节点指针
                  指向传入的FREQ指针，不用申请内存。
 Input          : pstFreqIn     : 传入的FREQ节点
 Output         : pstBandNode   : 需要插入FREQ节点的本地BAND节点
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddFreqNodeToLocal(CSS_PUB_PREF_BAND_STRU *pstBandNode, CSS_PUB_PREF_FREQ_STRU *pstFreqIn)
{
    CSS_PUB_PREF_FREQ_STRU             *pstFreqNode;
    CSS_PUB_PREF_FREQ_STRU             *pstFreqNodeTmp;

    /* 循环遍历，找到FREQ的节点指针 */
    pstFreqNode = pstBandNode->pstFreqHead;
    while (CSS_NULL_PTR != pstFreqNode)
    {
        /* 如找到相同的频点，则更新制式支持flag，并释放传入的指针内存 */
        if (pstFreqNode->ulFreqBegin == pstFreqIn->ulFreqBegin
            && pstFreqNode->ulFreqEnd == pstFreqIn->ulFreqEnd)
        {
            pstFreqNode->ucRatSupport |= pstFreqIn->ucRatSupport;
            CSS_FreeCloudPreferNode(pstFreqIn);
            return;
        }
        pstFreqNode = pstFreqNode->pstNext;
    }

    /* 如果节点个数已达最大值，则去掉头部的，个数减1 */
    if (pstBandNode->ucFreqNum >= CSS_MAX_MEMORY_PERF_FREQ_NUM)
    {
        if (CSS_NULL_PTR != pstBandNode->pstFreqHead)
        {
            pstFreqNodeTmp = pstBandNode->pstFreqHead;

            /* 给新的头尾节点赋值 */
            pstBandNode->pstFreqHead = pstFreqNodeTmp->pstNext;
            if (pstBandNode->pstFreqTail == pstFreqNodeTmp)
            {
                pstBandNode->pstFreqTail = CSS_NULL_PTR;
            }

            /* 删除头结点 */
            CSS_FreeCloudPreferNode(pstFreqNodeTmp);

            /* 个数减1 */
            pstBandNode->ucFreqNum --;
        }
    }

    /* 如没有找到相同的频点，则将该节点添加到末尾 */
    if (CSS_NULL_PTR == pstBandNode->pstFreqHead)
    {
        pstBandNode->pstFreqHead          = pstFreqIn;
        pstBandNode->pstFreqTail          = pstFreqIn;
    }
    else
    {
        if (CSS_NULL_PTR != pstBandNode->pstFreqTail)
        {
            pstBandNode->pstFreqTail->pstNext = pstFreqIn;
        }
        pstBandNode->pstFreqTail          = pstFreqIn;
    }
    pstFreqIn->pstNext = CSS_NULL_PTR;
    pstBandNode->ucFreqNum ++;
}


/*****************************************************************************
 Function Name  : CSS_AddBandNodeToLocal
 Description    : 将一个BAND节点加入到本地某个MNC节点下，加入原则:
                  若发现本地MNC节点下已经有了相同的BAND数值，则遍历传入的BAND指针，
                  依次将传入BAND指针中的FREQ加入到本地BAND节点中;
                  若发现本地MNC节点下没有相同的BAND数值，则直接本地中的BAND尾节点指针
                  指向传入的BAND指针，不用申请内存。
 Input          : pstBandIn     : 传入的BAND节点
 Output         : pstMncNode    : 需要插入BAND节点的本地MNC节点
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddBandNodeToLocal(CSS_PUB_PREF_MNC_STRU *pstMncNode, CSS_PUB_PREF_BAND_STRU *pstBandIn)
{
    CSS_PUB_PREF_BAND_STRU             *pstBandNode;
    CSS_PUB_PREF_BAND_STRU             *pstBandNodeTmp;
    CSS_PUB_PREF_FREQ_STRU             *pstFreqNode;
    CSS_PUB_PREF_FREQ_STRU             *pstFreqNodeTmp;

    /* 循环遍历，找到该BAND的节点指针 */
    pstBandNode = pstMncNode->pstBandHead;
    while (CSS_NULL_PTR != pstBandNode)
    {
        /* 找到相同的BAND */
        if (pstBandNode->ucBandInd == pstBandIn->ucBandInd)
        {
            /* 将BAND 制式支持加入 */
            pstBandNode->ucRatSupport |= pstBandIn->ucRatSupport;

            /* 依次将传入BAND指针中的FREQ加入到本地BAND节点中，并释放传入的BAND指针内存 */
            pstFreqNode = pstBandIn->pstFreqHead;
            while (CSS_NULL_PTR != pstFreqNode)
            {
                pstFreqNodeTmp = pstFreqNode->pstNext;
                CSS_AddFreqNodeToLocal(pstBandNode, pstFreqNode);
                pstFreqNode = pstFreqNodeTmp;
            }
            CSS_FreeCloudPreferNode(pstBandIn);
            return;
        }
        pstBandNode = pstBandNode->pstNext;
    }

    /* 如果节点个数已达最大值，则去掉头部的，个数减1 */
    if (pstMncNode->ucBandNum >= CSS_MAX_MEMORY_PERF_BAND_NUM)
    {
        if (CSS_NULL_PTR != pstMncNode->pstBandHead)
        {
            pstBandNodeTmp = pstMncNode->pstBandHead;

            /* 给新的头尾节点赋值 */
            pstMncNode->pstBandHead = pstBandNodeTmp->pstNext;
            if (pstMncNode->pstBandTail == pstBandNodeTmp)
            {
                pstMncNode->pstBandTail = CSS_NULL_PTR;
            }

            /* 删除头结点 */
            CSS_DeleteAllFreq(pstBandNodeTmp);
            CSS_FreeCloudPreferNode(pstBandNodeTmp);

            /* 个数减1 */
            pstMncNode->ucBandNum --;
        }
    }

    /* 如没有找到相同的BAND，则将该节点添加到末尾 */
    if (CSS_NULL_PTR == pstMncNode->pstBandHead)
    {
        pstMncNode->pstBandHead          = pstBandIn;
        pstMncNode->pstBandTail          = pstBandIn;
    }
    else
    {
        if (CSS_NULL_PTR != pstMncNode->pstBandTail)
        {
            pstMncNode->pstBandTail->pstNext = pstBandIn;
        }
        pstMncNode->pstBandTail          = pstBandIn;
    }
    pstBandIn->pstNext = CSS_NULL_PTR;
    pstMncNode->ucBandNum ++;
}


/*****************************************************************************
 Function Name  : CSS_AddMncNodeToLocal
 Description    : 将一个MNC节点加入到本地某个MCC节点下，加入原则:
                  若发现本地MCC节点下已经有了相同的MNC数值，则遍历传入的MNC指针，
                  依次将传入MNC指针中的BAND加入到本地MNC节点中;
                  若发现本地MCC节点下没有相同的MNC数值，则直接本地中的MNC尾节点指针
                  指向传入的MNC指针，不用申请内存。
 Input          : pstMncIn      : 传入的MNC节点
 Output         : pstMccNode    : 需要插入MNC节点的本地MCC节点
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddMncNodeToLocal(CSS_PUB_PREF_MCC_STRU *pstMccNode, CSS_PUB_PREF_MNC_STRU *pstMncIn)
{
    CSS_PUB_PREF_MNC_STRU              *pstMncNode;
    CSS_PUB_PREF_MNC_STRU              *pstMncNodeTmp;
    CSS_PUB_PREF_BAND_STRU             *pstBandNode;
    CSS_PUB_PREF_BAND_STRU             *pstBandNodeTmp;

    /* 循环遍历，找到该MNC的节点指针 */
    pstMncNode = pstMccNode->pstMncHead;
    while (CSS_NULL_PTR != pstMncNode)
    {
        /* 找到相同的MNC */
        if (CSS_TRUE == CSS_isMncMatch(pstMncNode->aucMncId, pstMncIn->aucMncId))
        {
            /* 依次将传入MNC指针中的BAND加入到本地MNC节点中，并释放传入的MNC指针内存 */
            pstBandNode = pstMncIn->pstBandHead;
            while (CSS_NULL_PTR != pstBandNode)
            {
                pstBandNodeTmp = pstBandNode->pstNext;
                CSS_AddBandNodeToLocal(pstMncNode, pstBandNode);
                pstBandNode = pstBandNodeTmp;
            }
            CSS_FreeCloudPreferNode(pstMncIn);
            return;
        }
        pstMncNode = pstMncNode->pstNext;
    }

    /* 如果节点个数已达最大值，则去掉头部的，个数减1 */
    if (pstMccNode->ucMncNum >= CSS_MAX_MEMORY_PERF_MNC_NUM)
    {
        if (CSS_NULL_PTR != pstMccNode->pstMncHead)
        {
            pstMncNodeTmp = pstMccNode->pstMncHead;

            /* 给新的头尾节点赋值 */
            pstMccNode->pstMncHead = pstMncNodeTmp->pstNext;
            if (pstMccNode->pstMncTail == pstMncNodeTmp)
            {
                pstMccNode->pstMncTail = CSS_NULL_PTR;
            }

            /* 删除头结点 */
            CSS_DeleteAllBand(pstMncNodeTmp);
            CSS_FreeCloudPreferNode(pstMncNodeTmp);

            /* 个数减1 */
            pstMccNode->ucMncNum --;
        }
    }

    /* 如没有找到相同的MNC，则将该节点添加到末尾 */
    if (CSS_NULL_PTR == pstMccNode->pstMncHead)
    {
        pstMccNode->pstMncHead          = pstMncIn;
        pstMccNode->pstMncTail          = pstMncIn;
    }
    else
    {
        if (CSS_NULL_PTR != pstMccNode->pstMncTail)
        {
            pstMccNode->pstMncTail->pstNext = pstMncIn;
        }
        pstMccNode->pstMncTail          = pstMncIn;
    }
    pstMncIn->pstNext = CSS_NULL_PTR;
    pstMccNode->ucMncNum++;
}


/*****************************************************************************
 Function Name  : CSS_AddMccNodeToLocal
 Description    : 将一个MCC节点加入到本地，加入原则:
                  若发现本地已经有了相同的MCC，则遍历传入的MCC指针，
                  依次将传入MCC指针中的MNC加入到本地MCC节点中;
                  若发现本地没有相同的MCC，则直接本地中的MCC尾节点指针
                  指向传入的MCC指针，不用申请内存。
 Input          : pstMccIn      : 传入的MCC节点
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddMccNodeToLocal(CSS_PUB_PREF_MCC_STRU *pstMccIn)
{
    CSS_PUB_PREF_MCC_STRU              *pstMccNode;
    CSS_PUB_PREF_MNC_STRU              *pstMncNode;
    CSS_PUB_PREF_MCC_STRU              *pstMccNodeTmp;
    CSS_PUB_PREF_MNC_STRU              *pstMncNodeTmp;

    /* 循环遍历，找到该MCC的节点指针 */
    pstMccNode = CSS_GetPrefMccHeadNode();
    while (CSS_NULL_PTR != pstMccNode)
    {
        /* 找到相同的MCC */
        if (CSS_TRUE == CSS_isMccMatch(pstMccNode->aucMccId, pstMccIn->aucMccId))
        {
            /* 依次将传入MCC指针中的MNC加入到本地MCC节点中，并释放传入的MCC指针内存 */
            pstMncNode = pstMccIn->pstMncHead;
            while (CSS_NULL_PTR != pstMncNode)
            {
                pstMncNodeTmp  = pstMncNode->pstNext;
                CSS_AddMncNodeToLocal(pstMccNode, pstMncNode);
                pstMncNode = pstMncNodeTmp;
            }
            CSS_FreeCloudPreferNode(pstMccIn);
            return;
        }
        pstMccNode = pstMccNode->pstNext;
    }

    /* 如果节点个数已达最大值，则去掉头部的，个数减1 */
    if (CSS_GetPrefMccNodeNum() >= CSS_MAX_MEMORY_PERF_MCC_NUM)
    {
        if (CSS_NULL_PTR != CSS_GetPrefMccHeadNode())
        {
            pstMccNodeTmp = CSS_GetPrefMccHeadNode();

            /* 给新的头尾节点赋值 */
            CSS_GetPrefMccHeadNode() = pstMccNodeTmp->pstNext;
            if (CSS_GetPrefMccTailNode() == pstMccNodeTmp)
            {
                CSS_GetPrefMccTailNode() = CSS_NULL_PTR;
            }

            /* 删除头结点 */
            CSS_DeleteAllMnc(pstMccNodeTmp);
            CSS_FreeCloudPreferNode(pstMccNodeTmp);

            /* 个数减1 */
            CSS_GetPrefMccNodeNum() --;
        }
    }

    /* 将该节点添加到末尾，个数加1 */
    if (CSS_NULL_PTR == CSS_GetPrefMccHeadNode())
    {
        CSS_GetPrefMccHeadNode()          = pstMccIn;
        CSS_GetPrefMccTailNode()          = pstMccIn;
    }
    else
    {
        if (CSS_NULL_PTR != CSS_GetPrefMccTailNode())
        {
            CSS_GetPrefMccTailNode()->pstNext = pstMccIn;
        }
        CSS_GetPrefMccTailNode()          = pstMccIn;
    }
    CSS_GetPrefMccNodeNum() ++;
}


/*****************************************************************************
 Function Name  : CSS_UpdateRatFreqToNv
 Description    : 将本地某制式支持的FREQ节点写入NV。
 Input          : aucMncId      : 传入的MNC ID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_UpdateRatFreqToNv
(
    VOS_UINT8 aucMncId[2],
    VOS_UINT8 ucBand,
    CSS_RAT_TYPE_ENUM_UINT8 ucRat,
    CSS_PUB_PREF_FREQ_STRU *pstFreqNode,
    CSS_NV_PREF_MCC_STRU *pstNvMcc
)
{
    CSS_NV_PREF_MNC_STRU               *pNvMnc = CSS_NULL_PTR;
    CSS_NV_PREF_ARFCN_STRU             *pNvFreq = CSS_NULL_PTR;
    VOS_UINT8                           aucNvMnc[2] = {0};
    VOS_UINT8                           ucNvRat;

    /* 如果现有个数小于等于最大个数 */
    if (pstNvMcc->usMncNum <= CSS_NV_MAX_PREF_MNC_NUM)
    {
        /* 取已保存数据的最后一个MNC结构 */
        pNvMnc = &(pstNvMcc->astMnc[pstNvMcc->usMncNum-1]);

        /* 获取MNC id */
        CSS_ConvertMncDigitToSimMnc(pNvMnc->bitMncDigit1, pNvMnc->bitMncDigit2, pNvMnc->bitMncDigit3, aucNvMnc);

        /* 取该NV节点的制式 */
        ucNvRat = pNvMnc->bitRat;

        /* 如果MNC结构中的个数没满并且MNC、BAND、制式与要保存的MNC相同，则添加FREQ */
        if ((pNvMnc->ucArfcnNum < CSS_NV_MAX_PREF_ARFCN_NUM)
            &&(CSS_TRUE == CSS_isMncMatch(aucNvMnc, aucMncId))
            &&(ucBand == pNvMnc->ucBandInd)
            &&(ucNvRat == ucRat))
        {
            pNvFreq = &(pNvMnc->astArfcn[pNvMnc->ucArfcnNum]);
            pNvFreq->ulArfcnBegin = pstFreqNode->ulFreqBegin;
            pNvFreq->ulArfcnEnd   = pstFreqNode->ulFreqEnd;
            pNvMnc->ucArfcnNum ++;
        }
        /* 否则，找下一个MNC结构，并保存在该MNC的第一个FREQ结构里 */
        else
        {
            if (pstNvMcc->usMncNum < CSS_NV_MAX_PREF_MNC_NUM)
            {
                /* 保存相关参数 */
                pNvMnc = &(pstNvMcc->astMnc[pstNvMcc->usMncNum]);
                pNvMnc->bitMncDigit1 = (aucMncId[1] & CSS_OCTET_LOW_4_BITS);
                pNvMnc->bitMncDigit2 = ((aucMncId[1] & CSS_OCTET_HIGH_4_BITS) >> CSS_OCTET_MOVE_4_BITS);
                pNvMnc->bitMncDigit3 = ((aucMncId[0] & CSS_OCTET_HIGH_4_BITS) >> CSS_OCTET_MOVE_4_BITS);
                pNvMnc->bitRat = ucRat;
                pNvMnc->ucBandInd = ucBand;
                pstNvMcc->usMncNum ++;

                pNvFreq = &(pNvMnc->astArfcn[0]);
                pNvFreq->ulArfcnBegin = pstFreqNode->ulFreqBegin;
                pNvFreq->ulArfcnEnd   = pstFreqNode->ulFreqEnd;
                pNvMnc->ucArfcnNum = 1;
            }
        }
    }
}


/*****************************************************************************
 Function Name  : CSS_UpdateRatFreqToNv
 Description    : 将本地某制式支持的BAND节点写入NV，用于BAND下没有预置频点的情况
 Input          : aucMncId      : 传入的MNC ID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_UpdateRatBandToNv
(
    VOS_UINT8 aucMncId[2],
    CSS_RAT_TYPE_ENUM_UINT8 ucRat,
    CSS_PUB_PREF_BAND_STRU *pstBandNode,
    CSS_NV_PREF_MCC_STRU *pstNvMcc
)
{
    CSS_NV_PREF_MNC_STRU               *pNvMnc = CSS_NULL_PTR;

    if (pstNvMcc->usMncNum < CSS_NV_MAX_PREF_MNC_NUM)
    {
        pNvMnc = &(pstNvMcc->astMnc[pstNvMcc->usMncNum]);
        pNvMnc->bitMncDigit1 = (aucMncId[1] & CSS_OCTET_LOW_4_BITS);
        pNvMnc->bitMncDigit2 = ((aucMncId[1] & CSS_OCTET_HIGH_4_BITS) >> CSS_OCTET_MOVE_4_BITS);
        pNvMnc->bitMncDigit3 = ((aucMncId[0] & CSS_OCTET_HIGH_4_BITS) >> CSS_OCTET_MOVE_4_BITS);
        pNvMnc->bitRat = ucRat;
        pNvMnc->ucBandInd = pstBandNode->ucBandInd;
        pstNvMcc->usMncNum ++;
    }
}


/*****************************************************************************
 Function Name  : CSS_UpdateFreqToNv
 Description    : 将本地某个BAND下的所有FREQ节点写入NV。
 Input          : aucMncId      : 传入的MNC ID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_UpdateFreqToNv
(
    VOS_UINT8 aucMncId[2],
    CSS_PUB_PREF_BAND_STRU *pstBandNode,
    CSS_NV_PREF_MCC_STRU *pstNvMcc
)
{
    CSS_PUB_PREF_FREQ_STRU             *pstFreqNode;

    /* 如果FREQ数为零，也需要将BAND加入 */
    if (0 == pstBandNode->ucFreqNum)
    {
        /* 如果支持GSM，则加GSM加入 */
        if (CSS_TRUE == CSS_IsRatSupportInFlag(CSS_RAT_GSM, pstBandNode->ucRatSupport))
        {
            CSS_UpdateRatBandToNv(aucMncId, CSS_RAT_GSM, pstBandNode, pstNvMcc);
        }
        /* 如果支持WCDMA，则加WCDMA加入 */
        if (CSS_TRUE == CSS_IsRatSupportInFlag(CSS_RAT_UMTS_FDD, pstBandNode->ucRatSupport))
        {
            CSS_UpdateRatBandToNv(aucMncId, CSS_RAT_UMTS_FDD, pstBandNode, pstNvMcc);
        }
        /* 如果支持LTE，则加LTE加入 */
        if (CSS_TRUE == CSS_IsRatSupportInFlag(CSS_RAT_LTE, pstBandNode->ucRatSupport))
        {
            CSS_UpdateRatBandToNv(aucMncId, CSS_RAT_LTE, pstBandNode, pstNvMcc);
        }

        return;
    }

    /* 如果BAND有额外的ratSupport */
    if (0 != pstBandNode->ucRatSupport)
    {
        /* 如果支持GSM，则加GSM加入 */
        if (CSS_TRUE == CSS_IsRatSupportInFlag(CSS_RAT_GSM, pstBandNode->ucRatSupport))
        {
            CSS_UpdateRatBandToNv(aucMncId, CSS_RAT_GSM, pstBandNode, pstNvMcc);
        }
        /* 如果支持WCDMA，则加WCDMA加入 */
        if (CSS_TRUE == CSS_IsRatSupportInFlag(CSS_RAT_UMTS_FDD, pstBandNode->ucRatSupport))
        {
            CSS_UpdateRatBandToNv(aucMncId, CSS_RAT_UMTS_FDD, pstBandNode, pstNvMcc);
        }
        /* 如果支持LTE，则加LTE加入 */
        if (CSS_TRUE == CSS_IsRatSupportInFlag(CSS_RAT_LTE, pstBandNode->ucRatSupport))
        {
            CSS_UpdateRatBandToNv(aucMncId, CSS_RAT_LTE, pstBandNode, pstNvMcc);
        }
    }

    /* 循环遍历，找到FREQ的节点指针 */
    pstFreqNode = pstBandNode->pstFreqHead;
    while (CSS_NULL_PTR != pstFreqNode)
    {
        /* 如果支持GSM，则加GSM加入 */
        if (CSS_TRUE == CSS_IsRatSupportInFlag(CSS_RAT_GSM, pstFreqNode->ucRatSupport))
        {
            CSS_UpdateRatFreqToNv(aucMncId, pstBandNode->ucBandInd, CSS_RAT_GSM, pstFreqNode, pstNvMcc);
        }
        /* 如果支持WCDMA，则加WCDMA加入 */
        if (CSS_TRUE == CSS_IsRatSupportInFlag(CSS_RAT_UMTS_FDD, pstFreqNode->ucRatSupport))
        {
            CSS_UpdateRatFreqToNv(aucMncId, pstBandNode->ucBandInd, CSS_RAT_UMTS_FDD, pstFreqNode, pstNvMcc);
        }
        /* 如果支持LTE，则加LTE加入 */
        if (CSS_TRUE == CSS_IsRatSupportInFlag(CSS_RAT_LTE, pstFreqNode->ucRatSupport))
        {
            CSS_UpdateRatFreqToNv(aucMncId, pstBandNode->ucBandInd, CSS_RAT_LTE, pstFreqNode, pstNvMcc);
        }
        pstFreqNode = pstFreqNode->pstNext;
    }
}



/*****************************************************************************
 Function Name  : CSS_UpdateBandToNv
 Description    : 将本地某个MNC下的所有BAND写入NV。
 Input          : pstMccIn      : 传入的MCC节点
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_UpdateBandToNv(CSS_PUB_PREF_MNC_STRU *pstMncNode, CSS_NV_PREF_MCC_STRU *pstNvMcc)
{
    CSS_PUB_PREF_BAND_STRU             *pstBandNode;

    /* 循环遍历，找到该BAND的节点指针 */
    pstBandNode = pstMncNode->pstBandHead;
    while (CSS_NULL_PTR != pstBandNode)
    {
        CSS_UpdateFreqToNv(pstMncNode->aucMncId, pstBandNode, pstNvMcc);
        pstBandNode = pstBandNode->pstNext;
    }
}

/*****************************************************************************
 Function Name  : CSS_UpdateMncToNv
 Description    : 将本地某个MCC下的所有MNC写入NV。
 Input          : pstMccIn      : 传入的MCC节点
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_UpdateMncToNv(CSS_PUB_PREF_MCC_STRU *pstMccNode, CSS_NV_PREF_MCC_STRU *pstNvMcc)
{
    CSS_PUB_PREF_MNC_STRU              *pstMncNode;

    /* 循环遍历，找到该MNC的节点指针 */
    pstMncNode = pstMccNode->pstMncHead;
    while (CSS_NULL_PTR != pstMncNode)
    {
        CSS_UpdateBandToNv(pstMncNode, pstNvMcc);
        pstMncNode = pstMncNode->pstNext;
    }

    pstNvMcc->bitMccDigit1 = (pstMccNode->aucMccId[0] & CSS_OCTET_LOW_4_BITS);
    pstNvMcc->bitMccDigit2 = ((pstMccNode->aucMccId[0] & CSS_OCTET_HIGH_4_BITS) >> CSS_OCTET_MOVE_4_BITS);
    pstNvMcc->bitMccDigit3 = (pstMccNode->aucMccId[1] & CSS_OCTET_LOW_4_BITS);
}

/*****************************************************************************
 Function Name  : CSS_UpdateMccToNv
 Description    : 将本地某个MCC写入NV。
 Input          : pstMccIn      : 传入的MCC节点
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_UpdateMccToNv(VOS_UINT8 aucMccId[2], CSS_NV_PREF_MCC_STRU *pstNvMcc)
{
    CSS_PUB_PREF_MCC_STRU              *pstMccNode;

    /* 循环遍历，找到该MCC的节点指针 */
    pstMccNode = CSS_GetPrefMccHeadNode();
    while (CSS_NULL_PTR != pstMccNode)
    {
        /* 找到相同的MCC */
        if (CSS_TRUE == CSS_isMccMatch(pstMccNode->aucMccId, aucMccId))
        {
            CSS_UpdateMncToNv(pstMccNode, pstNvMcc);
            return CSS_SUCC;
        }
        pstMccNode = pstMccNode->pstNext;
    }
    return CSS_FAIL;
}

/*****************************************************************************
 Function Name  : CSS_WriteNvMccPrefFreq
 Description    : 将本地已存储的MCC 写入NV。
 Input          : pstMccIn      : 传入的MCC节点
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_WriteNvMccPrefFreq(VOS_VOID)
{
    VOS_UINT32                          ulDataLen = 0;
    CSS_NV_PREF_MCC_STRU               *pstNvPerfFreq;
    CSS_CLOUD_PUB_CONTROL_STRU         *pstCloudControl;
    VOS_UINT32                          ulResult;

    pstCloudControl = CSS_GetCloudContrlAddr();
    ulDataLen = sizeof(CSS_NV_PREF_MCC_STRU);

    CSS_INFO_LOG("CSS_WriteNvMccPrefFreq: enter");
    TLPS_PRINT2LAYER_INFO(CSS_WriteNvMccPrefFreq_ENUM, LNAS_ENTRY);

    /* 如果云通信特性不使用，直接返回 */
    if (CSS_FALSE == CSS_IsCloudStrategyEnable())
    {
        CSS_INFO_LOG("CSS_WriteNvMccPrefFreq: cloud strategy is not enabled");
        TLPS_PRINT2LAYER_INFO(CSS_WriteNvMccPrefFreq_ENUM, LNAS_FUNCTION_LABEL1);
        return;
    }

    /* 如果不从云端获取，也直接返回 */
    if (CSS_FALSE == CSS_IsPrefFreqEnable())
    {
        CSS_INFO_LOG("CSS_WriteNvMccPrefFreq: cloud pref freq is not enabled");
        TLPS_PRINT2LAYER_INFO(CSS_WriteNvMccPrefFreq_ENUM, LNAS_FUNCTION_LABEL2);
        return;
    }

    pstNvPerfFreq = (CSS_NV_PREF_MCC_STRU*)CSS_MEM_ALLOC(sizeof(CSS_NV_PREF_MCC_STRU));
    if (CSS_NULL_PTR == pstNvPerfFreq)
    {
        return;
    }

    CSS_PrintLocalPrefFreqInfo();

    /* 为0则表示还在初始化状态，没有MCC。不为0才更新MCC */
    /* MCC1 */
    if (0 != pstCloudControl->astNvMcc[0].aucMccId[0])
    {
        TLPS_PRINT2LAYER_INFO2( CSS_WriteNvMccPrefFreq_ENUM,
                                LNAS_FUNCTION_LABEL3,
                                pstCloudControl->astNvMcc[0].aucMccId[0],
                                pstCloudControl->astNvMcc[0].aucMccId[1]);

        CSS_MEM_SET_S(pstNvPerfFreq, sizeof(CSS_NV_PREF_MCC_STRU), 0, sizeof(CSS_NV_PREF_MCC_STRU));
        if (CSS_SUCC == CSS_UpdateMccToNv(pstCloudControl->astNvMcc[0].aucMccId, pstNvPerfFreq))
        {
            ulResult = CSS_NV_Write(EN_NV_ID_PS_CLOUD_PREFER_FREQ_MCC1,
                                    (VOS_VOID *)(pstNvPerfFreq),
                                    ulDataLen);
            if (VOS_OK != ulResult)
            {
                TLPS_PRINT2LAYER_INFO1(CSS_WriteNvMccPrefFreq_ENUM,LNAS_FUNCTION_LABEL3,ulResult);
            }
        }

    }

    /* MCC2 */
    if (0 != pstCloudControl->astNvMcc[1].aucMccId[0])
    {
        TLPS_PRINT2LAYER_INFO2( CSS_WriteNvMccPrefFreq_ENUM,
                                LNAS_FUNCTION_LABEL4,
                                pstCloudControl->astNvMcc[1].aucMccId[0],
                                pstCloudControl->astNvMcc[1].aucMccId[1]);

        CSS_MEM_SET_S(pstNvPerfFreq, sizeof(CSS_NV_PREF_MCC_STRU), 0, sizeof(CSS_NV_PREF_MCC_STRU));
        if (CSS_SUCC == CSS_UpdateMccToNv(pstCloudControl->astNvMcc[1].aucMccId, pstNvPerfFreq))
        {
            ulResult = CSS_NV_Write(EN_NV_ID_PS_CLOUD_PREFER_FREQ_MCC2,
                                    (VOS_VOID *)(pstNvPerfFreq),
                                    ulDataLen);
            if (VOS_OK != ulResult)
            {
                TLPS_PRINT2LAYER_INFO1(CSS_WriteNvMccPrefFreq_ENUM,LNAS_FUNCTION_LABEL4,ulResult);
            }
        }
    }

    /* MCC3 */
    if (0 != pstCloudControl->astNvMcc[2].aucMccId[0])
    {
        TLPS_PRINT2LAYER_INFO2( CSS_WriteNvMccPrefFreq_ENUM,
                                LNAS_FUNCTION_LABEL5,
                                pstCloudControl->astNvMcc[2].aucMccId[0],
                                pstCloudControl->astNvMcc[2].aucMccId[1]);

        CSS_MEM_SET_S(pstNvPerfFreq, sizeof(CSS_NV_PREF_MCC_STRU), 0, sizeof(CSS_NV_PREF_MCC_STRU));
        if (CSS_SUCC == CSS_UpdateMccToNv(pstCloudControl->astNvMcc[2].aucMccId, pstNvPerfFreq))
        {
            ulResult = CSS_NV_Write(EN_NV_ID_PS_CLOUD_PREFER_FREQ_MCC3,
                                    (VOS_VOID *)(pstNvPerfFreq),
                                    ulDataLen);
            if (VOS_OK != ulResult)
            {
                TLPS_PRINT2LAYER_INFO1(CSS_WriteNvMccPrefFreq_ENUM,LNAS_FUNCTION_LABEL5,ulResult);
            }
        }
    }

    CSS_MEM_FREE(pstNvPerfFreq);
}


/*****************************************************************************
 Function Name  : CSS_ConvertAscToHex
 Description    : 将ASC码转化成16进制
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_ConvertAscToHex(VOS_UINT8 *pucDest, VOS_UINT8 ucSrc)
{
    if (CSS_NULL_PTR == pucDest)
    {
        return CSS_FAIL;
    }

    /* 0-9 */
    if((ucSrc >= 0x30)&&(ucSrc <=0x39))
    {
        *pucDest = ucSrc - 0x30;
    }
    /* A-F */
    else if((ucSrc >= 0x41)&&(ucSrc <=0x46))
    {
        *pucDest = ucSrc - 0x41 + 10;
    }
    /* a-f */
    else if((ucSrc >= 0x61)&&(ucSrc <=0x66))
    {
        *pucDest = ucSrc - 0x61 + 10;
    }
    else
    {
        return CSS_FAIL;
    }
    return CSS_SUCC;
}


/*****************************************************************************
 Function Name  : CSS_ConvertStrToHex
 Description    : 将字符串转化成16进制
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_ConvertStrToHex(VOS_UINT8 *pucHex, const VOS_UINT8 *pucStr, VOS_UINT32 ulStrLen)
{
    VOS_UINT8                           ucConvertHex;
    VOS_UINT8                           ucTmpHex = 0;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulHexNum = 0;

    if ((CSS_NULL_PTR == pucHex)
        ||(CSS_NULL_PTR == pucStr)
        ||(0 == ulStrLen))
    {
        return CSS_FAIL;
    }

    if (0 != ulStrLen % 2)
    {
        return CSS_FAIL;
    }

    CSS_MEM_SET_S(pucHex, ulStrLen/2, 0, ulStrLen/2);

    for (ulLoop = 0; ulLoop < ulStrLen; ++ulLoop)
    {
        if(CSS_FAIL == CSS_ConvertAscToHex(&ucConvertHex, pucStr[ulLoop]))
        {
            return CSS_FAIL;
        }

        if(0 == ulLoop % 2)
        {
            ucTmpHex = (VOS_UINT8)(ucConvertHex << CSS_OCTET_MOVE_4_BITS);
        }
        else
        {
            ucTmpHex |= ucConvertHex;
            pucHex[ulHexNum++] = ucTmpHex;
        }
    }
    return CSS_SUCC;
}

/*****************************************************************************
 Function Name  : CSS_IsMccNeedToDelete
 Description    : 判断某个MCC是否需要删除(基于是否正在更新)
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsMccNeedToDelete(VOS_UINT8 aucMccId[2])
{
    VOS_UINT8                           ucIsBelongToMutiMccCountry;
    VOS_UINT32                          i;
    VOS_UINT32                          ulTmpMcc;
    VOS_UINT8                           aucTmpMcc[2];
    VOS_UINT32                          ulCountryIdx = 0;

    CSS_ConvertSimMccToGuMcc(aucMccId, &ulTmpMcc);
    ucIsBelongToMutiMccCountry = CSS_FALSE;

    /* 判断输入的MCC是否属于多MCC国家 */
    for (i = 0; i < CSS_MCC_COUNTY_NUM; ++i)
    {
        if (CSS_TRUE == CSS_IsMccBelongToCountry(ulTmpMcc, &(g_astCountryMccList[i])))
        {
            ucIsBelongToMutiMccCountry = CSS_TRUE;
            ulCountryIdx = i;
            break;
        }
    }

    /* 如果不属于多MCC国家 */
    if (CSS_FALSE == ucIsBelongToMutiMccCountry)
    {
        /* 如果在更新列表中 */
        if (CSS_TRUE == CSS_IsMccUpdatingInUpdateStateTable(aucMccId))
        {
            return CSS_FALSE;
        }
    }
    else
    {
        /* 如果属于多MCC国家，则判断该国家的每个MCC是否在更新列表中 */
        for (i = 0; i < g_astCountryMccList[ulCountryIdx].ulMccNum; ++i)
        {
            CSS_ConvertGuMccToSimMcc(g_astCountryMccList[ulCountryIdx].pulMccListAddr[i], aucTmpMcc);
            if (CSS_TRUE == CSS_IsMccUpdatingInUpdateStateTable(aucTmpMcc))
            {
                return CSS_FALSE;
            }
        }
    }

    return CSS_TRUE;
}


/*****************************************************************************
 Function Name  : CSS_DeleteLocalMccNotUpdating
 Description    : 将本地保存的MCC数据中不属于正在更新的MCC数据删掉，只有在内存已满的情况下才会调用此函数。用来接收最新的MCC。
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_DeleteLocalMccNotUpdating(VOS_VOID)
{
    CSS_PUB_PREF_MCC_STRU              *pMccNode;
    VOS_UINT8                           ucMccNum = 0;
    CSS_MCC_ID_STRU                     astMccId[CSS_MAX_MEMORY_PERF_MCC_NUM];
    VOS_UINT8                           ucLoopNum = 0;
    VOS_UINT8                           i;

    CSS_MEM_SET_S(astMccId, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_MEMORY_PERF_MCC_NUM, 0, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_MEMORY_PERF_MCC_NUM);

    /* 找到所有需要删除的MCC节点的MCC ID */
    pMccNode = CSS_GetPrefMccHeadNode();
    while ((CSS_NULL_PTR != pMccNode) && (ucLoopNum < CSS_GetPrefMccNodeNum()))
    {
        if ((CSS_TRUE == CSS_IsMccNeedToDelete(pMccNode->aucMccId))
             && (ucMccNum < CSS_MAX_MEMORY_PERF_MCC_NUM))
        {
            astMccId[ucMccNum].aucMccId[0] = pMccNode->aucMccId[0];
            astMccId[ucMccNum].aucMccId[1] = pMccNode->aucMccId[1];
            ucMccNum ++;

            TLPS_PRINT2LAYER_INFO2(CSS_DeleteLocalMccNotUpdating_ENUM, LNAS_FUNCTION_LABEL1, pMccNode->aucMccId[0], pMccNode->aucMccId[1]);
        }
        pMccNode = pMccNode->pstNext;
        ucLoopNum ++;
    }

    /* 根据MCC ID将所有MCC 删除 */
    for (i = 0; i < ucMccNum; ++i)
    {
        CSS_DeleteOneMcc(astMccId[i].aucMccId);
    }

}



VOS_VOID * CSS_AllocCloudPreferNodeAndClearFullMemory(VOS_UINT32 ulLen)
{
    #if(FEATURE_ON == FEATURE_CSS_CLOUD_MEMORY_IMPROVE)
    VOS_UINT32                          ulUsedLen = CSS_GetCloudMemUsedLen();
    VOS_UINT32                          ulOneBlockLen;

    /* 当要申请的节点长度大于BLOCK实际数据长度时，说明出现异常了 */
    if (ulLen > CSS_CLOUD_BLOCK_DATA_LEN)
    {
        TLPS_PRINT2LAYER_ERROR(CSS_AllocCloudPreferNodeAndClearFullMemory_ENUM, LNAS_CSS_ALLOC_SIZE_LARGER_THAN_BLOCK);
        return CSS_NULL_PTR;
    }

    /* 一个小块的大小 */
    ulOneBlockLen = sizeof(CSS_MEM_BLOCK_STRU);

    /* 若剩下的内存已不够使用，则删除老的MCC数据 */
    if ((ulUsedLen + ulOneBlockLen) > CSS_CLOUD_MEM_TOTAL_LEN)
    {
        TLPS_PRINT2LAYER_INFO(CSS_AllocCloudPreferNodeAndClearFullMemory_ENUM, LNAS_CSS_CLOUD_MEM_IS_FULL);
        CSS_DeleteLocalMccNotUpdating();
    }

    return CSS_AllocCloudPreferNode();

    #else

    return CSS_MEM_ALLOC(ulLen);

    #endif
}


#if(FEATURE_ON == FEATURE_CSS_CLOUD_MEMORY_IMPROVE)

VOS_VOID * CSS_AllocCloudPreferNode(VOS_VOID)
{
    CSS_MEM_BLOCK_STRU                 *pstBlock;
    VOS_UINT32                          ulOneBlockLen;
    VOS_UINT32                          ulTmpLen = 0;
    VOS_UINT32                          ulTotalNum = 0;
    VOS_UINT32                          ulLoop;

    /* 一个BLOCK的大小 */
    ulOneBlockLen = sizeof(CSS_MEM_BLOCK_STRU);

    /* 总的BLOCK个数 */
    ulTotalNum = CSS_CLOUD_MEM_TOTAL_LEN / ulOneBlockLen;

    /* 遍历所有BLOCK，找到没有使用的BLOCK */
    for (ulLoop = 0; ulLoop < ulTotalNum; ++ulLoop)
    {
        /* 取首地址的当前偏移作为当前BLOCK的首地址 */
        pstBlock = (CSS_MEM_BLOCK_STRU*)((VOS_UINT8*)CSS_GetCloudMemAddr()+ulTmpLen);

        /* 若当前BLOCK没有被使用 */
        if (CSS_FALSE == pstBlock->stMemHead.ucUsedFlag)
        {
            pstBlock->stMemHead.ucUsedFlag = CSS_TRUE;
            CSS_GetCloudMemUsedLen() += ulOneBlockLen;
            TLPS_PRINT2LAYER_INFO1(CSS_AllocCloudPreferNode_ENUM, LNAS_CSS_USE_CLOUD_MEM_BLOCK_INDEX, ulLoop);
            return &(pstBlock->aucData[0]);
        }

        ulTmpLen += ulOneBlockLen;
    }

    TLPS_PRINT2LAYER_INFO(CSS_AllocCloudPreferNode_ENUM, LNAS_CSS_ALLOC_RETURN_NULL_PTR);
    return CSS_NULL_PTR;
}
#endif



VOS_VOID CSS_FreeCloudPreferNode(VOS_VOID *pAddr)
{
    #if(FEATURE_ON == FEATURE_CSS_CLOUD_MEMORY_IMPROVE)
    CSS_MEM_BLOCK_STRU                 *pstBlock;
    VOS_UINT32                          ulOneBlockLen;
    VOS_UINT32                          ulBlockHeadLen;

    /* 合法性判断 */
    if (CSS_NULL_PTR == pAddr)
    {
        return;
    }

    /* 一个小块的大小 */
    ulOneBlockLen = sizeof(CSS_MEM_BLOCK_STRU);

    /* 一个小块的头结构大小 */
    ulBlockHeadLen = sizeof(CSS_MEM_BLOCK_HEAD_STRU);

    pstBlock = (CSS_MEM_BLOCK_STRU*)((VOS_UINT8*)pAddr-ulBlockHeadLen);

    /* 若内存已被使用，则清除使用标记，总使用大小相应减少 */
    if (CSS_TRUE == pstBlock->stMemHead.ucUsedFlag)
    {
        pstBlock->stMemHead.ucUsedFlag = CSS_FALSE;
        CSS_GetCloudMemUsedLen() -= ulOneBlockLen;
    }

    #else

    CSS_MEM_FREE(pAddr);

    #endif
}





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of CssCloudStrategyPublic.c */



