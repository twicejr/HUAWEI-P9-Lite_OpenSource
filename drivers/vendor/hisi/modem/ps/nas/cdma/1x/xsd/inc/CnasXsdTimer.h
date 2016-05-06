/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdTimer.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年7月3日
  最近修改   :
  功能描述   : timer参数定义
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月3日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XSD_TIMER_H__
#define __CNAS_XSD_TIMER_H__

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
/* XSD中定时器的时长 */
#define TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN                  (30*1000)
#define TI_CNAS_XSD_WAIT_XCC_START_CNF_LEN                  (5*1000)
#define TI_CNAS_XSD_WAIT_XREG_START_CNF_LEN                 (5*1000)
#define TI_CNAS_XSD_WAIT_CAS_START_CNF_LEN                  (10*1000)
#define TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF_LEN               (5*1000)
#define TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF_LEN              (5*1000)
#define TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF_LEN               (5*1000)

#define TI_CNAS_XSD_WAIT_CAS_SYNC_ONE_FREQ_LEN              (17*1000)  /* 等待CAS同步一个频点的保护定时器时长 */

#define TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN                    (30*1000)
#define TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN       (5*1000)

#define TI_CNAS_XSD_AVAILABLE_LEN                           (5*1000)

/* Reference to CDG 143 Table A-1 Configurable Parameters */
#define TI_CNAS_XSD_T_BSR_DIG_LEN                           (180*1000)
#define TI_CNAS_XSD_T_BSR_CALL_LEN                          (5*1000)
#define TI_CNAS_XSD_T_BSR_NEWSYS_LEN                        (1*1000)

#define TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER_LEN         (15*3600*1000)  /* 15 hours */

#define TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND_LEN         (3*1000)

#define TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER_LEN       (1*1000)

#define TI_CNAS_XSD_WAIT_CAS_SUSPEND_CNF_LEN                 (6*1000)

#define TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER_LEN     (15*1000)   /* 紧急呼CallBack模式搜网15s保护定时器 */
#define TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_BREAK_TIMER_LEN       (500)       /* 紧急呼CallBack模式搜网500毫秒保护定时器 */


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : CNAS_XSD_TIMER_ID_ENUM
 枚举说明  : XSD定时器的ID
 1.日    期   : 2014年7月4日
   作    者   : h00246512
   修改内容   : 新建

 2.日    期   : 2015年1月4日
   作    者   : y00245242
   修改内容   : 新建

 3.日    期   : 2015年7月4日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
enum CNAS_XSD_TIMER_ID_ENUM
{
    TI_CNAS_XSD_WAIT_CARD_FILE_CNF,
    TI_CNAS_XSD_WAIT_XCC_START_CNF,
    TI_CNAS_XSD_WAIT_XREG_START_CNF,
    TI_CNAS_XSD_WAIT_CAS_START_CNF,
    TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF,
    TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF,
    TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF,
    TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF,
    TI_CNAS_XSD_WAIT_CAS_OHM_IND,
    TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF,
    TI_CNAS_XSD_AVAILABLE_TIMER,
    /* Reference to CDG 143 Table A-1 Configurable Parameters */
    TI_CNAS_XSD_T_BSR_DIG,
    TI_CNAS_XSD_T_BSR_CALL,
    TI_CNAS_XSD_T_BSR_NEWSYS,
    TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND,
    TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER,
    TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER,
    TI_CNAS_XSD_AVAILABLE_MRU0_TIMER,
    TI_CNAS_XSD_WAIT_CAS_SUSPEND_CNF,
    TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER,    /* 紧急呼CALLBACK模式15s搜网保护定时器 */
    TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,            /* 紧急呼CALLBACK模式保护定时器 */
    TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_BREAK_TIMER,      /* 紧急呼CaLLBACK模式的间隔定时器 */
    TI_CNAS_XSD_TIMER_BUTT
};
typedef VOS_UINT32  CNAS_XSD_TIMER_ID_ENUM_UINT32;

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

#endif /* end of CnasXsdTimerMgmt.h */
