/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : tds_cellsearch_om_def.h
  版 本 号   : 初稿
  作    者   : guxiaohong
  生成日期   : 2012年8月10日
  最近修改   :
  功能描述   : 上报OM相关的定义结构体
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月10日
    作    者   : guxiaohong
    修改内容   :

******************************************************************************/


#ifndef TDS_CELLSEARCH_OM_DEF_H_
#define TDS_CELLSEARCH_OM_DEF_H_



#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */
/************************************************************
                     包含其它模块的头文件
************************************************************/

#include "balong_lte_dsp.h"




/************************************************************
                               宏定义
************************************************************/




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
    TPHY_REQ_CS_REQST_SWITCH           = OM_TCMD_ID(TPHY_CS_MID, OM_TYPE_REQ, 0x1),
    TPHY_REQ_CS_TRACE_SWITCH,
    TPHY_REQ_CS_ERROR_SWITCH,
    TPHY_REQ_CS_FMSYC_PARAST,
    TPHY_REQ_CS_CPSYC_PARAST,
    TPHY_REQ_CS_FQADJ_PARAST,
    TPHY_REQ_CS_MIDRD_PARAST,
    TPHY_REQ_CS_SFREQ_PARAST,
    TPHY_REQ_CS_ESYNC_PARAST,
    TPHY_REQ_SF_REQ_PARAST,
    TPHY_REQ_CS_REQ_PARAST,
    TPHY_REQ_CSM_REQ_PARAST
}TPHY_CS_REQ_ENUM;
typedef UINT16 TPHY_CS_REQ_ENUM_UINT16;


typedef struct TPHY_REQ_ICS_REQST_SWITCH
{
    OM_REQ_ENABLE_ENUM_UINT16 enTDSCSReqRpt;
    OM_REQ_ENABLE_ENUM_UINT16 enReserve;
}TPHY_REQ_ICS_REQST_SWITCH_STRU;


typedef struct TPHY_REQ_ICS_TRACE_SWITCH
{
    OM_REQ_ENABLE_ENUM_UINT16 enReqProTrace;
    OM_REQ_ENABLE_ENUM_UINT16 enCSFrameTrace;
    OM_REQ_ENABLE_ENUM_UINT16 enCSChipTrace;
    OM_REQ_ENABLE_ENUM_UINT16 enCSMidTrace;
    OM_REQ_ENABLE_ENUM_UINT16 enCSAdjTrace;
    OM_REQ_ENABLE_ENUM_UINT16 enSweepTrace;
}TPHY_REQ_ICS_TRACE_SWITCH_STRU;


typedef struct TPHY_REQ_ICS_ERROR_SWITCH
{
    OM_REQ_ENABLE_ENUM_UINT16 enCSFrameError;
    OM_REQ_ENABLE_ENUM_UINT16 enCSChipError;
    OM_REQ_ENABLE_ENUM_UINT16 enCSMidError;
    OM_REQ_ENABLE_ENUM_UINT16 enReserve;
}TPHY_REQ_ICS_ERROR_SWITCH_STRU;


typedef struct TPHY_REQ_ICS_FRAME_PARAST
{
	OM_REQ_ENABLE_ENUM_UINT16   enDistub;       // 帧同步是否做大时隙干扰消除，默认做干扰消除
	UINT16      usSwitchFlag;                   // 帧同步门限判断标识:0表示不进行门限判断，1表示进行门限判断
	UINT8		ucThresholdA;                   // 5/6的门限中的5
	UINT8		ucThresholdB;                   // 5/6的门限中的6
	UINT8		ucFrameCnt;                     // 帧同步需要计算子帧数，默认为5子帧
	UINT8		ucFrameMaxCnt;                  // 帧同步失败后最大子帧数，默认为20子帧
    UINT32      ulDwptThreshold;                // TDS_CS_FRAME_THRESHOLD  (1250) //1250; //1000;
    UINT32      ulCoffA;                        // A档位的系数 DS_CS_FRAME_COFFA      (1)
    UINT32      ulCoffB;                        // B档位的系数 DS_CS_FRAME_COFFA      (1)
    UINT16      usAgcA;                         // A档位的AGC
    UINT16      usAgcB;                         // B档位的AGC
}TPHY_REQ_ICS_FRAME_PARAST_STRU;


