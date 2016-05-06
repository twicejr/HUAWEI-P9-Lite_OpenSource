/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsDecode.c
  版 本 号   : 初稿
  作    者   : 谷传征
  生成日期   : 2015年7月14日
  最近修改   :
  功能描述   : Modem Decode Msg From PDE server
  函数列表   :
  修改历史   :
  1.日    期   : 2015年7月14日
    作    者   : g00261581
    修改内容   : CDMA-AGPS项目新增

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID                 PS_FILE_ID_TAF_XPDS_DECODE_C

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "TafXpdsDecode.h"
#include "TafXpdsMntn.h"
#include "TafMtaTimerMgmt.h"
#include "TafXpdsSndAt.h"
#include "TafXpdsCommFunc.h"

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 Global variable
*****************************************************************************/
TAF_XPDS_DECODE_REQ_MSG_HANDLER_STRU  g_astTafXpdsDecodeReqMsgHdlTbl[] = {
    {TAF_XPDS_FL_MSGTYPE_REQ_LOCATION_INFO,            TAF_XPDS_DecodeRequestLocResp},
    {TAF_XPDS_FL_MSGTYPE_REQ_MS_INFO,                  TAF_XPDS_DecodeRequestMsInfo},
    {TAF_XPDS_FL_MSGTYPE_REQ_PSEUDORANGE_MEAS,         TAF_XPDS_DecodeRequestPseudoRangeMeas},
    {TAF_XPDS_FL_MSGTYPE_REQ_PILOT_PHASE_MEAS,         TAF_XPDS_DecodeRequestPilotPhaseMeas},
    {TAF_XPDS_FL_MSGTYPE_REQ_CANCELLATION,             TAF_XPDS_DecodeRequestCancellation}
};

TAF_XPDS_DECODE_RESP_HANDLER_STRU  g_astTafXpdsDecodeRespMsgHdlTbl[] = {
    {TAF_XPDS_FL_MSGTYPE_RSP_REJECT,                   TAF_XPDS_DecodeReject},
    {TAF_XPDS_FL_MSGTYPE_RSP_PROV_LOCATION_RESPONSE,   TAF_XPDS_DecodeProvLocResp},
    {TAF_XPDS_FL_MSGTYPE_RSP_PROV_ACQ_ASSISTANCE,      TAF_XPDS_DecodeProvGpsAcqAssist},
    {TAF_XPDS_FL_MSGTYPE_RSP_PROV_GPS_ALMANAC,         TAF_XPDS_DecodeProvGpsAlmanac},
    {TAF_XPDS_FL_MSGTYPE_RSP_PROV_GPS_EPHEMERIS,       TAF_XPDS_DecodeProvGpsEphimeries}
};

TAF_XPDS_DECODE_MSG_TYPE_MAP_DATA_MASK_STRU  g_astTafXpdsDecodeRespTypeMapDataMaskTbl[] = {
    {TAF_XPDS_FL_MSGTYPE_RSP_REJECT,                   TAF_XPDS_RCV_PDE_DATA_MASK_RSP_REJECT},
    {TAF_XPDS_FL_MSGTYPE_RSP_PROV_LOCATION_RESPONSE,   TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_LOC_RSP},
    {TAF_XPDS_FL_MSGTYPE_RSP_PROV_ACQ_ASSISTANCE,      TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_ACQ_ASSIST},
    {TAF_XPDS_FL_MSGTYPE_RSP_PROV_GPS_EPHEMERIS,       TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_EPH},
    {TAF_XPDS_FL_MSGTYPE_RSP_PROV_GPS_ALMANAC,         TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_ALM},
};

TAF_XPDS_DECODE_MSG_TYPE_MAP_DATA_MASK_STRU  g_astTafXpdsDecodeReqTypeMapDataMaskTbl[] = {
    {TAF_XPDS_FL_MSGTYPE_REQ_LOCATION_INFO,            TAF_XPDS_RCV_PDE_DATA_MASK_REQ_LOC_INFO},
    {TAF_XPDS_FL_MSGTYPE_REQ_MS_INFO,                  TAF_XPDS_RCV_PDE_DATA_MASK_REQ_MS_INFO},
    {TAF_XPDS_FL_MSGTYPE_REQ_PSEUDORANGE_MEAS,         TAF_XPDS_RCV_PDE_DATA_MASK_REQ_PSEURANGE_MEAS},
    {TAF_XPDS_FL_MSGTYPE_REQ_PILOT_PHASE_MEAS,         TAF_XPDS_RCV_PDE_DATA_MASK_REQ_PILOT_PHASE_MEAS},
    {TAF_XPDS_FL_MSGTYPE_REQ_CANCELLATION,             TAF_XPDS_RCV_PDE_DATA_MASK_REQ_CANCELLATION},
};

/*****************************************************************************
  3 Function Definitions
*****************************************************************************/

VOS_UINT32 TAF_XPDS_DecodeGetValue(
    VOS_UINT8                           ucNumOfBits,
    VOS_UINT32                         *pulTotalBitsPrc,
    VOS_UINT8                          *pucCurrBuf,
    VOS_UINT32                         *pulCurIdx
)
{
    VOS_UINT8                           ucShiftVal;
    VOS_UINT32                          ulTempVal;
    VOS_UINT8                           ucBitsAqrd;
    VOS_UINT8                           ucNumBitsDec;
    VOS_UINT8                           ucFifthByte;
    VOS_UINT8                           ucBitsInFifthByte;

    ulTempVal    = 0;

    /* caluculate the shift value */
    ucBitsAqrd   = ((*pulTotalBitsPrc) % 8);
    ucNumBitsDec = 32 - ucBitsAqrd;
    ucShiftVal   = 32 - ucNumOfBits;

    ulTempVal    =    (((VOS_UINT32)pucCurrBuf[0] << 24)
                    | ((VOS_UINT32)pucCurrBuf[1] << 16)
                    | ((VOS_UINT32)pucCurrBuf[2] << 8)
                    | ((VOS_UINT32)pucCurrBuf[3]));

    ulTempVal    = (ulTempVal << ucBitsAqrd);

    /* if number of bits we need is <= number of bits we alredy copied to temp variable
        then direct right shift to eliminate extra bits, otherwise we have to get the
        number of extra bits of the decoding value from the 5th byte */
    if (ucNumOfBits <= ucNumBitsDec)
    {
        ulTempVal         = (ulTempVal >> ucShiftVal);
    }
    else
    {
        ucFifthByte       = pucCurrBuf[4];
        ucBitsInFifthByte = ucNumOfBits - ucNumBitsDec;
        ucFifthByte      &= (TAF_XPDS_GetMaskValue(ucBitsInFifthByte));
        ucFifthByte       = (ucFifthByte >> (8 - ucBitsAqrd));
        ulTempVal         = (ulTempVal >> (32 - ucNumBitsDec - ucBitsInFifthByte));
        ulTempVal         = (ulTempVal | (VOS_UINT32)ucFifthByte);
    }

    /* update current index and pulTotalBitsPrc*/
    *pulTotalBitsPrc += ucNumOfBits;
    *pulCurIdx = (*pulTotalBitsPrc) / 8;

    return ulTempVal;

}

/*****************************************************************************
 函 数 名  : TAF_XPDS_DecodeGetOneBitFromOneByte
 功能描述  : get 1 bit from a char
 输入参数  : ucBuffer
             usBitPos
 输出参数  :
 返 回 值  : value of this  bit
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月13日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_XPDS_DecodeGetOneBitFromOneByte(
    VOS_UINT8                           ucBuffer,
    VOS_UINT8                           ucBitPos
)
{
    VOS_UINT8                           ucOffset = 0;

    ucOffset    = (VOS_UINT8)(0x01UL << ((VOS_UINT8)(7UL - ucBitPos)));

    if (0 == (ucBuffer & ucOffset))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*****************************************************************************
 函 数 名  : TAF_MTA_GetBitsFromBytes
 功能描述  : get N bits from an array
 输入参数  : pucBuffer         VOS_UINT8类型的数组指针
             usBitPos          需要取出的BIT在数组中的bit 的位置
             ucBitNum          需要取出的bit数(1 - 32)
 输出参数  :
 返 回 值  : value of these N bits
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月13日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_DecodeGetBitsFromBytes(
    VOS_UINT8                          *pucBuffer,
    VOS_UINT16                          usBitPos,
    VOS_UINT8                           ucBitNum
)
{
    VOS_UINT8                           ucIndex             = 0;
    VOS_UINT8                           ucBitPosInOneByte   = 0;
    VOS_UINT16                          usBytePos           = 0;
    VOS_UINT8                           ucTheBitNum         = 0;
    VOS_UINT32                          ulResult            = 0;

    for (ucIndex = 0; ucIndex < ucBitNum; ucIndex++)
    {
        usBytePos           =  (usBitPos + ucIndex) / 8;
        ucBitPosInOneByte   =  (usBitPos + ucIndex) % 8;

        /* GET THIS BIT (0 OR 1) */
        ucTheBitNum = TAF_XPDS_DecodeGetOneBitFromOneByte(pucBuffer[usBytePos],
                                                          ucBitPosInOneByte);

        if (0 != ucTheBitNum)
        {
            ulResult += 0x01UL << ((VOS_UINT8)(ucBitNum - ucIndex - 1UL));
        }

    }

    return ulResult;

}


TAF_XPDS_DecodeRespHandler TAF_XPDS_DecodeGetRespHandler(
    VOS_UINT32                          ulRespType
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulLoopSize;

    ulLoopSize  = sizeof(g_astTafXpdsDecodeRespMsgHdlTbl) / sizeof(g_astTafXpdsDecodeRespMsgHdlTbl[0]);

    for (ulLoop = 0; ulLoop < ulLoopSize; ulLoop++)
    {
        if (ulRespType == g_astTafXpdsDecodeRespMsgHdlTbl[ulLoop].ulMsgType)
        {
            return g_astTafXpdsDecodeRespMsgHdlTbl[ulLoop].pfRespHandler;
        }
    }

    return VOS_NULL_PTR;
}


TAF_XPDS_DecodeReqHandler TAF_XPDS_DecodeGetReqHandler(
    VOS_UINT32                          ulReqType
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulLoopSize;

    ulLoopSize  = sizeof(g_astTafXpdsDecodeReqMsgHdlTbl) / sizeof(g_astTafXpdsDecodeReqMsgHdlTbl[0]);

    for (ulLoop = 0; ulLoop < ulLoopSize; ulLoop++)
    {
        if (ulReqType == g_astTafXpdsDecodeReqMsgHdlTbl[ulLoop].ulMsgType)
        {
            return g_astTafXpdsDecodeReqMsgHdlTbl[ulLoop].pfReqHandler;
        }
    }

    return VOS_NULL_PTR;
}



VOS_UINT32 TAF_XPDS_DecodeGetPdeDataMaskByRespType(
    VOS_UINT32                          ulRespType
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulLoopSize;

    ulLoopSize  = sizeof(g_astTafXpdsDecodeRespTypeMapDataMaskTbl) / sizeof(g_astTafXpdsDecodeRespTypeMapDataMaskTbl[0]);

    for (ulLoop = 0; ulLoop < ulLoopSize; ulLoop++)
    {
        if (ulRespType == g_astTafXpdsDecodeRespTypeMapDataMaskTbl[ulLoop].ulMsgType)
        {
            return g_astTafXpdsDecodeRespTypeMapDataMaskTbl[ulLoop].ulDataMask;
        }
    }

    return 0;
}


VOS_UINT32 TAF_XPDS_DecodeGetPdeDataMaskByReqType(
    VOS_UINT32                          ulReqType
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulLoopSize;

    ulLoopSize  = sizeof(g_astTafXpdsDecodeReqTypeMapDataMaskTbl) / sizeof(g_astTafXpdsDecodeReqTypeMapDataMaskTbl[0]);

    for (ulLoop = 0; ulLoop < ulLoopSize; ulLoop++)
    {
        if (ulReqType == g_astTafXpdsDecodeReqTypeMapDataMaskTbl[ulLoop].ulMsgType)
        {
            return g_astTafXpdsDecodeReqTypeMapDataMaskTbl[ulLoop].ulDataMask;
        }
    }

    return 0;
}



VOS_UINT32 TAF_XPDS_DecodeProvGpsEphimeries(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                          ulTotNumOfBits;
    VOS_UINT32                          ulCurrIdx;
    TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU  *pstProvEph = VOS_NULL_PTR;
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucNumOfSvP;
    VOS_UINT8                           ucPartNum;
    VOS_UINT8                           ucTotalParts;
    VOS_UINT8                           ucPrevNumSv;

    pstProvEph  = &(TAF_XPDS_GetPdePublicData()->stProvGpsEph);

    ulTotNumOfBits         = 0;
    ulCurrIdx              = 0;

    ucNumOfSvP   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    ucPartNum    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    ucTotalParts = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    ucPrevNumSv               = pstProvEph->ucNumOfSvP;
    pstProvEph->ucNumOfSvP   += (ucNumOfSvP + 1); // +1 is according to the specification */
    pstProvEph->ucPartNum     = ucPartNum;
    pstProvEph->ucTotalParts  = ucTotalParts;

    pstProvEph->ucABParIncl   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                     &ulTotNumOfBits,
                                                                     &pucHeadBuf[ulCurrIdx],
                                                                     &ulCurrIdx);

    /* ION数据使用第一个ucABParIncl为1的PART里的数据 */
    if (VOS_TRUE == pstProvEph->ucABParIncl)
    {
        if (VOS_FALSE == TAF_XPDS_GetRespGpsIonInEphimFlag())
        {
            pstProvEph->ucAlpha0 = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                         &ulTotNumOfBits,
                                                                         &pucHeadBuf[ulCurrIdx],
                                                                         &ulCurrIdx);
            pstProvEph->ucAlpha1 = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                         &ulTotNumOfBits,
                                                                         &pucHeadBuf[ulCurrIdx],
                                                                         &ulCurrIdx);
            pstProvEph->ucAlpha2 = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                         &ulTotNumOfBits,
                                                                         &pucHeadBuf[ulCurrIdx],
                                                                         &ulCurrIdx);
            pstProvEph->ucAlpha3 = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                         &ulTotNumOfBits,
                                                                         &pucHeadBuf[ulCurrIdx],
                                                                         &ulCurrIdx);
            pstProvEph->ucBeta0  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                         &ulTotNumOfBits,
                                                                         &pucHeadBuf[ulCurrIdx],
                                                                         &ulCurrIdx);
            pstProvEph->ucBeta1  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                         &ulTotNumOfBits,
                                                                         &pucHeadBuf[ulCurrIdx],
                                                                         &ulCurrIdx);
            pstProvEph->ucBeta2  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                         &ulTotNumOfBits,
                                                                         &pucHeadBuf[ulCurrIdx],
                                                                         &ulCurrIdx);
            pstProvEph->ucBeta3  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                         &ulTotNumOfBits,
                                                                         &pucHeadBuf[ulCurrIdx],
                                                                         &ulCurrIdx);

            TAF_XPDS_SetRespGpsIonInEphimFlag(VOS_TRUE);
        }
        else
        {
            ulTotNumOfBits += 64;

            ulCurrIdx      += 8;
        }

    }

    if (pstProvEph->ucNumOfSvP >= TAF_MSG_CDMA_MAX_EPH_PRN_NUM)
    {
        pstProvEph->ucNumOfSvP = TAF_MSG_CDMA_MAX_EPH_PRN_NUM;
    }

    for (ucLoop = ucPrevNumSv; ucLoop < pstProvEph->ucNumOfSvP; ucLoop++)
    {
        pstProvEph->astSatInfo[ucLoop].ucSv_Prn_Num   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                                              &ulTotNumOfBits,
                                                                                              &pucHeadBuf[ulCurrIdx],
                                                                                              &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].ucIODE         = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                                              &ulTotNumOfBits,
                                                                                              &pucHeadBuf[ulCurrIdx],
                                                                                              &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].usC_RS         = (VOS_UINT16)TAF_XPDS_DecodeGetValue(16,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].usDelta_N      = (VOS_UINT16)TAF_XPDS_DecodeGetValue(16,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].ulM0           = (VOS_UINT32)TAF_XPDS_DecodeGetValue(32,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].usC_UC         = (VOS_UINT16)TAF_XPDS_DecodeGetValue(16,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].ulEcCentricity = (VOS_UINT32)TAF_XPDS_DecodeGetValue(32,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].usC_US         = (VOS_UINT16)TAF_XPDS_DecodeGetValue(16,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].ulA_Sqrt       = (VOS_UINT32)TAF_XPDS_DecodeGetValue(32,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].usTOE          = (VOS_UINT16)TAF_XPDS_DecodeGetValue(16,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].usC_IC         = (VOS_UINT16)TAF_XPDS_DecodeGetValue(16,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].ulOmega_0      = (VOS_UINT32)TAF_XPDS_DecodeGetValue(32,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].usC_IS         = (VOS_UINT16)TAF_XPDS_DecodeGetValue(16,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].ulAngle_Incli  = (VOS_UINT32)TAF_XPDS_DecodeGetValue(32,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].usC_RC         = (VOS_UINT16)TAF_XPDS_DecodeGetValue(16,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].ulOmega        = (VOS_UINT32)TAF_XPDS_DecodeGetValue(32,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].ulOmegaDot     = (VOS_UINT32)TAF_XPDS_DecodeGetValue(24,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].usIdot         = (VOS_UINT16)TAF_XPDS_DecodeGetValue(14,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].usTOC          = (VOS_UINT16)TAF_XPDS_DecodeGetValue(16,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].ucAF2          = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                                              &ulTotNumOfBits,
                                                                                              &pucHeadBuf[ulCurrIdx],
                                                                                              &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].usAF1          = (VOS_UINT16)TAF_XPDS_DecodeGetValue(16,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
        pstProvEph->astSatInfo[ucLoop].ulAF0          = (VOS_UINT32)TAF_XPDS_DecodeGetValue(22,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);
    }

    TAF_XPDS_MNTN_TraceEphInfoCtxIndMsg();

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_DecodeProvGpsAlmanac(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                          ulTotNumOfBits;
    VOS_UINT32                          ulCurrIdx;
    TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU  *pstProvAlm = VOS_NULL_PTR;
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucPrevNumSat;

    ulTotNumOfBits           = 0;
    ulCurrIdx                = 0;
    ucLoop                   = 0;

    pstProvAlm               = &(TAF_XPDS_GetPdePublicData()->stProvGpsAlm);

    ucPrevNumSat             = pstProvAlm->ucNumOfSvP;

    pstProvAlm->ucNumOfSvP   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(6,
                                                                       &ulTotNumOfBits,
                                                                       &pucHeadBuf[ulCurrIdx],
                                                                       &ulCurrIdx);
    pstProvAlm->ucWeekNum    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                       &ulTotNumOfBits,
                                                                       &pucHeadBuf[ulCurrIdx],
                                                                       &ulCurrIdx);
    pstProvAlm->ucTOA        = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                       &ulTotNumOfBits,
                                                                       &pucHeadBuf[ulCurrIdx],
                                                                       &ulCurrIdx);
    pstProvAlm->ucPartNum    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                       &ulTotNumOfBits,
                                                                       &pucHeadBuf[ulCurrIdx],
                                                                       &ulCurrIdx);
    pstProvAlm->ucTotalParts = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                       &ulTotNumOfBits,
                                                                       &pucHeadBuf[ulCurrIdx],
                                                                       &ulCurrIdx);

    /* update the total number of satellites */
    pstProvAlm->ucNumOfSvP   = pstProvAlm->ucNumOfSvP + ucPrevNumSat + 1; /* +1 for the actual number of satellites */

    if (pstProvAlm->ucNumOfSvP >= TAF_MSG_CDMA_MAX_ALM_PRN_NUM)
    {
        pstProvAlm->ucNumOfSvP = TAF_MSG_CDMA_MAX_ALM_PRN_NUM;
    }

    for (ucLoop = ucPrevNumSat; ucLoop < pstProvAlm->ucNumOfSvP; ucLoop++)
    {
        pstProvAlm->astSatInfo[ucLoop].ucSv_Prn_Num   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                                                &ulTotNumOfBits,
                                                                                                &pucHeadBuf[ulCurrIdx],
                                                                                                &ulCurrIdx);
        pstProvAlm->astSatInfo[ucLoop].usDelta_Incli  = (VOS_UINT16)TAF_XPDS_DecodeGetValue(16,
                                                                                                 &ulTotNumOfBits,
                                                                                                 &pucHeadBuf[ulCurrIdx],
                                                                                                 &ulCurrIdx);
        pstProvAlm->astSatInfo[ucLoop].ulM0           = (VOS_UINT32)TAF_XPDS_DecodeGetValue(24,
                                                                                                 &ulTotNumOfBits,
                                                                                                 &pucHeadBuf[ulCurrIdx],
                                                                                                 &ulCurrIdx);
        pstProvAlm->astSatInfo[ucLoop].usEcCentricity = (VOS_UINT16)TAF_XPDS_DecodeGetValue(16,
                                                                                                 &ulTotNumOfBits,
                                                                                                 &pucHeadBuf[ulCurrIdx],
                                                                                                 &ulCurrIdx);
        pstProvAlm->astSatInfo[ucLoop].ulA_Sqrt       = (VOS_UINT32)TAF_XPDS_DecodeGetValue(24,
                                                                                                 &ulTotNumOfBits,
                                                                                                 &pucHeadBuf[ulCurrIdx],
                                                                                                 &ulCurrIdx);
        pstProvAlm->astSatInfo[ucLoop].ulOmega_0      = (VOS_UINT32)TAF_XPDS_DecodeGetValue(24,
                                                                                                 &ulTotNumOfBits,
                                                                                                 &pucHeadBuf[ulCurrIdx],
                                                                                                 &ulCurrIdx);
        pstProvAlm->astSatInfo[ucLoop].ulOmega        = (VOS_UINT32)TAF_XPDS_DecodeGetValue(24,
                                                                                                 &ulTotNumOfBits,
                                                                                                 &pucHeadBuf[ulCurrIdx],
                                                                                                 &ulCurrIdx);
        pstProvAlm->astSatInfo[ucLoop].usOmegaDot     = (VOS_UINT16)TAF_XPDS_DecodeGetValue(16,
                                                                                                 &ulTotNumOfBits,
                                                                                                 &pucHeadBuf[ulCurrIdx],
                                                                                                 &ulCurrIdx);
        pstProvAlm->astSatInfo[ucLoop].usAF1          = (VOS_UINT16)TAF_XPDS_DecodeGetValue(11,
                                                                                                 &ulTotNumOfBits,
                                                                                                 &pucHeadBuf[ulCurrIdx],
                                                                                                 &ulCurrIdx);
        pstProvAlm->astSatInfo[ucLoop].usAF0          = (VOS_UINT16)TAF_XPDS_DecodeGetValue(11,
                                                                                                 &ulTotNumOfBits,
                                                                                                 &pucHeadBuf[ulCurrIdx],
                                                                                                 &ulCurrIdx);
    }

    TAF_XPDS_MNTN_TraceAlmInfoCtxIndMsg();

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_DecodeProvGpsAcqAssist(
    VOS_UINT8                              *pucHeadBuf
)
{
    VOS_UINT32                                     ulTotNumOfBits;
    VOS_UINT32                                     ulCurrIdx;
    TAF_XPDS_FWDLINK_RSP_GPS_ACQ_ASSIST_STRU      *pstProvAcqAssist;
    VOS_UINT8                                      ucLoop;

    pstProvAcqAssist = &(TAF_XPDS_GetPdePublicData()->stProvAcqAssist);

    PS_MEM_SET(pstProvAcqAssist, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_GPS_ACQ_ASSIST_STRU));

    ulTotNumOfBits              = 0;
    ulCurrIdx                   = 0;

    pstProvAcqAssist->ucNumOfSv      = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                     &ulTotNumOfBits,
                                                                     &pucHeadBuf[ulCurrIdx],
                                                                     &ulCurrIdx);
    pstProvAcqAssist->ucTimeOfApp    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                     &ulTotNumOfBits,
                                                                     &pucHeadBuf[ulCurrIdx],
                                                                     &ulCurrIdx);
    pstProvAcqAssist->ucDopp0Incl    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                     &ulTotNumOfBits,
                                                                     &pucHeadBuf[ulCurrIdx],
                                                                     &ulCurrIdx);

    if (VOS_TRUE == pstProvAcqAssist->ucDopp0Incl)
    {
        pstProvAcqAssist->ucAddDoppIncl  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);
    }

    pstProvAcqAssist->ucCodePhParIncl    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                         &ulTotNumOfBits,
                                                                         &pucHeadBuf[ulCurrIdx],
                                                                         &ulCurrIdx);

    if (VOS_TRUE == pstProvAcqAssist->ucCodePhParIncl)
    {
        pstProvAcqAssist->usRefPn    = (VOS_UINT16)TAF_XPDS_DecodeGetValue(10,
                                                                      &ulTotNumOfBits,
                                                                      &pucHeadBuf[ulCurrIdx],
                                                                      &ulCurrIdx);
    }

    pstProvAcqAssist->ucAzElIncl     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                    &ulTotNumOfBits,
                                                                    &pucHeadBuf[ulCurrIdx],
                                                                    &ulCurrIdx);

    for (ucLoop = 0; ucLoop < pstProvAcqAssist->ucNumOfSv + 1; ucLoop++)
    {
        pstProvAcqAssist->astSatInfo[ucLoop].ucSvPrnNum    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(6,
                                                                                              &ulTotNumOfBits,
                                                                                              &pucHeadBuf[ulCurrIdx],
                                                                                              &ulCurrIdx);

        if (VOS_TRUE == pstProvAcqAssist->ucDopp0Incl)
        {
            pstProvAcqAssist->astSatInfo[ucLoop].sDoppler0       = (VOS_INT16)TAF_XPDS_DecodeGetValue(12,
                                                                                                   &ulTotNumOfBits,
                                                                                                   &pucHeadBuf[ulCurrIdx],
                                                                                                   &ulCurrIdx);
        }

        if (VOS_TRUE == pstProvAcqAssist->ucAddDoppIncl)
        {
            pstProvAcqAssist->astSatInfo[ucLoop].cDoppler1       = (VOS_INT8)TAF_XPDS_DecodeGetValue(7,
                                                                                                  &ulTotNumOfBits,
                                                                                                  &pucHeadBuf[ulCurrIdx],
                                                                                                  &ulCurrIdx);
            pstProvAcqAssist->astSatInfo[ucLoop].ucDopplerWin    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                                                  &ulTotNumOfBits,
                                                                                                  &pucHeadBuf[ulCurrIdx],
                                                                                                  &ulCurrIdx);
        }

        if (VOS_TRUE == pstProvAcqAssist->ucCodePhParIncl)
        {
            pstProvAcqAssist->astSatInfo[ucLoop].usSvCodePh      = (VOS_UINT16)TAF_XPDS_DecodeGetValue(10,
                                                                                                   &ulTotNumOfBits,
                                                                                                   &pucHeadBuf[ulCurrIdx],
                                                                                                   &ulCurrIdx);
            pstProvAcqAssist->astSatInfo[ucLoop].ucSvCodePhInt   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                                                  &ulTotNumOfBits,
                                                                                                  &pucHeadBuf[ulCurrIdx],
                                                                                                  &ulCurrIdx);
            pstProvAcqAssist->astSatInfo[ucLoop].ucGpsBitNum     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                                                                  &ulTotNumOfBits,
                                                                                                  &pucHeadBuf[ulCurrIdx],
                                                                                                  &ulCurrIdx);
            pstProvAcqAssist->astSatInfo[ucLoop].ucSvCodePhWin   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                                                  &ulTotNumOfBits,
                                                                                                  &pucHeadBuf[ulCurrIdx],
                                                                                                  &ulCurrIdx);
        }

        if (VOS_TRUE == pstProvAcqAssist->ucAzElIncl)
        {
            pstProvAcqAssist->astSatInfo[ucLoop].ucAzimuth       = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                                                  &ulTotNumOfBits,
                                                                                                  &pucHeadBuf[ulCurrIdx],
                                                                                                  &ulCurrIdx);
            pstProvAcqAssist->astSatInfo[ucLoop].ucElevation     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                                                  &ulTotNumOfBits,
                                                                                                  &pucHeadBuf[ulCurrIdx],
                                                                                                  &ulCurrIdx);
        }
    }

    return VOS_OK;

}


