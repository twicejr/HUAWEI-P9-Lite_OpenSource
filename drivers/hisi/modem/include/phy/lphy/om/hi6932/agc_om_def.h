/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
 文 件 名   : AFC.h
 版 本 号   : 初稿
 作    者   : Shen Guang
 生成日期   : 2010年12月23日
 最近修改   :
 功能描述   : AFC的头文件
 函数列表   :
 修改历史   :
 1.日    期   : 2010年12月23日
   作    者   : Shen Guang
   修改内容   : 创建文件
 2.日    期   : 2012年04月17日
   作    者   : Shen Guang
   修改内容   : [DTS2012022700423]FDD-TDD互操作
 3.日    期   : 2012年05月05日
   作    者   : Shen Guang
   修改内容   : [DTS2012050201496]修改AGC驻留失步问题

******************************************************************************/


#ifndef __AGC_OM_DEF_H__
#define __AGC_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
/************************************************************
                     包含其它模块的头文件
************************************************************/

/************************************************************
                               宏定义
************************************************************/
#ifndef LPHY_MAX_RX_ANTENNA_NUM
#define LPHY_MAX_RX_ANTENNA_NUM     (4)
#endif

#ifndef AGC_MAX_CC_NUM
#define AGC_MAX_CC_NUM           LPHY_FEATURE_MAX_CARRIER_NUM
#endif

#ifndef AGC_MAX_SERV_FREQ_NUM
#define AGC_MAX_SERV_FREQ_NUM					(LPHY_FEATURE_MAX_CARRIER_NUM+2)
#endif

#ifndef AGC_EMBMS_MAX_CH
#define AGC_EMBMS_MAX_CH    (2)
#endif

#define AGC_BANDSCAN_COMB_NUM	 (16)
/************************************************************
                             数据结构定义
************************************************************/

/************************************************************
                             接口函数声明
 ************************************************************/

/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
typedef enum
{
    LPHY_REQ_AGC_REPORT_ENA                         = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_AAGC_FIXED_RF_GAIN_CONFIG_ENA,
    LPHY_REQ_AAGC_FIXED_PRE_GAIN_CONFIG_ENA,
    LPHY_REQ_AAGC_FIXED_POST_GAIN_CONFIG_ENA,
    LPHY_REQ_AAGC_ANTENNA_ADJUST_CONFIG_ENA,
    LPHY_REQ_AAGC_INTERFERENCE_CONFIG_ENA,
    LPHY_REQ_AAGC_DEM_PERIOD_CONFIG_ENA,
    LPHY_REQ_AAGC_PRE_TARGET_CONFIG_ENA,
    LPHY_REQ_AAGC_POST_TARGET_CONFIG_ENA,
    LPHY_REQ_AAGC_TDD_BLOCK_POWER_THRE_CONFIG_ENA,
    LPHY_REQ_AAGC_TDD_BLOCK_GAIN_STEPSIZE_CONFIG_ENA,
    LPHY_REQ_DAGCF_DEM_FIXED_GAIN_CONFIG_ENA,
    LPHY_REQ_DAGCF_MSR_FIXED_GAIN_CONFIG_ENA,
    LPHY_REQ_DAGCF_ADJ_BIT_CONFIG_ENA,
    LPHY_REQ_DAGCF_EXTRA_PA_CONFIG_ENA,
    LPHY_REQ_DAGCF_SHIFT_BIT_CONFIG_ENA,
    LPHY_REQ_TRIGGER_RFIN_SAMPLING_ENA,
    LPHY_REQ_MAGC_REPORT_ENA,
    LPHY_REQ_AGC_BAND_SCAN_PWR_RPT_ENA,
    LPHY_REQ_AGC_FREQ_BUF_RPT_ENA,
    LPHY_REQ_AGC_COM_RPT_ENA,
    LPHY_REQ_AGC_FREQ_CFG_RPT_ENA,
    LPHY_REQ_AGC_MODE_CFG_FREQ_PROC_RPT_ENA,
    LPHY_REQ_AGC_NV_BUF_INFO_RPT_ENA,
    LPHY_REQ_AGC_CALC_DIRECT_CONN_ENA,
    LPHY_REQ_AGC_CHANCTRL_FREQ_CFG_RPT_ENA,
 	LPHY_REQ_HRL_INTERFACE_RPT_ENA,
    LPHY_REQ_HRL_STATUS_RPT_ENA,
    LPHY_REQ_HRL_NV_INFO_RPT_ENA,
    LPHY_REQ_HRL_ENABLE_ENA,
    LPHY_REQ_HRL_FIX_THR_COEF_ENA,
    LPHY_REQ_HRL_FIX_COM_COEF_ENA,
    LPHY_REQ_HRL_FIX_FILTER_IN_FOESET_ENA,
    LPHY_REQ_HRL_FIX_WORK_MODE_ENA,
    LPHY_REQ_HRL_FIX_SUPPRESS_IDX_ENA,
    LPHY_REQ_HRL_FIX_COMEN_ENA,
    LPHY_REQ_HRL_SET0_INTERFACE_RPT_ENA,
    LPHY_REQ_HRL_FIX_COM_IDX_ENA
}LPHY_REQ_AGC_ENUM;

typedef enum
{
    AGC_OM_SWITCH_OFF = 0,
    AGC_OM_SWITCH_ON,
}AGC_OM_SWITCH_ENUM;

typedef UINT16 AGC_OM_SWITCH_ENUM_UINT16;
typedef UINT32 AGC_OM_SWITCH_ENUM_UINT32;


typedef enum
{
    DEBUG_RFIN_NO_TRIGGER = 0,
    DEBUG_RFIN_SAMPLING_ENABLE,
    DEBUG_RFIN_PBCH_FAILURE,
    DEBUG_RFIN_GAP_INTER_FREQ_START,
    DEBUG_RFIN_IDLE_INTER_FREQ_START,
    DEBUG_RFIN_INTER_FREQ_FINISH,
    DEBUG_RFIN_PRE_DEFINED_SUBFRAME,
    DEBUG_RFIN_DLSCH_CRC,
    DEBUG_RFIN_BCCH_CRC,
    DEBUG_RFIN_PCH_CRC,
    DEBUG_RFIN_TIMING_ERROR,
    DEBUG_EMU_ABNORMAL_RPT,
    DEBUG_CMU_ABNORMAL_RPT,
    DEBUG_AFC_ABNORMAL_RPT
}LPHY_DEBUG_RFIN_SAMPLING_TYPE_ENUM;
typedef UINT16 LPHY_DEBUG_RFIN_SAMPLING_TYPE_ENUM_UINT16;

typedef enum
{
    AGC_BANDSCAN_STAGE_NULL 			= 0,
    AGC_BANDSCAN_STAGE_1,
	AGC_BANDSCAN_STAGE_2,
    AGC_BANDSCAN_STAGE_DONE
} AGC_BANDSCAN_STAGE_ENUM;
typedef UINT16 AGC_BANDSCAN_STAGE_ENUM_UINT16;

typedef struct
{
	AGC_BANDSCAN_STAGE_ENUM_UINT16 enStage;
	UINT16 usCounter;
	INT32 alBandScanDbm[LPHY_MAX_RX_ANTENNA_NUM][AGC_BANDSCAN_COMB_NUM];
}AGC_BANDSCAN_CTRL_STRU;


typedef struct
{
    LPHY_DEBUG_RFIN_SAMPLING_TYPE_ENUM  enRfinSamplingTrigger;
    UINT32                              ulCounter;
    UINT16                              usFreqInfo;
    UINT16                              usCellId;
    INT16                               sUpThreshold;
    INT16                               sLowThreshold;
    UINT16                              usEmuMode;
    UINT16                              enCcIndex;
}LPHY_DEBUG_RFIN_SAMPLING_CTRL_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enReportEn;    /*1 使能AGC状态上报*/
}LPHY_REQ_AGC_REPORT_ENA_STRU;


typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enReportEn;
}LPHY_REQ_AGC_BANDSCAN_PWR_RPT_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enReportEn;
}LPHY_REQ_AGC_FREQ_BUF_RPT_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enReportEn;
}LPHY_REQ_MAGC_REPORT_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enReportEn;

}LPHY_REQ_AGC_COMPENSATION_REPORT_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enReportEn;

}LPHY_REQ_AGC_FREQ_CFG_RPT_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enReportEn;

}LPHY_REQ_AGC_MODE_CFG_FREQ_PROC_RPT_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enReportEn;

}LPHY_REQ_AGC_NV_BUF_INFO_RPT_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enReportEn;
}LPHY_REQ_AGC_CHANCTRL_FREQ_CFG_ENA_STRU;

typedef enum
{
    AGC_INDEPENDENT_ANTENNA,
    AGC_COMBINED_ANTENNA,
    AGC_NOISE_SAME,
    AGC_ON_AIR
}AGC_ANT_CONFIG_ENUM;
typedef UINT16  AGC_ANT_CONFIG_ENUM_UINT16;

typedef enum
{
    AGC_ADJMODE_INDEPENDENT = 0,
    AGC_ADJMODE_NOISESAME,
	AGC_ADJMODE_UNITY
}AGC_ADJMODE_ENUM;
typedef UINT8 AGC_ADJMODE_ENUM_UINT8;


typedef enum
{
    AGC_NO_INTERFERENCE =0,
    AGC_ACS_INTERF_VAR,
    AGC_ACS_INTERF_CONST,
    AGC_NB_INTERF_VAR,
    AGC_NB_INTERF_CONST,
    AGC_INTERF_BUTT,
}AGC_INTERFERENCE_TYPE_ENUM;
typedef INT16  AGC_INTERFERENCE_TYPE_ENUM_INT16;

typedef enum
{
    AGC_DEM_PERIOD_1MS = 0,
    AGC_DEM_PERIOD_5MS,
    AGC_DEM_PERIOD_10MS,
    AGC_DEM_PERIOD_20MS,
    AGC_DEM_PERIOD_BUTT,
}AGC_DEM_MODE_SEL_ENUM;
typedef UINT16  AGC_DEM_MODE_SEL_ENUM_UINT16;

typedef enum
{
    AGC_RF_IDX0 = 0,
    AGC_RF_IDX1,
    AGC_RF_IDX2,
    AGC_RF_IDX3,
    AGC_RF_IDX4,
    AGC_RF_IDX5,
    AGC_RF_IDX6,
    AGC_RF_IDX7,
    AGC_RF_IDX8,
    AGC_RF_IDX9,
    AGC_RF_IDX10,
    AGC_RF_IDX11,
    AGC_RF_IDX12,
    AGC_RF_IDX13,
    AGC_RF_IDX14,
    AGC_RF_IDX15,
}AGC_RF_IDX_ENUM;
typedef UINT16  AGC_RF_IDX_ENUM_UINT16;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    AGC_RF_IDX_ENUM_UINT16       aenFixedRfIdx[AGC_MAX_CC_NUM][LPHY_MAX_RX_ANTENNA_NUM];//om for ca
}LPHY_REQ_AAGC_FIXED_RF_GAIN_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    INT16     asFixedPreDagcGain[AGC_MAX_CC_NUM][LPHY_MAX_RX_ANTENNA_NUM];//om for ca
}LPHY_REQ_AAGC_FIXED_PRE_GAIN_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    INT16     asFixedPostDagcGain[AGC_MAX_CC_NUM][LPHY_MAX_RX_ANTENNA_NUM];//om for ca
}LPHY_REQ_AAGC_FIXED_POST_GAIN_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT16    enEnable;
    AGC_ANT_CONFIG_ENUM_UINT16   enAntennaConfig; // default AGC_ON_AIR
}LPHY_REQ_AAGC_ANTENNA_ADJUST_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT16    enEnable;
    AGC_INTERFERENCE_TYPE_ENUM_INT16      enInterfConfig;
}LPHY_AGC_OM_INTERF_CONFIG_STRU;

