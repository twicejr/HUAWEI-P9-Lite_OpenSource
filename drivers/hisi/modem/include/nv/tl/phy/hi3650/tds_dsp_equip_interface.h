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
#define TDS_TX_LEVEL_6362_NUM   (20)

#define TDS_PA_LEVEL_NUM		(3)
#define TDS_TX_CAL_POINT_NUM	(5)
#define TDS_BBGAIN_NUM_PER_RFGAIN (2)
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
    INT16 sPaTempComp[TDS_PA_LEVEL_NUM][TDS_EQUIP_TEMP_NUM];
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
    INT16  asComp[TDS_PA_LEVEL_NUM][TDS_EQUIP_TEMP_NUM];
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
    UINT16 usFreqNum;
    UINT16 usRes;
    UINT16 ausTxCalFreqList[TDS_RF_TX_FREQ_NUM];           /*TX校准频点，由低到高放置*/
    INT16  asTxCalCompListWired[TDS_RF_TX_FREQ_NUM];       /*TX有线频率补偿，实验室填写 默认全0，1/8db*/
    INT16  asTxCalCompListWireless[TDS_RF_TX_FREQ_NUM];    /*TX无线频率补偿，实验室填写 默认全0，1/8db*/
}TDS_TX_CAL_LIST_STRU;
typedef struct
{
    INT16  asPaDiff[TDS_PA_LEVEL_NUM];/*pa中低档位和高档位的功率差，第一个值填0  如 0 -5 -10*/
    UINT16 usRes;
    INT16  asRfDefaultPower[TDS_TX_LEVEL_6362_NUM][TDS_BBGAIN_NUM_PER_RFGAIN];
}TDS_DEFAULT_POW_TABLE_STRU;

typedef struct
{
    INT16 sMaxPow;
    INT16 sMinPow;
}TDS_NV_TX_APC_GAIN_STATUS_POW;
typedef struct
{
    TDS_NV_TX_APC_GAIN_STATUS_POW astTxPaPower[TDS_PA_LEVEL_NUM][TDS_TX_LEVEL_6362_NUM];
}TDS_NV_TX_CAL_RESULT_TABLE_STRU;
typedef struct
{
    UINT16  ausGainNumsNeedCalEachPaLevel[TDS_PA_LEVEL_NUM];/*每个pa档位需要校准rfgain 的个数*/
    UINT16  sCtDbbValue;
    UINT16  ausLteApcTable[TDS_TX_LEVEL_6362_NUM][TDS_BBGAIN_NUM_PER_RFGAIN];
}TDS_APC_TABLE_STRU;
typedef struct
{
    INT16  ssPhyHkadcCh;
    INT16  ssRsv;
}TDS_PA_TEMP_DET_CHANNEL_STRU;
typedef struct
{
    TDS_PA_LEVEL_THRE_STRU  stPaThre;
	TDS_TX_CAL_LIST_STRU                stTxCalFreqListLab;   /*校准频点列表*/
    TDS_APC_TABLE_STRU                  stApcTableLab;        /*发射功率控制字表*/
    TDS_DEFAULT_POW_TABLE_STRU          stTxDefaultPowLab;    /*默认发射功率，做发射判决门限使用*/
    TDS_RF_TXIQ_CAL_STRU stTxiqCal;
    TDS_TX_RF_FREQ_COMP_STRU            stFreqCompFac;         /*频率补偿表*/
    TDS_TX_PA_TEMP_COMP                 stTempCompFac;         /*温度补偿表*/
    TDS_NV_TX_CAL_RESULT_TABLE_STRU     stTXCalResultFac;      /*发射功率校准结果*/
    TDS_TX_RF_BB_ATT_STRU               stBbAtt;
    TDS_PA_TEMP_DET_CHANNEL_STRU        stPaTempDetCh;
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