VOS_UINT32 TAF_XPDS_DecodeProvLocResp(
    VOS_UINT8                               *pucHeadBuf
)
{
    VOS_UINT32                                 ulTotNumOfBits;
    VOS_UINT32                                 ulCurrIdx;
    TAF_XPDS_FWDLINK_RSP_LOC_RESP_STRU        *pstProvLocRsp;

    pstProvLocRsp  = &(TAF_XPDS_GetPublicDataAddr()->stProvLocRsp);

    PS_MEM_SET(pstProvLocRsp, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_LOC_RESP_STRU));

    ulTotNumOfBits              = 0;
    ulCurrIdx                   = 0;

    pstProvLocRsp->usTimeRefCdma  = (VOS_UINT16)TAF_XPDS_DecodeGetValue(14,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);
    pstProvLocRsp->lLattitude     = (VOS_INT32)TAF_XPDS_DecodeGetValue(25,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);

    pstProvLocRsp->lLongitude     = (VOS_INT32)TAF_XPDS_DecodeGetValue(26,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);
    pstProvLocRsp->ucLocUncerAng  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                          &ulTotNumOfBits,
                                                                          &pucHeadBuf[ulCurrIdx],
                                                                          &ulCurrIdx);
    pstProvLocRsp->ucLocUncerA    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                          &ulTotNumOfBits,
                                                                          &pucHeadBuf[ulCurrIdx],
                                                                          &ulCurrIdx);
    pstProvLocRsp->ucLocUncerP    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                          &ulTotNumOfBits,
                                                                          &pucHeadBuf[ulCurrIdx],
                                                                          &ulCurrIdx);
    pstProvLocRsp->ucFixType      = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                          &ulTotNumOfBits,
                                                                          &pucHeadBuf[ulCurrIdx],
                                                                          &ulCurrIdx);
    pstProvLocRsp->ucVelocityIncl = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                          &ulTotNumOfBits,
                                                                          &pucHeadBuf[ulCurrIdx],
                                                                          &ulCurrIdx);

    if (VOS_TRUE == pstProvLocRsp->ucVelocityIncl)
    {
        pstProvLocRsp->usVelocityHor  = (VOS_UINT16)TAF_XPDS_DecodeGetValue(9,
                                                                               &ulTotNumOfBits,
                                                                               &pucHeadBuf[ulCurrIdx],
                                                                               &ulCurrIdx);
        pstProvLocRsp->usHeading      = (VOS_UINT16)TAF_XPDS_DecodeGetValue(10,
                                                                               &ulTotNumOfBits,
                                                                               &pucHeadBuf[ulCurrIdx],
                                                                               &ulCurrIdx);
        pstProvLocRsp->cVelocityVer   = (VOS_INT8)TAF_XPDS_DecodeGetValue(8,
                                                                              &ulTotNumOfBits,
                                                                              &pucHeadBuf[ulCurrIdx],
                                                                              &ulCurrIdx);
    }

    pstProvLocRsp->ucClockIncl        = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                              &ulTotNumOfBits,
                                                                              &pucHeadBuf[ulCurrIdx],
                                                                              &ulCurrIdx);

    if (VOS_TRUE == pstProvLocRsp->ucClockIncl)
    {
        pstProvLocRsp->lClockBias     = (VOS_INT32)TAF_XPDS_DecodeGetValue(18,
                                                                               &ulTotNumOfBits,
                                                                               &pucHeadBuf[ulCurrIdx],
                                                                               &ulCurrIdx);
        pstProvLocRsp->sClockDrift    = (VOS_INT16)TAF_XPDS_DecodeGetValue(16,
                                                                               &ulTotNumOfBits,
                                                                               &pucHeadBuf[ulCurrIdx],
                                                                               &ulCurrIdx);
    }

    pstProvLocRsp->ucHeightIncl       = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                              &ulTotNumOfBits,
                                                                              &pucHeadBuf[ulCurrIdx],
                                                                              &ulCurrIdx);

    if (VOS_TRUE == pstProvLocRsp->ucHeightIncl)
    {
        pstProvLocRsp->sHeight        = (VOS_INT16)TAF_XPDS_DecodeGetValue(14,
                                                                               &ulTotNumOfBits,
                                                                               &pucHeadBuf[ulCurrIdx],
                                                                               &ulCurrIdx);
        pstProvLocRsp->ucLocUncerV    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                              &ulTotNumOfBits,
                                                                              &pucHeadBuf[ulCurrIdx],
                                                                              &ulCurrIdx);
    }

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_DecodeReject(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                          ulTotNumOfBits;
    VOS_UINT32                          ulCurrIdx;
    TAF_XPDS_FWDLINK_RSP_REJECT_STRU   *pstReject;

    pstReject = (TAF_XPDS_FWDLINK_RSP_REJECT_STRU*)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                                sizeof(TAF_XPDS_FWDLINK_RSP_REJECT_STRU));
    if (VOS_NULL_PTR == pstReject)
    {
        XPDS_ERROR_LOG("TAF_XPDS_DecodeReject, malloc failed");
        return VOS_ERR;
    }
    PS_MEM_SET(pstReject, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_REJECT_STRU));

    ulTotNumOfBits = 0;
    ulCurrIdx      = 0;

    pstReject->ucRejReqType = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                      &ulTotNumOfBits,
                                                                      &pucHeadBuf[ulCurrIdx],
                                                                      &ulCurrIdx);

    pstReject->ucRejReason  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                      &ulTotNumOfBits,
                                                                      &pucHeadBuf[ulCurrIdx],
                                                                      &ulCurrIdx);

    XPDS_WARNING1_LOG("TAF_XPDS_DecodeReject, PDE resp rej to prev req type :", pstReject->ucRejReqType);

    PS_MEM_FREE(UEPS_PID_XPDS, pstReject);

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_DecodeRequestCancellation(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                           ulNumBitsProcessed;
    VOS_UINT32                           ulCurIdx;
    TAF_XPDS_FWDLINK_REQ_CANCEL_STRU    *pstFwdReqCancel;

    ulNumBitsProcessed = 0;
    ulCurIdx           = 0;
    pstFwdReqCancel    = &(TAF_XPDS_GetPdePublicData()->stFwdReqCancel);

    PS_MEM_SET(pstFwdReqCancel, 0x00, sizeof(TAF_XPDS_FWDLINK_REQ_CANCEL_STRU));

    /* get the Cancellation type */
    pstFwdReqCancel->ucCancelType = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                       &ulNumBitsProcessed,
                                                                       &pucHeadBuf[ulCurIdx],
                                                                       &ulCurIdx);

    switch (pstFwdReqCancel->ucCancelType)
    {
        case TAF_XPDS_FL_MSGTYPE_REQ_LOCATION_INFO:
            TAF_XPDS_SetReqLocRespFlag(VOS_FALSE);
            break;

        case TAF_XPDS_FL_MSGTYPE_REQ_MS_INFO:
            TAF_XPDS_SetReqMsInfoFlag(VOS_FALSE);
            break;

        case TAF_XPDS_FL_MSGTYPE_REQ_PSEUDORANGE_MEAS:
            TAF_XPDS_SetReqPsuRangMeasFlag(VOS_FALSE);
            break;

        case TAF_XPDS_FL_MSGTYPE_REQ_PILOT_PHASE_MEAS:
            TAF_XPDS_SetReqPilotPhaseMeasFlag(VOS_FALSE);
            break;

        default:
            break;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_DecodeRequestPilotPhaseMeas(
    VOS_UINT8                                   *pucHeadBuf
)
{
    VOS_UINT32                                  ulNumBitsProcessed;
    VOS_UINT32                                  ulCurIdx;
    TAF_XPDS_FWDLINK_REQ_PILOT_PHASE_MEAS_STRU *pstFwdPilotPhaseMeas;

    ulNumBitsProcessed      = 0;
    ulCurIdx                = 0;

    pstFwdPilotPhaseMeas    = &(TAF_XPDS_GetPdePublicData()->stFwdReqPilotPhaseMeas);

    PS_MEM_SET(pstFwdPilotPhaseMeas, 0x00, sizeof(TAF_XPDS_FWDLINK_REQ_PILOT_PHASE_MEAS_STRU));

    /* update the response flag for Provide pilot phase response */
    TAF_XPDS_SetReqPilotPhaseMeasFlag(VOS_TRUE);

    /* get Preferred response quality */
    pstFwdPilotPhaseMeas->ucPrefRespQual  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                                    &ulNumBitsProcessed,
                                                                                    &pucHeadBuf[ulCurIdx],
                                                                                    &ulCurIdx);

    /* get Number of fixes */
    pstFwdPilotPhaseMeas->ucNumOfFixes    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                                    &ulNumBitsProcessed,
                                                                                    &pucHeadBuf[ulCurIdx],
                                                                                    &ulCurIdx);

    /* get Time between fixes */
    pstFwdPilotPhaseMeas->ucTimeBetFix    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                                    &ulNumBitsProcessed,
                                                                                    &pucHeadBuf[ulCurIdx],
                                                                                    &ulCurIdx);

    /* get Offset requested */
    pstFwdPilotPhaseMeas->ucOffsetReq     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                    &ulNumBitsProcessed,
                                                                                    &pucHeadBuf[ulCurIdx],
                                                                                    &ulCurIdx);

    /* get Desired pilot phase resolution */
    pstFwdPilotPhaseMeas->ucDesPilPhRes   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                    &ulNumBitsProcessed,
                                                                                    &pucHeadBuf[ulCurIdx],
                                                                                    &ulCurIdx);

    return VOS_OK;

}