typedef struct
{
	LPHY_AGC_OM_INTERF_CONFIG_STRU astInterfConfig[AGC_MAX_CC_NUM];//om for ca
}LPHY_REQ_AAGC_INTERFERENCE_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT16    enEnable;
    AGC_DEM_MODE_SEL_ENUM_UINT16 enDemPeriodSel;
}LPHY_REQ_AAGC_DEM_PERIOD_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    INT32     lPreTarPower;
}LPHY_REQ_AAGC_PRE_TARGET_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    INT32     lPostTarPower;
}LPHY_REQ_AAGC_POST_TARGET_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    INT32     lTddBlockPowerThresh;
}LPHY_REQ_AAGC_TDD_BLOCK_POWER_THRE_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    INT32     lTddBlockGainStep;
}LPHY_REQ_AAGC_TDD_BLOCK_GAIN_STEPSIZE_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32 enEnable;
    UINT32    aulDemFixedDagcFGain[AGC_MAX_CC_NUM];//om for ca
}LPHY_REQ_DAGCF_DEM_FIXED_GAIN_CONFIG_ENA_STRU;

typedef enum
{
    HRL_SWITCH_OFF = 0,
    HRL_SWITCH_ON,
}HRL_SWITCH_ENUM;
typedef UINT16 HRL_SWITCH_ENUM_UINT16;
typedef UINT32 HRL_SWITCH_ENUM_UINT32;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT16  enEnable;
    UINT16 usRsv;
}LPHY_REQ_HRL_INTERFACE_RPT_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT16  enEnable;
    UINT16 usRsv;
}LPHY_REQ_HRL_STATUS_RPT_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT16  enEnable;
    UINT16 usRsv;
}LPHY_REQ_HRL_NV_INFO_RPT_ENA_STRU;

/*谐波,DC 抑制索引 */
typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT16  enEnable;
    UINT16 usRsv;
    UINT16 usDemHarIdx[AGC_MAX_CC_NUM];
    UINT16 usDemDcIdx[AGC_MAX_CC_NUM];
    UINT16 usMeasHarIdx[AGC_MAX_CC_NUM];
    UINT16 usMeasDcIdx[AGC_MAX_CC_NUM];
}LPHY_REQ_HRL_FIX_SUPPRESS_ENA_STRU;

/*谐波抑制使能打桩*/
typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32  enEnable;
    HRL_SWITCH_ENUM_UINT32 enHrlSwitch[AGC_MAX_CC_NUM];
}LPHY_REQ_HRL_ENA_CFG_STRU;

/*HRL 工作模式打桩*/
typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT16  enEnable;
    UINT8 ucHrlMode[AGC_MAX_CC_NUM];
}LPHY_REQ_HRL_FIX_WORK_MODE_CFG_ENA_STRU;
/*直流偏置打桩*/
typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32  enEnable;
    INT32 lFilterInFOest[AGC_MAX_CC_NUM];
}LPHY_REQ_HRL_FIX_FOEST_ENA_STRU;

/*补偿系数打桩*/
typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32  enEnable;
    SINT16 sComCoefReal[AGC_MAX_CC_NUM];
    SINT16 sComCoefImg[AGC_MAX_CC_NUM];    
}LPHY_REQ_HRL_FIX_COM_COEF_ENA_STRU;

/*抑制门限系数打桩*/
typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT16  enEnable;
    UINT8 ucThrCoef[AGC_MAX_CC_NUM];  
}LPHY_REQ_HRL_FIX_THR_COEF_ENA_STRU;

/*抑制门限系数打桩*/
typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32  enEnable;
    HRL_SWITCH_ENUM_UINT32 enHrlComSwitch[AGC_MAX_CC_NUM];  
}LPHY_REQ_HRL_FIX_COMEN_ENA_STRU;

/*谐波软值置零接口信息上报开关*/
typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32  enEnable;
}LPHY_REQ_HRL_SET0_INTERFACE_RPT_ENA_STRU;

typedef struct
{
    UINT16 usComIdx;
    UINT8  aucComFlag[2][3]; //2r 3idx
}LPHY_REQ_HRL_FIX_COM_IDX_STRU;

/*补偿索引打桩*/
typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32  enEnable;
    LPHY_REQ_HRL_FIX_COM_IDX_STRU stHarComInfo[AGC_MAX_CC_NUM];  //2cc
    LPHY_REQ_HRL_FIX_COM_IDX_STRU stDcComInfo[AGC_MAX_CC_NUM];   //2cc
}LPHY_REQ_HRL_FIX_COM_IDX_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    UINT32    aulMsrFixedDagcFGain[AGC_MAX_CC_NUM];//om for ca
}LPHY_REQ_DAGCF_MSR_FIXED_GAIN_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    UINT32    ulAdjBit;
}LPHY_REQ_DAGCF_ADJ_BIT_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    UINT32    ulExtraPA;
}LPHY_REQ_DAGCF_EXTRA_PA_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32    enEnable;
    UINT32    ulDemBitShift;
    UINT32    ulMsrBitShift;
}LPHY_REQ_DAGCF_SHIFT_BIT_CONFIG_ENA_STRU;


