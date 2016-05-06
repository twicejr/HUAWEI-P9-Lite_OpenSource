

#ifndef __ATPHYINTERFACE_H__
#define __ATPHYINTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define W_AFC_INIT_VALUE                (0x959)           /* W_AFC状态初值 */

#define WDSP_CTRL_TX_OFF                 2       /*表示DSP强制上行RF关闭*/
#define WDSP_CTRL_TX_ON                  3       /*表示DSP强制上行RF打开*/

#define WDSP_CTRL_TX_ONE_TONE            8       /* 表示打开同相单音信号 */
#define WDSP_CTRL_TX_TWO_TONE            9       /* 表示打开反相单音信号 */

#define GDSP_CTRL_TX_OFF                0xAAAA   /*表示DSP强制上行RF关闭*/
#define GDSP_CTRL_TX_ON                 0x5555   /*表示DSP强制上行RF打开*/

#define WDSP_MAX_TX_AGC                 2047
#define GDSP_MAX_TX_VPA                 1023

#define BBP_PA_HIGH_MODE                1       /*PA高增益模式*/
#define BBP_PA_MID_MODE                 2       /*PA中增益模式*/
#define BBP_PA_LOW_MODE                 3       /*PA低增益模式*/
#define BBP_PA_AUTO_MODE                0       /*PA自动增益模式*/

#define DSP_CTRL_RX_OFF                2       /*CPU控制关闭射频芯片。*/
#define DSP_CTRL_RX_ANT1_ON            3       /*CPU控制打开射频芯片,天线1。*/
#define DSP_CTRL_RX_ALL_ANT_ON         7       /*CPU控制打开射频芯片,天线1和2 */

#define DSP_LNA_HIGH_GAIN_MODE          (0x2)     /* DSP固定LNA为高增益模式 */
#define DSP_LNA_LOW_GAIN_MODE           (0x1)     /* DSP固定LNA为低增益模式 */
#define DSP_LNA_NO_CTRL_GAIN_MODE       (0x0)     /* WBBP控制LNA模式,自动模式 */

#define AT_GDSP_AGC_GAIN1_75DB          (0)      /*GDSP AGC增益,0档*/
#define AT_GDSP_AGC_GAIN2_63DB          (1)      /*GDSP AGC增益,1档*/
#define AT_GDSP_AGC_GAIN3_43DB          (2)      /*GDSP AGC增益,2档*/
#define AT_GDSP_AGC_GAIN4_23DB          (3)      /*GDSP AGC增益,3档*/


#define AT_GDSP_RX_MODE_BURST           (0)      /*接收*/
#define AT_GDSP_RX_MODE_CONTINOUS_BURST (1)      /*连续接收*/
#define AT_GDSP_RX_MODE_STOP            (2)      /*停止*/


#define AT_GDSP_RX_SLOW_AGC_MODE        (0)      /*Slow AGC*/
#define AT_GDSP_RX_FAST_AGC_MODE        (1)      /*fast AGC*/

#define AT_DSP_RF_AGC_STATE_ERROR       (-1)     /*取得测量值时的增益状态，-1表示出错 */

#define AT_DSP_RSSI_MEASURE_NUM         (1)      /*RSSI的测量次数*/
#define AT_DSP_RSSI_MEASURE_INTERVAL    (0)      /*RSSI的测量间隔时间，单位ms */
#define AT_DSP_RSSI_VALUE_UINT          (0.125)  /*RSSI测量值，单位0.125dBm*/
#define AT_DSP_RSSI_VALUE_MUL_THOUSAND  (125)    /*RSSI测量值,单位0.125dBm*1000*/

/*tyg*/
#define AT_DPS_NOISERSSI_MAX_NUM        (32)

#define AT_RX_PRI_ON                    (0)      /*测量主集*/
#define AT_RX_DIV_ON                    (1)      /*测量分集*/
#define AT_RXON_OPEN                    (0)      /*最近一次执行的是打开接收机RXON=1操作*/
#define AT_TXON_OPEN                    (1)      /*最近一次执行的是打开发射机TXON=1操作*/

