/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : PhyRfCalInterface.h
  版 本 号   : V300R002 初稿
  作    者   : j00105005
  生成日期   : 2011年3月15日
  最近修改   :
  功能描述   : 该头文件定义了PC侧与单板DSP的快慢速校准接口
  函数列表   :
  修改历史   :
  1.日    期   : 2011年3月15日
    作    者   : j00105005
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __PHYRFCALINTERFACE_H__
#define __PHYRFCALINTERFACE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/


#define GPHY_RF_CAL_TX_ON                   ( 0x5555 )                              /* 老化测试中，使能发射 */
#define GPHY_RF_CAL_TX_OFF                  ( 0xaaaa )                              /* 老化测试中，停止发射 */



/* Mask code Used for PHY_RF_CAL_W_SELF_CAL_REQ_STRU */
#define MASK_SELF_CAL_TX_IQ_MISMATCH        ( 1<<0 )
#define MASK_SELF_CAL_W_RX_DCR              ( 1<<1 )
#define MASK_SELF_CAL_W_RX_IP2              ( 1<<2 )
/* Mask code Used for PHY_RF_CAL_ET_DELAY_SELF_CAL_REQ_STRU */
#define MASK_SELF_CAL_W_ET_DELAY            ( 1<<3 )
#define MASK_SELF_CAL_W_ET_DELAY_FREQCOMP   ( 1<<4 )

/* Mask code Used for PHY_RF_CAL_W_TRX_PARA_CFG_REQ_STRU */
#define MASK_W_TRX_CFG_TX_AFC               ( 1<<0 )
#define MASK_W_TRX_CFG_TX_CFIX              ( 1<<1 )
#define MASK_W_TRX_CFG_TX_ARFCN             ( 1<<2 )
#define MASK_W_TRX_CFG_TX_ONOFF             ( 1<<3 )
#define MASK_W_TRX_CFG_TX_RFIC_MODE         ( 1<<4 )
#define MASK_W_TRX_CFG_TX_PAMODE            ( 1<<5 )
#define MASK_W_TRX_CFG_TX_POWER_PARA        ( 1<<6 )
#define MASK_W_TRX_CFG_TX_PA_VCC            ( 1<<7 )  /* APT ET调试时均是强配PA电压，共用一个掩码 */
#define MASK_W_TRX_CFG_PD_ONOFF             ( 1<<8 )
#define MASK_W_TRX_CFG_TX_UPA               ( 1<<9 )
#define MASK_W_TRX_CFG_SELF_CAL             ( 1<<10 )
#define MASK_W_TRX_CFG_TX_C2FIX             ( 1<<11 )
#define MASK_W_TRX_CFG_TX_DPA               ( 1<<12 )
#define MASK_W_TRX_CFG_TX_ET_TIMEDELAY      ( 1<<13 )
#define MASK_W_TRX_CFG_TX_DPD               ( 1<<14 )
#define MASK_W_TRX_CFG_TX_V_IQ              ( 1<<15 ) /* 如果只有Viq的掩码，表示输出恒定幅度，如果Viq和Step的掩码都打开，表示幅度从Viq步进，到最大幅度后，自动循环 */
#define MASK_W_TRX_CFG_RX_ARFCN             ( 1<<16 )
#define MASK_W_TRX_CFG_RX_CROSS_ARFCN       ( 1<<17 )
#define MASK_W_TRX_CFG_RX_ONOFF             ( 1<<18 )
#define MASK_W_TRX_CFG_RX_ANTSEL            ( 1<<19 )
#define MASK_W_TRX_CFG_RX_AGC_GAIN          ( 1<<20 )
#define MASK_W_TRX_CFG_RX_EVM               ( 1<<21 )
#define MASK_W_TRX_CFG_XO_SELFCAL           ( 1<<22 )
#define MASK_W_TRX_CFG_TX_ETDPD_COMP        ( 1<<28 ) /* ETDPD温补/频补 */

#define MASK_W_TRX_CFG_TX_ET_COMP           ( 1<<29 ) /* ET校准的增益压缩点是否生效，如果掩码为1，则增益压缩点使用原语带的值，否则使用NV的值 */
#define MASK_W_TRX_CFG_TX_WAVE              ( 1<<30 )
#define MASK_W_TRX_CFG_TX_IQ_STEP           ( ( ( UINT32 )1 )<<31 )

#define MASK_W_TRX_CFG_TX_APT               MASK_W_TRX_CFG_TX_PA_VCC


/* Mask code Used for PHY_RF_CAL_W_TRX_FAST_CAL_REQ_STRU_usTxMask */
#define MASK_W_TRX_FAST_CAL_REQ_TXMASK_HDET     ( 1<<0 )
#define MASK_W_TRX_FAST_CAL_REQ_TXMASK_APT      ( 1<<1 )
#define MASK_W_TRX_FAST_CAL_REQ_TXMASK_VGA      ( 1<<2 )
#define MASK_W_TRX_FAST_CAL_REQ_TXMASK_DCOFFSET ( 1<<3 )

/* Mask code Used for PHY_RF_CAL_W_ET_FAST_REQ_STRU_usMask */
#define MASK_W_ET_FAST_REQ_MASK_HDET           ( 1<<0 )
#define MASK_W_ET_FAST_REQ_MASK_COMP           ( 1<<1 )

/* Mask code Used for PHY_RF_CAL_W_PD_PARA_CFG_REQ_STRU */
#define MASK_W_PD_PARA_CFG_THROUGH          ( 1<<0 )
#define MASK_W_PD_PARA_CFG_DC_OFFSET        ( 1<<1 )
#define MASK_W_PD_PARA_CFG_VGA              ( 1<<2 )

/* Mask code Used for PHY_CAL_RF_COMM_DATA_RPT_MSG_HEAD_STRU_ulTestItemsBitMap */
#define MASK_RF_COMM_DATA_RPT_ET_LUT        ( 1<<0 )
#define MASK_RF_COMM_DATA_RPT_DPD_LUT       ( 1<<1 )
#define MASK_RF_COMM_DATA_RPT_ET_DELAY      ( 1<<2 )


/* W Rx AGC GAIN COUNT */
#define W_RX_NOBLOCK_AGC_GAIN_COUNT         ( 8 )
#define W_RX_BLOCK_AGC_GAIN_COUNT           ( 8 )

#define W_TRX_MAX_STEP_COUNT                ( 16 )
#define W_TRX_MAX_SWEEP_FRAME_COUNT         ( 38 )  /* PC一次下发给UE侧数据包最大8K限制 */
#define W_TRX_MAX_REPORT_COUNT              ( 900 ) /* DSP一次上报的最大个数，包括Rssi At1(0.125dBm)+Rssi At2(0.125dBm)+PD测量结果 */

/* W模校准上报时成功失败标识 */
#define WPHY_TOOL_CAL_RESULT_RPT_SUCCESS    ( 0 )

/* C模校准上报时成功失败标识 */
#define CPHY_TOOL_CAL_RESULT_RPT_SUCCESS    ( 0 )

/* W模自校准的频段最大个数 */
#define SELF_CAL_BAND_ID_MAX_COUNT          (10)

/* X模自校准的频段最大个数 */
#define CDMA_SELF_CAL_BAND_ID_MAX_COUNT     ( 2 )

#define WG_BBP_RF_REG_WR_MAX_COUNT          ( 8 )

/* X模寄存器读写个数 */
#define CSDR_BBP_RF_REG_WR_MAX_COUNT        WG_BBP_RF_REG_WR_MAX_COUNT

/*  G TRX CFG MARCO */
/* Mask code Used for RF_CAL_G_TX_PARA_CFG_REQ_STRU */
#define MASK_CAL_RF_G_TX_AFC                ( 1<<0 )  /* 上行单板频率控制值 */
#define MASK_CAL_RF_G_TX_ARFCN              ( 1<<1 )  /* 上行频点是否生效 */
#define MASK_CAL_RF_G_TX_ONOFF              ( 1<<2 )  /* 上行发射开关是否生效 */
#define MASK_CAL_RF_G_TX_DATA_PATTERN       ( 1<<3 )  /* 上行的数据类型是否生效 */
#define MASK_CAL_RF_G_TX_CFIX               ( 1<<4 )  /* 上行Cfix是否生效 */
#define MASK_CAL_RF_G_TX_SLOT_CFG           ( 1<<5 )  /* 上行的时隙配置是否生效 */
#define MASK_CAL_RF_G_TX_C2FIX              ( 1<<6 )  /* 上行Cfix是否生效 */


/* Mask code Used for RF_CAL_G_RX_PARA_CFG_REQ_STRU */
#define MASK_CAL_RF_G_RX_ARFCN              ( 1<<0 )  /* 下发频点 */
#define MASK_CAL_RF_G_RX_MODE               ( 1<<1 )  /* 下发接收模式 */
#define MASK_CAL_RF_G_RX_AGCMODE            ( 1<<2 )  /* 下发测量模式 */
#define MASK_CAL_RF_G_RX_AGCGAIN            ( 1<<3 )  /* 下发AGC档位 */

/* Mask code User for PHY_RF_CAL_G_TX_FAST_CAL_REQ_STRU */
#define MASK_G_TX_FAST_CAL_REQ_TXMASK_APT   ( 1<<0 )  /* APT使能*/

#define G_TX_PARA_MAX_SLOT_CNT_PER_FRAME    ( 4 )

#define G_TX_MAX_STEP_COUNT                 ( 7 )       /* 当前只支持4时隙*/
#define G_TRX_MAX_SWEEP_FRAME_COUNT         ( 120 )
#define G_RX_MAX_STEP_COUNT                 ( 7 )
#define G_RX_MAX_RSSI_COUNT                 ( G_TRX_MAX_SWEEP_FRAME_COUNT * G_RX_MAX_STEP_COUNT )
#define G_RX_AGC_GAIN_COUNT                 ( 8 )
#define W_GAUGE_RESULT_SIZE                 ( 13 )      /* 32K校准上报数据个数 */



#define GSM_TX_HD35_PCL_NUM                 ( 3 )
#define GSM_TX_HD35_ARFCN_NUM               ( 3 )
#define GSM_TX_HD35_STEP_NUM                ( 5 )
#define GSM_TX_HD35_BAND_NUM                ( 4 )

#define GPHY_RX_IQ_MISMATCH_SLOT_NUM        ( 64 )      /* 总采集64(4*16)个时隙数据，16帧，每帧4个时隙 */

#define W_RX_EVM_REPORT_ON                  ( 1 )       /* EVM上报打开 */
#define W_RX_EVM_REPORT_OFF                 ( 0 )       /* EVM上报关闭 */
#define W_RX_EVM_REPORT_DATA_COUNT          ( 10240 )   /* EVM一次上报最大的数据,32bit */



/* 消息头GSM 模式ID Componentid
   lte          0x3000
   tds          0x3100
   gsm          0x3200
   wcdma        0x3300
   x            0x3400
   与模式无关   0x3f00 */

#define GPHY_MSGHEAD_COMPONENT_ID           ( 0x3200 )
#define WPHY_MSGHEAD_COMPONENT_ID           ( 0x3300 )
#define CPHY_MSGHEAD_COMPONENT_ID           ( 0x3400 )

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
 枚举名    :PHY_TOOL_MSG_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :RF CAL MSG ID ENUM
*****************************************************************************/
enum PHY_TOOL_MSG_ID_ENUM
{
    /* WCDMA RF快速校准接口原语列表 */
    ID_TOOL_WPHY_CAL_TRX_FAST_CAL_REQ       = 0x1240,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_TRX_FAST_CAL_REQ_STRU */

    ID_TOOL_WPHY_CAL_PD_PARA_CFG_REQ        = 0x1241,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_PD_PARA_CFG_REQ_STRU */

    /* WCDMA RF自校准接口原语列表 */
    ID_TOOL_WPHY_CAL_SELF_CAL_REQ           = 0x1242,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_SELF_CAL_REQ_STRU */

    /* WCDMA RF慢速校准接口原语列表 */
    ID_TOOL_WPHY_CAL_TRX_PARA_CFG_REQ       = 0x1243,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_TRX_PARA_CFG_REQ_STRU */
    ID_TOOL_WPHY_CAL_RX_RSSI_MEAS_REQ       = 0x1244,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_RX_RSSI_MEAS_REQ_STRU */
    ID_WPHY_TOOL_GAUGE_REQ                  = 0x1245,                           /* _H2ASN_MsgChoice  WPHY_TOOL_GAUGE_REQ_STRU */

