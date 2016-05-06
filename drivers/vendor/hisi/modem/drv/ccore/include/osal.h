/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : os_adapt.h
  版 本 号   : 初稿
  作    者   : 李江雄 00134988
  生成日期   : 2013年9月4日
  最近修改   :
  功能描述   : 封装系统函数
  函数列表   :
  修改历史   :
  1.日    期   : 2013年9月4日
    作    者   : 李江雄 00134988
    修改内容   : 创建文件

  说明:
******************************************************************************
  History:                                                                *
    *   1. Date        :                                                  *
    *      Author      :                                                  *
    *      Modification:                                                  *
******************************************************************************/
#ifndef _OS_ADAPT_H
#define _OS_ADAPT_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#ifdef __OS_RTOSCK__
#include <sre_sem.h>
#include <sre_mem.h>
#include <sre_task.h>
#include <sre_hwi.h>
#include <sre_exc.h>
#include <sre_mmu.h>
#include <osl_types.h>
#include <stdarg.h>
#include <sre_io_intf.h>
#else
#include <vxWorks.h>
#include <semLib.h>
#include <memPartLib.h>
#include <vmLibCommon.h>
#endif

#ifndef OSAL_OK
#define OSAL_ERROR              (-1)
#define OSAL_OK                 (0)
#define OSAL_NULL               (0)
#endif

/******************************************************************************
                        semaphore adapt
******************************************************************************/
#ifdef __OS_RTOSCK__
#define OSAL_SEM_FULL       OS_SEM_FULL
#define OSAL_SEM_EMPTY      OS_SEM_EMPTY

#define OSAL_SEM_PRIORITY       SEM_MODE_PRIOR
#define OSAL_SEM_FIFO           SEM_MODE_FIFO
#define OSAL_SEM_INVERSION_SAFE  0x08

#define OSAL_WAIT_FOREVER       OS_WAIT_FOREVER
#define OSAL_NO_WAIT            0
#define OSAL_MEM_ALIGN          4
#else
#define OSAL_SEM_FULL       SEM_FULL
#define OSAL_SEM_EMPTY      SEM_EMPTY

#define OSAL_SEM_PRIORITY       SEM_Q_PRIORITY
#define OSAL_SEM_FIFO           SEM_Q_FIFO
#define OSAL_SEM_DELETE_SAFE    SEM_DELETE_SAFE
#define OSAL_SEM_INVERSION_SAFE    SEM_INVERSION_SAFE

#define OSAL_WAIT_FOREVER       WAIT_FOREVER
#define OSAL_NO_WAIT            NO_WAIT
#endif

#define OSAL_TRUE      1
#define OSAL_FALSE     0

#ifdef _DRV_LLT_
typedef void *    OSAL_SEM_ID;
#else
#ifdef __OS_RTOSCK__
typedef SEM_HANDLE_T  OSAL_SEM_ID;
#else
typedef SEM_ID     OSAL_SEM_ID;
#endif
#endif

extern int OSAL_SemMCreate (OSAL_SEM_ID *mutex, int options);
extern int OSAL_SemBCreate (OSAL_SEM_ID *mutex,int count, int options);
extern int OSAL_SemCCreate (OSAL_SEM_ID *mutex,int count, int options);
extern int OSAL_SemTake(OSAL_SEM_ID mtx_h,unsigned int timeout);
extern int OSAL_SemGive(OSAL_SEM_ID mtx_h);
extern int osal_semDelete(OSAL_SEM_ID * mtx_h);
#define OSAL_SemDelete(sem) osal_semDelete(&sem)


/******************************************************************************
                        memory adapt
******************************************************************************/
#ifdef __OS_RTOSCK__
#define VM_STATE_MASK_VALID		    0x40
#define VM_STATE_MASK_WRITABLE		0x3F

#define OSAL_VM_STATE_VALID
#define OSAL_VM_STATE_VALID_NOT
#define OSAL_VM_STATE_WRITABLE               OS_MMU_STATE_WRITE
#define OSAL_VM_STATE_WRITABLE_NOT           (OS_MMU_STATE_READ|OS_MMU_STATE_EXE)
#define OSAL_VM_STATE_CACHEABLE              OS_MMU_STATE_CACHE_WBWA
#define OSAL_VM_STATE_CACHEABLE_NOT          OS_MMU_STATE_CACHE_OFF
#define OSAL_VM_STATE_CACHEABLE_WRITETHROUGH

