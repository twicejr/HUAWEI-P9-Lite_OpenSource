/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : SleepSleep.h
  版 本 号   : 初稿
  作    者   : zuowen
  生成日期   : 2005年3月7日
  最近修改   :
  功能描述   : SleepSleep.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2005年3月7日
    作    者   : zuowen
    修改内容   : 创建文件
  2.日    期   : 2006年4月13日
    作    者   : w45442
    修改内容   : 修改问题单A32D03034

******************************************************************************/
#ifndef __SLEEPSLEEP_H__
#define __SLEEPSLEEP_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define DSP_PLL_LOCK   0  /* DSP PLL的锁相环输出稳定 */
#define DSP_PLL_UNLOCK 1  /* DSP PLL的锁相环输出不稳定 */

/* SLEEP 模块控制变量 */
#define CURRENT_MODULE_SLEEP    (0)
#define CURRENT_MODULE_RUN      (1)

/* 从模低功耗控制变量 */
#define SLAVE_MODULE_SLEEP      (0)
#define SLAVE_MODULE_RUN        (1)

#define HPA_LOAD_PHY_TRACE_NUM  (5)
#define SLEEP_RECORD_TRACK_NUM  (3)

#define SLEEP_BBE16_RECORD_TRACK_NUM  (3)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

typedef struct
{
    VOS_UINT32 ulSystemState;
    VOS_UINT32 ulSlaveSystemState;   /* 从模低功耗状态 */
    VOS_UINT32 ulDspPllState;        /* DSP PLL 的状态 0 已关闭 1 未关闭 */
    VOS_UINT32 ulBbpPllState;        /* BBP PLL 的状态 0 已关闭 1 未关闭 */
    VOS_UINT32 ulRfLdoState;         /* RF LDO 的状态 0 已关闭 1 未关闭 */
    VOS_UINT32 ulMpuState;           /* MPU 的状态 0 SLEEP 状态 1 NORMAL 状态 */
}SLEEP_CTRL_STRU;

typedef struct
{
    VOS_UINT32 ulCount;              /* 记录发生的次数 */
    VOS_UINT32 ulSlice;              /* 记录发生的Slice值 */
}SLEEP_RECORD_STRU;

/*****************************************************************************
 结构名    : SLEEP_RECORD_TRACK_STRU
 结构说明  : 记录低功耗处理时间轨迹
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulCount;                         /* 记录发生的次数 */
    VOS_UINT32 aulSlice[SLEEP_RECORD_TRACK_NUM]; /* 记录发生的Slice值 */
}SLEEP_RECORD_TRACK_STRU;

/*****************************************************************************
 结构名    : SLEEP_BBE16_RECORD_TRACK_STRU
 结构说明  : 记录X模低功耗处理时间轨迹
*****************************************************************************/
typedef struct
{
    VOS_CHAR*  pucTrackId;                              /* 状态名 */
    VOS_UINT32 ulCount;                                 /* 记录发生的次数 */
    VOS_UINT32 aulSlice[SLEEP_BBE16_RECORD_TRACK_NUM];  /* 记录发生的Slice值 */
}SLEEP_BBE16_RECORD_TRACK_STRU;

typedef struct
{
    /*搜网低功耗流程*/
    SLEEP_RECORD_STRU  stEnterLowPowerErr;  /*记录进入低功耗模式失败 */
    SLEEP_RECORD_STRU  stLowPowerIpc;       /*记录发送IPC中断通知DSP进入HALT */
    SLEEP_RECORD_STRU  stExitLowPowerRet;   /*记录当前不在低功耗下，调用出低功耗函数 */
    SLEEP_RECORD_STRU  stLowPowerNMI;       /*记录发送NMI中断唤醒DSP */

    /*飞行模式流程*/
    SLEEP_RECORD_STRU  stFlyModeIpc;        /*记录发送IPC中断通知DSP进入HALT */
    SLEEP_RECORD_STRU  stFlyModeNMI;        /*记录发送NMI中断唤醒DSP */

    /*CONNET&IDLE记录*/
    SLEEP_RECORD_STRU  stConnectMode;       /*记录DSP通知ARM进入连接态时 */
    SLEEP_RECORD_STRU  stIdleMode;          /*记录DSP通知ARM进入IDLE态时 */

    SLEEP_RECORD_STRU  stWDrxReadPcchData;  /*记录在DSP进入HALT后通知层二读取数据面邮箱*/
}LOWPOWER_STATE_STRU;