VOS_UINT32 TAF_XPDS_DecodeRequestLocResp(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                               ulNumBitsProcessed;
    VOS_UINT32                               ulCurIdx;
    TAF_XPDS_FWDLINK_REQ_LOC_RESP_STRU      *pstFwdReqLocResp;

    ulNumBitsProcessed  = 0;
    ulCurIdx            = 0;

    pstFwdReqLocResp    = &(TAF_XPDS_GetPdePublicData()->stFwdReqLocResp);

    /* update the response flag for Provide location response */
    TAF_XPDS_SetReqLocRespFlag(VOS_TRUE);

    PS_MEM_SET(pstFwdReqLocResp, 0x00, sizeof(TAF_XPDS_FWDLINK_REQ_LOC_RESP_STRU));

    /* get the Preferred response quality */
    pstFwdReqLocResp->ucPrefRespQual = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* get the Number of fixes */
    pstFwdReqLocResp->ucNumOfFixes   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* get the Time between fixes */
    pstFwdReqLocResp->ucTimeBetFix   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* get the Height information requested */
    pstFwdReqLocResp->ucHeightReq    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* get the Clock correction for GPS time requested */
    pstFwdReqLocResp->ucClkCorGpsReq = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* get Velocity information requested */
    pstFwdReqLocResp->ucVelocityReq  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_DecodeRequestMsInfo
 功能描述  : PDE Request Ms Info
 输入参数  : VOS_UINT8                          *pucHeadBuf
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月17日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_DecodeRequestMsInfo(
    VOS_UINT8                          *pucHeadBuf
)
{

    /* update the response flag for Provide location response */
    TAF_XPDS_SetReqMsInfoFlag(VOS_TRUE);

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_DecodeRequestPseudoRangeMeas(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                                 ulNumBitsProcessed;
    VOS_UINT32                                 ulCurIdx;
    TAF_XPDS_FWDLINK_REQ_PSUERANGE_MEAS_STRU  *pstFwdPsuRangeMeas;

    ulNumBitsProcessed = 0;
    ulCurIdx           = 0;

    pstFwdPsuRangeMeas = &(TAF_XPDS_GetPdePublicData()->stFwdReqPsuRangeMeas);

    PS_MEM_SET(pstFwdPsuRangeMeas, 0x00, sizeof(TAF_XPDS_FWDLINK_REQ_PSUERANGE_MEAS_STRU));

    /* update the response flag for provide psuedo range measurement response */
    TAF_XPDS_SetReqPsuRangMeasFlag(VOS_TRUE);

    /* get Preferred response quality */
    pstFwdPsuRangeMeas->ucPrefRespQual =  (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                                  &ulNumBitsProcessed,
                                                                                  &pucHeadBuf[ulCurIdx],
                                                                                  &ulCurIdx);

    /* get Number of fixes */
    pstFwdPsuRangeMeas->ucNumOfFixes   =  (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                                  &ulNumBitsProcessed,
                                                                                  &pucHeadBuf[ulCurIdx],
                                                                                  &ulCurIdx);

    /* get Time between fixes */
    pstFwdPsuRangeMeas->ucTimeBetFix   =  (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                                  &ulNumBitsProcessed,
                                                                                  &pucHeadBuf[ulCurIdx],
                                                                                  &ulCurIdx);

    /* get Offset requested */
    pstFwdPsuRangeMeas->ucOffsetReq    =  (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                  &ulNumBitsProcessed,
                                                                                  &pucHeadBuf[ulCurIdx],
                                                                                  &ulCurIdx);

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_DecodePdeHeaderInfo(
    VOS_UINT8                          *pucHeadBuf,
    TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdMsgHeader
)
{
    VOS_UINT32                          ulNumBitsProcessed;
    VOS_UINT32                          ulCurIdx;
    VOS_UINT32                          ulTotHdrLen;

    ulNumBitsProcessed = 0;
    ulCurIdx           = 0;
    ulTotHdrLen        = TAF_XPDS_PDE_HEADER_LEN_MIN;

    PS_MEM_SET(pstPdMsgHeader, 0x00, sizeof(TAF_XPDS_PD_MSG_HEADER_STRU));

    pstPdMsgHeader->ucSessStart = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1, &ulNumBitsProcessed, &pucHeadBuf[ulCurIdx], &ulCurIdx);
    pstPdMsgHeader->ucSessEnd   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1, &ulNumBitsProcessed, &pucHeadBuf[ulCurIdx], &ulCurIdx);
    pstPdMsgHeader->ucSessSrc   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1, &ulNumBitsProcessed, &pucHeadBuf[ulCurIdx], &ulCurIdx);

    pstPdMsgHeader->ucSessTag   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5, &ulNumBitsProcessed, &pucHeadBuf[ulCurIdx], &ulCurIdx);
    pstPdMsgHeader->ucPdMsgType = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8, &ulNumBitsProcessed, &pucHeadBuf[ulCurIdx], &ulCurIdx);

    /* if PDE msg type is not 0x00 then it is invalid and no need to process */
    if (pstPdMsgHeader->ucPdMsgType != 0x00)
    {
        XPDS_WARNING1_LOG("TAF_XPDS_DecodePDEHeaderInfo, PDE message type not 0x00, msgType:", pstPdMsgHeader->ucPdMsgType);
        pstPdMsgHeader->usPdMsgLen = (VOS_UINT8)TAF_XPDS_DecodeGetValue(10, &ulNumBitsProcessed, &pucHeadBuf[ulCurIdx], &ulCurIdx);
        pstPdMsgHeader->ucRegulInd  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2, &ulNumBitsProcessed, &pucHeadBuf[ulCurIdx], &ulCurIdx);
        ulTotHdrLen              += 2; // 2 is the size of usPDEMsgLen + ucRegulInd fields
    }

    pstPdMsgHeader->ucNumOfReq   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4, &ulNumBitsProcessed, &pucHeadBuf[ulCurIdx], &ulCurIdx);;
    pstPdMsgHeader->ucNumOfResp  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4, &ulNumBitsProcessed, &pucHeadBuf[ulCurIdx], &ulCurIdx);;

    if (1 == pstPdMsgHeader->ucSessStart)
    {
        TAF_XPDS_SetPdeSessionStatus(TAF_XPDS_PDE_SESSION_STATUS_STARTED);

        TAF_XPDS_SetPdeSessionTriggerType(TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_NETWORK);

        TAF_XPDS_SetSessTagInRsvPdMsgHeader(pstPdMsgHeader->ucSessTag);
    }

    if (1 == pstPdMsgHeader->ucSessEnd)
    {
        TAF_XPDS_SetPdeSessionStatus(TAF_XPDS_PDE_SESSION_STATUS_ENDED);
    }

    TAF_XPDS_SetFwdPdMsgHeader(pstPdMsgHeader);

    TAF_XPDS_MNTN_TraceForwardPdeHeaderInfo();

    return ulTotHdrLen;
}


VOS_UINT32 TAF_XPDS_DecodeGetRespIndex(
    VOS_UINT8                          *pucOneMsgBuf,
    TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdMsgHeader
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulReqMsgLen;
    VOS_UINT8                           ucLoop;

    /* initally set the index to PDE msg header length */
    ulIndex       = TAF_XPDS_PDE_HEADER_LEN_MIN;

    /* loop through all the requests and skip length */
    for (ucLoop = 0; ucLoop < pstPdMsgHeader->ucNumOfReq; ucLoop++)
    {
        /* get the message length of current request */
        ulReqMsgLen  = (pucOneMsgBuf + ulIndex)[1];

        /* update the index */
        ulIndex  += ulReqMsgLen + 2; // 2 byte for length of fileds Reserved + Req Type + Req par len
    }

    return ulIndex;
}


VOS_UINT32 TAF_XPDS_DecodeRespInfo(
    VOS_UINT8                          *pucOneMsgBuf,
    TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdMsgHeader,
    VOS_UINT32                         *pulOutDataMask
)
{
    VOS_UINT32                                              ulProcBytes;
    VOS_UINT32                                              ulLoop;
    VOS_UINT32                                              ulRespType;
    VOS_UINT32                                              ulRespParLen;
    TAF_XPDS_DecodeRespHandler                              pfRespHandlr;
    VOS_UINT32                                              ulDataMask;
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_ENUM_UINT8              enOmGpsMsgType;

    ulProcBytes = 0;

    ulDataMask = 0;

    for (ulLoop = 0; ulLoop < pstPdMsgHeader->ucNumOfResp; ulLoop++)
    {
        ulRespType   = (((pucOneMsgBuf + ulProcBytes)[0]) & 0x0F);
        ulRespParLen = (pucOneMsgBuf + ulProcBytes)[1];

        pfRespHandlr = TAF_XPDS_DecodeGetRespHandler(ulRespType);

        ulProcBytes += 2; // 2 is size of field Reserve + unsol_resp + resp_type + resp_par_len

        if (VOS_NULL_PTR == pfRespHandlr)
        {
            XPDS_WARNING_LOG("TAF_XPDS_DecodeProcRespBuf: message handler is NULL");
            ulProcBytes += ulRespParLen;
            continue;
        }

        (VOS_VOID)pfRespHandlr((VOS_UINT8 *)(pucOneMsgBuf + ulProcBytes)); // 2 is size of field Reserve + unsol_resp + resp_type + resp_par_len

        ulDataMask |= TAF_XPDS_DecodeGetPdeDataMaskByRespType(ulRespType);

        enOmGpsMsgType = TAF_XPDS_ConvertFlPdeRspMsgTypeToOmGpsMsgType(ulRespType);

        TAF_XPDS_SndOmGpsSignalMsgInd(enOmGpsMsgType);

        ulProcBytes += ulRespParLen;
    }

    *pulOutDataMask = ulDataMask;

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_DecodeReqInfo(
    VOS_UINT8                          *pucOneMsgBuf,
    TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdMsgHeader,
    VOS_UINT32                         *pulOutDataMask
)
{
    VOS_UINT32                                              ulProcBytes;
    VOS_UINT32                                              ulLoop;
    VOS_UINT32                                              ulReqType;
    VOS_UINT32                                              ulReqParLen;
    TAF_XPDS_DecodeReqHandler                               pfReqHandlr;
    TAF_XPDS_REVLINK_RSP_REJECT_STRU                        stRejInfo;
    VOS_UINT32                                              ulDataMask;
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_ENUM_UINT8              enOmGpsMsgType;

    ulProcBytes = 0;

    ulDataMask = 0;

    for (ulLoop = 0; ulLoop < pstPdMsgHeader->ucNumOfReq; ulLoop++)
    {
        ulReqType   = (((pucOneMsgBuf + ulProcBytes)[0]) & 0x0F);
        ulReqParLen = (pucOneMsgBuf + ulProcBytes)[1];

        pfReqHandlr = TAF_XPDS_DecodeGetReqHandler(ulReqType);

        if (VOS_NULL_PTR == pfReqHandlr)
        {
            PS_MEM_SET(&stRejInfo, 0x0, sizeof(TAF_XPDS_REVLINK_RSP_REJECT_STRU));

            /* send the req rej to PDE */
            stRejInfo.ucRejReason   = TAF_XPDS_RL_REJ_REASON_MS_CAP_NOT_SUPPORTED;
            stRejInfo.ucRejReqType  = (VOS_UINT8)ulReqType;

            TAF_XPDS_SndAtApPdeRejectRsp(&stRejInfo);

            ulProcBytes += ulReqParLen + 2; // 2 is size of field Reserve  + req_type + req_par_len
            continue;
        }

        (VOS_VOID)pfReqHandlr(pucOneMsgBuf + ulProcBytes + 2); // 2 is size of field Reserve  + req_type + req_par_len

        ulDataMask |= TAF_XPDS_DecodeGetPdeDataMaskByReqType(ulReqType);

        enOmGpsMsgType = TAF_XPDS_ConvertFlPdeReqMsgTypeToOmGpsMsgType(ulReqType);

        TAF_XPDS_SndOmGpsSignalMsgInd(enOmGpsMsgType);

        ulProcBytes += ulReqParLen + 2; // 2 is size of field Reserve  + req_type + req_par_len
    }

    *pulOutDataMask = ulDataMask;

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_DecodeOnePdeMsg(
    VOS_UINT8                          *pucOneMsgBuf,
    VOS_UINT32                         *pulOutDataMask
)
{
    VOS_UINT32                          ulRes;
    TAF_XPDS_PD_MSG_HEADER_STRU         stPdMsgHeader;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulPdeHdrLen;
    VOS_UINT32                          ulDataMaskRsp;
    VOS_UINT32                          ulDataMaskReq;

    ulPdeHdrLen = TAF_XPDS_DecodePdeHeaderInfo(pucOneMsgBuf, &stPdMsgHeader);

    if (ulPdeHdrLen != TAF_XPDS_PDE_HEADER_LEN_MIN)
    {
        XPDS_WARNING_LOG("TAF_XPDS_DecodeOnePdeMsg: PDE message type is other than 0x00, not processed now");
        return VOS_ERR;
    }

    /* as protocol says its better to process response element first, so get the
        index from where the response part begins */
    ulIndex = TAF_XPDS_DecodeGetRespIndex(pucOneMsgBuf, &stPdMsgHeader);

    ulDataMaskRsp = 0;

    /* process the response buffer */
    ulRes = TAF_XPDS_DecodeRespInfo(pucOneMsgBuf + ulIndex, &stPdMsgHeader, &ulDataMaskRsp);

    if (VOS_OK != ulRes)
    {
        XPDS_ERROR_LOG("TAF_XPDS_DecodeOnePdeMsg: TAF_XPDS_DecodeRespInfo failed");

        *pulOutDataMask = 0;

        return VOS_ERR;
    }

    ulDataMaskReq = 0;

    /* process the request buffer */
    ulRes = TAF_XPDS_DecodeReqInfo(pucOneMsgBuf + TAF_XPDS_PDE_HEADER_LEN_MIN,
                                   &stPdMsgHeader,
                                   &ulDataMaskReq);

    if (VOS_OK != ulRes)
    {
        XPDS_ERROR_LOG("TAF_XPDS_DecodeOnePdeMsg: TAF_XPDS_DecodeReqInfo failed");

        *pulOutDataMask = 0;

        return VOS_ERR;
    }

    *pulOutDataMask = ulDataMaskRsp | ulDataMaskReq;

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_DecodeForwardPdeData(
    VOS_UINT8                          *pucMsgBuf,
    VOS_UINT32                          ulTotLength,
    VOS_UINT32                         *pulOutDataMask
)
{
    VOS_UINT32                          ulRes;
    VOS_UINT32                          ulProcLength;
    VOS_UINT32                          ulCurrMsgLen;
    VOS_UINT8                           aucPdeMsg[TAF_XPDS_MAX_PDM_MSG_BUF_LEN];
    VOS_UINT32                          ulDataMask;
    VOS_UINT32                          ulDataMaskOnePdeMsg;

    /* initialise processed length */
    ulProcLength     = 0;

    ulDataMask = 0;

    /* process every message */
    /* loop till the full buffer is processed */
    while (ulProcLength < ulTotLength)
    {
        /* 当前PDE报文有效字段的长度，不包括消息头的1个比特 */
        ulCurrMsgLen  = pucMsgBuf[0];

        if (ulCurrMsgLen > TAF_XPDS_MAX_DELIVER_DATA_LEN)
        {
            XPDS_ERROR1_LOG("TAF_XPDS_DecodeForwardPdeData: deliver data lengh is:", ulCurrMsgLen);
            return VOS_ERR;
        }

        PS_MEM_SET(aucPdeMsg, 0x00, TAF_XPDS_MAX_PDM_MSG_BUF_LEN);

        /* copy one message */
        PS_MEM_CPY(aucPdeMsg, pucMsgBuf + 1, ulCurrMsgLen);

        ulDataMaskOnePdeMsg = 0;

        /* process one message */
        ulRes = TAF_XPDS_DecodeOnePdeMsg(aucPdeMsg, &ulDataMaskOnePdeMsg); // +1 for skipping data length field of data burst message

        if (ulRes != VOS_OK)
        {
            XPDS_ERROR_LOG("TAF_XPDS_DecodeForwardPdeData: decode msg fail!");
            return VOS_ERR;
        }

        ulDataMask |= ulDataMaskOnePdeMsg;

        /* update the processed length */
        ulProcLength += (ulCurrMsgLen + 1); // +1 for data length field of data burst message

        pucMsgBuf += (ulCurrMsgLen + 1);
    }

    *pulOutDataMask = ulDataMask;

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_DecodeMpcStartPosRsp
 功能描述  : decode PDE ADDR 参考协议(gpsone user plane ms-mpc ch4.2.3.1)
 输入参数  :    ulDataLen: 总数据长度
                *pucData:  数组首地址
                *pusBytePos:当前的数组位置
 输出参数  :    *pstPdeAddr: PDE 地址信息
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月13日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_DecodePdeAddr(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData,
    VOS_UINT16                         *pusBytePos,
    TAF_XPDS_PDE_ADDR_STRU              *pstPdeAddr
)
{
    TAF_XPDS_CFG_INFO_STRU             *pstCagpsCfg;
    VOS_UINT8                           ucIndex;

    /* decode pde addr len */
    pstPdeAddr->ucPdeAddLen     = pucData[*pusBytePos];
    *pusBytePos                += 1;

    if (0 != pstPdeAddr->ucPdeAddLen)
    {
        /* decode pde addr encoding */
        pstPdeAddr->enPdeEncoding = pucData[*pusBytePos];
        *pusBytePos   += 1;

        /* decode pde URL addr */
        if (TAF_XPDS_PDE_ADDR_ENCODE_URL  == pstPdeAddr->enPdeEncoding)
        {
            for (ucIndex = 0;
                 ucIndex < (pstPdeAddr->ucPdeAddLen - 1);
                 ucIndex++)
            {

                pstPdeAddr->aucPdeUrlAddr[ucIndex] = pucData[*pusBytePos];
                *pusBytePos   += 1;
            }
        }
        else if (TAF_XPDS_PDE_ADDR_ENCODE_IP  == pstPdeAddr->enPdeEncoding)
        {
            /* 使用Memcpy 将0XC0A80001 转化成0X0100A8C0  */
            PS_MEM_CPY((VOS_UINT8*)&(pstPdeAddr->ulPdeIpAddr),
                        pucData + *pusBytePos,
                        4);

            *pusBytePos   += 4;

            pstPdeAddr->usPdePortNum = (pucData[*pusBytePos] << 8)
                                       + pucData[*pusBytePos + 1];
            *pusBytePos   += 2;

            pstCagpsCfg = TAF_XPDS_GetAgpsCfg();

            /* IPV4 */
            pstCagpsCfg->ulPdeAddr = pstPdeAddr->ulPdeIpAddr;
            pstCagpsCfg->ulPdePort = pstPdeAddr->usPdePortNum;
        }
        else
        {
            /* 非IP&URL 暂时确定是无效值 */
            XPDS_ERROR_LOG("TAF_MTA_DecodePdeAddr : WRONG PDE ADDR TYPE");

            return VOS_ERR;
        }
    }
    else
    {
        XPDS_ERROR_LOG("TAF_MTA_DecodePdeAddr : NO PDE ADDR");

        return VOS_ERR;
    }

    if (*pusBytePos <= (ulDataLen - 1))
    {
        return VOS_OK;
    }
    else
    {
        XPDS_ERROR_LOG("TAF_MTA_DecodePdeAddr : WRONG PDE ADDR DATA LEN");
        return VOS_ERR;
    }

}

/*****************************************************************************
 函 数 名  : TAF_MTA_DecodeMpcStartPosRsp
 功能描述  : decode mpc pos rsp 参考协议(gpsone user plane ms-mpc ch4.2.3.1)
 输入参数  : ulDataLen        数据长度
             pucData          数据指针
 输出参数  : pstStartPosRsp
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月13日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_DecodeMpcStartPosRsp(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData,
    TAF_XPDS_MPC_START_POS_RSP_STRU    *pstStartPosRsp
)
{
    VOS_UINT16                          usBitPos    = 0;
    VOS_UINT16                          usBytePos   = 0;

    /* decode version */
    pstStartPosRsp->ucVersion   =  pucData[0];
    usBytePos   += 1;

    /* decode msg type */
    pstStartPosRsp->enMsgType   =  pucData[usBytePos];
    usBytePos   += 1;

    /* decode msg len */
    pstStartPosRsp->usLen       =  (pucData[usBytePos] << 8) + pucData[usBytePos + 1];
    usBytePos   += 2;

    /* decode correlation id */
    pstStartPosRsp->ucCorrelationId = pucData[usBytePos];
    usBytePos   += 1;

    /* decode pos status indicator */
    pstStartPosRsp->enPosStatusInd  = pucData[usBytePos];
    usBytePos   += 1;

    if ((TAF_XPDS_POS_STATUS_INDICATOR_USE_GPSONE  == pstStartPosRsp->enPosStatusInd)
     || (TAF_XPDS_POS_STATUS_INDICATOR_CACHED_POS  == pstStartPosRsp->enPosStatusInd)
     || (TAF_XPDS_POS_STATUS_INDICATOR_WITH_CELL_SECTOR == pstStartPosRsp->enPosStatusInd))
    {

        if (VOS_ERR ==  TAF_XPDS_DecodePdeAddr(ulDataLen,
                                              pucData,
                                             &usBytePos,
                                             &pstStartPosRsp->stPdeAddr))
        {
            XPDS_ERROR_LOG("TAF_MTA_DecodeMpcStartPosRsp: TAF_MTA_DecodePdeAddr ERR");
            return VOS_ERR;
        }

        /* decode pos inc flag */
        pstStartPosRsp->usPosIncFlag    =   pucData[usBytePos];
        usBytePos   += 1;

        if (0 == pstStartPosRsp->usPosIncFlag)
        {
            return VOS_OK;
        }

        /* decode time stamp */
        pstStartPosRsp->stTimeStamp.ulWeekNum = (pucData[usBytePos] << 8) + pucData[usBytePos + 1];
        usBytePos   += 2;

        pstStartPosRsp->stTimeStamp.ulSecNum  =   (pucData[usBytePos] << 16)
                                                + (pucData[usBytePos + 1] << 8)
                                                + (pucData[usBytePos + 2]);
        usBytePos   += 3;

        usBitPos     = (VOS_UINT16)(8 * usBytePos);

        /* decode lat */
        pstStartPosRsp->ulLat   = TAF_XPDS_DecodeGetBitsFromBytes(pucData,
                                                           usBitPos,
                                                           25);
        usBitPos   += 25;

        /* decode long */
        pstStartPosRsp->ulLong  = TAF_XPDS_DecodeGetBitsFromBytes(pucData,
                                                           usBitPos,
                                                           26);
        usBitPos   += 26;

        /* decode LOC_UNCRTNTY_ANG */
        pstStartPosRsp->ucLocUncrtntyAng    =  (VOS_UINT8)TAF_XPDS_DecodeGetBitsFromBytes(pucData,
                                                           usBitPos,
                                                           4);
        usBitPos   += 4;

        /* decode LOC_UNCRTNTY_A */
        pstStartPosRsp->ucLocUncrtntyA      =  (VOS_UINT8)TAF_XPDS_DecodeGetBitsFromBytes(pucData,
                                                           usBitPos,
                                                           5);
        usBitPos   += 5;

        /* decode LOC_UNCRTNTY_P */
        pstStartPosRsp->ucLocUncrtntyP      =  (VOS_UINT8)TAF_XPDS_DecodeGetBitsFromBytes(pucData,
                                                           usBitPos,
                                                           5);
        usBitPos   += 5;

        /* decode VELOCITY_INCL */
        pstStartPosRsp->ucVelocityIncl      =  (VOS_UINT8)TAF_XPDS_DecodeGetBitsFromBytes(pucData,
                                                           usBitPos,
                                                           1);
        usBitPos   += 1;

        if (VOS_TRUE == pstStartPosRsp->ucVelocityIncl)
        {
            /* decode VELOCITY_HOR */
            pstStartPosRsp->usVelocityHor   =  (VOS_UINT16)TAF_XPDS_DecodeGetBitsFromBytes(pucData,
                                                           usBitPos,
                                                           9);
            usBitPos   += 9;

            /* decode HEADING */
            pstStartPosRsp->usHeading       =  (VOS_UINT16)TAF_XPDS_DecodeGetBitsFromBytes(pucData,
                                                           usBitPos,
                                                           10);
            usBitPos   += 10;

            /* decode VELOCITY_VER */
            pstStartPosRsp->usVelocityVer   =  (VOS_UINT16)TAF_XPDS_DecodeGetBitsFromBytes(pucData,
                                                           usBitPos,
                                                           8);
            usBitPos   += 8;
        }

        /* decode HEIGHT_INCL */
        pstStartPosRsp->usHeihtIncl         =  (VOS_UINT8)TAF_XPDS_DecodeGetBitsFromBytes(pucData,
                                                           usBitPos,
                                                           1);
        usBitPos   += 1;

        if (VOS_TRUE == pstStartPosRsp->usHeihtIncl)
        {
            /* decode HEIGHT */
            pstStartPosRsp->usHeiht         =  (VOS_UINT16)TAF_XPDS_DecodeGetBitsFromBytes(pucData,
                                                               usBitPos,
                                                               14);
            usBitPos   += 14;

            /* decode LOC_UNCRTNTY_V */
            pstStartPosRsp->usLocUncrtntyV  =  (VOS_UINT8)TAF_XPDS_DecodeGetBitsFromBytes(pucData,
                                                               usBitPos,
                                                               5);
            usBitPos   += 5;

        }

        if (((usBitPos + 7) / 8) == ulDataLen)
        {
            return VOS_OK;
        }
        else
        {
            return VOS_ERR;
        }

    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_DecodeMpcPosReportRsp
 功能描述  : decode mpc pos rsp 参考协议(gpsone user plane ms-mpc ch4.2.3.1)
 输入参数  : ulDataLen        数据长度
             pucData          数据指针
 输出参数  : pstStartPosRsp
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月13日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_DecodeMpcPosReportRsp(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData,
    TAF_XPDS_MPC_POS_REPORT_RSP_STRU   *pstPosReportRsp
)
{
    VOS_UINT16                          usBytePos = 0;

    /* decode version */
    pstPosReportRsp->ucVersion = pucData[usBytePos];
    usBytePos                 += 1;

    /* decode msg_type */
    pstPosReportRsp->enMsgType = pucData[usBytePos];
    usBytePos                 += 1;

    /* decode len */
    pstPosReportRsp->usLen     = (pucData[usBytePos] << 8) + pucData[usBytePos + 1];
    usBytePos                 += 2;

    /* decode correlation id */
    pstPosReportRsp->ucCorrelationId = pucData[usBytePos];
    usBytePos                 += 1;

    /* decode report status indicator */
    pstPosReportRsp->enReportStatus = pucData[usBytePos];

    usBytePos                 += 1;
    if (TAF_XPDS_MPC_REPORT_STATUS_PDE_HANDOFF == pstPosReportRsp->enReportStatus)
    {
        /* decode PDE ADDR */
        if (VOS_ERR == TAF_XPDS_DecodePdeAddr(ulDataLen,
                                             pucData,
                                            &usBytePos,
                                            &pstPosReportRsp->stPdeAddr))
        {
            XPDS_ERROR_LOG("TAF_MTA_DecodeMpcPosReportRsp : TAF_MTA_DecodePdeAddr err");

            return VOS_ERR;
        }

        if (ulDataLen < (usBytePos + 1))
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_DecodeXsmsMpcPosReq
 功能描述  : decode mpc pos req 参考协议(gpsone user plane ms-mpc ch3.1.1.1)
 输入参数  : ulDataLen        数据长度
             pucData          数据指针
 输出参数  : pstStartPosRsp
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月13日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_DecodeXsmsMpcPosReq(
    VOS_UINT32                      ulDataLen,
    VOS_UINT8                      *pucData,
    TAF_XPDS_RCV_XSMS_POS_REQ_STRU *pstPosReportRsp
)
{
    VOS_UINT16                          usBytePos = 0;

    /* decode version */
    pstPosReportRsp->ucVersion = pucData[usBytePos];
    usBytePos                 += 1;

    /* decode msg_type */
    pstPosReportRsp->ucMsgType = pucData[usBytePos];
    usBytePos                 += 1;

    /* decode len */
    pstPosReportRsp->ucLen     = pucData[usBytePos];
    usBytePos                 += 1;

    /* decode enNotificationInd */
    pstPosReportRsp->enNotificationInd  = pucData[usBytePos];
    usBytePos                 += 1;

    /* decode enPosTechInd */
    pstPosReportRsp->enPosTechInd = pucData[usBytePos];
    usBytePos                 += 1;

    /* decode ucPosQoSInc */
    pstPosReportRsp->ucPosQoSInc = pucData[usBytePos];
    usBytePos                 += 1;

    /* decode ucPosQoS */
    pstPosReportRsp->ucPosQoS = pucData[usBytePos];
    usBytePos                 += 1;

    /* decode usNumOfFixs */
    pstPosReportRsp->usNumOfFixs = (pucData[usBytePos] << 8) + pucData[usBytePos + 1];
    usBytePos                 += 2;

    /* decode usTimeBetweenFixs */
    pstPosReportRsp->usTimeBetweenFixs  = (pucData[usBytePos] << 8) + pucData[usBytePos + 1];
    usBytePos                 += 2;

    /* decode enIS801PosMode */
    pstPosReportRsp->enIS801PosMode = pucData[usBytePos];
    usBytePos                 += 1;

    /* decode ucCorrelationId */
    pstPosReportRsp->ucCorrelationId  = pucData[usBytePos];
    usBytePos                 += 1;

    /* decode ucReqIdEncode */
    pstPosReportRsp->ucReqIdEncode  = pucData[usBytePos];
    usBytePos                 += 1;

    /* decode ucReqIdLen */
    pstPosReportRsp->ucReqIdLen = pucData[usBytePos];
    usBytePos                 += 1;

    /* decode ucReqId  */
    PS_MEM_CPY(pstPosReportRsp->aucData, pucData + usBytePos, pstPosReportRsp->ucReqIdLen);
    usBytePos                 +=  pstPosReportRsp->ucReqIdLen;

    if (usBytePos == ulDataLen)
    {
        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_DecodeXsms
 功能描述  : decode mpc pos req 参考协议(gpsone user plane ms-mpc ch3.1.1.1)
 输入参数  : ulDataLen        数据长度
             pucData          数据指针
 输出参数  : pstStartPosRsp
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月13日
    作    者   : c00299064
    修改内容   : 新生成函数
  2.日    期   : 2015年09月06日
    作    者   : y00174758
    修改内容   : AGPS迭代2: 增加
*****************************************************************************/
TAF_XPDS_XSMS_MSG_DECODE_RSLT_ENUM_UINT8 TAF_XPDS_DecodeXsmsRcvMsg(
    VOS_UINT32                      ulDataLen,
    VOS_UINT8                      *pucData,
    TAF_XPDS_RCV_XSMS_MSG_STRU     *pstXsmsMsg
)
{
    VOS_UINT32                          ulRet = VOS_OK;

    pstXsmsMsg->enMsgChoice             = pucData[1];

    switch (pucData[1])
    {
        case TAF_XPDS_RCV_XSMS_MSG_TYPE_NI_POS_REQ:

            ulRet = TAF_XPDS_DecodeXsmsMpcPosReq(ulDataLen,
                                                      pucData,
                                                     &pstXsmsMsg->stXsmsMsgUnion.stPosReq);

            TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_SMS_MPC_FL_POS_REQ);

            break;

        case TAF_XPDS_RCV_XSMS_MSG_TYPE_CANCEL_NI_TRACK:

            PS_MEM_CPY(&pstXsmsMsg->stXsmsMsgUnion.stCancelNI,
                pucData,
                sizeof(TAF_XPDS_RCV_CANCEL_NI_TRACK_STRU));

            TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_SMS_MPC_FL_CANCEL_NI_TRACK);

            break;

        case TAF_XPDS_RCV_XSMS_MSG_TYPE_REFRESH_MR_TRACK:

            PS_MEM_CPY(&pstXsmsMsg->stXsmsMsgUnion.stRefreshMR,
                pucData,
                sizeof(TAF_XPDS_RCV_REFRESH_MR_TRACK_STRU));

            TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_SMS_MPC_FL_REFRESH_MR_TRACK);

            break;

        default:
            XPDS_ERROR_LOG("TAF_XPDS_DecodeXsmsRcvMsg:wrong msg type");
            return TAF_XPDS_XSMS_MSG_DECODE_RSLT_ERROR;
    }

    if (VOS_OK == ulRet)
    {
        if (TAF_XPDS_CUR_VERSION != pucData[0])
        {
            return TAF_XPDS_XSMS_MSG_DECODE_RSLT_UNSUPPORTED_VERSION;
        }
        else
        {
            return TAF_XPDS_XSMS_MSG_DECODE_RSLT_SUCCESS;
        }
    }
    else
    {
        return TAF_XPDS_XSMS_MSG_DECODE_RSLT_ERROR;
    }
}


#if 0


VOS_UINT32 TAF_XPDS_DecodeExtReject(
    VOS_UINT8                              *pucHeadBuf
)
{
    VOS_UINT32                                 ulTotNumOfBits;
    VOS_UINT32                                 ulCurrIdx;
    TAF_XPDS_FWDLINK_RSP_EXT_REJECT_STRU      *pstExtReject;

    pstExtReject  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_RSP_EXT_REJECT_STRU));
    if (VOS_NULL_PTR == pstExtReject)
    {
        return VOS_ERR;
    }

    PS_MEM_SET(pstExtReject, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_REJECT_STRU));

    ulTotNumOfBits          = 3;
    ulCurrIdx               = 0;

    /* rejected request type */
    pstExtReject->ucRejReqType      = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                      &ulTotNumOfBits,
                                                                      &pucHeadBuf[ulCurrIdx],
                                                                      &ulCurrIdx);

    /* reason for rejection */
    pstExtReject->ucRejReason       = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                      &ulTotNumOfBits,
                                                                      &pucHeadBuf[ulCurrIdx],
                                                                      &ulCurrIdx);

    /* ertry time present or not */
    pstExtReject->ucRetryTimeIncl   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                      &ulTotNumOfBits,
                                                                      &pucHeadBuf[ulCurrIdx],
                                                                      &ulCurrIdx);

    if (VOS_TRUE == pstExtReject->ucRetryTimeIncl)
    {
        /* ertry time present or not */
        pstExtReject->ucRetryTime   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                          &ulTotNumOfBits,
                                                                          &pucHeadBuf[ulCurrIdx],
                                                                          &ulCurrIdx);
    }

    PS_MEM_FREE(UEPS_PID_XPDS, pstExtReject);

    return VOS_OK;
}