#define AT_BIT0                            0x00000001L
#define AT_BIT1                            0x00000002L
#define AT_BIT2                            0x00000004L
#define AT_BIT3                            0x00000008L
#define AT_BIT4                            0x00000010L
#define AT_BIT5                            0x00000020L
#define AT_BIT6                            0x00000040L
#define AT_BIT7                            0x00000080L
#define AT_BIT8                            0x00000100L
#define AT_BIT9                            0x00000200L
#define AT_BIT10                           0x00000400L
#define AT_BIT11                           0x00000800L
#define AT_BIT12                           0x00001000L
#define AT_BIT13                           0x00002000L
#define AT_BIT14                           0x00004000L
#define AT_BIT15                           0x00008000L

/* W_RF_CFG_REQ命令的掩码 */
#define W_RF_MASK_AFC                   AT_BIT0
#define W_RF_MASK_TX_ARFCN              AT_BIT1
#define W_RF_MASK_TX_TXONOFF            AT_BIT2
#define W_RF_MASK_TX_PAMODE             AT_BIT3
#define W_RF_MASK_TX_AGC                AT_BIT4
#define W_RF_MASK_TX_POWER              AT_BIT5
#define W_RF_MASK_RX_RXONOFF            AT_BIT6
#define W_RF_MASK_RX_ARFCN              AT_BIT7
#define W_RF_MASK_RX_ANTSEL             AT_BIT8
#define W_RF_MASK_RX_LNAMODE            AT_BIT9
#define W_RF_MASK_RX_PGC                AT_BIT10
#define W_RF_MASK_TX_POWDET             AT_BIT11

/* G_RF_RX_CFG_REQ_STRU结构中uhwMask的比特位定义 */
#define G_RF_MASK_RX_ARFCN              AT_BIT0            /* 下发频点 */
#define G_RF_MASK_RX_MODE               AT_BIT1            /* 下发接收模式 */
#define G_RF_MASK_RX_AGCMODE            AT_BIT2            /* 下发测量模式 */
#define G_RF_MASK_RX_AGCGAIN            AT_BIT3            /* 下发AGC档位 */

/* G_RF_TX_CFG_REQ_STRU结构中uhwMask的比特位定义 */
/* 注意: 1)在GMSK调制方式下，目标发射功率可通过G_RF_MASK_TX_GSMK_PA_VOLT
           或G_RF_MASK_TX_POWER下发,但不能同时下发;
         2)在8PSK调制方式下:目标功率值只能通过G_RF_MASK_TX_POWER下发
         3)各比特位可以同时下发，但不能相互冲突 */
#define G_RF_MASK_TX_AFC                AT_BIT0            /* 下发单板频率控制值 */
#define G_RF_MASK_TX_ARFCN              AT_BIT1            /* 下发发射频点 */
#define G_RF_MASK_TX_TXEN               AT_BIT2            /* 下发发射控制位 */
#define G_RF_MASK_TX_TXMODE             AT_BIT3            /* 下发发送模式 */
#define G_RF_MASK_TX_MOD_TYPE           AT_BIT4            /* 下发调制模式 */
#define G_RF_MASK_TX_GSMK_PA_VOLT       AT_BIT5            /* 下发GMSK调制时 PA目标控制电压 */
#define G_RF_MASK_TX_POWER              AT_BIT6            /* 下发目标发射控制值,GMSK和8PSK共用 */
#define G_RF_MASK_TX_8PSK_PA_VBIAS      AT_BIT7            /* 下发8PSK调制时PA偏置电压 */
#define G_RF_MASK_TX_TXOLC              AT_BIT8            /* 下发TXOLC寄存器值 */
#define G_RF_MASK_TX_DATA_PATTERN       AT_BIT9

/*调制方式*/
#define G_MOD_TYPE_GMSK                 0       /* GMSK调制方式 */
#define G_MOD_TYPE_8PSK                 1       /* 8PSK调制方式 */

/* noise tool 最大上报的结果个数 */
#define PHY_NOISE_MAX_RESULT_NUMB       32

/* 如果工具下发的上行功率为0xff则为不打开上行 */
#define PHY_NOIST_TOOL_CLOSE_TX         0xff

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* 打开天线的模式 */
enum AT_ANT_MODE_ENUM
{
    ANT_ONE  = 1,/*只打开主集天线*/
    ANT_TWO  = 2,/*同时打开主集和分集天线*/
    ANT_BUTT
};
typedef VOS_UINT8 AT_ANT_MODE_UINT8;

/* WDSP 格式频段定义*/
enum AT_W_BAND_ENUM
{
    W_FREQ_BAND1 = 1,
    W_FREQ_BAND2,
    W_FREQ_BAND3,
    W_FREQ_BAND4,
    W_FREQ_BAND5,
    W_FREQ_BAND6,
    W_FREQ_BAND7,
    W_FREQ_BAND8,
    W_FREQ_BAND9,
    W_FREQ_BAND10,                                                              /*  BAND10 不支持 */
    W_FREQ_BAND11,
    W_FREQ_BAND_BUTT
};
typedef VOS_UINT16 AT_WDSP_BAND_ENUM_UINT16;

/* GDSP 频段定义 */
enum AT_GDSP_BAND_ENUM
{
    G_FREQ_BAND_GSM850 = 0,
    G_FREQ_BAND_GSM900,
    G_FREQ_BAND_DCS1800,
    G_FREQ_BAND_PCS1900,
    G_FREQ_BAND_BUTT
};
typedef VOS_UINT16 AT_GDSP_BAND_ENUM_UINT16;

/* AT HPA设置结果 0:success, 1:fail */
enum AT_HPA_CFG_RLST_ENUM
{
    AT_HPA_RSLT_SUCC = 0,
    AT_HPA_RSLT_FAIL,
    AT_HPA_RSLT_BUTT
};
typedef VOS_UINT16 AT_HPA_CFG_RLST_ENUM_UINT16;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/
/*#define ID_HPA_AT_TRANS_MSG_ID          0x8001            透明消息ID */

        /* W慢速校准原语ID*/
#define ID_AT_HPA_RF_CFG_REQ            0x2621
#define ID_HPA_AT_RF_CFG_CNF            0x62E0

#define ID_AT_HPA_RF_RX_RSSI_REQ        0x2622
#define ID_HPA_AT_RF_RX_RSSI_IND        0x62E1

        /* W PLL锁定状态查询原语ID*/
#define ID_AT_WPHY_RF_PLL_STATUS_REQ    0x2623
#define ID_AT_WPHY_RF_PLL_STATUS_CNF    0x62E2

        /* G慢速校准原语ID*/
#define ID_AT_GHPA_RF_RX_CFG_REQ        0x2415          /*RX慢速校准参数配置*/
#define ID_AT_GHPA_RF_TX_CFG_REQ        0x2418          /*TX慢速校准参数配置*/
#define ID_GHPA_AT_RF_MSG_CNF           0x4212          /* 通用回复消息原语 */

#define ID_AT_GHPA_RF_RX_RSSI_REQ       0x2416          /*RX慢速校准测量请求*/
#define ID_GHPA_AT_RF_RX_RSSI_IND       0x4210          /*RX慢速校准测量结果上报*/

        /* G PLL锁定状态查询原语ID*/
#define ID_AT_GPHY_RF_PLL_STATUS_REQ    0x2419
#define ID_AT_GPHY_RF_PLL_STATUS_CNF    0x4219

        /* PD检测状态查询原语ID*/
#define ID_AT_WPHY_POWER_DET_REQ        0x2624
#define ID_AT_WPHY_POWER_DET_CNF        0x62e3

/* noise tool 和wphy的接口 */
#define ID_AT_HPA_RF_NOISE_CFG_REQ      0x2625
#define ID_HPA_AT_RF_NOISE_RSSI_IND     0x62e4
/**/
/* 回复给NOISE TOOL的消息原语 原语ID */
#define ID_AT_GHPA_RF_NOISE_CFG_REQ     0x241A
#define ID_GHPA_AT_RF_NOISE_RSSI_IND    0x421A

#define ID_AT_HPA_MIPI_WR_REQ           0x2490
#define ID_HPA_AT_MIPI_WR_CNF           0x4290
#define ID_AT_HPA_MIPI_RD_REQ           0x2491
#define ID_HPA_AT_MIPI_RD_CNF           0x4291

#define ID_AT_HPA_SSI_WR_REQ            0x2492
#define ID_HPA_AT_SSI_WR_CNF            0x4292
#define ID_AT_HPA_SSI_RD_REQ            0x2493
#define ID_HPA_AT_SSI_RD_CNF            0x4293

#define ID_AT_HPA_PDM_CTRL_REQ          0x2494
#define ID_HPA_AT_PDM_CTRL_CNF          0x4294

        /* CDMA慢速校准原语ID*/
#define ID_AT_CHPA_RF_CFG_REQ            0x6300
#define ID_CHPA_AT_RF_CFG_CNF            0x6301

#define ID_AT_CHPA_RF_RX_RSSI_REQ        0x6302
#define ID_CHPA_AT_RF_RX_RSSI_IND        0x6303

/*****************************************************************************
 结构名    : C_RF_CFG_PARA_STRU
 结构说明  : RF配置参数结构
 1.日    期   : 2011年11月16日
   作    者   : f62575
   修改内容   : 补充结构注释
*****************************************************************************/
typedef struct
{
    /* Tx Cfg */
    VOS_UINT16                          usMask;                                 /* 按位标识配置类型 */
    VOS_UINT16                          usTxAFCInit;                            /* AFC */
    VOS_UINT16                          usTxBand;                               /* 1,2,3...,协议中的band编号,注意不是BandId */
    VOS_UINT16                          usTxFreqNum;                            /* Arfcn */
    VOS_UINT16                          usTxEnable;                             /* TX通道使能控制 */
    VOS_UINT16                          usTxPAMode;                             /* PA模式控制 */
    VOS_INT16                           sTxPower;                               /* 0.1dBm */

    /* Rx Cfg */
    VOS_UINT16                          usRxEnable;                             /* RX通道使能控制 */
    VOS_UINT16                          usRxBand;                               /* 1,2,3...,协议中的band编号*/
    VOS_UINT16                          usRxFreqNum;                            /* Arfcn*/
    VOS_UINT16                          usRxAntSel;                             /* Ant1/Ant2*/
    VOS_UINT16                          usRsv;             /* 保留位 */

}C_RF_CFG_PARA_STRU;

/* AT_HPA 参数配置原语接口 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /* 保留位 */
    C_RF_CFG_PARA_STRU                  stRfCfgPara;            /* RF配置参数结构 */
}AT_CHPA_RF_CFG_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /* 保留位 */
    VOS_UINT16                          usMeasNum;             /* RSSI的测量次数 */
    VOS_UINT16                          usInterval;            /* RSSI的测量间隔时间，单位ms */
}AT_CHPA_RF_RX_RSSI_REQ_STRU;



