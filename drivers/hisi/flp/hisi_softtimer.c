/*
 * hisi softtime driver.
 *
 * Copyright (C) 2015 huawei Ltd.
 * Author:lijiangxiong <lijingxiong@huawei.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/module.h>
#include <linux/types.h>
#include <linux/semaphore.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/pm.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include "hisi_softtimer.h"

#define HISI_SOFTTIME_TIMER_BASE            0xfff1c000
#define HISI_SOFTTIME_IRQ                   (97)
#define HISI_SOFTTIME_FREQ                  (32*1024)
#define SOFTTIMER_MAX_LENGTH                (0xFFFFFFFF>>15)
#define ELAPESD_TIME_INVAILD                0xFFFFFFFF
#define TIMER_INIT_FLAG                     0X5A5A5A5A

#define TIMERLOAD(n)                        ((n) << 5)
#define TIMERVALUE(n)                       (((n) << 5) + 0x04)
#define TIMERCTRL(n)                        (((n) << 5) + 0x08)
#define TIMERINTCLR(n)                      (((n) << 5) + 0x0C)
#define TIMERRIS(n)                         (((n) << 5) + 0x10)
#define TIMERMIS(n)                         (((n) << 5) + 0x14)
#define TIMERBGLOAD(n)                      (((n) << 5) + 0x18)

#define TIMER_EN_ACK                        (1<<4)
#define TIMER_INT_MASK                      (1<<2)
#define TIMER_MODE_PERIOD                   (1<<1)
#define HARD_TIMER_ENABLE                   1
#define HARD_TIMER_DISABLE                  0
#define TIMER_ONCE_COUNT                    0
#define TIMER_PERIOD_COUNT                  1
#ifndef TIMER_TRUE
#define TIMER_TRUE                          1
#endif
#ifndef TIMER_FALSE
#define TIMER_FALSE                         0
#endif

struct softtimer_ctrl {
    struct list_head        timer_list_head;
    unsigned int            softtimer_start_value;
    unsigned int            irqnum;
    void __iomem            *hard_timer_addr;
    struct semaphore        soft_timer_sem;
    spinlock_t              soft_timer_lock;
    struct tasklet_struct   softtimer_tasklet;
    unsigned int            rate;
    unsigned int            init_flag;
    struct clk              *clk;
    unsigned int            clk_is_enable;
};

static struct softtimer_ctrl timer_control;

static __inline__ unsigned int  timer_get_value(void)
{
    unsigned int ret = 0;

    ret = readl(timer_control.hard_timer_addr + TIMERCTRL(0));
    if (ret&0x80) {
        ret = readl(timer_control.hard_timer_addr + TIMERVALUE(0));
        if (ret > timer_control.softtimer_start_value)
            return timer_control.softtimer_start_value;
        else
            return ret;
    }  else {
        return 0;
    }
}
static void start_hard_timer(unsigned int ulvalue)
{
    unsigned int ret = 0;
    printk(KERN_INFO "softtimer:start_hard_timer enter [%d] \n", ulvalue);
    timer_control.softtimer_start_value = ulvalue;
    ret = readl(timer_control.hard_timer_addr + TIMERCTRL(0));
    writel(ret&(~0x80), timer_control.hard_timer_addr+TIMERCTRL(0));
    writel(ulvalue, timer_control.hard_timer_addr + TIMERLOAD(0));
    ret = readl(timer_control.hard_timer_addr+TIMERCTRL(0));
    writel(ret | 0xA2, timer_control.hard_timer_addr + TIMERCTRL(0));
}
static void stop_hard_timer(void)
{
    unsigned int ret = 0;
    ret = readl(timer_control.hard_timer_addr+TIMERCTRL(0));
    writel(ret&(~0x80), timer_control.hard_timer_addr+TIMERCTRL(0));
    timer_control.softtimer_start_value = ELAPESD_TIME_INVAILD;
}

static unsigned int hard_timer_elapsed_time(void)
{
    unsigned int ulTempValue = 0;
    if (ELAPESD_TIME_INVAILD == timer_control.softtimer_start_value) {
        return 0;
    }
    ulTempValue = timer_get_value();
    return ((timer_control.softtimer_start_value < ulTempValue) ? 0 :
            (timer_control.softtimer_start_value - ulTempValue+1));
}

void hisi_softtimer_add(struct softtimer_list *timer)
{
    unsigned int elapsed_time = hard_timer_elapsed_time();
    struct softtimer_list *p = NULL;

    if ((NULL == timer) || (timer_control.init_flag != TIMER_TRUE))  {
        return ;
    }
    spin_lock_bh(&timer_control.soft_timer_lock);
    /*if timer is added previous*/
    if (!list_empty(&timer->entry))    {
        spin_unlock_bh(&timer_control.soft_timer_lock);
        return ;
    }
    printk(KERN_INFO "softtimer:%s ENTER [%d][0x%x]\n", __func__, timer->timeout, elapsed_time);
    timer->timeout = timer->count_num;
    /*if timer list is empty*/
    if (list_empty(&(timer_control.timer_list_head)))    {
        list_add_tail(&(timer->entry), &(timer_control.timer_list_head));
    }    else     {
        /*if not empty , added to timer list by timeout value*/
        timer->timeout += elapsed_time;
        p = list_first_entry(&(timer_control.timer_list_head), struct softtimer_list, entry);
        if ((TIMER_TRUE == p->is_running) && (0 == elapsed_time))    {
            timer->timeout += p->timeout;
        }
        if (elapsed_time != 0)   {
            timer->timeout -= 1;
            elapsed_time     -= 1;
        }
        list_for_each_entry(p, &(timer_control.timer_list_head), entry)  {
            if (p->timeout <= timer->timeout)     {
                timer->timeout -= p->timeout;
            }  else   {
                break;
            }
        }
        if (&(p->entry) != &(timer_control.timer_list_head))  {
            p->timeout -= timer->timeout;
        }
        list_add_tail(&(timer->entry), &(p->entry));
    }
    /*if the timer is first at list*/
    if (timer_control.timer_list_head.next == &(timer->entry))    {
        if ((timer->entry.next) != (&(timer_control.timer_list_head))) {
            p = list_entry(timer->entry.next, struct softtimer_list, entry);
            if (TIMER_TRUE == p->is_running) {
                p->is_running = TIMER_FALSE;
            }
        }
        timer->is_running = TIMER_TRUE;
        start_hard_timer(timer->timeout);
    }
    spin_unlock_bh(&timer_control.soft_timer_lock);
}
int hisi_softtimer_delete(struct softtimer_list *timer)
{
    struct softtimer_list *p = NULL;
    if (NULL == timer)    {
        return  -EIO;
    }
    spin_lock_bh(&timer_control.soft_timer_lock);
    if (list_empty(&timer->entry))    {
        spin_unlock_bh(&timer_control.soft_timer_lock);
        return 0;
    }    else    {
        /*if the last one,just delete it*/
        if (timer->entry.next == &(timer_control.timer_list_head))        {
            timer->is_running = TIMER_FALSE;
            list_del_init(&(timer->entry));
        }   else if ((timer->entry.prev == &(timer_control.timer_list_head))
                && (timer->entry.next != &(timer_control.timer_list_head))) {
            /*if it is the first one,and timer list have other node*/
            timer->is_running = TIMER_FALSE;
            list_del_init(&(timer->entry));
            p = list_first_entry(&(timer_control.timer_list_head),
                           struct softtimer_list, entry);
            p->timeout += timer->timeout - hard_timer_elapsed_time();
            start_hard_timer(p->timeout);
            p->is_running = TIMER_TRUE;
        }	else          {
            /*if it is middle node*/
            p = list_entry(timer->entry.next, struct softtimer_list, entry);
            p->timeout += timer->timeout;
            timer->is_running = TIMER_FALSE;
            list_del_init(&(timer->entry));
        }
    }
    /*if timer list is empty after delete node*/
    if (list_empty(&(timer_control.timer_list_head)))     {
        stop_hard_timer();
    }
    spin_unlock_bh(&timer_control.soft_timer_lock);
    return 0;
}

int hisi_softtimer_create(struct softtimer_list *sft_info, softtimer_func func,
       unsigned long para, unsigned int timeout)
{
    unsigned long delaytime;
    INIT_LIST_HEAD(&(sft_info->entry));
    sft_info->is_running = TIMER_FALSE;
    sft_info->init_flags = TIMER_INIT_FLAG;
    sft_info->func = func ;
    sft_info->para = para ;
    /*CHECK INPUT PARAMETER*/
    if (timeout > SOFTTIMER_MAX_LENGTH*1000)    {
        printk(KERN_ERR "softtimer:timeout err\n");  /* [false alarm]:fortify */
        return -EIO;
    }
    delaytime = (timer_control.rate  * (unsigned long)timeout)/1000;
    sft_info->timeout = (unsigned int)delaytime;
    sft_info->count_num = sft_info->timeout;
    return 0;
}

int hisi_softtimer_modify(struct softtimer_list *timer, unsigned int new_expire_time)
{
    unsigned long delaytime;
    if ((NULL == timer) || (!list_empty(&timer->entry)))    {
        return -EIO;
    }
    if (new_expire_time > SOFTTIMER_MAX_LENGTH*1000)    {
        printk(KERN_ERR "softtimer:timeout err\n");  /* [false alarm]:fortify */
        return -EIO;
    }
    delaytime = (timer_control.rate * (unsigned long)new_expire_time)/1000;
    timer->timeout = (unsigned int)delaytime;
    timer->count_num = timer->timeout;
    return 0;
}

int hisi_softtimer_free(struct softtimer_list *p)
{
    if ((NULL == p) || (!list_empty(&p->entry)))	{
        return -EIO;
    }
    p->init_flags = 0;
    return 0;
}
static void thread_softtimer_fun(unsigned long arg)
{
    struct softtimer_list     *p = NULL;
    softtimer_func func = NULL;
    unsigned long para = 0;

    printk(KERN_INFO "softtimer:thread_softtimer_fun\n");
    spin_lock(&timer_control.soft_timer_lock);

    timer_control.softtimer_start_value = ELAPESD_TIME_INVAILD;
    if (!list_empty(&(timer_control.timer_list_head)))    {
        p = list_first_entry(&(timer_control.timer_list_head), struct softtimer_list, entry);
        if (p->is_running == TIMER_TRUE)        {
            list_del_init(&p->entry);
            p->is_running = TIMER_FALSE;
            func = p->func;
            para = p->para;
            spin_unlock(&timer_control.soft_timer_lock);
            func(para);
            spin_lock(&timer_control.soft_timer_lock);

            while (!list_empty(&(timer_control.timer_list_head)))     {
                p = list_first_entry(&(timer_control.timer_list_head), struct softtimer_list, entry);
                if (0 == p->timeout)     {
                    list_del_init(&p->entry);
                    p->is_running = TIMER_FALSE;
                    func = p->func;
                    para = p->para;
                    spin_unlock(&timer_control.soft_timer_lock);
                    func(para);
                    spin_lock(&timer_control.soft_timer_lock);

                }   else  {
                    break;
                }
            }
            /*if have other node*/
            if (!list_empty(&(timer_control.timer_list_head)))        {
                p = list_first_entry(&(timer_control.timer_list_head),
                                struct softtimer_list, entry);
                p->is_running = TIMER_TRUE;
                start_hard_timer(p->timeout);
            }    else   {
                stop_hard_timer();
            }
        }  else  if (p->is_running == TIMER_FALSE)  {
            p->is_running = TIMER_TRUE;
            start_hard_timer(p->timeout);
        }
    }  else {
        stop_hard_timer();
    }
    spin_unlock(&timer_control.soft_timer_lock) ;
}

static irqreturn_t IntTimerHandler (int irq, void *dev_id)
{
    unsigned int readValue = 0;

    readValue = readl(timer_control.hard_timer_addr+TIMERMIS(0));
    printk(KERN_INFO "softtimer:IntTimerHandler %d\n", readValue);

    if (0 != readValue)    {
        writel(0x1, timer_control.hard_timer_addr + TIMERINTCLR(0));
        tasklet_schedule(&timer_control.softtimer_tasklet);
    }
    return IRQ_HANDLED;
}

void hisi_softtimer_uninit(void)
{
    free_irq(timer_control.irqnum, NULL);
    if (timer_control.clk_is_enable) {
        clk_disable_unprepare(timer_control.clk);
        timer_control.clk_is_enable = TIMER_FALSE;
    }
    if (timer_control.hard_timer_addr) {
        iounmap(timer_control.hard_timer_addr);
    }
    return ;
}
EXPORT_SYMBOL_GPL(hisi_softtimer_uninit);

int hisi_softtimer_init (struct platform_device *pdev)
{
    unsigned int ret = 0;
    struct device_node *node = pdev->dev.of_node;
    timer_control.irqnum = irq_of_parse_and_map(node, 0);
    timer_control.clk = devm_clk_get(&pdev->dev, NULL);
    if (IS_ERR(timer_control.clk)) {
        printk(KERN_ERR "softtimer: devm_clk_get ERROR\n");
        return PTR_ERR(timer_control.clk);
    }
    ret = clk_prepare_enable(timer_control.clk);
    if (ret) {
        printk(KERN_ERR "softtimer:clk_prepare_enable error\n");
        return ret;
    }
    timer_control.clk_is_enable = TIMER_TRUE;
    timer_control.hard_timer_addr = of_iomap(node, 0);
    if (!timer_control.hard_timer_addr) {
        printk(KERN_ERR "softtimer:hisi_softtimer_init ERROR\n");
        return -ENOMEM ;
    }
    INIT_LIST_HEAD(&(timer_control.timer_list_head));
    timer_control.rate                    = HISI_SOFTTIME_FREQ;
    timer_control.softtimer_start_value  = ELAPESD_TIME_INVAILD;

    /*in default state ,clk is opened*/
    spin_lock_init(&timer_control.soft_timer_lock);
    tasklet_init(&timer_control.softtimer_tasklet, thread_softtimer_fun, 0);
    ret = request_irq(timer_control.irqnum, IntTimerHandler, IRQF_DISABLED | IRQF_TIMER,
                    "softtimer", NULL);
    if (ret) {
        goto error;
    }
    timer_control.init_flag = TIMER_TRUE;
    printk(KERN_ERR "softtimer:hisi_softtimer_init enter,%d\n", timer_control.rate);
    return 0;
error:
    hisi_softtimer_uninit();
    return ret;
}
EXPORT_SYMBOL_GPL(hisi_softtimer_init);

static void hisi_softtimer_timeout(unsigned long data)
{
    printk(KERN_INFO "hisi_softtimer_timeout\n");
    return ;
}

struct softtimer_list timer = {0};
void hisi_softtimer_test(int timeout)
{
    static int  flag;
    if (0 == flag)    {
        hisi_softtimer_create(&timer , hisi_softtimer_timeout , 0, 0);
        flag = 1;
    }
    printk(KERN_INFO "hisi_softtimer_test enter\n");
    hisi_softtimer_delete(&timer);
    hisi_softtimer_modify(&timer, timeout);
    hisi_softtimer_add(&timer);
}

int hisi_softtimer_suspend(struct platform_device *dev, pm_message_t state)
{
    printk(KERN_ERR "%s %d:\n", __func__, __LINE__);

    return 0;
}
EXPORT_SYMBOL_GPL(hisi_softtimer_suspend);

int hisi_softtimer_resume(struct platform_device *dev)
{
    printk(KERN_ERR "%s %d:\n", __func__, __LINE__);

    return 0;
}
EXPORT_SYMBOL_GPL(hisi_softtimer_resume);

MODULE_AUTHOR(" hisi<hisi@huawei.com>");
MODULE_DESCRIPTION("Generic huawei softtimer driver ");
MODULE_LICENSE("GPL");