VOS_UINT32 TAF_XPDS_DecodeProvExtLocResp(
    VOS_UINT8                               *pucHeadBuf
)
{
    VOS_UINT32                                     ulTotNumOfBits;
    VOS_UINT32                                     ulCurrIdx;
    TAF_XPDS_FWDLINK_RSP_EXT_LOC_RESP_STRU        *pstProvExtLocRsp;

    pstProvExtLocRsp  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_RSP_EXT_LOC_RESP_STRU));
    if (VOS_NULL_PTR == pstProvExtLocRsp)
    {
        return VOS_ERR;
    }

    PS_MEM_SET(pstProvExtLocRsp, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_EXT_LOC_RESP_STRU));

    ulTotNumOfBits              = 3;
    ulCurrIdx                   = 0;

    /* time reference included or not */
    pstProvExtLocRsp->ucTimeRefIncl = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);
    if (VOS_TRUE == pstProvExtLocRsp->ucTimeRefIncl)
    {
        /* time reference */
        pstProvExtLocRsp->ulTimeRef = (VOS_UINT32)TAF_XPDS_DecodeGetValue(22,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);
    }


    /* fix type information included or not */
    pstProvExtLocRsp->ucFixTypeIncl = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                       &ulTotNumOfBits,
                                                                       &pucHeadBuf[ulCurrIdx],
                                                                       &ulCurrIdx);

    if(VOS_TRUE == pstProvExtLocRsp->ucFixTypeIncl)
    {
        /* fix type */
        pstProvExtLocRsp->ucFixType = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);
    }

    /* lattitude */
    pstProvExtLocRsp->ulLattitude   = (VOS_UINT32)TAF_XPDS_DecodeGetValue(25,
                                                                       &ulTotNumOfBits,
                                                                       &pucHeadBuf[ulCurrIdx],
                                                                       &ulCurrIdx);

    /* longitude */
    pstProvExtLocRsp->ulLongitude   = (VOS_UINT32)TAF_XPDS_DecodeGetValue(26,
                                                                       &ulTotNumOfBits,
                                                                       &pucHeadBuf[ulCurrIdx],
                                                                       &ulCurrIdx);

    /* horizontal location uncertainity type */
    pstProvExtLocRsp->ucLocUncHType     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                       &ulTotNumOfBits,
                                                                       &pucHeadBuf[ulCurrIdx],
                                                                       &ulCurrIdx);

    /* horizontal location uncertainity type */
    pstProvExtLocRsp->ucLocUncHType     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                       &ulTotNumOfBits,
                                                                       &pucHeadBuf[ulCurrIdx],
                                                                       &ulCurrIdx);

    if (0x00 == pstProvExtLocRsp->ucLocUncHType)
    {
        /* horizontal location uncertainity */
        pstProvExtLocRsp->ucLocUncH     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);

        /* horizontal location uncertainity confidential level */
        pstProvExtLocRsp->ucLocUncHCnf  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);

    }
    else if (0x01 == pstProvExtLocRsp->ucLocUncHType)
    {
        /* angle of axis of standard error eclipse for horizontal location uncertainity */
        pstProvExtLocRsp->ucLocUncAng   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);

        /* standard deviation of error along angle specified for Horizontal loc uncertainity */
        pstProvExtLocRsp->ucLocUncA     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);

        /* standard deviation of error perpendicular angle specified for Horizontal loc uncertainity */
        pstProvExtLocRsp->ucLocUncP     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);
    }
    else
    {
        PS_MEM_FREE(UEPS_PID_XPDS, pstProvExtLocRsp);
        return VOS_ERR;
    }


    /* height information included or not */
    pstProvExtLocRsp->ucHeightIncl     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                       &ulTotNumOfBits,
                                                                       &pucHeadBuf[ulCurrIdx],
                                                                       &ulCurrIdx);

    if (VOS_TRUE == pstProvExtLocRsp->ucHeightIncl)
    {
        /* height in meters */
        pstProvExtLocRsp->usHeight     = (VOS_UINT16)TAF_XPDS_DecodeGetValue(14,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);

        /* vertical location uncertainity */
        pstProvExtLocRsp->ucLocUncV     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);

        /* vertical location uncertainity confidential level */
        pstProvExtLocRsp->ucLocUncVCnf     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);
    }

    /* velocity information included or not */
    pstProvExtLocRsp->ucVeloIncl     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                       &ulTotNumOfBits,
                                                                       &pucHeadBuf[ulCurrIdx],
                                                                       &ulCurrIdx);

    if (VOS_TRUE == pstProvExtLocRsp->ucVeloIncl)
    {
        /* horizontal velocity magnitude */
        pstProvExtLocRsp->usVeloHor     = (VOS_UINT16)TAF_XPDS_DecodeGetValue(11,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);

        /* horizontal velocity magnitude */
        pstProvExtLocRsp->usHeading     = (VOS_UINT16)TAF_XPDS_DecodeGetValue(10,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);

        /* Horizontal velocity uncertainity type */
        pstProvExtLocRsp->ucVeloUncHType     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);

        if (0x00 == pstProvExtLocRsp->ucVeloUncHType)
        {
            /* horizontal velocity uncertainity */
            pstProvExtLocRsp->ucVeloUncH     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                               &ulTotNumOfBits,
                                                                               &pucHeadBuf[ulCurrIdx],
                                                                               &ulCurrIdx);

            /* horizontal velocity uncertainity */
            pstProvExtLocRsp->ucVeloUncHCnf = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                                               &ulTotNumOfBits,
                                                                               &pucHeadBuf[ulCurrIdx],
                                                                               &ulCurrIdx);
        }
        else if (0x01 == pstProvExtLocRsp->ucVeloUncHType)
        {
            /* angle of axis of standard error eclipse for horizontal velocity uncertainity */
            pstProvExtLocRsp->ucVeloUncAng  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                               &ulTotNumOfBits,
                                                                               &pucHeadBuf[ulCurrIdx],
                                                                               &ulCurrIdx);

            /* standard deviation of error along angle specified for Horizontal velocity uncertainity */
            pstProvExtLocRsp->ucVeloUncA    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                               &ulTotNumOfBits,
                                                                               &pucHeadBuf[ulCurrIdx],
                                                                               &ulCurrIdx);

            /* standard deviation of error perpendicular angle specified for Horizontal velocity uncertainity */
            pstProvExtLocRsp->ucVeloUncP    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                               &ulTotNumOfBits,
                                                                               &pucHeadBuf[ulCurrIdx],
                                                                               &ulCurrIdx);

        }
        else
        {
            PS_MEM_FREE(UEPS_PID_XPDS, pstProvExtLocRsp);
            return VOS_ERR;
        }

        /* vertical velocity included or not */
        pstProvExtLocRsp->ucVeloVertIncl   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);

        if (VOS_TRUE == pstProvExtLocRsp->ucVeloVertIncl)
        {
            /* vertical velocity */
            pstProvExtLocRsp->ucVeloVert   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                               &ulTotNumOfBits,
                                                                               &pucHeadBuf[ulCurrIdx],
                                                                               &ulCurrIdx);

            /* vertical velocity uncertainity */
            pstProvExtLocRsp->ucVeloUncV   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                               &ulTotNumOfBits,
                                                                               &pucHeadBuf[ulCurrIdx],
                                                                               &ulCurrIdx);

            /* vertical velocity uncertainity confidential level */
            pstProvExtLocRsp->ucVeloUncVCnf   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                                               &ulTotNumOfBits,
                                                                               &pucHeadBuf[ulCurrIdx],
                                                                               &ulCurrIdx);
        }
    }

    /* clock bias included or not */
    pstProvExtLocRsp->ucClockBiasIncl   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                       &ulTotNumOfBits,
                                                                       &pucHeadBuf[ulCurrIdx],
                                                                       &ulCurrIdx);

    if (pstProvExtLocRsp->ucClockBiasIncl )
    {
        /* clock bias */
        pstProvExtLocRsp->ulClockBias   = (VOS_UINT32)TAF_XPDS_DecodeGetValue(18,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);
    }

    /* clock drift included or not */
    pstProvExtLocRsp->ucClockDriftIncl  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                       &ulTotNumOfBits,
                                                                       &pucHeadBuf[ulCurrIdx],
                                                                       &ulCurrIdx);

    if (pstProvExtLocRsp->ucClockDriftIncl )
    {
        /* clock bias */
        pstProvExtLocRsp->ulClockDrift   = (VOS_UINT32)TAF_XPDS_DecodeGetValue(17,
                                                                           &ulTotNumOfBits,
                                                                           &pucHeadBuf[ulCurrIdx],
                                                                           &ulCurrIdx);
    }

    PS_MEM_FREE(UEPS_PID_XPDS, pstProvExtLocRsp);

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_DecodeExtBsCapabilities(
    VOS_UINT8                               *pucHeadBuf
)
{
    VOS_UINT32                                  ulTotNumOfBits;
    VOS_UINT32                                  ulCurrIdx;
    TAF_XPDS_FWDLINK_RSP_EXT_BS_CAP_STRU       *pstProvExtBsCap;

    pstProvExtBsCap  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_RSP_EXT_BS_CAP_STRU));
    if (VOS_NULL_PTR == pstProvExtBsCap)
    {
        return VOS_ERR;
    }

    PS_MEM_SET(pstProvExtBsCap, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_EXT_BS_CAP_STRU));

    ulTotNumOfBits              = 3;
    ulCurrIdx                   = 0;

    /* base station location standard revision number */
    pstProvExtBsCap->ucBsLsRev  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(6,
                                                                  &ulTotNumOfBits,
                                                                  &pucHeadBuf[ulCurrIdx],
                                                                  &ulCurrIdx);
    /* GPS capability indicator */
    pstProvExtBsCap->ucGpscId   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                  &ulTotNumOfBits,
                                                                  &pucHeadBuf[ulCurrIdx],
                                                                  &ulCurrIdx);
    /* advanced forward link trilateration capability indicator */
    pstProvExtBsCap->ucAfltcId  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                  &ulTotNumOfBits,
                                                                  &pucHeadBuf[ulCurrIdx],
                                                                  &ulCurrIdx);

    /* ephimeries life extension capability indicator */
    pstProvExtBsCap->ucEphLifeExtCap  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                        &ulTotNumOfBits,
                                                                        &pucHeadBuf[ulCurrIdx],
                                                                        &ulCurrIdx);

    /* autonomous position determination capability indicator */
    pstProvExtBsCap->ucApdcId  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                 &ulTotNumOfBits,
                                                                 &pucHeadBuf[ulCurrIdx],
                                                                 &ulCurrIdx);

    PS_MEM_FREE(UEPS_PID_XPDS, pstProvExtBsCap);

    return VOS_OK;
}



