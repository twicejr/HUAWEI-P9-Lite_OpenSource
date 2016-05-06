/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : CssProcSrchRslt.c
  Description     : 该C文件给出了CSS模块处理收到的搜网结果和存储结果的实现
  History           :
     1.chengmin 00285307    2015-05-15  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "CssNvInterface.h"
#include "CssPublic.h"
#include "NasMmlCtx.h"
#include "CssProcLphyMsg.h"
#include "stdlib.h"
#include "CssProcSrchRslt.h"

#define    THIS_FILE_ID        PS_FILE_ID_CSSPROCSRCHRSLT_C

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



/*****************************************************************************
  3 Function
*****************************************************************************/


/*****************************************************************************
 Function Name   : CSS_RssiCompare
 Description     : 能量从大到小排序函数
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    chengmin 00285307      2015-05-15  Draft Enact
*****************************************************************************/
VOS_INT32 CSS_RssiCompare( const VOS_VOID *arg1, const VOS_VOID *arg2 )
{
    CSS_FREQ_RANGE_STRU             *pstFreqRange1;
    CSS_FREQ_RANGE_STRU             *pstFreqRange2;

    pstFreqRange1 = (CSS_FREQ_RANGE_STRU*) arg1;
    pstFreqRange2 = (CSS_FREQ_RANGE_STRU*) arg2;
    if (pstFreqRange1->sRssi > pstFreqRange2->sRssi)
    {
        return -1;
    }
    else if (pstFreqRange1->sRssi < pstFreqRange2->sRssi)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


/*****************************************************************************
 Function Name   : CSS_FreqCompare
 Description     : 能量从小到大排序函数
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    chengmin 00285307      2015-05-15  Draft Enact
*****************************************************************************/
VOS_INT32 CSS_FreqCompare( const VOS_VOID *arg1, const VOS_VOID *arg2 )
{
    CSS_FREQ_RANGE_STRU             *pstFreqRange1;
    CSS_FREQ_RANGE_STRU             *pstFreqRange2;

    pstFreqRange1 = (CSS_FREQ_RANGE_STRU*) arg1;
    pstFreqRange2 = (CSS_FREQ_RANGE_STRU*) arg2;
    if (pstFreqRange1->usCentralFreq > pstFreqRange2->usCentralFreq)
    {
        return 1;
    }
    else if (pstFreqRange1->usCentralFreq < pstFreqRange2->usCentralFreq)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/*****************************************************************************
 Function Name   : CSS_GetThreshold
 Description     : 获取能量门限
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    chengmin 00285307      2015-05-15  Draft Enact
*****************************************************************************/
VOS_INT16 CSS_GetThreshold(VOS_VOID)
{
    VOS_INT16                           sThreshold = INT16_MAX;
    CSS_CONTROL_STRU                   *pstCssControl;
    CSS_COMM_SCAN_BAND_NODE_STRU       *pstCurBandNode;

    pstCurBandNode   = CSS_GetCommScanBandListCurrNode();

    pstCssControl    = CSS_GetControlAddr();

    /* 如果请求的是高能量扫频，则获取各个制式的高能量门限，并以最低的为准 */
    if (CSS_OP_TRUE == pstCssControl->stCommMsg.bitOpHighRssi)
    {
        if (CSS_OP_TRUE == pstCurBandNode->stBandInfo.bitOpLteSupport)
        {
            sThreshold = pstCssControl->stRssiThreshold.sLHighRssiThresHold;
        }
        if (CSS_OP_TRUE == pstCurBandNode->stBandInfo.bitOpWcdmaSupport)
        {
            sThreshold = CSS_MIN(sThreshold, pstCssControl->stRssiThreshold.sWHighRssiThresHold);
        }
        if (CSS_OP_TRUE == pstCurBandNode->stBandInfo.bitOpGsmSupport)
        {
            sThreshold = CSS_MIN(sThreshold, pstCssControl->stRssiThreshold.sGHighRssiThresHold);
        }
    }
    /* 如果请求的是非高能量扫频，则获取各个制式的可驻留能量门限，并以最低的为准 */
    else
    {
        if (CSS_OP_TRUE == pstCurBandNode->stBandInfo.bitOpLteSupport)
        {
            sThreshold = pstCssControl->stRssiThreshold.sLLowRssiThresHold;
        }
        if (CSS_OP_TRUE == pstCurBandNode->stBandInfo.bitOpWcdmaSupport)
        {
            sThreshold = CSS_MIN(sThreshold, pstCssControl->stRssiThreshold.sWLowRssiThresHold);
        }
        if (CSS_OP_TRUE == pstCurBandNode->stBandInfo.bitOpGsmSupport)
        {
            sThreshold = CSS_MIN(sThreshold, pstCssControl->stRssiThreshold.sGLowRssiThresHold);
        }
    }

    return sThreshold;
}
/*****************************************************************************
 Function Name   : CSS_DivideToFreqRangeByBand
 Description     : 按照协议将某个BAND分成若干段，用于向LPHY下发扫频请求
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    chengmin 00285307      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_DivideToFreqRangeByBand
(
    CSS_LPHY_BAND_IND_ENUM_UINT16       usBand,
    CSS_LPHY_FREQ_RANGE_INFO_STRU     **ppstFreqRangeIn,
    VOS_UINT8                          *pucFreqRangeNum
)
{
    VOS_UINT16                           usFreqBegin;
    VOS_UINT16                           usFreqEnd;
    VOS_UINT16                           usLoop;
    VOS_UINT8                            ucNum;
    CSS_LPHY_FREQ_RANGE_INFO_STRU       *pstFreqRange;

    *ppstFreqRangeIn = CSS_NULL_PTR;
    *pucFreqRangeNum = CSS_NULL;

    /* 如果是非标频段，直接返回失败 */
    if (CSS_LPHY_BAND_IND_43 < usBand)
    {
        CSS_WARN_LOG("CSS_DivideToFreqRangeByBand:BAND num exceed 43!!!");
        TLPS_PRINT2LAYER_WARNING(CSS_DivideToFreqRangeByBand_ENUM, LNAS_BAND_NumExceed43);
        return CSS_FAIL;
    }

    /* 若果是不存在的BAND，直接返回失败 */
    if ((CSS_LPHY_BAND_IND_15 == usBand)
         ||(CSS_LPHY_BAND_IND_16 == usBand)
         ||(CSS_LPHY_BAND_IND_32 == usBand))
    {
        CSS_WARN_LOG("CSS_DivideToFreqRangeByBand:wrong BAND num!!!");
        TLPS_PRINT2LAYER_WARNING(CSS_DivideToFreqRangeByBand_ENUM, LNAS_WrongBANDNum);
        return CSS_FAIL;
    }

    /* 获取该BAND的协议起始和结束频率 */
    usFreqBegin     = g_ausCssLteBandFreq[usBand-1].usFreqBegin;
    usFreqEnd       = g_ausCssLteBandFreq[usBand-1].usFreqEnd;

    /* 首先获得需要分段的段数 */
    ucNum           = CSS_NULL;
    usLoop          = usFreqBegin;
    while(usLoop < usFreqEnd)
    {
        ucNum++;
        usLoop += CSS_FREQ_RANGE_999_100KHZ;
    }

    /* 得到段数后申请内存空间 */
    *pucFreqRangeNum = ucNum;
    pstFreqRange    = CSS_MEM_ALLOC(ucNum*sizeof(CSS_LPHY_FREQ_RANGE_INFO_STRU));

    /* 申请内存失败则返回 */
    if (CSS_NULL_PTR == pstFreqRange)
    {
        CSS_WARN_LOG("CSS_DivideToFreqRangeByBand:Alloc MEM FAIL!!!");
        return CSS_FAIL;
    }

    /* 获取每个小段的起始和结束频率 */
    ucNum           = CSS_NULL;
    usLoop          = usFreqBegin;
    while(usLoop < usFreqEnd)
    {
        pstFreqRange[ucNum].usFreqBegin = usLoop;
        if ((usLoop + CSS_FREQ_RANGE_999_100KHZ) < usFreqEnd)
        {
            pstFreqRange[ucNum].usFreqEnd = usLoop + CSS_FREQ_RANGE_999_100KHZ;
        }
        else
        {
            pstFreqRange[ucNum].usFreqEnd = usFreqEnd;
        }
        ucNum++;
        usLoop += CSS_FREQ_RANGE_999_100KHZ;
    }

    *ppstFreqRangeIn = pstFreqRange;

    return CSS_SUCC;
}

/*****************************************************************************
 Function Name   : CSS_GetSuportFlagFromRatList
 Description     : 根据请求的RATLIST获取各制式的支持情况
 Input           : None
 Output          : 是否成功
 Return          : VOS_UINT32
 History         :
    1.    chengmin 00285307      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_GetSuportFlagFromRatList
(
    const CSS_RAT_LIST  *pstRatList,
    VOS_UINT8           *pucRatFlag
)
{
    VOS_UINT8            ucLoop;
    VOS_UINT8            ucSuportFlag = 0;
    for (ucLoop = 0; ucLoop < pstRatList->ucRatNum; ++ucLoop)
    {
        if (CSS_RAT_GSM == pstRatList->aucRatList[ucLoop])
        {
            ucSuportFlag |= CSS_GSM_SUPORT_OP;
        }
        else if (CSS_RAT_LTE== pstRatList->aucRatList[ucLoop])
        {
            ucSuportFlag |= CSS_LTE_SUPORT_OP;
        }
        else if (CSS_RAT_UMTS_FDD== pstRatList->aucRatList[ucLoop])
        {
           ucSuportFlag |= CSS_WCDMA_SUPORT_OP;
        }
    }

    *pucRatFlag = ucSuportFlag;

    return CSS_TRUE;
}

/*****************************************************************************
 Function Name   : CSS_GetLteSuportFlag
 Description     : 根据BAND、NV是否支持、UE的BAND支持能力、请求的制式来决定是否处理L模
 Input           : None
 Output          : 是否处理
 Return          :
 History         :
    1.    chengmin 00285307      2015-05-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_GetLteSuportFlag
(
    VOS_UINT8                          ucBand,
    VOS_UINT8                          ucOpNVSupport,
    NAS_MML_MS_BAND_INFO_STRU         *pstUserSetBand,
    VOS_UINT8                          ucRequireFlag,
    VOS_UINT8                         *pucSuportFlag
)
{
    VOS_UINT8            ucIsSuport  = 0;
    if ((CSS_OP_TRUE == ucOpNVSupport)
        && (CSS_FALSE != (ucRequireFlag & CSS_LTE_SUPORT_OP)))
    {
        if (32 > ucBand)
        {
            ucIsSuport = (pstUserSetBand->stLteBand.aulLteBand[0] >> (ucBand-1)) & 0x00000001;
        }
        else
        {
            ucIsSuport = (pstUserSetBand->stLteBand.aulLteBand[1] >> (ucBand-33)) & 0x00000001;
        }
        if (ucIsSuport)
        {
            *pucSuportFlag |= CSS_LTE_SUPORT_OP;
        }
    }
}

/*****************************************************************************
 Function Name   : CSS_GetGsmSuportFlag
 Description     : 根据BAND、NV是否支持、UE的BAND支持能力、请求的制式来决定是否处理G模
 Input           : None
 Output          : 是否处理
 Return          :
 History         :
    1.    chengmin 00285307      2015-05-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_GetGsmSuportFlag
(
    VOS_UINT8                          ucBand,
    VOS_UINT8                          ucOpNVSupport,
    NAS_MML_MS_BAND_INFO_STRU         *pstUserSetBand,
    VOS_UINT8                          ucRequireFlag,
    VOS_UINT8                         *pucSuportFlag
)
{
    VOS_UINT8            ucIsSuport  = 0;
    if ((CSS_OP_TRUE == ucOpNVSupport)
        && (CSS_FALSE != (ucRequireFlag & CSS_GSM_SUPORT_OP)))
    {
        if (5 == ucBand)
        {
            ucIsSuport = ((pstUserSetBand->unGsmBand.ulBand) & 0x0004);
        }
        else if (2 == ucBand)
        {
            ucIsSuport = ((pstUserSetBand->unGsmBand.ulBand) & 0x0080);
        }
        else if (3 == ucBand)
        {
            ucIsSuport = ((pstUserSetBand->unGsmBand.ulBand) & 0x0040);
        }
        else if (8 == ucBand)
        {
            ucIsSuport = (((pstUserSetBand->unGsmBand.ulBand) & 0x0020)
                         | ((pstUserSetBand->unGsmBand.ulBand) & 0x0010)
                         | ((pstUserSetBand->unGsmBand.ulBand) & 0x008));
        }
        else
        {
        }
        /*
        if (32 > ucBand)
        {
            ucIsSuport = (pstUserSetBand->unGsmBand.ulBand >> (ucBand-1)) & 0x0001;
        }
        */
        if (ucIsSuport)
        {
            *pucSuportFlag |= CSS_GSM_SUPORT_OP;
        }
    }
}

