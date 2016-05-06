/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallTimer.h
  版 本 号   : 初稿
  作    者   : dfakl;f
  生成日期   : 2010年5月19日
  最近修改   :
  功能描述   : MnCallTimer.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2010年5月19日
    作    者   : dfakl;f
    修改内容   : 创建文件

******************************************************************************/

#ifndef __MNCALLTIMER_H__
#define __MNCALLTIMER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "MnComm.h"
#include "MnCallMgmt.h"


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define MN_CALL_TIMER_TICK              (10)


/*****************************************************************************
  3 枚举定义
*************************************************************************/
/*CALL模块定时器ID的定义*/
enum MN_CALL_TIMER_ID_ENUM
{
    MN_CALL_TID_WAIT_CST_SETUP           = MN_TIMER_CLASS_CCA,                  /* 向CST模块发送SETUP消息之后，启动该定时器，用于保护 */
    MN_CALL_TID_RING,
    
    /* FDN与CALL control检查移到SPM，这里定时器ID删除 */

    MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD,
    MN_CALL_TID_WAIT_CALL_REDAIL_INTERVAL,

    /* Added by l00198894 for V9R1 STK升级, 2013/07/11, begin */
    TAF_CALL_TID_DTMF_ON_LENGTH,               /* start dtmf ack和stop dtmf req之间的时间间隔定时器 */
    TAF_CALL_TID_DTMF_OFF_LENGTH,              /* stop dtmf ack 和start dtmf req之间的时间间隔定时器 */
    /* Added by l00198894 for V9R1 STK升级, 2013/07/11, end */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-1, begin */
    TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD,                                       /* eCall重拨时长定时器 */
    TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL,                                     /* eCall重拨间隔定时器 */
    TAF_CALL_TID_T2,                                                             /* eCall通话时长定时器 */
    TAF_CALL_TID_T9,                                                             /* 等待MT eCall时长定时器 */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-1, end */

    MN_CALL_TID_BUTT
};
typedef VOS_UINT32  MN_CALL_TIMER_ID_ENUM_U32;

/*****************************************************************************
 枚举名    : MN_CALL_TIMER_STATUS_ENUM_U8
 结构说明  : call定时器状态,停止或运行
  1.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : 新建
*****************************************************************************/
enum MN_CALL_TIMER_STATUS_ENUM
{
    MN_CALL_TIMER_STATUS_STOP,              /* 定时器停止状态 */
    MN_CALL_TIMER_STATUS_RUNING,            /* 定时器运行状态 */
    MN_CALL_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 MN_CALL_TIMER_STATUS_ENUM_U8;





/*****************************************************************************
  4 类型定义
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
/* 超时处理函数的类型定义 */
typedef VOS_VOID (* MN_CALL_TIMEOUT_PROC_FUNC)(VOS_UINT32 ulParam);


typedef struct
{
    HTIMER                              hTimer;
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId;

    MN_CALL_TIMER_STATUS_ENUM_U8        enTimerStatus;                          /* 定时器的运行状态,启动或停止 */
    VOS_UINT8                           aucReserved1[3];
}MN_CALL_TIMER_HANDLE_STRU;

/* 定时器信息结构 */
typedef struct
{
    VOS_UINT32                          ulTimeout;
    MN_CALL_TIMEOUT_PROC_FUNC           pfnTimeoutProc;
} MN_CALL_TIMER_INFO_STRU;




/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : MN_CALL_ProcTimeoutMsg
 功能描述  : 处理定时器超时消息。
 输入参数  : pMsg  - 定时器超时消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月20日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_VOID  MN_CALL_ProcTimeoutMsg(
    REL_TIMER_MSG                       *pTmrMsg
);

/*****************************************************************************
 函 数 名  : MN_CALL_StartTimer
 功能描述  : 启动指定的定时器
 输入参数  : enTimerId:指定定时器TimerId
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月20日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_VOID  MN_CALL_StartTimer(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId,
    VOS_UINT32                          ulParam,
    VOS_UINT32                          ulLength,
    VOS_UINT8                           ucTimerMode
);

/*****************************************************************************
 函 数 名  : MN_CALL_StopTimer
 功能描述  : 停止指定的定时器
 输入参数  : enTimerId:指定定时器TimerId
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月20日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_VOID MN_CALL_StopTimer(
    MN_CALL_TIMER_ID_ENUM_U32            enTimerId
);

/*****************************************************************************
 函 数 名  : MN_MSG_InitAllTimers
 功能描述  : 初始化所有定时器，应在初始化及Reset时被调用
 输入参数  : enPowerState - 开机或关机
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月20日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_VOID  MN_CALL_InitAllTimers(MN_CALL_POWER_STATE_ENUM_U8 enPowerState);

/*****************************************************************************
 函 数 名  : MN_CALL_CstSetupTimeout
 功能描述  : 处理发给CST模块的setup消息的超时处理
 输入参数  : ulParam:定时器参数
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月20日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_VOID  MN_CALL_CstSetupTimeout(
    VOS_UINT32                          ulParam
);

/*****************************************************************************
 函 数 名  : MN_CALL_RingTimerTimeout
 功能描述  : 循环定时器，如果超时的时候，通知上层Incoming
 输入参数  : ulParam:定时器参数
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月20日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_RingTimerTimeout(
    VOS_UINT32                          ulParam
);

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */

VOS_VOID MN_CALL_UpdateTimerPeriod(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId,
    VOS_UINT32                          ulTimerLen
);
VOS_VOID MN_CALL_CallRedialPeriodTimeout(VOS_UINT32 ulParam);

VOS_VOID MN_CALL_CallRedialIntervalTimeout(VOS_UINT32 ulParam);

VOS_UINT32  MN_CALL_GetTimerRemainLen(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId
);

VOS_UINT32 MN_CALL_GetTimerLen(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId
);

MN_CALL_TIMER_STATUS_ENUM_U8  MN_CALL_GetTimerStatus(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId
);



/* Added by l00198894 for V9R1 STK升级, 2013/07/11, begin */
VOS_VOID TAF_CALL_RcvTiDtmfOnLengthExpired(
    VOS_UINT32                          ulParam
);
/* Added by l00198894 for V9R1 STK升级, 2013/07/11, end */

VOS_VOID TAF_CALL_RcvTiDtmfOffLengthExpired(
    VOS_UINT32                          ulParam
);

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-1, begin */
VOS_UINT32 TAF_CALL_GetTimerLen(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId
);

#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID TAF_CALL_EcallRedialPeriodTimeout(VOS_UINT32 ulParam);

VOS_VOID TAF_CALL_EcallRedialIntervalTimeout(VOS_UINT32 ulParam);

VOS_VOID TAF_CALL_RcvT2TimerExpired(
    VOS_UINT32                          ulParam
);

VOS_VOID TAF_CALL_RcvT9TimerExpired(
    VOS_UINT32                          ulParam
);
#endif

VOS_VOID TAF_CALL_StopAllRedialTimers(VOS_UINT8 ucCallId);

VOS_UINT32 TAF_CALL_GetRedialIntervalTimerLen(VOS_UINT8 ucCallId);

VOS_UINT32 TAF_CALL_GetRemainRedialPeriodTimerLen(VOS_UINT8 ucCallId);

VOS_VOID TAF_CALL_StartRedialPeriodTimer(VOS_UINT8 ucCallId);

MN_CALL_TIMER_STATUS_ENUM_U8 TAF_CALL_GetRedialIntervalTimerStatus(VOS_UINT8 ucCallId);
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-1, end */

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MnCallTimer.h */