VOS_UINT32 TAF_XPDS_DecodeEnhBsAlmanac(
    VOS_UINT8                               *pucHeadBuf
)
{
    VOS_UINT32                                  ulTotNumOfBits;
    VOS_UINT32                                  ulCurrIdx;
    TAF_XPDS_FWDLINK_RSP_ENH_BS_ALM_STRU       *pstProvEnhBsAlm;
    VOS_UINT8                                   ucPartNum;
    VOS_UINT8                                   ucTotalParts;
    VOS_UINT32                                  ulLatRef;
    VOS_UINT32                                  ulLongRef;
    VOS_UINT8                                   ucNumOfFreqP;
    VOS_UINT8                                   ucPrevNumOfFreqP;
    VOS_UINT8                                   ucLoopCount;
    VOS_UINT8                                   ucLoopCount2;
    VOS_UINT8                                   ucLoopCount3;
    VOS_UINT8                                   ucLoopCount4;
    VOS_UINT8                                   ucLoopCount5;
    TAF_XPDS_ENH_BS_ALM_PILOT_INFO_STRU        *pstEnhBSAlmInfo;

    ucLoopCount     = 0;
    ucLoopCount2    = 0;
    ucLoopCount3    = 0;
    ucLoopCount4    = 0;
    ucLoopCount5    = 0;

    pstProvEnhBsAlm  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_RSP_ENH_BS_ALM_STRU));
    if (VOS_NULL_PTR == pstProvEnhBsAlm)
    {
        return VOS_ERR;
    }

    ulTotNumOfBits              = 3;
    ulCurrIdx                   = 0;

    /* part number */
    ucPartNum  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                      &ulTotNumOfBits,
                                                      &pucHeadBuf[ulCurrIdx],
                                                      &ulCurrIdx);

    /* total number of parts */
    ucTotalParts   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                      &ulTotNumOfBits,
                                                      &pucHeadBuf[ulCurrIdx],
                                                      &ulCurrIdx);

    /* reference longitude */
    ulLatRef   = (VOS_UINT32)TAF_XPDS_DecodeGetValue(23,
                                                      &ulTotNumOfBits,
                                                      &pucHeadBuf[ulCurrIdx],
                                                      &ulCurrIdx);

    /* reference longitude */
    ulLongRef  = (VOS_UINT32)TAF_XPDS_DecodeGetValue(24,
                                                      &ulTotNumOfBits,
                                                      &pucHeadBuf[ulCurrIdx],
                                                      &ulCurrIdx);

    /* number of frequency record */
    ucNumOfFreqP   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                      &ulTotNumOfBits,
                                                      &pucHeadBuf[ulCurrIdx],
                                                      &ulCurrIdx);

    if (0x00 == ucPartNum)
    {
        PS_MEM_SET(pstProvEnhBsAlm, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_ENH_BS_ALM_STRU));
    }

    ucPrevNumOfFreqP                = pstProvEnhBsAlm->ucNumOfFreqP;
    pstProvEnhBsAlm->ucNumOfFreqP  += ucNumOfFreqP;
    pstProvEnhBsAlm->ucPartNum      = ucPartNum;
    pstProvEnhBsAlm->ucTotalParts   = ucTotalParts;
    pstProvEnhBsAlm->ulLatRef       = ulLatRef;
    pstProvEnhBsAlm->ulLongRef      = ulLongRef;

    for (ucLoopCount = ucPrevNumOfFreqP; ucLoopCount < pstProvEnhBsAlm->ucNumOfFreqP; ucLoopCount++)
    {

        /* band class */
        pstProvEnhBsAlm->astFreqInfo[ucLoopCount].ucBandClass = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                              &ulTotNumOfBits,
                                                                              &pucHeadBuf[ulCurrIdx],
                                                                              &ulCurrIdx);

        /* frequency assignment */
        pstProvEnhBsAlm->astFreqInfo[ucLoopCount].usCdmaFreq = (VOS_UINT16)TAF_XPDS_DecodeGetValue(11,
                                                                              &ulTotNumOfBits,
                                                                              &pucHeadBuf[ulCurrIdx],
                                                                              &ulCurrIdx);

        /* mode indicator */
        pstProvEnhBsAlm->astFreqInfo[ucLoopCount].ucModeInd  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                                              &ulTotNumOfBits,
                                                                              &pucHeadBuf[ulCurrIdx],
                                                                              &ulCurrIdx);

        /* pilot information as previous or not */
        pstProvEnhBsAlm->astFreqInfo[ucLoopCount].ucPilInfAsPrev  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                              &ulTotNumOfBits,
                                                                              &pucHeadBuf[ulCurrIdx],
                                                                              &ulCurrIdx);

        if (VOS_FALSE == pstProvEnhBsAlm->astFreqInfo[ucLoopCount].ucPilInfAsPrev)
        {

            /* pilot identification included or not */
            pstProvEnhBsAlm->astFreqInfo[ucLoopCount].ucPilotIdIncl  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                  &ulTotNumOfBits,
                                                                                  &pucHeadBuf[ulCurrIdx],
                                                                                  &ulCurrIdx);

            /* repeater information included or not */
            pstProvEnhBsAlm->astFreqInfo[ucLoopCount].ucRptrInfIncl  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                  &ulTotNumOfBits,
                                                                                  &pucHeadBuf[ulCurrIdx],
                                                                                  &ulCurrIdx);

            if (VOS_TRUE == pstProvEnhBsAlm->astFreqInfo[ucLoopCount].ucRptrInfIncl)
            {
                /* repeater identification length */
                pstProvEnhBsAlm->astFreqInfo[ucLoopCount].ucRptrIdLen  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(6,
                                                                                      &ulTotNumOfBits,
                                                                                      &pucHeadBuf[ulCurrIdx],
                                                                                      &ulCurrIdx);
            }

            /* repeater identification length */
            pstProvEnhBsAlm->astFreqInfo[ucLoopCount].usNumOfPilTxF  = (VOS_UINT16)TAF_XPDS_DecodeGetValue(9,
                                                                                  &ulTotNumOfBits,
                                                                                  &pucHeadBuf[ulCurrIdx],
                                                                                  &ulCurrIdx);

            for (ucLoopCount2 = 0; ucLoopCount2 < pstProvEnhBsAlm->astFreqInfo[ucLoopCount].usNumOfPilTxF; ucLoopCount2++)
            {

                pstEnhBSAlmInfo = &pstProvEnhBsAlm->astFreqInfo[ucLoopCount].astPilotInfo[ucLoopCount2];

                /* pilot record length */
                pstEnhBSAlmInfo->ucPilRecLen = (VOS_UINT8)TAF_XPDS_DecodeGetValue(7,
                                                                                      &ulTotNumOfBits,
                                                                                      &pucHeadBuf[ulCurrIdx],
                                                                                      &ulCurrIdx);

                /* pilot signal transmission type */
                pstEnhBSAlmInfo->ucPilTxType = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                                                      &ulTotNumOfBits,
                                                                                      &pucHeadBuf[ulCurrIdx],
                                                                                      &ulCurrIdx);


                if (0x00 == pstEnhBSAlmInfo->ucPilTxType)
                {
                    /* pilot signal transmission type */
                    pstEnhBSAlmInfo->stPilPxTypSpc.stPilPxTyp00.usPilotPn = (VOS_UINT16)TAF_XPDS_DecodeGetValue(9,
                                                                                                          &ulTotNumOfBits,
                                                                                                          &pucHeadBuf[ulCurrIdx],
                                                                                                          &ulCurrIdx);

                    if (VOS_TRUE == pstProvEnhBsAlm->astFreqInfo[ucLoopCount].ucPilotIdIncl)
                    {
                        /* whether SID and NID as previous or not */
                        pstEnhBSAlmInfo->stPilPxTypSpc.stPilPxTyp00.ucSidNidAsPrev = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                                              &ulTotNumOfBits,
                                                                                                              &pucHeadBuf[ulCurrIdx],
                                                                                                              &ulCurrIdx);

                        if(VOS_FALSE == pstEnhBSAlmInfo->stPilPxTypSpc.stPilPxTyp00.ucSidNidAsPrev)
                        {
                            /* system ID */
                            pstEnhBSAlmInfo->stPilPxTypSpc.stPilPxTyp00.usSID = (VOS_UINT16)TAF_XPDS_DecodeGetValue(15,
                                                                                                                  &ulTotNumOfBits,
                                                                                                                  &pucHeadBuf[ulCurrIdx],
                                                                                                                  &ulCurrIdx);

                            /* network ID */
                            pstEnhBSAlmInfo->stPilPxTypSpc.stPilPxTyp00.usNID = (VOS_UINT16)TAF_XPDS_DecodeGetValue(16,
                                                                                                                  &ulTotNumOfBits,
                                                                                                                  &pucHeadBuf[ulCurrIdx],
                                                                                                                  &ulCurrIdx);
                        }

                        /* base station ID */
                        pstEnhBSAlmInfo->stPilPxTypSpc.stPilPxTyp00.usBaseId = (VOS_UINT16)TAF_XPDS_DecodeGetValue(16,
                                                                                                              &ulTotNumOfBits,
                                                                                                              &pucHeadBuf[ulCurrIdx],
                                                                                                              &ulCurrIdx);


                        if (0x01 == pstProvEnhBsAlm->astFreqInfo[ucLoopCount].ucModeInd)
                        {
                            for (ucLoopCount3 = 0; ucLoopCount3 < TAF_XPDS_FL_SEC_ID_LEN; ucLoopCount3++)
                            {
                                /* sector ID */
                                pstEnhBSAlmInfo->stPilPxTypSpc.stPilPxTyp00.aucSectorId[ucLoopCount3] = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                                                                          &ulTotNumOfBits,
                                                                                                                                          &pucHeadBuf[ulCurrIdx],
                                                                                                                                          &ulCurrIdx);
                            }
                        }
                    }

                    if (VOS_TRUE == pstProvEnhBsAlm->astFreqInfo[ucLoopCount].ucRptrInfIncl)
                    {
                        /* unlisted repeaters */
                        pstEnhBSAlmInfo->stPilPxTypSpc.stPilPxTyp00.ucUnsolRptrs = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                                                                          &ulTotNumOfBits,
                                                                                                                          &pucHeadBuf[ulCurrIdx],
                                                                                                                          &ulCurrIdx);
                    }

                    /* reserved */
                    pstEnhBSAlmInfo->stPilPxTypSpc.stPilPxTyp00.aucReserved[0]  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                                                      &ulTotNumOfBits,
                                                                                                                      &pucHeadBuf[ulCurrIdx],
                                                                                                                      &ulCurrIdx);

                    /* reserved */
                    pstEnhBSAlmInfo->stPilPxTypSpc.stPilPxTyp00.aucReserved[1]  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                                                      &ulTotNumOfBits,
                                                                                                                      &pucHeadBuf[ulCurrIdx],
                                                                                                                      &ulCurrIdx);

                }
                else if (0x01 == pstEnhBSAlmInfo->ucPilTxType)
                {
                    /*  RPTR type */
                    pstEnhBSAlmInfo->stPilPxTypSpc.stPilPxTyp01.ucRptrType  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                                                                      &ulTotNumOfBits,
                                                                                                                      &pucHeadBuf[ulCurrIdx],
                                                                                                                      &ulCurrIdx);
                    if (0x01 != pstEnhBSAlmInfo->stPilPxTypSpc.stPilPxTyp01.ucRptrType)
                    {
                        /* whether RPTR included or not */
                        pstEnhBSAlmInfo->stPilPxTypSpc.stPilPxTyp01.ucRptrIdIncl  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                                                          &ulTotNumOfBits,
                                                                                                                          &pucHeadBuf[ulCurrIdx],
                                                                                                                          &ulCurrIdx);

                        if (VOS_TRUE == pstEnhBSAlmInfo->stPilPxTypSpc.stPilPxTyp01.ucRptrIdIncl)
                        {
                            for (ucLoopCount4 = 0; ucLoopCount4 <= pstProvEnhBsAlm->astFreqInfo[ucLoopCount].ucRptrIdLen; ucLoopCount4++)
                            {
                                /* Rptr ID */
                                pstEnhBSAlmInfo->stPilPxTypSpc.stPilPxTyp01.aucRptrId[ucLoopCount4]  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                                                                  &ulTotNumOfBits,
                                                                                                                                  &pucHeadBuf[ulCurrIdx],
                                                                                                                                  &ulCurrIdx);

                            }
                        }
                    }


                    /* reservd */
                    pstEnhBSAlmInfo->stPilPxTypSpc.stPilPxTyp01.aucReserved[0]  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                                                      &ulTotNumOfBits,
                                                                                                                      &pucHeadBuf[ulCurrIdx],
                                                                                                                      &ulCurrIdx);
                    /* reservd */
                    pstEnhBSAlmInfo->stPilPxTypSpc.stPilPxTyp01.aucReserved[1]  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                                                      &ulTotNumOfBits,
                                                                                                                      &pucHeadBuf[ulCurrIdx],
                                                                                                                      &ulCurrIdx);
                }
                else
                {

                    PS_MEM_FREE(UEPS_PID_XPDS, pstProvEnhBsAlm);
                    return VOS_ERR;
                }

                /* location as previous or not */
                pstEnhBSAlmInfo->ucLocAsPrev = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                      &ulTotNumOfBits,
                                                                                      &pucHeadBuf[ulCurrIdx],
                                                                                      &ulCurrIdx);
                if (VOS_FALSE == pstEnhBSAlmInfo->ucLocAsPrev)
                {
                    /* difference in lattitude relative to reference */
                    pstEnhBSAlmInfo->usDeltaLat = (VOS_UINT16)TAF_XPDS_DecodeGetValue(16,
                                                                                          &ulTotNumOfBits,
                                                                                          &pucHeadBuf[ulCurrIdx],
                                                                                          &ulCurrIdx);

                    /* difference in longitude relative to reference */
                    pstEnhBSAlmInfo->usDeltaLong = (VOS_UINT16)TAF_XPDS_DecodeGetValue(16,
                                                                                          &ulTotNumOfBits,
                                                                                          &pucHeadBuf[ulCurrIdx],
                                                                                          &ulCurrIdx);

                    /* standard deviation of horizontal location error */
                    pstEnhBSAlmInfo->ucLocUncH  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                                          &ulTotNumOfBits,
                                                                                          &pucHeadBuf[ulCurrIdx],
                                                                                          &ulCurrIdx);

                    /* height information included or not */
                    pstEnhBSAlmInfo->ucHeightIncl  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                          &ulTotNumOfBits,
                                                                                          &pucHeadBuf[ulCurrIdx],
                                                                                          &ulCurrIdx);

                    if (VOS_TRUE == pstEnhBSAlmInfo->ucHeightIncl)
                    {
                        /* height of the antenna */
                        pstEnhBSAlmInfo->usHeight  = (VOS_UINT16)TAF_XPDS_DecodeGetValue(10,
                                                                                              &ulTotNumOfBits,
                                                                                              &pucHeadBuf[ulCurrIdx],
                                                                                              &ulCurrIdx);
                    }

                }

                /* altitude aiding information as previous or not */
                pstEnhBSAlmInfo->ucAltInfAsPrev  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                      &ulTotNumOfBits,
                                                                                      &pucHeadBuf[ulCurrIdx],
                                                                                      &ulCurrIdx);

                if (VOS_FALSE == pstEnhBSAlmInfo->ucAltInfAsPrev)
                {
                    /* average terraiin height */
                    pstEnhBSAlmInfo->usAvrgTerrHeight  = (VOS_UINT16)TAF_XPDS_DecodeGetValue(10,
                                                                                          &ulTotNumOfBits,
                                                                                          &pucHeadBuf[ulCurrIdx],
                                                                                          &ulCurrIdx);

                    /* standard deviation of terrain height */
                    pstEnhBSAlmInfo->ucTerrHeightVar  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                                          &ulTotNumOfBits,
                                                                                          &pucHeadBuf[ulCurrIdx],
                                                                                          &ulCurrIdx);
                }

                /* time correction is as previous or not */
                pstEnhBSAlmInfo->ucTimeCorrAsPrev  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                      &ulTotNumOfBits,
                                                                                      &pucHeadBuf[ulCurrIdx],
                                                                                      &ulCurrIdx);
                if (VOS_FALSE == pstEnhBSAlmInfo->ucTimeCorrAsPrev )
                {
                    /* time correction */
                    pstEnhBSAlmInfo->usTimeCorr  = (VOS_UINT16)TAF_XPDS_DecodeGetValue(10,
                                                                                          &ulTotNumOfBits,
                                                                                          &pucHeadBuf[ulCurrIdx],
                                                                                          &ulCurrIdx);

                    /* standard deviation of time correction error */
                    pstEnhBSAlmInfo->ucTimeCorrUnc  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                                          &ulTotNumOfBits,
                                                                                          &pucHeadBuf[ulCurrIdx],
                                                                                          &ulCurrIdx);
                }


                /* antenna angle information included or not */
                pstEnhBSAlmInfo->ucAntAngInfIncl  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                      &ulTotNumOfBits,
                                                                                      &pucHeadBuf[ulCurrIdx],
                                                                                      &ulCurrIdx);

                if (VOS_TRUE == pstEnhBSAlmInfo->ucAntAngInfIncl)
                {
                    /* antenna opening angle */
                    pstEnhBSAlmInfo->ucAntOpenAng  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(6,
                                                                                          &ulTotNumOfBits,
                                                                                          &pucHeadBuf[ulCurrIdx],
                                                                                          &ulCurrIdx);

                    /* antenna azimuth */
                    pstEnhBSAlmInfo->ucAntAzimuth  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(6,
                                                                                          &ulTotNumOfBits,
                                                                                          &pucHeadBuf[ulCurrIdx],
                                                                                          &ulCurrIdx);
                }

                /* antenna range information included or not */
                pstEnhBSAlmInfo->ucAntRngInfIncl  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                      &ulTotNumOfBits,
                                                                                      &pucHeadBuf[ulCurrIdx],
                                                                                      &ulCurrIdx);
                if (VOS_TRUE == pstEnhBSAlmInfo->ucAntRngInfIncl )
                {
                    /* number of antenna ranges */
                    pstEnhBSAlmInfo->ucNumOfAnrRngs  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                                          &ulTotNumOfBits,
                                                                                          &pucHeadBuf[ulCurrIdx],
                                                                                          &ulCurrIdx);

                    for (ucLoopCount5 = 0; ucLoopCount5 < pstEnhBSAlmInfo->ucNumOfAnrRngs; ucLoopCount5++)
                    {
                        /* reference recieved pilot power */
                        pstEnhBSAlmInfo->astAntenaInfo[ucLoopCount5].ucRefRxPow = (VOS_UINT8)TAF_XPDS_DecodeGetValue(7,
                                                                                              &ulTotNumOfBits,
                                                                                              &pucHeadBuf[ulCurrIdx],
                                                                                              &ulCurrIdx);

                        /* antenna range */
                        pstEnhBSAlmInfo->astAntenaInfo[ucLoopCount5].usAntRange = (VOS_UINT16)TAF_XPDS_DecodeGetValue(14,
                                                                                              &ulTotNumOfBits,
                                                                                              &pucHeadBuf[ulCurrIdx],
                                                                                              &ulCurrIdx);
                    }

                }

                if (0 != (ulTotNumOfBits %8))
                {
                    ulCurrIdx++;
                    ulTotNumOfBits += (8 - (ulTotNumOfBits %8));
                }

            }
        }
    }

    if (0 != (ulTotNumOfBits %8))
    {
        ulCurrIdx++;
        ulTotNumOfBits += (8 - (ulTotNumOfBits %8));
    }

    PS_MEM_FREE(UEPS_PID_XPDS, pstProvEnhBsAlm);

    return VOS_OK;
}




