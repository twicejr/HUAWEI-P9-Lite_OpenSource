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
#include <hi6xxx_sim.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/module.h>
#include <linux/stat.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>

static struct balong_sim_plat_data* sim1_plat_data=NULL;
static struct balong_sim_plat_data* sim2_plat_data=NULL;
static struct workqueue_struct *workqueue = NULL;
static struct work_struct sim1_irq_work;
static struct work_struct sim2_irq_work;
static int g_sim1_present_electrical_lvl = HIGH_LEVEL;  /*level range 0 or 1 depends on HW of SIMCARD*/
static int g_sim2_present_electrical_lvl = HIGH_LEVEL;  /*level range 0 or 1 depends on HW of SIMCARD*/


static unsigned int get_sim_status(unsigned int sim_detection_gpio, int sim_present_electrical_lvl)
{
    int electrical_lvl;
    electrical_lvl = gpio_get_value(sim_detection_gpio);
    pr_info("get_sim_status electrical_lvl  [%d]\n", electrical_lvl);
    return (unsigned int)((electrical_lvl ^ sim_present_electrical_lvl) ? 0:1);
}

static void balong_sim1_set_status(struct work_struct *work)
{
    
    /*anti-jitter, msleep(10)*/
    msleep(SIM_DEBOUNCE_TIME);
    sim1_plat_data->sim_status = get_sim_status(sim1_plat_data->sim_detection_gpio, g_sim1_present_electrical_lvl);
    
    pr_info("balong_sim1_set_status  sim_status [%d]\n", sim1_plat_data->sim_status);
}

static void balong_sim2_set_status(struct work_struct *work)
{
    
    /*anti-jitter, msleep(10)*/
    msleep(SIM_DEBOUNCE_TIME);
    sim2_plat_data->sim_status = get_sim_status(sim2_plat_data->sim_detection_gpio, g_sim2_present_electrical_lvl);
    pr_info("balong_sim2_set_status  sim_status [%d]\n", sim2_plat_data->sim_status);
}


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

    len = sprintf(buf, "%s %d\n", sim1_plat_data->name, sim1_plat_data->sim_status);
    return len;
}

static ssize_t show_sim2_absent_stat(struct device *dev, struct device_attribute *attr, char *buf)
{
    ssize_t len;

    len = sprintf(buf, "%s %d\n", sim2_plat_data->name, sim2_plat_data->sim_status);
    return len;
}
/*SIM1: ""*/
/*SIM2: ""*/
static DEVICE_ATTR(sim1_status, S_IRUGO, show_sim1_absent_stat, NULL);
static DEVICE_ATTR(sim2_status, S_IRUGO, show_sim2_absent_stat, NULL);


static struct balong_sim_plat_data  balong_sim1_plat_data = {
    .name = SIM1,
    .sim_status = 0,
};

static struct balong_sim_plat_data  balong_sim2_plat_data = {
    .name = SIM2,
    .sim_status = 0,
};

#ifdef CONFIG_OF
static const struct of_device_id balong_sim_match[] = {
    { .compatible = "hisilicon,balong_sim1",
      .data=&balong_sim1_plat_data,
    },
    { .compatible = "hisilicon,balong_sim2",
      .data=&balong_sim2_plat_data,
    },
    {},
};

MODULE_DEVICE_TABLE(of, balong_sim_match);

#endif

