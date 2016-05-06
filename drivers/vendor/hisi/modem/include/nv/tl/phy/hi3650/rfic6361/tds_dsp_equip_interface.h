#ifndef  ___TDS_ct_nv_H____
#define ___TDS_ct_nv_H____

//#include "type_define.h"

#define TDS_RF_RX_FREQ_NUM    (32)
#define TDS_RF_TX_FREQ_NUM    (32)
#define TDS_EQUIP_TEMP_NUM    (32)

#define TDS_RF_COMMON_TEMP_NUM  (32)

 /** TDS RX档位数量 **/
#define TDS_RX_LEVEL_NUM        (8)
#define TDS_TX_LEVEL_NUM         (16)

#define TDS_PA_LEVEL_NUM		(3)
#define TDS_TX_CAL_POINT_NUM	(5)

/** 为装备共享结构体  **/
typedef struct
{
    INT16 asAgcTblNoBlock[TDS_RX_LEVEL_NUM];
    INT16 asAgcTblBlock[TDS_RX_LEVEL_NUM];
}TDS_RF_AGC_PARA_STRU;


typedef struct 
{
    TDS_RF_AGC_PARA_STRU stRfAgcCodePara; /*AGC控制字*/
    TDS_RF_AGC_PARA_STRU stRfAgcUpThrGain; /*AGC升档门限*/
    TDS_RF_AGC_PARA_STRU stRfAgcDownThrGain; /*AGC降档门限*/
    TDS_RF_AGC_PARA_STRU stRfAgcTotalGain; /*AGC总增益*/
}TDS_AGC_BAND_PARA_STRU;



typedef struct 
{
    UINT16 usCompDCI[32];
    UINT16 usCompDCQ[32];
}TDS_DCOC_CAL_STRU;


typedef struct 
{
    INT16  sAmplitude;
    INT16  sPhase;
    INT16  sDCI;
    INT16  sDCQ;
}TDS_RF_TXIQ_CAL_STRU;


typedef struct 
{
    INT16 sFreqComp[TDS_RF_TX_FREQ_NUM];
}TDS_TX_RF_FREQ_COMP_STRU;
typedef struct 
{
    INT16 sPaTempComp[3][32];
}TDS_TX_PA_TEMP_COMP;
typedef struct 
{
    UINT16 usAttenTable[60];
}TDS_TX_ATTEN_TABLE;
typedef struct 
{
    UINT16 usPowerVoltage[3];
}TDS_TX_POWERDET_VOLTAGE;

typedef struct 
{
    UINT16      usFreqList[TDS_RF_RX_FREQ_NUM];            /*Rx频率校准表*/
    UINT16      rsd;
    UINT16      usFreqNum;
}TDS_RX_CAL_FREQ_STRU;
    
typedef struct 
{
    INT16 asRxFreqComp[TDS_RX_LEVEL_NUM][TDS_RF_RX_FREQ_NUM];
}TDS_AGC_FREQ_COMP_UNIT_STRU;
typedef struct 
{
    TDS_AGC_FREQ_COMP_UNIT_STRU stNoBlk;
    TDS_AGC_FREQ_COMP_UNIT_STRU stBlk;
}TDS_AGC_FREQ_COMP_STRU;
    
typedef struct 
{
    INT16 asRxTempCmpVal[TDS_EQUIP_TEMP_NUM];
}TDS_AGC_TEMP_COMP_STRU;

    
typedef struct
{
    TDS_RX_CAL_FREQ_STRU stRxFreq;
    TDS_AGC_FREQ_COMP_STRU stFreqComp;
    TDS_AGC_TEMP_COMP_STRU stTempComp;
    TDS_AGC_BAND_PARA_STRU   stAgcTable;        /*agc NV项 */
    TDS_DCOC_CAL_STRU stDcoc;
}TDS_BAND_RXPATH_PARA_STRU;
typedef struct 
{
    UINT16 usFreqList[TDS_RF_TX_FREQ_NUM];
    UINT16 rsd;
    UINT16 usFreqNum;
}TDS_TX_CAL_FREQ_STRU;

