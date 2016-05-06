#ifndef  __TDS_OM_SCHDL_DEF_H_______
#define  __TDS_OM_SCHDL_DEF_H_______

#include "type_define.h"
#include "om_base_def.h"

typedef enum TDS_SCHDL_OM_REQ_MSGID
{
    TPHY_REQ_SCHDL_CPUUSED  = OM_TCMD_ID(TPHY_SCHED_MID, OM_TYPE_REQ, 0x1),
    TPHY_REQ_SCHDL_FUNCSTAT = OM_TCMD_ID(TPHY_SCHED_MID, OM_TYPE_REQ, 0x2),
    TPHY_REQ_RPT_SCHED_SYM_TIME
}TDS_SCHDL_OM_REQ_MSGID_ENUM;

typedef struct __TPHY_REQ_RPT_SCHED_SYM_TIME_STRU__
{
	UINT32       enEnaRpt;
}TPHY_REQ_RPT_SCHED_SYM_TIME_STRU;


typedef struct
{
    UINT32 ulCpuUsedEnable;
    UINT32 ulCpuStatPeriod;
    void *pTmHdl;
}TPHY_SCHDL_REQ_CPUUSED_STRU;

typedef enum
{
    NON_OVERWRITE_MODE,
    OVERWRITE_MODE,
}CB_WORK_MODE_ENUM;
typedef UINT32 CB_WORK_MODE_ENUM_UINT32;








typedef struct
{
    UINT32 ulFuncStatEnable;
    UINT32 ulFuncStatPeriod;
    CB_WORK_MODE_ENUM_UINT32 ulCbMode;
    void *pTmHdl;
}TPHY_SCHDL_REQ_FUNCSTAT_STRU;

typedef struct
{
    UINT16 usCpuUsed;
    UINT16 usRsvd;
}TPHY_SCHDL_RPT_CPUUSED_STRU;

typedef enum
{
    TDS_SCHD_FILE        = 0,
    TDS_INT_FILE,
    TDS_MAILBOX_FILE,
    TDS_OM_FILE,
    TDS_FILE_ID_BUTT
}TDS_FILE_ID_ENUM;
typedef UINT16 TDS_FILE_ID_ENUM_UINT16;
typedef enum
{
    TASK_STAT,
    INT_STAT,
}TDS_OM_STAT_TYPE;
typedef UINT16 TDS_OM_STAT_TYPE_UINT16;

typedef struct
{
    TDS_OM_STAT_TYPE_UINT16 usOmStatType;
    TDS_FILE_ID_ENUM_UINT16 ulFileId;
    UINT16 usLineNum;
    UINT16 usFrame;
    UINT16 usType;  /*0:start,1:end*/
    UINT16 usPara;
    UINT32 ulTaskTime;  /*dsp cycle*/
}TDS_SCHD_OM_TIME_STRU;


typedef struct
{
    TDS_SCHD_OM_TIME_STRU stTdsFuncInfo[32];
}TPHY_SCHDL_RPT_FUNC_STAT_STRU;

typedef struct TDS_SCHDL_TS_INT_DELAY
{
    UINT16 usTsIntErrFlag;                               /*有时隙中断延迟，累积多余一个时隙中断告警*/
    UINT8 ucLastCorrectTs;                                  /*有时隙中断延迟，上一次调度正常时隙号*/
    UINT8 ucErrTsCnt;                                    /*有时隙中断延迟，累积时隙中断数*/
}TDS_SCHDL_TS_INT_DELAY_STRU;

typedef struct
{
    UINT16  usSfn;              /*子帧号*/
    UINT16  usWorkMod;          /*工作模式*/
    UINT16  usCellId;           /*小区ID*/
    UINT16  usSevFreq;          /*服务频点*/

    /*AFC TIMING*/
    UINT32  ulAfcPdm;
    INT32   lTimAdj;
    INT16   sFreqOffset;
    INT16   sIllockFlag;

    /*AGC*/
    UINT16  usTs0Freq;
    UINT16  ausGain[7];

    /*CQI SYNC SIR*/
    UINT8   usModFormat;
    UINT8   usTbiOut;
    INT16   sDpchScale;
    INT16   sSir;
    INT16   sDschSir;

    /*CD*/
    INT8    cViterCrc; /*正确报1，错误报 -1.ICS:PCCPCH ACC/IDEL:sccpch DCH:DPCH */
    INT8    cTurboCrc;
    UINT8   ucDlTfci;
    UINT8   ucSbFlag;

    UINT8   ucDschTsMap;
    UINT8   ucNewDataInd;
    UINT8   ucDschRv;
    UINT8   ucHarqId;

	UINT16  usDschTbsize;
	UINT16  usIpcmFromHifi;

    INT8    ucScchCrc;
    INT8    cPichRes;
    INT8    ucAgchCrc;
	INT8    ucRev;

    /*UL*/
    INT16   sSS;
    INT16   sTxPower[3];
    UINT16  usUlTfci;

    /*PC*/
    INT16   sDwDpchTpc;
    UINT16  usScchLostNum;
    UINT16  usAgchLostNum;

    /*JD*/
    INT16   lMaxPathPos;
    INT16   lCellPos;
    UINT16  ausCirCellId[4];
    INT16   asTs0Scale[8];
    INT16   asSevScale[8];

}TDS_OM_FTTA_STRU;
extern TDS_OM_FTTA_STRU   gastTdsOmFttaData[4];


//extern void TDS_SCHD_OMFunStat(TDS_FILE_ID_ENUM_UINT16 ulFileId, UINT16 usLineNum, TDS_SCHD_OM_TASKSSTAT_TYPE_UINT16 usType, UINT16 usPara, TDS_OM_STAT_TYPE_UINT16 usOmStatType, INT_TYPE_UINT16 usTdsIntType);


/************************************************************
                           5. SG
************************************************************/
typedef enum TDS_SCHDL_OM_RPT_IND
{
    TPHY_SCHDL_RRT_CPUUSED_IND      =  OM_TCMD_ID(TPHY_SCHED_MID, OM_TYPE_TRACE, 0x1),
    TPHY_SCHDL_RRT_FUNCSTAT_IND     =  OM_TCMD_ID(TPHY_SCHED_MID, OM_TYPE_TRACE, 0x2),
    TPHY_SCHDL_RRT_TS_INT_DELAY_IND =  OM_TCMD_ID(TPHY_SCHED_MID, OM_TYPE_TRACE, 0x3),

    TPHY_SG_SCHED_SYM_TIME,
    TPHY_SG_SCHED_FUNC_CORE_COUNTER,
}TDS_SCHDL_OM_RPT_ENUM;


#define TDS_MAX_SCHDL_FUN_NUM           6
#define TDS_MAX_SCHDL_SLT_NUM           10

typedef struct __TPHY_SG_SCHED_SYM_TIME_STRU__
{
    UINT32    ulStartTime[TDS_MAX_SCHDL_SLT_NUM];      
    UINT32    ulEndTime[TDS_MAX_SCHDL_SLT_NUM];
    UINT32	  ulDuration[TDS_MAX_SCHDL_SLT_NUM];	
}TPHY_SG_SCHED_SYM_TIME_STRU;

typedef struct __TPHY_SG_SCHED_FUNC_CORE_CNT_STRU__
{
    UINT32  ulFuncCounter0[TDS_MAX_SCHDL_SLT_NUM][TDS_MAX_SCHDL_FUN_NUM];
}TPHY_SG_SCHED_FUNC_CORE_CNT_STRU;

#endif /* __TDS_OM_SCHDL_DEF_H_______ */

