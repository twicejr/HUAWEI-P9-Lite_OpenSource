/*
 * arch/arm/mach-hi6620/balong_sim.c
 *
 * Copyright (C) 2011 Hisilicon Co. Ltd.
 *
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <linux/workqueue.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/kernel.h> /* string operation */
#include <linux/gpio.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <mach/balong_sim.h>
#include <mach/platform.h>
#include <reg_ops.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <mach/pmussi_drv.h>
#include "soc_smart_interface.h"
#include <hsad/config_mgr.h>

static struct balong_sim_plat_data* sim1_plat_data=NULL;
static struct balong_sim_plat_data* sim2_plat_data=NULL;
static struct workqueue_struct *workqueue = NULL;
static struct work_struct sim1_irq_work;
static struct work_struct sim2_irq_work;
static int g_sim1_present_electrical_lvl = HIGH_LEVEL;  /*level range 0 or 1 depends on HW of SIMCARD*/
static int g_sim2_present_electrical_lvl = HIGH_LEVEL;  /*level range 0 or 1 depends on HW of SIMCARD*/

unsigned int get_sim_status(unsigned int sim_detection_gpio, int sim_present_electrical_lvl)
{
    int electrical_lvl;
    electrical_lvl = gpio_get_value(sim_detection_gpio);
    pr_info("get_sim_status electrical_lvl  [%d]\n", electrical_lvl);
    return ((electrical_lvl ^ sim_present_electrical_lvl) ? 0:1);
}

void set_sim_en_int(char *sim_name, unsigned int sim_status)
{
#if 0 /* Acore不控制sim的电源开关操作,全部放到Ccore */
    SOC_SMART_SIMCARD_EN_UNION simcard_en;
    unsigned int reg_addr = SOC_SMART_SIMCARD_EN_ADDR(0);

    simcard_en = (SOC_SMART_SIMCARD_EN_UNION)pmussi_reg_read(reg_addr);
    pr_info("set_sim_en_int RO simcard_en [%d] , sim_status [%d]\n", simcard_en, sim_status);
    if (!strcmp(SIM1 , sim_name))
    {
        if(sim_status)
        {
            simcard_en.reg.en_ldo9_int = 1;
            simcard_en.reg.sim0_en_int = 1;
        }
        else
        {
            simcard_en.reg.en_ldo9_int = 0;
            simcard_en.reg.sim0_en_int = 0;
        }
    }
    
    if (!strcmp(SIM2 , sim_name))
    {
        if(sim_status)
        {
            simcard_en.reg.en_ldo11_int = 1;
            simcard_en.reg.sim1_en_int = 1;
        }
        else
        {
            simcard_en.reg.en_ldo11_int = 0;
            simcard_en.reg.sim1_en_int = 0;
        }
    }

    pmussi_reg_write (reg_addr, simcard_en.value);
    pr_info("set_sim_en_int W simcard_en [%d]\n", simcard_en);
#endif
}

void balong_sim1_set_status(void)
{
    
    /*anti-jitter, msleep(10)*/
    msleep(SIM_DEBOUNCE_TIME);
    sim1_plat_data->sim_status = get_sim_status(sim1_plat_data->sim_detection_gpio, g_sim1_present_electrical_lvl);
    pr_info("balong_sim1_set_status  sim_status [%d]\n", sim1_plat_data->sim_status);
#ifndef SIM_HPD
    set_sim_en_int(sim1_plat_data->name, sim1_plat_data->sim_status);
#endif
}

void balong_sim2_set_status(void)
{
    
    /*anti-jitter, msleep(10)*/
    msleep(SIM_DEBOUNCE_TIME);
    sim2_plat_data->sim_status = get_sim_status(sim2_plat_data->sim_detection_gpio, g_sim2_present_electrical_lvl);
    pr_info("balong_sim2_set_status  sim_status [%d]\n", sim2_plat_data->sim_status);
#ifndef SIM_HPD
    set_sim_en_int(sim2_plat_data->name, sim2_plat_data->sim_status);
#endif
}

#ifdef SIM_HPD
static irqreturn_t sim1_hpd_out_irq_handler(int irq, void *data)
{
    pr_info("sim1_hpd_out_irq_handler  %d\n",irq);
    return IRQ_HANDLED;
}

static irqreturn_t sim1_hpd_in_irq_handler(int irq, void *data)
{
    pr_info("sim1_hpd_in_irq_handler %d \n",irq);
    return IRQ_HANDLED;
}

static irqreturn_t sim2_hpd_out_irq_handler(int irq, void *data)
{
    pr_info("sim2_hpd_out_irq_handler %d \n", irq);
    return IRQ_HANDLED;
}

static irqreturn_t sim2_hpd_in_irq_handler(int irq, void *data)
{
    pr_info("sim2_hpd_in_irq_handler  %d\n", irq);
    return IRQ_HANDLED;
}
#endif

static irqreturn_t sim1_detection_irq_handler(int irq, void *data)
{
    queue_work(workqueue, &sim1_irq_work);
    return IRQ_HANDLED;
}

static irqreturn_t sim2_detection_irq_handler(int irq, void *data)
{
    queue_work(workqueue, &sim2_irq_work);
    return IRQ_HANDLED;
}

static ssize_t show_sim1_absent_stat(struct device *dev, struct device_attribute *attr, char *buf)
{
    ssize_t len;
    unsigned long flags;

    len = sprintf(buf, "%s %d\n", sim1_plat_data->name, sim1_plat_data->sim_status);
    return len;
}

static ssize_t show_sim2_absent_stat(struct device *dev, struct device_attribute *attr, char *buf)
{
    ssize_t len;
    unsigned long flags;

    len = sprintf(buf, "%s %d\n", sim2_plat_data->name, sim2_plat_data->sim_status);
    return len;
}
/*SIM1: "/sys/devices/platform/balong_sim.1/sim1_status"*/
/*SIM2: "/sys/devices/platform/balong_sim.2/sim2_status"*/
static DEVICE_ATTR(sim1_status, S_IRUGO, show_sim1_absent_stat, NULL);
static DEVICE_ATTR(sim2_status, S_IRUGO, show_sim2_absent_stat, NULL);

