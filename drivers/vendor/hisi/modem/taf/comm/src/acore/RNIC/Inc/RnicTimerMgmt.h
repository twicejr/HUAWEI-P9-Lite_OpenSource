

#ifndef __RNIC_TIMERMGMT_H__
#define __RNIC_TIMERMGMT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "product_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* RNIC中同时运行的定时器的最大数目 */
#define RNIC_MAX_TIMER_NUM                      (TI_RNIC_TIMER_BUTT)

#define TI_RNIC_UNIT                            (1000)                          /* 1s = 1000ms */

#define TI_RNIC_DSFLOW_STATS_LEN                (2000)                          /* 2秒统计一次速率 */
#define TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN      (10000)                         /* 10秒拨号断开定时器 */
#define TI_RNIC_DEMAND_DIAL_PROTECT_LEN         (1000)                          /* 1秒拨号保护定时器 */

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
#if  (MULTI_MODEM_NUMBER == 3)
#define RNIC_IS_DSFLOW_TIMER_ID(enTimerId)          \
            ((TI_RNIC_DSFLOW_STATS_0 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_1 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_2 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_3 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_4 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_5 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_6 == (enTimerId)))
#else
#define RNIC_IS_DSFLOW_TIMER_ID(enTimerId)          \
            ((TI_RNIC_DSFLOW_STATS_0 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_1 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_2 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_3 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_4 == (enTimerId)))
#endif /* #if (MULTI_MODEM_NUMBER == 3) */
#else
#define RNIC_IS_DSFLOW_TIMER_ID(enTimerId)          \
            ((TI_RNIC_DSFLOW_STATS_0 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_1 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_2 == (enTimerId)))
#endif

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


enum RNIC_TIMER_ID_TYPE_ENUM
{
    TI_RNIC_DEMAND_DIAL_DISCONNECT,                                             /* 按需拨号断开定时器 */
    TI_RNIC_DEMAND_DIAL_PROTECT,                                                /* 按需拨号保护定时器 */
    TI_RNIC_DSFLOW_STATS_0,                                                     /* 网卡0的2秒的流量统计定时器 */
    TI_RNIC_DSFLOW_STATS_1,                                                     /* 网卡1的2秒的流量统计定时器 */
    TI_RNIC_DSFLOW_STATS_2,                                                     /* 网卡2的2秒的流量统计定时器 */
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    TI_RNIC_DSFLOW_STATS_3,                                                     /* 网卡3的2秒的流量统计定时器 */
    TI_RNIC_DSFLOW_STATS_4,                                                     /* 网卡4的2秒的流量统计定时器 */
#if  (MULTI_MODEM_NUMBER == 3)
    TI_RNIC_DSFLOW_STATS_5,                                                     /* 网卡5的2秒的流量统计定时器 */
    TI_RNIC_DSFLOW_STATS_6,                                                     /* 网卡6的2秒的流量统计定时器 */
#endif /* #if (MULTI_MODEM_NUMBER == 3) */
#endif
    TI_RNIC_TIMER_BUTT
};
typedef VOS_UINT16 RNIC_TIMER_ID_ENUM_UINT16;


enum RNIC_TIMER_STATUS_ENUM
{
    RNIC_TIMER_STATUS_STOP,                                                     /* 定时器停止状态 */
    RNIC_TIMER_STATUS_RUNING,                                                   /* 定时器运行状态 */
    RNIC_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 RNIC_TIMER_STATUS_ENUM_UINT8;


enum RNIC_TIMER_OPERATION_TYPE_ENUM
{
    RNIC_TIMER_OPERATION_START,                                                 /* 启动定时器 */
    RNIC_TIMER_OPERATION_STOP,                                                  /* 停止定时器 */
    RNIC_TIMER_OPERATION_TYPE_ENUM_BUTT
};
typedef VOS_UINT8  RNIC_TIMER_OPERATION_TYPE_ENUM_UINT8;


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
    HTIMER                              hTimer;                                 /* 定时器的运行指针 */
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;                          /* 定时器的运行状态,启动或停止 */
    VOS_UINT8                           aucRsv[7];                              /* 保留 */
} RNIC_TIMER_CTX_STRU;



typedef struct
{
    VOS_MSG_HEADER
    RNIC_TIMER_ID_ENUM_UINT16               enTimerId;                          /* 定时器ID */
    RNIC_TIMER_OPERATION_TYPE_ENUM_UINT8    enTimeAction;                       /* 定时器操作类型 */
    VOS_UINT8                               aucRsv[1];                          /* 保留 */
    VOS_UINT32                              ulTimeLen;                          /* 定时器长度 */
}RNIC_TIMER_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID  RNIC_InitAllTimers(
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx
);

VOS_VOID  RNIC_StartTimer(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId,
    VOS_UINT32                          ulLen
);

VOS_VOID  RNIC_StopTimer(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId
);

VOS_VOID  RNIC_StopAllTimer( VOS_VOID );

RNIC_TIMER_STATUS_ENUM_UINT8  RNIC_GetTimerStatus(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId
);

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

#endif /* end of RnicTimerMgmt.h */
