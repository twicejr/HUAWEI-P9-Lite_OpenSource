/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : SpySystem.h
  版 本 号   : 初稿
  作    者   : m00128685
  生成日期   : 2009年3月23日
  最近修改   :
  功能描述   : Monitor.C 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2009年3月23日
    作    者   : m00128685
    修改内容   : 创建文件

******************************************************************************/

#ifndef __SPYSYSTEM_H__
#define __SPYSYSTEM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define SPY_INFO_LOG(string)                PS_LOG(WUEPS_PID_SPY, 0, PS_PRINT_INFO,     string)
#define SPY_NORMAL_LOG(string)              PS_LOG(WUEPS_PID_SPY, 0, PS_PRINT_NORMAL,   string)
#define SPY_WARNING_LOG(string)             PS_LOG(WUEPS_PID_SPY, 0, PS_PRINT_WARNING,  string)
#define SPY_ERROR_LOG(string)               PS_LOG(WUEPS_PID_SPY, 0, PS_PRINT_ERROR,    string)

#define SPY_INFO1_LOG(string, para1)        PS_LOG1(WUEPS_PID_SPY, 0, PS_PRINT_INFO,   string, para1)
#define SPY_NORMAL1_LOG(string, para1)      PS_LOG1(WUEPS_PID_SPY, 0, PS_PRINT_NORMAL, string, para1)
#define SPY_WARNING1_LOG(string, para1)     PS_LOG1(WUEPS_PID_SPY, 0, PS_PRINT_WARNING,string, para1)
#define SPY_ERROR1_LOG(string, para1)       PS_LOG1(WUEPS_PID_SPY, 0, PS_PRINT_ERROR,  string, para1)

#define SAR_NORMAL_LOG(string)              PS_LOG(WUEPS_PID_SAR, 0, PS_PRINT_NORMAL,   string)
#define SAR_WARNING_LOG(string)             PS_LOG(WUEPS_PID_SAR, 0, PS_PRINT_WARNING,  string)
#define SAR_ERROR_LOG(string)               PS_LOG(WUEPS_PID_SAR, 0, PS_PRINT_ERROR,    string)


#define SPY_TEMP_THRESHOLD_PARA_CHANGE      1          /* 需要更新该参数 */
#define SPY_TEMP_THRESHOLD_PARA_UNCHANGE    0          /* 无需更新该参数*/

#define SPY_TEMP_THRESHOLD_PARA_INVALID     0xFFFFFFFF /*无效门限值或使能位的值*/

/*定义了监控任务的定时器时长*/
#define SPY_TIMER_LEN                       1000

/*定义流控定时器时长*/
#define SPY_FLOW_CTRL_TIMER_LEN  \
        (g_stTempProtectNv.stTempCtrlPara.ulWaitTimer * 1000)

/*定义流控定时器名称*/
#define TIMER_FLOWCTRL                      2
/*定义了各个监控点的投票值*/
#define SPY_VOTE_POWEROFF                   (-5)    /*当前需要下电*/
#define SPY_VOTE_SOFTDOWN                   (-4)    /*当前需要软关机*/
#define SPY_VOTE_QOSDOWN                    (-3)
#define SPY_VOTE_TEMPWAIT                   (-1)    /*当前需要进行温度调节后的等待*/
#define SPY_VOTE_RESUME                     (1)     /*当前需要软开机*/
#define SPY_VOTE_NOMAL                      (255)   /*当前不需要动作*/


#define SPY_TEMP_MAX_INTERVAL               5

/*定义了ADC对应的电压值*/
#define SPY_BATTERY_MAX_VOLT                4200
#define SPY_BATTERY_MIN_VOLT                3400


#define GET_TEMP_INTERVAL(oldTemp, newTemp) \
        ((oldTemp > newTemp)? (oldTemp - newTemp):(newTemp - oldTemp))

#define SPY_GET_LOW_RATE(A,B) (((A)<(B))?(A):(B))
#define SPY_GET_MAX_RATE(A,B) (((A)>(B))?(A):(B))

#define TEMP_CLOSE_ITEM                     0x01
#define TEMP_ALARM_ITEM                     0x02
#define TEMP_RESUME_ITEM                    0x04
#define TEMP_POWEROFF_ITEM                  0x08
#define TEMP_ALL_ITEM                       0x0F

#define USIM_TEMP_TABLE_LEN                 19

#define SPY_QOS_CHANGED_FLAG                1
#define SPY_QOS_UNCHANGED_FLAG              0

#define TEMP_CLOSE_ADC_COUNT  \
        g_stTempProtectNv.stTempCtrlPara.ucTempCloseCount

#define TEMP_ALARM_ADC_COUNT  \
        g_stTempProtectNv.stTempCtrlPara.ucTempOverCount

#define TEMP_POWEROFF_ADC_COUNT \
        g_stTempProtectNv.stTempCtrlPara.ucTempPowerOffCount

#define TEMP_RESUME_ADC_COUNT \
        g_stTempProtectNv.stTempCtrlPara.ucTempRsumeCount

#define TEMP_CLOSE_THRESHOLD  \
        g_stTempProtectNv.lCloseAdcThreshold

#define TEMP_ALARM_THRESHOLD  \
        g_stTempProtectNv.lAlarmAdcThreshold

#define TEMP_POWEROFF_THRESHOLD  \
        g_stTempProtectNv.lPowerOffThreshold

#define TEMP_RESUME_THRESHOLD \
        g_stTempProtectNv.lResumeAdcThreshold

#define TEMP_SIM_POWEROFF_THRESHOLD \
        g_stTempProtectNv.lSIMPowerOffThreshold

#define TEMP_CLOSE_TIMER_LEN  \
        (g_stTempProtectNv.stTempCtrlPara.ulWaitTimer)

#define TEMP_ALARM_TIMER_LEN  \
        g_stTempProtectNv.stTempCtrlPara.ulAlarmTimer

/* SPY统计调试信息开关宏 */
#define SPY_STATISTICS_DEBUG

#define SPY_SAR_ANTEN_STATUS_IND        0x0001

#define SPY_TEMP_PARA_SIZE              (16)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*定义了投票结果的 */
enum SPY_VOTERESULT_ENUM
{
    SPY_VOTERESULT_NULL          =0,    /*当前不需要动作*/
    SPY_VOTERESULT_DEFQOS        =1,    /*当前需要恢复Qos到用户原始值*/
    SPY_VOTERESULT_PSON          =2,    /*当前需要开机*/
    SPY_VOTERESULT_DOWNQOS       =3,     /*当前需要进行流控下调*/
    SPY_VOTERESULT_PSOFF,                /*当前需要软关机*/
    SPY_VOTERESULT_POWEROFF,             /*当前需要下电*/
    SPY_VOTERESULT_BUTT
};

typedef VOS_UINT32  SPY_VOTERESULT_ENUM_UINT32;

/*定义了系统状态*/
enum SPY_STATE_ENUM
{
    SPY_STATE_NORMAL            =0, /*当前处于正常态*/
    SPY_STATE_QOS               =1, /*当前处于调节Qos后状态*/
    SPY_STATE_PSOFF             =2, /*当前处于关机状态*/
    SPY_STATE_BUTT
};

typedef VOS_UINT32 SPY_STATE_ENUM_UINT32;

/*定义了当前CPU检测的状态*/
enum CHECKCPU_STATE_ENUM
{
    SPY_CHECKCPUSTART           =0,   /*开始查询CPU占有率，需要记录初始值*/
    SPY_CHECKCPUALREAD          =1,   /*已经开始查询CPU占有率，需要根据上一次记录的值和本次查询的差，计算CPU占有率*/
    SPY_CHECKCPU_BUTT
};
typedef VOS_UINT32 CHECKCPU_STATE_ENUM_UINT32;

enum SPY_EVENT_NAME_ENUM
{
    SPY_EVENT_TEMP_OVER_HIGH = 1,
    SPY_EVENT_TEMP_RESUME,
    SPY_EVENT_CPU_OVER_HIGH,
    SPY_EVENT_CPU_LOW,
    SPY_EVENT_VOTE_RESULT,
    SPY_EVENT_DFS_CHANGED,             /* 调频事件 */
    SPY_EVENT_BUTT
};
typedef VOS_UINT32 SPY_EVENT_NAME_ENUM_UINT32;

enum TEMP_ENABLE_ENUM
{
    TEMP_CLOSE_STATE = 0,
    TEMP_ENABLE_STATE,
    TEMP_ENABLE_BUTT
};
typedef VOS_UINT32 TEMP_ENABLE_ENUM_UINT32;


enum TMEP_STATE_ENUM
{
    TEMP_NORMAL_STATE = 0,
    TEMP_WAIT_STATE,
    TEMP_STATE_BUTT
};
typedef VOS_UINT32 TEMP_STATE_ENUM_UINT32;

