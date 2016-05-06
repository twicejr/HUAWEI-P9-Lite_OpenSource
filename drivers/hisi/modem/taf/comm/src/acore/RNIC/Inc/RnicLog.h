
#ifndef __RNIC_LOG_H__
#define __RNIC_LOG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#include "PsCommonDef.h"
/* Added by wx270776 for OM融合, 2015-6-27, begin */
#include "AtMntn.h"
/* Added by wx270776 for OM融合, 2015-6-27, end */

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*================================================*/
/* 数值宏定义 */
/*================================================*/
#define     RNIC_MEM_FAIL()              TAF_LOG(ACPU_PID_RNIC, 0, PS_LOG_LEVEL_ERROR, "RNIC Mem Operation Failed!");
#define     RNIC_MSG_FAIL()              TAF_LOG(ACPU_PID_RNIC, 0, PS_LOG_LEVEL_ERROR, "RNIC Msg Opration Failed!");
#define     RNIC_TIMER_FAIL()            TAF_LOG(ACPU_PID_RNIC, 0, PS_LOG_LEVEL_ERROR, "RNIC Timer Opration Failed!");

/*================================================*/
/* 功能函数宏定义 */
/*================================================*/
#ifndef SUBMOD_NULL
#define    SUBMOD_NULL                                                  (0)
#endif

#define    RNIC_INFO_LOG(Mod, String)                                    TAF_LOG ( (Mod), SUBMOD_NULL,  PS_LOG_LEVEL_INFO, (String) )
#define    RNIC_INFO_LOG1(Mod, String,Para1)                             TAF_LOG1 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1) )
#define    RNIC_INFO_LOG2(Mod, String,Para1,Para2)                       TAF_LOG2 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    RNIC_INFO_LOG3(Mod, String,Para1,Para2,Para3)                 TAF_LOG3 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    RNIC_INFO_LOG4(Mod, String,Para1,Para2,Para3,Para4)           TAF_LOG4 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    RNIC_NORMAL_LOG(Mod, String)                                  TAF_LOG ( (Mod), SUBMOD_NULL,  PS_LOG_LEVEL_NORMAL, (String) )
#define    RNIC_NORMAL_LOG1(Mod, String,Para1)                           TAF_LOG1 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1) )
#define    RNIC_NORMAL_LOG2(Mod, String,Para1,Para2)                     TAF_LOG2 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    RNIC_NORMAL_LOG3(Mod, String,Para1,Para2,Para3)               TAF_LOG3 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    RNIC_NORMAL_LOG4(Mod, String,Para1,Para2,Para3,Para4)         TAF_LOG4 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    RNIC_WARNING_LOG(Mod, String)                                 TAF_LOG ( (Mod), SUBMOD_NULL,  PS_LOG_LEVEL_WARNING, (String) )
#define    RNIC_WARNING_LOG1(Mod, String,Para1)                          TAF_LOG1 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1) )
#define    RNIC_WARNING_LOG2(Mod, String,Para1,Para2)                    TAF_LOG2 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    RNIC_WARNING_LOG3(Mod, String,Para1,Para2,Para3)              TAF_LOG3 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    RNIC_WARNING_LOG4(Mod, String,Para1,Para2,Para3,Para4)        TAF_LOG4 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    RNIC_ERROR_LOG(Mod, String)                                   TAF_LOG ( (Mod), SUBMOD_NULL,  PS_LOG_LEVEL_ERROR, (String) )
#define    RNIC_ERROR_LOG1(Mod, String,Para1)                            TAF_LOG1 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1) )
#define    RNIC_ERROR_LOG2(Mod, String,Para1,Para2)                      TAF_LOG2 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    RNIC_ERROR_LOG3(Mod, String,Para1,Para2,Para3)                TAF_LOG3 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    RNIC_ERROR_LOG4(Mod, String,Para1,Para2,Para3,Para4)          TAF_LOG4 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

/*******************************************************************************
  3 枚举定义
*******************************************************************************/

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

#endif /* RnicLog.h */



