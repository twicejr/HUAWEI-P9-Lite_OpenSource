/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasNvInterface.h
  Description     : NasNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __PHY_H__
#define __PHY_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           参数设置消息结构                                 *
*                                                                            *
******************************************************************************/

/*****************************************************************************
 结构名    : IMEI_STRU
 结构说明  : IMEI结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                     ulWBand;
    VOS_UINT32                                     ulWbandExtRsv;
    VOS_UINT32                                     ulGeBand;
}NV_WG_RF_MAIN_BAND_STRU;


/*****************************************************************************
 结构名    : 
 结构说明  : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                     Rf_Connect;
    VOS_UINT16                                     Abb_Connect;
}GSM_STRU;

/*****************************************************************************
 备注 : lanke添加，请liuyan核对 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                     TA_Stub;
}TA_STUB_STRU;


/*****************************************************************************
 备注 : lanke添加，请liuyan核对 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                     TA_RF_DELAY_VAL;
}TA_RF_DELAY_VAL_STRU;

/*****************************************************************************
 备注 : lanke添加，请liuyan核对 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                     uhwOpenTotolpcFlg;
    VOS_UINT16                                     uhwOutageProbability;
    VOS_UINT16                                     uhwSirErrorStep;
    VOS_UINT16                                     uhwCorrectionFactor;
    VOS_UINT16                                     uhwSirOutageOffset;
    VOS_INT16                                     shwOoutageIncrementThresUp;
    VOS_INT16                                     shwOoutageIncrementThresDown;
    VOS_INT16                                     shwOutagetargetStepUp;
    VOS_INT16                                     shwOutagetargetStepDown;
    VOS_INT16                                     shwRsv;
}NV_TOTOLPC_PARA_CTR_STRU;

/*****************************************************************************
 备注 : lanke添加，请liuyan核对 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                     usLteEvaluateServCellReportCorr;    /*[0,30]*/
    VOS_INT16                                     sLteEvaluateServCellRscpThres;    /*[-1040,-320]*/
    VOS_UINT16                                     usLteEvaluateServCellDeltaThres;    /*[0,480]*/
}NV_DRX_LTE_EVALUATE_PARA_STRU;

/*****************************************************************************
 备注 : lanke添加，请liuyan核对 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                     TimeRXNoDataDpa;
    VOS_UINT16                                     TimeRXNoDataR99Turbo;
    VOS_UINT16                                     TimeRXNoDataR99Vtb;
}NV_ANT2_OFF_EVA_THRESH_STRU;


typedef struct
{
    VOS_UINT16                                     Rf_Connect;
    VOS_UINT16                                     Abb_Connect;
}WCDMA_STRU;

typedef struct
{
    WCDMA_STRU                                   stWcdma;
    GSM_STRU                                     stGsm[4];
}NV_WG_AB_CHAN_EQUAL_STRU;


/*****************************************************************************
 结构名    : TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU
 结构说明  : TAF_CUSTOM_SIM_LOCK_PLMN_INFO结构
*****************************************************************************/


typedef struct
{
    VOS_INT16                               NV_GSM850_TX_TEMP_COMP[16];    /*[-100,100]*/
}NV_GSM_BAND_TX_TEMP_COMP_STRU;


typedef struct
{
    VOS_UINT16                              NV_EDGE850_TX_PA_GAIN_DEFAULT;
}NV_GSM_BAND_TX_PA_GAIN_DEFAULT_STRU;



typedef struct
{
    VOS_INT16                                     sPower10th;
    VOS_UINT16                                     usPaVcc;
    VOS_UINT16                                     usPaBias1;
    VOS_UINT16                                     usPaBias2;
    VOS_UINT16                                     usPaBias3;
}ASTAPTTABLE_STRU;




typedef struct
{
    VOS_INT16                               NV_W_TX_DCUPA_IQ_REDUCTION[7];
}NV_W_TX_DCUPA_IQ_REDUCTION_STRU;

typedef struct
{
    VOS_UINT16                                     usLowPwrActiveTime[4];
}NV_W_TX_RFIC_LOWPWR_CFG_TIMING_STRU;


typedef struct
{
    VOS_INT16                               NV_W_TX_HDET_DCUPA_CM_COMP_B1[7];
}NV_W_TX_HDET_DCUPA_CM_COMP_STRU;

typedef struct
{
    VOS_UINT16                                     usTxSwcActiveTime;
}NV_W_TX_SW_CFG_TIMING_STRU;

typedef struct
{
    VOS_INT16                               NV_W_TX_PA_APT_DCUPA_CM_COMP_B1[7];
}NV_W_TX_PA_APT_DCUPA_CM_COMP_STRU;

