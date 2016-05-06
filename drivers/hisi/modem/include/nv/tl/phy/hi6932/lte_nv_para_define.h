/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : lte_nv_para_define.h
  版 本 号   : 初稿
  作    者   : tuzhiguo(52067)
  生成日期   : 2010年12月28日
  最近修改   :
  功能描述   : NV项定义,定义和算法配置有关的NV项
  函数列表   :
  修改历史   :
  1.日    期   : 2010年12月28日
    作    者   : tuzhiguo(52067)
    修改内容   : 创建文件
--------------------------------------------------------------------------------
  2.日    期 : 2011年6月28日
    作    者 : shijiahong
    修改内容 : DTS2011062404331 加入6360AGC的宏定义
-------------------------------------------------------------------------------
 3.日    期 : 2011年9月20日
    作    者 : zengshangyou
    修改内容 : DTS2011090203399 加入CT BT NV
-------------------------------------------------------------------------------
 4.日    期 : 2011年10月8日
    作    者 : zengshangyou
    修改内容 : DTS2011092600031 CT BT数据结构常开 AGC_MAX_GAIN_LEVEL修改为16
--------------------------------------------------------------------------------
 5. 日    期   : 2011年10月14日
    作    者   : liuxu
    修改内容   : <DTS2011101401498> NV项增加UE能力等接口
 --------------------------------------------------------------------------------
6.日  期   : 2011年 11 月 14日
   作  者   : shijiahong
   修改内容 : DTS 将前端相关配置时间T1~T10移入NV  PN:DTS2011111401524

7.日    期   : 2011年11月26日
  作    者   : tuzhiguo
  修改内容   : DTS2011111800531 合入Pliot版本，增加CQI/SYNC项
--------------------------------------------------------------------------------
8.日  期   : 2011年 12 月 06日
   作  者   : shijiahong
   修改内容 : DSP相关的所有配置时间移入NV,PN:DTS2011120604351
--------------------------------------------------------------------------------
9.日    期   : 2011年12月19日
  作    者   : tuzhiguo
  修改内容   : DTS2011121502820 ETU信道的trms档位有小概率(20%)估计不准，
          估成EVA信道，从而影响性能，算法对此修改一下trms的档位判断
--------------------------------------------------------------------------------
 10.日    期   : 2012年04月17日
   作    者   : Shen Guang
   修改内容   : [DTS2012022700423]FDD-TDD互操作
------------------------------------------------------------------------------
 11.日    期   : 2012年5月26日
    作    者   : xueqiuyan
    修改内容   : [DTS2012032702692]GCF测试杂散模板指标超标，添加A-MPR特性

------------------------------------------------------------------------------
 13.日    期   : 2015年02月26日
    作    者   : lijiuyong
    修改内容   :同步多模TAS
******************************************************************************/


#ifndef __LTE_NV_PARA_DEFINE_HI6950_H__
#define __LTE_NV_PARA_DEFINE_HI6950_H__
#include "product_config.h"
#include "TLPhyInterface.h"
#include "lt_nv_common_interface.h"
#include "LRrcLPhyInterface.h"
#include "PhyNvDefine.h"


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
#define    LPHY_TX_DUAL_ANTENNA         2
#define    INTERP_COEF_ROW              9
#define    INTERP_COEF_COLUMN           3
#define    PB_TIME_DOMAIN_INTP_NUM     10
#define    PDU_TIME_DOMAIN_INTP_NUM    14
#define    IIR_ALPHA_NUMBER             6
#define    CHE_CPE_ROW                  8
#define    CHE_CPE_COLOUM               8
#define    LPHY_MAX_BANDWIDTH_NUM       6

#define    AGC_INTF_DET_THR_BW_NUM     12

#define    RF_9361_HW_TYPE              10
#define    RF_6360_HW_TYPE              11
#define    UL_APT_VBIAS_NUM             16

/*ET功能涉及的宏定义*/
#define    UL_ET_MAX_ET_MIPICMD_NUM       10
#define    UL_ET_MAX_APT_MIPICMD_NUM      10
#define    UL_ET_MAX_BYPASS_MIPICMD_NUM   16
#define    UL_ET_MAX_GAIN_COMP_NUM        16
#define    UL_ET_LUT_TBL_MAX_NUM          256
#define    UL_ET_FINEDLY_PARA_NUM          10

#define    LHPA_LOAD_NV_ET_VENDOR_TI        0
#define    LHPA_LOAD_NV_ET_VENDOR_R2        1
#define    LHPA_LOAD_NV_ET_VENDOR_QU        2

#define    UL_ET_ETM_CURMODE_DEFAULT      0
#define    UL_ET_ETM_CURMODE_ET            1
#define    UL_ET_ETM_CURMODE_APT           2
#define    UL_ET_ETM_CURMODE_BYPASS        3
#define    AGC_MAX_GAIN_LEVEL    (8)
#define    AGC_HRL_MAX_HAR_FREQ_NUM           (6)

#define    AGC_MAX_INTERF_TYPE   2
#define    AGC_MAX_GAIN_TYPE     3

#define    NV_RFIC_BALONGV7_MULTIBAN_BAND7
/* #define NV_RFIC_BALONGV7_MULTIBAN_BAND38 */
#define    MAX_HI6360_INITIAL_REG_NUM       40
#define    MAX_DSP_CFG_REG_RESV_NUM         4
#define    MAX_RF_BAND_NUM                  (28)

#define    RF_AGC_GAIN_NUM (8)
#define    RF_TX_FREQ_NUM (32)
#define    RF_RX_FREQ_NUM (16)
#define    RF_TX_GAIN_NUM (16)
#define    RF_TX_GAIN_6362_NUM (20)      /*K3V5 修改apc table num*/
#define    RF_BBGAIN_NUM_PER_RFGAIN (2)  /*k3v5_bzj 每个rf gain校准的bb gain的个数*/
#define    RF_BAND_WIDTH_NUM  8  /*k3v5_bzj lte带宽的个数*/
#define    RF_PA_GAIN_NUM  3
#define    RF_HD3_FREQ_NUM  2
#define    RF_HD3_POW_NUM   4
#define    RF_FILTER_MAX_COMP_AREA_NUM   (4) /*rf滤波器最大补偿区域个数*/
/*PBCH  噪声白化*/

#define    PD_PWR_CUR_MAX_NUM         16   /*PD功率曲线点个数*/
#define    PD_CAL_DAC_CFG_MAX_NUM     16   /*PD自校准过程DAC配置过程*/
#define    PD_CAL_VGA_CFG_MAX_NUM     8    /*PD自校准过程DAC配置过程*/
#define    PD_CAL_TX_REQ_NUM           16

#define    MAX_RFIC_PATH_NUM           2
#define    MAX_CHAN_NUM                4   /*2R下，下行支持的最大通道数*/
#define    MAX_RX_ANT_NUM              4   /*V7R5 下行天线数目*/
#define    MAX_TX_CHAN_NUM              (2) /*V7R5 上行通道数目*/
#define    MAX_IIP2_CHAN_NUM           4
#define    PA_TEMP_NUM                 32
#define  BAND_NUM_MAX          (28)
#define  BANDCOMB_NUM_MAX     (128)
#define  MAX_RFIC_INIT_REG    (256)
#define  RX_ANT_SEL_MIPI_NUM   (3)
#define  ANT_TUNNER_MIPI_NUM  (2)
#define  TX_ANT_SEL_MIPI_NUM   (2)
#define  PA_MODE_MIPI_NUM   (4)
#define  CA_ANT_MIPI_NUM  (2)
#define MAX_LSCANW_BAND_NUM     (7)
#define ANT_MIPI_NUM    (3)
#define    REGION_0                     0
#define    REGION_1                     1
#define    REGION_2                     2
#define    REGION_3                     3
#define    REGION_4                     4
#define    REGION_5                     5
#define    REGION_6                     6

#define    NO_RESULT               0xFFFF
#define    NUM_0                        0
#define    NUM_1                        1
#define    NUM_2                        2
#define    NUM_3                        3
#define    NUM_4                        4
#define    NUM_5                        5
#define    NUM_6                        6
#define    NUM_7                        7

#define    LPHY_NS14_BANDWIDTH_NUM      2


/************************************************************
                             数据结构定义
************************************************************/
#if 0

typedef struct
{
    UINT8 WhitenRuuSize1;                                 /*噪声白化的粒度1*/
    UINT8 WhitenRuuSize2;                                 /*噪声白化的粒度2*/
    UINT8 WhitenThreMode;                                 /*0: 使用DSP 查表计算的门限值  1： 使用NV项配置的门限值*/
    UINT8 Threshold_A;                                    /*噪声白化自适应开关门限Threshold_A*/
    UINT8 Threshold_B;                                    /*噪声白化自适应开关门限Threshold_B*/
    UINT8 WhitenSwitchPBCH;                               /*PBCH噪声白化硬开关*/
    UINT8 Rsv0[2];
}NV_PB_IRC_STRU;
/* BEGIN: Added by l00174474, 2011/6/8   问题单号:DTS2011060205002*/

/*PDC  IRC*/

typedef struct
{
    UINT8 WhitenRuuSize1;                                 /*噪声白化的粒度1*/
    UINT8 WhitenRuuSize2;                                 /*噪声白化的粒度2*/
    UINT8 PdcSInd;                                        /*不使用PDS sym4: 0 使用PDS sym4: 1 */
    UINT8 WhitenThreMode;                                 /*0: 使用DSP 查表计算的门限值  1： 使用NV项配置的门限值*/
    UINT8 Threshold_A;                                    /*噪声白化自适应开关门限Threshold_A*/
    UINT8 Threshold_B;                                    /*噪声白化自适应开关门限Threshold_B*/
    UINT8 Threshold_C;                                    /*噪声白化自适应开关门限Threshold_C*/
    UINT8 WhitenSwitchPDCCH;                              /*PDCCH噪声白化硬开关*/
    UINT8 WhitenSwitchPCFICH;                             /*PCFICH噪声白化硬开关*/
    UINT8 WhitenSwitchPHICH;                              /*PHICH噪声白化硬开关*/
    UINT8 Rsv0[2];
    UINT16 PHICH_TH_NonWhiten;                            /*PHICH噪声白化硬开关关闭时的门限*/
    UINT16 PHICH_TH_Whiten;                               /*PHICH噪声白化硬开关开启时的门限*/
} NV_PDC_IRC_STRU;

/*PDS  IRC*/
typedef struct
{
     UINT8 WhitenRuuSize1;                                /*噪声白化的粒度1*/
     UINT8 WhitenRuuSize2;                                /*噪声白化的粒度2*/
     UINT8 PdsSInd;                                       /*用一个slot 或两个， 使用与否符号0，1*/
     UINT8 WhitenThreMode;                                /*0: 使用DSP 查表计算的门限值  1： 使用NV项配置的门限值*/
     UINT8 Threshold_A;                                   /*噪声白化自适应开关门限Threshold_A */
     UINT8 Threshold_B;                                   /*噪声白化自适应开关门限Threshold_B */
     UINT8 Threshold_C;                                   /*噪声白化自适应开关门限Threshold_C */
     UINT8 WhitenSwitchPDSCH;                             /*PDSCH噪声白化硬开关*/
     UINT8 BfWhitenRuuSize1;                              /*噪声白化的粒度1*/
     UINT8 BfWhitenRuuSize2;                              /*噪声白化的粒度2*/
     UINT8 BfPdsSInd;                                     /*用一个slot 或两个， 使用与否符号0，1*/
     UINT8 BfWhitenThreMode;                              /*0: 使用DSP 查表计算的门限值  1： 使用NV项配置的门限值*/
     UINT8 BfThreshold_A;                                 /*噪声白化自适应开关门限Threshold_A */
     UINT8 BfThreshold_B;                                 /*噪声白化自适应开关门限Threshold_B */
     UINT8 BfThreshold_C;                                 /*噪声白化自适应开关门限Threshold_C */
     UINT8 BfWhitenSwitchPDSCH;                           /*PDSCH噪声白化硬开关*/
} NV_PDS_IRC_STRU;
#endif
typedef struct
{
    UINT8 WhitenRuuSize1;                                 /*噪声白化的粒度1*/
    UINT8 WhitenRuuSize2;                                 /*噪声白化的粒度2*/
    UINT8 WhitenThreMode;                                 /*0: 使用DSP 查表计算的门限值  1： 使用NV项配置的门限值*/
    UINT8 Threshold_A;                                    /*噪声白化自适应开关门限Threshold_A*/
    UINT8 Threshold_B;                                    /*噪声白化自适应开关门限Threshold_B*/
    UINT8 WhitenSwitchPBCH;                               /*PBCH噪声白化硬开关*/
    UINT8 Rsv0[2];
}NV_PB_IRC_STRU;

#define NV_PB_IRC_STRU_DEFAULT						{\
														6,\
														3,\
														0,\
														0,\
														100,\
														1,\
														0\
													}


/*PB  IRC*/

typedef struct
{
    UINT8 WhitenRuuSize1;                                 /*噪声白化的粒度1:alex 表62   */
    UINT8 WhitenRuuSize2;                                 /*噪声白化的粒度2             */
	UINT8 BalanceEst;									  /*干扰平衡判断使能che_irc_bl_est*/
    UINT8 WhitenThreMode;                                 /*0: 使用DSP 查表计算的门限值  1： 使用NV项配置的门限值*/
    UINT8 Threshold_A;                                    /*噪声白化自适应开关门限Threshold_A*/
    UINT8 Threshold_B;                                    /*噪声白化自适应开关门限Threshold_B*/
    UINT8 RuuTtiSwitch;									  /*Ruu_TTI_SWTICH*/
    UINT8 WhitenSwitchPDCCH;                              /*PDCCH噪声白化硬开关*/
    UINT8 IntraBalanceNum;								  /*RB 内不平衡点数*/
    UINT8 IntraBalanceThr;								  /*RB 内不平衡门限*/
    UINT8 InterBalanceNum;								  /*RB 间不平衡点数*/
    UINT8 InterBalanceThr;								  /*RB 间不平衡门限*/
    UINT8 RuuMode;										  /*RUU MODE*/
    UINT8 ucIRCRuuSet0;                                 /*PDCCH IRC Ruu非主对角线置0*/
    UINT8 ucCQIThrs_A;                                  /*CQI门限A*/
    UINT8 ucTGT_W;                       /* P矩阵计算主对角线元素自适应调整时参考位宽*/

} NV_PDC_IRC_STRU;



#define NV_PDC_IRC_STRU_DEFAULT						{\
														6,				/*WhitenRuuSize1*/\
														2,				/*WhitenRuuSize2*/\
														1,				/*BalanceEst*/\
														0,				/*WhitenThreMode*/\
														20,				/*Threshold_A*/\
														200,			/*Threshold_B*/\
														1,				/*RuuTtiSwitch*/\
														1,				/*WhitenSwitchPDCCH*/\
														2,				/*IntraBalanceNum*/\
														4,				/*IntraBalanceThr*/\
														3,				/*InterBalanceNum*/\
														4,				/*InterBalanceThr*/\
														1,				/*RuuMode*/\
														{0,0,0}			/*Rsv*/\
													}

/*PDS  IRC*/

typedef struct
{
     UINT8 WhitenRuuSize1;                                /*噪声白化的粒度1*/
     UINT8 WhitenRuuSize2;                                /*噪声白化的粒度2*/
     UINT8 PdsSInd;                                       /*用一个slot 或两个， 使用与否符号0，1；0/1/2/3，1/3定义与算法同，与BBP不同*/
     UINT8 Flag0th;										  /*符号01是否参加累加0/1/2*/
     UINT8 WhitenThreMode;                                /*0: 使用DSP 查表计算的门限值  1： 使用NV项配置的门限值*/
     UINT8 Threshold_A;                                   /*噪声白化自适应开关门限Threshold_A */
     UINT8 Threshold_B;                                   /*噪声白化自适应开关门限Threshold_B */
     UINT8 BfSDisIrcFlag;								  /*BF S SUBFRAME DISTRIBUTE IRC FLAG: 0, 1, 2  add che_irc_sd_set0 */
     UINT8 WhitenSwitchPDSCH;                             /*PDSCH噪声白化硬开关*/
     UINT8 BfWhitenRuuSize1;                              /*噪声白化的粒度1*/
     UINT8 BfWhitenRuuSize2;                              /*噪声白化的粒度2*/
     UINT8 AgcAdjDecideNosieProcFlag;					  /*是否使用agcadj flag标志*/
     UINT8 BfWhitenThreMode;                              /*0: 使用DSP 查表计算的门限值  1： 使用NV项配置的门限值*/
     UINT8 BfThreshold_A;                                 /*噪声白化自适应开关门限Threshold_A */
     UINT8 BfThreshold_B;                                 /*噪声白化自适应开关门限Threshold_B */
     UINT8 PdsRuuMode;									  /*RUU MODE*/
     UINT8 BfWhitenSwitchPDSCH;                           /*PDSCH噪声白化硬开关*/
     UINT8 JudgeSym0BalanceFlag;						  /* 判断符号0是否平衡使能*/
     UINT8 JudgeSym0BalanceThr;						      /* 判断符号0是否平衡门限*/
     UINT8 ucRsv;
} NV_PDS_IRC_STRU;

#define NV_PDS_IRC_STRU_DEFAULT								{\
																6,		/*WhitenRuuSize1*/\
																3,		/*WhitenRuuSize2*/\
																3,		/*PdsSInd*/\
																2,		/*Flag0th*/\
																0,		/*WhitenThreMode*/\
																40,		/*Threshold_A*/\
																80,		/*Threshold_B*/\
																0,      /*TBD BfSDisIrcFlag*/\
																1,		/*WhitenSwitchPDSCH*/\
																6,      /*TBD BfWhitenRuuSize1*/\
																3,      /*TBD BfWhitenRuuSize2*/\
															 	1,		/*AgcAdjDecideNosieProcFlag*/\
															 	0,		/*BfWhitenThreMode*/\
															 	64,		/*BfThreshold_A*/\
															 	100,	/*BfThreshold_B*/\
															 	1,		/*PdsRuuMode*/\
															 	1,		/*BfWhitenSwitchPDSCH*/\
															 	1,		/*JudgeSym0BalanceFlag*/\
															 	16,		/*JudgeSym0BalanceThr*/\
															 	0,		/*ucRsv*/\
															 }

typedef struct
{
    NV_PB_IRC_STRU     stPbIrc;
    NV_PDC_IRC_STRU    stPdcIrc;
    NV_PDS_IRC_STRU    stPdsIrc;

} NV_IRC_STRU;

typedef struct
{
	NV_IRC_STRU stIrc[2];
}NV_IRC_PUB_STRU;