static int balong_sim_probe(struct platform_device *pdev)
{
    struct balong_sim_plat_data *plat = NULL;
    int err;

    dev_dbg(&pdev->dev, "balong_sim_probe\n");

    plat = pdev->dev.platform_data;

    if (!strcmp(SIM1 , plat->name))
    {
        sim1_plat_data = pdev->dev.platform_data;
        if (!get_hw_config_int("sim/sim1_detection_gpio", &(sim1_plat_data->sim_detection_gpio), NULL))
        {
            pr_err("Get sim/sim1_detection_gpio failed\n");
            return -EINVAL;
        }
        
        if (!get_hw_config_int("sim/sim1_present_electrical_lvl", &(g_sim1_present_electrical_lvl), NULL))
        {
            pr_err("Get sim/sim1_detection_gpio failed\n");
            return -EINVAL;
        }
        pr_info("balong_sim_probe SIM1 dev name [%s], sim1_detection_gpio [%d], sim1_present_electrical_lvl [%d]\n", 
                    plat->name, sim1_plat_data->sim_detection_gpio, g_sim1_present_electrical_lvl);
    }

    if (!strcmp(SIM2 , plat->name))
    {
        sim2_plat_data = pdev->dev.platform_data;
        if (!get_hw_config_int("sim/sim2_detection_gpio", &(sim2_plat_data->sim_detection_gpio), NULL))
        {
            pr_err("Get sim/sim2_detection_gpio failed\n");
            return -EINVAL;
        }

        if (!get_hw_config_int("sim/sim2_present_electrical_lvl", &(g_sim2_present_electrical_lvl), NULL))
        {
            pr_err("Get sim/sim2_detection_gpio failed\n");
            return -EINVAL;
        }
        pr_info("balong_sim_probe SIM2 dev name [%s], sim2_detection_gpio [%d], sim2_present_electrical_lvl [%d]\n", 
                    plat->name, sim2_plat_data->sim_detection_gpio, g_sim2_present_electrical_lvl);
    }

    err = gpio_request_one(plat->sim_detection_gpio, GPIOF_IN, plat->name);
    if (err) {
        dev_warn(&pdev->dev, "no sim-detect pin available!\n");
        return err;
    }

    /*Initialize sim status when booting*/
    if (!strcmp(SIM1 , plat->name))
    {
        plat->sim_status = get_sim_status(plat->sim_detection_gpio, g_sim1_present_electrical_lvl);
    }

    if (!strcmp(SIM2 , plat->name))
    {
        plat->sim_status = get_sim_status(plat->sim_detection_gpio, g_sim2_present_electrical_lvl);
    }

    pr_info("balong_sim_probe sim_status [%d]\n", plat->sim_status);

    /*Temp: set sim_en_int of register SIMCARD_EN*/
    /*TODO:需要找到软件哪里设置了sim_en_int位*/
    set_sim_en_int(plat->name, plat->sim_status);

    /*以下代码只执行一次，SIM1和SIM2共用一个任务队列*/
    if (!workqueue)
    {
        /* Initialize works */
        workqueue = create_singlethread_workqueue("balong_sim_workqueue");
        if (!workqueue) {
            dev_err(&pdev->dev, "Create workqueue failed\n");
            err = -1;
            goto err_init_workqueue;
        }
        else
        {
            pr_info("balong_sim_probe, Initialization of workqueue succeed\n");
        }
    }
    
    /*request SIM irq*/
    if (!strcmp(SIM1 , plat->name))
    {
        INIT_WORK(&sim1_irq_work, balong_sim1_set_status);

        err = request_irq(gpio_to_irq(plat->sim_detection_gpio), sim1_detection_irq_handler,
    	    IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,
    	    pdev->name, pdev);
        if (err) {
            dev_warn(&pdev->dev, "request gpio irq error\n");
            goto no_sim_detect_irq;
        }

#ifdef SIM_HPD
        pr_info(" SIM1 sim_hpd_out_f [%d]\n", plat->sim_hpd_out_f);
        pr_info(" SIM1 sim_hpd_in_f [%d]\n", plat->sim_hpd_in_f);
        /*SIM HPD out irq request*/
        err = request_irq(plat->sim_hpd_out_f, sim1_hpd_out_irq_handler,
    	    IRQF_TRIGGER_FALLING| IRQF_TRIGGER_RISING, pdev->name, pdev);
        if (err) {
            dev_warn(&pdev->dev, "request sim_hpd_out_f irq error\n");
            goto no_sim_hpd_out_irq;
        }

        /*SIM HPD in irq request*/
        err = request_irq(plat->sim_hpd_in_f, sim1_hpd_in_irq_handler,
    	    IRQF_TRIGGER_FALLING| IRQF_TRIGGER_RISING, pdev->name, pdev);
        if (err) {
            dev_warn(&pdev->dev, "request sim_hpd_in_f irq error\n");
            goto no_sim_hpd_in_irq;
        }
#endif
            
        /* sysfs entries for IO control */
        err = device_create_file(&(pdev->dev), &dev_attr_sim1_status);
        if (err) {
            dev_err(&pdev->dev, "Failed to create sysfs entry\n");
            goto err_create_device_file;
        }
    }

    if (!strcmp(SIM2 , plat->name))
    {
        INIT_WORK(&sim2_irq_work, balong_sim2_set_status);

        err = request_irq(gpio_to_irq(plat->sim_detection_gpio), sim2_detection_irq_handler,
    	    IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,
    	    pdev->name, pdev);
        if (err) {
            dev_warn(&pdev->dev, "request gpio irq error\n");
            goto no_sim_detect_irq;
        }

#ifdef SIM_HPD
        pr_info(" SIM2 sim_hpd_out_f [%d]\n", plat->sim_hpd_out_f);
        pr_info(" SIM2 sim_hpd_in_f [%d]\n", plat->sim_hpd_in_f);
        /*SIM HPD out irq request*/
        err = request_irq(plat->sim_hpd_out_f, sim2_hpd_out_irq_handler,
    	    IRQF_TRIGGER_FALLING| IRQF_TRIGGER_RISING, pdev->name, pdev);
        if (err) {
            dev_warn(&pdev->dev, "request sim_hpd_out_f irq error\n");
            goto no_sim_hpd_out_irq;
        }

        /*SIM HPD in irq request*/
        err = request_irq(plat->sim_hpd_in_f, sim2_hpd_in_irq_handler,
    	    IRQF_TRIGGER_FALLING| IRQF_TRIGGER_RISING, pdev->name, pdev);
        if (err) {
            dev_warn(&pdev->dev, "request sim_hpd_in_f irq error\n");
            goto no_sim_hpd_in_irq;
        }
#endif
        
        /* sysfs entries for IO control */
        err = device_create_file(&(pdev->dev), &dev_attr_sim2_status);
        if (err) {
            dev_err(&pdev->dev, "Failed to create sysfs entry\n");
            goto err_create_device_file;
        }
    }
    return 0;
    
err_create_device_file:
#ifdef SIM_HPD
    if (!strcmp(SIM1 , plat->name)) free_irq(plat->sim_hpd_in_f, sim1_hpd_in_irq_handler);
    if (!strcmp(SIM2 , plat->name)) free_irq(plat->sim_hpd_in_f, sim2_hpd_in_irq_handler);
#endif
no_sim_hpd_in_irq:
#ifdef SIM_HPD
    if (!strcmp(SIM1 , plat->name)) free_irq(plat->sim_hpd_out_f, sim1_hpd_out_irq_handler);
    if (!strcmp(SIM2 , plat->name)) free_irq(plat->sim_hpd_out_f, sim2_hpd_out_irq_handler);
#endif
no_sim_hpd_out_irq:
    if (!strcmp(SIM1 , plat->name)) free_irq(gpio_to_irq(plat->sim_detection_gpio), sim1_detection_irq_handler);
    if (!strcmp(SIM2 , plat->name)) free_irq(gpio_to_irq(plat->sim_detection_gpio), sim2_detection_irq_handler);
no_sim_detect_irq:
    destroy_workqueue(workqueue);
    workqueue = NULL;
err_init_workqueue:
    gpio_free(plat->sim_detection_gpio);
    return err;
}

static int balong_sim_remove(struct platform_device *pdev)
{
    struct balong_sim_plat_data *plat = NULL; 
    plat = pdev->dev.platform_data;
    
    dev_dbg(&pdev->dev, "balong_sim_remove\n");
    if (!strcmp(SIM1 , plat->name)) 
    {
        free_irq(gpio_to_irq(plat->sim_detection_gpio), sim1_detection_irq_handler);
#ifdef SIM_HPD
        free_irq(plat->sim_hpd_out_f, sim1_hpd_out_irq_handler);
        free_irq(plat->sim_hpd_in_f, sim1_hpd_in_irq_handler);
#endif
        device_remove_file(&(pdev->dev), &dev_attr_sim1_status);
    }
    if (!strcmp(SIM2 , plat->name))
    {
        free_irq(gpio_to_irq(plat->sim_detection_gpio), sim2_detection_irq_handler);
#ifdef SIM_HPD
        free_irq(plat->sim_hpd_out_f, sim2_hpd_out_irq_handler);
        free_irq(plat->sim_hpd_in_f, sim2_hpd_in_irq_handler);
#endif
        device_remove_file(&(pdev->dev), &dev_attr_sim2_status);
    }
    destroy_workqueue(workqueue);
    return 0;
}

static struct platform_driver balong_sim_driver = {
    .probe = balong_sim_probe,
    .remove = balong_sim_remove,
    .driver = {
        .name ="balong_sim",
        .owner = THIS_MODULE,
    },
};

static int __init balong_sim_init(void)
{
    return platform_driver_register(&balong_sim_driver);
}

static void __exit balong_sim_exit(void)
{
    platform_driver_unregister(&balong_sim_driver);
}

module_init(balong_sim_init);
module_exit(balong_sim_exit);
MODULE_DESCRIPTION("Balong Sim Driver");
MODULE_LICENSE("GPL");
