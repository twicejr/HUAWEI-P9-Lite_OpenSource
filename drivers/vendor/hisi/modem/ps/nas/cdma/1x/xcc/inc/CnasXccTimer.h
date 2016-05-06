/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccTimer.h
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年7月10日
  最近修改   :
  功能描述   : XCC模块timer相关的定义
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月10日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XCC_TIMER_H__
#define __CNAS_XCC_TIMER_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* TI_CNAS_XCC_T52M 的时长5s */
#define TI_CNAS_XCC_T52M_LEN                                (5*1000)

/* TI_CNAS_XCC_T53M 的时长65s */
#define TI_CNAS_XCC_T53M_LEN                                (65*1000)

/* TI_CNAS_XCC_T54M 的时长0.2s */
#define TI_CNAS_XCC_T54M_LEN                                (2*100)

/* L2 ACK接入层的保护时长是120S, 接入时，接入层的保护时长是300S */
#define TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP_LEN                (5*1000)
#define TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN                     (305*1000)
#define TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND_LEN               (15*1000)
#define TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP_LEN               (5*1000)
#define TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING_LEN           (5*1000)

/* CNAS发送CNAS_CAS_1X_DSCH_DATA_REQ到CAS，CAS在6s超时后向CTTF发cancel
   收到cancel结果或超时后，给CNAS发DATA_CNF结果。CAS理论最长12s，CNAS加
   1s余量，定时器改为12+1=13s  */
#define TI_CNAS_XCC_WAIT_CONN_L2_ACK_LEN                    (13*1000)
#define TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK_LEN               (13*1000)

#define TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK_LEN          (13*1000)

#define TI_CNAS_XCC_WAIT_EMERGENCY_CALL_FLASH_CNF_L2_ACK_LEN (13*1000)

#define TI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK_LEN            (13*1000)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : CNAS_XCC_TIMER_ID_ENUM
 枚举说明  : XCC模块的TIMER ID定义
 1.日    期   : 2014年07月10日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
enum CNAS_XCC_TIMER_ID_ENUM
{
    /* Reference to C.S0005-A Table D-1. Time Limits:
     Maximum time to receive a message in the Waiting for Order Substate of the Call Control processing
     that transits Call Control instance to a different substate or state */
    TI_CNAS_XCC_T52M,

    /* Reference to C.S0005-A Table D-1. Time Limits:
     Maximum time to receive a message in the Waiting for Mobile Station Answer Substate of Call Control
     processing that transits the Call Control instance to a different substate or state */
    TI_CNAS_XCC_T53M,

    TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP,
    TI_CNAS_XCC_WAIT_AS_EST_CNF,
    TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND,
    TI_CNAS_XCC_WAIT_CONN_L2_ACK,
    TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP,
    TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING,

    TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK,

    TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK,

    TI_CNAS_XCC_WAIT_EMERGENCY_CALL_FLASH_CNF_L2_ACK,

    TI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK,

    TI_CNAS_XCC_TIMER_ID_BUTT
};
typedef VOS_UINT32  CNAS_XCC_TIMER_ID_ENUM_UINT32;


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
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)



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

#endif /* end of __CNAS_XCC_TIMER_H__ */