#elif defined(__OS_VXWORKS__)
#define OSAL_VM_STATE_VALID             VM_STATE_VALID
#define OSAL_VM_STATE_VALID_NOT         VM_STATE_VALID_NOT
#define OSAL_VM_STATE_WRITABLE               VM_STATE_WRITABLE
#define OSAL_VM_STATE_WRITABLE_NOT           VM_STATE_WRITABLE_NOT
#define OSAL_VM_STATE_CACHEABLE              VM_STATE_CACHEABLE
#define OSAL_VM_STATE_CACHEABLE_NOT          VM_STATE_CACHEABLE_NOT
#define OSAL_VM_STATE_CACHEABLE_WRITETHROUGH VM_STATE_CACHEABLE_WRITETHROUGH
#endif

extern void * OSAL_Malloc (unsigned int nBytes );
extern void * OSAL_Calloc (unsigned int elemNum, unsigned int Bytes);
extern void * OSAL_Realloc ( void * pBlock,	unsigned int newSize	);
extern void * OSAL_MemAlign ( unsigned int align_size,unsigned int nBytes );
extern void * OSAL_CacheDmaMalloc ( unsigned int nBytes );
extern void OSAL_Free( void *ptr);
extern int OSAL_CacheDmaFree ( void *ptr );
/*suggest don't use this function */
extern int OSAL_VmStateSet ( void *context,unsigned int virtAdrs, unsigned int len, \
            unsigned int stateMask,unsigned int state);
extern int OSAL_MmuPageMap(void *context, unsigned int uwVirtAddr, unsigned int uwPhysAddr, \
    unsigned int uwLen, unsigned int uwStateMask, unsigned int uwState);
extern int OSAL_MmuEnable(int enable);
/******************************************************************************
                        task adapt
******************************************************************************/
#ifdef _DRV_LLT_
#define OSAL_TASK_FUNC    FUNCPTR
typedef void *    OSAL_TASK_ID;
#else
#ifdef __OS_RTOSCK__
#define OSAL_TASK_FUNC    TSK_ENTRY_FUNC
typedef unsigned int      OSAL_TASK_ID;
#else
#define OSAL_TASK_FUNC    FUNCPTR
typedef int               OSAL_TASK_ID;
#endif
#endif
#ifdef __OS_RTOSCK__
#define OSAL_FUNCPTR OS_VOID_FUNC
#else
#define OSAL_FUNCPTR FUNCPTR
#endif

extern int OSAL_TaskCreate(OSAL_TASK_ID *task, char *name,int priority,
    int options,int stackSize,OSAL_TASK_FUNC entryPt,int arg1,
    int arg2,int arg3,int arg4);

extern int osal_taskDelete( OSAL_TASK_ID * tskid );
extern int OSAL_TaskSuspend(OSAL_TASK_ID  task );
extern int OSAL_TaskDelay(int ticks );
extern int OSAL_TaskSelf(void);
extern int OSAL_TaskIdByName(char * name);
extern int OSAL_TaskPriorityGet(int  task, int * pPriority);
extern int OSAL_TaskPrioritySet(int task, int pPriority);
extern int OSAL_TaskIdListGet(int idList[], unsigned int maxTasks, unsigned int *pTaskNum);
extern void OSAL_TaskLock(void);
extern void OSAL_TaskUnLock(void);
extern int OSAL_TaskCreateHookAdd(OSAL_FUNCPTR hook);
extern int OSAL_TaskSwitchHookAdd(OSAL_FUNCPTR hook);
extern int OSAL_TaskCreateHookDel(OSAL_FUNCPTR hook);
extern int OSAL_TaskSwitchHookDel(OSAL_FUNCPTR hook);
extern int OSAL_IntHookAdd(OSAL_FUNCPTR in_hook,OSAL_FUNCPTR out_hook);
extern int OSAL_ExcHookAdd(OSAL_FUNCPTR hook);
#define OSAL_TaskDelete(tskid)  osal_taskDelete((OSAL_TASK_ID *)&tskid)
extern int OSAL_TaskIDVerify(int taskID);
extern int OSAL_TaskNameGet(int taskID,char **pName);

