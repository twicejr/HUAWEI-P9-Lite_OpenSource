/*lint --e{762 } */
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



#ifndef BSP_NULL
#define BSP_NULL            (void*)0
#endif



struct wdt_control{
	wdt_timeout_cb wdt_cb;
};
void hi6930_wdt_lowtask(void);
s32 hi6930_wdt_init(void);
s32 bsp_wdt_suspend(u32 timeout);
void bsp_wdt_resume(void);

#endif /* __WDT_BALONG_H__*/
