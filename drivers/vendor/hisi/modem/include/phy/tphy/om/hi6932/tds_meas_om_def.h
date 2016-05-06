/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : Tds_meas_om_def.h
  Description     : Tds_meas_om_def.h header file
  History         :
      1.x58160       2013-3-19   Draft Enact

******************************************************************************/

#ifndef __TDS_MEAS_OM_DEF_H__
#define __TDS_MEAS_OM_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include  "type_define.h"
#include  "tds_measspecdef.h"
#include  "tds_measreturnrslt.h"
#include  "om_interface.h"
#include  "om_base_def.h"




/*
#pragma pack(4)
*/
/*****************************************************************************
  2 Macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 枚举名    : TDS_MEAS_FILE_ID_ENUM_UINT32
 协议表格  :
 枚举说明  : TDS测量模块的c文件ID定义
*****************************************************************************/
enum TDS_MEAS_FILE_ID_ENUM
{
    TDS_MEAS_GLOBAL_FILE        = 0,
    TDS_MEAS_COMM_FILE,
    TDS_MEAS_TIMER_FILE,
    TDS_MEAS_OM_FILE,
    TDS_MEAS_ICS_TASK_FILE,
    TDS_MEAS_IDLE_TASK_FILE,    //5,
    TDS_MEAS_ACC_TASK_FILE,
    TDS_MEAS_DCH_TASK_FILE,
    TDS_MEAS_CTU_TASK_FILE,
    TDS_MEAS_INTERFACE_FILE,    //9
    TDS_MEAS_CTU_FILE,
    TDS_MEAS_OM_STUB_FILE,
    TDS_MEAS_IRAT_TASK_FILE,
    TDS_MEAS_CONN_IRAT_FILE,
    TDS_MEAS_PERIOD_SRCH_FILE,
    TDS_MEAS_DSDS_FILE,
    /* 可增加其他的文件*/

    TDS_MEAS_FILE_ID_BUTT
};
typedef UINT32 TDS_MEAS_FILE_ID_ENUM_UINT32;


/*****************************************************************************
 枚举名    : TDS_MEAS_OM_RPT_IND_ENUM
 协议表格  :
 枚举说明  : TDS测量模块的IND 消息ID定义
*****************************************************************************/
enum TDS_MEAS_OM_RPT_IND_ENUM
{
    TPHY_MEAS_ERR_IND     =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x0),
    TPHY_MEAS_RIS_IND     =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x1),
    TPHY_MEAS_ISCP_IND    =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x2),
    TPHY_MEAS_RSSI_IND    =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x3),
    TPHY_MEAS_PULSE_PWR_IND =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x4),
    TPHY_MEAS_PULSE_IND     =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x5),
    TPHY_MEAS_TIMER_IND   = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x6),
    TPHY_MEAS_STATE_IND   = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x7),
    TPHY_MEAS_FREQ_CELL_LIST_IND = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x8),
    TPHY_MEAS_TIME_DOMAIN_PWR_IND = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x9),
    TPHY_MEAS_CIR_IND     =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0xA),
    TPHY_MEAS_M_IND       =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0xB),
    TPHY_MEAS_SR_IND      =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0xC),
    TPHY_MEAS_OM_ENERGY_IND  =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0xD),
    TPHY_MEAS_OM_NOISE_PWR_IND  =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0xE),
    TPHY_MEAS_BEST_SORT_CELL_IND  =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0xF),
    TPHY_MEAS_BEST_CELL_FROM_CHE  =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x10),
    TPHY_MEAS_BEST_CELL_LIST_TO_CHE  =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x11),
    TPHY_MEAS_DATA_RCV_CFG_IND  =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x12),
    TPHY_MEAS_CONN_IRAT_GATH_SLOT_IND  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x13),
    TPHY_MEAS_CONN_IRAT_BUILD_CMD_IND  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x14),
    TPHY_MEAS_CONN_IRAT_DISCARD_CMD_IND  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x15),
    TPHY_MEAS_CONN_IRAT_SND_PRE_INT0_IND  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x16),
    TPHY_MEAS_CONN_IRAT_INT1_START_IND  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x17),
    TPHY_MEAS_CONN_IRAT_INT2_END_IND  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x18),
    TPHY_MEAS_IDLE_PRE_INT0  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x19),
    TPHY_MEAS_IDLE_INT1  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x1A),
    TPHY_MEAS_IDLE_INT2  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x1B),
    TPHY_MEAS_RCV_INT3  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x1C),
    TPHY_MEAS_SND_INT4  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x1D),
    TPHY_MEAS_SND_INT5  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x1E),
    TPHY_MEAS_SND_IMM_INT2  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x1F),
    TPHY_MEAS_PERIOD_SRCH_NEW_CELL_IND  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x20),
    TPHY_MEAS_PERIOD_SRCH_CALC_IND  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x21),

    TPHY_MEAS_IRAT_RCV_INT0  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x30),
    TPHY_MEAS_IRAT_RCV_INT1  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x31),
    TPHY_MEAS_IRAT_RCV_INT2  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x32),
    TPHY_MEAS_IRAT_SND_INT3  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x33),
    TPHY_MEAS_IRAT_RCV_INT4  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x34),
    TPHY_MEAS_IRAT_RCV_INT5  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x35),
    TPHY_MEAS_IRAT_RCV_INT6  = OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x36),
	TPHY_MEAS_INFO_IND       =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_IND, 0x40)
};
/*****************************************************************************
 枚举名    : TDS_MEAS_OM_REQ_ENUM
 协议表格  :
 枚举说明  : TDS测量模块的OM REQUEST 消息ID定义
*****************************************************************************/
enum TDS_MEAS_OM_REQ_ENUM
{
    TPHY_MEAS_OM_SWTICH_REQ =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_REQ, 0x0),
    TPHY_MEAS_TIMER_SWTICH_REQ =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_REQ, 0x1),
    TPHY_MEAS_STATE_SWTICH_REQ =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_REQ, 0x2),
    TDS_MEAS_FREQ_CELL_REQ =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_REQ, 0x3)
};

