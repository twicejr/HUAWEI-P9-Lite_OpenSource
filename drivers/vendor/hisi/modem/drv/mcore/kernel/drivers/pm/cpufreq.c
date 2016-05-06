#include "cmsis_os.h"

#include "osl_types.h"
#include "osl_bio.h"
#include "osl_irq.h"
#include "m3_cpufreq.h"

T_CPUFREQ_ST g_cpufreq;
u32 g_set_profile = 0;

void cpufreq_init(void)
{

}
void cpufreq_cti_init(void)
{
}
void cpufreq_cti_unlock(u32 base_addr)
{
}
void cpufreq_cti_lock(u32 base_addr)
{
}

void cpufreq_m3_cti_init(void)
{
}

void cpufreq_ccore_cti_init(void)
{
    
}


void cpufreq_acore_cti_init(void)
{
    
}

void pm_dfs_bak(void)
{

}
s32 dfs_get_cur_mode(u32 *cur_ddr)
{
    *cur_ddr = 5;
    return 1;
}

void dfs_set_profile(u32 profile)
{

}

void cpufreq_print_debug(int flag)
{

}
void cpufreq_ccore_unlock(void)
{
	
}
void cpufreq_set_sleepflag(u32 core_type, u32 flag)
{

}

inline void cpufreq_dump_pro_timeslice(u32 cur, u32 new)
{

}