/************************************************************
                           3. Sg数据结构定义
************************************************************/

typedef enum
{
    AGC_DIRECT_NONE_CONN 			= 0,
    AGC_DIRECT_CONN,
} AGC_DIRECT_CONN_ENUM;
typedef UINT16 AGC_DIRECT_CONN_ENUM_UINT16;

typedef enum
{
    AGC_CC_DEACTIVE = 0,
    AGC_CC_ENACTIVE,
    AGC_CC_CHANGE_CHAN          /*激活状态不变只有通道发生改变，AGC需要hold 一个子帧*/
}AGC_CC_STATUS_ENUM;
typedef UINT16 AGC_CC_STATUS_ENUM_UINT16;

typedef enum
{
    LPHY_SG_AAGC_REPORT_ENA                     = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_SG, 0x0),
    LPHY_SG_DAGC_REPORT_ENA                     = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_SG, 0x1),
    LPHY_SG_MDAGCF_REPORT_ENA                   = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_SG, 0x2),
    LPHY_SG_MAAGC_MAIN_AREA_REPORT_ENA          = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_SG, 0x3),
    LPHY_SG_MAAGC_NON_MAIN_AREA_REPORT_ENA      = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_SG, 0x4),
}LPHY_SG_AGC_ENUM;

typedef struct
{
    INT16     sPreTargetPower;
    INT16     sPostTargetPower;
}AGC_TARGET_POWER_STRU;


typedef struct
{
	INT32   alPreRssiSymbolAcc[LPHY_MAX_RX_ANTENNA_NUM];			//pre-rssi dB 符号累和
	INT32	alPostRssiSymbolAcc[LPHY_MAX_RX_ANTENNA_NUM];			//post-rssi dB 符号累和
	INT32	alInbandSymbolAcc[LPHY_MAX_RX_ANTENNA_NUM];				//inband dB 符号累和
	INT32	alCRSSubframeAcc[LPHY_MAX_RX_ANTENNA_NUM];				//每子帧平均CRS dB子帧间累和
	INT32	alCRSAccTmp0[LPHY_MAX_RX_ANTENNA_NUM];			//每子帧CRS符号0 4 7 11 dB累和
	INT32	alCRSAccTmp1[LPHY_MAX_RX_ANTENNA_NUM];			//每子帧CRS符号1 8 dB累和
	UINT8	aucSymbolNum[4];
	UINT8	aucSubframeNum[4];
	UINT8   aucEmbmsReNum[4];
}AGC_ACC_INFO_STRU;

typedef struct
{
	AGC_ACC_INFO_STRU stAccInfo;									//统计周期累和
	AGC_DIRECT_CONN_ENUM_UINT16      enDirectConnIndicate[LPHY_MAX_RX_ANTENNA_NUM];         //4收直连指示
    INT16     asPreRssidB[LPHY_MAX_RX_ANTENNA_NUM];                 //接收天线0/1/2/3的滤波前时域DAGC的RSSI 平均值
    INT16     asPreDAGCTgain[LPHY_MAX_RX_ANTENNA_NUM];         		//接收天线0/1/2/3的滤波前时域DAGC增益
    INT16     asPreAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];           	//滤波前接收天线0/1/2/3天线口功率,dBm
    INT16     asPostRssidB[LPHY_MAX_RX_ANTENNA_NUM];                //滤波后接收天线0/1/2/3的时域DAGC的RSSI 平均值
    INT16     asPostDAGCTgain[2][LPHY_MAX_RX_ANTENNA_NUM];       	//滤波后接收天线0/1/2/3的时域DAGC增益, none-ABS、ABS
    INT16     asPostAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];          	//滤波后接收天线0/1/2/3天线口功率,dBm
    INT16     asAAGCgain[LPHY_MAX_RX_ANTENNA_NUM];             		//接收天线0/1/2/3的AAGC增益
    UINT16    ausLNAGain[LPHY_MAX_RX_ANTENNA_NUM];             		//当前接收天线0/1/2/3的LNA档位
    UINT16    ausRFGain[LPHY_MAX_RX_ANTENNA_NUM];
    UINT16    ausRFIdex[LPHY_MAX_RX_ANTENNA_NUM];
    AGC_RF_IDX_ENUM_UINT16    aenFinalIdx[LPHY_MAX_RX_ANTENNA_NUM];
    AGC_INTERFERENCE_TYPE_ENUM_INT16    aenAAGCIdxSel[LPHY_MAX_RX_ANTENNA_NUM];          //接收天线0/1/2/3索引选择信号
    /*last Value*/
    UINT16    ausLastRfGain[LPHY_MAX_RX_ANTENNA_NUM];      //接收天线0/1/2/3的AAGC增益
    INT16     asLastCrsAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];      //接收天线0/1/2/3的AAGC增益
    INT16     asLastPreAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];      //接收天线0/1/2/3的AAGC增益
    INT16     asLastPostAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];      //接收天线0/1/2/3的AAGC增益

    INT16     asLastAAGCgain[LPHY_MAX_RX_ANTENNA_NUM];      //接收天线0/1/2/3的AAGC增益
    INT16     asLastPreDAGCTgain[LPHY_MAX_RX_ANTENNA_NUM];  //滤波后接收天线0/1/2/3的时域DAGC增益
    INT16     asLastPostDAGCTgain[LPHY_MAX_RX_ANTENNA_NUM]; //接收天线0/1/2/3的AAGC增益alex tbd abs

    /*多模增加内容*/
    UINT8    ucFixAgcFlag;                                /*该频点固定AGC标识*/
    UINT8    ucReserved;                                     /*磁滞时能*/
    UINT8    ucLastFixAgcFlag;
    //UINT8    ucReserved2;
    UINT8    ucInterAutoGainConuter;
    /*END*/
    INT16     asInBanddB[LPHY_MAX_RX_ANTENNA_NUM];                	//平均的InBand功率统计未折到天线口，连续CA场景针对中心频点为Sum_InBand
    INT16     asInBandAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];         	//asInBanddB 折算到天线口
    INT16     asCRSdB[LPHY_MAX_RX_ANTENNA_NUM];                		//平均的CRS功率统计未折到天线口，连续CA场景针对中心频点为Sum_CRS
    INT16     asCRSAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];              //asCRSdB 折算到天线口
	AGC_INTERFERENCE_TYPE_ENUM_INT16 enInterfInd;
    AGC_DIRECT_CONN_ENUM_UINT16 enDirectConnInd;
}AAGC_PARA_STRU;

typedef struct
{
    UINT32    aulRx0Sym0Pwr[4];  
    UINT32    aulRx1Sym0Pwr[4];  
    UINT16    ausSym0PwrInv[4];  
	UINT32	  aulCSIDAGCFGain[4];
    UINT32    aulDAGCFGain[4];   
    UINT16    ausPaValue[4];
    UINT32    aulPcValue[4];

    INT16     asAGCNoiseFactor[AGC_MAX_CC_NUM][LPHY_MAX_RX_ANTENNA_NUM];         //噪声因子//cc0 cc1 cc2 cc3
    UINT16    ausDAGCFTar[4];              //根据ADJBit得到,计算DAGCF目标功率,在符号2中断中更新
    UINT8     ucCounter1;
    UINT8     ucCounter3;
    UINT8	  aucRsv[2];
}DAGCF_PARA_STRU;

typedef struct LPHY_AGC_OM_AAGC_CC_STATE
{
    LPHY_CA_CC_ENUM_UINT16    enCCIdx;
    AGC_CC_STATUS_ENUM_UINT16 enCCState;
    UINT32 ulShowIdx;
}LPHY_AGC_OM_AAGC_CC_STATE_STRU;

typedef struct
{
    AGC_ADJMODE_ENUM_UINT8     enIndepAGCFlag;
    UINT8     ucFreqIndex;
    UINT16    usFreqInfo;
    UINT32    ulContCaFlag;
    UINT16    usCaMemberFreqInfo[2];
    AAGC_PARA_STRU    stAAGCPara;
}LPHY_AGC_OM_AAGC_REPORT_ONE_CC_STRU;

typedef struct
{
    LPHY_AGC_OM_AAGC_CC_STATE_STRU      astOmAagcCCState[6];
	LPHY_AGC_OM_AAGC_REPORT_ONE_CC_STRU astAAgcPara[6];//om for ca
} LPHY_SG_AAGC_REPORT_ENA_STRU;

typedef struct
{
    UINT8     aucAgcPaIndex[4];                //PA 索引cc0 cc1
    UINT8     aucExtraPa[4];                   //Extra PA   cc0 cc1
    UINT8     ucMflag;
    UINT8     ucReserved;
    UINT16    usSubFrameNum;// = SCHED_GetSubFrmNum();
    DAGCF_PARA_STRU   stDAGCFPara;             //当前子帧DAGCF的参数
} LPHY_SG_DAGC_REPORT_ENA_STRU;

typedef struct
{
    UINT16    usMs1DagcfGain;
    UINT16    usReserved;
    UINT16    usMDagcfGain[AGC_EMBMS_MAX_CH];

    UINT16    usDagcfGainDiff[AGC_EMBMS_MAX_CH];
    UINT16    usDagcfGainCoef[AGC_EMBMS_MAX_CH];

    INT16     sOutDiffPowdBm[AGC_EMBMS_MAX_CH];//PMCH子帧与之前紧邻的单播子帧滤波后天线口功率之差

} LPHY_SG_MDAGC_REPORT_ENA_STRU;

typedef struct
{
    UINT16 usMagcStrartFlag;
    UINT16 usEmbmsHold;

    UINT16 usEmbmsflag;
    UINT16 usFirstFrameFlag;

    UINT16 usMagcCalcFlag;
    UINT16 usCurMrsValid;

    UINT16 usNextMrsValid;
    UINT16 usCfgValid;

    UINT16 usMainAreaFlg;
    UINT16 usPeriod;

    UINT16 usSfnCounter;
    UINT16 usSubFrmNum;
} LPHY_TRACE_MDAGC_STATE_STRU;



typedef struct
{
    AAGC_PARA_STRU    astMAGCPara[2];
} LPHY_SG_MAAGC_REPORT_ENA_STRU;

/* END: Added by s00175552, 2011/8/01   问题单号:DTS2011080101213*/

/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum
{
    LPHY_TRACE_AGC_STATE         = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_AGC_TDD_BLOCK_EVENT,
    LPHY_TRACE_AGC_SPECIAL_SENARIO_1,
    LPHY_TRACE_AGC_SPECIAL_SENARIO_3,
    LPHY_TRACE_AGC_SPECIAL_SENARIO_4,
    LPHY_TRACE_AGC_SPECIAL_SENARIO_6,
    LPHY_TRACE_AGC_FREQ_INFO,
    LPHY_TRACE_AGC_EMBMS_FRAME,
    LPHY_TRACE_MDAGC_STATE,
    LPHY_TRACE_AGC_EMBMS_MUTE,
	LPHY_TRACE_AGC_BANDSCAN_PWR_INFO,
	LPHY_TRACE_AGC_COMPENSATION_INFO,
	LPHY_TRACE_AGC_FREQ_CFG,
	LPHY_TRACE_AGC_MODE_CFG_FREQ_PROC,
	LPHY_TRACE_AGC_MODE_REQ_GAIN_CFG,
	LPHY_TRACE_AGC_MODE_CFG,
	LPHY_TRACE_AGC_DRX_GAIN_CFG,
	LPHY_TRACE_AGC_NV_BUF_INFO,
	LPHY_TRACE_AGC_CHANCTRL_FREQ_CFG,
	LPHY_TRACE_HRL_STATUS_INFO,
    LPHY_TRACE_HRL_INTERFACE_RSRP_INFO,
    LPHY_TRACE_HRL_INTERFACE_FOEST_INFO,
    LPHY_TRACE_HRL_NV_INFO,
    LPHY_TRACE_HRL_SET0_INTERFACE_INFO
}LPHY_TRACE_AGC_ENUM;


