/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  softtimer_balong.c.c
*
*   作    者 :  lixiaojie l00227190
*
*   描    述 :  本文件主要完成softtimer驱动编写
*
*   修改记录 :  2013年2月20日  v1.00  l00227190  创建
*************************************************************************/
/*lint --e{438,537,732}*/
#include <osl_common.h>
#include <bsp_softtimer.h>
#include <soc_clk.h>
#include <bsp_memmap.h>
#include <bsp_om.h>
#include <bsp_hardtimer.h>
#include <libfdt.h>
#include <soc_timer.h>
#include "softtimer_balong.h"
#include "m3_dump.h"
#ifdef __cplusplus
extern "C" 
{
#endif
#define  softtimer_print(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_SOFTTIMER, "[softtimer]: <%s> "fmt"\n", __FUNCTION__, ##__VA_ARGS__))
/*lint --e{133 } */
osSemaphoreDef(soft_timer_sem);
static void thread_softtimer_fun(void const *obj);
osThreadDef(thread_softtimer_fun, osPriorityAboveNormal, 1, 1024);
irqreturn_t IntTimerHandler(void);

struct softtimer_ctrl
{
    struct list_head timer_list_head;
    u32 softtimer_start_value;                         /*记录每次物理timer计数起始值                     */
    u32 hard_timer_id_addr;                            /*软timer使用的物理timer地址                     */
    osThreadId thread_softtimer_id;                /*记录创建的任务                                 */
    osSemaphoreId      soft_timer_sem;    
    u32 clk;                                           /*所使用物理timer的时钟频率                       */
};

static struct softtimer_ctrl timer_control;       
#ifdef TIMER_ARM_FEATURE
static u32 __inline__ timer_get_value(void)
{
	u32 ret = 0;
	ret=readl(timer_control.hard_timer_id_addr + ARM_ODD_CTRL_OFFSET);
	if(ret&0x80)
	{
		ret=readl(timer_control.hard_timer_id_addr + ARM_ODD_VALUE_OFFSET);
		if(ret >timer_control.softtimer_start_value)
			return timer_control.softtimer_start_value;
		else
			return ret;
	}
	else
		return 0;
}
static void start_hard_timer(u32 ulvalue )
{
    u32 ret = 0;
    timer_control.softtimer_start_value = ulvalue;
    ret = readl(timer_control.hard_timer_id_addr+ARM_ODD_CTRL_OFFSET);
    writel(ret&(~0x80),timer_control.hard_timer_id_addr+ARM_ODD_CTRL_OFFSET);
    if(0==ulvalue)
	ulvalue=1;
    writel(ulvalue, timer_control.hard_timer_id_addr + ARM_ODD_LOAD_OFFSET);
    ret = readl(timer_control.hard_timer_id_addr+ARM_ODD_CTRL_OFFSET);
	/*one shot mode, 32bit cnt,unmask irq,start timer*/
    writel(ret |0xA3, timer_control.hard_timer_id_addr +ARM_ODD_CTRL_OFFSET);
}
static void stop_hard_timer()
{
    u32 ret = 0;
    ret = readl(timer_control.hard_timer_id_addr+ARM_ODD_CTRL_OFFSET);
    writel(ret&(~0x80),timer_control.hard_timer_id_addr+ARM_ODD_CTRL_OFFSET);
    timer_control.softtimer_start_value = ELAPESD_TIME_INVAILD;
}
#elif defined(TIMER_SYNOPSIS_FEATURE)
static u32 __inline__ timer_int_status(void)
{
	return readl(TIMER_INTSTATUS(timer_control.hard_timer_id_addr));
}
static u32 __inline__ timer_get_value(void)
{
	u32 ret = 0;
	ret = readl(timer_control.hard_timer_id_addr + HI_TIMER_CONTROLREG_OFFSET); 
	if(ret&0x1)
	{
		ret=readl(timer_control.hard_timer_id_addr + HI_TIMER_CURRENTVALUE_OFFSET);
		if(ret >timer_control.softtimer_start_value)
		{
			if(timer_int_status())
				return 0;
			else
				return timer_control.softtimer_start_value;
		}
		else
			return ret;
	}
	else
		return 0;
	
}

static void start_hard_timer(u32 ulvalue )
{
    u32 ret = 0;
    timer_control.softtimer_start_value = ulvalue;
    writel(0x0, timer_control.hard_timer_id_addr + HI_TIMER_CONTROLREG_OFFSET);
    while(readl(timer_control.hard_timer_id_addr +HI_TIMER_CURRENTVALUE_OFFSET)!=(u32)0xffffffff)
    {}
    writel(ulvalue, timer_control.hard_timer_id_addr + HI_TIMER_LOADCOUNT_OFFSET);
    writel(0x1, timer_control.hard_timer_id_addr + HI_TIMER_CONTROLREG_OFFSET);
    do{
		ret = readl(timer_control.hard_timer_id_addr + HI_TIMER_CONTROLREG_OFFSET);
	}while((ret&0x1)!=0x1);
    timer_control.softtimer_start_value = ulvalue;
}

static void stop_hard_timer()
{
    u32 ret = 0;
    writel(0x0, timer_control.hard_timer_id_addr + HI_TIMER_CONTROLREG_OFFSET);
    do{
		ret = readl(timer_control.hard_timer_id_addr + HI_TIMER_CONTROLREG_OFFSET);
	}while(ret&0x1);
    timer_control.softtimer_start_value = ELAPESD_TIME_INVAILD;
}
#else
#endif
static u32 hard_timer_elapsed_time()
{
    u32 ulTempValue = 0;
    if ( ELAPESD_TIME_INVAILD == timer_control.softtimer_start_value)
    {
        return 0;
    }
    ulTempValue = timer_get_value();
    return timer_control.softtimer_start_value - ulTempValue;
}

void bsp_softtimer_add(struct softtimer_list * timer)
{
    u32 elapsed_time = 0;
    struct softtimer_list *p = NULL;
    unsigned long flags = 0;
    if (NULL == timer)
    {
        softtimer_print("para  NULL\n");
        return;
    }
    local_irq_save(flags);
    /*如果已经在超时链表中，则不插入*/
    if(!list_empty(&timer->entry))
    {
    	 local_irq_restore(flags);
    	 return;
    }
    timer->timeout = timer->count_num;
    elapsed_time = hard_timer_elapsed_time();
    timer->timeout += elapsed_time;
    /*如果timer链表为空，则插入头结点*/
    if (list_empty(&(timer_control.timer_list_head)))
    {
        list_add_tail(&(timer->entry),&(timer_control.timer_list_head));
    }
    /*如果链表不为空，则按照超时时间从小到大插入*/
    else
    {
        list_for_each_entry(p,&(timer_control.timer_list_head),entry)
        {
            if(p->timeout <= timer->timeout)
	        {
	            timer->timeout -= p->timeout;
	        }
	        else
	        {
	            break;
	        }
	    }
	    if(&(p->entry)!=&(timer_control.timer_list_head))
	    {
	        p->timeout -= timer->timeout;
	    }
	    list_add_tail(&(timer->entry),&(p->entry));
    }
    if (timer_control.timer_list_head.next == &(timer->entry))
    {
        timer->timeout -= elapsed_time;
	 if ((timer->entry.next)!=(&(timer_control.timer_list_head)))
	 {
	     p = list_entry(timer->entry.next,struct softtimer_list,entry);
	     if(TIMER_TRUE==p->is_running)
	     {
	         p->is_running = TIMER_FALSE;
	     }
	 }
	 timer->is_running = TIMER_TRUE;
	 start_hard_timer(timer->timeout);
    }
    local_irq_restore(flags);
}
s32 bsp_softtimer_delete(struct softtimer_list * timer)
{
    struct softtimer_list * p=NULL;
    unsigned long flags;
    if (NULL == timer)
    {
        softtimer_print("NULL para \n");
        return ERROR;
    }
    local_irq_save(flags);
    if (list_empty(&timer->entry))
    {
        local_irq_restore(flags);
   	 return NOT_ACTIVE;
    }
    else
    {
        if(timer->entry.next == &(timer_control.timer_list_head))/*如果删除的是最后一个节点，直接删除*/
        {
            timer->is_running = TIMER_FALSE;
            list_del_init(&(timer->entry));
        }
	 /*如果删除的是链表中第一个结点,并且其后还有其他结点*/
        else if((timer->entry.prev == &(timer_control.timer_list_head))
			&&(timer->entry.next != &(timer_control.timer_list_head)))
        {
            timer->is_running = TIMER_FALSE;
            list_del_init(&(timer->entry));
			p=list_first_entry(&(timer_control.timer_list_head),struct softtimer_list,entry);/**/
			p->timeout += timer->timeout -hard_timer_elapsed_time();
			start_hard_timer(p->timeout);
			p->is_running = TIMER_TRUE;
        }
	 /*如果删除的是中间节点*/
        else
        {
            p = list_entry(timer->entry.next,struct softtimer_list,entry);
	        p->timeout += timer->timeout;
	        timer->is_running = TIMER_FALSE;
	        list_del_init(&(timer->entry));
        }
    }
    if (list_empty(&(timer_control.timer_list_head)))/*如果删除完事后链表为空，则停止计数*/
    {
        stop_hard_timer();
    }
    local_irq_restore(flags);
    return OK;
}

s32 bsp_softtimer_modify(struct softtimer_list *timer,u32 new_expire_time)
{
    if((NULL == timer)||(!list_empty(&timer->entry)) )
    {
        return ERROR;
    }
    if((new_expire_time) < (0xFFFFFFFF/timer_control.clk)) 
    {
        timer->timeout= (timer_control.clk* new_expire_time)/1000;
    }
    else /* 防止乘法溢出 */ 
    {
        timer->timeout= timer_control.clk * (new_expire_time/1000);
    }
    timer->count_num = timer->timeout;
    return OK;
}

s32 bsp_softtimer_create(struct softtimer_list *sft_info)
{
    INIT_LIST_HEAD(&(sft_info->entry));
    sft_info->is_running = TIMER_FALSE;
    sft_info->init_flags = TIMER_INIT_FLAG;
    	/*如果超出最大值，则返回失败,单位为ms*/
	if(sft_info->timeout>0xFFFFFFFF/timer_control.clk*1000)
	{
		softtimer_print("too long\n");
		return ERROR;
    }
    if((sft_info->timeout) < 0xFFFFFFFF/timer_control.clk)  /* 对小于SOFTTIMER_MAX_LENGTH的计时，可以保持精度 */
    {
	  sft_info->timeout= (timer_control.clk*(sft_info->timeout))/1000;
    }
    else /* 防止乘法溢出 */ 
    {
	 sft_info->timeout= timer_control.clk* ((sft_info->timeout)/1000);
    }	
    sft_info->count_num = sft_info->timeout;
     return OK;
}
s32 bsp_softtimer_free(struct softtimer_list *p)
{
    if ((NULL == p)||(!list_empty(&p->entry)))
	{
	    return ERROR;
    }
	p->init_flags = 0;
	 return OK;   
}
static void thread_softtimer_fun(void const *obj)
{
	struct softtimer_list     *p = NULL;
	unsigned long flags;
	softtimer_func func =NULL;
	u32 para = 0;
	/* coverity[no_escape] */
	/*lint --e{569 } */
	for( ; ; )
	{
	        /* coverity[sleep] */
		osSemaphoreWait(timer_control.soft_timer_sem, osWaitForever);
		 /* coverity[lock_acquire] */
		local_irq_save(flags);
		timer_control.softtimer_start_value = ELAPESD_TIME_INVAILD;
		if (!list_empty(&(timer_control.timer_list_head)))
		{
			p = list_first_entry(&(timer_control.timer_list_head),struct softtimer_list,entry);
			if(p->is_running == TIMER_TRUE)
			{
				list_del_init(&p->entry);
				p->is_running = TIMER_FALSE;
				func = p->func;
				para = p->para;
				local_irq_restore(flags); 
				func(para);			
				local_irq_save(flags);
				while(!list_empty(&(timer_control.timer_list_head)))
				{
					p=list_first_entry(&(timer_control.timer_list_head),struct softtimer_list,entry);
					if(0==p->timeout)
					{
						list_del_init(&p->entry);
						p->is_running = TIMER_FALSE;
						func = p->func;
						para = p->para;
						local_irq_restore(flags); 
						func(para);
						local_irq_save(flags);
					}
					else
						break;
				}
				if (!list_empty(&(timer_control.timer_list_head)))/*如果还有未超时定时器*/
				{
					p=list_first_entry(&(timer_control.timer_list_head),struct softtimer_list,entry);
					p->is_running = TIMER_TRUE;
					start_hard_timer(p->timeout);
				}
				else 
				{  
					stop_hard_timer();
				}	
			}
			else  if (p->is_running == TIMER_FALSE)
			{
				p->is_running = TIMER_TRUE;
				start_hard_timer(p->timeout);
			}
		}
		else
		{
			stop_hard_timer();
		}
		local_irq_restore(flags); 
	} 
}
#ifdef TIMER_ARM_FEATURE
irqreturn_t IntTimerHandler(void)
{
	 u32 readValue = 0;    
    /*1、读取硬件定时器的中断状态
	 2、如果有中断，则清中断，同时释放信号量
   */
    dump_int_enter(get_irq());
    readValue = readl(timer_control.hard_timer_id_addr+ARM_ODD_INTMIS_OFFSET);
    if (0 != readValue)
    {
        writel(0x1,timer_control.hard_timer_id_addr+ARM_ODD_INTCLR_OFFSET);
        osSemaphoreRelease(timer_control.soft_timer_sem);
    }

	dump_int_exit(get_irq());

	return IRQ_HANDLED;
}
#elif defined(TIMER_SYNOPSIS_FEATURE)
irqreturn_t IntTimerHandler(void)
{
	 u32 readValue = 0;    
    /*1、读取硬件定时器的中断状态
	 2、如果有中断，则清中断，同时释放信号量
   */
    dump_int_enter(get_irq());    
    readValue = readl(timer_control.hard_timer_id_addr+HI_TIMER_INTSTATUS_OFFSET);
    if (0 != readValue)
    {
        readValue = readl(timer_control.hard_timer_id_addr+HI_TIMER_EOI_OFFSET);
        osSemaphoreRelease(timer_control.soft_timer_sem);
    }

    dump_int_exit(get_irq());

    return IRQ_HANDLED;
}
#else
#endif
int  bsp_softtimer_init(void)
{
    struct device_node *ptr_device_node = NULL;
	const char *compatible_name = "hisilicon,softtimer_m3";
	char *ret_of_iomap = NULL;
	unsigned int irq_no_mcpu_softtimer = 0;

    /* 读取基地址并映射 */
	ptr_device_node = of_find_compatible_node(NULL, NULL, compatible_name);
	if (!ptr_device_node)  /* 找不到节点 */
	{
		softtimer_print("1 er\n");
		return ERROR;
	}
    ret_of_iomap = of_iomap(ptr_device_node, 0); 
	if (!ret_of_iomap)  /* 映射错误 */
	{
		return ERROR;
	}
	timer_control.hard_timer_id_addr=(u32)ret_of_iomap;
	//printk(" timer_control.hard_timer_id_addr =0x%x\n", timer_control.hard_timer_id_addr);
	 /* 获取中断号 */
	irq_no_mcpu_softtimer= irq_of_parse_and_map(ptr_device_node, 0);
	if(of_property_read_u32_array(ptr_device_node, "clock-frequency", &timer_control.clk, 1))
	{
		 softtimer_print("2 er\n");
		 return -1;
	}
    INIT_LIST_HEAD(&(timer_control.timer_list_head));
    timer_control.softtimer_start_value  = ELAPESD_TIME_INVAILD;
    
	timer_control.soft_timer_sem=osSemaphoreCreate(osSemaphore(soft_timer_sem),SEM_FULL);
	if(NULL == timer_control.soft_timer_sem)
	{
		softtimer_print("3 err\n");
		return ERROR;
	}
	/*lint --e{569 } */
	osSemaphoreWait(timer_control.soft_timer_sem, osWaitForever);
	 timer_control.thread_softtimer_id = osThreadCreate(osThread(thread_softtimer_fun), (void*)0);
	if (timer_control.thread_softtimer_id == NULL)
	{
		softtimer_print("4 err\n");
		return ERROR;
	}
	stop_hard_timer();
    	(void)request_irq(irq_no_mcpu_softtimer, (irq_handler_t)IntTimerHandler, 0, "softtimer irq", 0);
	enable_irq(irq_no_mcpu_softtimer);
	softtimer_print("ok\n");
	return 0;
}
#ifdef __cplusplus
}
#endif