typedef struct TPHY_REQ_ICS_CSYNC_PARAST
{
	UINT8       ucPeakAvrThd;                   // chip级同步中的峰均比门限值，默认为10
	UINT8		ucChanSyncCnt;                  // 输出给信道估计的SyncId个数，默认为3
	UINT8		ucThresholdA;                   // 信道冲激阈值门限值A   A/B=3.625
	UINT8		ucThresholdB;                   // 信道冲激阈值门限值B
	UINT8       ucOutSyncCnt;                   // chip级同步检测输出的syncId个数
	UINT8		ucFrameCnt;                     // 帧同步需要计算子帧数
	UINT8       aucReserve[2];
}TPHY_REQ_ICS_CSYNC_PARAST_STRU;


typedef struct TPHY_REQ_ICS_MIDRD_PARAST
{
	UINT8       ucFrameCnt;                     // Midamble码需要计算子帧数
	UINT8       aucReserve[3];
}TPHY_REQ_ICS_MIDRD_PARAST_STRU;


typedef struct TPHY_REQ_ICS_FQADJ_PARAST
{
	UINT8       ucFqAdjCnt;                     // 频率粗调次数
	UINT8		ucFrameCnt;                     // 频率粗调需要计算子帧数
	UINT8       aucReserve[2];
}TPHY_REQ_ICS_FQADJ_PARAST_STRU;


typedef struct TPHY_REQ_ICS_ECSYNC_PARAST
{
	UINT8       ucExactCnt;                     // chip级以下调整次数
	UINT8		ucFrameCnt;                     // chip级以下调整一次需要计算子帧数
	UINT8       aucReserve[2];
}TPHY_REQ_ICS_ECSYNC_PARAST_STRU;


typedef struct
{
    UINT16      usBegFreq;
    UINT16      usEndFreq;
} TDS_SF_FREQBAND_STRU;


typedef struct TPHY_REQ_ICS_SFREQ_PARAST
{
    UINT16      usSyncStatus;
    UINT16      usFreqBandNum;
    TDS_SF_FREQBAND_STRU  stFreqBand[3];
}TPHY_REQ_ICS_SFREQ_PARAST_STRU;



typedef struct TPHY_REQ_ICS_CS_PARAST
{
    UINT32  ulBBIT_FLAG;
    UINT32  ulCSFreq;
    UINT32  ulCSId;
    UINT32  ulSyncStatus;
    UINT32  ulSyncId;
    UINT32  ulMidId;
}TDS_REQ_ICS_CS_PARAST_STRU;


typedef struct TPHY_REQ_ICS_CSM_PARAST
{
    UINT32 ulStatus;
    UINT32 ulFreq;
    UINT32 ulCellId;
}TDS_REQ_ICS_CSM_PARAST_STRU;



/************************************************************
                           2. CNF数据结构定义
************************************************************/

typedef enum
{
    TPHY_CNF_CS_CNF					= OM_TCMD_ID(TPHY_CS_MID, OM_TYPE_CNF, 0x1),
}TPHY_CS_CNF_ENUM;


/************************************************************
                           3. Ind数据结构定义
************************************************************/

typedef enum
{
    TPHY_IND_CS_TM_REPORT           = OM_TCMD_ID(TPHY_CS_MID, OM_TYPE_IND, 0x1),
    TPHY_IND_CS_CP_REPORT,
}TPHY_CS_IND_ENUM;
typedef UINT16 TPHY_CS_IND_ENUM_UINT16;



/************************************************************
                           4. TRACE数据结构定义
************************************************************/

typedef enum
{
    TPHY_TRACE_CS_REQ_STRU              = OM_TCMD_ID(TPHY_CS_MID, OM_TYPE_TRACE, 0x1),
    TPHY_TRACE_CS_FSYNC_POS,
	TPHY_TRACE_CS_CSYNC_PARA,
	TPHY_TRACE_CS_CSYNC_CORRPWR,
	TPHY_TRACE_CS_CSYNC_CORRSYNCID,
	TPHY_TRACE_CS_CSYNC_CHANPWR,
	TPHY_TRACE_CS_CSYNC_POS,
	TPHY_TRACE_CS_MIDRD_RES,
	TPHY_TRACE_CS_MIDRD_CHANPWR,
	TPHY_TRACE_CS_MIDRD_PEAK,
	TPHY_TRACE_CS_FQADJ_OFF,
	TPHY_TRACE_CS_CNF_STRU,
	TPHY_TRACE_CS_CAL_STRU,
	TPHY_TRACE_SF_FSYNC_POS,
	TPHY_TRACE_SF_RST,
	TPHY_TRACE_CS_RECDATA_PARA,
	TPHY_TRACE_CS_RECEDData_PARA,
	TPHY_TRACE_CS_CSYNC_PARASTRU,
	TPHY_TRACE_CS_MIDRD_PARASTRU,
	TPHY_TRACE_CS_MIDRD_SYNCCALVAL,
	TPHY_TRACE_CS_INPUT_CHANVAL,
	TPHY_TRACE_CS_NOIC_CHANVAL,
	TPHY_TRACE_CS_SR_CHANVAL,
	TPHY_TRACE_CS_DWPTS_DATA,
	TPHY_TRACE_CS_MIDRD_DATA,
}TPHY_CS_TRACE_ENUM;
typedef UINT16 TPHY_CS_TRACE_ENUM_UINT16;

