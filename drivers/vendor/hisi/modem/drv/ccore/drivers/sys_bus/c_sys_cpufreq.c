#include <of.h>
#include <osl_malloc.h>
#include <osl_thread.h>
#include <bsp_cpufreq.h>
#include <bsp_slice.h>
#include <c_sys_bus_core.h>
#include <c_sys_bus_pressure.h>
#include <c_sys_cpufreq.h>


static u32 sys_cpufreq_debug_ddr_pro = 0;
static u32 sys_cpufreq_debug_ddr_flag = 1;
static u32 sys_cpufreq_debug_ddr_tick = 10;

static void sys_cpufreq_stress_task(void)
{
    u32 tmp = 0;
    u32 i = 0, j = 0;
    
    cpufreq_debug_stop(1,0);
    while (sys_cpufreq_debug_ddr_flag)
    {
        cpufreq_debug_set_target(1, 1, 4, 0);
        for (i = BALONG_FREQ_MAX; i > BALONG_FREQ_MIN; i--)
        {
            for (j = (u32)BALONG_FREQ_MIN; j < (u32)BALONG_FREQ_MAX; j++)
            {
                cpufreq_debug_set_target(1, 0, 3, 0);
                (void)cpufreq_dfs_set_profile((s32)i);
                (void)osl_task_delay(1);
                tmp = j;/* [false alarm]:debug test program */
                cpufreq_debug_set_target(1, 0, 3, 0);
                (void)cpufreq_dfs_set_profile((s32)tmp);
                sys_cpufreq_debug_ddr_pro = cpufreq_dfs_get_profile();
                (void)osl_task_delay((s32)sys_cpufreq_debug_ddr_tick);
            }
        }
    }
}

static OSL_TASK_ID sys_stress_test_id = 0;
static void sys_cpufreq_stress_task_int(void)
{
	(void)osl_task_init("stresstest", 33, 4096, (OSL_TASK_FUNC)sys_cpufreq_stress_task, 0, &sys_stress_test_id); /*lint !e64 !e119 */
}

void sys_cpufreq_record(struct master* master)
{
}

void sys_cpufreq_report(struct master* master)
{
}

void sys_cpufreq_start(struct master* master)
{
    sys_cpufreq_debug_ddr_flag = 1;
    sys_cpufreq_stress_task_int();
}

void sys_cpufreq_stop(struct master* master)
{
    sys_cpufreq_debug_ddr_flag = 0;
    if (0 != sys_stress_test_id)
        kthread_stop(sys_stress_test_id);
}

void sys_cpufreq_init(struct master* master)
{
    master->start = sys_cpufreq_start;
    master->stop = sys_cpufreq_stop;
    master->record = sys_cpufreq_record;
    master->report = sys_cpufreq_report;

    sys_bus_trace("cpufreq ok\n");
}


