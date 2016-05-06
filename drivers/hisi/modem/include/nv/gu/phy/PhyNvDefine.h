/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : PhyNvDefine.h
  Description     : PhyNvDefine.h header file
  History         :

******************************************************************************/
#ifndef __PHYNVDEFINE_H__
#define __PHYNVDEFINE_H__


#ifndef MS_VC6_PLATFORM
#ifndef TENSILICA_PLATFORM
#include "vos.h"
#endif
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(1)


/*****************************************************************************
  2 宏定义
*****************************************************************************/


#define UCOM_NV_EDGE_TX_TEMP_COMP_NUM           ( 16 )
#define UCOM_NV_EDGE_TX_RF_GAIN_CTRL_NUM        ( 20 )
#define UCOM_NV_INTERFERENCE_TABLE_MAX_NUM      ( 8 )                           /* 干扰规则表最大个数*/
#define UCOM_NV_INTERFERENCE_BUSINESS_TYPE_NUM  ( 3 )                           /* 干扰业务类型个数*/


#define UCOM_NV_G_RAMP_PWR_LEVEL_NUM        ( 7 )                               /* 依次以10dBm,20dBm划分为3个爬坡功率区间 */
#define UCOM_NV_G_TX_REF_CHAN_NUM_MAX       ( 32 )                              /* TX频率补偿校准频点最大个数 */


#define UCOM_NV_G_TX_8PSK_PWR_CONT_NUM      ( 30 )                              /* (自研)8PSK需要校正的发射功率点为30个 */
#define UCOM_NV_G_TX_PWR_CONT_NUM           ( 60 )                              /* 需要校正的发射功率点为60个 */


#define UCOM_NV_G_TEMP_LEVEL_NUM            ( 16 )                              /* [温度档位,共5档:-20~0,0~20,20~40,40~60,60~85] */
#define UCOM_NV_G_AGC_LEVEL_MAX_NUM         ( 8 )
#define UCOM_NV_G_GAIN_THRESHOLD_MAX_NUM    ( UCOM_NV_G_AGC_LEVEL_MAX_NUM - 1 )  /* UCOM_NV_G_AGC_LEVEL_MAX_NUM - 1 */
#define UCOM_G_RX_OTHER_GAIN_DCR_CHAN_NUM   ( UCOM_NV_G_AGC_LEVEL_MAX_NUM - 1 ) /* 本频其它档位DCR校准结果 */


#define UCOM_NV_G_CHAN_GAIN_MAX_NUM         ( 8 )                               /* 接收增益档数，与AGC档位呈对应关系 */

#define UCOM_NV_G_TX_POWER_LEVEL_NUM        ( 3 )                               /* 将发射功率划分为3个等级 */
#define UCOM_NV_G_TX_CHAN_COMP_NUM          ( 32 )                              /* 8PSK TX频率补偿参考补偿点个数 */
#define UCOM_NV_G_PCL_NUM                   ( 32 )                              /* 功率等级个数 */
#define UCOM_NV_G_TX_SLOT_MAX_NUM           ( 4 )                               /* 功率等级个数 */

#define UCOM_NV_G_TX_ATTEN_NUM              ( 55 )                              /* 8PSK 衰减个数 */

#define UCOM_NV_G_RX_CHAN_COMP_NUM          ( 16 )                              /* 低频段参考补偿点个数 */
#define UCOM_NV_G_HIGH_BAND_CHAN_COMP_NUM   ( 16 )                              /* 高频段参考补偿点个数 */

#define UCOM_NV_G_RX_GSM850_GAIN0_DCR_NUM   ( 42 )
#define UCOM_NV_G_RX_GSM900_GAIN0_DCR_NUM   ( 65 )
#define UCOM_NV_G_RX_DCS1800_GAIN0_DCR_NUM  ( 125 )
#define UCOM_NV_G_RX_PCS1900_GAIN0_DCR_NUM  ( 100 )
#define UCOM_G_RX_GAIN0_DCR_MAX_NUM         ( 125 )

#if ( FEATURE_ON == FEATURE_VIRTUAL_BAND )
#define UCOM_NV_G_BAND_NUM                  ( 5 )                               /* GSM Narrow Dcs共五个频段 */
#else
#define UCOM_NV_G_BAND_NUM                  ( 4 )                               /* GSM共四个频段 */
#endif
#define UCOM_NV_G_BAND_NUMBER               ( 4 )                               /* GSM共四个频段 */
#define UCOM_NV_G_HIGH_BAND_NUM             ( 2 )                               /* 高频段包括1800/1900两个频段 */
#define UCOM_NV_G_LOW_BAND_NUM              ( 2 )                               /* 低频段包括850/900两个频段 */
#define UCOM_NV_G_HIGH_BAND_INDEX           ( 0 )                               /* 高频段包括1800/1900两个频段 */
#define UCOM_NV_G_LOW_BAND_INDEX            ( 1 )                               /* 低频段包括850/900两个频段 */
#define UCOM_NV_G_HIGH_LOW_BUTT             ( 2 )                               /* G模区分高低BAND */
#define UCOM_NV_G_SUBBAND_NUM               ( 3 )                               /* 每频段内子频段个数 */
#define UCOM_NV_G_RAMP_COEF_NUM             ( 16 )                              /* 爬坡点数 */
#define UCOM_NV_G_LNA_GPIO_STEP_NUM         ( 4 )                              /* LNA GPIO的配置最大档位数 */
#define UCOM_NV_G_LNA_MIPI_STEP_NUM         ( 4 )                              /* LNA MIPI的配置最大档位数 */
#define UCOM_NV_G_LNA_GAIN_INDEX_NUM        ( 8 )                              /* LNA MIPI的配置最大档位数 */
#define UCOM_NV_G_LNA_MIPI_CMD_MAX_NUM      ( 4 )                              /* LNA MIPI指令控制字命令最大数目 */
#define UCOM_NV_G_LNA_MIPI_DATA_MAX_NUM     ( 4 )                              /* LNA MIPI指令控制字命令最大数目 */


#define UCOM_NV_W_BAND_SECTION_NUM                  ( 3 )                       /* W BAND SECTION */
#define UCOM_NV_WCDMA_PA_EN_LINE_NUM        ( 4 )                               /* w pa 4 line */

/* 最大HSUPA ETFCI 表格个数 */
#define UCOM_NV_HSUPA_ETFCI_TABLE_MAX_NUM   ( 6 )

#define UCOM_NV_W_TX_TEMP_COMP_NUM                  ( 16 )                      /* 每个RF Gain档位的温度补偿数目 */

#define UCOM_NV_W_TX_RF_GAIN_CTRL_NUM               ( 20 )                      /* RF增益档位理论数目 */

#define UCOM_W_MAX_RF_GAIN_CTRL_NUM             ( 20 )                          /* rf gain ctrl最大档位数 */

#define UCOM_W_MAX_RF_BIAS_NUM                  ( 16 )                          /* rf BIAS最大档位数 */
#define UCOM_W_MAX_RF_BB_GAIN_NUM               ( 32 )                          /* rf BB GAIN最大档位数 */

#define UCOM_NV_MAX_RF_VCO_CONFIG_NUM               ( 4 )                       /* RF VCO CONFIG */
#define UCOM_NV_W_TX_RF_BIAS_NUM                    ( 0x4 )                     /* RF TX BIAS */
#define UCOM_NV_W_TX_DPA_IQ_REDUCTION_NUM           ( 15 )                      /* DPA业务数字回退 */
#define UCOM_NV_W_TX_SCUPA_IQ_REDUCTION_NUM         ( 26 )                      /* SC-UPA业务数字回退 */
#define UCOM_NV_W_TX_DPA_MPR_NUM                    ( 15 )                      /* DPA业务的功率回退 */
#define UCOM_NV_W_ANT_NUM                           ( 2 )                       /* 2天线 */
#define UCOM_NV_W_TX_SCUPA_MPR_NUM                  ( 26 )                      /* SC-UPA业务的功率回退 */
#define UCOM_NV_W_TX_DCUPA_MPR_NUM                  ( 7 )                       /* SC-UPA业务的功率回退 */
#define UCOM_NV_SAR_BACKOFF_NUM                     ( 6 )                       /* 降SAR共分6个等级， */
#define UCOM_NV_SAR_MODEM_SCENE_NUM                 ( 3 )                       /* modem sar的场景数(分为对端modem不发射场景，对端modem低频发射发射场景，
                                                                                   对端modem高频发射发射场景 ) */
#define UCOM_NV_W_SAR_SPECIAL_SCENE_NUM             ( 4 )                       /* WPHY支持4个特殊场景的配置 */
#define UCOM_NV_W_PA_GAIN_SWITCH_COMP_BOUNDARY_NUM  ( 5 )                       /* W TX PA增益切换点补偿,每个BAND区分5个区间 */
#define UCOM_NV_APT_TABLE_MAX_LEN           ( 96 )                              /* APT表的最大个数 */
#define UCOM_NV_APT_STEP_0_8_NUM            ( 32 )                              /* 0.8db步进每个档位下APT最大个数 */
#define UCOM_NV_APT_STEP_0_4_NUM            ( 48 )                              /* 0.4db步进每个档位下APT最大个数 */
#define UCOM_NV_APT_MAX_NUM                 ( UCOM_NV_APT_STEP_0_4_NUM )        /* 每个档位下APT补偿的最大个数 */
#define UCOM_NV_W_PA_NONLINEAR_NUM          ( UCOM_NV_APT_TABLE_MAX_LEN )       /* PA非线性补偿 */

#define UCOM_NV_PA_GAIN_MAX_NUM             ( 3 )                               /* PA档位个数 */
#define UCOM_WCDMA_UARFCN_NUM               ( 0x10 )                            /* 每个频段下UARFCN个数 */
#define UCOM_NV_W_TX_PA_MODE_NUM            ( 3 )                               /* PA 增益个数:高中低 */
#define UCOM_NV_W_TEMP_NUM                  ( 0x10  )                           /* 温度补偿设置的温度点，前5个分别代表 -20,0,20,40,60，第6个用于字节对齐 */
#define UCOM_NV_W_TX_PA_TEMP_NUM            ( 0x10 )                            /* TX PA的温度补偿设置的温度点，由工具下发，共16个 */
#define UCOM_NV_W_TX_FREQ_COMP_NUM          ( 0x10 )                            /* TX PA的温度补偿设置的温度点，由工具下发，共16个 */


#define UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM             ( 0x8 )
#define UCOM_NV_W_AGC_GAIN_NOBLK_THRESHOLD_NUM        ( UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM -1 )  /* 6361中AGC GAIN档位切换门限的个数
                                                         该值依赖于档位=(UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM - 1) */

#define UCOM_NV_W_AGC_GAIN_BLK_STEP_NUM               ( 0x8 )                                           /* NV项中block档位个数 */
#define UCOM_NV_W_AGC_GAIN_BLK_THRESHOLD_NUM          ( UCOM_NV_W_AGC_GAIN_BLK_STEP_NUM - 1 )    /* 6361中AGC GAIN档位切换门限的个数
                                                                  UCOM_NV_W_AGC_GAIN_BLK_STEP_NUM - 1 */

#define UCOM_NV_W_LNA_MIPI_CMD_MAX_NUM              ( 0x4 )                     /* LNA MIPI指令控制字命令最大数目 */
#define UCOM_NV_W_LNA_MIPI_DATA_MAX_NUM             ( 0x4 )                     /* LNA MIPI数据控制字命令最大数目 */
#define UCOM_NV_W_LNA_GPIO_STEP_NUM                 ( 0x4 )                     /* LNA GPIO配置档位 */
#define UCOM_NV_W_LNA_MIPI_STEP_NUM                 ( 0x4 )                     /* LNA MIPI配置档位 */

#define UCOM_NV_W_TX_HDET_DPA_CM_COMP_NUM           ( 15 )                      /* DPA业务PD的CM补偿 */
#define UCOM_NV_W_TX_HDET_SCUPA_CM_COMP_NUM         ( 26 )                      /* SC-UPA业务PD的CM补偿 */

#define UCOM_NV_W_APT_FREQ_COMP_NUM                 ( 16 )
#define UCOM_NV_W_APT_TEMP_COMP_NUM                 ( 16 )

#define UCOM_NV_W_CHANNEL_NUM               ( 3 )                               /* NV项每个BAND区分高中低三个信道 */
#define UCOM_NV_W_PA_SWITCH_COMP_SLOT       ( 4 )                               /* Pa切换补偿时隙数 */
#define UCOM_NV_W_APC_ATTEN_NUM             ( 0x58 )
#define UCOM_NV_W_TX_HDET_PV_NUM            ( 0x10 )                            /* PA的工作电压个数 */
#define UCOM_NV_W_PA_GAIN_SWITCH_COMP_CHAN_NUM      ( 4 )                       /* W TX PA增益切换点补偿的4个分界频点 */
#define UCOM_NV_W_TX_APT_SCUPA_CM_COMP_NUM          ( 26 )                      /* SC-UPA业务APT的CM补偿 */

#define UCOM_NV_W_TX_APT_DPA_CM_COMP_NUM            ( 15 )                     /* DPA业务APT的CM补偿 */
#define UCOM_NV_W_TX_PA_VBIAS_NUM           ( 3 )                               /* pa vbias个数 */


#define UCOM_NV_W_TOTAL_BAND_NUM            ( 0x06 )
#define UCOM_NV_W_RF_BAND_CONFIG_NUM            ( 10 )                          /* ext band config支持的W频段 */

#define UCOM_NV_RFABB_INIT_REG_NUM              ( 60 )                          /* 6361初始化寄存器定义了60个 */
#define UCOM_NV_RFABB_INIT_REG_NEW_RAM_NUM      ( 256 )                         /* 6362初始化寄存器定义了256个 */

/* AP+Sensor手持状态个数,目前支持5种状态 */
#define UCOM_NV_TUNER_HANDLE_STATUS_NUM         ( 5 )

/* active时，w tuner支持的最大MIPI个数 */
#define UCOM_NV_W_TUNER_MIPI_CMD_MAX_NUM        ( 7 )
#define UCOM_NV_W_TUNER_MIPI_DATA_MAX_NUM       ( 8 )

/* G tuner支持的最大MIPI个数 */
#define UCOM_NV_GSM_TUNER_MIPI_CMD_MAX_NUM      ( 5 )
#define UCOM_NV_GSM_TUNER_MIPI_DATA_MAX_NUM     ( 6 )

/* WG PA支持的最大MIPI个数 */
#define UCOM_NV_PA_MIPI_CMD_MAX_NUM             ( 5 )
#define UCOM_NV_PA_MIPI_DATA_MAX_NUM            ( 6 )

/* ET支持的最大MIPI个数 */
#define UCOM_NV_ET_MIPI_CMD_MAX_NUM             ( 7 )
#define UCOM_NV_ET_MIPI_DATA_MAX_NUM            ( 8 )


#define UCOM_NV_MAX_MIPI_ANT_CMD_NUMBER         ( 4 )                           /* ant switch控制字命令最大数目 */
#define UCOM_NV_MAX_MIPI_ANT_DATA_NUMBER        ( 5 )                           /* ant switch数据字命令最大数目 */

#define UCOM_NV_MIPI_NOTCH_CMD_NUMBER           ( 3 )                           /* notch控制字命令最大数目 */
#define UCOM_NV_MIPI_NOTCH_DATA_NUMBER          ( 4 )                           /* notch数据字最大数目 */

#define UCOM_NV_W_MIPI_PA_TRIGGER_NUM           ( 2 )

#define UCOM_G_RX_GAIN0_DCR_CHAN_NUM            ( 16 )                          /*DCR channel NUM */
/* DCXO多项式系数的个数 */
#define UCOM_DCXO_POLY_COEFF_NUM            ( 4 )

#define UCOM_NV_XO_TEMP_COMP_NUM            ( 32 )
#define UCOM_NV_BATT_TEMP_SENSOR_NUM        ( 8 )
/* 存放 144组温度-频率样本点:存数时按照 FIFO原则 */
#define UCOM_DCXO_TEMP_AFC_MAX_NUM          ( 144 )
#define UCOM_NV_PA_TEMP_SENSOR_NUM          ( 32 )

#define UCOM_NV_GSM_LINEAR_PA_GAIN_NUM                ( 4 )                       /* GSM 线性PA增益个数 */

#define UCOM_NV_GSM_LINEAR_PA_SWITCH_THRESHOLD_NUM    ( UCOM_NV_GSM_LINEAR_PA_GAIN_NUM - 1 )  /* GSM 线性PA增益个数 */

#define UCOM_NV_DCXO_SEARCH_AFC_OFFSET_SAMPLE_NUM       ( 5 )                   /* 三次搜网AFC偏置计算曲线样本个数 */

#define UCOM_NV_RCM_TAS_TABLE_NUM                      ( 20 )                   /* TAS计分表的状态个数，新旧计分表都扩展为20 */


#define UCOM_NV_GSM_TX_HD35_ARFCN_NUM                 ( 3 )                     /* 每个频段三个校准频点 */
#define UCOM_NV_GSM_TX_HD35_PCL_NUM                   ( 3 )                     /* 每个频点三个校准PCL点 */
#define UCOM_NV_CDMA_RF_BB_GAIN_NUM                   ( 32 )                    /* RF BB档位为32档 */
#define UCOM_NV_CDMA_ANT_NUM                          ( 2 )                     /* 2天线 */
#define UCOM_NV_CDMA_CHANNEL_NUM                      ( 3 )                     /* NV项每个BAND区分高中低三个信道 */
#define UCOM_NV_CDMA_UARFCN_NUM                       ( 0x10 )                  /* 每个频段下UARFCN个数 */

#define UCOM_NV_CDMA_AGC_GAIN_NOBLK_STEP_NUM          ( UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM )                            /* NV项中noblock档位个数 */
#define UCOM_NV_CDMA_AGC_GAIN_NOBLK_THRESHOLD_NUM     ( UCOM_NV_CDMA_AGC_GAIN_NOBLK_STEP_NUM -1 )  /* 6361中AGC GAIN档位切换门限的个数
                                                                                                      该值依赖于档位=(CSDR_NV_CDMA_AGC_GAIN_NOBLK_STEP_NUM - 1) */
#define UCOM_NV_CDMA_AGC_GAIN_BLK_STEP_NUM            ( UCOM_NV_W_AGC_GAIN_BLK_STEP_NUM )                                      /* NV项中block档位个数 */
#define UCOM_NV_CDMA_AGC_GAIN_BLK_THRESHOLD_NUM       ( UCOM_NV_CDMA_AGC_GAIN_BLK_STEP_NUM - 1 )   /* 6361中AGC GAIN档位切换门限的个数 */
#define UCOM_NV_CDMA_TX_PA_MODE_NUM                   ( 3 )                     /* 高中低档位 */
#define UCOM_NV_CDMA_TOTAL_BAND_NUM                   ( 0x06 )

#define UCOM_NV_CDMA_APC_ATTEN_NUM                    ( UCOM_NV_W_APC_ATTEN_NUM )
#define UCOM_NV_CDMA_BAND_SECTION_NUM                 ( UCOM_NV_W_BAND_SECTION_NUM ) /* W BAND SECTION */
#define UCOM_NV_CDMA_TX_HDET_PV_NUM                   ( UCOM_NV_W_TX_HDET_PV_NUM )
#define UCOM_NV_CDMA_TX_PA_TEMP_NUM                   ( UCOM_NV_W_TX_PA_TEMP_NUM )   /* TX PA的温度补偿设置的温度点，由工具下发，共16个 */
#define UCOM_NV_CDMA_TX_FREQ_COMP_NUM                 ( UCOM_NV_W_TX_FREQ_COMP_NUM ) /* TX PA的温度补偿设置的温度点，由工具下发，共16个 */
#define UCOM_NV_CDMA_TX_RF_GAIN_CTRL_NUM              ( UCOM_NV_W_TX_RF_GAIN_CTRL_NUM )
#define UCOM_NV_CDMA_TX_TEMP_COMP_NUM                 ( UCOM_NV_W_TX_TEMP_COMP_NUM )
#define UCOM_NV_CDMA_TEMP_NUM                         ( UCOM_NV_W_TEMP_NUM )

#define UCOM_NV_TRI_MODE_CHAN_PARA_PROFILE_NUM        ( 8 )                     /* 包含全网通性特的通道配置场景数目 */

#define UCOM_NV_FEM_IO_CFG_MAX                        ( 16 )                    /* 18002 nv中最多支持的配置个数 */

/* BBP接口提供8张DPD表，切换门限为9个，每张表深度为64 */
#define UCOM_NV_BBP_DPD_LUT_MAX_NUM                 ( 8 )
#define UCOM_NV_DPD_LUT_THERSHOLD_MAX_NUM           ( UCOM_NV_BBP_DPD_LUT_MAX_NUM + 1 )
#define UCOM_NV_DPD_LUT_MAX_LEN                     ( 64 )

/* NV项中定义成9张表是表示成3*3，即可能区分高中低信道，每个信道3张表 */
#define UCOM_NV_DPD_LUT_MAX_NUM                     ( 9 )
#define UCOM_NV_ET_LUT_MAX_LEN                      ( 256 )

#define UCOM_NV_W_DPD_FREQ_COMP_NUM                 ( UCOM_NV_W_APT_FREQ_COMP_NUM )
#define UCOM_NV_W_DPD_TEMP_COMP_NUM                 ( UCOM_NV_W_APT_TEMP_COMP_NUM )

#define UCOM_NV_ET_DELAY_FREQ_COMP_MAX_NUM          ( 8 )                       /* ET DELAY 频补最大值 */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
 枚举名    :UCOM_NV_DC_SC_MODE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :载波模式
*****************************************************************************/
enum UCOM_NV_DC_SC_MODE_ENUM
{
    UCOM_NV_SC_MODE                     = 0,                                    /* 单载波模式 */
    UCOM_NV_DC_MODE                     = 1,                                    /* 双载波模式 */
    UCOM_NV_DC_SC_MODE_BUTT             = 2
};
typedef VOS_UINT16 UCOM_NV_DC_SC_MODE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : UCOM_NV_CHAN_CONNECT_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : A/B通道的标识
*****************************************************************************/
enum UCOM_NV_CHAN_CONNECT_ENUM
{
    UCOM_NV_CHAN_CONNECT_A                  = 0,                                /* A通道 */
    UCOM_NV_CHAN_CONNECT_B                  = 1,                                   /* B通道 */
    UCOM_NV_CHAN_CONNECT_BUTT               = 2
};
typedef VOS_UINT16 UCOM_NV_CHAN_CONNECT_ENUM_UINT16;


/*****************************************************************************
 枚举名    : UCOM_NV_WCDMA_SPUR_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 谐波点类型
*****************************************************************************/
enum UCOM_NV_WCDMA_SPUR_TYPE_ENUM
{
    UCOM_NV_WCDMA_SPUR_1920                  = 0,                               /* 19.20M */
    UCOM_NV_WCDMA_SPUR_1536                  = 1,                                  /* 15.36M */
    UCOM_NV_WCDMA_SPUR_6144                  = 2,                                  /* 61.44M */
    UCOM_NV_WCDMA_SPUR_BUTT                  = 3
};
typedef VOS_UINT16 UCOM_NV_WCDMA_SPUR_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    :UCOM_NV_XO_TYPE_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :晶体类型区分,0表示 DCXO,1表示 TCXO
*****************************************************************************/
enum UCOM_NV_XO_TYPE_ENUM
{
    UCOM_NV_XO_TYPE_DCXO                = 0,                                    /* 表示使用 DCXO */                                                           /* 上行仅存在DPCH */
    UCOM_NV_XO_TYPE_TCXO                = 1,                                    /* 表示使用 TCXO */                                                             /* 上行存在RACH */
    UCOM_NV_XO_TYPE_BUTT                = 2
};
typedef VOS_UINT16 UCOM_NV_XO_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    :UCOM_NV_DCXO_TEMP_CIRCUIT_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :DCXO中有两个温度采集电路，一个用于采集常温和高温，另一个用于采集低温和部分常温
*****************************************************************************/
enum UCOM_NV_DCXO_TEMP_CIRCUIT_ENUM
{
    UCOM_NV_DCXO_TEMP_CIRCUIT_HIGH              = 0,                            /* 高温电路  */
    UCOM_NV_DCXO_TEMP_CIRCUIT_NORMAL            = 0,                            /* 常温和高温电路是一个 */                                                           /* 上行仅存在DPCH */
    UCOM_NV_DCXO_TEMP_CIRCUIT_LOW               = 1,                            /* 低温电路 */                                                             /* 上行存在RACH */
    UCOM_NV_DCXO_TEMP_CIRCUIT_BUTT              = 2
};
typedef VOS_UINT16 UCOM_NV_DCXO_TEMP_CIRCUIT_ENUM_UINT16;

/*****************************************************************************
 枚举名    :UCOM_NV_SINGLE_XO_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :单时钟类型
*****************************************************************************/
enum UCOM_NV_SINGLE_XO_TYPE_ENUM
{
    UCOM_NV_SINGLE_XO_TYPE_UNSUPPORT      = 0,                                    /* 不支持单时钟 */                                                           /* 上行仅存在DPCH */
    UCOM_NV_SINGLE_XO_TYPE_TCXO           = 1,                                    /* 单TCXO */                                                           /* 上行存在RACH */
    UCOM_NV_SINGLE_XO_TYPE_DCXO           = 2,                                    /* 单DCXO */
    UCOM_NV_SINGLE_XO_TYPE_BUTT
};
typedef VOS_UINT16 UCOM_NV_SINGLE_XO_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    :UCOM_NV_POWER_STEP_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :APT表类型区分,0表示 0.8db步进,1表示 0.4db步进
*****************************************************************************/
enum UCOM_NV_APT_STEP_ENUM
{
    UCOM_NV_POWER_STEP_0_POINT_8_DB           = 0,                                /* 表示APT表为0.8db步进 */                                                           /* 上行仅存在DPCH */
    UCOM_NV_POWER_STEP_0_POINT_4_DB           = 1,                                /* 表示APT表为0.4db步进 */                                                             /* 上行存在RACH */
    UCOM_NV_POWER_STEP_BUTT
};
typedef VOS_UINT16 UCOM_NV_POWER_STEP_ENUM_UINT16;

/*****************************************************************************
 枚举名    :UCOM_NV_BBP_HARQ_OUT_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :HARQ外移类型区分,0表示不支持外移, 1表示外移到DDR, 2表示外移到片内内存
*****************************************************************************/
enum UCOM_NV_BBP_HARQ_OUT_TYPE_ENUM
{
    UCOM_NV_BBP_HARQ_OUT_NOT_SUPPORT       = 0,                                /* 不支持HARQ外移 */                                                           /* 上行仅存在DPCH */
    UCOM_NV_BBP_HARQ_OUT_IN_DDR            = 1,                                /* HARQ外移到DDR */                                                             /* 上行存在RACH */
    UCOM_NV_BBP_HARQ_OUT_IN_CHIP           = 2,                                /* HARQ外移到片内内存 */
    UCOM_NV_BBP_HARQ_OUT_BUTT
};
typedef VOS_UINT16 UCOM_NV_BBP_HARQ_OUT_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    :UCOM_NV_RCM_AGENTC_COMPARE_PHASE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :天线比较阶段,分为三个阶段
*****************************************************************************/
enum UCOM_NV_RCM_AGENTC_COMPARE_PHASE_ENUM
{
    UCOM_NV_RCM_AGENTC_COMPARE_PHASE_ONE                     = 0,
    UCOM_NV_RCM_AGENTC_COMPARE_PHASE_TWO                     = 1,
    UCOM_NV_RCM_AGENTC_COMPARE_PHASE_THREE                   = 2,
    UCOM_NV_RCM_AGENTC_COMPARE_PHASE_BUTT                    = 3
};
typedef VOS_UINT16 UCOM_NV_RCM_AGENTC_COMPARE_PHASE_ENUM_UINT16;


/*****************************************************************************
 枚举名    :UCOM_NV_32K_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :32K时钟类型
*****************************************************************************/
enum UCOM_NV_32K_TYPE_ENUM
{
    UCOM_NV_32K_TYPE_32000              = 0,                                    /* 32k时钟个数32000 */                                                           /* 上行仅存在DPCH */
    UCOM_NV_32K_TYPE_32764              = 1,                                    /* 32k时钟个数32764 */                                                           /* 上行存在RACH */
    UCOM_NV_32K_TYPE_32768              = 2,                                    /* 32k时钟个数32768 */
    UCOM_NV_32K_TYPE_BUTT
};
typedef VOS_UINT16 UCOM_NV_32K_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    :UCOM_NV_DRX_CTRL_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :0表示不允许睡眠，1表示允许睡眠
*****************************************************************************/
enum UCOM_NV_DRX_CTRL_ENUM
{
    UCOM_NV_DRX_CTRL_DISABLE                = 0,                                /* 不允许睡眠 */                                                           /* 上行仅存在DPCH */
    UCOM_NV_DRX_CTRL_ENABLE                 = 1,                                /* 允许睡眠 */                                                             /* 上行存在RACH */
    UCOM_NV_DRX_CTRL_BUTT
};
typedef VOS_UINT16 UCOM_NV_DRX_CTRL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : UCOM_NV_RFFE_CTRL_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 前端器件配置接口类型,目前区分使用MIPI或GPIO
*****************************************************************************/
enum UCOM_NV_RFFE_CTRL_ENUM
{
    UCOM_NV_RFFE_CTRL_GPIO              = 0,                                    /* 使用GPIO配置方式 */
    UCOM_NV_RFFE_CTRL_MIPI              = 1,                                    /* 使用MIPI配置方式 */
    UCOM_NV_RFFE_CTRL_GPIO_AND_MIPI     = 2,                                    /* 使用GPIO+MIPI配置方式 */
    UCOM_NV_RFFE_CTRL_BUTT
};
typedef VOS_UINT16 UCOM_NV_RFFE_CTRL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : UCOM_NV_TUNER_SUPPORT_MODE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : tuner支持的形式，0:硬件不支持，1:支持开环，2:支持AP+Sensor,
             3:支持动态调谐
*****************************************************************************/
enum UCOM_NV_TUNER_SUPPORT_MODE_ENUM
{
    UCOM_NV_TUNER_SUPPORT_NONE                  = 0,
    UCOM_NV_TUNER_SUPPORT_OPEN_LOOP             = 1,
    UCOM_NV_TUNER_SUPPORT_AP_SENSOR             = 2,
    UCOM_NV_TUNER_SUPPORT_CLOSED_LOOP           = 3,
    UCOM_NV_TUNER_SUPPORT_BUTT
};
typedef VOS_UINT16 UCOM_NV_TUNER_SUPPORT_MODE_ENUM_UINT16;

/*****************************************************************************
 枚举名    :UCOM_NV_RX_EVM_TEST_EN_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :Rx EVM测试
*****************************************************************************/
enum UCOM_NV_RX_EVM_TEST_EN_ENUM
{
    UCOM_NV_RX_EVM_TEST_DISABLE         = 0,                                    /* 表示正常模式 */                                                           /* 上行仅存在DPCH */
    UCOM_NV_RX_EVM_TEST_ENABLE          = 1,                                    /* 表示Rx EVM测试模式 */                                                             /* 上行存在RACH */
    UCOM_NV_RX_EVM_TEST_BUTT            = 2
};
typedef VOS_UINT16 UCOM_NV_RX_EVM_TEST_EN_ENUM_UINT16;


/*****************************************************************************
 枚举名    :UCOM_NV_FEMIO_CTRL_MODE_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum UCOM_NV_FEMIO_CTRL_MODE_ENUM
{
    UCOM_NV_FEMIO_CTRL_TOP              = 0,                                    /* 无需配置 */                                                          /* 上行仅存在DPCH */
    UCOM_NV_GPIO_ONLY                   = 1,                                    /* 只配置GPIO */                                                           /* 上行存在RACH */
    UCOM_NV_MIPI_ONLY                   = 2,                                    /* 只配置MIPI */
    UCOM_NV_GPIO_MIPI                   = 3,                                    /* 配置GPIO和MIPI */
    UCOM_NV_FEMIO_CTRL_BUTT
};
typedef VOS_UINT32 UCOM_NV_FEMIO_CTRL_MODE_ENUM_UINT32;

/*****************************************************************************
 枚举名    :UCOM_NV_DCXO_TEMP_RISE_METHOD_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum UCOM_NV_DCXO_TEMP_RISE_METHOD_ENUM
{
    UCOM_NV_DCXO_TEMP_RISE_USE_AP       = 1,                                    /* 使用AP升温 */                                                          /* 上行仅存在DPCH */
    UCOM_NV_DCXO_TEMP_RISE_USE_PA       = 2,                                    /* 使用PA升温 */                                                           /* 上行存在RACH */
    UCOM_NV_DCXO_TEMP_RISE_USE_APANDPA  = 3,                                    /* 使用AP和PA升温 */
    UCOM_NV_DCXO_TEMP_RISE_BUTT
};
typedef VOS_UINT16 UCOM_NV_DCXO_TEMP_RISE_METHOD_ENUM_UINT16;
/*****************************************************************************
 枚举名    :UCOM_NV_INTERFERENCE_BUSINESS_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :干扰判决业务类型
*****************************************************************************/
enum UCOM_NV_INTERFERENCE_BUSINESS_TYPE_ENUM
{
    UCOM_NV_INTERFE_BUSINESS_TYPE_IDLE     =0 ,                            /* Idle状态 */
    UCOM_NV_INTERFE_BUSINESS_TYPE_PS          ,                            /* PS业务状态 */
    UCOM_NV_INTERFE_BUSINESS_TYPE_CS          ,                            /* CS业务状态 */
    UCOM_NV_INTERFE_BUSINESS_TYPE_BUTT

};
typedef VOS_UINT16 UCOM_NV_INTERFERENCE_BUSINESS_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    :UCOM_NV_INTERFE_ACTION_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :干扰判决动作
*****************************************************************************/
enum UCOM_NV_INTERFE_ACTION_ENUM
{
    UCOM_NV_INTERFE_ACTION_NONE                        =   0,                   /* 无效值 */
    UCOM_NV_INTERFE_ACTION_CURRENT_RX_BLANKING         =   1,                   /* 当前模的rxblanking */
    UCOM_NV_INTERFE_ACTION_CURRENT_TX_BLANKING         =   2,                   /* 当前模的txblanking */
    UCOM_NV_INTERFE_ACTION_OPPOSITE_RX_BLANKING        =   3,                   /* 对方模的rxblanking */
    UCOM_NV_INTERFE_ACTION_OPPOSITE_TX_BLANKING        =   4,                   /* 对方模的txblanking */
    UCOM_NV_INTERFE_ACTION_CURRENT_G_AVOID_L           =   5,                   /* G当前模 RXBLANKING 避让LTE寻呼 */
    UCOM_NV_INTERFE_ACTION_OPPOSITE_G_AVOID_L          =   6,                   /* G对方模 RXBLANKING 避让LTE寻呼 */
    UCOM_NV_INTERFE_ACTION_BUTT
};
typedef VOS_UINT16 UCOM_NV_INTERFE_ACTION_ENUM_UINT16;

/*****************************************************************************
 枚举名    :UCOM_NV_INTERFE_FEATURE_SWITCH_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :特性开关
*****************************************************************************/
enum UCOM_NV_FEATURE_SWITCH_ENUM
{
    UCOM_NV_INTERFE_FEATURE_SWITCH_CLOSE                    =  0,               /* 特性开关关闭 */
    UCOM_NV_INTERFE_INTERFERENCE_OPEN                           ,               /* 干扰特性开关打开 */
    UCOM_NV_INTERFE_MAX_POWER_BACKOFF_OPEN                      ,               /* 最大功率回退特性开关打开 */
    UCOM_NV_INTERFE_INTERFERENCE_MAX_POWER_BACKOFF_OPEN         ,               /* 干扰和最大功率回退特性开关都打开 */
    UCOM_NV_INTERFE_FEATURE_SWITCH_BUTT
};
typedef VOS_UINT16 UCOM_NV_INTERFE_FEATURE_SWITCH_ENUM_UINT16;

/*****************************************************************************
  6 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           参数设置消息结构                                 *
*                                                                            *
******************************************************************************/
/* xiongjiangjiang Begine */
/*****************************************************************************
 结构名    : UCOM_NV_NV_ITEM_XO_DEFINE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UCOM_NV_XO_TYPE_ENUM_UINT16             enXoDefine;
}UCOM_NV_NV_ITEM_XO_DEFINE_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_MIPI_CMD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MIPI 指令控制段定义，奇偶校验由软件完成
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  uhwSlaveAddr    :4;                             /* Mipi Slave地址，有效值0-15 */
    VOS_UINT16                  uhwRegAddr      :9;                             /* 寄存器地址 OR 起始地址 */
    VOS_UINT16                  uhwByteCnt      :3;                             /* 需要写入的byte(连续)个数 */
}UCOM_NV_MIPI_CMD_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_MIPI_BYTE_DATA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MIPI 指令数据段定义，奇偶校验由软件完成
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  uhwByteData     :8;                             /* 指令数据段定义，奇偶校验由软件完成 */
    VOS_UINT16                  uhwMasterSel    :3;                             /* Mipi Master指示 */
    VOS_UINT16                  uhwReserved     :5;                             /* 保留 */
}UCOM_NV_MIPI_BYTE_DATA_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_MIPI_COMM_STRU
 协议表格  :
 结构说明  : 用于一些mipi功能公共指令定义
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU                   astMipiCmd[5];
    UCOM_NV_MIPI_BYTE_DATA_STRU             astMipiData[6];
}UCOM_NV_MIPI_COMM_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_WG_MIPI_INIT_WORD_STRU
 结构说明  : 用于主模初始化或唤醒,初始化mipi器件的接口
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU                   astMipiCmd[15];
    UCOM_NV_MIPI_BYTE_DATA_STRU             astMipiData[16];
}UCOM_NV_WG_MIPI_INIT_WORD_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_PHY_AUTO_INIT_FLAG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PHY是否上电自动初始化
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwPhyAutoInitFlag;
}UCOM_NV_PHY_AUTO_INIT_FLAG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_NV_ITEM_XO_DEFINE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 单时钟类型定义
*****************************************************************************/
typedef struct
{
    UCOM_NV_SINGLE_XO_TYPE_ENUM_UINT16      enSingleXoType;                     /* 单时钟是否使能,0:不支持，1:单tcxo，2:单dcxo */
    UCOM_NV_32K_TYPE_ENUM_UINT16            en32kType;                          /* 0:32000,1:32764，2:32768*/

}UCOM_NV_SINGLE_XO_DEFINE_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_AFC_K_VALUE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 单时钟K值定义
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwKValue;                          /* 表示BBP AFC每调整单位的hz数，默认为4 */
    VOS_UINT16                              uhwReserve;                         /* 保留 */

}UCOM_NV_W_AFC_K_VALUE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_RFIC_TEMP_COMP_WEIGH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : rf reg12 温度因子NV_RFIC_TEMP_COMP_WEIGTH
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwNvRficTempCompWeigh;
}UCOM_NV_RFIC_TEMP_COMP_WEIGH_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_XO_INIT_FREQUENCY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :2.2表示普通晶体的初始频偏和温度
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwInitFrequency;                       /* 普通晶体的初始频偏 */
    VOS_INT16                           shwInitTemperature;                     /* 普通晶体的初始温度 */
}UCOM_NV_XO_INIT_FREQUENCY_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_DYNAMIC_FREQUENCY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :2.2表示平台上次AFC锁定值
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwDymamicFrequency;                    /* 平台上次AFC锁定值 */
    VOS_INT16                           shwDymamicTemperature;                  /* 平台上次AFC的温度 */
}UCOM_NV_DYNAMIC_FREQUENCY_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_WG_TX_TEMP_DEFINE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :7.3 3G和2G上行发射功率相对温度变化范围
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwTxTempDefine[UCOM_NV_W_TX_PA_TEMP_NUM];
}UCOM_NV_WG_TX_TEMP_DEFINE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_TEMP_SENCOR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :for UCOM_NV_PA_TEMP_SENSOR_STRU
                UCOM_NV_XO_TEMP_SENSOR_STRU
                UCOM_NV_USIM_BATT_TEMP_SENSOR_STRU
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwPaTempTemp;                          /* 温度:0.1度 */
    VOS_UINT16                          uhwPaTempVol;                           /* 热敏电阻检测电压 */
}UCOM_NV_TEMP_SENCOR_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_PA_TEMP_SENSOR_TABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :7.1 PA的温度检测表
*****************************************************************************/
typedef struct
{
    UCOM_NV_TEMP_SENCOR_STRU            astPaTempSensor[UCOM_NV_PA_TEMP_SENSOR_NUM];
}UCOM_NV_PA_TEMP_SENSOR_TABLE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_XO_TEMP_SENSOR_TABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :7.1 普通晶体的常(高)温电压-温度表
*****************************************************************************/
typedef struct
{
    UCOM_NV_TEMP_SENCOR_STRU            astXoTempSensor[UCOM_NV_XO_TEMP_COMP_NUM];
}UCOM_NV_XO_TEMP_SENSOR_TABLE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_XO_LOW_TEMP_SENSOR_TABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :7.1 普通晶体的低温电压-温度表
*****************************************************************************/
typedef struct
{
    UCOM_NV_TEMP_SENCOR_STRU            astXoLowTempSensor[UCOM_NV_XO_TEMP_COMP_NUM];
}UCOM_NV_XO_LOW_TEMP_SENSOR_TABLE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_BATT_TEMP_SENSOR_TABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :7.1 电池的温度检测表
*****************************************************************************/
typedef struct
{
    UCOM_NV_TEMP_SENCOR_STRU            astBattTempSensor[UCOM_NV_BATT_TEMP_SENSOR_NUM];
}UCOM_NV_BATT_TEMP_SENSOR_TABLE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY
 协议表格  :
 ASN.1描述 :
 结构说明  : 产品类型NV。不同产品，Log保存路径不一样
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwProductType;                         /* 产品类型 */
    VOS_UINT16                          uhwReserve;                             /* 保留 */
}UCOM_NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY;

/*****************************************************************************
 结构名    : UCOM_NV_XO_LOW_TEMP_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : XO低温检测特性相关NV,包括特性开关与电路切换门限
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwLowTempSupport;                      /* 硬件是否支持低温检测，0-不支持，1-支持 */
    VOS_INT16                           shwSwitchDeltaTemp;                     /* 低温电路与原有电路的切换门限为(校准温度+该值)，
                                                                                   当低于切换门限温度时使用低温电路，默认为0，
                                                                                   即切换门限为校准温度(常温电路)，单位0.1度 */
    VOS_UINT16                          uhwTempDeltaThreshold;                  /* 两个电路校准值的偏差门限，默认为10，单位0.1度 */
    VOS_UINT16                          uhwReserve;                             /* 保留 */
}UCOM_NV_XO_LOW_TEMP_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_XO_INIT_LOW_TEMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 校准时，低温电路的检测温度，备份恢复项
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwInitLowTemp;                         /* 校准时，低温电路的检测温度，单位0.1度 */
    VOS_UINT16                          uhwReserve;                             /* 保留 */
}UCOM_NV_XO_INIT_LOW_TEMP_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_WG_IQ_REV_CONTROL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IQ接反配置
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRxAIRevSel;                          /* Rx A I路接反 */
    VOS_UINT16                          uhwRxAQRevSel;                          /* Rx A Q路接反 */
    VOS_UINT16                          uhwRxBIRevSel;                          /* Rx B I路接反 */
    VOS_UINT16                          uhwRxBQRevSel;                          /* Rx B Q路接反 */
    VOS_UINT16                          uhwTxIRevSel;                           /* Tx I路接反 */
    VOS_UINT16                          uhwTxQRevSel;                           /* Tx Q路接反 */
}UCOM_NV_WG_IQ_REV_CONTROL_STRU;


/*****************************************************************************
 结构名    : UCOM_DCXO_TEMP_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存DCXO多项式的 4个系数和温度的最大最小值
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          auwMantissaDefault[UCOM_DCXO_POLY_COEFF_NUM];  /* 依次存放a0,a1,a2,a3的尾数 */
    VOS_UINT16                          auhwExponentDefault[UCOM_DCXO_POLY_COEFF_NUM]; /* 依次存放a0,a1,a2,a3的指数 */
    /* 特别说明:shwTmax/shwTmin实际上是和样本邦定的,和系数定义在一起不合理.因为不合理,所以DSP内部
       只使用pstAfcContext->stDcxoPara.shwSampleTempMax/shwSampleTempMin */
    VOS_INT16                           shwTmax;                                /* 样本温度最大值 */
    VOS_INT16                           shwTmin;                                /* 样本温度最小值 */
}UCOM_NV_DCXO_TEMP_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_DCXO_AFC_VS_TEMP_VALUE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 存放一组DCXO的温度-频率(实际为AFC控制值)样本
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTemp;                                /* 温度 */
    VOS_INT16                           shwFreqPpm;                              /* 上面温度下对应的相对频偏 */
}UCOM_NV_DCXO_AFC_VS_TEMP_VALUE_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_DCXO_TEMP_READ_PERIOD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DCXO读取温度的周期,区分IDLE态和DCH态
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwIdlePeriod;                          /* IDLE态下读取周期 */
    VOS_UINT16                          uhwDchPeriod;                           /* IDLE态下读取周期 */
}UCOM_NV_DCXO_TEMP_READ_PERIOD_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_DCXO_TEMP_COMP_THRESHOLD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DCXO多项式系数更新门限
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          auwLowMantissa[UCOM_DCXO_POLY_COEFF_NUM];
    VOS_UINT16                          auhwLowExponent[UCOM_DCXO_POLY_COEFF_NUM];
    VOS_UINT32                          auwHighMantissa[UCOM_DCXO_POLY_COEFF_NUM];
    VOS_UINT16                          auhwHighExponent[UCOM_DCXO_POLY_COEFF_NUM];
}UCOM_NV_DCXO_TEMP_COMP_THRESHOLD_STRU;


/*****************************************************************************
 结构名    : UCOM_DCXO_FREQ_VS_TEMP_ARRAY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 存放DCXO的温度-频率(实际为AFC控制值)样本集合
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwValidNum;                             /* 样本的有效个数 */
    VOS_INT16                           shwTmax;                                /* 样本温度最大值 */
    VOS_INT16                           shwTmin;                                /* 样本温度最小值 */
    UCOM_NV_DCXO_AFC_VS_TEMP_VALUE_STRU astAfcTempValue[UCOM_DCXO_TEMP_AFC_MAX_NUM]; /* 样本数据 */
}UCOM_NV_DCXO_FREQ_VS_TEMP_ARRAY_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_DCXO_SAMPLE_UPDATE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DCXO样本更新参数定义
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwWcdmaPeriod;                          /* W DCXO样本写入NV周期，单位帧,默认30000 */
    VOS_UINT32                          uwGsmPeriod;                            /* G DCXO样本写入NV周期，单位帧,默认65000 */
    VOS_UINT16                          uhwUpdateLowThr;                        /* 样本更新下门限,默认644,即0.6ppm*2^30/10^6 */
    VOS_UINT16                          uhwUpdateHighThr;                       /* 样本更新上门限,默认2684,即2.5ppm*2^30/10^6 */
}UCOM_NV_DCXO_SAMPLE_UPDATE_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_TAS_GPIO_CTRL_WORD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwTasM2PowerCtrlWord;                   /* Tas TxBlanking时M0衰减M2功率的控制字 */
}UCOM_NV_TAS_GPIO_CTRL_WORD_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_SAR_BACKOFF_TEST_MODE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 降SAR测试模式
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSarBackoffTestModeFlg;               /* 降SAR测试模式 */
}UCOM_NV_SAR_BACKOFF_TEST_MODE_STRU;

typedef UCOM_NV_SAR_BACKOFF_TEST_MODE_STRU  UCOM_NV_GUC_SAR_BACKOFF_TEST_MODE_STRU;
/*****************************************************************************
 枚举名    : UCOM_NV_WG_DCOFFSET_THRESHOLD_STRU
 协议表格  :
 枚举说明  : DC offset的直流校准门限
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwDciLimit;                            /* I路的直流门限,单位mV */
    VOS_INT16                           shwDcqLimit;                            /* Q路的直流门限,单位mV */
}UCOM_NV_WG_DCOFFSET_THRESHOLD_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_DCXO_CTRIM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DCXO C1值
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwDcxoCTrim;                           /*Range:[0,255]*/
}UCOM_NV_DCXO_CTRIM_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_DCXO_C2_FIX_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DCXO C2校准值
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwDcxoC2fix;
}UCOM_NV_DCXO_C2_FIX_STRU;
/*****************************************************************************
 结构名    : UCOM_NV_TCXO_AFC_SLOPE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UCOM_NV_TCXO_AFC_SLOPE_STRU
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwAfcSlope;                             /* TCXO AFC??,??? */
}UCOM_NV_TCXO_AFC_SLOPE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_DCXO_SEARCH_AFC_OFFSET_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ashwSearchAfc2和ashwSearchAfcDelta2构成第二次搜网的校准曲线
             ashwSearchAfc3和ashwSearchAfcDelta3构成第三次搜网的校准曲线
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwSearchAfc2[UCOM_NV_DCXO_SEARCH_AFC_OFFSET_SAMPLE_NUM];      /* 第二次搜索AFC值 */
    VOS_INT16                           ashwSearchAfcDelta2[UCOM_NV_DCXO_SEARCH_AFC_OFFSET_SAMPLE_NUM]; /* 第二次搜索AFC偏置值 */
    VOS_INT16                           ashwSearchAfc3[UCOM_NV_DCXO_SEARCH_AFC_OFFSET_SAMPLE_NUM];      /* 第三次搜索AFC值 */
    VOS_INT16                           ashwSearchAfcDelta3[UCOM_NV_DCXO_SEARCH_AFC_OFFSET_SAMPLE_NUM]; /* 第三次搜索AFC偏置值 */
}UCOM_NV_DCXO_SEARCH_AFC_OFFSET_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_BUCK_VOLT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : BUCK电压值
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwBuck1Volt;                           /* buck1电压值,单位mV */
    VOS_UINT16                          uhwBuck2Volt;                           /* buck2电压值,单位mV */
}UCOM_NV_BUCK_VOLT_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_RFIC_SSI_WAIT_TIME_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : BUCK电压值
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRficSsiWaitTime;
}UCOM_NV_RFIC_SSI_WAIT_TIME_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_LINEAR_PA_GAIN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 线性PA的增益
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwNumber;
    VOS_INT16                           ashwGain[UCOM_NV_GSM_LINEAR_PA_GAIN_NUM];
}UCOM_NV_GSM_LINEAR_PA_GAIN_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_EDGE_LINEAR_PA_GAIN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 线性PA的增益
*****************************************************************************/
/*****************************************************************************
 结构名    : UCOM_NV_GSM_LINEAR_PA_GAIN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 线性PA的增益
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwNumber;
    VOS_INT16                           ashwGain[UCOM_NV_GSM_LINEAR_PA_GAIN_NUM];
}UCOM_NV_EDGE_LINEAR_PA_GAIN_STRU;



/*****************************************************************************
 结构名    : UCOM_NV_GSM_TX_PCL_PA_GAIN_INDEX_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 线性PA的增益索引
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           auhwPaGainIndex[UCOM_NV_G_PCL_NUM];     /* 32个功率等级对应的PA增益索引 */
}UCOM_NV_GSM_TX_PCL_PA_GAIN_INDEX_STRU;



/*****************************************************************************
 结构名    : UCOM_NV_EDGE_TX_PCL_PA_GAIN_INDEX_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 线性PA的增益索引
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           auhwPaGainIndex[UCOM_NV_G_PCL_NUM];     /* 32个功率等级对应的PA增益索引 */
}UCOM_NV_EDGE_TX_PCL_PA_GAIN_INDEX_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_TX_REF_CHAN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwValidChanNum;                                /* 有效频点个数 */
    VOS_UINT16                          auhwTxChan[UCOM_NV_G_TX_REF_CHAN_NUM_MAX];      /* 参考频点列表 */
}UCOM_NV_TX_CAL_CHAN_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_RAMP_INDEX_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwRampIndex[UCOM_NV_G_PCL_NUM];
}UCOM_NV_GSM_RAMP_INDEX_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_EDGE_RAMP_INDEX_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwRampIndex[UCOM_NV_G_PCL_NUM];
}UCOM_NV_EDGE_RAMP_INDEX_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_RAMP_COEFF_STRU
 协议表格  :
 结构说明  : GSM/EDGE上下行爬坡表NV项参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwRampUp[UCOM_NV_G_RAMP_COEF_NUM];    /* 上坡表 */
    VOS_UINT16                          auhwRampDown[UCOM_NV_G_RAMP_COEF_NUM];  /* 下坡表 */
}UCOM_NV_GSM_RAMP_COEFF_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_RAMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM爬坡系数结构
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_RAMP_COEFF_STRU         astRampCoeff[UCOM_NV_G_RAMP_PWR_LEVEL_NUM];     /* [依次以10dBm,20dBm划分为3个区间] */
}UCOM_NV_GSM_RAMP_STRU;



/*****************************************************************************
 结构名    : UCOM_NV_EDGE_RAMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : EDGE爬坡系数结构
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_RAMP_COEFF_STRU         astRampCoeff[UCOM_NV_G_RAMP_PWR_LEVEL_NUM];     /* [依次以10dBm,20dBm划分为3个区间] */
}UCOM_NV_EDGE_RAMP_STRU;



/*****************************************************************************
 结构名    : UCOM_NV_GSM_PA_TABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 注意电压和发射功率的对应关系 */
    VOS_UINT16                          auhwTxPower[UCOM_NV_G_TX_PWR_CONT_NUM];         /* 需要校正的发射功率 */
    VOS_UINT16                          auhwContVolt[UCOM_NV_G_TX_PWR_CONT_NUM];        /* 需要校正的发射功率对应的控制电压 */
}UCOM_NV_GSM_PA_TABLE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_PA_TABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/

/* 自研RF，8PSK同样使用电压字控制 */
typedef struct
{
    VOS_UINT16                          auhwContVolt[UCOM_NV_G_TX_8PSK_PWR_CONT_NUM];   /* 需要校正的发射功率对应的控制电压 */
    VOS_UINT16                          auhwTxPower[UCOM_NV_G_TX_8PSK_PWR_CONT_NUM];    /* 需要校正的发射功率 */
}UCOM_NV_EDGE_PA_TABLE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_PA_TABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwGsmMaxTxVolt;
    VOS_UINT16                          uhwGsmMaxTxPower;
}UCOM_NV_GSM_MAX_TX_VOLT_POWER;


/*****************************************************************************
 结构名    : UCOM_NV_G_TIMING_CTRL_CTRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwTimingCtrl;
}UCOM_NV_G_TIMING_CTRL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_G_RAMP_POINTS_CTRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 爬坡点数结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRampPoints;                          /* 爬坡点数 */
}UCOM_NV_G_RAMP_POINTS_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_G_PREMOD_SYMBOL_CTRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 预调制符号结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwPreModSymbol;                        /* 预调制符号 */
}UCOM_NV_G_PREMOD_SYMBOL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_G_TX_BURST_OFFSET_CTRU
 协议表格  :
 ASN.1描述 :
 结构说明  : burset offset结构
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTxBurstOffset;                       /* GSM burst offset */
}UCOM_NV_G_TX_BURST_OFFSET_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_G_TX_PA_LENGTH_CTRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PA保持最大电压的长度结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwTxPaLength;                          /* PA保持最大电压的长度，单位为Qb */
}UCOM_NV_G_TX_PA_LENGTH_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_G_PA_PRECHG_VOLT_CTRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PA保持最大电压的长度结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwPaPrechgVolt;                        /*Range:[0,1023]*//* 校准后的预充电压 */
}UCOM_NV_G_PA_PRECHG_VOLT_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_G_PA_FACTORY_PRECHARGE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwInit;
    VOS_INT16                           shwDelta;
}UCOM_NV_G_PA_FACTORY_PRECHARGE_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_RX_IP2_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :I和Q通道直流，为NV项中通用的I和Q通道偏置
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwIReg;                                /* I路寄存器取值，拼接方式 = SN[0]+DATA[6:0] */
    VOS_INT16                           shwQReg;                                /* Q路寄存器取值，拼接方式 = SN[0]+DATA[6:0] */
}UCOM_NV_RX_IP2_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_RX_IP2_CAL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :5.2 每个BAND在高中低频点下，对I和Q路的电路参数补偿
*****************************************************************************/
typedef struct
{
    UCOM_NV_RX_IP2_STRU                 astRxIp2Cal[3];
}UCOM_NV_GSM_RX_IP2_CAL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_RX_AGC_FREQ_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :5.4 在AGC增益在统一个频段内因频点不同而引起的增益变化
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwRxAgcFreqComp[UCOM_NV_G_RX_CHAN_COMP_NUM];  /*Rang:[-64,64]*//* 一个频段内16个频点 */
}UCOM_NV_GSM_RX_AGC_FREQ_COMP_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_EDGE_TX_APC_RF_ATTEN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :6.1 RF芯片对基带信号的衰减，用于配置RF芯片寄存器
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwEdgeTxApcRfAtten[UCOM_NV_G_TX_ATTEN_NUM];
}UCOM_NV_EDGE_TX_APC_RF_ATTEN_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_EDGE_TX_APC_DBB_ATTEN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :6.1 DBB芯片对基带信号的补偿，
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwEdgeTxApcDbbAtten[UCOM_NV_G_TX_ATTEN_NUM];
}UCOM_NV_EDGE_TX_APC_DBB_ATTEN_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_PA_VBIAS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :6.3 在不同功率等级下，因为PA供电电压(或者偏置电压)可以下降到的最低电压
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwPaVbias[UCOM_NV_G_PCL_NUM];     /* 32个DA变换前的值 */
}UCOM_NV_GSM_PA_VBIAS_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_EDGE_PA_VBIAS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :6.3 在不同功率等级下，因为PA供电电压(或者偏置电压)可以下降到的最低电压
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwPaVbias[UCOM_NV_G_PCL_NUM];     /* 32个DA变换前的值 */
}UCOM_NV_EDGE_PA_VBIAS_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_PA_VBIAS_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :6.3 在不同功率等级下，因为PA供电电压(或者偏置电压)下降，而引起PA增益变化的大小。
*****************************************************************************/
typedef struct
{
    VOS_INT16                           auhwPaVccVbiasComp[UCOM_NV_G_PCL_NUM];  /* 32个功率补偿值 */
}UCOM_NV_GSM_PA_VCC_VBIAS_COMP_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_EDGE_PA_VBIAS_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :6.3 在不同功率等级下，因为PA供电电压(或者偏置电压)下降，而引起PA增益变化的大小。
*****************************************************************************/
typedef struct
{
    VOS_INT16                           auhwPaVccVbiasComp[UCOM_NV_G_PCL_NUM];  /* 32个功率补偿值 */
}UCOM_NV_EDGE_PA_VCC_VBIAS_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_TX_TEMP_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GMSK(线性PA) TX相对于温度变化的补偿
*****************************************************************************/
typedef struct
{
    /* 温度范围的取值取决于UCOM_NV_WG_TX_TEMP_DEFINE_STRU */
    VOS_INT16                           ashwGsmTxTempComp[UCOM_NV_G_TEMP_LEVEL_NUM];   /*Range:[-100,100]*/
}UCOM_NV_GSM_TX_TEMP_COMP_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_EDGE_TX_TEMP_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :7.7 8PSK TX相对于温度变化的补偿
*****************************************************************************/
typedef struct
{
    /* 温度范围的取值取决于UCOM_NV_WG_TX_TEMP_DEFINE_STRU */
    VOS_INT16                           ashwEdgeTxTempComp[UCOM_NV_G_TEMP_LEVEL_NUM];   /*Range:[-100,100]*/
}UCOM_NV_EDGE_TX_TEMP_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_RX_CAL_CHAN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :需要校准的GSM的频点个数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwValidCalChanNum;                     /*Range:[0,16]*/
    VOS_UINT16                          auhwGsmRxCalChan[UCOM_NV_G_RX_CHAN_COMP_NUM];
}UCOM_NV_GSM_RX_CAL_CHAN_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_RX_AGC_GAIN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :5.3 AGC每个状态的增益值，总共分成8档
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwRxAgcGain[UCOM_NV_G_CHAN_GAIN_MAX_NUM];
}UCOM_NV_GSM_RX_AGC_GAIN_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_ EDGE_TX_TEMP_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 表示每档档RF Gain对应的温度补偿值
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwTempComp10th[UCOM_NV_EDGE_TX_TEMP_COMP_NUM];      /* 表示某一档RF Gain在16个采样温度下的温度补偿值，单位为0.1dB */
}UCOM_NV_EDGE_TEMP_COMP_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_EDGE_TX_RF_GAIN_TEMP_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 表示15档RF Gain对应的温度补偿值
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwValidCount;
    UCOM_NV_EDGE_TEMP_COMP_STRU         astTempComp[UCOM_NV_EDGE_TX_RF_GAIN_CTRL_NUM];      /* 表示15档RF Gain在16个采样温度下的温度补偿值 */
}UCOM_NV_EDGE_RF_GAIN_TEMP_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_PA_VCC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 在不同功率等级下，GSM对应的VCC电压控制字
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwGsmPaVcc[UCOM_NV_G_PCL_NUM];        /* 32个DA变换前的值 */
}UCOM_NV_GSM_PA_VCC_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_EDGE_PA_VCC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 在不同功率等级下，EDGE对应的VCC电压控制字
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwEdgePaVcc[UCOM_NV_G_PCL_NUM];       /* 32个DA变换前的值 */
}UCOM_NV_EDGE_PA_VCC_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_CLOSE_MIPI_PA_VCC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : close vcc control
*****************************************************************************/
typedef struct
{
    UCOM_NV_MIPI_CMD_STRU               stClosePaVccMipiCmd;                    /* 关闭PaVcc的mipi指令帧 */
    UCOM_NV_MIPI_BYTE_DATA_STRU         stClosePaVccMipiData;                   /* 关闭PaVcc的Mipi数据帧 */
}UCOM_NV_GSM_CLOSE_MIPI_PA_VCC_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_DEV_AVOID_GSM_SLOT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GPS避让GSM时隙
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwPowerThreshold;                      /* 功率门限，大于该门限时启动避让模式，单位为0.1dbm */
    VOS_UINT16                          uhwBandMask;                            /* 用于避让的频段掩码，BIT0/1/2/3对应850/900/1800/1900M */
    VOS_UINT32                          uwIoMask;                               /* 用于避让的管脚 */
}UCOM_NV_DEV_AVOID_GSM_SLOT_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_REDUCE_CURRENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 二级限流
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwReduceCurrentEn;                     /* 二级限流使能 */
    UCOM_NV_RFFE_CTRL_ENUM_UINT16       enCtrlMode;                             /* 控制方式MIPI或GPIO */
    VOS_UINT32                          uwGpioMask;                             /* 二级限流使用的管脚 */
    UCOM_NV_MIPI_CMD_STRU               stPmuMipiCmd;                           /* 二级限流对应的PMU地址 */
    UCOM_NV_MIPI_BYTE_DATA_STRU         stDefaultMipiData;                      /* 缺省时的电流值(第一个时隙) */
    UCOM_NV_MIPI_BYTE_DATA_STRU         stLimitMipiData;                        /* 限流时的配置值(非第一个时隙) */
    VOS_UINT16                          uhwReserved;
}UCOM_NV_GSM_REDUCE_CURRENT_STRU;


/*****************************************************************************
 结构名    : UCOM_GSM_TX_APC_CAL_TEMP
 协议表格  :
 ASN.1描述 :
 结构说明  : Gsm下APC校准温度
*****************************************************************************/
typedef struct
{
    VOS_INT16                               shwGsmTxApcCalTemp;                 /*Range:[-300,1350]*/
}UCOM_GSM_TX_APC_CAL_TEMP_STRU;


/*****************************************************************************
 结构名    : UCOM_EDGE_TX_APC_CAL_TEMP
 协议表格  :
 ASN.1描述 :
 结构说明  : Edge下APC校准温度
*****************************************************************************/
typedef struct
{
    VOS_INT16                               shwEdgeTxApcCalTemp;                /*Range:[-300,1350]*/
}UCOM_EDGE_TX_APC_CAL_TEMP_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_START_BYPASS_THRESHOLD
 协议表格  :
 ASN.1描述 :
 结构说明  : G模的Bypass门限
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwGsmStartBypassThreshold;
}UCOM_NV_GSM_START_BYPASS_THRESHOLD_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_TX_POWER
 协议表格  :
 ASN.1描述 :
 结构说明  : 需要校正的发射功率
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwGsmTxPower[UCOM_NV_G_TX_PWR_CONT_NUM];  /*Range:[-400,400]*//* 需要校正的发射功率 */
}UCOM_NV_GSM_TX_POWER_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_TX_POWER
 协议表格  :
 ASN.1描述 :
 结构说明  : 需要校正的发射功率对应的控制电压
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwGsmContVolt[UCOM_NV_G_TX_PWR_CONT_NUM]; /*Range:[0,1023]*//* 需要校正的发射功率对应的控制电压 */
}UCOM_NV_GSM_CONT_VOLT_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_TX_POWER
 协议表格  :
 ASN.1描述 :
 结构说明  : 不同频点的发射功率的补偿值
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwGsmTxFreqComp[UCOM_NV_G_TX_CHAN_COMP_NUM];  /*Range:[-100,100]*//* [频段][不同频点的发射功率的补偿值] ，单位0.1dBm*/
}UCOM_NV_GSM_TX_FREQ_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_EDGE_TX_FREQ_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Edge校准发射功率的补偿值
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwGsmTxFreqComp[UCOM_NV_G_TX_CHAN_COMP_NUM];  /*Range:[-100,100]*//* [频段][不同频点的发射功率的补偿值] ，单位0.1dBm*/
}UCOM_NV_EDGE_TX_FREQ_COMP_STRU;



/*****************************************************************************
 结构名    : UCOM_NV_GSM_LINEAR_PA_TX_APC_DBB_ATTEN
 协议表格  :
 ASN.1描述 :
 结构说明  : gsm linear pa apc dbb atten
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwGsmLinearPaTxApcDbbAtten[UCOM_NV_G_TX_ATTEN_NUM];   /*Range:[-40,10]*//* gsm linear pa apc dbb atten */
}UCOM_NV_GSM_LINEAR_PA_TX_APC_DBB_ATTEN_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_TX_RF_ATTEN
 协议表格  :
 ASN.1描述 :
 结构说明  : RF衰减
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwGsmTxRfAtten;   /* RF衰减 */
}UCOM_NV_GSM_TX_RF_ATTEN_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_TX_POWER_LEVEL
 协议表格  :
 ASN.1描述 :
 结构说明  : 4频段功率等级到dBm的映射表
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwGsmTxPowerLevel[UCOM_NV_G_PCL_NUM]; /* 4频段功率等级到dBm的映射表 */
}UCOM_NV_GSM_TX_POWER_LEVEL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_MAX_POWER_REDUCTION
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM最大发射功率回退
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwGsmMaxPowerReduction[UCOM_NV_G_TX_SLOT_MAX_NUM];
}UCOM_NV_GSM_MAX_POWER_REDUCTION_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_WIRELESS_MAX_POWER
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM无线最大发射功率
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwGsmWirelessMaxPower[UCOM_NV_G_TX_SLOT_MAX_NUM]; /* 无线 *//* 4频段GMSK空口发射时的功率衰减 */
}UCOM_NV_GSM_WIRELESS_MAX_POWER_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_SAR_BACK_OFF_POWER
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM下各时隙SAR回退值
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwGsmSarBackoffPower[UCOM_NV_SAR_BACKOFF_NUM][UCOM_NV_SAR_MODEM_SCENE_NUM];
}UCOM_NV_GSM_SAR_BACK_OFF_POWER_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_EDGE_TX_PA_GAIN
 协议表格  :
 ASN.1描述 :
 结构说明  : 传统PA的增益
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEdgeTxPaGain;                        /* 传统PA的增益 */
}UCOM_NV_EDGE_TX_PA_GAIN_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_LINEAR_PA_APC_RF_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GMSK(线性PA)下APC RF控制字
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwGsmLinearPaApcRfCtrl[UCOM_NV_G_TX_ATTEN_NUM];    /* apc rf ctrl */
}UCOM_NV_GSM_LINEAR_PA_APC_RF_CTRL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_EDGE_TX_APC_RF_CTRL
 协议表格  :
 ASN.1描述 :
 结构说明  : EDGE下APC RF控制字
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwEdgeTxApcRfCtrl[UCOM_NV_G_TX_ATTEN_NUM];    /* apc rf ctrl */
}UCOM_NV_EDGE_TX_APC_RF_CTRL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_LINEAR_PA_RF_GAIN_STATE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GMSK(线性PA)下APC DBB衰减
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwGsmLinearPaRfGainStateIndex[UCOM_NV_G_TX_ATTEN_NUM]; /* rf gain 索引 */
}UCOM_NV_GSM_LINEAR_PA_RF_GAIN_STATE_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_LINEAR_PA_NONLINEAR_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GMSK(线性PA)下APC DBB衰减
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwComp[UCOM_NV_G_PCL_NUM];
}UCOM_NV_GSM_LINEAR_PA_NONLINEAR_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_EDGE_LINEAR_PA_NONLINEAR_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : EDGE(线性PA)下APC DBB衰减
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwComp[UCOM_NV_G_PCL_NUM];
}UCOM_NV_EDGE_LINEAR_PA_NONLINEAR_COMP_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_EDGE_TX_RF_GAIN_STATE_INDEX
 协议表格  :
 ASN.1描述 :
 结构说明  : EDGE下APC DBB衰减
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwEdgeTxRfGainStateIndex[UCOM_NV_G_TX_ATTEN_NUM]; /* rf gain 索引 */
}UCOM_NV_EDGE_TX_RF_GAIN_STATE_INDEX_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_G_RSSI_ARITHMETIC_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : G模通道固定增益
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRssiArithmeticPara;
}UCOM_NV_G_RSSI_ARITHMETIC_PARA_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_G_RX_PLL_ADVANCE_TIMING_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : rx pll提前打开时间
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRxPllAdvanceTiming;
}UCOM_NV_G_RX_PLL_ADVANCE_TIMING_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_AFC_FE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwAfcFeDelayFn;                        /* FE延迟帧数 */
    VOS_UINT16                          uhwAfcFePowerDis;                       /*  */
    VOS_UINT16                          uhwAfcFeDchFcut0;                       /*  */
    VOS_UINT16                          uhwAfcFeDchFcut1;                       /*  */
}UCOM_NV_GSM_AFC_FE_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_G_ADJ_CHAN_INTERFERE_EN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 邻频抑制使能标志
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwAdjChanInterfereEn;                  /* 邻频抑制使能 */
}UCOM_NV_G_ADJ_CHAN_INTERFERE_EN_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_G_LS_DCR_EN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ls dcr使能标志
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwLsDcrEn;                             /* ls dcr使能 */
}UCOM_NV_G_LS_DCR_EN_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_G_LINEAR_PA_ENABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LinearPA使能标志
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwLinearPaEnable;                      /* linear Pa使能 */
}UCOM_NV_G_LINEAR_PA_ENABLE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_LINEAR_PA_GAIN_WORD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 线性PA的增益控制字
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          auwWord[UCOM_NV_GSM_LINEAR_PA_GAIN_NUM];
}UCOM_NV_GSM_LINEAR_PA_GAIN_WORD_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_G_APT_ENABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LinearPA使能标志
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwGsmAptEnable;                        /* 2G APT使能标志 */
}UCOM_NV_G_APT_ENABLE_STRU;



/*****************************************************************************
 结构名    : UCOM_NV_GSM_SPUR_ACPR_OPT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM SPUR ACPR优化
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwGsmSpurAcprOpt;                      /* 2G GSM SPUR 优化 */
}UCOM_NV_GSM_SPUR_ACPR_OPT_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_G_BY_PASS_GPIO_MASK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Bypass导通时配置GPIO口的bit位
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwBypassGpioMask;                       /* Bypass导通时配置GPIO口的bit位 */
}UCOM_NV_G_BY_PASS_GPIO_MASK_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_G_PA_VCC_MIPI_CMD_FRAME_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 打开PaVcc的mipi指令帧
*****************************************************************************/
typedef struct
{
    UCOM_NV_MIPI_CMD_STRU               stPaVccMipiCmdFrame;                    /* 打开PaVcc的mipi指令帧 */
    VOS_UINT16                          uhwMipiMasterSel;
}UCOM_NV_G_PA_VCC_MIPI_CMD_FRAME_STRU;



/*****************************************************************************
 枚举名    : UCOM_NV_GSM_RX_AGC_CTRL_STRU
 协议表格  :
 枚举说明  : 5.3G下行AGC增益控制字
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          aunRxAgcCtrl[UCOM_NV_G_AGC_LEVEL_MAX_NUM];
}UCOM_NV_GSM_RX_AGC_CTRL_STRU;


/*****************************************************************************
 枚举名    : UCOM_NV_GSM_AGC_SWITCH_THRESHOLD_STRU
 协议表格  :
 枚举说明  : AGC增益切换门限
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwIncDelay;                                /* 切换迟滞 */
    VOS_INT16                           ashwDec[UCOM_NV_G_GAIN_THRESHOLD_MAX_NUM];  /* 切换门限 */
}UCOM_NV_GSM_AGC_SWITCH_THRESHOLD_STRU;


/*****************************************************************************
 枚举名    : UCOM_NV_GSM_AGC_FASTMEAS_THRESHOLD_STRU
 协议表格  :
 枚举说明  : 快速测量AGC增益切换门限
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwInitAgc;                                 /* 快速测量初始档位 */
    VOS_INT16                           ashwDec[UCOM_NV_G_GAIN_THRESHOLD_MAX_NUM];  /* 切换门限 */
}UCOM_NV_GSM_AGC_FASTMEAS_THRESHOLD_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_ACPR_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTempThreshold;                       /* 温度门限，单位为度 */
    VOS_INT16                           shwPowerComp;                           /* 功率补偿，单位为0.1dbm */
}UCOM_NV_GSM_ACPR_CONFIG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_EDGE_RF_TX_BIAS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwBiasHighTemp;                       /* 温度门限，单位为度 */
    VOS_INT16                           shwBiasRoomTemp;                           /* 功率补偿，单位为0.1dbm */
}UCOM_NV_EDGE_RF_TX_BIAS_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_RX_DCR_CHAN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :DCR 需要校准的GSM的频点个数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uhwValidDcrChanNum;
    VOS_UINT16                          auhwGsmRxCalChan[ UCOM_G_RX_GAIN0_DCR_CHAN_NUM ];
}UCOM_NV_GSM_RX_DCR_CHAN_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_RX_DC_OFFSET_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM DC Offset值
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwInitDcoci;                           /* 初始值,RFIC控制值为0x80对应的I路DC值 */
    VOS_INT16                           shwInitDcocq;                           /* 初始值,RFIC控制值为0x80对应的Q路DC值 */
    VOS_INT16                           shwRfDci;                               /* 校准后,RFIC I路DC控制值 */
    VOS_INT16                           shwRfDcq;                               /* 校准后,RFIC Q路DC控制值 */
    VOS_INT16                           shwRemainDcoci;                         /* 校准后,I路残余DC值 */
    VOS_INT16                           shwRemainDcocq;                         /* 校准后,Q路残余DC值 */
}UCOM_NV_GSM_DC_OFFSET_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_RX_DC_OFFSET_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM DC Offset值
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwValidCount;
    UCOM_NV_GSM_DC_OFFSET_STRU          astGain0DcOffset[ UCOM_G_RX_GAIN0_DCR_CHAN_NUM ];
}UCOM_NV_GSM_RX_DC_OFFSET_GAIN0_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_RX_DC_OFFSET_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM DC Offset值
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_DC_OFFSET_STRU           astGain0[UCOM_G_RX_GAIN0_DCR_CHAN_NUM ];             /* 本频Gain0档位，DCR校准结果 */
    UCOM_NV_GSM_DC_OFFSET_STRU           astOtherGain[UCOM_G_RX_OTHER_GAIN_DCR_CHAN_NUM];  /*本频其它档位DCR校准结果:UCOM_NV_G_AGC_LEVEL_MAX_NUM -1 */
    UCOM_NV_GSM_DC_OFFSET_STRU           astCrossBandGain0[UCOM_G_RX_GAIN0_DCR_CHAN_NUM];     /* 异频Gain0档位，DCR校准结果 */
    UCOM_NV_GSM_DC_OFFSET_STRU           astCrossBandOtherGain[UCOM_G_RX_OTHER_GAIN_DCR_CHAN_NUM]; /*异频其它档位DCR校准结果:UCOM_NV_G_AGC_LEVEL_MAX_NUM -1 */
}UCOM_NV_GSM_RX_DC_OFFSET_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_RF_GPIO_MASK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RF 控制结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwGsmAntMask;                           /* 该值表示W的BAND或者G模的BAND标识 */
    VOS_UINT32                          uwPaEnMask;                             /* RF所在的通道 */
    VOS_UINT32                          uwPaBandMask;                           /* 天线1的开关值 */
    VOS_UINT32                          uwPaModeMask;                           /* 天线2的开关值 */
}UCOM_NV_GSM_RF_GPIO_MASK_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_TUNER_GPIO_MASK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RF TUNER GPIO控制结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwTunerMask;                            /* Tuner的掩码，如TUNER使用BIT2,BIt3作为线控，则掩码为BIT2|BIT3 */
    VOS_UINT32                          uwReserved;                             /* 保留位 */
}UCOM_NV_GSM_TUNER_GPIO_MASK_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_NCELL_TASK_RANK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 邻区任务优先级结构
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwImmedExeRankRxlevThd;                /* 突然增强邻区Rxlev判决门限 10  */
    VOS_INT16                           shwLowRxlevRankRxlevThd;                /* 低Rxlev邻区Rxlev判决门限 108 */
    VOS_UINT16                          uhwBchTimerOutCntPeriod;                /* 空闲态定时器超时次数计数周期 12 */
    VOS_UINT16                          uhwBchSBSuccRankLockLen;                /* 空闲态SB成功优先级锁定时长 6 */
    VOS_UINT16                          uhwBchBlackListRankLockLen;             /* 空闲态黑名单优先级锁定时长 6 */
    VOS_UINT16                          uhwDchTimerOutCntPeriod;                /* 专用态定时器超时次数计数周期 12 */
    VOS_UINT16                          uhwDchSBSuccRankLockLen;                /* 专用态SB成功优先级锁定时长 2 */
    VOS_UINT16                          uhwDchBlackListRankLockLen;             /* 专用态黑名单优先级锁定时长 2 */
}UCOM_NV_GSM_NCELL_TASK_RANK_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_INTERRAT_GAP_NUM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 异系统任务分沟个数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwWphyGapNum;                          /* WPHY的沟的个数 */
    VOS_UINT16                          uhwLphyGapNum;                          /* LPHY的沟的个数 */
    VOS_UINT16                          uhwTphyGapNum;                          /* TPHY的沟的个数 */
    VOS_UINT16                          uhwRsv;                                 /* rsv */
}UCOM_NV_GSM_INTERRAT_GAP_NUM_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_INTERRAT_RANK_AND_GAP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 专用态异系统任务优先级及分沟个数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwHighestRank;                         /* 专用态异系统任务最高优先级默认值5 */
    VOS_UINT16                          uhwLowestRank;                          /* 专用态异系统任务最低优先级默认值205 */
    VOS_UINT16                          uhwRankStep;                            /* 专用态异系统任务优先级变化步长默认值30*/
    VOS_UINT16                          uhwOverMaxGapRank;                      /* 专用态异系统任务已经分配的沟的数目大于最大值之后的优先级默认值205 */
    UCOM_NV_GSM_INTERRAT_GAP_NUM_STRU   stMaxGapNum;                            /* 异系统任务最大可分配沟数目默认值1个 */

}UCOM_NV_GSM_INTERRAT_RANK_AND_GAP_STRU;



/*****************************************************************************
 结构名    : UCOM_NV_GSM_INTERRAT_TASK_RANK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 异系统任务优先级结构
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_INTERRAT_RANK_AND_GAP_STRU  stBchInterratRank;                  /* 空闲态异系统优先级115，115，0，115，分的沟数均为1 */
    UCOM_NV_GSM_INTERRAT_RANK_AND_GAP_STRU  stCsDchInterratRank;                /* cs 专用态异系统任务的优先级结构5,205,30,205,均分5个沟 */
    UCOM_NV_GSM_INTERRAT_RANK_AND_GAP_STRU  stPsDchInterratRank;                /* ps 专用态异系统任务的优先级结构5,205,30,205,均分12个沟 */
}UCOM_NV_GSM_INTERRAT_TASK_RANK_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_NCELL_SHEDULE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 邻区调度参数结构
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_NCELL_TASK_RANK_STRU        stNcellTaskRank;                    /* 邻区任务优先级 */
    UCOM_NV_GSM_INTERRAT_TASK_RANK_STRU     stInterratTaskRank;                 /* 异系统任务优先级 */
}UCOM_NV_GSM_NCELL_SCHEDULE_CFG_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_MEA_RSSI_TO_AGC_GAIN_THD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 邻区调度参数结构
初始配置多伦快速测量模式，若当次测量值<-56dBm，下次配置档位A单轮测量模式，否则下次配置档位B单轮测量模式；
如果当前是档位A单轮测量模式，且当次测量值>-53dBm，下次配置档位B单轮测量模式；
如果当前是档位B单轮测量模式，且当次测量值<-59dBm，下次配置档位A单轮测量模式

*****************************************************************************/
typedef struct
{
    VOS_INT16                       shwThreeModeToAorBGainThd;                  /* 初始配置多伦快速测量模式，若当次测量值<-56dBm，下次配置档位A单轮测量模式，否则下次配置档位B单轮测量模式 */
    VOS_INT16                       shwAGainToBGainThd;                         /* 当前在A档 当次测量值>-53dBm，下次配置档位B单轮测量模式 */
    VOS_INT16                       shwBGainToAGainThd;                         /* 当前是档位B单轮测量模式，且当次测量值<-59dBm，下次配置档位A单轮测量模式 */
    VOS_UINT16                      uhwRssiCompensation;                        /* 单轮测量，RSSI的补充修正值，默认0.75dB */
}UCOM_NV_GSM_MEA_RSSI_TO_AGC_GAIN_THD_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_DSDA_POWER_LIMIT_STRU
 结构说明  : 双卡发射功率限制NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      uhwPowerLmtEnable;                          /* 限制功率开关 */
    VOS_UINT16                      auhwPowerLmtLow[UCOM_NV_G_HIGH_LOW_BUTT];   /* 限制功率最小值，单位0.1dBm */
    VOS_UINT16                      auhwPowerLmtHigh[UCOM_NV_G_HIGH_LOW_BUTT];  /* 限制功率稳态值，单位0.1dBm */
    VOS_UINT16                      auhwPowerLmtMax[UCOM_NV_G_HIGH_LOW_BUTT];   /* 限制功率最大值，单位0.1dBm */
}UCOM_NV_GSM_DSDA_POWER_LIMIT_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_RAMP_DAC_REV_STRU
 结构说明  : 双卡发射功率限制NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      uhwGsmRampDacRev;                           /* gsm爬坡dac是否交叉,0:不交叉,1:交叉 */
}UCOM_NV_GSM_RAMP_DAC_REV_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_ANT_TUNER_CTRL_INFO_STRU
 结构说明  : 天线调谐的控制结构体,MIPI型tuner,考虑兼容多种型号，提供最多6个控制字
*****************************************************************************/
typedef struct
{
    UCOM_NV_TUNER_SUPPORT_MODE_ENUM_UINT16  enAntTunerMode;                     /* 硬件是否支持天线调谐，0不支持，1支持 */
    UCOM_NV_RFFE_CTRL_ENUM_UINT16           enAntTunerCtrlType;                 /* 天线调谐是通过MIPI控制还是GPIO,0表示GPIO,1表示MIPI */
    UCOM_NV_GSM_TUNER_GPIO_MASK_STRU        stTunerGpioMask;
    UCOM_NV_MIPI_COMM_STRU                  stTunerActiveReg;                   /* tuner的公共初始化控制字，用于一些寄存器只需要模式加载配置一次 */
    UCOM_NV_MIPI_COMM_STRU                  stTunerIdleReg;                     /* 配置tuner为IDLE态或低功耗态的控制字 */
} UCOM_NV_G_ANT_TUNER_CTRL_INFO_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_EXT_LNA_MIPI_WORD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : mipi lna 控制字
*****************************************************************************/
typedef struct
{
    VOS_UINT32                               uwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU                    astLnaMipiCmd[UCOM_NV_G_LNA_MIPI_CMD_MAX_NUM];
    UCOM_NV_MIPI_BYTE_DATA_STRU              astLnaMipiData[UCOM_NV_G_LNA_MIPI_DATA_MAX_NUM];
}UCOM_NV_GSM_EXT_LNA_MIPI_WORD_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_EXT_LNA_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : EXT LNA INFO
*****************************************************************************/
typedef struct
{
    VOS_UINT32                               uwGpioEnable;                              /* GPIO使能信号 */
    VOS_UINT32                               uwLnaGpioNumber;                           /* 支持的档位数*/
    VOS_UINT32                               auwLnaGpio[UCOM_NV_G_LNA_GPIO_STEP_NUM];   /* 4档LNA GPIO的配置 */
    VOS_UINT32                               uwLnaGpioMask;                             /* 使用的LNA GPIO的掩码 */
    VOS_UINT32                               uwMipiEnable;                              /* MIPI使能信号*/
    VOS_UINT32                               uwLnaMipiNumber;                           /* 支持的档位数*/
    UCOM_NV_GSM_EXT_LNA_MIPI_WORD_STRU       astLnaMipi[UCOM_NV_G_LNA_MIPI_STEP_NUM];   /* MIPI LNA 配置 */
    UCOM_NV_GSM_EXT_LNA_MIPI_WORD_STRU       stLnaOff;                                  /* LNA 关闭配置*/
    VOS_UINT32                               auwGainIndex[UCOM_NV_G_LNA_GAIN_INDEX_NUM];/* BLOCK下AGC档位的lna增益索引*/
}UCOM_NV_GSM_EXT_LNA_INFO_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_EXT_LNA_COMMON_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : EXT LNA COMMON INFO
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_EXT_LNA_INFO_STRU              stMainLnaInfo;       /* 主集mipi lna 信息 */
    UCOM_NV_GSM_EXT_LNA_INFO_STRU              stDivLnaInfo;        /* 分集mipi lna 信息  */
}UCOM_NV_GSM_EXT_LNA_COMMON_INFO_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_EXT_LNA_AGC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 外置LNA的AGC配置信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwAgcCtrlEnable;        /* LNA 打开的时候，是否支持AGC档位切换 */
    UCOM_NV_GSM_RX_AGC_CTRL_STRU                stAgcCtrlWord;          /* LNA ON的时候使用的AGC增益控制字 */
}UCOM_NV_GSM_RX_AGC_CTRL_EXT_LNA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_EXT_LNA_AGC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 外置LNA的AGC配置信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                   uwAgcThrdEnable;   /* LNA 打开的时候，是否配置AGC档位切换门限 */
    UCOM_NV_GSM_AGC_SWITCH_THRESHOLD_STRU        stAgcThresholdAb; /* LNA ON的时候使用的AGC切换门限 */
}UCOM_NV_GSM_RX_AGC_SWITCH_THRD_EXT_LNA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_ANT_TUNER_CTRL_PARA_STRU
 结构说明  : 天线调谐码字信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwCodeSearchStep;                  /* 调谐时码字搜索步长 */
    VOS_UINT16                              uhwBypassMaxCode;                   /* Bypass时的最大码字，例RF1108为0x40 */
    VOS_UINT16                              uhwBypassMinCode;                   /* Bypass时的最小码字，例RF1108为0x5F */
    VOS_UINT16                              uhwUpperCode;                       /* 天线调谐码字上限，例RF1108为0 */
    VOS_UINT16                              uhwLowerCode;                       /* 天线调谐码字下限，例RF1108为31 */
    VOS_UINT16                              auhwReserve[3];                     /* 不确定码字格式和大小，先保留 */
} UCOM_NV_W_ANT_TUNER_CODE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_CLOSE_LOOP_TUNER_PARA_STRU
 结构说明  : 闭环tuner参数结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwBandSupport;                      /* 对应bit为1表示这个band支持动态天线调谐,否则不支持 */
    VOS_UINT32                              uwBandExten;                        /* 以后band ID可能超出32 */
    VOS_UINT16                              uhwActiveTime;                      /* 天线调谐配置提前帧头配置量，当上行打开后，WBBP每次在帧头提前cpu_tx_sw_active_time进行配置，单位为chip */
    VOS_UINT16                              uhwSampleTime;                      /* 天线调谐平均检测次数,默认配置为4 */
    VOS_UINT16                              uhwDelayFrame;                      /* 完成一轮调谐后的等待时间，单位帧 */
    VOS_UINT16                              uhwEchoLossThreshold;               /* 天线调谐回波损耗门限,精度0.1dBm */
    VOS_UINT32                              uwForWardGpioWord;                  /* 驻波检测前向配置 */
    VOS_UINT32                              uwReverseGpioWord;                  /* 驻波检测反向配置 */
    UCOM_NV_MIPI_CMD_STRU                   stTunerMipiCmd;                     /* MIPI控制字 */
    VOS_UINT16                              uhwReserved;                        /* 保留 */
    UCOM_NV_W_ANT_TUNER_CODE_STRU           stAntTunerCode;                     /* 天线调谐码字信息 */
} UCOM_NV_W_CLOSE_LOOP_TUNER_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_ANT_TUNER_CTRL_INFO_STRU
 结构说明  : 天线调谐的控制结构体,MIPI型tuner,考虑兼容多种型号，提供最多6个控制字
*****************************************************************************/
typedef struct
{
    UCOM_NV_TUNER_SUPPORT_MODE_ENUM_UINT16  enAntTunerMode;                     /* 0:硬件不支持，1:支持开环，2:支持AP+Sensor, 3:支持动态调谐 */
    UCOM_NV_RFFE_CTRL_ENUM_UINT16           enAntTunerCtrlType;                 /* 天线调谐是通过MIPI控制还是GPIO,0表示GPIO,1表示MIPI */
    UCOM_NV_MIPI_COMM_STRU                  stTunerActiveReg;                   /* tuner的公共初始化控制字，用于一些寄存器只需要模式加载配置一次 */
    UCOM_NV_MIPI_COMM_STRU                  stTunerIdleReg;                     /* 配置tuner为IDLE态或低功耗态的控制字 */
    UCOM_NV_W_CLOSE_LOOP_TUNER_PARA_STRU    stCloseLoopTunerCtrl;               /* 闭环tuner参数 */
} UCOM_NV_W_ANT_TUNER_CTRL_INFO_STRU;

typedef UCOM_NV_W_ANT_TUNER_CTRL_INFO_STRU UCOM_NV_CDMA_ANT_TUNER_CTRL_INFO_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_RF_DIV_BAND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 是否支持分集
*****************************************************************************/
typedef struct
{
    VOS_UINT32          uwWBand;
    VOS_UINT32          uwWbandExtRsv;
}UCOM_NV_W_RF_DIV_BAND_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_RF_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RF 控制结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwBand;                                /* 该值表示W的BAND或者G模的BAND标识 */
    VOS_UINT16                          uhwRfChannel;                           /* RF所在的通道 */
    VOS_UINT32                          uwAntSwitch;                        /* 天线1的开关值 */
    VOS_UINT32                          uwOtherSwitch;                          /* 其它天线开关值 */
    VOS_UINT32                          uwPaControlWord;                        /* W模PA使能 */
}UCOM_NV_RF_CONFIG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_BAND_RF_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :2.1表示支持的3G和2G频段、3G分集支持情况、每个频段与RF
            通道对应关系天线开关切换选择、DBB对3GPA的控制
*****************************************************************************/
typedef struct
{
    UCOM_NV_RF_CONFIG_STRU              stRxMainRfBandCofig;                    /* 包括了2G和3G的所有频道 */

    UCOM_NV_RF_CONFIG_STRU              stRxDvtyRfBandCofig;                    /* 包括了2G和3G的所有频道 */

    UCOM_NV_RF_CONFIG_STRU              stTxRfBandCofig;                        /* 包括了2G和3G的所有频道 */
}UCOM_NV_W_BAND_RF_CONFIG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_WG_RF_BAND_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :2.1表示支持的3G和2G频段、3G分集支持情况、每个频段与RF
            通道对应关系天线开关切换选择、DBB对3GPA的控制
*****************************************************************************/
typedef struct
{
    UCOM_NV_RF_CONFIG_STRU              astGsmRxRfBandConfig[UCOM_NV_G_BAND_NUMBER];        /* 包括了2G RX 所有频段 */

    UCOM_NV_RF_CONFIG_STRU              astGsmTxRfBandConfig[UCOM_NV_G_BAND_NUMBER];        /* 包括了2G TX 频段 */

    UCOM_NV_W_BAND_RF_CONFIG_STRU       astWcdmaRfBandConfig[UCOM_NV_W_TOTAL_BAND_NUM];     /* 包括了3G 频段 */
}UCOM_NV_WG_RF_BAND_CONFIG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_EXT_RF_BAND_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W扩展band config
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_BAND_RF_CONFIG_STRU       astWcdmaRfBandConfig[UCOM_NV_W_RF_BAND_CONFIG_NUM];     /* 包括了3G 频段 */
}UCOM_NV_W_RF_BAND_CONFIG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_RF_INIT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RF初始化结果
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwRfAddr;
    VOS_UINT16          uhwRfAddrValue;
}UCOM_NV_RF_INIT_INFO_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_RF_INIT_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RF初始化结果
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwRfCount;
    UCOM_NV_RF_INIT_INFO_STRU               stConfigInfo[UCOM_NV_RFABB_INIT_REG_NUM];
}UCOM_NV_RF_INIT_CONFIG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_RF_INIT_CONFIG_NEW_RAM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RF初始化结果
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwRfCount;
    UCOM_NV_RF_INIT_INFO_STRU               stConfigInfo[UCOM_NV_RFABB_INIT_REG_NEW_RAM_NUM];
}UCOM_NV_RF_INIT_CONFIG_NEW_RAM_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_PHY_SW_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 解决前端差异性的NV项。这里是时钟类的属性
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          stDrxTSysclk;
    VOS_UINT16                          uhwWcdmaIp2DataWidth;       /* W IP2的位宽,0:12bit,1:14bit */
    VOS_UINT16                          uhwReservedWord;            /* 保留用于以后自行扩展 */
    VOS_UINT32                          uwReservedWords[6];         /* 保留用于以后自行扩展 */
} UCOM_NV_PHY_SW_CFG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_WG_MMMB_PA_SEL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MIPI新增NV项,PA控制模式
*****************************************************************************/
typedef struct
{
    VOS_UINT32          uwWBand;
    VOS_UINT32          uwWbandExtRsv;
    VOS_UINT32          uwGeBand;
}UCOM_NV_WG_MMMB_PA_SEL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_ANT_SWITCH_CONTROL_MODE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MIPI新增NV项,天线控制模式
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwWcdmaBandMainAnt;                    /* [0]-BAND1;[1]-BAND2;以此类推 */
    VOS_UINT32                          uwWcdmaBandDvtyAnt;                    /* [0]-BAND1;[1]-BAND2;以此类推 */
    VOS_UINT32                          uwWbandExtRsv;                        /* [0]-GSM450;[1]-GSM480;... */
    VOS_UINT32                          uwWbandExtRsv2;                        /* [0]-GSM450;[1]-GSM480;... */
    VOS_UINT32                          uwGsmBandRxAnt;                        /* [0]-GSM450;[1]-GSM480;... */
    VOS_UINT32                          uwGsmBandTxAnt;                        /* [0]-GSM450;[1]-GSM480;... */
}UCOM_NV_ANT_SWITCH_CONTROL_MODE_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_WG_DRX_RESUME_TIME_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : WG DRX 睡眠唤醒ABB、RF等外设稳定和软件恢复时间
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwAbbPwrRsmTime;                        /* ABB AD/DA数字部分电源稳定时间,单位us */
    VOS_UINT32                          uwRfPwrRsmTime;                         /* RF 模拟域电源稳定时间,单位us */
    VOS_UINT32                          uwAntSwitchPwrRsmTime;                  /* 天线开关电源稳定时间,单位us */
    VOS_UINT32                          uwAbbWpllRsmTime;                       /* ABB WPLL稳定时间,单位us */
    VOS_UINT32                          uwAbbGpllRsmTime;                       /* ABB GPLL稳定时间 ,单位us*/
    VOS_UINT32                          uwBbpPllRsmTime;                        /* SOC BBP PLL稳定时间,单位us */
    VOS_UINT32                          uwPaStarRsmTime;                            /* 保留字段 */
    VOS_UINT32                          uwSysProtectTime;                       /* 系统恢复保护时间 */

    VOS_UINT32                          uwTcxoRsmTime;                          /* TCXO稳定时间,单位us */
    VOS_UINT32                          uwDcxoRsmTime;                          /* DCXO稳定时间,单位us */
    VOS_UINT32                          uwSlowToMcpuRsmTime;                    /* 从SLOW到MCPU上电恢复时间,单位us */
    VOS_UINT32                          uwWphyRsmTime;                          /* W物理层唤醒恢复时间,单位us */
    VOS_UINT32                          uwGphyRsmTime;                          /* G物理层唤醒恢复时间,单位us */
    VOS_UINT32                          uwTaskSwitchTime;                       /* 操作系统任务切换时间,单位us */
    VOS_UINT32                          uwPaPwrRsmTime;                         /* PA电源稳定时间,单位us */
}UCOM_NV_WG_DRX_RESUME_TIME_STRU;



/*****************************************************************************
 结构名    : UCOM_NV_WG_DRX_ADVANCE_TIME_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : WG DRX 提前唤醒量,根据待机个数取不同的数据.
             替换上面NV项
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwMcuTcxoRsumeTime;
    VOS_UINT32                          uwMcuDcxoRsumeTime;
    VOS_UINT32                          uwModemRsumeTime;
    VOS_UINT16                          auhwOamAdvanceTime[2][4];                  /* DSDA 下标0/DSDS 1:OAM模式提前量:m0/m1/m2,单位us */
    VOS_UINT16                          auhwGphyAdvanceTime[2][4];                 /* DSDA 下标0/DSDS 1:GSM模式提前量:m0/m1/m2,单位us */
    VOS_UINT16                          auhwWphyAdvanceTime[2][4];                 /* DSDA 下标0/DSDS 1:WCDMA模式提前量:m0/m1/m2,单位us */
}UCOM_NV_WG_DRX_ADVANCE_TIME_STRU;



/*****************************************************************************
 结构名    : UCOM_NV_SUPPORT_RATMODE_MASK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : modem支持的所有模式信息
             bit0:是否支持GSM;
             bit1:是否支持WCDMA;
             bit2:是否支持LTE;
             bit3:是否支持TDS;
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSupportRatMask;                      /* Modem支持的所有mode信息 */
}UCOM_NV_SUPPORT_RATMODE_MASK_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_PA_DEFAULT_VOLT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PA默认电压值,电压单位:1mV
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwWcdmaPaVolt;                         /* WCDMA PA默认电压 */
    VOS_UINT16                          uhwGsmPaVolt;                           /* GSM PA默认电压 */
}UCOM_NV_PA_DEFAULT_VOLT_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_WG_ABB_PLL_STABLE_TIME_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PLL稳定时间,稳定时间单位:1us
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwWcdmaPllStableTime;                  /* WCDMA PLL稳定时间 */
    VOS_UINT16                          uhwGsmPllStableTime;                    /* GSM PLL稳定时间 */
}UCOM_NV_WG_ABB_PLL_STABLE_TIME_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_RCM_PARA_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RCM新增NV项
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwTimingCalThld;                    /* 时钟校准门限 */
    VOS_UINT16                              uhwReserved1;
    VOS_UINT16                              uhwReserved2;
    VOS_UINT16                              uhwReserved3;
    VOS_UINT16                              uhwReserved4;
    VOS_UINT16                              uhwReserved5;
}UCOM_NV_RCM_PARA_CONFIG_STRU;

/*****************************************************************************
结构名    : UCOM_NV_RCM_RF_SHARE_CFG_STRU
结构说明  : UCOM_NV_RCM_RF_SHARE_CFG_STRU对应的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSupportFlag;      /*Range:[0,1]*//* 功能是否支持标记 */
    VOS_UINT16                          usGSMRFID;          /* GSM接入模式RFID信息 */
    VOS_UINT16                          usWCDMARFID;        /* WCDMA接入模式RFID信息 */
    VOS_UINT16                          usTDSRFID;          /* TD-SCDMA接入模式RFID信息 */
    VOS_UINT16                          usLTERFID;          /* LTE接入模式RFID信息 */
    VOS_UINT16                          usCDMARFID;         /* CMDA接入模式RFID信息 */
    VOS_UINT16                          usEVDORFID;         /* CDMA EVDO接入模式RFID信息 */
    VOS_UINT16                          usReserved;
} UCOM_NV_RCM_RF_SHARE_CFG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_RCM_TEST_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RCM测试需求
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwRcmTestCtrl;                          /* RCM测试需求
                                                                                   BIT0表示在测试卡场景是否强制打开TAS,
                                                                                   BIT1表示环回模式启动是否强制打开TAS */

    VOS_UINT32                          uwResvered;                             /* 保留 */
}UCOM_NV_RCM_TEST_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_SVLTE_SUPPORT_FLAG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SVLTE配置,结构参见SVLTE_SUPPORT_FLAG_STRU,ID=60.文件为"NasNvInterface.h"
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwSvLte;
}UCOM_NV_SVLTE_SUPPORT_FLAG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_TAS_FUNC_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RCM新增NV项 uhwTasFuncEnable
             bit0: 0 - TAS Disabled
                   1 - TAS Enabled
             bit1: 0 - MAS Disabled
                   1 - MAS Enabled,仅在bit0=1时才允许设置1
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwTasFuncEnable;                       /* TAS/MAS功能是否有效 */
}UCOM_NV_TAS_FUNC_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_RCM_TAS_TABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RCM新增NV项
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  uhwTasChoiceData[UCOM_NV_RCM_TAS_TABLE_NUM];    /* TAS切换抉择表 */
    VOS_UINT32                  uwTasScoreData[UCOM_NV_RCM_TAS_TABLE_NUM];      /* TAS状态计分表 */
}UCOM_NV_RCM_TAS_TABLE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_RCM_TAS_TABLE_TRI_MODEM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 天际通TAS新增NV项
*****************************************************************************/
typedef UCOM_NV_RCM_TAS_TABLE_STRU  UCOM_NV_RCM_TAS_TABLE_TRI_MODEM_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_RCM_TAS_CDMA_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RCM新增NV项，用于控制连接态下CDMA天线切换调度
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwCompareNum[UCOM_NV_RCM_AGENTC_COMPARE_PHASE_BUTT];      /* 采样个数,测量报告个数 */
    VOS_UINT16                          auhwDeltaAveRxAGC[UCOM_NV_RCM_AGENTC_COMPARE_PHASE_BUTT];   /* 差值门限,单位dB */
    VOS_UINT16                          auhwFrozenNum[UCOM_NV_RCM_AGENTC_COMPARE_PHASE_BUTT];       /* 冻结时间乘数，冻结时间=num*1X测量上报周期 */
    VOS_UINT16                          uhwFinalFrozenNum;                                          /* 比较三个子阶段都不满足异常保护时间乘数 */
    VOS_UINT16                          uhwSPassThreshold;                                          /* SPass次数门限 */
    VOS_UINT16                          uhwSFailThreshold;                                          /* SFail次数门限 */
}UCOM_NV_RCM_TAS_CDMA_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GUPHY_FUNC_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : v7r1c50 低功耗控制结构16位
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  CsOnlyAntCtrl           :1;                     /* CS ONLY关分集控制 */
    VOS_UINT16                  ScAbbCtrl               :1;                     /* SC ABB控制 */
    VOS_UINT16                  AbbCtrl                 :1;                     /* CS ONLY abb控制 */
    VOS_UINT16                  RficRegCtrl             :1;                     /* CS ONLY RF调寄存器控制 */
    VOS_UINT16                  RficVolCtrl             :1;                     /* CS ONLY RF调电压控制 */
    VOS_UINT16                  GudspPowerDownCtrl      :1;                     /* GU 从模下电控制 */
    VOS_UINT16                  SimpleSlotIntCtrl       :1;                     /* W 精简时隙控制 */
    VOS_UINT16                  LoopRfLowpowerCtrl      :1;                     /* 环回允许RF低功耗控制 1允许 0不允许，默认不允许 */

    VOS_UINT16                  LoopRxAnt2Ctrl          :1;                     /* 环回允许rx动态分集控制 1允许 0不允许，默认不允许 */
    VOS_UINT16                  PsR99RxAnt2Ctrl         :1;                     /* ps r99 rx关分集控制 DCM需求*/
    VOS_UINT16                  PsRxAnt2Ctrl            :1;                     /* ps R99和DPA rx关分集控制为1相当于动态分集相关代码全部关闭 */
    VOS_UINT16                  PsVoltLPCtrl            :1;                     /* PS 调压低功耗特性代码控制位, 1打开 0不打开，默认打开 */
    VOS_UINT16                  PsCsAntCtrl             :1;                     /* PS CS并发下关分集控制 */
    VOS_UINT16                  reserved                :1;
    VOS_UINT16                  DpaOpenIpc              :1;                     /* dpa业务下E5776、860产品形态打开IPC中断开关控制，默认不打开 */
    VOS_UINT16                  GphyCsInterferennceCtrl :1;                     /* GSM CS同频干扰掉话问题规避方案控制:1-表示打开该功能,否则表示关闭 */
}UCOM_NV_GUPHY_FUNC_CTRL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_WG_TEMPPROTECT_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwTempTypeId;                          /* 0-13 */
    VOS_UINT16                          uhwCloseAnt2Flag;                       /* 温保是否开关分集 */
    VOS_INT16                           shwCloseAnt2TempThresh;                 /* 高温关闭分集门限 */
    VOS_INT16                           shwOpenAnt2TempThresh;                  /* 低温打开分集门限 */
    VOS_UINT16                          uhwMaxPowLimitFlag;                     /* 温保是否限制最大发射功率 */
    VOS_INT16                           shwMaxPowLimitAlarmThresh;              /* 温保限制最大发射功率,高温门限 */
    VOS_INT16                           shwMaxPowLimitResumeThresh;             /* 温保限制最大发射功率,恢复门限 */
    VOS_INT16                           shwWMaxPowLimitValue;                   /* 温保限制W最大发射功率 */
    VOS_INT16                           shwGMaxPowLimitValue;                   /* 温保限制G最大发射功率 */
}UCOM_NV_WG_TEMPPROTECT_CTRL_STRU;

/* xiongjiangjiang Edn */

/*****************************************************************************
 结构名    : UCOM_NV_W_RF_RX_BIAS_DELTA_GAIN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RF RX DELTA GAIN
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwTxChanDelay;
}UCOM_NV_W_RF_TX_CHAN_DELAY_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_ANT_PERFORM_TEST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwAntPerformanceTest;
}UCOM_NV_W_ANT_PERFORM_TEST_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_CQI_ANT2_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwCQICtrlFlag;
    VOS_UINT16                          uhwCQIThresh1;                          /* CQI高门限 */
    VOS_UINT16                          uhwCQIThresh2;                          /* CQI低门限 */
    VOS_UINT16                          uhwCQITime1;                            /* CQI高于高门限关分集延迟时间 */
    VOS_UINT16                          uhwCQITime2;                            /* CQI低于低门限开分集延迟时间 */
}UCOM_NV_W_CQI_ANT2_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_UL_RF_GATE0_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwUlRfGate0;
}UCOM_NV_W_UL_RF_GATE0_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_UL_RF_GATE1_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwUlRfGate1;
}UCOM_NV_W_UL_RF_GATE1_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_PA_INIT_DELAY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwPaInitDelay;
}UCOM_NV_W_PA_INIT_DELAY_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_PA_OFF_DELAY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwPaOffDelay;
}UCOM_NV_W_PA_OFF_DELAY_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_INIT_DELAY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwTxInitDelay;
}UCOM_NV_W_TX_INIT_DELAY_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_OFF_DELAY_STRUS
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwTxOffDelay;
}UCOM_NV_W_TX_OFF_DELAY_STRUS;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_IDLE_ONE_DELAY_STRUS
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwTxIdleOnDelay;
}UCOM_NV_W_TX_IDLE_ONE_DELAY_STRUS;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_IDLE_OFF_DELAY_STRUS
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwTxIdleOffDelay;
}UCOM_NV_W_TX_IDLE_OFF_DELAY_STRUS;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_ABB_INIT_DELAY_STRUS
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwTxAbbInitDelay;
}UCOM_NV_W_TX_ABB_INIT_DELAY_STRUS;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_ABB_OFF_DELAY_STRUS
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwTxAbbOffDelay;
}UCOM_NV_W_TX_ABB_OFF_DELAY_STRUS;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_GAIN_CTRL_TIMING_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          shwTxGainOpenTime;                      /* 提前打开上行RF增益的chip数 */
}UCOM_NV_W_TX_GAIN_CTRL_TIMING_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_DRX_CS_PERIOD_MEAS_CLASS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 影响小区搜索周期的测量等级因子
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwClass1Factor;                        /* 除以下两种情况外的其它所有 */
    VOS_UINT16                          uhwClass2Factor;                        /* 满足测量下移准则，且只有本频或异频 */
    VOS_UINT16                          uhwClass3Factor;                        /* 只有主小区测量 */
    VOS_UINT16                          uhwRsv;
}UCOM_NV_W_DRX_CS_PERIOD_MEAS_CLASS_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_DRX_MEAS_CORR_LENTH_MEAS_CALSS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 影响测量相关长度的测量等级因子
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwClass1Factor;                        /* 除以下两种情况外的其它所有 */
    VOS_UINT16                          uhwClass2Factor;                        /* 满足测量下移准则，且只有本频或异频 */
    VOS_UINT16                          uhwClass3Factor;                        /* 只有主小区测量 */
    VOS_UINT16                          uhwRsv;
}UCOM_NV_W_DRX_MEAS_CORR_LENTH_MEAS_CALSS_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_DRX_STRONG_CELL_CTRL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 强邻区控制信息
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwIntraStrongCellNum;                  /* 本频强邻区个数 */
    VOS_UINT16                          uhwIntraMeasReserveCellNum;             /* 每次本频测量保留的强小区个数 */
    VOS_UINT16                          uhwInterStrongCellNum;                  /* 异频强邻区个数 */
    VOS_UINT16                          uhwInterMeasReserveCellNum;             /* 每次异频测量保留的强小区个数 */
}UCOM_NV_W_DRX_STRONG_CELL_CTRL_INFO_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_DRX_CTRL_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwDrxMaxCsPeriodLenth;                 /* DRX态下最大的小区搜索周期 */
    VOS_UINT16                          uhwDrxMinMeasCorrLenth;                 /* DRX态下最小的测量相关长度 */
    VOS_UINT16                          uhwDrxMaxMeasCorrLenth;                 /* DRX态下最大的测量相关长度 */
    VOS_UINT16                          uhwDrxMaxCsStep1Lenth;                  /* DRX态下最大的小区搜索step1长度 */
    VOS_UINT16                          uhwDrxMinCsStep1Lenth;                  /* DRX态下最小的小区搜索step1长度 */
    VOS_UINT16                          uhwRsv;
    UCOM_NV_W_DRX_CS_PERIOD_MEAS_CLASS_STRU         stDrxCsPeriodMeasClass;         /* 影响小区搜索周期的测量等级因子 */
    UCOM_NV_W_DRX_MEAS_CORR_LENTH_MEAS_CALSS_STRU   stDrxMeasCorrLenthMeasClass;    /* 影响测量相关长度的测量等级因子 */
    UCOM_NV_W_DRX_STRONG_CELL_CTRL_INFO_STRU        stDrxStrongCellCtrlInfo;        /* 强邻区控制信息 */
}UCOM_NV_W_DRX_CTRL_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_CQI_CORRECT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwCqiCorrectEnable;                     /* CQI动态补偿使能开关,0 关闭；1 打开 */
    VOS_UINT32                          uwSblerHighThreshold;                   /* SBLER 高控制门限,单位0.01 */
    VOS_UINT32                          uwSblerLowThreshold;                    /* SBLER 低控制门限,单位0.01 */
    VOS_UINT32                          uwScheduleRateThreshold;                /* 调度率控制门限,单位0.01 */
}UCOM_NV_W_CQI_CORRECT_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_PSCH_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwPschLen;                             /* PSCH搜索的相干长度 */
    VOS_UINT16                          uhwPschThd;                             /* PSCH搜索的噪声门限 */
}UCOM_NV_W_PSCH_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TOTOLPC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwOpenTotolpcFlg;                  /* 是否启动Tot Olpc算法标志，默认值1 */
    VOS_UINT16                              uhwOutageProbability;               /* Totolpc算法中的参数，默认值15*/
    VOS_UINT16                              uhwSirErrorStep;                    /* Totolpc算法中的参数，默认值1*/
    VOS_UINT16                              uhwCorrectionFactor;                /* Totolpc算法中的参数，默认值10*/
    VOS_UINT16                              uhwSirOutageOffset;                 /* Totolpc算法中的参数，默认值0*/
    VOS_INT16                               shwOutageIncrementThresUp;          /*TOT OLPC算法中的参数OutageIncrementThresholdUp，默认值26*/
    VOS_INT16                               shwOutageIncrementThresDown;        /*TOT OLPC算法中的参数OutageIncrementThresholdDown，默认值-19*/
    VOS_INT16                               shwOutagetargetStepUp;              /*TOT OLPC算法中的参数OutagetargetStepUp，默认值10*/
    VOS_INT16                               shwOutagetargetStepDown;            /*TOT OLPC算法中的参数OutagetargetStepDown，默认值-10*/
    VOS_INT16                               shwReserve;                             /*保留位，默认值0*/
} UCOM_NV_W_TOTOLPC_STRU;

/*****************************************************************************
 枚举名    : UCOM_NV_W_CPC_DRX_STRU
 协议表格  :
 枚举说明  :CPC DRX项目使用的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRfWorkMode;                          /* RF进入低功耗状态时，进入Idle态还是进入StandBy态*/
    VOS_UINT16                          uhwCpcDrxCtrlFlag;                      /* 控制CPC DRX相关功能开关的标志*/
}UCOM_NV_W_CPC_DRX_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RX_IP2_CAL_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :IP2校准门限,主集分集共用同一个结构
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwIp2TxRefPower;                  /* 校准时上行通道的功率，单位为0.1dbm */
    VOS_INT16                           shwReserved;                       /* 暂不使用，保留 */
}UCOM_NV_W_RX_IP2_CAL_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_IQ_MISMATCH_CAL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :TX IQ MISMATCH校准初始功率和门限
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTxIqMismatch2RefPower;           /* 校准时上行通道的功率，单位为0.1dbm */
    VOS_INT16                           shwAmpCorrThreshold;                /* 校准后IMD2的门限，单位db */
    VOS_INT16                           shwDcCorrThreshold;                 /* 校准后IMD2的门限，单位db */
}UCOM_NV_W_TX_IQ_MISMATCH_CAL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_RSSI_ARITHMETIC_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwRssiArithmeticPara;
}UCOM_NV_W_RSSI_ARITHMETIC_PARA_STRU;



/*****************************************************************************
 结构名    : UCOM_NV_W_TX_PA_APT_ENABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwWBand;                      /* bit位是1代表支持APT */
    VOS_UINT32                          uwWBandExtRsv;                /* bit位是1代表支持APT */
}UCOM_NV_W_TX_PA_APT_ENABLE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_EEIC_EN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwEEICEn;
}UCOM_NV_W_EEIC_EN_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_IPS_FLG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwIpsFlg;
}UCOM_NV_W_IPS_FLG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RX_SPUR_REMOVE_ALG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 谐波消除算法
*****************************************************************************/
typedef struct
{
    UCOM_NV_WCDMA_SPUR_TYPE_ENUM_UINT16 enSpurType;                             /* 谐波点类型 */
    VOS_UINT16                          uhwMainRemoveEnable;                    /* 主集使能 */
    VOS_UINT16                          uhwDivRemoveEnable;                     /* 分集使能 */
    VOS_INT16                           shwRssiThreshold;                       /* 启动谐波消除算法的rssi门限 */
    VOS_UINT16                          uhwFilterCoeff;                         /* 滤波因子 */
}UCOM_NV_W_RX_SPUR_REMOVE_ALG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RF_M_VALUE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              auhwRfMValue[2];                    /* 0: usRfScMDaValue 1:usRfDcMDaValue */
}UCOM_NV_W_RF_M_VALUE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_LOWPOWER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W低功耗特性所需门限以及开关
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwAllocToUseExtraMpUnit;       /* 允许使用10~19单元,范围 [0,1] ,推荐 0 */
    VOS_UINT16                          uhwAllocToUseExtraMpUnitInCPC;  /* CPC 允许使用10~15单元,范围 [0,1],推荐 1 */
    VOS_UINT16                          uhwIntraFMSRUsing5msPerFrEn;    /* 本频5ms方案, 范围 [0,1]，推荐 1 */

    /* 关闭 EEIC */
    VOS_UINT16                          uhwThrptUppLmtPerCrNMThd;       /* 范围0~2000,精度1(100Kbps),推荐 130 */
    VOS_UINT16                          uhwThrptUppLmtPerCrNonMimoEn;   /* 范围[0,1],推荐 1 */

    /* 关闭分集 */
    VOS_UINT16                          uhwCorrCoefAccFrm;              /* 比较统计帧数，单位10帧，范围0~1024,推荐 10 */
    VOS_UINT32                          uwCorrCoefShutDownThd;          /* 关闭门限，为原值平方后放大10000倍,范围0~1000000,默认 400, */
    VOS_UINT16                          uhwAntRssiShutDownThd;          /* 关闭门限，单位1dBm，范围0~100，推荐20 推荐 10 */
    VOS_UINT16                          uhwCorrCoefCalEn;               /* 范围[0,1],推荐 1 */
    VOS_UINT16                          uhwAntRssiCmprEn;               /* 范围[0,1],推荐 1 */
    VOS_UINT16                          uhwAntRssiCmprAccFrm;           /* 范围0~1024, 推荐 10 */
    VOS_UINT16                          uhwCorrCoefReCalDelayFrm;       /* 范围0~1024, 推荐 10 */
    VOS_UINT16                          uhwAntRssiReOpenDelayFrm;       /* 范围0~1024, 推荐 10 */

    /* Wd静态信道按时隙更新 */
    VOS_UINT16                          uhwWdCalPerSlotEn;              /* 范围 [0,1],    推荐 1 */
    VOS_UINT16                          uhwWdCalPerSlotThd;             /* 范围0~511,   推荐 251 */

}UCOM_NV_W_LOWPOWER_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_PA_ENABLE_SELECT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : w pa en 4线选择
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwLineSel[UCOM_NV_WCDMA_PA_EN_LINE_NUM];
}UCOM_NV_W_PA_ENABLE_SELECT_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_HSUPA_MAX_POWER_TEST_MODE_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA最大发射功率测试模式控制
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEnableFlag;
    VOS_UINT16                          auhwMinSetEtfci[UCOM_NV_HSUPA_ETFCI_TABLE_MAX_NUM];
}UCOM_NV_W_HSUPA_MAX_POWER_TEST_MODE_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_HDET_TIMING_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 功率检测中使用的NV项结构
*****************************************************************************/
typedef struct
{
    VOS_INT16                              shwPaStableTiming;                   /* 发射功率变化后，RF与PA的稳定时间，单位为chip*/
    VOS_INT16                              shwPdHkadcChanSelTiming;             /*授权有效到发送HKADC通道控制字时刻间隔，单位为chip*/
    VOS_INT16                              shwPdStartInterval;                  /* ABB从bypass为低到启动start（ABB开始转换）的时间间隔，单位为chip*/
    VOS_INT16                              shwPdInterval;                       /* 两次功率检测之间的时间间隔，单位为chip*/
    VOS_INT16                              shwPdsampleTiming;                   /* HKADC采样信号处理时间，单位为chip*/
    VOS_INT16                              shwDcOffsetSampleNum;                /*WHKADC上行每个时隙进行dc offset检测的次数*/
    VOS_INT16                              shwPdSampleNum;                      /*W上行每个时隙进行PD检测的次数*/
} UCOM_NV_W_HDET_TIMING_CONFIG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_TEMP_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 表示每档RF Gain对应的温度补偿值
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwTempComp[UCOM_NV_W_TX_TEMP_COMP_NUM];       /* 表示某一档RF Gain在16个采样温度下的温度补偿值，单位为0.1dB */
}UCOM_NV_W_TX_TEMP_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_RF_GAIN_TEMP_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 表示15档RF Gain对应的温度补偿值
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwValidCount;                                   /* 有效的档位数 */
    UCOM_NV_W_TX_TEMP_COMP_STRU         astTempComp[UCOM_NV_W_TX_RF_GAIN_CTRL_NUM];     /* 表示15档RF Gain在16个采样温度下的温度补偿值 */
}UCOM_NV_W_TX_RF_GAIN_TEMP_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_VOICE_APC_SIG_ENABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwVoiceApcSigEnable;               /* 表示在信令模式下是否激活Voice模式的APC表 */
}UCOM_NV_W_VOICE_APC_SIG_ENABLE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_VOICE_APC_CAL_ENABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwVoiceApcCalEnable;               /* 表示在校准模式下是否校准Voice模式的APC表 */
}UCOM_NV_W_VOICE_APC_CAL_ENABLE_STRU;

/*****************************************************************************
 枚举名    : UCOM_NV_W_RX_AGC_GAIN_VALID_COUNT_STRU
 协议表格  :
 枚举说明  : AGC档位个数的NV项，包括BLOCK和非BLOCK
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwAgcGainNoBlockNum;                   /* 非Block模式的AGC控制字 */
    VOS_UINT16                          uhwAgcGainBlockNum;                     /* Block模式的AGC控制字 */
}UCOM_NV_W_RX_AGC_GAIN_VALID_COUNT_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_RF_GAIN_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : rf gain ctrl 档位数
*****************************************************************************/
typedef struct
{
    VOS_UINT32          uwValidCount;
    VOS_UINT16          auhwRfGainCtrl[UCOM_W_MAX_RF_GAIN_CTRL_NUM];
}UCOM_NV_W_TX_RF_GAIN_CTRL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_TX_RF_BIAS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : rf BIAS 档位数
*****************************************************************************/
typedef struct
{
    VOS_UINT32          uwValidCount;
    VOS_UINT16          auhwRfBias[UCOM_W_MAX_RF_BIAS_NUM];
}UCOM_NV_W_TX_RF_BIAS_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_BB_GAIN_VS_ATTEN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : BB每个档位对应的衰减值
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwBbGainCtrl;
    VOS_INT16           shwBbAtten10th;
}UCOM_NV_W_BB_GAIN_VS_ATTEN_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_BB_GAIN_TABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : BB的档位数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                             uwValidCount;
    UCOM_NV_W_BB_GAIN_VS_ATTEN_STRU        astBbGain[UCOM_W_MAX_RF_BB_GAIN_NUM];
}UCOM_NV_W_BB_GAIN_TABLE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_ECIOR_CTRL_STRU
 结构说明  : ec/ior的控制结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwCqiLoadSwitchThreshold;          /* CQI切换门限，默认配置为15;*/
    VOS_UINT16                          uhwLoadRateThreshold1;              /* 调度率门限1，默认配置为6;*/
    VOS_UINT16                          uhwLoadRateThreshold2;              /* 调度率门限2，默认配置为10; */
} UCOM_NV_W_ECIOR_CTRL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_RF_VCO_REG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RF VCO REG
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRegAddress;
    VOS_UINT16                          uhwRegValue;
}UCOM_NV_W_RF_VCO_REG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RF_VCO_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RF VCO CONFIG
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwValidCounter;
    UCOM_NV_W_RF_VCO_REG_STRU           astRegConfig[UCOM_NV_MAX_RF_VCO_CONFIG_NUM];
}UCOM_NV_W_RF_VCO_CONFIG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_WCDMA_RF_TX_BIAS_REG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RF TX BIAS
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRegAddress;
    VOS_UINT16                          uhwRegValue;
}UCOM_NV_W_RF_TX_BIAS_REG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RF_TX_BIAS_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RF TX BIAS
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwValidCounter;
    UCOM_NV_W_RF_TX_BIAS_REG_STRU       astBias[UCOM_NV_W_TX_RF_BIAS_NUM];
}UCOM_NV_W_RF_TX_BIAS_CONFIG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RX_RFIC_BIAS_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RF RX BIAS
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwRfRxAbBiasAddress;                                     /* RX AB BIAS地址 */
    VOS_UINT16                              uhwRfRxCdBiasAddress;                                     /* RX CD BIAS地址 */
    VOS_UINT32                              uwReserved;
}UCOM_NV_W_RX_RFIC_BIAS_CFG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RF_RX_BIAS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RF RX BIAS
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwNoBlockStateBias[UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM]; /* no block bias的NV项 */
}UCOM_NV_W_RF_RX_BIAS_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RF_RX_BIAS_DELTA_GAIN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RF RX DELTA GAIN
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwNoBlockStateDeltaGain[UCOM_NV_W_ANT_NUM][UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM]; /* no block delta gain的NV项 */
}UCOM_NV_W_RF_RX_BIAS_DELTA_GAIN_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RX_RFIC_BIAS_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RF RX BIAS
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RF_RX_BIAS_STRU                stRfRxBiasNormalMode;      /* 正常模式下, Rx Bias配置 */
    UCOM_NV_W_RF_RX_BIAS_STRU                stRfRxBiasVoiceMode;       /* VOICE模式下,Rx Bias配置 */
    UCOM_NV_W_RF_RX_BIAS_DELTA_GAIN_STRU     stRfRxBiasDeltaGain;       /* VOICE模式与正常模式下的增益差 */
}UCOM_NV_W_RX_RFIC_BIAS_CTRL_STRU;

/*****************************************************************************
 枚举名    : UCOM_NV_W_RX_AGC_SWITCH_VOICE_MODE_STRU
 协议表格  :
 枚举说明  : VOICE模式下的AGC档位切换门限的NV项，只包括非BLOCK状态的
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwNoBlockAgcThresholdInc[UCOM_NV_W_AGC_GAIN_NOBLK_THRESHOLD_NUM];           /* NoBlock方式下档位增加 */
    VOS_INT16                           ashwNoBlockAgcThresholdDec[UCOM_NV_W_AGC_GAIN_NOBLK_THRESHOLD_NUM];           /* NoBlock方式下档位增加 */
}UCOM_NV_W_RX_AGC_SWITCH_VOICE_MODE_STRU;

/*****************************************************************************
 枚举名    : UCOM_NV_W_RX_EXT_LNA_AGC_SWITCH_VOICE_MODE_STRU
 协议表格  :
 枚举说明  : 有LNA情况下，VOICE模式下的AGC档位切换门限的NV项，只包括非BLOCK状态的
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwExtLnaVoiceAgcThrdEnable;
    VOS_INT16                           ashwExtLnaNoBlockAgcThrdInc[UCOM_NV_W_AGC_GAIN_NOBLK_THRESHOLD_NUM];           /* NoBlock方式下档位增加 */
    VOS_INT16                           ashwExtLnaNoBlockAgcThrdDec[UCOM_NV_W_AGC_GAIN_NOBLK_THRESHOLD_NUM];           /* NoBlock方式下档位增加 */
}UCOM_NV_W_RX_EXT_LNA_AGC_SWITCH_VOICE_MODE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_HDET_HKADC_CHAN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSeperatePaHdetChannel;           /* 分立PA HDET通道 */
    VOS_UINT16                          uhwReserved;               /*暂未使用，保留 */
}UCOM_NV_W_HDET_HKADC_CHAN_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_DPA_IQ_REDUCTION_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPA数字回退
*****************************************************************************/

typedef struct
{
    VOS_INT16                           ashwDpaIqReduction[UCOM_NV_W_TX_DPA_IQ_REDUCTION_NUM];
}UCOM_NV_W_TX_DPA_IQ_REDUCTION_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_SCUPA_IQ_REDUCTION_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SC-UPA数字回退
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwScUpaIqReduction[UCOM_NV_W_TX_SCUPA_IQ_REDUCTION_NUM];
}UCOM_NV_W_TX_SCUPA_IQ_REDUCTION_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_DPA_MPR_STRU_HI6361
 协议表格  :
 ASN.1描述 :
 结构说明  : DPA功率回退
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwDpaMpr[UCOM_NV_W_TX_DPA_MPR_NUM];
}UCOM_NV_W_TX_DPA_MPR_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_SCUPA_MPR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPA功率回退
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwScUpaMpr[UCOM_NV_W_TX_SCUPA_MPR_NUM];
}UCOM_NV_W_TX_SCUPA_MPR_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_DCUPA_MPR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPA功率回退
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwDcUpaMpr[UCOM_NV_W_TX_DCUPA_MPR_NUM];
}UCOM_NV_W_TX_DCUPA_MPR_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_HKADC_SSI_WAIT_TIME_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwHkadcSsiWaitTime;
}UCOM_NV_W_HKADC_SSI_WAIT_TIME_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_DRX_LTE_EVALUATE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE测量下移门限参数结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwLteEvaluateServCellReportCorr;       /* Lte测量不下移时服务小区测量上报周期系数默认6，范围0，30 */
    VOS_INT16                           shwLteEvaluateServCellRscpThres;        /* Lte测量下移判决的服务小区RSCP绝对值门限，单位0.125db，默认-640，范围-1040，-320 */
    VOS_UINT16                          uhwLteEvaluateServCellDeltaThres;       /* Lte测量下移判决的服务小区rscp变化值门限，单位0.125db，默认160，范围0，480 */
}UCOM_NV_W_DRX_LTE_EVALUATE_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_VOLT_LOWPOWER_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 调压低功耗控制NV
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwLowVoltDeltaPower;                   /* 降压最大发射功率差值门限,默认2dBm,,范围0~24dBm */
    VOS_UINT16                          uhwDataFrameThreshold;                  /* 连续数据帧个数门限,默认50,单位10msOr2ms */
    VOS_UINT16                          uhwNoDataFrameThreshold;                /* 连续无数据帧个数门限,默认80,单位10ms */
    VOS_INT16                           shwLowRssiThreshold;                    /* 升压RSSI门限,默认-95dBm */
    VOS_INT16                           shwHighRssiThreshold;                   /* 降压RSSI门限,默认-85dBm */
    VOS_UINT16                          uhwTxPowerCntThreshold;                 /* 升压发射功率统计个数门限,默认8,单位10ms */
    VOS_UINT16                          uhwHsupaRemainPowerCntThreshold;        /* 升压HSUPA剩余功率不足统计个数门限,默认8,单位10ms */
    VOS_UINT16                          uhwR99RemainPowerCntThreshold;          /* 升压R99剩余功率不足统计个数门限,默认8,单位10ms */
    VOS_UINT16                          uhwForceConfigLowPowerThreshold;        /* 强制降压计时门限,默认100,单位10ms */
}UCOM_NV_VOLT_LOWPOWER_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_ANT2_OFF_EVA_THRESH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 天线2关闭的评估门限参数结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwTimeRxNoDataDpa;                     /* 80、160、320、640、1000单位ms。默认160ms */
    VOS_UINT16                          uhwTimeRxNoDataR99Turbo;                /* 80、160、320、640、1000单位ms。默认160ms */
    VOS_UINT16                          uhwTimeRxNoDataR99Vtb;                  /* 80、160、320、640、1000单位ms。默认160ms */
}UCOM_NV_W_ANT2_OFF_EVA_THRESH_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_WCDMA_RX_CAL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :需要校准的WCDMA的频点个数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwValidCalChanNum;
    VOS_UINT16                          auhwRxCalChan[UCOM_WCDMA_UARFCN_NUM];        /* _H2ASN_Replace PHY_UINT16_ARRAY2_16 auhwRxCalChan[UCOM_WCDMA_BAND_NUM][UCOM_NV_W_UARFCN_NUM]; */ /* RX频点区间，3个频段，每个频段16个UARFCN */
}UCOM_NV_WCDMA_RX_CAL_CHAN_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RX_IP2_CAL_CHAN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :3.3需要进行IP2校准的频点
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwHighFreq;
    VOS_UINT16                          uhwMidFreq;
    VOS_UINT16                          uhwLowFreq;
}UCOM_NV_W_RX_IP2_CAL_CHAN_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_RX_IP2_CAL_AT1_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :主集RX通道每个BAND在高中低频点分集关闭和打开两种情况下，对I和Q路的电路参数补偿
*****************************************************************************/
typedef struct
{
    UCOM_NV_RX_IP2_STRU                 stRxIp2OffsetHDivyOn;                   /* 高频点分集开启 */
    UCOM_NV_RX_IP2_STRU                 stRxIp2OffsetHDivyOff;                  /* 高频点分集关闭 */
    UCOM_NV_RX_IP2_STRU                 stRxIp2OffsetMDivyOn;                   /* 中频点分集开启 */
    UCOM_NV_RX_IP2_STRU                 stRxIp2OffsetMDivyOff;                  /* 中频点分集关闭 */
    UCOM_NV_RX_IP2_STRU                 stRxIp2OffsetLDivyOn;                   /* 低频点分集开启 */
    UCOM_NV_RX_IP2_STRU                 stRxIp2OffsetLDivyOff;                  /* 低频点分集关闭 */
}UCOM_NV_W_RX_IP2_CAL_AT1_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RX_IP2_CAL_AT2_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :分集RX通道每个BAND在高中低频点下，对I和Q路的电路参数补偿
*****************************************************************************/
typedef struct
{
    UCOM_NV_RX_IP2_STRU                 stRxIp2OffsetH;
    UCOM_NV_RX_IP2_STRU                 stRxIp2OffsetM;
    UCOM_NV_RX_IP2_STRU                 stRxIp2OffsetL;
}UCOM_NV_W_RX_IP2_CAL_AT2_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RX_IP2_THRESHOLD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :IP2校准门限,主集分集共用同一个结构
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwIp2StopThreshold;                    /* 停止门限 */
    VOS_INT16                           shwIp2FailThreshold;                    /* 失败门限 */
}UCOM_NV_W_RX_IP2_THRESHOLD_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RX_IP2_CAL_ENABLE_AT2_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwRxIp2CalEnableAt2;           /* 0表示启动分集天线IP2校准，1表示不启动 */
}UCOM_NV_W_RX_IP2_CAL_ENABLE_AT2_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RX_AGC_FREQ_COMP_ANT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :3.5 AGC增益在统一个频段内因频点不同而引起的增益变化
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwRxAgcFreqComp[UCOM_WCDMA_UARFCN_NUM];
}UCOM_NV_W_RX_AGC_FREQ_COMP_ANT_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RX_AGC_GAIN_ANY_CARRIER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AGC Gain校准值
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwRxAgcGainNoBlock[UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM];
    VOS_INT16                           ashwRxAgcGainBlock[UCOM_NV_W_AGC_GAIN_BLK_STEP_NUM];
}UCOM_NV_W_RX_AGC_GAIN_ANY_CARRIER_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_RX_AGC_GAIN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AGC Gain校准值
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RX_AGC_GAIN_ANY_CARRIER_STRU            astAgcGain[UCOM_NV_DC_SC_MODE_BUTT];    /* AGC Gain,区分主辅载波 */
}UCOM_NV_W_RX_AGC_GAIN_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_RX_AGC_GAIN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AGC Gain校准值
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RX_AGC_GAIN_STRU            astRxAgcGainAnt[UCOM_NV_W_ANT_NUM];    /* AGC Gain,区分主辅载波 */
}UCOM_NV_W_RX_AGC_GAIN_DANT_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_RX_AGC_GAIN_PRE_ANY_CARRIER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AGC Gain Predefined值
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwRxAgcGainPreNoBlock[UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM];
    VOS_INT16                           ashwRxAgcGainPreBlock[UCOM_NV_W_AGC_GAIN_BLK_STEP_NUM];
}UCOM_NV_W_RX_AGC_GAIN_PRE_ANY_CARRIER_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RX_AGC_GAIN_PRE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AGC Gain Predefined值
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RX_AGC_GAIN_PRE_ANY_CARRIER_STRU
                                        astRxAgcGainPreCarrier[UCOM_NV_DC_SC_MODE_BUTT];         /* AGC Gain Pre值,区分主辅载波 */
}UCOM_NV_W_RX_AGC_GAIN_PRE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RX_AGC_GAIN_PRE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AGC Gain Predefined值
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RX_AGC_GAIN_PRE_STRU
                                        astRxAgcGainPreAnt[UCOM_NV_W_ANT_NUM];         /* AGC Gain Pre值,区分主辅载波 */
}UCOM_NV_W_RX_AGC_GAIN_PRE_DANT_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RX_AGC_FRONT_END_GAIN_PRE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AGC Front End Predefined值
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwRxFrontEndGainPre[UCOM_NV_DC_SC_MODE_BUTT];   /* Front End Predefined */
}UCOM_NV_W_RX_AGC_FRONT_END_GAIN_PRE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RX_AGC_FRONT_END_GAIN_PRE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AGC Front End Predefined值
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RX_AGC_FRONT_END_GAIN_PRE_STRU         astRxFrontEndGainPre[UCOM_NV_W_ANT_NUM];   /* Front End Predefined */
}UCOM_NV_W_RX_AGC_FRONT_END_GAIN_PRE_DANT_STRU;


/*****************************************************************************
 枚举名    : RX_AGC_GAIN_SWITCH_THRESHOLD_STRU
 协议表格  :
 枚举说明  : AGC档位切换门限的NV项，包括BLOCK和非BLOCK
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwNoBlockAgcThresholdInc[UCOM_NV_W_AGC_GAIN_NOBLK_THRESHOLD_NUM];           /* NoBlock方式下档位增加 */
    VOS_INT16                           ashwNoBlockAgcThresholdDec[UCOM_NV_W_AGC_GAIN_NOBLK_THRESHOLD_NUM];           /* NoBlock方式下档位增加 */
    VOS_INT16                           ashwBlockAgcThresholdInc[UCOM_NV_W_AGC_GAIN_BLK_THRESHOLD_NUM];             /* Block方式下档位增加 */
    VOS_INT16                           ashwBlockAgcThresholdDec[UCOM_NV_W_AGC_GAIN_BLK_THRESHOLD_NUM];             /* Block方式下档位增加 */
}UCOM_NV_W_RX_AGC_GAIN_SWITCH_THRESHOLD_STRU;

/*****************************************************************************
 枚举名    : UCOM_NV_W_RX_AGC_GAIN_PREDEFINED_ANYCARRIER_STRU
 协议表格  :
 枚举说明  : AGC档位切换门限的NV项，包括BLOCK和非BLOCK
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RX_AGC_GAIN_SWITCH_THRESHOLD_STRU      astRxAgcGainSwitchThreshold[UCOM_NV_DC_SC_MODE_BUTT];
}UCOM_NV_W_RX_AGC_GAIN_SWITCH_THRESHOLD_DCARR_STRU;


/*****************************************************************************
 枚举名    : UCOM_NV_W_RX_AGC_CTRL_STRU
 协议表格  :
 枚举说明  : AGC控制字的NV项，包括BLOCK和非BLOCK
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      unAgcCtrlNoBlock[UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM];                   /* 非Block模式的AGC控制字 */
    VOS_UINT32                      unAgcCtrlBlock[UCOM_NV_W_AGC_GAIN_BLK_STEP_NUM];                     /* Block模式的AGC控制字 */
}UCOM_NV_W_RX_AGC_CTRL_STRU;

/*****************************************************************************
 枚举名    : UCOM_NV_W_RX_AGC_CTRL_STRU
 协议表格  :
 枚举说明  : AGC控制字的NV项，包括BLOCK和非BLOCK
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RX_AGC_CTRL_STRU  astRxAgcCtrl[UCOM_NV_DC_SC_MODE_BUTT];
}UCOM_NV_W_RX_AGC_CTRL_DCARR_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_EXT_LNA_MIPI_WORD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : mipi lna 控制字
*****************************************************************************/
typedef struct
{
    VOS_UINT32                               uwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU                    astLnaMipiCmd[UCOM_NV_W_LNA_MIPI_CMD_MAX_NUM ];
    UCOM_NV_MIPI_BYTE_DATA_STRU              astLnaMipiData[UCOM_NV_W_LNA_MIPI_DATA_MAX_NUM ];
}UCOM_NV_W_EXT_LNA_MIPI_WORD_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_EXT_LNA_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : EXT LNA INFO
*****************************************************************************/
typedef struct
{
    VOS_UINT32                               uwGpioEnable;                              /* GPIO使能信号 */
    VOS_UINT32                               uwLnaGpioNumber;                           /* 支持的档位数*/
    VOS_UINT32                               auwLnaGpio[UCOM_NV_W_LNA_GPIO_STEP_NUM];   /* 4档LNA GPIO的配置 */
    VOS_UINT32                               uwLnaGpioMask;                             /* 使用的LNA GPIO的掩码 */
    VOS_UINT32                               uwMipiEnable;                              /* MIPI使能信号*/
    VOS_UINT32                               uwLnaMipiNumber;                           /* 支持的档位数*/
    UCOM_NV_W_EXT_LNA_MIPI_WORD_STRU         astLnaMipi[UCOM_NV_W_LNA_MIPI_STEP_NUM];   /* MIPI LNA 配置 */
    UCOM_NV_W_EXT_LNA_MIPI_WORD_STRU         stLnaOff;                                  /* LNA 关闭配置*/
    VOS_UINT32                               auwUnBlockGainIndex[UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM];/* BLOCK下AGC档位的lna增益索引*/
    VOS_UINT32                               auwBlockGainIndex[UCOM_NV_W_AGC_GAIN_BLK_STEP_NUM];/* BLOCK下AGC档位的lna增益索引*/
}UCOM_NV_W_EXT_LNA_INFO_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_EXT_LNA_COMMON_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : EXT LNA COMMON INFO
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_EXT_LNA_INFO_STRU              stMainLnaInfo;       /* 主集mipi lna 信息 */
    UCOM_NV_W_EXT_LNA_INFO_STRU              stDivLnaInfo;        /* 分集mipi lna 信息  */
}UCOM_NV_W_EXT_LNA_COMMON_INFO_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RX_AGC_CTRL_EXT_LNA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 外置LNA的AGC配置信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                               uwAgcCtrlEnable;     /* LNA 打开的时候，是否支持AGC档位切换 */
    UCOM_NV_W_RX_AGC_CTRL_DCARR_STRU         stAgcCtrlWord;       /* LNA ON的时候使用的AGC增益控制字 */
}UCOM_NV_W_RX_AGC_CTRL_EXT_LNA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RX_AGC_SWITCH_THRD_EXT_LNA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 外置LNA的AGC配置信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                                uwAgcThrdEnable;/* LNA 打开的时候，是否配置AGC档位切换门限 */
    UCOM_NV_W_RX_AGC_GAIN_SWITCH_THRESHOLD_DCARR_STRU         stAgcThreshold; /* LNA ON的时候使用的AGC切换门限 */
}UCOM_NV_W_RX_AGC_SWITCH_THRD_EXT_LNA_STRU;


/*****************************************************************************
 枚举名    : UCOM_NV_W_DCOFFSET_STRU
 协议表格  :
 枚举说明  : DC offset的结构体类型
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwDci;                                 /* I路的直流值 */
    VOS_INT16                           shwDcq;                                 /* Q路的直流值 */
}UCOM_NV_W_DCOFFSET_STRU;


/*****************************************************************************
 枚举名    : UCOM_NV_W_DCOFFSET_ANYCARRIER_STRU
 协议表格  :
 枚举说明  : DC offset的结构体类型
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_DCOFFSET_STRU             astNoBlockDcOffset[UCOM_NV_W_AGC_GAIN_BLK_STEP_NUM];       /* block模式下各档位的DC offset */
    UCOM_NV_W_DCOFFSET_STRU             astBlockDcOffset[UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM];         /* 非block模式下各档位的DC offset */
}UCOM_NV_W_DCOFFSET_ANYCARRIER_STRU;


/*****************************************************************************
 枚举名    : W_DCOFFSET_ANT_STRU
 协议表格  :
 枚举说明  : DC offset的结构体类型
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_DCOFFSET_ANYCARRIER_STRU              astAnyCarrierDcOffset[UCOM_NV_DC_SC_MODE_BUTT];   /* SC\DC载波模式下的DC值 */
}UCOM_NV_W_DCOFFSET_ANT_STRU;

/*****************************************************************************
 枚举名    : UCOM_NV_W_DCOFFSET_ANT_STRU
 协议表格  :
 枚举说明  : DC offset的结构体类型
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_DCOFFSET_ANT_STRU              astDcOffsetAnt[UCOM_NV_W_ANT_NUM];
}UCOM_NV_W_DCOFFSET_DANT_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_FEM_CHAN_CONNECT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : A/B通道对等选择,前端Ch0/CH1通道选择
*****************************************************************************/
typedef struct
{
    UCOM_NV_CHAN_CONNECT_ENUM_UINT16    enRfConnect;                            /* RF~RFIC之间的连接:0:主集连接在RF_A，1:主集连接在RF_B */
    UCOM_NV_CHAN_CONNECT_ENUM_UINT16    enRfAbbConnect;                         /* RFIC与ABB之间的连接,硬件连线,不需要软件配置 */
    UCOM_NV_CHAN_CONNECT_ENUM_UINT16    enAbbBbpConnect;                        /* ABB与BBP COM1之间的连接:0:主集连接在ABB_A，1:主集连接在ABB_B */
    VOS_UINT16                          uhwChanSwitch;                          /* 定义每个band选择通道0或者1,目前V9R1上默认主卡通道都选择0,副卡通道都选择1. */

}UCOM_NV_FEM_CHAN_CONNECT_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_WCDMA_TX_CAL_CHAN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :需要校准的WCDMA的频点个数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwValidCalChanNum;
    VOS_UINT16                          auhwTxCalChan[UCOM_WCDMA_UARFCN_NUM];        /* _H2ASN_Replace PHY_UINT16_ARRAY2_16 auhwRxCalChan[UCOM_WCDMA_BAND_NUM][UCOM_NV_W_UARFCN_NUM]; */ /* RX频点区间，3个频段，每个频段16个UARFCN */
}UCOM_NV_WCDMA_TX_CAL_CHAN_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_WCDMA_TX_WIRED_MAX_POWER_RACH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwTxWiredMaxPowerRach;                             /* 三个频段，上行仅存在DPCH或存在RACH时UE可允许的最大发射功率，单位0.1dbm;第0列为RACH,第1列为DPCH, */
}UCOM_NV_WCDMA_TX_WIRED_MAX_POWER_RACH_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_WCDMA_TX_WIRED_MAX_POWER_DPCH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwTxWiredMaxPowerDpch;                             /* 三个频段，上行仅存在DPCH或存在RACH时UE可允许的最大发射功率，单位0.1dbm;第0列为RACH,第1列为DPCH, */
}UCOM_NV_WCDMA_TX_WIRED_MAX_POWER_DPCH_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_WCDMA_TX_WIRED_MAX_POWER_TEMP_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   ashwTxWiredMaxPowerTempComp[UCOM_NV_W_TEMP_NUM];    /* 最大发射功率补偿增益，单位0.1dbm;3个频段，5个预先定义的温度点:-20,0,20,40,60,第6个点用于对齐，不使用 */
}UCOM_NV_WCDMA_TX_WIRED_MAX_POWER_TEMP_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_WCDMA_TX_MIN_POWER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwTxMinPower;                                      /* UE允许的最小发射功率，单位0.1dbm;3个频段，5个预先定义的温度点:-20,0,20,40,60,第6个点用于对齐，不使用 */
}UCOM_NV_WCDMA_TX_MIN_POWER_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_WCDMA_TX_MIN_POWER_TEMP_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   ashwTxMinPowerTempComp[UCOM_NV_W_TEMP_NUM];         /* 最小发射功率温度补偿 */
}UCOM_NV_WCDMA_TX_MIN_POWER_TEMP_COMP_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_TX_HDET_VGA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwTxHdetVga;                                                   /* 表示PD的前级衰减 和VGA值*/
}UCOM_NV_W_TX_HDET_VGA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_HDET_DCOFFSET_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwTxHdetDcOffset;                                              /* 表示DCOFFSET */
}UCOM_NV_W_TX_HDET_DCOFFSET_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_HDET_POWER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwTxHdetContPower[UCOM_NV_W_TX_HDET_PV_NUM];                  /* 高增益模式下，测试功率和电压关系的功率测试点 */
}UCOM_NV_W_TX_HDET_POWER_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_HDET_HKADC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwTxHdetVolt[UCOM_NV_W_TX_HDET_PV_NUM];                       /* 高增益模式下，测试功率和电压关系时电压测试值 */
}UCOM_NV_W_TX_HDET_HKADC_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_HDET_FREQ_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwTxHdetFreqComp[UCOM_WCDMA_UARFCN_NUM];                       /* 不同频点对功率器件影响不同，频率补偿值 */
}UCOM_NV_W_TX_HDET_FREQ_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_HDET_TEMP_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwTxHdetTempComp[UCOM_NV_W_TEMP_NUM];  /* 不同温度对功率器件影响不同，温度补偿值.区分高中低信道,顺序为中高低 */
}UCOM_NV_W_TX_HDET_TEMP_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_HDET_START_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTxHdetStart;                                                 /* TX 发射功率超过该值时，BBP自动启动功率检测 */
}UCOM_NV_W_TX_HDET_START_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_HDET_STOPT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTxHdetStop;                                                  /* TX 发射功率小于该值时，BBP自动停止功率检测 */
}UCOM_NV_W_TX_HDET_STOPT_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_WCDMA_TX_WIRE_MAXPOWER_RACH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwTxWirelessMaxPowerRach;                          /* 无线 *//* 空口发射功率:_UCOM_TX_PWR_CTRL_SWITCH */
}UCOM_NV_WCDMA_TX_WIRE_MAXPOWER_RACH_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_WCDMA_TX_WIRE_MAXPOWER_DPCH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwTxWirelessMaxPowerDpch;                          /* 无线 *//* 空口发射功率:_UCOM_TX_PWR_CTRL_SWITCH */
}UCOM_NV_WCDMA_TX_WIRE_MAXPOWER_DPCH_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_WCDMA_TX_WIRELESS_POWER_TEMP_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   ashwTxWirelessPowerTempComp[UCOM_NV_W_TEMP_NUM];    /* 空口功率下温度补偿 */
}UCOM_NV_WCDMA_TX_WIRELESS_POWER_TEMP_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_GAIN_COMP_VS_PA_CHAN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwHighFreq;                            /* 用于判断高频点区间的频点 */
    VOS_UINT16                          uhwLowFreq;                             /* 用于判断低频点区间的频点 */
}UCOM_NV_W_TX_GAIN_COMP_VS_PA_CHAN_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_GAIN_COMP_VS_PA_CH_STRU
 协议表格  :
 结构说明  : W TX PA增益切换点补偿的区间分界点
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwValidNum;                             /* 表示以下频点几个有效 */
    VOS_UINT16                          auhwFreqChan[UCOM_NV_W_PA_GAIN_SWITCH_COMP_CHAN_NUM];
}UCOM_NV_W_TX_GAIN_COMP_VS_PA_CH_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_PA_GAIN_SWITCH_COMP_STRU
 协议表格  :
 结构说明  : W TX PA增益切换时功率补偿值
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwH2MComp;                             /* PA增益从高切到中的门限补偿,单位0.1db */
    VOS_INT16                           shwM2HComp;                             /* PA增益从中切到高的门限补偿,单位0.1db */
    VOS_INT16                           shwM2LComp;                             /* PA增益从中切到低的门限补偿,单位0.1db */
    VOS_INT16                           shwL2MComp;                             /* PA增益从低切到中的门限补偿,单位0.1db */
}UCOM_NV_W_PA_GAIN_SWITCH_COMP_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_TX_PA_GAIN_SWITCH_COMP_STRU
 协议表格  :
 结构说明  : W TX 4个时隙的PA增益切换时功率补偿值
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_PA_GAIN_SWITCH_COMP_STRU  astSlotComp[UCOM_NV_W_PA_SWITCH_COMP_SLOT];
}UCOM_NV_W_TX_PA_GAIN_SWITCH_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_APC_TEMP_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwTxApcTemp;                                       /* 保存校准时的温度值:本项保存中信道下,每个BAND的高中低PA增益模式下校准时候的温度值,列表示高中低 */
}UCOM_NV_W_TX_APC_TEMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_PA_GAIN_SWITH_THRESHOLD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/

typedef struct
{
    VOS_INT16                           shwPaGainThresH2M;                      /* PA从高增益到中增益的切换门限 */
    VOS_INT16                           shwPaGainThresM2H;                      /* PA从中增益到高增益的切换门限 */
    VOS_INT16                           shwPaGainThresM2L;                      /* PA从中增益到低增益的切换门限 */
    VOS_INT16                           shwPaGainThresL2M;                      /* PA从低增益到中增益的切换门限 */
}UCOM_NV_W_PA_GAIN_SWITH_THRESHOLD_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RF_PA_GAIN_CTRL_WORD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          uwRfPaCtrlHighMode;                     /* PA高增益模式控制字 */
    VOS_UINT32                          uwRfPaCtrlMediumMode;                   /* PA中增益模式控制字 */
    VOS_UINT32                          uwRfPaCtrlLowMode;                      /* PA低增益模式控制字 */
}UCOM_NV_W_RF_PA_GAIN_CTRL_WORD_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_PA_GAIN_SWITH_TIMING_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/

typedef struct
{
    VOS_INT16                           shwPaGainSwitchH2M;                     /* PA增益高增益到中增益切换时序 */
    VOS_INT16                           shwPaGainSwitchM2H;                     /* PA增益中增益到高增益切换时序 */
    VOS_INT16                           shwPaGainSwitchM2L;                     /* PA增益中增益到低增益切换时序 */
    VOS_INT16                           shwPaGainSwitchL2M;                     /* PA增益低增益到中增益切换时序 */
}UCOM_NV_W_PA_GAIN_SWITH_TIMING_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_TX_IQ_MISMATCH_DCR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :2.3 每组NV项目表示上行IQ mismatch和DC offset
            正常工作时，将此参数配置给DBB，对TX通道进行预畸变
            以弥补上行通道的IQ mismatch和残余DC。
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwAmplitude;                           /* 幅值校正因子 */
    VOS_INT16                           shwPhase;                               /* 相位校正因子 */
    VOS_INT16                           shwDCI;                                 /* 直流校正实部 */
    VOS_INT16                           shwDCQ;                                 /* 直流校正虚部 */
}UCOM_NV_TX_IQ_MISMATCH_DCR_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_PA_GAIN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 表示RFIC和DBB不衰减的情况下，高中低3档增益的增益值
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwPaGain[UCOM_NV_W_TX_PA_MODE_NUM];           /* 非VOICE模式下，表示RFIC和DBB不衰减的情况下，高中低3档增益的增益值，单位为0.1dB */
}UCOM_NV_W_TX_PA_GAIN_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_PA_GAIN_VOICE_MODE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 表示VOICE模式下，RFIC和DBB不衰减的情况下，高中低3档增益的增益值
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwPaGain[UCOM_NV_W_TX_PA_MODE_NUM];           /* 表示VOICE模式下，RFIC和DBB不衰减的情况下，高中低3档增益的增益值，单位为0.1dB */
}UCOM_NV_W_TX_PA_GAIN_VOICE_MODE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_PHASE_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :4.2 PA模式从高增益切换到中增益、中增益切换到低增益、低增益切换到
                中增益、中增益切换到高增益时，由于TX和PA会对基带IQ信号产生相位
                旋转。
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwPaH2M;
    VOS_INT16                           shwPaM2H;
    VOS_INT16                           shwPaM2L;
    VOS_INT16                           shwPaL2M;

}UCOM_NV_W_TX_PHASE_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_PHASE_COMP_TIMING_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwTxPhaseCompTiming;
}UCOM_NV_W_TX_PHASE_COMP_TIMING_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_GAIN_FREQCOMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   ashwTxGainFreqComp[UCOM_NV_W_TX_FREQ_COMP_NUM];     /* _H2ASN_Replace PHY_UINT16_ARRAY2_16 ashwHigh[W_BAND_NUM][W_UARFCN_NUM];*/ /* TX高增益频率补偿值 */
}UCOM_NV_W_TX_GAIN_FREQCOMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_GAIN_TEMP_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :7.4 PA处于高中低增益模式下，频段内高、中、低信道下，TX发射功率相对于温度变化的补偿
*****************************************************************************/
typedef struct
{
    /* 温度范围的取值取决于UCOM_NV_WG_TX_TEMP_DEFINE_STRU */
    VOS_INT16                           ashwTxGainTempComp[UCOM_NV_W_TX_PA_TEMP_NUM];
}UCOM_NV_W_TX_GAIN_TEMP_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_HSDPCCH_DELTA_GAIN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTpcAlgo1UlPowGain;
    VOS_INT16                           shwTpcAlgo1HsDpaPowMode;
    VOS_INT16                           shwTpcAlgo2UlPowGain;
    VOS_INT16                           shwTpcAlgo2HsDpaPowMode;
}UCOM_NV_W_HSDPCCH_DELTA_GAIN_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_SAR_BACKOFF_POWER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 降SAR功率回退值
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   ashwWcdmaSarBackoffPower[UCOM_NV_SAR_BACKOFF_NUM][UCOM_NV_SAR_MODEM_SCENE_NUM];
}UCOM_NV_W_SAR_BACKOFF_POWER_STRU;

typedef UCOM_NV_W_SAR_BACKOFF_POWER_STRU UCOM_NV_CDMA_SAR_BACKOFF_POWER_STRU;
/*****************************************************************************
 结构名    : UCOM_NV_W_SAR_BACKOFF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 降SAR功率回退值(DPDT状态，modem场景，AT档位)
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwSupportBandBitmap;            /* 当特殊场景生效时，优先查看对应的频段是否支持特殊场景，如果支持，则使用本NV项进行功率回退。 */
    UCOM_NV_W_SAR_BACKOFF_POWER_STRU            stDpdtPassThrough;              /* DPDT状态为直通态时的SAR回退 */
    UCOM_NV_W_SAR_BACKOFF_POWER_STRU            stDpdtSwap;                     /* DPDT状态为交叉态时的SAR回退 */
}UCOM_NV_W_SAR_BACKOFF_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_SAR_SPECIAL_SCENE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SAR特殊场景的配置
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_SAR_BACKOFF_STRU                  astSpeceilScene[UCOM_NV_W_SAR_SPECIAL_SCENE_NUM];
                                                                                /* 特殊场景的SAR回退。最多支持4个 */
}UCOM_NV_W_SAR_SPECIAL_SCENE_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_SAR_BAND_ATTRIBUTE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM SAR功能的频段属性(高频段/低频段)
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwBandMask;                     /* 对应的bit置位1代表高频段。BIT0表示850M,BIT1表示900M,BIT2表示1800M,BIT3表示1900M, */
}UCOM_NV_GSM_SAR_BAND_ATTRIBUTE_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_SAR_BAND_PARTITION_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W SAR功能的频段属性(高频段/低频段)
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwBandMask;                     /* 对应的bit置位1代表高频段。BIT0表示B1，BIT1表示B2，BIT2表示B3，以此类推 */
    VOS_UINT32                                  uwResvered;
}UCOM_NV_W_SAR_BAND_ATTRIBUTE_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_APC_RFIC_CTRL_GAIN_STRU
 协议表格  :
 结构说明  : APC table表
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  auhwApcRficCtrlGain[UCOM_NV_W_APC_ATTEN_NUM];

}UCOM_NV_W_APC_RFIC_CTRL_GAIN_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_APC_DBB_ATTEN_GAIN_STRU
 协议表格  :
 结构说明  : APC table表
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   ashwApcDbbAttenGain[UCOM_NV_W_APC_ATTEN_NUM];

}UCOM_NV_W_APC_DBB_ATTEN_GAIN_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_APC_GAIN_STATE_INDEX_STRU
 协议表格  :
 结构说明  : APC table表
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  auhwRfGainStateIndexGain[UCOM_NV_W_APC_ATTEN_NUM];

}UCOM_NV_W_APC_GAIN_STATE_INDEX_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_APC_RFIC_CTRL_GAIN_VOICE_MODE_STRU
 协议表格  :
 结构说明  : APC table表
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  auhwApcRficCtrlGainVoiceMode[UCOM_NV_W_APC_ATTEN_NUM];

}UCOM_NV_W_APC_RFIC_CTRL_GAIN_VOICE_MODE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_APC_DBB_ATTEN_GAIN_MODE_STRU
 协议表格  :
 结构说明  : APC table表
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   ashwApcDbbAttenGainVoiceMode[UCOM_NV_W_APC_ATTEN_NUM];

}UCOM_NV_W_APC_DBB_ATTEN_GAIN_VOICE_MODE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_APC_STATE_INDEX_GAIN_VOICE_MODE_STRU
 协议表格  :
 结构说明  : APC table表
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  auhwRfGainStateIndexGainVoiceMode[UCOM_NV_W_APC_ATTEN_NUM];

}UCOM_NV_W_APC_STATE_INDEX_GAIN_VOICE_MODE_STRU;



/*****************************************************************************
 结构名    : UCOM_NV_W_TX_PA_APT_STRU
 协议表格  :
 结构说明  : APT发射功率的结构体类型
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwPower10th;                           /* 每个档位下APT发射功率 */

    VOS_UINT16                          uhwPaVcc;                               /* 每个档位下APT电压控制字 */
    VOS_UINT16                          uhwPaVbias;                             /* 每个档位下MmmbPaVbias电压控制字 */
    VOS_UINT16                          uhwPaVbias2;                            /* 每个档位下MmmbPaVbias2 */
    VOS_UINT16                          uhwPaVbias3;                            /* 每个档位下MmmbPaVbias3 */
}UCOM_NV_W_TX_PA_APT_STRU;

typedef UCOM_NV_W_TX_PA_APT_STRU                UCOM_NV_CDMA_TX_PA_APT_STRU;
/*****************************************************************************
 结构名    : UCOM_NV_W_TX_PA_APT_TABLE_STRU
 协议表格  :
 结构说明  : APT发射功率的结构体类型
*****************************************************************************/
typedef struct
{
    UCOM_NV_POWER_STEP_ENUM_UINT16      enAptStepMode;
    VOS_UINT16                          auhwValidCount[UCOM_NV_PA_GAIN_MAX_NUM];
    UCOM_NV_W_TX_PA_APT_STRU            astAptTable[UCOM_NV_APT_TABLE_MAX_LEN];
}UCOM_NV_W_TX_PA_APT_TABLE_STRU;

typedef UCOM_NV_W_TX_PA_APT_TABLE_STRU UCOM_NV_CDMA_TX_PA_APT_TABLE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_MIPI_PA_TIMING_CFG_STRU
 协议表格  :
 结构说明  : PA的控制信息提前于时隙头生效时间，单位chip
*****************************************************************************/
typedef struct
{
    VOS_UINT16              uhwPaVccActiveTime;
    VOS_UINT16              uhwPaBias1ActiveTime;
    VOS_UINT16              uhwPaBias2ActiveTime;
    VOS_UINT16              uhwPaBias3ActiveTime;
    VOS_UINT16              uhwTrigger1ActiveTime;
    VOS_UINT16              uhwTrigger2ActiveTime;
}UCOM_NV_W_MIPI_APT_TIMING_CFG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_APT_CTRL_STRU
 协议表格  :
 结构说明  : APT表中PA控制信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwAptPaVbias1En         :1;             /* APT表中 PaVbias是否有效 */
    VOS_UINT32                          uwAptPaVbias2En         :1;             /* APT表中 PaVbias1是否有效 */
    VOS_UINT32                          uwAptPaVbias3En         :1;             /* APT表中 PaVbias2是否有效 */
    VOS_UINT32                          uwAptMipiTrigger1En     :1;             /* Mipi Trigger[0]是否有效 */
    VOS_UINT32                          uwAptMipiTrigger2En     :1;             /* Mipi Trigger[1]是否有效 */
    VOS_UINT32                          uwAptPaVccCtrlType      :2;             /* APT表中 pa Vcc控制类型,0:PDM,1:MIPI */
    VOS_UINT32                          uwAptPaVbiasCtrlType    :2;             /* APT表中 pa Vbias控制类型,0:DAC,1:MIPI */
    VOS_UINT32                          uwAptPaVccMipiChSel     :3;             /* APT表中 pa Vcc为Mipi控时，选择MIPI通道 */
    VOS_UINT32                          uwAptPaVbias1MipiChSel  :3;             /* APT表中 pa Vbias为Mipi控时，选择MIPI通道 */
    VOS_UINT32                          uwAptPaVbias2MipiChSel  :3;             /* APT表中 pa Vbias1为Mipi控时，选择MIPI通道 */
    VOS_UINT32                          uwAptPaVbias3MipiChSel  :3;             /* APT表中 pa Vbias2为Mipi控时，选择MIPI通道 */
    VOS_UINT32                          uwReserve               :11;            /* 保留 */
}UCOM_NV_W_APT_CTRL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_APT_MIPI_PA_TRIGGER_STRU
 协议表格  :
 结构说明  : Mipi PA trigger的mipi控制指令
*****************************************************************************/
typedef struct
{
    UCOM_NV_MIPI_CMD_STRU               astPaTriggerMipiCmd[UCOM_NV_W_MIPI_PA_TRIGGER_NUM];
    UCOM_NV_MIPI_BYTE_DATA_STRU         astPaTriggerMipiData[UCOM_NV_W_MIPI_PA_TRIGGER_NUM];
}UCOM_NV_W_APT_MIPI_PA_TRIGGER_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_APT_CTRL_PARA_STRU
 协议表格  :
 结构说明  : APT控制信息
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_APT_CTRL_STRU             stAptCtrlInfo;
    UCOM_NV_MIPI_CMD_STRU               stPaVccMipiCmd;                                 /* PA Vcc的mipi控制指令,数据在APT中 */
    UCOM_NV_MIPI_CMD_STRU               astPaVbiasMipiCmd[UCOM_NV_W_TX_PA_VBIAS_NUM];   /* 配置PA Vbias的控制指令，数据在APT中 */
    UCOM_NV_W_APT_MIPI_PA_TRIGGER_STRU  stMipiPaTrigger;                                /* Mipi PA Trigger指令，保证APT表中Pa指令同时生效，避免临界情况  */
    UCOM_NV_W_MIPI_APT_TIMING_CFG_STRU  stMipiAptTimingInfo;                            /* PA的控制信息提前于时隙头生效时间，单位chip */
}UCOM_NV_W_APT_CTRL_PARA_STRU;

typedef UCOM_NV_W_APT_CTRL_PARA_STRU UCOM_NV_CDMA_APT_CTRL_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_ANT_TUNER_BAND_PARA_STRU
 协议表格  :
 结构说明  : 天线调谐BAND控制结构体类型
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwAntTunerCode;                   /* 当前BAND天线调谐默认值 */
    VOS_UINT16                              uhwReserve;
    VOS_UINT16                              uhwAntTunerStart;                  /* 当前BAND驻波检测启动门限,BBP未提供接口，暂和PD打开门限一致 */
    VOS_INT16                               shwAntTunerComp;                   /* 反向功率补偿，精度0.1dbm */
}UCOM_NV_W_ANT_TUNER_BAND_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TUNER_MIPI_DATA_FRAME_STRU
 协议表格  :
 结构说明  : Tuner的数据帧
*****************************************************************************/
typedef struct
{
    UCOM_NV_MIPI_BYTE_DATA_STRU         astTunerMipiData[UCOM_NV_W_TUNER_MIPI_DATA_MAX_NUM];
}UCOM_NV_W_TUNER_MIPI_DATA_FRAME_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_TUNER_MIPI_DATA_FRAME_STRU
 协议表格  :
 结构说明  : Tuner的数据帧
*****************************************************************************/
typedef struct
{
    UCOM_NV_MIPI_BYTE_DATA_STRU             astMipiData[UCOM_NV_GSM_TUNER_MIPI_DATA_MAX_NUM];
}UCOM_NV_GSM_TUNER_MIPI_DATA_FRAME_STRU;


/*****************************************************************************
 枚举名    : UCOM_NV_W_TUNER_MIPI_CTRL_WORD_STRU
 协议表格  :
 枚举说明  : W配置数据,最多支持五种状态
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU                   astMipiTunnerCmd[UCOM_NV_W_TUNER_MIPI_CMD_MAX_NUM];
    UCOM_NV_W_TUNER_MIPI_DATA_FRAME_STRU    astMipiDataStatus[UCOM_NV_TUNER_HANDLE_STATUS_NUM];
}UCOM_NV_W_TUNER_MIPI_CTRL_WORD_STRU;

typedef UCOM_NV_W_TUNER_MIPI_CTRL_WORD_STRU UCOM_NV_CDMA_TUNER_MIPI_CTRL_WORD_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_G_TUNER_MIPI_TX_CTRL_WORD_STRU
 协议表格  :
 结构说明  : G模Tx默认配置数据
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU                       astMipiTunnerCmd[UCOM_NV_GSM_TUNER_MIPI_CMD_MAX_NUM];
    UCOM_NV_GSM_TUNER_MIPI_DATA_FRAME_STRU      astMipiDataStatus[UCOM_NV_TUNER_HANDLE_STATUS_NUM];
}UCOM_NV_G_TUNER_MIPI_TX_CTRL_WORD_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_TUNER_MIPI_DATA_RX_STRU
 协议表格  :
 结构说明  : G模Rx默认配置数据
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU                       astMipiTunnerCmd[UCOM_NV_GSM_TUNER_MIPI_CMD_MAX_NUM];
    UCOM_NV_GSM_TUNER_MIPI_DATA_FRAME_STRU      astMipiDataStatus[UCOM_NV_TUNER_HANDLE_STATUS_NUM];
}UCOM_NV_G_TUNER_MIPI_RX_CTRL_WORD_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_TX_HDET_SCUPA_CM_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SC-UPA的CM值补偿
*****************************************************************************/

typedef struct
{
    VOS_INT16                           ashwScUpaPdComp[UCOM_NV_W_TX_HDET_SCUPA_CM_COMP_NUM];
}UCOM_NV_W_TX_HDET_SCUPA_CM_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_HDET_DPA_CM_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPA的CM值补偿
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwDpaPdComp[UCOM_NV_W_TX_HDET_DPA_CM_COMP_NUM];
}UCOM_NV_W_TX_HDET_DPA_CM_COMP_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_TX_APT_CM_SCUPA_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SC-UPA业务的APT模式scupa补偿
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwAptCmScupaComp[UCOM_NV_W_TX_APT_SCUPA_CM_COMP_NUM];
}UCOM_NV_W_TX_APT_CM_SCUPA_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_APT_CM_DPA_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SC-UPA业务的APT模式dpa补偿
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwAptCmDpaComp[UCOM_NV_W_TX_APT_DPA_CM_COMP_NUM];
}UCOM_NV_W_TX_APT_CM_DPA_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_APT_TEMP_COMP_STRU_HI6361
 协议表格  :
 ASN.1描述 :
 结构说明  : APT频率补偿
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwAptTempComp[UCOM_NV_W_APT_FREQ_COMP_NUM][UCOM_NV_W_APT_TEMP_COMP_NUM];                                /* 该值表示W的BAND或者G模的BAND标识 */
}UCOM_NV_W_APT_TEMP_COMP_STRU;

typedef UCOM_NV_W_APT_TEMP_COMP_STRU UCOM_NV_CDMA_APT_TEMP_COMP_STRU;

/*****************************************************************************
 枚举名    : UCOM_NV_W_APT_COMP_STRU
 协议表格  :
 枚举说明  : APT电压补偿的结构体类型
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwAptComp[UCOM_NV_APT_TABLE_MAX_LEN];       /* 每个档位下APT补偿 */
}UCOM_NV_W_APT_COMP_STRU;

typedef UCOM_NV_W_APT_COMP_STRU UCOM_NV_CDMA_APT_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_PA_NONLINEAR_STRU_HI6361
 协议表格  :
 ASN.1描述 :
 结构说明  : PA非线性补偿
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwPower;
    VOS_INT16                           shwNonLinearComp;
}UCOM_NV_W_PA_NONLINEAR_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_PA_NONLINEAR_COMP_STRU_HI6361
 协议表格  :
 ASN.1描述 :
 结构说明  : PA非线性补偿
*****************************************************************************/
typedef struct
{
    UCOM_NV_POWER_STEP_ENUM_UINT16      enPowerStepMode;
    VOS_UINT16                          auhwValidCount[UCOM_NV_PA_GAIN_MAX_NUM];
    UCOM_NV_W_PA_NONLINEAR_STRU         astNonLinear[UCOM_NV_W_PA_NONLINEAR_NUM];
}UCOM_NV_W_PA_NONLINEAR_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_LOW_VOLT_SWITCH_THRESHOLD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/

typedef struct
{
    VOS_INT16                           shwStartPower;                          /* 降压门限,默认16dBm,范围0~22dBm */
    VOS_INT16                           shwStopPower;                           /* 升压门限,默认18dBm,范围0~22dBm */
}UCOM_NV_W_TX_LOW_VOLT_SWITCH_THRESHOLD_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_MAIL_BOX_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W邮箱配置
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwWcdmaMailBoxFlag;                 /* W邮箱方案，1:邮箱方案有效；0:无效 */
    VOS_UINT16                          uhwReserved;                /* 保留字节 */
}UCOM_NV_W_MAIL_BOX_CONFIG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TX_LOW_VOLT_SWITCH_THRESHOLD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwSlaveSampleNum;                      /* 从模分集模式切换的采样点数,默认为1 */
    VOS_UINT16                          uhwDrxIntraSampleNum;                   /* DRX本频分集模式切换的采样点数,默认为1 */
    VOS_UINT16                          uhwDrxInterSampleNum;                   /* DRX异频分集模式切换的采样点数,默认为1 */
    VOS_UINT16                          uhwFachIntraSampleNum;                  /* FACH本频分集模式切换的采样点数,默认为2 */
    VOS_UINT16                          uhwFachInterSampleNum;                  /* FACH异频分集模式切换的采样点数,默认为1 */
    VOS_UINT16                          uhwDchIntraSampleNum;                   /* DCH本频分集模式切换的采样点数,默认为10 */
    VOS_UINT16                          uhwDchInterSampleNum;                   /* DCH异频分集模式切换的采样点数,默认为1 */
    VOS_INT16                           shwMain2ScndThreshold;                  /* 发射主集切发射分集的门限，TX_MAIN_RSCP - TX_SCND_RSCP <= 门限，切换到发射分集，-48(-6dB,1/8dB精度) */
    VOS_INT16                           shwScnd2MainThreshold;                  /* 发射主集切发射分集的门限，TX_MAIN_RSCP - TX_SCND_RSCP > 门限，切换到发射分集，-16(-2dB,1/8dB精度) */
    VOS_INT16                           shwMeasValidThreshold;                  /* 测量值有效门限，-960(-120dB,1/8dB精度) */
    VOS_INT16                           uhwMeasNonEqualThreshold;               /* 测量值有效门限，|TX_MAIN_RSCP - TX_SCND_RSCP| > 门限，说明两个发射天线能量不均等,24(3dB,1/8dB精度) */
    VOS_UINT16                          uhwEvaTxEnable;                         /* 评估发射分集使能的标记，1表示使能、0表示不使能 */
}UCOM_NV_W_TX_DIV_MODE_EVALUATE_PARA_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_MAIN_ANT_ESTIMATE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 主天线评估NV参数
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwRssiThreshold;                       /* 启动双天线测量的RSSI门限(单位为0.125dbm) */
    VOS_INT16                           shwRscpThreshold;                       /* 启动双天线测量的RSCP门限(单位为0.125dbm) */
    VOS_UINT16                          uhwEstimateTime;                        /* 评估时间(单位为1ms) */
    VOS_UINT16                          uhwReserved;                            /* 四字节对齐 */
}UCOM_NV_W_MAIN_ANT_ESTIMATE_PARA_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_WCDMA_DUAL_ANT_COMPARE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 双天线比较状态NV参数
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwRscpThreshold[3];                    /* 各个阶段天线切换的RSCP门限(单位为0.125dbm) */
    VOS_UINT16                          uhwCompareTime[3];                      /* 各个阶段的双天线比较时间(单位为1ms) */
}UCOM_NV_W_DUAL_ANT_COMPARE_PARA_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_WCDMA_ANT_PROTECT_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 天线保护状态NV参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwFrozenTime;                          /* 进行主天线评估状态的冻结时间(单位为1ms) */
}UCOM_NV_W_ANT_PROTECT_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_BLIND_STATE_ONE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 盲切换阶段一评估NV参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwStateOneTime;                    /* 阶段一比较时间 */
    VOS_INT16                               shwWorstRscpValue;                  /* 最差RSCP信号门限值 */
    VOS_INT16                               shwWorseRscpValue;                  /* 较差RSCP信号门限值 */
    VOS_UINT16                              uhwDeltaRscpValue;                  /* 手握导致信号强度下降判决门限 */
}UCOM_NV_W_BLIND_STATE_ONE_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_DUAL_ANT_DPDT_PROTECT_TIME_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 天线交换DPDT开关保护时间控制字
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwPaOffToAntExchangeTime;          /* 关闭PA到输出DPDT信号时间 */
    VOS_UINT16                              uhwAntExchangeToPaOnTime;           /* 输出DPDT信号到打开PA时间 */
}UCOM_NV_DUAL_ANT_DPDT_PROTECT_TIME_STRU;



/*****************************************************************************
 结构名    : UCOM_NV_W_BLIND_STATE_TWO_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 盲切换阶段二评估NV参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwStateTwoTime;                    /* 阶段二比较时间 */
    VOS_UINT16                              uhwReserved;                        /* 保留字段 */
    VOS_UINT16                              auhwFrozenTime[4];                   /* 天线切换冻结保护时间 */
}UCOM_NV_W_BLIND_STATE_TWO_PARA_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_TAS_CTRL_WORD_PRE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 天线交换控制字
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwWcdmaAntPassThroughCtrlWord;      /* 天线直通时的GPIO控制字 */
    VOS_UINT32                              uwWcdmaAntSwapCtrlWord;             /* 天线交换时的GPIO控制字 */
}UCOM_NV_W_TAS_CTRL_WORD_PRE_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_TAS_CTRL_WORD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 天线交换控制字
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwWcdmaAntMasPassThroughTasPassThroughCtrlWord;      /* 天线MAS=0,TAS=0时的GPIO控制字 */
    VOS_UINT32                              uwWcdmaAntMasPassThroughTasSwapCtrlWord;             /* 天线MAS=0,TAS=1时时的GPIO控制字 */
    VOS_UINT32                              uwWcdmaAntMasSwapTasPassThroughCtrlWord;             /* 天线MAS=1,TAS=0时的GPIO控制字 */
    VOS_UINT32                              uwWcdmaAntMasSwapTasSwapCtrlWord;                    /* 天线MAS=1,TAS=1时时的GPIO控制字 */
}UCOM_NV_W_TAS_CTRL_WORD_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_TAS_NONBLIND_MEAS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAS明切测量的控制参量
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwAlpha;                           /* alpha滤波因子，滤波公式:shwFilterValue = shwFilterValue*(1-shwAlpha/10) + shwCurrentValue*shwAlpha/10; 其中shwAlpha = ( PHY_INT16)uhwAlpha*/
    VOS_UINT16                              uhwEvaluateTime;                    /* 评估时间(单位为1ms) */
    VOS_INT16                               shwRscpHighThd;                     /* 高门限 */
    VOS_INT16                               shwRscpLowThd;                      /* 低门限 */
    VOS_UINT16                              uhwCountLowThd;                     /* Low Count 计数 */
    VOS_UINT16                              uhwCountHighThd;                    /* High Count 计数 */
    VOS_UINT16                              uhwCountTotalThd;                   /* Total Count 计数  */
    VOS_UINT16                              uhReserve;                          /* 4字节对齐 */

}UCOM_NV_W_TAS_NONBLIND_MEAS_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_TAS_NONBLIND_MEAS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAS明切测量的控制参量
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwAlpha;                           /* alpha滤波因子 */
    UCOM_NV_W_ANT_PROTECT_PARA_STRU         stAntProtect;                       /* 天线保护阶段参量 */
    UCOM_NV_W_MAIN_ANT_ESTIMATE_PARA_STRU   stAntEstimate;                      /* 主天线评估参量 */
    UCOM_NV_W_DUAL_ANT_COMPARE_PARA_STRU    stAntCompare;                       /* 双天线比较参量 */
}UCOM_NV_W_TAS_NONBLIND_MEAS_PRE_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_TAS_BLIND_MEAS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAS盲切测量的控制参量
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwStateOneTime;                    /* 阶段一比较时间 */
    VOS_INT16                               shwWorstRscpValue;                  /* 最差RSCP信号门限值 */
    VOS_INT16                               shwWorseRscpValue;                  /* 较差RSCP信号门限值 */
    VOS_UINT16                              uhwDeltaRscpValue;                  /* 手握导致信号强度下降判决门限 */
    VOS_UINT16                              uhwStateTwoTime;                    /* 阶段二比较时间 */
    VOS_UINT16                              uhwDeltaRscpValuetest;                  /* 保留字段 */
    VOS_UINT16                              auhwFrozenTime[4];                  /* 天线切换冻结保护时间 */
}UCOM_NV_W_TAS_BLIND_MEAS_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TAS_PHY_STATE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAS物理层状态上报所需门限值
*****************************************************************************/
typedef struct
{
    VOS_INT16                               shwGoodRscpThres;                   /* 属于好信号RSCP门限值(单位为0.125dbm) */
    VOS_INT16                               shwPoorRscpThres;                   /* 属于差信号RSCP门限值(单位为0.125dbm) */
    VOS_UINT16                              uhwSFailNum;                        /* S准则连续失败次数 */
    VOS_UINT16                              uhwSPassNum;                        /* S准则连续成功次数 */
    VOS_UINT16                              uhwRachFailNum;                     /* 随即接入连续失败次数 */
    VOS_UINT16                              uhwFachEstimateTime;                /* fach态下评估间隔，以1ms为单位 */
}UCOM_NV_W_TAS_PHY_STATE_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TAS_SEARCHING_STATE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAS物理层Searching态参数
*****************************************************************************/
typedef struct
{
    VOS_INT16                               shwGoodRssiThres;                   /* 属于好信号RSSI门限值(单位为0.125dbm) */
    VOS_INT16                               shwPoorRssiThres;                   /* 属于差信号RSSI门限值(单位为0.125dbm) */
    VOS_UINT16                              uhwDeltaRssiValue;                  /* 天线比较能量差值(单位为0.125dbm)，大于等于此门限天线切换 */
    VOS_UINT16                              uhwReserved;                        /* 保留字段 */
}UCOM_NV_W_TAS_SEARCHING_STATE_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TAS_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAS算法控制参量
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_TAS_PHY_STATE_PARA_STRU       stTasPhyStatePara;                  /* 物理层状态上报参数门限 */
    UCOM_NV_W_TAS_SEARCHING_STATE_PARA_STRU stTasSearchingPara;                 /* 物理层搜网算法参数 */
    UCOM_NV_W_TAS_NONBLIND_MEAS_PRE_STRU    stTasNotBlindCtrl;                  /* TAS明切测量的控制参量 */
    UCOM_NV_W_TAS_BLIND_MEAS_STRU           stTasBlindCtrl;                     /* TAS盲切测量的控制参量*/
}UCOM_NV_W_TAS_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_TAS_RF_CTRL_STRU
 协议表格  :
 ASN.1描述 : auwBandBlindSwitchMap是针对每个band是否使用TAS盲切算法做的bitmap。
             auwBandBlindSwitchMap[0]bit0代表band1，bit1代表band2，以此类推。
             auwBandBlindSwitchMap[1]bit0代表band33，bit1代表band34，以此类推。
             bit位为1，代表此band使用盲切算法，否则反之。
 结构说明  : TAS射频相关控制参量
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              auwBandBlindSwitchMap[2];           /* BAND是否适用盲切 */
    UCOM_NV_W_TAS_CTRL_WORD_PRE_STRU        stTasCtrlWord;                      /* 天线切换控制字 */
}UCOM_NV_W_TAS_RF_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_HARQ_OUT_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HARQ外移配置NV结构
*****************************************************************************/
typedef struct
{
    UCOM_NV_BBP_HARQ_OUT_TYPE_ENUM_UINT16   enHarqOutType;                      /* HARQ外移类型 */
    VOS_UINT16                              uwReserve;
}UCOM_NV_HARQ_OUT_CONFIG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_DRX_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : WCDMA主从模DRX控制
*****************************************************************************/
typedef struct
{
    UCOM_NV_DRX_CTRL_ENUM_UINT16           enMasterDrxEnableFlag;               /* 主模DRX控制标志 */
    UCOM_NV_DRX_CTRL_ENUM_UINT16           enSlaveDrxEnableFlag;                /* 从模DRX控制标志 */
}UCOM_NV_W_DRX_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_GCF_INIT_GAIN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 双天线测量的控制参量
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwGsmRssiAgcSwitch;                /* GSM RSSI配置AGC初始增益开关 */
    VOS_UINT16                              uhwGsmRssiAgcGain;                  /* GSM RSSI AGC初始档位 */
}UCOM_NV_GSM_GCF_INIT_GAIN_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_VIRTUAL_BAND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM 虚拟频段使能标志和临界频点
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           uhwGsmVirtualBand;                     /* 0-不支持虚拟频段方案; 1-旧的虚拟频段方案；2-新的虚拟频段方案 */
    VOS_UINT16                           uhwGsmFreqBound;                       /* B3L和B3H频点号分界点 */
}UCOM_NV_GSM_VIRTUAL_BAND_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_TX_CTUNE_LUT_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM发射Ctune调试Lut参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           uhwGsmTxCtuneLutCtrl;
}UCOM_NV_GSM_TX_CTUNE_LUT_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_EXT_STRONG_NCELL_THRESHOLD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM邻区进入六强邻区的电平门限
*****************************************************************************/
typedef struct
{
    VOS_INT16                            shwGsmExtStrongNcellThresh;            /* GSM邻区进入六强邻区的电平门限 */
}UCOM_NV_GSM_EXT_STRONG_NCELL_THRESHOLD_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_SSC_CONFIG_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM SSC NV 参数配置
*****************************************************************************/
typedef struct
{
    VOS_UINT16                            uhwGsmSscSupportFlag;                /* GSM SSC开关控制 */
    VOS_UINT16                            uhwBlackThreshold;                   /* 黑名单小区变好的阈值 */
    VOS_UINT16                            uhwC2Threshold;                      /* 邻区C2值高于服务小区阈值 */
    VOS_UINT16                            uhwC1Threshold;                      /* 服务小区C1阈值 */
    VOS_UINT16                            uhwRxlevAThreshold;                  /* 服务小区接收电平阈值 */
    VOS_UINT16                            uhwReserved;
}UCOM_NV_GSM_SSC_CONFIG_PARA_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_WCDMA_TX_CTUNE_LUT_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : WCDMA发射Ctune调试Lut参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           uhwWcdmaTxCtuneLutCtrl;
}UCOM_NV_WCDMA_TX_CTUNE_LUT_CTRL_STRU;
/*****************************************************************************
 结构名    : UCOM_NV_CHANNEL_WBBP_GAP_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RFIC新增NV项,WBBP Gap操作通道配置参数,对应WBBP接口说明书"跨通道测量"
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwT1ForIdlePch;                                         /* idlepch态T1延迟配置,单位chip */
    VOS_UINT16          uhwT2ForIdlePch;                                         /* idlepch态T2延迟配置,单位chip */
    VOS_UINT16          uhwT3ForIdlePch;                                         /* idlepch态T3延迟配置,单位chip */
    VOS_UINT16          uhwT4ForIdlePch;                                         /* idlepch态T4延迟配置,单位chip */
    VOS_UINT16          uhwT1ForFach;                                            /* FACH态T1延迟配置,单位chip */
    VOS_UINT16          uhwT2ForFach;                                            /* FACH态T2延迟配置,单位chip */
    VOS_UINT16          uhwT3ForFach;                                            /* FACH态T3延迟配置,单位chip */
    VOS_UINT16          uhwT4ForFach;                                            /* FACH态T4延迟配置,单位chip */
    VOS_UINT16          uhwT1ForDch;                                             /* DCH态T1延迟配置,单位chip */
    VOS_UINT16          uhwT2ForDch;                                             /* DCH态T2延迟配置,单位chip */
    VOS_UINT16          uhwT3ForDch;                                             /* DCH态T3延迟配置,单位chip */
    VOS_UINT16          uhwT4ForDch;                                             /* DCH态T4延迟配置,单位chip */

}UCOM_NV_CHANNEL_WBBP_GAP_CONFIG_STRU;



/*****************************************************************************
 结构名    : UCOM_NV_WCDMA_CHANNEL_SWITCH_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RFIC新增NV项,通道交叉配置
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwRfSignalSwitch;                                      /* RF信号交叉 */
    VOS_UINT16          uhwMipiSignalSwitch;                                    /* MIPI信号交叉 */
    VOS_UINT16          uhwAbbTxSignalSwitch;                                   /* ABB TX信号交叉 */
    VOS_UINT16          uhwAbbRxSignalSwitch;                                   /* ABB RX信号交叉 */
    VOS_UINT16          uhwPmuSignalSwitch;                                     /* PMU信号交叉 */
    VOS_UINT16          uhwAptSignalSwitch;                                     /* APT信号交叉 */
}UCOM_NV_CHANNEL_SWITCH_CONFIG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_CHANNEL_UNBIND_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RFIC新增NV项,通道BAND不绑定配置
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwMipiUnbindEn;                                         /* MIPI非绑定使能 */
    VOS_UINT16          uhwMipiCh0Select;                                        /* MIPI通道0选择 */
    VOS_UINT16          uhwMipiCh1Select;                                        /* MIPI通道1选择 */
    VOS_UINT16          uhwAfcCh0Select;                                         /* AFC通道0选择 */
    VOS_UINT16          uhwAfcCh1Select;                                         /* AFC通道1选择 */
    VOS_UINT16          uhwAptCh0Select;                                         /* APT通道0选择 */
    VOS_UINT16          uhwAptCh1Select;                                         /* APT通道1选择 */
    VOS_UINT16          uhwPmuCh0Select;                                         /* PMU通道0选择 */
    VOS_UINT16          uhwPmuCh1Select;                                         /* PMU通道1选择 */
    VOS_UINT16          uhwAbbTxCh0Select;                                       /* ABB TX通道0选择,6363使用 */
    VOS_UINT16          uhwAbbTxCh1Select;                                       /* ABB TX通道1选择 6363使用*/

}UCOM_NV_CHANNEL_UNBIND_CONFIG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_MIPI_NOTCH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : mipi NOTCH 寄存器地址
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwCmdValidCnt;                     /* Nothc Mipi命令字个数，uhwNotchControlMode=2或者3时有效 */
    UCOM_NV_MIPI_CMD_STRU                   astMipiCmd[UCOM_NV_MIPI_NOTCH_CMD_NUMBER];/* Nothc MipiCmd，uhwNotchControlMode=2或者3时有效 */
    UCOM_NV_MIPI_BYTE_DATA_STRU             astMipiData[UCOM_NV_MIPI_NOTCH_DATA_NUMBER];     /* Nothc MipiData，uhwNotchControlMode=2或者3时有效 */
}UCOM_NV_GSM_MIPI_NOTCH_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_NOTCH_POWER_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  NOTCH POWER COMP
*****************************************************************************/
typedef struct
{
    VOS_INT16                               shwNotchPowerThreshold;             /* Notch发射功率大于该值时不进行发射功率补偿 */
    VOS_INT16                               shwNotchPowerComp;                  /* Notch发射功率补偿值 */
}UCOM_NV_GSM_NOTCH_POWER_COMP_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_NOTCH_CHAN_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 天线开关滤波器通道的控制
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwNotchSupportFlag;                /* DCS1800 TX NOTCH开关支持标志，1表示支持，0表示不支持 */
    VOS_UINT16                              uhwNotchControlMode;                /* NOTCH控制方式:1表示GPIO模式，2表示Mipi方式，3表示GPIO+MIPI组合方式 */
    VOS_UINT32                              uwNotchGpioSetValue;                /* Nothc GPIO控制值，uhwNotchControlMode=1或者3时有效 */
    VOS_UINT32                              uwNotchGpioDefaultValue;            /* Nothc GPIO控制值，uhwNotchControlMode=1或者3时有效 */
    UCOM_NV_GSM_MIPI_NOTCH_STRU             stNotchMipi;                        /* 天线NOTCH通道MIPI接口控制地址 */
    UCOM_NV_GSM_NOTCH_POWER_COMP_STRU       stNotchPowerComp;                   /* Notch发射功率补偿 */
}UCOM_NV_GSM_NOTCH_CHAN_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DFS新增NV项,动态调频参数,只修改合入V7R2和V9R1
*****************************************************************************/
typedef struct
{
    VOS_UINT32          uwDdrFreq;                                        /* DDR频率配置(单位KHz)  */
    VOS_UINT32          uwCcpuFreq;                                       /* CCPU频率配置(单位KHz) */
    VOS_UINT32          uwBusFreq;                                        /* 总线频率配置(单位KHz) */

}UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_MODEM_DFS_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DFS新增NV项,只修改合入V7R2和V9R1
*****************************************************************************/
typedef struct
{
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stCsCfg;                                          /* 语音模式下Profile设置值 */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stDrxCfg;                                         /* 待机模式下Profile设置值 */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stFachCfg;                                        /* FACH态下Profile设置值 */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stHspaCfg;                                        /* HSPA数据业务模式下Profile设置值 */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stR99PsCfg;                                       /* R99数据业务模式下Profile设置值 */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stSlaveWorkCfg;                                   /* 从模工作状态下Profile设置值 */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stSlaveSleepCfg;                                  /* 从模睡眠状态下Profile设置值 */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stMinCfg;                                         /* 最小的Profile设置值 */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stNoSignalCfg;                                    /* 非信令的Profile设置值 */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stReserved;                                       /* 保留的Profile设置值 */
}UCOM_NV_W_MODEM_DFS_CONFIG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_CS_INTRA_STEP23_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 本频三步法小区搜索参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwCsStep23SlotNum;                 /* DRX态本频三步法小区搜索step23的时隙头个数，初始值为1 */
    VOS_UINT16                              uhwCsStep23Period;                  /* DRX态本频三步法小区搜索周期，初始值为3072帧，即30.72s */
}UCOM_NV_W_CS_INTRA_STEP23_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_QPC_REGDEFAULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : QPC NV项
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      uhwDefaultCloseTime;                 /* 默认关闭时间     默认80(单位 帧)，0代表QPC未使能 */
    VOS_UINT16                      uhwDefaultGuardTime;                 /* 默认保护开启时长 默认20(单位 帧) */
    VOS_UINT16                      uhwDefaultOpenTime;                 /* 默认数据触发时长 默认40(单位 帧) */

    VOS_UINT16                      uhwReserve;
}UCOM_NV_QPC_REGDEFAULT_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_G_MODEM_DFS_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DFS新增NV项,只修改合入V7R2和V9R1
*****************************************************************************/
typedef struct
{
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stCsCfg;                                          /* 语音业务模式下Profile设置值 */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stPsCfg;                                          /* 数据业务模式下Profile设置值 */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stDrxCfg;                                         /* 待机模式下Profile设置值 */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stTuningCfg;                                      /* tuning dch状态下Profile设置值 */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stSearchingCfg;                                   /* 搜网模式下设置值 */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stSlaveWorkCfg;                                   /* 从模工作状态下Profile设置值 */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stSlaveSleepCfg;                                  /* 从模睡眠状态下Profile设置值 */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stMinCfg;                                         /* 最小的Profile设置值 */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stNoSignalCfg;                                    /* 非信令的Profile设置值 */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stReserved;                                       /* 保留的Profile设置值 */

}UCOM_NV_G_MODEM_DFS_CONFIG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_TUNER_GPIO_VALUE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 作为gpio tuner使用，暂不区分Tx/Rx，预留resvered bit用于扩展。
             生效的时间(Tx:Nv可配置，RX:提前150us)。
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwGpio;                         /* 对应前端线控 */
    VOS_UINT32                                  uwResvered;
}UCOM_NV_GSM_TUNER_GPIO_VALUE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_PHASE_ERROR_STANDARD_MODE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CMU使用standard模式测试gmsk phase error时，需要配置次NV项为1。
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwMode;                                                /* CMU使用standard模式测试gmsk phase error时，需要配置次NV项为1 */
}UCOM_NV_GSM_PHASE_ERROR_STANDARD_MODE_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_RF_INTERFERE_CONTROL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 控制TDS/LTE的天线开关,目的是避免B39和B3H的干扰
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwFuncOn;                      /* 0-不使能，1-使能 */
    VOS_UINT32                                  uwGpioMask;                     /* 线控清除 */
    VOS_UINT32                                  uwGpioRxValue;                  /* 关闭TDS/LTE发射的线控 */
    VOS_UINT32                                  uwGpioDefaultValue;             /* TDS/LTE发射的线控默认值 */
}UCOM_NV_GSM_RF_INTERFERE_CONTROL_STRU;



/*****************************************************************************
 结构名    : UCOM_NV_PA_MIPI_WORD_STRU
 协议表格  :
 结构说明  : 用于一些mipi功能公共指令定义
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU                   astMipiCmd[UCOM_NV_PA_MIPI_CMD_MAX_NUM];
    UCOM_NV_MIPI_BYTE_DATA_STRU             astMipiData[UCOM_NV_PA_MIPI_DATA_MAX_NUM];
}UCOM_NV_PA_MIPI_WORD_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_RFFE_MIPI_PA_CTRL_STRU
 协议表格  :
 结构说明  : PA的MIPI指令
*****************************************************************************/
typedef struct
{
    UCOM_NV_PA_MIPI_WORD_STRU               stMipiPaOn;
    UCOM_NV_PA_MIPI_WORD_STRU               stMipiPaOff;
    UCOM_NV_PA_MIPI_WORD_STRU               stMipiPaGainH;
    UCOM_NV_PA_MIPI_WORD_STRU               stMipiPaGainM;
    UCOM_NV_PA_MIPI_WORD_STRU               stMipiPaGainL;
}UCOM_NV_W_RFFE_MIPI_PA_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_ET_MIPI_WORD_STRU
 协议表格  :
 结构说明  : 用于一些mipi功能公共指令定义
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU                   astMipiCmd[UCOM_NV_ET_MIPI_CMD_MAX_NUM];
    UCOM_NV_MIPI_BYTE_DATA_STRU             astMipiData[UCOM_NV_ET_MIPI_DATA_MAX_NUM];
}UCOM_NV_ET_MIPI_WORD_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_RFFE_MIPI_ET_CTRL_STRU
 协议表格  :
 结构说明  : Et的MIPI指令
*****************************************************************************/
typedef struct
{
    UCOM_NV_ET_MIPI_WORD_STRU               stMipiEtOn;                         /* ET器件打开mipi控制字 */
    UCOM_NV_ET_MIPI_WORD_STRU               stMipiEtOff;                        /* ET器件关闭mipi控制字 */
    UCOM_NV_ET_MIPI_WORD_STRU               stMipiEtMode;                       /* ET器件配置为ET 模式mipi控制字 */
    UCOM_NV_ET_MIPI_WORD_STRU               stMipiMAptMode;                     /* ET器件配置为M APT 模式mipi控制字 */
    UCOM_NV_ET_MIPI_WORD_STRU               stMipiLAptMode;                     /* ET器件配置为L APT 模式mipi控制字 */
}UCOM_NV_W_RFFE_MIPI_ET_CTRL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_MIPI_SINGLE_CMD_STRU
 协议表格  :
 结构说明  : 指供一个MIPI指令的结构
*****************************************************************************/
typedef struct
{
    UCOM_NV_MIPI_CMD_STRU                   stMipiCmd;
    UCOM_NV_MIPI_BYTE_DATA_STRU             stMipiData;
}UCOM_NV_MIPI_SINGLE_CMD_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_G_MIPI_PA_TIMING_STRU
 协议表格  :
 结构说明  : MIPI PA timing
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  uhwMipiPaInitTiming;
    VOS_UINT16                  uhwMipiPaGainSetTiming;
    VOS_UINT16                  uhwMipiPaTrigTiming;
    VOS_UINT16                  uhwMipiPaOffTiming;
    VOS_UINT16                  uhwMipiPaMultiSlotGainSetTiming;
    VOS_UINT16                  uhwMipiPaMultiSlotTrigTiming;
    VOS_UINT16                  uhwResvered3;
    VOS_UINT16                  uhwResvered2;
    VOS_UINT16                  uhwResvered1;
    VOS_UINT16                  uhwResvered0;
}UCOM_NV_G_MIPI_PA_TIMING_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_G_RFFE_MIPI_PA_CTRL_STRU
 协议表格  :
 结构说明  : PA的MIPI指令
*****************************************************************************/
typedef struct
{
    UCOM_NV_G_MIPI_PA_TIMING_STRU           stGsmMipiPaTiming;
    UCOM_NV_G_MIPI_PA_TIMING_STRU           stEdgeMipiPaTiming;
    UCOM_NV_PA_MIPI_WORD_STRU               stMipiPaInit;
    UCOM_NV_PA_MIPI_WORD_STRU               astGsmMipiPaPclGain[UCOM_NV_GSM_LINEAR_PA_GAIN_NUM];
    UCOM_NV_PA_MIPI_WORD_STRU               astEdgeMipiPaPclGain[UCOM_NV_GSM_LINEAR_PA_GAIN_NUM];
    UCOM_NV_PA_MIPI_WORD_STRU               stMipiPaTrigger;
    UCOM_NV_PA_MIPI_WORD_STRU               stMipiPaOff;
}UCOM_NV_G_RFFE_MIPI_PA_CTRL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : mipi ant 寄存器控制字
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU               astAntMipiCmd[UCOM_NV_MAX_MIPI_ANT_CMD_NUMBER];
    UCOM_NV_MIPI_BYTE_DATA_STRU         astAntMipiData[UCOM_NV_MAX_MIPI_ANT_DATA_NUMBER];
}UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_ANT_SWITCH_MIPI_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : mipi ant 寄存器控制字
*****************************************************************************/
typedef struct
{
    UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU      stMainAntMipiCtrl;
    UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU      stDivAntMipiCtrl;
}UCOM_NV_W_ANT_SWITCH_MIPI_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_G_ANT_SWITCH_MIPI_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : mipi ant 寄存器控制字
*****************************************************************************/
typedef struct
{
    UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU      stOpenRxAntMipiCtrl;
    UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU      stOpenTxAntMipiCtrl;
    UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU      stCloseRxAntMipiCtrl;
    UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU      stCloseTxAntMipiCtrl;
}UCOM_NV_G_ANT_SWITCH_MIPI_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_DSDS_PS_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : V8R1 DSDS新增NV项，用来配置DSDS模式下GSM各个任务向RCM申请RF资源时的任务抢占参数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwPsPrmptPeriod;                /* PS无限长任务的抢占统计周期，单位32K系统时钟CLK个数，默认值:0x1fffffff */
    VOS_UINT32                                  uwPsPrmptTimeThd;               /* PS无限长任务单次被抢占时间门限，单位32K系统时钟CLK个数，默认值:0x1fffffff */
    VOS_UINT32                                  uwPsTotalPrmptTimeThd;          /* PS无限长任务周期内累计被抢占时间门限，单位32K系统时钟CLK个数，默认值:0x1fffffff */
    VOS_UINT32                                  uwReserved1;                    /* 保留1 */
    VOS_UINT16                                  uhwReserved2;                   /* 保留2 */
    VOS_UINT16                                  uhwReserved3;                   /* 保留3 */
}UCOM_NV_GSM_DSDS_PS_CONFIG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_PHY_MODE_DSDS_FLAG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : V8R1 DSDS新增NV项,单卡情况下配置为0，双卡情况下用来区分DSDA和DSDS
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                 uhwGsmDsdsFlag;                  /* 单卡必须配置为0，双卡条件下 0:代表DSDA,1:代表DSDS */
    VOS_UINT16                                 uhwWcdmaDsdsFlag;                /* 单卡必须配置为0，双卡条件下 0:代表DSDA,1:代表DSDS */
    VOS_UINT16                                 uhwRsvDsdsFlag;                  /* 保留 */
}UCOM_NV_PHY_MODE_DSDS_FLAG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_ANT_SHARE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 共天线使能标志
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwAntShareEn;                  /* 0-不支持; 1-支持 */
}UCOM_NV_ANT_SHARE_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_VIRTUAL_BAND_ANT_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 虚拟频段的天线开关配置
*****************************************************************************/
typedef struct
{
    UCOM_NV_RF_CONFIG_STRU                      stGsmVirtualBandRfConfig;       /* 虚拟频段的天线开关配置 */
}UCOM_NV_GSM_VIRTUAL_BAND_ANT_CONFIG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_PHY_MODE_DSDS_FLAG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : V8R1 DSDS新增NV项,上行调制数字滤波使能
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                 uhwGsmTxLpfEn;                   /* 上行调制数字滤波使能 0:代表不使能,1:代表使能 */
    VOS_UINT16                                 uhwRsv;                          /* 保留 */
}UCOM_NV_GSM_TX_LPF_EN_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_TAS_CTRL_WORD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM双天线切换GPIO控制字
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           uwGsmAntThroughCtrlWord;               /* 主天线的GPIO控制字 */
    VOS_UINT32                           uwGsmAntSwapCtrlWord;                  /* 辅天线的GPIO控制字 */
    VOS_UINT32                           uwGsmDualAntClearMask;                 /* 天线控制清除掩码 */
}UCOM_NV_GSM_TAS_CTRL_WORD_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_TAS_CTRL_WORD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM双天线切换TAS+MAS GPIO控制字
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           uwGsmAntTasOnlyThroughCtrlWord;        /* 天线00(TAS=0 MAS=0)的GPIO控制字 */
    VOS_UINT32                           uwGsmAntTasOnlySwapCtrlWord;           /* 天线01(TAS=1 MAS=0)的GPIO控制字 */
    VOS_UINT32                           uwGsmAntMasThroughCtrlWord;            /* 天线10(TAS=0 MAS=1)的GPIO(G0、G1不同) */
    VOS_UINT32                           uwGsmAntMasSwapCtrlWord;               /* 天线11(TAS=1 MAS=1)的GPIO控制字(G0、G1不同) */
    VOS_UINT32                           uwGsmDualAntClearMask;                 /* 天线控制清除掩码(G0、G1不同) */
}UCOM_NV_GSM_TAS_MAS_CTRL_WORD_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_MAS_BAND_SUPPORT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 频段是否支持Ia、Ib(Ia指TAS_DPDT=passthrough的MAS比较状态,Ib指TAS_DPDT=swap的MAS比较状态)
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           uhwGsmMasBandSupportIa;                /* 频段是否支持Ia(低4 bit表示GSM四个频段 0-不支持 1-支持) */
    VOS_UINT16                           uhwGsmMasBandSupportIb;                /* 频段是否支持Ib(低4 bit表示GSM四个频段 0-不支持 1-支持) */
}UCOM_NV_GSM_MAS_BAND_SUPPORT_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_TAS_RF_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM双天线切换Rf参数
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_TAS_MAS_CTRL_WORD_STRU      stGsmTasMasCtrlWord;                /* TAS MAS DPDT GPIO控制字 */
    UCOM_NV_GSM_MAS_BAND_SUPPORT_STRU       stGsmMasBandSupport;                /* 频段是否支持Ia、Ib */
}UCOM_NV_GSM_TAS_RF_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_PRI_ANT_ESTIMATE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 双天线切换主天线能量评估阶段参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwGsmAntEstimatePeriodNum;         /* 统计周期个数 */
    VOS_INT16                               shwGsmAntEstimatePowerCmpThreshold; /* 能量判决门限 */
}UCOM_NV_GSM_PRI_ANT_ESTIMATE_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_DUAL_ANT_COMPARE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 双天线切换主辅天线能量比较阶段参数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwGsmAntCompareCollectTime;         /* 采集时间 */
    VOS_UINT16                              uhwGsmAntCompareFirstPeriodNum;     /* 状态1的统计周期个数 */
    VOS_UINT16                              uhwGsmAntCompareSecondPeriodNum;    /* 状态2的统计周期个数 */
    VOS_UINT16                              uhwGsmAntCompareThirdPeriodNum;     /* 状态3的统计周期个数 */
    VOS_INT16                               shwGsmAntCompareFirstPowerCmpThreshold;  /* 状态1的能量判决门限 */
    VOS_INT16                               shwGsmAntCompareSecondPowerCmpThreshold; /* 状态2的能量判决门限 */
    VOS_INT16                               shwGsmAntCompareThirdPowerCmpThreshold;  /* 状态3的能量判决门限 */
}UCOM_NV_GSM_DUAL_ANT_COMPARE_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_DUAL_ANT_CS_DCH_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CS_DCH双天线切换参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwGsmDualAntAlphaPara;             /* 双天线切换平滑滤波系数 */
    VOS_UINT16                              uhwRsv;
    UCOM_NV_GSM_PRI_ANT_ESTIMATE_PARA_STRU  stGsmPriAntEstimatePara;            /* 双天线切换主天线能量评估阶段参数 */
    UCOM_NV_GSM_DUAL_ANT_COMPARE_PARA_STRU  stGsmDualAntComparePara;            /* 双天线切换主辅天线能量比较阶段参数 */
    VOS_UINT32                              uwGsmAntHandleDelayPara;            /* 双天线切换后的迟滞参数 */
}UCOM_NV_GSM_DUAL_ANT_CS_DCH_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_DUAL_ANT_ACCESS_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ACCESS态双天线切换参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwRaCntThreshold;                  /* RA次数门限 */
    VOS_UINT16                              uhwRsv;
}UCOM_NV_GSM_DUAL_ANT_ACCESS_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_DUAL_ANT_IDLE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IDLE态双天线切换参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwC1FailCntThreshold;              /* C1_fail事件判决次数门限 */
    VOS_UINT16                              uhwC1PassCntThreshold;              /* C1_pass事件判决次数门限 */
}UCOM_NV_GSM_DUAL_ANT_IDLE_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_TAS_SEARCHING_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SEARCHING态双天线切换参数
*****************************************************************************/
typedef struct
{
    VOS_INT16                              shwQualityLowThreshold;              /* TAS_SEARCHING态测量结果低门限 */
    VOS_INT16                              shwQualityHighThreshold;             /* TAS_SEARCHING态测量结果高门限 */
    VOS_INT16                              shwDiffValue;                        /* TAS_SEARCHING态测量结果差值 */
    VOS_UINT16                             uhwRsv;
}UCOM_NV_GSM_TAS_SEARCHING_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_TAS_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 双天线切换参数
*****************************************************************************/
typedef struct
{
    VOS_INT16                               shwSignalPoorThreshold;             /* 上报RCM信号POOR门限 */
    VOS_INT16                               shwSignalGoodThreshold;             /* 上报RCM信号GOOD门限 */
    UCOM_NV_GSM_DUAL_ANT_CS_DCH_PARA_STRU   stGsmDualAntCsDchPara;              /* 双天线切换CSDCH参数 */
    UCOM_NV_GSM_DUAL_ANT_ACCESS_PARA_STRU   stGsmDualAntAccessPara;             /* 双天线切换ACCESS参数 */
    UCOM_NV_GSM_DUAL_ANT_IDLE_PARA_STRU     stGsmDualAntIdlePara;               /* 双天线切换IDLE参数 */
    UCOM_NV_GSM_TAS_SEARCHING_PARA_STRU     stGsmDualAntSearchingPara;          /* 双天线切换SEARCHING参数 */
}UCOM_NV_GSM_TAS_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_DUAL_ANT_ESTIMATE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 双天线切换主天线能量评估阶段参数
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_PRI_ANT_ESTIMATE_PARA_STRU      stActiveTasEstimate;            /* 主控的评估阶段参数 */
    UCOM_NV_GSM_PRI_ANT_ESTIMATE_PARA_STRU      stPassiveMasEstimate;           /* 被控MAS的评估阶段参数 */
}UCOM_NV_GSM_TAS_MAS_ESTIMATE_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_TAS_MAS_SUB_COMPARE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : compare阶段参数，包括主控 Ia Ib II IIa，被控Ia Ib
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwGsmAntCompareCollectTime;         /* 采集时间 */
    VOS_UINT16                              uhwGsmDualAntAlphaPara;             /* 双天线切换平滑滤波系数 */
    VOS_UINT16                              uhwCountTotalNum;                   /* 总的上报周期计数门限 */
    VOS_UINT16                              uhwCountHighNum;                    /* 差值高门限计数门限 */
    VOS_UINT16                              uhwCountLowNum;                     /* 总的上报周期计数门限 */
    VOS_INT16                               shwCountHighPowerDletaThreshold;    /* 高门限计数的能量差值门限 */
    VOS_INT16                               shwCountLowPowerDletaThreshold;     /* 低门限计数的能量差值门限 */
}UCOM_NV_GSM_TAS_MAS_SUB_COMPARE_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_ACTIVE_TAS_COMPARE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 主控TAS的比较阶段NV参数
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_TAS_MAS_SUB_COMPARE_PARA_STRU  stMasStateIaPara;
    UCOM_NV_GSM_TAS_MAS_SUB_COMPARE_PARA_STRU  stMasStateIbPara;
    UCOM_NV_GSM_TAS_MAS_SUB_COMPARE_PARA_STRU  stTasStateIIPara;
}UCOM_NV_GSM_ACTIVE_TAS_COMPARE_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_PASSIVE_MAS_COMPARE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 被控MAS的比较阶段NV参数
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_TAS_MAS_SUB_COMPARE_PARA_STRU  stMasStateIaPara;
    UCOM_NV_GSM_TAS_MAS_SUB_COMPARE_PARA_STRU  stMasStateIbPara;
}UCOM_NV_GSM_PASSIVE_MAS_COMPARE_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_DUAL_ANT_COMPARE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : compare切换参数
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwGoodEnoughPowerThreshold;    /* 天线足够好能量门限 */
    VOS_UINT16                                  uhwRsv;
    UCOM_NV_GSM_ACTIVE_TAS_COMPARE_PARA_STRU    stActiveTasComparePara;         /* 主控TAS的比较阶段参数 */
    UCOM_NV_GSM_PASSIVE_MAS_COMPARE_PARA_STRU   stPassiveMasComparePara;        /* 被控MAS的比较阶段参数 */
}UCOM_NV_GSM_TAS_MAS_COMPARE_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_DUAL_ANT_DELAY_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DELAY参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwActiveTasDelayPara;              /* 主控TAS的迟滞参数,单位ms */
    VOS_UINT16                              uhwPassiveMasDelayPara;             /* 被控MAS的迟滞参数,单位ms */
}UCOM_NV_GSM_TAS_MAS_DELAY_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_DUAL_ANT_CS_DCH_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CS_DCH双天线切换参数
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_TAS_MAS_ESTIMATE_PARA_STRU  stGsmPriAntEstimatePara;            /* 双天线切换主天线能量评估阶段参数 */
    UCOM_NV_GSM_TAS_MAS_COMPARE_PARA_STRU   stGsmDualAntComparePara;            /* 双天线切换主辅天线能量比较阶段参数 */
    UCOM_NV_GSM_TAS_MAS_DELAY_PARA_STRU     stGsmDualAntDelayPara;              /* 双天线切换后的迟滞参数 */
}UCOM_NV_GSM_TAS_MAS_CS_DCH_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_TAS_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 双天线切换参数
*****************************************************************************/
typedef struct
{
    VOS_INT16                               shwSignalPoorThreshold;             /* 上报RCM信号POOR门限 */
    VOS_INT16                               shwSignalGoodThreshold;             /* 上报RCM信号GOOD门限 */
    UCOM_NV_GSM_TAS_MAS_CS_DCH_PARA_STRU    stGsmDualAntCsDchPara;              /* TAS+MAS双天线切换CSDCH参数(TAS MAS内部区分) */
    UCOM_NV_GSM_DUAL_ANT_ACCESS_PARA_STRU   stGsmDualAntAccessPara;             /* 双天线切换ACCESS参数(TAS MAS共用) */
    UCOM_NV_GSM_DUAL_ANT_IDLE_PARA_STRU     stGsmDualAntIdlePara;               /* 双天线切换IDLE参数(TAS MAS共用) */
    UCOM_NV_GSM_TAS_SEARCHING_PARA_STRU     stGsmDualAntSearchingPara;          /* 双天线切换SEARCHING参数(TAS MAS共用) */
}UCOM_NV_GSM_TAS_MAS_SCHL_PARA_STRU;

/*****************************************************************************
结构名    : UCOM_NV_W_CS_ANT2_CTRL_STRU
结构说明  :
对应NVID:

  1.日    期   : 2014年12月30日
    作    者   : z68255
    修改内容   : 初始生成
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwCsAnt2AutoSwitch;                    /* 语音动态分集开关 */
    VOS_UINT16                          uhwFrameThreshold;                      /* Frame判决门限  */
    VOS_INT16                           shwSirOpenThreshold;                    /* SIR统计法Open判决门限，单位0.01db */
    VOS_INT16                           shwTpcOpenThreshold;                    /* TPC统计法Open判决门限，百分比*100 */
    VOS_INT16                           shwSirCloseThreshold;                   /* SIR统计法Close判决门限，单位0.01db  */
    VOS_UINT16                          uhwErrBlocksToClose;                    /*BLER方法关分集判决时错误块达到目标误块比例的门限，百分比*100*/
    VOS_UINT16                          uhwErrBlocksToOpen;                     /*BLER方法开分集判决时错误块达到目标误块比例的门限，百分比*100*/
    VOS_UINT16                          uhwSnapNumberToJudge;                   /*BLER方法判决时窗内所需最小统计块数*/
    VOS_UINT16                          uhwBlerJudgeFlag;                       /*1为BLER方法，0为SIR方法*/
    VOS_UINT16                          uhwErrorSnapClose;                      /*BLER方法关分集判决时快拍误块个数门限*/
    VOS_UINT16                          uhwErrorSnapOpen;                       /*BLER方法开分集判决时快拍误块个数门限*/
    VOS_UINT16                          uhwRsv0;                                /*保留*/
}UCOM_NV_W_CS_ANT2_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_IDLE_ANT2_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : WCDMA动态分集控制
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwIdleAnt2AutoSwitch;                  /* IDLE动态分集开关 */
    VOS_INT16                           shwRSCPThreshold;                       /* RSCP门限,按照1/8精度限幅 */
    VOS_INT16                           shwECN0Threshold;                       /* ECN0门限,按照1/8精度限幅 */
    VOS_UINT16                          uhwAlphaThreshold;                      /* Alpha filter 门限 */
}UCOM_NV_W_IDLE_ANT2_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_T313_BACK_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : T313回退值控制
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwT313BackEn;                          /* T313回退控制开关 */
    VOS_UINT16                          uhwT313BackValue;                       /* T313回退值，单位10ms */
    VOS_UINT16                          uhwT313MinValue;                        /* T313最小值，单位10ms */
    VOS_UINT16                          uhwReserved;                            /* 保留 */
}UCOM_NV_W_T313_BACK_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_SYNC_MODULE_OPTIMIZE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 同失步模块优化参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwCloseUlDelayTime;                    /* 失步后延迟关闭上行的时间，单位为10ms，0为优化关闭 */
    VOS_UINT16                          uhwQinQoutOptimizeSwitch;               /* QinQout门限优化开关,0为优化关，1为优化开 */
}UCOM_NV_W_SYNC_MODULE_OPTIMIZE_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_FET_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : FET控制NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwFetEnable;                           /* FET特性开关:关闭为0,打开为1 */
    VOS_UINT16                          uhwTestEnable;                          /* FET测试开关:关闭为0,打开为1,打开的情况下可以在测试模式下打开FET */
    VOS_UINT16                          uhwForceOpenRxEnable;                   /* 下行强开开关:不强开为0,强开为1 */
    VOS_INT16                           shwRxOpenPowerThresh;                   /* 下行打开功率门限, 单位0.1dBm */
    VOS_INT16                           shwRxClosePowerThresh;                  /* 下行关闭功率门限, 单位0.1dBm */
    VOS_UINT16                          uhwRxOpenPowerEvaCntThresh;             /* 下行关闭到打开功率持续评估长度门限, 单位帧 */
    VOS_INT16                           shwRxOpenRscpThresh;                    /* 下行打开RSCP门限, 单位0.125dBm */
    VOS_INT16                           shwRxCloseRscpThresh;                   /* 下行关闭RSCP门限, 单位0.125dBm */
    VOS_INT16                           shwRxOpenEcn0Thresh;                    /* 下行打开Ecn0门限, 单位0.125dBm */
    VOS_INT16                           shwRxCloseEcn0Thresh;                   /* 下行关闭Ecn0门限, 单位0.125dBm */
    VOS_UINT16                          uhwRxOpenEnergyEvaCntThresh;            /* 下行关闭到打开能量持续评估长度门限, 单位帧 */
    VOS_INT16                           shwOlpcSirTargetDelta;                  /* 外环功控SirTarget调整值, 单位0.01dBm */
}UCOM_NV_W_FET_CTRL_STRU;



/*****************************************************************************
 结构名    : UCOM_NV_GSM_PCH_DUMMY_DETECT_FLAG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : V8R1 dummy_pch检测控制结构该flag=0时 不开启dummyPch检测 =1时开启。
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwGsmPchDummyDetectFlag;           /* dummy_pch检测开启标志位 */

}UCOM_NV_GSM_PCH_DUMMY_DETECT_FLAG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_PA_TEMP_DET_CHANNEL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W PA温度检测通道
*****************************************************************************/
typedef struct
{
    VOS_INT16                               sChannel;
    VOS_UINT16                              usResvered;
}UCOM_NV_W_PA_TEMP_DET_CHANNEL_STRU;

typedef UCOM_NV_W_PA_TEMP_DET_CHANNEL_STRU UCOM_NV_CDMA_PA_TEMP_DET_CHANNEL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_PA_TEMP_DET_CHANNEL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : G PA温度检测通道
*****************************************************************************/
typedef struct
{
    VOS_INT16                               sChannel;
    VOS_UINT16                              usResvered;
}UCOM_NV_GSM_PA_TEMP_DET_CHANNEL_STRU;



/*****************************************************************************
 结构名    : UCOM_NV_GSM_DRX_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM主从模DRX控制
*****************************************************************************/
typedef struct
{
    UCOM_NV_DRX_CTRL_ENUM_UINT16       enMasterDrxEnableFlag;               /* 主模允许睡眠 */
    UCOM_NV_DRX_CTRL_ENUM_UINT16       enSlaveDrxEnableFlag;                /* 从模允许睡眠 */
}UCOM_NV_GSM_DRX_CTRL_STRU;



/*****************************************************************************
 结构名    : UCOM_NV_RF_RX_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :2.1表示支持的3G和2G频段、3G分集支持情况、每个频段与RF
            通道对应关系天线开关切换选择、DBB对3GPA的控制
*****************************************************************************/
typedef struct
{

    VOS_UINT16                          uhwRfSsiChannel;                    /* RFIC选择*/

    VOS_UINT16                          uhwRfOutPortGroup;                     /* RFIC输出主分集通道选择*/

    VOS_UINT16                          uhwRfMainPort;                          /* RFIC输出主集所在端口选择*/

    VOS_UINT16                          uhwAbbChannel;                      /* ABB通道选择 */

    VOS_UINT16                          uhwAbbMainPath;                         /* ABB通道内，主分集路径选择*/

    VOS_UINT16                          uhwMixerSel;                        /* Mixer选择，通过选group来实现*/

    VOS_UINT16                          uhwPllSel;                          /* PLL选择 */

    VOS_UINT16                          uhwReserved;

}UCOM_NV_RF_RX_CONFIG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_RF_TX_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :2.1表示支持的3G和2G频段、3G分集支持情况、每个频段与RF
            通道对应关系天线开关切换选择、DBB对3GPA的控制
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwAbbChannel;                      /* ABB通道选择 */

    VOS_UINT16                          uhwRfSsiChannel;                    /* RFIC选择*/

    VOS_UINT16                          uhwFbPin;                           /* RFIC跟Tx绑定，FB Band pin,0:FB1,1:FB2 */

    VOS_UINT16                          uhwReserved;
}UCOM_NV_RF_TX_CONFIG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_RF_TRX_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :2.1表示支持的3G和2G频段、3G分集支持情况、每个频段与RF
            通道对应关系天线开关切换选择、DBB对3GPA的控制
*****************************************************************************/
typedef struct
{
    UCOM_NV_RF_RX_CONFIG_STRU           stRfRxConfig;

    UCOM_NV_RF_TX_CONFIG_STRU           stRfTxConfig;

}UCOM_NV_RF_TRX_CONFIG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_RX_IQ_MISMATCH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM接收振幅校正因子，相位校正因子
             正常工作时，将此参数配置给DBB，对RX通道进行预畸变以弥补下行通道
             的IQ mismatch。
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwAmplitude;                           /* 振幅校正因子，+-511 */
    VOS_INT16                           shwPhase;                               /* 相位校正因子，+-1023 */
}UCOM_NV_GSM_RX_IQ_MISMATCH_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_HD3_HD5_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :存放一个点的HD3/HD5校准值
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwBr;                                  /* HD3校准值实部 */
    VOS_INT16                           shwBi;                                  /* HD3校准值虚部 */
    VOS_INT16                           shwCr;                                  /* HD5校准值实部 */
    VOS_INT16                           shwCi;                                  /* HD5校准值虚部 */
}UCOM_NV_GSM_HD3_HD5_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_HD3_HD5_PCL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :存放一个频点的HD3/HD5校准值
*****************************************************************************/
typedef struct
{
    /* 分别存放Max_PCL、Max_PCL+1、Max_PCL+2三个功率等级的HD3/HD5校准结果 */
    UCOM_NV_GSM_HD3_HD5_STRU            astPclHd3Hd5[UCOM_NV_GSM_TX_HD35_PCL_NUM];
}UCOM_NV_GSM_HD3_HD5_PCL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_HD35_ARFCN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :存放一个频段的HD3/HD5校准值
            Br = 1/(A^2) ，(A为测试信号的浮点峰值)。算法进行定点化方式如下：
            假设测试信号的RMS值为282mv，则其峰值A = 282*sqrt(2)mv
            对于HD3，Br =1/(A^2)=2^11/((0.282*√2)^2)=12877
            对于HD5，Cr =1/(A^4)=2^8/((0.282*√2))^4)=10121
*****************************************************************************/
typedef struct
{

    VOS_UINT16                          auhwArfcn[UCOM_NV_GSM_TX_HD35_ARFCN_NUM];           /* 信号低中高三个频点,包含频段 */
    VOS_UINT16                          uhwReserved;

}UCOM_NV_GSM_HD35_ARFCN_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_TX_HD3_HD5_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :存放一个频段的HD3/HD5校准值
            Br = 1/(A^2) ，(A为测试信号的浮点峰值)。算法进行定点化方式如下：
            假设测试信号的RMS值为282mv，则其峰值A = 282*sqrt(2)mv
            对于HD3，Br =1/(A^2)=2^11/((0.282*√2)^2)=12877
            对于HD5，Cr =1/(A^4)=2^8/((0.282*√2))^4)=10121
*****************************************************************************/
typedef struct
{

    UCOM_NV_GSM_HD3_HD5_PCL_STRU        astChannelHd3Hd5[UCOM_NV_GSM_TX_HD35_ARFCN_NUM];    /* 分别存放低、中、高三个频点的校准结果 */

}UCOM_NV_GSM_TX_HD3_HD5_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_TX_IQ_SELF_CAL_6362_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :Tx 自校准NV
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTxLoLeakageDciFixed;                 /*校准Lo Leakage时，配置的I路直流值*/

    VOS_UINT16                          uhwTxIqMismatchCalCntMax;               /*IQ Mismatch最大校准次数*/

    VOS_UINT32                          uwTxLoLeakageCorrErrThrd;               /*校准Lo Leakage时相关失败门限*/

    VOS_UINT32                          uwTxIqMismatchIrStopThrd;               /*IQ Mismatch校准停止门限*/

    VOS_UINT32                          uwTxIqMismatchIrFailThrd;               /*IQ Mismatch校准失败门限*/

}UCOM_NV_TX_IQ_SELF_CAL_6362_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_HD35_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Hd35自校准相关参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwCouplerEn;                           /* Coupler外部环回还是Rfic内部环回，1--Coupler外部环回，0--Rfic内部环回 */
    VOS_UINT16                          uhwLowBandScale;                        /* 低频段校准值作为最终补偿值需要相乘的系数，由硬件人员提取 */
    VOS_INT16                           shwHd3FixedBrValue;                     /* 默认值12877 具体说明见结构体注释 */
    VOS_INT16                           shwHd5FixedCrValue;                     /* 默认值10121 具体说明见结构体注释 */
    VOS_UINT32                          uwHd3JudgeThd;                          /* 默认值24318 Hd3,Step3的判决门限,算法说明书给出 */
    VOS_UINT32                          uwHd5JudgeThd;                          /* 默认值618 Hd5,Step3的判决门限,算法说明书给出 */
    VOS_UINT32                          uwHd3Step2Thd;                          /* 默认值24318,Hd3自校准Step2的判决门限 */
    VOS_UINT32                          uwHd5Step2Thd;                          /* 默认值618,Hd5自校准Step2的判决门限 */
    VOS_UINT16                          uhwMrxRegValue;                         /* Mrx寄存器的配置值 */
    VOS_UINT16                          uhwHighBandScale;                       /* 高频段校准值作为最终补偿值需要相乘的系数，由硬件人员提取 */
}UCOM_NV_GSM_HD35_PARA_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_RF_VERSION_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :RF版本号NV项
*****************************************************************************/
typedef struct
{

    VOS_UINT32                          uwRfVersion;                            /* 0:RF6361;1:RF6362 */
}UCOM_NV_RF_VERSION_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_RF_CTRL_PORT_SEL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RFIC新增NV项,通道BAND不绑定配置
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwAfcPortSelect    :4;                                    /* AFC端口选择 */
    VOS_UINT32                          uwAptPortSelect    :4;                                    /* APT端口选择 */
    VOS_UINT32                          uwRampPortSelect   :4;                                    /* PMU端口选择 */
    VOS_UINT32                          uwReserved         :20;                                    /* 保留 */
}UCOM_NV_RF_CTRL_PORT_SEL_STRU;

typedef UCOM_NV_RF_CTRL_PORT_SEL_STRU  UCOM_NV_CDMA_RF_CTRL_PORT_SEL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_TCXO_CTRL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TCXO多次搜网相关的NV项,

*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTcxoSrchTempHigh;                    /* 启动多次搜网的高温门限 */
    VOS_INT16                           shwTcxoSrchTempLow;                     /* 启动多次搜网的低温门限 */
    VOS_INT16                           shwUpdateTcxoTempHigh;                  /* 上报AFC的高温门限 */
    VOS_INT16                           shwUpdateTcxoTempLow;                   /* 上报AFC的低温门限,在这个范围内才上报AFC的值 */
    VOS_UINT16                          uhwTcxoDynamicMax;                      /* 经过老化后TCXO控制字允许的最大变化量 */
    VOS_UINT16                          uhwReserve;                             /* 保留字段 */
}UCOM_NV_TCXO_CTRL_INFO_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_TCXO_AGING_THR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TCXO多次搜网相关的NV项,

*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwGsmAfcCIThres;                       /* GSM认为AFC锁定的门限值 */
    VOS_UINT16                          uhwCompWithDynMax;                      /* 是否保存dynamic的高门限用于开机第一次 */
    VOS_UINT16                          uhwCompWithDynMin;                      /* 是否保存dynamic的低门限用于开机第一次 */
    VOS_UINT16                          uhwCompWithDynMax2;                     /* 是否保存dynamic的高门限用于非开机第一次 */
    VOS_UINT16                          uhwCompWithDynMin2;                     /* 是否保存dynamic的高门限用于非开机第一次  */
    VOS_UINT16                          uhwReserve;                             /* 保留字段 */
}UCOM_NV_TCXO_AGING_THR_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_OPTIMIZE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : G模优化结构，专用态搜索优化控制结构该flag=0时 不开启默认使用原有方案，flag=1时开启。
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwGsmDchFastSrchFlag   :1;              /* 专用态搜索优化开启标志位 lag=0时 不开启默认使用原有方案，flag=1时开启 */
    VOS_UINT32                          uwGsmBchFast101Flag    :1;              /* 待机状态下快速101的标志位 */
    VOS_UINT32                          uwGsmCellFastSrchFlag  :1;              /* 开机搜网优化 */
    VOS_UINT32                          uwGsmBchPageRptFlag    :1;              /* 空闲态寻呼消息是否上报GAS的开关;1-无条件上报;0-解到有用信息上报 */
    VOS_UINT32                          uwGsmAdrxFlag          :1;              /* ADRX开关 */
    VOS_UINT32                          uwSlaveGsmNcoFlag      :1;              /* 从模NCO纠偏开关 */
    VOS_UINT32                          uwReserved2            :26;
}UCOM_NV_GSM_OPTIMIZE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_ANT_IDLE_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GPIO idle时隙天线的配置状态
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwAntSwitch;                    /* 空闲时隙时天线的开关值 */
    VOS_UINT32                                  uwReserved5;                    /* 保留字段 */
    VOS_UINT32                                  uwReserved4;                    /* 保留字段 */
    VOS_UINT32                                  uwReserved3;                    /* 保留字段 */
    VOS_UINT32                                  uwReserved2;                    /* 保留字段 */
    VOS_UINT32                                  uwReserved1;                    /* 保留字段 */
    VOS_UINT32                                  uwReserved0;                    /* 保留字段 */
}UCOM_NV_GSM_ANT_IDLE_CONFIG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_WG_IQMISMATCH_CAL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 说明RFIC的环回路径
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRfic0MrxAbbChannel    :8;                               /* RFIC0环回连接的ABB通道选择 */
    VOS_UINT16                          uhwRfic0MrxAbbPath       :8;                               /* RFIC0环回连接的ABB通道内ABB_A、ABB_B选择 */
    VOS_UINT16                          uhwRfic1MrxAbbChannel    :8;                               /* RFIC1环回连接的ABB通道选择 */
    VOS_UINT16                          uhwRfic1MrxAbbPath       :8;                               /* RFIC1环回连接的ABB通道内ABB_A、ABB_B选择 */
}UCOM_NV_WG_IQMISMATCH_CAL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_FEATURE_XPASS_EN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : XPASS高铁功能使能NV，0为关闭，1为打开
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         uhwXpassEnFlag;                          /* XPASS高铁功能使能NV，0为关闭，1为打开 */
    VOS_UINT16                         uhwReserve;
}UCOM_NV_GSM_FEATURE_XPASS_EN_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_DCXO_MAX_MIN_COEFF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 厂商给出的dcxo最大最小曲线
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          auwMantissaMax[3];                      /* 依次存放最大值a1,a2,a3的尾数 */
    VOS_UINT32                          auwMantissaMin[3];                      /* 依次存放最小值a1,a2,a3的尾数 */
    VOS_UINT16                          auhwExponentMax[3];                     /* 依次存放最大值a1,a2,a3的指数 */
    VOS_UINT16                          auhwExponentMin[3];                     /* 依次存放最小值a1,a2,a3的指数 */
}UCOM_NV_DCXO_MAX_MIN_COEFF_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_ET_EN_MASK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ET 是否支持
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwEtBandMask;                           /* bit0为1表示支持band1, 类推 */
    VOS_UINT32                          uwEtBandMaskEx;
}UCOM_NV_W_ET_EN_MASK_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_DPD_EN_MASK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPD是否支持
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwDpdBandMask;                          /* bit0为1表示支持band1, 类推 */
    VOS_UINT32                          uwDpdBandMaskEx;
}UCOM_NV_W_DPD_EN_MASK_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_DPD_LUT_THRESHOLD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPD LUT切换门限
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwValidCnt;                            /* 有效个数 */
    VOS_UINT16                          auhwLutSwitchThreshold[UCOM_NV_DPD_LUT_THERSHOLD_MAX_NUM]; /* 切换门限,如果是功率模式，单位0.1dB，如果是APC Index模式，从0开始映射
                                                                                                       门限值从门限0到门限8大小递增 */
}UCOM_NV_W_DPD_LUT_THRESHOLD_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_DPD_STEP_V_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : BBP查DPD LUT的量化参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwDpdStepV[UCOM_NV_BBP_DPD_LUT_MAX_NUM];
}UCOM_NV_W_DPD_STEP_V_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_ET_DPD_CTRL_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : BBP根据该NV项确定每张DPD表的使用场景,BBP接口提供8张DPD表，切换门限为9个，每张表深度为64
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwDpdIndexMode;                        /* 0: 功率模式; 1:Apc setting  */
    VOS_UINT16                          uhwReserved;
    UCOM_NV_W_DPD_LUT_THRESHOLD_STRU    stDpdThreshold;                         /* DPD LUT切换门限 */
    UCOM_NV_W_DPD_STEP_V_STRU           stDpdStepV;
}UCOM_NV_W_DPD_LUT_THRESHOLD_PARA_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_DPD_LUT_CAL_POWER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPD表校准时的功率或RF控制字
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwValidCnt;                             /* 有效个数 */
    VOS_INT16                           ashwDpdCalPower[UCOM_NV_DPD_LUT_MAX_NUM]; /* 每张DPD表校准时的功率或RF控制字,如果是功率模式，单位0.1dB，如果是APC Index模式 */
}UCOM_NV_W_DPD_LUT_CAL_POWER_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_ET_DPD_MRX_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ET DPD自校准MRX配置信息,FbPin与PD相同
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwMrxGain       :2;                     /* mrx gain */
    VOS_UINT32                          uwMrxVgaGain    :4;                     /* Rx_A Vga Gain */
    VOS_UINT32                          uwReserved1     :1;                     /*  */
    VOS_UINT32                          uwMrxDcAdjust   :2;                     /* MRX直流调整 */
    VOS_UINT32                          uwReserved2     :23;
}UCOM_NV_W_ET_DPD_MRX_CFG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_DPD_SELF_CAL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_DPD_LUT_CAL_POWER_STRU    stDpdCalPower;                          /* DPD自校准方案中需要校准的功率点 */
    VOS_UINT16                          auhwDpdLinearGainIndex[UCOM_NV_BBP_DPD_LUT_MAX_NUM];  /* DPD自校准方案中对应每张DPD表的期望gain index,有效值0-63，算法推荐8，与PA有关 */
    UCOM_NV_W_ET_DPD_MRX_CFG_STRU       stReserved;                             /* ET 及DPD校准时，MRX配置参数 */
    UCOM_NV_MIPI_COMM_STRU              stMipiReserved;                         /* ET 及DPD校准时，ET器件可能需要改配 */
}UCOM_NV_W_DPD_SELF_CAL_INFO_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_ET_DPD_SELF_CAL_FE_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_ET_DPD_MRX_CFG_STRU       stMrxCfgInfo;                           /* ET 及DPD校准时，MRX配置参数 */
    UCOM_NV_MIPI_COMM_STRU              stEtDpdCalMipiCfg;                      /* ET 及DPD校准时，ET器件可能需要改配 */
}UCOM_NV_W_ET_DPD_SELF_CAL_FE_CFG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_ET_INT_TIME_DELAY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 可能只需要校准包络通路分数延时，所以定义整数延时默认值
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwDataPathIntDelay;                    /* 数据通路整数延时 */
    VOS_UINT16                          uhwEtPathIntDelay;                      /* 包络通路整数延时 */
}UCOM_NV_W_ET_INT_TIME_DELAY_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_DPD_COMP_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPD LUT
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwDpdCompI;
    VOS_INT16                           shwDpdCompQ;
}UCOM_NV_W_DPD_COMP_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_DPD_TABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPD LUT 每张表深度为64
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_DPD_COMP_PARA_STRU        astDpdPara[UCOM_NV_DPD_LUT_MAX_LEN];
}UCOM_NV_W_DPD_TABLE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_DPD_LUT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPD LUT BBP接口提供8张DPD表，切换门限为9个，每张表深度为64
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_DPD_TABLE_STRU            astDpdLut[UCOM_NV_BBP_DPD_LUT_MAX_NUM];
}UCOM_NV_W_DPD_LUT_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_ET_PA_VCC_DATA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 复数数据结构
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwPower;                                /* 功率或APC index */
    VOS_INT16                           shwPaVcc;                                /* 电压控制字 */
}UCOM_NV_W_ET_PA_VCC_DATA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_ET_PA_VCC_LUT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ET Pa Vcc LUT
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_ET_PA_VCC_DATA_STRU       astEtPaVccLut[UCOM_NV_ET_LUT_MAX_LEN];  /* LUT数据 */
}UCOM_NV_W_ET_PA_VCC_LUT_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_DPD_TEMP_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPD LUT的温度补偿
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwTempComp[UCOM_NV_W_TX_PA_TEMP_NUM];      /* P-Vcc LUT的温度补偿 */
}UCOM_NV_W_ET_TIME_DELAY_TEMP_COMP_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_ET_ENVELOP_TIME_DELAY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ET Time Delay校准结果
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEnvelopTimeDelay;                    /* Et 包络通路Time Delay */
    VOS_UINT16                          uhwRslv;                                /* 保留 */
}UCOM_NV_W_ET_ENVELOP_TIME_DELAY_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_ET_TIME_DELAY_FREQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ET Time Delay提取结果
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwFreqChan;                             /* 频点 */
    VOS_INT16                           shwEtDelayFreqComp;                     /* delay comp */
    VOS_UINT16                          uhwReserved;                            /* reserved; */
}UCOM_NV_W_ET_TIME_DELAY_FREQ_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_ET_TIME_DELAY_FREQ_CAL_CHAN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ET Time Delay频补提取结果
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEtTimeDelayCalEnable;
    VOS_UINT16                          uhwChannelNum;                          /* 每个Band有效个数 */
    VOS_UINT32                          auwFreqChan[UCOM_NV_ET_DELAY_FREQ_COMP_MAX_NUM];/* Et 包络通路Time Delay */
}UCOM_NV_W_ET_TIME_DELAY_FREQ_CAL_CHAN_STRU;



/*****************************************************************************
 结构名    : UCOM_NV_W_ET_TIME_DELAY_FREQ_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ET Time Delay频补提取结果
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwChannelNum;                           /* 每个Band有效个数 */
    UCOM_NV_W_ET_TIME_DELAY_FREQ_STRU   astEtTimeDelayFreq[UCOM_NV_ET_DELAY_FREQ_COMP_MAX_NUM];/* Et 包络通路Time Delay */
}UCOM_NV_W_ET_TIME_DELAY_FREQ_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_ET_DELAY_FREQ_COMP_DEFAULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ET Time Delay频补提取结果
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwEtTimeDelayFreq[UCOM_NV_ET_DELAY_FREQ_COMP_MAX_NUM];/* Et 包络通路Time Delay */
}UCOM_NV_W_ET_DELAY_FREQ_COMP_DEFAULT_STRU;





/*****************************************************************************
 结构名    : UCOM_NV_W_DPD_TEMP_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPD温度补偿
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwTempComp[UCOM_NV_W_DPD_TEMP_COMP_NUM]; /*  */
}UCOM_NV_W_DPD_TEMP_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_DPD_FREQ_TEMP_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPD频率-温度补偿
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_DPD_TEMP_COMP_STRU        astTempCompFreqIndex[UCOM_NV_W_DPD_FREQ_COMP_NUM]; /*  */
}UCOM_NV_W_DPD_FREQ_TEMP_COMP_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_ET_TIME_DELAY_CTRL_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ET Time Delay校准控制系数
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwDelayCalPower;                       /* ET Time Delay校准的功率 */
    VOS_INT16                           shwLowerOffset;                         /* ET Time Delay下限 */
    VOS_INT16                           shwUpperOffset;                         /* ET Time Delay上限 */
    VOS_INT16                           shwSweepOffset;                         /* ET Time Delay校准步进值 */
}UCOM_NV_W_ET_TIME_DELAY_CTRL_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_ET_DELAY_CAL_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Et Delay校准信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwCenterEnvelopTimeDelay;              /* delay的中心值 */
    VOS_UINT16                          uhwBinarySearchRangeOffset;             /* 二分法搜索的offset */
    VOS_UINT16                          uhwSweepRange;                          /* 扫描范围 */
    VOS_UINT16                          uhwSweepStep;                           /* 扫描步长 */
}UCOM_NV_W_ET_DELAY_CAL_PARA_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_ET_GAIN_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 按照功率查表类型时，可以近似认为功率和电压的满足现行关系V = P*Gain+GainOffet，
 不同单板的（Gain, GainOffset）可以通过校准获得，通过软件半静态配置
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwGain;                                /* ET LUT 修正斜率 */
    VOS_INT16                           shwGainOffset;                          /* ET LUT 修正偏移 */
}UCOM_NV_W_ET_GAIN_PARA_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_CDMA_1X_CPROC_GENERAL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : NV parameters for CPROC 1x.
*****************************************************************************/
typedef struct
{
    /**
     * RF settling time in number of PCGs (1.25 ms)
     */
    VOS_INT32  slCproc1xRfSettlingTime;

    /**
     * Maximum number of pilots in the active set.
     * Does not really belong in NV but should be a common define for CAS, CPROC and CSDR.
     */
    VOS_INT32  slSupportActiveSetNum;

    /**
     * Size of the measurement window in q-chips
     */
    VOS_INT32  slCproc1xSmMeasWindowSize;

    /**
     * Size of the MPS window in q-chips
     */
    VOS_INT32  slCproc1xSmMpsWindowSize;

    /**
     * Size of the pilot search window in q-chips
     */
    VOS_INT32  slCproc1xSmPilotSearchWindowSize;

    /**
     * Maximum number of q-chips uwDelaySpreadRMS may change between two samples
     * if it shall be considered reliable.
     */
    VOS_INT32  slCproc1xSmMpsMaxChangeRmsThreshold;

    /**
     * Front and back guard interval length in q-chips
     */
    VOS_INT32  slCproc1xSmMpsGuardIntervalLength;

    /**
     * Threshold for selecting MPS window sliding algorithm in q-chips
     * if uwDelaySpreadRMS > CPROC_1X_SM_MPS_ALGORITHM_SELECT_THRESHOLD
     * then rule 1
     * else rule 2
     */
    VOS_INT32  slCproc1xSmMpsAlgorithmSelectThreshold;

    /**
     * How far to adjust the MPS window when rule 1 is selected, in q-chip.
     */
    VOS_INT32  slCproc1xSmMpsRule1SlideStep;

    /**
     * How far to adjust the MPS window when rule 2 is selected, in q-chip.
     */
    VOS_INT32  slCproc1xSmMpsRule2SlideStep;

    /**
     * Threshold for when to slide window when adjusting according to rule 2, in q-chip.
     */
    VOS_INT32  slCproc1xSmMpsRule2DeltaThreshold;

    /**
     * Level where a pilot is considered as valid.
     */
    VOS_INT32  slCproc1xPdbDetectedThreshold;
    VOS_INT32  slPsGoodPilotThreshold;

    /**
     * Number of times a pilot may be below CPROC_1X_PDB_DETECTED_THRESHOLD before it is removed from PDB.
     */
    VOS_INT32  slCproc1xPdbMaxAgeBelowThreshold;

    /**
     * Maximum number of CF neighbors to measure in one CF gap.
     */
    VOS_INT32  slCproc1xNumCfNeighToMeasure;

    /**
     * Maximum number of pilot searches in one CF gap.
     */
    VOS_INT32  slCproc1xNumCfNeighSearches;

    /**
     * Threshold to add IC pilot to IC in db.
     */
    VOS_INT32  slCproc1xIcAddMargin;

    /**
     * Threshold to remove IC pilot to IC in db.
     */
    VOS_INT32  slCproc1xIcRemoveMargin;

    /**
     * Does the platform support diversity antenna
     */
    VOS_INT32  slCproc1xDiversityAntenna;

    /**
     * Does the platform support interference cancellation
     */
    VOS_INT32  slCproc1xIcSupported;

    /**
     * ESS priorities for measurements
     */
    VOS_INT32  slCproc1xMeasSfPriority;
    VOS_INT32  slCproc1xMeasCfPriority;


}UCOM_NV_CDMA_1X_CPROC_GENERAL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_CDMA_HRPD_CPROC_GENERAL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : NV parameters for CPROC HRPD.
*****************************************************************************/
typedef struct
{
    VOS_INT32 slKalle;
}UCOM_NV_CDMA_HRPD_CPROC_GENERAL_STRU;


/*******************************************************
CDMA NV begin
*********************************************************/

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_RF_MAIN_BAND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 主集支持的band，按照Bit位表示BC0~BC21是否支持，1表示支持。
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwSupportBand;
}UCOM_NV_CDMA_RF_MAIN_BAND_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_RF_DIV_BAND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 分集支持的band，按照Bit位表示BC0~BC21是否支持，1表示支持。
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwSupportBand;
}UCOM_NV_CDMA_RF_DIV_BAND_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_RF_BAND_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :2.1表示CDMA支持的每个频段与RF
            通道对应关系天线开关切换选择、DBB对3GPA的控制
*****************************************************************************/
typedef struct
{
    UCOM_NV_RF_CONFIG_STRU       astCdmaRfBandMainRxConfig[UCOM_NV_CDMA_TOTAL_BAND_NUM];     /* 包括了CDMA所有频段 */
    UCOM_NV_RF_CONFIG_STRU       astCdmaRfBandDvtyRxConfig[UCOM_NV_CDMA_TOTAL_BAND_NUM];     /* 包括了CDMA所有频段 */
    UCOM_NV_RF_CONFIG_STRU       astCdmaRfBandTxConfig[UCOM_NV_CDMA_TOTAL_BAND_NUM];         /* 包括了CDMA所有频道 */
}UCOM_NV_CDMA_RF_BAND_CONFIG_STRU;

typedef UCOM_NV_W_RX_AGC_GAIN_VALID_COUNT_STRU  UCOM_NV_CDMA_RX_AGC_GAIN_VALID_COUNT_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_RX_IP2_CAL_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : X模 Rx IP2校准的配置和校准门限。
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTxRefPower;                          /* 校准时上行通道的功率，单位为0.1dBm */
    VOS_INT16                           shwImd2Threshold;                       /* 校准后IMD2的门限，单位dB */
}UCOM_NV_CDMA_RX_IP2_CAL_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_TX_TIMING_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : X模 上行发射时间
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwPaOnDelay;                           /* 提前打开上行PA的chip数。默认值25 */
    VOS_UINT16                          uhwPaOffDelay;                          /* 延后关闭上行PA的chip数。*/
    VOS_UINT16                          uhwRfTxEnOnDelay;                       /* 提前打开上行RF TX EN的线控chip数,默认值220 */
    VOS_UINT16                          uhwRfTxEnOffDelay;                      /* 延后关闭上行RF TX EN的线控chip数,默认值220 */
    VOS_UINT16                          uhwRfIdleOnDelay;                       /* 提前打开上行RF IDLE->On状态的chip数,默认值220 */
    VOS_UINT16                          uhwRfOnIdleDelay;                       /* 延后上行RF On->IDLE状态关闭的chip数  */
    VOS_UINT16                          uhwTxAbbOnDelay;                        /* 提前打开上行ABB En 线控的chip数。默认值164 */
    VOS_UINT16                          uhwTxAbbOffDelay;                       /* 延后关闭上行ABB的chip数。*/
    VOS_UINT16                          uhwBbpDbbAttenActiveTime;               /* 上行dbb控制字提前时隙头生效位置 单位1/4chip 默认值0 */
    VOS_UINT16                          uhwBbpPhaseCompActiveTime;              /* 表示上行相位补偿提前时隙头生效位置，单位1/4chip 默认值0 */
    VOS_UINT16                          uhwBbpSlotOffset;                       /* 上行时隙头相对sys_cnt时隙边界提前量，单位1/4chip 默认值0x97 */
    VOS_UINT16                          uhwRfTxAgcActiveTime;                   /* 上行理论功率生效提前量，单位chip，默认值22 */
    VOS_UINT16                          uhwReserve;
    VOS_UINT16                          uhwReserve1;
    VOS_UINT16                          uhwReserve2;
    VOS_UINT16                          uhwReserve3;
}UCOM_NV_CDMA_TX_TIMING_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_CDMA_HDET_TIMING_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 功率检测中使用的NV项结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwPaStableTiming;                  /* 发射功率变化后，RF与PA的稳定时间，单位为chip*/
    VOS_UINT16                              uhwPdHkadcChanSelTiming;            /*授权有效到发送HKADC通道控制字时刻间隔，单位为chip*/
    VOS_UINT16                              uhwPdStartInterval;                 /* ABB从bypass为低到启动start（ABB开始转换）的时间间隔，单位为chip*/
    VOS_UINT16                              uhwPdInterval;                      /* 两次功率检测之间的时间间隔，单位为chip*/
    VOS_UINT16                              uhwPdsampleTiming;                  /* HKADC采样信号处理时间，单位为chip*/
    VOS_UINT16                              uhwDcOffsetSampleNum;               /*WHKADC上行每个时隙进行dc offset检测的次数*/
    VOS_UINT16                              uhwPdSampleNum;                     /*W上行每个时隙进行PD检测的次数*/
    VOS_UINT16                              uhwReserved1;                       /*保留位*/
    VOS_UINT16                              uhwReserved2;                       /*保留位*/
    VOS_UINT16                              uhwReserved3;                       /*保留位*/
} UCOM_NV_CDMA_HDET_TIMING_CONFIG_STRU;

typedef UCOM_NV_W_ANT_PERFORM_TEST_STRU         UCOM_NV_CDMA_ANT_PERFORM_TEST_STRU;

//RX_RSSI_ARITHMETIC_PARAMETER
typedef UCOM_NV_W_TX_RF_GAIN_TEMP_COMP_STRU     UCOM_NV_UC_TX_RF_GAIN_TEMP_COMP_STRU;        /* RFIC温度补偿表 */
typedef UCOM_NV_W_RX_AGC_SWITCH_VOICE_MODE_STRU UCOM_NV_CDMA_RX_AGC_SWITCH_VOICE_MODE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_TX_PA_APT_ENABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 根据bit位表示是否使能APT
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwCdmaBand;                             /* bit位是1代表支持APT */
}UCOM_NV_CDMA_TX_PA_APT_ENABLE_STRU;

typedef UCOM_NV_W_TX_RF_GAIN_CTRL_STRU          UCOM_NV_CDMA_TX_RF_GAIN_CTRL_STRU;
typedef UCOM_NV_W_TX_RF_BIAS_STRU               UCOM_NV_CDMA_TX_RF_BIAS_STRU;
typedef UCOM_NV_W_BB_GAIN_TABLE_STRU            UCOM_NV_CDMA_BB_GAIN_TABLE_STRU;
typedef UCOM_NV_W_CPC_DRX_STRU                  UCOM_NV_CDMA_CPC_DRX_STRU;    /* 低功耗工作模式选择 */
/*****************************************************************************
 结构名    : UCOM_NV_CDMA_TX_IQ_MISMATCH_CAL_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :TX IQ MISMATCH校准初始功率和门限
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTxIqMismatch2RefPower;           /* 校准时上行通道的功率，单位为0.1dbm */
    VOS_INT16                           shwAmpCorrThreshold;                /* 校准后IMD2的门限，单位db */
    VOS_INT16                           shwDcCorrThreshold;                 /* 校准后IMD2的门限，单位db */
    VOS_UINT16                          uhwReserved;
}UCOM_NV_CDMA_TX_IQ_MISMATCH_CAL_PARA_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_CDMA_RX_IP2_CAL_CHAN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 需要IP2校准时的频率
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          auwFrequencyKHz[UCOM_NV_CDMA_CHANNEL_NUM];           /* 0 - High Channel; 1 - Mid Channel; 2 - Low Chan */
}UCOM_NV_CDMA_RX_IP2_CAL_FREQ_STRU;

typedef UCOM_NV_W_RX_IP2_CAL_AT1_STRU           UCOM_NV_CDMA_RX_IP2_CAL_AT1_STRU;
typedef UCOM_NV_W_RX_IP2_CAL_AT2_STRU           UCOM_NV_CDMA_RX_IP2_CAL_AT2_STRU;
typedef UCOM_NV_W_RX_IP2_THRESHOLD_STRU         UCOM_NV_CDMA_RX_IP2_THRESHOLD_STRU;
typedef UCOM_NV_W_RX_IP2_CAL_ENABLE_AT2_STRU    UCOM_NV_CDMA_RX_IP2_CAL_ENABLE_AT2_STRU;  /* 0表示启动分集天线IP2校准，1表示不启动 */

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_RX_IQ_DC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IQ直流值
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwDcICode;                             /* I路的直流码值 */
    VOS_INT16                           shwDcQCode;                             /* Q路的直流码值 */
}UCOM_NV_CDMA_RX_IQ_DC_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_RX_DC_OFFSET_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : BLOCK和NOBLOCK直流表
*****************************************************************************/
typedef struct
{
    UCOM_NV_CDMA_RX_IQ_DC_STRU          astNoBlockDcOffset[UCOM_NV_CDMA_AGC_GAIN_NOBLK_STEP_NUM];
    UCOM_NV_CDMA_RX_IQ_DC_STRU          astBlockDcOffset[UCOM_NV_CDMA_AGC_GAIN_BLK_STEP_NUM];
}UCOM_NV_CDMA_BLK_NBLK_DC_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_RX_DCOFFSET_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 区分天线
*****************************************************************************/
typedef struct
{
    UCOM_NV_CDMA_BLK_NBLK_DC_STRU       astDcOffsetAnt[UCOM_NV_CDMA_ANT_NUM];   /* 天线选择 */
}UCOM_NV_CDMA_RX_DCOFFSET_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_RX_CAL_FREQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 需要校准的CDMA的频点个数和频率
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwValidCalChanNum;                          /* 频率个数 */
    VOS_UINT16                          uhwReserved;
    VOS_UINT32                          auwRxFrequencyKHz[UCOM_NV_CDMA_UARFCN_NUM];  /* 频率表，单位KHz */
}UCOM_NV_CDMA_RX_CAL_FREQ_STRU;

/*****************************************************************************
 枚举名    : UCOM_NV_CDMA_RX_AGC_GAIN_SWITCH_THRESHOLD_STRU
 协议表格  :
 枚举说明  : AGC档位切换门限的NV项，包括BLOCK和非BLOCK
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwNoBlockAgcThresholdInc[UCOM_NV_CDMA_AGC_GAIN_NOBLK_THRESHOLD_NUM];           /* NoBlock方式下档位增加 */
    VOS_INT16                           ashwNoBlockAgcThresholdDec[UCOM_NV_CDMA_AGC_GAIN_NOBLK_THRESHOLD_NUM];           /* NoBlock方式下档位增加 */
    VOS_INT16                           ashwBlockAgcThresholdInc[UCOM_NV_CDMA_AGC_GAIN_BLK_THRESHOLD_NUM];               /* Block方式下档位增加 */
    VOS_INT16                           ashwBlockAgcThresholdDec[UCOM_NV_CDMA_AGC_GAIN_BLK_THRESHOLD_NUM];               /* Block方式下档位增加 */
}UCOM_NV_CDMA_RX_AGC_GAIN_SWITCH_THRESHOLD_STRU;

typedef UCOM_NV_W_RX_AGC_CTRL_STRU      UCOM_NV_CDMA_RX_AGC_CTRL_STRU;

/*****************************************************************************
 枚举名    : UCOM_NV_CDMA_RX_AGC_GAIN_BLK_NBLK_STRU
 协议表格  :
 枚举说明  : AGC控制字对应增益值，包括BLOKC和非BLOCK,单位0.125dbm.
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwNoBlockAgcGain[UCOM_NV_CDMA_AGC_GAIN_NOBLK_STEP_NUM];           /* NoBlock方式下档位增加 */
    VOS_INT16                           ashwBlockAgcGain[UCOM_NV_CDMA_AGC_GAIN_BLK_STEP_NUM];               /* NoBlock方式下档位增加 */
}UCOM_NV_CDMA_RX_AGC_GAIN_ANT_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_RX_AGC_GAIN_ANT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AGC默认增益值，区分天线
*****************************************************************************/
typedef struct
{
    UCOM_NV_CDMA_RX_AGC_GAIN_ANT_STRU   astAgcGainAnt[UCOM_NV_CDMA_ANT_NUM];    /* 天线选择 */
}UCOM_NV_CDMA_RX_AGC_GAIN_DEFAULT_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_RX_AGC_GAIN_ANT_DEF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AGC默认增益值，区分天线
*****************************************************************************/
typedef struct
{
    UCOM_NV_CDMA_RX_AGC_GAIN_ANT_STRU   astAgcGainAnt[UCOM_NV_CDMA_ANT_NUM];    /* 天线选择 */
}UCOM_NV_CDMA_RX_AGC_GAIN_STRU;

typedef UCOM_NV_W_RX_AGC_FREQ_COMP_ANT_STRU     UCOM_NV_CDMA_RX_AGC_FREQ_COMP_ANT_STRU;    /* AGC频率补偿表，16个采样点，区分天线 */
typedef UCOM_NV_FEM_CHAN_CONNECT_STRU           UCOM_NV_CDMA_FEM_CHAN_CONNECT_STRU;

/*****************************************************************************
 结构名    : CSDR_NV_CDMA_RF_PA_GAIN_CTRL_WORD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PA增益控制字
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          auwRfPaCtrlMode[UCOM_NV_CDMA_TX_PA_MODE_NUM];   /* PA高/中/低增益模式控制字 */
}UCOM_NV_CDMA_RF_PA_GAIN_CTRL_WORD_STRU;

/*****************************************************************************
 结构名    : CSDR_NV_CDMA_PA_GAIN_SWITCH_THRESHOLD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PA档位切换门限
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwPaGainThresH2M;                      /* PA从高增益到中增益的切换门限 */
    VOS_INT16                           shwPaGainThresM2H;                      /* PA从中增益到高增益的切换门限 */
    VOS_INT16                           shwPaGainThresM2L;                      /* PA从中增益到低增益的切换门限 */
    VOS_INT16                           shwPaGainThresL2M;                      /* PA从低增益到中增益的切换门限 */
}UCOM_NV_CDMA_PA_GAIN_SWITCH_THRESHOLD_STRU;

typedef UCOM_NV_W_PA_GAIN_SWITH_TIMING_STRU     UCOM_NV_CDMA_PA_GAIN_SWITCH_TIMING_STRU;  /* PA档位切换时序 */
typedef UCOM_NV_W_TX_PHASE_COMP_STRU            UCOM_NV_CDMA_TX_PHASE_COMP_STRU;           /* PA切换相位补偿 */
typedef UCOM_NV_W_TX_PHASE_COMP_TIMING_STRU     UCOM_NV_CDMA_TX_PHASE_COMP_TIMING_STRU;   /* PA切换相位补偿时序 */
typedef UCOM_NV_TX_IQ_MISMATCH_DCR_STRU         UCOM_NV_CDMA_TX_IQ_MISMATCH_STRU;          /* 校准后的幅相校正因子和直流校正参数 */
typedef UCOM_NV_TX_IQ_SELF_CAL_6362_STRU        UCOM_NV_CDMA_TX_IQ_SELF_CAL_6362_STRU;     /* DC offset的直流校准门限 */

/*****************************************************************************
 结构名    : CSDR_NV_CDMA_TX_CAL_CHAN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :需要校准的CDMA的频点个数与频率
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwValidCalChanNum;                          /* 频率个数 */
    VOS_UINT16                          uhwReserved;
    VOS_UINT32                          auwTxFrequencyKHz[UCOM_NV_CDMA_UARFCN_NUM];  /* 频率值,单位KHz */
}UCOM_NV_CDMA_TX_CAL_FREQ_STRU;

typedef UCOM_NV_W_TX_APC_TEMP_STRU                        UCOM_NV_CDMA_TX_APC_TEMP_STRU;            /* 校准时的温度 */
typedef UCOM_NV_W_TX_PA_GAIN_STRU                         UCOM_NV_CDMA_TX_PA_GAIN_STRU;             /* PA各档位下的增益值 */
typedef UCOM_NV_W_APC_GAIN_STATE_INDEX_STRU               UCOM_NV_CDMA_RF_GAIN_STATE_INDEX_STRU;   /* APC表索引值 */
typedef UCOM_NV_W_APC_RFIC_CTRL_GAIN_STRU                 UCOM_NV_CDMA_APC_RFIC_CTRL_GAIN_STRU;    /* APC表控制字 */
typedef UCOM_NV_W_APC_DBB_ATTEN_GAIN_STRU                 UCOM_NV_CDMA_APC_DBB_ATTEN_GAIN_STRU;    /* DBB回退值 */

typedef UCOM_NV_W_TX_PA_GAIN_VOICE_MODE_STRU              UCOM_NV_CDMA_TX_PA_GAIN_VOICE_MODE_STRU;           /* 语音模式下PA各档增益值 */
typedef UCOM_NV_W_APC_STATE_INDEX_GAIN_VOICE_MODE_STRU    UCOM_NV_CDMA_RF_STATE_INDEX_GAIN_VOICE_MODE_STRU; /* 语音模式下APC表索引值 */
typedef UCOM_NV_W_APC_RFIC_CTRL_GAIN_VOICE_MODE_STRU      UCOM_NV_CDMA_APC_RFIC_CTRL_GAIN_VOICE_MODE_STRU;  /* 语音模式下APC控制字 */
typedef UCOM_NV_W_APC_DBB_ATTEN_GAIN_VOICE_MODE_STRU      UCOM_NV_CDMA_APC_DBB_ATTEN_GAIN_VOICE_MODE_STRU;  /* 语音模式下DBB回退值 */

typedef UCOM_NV_W_TX_HDET_VGA_STRU                        UCOM_NV_CDMA_TX_HDET_VGA_STRU;       /* PD VGA的校准输入参数 */
typedef UCOM_NV_W_TX_HDET_DCOFFSET_STRU                   UCOM_NV_CDMA_TX_HDET_DCOFFSET_STRU;  /* PD DC Offset的校准结果 */
typedef UCOM_NV_W_TX_HDET_POWER_STRU                      UCOM_NV_CDMA_TX_HDET_POWER_STRU;     /* 高增益模式下，测试功率和电压关系的功率测试点 */
typedef UCOM_NV_W_TX_HDET_HKADC_STRU                      UCOM_NV_CDMA_TX_HDET_HKADC_STRU;     /* 高增益模式下，测试功率和电压关系时电压测试值 */
typedef UCOM_NV_W_TX_HDET_START_STRU                      UCOM_NV_CDMA_TX_HDET_START_STRU;     /* TX 发射功率超过该值时，BBP自动启动功率检测 */
typedef UCOM_NV_W_TX_HDET_STOPT_STRU                      UCOM_NV_CDMA_TX_HDET_POWER_OFFSET_STRU; /* TX 发射功率超过该值时，BBP自动启动功率检测 */
typedef UCOM_NV_W_HDET_HKADC_CHAN_STRU                    UCOM_NV_CDMA_HDET_HKADC_CHAN_STRU;   /* 分立PA HDET通道 */
typedef UCOM_NV_W_TX_HDET_FREQ_COMP_STRU                  UCOM_NV_CDMA_TX_HDET_FREQ_COMP_STRU; /* 不同频点对功率器件影响不同，频率补偿值 */
typedef UCOM_NV_W_TX_HDET_TEMP_COMP_STRU                  UCOM_NV_CDMA_TX_HDET_TEMP_COMP_STRU; /* 不同温度对功率器件影响不同，温度补偿值.区分高中低信道,顺序为中高低 */
typedef UCOM_NV_W_TX_GAIN_FREQCOMP_STRU                   UCOM_NV_CDMA_TX_GAIN_FREQ_COMP_STRU; /* PA频率补偿表，分高中低三档 */
typedef UCOM_NV_W_TX_GAIN_TEMP_COMP_STRU                  UCOM_NV_CDMA_TX_GAIN_TEMP_COMP_STRU; /* PA温度补偿表，分高中低档位和高中低信道 */
typedef UCOM_NV_W_RFFE_MIPI_PA_CTRL_STRU                  UCOM_NV_CDMA_RFFE_MIPI_PA_CTRL_STRU;  /* MIPI PA指令 */
typedef UCOM_NV_W_ANT_SWITCH_MIPI_STRU                    UCOM_NV_CDMA_ANT_SWITCH_MIPI_STRU;    /* MIPI 天线开关指令 */
typedef UCOM_NV_DUAL_ANT_DPDT_PROTECT_TIME_STRU           UCOM_NV_CDMA_DUAL_ANT_DPDT_PROTECT_TIME_STRU; /* DPDT切换保护时间 */

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_TX_GAIN_COMP_VS_PA_CHAN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwHighFreq;                             /* 用于判断高频点区间的频点 */
    VOS_UINT32                          uwLowFreq;                              /* 用于判断低频点区间的频点 */
}UCOM_NV_CDMA_TX_GAIN_COMP_VS_PA_CHAN_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_TX_PA_APT_EVDO_COMP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 根据不同的信道配比设置不同的补偿值
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwAptEvdoComp[16];                    /* 用于EVDO模式APT功率补偿 */
 }UCOM_NV_CDMA_TX_PA_APT_EVDO_COMP_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_CDMA_ALG_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :算法维护的NV项
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwDagcInit;                            /* DAGC,初始值，需要算法给从NV项获得 */
    VOS_UINT16                          uhwAagcCoeff;                           /* AAGC Alpha滤波系数,从NV项获得 */
    VOS_UINT16                          uhwDagcCoeff;                           /* DAGC Alpha滤波系数,从NV项获得 */
    VOS_INT16                           shwIqMismatchInit;                      /* CBBP IQ MISMATCH初值,从NV项获得 */
    VOS_INT16                           shwDcrInit;                             /* CBBP DCR初值,从NV项获得 */
    VOS_INT16                           shwAagcGainInit;                        /* CBBP AAGC档位增益初值,从NV项获得 */
    VOS_INT16                           uhwReserved1;                           /* uhwReserved */
    VOS_INT16                           uhwReserved2;                           /* uhwReserved */
    VOS_INT16                           uhwReserved3;                           /* uhwReserved */
    VOS_INT16                           uhwReserved4;                           /* uhwReserved */
}UCOM_NV_CDMA_ALG_CFG_STRU;

typedef UCOM_NV_W_UL_RF_GATE0_STRU              UCOM_NV_CDMA_UL_RF_GATE0_STRU;       /* 削波门限0 */
typedef UCOM_NV_W_UL_RF_GATE1_STRU              UCOM_NV_CDMA_UL_RF_GATE1_STRU;       /* 削波门限1 */
typedef UCOM_NV_WG_IQ_REV_CONTROL_STRU          UCOM_NV_CDMA_IQ_REV_CONTROL_STRU;    /* IQ数据反向设置 */
typedef UCOM_NV_RF_INIT_CONFIG_STRU             UCOM_NV_GUC_RF_INIT_CONFIG_STRU;     /* RFIC寄存器初始配置 */
typedef UCOM_NV_RF_INIT_CONFIG_NEW_RAM_STRU     UCOM_NV_GUC_RF_INIT_CONFIG_NEW_RAM_STRU;     /* RFIC寄存器初始配置 */
typedef UCOM_NV_XO_INIT_FREQUENCY_STRU          UCOM_NV_GUC_XO_INIT_FREQUENCY_STRU;  /* 晶体初始频偏和温度 */
typedef UCOM_NV_DYNAMIC_FREQUENCY_STRU          UCOM_NV_GUC_DYNAMIC_FREQUENCY_STRU;  /* 频偏调整上一次保存的频偏和温度 */
typedef UCOM_NV_W_RSSI_ARITHMETIC_PARA_STRU     UCOM_NV_UC_RSSI_ARITHMETIC_PARA_STRU;
typedef UCOM_NV_W_AFC_K_VALUE_STRU              UCOM_NV_GUC_AFC_K_VALUE_STRU;         /* AFC每个控制字调整的频偏步长，单位hz，目前4hz */
typedef UCOM_NV_RFIC_TEMP_COMP_WEIGH_STRU       UCOM_NV_GUC_RFIC_TEMP_COMP_WEIGH_STRU;
typedef UCOM_NV_WG_TX_TEMP_DEFINE_STRU          UCOM_NV_GUC_TX_TEMP_DEFINE_STRU;      /* 温度范围表，单位0.1度，16个采样点 */
typedef UCOM_NV_W_TX_TEMP_COMP_STRU             UCOM_NV_CDMA_TX_TEMP_COMP_STRU;       /* RFIC 15个档位下，每个档位对应16个温度补偿表 */
typedef UCOM_NV_RF_TRX_CONFIG_STRU              UCOM_NV_CDMA_RF_TRX_CONFIG_STRU;
typedef UCOM_NV_SINGLE_XO_DEFINE_STRU           UCOM_NV_GUC_SINGLE_XO_DEFINE_STRU;   /* 时钟特性NV */
typedef UCOM_NV_RF_VERSION_STRU                 UCOM_NV_GUC_RF_VERSION_STRU;   /* RF版本号 */
typedef UCOM_NV_WG_IQMISMATCH_CAL_STRU          UCOM_NV_GUC_RF_MRX_CONNECT_STRU; /* 各RF MRX环回所在通道与ABB的连接情况 */
typedef UCOM_NV_WG_DCOFFSET_THRESHOLD_STRU      UCOM_NV_GUC_DCOFFSET_THRESHOLD_STRU;     /* DC offset的直流校准门限 */

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_ANT_SWITCH_CONTROL_MODE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 按照Bit位表示BC0~BC21 主分集天线开关控制方式为GPIO或MIPI，0表示GPIO,1表示MIPI。
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwMainAntCtrlModeBitMap;
    VOS_UINT32                          uwDvtyAntCtrlModeBitMap;
}UCOM_NV_CDMA_ANT_SWITCH_CONTROL_MODE_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_CDMA_ANT_SWITCH_CONTROL_MODE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 按照Bit位表示BC0~BC21 PA控制方式为GPIO或MIPI，0表示GPIO,1表示MIPI。
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwPaCtrlModeBitMap;
}UCOM_NV_CDMA_PA_CONTROL_MODE_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_TRI_MODE_ENABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 全网通特性使能开关(0:关闭 1:打开)
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwEnable;                          /* 全网通特性开关 */
    VOS_UINT16                              uhwReserved;
}UCOM_NV_TRI_MODE_ENABLE_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_TRI_MODE_FEM_PROFILE_ID_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 指示使用全网通场景Profile Id的NV项
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwProfileId;                        /* 根据使用场景，控制前端器件的上下电（ABB，TCXO，RF）以及RF通道的控制。
                                                                                   由AT命令下发配置。默认值为0。取值范围0-7。 */
    VOS_UINT32                              auwReserved[3];                     /* 保留，将来扩展使用 */
}UCOM_NV_TRI_MODE_FEM_PROFILE_ID_STRU;


/*****************************************************************************
结构名    : UCOM_NV_MODE_BASIC_PARA_STRU
结构说明  :
对应NVID:

  1.日    期   : 2014年12月30日
    作    者   : z68255
    修改内容   : 初始生成
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwABBSwitch;                       /* 用于ABB PLL开关的控制。0:ABB CH0 1:ABB CH1 2:ABB CH0&CH1都打开 */
    VOS_UINT16                              uhwRFSwitch;                        /* 用于RFIC电源开关的控制。0:RFIC使用MIPI0控制供电方式 1：RFIC使用MIPI1控制供电方式 2：同时打开两路电源。*/
    VOS_UINT16                              uhwTCXOSwitch;                      /* 0:TCXO0 1:TCXO1 */
    VOS_UINT16                              uhwReserved;                     /* 保留，将来扩展使用 */
}UCOM_NV_MODE_BASIC_PARA_STRU;

/*****************************************************************************
 结构名    : NV_TRI_MODE_CHAN_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 全网通通道参数配置参数  (不能改变)
*****************************************************************************/
typedef struct
{
    UCOM_NV_MODE_BASIC_PARA_STRU           stModeBasicPara[2];                  /* 下标[0]:表示GSM模式下的前端器件的上下电控制。
                                                                                   下标[1]:表示WCDMA模式下的前端器件的上下电控制。
                                                                                    注：副卡时，不使用WCDMA模式的配置。*/
    VOS_UINT32                              uwRfSwitch;                         /* 用于控制共分集的开关 */
    VOS_UINT32                              uwGsmRficSel;                       /* 信令模式下当前使用的通道（0：RF0,1：RF1） */
    VOS_UINT32                              uwGpioCtrl;                         /* 是否需要时钟切换(0:不需要, 1:需要 )*/
    VOS_UINT32                              auwReserved[14];                    /* 保留，将来扩展使用 */
}UCOM_NV_TRI_MODE_CHAN_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_TRI_MODE_FEM_CHAN_PROFILE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 8种场景的通道配置
*****************************************************************************/
typedef struct
{
    UCOM_NV_TRI_MODE_CHAN_PARA_STRU        astPara[UCOM_NV_TRI_MODE_CHAN_PARA_PROFILE_NUM];  /* 最多支持8个场景的配置 */
}UCOM_NV_TRI_MODE_FEM_CHAN_PROFILE_STRU;


/*****************************************************************************
结构名    : UCOM_NV_MODE_BASIC_EXT_PARA_STRU
结构说明  :
对应NVID:

  1.日    期   : 2014年12月30日
    作    者   : z68255
    修改内容   : 初始生成
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwABBSwitch;                       /* 用于ABB PLL开关的控制。0:ABB CH0 1:ABB CH1 2:ABB CH0&CH1都打开 */
    VOS_UINT16                              uhwRFSwitch;                        /* 用于RFIC电源开关的控制。0:RFIC使用MIPI0控制供电方式 1：RFIC使用MIPI1控制供电方式 2：同时打开两路电源。*/
    VOS_UINT16                              uhwTCXOSwitch;                      /* 0:TCXO0 1:TCXO1 */
    VOS_UINT16                              uhwRfClk;                           /* 1:本模式的RFIC连接在PMURF0_CLK_19M2
                                                                                   0: 表示未使用 */
    VOS_UINT16                              uhwReserved[4];                     /* 保留，将来扩展使用 */
}UCOM_NV_MODE_BASIC_EXT_PARA_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_TRI_MODE_CHAN_PARA_EXT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 全网通通道参数配置参数  (不能改变)
*****************************************************************************/
typedef struct
{
    UCOM_NV_MODE_BASIC_EXT_PARA_STRU        stModeBasicPara[8];                  /* 下标[0]:表示GSM模式下的前端器件的上下电控制;
                                                                                    下标[1]:表示WCDMA模式下的前端器件的上下电控制;
                                                                                    下标[2]:表示LTE模式下的前端器件的上下电控制;
                                                                                    下标[3]:表示TDS模式下的前端器件的上下电控制;
                                                                                    下标[4]:表示1X模式下的前端器件的上下电控制;
                                                                                    下标[5]:表示HRPD模式下的前端器件的上下电控制;
                                                                                    下标[6]:预留;
                                                                                    下标[7]:预留  */
    VOS_UINT32                              uwRfSwitch;                         /* 用于控制共分集的开关 */
    VOS_UINT32                              uwGsmRficSel;                       /* 信令模式下当前使用的通道（0：RF0,1：RF1） */
    VOS_UINT32                              uwGpioCtrl;                         /* 是否需要时钟切换(0:不需要, 1:需要 )*/
    VOS_UINT32                              uwCdmaRficSel;                      /* 信令模式下当前使用的通道（0：RF0,1：RF1） */
    VOS_UINT32                              auwReserved[13];                    /* 保留，将来扩展使用 */
}UCOM_NV_TRI_MODE_CHAN_PARA_EXT_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_FEM_CHAN_PROFILE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 8种场景的通道配置
*****************************************************************************/
typedef struct
{
    UCOM_NV_TRI_MODE_CHAN_PARA_EXT_STRU    astPara[UCOM_NV_TRI_MODE_CHAN_PARA_PROFILE_NUM];  /* 最多支持8个场景的配置 */
}UCOM_NV_FEM_CHAN_PROFILE_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_RF_RX_EVM_TEST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Wcdma RxEvm测试选择NV
*****************************************************************************/
typedef struct
{
    UCOM_NV_RX_EVM_TEST_EN_ENUM_UINT16  enRxEvmTestEn;                          /* RxEvm测试使能，0:正常模式,1:测试模式 */
    VOS_UINT16                          uhwReserved;
}UCOM_NV_W_RF_RX_EVM_TEST_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_DCXO_C_TRIM_DEFAULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Wcdma Afc校准
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwInitCfix;                            /* Afc校准方式 选择  */
    VOS_UINT16                          uhwFreqErrThr;                          /*C1是否需要自校准*/
    VOS_UINT16                          uhwCfixLowerLimit;                      /*C1是否需要自校准*/
    VOS_UINT16                          uhwCfixUpperLimit;                      /*C1是否需要自校准*/

}UCOM_NV_DCXO_C_TRIM_DEFAULT_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_M_DA_VALUE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : M值
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRfMDaValue;                          /* M值 */
    VOS_UINT16                          uhwReserved;
}UCOM_NV_CDMA_M_DA_VALUE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_MAXMIN_POWER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 最大最小功率
*****************************************************************************/
typedef struct
{
    VOS_INT16                          shwTxWirelessMaxPowerAch;                /* 无线ACH通道最大功率 */
    VOS_INT16                          shwTxWirelessMaxPowerTch;                /* 无线TCH通道最大功率 */
    VOS_INT16                          shwTxWireMaxPowerAch;                    /* 有线ACH通道最大功率 */
    VOS_INT16                          shwTxWireMaxPowerTch;                    /* 有线TCH通道最大功率 */
    VOS_INT16                          shwTxMinPower;                           /* 最小功率 */
    VOS_INT16                          shwReserved;
}UCOM_NV_CDMA_TX_POWER_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_TEST_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : WCDMA测试特性专用开关，默认测试特性都为关闭。0表示开关关闭 1表示开关打开
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwTestDrxIgnorePiValue:1;               /* 不考虑pi值，无条件进行PCH译码的处理 */
    VOS_UINT32                          uwTestDrxSccpchAlwaysOpen:1;            /* 不考虑pi值，且SCCPCH长开进行PCH译码的处理 */
    VOS_UINT32                          uwTestCpcMntnInfo:1;                    /* cpc可维可测开关,1-打开,0-关闭，默认关闭 */
    VOS_UINT32                          uwReserve:29;
}UCOM_NV_W_TEST_CTRL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_VIA_C_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Via CUse配置nv项
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwViaCSupportEn;                   /* 外置VIA C 支持使能，0-不使能，1--使能 */
    VOS_UINT16                              uhwViaCActiveIndGpio;               /* 外置VIA C 工作指示GPIO */
    VOS_UINT32                              uwViaCLineCtrlMask;                 /* 外置VIA C Band指示Mask */
    VOS_UINT32                              uwViaCLineCtrl;                     /* 外置VIA C Band指示线控值 */
}UCOM_NV_VIA_C_CONFIG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_B26_ANT_SHARE_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : B26共天线配置nv项
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwFeatureB26AntShareEn;            /* B26共天线使能，0-不使能，1--使能 */
    VOS_UINT16                              uhwReserved;                        /* 保留位 */
    VOS_UINT32                              uwB26AntShareDpdt;                  /* B26天线切换DPDT线控值 */
    VOS_UINT32                              uwB26TxDisableLineCtrl;             /* B26 TX关闭使能线控值 */
    VOS_UINT32                              uwB26VoLTESupportLineCtrl;          /* VoLTE指示管脚线控值 */
}UCOM_NV_B26_ANT_SHARE_CONFIG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_FEM_PIN_TO_GPIO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 线控索引和GPIO管脚号的映射表
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwFemPinToGpio[32];                 /* GPIO转换表 */
}UCOM_NV_FEM_PIN_TO_GPIO_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_RX_FE_NF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 射频下行接收噪声系数NF和插损FE和值
*****************************************************************************/
typedef struct
{
    VOS_INT16                          shwRxFeNfValue;                      /* 射频下行接收噪声系数NF和插损FE和值, 单位为0.1dbm*/
    VOS_INT16                          shwReserved;
}UCOM_NV_W_RX_FE_NF_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_RFFE_GPIO_VALUE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwGpioMask;                         /* 射频管脚掩码,0表示该bit位不需要控制 */
    VOS_UINT32                              uwGpioValue;                        /* 射频管脚输出电平 值,0表示该低电平，1表示高电平 */
}UCOM_NV_RFFE_GPIO_VALUE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GPIO_MIPI_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UCOM_NV_FEMIO_CTRL_MODE_ENUM_UINT32     enMode;                             /* 配置模式 */
    UCOM_NV_RFFE_GPIO_VALUE_STRU            stGpioCtrl;                         /* GPIO 配置 */
    UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU  stMipiCtrl;                         /* MIPI 配置 */
}UCOM_NV_GPIO_MIPI_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_FEM_GPIO_MIPI_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 天线开关配置，该结构体drv已经定义
*****************************************************************************/
typedef struct
{
    UCOM_NV_GPIO_MIPI_CTRL_STRU             stFemGpioMipiCtrl[UCOM_NV_FEM_IO_CFG_MAX];
}UCOM_NV_FEM_GPIO_MIPI_CTRL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_MAS_STATE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAS STATE的控制参量
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwStateEvaluateTime;               /* 阶段评估时间，单位:ms */
    VOS_INT16                               shwStateRscpDeltaThd;               /* Delta门限值，单位:dB */
}UCOM_NV_W_MAS_STATE_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_MAS_STATEI_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAS STATEI的控制参量
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwStateITime;                      /* 阶段I评估时间，单位:ms */
    VOS_INT16                               shwWorstRscpValue;                  /* 最差RSCP信号门限值，单位:dB */
    VOS_INT16                               shwWorseRscpValue;                  /* 较差RSCP信号门限值，单位:dB */
    VOS_INT16                               shwDeltaRscpValue;                  /* 手握导致信号强度下降判决门限 */

}UCOM_NV_W_MAS_STATEI_COM_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_MAS_STATEI_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAS STATEI的控制参量
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_MAS_STATEI_COM_STRU         stStateIActive;                       /* 主控StateI信息 */
    UCOM_NV_W_MAS_STATEI_COM_STRU         stStateIPassive;                      /* 被控StateI信息 */

}UCOM_NV_W_MAS_STATEI_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_MAS_STATEI_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAS STATEIAIB的控制参量
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_MAS_STATE_STRU                      stStateIaIbActiveInfo;        /* 主控StateIaIb信息 */
    UCOM_NV_W_MAS_STATE_STRU                      stStateIaIbPassiveInfo;       /* 被控StateIaIb信息 */

}UCOM_NV_W_MAS_STATEIAIB_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_MAS_STATEII_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAS STATEII的控制参量
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_MAS_STATE_STRU                              stStateIIBlindInfo;   /* 阶段II盲切信息 */
    UCOM_NV_W_TAS_NONBLIND_MEAS_STRU                      stStateIINonBlindInfo;/* 阶段II明切信息 */

}UCOM_NV_W_MAS_STATEII_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_MAS_STATEIII_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAS STATEII的控制参量
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwActiveFrozenTime;                /* 主控阶段III冻结时间 */
    VOS_UINT16                              uhwPassiveFrozenTime;               /* 被控阶段III冻结时间 */

}UCOM_NV_W_MAS_STATEIII_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_TAS_BLIND_MEAS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAS盲切测量的控制参量
*****************************************************************************/
typedef struct
{
   UCOM_NV_W_MAS_STATEI_STRU                              stInfoStateI;         /* 阶段I信息 */
   UCOM_NV_W_MAS_STATEIAIB_STRU                           stInfoStateIa;        /* 阶段IaIb信息 */
   UCOM_NV_W_MAS_STATEIAIB_STRU                           stInfoStateIb;        /* 阶段IaIb信息 */
   UCOM_NV_W_MAS_STATEII_STRU                             stInfoStateII;        /* 阶段II信息 */
   UCOM_NV_W_MAS_STATEIII_STRU                            stInfoStateIII;       /* 阶段III信息 */
   VOS_INT16                                              shwAntGoodEnoughThd;  /* 天线能量足够好RSCP门限值(单位为0.125dbm) */
   VOS_INT16                                              uhwReserve;
}UCOM_NV_W_MAS_SCHDL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_TAS_MAS_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAS算法控制参量
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_TAS_PHY_STATE_PARA_STRU       stTasPhyStatePara;                  /* 物理层状态上报参数门限 */
    UCOM_NV_W_TAS_SEARCHING_STATE_PARA_STRU stTasSearchingPara;                 /* 物理层搜网算法参数 */
    UCOM_NV_W_MAS_SCHDL_STRU                stMasPara;                          /* MAS参数 */

}UCOM_NV_W_TAS_MAS_CTRL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_W_TAS_MAS_RF_CTRL_STRU
 协议表格  :
 ASN.1描述 : auwBandBlindSwitchMap是针对每个band是否使用TAS盲切算法做的bitmap。
             auwBandBlindSwitchMap[0]bit0代表band1，bit1代表band2，以此类推。
             auwBandBlindSwitchMap[1]bit0代表band33，bit1代表band34，以此类推。
             bit位为1，代表此band使用盲切算法，否则反之。
 结构说明  : TAS射频相关控制参量
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              auwBandBlindSwitchMap[2];           /* BAND是否适用盲切 */
    UCOM_NV_W_TAS_CTRL_WORD_STRU            stTasCtrlWord;                      /* 天线切换控制字 */
    VOS_UINT32                              auwBandIaEnable[2];                 /* 第一字节uwBandIaEnable[0]从低到高分别代表Band0~Band31是否支持Ia:0,不支持；1，支持*/
                                                                                /* 第二字节uwBandIaEnable[1]从低到高分别代表Band32~Band63是否支持Ia:0,不支持；1，支持*/
    VOS_UINT32                              auwBandIbEnable[2];                 /* 第一字节uwBandIbEnable[0]从低到高分别代表Band0~Band31是否支持Ib:0,不支持；1，支持*/
                                                                                /* 第二字节uwBandIbEnable[1]从低到高分别代表Band32~Band63是否支持Ib:0,不支持；1，支持*/
}UCOM_NV_W_TAS_MAS_RF_CTRL_STRU;


typedef UCOM_NV_W_TAS_MAS_RF_CTRL_STRU     UCOM_NV_CDMA_TAS_MAS_RF_CTRL_STRU; /* CDMA TAS RF Ctrl */

/*****************************************************************************
 结构名    : UCOM_NV_GSM_PSRCH_SEARCH_PCELL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 在Search状态下,并行搜索时读取系统消息和提前同步个数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwDsdaBcchNum;                     /* DSDA情况下并行读取系统消息的个数 */
    VOS_UINT16                              uhwDsdaSyncNum;                     /* DSDA情况下并行读取系统消息之后提前同步个数 */
    VOS_UINT16                              uhwDsdsIdleBcchNum;                 /* DSDS情况下对方卡非DCH态并行读取系统消息的个数 */
    VOS_UINT16                              uhwDsdsIdleSyncNum;                 /* DSDS情况下对方卡非DCH态并行读取系统消息之后提前同步个数 */
    VOS_UINT16                              uhwDsdsDchBcchNum;                  /* DSDS情况下对方卡DCH态并行读取系统消息的个数 */
    VOS_UINT16                              uhwDsdsDchSyncNum;                  /* DSDS情况下对方卡DCH态并行读取系统消息之后提前同步个数 */
}UCOM_NV_GSM_PSRCH_SEARCH_PCELL_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_IDLE_PARALLEL_NUM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 在驻留状态下,并行搜索时读取系统消息和提前同步个数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwDsdaIdleBcchNum;                 /* DSDA情况下本卡IDLE态并行读取系统消息的个数 */
    VOS_UINT16                              uhwDsdaIdleSyncNum;                 /* DSDA情况下本卡IDLE态并行读取系统消息之后提前同步个数 */
    VOS_UINT16                              uhwDsdaDchBcchNum;                  /* DSDA情况下本卡DCH态并行读取系统消息的个数 */
    VOS_UINT16                              uhwDsdaDchSyncNum;                  /* DSDA情况下本卡DCH态并行读取系统消息之后提前同步个数 */
    VOS_UINT16                              uhwDsdsIdleBcchNum;                 /* DSDS情况下对方卡非DCH态并行读取系统消息的个数 */
    VOS_UINT16                              uhwDsdsIdleSyncNum;                 /* DSDS情况下对方卡非DCH态并行读取系统消息之后提前同步个数 */
    VOS_UINT16                              uhwDsdsDchBcchNum;                  /* DSDS情况下对方卡DCH态并行读取系统消息的个数 */
    VOS_UINT16                              uhwDsdsDchSyncNum;                  /* DSDS情况下对方卡DCH态并行读取系统消息之后提前同步个数 */
}UCOM_NV_GSM_PSRCH_IDLE_PCELL_STRU;




/*****************************************************************************
 结构名    : UCOM_NV_GSM_PSRCH_PCELL_NUM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 在Search状态下,并行搜索时读取系统消息和提前同步个数
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_PSRCH_SEARCH_PCELL_STRU     stSearchPcellNum;                   /* 本卡Search状态下,并行度 */
    UCOM_NV_GSM_PSRCH_IDLE_PCELL_STRU       stIdlePcellNum;                     /* 本卡idle状态下,并行度 */
}UCOM_NV_GSM_PSRCH_PCELL_NUM_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_CDMA_LPC_SWITCH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSDR低功耗开关，初始版本默认都关闭
*****************************************************************************/
typedef struct
{
    VOS_UINT32          uhwDeepSleepEnable:1;          /* bit0:CSDR深睡允许标志 */
    VOS_UINT32          uhw1xMasterDrxEnable:1;        /* bit1:1X主模睡眠允许标志  */
    VOS_UINT32          uhw1xSlaveDrxEnable:1;         /* bit2:1X从模睡眠允许标志  */
    VOS_UINT32          uhwHrpdMasterDrxEnable:1;      /* bit3:HRPD主模睡眠允许标志  */
    VOS_UINT32          uhwHrpdSlaveDrxEnable:1;       /* bit4:HRPD从模睡眠允许标志  */
    VOS_UINT32          uhwResverd:27;                 /* bit5~31 */
}UCOM_NV_CDMA_LPC_SWITCH_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_CDMA_LPC_ADV_WAKEUP_TIME_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSDR低功耗，配置各个组件提前唤醒时间
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      uhwMcuStableTime;    /* MCU上电稳定需要的时间，单位us */
    VOS_UINT16                      uhwDrvStableTime;    /* DRV上电稳定需要的时间，单位us */
    VOS_UINT16                      uhwOamStableTime;    /* OAM上电稳定需要的时间，单位us */
    VOS_UINT16                      uhwCphyStableTime;   /* PHY上电稳定需要的时间，单位us */
    VOS_UINT16                      uhwResverd1;
    VOS_UINT16                      uhwResverd2;
}UCOM_NV_CDMA_LPC_ADV_WAKEUP_TIME_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_CF_GAP_LENGTH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HRPD 异频沟长
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwCfGapLength;                 /* HRPD 异频沟长，单位slot */
    VOS_UINT16          uhwResverd;                     /* 保留位 */
}UCOM_NV_CDMA_CF_GAP_LENGTH_STRU;




/*****************************************************************************
 结构名    : UCOM_NV_CDMA_TAS_ACCESS_PARA_STRU
 协议表格  :
 结构说明  : access态下,随机接入失败次数判断门限N_FAIL
*****************************************************************************/
typedef struct
{

   VOS_UINT16           uhwAccessNFailThreshold;                                /* ACCESS态，随机接入失败次数判断门限,对应CTTF接口中usSeqNum字段 */
   VOS_UINT16           uhwRsv;                                                 /* 保留 */

}UCOM_NV_CDMA_TAS_ACCESS_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_TAS_RSCP_REPORT_T1_STRU
 协议表格  :
 结构说明  : RSCP Report T1值定义
*****************************************************************************/
typedef struct
{

   VOS_UINT16           uhwHighSpeedT1;                                         /* 速度估计为高速的时候，RSCP上报周期T1取值，默认160ms */
   VOS_UINT16           uhwMidSpeedT1;                                          /* 速度估计为中速的时候，RSCP上报周期T1取值，默认320ms */
   VOS_UINT16           uhwLowSpeedT1;                                          /* 速度估计为低速的时候，RSCP上报周期T1取值，默认640ms */
   VOS_UINT16           uhwRsv;                                                 /* 4字节对齐 */
}UCOM_NV_CDMA_TAS_RSCP_REPORT_T1_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_CDMA_TAS_CTRL_STRU
 协议表格  :
 结构说明  : cdma 1x tas特性控制NV定义
*****************************************************************************/
typedef struct
{
   UCOM_NV_CDMA_TAS_ACCESS_PARA_STRU        stTasAccessPara;                    /* Access态下，Tas配置参数结构体 */
   UCOM_NV_CDMA_TAS_RSCP_REPORT_T1_STRU     stTasTchRspcT1Para;                 /* TCH态下，Rscp T1参数          */
}UCOM_NV_CDMA_TAS_CTRL_PARA_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_VIA_C_SEC_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Via CUse副卡配置nv项
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwViaCSecSupportEn;                /* 外置VIA C 副卡支持使能，0-不使能，1--使能 */
    VOS_UINT16                              uhwReserved;                        /* 保留位 */
    VOS_UINT32                              uwViaCSpdt;                         /* 上电初始化Cdma通道切换线控值，支持多个bit配置 */
    VOS_UINT32                              uwViaCSecLineCtrlMask;              /* 副卡外置VIA C Band指示Mask */
    VOS_UINT32                              uwViaCSecLineCtrl;                  /* 副卡外置VIA C Band指示线控值 */
}UCOM_NV_VIA_C_SEC_CONFIG_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_UPRAISE_POWER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 无线模式下，初始接入场景提升发射功率NV控制
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwUpraisePowerEnable;                  /* 功率提升特性开关:关闭为0,打开为1 */
    VOS_UINT16                          uhwUpraisePowerLevel;                   /* 功率提升的门限(建议抬升1~2个PCL)，单位: PCL */
}UCOM_NV_GSM_UPRAISE_POWER_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_TIME_AVG_SAR_FUNC_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 时间平均降SAR功能NV
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwTimeAvgSarFuncEnable;        /* 时间平均降SAR功能开关 */
    VOS_UINT16                                  uhwReserved;                    /* 保留字段 */
}UCOM_NV_TIME_AVG_SAR_FUNC_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_GSM_SAR_TIME_AVG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM时间平均降SAR NV结构体
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwGsmSarDprOnThd;              /* GSM启动动态功率回退的功率门限，单位0.1 dBm */
    VOS_INT16                                   shwGsmSarDprOffThd;             /* GSM关闭动态功率回退的功率门限，单位0.1 dBm */
    VOS_INT16                                   ashuwGmskSarLimitedMaxPwr[UCOM_NV_G_TX_SLOT_MAX_NUM];   /* GMSK调制方式1-4个发射时隙的启动DPR的最大限制功率，单位0.1 dBm */
    VOS_INT16                                   ashuw8pskSarLimitedMaxPwr[UCOM_NV_G_TX_SLOT_MAX_NUM];   /* 8PSK调制方式1-4个发射时隙的启动DPR的最大限制功率，单位0.1 dBm */
    VOS_UINT16                                  uhwGsmTimeAvgSarPeriod;         /* GSM时间平均SAR的判决周期(包含400个统计周期),单位s */
    VOS_UINT16                                  uhwRsv;                         /* 保留值 */
}UCOM_NV_GSM_SAR_TIME_AVG_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_W_SAR_TIME_AVG_SAR_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Wcdma时间平均SAR控制
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwWcdmaSarDprOnThd;                    /* WPHY启动动态功率回退功率门限,单位0.1dbm */
    VOS_INT16                           shwWcdmaSarDprOffThd;                   /* WPHY取消动态功率回退功率门限,单位0.1dbm */
    VOS_INT16                           shwWcdmaSarLimitedPwr;                  /* WPHY启动功率回退后的最大限制功率,单位0.1dbm */
    VOS_UINT16                          uhwWcdmaSarAdjudgePeriod;               /* WPHY时间平均SAR的判决周期,如3分钟或6分钟,单位s */
}UCOM_NV_W_SAR_TIME_AVG_SAR_CTRL_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_XO_SELF_CAL_ENABLE
 协议表格  :
 ASN.1描述 :
 结构说明  : 是否使用新方法校准XO
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwXoCalEnable;                         /* 是否使用新方法校准 */
    VOS_UINT16                          uhwReserve;
}UCOM_NV_XO_SELF_CAL_ENABLE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_XO_SELF_CAL_DONE
 协议表格  :
 ASN.1描述 :
 结构说明  : 是否已使用新方法校准XO
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwXoCalDone;                           /* 是否已使用新方法校准 */
    VOS_UINT16                          uhwReserve;
}UCOM_NV_XO_SELF_CAL_DONE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_XO_REF_TEMP_COMP
 协议表格  :
 ASN.1描述 :
 结构说明  : XO校准计算参数
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwXoRefTemp;                           /* XO参考温度 */
    VOS_UINT16                          uhwReserve;
    VOS_UINT16                          uhwA2Exponent;                          /* 依次存放a2的指数 */
    VOS_UINT16                          uhwA3Exponent;                          /* 依次存放a3的指数 */
    VOS_UINT32                          uwA2Mantissa;                           /* 依次存放a2的尾数 */
    VOS_UINT32                          uwA3Mantissa;                           /* 依次存放a3的尾数 */
    VOS_UINT16                          uhwA2ExponentDefault;                   /* 依次存放a2的指数 */
    VOS_UINT16                          uhwA3ExponentDefault;                   /* 依次存放a3的指数 */
    VOS_UINT32                          uwA2MantissaDefault;                    /* 依次存放a2的尾数 */
    VOS_UINT32                          uwA3MantissaDefault;                    /* 依次存放a3的尾数 */
    VOS_INT16                           shwTmax;                                /* XO最大工作温度 */
    VOS_INT16                           shwTmin;                                /* XO最小工作温度 */
}UCOM_NV_XO_REF_TEMP_COMP_STRU;


/*****************************************************************************
 结构名    : UCOM_NV_XO_SELF_CAL_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : XO校准参数
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwC1C2Temp;                    /* 单位0.1度，C1C2校准结束后温度门限   */
    VOS_INT16                                   shwA0A1Temp;                    /* 单位0.1度，a0、a1校准结束后的温度门限，即最后一个样本点的温度 */
    VOS_UINT16                                  uhwA0A1Time;                    /*单位ms，校准a0、a1时的时间门限 */
    UCOM_NV_DCXO_TEMP_RISE_METHOD_ENUM_UINT16   enTempRiseMethod;               /*升温方法，1表示AP升温，2表示PA升温，3表示AP、PA一起升温 */
    VOS_INT16                                   shwTempRiseStep;                /* 单位0.1度, 校准a0、a1时的每次升温超过多少度采集一次频偏结果 */
    VOS_UINT16                                  uhwTempVsFreqNum;               /*采集几个频偏结果后进行a0、a1计算 */
    VOS_UINT16                                  uhwGetTempTimeStep;             /*单位ms，每次温度读取间隔 */
    VOS_UINT16                                  uhwRiseTimeStable;              /*单位ms，AP或PA升温后，等待多少时间后开始采集温度频偏结果 */
    VOS_UINT16                                  uhwTotalCoreNum;                /*AP总共的核数 */
    VOS_UINT16                                  uhwRiseTempCoreNum;             /*AP升温方式，起始烧的AP核的个数  */
}UCOM_NV_XO_SELF_CAL_PARA_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_XO_CAL_AGC_GAIN_INDEX_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : XO校准时Rx AGC档位
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRxLevel;                             /* 下行档位 */
    VOS_INT16                           shwToneLevel;                           /* 仪器发射信号强度 */
}UCOM_NV_XO_CAL_AGC_GAIN_INDEX_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_CSDR_HRPD_FIX_DRCVALUE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : cdma hrpd csdr固定drcvalue的NV定义
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwFixDrcValueFlag;                                     /* 允许固定drc value标志 */
    VOS_UINT16          uhwFixedDrcValue;                                       /* 固定的drc value值 */
}UCOM_NV_CSDR_HRPD_FIX_DRCVALUE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_INTERFE_RULE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 干扰判决业务类型定义
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  uhwIdle         :4;                             /* 空闲状态 UCOM_NV_INTERFE_BUSINESS_TYPE_IDLE */
    VOS_UINT32                  uhwData         :4;                             /* 数传业务状态 UCOM_NV_INTERFE_BUSINESS_TYPE_PS*/
    VOS_UINT32                  uhwVoice        :4;                             /* 语音业务状态 UCOM_NV_INTERFE_BUSINESS_TYPE_CS*/
    VOS_UINT32                  uhwReversed     :20;                            /* 保留 */
}UCOM_NV_INTERFE_JUDGE_BUSINESS_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_INTERFE_JUDGE_BUSINESS_UNION
 协议表格  :
 ASN.1描述 :
 结构说明  : 业务类型定义
*****************************************************************************/
typedef union
{
    VOS_UINT32                              uhwInterJudgeBusiness;              /* 干扰判决业务类型 */
    UCOM_NV_INTERFE_JUDGE_BUSINESS_STRU     stInterfeJudgeBusiness;             /* 干扰判决业务类型定义值 */
} UCOM_NV_INTERFE_JUDGE_BUSINESS_UNION;

/*****************************************************************************
 结构名    : UCOM_NV_INTERFE_RULE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 最大功率回退业务类型定义
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  uwOppositeIdle          :5;                            /* 对方模空闲状态 */
    VOS_UINT32                  uwCurrentIdle           :5;                            /* 当前模空闲状态 */
    VOS_UINT32                  uwOppositeData          :5;                            /* 对方模数传业务状态 */
    VOS_UINT32                  uwCurrentData           :5;                            /* 当前模数传业务状态 */
    VOS_UINT32                  uwOppositeVoice         :5;                            /* 对方模语音业务状态 */
    VOS_UINT32                  uwCurrentVoice          :5;                            /* 当前模语音业务状态 */
    VOS_UINT32                  uwReversed              :2;                            /* 保留 */
}UCOM_NV_POWER_BACKOFF_BUSINESS_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_POWER_BACKOFF_BUSINESS_UNION
 协议表格  :
 ASN.1描述 :
 结构说明  : 最大功率回退定义
*****************************************************************************/
typedef union
{
    VOS_UINT32                                      uwPowerBackoffBusiness;    /* 最大功率回退业务类型 */
    UCOM_NV_POWER_BACKOFF_BUSINESS_STRU             stPowerBackoffBusines;     /* 最大功率回退业务类型定义值 */
} UCOM_NV_POWER_BACKOFF_BUSINESS_UNION;
/*****************************************************************************
 结构名    : UCOM_NV_INTERFE_BAND_MODE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 频段和模式类型定义
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  uwCurrentBand           :8;                     /* 当前模频段 */
    VOS_UINT32                  uwCurrentMode           :8;                     /* 当前模模式类型,0:GSM;1:WCDMA;2:LTE;3:TDS;4:CDMA */
    VOS_UINT32                  uwOppositeBand          :8;                     /* 对方模频段 */
    VOS_UINT32                  uwOppositeMode          :8;                     /* 对方模模式类型,0:GSM;1:WCDMA;2:LTE;3:TDS;4:CDMA */
}UCOM_NV_INTERFE_BAND_MODE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_INTERFE_RULE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 干扰判决一条数据定义
*****************************************************************************/
typedef struct
{
    UCOM_NV_INTERFE_BAND_MODE_STRU              stInterfeBandMode;              /* 当前对方模频段和模式类型定义 */

    UCOM_NV_INTERFE_JUDGE_BUSINESS_UNION        aunBusinessType[UCOM_NV_INTERFERENCE_BUSINESS_TYPE_NUM];/* 业务类型 */
    VOS_UINT16                                  uhwReversed;                    /* 保留 */
    VOS_UINT16                                  uhwRxBlankLowFreq;              /* Rx Blanking范围低频率 */
    VOS_UINT16                                  uhwRxBlankHighFreq;             /* Rx Blanking范围高频率 */
    VOS_UINT16                                  uhwTxBlankLowFreq;              /* Tx Blanking范围低频率 */
    VOS_UINT16                                  uhwTxBlankHighFreq;             /* Tx Blanking范围高频率 */
} UCOM_NV_INTERFE_RULE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_INTERFE_RULE_TABLE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 干扰判决表定义
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwValidCount;
    UCOM_NV_INTERFE_RULE_STRU                   stInterferenceRule[UCOM_NV_INTERFERENCE_TABLE_MAX_NUM]; /* 干扰判决表 */
} UCOM_NV_INTERFE_RULE_TABLE_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_INTERFE_BACKOFF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 最大功率回退定义
*****************************************************************************/
typedef struct
{
    UCOM_NV_INTERFE_BAND_MODE_STRU              stInterfeBandMode;              /* 当前对方模频段和模式类型定义 */
    UCOM_NV_POWER_BACKOFF_BUSINESS_UNION        aunBusinessType[UCOM_NV_INTERFERENCE_BUSINESS_TYPE_NUM];/* 业务类型 */
} UCOM_NV_INTERFE_BACKOFF_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_INTERFE_POWER_BACKOFF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 最大功率回退表定义
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwValidCount;
    UCOM_NV_INTERFE_BACKOFF_STRU                stInterfePowerBackoff[UCOM_NV_INTERFERENCE_TABLE_MAX_NUM];/* 最大功率回退表 */
} UCOM_NV_INTERFE_POWER_BACKOFF_STRU;

/*****************************************************************************
 结构名    : UCOM_NV_FEATURE_INTERFE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 特性开关定义
*****************************************************************************/
typedef struct
{
    UCOM_NV_INTERFE_FEATURE_SWITCH_ENUM_UINT16          enInterfeSwitch;        /* 特性开关 */
    VOS_UINT16                                          uhwReversed;            /* 保留*/
} UCOM_NV_FEATURE_INTERFE_STRU;

/****************************************************************************
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







#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif /* end of PhyNvDefine.h */