/*****************************************************************************
 Function Name   : CSS_GetWcdmaSuportFlag
 Description     : 根据BAND、NV是否支持、UE的BAND支持能力、请求的制式来决定是否处理W模
 Input           : None
 Output          :
 Return          :
 History         :
    1.    chengmin 00285307      2015-05-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_GetWcdmaSuportFlag
(
    VOS_UINT8                          ucBand,
    VOS_UINT8                          ucOpNVSupport,
    NAS_MML_MS_BAND_INFO_STRU         *pstUserSetBand,
    VOS_UINT8                          ucRequireFlag,
    VOS_UINT8                         *pucSuportFlag
)
{
    VOS_UINT8            ucIsSuport  = 0;
    if ((CSS_OP_TRUE == ucOpNVSupport)
        && (CSS_FALSE != (ucRequireFlag & CSS_WCDMA_SUPORT_OP)))
    {
        if (32 > ucBand)
        {
            ucIsSuport = (pstUserSetBand->unWcdmaBand.ulBand >> (ucBand-1)) & 0x0001;
            if (ucIsSuport)
            {
                *pucSuportFlag |= CSS_WCDMA_SUPORT_OP;
            }
        }
    }
}




/*****************************************************************************
 Function Name   : CSS_RatSuportFlagForCommBandScan
 Description     : 根据UE的BAND能力、NV中配置、扫频请求获得BAND支持哪些制式
 Input           : None
 Output          : 是否处理
 Return          : VOS_UINT32
 History         :
    1.    chengmin 00285307      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_RatSuportFlagForCommBandScan
(
    CSS_BAND_PARA_STRU                *pstBandInfo,
    NAS_MML_MS_BAND_INFO_STRU         *pstUserSetBand,
    VOS_UINT8                         *pucRatFlag
)
{
    VOS_UINT8                             ucBand  = pstBandInfo->ucBandInd;
    CSS_CONTROL_STRU                     *pstCssControl;

    VOS_UINT8                             ucSuportFlag = 0;
    VOS_UINT8                             ucRequireFlag= 0;

    pstCssControl = CSS_GetControlAddr();

    /* 如果是非标频段，直接返回失败 */
    if (CSS_LPHY_BAND_IND_43 < ucBand)
    {
        CSS_WARN_LOG("CSS_GetSuportBandRatOp:BAND num exceed 43!!!");
        TLPS_PRINT2LAYER_WARNING(CSS_RatSuportFlagForCommBandScan_ENUM, LNAS_BAND_NumExceed43);
        return CSS_FAIL;
    }

    /* 若果是不存在的BAND，直接返回失败 */
    if ((CSS_LPHY_BAND_IND_15 == ucBand)
         ||(CSS_LPHY_BAND_IND_16 == ucBand)
         ||(CSS_LPHY_BAND_IND_32 == ucBand))
    {
        CSS_WARN_LOG("CSS_GetSuportBandRatOp:wrong BAND num!!!");
        TLPS_PRINT2LAYER_WARNING(CSS_RatSuportFlagForCommBandScan_ENUM, LNAS_WrongBANDNum);
        return CSS_FAIL;
    }

    /* 扫频请求的制式 */
    (VOS_VOID)CSS_GetSuportFlagFromRatList(&(pstCssControl->stCommMsg.stRatList), &ucRequireFlag);

    /* 如果扫频请求和NV中都有该制式，则看UE实际是否支持该制式 */
    /* LTE */
    CSS_GetLteSuportFlag(ucBand,
                         pstBandInfo->bitOpLteSupport,
                         pstUserSetBand,
                         ucRequireFlag,
                         &ucSuportFlag);

    /* GSM */
    CSS_GetGsmSuportFlag(ucBand,
                         pstBandInfo->bitOpGsmSupport,
                         pstUserSetBand,
                         ucRequireFlag,
                         &ucSuportFlag);

    /* WCDMA */
    CSS_GetWcdmaSuportFlag(ucBand,
                         pstBandInfo->bitOpWcdmaSupport,
                         pstUserSetBand,
                         ucRequireFlag,
                         &ucSuportFlag);

    *pucRatFlag = ucSuportFlag;

    return CSS_SUCC;
}

