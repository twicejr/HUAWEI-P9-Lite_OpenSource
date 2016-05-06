/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : emu_om_def.h
  版 本 号   : 初稿
  作    者   : w54192
  生成日期   : 2011年03月29日
  最近修改   :
  功能描述   : 定义能量测量模块OM需要上报的结构体,该文件最终会交付给HiStudio使用
  函数列表   :
  修改历史   :
--------------------------------------------------------------------------------
1.日    期   : 2011年03月29日
  作    者   : wukeshou(54192)
  修改内容   : 创建文件
--------------------------------------------------------------------------------
2.日    期 : 2011年06月11日
作    者 : wukeshou
修改内容 : DTS2011061100029

******************************************************************************/

/************************************************************
                     包含其它模块的头文件
************************************************************/
#ifndef __EMU_OM_DEF_H__
#define __EMU_OM_DEF_H__

#include "om_base_def.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************
                               宏定义
************************************************************/
#define EMU_FREQ_NUM                 (11) /*EMU_MAX_LIST_NUM宏需要对应EMU_MAX_LIST_NUM*/
#define EMU_CELL_NUM                 (32) /*大小和EMU_CELL_BUF_SIZE对应*/

/************************************************************
                             数据结构定义
************************************************************/


/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
typedef enum
{
	LPHY_REQ_EMU_EN_CLOSE = 0,
	LPHY_REQ_EMU_EN_OPEN
} LPHY_EMU_REQ_ENABLE_ENUM;

typedef  UINT16  LPHY_EMU_REQ_ENABLE_ENUM_UINT16;


typedef enum __LPHY_REQ_EMU__
{
    LPHY_REQ_EMU_SG_EN            = OM_CMD_ID(LPHY_EMU_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_EMU_SG_SERVE_EN,
    LPHY_REQ_EMU_SDR_PRINT_EN,
    LPHY_REQ_EMU_LIST_PRINT_EN,
    LPHY_REQ_EMU_ALARM_STAT_EN
}LPHY_REQ_MSGID_EMU_ENUM;
typedef UINT16 LPHY_REQ_MSGID_EMU_ENUM_UINT16;

typedef struct
{
    LPHY_EMU_REQ_ENABLE_ENUM_UINT16    usEmuSGEn;          /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
    UINT16                             usFreqReportNum[EMU_FREQ_NUM];
} LPHY_REQ_EMU_SG_EN_STRU;

typedef struct
{
    LPHY_EMU_REQ_ENABLE_ENUM_UINT16    usEmuSGServeEn;     /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_EMU_SG_SERVE_EN_STRU;

typedef struct
{
    LPHY_EMU_REQ_ENABLE_ENUM_UINT16    usSdrPrintEn;     /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_EMU_SG_SDR_PRINT_EN_STRU;

typedef struct
{
    LPHY_EMU_REQ_ENABLE_ENUM_UINT16    usListPrintEn;     /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_EMU_SG_LIST_PRINT_EN_STRU;

typedef  struct
{
	LPHY_EMU_REQ_ENABLE_ENUM_UINT16    usEmuStatEn;
	UINT16                             usRsv;
	UINT16                             usFreq;
	UINT16                             usCellNum;
	UINT16                             usCellList[8];
}LPHY_REQ_EMU_ALARM_STAT_EN_STRU;


/*old**/

// 算法数据结构
typedef struct _EMU_ALG_RESULT_REQ
{
    LPHY_EMU_REQ_ENABLE_ENUM_UINT16   usReqType;          /*1 使能上报, 0关闭上报*/
    UINT16                            rsv;
    UINT16                            usFreqReportNum[EMU_FREQ_NUM];  // 频点小区上报数量
}EMU_ALG_RESULT_REQ_STRU;


/************************************************************
                           3. sg数据结构定义
************************************************************/




/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum
{
    LPHY_TRACE_EMU_CONN_INTRA_EVT              = OM_CMD_ID(LPHY_EMU_MID, OM_TYPE_TRACE, 0x0),
    LPHY_TRACE_EMU_CONN_INTER_EVT,
    LPHY_TRACE_EMU_CONN_GSM_EVT,
    LPHY_TRACE_EMU_CONN_WCDMA_EVT,
    LPHY_TRACE_EMU_IDLE_INTRA_EVT,
    LPHY_TRACE_EMU_IDLE_INTER_EVT,
    LPHY_TRACE_EMU_IDLE_GSM_EVT,
    LPHY_TRACE_EMU_IDLE_WCDMA_EVT,
    LPHY_TRACE_EMU_IDLE_TASK_UPDT_EVT,
    LPHY_TRACE_EMU_CS_ITO_UPDT_EVT,
    LPHY_TRACE_EMU_CS_FINISH_EVT,
    LPHY_TRACE_EMU_IDLE_SETUP_EVT,
    LPHY_TRACE_EMU_IDLE_RELEASE_EVT,
    LPHY_TRACE_EMU_CONN_SETUP_EVT,
    LPHY_TRACE_EMU_CONN_RELEASE_EVT,
	LPHY_TRACE_EMU_HOLD_EVT,
	LPHY_TRACE_EMU_UNHOLD_EVT,
	LPHY_TRACE_EMU_SLAVE_DONE_EVT,
	LPHY_TRACE_EMU_BSIC_REQ_EVT,
	LPHY_TRACE_EMU_ITAT_DONE_EVT,
	LPHY_TRACE_EMU_L_INTER_SHIFT_EVT,
	LPHY_TRACE_EMU_W_FREQ_SHIFT_EVT,
	LPHY_TRACE_EMU_TASK_STOP_EVT,
	LPHY_TRACE_EMU_SERV_LOST_EVT,
	LPHY_TRACE_EMU_PAR_LOW_EVT,
	LPHY_TRACE_EMU_NO_FREE_CELL_EVT,
	LPHY_TRACE_EMU_SCELL_ACTIVE_EVT,
	LPHY_TRACE_EMU_SCELL_INACTIVE_EVT,
	LPHY_TRACE_EMU_CONN_SCHED_CHANGE_EVT,
	LPHY_TRACE_EMU_CONN_ACTION_IND_EVT,
	LPHY_TRACE_EMU_GAP_CNT_UPDATE_EVT,
	LPHY_TRACE_EMU_CDRX_CNT_UPDATE_EVT,
	LPHY_TRACE_EMU_CONN_GAP_IN_EVT,
	LPHY_TRACE_EMU_CONN_GAP_OUT_EVT,
	LPHY_TRACE_EMU_CONN_V_GAP_IN_EVT,
	LPHY_TRACE_EMU_CONN_V_GAP_OUT_EVT,
	LPHY_TRACE_EMU_GAP_CATEGORY_CHANGE_EVT,
	LPHY_TRACE_EMU_TASK_STATE_CHANGE_EVT,	
	LPHY_TRACE_EMU_RESTART_ALL_TASK_EVT,
	LPHY_TRACE_EMU_CDRX_NC_EVT,
	LPHY_TRACE_EMU_CDRX_ACTIVETIME_EVT,
    LPHY_TRACE_EMU_EVT_BUTT
}LPHY_TRACE_EMU_EVT_ENUM;

/*LPHY_TRACE_EMU_CONN_INTRA_EVT ~ ?*/
typedef struct
{
    UINT32  ulEmuEvtInfo[6];
}LPHY_TRACE_EMU_EVT_STRU;


/************************************************************
                           5. ERROR数据结构定义
************************************************************/
typedef enum
{
    LPHY_WARN_EMU_LOSE_INT              = OM_CMD_ID(LPHY_EMU_MID, OM_TYPE_ERROR, 0x0),
    LPHY_WARN_EMU_TDD_CELL_POSITION,
    LPHY_WARN_EMU_TRACKER_LOW_PAR,
    LPHY_WARN_EMU_CS_LOSE_SERV,
    LPHY_WARN_EMU_EST_TOF_TOO_LARGE,
    LPHY_WARN_EMU_AFC_UNLOCK,
    LPHY_WARN_EMU_AFC_HOLD
}LPHY_ERROR_EMU_ENUM;

typedef struct
{
    UINT32  ulEmuEvtInfo[6];
}LPHY_ERROR_EMU_STRU;



/************************************************************
                           6. IND数据结构定义
************************************************************/

typedef enum
{
    LPHY_IND_EMU_ALL_FREQ_SG         = OM_CMD_ID(LPHY_EMU_MID, OM_TYPE_IND, 0x0),
	LPHY_IND_EMU_SERVE,
    LPHY_IND_EMU_EMU_CFG_CHANNELS,
    LPHY_IND_EMU_EMU_INT,
    LPHY_IND_EMU_EMU_RESULT,
    LPHY_IND_EMU_EMU_STATE,
    LPHY_IND_EMU_ALARM_STAT
}LPHY_IND_EMU_ENUM;


// 返回算法结果
typedef struct _EMU_RESULT_REPORT
{
    UINT16 usFreqInfo;                           // 频点值
    UINT16 usCellID;                             // 小区ID
    INT16  sTimingDelta;                         // 定时调整值
    UINT16 usReserved;
    INT32  ulRsrp_R0;                            // 接收天线0的RSRP
    INT32  ulRsrp_R1;                            // 接收天线1的RSRP
    INT32  ulRsrq_R0;                            // 接收天线0的RSRQ
    INT32  ulRsrq_R1;                            // 接收天线1的RSRQ
    INT32  ulRssi_R0;                            // 接收天线0的RSSI
    INT32  ulRssi_R1;                            // 接收天线1的RSSI
}EMU_RESULT_REPORT_STRU;

typedef struct _EMU_ALL_FREQ_SG
{
    UINT16 usCellNum;                            // 有效小区数
    UINT16 usReserved;
    EMU_RESULT_REPORT_STRU  stCell[EMU_CELL_NUM];
}EMU_IND_ALL_FREQ_SG_STRU;

/*主小区的信息*/
typedef struct _EMU_RESULT_SERVE
{
    UINT16 usCellID;                            // 小区ID
    UINT16 usReserved;
    INT32  lRsrp;                               // 接收天线0的RSRP
    INT32  lRsrp_R0;                            // 接收天线0的RSRP
    INT32  lRsrp_R1;                            // 接收天线1的RSRP
    INT32  lRssi_R0;                            // 接收天线0的RSSI
    INT32  lRssi_R1;                            // 接收天线1的RSSI
    INT32  lRsrq;                               // 接收天线0的RSRQ
    INT32  lSINR;
}EMU_IND_SERVE_SG_STRU;

typedef  struct
{
	UINT32  ulMsrReportNum;
	UINT32  ulFalseAlarmPerNum;
	UINT32  ulFalseAlarmNum;
	UINT32  ulLeastRsrpNum;
	UINT32  ulLeastRealNum;

}EMU_IND_FALSE_ALARM_STRU;


typedef struct _EMU_ALG_CTRL
{
    UINT16 ebTimingLimitFlag;                    // 时偏补偿模块中限幅模块是否打开               ，TRUE-打开；FALSE-关闭
    UINT16 ebDrxAlphaFilterFlag;                 // DRX态下信道总功率/噪声Alpha滤波清零开关      ，TRUE-打开；FALSE-关闭
    UINT16 eDbAlphaFilterFlag;                   // dB域alpha滤波清零开关                      ，TRUE-打开；FALSE-关闭
    UINT16 usMeasSymbolNums;                     // 每个测量周期测量的符号数
}EMU_ALG_CTRL_STRU;


// 算法标志结构
typedef struct _EMU_ALG_CTRL_REQ
{
    LPHY_REQ_MSGID_EMU_ENUM_UINT16   usReqType;  // 请求类型
    UINT16                           ulReaserve;
    EMU_ALG_CTRL_STRU                stAlg_Ctrl;
}EMU_ALG_CTRL_REQ_STRU;



/*LPHY_IND_EMU_EMU_CFG_GLOBAL*/
typedef struct
{
    UINT32 ulCell_Band;
    UINT32 ulInter_En;
    UINT32 ulTiming_En;
    UINT32 ulAngle_Th;
    UINT32 ulDelta_Coeff;
    UINT32 ulAagc_Pos;
    UINT32 ulAdj_En;
    UINT32 ulEmu_Ctrl;
}LPHY_IND_EMU_GLOBAL_CFG_STRU;

typedef struct
{
    UINT32 ulInf;
    UINT32 ulSync;
    UINT32 ulTiming_delta;
    UINT32 ulLast_delta_i0;
    UINT32 ulLast_delta_q0;
    UINT32 ulLast_delta_i1;
    UINT32 ulLast_delta_q1;
    UINT32 ulLast_agc_gain0;
    UINT32 ulLast_agc_gain1;
    UINT32 ulLast_pn_alpha0;
    UINT32 ulLast_pn_alpha1;
    UINT32 ulLast_rsrp0;
    UINT32 ulLast_rsrp1;
    UINT32 ulLast_rssi0;
    UINT32 ulLast_rssi1;
    UINT32 ulLast_theta;
}LPHY_EMU_BBP_ONE_CH_CFG_STRU;

/*LPHY_IND_EMU_EMU_CFG_CHANNELS*/
typedef struct
{
    UINT32 ulEmuBwReg;
    UINT32 ulEmuInterEnReg;
    UINT32 ulEmuCtrlReg;
    UINT32 ulEmu_RptMode;
    UINT32 ulEmuFddTddSel;

    LPHY_EMU_BBP_ONE_CH_CFG_STRU stBbpChCfg[8];

    UINT32 ulSym_num0;
    UINT32 ulSym_num1;
    UINT32 ulTiming_kalman_idx0;
    UINT32 ulTiming_kalman_idx1;
    UINT32 ulRsrp_kalman_idx0;
    UINT32 ulRsrp_kalman_idx1;
    UINT32 ulRsrp_alpha;
    UINT32 ulRsrp_first_alpha;
    UINT32 ulEmu_en;
    UINT32 ulEmu_start;
    UINT32 ulEmu_stop;
    UINT32 ulEmu_Dma_en;
}LPHY_IND_EMU_CHANNELS_CFG_STRU;


/*LPHY_IND_EMU_EMU_INT*/
typedef struct
{
    UINT32  ulEmuEvtInfo[6];//usFreqInfo; BALONGV7_SMU_REG_SMU_SYM_CNT0_REG; BALONGV7_SMU_REG_SMU_SYM_CNT1_REG
}LPHY_IND_EMU_INT_STRU;

typedef struct
{
    UINT32 ulLast_delta_i0;
    UINT32 ulLast_delta_q0;
    UINT32 ulLast_delta_i1;
    UINT32 ulLast_delta_q1;
    UINT32 ulLast_agc_gain0;
    UINT32 ulLast_agc_gain1;
    UINT32 ulLast_pn_alpha0;
    UINT32 ulLast_pn_alpha1;
    UINT32 ulLast_rsrp0;
    UINT32 ulLast_rsrp1;
    UINT32 ulLast_rssi0;
    UINT32 ulLast_rssi1;
    UINT32 ulLast_theta;
    UINT8  ucTiming_kalman_index;               //
    UINT8  ucRsrp_kalman_index;                 //
    UINT8  ucAlpha_Init;                       //
    UINT8  ucReserved;                          //
}EMU_OM_CELL_BBP_CTX_STRU;


typedef struct
{
    INT16                       sRssi_current0;
    INT16                       sRssi_current1;
    INT16                       sRsrp_current0;
    INT16                       sRsrp_current1;
    INT16                       sRsrq_current0;
    INT16                       sRsrq_current1;
    INT16                       sRsrp_rpt;
    INT16                       sRsrq_rpt;
}EMU_OM_CALC_RESULT_STRU;


typedef struct
{
    EMU_OM_CELL_BBP_CTX_STRU    stEmuBbpCellCtx;
    EMU_OM_CALC_RESULT_STRU     stResult;
    UINT16                      usCellId;
    UINT16                      usMeasSymb;
}LPHY_EMU_CELL_RESULT_STRU;


/*LPHY_IND_EMU_EMU_RESULT*/
typedef struct
{
	UINT16 usCellId;
	UINT16 enCellCPInd;
	UINT16 enBandWidth;
	UINT16 usTxNum;
	UINT32 ulCellPosition;
	UINT32 ulPnCnter;
	UINT32 ulTimeOffsetCnter;
	UINT32 ulDagc[2];
	INT16  sAagc[2];
	INT32  lTheta;
	UINT32 ulTxRxPh[4];
	UINT32 ulTxRxPn[4];
	UINT32 ulRsrpBef[2];
	UINT32 ulRsrpAft[2];
	INT16  sRsrpdB[2];
	INT32  lRsv[2];

}EMU_SDR_PROC_RESULT;


/*LPHY_IND_EMU_EMU_STATE*/
typedef struct
{
    UINT32 ulCsInterStartCnt;
    UINT32 ulCsSlaveStartCnt;
    UINT32 ulEmuIntraCfgCnt;
    UINT32 ulEmuIntraIntCnt;
    UINT32 ulEmuInterCfgCnt;
    UINT32 ulEmuInterIntCnt;
    UINT32 ulEmuSlaveCfgCnt;
    UINT32 ulEmuSlaveIntCnt;
    UINT32 ulEmuRptIntraCnt;
    UINT32 ulEmuRptInterCnt;
    UINT32 ulEmuWOccasionCnt;
    UINT32 ulEmuGOccasionCnt;
    UINT32 ulEmuWFinishCnt;
    UINT32 ulEmuGFinishCnt;
}LPHY_IND_EMU_STATE_STRU;

typedef struct
{
    UINT16  ausCQI[2];
    UINT16  usRI;
    UINT8   aucRes[2];
}LPHY_IND_EMU_AT_RI_CQI_STRU;

typedef struct
{
    UINT16  usOpId;
    UINT16  usTa;
    INT32   lSINR;
    LPHY_IND_EMU_AT_RI_CQI_STRU stRiCqiPara;
}LPHY_IND_EMU_AT_MEAS_STRU;


/************************************************************
                             接口函数声明
 ************************************************************/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __EMU_OM_DEF_H__ */
