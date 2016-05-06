/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_CORE_PTask.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年05月04日
  最近修改   :
  功能描述   : 定义循环型任务类BST_CORE_PTask
  函数列表   :
  修改历史   :
  1.日    期   : 2014年05月13日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

#ifndef __BST_CORE_P_TASK_H__
#define __BST_CORE_P_TASK_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_CORE_Task.h"


#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_CORE_GetCycleToMs(ulCyc)    ( (ulCyc)*BST_SRV_DTC_BAS_UNT )
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/

/*****************************************************************************
  5 类/结构定义
*****************************************************************************/
class BST_CTaskSchdler;
class BST_SRV_CHbDetector;

class BST_CORE_CPTask :
    BST_PUBLIC BST_CTask
{
BST_PUBLIC:
    BST_ERR_ENUM_UINT8                  ConfigCycleTicks( BST_UINT32 ulTickFct );
    BST_VOID                            Suspend         ( BST_VOID );
    BST_VOID                            Maintain        ( BST_VOID );
    BST_VOID                            Waiting         ( BST_VOID );
    BST_UINT32                          IsBusy          ( BST_VOID );
    BST_VOID                            Finished        ( BST_VOID );
    BST_VOID                            TxStart         ( BST_VOID );
    virtual BST_VOID                    onUpdateCycle   ( BST_UINT16 ulDetCycle );
    virtual BST_VOID                    onCycleError     ( BST_VOID );
    BST_VOID                            onExecute       ( BST_VOID );
    friend class                        BST_CTaskSchdler;
    friend class                        BST_SRV_CHbDetector;
BST_PROTECTED:
    BST_TICK_T                          m_ulCycle;
    BST_TICK_T                          m_ulSuspCounter;
    BST_UINT32                          m_ulBusyFlag;
                                        BST_CORE_CPTask ( BST_PROCID_T in_usProcId,
                                                          BST_TASKID_T in_usTaskId );
    virtual                            ~BST_CORE_CPTask ( BST_VOID );
};

/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/


/*****************************************************************************
  8 函数声明
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif


