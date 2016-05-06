/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ToolNvInterface.h
  Description     : ToolNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __TOOLNVINTERFACE_H__
#define __TOOLNVINTERFACE_H__

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
#define GSM_RX_AGC_GAIN_NUM			      (8)
#define W_RX_NOBLOCK_AGC_GAIN_MAX_COUNT   (8)
#define W_RX_BLOCK_AGC_GAIN_MAX_COUNT     (8)
#define WCDMA_PA_MODE_CNT                ((PA_MODE_BUTT) - (PA_MODE_HIGH))
#define W_PA_CNT						  (3)
#define NV_GSM_LINEAR_PA_GAIN_NUM		  (4)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/* W PA模式 */
enum  W_TX_PA_MODE_ENUM
{
    PA_MODE_AUTO  = 0,
    PA_MODE_HIGH  = 1,
    PA_MODE_MID   = 2,
    PA_MODE_LOW   = 3,
    PA_MODE_BUTT  = 4
};

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           参数设置消息结构                                 *
*                                                                            *
******************************************************************************/

//Tcxo Cal
/*****************************************************************************
 NV名	   : NV_XO_INIT_FREQUENCY_DEFAULT
 结构体名  : XO_AFC_FREQERR_DEFAULT_STRU
 结构说明  : XO校准门限值
*****************************************************************************/
typedef struct
{
    INT16                   sInitAfc;
    UINT16                  usFreqErrThreshold;
    INT16		    sAfcLowerLimit;
    INT16		    sAfcUpperLimit;
}XO_AFC_FREQERR_DEFAULT_STRU;

/*****************************************************************************
 NV名	   : NV_DCXO_C_TRIM_DEFAULT
 结构体名  : XO_AFC_FREQERR_DEFAULT_STRU
 结构说明  : C_TRIM的初始值
*****************************************************************************/
typedef struct
{
    INT16                   sInitCfix;
    UINT16                  usFreqErrThreshold; 			   /* 0.1ppm */
    UINT16		    usCfixLowerLimit;
    UINT16		    usCfixUpperLimit;
}DCXO_C_TRIM_DEFAULT_STRU;


//W Trx Cal
/*****************************************************************************
 NV名	   : NV_DXCO_C2_FIX
 结构体名  : DXCO_C2_FIX_DEFAULT
 结构说明  : C2 校准参数
*****************************************************************************/
typedef struct
{
	UINT16				usC2fixDefault;
	UINT16 				usC2fixLowerLimit;
	UINT16 				usC2fixUpperLimit;
	UINT16 				usC2fixFactoryCal; //0表示不需要产线校准,其它表示需要
}DXCO_C2_FIX_DEFAULT;
//W Trx Cal
/*****************************************************************************
 NV名	   : NV_W_TX_APC_CAL_PARA
 结构体名  : NV_W_TX_APC_CAL_PARA_STRU
 结构说明  : Apc 校准参数
*****************************************************************************/
typedef struct
{
    INT16   sBbGainCalUpperLimit10th;
    INT16   sBbGainCalLowerLimit10th;
    INT16   sBbGainCalExtend10th;
    INT16   sReserved[3];
}NV_W_TX_APC_CAL_PARA_STRU;

typedef NV_W_TX_APC_CAL_PARA_STRU NV_CDMA_TX_APC_CAL_PARA_STRU;

//W APT Comp Correction
/*****************************************************************************
 NV名	   : NV_W_TX_PA_APT_COMP_CORRECTION
 结构体名  : NV_W_TX_APT_COMP_CORRECTION_STRU
 结构说明  : Apt补偿PA Gain mask
*****************************************************************************/
typedef struct
{
    UINT32 ulGainMask;
}NV_W_TX_APT_COMP_CORRECTION_STRU;

//RFIC Ctrl mask
/*****************************************************************************
 NV名	   : NV_W_TX_RFIC_CTRL_MASK
 结构体名  : NV_W_TX_RFIC_CTRL_MASK_STRU
 结构说明  : RFIC控制mask
*****************************************************************************/
typedef struct 
{
    UINT32  ulRfGainMask;       // Consist of Vdd sel, Pmax gain, RF gain and RF bias
    UINT32  ulBbGainMask;       // Consist of RF BB gain
}NV_W_TX_RFIC_CTRL_MASK_STRU;


