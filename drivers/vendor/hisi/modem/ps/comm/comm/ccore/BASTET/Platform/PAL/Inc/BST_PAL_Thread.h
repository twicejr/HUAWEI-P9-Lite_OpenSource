/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_PAL_Thread.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年06月26日
  最近修改   :
  功能描述   : 定Win32操作系统线程处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月28日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

#ifndef __BST_PAL_THREAD_H__
#define __BST_PAL_THREAD_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "vos.h"
#include "VosPidDef.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_OS_PalGetCurrentThreadId()  ( BST_NULL_PTR )
#define BST_OS_PalDefineLock( tLock )   BST_UINT32  tLock
#define BST_OS_PalThreadLock()          VOS_SplIMP()
#define BST_OS_PalThreadUnLock(tLock)   VOS_Splx(tLock)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/

/*****************************************************************************
  5 类/结构定义
*****************************************************************************/
typedef VOS_SPINLOCK                    BST_OS_PAL_SPINLOCK_T;
typedef VOS_UINT32                      BST_OS_PAL_THREAD_ID;
typedef VOS_INT32                       BST_OS_PAL_LOCKCNT_T;
/*****************************************************************************
  6 UNION定义
*****************************************************************************/

/*****************************************************************************
  7 全局变量声明
*****************************************************************************/

/*****************************************************************************
  8 函数声明
*****************************************************************************/
BST_VOID                BST_OS_PalInitLock     ( BST_VOID );

BST_VOID                BST_OS_PalInitSpinLock ( BST_OS_PAL_SPINLOCK_T *pSpinLock );

BST_UINT32              BST_OS_PalSpinLock     ( BST_OS_PAL_SPINLOCK_T *pSpinLock );

BST_VOID                BST_OS_PalSpinUnLock   (
    BST_OS_PAL_SPINLOCK_T  *pSpinLock,
    BST_UINT32              ulCounter );

BST_VOID                BST_OS_PalCreateThread (
    BST_INT8               *pacTaskName,
    BST_OS_THREAD_T         ThreadEntry,
    BST_VOID               *pvArg,
    BST_UINT32              ulStackSize,
    BST_UINT32              ulPrio );


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif
