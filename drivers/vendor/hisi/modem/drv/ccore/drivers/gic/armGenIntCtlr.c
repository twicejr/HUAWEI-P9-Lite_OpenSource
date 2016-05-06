/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  armGenIntCtlr.c
*
*   作    者 :  xumushui
*
*   描    述 :  GIC模块
*
*   修改记录 :  2011年5月20日    xumushui  create
*
*************************************************************************/
#include <vxWorks.h>
#include <vsbConfig.h>
#include <intLib.h>
#include <arch/arm/intArmLib.h>
#include <arch/arm/excArmLib.h>
#include <iv.h>
#include <sysLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memLib.h>
#include "armGenIntCtlr.h"

#include <logLib.h>

#include "product_config.h"
#include "bsp_memmap.h"
#include <soc_interrupts.h>

#ifdef  _WRS_CONFIG_SV_INSTRUMENTATION
#include <private/eventP.h>
#endif
#ifdef _WRS_CONFIG_SMP
#include <cacheLib.h>
#endif
UINT32 g_vicIntCheck = 0;

IMPORT STATUS (*_func_isrConnect) (VOIDFUNCPTR *, VOIDFUNCPTR, int);
IMPORT STATUS (*_func_isrDisconnect) (VOIDFUNCPTR *, VOIDFUNCPTR, int);


UINT32 sysGicLevCfg[(INT_LVL_MAX - GIC_SPI_START)/4]=   /*only spi levels initialized here*/
{    /*spi interrupt levels*/
	0xf0f0f080   ,0xe0f01008   ,0x284848f0   ,0xf0f0f018,
	GIC_SPI_LEVEL,GIC_SPI_LEVEL,0x30f0f0f0   ,0x08d8f030,
	0xf0f030f0   ,0xf0f0f040   ,0xf010f0f0   ,0xf0f0f0f0,
	GIC_SPI_LEVEL,GIC_SPI_LEVEL,GIC_SPI_LEVEL,0x28281020,
	GIC_SPI_LEVEL,GIC_SPI_LEVEL,GIC_SPI_LEVEL,GIC_SPI_LEVEL,
	GIC_SPI_LEVEL,GIC_SPI_LEVEL,GIC_SPI_LEVEL,GIC_SPI_LEVEL,
	GIC_SPI_LEVEL,GIC_SPI_LEVEL,GIC_SPI_LEVEL,GIC_SPI_LEVEL,
	GIC_SPI_LEVEL,GIC_SPI_LEVEL,GIC_SPI_LEVEL,GIC_SPI_LEVEL
};

UINT32 sysGicCfg[(INT_LVL_MAX - GIC_SPI_START)/4] =
{
	GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,
	GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,
	GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,
	GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,
	GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,
	GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,
	GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,
	GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0,GIC_CFG_TO_CPU0
};


LOCAL UINT32 armGicLinesNum = 0;
LOCAL UINT32 armGicBase = 0;

FUNCPTR vicIntLvlChgHookPtr = (FUNCPTR) NULL; /*lint !e830*/
FUNCPTR vicIntBreakInPtr = (FUNCPTR) NULL; /*lint !e830*/
FUNCPTR vicIntBreakOutPtr = (FUNCPTR) NULL;/*lint !e830*/

extern STATUS intArchConnect (VOIDFUNCPTR * vector, VOIDFUNCPTR routine,
	                      int parameter);
extern STATUS intArchDisconnect (VOIDFUNCPTR * vector, VOIDFUNCPTR routine,
                                 int parameter);

void armGicCtlInit();
LOCAL STATUS armGicDevInit ();
LOCAL STATUS armGicLvlChg (int,int);
LOCAL STATUS armGicIntDevInit (int cpuNum);
LOCAL STATUS armGicLvlEnable(int VecId);
LOCAL STATUS armGicLvlDisable(int VecId);

STATUS armGicHwEnable(int VecId);
STATUS armGicHwDisable(int VecId);

LOCAL  STATUS armGicLvlVecChk
 (
    int * pLevel,
    int * pVector,
    int * pSrcCpuId
  );
LOCAL STATUS armGicLvlVecAck
    (
    int level,
    int vector,
    int srcCpuId
    );

STATUS armGicConnect
    (
    VOIDFUNCPTR * vector,	/* interrupt vector to attach to     */
    VOIDFUNCPTR   routine,	/* routine to be called              */
    int           parameter	/* parameter to be passed to routine */
    );
STATUS armGicDisconnect
    (
    VOIDFUNCPTR * vector,	/* interrupt vector to attach to     */
    VOIDFUNCPTR   routine,	/* routine to be called              */
    int           parameter	/* parameter to be passed to routine */
    );


/*initialize gic device,install function pointers*/
void armGicCtlInit()
    {

     armGicLinesNum = INT_LVL_MAX;
     armGicBase = HI_MDM_GIC_BASE_ADDR;

    /*install poniters for intEnable\intDisable\intConnect\.etc*/
    sysIntLvlVecChkRtn = (FUNCPTR)armGicLvlVecChk;	/* return vector and level */
    sysIntLvlVecAckRtn = (FUNCPTR)armGicLvlVecAck;	/* ack vector and level */
    sysIntLvlEnableRtn  = (FUNCPTR)armGicHwEnable;
    sysIntLvlDisableRtn = (FUNCPTR)armGicHwDisable;
    sysIntLvlChgRtn     = (FUNCPTR)armGicHwLvlChg;

    if (_func_isrConnect == NULL)
        _func_isrConnect = (FUNCPTR)armGicConnect;
    if  (_func_isrDisconnect == NULL)
        _func_isrDisconnect = (FUNCPTR)armGicDisconnect;

    /* initialize the GIC */
    armGicDevInit ();

    }
/*******************************************************************************
*
* armGicDevInit - initialize the interrupt controller
*
* This routine initializes the interrupt controller device, disabling all
* interrupt sources. It connects the device driver specific routines
* into the architecture level hooks. If the BSP needs to create a wrapper
* routine around any of the architecture level routines, it should install the
* pointer to the wrapper routine after calling this routine.
*
* RETURNS: OK or ERROR if parameter is invalid.
*
* ERRNO: N/A
*/

LOCAL STATUS armGicDevInit()
    {

    int coreId;
    /* 获取CoreID*/
    coreId = 0;//((*(int *)0x80000ac) & 0xf);

    /*intialise this CPU interfacea and GIC registers*/
    armGicIntDevInit(coreId);
    return OK;
    }

