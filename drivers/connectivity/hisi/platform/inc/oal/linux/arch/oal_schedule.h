

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

/* 获取毫秒级时间戳*/
#define OAL_TIME_GET_STAMP_MS() jiffies_to_msecs(jiffies)

/* 获取高精度毫秒时间戳,精度1ms*/
#define OAL_TIME_GET_HIGH_PRECISION_MS()  oal_get_time_stamp_from_timeval()

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


OAL_STATIC OAL_INLINE oal_void  oal_spin_lock(oal_spin_lock_stru *pst_lock)
{
    oal_spin_lock_magic_bug(pst_lock);
    spin_lock(&pst_lock->lock);
}


OAL_STATIC OAL_INLINE oal_void  oal_spin_unlock(oal_spin_lock_stru *pst_lock)
{
    oal_spin_lock_magic_bug(pst_lock);
    spin_unlock(&pst_lock->lock);
}


OAL_STATIC OAL_INLINE oal_void oal_spin_lock_bh(oal_spin_lock_stru *pst_lock)
{
    oal_spin_lock_magic_bug(pst_lock);
    spin_lock_bh(&pst_lock->lock);
}


OAL_STATIC OAL_INLINE oal_void oal_spin_unlock_bh(oal_spin_lock_stru *pst_lock)
{
     oal_spin_lock_magic_bug(pst_lock);
     spin_unlock_bh(&pst_lock->lock);
}


OAL_STATIC OAL_INLINE oal_void  oal_spin_lock_irq_save(oal_spin_lock_stru *pst_lock, oal_uint *pui_flags)
{
    oal_spin_lock_magic_bug(pst_lock);
    spin_lock_irqsave(&pst_lock->lock, *pui_flags);
}


OAL_STATIC OAL_INLINE oal_void  oal_spin_unlock_irq_restore(oal_spin_lock_stru *pst_lock, oal_uint *pui_flags)
{
    oal_spin_lock_magic_bug(pst_lock);
    spin_unlock_irqrestore(&pst_lock->lock, *pui_flags);
}


OAL_STATIC OAL_INLINE oal_uint32  oal_spin_lock_irq_exec(oal_spin_lock_stru *pst_lock, oal_irqlocked_func func, oal_void *p_arg, oal_uint *pui_flags)
{
    oal_uint32  ul_rslt;

    spin_lock_irqsave(&pst_lock->lock, *pui_flags);

    ul_rslt = func(p_arg);

    spin_unlock_irqrestore(&pst_lock->lock, *pui_flags);

    return ul_rslt;
}


OAL_STATIC OAL_INLINE oal_void  oal_rw_lock_init(oal_rwlock_stru *pst_lock)
{
    rwlock_init(pst_lock);
}


OAL_STATIC OAL_INLINE oal_void  oal_rw_lock_read_lock(oal_rwlock_stru *pst_lock)
{
    read_lock(pst_lock);
}


OAL_STATIC OAL_INLINE oal_void  oal_rw_lock_read_unlock(oal_rwlock_stru *pst_lock)
{
    read_unlock(pst_lock);
}


OAL_STATIC OAL_INLINE oal_void  oal_rw_lock_write_lock(oal_rwlock_stru *pst_lock)
{
    write_lock(pst_lock);
}


OAL_STATIC OAL_INLINE oal_void  oal_rw_lock_write_unlock(oal_rwlock_stru *pst_lock)
{
    write_unlock(pst_lock);
}



OAL_STATIC OAL_INLINE oal_void  oal_task_init(oal_tasklet_stru *pst_task, oal_defer_func p_func, oal_void *p_args)
{
    tasklet_init(pst_task, p_func, (oal_uint)p_args);
}


OAL_STATIC OAL_INLINE oal_void oal_task_kill(oal_tasklet_stru *pst_task)
{
    return tasklet_kill(pst_task);
}


OAL_STATIC OAL_INLINE oal_void  oal_task_sched(oal_tasklet_stru *pst_task)
{
    tasklet_schedule(pst_task);
}


OAL_STATIC OAL_INLINE oal_uint oal_task_is_scheduled(oal_tasklet_stru *pst_task)
{
    return test_bit(TASKLET_STATE_SCHED, (oal_uint *)&pst_task->state);
}


OAL_STATIC OAL_INLINE oal_int32  oal_atomic_read(oal_atomic *p_vector)
{
    return atomic_read(p_vector);
}


OAL_STATIC OAL_INLINE oal_void  oal_atomic_set(oal_atomic *p_vector, oal_int32 l_val)
{
    atomic_set(p_vector, l_val);
}


OAL_STATIC OAL_INLINE oal_void oal_atomic_dec(oal_atomic *p_vector)
{
    atomic_dec(p_vector);
}


OAL_STATIC OAL_INLINE oal_void  oal_atomic_inc(oal_atomic *p_vector)
{
    atomic_inc(p_vector);
}


OAL_STATIC OAL_INLINE oal_int32  oal_atomic_inc_and_test(oal_atomic *p_vector)
{
    return atomic_inc_and_test(p_vector);
}


OAL_STATIC OAL_INLINE oal_int32  oal_atomic_dec_and_test(oal_atomic *p_vector)
{
    return atomic_dec_and_test(p_vector);
}


OAL_STATIC OAL_INLINE oal_void  oal_time_get_stamp_us(oal_time_us_stru *pst_usec)
{
    struct timespec ts;

    getnstimeofday(&ts);

    pst_usec->i_sec     = ts.tv_sec;

    pst_usec->i_usec    = ts.tv_nsec /1000;

}


OAL_STATIC OAL_INLINE oal_time_t_stru oal_ktime_get(oal_void)
{
    return ktime_get();
}


OAL_STATIC OAL_INLINE oal_time_t_stru oal_ktime_sub(const oal_time_t_stru lhs, const oal_time_t_stru rhs)
{
    return ktime_sub(lhs, rhs);
}


OAL_STATIC OAL_INLINE oal_void  oal_timer_init(oal_timer_list_stru *pst_timer, oal_uint32 ul_delay, oal_timer_func p_func, oal_uint ui_arg)
{
    init_timer(pst_timer);
    pst_timer->expires = jiffies + msecs_to_jiffies(ul_delay);
    pst_timer->function = p_func;
    pst_timer->data = ui_arg;
}


OAL_STATIC OAL_INLINE oal_int32  oal_timer_delete(oal_timer_list_stru *pst_timer)
{
    return del_timer(pst_timer);
}


OAL_STATIC OAL_INLINE oal_int32  oal_timer_delete_sync(oal_timer_list_stru *pst_timer)
{
    return del_timer_sync(pst_timer);
}


OAL_STATIC OAL_INLINE oal_void  oal_timer_add(oal_timer_list_stru *pst_timer)
{
    add_timer(pst_timer);
}


OAL_STATIC OAL_INLINE oal_int32  oal_timer_start(oal_timer_list_stru *pst_timer, oal_uint ui_delay)
{
    return mod_timer(pst_timer, (jiffies + msecs_to_jiffies(ui_delay)));
}


OAL_STATIC OAL_INLINE oal_void  oal_timer_start_on(oal_timer_list_stru *pst_timer, oal_uint ui_delay, oal_int32 cpu)
{
    pst_timer->expires = jiffies + msecs_to_jiffies(ui_delay);
    add_timer_on(pst_timer, cpu);
}


OAL_STATIC OAL_INLINE oal_uint32  oal_copy_from_user(oal_void *p_to, const oal_void *p_from, oal_uint32 ul_size)
{
    return (oal_uint32)copy_from_user(p_to, p_from, (oal_uint)ul_size);
}


OAL_STATIC OAL_INLINE oal_uint32  oal_copy_to_user(oal_void *p_to, const oal_void *p_from, oal_uint32 ul_size)
{
    return (oal_uint32)copy_to_user(p_to, p_from, (oal_uint)ul_size);
}


OAL_STATIC OAL_INLINE oal_proc_dir_entry_stru* oal_create_proc_entry(const oal_int8 *pc_name, oal_uint16 us_mode, oal_proc_dir_entry_stru *pst_parent)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
    return NULL;
#else
    return create_proc_entry(pc_name, us_mode, pst_parent);
#endif
}


OAL_STATIC OAL_INLINE void oal_remove_proc_entry(const oal_int8 *pc_name, oal_proc_dir_entry_stru *pst_parent)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
#else
    return remove_proc_entry(pc_name, pst_parent);
#endif
}


OAL_STATIC OAL_INLINE oal_uint32 oal_time_is_before(oal_uint ui_time)
{
    return (oal_uint32)time_is_before_jiffies(ui_time);
}


OAL_STATIC OAL_INLINE oal_uint32 oal_time_after(oal_uint32 ul_time_a, oal_uint32 ul_time_b)
{
    return (oal_uint32)time_after((oal_ulong)ul_time_a, (oal_ulong)ul_time_b);
}

OAL_INLINE static char* oal_get_current_task_name(oal_void)
{
	return current->comm;
}

OAL_STATIC OAL_INLINE oal_uint32  oal_wait_for_completion_timeout(oal_completion *pst_completion, oal_uint32 ul_timeout)
{
    return wait_for_completion_timeout(pst_completion, ul_timeout);
}

#ifdef _PRE_OAL_FEATURE_TASK_NEST_LOCK

extern oal_void _oal_smp_task_lock_(oal_task_lock_stru* pst_lock,oal_ulong  claim_addr);
#define oal_smp_task_lock(lock)    _oal_smp_task_lock_(lock, (oal_ulong)_THIS_IP_)


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


OAL_STATIC OAL_INLINE oal_void oal_smp_task_lock_init(oal_task_lock_stru* pst_lock)
{
    oal_memset((oal_void*)pst_lock,0,sizeof(oal_task_lock_stru));

	oal_spin_lock_init(&pst_lock->lock);
	OAL_WAIT_QUEUE_INIT_HEAD(&pst_lock->wq);
	pst_lock->claimed = 0;
	pst_lock->claim_cnt = 0;
}
#endif


OAL_STATIC OAL_INLINE oal_uint64 oal_get_time_stamp_from_timeval(oal_void)
{
    struct timeval tv;
    oal_uint64 curr_time;

    do_gettimeofday(&tv);
    curr_time = tv.tv_usec;
    do_div(curr_time, 1000);
    curr_time = curr_time + tv.tv_sec * 1000;

    return curr_time;

}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_schedule.h */