/*****************************************************************************
 Function Name   : CSS_RatSuportFlagForAllBandScan
 Description     : 根据UE的BAND能力看某BAND是否支持
 Input           : None
 Output          :
 Return          : VOS_UINT32
 History         :
    1.    chengmin 00285307      2015-05-25  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_RatSuportFlagForAllBandScan
(
    VOS_UINT8                          ucBand,
    NAS_MML_MS_BAND_INFO_STRU         *pstUserSetBand,
    VOS_UINT8                         *pucRatFlag

)
{
    VOS_UINT8                             ucRequireFlag= 0;
    VOS_UINT8                             ucSuportFlag = 0;
    CSS_CONTROL_STRU                     *pstCssControl;

    *pucRatFlag = 0;

    /* 如果是非标频段，直接返回失败 */
    if (CSS_LPHY_BAND_IND_43 < ucBand)
    {
        CSS_WARN_LOG("CSS_GetUESuportBandOp:BAND num exceed 43!!!");
        TLPS_PRINT2LAYER_WARNING(CSS_RatSuportFlagForAllBandScan_ENUM, LNAS_BAND_NumExceed43);

        return CSS_FAIL;
    }

    /* 若果是不存在的BAND，直接返回失败 */
    if ((CSS_LPHY_BAND_IND_15 == ucBand)
         ||(CSS_LPHY_BAND_IND_16 == ucBand)
         ||(CSS_LPHY_BAND_IND_32 == ucBand))
    {
        CSS_WARN_LOG("CSS_GetUESuportBandOp:wrong BAND num!!!");
        TLPS_PRINT2LAYER_WARNING(CSS_RatSuportFlagForAllBandScan_ENUM, LNAS_WrongBANDNum);
        return CSS_FAIL;
    }

    pstCssControl = CSS_GetControlAddr();

    /* 扫频请求的制式 */
    (VOS_VOID)CSS_GetSuportFlagFromRatList(&(pstCssControl->stCommMsg.stRatList), &ucRequireFlag);

    /* LTE */
    CSS_GetLteSuportFlag(ucBand,
                         CSS_OP_TRUE,
                         pstUserSetBand,
                         ucRequireFlag,
                         &ucSuportFlag);

    /* GSM */
    CSS_GetGsmSuportFlag(ucBand,
                         CSS_OP_TRUE,
                         pstUserSetBand,
                         ucRequireFlag,
                         &ucSuportFlag);

    /* WCDMA */
    CSS_GetWcdmaSuportFlag(ucBand,
                         CSS_OP_TRUE,
                         pstUserSetBand,
                         ucRequireFlag,
                         &ucSuportFlag);

    *pucRatFlag = ucSuportFlag;

    return CSS_SUCC;

}




VOS_UINT32  CSS_ProcAllBandScanReqest(VOS_VOID)
{
    VOS_UINT8                          ucBandLoop;
    CSS_COMM_SCAN_BAND_NODE_STRU      *pstBandNode        = CSS_NULL_PTR;
    NAS_MML_MS_BAND_INFO_STRU         *pstUserSetBand     = CSS_NULL_PTR;
    VOS_UINT8                          ucSuportFlag;

    /* 获取UE实际支持的BAND */
    pstUserSetBand  = NAS_MML_GetMsSupportBand();
    if (CSS_NULL_PTR == pstUserSetBand)
    {
        return CSS_FAIL;
    }

    /* 将获取的BAND信息钩到HIDS */
    CSS_SendOmMmlUeSupportBandInfoInd(pstUserSetBand);

    for (ucBandLoop=1; ucBandLoop<=CSS_BAND_IND_43; ++ucBandLoop)
    {
        if (CSS_SUCC != CSS_RatSuportFlagForAllBandScan(ucBandLoop, pstUserSetBand, &ucSuportFlag))
        {
            continue;
        }
        /* 三种制式都不支持 */
        if ((CSS_FALSE == (ucSuportFlag & CSS_GSM_SUPORT_OP))
            && (CSS_FALSE == (ucSuportFlag & CSS_WCDMA_SUPORT_OP))
            && (CSS_FALSE == (ucSuportFlag & CSS_LTE_SUPORT_OP)))
        {
            continue;
        }
        /*申请内存并初始化*/
        pstBandNode = (CSS_COMM_SCAN_BAND_NODE_STRU*)CSS_MEM_ALLOC(sizeof(CSS_COMM_SCAN_BAND_NODE_STRU));
        if (CSS_NULL_PTR == pstBandNode)
        {
            CSS_FreeCommScanRsltMemory();
            return CSS_FAIL;
        }

        CSS_MEM_SET_S(pstBandNode, sizeof(CSS_COMM_SCAN_BAND_NODE_STRU), 0, sizeof(CSS_COMM_SCAN_BAND_NODE_STRU));

        /*分割频段*/
        if (CSS_SUCC != CSS_DivideToFreqRangeByBand(ucBandLoop,
                                                      &(pstBandNode->stBandInfo.pstScanReqArray),
                                                      &(pstBandNode->stBandInfo.ucScanReqCount)))
        {
            CSS_FreeCommScanRsltMemory();
            (VOS_VOID)CSS_MEM_FREE(pstBandNode);
            return CSS_FAIL;
        }

        pstBandNode->stBandInfo.ucBandInd              = ucBandLoop;
        pstBandNode->stBandInfo.bitOpGsmSupport        = (ucSuportFlag>>CSS_GSM_OP_OFFSET)&0x01;
        pstBandNode->stBandInfo.bitOpWcdmaSupport      = (ucSuportFlag>>CSS_WCDMA_OP_OFFSET)&0x01;
        pstBandNode->stBandInfo.bitOpLteSupport        = (ucSuportFlag>>CSS_LTE_OP_OFFSET)&0x01;

        /*往末尾添加节点*/
        if (CSS_NULL_PTR == CSS_GetCommScanBandListHeadNode())
        {
            CSS_GetCommScanBandListHeadNode()          = pstBandNode;
            CSS_GetCommScanBandListTailNode()          = pstBandNode;
        }
        else
        {
            CSS_GetCommScanBandListTailNode()->pstNext = pstBandNode;
            CSS_GetCommScanBandListTailNode()          = pstBandNode;
        }
        CSS_GetCommScanBandListAddr()->ucBandCount ++;

        /* BAND数最多支持22个 */
        if (CSS_MAX_BAND_NUM <= CSS_GetCommScanBandListAddr()->ucBandCount)
        {
            break;
        }
    }

    /* 初始化当前正在处理的指针节点 */
    CSS_GetCommScanBandListCurrNode() = CSS_GetCommScanBandListHeadNode();
    CSS_GetCommScanCurFreqRangeIdx()  = CSS_NULL;

    if (0 == CSS_GetCommScanBandListAddr()->ucBandCount)
    {
        CSS_INFO_LOG("CSS_ProcCommBandScanReqest:bandcount is 0");
        TLPS_PRINT2LAYER_INFO(CSS_ProcAllBandScanReqest_ENUM, LNAS_BandCountIsZero);
        return CSS_FAIL;
    }
    return CSS_SUCC;
}





