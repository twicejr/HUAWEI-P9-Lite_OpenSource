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

#include "hisi_perf_timer.h"

#define MODULE_NAME                            "perf_monitor_irq"

/*timing for 1s */
#define BW_TIMER_FREQ_48M                  (4800000)
/*timer_value = time * freq*/
#define BW_TIMER_SET_VALUE(x)              ((BW_TIMER_FREQ_48M) / 100000 * (x) / 10)

/*timer2 register offsets and masks */
#define BW_TIMER_DEFAULT_LOAD              (0xFFFFFFFF)
/*max data of int32*/
#define MAX_DATA_OF_32BIT                  (0xFFFFFFFF)
/*max time that timer2 can be timing(useconds)*/
#define BW_TIMER_MAX_TIMING                ((MAX_DATA_OF_32BIT / BW_TIMER_FREQ_48M) * 1000000)

struct hisi_bw_timer {
    spinlock_t                lock;
    void __iomem              *base;
    struct clk                *clk;
    struct clk                *pclk;
    int                       irq;
 };

/* local variables */
struct hisi_bw_timer bandwidth_timer;

#define MAX_MONITOR_MOUDLE 16
int moudle_num = 0;
static struct hisi_bw_dump hisi_module_map[MAX_MONITOR_MOUDLE];

int hisi_bw_timer_set_callback(struct hisi_bw_dump moudle_callback)
{
    int ret = 0;

    if (moudle_num >= MAX_MONITOR_MOUDLE) {
        printk("hisi_bw_timer_set_callback err! full moudle");
        goto OUT;
    }

    hisi_module_map[moudle_num].hisi_moudle_dump_stop = moudle_callback.hisi_moudle_dump_stop;
    hisi_module_map[moudle_num].hisi_moudle_dump_print = moudle_callback.hisi_moudle_dump_print;
    hisi_module_map[moudle_num].hisi_moudle_dump_restart = moudle_callback.hisi_moudle_dump_restart;

    moudle_num++;

    ret = 1;
OUT:
    return ret;
}

void hisi_bw_timer_clear_callback(void)
{
    int i;
    for (i=0; i<MAX_MONITOR_MOUDLE; i++) {
        hisi_module_map[i].hisi_moudle_dump_stop = NULL;
        hisi_module_map[i].hisi_moudle_dump_print = NULL;
        hisi_module_map[i].hisi_moudle_dump_restart = NULL;
    }

    moudle_num = 0;
}


/*local functions*/
static void hisi_bw_timer_set_time(unsigned int time);
static void hisi_bw_timer_init_config(void);
static int  hisi_bw_timer_clk_get(void);
static int  hisi_bw_timer_clk_enable(void);
static void hisi_bw_timer_clk_disable(void);

static void hisi_bw_timer_set_time(unsigned int time)
{
    unsigned long ctrl, flags;

    spin_lock_irqsave(&bandwidth_timer.lock, flags);

    ctrl = readl(bandwidth_timer.base + TIMER_CTRL);

    /*first disable timer*/
    ctrl &= (~TIMER_CTRL_ENABLE);
    writel(ctrl, bandwidth_timer.base + TIMER_CTRL);

    /*set TIME_LOAD register together*/
    writel(time, bandwidth_timer.base + TIMER_LOAD);

    writel(time, bandwidth_timer.base + TIMER_BGLOAD);

    /*then enable timer again*/
    ctrl |= (TIMER_CTRL_ENABLE | TIMER_CTRL_IE);

    writel(ctrl, bandwidth_timer.base + TIMER_CTRL);

    spin_unlock_irqrestore(&bandwidth_timer.lock, flags);
}

/*
*func: do timer initializtion
*
*description:
*1. set timer clk to 4.8MHz
*2. if mode is periodic and period is not the same as timer value, set bgload value
*3. set timer control: mode, 32bits, no prescale, interrupt enable, timer enable
*
*/
static void hisi_bw_timer_init_config(void)
{
    unsigned long flags, ctrl = 0;
    //unsigned int reg = 0;
    //int ret = 0;
    //struct clk  *tempclk;

    spin_lock_irqsave(&bandwidth_timer.lock, flags);

    /*1. timer select 4.8M*/
    /*
    tempclk = clk_get_parent_by_index(bandwidth_timer.pclk, 1);
    if (IS_ERR_OR_NULL(tempclk)) {
        printk("fail to get parent clk. \n");
        return;
    }

    ret = clk_set_parent(bandwidth_timer.pclk, tempclk);
    if (ret < 0) {
    	pr_err("clk_set_parent :Failed to set parent!\n");
    	return;
    }
    */

    /*2. clear the interrupt */
    writel(1, bandwidth_timer.base + TIMER_INTCLR);

    /*3. set timer2 control reg: 32bit, interrupt disable, timer_value, oneshot mode and disable wakeup_timer*/
    ctrl = TIMER_CTRL_32BIT;

    writel(BW_TIMER_DEFAULT_LOAD, bandwidth_timer.base + TIMER_LOAD);

    //ctrl |= TIMER_CTRL_ONESHOT;
    ctrl |= TIMER_CTRL_PERIODIC;

    writel(ctrl, bandwidth_timer.base + TIMER_CTRL);

    spin_unlock_irqrestore(&bandwidth_timer.lock, flags);
}

static irqreturn_t hisi_bw_timer_interrupt(int irq, void *dev_id)
{
    int i;

    if ((readl(bandwidth_timer.base + TIMER_RIS)) & 0x1) {
        /* clear the interrupt */
        writel(1, bandwidth_timer.base + TIMER_INTCLR);

        for (i=0; i<moudle_num; i++) {
            if (hisi_module_map[i].hisi_moudle_dump_stop)
                hisi_module_map[i].hisi_moudle_dump_stop();
        }
        for (i=0; i<moudle_num; i++) {
            if (hisi_module_map[i].hisi_moudle_dump_print)
                hisi_module_map[i].hisi_moudle_dump_print();
        }
        for (i=0; i<moudle_num; i++) {
            if (hisi_module_map[i].hisi_moudle_dump_restart)
                hisi_module_map[i].hisi_moudle_dump_restart();
        }
    }
    return IRQ_HANDLED;
}

void hisi_bw_timer_disable(void)
{
    unsigned long ctrl, flags;

    spin_lock_irqsave(&bandwidth_timer.lock, flags);

    ctrl = readl(bandwidth_timer.base + TIMER_CTRL);

    ctrl &= ~(TIMER_CTRL_ENABLE | TIMER_CTRL_IE);

    writel(ctrl, bandwidth_timer.base + TIMER_CTRL);

    spin_unlock_irqrestore(&bandwidth_timer.lock, flags);

    /*disbale clk*/
    hisi_bw_timer_clk_disable();
}

static int hisi_bw_timer_clk_get(void)
{
    int ret = 0;

    /*get timer clk*/
    bandwidth_timer.clk = clk_get(NULL,TIMER_NAME);
    if (IS_ERR(bandwidth_timer.clk)) {
        printk("hisi_bw_timer_clk_get: clk not found\n");
        ret = PTR_ERR(bandwidth_timer.clk);
        return ret;
    }

    bandwidth_timer.pclk = clk_get_parent(bandwidth_timer.clk);
    if (IS_ERR(bandwidth_timer.pclk)) {
        printk("hisi_bw_timer_clk_get: pclk not found\n");
        ret = PTR_ERR(bandwidth_timer.pclk);
        return ret;
    }

    return ret;
}

static int hisi_bw_timer_clk_enable(void)
{
    int ret = 0;

    ret = clk_prepare_enable(bandwidth_timer.clk);
    if (ret ) {
        printk("hisi_bw_timer_clk_enable :clk prepare enable failed !\n");
    }

    return ret;
}

static void hisi_bw_timer_clk_disable(void)
{
    clk_disable_unprepare(bandwidth_timer.clk);
}

static void hisi_bw_timer_clk_put(void)
{
    clk_put(bandwidth_timer.clk);
}

/*
*func: used for wakeup on timer for S/R
*
*decs: set timer2 count value = (seconds*1000+milliseconds)*32.768 ms
*mode is used for user to set timer work in periodic or oneshot mode
*mode: 0 for periodic
*          1 for oneshot
*/
int hisi_pm_bw_on_timer(unsigned int seconds, unsigned int useconds)
{
    int ret = 0;
    unsigned int set_time;
	unsigned int rate;

    if (!seconds && !useconds) {
        printk("hisi_pm_bw_on_timer: input time error!\n");
        goto OUT;
    }

    rate = clk_get_rate(bandwidth_timer.clk);
    printk("==== hisi_pm_bw_on_timer rate is %d\r\n", rate);

    /*change time to milliseconds format*/
    set_time = 1000 * 1000 * seconds + useconds;
    printk("==== hisi_pm_bw_on_timer set_time is %d, BW_TIMER_SET_VALUE(%d)\r\n",
        set_time, BW_TIMER_SET_VALUE(set_time));

    if (BW_TIMER_MAX_TIMING < set_time) {
        printk("hisi_pm_bw_on_timer: input timing overflow!\n");
        goto OUT;
    }

    /*enable clk*/
    if(hisi_bw_timer_clk_enable()) {
        printk("hisi_pm_bw_on_timer: clk enable error!\n");
        goto OUT;
    }

    /*add for the case ICS4.0 system changed the timer clk to 6.5MHz
    here changed back to 4.8MHz.
    */
    hisi_bw_timer_init_config();
    hisi_bw_timer_set_time(BW_TIMER_SET_VALUE(set_time));
    ret = 1;
OUT:
    return ret;
}
EXPORT_SYMBOL(hisi_pm_bw_on_timer);

int hisi_bw_timer_init(int bind_cpu_id)
{
    int ret = 0;

    if (bandwidth_timer.clk)
        return 1;

    if (hisi_bw_timer_clk_get()) {
        printk("clk get failed\n");
        goto err_clk_get;
    }

    bandwidth_timer.base = ioremap(TIMER5_BASE, RES_SIZE);
    if (!bandwidth_timer.base) {
        printk("ioremap fail\n");
        goto err_ioremap;
    }

    spin_lock_init(&bandwidth_timer.lock);

	ret = clk_set_rate(bandwidth_timer.clk, BW_TIMER_FREQ_48M);
	if (ret){
		pr_err("[%s] set rate falied,%d\n",__func__,__LINE__);
		goto err_clk_enable;
	}

    if(hisi_bw_timer_clk_enable()) {
        printk("clk enable failed\n");
        goto err_clk_enable;
    }

    bandwidth_timer.irq = TIMER5_IRQ;

    /*do timer init configs: disable timer ,mask interrupt, clear interrupt and set clk to 32.768KHz*/
    hisi_bw_timer_init_config();

    /*register timer2 interrupt*/
    if(request_irq(bandwidth_timer.irq, hisi_bw_timer_interrupt, IRQF_NO_SUSPEND, MODULE_NAME, NULL)) {
        printk("request irq for timer5 error\n");
        goto err_clk_enable;
    }

    irq_set_affinity(bandwidth_timer.irq, cpumask_of(bind_cpu_id));

    /*when init config finished, disable the clk and pclk for timer and enable them when needed.*/
    hisi_bw_timer_clk_disable();

    printk("hisi bandwidth timer init has been finished\n");

    return 1;

err_clk_enable:
    hisi_bw_timer_clk_disable();
    iounmap(bandwidth_timer.base);
err_ioremap:
    hisi_bw_timer_clk_put();
err_clk_get:
    bandwidth_timer.clk = NULL;
    bandwidth_timer.pclk = NULL;
    //release_mem_region(res->start, resource_size(res));
    printk("hisi bandwidth timer init failed!\n");
    return ret;
}
EXPORT_SYMBOL(hisi_bw_timer_init);

int hisi_bw_timer_deinit(void)
{
    if (!bandwidth_timer.clk)
        return 0;

    free_irq(bandwidth_timer.irq, NULL);
    iounmap(bandwidth_timer.base);
    hisi_bw_timer_clk_disable();
    hisi_bw_timer_clk_put();
    bandwidth_timer.clk = NULL;
    bandwidth_timer.pclk = NULL;

    return 0;
}
EXPORT_SYMBOL(hisi_bw_timer_deinit);
