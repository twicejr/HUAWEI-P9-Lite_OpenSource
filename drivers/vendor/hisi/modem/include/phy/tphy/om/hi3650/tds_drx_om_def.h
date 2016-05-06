#ifndef  __TDS_DRX_OM_DEF_H_______
#define  __TDS_DRX_OM_DEF_H_______

#include "type_define.h"
#include "om_base_def.h"

typedef enum TDS_DRX_OM_REQ_MSGID
{
    TPHY_REQ_DRX_CLKMEASSTAT = OM_TCMD_ID(TPHY_DRX_MID, OM_TYPE_REQ, 0x0),
    TPHY_REQ_DRX_IDLESLEEPPARA = OM_TCMD_ID(TPHY_DRX_MID, OM_TYPE_REQ, 0x1),
    TPHY_REQ_DRX_IDLEDETAILINFO = OM_TCMD_ID(TPHY_DRX_MID, OM_TYPE_REQ, 0x2),
}TDS_DRX_OM_REQ_MSGID_ENUM;

typedef enum TDS_DRX_OM_RPT_IND
{
    TPHY_DRX_REPORT_CLKMEASSTAT_IND =  OM_TCMD_ID(TPHY_DRX_MID, OM_TYPE_TRACE, 0x0),

    TPHY_DRX_REPORT_IDLESLEEPPARA_IND =  OM_TCMD_ID(TPHY_DRX_MID, OM_TYPE_TRACE, 0x1),

    TPHY_DRX_REPORT_IDLEDETAILINFO_IND =  OM_TCMD_ID(TPHY_DRX_MID, OM_TYPE_TRACE, 0x2),

}TDS_DRX_OM_RPT_ENUM;


typedef struct
{
    UINT32 ulClkMeasStatEnable;
}TPHY_DRX_REQ_CLKMEASSTAT_STRU;


typedef struct
{
    UINT32 ulIdleSleepParaEnable;

}TPHY_DRX_REQ_IDLESLEEPPARA_STRU;

typedef struct
{
    UINT32 ulIdleDetailInfoEnable;

}TPHY_DRX_REQ_IDLEDETAILINFO_STRU;

/*****************************************************************************
 结构名    :TDS_DRX_OM_SLEEP_TIME_STRU
 协议表格  :
 结构说明  :TDS DRX睡眠时长参数信息
*****************************************************************************/
typedef struct
{
    UINT32 ulToatalSleepChipTime;
    UINT32 ulToatalSleep32kTime;
    UINT32 ulWakeup32kTime;
    UINT32 ulSwitch32kTime;
    UINT32 ulSleepReadyChipTime;
    UINT32 ulPreWakeSfnNum;
}TDS_DRX_SLEEP_TIME_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usChipNum;
    TDS_DRX_SLEEP_TIME_STRU stTdsDrxSleepPara;
}TDS_DRX_OM_SLEEP_TIME_STRU;

typedef enum
{
    TDS_OM_PICH_TASK = 0,
    TDS_OM_PCH_TASK,
    TDS_OM_ENERGY_MEAS_TASK,
    TDS_OM_CELL_SEARCH_TASK,
    TDS_OM_CLK_MEAS_TASK,
    TDS_OM_PRESYNC_TASK,
    TDS_OM_SYSINFO_TASK,
    TDS_OM_DRX_MAX_TASK,
} TDS_DRX_OM_TASK_ENUM;
typedef UINT16 TDS_DRX_OM_TASK_ENUM_UINT16;

typedef enum
{
    TDS_OM_TASK_START,
    TDS_OM_TASK_END,
    TDS_OM_TASK_TYPE_NUM,
}TDS_DRX_OM_TASK_OP_TYPE;
typedef UINT16 TDS_DRX_OM_TASK_OP_TYPE_UINT16;

typedef enum
{
    DRX_OM_WAKE_UP_STATE,
    DRX_OM_DSP_OK_STATE,
    DRX_OM_NORMAL_WORKING_STATE,
    DRX_OM_PRE_SLEEP_READY_STATE,
    DRX_OM_SLEEP_ENABLE_STATE,
    DRX_OM_STATE_NUM,
}TDS_DRX_OM_STATE_ENUM;
typedef UINT16 TDS_DRX_OM_STATE_ENUM_UINT16;

