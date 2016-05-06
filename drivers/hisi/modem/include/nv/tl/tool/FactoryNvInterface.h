#include "nv_struct_datatype_def.txt"
typedef struct
{
    VOS_UINT8 aucBSN[20]; // 以\0结束
}NV_ID_BOARD_BSN_STRU;

typedef struct
{
    VOS_UINT8 aucFacInfo[2][128]; // 以\0结束
}NV_ID_MANUF_INFO_STRU;

typedef struct
{
    VOS_UINT32 ulIMEIWrTimes;
}NV_ID_IMEI_WR_TIMES_STRU;

typedef struct
{
    VOS_UINT8 ucProvComp;
    VOS_UINT8 ucPlatInfo;
}NV_ID_PLAT_INFO_STRU;

typedef struct
{
    S8 auclProductModel[32]; // 以0结尾
}NV_ID_PRD_MODEL_STRU;

typedef struct
{
    S8 auclBoardModel[32]; // 以0结尾
}NV_ID_BOARD_MODEL_STRU;


typedef struct
{
    VOS_UINT32 ulSegNum;
    VOS_UINT32 aulStartMccMnc[20];
    VOS_UINT32 aulEndMccMnc[20];
}NV_ID_CS_SIM_LOCK_STRU;

typedef struct
{
    VOS_UINT32 ulSimLockFuncSwt; // 0为关，1为开
}NV_ID_CS_SIM_LOCK_FUNC_SWITCH_STRU;

typedef struct
{
    VOS_UINT32 ulPortLockPassLen;
    VOS_UINT8 aucPortLockPass[36]; // 最长32字节，以\0结尾
}NV_ID_PORT_LOCK_STRU;

typedef struct
{
    VOS_UINT8 aucPwd[8];
    VOS_UINT8 aucPermPwd[8];
    VOS_UINT32 ulLockFlag;
}NV_ID_SIMLOCK_PWD_STRU;

typedef struct
{
    VOS_UINT8 aucMagicNum[16];
}NV_ID_MAGIC_NUM_STRU;

typedef struct
{
    /* 动态TCXO高门限 */
    VOS_UINT16                          usVctcxoThdHigh;

    /* 动态TCXO值, UE上电时由HPA读取NV并配置DSP,UE上电开机进入连接态后从DSP获取有效值写入NV */
    VOS_UINT16                          usVctcxoDynamic;

       /* 动态TCXO取值是否有效标识, DSP可不用,0: 有效；其余无效，无效时usDynamicTcxo值无意义 */
    VOS_UINT16                          usVctcxoFlag;

    /* 动态TCXO功能是否使用开关, DSP可不用,修改后, 需要下电再上电才会生效
     0: 关闭, 关闭时usVctcxoDynamic取值usVctcxoInit1: 打开 */
    VOS_UINT16                          usVctcxoFuncSwitch;
}TCXO_DYNAMIC_CONFIG_STRU;

typedef struct
{
    VOS_UINT16 usVctcxoInit;
}NV_ID_TCXO_INIT_FREQ_STRU;


typedef struct
{
    VOS_UINT16 ausTempSensTab[12];
}NV_ID_TEMP_SENSOR_TABLE_STRU;

#if 0
typedef struct
{
    VOS_UINT16 usAntModemLoss[2];
}NV_ID_ANT_MODEM_LOSS_STRU;
#endif
typedef struct
{
    VOS_UINT16 ausCalibFreq[32];
}NV_ID_LTE_RX_CALIBRATION_FREQ_LIST_STRU;

typedef struct
{
    VOS_UINT32 aulRxAgcTableAnt1[128];
}NV_ID_LTE_RX_AGC_TABLE_ANT1_STRU;

typedef struct
{
    VOS_UINT32 aulRxAgcTableAnt2[128];
}NV_ID_LTE_RX_AGC_TABLE_ANT2_STRU;

typedef struct
{
    VOS_UINT8 aucRxAagcGainIdxTblAnt1[128];
}NV_ID_LTE_RX_AGCGAIN_INDEX_TABLE_ANT1_STRU;

typedef struct
{
    VOS_UINT8 aucRxAagcGainIdxTblAnt2[128];
}NV_ID_LTE_RX_AGCGAIN_INDEX_TABLE_ANT2_STRU;

typedef struct
{
    VOS_INT16 asRxAgcTabAnt1Err[128];
}NV_ID_LTE_RX_AGC_TABLE_ANT1_ERR_STRU;

typedef struct
{
    VOS_INT16 asRxAgcTabAnt2Err[128];
}NV_ID_LTE_RX_AGC_TABLE_ANT2_ERR_STRU;

typedef struct
{
    VOS_INT16 asLnaGain0FreqCompAnt1[16];
}NV_ID_LTE_LNAGAIN0_FREQ_COMP_ANT1_STRU;

typedef struct
{
    VOS_INT16 asLnaGain0FreqCompAnt2[16];
}NV_ID_LTE_LNAGAIN0_FREQ_COMP_ANT2_STRU;

typedef struct
{
    VOS_INT16 asLnaGain1FreqCompAnt1[16];
}NV_ID_LTE_LNAGAIN1_FREQ_COMP_ANT1_STRU;

typedef struct
{
    VOS_INT16 asLnaGain1FreqCompAnt2[16];
}NV_ID_LTE_LNAGAIN1_FREQ_COMP_ANT2_STRU;

typedef struct
{
    VOS_INT16 asLnaGain2FreqCompAnt1[16];
}NV_ID_LTE_LNAGAIN2_FREQ_COMP_ANT1_STRU;

typedef struct
{
    VOS_INT16 asLnaGain2FreqCompAnt2[16];
}NV_ID_LTE_LNAGAIN2_FREQ_COMP_ANT2_STRU;

typedef struct
{
    VOS_INT16 asLnaGain3FreqCompAnt1[16];
}NV_ID_LTE_LNAGAIN3_FREQ_COMP_ANT1_STRU;

typedef struct
{
    VOS_INT16 asLnaGain3FreqCompAnt2[16];
}NV_ID_LTE_LNAGAIN3_FREQ_COMP_ANT2_STRU;

typedef struct
{
    VOS_UINT16 ausTxCalibFreqList[32];
}NV_ID_LTE_TX_CALIBRATION_FREQ_LIST_STRU;

typedef struct
{
    VOS_INT16 sTxApcHighThrd;
}NV_ID_LTE_TX_APC_HIGHGAIN_THRESHHOLD_STRU;

typedef struct
{
    VOS_INT16 sTxApcLowThrd;
}LTE_TX_APC_LOWGAIN_THRESHHOLD_STRU;

typedef struct
{
    VOS_UINT16 ausTxApcHighGain[32];
}NV_ID_LTE_TX_APC_HIGHGAIN_TABLE_STRU;

typedef struct
{
    VOS_UINT16 ausTxApcLowGain[60];
}NV_ID_LTE_TX_APC_LOWGAIN_TABLE_STRU;

typedef struct
{
    VOS_INT16 asTxApcFreqCompHighGain[4][16];
}NV_ID_LTE_TX_APC_FREQ_COMP_HIGHGAIN_STRU;

typedef struct
{
    VOS_INT16 asTxApcFreqCompLowGain[4][16];
}NV_ID_LTE_TX_APC_FREQ_COMP_LOWGAIN_STRU;

typedef struct
{
    VOS_UINT16 usAdcOpenTime;
}NV_ID_ADC_OPEN_TIME_STRU;

typedef struct
{
    VOS_UINT16 usRficT1;
}NV_ID_RFIC_T1_STRU;
typedef struct
{
    VOS_UINT16 usRficT2;
}NV_ID_RFIC_T2_STRU;
typedef struct
{
    VOS_UINT16 usRficT3;
}NV_ID_RFIC_T3_STRU;

typedef struct
{
    VOS_UINT16 usRficT4_1_DOT_4;
    VOS_UINT16 usRficT4_3;
    VOS_UINT16 usRficT4_5;
    VOS_UINT16 usRficT4_10;
    VOS_UINT16 usRficT4_15;
    VOS_UINT16 usRficT4_20;
}NV_ID_RFIC_T4_STRU;

typedef struct
{
    VOS_UINT16 usRficT7;
}NV_ID_RFIC_T7_STRU;

typedef struct
{
    VOS_UINT16 usRficT8;
}NV_ID_RFIC_T8_STRU;

typedef struct
{
    VOS_UINT16 usRficT9;
}NV_ID_RFIC_T9_STRU;

typedef struct
{
    VOS_UINT16 usRficT10;
}NV_ID_RFIC_T10_STRU;

typedef struct
{
    VOS_UINT16 usPaOpenTime;
}NV_ID_PA_OPEN_TIME_STRU;


typedef struct
{
    VOS_UINT32 aulAagcLnaTh[7];
}NV_ID_AAGC_LNA_THRESHOLD_STRU;


typedef struct
 {
     VOS_UINT32 aulAagcLNAOffAddr[4];
 }NV_ID_AAGC_LNA_OFF_ADDR_STRU;


typedef struct
 {
     CHAR_T ulFacInfo0[128];
 }NV_ID_FACINFO_0_STRU;

typedef struct
 {
     CHAR_T ulFacInfo1[128];
 }NV_ID_FACINFO_1_STRU;

typedef struct
{
    CHAR_T    aucImei[16];
}NV_IMEI_STRU;

typedef struct
{
   UINT16 ausDbmToGainTblNormal[120];
}NV_DBM_TO_GAIN_TBL_NORM_STRU;

typedef struct
{
    UINT16 ausDbmToGainTblAcsBlk[128];
}NV_DBM_TO_GAIN_TBL_ACS_STRU;

typedef struct
{
    VOS_UINT16 ausTempSens[32];

}NV_TEMP_SENSOR_TABLE_STRU;


typedef struct
{
    VOS_INT16 asTxApcTempCompHighGain[20];
}NV_LTE_TX_APC_TEMP_COMP_HIGHGAIN_STRU;

typedef struct
{
    VOS_INT16 asTxApcTempCompLowGain[20];
}NV_LTE_TX_APC_TEMP_COMP_LOWGAIN_STRU;

typedef struct
{
    VOS_INT16 asLnaGainTmpComp[20];
}NV_LTE_LNAGAIN_TEMP_COMP_TABLE_STRU;

typedef struct
{
    VOS_INT16 asApcLevelComp[4];
}NV_LTE_APC_LEVEL_COMP_STRU;


typedef struct
{
    VOS_UINT32 aulRxAgcTableAnt[32];
}NV_ID_LTE_RX_AGC_TABLE_ANT_STRU;

typedef struct
{
    VOS_INT16 asAgcTempComp[32];
}NV_LTE_AGC_TEMP_COMP_TABLE_STRU;

typedef struct
{
    VOS_UINT16 ausIp2CalChan[8];
}NV_LTE_IP2_CAL_CHAN_STRU;

typedef struct
{
    VOS_UINT16 usIp2CalApccode;
}NV_ID_LTE_IP2_CAL_APCCODE_STRU;

typedef struct
{
    VOS_INT16 asIp2Cal[8][2];
}NV_ID_LTE_IP2_CAL_STRU;

typedef struct
{
    VOS_INT16 asAgcFreqCompAnt[8][32];
}NV_ID_LTE_AGC_FREQ_COMP_STRU;

typedef struct
{
    VOS_INT16 asTxApcGainThrd[4];
}NV_ID_LTE_TX_APC_GAIN_THRESHHOLD_STRU;


typedef struct
{
    VOS_INT16 asPaPower[4];
}NV_ID_LTE_PA_POWER_STRU;

typedef struct
{
    VOS_INT16 asTxApcTempComp[16][32];
}NV_ID_LTE_TX_APC_TEMP_COMP_STRU;


typedef struct
{
    VOS_UINT16  usDbbAtt;        /*DBB衰减1/8db为单位*/
    VOS_UINT16  usAbbAttWord;    /*ABB衰减控制字*/
}NV_APC_ATT_TABLE_STRU;

typedef struct
{
   NV_APC_ATT_TABLE_STRU stAttTable[88];
}NV_ID_LTE_APC_ATT_TABLE_STRU;


typedef struct
{
    VOS_INT16 asPaHighCalPwr[4];            /*PA高档校准功率值*/
}NV_ID_LTE_TX_CAL_HIGHGAIN_POWER_STRU;

typedef struct
{
    VOS_INT16 asPaMidCalPwr[4];            /*PA中档校准功率值*/
}NV_ID_LTE_TX_CAL_MIDGAIN_POWER_STRU;

typedef struct
{
    VOS_INT16 asPaLowCalPwr[10];            /*PA低档校准功率值*/
}NV_ID_LTE_TX_CAL_LOWGAIN_POWER_STRU;

typedef struct
{
    VOS_INT16 asTxFreqCmpHighVal[4][16];
}NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_STRU;

typedef struct
{
    VOS_INT16 asTxFreqCmpMidVal[4][16];
}NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_STRU;

typedef struct
{
    VOS_INT16 asTxFreqCmpLowVal[10][16];
}NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_STRU;

/*电池校准参数NV*/
typedef struct
{
    VOS_INT16 usMinValue;		/*最小电压值，预置值3400*/
    VOS_INT16 usMaxValue;		/*最大电压值，预置值4200*/
}NV_ID_VBAT_CALIBART_STRU;

