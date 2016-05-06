/*************************************************************************
*   版权所有(C) 1987-2009, 深圳华为技术有限公司.
*
*   文 件 名 :  BSP_CLK.c
*
*   作    者 :  liumengcun
*
*   描    述 :  本文件命名为"CLK_UsrTimer.c", 实现用户时钟初始化,挂接,开启,关闭等功能
*
*   修改记录 :  2009年3月5日  v1.00  liumengcun  创建
*               2009年5月19日 v1.00  liumengcun  修改
*   BJ9D00787:【ST BSP CLOCK】用户单次TIMER启动后依次去使能、使能TIMER，启动周期TIMER
*              的处理不符合预期，并且处理的驱动代码中发生了除零运算
*   BJ9D00699: 用户时钟BSP_USRCLK_TimerMilliSecStart()设置定时器超时的毫秒值小于系统
*              最小值没有返回错误
*   BJ9D00652: 设置单次TIMER为允许的最小值，发现偶尔会有系统挂死的现象
*				2009年5月19日 v1.00  liumengcun  修改
*	BJ9D00953:启动一个周期timer，然后调用BSP_USRCLK_TimerStop（该接口只为one shot
*             timer提供），发现周期timer被停掉了
*************************************************************************/
#include "copyright_wrs.h"
#include "vxWorks.h"
#include "logLib.h"
#include "tickLib.h"
#include "stdlib.h"
#include "string.h"
#include "iv.h"
#include "intLib.h"
#include "prjParams.h"

#include "mdrv.h"
#include "sysTimer.h"


//BSP_U32  g_u32TickCnt;

/* locals */
/*系统时钟*/
LOCAL SYSCLKFUNCPTR sysClkRoutine	= NULL; /* routine to call on clock interrupt */
LOCAL int sysClkArg		= 0;    /* its argument */
LOCAL int sysClkRunning		= FALSE;
LOCAL int sysClkConnected	= FALSE;
LOCAL int sysClkTicksPerSecond	= 100;
UINT32 g_u32sysClkTickCounter = 0;
UINT32 g_sysIntFirstTime = 0;
//int g_sysIntFirstTime = 0;


//int g_sysStampIntFirstTime = 0;
//int g_softTimeIntFirstTime = 0;


extern void sysHwInit2 (void);

//LOCAL BOOL	BspClkRunning = FALSE;   /* bsp clk running flag */
//LOCAL int BspClkTicksPerSecond = 100;
//int g_UsrIntFirstTime = 0;
extern void cpufreq_checkload_in_sysint(void);
/*****************************************************************************
* 函 数 名  : sysClkInt
*
* 功能描述  : This routine handles the system clock interrupt.  It is attached
*             to the clock interrupt vector by the routine sysClkConnect().
*
* 输入参数  : 无
* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  : 2009年1月20日   liumengcun  creat

*****************************************************************************/
void sysClkInt (void)
{
    /* 读取寄存器输出值*/
    UINT readValue;

    /*SYS CLK*/
    BSP_REG_READ(SYSTIMER_BASE_ADDR, CLK_REGOFF_INTSTATUS, readValue);

    if(readValue != 0)
    {
    	/* 系统时钟tick计数*/
    	g_u32sysClkTickCounter++;

        /*清中断:此处V7R2和 p532有差异，在platform下处理*/
	systimer_int_clear(SYSTIMER_BASE_ADDR);

        /* If any routine attached via sysClkConnect(), call it */
        if (sysClkRoutine != NULL)
        {
            (* sysClkRoutine) (sysClkArg);
        }
    }
    cpufreq_checkload_in_sysint();
}

/*****************************************************************************
* 函 数 名  : sysClkConnect
*
* 功能描述  : This routine specifies the interrupt service routine to be called
*             at each clock interrupt.  It does not enable system clock interrupts.
*             Normally it is called from usrRoot() in usrConfig.c to connect
*             usrClock() to the system clock interrupt.
*
* 输入参数  : FUNCPTR routine   routine to be called at each clock interrupt
              int arg	        argument with which to call routine
* 输出参数  : 无
* 返 回 值  : OK, or ERROR if the routine cannot be connected to the interrupt.
*
* 修改记录  : 2009年1月20日   liumengcun  creat

*****************************************************************************/
STATUS sysClkConnect
    (
    SYSCLKFUNCPTR routine,	  /* routine to be called at each clock interrupt */
    int arg		          /* argument with which to call routine */
    )
    {
    if (sysClkConnected == FALSE)
    {
    	sysHwInit2 ();	  /* XXX for now -- needs to be in usrConfig.c */
    	sysClkConnected = TRUE;
    }

    sysClkRoutine = NULL; /* ensure routine not called with wrong arg */

    sysClkArg	  = arg;
    sysClkRoutine = routine;

    return OK;
    }

/*****************************************************************************
* 函 数 名  : sysClkDisable
*
* 功能描述  : This routine disables system clock interrupts.
*
* 输入参数  : 无
* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  : 2009年1月20日   liumengcun  creat

*****************************************************************************/
void sysClkDisable (void)
{
    if (sysClkRunning)
	{
	    /* 关闭中断使能寄存器*/
        BSP_REG_WRITE(SYSTIMER_BASE_ADDR,CLK_REGOFF_CTRL, CLK_DEF_DISABLE);

    	/* 系统时钟tick计数清零*/
    	g_u32sysClkTickCounter = 0;
    	sysClkRunning = FALSE;
	}
}
/*****************************************************************************
* 函 数 名  : sysClkEnable
*
* 功能描述  : This routine enables system clock interrupts.
*
* 输入参数  : 无
* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  : 2009年1月20日   liumengcun  creat

*****************************************************************************/
void sysClkEnable (void)
{
    UINT32 tc;
    unsigned int u32Times = 100;
    unsigned int i = 0;

    if (!sysClkRunning)
	{
    	/* 系统tick计数清零*/
    	g_u32sysClkTickCounter = 0;

        BSP_REG_WRITE(SYSTIMER_BASE_ADDR,CLK_REGOFF_CTRL, CLK_DEF_DISABLE);

    	/* Calculate the timer value*/
    	tc = (UINT32)((SYS_TIMER_CLK / sysClkTicksPerSecond) - AMBA_RELOAD_TICKS);

    	/* Load Timer Reload value into Timer registers */
        BSP_REG_WRITE (SYSTIMER_BASE_ADDR,CLK_REGOFF_LOAD, tc);

        /* 查询计数器使能是否生效 */
	i = systimer_check_enable_success();
        if(i == u32Times)
        {
            logMsg("write LoadValue error\n",1,2,3,4,5,6);
            return;
        }

        BSP_REG_WRITE(SYSTIMER_BASE_ADDR,CLK_REGOFF_CTRL, CLK_DEF_ENABLE);

        /*第一次启动时需要使能中断*/
    	if(0 == g_sysIntFirstTime)
        {
        	/* enable clock interrupt in interrupt controller */
        	TIMER_INT_ENABLE (INT_LVL_SYSTIMER);
        	g_sysIntFirstTime = 1;
        }

    	sysClkRunning = TRUE;
	}
}
/*****************************************************************************
* 函 数 名  : sysClkRateGet
*
* 功能描述  : This routine returns the interrupt rate of the system clock.
*
* 输入参数  : 无
* 输出参数  : 无
* 返 回 值  : The number of ticks per second of the system clock.
*
* 修改记录  : 2009年1月20日   liumengcun  creat

*****************************************************************************/
int sysClkRateGet (void)
{
    return sysClkTicksPerSecond;
}

/*****************************************************************************
* 函 数 名  : sysClkRateSet
*
* 功能描述  : This routine sets the interrupt rate of the system clock.  It does
*             not enable system clock interrupts unilaterally, but if the system
*             clock is currently enabled, the clock is disabled and then
*             re-enabled with the new rate.  Normally it is called by usrRoot()
*             in usrConfig.c.
*
* 输入参数  : int ticksPerSecond   number of clock interrupts per second
* 输出参数  : 无
* 返 回 值  : OK, or ERROR if the tick rate is invalid or the timer cannot be set.
*
* 修改记录  : 2009年1月20日   liumengcun  creat

*****************************************************************************/
STATUS sysClkRateSet
    (
    int ticksPerSecond	    /* number of clock interrupts per second */
    )
    {
    if (ticksPerSecond < SYS_CLK_RATE_MIN || ticksPerSecond > SYS_CLK_RATE_MAX)
    {
        logMsg("sysClkRateSet err, ticksPerSecond: %d \n",ticksPerSecond,0,0,0,0,0);
	    return ERROR;
    }

    sysClkTicksPerSecond = ticksPerSecond;

    if (sysClkRunning)
	{
    	sysClkDisable ();
    	sysClkEnable ();
	}

    return OK;
    }

/*****************************************************************************
* 函 数 名  : sysClkTicksGet
*
* 功能描述  : 获得系统时钟启动以来的tick数.
*
* 输入参数  : 无
* 输出参数  : 无
* 返 回 值  : 系统时钟启动以来的tick数.
*
* 修改记录  : 2009年2月24日   liumengcun  creat

*****************************************************************************/
UINT32 sysClkTicksGet (void)
{
    return g_u32sysClkTickCounter;
}