    /* W寄存器读写接口 */
    ID_TOOL_WPHY_WR_RFIC_REG_REQ             = 0x1246,
    ID_TOOL_WPHY_WR_BBP_REG_REQ              = 0x1247,

	/* WCDMA ET快速校准接口 */
	ID_TOOL_WPHY_CAL_ET_FAST_REQ             = 0x1248,

    /* WCDMA ET Delay Freq Comp自校准接口原语 */
    ID_TOOL_WPHY_CAL_ET_DELAY_FREQ_COMP_SELF_CAL_REQ = 0x1249,               /* _H2ASN_MsgChoice  PHY_RF_CAL_ET_DELAY_SELF_CAL_REQ_STRU */

    /* DCXO自校准 */
    ID_TOOL_WPHY_CAL_XO_COFFICIENT_REQ      = 0x124a,

    ID_RRC_PHY_SWITCH_MOANT_IND             = 0x1250,                           /* _H2ASN_MsgChoice  RRC_PHY_SWITCH_MOANT_IND_STRU */

    /* W RF通用CNF */
    ID_WPHY_TOOL_CAL_RF_MSG_CNF             = 0x21F0,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_RF_MSG_CNF_STRU */

    ID_WPHY_TOOL_CAL_TX_POWER_DETECT_IND    = 0x21F1,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_RF_TX_PD_IND_STRU */
    ID_WPHY_TOOL_GAUGE_CNF                  = 0x21F2,                           /* _H2ASN_MsgChoice  WPHY_TOOL_GAUGE_CNF_STRU */
    ID_WPHY_TOOL_GAUGE_IND                  = 0x21F3,                           /* _H2ASN_MsgChoice  WPHY_TOOL_GAUGE_IND_STRU */

    ID_WPHY_TOOL_CAL_TRX_FAST_CAL_IND       = 0x21F4,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_TRX_FAST_CAL_IND_STRU */
    ID_WPHY_TOOL_CAL_SELF_CAL_IND           = 0x21F5,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_SELF_CAL_IND_STRU */

    ID_WPHY_TOOL_CAL_RX_RSSI_MEAS_IND       = 0x21F6,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_RX_RSSI_MEAS_IND_STRU */


    ID_WPHY_TOOL_R_RFIC_REG_IND             = 0x21F8,
    ID_WPHY_TOOL_R_BBP_REG_IND              = 0x21F9,

    /* W IP2自校准获取IM2上报接口 */
    ID_WPHY_TOOL_IP2_IM2_VALUE_IND          = 0x21FA,
    ID_WPHY_TOOL_RX_EVM_MEAS_IND            = 0x21FB,

    /* 物理层通用数据上报 */
    ID_PHY_TOOL_COMM_DATA_IND               = 0x21FD,

    /* 物理层可维可测数据上报 */
    ID_PHY_TOOL_MNTN_DATA_RPT               = 0x21FE,
    ID_WPHY_TOOL_CAL_XO_COFFICIENT_IND      = 0x21FF,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_RX_RSSI_MEAS_IND_STRU */
    //CDMA消息ID的定义，ID还需要重新定义
    /* CDMA RF快速校准接口原语列表 */
    ID_TOOL_CPHY_CAL_TRX_FAST_CAL_REQ       = 0x2F00,

    ID_TOOL_CPHY_CAL_PD_PARA_CFG_REQ        = 0x2F01,

    /* CDMA RF自校准接口原语列表 */
    ID_TOOL_CPHY_CAL_SELF_CAL_REQ           = 0x2F02,

    /* CDMA RF慢速校准接口原语列表 */
    ID_TOOL_CPHY_CAL_TRX_PARA_CFG_REQ       = 0x2F03,
    ID_TOOL_CPHY_CAL_RX_RSSI_MEAS_REQ       = 0x2F04,

    /* CDMA RFIC和BBP读写接口原语列表 */
    ID_TOOL_CPHY_CAL_WR_RFIC_REG_REQ         = 0x2F05,
    ID_TOOL_CPHY_CAL_WR_BBP_REG_REQ          = 0x2F06,

    /* CDMA RF通用CNF */
    ID_CPHY_TOOL_CAL_RF_MSG_CNF             = 0x2F10,

    ID_CPHY_TOOL_CAL_TX_POWER_DETECT_IND    = 0x2F20,

    ID_CPHY_TOOL_CAL_TRX_FAST_CAL_IND       = 0x2F21,
    ID_CPHY_TOOL_CAL_SELF_CAL_IND           = 0x2F22,

    ID_CPHY_TOOL_CAL_RX_RSSI_MEAS_IND       = 0x2F23,

    /* CDMA RFIC和BBP读标记IND */
    ID_CPHY_TOOL_CAL_R_RFIC_REG_IND         = 0x2F24,
    ID_CPHY_TOOL_CAL_R_BBP_REG_IND          = 0x2F25,

    /* GSM RF快速校准接口原语列表 */
    ID_TOOL_GPHY_CAL_RX_FAST_CAL_REQ        = 0x1740,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_FAST_CAL_REQ_STRU */
    ID_TOOL_GPHY_CAL_TX_FAST_CAL_REQ        = 0x1741,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_TX_FAST_CAL_REQ_STRU */

    /* GSM 自校准接口原语列表 */
    ID_TOOL_GPHY_CAL_SELF_CAL_REQ           = 0x1742,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_SELF_CAL_REQ_STRU */
    ID_TOOL_GPHY_CAL_RX_DCR_CAL_REQ         = 0x1743,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_DCR_REQ_STRU */

    /* GSM RF慢速校准接口原语列表 */
    ID_TOOL_GPHY_CAL_TX_PARA_CFG_REQ        = 0x1744,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_TX_PARA_CFG_REQ_STRU */
    ID_TOOL_GPHY_CAL_RX_PARA_CFG_REQ        = 0x1745,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_PARA_CFG_REQ_STRU */
    ID_TOOL_GPHY_CAL_RX_RSSI_MEAS_REQ       = 0x1746,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_RSSI_MEAS_REQ_STRU */

    ID_TOOL_GPHY_WR_RFIC_REG_REQ            = 0x1747,
    ID_TOOL_GPHY_WR_BBP_REG_REQ             = 0x1748,

    ID_TOOL_GPHY_CAL_RX_IQ_MISMATCH_REQ     = 0x1751,

    /* GSM HD3HD5校准原语 */
    ID_TOOL_GPHY_CAL_TX_HD3_HD5_REQ         = 0x1752,

    ID_MPH_SWITCH_M1XO_IND                  = 0x1753,

    ID_TOOL_GPHY_SWITCH_MOANT_IND           = 0x1754,

    /* G RF通用CNF */
    ID_GPHY_TOOL_CAL_RF_MSG_CNF             = 0x7120,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RF_MSG_CNF_STRU */

    ID_GPHY_TOOL_CAL_RX_FAST_CAL_IND        = 0x7121,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_FAST_CAL_IND_STRU */

    ID_GPHY_TOOL_CAL_SELF_CAL_IND           = 0x7122,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_SELF_CAL_IND_STRU */
    ID_GPHY_TOOL_CAL_RX_DCR_CAL_IND         = 0x7123,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_DCR_RPT_IND_STRU */
    ID_GPHY_TOOL_CAL_RX_RSSI_MEAS_IND       = 0x7124,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_RSSI_MEAS_IND_STRU */

    ID_GPHY_TOOL_R_RFIC_REG_IND             = 0x7126,
    ID_GPHY_TOOL_R_BBP_REG_IND              = 0x7127,

    ID_GPHY_TOOL_CAL_RX_IQ_MISMATCH_IND     = 0x7128,

    ID_GPHY_TOOL_CAL_TX_HD3_HD5_IND         = 0x7129,

};
typedef UINT16 PHY_TOOL_MSG_ID_ENUM_UINT16;


/*****************************************************************************
 枚举名    :RF_CAL_SELF_CAL_ERR_CODE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :物理层自校准失败原因说明
*****************************************************************************/
enum RF_CAL_SELF_CAL_ERR_CODE_ENUM
{
    RF_CAL_SELF_CAL_SUCCESS                               = 0,
    RF_CAL_SELF_CAL_FAIL                                  = 1,
    RF_CAL_SELF_CAL_IP2_MEM_ALLOC_FAIL                    = 2,                  /* IP2校准时,申请uncache内存失败 */
    RF_CAL_SELF_CAL_IP2_GREATER_THAN_FAIL_THRESHOLD       = 3,                  /* 找不到满足失败门限的点,若有些频点是好的,可能是双工隔离太差 */
    RF_CAL_SELF_CAL_IP2_SAMPLE_DATA_FAIL                  = 4,                  /* 采数失败,说明EDMA通道申请出了问题 */
    RF_CAL_SELF_CAL_IQMISMATCH_CORR_FAIL                  = 5,                  /* BBP相关运算失败 */
    RF_CAL_SELF_CAL_IQMISMATCH_OVER_CODE                  = 6,                  /* A,P,I,Q中至少有一个码字超出[-64,63] */
    RF_CAL_SELF_CAL_DCR_CORR_FAIL                         = 7,                  /* DCR相关运算失败 */
    RF_CAL_SELF_CAL_DCR_ITERATIVE_FAIL                    = 8,                  /* 迭代三次仍然不满足门限要求，校准失败 */
    RF_CAL_SELF_CAL_LOLEAKAGE_MEM_ALLOC_FAIL              = 9,                  /* 分配内存失败 */
    RF_CAL_SELF_CAL_LOLEAKAGE_SAMPLE_DATA_FAIL            = 10,                 /* Lo Leakage采数失败 */
    RF_CAL_SELF_CAL_LOLEAKAGE_CORR_FAIL                   = 11,                 /* 相关运算失败 */
    RF_CAL_SELF_CAL_LOLEAKAGE_CALC_FAIL                   = 12,                 /* Lo Leakage计算失败 */
    RF_CAL_SELF_CAL_IQMISMATCH_SAMPLE_DATA_FAIL           = 13,                 /* IQMISMATCH采数据错误 */
    RF_CAL_SELF_CAL_IQMISMATCH_STEP2_MCTMP_FAIL           = 14,                 /* 计算TX IQMC_Tmp 和 MRXIQMC值错误 */
    RF_CAL_SELF_CAL_IQMISMATCH_STEP2_AP_FAIL              = 15,                 /* 计算第一次A、P值错误 */
    RF_CAL_SELF_CAL_IQMISMATCH_STEP3_IR_FAIL              = 16,                 /* 计算IR_Linear错误 */
    RF_CAL_SELF_CAL_IQMISMATCH_STEP3_ANGLE_FAIL           = 17,                 /* 计算调整角度错误 */
    RF_CAL_SELF_CAL_IQMISMATCH_STEP3_AP_FAIL              = 18,                 /* 计算第二次A、P值错误 */
    RF_CAL_SELF_CAL_IQMISMATCH_STEP4_IR_FAIL              = 19,                 /* 计算IR1错误 */
    RF_CAL_SELF_CAL_IQMISMATCH_STEP4_AP_FAIL              = 20,                 /* 计算第三次A、P值错误 */
    RF_CAL_SELF_CAL_IQMISMATCH_STEP5_IR_FAIL              = 21,                 /* 计算IR2错误 */
    RF_CAL_SELF_CAL_IQMISMATCH_5TIMES_FAIL                = 22,                 /* 计算IR2错误 */
    RF_CAL_SELF_CAL_SYS_TIME_SYN_FAIL                     = 23,                 /* CFN/SFN同步失败 */
    RF_CAL_SELF_CAL_LOLEAKAGE_STEP1_SAMPLE_DATA_FAIL      = 24,                 /* LOLeakge Step1采数失败 */
    RF_CAL_SELF_CAL_LOLEAKAGE_STEP2_SAMPLE_DATA_FAIL      = 25,                 /* LOLeakge Step2采数失败 */
    RF_CAL_SELF_CAL_IQMISMATCH_STEP1_SAMPLE_DATA_FAIL     = 26,                 /* IQ Step1采数据错误 */
    RF_CAL_SELF_CAL_IQMISMATCH_STEP2_SAMPLE_DATA_FAIL     = 27,                 /* IQ Step2采数据错误 */
    RF_CAL_SELF_CAL_IQMISMATCH_STEP3_SAMPLE_DATA_FAIL     = 28,                 /* IQ Step3采数据错误 */
    RF_CAL_SELF_CAL_IQMISMATCH_STEP4_SAMPLE_DATA_FAIL     = 29,                 /* IQ Step4采数据错误 */
    RF_CAL_SELF_CAL_ET_DPD_MEM_ALLOC_FAIL                 = 30,                 /* DPD校准时,申请uncache内存失败 */
    RF_CAL_SELF_CAL_ET_DPD_DATA_SYNC_FAIL                 = 31,                 /* 数据同步失败 */
    RF_CAL_SELF_CAL_ET_DPD_MISS_FIRST_POINT               = 32,                 /* 数据同步失败，没有采到单音突变 */
    RF_CAL_SELF_CAL_DPD_AMAM_CALC_FAIL                    = 33,                 /* DPD AMAM计算错误 */
    RF_CAL_SELF_CAL_DPD_SAMPLE_DATA_FAIL                  = 34,                 /* 采数据错误 */
    RF_CAL_SELF_CAL_DPD_CALC_AMPM_FAIL                    = 35,                 /* 计算平均相位平均幅度失败 */
    RF_CAL_SELF_CAL_ET_SAMPLE_DATA_FAIL                   = 36,                 /* ET采数据错误 */
    RF_CAL_SELF_CAL_ET_GET_COMPRESS_POINT_FAIL            = 37,                 /* 采数据错误 */
    RF_CAL_SELF_CAL_ET_TIME_DELAY_SAMPLE_DATA_FAIL        = 38,                 /* ET_TIME_DELAY采数据错误 */
    RF_CAL_SELF_CAL_IQMISMATCH_SYNC_FAIL                  = 39,                 /* 获取同步位置失败 */
    RF_CAL_SELF_CAL_IQMISMATCH_SET_SAMPLE_TIME_FAIL       = 40,                 /* 查找定时采数起始时间失败 */
    RF_CAL_SELF_CAL_IQMISMATCH_DATA_TRANSFER_FAIL         = 41,                 /* 搬数失败,DMA或BBPMASTER */
    RF_CAL_SELF_CAL_ET_TIME_DELAY_NV_ERROR                = 42,                 /* NV给的上下delay错误 */
    RF_CAL_SELF_CAL_IQMISMATCH_ANGLE_CALC_FAIL            = 43,                 /* c/a虚部为负，不满足+90度要求 */
    RF_CAL_SELF_CAL_ET_DELAY_ACLR_MEM_ALLOC_FAIL          = 44,                 /* Delay计算Aclr时申请内存失败 */
    RF_CAL_SELF_CAL_ET_DELAY_ACLR_CENTER_SQUARE_FULL      = 45,                 /* Delay计算Aclr时中心信号平方和溢出 */
    RF_CAL_SELF_CAL_IQMISMATCH_TRANSIT_DATA_FAIL          = 1000,               /* 搬数失败 */
    RF_CAL_SELF_CAL_BUTT
};
typedef UINT16 RF_CAL_SELF_CAL_ERR_CODE_ENUM_UINT16;


/*****************************************************************************
 枚举名    :W_TX_RFIC_MODE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  :RF CAL W TRX FAST ENUM
*****************************************************************************/
enum W_TX_RFIC_MODE_ENUM
{
    W_TX_RFIC_MODE_NORMAL              = 0,
    W_TX_RFIC_MODE_VOICE,
    W_TX_RFIC_MODE_BUTT
};
typedef UINT16 W_TX_RFIC_MODE_ENUM_UINT16;


/*****************************************************************************
 枚举名    :W_TX_POWER_CTRL_MODE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :RF CAL W TRX FAST ENUM
*****************************************************************************/
enum W_TX_POWER_CTRL_MODE_ENUM
{
    W_TX_CAL_POWER_CTRL_POWER              = 0,
    W_TX_CAL_POWER_CTRL_POWER_ATTEN,
    W_TX_CAL_POWER_CTRL_REGISTER,
    W_TX_CAL_POWER_CTRL_BUTT
};
typedef UINT16 W_TX_POWER_CTRL_MODE_ENUM_UINT16;


/*****************************************************************************
 枚举名    :W_FAST_STEP_WIDTH_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :RF CAL W TRX FAST ENUM
*****************************************************************************/

enum W_FAST_STEP_WIDTH_ENUM
{
    WIDTH_2MS                               = 2,
    WIDTH_10MS                              = 10,
    WIDTH_20MS                              = 20,
    WIDTH_BUTT
};
typedef UINT16 W_FAST_STEP_WIDTH_ENUM_UINT16;

/* W PA模式 */
enum  W_TX_PA_MODE_ENUM
{
    PA_MODE_AUTO  = 0,
    PA_MODE_HIGH,
    PA_MODE_MID,
    PA_MODE_LOW,
    PA_MODE_BUTT
};

enum  W_RX_ANT_ENUM
{
    W_RX_ANT1 = 1,  // main ant
    W_RX_ANT2 = 2,  // diversity ant
    W_RX_BUTT
};

/* W Rx 载波模式 0:单载波, 1:双载波 */
enum  W_RX_CARRIER_MODE_ENUM
{
    W_RX_CARRIER_MODE_SC = 0,
    W_RX_CARRIER_MODE_DC = 1,
};

/* W Rx BLOCK模式 0: No Block,   1:Block; */
enum W_RX_BLOCK_MODE_ENUM
{
    W_RX_WITHOUT_BLOCK = 0,
    W_RX_WITH_BLOCK,
};

/* W Rx 档位配置模式 0:档位自动调整 1:档位强配 */
enum W_RX_AGC_CTRL_MODE_ENUM
{
    W_RX_AGC_CTRL_AUTO = 0,
    W_RX_AGC_CTRL_APPOINTED,
};

/*****************************************************************************
 枚举名    :G_TX_MODULATION_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum G_TX_MODULATION_TYPE_ENUM
{
    MODE_GMSK                               = 0,
    MODE_8PSK                               = 1,
    MODE_BUTT
};
typedef UINT16 G_TX_MODULATION_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    :G_TX_POWER_CTRL_MODE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum G_TX_POWER_CTRL_MODE_ENUM
{
    G_TX_CAL_POWER_CTRL_TX_AGC                  = 0,
    G_TX_CAL_POWER_CTRL_POWER,
    G_TX_CAL_POWER_CTRL_POWER_ATTEN,
    G_TX_CAL_POWER_CTRL_REGISTER,
    G_TX_CAL_POWER_CTRL_BUTT
};
typedef UINT16 G_TX_POWER_CTRL_MODE_ENUM_UINT16;




enum G_RX_WAVE_TYPE_ENUM
{
    RX_BURST     = 0,
    RX_CONTINOUS = 1,
    RX_TYPE_BUTT
};

enum G_RX_MEAS_MODE_ENUM
{
    AGC_SLOW = 0,
    AGC_FAST = 1,
    AGC_BUTT
};

/*****************************************************************************
 枚举名    :C_FAST_STEP_WIDTH_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :RF CAL C TRX FAST ENUM
*****************************************************************************/

enum C_FAST_STEP_WIDTH_ENUM
{
    CSDR_2PCG_STEP_WIDTH_LENGTH             = 2500,
    CSDR_4PCG_STEP_WIDTH_LENGTH             = 5000,
    CSDR_8PCG_STEP_WIDTH_LENGTH             = 10000,
    CSDR_PCG_STEP_WIDTH_LENGTH_BUTT
};
typedef UINT16 C_FAST_STEP_WIDTH_ENUM_UINT16;

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/


/*****************************************************************************
 结构名    : PHY_CAL_COMPLEX_DATA_INT16_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    INT16                               sReal;                                  /* 复数实部 */
    INT16                               sImg;                                   /* 复数虚部 */
}PHY_CAL_COMPLEX_DATA_INT16_STRU;

/*****************************************************************************
 结构名    : PHY_CAL_MSG_DEAD_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usComponentId;                          /* 组件 ID */
}PHY_CAL_MSG_DEAD_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_W_TX_UPA_PARA_STRU
 协议表格  :
 结构说明  : WCDMA RF慢速校准接口 -- UPA参数 ( 临时放在这里 )
*****************************************************************************/
typedef struct
{
    /* 下面的参数是发射UPA需要使用的 */
    UINT16                              usBec;
    UINT16                              usBed1;
    UINT16                              usBed2;
    UINT16                              usBc;
    UINT16                              usBd;
    UINT16                              usTxSlotFormat;     /* 调试模式:填入的是时隙格式 */
    UINT16                              usTxChanNum;        /* 码道个数 */
}PHY_RF_CAL_W_TX_UPA_PARA_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_W_TX_DPA_PARA_STRU
 协议表格  :
 结构说明  : WCDMA RF慢速校准接口 -- DPA参数
*****************************************************************************/
typedef struct
{
    /* 下面的参数是发射DPA需要使用的 */
    UINT16                              usBc;
    UINT16                              usBd;
    UINT16			        			usBhs;
    UINT16                              usRsv;
}PHY_RF_CAL_W_TX_DPA_PARA_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_W_TX_REG_CTRL_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usRficGainCtrl;
    INT16                               sDbbAtten10th;
}PHY_RF_CAL_W_TX_REG_CTRL_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_AFC_PARA_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    INT16                               sAfc;                                   /* AFC控制字 */
    UINT16                              usCfix:8;                               /* 单DCXO c1 的控制字，取值范围为[0,255] */
    UINT16                              usC2fix:8;                              /* 单DCXO C2 的控制字，取值范围为[0,7] */
}PHY_RF_CAL_AFC_PARA_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_W_TX_POWER_PARA_UNION
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef union
{
    INT16                               sTxPower10th;
    INT16                               sTxPowerAtten10th;
    PHY_RF_CAL_W_TX_REG_CTRL_STRU       stTxRegCtrlPara;
}PHY_RF_CAL_W_TX_POWER_PARA_UNION;


/*****************************************************************************
 结构名    : W_RX_AGC_GAIN_CFG_STRU
 协议表格  :
 结构说明  : WCDMA RF快慢速校准接口Rx Agc Gain配置位域定义
            BIT[15] : 0:No Block， 1:Block;
            BIt[14] : 0:单载波，   1：双载波
            BIT[13] : 0:档位自动调整 1:档位强配
            BIT[2:0]: 0:第一档(增益最高的),依次类推
*****************************************************************************/
typedef struct
{
    UINT16                              AgcGainLvl:3;
    UINT16                                        :5;
    UINT16                                        :5;
    UINT16                              GainLvlMode:1;  /* 0 - 档位自动调整， 1- 强制档位 */
    UINT16                              CarrierMode:1;  /* 0 - 单载波， 1 - 双载波 */
    UINT16                              BlockMode:1;    /* 0 - no block, 1 - block */
}W_RX_AGC_GAIN_CFG_STRU;

/*****************************************************************************
 结构名    : W_TX_PA_PARA_CFG_STRU
 协议表格  :
 结构说明  : WCDMA RF慢速校准接口
*****************************************************************************/
typedef struct
{
    UINT16                              ucPaVcc:8;                              /* PA Vcc 的电压控制字 */
    UINT16                              ucPaBias:8;                             /* PA Bias电压控制字，MMMB PA时该数据有效，普通PA时WDSP直接丢弃该字段 */
}W_TX_PA_PARA_CFG_STRU;

typedef struct
{
    UINT16                              ucPdDcOffset:8;                          /* PD DCOFFSET的值,取值范围[0,31] */
    UINT16                              ucPdVga:8;                               /* PD VGA的值,其中bit1表示衰减是否打开，Bit[6:4]表示VGA的取值 */
}W_TX_PD_PARA_CFG_STRU;

typedef struct
{
    UINT16                              ucRficMode:8;                             /* RFIC的工作模式，0:正常模式；1:Voice模式 */ /*W_TX_RFIC_MODE_ENUM_UINT8*/
    UINT16                              ucTxPaMode:8;                             /* 0:自动控制;1:高增益;2:中增益;3:低增益 */
}W_TX_RFIC_PA_MODE_STRU;


typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* 原语类型 */
    UINT16                              usRsv;                                  /* 保留位   */

    UINT32                              ulMask;                                 /* 掩码位，根据bit位表示下面的字段是否有效，bit位的映射关系参见MASK_W_TRX_CFG_* */

    /* Afc Para Cfg */
    PHY_RF_CAL_AFC_PARA_STRU            stAfcPara;                              /* AFC控制字 */

    /* Tx Para Cfg */
    UINT16                              usTxBand;                               /* W模BAND:1表示BAND1,2表示BAND2,依次类推 */
    UINT16                              usTxChannel;                            /* W模TX频点号,如BAND1的9750 */
    UINT16                              usTxEnable;                             /* 低8Bit定义 ---Tx发射 0:不使能,1:使能
                                                                                   高8Bit定义 ---调制方式 0:正常调制,1:CW单音信号, 2:双音信号
                                                                                */
    W_TX_RFIC_PA_MODE_STRU              stTxRficPaMode;
    W_TX_POWER_CTRL_MODE_ENUM_UINT16    usTxPowerCtrlMode;                      /* 功率控制模式，和unTxPowerPara使用同样的掩码。
                                                                                    0：功率模式，此时unTxPowerPara.usTxPower10th有效；
                                                                                    1：功率衰减模式，此时unTxPowerPara.usTxPowerAtten10th有效；
                                                                                    2：寄存器控制方式，此时unTxPowerPara.stTxRegCtrlPara有效；*/
    PHY_RF_CAL_W_TX_POWER_PARA_UNION    unTxPowerPara;                          /* 功率控制参数，和ucTxPowerCtrlMode使用同样的掩码 */

    /* Pa Volt Para Cfg */
    W_TX_PA_PARA_CFG_STRU               stPaParaCfg;
    UINT16                              usSelfCal;                              /* 自校准项目，其中高8bit：
                                                                                    0 - 正常模式，或者从自校准模式回到正常模式
                                                                                    1 - W IIP2自校准调试模式，此时工具保证下发的Tx channel = Rx Channel
                                                                                    2 - W IQ Mismatch自校准模式，此时工具保证下发的Rx Channel = Tx Channel
                                                                                    3 - G IQ Mismatch自校准模式，GSM模式下本来就只有1个信道号，此时请DSP自己选择
                                                                                        Tx Band和Tx channel
                                                                                        其中Tx Band含义： 0-GSM850,1-GSM900，2-DCS1800，3-PCS1900
                                                                                    4 - W ET LUT自校准
                                                                                    5 - W DPD LUT自校准
                                                                                   其中低8bit含义：
                                                                                   W IIP2校准模式下，
                                                                                   0 - 主集+分集
                                                                                   1 - 主集
                                                                                   W/G IQ Mismatch校准模式下，
                                                                                   0 - feedback
                                                                                   1 - 直接发送到天线口

                                                                                   注意：在自校准模式下，其他掩码也应该能正常工作
                                                                                   注意：如果从自校准模式回退到正常模式，DSP需要把RFIC和BBP配置回正常模式
                                                                                */

    /* Rx Para Cfg */
    UINT16                              usRxBand;                               /* W模BAND:1表示BAND1,2表示BAND2,依次类推 */
    UINT16                              usRxChannel;                            /* W模RX频点号,如BAND1的10700 */
    UINT16                              usRxCrossBand;                          /* 异频测量的Band。
                                                                                    如果用户使能该字段*，则AGC表配置为usRxBand对应的AGC表，
                                                                                    工作的Band和频点配置为usRxCrossBand和usRxCrossChannel */
    UINT16                              usRxCrossChannel;                       /* 异频测量的频点 */

    UINT16                              usRxEnable;                             /* 0:不使能,1:使能 */
    UINT16                              usRxAntSel;                             /* 1:主集天线;2:分集天线 */
    W_RX_AGC_GAIN_CFG_STRU              stRxAgcGain;                            /* BIT[15] : 0:No Block， 1:Block;
                                                                                   BIt[14] : 0:单载波，   1：双载波
                                                                                   BIT[13] : 0:档位自动调整 1:档位强配
                                                                                   BIT[2:0]: 0:第一档(增益最高的),依次类推 */
    UINT16                              usRsv3;                                 /* 结构对齐 */

    /* 下面的参数是发射UPA需要使用的--为了不影响现有的AT命令,仅在该结构体后面增加相关变量 */
    UINT16                              usUpaEnable;                            /* LMT发射UPA信号打开关闭.0:关闭;1:打开 */
    UINT16                              usTxCarrMode;                           /* TX载波模式.0:单载波;1:双载波 */
    PHY_RF_CAL_W_TX_UPA_PARA_STRU       stPrimCarr;                             /* 主载波相关的参数 */
    PHY_RF_CAL_W_TX_UPA_PARA_STRU       stSecondCarr;                           /* 辅载波相关的参数 */


    UINT16                              usDpaEnable;	                        /* LMT发射DPA信号打开关闭.0:关闭;1:打开 */
    UINT16                              usRsv4;
    PHY_RF_CAL_W_TX_DPA_PARA_STRU       stDpaPara;                              /* DPA相关的参数 */

    INT16                               sIp2IValue;                             /* IP2 I通道码字 */
    INT16                               sIp2QValue;                             /* IP2 Q通道码字 */

    UINT16                              usEvmIndOnOff;                          /* EVM数据上报是否使能，1表示打开上报，0表示关闭上报 */
    UINT16                              usEnableReportData;                     /* EVM原始数据是否上报，1表示上报，0表示不上报 */
    /* ET delay 由 MASK_W_TRX_CFG_TX_ET_TIMEDELAY 控制 */
    INT16                               sSignalDelay;                           /* 信号通道只有整数延时寄存器配置  */
    INT16                               sEnvelopDelay;                          /* 包络通道延时,单位为1/1024sample */

    /* 激活哪一张dpd表，范围0~9 ，由 MASK_W_TRX_CFG_TX_DPD 控制 */
    INT16                               sDpdTableIndex;

    /* IQ幅度配置，，由 MASK_W_TRX_CFG_TX_V_IQ 控制
       如果用户配置了需要遍历IQ，且使能 MASK_W_TRX_CFG_PD_ONOFF
       则DSP会遍历Viq，并找到增益压缩点，通过PD上报原语上报增益压缩点时的PD检测值
       PD上报原语参见PHY_RF_CAL_W_RF_TX_PD_IND_STRU
    */
    INT16                               sViq;
    INT16                               sViqStep;

    /* 由MASK_W_TRX_CFG_TX_ET_COMP控制 */
    INT16                               sEtPowerCompression;                    /* ET校准时的增益压缩点，单位0.1dB */
    UINT16                              usEnableEtDpdComp;                      /* BIT0:表示ET补偿使能，BIT1表示DPD补偿使能 */
    UINT16                              usRsv5;
    INT16                               sEtFreqTempComp;                        /* ET频补温补，单位0.1dB */
    INT16                               sDpdFreqTempComp;                       /* DPD频补温补，单位0.1dB */


}PHY_RF_CAL_W_TRX_PARA_CFG_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_W_PD_PARA_CFG_REQ_STRU
 协议表格  :
 结构说明  : W PD参数配置原语
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* 原语类型 */
    UINT16                              usRsv;                                  /* 保留位 */

    UINT16                              usMask;                                 /* refer to MASK_CAL_W_PD_* */

    /* PD Cfg */
    UINT16                              usPdInputThrough;                       /* 0 - 关闭PD的输入信号， 1 - 打开PD的输入信号 */
    W_TX_PD_PARA_CFG_STRU               stTxPdPara;                             /* PD VGA参数 PD DC的参数 */
}PHY_RF_CAL_W_PD_PARA_CFG_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_W_RF_MSG_CNF_STRU
 协议表格  :
 结构说明  : W TRX 快慢速校准通用CNF
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usComponentId;                          /* 组件 ID */
    UINT16                              usRecMsgID;                             /* 对应的下发Msg ID */
    UINT16                              usErrorCode;
}PHY_RF_CAL_W_RF_MSG_CNF_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_W_RF_DCXO_CAL_MSG_CNF_STRU
 协议表格  :
 结构说明  : W DCXO校准通用CNF
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usComponentId;
    UINT16                              usRecMsgID;                             /* 对应的下发Msg ID */
    UINT16                              usErrorCode;
}PHY_RF_CAL_W_RF_DCXO_CAL_MSG_CNF_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_W_RF_TX_PD_IND_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usComponentId;                          /* 组件 ID */
    INT16                               sPdHkadc;
    UINT16                              usRsv2;
}PHY_RF_CAL_W_RF_TX_PD_IND_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_COMM_DATA_DPD_LUT_RPT_STRU
 协议表格  :
 结构说明  : DPD上报数据
*****************************************************************************/
typedef struct
{
    UINT32                              ulBitMap;
    UINT32                              ulLen;
    PHY_CAL_COMPLEX_DATA_INT16_STRU     ulDpdLut[64];
}PHY_RF_CAL_COMM_DATA_DPD_LUT_RPT_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_COMM_DATA_ET_LUT_RPT_STRU
 协议表格  :
 结构说明  : ET上报数据
*****************************************************************************/
typedef struct
{
    UINT32                              ulBitMap;
    UINT32                              ulLen;
    INT16                               sPdHkadc;
    UINT16                              usCompressSingleToneV;
    UINT32                              ulCompressMrxCorr;                      /* MRX电路检测的相关值 */
    UINT32                              ulMrxCorr[64];                          /* 64阶MRX值 */
}PHY_RF_CAL_COMM_DATA_ET_LUT_RPT_STRU;


/*****************************************************************************
 结构名    : NV_W_ET_DELAY_FREQ_COMP_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    INT16 asEtDelayFreqComp[8];
}NV_W_ET_DELAY_FREQ_COMP_STRU;

/*****************************************************************************
 结构名    : ANYBAND_W_ET_FREQ_COMP_CAL_DATA_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                          usBandId;
    UINT16                          usRsv;
    NV_W_ET_DELAY_FREQ_COMP_STRU    stNvEtDelayFreqComp;
}ANYBAND_W_ET_DELAY_CAL_DATA_STRU;

/*****************************************************************************
 结构名    : PHY_RF_W_ET_FREQ_COMP_SELF_CAL_IND_DATA_STRU
 协议表格  : TDB：需要支持变长
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT32                                      ulBitMap;
    UINT32                                      ulLen;

    UINT16                                      usErrCode;                              /* Reference to RF_CAL_SELF_CAL_* */
    UINT16                                      usErrBand;                              /*存放校准失败的频段*/
    UINT16                                      usSelfCalMask;                          /*存放DSP自校准项*/
    UINT16                                      usBandCnt;                              /*存放DSP频段个数*/
    ANYBAND_W_ET_DELAY_CAL_DATA_STRU            astCalData[SELF_CAL_BAND_ID_MAX_COUNT];
}PHY_RF_CAL_COMM_DATA_ET_DELAY_RPT_STRU;

/*****************************************************************************
 结构名    : PHY_CAL_RF_COMM_DATA_RPT_MSG_HEAD_STRU
 协议表格  :
 结构说明  : 通用数据上报结构头
*****************************************************************************/
typedef struct
{
    PHY_CAL_MSG_DEAD_STRU               stMsgHead;
    UINT32                              ulTestItemsBitMap;                      /* 内容指示，若包括某个内容,置上相应bit */

    /**********************************************************
    后面跟上报的内容，包括各内容指示，各内容长度
    UINT32                              ulTest1BitMap;                          第一组数据内容指示，若包括某个内容,置上相应bit
    UINT32                              ulTest1Len;                             第一组数据byte个数，从ulTest1BitMap(包括)开始到ulTest2BitMap(不包括)结束
    UINT16                              usTest1Data[n];                         第一组数据
    UINT32                              ulTest2BitMap;                          第二组数据内容指示，若包括某个内容,置上相应bit
    UINT32                              ulTest2Len;                             第二组数据byte个数，从ulTest2BitMap(包括)开始
    UINT16                              usTest2Data[n];                         第二组数据
    ..........                                                                  后面类似

    *********************************************************/

}PHY_CAL_RF_COMM_DATA_RPT_MSG_HEAD_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_W_RX_RSSI_MEAS_REQ_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    UINT16                              usMeasNum;
    UINT16                              usInterval;
}PHY_RF_CAL_W_RX_RSSI_MEAS_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_W_RX_RSSI_MEAS_IND_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usComponentId;                          /* 组件 ID */
    INT16                               sRSSI;
    UINT16                              usAgcState;
}PHY_RF_CAL_W_RX_RSSI_MEAS_IND_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_W_SELF_CAL_REQ_STRU
 协议表格  : 自校准的校准项和Band
 结构说明  : WCDMA RF Self Cal接口
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    UINT16                              usSelfCalMask;                          /* reference to MASK_SELF_CAL_* */
    UINT16                              usModemIndex;                           /* 0-modem0,1-modem1 */
    UINT32                              ulBandMask;                             /* 根据Bit位判断是否支持哪些Band，其中根据Msg ID判断是W band还是G Band */
    UINT32                              ulBandExtMask;                          /* 扩展用，目前预留 */
}PHY_RF_CAL_W_SELF_CAL_REQ_STRU;


/*****************************************************************************
 结构名    : NV_TX_IQ_MISMATCH_DCR_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    INT16                               sAmp;
    INT16                               sPhase;
    INT16                               sDci;
    INT16                               sDcq;
}NV_TX_IQ_MISMATCH_STRU;

/*****************************************************************************
 结构名    : RESULT_TX_IQ_MISMATCH_DCR_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    INT16                               sAmpCorr;
    INT16                               sDcCorr;
}RESULT_TX_IQ_MISMATCH_STRU;

/*****************************************************************************
 结构名    : RX_IQ_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    INT16                               sI;
    INT16                               sQ;
}RX_IQ_STRU;


/*****************************************************************************
 结构名    : ANY_CARRIER_DC_OFFSET_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    RX_IQ_STRU                          stNoBlockDcOffset[W_RX_NOBLOCK_AGC_GAIN_COUNT];
    RX_IQ_STRU                          stBlockDcOffset[W_RX_BLOCK_AGC_GAIN_COUNT];
}ANY_CARRIER_DC_OFFSET_STRU;

/*****************************************************************************
 结构名    : ANY_ANT_ANY_CARRIER_DC_OFFSET_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    ANY_CARRIER_DC_OFFSET_STRU          stCarrier[2];                                    /* 其中0表示SC，1表示DC */
}ANY_ANT_ANY_CARRIER_DC_OFFSET_STRU;

/*****************************************************************************
 结构名    : NV_W_RX_DCOFFSET_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    ANY_ANT_ANY_CARRIER_DC_OFFSET_STRU  stAnt[2];                                /* 其中0表示AT1,1表示AT2 */
}NV_W_RX_DCOFFSET_STRU;

/*****************************************************************************
 结构名    : RESULT_W_RX_DCOFFSET_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef NV_W_RX_DCOFFSET_STRU RESULT_W_RX_DCOFFSET_STRU;

/*****************************************************************************
 结构名    : ANY_CHAN_W_RX_IP2_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    RX_IQ_STRU                          stDivOn;
    RX_IQ_STRU                          stDivOff;
}ANY_CHAN_W_RX_IP2_STRU;

/*****************************************************************************
 结构名    : NV_W_RX_IP2_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    ANY_CHAN_W_RX_IP2_STRU              stChan[3];                                  /* 0：高信道，1：中信道，2：低信道 */
}NV_W_RX_IP2_STRU;

/*****************************************************************************
 结构名    : W_RX_IMD2_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    INT16                               sIMD2;
    INT16                               sRsv;
}W_RX_IMD2_STRU;

/*****************************************************************************
 结构名    : ANY_CHAN_W_RX_IMD2_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    W_RX_IMD2_STRU                      stDivOn;
    W_RX_IMD2_STRU                      stDivOff;
}ANY_CHAN_W_RX_IMD2_STRU;

/*****************************************************************************
 结构名    : RESULT_W_RX_IP2_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    ANY_CHAN_W_RX_IMD2_STRU  stChan[3];                                  /* 0：高信道，1：中信道，2：低信道 */
}RESULT_W_RX_IP2_STRU;

/*****************************************************************************
 结构名    : ANY_BAND_W_SELF_CAL_IND_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usBandId;                               /* 按MASK位上报 */
    UINT16                              usRsv;
    NV_TX_IQ_MISMATCH_STRU              stNvTxIqMismatch;
    RESULT_TX_IQ_MISMATCH_STRU          stResultTxIqMismatch;
    NV_W_RX_DCOFFSET_STRU               stNvRxDcOffset;
    RESULT_W_RX_DCOFFSET_STRU           stResultRxDcOffset;
    NV_W_RX_IP2_STRU                    stNvRxIp2;
    RESULT_W_RX_IP2_STRU                stResultRxIp2;
}ANY_BAND_WG_SELF_CAL_IND_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_W_SELF_CAL_IND_STRU
 协议表格  : TDB：需要支持变长
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usComponentId;                          /* 组件 ID */
    UINT16                              usErrCode;                              /* Reference to RF_CAL_SELF_CAL_* */
    UINT16                              usErrBand;                              /*存放校准失败的频段*/
    UINT16                              usSelfCalMask;                          /*存放DSP自校准项*/
    UINT16                              usBandCnt;                              /*存放DSP频段个数*/
    ANY_BAND_WG_SELF_CAL_IND_STRU       astSelfCalRlt[SELF_CAL_BAND_ID_MAX_COUNT];
}PHY_RF_CAL_W_SELF_CAL_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_C_SELF_CAL_IND_STRU
 协议表格  : TDB：需要支持变长
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usComponentId;                          /* 组件 ID */

    UINT16                              usErrCode;                              /* Reference to RF_CAL_SELF_CAL_* */
    UINT16                              usErrBand;                              /*存放校准失败的频段*/
    UINT16                              usSelfCalMask;                          /*存放DSP自校准项*/
    UINT16                              usBandCnt;                              /*存放DSP频段个数*/
    ANY_BAND_WG_SELF_CAL_IND_STRU       astSelfCalRlt[CDMA_SELF_CAL_BAND_ID_MAX_COUNT];
}PHY_RF_CAL_C_SELF_CAL_IND_STRU;

/*****************************************************************************
 结构名    : ANY_STEP_PARA_STRU
 协议表格  :
 结构说明  : WCDMA RF快速校准单个Step的参数
*****************************************************************************/
typedef struct
{
    W_RX_AGC_GAIN_CFG_STRU              stRxAgcGain;                            /* BIt[15] : 0: No Block,   1:Block;
                                                                                   BIT[14] : 0:单载波，     1:双载波
                                                                                   BIT[13] : 0:档位自动调整 1:档位强配
                                                                                   BIT[2:0]: 0:第一档(增益最高的)，依次类推*/
    W_TX_RFIC_PA_MODE_STRU              stTxRficPaMode;
    PHY_RF_CAL_W_TX_POWER_PARA_UNION    unTxPowerPara;
    W_TX_PA_PARA_CFG_STRU               stPaParaCfg;
    W_TX_PD_PARA_CFG_STRU               stTxPdPara;                              /* PD VGA参数 PD DC的参数 */
}ANY_STEP_PARA_STRU;


/*****************************************************************************
 结构名    : W_TRX_FAST_FRAME_STRU
 协议表格  :
 结构说明  : WCDMA RF快速校准接口
*****************************************************************************/
typedef struct
{
    UINT16                              usBand;
    UINT16                              usStepCnt;                              /* [1, 16] */
    UINT16                              usTxArfcn;
    UINT16                              usRxArfcn;
    UINT16                              usTxStepPattern;
    UINT16                              usRxStepPattern;
    ANY_STEP_PARA_STRU                  astStepData[W_TRX_MAX_STEP_COUNT];
}W_TRX_FAST_FRAME_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_W_TRX_FAST_CAL_REQ_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;

    UINT16                              usTxMask;                               /* BIT[3]: PD DCOFFSET是否生效
                                                                                   BIT[2]: PD VGA是否生效
                                                                                   BIT[1]: APT是否生效
                                                                                   BIT[0]: PD检测是否使能*/ /* Reference to MASK_W_TRX_FAST_CAL_REQ_TXMASK_* */
    W_TX_POWER_CTRL_MODE_ENUM_UINT16    usTxPowerCtrlMode;                      /* 功率控制模式，和unTxPowerPara使用同样的掩码。
                                                                                   0：功率模式， 此时unTxPowerPara.usTxPower10th有效；
                                                                                   1：功率衰减模式，此时unTxPowerPara.usTxPowerAtten10th有效；
                                                                                   2：寄存器控制方式，此时unTxPowerPara.stTxRegCtrlPara有效；*/

    W_FAST_STEP_WIDTH_ENUM_UINT16       usStepWidthMs;                          /* Reference to W_FAST_STEP_WIDTH_ENUM */
    UINT16                              usRsv2;

    UINT16                              usTxFrameCnt;                           /* [1, W_TRX_MAX_SWEEP_FRAME_CNT] */
    UINT16                              usRxFrameCnt;                           /* [1, W_TRX_MAX_SWEEP_FRAME_CNT] */

    /* 接口文档中按照最大长度定义，方便部件直接使用该结构申请内存，
       消息中实际长度为有效帧数 */
    W_TRX_FAST_FRAME_STRU               astSweepFrame[W_TRX_MAX_SWEEP_FRAME_COUNT];
}PHY_RF_CAL_W_TRX_FAST_CAL_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_W_TRX_FAST_CAL_REQ_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* 原语类型 */
    UINT16                              usComponent;                            /* 器件类型 */
    UINT32                              ulMask;                                 /* 下行Band */

    UINT16                              usRxBand;                               /* 下行Band */
    UINT16                              usRsv;                                  /* 保留 */
    UINT32                              ulRxChannel;                            /* 下行频点 */

    W_RX_AGC_GAIN_CFG_STRU              stRxAgcGain;                            /* BIT[15] : 0:No Block， 1:Block;
                                                                               BIt[14] : 0:单载波，   1：双载波
                                                                               BIT[13] : 0:档位自动调整 1:档位强配
                                                                               BIT[2:0]: 0:第一档(增益最高的),依次类推 */
    UINT16                              usRes;

    UINT16                              usC2CalEnable;                          /* C2是否校准 */
    UINT16                              usC2Fix;                                /* C2值 */
    UINT16                              usC2LowerLimit;                         /* C2校准下限 */
    UINT16                              usC2UpperLimit;                         /* C2校准上限 */

    UINT16                              usC1CalEnable;                          /* C1是否校准 */
    UINT16                              usC1Fix;                                /* C1值 */

    W_TX_RFIC_PA_MODE_STRU              stTxRficPaMode;
    W_TX_POWER_CTRL_MODE_ENUM_UINT16    usTxPowerCtrlMode;                      /* 功率控制模式，和unTxPowerPara使用同样的掩码。
                                                                                    0：功率模式，此时unTxPowerPara.usTxPower10th有效；
                                                                                    1：功率衰减模式，此时unTxPowerPara.usTxPowerAtten10th有效；
                                                                                    2：寄存器控制方式，此时unTxPowerPara.stTxRegCtrlPara有效；*/
    PHY_RF_CAL_W_TX_POWER_PARA_UNION    unTxPowerPara;                          /* 功率控制参数，和ucTxPowerCtrlMode使用同样的掩码 */

    UINT16                              ausRes[32];

}PHY_RF_CAL_W_DCXO_SELF_CAL_REQ_STRU;

/*****************************************************************************
 结构名    : RAW_IQ_DATA_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/

typedef struct
{
    UINT16                             uhwExpOut;
    UINT16                             usRsv;
    UINT32                             uwA1SigOut;
}COFFICIENT_DATA_STRU;

typedef struct
{
    INT16                              sIData;
    INT16                              sQData;
}RAW_IQ_DATA_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_W_RF_RX_EVM_RESULT_IND_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;
    UINT16                              usComponentId;                          /* 组件 ID */
    UINT16                              usNum;   /*上报的第几次数据,从1开始*/
    UINT16                              usEvm;
    INT32                               swFreq;
    INT32                               swInitialPhase;
    UINT32                              ulReportDataCount;
    RAW_IQ_DATA_STRU                    astIqData[W_RX_EVM_REPORT_DATA_COUNT];
}PHY_RF_CAL_W_RF_RX_EVM_IND_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_W_TX_PA_VCC_UNION
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef union
{
    INT16                               sTxEtDac;
    W_TX_PA_PARA_CFG_STRU               stPaParaCfg;
}PHY_RF_CAL_W_TX_PA_VCC_UNION;


/*****************************************************************************
 结构名    : ET_STEP_PARA_STRU
 协议表格  :
 结构说明  : WCDMA ET快速校准单个Step的参数
*****************************************************************************/
typedef struct
{
    UINT16                              usRsv;
    W_TX_RFIC_PA_MODE_STRU              stTxRficPaMode;
    PHY_RF_CAL_W_TX_POWER_PARA_UNION    unTxPowerPara;
    PHY_RF_CAL_W_TX_PA_VCC_UNION        stPaParaCfg;
    INT16                               sEtPowerCompression;                      /* ET校准时的增益压缩点，单位0.1dB */
}ET_STEP_PARA_STRU;


/*****************************************************************************
 结构名    : ET_FAST_FRAME_STRU
 协议表格  :
 结构说明  : WCDMA ET快速的帧结构
*****************************************************************************/
typedef struct
{
    UINT16                              usBand;
    UINT16                              usStepCnt;                              /* [1, 16] */
    UINT16                              usTxArfcn;
    UINT16                              usRsv;
    UINT16                              usTxStepPattern;
    UINT16                              usRsv2;
    ET_STEP_PARA_STRU                   astStepData[W_TRX_MAX_STEP_COUNT];
}ET_FAST_FRAME_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_W_ET_FAST_REQ_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;

    UINT16                              usMask;                                 /*
                                                                                   BIT[1]：增益压缩点是否生效，如果增益压缩点生效，则每个电压下DSP需要遍历Viq，完成后找出压缩点对应的Viq，并上报压缩点对应的MRX值
                                                                                   BIT[0]: PD检测是否使能，如果PD检测使能，则找到压缩点后，需要重发一次，读取对应的PD值并上报；*/
                                                                                /* Reference to PHY_RF_CAL_W_ET_FAST_REQ_STRU_* */
    W_TX_POWER_CTRL_MODE_ENUM_UINT16    usTxPowerCtrlMode;                      /* 功率控制模式，和unTxPowerPara使用同样的掩码。
                                                                                   0：功率模式， 此时unTxPowerPara.usTxPower10th有效；
                                                                                   1：功率衰减模式，此时unTxPowerPara.usTxPowerAtten10th有效；
                                                                                   2：寄存器控制方式，此时unTxPowerPara.stTxRegCtrlPara有效；*/

    UINT16                              usRsv1;                                 /* 预留 */
    UINT16                              usCalAlgorithm;                         /* 0 - 等压缩模式，1 - 等增益模式 */
    UINT16                              usTxFrameCnt;                           /* [1, W_TRX_MAX_SWEEP_FRAME_CNT] */
    UINT16                              usRsv2;                                 /* 预留 */

    /* 接口文档中按照最大长度定义，方便部件直接使用该结构申请内存，
       消息中实际长度为有效帧数 */
    ET_FAST_FRAME_STRU               astSweepFrame[W_TRX_MAX_SWEEP_FRAME_COUNT];
}PHY_RF_CAL_W_ET_FAST_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_W_RF_DCXO_SELFCAL_IND_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;
    UINT16                              usComponentId;
    UINT32                              ulErrorCode;
    UINT16                              usC2Fix;
    UINT16                              usC1Fix;
    INT16                               sInitTemp;
    INT16                               sInitFreq;
    COFFICIENT_DATA_STRU                stA0;
    COFFICIENT_DATA_STRU                stA1;
    COFFICIENT_DATA_STRU                stA2;
    COFFICIENT_DATA_STRU                stA3;
    VOS_INT16                           shwTmax;                                /* XO最大工作温度 */
    VOS_INT16                           shwTmin;                                /* XO最小工作温度 */
    INT16                               sDcxoInitTemp;                          /* 曲线计算初始温度 */
    INT16                               sBeforeTempUp;                          /* a0、a1校准前温度 */
    INT16                               sAfterTempUp;                           /* a0、a1校准后温度 */
    UINT16                              ausRsv[15];
}PHY_RF_CAL_W_RF_DCXO_SELFCAL_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_W_TRX_FAST_CAL_IND_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usComponentId;                          /* 组件 ID */
    UINT16                              usRssiCnt;                              /* RSSI测量值的个数 */
    UINT16                              usPowerDetectorCnt;

    /* 接口文档中按照最大长度定义，方便部件直接使用该结构申请内存，
       消息中实际长度为有效帧数 */
    INT16                               asReportData[W_TRX_MAX_REPORT_COUNT];     /*Rssi At1(0.125dBm)+Rssi At2(0.125dBm)+PD测量结果 */
}PHY_RF_CAL_W_TRX_FAST_CAL_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_G_TX_REG_CTRL_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usRficGainCtrl;                         /* RF Gain的控制寄存器值，有RF Gain和BB Gain组合而成 */
    INT16                               sDbbAtten10th;                          /* Dbb的衰减值，取值范围[-70,+10] */
}PHY_RF_CAL_G_TX_REG_CTRL_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_G_TX_POWER_PARA_UNION
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef union
{
    UINT16                              usTxAgc;                                /* 对应Tx Vpa控制模式 */
    INT16                               sTxPower10th;                           /* 对应功率模式 */
    INT16                               sTxPowerAtten10th;                      /* 功率衰减模式 */
    PHY_RF_CAL_G_TX_REG_CTRL_STRU       stTxRegCtrlPara;                        /* 寄存器控制模式 */
}PHY_RF_CAL_G_TX_POWER_PARA_UNION;

/*****************************************************************************
 结构名    : G_RF_SINGLE_SLOT_CFG_STRU
 协议表格  :
 结构说明  : G TX GSM RF慢速校准接口
*****************************************************************************/
typedef struct
{
    UINT16                              ucTxModType:8;                          /* 发射调制方式:0表示GMSK调制;1表示8PSK调制  G_TX_MODULATION_TYPE_ENUM_UINT8 */
    UINT16                              ucTxPowerCtrlMode:8;                    /* 发射控制方式：G_TX_POWER_CTRL_MODE_ENUM_UINT16
                                                                                    0：GMSK电压控制,此方式下usTxVpa要配置；
                                                                                    1：功率控制,此方式下usTxPower10th要配置；
                                                                                    2：功率衰减模式，此方式下sTxPowerAtten10th要配置；
                                                                                    3：寄存器控制模式，此方式下stTxRegCtrlPara要配置*/
}G_TX_MODE_TYPE_POWER_CTRL_CFG_STRU;

typedef struct
{
    UINT16                              usTxMode;                               /* 0： burst,1:Continue */
    G_TX_MODE_TYPE_POWER_CTRL_CFG_STRU  stTxModTypePowerCtrl;
    PHY_RF_CAL_G_TX_POWER_PARA_UNION    unTxPowerPara;

    UINT16                              usPaVcc;                                /* EDGE PA Vcc控制电压，目前不支持 */
    UINT16                              usPaVramp;                              /* EDGE PA Vramp控制电压，在调制方式为8PSK，非功率控制模式下有效 */
    UINT16                              usPaGainIndex;                          /* linea pa增益索引( 0:auto,1:ultra high,2:high,3:mid,4:low ) */
    UINT16                              usRsv;                                  /* 保留 */
}G_RF_SINGLE_SLOT_CFG_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_TX_PARA_CFG_REQ_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;

    UINT32                              ulMask;                                 /* Reference to MASK_CAL_RF_G_TX_* */

    /* Afc Para Cfg */
    PHY_RF_CAL_AFC_PARA_STRU            stAfcPara;                              /* AFC控制字 */

    UINT16                              usFreqNum;                              /* (Band << 12) | Arfcn */
    UINT16                              usTxEnable;                             /* 发送使能控制:0x5555-使能发送;0xAAAA-停止发送;TSC 0; */
    UINT16                              usDataPattern;                          /* 0：All 0；1：All 1；2：Random */
    UINT16                              usSlotCnt;                              /* 配置时隙个数，范围1~4和8,不需指定具体使用哪些时隙，DSP自动配置1~4时隙发射 */
    G_RF_SINGLE_SLOT_CFG_STRU           astSlotCfg[G_TX_PARA_MAX_SLOT_CNT_PER_FRAME]; /* 每个时隙的配置情况 */
}PHY_RF_CAL_G_TX_PARA_CFG_REQ_STRU;

/*****************************************************************************
 结构名    : G_SELF_CAL_RESULT_STRU
 协议表格  :
 结构说明  : GSM RF自校准接口
             启动G模自校准的Req接口与W模相同
*****************************************************************************/
typedef PHY_RF_CAL_W_SELF_CAL_REQ_STRU PHY_RF_CAL_G_SELF_CAL_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_G_SELF_CAL_IND_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef PHY_RF_CAL_W_SELF_CAL_IND_STRU PHY_RF_CAL_G_SELF_CAL_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RX_PARA_CFG_REQ_STRU
 协议表格  :
 结构说明  : G Rx
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv1;

    UINT16                              usMask;                                 /* Reference to MASK_CAL_RF_G_RX_* */
    UINT16                              usFreqNum;                              /* (Band << 12) | Arfcn */
    UINT16                              usRxMode;                               /* 0:burst接收; 1:连续接收;目前只支持burst接收方式 */
    UINT16                              usAGCMode;                              /* Fast AGC,Slow AGC */
    UINT16                              usAGCGain;                              /* AGC档位：0-第一档…… */
    UINT16                              usRsv2;
}PHY_RF_CAL_G_RX_PARA_CFG_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RX_RSSI_MEAS_REQ_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv1;
    UINT16                              usMeasNum;
    UINT16                              usRsv2;
}PHY_RF_CAL_G_RX_RSSI_MEAS_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RX_RSSI_MEAS_IND_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usComponentId;                          /* 组件 ID */
    INT16                               sRSSI;
    UINT16                              usRsv2;
}PHY_RF_CAL_G_RX_RSSI_MEAS_IND_STRU;

/*****************************************************************************
 结构名    : G_RF_TX_STEP_STRU
 协议表格  :
 结构说明  : GSM RF快速校准帧结构
*****************************************************************************/
typedef struct
{
    PHY_RF_CAL_G_TX_POWER_PARA_UNION    unTxPowerPara;
    UINT16                              usPaVcc;
    UINT16                              usPaVramp;                              /* EDGE Pa控制电压 */
    UINT16                              usPaGainIndex;                          /* linea pa增益索引( 0:auto,1:ultra high,2:high,3:mid,4:low ) */
}G_RF_TX_STEP_STRU;

/*****************************************************************************
 结构名    : G_RF_TX_SEQUENCE_STRU
 协议表格  :
 结构说明  : GSM RF快速校准接口
*****************************************************************************/
typedef struct
{
    UINT16                              usChannel;
    UINT16                              usStepPattern;                          /* 按Bit位表示当前时隙是否工作 */

    G_RF_TX_STEP_STRU                   astStepValue[G_TX_MAX_STEP_COUNT];        /*当前最大只支持四时隙*/
}G_RF_TX_SEQUENCE_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_TX_FAST_CAL_REQ_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;

    UINT16                              usTxMask;                               /* Bit[0]:APT是否生效
                                                                                用MASK位MASK_G_TX_FAST_CAL_REQ_TXMASK_APT表示*/

    G_TX_MODE_TYPE_POWER_CTRL_CFG_STRU  stTxModTypePowerCtrl;

    UINT16                              usFrameCnt;
    UINT16                              usRsv2;                                 /* 后续扩展预留 */

    /* 接口文档中按照最大长度定义，方便部件直接使用该结构申请内存，
       消息中实际长度为有效帧数 */
    G_RF_TX_SEQUENCE_STRU               astTxSequence[G_TRX_MAX_SWEEP_FRAME_COUNT];
}PHY_RF_CAL_G_TX_FAST_CAL_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RF_MSG_CNF_STRU
 协议表格  :
 结构说明  : G TRX 快慢速校准通用CNF
*****************************************************************************/
typedef PHY_RF_CAL_W_RF_MSG_CNF_STRU PHY_RF_CAL_G_RF_MSG_CNF_STRU;
typedef PHY_RF_CAL_W_RF_MSG_CNF_STRU PHY_RF_CAL_WG_RF_MSG_CNF_STRU;


/*****************************************************************************
 结构名    : G_RF_RX_SEQUENCE_STRU
 协议表格  :
 结构说明  : G Rx
*****************************************************************************/
typedef struct
{
    UINT16                              usChannel;
    UINT16                              ausAgcGain[G_RX_MAX_STEP_COUNT];          /* 每帧必须配7个测量档位 */
}G_RF_RX_SEQUENCE_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RX_FAST_CAL_REQ_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;

    UINT16                              usFrameCnt;                             /* 测量帧数 */
    UINT16                              usRsv2;

    /* 接口文档中按照最大长度定义，方便部件直接使用该结构申请内存，
       消息中实际长度为有效帧数 */
    G_RF_RX_SEQUENCE_STRU               astRxSequence[G_TRX_MAX_SWEEP_FRAME_COUNT];
}PHY_RF_CAL_G_RX_FAST_CAL_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RX_FAST_CAL_IND_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usComponentId;

    UINT16                              usRssiNum;                              /* 测量个数，最大为G_RX_MAX_RSSI_CNT个,不包括同步帧 */
    UINT16                              usRsv2;

    /* 接口文档中按照最大长度定义，方便部件直接使用该结构申请内存，
       消息中实际长度为有效帧数 */
    INT16                               asRssiValue[G_RX_MAX_RSSI_COUNT];         /* 每帧上报7个点，最大G_RX_MAX_RSSI_CNT个 */
}PHY_RF_CAL_G_RX_FAST_CAL_IND_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RX_DCR_START_REQ_STRU
 协议表格  :
 结构说明  : G Rx DCR
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv1;

    UINT16                              usBandMask;                             /* Bit0:GSM850; Bit1:GSM900; Bit2:DCS; Bit3:PCS; */
    UINT16                              usRsv2;
}PHY_RF_CAL_G_RX_DCR_REQ_STRU;

/*****************************************************************************
 结构名    : NV_G_RX_DCOFFSET_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    INT16                               sInitDcocI;
    INT16                               sInitDcocQ;
    INT16                               sDcI;
    INT16                               sDcQ;
    INT16                               sRemainDcocI;
    INT16                               sRemainDcocQ;
}G_RX_DCR_STRU;

typedef struct
{
    G_RX_DCR_STRU                       astGain0[16];
}NV_G_RX_DCOFFSET_GAIN0_STRU;

typedef struct
{
    NV_G_RX_DCOFFSET_GAIN0_STRU         stGain0Dc;
    G_RX_DCR_STRU                       astOtherGainDc[G_RX_AGC_GAIN_COUNT - 1];
    NV_G_RX_DCOFFSET_GAIN0_STRU         stCrossBandGain0Dc;
    G_RX_DCR_STRU                       astCrossBandOtherGainDc[G_RX_AGC_GAIN_COUNT - 1];
}NV_G_RX_DCOFFSET_STRU;

/*****************************************************************************
 结构名    : ANY_BAND_G_RX_DCOFFSET_IND_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usBand;
    UINT16                              usRsv;

    NV_G_RX_DCOFFSET_STRU               stNvRxDcr;
}ANY_BAND_G_RX_DCOFFSET_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RX_DCR_IND_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usComponentId;                          /* 组件ID */

    UINT16                              usErrCode;                              /* Error code */
    UINT16                              usErrBand;                              /* 存放校准失败的频段 */

    UINT16                              usBandCnt;
    UINT16                              usRsv2;

    /* 接口文档中按照最大长度定义，方便部件直接使用该结构申请内存，
       消息中实际长度为有效帧数 */
    ANY_BAND_G_RX_DCOFFSET_IND_STRU     astBand[5];
}PHY_RF_CAL_G_RX_DCR_IND_STRU;

/*****************************************************************************
 结构名    : NV_G_RX_IQ_MISMATCH_STRU
结构说明  : IQ Mismatch校准结果
*****************************************************************************/
typedef struct
{
    INT16                               sAmp;                                   /* 幅度值 */
    INT16                               sPhase;                                 /* 相位值 */
} NV_G_RX_IQ_MISMATCH_STRU;

/*****************************************************************************
结构名    : RUN_DATA_G_RX_IQ_MISMATCH_STRU
结构说明  : IQ Mismatch校准过程数据
*****************************************************************************/
typedef struct
{
    INT32                               sISquare;                               /* E(|I|^2) */
    INT32                               sQSquare;                               /* E(|Q|^2) */
    INT32                               sIQMultiply;                            /* E(IQ) */
} RUN_DATA_G_RX_IQ_MISMATCH_STRU;

/*****************************************************************************
结构名   : PHY_RF_CAL_G_RX_IQ_MISMATCH_IND_STRU
结构说明  : G Rx IqMismatch校准结果
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* 消息原语 */
    UINT16                              usComponentId;                          /* 组件 ID */

    UINT16                              usErrCode;                              /* 失败码 */
    UINT16                              usRsv2;

    NV_G_RX_IQ_MISMATCH_STRU            stNvRxIqMismatch;                       /* 校准结果 */
    RUN_DATA_G_RX_IQ_MISMATCH_STRU      astRunDataRxIqMismatch[GPHY_RX_IQ_MISMATCH_SLOT_NUM];             /* 中间数据 */
}PHY_RF_CAL_G_RX_IQ_MISMATCH_IND_STRU;

/*****************************************************************************
结构名   : PHY_RF_CAL_G_RX_IQ_MISMATCH_REQ_STRU
结构说明  : G Rx IqMismatch校准命令
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* 消息原语 */
    UINT16                              usRsv1;

    UINT16                              usBandId;
    UINT16                              usRxChannel;

    INT16                               sRefIor10th;                            /* 参考信号强度，单位0.1dBm */
    INT16                               sAmpCorrThreshold;                      /* 校准通过门限*/
    INT16                               sPhsCorrTHreshold;

}PHY_RF_CAL_G_RX_IQ_MISMATCH_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_G_TX_HD3_HD5_REQ_STRU
 结构说明  : G Tx HD3/HD5校准命令
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* 消息原语*/
    UINT16                              usRsv1;

    UINT16                              usBandMask;                             /* Bit0:GSM850; Bit1:GSM900; Bit2:DCS; Bit3:PCS; */
    UINT16                              usRsv2;
}PHY_RF_CAL_G_TX_HD3_HD5_REQ_STRU;


/*****************************************************************************
 结构名    : ANY_PCL_G_TX_HD3_HD5_RUN_DATA_STRU
 结构说明  : 单个功率等级的HD3/HD5的校准过程数据
*****************************************************************************/
typedef struct
{
    INT32                               sHD3Amp;
    INT32                               asHD3Corr[GSM_TX_HD35_STEP_NUM];
    INT32                               sHD5Amp;
    INT32                               asHD5Corr[GSM_TX_HD35_STEP_NUM];

}ANY_PCL_G_TX_HD3_HD5_RUN_DATA_STRU;


/*****************************************************************************
 结构名    : ANY_CHANN_G_TX_HD3_HD5_RUN_DATA_STRU
 结构说明  : 单个频点的HD3/HD5的校准过程数据
*****************************************************************************/
typedef struct
{
    ANY_PCL_G_TX_HD3_HD5_RUN_DATA_STRU  astPclHd3Hd5RunData[GSM_TX_HD35_PCL_NUM];                 /* 分别存放Max_PCL、Max_PCL+1、Max_PCL+2三个功率等级的HD3/HD5校准过程数据 */

}ANY_CHANN_G_TX_HD3_HD5_RUN_DATA_STRU;


/*****************************************************************************
 结构名    : ANY_CHANN_G_TX_HD3_HD5_STRU
 结构说明  : 单个功率等级的HD3/HD5校准结果
*****************************************************************************/
typedef struct
{
    INT16                               sBr;                                    /* HD3校准值实部 */
    INT16                               sBi;                                    /* HD3校准值虚部 */
    INT16                               sCr;                                    /* HD5校准值实部 */
    INT16                               sCi;                                    /* HD5校准值虚部 */

}ANY_PCL_G_TX_HD3_HD5_STRU;


/*****************************************************************************
 结构名    : ANY_CHANN_G_TX_HD3_HD5_STRU
 结构说明  : 单个频点的HD3/HD5校准结果
*****************************************************************************/
typedef struct
{
    ANY_PCL_G_TX_HD3_HD5_STRU           astPclHd3Hd5[GSM_TX_HD35_PCL_NUM];      /* 分别存放Max_PCL、Max_PCL+1、Max_PCL+2三个功率等级的HD3/HD5校准结果 */

}ANY_CHANN_G_TX_HD3_HD5_STRU;


/*****************************************************************************
 结构名    : ANY_BAND_G_TX_HD3_HD5_IND_STRU
 结构说明  : 单个频段的HD3/HD5校准结果和过程数据
*****************************************************************************/
typedef struct
{
    UINT16                                  usBand;                             /* Band信息 */
    UINT16                                  usRsv;
    ANY_CHANN_G_TX_HD3_HD5_STRU             astChannHd3Hd5[GSM_TX_HD35_ARFCN_NUM];                  /* 分别存放低、中、高三个频点的校准结果*/
    ANY_CHANN_G_TX_HD3_HD5_RUN_DATA_STRU    astChannHd3Hd5RunData[GSM_TX_HD35_ARFCN_NUM];           /* 分别存放低、中、高三个频点的校准过程数据 */

}ANY_BAND_G_TX_HD3_HD5_IND_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_TX_HD3_HD5_IND_STRU
 结构说明  : G PHY上报HD3/HD5结果
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* 消息原语 */
    UINT16                              usComponentId;                          /* 组件 ID */

    UINT16                              usErrCode;                              /* 失败码 用于PHY定位问题 */
    UINT16                              usErrBand;                              /* 校准失败的频段 如果多个校准失败默认上报第一个失败的band */

    UINT16                              usBandCnt;                              /* 校准频段的个数 */
    UINT16                              usRsv2;

    ANY_BAND_G_TX_HD3_HD5_IND_STRU      astBandHd3Hd5[GSM_TX_HD35_BAND_NUM];    /* 最大支持G 4个频段 */

}PHY_RF_CAL_G_TX_HD3_HD5_IND_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_GAUGE_REQ_STRU
 协议表格  :
 结构说明  : 用于32K测量任务的启动和停止
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    UINT32                              ulAction;                               /* 1-启动32K测量;0-停止32K测量 */
}WPHY_TOOL_GAUGE_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_GAUGE_CNF_STRU
 协议表格  :
 结构说明  : 用于32K测量任务的启动和停止的原语回复
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    UINT32                              ulAction;                               /* 1-启动32K测量;0-停止32K测量 */
}WPHY_TOOL_GAUGE_CNF_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_GAUGE_IND_STRU
 协议表格  :
 结构说明  : 用于32K测量结果的上报
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usComponentId;                          /* 组件 ID */
    UINT32                              aulData[W_GAUGE_RESULT_SIZE];
}WPHY_TOOL_GAUGE_IND_STRU;

/*****************************************************************************
 结构名    : WR_REG_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT32                              ulRegAdd;
    UINT32                              ulRegValue;
}WR_REG_STRU;

/*****************************************************************************
 结构名    : WPHY_RF_WR_RFIC_REG_REQ_STRU
 协议表格  :
 结构说明  : TOOL通过DSP读写RFIC的寄存器，要求信令/非信令下均有效
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;

    UINT8                               ucWriteReadFlag;                        /* 0:Read，此时需要回复CNF和IND */
    UINT8                               ucChannelNo;                            /* 需要读取RF对应的通道号:0:表示通道0,1:表示通道1 */
    UINT16                              usRegCnt;                               /* 1~1024 */

    /* 接口文档中按照最大长度定义，方便部件直接使用该结构申请内存，
       消息中实际长度为有效帧数 */
    WR_REG_STRU                         astRegData[WG_BBP_RF_REG_WR_MAX_COUNT];
}WPHY_RF_WR_RFIC_REG_REQ_STRU;


/*****************************************************************************
 结构名    : WPHY_RF_WR_RFIC_REG_IND_STRU
 协议表格  :
 结构说明  : TOOL通过DSP读写RFIC的寄存器，要求信令/非信令下均有效
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usComponentId;                          /* 组件 ID */
    UINT16                              usWriteReadFlag;                        /* 0:Read */
    UINT16                              usRegCnt;                               /* 1~1024 */

    /* 接口文档中按照最大长度定义，方便部件直接使用该结构申请内存，
       消息中实际长度为有效帧数 */
    WR_REG_STRU                         astRegData[WG_BBP_RF_REG_WR_MAX_COUNT];
}WPHY_RF_WR_RFIC_REG_IND_STRU;


/*****************************************************************************
 结构名    : WPHY_RF_WR_BBP_REG_REQ_STRU
 协议表格  :
 结构说明  : TOOL通过BBP读写RFIC的寄存器，要求信令/非信令下均有效
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;

    UINT16                              usWriteReadFlag;                        /* 0:Read，此时需要回复CNF和IND
                                                                                   1:Write，此时只需要回复CNF*/
    UINT16                              usRegCnt;                               /* 1~1024 */

    /* 接口文档中按照最大长度定义，方便部件直接使用该结构申请内存，
       消息中实际长度为有效帧数 */
    WR_REG_STRU                         astRegData[WG_BBP_RF_REG_WR_MAX_COUNT];
}WPHY_RF_WR_BBP_REG_REQ_STRU;


/*****************************************************************************
 结构名    : WPHY_RF_WR_RFIC_REG_IND_STRU
 协议表格  :
 结构说明  : TOOL通过DSP读写BBP的寄存器，要求信令/非信令下均有效
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usComponentId;                          /* 组件 ID */

    UINT16                              usWriteReadFlag;                        /* 0:Read */
    UINT16                              usRegCnt;                               /* 1~1024 */

    /* 接口文档中按照最大长度定义，方便部件直接使用该结构申请内存，
       消息中实际长度为有效帧数 */
    WR_REG_STRU                         astRegData[WG_BBP_RF_REG_WR_MAX_COUNT];
}WPHY_RF_WR_RFIC_BBP_IND_STRU;


/*****************************************************************************
 结构名    : GPHY_RF_WR_RFIC_REG_REQ_STRU
 协议表格  :
 结构说明  : TOOL通过DSP读写RFIC的寄存器，要求信令/非信令下均有效
*****************************************************************************/
typedef  WPHY_RF_WR_RFIC_REG_REQ_STRU GPHY_RF_WR_RFIC_REG_REQ_STRU;


/*****************************************************************************
 结构名    : GPHY_RF_WR_RFIC_REG_IND_STRU
 协议表格  :
 结构说明  : TOOL通过DSP读写RFIC的寄存器，要求信令/非信令下均有效
*****************************************************************************/
typedef  WPHY_RF_WR_RFIC_REG_IND_STRU GPHY_RF_WR_RFIC_REG_IND_STRU;


/*****************************************************************************
 结构名    : GPHY_RF_WR_BBP_REG_REQ_STRU
 协议表格  :
 结构说明  : TOOL通过BBP读写RFIC的寄存器，要求信令/非信令下均有效
*****************************************************************************/
typedef WPHY_RF_WR_BBP_REG_REQ_STRU GPHY_RF_WR_BBP_REG_REQ_STRU;

/*****************************************************************************
 结构名    : GPHY_RF_WR_RFIC_REG_IND_STRU
 协议表格  :
 结构说明  : TOOL通过DSP读写BBP的寄存器，要求信令/非信令下均有效
*****************************************************************************/
typedef WPHY_RF_WR_RFIC_BBP_IND_STRU GPHY_RF_WR_RFIC_BBP_IND_STRU;
typedef PHY_RF_CAL_W_RX_RSSI_MEAS_REQ_STRU PHY_RF_CAL_C_RX_RSSI_MEAS_REQ_STRU;
typedef PHY_RF_CAL_W_RF_MSG_CNF_STRU PHY_RF_CAL_C_RF_MSG_CNF_STRU;
typedef PHY_RF_CAL_W_RX_RSSI_MEAS_IND_STRU PHY_RF_CAL_C_RX_RSSI_MEAS_IND_STRU;
typedef PHY_RF_CAL_W_PD_PARA_CFG_REQ_STRU PHY_RF_CAL_C_PD_PARA_CFG_REQ_STRU;
typedef PHY_RF_CAL_W_RF_TX_PD_IND_STRU PHY_RF_CAL_C_RF_TX_PD_IND_STRU;
typedef W_TX_PD_PARA_CFG_STRU  C_TX_PD_PARA_CFG_STRU;
typedef PHY_RF_CAL_W_TX_REG_CTRL_STRU CSDR_CAL_RF_TX_REG_CTRL_STRU;
typedef W_TX_RFIC_PA_MODE_STRU   CSDR_TX_RFIC_PA_MODE_STRU;
/* DCR调试 */
//typedef PHY_RF_CAL_W_SELF_CAL_IND_STRU  PHY_RF_CAL_C_SELF_CAL_IND_STRU;
typedef NV_W_RX_DCOFFSET_STRU PHY_RF_CAL_C_RX_DCOFFSET_STRU;
typedef ANY_BAND_WG_SELF_CAL_IND_STRU ANY_BAND_C_SELF_CAL_IND_STRU;
typedef PHY_RF_CAL_W_SELF_CAL_REQ_STRU PHY_RF_CAL_C_SELF_CAL_REQ_STRU;

typedef W_RX_IMD2_STRU            CSDR_RX_IMD2_STRU;                           /*存放IMD2值*/

/* RFIC和BBP读写 */
typedef WPHY_RF_WR_RFIC_REG_REQ_STRU PHY_RF_CAL_C_WR_RFIC_REG_REQ_STRU;
typedef WPHY_RF_WR_BBP_REG_REQ_STRU  PHY_RF_CAL_C_WR_BBP_REG_REQ_STRU;
typedef WPHY_RF_WR_RFIC_REG_IND_STRU PHY_RF_CAL_C_WR_RFIC_REG_IND_STRU;
typedef WPHY_RF_WR_RFIC_BBP_IND_STRU  PHY_RF_CAL_C_WR_BBP_REG_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_C_TRX_PARA_CFG_REQ_STRU
 协议表格  :
 结构说明  : C模慢速校准消息接口参数
*****************************************************************************/
typedef struct
{
    UINT16                              usMsgID;
    UINT16                              usRsv1;
    UINT32                              ulMask;                                 /* 复用W慢速校准接口定义*/

    /* Afc Para Cfg */
    PHY_RF_CAL_AFC_PARA_STRU            stAfcPara;                              /* AFC控制字*/

    /* Tx Para Cfg */
    UINT16                              usTxBand;
    UINT16                              usRsv2;
    UINT32                              ulTxFreq;                               /* Freq, KHZ单位*/
    UINT16                              usTxEnable;                             /* 低Bit定义---Tx发射0:不使能,1:使能
                                                                                   高Bit定义---调制方式0:正常调制,1:CW单音信号*/
    W_TX_RFIC_PA_MODE_STRU              stTxRficPaMode;
    W_TX_POWER_CTRL_MODE_ENUM_UINT16    usTxPowerCtrlMode;                      /* 复用W慢速校准接口定义*/
    UINT16                              usRsv3;
    PHY_RF_CAL_W_TX_POWER_PARA_UNION    unTxPowerPara;                          /* 复用W慢速校准接口定义*/

    /* Pa Volt Para Cfg */
    W_TX_PA_PARA_CFG_STRU               stPaParaCfg;
    UINT16                              usSelfCal;

    /* Rx Para Cfg */
    UINT16                              usRxBand;
    UINT16                              usRsv4;
    UINT32                              ulRxFreq;                               /* Freq, KHZ单位*/

    UINT16                              usRxEnable;                             /* 复用W慢速校准接口定义*/
    UINT16                              usRxAntSel;                             /* 复用W慢速校准接口定义*/

    W_RX_AGC_GAIN_CFG_STRU              stRxAgcGain;                            /* 复用W慢速校准接口定义*/
    UINT16                              usRsv5;

    INT16                               sIp2IValue;                             /* IP2 I通道码字*/
    INT16                               sIp2QValue;                             /* IP2 Q通道码字*/

}PHY_RF_CAL_C_TRX_PARA_CFG_REQ_STRU;

/*****************************************************************************
 结构名    : C_TRX_FAST_FRAME_STRU
 协议表格  :
 结构说明  : C模快速校准消息接口FRAME参数
*****************************************************************************/
typedef struct
{
    UINT16                              usBand;                                 /*频段只是用于确定使用哪一套Bc的Nv项,校准频率以下面配置的Freq为准*/
    UINT16                              usStepCnt;                              /* [1, 16] */
    UINT32                              ulTxFreq;                               /*单板上行Freq, KHz单位*/
    UINT32                              ulRxFreq;                               /*单板下行Freq, KHz单位*/
    UINT16                              usTxStepPattern;                        /*复用W快速校准接口定义*/
    UINT16                              usRxStepPattern;                        /*复用W快速校准接口定义*/
    ANY_STEP_PARA_STRU                  astStepData[W_TRX_MAX_STEP_COUNT];      /*复用W快速校准接口定义*/
}C_TRX_FAST_FRAME_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_C_TRX_FAST_CAL_REQ_STRU
 协议表格  :
 结构说明  : C模快速校准消息接口参数
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;
    UINT16                              usRsv;

    UINT16                              usTxMask;                               /*复用W快速校准接口定义*/
    W_TX_POWER_CTRL_MODE_ENUM_UINT16    usTxPowerCtrlMode;                      /*复用W快速校准接口定义*/
    C_FAST_STEP_WIDTH_ENUM_UINT16       usStepWidthMs;                          /*和装备约定仅支持2、4、8个pcg，
                                                                                  对应的stepwidth是2500,5000,10000*/
    UINT16                              usRsv2;

    UINT16                              usTxFrameCnt;                           /*复用W快速校准接口定义*/
    UINT16                              usRxFrameCnt;                           /*复用W快速校准接口定义*/

    C_TRX_FAST_FRAME_STRU               astSweepFrame[W_TRX_MAX_SWEEP_FRAME_COUNT];
}PHY_RF_CAL_C_TRX_FAST_CAL_REQ_STRU;


/* 接收端的处理，另封装一个消息 */
typedef  struct CSDR_CAL_RECV_MSG_STRU_tag
{
    VOS_MSG_HEADER
    PHY_UINT32                         *puwMsgBody;
}CSDR_CAL_RECV_MSG_STRU;


/*****************************************************************************
 结构名    : MPH_SWITCH_M1XO_IND_STRU
 协议表格  :
 结构说明  : 在非信令BT时，发送消息通知GPHY切换UE模式。用于全网通特性。
             0:modem1工作在tcxo1 1:modem1工作在tcxo0。
             消息需要在LOAD PHY之后配置。
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 模拟协议栈的消息，添加VOS头 */
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* 原语类型 */
    UINT16                              usToolId;                                  /* 保留位 */
    UINT16                              usUeMode;                               /* 0:modem1工作在tcxo1 1:modem1工作在tcxo0 */
    UINT16                              usResvered;
}MPH_SWITCH_M1XO_IND_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_SWITCH_MOANT_IND_STRU
 协议表格  :
 结构说明  : 在非信令BT时，发送消息通知WPHY切换UE模式。用于全网通特性。
             0:w各频段工作在主天线 1:W B8工作在副天线.
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 模拟协议栈的消息，添加VOS头 */
    PHY_TOOL_MSG_ID_ENUM_UINT16         usMsgID;                                /* 原语类型 */
    UINT16                              usToolId;                               /* 保留位 */
    UINT16                              usUeMode;                               /* 0:w各频段工作在主天线 1:W B8工作在副天线 */
    UINT16                              usResvered;
}RRC_PHY_SWITCH_MOANT_IND_STRU;



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of PhyRfCalInterface.h */