typedef struct
{
   UINT8   RsIntpCoef[INTERP_COEF_ROW][INTERP_COEF_COLUMN];         /*加密系数配置*/
   UINT8   Rsv0;
   UINT16  PbchTimeIntCoef[PB_TIME_DOMAIN_INTP_NUM];                /*PB时域插值系数配置*/
   UINT16  PduTimeIntCoef[PDU_TIME_DOMAIN_INTP_NUM];                /*PDU时域插值系数配置*/
   UINT8   AlphaCoef[IIR_ALPHA_NUMBER];                             /*Alpha滤波系数配置*/
   UINT16  Rsv1;
   UINT32  ChanPhaseErrRx0[CHE_CPE_ROW][CHE_CPE_COLOUM];
   UINT32  ChanPhaseErrRx1[CHE_CPE_ROW][CHE_CPE_COLOUM];
} NV_CHE_INTP_STRU;

/*定时NV定义*/
typedef struct{
    VOS_UINT16  T_ParTD[6];         /*default: [48 64 64  96 96 96]时域加密时信道PDP峰均比保护门限，对应1.4M到20M带宽                       */
    VOS_UINT16  T_ParFD[6];         /*default: [64 64 64  96 96 96]频域加密时信道PDP峰均比保护门限，对应1.4M到20M带宽                       */
    VOS_UINT16  TrefShort[6];       /*default: [32 32 11 11 8 8]   DRX预同步 or IDLE解寻呼场景的定时提前量，以0.5Ts为单位,对应1.4M到20M带宽 */
    VOS_UINT16  TrefCommon[6];      /*default: [16 16 11 11 8 8]   其他场景的定时提前量，以0.5Ts为单位,对应1.4M到20M带宽                    */
    VOS_UINT16  FPWLenShort[6];     /*default: [3 6 12 24 48]      DRX预同步 or IDLE解寻呼场景的首径搜索窗长度，对应1.4M到20M带宽           */
    VOS_UINT16  FPWLenCommon[6];    /*default: [10 20 40 80 160]   其他场景的首径搜索窗长度，对应1.4M到20M带宽                              */
    VOS_UINT16  Tb;                 /*default: 384                 窗W1b和W2b的门限因子                                                     */
    VOS_UINT16  EndValue;           /*default: 8                   滤波系数下限索引值                                                      */
    VOS_UINT16  W;                  /*default: 128                 多径搜索窗搜索窗长                                                       */
    VOS_UINT16  FPWindow;           /*default: 20                  多径搜索窗基于峰值向前搜索首径的范围                                     */
    VOS_UINT16  HoldThrsh;          /*default: 32                  多径搜索窗低信噪比保护门限                                               */
    VOS_UINT16  Ncs;                /*default: 5                   连接态DRX用于判断解调定时有效性的小区搜索次数                            */
    VOS_UINT16  ResetThrs;          /*default: 288                 多径搜索窗判断解调定时有效性的门限(0.5Ts)                                */
    VOS_UINT16  Reserved;           /*default: 0                                                                                            */
}NV_TIMING_PARA_STRU;

typedef struct
{
    VOS_UINT8   N_6RB[4];           /*default: {[40,40,20,20]}*/
    VOS_UINT8   N_15RB[4];          /*default: {[40,40,20,20]}*/
    VOS_UINT8   N_Other;            /*default: {10}*/
    VOS_UINT8   Reserverd[3];       /*default: {0}*/
}NV_EMU_FAKECELL_PARA_STRU;
typedef struct
{
    UINT8    ucIdleInterFreqThrd;             /*default: 5 */
    UINT8    ucConnInterFreqThrd;             /*default: 5 */
    INT16    usReserved;
}NV_EMU_TASK_PERIOD_PARA_STRU;
typedef struct
{
    NV_EMU_TASK_PERIOD_PARA_STRU  stEmuTaskPeriodPara;
}NV_EMU_PARA_STRU;
typedef struct{
    VOS_UINT8   RuuAlpha;                       /*default:{{0},             Ruu的滤波因子                                                  */
    VOS_UINT8   WhitenRBStep;                   /*default:{0},              白化开关的频域子带粒度配置                                      */
    VOS_UINT8   CSIWhitenFlag;                  /*default:{0},              CQI计算是否白化的硬开关                                          */
    VOS_UINT8   CSIWhitenSwitchMode;            /*default:{0},              CQI计算是否用全带宽的干扰矩阵来做白化运算                        */
    VOS_UINT8   CSIWhitenKg[6];                 /*default:{1,1,1,1,1,1},    白化开关的频域RB粒度配置                                         */
    VOS_INT8    ESINRRepairFactor1[24];         /*default:{1,1,1,0,0,1,-1,-1,-1,-1,-1,-1,1,1,1,0,0,1,-1,-1,-1,-1,-1,-1},  有效信噪比补偿值1            */
    VOS_INT8    ESINRRepairFactor2[24];         /*default:{-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0},  有效信噪比补偿值2            */
    VOS_INT8    ESINRRepairFactor3[24];         /*default:{0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1},  有效信噪比补偿值3            */
    VOS_INT8    ESINRRepairFactor4[24];         /*default:{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  有效信噪比补偿值4            */
    VOS_INT8    RuuZeroFlag;                    /*default: 1*/
    VOS_INT8    Reserved;                       /*default: 0*/
    VOS_UINT16  gausRIFactorTrms[2][3];    // [256,256,256,256,256,256]          分别对应效率和 RBIR的 0,1,2
    VOS_UINT16  gausRIFactorCorr[2][3];    // [170,180,256,170,180,256]          分别对应效率和 RBIR的 0,1,2
    VOS_UINT16  gausRIFactorTm[2][4];      // [256,300,256,256,256,300,256,256]  分别对应效率和 RBIR的 TM3,TM4,TM8,TM9
    VOS_UINT16  gausRIFactorDuplex[2][2];  // [256,256,256,256]                  分别对应效率和 RBIR的 FDD,TDD
    VOS_UINT16  gausRIFactorWhiten[2][2];  // [256,256,256,256]                  分别对应效率和 RBIR的 非白化 ,白化
    VOS_UINT16  gausRIFactorVelocity[2];   // [256,281]                          分别对应高速和低速的取值
}NV_CQI_PARA_STRU;

typedef struct _LTE_ASU_NV_SUB_STRU_{
    UINT32                     ulPrachFailNumThr;  //下面是算法判决各门限值，连续接入失败达到门限次数则切天线
    UINT16                     usNGCThr;           //连接态连续判决为GOOD的门限次数，下面类似
    UINT16                     usNPCThr;
    UINT16                     usNGIThr;
    UINT16                     usNPIThr;

    UINT16                     usNumHappyIdleThr;
    UINT16                     usNumUnhappyIdleThr;
    INT32                      lGoodRsrpThr;       //判断为GOOD的RSRP门限值 下面类似
    INT32                      lPoorRsrpThr;
    INT16                      sGoodSinrThr;
    INT16                      sPoorSinrThr;
}LTE_ASU_NV_SUB_STRU;

typedef struct{
	UINT32        NV_ID_LTE_AS_CTRL;		//Bit0：表示天线检测功能是否开启，默认值为1。
											//Bit1：表示天线切换功能是否开启，默认值为1。
											//Bit2：指示DPDT默认状态。
											//Bit8~12：指示控制DPDT的GPIO序号。
											//其余Bits为预留。
	UINT8         NV_ID_LTE_AS_ALG_PARA[8];	//Byte0：alpha 滤波遗忘因子（量纲扩大16倍），默认值为2。
											//Byte1：N1 默认值 1
											//Byte2：N2 默认值 5
											//Byte3：N3 默认值 7
											//Byte4：SW_THR1 默认值 9dB
											//Byte5：SW_THR2 默认值 6dB
											//Byte6：SW_THR3 默认值 3dB
											//Byte7：SW_HYST 默认值 2s
    //+TAS250 20140928 begin
    LTE_ASU_NV_SUB_STRU stAsuNvSubPara;

	UINT32         NV_ID_LTE_TAS250_ENA;// 0
	//+tas250 end
}NV_ASU_PARA_STRU;

/*****************************************************************************
 数据结构说明  : LTE TAS扫频阶段Rssi门限值类型定义
*****************************************************************************/
typedef struct
{
	INT16     ssLteTasBsRssiThdFdd;              /*FDD下的TAS扫频Rssi门限*/
	INT16     ssLteTasBsRssiThdTdd;			     /*TDD下的TAS扫频Rssi门限*/
}NV_LTE_TAS_BS_RSSI_THD_STRU;

typedef struct{
    VOS_UINT8   RuuAlpha;                        /*default:{{0},      Ruu的滤波因子                                                  */
    VOS_INT8    RLMWhitenSwitch;                 /*default:{1},       RLM计算是否白化的硬开关                                         */
    VOS_INT8    RLMSwitchMode;                   /*default:{0},       白化开关的粒度是否是全带宽                                      */
    VOS_INT8    RLMWhitenN[2];                   /*default:{10,1},    白化开关的粒度,[0]对应粒度1，[1]对应粒度2                       */
    VOS_INT8    RLM_WhitenThd_FDD[24];           /*default:{0,...,0}, FDD，RLM Whiten判决门限修正值                                  */
    VOS_INT8    RLM_WhitenThd_TDD[24];           /*default:{0,...,0}, TDD，RLM Whiten判决门限修正值   "                              */
    VOS_INT8    RuuZeroFlag;                     /*default: 1*/
    INT8        cN310OutComp[2];
    INT8        cN310InComp[2];
}NV_RLM_PARA_STRU;

typedef struct{
    VOS_INT8    Corr_Tlayer1IRC;                 /*default: 19,       1发射天线或1接收天线时，判断噪声白化后的相关性的门限值         */
    VOS_INT8    Corr_Tlayer2IRC;                 /*default: 4},       2发2收或4发2收时，判断噪声白化后的相关性的门限值              */
    VOS_INT8    Reserved[2];                     /*Reseved: TBD*/
 }NV_ANTCORR_PARA_STRU;

/*VITERBI*/
typedef struct
{
    VOS_UINT16 DciTotalPwrThresh[2][4][4];      /*全体CCE软件度量值判决门限, [噪声白化开关][RSSP区间][DAGC调整量索引]*/
    VOS_UINT16 DciSinglePwrThresh[2][4][4];     /*单CCE软件度量值判决门限, [噪声白化开关][RSSP区间][DAGC调整量索引]*/
    VOS_UINT16 DciBerThresh[2];                 /*BER判决门限, [噪声白化开关]*/
    VOS_UINT32 CcDecTraceSelOrder;              /*加比选中幸存路径选择和回溯时起始状态选择的优先级顺序开关*/
}NV_VITERBI_PARA_STRU;

/*TURBO*/
typedef struct
{
    VOS_UINT32 TurboDecIterFactor;              /*各次迭代可靠因子, 取值范围: 35-48, 默认为45*/
}NV_TURBO_PARA_STRU;

typedef struct
{
    UINT16    ausRsThrd1Fdd[LPHY_TX_DUAL_ANTENNA][LPHY_MAX_BANDWIDTH_NUM];
    UINT16    ausRsThrd1TddCfg0[LPHY_TX_DUAL_ANTENNA][LPHY_MAX_BANDWIDTH_NUM];
    UINT16    ausRsThrd1TddNCfg0[LPHY_TX_DUAL_ANTENNA][LPHY_MAX_BANDWIDTH_NUM];
#if 0
    UINT16    ausOLHighThrd[2][LPHY_MAX_BANDWIDTH_NUM];
    UINT16    ausOLLowThrd[2][LPHY_MAX_BANDWIDTH_NUM];
#endif
    UINT16    ausILHighThrd[2][LPHY_MAX_BANDWIDTH_NUM];
    UINT16    ausILLowThrd[2][LPHY_MAX_BANDWIDTH_NUM];
}AFC_NV_RS_CONFIG_STRU;
typedef struct
{
    UINT16 usVctcxoThdHigh;             /* 动态TCXO高门限 */
    UINT16 usVctcxoDynamic;             /* 动态TCXO值, UE上电时由HPA读取NV并配置DSP,
                                               UE上电开机进入连接态后从DSP获取有效值写入NV */
    UINT16 usVctcxoFlag;                /* 动态TCXO取值是否有效标识, DSP可不用,
                                               0: 有效；其余无效，无效时usDynamicTcxo值无意义 */
    UINT16 usVctcxoFuncSwitch;          /* 动态TCXO功能是否使用开关, DSP可不用,
                                               修改后, 需要下电再上电才会生效
                                               0: 关闭, 关闭时usVctcxoDynamic取值usVctcxoInit
                                               1: 打开 */
}LTE_TCXO_DYNAMIC_CONFIG_STRU;

typedef struct
{
    UINT16    usEnableFlag;
    UINT16    usHSTMode;
    AFC_NV_RS_CONFIG_STRU    stAfcNvCRsConfig;
/*#ifdef CHIP_BB_6920CS   */
    AFC_NV_RS_CONFIG_STRU    stAfcNvMRsConfig;
/* #endif */
    UINT16    usFreqAdjustLimit; /*usLoopAdjustLimit; */
    UINT16    usFOHSTCompensation;
    /* UINT16    usInitPDM; */
    /* UINT16    usDynamicPDM;*/
    UINT16    usVoltageFactor;
    UINT16    usMFreqAdjustLimit;

    UINT16    usPdmHighThreshold;
    UINT16    usFreqOffsetThreLow;
    UINT16    usFreqOffsetThreHigh;
    UINT16    usPdmCcThreshold;
    UINT16    ausPdmParThreshold[LPHY_MAX_BANDWIDTH_NUM];
	UINT16                                  usRsv;
    INT16 sTempDiffNum;                 //温差超过门限次数
    INT16 sNormalTempLowLimt;           //常温区域低温门限
    INT16 sNormalTempHighLimt;          //常温区域高温门限
    INT16 sNormalCpThresh;              //常规CP阈值
    INT16 sExtendCpThresh;              //扩展CP阈值
    INT16 sCsDemodTimDiffNum;           //小区搜索与解调定时偏差次数
    INT16 sNormalTempDiff[4];           //常温区域温差门限，按DRX周期从高到低排序
    INT16 sNonNormalTempDiff[4];        //非常温区域温差门限，按DRX周期从高到低排序
}NV_AFC_PARA_STRU;

typedef struct {
    UINT8       ucVersion[16];                  /*发布版本年月日*/
    UINT32      ulVersionId;                    /*发布版本标识*/
}NV_VERSION_STRU;

typedef struct
{
    INT16     sPreTargetPowerFdd;
    INT16     sPreTargetPowerTdd;
    INT16     sPostTargetPower;
    INT16     sLeastSNR;

/*    INT16     sPwrConst; */
/*	UINT16    usReserved; */

    UINT8     ucDAGCAdjBitForTM1To6;
    UINT8     ucDAGCAdjBitForTM7To8;
    INT8      cMinAntPwr;
    INT8      cMaxAntPwr;

    UINT8     ucACSFilterThreshold[AGC_INTF_DET_THR_BW_NUM];//ca changed
    INT8      cACSPowerThreshold0[AGC_INTF_DET_THR_BW_NUM];
    INT8      cACSPowerThreshold1[AGC_INTF_DET_THR_BW_NUM];
    UINT8     ucNBFilterThreshold[AGC_INTF_DET_THR_BW_NUM];
    INT8      cNBPowerThreshold0[AGC_INTF_DET_THR_BW_NUM];
    INT8      cNBPowerThreshold1[AGC_INTF_DET_THR_BW_NUM];
    INT32    lHrlRsrpThr;
}NV_AGC_PARA_STRU;
/*UL NV */
typedef enum
{
    APC_GAIN_LEVEL_0 = 0,
    APC_GAIN_LEVEL_1 ,
    APC_GAIN_LEVEL_2 ,
    APC_GAIN_LEVEL_3,
    APC_GAIN_LEVEL_INVALID
}UL_APC_GAIN_LEVEL_ENUM;


typedef enum
{
    APC_GAIN_NONCROSS = 0,
    APC_GAIN_CROSS
}UL_APC_GAIN_CROSS_FLAG_ENUM;

typedef UINT16 UL_APC_GAIN_CROSS_FLAG_ENUM_UINT16;
typedef UINT16 UL_APC_GAIN_LEVEL_ENUM_UINT16;

typedef struct
{
    INT16 sPwrLow;
    INT16 sPwrHigh;
    UL_APC_GAIN_LEVEL_ENUM_UINT16 enAPcGainLevel;
    UL_APC_GAIN_CROSS_FLAG_ENUM_UINT16 enAgcGainCrossFlag;
}UL_APC_GAIN_CTRL_STRU;

typedef struct
{
    INT16  sPwr;
    UINT16 usVga;
}UL_APC_TABLE_ITEM_STRU;


#define APC_GAIN_AREA_NUM 3
#define APC_TABLE_NUM 2
#define APC_TABLE_LEN 64
/* #define APC_GAIN_LEVEL_NUM 4 */
/* BEGIN: Added by l00131321, 2012/11/24   问题单号:V7R2_MODIFY*/
typedef struct
{
    UINT16 usFreqFixSwitch;
    UINT16 usFreqSwitchStub;
    INT32  lIniPhase;
    INT32  lDeltaPhase;
}UL_FREQ_FIX_CTRl_STRU;

typedef struct
{
    UINT32 ulUlCfrSwitch;
    INT16  sSrsCfrThred;
    INT16  sPuschCfrThred;
}UL_CFR_CTRl_STRU;

typedef struct
{
    UINT16 usMtaSwitch;
    UINT16 usMtaAdjType; /* 0为子帧级调整，1为符号级调整 */
}UL_MTA_CTRL_STRU;

typedef struct
{
    UL_CFR_CTRl_STRU stCfrCtrl;
    UL_APC_GAIN_CTRL_STRU astApcCtrl[APC_GAIN_AREA_NUM];
    //UL_APC_TABLE_ITEM_STRU astApcTable[APC_TABLE_NUM][APC_TABLE_LEN];
    //UL_MTA_CTRL_STRU stMtaCtrl;
}NV_UL_PARA_STRU;


typedef struct
{
    UINT32 ulRegAddr;
    UINT32 ulValue;
}BBP_CFG_ITEM_STRU;

typedef struct
{
    UINT16 usRficRegAddr;
    UINT16 usRficRegValue;
}NV_LPHY_RFIC_CFG_STRU;


typedef enum
{
    RFIN_RFCH_RX0,
    RFIN_RFCH_RX1,
    RFIN_RFCH_RX2,
    RFIN_RFCH_RX3,
    RFIN_RFCH_BUTT
}RFIN_RFCH_ENUM;

typedef UINT8 RFIN_RFCH_ENUM_UINT8;


typedef struct
{
    RFIN_RFCH_ENUM_UINT8    enRfchType;
    UINT8                   usSingleAntFlag;
    UINT8                   usRsv0;
    UINT8                   usRsv1;
}NV_PHY_FUNC_VERIFY_STUB_STRU;