typedef struct
{
    SLEEP_RECORD_STRU  stLoadHifiReq;       /* 记录加载HIFI */
    SLEEP_RECORD_STRU  stLoadTimeout;       /* 记录加载HIFI超时 */
    SLEEP_RECORD_STRU  stHifiLoadIpc;       /* 记录加载HIFI中断回复 */
    SLEEP_RECORD_STRU  stHifiSleepIpc;      /* 记录HIFI睡眠请求 */
    SLEEP_RECORD_STRU  stHifiStateErr;      /* 记录HIFI状态不正确 */
}HIFI_STATE_STRU;

typedef struct
{
    VOS_UINT32 ulPAState;                                           /* 记录PA状态 0 为下电 1 为上电 */
    VOS_UINT32 ulRFState;                                           /* 记录RF状态 0 为下电 1 为上电 */
    VOS_UINT32 ulBBPSocPwState;                                     /* 记录BBP SOC状态  0 为下电 1 为上电 */
    VOS_UINT32 ulBBPPwState;                                        /* 记录BBP PW状态 0 为下电 1 为上电 */
    VOS_UINT32 ulDspPwState;                                        /* 记录DSP PW状态 0 为下电 1 为上电 */
    VOS_UINT32 ulABBPwState;                                        /* 记录ABB PW状态 0 为下电 1 为上电 */
    VOS_UINT32 ulDspPllState;                                       /* 记录DSP PLL状态 0 为关闭 1 为开启 */
    VOS_UINT32 ulBBPPllState;                                       /* 记录BBP PLL状态 0 为关闭 1 为开启*/
}SLEEP_SLAVE_CTRL_STRU;

/* 从模低功耗记录 */
typedef struct
{
    SLEEP_RECORD_STRU       astEnterSlaveMode[PWC_COMM_MODE_BUTT];      /* 记录进入从模低功耗 组1为W 组2为G 组3为L(不使用) */
    SLEEP_RECORD_STRU       astEnterSlaveModeErr[PWC_COMM_MODE_BUTT];   /* 记录进入从模低功耗失败 组1为W 组2为G 组3为L(不使用) */
    SLEEP_RECORD_STRU       astExitSlaveMode[PWC_COMM_MODE_BUTT];       /* 记录退出从模低功耗 组1为W 组2为G 组3为L(不使用) */
    SLEEP_RECORD_STRU       astExitSlaveModeErr[PWC_COMM_MODE_BUTT];    /* 记录退出从模低功耗失败 组1为W 组2为G 组3为L(不使用) */
    SLEEP_RECORD_STRU       stActiveHw;                                 /* 记录上电状态 */
    SLEEP_RECORD_STRU       stDeactiveHw;                               /* 记录下电状态 */
    SLEEP_SLAVE_CTRL_STRU   astSlaveRTTState[PWC_COMM_MODE_BUTT];       /* 记录RTT子系统状态 组1为W 组2为G 组3为L(不使用) */
}SLAVE_LOW_POWER_STATE_STRU;

typedef struct
{
    VOS_UINT32              ulloadPhyStart;
    VOS_UINT32              ulLoadPhyReqCount;
    VOS_UINT32              ulLoadPhyReqTime[HPA_LOAD_PHY_TRACE_NUM];
    VOS_UINT32              ulLoadPhyCnfCount;
    VOS_UINT32              ulLoadPhyCnfTime[HPA_LOAD_PHY_TRACE_NUM];
    VOS_UINT32              ulLoadPhyCnfResult[HPA_LOAD_PHY_TRACE_NUM];
    VOS_UINT32              ulLoadPhyCount;
    VOS_UINT32              ulLoadPhySuccessCount;
    VOS_UINT32              ulLoadPhyFailCount;
    VOS_UINT32              ulLoadPhyState;
    VOS_UINT32              ulLoadPhyErrMsgIdCnt;
    VOS_UINT32              ulLoadPhyErrMsgId;
    VOS_UINT32              ulLoadPhyErrResult;
    VOS_UINT32              ulLoadPhyErrMsgIdSlice[HPA_LOAD_PHY_TRACE_NUM];
    VOS_UINT32              ulLoadPhyIpcCount;
    VOS_UINT32              ulLoadPhyIpcSlice[HPA_LOAD_PHY_TRACE_NUM];
    VOS_UINT32              ulLoadPhyIpcMask[HPA_LOAD_PHY_TRACE_NUM];
    VOS_UINT32              ulLoadPhyIpcClearMask[HPA_LOAD_PHY_TRACE_NUM];
    VOS_UINT32              ulLoadPhyResult;
    VOS_UINT32              ulLoadPhyResultSlice;
}HPA_LOAD_PHY_STATE_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

extern HIFI_STATE_STRU              *g_pstHifiStateSlice;
extern HPA_LOAD_PHY_STATE_STRU      *g_pstLoadPhyState;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __SLEEPSLEEP_H__ */
