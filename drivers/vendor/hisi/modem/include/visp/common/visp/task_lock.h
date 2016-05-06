/*
 * task_lock.h
 *
 * This is the BRL - big task lock. only for VRP.
 * It can be running in Linux or VxWorks envrioment.
 * Notes :
 * __CONFIG_PREEMPT_BRL : lock preeption compile macro

 * author: liuyong 42922@huawei
 * date  : 2008-07-25
 */
#ifndef __TASK_LOCK_H
#define __TASK_LOCK_H

#if (VOS_OS_VER == VOS_LINUX) 
#include <pthread.h>
#include <sys/syscall.h>

#endif


/*
 * compile macro.
 */

#define __CONFIG_PREEMPT_BRL


/*
 * Generic compiler-dependent macros required for 
 * build go below this comment. Actual compiler/compiler version
 * specific implementations come from the above header files
 *
 * branch prediction built-macro:
 * MIPS32 or MIPS64 specificlly deprecate to use it. 
 * by LiuYong
 */
#define __builtin_expect(expr, val) (expr)

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)



#ifdef __PC_LINT__
#define __SIZEOF_PTHREAD_MUTEX_T 24
#define __SIZEOF_PTHREAD_MUTEXATTR_T 4


/* Data structures for mutex handling.  The structure of the attribute
   type is not exposed on purpose.  */
typedef union
{
    struct
    {
        int __lock;
        unsigned int __count;
        int __owner;
        /* KIND must stay at this position in the structure to maintain
           binary compatibility.  */
        int __kind;
        unsigned int __nusers;
        int __spins;
    } __data;
    
    char __size[__SIZEOF_PTHREAD_MUTEX_T];
    long int __align;
} pthread_mutex_t;

typedef union
{
  char __size[__SIZEOF_PTHREAD_MUTEXATTR_T];
  long int __align;
} pthread_mutexattr_t;

#endif




#if (VOS_OS_VER == VOS_LINUX) 
/* struct */
typedef pthread_mutex_t semphore_lock;   
#elif (VOS_OS_VER == VOS_VXWORKS)
/* pointer */
typedef struct semaphore* semphore_lock;     
#endif




#define BUG()\
do{\
    printf("\nBugs:File(%s), Line(%u), Function(%s).\n", \
       (__FILE__),(__LINE__),(__FUNCTION__));\
}while(0)



#define BUG_ON(p) do { if (p) BUG(); } while (0)

/* vos_printf存在大量的阻塞性操作
 */
#define tsk_printf    printf


/* TASK_LOCKED: take big task lock.
 * TASK_UNLOCKED: do not take big task lock.
 */
#define TASK_LOCK    (0x55)
#define TASK_UNLOCK  (0xAA)


extern long int syscall (long int __sysno, ...);

#if (VOS_OS_VER == VOS_LINUX)
#if (VOS_HARDWARE_PLATFORM == VOS_MIPS)
#define __CUR_THREAD_ID  syscall(4222)
#else
#define __CUR_THREAD_ID  syscall(224)
#endif
#elif (VOS_OS_VER == VOS_VXWORKS)
#define __CUR_THREAD_ID taskIdCurrent
#endif

extern void TCPIP_ProductLock(void);
extern void TCPIP_ProductUnLock(void);
/* Modified by yanlei00216869, 【代码检视】通过增加编译宏控制，使得以.so方式提供给bluestar的visp，不依赖产品代码, 2014/10/25   问题单号:DTS2014102504024  */
#if ( (VOS_OS_VER == VOS_LINUX) && (TCPIP_FOR_BLUESTAR == VRP_NO) )
/*End of Modified by yanlei00216869, 2014/10/25   问题单号:DTS2014102504024  */
#define VRP_LOCK()  TCPIP_ProductLock()
#define VRP_UNLOCK() TCPIP_ProductUnLock()
#else
#define VRP_LOCK()
#define VRP_UNLOCK()
#endif

/*
 * extern function
 */
int lock_init(void);
void __task_lock_init(void);
void __task_lock(void);
void __task_unlock(void);
unsigned long __task_lock_status(void);
int __task_lock_owner(void);

#if (VOS_OS_VER == VOS_LINUX) 
int __mutex_init(semphore_lock *mutex);
int __mutex_lock(semphore_lock * mutex);
int __mutex_unlock(semphore_lock * mutex);
void __mutex_show(int level);
int __mutex_unlock_force(semphore_lock * mutex);

void __task_reg_delete_hook(void);

#endif

#endif  /* #ifndef __TASK_LOCK_H */
