

#ifndef __CMMCATIMERMGMT_H__
#define __CMMCATIMERMGMT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#include "PsCommonDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* CMMCA中同时运行的定时器的最大数目 */
#define CMMCA_MAX_TIMER_NUM             (TI_CMMCA_TIMER_BUTT)

/* 定时器TI_CMMCA_WAIT_IPV6_RA_INFO的时长 */
#define TI_CMMCA_WAIT_IPV6_RA_INFO_LEN  (6 * 1000)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum CMMCA_TIMER_ID_ENUM
{
    TI_CMMCA_WAIT_IPV6_RA_INFO,                                                 /* 等待IPV6 RA INFO定时器 */

    TI_CMMCA_TIMER_BUTT
};
typedef VOS_UINT32  CMMCA_TIMER_ID_ENUM_UINT32;


enum CMMCA_TIMER_STATUS_ENUM
{
    CMMCA_TIMER_STATUS_STOP,                                                    /* 定时器停止状态 */
    CMMCA_TIMER_STATUS_RUNNING,                                                 /* 定时器运行状态 */
    CMMCA_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 CMMCA_TIMER_STATUS_ENUM_UINT8;


enum CMMCA_TIMER_OPERATION_TYPE_ENUM
{
    CMMCA_TIMER_OPERATION_START,                                                /*启动定时器*/
    CMMCA_TIMER_OPERATION_STOP,                                                 /*停止定时器*/
    CMMCA_TIMER_OPERATION_TYPE_ENUM_BUTT
};
typedef VOS_UINT8 CMMCA_TIMER_OPERATION_TYPE_ENUM_UINT8;


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
    VOS_PID                             ulPid;                    /* 启动Timer的PID */
    VOS_UINT32                          ulTimerName;              /* Timer名 */
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;              /* 定时器精度 */
}CMMCA_TIMER_PRECISION_STRU;


typedef struct
{
    HTIMER                              hTimer;                                 /* 定时器的运行指针 */
    CMMCA_TIMER_ID_ENUM_UINT32          enTimerId;                              /* 定时器的ID */
    CMMCA_TIMER_STATUS_ENUM_UINT8       enTimerStatus;                          /* 定时器的运行状态,启动或停止 */
    VOS_UINT8                           aucRsv[3];                              /* 保留*/
}CMMCA_TIMER_CTX_STRU;


typedef struct
{
    VOS_MSG_HEADER                                            /* _H2ASN_Skip */
    CMMCA_TIMER_ID_ENUM_UINT32            enTimerId;          /* _H2ASN_Skip */
    VOS_UINT32                            ulTimerLen;         /* 定时器长度*/
    CMMCA_TIMER_OPERATION_TYPE_ENUM_UINT8 enTimerAction;      /* 定时器操作类型 */
    VOS_UINT8                             aucReserved[3];
}CMMCA_TIMER_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID  CMMCA_StartTimer(
    VOS_UINT32                          ulPid,
    CMMCA_TIMER_ID_ENUM_UINT32          enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT32                          ulParam
);

VOS_VOID CMMCA_StopTimer(
    VOS_UINT32                          ulPid,
    CMMCA_TIMER_ID_ENUM_UINT32          enTimerId
);

CMMCA_TIMER_STATUS_ENUM_UINT8 CMMCA_GetTimerStatus(
    VOS_UINT32                          ulPid,
    CMMCA_TIMER_ID_ENUM_UINT32          enTimerId
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

#endif /* end of CmmcaTimerMgmt.h */
