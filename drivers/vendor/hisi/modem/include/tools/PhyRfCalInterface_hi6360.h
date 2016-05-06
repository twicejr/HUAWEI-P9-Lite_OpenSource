/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : PhyRfCalInterface_hi6360.h
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

#ifndef __PHYRFCALINTERFACE_HI6360_H__
#define __PHYRFCALINTERFACE_HI6360_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define MASK_SELF_CAL_TX_IQ_MISMATCH_HI6360        ( 0x0001 )
#define MASK_SELF_CAL_W_RX_DCR_HI6360              ( 0x0002 )
#define MASK_SELF_CAL_W_RX_IP2_HI6360              ( 0x0004 )

#define SELF_CAL_BAND_ID_MAX_COUNT_HI6360          ( 10 )

#define W_RX_NOBLOCK_AGC_GAIN_COUNT_HI6360         ( 8 )
#define W_RX_BLOCK_AGC_GAIN_COUNT_HI6360           ( 5 )

/* Mask code Used for RF_CAL_W_CFG_REQ_STRU */
#define MASK_CAL_RF_W_TX_AFC_HI6360                ( 0x0001 )
#define MASK_CAL_RF_W_TX_ARFCN_HI6360              ( 0x0002 )
#define MASK_CAL_RF_W_TX_TXONOFF_HI6360            ( 0x0004 )
#define MASK_CAL_RF_W_TX_PAMODE_HI6360             ( 0x0008 )
#define MASK_CAL_RF_W_TX_DBB_RF_ATTEN_HI6360       ( 0x0010 )
#define MASK_CAL_RF_W_TX_POWER_HI6360              ( 0x0020 )
#define MASK_CAL_RF_W_RX_RXONOFF_HI6360            ( 0x0040 )
#define MASK_CAL_RF_W_RX_ARFCN_HI6360              ( 0x0080 )
#define MASK_CAL_RF_W_RX_ANTSEL_HI6360             ( 0x0100 )
#define MASK_CAL_RF_W_RX_CARRMODE_HI6360           ( 0x0200 )
#define MASK_CAL_RF_W_TX_PWR_ATTEN_HI6360          ( 0x0400 )
#define MASK_CAL_RF_W_PD_ONOFF_HI6360              ( 0x0800 )
#define MASK_CAL_RF_W_RX_AGC_GAIN_HI6360           ( 0x1000 )
#define MASK_CAL_RF_W_TX_PA_VBIAS_HI6360           ( 0x2000 )
#define MASK_CAL_RF_W_TX_CFIX_HI6360               ( 0x4000 )
#define MASK_CAL_RF_W_TX_UPA_HI6360                ( 0x8000 )

/* Mask code Used for PHY_RF_CAL_W_TRX_FAST_CAL_REQ_STRU_HI6360 */
#define MASK_CAL_RF_W_TX_FAST_PDM_HI6360           ( 0x0001 )
#define MASK_CAL_RF_W_TX_FAST_PWR_HI6360           ( 0x0002 )
#define MASK_CAL_RF_W_TX_FAST_ATTEN_HI6360         ( 0x0004 )
#define MASK_CAL_RF_W_TX_FAST_PAVBIAS_HI6360       ( 0x0008 )
#define MASK_CAL_RF_W_TX_FAST_PDVGA_HI6360         ( 0x0010 )
#define MASK_CAL_RF_W_TX_FAST_PDDISTUNE_HI6360     ( 0x0020 )

/* W Rx 载波模式 */
#define W_RX_CARRIER_MODE_SC_HI6360                ( 0 )
#define W_RX_CARRIER_MODE_DC_HI6360                ( 1 )

#define W_TRX_MAX_STEP_CNT_HI6360                  ( 16 )
#define W_TRX_MAX_SWEEP_FRAME_CNT_HI6360           ( 50 )

/* StepData Bit */
#define W_TX_PWR_ATTEN_BIT_HI6360                  ( 0x000003FF )
#define W_RX_AGC_MODE_BIT_HI6360                   ( 0x00003C00 )
#define W_TX_PA_MODE_BIT_HI6360                    ( 0x0000C000 )
#define W_TX_PA_VBIAS_BIT_HI6360                   ( 0x007F0000 )
#define W_TX_PD_VGA_BIT_HI6360                     ( 0x07800000 )
#define W_TX_PD_DISTUNE_BIT_HI6360                 ( 0x78000000 )

/* W模校准上报时成功失败标识 */
#define WPHY_TOOL_CAL_RESULT_RPT_SUCCESS_HI6360    ( 0 )
/*  G TRX CFG MARCO
*/
//////////////////////////////////////////////////////////////////////////
/* Mask code Used for RF_CAL_G_TX_PARA_CFG_REQ_STRU */
#define MASK_CAL_RF_G_TX_AFC_HI6360         ( 0x0001 )  /* 下发单板频率控制值 */
#define MASK_CAL_RF_G_TX_ARFCN_HI6360       ( 0x0002 )  /* 下发发射频点 */
#define MASK_CAL_RF_G_TX_TXEN_HI6360        ( 0x0004 )  /* 下发发射控制位 */

/* Mask code Used for RF_CAL_G_RX_PARA_CFG_REQ_STRU */
#define MASK_CAL_RF_G_RX_ARFCN_HI6360       ( 0x0001 )  /* 下发频点 */
#define MASK_CAL_RF_G_RX_MODE_HI6360        ( 0x0002 )  /* 下发接收模式 */
#define MASK_CAL_RF_G_RX_AGCMODE_HI6360     ( 0x0004 )  /* 下发测量模式 */
#define MASK_CAL_RF_G_RX_AGCGAIN_HI6360     ( 0x0008 )  /* 下发AGC档位 */

#define G_TX_PARA_MAX_SLOT_CNT_PER_FRAME_HI6360  ( 4 )

/* Mask code Used for PHY_RF_CAL_G_TX_FAST_CAL_REQ_STRU */
#define MASK_RF_CAL_G_TX_FAST_POWER         ( 0x0001 )  /* 下发功率(0.125dBm) */
#define MASK_RF_CAL_G_TX_FAST_AGC           ( 0x0002 )  /* 下发AGC */
#define MASK_RF_CAL_G_TX_FAST_POWER_ATTEN   ( 0x0004 )  /* 下发8PSK Power Atten */
#define MASK_RF_CAL_G_TX_FAST_PCL           ( 0x0008 )  /* 下发8PSK PCL */
#define MASK_RF_CAL_G_TX_FAST_PAVBIAS       ( 0x0010 )  /* 下发8PSK PaVbias */

#define G_TX_MAX_STEP_CNT_HI6360            ( 7 )       /* 当前只支持4时隙*/
#define G_TX_MAX_SWEEP_FRAME_CNT_HI6360     ( 120 )
#define G_RX_MAX_STEP_CNT_HI6360            ( 7 )
#define G_RX_MAX_SWEEP_FRAME_CNT_HI6360     ( 100 )
#define G_RX_MAX_RSSI_CNT_HI6360            ( G_RX_MAX_SWEEP_FRAME_CNT_HI6360 * G_RX_MAX_STEP_CNT_HI6360)
#define W_GAUGE_RESULT_SIZE_HI6360          ( 13 )      /* 32K校准上报数据个数 */
/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
 枚举名    :PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360
 协议表格  :
 ASN.1描述 :
 枚举说明  :RF CAL MSG ID ENUM
*****************************************************************************/
enum PHY_TOOL_MSG_ID_ENUM_HI6360
{
    /* WCDMA RF慢速校准接口原语列表 */
    ID_TOOL_WPHY_CAL_TRX_PARA_CFG_REQ_HI6360       = 0x1230,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_TRX_PARA_CFG_REQ_STRU_HI6360 */

    ID_TOOL_WPHY_CAL_RX_RSSI_MEAS_REQ_HI6360       = 0x1231,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_RX_RSSI_MEAS_REQ_STRU_HI6360 */
    ID_WPHY_TOOL_CAL_RX_RSSI_MEAS_IND_HI6360       = 0x21EA,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_RX_RSSI_MEAS_IND_STRU_HI6360 */

    /* WCDMA RF自校准接口原语列表 */
    ID_TOOL_WPHY_CAL_SELF_CAL_REQ_HI6360           = 0x1229,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_SELF_CAL_REQ_STRU_HI6360 */
    ID_WPHY_TOOL_CAL_SELF_CAL_IND_HI6360           = 0x21E8,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_SELF_CAL_IND_STRU_HI6360 */

    /* WCDMA RF快速校准接口原语列表 */
    ID_TOOL_WPHY_CAL_TRX_FAST_CAL_REQ_HI6360       = 0x1227,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_TRX_FAST_CAL_REQ_STRU_HI6360 */
    ID_WPHY_TOOL_CAL_TRX_FAST_CAL_IND_HI6360       = 0x21E6,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_TRX_FAST_CAL_IND_STRU_HI6360 */

    /* W RF通用CNF */
    ID_WPHY_TOOL_CAL_RF_MSG_CNF_HI6360             = 0x21E0,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_RF_MSG_CNF_STRU_HI6360 */

    ID_WPHY_TOOL_CAL_TX_POWER_DETECT_IND_HI6360    = 0x21E4,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_W_RF_TX_PD_IND_STRU_HI6360 */

    ID_WPHY_TOOL_GAUGE_REQ_HI6360                  = 0x1232,                           /* _H2ASN_MsgChoice  WPHY_TOOL_GAUGE_REQ_STRU */
    ID_WPHY_TOOL_GAUGE_CNF_HI6360                  = 0x21E5,                           /* _H2ASN_MsgChoice  WPHY_TOOL_GAUGE_CNF_STRU_HI6360 */
    ID_WPHY_TOOL_GAUGE_IND_HI6360                  = 0x21E6,                           /* _H2ASN_MsgChoice  WPHY_TOOL_GAUGE_IND_STRU_HI6360 */

    /* GSM RF慢速校准接口原语列表 */
    ID_TOOL_GPHY_CAL_TX_PARA_CFG_REQ_HI6360 = 0x1732,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_TX_PARA_CFG_REQ_STRU */
    ID_TOOL_GPHY_CAL_RX_PARA_CFG_REQ_HI6360 = 0x1733,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_PARA_CFG_REQ_STRU */

    ID_TOOL_GPHY_CAL_RX_RSSI_MEAS_REQ_HI6360= 0x1734,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_RSSI_MEAS_REQ_STRU */
    ID_GPHY_TOOL_CAL_RX_RSSI_MEAS_IND_HI6360= 0x7118,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_RSSI_MEAS_IND_STRU */

    /* GSM RF自校准接口原语列表 */
    ID_TOOL_GPHY_CAL_SELF_CAL_REQ_HI6360           = 0x1731,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_SELF_CAL_REQ_STRU_HI6360 */
    ID_GPHY_TOOL_CAL_SELF_CAL_IND_HI6360           = 0x7116,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_SELF_CAL_IND_STRU_HI6360 */

    /* GSM RF快速校准接口原语列表 */
    ID_TOOL_GPHY_CAL_TX_FAST_CAL_REQ_HI6360 = 0x1721,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_TX_FAST_CAL_REQ_STRU */

    /* G RF通用CNF */
    ID_GPHY_TOOL_CAL_RF_MSG_CNF_HI6360      = 0x7112,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RF_MSG_CNF_STRU */

    ID_TOOL_GPHY_CAL_RX_FAST_CAL_REQ_HI6360 = 0x1720,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_FAST_CAL_REQ_STRU */
    ID_GPHY_TOOL_CAL_RX_FAST_CAL_IND_HI6360 = 0x7113,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_FAST_CAL_IND_STRU */

    ID_TOOL_GPHY_CAL_RX_IP2_CAL_REQ         = 0x1728,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_IP2_CAL_REQ_STRU */
    ID_GPHY_TOOL_CAL_RX_IP2_CAL_IND         = 0x7117,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_IP2_CAL_IND_STRU */

    ID_TOOL_GPHY_CAL_RX_DCR_START_REQ       = 0x1725,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_DCR_START_REQ_STRU */
    ID_GPHY_TOOL_CAL_RX_DCR_RPT_IND         = 0x7114,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_DCR_RPT_IND_STRU */
    ID_GPHY_TOOL_CAL_RX_DCR_STOP_CNF        = 0x7115,                           /* _H2ASN_MsgChoice  PHY_RF_CAL_G_RX_DCR_STOP_CNF_STRU */

};
typedef UINT16 PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360;


/*****************************************************************************
 枚举名    :RF_CAL_SELF_CAL_ERR_CODE_ENUM_UINT16_HI6360
 协议表格  :
 ASN.1描述 :
 枚举说明  :RF CAL W/G Self Cal Fail Code ENUM
*****************************************************************************/
enum RF_CAL_SELF_CAL_ERR_CODE_ENUM_HI6360
{
    RF_CAL_SELF_CAL_SUCCESS_HI6360                 = 0,
    RF_CAL_SELF_CAL_IQ_MISMATCH_FAIL_HI6360,
    RF_CAL_SELF_CAL_W_RX_DCOFFSET_FAIL_HI6360,
    RF_CAL_SELF_CAL_W_RX_IP2_FAIL_HI6360,
    RF_CAL_SELF_CAL_BUTT_HI6360,
};
typedef UINT16 RF_CAL_SELF_CAL_ERR_CODE_ENUM_UINT16_HI6360;



/*****************************************************************************
 枚举名    :W_FAST_TX_STEP_TYPE_ENUM_UINT16_HI6360
 协议表格  :
 ASN.1描述 :
 枚举说明  :RF CAL W TRX FAST ENUM
*****************************************************************************/
enum W_FAST_TX_STEP_TYPE_ENUM_HI6360
{
    TX_STEP_TYPE_PDM_HI6360                        = 0,
    TX_STEP_TYPE_PWR_HI6360,
    TX_STEP_TYPE_ATTEN_HI6360,
    TX_STEP_TYPE_BUTT_HI6360
};
typedef UINT16 W_FAST_TX_STEP_TYPE_ENUM_UINT16_HI6360;


/*****************************************************************************
 枚举名    :W_FAST_STEP_WIDTH_ENUM_UINT16_HI6360
 协议表格  :
 ASN.1描述 :
 枚举说明  :RF CAL W TRX FAST ENUM
*****************************************************************************/

enum W_FAST_STEP_WIDTH_ENUM_HI6360
{
    WIDTH_10MS_HI6360                              = 10,
    WIDTH_20MS_HI6360                              = 20,
    WIDTH_30MS_HI6360                              = 30,
    WIDTH_40MS_HI6360                              = 40,
    WIDTH_BUTT_HI6360
};
typedef UINT16 W_FAST_STEP_WIDTH_ENUM_UINT16_HI6360;

/*****************************************************************************
 枚举名    :G_MODE_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum G_MODE_TYPE_ENUM_HI6360
{
    MODE_GMSK_HI6360                               = 0,
    MODE_8PSK_HI6360                               = 1,
    MODE_BUTT_HI6360
};
typedef UINT16 G_MODE_TYPE_ENUM_UINT16_HI6360;


/*****************************************************************************
 枚举名    :G_SINGLE_SLOT_CTRL_MODE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum G_SINGLE_SLOT_CTRL_MODE_ENUM_HI6360
{
    CTRL_GMSK_VPA_HI6360                           = 0,
    CTRL_POWER_HI6360                              = 1,
    CTRL_8PSK_PAVBIAS_DBB_RF_ATTEN_HI6360          = 2,
    CTRL_BUTT
};
typedef UINT16 G_SINGLE_SLOT_CTRL_MODE_ENUM_UINT16_HI6360;


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
 结构名    : PHY_RF_CAL_W_TX_UPA_PARA_STRU_HI6360
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
}PHY_RF_CAL_W_TX_UPA_PARA_STRU_HI6360;

/*****************************************************************************
 结构名    : PHY_RF_CAL_W_TRX_PARA_CFG_REQ_STRU_HI6360
 协议表格  :
 结构说明  : WCDMA RF慢速校准接口
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360      usMsgID;                                /* 原语类型 */
    UINT16                                  usRsv;                                  /* 保留位   */

    UINT16                                  usCfix;                                 /* DCXO Cfix 的控制字 */

    /* Tx Para Cfg */
    UINT16                                  usMask;                                 /* Reference MASK_CAL_RF_W_* */
    UINT16                                  usTxAfcInit;                            /* AFC初值 */
    UINT16                                  usTxBand;                               /* W模BAND:1表示BAND1,2表示BAND2,依次类推 */
    UINT16                                  usTxFreqNum;                            /* W模TX频点号,如BAND1的9750 */
    UINT16                                  usTxEnable;                             /* 0:不使能,1:使能 */
    UINT16                                  usTxPaMode;                             /* 0:自动控制;1:高增益;2:中增益;3:低增益 */
    INT16                                   sTxPower;                               /* 0.1dBm */
    INT16                                   sDbbAtten;                              /* DBB对信号衰减的控制字 */
    UINT16                                  usRfAtten;                              /* RF对信号衰减的控制字 */
    INT16                                   sTxPwrAtten;                            /* 对信号的衰减,单位0.1dBm */
    UINT16                                  usPaVbias;                              /* W PA Vbias 的控制字 */

    /* Rx Para Cfg */
    UINT16                                  usRxEnable;                             /* 0:不使能,1:使能 */
    UINT16                                  usRxBand;                               /* W模BAND:1表示BAND1,2表示BAND2,依次类推 */
    UINT16                                  usRxFreqNum;                            /* W模RX频点号,如BAND1的10700 */
    UINT16                                  usRxAntSel;                             /* 1:主集天线;2:分集天线 */
    UINT16                                  usRxAgcGain;                            /* BIT[15] : 1:5档, 0:8档;
                                                                                   BIT[3]  : 1:自动 0:DSP强配5/8档中的某一档
                                                                                   BIT[2:0]: 0:5/8档的第一档(增益最高的),依次类推 */
    UINT16                                  usRxCarrMode;                           /* 0:单载波;1:双载波 */

    /* 下面的参数是发射UPA需要使用的--为了不影响现有的AT命令,仅在该结构体后面增加相关变量 */
    UINT16                                  usUpaEnable;                            /* LMT发射UPA信号打开关闭.0:关闭;1:打开 */
    UINT16                                  usTxCarrMode;                           /* TX载波模式.0:单载波;1:双载波 */
    PHY_RF_CAL_W_TX_UPA_PARA_STRU_HI6360    stPrimCarr;                             /* 主载波相关的参数 */
    PHY_RF_CAL_W_TX_UPA_PARA_STRU_HI6360    stSecondCarr;                           /* 辅载波相关的参数 */

}PHY_RF_CAL_W_TRX_PARA_CFG_REQ_STRU_HI6360;


/*****************************************************************************
 结构名    : PHY_RF_CAL_W_RF_MSG_CNF_STRU_HI6360
 协议表格  :
 结构说明  : W TRX 快慢速校准通用CNF
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    UINT16                              usRecMsgID;                             /* 对应的下发Msg ID */
    UINT16                              usFlag;
}PHY_RF_CAL_W_RF_MSG_CNF_STRU_HI6360;


/*****************************************************************************
 结构名    : PHY_RF_CAL_W_RF_TX_PD_IND_STRU_HI6360
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv1;
    INT16                               sPdHkadc;
    UINT16                              usRsv2;
}PHY_RF_CAL_W_RF_TX_PD_IND_STRU_HI6360;


/*****************************************************************************
 结构名    : PHY_RF_CAL_W_RX_RSSI_MEAS_REQ_STRU_HI6360
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    UINT16                              usMeasNum;
    UINT16                              usInterval;
}PHY_RF_CAL_W_RX_RSSI_MEAS_REQ_STRU_HI6360;


/*****************************************************************************
 结构名    : PHY_RF_CAL_W_RX_RSSI_MEAS_IND_STRU_HI6360
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    INT16                               sRSSI;
    UINT16                              usAgcState;
}PHY_RF_CAL_W_RX_RSSI_MEAS_IND_STRU_HI6360;


/*****************************************************************************
 结构名    : PHY_RF_CAL_W_SELF_CAL_REQ_STRU_HI6360
 协议表格  :
 结构说明  : WCDMA RF Self Cal接口
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    UINT16                              usSelfCalMask;                          /* reference to MASK_SELF_CAL_* */
    UINT16                              usRfBandCount;                          /* 存放DSP频段个数 */
    UINT16                              ausBandId[SELF_CAL_BAND_ID_MAX_COUNT_HI6360];
}PHY_RF_CAL_W_SELF_CAL_REQ_STRU_HI6360;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_SELF_CAL_REQ_STRU_HI6360
 协议表格  :
 结构说明  : WCDMA RF Self Cal接口
*****************************************************************************/
typedef PHY_RF_CAL_W_SELF_CAL_REQ_STRU_HI6360 PHY_RF_CAL_G_SELF_CAL_REQ_STRU_HI6360;



/*****************************************************************************
 结构名    : TX_IQ_MISMATCH_DCR_STRU_HI6360
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    INT16                               sAmp;
    INT16                               sPhase;
    INT16                               sDci;
    INT16                               sDcq;
}TX_IQ_MISMATCH_DCR_STRU_HI6360;


/*****************************************************************************
 结构名    : RX_IQ_STRU_HI6360
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    INT16                               sI;
    INT16                               sQ;
}RX_IQ_STRU_HI6360;


/*****************************************************************************
 结构名    : W_RX_DCOFFSET_STRU_HI6360
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    RX_IQ_STRU_HI6360                          astScNoBlockAt1[W_RX_NOBLOCK_AGC_GAIN_COUNT_HI6360];
    RX_IQ_STRU_HI6360                          astScBlockAt1[W_RX_BLOCK_AGC_GAIN_COUNT_HI6360];
    RX_IQ_STRU_HI6360                          astDcNoBlockAt1[W_RX_NOBLOCK_AGC_GAIN_COUNT_HI6360];
    RX_IQ_STRU_HI6360                          astDcBlockAt1[W_RX_BLOCK_AGC_GAIN_COUNT_HI6360];
    RX_IQ_STRU_HI6360                          astScNoBlockAt2[W_RX_NOBLOCK_AGC_GAIN_COUNT_HI6360];
    RX_IQ_STRU_HI6360                          astScBlockAt2[W_RX_BLOCK_AGC_GAIN_COUNT_HI6360];
    RX_IQ_STRU_HI6360                          astDcNoBlockAt2[W_RX_NOBLOCK_AGC_GAIN_COUNT_HI6360];
    RX_IQ_STRU_HI6360                          astDcBlockAt2[W_RX_BLOCK_AGC_GAIN_COUNT_HI6360];
}W_RX_DCOFFSET_STRU_HI6360;


/*****************************************************************************
 结构名    : W_RX_IP2_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    RX_IQ_STRU_HI6360                          stHChanDivOn;
    RX_IQ_STRU_HI6360                          stHChanDivOff;
    RX_IQ_STRU_HI6360                          stMChanDivOn;
    RX_IQ_STRU_HI6360                          stMChanDivOff;
    RX_IQ_STRU_HI6360                          stLChanDivOn;
    RX_IQ_STRU_HI6360                          stLChanDivOff;
}W_RX_IP2_ANT1_STRU_HI6360;

/*****************************************************************************
 结构名    : W_RX_IP2_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    RX_IQ_STRU_HI6360                        stCalChanIQ[3];    // 0:高信道，1:中信道，2:低信道
}W_RX_IP2_ANT2_STRU_HI6360;

/*****************************************************************************
 结构名    : W_SELF_CAL_RESULT_STRU_HI6360
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usBandId;
    UINT16                              usRsv;
    TX_IQ_MISMATCH_DCR_STRU_HI6360      stTxIqMismatchDcr;
    W_RX_DCOFFSET_STRU_HI6360           stRxDcOffset;
    W_RX_IP2_ANT1_STRU_HI6360           stRxIp2Ant1;
}W_SELF_CAL_RESULT_STRU_HI6360;


/*****************************************************************************
 结构名    : PHY_RF_CAL_W_SELF_CAL_IND_STRU_HI6360
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    UINT16                              usErrCode;                              /* Reference to RF_CAL_SELF_CAL_* */
    UINT16                              usErrBand;                              /*存放校准失败的频段*/
    UINT16                              usSelfCalMask;                          /*存放DSP自校准项*/
    UINT16                              usRfBandCount;                          /*存放DSP频段个数*/
    W_SELF_CAL_RESULT_STRU_HI6360       astSelfCalRlt[SELF_CAL_BAND_ID_MAX_COUNT_HI6360];
}PHY_RF_CAL_W_SELF_CAL_IND_STRU_HI6360;


/*****************************************************************************
 结构名    : W_TRX_FAST_FRAME_STRU_HI6360
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
    UINT16                              usRxAgcModePattern;                     /* Bit -- set 1:Block; set 0:NoBlock */
    UINT16                              usRxCarrModePattern;                    /* Bit -- set 1:Double; set 0:Single */
    UINT32                              aulStepData[W_TRX_MAX_STEP_CNT_HI6360];        /* Bit[30:27]: PD Distune;
                                                                                   Bit[26:23]: PD VGA;
                                                                                   Bit[22:16]: TX PA VBIAS;
                                                                                   Bit[15:14]: Pa Mode;
                                                                                   Bit[13:10]: Rx Agc;
                                                                                   Bit[9:0]:   Tx PWR/ATTEN(0.1dBm)
                                                                                */
}W_TRX_FAST_FRAME_STRU_HI6360;


/*****************************************************************************
 结构名    : PHY_RF_CAL_W_TRX_FAST_CAL_REQ_STRU_HI6360
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usTxStepType;                           /* Reference to W_FAST_TX_STEP_TYPE_ENUM_HI6360 */
    UINT16                              usStepWidth;                            /* Reference to W_FAST_STEP_WIDTH_ENUM_HI6360 */
    UINT16                              usPowerDetect;                          /*1 - report detected volt; 0 - no report*/
    UINT16                              usTxFrameCnt;                           /* [1, W_TRX_MAX_SWEEP_FRAME_CNT_HI6360] */
    UINT16                              usRxFrameCnt;                           /* [1, W_TRX_MAX_SWEEP_FRAME_CNT_HI6360] */
    W_TRX_FAST_FRAME_STRU_HI6360        astSweepFrame[W_TRX_MAX_SWEEP_FRAME_CNT_HI6360];
}PHY_RF_CAL_W_TRX_FAST_CAL_REQ_STRU_HI6360;



/*****************************************************************************
 结构名    : PHY_RF_CAL_W_TRX_FAST_CAL_IND_STRU_HI6360
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    UINT16                              usRssiCnt;                              /* 0:PDM, 1:Power */
    UINT16                              usPowerDetectorCnt;
    INT16                               asReportData[900];                      /*Rssi At1(0.125dBm)+Rssi At2(0.125dBm)+PD测量结果 */
}PHY_RF_CAL_W_TRX_FAST_CAL_IND_STRU_HI6360;



/*****************************************************************************
 结构名    : G_RF_SINGLE_SLOT_CFG_STRU
 协议表格  :
 结构说明  : G TX GSM RF慢速校准接口
*****************************************************************************/
typedef struct
{
    UINT16                                     usTxMode;                               /* 0： burst */
    G_MODE_TYPE_ENUM_UINT16_HI6360             usModType;                              /* 发射调制方式:0表示GMSK调制;1表示8PSK调制*/
    G_SINGLE_SLOT_CTRL_MODE_ENUM_UINT16_HI6360 usCtrlMode;                             /* 发射控制方式：
                                                                                    0：GMSK电压控制,此方式下usTxVpa要配置；
                                                                                    1：功率控制,此方式下usTxPower要配置；
                                                                                    2：8PSK PaVbias电压&DBB Atten&RF Atten控制，
                                                                                    usPAVbias和usRfAtten,sDbbAtten三个参数都要配置；*/
    UINT16                              usRfAtten;
    UINT16                              usTxPower;                              /* 目标发射功率,单位为0.1dBm,GSM和EDGE共用 */
    UINT16                              usTxVpa;                                /* GSM PA发射功率控制电压 */
    INT16                               sDbbAtten;
    UINT16                              usPAVbias;                              /* EDGE PA 控制电压*/
}G_RF_SINGLE_SLOT_CFG_STRU_HI6360;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_TX_PARA_CFG_REQ_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    UINT16                              usMask;                                 /* Reference to MASK_CAL_RF_G_TX_* */
    UINT16                              usAFC;
    UINT16                              usFreqNum;                              /* (Band << 12) | Arfcn */
    UINT16                              usTxEnable;                             /* 发送使能控制:0x5555-使能发送;0xAAAA-停止发送;TSC 0; */
    UINT16                              usDataPattern;                          /* 0：All 0；1：All 1；2：Random */
    UINT16                              usSlotCnt;                              /* 配置时隙个数，范围1~4和8,不需指定具体使用哪些时隙，DSP自动配置1~4时隙发射 */
    G_RF_SINGLE_SLOT_CFG_STRU_HI6360    astSlotCfg[G_TX_PARA_MAX_SLOT_CNT_PER_FRAME_HI6360]; /* 每个时隙的配置情况 */
}PHY_RF_CAL_G_TX_PARA_CFG_REQ_STRU_HI6360;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RX_PARA_CFG_REQ_STRU
 协议表格  :
 结构说明  : G Rx
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv1;
    UINT16                              usMask;                                 /* Reference to MASK_CAL_RF_G_RX_* */
    UINT16                              usFreqNum;                              /* (Band << 12) | Arfcn */
    UINT16                              usRxMode;                               /* 0:burst接收; 1:连续接收;目前只支持burst接收方式 */
    UINT16                              usAGCMode;                              /* Fast AGC,Slow AGC */
    UINT16                              usAGCGain;                              /* AGC档位：自动档，五档；取值为自动档--0，五档--1~5 */
    UINT16                              usRsv2;
}PHY_RF_CAL_G_RX_PARA_CFG_REQ_STRU_HI6360;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RX_RSSI_MEAS_REQ_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv1;
    UINT16                              usMeasNum;
    UINT16                              usRsv2;
}PHY_RF_CAL_G_RX_RSSI_MEAS_REQ_STRU_HI6360;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RX_RSSI_MEAS_IND_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    INT16                               sRSSI;
    UINT16                              usRsv2;
}PHY_RF_CAL_G_RX_RSSI_MEAS_IND_STRU_HI6360;



/*****************************************************************************
 结构名    : G_SELF_CAL_RESULT_STRU
 协议表格  :
 结构说明  : GSM RF自校准接口
             启动G模自校准的Req接口与W模相同
*****************************************************************************/
typedef W_SELF_CAL_RESULT_STRU_HI6360 G_SELF_CAL_RESULT_STRU;

/*****************************************************************************
 结构名    : PHY_RF_CAL_G_SELF_CAL_IND_STRU_HI6360
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef PHY_RF_CAL_W_SELF_CAL_IND_STRU_HI6360 PHY_RF_CAL_G_SELF_CAL_IND_STRU_HI6360;

/*****************************************************************************
 结构名    : G_RF_TX_STEP_STRU
 协议表格  :
 结构说明  : GSM RF快速校准帧结构
*****************************************************************************/
typedef struct
{
    INT16                               sPwrPara;                               /* Tx Power/Tx Agc/Power Atten(0.1dBm)/PCL according to usTxModeMask */
    UINT16                              usExternPara;                           /* PaVbias according to usTxModeMask, if no PaVbias_Mask DSP Use Max PaVbias */
}G_RF_TX_STEP_STRU_HI6360;

/*****************************************************************************
 结构名    : G_RF_TX_SEQUENCE_STRU
 协议表格  :
 结构说明  : GSM RF快速校准接口
             G Tx
*****************************************************************************/
typedef struct
{
    G_RF_TX_STEP_STRU_HI6360                   astStepValue[G_TX_MAX_STEP_CNT_HI6360];        /*当前最大只支持四时隙*/
}G_RF_TX_SEQUENCE_HI6360_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_TX_FAST_CAL_REQ_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usTxPattern;                            /* 低8Bit有效 */
    G_MODE_TYPE_ENUM_UINT16_HI6360      usModType;                              /* 0:GMSK; 1:8PSK */
    UINT16                              usTxModeMask;                           /* Reference to MASK_RF_CAL_G_TX_FAST_ */
    UINT16                              usFrameCnt;
    UINT16                              usRsv;
    UINT16                              ausChannel[G_TX_MAX_SWEEP_FRAME_CNT_HI6360];   /*ausChannel与astTxSequence一一对应*/
    G_RF_TX_SEQUENCE_HI6360_STRU        astTxSequence[G_TX_MAX_SWEEP_FRAME_CNT_HI6360];
}PHY_RF_CAL_G_TX_FAST_CAL_REQ_STRU_HI6360;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RF_MSG_CNF_STRU
 协议表格  :
 结构说明  : G TRX 快慢速校准通用CNF
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    UINT16                              usRecMsgID;                             /* 接收到的消息ID（当前回应的消息ID） */
    UINT16                              usFlag;                                 /* 0:Correct；1:Error */
}PHY_RF_CAL_G_RF_MSG_CNF_STRU_HI6360;


/*****************************************************************************
 结构名    : G_RF_RX_SEQUENCE_STRU
 协议表格  :
 结构说明  : G Rx
*****************************************************************************/
typedef struct
{
    UINT16                              usChannel;
    UINT16                              ausAgcGain[G_RX_MAX_STEP_CNT_HI6360];          /* 每帧必须配7个测量档位 */
}G_RF_RX_SEQUENCE_STRU_HI6360;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RX_FAST_CAL_REQ_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv1;
    UINT16                              usChannelCnt;                           /* 测量帧数 */
    UINT16                              usRsv2;
    G_RF_RX_SEQUENCE_STRU_HI6360        astRxSequence[G_RX_MAX_SWEEP_FRAME_CNT_HI6360];
}PHY_RF_CAL_G_RX_FAST_CAL_REQ_STRU_HI6360;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RX_FAST_CAL_IND_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv1;
    UINT16                              usRssiNum;                              /* 测量个数，最大为G_RX_MAX_RSSI_CNT个,不包括同步帧 */
    UINT16                              usRsv2;
    INT16                               asRssiValue[G_RX_MAX_RSSI_CNT_HI6360];         /* 每帧上报7个点，最大G_RX_MAX_RSSI_CNT个 */
}PHY_RF_CAL_G_RX_FAST_CAL_IND_STRU_HI6360;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RX_DCR_START_REQ_STRU
 协议表格  :
 结构说明  : G Rx DCR
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    UINT16                              usBandMask;                             /* Bit0:GSM850; Bit1:GSM900; Bit2:DCS; Bit3:PCS; */
    UINT16                              usFramesCnt;                            /* 统计帧数 */
}PHY_RF_CAL_G_RX_DCR_START_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RX_DCR_RPT_IND_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv1;
    UINT16                              usFreq;                                 /* 测量的频段号和频点号（band《12 | channel）*/
    UINT16                              usFreqIndex;                            /* 频点索引号 */
    UINT16                              usGain;                                 /* 测量使用的档位，范围0、1、2、3 */
    UINT16                              usRsv2;
    INT16                               sIDCOffset;
    INT16                               sQDCOffset;
}PHY_RF_CAL_G_RX_DCR_RPT_IND_STRU_HI6360;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RX_DCR_STOP_CNF_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/

typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;                                  /* 保留位 */
}PHY_RF_CAL_G_RX_DCR_STOP_CNF_STRU;



/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RX_IP2_CAL_REQ_STRU
 协议表格  :
 结构说明  : G Rx IP2
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    UINT16                              usFreqNum;                              /* (Band<<12)|Channel */
    UINT16                              usAGCGain;                              /* 校准时要求的AGC状态 */
}PHY_RF_CAL_G_RX_IP2_CAL_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RF_CAL_G_RX_IP2_CAL_IND_STRU
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    INT16                               sIData;                                 /* I路测量值 */
    INT16                               sQData;                                 /* Q路测量值 */
}PHY_RF_CAL_G_RX_IP2_CAL_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_GAUGE_REQ_STRU_HI6360
 协议表格  :
 结构说明  : 用于32K测量任务的启动和停止
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    UINT32                              ulAction;                               /* 1-启动32K测量;0-停止32K测量 */
}WPHY_TOOL_GAUGE_REQ_STRU_HI6360;

/*****************************************************************************
 结构名    : WPHY_TOOL_GAUGE_CNF_STRU_HI6360
 协议表格  :
 结构说明  : 用于32K测量任务的启动和停止的原语回复
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    UINT32                              ulAction;                               /* 1-启动32K测量;0-停止32K测量 */
}WPHY_TOOL_GAUGE_CNF_STRU_HI6360;

/*****************************************************************************
 结构名    : WPHY_TOOL_GAUGE_IND_STRU_HI6360
 协议表格  :
 结构说明  : 用于32K测量结果的上报
*****************************************************************************/
typedef struct
{
    PHY_TOOL_MSG_ID_ENUM_UINT16_HI6360  usMsgID;                                /* _H2ASN_Skip */ /* 原语类型 */
    UINT16                              usRsv;
    UINT32                              aulData[W_GAUGE_RESULT_SIZE_HI6360];
}WPHY_TOOL_GAUGE_IND_STRU_HI6360;

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of PhyRfCalInterface_hi6360.h */

