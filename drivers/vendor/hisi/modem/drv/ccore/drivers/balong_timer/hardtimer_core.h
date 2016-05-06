#ifndef __HARDTIMER_BALONG_H__
#define __HARDTIMER_BALONG_H__
#include <hi_timer.h>
#include <osl_list.h>
#include <osl_spinlock.h>
#include <drv_comm.h>
#include <bsp_hardtimer.h>
/*lint -e{760}*/

#ifndef SEM_EMPTY
#define SEM_EMPTY 0
#endif

#ifndef SEM_FULL
#define SEM_FULL 1
#endif

#define TIMERS_INTSTATUS(hard_timer_module_addr)                  (hard_timer_module_addr + 0xA0)
#define TIMERS_EOI(hard_timer_module_addr)                        (hard_timer_module_addr+ 0xA4 )
#define TIMERS_RAWINTSTATUS(hard_timer_module_addr)               (hard_timer_module_addr+ 0xA8)
#define TIMER_LOADCOUNT(hard_timer_id_addr)                       (hard_timer_id_addr + HI_TIMER_LOADCOUNT_OFFSET )
#define TIMER_LOADCOUNT_H(hard_timer_id_addr)                     (hard_timer_id_addr + HI_TIMER_LOADCOUNT_H_OFFSET )
#define TIMER_CURRENTVALUE(hard_timer_id_addr)                    (hard_timer_id_addr + HI_TIMER_CURRENTVALUE_OFFSET )
#define TIMER_CURRENTVALUE_H(hard_timer_id_addr)                  (hard_timer_id_addr +  HI_TIMER_CURRENTVALUE_H_OFFSET)
#define TIMER_CONTROLREG(hard_timer_id_addr)                      (hard_timer_id_addr + HI_TIMER_CONTROLREG_OFFSET )
#define TIMER_EOI(hard_timer_id_addr)                             (hard_timer_id_addr +  HI_TIMER_EOI_OFFSET)
#define TIMER_INTSTATUS(hard_timer_id_addr)                       (hard_timer_id_addr + HI_TIMER_INTSTATUS_OFFSET )

#define TIMER_EN_ACK                                 (1<<4)
#define TIMER_INT_MASK                               (1<<2)
#define TIMER_MODE_PERIOD                            (1<<1)
#define HARD_TIMER_ENABLE                             1
#define HARD_TIMER_DISABLE                            0
 

struct timer_device ;

struct timer_core_ops{
	s32 (*timer_init)(struct timer_device  *device);
	s32 (*timer_enable)(struct timer_device  *device);
	s32 (*timer_disable)(struct timer_device  *device);
	void (*timer_mask)(struct timer_device  *device);
	void (*timer_unmask)(struct timer_device  *device);
	u32 (*timer_get_cur_value)(struct timer_device  *device);
	u32 (*timer_int_status)(struct timer_device  *device);
	void (*timer_set_init_value)(struct timer_device  *device,unsigned int value);
	void (*timer_int_clear)(struct timer_device  *device);
	u32 (*check_timer_enabled)(struct timer_device  *device);
	void (*suspend)(struct timer_device  *device);
	void (*resume)(struct timer_device  *device);
};
struct timer_driver {
    struct timer_core_ops	*ops;
    unsigned int periphid;
    const char	 *driver_name;
    struct list_head timer_drivers;
};
struct timer_device {
	char*				name;
    unsigned int        base_addr;		
    unsigned int        irq;			/* irq number */
    unsigned int        clk;	    
    unsigned int        periphid;
	unsigned int 		sr_flag;/*timer suspend flag*/
	spinlock_t 			lock;
	unsigned int 		lp_timer_valuereg;
	unsigned int 		lp_timer_ctrlreg;
    struct timer_driver  *driver;
	struct bsp_hardtimer_control timer_ctrl;
};

void bsp_timer_driver_register(struct timer_driver  *timer_driver);
void synopsis_timer_drviver_init(void);
void arm_timer_drviver_init(void);
extern int set_adp_timer_isr_and_pm(void);
extern void set_timer_clk(void);
#endif
