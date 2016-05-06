/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
 文 件 名   : rfe_om_def.h
 版 本 号   : 初稿
 作    者   : wangxu
 生成日期   : 2011年4月25日
 最近修改   :
 功能描述   : RFE OM 的头文件
 函数列表   :
 修改历史   :
 1.日    期   : 2011年4月25日
   作    者   : wangxu
   修改内容   : 创建文件
 --------------------------------------------------------------------------------
2.日  期   : 2011年 10 月 14日
   作  者   : shijiahong
   修改内容 : DTS2011101403388 合Hi6360可维可测
--------------------------------------------------------------------------------
3.日  期     : 2011年10月31日
  作  者     : wangxu
  修改内容   : DTS2011103100442 LCS PHASE I 代码合入

******************************************************************************/


#ifndef __RFE_OM_DEF_H__
#define __RFE_OM_DEF_H__

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
#define RFE_OM_READREG_NUM  12
#define     RFIC_EVT_SSIMAXNUM              (32)
#define     MIPI_MAX_NUM                    (30) /*以最小 mipi NV结构体为单位*/

#define  RFIN_Rx_Downlink                        (1 << 0)            /* */
#define  RFIN_Rx_DUMMY                           (1 << 1)            /* */
#define  RFIN_Rx_S                               (1 << 2)            /* */
#define  RFIN_Rx_S_DUMMY                         (1 << 3)            /* */
#define  RFIN_Tx_PUXCH                           (1 << 4)            /*PUSCH/PUCCH/PUSCH&PUCCH Long*/
#define  RFIN_Tx_PRACH                           (1 << 14)           /*PRACH 1~3 Long */
#define  RFIN_Tx_DUMMY                           (1 << 5)            /*no send*/
#define  RFIN_Tx_PUXCH_SHORTEN                   (1 << 6)            /*PUSCH/PUCCH/PUSCH&PUCCH Short*/
#define  RFIN_Tx_PRACH_SHORTEN                   (1 << 15)           /*PRACH 1~3 Short */
#define  RFIN_Tx_SRS_ONLY                        (1 << 7)            /*SRS On U Sfrm*/
#define  RFIN_Tx_PUXCH_SRS                       (1 << 8)            /* PUSCH&SRS/PUCCH&SRS/PUSCH&PUCCH&SRS*/
#define  RFIN_S_SRS_BOTH                         (1 << 9)            /* 2 SRS On S Sfrm*/
#define  RFIN_S_SRS_LAST                         (1 << 10)            /*2nd SRS On S Sfrm*/
#define  RFIN_S_SRS_SecondLAST                   (1 << 11)            /*1ST */
#define  RFIN_S_PRACH4                           (1 << 12)            /* */
#define  RFIN_S_PRACH4_DUMMY                     (1 << 13)            /* */
#define  RFIC_IDLE (0)
#define  RFIC_STANDBY (1)
#define  RFIC_RXON  (2)
#define  RFIC_TXON (3)


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
    LPHY_REQ_RFE_MBX_REPORT_ENA        = OM_CMD_ID(LPHY_RFE_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_RFE_NV_REPORT_ENA,
    LPHY_REQ_RFIN_DRV_REPORT_ENA,
    LPHY_REQ_RFE_REG_READ_ENA,
    LPHY_REQ_RFE_FIX_UL_POWER_ENA,
    LPHY_REQ_RFE_PCC_STATUS_REPORT_ENA,
    LPHY_REQ_RFE_SCC_STATUS_REPORT_ENA,
    LPHY_REQ_RFE_FORCE_CELL_STATUS_REPORT_ENA,
    LPHY_REQ_RFE_DLCH_STATUS_REPORT_ENA,
    LPHY_REQ_RFE_ULCH_STATUS_REPORT_ENA,
    LPHY_REQ_RFE_FORCE_CH_STATUS_REPORT_ENA,
    LPHY_REQ_RFE_FPU_CELL_CONFIG_REPORT_ENA,
    LPHY_REQ_RFE_DELAY_TIME_REPORT_ENA,
    LPHY_REQ_RFE_DL_CA_CONFIG_REPORT_ENA,
    LPHY_REQ_RFE_CC2CH_IDX_REPORT_ENA,
    LPHY_REQ_RFE_INFO_REPORT_ID,
}LPHY_REQ_RFE_INFO_ENUM;

typedef enum
{
    RFE_OM_SWITCH_OFF = LPHY_FALSE,
    RFE_OM_SWITCH_ON = LPHY_TRUE
}RFE_OM_SWITCH_ENUM;
typedef UINT16 RFE_OM_SWITCH_ENUM_UINT16;
typedef struct
{
    RFE_OM_SWITCH_ENUM_UINT16   enReportEn;    /*1 使能AFC状态上报*/
    UINT16                      usReserved;
}LPHY_REQ_RFE_REPORT_ENA_STRU;

typedef enum
{
    RFE_OM_INFO_TYPE_L1C_ITF                     = 0,
    RFE_OM_INFO_TYPE_SLAVE_TIME_RECOVER,
    RFE_OM_INFO_TYPE_RFIN_DL_CH_GROUP_INFO,
    RFE_OM_INFO_TYPE_RFIN_DL_EVENT
}RFE_OM_INFO_TYPE_ENUM;
typedef UINT16 RFE_OM_INFO_TYPE_ENUM_UINT16;

typedef enum
{
    RFE_CCA_CC_INVALID = 0,
    RFE_CCA_CC_PRIMARY ,
    RFE_CCA_CC_SECOND
}RFE_CCA_CC_TYPE_ENUM;

typedef UINT16 RFE_CCA_CC_TYPE_ENUM_UINT16;

typedef enum
{
    LPHY_RFE_PCC = 0,
    LPHY_RFE_SCC1,
    LPHY_RFE_SCC2,
    LPHY_RFE_SCC3,
    LPHY_RFE_NOGAP = 4, /* add for No Gap measurement use*/
    LPHY_RFE_INVALID_CC = 4
}LPHY_RFE_CC_ENUM;

typedef UINT16 LPHY_RFE_CC_ENUM_UINT16;
typedef enum
{
    PA_LOW_LEVEL = 0,
    PA_MID_LEVEL,
    PA_HIGH_LEVEL,
    PA_LEVEL_BUTT
}PA_LEVEL_INDEX_ENUM;

typedef UINT16 PA_LEVEL_INDEX_ENUM_UINT16;
typedef UINT8 PA_LEVEL_INDEX_ENUM_UINT08;

typedef enum
{
    RFE_UL_PATH0 = 0,
    RFE_UL_PATH1 = 1
}RFE_UL_PATH_ENUM;
typedef UINT16 RFE_UL_PATH_ENUM_UINT16;

typedef enum
{
    RFE_SET_RX_3072_DELAY_TIME = 0,
    RFE_SET_RX_6144_DELAY_TIME,
    RFE_SET_TX_3072_DELAY_TIME,
    RFE_SET_TX_6144_DELAY_TIME,
    RFE_SET_BOTH_3072_DELAY_TIME,
    RFE_SET_BOTH_6144_DELAY_TIME,
}RFE_DELAYTIME_TYPE_ENUM;
typedef UINT16 RFE_DELAYTIME_TYPE_ENUM_UINT16;

enum RFE_SAMPLE_RATE_ENUM
{
    RFE_SAMPLE_RATE_7_68M = 0,
    RFE_SAMPLE_RATE_15_36M,
    RFE_SAMPLE_RATE_30_72M,
    RFE_SAMPLE_RATE_61_44M
};
typedef UINT16 RFE_SAMPLE_RATE_ENUM_UINT16;

typedef struct
{
    RFE_OM_SWITCH_ENUM_UINT16   enEnable;
    LPHY_CA_CC_ENUM_UINT16      enCcIndex;
    RFE_UL_PATH_ENUM_UINT16     enTxPath;
    PA_LEVEL_INDEX_ENUM_UINT08  enPaLevel;
    UINT8                       ucApcCodeLessThan20;
}LPHY_REQ_REF_FIX_UL_POWER_STRU;

/*LPHY_REQ_RFE_INFO_REPORT_ID*/
typedef struct
{
    RFE_OM_INFO_TYPE_ENUM_UINT16    enRfeInfoType;
    RFE_OM_SWITCH_ENUM_UINT16       enRfeOmSwitch;
}LPHY_REQ_RFE_INFO_ENA_STRU;
typedef struct
{
    UINT32                            ucValidflg:1;         /*当前指令是否有效*/
    UINT32                            ucExWFlg:1;           /*是否采用扩展写发送方式,1是*/
    UINT32                            ucWatTime:8;          /*发送完等待时间*/
    UINT32                            ucSlaveid:4;          /*设备USID*/
    UINT32                            ucMipiAddr:8;         /*在MIPI设备中的偏移地址*/
    UINT32                            ucByteCnt:3;          /*如果是扩展指令，指明CNT*/
    UINT32                            ucBbpMipiPin:3;
    UINT32                            ulRsv:4;
} NV_MIPI_CMD_CTRL_OM_STRU;/*要和NV中定义的结构体NV_MIPI_CMD_CTRL_STRU保持一样*/
typedef struct
{
    NV_MIPI_CMD_CTRL_OM_STRU            stMipiCtrl;

    UINT8                            ucCmdByte0;
    UINT8                            ucCmdByte1;
    UINT8                            ucCmdByte2;
    UINT8                            ucCmdByte3;
}LPHY_MIPIDEV_CMD_OM_STRU;/*要和NV中定义的结构体LPHY_MIPIDEV_CMD_STRU保持一样*/
typedef struct
{
    RFE_OM_SWITCH_ENUM_UINT16    enReportEn;    /*1 使能AFC状态上报*/
    UINT16   usReserved;
    /*Reg*/
    UINT8    ucBbpRegNum;
    UINT8    ucSsiRegNum;
    UINT8    ucMipiRegNum;

#if (defined(LPHY_FEM_CHAN_COMB))
    UINT8    ucRficIdx;
#else
    UINT8    ucCtuIdx;
#endif

    UINT32   aulBbpAddr[RFE_OM_READREG_NUM];
    UINT32   aulSsiAddr[RFE_OM_READREG_NUM];
    NV_MIPI_CMD_CTRL_OM_STRU   astMipiCtrlInfo[RFE_OM_READREG_NUM];
}LPHY_REQ_RFE_REG_READ_ENA_STRU;
#if 0
/************************************************************
                           2. CNF数据结构定义
************************************************************/
typedef enum
{
    LPHY_CNF_AFC_FIX_PDM_ENA         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_CNF, 0x1),

}LPHY_CNF_AFC_ENUM;

typedef struct
{
    UINT32                  ulMsgId;    /*1 CNF消息ID*/
}LPHY_CNF_AFC_FIX_PDM_ENA_STRU;

#endif
/************************************************************
                           3. Sg数据结构定义
************************************************************/

/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum
{
    LPHY_TRACE_RFE_MBX                      = OM_CMD_ID(LPHY_RFE_MID, OM_TYPE_TRACE, 0x0),
    LPHY_TRACE_RFE_REG_READ,
    LPHY_TRACE_RFE_SCC_MBX,
    LPHY_TRACE_RFE_PCC_STATUS,
    LPHY_TRACE_RFE_SCC_STATUS,
    LPHY_TRACE_RFE_DLCH_STATUS,
    LPHY_TRACE_RFE_ULCH_STATUS,
    LPHY_TRACE_RFE_APC_PARA,

    LPHY_TRACE_RFE_UL_PARA,
    LPHY_TRACE_RFE_DELAY_TIME,
    LPHY_TRACE_RFE_IRAT_STATUS,
    LPHY_TRACE_RFE_CC2CH_IDX,
    LPHY_TRACE_RFE_NV,
    LPHY_TRACE_RFE_DL_CELLINFO,
    LPHY_TRACE_RFE_UL_CELLINFO,

    LPHY_TRACE_RFIN_EVT_RX_ON_CH0_RPT      = OM_CMD_ID(LPHY_RFE_MID, OM_TYPE_TRACE, 0x20),
    LPHY_TRACE_RFIN_EVT_RX_ON_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_ON_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_ON_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_ON_EX_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_ON_EX_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_ON_EX_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_ON_EX_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_INTERON_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERON_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERON_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERON_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_OFF_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_OFF_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_OFF_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_OFF_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_OFF_EX_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_OFF_EX_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_OFF_EX_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_OFF_EX_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_INTEROFF_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTEROFF_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTEROFF_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTEROFF_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_INTRA_FREQ_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_INTRA_FREQ_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_INTRA_FREQ_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_INTRA_FREQ_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_INTERFREQ_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERFREQ_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERFREQ_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERFREQ_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_SHUTDOWN_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_SHUTDOWN_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_SHUTDOWN_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_SHUTDOWN_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_AGC_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_AGC_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_AGC_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_AGC_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_AGC_EX_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_AGC_EX_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_AGC_EX_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_AGC_EX_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_INTERAGC_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERAGC_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERAGC_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERAGC_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_RX_INTRAFLAGON_RPT,
    LPHY_TRACE_RFIN_EVT_RX_INTERFLAGON_RPT,

    LPHY_TRACE_RFIN_EVT_RX_CLEAR_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_RX_CLEAR_CH1_RPT,
    LPHY_TRACE_RFIN_EVT_RX_CLEAR_CH2_RPT,
    LPHY_TRACE_RFIN_EVT_RX_CLEAR_CH3_RPT,

    LPHY_TRACE_RFIN_EVT_TX_ON_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_ON_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_ON_EX0_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_ON_EX0_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_ON_EX1_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_ON_EX1_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_OFF_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_OFF_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_OFF_EX_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_OFF_EX_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_SHUTDOWN_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_SHUTDOWN_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_AGC_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_AGC_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_AGC_EX0_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_AGC_EX0_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_AGC_EX1_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_AGC_EX1_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_SWITCHFREQ_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_SWITCHFREQ_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_SWITCHFREQON_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_SWITCHFREQON_CH1_RPT,

    LPHY_TRACE_RFIN_EVT_TX_CLEAR_CH0_RPT,
    LPHY_TRACE_RFIN_EVT_TX_CLEAR_CH1_RPT,
    //LPHY_TRACE_RFIN_EVT_TX_CLEAR_CH2_RPT,
    //LPHY_TRACE_RFIN_EVT_TX_CLEAR_CH3_RPT,
    //LPHY_TRACE_RFIN_EVT_TX_SWITCHFREQ_CH2_RPT,
    //LPHY_TRACE_RFIN_EVT_TX_SWITCHFREQ_CH3_RPT,
    LPHY_TRACE_RFIN_EVT_RX_IIP2_RPT,
    LPHY_TRACE_RFIN_EVT_MRX_RPT,
    LPHY_TRACE_RFIN_DVTY_DISABLE_CHB_RPT,
    LPHY_TRACE_RFIN_DVTY_DISABLE_CHCD_RPT,
    LPHY_TRACE_RFIN_DVTY_DISABLE_CHBCD_RPT,
    LPHY_TRACE_RFIN_DVTY_ENABLE_CHB_RPT,
    LPHY_TRACE_RFIN_DVTY_ENABLE_CHCD_RPT,
    LPHY_TRACE_RFIN_DVTY_ENABLE_CHBCD_RPT

}LPHY_TRACE_RFE_CTU_EVENT_ENUM;
typedef enum
{
    LPHY_TRACE_RFE_HI6360_BEFORE_CHANGEFRQ_EVT        = OM_CMD_ID(LPHY_RFE_MID, OM_TYPE_TRACE, 0x40),
    LPHY_TRACE_RFE_HI6360_AFTER_CHANGEFRQ_EVT

}LPHY_TRACE_RFE_HI6360_EVENT_ENUM;

/*L1C->L1B数据通道请求类型*/
enum RFE_REQ_TYPE_ENUM
{
    LTE_RFE_REQ_INVALID = 0,                        /*RFE 请求无效*/
    LTE_RFE_BAND_SCAN_REQ,                          /*小区搜索频段预处理、频点排序过程之一，设置频点和带宽（20M/1.4M）后返回rssi*/
    LTE_RFE_INIT_CS_REQ,                            /*初始频点搜索射频前端切换*/
    LTE_RFE_INIT_PBCH_NCELL_BCCH_START_REQ,         /*初始解广播或解邻区广播 初始解MIB SIB射频前端切换，启动AFC 定时跟踪*/
    LTE_RFE_NCELL_BCCH_RELEASE_REQ,                 /*初始解广播或解邻区广播释放，第二种情况数据通道需回切*/
    LTE_RFE_DL_PARA_CHANGE_REQ,                     /*数据通道当前小区系统参数变更请求，仅涉及带宽、发送天线数、TDD UL/DL配比 特殊子帧格式变化*/
    LTE_RFE_CAMP_REQ,                               /*驻留请求*/
//    LTE_RFE_NCELL_PBCH_PDSCH_REQ,                   /*邻区MIB解调请求*/
//    LTE_RFE_NCELL_2_MAIN_CELL_REQ,                  /*邻区SIB解调请求*/
    LTE_RFE_IDLE_2_CONN_REQ,                        /*进入连接态请求,原语解调建立专有PDSCH信道时发起*/
//    LTE_RFE_TX_OPEN_REQ,                            /*进入连接态请求,原语上行建立PUSCH信道时发起*/
    LTE_RFE_INTER_MEAS_NO_GAP_REQ,                  /*IDLE态异频测量请求*/
    LTE_RFE_INTER_MEAS_RELEAS_REQ,                  /*异频测量释放和GU occasion释放*/
    LTE_RFE_INTER_MEAS_GAP_REQ,                     /*连接态异频测量请求*/
    LTE_RFE_GU_OCCASION_REQ,                        /*GU occasion请求*/
    LTE_RFE_HO_REQ,                                 /*切换请求*/
    LTE_RFE_NOGAP_CONFIG_REQ,                                 /*无Gap请求*/
    LTE_RFE_NOGAP_START_REQ,                                 /*无Gap请求*/
    LTE_RFE_NOGAP_STOP_REQ,                                 /*无Gap请求*/
    LTE_RFE_NOGAP_DECONFIG_REQ                       /*无Gap请求*/
};
typedef UINT16 RFE_REQ_TYPE_ENUM_UINT16;

typedef enum
{
    RFE_NCBAND_0BAND = 0,
    RFE_NCBAND_1BAND,
    RFE_NCBAND_NBAND
}RFE_NCBAND_TYPE_ENUM;

typedef UINT16 RFE_NCBAND_TYPE_ENUM_UINT16;

typedef enum
{
    RFD_RX_ON_EVT = 0,
    RFD_RX_OFF_EVT,
    RFD_RX_SHUTDOWN_EVT,
    RFD_RX_FREQ_EVT,
    RFD_RX_AGC_EVT,
    RFD_TX_ON_EVT,
    RFD_TX_OFF_EVT,
    RFD_TX_SHUTDOWN_EVT,
    RFD_TX_APC_EVT,
    RFD_TX_FREQ_EVT,
    RFD_INTRA_FLAGON,
    RFD_INTER_FLAGON,
    RFD_DRV_EVT_BUTT
}RFD_DRV_EVT_ENUM;
typedef UINT16 RFD_DRV_EVT_ENUM_UINT16;
typedef enum
{
    SSI_RX_ON_EVT = 0,
    SSI_RX_OFF_EVT,
    SSI_RX_SHUTDOWN_EVT,
    SSI_RX_FREQ_EVT,
    SSI_RX_AGC_EVT,

    SSI_TX_ON_EVT,
    SSI_TX_OFF_EVT,
    SSI_TX_FREQ_EVT,
    SSI_TX_SWITCH_ON_EVT,
    SSI_TX_SHUTDOWN_EVT,
    SSI_TX_APC_EVT,

    SSI_EVT_BUTT
}RFD_SSI_EVT_ENUM;
typedef UINT16 RFD_SSI_EVT_ENUM_UINT16;
typedef enum
{
    MIPI_RX_ON_EVT = 0,

    MIPI_TX_ON_EVT,
    MIPI_TX_OFF_EVT,
    MIPI_TX_APC_EVT,

    MIPI_EVT_BUTT
}RFD_MIPI_EVT_ENUM;
typedef UINT16 RFD_MIPI_EVT_ENUM_UINT16;
typedef enum
{
    FPU_CC_TYPE_PCC = 0,
    FPU_CC_TYPE_CC1 ,
    FPU_CC_TYPE_CC2 ,
    FPU_CC_TYPE_CC3
}FPU_CC_TYPE_ENUM;

typedef  UINT16   RFE_FPU_CC_TYPE_ENUM_UINT16;

typedef enum
{
    RFE_INVALID_CA = 0,
    RFE_INTER_BAND_CA ,
    RFE_INTRA_BAND_CONTIGOUS_CA ,
    RFE_INTRA_BAND_NONCONTIGOUS_CA
}RFE_CA_TYPE_ENUM;
typedef UINT16 RFE_CA_TYPE_ENUM_UINT16;

typedef enum
{
    RFE_DL_SCELL_REQ = 0,
    RFE_UL_SCELL_REQ,
}RFE_SCELL_REQ_DLUL_ENUM;
typedef UINT8 RFE_SCELL_REQ_DLUL_ENUM_UINT08;

typedef enum
{
    RFE_CC_INVALID = 0,
    RFE_SINGLE_CC_ACT,
    RFE_CONTIGOUS_CA_ACT,
}RFE_ACT_CC_TYPE_ENUM;
typedef UINT16 RFE_ACT_CC_TYPE_ENUM_UINT16;

typedef enum
{
    RFE_CC_NO_PROC = 0,
    RFE_1TO2_HOLD,
    RFE_2TO1_HOLD,
    RFE_1TO1_NO_PROC,
    RFE_2TO2_NO_PROC,
    RFE_ACT1_TO1_START,
    RFE_ACT1_TO2_START,
    RFE_ACT2_TO2_START,
    RFE_DEACT_STOP,
    RFE_ONLY_CHCHANGE,
}RFE_CC_PROC_TYPE_ENUM;
typedef UINT16 RFE_CC_PROC_TYPE_ENUM_UINT16;

typedef enum
{
    SCELL_OFF                  = 0,
    SCELL_CFG_INACTIVE,
    SCELL_PRE_SYNC,
    SCELL_ACTIVE_ON,
    SCELL_MEAS_ON,
    SCELL_BOTH_ON
} RFE_SCELL_STATE_ENUM;
typedef  UINT16   RFE_SCELL_STATE_ENUM_UINT16;

typedef enum
{
    RFE_SCC_STATE_MOVE_NULL            = 0,
    RFE_SCC_OFF_TO_CFGINACTIVE,

    RFE_SCC_CFGINACTIVE_TO_OFF,
    RFE_SCC_CFGINACTIVE_TO_PRESYNC,
    RFE_SCC_CFGINACTIVE_TO_MACACTIVEON,
    RFE_SCC_CFGINACTIVE_TO_MEASACTIVEON,
    RFE_SCC_CFGINACTIVE_TO_BOTHON,

    RFE_SCC_PRESYNC_TO_OFF,
    RFE_SCC_PRESYNC_TO_CFGINACTIVE,
    RFE_SCC_PRESYNC_TO_MACACTIVEON,
    RFE_SCC_PRESYNC_TO_MEASACTIVEON,
    RFE_SCC_PRESYNC_TO_BOTHON,

    RFE_SCC_MACACTIVEON_TO_OFF,
    RFE_SCC_MACACTIVEON_TO_CFGINACTIVE,
    RFE_SCC_MACACTIVEON_TO_MEASACTIVEON,
    RFE_SCC_MACACTIVEON_TO_BOTHON,

    RFE_SCC_MEASACTIVEON_TO_OFF,
    RFE_SCC_MEASACTIVEON_TO_CFGINACTIVE,
    RFE_SCC_MEASACTIVEON_TO_MACACTIVEON,
    RFE_SCC_MEASACTIVEON_TO_BOTHON,

    RFE_SCC_BOTHON_TO_OFF,
    RFE_SCC_BOTHON_TO_CFGINACTIVE,
    RFE_SCC_BOTHON_TO_MACACTIVEON,
    RFE_SCC_BOTHON_TO_MEASACTIVEON,

}RFE_SCC_STATE_MOVE_ENUM;
typedef  UINT16  RFE_SCC_STATE_MOVE_ENUM_UINT16;

typedef enum
{
    RFE_SCC_FPU_FULL_CONFIG = 5,
    RFE_SCC_FPU_ONLY_TIMING_CONFIG
}RFE_SCC_FPU_CONFIG_ENUM;
typedef  UINT16  RFE_SCC_FPU_CONFIG_ENUM_UINT16;

typedef enum
{
	RFE_TIMING_SWITCH_INVALID = 0,
	RFE_TIMING_SWITCH_FROME_DEM,
	RFE_TIMING_SWITCH_FROME_CSU
}RFE_TIMING_SWITCH_ENUM;
typedef  UINT16  RFE_TIMING_SWITCH_ENUM_UINT16;

typedef enum
{
    RFE_OM_EMCS_REQ_BAND_SCAN               = 0,
    RFE_OM_EMCS_REQ_FREE_CELL_SEARCH ,
    RFE_OM_EMCS_REQ_INTER_MEAS,
    RFE_OM_EMCS_REQ_INTER_MEAS_FINISH,
    RFE_OM_EMCS_REQ_INTER_SRCH_FINISH,
    RFE_OM_EMCS_REQ_INTER_MEAS_RELEASE,
    RFE_OM_EMCS_REQ_GAP_INTER_MODE,
    RFE_OM_EMCS_REQ_W_OCCASION,
    RFE_OM_EMCS_REQ_G_RSSI_OCCASION,
    RFE_OM_EMCS_REQ_G_BSIC_VERIFY_OCCASION,
    RFE_OM_EMCS_REQ_G_BSIC_CONFIRM_OCCASION,
    RFE_OM_EMCS_REQ_OCCASION_RELEASE,
    RFE_OM_EMCS_REQ_SLAVE_OCCASION_REQ,
//#ifdef BALONGV7_FEATURE_LCS
    RFE_OM_EMCS_REQ_LCS_OCCASION_REQ
//#endif
}RFE_OM_EMCS_REQ_TYPE_ENUM;
typedef UINT16 RFE_OM_EMCS_REQ_TYPE_ENUM_UINT16;

typedef enum
{
    RFE_NORMAL_MODE = 0, /*正常业务模式*/
    RFE_EQUIP_MODE,    /*装备模式*/
    RFE_EQUIP_CAL_MODE /*装备校准模式*/
}RFE_WORK_MODE_ENUM;
typedef UINT16 RFE_WORK_MODE_ENUM_UINT16;

typedef enum
{
    RF_BAND_WIDTH_1D4M = 0,
    RF_BAND_WIDTH_3M,
    RF_BAND_WIDTH_5M,
    RF_BAND_WIDTH_10M,
    RF_BAND_WIDTH_15M,
    RF_BAND_WIDTH_20M,
    RF_BAND_WIDTH_30M,
    RF_BAND_WIDTH_40M,
    RF_BAND_WIDTH_BUTT
}RFE_RF_BAND_WIDTH_ENUM;

typedef  UINT16  RFE_RF_BAND_WIDTH_ENUM_UINT16;

typedef enum
{
    RFIN_SAMPLE_RATE_30_72M  =  0,
    RFIN_SAMPLE_RATE_15_36M,
    RFIN_SAMPLE_RATE_7_68M,
    RFIN_SAMPLE_RATE_61_44M
}RFIN_SAMPLE_RATE_ENUM;
typedef UINT16 LPHY_RFIN_SAMPLE_RATE_ENUM_UINT16;

typedef enum
{
    BAND_NV_INTRA = 0,
    BAND_NV_INTER,
    BAND_NV_BUTT
}FE_BAND_NV_ENUM;
typedef UINT16  FE_BAND_NV_ENUM_UINT16;

typedef enum
{
    RFIN_CH_NO_CFG = 0,
    RFIN_CH_CFGED,
    RFIN_CH_CFG_BUTT
}RFIN_CH_CFG_STAT_ENUM;
typedef UINT16 RFIN_CH_CFG_STAT_ENUM_UINT16;

typedef enum
{
    RFIN_CH_NO_ACT,
    RFIN_CH_ACTED,
    RFIN_CH_ACT_BUTT
}RFIN_CH_ACT_STAT_ENUM;
typedef UINT16 RFIN_CH_ACT_STAT_ENUM_UINT16;

typedef enum
{
    RFIN_CH_NO_COMB = 0,
    RFIN_CH_COMBED,
    RFIN_CH_COMB_BUTT
}RFIN_CH_COMB_STAT_ENUM;
typedef UINT16 RFIN_CH_COMB_STAT_ENUM_UINT16;

typedef enum
{
    RFIN_CH_NOT_BAK = 0,
    RFIN_CH_BAKED,
    RFIN_CH_BAK_BUTT
}RFIN_CH_BAK_STAT_ENUM;
typedef UINT16 RFIN_CH_BAK_STAT_ENUM_UINT16;

typedef enum
{
    RFIN_DL_INTRA_EVT = 0,
    RFIN_DL_INTER_EVT
}RFIN_DL_EVT_TYPE_ENUM;
typedef UINT16 RFIN_DL_EVT_TYPE_ENUM_UINT16;

typedef enum
{
    RFE_1BAND_NV,
    RFE_NBAND_NV
}RFE_NV_TYPE_ENUM;
typedef UINT16 RFE_NV_TYPE_ENUM_UINT16;

typedef enum
{
    RFIN_TX_CLEAR_INVALID = 0,
    RFIN_TX_CLEAR_1CH,
    RFIN_TX_CLEAR_2CH
}RFIN_TX_CLEAR_IND_ENUM;
typedef UINT16 RFIN_TX_CLEAR_IND_ENUM_UINT16;

typedef enum
{
    RFIN_UL_NO_CA = 0,
    RFIN_UL_CA,
    RFIN_UL_PCC_CFG_CA,
    RFIN_UL_SCC_CFG_CA
}RFIN_UL_CH_CA_IND_ENUM;
typedef UINT16 RFIN_UL_CH_CA_IND_ENUM_UINT16;

typedef enum
{
    RFIN_Rx_Downlink_SFM            = RFIN_Rx_Downlink,
    RFIN_Rx_DUMMY_SFM               = RFIN_Rx_DUMMY,
    RFIN_Rx_S_SFM                   = RFIN_Rx_S,
    RFIN_Rx_S_DUMMY_SFM             = RFIN_Rx_S_DUMMY,
    RFIN_Tx_PUXCH_SFM               = RFIN_Tx_PUXCH,           /*PUSCH/PUCCH/PUSCH&PUCCH Long*/
    RFIN_Tx_PRACH_SFM               = RFIN_Tx_PRACH,           /*PRACH 1~3 Long */
    RFIN_Tx_DUMMY_SFM               = RFIN_Tx_DUMMY,            /*no send*/
    RFIN_Tx_PUXCH_SHORTEN_SFM       = RFIN_Tx_PUXCH_SHORTEN,     /*PUSCH/PUCCH/PUSCH&PUCCH Short*/
    RFIN_Tx_PRACH_SHORTEN_SFM       = RFIN_Tx_PRACH_SHORTEN,           /*PRACH 1~3 Short */
    RFIN_Tx_SRS_ONLY_SFM            = RFIN_Tx_SRS_ONLY,            /*SRS On U Sfrm*/
    RFIN_Tx_PUXCH_SRS_SFM           = RFIN_Tx_PUXCH_SRS,            /* PUSCH&SRS/PUCCH&SRS/PUSCH&PUCCH&SRS*/
    RFIN_S_SRS_BOTH_SFM             = RFIN_S_SRS_BOTH,            /* 2 SRS On S Sfrm*/
    RFIN_S_SRS_LAST_SFM             = RFIN_S_SRS_LAST,            /*2nd SRS On S Sfrm*/
    RFIN_S_SRS_SecondLAST_SFM       = RFIN_S_SRS_SecondLAST,            /*1ST */
    RFIN_S_PRACH4_SFM               = RFIN_S_PRACH4,
    RFIN_S_PRACH4_DUMMY_SFM         = RFIN_S_PRACH4_DUMMY
}RFE_SFM_TYPE_ENUM;
typedef UINT32 RFE_SFM_TYPE_ENUM_UINT32;

typedef enum
{
    RFIC_IDLE_TYPE     = RFIC_IDLE,
    RFIC_STANDBY_TYPE  = RFIC_STANDBY,
    RFIC_RXON_TYPE     = RFIC_RXON,
    RFIC_TXON_TYPE     = RFIC_TXON,
    RFIC_STATE_BUTT
}RFIC_STATE_TYPE_ENUM;
typedef UINT16 RFIC_STATE_TYPE_ENUM_UINT16;

typedef enum
{
    RFIN_IDLE_TO_STANDBY = ((RFIC_IDLE << 8)    | RFIC_STANDBY),
    RFIN_STANDBY_TO_IDLE = ((RFIC_STANDBY << 8) | RFIC_IDLE),
    RFIN_IDLE_TO_RXON    = ((RFIC_IDLE << 8)    | RFIC_RXON),
    RFIN_STANDBY_TO_RXON = ((RFIC_STANDBY << 8) | RFIC_RXON),
    RFIN_RXON_TO_IDLE    = ((RFIC_RXON << 8)    | RFIC_IDLE),
    RFIN_RXON_TO_STANDBY = ((RFIC_RXON << 8)    | RFIC_STANDBY),
    RFIN_RXON_TO_TXON    = ((RFIC_RXON << 8)    | RFIC_TXON),
    RFIN_IDLE_TO_TXON    = ((RFIC_IDLE << 8)    | RFIC_TXON),
    RFIN_STANDBY_TO_TXON = ((RFIC_STANDBY << 8) | RFIC_TXON),
    RFIN_TXON_TO_IDLE    = ((RFIC_TXON << 8)    | RFIC_IDLE),
    RFIN_TXON_TO_STANDBY = ((RFIC_TXON << 8)    | RFIC_STANDBY),
    RFIN_TXON_TO_RXON    = ((RFIC_TXON << 8)    | RFIC_RXON),
    RFIN_RX_AGC_TO_AGC,
    RFIN_TX_APC_TO_APC_PRACH,
    RFIN_TX_APC_TO_APC_PUSCH_PUCCH,
    RFIN_TX_APC_TO_APC_SRS,
    RFIN_NO_CHANGE       =  0xFFFF
}RFIN_STATE_MOVE_TYPE_ENUM;
typedef UINT16 RFIN_STATE_MOVE_TYPE_ENUM_UINT16;

typedef enum
{
    RFIN_UL_PRACH_CH    = 0,
    RFIN_UL_PUSCH_PUCCH_CH,
    RFIN_UL_SRS_CH,
    RFIN_UL_CH_BUTT
}RFIN_UL_CH_TYPE_ENUM;

typedef UINT16 RFIN_UL_CH_TYPE_ENUM_UINT16;

typedef struct
{
    UINT8 ucUlRfChIdx;       //pusch使能标志
    UINT8 ucRsv;
    UINT16 usApcCode;
    UINT16 usPaLevel;
    UINT16 usAptPdmVal;
    UINT16 enUlCcIdx;
    RFIN_UL_CH_TYPE_ENUM_UINT16  enUlChType;
} LTE_RFIN_UL_APC_INFO_STRU;

/*LPHY_TRACE_RFE_CTU_LTE_INT0_EVT ~ LPHY_TRACE_RFE_CTU_GSM_INT6_EVT*/
typedef struct
{
    UINT32  ulCtuInfo[6];
}LPHY_TRACE_RFE_CTU_EVENT_STRU;
typedef struct
{
    UINT32  ulHi6360Info[6];
}LPHY_TRACE_RFE_HI6360_EVENT_STRU;

typedef struct
{
    UINT16                              usGUOccasionLen;      /*GU occasion长度*/
    UINT8                               ucGUOccasionType;     /*GU occasion类型*/
    UINT8                               ucWDchSwfreqFlag;     /*W连接态频点更换指示*/
}LTE_RFE_IRAT_CONFIG_STRU;
typedef struct
{
    UINT16                              usUlFreqInfo;         /*上行频点*/
    LTE_BAND_WIDTH_ENUM_UINT16          enULBandWidth;            /*上行行系统带宽*/
    UINT16                              usUlBandNum;          /*上行BAND*/
    UINT8                               ucUlConfigValidFlg;   /*上行配置有效标识*/
    UINT8                               ucRsv;
}LTE_RFE_UL_CELLINFO_STRU;
/*L1C->L1B数据通道请求结构体类型定义*/
typedef struct{
    LTE_CELL_INFO_STRU                  stCellDlInfo;         /*小区下行参数*/
    LTE_DUAL_PSS_SCAN_INFO_STRU         stDualPssScanInfo;     /*并行扫频参数*/
    RFE_REQ_TYPE_ENUM_UINT16            enRfeReqType;         /*射频前端请求类型*/
    UINT16                              usUlFrequency;        /*上行频点*/
    LTE_BAND_WIDTH_ENUM_UINT16          enUlBw;               /*上行行系统带宽*/
    RFE_CCA_CC_TYPE_ENUM_UINT16         enCcaCcType;
    LPHY_RFE_CC_ENUM_UINT16             en2ndCcIdx;
    UINT16                              usPdm;                /*AFC PDM值（初始小区搜索,重选、切换时赋值）*/
    UINT32                              ulFramePosition;      /*小区帧定时*/
    UINT16                              usUlBandNum;          /*上行BAND*/
    UINT16                              usGUOccasionLen;      /*GU occasion长度*/
    UINT8                               ucUlConfigValidFlg;   /*上行配置有效标识*/
    UINT8                               ucGUOccasionType;     /*GU occasion类型*/
    UINT8                               ucWDchSwfreqFlag;     /*W连接态频点更换指示*/
    UINT8                               ucSccIndex;
} LTE_RFE_REQ_STRU;
typedef struct
{
    UINT32   ulAddr;
    UINT32   ulData;
}RFE_REG_STRU;
typedef struct
{
    UINT8    ucBbpRegNum;
    UINT8    ucSsiRegNum;
    UINT8    ucMipiRegNum;
    UINT8    ucReserved;
    UINT32   aulSsiReg[RFE_OM_READREG_NUM];
    LPHY_MIPIDEV_CMD_OM_STRU    astMipiReg[RFE_OM_READREG_NUM];
    RFE_REG_STRU                astBbpReg[RFE_OM_READREG_NUM];
}LPHY_TRACE_RFE_REG_READ_STRU;

typedef struct{
    UINT32                          *pBandNvDestBuf;    /*NV TCM addr*/
    UINT32                          *pBandNvSrcBuf;     /*NV DDR addr*/
    FE_BAND_NV_ENUM_UINT16          usBandType;         /*NV Load type*/
    UINT16                          usBand;
    UINT16                          usValidFlag;
    UINT16                          usReserved;
} LTE_RFE_NV_TRACE_STRU;
typedef struct
{
    RFE_FPU_CC_TYPE_ENUM_UINT16 enFpuCcIdx;
    UINT16  usReserved;
    UINT8   ucRecvAntNumFpu;
    UINT8   ucTransAntNumFpu;
    UINT8   ucDwptsLen;
    UINT8   ucSampingRate;
}RFE_FPU_CELL_CONFIG_STRU;
/*L1C->L1B数据通道请求结构体类型定义*/

typedef struct{
    UINT16                          usSingleIntraNvBand;
    UINT16                          usSingleInterNvBand;
    UINT16                          usInterNvUseFlag;
    UINT16                          usRsv;
} RFE_SINGLE_BAND_NV_INFO_STRU;

typedef struct
{
    LTE_CELL_INFO_STRU                  stCellDlInfo;         /*小区下行参数*/
    UINT16                               usULInfoCfgFlg;
    UINT16                              usUlFreqInfo;       /*上行频点*/
    LTE_BAND_WIDTH_ENUM_UINT16          enULBandWidth ;     /*上行带宽参数*/
    UINT16                              usUlBandNum;        /*上行BAND*/
    RFE_CA_TYPE_ENUM_UINT16             enCaType;
    LPHY_RFE_CC_ENUM_UINT16             enUl2ndCcIdx;
    RFE_CCA_CC_TYPE_ENUM_UINT16         enUlCcaCcType;

    RFE_REQ_TYPE_ENUM_UINT16            enRfeReqType;         /*射频前端请求类型*/

    LPHY_RFE_CC_ENUM_UINT16             enCcIdx;
    UINT8                               ucTxAntNumforAgc;     /*送给AGC发送天线数目，0表示盲检*/
    RFE_SCELL_REQ_DLUL_ENUM_UINT08      enDlUlFlag;
    UINT32                              ulFramePosition;      /*小区帧定时*/
} LTE_RFE_SCC_REQ_STRU;

/*RFIN EVT report*/
/*RFIN EVT report*/
typedef struct
{
    UINT32 ulEventTimeRef        : 3;
    UINT32 ulRsv0                : 13;
    UINT32 ulEventTime           : 16;
}RFE_RFIN_EVENT_TIME_CFG_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU stRfinEvtTime;
    RFIN_STATE_MOVE_TYPE_ENUM_UINT16 enRfinStatMoveType;    //高8bit表示RFIC历史状态，低8bit表示RFIC目标状态
    UINT16 usRsv;
}RFE_RFIN_EVENT_CFG_INFO_STRU;

typedef struct
{
    UINT32 ulSsiCfgFlag           : 1;
    UINT32 ulRsv0                 : 15;
    UINT32 ulSsiCfgTimeOffset     : 16;

    UINT32 ulSsiNum               : 8;
    UINT32 ulRsv2                 : 8;
    UINT32 ulSsiBufferBase        : 8;
    UINT32 ulRsv1                 : 8;

}RFE_RFIN_SSI_CFG_STRU;

typedef struct
{
    UINT32 ulMipiCfgFlag           : 1;
    UINT32 ulRsv0                  : 15;
    UINT32 ulMipiCfgTimeOffset     : 16;

    UINT32 ulMipiNum               : 9;
    UINT32 ulRsv2                 : 7;
    UINT32 ulMipiBufferBase        : 9;
    UINT32 ulRsv1                 : 7;

}RFE_RFIN_MIPI_CFG_STRU;

typedef struct
{
    UINT32 ulFpuDataEn          : 2;
    UINT32 ulRsv4               : 2;
    UINT32 ulAdiuEn             : 2;
    UINT32 ulRsv3               : 2;
    UINT32 ulAbbRxbEn           : 2;
    UINT32 ulRsv2               : 2;
    UINT32 ulAbbRxaEn           : 2;
    UINT32 ulRsv1               : 2;
    UINT32 ulRsv0               : 16;
}RFE_RFIN_RX_LINE_CFG_STRU;

typedef struct
{
    UINT32 ulLnaEnSel            : 1;
    UINT32 ulRsv1                : 3;
    UINT32 ulLnaEnIdx            : 2;
    UINT32 ulRsv0                : 26;
}RFE_RFIN_LNA_EN_CFG_STRU;

typedef struct
{
    UINT32 ulAntSelFlag            : 1;
    UINT32 ulRsv1                  : 3;
    UINT32 ulAntIdx                : 4;
    UINT32 ulRsv0                  : 8;
    UINT32 ulAntCfgTimeOffset      : 16;
}RFE_RFIN_ANT_EN_CFG_STRU;

typedef struct
{
    UINT32 ulEventEnFlag           : 1;
    UINT32 ulRsv0                  : 31;
}RFE_RFIN_EVENT_EN_CFG_STRU;

typedef struct
{
    UINT32 ulLnaModeSel           : 1;
    UINT32 ulRsv1                 : 15;
    UINT32 ulLnaModeIdx           : 2;
    UINT32 ulRsv0                 : 14;
}RFE_RFIN_LNA_MODE_CFG_STRU;

typedef struct
{
    UINT32 ulAbbCfgVld          : 2;
    UINT32 ulRsv0               : 30;
}RFE_RFIN_INTRA_FREQ_LINE_CFG_STRU;

typedef struct
{
    UINT32 ulFpuGapEn            : 2;
    UINT32 ulRsv5                : 2;
    UINT32 ulFpuInterIntra       : 2;
    UINT32 ulRsv4                : 2;
    UINT32 ulIntersysIngapPreInd : 2;
    UINT32 ulRsv3                : 2;
    UINT32 ulIntrasysValid       : 2;
    UINT32 ulRsv2                : 2;
    UINT32 ulIntrasysValidDelay  : 2;
    UINT32 ulRsv1                : 2;
    UINT32 ulInterFlagEn         : 2;
    UINT32 ulRsv0                : 10;
}RFE_RFIN_INTER_FLAG_LINE_CFG_STRU;

typedef struct
{
    UINT32 ulValidFlag             : 1;
    UINT32 ulResv1                 : 3;
    UINT32 ulDbbRate               : 2;
    UINT32 ulResv0                 : 10;
    UINT32 ulDbbRateTimeOffset     : 16;
}RFE_RFIN_DBB_RATE_CFG_STRU;

typedef struct
{
    UINT32 ulAbbTxEn            : 2;
    UINT32 ulRsv4               : 2;
    UINT32 ulETActEn            : 2;
    UINT32 ulRsv3               : 2;
    UINT32 ulRsv2               : 4;
    UINT32 ulAPTPdmEn           : 2;
    UINT32 ulRsv1               : 2;
    UINT32 ulRsv0               : 16;
}RFE_RFIN_TX_LINE_CFG_STRU;

typedef struct
{
    UINT32 ulPaModeSel            : 1;
    UINT32 ulRsv1                 : 15;
    UINT32 ulPaModeIdx            : 2;
    UINT32 ulRsv0                 : 14;
}RFE_RFIN_PA_MODE_CFG_STRU;

typedef struct
{
    UINT32 ulPaEnSel              : 1;
    UINT32 ulRsv1                 : 3;
    UINT32 ulPaEnIdx              : 2;
    UINT32 ulRsv0                 : 26;
}RFE_RFIN_PA_EN_CFG_STRU;

typedef struct
{
    UINT32 ulPdmModuSel           :1;
    UINT32 ulRsv0                 :15;
    UINT32 ulPdmModu              :16;
}RFE_RFIN_PDM_MODU_CFG_STRU;
typedef struct
{
    UINT16  ulRficCmdNum;
    UINT16  usChIdx;
    UINT32  aulSsiCmd[RFIC_EVT_SSIMAXNUM];
}RF_RFIC_SSI_CMD_STRU;



typedef struct
{
    UINT32 ulMipiCmdNum;
    UINT32 aulCmdBuffer[MIPI_MAX_NUM];
}RFD_MIPI_SWITCH_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU       stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU              stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU             stMipiCfg;
    RFE_RFIN_RX_LINE_CFG_STRU          stLineCfg;
    RFE_RFIN_LNA_EN_CFG_STRU           stLnaEnCfg;
    RFE_RFIN_ANT_EN_CFG_STRU           stAntEnCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU         stEventEnCfg;
}RFE_RFIN_RX_SWITCH_RFIN_STRU;

typedef struct
{
    RF_RFIC_SSI_CMD_STRU               stSsiCfg;
    RFD_MIPI_SWITCH_STRU               stMipiCfg;
    RFE_RFIN_RX_SWITCH_RFIN_STRU       stRfinCfg;
}RFE_RFIN_RX_SWITCH_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU       stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU              stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU             stMipiCfg;
    RFE_RFIN_RX_LINE_CFG_STRU          stLineCfg;
    RFE_RFIN_ANT_EN_CFG_STRU           stAntEnCfg;
    RFE_RFIN_LNA_EN_CFG_STRU           stLnaEnCfg;
    RFE_RFIN_LNA_MODE_CFG_STRU         dtLnaModeCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU         stEventEnCfg;
}RFE_RFIN_RX_DVTY_RFIN_STRU;
typedef struct
{
    RF_RFIC_SSI_CMD_STRU               stSsiCfg;
    //RFD_MIPI_SWITCH_STRU               stMipiCfg;
    RFE_RFIN_RX_DVTY_RFIN_STRU     stRfinCfg;
}RFE_RFIN_RX_DVTY_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU       stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU              stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU             stMipiCfg;
    RFE_RFIN_RX_LINE_CFG_STRU          stLineCfg;
    RFE_RFIN_LNA_EN_CFG_STRU           stLnaEnCfg;
    RFE_RFIN_LNA_MODE_CFG_STRU         dtLnaModeCfg;
    RFE_RFIN_ANT_EN_CFG_STRU           stAntEnCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU         stEventEnCfg;
}RFE_RFIN_RX_SHUTDOWN_RFIN_STRU;

typedef struct
{
    RF_RFIC_SSI_CMD_STRU               stSsiCfg;
    RFD_MIPI_SWITCH_STRU               stMipiCfg;
    RFE_RFIN_RX_SHUTDOWN_RFIN_STRU     stRfinCfg;
}RFE_RFIN_RX_SHUTDOWN_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU        stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU               stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU              stMipiCfg;
    RFE_RFIN_INTRA_FREQ_LINE_CFG_STRU   stLineCfg;
    RFE_RFIN_DBB_RATE_CFG_STRU          stDbbRateCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU          stEventEnCfg;
}RFE_RFIN_INTRA_FREQ_RFIN_STRU;

typedef struct
{
    RF_RFIC_SSI_CMD_STRU               stSsiCfg;
    RFD_MIPI_SWITCH_STRU               stMipiCfg;
    RFE_RFIN_INTRA_FREQ_RFIN_STRU      stRfinCfg;
}RFE_RFIN_INTRA_FREQ_STRU;

/*inter event*/
typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU        stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU               stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU              stMipiCfg;
    RFE_RFIN_INTRA_FREQ_LINE_CFG_STRU   stLineCfg;
    RFE_RFIN_DBB_RATE_CFG_STRU          stDbbRateCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU          stEventEnCfg;
}RFE_RFIN_INTER_FREQ_RFIN_STRU;
typedef struct
{
    RF_RFIC_SSI_CMD_STRU               stSsiCfg;
    RFD_MIPI_SWITCH_STRU               stMipiCfg;
    RFE_RFIN_INTER_FREQ_RFIN_STRU      stRfinCfg;
}RFE_RFIN_INTER_FREQ_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU        stEvtTimeCfg;
    RFE_RFIN_INTER_FLAG_LINE_CFG_STRU   stLineCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU          stEventEnCfg;
}RFE_RFIN_INTER_FLAG_ON_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU        stEvtTimeCfg;
    RFE_RFIN_INTER_FLAG_LINE_CFG_STRU   stLineCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU          stEventEnCfg;
}RFE_RFIN_INTAR_FLAG_ON_STRU;


typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU        stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU               stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU              stMipiCfg;
    RFE_RFIN_LNA_MODE_CFG_STRU          stLnaModCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU          stEventEnCfg;
}RFE_RFIN_RX_AGC_RFIN_STRU;

typedef struct
{
    RF_RFIC_SSI_CMD_STRU                stSsiCfg;
    RFD_MIPI_SWITCH_STRU                stMipiCfg;
    RFE_RFIN_RX_AGC_RFIN_STRU           stRfinCfg;
}RFE_RFIN_RX_AGC_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU       stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU              stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU             stMipiCfg;
    UINT32                             usRsv;
    RFE_RFIN_TX_LINE_CFG_STRU          stLineCfg;
    RFE_RFIN_PA_EN_CFG_STRU            stPaEnCfg;
    RFE_RFIN_ANT_EN_CFG_STRU           stAntEnCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU         stEventEnCfg;
}RFE_RFIN_TX_SWITCH_RFIN_STRU;

typedef struct
{
    RF_RFIC_SSI_CMD_STRU               stSsiCfg;
    RFD_MIPI_SWITCH_STRU               stMipiCfg;
    RFE_RFIN_TX_SWITCH_RFIN_STRU       stRfinCfg;
}RFE_RFIN_TX_SWITCH_STRU;


typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU       stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU              stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU             stMipiCfg;
    RFE_RFIN_TX_LINE_CFG_STRU          stLineCfg;
    RFE_RFIN_PA_EN_CFG_STRU            stPaEnCfg;
    RFE_RFIN_ANT_EN_CFG_STRU           stAntEnCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU         stEventEnCfg;
}RFE_RFIN_CLEAR_TX_SWITCH_RFIN_STRU;
typedef struct
{
    //RF_RFIC_SSI_CMD_STRU               stSsiCfg;
    RFD_MIPI_SWITCH_STRU               stMipiCfg;
    RFE_RFIN_CLEAR_TX_SWITCH_RFIN_STRU stRfinCfg;
}RFE_RFIN_CLEAR_TX_SWITCH_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU       stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU              stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU             stMipiCfg;
    RFE_RFIN_PA_MODE_CFG_STRU          stPaModeCfg;
    RFE_RFIN_PDM_MODU_CFG_STRU         stPdmModuCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU         stEventEnCfg;
}RFE_RFIN_TX_AGC_RFIN_STRU;
typedef struct
{
    RF_RFIC_SSI_CMD_STRU               stSsiCfg;
    RFD_MIPI_SWITCH_STRU               stMipiCfg;
    RFE_RFIN_TX_AGC_RFIN_STRU          stRfinCfg;
}RFE_RFIN_TX_AGC_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU       stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU              stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU             stMipiCfg;
	UINT32                             usRsv;
    RFE_RFIN_TX_LINE_CFG_STRU          stLineCfg;
    RFE_RFIN_PA_MODE_CFG_STRU          stPaModeCfg;
    RFE_RFIN_PA_EN_CFG_STRU            stPaEnCfg;
    RFE_RFIN_ANT_EN_CFG_STRU           stAntEnCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU         stEventEnCfg;
}RFE_RFIN_TX_SHUTDOWN_RFIN_STRU;
typedef struct
{
    RF_RFIC_SSI_CMD_STRU               stSsiCfg;
    RFD_MIPI_SWITCH_STRU               stMipiCfg;
    RFE_RFIN_TX_SHUTDOWN_RFIN_STRU     stRfinCfg;
}RFE_RFIN_TX_SHUTDOWN_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU        stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU               stSsiCfg;
    UINT32                              ulRsv[3];
    RFE_RFIN_EVENT_EN_CFG_STRU          stEventEnCfg;
}RFE_RFIN_RX_IIP2_RFIN_STRU;

typedef struct
{
    RF_RFIC_SSI_CMD_STRU               stSsiCfg;
    RFD_MIPI_SWITCH_STRU               stMipiCfg;
    RFE_RFIN_RX_IIP2_RFIN_STRU         stRfinCfg;
}RFE_RFIN_RX_IIP2_STRU;

typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU        stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU               stSsiCfg;
    UINT32                              aulRsv[5];
    RFE_RFIN_EVENT_EN_CFG_STRU          stEventEnCfg;
}RFE_RFIN_MRX_RFIN_STRU;
typedef struct
{
    RF_RFIC_SSI_CMD_STRU               stSsiCfg;
    RFD_MIPI_SWITCH_STRU               stMipiCfg;
    RFE_RFIN_MRX_RFIN_STRU             stRfinCfg;
}RFE_RFIN_MRX_STRU;
typedef struct
{
    RFE_RFIN_EVENT_TIME_CFG_STRU       stEvtTimeCfg;
    RFE_RFIN_SSI_CFG_STRU              stSsiCfg;
    RFE_RFIN_MIPI_CFG_STRU             stMipiCfg;
       UINT32                             ulRsv;
    RFE_RFIN_PA_MODE_CFG_STRU          stPaModeCfg;
    RFE_RFIN_PDM_MODU_CFG_STRU         stPdmModuCfg;
    RFE_RFIN_EVENT_EN_CFG_STRU         stEventEnCfg;
}RFE_RFIN_TX_APC_RFIN_STRU;
typedef struct
{
    RF_RFIC_SSI_CMD_STRU               stSsiCfg;
    RFD_MIPI_SWITCH_STRU               stMipiCfg;
    RFE_RFIN_TX_APC_RFIN_STRU          stRfinCfg;
}RFE_RFIN_TX_APC_STRU;

typedef struct
{
    LTE_CELL_INFO_STRU                  stCellDlInfo;
    UINT16                              usULInfoCfgFlg;     /*上行配置信息有效标志*/
    UINT16                              usUlFreqInfo;       /*上行频点*/
    LTE_BAND_WIDTH_ENUM_UINT16          enULBandWidth ;     /*上行带宽参数*/
    UINT16                              usUlBandNum;        /*上行BAND*/


    RFE_REQ_TYPE_ENUM_UINT16            enRfeReqType;       /*射频前端请求类型*/
    UINT8                               ucTxAntNumforAgc;   /*不使用，使用PCC的*/
    UINT8                               ucUlTransAntNum;    /*UE 上行发送天线数目*/
    UINT32                              ulSccFramePos;      /*Scell 小区帧定时,配置使用的 0.25 ts*/
    UINT32                              ulSccFramePosOld;   /*scell frame head isn't exist, use pcell as old  0.25 ts*/

    RFE_FPU_CC_TYPE_ENUM_UINT16         en1stFpuCcIdx;
    RFE_FPU_CC_TYPE_ENUM_UINT16         en2ndFpuCcIdx;

    RFE_CA_TYPE_ENUM_UINT16             enCaType;
    RFE_CCA_CC_TYPE_ENUM_UINT16         enCcaCcType;
    LPHY_RFE_CC_ENUM_UINT16             en2ndCcIdx;

    RFE_ACT_CC_TYPE_ENUM_UINT16         enActCcType;

    RFE_CC_PROC_TYPE_ENUM_UINT16        enCcProType;
    UINT8                               ucOldFreqSwitchInd;
    UINT8                               ucNewFreqSwitchInd;

    RFE_CA_TYPE_ENUM_UINT16             enUlCaType;
    RFE_CCA_CC_TYPE_ENUM_UINT16         enUlCcaCcType;

    LPHY_RFE_CC_ENUM_UINT16             enUl2ndCcIdx;

    UINT16                              usUlCfgCCaFlag;
    RFE_SAMPLE_RATE_ENUM_UINT16         enUlSampleRate;

    UINT8                               ucRxClearRfChIdx;  //rx clear
    UINT8                               ucTxClearRfChIdx[2]; //tx clear
    UINT8                               ucCaWithPccFlag;
    UINT16                              usCcCenterFreq;      /*cc center  freq*/

    RFE_RF_BAND_WIDTH_ENUM_UINT16       enCcBw;
    RFE_SCELL_STATE_ENUM_UINT16         enScellState;

    RFE_SCC_STATE_MOVE_ENUM_UINT16      enScellMoveState;

    UINT16                              usDlIntraBandIdx;

    UINT16                              usUlIntraBandIdx;
    UINT8                               ucCfgInActiveReq;
    UINT8                               ucDeCfgInActiveReq;

    UINT8                               ucMacActiveReq;
    UINT8                               ucMacInActiveReq;
    UINT8                               ucMeasActiveReq;
    UINT8                               ucMeasInActiveReq;

    UINT8                               ucOtdoaActiveReq;
    UINT8                               ucOtdoaInActiveReq;

    UINT8                               ucMeasValidFlag;
    UINT8                               ucOtdoaValidFlag;

    /*align*/
    UINT8                               ucFpuActFlag;        /*for fpu sym10 config  */
    UINT8                               ucFpuInActFlag;      /*for fpu sym10 config  */
	UINT8                               ucReSyncFlag;
    UINT8                               ucRfChIdx;

    UINT8                               ucDlNewCfgInd;
    UINT8                               ucUlNewCfgInd;

    UINT16                              usDlRfPathIndex;
    UINT8                              ucRficIdx;
	UINT8                              ucUlRficIdx;
    UINT16                              usUlRfPathIndex;
    UINT8                              ucRfRxSel;         /*rfic abcd选择*/
    UINT8                              ucRsv[2];
    UINT8                              ucTddRficFirstOnFlag;
    //UINT8                               ucNonCcInActDelay;   /*for scc fpu delay next subfrm sym6 to deactivate*/
    UINT8                               ucScellActive;       /*dem  active deactive, 小区搜索搜到帧头为true*/
    /*align*/
    UINT8                               ucFrmHeadExist;      /*frame head exist or not*/
    UINT8                               ucMacTriWaitFlag;
    UINT8                               ucMeasTriWaitFlag;
    RFE_SCC_FPU_CONFIG_ENUM_UINT16      enSccFpuCfgMode;

    LTE_TDD_SUBFRAME_TYPE_ENUM_UINT16   enFpuNext1SfrmType;
    LTE_TDD_SUBFRAME_TYPE_ENUM_UINT16   enFpuNext2SfrmType;
    UINT16                              usRsvd;

	INT32                               lUlTpaDlt;
	RFE_TIMING_SWITCH_ENUM_UINT16       enTimeSwitchType;
	LPHY_RFE_CC_ENUM_UINT16             enCcIdx;
}RFE_STATUS_SCC_STRU;
typedef struct
{
    UINT16 usTxActInd                   : 1;
    UINT16 usTxEx0ActInd                : 1;
    UINT16 usTxEx1ActInd                : 1;
    UINT16 usTxDeActInd                 : 1;
    UINT16 usTxExDeActInd               : 1;
    UINT16 usCfgInd                     : 1;
    UINT16 usDeCfgInd                   : 1;
    UINT16 usRxClearInd                 : 1;
    UINT16 usFreqSwtichInd              : 1;
    UINT16 usTxApcInd                   : 1;
    UINT16 usTxApcEx0Ind                : 1;
    UINT16 usTxApcEx1Ind                : 1;
    UINT16 usRsv                        : 4;
	UINT16 usReserved;
}RFE_RFIN_UL_CH_ACTION_IND_STRU;

typedef struct
{
    UINT16 usActInd                 : 1;
    UINT16 usDeActInd               : 1;
    UINT16 usDeActExInd             : 1;
    UINT16 usCfgInd                 : 1;
    UINT16 usDeCfgInd               : 1;
    UINT16 usCombInd                : 1;
    UINT16 usDeCombInd              : 1;
    UINT16 usFlagOnInd              : 1;
    UINT16 usFreqSwtichInd          : 1;
    UINT16 usCtuUncloseInd          : 1;  //0表示要关闭
    UINT16 usSlaveModeInd           : 1;  // LTE slave mode, enter into occasion
    UINT16 usGuFlagOnInd            : 1;
	UINT16 usRficClearInd			: 1;  //清场标志
    UINT16 usAbbOnlyInd             : 1;
    UINT16 usRsv                    : 2;
	UINT16 usReserved;
}RFE_RFIN_DL_CH_ACTION_IND_STRU;

typedef struct
{
    UINT8                                     ucRfChIdx;      /* 通道ID */
    UINT8                                     ucRficIdx;      /* 通道rfic */
    UINT8                                     ucClearDlChIdx;  /* RxClearOff 行为对应的DL CH */
    UINT8                                     ucRfRxSel;      /* 对应的rx */
    UINT16                                    usUlRfChIndex;    /* 通道Band对应的RF CH*/
    UINT16                                    usRsv;

    RFIN_CH_CFG_STAT_ENUM_UINT16              enRfCfgStat;    /* 通道配置状态 */
    RFIN_CH_ACT_STAT_ENUM_UINT16              enRfActStat;    /* 通道激活状态 */

    RFE_WORK_MODE_ENUM_UINT16                 usWorkMode;    /*正常工作模式，或者装备模式*/
    UINT8                                     ucCtuChIdx;      /*对应的下行的ChIdx*/
    UINT8                                     ucCAInd;         /*通道对应的CA是否是激活状态*/

    RFIN_UL_CH_CA_IND_ENUM_UINT16             enUlChCaType;
    UINT16                                    usRsv1;

    LPHY_RFE_CC_ENUM_UINT16                   en1stCcIdx;
    LPHY_RFE_CC_ENUM_UINT16                   en2ndCcIdx;

    RFE_SCC_STATE_MOVE_ENUM_UINT16            en1stCcMoveState;
    RFE_SCC_STATE_MOVE_ENUM_UINT16            en2stCcMoveState;

    UINT16                                    usFreqInfo;               /*频点*/
    UINT16                                    usBandNum;                /*Band*/

    RFE_RF_BAND_WIDTH_ENUM_UINT16             enUlBandWidth;            /*带宽*/ //senUlBandWidth
    LTE_FRAME_TYPE_ENUM_UINT16                enDuplexMode;             /*帧类型:FDD or TDD*/

    LTE_CP_TYPE_ENUM_UINT16                   enCpType;                 /*cp类型*/
    UINT8                                     ucTransAntNum;            /* 发送天线数目 */
    UINT8                                     ucPaOnFlag;        /* 1--immediate en, 0--buffer time */

    LTE_TDD_SPEC_SUBFRM_CFG_ENUM_UINT16       enSpecSubframeCfg;        /* 特殊子帧配比 */
    RFE_NV_TYPE_ENUM_UINT16                   enNvType;                 /* NV类型，为RFE_1BAND_NV 还是RFE_NBAND_NV */

    //NV_SINGLE_BAND_FE_PARA_STRU               *pstNvParaPoint;          /* RFE_1BAND_NV */
    //NV_BAND_FE_UL_PARA_STRU                   *pstUlChPara;
    UINT32                                    *pstUlChPara;
    //NV_NCCA_UL_BAND_PARA_STRU                 *pstNcCaUlBandNvPoint;    /* RFE_NBAND_NV */
    UINT32                                    *pstNcCaUlBandNvPoint;    /* RFE_NBAND_NV */
    //NV_NCCA_UL_COMM_PARA_STRU                 *pstNcCaUlCommNvPoint;
    UINT32                                    *pstNcCaUlCommNvPoint;
    //NV_NCCA_DL_BAND_PARA_STRU                 *pstNcCaDlBandNvPoint;
    UINT32                                    *pstNcCaDlBandNvPoint;
    RFE_SFM_TYPE_ENUM_UINT32                  ulNext2SfrmType;          /* 假定当前子帧为N子帧，N+2子帧类型 */
    RFE_SFM_TYPE_ENUM_UINT32                  ulNext1SfrmType;          /* 假定当前子帧为N子帧，N+1子帧类型 */
    //RFE_RFIN_EVENT_TIME_CFG_STRU              stChActEvtTime; /*事件生效类型*/
    RFIN_STATE_MOVE_TYPE_ENUM_UINT16          enRfinStatMoveType;
	UINT16                                    usReserved;
    RFE_RFIN_UL_CH_ACTION_IND_STRU            stChActionInd;   /* 上行通道行为指示 */
}RFE_UL_RFIN_CHAN_INFO_STRU;
typedef struct
{

    UINT8                                     ucRfChIdx;       /* 通道ID */
    UINT8                                     ucCombRfChIdx;   /* 绑定通道ID */
    UINT16                                    usDlRfChIndex;    /* 通道Band对应的RF CH*/
    UINT8                                    ucRficIdx;
    UINT8                                    ucRfRxSel;         /*rfic abcd选择*/
    UINT16                                    usRsv;
    RFIN_STATE_MOVE_TYPE_ENUM_UINT16          enRfinStatMoveType;
    UINT8                                     ucTddChFisrtOnFlag;
    UINT8                                     ucReserved;

    RFIN_CH_COMB_STAT_ENUM_UINT16             enRfCombStat;    /* 通道绑定状态 */
    RFIN_CH_CFG_STAT_ENUM_UINT16              enRfCfgStat;     /* 通道配置状态 */
    RFIN_CH_ACT_STAT_ENUM_UINT16              enRfActStat;     /* 通道激活状态 */
    RFIN_CH_BAK_STAT_ENUM_UINT16              enChBakStat;     /* 通道备份状态 */
    RFIN_DL_EVT_TYPE_ENUM_UINT16              enRfinEvtType;   /*INter和Intra切频事件*/
    RFIN_TX_CLEAR_IND_ENUM_UINT16             enTxClearInd;             /* TxClearOff 行为指示 */

    /* TxClearOff 行为对应的Ul CH, 如果上行是MIMO，其对应的2个Ul CH在2个RFIC 上，需要对应2个UL CH */
    UINT8                                     ucClearUlChIdx[2];
    UINT8                                     ucOnlyCloseLineCtrlFlag;  /* 异频测量出沟仅关接收线控*/
    UINT8                                     ucCAInd;                 /*通道对应的CA是否是激活状态*/

    UINT8                                     ucPrimaryChFlag;         /*主载波所在通道有效标志位*/
    UINT8                                     ucFddForcedFlag;
    RFE_WORK_MODE_ENUM_UINT16                 usWorkMode;

    LPHY_RFE_CC_ENUM_UINT16                   en1stCcIdx;
    LPHY_RFE_CC_ENUM_UINT16                   en2ndCcIdx;
    LPHY_RFE_CC_ENUM_UINT16                   enDeAct1stCcIdx;    /* 当前子帧第一个去激活的载波索引 */
    LPHY_RFE_CC_ENUM_UINT16                   enDeAct2ndCcIdx;  /* 当前子帧第二个去激活的载波索引 */

    RFE_SCC_STATE_MOVE_ENUM_UINT16            en1stCcMoveState;
    RFE_SCC_STATE_MOVE_ENUM_UINT16            en2stCcMoveState;
    UINT16                                    usFreqInfo;               /*频点*/
    UINT16                                    usBandNum;                /*Band*/
    RFE_RF_BAND_WIDTH_ENUM_UINT16             enDlBandWidth;            /*带宽*/
    LTE_FRAME_TYPE_ENUM_UINT16                enDuplexMode;             /*帧类型:FDD or TDD*/

    LTE_CP_TYPE_ENUM_UINT16                   enCpType;                 /*cp类型*/
    UINT8                                     ucRecvAntNum;             /* 接收天线数目 */
    UINT8                                     ucActRecvAntNum;

    LTE_TDD_SPEC_SUBFRM_CFG_ENUM_UINT16       enSpecSubframeCfg;        /* 特殊子帧配比 */
    RFE_NV_TYPE_ENUM_UINT16                   enNvType;                 /* NV类型，为RFE_1BAND_NV 还是RFE_NBAND_NV */

    UINT32                                    *pstDlChPara;
    //NV_BAND_FE_DL_PARA_STRU                   *pstDlChPara;
    UINT32                                    *pstNcCaDlBandNvPoint;        /* RFE_NBAND_NV */
    //NV_NCCA_DL_BAND_PARA_STRU                 *pstNcCaDlBandNvPoint;        /* RFE_NBAND_NV */
    UINT32                                    *pstNcCaDlCommNvPoint;         /*NCCA DL Band 公共参数*/
    //NV_NCCA_DL_COMM_PARA_STRU                 *pstNcCaDlCommNvPoint;         /*NCCA DL Band 公共参数*/
    UINT32                                    *pstNcCaUlBandNvPoint;        /*NCCA UL 各Band  私有参数*/
    //NV_NCCA_UL_BAND_PARA_STRU                 *pstNcCaUlBandNvPoint;        /*NCCA UL 各Band  私有参数*/
    RFE_SFM_TYPE_ENUM_UINT32                  ulNextSfrmType;           /* 假定当前子帧为N子帧，N+1子帧类型 */
    RFE_SFM_TYPE_ENUM_UINT32                  ulCurrSfrmType;           /* 当前子帧类型，N子帧类型 */

    RFE_RFIN_DL_CH_ACTION_IND_STRU            stChActionInd;            /* 下行通道行为指示 */

}RFE_RFIN_CHAN_INFO_STRU;

typedef struct
{
    UINT16  usCcIndex;
    RFE_DELAYTIME_TYPE_ENUM_UINT16  enType;
	UINT16  usRxChDlyTime;                  /*下行通道延迟补偿,T8,空口到基带的硬件器件延迟*/
	UINT16  usTxChDlyTime;                  /*上行通道延迟补偿,tul*/
}RFE_CH_DELAY_TIMER_STRU;
/************************************************************
                           5. ERROR数据结构定义
************************************************************/
/************************************************************
                           7. Ind数据结构定义
************************************************************/
typedef enum
{
    LPHY_IND_RFE_L1C_DEM_CMD_ID               = OM_CMD_ID(LPHY_RFE_MID, OM_TYPE_IND, 0x0),
    LPHY_IND_RFE_L1C_EMCS_CMD_ID,
    LPHY_IND_RFE_TIME_RCVR_IND_ID,

    LPHY_IND_RFE_RFIN_DL_CH_GROUP0_IND_ID,
    LPHY_IND_RFE_RFIN_DL_CH_GROUP1_IND_ID,
    LPHY_IND_RFE_RFIN_DL_CH_GROUP2_IND_ID,

    LPHY_IND_RFE_RFIN_EVNET_RX_ON_ID,
    LPHY_IND_RFE_RFIN_EVNET_RX_ON_EX_ID,
    LPHY_IND_RFE_RFIN_EVNET_RX_OFF_ID,
    LPHY_IND_RFE_RFIN_EVNET_RX_OFF_EX_ID,
    LPHY_IND_RFE_RFIN_EVNET_RX_AGC_ID,
    LPHY_IND_RFE_RFIN_EVNET_RX_AGC_EX_ID,
    LPHY_IND_RFE_RFIN_EVNET_CLEAR_TX_OFF_ID,
    LPHY_IND_RFE_RFIN_EVNET_RX_SHUTDOWN_ID,
    LPHY_IND_RFE_RFIN_EVNET_INTRA_FREQ_ID,
    LPHY_IND_RFE_RFIN_EVNET_TX_ON_ID,
    LPHY_IND_RFE_RFIN_EVNET_TX_ON_EX0_ID,
    LPHY_IND_RFE_RFIN_EVNET_TX_ON_EX1_ID,
    LPHY_IND_RFE_RFIN_EVNET_TX_OFF_ID,
    LPHY_IND_RFE_RFIN_EVNET_TX_OFF_EX_ID,
    LPHY_IND_RFE_RFIN_EVNET_TX_AGC_ID,
    LPHY_IND_RFE_RFIN_EVNET_TX_AGC_EX0_ID,
    LPHY_IND_RFE_RFIN_EVNET_TX_AGC_EX1_ID,
    LPHY_IND_RFE_RFIN_EVNET_CLEAR_RX_OFF_ID,
    LPHY_IND_RFE_RFIN_EVNET_TX_SHUTDOWN_ID,
    LPHY_IND_RFE_RFIN_EVNET_INTER_RX_ON_ID,
    LPHY_IND_RFE_RFIN_EVNET_INTER_RX_OFF_ID,
    LPHY_IND_RFE_RFIN_EVNET_INTER_FLAG_ON_ID,
    LPHY_IND_RFE_RFIN_EVNET_INTER_FLAG_OFF_ID,
    LPHY_IND_RFE_RFIN_EVNET_INTER_AGC_ID,
    LPHY_IND_RFE_RFIN_EVNET_INTER_FREQ_ID
}LPHY_IND_RFE_L1C_CMD_ENUM;

typedef UINT16 LPHY_IND_RFE_L1C_CMD_ENUM_UINT16;


enum RFE_OM_DEM_REQ_TYPE_ENUM
{
    RFE_OM_DEM_REQ_CAMP_MAINCELL           =0,
    RFE_OM_DEM_REQ_NCELL_BCCH_START,
    RFE_OM_DEM_REQ_NCELL_BCCH_FINISH,
    RFE_OM_DEM_REQ_SERV_BCCH_START,
    RFE_OM_DEM_REQ_SERV_BCCH_FINISH,
    RFE_OM_DEM_REQ_DL_SYSPARA_CHANGE,
    RFE_OM_DEM_REQ_HANDOVER_BLIND,
    RFE_OM_DEM_REQ_HANDOVER_NON_BLIND
};
typedef UINT16 RFE_OM_DEM_REQ_TYPE_ENUM_UINT16;


typedef struct
{
    UINT16                              usFreqInfo;
    UINT16                              usCellID;
    LTE_FRAME_TYPE_ENUM_UINT16          enMultiplexMode;
    LTE_CP_TYPE_ENUM_UINT16             enCPType;
    LTE_TDD_SPEC_SUBFRM_CFG_ENUM_UINT16 enSpecSFCfg;
    LTE_TDD_UD_CFG_ENUM_UINT16          enULDLCfg;
    UINT32                              ulFramePosition;
    LTE_BAND_WIDTH_ENUM_UINT16          enSysBandWidth;
    UINT8                               ucTxAntennaNum;
}RFE_OM_DL_CFG_PARA_STRU;

/*LPHY_IND_RFE_L1C_DEM_CMD_ID*/
typedef struct
{
    RFE_OM_DEM_REQ_TYPE_ENUM_UINT16         enFreqSwitchType;
    UINT8                                   ucIratHoFlag;      /*IRAT -> LTE切换标识，1有效*/
    UINT8                                   ucRsvd;
    RFE_OM_DL_CFG_PARA_STRU                 stDLCfgPara;
}RFE_OM_DEM_REQ_STRU;

/*LPHY_IND_RFE_L1C_EMCS_CMD_ID*/
typedef struct
{
    UINT16                              usInterFreq;
    UINT16                              usRsvd;
    RFE_OM_EMCS_REQ_TYPE_ENUM_UINT16    enFreqSwitchType;
    LTE_BAND_WIDTH_ENUM_UINT16          enSysBandWidth;
    LTE_FRAME_TYPE_ENUM_UINT16          enMultiplexMode;
    UINT16                              usOccasionInms;
    UINT8                               ucWFrequencySwitchFlag;
}RFE_OM_EMCS_REQ_STRU;


typedef struct{
    union {
        struct{
            UINT32      gFnLow      :   11;//[0,10]  0-1325
            UINT32      gFnHigh     :   11;//[11,21] 0-2047
        } u;
        UINT32 bits;
    } gfn;

    UINT16 usGsmQb;         /*0-4999*/
    UINT8  aucRsv[2];
}RFE_OM_GSM_TIMING_STRU;

typedef union{
    struct{
        UINT32      clockInChip             :   4;//[0,3] 0-15
        UINT32      chip                    :   12;//[4,15] 0-2559
        UINT32      slot                    :   4;//[16,19] 0-14
        UINT32      sfn                     :   12;//[20,31] 0-4095
    } u;
    UINT32 bits;
}RFE_OM_WCDMA_TIMING_UINION;

typedef union{
    struct{
        UINT32      chip                    :   12;//[0,11] 0-2559
        UINT32      slot                    :   4;//[12,15] 0-14
    } u;
    UINT32 bits;
}RFE_OM_WCDMA_SYSABS_UINION;


typedef union{
    struct{
        UINT32      ts                      :   15;//[0,14]  0-30719
        UINT32      sbfn                    :   4;//[15,18]  0-9
        UINT32      sfn                     :   10;//[19,28] 0-1023
    } u;
    UINT32 bits;
}RFE_OM_LTE_TIMING_UINION;

typedef union{
    struct{
        UINT32      cycle                   :   3; //[0,2]
        UINT32      rsv1                    :   1; //[3]
        UINT32      ts                      :   15;//[4,18]  0-30719
        UINT32      rsv2                    :   1; //[19]
        UINT32      sbfn                    :   4; //[20,23] 0-9
    } u;
    UINT32 bits;
}RFE_OM_LTE_ABS_TIMING_UINION;

typedef struct
{
    UINT32 ulSfn;     //子帧号
    UINT32 ulChip;    //1/32chip 为单位
}RFE_OM_TDS_TIMING_STRU;


typedef struct{
    RFE_OM_LTE_ABS_TIMING_UINION   uLteTiming;
    RFE_OM_WCDMA_TIMING_UINION     uWcdmaTiming;
    RFE_OM_WCDMA_SYSABS_UINION     uWcdmaSysAbsOffs;
    RFE_OM_GSM_TIMING_STRU         stGsmTiming;
    RFE_OM_TDS_TIMING_STRU         stTdsTiming;
    UINT32                         ulCtuDsp;
    UINT8                          ucValidFlg;
    UINT8                          aucRsv[3];
}RFE_OM_IRAT_TIMING_STRU;

/*LPHY_IND_RFE_TIME_RCVR_IND_ID*/
typedef struct{
    RFE_OM_IRAT_TIMING_STRU         stOldTime;
    RFE_OM_IRAT_TIMING_STRU         stNewTime;
    RFE_OM_LTE_ABS_TIMING_UINION    stRecoveredLteTime;
    UINT32                          ulDeltaT;
}RFE_OM_SLAVE_TIME_RECOVER_IND_STRU;
typedef struct
{
    //RFIN_CH0_RAGC_TIME_UNION  stEvtTimeCfg;
	UINT16 usRxABGain;
	UINT16 usRxCDGain;
	UINT16 usRxADcoc;
	UINT16 usRxBDcoc;
	UINT16 usRxCDcoc;
	UINT16 usRxDDcoc;
    UINT16 usRfAIIP2;
    UINT16 usRfBIIP2;
    UINT16 usRfCIIP2;
    UINT16 usRfDIIP2;
    RFE_WORK_MODE_ENUM_UINT16 usWorkMode;
    UINT16 usAgcDcocMode;//added liliuwei00279357,0:agc dcoc都配置，1: 配置agc 2:配置dcoc  其他值；非法  20150306
    //UINT16 usRsv;
} LTE_RFD_RX_AGC_CFG_STRU;

typedef struct
{
    //RFIN_CH0_RON_TIME_UNION             stEvtTimeCfg;           /*生效时间和触发时刻*/
    UINT16                              usDlRfChIndex;          /*此band使用的RF通道号*/
    UINT16                              usFreqInfo;             /*频点*/
    RFE_RF_BAND_WIDTH_ENUM_UINT16       enBandWidth;            /*带宽*/
    //LTE_FRAME_TYPE_ENUM_UINT16          enDuplexMode;           /*FDD/TDD*/
    LPHY_RFIN_SAMPLE_RATE_ENUM_UINT16   enSampleRate;           /*采样率*/
}LTE_RFD_RX_CH_CFG_STRU;
typedef struct
{
    UINT8                              ucReserved;                 /*CTU通道号*/
    UINT8                              ucUlRfChIndex;          /*此band使用的RF通道号*/
    UINT16                              usFreqInfo;             /*频点*/
    RFE_RF_BAND_WIDTH_ENUM_UINT16       enBandWidth;            /*带宽*/
    //LPHY_RFIN_SAMPLE_RATE_ENUM_UINT16   enSampleRate;           /*采样率*/
    UINT16 usApcCode;
    UINT16 usAptPdmVal;
    UINT16 usRsv;
}LTE_RFD_TX_CFG_STRU;

typedef enum
{
	RFIN_UL_MIPI_IND   = 0,
	RFIN_DL_MIPI_IND,
	RFIN_MIPI_IND_BUTT
}RFIN_MIPI_TYPE_IND_ENUM;

typedef UINT16 RFIN_MIPI_TYPE_IND_ENUM_UINT16;

typedef enum
{
	RFIN_UL_PRIVATE0_SFRM_HEAD_MIPI_IND   = 0,
	RFIN_UL_PRIVATE0_SFRM_MIDD_MIPI_IND,
	RFIN_UL_PRIVATE0_SFRM_HEAD_AND_UL_COMMON_SFRM_MIDD_MIPI_IND,
	RFIN_UL_PRIVATE1_SFRM_HEAD_MIPI_IND,
	RFIN_UL_PRIVATE1_SFRM_MIDD_MIPI_IND,
	RFIN_UL_PRIVATE1_SFRM_HEAD_AND_UL_COMMON_SFRM_MIDD_MIPI_IND,
	RFIN_UL_COMMON_SFRM_HEAD_MIPI_IND,
	RFIN_UL_COMMON_SFRM_MIDD_MIPI_IND,
	RFIN_DL_COMMON_MIPI_IND,
	RFIN_MIPI_IND_SEL_BUTT
}RFIN_MIPI_IND_SEL_ENUM;

typedef UINT16 RFIN_MIPI_IND_SEL_ENUM_UINT16;

typedef struct
{
    RFD_MIPI_EVT_ENUM_UINT16            enMipiEvt;
    UINT16                              usMipiAddrOffSet;           /*MIPI Buffer偏移地址*/

    NV_BAND_UL_MIPI_CTRL_STRU    	    *pstUlMipiConfig; 		 /*上行通道MIPI  相关参数*/
	NV_BAND_DL_MIPI_CTRL_STRU    	    *pstDlMipiConfig;     /*下行通道MIPI  相关参数*/
    LPHY_MIPIDEV_CMD_STRU               *pstMipiAntSel;        /* 天线开关相关参数 */
    RFIN_MIPI_TYPE_IND_ENUM_UINT16      enMipiTypeInd;
    UINT16                              usRvs;
    //RFE_NV_TYPE_ENUM_UINT16             enNvType;               /* NV类型，为RFE_1BAND_NV 还是RFE_NBAND_NV */
    PA_LEVEL_INDEX_ENUM_UINT16          enPaLevel;
    UINT16                              usPaTime;
    UINT16                              usMipiTime;
    UINT16                              usReserved;
}RFD_MIPI_CFG;
typedef struct
{
 	UINT8                              ucActRecvAntNum;            /*接收天线数*/
    UINT8                              ucRficClearInd;                 /*CTU通道号*/
    UINT16                              usReserved;
    LTE_RFD_RX_AGC_CFG_STRU             stRxAgcCfg;                 /*AGC相关RFD事件参数*/
    LTE_RFD_RX_CH_CFG_STRU              stRxChCfg;                  /*通道相关RFD事件参数*/
}LTE_RFD_RX_CFG_STRU;
typedef struct
{
    UINT32                              ulBbpBufAddr;               /*RFIN各事件配置寄存器地址*/
    UINT32                              ulSsiTime;                /*SSI 命令延迟时间*/
    UINT32                              ulAntTime;                /*天线开关延迟时间*/
    UINT32                              ulOmMsgId;                  /*RFIN事件可谓可测ID*/
    UINT32                              ulEvtTimeCfg;           /*生效时间和触发时刻*/

    UINT16                              usBandNum;                  /*band 号*/
    RFD_DRV_EVT_ENUM_UINT16             enDrvEvt;                    /*RFD事件*/

    RFD_SSI_EVT_ENUM_UINT16             enSsiEvt;
    UINT16                              usSsiBufOffset;             /*SSI Buffer偏移地址*/

    LTE_FRAME_TYPE_ENUM_UINT16          enDuplexMode;               /*FDD/TDD*/
    RFE_WORK_MODE_ENUM_UINT16           enWorkMode;

    RFIN_STATE_MOVE_TYPE_ENUM_UINT16    enRfinStatMoveType;
    UINT8                              ucFddForcedFlag;
    UINT8                              ucReserved;

    UINT8                              ucPrimaryChFlag;
    UINT8                              ucMipiCfgEn;                /*是否配置MIPI*/
    UINT8                              ucCtuChIdx;
    UINT8                              ucFreqSwtichInd;
    UINT8                              ucRficIdx;
    UINT8                              ucRfRxSel;
    UINT8                              ucTddChFisrtOnFlag;
    UINT8                              ucRsv;
    LTE_RFD_RX_CFG_STRU                 stRxCfg;
    LTE_RFD_TX_CFG_STRU                 stTxCfg;                  /*通道相关RFD事件参数*/
    RFD_MIPI_CFG                        stMipiCfg;
}RFD_EVT_PARA_STRU;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __RFE_OM_DEF_H__ */


