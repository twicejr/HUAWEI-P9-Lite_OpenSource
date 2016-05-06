/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsCommFunc.c
  版 本 号   : 初稿
  作    者   : c00299064
  生成日期   : 2015年9月14日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2015年9月14日
    作    者   : g00261581
    修改内容   : CDMA-AGPS项目新增

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifndef BIG_ENDIAN
#define BIG_ENDIAN 1
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_COMM_FUNC_C

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "AtXpdsInterface.h"
#include "TafXpdsCtx.h"
#include "TafXpdsMntn.h"
#include "TafXpdsSndAt.h"
#include "TafSdcCtx.h"
#include "TafXpdsSndXsms.h"
#include "TafXpdsSndCas.h"
#include "TafXpdsCommFunc.h"



#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

const VOS_FLOAT g_sfPnPhaseMatchTable[64] =
{
    1   ,1.125   ,1.25   ,1.375   ,1.5   ,1.625   ,1.75   ,1.875   ,
    2   ,2.25    ,2.5    ,2.75    ,3     ,3.25    ,3.5    ,3.75    ,
    4   ,4.5     ,5      ,5.5     ,6     ,6.5     ,7      ,7.5     ,
    8   ,9       ,10     ,11      ,12    ,13      ,14     ,15      ,
    16  ,18      ,20     ,22      ,24    ,26      ,28     ,30      ,
    32  ,36      ,40     ,44      ,48    ,52      ,56     ,60      ,
    64  ,72      ,80     ,88      ,96    ,104     ,112    ,120     ,
    128 ,144     ,160    ,176     ,192   ,208     ,224    ,240
};

TAF_XPDS_RSLT_REASON_ITEM_STRU          g_astTafXpdsRlstReasonMapItem[] =
{
    {TAF_XPDS_PROC_RSLT_AT_STOP           , TAF_XPDS_CANCEL_REASON_USER_CANCEL           },
    {TAF_XPDS_PROC_RSLT_UP_PDE_DISCONNECT , TAF_XPDS_CANCEL_REASON_PDE_DISCONNECT        },
    {TAF_XPDS_PROC_RSLT_UP_MPC_DISCONNECT , TAF_XPDS_CANCEL_REASON_MPC_DISCONNECT        },
    {TAF_XPDS_PROC_RSLT_PDE_REJECT        , TAF_XPDS_CANCEL_REASON_PDE_REJ_POS_SESSION   },
    {TAF_XPDS_PROC_RSLT_IS801_TIMEOUT     , TAF_XPDS_CANCEL_REASON_IS801_SESSION_TIME_OUT},
    {TAF_XPDS_MPC_PROC_RSLT_TIMER_OUT     , TAF_XPDS_CANCEL_REASON_MPC_RSP_TIME_OUT      },
};

/*****************************************************************************
  3 Function Definitions
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_XPDS_ConvertPrefRespQualValueToTimerLimitLen
 功能描述  : 转换PrefRespQual字段值为定时器时长
 输入参数  : VOS_UINT8                           ucPrefRespQual
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月24日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_ConvertPrefRespQualValueToTimerLimitLen(
    VOS_UINT8                           ucPrefRespQual
)
{
    VOS_UINT32                          ulTimerLen;

    ulTimerLen = 0;

    switch (ucPrefRespQual)
    {
        case 0x00:
            ulTimerLen = 2 * 1000;
            break;

        case 0x01:
            ulTimerLen = 4 * 1000;
            break;

        case 0x02:
            ulTimerLen = 8 * 1000;
            break;

        case 0x03:
            ulTimerLen = 16 * 1000;
            break;

        case 0x04:
            ulTimerLen = 32 * 1000;
            break;

        case 0x05:
            ulTimerLen = 64 * 1000;
            break;

        case 0x06:
            ulTimerLen = 128 * 1000;
            break;

        case 0x07:
            ulTimerLen = 256 * 1000;
            break;

        default:
            break;
    }

    return ulTimerLen;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetPnbyPhaseID
 功能描述  : 在指定缓存中找出对应小区ID的所有Pn Phase
 输入参数  : usPilotPN          -- 小区ID
             pstCasRptPilotBuff -- 待查查找PN phase

 输出参数  : pstCasRptPilotBuff -- 对应小区的所有PN phase

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月10日
    作    者   : d00212987
    修改内容   : AGPS迭代1新增
*****************************************************************************/
VOS_VOID TAF_XPDS_GetPnbyPhaseID(
    VOS_UINT16                          usPilotPN,
    TAF_XPDS_CAS_RPT_PILOT_BUFF_STRU   *pstCasRptPilotBuff
)
{
    VOS_UINT32                          ulLoopCount;

    for (ulLoopCount = 0; ulLoopCount < pstCasRptPilotBuff->ulPilotMeasNum; ulLoopCount++)
    {
        if (usPilotPN == pstCasRptPilotBuff->astPilotMeasInfo[ulLoopCount].usPilotPN)
        {
            pstCasRptPilotBuff->aulPnPhasebuff[pstCasRptPilotBuff->ulPnPhasebuffNum] = pstCasRptPilotBuff->astPilotMeasInfo[ulLoopCount].ulPnPhase;

            pstCasRptPilotBuff->ulPnPhasebuffNum++;

            if (TAF_XPDS_PILOT_PHASE_BUFF_MAX <= pstCasRptPilotBuff->ulPnPhasebuffNum)
            {
                return;
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_CalcDataVar
 功能描述  : 计算方差
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月27日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_FLOAT TAF_XPDS_CalcDataVar
(
    VOS_UINT32                          ulDataNum,
    VOS_UINT32                         *pulData
)
{
    VOS_FLOAT                           sfAvrg      = 0.0F;
    VOS_UINT32                          ulIndex     = 0;
    VOS_UINT32                          ulSum       = 0;
    VOS_FLOAT                           sfVarSum    = 0.0F;

    if (0 == ulDataNum)
    {
        return 0.0F;
    }

    /* 计算平均值 */
    for (ulIndex = 0; ulIndex < ulDataNum; ulIndex++)
    {
        ulSum += pulData[ulIndex];
    }

    sfAvrg = (VOS_FLOAT)ulSum / ulDataNum;

    /* 计算方差 */
    for (ulIndex = 0; ulIndex < ulDataNum; ulIndex++)
    {
        sfVarSum += ((pulData[ulIndex] - sfAvrg) * (pulData[ulIndex] - sfAvrg));
    }

    return (sfVarSum / ulDataNum);

}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SquareRoot
 功能描述  : 计算平方根的函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月27日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_FLOAT TAF_XPDS_SquareRoot(VOS_FLOAT sfNumber)
{
    VOS_UINT32                      ulMagic = 0;
    VOS_FLOAT                       sfSqrt;
    VOS_FLOAT                       sfOffset;
    const VOS_FLOAT                 sfThreeHalf = 1.5F;

    sfOffset    = 0.5F * sfNumber;
    sfSqrt      = sfNumber;
    ulMagic     = *(VOS_UINT32*)&sfSqrt;
    ulMagic     = 0x5F3759DF - (ulMagic >> 1);
    sfSqrt      = *(VOS_FLOAT*)&ulMagic;

    /* 迭代1 */
    sfSqrt      = sfSqrt * (sfThreeHalf - (sfOffset * sfSqrt * sfSqrt));

    /* 迭代2 */
    sfSqrt      = sfSqrt * (sfThreeHalf - (sfOffset * sfSqrt * sfSqrt));

    return (sfSqrt * sfNumber);

}

/*****************************************************************************
 函 数 名  : TAF_XPDS_CalcPnPhaseSqrt
 功能描述  : 计算RMS_ERR_PHASE的函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月27日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_XPDS_CalcRmsErrPhase(
    VOS_FLOAT                           sfSqrt
)
{
    VOS_UINT8                           ucLoop = 0;

    if (1.0 > sfSqrt)
    {
        return 0;
    }

    for (ucLoop = 0; ucLoop < 64; ucLoop++)
    {
        if (g_sfPnPhaseMatchTable[ucLoop] > sfSqrt)
        {
            return ucLoop;
        }
    }

    return 63;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_CalcPnPhaseSqrt
 功能描述  : 计算平方根的函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月27日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_XPDS_CalcPnPhaseSqrt(
    VOS_UINT32                         *pulData,
    VOS_UINT32                          ulDataLen
)
{
    VOS_FLOAT                           sfVar       = 0.0F;
    VOS_FLOAT                           sfChipSqrt  = 0.0F;
    VOS_FLOAT                           sfMeterSqrt = 0.0F;

    sfVar   = TAF_XPDS_CalcDataVar(ulDataLen, pulData);

    sfChipSqrt  = TAF_XPDS_SquareRoot(sfVar);

    /* 将SQRT(CHIP 转换成 METER) */
    sfMeterSqrt = sfChipSqrt * 300 / 1.2288F;

    /* 查表得到RMS_ERR_PHASE */
    return TAF_XPDS_CalcRmsErrPhase(sfMeterSqrt / 16.0F);

}

/*****************************************************************************
 函 数 名  : TAF_XPDS_UpdatePpmInGlobal
 功能描述  : 处理PPM INFO 相关的消息
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月10日
    作    者   : c00299064
    修改内容   : AGPS迭代1新增
*****************************************************************************/
VOS_VOID TAF_XPDS_UpdatePpmInGlobal(VOS_VOID)
{
    TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU        *pstPilotInfo;
    TAF_XPDS_CAS_RPT_PILOT_BUFF_STRU                  *pstCasRptPilotBuff;
    VOS_UINT8                                          ucPilotCalcValue;
    VOS_UINT32                                         ulLoopCount;

    pstPilotInfo = &(TAF_XPDS_GetPublicDataAddr()->stPilotInfo);

    pstCasRptPilotBuff = &pstPilotInfo->stCasRptPilotBuff;

    if (TAF_XPDS_PILOT_MEAS_BUFF_MAX < pstCasRptPilotBuff->ulPilotMeasNum)
    {
        pstCasRptPilotBuff->ulPilotMeasNum = TAF_XPDS_PILOT_MEAS_BUFF_MAX;
    }

    if (pstPilotInfo->ucNumOfPilotP > TAF_XPDS_RL_PHASE_PILREC_MAX)
    {
        pstPilotInfo->ucNumOfPilotP = TAF_XPDS_RL_PHASE_PILREC_MAX;
    }

    /* 启动计算pilot phase均方差 */
    /* 按照pn offset取出所有ph phase 计算方差 */
    for (ulLoopCount = 0; ulLoopCount < pstPilotInfo->ucNumOfPilotP; ulLoopCount++)
    {
        /* 按照pn phase ID取出全部pn phase*/
        pstCasRptPilotBuff->ulPnPhasebuffNum = 0;

        TAF_XPDS_GetPnbyPhaseID(pstPilotInfo->astPilotRec[ulLoopCount].usPilotPN,
                                     pstCasRptPilotBuff);

        ucPilotCalcValue = TAF_XPDS_CalcPnPhaseSqrt(pstCasRptPilotBuff->aulPnPhasebuff,
                                                         pstCasRptPilotBuff->ulPnPhasebuffNum);

        pstPilotInfo->astPilotRec[ulLoopCount].ucRmsErrPhase = ucPilotCalcValue;
    }

    /* Hook Pilot Phase Info Got From CAS */
    TAF_XPDS_MNTN_TracePilotPhaseInfoCtxIndMsg();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_FormatPnStrength
 功能描述  : XPDS收到CAS PnStrength 按协议强转成需求值
 输入参数  : sRefPnStrength : CAS上报sRefPnStrength
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月10日
    作    者   : d00212987
    修改内容   : AGPS迭代1新增
*****************************************************************************/
VOS_UINT8 TAF_XPDS_FormatPnStrength(
    VOS_INT16                           sRefPnStrength
)
{
    VOS_INT16                           sPnStrengthTemp;

 /* 3GPP2 C.S0022-0  v3 .0:
    If this value is less than 0,the modile station shall set this field to '000000'.
    If this value is greater than '11111' the mobile station shall set this field to '11111'*/
    sPnStrengthTemp = (sRefPnStrength / -4);

    if (TAF_XPDS_MIN_PILOT_STRENGTH_VALUE > sPnStrengthTemp)
    {
        sPnStrengthTemp = TAF_XPDS_MIN_PILOT_STRENGTH_VALUE;
    }
    else if (TAF_XPDS_MAX_PILOT_STRENGTH_VALUE < sPnStrengthTemp)
    {
        sPnStrengthTemp = TAF_XPDS_MAX_PILOT_STRENGTH_VALUE;
    }
    else
    {
    }

    return (VOS_UINT8)sPnStrengthTemp;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_FormatServFreqRssi
 功能描述  : XPDS收到CAS ServFreqRssi 按协议强转成需求值
 输入参数  : sServFreqRssi : CAS上报sServFreqRssi
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月10日
    作    者   : d00212987
    修改内容   : AGPS迭代1新增
*****************************************************************************/
VOS_UINT8 TAF_XPDS_FormatServFreqRssi(
    VOS_INT16                           sServFreqRssi
)
{
    VOS_INT16                           sServFreqRssiTemp;

/* The mobile station shall set this field to max (0, min(31,「(total_received_power + 110)/2))
    where total_received_power is the mean input power
    received by the mobile station on frequency CDMA_FREQ, in dB m/1. 23 MH z.
    Note that this de finition is taken from the SF_TOTAL_RX_PWR(se rving frequency total received
    power) defined in TIA/EIA-95 -B Section 6.7.2.3.2.20 :Candidate Frequency Search Report Message.
*/
    sServFreqRssiTemp = ((sServFreqRssi / 8) + 110);

    /* 除 2 取上限 */
    sServFreqRssiTemp = ((sServFreqRssiTemp + 1) / 2);

    if (31 < sServFreqRssiTemp)
    {
        sServFreqRssiTemp = 31;
    }

    if (0 > sServFreqRssiTemp)
    {
        sServFreqRssiTemp = 0;
    }

    return (VOS_UINT8)sServFreqRssiTemp;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_FindCancelReasonByRslt
 功能描述  : 通过当前的处理结果查找CANCEL原因值
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月09日
    作    者   : g00256031
    修改内容   : AGPS迭代2新增
*****************************************************************************/
TAF_XPDS_CANCEL_REASON_ENUM_UINT8 TAF_XPDS_FindCancelReasonByRslt(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enProcRslt
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulArraySize;

    ulArraySize = sizeof(g_astTafXpdsRlstReasonMapItem)/sizeof(g_astTafXpdsRlstReasonMapItem[0]);

    for (ulIndex = 0; ulIndex < ulArraySize; ulIndex++)
    {
        if (enProcRslt == g_astTafXpdsRlstReasonMapItem[ulIndex].enProcRslt)
        {
            return (TAF_XPDS_CANCEL_REASON_ENUM_UINT8)g_astTafXpdsRlstReasonMapItem[ulIndex].ulCancelReason;
        }
    }

    return TAF_XPDS_CANCEL_REASON_BUTT;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_ConvertOmGpsFixModeToXpdsGpsFixMode
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
TAF_XPDS_FIX_MODE_ENUM_UINT8 TAF_XPDS_ConvertOmGpsFixModeToXpdsGpsFixMode(
    NAS_OM_CDMA_GPS_FIX_MODE_ENUM_UINT8                     enOmGpsFixMode
)
{
    switch (enOmGpsFixMode)
    {
        case NAS_OM_CDMA_GPS_FIX_MODE_UNKNOWN:
            return TAF_XPDS_UNKOWN_MODE;

        case NAS_OM_CDMA_GPS_FIX_MODE_MSA:
            return TAF_XPDS_MSA_MODE;

        case NAS_OM_CDMA_GPS_FIX_MODE_MSB:
            return TAF_XPDS_MSB_MODE;

        case NAS_OM_CDMA_GPS_FIX_MODE_MSS:
            return TAF_XPDS_MSS_MODE;

        default:
            return TAF_XPDS_MODE_BUTT;
    }
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_ConvertOmGpsFixModeToXpdsGpsFixMode
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
TAF_XPDS_GPS_START_MODE_ENUM_UINT8 TAF_XPDS_ConvertOmGpsStartModeToXpdsStartMode(
    NAS_OM_CDMA_GPS_START_MODE_ENUM_UINT8                     enOmGpsStartMode
)
{
    switch (enOmGpsStartMode)
    {
        case NAS_OM_CDMA_GPS_START_MODE_COLD:
            return TAF_XPDS_GPS_START_MODE_COLD;

        case NAS_OM_CDMA_GPS_START_MODE_HOT:
            return TAF_XPDS_GPS_START_MODE_HOT;

        default:
            return TAF_XPDS_MODE_BUTT;
    }
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_ConvertXpdsGpsFixTypeToOmGpsFixType
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
NAS_OM_CDMA_GPS_FIX_TYPE_ENUM_UINT8 TAF_XPDS_ConvertXpdsGpsFixTypeToOmGpsFixType(
    TAF_MSG_CDMA_GPS_FIX_TYPE_ENUM_UINT8                    enXpdsFixType
)
{
    switch (enXpdsFixType)
    {
        case TAF_MSG_CDMA_GPS_FIX_UNKNOWN:
            return NAS_OM_CDMA_GPS_FIX_TYPE_UNKNOWN;

        case TAF_MSG_CDMA_GPS_FIX_2D:
            return NAS_OM_CDMA_GPS_FIX_TYPE_2D;

        case TAF_MSG_CDMA_GPS_FIX_3D:
            return NAS_OM_CDMA_GPS_FIX_TYPE_3D;

        case TAF_MSG_CDMA_GPS_FIX_TYPE_MAX:
            return NAS_OM_CDMA_GPS_FIX_TYPE_MAX;

        default:
            return NAS_OM_CDMA_GPS_FIX_TYPE_ENUM_BUTT;
    }
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_ConvertFlPdeRspMsgTypeToOmGpsMsgType
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_ENUM_UINT8 TAF_XPDS_ConvertFlPdeRspMsgTypeToOmGpsMsgType(
    VOS_UINT32                          ulRspType
)
{
    switch (ulRspType)
    {
        case TAF_XPDS_FL_MSGTYPE_RSP_REJECT:
            return NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_RSP_REJECT;

        case TAF_XPDS_FL_MSGTYPE_RSP_PROV_LOCATION_RESPONSE:
            return NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_RSP_PROV_LOC_RSP;

        case TAF_XPDS_FL_MSGTYPE_RSP_PROV_ACQ_ASSISTANCE:
            return NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_RSP_PROV_GPS_ACQ_ASSIST;

        case TAF_XPDS_FL_MSGTYPE_RSP_PROV_GPS_EPHEMERIS:
            return NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_RSP_PROV_GPS_EPH;

        case TAF_XPDS_FL_MSGTYPE_RSP_PROV_GPS_ALMANAC:
            return NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_RSP_PROV_GPS_ALM;

        default:
            return NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_BUTT;
    }
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_ConvertFlPdeReqMsgTypeToOmGpsMsgType
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_ENUM_UINT8 TAF_XPDS_ConvertFlPdeReqMsgTypeToOmGpsMsgType(
    VOS_UINT32                          ulReqType
)
{
    switch (ulReqType)
    {
        case TAF_XPDS_FL_MSGTYPE_REQ_LOCATION_INFO:
            return NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_REQ_LOC_RSP;

        case TAF_XPDS_FL_MSGTYPE_REQ_MS_INFO:
            return NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_REQ_MS_INFO;

        case TAF_XPDS_FL_MSGTYPE_REQ_PSEUDORANGE_MEAS:
            return NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_REQ_PSUEDO_MEAS;

        case TAF_XPDS_FL_MSGTYPE_REQ_PILOT_PHASE_MEAS:
            return NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_FL_REQ_PH_MEAS;

        default:
            return NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_BUTT;
    }
}


#endif

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

