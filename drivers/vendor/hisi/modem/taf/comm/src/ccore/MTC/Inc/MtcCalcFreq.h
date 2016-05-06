/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MtcCalcFreq.h
  版 本 号   : 初稿
  作    者   : j00174725
  生成日期   : 2014年03月04日
  最近修改   :
  功能描述   : MtcCalcFreq.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年03月04日
    作    者   : j00174725
    修改内容   : 创建文件

******************************************************************************/

#ifndef __MTC_CALC_FREQ_H__
#define __MTC_CALC_FREQ_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "LNvCommon.h"
#endif

#include "MtcRrcInterface.h"
#include "MtcRfLcdIntrusion.h"
#include "MtcCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, GU 结构定义(由上官声长00266224提供) Begin */
#define DC_MIMO_REMOVEINTERFREQOFF                  ( 0xbfff )                  /* 去除偏移值 */
#define FREQ_BAND_NUM                               ( 10 )                               /* 目前支持的频带数目 */
/* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, GU 结构定义(由上官声长00266224提供) End */

#if (FEATURE_ON == FEATURE_LTE)
/* 检查是否为FDD的band ind */
#define MTC_COMM_CHECK_IS_FDD_BAND_IND(ucBandInd)\
    ((((MTC_FREQ_BAND1 <= ucBandInd) && (MTC_FREQ_BAND32 > ucBandInd)))? VOS_TRUE:VOS_FALSE)

/* 检查是否为TDD的band ind */
#define MTC_COMM_CHECK_IS_PROCOL_TDD_BAND_IND(ucBandInd)\
    (((MTC_FREQ_BAND33 <= ucBandInd) && (MTC_FREQ_BAND44 >= ucBandInd))? VOS_TRUE:VOS_FALSE)

/* 非标准频段 begin */
#define MTC_COMM_CHECK_IS_NONSTANDARD_BAND_IND(ucBandInd)\
    ((((LTE_COMM_NONSTANDARD_BAND_BEGIN  <= ucBandInd) && (LTE_COMM_NONSTANDARD_BAND_END >= ucBandInd)) )? VOS_TRUE:VOS_FALSE)
#endif

/* Add by y00213812 for RF&LCD INTRUSION, 2014-03-04, Begin WCDMA 相关定义(shangguanshengchang提供)*/
#define MTC_GAS_BAND_TYPE_UNKNOWN                      (0)                      /* 未知频段 */

#define MTC_GSM_BAND_TYPE_450                          (0x0001)                /* ARFCN所代表的频段:GSM 450 */
#define MTC_GSM_BAND_TYPE_480                          (0x0002)                /* ARFCN所代表的频段:GSM 480 */
#define MTC_GSM_BAND_TYPE_850                          (0x0004)                /* ARFCN所代表的频段:GSM 850 */
#define MTC_GSM_BAND_TYPE_P900                         (0x0008)                /* ARFCN所代表的频段:P-GSM 900 */
#define MTC_GSM_BAND_TYPE_R900                         (0x0010)                /* ARFCN所代表的频段:R-GSM 900 */
#define MTC_GSM_BAND_TYPE_E900                         (0x0020)                /* ARFCN所代表的频段:E-GSM 900 */
#define MTC_GSM_BAND_TYPE_1800                         (0x0040)                /* ARFCN所代表的频段:DCS 1800 */
#define MTC_GSM_BAND_TYPE_1900                         (0x0080)                /* ARFCN所代表的频段:PCS 1900 */
#define MTC_GSM_BAND_TYPE_700                          (0x0100)                /* ARFCN所代表的频段:GSM 700 */
/* Add by y00213812 for RF&LCD INTRUSION, 2014-03-04, Begin WCDMA 相关定义(shangguanshengchang提供)*/



/* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, Begin WCDMA 相关定义(jiachangqin提供)*/
#define MTC_WAS_FREQ_BAND2_ADD_MAX_FREQ_NUM             (12)                    /*频段2的最大附加频率数*/
#define MTC_WAS_FREQ_BAND4_ADD_MAX_FREQ_NUM             (9)                     /*频段4的最大附加频率数*/
#define MTC_WAS_FREQ_BAND5_ADD_MAX_FREQ_NUM             (6)                     /*频段5的最大附加频率数*/
#define MTC_WAS_FREQ_BAND6_ADD_MAX_FREQ_NUM             (2)                     /*频段6的最大附加频率数*/
#define MTC_WAS_FREQ_BAND7_ADD_MAX_FREQ_NUM             (14)                    /*频段7的最大附加频率数*/
#define MTC_WAS_FREQ_BAND19_ADD_MAX_FREQ_NUM            (3)                     /*频段19的最大附加频率数*/

#define MTC_WAS_FREQ_BAND1_DL_LOW_FREQ                  (10562)
#define MTC_WAS_FREQ_BAND1_DL_HIGH_FREQ                 (10838)
#define MTC_WAS_FREQ_BAND1_TXRXSEPERATION               (950)

#define MTC_WAS_FREQ_BAND2_DL_LOW_FREQ                  (9662)
#define MTC_WAS_FREQ_BAND2_DL_HIGH_FREQ                 (9938)
#define MTC_WAS_FREQ_BAND2_TXRXSEPERATION               (400)

#define MTC_WAS_FREQ_BAND3_DL_LOW_FREQ                  (1162)
#define MTC_WAS_FREQ_BAND3_DL_HIGH_FREQ                 (1513)
#define MTC_WAS_FREQ_BAND3_TXRXSEPERATION               (225)

#define MTC_WAS_FREQ_BAND4_DL_LOW_FREQ                  (1537)
#define MTC_WAS_FREQ_BAND4_DL_HIGH_FREQ                 (1738)
#define MTC_WAS_FREQ_BAND4_TXRXSEPERATION               (225)

#define MTC_WAS_FREQ_BAND5_DL_LOW_FREQ                  (4357)
#define MTC_WAS_FREQ_BAND5_DL_HIGH_FREQ                 (4458)
#define MTC_WAS_FREQ_BAND5_TXRXSEPERATION               (225)

#define MTC_WAS_FREQ_BAND6_DL_LOW_FREQ                  (4387)
#define MTC_WAS_FREQ_BAND6_DL_HIGH_FREQ                 (4413)
#define MTC_WAS_FREQ_BAND6_TXRXSEPERATION               (225)

#define MTC_WAS_FREQ_BAND7_DL_LOW_FREQ                  (2237)
#define MTC_WAS_FREQ_BAND7_DL_HIGH_FREQ                 (2563)
#define MTC_WAS_FREQ_BAND7_TXRXSEPERATION               (225)

#define MTC_WAS_FREQ_BAND8_DL_LOW_FREQ                  (2937)
#define MTC_WAS_FREQ_BAND8_DL_HIGH_FREQ                 (3088)
#define MTC_WAS_FREQ_BAND8_TXRXSEPERATION               (225)

#define MTC_WAS_FREQ_BAND9_DL_LOW_FREQ                  (9237)
#define MTC_WAS_FREQ_BAND9_DL_HIGH_FREQ                 (9387)
#define MTC_WAS_FREQ_BAND9_TXRXSEPERATION               (475)

#define MTC_WAS_FREQ_BAND10_DL_LOW_FREQ                 (3112)
#define MTC_WAS_FREQ_BAND10_DL_HIGH_FREQ                (3388)
#define MTC_WAS_FREQ_BAND10_TXRXSEPERATION              (225)

#define MTC_WAS_FREQ_BAND11_DL_LOW_FREQ                 (3712)
#define MTC_WAS_FREQ_BAND11_DL_HIGH_FREQ                (3787)
#define MTC_WAS_FREQ_BAND11_TXRXSEPERATION              (225)

#define MTC_WAS_FREQ_BAND19_DL_LOW_FREQ                 (712)
#define MTC_WAS_FREQ_BAND19_DL_HIGH_FREQ                (763)
#define MTC_WAS_FREQ_BAND19_TXRXSEPERATION              (400)

/* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, End WCDMA 相关定义(jiachangqin提供)*/

/* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, End WCDMA 相关定义(baihongjin提供)*/
#define MTC_TDS_FRQ_UNIN                                (2) /* 单位为100KHZ */
/* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, End WCDMA 相关定义(baihongjin提供)*/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, GU 结构定义 Begin */
/*****************************************************************************
 结构名    : MTC_RF_WCDMA_FREQ_BAND_INFO_STRU
 协议表格  : 25.101协议
 结构说明  : 频段的相关信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwFreqBandId;                          /* BAND ID*/
    VOS_UINT16                          uhwTxRxSeparation;                      /* 协议典型的上下行收发频差*/
    VOS_UINT16                          uhwDlGeneralFreqNum_High;               /* 一般频点的下行频点上限 */
    VOS_UINT16                          uhwDlGeneralFreqNum_Low;                /* 一般频点的下行频点下限 */
    VOS_UINT16                          uhwDlGeneralOffset;                     /* 一般频点的下行偏置 */
    VOS_UINT16                          uhwDlAddOffset;                         /* 离散频点的下行偏置 */
    VOS_UINT16                          uhwUlGeneralFreqNum_High;               /* 一般频点的上行频点上限 */
    VOS_UINT16                          uhwUlGeneralFreqNum_Low;                /* 一般频点的上行频点下限 */
    VOS_UINT16                          uhwUlGeneralOffset;                     /* 一般频点的上行偏置 */
    VOS_UINT16                          uhwUlAddOffset;                         /* 离散频点的上行偏置 */
    VOS_UINT16                          uhwBandWidth;                           /* 频段带宽 */
    VOS_UINT16                          uhwStartFreq;                           /* 频段起始频率 100kHZ */
}MTC_RF_WCDMA_FREQ_BAND_INFO_STRU;
/* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, GU 结构定义 End */

/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT16 MTC_CalcGsmDlFreq(
    VOS_UINT16                          ushwBand,
    VOS_UINT16                          ushwFreqIndex
);

VOS_UINT16  MTC_CalcWcdmaDlFreq(
    VOS_UINT16                          ushwFreqBandId,
    VOS_UINT16                          ushwDlFreqNum
);

VOS_UINT32 MTC_WCDMAFindFreqBandNoByDlFreq(VOS_UINT16 usDlFreq);


#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT16  MTC_CalcLteDlFreq(
    VOS_UINT16                          ucFreqBandIndicator,
    VOS_UINT32                          ulDlEarfcn
);
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
VOS_UINT16  MTC_CalcTdsDlFreq(
    VOS_UINT16                          usDlEarfcn
);

VOS_UINT16  MTC_TDS_GetBandInfoByDlArfcn(VOS_UINT32 ulDlEarfcn);
#endif

#if 0
VOS_VOID  MTC_FillGsmNcellFreq(
    MTC_RF_USING_FREQ_LIST_STRU        *pstRfUsingFreqList,
    MTC_RF_FREQ_LIST_STRU              *pstRfFreqList
);

VOS_VOID  MTC_FillWcdmaNcellFreq(
    MTC_RF_USING_FREQ_LIST_STRU        *pstRfUsingFreqList,
    MTC_RF_FREQ_LIST_STRU              *pstRfFreqList
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID  MTC_FillLteNcellFreq(
    MTC_RF_USING_FREQ_LIST_STRU        *pstRfUsingFreqList,
    MTC_RF_FREQ_LIST_STRU              *pstRfFreqList
);
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
VOS_VOID  MTC_FillTdsNcellFreq(
    MTC_RF_USING_FREQ_LIST_STRU        *pstRfUsingFreqList,
    MTC_RF_FREQ_LIST_STRU              *pstRfFreqList
);
#endif
#endif

VOS_VOID  MTC_CalcHoppingFreq(
    MTC_RF_FREQ_LIST_STRU              *pstGsmFreqInfo,
    MTC_RF_FREQ_LIST_STRU              *pstRfFreqList
);

VOS_VOID  MTC_ChangeRfArfcnToFreq(
    RRC_MTC_USING_FREQ_IND_STRU        *pstUsingFreq,
    MTC_RF_USING_FREQ_LIST_STRU        *pstRfFreqList
);

VOS_VOID MTC_CalcRfDlFreq(
    RRC_MTC_USING_FREQ_IND_STRU        *pstUsingFreq,
    MTC_MODEM_FREQ_LIST_STRU           *pstModemFreq
);

VOS_VOID MTC_GetTLBandInfoFromUsingFreq(
    RRC_MTC_USING_FREQ_IND_STRU        *pstUsingFreq
);


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MtcCalcFreq.h */