/*******************************************************************************
*
* armGicIntDevInit - initialize the interrupt controller
* Note that for multicore processor, some registers are banked for each process.
* This routine uses CPU0 to initialize the common resources and banked
* registers are processed by every processor.
*
* RETURNS: always OK
*
* ERRNO: N/A
*/
LOCAL STATUS armGicIntDevInit
    (
    int cpuNum
    )
    {
    UINT32 i;
    /* clear all pending PPI and SGI interrupts in the distributor */

    *GIC_IntPendClr(0) = ALL_PPI_INT_MASK | ALL_SGI_INT_MASK;

    /*
    interrupt register is read only
    if read *GIC_Type is 0xfc23,means it have two cpu interfaces and 128 interrupts
    are supported maximumly,Security Extensions is implemented
    */

    /* set default priority for all SGI interrupt to level 0(highest) */

    for (i = 0; i < SGI_INT_MAX; i += PRIOS_PER_WORD)
        *GIC_Prio(i) = GIC_IPI_LEVEL;     /* SGI level(24) */

    for (i = 0; i < SGI_INT_MAX; i += CONFIGS_PER_WORD)
        *GIC_Config(i) = GIC_INT_CONFIG_SOFT; /* N-N, Edge triggered */

    for (i = SGI_INT_MAX; i < GIC_SPI_START; i += PRIOS_PER_WORD)
        *GIC_Prio(i) = GIC_DEFAULT_LEVEL; /* PPI level - lowest */


        /* disable distributor */
        *GIC_Control = 0;

        /* disable all SPI interrupts */

        for(i = GIC_SPI_START; i < armGicLinesNum; i += BITS_PER_WORD)
            *GIC_IntEnClr(i) = 0xffffffff;

        /* Clear all pending SPI interrupts in the distributor */

        for (i = GIC_SPI_START; i < armGicLinesNum; i += BITS_PER_WORD)
            *GIC_IntPendClr(i) = 0xffffffff;

        /*
         * set default priority for all interrupts
         * interrupts to go to CPU 0
         */
        for (i = GIC_SPI_START; i < armGicLinesNum; i += PRIOS_PER_WORD)
            {
                *GIC_Prio(i)    = sysGicLevCfg[(i - GIC_SPI_START)/4];
                *GIC_CPUTarg(i) = sysGicCfg[(i - GIC_SPI_START)/4];
            }

        /*set interrupt config register*/
        for (i = GIC_SPI_START; i < armGicLinesNum; i += CONFIGS_PER_WORD)
            *GIC_Config(i) = GIC_INT_CONFIG_SPI; /* 1-N, Level High */



    /* enable all interrupt priorities */

    *GIC_CPU_PriMask = GIC_INT_ALL_ENABLED;

    /* enable preemption of all interrupts */

    *GIC_CPU_BinPoint = GIC_CPU_BINP_DEFAULT;

    /* enable this processor's CPU interface */

    *GIC_CPU_Control = GIC_CONTROL_ENABLE;


        /* enable distributor */
        *GIC_Control = GIC_CONTROL_ENABLE;

    return OK;
    }
/*******************************************************************************
*This routine is used to check interrupt id and interrupt cpuid
*
*/
LOCAL STATUS  armGicLvlVecChk
    (
    int * pLevel,
    int * pVector,
    int * pSrcCpuId
    )
    {
    UINT32 currentLevel, levelBak;

    g_vicIntCheck = 1;
    if (NULL != vicIntBreakInPtr)
    {
        (void)vicIntBreakInPtr(); /*lint !e534 !e718*/
    }
    /* read pending interrupt register and mask undefined bits */
    levelBak = *GIC_CPU_IntAck;
    currentLevel = levelBak & GIC_INT_SPURIOUS;
    /*  If no interrupt is pending, register will have a value of 0x3ff,
     * return ERROR   */
    if (currentLevel == GIC_INT_SPURIOUS)
        {
        return ERROR;
        }
    /* check if interrupt is IPI */
    if(currentLevel < SGI_INT_MAX)
        {
        /*
         * When we find that this is a SGI interrupt, we add armGicLinesNum to
         * the current SGI level (0 - SGI_INT_MAX), in other words, the SGI
         * level is redefined by software to declare that this is a specific
         * interrupt, then we need save the source CPU ID to ack this interrupt.
         */
        *pSrcCpuId = levelBak & GIC_SGI_SRC_CPU_ID_MASK;
        *pLevel = (int)(currentLevel + armGicLinesNum);
        *pVector = IVEC_TO_INUM(currentLevel + armGicLinesNum);
        }
    else
        {
        *pLevel =(int)currentLevel;
        *pVector = IVEC_TO_INUM(currentLevel);
        }
    if(vicIntLvlChgHookPtr != NULL)
    {
        (void)vicIntLvlChgHookPtr(0, *pLevel); /*lint !e534 !e119*/
    }
    return OK;
    }

/*******************************************************************************
*
* armGicLvlVecAck - acknowledge the current interrupt
*
* This routine acknowledges the current interrupt cycle. The level and vector
* values are those generated during the armGicLvlVecChk() routine for this
* interrupt cycle.
*
* RETURNS: OK or ERROR if level is invalid.
*
* ERRNO
*/
LOCAL STATUS armGicLvlVecAck
    (
    int level,    /* old interrupt level to be restored */
    int vector,  /* current interrupt vector, if needed */
    int srcCpuId
    )
    {
    UINT32 maxIntLines;
    g_vicIntCheck=0;

#ifdef _WRS_CONFIG_SMP
        maxIntLines = armGicLinesNum + ARM_GIC_IPI_COUNT;
#else


    maxIntLines = armGicLinesNum;



#endif /* _WRS_CONFIG_SMP */
    /*
     * Validity check for level. Note that for PPI, we always return
     * ERROR, as PPI is not used.
     */
    if (level < 0 || level >= (int)maxIntLines || (level >= SGI_INT_MAX && level < GIC_SPI_START)) /* PPI check ,16-31*/
        return ERROR;
    /*
     * Ack the interrupt. It's implemented on the CPU interface to the
     * interrupt distributor.
     */
    if (level >= (int)armGicLinesNum)
    {
     /*
         * SGI is used to implement the IPI. The source CPU ID must be carried
         * to acknowledge the SGI interrupts.
         */
        level -= (int)armGicLinesNum;
        level |= srcCpuId;
        }

    *GIC_CPU_EOInt =(UINT32) level;

    if (NULL != vicIntBreakOutPtr)
    {
        (void)vicIntBreakOutPtr(); /*lint !e534*/
    }

    if(vicIntLvlChgHookPtr != NULL)
    {
        (void)vicIntLvlChgHookPtr(1, level); /*lint !e534 !e119*/
    }

    return OK;
    }
/*******************************************************************************
* armGicLvlChg - change the interrupt level value
*
* This routine sets the interrupt priority.Levels are 0(highest) - 0x1f(lowest).
* These are 32 levels; Every interrupt level is in step of 8;
*
* RETURNS: OK or ERROR
* ERRNO: N/A
*/

LOCAL STATUS armGicLvlChg
    (
    int vector,
    int level    /* new interrupt level */
    )
    {
     int Lvlmask;
     int OldLevel;
     int key;

      /*
     * Validity check for level. Note that for PPI, we always return
     * ERROR, as PPI is not used.
     */
        if ((vector >= SGI_INT_MAX && vector < GIC_SPI_START) || (vector >= (int)armGicLinesNum ))
            return ERROR;
        else
        {
            /*32 levels are supported maximumly*/
            if(level >= GIC_LEVEL_MAX - 1)
                return ERROR;
            else
            {
                key = intCpuLock();
                OldLevel = *GIC_Prio(vector);
                Lvlmask  =~ (BYTE_MASK << REG_BYTE(vector));
                OldLevel &= Lvlmask;                        /* only change one btye corresponding to vector*/
		        /*level from 0-248,in step of 8,total 32 levels*/
                level = (level << 3) << REG_BYTE(vector);
                *GIC_Prio(vector) = (OldLevel | level);
                intCpuUnlock(key);
            }
        }
        return OK;
    }

/*******************************************************************************
*
* armGicLvlEnable - enable a single interrupt level
*
* This routine enables a specific interrupt level at the interrupt distributor.
* The enabled level will be allowed to generate an interrupt to the configured
* CPU(s). Without being enabled, the interrupt is blocked.
*
* RETURNS: OK or ERROR if level is invalid.
* ERRNO: N/A
*/

LOCAL STATUS  armGicLvlEnable
    (
        int VecId  /* level to be enabled */
    )
    {
    int key;

    if ((VecId >= 0) && (VecId < SGI_INT_MAX))
        return OK;        /*SGI interrupt is enabled*/

    //ppi doesn't need to enable  ?


    if (VecId < GIC_SPI_START || VecId >= (int)armGicLinesNum )
        return ERROR;

    key = intCpuLock ();              /* LOCK INTERRUPTS */

    *GIC_IntEnable(VecId) = BIT(VecId); /* enable interrupt */

    intCpuUnlock (key);               /* UNLOCK INTERRUPTS */

    return OK;
    }

/*******************************************************************************
*
* armGicLvlDisable - disable a single interrupt level
*
* This routine disables a specific interrupt level at the interrupt distributor.
* The disabled level is prevented from generating an interrupts.
*
* RETURNS: OK or ERROR if level is invalid.
*
* ERRNO: N/A
*/

LOCAL STATUS armGicLvlDisable
    (
        int VecId  /* level to be disabled */
    )
    {
    int key;
    if ((VecId >= 0) && (VecId < SGI_INT_MAX))
        return OK;        /*SGI interrupt can not be enabled*/

    if (VecId < GIC_SPI_START || VecId >= (int)armGicLinesNum)
        return ERROR;

    key = intCpuLock ();

    *GIC_IntEnClr(VecId) = BIT(VecId);

    intCpuUnlock (key);

    return OK;
    }

/*******************************************************************************
*
* armGicHwEnable - enable hardware interrupt
*
* This routine enables the interrupt
*
* RETURNS: OK if operation successful else ERROR
*
* ERRNO: N/A
*/
STATUS armGicHwEnable
    (
        int VecId
    )
    {

         return armGicLvlEnable(VecId);
    }

/******************************************************************************
*
* armGicHwDisable - disable device interrupt
*
* This routine disables the interrupt
*
* RETURNS: OK if operation successful else ERROR
*
* ERRNO: N/A
*/

STATUS armGicHwDisable
    (
        int VecId
    )
    {

        return armGicLvlDisable(VecId);
    }

/******************************************************************************
*
* armGicHwLvlChg - change the interrupt level value
*
* This routine sets the current interrupt level to the specified level.
*
* RETURNS: Previous interrupt level.
*
* ERRNO: N/A
*/

STATUS armGicHwLvlChg
    (
    int vector,
    int level
    )
    {
    return armGicLvlChg(vector,level);
    }

/*******************************************************************************
* armGicConnect - interrupt connect handler
*
* This function implements the connection of interrupt handler. It's used to
* support intConnect(...).
*
* RETURNS: OK if operation successful else ERROR
*
* ERRNO: N/A
*/
STATUS armGicConnect
    (
    VOIDFUNCPTR * vector,	/* interrupt vector to attach to     */
    VOIDFUNCPTR   routine,	/* routine to be called              */
    int           parameter	/* parameter to be passed to routine */
    )
    {
    return (intArchConnect(vector, (VOIDFUNCPTR) routine,
                            (int) parameter));
    }

/*******************************************************************************
* armGicDisconnect - interrupt connect handler
*
* This function implements the disconnection of interrupt handler. It's used to
* support intDisconnect(...).
*
* RETURNS: OK if operation successful else ERROR
*
* ERRNO: N/A
*/
STATUS armGicDisconnect
    (
    VOIDFUNCPTR * vector,	/* interrupt vector to attach to     */
    VOIDFUNCPTR   routine,	/* routine to be called              */
    int           parameter	/* parameter to be passed to routine */
    )
    {
    return (intArchDisconnect(vector, (VOIDFUNCPTR) routine,
                            (int) parameter));
    }

/*******************************************************************************
*
* armGicIntReroute - reroute interrupt to specified CPU
*
* This routine reroutes device interrupt to requested CPU. Note that the cpu is
* specified in a cpuset_t type, and this would allow for multiple cpus to be
* bundled with the interrupt. Multicore processor can ensure that only one CPU
* will be triggered if the interrupt occurs.
*
* RETURNS: OK if operation successful else ERROR
*
* ERRNO: N/A
*/
STATUS armGicIntReroute
    (
    UINT32                 vectorId,
    cpuset_t            destCpu
    )
    {
    UINT32 OlddestCpu;
    UINT32 TgCpuMask;
    int key;
    if((vectorId < GIC_SPI_START) || (vectorId > armGicLinesNum))
        return ERROR;
    else
        {
        if(destCpu >= GIC_CPU_NUM )
            return ERROR;
        else
        {
            key = intCpuLock();
            OlddestCpu = *GIC_CPUTarg(vectorId);
            TgCpuMask  =~ (BYTE_MASK << REG_BYTE(vectorId)); /*get byte mask*/
            OlddestCpu &= TgCpuMask;                     /* only change one btye corresponding to vector*/
            destCpu = destCpu << REG_BYTE(vectorId);
            *GIC_CPUTarg(vectorId) = OlddestCpu | destCpu;
            intCpuUnlock(key);
        }
        }
     return OK;
    }
	/*******************************************************************************
	*
	* armGicTriSet - set the interrupt trigger
	*
	* RETURNS: OK or ERROR if parameter is invalid.
	*
	* ERRNO: N/A
	*/
	 int armGicSetType(UINT32 irq, enum tri_mode type)
	 {
	        UINT32 enablemask = 1 << (irq % 32);
		/*UINT32 enableoff = (irq / 32) * 4;*/
		UINT32 confmask = 0x2 << ((irq % 16) * 2);
		/*UINT32 confoff = (irq / 16) * 4;*/
		UINT32 enabled = 0;
		UINT32 oldLev,key;

		/* Interrupt configuration for SGIs can't be changed */
		if (irq < 16)
			return ERROR;

		if (type != LEVEL && type !=EDGE)
			return ERROR;

		//raw_spin_lock(&irq_controller_lock);
             key = intCpuLock ();
	       oldLev =  *GIC_Config(irq) ;
		//val = readl_relaxed(base + GIC_DIST_CONFIG + confoff);
		if (type == LEVEL)
			oldLev &= ~confmask;
		else if (type == EDGE)
			oldLev |= confmask;

		/*
		 * As recommended by the spec, disable the interrupt before changing
		 * the configuration
		 */
		if (*GIC_IntEnable(irq) & enablemask) {
                      *GIC_IntEnClr(irq) = enablemask;
			enabled = 1;
		}

		   *GIC_Config(irq) = oldLev;

		if (enabled)
                  *GIC_IntEnable(irq) = enablemask;
	      intCpuUnlock(key);
		return 0;
	}

/*****************************************************************************
* 函 数 名  : vicIntBreakInHook
*
* 功能描述  : 挂接入中断钩子函数

* 输入参数  : FUNCPTR p_Func

* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  : 2009年7月9日   zhanghailun  creat

*****************************************************************************/

void vicIntBreakInHook(FUNCPTR p_Func)
{
    vicIntBreakInPtr = p_Func;
}
/*****************************************************************************
* 函 数 名  : vicIntBreakOutHook
*
* 功能描述  : 挂接出中断钩子函数

* 输入参数  : FUNCPTR p_Func

* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  : 2009年7月9日   zhanghailun  creat

*****************************************************************************/
void vicIntBreakOutHook(FUNCPTR p_Func)
{
    vicIntBreakOutPtr = p_Func;
}
/*****************************************************************************
* 函 数 名  : vicIntBreakInHookDel
*
* 功能描述  : 取消入中断钩子函数

* 输入参数  : FUNCPTR p_Func

* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  : 2009年7月9日   zhanghailun  creat

*****************************************************************************/

void vicIntBreakInHookDel(void)
{
    vicIntBreakInPtr = (FUNCPTR) NULL;
}
/*****************************************************************************
* 函 数 名  : vicIntBreakOutHookDel
*
* 功能描述  : 取消出中断钩子函数

* 输入参数  : FUNCPTR p_Func

* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  : 2009年7月9日   zhanghailun  creat

*****************************************************************************/

void vicIntBreakOutHookDel(void)
{
    vicIntBreakOutPtr = (FUNCPTR) NULL;
}

/****************************************************************************
*
*modify by wangjing 2011-3-31
*修改原因:可维可测移植，注册中断记录回调函数
*
*****************************************************************************/

void vicIntLvlChgHookAdd(FUNCPTR p_Func)
{
    vicIntLvlChgHookPtr = p_Func;
}

void vicIntLvlChgHookDel(void)
{
    vicIntLvlChgHookPtr = (FUNCPTR) NULL;
}





