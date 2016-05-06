/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsTimerMgmt.h
  版 本 号   : 初稿
  作    者   : o00132663
  生成日期   : 2011年12月13日
  最近修改   :
  功能描述   : TafApsTimerMgmt.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月13日
    作    者   : o00132663
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFAPSTIMERMGMT_H__
#define __TAFAPSTIMERMGMT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "MnComm.h"
#include "TafApsApi.h"
#include "ApsL4aInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* APS中同时运行的定时器的最大数目 */
#define TAF_APS_MAX_TIMER_NUM           (30)

/*将定时器的秒转换成DOPRA定时器所需的毫秒，需要乘以1000 */
#define TIMER_S_TO_MS_1000              (1000)

/*PDP状态转换时需要的几个定时器的时间长度，单位为秒*/
#define TIMER_3380_S                    (30)
#define TIMER_3381_S                    (8)
#define TIMER_3390_S                    (8)

/*PDP操作中的定时器通常都要循环几次才最终退出*/
#define TIMER_4_TIMES                   (4)
#define TIMER_5_TIMES                   (5)

/*网络激活手动应答时，网络侧等待的时间是 T3385 * 5(次) = 8*5 = 40s,那么UE侧等待
手动应答的时间就必须再减去网络传输将消耗的延迟，定为20S*/
#define TIMER_APS_NET_PDP_ACTIVE_PENDING_S          (20)

/* 激活SNDCP流程保护定时器时长 */
#define TI_TAF_APS_SNDCP_ACT_TIMER_LEN              (180 * TIMER_S_TO_MS_1000)

/* 修改SNDCP流程保护定时器时长 */
#define TI_TAF_ASP_SNDCP_MDF_TIMER_LEN              (120 * TIMER_S_TO_MS_1000)

/* APS定时器的时长，单位:毫秒 */
#define TI_TAF_APS_MS_ACTIVATING_LEN                    ((TIMER_3380_S * TIMER_S_TO_MS_1000 * TIMER_5_TIMES) + (TIMER_S_TO_MS_1000 * 1))
#define TI_TAF_APS_NET_ACTIVATING_LEN                   (TIMER_APS_NET_PDP_ACTIVE_PENDING_S * TIMER_S_TO_MS_1000)
#define TI_TAF_APS_MS_MODIFYING_LEN                     ((TIMER_3381_S * TIMER_S_TO_MS_1000 * (TIMER_5_TIMES + 1)) + TI_TAF_ASP_SNDCP_MDF_TIMER_LEN)
#define TI_TAF_APS_MS_DEACTIVATING_LEN                  (TIMER_3390_S * TIMER_S_TO_MS_1000 * (TIMER_5_TIMES + 1))

#define TI_TAF_APS_DSFLOW_REPORT_LEN                    (TIMER_S_TO_MS_1000)

#define TI_TAF_APS_DEFAULT_DSFLOW_WRITE_NV_LEN          (2)

#define TI_TAF_APS_WAIT_L4A_CNF_LEN                     (2  * TIMER_S_TO_MS_1000)

#define TI_TAF_APS_1_TICK_10_MS                 (10)        /* 1 tick为10ms */

#define TAF_APS_INVALID_TIMER_PARA                  (0xFFFFFFFF)
#define TAF_APS_INVALID_CMD_PARA                    (TAF_APS_INVALID_TIMER_PARA)

/* 默认PPP去激活时间:30S */
#define TI_TAF_APS_CDATA_DEFAULT_PPP_DEACT_LEN              (30)

/**
 * CDG 143 4.7 Voice and Data Call Origination
 */
/* 按照CGD143 5.9.3 重播定时器最大时长为30s */
#define TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD_LEN        ( 30 * 1000 )

#define TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN      ( 4 * 1000 )
#define TI_TAF_APS_CDATA_ESTING_LEN                         ( 370 * 1000 )
#define TI_TAF_APS_CDATA_DISCING_LEN                        ( 30 * 1000 )
#define TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF_LEN        ( 30 * 1000 )
#define TI_TAF_APS_CDATA_HRPD_LOST_TIMER_LEN                ( 5 * 1000 )

#define TI_TAF_APS_1X_TO_HRPD_HANDOFF_TIMER_LEN             ( 3 * 1000 )



/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : TAF_APS_TIMER_STATUS_ENUM
 结构说明  : APS定时器状态,停止或运行
  1.日    期   : 2011年12月13日
    作    者   : 欧阳飞 00132663
    修改内容   : 新建
*****************************************************************************/
enum TAF_APS_TIMER_STATUS_ENUM
{
    TAF_APS_TIMER_STATUS_STOP,              /* 定时器停止状态 */
    TAF_APS_TIMER_STATUS_RUNING,            /* 定时器运行状态 */
    TAF_APS_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 TAF_APS_TIMER_STATUS_ENUM_U8;

/*****************************************************************************
 枚举名    : TAF_APS_TIMER_ID_ENUM
 枚举说明  : APS定时器的ID
 1.日    期   : 2011年12月13日
   作    者   : 欧阳飞 00132663
   修改内容   : 新建
*****************************************************************************/
enum TAF_APS_TIMER_ID_ENUM
{
    /* 用户激活定时器 */
    TI_TAF_APS_MS_ACTIVATING                    = MN_TIMER_CLASS_APS + 0x01,

    /* 网络激活定时器 */
    TI_TAF_APS_NET_ACTIVATING                   = MN_TIMER_CLASS_APS + 0x02,

    /* PDP MODIFY定时器 */
    TI_TAF_APS_MS_MODIFYING                     = MN_TIMER_CLASS_APS + 0x03,

    /* 用户去激活定时器 */
    TI_TAF_APS_MS_DEACTIVATING                  = MN_TIMER_CLASS_APS + 0x04,

    /* 流量统计相关定时器 */
    TI_TAF_APS_DSFLOW_REPORT                    = MN_TIMER_CLASS_APS + 0x05,
    TI_TAF_APS_DSFLOW_WRITE_NV                  = MN_TIMER_CLASS_APS + 0x06,

    /* 暂停PDP激活定时器，AT&T定制特性(PDP激活受限) */
    TI_TAF_APS_LIMIT_PDP_ACT                    = MN_TIMER_CLASS_APS + 0x08,

#if ( FEATURE_ON == FEATURE_LTE )
    /* L4A消息保护定时器 */
    TI_TAF_APS_WAIT_SET_CGDCONT_CNF             = MN_TIMER_CLASS_APS + 0x101,
    TI_TAF_APS_WAIT_SET_CGDSCONT_CNF            = MN_TIMER_CLASS_APS + 0x102,
    TI_TAF_APS_WAIT_SET_CGTFT_CNF               = MN_TIMER_CLASS_APS + 0x103,
    TI_TAF_APS_WAIT_SET_CGAUTO_CNF              = MN_TIMER_CLASS_APS + 0x104,
    TI_TAF_APS_WAIT_SET_CGANS_CNF               = MN_TIMER_CLASS_APS + 0x105,
    TI_TAF_APS_WAIT_SET_CGEQOS_CNF              = MN_TIMER_CLASS_APS + 0x106,
    TI_TAF_APS_WAIT_SET_AUTHDATA_CNF            = MN_TIMER_CLASS_APS + 0X107,

    TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF           = MN_TIMER_CLASS_APS + 0x108,
    TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF          = MN_TIMER_CLASS_APS + 0x109,
    TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF            = MN_TIMER_CLASS_APS + 0x10A,
    TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF           = MN_TIMER_CLASS_APS + 0x10B,

    /* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
    TI_TAF_APS_WAIT_GET_LTE_CS_CNF              = MN_TIMER_CLASS_APS + 0x10C,
    TI_TAF_APS_WAIT_SET_PDPROF_CNF              = MN_TIMER_CLASS_APS + 0x10D,
    TI_TAF_APS_WAIT_GET_CEMODE_CNF              = MN_TIMER_CLASS_APS + 0x10E,

    /* Add by w00199382 for V7代码同步, 2012-04-07, End   */

#endif

    TI_TAF_APS_CDATA_ESTING                     = MN_TIMER_CLASS_APS + 0x200,
    TI_TAF_APS_CDATA_DISCING                    = MN_TIMER_CLASS_APS + 0x201,
    TI_TAF_APS_CDATA_DORMANT                    = MN_TIMER_CLASS_APS + 0x202,
    TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD    = MN_TIMER_CLASS_APS + 0x203,
    TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL  = MN_TIMER_CLASS_APS + 0x204,
    TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF    = MN_TIMER_CLASS_APS + 0x205,
    TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF = MN_TIMER_CLASS_APS + 0x206,
    TI_TAF_APS_CDATA_HRPD_LOST_TIMER            = MN_TIMER_CLASS_APS + 0x207,
    TI_TAF_APS_CDATA_EPZID_HAT                  = MN_TIMER_CLASS_APS + 0x208,
    TI_TAF_APS_CDATA_EPZID_HT                   = MN_TIMER_CLASS_APS + 0x209,
    TI_TAF_APS_1X_TO_HRPD_HANDOFF_TIMER         = MN_TIMER_CLASS_APS + 0x20A,

    TI_TAF_APS_TIMER_BUTT
};
typedef VOS_UINT32  TAF_APS_TIMER_ID_ENUM_UINT32;

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
 结构名    : TAF_APS_TIMER_CXT_STRU
 结构说明  : APS定时器运行上下文
 1.日    期   : 2011年12月13日
   作    者   : 欧阳飞 00132663
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    HTIMER                              hTimer;                                 /* 定时器的运行指针 */
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId;                              /* 定时器的ID */
    VOS_UINT32                          ulPara;                                 /* 定时器关联的PDPID */
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;                          /* 定时器的运行状态,启动或停止 */
    VOS_UINT8                           aucReserve[3];                          /* 保留位 */
} TAF_APS_TIMER_CTX_STRU;


/*****************************************************************************
 结构名    : TAF_APS_TIMER_INFO_STRU
 结构说明  : log出APS定时器运行情况
 1.日    期   : 2011年12月13日
   作    者   : 欧阳飞 00132663
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;      /* 定时器状态 */
    VOS_UINT8                           aucReserve[3];      /* 保留位 */
    VOS_UINT32                          ulPara;             /* 定时器参数 */
    VOS_UINT32                          ulLen;              /* 定时器时长 */
}TAF_APS_TIMER_INFO_STRU;

typedef struct
{
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId;          /* TimerID */
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;        /* 定时器精度 */
}TAF_APS_TIMER_PRECISION_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 外部函数变量声明
*****************************************************************************/
/* Deleted by wx270776 for OM融合, 2015-6-28, begin */
/* Deleted by wx270776 for OM融合, 2015-6-28, end */


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_VOID  TAF_APS_InitAllTimers(
    TAF_APS_TIMER_CTX_STRU              *pstApsTimerCtx
);

VOS_VOID  TAF_APS_StartTimer(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT32                          ulPara
);

VOS_VOID  TAF_APS_StopTimer(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulPara
);

VOS_VOID  TAF_APS_StopAllTimer( VOS_VOID );

VOS_VOID  TAF_APS_StopPdpAllTimer(
    VOS_UINT32                          ulPara
);

TAF_APS_TIMER_STATUS_ENUM_U8  TAF_APS_GetTimerStatus(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulPara
);

VOS_UINT32  TAF_APS_BuildTmrParaByCtrlHdr(
    VOS_UINT32                          ulModuleId,
    VOS_UINT32                          ulClientId
);
VOS_VOID TAF_APS_GetRemainTimerLen(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulPara,
    VOS_UINT32                         *pulRemainTimeLen
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

#endif /* end of TafApsTimerMgmt.h */
