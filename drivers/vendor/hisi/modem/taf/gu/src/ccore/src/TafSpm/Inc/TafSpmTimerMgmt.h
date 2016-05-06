/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmTimerMgmt.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年5月9日
  最近修改   :
  功能描述   : TafSpmTimerMgmt.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_SPM_TIMERMGMT_H__
#define __TAF_SPM_TIMERMGMT_H__

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
/* 增强型会议发起多个联系人，进行FDN/CC检查的保护时长增长致8s */
#define             TI_TAF_SPM_WAIT_PB_FDN_CHECK_CNF_LEN                (8000)
#define             TI_TAF_SPM_WAIT_USIM_CALL_CTRL_CNF_LEN              (8000)

/* Added by y00245242 for VoLTE_PhaseII  项目, 2013-9-23, begin */
/*
 * The following service request timer value dependence on:
 *  1. SMS: AT_SMS_CMGS_SET_PARA_TIME/AT_SMS_CMSS_SET_PARA_TIME
 *  2. SS: AT_SS_SET_PARA_TIME/AT_SS_QRY_PARA_TIME
 *  3. CC: AT_SET_PARA_TIME.
 * see ATCmdProc.h file.
 */
#define             TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER_VAL             (25000)             /* CC业务请求保护定时器值 */
#define             TI_TAF_SPM_SMS_SRV_REQ_PROTECT_TIMER_VAL            (30000)             /* SMS业务请求保护定时器值 */
#define             TI_TAF_SPM_SS_SRV_REQ_PROTECT_TIMER_VAL             (30000)             /* SS业务请求保护定时器值 */
/* Added by y00245242 for VoLTE_PhaseII  项目, 2013-9-23, end */

#define             TI_TAF_SPM_CC_SMS_SS_SRV_REQ_PROTECT_TIMER_DEFAULT_VAL      (3000)      /* CC业务请求保护定时器默认值 */

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-26, begin */
#define             TI_TAF_SPM_CC_ECALL_REQ_PROTECT_TIMER_VAL           (90000)             /* ecall CC业务请求保护定时器值，T305+2*T308 */
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-26, end */

#define             TAF_SPM_MAX_TIMER_NUM                               (10)                /* spm中同时运行的定时器的最大数目 */


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : TAF_SPM_TIMER_STATUS_ENUM
 结构说明  : SPM定时器状态,停止或运行
  1.日    期   : 2013年5月9日
    作    者   : W00176964
    修改内容   : 新建
*****************************************************************************/
enum TAF_SPM_TIMER_STATUS_ENUM
{
    TAF_SPM_TIMER_STATUS_STOP,              /* 定时器停止状态 */
    TAF_SPM_TIMER_STATUS_RUNING,            /* 定时器运行状态 */
    TAF_SPM_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 TAF_SPM_TIMER_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SPM_TIMER_ID_ENUM_UINT32
 枚举说明  : MN的spm模块的定时器ID枚举定义
 1.日    期   : 2013年5月8日
   作    者   : W00176964
   修改内容   : 新建
*****************************************************************************/                     
enum TAF_SPM_TIMER_ID_ENUM
{
    TI_TAF_SPM_WAIT_PB_FDN_CHECK_CNF                             = MN_TIMER_CLASS_SPM,/* 等待PB的FDN检查结果保护定时器 */
    TI_TAF_SPM_WAIT_USIM_CALL_CTRL_CNF,                                               /* 等待USIM的call control检查结果保护定时器 */
/* Added by y00245242 for VoLTE_PhaseII  项目, 2013-9-23, begin */
    TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER,                                                /* CC 业务请求保护定时器 */
    TI_TAF_SPM_SMS_SRV_REQ_PROTECT_TIMER,                                               /* SMS 业务请求保护定时器 */
    TI_TAF_SPM_SS_SRV_REQ_PROTECT_TIMER,                                                /* SS 业务请求保护定时器 */
/* Added by y00245242 for VoLTE_PhaseII  项目, 2013-9-23, end */
    
    TI_TAF_SPM_TIMER_BUTT
};
typedef VOS_UINT32 TAF_SPM_TIMER_ID_ENUM_UINT32;



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
 结构名    : TAF_SPM_TIMER_CTX_STRU
 结构说明  : spm定时器运行上下文
 1.日    期   : 2013年5月9日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    HTIMER                              hTimer;                                 /* 定时器的运行指针 */
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId;                              /* 定时器的ID */
    TAF_SPM_TIMER_STATUS_ENUM_UINT8     enTimerStatus;                          /* 定时器的运行状态,启动或停止 */
    VOS_UINT8                           aucReserve[1];                          /* 保留位 */
    VOS_UINT16                          usClientId;                             /* 定时器关联的client PID */
} TAF_SPM_TIMER_CTX_STRU;


/*****************************************************************************
 结构名    : TAF_SPM_TIMER_INFO_STRU
 结构说明  : log出SPM定时器运行情况
 1.日    期   : 2013年5月9日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    TAF_SPM_TIMER_STATUS_ENUM_UINT8     enTimerStatus;      /* 定时器状态 */
    VOS_UINT8                           aucReserve[1];      /* 保留位 */    
    VOS_UINT16                          usClientId;         /* 定时器关联client ID */
    VOS_UINT32                          ulLen;              /* 定时器时长 */
}TAF_SPM_TIMER_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 外部函数变量声明
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID  TAF_SPM_StartTimer(
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT16                          usClientId
);

VOS_VOID  TAF_SPM_StopTimer(
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT16                          usClientId
);

TAF_SPM_TIMER_STATUS_ENUM_UINT8  TAF_SPM_GetTimerStatus(
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT16                          usClientId
);

VOS_VOID  TAF_SPM_InitAllTimers(
    TAF_SPM_TIMER_CTX_STRU              *pstSpmTimerCtx
);

VOS_VOID  TAF_SPM_SndOmTimerStatus(
    TAF_SPM_TIMER_STATUS_ENUM_UINT8     enTimerStatus,
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT16                          usClientId
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

#endif /* end of TafSpmTimerMgmt.h */