/*****************************************************************************
 枚举名    : TDS_MEAS_OM_CNF_ENUM
 协议表格  :
 枚举说明  : TDS测量模块的OM CONFIRM 消息ID定义
*****************************************************************************/
enum TDS_MEAS_OM_CNF_ENUM
{
    /*TPHY_MEAS_OM_SWTICH_CNF =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_CNF, 0x0),
    TPHY_MEAS_TIMER_SWTICH_CNF =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_CNF, 0x1)*/
    TPHY_MEAS_OM_SWTICH_CNF =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_REQ, 0x0),
    TPHY_MEAS_TIMER_SWTICH_CNF =  OM_TCMD_ID(TPHY_MEAS_MID, OM_TYPE_REQ, 0x1)
};

/*****************************************************************************
 枚举名    :
 协议表格  :
 枚举说明  :
*****************************************************************************/
enum TDS_MEAS_ISCP_TYPE_ENUM
{
    TDS_MEAS_ISCP_TYPE_1        = 0,
    TDS_MEAS_ISCP_TYPE_2,
    TDS_MEAS_ISCP_TYPE_BUTT
};
typedef UINT16 TDS_MEAS_ISCP_TYPE_ENUM_UINT16;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : TDS_MEAS_OM_ERR_IND_STRU
 协议表格  :
 结构说明  : 运行中出错的信息上报，用来代替printf打印的字符串
*****************************************************************************/
typedef struct TDS_MEAS_OM_ERR_IND
{
    TDS_MEAS_FILE_ID_ENUM_UINT32        uLFileId;   /*错误所在的文件ID*/
    UINT32                              ulLineNo;   /*错误所在的文件行号*/
    TDS_MEAS_ERR_CODE_ENUM_UINT32       ulErrCode;  /*错误类型*/
    OM_REPORT_LEVEL_ENUM_UINT32         ulErrLvl;   /*错误等级*/
    UINT32                              ulParaNum;
    UINT32                              ulPara1;
    UINT32                              ulPara2;
    UINT32                              ulPara3;
}TDS_MEAS_OM_ERR_IND_STRU;

