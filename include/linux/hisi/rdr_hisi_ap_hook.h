/*******************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

 *******************************************************************************
 文 件 名   : rdr_hisi_ap_hook.h
 版 本 号   : 初稿
 作    者   : 蒋孝伟 00207786
 生成日期   : 2015年1月15日
 最近修改   :
 功能描述   : AP侧轨迹钩子头文件
 修改历史   :
 1.日    期 : 2015年1月15日
 作    者   : 蒋孝伟 00207786
 修改内容   : 创建文件

 *******************************************************************************/
#include <linux/thread_info.h>
#include <linux/hisi/rdr_types.h>
#include <linux/hisi/rdr_pub.h>

typedef u64 (*arch_timer_func_ptr)(void);

typedef enum{
    HK_IRQ = 0,
    HK_TASK,
    HK_CPUIDLE,
    HK_WORKER,
    HK_PERCPU_TAG, /*percpu的轨迹加在HK_PERCPU_TAG以上*/
    HK_CPU_ONOFF = HK_PERCPU_TAG,
    HK_SYSCALL,
    HK_HUNGTASK,
    HK_BUDDY_FAIL,
    HK_TASKLET,
    HK_MAX
}
hook_type;

typedef struct
{
    u64 clock;
    u64 jiff;
    u32 irq;
    u8 dir;
}
irq_info;

typedef struct
{
    u64 clock;
    u64 stack;
    u32 pid;
    char comm[TASK_COMM_LEN];
}
task_info;

typedef struct
{
    u64 clock;
    u8 dir;
}
cpuidle_info;

typedef struct
{
    u64 clock;
    u8 cpu;
    u8 on;
}
cpu_onoff_info;

typedef struct
{
    u64 clock;
    u32 syscall;
    u8 cpu;
    u8 dir;
}
syscall_info;

typedef struct
{
    u64 clock;
    u32 timeout;
    u32 pid;
    char comm[TASK_COMM_LEN];
}
hung_task_info;

typedef struct
{
    u64 clock;
    u32 order;
    u32 pid;
    char comm[TASK_COMM_LEN];
}
buddy_fail_info;

typedef struct
{
    u64 clock;
    u64 action;
    u8 cpu;
    u8 dir;
}
tasklet_info;

typedef struct
{
    u64 clock;
    u64 action;
    u8 dir;
}
worker_info;

typedef struct
{
    unsigned char * buffer_addr;
    unsigned char * percpu_addr[NR_CPUS];
    unsigned int    percpu_length[NR_CPUS];
    unsigned int    buffer_size;
}
percpu_buffer_info;

int register_arch_timer_func_ptr(arch_timer_func_ptr func);
int irq_buffer_init(percpu_buffer_info* buffer_info, unsigned char* addr, unsigned int size);
int task_buffer_init(percpu_buffer_info* buffer_info, unsigned char* addr, unsigned int size);
int cpuidle_buffer_init(percpu_buffer_info* buffer_info, unsigned char* addr, unsigned int size);
int cpu_onoff_buffer_init(unsigned char* addr, unsigned int size);
int syscall_buffer_init(unsigned char* addr, unsigned int size);
int hung_task_buffer_init(unsigned char* addr, unsigned int size);
int buddy_fail_buffer_init(unsigned char* addr, unsigned int size);
int worker_buffer_init(percpu_buffer_info* buffer_info, unsigned char* addr, unsigned int size);
int tasklet_buffer_init(unsigned char* addr, unsigned int size);

#ifdef CONFIG_HISI_BB
void irq_trace_hook(unsigned int dir, unsigned int old_vec, unsigned int new_vec);
void task_switch_hook(const void *pre_task, void *next_task);
void cpuidle_stat_hook (u32 dir);
void cpu_on_off_hook(u32 cpu, u32 on);
void syscall_hook(u32 syscall_num, u32 dir);
void hung_task_hook(void *tsk, u32 timeout);
void tasklet_hook(u64 address, u32 dir);
void worker_hook(u64 address, u32 dir);
/*void buddy_fail_hook(u32 order); is declared in include/linux/gfp.h*/
#else
static inline void irq_trace_hook(unsigned int dir, unsigned int old_vec, unsigned int new_vec){}
static inline void task_switch_hook(const void *pre_task, void *next_task){}
static inline void cpuidle_stat_hook (u32 dir){}
static inline void cpu_on_off_hook(u32 cpu, u32 on){}
static inline void syscall_hook(u32 syscall_num, u32 dir){}
static inline void hung_task_hook(void *tsk, u32 timeout){}
static inline u32 get_current_last_irq(unsigned int cpu){}
static inline void tasklet_hook(u64 address, u32 dir){}
static inline void worker_hook(u64 address, u32 dir){}
#endif
int hisi_ap_hook_install(hook_type hk);
int hisi_ap_hook_uninstall(hook_type hk);