/*SIM温度变化超限标记*/
enum SIM_TEMP_FLAG_ENUM
{
    SIM_TEMP_LOW_FLAG   =0,
    SIM_TEMP_HIGH_FLAG  =1,
    SIM_TEMP_FLAG_BUTT
};

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/

/*定义了通用消息结构*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgName;      /* 消息类型 */
    VOS_UINT32                  ulResult;
    VOS_INT32                   lAntenStatus;   /* 天线状态 */
    MODEM_ID_ENUM_UINT16        enModemID;      /* 卡ID */
    VOS_UINT16                  usRsv;
}SPY_MSG_STRU;

/*****************************************************************************
  6 消息定义
*****************************************************************************/



/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*定义了系统当前状态*/
typedef struct
{
    VOS_UINT32                  ulCurPSStatus;      /*当前系统的开机状态*/
}SPY_SYSCUR_STATUS;

typedef struct
{
    TEMP_ENABLE_ENUM_UINT32     enTempEnable;           /*当前系统温度监控始能开关*/
    TEMP_STATE_ENUM_UINT32      enTempState;           /*当前系统状态，见a)中描述*/
    VOS_UINT32                  ulTempCloseCount;      /*关机温度计数器*/
    VOS_UINT32                  ulTempAlarmCount;      /*告警温度计数器*/
    VOS_UINT32                  ulTempPowerOffCount;   /*下电温度计数器*/
    VOS_UINT32                  ulTempResumeCount;     /*正常温度计数器*/
    VOS_UINT32                  ulTempWaitTimeLen;     /*当系统状态变化时，需要等待的时间长度*/
    VOS_UINT32                  ulBatteryTempAlarmCount ; /*用于记录当前的电池超过门限次数*/
    VOS_INT                     lOldTemperature;       /*上一次查询到的温度*/
}SPY_TEMP_STATE_CTRL_STRU;

typedef struct
{
    VOS_UINT16                  usMinADC;/*3.4 V电压时的ADC值*/
    VOS_UINT16                  usMaxADC;/* 4.2 V电压时的ADC值*/
}NVIM_Battery_STRU;

typedef struct
{
    VOS_UINT32      ulFlag;
    VOS_INT32       lTempThreshold;
    VOS_UINT32      ulMaxNum;
}NVIM_E5_TEMP_PROTECT_STRU;

#ifdef SPY_STATISTICS_DEBUG
typedef struct
{
    VOS_UINT32                          ulFlowCtrlDownNum;
    VOS_UINT32                          ulFlowCtrlUpNum;
    VOS_UINT32                          ulSoftPowerOffNum;
    VOS_UINT32                          ulSoftPowerOnNum;
    VOS_UINT32                          ulPowerOffNum;
}SPY_STATISTICS_INFO_STRU;

#define SPY_RECORD_NUM 100
typedef struct
{
    VOS_UINT32      ulTime;
    VOS_CHAR        acType[16];
} SPY_TIME_STRU;
typedef struct
{
    VOS_UINT32      ulCount;
    SPY_TIME_STRU   astRecord[SPY_RECORD_NUM];
} SPY_RECORD_STRU;
#endif


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
extern SPY_TEMP_STATE_CTRL_STRU        g_stTempStateCtrl; /*保存当前温度保护模块的状态*/

extern HTIMER                          g_stSpyFlowCtrlTimer;

/*****************************************************************************
  10 函数声明
*****************************************************************************/

extern VOS_UINT8 MMA_GetCurrentPhoneMode(VOS_VOID);

extern VOS_UINT32 SHPA_GetRateType(MODEM_ID_ENUM_UINT16 enModemID);

extern VOS_VOID Spy_ReportEvent(SPY_EVENT_NAME_ENUM_UINT32 enEventId, VOS_INT lSimTemp);

extern VOS_UINT32 Spy_SarMsgProc(MsgBlock *pMsg);

extern VOS_UINT32 Spy_SoftPowerOff(VOS_VOID);

extern VOS_UINT32 Spy_SysCtrlCmd(VOS_UINT8 usOpId, VOS_UINT16 usClientId, VOS_UINT32 ulMode, MODEM_ID_ENUM_UINT16 enModemID);

extern VOS_VOID Spy_SendAntenStatusToLte(MODEM_ID_ENUM_UINT16 enModemID, VOS_INT32 lAntenStatus);


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif




