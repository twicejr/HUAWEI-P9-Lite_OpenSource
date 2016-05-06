/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : oal_schedule.h
  版 本 号   : 初稿
  作    者   : t00231215
  生成日期   : 2012年11月29日
  最近修改   :
  功能描述   : oal_types.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月29日
    作    者   : t00231215
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_LINUX_SCHEDULE_H__
#define __OAL_LINUX_SCHEDULE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
/*lint -e322*/
#include <asm/atomic.h>
#include <linux/spinlock.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/jiffies.h>
#include <linux/time.h>
#include <asm/param.h>
#include <linux/timer.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/ktime.h>

#ifdef CONFIG_HAS_WAKELOCK
#include <linux/wakelock.h>
#endif

/*lint +e322*/

/*****************************************************************************
  2 宏定义
*****************************************************************************/

typedef atomic_t                oal_atomic;

#define OAL_SPIN_LOCK_MAGIC_TAG (0xdead4ead)
typedef struct _oal_spin_lock_stru_
{
#ifdef CONFIG_SPIN_LOCK_MAGIC_DEBUG
    oal_uint32  magic;
    oal_uint32  reserved;
#endif
    spinlock_t  lock;
}oal_spin_lock_stru;

#ifdef CONFIG_SPIN_LOCK_MAGIC_DEBUG
#define OAL_DEFINE_SPINLOCK(x) 	 oal_spin_lock_stru x = {\
            .magic = OAL_SPIN_LOCK_MAGIC_TAG,\
            .lock = __SPIN_LOCK_UNLOCKED(x)}
#else
#define OAL_DEFINE_SPINLOCK(x) 	 oal_spin_lock_stru x = {\
            .lock = __SPIN_LOCK_UNLOCKED(x)}
#endif

/* 函数指针，用来指向需要自旋锁保护的的函数 */
typedef oal_uint32              (*oal_irqlocked_func)(oal_void *);

typedef rwlock_t                oal_rwlock_stru;
typedef struct timer_list              oal_timer_list_stru;


typedef struct tasklet_struct       oal_tasklet_stru;
typedef oal_void                    (*oal_defer_func)(oal_uint);

/* tasklet声明 */
#define OAL_DECLARE_TASK    DECLARE_TASKLET

typedef wait_queue_t         oal_wait_queue_stru;
typedef wait_queue_head_t    oal_wait_queue_head_stru;

/**
 * wait_event_interruptible_timeout - sleep until a condition gets true or a timeout elapses
 * @_wq: the waitqueue to wait on
 * @_condition: a C expression for the event to wait for
 * @_timeout: timeout, in jiffies
 *
 * The process is put to sleep (TASK_INTERRUPTIBLE) until the
 * @condition evaluates to true or a signal is received.
 * The @condition is checked each time the waitqueue @wq is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the wait condition.
 *
 * The function returns 0 if the @timeout elapsed, -ERESTARTSYS if it
 * was interrupted by a signal, and the remaining jiffies otherwise
 * if the condition evaluated to true before the timeout elapsed.
 */
#define OAL_WAIT_EVENT_INTERRUPTIBLE_TIMEOUT(_st_wq, _condition, _timeout) \
    wait_event_interruptible_timeout(_st_wq, _condition, _timeout)

#define OAL_WAIT_EVENT_TIMEOUT(_st_wq, _condition, _timeout) \
    wait_event_timeout(_st_wq, _condition, _timeout)

#define OAL_WAIT_EVENT_INTERRUPTIBLE(_st_wq, _condition)\
    wait_event_interruptible(_st_wq, _condition)

#define OAL_WAIT_QUEUE_WAKE_UP_INTERRUPT(_pst_wq)     wake_up_interruptible(_pst_wq)

#define OAL_WAIT_QUEUE_WAKE_UP(_pst_wq)     wake_up(_pst_wq)

#define OAL_INTERRUPTIBLE_SLEEP_ON(_pst_wq) interruptible_sleep_on(_pst_wq)

#define OAL_WAIT_QUEUE_INIT_HEAD(_pst_wq)   init_waitqueue_head(_pst_wq)

/* 获取毫秒级时间戳 */
#define OAL_TIME_GET_STAMP_MS() jiffies_to_msecs(jiffies)

#define OAL_ENABLE_CYCLE_COUNT()
#define OAL_DISABLE_CYCLE_COUNT()
#define OAL_GET_CYCLE_COUNT() 0

/* 寄存器反转模块运行时间计算 */
#define OAL_TIME_CALC_RUNTIME(_ul_start, _ul_end)   ((((OAL_TIME_US_MAX_LEN) / HZ) * 1000) + ((OAL_TIME_US_MAX_LEN) % HZ) * (1000 / HZ) - (_ul_start) + (_ul_end))

#define OAL_TIME_JIFFY    jiffies

#define OAL_TIME_HZ       HZ

#define OAL_MSECS_TO_JIFFIES(_msecs)    msecs_to_jiffies(_msecs)

#define OAL_JIFFIES_TO_MSECS(_jiffies)      jiffies_to_msecs(_jiffies)

#define OAL_INIT_COMPLETION(_my_completion) init_completion(_my_completion)

#define OAL_COMPLETE(_my_completion)        complete(_my_completion)

#define oal_in_interrupt()  in_interrupt()

#define oal_in_atomic()     in_atomic()
typedef void (*oal_timer_func)(oal_uint);

typedef oal_uint32 (*oal_module_func_t)(oal_void);

/* 模块入口 */
#define oal_module_init(_module_name)   module_init(_module_name)

#define oal_module_license(_license_name) MODULE_LICENSE(_license_name)

#define oal_module_param    module_param

#define OAL_S_IRUGO         S_IRUGO

/* 模块出口 */
#define oal_module_exit(_module_name)   module_exit(_module_name)

/* 模块符号导出 */
#define oal_module_symbol(_symbol)      EXPORT_SYMBOL(_symbol)
#define OAL_MODULE_DEVICE_TABLE(_type, _name) MODULE_DEVICE_TABLE(_type, _name)

#define oal_smp_call_function_single(core, task, info, wait) smp_call_function_single(core, task, info, wait)

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
typedef struct proc_dir_entry       oal_proc_dir_entry_stru;

typedef struct mutex                oal_mutex_stru;

typedef struct completion           oal_completion;


typedef struct
{
    oal_int i_sec;
    oal_int i_usec;
}oal_time_us_stru;

typedef ktime_t oal_time_t_stru;

typedef struct _oal_task_lock_stru_
{
    oal_wait_queue_head_stru	wq;
    struct task_struct	*claimer;	/* task that has host claimed */
    oal_spin_lock_stru		lock;		/* lock for claim and bus ops */
    oal_ulong			 claim_addr;
    oal_uint32           claimed;
    oal_int32			 claim_cnt;
}oal_task_lock_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : oal_spin_lock_init
 功能描述  : 自旋锁初始化，把自旋锁设置为1（未锁状态）。
 输入参数  : *pst_lock: 锁的地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月19日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_spin_lock_init(oal_spin_lock_stru *pst_lock)
{
    spin_lock_init(&pst_lock->lock);
#ifdef CONFIG_SPIN_LOCK_MAGIC_DEBUG	
    pst_lock->magic = OAL_SPIN_LOCK_MAGIC_TAG;
#endif
}

OAL_STATIC OAL_INLINE oal_void  oal_spin_lock_magic_bug(oal_spin_lock_stru *pst_lock)
{
#ifdef CONFIG_SPIN_LOCK_MAGIC_DEBUG
    if(OAL_UNLIKELY((oal_uint32)OAL_SPIN_LOCK_MAGIC_TAG != pst_lock->magic))
    {
#ifdef CONFIG_PRINTK
        /*spinlock never init or memory overwrite?*/
    	printk(KERN_EMERG "[E]SPIN_LOCK_BUG: spinlock:%p on CPU#%d, %s,magic:%08x should be %08x\n", pst_lock,
    	                    raw_smp_processor_id(),current->comm, pst_lock->magic,OAL_SPIN_LOCK_MAGIC_TAG);
        print_hex_dump(KERN_EMERG, "spinlock_magic: ", DUMP_PREFIX_ADDRESS, 16, 1,
	       (oal_uint8 *)((oal_ulong)pst_lock - 32), 32 + sizeof(oal_spin_lock_stru) + 32, true);
        printk(KERN_EMERG"\n");
#endif
        OAL_WARN_ON(1);
    }
#endif
}

/*****************************************************************************
 函 数 名  : oal_spin_lock
 功能描述  : 自旋锁在软中断以及内核线程等核心态上下文环境下的加锁操作。如果
             能够立即获得锁，它就马上返回，否则，它将自旋在那里，直到该自旋
             锁的保持者释放，这时，它获得锁并返回。
 输入参数  : *pst_lock:自旋锁地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月19日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_spin_lock(oal_spin_lock_stru *pst_lock)
{
    oal_spin_lock_magic_bug(pst_lock);
    spin_lock(&pst_lock->lock);
}

/*****************************************************************************
 函 数 名  : oal_spin_unlock
 功能描述  : Spinlock在内核线程等核心态上下文环境下的解锁操作。
 输入参数  : *pst_lock:自旋锁地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月19日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_spin_unlock(oal_spin_lock_stru *pst_lock)
{
    oal_spin_lock_magic_bug(pst_lock);
    spin_unlock(&pst_lock->lock);
}

/*****************************************************************************
 函 数 名  : oal_spin_lock_bh
 功能描述  : 自旋锁在软中断以及内核线程等核心态上下文环境下的加锁操作。如果
             能够立即获得锁，它就马上返回，否则，它将自旋在那里，直到该自旋
             锁的保持者释放，这时，它获得锁并返回。
 输入参数  : pst_lock:自旋锁地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_spin_lock_bh(oal_spin_lock_stru *pst_lock)
{
    oal_spin_lock_magic_bug(pst_lock);
    spin_lock_bh(&pst_lock->lock);
}

/*****************************************************************************
 函 数 名  : oal_spin_unlock_bh
 功能描述  : Spinlock在软中断以及内核线程等核心态上下文环境下的解锁操作。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_spin_unlock_bh(oal_spin_lock_stru *pst_lock)
{
     oal_spin_lock_magic_bug(pst_lock);
     spin_unlock_bh(&pst_lock->lock);
}

/*****************************************************************************
 函 数 名  : oal_spin_lock_irq_save
 功能描述  : 获得自旋锁的同时获得保存标志寄存器的值，并且失效本地中断。
 输入参数  : *pst_lock:自旋锁地址
             pui_flags:标志寄存器
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_spin_lock_irq_save(oal_spin_lock_stru *pst_lock, oal_uint *pui_flags)
{
    oal_spin_lock_magic_bug(pst_lock);
    spin_lock_irqsave(&pst_lock->lock, *pui_flags);
}

/*****************************************************************************
 函 数 名  : oal_spin_unlock_irq_restore
 功能描述  : 释放自旋锁的同时，恢复标志寄存器的值，恢复本地中断。它与oal_sp-
             in_lock_irq配对使用
 输入参数  : *pst_lock:自旋锁地址
             pui_flags:标志寄存器
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_spin_unlock_irq_restore(oal_spin_lock_stru *pst_lock, oal_uint *pui_flags)
{
    oal_spin_lock_magic_bug(pst_lock);
    spin_unlock_irqrestore(&pst_lock->lock, *pui_flags);
}

/*****************************************************************************
 函 数 名  : oal_spin_lock_irq_exec
 功能描述  : 获取自旋锁，关闭中断，执行某个函数，完了之后再打开中断，释放自
             旋锁。
 输入参数  : *pst_lock:自旋锁地址
             func：函数指针地址
             *p_arg：函数参数
             *pui_flags: 中断标志寄存器
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_spin_lock_irq_exec(oal_spin_lock_stru *pst_lock, oal_irqlocked_func func, oal_void *p_arg, oal_uint *pui_flags)
{
    oal_uint32  ul_rslt;

    spin_lock_irqsave(&pst_lock->lock, *pui_flags);

    ul_rslt = func(p_arg);

    spin_unlock_irqrestore(&pst_lock->lock, *pui_flags);

    return ul_rslt;
}

/*****************************************************************************
 函 数 名  : oal_rw_lock_init
 功能描述  : 读写锁初始化，把读写锁设置为1（未锁状态）。
 输入参数  : pst_lock: 读写锁结构体地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月12日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_rw_lock_init(oal_rwlock_stru *pst_lock)
{
    rwlock_init(pst_lock);
}

/*****************************************************************************
 函 数 名  : oal_rw_lock_read_lock
 功能描述  : 获得指定的读锁
 输入参数  : pst_lock: 读写锁结构体地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月12日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_rw_lock_read_lock(oal_rwlock_stru *pst_lock)
{
    read_lock(pst_lock);
}

/*****************************************************************************
 函 数 名  : oal_rw_lock_read_unlock
 功能描述  : 释放指定的读锁
 输入参数  : pst_lock: 读写锁结构体地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月12日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_rw_lock_read_unlock(oal_rwlock_stru *pst_lock)
{
    read_unlock(pst_lock);
}

/*****************************************************************************
 函 数 名  : oal_rw_lock_write_lock
 功能描述  : 获得指定的写锁
 输入参数  : pst_lock: 读写锁结构体地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月12日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_rw_lock_write_lock(oal_rwlock_stru *pst_lock)
{
    write_lock(pst_lock);
}

/*****************************************************************************
 函 数 名  : oal_rw_lock_write_unlock
 功能描述  : 释放指定的写锁
 输入参数  : pst_lock: 读写锁结构体地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月12日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_rw_lock_write_unlock(oal_rwlock_stru *pst_lock)
{
    write_unlock(pst_lock);
}


/*****************************************************************************
 函 数 名  : oal_task_init
 功能描述  : 任务初始化。初始化完成后，任务处于挂起状态。
 输入参数  : pst_task: 任务结构体指针
             func: 任务处理函数入口地址
             p_args: 需进行处理的函数的入参地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月8日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_task_init(oal_tasklet_stru *pst_task, oal_defer_func p_func, oal_void *p_args)
{
    tasklet_init(pst_task, p_func, (oal_uint)p_args);
}

/*****************************************************************************
 函 数 名  : oal_task_kill
 功能描述  : 退出task运行
 输入参数  : pst_task: 任务结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月29日
    作    者   : wangjianchang wWX278082
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_task_kill(oal_tasklet_stru *pst_task)
{
    return tasklet_kill(pst_task);
}

/*****************************************************************************
 函 数 名  : oal_task_sched
 功能描述  : 任务调度，令任务处于准备就绪状态；当任务执行完后，又回到挂起状
             态。
 输入参数  : pst_task: 任务结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月8日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_task_sched(oal_tasklet_stru *pst_task)
{
    tasklet_schedule(pst_task);
}

/*****************************************************************************
 函 数 名  : oal_task_is_scheduled
 功能描述  : 检测tasklet是否等待执行
 输入参数  : pst_task: 任务结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : wangjianchang wWX278082
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint oal_task_is_scheduled(oal_tasklet_stru *pst_task)
{
    return test_bit(TASKLET_STATE_SCHED, (oal_uint *)&pst_task->state);
}

/*****************************************************************************
 函 数 名  : oal_atomic_read
 功能描述  : 读取原子变量的值
 输入参数  : *p_vector: 需要进行原子操作的原子变量地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月26日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_atomic_read(oal_atomic *p_vector)
{
    return atomic_read(p_vector);
}

/*****************************************************************************
 函 数 名  : oal_atomic_set
 功能描述  : 原子地设置原子变量p_vector值为ul_val
 输入参数  : p_vector: 需要进行原子操作的原子变量地址
             l_val  : 需要被设置成的值
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月11日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_atomic_set(oal_atomic *p_vector, oal_int32 l_val)
{
    atomic_set(p_vector, l_val);
}

/*****************************************************************************
 函 数 名  : oal_atomic_dec
 功能描述  : 原子的给入参减1，
 输入参数  : *p_vector: 需要进行原子操作的原子变量地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_atomic_dec(oal_atomic *p_vector)
{
    atomic_dec(p_vector);
}

/*****************************************************************************
 函 数 名  : oal_atomic_inc
 功能描述  : 原子的给如参加一
 输入参数  : *p_vector: 需要进行原子操作的原子变量地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月26日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_atomic_inc(oal_atomic *p_vector)
{
    atomic_inc(p_vector);
}

/*****************************************************************************
 函 数 名  : oal_atomic_inc_and_test
 功能描述  : 原子递增后检查结果是否为0
 输入参数  : *p_vector: 需要进行原子操作的原子变量地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月10日
    作    者   : d00262548
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_atomic_inc_and_test(oal_atomic *p_vector)
{
    return atomic_inc_and_test(p_vector);
}

/*****************************************************************************
 函 数 名  : oal_atomic_dec_and_test
 功能描述  : 原子递减后检查结果是否为0
 输入参数  : *p_vector: 需要进行原子操作的原子变量地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月10日
    作    者   : d00262548
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_atomic_dec_and_test(oal_atomic *p_vector)
{
    return atomic_dec_and_test(p_vector);
}

/*****************************************************************************
 函 数 名  : oal_time_get_stamp_us
 功能描述  : 获取微妙精度级的时间戳
 输入参数  : pst_usec: 时间结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月30日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_time_get_stamp_us(oal_time_us_stru *pst_usec)
{
    struct timespec ts;

    getnstimeofday(&ts);

    pst_usec->i_sec     = ts.tv_sec;

    pst_usec->i_usec    = ts.tv_nsec /1000;

}

/*****************************************************************************
 函 数 名  : oal_ktime_get
 功能描述  : 调用内核函数获取当前时间戳
 输入参数  : oal_void
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月27日
    作    者   : w00346925
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_time_t_stru oal_ktime_get(oal_void)
{
    return ktime_get();
}

/*****************************************************************************
 函 数 名  : oal_ktime_sub
 功能描述  : 调用内核函数获取时间差值
 输入参数  : const oal_time_t_stru lhs,
             const oal_time_t_stru rhs
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月27日
    作    者   : w00346925
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_time_t_stru oal_ktime_sub(const oal_time_t_stru lhs, const oal_time_t_stru rhs)
{
    return ktime_sub(lhs, rhs);
}

/*****************************************************************************
 函 数 名  : oal_timer_init
 功能描述  : 初始化定时器
 输入参数  : pst_timer: 定时器结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_timer_init(oal_timer_list_stru *pst_timer, oal_uint32 ul_delay, oal_timer_func p_func, oal_uint ui_arg)
{
    init_timer(pst_timer);
    pst_timer->expires = jiffies + msecs_to_jiffies(ul_delay);
    pst_timer->function = p_func;
    pst_timer->data = ui_arg;
}

/*****************************************************************************
 函 数 名  : oal_timer_delete
 功能描述  : 删除定时器
 输入参数  : pst_timer: 定时器结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_timer_delete(oal_timer_list_stru *pst_timer)
{
    return del_timer(pst_timer);
}

/*****************************************************************************
 函 数 名  : oal_timer_delete_sync
 功能描述  : 同步删除定时器，用于多核
 输入参数  : pst_timer: 定时器结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_timer_delete_sync(oal_timer_list_stru *pst_timer)
{
    return del_timer_sync(pst_timer);
}

/*****************************************************************************
 函 数 名  : oal_timer_add
 功能描述  : 激活定时器
 输入参数  : pst_timer: 定时器结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_timer_add(oal_timer_list_stru *pst_timer)
{
    add_timer(pst_timer);
}

/*****************************************************************************
 函 数 名  : oal_timer_start
 功能描述  : 重启定时器
 输入参数  : pst_timer: 结构体指针
             ui_expires: 重启的溢出事件
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_timer_start(oal_timer_list_stru *pst_timer, oal_uint ui_delay)
{
    return mod_timer(pst_timer, (jiffies + msecs_to_jiffies(ui_delay)));
}

/*****************************************************************************
 函 数 名  : oal_timer_start_on
 功能描述  : 指定cpu,重启定时器,调用时timer要处于非激活状态否者会死机
 输入参数  : pst_timer: 结构体指针
             ui_expires: 重启的溢出事件
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月20日
    作    者   : z00262551
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_timer_start_on(oal_timer_list_stru *pst_timer, oal_uint ui_delay, oal_int32 cpu)
{
    pst_timer->expires = jiffies + msecs_to_jiffies(ui_delay);
    add_timer_on(pst_timer, cpu);
}

/*****************************************************************************
 函 数 名  : oal_copy_from_user
 功能描述  : 将用户态数据拷贝到内核态
 输入参数  : p_to: 目的地
             p_from : 源
             ul_size : 需要拷贝的长度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月12日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_copy_from_user(oal_void *p_to, const oal_void *p_from, oal_uint32 ul_size)
{
    return (oal_uint32)copy_from_user(p_to, p_from, (oal_uint)ul_size);
}

/*****************************************************************************
 函 数 名  : oal_copy_to_user
 功能描述  : 将内核态数据拷贝到用户态
 输入参数  : p_to: 目的地
             p_from : 源
             ul_size : 需要拷贝的长度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月27日
    作    者   : duankaiyong 00194999
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_copy_to_user(oal_void *p_to, const oal_void *p_from, oal_uint32 ul_size)
{
    return (oal_uint32)copy_to_user(p_to, p_from, (oal_uint)ul_size);
}

/*****************************************************************************
 函 数 名  : oal_create_proc_entry
 功能描述  : 创建proc_entry结构体
 输入参数  : pc_name: 创建的proc_entry的名字
             us_mode: 创建模式
             pst_parent: 母proc_entry结构体，继承属性
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月12日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_proc_dir_entry_stru* oal_create_proc_entry(const oal_int8 *pc_name, oal_uint16 us_mode, oal_proc_dir_entry_stru *pst_parent)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
    return NULL;
#else
    return create_proc_entry(pc_name, us_mode, pst_parent);
#endif
}

/*****************************************************************************
 函 数 名  : oal_remove_proc_entry
 功能描述  : 创建proc_entry结构体
 输入参数  : pc_name: 创建的proc_entry的名字
             pst_parent: 母proc_entry结构体，继承属性
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月12日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE void oal_remove_proc_entry(const oal_int8 *pc_name, oal_proc_dir_entry_stru *pst_parent)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
#else
    return remove_proc_entry(pc_name, pst_parent);
#endif
}

/*****************************************************************************
 函 数 名  : oal_time_is_before
 功能描述  : 判断ul_time是否比当前时间早
             若早，表示超时时间已过；若不早，表明还未超时
 输入参数  : oal_uint ui_time
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月20日,星期二
    作    者   : y00201072
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 oal_time_is_before(oal_uint ui_time)
{
    return (oal_uint32)time_is_before_jiffies(ui_time);
}

/*****************************************************************************
 函 数 名  : oal_time_after
 功能描述  : 判断时间戳ul_time_a是否在ul_time_b之后:
 输入参数  : oal_uint ui_time
 输出参数  : 无
 返 回 值  : Return: 1 ul_time_a在ul_time_b之后; 否则 Return: 0
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月10日
    作    者   : w00357635
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 oal_time_after(oal_uint32 ul_time_a, oal_uint32 ul_time_b)
{
    return (oal_uint32)time_after((oal_ulong)ul_time_a, (oal_ulong)ul_time_b);
}

OAL_INLINE static char* oal_get_current_task_name(oal_void)
{
	return current->comm;
}
/*****************************************************************************
 函 数 名  : oal_wait_for_completion_timeout
 功能描述  : 同步：等待超时检查
 输入参数  : 无
 输出参数  : 无
 返 回 值  : Return: 0 if timed out, and positive (at least 1, or number of jiffies left till timeout) if completed.
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : z00273164
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_wait_for_completion_timeout(oal_completion *pst_completion, oal_uint32 ul_timeout)
{
    return wait_for_completion_timeout(pst_completion, ul_timeout);
}

#ifdef _PRE_OAL_FEATURE_TASK_NEST_LOCK
/*****************************************************************************
 函 数 名  : oal_smp_task_lock
 功能描述  : lock the task, the lock can be double locked by the same process
 输入参数  : 
             
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
extern oal_void _oal_smp_task_lock_(oal_task_lock_stru* pst_lock,oal_ulong  claim_addr);
#define oal_smp_task_lock(lock)    _oal_smp_task_lock_(lock, (oal_ulong)_THIS_IP_)

/*****************************************************************************
 函 数 名  : oal_smp_task_unlock
 功能描述  : unlock the task
 输入参数  : 
             
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月28日
    作    者   : z00262551
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_smp_task_unlock(oal_task_lock_stru* pst_lock)
{
	oal_ulong flags;

	if(OAL_WARN_ON(in_interrupt() || in_atomic()))
	{
	    return;
	}

    if(OAL_UNLIKELY(!pst_lock->claimed))
    {
        OAL_WARN_ON(1);
        return;
    }

    oal_spin_lock_irq_save(&pst_lock->lock, &flags);
	if(--pst_lock->claim_cnt)
	{
	    oal_spin_unlock_irq_restore(&pst_lock->lock, &flags);
	}
	else
	{
		pst_lock->claimed = 0;
		pst_lock->claimer = NULL;
		oal_spin_unlock_irq_restore(&pst_lock->lock, &flags);
		wake_up(&pst_lock->wq);
	}
}

/*****************************************************************************
 函 数 名  : oal_smp_task_lock_init
 功能描述  : task struct init
 输入参数  : 
             
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月28日
    作    者   : z00262551
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_smp_task_lock_init(oal_task_lock_stru* pst_lock)
{
    oal_memset((oal_void*)pst_lock,0,sizeof(oal_task_lock_stru));

	oal_spin_lock_init(&pst_lock->lock);
	OAL_WAIT_QUEUE_INIT_HEAD(&pst_lock->wq);
	pst_lock->claimed = 0;
	pst_lock->claim_cnt = 0;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_schedule.h */