/*****************************************************************************
 结构名    : DRX_CTRL_FLAG_BIT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DRX控制开关
*****************************************************************************/
typedef struct
{
    UINT32  bitIdleDrxFlag              :1;
    UINT32  bitDspPwCtrl                :1;
    UINT32  bitLowDspPwCtrl             :1;
    UINT32  bitBbpPwCtrl                :1;
    UINT32  bitRfPwCtrl                 :1;
    UINT32  bitRfDvtyPwCtrl             :1;
    UINT32  bitPaPwCtrl                 :1;
    UINT32  bitLteSlavePwCtrl           :1;
    UINT32  bitGUTSlavePwCtrl           :1;
    UINT32  bitDspDfsCtrl               :1;
    UINT32  bitBbpDspDvsCtrl            :1;
    UINT32  bitSicClose                 :1;
    UINT32  bitBbpDfsCtrl               :1;
    UINT32  bitFlag13                   :1;
    UINT32  bitFlag14                   :1;
    UINT32  bitFlag15                   :1;
    UINT32  bitTimeMeasIdx0             :1;
    UINT32  bitTimeMeasIdx1             :1;
    UINT32  bitTimeMeasIdx2             :1;
    UINT32  bitFlag19                   :1;
    UINT32  bitFlag20                   :1;
    UINT32  bitFlag21                   :1;
    UINT32  bitFlag22                   :1;
    UINT32  bitFlag23                   :1;
    UINT32  bitFlag24                   :1;
    UINT32  bitFlag25                   :1;
    UINT32  bitFlag26                   :1;
    UINT32  bitFlag27                   :1;
    UINT32  bitFlag28                   :1;
    UINT32  bitAllActCdrxFlag           :1;/*使用CDRX打桩一直激活*/
    UINT32  bitDisCdrxFlag              :1;/*使用CDRX打桩去使能CDRX参数*/
    UINT32  bitGcfCdrxStubFlag          :1;/*已经被仪器测试使用，不要再使用*/
}DRX_CTRL_FLAG_BIT_STRU;

/*****************************************************************************
 结构体名  : NV_LPHY_DSP_CONFIG
 协议表格  :
 ASN.1描述 :
 枚举说明  : LPHY DSP开机初始化公共参数配置NV结构体定义
*****************************************************************************/
typedef struct{
    LRRC_LPHY_ANTANNA_PORT_ENUM_UINT16  enAntennaPortsCount;                /*LPHY UE的天线中用来接收下行信号的天线数目*/
    LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16 enLteMode;                          /*LPHY 初始化时默认的复用模式*/
    UINT32                              aulNvLteAntennaSwitchBand[MAX_RF_BAND_NUM];       /*LTE各Band对应的天线开关值, 比特0:9：FDD天线开关或TDD Rx天线开关值;比特16:25：TDD Tx天线开关值*/
    UINT16                              usNvLteOccaPreTime;                 /*lte构造异系统occasion时预处理中断提前量，单位us*/
    UINT8                               ucPowerOnLoadFlag;                  /*LPHY DSP上电第一次加载标识: "1"上电第一次加载;"0"非上电第一次加载*/
    UINT8                               ucNvLteInitialCfgRfabb;             /*LPHY 初始化时是否配置RF、ABB标识："1"配置;"0"不配置*/
    UINT8                               ucHwVersion;                        /*BalongV7R1硬件版本号*/
    UINT8                               ucNvLteBandNumber;                  /*LTE Band个数,<8*/
    UINT8                               aucNvLteBandInd[MAX_RF_BAND_NUM];                  /*LTE Band号数组，每个值对应LTE Band号*/
    UINT8                               aucNvLtePaEnInd[MAX_RF_BAND_NUM];                  /*LTE各Band对应的PA En比特位,Band指示与aucNvLteBandInd一致*/
    UINT8                               ucNvLteDefaultBandIdx;              /*初始化时缺省BAND序号*/
    /* BEGIN: Added by l00131321, 2011/10/15   问题单号:DTS2011101401498*/
    UINT8                               ucUeCap;                            /*1表示ue能力1，2标识ue能力2，5表示ue能力5*/
    UINT8                               ucAntSelect;                    /*0:false,1:true */
    UINT8                               ucSupport64Qam;                    /*0:64qam不支持，1:64qcam支持*/
    #if 0
    /*UINT8                               aucDspCfgRsv[2];  */                  /*LPHY 初始化配置预留参数*/
    UINT8                               ucIdleDrxControlFlag;/*IDLE DRX控制标志 */
    UINT8                               aucDspCfgRsv;                    /*LPHY 初始化配置预留参数*/

    /*#else*/
    #endif
    UINT16                              usLteTxTrxSwitchCfg;                /*LTE的Tx_switch和TRx_switch扩展标志，表示Tx_switch是否要扩展为2根*/
    UINT16                              usLteAbbIfFormat;                   /*LTE ABB接口配置*/
    UINT8                               ucLteC0C1Sel;                       /*双待时lte放在通道c0还是c1上*/
    UINT8                               ucLteSsiReadChSel;                  /*lte SSI回读的通道选择*/
    UINT8                               ucLteRficAd9361Sel;                 /*lte 是否选用AD9361*/
    UINT8                               ucLteAd9361TcvrOnFlag;              /*LTE使用AD9361支持多模单待时LTE的TCVR_ON管脚在通道0输出的状态*/
    UINT8                               ucTxiqFeedbackPath;                /*Hi6361s 通路A/B选择*/
    UINT8                               ucLteWakeSwitchTime;                /*Wake 唤醒到时钟切换的时间*/
    DRX_CTRL_FLAG_BIT_STRU              stNvDrxControlBitFlag;              /*IDLE DRX控制标志 */
}NV_LPHY_DSP_CONFIG;



/*****************************************************************************
 结构体名  : NV_GULPHY_COMMON_PARA_CONFIG
 协议表格  :
 ASN.1描述 :
 枚举说明  : GUL多模公共参数配置NV结构体定义
*****************************************************************************/
typedef struct{
    UINT8                               ucNvSingleDualModeInd;              /*单双待指示，0：单待；1：双待*/
    UINT8                               ucNvSingleDualRficInd;              /*单双RFIC，0：双RFIC；1：单RFIC*/
    UINT8                               ucNvCtuTimingDelayCnt;              /*CTU检测到timing_get_ind后固定延迟nv_ctu_timing_delay_cnt个CTU时钟周期后拉高timing_valid信号。*/
    UINT8                               ucNvPaMuxCtrl;                      /*GUL PA复用控制，3bit*/
}NV_GULPHY_COMMON_PARA_CONFIG;

typedef struct
{
              UINT16 usT1;                  /*T1默认值配置(根据切频配置寄存器数目而定)*/
              UINT16 usT2;                  /*T2默认值配置(RFIC锁频时间)*/
              UINT16 usT3FDD;               /*T3_FDD默认值配置(本频与异频之间的保护时间)*/
              UINT16 usT3TDD;               /*T3_TDD默认值配置(本频与异频之间的保护时间)*/
              UINT16 usT4;                  /*T4默认值配置(FIR滤波器延时)*/
              UINT16 usAGCCfgTime;          /*AGC配置提前量(逻辑配置射频增益的提前量)*/
              UINT16 usFDDADCOpenTime;      /*FDD ABB ADC打开提前量*/
              UINT16 usTDDADCOpenTime;      /*TDD ABB ADC打开提前量*/
              UINT16 usDACOpenTime;         /*ABB DAC打开提前量*/
              UINT16 usT7UL;                /*UL_RFIC_T7(TDD上行模式切换配置提前量)*/
              UINT16 usT7DL;                /*RFIC_T7(TDD下行模式切换配置提前量)*/
              UINT16 usT8ULFDD[7];          /*UL_FDD_T8_COMPENSATE*/
              UINT16 usT8ULTDD[7];          /*UL_TDD_T8_COMPENSATE*/
              UINT16 usT9;                  /*T9(TDD下行模式切换配置提前量)*/
              UINT16 usT10VGASPICfgTime;    /*T10上行VGA的SPI配置时间*/
              UINT16 usT15;                 /*T15*/
              UINT16 usTul[7];              /*上行通道延时*/
              UINT16 usPaOpenTime;          /*PA打开时间，基于PA特性*/
              UINT16 usPaAttTime;           /*PA ATT打开时间，基于PA特性*/
              UINT16 usAntSelTime;          /*ANT打开时间，基于ANT特性*/
              UINT16 usReserve;             /*保留备用*/
}NV_DSP_CONFIG_TIME_STRU;
/*****************************************************************************
 结构体名  : NV_LPHY_AGC_BASE_TABLE_STRU
 协议表格  :
 ASN.1描述 :
 枚举说明  : LPHY DSP AGC基准表NV结构体定义
*****************************************************************************/
typedef struct{
    UINT32 aulRx1AgcBaseTable[128];
    UINT32 aulRx2AgcBaseTable[128];
}NV_LPHY_AGC_BASE_TABLE_STRU;

typedef struct
{

     INT16 usFreqCmpInd;
     INT16 usTempCmpInd;
}NV_BT_CMP_SWITCH_STRU;

typedef struct
{
    UINT16 usDbbAtt;
	UINT16 usAbbAtt;
}NV_APC_ATT_TABLE_STRU;

typedef struct
{
    INT16 sHigh2MidThre;
	INT16 sMid2HighThre;
	INT16 sMid2LowThre;
	INT16 sLow2MidThre;
}EQUIP_PA_LEVEL_THRE_STRU;
typedef struct
{
 EQUIP_PA_LEVEL_THRE_STRU astPaThre[MAX_TX_CHAN_NUM];
}NV_PA_LEVEL_THRE_STRU;
typedef struct
{
    UINT32 ulDbbAttRegVal;
    UINT32 ulAbbAttRegVal;
    UINT32 ulAptPdmRegVal;
    UINT32 ulAptVoltRegVal;
    INT32  sUlPwr;
    UINT16 usBandwith;
    UINT16 usUlFreq;
    UINT16 usRbStart;
    UINT16 usRbNum;
    UINT16 usUlChType;
    UINT16 usRsv;
}UL_PWR_REG_STRU;
typedef struct
{
    UINT16 usUsePdmAptFlg;    /*1:enable  0:disable*/
    UINT16 usUseETMAptFlg;    /*1:enable  0:disable*/
    UINT16 usPDMAptEn;        /*pdm apt en*/
    UINT16 usETMEtEn;         /*etm ET en*/
    UINT16 usETMAptEn;
    UINT16 usETtoAptThres;
}EQUIP_APT_PARA_STRU;
typedef struct
{
    EQUIP_APT_PARA_STRU  stCh0AptPara;
    EQUIP_APT_PARA_STRU  stCh1AptPara;
}UL_APT_PARA_STRU;

typedef struct
{
    INT16  sTxpower;
    UINT16 usVoltVal;
}UL_APT_TX_POWER_PDMVAL_STRU;

typedef struct
{
    UINT16  ausCh0LteAptTable[RF_TX_GAIN_6362_NUM];
    UINT16  ausCh1LteAptTable[RF_TX_GAIN_6362_NUM];
}UL_APT_GAIN_VS_VBIAS_STRU;
typedef struct
{
    UINT16 usPdTotalFlg;         /*PD功能总开关*/
    UINT16 usDcOffsetThr;        /*DC offset门限，0.001v精度*/
    UINT16 usVgalowerGainThr;    /*VGA GAIN门限下限,0.001v精度*/
    UINT16 usVgaUperGainThr;     /*VGA GAIN门限下限0.001v精度*/
    UINT16 usHkAdcVCoeff;        /*HkAdc电压洗系数，HKADC读取值乘以该值除以1024为电压值(mv)*/
    UINT16 usPdCmpOffSwitch;     /*PD补偿开关，置为1则只检测不补偿*/
    UINT16 usPdValidTime;        /*PD检测时效时间*/
    UINT16 usPdCycNum;           /*PD循环次数，0对应1次，1对应2*/
    UINT16 usPdMaxPwrCmp;        /*PD最大的补偿保护,Delta大于此值按当前值补偿*/
    UINT16 usPdMinPwrCmp;        /*PD最小的补偿,Delta小于此值不再补偿*/
}NV_LPHY_PD_COMM_PARA;

typedef struct
{
    UINT16 usPdEnableFlg;          /*当前BAND是否使能PD*/
    INT16  sPwrStartThr;
    INT16  sPwrStopThr;
    UINT16 usPdAttenBx;            /*输入的功率衰减值*/
    UINT16 usPdRmsRfEn;            /*是否连接衰减器配置*/
    UINT16 usPdRfaSel;             /*1为9db，0为5db*/
    UINT16 usPdOrigCalVgaCfg;      /*初始校准VGA配置*/
    UINT16 usPdPowerIndexValidNum; /*预定义电压曲线有效个数*/
    UINT16 ausPdPowerIndex[PD_PWR_CUR_MAX_NUM];    /*预定义电压曲线*/
    UINT16 usPdDacCfgValidNum; /*预定义DAC配置表有效个数*/
    UINT16 usHkAdcChanl;           /*当前BAND使用的HKADC通道*/
    UINT16 ausPdCalDacList[PD_CAL_DAC_CFG_MAX_NUM];    /*校准过程DAC配置表*/
    UINT16 usPdVagCfgValidNum;     /*VGA配置有效个数*/
    UINT16 usRsv1;
    UINT16 aulPdCalVgaList[PD_CAL_VGA_CFG_MAX_NUM];       /*VGA配置表*/
    UINT16 usPdCalFreqValidNum;     /*VGA配置有效个数*/
    UINT16 usRsv2;
    UINT16 aulFreqList[PD_CAL_TX_REQ_NUM];
}NV_UL_PD_TX_PARA;

typedef struct
{
    UINT16 usDcOffset;             /*校准得到的DC配置*/
    UINT16 usVgaCfg;               /*VGA配置*/
}NV_TX_PD_AUTO_CAL_PARA;

/**************************ET相关，按照算法和逻辑要求，主要寄存器都设为可配置********/
typedef struct
{
    UINT16                          usEtTotalSwitch;        /*ET总开关*/
    UINT16                          usHKADCRatio;           /*Vout输入HKADC的分压比*/
    UINT16                          usCurEtmVendor;         /*当前ETM Vendor 0:TI,1:R2,2:Q,*/
    UINT16                          usAptEtActModeTime;     /*APT_ET_MODE_TIME,T4*/
} NV_TX_ET_COMM_PARA_STRU;

typedef struct
{
    UINT32         ulBypassCfg;       /*ET模块Bypass设置*/
    UINT32         ulDataDely;        /*数据通道延时*/
    UINT16         usPowerOffset;     /*功率偏置*/
    UINT16         usRsr;              /*保留*/
}UL_TX_ET_BBP_MOD_CFG_STRU;

typedef struct
{
    UINT32         ulEvDely;    /*包络通道延时粗调*/
} NV_TX_ET_EVDELY;

typedef struct
{
    UINT32         aulFineDlyPara[UL_ET_FINEDLY_PARA_NUM];    /*分数延迟寄存器值*/
    UINT16         usInitFineDly;        /*分数延迟插值中心*/
    UINT16         usRsv;
}NV_TX_ET_FINEDLY_PARA;

typedef struct
{
    INT16  sTxpower;            /*功率点*/
    UINT16 usGainComp;          /*补偿值,单位1/8db*/
}NV_LTE_ET_GAIN_COMP_PARA;

typedef struct
{
    UINT32         ulNum;     /*补偿功率点数*/
    NV_LTE_ET_GAIN_COMP_PARA   ulEtGainCmp[UL_ET_MAX_GAIN_COMP_NUM];    /*ET模式下pa增益补偿*/
}NV_LTE_ET_GAIN_COMP;

typedef struct
{
    UINT32                            ucValidflg:1;         /*当前指令是否有效*/
    UINT32                            ucExWFlg:1;           /*是否采用扩展写发送方式,1是*/
    UINT32                            ucWatTime:8;          /*发送完等待时间*/
    UINT32                            ucSlaveid:4;          /*设备USID*/
    UINT32                            ucMipiAddr:8;         /*在MIPI设备中的偏移地址*/
    UINT32                            ucByteCnt:3;          /*如果是扩展指令，指明CNT*/
    UINT32                            ucMipiPortSel:3;
    UINT32                            ulRsv:4;
} NV_MIPI_CMD_CTRL_STRU;

typedef struct
{
    NV_MIPI_CMD_CTRL_STRU            stMipiCtrl;

    UINT8                            ucCmdByte0;
    UINT8                            ucCmdByte1;
    UINT8                            ucCmdByte2;
    UINT8                            ucCmdByte3;
}LPHY_MIPIDEV_CMD_STRU;

typedef struct
{
    UINT16                              usPavcc;              /*APT_PA_VCC*/
    UINT16                              usAptVoltOffset;     /*APT配置电压寄存器偏移*/
    UL_TX_ET_BBP_MOD_CFG_STRU           stBbpEtCfg;           /*BBP寄存器配置*/
    UINT32                              ulETMipiCmdnum;      /*对ETM做ET激活的MIPI指令个数*/
    UINT32                              ulAPTMipiCmdnum;     /*对ETM做APT激活的MIPI指令个数*/
    UINT32                              ulBypassMipiCmdnum;  /*对ETM做Bypass激活的MIPI指令个数*/
    LPHY_MIPIDEV_CMD_STRU               stMipiEtmETCmdTriger;     /*激活ET的MIPI命令*/
    LPHY_MIPIDEV_CMD_STRU               stMipiEtmAPTCmdTriger;    /*激活APT的MIPI命令*/
    LPHY_MIPIDEV_CMD_STRU               stMipiEtmBypassCmdTriger; /*激活Bypass的MIPI命令*/
    LPHY_MIPIDEV_CMD_STRU               astMipiEtmETInitCmd[UL_ET_MAX_ET_MIPICMD_NUM];        /*ET模式的MIPI指令*/
    LPHY_MIPIDEV_CMD_STRU               astMipiEtmAPTInitCmd[UL_ET_MAX_APT_MIPICMD_NUM];      /*APT模式的MIPI命令*/
    LPHY_MIPIDEV_CMD_STRU               astMipiEtmBypassInitCmd[UL_ET_MAX_BYPASS_MIPICMD_NUM];/*Bypass模式的Bypass指令*/
    LPHY_MIPIDEV_CMD_STRU               stMipiEtmAPTVoltCmd;   /*ETM的APT模式输出电压*/
} NV_TX_ETM_VENDOR_PARA;

typedef struct
{
    VOS_UINT16                   usEtSwitch;          /*Band的ET开关*/
    INT16                        sEtThresh;           /*启动ET 的 功率门限*/
    INT16                        sAPTThresh;          /*启动APT 的功率门限*/
    INT16                        sCurMod;             /*当前模式:1-ET, 2-APT，3-Bypass*/
    INT16                        usHkAdcChanl;        /*当前BAND使用的HKADC通道*/
    UINT16                       usLowChanlFreq;      /*低于此频点为该BNAD低信道*/
    UINT16                       usHighChanlFreq;     /*高于此频点为该BAND高信道*/
    UINT16                       usRsv;
} NV_TX_ET_BAND_PARA;

typedef struct
{
    UINT32                       aulLutTbl[UL_ET_LUT_TBL_MAX_NUM];
} NV_TX_ET_CH_LUT_TBL_PARA;


typedef struct
{
    UINT16              usETPostOffset;          /*ET_Voffset*/
    UINT16              usETPostGain;             /*ET_Gain*/
}NV_LTE_ET_VOFFSET_GAIN;

#define PA_LEVEL_NUM  3
#define LNA_LEVEL_NUM 4
#define APC_ATT_MAX_NUM 88

typedef struct __NV_DEM_LIST_STRU__
{
    UINT8    ucInAdjBit;
    UINT8    ucInAdjBitBF;
    UINT8    ucPdschSfbcDemAlg;
    UINT8    ucPdschSdmaDemAlg;
    UINT16   usPHICHDemTHIrcOFF;
    UINT16   usPHICHDemTHIrcON;
}NV_DEM_LIST_STRU;

typedef struct
{
    INT16 usPaDiff[4];
}NV_PA_POWER_DIFFERENCE;

typedef struct
{
     UINT16 usAntCompDCI[16];
     UINT16 usAntCompDCQ[16];
}RF_DOCOC_ANT_ITEM_STRU;


typedef struct
{
    UINT16 usValidFlg;
    UINT16 usValidAntNum;
    RF_DOCOC_ANT_ITEM_STRU   astAntCal[MAX_RX_ANT_NUM];
}RF_DCOCS_DCCOMP_ITEM_STRU;

typedef struct
{
    RF_DCOCS_DCCOMP_ITEM_STRU  astDcocCalRst[MAX_RFIC_PATH_NUM];
}RF_DCOC_CAL_STRU;

typedef RF_DCOC_CAL_STRU NV_DCOC_CAL_TABLE_STRU;

typedef struct
{
    UINT16 usValidFlg;
    UINT16 usRsv;
	UINT16 usMain_I_DivOff[MAX_IIP2_CHAN_NUM];
	UINT16 usMain_Q_DivOff[MAX_IIP2_CHAN_NUM];
	UINT16 usMain_I_DivOn[MAX_IIP2_CHAN_NUM];
	UINT16 usMain_Q_DivOn[MAX_IIP2_CHAN_NUM];
	UINT16 usDiv_I[MAX_IIP2_CHAN_NUM];
	UINT16 usDiv_Q[MAX_IIP2_CHAN_NUM];
}NV_IIP2_CAL_ITEM;

typedef struct
{
	UINT16 usChanNum;
	UINT16 usRsv;
    NV_IIP2_CAL_ITEM    astIp2CalRst[MAX_RFIC_PATH_NUM];
}NV_IIP2_CAL_TABLE;

typedef struct
{
    INT16  sAmplitude;
    INT16  sPhase;
    INT16  sDCI;
    INT16  sDCQ;
}NV_TXIQ_ITEM_STRU;
typedef struct
{
    NV_TXIQ_ITEM_STRU astTxiqResult[MAX_TX_CHAN_NUM];
#if 0
    INT16  sAmplitude;
    INT16  sPhase;
    INT16  sDCI;
    INT16  sDCQ;
#endif
}NV_LTE_RF_TXIQ_CAL_STRU;

typedef struct
{
    INT16 sGainStatus[RF_TX_GAIN_NUM];
}NV_TX_APC_GAIN_ITEM_STRU;

typedef struct
{
    NV_TX_APC_GAIN_ITEM_STRU  astGainItem[3];  /*PA LEVEL,3档*/
}NV_TX_APC_GAIN_STRU;

typedef struct
{
    UINT16 usBias[RF_TX_GAIN_NUM];
}NV_TX_RF_BIAS_STRU;

typedef struct
{
    INT16 asBandWithCmp[4]; /*针对5M,10M,15M,20M*/
}NV_TX_RF_BANDWITH_CMP;

typedef struct
{
    UINT8   aucBbAttGain[RF_TX_GAIN_NUM];
    UINT16  usRsv1;
    UINT16  usRsv2;
    NV_TX_RF_BANDWITH_CMP stBandWithCmp;
}NV_TX_RF_BB_ATT_STRU;

typedef struct
{
    INT16 sFreqComp[RF_TX_FREQ_NUM];
}EQUIP_TX_RF_CHAN_FREQ_COMP_STRU;
/*typedef struct
{
    EQUIP_TX_RF_CHAN_FREQ_COMP_STRU  astFreq[MAX_TX_CHAN_NUM];
}NV_TX_RF_CHAN_FREQ_COMP_STRU;
*/
typedef struct
{
    EQUIP_TX_RF_CHAN_FREQ_COMP_STRU  astFreq[MAX_TX_CHAN_NUM];
}NV_TX_RF_FREQ_COMP_STRU;
typedef struct
{
    INT16 sPaTempComp[3][32];
}EQUIP_TX_PA_TEMP_COMP;
typedef struct
{
    EQUIP_TX_PA_TEMP_COMP  astTxTempCompFac[MAX_TX_CHAN_NUM];
}NV_TX_PA_TEMP_COMP;
typedef struct
{
    UINT16 usAttenTable[60];
}NV_TX_ATTEN_TABLE;
typedef struct
{
    UINT16 usPowerVoltage[3];
}NV_TX_POWERDET_VOLTAGE;

typedef struct
{
    UINT32 ulSwitchFlg;
    UINT32 ulResv;
}NV_LPHY_SWITCH_STRU;

typedef struct
{
	UINT32 	usRCcode;
	UINT32  usRsv;
}NV_RF_CA_RCCODE_STRU;

typedef struct
{
	INT16 ucLimitLeft;
    INT16 ucLimitRight;
    UINT16 ucInteration;
    UINT16 ucRsv;
}NV_RF_CA_RCCAL_CFG_STRU;

typedef NV_LPHY_SWITCH_STRU NV_LPHY_RF_BOARD_TYPE;

typedef struct
{
    UINT8 ucHarSwitch;
    UINT8 ucDcSwitch;
    UINT8 ucHarSpurFreqNum; //谐波干扰频点个数  小于AGC_HRL_MAX_HAR_FREQ_NUM
    UINT8 ucRsv;
    UINT16 ausHarSpurFreqInfo[AGC_HRL_MAX_HAR_FREQ_NUM];
}NV_HRL_SPUR_STRU;

typedef struct
{
    /*band related*/

    UINT8     ucAGCAcsMinGainZ;
    UINT8     ucAGCNbMinGainY;
    UINT8     ucReserved;
    UINT8     ucDefaultGain0;

    UINT8     ucDefaultGain1;
    UINT8     ucDefaultGain2;
    UINT16    usReserved;

    /*RF/AGC增益表*/
    UINT32     ulAGCGainTable[AGC_MAX_GAIN_LEVEL];
    UINT32     ulAGCAcsGainTable[AGC_MAX_GAIN_LEVEL];
    UINT32     ulAGCNbGainTable[AGC_MAX_GAIN_LEVEL];
    UINT32     ulRFIdxTable[2][AGC_MAX_GAIN_LEVEL];
    INT16      sRFErrorTable[4][AGC_MAX_GAIN_LEVEL];
}NV_AGC_BAND_GAIN_TABLE_STRU;
typedef struct
{
    UINT16      usFreqNum;
    UINT16      usRes;
    UINT16      usRxCalibrFreqList[RF_RX_FREQ_NUM];            /*Rx频率校准表*/
}NV_LTE_RX_CAL_LIST_STRU;
typedef struct
{
    INT8   	usAgcFreqComp[RF_AGC_GAIN_NUM][RF_RX_FREQ_NUM];
}LTE_RX_ANT_TYPE_COMP;
typedef struct
{
    LTE_RX_ANT_TYPE_COMP stAnt0FreqComp;
    LTE_RX_ANT_TYPE_COMP stAnt1FreqComp;
    LTE_RX_ANT_TYPE_COMP stAnt2FreqComp;
    LTE_RX_ANT_TYPE_COMP stAnt3FreqComp;
}LTE_RX_FREQ_BLOCK_TYPE;
typedef struct
{
    LTE_RX_FREQ_BLOCK_TYPE stNoBlockComp;
    LTE_RX_FREQ_BLOCK_TYPE stBlockComp;
}NV_LTE_RX_FREQ_COMP_STRU;

typedef struct
{
    UINT16 usTXPathNum;
    UINT16 usTXAntIndex[2];
}LTE_TX_PARA_STRU;

typedef struct
{
    UINT16 usRXPathNum;
    UINT8 usRXAntNum;
    UINT8  bitDefaultPathRxAnt0EnableFlg :1;
    UINT8  bitDefaultPathRxAnt1EnableFlg :1;
    UINT8  bitDefaultPathRxAnt2EnableFlg :1;
    UINT8  bitDefaultPathRxAnt3EnableFlg :1;
    UINT8  bitSecondPathRxAnt0EnableFlg  :1;
    UINT8  bitSecondPathRxAnt1EnableFlg  :1;
    UINT8  bitSecondPathRxAnt2EnableFlg  :1;
    UINT8  bitSecondPathRxAnt3EnableFlg  :1;

}LTE_RX_PARA_STRU;

typedef struct
{
    LTE_TX_PARA_STRU stTxCalPara;
    LTE_RX_PARA_STRU stRxCalPara;
}LTE_CAL_PARA_STRU;
typedef struct
{
    NV_LTE_RX_CAL_LIST_STRU      stRxCalFreqListLab;            /*Rx频率校准表*/
    NV_LTE_RX_FREQ_COMP_STRU   	 stchan0FreqCompFac;            /*每个通道频补*/
    NV_LTE_RX_FREQ_COMP_STRU   	 stchan1FreqCompFac;
    RF_DCOC_CAL_STRU             stDcocTbl;
    INT16     	asRxTempCmpVal[32];
    INT16     	asIP2CalChanList[MAX_IIP2_CHAN_NUM];
    NV_IIP2_CAL_TABLE stIP2CalResult;
    UINT16      usIp2CalApcCode;
    UINT16      usRsv2;
    NV_AGC_BAND_GAIN_TABLE_STRU           stAGCTable;        /*agc NV项 */
 	NV_HRL_SPUR_STRU                      stNvHrlInfo;       /*谐波控制结构*/
}NV_BAND_RXPATH_PARA_STRU;



typedef struct{
    UINT8 ucRxBtLeverMapTable[16];
}NV_RX_BT_LEVEL_MAP_TABLE_STRU;

typedef struct
{
    UINT16                      usRegionAVal;
    UINT16                      usRegionBVal;
    UINT16                      usRegionCVal;
    UINT16                      usRegionDVal;
}UL_AMPR_STRU;
/* BEGIN: Added by y00272211, 2015/2/12   问题单号:seattle_AMPR*/
typedef struct
{
    UINT16                      ausRegionAVal[NUM_2];
    UINT16                      ausRegionBVal[NUM_2];
    UINT16                      ausRegionCVal[NUM_2];
}UL_AMPR_EXTEND_STRU;
typedef struct
{
    UL_AMPR_STRU                astAmprValNS12[LPHY_MAX_BANDWIDTH_NUM];
    UINT16                      ausAmprNS12_1D4[NUM_3];
    UINT16                      usRev;
    UINT16                      ausAmprValNS13[NUM_2];
    UINT16                      ausAmprValNS14[LPHY_NS14_BANDWIDTH_NUM][NUM_2];
    UL_AMPR_EXTEND_STRU         astAmprValNS15[LPHY_MAX_BANDWIDTH_NUM];
}UL_AMPR_BAND26_STRU;
typedef struct
{
    UINT16                      ausAmprValNS18[NUM_2];
}UL_AMPR_BAND28_STRU;
/*band相关*/
typedef struct
{
    UINT16                      ausAmprValNS03[REGION_5];
    UINT16                      usRev;
}UL_AMPR_NS03_STRU;
typedef struct
{
    UINT16                      ausAmprValNS22[NUM_3][REGION_4];
}UL_AMPR_NS22_STRU;

/*band无关*/
typedef struct
{
    UL_AMPR_EXTEND_STRU         stAmprValNS07;
}UL_AMPR_NS07_STRU;
typedef struct
{
    UINT16                      usAmprValNS08;
    UINT16                      usRev;
}UL_AMPR_NS08_STRU;
typedef struct
{
    UINT16                      ausAmprValNS10[NUM_2];
}UL_AMPR_NS10_STRU;
typedef struct
{
    UINT16                      ausAmpr_Bw3M[NUM_2];
    UINT16                      ausAmpr_Bw5M[NUM_3];
    UINT16                      usAmpr_Bw10M;
    UINT16                      ausAmpr_Bw15M[NUM_2][REGION_5];
    UINT16                      ausAmpr_Bw20M[NUM_5];
    UINT16                      usRev;
}UL_AMPR_NS11_STRU;
typedef struct
{
    UINT16                      ausAmpr[NUM_3][NUM_3][REGION_5];/*频点、带宽和Region*/
    UINT16                      usRev;
}UL_AMPR_NS16_STRU;

typedef struct
{
    UINT16                      ausAmprValNS19[NUM_3][NUM_3];
    UINT16                      usRev;
}UL_AMPR_NS19_STRU;
typedef struct
{
    UINT16                      ausAmpr_Bw5M[NUM_4];
    UINT16                      ausAmpr_Bw10M[NUM_6];
    UINT16                      ausAmpr_Bw15M[NUM_6];
    UINT16                      ausAmpr_Bw20M[NUM_7];
    UINT16                      usRev;
}UL_AMPR_NS20_STRU;
typedef struct
{
    UINT16                      ausAmprValNS21[NUM_4];
}UL_AMPR_NS21_STRU;



typedef struct
{
	INT16  sWireLessMaxPwr;                   /*无线状态最大功率*/
	INT16  sWiredMaxPwr;                      /*传导状态最大功率*/
	UINT16 usTestModeInd;                     /*降SAR测试模式指示*/
	INT16  sReducedPwr[9];                    /*降SAR回退功率*/
}NV_ANT_SAR_STRU;

/*TAS2.0/2.5 SAR, max Power back NV*/

#define NORMSCEN_PWRBCK_LEVEL               6 /*一般场景，回退功率档位数*/
#define ESPSCEN_PWRBCK_LEVEL                3 /*特殊场景，回退功率档位数*/
#define MAX_ESPSCEN_BANDS_NUM               8 /*支持特殊场景的最大band数*/

typedef struct
{
    UINT16 usEspScenBand[MAX_ESPSCEN_BANDS_NUM];/*支持特殊场景的band索引列表*/
    UINT32 ulHLFreqThre;/*band高低频判决门限*/
}NV_LTE_COM_ANT_SAR_STRU; //降SAR公共参数

typedef enum
{
    SAR_PWR_BACK = 0,
    SAR_LF_BACK,
    SAR_HF_BACK,
    SAR_DPDTEX_PWR_BACK,
    SAR_DPDTEX_LF_BACK,
    SAR_DPDTEX_HF_BACK,
    SAR_INVALID
}NV_SCENE_SAR_ENUM;
typedef UINT32 NV_SCENE_SAR_ENUM_UINT32;

typedef struct
{
    INT16  sPwrBk                 ;/*DPDT直连，单modem，降SAR回退功率*/
    INT16  sLFrqPwrBk             ;/*DPDT直连，双modem对方低频，降SAR回退功率*/
    INT16  sHFrqPwrBk             ;/*DPDT直连，双modem对方高频，降SAR回退功率*/
    INT16  sDpdtExPwrBk           ;/*DPDT交叉，单modem，降SAR回退功率*/
    INT16  sDpdtExLFrqPwrBk       ;/*DPDT交叉，双modem对方低频，降SAR回退功率*/
    INT16  sDpdtExHFrqPwrBk       ;/*DPDT交叉，双modem对方高频，降SAR回退功率*/
}NV_SCENE_SAR_STRU;/*一般场景,降SAR回退功率*/

typedef struct
{
    INT16  sWireLessMaxPwr;         /*无线状态最大功率*/
    INT16  sWiredMaxPwr;            /*传导状态最大功率*/
    UINT16 usTestModeInd;           /*降SAR测试模式指示*/
    UINT16 usPwrBckEnFlag;          /*降SAR使能标志，1:降SAR, 0:不降SAR*/
    NV_SCENE_SAR_STRU      astNSSar[NORMSCEN_PWRBCK_LEVEL]; /*一般场景,降SAR回退功率*/
    NV_SCENE_SAR_STRU      astESSar[ESPSCEN_PWRBCK_LEVEL];  /*特殊场景,降SAR回退功率*/
}NV_LTE_DPDT_ANT_SAR_STRU;



#if 1
typedef struct
{
    UINT16 usValidFlag;    /*DBB回退生效标记*/
    UINT16 usMinRbNum;
    UINT16 usMaxRbNum;
    UINT16 usRbStart;
    UINT16 usBw;
    UINT16 usPowThreshold; /*功率大于此门限时才进行DBB回退，单位1/16*/
    UINT16 usDbbValue;     /*DBB 回退值， 单位1/16*/
    UINT16 usTargetPow;    /*回退后目标功率，单位1/16*/
}LTE_DBB_REDUCED_STRU;

#define MAX_DBB_REDUCED_NUM (6)

typedef struct
{
    UINT32 usDbbTotalValidFlag;
    LTE_DBB_REDUCED_STRU astDbbRed[MAX_DBB_REDUCED_NUM];
    UINT16 usDbbReduceAndULModemLoss[2];/* usDbbReduceAndULModemLoss[0] 为Ampr时Dbb的额外回退值；usDbbReduceAndULModemLoss[1]为ModemLoss */
}LTE_OTHER_COMP_STRU;
#else

typedef struct
{
    INT16  sDivLossComp;
    UINT16 usRes;
}LTE_TX_DIVERSITY_LOSS_COMP;
#endif

typedef struct
{
    UINT16 usValidFreqNum;
    UINT16 usValidPwrNum;
    INT16  asPdPower[PD_CAL_TX_REQ_NUM][PD_PWR_CUR_MAX_NUM];
}NV_TX_PD_PWR_TABLE_STRU;

typedef struct
{
    UINT16 usValidFreqNum;
    UINT16 usValidVoltNum;
    UINT16 ausPdVolt[PD_CAL_TX_REQ_NUM][PD_PWR_CUR_MAX_NUM];
}NV_TX_PD_VOLT_TABLE_STRU;

