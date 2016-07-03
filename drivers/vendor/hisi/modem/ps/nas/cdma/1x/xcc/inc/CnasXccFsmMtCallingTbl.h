

#ifndef __CNAS_XCC_FSM_MT_CALLING_TBL_H__
#define __CNAS_XCC_FSM_MT_CALLING_TBL_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "NasFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CNAS_XCC_GetMtCallingStaTbl()                          (g_astCnasXccMtCallingStaTbl)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


enum CNAS_XCC_MT_CALLING_STA_ENUM
{
    CNAS_XCC_MT_CALLING_STA_INIT                        ,     /* 初始化 */

    CNAS_XCC_MT_CALLING_STA_WAIT_APS_SUSPEND_RSP        ,     /* 等待APS挂起回复 */

    CNAS_XCC_MT_CALLING_STA_WAIT_AS_EST_CNF             ,     /* 等待AS建联回复 */

    CNAS_XCC_MT_CALLING_STA_WAIT_AS_CALL_INIT           ,     /* 等待AS电话指示 */

    CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ORDER              ,     /* 等待ORDER指示 */

    CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER             ,     /* 等待应答指示 */

    CNAS_XCC_MT_CALLING_STA_WAIT_CONNECT_L2_ACK         ,     /* 等待L2连接回复 */

    CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP       ,     /* 等待来电回复 */

    CNAS_XCC_MT_CALLING_STA_BUTT
};

typedef VOS_UINT32  CNAS_XCC_MT_CALLING_STA_ENUM_UINT32;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern NAS_FSM_DESC_STRU                    g_stCnasXccMtCallingFsmDesc;
extern NAS_STA_STRU                         g_astCnasXccMtCallingStaTbl[];

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

VOS_UINT32 CNAS_XCC_GetMtCallingStaTblSize(VOS_VOID);

NAS_FSM_DESC_STRU * CNAS_XCC_GetMtCallingFsmDescAddr(VOS_VOID);


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

#endif /* end of CnasXccFsmPreProcTbl.h */


