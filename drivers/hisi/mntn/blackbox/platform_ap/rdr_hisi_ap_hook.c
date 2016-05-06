/*******************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

 *******************************************************************************
 文 件 名   : rdr_hisi_ap_hook.c
 版 本 号   : 初稿
 作    者   : 蒋孝伟 00207786
 生成日期   : 2015年1月15日
 最近修改   :
 功能描述   : AP侧轨迹钩子功能代码
 修改历史   :
 1.日  期   : 2015年1月12日
   作  者   : 蒋孝伟 00207786
 修改内容   : 创建文件

 *******************************************************************************/

/*******************************************************************************
  1 头文件包含
 *******************************************************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sysfs.h>
#include <linux/printk.h>
#include <linux/sched.h>
#include <linux/atomic.h>
#include <linux/cpu.h>
#include <linux/mutex.h>
#include <linux/ctype.h>
#include <linux/smp.h>
#include <linux/preempt.h>
#include <linux/delay.h>
#include <linux/kobject.h>
#include <linux/device.h>
#include <linux/hisi/rdr_hisi_ap_hook.h>

#include "rdr_hisi_ap_ringbuffer.h"

static unsigned char *g_hook_buffer_addr[HK_MAX] = { 0 };
static percpu_buffer_info *g_hook_percpu_buffer[HK_PERCPU_TAG] = { NULL };

static const char *g_hook_trace_pattern[HK_MAX] = {
	"irq_switch::ktime,slice,vec,dir", /*IRQ*/
	"task_switch::ktime,stack,pid,comm", /*TASK*/
	"cpuidle::ktime,dir", /*CPUIDLE*/
	"worker::ktime,action,dir", /*WORKER*/
	"cpu_onoff::ktime,cpu,on",	/*CPU_ONOFF */
	"syscall::ktime,syscall,cpu,dir", /*SYSCALL*/
	"hung_task::ktime,timeout,pid,comm",	/*HUNG_TASK */
	"buddy_fail::ktime,order,pid,comm",	/*BUDDY_FAIL */
	"tasklet::ktime,action,cpu,dir" /*TASKLET*/
};

static atomic_t g_hisi_ap_hook_on[HK_MAX] = { ATOMIC_INIT(0) };
static u32 g_hisi_last_irqs[NR_CPUS] = { 0 };
struct task_struct *g_last_task_ptr[NR_CPUS] = { NULL };

struct mutex hook_switch_mutex;
arch_timer_func_ptr g_arch_timer_func_ptr;

int register_arch_timer_func_ptr(arch_timer_func_ptr func)
{
	if (IS_ERR_OR_NULL(func)) {
		printk(KERN_ERR
		       "[%s], arch_timer_func_ptr [0x%p] is invalid!\n",
		       __func__, func);
		return -EINVAL;
	}
	g_arch_timer_func_ptr = func;
	return 0;
}

int single_buffer_init(unsigned char *addr, unsigned int size, hook_type hk,
		       unsigned int fieldcnt)
{
	if (hk >= HK_MAX) {
		printk(KERN_ERR "[%s], argument hook_type [%d] is invalid!\n",
		       __func__, hk);
		return -EINVAL;
	}
	g_hook_buffer_addr[hk] = addr;

	printk(KERN_DEBUG
	       "hisiap_ringbuffer_init: g_hook_trace_pattern[%d]: %s\n", hk,
	       g_hook_trace_pattern[hk]);
	return hisiap_ringbuffer_init((struct hisiap_ringbuffer_s *)addr, size,
				      fieldcnt, g_hook_trace_pattern[hk]);
}

int percpu_buffer_init(percpu_buffer_info *buffer_info, u32 ratio[][8],	/* HERE:8 */
		       u32 cpu_num, u32 fieldcnt, const char *keys)
{
	int i, ret;
	percpu_buffer_info *buffer = buffer_info;

	for (i = 0; i < cpu_num; i++) {
		printk(KERN_DEBUG "[%s], ratio[%d][%d] = [%d]\n", __func__,
		       (cpu_num - 1), i, ratio[cpu_num - 1][i]);
		buffer->percpu_length[i] = buffer->buffer_size / 16 * ratio[cpu_num - 1][i];	/* HERE:16 */

		if (0 == i) {
			buffer->percpu_addr[0] = buffer->buffer_addr;
		} else {
			buffer->percpu_addr[i] =
			    buffer->percpu_addr[i - 1] +
			    buffer->percpu_length[i - 1];
		}

		printk(KERN_DEBUG
		       "[%s], [%d]: percpu_addr [0x%p], percpu_length [0x%x], fieldcnt [%d]\n",
		       __func__, i, buffer->percpu_addr[i],
		       buffer->percpu_length[i], fieldcnt);

		ret =
		    hisiap_ringbuffer_init((struct hisiap_ringbuffer_s *)
					   buffer->percpu_addr[i],
					   buffer->percpu_length[i], fieldcnt,
					   keys);
		if (ret) {
			printk(KERN_ERR
			       "[%s], cpu [%d] ringbuffer init failed!\n",
			       __func__, i);
			return ret;
		}
	}
	return 0;
}

int hook_percpu_buffer_init(percpu_buffer_info *buffer_info,
			    unsigned char *addr, u32 size, u32 fieldcnt,
			    hook_type hk, u32 ratio[][8])
{
	u32 cpu_num = num_possible_cpus();
	printk(KERN_INFO "[%s], num_online_cpus [%d] !\n", __func__,
	       num_online_cpus());

	if (IS_ERR_OR_NULL(addr) || IS_ERR_OR_NULL(buffer_info)) {
		printk(KERN_ERR
		       "[%s], buffer_info [0x%p] buffer_addr [0x%p], buffer_size [0x%x]\n",
		       __func__, buffer_info, addr, size);
		return -EINVAL;
	}

	if (hk >= HK_PERCPU_TAG || hk < HK_IRQ) {
		printk(KERN_ERR "[%s], hook_type [%d] is invalid!\n", __func__,
		       hk);
		return -EINVAL;
	}

	printk(KERN_INFO "[%s], buffer_addr [0x%p], buffer_size [0x%x].\n",
	       __func__, addr, size);

	g_hook_buffer_addr[hk] = addr;
	g_hook_percpu_buffer[hk] = buffer_info;
	g_hook_percpu_buffer[hk]->buffer_addr = addr;
	g_hook_percpu_buffer[hk]->buffer_size = size;

	return percpu_buffer_init(buffer_info, ratio, cpu_num,
				  fieldcnt, g_hook_trace_pattern[hk]);
}

int irq_buffer_init(percpu_buffer_info *buffer_info, unsigned char *addr,
		    unsigned int size)
{
	unsigned int irq_record_ratio[8][8] = {
	{16, 0, 0, 0, 0, 0, 0, 0},	/*HERE:[8][8]*/
	{8, 8, 0, 0, 0, 0, 0, 0},
	{8, 4, 4, 0, 0, 0, 0, 0},
	{8, 4, 2, 2, 0, 0, 0, 0},
	{8, 4, 2, 1, 1, 0, 0, 0},
	{8, 4, 1, 1, 1, 1, 0, 0},
	{6, 4, 2, 1, 1, 1, 1, 0},
	{6, 4, 1, 1, 1, 1, 1, 1}
	};

	return hook_percpu_buffer_init(buffer_info, addr, size,
				       sizeof(irq_info), HK_IRQ,
				       irq_record_ratio);
}

int task_buffer_init(percpu_buffer_info *buffer_info, unsigned char *addr,
		     unsigned int size)
{
	unsigned int task_record_ratio[8][8] = {
	{16, 0, 0, 0, 0, 0, 0, 0},
	{8, 8, 0, 0, 0, 0, 0, 0},
	{8, 4, 4, 0, 0, 0, 0, 0},
	{8, 4, 2, 2, 0, 0, 0, 0},
	{4, 4, 4, 2, 2, 0, 0, 0},
	{4, 4, 2, 2, 2, 2, 0, 0},
	{4, 4, 2, 2, 2, 1, 1, 0},
	{4, 2, 2, 2, 2, 2, 1, 1}
	};

	return hook_percpu_buffer_init(buffer_info, addr, size,
				       sizeof(task_info), HK_TASK,
				       task_record_ratio);
}

int cpuidle_buffer_init(percpu_buffer_info *buffer_info, unsigned char *addr,
			unsigned int size)
{
	unsigned int cpuidle_record_ratio[8][8] = {
	{16, 0, 0, 0, 0, 0, 0, 0},
	{8, 8, 0, 0, 0, 0, 0, 0},
	{8, 4, 4, 0, 0, 0, 0, 0},
	{8, 4, 2, 2, 0, 0, 0, 0},
	{4, 4, 4, 2, 2, 0, 0, 0},
	{4, 4, 2, 2, 2, 2, 0, 0},
	{4, 4, 2, 2, 2, 1, 1, 0},
	{4, 3, 3, 2, 1, 1, 1, 1}
	};

	return hook_percpu_buffer_init(buffer_info, addr, size,
				       sizeof(cpuidle_info), HK_CPUIDLE,
				       cpuidle_record_ratio);
}

int worker_buffer_init(percpu_buffer_info *buffer_info, unsigned char *addr,
		       unsigned int size)
{
	unsigned int worker_record_ratio[8][8] = {
	{16, 0, 0, 0, 0, 0, 0, 0},
	{8, 8, 0, 0, 0, 0, 0, 0},
	{8, 4, 4, 0, 0, 0, 0, 0},
	{8, 4, 2, 2, 0, 0, 0, 0},
	{4, 4, 4, 2, 2, 0, 0, 0},
	{4, 4, 2, 2, 2, 2, 0, 0},
	{4, 4, 2, 2, 2, 1, 1, 0},
	{4, 3, 3, 2, 1, 1, 1, 1}
	};

	return hook_percpu_buffer_init(buffer_info, addr, size,
				       sizeof(worker_info), HK_WORKER,
				       worker_record_ratio);
}

int cpu_onoff_buffer_init(unsigned char *addr, unsigned int size)
{
	return single_buffer_init(addr, size, HK_CPU_ONOFF,
				  sizeof(cpu_onoff_info));
}

int syscall_buffer_init(unsigned char *addr, unsigned int size)
{
	return single_buffer_init(addr, size, HK_SYSCALL, sizeof(syscall_info));
}

int hung_task_buffer_init(unsigned char *addr, unsigned int size)
{
	return single_buffer_init(addr, size, HK_HUNGTASK,
				  sizeof(hung_task_info));
}

int buddy_fail_buffer_init(unsigned char *addr, unsigned int size)
{
	return single_buffer_init(addr, size, HK_BUDDY_FAIL,
				  sizeof(buddy_fail_info));
}

int tasklet_buffer_init(unsigned char *addr, unsigned int size)
{
	return single_buffer_init(addr, size, HK_TASKLET, sizeof(tasklet_info));
}

/*******************************************************************************
Function:       irq_trace_hook
Description:	中断轨迹记录
Input:		    dir:0中断进入，1中断退出，new_vec:当前中断
Output:		    NA
Return:		    NA
********************************************************************************/
void irq_trace_hook(unsigned int dir, unsigned int old_vec,
		    unsigned int new_vec)
{
	/* 记录时戳、cpu_id、中断号、中断进出方向； */
	irq_info info;
	u8 cpu;

	/*hook is not installed. */
	if (!atomic_read(&g_hisi_ap_hook_on[HK_IRQ])) {
		return;
	}

	info.clock = hisi_getcurtime();
	if (g_arch_timer_func_ptr) {
		info.jiff = (*g_arch_timer_func_ptr) ();
	} else {
		info.jiff = jiffies_64;
	}
	cpu = (u8) smp_processor_id();
	info.dir = (u8) dir;
	info.irq = (u32) new_vec;
	g_hisi_last_irqs[cpu] = new_vec;

	hisiap_ringbuffer_write((struct hisiap_ringbuffer_s *)
				g_hook_percpu_buffer[HK_IRQ]->percpu_addr[cpu],
				(u8 *)&info);

}
EXPORT_SYMBOL(irq_trace_hook);

