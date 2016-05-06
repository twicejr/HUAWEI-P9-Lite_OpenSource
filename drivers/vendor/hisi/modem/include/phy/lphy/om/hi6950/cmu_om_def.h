/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : cmu_om_def.h
  版 本 号   : 初稿
  作    者   : w54192
  生成日期   : 2011年03月29日
  最近修改   :
  功能描述   : 定义公共测量模块OM需要上报的结构体,该文件最终会交付给HiStudio使用
  函数列表   :
  修改历史   :
  1.日    期   : 2011年03月29日
    作    者   : wukeshou(54192)
    修改内容   : 创建文件

******************************************************************************/

/************************************************************
                     包含其它模块的头文件
************************************************************/
#include "om_base_def.h"

/************************************************************
                               宏定义
************************************************************/
#define CMU_SB_MAX                 25

/************************************************************
                             数据结构定义
************************************************************/

/************************************************************
                             接口函数声明
 ************************************************************/

#ifndef __CMU_OM_DEF_H__
#define __CMU_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define CMU_RX_MAX_NUM         NUM_OF_RX_ANT
#define CMU_TX_MAX_NUM         NUM_OF_TX_ANT
#define NUM_FRAME_TYPE         4
#define NUM_OF_INTERP_CRS_RB   4
#define NUM_OF_CRS_RB          2
#define NUM_OF_TX_ANT          2
#define NUM_OF_RX_ANT          4
#define NUM_OF_IQPATH          2

#define NUM_OF_RS_SYMB         4
#define NUM_OF_RB              100
#define NUM_OF_RB_20M          100
#define NUM_OF_RB_15M          75
#define NUM_OF_RB_10M          50
#define NUM_OF_RB_5M           25
#define NUM_OF_RB_3M           15
#define NUM_OF_RB_1P4M         6

#define MAX_NUM_OF_SUBBAND_PN       25


/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
typedef enum __LPHY_REQ_MSGID_CMU__
{
    LPHY_REQ_CMU_REPORT_ENA            = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_REQ, 0x0),
	LPHY_DT_MEAS_INFO_REQ              = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_REQ, 0x100)
}LPHY_REQ_MSGID_CMU_ENUM;
typedef UINT16 LPHY_REQ_MSGID_CMU_ENUM_UINT16;
typedef enum
{
    CMU_OM_SWITCH_OFF = 0,
    CMU_OM_SWITCH_ON,
}CMU_OM_SWITCH_ENUM;
typedef UINT16 CMU_OM_SWITCH_ENUM_UINT16;
typedef struct
{
   CMU_OM_SWITCH_ENUM    enCmuSgReportEn;

}LPHY_REQ_CMU_SG_REPORT_ENA_STRU;

#if 0
/************************************************************
                           2. CNF数据结构定义
************************************************************/
typedef enum __LPHY_CNF_MSGID_CMU__
{
    LPHY_CNF_CMU_RESERVED            = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_CNF, 0x0),
    LPHY_CNF_CMU_ENA_ALG,              /*使能公共测量结果上报*/
    LPHY_CNF_CMU_ENA_CFG,              /*配置公共测量的算法开关*/
}LPHY_CNF_MSGID_CMU_ENUM;
typedef UINT16 LPHY_CNF_MSGID_CMU_ENUM_UINT16;

// REQ时返回的CNF结构
typedef struct _CMU_CNF_REQ
{
    LPHY_CNF_MSGID_CMU_ENUM_UINT16   usCnfType;  // 请求类型
    UINT16                           ulReaserve;
}CMU_CNF_STRU;

#endif
/************************************************************
                           3. Sg数据结构定义
************************************************************/
typedef enum
{
    LPHY_SG_CMU_PCC_REPORT_ENA         = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_SG, 0x0),
    LPHY_SG_CMU_SCC0_REPORT_ENA,
    LPHY_SG_CMU_SCC1_REPORT_ENA,
    LPHY_SG_CMU_SCC2_REPORT_ENA,
    LPHY_SG_CMU_CONIND_REPORT_ENA,
}LPHY_SG_CMU_ENUM;

typedef enum CMU_STATE
{
	CMU_IDLE = 0,
	CMU_DRX,
	CMU_HOLD,
	CMU_WAIT,
	CMU_CONFIG_BBP,
	CMU_CONFIG_FINISH,
	CMU_WORKING
}CMU_STATE_ENUM;
typedef UINT16 CMU_STATE_ENUM_UINT16;


typedef enum ALPHA_STATE
{
	ALPHA_INIT = 0,
	ALPHA_WORKING
}ALPHA_STATE_ENUM;
typedef UINT16 ALPHA_STATE_ENUM_UINT16;


typedef struct
{
    /*Do not change the order and the size of this structrue must be 160bit times*/
    INT16            asCmuSnr[NUM_FRAME_TYPE][CMU_RX_MAX_NUM];
	//INT16            asCmuServSnr[CMU_RX_MAX_NUM];
	UINT8            aucConnectionInd[CMU_TX_MAX_NUM*CMU_RX_MAX_NUM];

    UINT32           aulCmuServCrsRsrp[CMU_RX_MAX_NUM];
    //UINT32           aulCmuServNoisePower[CMU_RX_MAX_NUM];
    UINT32           aulCmuFinalNoisePower[NUM_FRAME_TYPE][CMU_RX_MAX_NUM];
	UINT32           aulCmuFinalPdcPn[NUM_FRAME_TYPE][CMU_RX_MAX_NUM];
	UINT32           aulCmuFinalPickPn[NUM_FRAME_TYPE][CMU_RX_MAX_NUM];
    //UINT32           aulCmuFinalSBPn[NUM_FRAME_TYPE*MAX_NUM_OF_SUBBAND_PN][CMU_RX_MAX_NUM];

    UINT32           aulChPowerTxRx[CMU_TX_MAX_NUM*CMU_RX_MAX_NUM];
    UINT32           aulNoisePowerTxRx[NUM_FRAME_TYPE][CMU_TX_MAX_NUM*CMU_RX_MAX_NUM];

	UINT32           ulConIndKalmanIndex;

	//UINT32           aulCmuRsrpConInd[CMU_TX_MAX_NUM*CMU_RX_MAX_NUM];//Filtered
	UINT32           aulCmuPhConInd[CMU_TX_MAX_NUM*CMU_RX_MAX_NUM];//Filtered
	UINT32           aulCmuPnConInd[CMU_TX_MAX_NUM*CMU_RX_MAX_NUM];//Filtered

	UINT32           aulAgcNoisePower[NUM_FRAME_TYPE][CMU_RX_MAX_NUM];

	INT16            asCmuCrsSinr[NUM_OF_RS_SYMB][CMU_TX_MAX_NUM];
	INT16            asCmuPbchSinr[CMU_TX_MAX_NUM];

	UINT32           ulCmuRSrpdBm[CMU_RX_MAX_NUM];

	INT16            sCmuOutRsrpdBm;

    UINT16           usCurrRlmFlag;

	UINT16           usCurrFramType;
	UINT16           usNextFramType;

}CMU_CALC_PARA_STRU;