/*****************************************************************************
 NV名	   : MAX_BB_GAIN_DBB_ATTEN_STRU
 结构体名  : MAX_BB_GAIN_DBB_ATTEN_STRU
 结构说明  : Max bb gain Dbb Atten
*****************************************************************************/
typedef struct
{
    UINT8  ucMaxRfBbGainIndex;
    INT8   cMaxDbbAtten;	
}MAX_BB_GAIN_DBB_ATTEN_STRU;

/*****************************************************************************
 NV名	   : NV_W_TX_APC_GENERATION_RULE_ANY_PA_STRU
 结构体名  : NV_W_TX_APC_GENERATION_RULE_ANY_PA_STRU
 结构说明  : Apc Generation Rule
*****************************************************************************/
typedef struct
{
    UINT16 usRfGainLimit;
    UINT16 usValidCnt;
    MAX_BB_GAIN_DBB_ATTEN_STRU astData[20];
}NV_W_TX_APC_GENERATION_RULE_ANY_PA_STRU;

/*****************************************************************************
 NV名	   : NV_W_TX_APC_GENERATION_RULE
 结构体名  : NV_W_TX_APC_GENERATION_RULE_STRU
 结构说明  : Apc Generation Rule
*****************************************************************************/
typedef struct
{
    NV_W_TX_APC_GENERATION_RULE_ANY_PA_STRU astAnyPaApcRule[W_PA_CNT];
}NV_W_TX_APC_GENERATION_RULE_STRU;

typedef NV_W_TX_APC_GENERATION_RULE_STRU NV_CDMA_TX_APC_GENERATION_RULE_STRU;

/*****************************************************************************
 NV名	   : NV_W_TX_RF_BIAS_INDEX_(VOICE_MODE)_B*
 结构体名  : NV_W_TX_RF_BIAS_INDEX_STRU
 结构说明  : Rf Bias Index
*****************************************************************************/
typedef struct
{
    UINT32  ulValidCount;
    UINT16  ausRfBiasIndex[20];
}NV_W_TX_RF_BIAS_INDEX_STRU;

typedef NV_W_TX_RF_BIAS_INDEX_STRU NV_CDMA_TX_RF_BIAS_INDEX_STRU;

/*****************************************************************************
 NV名	   : NV_W_RX_AGC_GAIN_CAL_PARA
 结构体名  : NV_W_RX_AGC_GAIN_CAL_PARA_STRU
 结构说明  : Agc Gain Cal Para
*****************************************************************************/
typedef struct
{
    INT16   asNoBlockIor[W_RX_NOBLOCK_AGC_GAIN_MAX_COUNT];
    INT16   asBlockIor[W_RX_BLOCK_AGC_GAIN_MAX_COUNT];
}NV_W_RX_AGC_GAIN_CAL_PARA_STRU;

typedef NV_W_RX_AGC_GAIN_CAL_PARA_STRU NV_CDMA_RX_AGC_GAIN_CAL_PARA_STRU;

/*****************************************************************************
 NV名	   : NV_WG_RX_AGC_GAIN_CAL_THRESHOLD
 结构体名  : NV_WG_RX_AGC_GAIN_CAL_THRESHOLD_STRU
 结构说明  : Rx Agc Cal Threshold
*****************************************************************************/
typedef struct
{
    INT16   sUpLimit;
    INT16   sLowLimit;
}NV_WG_RX_AGC_GAIN_CAL_THRESHOLD_STRU;


//W Pd Cal
/*****************************************************************************
 NV名	   : NV_W_TX_HDET_CAL_PARA_B*
 结构体名  : NV_W_PD_CAL_PARA_ANYBAND_STRU
 结构说明  : Pd Cal Para
*****************************************************************************/
typedef struct
{
    INT16   sMinPowerLmt10th;
    UINT16  usMinPdLmt;
    INT16   sMaxPowerLmt10th;
    UINT16  usMaxPdLmt;
}NV_W_PD_CAL_PARA_ANYBAND_STRU