static int balong_sim_probe(struct platform_device *pdev)
{
    struct balong_sim_plat_data *plat = NULL;
    const struct of_device_id *match;
    enum of_gpio_flags gpio_flags;
    int err;

    dev_dbg(&pdev->dev, "balong_sim_probe\n");

    if ((match = of_match_node(balong_sim_match, pdev->dev.of_node)) == NULL) {
        dev_err(&pdev->dev, "dev node is not match. exiting.\n");
        return -ENODEV;   
    }
    
    plat = (struct balong_sim_plat_data *)match->data;
    if (plat == NULL) {
        dev_err(&pdev->dev, "no platform data\n");
        return -EINVAL;
    }

    pr_err("balong_sim_probe, enter %s\n",plat->name);

    if (!strcmp(SIM1 , plat->name))
    {
        sim1_plat_data = plat;               
        sim1_plat_data->sim_detection_gpio = of_get_gpio_by_prop(pdev->dev.of_node,"gpio-sim1_detect,gpio-irq",0,0, &gpio_flags);

        err = of_property_read_u32(pdev->dev.of_node, "gpio_sim1_in_val", &g_sim1_present_electrical_lvl);
        if (err < 0) 
        {
            dev_err(&pdev->dev, "sim1 obtain the ele lvl failed err = %d\n",err);  
            return -EINVAL;
        }
	                 
    }
    
    if (!strcmp(SIM2 , plat->name))
    {
        sim2_plat_data = plat;
        sim2_plat_data->sim_detection_gpio = of_get_gpio_by_prop(pdev->dev.of_node,"gpio-sim2_detect,gpio-irq",0,0, &gpio_flags);

        err = of_property_read_u32(pdev->dev.of_node, "gpio_sim2_in_val", &g_sim2_present_electrical_lvl);
        if (err < 0) 
        {
            dev_err(&pdev->dev, "sim2 obtain the ele lvl failed err = %d\n",err);  
            return -EINVAL;
        }
	          
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
    /*以下代码只执行一次，SIM1和SIM2共用一个任务队列*/
    if (!workqueue) {
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
        /*request irq for sim1*/
        INIT_WORK(&sim1_irq_work, balong_sim1_set_status);
        
        err = request_irq(gpio_to_irq(sim1_plat_data->sim_detection_gpio), sim1_detection_irq_handler,
    	    IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,
    	    pdev->name, pdev);
        if (err) {
            dev_warn(&pdev->dev, "sim1:request gpio irq error\n");
            goto no_sim_detect_irq;
        }
           
        /* sysfs entries for IO control */
        err = device_create_file(&(pdev->dev), &dev_attr_sim1_status);
        if (err) {
            dev_err(&pdev->dev, "sim1:Failed to create sysfs entry\n");
            goto err_create_device_file;
        }
    }

    if (!strcmp(SIM2 , plat->name))
    {
        INIT_WORK(&sim2_irq_work, balong_sim2_set_status);

        err = request_irq(gpio_to_irq(sim2_plat_data->sim_detection_gpio), sim2_detection_irq_handler,
    	    IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,
    	    pdev->name, pdev);
        if (err) {
            dev_warn(&pdev->dev, "sim2:request gpio irq error\n");
            goto no_sim_detect_irq;
        }
        
        /* sysfs entries for IO control */
        err = device_create_file(&(pdev->dev), &dev_attr_sim2_status);
        if (err) {
            dev_err(&pdev->dev, "sim2:Failed to create sysfs entry\n");
            goto err_create_device_file;
        }
    }
    return 0;

err_create_device_file:
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
    const struct of_device_id *match;

    dev_dbg(&pdev->dev, "balong_sim_remove\n");

    if ((match = of_match_node(balong_sim_match, pdev->dev.of_node)) == NULL) {
        dev_err(&pdev->dev, "dev node is not match. exiting.\n");
        return -ENODEV;   
    }

    plat = (struct balong_sim_plat_data *)match->data;
    if (plat == NULL) {
        dev_err(&pdev->dev, "no platform data\n");
        return -EINVAL;
    }

    
    if (!strcmp(SIM1 , plat->name))
    {
        free_irq(gpio_to_irq(sim1_plat_data->sim_detection_gpio), sim1_detection_irq_handler);
        device_remove_file(&(pdev->dev), &dev_attr_sim1_status);
    }

    if (!strcmp(SIM2 , plat->name))
    {
        free_irq(gpio_to_irq(sim2_plat_data->sim_detection_gpio), sim2_detection_irq_handler);
        device_remove_file(&(pdev->dev), &dev_attr_sim2_status);
    }

    if(workqueue)
    {
        destroy_workqueue(workqueue);
    }
    return 0;
}

static struct platform_driver balong_sim_driver = {
    .probe = balong_sim_probe,
    .remove = balong_sim_remove,
    .driver = {
        .name ="balong_sim",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(balong_sim_match),   
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