typedef struct
{
    UINT32           aulCmuSdrPhRx[CMU_RX_MAX_NUM];// kalman input
    UINT32           aulCmuSdrPnRx[NUM_FRAME_TYPE][CMU_RX_MAX_NUM];// kalman input

	UINT32           aulCmuFilteredPhRx[CMU_RX_MAX_NUM];
    UINT32           aulCmuFilteredPnRx[NUM_FRAME_TYPE][CMU_RX_MAX_NUM];

    UINT32           ulPhPnKalmanIndex;
    UINT32           ulRsrpKalmanIndex;
    UINT32           ulNoiseKalmanIndex[NUM_FRAME_TYPE];

	//UINT32           aulCmuSdrSumSBPnRx[NUM_FRAME_TYPE*MAX_NUM_OF_SUBBAND_PN][CMU_RX_MAX_NUM];// kalman input
    UINT32           aulCmuFilteredSumSBPnRx[NUM_FRAME_TYPE*MAX_NUM_OF_SUBBAND_PN][CMU_RX_MAX_NUM];// kalman output
    UINT32           aulCmuFinalSBPn[NUM_FRAME_TYPE*MAX_NUM_OF_SUBBAND_PN][CMU_RX_MAX_NUM];

    //UINT32           aulCmuSdrSumPickPnRx[NUM_FRAME_TYPE][CMU_RX_MAX_NUM];// kalman input
    UINT32           aulCmuFilteredSumPickPnRx[NUM_FRAME_TYPE][CMU_RX_MAX_NUM];// kalman output
    UINT32           aulCmuSdrPdcPnRx[NUM_FRAME_TYPE][CMU_RX_MAX_NUM];
    UINT32           aulCmuFilteredPdcPnRx[NUM_FRAME_TYPE][CMU_RX_MAX_NUM];
	UINT32           ulPdcPnKalmanIndex[NUM_FRAME_TYPE];

    UINT32           ulSinrKalmanIndex;
    INT32            aulCmuFilteredSinrRx[CMU_RX_MAX_NUM];

	UINT32           aulCmuRsFilteredRsrp[NUM_OF_RS_SYMB][CMU_TX_MAX_NUM*CMU_RX_MAX_NUM];
	UINT32           aulCmuRsFilteredPn[NUM_OF_RS_SYMB][CMU_TX_MAX_NUM*CMU_RX_MAX_NUM];
	UINT32           aulRsPbchFilteredRsrp[CMU_TX_MAX_NUM*CMU_RX_MAX_NUM];
	UINT32           aulRsPbchFilteredPn[CMU_TX_MAX_NUM*CMU_RX_MAX_NUM];
	UINT32           ulCmuRsKalmanIndex;
	UINT32           ulRsPbchKalmanIndex;
	UINT32           ulRsReportPeriod;
	UINT32           ulRsPbchReportPeriod;

	INT16            asRsSinr[NUM_OF_RS_SYMB][CMU_TX_MAX_NUM*CMU_RX_MAX_NUM];
	INT16            asPbchSinr[CMU_TX_MAX_NUM*CMU_RX_MAX_NUM];

	ALPHA_STATE_ENUM_UINT16  enRsAlphaState;
	ALPHA_STATE_ENUM_UINT16  enPbchAlphaState;
	UINT8                    ucdBAlpha;
}CMU_CALC_PARA_KALMAN;

typedef struct
{
	CMU_CALC_PARA_STRU     stCmuCalcPara;
	UINT32                 ulTsPos;
	INT32                  lTsNum;
    UINT8                  aucRxChoose[NUM_OF_RX_ANT];
	UINT32 			       aulAgcGainRatio[NUM_OF_RX_ANT];
	UINT8                  ucNoiseAvailableFlag[NUM_FRAME_TYPE];
    INT16                  asAgcAdjFac[NUM_FRAME_TYPE][NUM_OF_RX_ANT];
	INT16                  asAgcGaindBSym[NUM_OF_RX_ANT];
	INT16                  asAgcGainFormerdBSym[NUM_OF_RX_ANT];
	CMU_STATE_ENUM_UINT16  enCmuState;
    CMU_STATE_ENUM_UINT16  enCmuLastState;
	UINT8                  ucResultValid;
    UINT8                  ucReserved[3];
}CMU_PARA_STRU;

typedef struct
{
	UINT32                 ulrsrp[NUM_OF_RX_ANT*NUM_OF_TX_ANT];
	UINT32                 ulPn[NUM_OF_RX_ANT*NUM_OF_TX_ANT];
	INT32                  lSnr[NUM_OF_RX_ANT*NUM_OF_TX_ANT];
}CMU_PARA_STRU_CONIND;

/************************************************************
                           3. Ind数据结构定义
************************************************************/
/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum __LPHY_TRACE_CMU_
{
    LPHY_TRACE_CMU_RESERVED              = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_TRACE, 0x0),
	LPHY_TRACE_CMU_STATE,                        // 跟踪CMU的状态
	LPHY_TRACE_CMU_CFG,                          // 跟踪CMU的配置过程
	LPHY_TRACE_CMU_RESULT,                       // 跟踪CMU的计算过程
	LPHY_TRACE_CMU_CELL,                         // 跟踪CMU的小区状况
	LPHY_TRACE_CMU_SFNUM,                        // 跟踪CMU的子帧号
}LPHY_TRACE_CMU_ENUM;
typedef UINT16 LPHY_TRACE_CMU_ENUM_UINT16;


typedef struct
{
    UINT32      ulLineNum;
    UINT32      ulCmuState;
}LPHY_TRACE_CMU_STATE_STRU;