typedef struct
{
    UINT16  usValidNum;
    UINT16  usRsv;
    INT16 asPdTempCmp[32];
}NV_TX_PD_TEMPCMP_TABLE_STRU;
#if 0
typedef struct
{
	INT16 sTx1RbAdjVal;                      /*1RB发送时调整值 1/8db为单位*/
	INT16 sRsv[15];
}NV_TX_CMP_RSV_STRU;
#endif
typedef struct
{
	UINT16    usStartRbArea;    /*带宽带宽内需要补偿的起始rb*/
	UINT16    usEndRbArea;      /*带宽内最上端多少个RB内需要补偿 */
	INT16     sRes;         /* 低RB位置补偿值 */
	INT16     sCmpVal;      /* 高RB位置补偿值 */
}NV_TX_RF_ABB_FILTER_CMP_STRU;
typedef struct
{
    NV_TX_RF_ABB_FILTER_CMP_STRU ast5MComp[RF_FILTER_MAX_COMP_AREA_NUM]; /*5M滤波器补偿值*/
    NV_TX_RF_ABB_FILTER_CMP_STRU ast10MComp[RF_FILTER_MAX_COMP_AREA_NUM]; /*10M滤波器补偿值*/
    NV_TX_RF_ABB_FILTER_CMP_STRU ast15MComp[RF_FILTER_MAX_COMP_AREA_NUM]; /*15M滤波器补偿值*/
    NV_TX_RF_ABB_FILTER_CMP_STRU ast20MComp[RF_FILTER_MAX_COMP_AREA_NUM]; /*20M滤波器补偿值*/
    NV_TX_RF_ABB_FILTER_CMP_STRU ast30MComp[RF_FILTER_MAX_COMP_AREA_NUM]; /*30M滤波器补偿值*/
    NV_TX_RF_ABB_FILTER_CMP_STRU ast40MComp[RF_FILTER_MAX_COMP_AREA_NUM]; /*40M滤波器补偿值*/
}EQUIP_TX_FILTER_CMP_STRU;
typedef struct
{
    EQUIP_TX_FILTER_CMP_STRU  astTxFilterCompLab[MAX_TX_CHAN_NUM];
}NV_EQUIP_TX_FILTER_CMP_STRU;
typedef struct
{
    UINT16  ausGainNumsNeedCalEachPaLevel[RF_PA_GAIN_NUM];/*每个pa档位需要校准rfgain 的个数*/
    UINT16  sDbbValue;/*sDbbValue; 暂时不开发这个配置，避免引起麻烦*/
    UINT16  ausLteApcTable[RF_TX_GAIN_6362_NUM][RF_BBGAIN_NUM_PER_RFGAIN];
}EQUIP_LTE_APC_TABLE_STRU;
typedef struct
{
    EQUIP_LTE_APC_TABLE_STRU astApcTableLab[MAX_TX_CHAN_NUM];
}NV_LTE_APC_TABLE_STRU;
typedef struct
{
    INT16  asPaDiff[RF_PA_GAIN_NUM];/*pa中低档位和高档位的功率差，第一个值填0  如 0 -5 -10*/
    UINT16 usFreqCompPowerIndex;
    INT16  asRfDefaultPower[RF_TX_GAIN_6362_NUM][RF_BBGAIN_NUM_PER_RFGAIN];
}EQUIP_LTE_DEFAULT_POW_TABLE_STRU;
typedef struct
{
    EQUIP_LTE_DEFAULT_POW_TABLE_STRU  astTxDefaultPowLab[MAX_TX_CHAN_NUM];
}NV_LTE_DEFAULT_POW_TABLE_STRU;
typedef struct
{
    UINT16 usFreqNum;
    UINT16 usRes;
    UINT16 ausTxCalFreqList[RF_TX_FREQ_NUM];           /*TX校准频点，由低到高放置*/
    INT16  asTxCalCompListWired[RF_TX_FREQ_NUM];       /*TX有线频率补偿，实验室填写 默认全0，1/8db*/
    INT16  asTxCalAptPdmValFreqComp[RF_TX_FREQ_NUM];    /*TX APT 电压频率补偿 1/10V*/
}EQUIP_LTE_TX_CAL_LIST_STRU;
typedef struct
{
    EQUIP_LTE_TX_CAL_LIST_STRU astTxCalFreqListLab[MAX_TX_CHAN_NUM];
}NV_LTE_TX_CAL_LIST_STRU;
typedef struct
{
    INT16 sMaxPow;
    INT16 sMinPow;
}NV_LTE_TX_APC_GAIN_STATUS_POW;
typedef struct
{
    NV_LTE_TX_APC_GAIN_STATUS_POW astTxPaPower[RF_PA_GAIN_NUM][RF_TX_GAIN_6362_NUM];
}LTE_TX_CHAN_TABLE_STRU;
typedef struct
{
    LTE_TX_CHAN_TABLE_STRU astTxCHCalResultFac[MAX_TX_CHAN_NUM];
}NV_LTE_TX_CAL_RESULT_TABLE_STRU;
typedef struct
{
    INT16 sReal;
    INT16 sImg;
} LTE_CT_COMPLEX_STRU;
typedef struct
{
    LTE_CT_COMPLEX_STRU stHD3Cal10MLow;
    LTE_CT_COMPLEX_STRU stHD3Cal10MHigh;
    LTE_CT_COMPLEX_STRU stHD3Cal15MLow;
    LTE_CT_COMPLEX_STRU stHD3Cal15MHigh;
    LTE_CT_COMPLEX_STRU stHD3Cal20MLow;
    LTE_CT_COMPLEX_STRU stHD3Cal20MHigh;
}EQUIP_CT_HD3_CAL_POINT;
typedef struct
{
    EQUIP_CT_HD3_CAL_POINT astHD3CalPoint[MAX_TX_CHAN_NUM];
} LTE_CT_HD3_CAL_POINT;
typedef struct
{
    LTE_CT_HD3_CAL_POINT stHD3CalRst[RF_HD3_FREQ_NUM][RF_HD3_POW_NUM];/*3个频点，5个功率点*/
} NV_LTE_HD3_CAL_RSULT_STRU;
typedef struct
{
    UINT16 ausFreqList[RF_HD3_FREQ_NUM];
    INT16  asPowList[RF_HD3_POW_NUM];
}EQUIP_LTE_HD3_CAL_PARA_STRU;
typedef struct
{
    EQUIP_LTE_HD3_CAL_PARA_STRU astHD3CalParaLab[MAX_TX_CHAN_NUM];
} NV_LTE_HD3_CAL_PARA_STRU;

typedef struct
{
    UINT16 usFailThreshold;
    UINT16 usIterationNum;
    UINT16 usRsv0;
    UINT16 usRsv1;
}NV_LTE_TXIQ_CAL_PARA_STRU;

typedef struct
{
    INT16  asFilterCmp[8];/*1.4M 3M 5M 10M 15M 20M 30M 40M滤波器补偿*/
    UINT16 usRsv0;
    UINT16 usRsv1;
    UINT16 usRsv2;
    UINT16 usRsv3;
    UINT16 usRsv4;
    UINT16 usRsv5;
    UINT16 usRsv6;
    UINT16 usRsv7;
}NV_LTE_RESEVERD_NV_STRU;

/* BEGIN: Added by m00128895, 2015/10/8   PN:HP 降SAR特性开发*/
typedef struct NV_TX_HP_DEC_SAR
{
    UINT16 usAverSarExpPrd;    /*HP 降SAR算法功率平均周期，单位s，典型3或6分钟*/
    INT16  sAveSarExpThred;   /*HP 降SAR算法DPR ON触发平均功率门限，单位1/8dBm*/
    UINT16 usDprOnSarOffSet;   /*HP 降SAR算法限幅功率，相对DPR ON触发平均功率门限，单位1/8dBm*/
    UINT16 usDprOffSarOffSet;  /*HP 降SAR算法关闭触发门限，相对DPR ON触发平均功率门限，单位1/8dBm*/
}NV_TX_HP_DEC_SAR_STRU;

typedef struct
{
    NV_PA_LEVEL_THRE_STRU stPaThre;          /*PA档位门限*/
    NV_LTE_TX_CAL_LIST_STRU         stTxCalFreqListLab;      /*TX校准频点，由低到高放置*/
    NV_LTE_APC_TABLE_STRU           stApcTableLab;           /*k3v5_bzj apc teble pre band*/
    NV_EQUIP_TX_FILTER_CMP_STRU           stTxFilterCompLab;    /*k3v5_bzj 不同带宽,rb的功率补偿 1/8db单位*/
    NV_LTE_DEFAULT_POW_TABLE_STRU   stTxDefaultPowLab;       /*k3v5_bzj rf默认发射功率，做校准门限判断使用*/
    NV_LTE_TX_CAL_RESULT_TABLE_STRU stTXCalResultFac;        /*k3v5_bzj 发射校准结果*/
    NV_LTE_RF_TXIQ_CAL_STRU                stTxiqCal;
    NV_LTE_TXIQ_CAL_PARA_STRU       stTxiqCalPara;
    NV_LTE_HD3_CAL_PARA_STRU        stHD3CalParaLab;          /*HD3校准参数*/
    NV_LTE_HD3_CAL_RSULT_STRU       stHD3CalResultFac;        /*HD3校准结果*/
    NV_TX_RF_FREQ_COMP_STRU         stFreq;                   /*k3v5_bzj*/
    NV_TX_PA_TEMP_COMP              stTxTempCompFac;
    //INT16   asLteTxTempCmpVal[RF_TX_GAIN_6362_NUM][32];  /*tx温补*//*k3v5_bzj*/
    UL_APT_PARA_STRU                   stAptPara;        /*APT功能使能开关*/
	UL_APT_GAIN_VS_VBIAS_STRU          stPaHighVoltTbl;   /*APT PDM高档位控制字*/
	UL_APT_GAIN_VS_VBIAS_STRU          stPaMidVoltTbl;    /*APT PDM中控制字*/
	UL_APT_GAIN_VS_VBIAS_STRU          stPaLowVoltTbl;    /*APT PDM低控制字*/
    /*MPR begin*/
    UINT16 ausMprVal[4];
    /*MPR end*/
    UL_AMPR_STRU astAMprVal[LPHY_MAX_BANDWIDTH_NUM];
    UINT32 ulAmprValNS05;
    UINT16 usAmprValNS09[2];
    UL_AMPR_NS03_STRU       stAmprValNS03;
    UL_AMPR_NS22_STRU       stAmprValNS22;
    UINT16  asAptPaHighCmp[UL_APT_VBIAS_NUM-15];             /*APT PA增益补偿*/
    UINT16  asAptPaMidCmp[UL_APT_VBIAS_NUM-15];              /*APT PA增益补偿*/
    UINT16  asAptPaLowCmp[UL_APT_VBIAS_NUM-15];              /*APT PA增益补偿*/
	/*NV_TX_CMP_RSV_STRU   stTxCmpRsv;*/
    NV_ANT_SAR_STRU   stAntSarPwr;

    NV_LTE_DPDT_ANT_SAR_STRU        stLteDpdtAntSarPwr;


    LTE_OTHER_COMP_STRU     stOtherComp;

    NV_UL_PD_TX_PARA              stPdNv;
    NV_TX_PD_AUTO_CAL_PARA        stPdAutoCal;
    NV_TX_PD_PWR_TABLE_STRU       stPdPowerTbl;         /*PD功率表*/
    NV_TX_PD_VOLT_TABLE_STRU      stPdVoltTbl;          /*PD电压表*/
    NV_TX_PD_TEMPCMP_TABLE_STRU   stPdTempTbl;          /*PD温度表*/

    /* BEGIN: Added by m00128895, 2015/10/8   PN:HP 降SAR特性开发*/
    NV_TX_HP_DEC_SAR_STRU         stHpDecSarPara;       /*HP 降SAR算法NV参数*/

    /*ET功能涉及NV*/
	NV_TX_ET_CH_LUT_TBL_PARA      stEtLowChLut;         /*低信道LUT表，生产NV*/
	NV_TX_ET_CH_LUT_TBL_PARA      stEtMiddleChLut;      /*中信道LUT表，生产NV*/
	NV_TX_ET_CH_LUT_TBL_PARA      stEtHighChLut;        /*高信道LUT表，生产NV*/
	NV_TX_ET_BAND_PARA            stEtBandPara;         /*ET BAND NV，非生产NV*/
	NV_LTE_ET_GAIN_COMP           stEtGainComp;         /*ET PA Gain 补偿*/
	NV_TX_ET_FINEDLY_PARA         stEtFineDlyPara;      /*ET 细调分数延迟系数，生产NV*/
	NV_LTE_ET_VOFFSET_GAIN        stEtVoffsetGain;      /*ETM Voffset和Gain校准值，生产NV*/
	NV_TX_ET_EVDELY               stEtEvDely;           /*ET 包络通道延时粗调*/

    /* BEGIN: Added by l00260332, 2015/5/14   问题单号:V7R5 MODDIFY FOR 4R2T NV*/
    LTE_CAL_PARA_STRU             stCalPathAndAntNum;
    NV_LTE_RESEVERD_NV_STRU       stRsvNv;
	//NV_RF_CA_RCCODE_STRU          stRfRCcode;           /*RFIC Code*/
}NV_BAND_TXPATH_PARA_STRU;

typedef struct
{
	UINT16 usDlModemLoss[MAX_RX_ANT_NUM];
}NV_MODEM_LOSS_STRU;

typedef struct
{
	NV_MODEM_LOSS_STRU          stModemLoss;						   /*Modem与整机天线间线损*/
	UINT16                      ausTempSensor[PA_TEMP_NUM];            /*PA热敏电阻检测到的平台温度转变成电压*/
}NV_BAND_COMMON_PARA_STRU;





#define MAX_PCC_BAND_NUM  12
#define MAX_SCC_BAND_NUM        5
#define MAX_RF_INIT_REG_NUM     32
#define MAX_COMM_RSV            2
#define MAX_ABB_CH               2
#define MAX_BAND_RSV             2
#define RFIC_CTUNE_DEBUG        2
#define MAX_MIPI_INIT_NUM   16
#define MAX_CA_COUPLE           20
#define MAX_DEBUG_NUM           (12)

#define MAX_BAND_PATH_NUM  (2)
typedef struct
{
	UINT32  		bitAbbChFor2Rx01	: 2;  		/*band使用的ABB通道双收band均使用该通道号*/
	UINT32  		bitAbbChFor4Rx23	: 2;  		/*band使用的ABB通道仅4收band使用的另一个通道号*/
	UINT32  		bitAfcPinSel		: 2; 		/*band afc pdm源选择*/
	UINT32           bitRsv              : 26;
}NV_CHAN_PARA_STRU;
typedef struct
{
	UINT32  		bitRficIndex		: 1; 	 	/*最多两个RFIC*/
	UINT32  		bitRficVCOCore		: 1; 	 	/*最多两个RFIC*/
	UINT32  		bitRficDiv		    : 4; 	 	/*最多两个RFIC*/
	UINT32  		bitRficGroupSel	    : 1;  		/*RFIC LNA GROUP*/
	UINT32  		bitRficRxLOSel		: 1;  		/*RFIC RX LO SEL*/
	UINT32  		bitRfRx0LNA		    : 4;  		/*RFIC RXA LNA*/
	UINT32  		bitRfRx1LNA		    : 4; 		/*RFIC RXB LNA*/
	UINT32  		bitRfRx2LNA			: 4;  		/*band为非4收该配置无效，无需不配置*/
	UINT32  		bitRfRx3LNA		 	: 4; 	 	/*band为非4收该配置无效，无需不配置*/
	UINT32  		bitRfABExchgFlg		: 1;  		/*band使用的ABB通道双收band均使用该通道号*/
	UINT32  		bitRfCDExchgFlg		: 1;  		/*band使用的ABB通道仅4收band使用的另一个通道号*/
	UINT32		    bitRfRxSel          : 1;
	UINT32          bitRsv				: 5;
}NV_RFIC_PARA_STRU;
typedef struct
{
    NV_CHAN_PARA_STRU   stChPara;
    NV_RFIC_PARA_STRU   stRficPara;
}NV_BAND_DL_CHAN_PARA_STRU;
typedef struct
{
	UINT32  		bitRficIndex			: 1;  		/*最多两个RFIC*/
	UINT32  		bitRficVCOCore		    : 1; 	 	/*最多两个RFIC*/
	UINT32  		bitRficDiv		        : 4; 	 	/*最多两个RFIC*/
	UINT32  		bitRfTx0Port			: 4; 		/*RFIC TX0 LNA*/
	UINT32  		bitRfTx1Port			: 4; 		/*RFIC TX1 LNA,暂未使用只有上行MIMO使用*/
	UINT32  		bitAbbChForTx0   		: 2;  		/*band 上行使用的ABB通道*/
	UINT32  		bitAbbChForTx1   		: 2;  		/*只有上行MIMO使用*/
	UINT32  		bitAptPinSel		: 2; 		/*band apt pdm源选择*/
	UINT32  		bitPmuAuxSel		: 2;		/*band auxdac 源选择*/
	UINT32  		bitRsv				    : 10;
}NV_BAND_UL_CHAN_PARA_STRU;
typedef struct
{
	NV_BAND_DL_CHAN_PARA_STRU stBandRxPara;
	NV_BAND_UL_CHAN_PARA_STRU stBandTxPara;
}NV_FE_PATH_PARA_STRU;
typedef struct
{
	UINT16 usBand;
	UINT16 usPathNum;
	NV_FE_PATH_PARA_STRU stBandFePath[MAX_BAND_PATH_NUM];
}NV_FE_BAND_CH_PARA_STRU;

typedef struct
{
    UINT32                           bitDualStandbyFlg     :1;                    /*单双待指示 1:双待 0:单待*/
    UINT32                           bitRficNum             :2;                    /*当前平台rfic数目*/
    UINT32                           bitLTUsedRficIdx        :1;                   /*单rfic时当前正使用的rf*/
    UINT32                           bitPrint                :1;
    UINT32                           bitDeepPrint           :1;
    UINT32                           bitRsvAllEn            :10;
    UINT32                           bitPccBandNum          :16;                  /*当前配置支持band数目*/
    NV_FE_BAND_CH_PARA_STRU          stFeBandChPara[BAND_NUM_MAX];
}NV_FE_BASIC_INFO_STRU;
typedef struct
{
	UINT16 usBandDelayTime;
	UINT16 usBandAdvanceTime;
	UINT16 usRxAdvanceTime;
	UINT16 usRxDelayTime;
	UINT16 usTxAdvanceTime;
	UINT16 usTxDelayTime;
    UINT16 usRxAgcTime;
	UINT16 usTimeMaskSenario[9];
}NV_SCENE_TIMER_STRU;
typedef struct
{
	UINT16 usCtuInt0Time[2];
	UINT16 usCtuIntraValidTime[2];
	UINT16 usCtuIntraValidDelayTime[2];
	UINT16 usAbbRxEnTime[2];
	UINT16 usAbbTxEnTime[2];
	UINT16 usRfinInterEnTime[2];
	UINT16 usFpuDatEnTime[2];
	UINT16 usFpuGapEnTime[2];
	UINT16 usFpuInterIntraTime[2];
	UINT16 usExLnaEnTimeRsv;
	UINT16 usAntDlSelTimeRsv;
	UINT16 usAntUlSelTimeRsv;
	UINT16 usAntTimeRsv;
	UINT16 usAdiuEnTime[2];
	UINT16 usAptPdmEnTime[2];
	UINT16 usAptPdmModuTime[2];
	UINT16 usAuxSsiTime0[2];
	UINT16 usAbbCfgTime;
	UINT16 usAuxSsiTime1;
}NV_LINECTRL_TIMER_STRU;
typedef struct
{
	UINT16 usIdle2RxOnTime;
	UINT16 usStb2RxOnTime;
	UINT16 usTxOn2RxOnTime;
	UINT16 usIdle2TxOnTime;
	UINT16 usStb2TxOnTime;
	UINT16 usRxOn2TxOnTime;
	UINT16 usIdle2StbTime;
	UINT16 usRsv;
}NV_SSI_MIPI_SCENE_ADVTIMER_STRU;
typedef NV_SSI_MIPI_SCENE_ADVTIMER_STRU NV_SSI_TDD_SCENE_ADVTIMER_STRU;
typedef NV_SSI_MIPI_SCENE_ADVTIMER_STRU NV_SSI_FDD_SCENE_ADVTIMER_STRU;
typedef NV_SSI_MIPI_SCENE_ADVTIMER_STRU NV_MIPI_TDD_SCENE_ADVTIMER_STRU;
typedef NV_SSI_MIPI_SCENE_ADVTIMER_STRU NV_MIPI_FDD_SCENE_ADVTIMER_STRU;
typedef struct
{
	UINT16  usRxChDlyTime;                      /*下行通道延迟补偿*/
	UINT16  usTxChDlyTime;                  /*上行通道延迟补偿*/
}NV_CH_DELAY_TIMER_STRU;
typedef NV_CH_DELAY_TIMER_STRU NV_FDD_CH_DELAY_Rate6144_TIMER_STRU;
typedef NV_CH_DELAY_TIMER_STRU NV_FDD_CH_DELAY_Rate3072_TIMER_STRU;
typedef NV_CH_DELAY_TIMER_STRU NV_TDD_CH_DELAY_Rate6144_TIMER_STRU;
typedef NV_CH_DELAY_TIMER_STRU NV_TDD_CH_DELAY_Rate3072_TIMER_STRU;
typedef struct
{
	NV_SCENE_TIMER_STRU        	 stSceneTimer;
	NV_LINECTRL_TIMER_STRU            stLineCtrlTimer;
	NV_SSI_TDD_SCENE_ADVTIMER_STRU   stSsiTddSceneAdvTimer;
	NV_SSI_FDD_SCENE_ADVTIMER_STRU   stSsiFddSceneAdvTimer;
	NV_MIPI_TDD_SCENE_ADVTIMER_STRU  stMipiTddSceneAdvTimer;
	NV_MIPI_FDD_SCENE_ADVTIMER_STRU  stMipiFddSceneAdvTimer;
	NV_FDD_CH_DELAY_Rate6144_TIMER_STRU   stFddChDlyRate6144Timer;
	NV_FDD_CH_DELAY_Rate3072_TIMER_STRU   stFddChDlyRate3072Timer;
	NV_TDD_CH_DELAY_Rate6144_TIMER_STRU   stTddChDlyRate6144Timer;
	NV_TDD_CH_DELAY_Rate3072_TIMER_STRU   stTddChDlyRate3072Timer;
}NV_FE_TIMER_STRU;

typedef struct
{
    UINT16 usRegAddr;
    UINT16 usRegCfg;
}NV_RFIC_REG_CONFIG_STRU;

typedef struct
{
    UINT32 ulInitNum;
    NV_RFIC_REG_CONFIG_STRU stRfCfg[MAX_RF_INIT_REG_NUM];
}NV_FE_RFIC_INIT_STRU;

typedef struct
{
    UINT8 ucDebugEn;
    UINT8 ucRegNum;
    UINT16 usProcCH;
    UINT8 ucRfRegList[MAX_DEBUG_NUM];
}NV_RF_REG_DEBUG_STRU;

typedef struct
{
    UINT32 ulRegAddr;
    UINT32 ulRegCfg;
}NV_BBP_REG_CFG_STRU;
typedef struct
{
    UINT32 bitValidFlg  : 1;
    UINT32 bitRfRegAddr : 8;
    UINT32 bitRfRegCfg  : 16;
    UINT32 bitRsv        : 7;
}NV_RF_CTUNING_DEBUG_STRU;
typedef struct
{
    UINT32               ulRfTcvrOn;
    UINT32               ulRfUnReset;        /*RF解复位配置 1:解复位*/
    UINT32               ulAgcStub;          /*前端强制打桩，高16bit为生效标志，低16bit为控制字*/
    UINT32               ulApcStub;          /*前端强制打桩，高16bit为生效标志，低16bit为控制字*/
    UINT32               ulTrxSwitchMap;
    UINT32               ulTx0SwitchMap;
    UINT32               ulTx1SwitchMap;
    UINT32               ulAbbIfFmt;          /*ABB IQ交换*/
    UINT32               ulNewOrOldBoard;     /*根据此NV值决定用新的或者老的DBB TABLE 0:老的; 1:新的*/
    NV_BBP_REG_CFG_STRU  stRsvBbpCfg[MAX_COMM_RSV];  /*预留，调试用*/
    NV_RF_REG_DEBUG_STRU stRfDebug;
}NV_FE_COMM_CONFIG_STRU;

#if defined(LPHY_FEATURE_TAS)
typedef struct
{
    UINT32 ulDpdt0Default;
    UINT32 ulDpdt0SwitchMap;
    UINT32 ulDpdtPreT1;
    UINT32 ulDpdtPostT2;
}NV_PBAND_TAS_CFG;
#else
typedef struct
{
    UINT32 ulDpdt0Default;
    UINT32 ulDpdt0SwitchMap;
    UINT32 ulDpdt1Default;
    UINT32 ulDpdt1SwitchMap;
}NV_PBAND_TAS_CFG;
#endif

typedef struct
{
    UINT32 ulDpdtDefault;
    UINT32 ulDpdtSwitchMap;
}TL_NV_MAS_GPIO_CFG;
typedef struct
{
    UINT32 ulTasDpdt0Default;
    UINT32 ulTasDpdt0SwitchMap;
}NV_GPIO_TAS_CFG;

typedef struct
{
    UINT32 ulTasDpdtPreT1;
    UINT32 ulTasDpdtPostT2;
}NV_TAS_DPDT_PROTECT_CFG;

typedef struct
{
    UINT32 ulTasClgModeGpio;
}NV_TAS_CLG_MODE_GPIO_CFG;

typedef struct
{
    INT16 slDpdtMeasStartThr;
    INT16 ulReserv;
}NV_TAS_BLIND_SW_THD_STRU;
typedef struct
{
    INT32 lHappyRsrpThr;
    INT32 lUnhappyRsrpThr;
}NV_TAS_HAPPY_UNHAPPY_THD_STRU;

typedef struct
{
    UINT32 bitAbbCH                       :1;          /*Band所在ABB通道，0:CH0，1:CH1*/
    UINT32 bitRfIdx                       :1;          /*Band所在RFIC，0:RFIC0，1:RFIC1*/
    UINT32 bitAfcPdmSrcSel               :1;          /*band afc pdm 源选择*/
    UINT32 bitAptPdmSrcSel               :1;          /*band apt pdm 源选择*/
    UINT32 bitPmuSsiSrcSel               :1;
    UINT32 bitRfABChanExchg              :1;          /*ABB AB通道交换标志 1:交换 0:不交换*/
    UINT32 bitIntraBandNonCCABExchg     :1;          /*同1band非连续CA AB通道交换标记*/
    UINT32 bitRsv                         :1;
}NV_PBAND_CHAN_PARA_STRU;

typedef struct
{
    UINT32                  ulBandAntSelRx;      /*Band接收天线开关*/
    UINT32                  ulTddBandAntSelTx0;  /*发射天线选择指示为0时，Band发射天线开关，仅TDD适用*/
    UINT32                  ulBandAntSelTx1;    /*发射天线选择指示为1时，Band发射天线开关*/
    UINT32                  ulTxAntSel;
    UINT32                  ulPaEnMap;          /*各Band Paen map,SCC无此参数*/
    UINT32                  ulPaMode0Map;
    UINT32                  ulPaMode1Map;
    UINT16                  usPaModeCfg;        /*0x0~0x3依次为低，中，NULL，高档,0x30自控*/
    UINT8                   ucPaEnCfg;          /*0x3:强制高 0x1强制低，0x30自控*/
    UINT8                   ucUserPaOpenTime;
    NV_BBP_REG_CFG_STRU     stBandRsv[MAX_BAND_RSV];
    NV_PBAND_TAS_CFG        stTasConfig;       /*tas config*/
}NV_PBAND_CONFIG_PARA_STRU;
typedef struct
{
    UINT8  ucRx0Lna;
    UINT8  ucRx1Lna;
    UINT8  ucTxLna;
    UINT8  ucResv;
    NV_RF_CTUNING_DEBUG_STRU stRfCtuning;
}NV_PBAND_RFIC_PARA_STRU;
typedef struct
{
    UINT32 ulNum;
    LPHY_MIPIDEV_CMD_STRU astMipiCfg[MAX_MIPI_INIT_NUM];
}NV_MIPI_INIT_STRU;
typedef struct
{
    NV_PBAND_CHAN_PARA_STRU     stPBandChPara[MAX_PCC_BAND_NUM];
    NV_PBAND_CONFIG_PARA_STRU   stPBandConfig[MAX_PCC_BAND_NUM];
    NV_PBAND_RFIC_PARA_STRU     stPBandRficPara[MAX_PCC_BAND_NUM];
}NV_FE_PBAND_INFO_STRU;
typedef struct
{
    LPHY_MIPIDEV_CMD_STRU      stAnt0SelMipiRx; /*ANT0接收天线开关*/
    LPHY_MIPIDEV_CMD_STRU      stAnt1SelMipiRx; /*ANT1接收天线开关*/
    LPHY_MIPIDEV_CMD_STRU      stAnt0SelMipiTx; /*ANT0发送天线开关*/
    LPHY_MIPIDEV_CMD_STRU      stAnt1SelMipiTx; /*ANT1发送天线开关*/
    LPHY_MIPIDEV_CMD_STRU      stPaOnMipi;          /*PA使能命令*/
    LPHY_MIPIDEV_CMD_STRU      stPaOffMipi;          /*PA使能命令*/
    LPHY_MIPIDEV_CMD_STRU      stPaHighMipi;   /*PA高档MIPI命令*/
    LPHY_MIPIDEV_CMD_STRU      stPaMidMipi;    /*PA中档MIPI命令*/
    LPHY_MIPIDEV_CMD_STRU      stPaLowMipi;    /*PA低档MIPI命令*/
    LPHY_MIPIDEV_CMD_STRU      stTunerAnt0Mipi[2];    /*ANT0天线调谐*/
    LPHY_MIPIDEV_CMD_STRU      stTunerAnt1Mipi[2];    /*ANT0天线调谐*/
    LPHY_MIPIDEV_CMD_STRU      stMipiRsv[2];           /*预留一条MIPI*/
}NV_PBAND_MIPI_PARA_NEW_STRU;
typedef struct
{
    NV_PBAND_MIPI_PARA_NEW_STRU     stPBandMipiPara[MAX_PCC_BAND_NUM];
}NV_FE_PBAND_MIPI_INFO_STRU;

typedef struct
{
    UINT32                  ulBandAntSelRx;      /*Band接收天线开关*/
    UINT8                      ucSccTunerIdx;
    UINT8                      ulResv[3];       /*Note: ulResv[2] is used as main/dvty antenna switch flag*/
    LPHY_MIPIDEV_CMD_STRU      stAnt0SelMipiRx; /*SCC ANT0接收天线开关*/
    LPHY_MIPIDEV_CMD_STRU      stAnt1SelMipiRx; /*SCC ANT1接收天线开关*/
}NV_SBAND_LINE_STRU;



/*通道基本参数*/
typedef struct
{
    UINT32  bitRx0Lna           :4;
    UINT32  bitRx1Lna           :4;
    UINT32  bitRsv0              :24;
}NV_SBAND_RFIC_CONFIG_STRU;

    //NV_SBAND_CHAN_PARA_STRU         stSBandChanPara[MAX_SCC_BAND_NUM];

typedef struct
{
    NV_SBAND_RFIC_CONFIG_STRU   stRfCfg;
    NV_SBAND_LINE_STRU          stSBandInfo;
}NV_SBAND_CONFIG_STRU;

/*RFIC 基本参数*/
typedef struct
{
    UINT16                           usSBandNum;
    UINT16                           usSBandInd[MAX_SCC_BAND_NUM]; /*SCC * 5*/
    UINT16                           usRsv[2];


    NV_SBAND_CONFIG_STRU            stSBandPara[MAX_SCC_BAND_NUM];
}NV_SBAND_CONFIG_PARA_STRU;

typedef struct
{

    NV_SBAND_CONFIG_PARA_STRU   stSBandConfig[MAX_PCC_BAND_NUM];
}NV_FE_SBAND_INFO_STRU;

typedef struct
{
    UINT16 usPccBand;
    UINT16 usSccBand;
    LPHY_MIPIDEV_CMD_STRU      stAnt0TunerMipi[2]; /*SCC ANT0接收天线开关*/
    LPHY_MIPIDEV_CMD_STRU      stAnt1TunerMipi[2]; /*SCC ANT0接收天线开关*/
}NV_FE_CA_TUNER_PARA_STRU;


typedef struct
{
    NV_FE_CA_TUNER_PARA_STRU   stCaTunerPara[MAX_CA_COUPLE];
}NV_FE_CA_TUNER_INFO_STRU;

typedef struct
{


	UINT32 	ulLPhyNvSize;
}NV_LPHY_NV_SIZE_STRU;

/*for notch only B39*/
#define NOTCH_MIPI_MAX  2
typedef struct
{
	UINT16 usNotchEnFlg;
	UINT16 usGpioCfgFlg;
	UINT32 ulGpioNotchCfg;
	LPHY_MIPIDEV_CMD_STRU  stNotchMipiCfg[NOTCH_MIPI_MAX];
}NV_FE_NOTCH_INFO_STRU;

typedef struct
{
    UINT16 		 usLWCoexEnbale;
    UINT16       usTimerAheadTx;
    UINT16		 usTimerDelayTx;
    UINT16       usTimerAheadRx;
    UINT16		 usTimerDelayRx;
    UINT16		usWlanPriTimeout;
}NV_LPHY_LWCOEX_INIT_PARA_STRU;


typedef struct
{
    UINT8       ucLWCoexUartOrGpio;
    UINT8       ucRev0;
    UINT8       ucRev1;
    UINT8       ucRev2;
}NV_LPHY_LWCOEX_FEATURE_SELECT_STRU;

/* BEGIN: Added by m00128895, 2015/9/10   PN:Vramp 开发，meiaihong*/
#define MAX_LTE_VRAMP_PA_BAND_NUM    (2)

typedef struct
{
    UINT16 usPAOnTime;    /*PA Vramp提前配置时间，单位为Ts 1/30.72us*/
    UINT16 usPAOffTime;   /*PA Vramp延迟配置时间，单位为Ts 1/30.72us*/
    UINT16 usPaAgcOnTime; /*TX增益事件中AUXDAC SSI指令发送提前量，单位Ts,1/30.72us*/
    UINT16 usReserved;
}LTE_VRAMP_PA_ONOFFTIME_STRU;

typedef struct
{
    UINT16 usBandInd;     /*Band指示*/
    UINT16 usVrampFlag;
    UINT16 usPAHighVoltage;/*PA Vramp 高档位电压值,单位 2.5V/1024*/
    UINT16 usPAMidVoltage; /*PA Vramp 中档位电压值,单位 2.5V/1024*/
    UINT16 usPALowVoltage; /*PA Vramp 低档位电压值,单位 2.5V/1024*/
    UINT16 usReserved;
}NV_LPHY_VRAMP_BAND_PARA_STRU;

typedef struct
{
    UINT16 usVrampBandNum;
    UINT16 usReserved;
    LTE_VRAMP_PA_ONOFFTIME_STRU  stPaOnOffTime;
    NV_LPHY_VRAMP_BAND_PARA_STRU astVrampBandStru[MAX_LTE_VRAMP_PA_BAND_NUM];
}NV_LPHY_VRAMP_PARA_STRU;

#if 0
typedef struct
{
    UINT16      usVrmpFlag;
    UINT16      usBand39Vol;
}NV_LPHY_VRAMP_PARA_STRU;
#endif


#define MAX_MIPI_PA_ADDED_NUM    (2)
typedef struct
{
    LPHY_MIPIDEV_CMD_STRU   stPaLowCfg[MAX_MIPI_PA_ADDED_NUM];
    LPHY_MIPIDEV_CMD_STRU   stPaMidCfg[MAX_MIPI_PA_ADDED_NUM];
    LPHY_MIPIDEV_CMD_STRU   stPaHigCfg[MAX_MIPI_PA_ADDED_NUM];
    LPHY_MIPIDEV_CMD_STRU   stPaTrig;
}MIPI_PA_CONFIG_STRU;
typedef struct
{
    UINT32 ulPaTrigModeEn;
    MIPI_PA_CONFIG_STRU stBandPaMipi[MAX_PCC_BAND_NUM];
}NV_MIPI_PA_ADDED_CONFIG_STRU;

typedef struct
{
    LPHY_MIPIDEV_CMD_STRU stMipiAntRx0;
    LPHY_MIPIDEV_CMD_STRU stMipiAntRx1;
    LPHY_MIPIDEV_CMD_STRU stMipiAntTx;
}MIPI_ANT_CONFIG_STRU;

typedef struct
{
    MIPI_ANT_CONFIG_STRU stBandAddedAntMipi[MAX_PCC_BAND_NUM];
}NV_MIPI_ANT_ADDED_CONFIG_STRU;

/*切换状态的门限参数*/
typedef struct{
    UINT16		  usProbePeriod;        /*采数周期-单位-毫秒*/
    UINT8		  ucFilterAlpha;		// alpha 滤波遗忘因子（量纲扩大16倍），默认值为2。
 	UINT8		  ucCntHighThr;		    /*算法运行时满足高门限的连续次数门限*/
	UINT8		  ucCntLowThr;		    /*算法运行时满足低门限的连续次数门限*/
	UINT8		  ucCntTotalThr;	  	/*算法运行时二个天线最多比较次数门限*/
	UINT8		  ucDeltaHighThr;	    /*算法的二阶门限中的高门限，是待测天线和当前天线的能量差值*/
	UINT8		  ucDeltaLowThr;	    /*算法的二阶门限中的低门限，是待测天线和当前天线的能量差值*/
}NV_ASU_STATE_SUB_STRU;

/*稳态的门限*/
typedef struct{
    UINT16		  usPeriod;
    INT16		  ssRsv0;

 	INT32		  slOutStableRsrpThr;
    INT32         slOutStableSinrThr;
    UINT32        ulOutStablePoorCntThr;

	INT32		  slInStableRsrpThr;
    INT32         slInStableSinrThr;
}NV_ASU_STABLE_STRU;

/*主控、被控、稳态等的门限参数NV*/
typedef struct{
    NV_ASU_STABLE_STRU           stActiveStableThr;
    NV_ASU_STABLE_STRU           stPassiveStableThr;
	NV_ASU_STATE_SUB_STRU	     stActiveIbMasThr;       //主控上MAS切门限值
	NV_ASU_STATE_SUB_STRU	     stActiveIaMasThr;       //主控下MAS切门限值
    NV_ASU_STATE_SUB_STRU	     stPassiveIbMasThr;      //被控上MAS切门限值
    NV_ASU_STATE_SUB_STRU	     stPassiveIaMasThr;      //被控下MAS切门限值
    NV_ASU_STATE_SUB_STRU	     stTasThr;               //这个保留 仍使用原来的TAS NV结构: NV_ASU_PARA_STRU
    UINT16			             usActiveFrzTime;          //冻结态
    UINT16			             usPassiveFrzTime;         //冻结态
    UINT16			             usMasEna;
    UINT16			             usRsv0;
}NV_MAS_ASU_MODE_STRU;

typedef struct
{
    UINT16                       usTrigerBand;
    UINT16                       usTrigerFreq;
    UINT32			             usRsv;
}NV_LPHY_SINGLE_RX_BAND_CAL_PARA_STRU;



typedef struct
{
    UINT16 usBandNum;/*采用Eagle PA 的Band 数*/
    UINT16 usRsv;
    UINT16 ausEaglePaBand[BAND_NUM_MAX];/*采用Eagle Pa的Band列表*/
}NV_PA_TYPE_FLAG_STRU;
/****************************************************************************************/
typedef struct
{
    UINT16 usBtDbbReduce;
    UINT16 usWirelessDbbReduce;
    UINT16 rsv0;
    UINT16 rsv1;
}NV_BT_DBB_REDUCE_STRU;

/*****************************************band无关的nv项*********************************/
typedef struct
{
    NV_LPHY_NV_SIZE_STRU        stLPhyNvSize;       /*NV项Size*/
    NV_TIMING_PARA_STRU         stTiming;           /*定时NV项*/
    NV_EMU_FAKECELL_PARA_STRU   stEmuFakeCell;      /*能量测量小区定时失效判决*/
    NV_CQI_PARA_STRU            stCqi;              /*CQI NV项*/
	NV_ASU_PARA_STRU            stAsu;
    NV_ANTCORR_PARA_STRU        stCorr;             /*相关 NV项*/
    NV_RLM_PARA_STRU            stRLM;              /*RLM相关项*/
    NV_AFC_PARA_STRU            stAFC;              /*AFC NV项*/
    NV_IRC_PUB_STRU             stIrcPub;
    NV_CHE_INTP_STRU            stCheIntp;
    NV_VITERBI_PARA_STRU        stViterbi;
    NV_TURBO_PARA_STRU          stTurbo;
    NV_DEM_LIST_STRU            stDEM;
    NV_EMU_PARA_STRU            stEmu;                /*能量测量*/
    //NV_LPHY_AGC_BASE_TABLE_STRU stAgcBase;          /*AGC基准表*/
    NV_UL_PARA_STRU             stUl;
    NV_AGC_PARA_STRU            stAGC;                         /*agc NV项 */
    NV_VERSION_STRU             stVersion;          /*NV 版本信息*/

    NV_LPHY_DSP_CONFIG          stDspCfg;           /*DSP开机初始化公共参数配置NV*/
    NV_GULPHY_COMMON_PARA_CONFIG stGULCommParaCfg;  /*GUL多模公共参数配置NV结构体*/

    LTE_TCXO_DYNAMIC_CONFIG_STRU    stVctcxoDynamicConfig;
    UINT16 	usVctcxoInit;	                        /*Vco初值*/
    UINT16      usRsv1;

    NV_BT_CMP_SWITCH_STRU stBtCmpSwitch;

	NV_DSP_CONFIG_TIME_STRU      stRFECfgTime;      /*DSP相关配置时间移入NV项中*/

    NV_FE_NOTCH_INFO_STRU               stNotchInfo;   /*notch config*/
    NV_FE_BASIC_INFO_STRU               stFeBasicInfo;
/*    NV_FE_RFIC_INIT_STRU                stFeRfInitInfo;*/
    NV_FE_COMM_CONFIG_STRU              stFeCommCfg;
    NV_FE_PBAND_INFO_STRU               stPBandCfg;
    NV_FE_SBAND_INFO_STRU               stSBandCfg;
/*    NV_FE_PBAND_MIPI_INFO_STRU          stPBandMipiCfg;
    NV_FE_CA_TUNER_INFO_STRU            stCaTunerCfg;*/
    NV_MIPI_PA_ADDED_CONFIG_STRU        stPaMipiAddedCfg;   /*mipi pa额外配置*/

    NV_PHY_FUNC_VERIFY_STUB_STRU       stPhyFuncDebugPara;
    NV_RX_BT_LEVEL_MAP_TABLE_STRU stRxBtMapTable;

    VOS_UINT32                    ulSleepAddr;
	//NV_TX_FILTER_CMP_STRU         stTxFilterCmp;
	NV_PA_POWER_DIFFERENCE        stDefaultPaPowerDiff;
    NV_TX_APC_GAIN_STRU           stDefaultTxGainStatus;
    NV_LPHY_PD_COMM_PARA          stPdComm;
    NV_MIPI_INIT_STRU             stMipiInitCfg;

    /*ET功能使用NV*/
    NV_TX_ET_COMM_PARA_STRU       stEtCommPara;                /*ET公共参数*/
    NV_TX_ETM_VENDOR_PARA         stEtEtmVendorPara;           /*ET Modulator厂家参数*/

    /*RFIC校准使用NV*/
    NV_RF_CA_RCCAL_CFG_STRU       stRfRCcalCfg;                /*RFIC CA 校准参数*/
    NV_LPHY_LWCOEX_INIT_PARA_STRU  stLWCoexInitPara;

	NV_FE_TIMER_STRU                       stFeTimer;
    NV_LPHY_VRAMP_PARA_STRU             stVrampPara;

    TLCOMM_NV_SINGLE_XO_DEFINE_STRU stSingleXoDefine;           /*单XO类型及32k钟频率类型*/
    /* BEGIN: Added by y00272211, 2015/5/9   问题单号:V7R5_AMPR*/
	UL_AMPR_BAND26_STRU                 stAmprValBand26;
    UL_AMPR_BAND28_STRU                 stAmprValBand28;
	UL_AMPR_NS07_STRU                   stAmprValNS07;
	UL_AMPR_NS08_STRU                   stAmprValNS08;
	UL_AMPR_NS10_STRU                   stAmprValNS10;
	UL_AMPR_NS11_STRU                   stAmprValNS11;
    UL_AMPR_NS16_STRU                   stAmprValNS16;
	UL_AMPR_NS19_STRU                   stAmprValNS19;
	UL_AMPR_NS20_STRU                   stAmprValNS20;
	UL_AMPR_NS21_STRU                   stAmprValNS21;

    UINT16                              stTasEna;
	UINT16                              usResv2;
	NV_GPIO_TAS_CFG                     stLteGpioTas;
    NV_TAS_DPDT_PROTECT_CFG             stLteDpdtProtect;
	NV_LTE_TAS_BS_RSSI_THD_STRU         stTasBSRssiThd;					/*LTE TAS扫频阶段Rssi门限值*/
	NV_TAS_BLIND_SW_THD_STRU            stTasBlindSwThr;
	TL_NV_MAS_GPIO_CFG                  stLteGpioMas;
    NV_TAS_CLG_MODE_GPIO_CFG            stTasClgModeGpioMap;
	NV_TAS_HAPPY_UNHAPPY_THD_STRU       stTasHappyThr;

    NV_LTE_COM_ANT_SAR_STRU stComAntSar; //降SAR公共参数

	NV_MAS_ASU_MODE_STRU       stMasPara;

    NV_LPHY_SINGLE_RX_BAND_CAL_PARA_STRU         stRxBandCalPara;

    NV_PA_TYPE_FLAG_STRU                stpaTypeInfo; /*采用 Eagle Pa的band信息*/

    NV_BT_DBB_REDUCE_STRU  stBtDbbReduce;


    NV_LPHY_LWCOEX_FEATURE_SELECT_STRU  stLWCoexFeatureInfo; /*选择uart or gpio*/
	    /*dallas 抗干扰方案及功率回退*/
    UCOM_NV_FEATURE_INTERFE_STRU           stGuInterEnable;
    UCOM_NV_INTERFE_RULE_TABLE_STRU        stGuInterRuleTab;
    UCOM_NV_INTERFE_POWER_BACKOFF_STRU     stGuBackOff;

    /* BEGIN: Added by m00128895, 2015/10/29   PN:HP 降SAR特性开发*/
    UCOM_NV_TIME_AVG_SAR_FUNC_CTRL_STRU       stHpSarSwitch;
}LTE_NV_PARA_STRU;
/**********************************************************************************************/
/*******************************band相关的nv项*******************************************/
typedef struct
{
    NV_BAND_COMMON_PARA_STRU         stCommon;
    NV_BAND_RXPATH_PARA_STRU         stRxPath;
    NV_BAND_TXPATH_PARA_STRU         stTxPath;
}LTE_BAND_NV_PARA_STRU;

typedef struct
{
    NV_BAND_COMMON_PARA_STRU         stCommon;
    NV_BAND_RXPATH_PARA_STRU         stRxPath;
}LTE_BAND_NV_RX_PARA_STRU;
/**********************************************************************************************/


/********************************************V7R5 FE NV********************************************/

/**************************begin  单载波或连续CA  begin****************************/

/*V7R5基带最大支持18个单载波band*/

/*********************************************************************************
     为了尽量节省数据空间，对LRRC2LPHY的Band数据传输格式进行编码，使用UINT8表示

     bit[6:7]两bit用来表示Band的分段，如28、128、228... (41、541、641...)分别

     表示0、1、2...段,bit[5:0]表示Band1~64，所以协议，最终传递到DSP的实际Band的计算公式如下:

     FDD: Band = ((ucBandInd >> 6) & 0x3) * 100 + (ucBandInd & 0x3f);

     TDD: Band = ((ucBandInd >> 6) & 0x3 + 5) * 100 + (ucBandInd & 0x3f);

     说明: FDD分段编码小于500，TDD分段编码大于500，便于判定FDD/TDD
 *********************************************************************************/

typedef struct
{
/*bitBand bitPart一定要注意字节序的问题*/
    UINT8   bitBand       : 6;  /*协议Band*/
    UINT8   bitPart       : 2;  /*每个Band最多分4段，FDD:0、1、2、3(如28、128、228、328),TDD :0、1、2、3(如41、541、641、741)*/
}LPHY_NV_BAND_STRU;

typedef struct
{
	UINT8     ucValidFlg;                    /*NV有效标记*/
	UINT8     ucBandNum;                     /*上下行band数，bit[0:3] for dl,bit[4:7] for ul*/

	LPHY_NV_BAND_STRU     stUlBandInd[2];    /*下行band list*/

	LPHY_NV_BAND_STRU     stDlBandInd[4];    /*下行band list*/

}LRRC_LPHY_BANDCOMB_STRU;


/*前端每一个单载波或连续CA的下行参数*/
typedef struct
{
    UINT16 usAddr;      /*rf 寄存器地址*/
    UINT16 usData;      /*rf 寄存器配置*/
}NV_RFIC_REG_STRU;
#if 0
typedef struct
{
    UINT32              ulInitRegNum;        /*需要初始化rf寄存器的数目*/
    NV_RFIC_REG_STRU    stRfInitCfg[MAX_RFIC_INIT_REG];    /*初始化寄存器列表，取前ulInitRegNum个*/
}NV_RFIC_INIT_STRU;
#endif

typedef struct
{
	UINT32 	    ulAntSelRx;  			  	    /*GPIO 天线开关0*/
	UINT32        ulAntSelRxRsv;
	UINT32 	    ulRxTuner;  	 	    /*GPIO 天线开关0  的tuner 配置*/
	UINT32 	    ulRxTunerRsv;
	UINT32      ulDpdtDefaultCfg[2];          /*DPDT 开关上电默认配置*/
	UINT32      ulDpdtSwitchMap[2];           /*DPDT 开关切换MAP*/
	UINT32      ulExtLnaMap[4];				/*下行扩展LNA配置*/
	UINT32      ulExtLnaMod[4];
}NV_BAND_DL_GPIO_CTRL_STRU;

typedef struct
{
	UINT32 		ulTxAntSel0;			    /*上行主集天线开关*/
	UINT32 		ulTxAntSel1;                        /*上行分集天线*/
	UINT32 		ulPaEnCtrl[4];				/*Band PA EN 线控配置*/
	UINT32 		ulPaModeCfg[4];			/*Band PA MODE 0 抵挡 1 中档 2 高档 线控配置*/
	UINT16  		usPaOpenTime;			    /*Band PA 打开提前量*/
	UINT16  		usPaModeTime;			    /*Band PA 打开提前量*/
	UINT16  		usPaCloseTime;
	UINT16            usTxPchApcSsiTime;
	UINT16            usTxPchApcMipiTime;
	UINT16            usTxSrsApcSsiTime;
	UINT16            usTxSrsApcMipiTime;
	UINT16  	        usRsv;
}NV_BAND_UL_GPIO_CTRL_STRU;

typedef struct
{
	LPHY_MIPIDEV_CMD_STRU 		stMipiAntSelRx0[RX_ANT_SEL_MIPI_NUM];			/*接收天线开关0 MIPI 参数*/
	LPHY_MIPIDEV_CMD_STRU 		stMipiAntSelRx1[RX_ANT_SEL_MIPI_NUM];			/*接收天线开关1 MIPI 参数*/
	LPHY_MIPIDEV_CMD_STRU 		stMipiAntSelRx2[RX_ANT_SEL_MIPI_NUM];			/*接收天线开关2 MIPI 参数*/
	LPHY_MIPIDEV_CMD_STRU 		stMipiAntSelRx3[RX_ANT_SEL_MIPI_NUM];			/*接收天线开关3 MIPI 参数*/
	LPHY_MIPIDEV_CMD_STRU 		stMipiAntSel0Tuner[ANT_TUNNER_MIPI_NUM]; 		/*接收天线开关0 tunner MIPI 参数*/
	LPHY_MIPIDEV_CMD_STRU 		stMipiAntSel1Tuner[ANT_TUNNER_MIPI_NUM];		/*接收天线开关1 tunner MIPI 参数*/
	LPHY_MIPIDEV_CMD_STRU 		stMipiAntSel2Tuner[ANT_TUNNER_MIPI_NUM]; 		/*接收天线开关2 tunner MIPI 参数*/
	LPHY_MIPIDEV_CMD_STRU 		stMipiAntSel3Tuner[ANT_TUNNER_MIPI_NUM];		/*接收天线开关3 tunner MIPI 参数*/
	LPHY_MIPIDEV_CMD_STRU     	stMipiTrig[4];
}NV_BAND_DL_MIPI_CTRL_STRU;
typedef struct
{
	LPHY_MIPIDEV_CMD_STRU  	stMipiAntSelTx0[TX_ANT_SEL_MIPI_NUM];		/*上行天线开关0 MIPI*/
	LPHY_MIPIDEV_CMD_STRU 	stMipiAntSelTx1[TX_ANT_SEL_MIPI_NUM];		/*上行天线开关1 MIPI*/
	LPHY_MIPIDEV_CMD_STRU 	stMipiPaOnCtrl;			    /*Band PA EN MIPI配置*/
	LPHY_MIPIDEV_CMD_STRU 	stMipiPaOffCtrl;				/*Band PA DISABLE MIPI配置*/
	LPHY_MIPIDEV_CMD_STRU 	stMipiPaModeHigh[PA_MODE_MIPI_NUM];			/*Band PA MODE 高档MIPI 配置*/
	LPHY_MIPIDEV_CMD_STRU 	stMipiPaModeMid[PA_MODE_MIPI_NUM];			/*Band PA MODE 中档MIPI 配置*/
	LPHY_MIPIDEV_CMD_STRU  	stMipiPaModeLow[PA_MODE_MIPI_NUM];			/*Band PA MODE 低档MIPI 配置*/
	LPHY_MIPIDEV_CMD_STRU  	stMipiPaTrig;					/*预留*/
}NV_BAND_UL_MIPI_CTRL_STRU;


typedef struct
{

	UINT16                                                ulDlRfChIndex;
	UINT16  							ulFemPathIdx;  		/*进入RFIC芯片入口的独立路径*/

	NV_BAND_DL_GPIO_CTRL_STRU 		stDlGpioConfig;     /*下行通道GPIO 相关参数*/
	NV_BAND_DL_MIPI_CTRL_STRU    	stDlMipiConfig;     /*下行通道MIPI  相关参数*/
}NV_BAND_FE_DL_PARA_STRU;

/*前端每一个单载波或连续CA的上行参数*/

typedef struct
{
	UINT16           ulUlRfChIndex;
	UINT16  		ulFemPathIdx;  		/*进入RFIC芯片入口的独立路径*/


	NV_BAND_UL_GPIO_CTRL_STRU 		stUlGpioConfig;		 /*上行通道GPIO 相关参数*/
	NV_BAND_UL_MIPI_CTRL_STRU    	stUlMipiConfig; 		 /*上行通道MIPI  相关参数*/

}NV_BAND_FE_UL_PARA_STRU;

/*前端通道每一个单载波或连续CA 频段 硬件参数*/
typedef struct
{
	UINT16  	usBand;				        /*band 号*/

	UINT8       ucNvValidFlg;              /*NV有效标志*/
	UINT8  	    ucRxAntNum	;  	            /*band 使用的RX天线个数*/
	UINT8       ucTxAntNum;
	UINT8 		ucSecondDlValidFlg;       /*下行校准时第二条通路的是否有效的指示*/
	UINT8  		ucSecondUlValidFlg ;      /*上行校准时第二条通路的是否有效的指示*/
	UINT8  	    ucRsv;

	NV_BAND_FE_DL_PARA_STRU	    stDefaultDLChPara;   /*下行默认通道硬件参数*/
	NV_BAND_FE_UL_PARA_STRU 	stDefaultULChPara;   /*上行默认通道硬件参数*/

	NV_BAND_FE_DL_PARA_STRU	    stSecondDLChPara;   /*下行另一通道校准有效时所需硬件参数*/
	NV_BAND_FE_UL_PARA_STRU 	stSecondULChPara;   /*上行另一通道校准有效时所需硬件参数*/

}NV_SINGLE_BAND_FE_PARA_STRU;



