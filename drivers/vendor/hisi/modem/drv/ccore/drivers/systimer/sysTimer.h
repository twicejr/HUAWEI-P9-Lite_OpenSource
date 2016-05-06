/*************************************************************************
*   版权所有(C) 1987-2004, 深圳华为技术有限公司.
*
*   文 件 名 :  CLK.h
*
*   作    者 :  liumengcun
*
*   描    述 :  用户时钟头文件
*
*   修改记录 :  2009年3月5日  v1.00  liumengcun  创建
*
*************************************************************************/

#ifndef _CLK_H_
#define _CLK_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "bsp_memmap.h"
#include "soc_interrupts.h"
#include <soc_timer.h>

#ifndef _ASMLANGUAGE
typedef  void (*SYSCLKFUNCPTR)(int);
#endif

/* frequency of counter/timers */
#define SYS_TIMER_CLK           CCORE_SYS_TIMER_CLK
#define SYSTIMER_BASE_ADDR      CCORE_SYS_TIMER_BASE_ADDR
#define INT_LVL_SYSTIMER        CCORE_SYS_TIMER_INT_LVL

//#define CLK_DEFULT_TICKS_PERSECOND 100

#define AMBA_RELOAD_TICKS    0

#define CLK_REGOFF_LOAD	     0x000	/* Load (R/W) */
#define CLK_REGOFF_VALUE     0x004	/* Value (R/O) */
#define CLK_REGOFF_CTRL      0x008	/* Control (R/W) */
#define CLK_REGOFF_CLEAR     0x00C	/* Clear (W/O) */
#define CLK_REGOFF_INTSTATUS 0x010	/* INT STATUS (R/O) */


/* 定时器1 的锁定控制寄存器,当完成定时器的锁定操作后，该寄存器自动清零*/
#define CLK_DEF_TC_UNLOCK	0       /* 0：不锁定*/
#define CLK_DEF_TC_LOCK		(1<<3)  /* 1：将定时器的当前值锁定到TIMER1_CURRENTVALUE中*/


/*时钟中断使能*/
#ifndef TIMER_INT_ENABLE
#define TIMER_INT_ENABLE(level) intEnable (level)
#endif
/*时钟中断去使能*/
#ifndef TIMER_INT_DISABLE
#define TIMER_INT_DISABLE(level) intDisable (level)
#endif


#ifdef __cplusplus
}
#endif

#endif /*end #define _CLK_H_*/