typedef struct
{
    UINT32      ulLineNum;
    UINT32      ulCmuCell;
}LPHY_TRACE_CMU_CELL_STRU;
typedef enum
{
    CMU_CFG_IDLE = 0,
    CMU_CFG_WAIT,
    CMU_CFG_UPLINK,
    CMU_CFG_MAXTAU,
    CMU_CFG_ALL,
    CMU_CFG_SERVCELL,
    CMU_CFG_ONLYTAU,
}CMU_CONFIG_ENUM;

typedef struct
{
    CMU_CONFIG_ENUM      enCmuCfg;
}LPHY_TRACE_CMU_CFG_STRU;

typedef struct
{
    UINT32      ulLineNum;
    UINT32      ulCmuResult;
}LPHY_TRACE_CMU_RESULT_STRU;

typedef struct
{
    UINT32      ulLineNum;
    UINT32      ulCmuSFNum;
}LPHY_TRACE_CMU_SFNUM_STRU;


/************************************************************
                           5. ERROR数据结构定义
************************************************************/
typedef enum __LPHY_ERROR_CMU_ENUM__
{
    /*PBCH, ERROR ID 1 - 15*/
    LPHY_ERROR_CMU_LOG_ERROR              = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_ERROR, 0x1),
    LPHY_ERROR_CMU_EXP_ERROR,
    LPHY_ERROR_CMU_DMA_ERROR
}LPHY_ERROR_CMU_ENUM;
typedef UINT16 LPHY_ERROR_CMU_ENUM_UINT16;

typedef struct
{
    UINT32      ulErrorType;
    INT32       lErrorValue;
}LPHY_TRACE_CMU_ERROR_STRU;



/************************************************************
                           6. DEBUG数据结构定义
************************************************************/
typedef enum __LPHY_DEBUG_CMU_ENUM__
{
    LPHY_DEBUG_CMU_RESERVED                         = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_DEBUG, 0x0),
    LPHY_DEBUG_CMU_LOGIC_REG,
    LPHY_DEBUG_CMU_BUFFER_VALUE,
    LPHY_DEBUG_CMU_CURRCAL_VALUE,
}LPHY_DEBUG_CMU_ENUM;
typedef UINT16 LPHY_DEBUG_CMU_ENUM_UINT16;

typedef struct
{
    UINT8 ccValidFlag;
    UINT8 ccIdx;
    UINT16 rsv;
    LTE_CP_TYPE_ENUM_UINT16 enCpType;
    INT16  sCRS_SinrR0;
    INT16  sCRS_SinrR1;
    INT16 sCRS_AvgSinr;
    //INT16  sDRS_AvgSinr;
    INT32  lCRS_Rsrq;
    INT32  lCRS_RsrpR0;
    INT32  lCRS_RsrpR1;
    INT32  lDRSRsrpR0;
    INT32  lDRSRsrpR1;
    INT32  lDRSRsrpR2;
    INT32  lDRSRsrpR3;
    INT32  lCRS_RssiR0;
    INT32  lCRS_RssiR1;
    INT16  sDRSSnrP5P7Rx0;
    INT16  sDRSSnrP5P7Rx1;
    INT16  sDRSSnrP5P7Rx2;
    INT16  sDRSSnrP5P7Rx3;

    INT16  sDRSSnrP8Rx0;
    INT16  sDRSSnrP8Rx1;
    INT16  sDRSSnrP8Rx2;
    INT16  sDRSSnrP8Rx3;

    INT16  sDRSSnrP9Rx0;
    INT16  sDRSSnrP9Rx1;
    INT16  sDRSSnrP9Rx2;
    INT16  sDRSSnrP9Rx3;

    INT16  sDRSSnrP10Rx0;
    INT16  sDRSSnrP10Rx1;
    INT16  sDRSSnrP10Rx2;
    INT16  sDRSSnrP10Rx3;

} LPHY_MEAS_INFO_SINGLE_CC_IND_STRU;

typedef struct
{
    LPHY_MEAS_INFO_SINGLE_CC_IND_STRU gastMeasInfoInd[4];
} LPHY_DT_MEAS_INFO_IND_STRU;



/*BEGIN: by humin, 2015/05/28*/
#if 1
typedef struct __DT_MEAS_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   usEna;
    UINT16   usReportPeriod;
} LPHY_DT_MEAS_INFO_REQ_STRU;
#endif
/*END: by humin, 2015/05/28*/
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CMU_OM_DEF_H__ */
