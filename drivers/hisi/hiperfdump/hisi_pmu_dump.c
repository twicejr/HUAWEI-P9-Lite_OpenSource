/* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*
*/

#include <linux/clk.h>
#include <linux/clk-private.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/spinlock.h>
#include <linux/types.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <asm/hardware/arm_timer.h>
#include <linux/module.h>
#include <linux/debugfs.h>

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <linux/of_address.h>
#include <linux/sched.h>

#include <linux/vmalloc.h>

#include "hisi_perf_timer.h"

#define DEFAULT_CORE 3
#define DEFAULT_T 1

int bind_cpu_id = DEFAULT_CORE;
int period_s = DEFAULT_T;
int period_us = 0;
int delay_time = 0;

/* CPU top-down */
#define MAX_EVENT_NUM 6
struct CPU_TOP_DOWN {
   int bigCoreIds[4];
   int bigCoreEventList[MAX_EVENT_NUM];

   int littleCoreIds[4];
   int littleCoreEventList[MAX_EVENT_NUM];
};
static struct CPU_TOP_DOWN cpu_top_down;

static char __iomem *CPU0_BASE = NULL;
static char __iomem *CPU4_BASE = NULL;
#define CPU_RES_SIZE 0x400000

#define CPU0_DEBUG_BASE 0xECC10000
#define CPU0_PMU_BASE 0xECC30000
#define CPU4_DEBUG_BASE 0xED410000
#define CPU4_PMU_BASE 0xED430000
#define CPU_OFFSET 0x00100000
#define PMU_DEBUG_OFFSET (CPU0_PMU_BASE - CPU0_DEBUG_BASE)

#define CPU_DEBUG_EDLAR 0xFB0
#define CPU_DEBUG_OSLAR_EL1 0x300

#define PMU_PMLAR 0xFB0
#define PMU_PMCR_EL0 0xE04

#define PMU_PMEVTYPER0_EL0 0x400
#define PMU_PMEVTYPER1_EL0 0x404
#define PMU_PMEVTYPER_OFFSET (PMU_PMEVTYPER1_EL0 - PMU_PMEVTYPER0_EL0)

#define PMU_PMCNTENSET_EL0 0xC00

#define PMU_PMEVCNTR0_EL0 0x000
#define PMU_PMEVCNTR1_EL0 0x008
#define PMU_PMEVCNTR_OFFSET (PMU_PMEVCNTR1_EL0 - PMU_PMEVCNTR0_EL0)

#define PMU_PMCCNTR_EL0_L 0x0F8
#define PMU_PMCCNTR_EL0_H 0x0FC

char *mem_addr = NULL;
#define LOG_SIZE 100*1024*1024

static long int cur_pos = 0;
static struct file* fd = NULL;
static mm_segment_t oldfs;
static int dump_header = 0;


#define outp32(addr, val) writel(val, addr)

void set_reg_dump(char __iomem *addr, u32 val, u8 bw, u8 bs)
{
    u32 mask = (1 << bw) - 1;
    u32 tmp = 0;

    tmp = readl(addr);
    tmp &= ~(mask << bs);
    outp32(addr, tmp | ((val & mask) << bs));
}

static int hisi_pmu_dump_open(struct inode *node, struct file *fp)
{
    return 0;
}

static ssize_t hisi_pmu_dump_read(struct file *fp, char __user *ch, size_t count, loff_t *ppos)
{
    return 0;
}

static void print_usage(void)
{
    printk("\r\nUsage:===================================\r\n"
                "-C [core_id] ----- bind this thread to the given core (default cpu3)\r\n"
                "    eg: -C 3\r\n"
                "-T [period_s] [period_us] ----- set sample period (default 1s)\r\n"
                "    eg: -T 0 100, 100us\r\n"
                "-R ----- reset all\r\n"
                "-1 ------  start dump\r\n"
                "-0 ------  end dump\r\n"
                "          \r\n"
                "-D [delay_time_ms]  ----- set delay time (ms)\r\n"
                "    eg: -D 1000, 1s\r\n"
                "-B [core_id_mask] [event1] | [event2] | [event3]  ---- set bigcore eventlist\r\n"
                "    eg: -B 0x3 0x1 | 0x2 | 0x3 | 0x4 | 0x5 | 0x6\r\n"
                "        set cpu4 and cpu5(0x3 -- 0011),\r\n"
                "        eventlist  0x1 | 0x2 | 0x3 | 0x4 | 0x5 | 0x6, six event\r\n"
                "-L [core_id_mask] [event1] | [event2] | [event3]  ---- set littlecore eventlist\r\n");
}

static void print_info(void)
{
    int i = 0, j = 0;
    printk(" ============================= \r\n");
    printk("bind_cpu_id is %d \r\n", bind_cpu_id);
    printk("period_s is %d, period_us is %d\r\n", period_s, period_us);
    printk("delay_time is %d ms \r\n", delay_time);

    for (j=0; j<4; j++) {
        if (cpu_top_down.littleCoreIds[j] != -1) {
            printk("cpu[%d] eventlist ",j);
            for (i=0; i<MAX_EVENT_NUM; i++) {
                printk(" 0x%x", cpu_top_down.littleCoreEventList[i]);
            }
            printk("\r\n");
        }
    }

    for (j=0; j<4; j++) {
        if (cpu_top_down.bigCoreIds[j] != -1) {
            printk("cpu[%d] eventlist ",j+4);
            for (i=0; i<MAX_EVENT_NUM; i++) {
                printk(" 0x%x", cpu_top_down.bigCoreEventList[i]);
            }
            printk("\r\n");
        }
    }
}


static int parse_eventlist(char* buf)
{
    int ret = 0;
    int cpu_id_mask;
    char temp[256] = {0};
    int event_num = 1;
    int eventlist[MAX_EVENT_NUM + 1] = {0};
    int i = 0, j = 0;
    char cmd[256] = "%s 0x%x 0x%x ";
    int big_core = 0;

    if (!buf)
        goto OUT;

    if (buf[1] == 'B' || buf[1] == 'b') {
        big_core = 1;
    } else if (buf[1] == 'L' || buf[1] == 'l') {
        big_core = 0;
    } else {
        goto OUT;
    }

    for (i=0; buf[i] !='\0'; i++) {
        if (buf[i] == '|') {
            strncat(cmd,"| 0x%x ",sizeof(cmd)-strlen(cmd));
            event_num++;
        }
    }

    printk("cmd is %s\r\n",cmd);

    i = sscanf(buf, cmd, &temp, &eventlist[0], &eventlist[1], &eventlist[2],
            &eventlist[3], &eventlist[4], &eventlist[5], &eventlist[6]);

    if (i < (2 + event_num)) {
        printk("parse_eventlist err. only parse %d args\r\n", i);
        goto OUT;
    }

    if (eventlist[0] < 0 || eventlist[0] > 0xf) {
        printk("cpu id err. %d", eventlist[0]);
        goto OUT;
    }

    cpu_id_mask = eventlist[0];
    i = 0;
    for (j=0; j<4; j++) {
        if (cpu_id_mask & (0x1 << j)) {
            if (big_core)
                cpu_top_down.bigCoreIds[i] = j;
            else
                cpu_top_down.littleCoreIds[i] = j;
        } else {
            if (big_core)
                cpu_top_down.bigCoreIds[i] = -1;
            else
                cpu_top_down.littleCoreIds[i] = -1;
        }
        i++;
    }

    for (i=0;i<event_num;i++) {
        if (big_core)
            cpu_top_down.bigCoreEventList[i] = eventlist[i+1];
        else
            cpu_top_down.littleCoreEventList[i] = eventlist[i+1];
    }
    for (i=event_num;i<MAX_EVENT_NUM;i++) {
        if (big_core)
            cpu_top_down.bigCoreEventList[i] = -1;
        else
            cpu_top_down.littleCoreEventList[i] = -1;
    }

    ret = 1;
OUT:
    return ret;
}

static void pmu_event_int(void)
{
    int index = 0;
    int cpu_id = 0;
    int event_index = 0;

    for (index=0; index<4; index++) {
        cpu_id = cpu_top_down.littleCoreIds[index];
        if (cpu_id != -1) {
            outp32(CPU0_BASE + cpu_id * CPU_OFFSET + CPU_DEBUG_EDLAR, 0xC5ACCE55);
            outp32(CPU0_BASE + cpu_id * CPU_OFFSET + CPU_DEBUG_OSLAR_EL1, 0x0);
            outp32(CPU0_BASE + cpu_id * CPU_OFFSET + PMU_DEBUG_OFFSET + PMU_PMLAR, 0xC5ACCE55);
            outp32(CPU0_BASE + cpu_id * CPU_OFFSET + PMU_DEBUG_OFFSET + PMU_PMCR_EL0, 0x7);
            for (event_index=0; event_index<MAX_EVENT_NUM; event_index++) {
                if (cpu_top_down.littleCoreEventList[event_index] != -1) {
                    outp32(CPU0_BASE + cpu_id * CPU_OFFSET + PMU_DEBUG_OFFSET
                        + PMU_PMEVTYPER0_EL0 + event_index * PMU_PMEVTYPER_OFFSET,
                        cpu_top_down.littleCoreEventList[event_index]);
                }
            }
            outp32(CPU0_BASE + cpu_id * CPU_OFFSET + PMU_DEBUG_OFFSET + PMU_PMCNTENSET_EL0, 0x8000003f);
        }
    }

    for (index=0; index<4; index++) {
        cpu_id = cpu_top_down.bigCoreIds[index];
        if (cpu_id != -1) {
            outp32(CPU4_BASE + cpu_id * CPU_OFFSET + CPU_DEBUG_EDLAR, 0xC5ACCE55);
            outp32(CPU4_BASE + cpu_id * CPU_OFFSET + CPU_DEBUG_OSLAR_EL1, 0x0);
            outp32(CPU4_BASE + cpu_id * CPU_OFFSET + PMU_DEBUG_OFFSET + PMU_PMLAR, 0xC5ACCE55);
            outp32(CPU4_BASE + cpu_id * CPU_OFFSET + PMU_DEBUG_OFFSET + PMU_PMCR_EL0, 0x7);
            for (event_index=0; event_index<MAX_EVENT_NUM; event_index++) {
                if (cpu_top_down.bigCoreEventList[event_index] != -1) {
                    outp32(CPU4_BASE + cpu_id * CPU_OFFSET + PMU_DEBUG_OFFSET
                        + PMU_PMEVTYPER0_EL0 + event_index * PMU_PMEVTYPER_OFFSET,
                        cpu_top_down.bigCoreEventList[event_index]);
                }
            }
            outp32(CPU4_BASE + cpu_id * CPU_OFFSET + PMU_DEBUG_OFFSET + PMU_PMCNTENSET_EL0, 0x8000003f);
        }

    }
}

static void pmu_event_enable(int enable)
{
    int index = 0;
    int cpu_id = 0;

    for (index=0; index<4; index++) {
        cpu_id = cpu_top_down.littleCoreIds[index];
        if (cpu_id != -1) {
            if (enable)
                outp32(CPU0_BASE + cpu_id * CPU_OFFSET + PMU_DEBUG_OFFSET + PMU_PMCR_EL0, 0x7);
            else
                outp32(CPU0_BASE + cpu_id * CPU_OFFSET + PMU_DEBUG_OFFSET + PMU_PMCR_EL0, 0x0);
        }
    }

    for (index=0; index<4; index++) {
        cpu_id = cpu_top_down.bigCoreIds[index];
        if (cpu_id != -1) {
            if (enable)
                outp32(CPU4_BASE + cpu_id * CPU_OFFSET + PMU_DEBUG_OFFSET + PMU_PMCR_EL0, 0x7);
            else
                outp32(CPU4_BASE + cpu_id * CPU_OFFSET + PMU_DEBUG_OFFSET + PMU_PMCR_EL0, 0x0);
        }
    }
}


static void pmu_dump_header(void)
{
    int index = 0;
    int cpu_id = 0;
    int event_index = 0;

    cur_pos += snprintf(mem_addr + cur_pos, LOG_SIZE - cur_pos - 1, "     time(s)    \t");

    for (index=0; index<4; index++) {
        cpu_id = cpu_top_down.littleCoreIds[index];
        if (cpu_id != -1) {
            cur_pos += snprintf(mem_addr + cur_pos,
                        LOG_SIZE - cur_pos - 1,
                        "CPU%d_cycle_L\tCPU%d_cycle_H\t",index,index);

           for (event_index=0; event_index<MAX_EVENT_NUM; event_index++) {
                if (cpu_top_down.littleCoreEventList[event_index] != -1) {
                    cur_pos += snprintf(mem_addr + cur_pos,
                        LOG_SIZE - cur_pos - 1,
                        "CPU%d(0x%04x)\t", index, cpu_top_down.littleCoreEventList[event_index]);
                }
            }
        }
    }

    for (index=0; index<4; index++) {
        cpu_id = cpu_top_down.bigCoreIds[index];
        if (cpu_id != -1) {
            cur_pos += snprintf(mem_addr + cur_pos,
                    LOG_SIZE - cur_pos - 1,
                    "CPU%d_cycle_L\tCPU%d_cycle_H\t",index+4,index+4);

           for (event_index=0; event_index<MAX_EVENT_NUM; event_index++) {
                if (cpu_top_down.bigCoreEventList[event_index] != -1) {
                    cur_pos += snprintf(mem_addr + cur_pos,
                        LOG_SIZE - cur_pos - 1,
                        "CPU%d(0x%04x)\t", index+4, cpu_top_down.bigCoreEventList[event_index]);
                }
            }
        }
    }

    cur_pos += snprintf(mem_addr + cur_pos, LOG_SIZE - cur_pos - 1, "\r\n");
}

static void pmu_event_dump(void)
{
    int index = 0;
    int cpu_id = 0;
    int event_index = 0;
    struct timeval hrtv;

    if (dump_header == 0) {
        pmu_dump_header();
        dump_header++;
    }

    do_gettimeofday(&hrtv);
    cur_pos += snprintf(mem_addr + cur_pos, LOG_SIZE - cur_pos - 1,
            "%d.%06d\t",
            (int)hrtv.tv_sec,(int)hrtv.tv_usec);

    for (index=0; index<4; index++) {
        cpu_id = cpu_top_down.littleCoreIds[index];
        if (cpu_id != -1) {
            //dump PMCCNTR_EL0
            cur_pos += snprintf(mem_addr + cur_pos, LOG_SIZE - cur_pos - 1,
                    "%08d\t",
                    readl(CPU0_BASE + cpu_id * CPU_OFFSET + PMU_DEBUG_OFFSET + PMU_PMCCNTR_EL0_L));
            cur_pos += snprintf(mem_addr + cur_pos, LOG_SIZE - cur_pos - 1,
                    "%08d\t",
                    readl(CPU0_BASE + cpu_id * CPU_OFFSET + PMU_DEBUG_OFFSET + PMU_PMCCNTR_EL0_H));

            for (event_index=0; event_index<MAX_EVENT_NUM; event_index++) {
                if (cpu_top_down.littleCoreEventList[event_index] != -1) {
                    //dump event
                    cur_pos += snprintf(mem_addr + cur_pos, LOG_SIZE - cur_pos - 1,
                    "%08d\t",
                    readl(CPU0_BASE + cpu_id * CPU_OFFSET + PMU_DEBUG_OFFSET
                        + PMU_PMEVCNTR0_EL0 + event_index * PMU_PMEVCNTR_OFFSET));
                }
            }
        }
    }

    for (index=0; index<4; index++) {
        cpu_id = cpu_top_down.bigCoreIds[index];
        if (cpu_id != -1) {
            //dump PMCCNTR_EL0
            cur_pos += snprintf(mem_addr + cur_pos, LOG_SIZE - cur_pos - 1,
                    "%08d\t",
                    readl(CPU4_BASE + cpu_id * CPU_OFFSET + PMU_DEBUG_OFFSET + PMU_PMCCNTR_EL0_L));
            cur_pos += snprintf(mem_addr + cur_pos, LOG_SIZE - cur_pos - 1,
                    "%08d\t",
                    readl(CPU4_BASE + cpu_id * CPU_OFFSET + PMU_DEBUG_OFFSET + PMU_PMCCNTR_EL0_H));

            for (event_index=0; event_index<MAX_EVENT_NUM; event_index++) {
                if (cpu_top_down.bigCoreEventList[event_index] != -1) {
                    //dump event
                    cur_pos += snprintf(mem_addr + cur_pos, LOG_SIZE - cur_pos - 1,
                    "%08d\t",
                    readl(CPU4_BASE + cpu_id * CPU_OFFSET + PMU_DEBUG_OFFSET
                        + PMU_PMEVCNTR0_EL0 + event_index * PMU_PMEVCNTR_OFFSET));
                }
            }
        }
    }

    cur_pos += snprintf(mem_addr + cur_pos, LOG_SIZE - cur_pos - 1, "\r\n");
}

static void bind_thread(void)
{
    pid_t curr_pid;
    curr_pid = __task_pid_nr_ns(current, PIDTYPE_PID, NULL);
    if (curr_pid > 0) {
        if (sched_setaffinity(curr_pid, cpumask_of(bind_cpu_id)) < 0) {
            printk("%s: sched_setaffinity err\n", __func__);
        }
    }
}

static void moudle_stop(void)
{
    //printk("moudle_stop\r\n");
    pmu_event_enable(0);
}

static void moudle_dump(void)
{
    //printk("moudle_dump\r\n");
   pmu_event_dump();
}

static void moudle_restart(void)
{
    //printk("moudle_restart\r\n");
    pmu_event_enable(1);
}

struct hisi_bw_dump cpu_pmu_event_callback =
            {moudle_stop, moudle_dump, moudle_restart};

static void pmu_do_start(void)
{
    struct timeval hrtv;
    char fileName[256] = {0};
    static int test_num = 0;

    do_gettimeofday(&hrtv);
    snprintf(fileName, sizeof(fileName), "/data/hwcdump/%d_%d.txt",(int)hrtv.tv_sec, test_num++);
    fd = filp_open(fileName, O_CREAT|O_RDWR, 0644);
    if (IS_ERR_OR_NULL(fd)) {
        printk("filp_open err\r\n");
        return;
    }

    if (!mem_addr)
        mem_addr = vmalloc(LOG_SIZE);

    if (!mem_addr) {
        printk("vmalloc err.\r\n");
        return;
    }
    memset(mem_addr, 0x00, LOG_SIZE);

    oldfs = get_fs();
	set_fs(KERNEL_DS);

    dump_header = 0;
    bind_thread();

    if (delay_time != 0)
        mdelay(delay_time);

    if (CPU0_BASE == NULL)
        CPU0_BASE = ioremap(CPU0_DEBUG_BASE, CPU_RES_SIZE);

    if (CPU4_BASE == NULL)
        CPU4_BASE = ioremap(CPU4_DEBUG_BASE, CPU_RES_SIZE);

    if (CPU0_BASE == NULL || CPU4_BASE == NULL) {
        printk("ioremap err for CPU0_DEBUG_BASE or CPU4_DEBUG_BASE\r\n");
        return;
    }


    hisi_bw_timer_set_callback(cpu_pmu_event_callback);
    hisi_bw_timer_init(bind_cpu_id);
    pmu_event_int();
    hisi_pm_bw_on_timer(period_s, period_us);

}

static void pmu_do_end(void)
{
    loff_t pos = 0;
    ssize_t write_len = 0;

    hisi_bw_timer_clear_callback();
    hisi_bw_timer_deinit();

    if (fd > 0 && cur_pos) {
        printk("mem_addr = %p, cur_pos = %ld, fd = %p\r\n", mem_addr,cur_pos,fd);
        write_len = vfs_write(fd, (char __user*)mem_addr, cur_pos, &pos);
        filp_close(fd, NULL);
        set_fs(oldfs);
        pos = 0;
    }
    cur_pos = 0;

    if (mem_addr) {
        vfree(mem_addr);
        mem_addr = NULL;
    }

    if (CPU0_BASE) {
        iounmap(CPU0_BASE);
        CPU0_BASE = NULL;
    }
    if (CPU4_BASE) {
        iounmap(CPU4_BASE);
        CPU4_BASE = NULL;
    }

}

static void pmu_do_reset(void)
{
    int i;
    for (i=0;i<4;i++) {
        cpu_top_down.bigCoreIds[i] = -1;
        cpu_top_down.littleCoreIds[i] = -1;
    }

    for (i=0;i<MAX_EVENT_NUM;i++) {
        cpu_top_down.bigCoreEventList[i] = -1;
        cpu_top_down.littleCoreEventList[i] = -1;
    }

    bind_cpu_id = DEFAULT_CORE;
    period_s = DEFAULT_T;
    period_us = 0;
    delay_time = 0;
}

static ssize_t hisi_pmu_dump_write(struct file *fp, const char __user *ch, size_t count, loff_t *ppos)
{
    char buf[1024] = {0};
    char temp[256] = {0};
    int temp_int[MAX_EVENT_NUM + 1] = {0};
    //preempt_disable();
    //preempt_enable();

    if (count >= sizeof(buf)) {
        return 0;
    }

    if (copy_from_user(buf, ch, count)) {
        return -EFAULT;
    }

    if (buf[0] != '-') {
        goto ERROR;
    }

    if (buf[1] == 'C' || buf[1] == 'c') {
        if (sscanf(buf, "%s %d", temp, &temp_int[0]) != 2
            || temp_int[0] < 0 || temp_int[0] > 7) {
           goto ERROR;
        }
        bind_cpu_id = temp_int[0];
        printk("set bind_cpu_id = %d\r\n", bind_cpu_id);
    } else if (buf[1] == 'T' || buf[1] == 't') {
        if (sscanf(buf, "%s %d %d", temp, &temp_int[0], &temp_int[1]) != 3
            || temp_int[0] < 0 || temp_int[1] < 0
            || (temp_int[0] == 0 && temp_int[1] == 0)) {
               goto ERROR;
        }
        period_s = temp_int[0];
        period_us = temp_int[1];
        printk("set period %d s,%d us\r\n", period_s, period_us);
    } else if (buf[1] == '1') {
        pmu_do_start();
    } else if (buf[1] == '0') {
        pmu_do_end();
    } else if (buf[1] == 'D' || buf[1] == 'd') {
        if (sscanf(buf, "%s %d", temp, &temp_int[0]) != 2
                || temp_int[0] < 0) {
               goto ERROR;
        }
        delay_time = temp_int[0];
        printk("set delay_time %d ms\r\n", delay_time);
    } else if (buf[1] == 'B' || buf[1] == 'b'
                || buf[1] == 'L' || buf[1] == 'l') {
        if (parse_eventlist(buf) == 0)
             goto ERROR;
    } else if (buf[1] == 'R' || buf[1] == 'r') {
        pmu_do_reset();
    } else {
         goto ERROR;
    }

    print_info();
    goto OUT;
ERROR:
    pr_info("unknow cmd: %s\n", buf);
    print_usage();
OUT:
    return count;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = hisi_pmu_dump_open,
	.read = hisi_pmu_dump_read,
	.write = hisi_pmu_dump_write,
};

static int __init hisi_pmu_dump_init(void)
{
    int i;
    struct dentry * rootdir = debugfs_create_dir("hisi_pmu_dump", NULL);
    debugfs_create_file("state", S_IWUSR, rootdir, NULL, &fops);

    for (i=0;i<4;i++) {
        cpu_top_down.bigCoreIds[i] = -1;
        cpu_top_down.littleCoreIds[i] = -1;
    }
    return 0;
}

static void __exit hisi_pmu_dump_exit(void)
{
}

module_init(hisi_pmu_dump_init);
module_exit(hisi_pmu_dump_exit);
