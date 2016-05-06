#ifndef __C_SYS_CPUFREQ_H__
#define __C_SYS_CPUFREQ_H__

#include <bsp_sram.h>
#include <bsp_cpufreq.h>
#include <c_sys_bus_pressure.h>
extern void cpufreq_debug_set_target(unsigned int msg_type, unsigned int source, unsigned int content, unsigned int 
profile);
extern int cpufreq_dfs_set_profile(int profile);
extern int cpufreq_dfs_get_profile(void);
extern void cpufreq_debug_stop(int flag, int enable);
void sys_cpufreq_init(struct master* master);

#endif /* __C_SYS_CPUFREQ_H__ */