VOS_UINT32  CSS_ProcCommBandScanReqest(VOS_VOID)
{
    VOS_UINT8                          ucLoop;
    CSS_COMM_SCAN_BAND_NODE_STRU      *pstBandNode        = CSS_NULL_PTR;
    NAS_MML_MS_BAND_INFO_STRU         *pstUserSetBand     = CSS_NULL_PTR;
    CSS_COMM_BAND_INFO_STRU           *pCommBandInfo;
    VOS_UINT8                          ucSuportFlag;

    /* 获取UE实际支持的BAND */
    pstUserSetBand  = NAS_MML_GetMsSupportBand();
    if (CSS_NULL_PTR == pstUserSetBand)
    {
        return CSS_FAIL;
    }

    TLPS_PRINT2LAYER_INFO1(CSS_ProcCommBandScanReqest_ENUM, LNAS_WcdmaBand, pstUserSetBand->unWcdmaBand.ulBand);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcCommBandScanReqest_ENUM, LNAS_GsmBand, pstUserSetBand->unGsmBand.ulBand);
    TLPS_PRINT2LAYER_INFO2(CSS_ProcCommBandScanReqest_ENUM, LNAS_LteBand, pstUserSetBand->stLteBand.aulLteBand[0],pstUserSetBand->stLteBand.aulLteBand[1]);

    /* 将获取的BAND信息钩到HIDS */
    CSS_SendOmMmlUeSupportBandInfoInd(pstUserSetBand);

    pCommBandInfo   = &(CSS_GetControlAddr()->stCommBandInfo);

    for (ucLoop = 0; ucLoop<pCommBandInfo->ucBandNum; ++ucLoop)
    {
        if (CSS_SUCC != CSS_RatSuportFlagForCommBandScan(&(pCommBandInfo->astBand[ucLoop]), pstUserSetBand, &ucSuportFlag))
        {
            continue;
        }

        /* 三种制式都不支持 */
        if ((CSS_FALSE == (ucSuportFlag & CSS_GSM_SUPORT_OP))
            && (CSS_FALSE == (ucSuportFlag & CSS_WCDMA_SUPORT_OP))
            && (CSS_FALSE == (ucSuportFlag & CSS_LTE_SUPORT_OP)))
        {
            continue;
        }

        /*申请内存并初始化*/
        pstBandNode = (CSS_COMM_SCAN_BAND_NODE_STRU*)CSS_MEM_ALLOC(sizeof(CSS_COMM_SCAN_BAND_NODE_STRU));
        if (CSS_NULL_PTR == pstBandNode)
        {
            CSS_FreeCommScanRsltMemory();
            return CSS_FAIL;
        }

        CSS_MEM_SET_S(pstBandNode, sizeof(CSS_COMM_SCAN_BAND_NODE_STRU), 0, sizeof(CSS_COMM_SCAN_BAND_NODE_STRU));

        /*分割频段*/
        if (CSS_SUCC != CSS_DivideToFreqRangeByBand(pCommBandInfo->astBand[ucLoop].ucBandInd,
                                                      &(pstBandNode->stBandInfo.pstScanReqArray),
                                                      &(pstBandNode->stBandInfo.ucScanReqCount)))
        {
            CSS_FreeCommScanRsltMemory();
            (VOS_VOID)CSS_MEM_FREE(pstBandNode);
            return CSS_FAIL;
        }

        pstBandNode->stBandInfo.ucBandInd              = pCommBandInfo->astBand[ucLoop].ucBandInd;
        pstBandNode->stBandInfo.bitOpGsmSupport        = (ucSuportFlag>>CSS_GSM_OP_OFFSET)&0x01;
        pstBandNode->stBandInfo.bitOpWcdmaSupport      = (ucSuportFlag>>CSS_WCDMA_OP_OFFSET)&0x01;
        pstBandNode->stBandInfo.bitOpLteSupport        = (ucSuportFlag>>CSS_LTE_OP_OFFSET)&0x01;

        /*往末尾添加节点*/
        if (CSS_NULL_PTR == CSS_GetCommScanBandListHeadNode())
        {
            CSS_GetCommScanBandListHeadNode()          = pstBandNode;
            CSS_GetCommScanBandListTailNode()          = pstBandNode;
        }
        else
        {
            CSS_GetCommScanBandListTailNode()->pstNext = pstBandNode;
            CSS_GetCommScanBandListTailNode()          = pstBandNode;
        }
        CSS_GetCommScanBandListAddr()->ucBandCount ++;

        /* BAND数最多支持22个 */
        if (CSS_MAX_BAND_NUM <= CSS_GetCommScanBandListAddr()->ucBandCount)
        {
            break;
        }
    }

    /* 初始化当前正在处理的指针节点 */
    CSS_GetCommScanBandListCurrNode() = CSS_GetCommScanBandListHeadNode();
    CSS_GetCommScanCurFreqRangeIdx()  = CSS_NULL;

    if (0 == CSS_GetCommScanBandListAddr()->ucBandCount)
    {
        CSS_INFO_LOG("CSS_ProcCommBandScanReqest:bandcount is 0");
        TLPS_PRINT2LAYER_INFO(CSS_ProcCommBandScanReqest_ENUM, LNAS_BandCountIsZero);
        return CSS_FAIL;
    }
    return CSS_SUCC;
}



VOS_UINT32  CSS_ProcBandScanReqest(VOS_VOID)
{
    CSS_CONTROL_STRU                   *pstCssControl;

    pstCssControl    = CSS_GetControlAddr();

    if (CSS_BAND_SCAN_ALL == pstCssControl->stCommMsg.enBandScanType)
    {
        return CSS_ProcAllBandScanReqest();
    }
    else if (CSS_BAND_SCAN_COMM == pstCssControl->stCommMsg.enBandScanType)
    {
        return CSS_ProcCommBandScanReqest();
    }

    return CSS_FAIL;
}


VOS_UINT32 CSS_ProcAsBandScanReqest(CSS_RAT_TYPE_ENUM_UINT8 ucRatType, const CSS_BAND_LIST *pBandList)
{
    VOS_UINT8                          ucLoop;
    CSS_COMM_SCAN_BAND_NODE_STRU      *pstBandNode        = CSS_NULL_PTR;
    VOS_UINT8                          ucBandNum          = 0;

    ucBandNum = (pBandList->ucBandNum <= CSS_AS_BAND_SCAN_REQ_MAX_BAND_NUM) ? pBandList->ucBandNum : CSS_AS_BAND_SCAN_REQ_MAX_BAND_NUM;

    for (ucLoop = 0; ucLoop < ucBandNum; ++ucLoop)
    {
        if (CSS_LPHY_BAND_IND_43 < pBandList->ausBandList[ucLoop])
        {
            TLPS_PRINT2LAYER_WARNING(CSS_ProcAsBandScanReqest_ENUM, LNAS_BAND_NumExceed43);
            continue;
        }

        /*申请内存并初始化*/
        pstBandNode = (CSS_COMM_SCAN_BAND_NODE_STRU*)CSS_MEM_ALLOC(sizeof(CSS_COMM_SCAN_BAND_NODE_STRU));
        if (CSS_NULL_PTR == pstBandNode)
        {
            CSS_FreeAsScanRsltMemory();
            return CSS_FAIL;
        }
        CSS_MEM_SET_S(pstBandNode, sizeof(CSS_COMM_SCAN_BAND_NODE_STRU), 0, sizeof(CSS_COMM_SCAN_BAND_NODE_STRU));

        /*分割频段*/
        if (CSS_SUCC != CSS_DivideToFreqRangeByBand(pBandList->ausBandList[ucLoop],
                                                      &(pstBandNode->stBandInfo.pstScanReqArray),
                                                      &(pstBandNode->stBandInfo.ucScanReqCount)))
        {
            CSS_FreeAsScanRsltMemory();
            (VOS_VOID)CSS_MEM_FREE(pstBandNode);
            return CSS_FAIL;
        }

        pstBandNode->stBandInfo.ucBandInd              = (VOS_UINT8)pBandList->ausBandList[ucLoop];

        if (CSS_RAT_GSM == ucRatType)
        {
            pstBandNode->stBandInfo.bitOpGsmSupport        = CSS_OP_TRUE;
        }
        else if (CSS_RAT_UMTS_FDD == ucRatType)
        {
            pstBandNode->stBandInfo.bitOpWcdmaSupport      = CSS_OP_TRUE;
        }
        else if (CSS_RAT_LTE == ucRatType)
        {
            pstBandNode->stBandInfo.bitOpLteSupport        = CSS_OP_TRUE;
        }
        else if (CSS_RAT_TDS == ucRatType)
        {
            pstBandNode->stBandInfo.bitOpTdsSupport        = CSS_OP_TRUE;
        }

        /*往末尾添加节点*/
        if (CSS_NULL_PTR == CSS_GetAsScanBandListHeadNode())
        {
            CSS_GetAsScanBandListHeadNode()          = pstBandNode;
            CSS_GetAsScanBandListTailNode()          = pstBandNode;
        }
        else
        {
            CSS_GetAsScanBandListTailNode()->pstNext = pstBandNode;
            CSS_GetAsScanBandListTailNode()          = pstBandNode;
        }
        CSS_GetAsScanBandListAddr()->ucBandCount ++;
    }

    /* 初始化当前正在处理的指针节点 */
    CSS_GetAsScanBandListCurrNode() = CSS_GetAsScanBandListHeadNode();
    CSS_GetAsScanCurFreqRangeIdx()  = CSS_NULL;

    if (0 == CSS_GetAsScanBandListAddr()->ucBandCount)
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAsBandScanReqest_ENUM, LNAS_BandCountIsZero);
        return CSS_FAIL;
    }
    return CSS_SUCC;
}