typedef struct
{
    INT16 usPaDiff[4];
}TDS_PA_POWER_DIFFERENCE;

typedef struct
{
	INT16 sMaxAtt[TDS_TX_LEVEL_NUM];
}TDS_TX_RF_BB_MAX_ATT_STRU;
	

typedef struct 
{
    INT16 sGainStatus[TDS_TX_LEVEL_NUM];
}TDS_TX_APC_GAIN_ITEM_STRU;
typedef struct 
{
	TDS_TX_APC_GAIN_ITEM_STRU astGainITem[3];
}TDS_TX_APC_GAIN_STRU;

typedef struct 
{
    UINT16 usBB0DBAllowedFlg;
    INT16 sMaxBBAttVal;
    INT16 sMaxPower;
    INT16 sMinNodeBRscp;
}TDS_TX_RF_BB_ATT_STRU;


typedef struct 
{
    UINT16 usBias[TDS_TX_LEVEL_NUM];
}TDS_TX_RF_BIAS_STRU;

typedef struct 
{
    INT16 sFreqComp[TDS_RF_TX_FREQ_NUM];
}TDS_TX_FREQ_COMP_STRU;
typedef struct
{
    INT16 sHigh2MidThre;
    INT16 sMid2HighThre;
    INT16 sMid2LowThre;
    INT16 sLow2MidThre;
}TDS_PA_LEVEL_THRE_STRU;
typedef struct
{
    INT16  asComp[TDS_TX_LEVEL_NUM][TDS_EQUIP_TEMP_NUM];
}TDS_TX_TEMP_COMP_STRU;

typedef struct
{
	INT16 asBBAtt[TDS_TX_CAL_POINT_NUM];
	INT16 sNum;
}TDS_TX_CAL_BB_ATT_STRU;

typedef struct
{
	INT16 asTxCalBB[TDS_TX_CAL_POINT_NUM];
}TDS_TX_CAL_GAIN_STRU;

typedef struct
{
	TDS_TX_CAL_GAIN_STRU astTxCalGain[TDS_TX_LEVEL_NUM];
}TDS_TX_CAL_PA_STRU;

typedef struct
{
	TDS_TX_CAL_PA_STRU astTxCalPa[TDS_PA_LEVEL_NUM];
}TDS_TX_CAL_PA_GAIN_BB_STRU;

typedef struct
{
    TDS_TX_CAL_FREQ_STRU stTxFreq;
    TDS_TX_TEMP_COMP_STRU stTempComp;
    TDS_PA_LEVEL_THRE_STRU  stPaThre;
    TDS_TX_FREQ_COMP_STRU stFreqComp;
	TDS_TX_RF_BB_MAX_ATT_STRU stBbMaxAtt;
    TDS_PA_POWER_DIFFERENCE stPaDiff;
	TDS_TX_APC_GAIN_ITEM_STRU stItemGain;
    TDS_TX_APC_GAIN_STRU stGain;
    TDS_TX_RF_BB_ATT_STRU stBbAtt;
    TDS_TX_RF_BIAS_STRU stBias;
    TDS_RF_TXIQ_CAL_STRU stTxiqCal;
	TDS_TX_CAL_PA_GAIN_BB_STRU stTxCal;
	TDS_TX_CAL_BB_ATT_STRU stTxCalBBAtt;
	TDS_TX_CAL_FREQ_STRU stPaTxFreq;
	TDS_TX_FREQ_COMP_STRU stPaMidFreqComp;
	TDS_TX_FREQ_COMP_STRU stPaLowFreqComp;
}TDS_BAND_TXPATH_PARA_STRU;
typedef struct 
{
    UINT16 ausTempSensor[TDS_RF_COMMON_TEMP_NUM];
    UINT16 rsd;
    UINT16 usTempNum;
}TDS_TEMPERATURE_SENSOR_STRU;


typedef struct
{
    TDS_TEMPERATURE_SENSOR_STRU stSensor;
}TDS_BAND_COMMON_PARA_STRU;


#endif /* ___TDS_ct_nv_H____ */
