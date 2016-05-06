#ifndef _BALONG_POWER_H
#define _BALONG_POWER_H

#include <linux/platform_device.h>

enum balong_gpio_index {
	BALONG_RESET = 1,
	BALONG_POWER_ON,
	BALONG_PMU_RESET,
	BALONG_HOST_ACTIVE,
	BALONG_HOST_WAKEUP,
	BALONG_SLAVE_WAKEUP,
	BALONG_POWER_IND,
	BALONG_RESET_IND,
	BALONG_GPIO_NUM,
};

struct balong_power_plat_data {
	unsigned int    modem_state;
};

/* MODEM state */
enum modem_state_index {
    MODEM_NOT_READY = 0,
    MODEM_READY,
    MODEM_INVALID,
};

/*NOTE:请统一使用宏定义作为文件节点处理函数的条件值*/
#define POWER_SET_OFF             2
#define BALONG_MODEM_RESET  10

#define RESET_WAIT_TIMEOUT_MCU_MAILMSG  3000

#endif /*_balong_POWER_H*/