typedef NV_W_PD_CAL_PARA_ANYBAND_STRU NV_CDMA_PD_CAL_PARA_ANYBAND_STRU;


/*****************************************************************************
 NV名	   : NV_W_HDET_VGA_CAL_LIST
 结构体名  : NV_W_HDET_VGA_CAL_LIST_STRU
 结构说明  : Pd Vga Cal List
*****************************************************************************/
typedef struct
{
    UINT32  ulValidCount;
    UINT16  usPdVga[16];
}NV_W_HDET_VGA_CAL_LIST_STRU;

typedef NV_W_HDET_VGA_CAL_LIST_STRU NV_CDMA_HDET_VGA_CAL_LIST_STRU;

/*****************************************************************************
 NV名	   : NV_W_HDET_VGA_THRESHOLD
 结构体名  : NV_W_HDET_VGA_THRESHOLD_STRU
 结构说明  : Pd VGA THRESHOLD
*****************************************************************************/
typedef struct
{
	UINT16 		usVgaThreshold;
}NV_W_HDET_VGA_THRESHOLD_STRU;

typedef NV_W_HDET_VGA_THRESHOLD_STRU NV_CDMA_HDET_VGA_THRESHOLD_STRU;

/*****************************************************************************
 NV名	   : NV_W_TX_HDET_VGA_B*
 结构体名  : NV_W_HDET_VGA_STRU
 结构说明  : Pd VGA
*****************************************************************************/
typedef struct
{
    UINT16      usPdVga;
}NV_W_HDET_VGA_STRU;

/*****************************************************************************
 NV名	   : NV_W_HDET_HKADC_PARA
 结构体名  : NV_W_HDET_HKADC_PARA_STRU
 结构说明  : Pd Hkadc Para
*****************************************************************************/
typedef struct
{
    UINT16  usRefVolt;
    UINT16  usBitWidth;
}NV_W_HDET_HKADC_PARA_STRU;

typedef NV_W_HDET_HKADC_PARA_STRU NV_CDMA_HDET_HKADC_PARA_STRU;

/*****************************************************************************
 NV名	   : NV_W_HDET_DCOFFSET_THRESHOLD
 结构体名  : NV_W_HDET_DCOFFSET_THRESHOLD_STRU
 结构说明  : Pd DcOffset Threshold
*****************************************************************************/
typedef struct
{
    INT16  sTarget;
    INT16  sLowerLimit;
    INT16  sUpperLimit;
}NV_W_HDET_DCOFFSET_THRESHOLD_STRU;

typedef NV_W_HDET_DCOFFSET_THRESHOLD_STRU NV_CDMA_HDET_DCOFFSET_THRESHOLD_STRU;

/*****************************************************************************
 NV名	   : NV_W_HDET_DCOFFSET_CAL_LIST
 结构体名  : NV_W_HDET_DCOFFSET_CAL_LIST_STRU
 结构说明  : Pd DcOffset Para
*****************************************************************************/
typedef struct
{
    UINT16   usMaxDcoffset;
    UINT16   usMinDcoffset;
}NV_W_HDET_DCOFFSET_CAL_LIST_STRU;

typedef NV_W_HDET_DCOFFSET_CAL_LIST_STRU NV_CDMA_HDET_DCOFFSET_CAL_LIST_STRU;

/*****************************************************************************
 NV名	   : NV_W_HDET_VGA_THRESHOLD
 结构体名  : NV_W_HDET_DCOFFSET_STRU
 结构说明  : Pd DcOffset
*****************************************************************************/
typedef struct
{
    UINT16   usPdDcOffset;
}NV_W_HDET_DCOFFSET_STRU;