/*******************************************************************************
Function:       task_switch_hook
Description:	记录内核任务轨迹；
Input:		    pre_task:当前任务task结构体指针，next_task:下一个任务task结构体指针；
Output:		    NA
Return:		    NA
Other:          added to kernel/sched/core.c
********************************************************************************/
void task_switch_hook(const void *pre_task, void *next_task)
{
	/* 记录时戳、cpu_id、next_task的pid、任务名，到对应cpu的循环buffer； */
	struct task_struct *task = (struct task_struct *)next_task;
	task_info info;
	u8 cpu;

	/*hook is not installed. */
	if (!atomic_read(&g_hisi_ap_hook_on[HK_TASK])) {
		return;
	}
	info.clock = hisi_getcurtime();
	cpu = (u8) smp_processor_id();
	info.pid = (u32) task->pid;
	(void)strncpy(info.comm, task->comm, sizeof(task->comm) - 1);	/* [false alarm]:info.comm last item set 0 at next line,will not overflow */
	info.comm[TASK_COMM_LEN - 1] = '\0';
	info.stack = (u64)task->stack;

	g_last_task_ptr[cpu] = task;
	hisiap_ringbuffer_write((struct hisiap_ringbuffer_s *)
				g_hook_percpu_buffer[HK_TASK]->percpu_addr[cpu],
				(u8 *)&info);
}
EXPORT_SYMBOL(task_switch_hook);

/*******************************************************************************
Function:       cpuidle_stat_hook
Description:	记录cpu进入idle下电，退出idle上电的轨迹
Input:		    dir:0进入idle or 1退出idle；
Output:		    NA
Return:		    NA
********************************************************************************/
void cpuidle_stat_hook(u32 dir)
{
	/* 记录时戳、cpu_id、进入idle还是退出idle，到对应的循环buffer； */
	cpuidle_info info;
	u8 cpu;

	/*hook is not installed. */
	if (!atomic_read(&g_hisi_ap_hook_on[HK_CPUIDLE])) {
		return;
	}
	info.clock = hisi_getcurtime();
	cpu = (u8) smp_processor_id();
	info.dir = (u8) dir;

	hisiap_ringbuffer_write((struct hisiap_ringbuffer_s *)
				g_hook_percpu_buffer[HK_CPUIDLE]->percpu_addr[cpu],
				(u8 *)&info);

}
EXPORT_SYMBOL(cpuidle_stat_hook);

/*******************************************************************************
Function:       cpu_on_off_hook
Description:	CPU插拔核记录，当前和SR流程发生的场景一致
Input:		    cpu：cpu号，on：1加核，0减核
Output:		    NA
Return:		    NA
Other:          added to drivers/cpufreq/cpufreq.c
********************************************************************************/
void cpu_on_off_hook(u32 cpu, u32 on)
{
	/* 记录时戳，cpu_id、cpu是on还是off，到对应的循环buffer； */
	cpu_onoff_info info;

	/*hook is not installed. */
	if (!atomic_read(&g_hisi_ap_hook_on[HK_CPU_ONOFF])) {
		return;
	}
	info.clock = hisi_getcurtime();
	info.cpu = (u8) cpu;
	info.on = (u8) on;

	hisiap_ringbuffer_write((struct hisiap_ringbuffer_s *)
				g_hook_buffer_addr[HK_CPU_ONOFF],
				(u8 *)&info);
}
EXPORT_SYMBOL(cpu_on_off_hook);

