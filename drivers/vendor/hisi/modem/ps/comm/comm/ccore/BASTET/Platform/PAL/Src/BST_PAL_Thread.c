/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_PAL_Thread.c
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年05月04日
  最近修改   :
  功能描述   : 操作系统线程处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月28日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_Typedefine.h"
#include "BST_PAL_Thread.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_PAL_THREAD_C
/*lint +e767*/
/******************************************************************************
   2 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : BST_OS_PalInitLock
 功能描述  : 初始化系统锁(空接口，Balong平台不需要)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_OS_PalInitLock( BST_VOID )
{
}

/*****************************************************************************
 函 数 名  : BST_OS_PalInitSpinLock
 功能描述  : 初始化自旋锁
 输入参数  : BST_OS_PAL_SPINLOCK_T *pSpinLock  自旋锁句柄
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_OS_PalInitSpinLock( BST_OS_PAL_SPINLOCK_T *pSpinLock )
{
    if( BST_NULL_PTR == pSpinLock )
    {
        return;
    }
    VOS_SpinLockInit( pSpinLock );
}
/*****************************************************************************
 函 数 名  : BST_OS_PalSpinLock
 功能描述  : 自旋锁锁定平台适配实现
 输入参数  : BST_OS_PAL_SPINLOCK_T *pSpinLock   自旋锁句柄
 输出参数  : 无
 返 回 值  : BST_UINT32                         自旋锁定深度
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_OS_PalSpinLock( BST_OS_PAL_SPINLOCK_T *pSpinLock )
{
    BST_UINT32                          ulFlags = 0;
    VOS_SpinLockIntLock( pSpinLock, ulFlags );
    return ulFlags;
}
/*****************************************************************************
 函 数 名  : BST_OS_PalSpinUnLock
 功能描述  : 自旋锁解除平台适配实现
 输入参数  : BST_OS_PAL_SPINLOCK_T *pSpinLock,  自旋锁句柄
             BST_UINT32 ulCounter               锁定深度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_OS_PalSpinUnLock( BST_OS_PAL_SPINLOCK_T *pSpinLock, BST_UINT32 ulCounter )
{
    if( BST_NULL_PTR == pSpinLock )
    {
        return;
    }
    VOS_SpinUnlockIntUnlock( pSpinLock, ulCounter );
}
/*****************************************************************************
 函 数 名  : BST_OS_PalTaskEntry
 功能描述  : 通用任务入口函数，实现4入参接口转化为2入参接口
 输入参数  : BST_UINT32 ulPara1,    真正执行的任务指针(BST_OS_THREAD_T)
             BST_UINT32 ulPara2,    任务输入参数(BST_VOID *)
             BST_UINT32 ulPara3,
             BST_UINT32 ulPara4
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_OS_PalTaskEntry( BST_UINT32 ulPara1, BST_UINT32 ulPara2,
                              BST_UINT32 ulPara3, BST_UINT32 ulPara4 )
{
    BST_OS_THREAD_T     pTaskFun;
    BST_VOID           *pArg;

    pTaskFun            = ( BST_OS_THREAD_T )ulPara1;
    pArg                = ( BST_VOID * )ulPara2;

    if ( BST_NULL_PTR == pTaskFun )
    {
        return;
    }

    pTaskFun( pArg );
}

/*****************************************************************************
 函 数 名  : BST_OS_PalCreateThread
 功能描述  : 新建线程
 输入参数  : BST_INT8* pacTaskName,         任务名称
             BST_OS_THREAD_T  ThreadEntry,  任务入口函数
             BST_VOID* pvArg,               任务输入参数
             BST_UINT32 ulStackSize,        任务堆栈深度
             BST_UINT32 ulPrio              任务优先级
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_OS_PalCreateThread (
    BST_INT8       *pacTaskName,
    BST_OS_THREAD_T ThreadEntry,
    BST_VOID       *pvArg,
    BST_UINT32      ulStackSize,
    BST_UINT32      ulPrio )
{
    BST_UINT32  aulTaskParam[ VOS_TARG_NUM ] = { 0 };
    BST_UINT32  ulTaskId;
    BST_UINT32  ulRet;
    BST_UINT32  ulRealPriority;

#if( VOS_TARG_NUM < 2 )

    return;
#endif

    aulTaskParam[0] = ( BST_UINT32 )ThreadEntry;
    aulTaskParam[1] = ( BST_UINT32 )pvArg;

    ulRet           =  VOS_GetFIdRelPri( ( enum VOS_PRIORITY_DEFINE )ulPrio, &ulRealPriority );
    if ( ulRet != VOS_OK )
    {
        BST_RLS_LOG( "BST_OS_PalCreateThread: VOS_GetFIdRelPri Failed!" );
        return;
    }

    VOS_CreateTask( ( BST_CHAR *)pacTaskName, 
                    &ulTaskId,
                    ( VOS_TASK_ENTRY_TYPE )BST_OS_PalTaskEntry,
                    ulRealPriority,
                    ulStackSize,
                    aulTaskParam );

}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


