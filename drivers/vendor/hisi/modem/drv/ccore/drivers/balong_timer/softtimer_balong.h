#include <hi_base.h>
#include <hi_timer.h>
#include <soc_interrupts.h>
#include <bsp_memmap.h>
#include <bsp_hardtimer.h>
#include <osl_irq.h>
/*lint -e{652,760}*/
/*∫Í∂®“Â*/
#ifndef OK
#define OK 0
#endif
#ifndef ERROR
#define ERROR (-1)
#endif
#define NOT_ACTIVE  1

#ifndef SEM_EMPTY
#define SEM_EMPTY 0
#endif

#ifndef SEM_FULL
#define SEM_FULL 1
#endif
#define SOFTTIMER_MAX_NUM 40

#ifdef __KERNEL__
typedef u32             SOFTTIMER_TASK_ID;
#define TIMER_TASK_WAKE_PRI         92
#define TIMER_TASK_NOWAKE_PRI   92

#elif defined(__OS_VXWORKS__)||defined(__OS_RTOSCK__)
typedef u32 SOFTTIMER_TASK_ID;
#define TIMER_TASK_WAKE_PRI         6
#define TIMER_TASK_NOWAKE_PRI   6
#endif

#define  TIMER_TASK_STK_SIZE            (0x1000)
#define ELAPESD_TIME_INVAILD             0xFFFFFFFF


