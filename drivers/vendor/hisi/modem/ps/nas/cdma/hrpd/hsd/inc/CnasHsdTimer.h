/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdTimer.h
  版 本 号   : 初稿
  作    者   : g00256031
  生成日期   : 2014年12月13日
  最近修改   :
  功能描述   : timer参数定义
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月13日
    作    者   : h00300378
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_HSD_TIMER_H__
#define __CNAS_HSD_TIMER_H__

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

/* HSD中定时器的时长 */
#define TI_CNAS_HSD_WAIT_CARD_FILE_CNF_LEN                  (30*1000)
#define TI_CNAS_HSD_WAIT_HSM_START_CNF_LEN                  (6*1000)        /* 迭代12改为6s */

#define TI_CNAS_HSD_WAIT_EHSM_START_CNF_LEN                 (5*1000)

#define TI_CNAS_HSD_WAIT_HLU_START_CNF_LEN                  (5*1000)
#define TI_CNAS_HSD_WAIT_CAS_START_CNF_LEN                  (5*1000)
#define TI_CNAS_HSD_WAIT_HSM_POWEROFF_CNF_LEN               (6*1000)
#define TI_CNAS_HSD_WAIT_HSM_POWERSAVE_CNF_LEN              (21*1000)
#define TI_CNAS_HSD_WAIT_EHSM_POWEROFF_CNF_LEN              (5*1000)
#define TI_CNAS_HSD_WAIT_HLU_POWEROFF_CNF_LEN               (5*1000)
#define TI_CNAS_HSD_WAIT_CAS_POWEROFF_CNF_LEN               (5*1000)
#define TI_CNAS_HSD_WAIT_CAS_SUSPEND_CNF_LEN                (6*1000)

#define TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN            (120*1000)  /* 20150407由65*16s改为120s */
#define TI_CNAS_HSD_WAIT_CAS_OHM_IND_LEN                    (60*1000)
#define TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN       (5*1000)
#define TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_ACQUIRE_CNF_LEN    (5*1000)
#define TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER_LEN         (15*3600*1000)  /* 15 hours */

#define TI_CNAS_HSD_AVAILABLE_LEN                           (5*1000)

#define TI_CNAS_HSD_AVAILABLE_RATIO                         (1000)

#define TI_CNAS_HSD_WAIT_SESSION_NEG_RSLT_IND_LEN           (200*1000)  /* HSM在180s之内会回复协商结果 */
#define TI_CNAS_HSD_WAIT_CAS_IRAT_OR_RESUME_IND_LEN         (65*1000)

#define TI_CNAS_HSD_WAIT_RRM_STATUS_IND_LEN                 (30*60*1000)

#define TI_CNAS_HSD_WAIT_CAS_SUSPEND_REL_CNF_LEN            (120*1000)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : CNAS_HSD_TIMER_ID_ENUM
 枚举说明  : HSD定时器的ID
 1.日    期   : 2014年12月14日
   作    者   : h00300378
   修改内容   : 新建
*****************************************************************************/
enum CNAS_HSD_TIMER_ID_ENUM
{
    TI_CNAS_HSD_WAIT_CARD_FILE_CNF,
    TI_CNAS_HSD_WAIT_HSM_START_CNF,
    TI_CNAS_HSD_WAIT_HLU_START_CNF,
    TI_CNAS_HSD_WAIT_CAS_START_CNF,
    TI_CNAS_HSD_WAIT_HSM_POWEROFF_CNF,
    TI_CNAS_HSD_WAIT_HLU_POWEROFF_CNF,
    TI_CNAS_HSD_WAIT_CAS_POWEROFF_CNF,
    TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF,
    TI_CNAS_HSD_WAIT_CAS_OHM_IND,
    TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF,
    TI_CNAS_HSD_AVAILABLE_TIMER,

    TI_CNAS_HSD_AVAILABLE_MRU0_TIMER,

    TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,

    TI_CNAS_HSD_WAIT_SESSION_NEG_RSLT_IND,
    TI_CNAS_HSD_WAIT_CAS_SUSPEND_CNF,
    TI_CNAS_HSD_WAIT_CAS_IRAT_OR_RESUME_IND,

    TI_CNAS_HSD_WAIT_EHSM_START_CNF,
    TI_CNAS_HSD_WAIT_EHSM_POWEROFF_CNF,
    TI_CNAS_HSD_WAIT_HSM_POWERSAVE_CNF,

    TI_CNAS_HSD_WAIT_RRM_STATUS_IND,

    TI_CNAS_HSD_WAIT_CAS_SUSPEND_REL_CNF,

    TI_CNAS_HSD_TIMER_BUTT
};
typedef VOS_UINT32  CNAS_HSD_TIMER_ID_ENUM_UINT32;

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

#endif /* end of CnasHsdTimerMgmt.h */
