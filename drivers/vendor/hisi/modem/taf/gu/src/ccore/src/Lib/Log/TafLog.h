
#ifndef _TAF_LOG_H_
#define _TAF_LOG_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#include "Taf_Common.h"
#include "msp_diag_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 全局变量定义
*****************************************************************************/


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define    TAF_INFO_LOG(Mod, String)                                    TAF_LOG  ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String) )
#define    TAF_INFO_LOG1(Mod, String,Para1)                             TAF_LOG1 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1) )
#define    TAF_INFO_LOG2(Mod, String,Para1,Para2)                       TAF_LOG2 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    TAF_INFO_LOG3(Mod, String,Para1,Para2,Para3)                 TAF_LOG3 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    TAF_INFO_LOG4(Mod, String,Para1,Para2,Para3,Para4)           TAF_LOG4 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    TAF_NORMAL_LOG(Mod, String)                                  TAF_LOG  ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String) )
#define    TAF_NORMAL_LOG1(Mod, String,Para1)                           TAF_LOG1 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1) )
#define    TAF_NORMAL_LOG2(Mod, String,Para1,Para2)                     TAF_LOG2 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    TAF_NORMAL_LOG3(Mod, String,Para1,Para2,Para3)               TAF_LOG3 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    TAF_NORMAL_LOG4(Mod, String,Para1,Para2,Para3,Para4)         TAF_LOG4 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    TAF_WARNING_LOG(Mod, String)                                 TAF_LOG  ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String) )
#define    TAF_WARNING_LOG1(Mod, String,Para1)                          TAF_LOG1 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1) )
#define    TAF_WARNING_LOG2(Mod, String,Para1,Para2)                    TAF_LOG2 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    TAF_WARNING_LOG3(Mod, String,Para1,Para2,Para3)              TAF_LOG3 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    TAF_WARNING_LOG4(Mod, String,Para1,Para2,Para3,Para4)        TAF_LOG4 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    TAF_ERROR_LOG(Mod, String)                                   TAF_LOG  ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String) )
#define    TAF_ERROR_LOG1(Mod, String,Para1)                            TAF_LOG1 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1) )
#define    TAF_ERROR_LOG2(Mod, String,Para1,Para2)                      TAF_LOG2 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    TAF_ERROR_LOG3(Mod, String,Para1,Para2,Para3)                TAF_LOG3 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    TAF_ERROR_LOG4(Mod, String,Para1,Para2,Para3,Para4)          TAF_LOG4 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )


#define    TAF_LOG(Mod, SubMod, Level, String) \
           (VOS_VOID)DIAG_LogReport( DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(Mod), DIAG_MODE_UMTS, (Level)), \
                           (Mod), __FILE__, __LINE__, "%s \r\n", (String) )

#define    TAF_LOG1(Mod, SubMod, Level, String, Para1) \
           (VOS_VOID)DIAG_LogReport( DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(Mod), DIAG_MODE_UMTS, (Level)), \
                           (Mod), __FILE__, __LINE__, "%s, %d \r\n", (String), (VOS_INT32)(Para1) )

#define    TAF_LOG2(Mod, SubMod, Level, String, Para1, Para2) \
           (VOS_VOID)DIAG_LogReport( DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(Mod), DIAG_MODE_UMTS, (Level)), \
                           (Mod), __FILE__, __LINE__, "%s, %d, %d \r\n", (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )

#define    TAF_LOG3(Mod, SubMod, Level, String, Para1, Para2, Para3) \
           (VOS_VOID)DIAG_LogReport( DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(Mod), DIAG_MODE_UMTS, (Level)), \
                           (Mod), __FILE__, __LINE__, "%s, %d, %d, %d \r\n", (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )

#define    TAF_LOG4(Mod, SubMod, Level, String, Para1, Para2, Para3, Para4) \
           (VOS_VOID)DIAG_LogReport( DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(Mod), DIAG_MODE_UMTS, (Level)), \
                           (Mod), __FILE__, __LINE__, "%s, %d, %d, %d, %d \r\n", (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


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

#endif
