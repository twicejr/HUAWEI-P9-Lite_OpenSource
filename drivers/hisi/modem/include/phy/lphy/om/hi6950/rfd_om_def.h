/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
 文 件 名   : rfd_om_def.h
 版 本 号   : 初稿
 作    者   : wangxu
 生成日期   : 2011年4月25日
 最近修改   :
 功能描述   : RFD OM 的头文件
 函数列表   :
 修改历史   :
 1.日    期   : 2012年1月9日
   作    者   : shijiahong
   修改内容   : 创建文件
 --------------------------------------------------------------------------------
 ******************************************************************************/

#ifndef __RFD_OM_DEF_H__
#define __RFD_OM_DEF_H__


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
/************************************************************
                     包含其它模块的头文件
************************************************************/

/************************************************************
                               宏定义
************************************************************/


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
    LPHY_RFD_SSI_RPT_REQ            = OM_CMD_ID(LPHY_RFD_MID, OM_TYPE_REQ, 0x0),/*切频上报请求*/
    LPHY_RFD_AGC_SSI_RPT_REQ,
    LPHY_RFD_DRV_PARA_RPT_REQ,
    LPHY_RFD_UL_MIN_TA_CONFIG_REG,
    LPHY_RFD_MIPICMD_DELAY_CONFIG_REG,
    LPHY_RFD_SSICMD_DELAY_CONFIG_REG,
    LPHY_RFD_DISABLE_TXOFF_REQ,
    LPHY_RFD_SET_SSI_OVERTIME_REQ,
    LPHY_RFD_INTF_REQ,                  /*抗干扰特性*/
}LPHY_RFD_OM_REQ_ENUM;

typedef enum
{
    RFD_OM_SWITCH_OFF = LPHY_FALSE,
    RFD_OM_SWITCH_ON = LPHY_TRUE
}RFD_OM_SWITCH_ENUM;
typedef UINT16 RFD_OM_SWITCH_ENUM_UINT16;

typedef struct
{
    RFD_OM_SWITCH_ENUM_UINT16   enReportEn;    /*1 使能AFC状态上报*/
    UINT16                      usReserved;
}LPHY_REQ_RFD_REPORT_ENA_STRU;
typedef struct
{
    UINT32                      ulMinTa;
}LPHY_REQ_RFD_MIN_TA_CONFIG_STRU;
typedef struct
{
    UINT32                      ulDelayTime;
}LPHY_REQ_RFD_CMD_DELAY_CONFIG_STRU;

typedef enum
{
    RFD_AGC_DC_CFG_OM_OFF = 0x0,
    RFD_AGC_DC_CFG_OM_ON
}RFD_AGC_DC_CFG_OM_SWITCH_ENUM;

typedef struct
{
    RFD_AGC_DC_CFG_OM_SWITCH_ENUM   enAgcDcCfgRpt;
    UINT16                          usAnt0RfGainCode; /*天线0的aagc code*/
    UINT16                          usAnt0RfDCCode;   /*天线0的dc code*/
    UINT16                          usAnt1RfGainCode; /*天线1的aagc code*/
    UINT16                          usAnt1RfDCCode;   /*天线1的dc code*/
}RFD_AGC_DC_CFG_OM_STRU;

/*抗干扰特性*/
typedef struct
{
    RFD_OM_SWITCH_ENUM_UINT16   enReportEn;   /*使能开关*/
    UINT16                      usRsv;
}LPHY_REQ_RFD_INTF_ENA_STRU;

/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum
{
    LPHY_TRACE_RFD_SSI_RX_ON_RPT                = OM_CMD_ID(LPHY_RFD_MID, OM_TYPE_TRACE, 0x0),
    LPHY_TRACE_RFD_SSI_RX_OFF_RPT,
    LPHY_TRACE_RFD_SSI_RX_SHUTDOWN_RPT,
    LPHY_TRACE_RFD_SSI_RX_FREQ_RPT,
    LPHY_TRACE_RFD_SSI_RX_AGC_RPT,

    LPHY_TRACE_RFD_SSI_TX_ON_RPT,
    LPHY_TRACE_RFD_SSI_TX_OFF_RPT,
    LPHY_TRACE_RFD_SSI_TX_FREQ_RPT,
    LPHY_TRACE_RFD_SSI_TX_FREQON_RPT,
    LPHY_TRACE_RFD_SSI_TX_SHUTDOWN_RPT,
    LPHY_TRACE_RFD_SSI_TX_APC_RPT,

    LPHY_TRACE_RFD_SSI_RX_CLEAR_RPT,
    LPHY_TRACE_RFD_SSI_TX_CLEAR_RPT,

    LPHY_TRACE_RFD_SSI_RX_IIP2_RPT,
    LPHY_TRACE_RFD_SSI_MRX_RPT,
    LPHY_TRACE_RFD_SSI_DVTY_DISABLE_CHB_RPT, /* 关分集ssi上报 */
    LPHY_TRACE_RFD_SSI_DVTY_DISABLE_CHCD_RPT,
    LPHY_TRACE_RFD_SSI_DVTY_DISABLE_CHBCD_RPT,
    LPHY_TRACE_RFD_SSI_DVTY_ENABLE_CHB_RPT,
    LPHY_TRACE_RFD_SSI_DVTY_ENABLE_CHCD_RPT,
    LPHY_TRACE_RFD_SSI_DVTY_ENABLE_CHBCD_RPT,

    LPHY_TRACE_RFD_MIPI_RX_ON_RPT               = OM_CMD_ID(LPHY_RFD_MID, OM_TYPE_TRACE, 0x20),
    LPHY_TRACE_RFD_MIPI_TX_ON_RPT,
    LPHY_TRACE_RFD_MIPI_TX_OFF_RPT,
    LPHY_TRACE_RFD_MIPI_TX_APC_RPT,

    LPHY_TRACE_RFD_PARA_RPT                     = OM_CMD_ID(LPHY_RFD_MID, OM_TYPE_TRACE, 0x30),
    LPHY_TRACE_RFD_INTF_STAT_RD_RPT,
    LPHY_TRACE_RFD_INTF_STAT_WR_RPT,
    LPHY_TRACE_RFD_INTF_STAT_CMP_RPT,
    LPHY_TRACE_RFD_INTF_BLANK_RPT,
    LPHY_TRACE_RFD_INTF_JUDGE_HANDLE_RPT,
    LPHY_TRACE_RFD_INTF_JUDGE_RXTX_RPT,
}LPHY_TRACE_RFD_EVENT_ENUM;
typedef UINT16 LPHY_TRACE_RFD_EVENT_ENUM_UINT16;

typedef enum
{
    RFE_RFIN_RX_EVT_START      = 0,
    RFE_RFIN_RX_ON_EVT,
    RFE_RFIN_RX_ON_EX_EVT,
    RFE_RFIN_RX_OFF_EVT,
    RFE_RFIN_RX_OFF_EX_EVT,
    RFE_RFIN_RX_AGC_EVT,
    RFE_RFIN_RX_AGC_EX_EVT,
    RFE_RFIN_RX_SHUTDOWN_EVT,
    RFE_RFIN_RX_CLEAR_EVT,
    RFE_RFIN_RX_FREQ_SWITCH_EVT,
    RFE_RFIN_RX_SET_FREQ_EVT,
    RFE_RFIN_RX_EVT_END,

    RFE_RFIN_TX_EVT_START,
    RFE_RFIN_TX_ON_EVT,
    RFE_RFIN_TX_ON_EX0_EVT,
    RFE_RFIN_TX_ON_EX1_EVT,
    RFE_RFIN_TX_OFF_EVT,
    RFE_RFIN_TX_OFF_EX_EVT,
    RFE_RFIN_TX_FREQ_SWITCH_EVT,
    RFE_RFIN_TX_AGC_EVT,
    RFE_RFIN_TX_AGC_EX0_EVT,
    RFE_RFIN_TX_AGC_EX1_EVT,
    RFE_RFIN_TX_SHUTDOWN_EVT,
    RFE_RFIN_TX_CLEAR_EVT,
    RFE_RFIN_INTRA_FREQ_EVT,
    RFE_RFIN_INTER_RX_ON_EVT,
    RFE_RFIN_INTER_RX_OFF_EVT,
    RFE_RFIN_INTER_FREQ_EVT,
    RFE_RFIN_TX_SET_FREQ_EVT,
    RFE_RFIN_INTER_FLAG_ON_EVT,
    RFE_RFIN_INTER_FLAG_OFF_EVT,
    RFE_RFIN_INTER_AGC_EVT,
    RFE_RFIN_EVT_BUTT

}LPHY_RFE_RFIN_EVENT_ENUM;
typedef UINT16 LPHY_RFD_RFIN_EVENT_ENUM_UINT16;
#define RFD_RX_EVT_NUM (RFE_RFIN_RX_EVT_END-RFE_RFIN_RX_EVT_START - 1)


typedef struct
{
    UINT32 ulModemId;
    UINT32 ulStatusAddr;
    UINT32 ulStatus;
    UINT32 ulFreqAddr;
    UINT32 ulFreq;
    UINT16 usRsv;
    UINT8  ucRsv1;
    UINT8  ucRsv2;
}RFE_INTF_MODEM_RD_WR_STRU;

typedef struct
{
    UINT16                                      enMode;          /*工作模式*/
    UINT16                                      enBusinessType;  /*业务类型*/
    UINT16                                      usTxFreq;        /*tx上行绝对频率,单位0.1M*/
    UINT16                                      usRxFreq;        /*rx下行绝对频率,单位0.1M */
    UINT16                                      usBand;          /*频段*/
    UINT16                                      usRsv;
}RFE_INTF_STATUS_SUB_STRU;

typedef struct
{
    UINT32                                      ulRsv;
    RFE_INTF_STATUS_SUB_STRU                    stGuStatus;
    RFE_INTF_STATUS_SUB_STRU                    stLteStatus;
    UINT16                                      usRsv1;
    UINT8                                       ucLteFlag;
    UINT8                                       ucGuFlag;
}RFE_INTF_STATUS_STRU;

typedef struct
{
    UINT16                                      usRsv;
    UINT8                                       ucFlg;
    UINT8                                       ucRsv1;
    UINT16                                      usGuRxHoldFlag;
    UINT16                                      usKillAbbFlag;

    UINT16                                      usAction0;
    UINT16                                      usAction1;
}RFE_INTF_BLANK_STRU;

typedef struct
{
    RFE_INTF_STATUS_SUB_STRU                    stCurrInfo;
    RFE_INTF_STATUS_SUB_STRU                    stOpstInfo;
    UINT8                                       ucNvCurrBand;
    UINT8                                       ucNvCurrMode;
    UINT8                                       ucNvOpstBand;
    UINT8                                       ucNvOpstMode;
    UINT16                                      usNvTxBlankTxFreq;
    UINT16                                      usNvTxBlankRxFreq;
    UINT16                                      usNvRxBlankTxFreq;
    UINT16                                      usNvRxBlankRxFreq;
    UINT16                                      usActionOld;
    UINT16                                      usActionNew;
    UINT16                                      usTest;
    UINT16                                      usRsv1;
    INT32                                       slRsv2;
}RFE_INTF_JUDGE_HANDLE_STRU;

typedef struct
{
    UINT16                                      usFreqMax;
    UINT16                                      usFreqMin;
    UINT16                                      usCurrTxFreq;
    UINT16                                      usOpstRxFreq;
    UINT16                                      usAction;
    UINT16                                      usRsv;
    INT32                                       slRsv1;
}RFE_INTF_JUDGE_RXTX_STRU;

typedef struct
{
    RFIN_CH0_RON_SSI_CFG_UNION          stRfinSsiCfg;
    RFIN_CH0_RON_SSI_ADDR_UNION         stRfinSsiAddr;
}RFE_RFIN_BBP_SSI_CFG_STRU;

typedef struct
{
    RFIN_CH0_RON_MIPI_CFG_UNION         stRfinMipiCfg;
    RFIN_CH0_RON_MIPI_ADDR_UNION        stRfinMipiAddr;
}RFE_RFIN_BBP_MIPI_CFG_STRU;
typedef struct
{
    RFIN_CH0_RON_TIME_UNION             stEvtTimeCfg;
    RFE_RFIN_BBP_SSI_CFG_STRU           stSsiCfg;
    RFE_RFIN_BBP_MIPI_CFG_STRU          stMipiCfg;
    RFIN_CH0_RON_LINE_UNION             stLineCfg;
    RFIN_CH0_RON_LNA_EN_UNION           stLnaEnCfg;
    RFIN_CH0_RON_ANT_UNION              stAntEnCfg;
    RFIN_CH0_RON_EN_UNION               stEventEnCfg;
}RFE_RFIN_RX_ON_BBP_STRU;
typedef struct
{
    RFIN_CH0_ROFF_TIME_UNION            stEvtTimeCfg;
    RFE_RFIN_BBP_SSI_CFG_STRU           stSsiCfg;
    RFE_RFIN_BBP_MIPI_CFG_STRU          stMipiCfg;
    RFIN_CH0_ROFF_LINE_UNION            stLineCfg;
    RFIN_CH0_ROFF_LNA_EN_UNION          stLnaEnCfg;
    RFIN_CH0_ROFF_ANT_UNION             stAntEnCfg;
    RFIN_CH0_ROFF_EN_UNION              stEventEnCfg;
}RFE_RFIN_RX_OFF_BBP_STRU;

/*inter event*/
typedef struct
{
    RFIN_INTER_FREQ_TIME_UNION          stEvtTimeCfg;//RFIN_INTER_FREQ_TIME_UNION
    RFE_RFIN_BBP_SSI_CFG_STRU           stSsiCfg;
    RFE_RFIN_BBP_MIPI_CFG_STRU          stMipiCfg;
    RFIN_INTER_FREQ_ABBCFG_UNION        stLineCfg;//RFE_RFIN_INTRA_FREQ_LINE_CFG_STRU
    RFIN_INTER_FREQ_DBB_RATE_UNION      stDbbRateCfg;//RFE_RFIN_DBB_RATE_CFG_STRU
    RFIN_INTER_FREQ_EN_UNION            stEventEnCfg;//RFIN_INTER_FREQ_EN_UNION
}RFE_RFIN_RX_FREQ_BBP_STRU;
typedef struct
{
    RFIN_CH0_RAGC_TIME_UNION            stEvtTimeCfg;
    RFE_RFIN_BBP_SSI_CFG_STRU           stSsiCfg;
    RFE_RFIN_BBP_MIPI_CFG_STRU          stMipiCfg;
    RFIN_CH0_RAGC_LNA_MODE_UNION        stLnaEnCfg;
    RFIN_CH0_RAGC_EN_UNION              stEventEnCfg;
}RFE_RFIN_RX_AGC_BBP_STRU;
typedef struct
{
    RFIN_CH0_RSHUT_TIME_UNION           stEvtTimeCfg;//RFIN_INTER_FREQ_TIME_UNION
    RFE_RFIN_BBP_SSI_CFG_STRU           stSsiCfg;
    RFE_RFIN_BBP_MIPI_CFG_STRU          stMipiCfg;
    RFIN_CH0_RSHUT_LINE_UNION           stLineCfg;//RFIN_CH0_RSHUT_LINE_UNION
    RFIN_CH0_RSHUT_LNA_EN_UNION         stLnaEnCfg;//RFIN_CH0_RSHUT_LNA_EN_UNION
    RFIN_CH0_RSHUT_LNA_MODE_UNION       stLnaModeCfg;
    RFIN_CH0_RSHUT_ANT_UNION            stAntEnCfg;
    RFIN_CH0_RSHUT_EN_UNION             stEventEnCfg;//RFIN_INTER_FREQ_EN_UNION
}RFE_RFIN_RX_SHUTDOWN_BBP_STRU;
typedef struct
{
    RFIN_INTER_FON_TIME_UNION           stEvtTimeCfg;
    RFIN_INTER_FON_LINE_UNION           stLineCfg;
    RFIN_INTER_FON_EN_UNION             stEventEnCfg;
}RFE_RFIN_RX_INTERFLAGON_BBP_STRU;
typedef struct
{
    RFIN_INTER_FON_TIME_UNION           stEvtTimeCfg;
    RFIN_INTER_FON_LINE_UNION           stLineCfg;
    RFIN_INTER_FON_EN_UNION             stEventEnCfg;
}RFE_RFIN_RX_INTER_FLAGON_BBP_STRU;
typedef struct
{
    RFIN_INTRA_FON_TIME_UNION           stEvtTimeCfg;
    RFIN_INTRA_FON_LINE_UNION           stLineCfg;
    RFIN_INTRA_FON_EN_UNION             stEventEnCfg;
}RFE_RFIN_RX_INTRA_FLAGON_BBP_STRU;
typedef struct
{
    RFIN_CH0_TON_TIME_UNION             stEvtTimeCfg;
    RFE_RFIN_BBP_SSI_CFG_STRU           stSsiCfg;
    RFE_RFIN_BBP_MIPI_CFG_STRU          stMipiCfg;
    RFIN_CH0_TON_AUXDAC_CFG_UNION       stAucDacCfg;
    RFIN_CH0_TON_LINE_UNION             stLineCfg;
    RFIN_CH0_TON_PA_EN_UNION            stPaEnCfg;
    RFIN_CH0_TON_ANT_UNION              stAntEnCfg;
    RFIN_CH0_TON_EN_UNION               stEventEnCfg;
}RFE_RFIN_TX_ON_BBP_STRU;
typedef struct
{
    RFIN_CH0_TOFF_TIME_UNION            stEvtTimeCfg;
    RFE_RFIN_BBP_SSI_CFG_STRU           stSsiCfg;
    RFE_RFIN_BBP_MIPI_CFG_STRU          stMipiCfg;
    RFIN_CH0_TOFF_AUXDAC_CFG_UNION      stAucDacCfg;
    RFIN_CH0_TOFF_LINE_UNION            stLineCfg;
    RFIN_CH0_TOFF_PA_EN_UNION           stPaEnCfg;
    RFIN_CH0_TOFF_ANT_UNION             stAntEnCfg;
    RFIN_CH0_TOFF_EN_UNION              stEventEnCfg;
}RFE_RFIN_TX_OFF_BBP_STRU;
typedef struct
{
    RFIN_CH0_TAGC_TIME_UNION            stEvtTimeCfg;
    RFE_RFIN_BBP_SSI_CFG_STRU           stSsiCfg;
    RFE_RFIN_BBP_MIPI_CFG_STRU          stMipiCfg;
    RFIN_CH0_TAGC_AUXDAC_CFG_UNION      stAucDacCfg;
    RFIN_CH0_TAGC_PA_MODE_UNION         stPaModeCfg;
    RFIN_CH0_TAGC_PDM_MODU_UNION        stPdmModuCfg;
    RFIN_CH0_TAGC_EN_UNION              stEventEnCfg;
}RFE_RFIN_TX_APC_BBP_STRU;
typedef struct
{
    RFIN_CH0_TSHUT_TIME_UNION           stEvtTimeCfg;
    RFE_RFIN_BBP_SSI_CFG_STRU           stSsiCfg;
    RFE_RFIN_BBP_MIPI_CFG_STRU          stMipiCfg;
    RFIN_CH0_TSHUT_AUXDAC_CFG_UNION     stAucDacCfg;
    RFIN_CH0_TSHUT_LINE_UNION           stLineCfg;
    RFIN_CH0_TSHUT_PA_MODE_UNION        stPaModeCfg;
    RFIN_CH0_TSHUT_PA_EN_UNION          stPaEnCfg;
    RFIN_CH0_TSHUT_ANT_UNION            stAntEnCfg;
    RFIN_CH0_TSHUT_EN_UNION             stEventEnCfg;
}RFE_RFIN_TX_SHUTDOWN_BBP_STRU;


typedef union
{
    RFE_RFIN_RX_ON_BBP_STRU             stRxOnBbp;
    RFE_RFIN_RX_OFF_BBP_STRU            stRxOffBbp;
    RFE_RFIN_RX_SHUTDOWN_BBP_STRU       stRxShutBbp;
    RFE_RFIN_RX_FREQ_BBP_STRU           stRxFreqBbp;
    RFE_RFIN_RX_AGC_BBP_STRU            stRxAgcBbp;
    RFE_RFIN_RX_INTER_FLAGON_BBP_STRU   stRxInterFlagOn;
    RFE_RFIN_RX_INTRA_FLAGON_BBP_STRU   stRxIntraFlagOn;
    RFE_RFIN_TX_ON_BBP_STRU             stTxOnBbp;
    RFE_RFIN_TX_OFF_BBP_STRU            stTxOffBbp;
    RFE_RFIN_TX_APC_BBP_STRU            stTxApcBbp;
    RFE_RFIN_TX_SHUTDOWN_BBP_STRU       stTxShutDownBbp;
}RFE_RFIN_RX_BBP_UNION;
typedef struct
{
    RF_RFIC_SSI_CMD_STRU                stSsiCfg;
    RFD_MIPI_SWITCH_STRU                stMipiCfg;
    RFE_RFIN_RX_BBP_UNION               unRfinCfg;
}RFE_RFIN_OM_RPT_STRU;
#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __RFD_OM_DEF_H__ */