VOS_UINT32 TAF_XPDS_DecodeRequestExtLocResp(
    VOS_UINT8                          *pucHeadBuf
)
{

    VOS_UINT32                               ulNumBitsProcessed;
    VOS_UINT32                               ulCurIdx;
    TAF_XPDS_FWDLINK_REQ_EXT_LOC_RESP_STRU  *pstFwdExtReqLocResp;

    ulNumBitsProcessed   = 2; /* 2 is the number of bits from req length field */
    ulCurIdx             = 0;

    pstFwdExtReqLocResp  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_REQ_EXT_LOC_RESP_STRU));
    if (VOS_NULL_PTR == pstFwdExtReqLocResp)
    {
        return VOS_ERR;
    }

    /* update the response flag for Provide location response */
    TAF_XPDS_SetReqExtLocRespFlag(VOS_TRUE);

    PS_MEM_SET(pstFwdExtReqLocResp, 0x00, sizeof(TAF_XPDS_FWDLINK_REQ_EXT_LOC_RESP_STRU));


    /* get the Number of fixes */
    pstFwdExtReqLocResp->ucNumOfFixes   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* get the Time between fixes */
    pstFwdExtReqLocResp->ucTimeBetFixes = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* get the max response time */
    pstFwdExtReqLocResp->ucMaxRespTime  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* get the fix type request */
    pstFwdExtReqLocResp->ucFixTypeReq   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* get QOS request type */
    pstFwdExtReqLocResp->ucQosReqType   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);


    if (0 == pstFwdExtReqLocResp->ucQosReqType)
    {
        /* get prefered response time */
        pstFwdExtReqLocResp->ucPrefRespTime = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);
    }

    if (1 == pstFwdExtReqLocResp->ucQosReqType)
    {
        /* get horizontal location uncertainity */
        pstFwdExtReqLocResp->ucLocUncHC = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);
    }

    if (1 == pstFwdExtReqLocResp->ucQosReqType)
    {
        /* get horizontal location uncertainity confident level */
        pstFwdExtReqLocResp->ucLocUncHCnf = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);
    }

    /* get horizontal location uncertainity eliptical requested or not*/
    pstFwdExtReqLocResp->ucLocUncHCReq = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* get Height request field */
    pstFwdExtReqLocResp->ucHeightReq = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* get clock correction for GPS time requested  */
    pstFwdExtReqLocResp->ucClkCorGpsReq = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* get velocity requested field */
    pstFwdExtReqLocResp->ucVelocityReq = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* get velocity uncertainity eliptical requested */
    pstFwdExtReqLocResp->ucVelUncHCReq = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    PS_MEM_FREE(UEPS_PID_XPDS, pstFwdExtReqLocResp);

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_DecodeRequestExtMsInfo(
    VOS_UINT8                          *pucHeadBuf
)
{

    VOS_UINT32                               ulNumBitsProcessed;
    VOS_UINT32                               ulCurIdx;
    TAF_XPDS_FWDLINK_REQ_EXT_MS_INFO_STRU   *pstFwdExtMsInfo;

    ulNumBitsProcessed   = 2; /* 2 is the number of bits from req length field */
    ulCurIdx             = 0;

    pstFwdExtMsInfo  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_REQ_EXT_MS_INFO_STRU));
    if (VOS_NULL_PTR == pstFwdExtMsInfo)
    {
        return VOS_ERR;
    }

    /* update the response flag for Provide location response */
    TAF_XPDS_SetReqExtMsInfoFlag(VOS_TRUE);

    PS_MEM_SET(pstFwdExtMsInfo, 0x00, sizeof(TAF_XPDS_FWDLINK_REQ_EXT_MS_INFO_STRU));


    /* get MS cap request */
    pstFwdExtMsInfo->ucMsCapReq        = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* get GPS rx cap requested */
    pstFwdExtMsInfo->ucGpsRxCapReq     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* get band class cap requested */
    pstFwdExtMsInfo->ucBandClsCapReq   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* get pilot del sense request */
    pstFwdExtMsInfo->ucPilotDelSensReq = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* get MS status requested */
    pstFwdExtMsInfo->ucMsStatusReq     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    PS_MEM_FREE(UEPS_PID_XPDS, pstFwdExtMsInfo);

    return VOS_OK;
}



VOS_UINT32 TAF_XPDS_DecodeRequestGenLocMeas(
    VOS_UINT8                          *pucHeadBuf
)
{

    VOS_UINT32                               ulNumBitsProcessed;
    VOS_UINT32                               ulCurIdx;
    TAF_XPDS_FWDLINK_REQ_GEN_LOC_MEAS_STRU  *pstFwdReqGenLocMeas;
    VOS_UINT8                                ucLoop;

    ulNumBitsProcessed   = 2; /* 2 is the number of bits from req length field */
    ulCurIdx             = 0;

    pstFwdReqGenLocMeas  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_REQ_GEN_LOC_MEAS_STRU));
    if (VOS_NULL_PTR == pstFwdReqGenLocMeas)
    {
        return VOS_ERR;
    }

    /* update the response flag for Provide location response */
    TAF_XPDS_SetReqExtMsInfoFlag(VOS_TRUE);

    PS_MEM_SET(pstFwdReqGenLocMeas, 0x00, sizeof(TAF_XPDS_FWDLINK_REQ_GEN_LOC_MEAS_STRU));


    /* number of fixes */
    pstFwdReqGenLocMeas->ucNumOfFix        = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* time between fixes */
    pstFwdReqGenLocMeas->ucTimeBetFix      = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* maximum response time */
    pstFwdReqGenLocMeas->ucMaxRespTime     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* prefered response time */
    pstFwdReqGenLocMeas->ucPrefRespTime    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* pilot identification information */
    pstFwdReqGenLocMeas->ucPilotIdReq      = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* psuedorange measurement */
    pstFwdReqGenLocMeas->ucPrMeasReq       = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    if (1 == pstFwdReqGenLocMeas->ucPrMeasReq)
    {
        /* satellite code phase */
        pstFwdReqGenLocMeas->ucSvCodePhIntReq  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);
    }

    /* pilot phase measurement */
    pstFwdReqGenLocMeas->ucPPMeasReq       = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    if (1 == pstFwdReqGenLocMeas->ucPPMeasReq)
    {
        /* pilot phase pusedo doppler measurement */
        pstFwdReqGenLocMeas->ucPpMeasDopplReq  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);

        /* repeater measurement */
        pstFwdReqGenLocMeas->ucRptrMeasReq     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);

        /* frequency list included flag */
        pstFwdReqGenLocMeas->ucReqFreqListIncl = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);

        if (1 == pstFwdReqGenLocMeas->ucReqFreqListIncl)
        {
            /* number of frequencies */
            pstFwdReqGenLocMeas->ucNumOfReqFreq    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                                    &ulNumBitsProcessed,
                                                                                    &pucHeadBuf[ulCurIdx],
                                                                                    &ulCurIdx);

            for (ucLoop = 0; ucLoop < pstFwdReqGenLocMeas->ucNumOfReqFreq + 1; ucLoop++)
            {
                /* band class */
                pstFwdReqGenLocMeas->astFreqInfo[ucLoop].ucBandClass    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                                        &ulNumBitsProcessed,
                                                                                        &pucHeadBuf[ulCurIdx],
                                                                                        &ulCurIdx);

                /* frequency information */
                pstFwdReqGenLocMeas->astFreqInfo[ucLoop].usCdmaFreq     = (VOS_UINT16)TAF_XPDS_DecodeGetValue(11,
                                                                                        &ulNumBitsProcessed,
                                                                                        &pucHeadBuf[ulCurIdx],
                                                                                        &ulCurIdx);

                /* mode indicator */
                pstFwdReqGenLocMeas->astFreqInfo[ucLoop].ucModeInd      = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                                                        &ulNumBitsProcessed,
                                                                                        &pucHeadBuf[ulCurIdx],
                                                                                        &ulCurIdx);

                /* repeater measurement on this frequency */
                pstFwdReqGenLocMeas->astFreqInfo[ucLoop].ucRptrMeasFReq = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                        &ulNumBitsProcessed,
                                                                                        &pucHeadBuf[ulCurIdx],
                                                                                        &ulCurIdx);

                /* get reserved bits */
                (VOS_VOID)TAF_XPDS_DecodeGetValue(2,
                                                        &ulNumBitsProcessed,
                                                        &pucHeadBuf[ulCurIdx],
                                                        &ulCurIdx);
            }

        }
    }

    /* offset requested */
    pstFwdReqGenLocMeas->ucOffsetReq     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    if (1 == pstFwdReqGenLocMeas->ucOffsetReq)
    {
        /* shortened offset reporting period */
        pstFwdReqGenLocMeas->ucShrtOffEnable = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);

        /* number of requested time offset */
        pstFwdReqGenLocMeas->ucNumReqOffset  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(6,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);

        /* offset reference time increment */
        pstFwdReqGenLocMeas->ucOffRefTimeInc = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);

        if (0 == pstFwdReqGenLocMeas->ucNumOfFix)
        {
            /* use time */
            pstFwdReqGenLocMeas->ucUseTime       = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                    &ulNumBitsProcessed,
                                                                                    &pucHeadBuf[ulCurIdx],
                                                                                    &ulCurIdx);
        }


    }

    if (1 == pstFwdReqGenLocMeas->ucUseTime)
    {
         /* action time */
         pstFwdReqGenLocMeas->usActionTIme    = (VOS_UINT16)TAF_XPDS_DecodeGetValue(10,
                                                                                 &ulNumBitsProcessed,
                                                                                 &pucHeadBuf[ulCurIdx],
                                                                                 &ulCurIdx);
    }

    PS_MEM_FREE(UEPS_PID_XPDS, pstFwdReqGenLocMeas);

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_DecodeRequestExtCancellation(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                             ulNumBitsProcessed;
    VOS_UINT32                             ulCurIdx;
    TAF_XPDS_FWDLINK_REQ_EXT_CANCEL_STRU  *pstFwdReqCancel;

    ulNumBitsProcessed = 2;
    ulCurIdx           = 0;

    pstFwdReqCancel  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_REQ_EXT_CANCEL_STRU));
    if (VOS_NULL_PTR == pstFwdReqCancel)
    {
        return VOS_ERR;
    }

    PS_MEM_SET(pstFwdReqCancel, 0x00, sizeof(TAF_XPDS_FWDLINK_REQ_EXT_CANCEL_STRU));

    /* get the Cancellation type */
    pstFwdReqCancel->ucCancelType = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    PS_MEM_FREE(UEPS_PID_XPDS, pstFwdReqCancel);

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_DecodeRequestMsgDelayMeas(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                                 ulNumBitsProcessed;
    VOS_UINT32                                 ulCurIdx;
    TAF_XPDS_FWDLINK_REQ_MSG_DELAY_MEAS_STRU  *pstFwdReqMsgDel;

    ulNumBitsProcessed = 2;
    ulCurIdx           = 0;

    pstFwdReqMsgDel  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_REQ_MSG_DELAY_MEAS_STRU));
    if (VOS_NULL_PTR == pstFwdReqMsgDel)
    {
        return VOS_ERR;
    }

    /* update the request flag */
    TAF_XPDS_SetReqMsgDelayMeasReqFlag(PS_TRUE);

    PS_MEM_SET(pstFwdReqMsgDel, 0x00, sizeof(TAF_XPDS_FWDLINK_REQ_MSG_DELAY_MEAS_STRU));

    /* message sequence number */
    pstFwdReqMsgDel->ucMsgSeq      = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* recieve to transmit time delay information */
    pstFwdReqMsgDel->ucRxTxDelayReq = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    PS_MEM_FREE(UEPS_PID_XPDS, pstFwdReqMsgDel);

    return VOS_OK;
}



VOS_UINT32 TAF_XPDS_DecodeRequestServSysInfo(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                                 ulNumBitsProcessed;
    VOS_UINT32                                 ulCurIdx;
    TAF_XPDS_FWDLINK_REQ_SERV_SYS_INFO_STRU   *pstFwdReqSerSys;

    ulNumBitsProcessed = 2;
    ulCurIdx           = 0;

    pstFwdReqSerSys  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_REQ_SERV_SYS_INFO_STRU));
    if (VOS_NULL_PTR == pstFwdReqSerSys)
    {
        return VOS_ERR;
    }

    /* update the request flag */
    TAF_XPDS_SetReqServSysInfoReqFlag(PS_TRUE);

    PS_MEM_SET(pstFwdReqSerSys, 0x00, sizeof(TAF_XPDS_FWDLINK_REQ_SERV_SYS_INFO_STRU));

    /* pilot id requested */
    pstFwdReqSerSys->ucPilotIdSeq    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);
    if (1 == pstFwdReqSerSys->ucPilotIdSeq)
    {
        /* extended pilot id requested */
        pstFwdReqSerSys->ucExtPilotIdSeq = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);
    }

    /* active set information requested */
    pstFwdReqSerSys->ucActiveSetSeq  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* neighbour list information requested */
    pstFwdReqSerSys->ucNeighListReq  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* base location information requested */
    pstFwdReqSerSys->ucBaseLocSeq    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    PS_MEM_FREE(UEPS_PID_XPDS, pstFwdReqSerSys);

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_DecodeRequestCoarseLocResp(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                                 ulNumBitsProcessed;
    VOS_UINT32                                 ulCurIdx;
    TAF_XPDS_FWDLINK_REQ_COARSE_LOC_RESP_STRU *pstFwdReqCoLocResp;

    ulNumBitsProcessed = 2;
    ulCurIdx           = 0;

    pstFwdReqCoLocResp  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_REQ_COARSE_LOC_RESP_STRU));
    if (VOS_NULL_PTR == pstFwdReqCoLocResp)
    {
        return VOS_ERR;
    }


    /* update the request flag */
    TAF_XPDS_SetReqGpsCoarseLocReqFlag(PS_TRUE);

    PS_MEM_SET(pstFwdReqCoLocResp, 0x00, sizeof(TAF_XPDS_FWDLINK_REQ_COARSE_LOC_RESP_STRU));

    /* number of fixes */
    pstFwdReqCoLocResp->ucNumOfFixes   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* time between fixes */
    pstFwdReqCoLocResp->ucTimeBetFixes = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    /* maximum response time */
    pstFwdReqCoLocResp->ucMaxRespTime  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    PS_MEM_FREE(UEPS_PID_XPDS, pstFwdReqCoLocResp);

    return VOS_OK;
}



VOS_UINT32 TAF_XPDS_DecodeProvGpsRealTimeIntInfo(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                                         ulNumBitsProcessed;
    VOS_UINT32                                         ulCurIdx;
    TAF_XPDS_FWDLINK_RSP_GPS_REALTIME_INTE_STRU       *pstFwdRspGpsInfo;
    VOS_UINT8                                          ucLoop;

    ulNumBitsProcessed = 3;
    ulCurIdx           = 0;

    pstFwdRspGpsInfo  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_RSP_GPS_REALTIME_INTE_STRU));
    if (VOS_NULL_PTR == pstFwdRspGpsInfo)
    {
        return VOS_ERR;
    }

    PS_MEM_SET(pstFwdRspGpsInfo, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_GPS_REALTIME_INTE_STRU));

    /* integrity type */
    pstFwdRspGpsInfo->ucIntegrityType = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);
    if (1 == pstFwdRspGpsInfo->ucIntegrityType)
    {
        /* faulty GPS satellite present */
        pstFwdRspGpsInfo->ucFaultySvPres = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);
        if (1 == pstFwdRspGpsInfo->ucFaultySvPres)
        {
            /* faulty GPS satellite present */
            pstFwdRspGpsInfo->ucNumOfFaultSv  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                                    &ulNumBitsProcessed,
                                                                                    &pucHeadBuf[ulCurIdx],
                                                                                    &ulCurIdx);

            for (ucLoop = 0; ucLoop < pstFwdRspGpsInfo->ucNumOfFaultSv; ucLoop++)
            {
                /* faulty satellites PRN number */
                pstFwdRspGpsInfo->aucFaultSvPrn[ucLoop] = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                                        &ulNumBitsProcessed,
                                                                                        &pucHeadBuf[ulCurIdx],
                                                                                        &ulCurIdx);

                /* TODO: reserve bits */
                (VOS_VOID)TAF_XPDS_DecodeGetValue(0,
                                                        &ulNumBitsProcessed,
                                                        &pucHeadBuf[ulCurIdx],
                                                        &ulCurIdx);
            }
        }
    }

    if (0 == pstFwdRspGpsInfo->ucIntegrityType)
    {

        /* NSAT */
        pstFwdRspGpsInfo->ucNSAT = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);

        /* adjusted state of satellites */
        pstFwdRspGpsInfo->ucASTAT = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

        for (ucLoop = 0; ucLoop < pstFwdRspGpsInfo->ucNSAT; ucLoop++)
        {

            /* satellite ID */
            pstFwdRspGpsInfo->astSatInfo[ucLoop].ucSatId = (VOS_UINT8)TAF_XPDS_DecodeGetValue(6,
                                                                                    &ulNumBitsProcessed,
                                                                                    &pucHeadBuf[ulCurIdx],
                                                                                    &ulCurIdx);

            /* adjusted psuedorange correction */
            pstFwdRspGpsInfo->astSatInfo[ucLoop].ucAPrc = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                                                    &ulNumBitsProcessed,
                                                                                    &pucHeadBuf[ulCurIdx],
                                                                                    &ulCurIdx);
        }
    }

    PS_MEM_FREE(UEPS_PID_XPDS, pstFwdRspGpsInfo);

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_DecodeProvDgpsAssis(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                                 ulNumBitsProcessed;
    VOS_UINT32                                 ulCurIdx;
    TAF_XPDS_FWDLINK_RSP_DGPS_ASSIS_STRU      *pstFwdRspDgpsAssi;
    VOS_UINT8                                  ucLoop;

    ulNumBitsProcessed = 3;
    ulCurIdx           = 0;

    pstFwdRspDgpsAssi  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_RSP_DGPS_ASSIS_STRU));
    if (VOS_NULL_PTR == pstFwdRspDgpsAssi)
    {
        return VOS_ERR;
    }

    PS_MEM_SET(pstFwdRspDgpsAssi, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_DGPS_ASSIS_STRU));

    /* time of week */
    pstFwdRspDgpsAssi->ulGpsTow       = (VOS_UINT16)TAF_XPDS_DecodeGetValue(20,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);
    /* status/health */
    pstFwdRspDgpsAssi->ucStatHealth  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);
    /* number of GPS satellite present */
    pstFwdRspDgpsAssi->ucNumOfStat = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    for (ucLoop = 0; ucLoop < pstFwdRspDgpsAssi->ucNumOfStat + 1; ucLoop++)
    {
        /* satellite id code */
        pstFwdRspDgpsAssi->astSatInfo[ucLoop].ucSatId = (VOS_UINT8)TAF_XPDS_DecodeGetValue(6,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);

        /* issue of data */
        pstFwdRspDgpsAssi->astSatInfo[ucLoop].ucIode = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);

        /* user differential range error */
        pstFwdRspDgpsAssi->astSatInfo[ucLoop].ucUDRE = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);

        /* psuedorange correction */
        pstFwdRspDgpsAssi->astSatInfo[ucLoop].usPRC  = (VOS_UINT16)TAF_XPDS_DecodeGetValue(12,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);
        /* psuedorange rate correction */
        pstFwdRspDgpsAssi->astSatInfo[ucLoop].ucRRC  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);
    }

    PS_MEM_FREE(UEPS_PID_XPDS, pstFwdRspDgpsAssi);

    return VOS_OK;
}



VOS_UINT32 TAF_XPDS_DecodeProvGpsCoarAquiAssis(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                                         ulNumBitsProcessed;
    VOS_UINT32                                         ulCurIdx;
    TAF_XPDS_FWDLINK_RSP_GPS_COARAQUI_STRU            *pstFwdRspGpsAssi;

    ulNumBitsProcessed = 3;
    ulCurIdx           = 0;

    pstFwdRspGpsAssi  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_RSP_GPS_COARAQUI_STRU));
    if (VOS_NULL_PTR == pstFwdRspGpsAssi)
    {
        return VOS_ERR;
    }

    PS_MEM_SET(pstFwdRspGpsAssi, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_GPS_COARAQUI_STRU));

    /* visible satellite list */
    pstFwdRspGpsAssi->ulSatVisList = (VOS_UINT32)TAF_XPDS_DecodeGetValue(32,
                                                                        &ulNumBitsProcessed,
                                                                        &pucHeadBuf[ulCurIdx],
                                                                        &ulCurIdx);
    PS_MEM_FREE(UEPS_PID_XPDS, pstFwdRspGpsAssi);

    return VOS_OK;
}