/*****************************************************************************
 结构名    : TDS_MEAS_OM_REQ_STRU
 协议表格  :
 结构说明  : om的开关设置时参数
*****************************************************************************/
typedef struct TDS_MEAS_OM_SWITCH_REQ
{
    UINT16                usTdsMeasOmErrSwitch;   /*om error信息上报的开关是否打开*/
    UINT16                usTdsMeasOmDataSwitch;  /*om 采数信息上报的开关是否打开*/
    UINT8                 ucTdsMeasSgSwitch;
    UINT8                 aucRsv[3];
}TDS_MEAS_OM_SWITCH_REQ_STRU;

/*****************************************************************************
 结构名    : TDS_MEAS_OM_SWITCH_CNF_STRU
 协议表格  :
 结构说明  : om的开关设置的confirm
*****************************************************************************/
typedef struct TDS_MEAS_OM_SWITCH_CNF
{
    TDS_MEAS_ERR_CODE_ENUM_UINT32       ulRslt;
}TDS_MEAS_OM_SWITCH_CNF_STRU;
/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usSwitch;       /*0:关闭，1:启动*/
    //TDS_MEAS_TIMER_MODE_ENUM_UINT16     usTimerType;    /*仅启动时使用*/
    UINT16     			                usTimerType;
    UINT32                              ulTimerLen;     /*仅启动时使用*/
    UINT32                              ulPara;         /*仅启动时使用*/
    //TDS_MEAS_HTIMER                     pHdl;           /*仅停止 时使用*/
    UINT32                           *pHdl;           /*仅停止 时使用*/
}TDS_MEAS_TIMER_SWITCH_REQ_STRU;

/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
//typedef struct
//{
//    TDS_MEAS_HTIMER                     pHdl;           /*仅停止时使用,返回启动定时器的句柄。如果为空，表示启动失败*/
//    UINT16                              usRsv;
//}TDS_MEAS_TIMER_SWITCH_CNF_STRU;

/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT32                              ulState;
}TDS_MEAS_STATE_SWITCH_REQ_STRU;

/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              ausCellId[TDS_MEAS_MAX_CELL_PER_FREQ];
}TDS_MEAS_CELLID_LIST_STRU;

/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    //TDS_MEAS_STATE_ENUM_UINT16          usMeasState;
    UINT16                              usMeasState;
    UINT16                              usFreqNum;
    UINT16                              ausFreq[TDS_MEAS_MAX_FREQ];
    UINT16                              ausFreqCellNum[TDS_MEAS_MAX_FREQ];
    TDS_MEAS_CELLID_LIST_STRU           astCellList[TDS_MEAS_MAX_FREQ];
}TDS_MEAS_FREQ_CELL_REQ_STRU;

/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    INT16  asChanpulse[TDS_MEAS_MAX_PULSE_ARRAY_LEN];
}TDS_MEAS_PULSE_IND_STRU;


/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT32  aulChanpulsePwr[TDS_MEAS_MAX_PULSE_ARRAY_LEN];
}TDS_MEAS_PULSE_PWR_IND_STRU;

/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usFreq;
    UINT16                              usCellId;
    INT16                               sIscp;
    UINT16                              usIscpLvl;
    UINT16                              usMaxIndex;
    TDS_MEAS_ISCP_TYPE_ENUM_UINT16      usIscptype;
    UINT32                              ulThr;
}TDS_MEAS_OM_ISCP_IND_STRU;
/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usCellMidId;
    UINT16                              usCellIndex;

    UINT16                              usK;
    UINT16                              usMO;
    UINT16                              usOffset;
    UINT16                              usMsn;
    INT16                               sAgcGain;
    INT16                               sAgcAdjust;
    UINT16                              usSsFlag;      /*是否测试ss*/
    /*-------输出-------*/
    INT16                               sRscp;          /*RSCP最后的值，单位dbm， -116 ~-25*/
    UINT16                              usRscpLevel;    /*RSCP[i]+116最后的值，单位dbm， 0 ~91*/
    INT16                               sSs;
    UINT32                              ulRscpPwr;      /*能量 0 ~0x7FFFFFFF*/
    UINT32                              ulScale;
    INT32                               lRscpScale;     /*(sRscp)*ulScale的加权的值*/
}TDS_MEAS_OM_RIS_IND_STRU;
/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usFreq;
    UINT16                              usFreqIndex;

    INT16                               sGainAjust;
    INT16                               sAgc;

    /*实际的rssi范围是 -100 ~ -25 db*/
    UINT16                              usReserve;
    INT16                               sRssi;
    UINT32                              ulRssiPwr;
}TDS_MEAS_OM_RSSI_IND_STRU;

/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    INT16                               asCirpulse[TDS_MEAS_BASE_MIDAMBLE_I_Q_NUM];
}TDS_MEAS_CIR_IND_STRU;
/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    INT16                               asM[TDS_MEAS_BASE_MIDAMBLE_I_Q_NUM];
}TDS_MEAS_M_IND_STRU;
/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    INT16                               asSr[TDS_MEAS_BASE_MIDAMBLE_I_Q_NUM];
}TDS_MEAS_SR_IND_STRU;

/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usFreq;
    UINT16                              usCellMid;
    INT16                               sRscp;
    INT16                               sIscp;
    INT16                               sSs;
    UINT16                              usRsv;
}TDS_MEAS_CELL_ENERGY_STRU;
/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usFreqNum;
    UINT16                              ausFreq[TDS_MEAS_MAX_FREQ];
    INT16                               asRssi[TDS_MEAS_MAX_FREQ];
    UINT16                              usCellNum;
    TDS_MEAS_CELL_ENERGY_STRU           astCellEnergy[TDS_MEAS_MAX_CELL];

    UINT16                              usMastFreq;
    UINT16                              usServFreq;
    UINT16                              usServCell;
    UINT16                              usBestNum;
    TDS_MEAS_CELL_ENERGY_STRU           astBestCell[TDS_MEAS_BEST_CELL_NUM];
}TDS_MEAS_OM_ENERGY_IND_STRU;
/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT32                              ulNoisePwr;
    UINT32                              ulScale;
}TDS_MEAS_OM_NOISE_PWR_IND_STRU;
/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usFreq;
    UINT16                              usBestCellNum;

    /*测量本地按照能量高低排序的小区*/
    UINT16                              ausSortCellMid[TDS_MEAS_BEST_CELL_NUM];
}TDS_MEAS_BEST_SORT_CELL_IND_STRU;

/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usFreq;
    UINT16                              usBestCellNum;

    /*测量按照能量高低排序的小区,但是，服务小在第一个位置的*/
    UINT16                              ausBestCellMid[TDS_MEAS_BEST_CELL_NUM];
}TDS_MEAS_BEST_CELL_LIST_TO_CHE_STRU;

/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usRsv;
    UINT16                              usBestCellMid;
}TDS_MEAS_BEST_CELL_FROM_CHE_STRU;

/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usFreq;
    UINT16                              usFourthFastFlg;
    INT32                               lRfStartTime;
    INT32                               lRfEndTime;  //RF生效时长，单位chip
}TDS_MEAS_OM_DATA_RCV_CFG_IND_STRU;
/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usCurSubFrm;
    UINT16                              usCurSchSlot;

    UINT16                              usCfgSubFrm;
    UINT16                              usSlotRedirect;
    UINT16                              usSlotBit;
    UINT16                              usRxSlotType;

    UINT16                              usSubFrmInfoWrtIdx;
    UINT16                              usSubFrmInfoRdIdx;
}TDS_MEAS_CONN_IRAT_GATH_SLOT_IND_STRU;

/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usActType;

    UINT16                              usSubFrm;
    UINT16                              usSlot;         /*occasion开始的slot或最后的一个slot*/
    UINT16                              usOccaLenInSlot;
    UINT16                              usSchSlotNum;  /*occasion动作调度的schedule slot*/
    UINT16                              usSlaveMode;

    UINT16                              usCmdFifoRdIndx;
    UINT16                              usCmdFifoWrtIndx;

    UINT16                              usTxSlotNum;
    UINT16                              usRxSlotNum;

    UINT32                              ulActChipTime;
}TDS_MEAS_CONN_IRAT_BUILD_CMD_IND_STRU;