/******************************************************************************
                        interrupter adapt
******************************************************************************/

#ifdef __OS_RTOSCK__
#define OSAL_INTERRUPT_FUNC    HWI_PROC_FUNC
#else
#define OSAL_INTERRUPT_FUNC    VOIDFUNCPTR
#endif

extern int OSAL_IntConnect( unsigned int num, OSAL_INTERRUPT_FUNC routine, int parameter );
extern int OSAL_IntDisconnect( unsigned int num, OSAL_INTERRUPT_FUNC routine, int parameter );
extern int OSAL_IntEnable( unsigned int num );
extern int OSAL_IntDisable( unsigned int num );
extern int OSAL_IntLock(void);
extern void OSAL_IntUnLock( int s32Lvl);
extern unsigned int OSAL_INT_CONTEXT(void);

/******************************************************************************
                        cache adapt
******************************************************************************/
typedef enum				/* CACHE_TYPE */
{
    OSAL_INSTRUCTION_CACHE ,
    OSAL_DATA_CACHE
} OSAL_CACHE_TYPE;

#ifdef __OS_RTOSCK__
#define OSAL_CACHE_ALIGN_SIZE    32
#else
#define OSAL_CACHE_ALIGN_SIZE    _CACHE_ALIGN_SIZE
#endif

extern int OSAL_CacheFlush( OSAL_CACHE_TYPE type,void *address,unsigned int bytes  );
extern int OSAL_CacheInvalid( OSAL_CACHE_TYPE type,void *address,unsigned int bytes  );

/******************************************************************************
                        system adapt
******************************************************************************/
#ifdef __OS_RTOSCK__
typedef  long long   OSAL_TICK_T;
#else
typedef  unsigned long    OSAL_TICK_T;
#endif

#ifdef __OS_RTOSCK__
typedef int (* OSAL_TIMER_HANDLER)(int para);

struct SysWdTime
{
    int     delay;              /* delay count, in ticks */
    OSAL_TIMER_HANDLER pRoutine;           /* routine to call on time-out */
    int     parameter;           /* parameter with which to call routine */
    int    flag;
} ;
extern int OSAL_TickISR(void);
extern int  OSAL_WdTimerReg (int delay,OSAL_TIMER_HANDLER pRoutine, int para );
#endif
extern OSAL_TICK_T OSAL_TickGet( void );
extern void OSAL_TickSet( OSAL_TICK_T tick );
extern int OSAL_SysClkRateGet( void );

/******************************************************************************
                        shell adapt
******************************************************************************/
typedef enum
{
    OSAL_SHELL_UART = 1 ,
    OSAL_SHELL_USB
} OSAL_SHELL_TYPE;

typedef enum
{
    OSAL_SHELL_OPEN ,
    OSAL_SHELL_CLOSE
} OSAL_SHELL_MODE;
#ifdef __OS_RTOSCK__
extern void OSAL_SetShellType(OSAL_SHELL_TYPE type);
extern OSAL_SHELL_TYPE OSAL_GetShellType(void);
extern void OSAL_SetShellMode(OSAL_SHELL_MODE mode);
extern OSAL_SHELL_MODE OSAL_GetShellMode(void);
extern unsigned int OSAL_SendChrToShell(OSAL_SHELL_TYPE shelltype,unsigned char ucChar );
#endif


/******************************************************************************
                        clock adapt
******************************************************************************/
#ifdef __OS_RTOSCK__

/*每秒tick数*/
#define TICK_PER_SEC TIMER_DEFAULT_TICKS

/* 1000 million nanoseconds / second */
#define BILLION         1000000000

/*将目前tick数转换为s以及ns*/
#define CONVERT_TO_SEC(a,b)  \
do { \
        register int hz = TICK_PER_SEC; \
	    (a).tv_sec  = (int)((b) / hz);   \
	    (a).tv_nsec = (int)(((b) % hz) * (BILLION / hz)); \
   } while (0)

typedef unsigned long osal_time_t;


struct os_timespec
{
    osal_time_t tv_sec;
    long tv_nsec;
};


extern int os_clock_gettime(int clock_id,struct os_timespec * tp);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _OS_ADAPT_H */