/*******************************************************************************
Function:       syscall_hook
Description:	记录系统调用轨迹
Input:		    syscall_num:系统调用号, dir:调用进出方向，0:进入，1:退出
Output:		    NA
Return:		    NA
Other:          added to arch/arm64/kernel/entry.S
********************************************************************************/
asmlinkage void syscall_hook(u32 syscall_num, u32 dir)
{
	/* 记录时戳、系统调用号，到对应的循环buffer； */
	syscall_info info;

	/*hook is not installed. */
	if (!atomic_read(&g_hisi_ap_hook_on[HK_SYSCALL])) {
		return;
	}
	info.clock = hisi_getcurtime();
	info.syscall = (u32) syscall_num;
	preempt_disable();
	info.cpu = (u8) smp_processor_id();
	preempt_enable_no_resched();
	info.dir = (u8) dir;

	hisiap_ringbuffer_write((struct hisiap_ringbuffer_s *)
				g_hook_buffer_addr[HK_SYSCALL], (u8 *)&info);
}
EXPORT_SYMBOL(syscall_hook);

/*******************************************************************************
Function:       hung_task_hook
Description:	记录hung task的task信息；
Input:		    tsk:任务结构体指针，timeout：超时时间；
Output:		    NA
Return:		    NA
********************************************************************************/
void hung_task_hook(void *tsk, u32 timeout)
{
	/* 记录时戳、任务pid、超时时间，到对应的循环buffer； */
	struct task_struct *task = (struct task_struct *)tsk;
	hung_task_info info;

	/*hook is not installed. */
	if (!atomic_read(&g_hisi_ap_hook_on[HK_HUNGTASK])) {
		return;
	}
	info.clock = hisi_getcurtime();
	info.timeout = (u32) timeout;
	info.pid = (u32) task->pid;
	/* [false alarm]:info.comm last item set 0 at next line,will not overflow */
	(void)strncpy(info.comm, task->comm, sizeof(task->comm) - 1);
	info.comm[TASK_COMM_LEN - 1] = '\0';

	hisiap_ringbuffer_write((struct hisiap_ringbuffer_s *)
				g_hook_buffer_addr[HK_HUNGTASK], (u8 *)&info);
}
EXPORT_SYMBOL(hung_task_hook);

/*******************************************************************************
Function:       buddy_fail_hook
Description:	记录通过alloc_pages、alloc_pages_node接口申请内存失败信息；
Input:		    order：申请内存大小是2的次方数；
Output:		    NA
Return:		    NA
********************************************************************************/
void buddy_fail_hook(u32 order)
{
	/* 记录时戳、order，当前任务pid，任务名，到对应的循环buffer； */
	struct task_struct *task = current;
	buddy_fail_info info;

	/*hook is not installed. */
	if (!atomic_read(&g_hisi_ap_hook_on[HK_BUDDY_FAIL])) {
		return;
	}
	info.clock = hisi_getcurtime();
	info.order = (u32) order;
	info.pid = (u32) task->pid;
	/* [false alarm]:info.comm last item set 0 at next line,will not overflow */
	(void)strncpy(info.comm, task->comm, sizeof(task->comm) - 1);
	info.comm[TASK_COMM_LEN - 1] = '\0';

	hisiap_ringbuffer_write((struct hisiap_ringbuffer_s *)
				g_hook_buffer_addr[HK_BUDDY_FAIL],
				(u8 *)&info);
}
EXPORT_SYMBOL(buddy_fail_hook);

/*******************************************************************************
Function:       tasklet_hook
Description:     记录tasklet 执行轨迹
Input:		    address:为tasklet 要执行function的 address, dir:调用进出方向，0:进入，1:退出
Output:		    NA
Return:		    NA
Other:          added to arch/arm64/kernel/entry.S
********************************************************************************/
asmlinkage void tasklet_hook(u64 address, u32 dir)
{
	/* 记录时戳、function address 、CPU 号,到对应的循环buffer */
	tasklet_info info;

	/*hook is not installed. */
	if (!atomic_read(&g_hisi_ap_hook_on[HK_TASKLET])) {
		return;
	}
	info.clock = hisi_getcurtime();
	info.action = (u64) address;
	info.cpu = (u8) smp_processor_id();
	info.dir = (u8) dir;

	hisiap_ringbuffer_write((struct hisiap_ringbuffer_s *)
				g_hook_buffer_addr[HK_TASKLET], (u8 *)&info);
}
EXPORT_SYMBOL(tasklet_hook);

/*******************************************************************************
Function:       worker_hook
Description:     记录worker执行轨迹
Input:		    address:为worker 要执行function的 address, dir:调用进出方向，0:进入，1:退出
Output:		    NA
Return:		    NA
Other:          added to arch/arm64/kernel/entry.S
********************************************************************************/
asmlinkage void worker_hook(u64 address, u32 dir)
{
	/* 记录时戳、function address 、CPU 号,到对应的循环buffer */
	worker_info info;
	u8 cpu;

	/*hook is not installed. */
	if (!atomic_read(&g_hisi_ap_hook_on[HK_WORKER])) {
		return;
	}
	info.clock = hisi_getcurtime();
	info.action = (u64) address;
	preempt_disable();
	cpu = (u8) smp_processor_id();
	preempt_enable();
	info.dir = (u8) dir;

	hisiap_ringbuffer_write((struct hisiap_ringbuffer_s *)
				g_hook_percpu_buffer[HK_WORKER]->percpu_addr[cpu],
				(u8 *)&info);
}
EXPORT_SYMBOL(worker_hook);

/*******************************************************************************
Function:       hisi_ap_hook_install
Description:	安装钩子；
Input:		    hk：钩子类型
Output:		    NA
Return:		    0:安装成功，<0:安装失败
********************************************************************************/
int hisi_ap_hook_install(hook_type hk)
{
	if (hk >= HK_MAX) {
		printk(KERN_ERR "[%s], hook type [%d] is invalid!\n", __func__,
		       hk);
		return -EINVAL;
	}

	atomic_set(&g_hisi_ap_hook_on[hk], 1);
	printk(KERN_DEBUG "[%s], hook [%d] is installed!\n", __func__, hk);

	return 0;
}

/*******************************************************************************
Function:       hisi_ap_hook_uninstall
Description:	卸载钩子；
Input:		    hk：钩子类型
Output:		    NA
Return:		    0:卸载成功，<0:卸载失败
********************************************************************************/
int hisi_ap_hook_uninstall(hook_type hk)
{
	if (hk >= HK_MAX) {
		printk(KERN_ERR "[%s], hook type [%d] is invalid!\n", __func__,
		       hk);
		return -EINVAL;
	}

	atomic_set(&g_hisi_ap_hook_on[hk], 0);
	printk(KERN_DEBUG "[%s], hook [%d] is uninstalled!\n", __func__, hk);

	return 0;
}

static int cpuidle_notifier(struct notifier_block *self, unsigned long cmd,
			    void *v)
{
	switch (cmd) {
	case IDLE_START:
		cpuidle_stat_hook(0);
		break;
	case IDLE_END:
		cpuidle_stat_hook(1);
		break;
	default:
		return NOTIFY_DONE;
	}

	return NOTIFY_OK;
}

static struct notifier_block cpuidle_notifier_block = {
	.notifier_call = cpuidle_notifier,
};

/*******************************************************************************
Function:       hot_cpu_callback
Description:    when cpu on/off, the func will be exec.
                And record cpu on/off hook to memory.
Input:          NA
Output:         NA
Return:         NA
********************************************************************************/
static int __cpuinit hot_cpu_callback(struct notifier_block *nfb,
                                           unsigned long action, void *hcpu)
{
	unsigned int cpu = (unsigned long)hcpu;

	switch (action) {
	case CPU_ONLINE:
	case CPU_ONLINE_FROZEN:
		cpu_on_off_hook(cpu, 1);
		break;
	case CPU_DOWN_PREPARE:
	case CPU_DOWN_PREPARE_FROZEN:
		cpu_on_off_hook(cpu, 0);
		break;
	case CPU_DOWN_FAILED:
	case CPU_DOWN_FAILED_FROZEN:
		cpu_on_off_hook(cpu, 1);
		break;
	default:
		return NOTIFY_DONE;
	}

	return NOTIFY_OK;
}

static struct notifier_block __refdata hot_cpu_notifier = {
	.notifier_call = hot_cpu_callback,
};

/*lint -e607*/
/*macro func B*/
#define HOOK_SYSFS_SWITCH(name, hook_type) \
static ssize_t show_hook_switch_##name(struct kobject *kobj, struct kobj_attribute *attr, char *buf)\
{\
	int ret = 0;\
	printk(KERN_ERR "[%s], hook_type [%d]\n", __func__, hook_type);\
	mutex_lock(&hook_switch_mutex);\
	ret = snprintf(buf, PAGE_SIZE, "%d\n", atomic_read(&g_hisi_ap_hook_on[hook_type]));\
	mutex_unlock(&hook_switch_mutex);\
	return ret;\
} \
\
static ssize_t store_hook_switch_##name(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)\
{\
	int ret = 0;\
	int input;\
	ret = sscanf(buf, "%d", &input);\
	printk(KERN_ERR "[%s], B: ret [%d] input [%d], hook_type [%d]!\n", __func__, ret, input, hook_type);\
	if ((ret != 1) || (input > 1) || (input < 0)) {\
		return -EINVAL;\
	} \
	if (!g_hook_buffer_addr[hook_type]) {\
		printk(KERN_ERR "[%s], g_hook_buffer_addr [%d] is null!\n", __func__, hook_type);\
		return -EINVAL;\
	} \
	mutex_lock(&hook_switch_mutex);\
	atomic_set(&g_hisi_ap_hook_on[hook_type], input);\
	mutex_unlock(&hook_switch_mutex);\
	printk(KERN_ERR "[%s], E: ret [%d] input [%d], hook_type [%d]!\n", __func__, ret, input, hook_type);\
	return ret;\
} \
static struct kobj_attribute hook_##name##_attr =\
__ATTR(name, (S_IRUGO | S_IWUSR), show_hook_switch_##name, store_hook_switch_##name);
/*macro func E*/
/*lint +e607*/

/*钩子功能sysfs开关*/
HOOK_SYSFS_SWITCH(irq, HK_IRQ);
HOOK_SYSFS_SWITCH(task, HK_TASK);
HOOK_SYSFS_SWITCH(cpuidle, HK_CPUIDLE);
HOOK_SYSFS_SWITCH(cpuonoff, HK_CPU_ONOFF);
HOOK_SYSFS_SWITCH(syscall, HK_SYSCALL);
HOOK_SYSFS_SWITCH(hungtask, HK_HUNGTASK);
HOOK_SYSFS_SWITCH(buddyfail, HK_BUDDY_FAIL);
HOOK_SYSFS_SWITCH(tasklet, HK_TASKLET);
HOOK_SYSFS_SWITCH(worker, HK_TASKLET);

static const struct attribute *hook_switch_attrs[] = {
	&hook_irq_attr.attr,
	&hook_task_attr.attr,
	&hook_cpuidle_attr.attr,
	&hook_cpuonoff_attr.attr,
	&hook_syscall_attr.attr,
	&hook_hungtask_attr.attr,
	&hook_buddyfail_attr.attr,
	&hook_tasklet_attr.attr,
	&hook_worker_attr.attr,
	NULL
};

static struct kobject *mntn_kobj;
static struct kobject *switch_kobj;
static int __init hisi_ap_hook_init(void)
{
	mutex_init(&hook_switch_mutex);

	idle_notifier_register(&cpuidle_notifier_block);
	register_hotcpu_notifier(&hot_cpu_notifier);

	/* wait for kernel_kobj node ready: */
	while (kernel_kobj == NULL)
		msleep(500);

	mntn_kobj = kobject_create_and_add("mntn", kernel_kobj);
	if (!mntn_kobj) {
		printk(KERN_ERR "[%s], create mntn failed...", __func__);
		return -ENOMEM;
	}

	switch_kobj = kobject_create_and_add("switch", mntn_kobj);
	if (!switch_kobj) {
		printk(KERN_ERR "[%s], create switch failed...", __func__);
		return -ENOMEM;
	}

	return sysfs_create_files(switch_kobj, hook_switch_attrs);
}

postcore_initcall(hisi_ap_hook_init);