typedef struct
{
    VOS_UINT16                              WDSP_RTT_TEST_SWITCH;    /*[0,1]*/
}WDSP_RTT_TEST_SWITCH_STRU;

typedef struct
{
    VOS_UINT32                              TA_Stub;
}TA_STUB_STRU;

typedef struct
{
    VOS_UINT32                              TA_RF_DELAY_VAL;
}TA_RF_DELAY_VAL_STRU;

typedef struct
{
    VOS_UINT16                                     usLteEvaluateServCellReportCorr;    /*[0,30]*/
    VOS_INT16                                     sLteEvaluateServCellRscpThres;    /*[-1040,-320]*/
    VOS_UINT16                                     usLteEvaluateServCellDeltaThres;    /*[0,480]*/
}NV_DRX_LTE_EVALUATE_PARA_STRU;

typedef struct
{
    VOS_UINT16                                     TimeRXNoDataDpa;
    VOS_UINT16                                     TimeRXNoDataR99Turbo;
    VOS_UINT16                                     TimeRXNoDataR99Vtb;
}NV_ANT2_OFF_EVA_THRESH_STRU;

typedef struct
{
    VOS_INT16                                     LowVoltDeltaPower;
    VOS_UINT16                                     DataFrameThreshold;
    VOS_UINT16                                     NoDataFrameThreshold;
    VOS_INT16                                     LowRssiThreshold;
    VOS_INT16                                     HighRssiThreshold;
    VOS_UINT16                                     TxPowerCntThreshold;
    VOS_UINT16                                     HsupaRemainPowerCntThreshold;
    VOS_UINT16                                     R99RemainPowerCntThreshold;
    VOS_UINT16                                     ForceConfigLowPowerThreshold;
}NV_VOLT_LOWPOWER_CTRL_STRU;

typedef struct
{
    VOS_UINT16                              WDSP_RTT_TEST_SWITCH;    /*[0,1]*/
}WDSP_RTT_TEST_SWITCH_STRU;

typedef struct
{
    VOS_UINT8                               GGPHYGCFContent[10];
}GGPHYGCFCONTENT_STRU;



typedef struct
{
    VOS_UINT32                                     Table1[30];
    VOS_UINT32                                     Table2[30];
    VOS_UINT32                                     Table3[30];
    VOS_UINT32                                     Table4[30];
    VOS_UINT32                                     Table5[30];
    VOS_UINT32                                     Table6[30];
    VOS_UINT32                                     Table7[30];
    VOS_UINT32                                     Table8[30];
    VOS_UINT32                                     Table9[30];
    VOS_UINT32                                     Table10[30];
    VOS_UINT32                                     Table11[30];
    VOS_UINT32                                     Table12[30];
    VOS_UINT32                                     Table13[30];
    VOS_UINT32                                     Table14[30];
    VOS_UINT32                                     Table15[30];
    VOS_UINT32                                     Table16[30];
    VOS_UINT32                                     Table17[30];
    VOS_UINT32                                     Table18[30];
}W_HSPA_CQI_TABLE1_STRU;

typedef struct
{
    VOS_UINT32                                     Table19[30];
    VOS_UINT32                                     Table20[30];
    VOS_UINT32                                     Table21[30];
    VOS_UINT32                                     Table22[30];
    VOS_UINT32                                     Table23[30];
    VOS_UINT32                                     Table24[30];
    VOS_UINT32                                     Table25[30];
    VOS_UINT32                                     Table26[30];
    VOS_UINT32                                     Table27[30];
    VOS_UINT32                                     Table28[30];
    VOS_UINT32                                     Table29[30];
    VOS_UINT32                                     Table30[30];
    VOS_UINT32                                     Table31[30];
    VOS_UINT32                                     Table32[30];
    VOS_UINT32                                     Table33[30];
    VOS_UINT32                                     Table34[30];
    VOS_UINT32                                     Table35[30];
    VOS_UINT32                                     Table36[30];
}W_HSPA_CQI_TABLE2_STRU;

typedef struct
{
    VOS_UINT32                                     Table37[30];
    VOS_UINT32                                     Table38[30];
    VOS_UINT32                                     Table39[30];
    VOS_UINT32                                     Table40[30];
    VOS_UINT32                                     Table41[30];
    VOS_UINT32                                     Table42[30];
    VOS_UINT32                                     Table43[30];
    VOS_UINT32                                     Table44[30];
    VOS_UINT32                                     Table45[30];
    VOS_UINT32                                     Table46[30];
    VOS_UINT32                                     Table47[30];
    VOS_UINT32                                     Table48[30];
    VOS_UINT32                                     Table49[30];
    VOS_UINT32                                     Table50[30];
    VOS_UINT32                                     Table51[30];
    VOS_UINT32                                     Table52[30];
    VOS_UINT32                                     Table53[30];
    VOS_UINT32                                     Table54[30];
}W_HSPA_CQI_TABLE3_STRU;

typedef struct
{
    VOS_UINT16                                     uhwOpenTotolpcFlg;
    VOS_UINT16                                     uhwOutageProbability;
    VOS_UINT16                                     uhwSirErrorStep;
    VOS_UINT16                                     uhwCorrectionFactor;
    VOS_UINT16                                     uhwSirOutageOffset;
    VOS_INT16                                     shwOoutageIncrementThresUp;
    VOS_INT16                                     shwOoutageIncrementThresDown;
    VOS_INT16                                     shwOutagetargetStepUp;
    VOS_INT16                                     shwOutagetargetStepDown;
    VOS_INT16                                     shwRsv;
}NV_TOTOLPC_PARA_CTR_STRU;

typedef struct
{
    VOS_UINT16      NV_PA_CONTROL_MIPI_MODE[2];
}NV_PA_CONTROL_MIPI_MODE_STRU;

typedef struct
{
    VOS_UINT16                                     usMultiplierUnit;
    VOS_UINT16                                     usDividerUnit;
}EXP_ALG_PARA_STRU;

typedef struct
{
    VOS_UINT32                                     ulValidCount;
    EXP_ALG_PARA_STRU                       stEXP_ALG_PARA_STRU[10];
}NV_W_HDET_NEGATIVE_EXP_ALG_TABLE_STRU;

typedef struct
{
    VOS_UINT32                                     ulValidCount;
    EXP_ALG_PARA_STRU                       stEXP_ALG_PARA_STRU[10];
}NV_W_HDET_POSITIVE_EXP_ALG_TABLE_STRU;

typedef struct
{
    VOS_INT16                                     sTxRefPower;
    VOS_INT16                                     sAmpCorrThreshold;
    VOS_INT16                                     sDcCorrThreshold;
}NV_GSM_TX_IQ_MISMATCH_CAL_PARA_STRU;

typedef struct
{
    VOS_INT16                               NV_GSM850_RX_AGC_GAIN_DEFAULT[8];
}NV_GSM850_RX_AGC_GAIN_DEFAULT_STRU;

typedef struct
{
    VOS_UINT16                                     usPaGainValidCnt;    /*[0,4]*/
    VOS_UINT16                                     ausPaGain[4];
}NV_GSM850_LINEAR_PA_GAIN_DEFAULT_STRU;


typedef struct
{
    VOS_UINT16                                     usPaGainValidCnt;    /*[0,4]*/
    VOS_UINT16                                     ausPaGain[4];
}NV_EDGE850_LINEAR_PA_GAIN_DEFAULT_STRU;

typedef struct
{
    VOS_INT16                               NV_GSM900_RX_AGC_GAIN_DEFAULT[8];
}NV_GSM900_RX_AGC_GAIN_DEFAULT_STRU;

typedef struct
{
    VOS_UINT16                                     usPaGainValidCnt;    /*[0,4]*/
    VOS_UINT16                                     ausPaGain[4];
}NV_GSM900_LINEAR_PA_GAIN_DEFAULT_STRU;

typedef struct
{
    VOS_UINT16                                     usPaGainValidCnt;    /*[0,4]*/
    VOS_UINT16                                     ausPaGain[4];
}NV_EDGE1900_LINEAR_PA_GAIN_DEFAULT_STRU;

typedef struct
{
    VOS_UINT16                                     usPaGainValidCnt;    /*[0,4]*/
    VOS_UINT16                                     ausPaGain[4];
}NV_PCS1900_LINEAR_PA_GAIN_DEFAULT_STRU;

typedef struct
{
    VOS_INT16                               NV_PCS1900_RX_AGC_GAIN_DEFAULT[8];
}NV_PCS1900_RX_AGC_GAIN_DEFAULT_STRU;

typedef struct
{
    VOS_INT16                               NV_PCS1900_RX_AGC_GAIN_DEFAULT[8];
}NV_PCS1900_RX_AGC_GAIN_DEFAULT_STRU;

typedef struct
{
    VOS_UINT16                                     usPaGainValidCnt;    /*[0,4]*/
    VOS_UINT16                                     ausPaGain[4];
}NV_DCS1800_LINEAR_PA_GAIN_DEFAULT_STRU;


typedef struct
{
    VOS_INT16                               NV_DCS1800_RX_AGC_GAIN_DEFAULT[8];
}NV_DCS1800_RX_AGC_GAIN_DEFAULT_STRU;

typedef struct
{
    VOS_UINT16                                     usPaGainValidCnt;    /*[0,4]*/
    VOS_UINT16                                     ausPaGain[4];
}NV_EDGE900_LINEAR_PA_GAIN_DEFAULT_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasNvInterface.h */