VOS_UINT32 TAF_XPDS_DecodeProvGpsCoarLocAssis(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                               ulNumBitsProcessed;
    VOS_UINT32                               ulCurIdx;
    TAF_XPDS_FWDLINK_RSP_GPS_COARLOC_STRU   *pstFwdRspGpsAssi;

    ulNumBitsProcessed = 3;
    ulCurIdx           = 0;

    pstFwdRspGpsAssi  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_RSP_GPS_COARLOC_STRU));
    if (VOS_NULL_PTR == pstFwdRspGpsAssi)
    {
        return VOS_ERR;
    }

    PS_MEM_SET(pstFwdRspGpsAssi, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_GPS_COARLOC_STRU));

    /* lattitude */
    pstFwdRspGpsAssi->usRefLat  = (VOS_UINT16)TAF_XPDS_DecodeGetValue(15,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);
    /* longitude */
    pstFwdRspGpsAssi->usRefLong = (VOS_UINT16)TAF_XPDS_DecodeGetValue(16,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    PS_MEM_FREE(UEPS_PID_XPDS, pstFwdRspGpsAssi);

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_DecodeProvExtGpsHealthInfo(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                                         ulNumBitsProcessed;
    VOS_UINT32                                         ulCurIdx;
    TAF_XPDS_FWDLINK_RSP_EXTGPS_HEALTH_STRU           *pstFwdRspGpsHlth;
    VOS_UINT8                                          ucLoop;

    ulNumBitsProcessed = 3;
    ulCurIdx           = 0;

    pstFwdRspGpsHlth  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_RSP_EXTGPS_HEALTH_STRU));
    if (VOS_NULL_PTR == pstFwdRspGpsHlth)
    {
        return VOS_ERR;
    }

    PS_MEM_SET(pstFwdRspGpsHlth, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_EXTGPS_HEALTH_STRU));

    /* bad satellite present */
    pstFwdRspGpsHlth->ucBadSvPres  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                            &ulNumBitsProcessed,
                                                                            &pucHeadBuf[ulCurIdx],
                                                                            &ulCurIdx);

    if (1 == pstFwdRspGpsHlth->ucBadSvPres)
    {
        /* number of bad satellites */
        pstFwdRspGpsHlth->ucNumOfBadSv = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                                &ulNumBitsProcessed,
                                                                                &pucHeadBuf[ulCurIdx],
                                                                                &ulCurIdx);

        for (ucLoop = 0; ucLoop < pstFwdRspGpsHlth->ucNumOfBadSv + 1; ucLoop++)
        {
            /* bad sv PRN number */
            pstFwdRspGpsHlth->aucSatPrnNum[ucLoop]= (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                                    &ulNumBitsProcessed,
                                                                                    &pucHeadBuf[ulCurIdx],
                                                                                    &ulCurIdx);
        }
    }

    PS_MEM_FREE(UEPS_PID_XPDS, pstFwdRspGpsHlth);

    return VOS_OK;
}



VOS_UINT32 TAF_XPDS_DecodeProvExtGpsAlmCorr(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                                 ulTotNumOfBits;
    VOS_UINT32                                 ulCurrIdx;
    TAF_XPDS_FWDLINK_RSP_EXTGPS_ALMCORR_STRU  *pstFwdRspGpsCorr;
    VOS_UINT8                                  ucLoop;
    VOS_UINT8                                  ucNumOfSvP;
    VOS_UINT8                                  ucPartNum;
    VOS_UINT8                                  ucTotalParts;
    VOS_UINT8                                  ucPrevNumSv;

    ulTotNumOfBits     = 3;
    ulCurrIdx          = 0;

    pstFwdRspGpsCorr  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_RSP_EXTGPS_ALMCORR_STRU));
    if (VOS_NULL_PTR == pstFwdRspGpsCorr)
    {
        return VOS_ERR;
    }

    ucPartNum    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    ucTotalParts = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    /* if part number is 0, it is the new message so refresh the context data */
    if (0 == ucPartNum)
    {
        PS_MEM_SET(pstFwdRspGpsCorr, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_EXTGPS_ALMCORR_STRU));
    }

    pstFwdRspGpsCorr->usTimeRef  = (VOS_UINT16)TAF_XPDS_DecodeGetValue(12,
                                                                     &ulTotNumOfBits,
                                                                     &pucHeadBuf[ulCurrIdx],
                                                                     &ulCurrIdx);

    pstFwdRspGpsCorr->ucWeekNum  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                     &ulTotNumOfBits,
                                                                     &pucHeadBuf[ulCurrIdx],
                                                                     &ulCurrIdx);

    pstFwdRspGpsCorr->ucTOA      = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                     &ulTotNumOfBits,
                                                                     &pucHeadBuf[ulCurrIdx],
                                                                     &ulCurrIdx);

    ucNumOfSvP                   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    ucPrevNumSv                     = pstFwdRspGpsCorr->ucNumOfSvP;
    pstFwdRspGpsCorr->ucNumOfSvP   += (ucNumOfSvP + 1); // +1 is according to the specification */
    pstFwdRspGpsCorr->ucPartNum     = ucPartNum;
    pstFwdRspGpsCorr->ucTotalParts  = ucTotalParts;

    for (ucLoop = ucPrevNumSv; ucLoop < pstFwdRspGpsCorr->ucNumOfSvP; ucLoop++)
    {
        pstFwdRspGpsCorr->astSatInfo[ucLoop].ucSvPrnNum     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                                              &ulTotNumOfBits,
                                                                                              &pucHeadBuf[ulCurrIdx],
                                                                                              &ulCurrIdx);

        pstFwdRspGpsCorr->astSatInfo[ucLoop].ucDeltaXYZIncl = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                              &ulTotNumOfBits,
                                                                                              &pucHeadBuf[ulCurrIdx],
                                                                                              &ulCurrIdx);

        if (1 == pstFwdRspGpsCorr->astSatInfo[ucLoop].ucDeltaXYZIncl)
        {
            pstFwdRspGpsCorr->astSatInfo[ucLoop].usDeltaX   = (VOS_UINT16)TAF_XPDS_DecodeGetValue(15,
                                                                                                   &ulTotNumOfBits,
                                                                                                   &pucHeadBuf[ulCurrIdx],
                                                                                                   &ulCurrIdx);

            pstFwdRspGpsCorr->astSatInfo[ucLoop].usDeltaY   = (VOS_UINT16)TAF_XPDS_DecodeGetValue(15,
                                                                                                   &ulTotNumOfBits,
                                                                                                   &pucHeadBuf[ulCurrIdx],
                                                                                                   &ulCurrIdx);

            pstFwdRspGpsCorr->astSatInfo[ucLoop].usDeltaZ   = (VOS_UINT16)TAF_XPDS_DecodeGetValue(15,
                                                                                                   &ulTotNumOfBits,
                                                                                                   &pucHeadBuf[ulCurrIdx],
                                                                                                   &ulCurrIdx);

            pstFwdRspGpsCorr->astSatInfo[ucLoop].usDeltaX_1 = (VOS_UINT16)TAF_XPDS_DecodeGetValue(11,
                                                                                                   &ulTotNumOfBits,
                                                                                                   &pucHeadBuf[ulCurrIdx],
                                                                                                   &ulCurrIdx);

            pstFwdRspGpsCorr->astSatInfo[ucLoop].usDeltaY_1 = (VOS_UINT16)TAF_XPDS_DecodeGetValue(11,
                                                                                                   &ulTotNumOfBits,
                                                                                                   &pucHeadBuf[ulCurrIdx],
                                                                                                   &ulCurrIdx);

            pstFwdRspGpsCorr->astSatInfo[ucLoop].usDeltaZ_1 = (VOS_UINT16)TAF_XPDS_DecodeGetValue(11,
                                                                                                   &ulTotNumOfBits,
                                                                                                   &pucHeadBuf[ulCurrIdx],
                                                                                                   &ulCurrIdx);

            pstFwdRspGpsCorr->astSatInfo[ucLoop].ucDeltaX_2 = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                                                   &ulTotNumOfBits,
                                                                                                   &pucHeadBuf[ulCurrIdx],
                                                                                                   &ulCurrIdx);

            pstFwdRspGpsCorr->astSatInfo[ucLoop].ucDeltaY_2 = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                                                   &ulTotNumOfBits,
                                                                                                   &pucHeadBuf[ulCurrIdx],
                                                                                                   &ulCurrIdx);

            pstFwdRspGpsCorr->astSatInfo[ucLoop].ucDeltaZ_2 = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                                                   &ulTotNumOfBits,
                                                                                                   &pucHeadBuf[ulCurrIdx],
                                                                                                   &ulCurrIdx);
        }

        pstFwdRspGpsCorr->astSatInfo[ucLoop].ucDeltaClkIncl = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                                               &ulTotNumOfBits,
                                                                                               &pucHeadBuf[ulCurrIdx],
                                                                                               &ulCurrIdx);

        if (1 == pstFwdRspGpsCorr->astSatInfo[ucLoop].ucDeltaClkIncl)
        {
            pstFwdRspGpsCorr->astSatInfo[ucLoop].ulDeltaClk   = (VOS_UINT32)TAF_XPDS_DecodeGetValue(17,
                                                                                                   &ulTotNumOfBits,
                                                                                                   &pucHeadBuf[ulCurrIdx],
                                                                                                   &ulCurrIdx);

            pstFwdRspGpsCorr->astSatInfo[ucLoop].usDeltaClk_1 = (VOS_UINT16)TAF_XPDS_DecodeGetValue(12,
                                                                                                   &ulTotNumOfBits,
                                                                                                   &pucHeadBuf[ulCurrIdx],
                                                                                                   &ulCurrIdx);

            pstFwdRspGpsCorr->astSatInfo[ucLoop].usDeltaClk_2 = (VOS_UINT16)TAF_XPDS_DecodeGetValue(9,
                                                                                                   &ulTotNumOfBits,
                                                                                                   &pucHeadBuf[ulCurrIdx],
                                                                                                   &ulCurrIdx);
        }
    }

    PS_MEM_FREE(UEPS_PID_XPDS, pstFwdRspGpsCorr);

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_DecodeProvExtGpsNavBits(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                                   ulTotNumOfBits;
    VOS_UINT32                                   ulCurrIdx;
    TAF_XPDS_FWDLINK_RSP_EXTGPS_NAVBITS_STRU    *pstFwdRspGpsBits;
    VOS_UINT8                                    ucLoop;
    VOS_UINT8                                    ucInLoop;
    VOS_UINT8                                    ucNumOfSvP;
    VOS_UINT8                                    ucPartNum;
    VOS_UINT8                                    ucTotalParts;
    VOS_UINT8                                    ucPrevNumSv;

    ulTotNumOfBits     = 3;
    ulCurrIdx          = 0;

    pstFwdRspGpsBits  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_RSP_EXTGPS_NAVBITS_STRU));
    if (VOS_NULL_PTR == pstFwdRspGpsBits)
    {
        return VOS_ERR;
    }

    ucPartNum       = (VOS_UINT8)TAF_XPDS_DecodeGetValue(6,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    ucTotalParts    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(6,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    ucNumOfSvP      = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    /* if part number is 0, it is the new message so refresh the context data */
    if (0 == ucPartNum)
    {
        PS_MEM_SET(pstFwdRspGpsBits, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_EXTGPS_NAVBITS_STRU));
    }

    pstFwdRspGpsBits->ucPartNum    = ucPartNum;
    pstFwdRspGpsBits->ucTotalParts = ucTotalParts;
    ucPrevNumSv                    = pstFwdRspGpsBits->ucNumOfSvP;
    pstFwdRspGpsBits->ucNumOfSvP  += ucNumOfSvP;

    for (ucLoop = ucPrevNumSv; ucLoop < pstFwdRspGpsBits->ucNumOfSvP; ucLoop++)
    {
        pstFwdRspGpsBits->astSatInfo[ucLoop].ucSvPrnNum     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                                              &ulTotNumOfBits,
                                                                                              &pucHeadBuf[ulCurrIdx],
                                                                                              &ulCurrIdx);

        /* to get subframe_1_2_3 , decode 112 bytes + 4 bits. total 900 bits */
        for (ucInLoop = 0; ucInLoop < 112; ucInLoop++)
        {
            pstFwdRspGpsBits->astSatInfo[ucLoop].aucSubF123[ucInLoop] = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                                              &ulTotNumOfBits,
                                                                                              &pucHeadBuf[ulCurrIdx],
                                                                                              &ulCurrIdx);

        }

        /* decode 4 bits left from above loop */
        pstFwdRspGpsBits->astSatInfo[ucLoop].aucSubF123[ucInLoop] = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                                      &ulTotNumOfBits,
                                                                                      &pucHeadBuf[ulCurrIdx],
                                                                                      &ulCurrIdx);

    }

    ucNumOfSvP   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                           &ulTotNumOfBits,
                                                           &pucHeadBuf[ulCurrIdx],
                                                           &ulCurrIdx);

    ucPrevNumSv                    = pstFwdRspGpsBits->ucNumOfFrP;
    pstFwdRspGpsBits->ucNumOfFrP  += ucNumOfSvP;

    for (ucLoop = ucPrevNumSv; ucLoop < pstFwdRspGpsBits->ucNumOfFrP; ucLoop++)
    {
        pstFwdRspGpsBits->astFrameInfo[ucLoop].ucFrameNum = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                                              &ulTotNumOfBits,
                                                                                              &pucHeadBuf[ulCurrIdx],
                                                                                              &ulCurrIdx);

        /* to get subframe_1_2_3 , decode 75 bytes . total 600 bits */
        for (ucInLoop = 0; ucInLoop < 75; ucInLoop++)
        {
            pstFwdRspGpsBits->astFrameInfo[ucLoop].aucSubF45[ucInLoop] = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                                              &ulTotNumOfBits,
                                                                                              &pucHeadBuf[ulCurrIdx],
                                                                                              &ulCurrIdx);
        }

    }

    PS_MEM_FREE(UEPS_PID_XPDS, pstFwdRspGpsBits);

    return VOS_OK;
}



VOS_UINT32 TAF_XPDS_DecodeProvExtGpsSensiAssis(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                                    ulTotNumOfBits;
    VOS_UINT32                                    ulCurrIdx;
    TAF_XPDS_FWDLINK_RSP_EXTGPS_SENASSI_STRU     *pstFwdRspGpsAssi;
    VOS_UINT8                                     ucLoop;
    VOS_UINT8                                     ucInLoop;
    VOS_UINT8                                     ucNumOfSvP;
    VOS_UINT8                                     ucPartNum;
    VOS_UINT8                                     ucTotalParts;
    VOS_UINT8                                     ucPrevNumSv;

    ulTotNumOfBits     = 3;
    ulCurrIdx          = 0;

    pstFwdRspGpsAssi  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_RSP_EXTGPS_SENASSI_STRU));
    if (VOS_NULL_PTR == pstFwdRspGpsAssi)
    {
        return VOS_ERR;
    }

    ucPartNum          = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    ucTotalParts       = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    /* if part number is 0, it is the new message so refresh the context data */
    if (0 == ucPartNum)
    {
        PS_MEM_SET(pstFwdRspGpsAssi, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_EXTGPS_SENASSI_STRU));
    }


    pstFwdRspGpsAssi->ucNavMsgFormIncl = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    pstFwdRspGpsAssi->usRefBitNum      = (VOS_UINT16)TAF_XPDS_DecodeGetValue(11,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    pstFwdRspGpsAssi->ucNavBitLen      = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    ucNumOfSvP                         = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    pstFwdRspGpsAssi->ucPartNum    = ucPartNum;
    pstFwdRspGpsAssi->ucTotalParts = ucTotalParts;
    ucPrevNumSv                    = pstFwdRspGpsAssi->ucNumOfDrP;
    pstFwdRspGpsAssi->ucNumOfDrP  += (ucNumOfSvP + 1); // +1 asper protocol

    for (ucLoop = ucPrevNumSv; ucLoop < pstFwdRspGpsAssi->ucNumOfDrP; ucLoop++)
    {
        if (1 == pstFwdRspGpsAssi->ucNavMsgFormIncl)
        {
            pstFwdRspGpsAssi->astDataRec[ucLoop].ucNavMsgForm = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                                                  &ulTotNumOfBits,
                                                                                                  &pucHeadBuf[ulCurrIdx],
                                                                                                  &ulCurrIdx);

            if (pstFwdRspGpsAssi->astDataRec[ucLoop].ucNavMsgForm != 1)
            {
                /* get navigation bits  */
                for (ucInLoop = 0; ucInLoop < ((4 * pstFwdRspGpsAssi->ucNavBitLen) / 8); ucInLoop++)
                {
                    pstFwdRspGpsAssi->astDataRec[ucLoop].aucNavMsgBits[ucInLoop] = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                                                      &ulTotNumOfBits,
                                                                                                      &pucHeadBuf[ulCurrIdx],
                                                                                                      &ulCurrIdx);

                }

                pstFwdRspGpsAssi->astDataRec[ucLoop].aucNavMsgBits[ucInLoop] = (VOS_UINT8)TAF_XPDS_DecodeGetValue(((4 * pstFwdRspGpsAssi->ucNavBitLen) % 8),
                                                                                                  &ulTotNumOfBits,
                                                                                                  &pucHeadBuf[ulCurrIdx],
                                                                                                  &ulCurrIdx);
            }
        }

        /* decode 4 bits left from above loop */
        pstFwdRspGpsAssi->astDataRec[ucLoop].ucNumOfSvDr = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                                      &ulTotNumOfBits,
                                                                                      &pucHeadBuf[ulCurrIdx],
                                                                                      &ulCurrIdx);

        for (ucInLoop = 0; ucInLoop < pstFwdRspGpsAssi->astDataRec[ucLoop].ucNumOfSvDr; ucInLoop++)
        {
            pstFwdRspGpsAssi->astDataRec[ucLoop].aucPRNNum[ucInLoop] = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                                              &ulTotNumOfBits,
                                                                                              &pucHeadBuf[ulCurrIdx],
                                                                                              &ulCurrIdx);
        }

    }

    PS_MEM_FREE(UEPS_PID_XPDS, pstFwdRspGpsAssi);

    return VOS_OK;
}


VOS_VOID TAF_XPDS_DecodeGenAquiAssisGlobInfo(
    VOS_UINT8                             *pucHeadBuf,
    VOS_UINT32                            *pulTotNumOfBits,
    VOS_UINT32                            *pulCurrIdx,
    TAF_XPDS_BS_GLOBAL_INFO_REC_STRU      *pstGlobInfo
)
{
    pstGlobInfo->ucGlobInfRecLen = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

    pstGlobInfo->ulTimeRef       = (VOS_UINT32)TAF_XPDS_DecodeGetValue(24,
                                                         pulTotNumOfBits,
                                                         &pucHeadBuf[*pulCurrIdx],
                                                         pulCurrIdx);

    pstGlobInfo->ucLocRefIncl    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

    if (1 == pstGlobInfo->ucLocRefIncl)
    {
        pstGlobInfo->ulLatRef  = (VOS_UINT32)TAF_XPDS_DecodeGetValue(23,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

        pstGlobInfo->ulLongRef = (VOS_UINT32)TAF_XPDS_DecodeGetValue(24,
                                                                 pulTotNumOfBits,
                                                                 &pucHeadBuf[*pulCurrIdx],
                                                                 pulCurrIdx);
    }

    pstGlobInfo->ucLocUncAng = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                         pulTotNumOfBits,
                                                         &pucHeadBuf[*pulCurrIdx],
                                                         pulCurrIdx);

    pstGlobInfo->ucLocUncA   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

    if (pstGlobInfo->ucLocUncAng != 0x0F)
    {
        pstGlobInfo->ucLocUncP = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);
    }

    pstGlobInfo->ucUncVIncl = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

    if (1 == pstGlobInfo->ucUncVIncl)
    {
        pstGlobInfo->ucLocUncV = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);
    }

    pstGlobInfo->ucClockIncl = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

    if (1 == pstGlobInfo->ucClockIncl)
    {
        pstGlobInfo->ucMsgSeq = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

        pstGlobInfo->usClkBias = (VOS_UINT16)TAF_XPDS_DecodeGetValue(9,
                                                                 pulTotNumOfBits,
                                                                 &pucHeadBuf[*pulCurrIdx],
                                                                 pulCurrIdx);

        pstGlobInfo->ucClkBiasUnc = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);
    }

    pstGlobInfo->ucClkDrftIncl = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

    if (1 == pstGlobInfo->ucClkDrftIncl)
    {
        pstGlobInfo->ucClkDrift    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

        pstGlobInfo->ucClkDriftUnc = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                 pulTotNumOfBits,
                                                                 &pucHeadBuf[*pulCurrIdx],
                                                                 pulCurrIdx);
    }

    /* update reserve bits */
    if (((*pulTotNumOfBits) % 8) > 0)
    {
        *pulCurrIdx      = (*pulCurrIdx) + 1;
        *pulTotNumOfBits = *pulTotNumOfBits  + (8 - ((*pulTotNumOfBits) % 8));
    }
}



