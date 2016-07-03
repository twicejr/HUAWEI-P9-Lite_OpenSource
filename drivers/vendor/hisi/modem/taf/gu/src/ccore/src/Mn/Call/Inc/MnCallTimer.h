

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

    TAF_CALL_TID_DTMF_ON_LENGTH,               /* start dtmf ack和stop dtmf req之间的时间间隔定时器 */
    TAF_CALL_TID_DTMF_OFF_LENGTH,              /* stop dtmf ack 和start dtmf req之间的时间间隔定时器 */

    TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD,                                       /* eCall重拨时长定时器 */
    TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL,                                     /* eCall重拨间隔定时器 */
    TAF_CALL_TID_T2,                                                             /* eCall通话时长定时器 */
    TAF_CALL_TID_T9,                                                             /* 等待MT eCall时长定时器 */

    MN_CALL_TID_BUTT
};
typedef VOS_UINT32  MN_CALL_TIMER_ID_ENUM_U32;


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

extern VOS_VOID  MN_CALL_ProcTimeoutMsg(
    REL_TIMER_MSG                       *pTmrMsg
);


extern VOS_VOID  MN_CALL_StartTimer(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId,
    VOS_UINT32                          ulParam,
    VOS_UINT32                          ulLength,
    VOS_UINT8                           ucTimerMode
);


extern VOS_VOID MN_CALL_StopTimer(
    MN_CALL_TIMER_ID_ENUM_U32            enTimerId
);


extern VOS_VOID  MN_CALL_InitAllTimers(MN_CALL_POWER_STATE_ENUM_U8 enPowerState);


extern VOS_VOID  MN_CALL_CstSetupTimeout(
    VOS_UINT32                          ulParam
);


VOS_VOID MN_CALL_RingTimerTimeout(
    VOS_UINT32                          ulParam
);



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



VOS_VOID TAF_CALL_RcvTiDtmfOnLengthExpired(
    VOS_UINT32                          ulParam
);

VOS_VOID TAF_CALL_RcvTiDtmfOffLengthExpired(
    VOS_UINT32                          ulParam
);

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