/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usCurrSubFrm;
    UINT16                              usCurrSchSlot;

    UINT16                              usActType;

    UINT16                              usSubFrm;
    UINT16                              usSlot;         /*occasion开始的slot或最后的一个slot*/
    UINT16                              usOccaLenInSlot;
    UINT16                              usSchSlotNum;  /*occasion动作调度的schedule slot*/
    UINT16                              usSlaveMode;

    UINT16                              usCmdFifoRdIndx;
    UINT16                              usCmdFifoWrtIndx;
}TDS_MEAS_CONN_IRAT_DISCARD_CMD_IND_STRU;
/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usCurrSubFrm;
    UINT16                              usCurrSchSlot;

    UINT16                              usRsv;
    UINT16                              usSlaveMode;

    UINT32                              ulActChipTime;
}TDS_MEAS_CONN_IRAT_SND_PRE_INT0_IND_STRU;
/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usCurrSubFrm;
    UINT16                              usCurrSchSlot;

    UINT16                              usActType;

    UINT16                              usSubFrm;
    UINT16                              usSlot;         /*occasion开始的slot或最后的一个slot*/
    UINT16                              usOccaLenInSlot;
    UINT16                              usSchSlotNum;  /*occasion动作调度的schedule slot*/
    UINT16                              usSlaveMode;

    UINT16                              usCmdFifoRdIndx;
    UINT16                              usCmdFifoWrtIndx;

    UINT32                              ulActChipTime;
}TDS_MEAS_CONN_IRAT_SND_INT1_2_IND_STRU;

/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usCurrSubFrm;
    UINT16                              usCurrSlot;

    UINT16                              usMeasState;
    UINT16                              usTargetIratMode;

    TDS_MEAS_FILE_ID_ENUM_UINT32        uLFileId;   /*错误所在的文件ID*/
    UINT32                              ulLineNo;   /*错误所在的文件行号*/
}TDS_MEAS_SND_CTU_OM_COMM_IND_STRU;

/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usCurrSubFrm;
    UINT16                              usCurrSlot;

    UINT16                              usSrcIratMode;
    UINT16                              usRsv;
    TDS_MEAS_FILE_ID_ENUM_UINT32        uLFileId;   /*错误所在的文件ID*/
    UINT32                              ulLineNo;   /*错误所在的文件行号*/
}TDS_MEAS_OM_RCV_CTU_IND_STRU;

/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usFreqIndex;
    UINT16                              usFreq;

    /*本次cs模块输入的小区*/
    UINT8                               ucInputNum;
    UINT8                               aucInputMidId[TDS_MEAS_CS_SYNC_CELL_NUM];

    /*从本次cs输入的小区中找出的新detect 小区*/
    UINT8                               ucNewDetectNum;
    UINT8                               aucNewDetMidId[TDS_MEAS_CS_SYNC_CELL_NUM];

    /*上次存储的所有dectect小区*/
    UINT8                               ucOldDetectNum;
    UINT8                               aucOldDetMidId[TDS_MEAS_CS_SYNC_CELL_NUM];

    /*根据本次识别的新dectect小区，综合后的所有的dectect小区*/
    UINT8                               ucCurrDetectNum;
    UINT8                               aucCurrDetMidId[TDS_MEAS_CS_SYNC_CELL_NUM];
    UINT8                               aucCellInvalid[TDS_MEAS_CS_SYNC_CELL_NUM];
}TDS_MEAS_OM_PERIOD_SRCH_NEW_CELL_IND_STRU;
/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT16                              usFreqIndex;
    UINT16                              usFreq;

    /*计算完能量后，存储的所有dectect小区*/
    UINT8                               ucOldDetectNum;
    UINT8                               aucOldDetMidId[TDS_MEAS_CS_SYNC_CELL_NUM];
    UINT8                               aucOldInvalid[TDS_MEAS_CS_SYNC_CELL_NUM];

    /*根据可信度删除小区后，综合后的所有的dectect小区*/
    UINT8                               ucCurrDetectNum;
    UINT8                               aucCurrDetMidId[TDS_MEAS_CS_SYNC_CELL_NUM];
    UINT8                               aucCurrInvalid[TDS_MEAS_CS_SYNC_CELL_NUM];
    UINT8                               aucRsv[2];
}TDS_MEAS_OM_PERIOD_SRCH_CALC_IND_STRU;


/*****************************************************************************
 结构名    :
 协议表格  :
 结构说明  :
*****************************************************************************/


/*****************************************************************************
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









/*
#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif
*/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of Tds_meas_om_def.h */