typedef enum
{
    AGC_BAND_SCAN = 0,            /*扫频模式*/
    AGC_INIT_CELL_SEARCH,         /*初始小区搜索模式，RSSI统计时长5ms，使用全部符号数据*/
    AGC_DEMOD,                    /*解调模式，RSSI统计使用导频符号*/
    AGC_GAP,                      /*GAP异频模式*/
    AGC_DRX,                      /*DRX异频模式*/
    AGC_NO_GAP_MEAS,              /*无GAP测量*/
    AGC_FIXED_GAIN0,              /*固定增益*/
    AGC_FIXED_GAIN1,
    AGC_NULL
} AGC_WORKING_MODE_ENUM;

typedef UINT16 AGC_WORKING_MODE_ENUM_UINT16;


typedef struct
{
    LTE_BAND_WIDTH_ENUM_UINT16      enAGCRFBW;     /*RF滤波器带宽*/
    LTE_BAND_WIDTH_ENUM_UINT16      enAGCBBBW;     /*基带滤波器带宽*/
} AGC_BW_CHANGE_STRU ;

typedef struct
{
    UINT16                             usAGCFreqInfo; 							/*AGC频点信息*/
    UINT16                             usBand;
    LPHY_CA_CC_ENUM_UINT16             enCcIdx;
    UINT16                             usRsv;
    AGC_BW_CHANGE_STRU                 stAGCBWChange; 							/*AGC带宽变化*/
}AGC_FREQUENCY_INFO_STRU;


typedef struct
{
    AGC_CC_STATUS_ENUM              enCCStatus;         /*载波状态*/
    CHANCTRL_CA_IND_ENUM_UINT16     enCAType;
    LPHY_CA_CC_ENUM_UINT16          enCaMemberCC;
    UINT16                          usFreqInfo; 							/*AGC频点信息*/
    UINT16                          usBand;
}CHANCTRL_CC_INFO_STRU;

typedef struct
{
    AGC_FREQUENCY_INFO_STRU         stCcFreqInfo;                           /*当前操作载波的频点信息*/
    AGC_CC_STATUS_ENUM_UINT16       enCcStatus;                             /*载波状态 active inactive*/
    CHANCTRL_CA_IND_ENUM_UINT16     enCaType;                               /*连续CA标志*/
    AGC_FREQUENCY_INFO_STRU         stCaMemberFreqInfo;                     /*CA成员的频点信息*/
    AGC_FREQUENCY_INFO_STRU         stContCaCenterFreqInfo;                 /*连续CA的中心频点信息*/
    UINT8                           ucValidFlg;                             /*接口生效标志*/
    UINT8                           ucReserved;
	LTE_FRAME_TYPE_ENUM_UINT16      enFrametype;
}AGC_MODE_CFG_CC_INFO_STRU;

typedef struct
{
    AGC_MODE_CFG_CC_INFO_STRU           astCcInfo[AGC_MAX_CC_NUM];	            /*每个载波信息*/
    AGC_WORKING_MODE_ENUM_UINT16       	enAAGCMode;    							/*当前子帧AAGC工作模式*/
    UINT32                             	ulBaseCellPos;
    UINT16                              usBandScanFreq;                         /*能量排序时 10.8M的中心频点*/
    UINT16                              usDualPssFlag;
} AGC_MODE_CFG_REQ_STRU;

typedef struct
{
    AGC_MODE_CFG_CC_INFO_STRU           astCcInfo[AGC_MAX_CC_NUM];	            /*每个载波信息*/
}AGC_MODE_CFG_FREQ_PROC_RPT_STRU;

typedef struct
{
    AGC_WORKING_MODE_ENUM_UINT16       	enAAGCMode;    							/*当前子帧AAGC工作模式*/
    UINT16                              usBandScanFreq;                         /*能量排序时 10.8M的中心频点*/
    UINT16                              usDualPssFlag;
    UINT16                              usReserved;
}AGC_MODE_CFG_RPT_STRU;


typedef struct
{
    UINT32      ulSubframe;
}LPHY_TRACE_AGC_EMBMS_FRAME_STRU;


typedef struct
{
    UINT16      usMute;
    UINT16      usFirstFrameFlg;
}LPHY_TRACE_AGC_EMBMS_MUTE_STRU;


typedef enum
{
    AGC_ENTER_TDD_BLOCK_STATE = 0,
    AGC_TDD_BLOCK_INC_PWR,
    AGC_TDD_BLOCK_REACH_MAX_GAIN,
}AGC_TDD_BLK_EVENT_TRACE_ENUM;

typedef struct
{
    INT16     sCounter;
    UINT16    usState;
}AGC_SPECIAL_SENARION_TRACE_STRU;
typedef struct
{
    AGC_TDD_BLK_EVENT_TRACE_ENUM    enEvent;
}LPHY_TRACE_TDD_BLK_STRU;


typedef enum
{
    AGC_CONFIG_SCELL_FREQ_INFO = 0,                     						/*配置AGC服务区频点信息(包括CA信息变化)*/
    AGC_CONFIG_NCELL_FREQ_INFO,                         						/*配置AGC异频频点信息*/
    AGC_SWITCH_SCELL_FREQ_INFO,                        	 						/*切换AGC服务区频点*/
} AGC_FREQ_CMD_ENUM;
typedef UINT16 AGC_FREQ_CMD_ENUM_UINT16;

typedef enum
{
    AGC_CHANCTR_FREQ_DISCFG = 0,
    AGC_CHANCTR_FREQ_CFG,
    AGC_CHANCTR_FREQ_BUTT,
}AGC_CHANCTR_FREQ_CFG_ENUM;
typedef UINT16 AGC_CHANCTR_FREQ_CFG_ENUM_UINT8;

#define AGC_MAX_SERV_FREQ_NUM					(LPHY_FEATURE_MAX_CARRIER_NUM+2)
#define AGC_MASTER_MODE_PCC_SCC_CA_BGS_FREQ_NUM (AGC_MAX_SERV_FREQ_NUM+1)  //cc + max ca number + bgs number
#define AGC_MAX_FREQ_NUM						(LPHY_FEATURE_MAX_INTER_EMU_NUM + AGC_MASTER_MODE_PCC_SCC_CA_BGS_FREQ_NUM)
#define AGC_FREQUENCY_NEAR_SPARE_IDX			(AGC_MAX_FREQ_NUM - 1)	/*STATIC FREQ IDX FOR BGS FREQ*/
#define AGC_INVALID_FREQ_INDEX					(AGC_MAX_FREQ_NUM)
#define AGC_MAX_NEAR_FREQ_NUM					(AGC_MAX_FREQ_NUM - 1)
#define AGC_NEAR_FREQ_NUM_DCOC                  (LPHY_FEATURE_MAX_INTER_EMU_NUM)

#define AGC_MAX_CONT_CA_NUM                     (2)

#define AGC_FREQ_CONFIG_NUM_MAX         (LPHY_FEATURE_MAX_INTER_EMU_NUM)
typedef struct
{
    AGC_FREQ_CMD_ENUM_UINT16            enAGCFreqCmd;							/*频点配置类型*/
    UINT16                              usAGCNumOfFreq;							/*频点配置个数*/

    UINT16                              usAGCFreqInfo[AGC_FREQ_CONFIG_NUM_MAX];	/*若为设置或切换服务区，频点放置PCC SCC CONT_CC*/
    UINT16								ausBand[AGC_FREQ_CONFIG_NUM_MAX];		/*若为设置或切换服务区，BAND号放置PCC SCC CONT_CC*/

    AGC_CHANCTR_FREQ_CFG_ENUM_UINT8     aenFreqCfgInd[AGC_FREQ_CONFIG_NUM_MAX];
    UINT16                              usCcIdx[AGC_MAX_SERV_FREQ_NUM];
    UINT16                              usDualPssFlag;
    UINT16                              usRsv;
} AGC_FREQ_INFO_STRU;

typedef struct
{
    UINT16                              usAGCNumOfFreq;     /*服务区频点个数，连续CA为2，其他为1*/
    UINT16                              usRsv1;
    UINT16                              usAGCFreqInfo[2];	/*放置/去配置CC时 idx0当前配置载波，有ca时启用idx1 存CA member*/
    UINT16								ausBand[2];			/*同上*/
    AGC_CHANCTR_FREQ_CFG_ENUM_UINT8     aenFreqCfgInd[2];   /*同上*/
    UINT16                              usRsv2;
    UINT16                              usCcIdx[2];
}AGC_CHANCTRL_CA_INFO_STRU;


typedef struct
{
    AGC_FREQ_INFO_STRU      stFreqInfo;
}LPHY_TRACE_FREQ_INFO_STRU;

#define     HRL_MAX_FREQ_NUM 	        (6)
#define     HRL_MAX_SYM_NUM 	        (4)
#define     HRL_MAX_IDX_NUM  	        (3)
#define     HRL_MAX_COM_IDX_NUM  	    (6)
#define     HRL_MAX_HAR_COM_IDX_NUM  	(3)

typedef struct
{
    UINT8  ucMbmsFlg[HRL_MAX_SYM_NUM];
    INT8  ucBbpRptSuppIdx[HRL_MAX_SYM_NUM][HRL_MAX_IDX_NUM];
}HRL_BBP_RESULT_STRU;

typedef struct
{
    UINT8 	ucHarSwitch; 	         //0:off 1:on
    UINT8  ucDcSwitch;              //DC偏置抑制有效标志,初始化默认为LPHY_FALSE
    UINT16  usSpurFreqInfo;

    LTE_BAND_WIDTH_ENUM_UINT16	enBWDem;	            //有效的解调带宽
    LTE_BAND_WIDTH_ENUM_UINT16	enBWMeas;	            //有效的测量带宽

    UINT16  usDemNre;                   //有用子载波数与当前带宽有关 [72 180 300 600 900 1200]
    UINT16  usMeasNre;                  //有用子载波数与当前带宽有关 [72 180 300 600 900 1200]

    UINT16 	usHarDemSuppIdx;           //解调通路谐波抑制所在子载波索引
    UINT16 	usHarMeasSuppIdx;          //测量通路谐波抑制所在子载波索引

    UINT16 	usDcDemSuppIdx;            //DC偏置抑制所在子载波索引
    UINT16 	usDcMeasSuppIdx;           //DC偏置抑制所在子载波索引

    UINT16  usHarComIdx;               //hrl 补偿索引
    UINT16  usDcComIdx;                //dc 补偿索引

    HRL_BBP_RESULT_STRU stHarBbpResult[LPHY_MAX_RX_ANTENNA_NUM]; //谐波抑制信息上报
    HRL_BBP_RESULT_STRU stDcBbpResult[LPHY_MAX_RX_ANTENNA_NUM];  //dc抑制信息上报
    UINT8 ucComFlag[LPHY_MAX_RX_ANTENNA_NUM][HRL_MAX_COM_IDX_NUM];
    UINT8 ucDemSet0Flag[LPHY_MAX_RX_ANTENNA_NUM][HRL_MAX_COM_IDX_NUM];
}HRL_CTRL_STRU;

typedef struct
{
    UINT16 usFreqInfo;
    UINT16 usBand;

    LPHY_CA_CC_ENUM_UINT16 enCc;
    UINT8 usHrlWorkState;
    UINT8 usRsv;

	HRL_CTRL_STRU stCtrlRpt;
}LPHY_HRL_STATUS_RPT_ENA_STRU;

typedef struct
{
    UINT8 ucHarSwitch;
    UINT8 ucDcSwitch;
    UINT8 ucHarSpurFreqNum; //谐波干扰频点个数  小于AGC_HRL_MAX_HAR_FREQ_NUM
    UINT8 ucRsv;
    UINT16 ausHarSpurFreqInfo[AGC_HRL_MAX_HAR_FREQ_NUM];
}LPHY_HRL_SPUR_RPT_STRU;


typedef struct
{
    SINT16 sRsrp;
    UINT16 usRsv;
}LPHY_HRL_INTERFACE_RSRP_STRU;

typedef struct
{
    SINT32 lFilterInFOest;
}LPHY_HRL_INTERFACE_FOEST_STRU;

/************************************************************
                           5. ERROR数据结构定义
************************************************************/
typedef enum
{
    LPHY_ERROR_AGC_ARRAY_INDEX         = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_ERROR, 0x1),
    LPHY_ERROR_AGC_CASE,
    LPHY_ERROR_AGC_UNKONW_FREQ
}LPHY_ERROR_AGC_ENUM;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulIncorrectValue;
}LPHY_ERROR_AGC_ARRAY_INDEX_STRU;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulCurrentCase;
    UINT32      ulLastCase;
}LPHY_ERROR_AGC_CASE_STRU;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulFreqInfo;
}LPHY_ERROR_AGC_FREQ_INFO_STRU;

typedef struct
{
	UINT8              usDcSuppressNum;
	UINT8              usHarSuppressNum;
    UINT16             ausSuppressIdx[6]; //0-2谐波 3-5 dc
}HRL_SET0_INTERFACE_RPT_STRU;

typedef union
{
    LPHY_TRACE_TDD_BLK_STRU           stAgcTddBlockEvent;
    LPHY_TRACE_AGC_EMBMS_FRAME_STRU   stAgcEmbmsTrace;
    AGC_SPECIAL_SENARION_TRACE_STRU   stAgcSpecialSenario;
    LPHY_ERROR_AGC_CASE_STRU          stAgcCaseError;
    LPHY_ERROR_AGC_FREQ_INFO_STRU     stAgcFreqInfoError;
}AGC_OM_REPORT_UNION;

typedef enum
{
    AGC_SERV_FREQ = 0,  //服务区频点
    AGC_NEAR_FREQ,      //临区频点
} AGC_FREQ_TYPE_ENUM;
typedef UINT16 AGC_FREQ_TYPE_ENUM_UINT16;

typedef struct
{
    UINT16                          usFreqInfo;
    UINT16                          usBand;
    AGC_FREQ_TYPE_ENUM_UINT16       usFreqType;
    UINT16                          usBufIdx;
}AGC_ONE_FREQ_RPT_STRU;

typedef struct
{
    AGC_ONE_FREQ_RPT_STRU astFreqInfo[16]; //共16个频点，HIDS 上报识别宏有问题，用数字来代替
}AGC_FREQ_RPT_STRU;


typedef enum
{
    AGC_NV_BAND_INVALID 			= 0,
    AGC_NV_BAND_SERV,
    AGC_NV_BAND_NEAR,
} AGC_NV_BAND_TYPE_ENUM;
typedef UINT16 AGC_NV_BAND_TYPE_ENUM_UINT16;


typedef struct
{
	AGC_NV_BAND_TYPE_ENUM_UINT16		enNvBandType;
	UINT16								usBandNum;
    UINT32                              ulCurrReqFlg;
    UINT32                              ulNvTableAddr;
    UINT32                              ulAGCGainTable[8];  //AGC_MAX_GAIN_LEVEL = 8, HIDS 上报识别宏有问题，用数字来代替
    UINT32                              ulRFIdxTable[8];    //AGC_MAX_GAIN_LEVEL = 8, HIDS 上报识别宏有问题，用数字来代替
}AGC_ONE_NV_RPT_STRU;


typedef struct
{
    AGC_ONE_NV_RPT_STRU astNvBufInfo[4]; //共4个NV buf， HIDS 上报识别宏有问题，用数字来代替

}AGC_NV_BUF_RPT_STRU;


typedef struct
{
    UINT16 usFreqInfo;
    UINT16 usBandWidth;
    
    UINT16 usAntIndex;
    UINT16 usRfIndex;
    
    UINT16 usModemLoss;
    UINT16 usCurTemp;
    
    SINT16 sFreqCmpVal;
    SINT16 sTempCmpVal;

    UINT16 usErrorTable;
    SINT16 sTotalCmpVal;
}AGC_AAGC_COMPENSATION_RPT_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32 enCalcDirectConnEn;    /*1 使能AGC状态上报*/
}LPHY_REQ_AGC_CALC_DIRECT_CONN_ENA_STRU;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __AGC_OM_DEF_H__ */

