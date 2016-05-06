/*C core test code*/
#include"bsp_wdt.h"
#include <osl_spinlock.h>
#include <osl_thread.h>

void bsp_wdt_test(void);
int  hi6930_wdt_case01(void);
s32 hi6930_wdt_case02(void);
s32 hi6930_wdt_case03(void);
s32 hi6930_wdt_case04(void);
void bsp_wdt_print_debug(void);

/*初始化WDT，使能WDT，去使能WDT*/
int  hi6930_wdt_case01(void)
{
	u32 timeout = 0,i=0;
	/* 使能复位和中断 */
    bsp_wdt_start();
	/*设置超时时间*/
	bsp_wdt_set_timeout(30);	
	/* 获取看门狗剩余超时时间 */
	while(i<10000)
	{
		i++;
	}
	bsp_wdt_get_timeleft(&timeout);
   /*stop watchdog*/
   if (0 == bsp_wdt_stop())
   	{
   	}
   else
   	{
		return WDT_ERROR;
   	}
	return WDT_OK;
}

/*使能WDT，产生中断(A核)，复位*/
s32 hi6930_wdt_case02(void)
{
	/* 并使能复位和中断 */
	bsp_wdt_start(); 
	/*设置超时间隔*/
	bsp_wdt_set_timeout(1);
	return WDT_OK;
}

/*测试回调函数*/
s32 hi6930_wdt_case03(void)
{
   	wdt_timeout_cb wdt_hook = (void*)1;
   	bsp_wdt_register_hook(wdt_hook);
   	bsp_wdt_unregister_hook();
   	return WDT_OK;
}

/*低功耗接口*/
s32 hi6930_wdt_case04(void)
{
	bsp_wdt_start();
	/*设置计数时间35s*/
	bsp_wdt_suspend(35);
	/*计数时间恢复为30s*/
	bsp_wdt_resume();
	bsp_wdt_stop();
	return WDT_OK;
}



void bsp_wdt_test(void)
{
	 spinlock_t lock;
    wdt_err("enter wdt test\n");
    spin_lock_init(&lock);
    spin_lock(&lock);
    spin_lock(&lock);
}



/*************************************wdt auto test start********************************************/
/* wdt nv must be enable*/
int bsp_wdt_start_test001(void)
{
	unsigned int timeleft = 0;
	bsp_wdt_start();

	bsp_wdt_get_timeleft(&timeleft);
	if (timeleft <= 30)
	{
		return BSP_OK;
	}
	else
	{
		return BSP_ERROR;
	}
}

int bsp_wdt_stop_test002(void)
{
	unsigned int timeleft = 0;
	bsp_wdt_start();
	bsp_wdt_stop();
	bsp_wdt_get_timeleft(&timeleft);
	if (timeleft >= 30)
	{
		osl_task_delay(10);
		wdt_err("%d\n", timeleft);
		return BSP_OK;
	}
	else
	{
		return BSP_ERROR;
	}
}

int bsp_wdt_keeplive_test003(void)
{
	unsigned int timeleft = 0;
	bsp_wdt_keepalive();
	bsp_wdt_get_timeleft(&timeleft);
	if ((timeleft > 20) && (timeleft <=30))
	{
		return BSP_OK;
	}
	else
	{
		return BSP_ERROR;
	}
}

int bsp_wdt_set_timeout_test004(void)
{
	unsigned int timeleft = 0;
	bsp_wdt_start();
	bsp_wdt_set_timeout(60);
	bsp_wdt_get_timeleft(&timeleft);
	if ((timeleft > 30) && (timeleft <=60))
	{
		return BSP_OK;
	}
	else
	{
		return BSP_ERROR;
	}
}

int bsp_wdt_register_hook_test005(void)
{
	unsigned int timeleft = 0;
	bsp_wdt_register_hook(&timeleft);
	bsp_wdt_reboot_register_hook(&timeleft);
	return BSP_OK;
}

int bsp_wdt_unregister_hook_test006(void)
{
	bsp_wdt_unregister_hook();
	bsp_wdt_reboot_unregister_hook();
	return BSP_OK;
}
/*************************************wdt auto test end********************************************/
