/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   :
  Version     : V100R001
  Date        : 2005-04-19
  Description :
  History     :
  1. Date:2005-04-19
     Author: w29695
     Modification:Create
*******************************************************************************/

#if !defined(_FRMWK_EXT_H_)
#define _FRMWK_EXT_H_



#include "PsCommonDef.h"


typedef VOS_SEM      MUTEX_ID;    /* 互斥量的标识类型定义 */
typedef VOS_SEM      SEMAPHORE_ID;      /* 信号量的标识类型定义 */
typedef VOS_UINT32   THREAD_ID;    /* 线程的标识类型定义 */
typedef VOS_PID      MSGQUE_ID;                         /* 消息队列的标识类型定义 */


/* 表示肯定/否定的全局宏 */
#define    WUEPS_TRUE               0
#define    WUEPS_FALSE              1

#define    WUEPS_OK                 0
#define    WUEPS_NG                 1

/* 表示无效的全局宏 */
#define    WUEPS_INVALID            (-1)

/* 取两数的最大值/最小值的全局宏 */
#define    WUEPS_MAX(a,b)           (((a)>(b)) ? (a) : (b))
#define    WUEPS_MIN(a,b)           (((a)<=(b))? (a) : (b))

/* ASSERT定义 */
#define    WUEPS_ASSERT( exp )      if( (exp) == 0 ){VOS_ASSERT(exp);}

#ifndef PS_RAND_MAX
#define PS_RAND_MAX 0x7fff
#endif

#define WUEPS_MUTEX_WAIT_TIME          20

#if(VOS_WIN32 == VOS_OS_VER)
#define WUEPS_SEMA_WAIT_TIME           30
#endif

/* WuepsLock返回值定义 */
#define WUEPS_LOCK_SUCCESS  (VOS_INT32)0                     /* 加锁成功 */
#define WUEPS_LOCK_FAILURE  (VOS_INT32)((VOS_INT)-1)             /* 加锁失败 */

/* WuepsUnlock返回值定义 */
#define WUEPS_UNLOCK_SUCCESS    (VOS_INT32)0                 /* 解锁成功 */
#define WUEPS_UNLOCK_FAILURE    (VOS_INT32)((VOS_INT)-1)         /* 解锁失败 */

/* WuepsMutexCreate返回值定义 */
#define WUEPS_MUTEX_CREATE_SUCCESS  (VOS_INT32)0             /* 创建成功 */
#define WUEPS_MUTEX_CREATE_FAILURE  ((VOS_INT32)-1)          /* 创建失败 */

/* WuepsMutexDestroy返回值定义 */
#define WUEPS_MUTEX_DESTROY_SUCCESS     (VOS_INT32)0         /* 删除成功 */
#define WUEPS_MUTEX_DESTROY_FAILURE     (VOS_INT32)((VOS_INT)-1) /* 删除失败 */

/* WuepsSemaphoreLock返回值定义 */
#define WUEPS_SEMAPHORE_LOCK_SUCCESS  (VOS_INT32)0               /* 加锁成功 */
#define WUEPS_SEMAPHORE_LOCK_FAILURE  ((VOS_INT32)-1)            /* 加锁失败 */

/* WuepsSemaphoreUnlock返回值定义 */
#define WUEPS_SEMAPHORE_UNLOCK_SUCCESS    (VOS_INT32)0           /* 解锁成功 */
#define WUEPS_SEMAPHORE_UNLOCK_FAILURE    (VOS_INT32)((int)-1)   /* 解锁失败 */

/* WuepsSemaphoreCreate返回值定义 */
#define WUEPS_SEMAPHORE_CREATE_SUCCESS  (VOS_INT32)0             /* 创建成功 */
#define WUEPS_SEMAPHORE_CREATE_FAILURE  (VOS_INT32)(-1)            /* 创建失败 */

/* WuepsSemaphoreDestroy返回值定义 */
#define WUEPS_SEMAPHORE_DESTROY_SUCCESS     (VOS_INT32)0         /* 销毁成功 */
#define WUEPS_SEMAPHORE_DESTROY_FAILURE     (VOS_INT32)((int)-1) /* 销毁失败 */

/* ulWaitOption值定义 */
#define WUEPS_SEMAPHORE_WAIT          ((VOS_INT32)-1)    /* 等待     */
#define WUEPS_SEMAPHORE_NO_WAIT       (VOS_INT32)0      /* 不等待   */

#define WUEPS_TIMER_TICK  10

extern VOS_INT32 WuepsLock(MUTEX_ID *pMutexId);
extern VOS_INT32 WuepsUnlock(MUTEX_ID *pMutexId);
extern VOS_INT32 WuepsSemaphoreCreate(SEMAPHORE_ID *pSemaphoreId,
                          const VOS_CHAR   *pcName,VOS_UINT32 ulInitCount);
extern VOS_INT32 WuepsSemaphoreDestroy(SEMAPHORE_ID *pSemaphoreId);
extern VOS_INT32 WuepsSemaphoreLock(SEMAPHORE_ID *pSemaphoreId,VOS_UINT32 ulWaitOption);
extern VOS_INT32 WuepsSemaphoreUnlock(SEMAPHORE_ID *pSemaphoreId);
extern VOS_INT32 WuepsMutexCreate(MUTEX_ID *pMutexId);
extern VOS_INT32 WuepsMutexDestroy(MUTEX_ID *pMutexId);



#define WUEPS_MAX_PID_NUM    40

/***********************************************
 *
 * FrameWork操作的返回值的定义
 *
 **********************************************/
#define WUEPS_FRAMEWORK_SUCCESS (VOS_INT32)0         /* FrameWork操作的成功标志  */
#define WUEPS_FRAMEWORK_FAILURE ((VOS_INT32)-1)      /* FrameWork操作的失败标志  */


/***********************************************
 *
 * 全局函数的外部声明
 *
 **********************************************/

#endif  /* !defined(_FRMWK_EXT_H_) */

/***************************** End Of File ***********************************/