/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/* W的RF配置结构 */
/* RF配置参数结构 */
/*****************************************************************************
 结构名    : W_RF_CFG_PARA_STRU
 结构说明  : RF配置参数结构
 1.日    期   : 2011年11月16日
   作    者   : f62575
   修改内容   : 补充结构注释
 2.日    期   : 2011年11月16日
   作    者   : f62575
   修改内容   : 适配物理层接口变更
                增加sRrcWidth, sDbbAtten, usRxCarrMode, usPaVbias
                移动sTxPower,
                删除sRxPGC
*****************************************************************************/
typedef struct
{
    /* TX RX均使用 */
    VOS_INT16                           sRrcWidth;                              /* 该变量暂时不用,双载波模式时,该值为RRC带宽,范围[-5,5]MHz */

    /* Tx Cfg */
    VOS_UINT16                          usMask;                                 /* 按位标识配置类型 */
    VOS_UINT16                          usTxAFCInit;                            /* AFC */
    VOS_UINT16                          usTxBand;                               /* 1,2,3...,协议中的band编号,注意不是BandId */
    VOS_UINT16                          usTxFreqNum;                            /* Arfcn */
    VOS_UINT16                          usTxEnable;                             /* TX通道使能控制 */
    VOS_UINT16                          usTxPAMode;                             /* PA模式控制 */
    VOS_INT16                           sTxPower;                               /* 0.1dBm */
    VOS_INT16                           sDbbAtten;                              /* DBB对信号衰减的控制字 映射到usTxAGC???，但含义不一致，找深圳确认 */
    VOS_UINT16                          usRfAtten;                              /* RF对信号衰减的控制字 */
    VOS_UINT16                          usTxAGC;                                /* 发射AGC控制 */
    VOS_UINT16                          usPaVbias;                              /* W PA Vbias 的控制字 */

    /* Rx Cfg */
    VOS_UINT16                          usRxEnable;                             /* RX通道使能控制 */
    VOS_UINT16                          usRxBand;                               /* 1,2,3...,协议中的band编号*/
    VOS_UINT16                          usRxFreqNum;                            /* Arfcn*/
    VOS_UINT16                          usRxAntSel;                             /* Ant1/Ant2*/
    VOS_UINT16                          usRxLNAGainMode;                        /* LNA模式控制 */


    VOS_UINT16                          usRxCarrMode;                           /* 0:单载波;1:双载波 */
}W_RF_CFG_PARA_STRU;


/* AT_HPA 参数配置原语接口 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /* 保留位 */
    W_RF_CFG_PARA_STRU                  stRfCfgPara;            /* RF配置参数结构 */
}AT_HPA_RF_CFG_REQ_STRU;

/* G的RF配置结构 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /* 保留位 */
    VOS_UINT16                          usMask;        /* Reference MASK_CAL_RF_G_RX_* section */
    VOS_UINT16                          usFreqNum;     /* (Band << 12) | Arfcn */
    VOS_UINT16                          usRxMode;      /* 0:burst接收; 1:连续接收;, */
    VOS_UINT16                          usAGCMode;     /* Fast AGC,Slow AGC */
    VOS_UINT16                          usAgcGain;     /* AGC档位，共四档,取值为0-3*/
    VOS_UINT16                          usRsv2;
}AT_GHPA_RF_RX_CFG_REQ_STRU;

/*****************************************************************************
 枚举名    : AT_GHPA_RF_CTRLMODE_TYPE_ENUM
 结构说明  : 发射控制方式：
             0：GMSK电压控制,此方式下usTxVpa要配置；
             1：功率控制,此方式下usTxPower要配置；
             2：8PSK PaVbias电压&DBB Atten&RF Atten控制，usPAVbias和usRfAtten,sDbbAtten三个参数都要配置；
1.日    期   : 2011年11月17日
  作    者   : f62575
  修改内容   : 新生成
*****************************************************************************/
enum AT_GHPA_RF_CTRLMODE_TYPE_ENUM
{
    AT_GHPA_RF_CTRLMODE_TYPE_GMSK,
    AT_GHPA_RF_CTRLMODE_TYPE_TXPOWER,
    AT_GHPA_RF_CTRLMODE_TYPE_8PSK,
    AT_GHPA_RF_CTRLMODE_TYPE_BUTT
};
typedef VOS_UINT8 AT_GHPA_RF_CTRLMODE_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : AT_GHPA_RF_TX_CFG_REQ_STRU
 结构说明  :
 1.日    期   : 2011年11月16日
   作    者   : f62575
   修改内容   : 补充注释
 2.日    期   : 2011年11月16日
   作    者   : f62575
   修改内容   : 适配物理层接口变更
                增加enCtrlMode, uhwRfAtten
                移动usModType,
                删除usTxolc
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* Msg ID */
    VOS_UINT16                          usRsv;                                  /* 保留位 */
    VOS_UINT16                          usMask;                                 /* Reference MASK_CAL_RF_G_TX_* section*/
    VOS_UINT16                          usAFC;                                  /* AFC */
    VOS_UINT16                          usModType;                              /* 发射调制方式:0表示GMSK调制;1表示8PSK调制方式 */
    VOS_UINT16                          usFreqNum;                              /* (Band << 12) | Arfcn */
    VOS_UINT16                          usTxEnable;                             /* 发送使能控制:0x5555-使能发送;0xAAAA-停止发送;TSC 0; TxData: 随机数 */
    VOS_UINT16                          usTxMode;                               /* 0:burst发送; 1:连续发送 */
    AT_GHPA_RF_CTRLMODE_TYPE_ENUM_UINT8 enCtrlMode;                             /* 发射控制方式：
                                                                                    0：GMSK电压控制,此方式下usTxVpa要配置；
                                                                                    1：功率控制,此方式下usTxPower要配置；
                                                                                    2：8PSK PaVbias电压&DBB Atten&RF Atten控制，
                                                                                    usPAVbias和usRfAtten,sDbbAtten三个参数都要配置；*/
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          uhwRfAtten;
    VOS_UINT16                          usTxPower;                              /* 目标发射功率,单位为0.1dBm,GSM和EDGE共用 */
    VOS_UINT16                          usTxVpa;                                /* GSM PA发射功率控制电压,取值范围: */
    VOS_INT16                           shwDbbAtten;
    VOS_UINT16                          usPAVbias;                              /* EDGE PA Vbais 电压 */
}AT_GHPA_RF_TX_CFG_REQ_STRU;


/*Response Head Struct    W/G通用 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usTransPrimID;     /* 0x8001 */
    VOS_UINT16                          usRsv1;            /* 保留位 */
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /* 保留位 */
}HPA_AT_HEADER_STRU;

typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT16                          usCfgMsgID;        /* 接收到的消息ID */
    VOS_UINT16                          usErrFlg;          /* 0:success, 1:fail */
}HPA_AT_RF_CFG_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /* 保留位 */
    VOS_UINT16                          usMeasNum;             /* RSSI的测量次数 */
    VOS_UINT16                          usInterval;            /* RSSI的测量间隔时间，单位ms */
}AT_HPA_RF_RX_RSSI_REQ_STRU;

/* 接收到测量质量上报请求后，上报前一次接收的RSSI测量结果  G/W通用 */
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_INT16                           sRSSI;            /* RSSI测量值 [-2048,+2047]，单位0.125dBm*/
    VOS_INT16                           sAGCGain;         /* 取得测量值时的增益状态，-1表示出错 */
}HPA_AT_RF_RX_RSSI_IND_STRU;

/*****************************************************************************
 结构名    : PHY_NOISE_RESULT_STRU
 结构说明  : PHY向AT上报的单个结果的结构
 1.日    期   : 2014年12月29日
   作    者   : tianyige
   修改内容   : Noise tool PHY上报结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDLFreq;                               /*PHY上报当前测量频点*/
    VOS_INT16                           sDLPriRssi;                             /*PHY上报对应主集RSSI*/
    VOS_INT16                           sDLDivRssi;                             /*PHY上报对应分集RSSI*/
    VOS_UINT16                          usRsv;
}PHY_NOISE_RESULT_STRU;

/*****************************************************************************
 结构名    : HPA_NOISE_RSSI_IND_STRU
 结构说明  : WPHY或GPHY向AT上报的消息结构
 1.日    期   : 2014年12月29日
   作    者   : tianyige
   修改内容   : Noise tool PHY上报结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDLRssiNum;                            /*PHY上报测量RSSI个数*/
    VOS_UINT16                          usMeaStatus;                            /*PHY上报测量状态，0表示成功，1表示参数错误，2表示超时 */
    PHY_NOISE_RESULT_STRU               astDlRssiResult[AT_DPS_NOISERSSI_MAX_NUM];
}HPA_NOISE_RSSI_IND_STRU;


/*****************************************************************************
 结构名    : PHY_AT_RF_NOISE_RSSI_IND_STRU
 结构说明  : WPHY或GPHY向AT上报的消息结构
 1.日    期   : 2014年12月29日
   作    者   : tianyige
   修改内容   : Noise tool PHY上报结构
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;                            /* 标准头 */
    HPA_NOISE_RSSI_IND_STRU             stRssiInd;                              /* 结果 */
}PHY_AT_RF_NOISE_RSSI_IND_STRU;

/*****************************************************************************
 结构名    : AT_PHY_RF_PLL_STATUS_REQ_STRU
 结构说明  : AT向WPHY或GPHY查询PLL状态的消息结构
 1.日    期   : 2013年11月29日
   作    者   : L00256032
   修改内容   : Added for PLL status query
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv1;            /* 保留位 */
    VOS_UINT16                          usDspBand;         /* DSP格式的频段值 */
    VOS_UINT16                          usRsv2;            /* 保留位 */
}AT_PHY_RF_PLL_STATUS_REQ_STRU;

/*****************************************************************************
 结构名    : AT_PHY_RF_PLL_STATUS_REQ_STRU
 结构说明  : WPHY或GPHY向AT返回PLL状态的消息结构
 1.日    期   : 2013年11月29日
   作    者   : L00256032
   修改内容   : Added for PLL status query
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT16                          usTxStatus;        /* 0:PLL失锁, 1:PLL锁定 */
    VOS_UINT16                          usRxStatus;        /* 0:PLL失锁, 1:PLL锁定 */
}PHY_AT_RF_PLL_STATUS_CNF_STRU;


/*****************************************************************************
 结构名    : AT_PHY_POWER_DET_REQ_STRU
 结构说明  : AT向WPHY查询功率检测的消息结构
 1.日    期   : 2014年05月06日
   作    者   : c00242732
   修改内容   : Added for Power_Detect query
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /* 保留位 */
}AT_PHY_POWER_DET_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_AT_POWER_DET_CNF_STRU
 结构说明  : WPHY向AT返回功率检测结果的消息结构
 1.日    期   : 2014年05月06日
   作    者   : c00242732
   修改内容   : Added for Power_Detect query
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_INT16                           sPowerDet;         /* 功率检测结果，0.1dBm精度 */
    VOS_UINT16                          usRsv;             /* 保留位 */
}PHY_AT_POWER_DET_CNF_STRU;


/*****************************************************************************
 结构名    : AT_HPA_RF_NOISE_CFG_REQ_STRU
 结构说明  : AT向GPHY下发noise tool请求
 1.日    期   : 2014年12月19日
   作    者   : tianyige
   修改内容   : Added for noise tool
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* Msg ID */
    VOS_UINT16                          usMode;                                 /* UE 模式 */
    VOS_UINT16                          usBand;                                 /* band信息 */
    VOS_UINT16                          usDlStartFreq;                          /* 下行开始频点 */
    VOS_UINT16                          usDlEndFreq;                            /* 下行结束频点 */
    VOS_UINT16                          usFreqStep;                             /* 步长 */
    VOS_INT16                           sTxPwr;                                 /* 发射功率 */
    VOS_UINT16                          usRsv;                                  /* 保留位 */
}AT_HPA_RF_NOISE_CFG_REQ_STRU;

/*****************************************************************************
 结构名    : AT_HPA_MIPI_WR_REQ_STRU
 结构说明  : 设置MIPI 寄存器请求结构体

 1.日    期   : 2015年9月10日
    作    者   : l00227485
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;
    VOS_UINT16                          usSlaveAddr;
    VOS_UINT16                          usRegAddr;
    VOS_UINT16                          usRegData;
    VOS_UINT16                          usMipiChannel;
    VOS_UINT16                          usRsv;
}AT_HPA_MIPI_WR_REQ_STRU;

/*****************************************************************************
 结构名    : HPA_AT_MIPI_WR_CNF_STRU
 结构说明  : AT与AT AGENT 设置MIPI 寄存器请求结构体
1.日    期   : 2015年9月10日
   作    者   :l00227485
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT32                          usErrFlg;          /* 0:success, 1:fail */
}HPA_AT_MIPI_WR_CNF_STRU;

/*****************************************************************************
 结构名    : AT_HPA_MIPI_RD_REQ_STRU
 结构说明  :查询MIPI 寄存器请求结构体
 1.日    期   : 2015年9月10日
    作    者   : l00227485
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* Msg ID */
    VOS_UINT16                          uhwSlaveAddr;                           /* 接收端地址 */
    VOS_UINT16                          uhwReg;                                 /* 寄存器个数 */
    VOS_UINT16                          uhwChannel;                             /* 开始的寄存器 */
}AT_HPA_MIPI_RD_REQ_STRU;

/*****************************************************************************
 结构名    : HPA_AT_MIPI_RD_CNF_STRU
 结构说明  : AT与AT AGENT 设置MIPI 寄存器请求结构体
1.日    期   : 2015年9月10日
   作    者   :l00227485
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT32                          ulValue;
    VOS_UINT32                          ulResult;
}HPA_AT_MIPI_RD_CNF_STRU;

/*****************************************************************************
 结构名    : AT_HPA_SSI_WR_REQ_STRU
 结构说明  : AT向PHY下发SSI请求
 1.日    期   : 2015年09月19日
   作    者   : x00316382
   修改内容   : Added for ssi tool
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;
    VOS_UINT16                          usRficSsi;                              /* Mipi */
    VOS_UINT16                          usRegAddr;                              /* 开始的寄存器 */
    VOS_UINT16                          usData;                                 /* 数据 */
}AT_HPA_SSI_WR_REQ_STRU;

/*****************************************************************************
 结构名    : HPA_AT_SSI_WR_CNF_STRU
 结构说明  : AT与AT AGENT 设置MIPI 寄存器请求结构体
1.日    期   : 2015年9月10日
   作    者   :l00227485
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT32                          usErrFlg;                               /* 0:success, 1:fail */
}HPA_AT_SSI_WR_CNF_STRU;

/*****************************************************************************
 结构名    : AT_HPA_SSI_RD_REQ_STRU
 结构说明  :
 1.日    期   : 2015年09月19日
   作    者   : x00316382
   修改内容   : Added for tool
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* Msg ID */
    VOS_UINT16                          usChannelNo;                            /* 接收端地址 */
    VOS_UINT32                          uwRficReg;
}AT_HPA_SSI_RD_REQ_STRU;

/*****************************************************************************
 结构名    : HPA_AT_SSI_RD_CNF_STRU
 结构说明  : AT与AT AGENT 设置MIPI 寄存器请求结构体
1.日    期   : 2015年9月10日
   作    者   :l00227485
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT32                          ulValue;
    VOS_UINT32                          ulResult;
}HPA_AT_SSI_RD_CNF_STRU;

/* 接收到测量质量上报请求后，上报前一次接收的RSSI测量结果  G/W通用 */
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_INT16                           sRSSI;            /* RSSI测量值 [-2048,+2047]，单位0.125dBm*/
    VOS_INT16                           sAGCGain;         /* 取得测量值时的增益状态，-1表示出错 */
}CHPA_AT_RF_RX_RSSI_IND_STRU;

typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT16                          usCfgMsgID;        /* 接收到的消息ID */
    VOS_UINT16                          usErrFlg;          /* 0:success, 1:fail */
}CHPA_AT_RF_CFG_CNF_STRU;

/*****************************************************************************
 结构名    : AT_HPA_PDM_CTRL_REQ_STRU
 结构说明  :
 1.日    期   : 2015年10月20日
   作    者   : x00316382
   修改内容   : Added for tool
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* Msg ID */
    VOS_UINT16                          usRsv;                                  /* 保留位 */
    VOS_UINT16                          usPdmRegValue;
    VOS_UINT16                          usPaVbias;
    VOS_UINT16                          usPaVbias2;
    VOS_UINT16                          usPaVbias3;
}AT_HPA_PDM_CTRL_REQ_STRU;

/*****************************************************************************
 结构名    : HPA_AT_PDM_CTRL_CNF_STRU
 结构说明  : AT与AT AGENT 设置PDM 寄存器请求结构体
1.日    期   : 2015年10月20日
  作    者   : x00316382
  修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT32                          ulResult;
}HPA_AT_PDM_CTRL_CNF_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of AtPhyInterface.h */
