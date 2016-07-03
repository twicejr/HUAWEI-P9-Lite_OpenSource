
#ifndef  NAS_CC_TIMER_PROC_H
#define  NAS_CC_TIMER_PROC_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasCcCommon.h"


/*****************************************************************************
  2 类型定义
*****************************************************************************/

#define TI_NAS_CC_T303_DEFAULT_LEN                          (30)                /* T303定时器默认时长，单位:秒 */

/* CC定时器ID定义 */
typedef enum
{
    TI_NAS_CC_T303,
    TI_NAS_CC_T305,
    TI_NAS_CC_T308,
    TI_NAS_CC_T310,
    TI_NAS_CC_T313,
    TI_NAS_CC_T323,
    TI_NAS_CC_T332,
    TI_NAS_CC_T335,
    TI_NAS_CC_T336,
    TI_NAS_CC_T337,
    TI_NAS_CC_HOLD,                                                             /* 呼叫保持/恢复操作的定时器 */
    TI_NAS_CC_MPTY,                                                             /* MPTY操作的定时器 */
    TI_NAS_CC_ECT,
    TI_NAS_CC_USER_CONN,                                                        /* 用户连接定时器 */
    TI_NAS_CC_RABMINACT_PROTECT,                                                        /* 用户连接定时器 */
    TI_NAS_CC_MAX
} NAS_CC_TIMER_ID_ENUM;

/* 启动T308的次数 */
enum
{
    NAS_CC_T308_FIRST                                       = 1,
    NAS_CC_T308_SECOND
};


/*****************************************************************************
  3 函数声明
*****************************************************************************/


VOS_UINT8 NAS_CC_GetNvTimerLen(
    NAS_CC_TIMER_ID_ENUM                enTimerId,
    VOS_UINT32                         *ulTimerLen
);


VOS_VOID NAS_CC_SetNvTimerLen(
    NAS_CC_TIMER_ID_ENUM                enTimerId,
    VOS_UINT32                          ulTimerLen
);


VOS_VOID  NAS_CC_InitAllTimers(VOS_VOID);



VOS_VOID  NAS_CC_StartTimer(
    NAS_CC_ENTITY_ID_T                  EntityId,
    NAS_CC_TIMER_ID_ENUM                enTimerId,
    VOS_UINT32                          ulParam
);


VOS_UINT32 NAS_CC_GetTimerLength(
    NAS_CC_TIMER_ID_ENUM                enTimerId
);


VOS_VOID  NAS_CC_StopTimer(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_TIMER_ID_ENUM                enTimerId
);



VOS_VOID  NAS_CC_StopAllTimer(
    NAS_CC_ENTITY_ID_T                  entityId
);



VOS_VOID  NAS_CC_ProcTimeoutMsg(
    VOS_VOID                            *pMsg
);


VOS_VOID  NAS_CC_StopAllRunningTimer(VOS_VOID);



VOS_VOID  NAS_CC_StartRabProtectTimer(VOS_VOID);


VOS_VOID  NAS_CC_StopRabProtectTimer(VOS_VOID);


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

#endif /* NAS_CC_TIMER_PROC_H */

