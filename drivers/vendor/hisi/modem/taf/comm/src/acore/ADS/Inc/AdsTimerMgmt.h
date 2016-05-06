

#ifndef __ADSTIMERMGMT_H__
#define __ADSTIMERMGMT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* ADS中同时运行的定时器的最大数目,目前只有一个 */
#define ADS_MAX_TIMER_NUM               (TI_ADS_TIMER_BUTT)

/* 定时器TI_ADS_UL_SEND的时长 */
#define TI_ADS_UL_SEND_LEN              (10)

/* 定时器TI_ADS_DSFLOW_STATS的时长，1秒统计一次速率 */
#define TI_ADS_DSFLOW_STATS_LEN         (1000)

/* 定时器TI_ADS_DL_PROTECT的时长, 100ms */
#define TI_ADS_DL_PROTECT_LEN           (100)

/* 定时器TI_ADS_DL_ADQ_EMPTY的时长, 10ms */
#define TI_ADS_DL_ADQ_EMPTY_LEN         (10)

/* 定时器TI_ADS_RPT_STATS的时长，2秒上报一次统计信息 */
#define TI_ADS_RPT_STATS_LEN         (2000)

typedef VOS_VOID (*PFN_ADS_TIMER_CALL_BACK_FUN)(VOS_UINT32 ulParam, VOS_UINT32 ulTimerName);

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : ADS_TIMER_ID_ENUM
 枚举说明  : ADS定时器的ID

  1.日    期   : 2011年12月7日
    作    者   : 鲁琳/l60609
    修改内容   : 定义ADS定时器的ID

  2.日    期   : 2012年7月17日
    作    者   : A00165503
    修改内容   : DTS2012071003092: ADS增加下行RD读取保护定时器(100ms), 防止RD
                 满且ADS未读取导致数传中断
*****************************************************************************/
enum ADS_TIMER_ID_ENUM
{
    TI_ADS_UL_SEND                      = 0x00,                                 /* ADS上行发送定时器 */
    TI_ADS_DSFLOW_STATS                 = 0x01,                                 /* 流量统计定时器 */
    TI_ADS_DL_ADQ_EMPTY                 = 0x02,                                 /* 下行ADQ空定时器 */
    TI_ADS_UL_DATA_STAT                 = 0x03,                                 /* 上行数据统计定时器 */

    TI_ADS_TIMER_BUTT
};
typedef VOS_UINT32  ADS_TIMER_ID_ENUM_UINT32;


/*****************************************************************************
 枚举名    : ADS_TIMER_STATUS_ENUM
 结构说明  : ADS定时器状态,停止或运行

  1.日    期   : 2011年12月7日
    作    者   : 鲁琳/l60609
    修改内容   : 定义ADS定时器状态
*****************************************************************************/
enum ADS_TIMER_STATUS_ENUM
{
    ADS_TIMER_STATUS_STOP,                                                      /* 定时器停止状态 */
    ADS_TIMER_STATUS_RUNNING,                                                   /* 定时器运行状态 */
    ASD_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 ADS_TIMER_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : ADS_TIMER_OPERATION_TYPE_ENUM
 结构说明  : ADS定时器操作的取值，用于SDT中显示

  1.日    期   : 2011年12月7日
    作    者   : 鲁琳/l60609
    修改内容   : 定义ADS定时器操作的取值，用于SDT中显示
*****************************************************************************/
enum ADS_TIMER_OPERATION_TYPE_ENUM
{
    ADS_TIMER_OPERATION_START,                                                  /*启动定时器*/
    ADS_TIMER_OPERATION_STOP,                                                   /*停止定时器*/
    ADS_TIMER_OPERATION_TYPE_ENUM_BUTT
};
typedef VOS_UINT8 ADS_TIMER_OPERATION_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : ADS_TIMER_STOP_CAUSE_ENUM
 结构说明  : ADS定时器停止的原因，用于SDT中显示

  1.日    期   : 2014年10月30日
    作    者   : 范晶/f00179208
    修改内容   : 定义ADS定时器停止的原因，用于SDT中显示
*****************************************************************************/
enum ADS_TIMER_STOP_CAUSE_ENUM
{
    ADS_TIMER_STOP_CAUSE_USER,                                                   /* 用户主动停止的 */
    ADS_TIMER_STOP_CAUSE_TIMEOUT,                                                /* 定时器超时显示停止的 */
    ADS_TIMER_STOP_CAUSE_ENUM_BUTT
};
typedef VOS_UINT8 ADS_TIMER_STOP_CAUSE_ENUM_UINT8;

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
 结构名    : ADS_TIMER_CTX_STRU
 结构说明  : ADS定时器运行时的上下文

  1.日    期   : 2011年12月7日
    作    者   : 鲁琳/l60609
    修改内容   : 定义ADS定时器运行时的上下文
*****************************************************************************/
typedef struct
{
    HTIMER                              hTimer;                                 /* 定时器的运行指针 */
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;                          /* 定时器的运行状态,启动或停止 */
    VOS_UINT8                           aucRsv[7];                              /* 保留*/
} ADS_TIMER_CTX_STRU;

/*****************************************************************************
 结构名称: ADS_TIMER_INFO_STRU
 结构说明: ADS定时器信息结构，用于SDT中显示
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    ADS_TIMER_ID_ENUM_UINT32            enTimerId;          /* _H2ASN_Skip */
    VOS_UINT32                          ulTimerLen;         /* 定时器长度*/
    ADS_TIMER_OPERATION_TYPE_ENUM_UINT8 enTimerAction;      /* 定时器操作类型 */
    ADS_TIMER_STOP_CAUSE_ENUM_UINT8     enTimerStopCause;   /* 定时器停止的原因 */
    VOS_UINT8                           aucReserved[2];
} ADS_TIMER_INFO_STRU;

/*****************************************************************************
 结构名称: ADS_TIMER_OPERATE_STRU
 结构说明: ADS定时器操作结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulPid;
    VOS_UINT32                              enTimerId;                          /* 定时器名称 */
    VOS_TIMER_PRECISION_ENUM_UINT32         enPrecision;                        /* 定时器精度 */
    VOS_UINT8                               aucReserved[4];
    PFN_ADS_TIMER_CALL_BACK_FUN             pfnTimerStartCallBack;              /* 定时器使用CALLBACK的函数 */
} ADS_TIMER_OPERATE_STRU;



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_VOID ADS_DL_StartProtectTimer(VOS_VOID);

VOS_VOID  ADS_StartTimer(
    ADS_TIMER_ID_ENUM_UINT32            enTimerId,
    VOS_UINT32                          ulLen
);

VOS_VOID ADS_StopTimer(
    VOS_UINT32                          ulPid,
    ADS_TIMER_ID_ENUM_UINT32            enTimerId,
    ADS_TIMER_STOP_CAUSE_ENUM_UINT8     enStopCause
);

ADS_TIMER_STATUS_ENUM_UINT8 ADS_GetTimerStatus(
    VOS_UINT32                          ulPid,
    ADS_TIMER_ID_ENUM_UINT32            enTimerId
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

#endif /* end of AdsTimerMgmt.h */
