#ifndef _BSP_CPUIDLE_H_
#define _BSP_CPUIDLE_H_
#include <product_config.h>

#ifdef CONFIG_CCORE_CPU_IDLE
extern void cpuidle_set_deepsleep_ops(int (*go_deepsleep)(void));
#else
static inline void cpuidle_set_deepsleep_ops(int (*go_deepsleep)(void)){}
#endif

#endif

