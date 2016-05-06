
#include <linux/kernel.h>
#include <linux/cpumask.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/kthread.h>
#include <osl_module.h>
#include <osl_malloc.h>
#include <osl_sem.h>
#include <osl_bio.h>
#include <bsp_thermal.h>

#define CORE_HEATING_MAX_NUM    12

struct core_heating{
    volatile u32 thread_flag;
    u32 core_id;
    struct cpumask cpu_mask;
};

struct current_core_heating_info{
    u32 core_num_max;
    u32 thermal_core;
    u32 config_cores;
};
struct core_heating g_cores_array[CORE_HEATING_MAX_NUM] = {};

struct current_core_heating_info g_thermal_info = {0};

static osl_sem_id thermal_sem;
static struct work_struct thremal_up,thremal_down;
static volatile u64 g_calc_result = 0;

void test_pid_affinity(struct core_heating *current_core)
{
    struct cpumask cpu_mask = {};
    pid_t curr_pid;

    cpumask_clear(&cpu_mask);
    curr_pid = task_pid_nr_ns(current, NULL);

    if(sched_getaffinity(curr_pid, &cpu_mask) < 0) 
    {
        thermal_print("sched_getaffinity err\n");
        return;
    }
    current_core->cpu_mask = cpu_mask;
    
    if(cpumask_test_cpu(current_core->core_id, &cpu_mask))
    {
        thermal_print("pid: %d is runnig in core : %d cpumask_weight:%d\n",curr_pid, current_core->core_id, cpumask_weight(&cpu_mask));
    }
    return;
}

void do_something_thermal_core(struct core_heating *current_core)
{
#ifdef BSP_CONFIG_PHONE_TYPE
    u64 math_calc = 0x10;
#else
    u32 math_calc = 0x10;
#endif
	int i;
    do{
        for(i=0;i<10000000;i++)
        {

            math_calc += (math_calc / 2);
            math_calc -= (2 * i);
            math_calc += (math_calc * 7);
            math_calc += (4 * i);
            math_calc += (math_calc / 5);
            math_calc -= (2 * i);
        }
        g_calc_result += math_calc;		
    }while(current_core->thread_flag != SYSTEM_HEATING_END);
}
int heating_core_kthread(void *core_array)
{
    struct core_heating *current_core = (struct core_heating *)core_array;
    test_pid_affinity(current_core);
    do_something_thermal_core(current_core);
    current_core->core_id = 0;
    cpumask_clear(&current_core->cpu_mask);
    return THERMAL_UP_OK;
}
void thermal_core_up(struct work_struct *unuse_work)
{
    u32 valid_core_num =0;
    struct task_struct *task;
    u32 core_num = 0;
    int i;
    pid_t curr_pid;
    struct cpumask cpu_mask = {};

    osl_sem_down(&thermal_sem);

    if(g_thermal_info.config_cores <= g_thermal_info.thermal_core)
    {
        osl_sem_up(&thermal_sem);
        return;
    }
    core_num = g_thermal_info.config_cores - g_thermal_info.thermal_core;

    valid_core_num = min(core_num,g_thermal_info.core_num_max);
    
    for(i = g_thermal_info.core_num_max; i > (g_thermal_info.core_num_max - valid_core_num); i--)
    {
        g_cores_array[i].core_id = i - 1;
        g_cores_array[i].thread_flag = (u32)SYSTEM_HEATING_BEGIN;
        
        task = (struct task_struct *)kthread_run(heating_core_kthread, &g_cores_array[i], "thermal_kthread");
        if(IS_ERR((void*)task))
        {
            core_num = g_thermal_info.core_num_max - i;
            thermal_print("kthread_run fail\n");
            goto end;
        }
        curr_pid = task_pid_nr_ns(task, NULL);
        
        cpumask_clear(&cpu_mask);
        cpumask_set_cpu(g_cores_array[i].core_id, &cpu_mask);

        if(sched_setaffinity(curr_pid, &cpu_mask) < 0) 
        {
            thermal_print("sched_setaffinity err\n");
        }
        else
        {
            thermal_print("new pid: %d is runnig in core : %d \n",curr_pid, g_cores_array[i].core_id);
        }

    }
    core_num = valid_core_num;
end:
    g_thermal_info.thermal_core += core_num;
    g_thermal_info.core_num_max -= core_num;
    osl_sem_up(&thermal_sem);
    thermal_print("increase %d cpus,thermal_cpus: %d,max_cpus: %d\n",core_num, g_thermal_info.thermal_core,num_possible_cpus());
}
void thermal_core_down(struct work_struct *unuse_work)
{
    u32 i;
    osl_sem_down(&thermal_sem);
    g_thermal_info.core_num_max = num_possible_cpus();
    for(i = g_thermal_info.core_num_max; \
        i > (g_thermal_info.core_num_max - g_thermal_info.thermal_core); i--)
    {
        g_cores_array[i].thread_flag = (u32)SYSTEM_HEATING_END;
    }
    thermal_print(" %d core thermal down\n",g_thermal_info.thermal_core);
    g_thermal_info.thermal_core = 0;
    osl_sem_up(&thermal_sem);
}
s32 thermal_icc_callback(u32 icc_channel_id , u32 len, void* context)
{
    s32 ret = 0;
    u32 cp_icc_info;

    ret = bsp_icc_read((u32)SYSTEM_HEADING_CHAN_ID, (u8*)&cp_icc_info, len);
    if (ret != (int)sizeof(u32))
    {
         thermal_print("bsp_icc_read errNo = 0x%x\n",ret);
         return THERMAL_UP_ERROR;
    }
    if(cp_icc_info & SYSTEM_HEATING_BEGIN)
    {
         osl_sem_down(&thermal_sem);
         g_thermal_info.config_cores = (cp_icc_info & 0xF);
         osl_sem_up(&thermal_sem);
         schedule_work(&thremal_up);
    }else if(cp_icc_info & SYSTEM_HEATING_END)
    {
         osl_sem_down(&thermal_sem);
         g_thermal_info.config_cores = 0;
         osl_sem_up(&thermal_sem);
         schedule_work(&thremal_down);
    }else
    {
         thermal_print("cp action unkown\n");
    }
    return THERMAL_UP_OK;
}

static int thermal_up_init(void)
{
    s32 ret = 0;
    osl_sem_init(1,&thermal_sem);
    INIT_WORK(&thremal_up,thermal_core_up);
    INIT_WORK(&thremal_down,thermal_core_down);
    g_thermal_info.core_num_max = num_possible_cpus();
    ret = bsp_icc_event_register((u32)SYSTEM_HEADING_CHAN_ID,\
        (read_cb_func)thermal_icc_callback, NULL, NULL, NULL);
    if(ret)
    {
        thermal_print("bsp_icc_event_register errNo = 0x%x\n",ret);
        return THERMAL_UP_ERROR;
    }
    return THERMAL_UP_OK;
}

module_init(thermal_up_init);