typedef struct
{
    VOS_UINT32 ulTmmi;
}NV_ID_BOARD_TMMI_STRU;

typedef struct
{
    VOS_INT16 stTxPowerCmp[16];
}UL_APT_TX_CMP_STRU;

//AT^PLATFORM?
typedef struct
{
    U16_T usProvider;
    U16_T usSubPlatForm;
}AT_PLATFORM_NV_STRU;

typedef struct
{
    VOS_UINT8    aucWifiSsid[32];
}AT_V7_WIFI_SSID_STRU;

typedef struct
{
    VOS_UINT8    aucWifiWepKey1[32];
    VOS_UINT8    aucWifiWepKey2[32];
    VOS_UINT8    aucWifiWepKey3[32];
    VOS_UINT8    aucWifiWepKey4[32];
}AT_V7_WIFI_SEC_STRU;

typedef struct
{
    VOS_UINT8    aucwlKeys[32];
}AT_WIFI_WIWEP_STRU;

typedef struct
{
    AT_WIFI_WIWEP_STRU astWiWepInfo[4];
} AT_V7_WIFI_WEP_INFO_STRU;

typedef struct
{
    VOS_UINT32                  ulState;
    AT_V7_WIFI_SSID_STRU        stWifiSsid;
    AT_V7_WIFI_SEC_STRU         stWifiSec;
    AT_V7_WIFI_WEP_INFO_STRU    stWifiWep;
}AT_WIFI_CSDFLT_STRU;

typedef struct
{
    VOS_INT16 stTxPowerCmp[16];
}UL_APT_TX_CMP_STRU;

typedef struct
{
    UINT16 ausMprVal[4];
}NV_ID_LTE_TX_MPR_STRU;

typedef struct
{
    UINT16                      usRegionAVal;
    UINT16                      usRegionBVal;
    UINT16                      usRegionCVal;
    UINT16                      usReserved;
}UL_AMPR_STRU;

typedef struct
{
    UL_AMPR_STRU astAMprVal[6];
}NV_ID_LTE_TX_AMPR_STRU;

#if 0
typedef struct
{
    UINT16    usLowRbArea;         //带宽内最下端多少个RB内需要补偿
    UINT16    usHighRbArea;        //带宽内最上端多少个RB内需要补偿
    UINT16    usRbNum;             //小于多少个RB需要补偿
    INT16     sLowPosCmpVal;       //低RB位置补偿值
    INT16     sHighPosCmpVal;      //高RB位置补偿值
}NV_TX_RF_ABB_FILTER_CMP_STRU;

typedef struct
{
    NV_TX_RF_ABB_FILTER_CMP_STRU stBandWidthCmp[4]; //针对5 10 15 20M带宽补偿
}NV_TX_FILTER_CMP_STRU;
#endif

typedef struct
{
	UINT32 ulRegAddr;
    UINT32 ulValue;
	UINT32 ulEquipOnVal;
	UINT32 ulEquipOffVal;
}NV_DSP_PA_CFG_STRU;


typedef struct
{
    U32_T UdpValue;
}NV_UDP_TYPE_STRU;

typedef struct
{
    UINT32 ulAmprValNS05;
}NV_ID_LTE_TX_AMPR_NS05_STRU;

typedef struct
{
    UINT16 usAmprValNS09[2];
}NV_ID_LTE_TX_AMPR_NS09_STRU;
typedef struct
{
    UINT16 usCompDCI[2*16];
    UINT16 usCompDCQ[2*16];
}NV_ID_LTE_DCOC_STRU;
typedef struct
{
    UINT16 usIP2Comp[24];
}NV_ID_LTE_IP2_STRU;
typedef struct
{
    UINT16 usDcOffset;
    UINT16 usVgaCfg;
}NV_TX_PD_AUTO_CAL_PARA;

typedef struct
{
    UINT16 usValidFreqNum;
    UINT16 usValidPwrNum;
    UINT16 ausPdPower[16][16];
}NV_TX_PD_PWR_TABLE_STRU;

typedef struct
{
    UINT16 usValidFreqNum;
    UINT16 usValidVoltNum;
    UINT16 ausPdVolt[16][16];
}NV_TX_PD_VOLT_TABLE_STRU;

typedef struct
{
    UINT16  usValidNum;
    UINT16  usRsv;
    INT16 asPdTempCmp[32];
}NV_TX_PD_TEMPCMP_TABLE_STRU;
