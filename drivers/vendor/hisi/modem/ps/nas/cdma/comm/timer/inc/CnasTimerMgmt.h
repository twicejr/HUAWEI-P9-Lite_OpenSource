/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasTimerMgmt.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年06月28日
  功能描述   : CnasTimerMgmt.c头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月28日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/
#ifndef _CNAS_TIMER_MGMT_H_
#define _CNAS_TIMER_MGMT_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 注: 暂定义CANS启动timer的最大数目为20，待后续确定每个模块同时启动定时器的最大数目时调整 */
#define CNAS_MAX_TIMER_RUNNING_NUM                          (20)

#define CNAS_TIMER_TICK                                     (10)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : CNAS_TIMER_STATUS_ENUM
 枚举说明  : 定时器状态ID枚举定义
 1.日    期   : 2014年07月03日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum CNAS_TIMER_STATUS_ENUM
{
    CNAS_TIMER_STATUS_STOP                              = 0x00,

    CNAS_TIMER_STATUS_RUNNING                           = 0x01,

    CNAS_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 CNAS_TIMER_STATUS_ENUM_UINT8;

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
/*****************************************************************************
 结构名    : CNAS_TIMER_INFO_STRU
 结构说明  : CNAS定时器信息结构

 1.日    期   : 2014年07月03日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTimerId;          /* 定时器标识 */
    VOS_UINT32                          ulParam;            /* 定时器参数标识, 如相同timer ID不同交易标识 */
    VOS_UINT32                          ulTimerLen;         /* 定时器时长 */
    VOS_UINT32                          ulTimerPrecision;   /* 定时器精度 */
}CNAS_TIMER_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_TIMER_CTX_STRU
 结构说明  : CNAS定时器信息结构

 1.日    期   : 2014年07月03日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    HTIMER                              pTimerHandle;       /* timer 句柄*/
    VOS_UINT32                          ulPid;              /* 启动timer的PID任务 */
    VOS_UINT32                          ulParam;            /* 定时器参数标识 */
    VOS_UINT32                          ulTimerId;          /* timer标识 */
    CNAS_TIMER_STATUS_ENUM_UINT8        enTimerStatus;      /* 定时器的运行状态,启动或停止 */
    VOS_UINT8                           aucReserved1[3];    /* 字节对齐保留位 */
}CNAS_TIMER_CTX_STRU;
/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
CNAS_TIMER_CTX_STRU* CNAS_GetTimerCtxAddr(VOS_VOID);

VOS_VOID CNAS_InitTimerCtx(VOS_VOID);

CNAS_TIMER_CTX_STRU* CNAS_GetAFreeTimerCtx(VOS_VOID);

VOS_VOID CNAS_StartTimer(
    VOS_UINT32                          ulPid,
    CNAS_TIMER_INFO_STRU               *pstTimerInfo
);

VOS_VOID CNAS_RestartTimer(
    VOS_UINT32                          ulPid,
    CNAS_TIMER_INFO_STRU               *pstTimerInfo
);

VOS_VOID CNAS_StopTimer(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ucTimerId,
    VOS_UINT32                          ulPara
);

VOS_VOID CNAS_StopAllTimerWithSpecifiedPid(
    VOS_UINT32                          ulPid
);

CNAS_TIMER_CTX_STRU* CNAS_GetSpecifiedTimerCtx(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulTimerId,
    VOS_UINT32                          ulPara
);

CNAS_TIMER_STATUS_ENUM_UINT8 CNAS_GetSpecifiedTimerStatus(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulTimerId,
    VOS_UINT32                          ulParam
);

VOS_UINT32 CNAS_GetSpecifiedTimerRemainLen(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ucTimerId,
    VOS_UINT32                          ulPara
);

#endif

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

#endif /* end of CnasTimerMgmt.h */
