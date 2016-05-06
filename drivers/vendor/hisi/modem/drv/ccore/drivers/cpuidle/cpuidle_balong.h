/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  cpuidle.h
*
*   作    者 :  xujingcui 00221564
*
*   描    述 :
*
*   修改记录 :  2013年3月28日  v1.00  xujingcui  创建
*************************************************************************/
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



