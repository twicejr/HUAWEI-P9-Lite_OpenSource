/******************************************************************************

                  版权所有 (C), 2014-2021, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallTimerMgmt.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2014年11月7日
  最近修改   :
  功能描述   : TafXCallTimerMgmt.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_XCALL_TIMERMGMT_H__
#define __TAF_XCALL_TIMERMGMT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "MnComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define             TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD_LEN                (30000)  /* silently redial 总定时器时长 */
#define             TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN              (4000)   /* silently redial 间隔时长 */
#define             TAF_XCALL_TIMER_TICK                                     (10)

#define             TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MIN      (360)   /* 同一对Stop Cont DTMF和Start的间隔时长，最小值,单位:ms */
#define             TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MAX      (1000)  /* 同一对Stop Cont DTMF和Start的间隔时长，最大值,单位:ms */

#define             TI_TAF_XCALL_TX01_LEN                                   (30000) /* TX01(这里包含TX101, TX201，TX401)为30s */
#define             TI_TAF_XCALL_T301_LEN                                   (50000) /* T301为50s */
#define             TI_TAF_XCALL_TX02_LEN                                   (6000)  /* TX02为6s */
#define             TI_TAF_XCALL_VOICE_ENCRYPT_WAIT_ORIG_REQ_LEN            (1000)  /* 等待呼叫时长为1s */
#define             TI_TAF_XCALL_DELAY_SEND_ENCRYPT_LEN                     (2000)  /* 密话请求延时发送请求时长 */
#define             TI_TAF_XCALL_REMOTE_CTRL_ANSWER_DEFAULT_TIMER_LEN       (600)   /* 10分钟, 单位s */
#define             TI_TAF_XCALL_REMOTE_CTRL_ANSWER_MAX_TIMER_LEN           (1800)  /* 30分钟, 单位s*/


#define             TI_TAF_XCALL_PUB_KEY_UPDATE_WAIT_ACK_LEN                (10000) /* 公钥更新过程中等待KMC的更新确认消息时长为10s */

#define             TAF_XCALL_EMC_CALL_REDIAL_PERIOD_DEFAULT                (600)
#define             TAF_XCALL_ENCVOICE_REQ_DEFAULT_DELAY_TIMER_LEN          (2)     /* 2秒    */
#define             TAF_XCALL_ENCVOICE_REQ_MAX_DELAY_TIMER_LEN              (10)    /* 10秒   */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : TAF_XCALL_TIMER_STATUS_ENUM
 结构说明  : XCALL定时器状态,停止或运行
  1.日    期   : 2014年11月17日
    作    者   : W00176964
    修改内容   : 新建
*****************************************************************************/
enum TAF_XCALL_TIMER_STATUS_ENUM
{
    TAF_XCALL_TIMER_STATUS_STOP,              /* 定时器停止状态 */
    TAF_XCALL_TIMER_STATUS_RUNING,            /* 定时器运行状态 */
    TAF_XCALL_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 TAF_XCALL_TIMER_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_XCALL_TIMER_ID_ENUM_UINT32
 枚举说明  : XCALL模块的定时器ID枚举定义
 1.日    期   : 2014年11月17日
   作    者   : W00176964
   修改内容   : 新建
*****************************************************************************/
enum TAF_XCALL_TIMER_ID_ENUM
{
    TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD                             = MN_TIMER_CLASS_XCALL,/* silently redial 总定时器 */
    TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL,                                               /* silently redial 间隔定时器 */

    TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL,                 /* Stop CONT DTMF命令和Start Cont DTMF命令之间的间隔，
                                                                        在收到Start Cont DTMF后启动，默认时长360ms，可通过nv配置 */

    TI_TAF_XCALL_VOICE_ENCRYPT_WAIT_ORIG_REQ_TIMER,                 /* 密话过程中等待Orig请求timer */

    TI_TAF_XCALL_DELAY_SEND_ENCRYPT_REQ,                            /* 延时密钥请求发送定时器 */

    TI_TAF_XCALL_TX01_TIMER,                                        /* TX01定时器 */

    TI_TAF_XCALL_TX02_TIMER,                                        /* TX02定时器 */

    TI_TAF_XCALL_PUB_KEY_UPDATE_WAIT_ACK_TIMER,                     /* 公钥更新过程中等待公钥更新确认消息定时器 */

    TI_TAF_XCALL_REMOTE_CTRL_WAIT_AP_ANSWER_TIMER,                  /* 远程控制等待AP应答定时器 */

    TI_TAF_XCALL_TIMER_BUTT
};
typedef VOS_UINT32 TAF_XCALL_TIMER_ID_ENUM_UINT32;



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
 结构名    : TAF_XCALL_TIMER_CTX_STRU
 结构说明  : XCALL定时器运行上下文
 1.日    期   : 2014年11月17日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    HTIMER                              hTimer;                                 /* 定时器的运行指针 */
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId;                              /* 定时器的ID */
    TAF_XCALL_TIMER_STATUS_ENUM_UINT8   enTimerStatus;                          /* 定时器的运行状态,启动或停止 */
    VOS_UINT8                           ucCallId;                               /* 定时器关联call ID */
    VOS_UINT8                           aucReserve[2];                          /* 保留位 */
} TAF_XCALL_TIMER_CTX_STRU;


/*****************************************************************************
 结构名    : TAF_XCALL_TIMER_INFO_STRU
 结构说明  : log出XCALL定时器运行情况
 1.日    期   : 2014年11月17日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    TAF_XCALL_TIMER_STATUS_ENUM_UINT8   enTimerStatus;      /* 定时器状态 */
    VOS_UINT8                           ucCallId;           /* 定时器关联call ID */
    VOS_UINT8                           aucReserve[2];      /* 保留位 */
    VOS_UINT32                          ulLen;              /* 定时器时长 */
}TAF_XCALL_TIMER_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 外部函数变量声明
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID  TAF_XCALL_StartTimer(
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucCallId
);

VOS_VOID  TAF_XCALL_StopTimer(
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT8                           ucCallId
);

TAF_XCALL_TIMER_STATUS_ENUM_UINT8  TAF_XCALL_GetTimerStatus(
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT8                           ucCallId
);

VOS_VOID  TAF_XCALL_InitAllTimers(
    TAF_XCALL_TIMER_CTX_STRU           *pstXcallTimerCtx
);

VOS_VOID  TAF_XCALL_SndOmTimerStatus(
    TAF_XCALL_TIMER_STATUS_ENUM_UINT8   enTimerStatus,
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_GetRemainTimerLen(
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT8                           ucCallId,
    VOS_UINT32                         *pulRemainTimeLen
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

#endif /* end of TafXCallTimerMgmt.h */