typedef struct
{
    UINT16 usSfn;
    UINT16 usChipNum;
}TDS_DRX_OM_TIME_STRU;
/*****************************************************************************
 结构名    :TDS_DRX_TASK_INFO_STRU
 协议表格  :
 结构说明  :TDS IDLE态任务信息
*****************************************************************************/
typedef struct
{
    TDS_DRX_OM_TASK_ENUM_UINT16 usTaskId;
    UINT16 usTaskEnterNum;          /*Task 执行次数*/
    TDS_DRX_OM_TIME_STRU stOpTypeTime[TDS_OM_TASK_TYPE_NUM];    /*记录最新的任务开始结束时刻*/
}TDS_DRX_TASK_INFO_STRU;

/*****************************************************************************
 结构名    :TDS_DRX_IDLE_STATE_INFO_STRU
 协议表格  :
 结构说明  :TDS IDLE DRX状态信息
*****************************************************************************/
typedef struct
{
    TDS_DRX_OM_STATE_ENUM_UINT16 usDrxOmState;
    UINT16 usStateNum;      /*上报周期内State进入次数*/
    TDS_DRX_OM_TIME_STRU stStateTime;     /*记录最新的state开始时刻*/
}TDS_DRX_IDLE_STATE_INFO_STRU;

/*****************************************************************************
 结构名    :TDS_DRX_PRESYNC_INFO_STRU
 协议表格  :
 结构说明  :TDS 定时预同步信息
*****************************************************************************/
typedef struct
{
    UINT16 usPresyncNum;    /*上报周期内presync次数*/
    UINT16 usRsvd;
    TDS_DRX_OM_TIME_STRU stPresyncStartTime;    /*记录最新的presync开始时刻*/
}TDS_DRX_PRESYNC_INFO_STRU;

/*****************************************************************************
 结构名    :TDS_DRX_OM_CLK_MEAS_INFO_STRU
 协议表格  :
 结构说明  :TDS 时钟测量信息
*****************************************************************************/
typedef struct
{
    UINT16 usClkMeasNum;    /*上报周期内clkmeas次数*/
    UINT16 usRsvd;
    TDS_DRX_OM_TIME_STRU stClkMeasStartTime;    /*记录最新的clkmeas开始时刻*/
}TDS_DRX_OM_CLK_MEAS_INFO_STRU;
/*****************************************************************************
 结构名    :TDS_DRX_OM_DETAIL_INFO_STRU
 协议表格  :
 结构说明  :TDS IDLE态详细控制信息
*****************************************************************************/
typedef struct
{
    TDS_DRX_OM_TIME_STRU stRptTime;
    TDS_DRX_TASK_INFO_STRU stTdsDrxTaskInfo[TDS_OM_DRX_MAX_TASK];
    TDS_DRX_IDLE_STATE_INFO_STRU stTdsDrxStateInfo[DRX_OM_STATE_NUM];
    TDS_DRX_PRESYNC_INFO_STRU stPresyncInfo;
    TDS_DRX_OM_CLK_MEAS_INFO_STRU stClkMeasInfo;
}TDS_DRX_OM_DETAIL_INFO_STRU;


/*****************************************************************************
 结构名    :TDS_DRX_OM_CLK_MEAS_STRU
 协议表格  :
 结构说明  :TDS DRX OM时钟测量参数结构
*****************************************************************************/
typedef struct
{
    UINT32 ulClkMeasCounter;
    UINT16 usClkMeasInt;
    UINT16 usClkMeasFrac;
    UINT16 usClkMeasValid;
    UINT16 usClkMeasState;
    UINT16 usClkMeasParaIndex;
    UINT16 usLastClkMeasSfn;
} TDS_DRX_OM_CLK_MEAS_STRU;

#endif /* __TDS_DRX_OM_DEF_H_______ */



