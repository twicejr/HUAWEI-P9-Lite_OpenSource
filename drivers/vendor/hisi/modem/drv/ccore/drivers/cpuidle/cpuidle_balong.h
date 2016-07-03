
#ifndef __CPUIDLE_BALONG_H__
#define __CPUIDLE_BALONG_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <product_config.h>
void cpuidle_set_deepsleep_ops(int (*go_deepsleep)(void));
void cpuidle_idle_management (void);
extern void cpu_enter_idle(void);

#ifdef CONFIG_CCORE_CPU_IDLE
void cpu_idle(void);
#else
static void cpu_idle(void) {}
#endif
#ifdef __cplusplus
}
#endif

#endif



