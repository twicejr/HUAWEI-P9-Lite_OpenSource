#ifndef __WDT_BALONG_H__
#define __WDT_BALONG_H__





#ifndef HARD_TIMER_ENABLE
#define HARD_TIMER_ENABLE              (1)
#endif
#ifndef TIMER_INT_MASK
#define TIMER_INT_MASK                    (1<<2)
#endif
 
#ifndef BSP_FALSE
#define BSP_FALSE           (0)
#endif
#ifndef BSP_TRUE
#define BSP_TRUE           (1)
#endif
typedef void(*wdt_timeout_cb)(int core);/*A¡¢CºË¹²ÓÃ*/


#ifndef BSP_NULL
#define BSP_NULL            (void*)0
#endif



struct wdt_control{
	wdt_timeout_cb wdt_cb;
	u32 periphid;
};
void bsp_wdt_feed(void);
void hi6930_wdt_lowtask(void);
s32 bsp_wdt_init(void);
void bsp_wdt_reboot_direct(void);
s32 bsp_wdt_suspend(u32 timeout);
void bsp_wdt_resume(void);
void bsp_wdt_stop_awdt(void);
void bsp_wdt_restart_awdt(void);
void bsp_wdt_stop_cwdt(void);
void bsp_wdt_restart_cwdt(void);
void bsp_wdt_enable(void);
s32 bsp_wdt_stop(void);

#endif /* __WDT_BALONG_H__*/