typedef struct
{
	UINT16		usCellId;
	UINT16		usSyncStatus;
	UINT16		usFreq;
	UINT16		usSyncId;
	UINT16		usMidId;
	UINT16      usReserve;
}TPHY_OM_TRACE_CS_REQ_STRU;


typedef struct
{
	UINT16		usCellId;
	UINT16		usResult;
	UINT16		usFreq;
	UINT16		usSyncId;
	UINT16		usMidId;
	UINT16      usRssi;
}TPHY_OM_TRACE_CS_CNF_STRU;


typedef struct
{
    UINT16      usCellId;           //
    UINT16      usFreq;             //
    INT16       sFrameOff;
    INT16       sMinPos;
}TPHY_OM_TRACE_CS_FSYNC_CALPOS_STRU;


typedef struct
{
	UINT32		ulEnvVal;
    UINT32		ulSysSyncNum;
    UINT16		usSyncIdArray;
    UINT16		usSysSyncId;        // ??Sync Id  ?Chip??????????
    UINT16		usSysMidId;     	// ??mid id   ?Midamble?????????
    UINT16		usBAFlag;           //
    UINT16		usSyncState;        //  1:sync  0: not sync
    UINT16		usReserved;
}TPHY_OM_TRACE_CS_CSYNC_PARA_STRU;


typedef struct
{
	UINT32		ulEnvVal;
    UINT32		ulRscp;
	UINT32		ulSatNum;
    UINT16		ausMeas[32];
}TPHY_OM_TRACE_CS_CSYNC_RESULT_STRU;


typedef struct
{
    UINT32      aulPeakPwr[32];
    UINT32      aulAverPwr[32];
}TPHY_OM_TRACE_CS_CSYNC_CORRPWR_STRU;


typedef struct
{
    UINT16      ausCorrSyncId[32];
}TPHY_OM_TRACE_CS_CSYNC_CORRSYNCID_STRU;


typedef struct
{
    UINT32      ulMaxChanPwr;
	UINT32		ulSubChanPwr;
	UINT32      aulChanPwr[64];
}TPHY_OM_TRACE_CS_CSYNC_CHANPWR_STRU;


typedef struct
{
    TPHY_OM_TRACE_CS_CSYNC_CHANPWR_STRU stChanPwr[3];
}TPHY_OM_TRACE_CS_CSYNC_AllCHANPWR_STRU;


typedef struct
{
    UINT16      usSyncId;
	UINT16		usSyncPos;
}TPHY_OM_TRACE_CS_CSYNC_POS_STRU;


typedef struct
{
	UINT32		ulMidNum;
    UINT16		ausMidIndex[3];
	UINT16		usReserved;
}TPHY_OM_TRACE_CS_MIDRD_RESULT_STRU;


typedef struct
{
	UINT32		ulMaxPos;
	UINT32		aulPwr[4];
}TPHY_OM_TRACE_CS_MIDRD_CHANPWR_STRU;


typedef struct
{
	UINT32		ulPeak;
	UINT32      ulNoise;
}TPHY_OM_TRACE_CS_MIDRD_PEAK_STRU;


typedef struct
{
	INT32		lFreqOff1;
	INT32		lFreqOff2;
}TPHY_OM_TRACE_CS_FQADJ_OFF_STRU;


typedef struct
{
	UINT16      ausPos[504];                // 扫频结果频点对应的帧同步位置
}TPHY_OM_TRACE_SF_FSYNC_POS_STRU;


typedef struct
{
	UINT16		ausFreq[12];             // 扫频结果中的频点
	UINT16		ausRssi[12];             // 扫频结果中的RSSI
	UINT16      ausPos[12];              // 扫频结果频点对应的帧同步位置
}TPHY_OM_TRACE_SF_FREQ_RST_STRU;


typedef struct
{
    UINT32      ulCSReqNum;
    UINT32      ulCSSucNum;
    UINT32      ulCSFalNum;
    UINT32      aulReserve1;
    UINT32      aulReserve2;
}TDS_OM_TRACE_CS_CALNUM_STRU;


typedef struct
{
	INT32		lEnvFlag;          // 初始小区搜索、被禁小区搜索、先验小区搜索
    INT32		lFuncVal;          // 函数功能:帧同步、chip级同步、midamble读取、频率粗调、chip级以下等
    INT32		lFuncStatus;       // 设置收数、收到数计算、后续计算等
    INT32		lPara1;
    INT32		lPara2;
    INT32		lPara3;
    INT32		lPara4;
    INT32		lPara5;
}TPHY_OM_TRACE_CS_PRO_PARA_STRU;


typedef struct
{
    UINT32  ulReqCellNum;        // 指定CellId的个数。无列表时为0，有先验列表或者被禁列表时为相应数
    UINT16  ausReqCellId[12];     // 先验列表或者被禁列表中对应的CellId
    UINT32  ulCalSyncNum;                             // 计算得到的sync个数
    UINT32  aulSyncCorr[6];      // 输出的sync对应的相关功率
    UINT16  ausSyncId[6];        // 输出的SyncId
    UINT16  ausSyncPos[6];       // 输出的SyncId对应的位置
}TDS_OM_TRACE_CS_CSYNC_STRU;


typedef struct
{
    UINT32  ulCellNum;                                  // 有效CellId个数
    UINT16  ausCellId[12];          // 有效CellId
    UINT16  ausReliable[12];        // CellId对应的置信度
    UINT16  ausSearchFlag[12];      // CellId干扰标识,是NoIc还是IC计算出的
    INT16   asPosOff[12];           // 小区偏移位置
}TDS_OM_TRACE_CS_MIDRD_STRU;


typedef struct
{
    UINT32 ulSyncId;
    UINT32 ulMidIndex;
    UINT32 ulChanPwr;
    UINT32 ulNoisePwr;
    UINT32 ulMaxPwrDb;
    UINT32 ulNoiseDb;
    INT32  lReliable;
    INT32  lReThreshold;
    UINT32 ulMiamblePar;
    UINT32 ulParThreshold;
    UINT32 ausPwrSum[4];
}TDS_OM_TRACE_CS_MIDRD_CALVAL;


typedef struct
{
    TDS_OM_TRACE_CS_MIDRD_CALVAL stMidVal[12];
}TDS_OM_TRACE_CS_MIDRD_ALLSYNC_CALSTRU;


typedef struct
{
    INT16 asChanVal[256];
}TDS_OM_TRACE_CS_CHANVal_STRU;


typedef struct
{
    INT16 asDataVal[256];
}TDS_OM_TRACE_CS_DWPTS_DATA;


typedef struct
{
    INT16 asDataVal[320];
}TDS_OM_TRACE_CS_MIDRD_DATA;


/************************************************************
                           6. ERROR 数据结构定义
************************************************************/

typedef enum
{
    TPHY_ERROR_CS_REQ_FEEDBACK_FAIL         = OM_TCMD_ID(TPHY_CS_MID, OM_TYPE_ERROR, 0x1),
    TPHY_ERROR_CS_CSYNC_MEAK_FAIL,
    TPHY_ERROR_CS_CSYNC_CHANPWR_FAIL,
    TPHY_ERROR_CS_DATA_PRO_FAIL,
    TPHY_ERROR_SF_DATA_PRO_FAIL,
    TPHY_ERROR_CSM_DATA_PRO_FAIL
}TPHY_CS_ERROR_ENUM;


typedef struct
{
	UINT32		ulEnvVal;
}TPHY_OM_ERROR_CS_CSYNC_MEAKFAIL_STRU;

typedef struct
{
	UINT16		usSatNum;
	UINT16		ausSyncId[3];
	UINT16		ausCorrPwrPos[3];       // ????????
	UINT16		ausMaxPwrPos[3];        // ?????????????
	UINT32		aulChanMaxPwr[3];       // ????????
}TPHY_OM_ERROR_CS_CSYNC_CHANPWRFAIL_STRU;

typedef struct
{
	UINT16		ausPos[3];
	UINT16		usReseved;
}TPHY_OM_ERROR_CS_CSYNC_NOSYNCPOSFAIL_STRU;

typedef struct
{
    UINT32  ulCSDataErr;
    UINT32  ulCSProcErr;
    UINT32  ulReserve1;
    UINT32  ulReserve2;
    UINT32  ulReserve3;
}TDS_OM_ERROR_CS_CALNUM_STRU;



#ifdef __cplusplus
#if __cplusplu
#endif
#endif /* __cplusplus */

#endif               /* define TDS_CELLSEARCH_OM_DEF_H_   */