VOS_UINT32  CSS_ProcLphyBandScanRsltForAsScan(const CSS_LPHY_BAND_SCAN_RESULT_LIST_STRU *pstLphyBandScanRslt)
{
    CSS_COMM_SCAN_BAND_NODE_STRU            *pstBandNode;
    VOS_UINT16                               usNum;
    CSS_FREQ_RANGE_STRU                     *pTmpAddr;

    pstBandNode = CSS_GetAsScanBandListCurrNode();
    if (CSS_NULL_PTR == pstBandNode)
    {
        return CSS_CAUSE_NULL_PTR;
    }

    if (CSS_NULL == pstLphyBandScanRslt->usFreqRangeNum)
    {
        return CSS_FAIL;
    }


    TLPS_PRINT2LAYER_INFO1(CSS_ProcLphyBandScanRsltForAsScan_ENUM, LNAS_BandInd, pstLphyBandScanRslt->enBandInd);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcLphyBandScanRsltForAsScan_ENUM, LNAS_FreqRangeNum, pstLphyBandScanRslt->usFreqRangeNum);

    usNum = pstBandNode->stBandInfo.ucScanRsltArrayCount + pstLphyBandScanRslt->usFreqRangeNum;

    /* 申请空间 */
    pTmpAddr                  = CSS_MEM_ALLOC(usNum*sizeof(CSS_FREQ_RANGE_STRU));
    if (CSS_NULL_PTR == pTmpAddr)
    {
        return CSS_FAIL;
    }

    if ((CSS_NULL_PTR != pstBandNode->stBandInfo.pstScanRsltArray)
        && (CSS_NULL != pstBandNode->stBandInfo.ucScanRsltArrayCount))
    {
        CSS_MEM_CPY_S(  pTmpAddr,
                        usNum*sizeof(CSS_FREQ_RANGE_STRU),
                        pstBandNode->stBandInfo.pstScanRsltArray,
                        pstBandNode->stBandInfo.ucScanRsltArrayCount * sizeof(CSS_FREQ_RANGE_STRU));
        CSS_MEM_CPY_S(  pTmpAddr+pstBandNode->stBandInfo.ucScanRsltArrayCount,
                        (usNum - pstBandNode->stBandInfo.ucScanRsltArrayCount)*sizeof(CSS_FREQ_RANGE_STRU),
                        pstLphyBandScanRslt->astFreqScanResult,
                        pstLphyBandScanRslt->usFreqRangeNum * sizeof(CSS_FREQ_RANGE_STRU));
    }
    else
    {
        CSS_MEM_CPY_S(  pTmpAddr,
                        usNum*sizeof(CSS_FREQ_RANGE_STRU),
                        pstLphyBandScanRslt->astFreqScanResult,
                        pstLphyBandScanRslt->usFreqRangeNum * sizeof(CSS_FREQ_RANGE_STRU));
    }

    if (CSS_NULL_PTR != pstBandNode->stBandInfo.pstScanRsltArray)
    {
        CSS_MEM_FREE(pstBandNode->stBandInfo.pstScanRsltArray);
    }

    pstBandNode->stBandInfo.ucScanRsltArrayCount = (VOS_UINT8)usNum;
    pstBandNode->stBandInfo.pstScanRsltArray = pTmpAddr;

    return CSS_SUCC;
}



VOS_UINT32 CSS_IsAsScanNeedSndLphyNextBandScanReq(VOS_VOID)
{
    CSS_COMM_SCAN_BAND_NODE_STRU            *pstBandNode;

    pstBandNode                              = CSS_GetAsScanBandListCurrNode();

    /*如果当前BAND的频段没有扫完，则继续扫下一个频段*/
    if (CSS_GetAsScanCurFreqRangeIdx() < pstBandNode->stBandInfo.ucScanReqCount-1)
    {
        CSS_GetAsScanCurFreqRangeIdx() ++;
        return CSS_TRUE;
    }
    /*如果当前BAND的频段已扫完*/
    else
    {
        /*如果BAND还没有遍历完*/
        if (CSS_NULL_PTR != pstBandNode->pstNext)
        {
            CSS_GetAsScanBandListCurrNode() = pstBandNode->pstNext;
            CSS_GetAsScanCurFreqRangeIdx()  = CSS_NULL;
            return CSS_TRUE;
        }
    }

    return CSS_FALSE;
}





VOS_UINT32  CSS_ProcLphyBandScanRsltForCommScan(const CSS_LPHY_BAND_SCAN_RESULT_LIST_STRU *pstLphyBandScanRslt)
{
    CSS_COMM_SCAN_BAND_NODE_STRU            *pstBandNode;
    VOS_UINT16                               usNum;
    VOS_UINT16                               ucLoop;
    CSS_FREQ_RANGE_STRU                     *pTmpAddr;
    VOS_INT16                                sThreshold     = CSS_NULL;
    VOS_UINT16                               usFreqRangeNum = CSS_NULL;
    CSS_LPHY_FREQ_INFO_STRU                  astFreqScanResult[CSS_LPHY_MAX_FREQ_NUM]={{0}};

    pstBandNode                              = CSS_GetCommScanBandListCurrNode();
    if (CSS_NULL_PTR == pstBandNode)
    {
        return CSS_CAUSE_NULL_PTR;
    }

    if (CSS_NULL == pstLphyBandScanRslt->usFreqRangeNum)
    {
        return CSS_FAIL;
    }

    TLPS_PRINT2LAYER_INFO1(CSS_ProcLphyBandScanRslt_ENUM, LNAS_BandInd, pstLphyBandScanRslt->enBandInd);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcLphyBandScanRslt_ENUM, LNAS_FreqRangeNum, pstLphyBandScanRslt->usFreqRangeNum);

    /*根据门限过滤*/
    sThreshold     = CSS_GetThreshold();
    for (ucLoop=0; ucLoop<pstLphyBandScanRslt->usFreqRangeNum; ++ucLoop)
    {
        if (pstLphyBandScanRslt->astFreqScanResult[ucLoop].lRssi >= sThreshold)
        {
            astFreqScanResult[usFreqRangeNum].lRssi           = pstLphyBandScanRslt->astFreqScanResult[ucLoop].lRssi;
            astFreqScanResult[usFreqRangeNum].usCentralFreq   = pstLphyBandScanRslt->astFreqScanResult[ucLoop].usCentralFreq;
            usFreqRangeNum++;
        }
    }


    usNum                     = (VOS_UINT16)pstBandNode->stBandInfo.ucScanRsltArrayCount + usFreqRangeNum;

    if (CSS_NULL == usNum)
    {
        return CSS_FAIL;
    }

    /*申请空间，将二者合在一起*/
    pTmpAddr                  = CSS_MEM_ALLOC(usNum*sizeof(CSS_FREQ_RANGE_STRU));
    if (CSS_NULL_PTR == pTmpAddr)
    {
        return CSS_FAIL;
    }

    if ((CSS_NULL_PTR != pstBandNode->stBandInfo.pstScanRsltArray)
        && (CSS_NULL != pstBandNode->stBandInfo.ucScanRsltArrayCount))
    {
        CSS_MEM_CPY_S(  pTmpAddr,
                        usNum * sizeof(CSS_FREQ_RANGE_STRU),
                        pstBandNode->stBandInfo.pstScanRsltArray,
                        pstBandNode->stBandInfo.ucScanRsltArrayCount * sizeof(CSS_FREQ_RANGE_STRU));
        CSS_MEM_CPY_S(  pTmpAddr+pstBandNode->stBandInfo.ucScanRsltArrayCount,
                        usFreqRangeNum * sizeof(CSS_FREQ_RANGE_STRU),
                        astFreqScanResult,
                        usFreqRangeNum * sizeof(CSS_FREQ_RANGE_STRU));
    }
    else
    {
        CSS_MEM_CPY_S(  pTmpAddr,
                        usNum * sizeof(CSS_FREQ_RANGE_STRU),
                        astFreqScanResult,
                        usFreqRangeNum * sizeof(CSS_FREQ_RANGE_STRU));
    }

    /* 对结果进行快速排序 */
    /*lint -e586*/
    qsort(pTmpAddr, usNum, sizeof(CSS_FREQ_RANGE_STRU), (CSS_COMP_FUNC)CSS_RssiCompare);
    /*lint +e586*/

    /* 如果总个数大于20个，只取20 */
    if (CSS_MAX_BAND_FREQ_RANGE_NUM < usNum)
    {
        usNum = CSS_MAX_BAND_FREQ_RANGE_NUM;
    }


    /* 如果原有空间大小与结果大小不同，需要重新申请空间 */
    if (usNum != pstBandNode->stBandInfo.ucScanRsltArrayCount)
    {
        if (CSS_NULL_PTR != pstBandNode->stBandInfo.pstScanRsltArray)
        {
            (VOS_VOID)CSS_MEM_FREE(pstBandNode->stBandInfo.pstScanRsltArray);
        }
        pstBandNode->stBandInfo.pstScanRsltArray   = CSS_MEM_ALLOC(usNum*sizeof(CSS_FREQ_RANGE_STRU));
        if (CSS_NULL_PTR == pstBandNode->stBandInfo.pstScanRsltArray)
        {
            (VOS_VOID)CSS_MEM_FREE(pTmpAddr);
            return CSS_FAIL;
        }
    }

    /* 给新的空间赋值 */
    CSS_MEM_CPY_S(  pstBandNode->stBandInfo.pstScanRsltArray,
                    usNum * sizeof(CSS_FREQ_RANGE_STRU),
                    pTmpAddr,
                    usNum * sizeof(CSS_FREQ_RANGE_STRU));

    pstBandNode->stBandInfo.ucScanRsltArrayCount   = (VOS_UINT8)usNum;

    TLPS_PRINT2LAYER_INFO1(CSS_ProcLphyBandScanRslt_ENUM, LNAS_ScanRsltArrayCount, usNum);

    (VOS_VOID)CSS_MEM_FREE(pTmpAddr);
    return CSS_SUCC;
}




VOS_UINT32 CSS_IsCommScanNeedSndLphyNextBandScanReq(VOS_VOID)
{
    CSS_COMM_SCAN_BAND_NODE_STRU            *pstBandNode;

    pstBandNode                              = CSS_GetCommScanBandListCurrNode();

    /*如果当前BAND的频段没有扫完，则继续扫下一个频段*/
    if (CSS_GetCommScanCurFreqRangeIdx() < pstBandNode->stBandInfo.ucScanReqCount-1)
    {
        CSS_GetCommScanCurFreqRangeIdx() ++;
        return CSS_TRUE;
    }
    /*如果当前BAND的频段已扫完*/
    else
    {
        /*如果BAND还没有遍历完*/
        if (CSS_NULL_PTR != pstBandNode->pstNext)
        {
            CSS_GetCommScanBandListCurrNode() = pstBandNode->pstNext;
            CSS_GetCommScanCurFreqRangeIdx()  = CSS_NULL;
            return CSS_TRUE;
        }
    }

    return CSS_FALSE;
}

/*****************************************************************************
 Function Name   : CSS_GetOneGsmBandScanInfo
 Description     : 获取G的band信息
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.wangchen 00209181     2015-06-04  Draft Enact
*****************************************************************************/
VOS_VOID CSS_GetOneRatBandScanInfo
(
    CSS_BAND_SCAN_LIST_INFO_STRU    *pstCssBandInfo,
    VOS_UINT8                       *pucBandNum,
    CSS_COMM_SCAN_BAND_NODE_STRU    *pBandNode,
    VOS_UINT8                       ucRatSupportFlag,
    VOS_INT16                       sRssiThresHold
)
{
    VOS_UINT8                           ucBandNum  = *pucBandNum;
    VOS_UINT16                          ucLoop;
    VOS_UINT16                          usFreqNum = pstCssBandInfo->astScanRange[ucBandNum].usFreqNum;
    /* c00285307 add for 多制式和重叠频段BAND优化 Begin */
    CSS_CONTROL_STRU                   *pstCssControl;

    pstCssControl = CSS_GetControlAddr();
    /* c00285307 add for 多制式和重叠频段BAND优化 End */

    if (CSS_MAX_BAND_NUM <= ucBandNum)
    {
        return;
    }

    if ((CSS_OP_TRUE == ucRatSupportFlag)
        && (CSS_NULL != pBandNode->stBandInfo.ucScanRsltArrayCount))
    {
        for (ucLoop = 0; ucLoop < pBandNode->stBandInfo.ucScanRsltArrayCount; ++ucLoop)
        {
            if (pBandNode->stBandInfo.pstScanRsltArray[ucLoop].sRssi >= sRssiThresHold)
            {
                pstCssBandInfo->astScanRange[ucBandNum].astFreqScanResult[usFreqNum].sRssi           = pBandNode->stBandInfo.pstScanRsltArray[ucLoop].sRssi;
                pstCssBandInfo->astScanRange[ucBandNum].astFreqScanResult[usFreqNum].usCentralFreq   = pBandNode->stBandInfo.pstScanRsltArray[ucLoop].usCentralFreq;
                ++usFreqNum;
            }
            else
            {
                break;
            }
        }
        pstCssBandInfo->astScanRange[ucBandNum].usFreqNum = usFreqNum;

        /* 如果存在高能量的频点，则BAND的个数增加 */
        if (CSS_NULL != pstCssBandInfo->astScanRange[ucBandNum].usFreqNum)
        {
            pstCssBandInfo->astScanRange[ucBandNum].enBandInd          = pBandNode->stBandInfo.ucBandInd;

            /*按中心频率从小到大快速排序*/
            /*lint -e586*/
            qsort(pstCssBandInfo->astScanRange[ucBandNum].astFreqScanResult,
                  pstCssBandInfo->astScanRange[ucBandNum].usFreqNum,
                  sizeof(CSS_FREQ_RANGE_STRU),
                  (CSS_COMP_FUNC)CSS_FreqCompare);
            /*lint +e586*/

            /* c00285307 add for 多制式和重叠频段BAND优化 Begin */
            if (CSS_OP_TRUE == pBandNode->stBandInfo.bitOpGsmSupport)
            {
                pstCssControl->aucRatSupportFlag[ucBandNum] |= CSS_GSM_SUPORT_OP;
            }
            if (CSS_OP_TRUE == pBandNode->stBandInfo.bitOpWcdmaSupport)
            {
                pstCssControl->aucRatSupportFlag[ucBandNum] |= CSS_WCDMA_SUPORT_OP;
            }
            if (CSS_OP_TRUE == pBandNode->stBandInfo.bitOpLteSupport)
            {
                pstCssControl->aucRatSupportFlag[ucBandNum] |= CSS_LTE_SUPORT_OP;
            }
            /* c00285307 add for 多制式和重叠频段BAND优化 End */

            ucBandNum ++;
            *pucBandNum = ucBandNum;
        }

    }
}


VOS_VOID CSS_GetOneBandScanInfo
(
    CSS_RAT_COVERAGE_STRU           stRatCoverage,
    CSS_BAND_SCAN_LIST_INFO_STRU    *pstCssBandInfo,
    VOS_UINT8                       *pucBandNum,
    CSS_COMM_SCAN_BAND_NODE_STRU    *pBandNode
)
{
    CSS_CONTROL_STRU                   *pstCssControl = CSS_GetControlAddr();

    switch(stRatCoverage.enRatType)
    {
        case CSS_RAT_GSM:
            if (CSS_COVERAGE_TYPE_HIGH == stRatCoverage.enCoverageType)
            {
                CSS_GetOneRatBandScanInfo(  pstCssBandInfo, pucBandNum, pBandNode,
                                            pBandNode->stBandInfo.bitOpGsmSupport,
                                            pstCssControl->stRssiThreshold.sGHighRssiThresHold);
            }
            else
            {
                CSS_GetOneRatBandScanInfo(  pstCssBandInfo, pucBandNum, pBandNode,
                                            pBandNode->stBandInfo.bitOpGsmSupport,
                                            pstCssControl->stRssiThreshold.sGLowRssiThresHold);
            }
            break;

        case CSS_RAT_UMTS_FDD:
            if (CSS_COVERAGE_TYPE_HIGH == stRatCoverage.enCoverageType)
            {
                CSS_GetOneRatBandScanInfo(  pstCssBandInfo, pucBandNum, pBandNode,
                                            pBandNode->stBandInfo.bitOpWcdmaSupport,
                                            pstCssControl->stRssiThreshold.sWHighRssiThresHold);
            }
            else
            {
                CSS_GetOneRatBandScanInfo(  pstCssBandInfo, pucBandNum, pBandNode,
                                            pBandNode->stBandInfo.bitOpWcdmaSupport,
                                            pstCssControl->stRssiThreshold.sWLowRssiThresHold);
            }
            break;

        case CSS_RAT_LTE:
            if (CSS_COVERAGE_TYPE_HIGH == stRatCoverage.enCoverageType)
            {
                CSS_GetOneRatBandScanInfo(  pstCssBandInfo, pucBandNum, pBandNode,
                                            pBandNode->stBandInfo.bitOpLteSupport,
                                            pstCssControl->stRssiThreshold.sLHighRssiThresHold);
            }
            else
            {
                CSS_GetOneRatBandScanInfo(  pstCssBandInfo, pucBandNum, pBandNode,
                                            pBandNode->stBandInfo.bitOpLteSupport,
                                            pstCssControl->stRssiThreshold.sLLowRssiThresHold);
            }
            break;

        default:
            break;
    }
}



/* 提供给外部调用，获取上次扫频结果的API。
stRatList:获取哪个接入技术下的扫频结果；
pCssBandInfo：外部模块传入存储扫频结果的地址，该内存由调用者分配，以及释放 */

CSS_RESULT_ENUM_UINT32 CSS_GetBandScanInfo
(
    CSS_RAT_COVERAGE_STRU stRatCoverage,
    CSS_BAND_SCAN_LIST_INFO_STRU* pstCssBandInfo
)
{
    VOS_UINT8                             ucRealBandNum = CSS_NULL;
    VOS_UINT8                             ucBandNodeNum = CSS_NULL;
    CSS_MAIN_STATE_ENUM_UINT16            enMainState        = CSS_MAIN_STATE_BUTT;    /* 当前处于的主状态 */
    CSS_SUB_STATE_ENUM_UINT16             enSubState         = CSS_SS_STATE_BUTT;      /* 当前处于的子状态 */
    CSS_COMM_SCAN_BAND_NODE_STRU         *pBandNode;

    pBandNode   = CSS_GetCommScanBandListHeadNode();
    enMainState = CSS_GetCurMainStatus();
    enSubState  = CSS_GetCurSubStatus();

    /* 状态不对，返回 */
    if (CSS_MS_IDLE != enMainState || CSS_SS_IDLE != enSubState)
    {
        CSS_WARN_LOG("CSS_GetBandScanInfo SCANING OR STOP SCANING");
        TLPS_PRINT2LAYER_WARNING(CSS_GetBandScanInfo_ENUM, LNAS_FUNCTION_LABEL1);
        return CSS_RESULT_FAIL;
    }

    if (CSS_NULL_PTR == pstCssBandInfo)
    {
        CSS_WARN_LOG("CSS_GetBandScanInfo pstCssBandInfo IS NULL");
        TLPS_PRINT2LAYER_WARNING(CSS_GetBandScanInfo_ENUM, LNAS_FUNCTION_LABEL2);
        return CSS_RESULT_FAIL;
    }

    /* 如果请求无覆盖类型，则直接退出，并返回失败 */
    if ((CSS_COVERAGE_TYPE_LOW != stRatCoverage.enCoverageType) &&
        (CSS_COVERAGE_TYPE_HIGH != stRatCoverage.enCoverageType))
    {
        CSS_WARN_LOG("CSS_GetBandScanInfo stRatCoverage is none");
        TLPS_PRINT2LAYER_WARNING(CSS_GetBandScanInfo_ENUM, LNAS_FUNCTION_LABEL3);
        return CSS_RESULT_FAIL;
    }

    /* 对传进的内存初始化为0 */
    CSS_MEM_SET_S(pstCssBandInfo, sizeof(CSS_BAND_SCAN_LIST_INFO_STRU), 0, sizeof(CSS_BAND_SCAN_LIST_INFO_STRU));

    /*对所有BAND指针节点循环*/
    while ((CSS_NULL_PTR != pBandNode)
           && (ucBandNodeNum < CSS_GetCommScanBandListAddr()->ucBandCount))
    {
        /* 对单个BAND节点进行处理 */
        CSS_GetOneBandScanInfo(stRatCoverage, pstCssBandInfo, &ucRealBandNum, pBandNode);
        /* 处理完后指针指向下一结点 */
        pBandNode      = pBandNode->pstNext;
        ucBandNodeNum  += 1;
    }

    pstCssBandInfo->ucBandNum = ucRealBandNum;

    CSS_SendOmBandApiInfoInd(&stRatCoverage, pstCssBandInfo);

    TLPS_PRINT2LAYER_WARNING1(CSS_GetBandScanInfo_ENUM, LNAS_BandNum, pstCssBandInfo->ucBandNum);

    if (0 == pstCssBandInfo->ucBandNum)
    {
        return CSS_RESULT_FAIL;
    }

    /* c00285307 add for 多制式和重叠频段BAND优化 Begin */
    /* 对扫频结果重新排序，将支持最少制式的BAND放最前面，支持更多制式的BAND放后面 */
    CSS_SortRsltByRatSupport(pstCssBandInfo, CSS_GetControlAddr()->aucRatSupportFlag);

    /* 将与扫频结果中有重叠频段的BAND新增在扫频结果中 */
    CSS_AddOverlapBandToRslt(&stRatCoverage, pstCssBandInfo);
    /* c00285307 add for 多制式和重叠频段BAND优化 End */

    CSS_SendOmBandApiInfoInd(&stRatCoverage, pstCssBandInfo);

    return CSS_RESULT_SUCC;
}


/*****************************************************************************
 Function Name   : CSS_SortRsltByRatSupport
 Description     : 对扫频结果重新排序，将支持最少制式的BAND放最前面，支持更多制式的BAND放后面
 Input           : pstCssBandInfo   - 扫频结果指针
                   pcRatSupportFlag - BAND的各制式支持能力
 Output          : pstCssBandInfo   - 排序后的扫频结果指针
 Return          : None
 History         :
    1.    chengmin 00285307      2015-07-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_SortRsltByRatSupport
(
    CSS_BAND_SCAN_LIST_INFO_STRU       *pstCssBandInfo,
    VOS_UINT8                          *pcRatSupportFlag
)
{
    /*lint -e813*/
    CSS_BAND_SCAN_LIST_INFO_STRU        stCssBandRslt       = {0};
    /*lint +e813*/
    VOS_UINT32                          ulLoop              = 0;
    VOS_UINT8                           ucNum               = 0;

    /* 拷贝内存用来判断 */
    CSS_MEM_CPY_S(  &stCssBandRslt,
                    sizeof(CSS_BAND_SCAN_LIST_INFO_STRU),
                    pstCssBandInfo,
                    sizeof(CSS_BAND_SCAN_LIST_INFO_STRU));
    /* 将需要操作的内存先初始化 */
    CSS_MEM_SET_S(pstCssBandInfo,
                    sizeof(CSS_BAND_SCAN_LIST_INFO_STRU),
                    0,
                    sizeof(CSS_BAND_SCAN_LIST_INFO_STRU));

    /* 找只支持1个制式的 */
    for (ulLoop = 0; ulLoop < stCssBandRslt.ucBandNum; ++ulLoop)
    {
        if (CSS_GSM_SUPORT_OP == pcRatSupportFlag[ulLoop]
            || CSS_WCDMA_SUPORT_OP == pcRatSupportFlag[ulLoop]
            || CSS_LTE_SUPORT_OP == pcRatSupportFlag[ulLoop])
        {
            CSS_MEM_CPY_S(  &(pstCssBandInfo->astScanRange[ucNum]), \
                            sizeof(CSS_BAND_SCAN_INFO_STRU), \
                            &(stCssBandRslt.astScanRange[ulLoop]), \
                            sizeof(CSS_BAND_SCAN_INFO_STRU));

            ucNum += 1;
        }
    }

    /* 找只支持2个制式的 */
    for (ulLoop = 0; ulLoop < stCssBandRslt.ucBandNum; ++ulLoop)
    {
        if ((CSS_GSM_SUPORT_OP | CSS_WCDMA_SUPORT_OP) == pcRatSupportFlag[ulLoop]
            || (CSS_GSM_SUPORT_OP | CSS_LTE_SUPORT_OP) == pcRatSupportFlag[ulLoop]
            || (CSS_WCDMA_SUPORT_OP | CSS_LTE_SUPORT_OP) == pcRatSupportFlag[ulLoop])
        {
            CSS_MEM_CPY_S(  &(pstCssBandInfo->astScanRange[ucNum]), \
                            sizeof(CSS_BAND_SCAN_INFO_STRU), \
                            &(stCssBandRslt.astScanRange[ulLoop]), \
                            sizeof(CSS_BAND_SCAN_INFO_STRU));

            ucNum += 1;
        }
    }

    /* 找只支持3个制式的 */
    for (ulLoop = 0; ulLoop < stCssBandRslt.ucBandNum; ++ulLoop)
    {
        if ((CSS_GSM_SUPORT_OP | CSS_WCDMA_SUPORT_OP | CSS_LTE_SUPORT_OP) == pcRatSupportFlag[ulLoop])
        {
            CSS_MEM_CPY_S(  &(pstCssBandInfo->astScanRange[ucNum]), \
                            sizeof(CSS_BAND_SCAN_INFO_STRU), \
                            &(stCssBandRslt.astScanRange[ulLoop]), \
                            sizeof(CSS_BAND_SCAN_INFO_STRU));

            ucNum += 1;
        }
    }

    pstCssBandInfo->ucBandNum = ucNum;
}

/*****************************************************************************
 Function Name   : CSS_AddBandToRslt
 Description     : 将需要新增的扫频结果加入目标数组中
 Input           : pstSour - 源结果
                   usBand  - 新加入的BAND值
 Output          : pstDest - 目标结果
 Return          : None
 History         :
    1.    chengmin 00285307      2015-07-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddBandToRslt
(
    CSS_RAT_COVERAGE_STRU                        *pstRatCoverage,
    CSS_BAND_SCAN_LIST_INFO_STRU                 *pstDest,
    CSS_BAND_SCAN_INFO_STRU                      *pstSour,
    VOS_UINT16                                    usBand,
    VOS_UINT32                                    ulBandIndex
)
{
    VOS_UINT16                          usFreqBegin;
    VOS_UINT16                          usFreqEnd;
    VOS_UINT32                          ulLoop;
    VOS_UINT16                          usCentralFreq;
    VOS_INT16                           sRssi;
    VOS_UINT16                          usNowFreqNum  = 0;
    CSS_CONTROL_STRU                   *pstCssControl = CSS_GetControlAddr();


    /* 获取新增BAND的频率范围 */
    usFreqBegin     = g_ausCssLteBandFreq[usBand-1].usFreqBegin;
    usFreqEnd       = g_ausCssLteBandFreq[usBand-1].usFreqEnd;


    /* 遍历每个频段 */
    for (ulLoop = 0; ulLoop < pstSour->usFreqNum; ++ulLoop)
    {
        usCentralFreq  = pstSour->astFreqScanResult[ulLoop].usCentralFreq;
        sRssi          = pstSour->astFreqScanResult[ulLoop].sRssi;

        /* 如果中心频率在新增的BAND的频段范围内，则加入 */
        if (usFreqBegin <= usCentralFreq
            && usFreqEnd >= usCentralFreq)
        {
            pstDest->astScanRange[pstDest->ucBandNum].enBandInd = usBand;
            pstDest->astScanRange[pstDest->ucBandNum].astFreqScanResult[usNowFreqNum].usCentralFreq = usCentralFreq;
            pstDest->astScanRange[pstDest->ucBandNum].astFreqScanResult[usNowFreqNum].sRssi = sRssi;
            usNowFreqNum += 1;
        }
    }

    /* 若加入的频段个数不为0，则将最终结果BAND个数加1 */
    if (0 != usNowFreqNum)
    {
        /* 将该BAND的各制式支持情况加入 */
        if (CSS_RAT_GSM == pstRatCoverage->enRatType)
        {
            pstCssControl->aucRatSupportFlag[pstDest->ucBandNum] = CSS_GSM_SUPORT_OP;
        }
        else if (CSS_RAT_UMTS_FDD == pstRatCoverage->enRatType)
        {
            pstCssControl->aucRatSupportFlag[pstDest->ucBandNum] = CSS_WCDMA_SUPORT_OP;
        }
        else if (CSS_RAT_LTE == pstRatCoverage->enRatType)
        {
            pstCssControl->aucRatSupportFlag[pstDest->ucBandNum] = CSS_LTE_SUPORT_OP;
        }
        else
        {
        }

        /* 将频段个数赋值 */
        pstDest->astScanRange[pstDest->ucBandNum].usFreqNum = usNowFreqNum;
        pstDest->ucBandNum += 1;
    }
}


/*****************************************************************************
 Function Name   : CSS_AddOverlapBandToRslt
 Description     : 将与扫频结果有重叠频段的BAND新增到扫频结果中
 Input           : pstRatCoverage - 请求扫频结果的参数
                   pstCssBandInfo - 扫频结果指针
 Output          : pstCssBandInfo - 扫频结果指针
 Return          : None
 History         :
    1.    chengmin 00285307      2015-07-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddOverlapBandToRslt
(
    CSS_RAT_COVERAGE_STRU              *pstRatCoverage,
    CSS_BAND_SCAN_LIST_INFO_STRU       *pstCssBandInfo
)
{
    /*lint -e813*/
    CSS_BAND_SCAN_LIST_INFO_STRU        stCssBandRslt       = {0};
    /*lint +e813*/
    VOS_UINT32                          ulLoop1             = 0;
    VOS_UINT32                          ulLoop2             = 0;

    /* 如果当前结果已经满了，不加入 */
    if (CSS_MAX_BAND_NUM == pstCssBandInfo->ucBandNum)
    {
        return;
    }

    /* 拷贝一份内存用于遍历 */
    CSS_MEM_CPY_S(  &stCssBandRslt,
                    sizeof(CSS_BAND_SCAN_LIST_INFO_STRU),
                    pstCssBandInfo,
                    sizeof(CSS_BAND_SCAN_LIST_INFO_STRU));

    /* 遍历扫频结果中的每个BAND */
    for (ulLoop1 = 0; ulLoop1 < stCssBandRslt.ucBandNum; ++ulLoop1)
    {
        /* 对于每个BAND，遍历全局共频率数组，看看是否有共频率BAND */
        for (ulLoop2 = 0; ulLoop2 < g_aucOverLapBandSize; ++ulLoop2)
        {
            /* 找到共频段的BAND */
            if (stCssBandRslt.astScanRange[ulLoop1].enBandInd  == g_aucOverLapBand[ulLoop2].ucBand1)
            {
                /* 判断是否需要加入 */
                if (CSS_TRUE == CSS_IsNeedAddToRslt(pstCssBandInfo,
                                                    pstRatCoverage,
                                                    g_aucOverLapBand[ulLoop2].ucBand2))
                {
                    CSS_AddBandToRslt(  pstRatCoverage,
                                        pstCssBandInfo,
                                        &(stCssBandRslt.astScanRange[ulLoop1]),
                                        g_aucOverLapBand[ulLoop2].ucBand2,
                                        ulLoop1);
                }
            }
            if (stCssBandRslt.astScanRange[ulLoop1].enBandInd  == g_aucOverLapBand[ulLoop2].ucBand2)
            {
                /* 判断是否需要加入 */
                if (CSS_TRUE == CSS_IsNeedAddToRslt(pstCssBandInfo,
                                                    pstRatCoverage,
                                                    g_aucOverLapBand[ulLoop2].ucBand1))
                {
                    CSS_AddBandToRslt(  pstRatCoverage,
                                        pstCssBandInfo,
                                        &(stCssBandRslt.astScanRange[ulLoop1]),
                                        g_aucOverLapBand[ulLoop2].ucBand1,
                                        ulLoop1);
                }
            }
        }
    }
}

/*****************************************************************************
 Function Name   : CSS_IsUeSupportBandByReq
 Description     : 根据UE的能力和请求参数来判断是否需要新增到扫频结果中
 Input           : pstRatCoverage - 请求扫频结果的参数
                   ucBand         - 新增BAND的值
 Output          : None
 Return          : 是否需要加入
 History         :
    1.    chengmin 00285307      2015-07-15  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsUeSupportBandByReq
(
    CSS_RAT_COVERAGE_STRU              *pstRatCoverage,
    VOS_UINT16                          ucBand
)
{
    NAS_MML_MS_BAND_INFO_STRU          *pstUserSetBand      = CSS_NULL_PTR;
    VOS_UINT8                           ucSuportFlag        = 0;

    /* 获取UE实际支持的BAND */
    pstUserSetBand  = NAS_MML_GetMsSupportBand();
    if (CSS_NULL_PTR == pstUserSetBand)
    {
        return CSS_FALSE;
    }

    /* 根据请求的参数来获取是否支持该BAND */
    if (CSS_RAT_GSM == pstRatCoverage->enRatType)
    {
        CSS_GetGsmSuportFlag((VOS_UINT8)ucBand, CSS_OP_TRUE, pstUserSetBand, CSS_GSM_SUPORT_OP, &ucSuportFlag);
    }
    else if (CSS_RAT_UMTS_FDD == pstRatCoverage->enRatType)
    {
        CSS_GetWcdmaSuportFlag((VOS_UINT8)ucBand, CSS_OP_TRUE, pstUserSetBand, CSS_WCDMA_SUPORT_OP, &ucSuportFlag);
    }
    else if (CSS_RAT_LTE == pstRatCoverage->enRatType)
    {
        CSS_GetLteSuportFlag((VOS_UINT8)ucBand, CSS_OP_TRUE, pstUserSetBand, CSS_LTE_SUPORT_OP, &ucSuportFlag);
    }
    else
    {
    }

    if (0 == ucSuportFlag)
    {
        return CSS_FALSE;
    }

    return CSS_TRUE;
}


/*****************************************************************************
 Function Name   : CSS_IsNeedAddToRslt
 Description     : 判断是否需要将该有重叠频段的BAND新增到扫频结果中
 Input           : pstRatCoverage - 请求扫频结果的参数
                   pstCssBandInfo - 扫频结果指针
                   ucBand         - 新增的共频段的BAND值
 Output          : None
 Return          : 是否需要加入
 History         :
    1.    chengmin 00285307      2015-07-15  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsNeedAddToRslt
(
    CSS_BAND_SCAN_LIST_INFO_STRU       *pstCssBandInfo,
    CSS_RAT_COVERAGE_STRU              *pstRatCoverage,
    VOS_UINT16                          ucBand
)
{
    VOS_UINT32                          ulLoop              = 0;

    /* 如果当前结果已经满了，不加入 */
    if (CSS_MAX_BAND_NUM == pstCssBandInfo->ucBandNum)
    {
        return CSS_FALSE;
    }

    /* 判断共频段的BAND是否已经在结果中 */
    for (ulLoop = 0; ulLoop < pstCssBandInfo->ucBandNum; ++ulLoop)
    {
        /* 已经在结果中 */
        if (pstCssBandInfo->astScanRange[ulLoop].enBandInd == ucBand)
        {
            return CSS_FALSE;
        }
    }
    /* 根据UE能力是否支持来判断 */
    if (CSS_FALSE == CSS_IsUeSupportBandByReq(pstRatCoverage, ucBand))
    {
        return CSS_FALSE;
    }

    return CSS_TRUE;
}





#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif





