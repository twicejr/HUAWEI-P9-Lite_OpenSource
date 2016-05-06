
#include <sre_hwi.h>
#include <sre_tick.h>
#include <sysTimer.h>
#include <osl_bio.h>
#include <bsp_hardtimer.h>
#include <of.h>
/*lint -e{539}*/
unsigned int systimer_base_addr = 0;
int sysClkTicksPerSecond	= 100;
unsigned int hrttimer_curtime_addr = 0;
unsigned int hrttimer_offset[2]={0};
unsigned int hrttimer_increase_count_flag = 0;
unsigned int systimer_init_flag = 0;
extern void cpufreq_checkload_in_sysint(void);
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
int sysClkRateGet(void)
{
    return sysClkTicksPerSecond;
}

UINT64 rtosckSysClkValueGet(void)
{
	UINT64 ret = 0;
	if(systimer_init_flag)
	{
		ret = (UINT64)readl(hrttimer_curtime_addr+hrttimer_offset[1]);
		ret =( ret << 32 )+ (UINT64)readl(hrttimer_curtime_addr+hrttimer_offset[0]);
		if(!hrttimer_increase_count_flag)
			return 0xFFFFFFFFFFFFFFFF - ret;
		else 
			return ret;
	}
	else
		return 0;
}
void systimer_hander_isr(void)
{
    
    /* 读取寄存器输出值*/
    unsigned int readValue;

    /*SYS CLK*/
    readValue=readl(systimer_base_addr+CLK_REGOFF_INTSTATUS);

    if(readValue != 0)
    {

        /*清中断*/ 
		systimer_int_clear(systimer_base_addr);
        SRE_TickISR();
    }
    cpufreq_checkload_in_sysint();
}
void rtosckClkStart(void)
{        
    unsigned int tc, irq=0;
#ifdef CONFIG_OF
	unsigned int temp=0;
    struct device_node *timer_node = NULL;
    const char *timer_name = "hisilicon,systimer_mdm";
    timer_node = of_find_compatible_node(NULL, NULL, timer_name);
    if(!timer_node)
    {
        (void)SRE_Printf("systimer of_find_compatible_node failed.\r\n");
        return;
    }
    if(of_property_read_u32_array(timer_node, "reg", &temp, 1)){
		(void)SRE_Printf("systimer of_property_read_u32_array failed \n");
		return ;
	}
	systimer_base_addr=temp;/*lint !e539*/
	irq = irq_of_parse_and_map(timer_node, 0);
	if(of_property_read_u32(timer_node, "clock-frequency", &tc)){
		(void)SRE_Printf("clock-frequency of_property_read_u32_array failed\n");
		return ;
	}
	tc=tc/100;
	 timer_node = of_find_compatible_node(NULL, NULL, "hisilicon,hrttimer_slice_mdm");
    if(!timer_node)
    {
        (void)SRE_Printf("systimer of_find_compatible_node failed .\n");
        return;
    }
    if(of_property_read_u32_array(timer_node, "reg", &hrttimer_curtime_addr, 1)){
		(void)SRE_Printf("hrttimer_curtime_addr of_property_read_u32_array failed 1\n");
		return ;
	}
	if(of_property_read_u32(timer_node, "increase_count_flag", &hrttimer_increase_count_flag)){/*lint !e539*/
		(void)SRE_Printf("hrttimer_curtime_addr increase_count_flag failed \n");
		return ;
	}
	if(of_property_read_u32_array(timer_node, "offset", hrttimer_offset, 2)){
		(void)SRE_Printf("hrttimer_curtime_addr of_property_read_u32_array failed 3\n");
		return ;
	}
#else
	systimer_base_addr = SYSTIMER_BASE_ADDR;
	irq = INT_LVL_SYSTIMER; 
    tc = (UINT32)((SYS_TIMER_CLK / 100) - AMBA_RELOAD_TICKS);
#endif
    /*挂接*/
    (void)SRE_HwiSetAttr(irq, SRE_HWI_PRIORITY0, OS_HWI_MODE_ENGROSS);
    (void)SRE_HwiCreate(irq,(HWI_PROC_FUNC)systimer_hander_isr,0);

    writel(CLK_DEF_DISABLE,systimer_base_addr+CLK_REGOFF_CTRL);
    
    /* Calculate the timer value*/
    
    /* Load Timer Reload value into Timer registers */
    writel(tc,systimer_base_addr+CLK_REGOFF_LOAD);
    systimer_int_clear(systimer_base_addr);
    
    writel(CLK_DEF_ENABLE,systimer_base_addr+CLK_REGOFF_CTRL);
	(void)systimer_check_enable_success();
    
    /* enable clock interrupt in interrupt controller */
    (void)SRE_HwiEnable (irq);
	systimer_init_flag=1;
    return;
}