//W FreqComp Cal
/*****************************************************************************
 NV名	   : NV_WG_RX_FREQ_COMP_CAL_THRESHOLD
 结构体名  : NV_WG_RX_FREQ_COMP_CAL_THRESHOLD_STRU
 结构说明  : Rx Freq Comp Cal Threshold
*****************************************************************************/
typedef struct
{
    INT16   sUpLimit;
    INT16   sLowLimit;
}NV_WG_RX_FREQ_COMP_CAL_THRESHOLD_STRU;


//W APT Cal


/*****************************************************************************
 NV名	   : NV_W_TX_APT_CAL_PARA_B*
 结构体名  : APT_CAL_PARA_ITEM_STRU
 结构说明  : Pa APT
 *****************************************************************************/
typedef struct
{
    INT16      sTargetAclr10th;
    INT16      sAclrMultiplierUnit;
    INT16      sAclrDividerUnit;
    INT16      sPowerMultiplierUnit;
    INT16      sPowerDividerUnit;
    INT16      sVoltDeltaLowerLimit;    
    INT16      sVoltDeltaUpperLimit;
}APT_CAL_PARA_ITEM_STRU;

/*****************************************************************************
 NV名	   : NV_W_TX_APT_CAL_PARA_B*
 结构体名  : NV_W_TX_APT_CAL_PARA_STRU
 结构说明  : Pa APT
 *****************************************************************************/
typedef struct
{
    UINT16                 usAptCalMask;
    APT_CAL_PARA_ITEM_STRU astAptCalPara[3];
}NV_W_TX_APT_CAL_PARA_STRU;

typedef NV_W_TX_APT_CAL_PARA_STRU NV_CDMA_TX_APT_CAL_PARA_STRU;

//GSM TX cal
/*****************************************************************************
 NV名	   : NV_GSM*_TX_SWEEP_DAC_RANGE
 结构体名  : NV_GSM_BAND_CTRL_VOLT_THRESHOLD
 结构说明  : GSM Range
 *****************************************************************************/
typedef struct 
{
    UINT16  usMaxDac;
    UINT16  usMultiSlotsDac;
    UINT16  usMinDac;
}NV_GSM_BAND_CTRL_VOLT_THRESHOLD;

/*****************************************************************************
 NV名	   : NV_GSM_RX_AGC_GAIN_VALID_RANGE
 结构体名  : NV_GSM_RX_AGC_GAIN_VALID_RANGE_STRU
 结构说明  : Gsm Rx agc gain Range
*****************************************************************************/

typedef struct
{
    UINT16  usGainRange;
}NV_GSM_RX_AGC_GAIN_VALID_RANGE_STRU;


/*****************************************************************************
 NV名	   : NV_GSM_RX_AGC_GAIN_CAL_PARA
 结构体名  : NV_GSM_RX_GAIN_CTRL_PARA_STRU
 结构说明  : Gsm Rx Agc Gain Ctrl
*****************************************************************************/
typedef struct
{
    INT16  sAgclor[8];
}NV_GSM_RX_GAIN_CTRL_PARA_STRU;

//Edge Tx Cal
/*****************************************************************************
 NV名	   : NV_EDGE_TX_RF_GAIN_CTRL
 结构体名  : NV_EDGE_RF_GAIN_CTRL_STRU
 结构说明  : Edge RF Gain Ctrl
*****************************************************************************/
typedef struct
{
    UINT32  ulValidCount;
    UINT16  ausRfGainCtrl[20];
}NV_EDGE_RF_GAIN_CTRL_STRU;

/*****************************************************************************
 NV名	   : NV_EDGE*_TX_RF_BIAS_INDEX
 结构体名  : NV_EDGE_RF_GAIN_CTRL_STRU
 结构说明  : Edge RF Bias Index
*****************************************************************************/
typedef struct
{
	UINT32  ulValidCount;
	UINT16	ausRfBaisIndex[20];
}NV_EDGE_RF_BASI_INDEX_STRU;

/*****************************************************************************
 NV名	   : NV_EDGE*_TX_RF_BIAS
 结构体名  : NV_EDGE_RF_BIAS_STUR
 结构说明  : Edge RF Bias
*****************************************************************************/
typedef struct  
{
	UINT32	ulValidCount;
	UINT16	ausRfBias[16];

}NV_EDGE_RF_BIAS_STUR;

/*****************************************************************************
 NV名	   : NV_EDGE_TX_RFIC_BB_GAIN_TABLE
 结构体名  : BB_GAIN_CTRL_VS_ATTEN_STRU
 结构说明  : BB Gain Table
*****************************************************************************/
typedef struct 
{
	UINT16   usBbGainCtrl;
	INT16	 sBbAtten10th;
}BB_GAIN_CTRL_VS_ATTEN_STRU;

/*****************************************************************************
 NV名	   : NV_EDGE_TX_RFIC_BB_GAIN_TABLE
 结构体名  : NV_EDGE_BB_GAIN_STRU
 结构说明  : Edge BB Gain
*****************************************************************************/
typedef struct
{
	UINT32  ulValidCount;
	BB_GAIN_CTRL_VS_ATTEN_STRU astBbGain[32];
}NV_EDGE_BB_GAIN_STRU;

/*****************************************************************************
 NV名	   : NV_EDGE*_TX_APC_GENERATION_RULE
 结构体名  : NV_EDGE_TX_APC_GENERATION_RULE
 结构说明  : Edge Tx Apc Generation Rule
*****************************************************************************/
typedef struct
{
    INT16  sDbbAtten10thAllowed;
    UINT32 ulValidCnt;
    UINT16 ausRfBbGainIndex[20];
}NV_EDGE_TX_APC_GENERATION_RULE;

/*****************************************************************************
 NV名	   : NV_EDGE*_TX_RF_GAIN_ATTEN
 结构体名  : NV_EDGE_RF_GAIN_ATTEN_STRU
 结构说明  : Edge RF Gain Atten
*****************************************************************************/
typedef struct
{
    UINT32	ulValidCount;
    INT16	asRfAtten10th[20];
}NV_EDGE_RF_GAIN_ATTEN_STRU;


/*****************************************************************************
 NV名	   : NV_EDGE_TX_APC_CAL_PARA
 结构体名  : NV_EDGE_TX_APC_CAL_PARA_STRU
 结构说明  : Apc Cal Para
*****************************************************************************/
typedef struct
{
     INT16	sGainAtten10th;
}NV_EDGE_TX_APC_CAL_PARA_STRU;

/*****************************************************************************
 NV名	   : NV_GSM*_RX_AGC_GAIN_DEFAULT
 结构体名  : NV_GSM_ANY_BAND_RX_AGC_GAIN_STRU
 结构说明  : Apc Cal Para
*****************************************************************************/
typedef struct
{
    INT16	asPower8th[GSM_RX_AGC_GAIN_NUM];
}NV_GSM_ANY_BAND_RX_AGC_GAIN_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_LINEAR_PA_GAIN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 线性PA的增益
*****************************************************************************/
typedef struct
{
    UINT16                          usNumber;
    INT16                           shwGain[NV_GSM_LINEAR_PA_GAIN_NUM];
}NV_EDGE_LINEAR_PA_GAIN_STRU;


/*****************************************************************************
 NV名	   : NV_GSM*_PA_PRECHG_CAL_THRESHOLD
 结构体名  : NV_GSM_BAND_PA_PRECHG_CAL_THRESHOLD_STRU
 结构说明  : Gsm Pa Precharge
*****************************************************************************/
typedef struct
{
    INT16	usNvIdGsmPaPrechargeThreshold;
}NV_GSM_BAND_PA_PRECHG_CAL_THRESHOLD_STRU;


/*****************************************************************************
 NV名	   : NV_W_TX_PA_GAIN_DEFAULT_B*
 结构体名  : NV_W_TX_PA_GAIN_STRU
 结构说明  : Pa Gain
*****************************************************************************/
typedef struct
{
    INT16  asPaGain10th[W_PA_CNT];
}NV_W_TX_PA_GAIN_STRU;

typedef NV_W_TX_PA_GAIN_STRU NV_CDMA_TX_PA_GAIN_STRU;


/*****************************************************************************
 NV名	   : NV_W_TX_RF_GAIN_ATTEN_HIGH(MID,LOW)_GAIN_(VOICE_MODE)_B*
 结构体名  : NV_W_TX_RF_GAIN_ATTEN_STRU
 结构说明  : Rf Gain Atten
*****************************************************************************/
typedef struct
{
    UINT32  ulValidCount;
    INT16   asRfAtten10th[20];
}NV_W_TX_RF_GAIN_ATTEN_STRU;

typedef NV_W_TX_RF_GAIN_ATTEN_STRU NV_CDMA_TX_RF_GAIN_ATTEN_STRU;

/*****************************************************************************
 NV名	   : NV_W_TX_PA_APT_TABLE(COMP)_DEFAULT_B*
 结构体名  : W_APT_STRU
 结构说明  : APT
*****************************************************************************/
typedef struct
{
	INT16      asPwr10th;
	UINT16     usVcc;
	UINT16	   usBias1;
	UINT16	   usBias2;
	UINT16	   usBias3;
}W_APT_STRU;
	
/*****************************************************************************
 NV名	   : NV_W_TX_PA_APT_TABLE(COMP)_DEFAULT_B*
 结构体名  : NV_W_TX_APT_TABLE_STRU
 结构说明  : APT
*****************************************************************************/
typedef struct
{
    UINT16      usAptStepMode;
    UINT16      ausValidCount[3];
    W_APT_STRU  astAptTable[96];
}NV_W_TX_APT_TABLE_STRU;

typedef NV_W_TX_APT_TABLE_STRU NV_CDMA_TX_APT_TABLE_STRU;

/*****************************************************************************
 NV名	   : NV_W_TX_PA_APT_TABLE(COMP)_DEFAULT_B*
 结构体名  : NV_W_TX_GAIN_APT_COMP_STRU
 结构说明  : APT COMP
*****************************************************************************/
typedef struct
{
    INT16  ashwAptComp[96];
}NV_W_TX_GAIN_APT_COMP_STRU;

typedef NV_W_TX_GAIN_APT_COMP_STRU NV_CDMA_TX_GAIN_APT_COMP_STRU;

/*****************************************************************************
 NV名	   : NV_GE_TX_LINEAR_PA_GAIN_CAL_PARA
 结构体名  : NV_GE_TX_LINEAR_PA_GAIN_CAL_PARA_STRU
 结构说明  : LINEAR PA GAIN PARA
*****************************************************************************/
typedef struct
{
    UINT16  usCalPcl[NV_GSM_LINEAR_PA_GAIN_NUM];
}NV_GE_TX_LINEAR_PA_GAIN_CAL_PARA_STRU;

/*****************************************************************************
 NV名	   : NV_GE_TX_LINEAR_APC_CAL
 结构体名  : NV_GE_TX_LINEAR_APC_CAL_STRU
 结构说明  : DBB默认衰减值
*****************************************************************************/
typedef struct
{
    INT16  sDbbAtten10th;
}NV_GE_TX_LINEAR_APC_CAL_STRU;


/*****************************************************************************
 NV名	   : NV_GSM_RX_IQ_MISMATCH_CAL_PARA
 结构体名  : NV_GSM_RX_IQ_MISMATCH_CAL_PARA_STRU
 结构说明  : 
*****************************************************************************/
typedef struct
{
    INT16   sRefIor10th;
    INT16   sAmpCorrThreshold;
    INT16   sPhsCorrThreshold;
}NV_GSM_RX_IQ_MISMATCH_CAL_PARA_STRU;


/*****************************************************************************
 NV名	   : NV_ET_COEFF_CAL_PARA_ANYBAND
 结构体名  : NV_ET_COEFF_CAL_PARA_ANYBAND_STRU
 结构说明  : ET Lut修正点校准功率
*****************************************************************************/
typedef struct
{
    UINT32  ulSampleCnt;
    INT16   asPower[8];
}NV_ET_COEFF_CAL_PARA_ANYBAND_STRU;

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
