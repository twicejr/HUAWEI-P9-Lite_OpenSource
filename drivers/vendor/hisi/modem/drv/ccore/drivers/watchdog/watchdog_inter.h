/*************************************************************************
*   版权所有(C) 1987-2014, 深圳华为技术有限公司.
*
*   文 件 名 :  wdog_balong.h
*
*   作    者 :  张良栋 z00265007
*
*   描    述 :  该文件为711 uart拨号业务内部使用头文件
*
*   修改记录 :  2015年01月23日  v1.00  z00265007  创建
*************************************************************************/
#ifndef    _WDOG_BALONG_H_
#define    _WDOG_BALONG_H_

#ifdef __cplusplus
extern "C" {
#endif
/**************************************************************************
  头文件包含                            
**************************************************************************/
#include <osl_list.h>
#include <osl_spinlock.h>
/*****************************************************************************
  1 宏定义
*****************************************************************************/
#define WDT_MDM_TASK_PRO		30
#define WDT_MDM_TASK_SIZE		(0x1000)
#define WDT_MDM_ENABLE 1

/*lint --e{10,527, 529, 123, 40, 63, 551,774 } */
#define ARM_DBG_READ(N, M, OP2, VAL) do {\
        asm volatile("mrc p14, 0, %0, " #N "," #M ", " #OP2 : "=r" (VAL));\
		} while (0)

#define ARM_DSCR_HDBGEN		(1 << 14)
#define WDG_PERI_ENABLE_OFFSET 0x33c
/*****************************************************************************
  2 结构体定义
*****************************************************************************/

struct wdt_mdm_dev_info
{
	u32 base_addr;
	u32 int_no;
};

struct wdg_nv_param
{
	u32 wdt_enable;
	u32 wdt_timeout;
	u32 wdt_keepalive_ctime;
	u32 wdt_suspend_timerout;
	u32 wdt_reserve;
};

struct watchdog_ops{
	int (*start)(struct wdg_nv_param);
	int (*stop)(void);
	int (*feed)(void);
	int (*set_timeout)(unsigned int);
	int (*get_timeleft)(unsigned int *);
	int (*suspend)(void);
	int (*resume)(void);
};

struct wdt_mdm_ctrl{
	struct watchdog_ops *ops;
	struct wdg_nv_param nv_param;
	unsigned int drv_id;
	unsigned int cur_timeout;
	unsigned int stop_flag;
	unsigned int task_delay_value;
	unsigned int init_flag;
	spinlock_t lock;
};

struct watchdog_driver{
	struct watchdog_ops *ops;
	unsigned int periphid;
	const char *driver_name;
	struct list_head wdog_lists;
};

extern int hard_watchdog_init(void);
extern int timer_watchdog_init(void);
extern int watchdog_device_register(struct watchdog_driver *drv);

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */
#endif