/*此结构只给CSS使用*/
typedef struct
{
	//UINT32  		bitRfRxVCOCore            : 1; 	 	/*VCO Core选择,不使用，代码写死*/
	UINT32  		bitRsv0     			: 1;
	//UINT32  		bitRfRxDiv		    	: 4; 	 	/*VCO除数,不使用，代码写死*/
	UINT32  		bitRsv1    		    	: 4;
	UINT32  		bitRficGroupSel	    	: 1;  		/*RFIC LNA GROUP*/
	//UINT32  		bitRficRxLOSel			: 1;  		/*本振选择目前和通道绑定，不使用*/
	UINT32  		bitRsv2     			: 1;
	UINT32  		bitRfRx0LNA		    	: 4;  		/*RFIC RXA LNA*/
	UINT32  		bitRfRx1LNA		    	: 4; 		/*RFIC RXB LNA*/
	UINT32  		bitRfChIdx      		: 2;  		/*band使用的ABB通道双收band均使用该通道号*/
	//UINT32  		bitRfTxVCOCore	        : 1; 	 	/*VCO Core选择,不使用，代码写死*/
	//UINT32  		bitRsv3     		    : 1;
	//UINT32  		bitRfTxDiv		        : 4; 	 	/*VCO除数,不使用，代码写死*/
	UINT32  		bitRsv4  		        : 4;
	UINT32  		bitRfTx0Port			: 4; 		/*RFIC TX0 Port 只有pcc 使用*/
    UINT32          bitRsv                  : 7;
}NV_CSS_RFIC_6362_STRU;

typedef struct
{
    UINT32 bitAbbCH                       :1;          /*Band所在ABB通道，0:CH0，1:CH1*/
    UINT32 bitRfIdx                       :1;          /*Band所在RFIC，0:RFIC0，1:RFIC1*/
    UINT32 bitAfcPdmSrcSel               :1;          /*band afc pdm 源选择*/
    UINT32 bitAptPdmSrcSel               :1;          /*band apt pdm 源选择*/
    UINT32 bitPmuSsiSrcSel               :1;
    UINT32 bitRfABChanExchg              :1;          /*ABB AB通道交换标志 1:交换 0:不交换*/
    UINT32 bitIntraBandNonCCABExchg      :1;          /*同1band非连续CA AB通道交换标记*/
    UINT32 bitBlindSwitchFlag            :1;        /*是否支持TAS盲切,0表支持，需产线定制*/
    UINT32 bitMasSupport                 :24;       /*MAS支持能力 0-不支持 1-支持下天线MAS
                                                      2-支持上天线MAS 3支持都上下天线MAS*/
}NV_CSS_PBAND_CHAN_PARA_STRU;

typedef struct
{
    UINT32 ulDpdt0Default;
    UINT32 ulDpdt0SwitchMap;
    UINT32 ulDpdt1Default;
    UINT32 ulDpdt1SwitchMap;
}NV_CSS_PBAND_TAS_CFG;

typedef struct
{
    UINT32                  ulBandAntSelRx;      /*Band接收天线开关*/
    UINT32                  ulTddBandAntSelTx0;  /*发射天线选择指示为0时，Band发射天线开关，仅TDD适用*/
    UINT32                  ulBandAntSelTx1;    /*发射天线选择指示为1时，Band发射天线开关*/
    UINT32                  ulTxAntSel;
    UINT32                  ulPaEnMap;          /*各Band Paen map,SCC无此参数*/
    UINT32                  ulPaMode0Map;
    UINT32                  ulPaMode1Map;
    UINT16                  usPaModeCfg;        /*0x0~0x3依次为低，中，NULL，高档,0x30自控*/
    UINT16                  usPaEnCfg;          /*0x3:强制高 0x1强制低，0x30自控*/
    UINT16                  usSrsPaOpenTime;
    UINT16                  usPchPaOpenTime;
    NV_CSS_PBAND_TAS_CFG        stTasConfig;       /*tas config*/
}NV_CSS_PBAND_CONFIG_PARA_STRU;

typedef struct
{
    UINT32 bitValidFlg  : 1;
    UINT32 bitRfRegAddr : 8;
    UINT32 bitRfRegCfg  : 16;
    UINT32 bitRsv        : 7;
}NV_CSS_RF_CTUNING_DEBUG_STRU;

typedef struct
{
    UINT8  ucRx0Lna;
    UINT8  ucRx1Lna;
    UINT8  ucTxLna;
    UINT8  ucResv;
    NV_CSS_RF_CTUNING_DEBUG_STRU stRfCtuning;
}NV_CSS_PBAND_RFIC_PARA_STRU;

typedef struct
{
    LPHY_MIPIDEV_CMD_STRU      stAnt0SelMipiRx[ANT_MIPI_NUM]; /*ANT0接收天线开关*/
    LPHY_MIPIDEV_CMD_STRU      stAnt1SelMipiRx[ANT_MIPI_NUM]; /*ANT1接收天线开关*/
    LPHY_MIPIDEV_CMD_STRU      stAnt0SelMipiTx[ANT_MIPI_NUM]; /*ANT0发送天线开关*/
    LPHY_MIPIDEV_CMD_STRU      stAnt1SelMipiTx[ANT_MIPI_NUM]; /*ANT1发送天线开关*/
	LPHY_MIPIDEV_CMD_STRU      stAnt0Trig; /*ANT1发送天线开关*/
    LPHY_MIPIDEV_CMD_STRU      stAnt1Trig; /*ANT1发送天线开关*/
    LPHY_MIPIDEV_CMD_STRU      stPaOnMipi;          /*PA使能命令*/
    LPHY_MIPIDEV_CMD_STRU      stPaOffMipi;         /*PA使能命令*/
    LPHY_MIPIDEV_CMD_STRU      stPaHighMipi[4];    /*PA高档MIPI命令*/
    LPHY_MIPIDEV_CMD_STRU      stPaMidMipi [4];     /*PA中档MIPI命令*/
    LPHY_MIPIDEV_CMD_STRU      stPaLowMipi [4];     /*PA低档MIPI命令*/
	LPHY_MIPIDEV_CMD_STRU      stPaTrig; /*ANT1发送天线开关*/
    LPHY_MIPIDEV_CMD_STRU      stTunerAnt0Mipi[2];    /*ANT0天线调谐*/
    LPHY_MIPIDEV_CMD_STRU      stTunerAnt1Mipi[2];    /*ANT0天线调谐*/
    LPHY_MIPIDEV_CMD_STRU      stMipiRsv[2];           /*预留一条MIPI*/
}NV_PBAND_MIPI_PARA_STRU;


typedef struct
{
    UINT32  bitRx0Lna           :4;
    UINT32  bitRx1Lna           :4;
    UINT32  bitRsv0              :24;
}NV_CSS_SBAND_RFIC_CONFIG_STRU;


typedef struct
{
    UINT16 usPccBand;
    UINT16 usSccBand;
    LPHY_MIPIDEV_CMD_STRU      stAnt0TunerMipi[2]; /*SCC ANT0接收天线开关*/
    LPHY_MIPIDEV_CMD_STRU      stAnt1TunerMipi[2]; /*SCC ANT0接收天线开关*/
}NV_CSS_FE_CA_TUNER_PARA_STRU;

typedef struct
{
    UINT32                     ulBandAntSelRx;      /*Band接收天线开关*/
    UINT32                     ucSccRfABExchg;
    LPHY_MIPIDEV_CMD_STRU      stAnt0SelMipiRx[3]; /*SCC ANT0接收天线开关*/
    LPHY_MIPIDEV_CMD_STRU      stAnt1SelMipiRx[3]; /*SCC ANT1接收天线开关*/
    /*Tuner Mipi Cmd move here*/
    NV_CSS_FE_CA_TUNER_PARA_STRU   stCaTunerPara;
    LPHY_MIPIDEV_CMD_STRU      stAnt0Trig; /*ANT1发送天线开关*/
	LPHY_MIPIDEV_CMD_STRU      stAnt1Trig; /*ANT1发送天线开关*/
}NV_CSS_SBAND_LINE_STRU;

typedef struct
{
	//NV_RFIC_6362_STRU 			stRfic;
    UINT8                           ucSccRfPathIdx;
    INT8                            scRsv[3];
    NV_CSS_SBAND_RFIC_CONFIG_STRU   stRfCfg;
    NV_CSS_SBAND_LINE_STRU          stSBandInfo;
}NV_CSS_SBAND_CONFIG_STRU;

typedef struct
{
    UINT32                           usSBandNum;
    UINT32                           usSBandInd[6]; /*SCC * 5*/
    UINT16                           usRsv[2];
    NV_CSS_SBAND_CONFIG_STRU         stSBandPara[6];
}NV_CSS_SBAND_CONFIG_PARA_STRU;

typedef struct
{
    UINT16                          usBand;
    UINT16                          usNvValidFlg;
    NV_CSS_PBAND_CHAN_PARA_STRU     stBandChanPara;
    NV_CSS_PBAND_CONFIG_PARA_STRU   stBandLinePara;
    NV_CSS_PBAND_RFIC_PARA_STRU     stBandRfPara;
    NV_PBAND_MIPI_PARA_STRU     stBandMipiPara;
    NV_CSS_SBAND_CONFIG_PARA_STRU   stBandSccPara;
}LPHY_RFD_CSS_INTRA_BAND_NV_STRU;

typedef struct
{
    NV_BAND_COMMON_PARA_STRU         stCommon;
    NV_BAND_RXPATH_PARA_STRU         stRxPath;
}LTE_NV_RX_PARA_LSCANW_STRU;

typedef struct
{
    LPHY_RFD_CSS_INTRA_BAND_NV_STRU     stRfdIntraBandNv;
    NV_CSS_RFIC_6362_STRU               stRfic6362;
}LTE_NV_RFD_LSCANW_STRU;

typedef struct
{
    UINT16 usBand;
    UINT16 usValidFlg;
    UINT32 ulFeNvAdd;
    UINT32 ulRxParaNvAdd;
}LRRC_LPHY_LSCANW_DDR_ADDR_STRU;
typedef struct
{
    LRRC_LPHY_LSCANW_DDR_ADDR_STRU strDdrAddr[MAX_LSCANW_BAND_NUM];
}LRRC_LPHY_LSCANW_DDR_ADDR_LIST_STRU;

/**************************end  单载波或连续CA  end****************************/
/**********************************begin  多载波 begin***********************************/

typedef struct
{
	NV_BAND_DL_MIPI_CTRL_STRU    		stDlMipiConfig;     /*下行通道MIPI  相关参数*/
	NV_BAND_DL_GPIO_CTRL_STRU 		    stRsv;     /*下行通道GPIO 相关参数*/
}NV_NCCA_DL_COMM_PARA_STRU;

typedef struct
{
	NV_BAND_UL_MIPI_CTRL_STRU    		stUlMipiConfig;     /*下行通道MIPI  相关参数*/
	NV_BAND_UL_GPIO_CTRL_STRU 		    stRsv;     /*下行通道GPIO 相关参数*/
}NV_NCCA_UL_COMM_PARA_STRU;
typedef struct
{
	NV_BAND_UL_GPIO_CTRL_STRU 		    stUlGpioConfig;     /*下行通道GPIO 相关参数*/
	NV_BAND_UL_MIPI_CTRL_STRU    		stUlMipiConfig;     /*下行通道MIPI  相关参数*/
}NV_NCCA_UL_PRIVATE_PARA_STRU;

typedef  struct
{
	/*UINT8                               uc4AntenaFlg;*/

	/*本CA组合下本Band对应下行的RFIC和Group的基准校准通道的误差项，实验室补偿，不做校准*/

	/*本CA组合下本Band对应的下行RF FrontEnd通路的编号, 用于不同的CA组合切换时识 别本Band是否
	   发生RFFE的切换对基带的处理包含时频同步、解调等有影响。 通路编号相同则认为通路不变*/
	//UINT32 								ulRfFeNum;

	UINT32 								ulBand;				/*band*/
	INT32 								lGainErrInd;
	UINT16								ulDlRfChIdx;/*前端单band RF通道配置参数2选1*/
	UINT16  		                                             ulFemPathIdx;
	NV_BAND_DL_GPIO_CTRL_STRU 		    stDlGpioConfig;     /*下行通道GPIO 相关参数*/
}NV_NCCA_DL_BAND_PARA_STRU;

typedef struct
{
	UINT32 					    ulTddAntSelTx0;			/*TDD 上行天线开关0*/
	UINT32 					    ulTddAntSelTx1;			/*TDD 上行天线开关1*/

	LPHY_MIPIDEV_CMD_STRU 		stMipiAntSel0[2];			/*接收天线开关0 MIPI 参数*/
	LPHY_MIPIDEV_CMD_STRU 		stMipiAntSel1[2];			/*接收天线开关1 MIPI 参数*/
	LPHY_MIPIDEV_CMD_STRU 		stMipiAntSel2[2];			/*接收天线开关2 MIPI 参数*/
	LPHY_MIPIDEV_CMD_STRU 		stMipiAntSel3[2];			/*接收天线开关3 MIPI 参数*/
	LPHY_MIPIDEV_CMD_STRU 		stMipiAntSel0Tuner[2]; 		/*接收天线开关0 tunner MIPI 参数*/
	LPHY_MIPIDEV_CMD_STRU 		stMipiAntSel1Tuner[2];		/*接收天线开关1 tunner MIPI 参数*/
	LPHY_MIPIDEV_CMD_STRU 		stMipiAntSel2Tuner[2]; 		/*接收天线开关2 tunner MIPI 参数*/
	LPHY_MIPIDEV_CMD_STRU 		stMipiAntSel3Tuner[2];		/*接收天线开关3 tunner MIPI 参数*/

}NV_CA_UL_BAND_ANT_SWITCH;
typedef  struct
{
	/*UINT8                               ucUl2AntenaFlg;

	UINT8                               ucUl2AntenaFlg;
	UINT8                               ucRsv[3];*/
	/*本CA组合下本Band对应的下行RF FrontEnd通路的编号,  用于不同的CA组合切换时识
	    别本Band是否发生RFFE的切换,  对基带的处理包含时频同步、解调等有影响。
	    通路编号相同则认为通路不变*/
	//UINT32 								ulRfFeNum;

	/*上行CA配置UL2CC（注意上行只配了1CC的场景不使用本值）且其中一个Band 为TDD band场景下，
	    本CA组合下某个上行子帧只有一个Band  载波发送，则取本值作为整个CA组合的天线开关值*/
	/*NV_CA_UL_BAND_ANT_SWITCH            stCaUlBandAntCfg;*/

	UINT32 								ulUlBand;				/*band*/
	INT32 								lGainErrInd;
	UINT16								ulUlRfChIdx;/*前端单band RF通道配置参数2选1*/
	UINT16  		                                             ulFemPathIdx;
	NV_NCCA_UL_PRIVATE_PARA_STRU		stUlBandGpioMipiPara;
}NV_NCCA_UL_BAND_PARA_STRU;


/*多band 组合nv 结构，最多包括4 RX和2 TX，该结构V7R5 支持128种组合，128个NV项据使用以下结构*/
typedef struct
{
	UINT16  							usDlBandNum;			 /*NCCA DL Band Num*/
	UINT16                              usValidFlg;
	UINT32 								ulDlBandInd[4];    	 /*NCCA DL Band Num List,最多4个band*/
	NV_NCCA_DL_COMM_PARA_STRU 	        stNcCaDlCommPara;		 /*NCCA DL Band 公共参数*/
	NV_NCCA_DL_BAND_PARA_STRU           stNcCaDlBandPara[4];   /*NCCA DL 各Band  私有参数*/

	UINT16  						    usUlBandNum	;  			/*NCCA UL Band Num*/
	UINT16                              usRsv;
	UINT32  							ulUlBandInd[2] ;   		/*NCCA UL Band Num List 最多两个band*/
	NV_NCCA_UL_COMM_PARA_STRU	        stNcCaUlCommPara;		    /*NCCA UL Band 公共参数*/
	NV_NCCA_UL_BAND_PARA_STRU           stNcCaUlBandPara[2];	    /*NCCA UL 各Band  私有参数*/
}NV_BANDCOMB_FE_PARA_STRU;



/**********************************begin  多载波 begin***********************************/
typedef struct
{
    UINT32				*pNvAddr;           /*nv ddr地址*/
    LPHY_NV_BAND_STRU   	 stBand;              /*band号*/
    UINT8               			  ucValidFlg;         /*band nv 有效标记*/
    UINT8                                ucRxAntNum;
    UINT8            			ucTxAntNum;
}LRRC_LPHY_DDR_SINGLE_BAND_STRU;

/*PS根据该结构将单载波NV信息加载到DSP内存*/
typedef struct
{
    LRRC_LPHY_DDR_SINGLE_BAND_STRU stNvDdrInfo[BAND_NUM_MAX];  /*预留24组，总共使用18组*/
}LRRC_LPHY_FENV_SINGLE_BAND_DDR_INFO_STRU;


typedef struct
{
    LRRC_LPHY_BANDCOMB_STRU stBandComb;   /*Band组合信息*/

    UINT32                  *pNvAddr;     /*nv ddr地址*/
}LRRC_LPHY_DDR_BANDCOMB_STRU;

/*PS根据该结构将单载波NV信息加载到DSP内存*/

typedef struct
{
    LRRC_LPHY_DDR_BANDCOMB_STRU stNvDdrInfo[BANDCOMB_NUM_MAX];  /*CA最多支持128组*/
}LRRC_LPHY_FENV_BANDCOMB_DDR_INFO_STRU;



#define LPHY_FE_RF_INIT_NV_DDR_BASE         (BAND_MAILBOX_NV_IDX_BASE_ADDR)
#define LPHY_FE_BAND_NV_DDR_BASE             (LPHY_FE_RF_INIT_NV_DDR_BASE + sizeof(UCOM_NV_RF_INIT_CONFIG_NEW_RAM_STRU *))
#define LPHY_FE_BANDCOMB_NV_DDR_BASE    	 (LPHY_FE_BAND_NV_DDR_BASE + sizeof(LRRC_LPHY_FENV_SINGLE_BAND_DDR_INFO_STRU))
#define NV_BAND_FE_LSCANW_STRU_DDR_BASE      (LPHY_FE_BANDCOMB_NV_DDR_BASE + sizeof(LRRC_LPHY_FENV_BANDCOMB_DDR_INFO_STRU))



/********************************************V7R5 FE NV********************************************/





/*定义全局变量,供各个模块访问*/
extern LTE_NV_PARA_STRU  *gptrLteNvPara;



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __LTE_NV_PARA_H__ */