VOS_VOID TAF_XPDS_DecodeGenAquiAssisSatRec(
    VOS_UINT8                                     *pucHeadBuf,
    VOS_UINT32                                    *pulTotNumOfBits,
    VOS_UINT32                                    *pulCurrIdx,
    TAF_XPDS_FWDLINK_RSP_GEN_AQUI_ASSI_STRU       *pstFwdRspAquAssi
)
{

    VOS_UINT8                              ucNumOfSvP;
    VOS_UINT8                              ucPrevNumSv;
    VOS_UINT8                              ucLoop;
    TAF_XPDS_GEN_AQUI_ASSI_SAT_REC_STRU   *pstSatRec;

    ucNumOfSvP      = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                            pulTotNumOfBits,
                                                            &pucHeadBuf[*pulCurrIdx],
                                                            pulCurrIdx);

    ucPrevNumSv                    = pstFwdRspAquAssi->ucNumOfSvP;
    pstFwdRspAquAssi->ucNumOfSvP  += ucNumOfSvP;

    for (ucLoop = ucPrevNumSv; ucLoop < pstFwdRspAquAssi->ucNumOfSvP; ucLoop++)
    {
        pstSatRec = &(pstFwdRspAquAssi->astSatRec[ucLoop]);

        pstSatRec->ucPRNNum = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                 pulTotNumOfBits,
                                                                 &pucHeadBuf[*pulCurrIdx],
                                                                 pulCurrIdx);

        pstSatRec->usSvCodePh = (VOS_UINT16)TAF_XPDS_DecodeGetValue(10,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

        pstSatRec->ucSvCodePhInt = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                 pulTotNumOfBits,
                                                                 &pucHeadBuf[*pulCurrIdx],
                                                                 pulCurrIdx);

        pstSatRec->ucGpsBitNum = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

        if (1 == pstFwdRspAquAssi->ucCodePhWinIncl)
        {
            pstSatRec->ucSvCodePhWin = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                     pulTotNumOfBits,
                                                                     &pucHeadBuf[*pulCurrIdx],
                                                                     pulCurrIdx);
        }

        pstSatRec->usDoppler0 = (VOS_UINT16)TAF_XPDS_DecodeGetValue(12,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

        pstSatRec->usDoppler1 = (VOS_UINT16)TAF_XPDS_DecodeGetValue(11,
                                                                 pulTotNumOfBits,
                                                                 &pucHeadBuf[*pulCurrIdx],
                                                                 pulCurrIdx);

        if (1 == pstFwdRspAquAssi->ucDopp2Incl)
        {
            pstSatRec->usDoppler2 = (VOS_UINT16)TAF_XPDS_DecodeGetValue(9,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);
        }

        if (1 == pstFwdRspAquAssi->ucDoppWinIncl)
        {
            pstSatRec->ucDopplerWin = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                 pulTotNumOfBits,
                                                                 &pucHeadBuf[*pulCurrIdx],
                                                                 pulCurrIdx);
        }

        if (1 == pstFwdRspAquAssi->ucSvOpModeIncl)
        {
            pstSatRec->ucSvOpModeLen = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

            pstSatRec->ucGpsFreq = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                     pulTotNumOfBits,
                                                                     &pucHeadBuf[*pulCurrIdx],
                                                                     pulCurrIdx);

           if ((pstSatRec->ucGpsFreq & 0x02) > 0)
           {
               pstSatRec->ucL2cMode = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                                        pulTotNumOfBits,
                                                                        &pucHeadBuf[*pulCurrIdx],
                                                                        pulCurrIdx);

               /* get reserved  bits */
               (VOS_VOID)TAF_XPDS_DecodeGetValue(2,
                                                   pulTotNumOfBits,
                                                   &pucHeadBuf[*pulCurrIdx],
                                                   pulCurrIdx);

           }
        }


        if (1 == pstFwdRspAquAssi->ucAzElIncl)
        {
            pstSatRec->ucAzimuthSv = (VOS_UINT8)TAF_XPDS_DecodeGetValue(6,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

            pstSatRec->ucElevationSv = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                 pulTotNumOfBits,
                                                                 &pucHeadBuf[*pulCurrIdx],
                                                                 pulCurrIdx);
        }

        if (1 == pstFwdRspAquAssi->ucSvHealthIncl)
        {
            pstSatRec->ucSvHealthInd = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                 pulTotNumOfBits,
                                                                 &pucHeadBuf[*pulCurrIdx],
                                                                 pulCurrIdx);
        }
    }
}


VOS_VOID TAF_XPDS_DecodeGenAquiAssisPilotRecTypeSpc(
    VOS_UINT8                                     *pucHeadBuf,
    VOS_UINT32                                    *pulTotNumOfBits,
    VOS_UINT32                                    *pulCurrIdx,
    TAF_XPDS_GEN_AQUI_ASSI_FREQ_REC_STRU          *pstFreqRec,
    TAF_XPDS_GEN_AQUI_ASSI_PIL_REC_STRU           *pstPilotRec,
    VOS_UINT32                                    *pulPilRecBits
)
{
    TAF_XPDS_GAA_PIL_TX_TYPE_00_SPEC_STRU         *pstPilPxTyp00;   /**< if PIL_PX_TYPE is 00 **/
    TAF_XPDS_GAA_PIL_TX_TYPE_01_SPEC_STRU         *pstPilPxTyp01;   /**< if PIL_PX_TYPE is 01 **/
    VOS_UINT8                                      ucRptrIdLen;
    VOS_UINT8                                      ucLoop;

    switch (pstPilotRec->ucPilTxType)
    {
        case 0:
            pstPilPxTyp00 = &(pstPilotRec->stPilTxTypSpc.stPilPxTyp00);
            pstPilPxTyp00->usPilotPn = (VOS_UINT16)TAF_XPDS_DecodeGetValue(9,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

            *pulPilRecBits += 9;

             if (1 == pstFreqRec->ucRptrInfIncl)
             {
                 pstPilPxTyp00->ucUnsolRptrs = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                  pulTotNumOfBits,
                                                                  &pucHeadBuf[*pulCurrIdx],
                                                                  pulCurrIdx);
                 *pulPilRecBits += 4;
             }

                /* reserved bits */
             (VOS_VOID)TAF_XPDS_DecodeGetValue(2,
                                              pulTotNumOfBits,
                                              &pucHeadBuf[*pulCurrIdx],
                                              pulCurrIdx);

             *pulPilRecBits += 2;

            break;

        case 1:
            pstPilPxTyp01 = &(pstPilotRec->stPilTxTypSpc.stPilPxTyp01);
            pstPilPxTyp01->ucRptrType = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

            *pulPilRecBits += 3;

            if (1 == pstPilPxTyp01->ucRptrType)
            {
                pstPilPxTyp01->ucRptrIdIncl = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                 pulTotNumOfBits,
                                                                 &pucHeadBuf[*pulCurrIdx],
                                                                 pulCurrIdx);

                *pulPilRecBits += 1;
                if (1 == pstPilPxTyp01->ucRptrIdIncl)
                {
                    ucRptrIdLen = pstFreqRec->ucRptrIdLen + 1;

                    for (ucLoop = 0; ucLoop < (ucRptrIdLen / 8); ucLoop++)
                    {
                        pstPilPxTyp01->aucRptrId[ucLoop] = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8,
                                                                         pulTotNumOfBits,
                                                                         &pucHeadBuf[*pulCurrIdx],
                                                                         pulCurrIdx);

                        *pulPilRecBits += 8;
                    }

                    pstPilPxTyp01->aucRptrId[ucLoop] = (VOS_UINT8)TAF_XPDS_DecodeGetValue((ucRptrIdLen % 8),
                                                                     pulTotNumOfBits,
                                                                     &pucHeadBuf[*pulCurrIdx],
                                                                     pulCurrIdx);

                    *pulPilRecBits += (ucRptrIdLen % 8);
                }
            }

             /* reserved bits */
            (VOS_VOID)TAF_XPDS_DecodeGetValue(2,
                                             pulTotNumOfBits,
                                             &pucHeadBuf[*pulCurrIdx],
                                             pulCurrIdx);

            *pulPilRecBits += 2;
            break;

        default:
            break;
    }
}

VOS_VOID TAF_XPDS_DecodeGenAquiAssisPilotRec(
    VOS_UINT8                             *pucHeadBuf,
    VOS_UINT32                            *pulTotNumOfBits,
    VOS_UINT32                            *pulCurrIdx,
    TAF_XPDS_GEN_AQUI_ASSI_FREQ_REC_STRU  *pstFreqRec
)
{
    VOS_UINT8                              ucLoop;
    TAF_XPDS_GEN_AQUI_ASSI_PIL_REC_STRU   *pstPilotRec;
    VOS_UINT32                             ulPilRecBits;

    ulPilRecBits = 0;
    for (ucLoop = 0; ucLoop < pstFreqRec->ucNumOfPilTxF; ucLoop++)
    {
        pstPilotRec = &(pstFreqRec->astPilotRec[ucLoop]);

        pstPilotRec->ucPilRecLen = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                                 pulTotNumOfBits,
                                                                 &pucHeadBuf[*pulCurrIdx],
                                                                 pulCurrIdx);

        pstPilotRec->ucPilTxType = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);
        ulPilRecBits += 4 + 2;

        TAF_XPDS_DecodeGenAquiAssisPilotRecTypeSpc(pucHeadBuf, pulTotNumOfBits,
                                                        pulCurrIdx, pstFreqRec,
                                                        pstPilotRec, &ulPilRecBits);

        pstPilotRec->ucLocAsPrev = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);
        ulPilRecBits += 1;

        if (0 == pstPilotRec->ucLocAsPrev)
        {
            pstPilotRec->usDistance = (VOS_UINT16)TAF_XPDS_DecodeGetValue(9,
                                                                     pulTotNumOfBits,
                                                                     &pucHeadBuf[*pulCurrIdx],
                                                                     pulCurrIdx);

            pstPilotRec->ucAzimuth = (VOS_UINT8)TAF_XPDS_DecodeGetValue(6,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

            ulPilRecBits += 9 + 6;
        }

        pstPilotRec->ucTimeCorAsPrev = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

        ulPilRecBits += 1;

        if (0 == pstPilotRec->ucTimeCorAsPrev)
        {
            pstPilotRec->ucTimeCorr = (VOS_UINT8)TAF_XPDS_DecodeGetValue(7,
                                                                 pulTotNumOfBits,
                                                                 &pucHeadBuf[*pulCurrIdx],
                                                                 pulCurrIdx);

            pstPilotRec->ucTimeCorrUnc = (VOS_UINT8)TAF_XPDS_DecodeGetValue(3,
                                                                 pulTotNumOfBits,
                                                                 &pucHeadBuf[*pulCurrIdx],
                                                                 pulCurrIdx);

            ulPilRecBits += 7 + 3;
        }

        /* reserved bits */
        if ((ulPilRecBits % 8) > 0)
        {
            (VOS_VOID)TAF_XPDS_DecodeGetValue((8 - (ulPilRecBits % 8)),
                                                 pulTotNumOfBits,
                                                 &pucHeadBuf[*pulCurrIdx],
                                                 pulCurrIdx);
        }
    }
}


VOS_VOID TAF_XPDS_DecodeGenAquiAssisFreqRec(
    VOS_UINT8                                     *pucHeadBuf,
    VOS_UINT32                                    *pulTotNumOfBits,
    VOS_UINT32                                    *pulCurrIdx,
    TAF_XPDS_FWDLINK_RSP_GEN_AQUI_ASSI_STRU       *pstFwdRspAquAssi
)
{

    VOS_UINT8                              ucNumOfFr;
    VOS_UINT8                              ucPrevNumSv;
    VOS_UINT8                              ucLoop;
    TAF_XPDS_GEN_AQUI_ASSI_FREQ_REC_STRU  *pstFreqRec;

    ucNumOfFr      = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                            pulTotNumOfBits,
                                                            &pucHeadBuf[*pulCurrIdx],
                                                            pulCurrIdx);

    ucPrevNumSv                    = pstFwdRspAquAssi->ucNumOfFreqP;
    pstFwdRspAquAssi->ucNumOfFreqP  += ucNumOfFr;

    for (ucLoop = ucPrevNumSv; ucLoop < pstFwdRspAquAssi->ucNumOfFreqP; ucLoop++)
    {
        pstFreqRec = &(pstFwdRspAquAssi->astFreqRec[ucLoop]);

        pstFreqRec->ucBandCls = (VOS_UINT8)TAF_XPDS_DecodeGetValue(5,
                                                                 pulTotNumOfBits,
                                                                 &pucHeadBuf[*pulCurrIdx],
                                                                 pulCurrIdx);

        pstFreqRec->usCdmaFreq = (VOS_UINT16)TAF_XPDS_DecodeGetValue(11,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

        pstFreqRec->ucModeInd = (VOS_UINT8)TAF_XPDS_DecodeGetValue(2,
                                                                 pulTotNumOfBits,
                                                                 &pucHeadBuf[*pulCurrIdx],
                                                                 pulCurrIdx);

        pstFreqRec->ucPilInfAsPrev = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);

        if (0 == pstFreqRec->ucPilInfAsPrev)
        {
            pstFreqRec->ucRptrInfIncl = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                     pulTotNumOfBits,
                                                                     &pucHeadBuf[*pulCurrIdx],
                                                                     pulCurrIdx);
        }

        if (1 == pstFreqRec->ucRptrInfIncl)
        {
            pstFreqRec->ucRptrIdLen = (VOS_UINT8)TAF_XPDS_DecodeGetValue(6,
                                                             pulTotNumOfBits,
                                                             &pucHeadBuf[*pulCurrIdx],
                                                             pulCurrIdx);
        }

        if (0 == pstFreqRec->ucPilInfAsPrev)
        {
            pstFreqRec->ucNumOfPilTxF = (VOS_UINT8)TAF_XPDS_DecodeGetValue(6,
                                                                 pulTotNumOfBits,
                                                                 &pucHeadBuf[*pulCurrIdx],
                                                                 pulCurrIdx);
        }
    }
}


VOS_UINT32 TAF_XPDS_DecodeProvGenAquiAssis(
    VOS_UINT8                          *pucHeadBuf
)
{
    VOS_UINT32                                         ulTotNumOfBits;
    VOS_UINT32                                         ulCurrIdx;
    TAF_XPDS_FWDLINK_RSP_GEN_AQUI_ASSI_STRU           *pstFwdRspAquAssi;
    VOS_UINT8                                          ucPartNum;
    VOS_UINT8                                          ucTotalParts;

    ulTotNumOfBits     = 3;
    ulCurrIdx          = 0;

    pstFwdRspAquAssi  = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_FWDLINK_RSP_GEN_AQUI_ASSI_STRU));
    if (VOS_NULL_PTR == pstFwdRspAquAssi)
    {
        return VOS_ERR;
    }


    ucPartNum          = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    ucTotalParts       = (VOS_UINT8)TAF_XPDS_DecodeGetValue(4,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    /* if part number is 0, it is the new message so refresh the context data */
    if (0 == ucPartNum)
    {
        PS_MEM_SET(pstFwdRspAquAssi, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_GEN_AQUI_ASSI_STRU));
    }

    pstFwdRspAquAssi->ucGlobInfoAsPrev = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    pstFwdRspAquAssi->ucPartNum    = ucPartNum;
    pstFwdRspAquAssi->ucTotalParts = ucTotalParts;

    /* get global information record */
    if (0 == pstFwdRspAquAssi->ucGlobInfoAsPrev)
    {
        TAF_XPDS_DecodeGenAquiAssisGlobInfo(pucHeadBuf, &ulTotNumOfBits, &ulCurrIdx, &(pstFwdRspAquAssi->stGlobInfo));
    }

    pstFwdRspAquAssi->ucSvInfInclP    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    if (1 == pstFwdRspAquAssi->ucSvInfInclP)
    {
        pstFwdRspAquAssi->ucCodePhWinIncl = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                 &ulTotNumOfBits,
                                                                 &pucHeadBuf[ulCurrIdx],
                                                                 &ulCurrIdx);

        pstFwdRspAquAssi->ucDopp2Incl     = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                 &ulTotNumOfBits,
                                                                 &pucHeadBuf[ulCurrIdx],
                                                                 &ulCurrIdx);

        pstFwdRspAquAssi->ucDoppWinIncl   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                 &ulTotNumOfBits,
                                                                 &pucHeadBuf[ulCurrIdx],
                                                                 &ulCurrIdx);

        pstFwdRspAquAssi->ucSvOpModeIncl  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                 &ulTotNumOfBits,
                                                                 &pucHeadBuf[ulCurrIdx],
                                                                 &ulCurrIdx);

        pstFwdRspAquAssi->ucAzElIncl      = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                 &ulTotNumOfBits,
                                                                 &pucHeadBuf[ulCurrIdx],
                                                                 &ulCurrIdx);

        pstFwdRspAquAssi->ucSvHealthIncl  = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                                 &ulTotNumOfBits,
                                                                 &pucHeadBuf[ulCurrIdx],
                                                                 &ulCurrIdx);

        /* get the satellite record information */
        TAF_XPDS_DecodeGenAquiAssisSatRec(pucHeadBuf, &ulTotNumOfBits, &ulCurrIdx, pstFwdRspAquAssi);
    }


    pstFwdRspAquAssi->ucBsInfInclP = (VOS_UINT8)TAF_XPDS_DecodeGetValue(1,
                                                             &ulTotNumOfBits,
                                                             &pucHeadBuf[ulCurrIdx],
                                                             &ulCurrIdx);

    if (1 == pstFwdRspAquAssi->ucBsInfInclP)
    {
        TAF_XPDS_DecodeGenAquiAssisFreqRec(pucHeadBuf, &ulTotNumOfBits, &ulCurrIdx, pstFwdRspAquAssi);
    }

    PS_MEM_FREE(UEPS_PID_XPDS, pstFwdRspAquAssi);

    return VOS_OK;

}
#endif


VOS_UINT32 TAF_XPDS_DecodeDataBurstMsg(
    TAF_XPDS_DATA_BURST_MSG_STRU       *pstDataBurMsg,
    VOS_UINT8                          *pcBurstMsg
)
{
    VOS_UINT32                          ulTotalBits;
    VOS_UINT32                          ulCurrIdx;
    VOS_INT32                           ulLoop;

    PS_MEM_SET(pstDataBurMsg, 0x00, sizeof(TAF_XPDS_DATA_BURST_MSG_STRU));

    ulTotalBits = 0;
    ulCurrIdx   = 0;

    pstDataBurMsg->ucMsgNum    = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8, &ulTotalBits,
                                                            &pcBurstMsg[ulCurrIdx], &ulCurrIdx);

    pstDataBurMsg->ucBurstType = (VOS_UINT8)TAF_XPDS_DecodeGetValue(6, &ulTotalBits,
                                                            &pcBurstMsg[ulCurrIdx], &ulCurrIdx);

    if (pstDataBurMsg->ucBurstType != TAF_XPDS_BURST_TYPE_POS_DET)
    {
        return VOS_ERR;
    }

    pstDataBurMsg->ucNumMsgs   = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8, &ulTotalBits,
                                                            &pcBurstMsg[ulCurrIdx], &ulCurrIdx);


    if (pstDataBurMsg->ucNumMsgs != 0x01)
    {
        return VOS_ERR;
    }

    pstDataBurMsg->ucNumFields = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8, &ulTotalBits,
                                                            &pcBurstMsg[ulCurrIdx], &ulCurrIdx);

    for (ulLoop = 0; ulLoop < pstDataBurMsg->ucNumFields; ulLoop++)
    {
        pstDataBurMsg->aucData[ulLoop] = (VOS_UINT8)TAF_XPDS_DecodeGetValue(8, &ulTotalBits,
                                                                &pcBurstMsg[ulCurrIdx], &ulCurrIdx);
    }

    return VOS_OK;
}


#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

