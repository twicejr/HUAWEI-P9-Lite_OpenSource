#ifndef _XMM_POWER_H
#define _XMM_POWER_H

#include <linux/platform_device.h>
#include <linux/gpio.h>


enum xmm_gpio_index {
	XMM_RESET,
	XMM_POWER_ON,
	XMM_PMU_RESET,
	XMM_HOST_ACTIVE,
	XMM_HOST_WAKEUP,
	XMM_SLAVE_WAKEUP,
	XMM_POWER_IND,
	XMM_RESET_IND,
	XMM_GPIO_NUM
};

struct xmm_power_plat_data {
	bool                    flashless;
	struct gpio             gpios[XMM_GPIO_NUM];
	struct platform_device *echi_device;
	char                   *block_name;
};


/* The state that can be set through FS interface */
#define POWER_SET_DEBUGOFF     	0    /* Only turn off the modem, for debug USE */
#define POWER_SET_DEBUGON      	1    /* Only turn on the modem, for debug USE */
#define POWER_SET_OFF       	2    
#define POWER_SET_ON       	3
#define POWER_SET_DL_FINISH     4

/* For usb to call for bus suspend/resume */
extern void xmm_power_runtime_idle(void);
extern void xmm_power_runtime_resume(void);


#endif /*_XMM_POWER_H*/

