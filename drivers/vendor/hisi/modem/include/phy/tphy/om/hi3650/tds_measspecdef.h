/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : Tds_MeasSpecDef.h
  Description     : Tds_MeasSpecDef.h header file
  History         :
      1.x58160       2013-5-16   Draft Enact

******************************************************************************/

#ifndef __TDS_MEASSPECDEF_H__
#define __TDS_MEASSPECDEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "product_config.h"
#include "TPsTPhyInterface.h"

/*#pragma pack(4)*/


/*****************************************************************************
  2 Macro
*****************************************************************************/

/*本频测量的最大小区个数*/
#define TDS_MEAS_MAX_INTRA_FREQ_CELL    32

/*最大测量的异频小区个数总和:8 个异频下的小区个数总和不超32*/
#define TDS_MEAS_MAX_INTER_FREQ_CELL    32

/* 每个频率下小区个数最大值:8 个异频+1个本频，每个频率下的小区个数最大不超32*/
#define TDS_MEAS_MAX_CELL_PER_FREQ      32


/*BEGIN: by humin, 2015/05/07*/
/*最大测量的小区个数总和:同频和异频的小区个数总和*/
#define TDS_MEAS_MAX_CELL               (64) //mark
#if    (TDS_MEAS_MAX_CELL !=  maxCellNum)
    #error "(TDS_MEAS_MAX_CELL !=  maxCellNum)"
#endif
/*END: by humin, 2015/05/07*/
/*最大测量的异频率个数*/
#define TDS_MEAS_MAX_INTER_FREQ         23

/*BEGIN: by humin, 2015/05/07*/
/*最大测量的频率个数:1本频 + 8个异频*/
#define TDS_MEAS_MAX_FREQ               (24)
#if    (TDS_MEAS_MAX_FREQ !=  ((TDS_MEAS_MAX_INTER_FREQ) + 1))
    #error "(TDS_MEAS_MAX_FREQ !=  ((TDS_MEAS_MAX_INTER_FREQ) + 1))"
#endif
/*END: by humin, 2015/05/07*/

/*最大测量的传输个数:6*/
#define TDS_MEAS_MAX_TRCH               (maxTrCH)

/*最大测量的上行时隙个数*/
#define TDS_MEAS_MAX_TX_TS_NUM          (maxTS_1)

/*最大测量的时隙个数:包括上行和下行*/
#define TDS_MEAS_MAX_TS_NUM          (7)

/*最大midamble的个数，后续统一替代*/
#define TDS_MEAS_BASE_MIDAMBLE_MAX_NUM      128

/*#define TDS_MEAS_MAX_PULSE_ARRAY_LEN        ((TDS_MEAS_BASE_MIDAMBLE_MAX_NUM) * 2)*/
#define TDS_MEAS_MAX_PULSE_ARRAY_LEN        (256)

/*base midamble的i、q冲击的总和个数:TDS_MEAS_BASE_MIDAMBLE_MAX_NUM*2*/
#define TDS_MEAS_BASE_MIDAMBLE_I_Q_NUM      (256)

/*rscp的最大线性值*/
#define TDS_MEAS_MAX_RSCP_PWR       0x7FFFFFFF

//#define TDS_MEAS_MAX_ISCP_PWR      0x7FFFFFFF


/*rscp的最大DB值*/
#define TDS_MEAS_MAX_RSCP_DB        (-25)

/*rscp的最小DB值*/
#define TDS_MEAS_MIN_RSCP_DB        (-116)

/*rscp level的最大DB值*/
#define TDS_MEAS_MAX_RSCP_LVL        (91)

/*rscp level的最小DB值*/
#define TDS_MEAS_MIN_RSCP_LVL        (0)


/*rssi的最大DB值*/
#define TDS_MEAS_MAX_RSSI_DB        (-25)

/*rssi的最小DB值*/
#define TDS_MEAS_MIN_RSSI_DB        (-100)

/*rssi level的最大DB值*/
#define TDS_MEAS_MAX_RSSI_LVL        (76)

/*rssi level的最小DB值*/
#define TDS_MEAS_MIN_RSSI_LVL        (0)

/*SCALE的最小可信门限值*/
#define TDS_MEAS_SCALE_VALID_THRES   (12)


/*每个频点最大的detect小区个数*/
#define TDS_MEAS_CS_SYNC_CELL_NUM     12

/*所有频点最大允许的detected小区个数总和*/
#define TDS_MEAS_DETECT_CELL_MAX_NUM   144

/*给信道估计的最好小区的最大个数*/
#define TDS_MEAS_BEST_CELL_NUM          6

/*所有频点排列出的最好小区个数*/
//#define TDS_MEAS_ALL_FREQ_BEST_CELL_MAX_NUM 6

#define TDS_MEAS_REBUILD_CELL_MAX_NUM       2

#define TDS_MEAS_AFC_CELL_MAX_NUM       4

//#define TDS_MEAS_OM_BEST_CELL_NUM       (TDS_MEAS_BEST_CELL_NUM)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
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

#endif /* end of Tds_MeasSpecDef.h */
