/*
 * Copyright (C) 2012-2015 HUAWEI, Inc.
 * Author: HUAWEI, Inc.
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/module.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/io.h>
#include <linux/jiffies.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>
#include <huawei_platform/log/hw_log.h>
#include <linux/notifier.h>
#include <linux/wakelock.h>
#include <linux/huawei/usb/hisi_usb.h>
#include <linux/timer.h>
#include <linux/hrtimer.h>
#include <dsm/dsm_pub.h>
#include <linux/huawei/hisi_adc.h>
#include <linux/delay.h>

#define HWLOG_TAG usb_short_circuit_protect
HWLOG_REGIST();

struct uscp_device_info
{
    struct device   *dev;
    struct workqueue_struct *uscp_wq;
    struct work_struct uscp_check_wk;
    struct notifier_block   usb_nb;
    struct hrtimer timer;
    int gpio_uscp;
    int adc_channel_uscp;
    int open_mosfet_temp;
    int close_mosfet_temp;
    int interval_switch_temp;
    int check_interval;
    int keep_check_cnt;
};

static struct dsm_dev dsm_uscp =
{
    .name = "dsm_usb_short_circuit_protect",
    .fops = NULL,
    .buff_size = 1024,
};
static int protect_enable = 0;
static int protect_dmd_notify_enable = 1;
static int T_A_TABLE[][2] =
{
  {-40, 3851},
  {-39, 3838},
  {-38, 3825},
  {-37, 3811},
  {-36, 3796},
  {-35, 3782},
  {-34, 3766},
  {-33, 3750},
  {-32, 3733},
  {-31, 3716},
  {-30, 3697},
  {-29, 3679},
  {-28, 3659},
  {-27, 3639},
  {-26, 3619},
  {-25, 3597},
  {-24, 3575},
  {-23, 3552},
  {-22, 3529},
  {-21, 3505},
  {-20, 3480},
  {-19, 3454},
  {-18, 3428},
  {-17, 3401},
  {-16, 3373},
  {-15, 3345},
  {-14, 3316},
  {-13, 3286},
  {-12, 3256},
  {-11, 3225},
  {-10, 3193},
  {-9, 3161},
  {-8, 3128},
  {-7, 3095},
  {-6, 3060},
  {-5, 3026},
  {-4, 2990},
  {-3, 2955},
  {-2, 2919},
  {-1, 2882},
  {0, 2845},
  {1, 2807},
  {2, 2769},
  {3, 2731},
  {4, 2692},
  {5, 2653},
  {6, 2614},
  {7, 2575},
  {8, 2535},
  {9, 2495},
  {10, 2455},
  {11, 2416},
  {12, 2376},
  {13, 2335},
  {14, 2295},
  {15, 2255},
  {16, 2215},
  {17, 2175},
  {18, 2135},
  {19, 2096},
  {20, 2056},
  {21, 2017},
  {22, 1977},
  {23, 1938},
  {24, 1900},
  {25, 1862},
  {26, 1824},
  {27, 1786},
  {28, 1749},
  {29, 1713},
  {30, 1676},
  {31, 1640},
  {32, 1605},
  {33, 1570},
  {34, 1535},
  {35, 1501},
  {36, 1468},
  {37, 1435},
  {38, 1402},
  {39, 1370},
  {40, 1339},
  {41, 1308},
  {42, 1277},
  {43, 1247},
  {44, 1218},
  {45, 1189},
  {46, 1161},
  {47, 1134},
  {48, 1107},
  {49, 1080},
  {50, 1054},
  {51, 1029},
  {52, 1004},
  {53, 979},
  {54, 955},
  {55, 932},
  {56, 909},
  {57, 887},
  {58, 866},
  {59, 844},
  {60, 823},
  {61, 803},
  {62, 783},
  {63, 764},
  {64, 745},
  {65, 727},
  {66, 709},
  {67, 691},
  {68, 674},
  {69, 658},
  {70, 641},
  {71, 626},
  {72, 610},
  {73, 595},
  {74, 580},
  {75, 566},
  {76, 552},
  {77, 539},
  {78, 525},
  {79, 512},
  {80, 500},
  {81, 488},
  {82, 476},
  {83, 464},
  {84, 453},
  {85, 442},
  {86, 431},
  {87, 421},
  {88, 411},
  {89, 401},
  {90, 391},
  {91, 382},
  {92, 373},
  {93, 364},
  {94, 355},
  {95, 347},
  {96, 338},
  {97, 331},
  {98, 323},
  {99, 315},
  {100, 308},
  {101, 301},
  {102, 294},
  {103, 287},
  {104, 280},
  {105, 274},
  {106, 268},
  {107, 261},
  {108, 255},
  {109, 250},
  {110, 244},
  {111, 238},
  {112, 233},
  {113, 228},
  {114, 223},
  {115, 218},
  {116, 213},
  {117, 208},
  {118, 204},
  {119, 199},
  {120, 195},
  {121, 191},
  {122, 186},
  {123, 182},
  {124, 178},
  {125, 175},
};

static struct dsm_client *uscp_client = NULL;
static struct uscp_device_info* g_di = NULL;
static struct wake_lock uscp_wakelock;

static void uscp_wake_lock(void)
{
    if(!wake_lock_active(&uscp_wakelock))
    {
        hwlog_info("wake lock\n");
        wake_lock(&uscp_wakelock);
    }
}

static void uscp_wake_unlock(void)
{
    if(wake_lock_active(&uscp_wakelock))
    {
        hwlog_info("wake unlock\n");
        wake_unlock(&uscp_wakelock);
    }
}

static void charge_type_handler(struct uscp_device_info* di, enum hisi_charger_type type)
{
    int interval;

    if (!protect_enable)
        return;
    if ((CHARGER_TYPE_DCP == type) || (CHARGER_TYPE_UNKNOWN == type))
    {
        if (hrtimer_active(&(di->timer)))
        {
            hwlog_info("timer already armed , do nothing\n");
        }
        else
        {
            uscp_wake_lock();
            hwlog_info("start uscp check\n");
            interval = 0;
            hrtimer_start(&di->timer, ktime_set(interval/MSEC_PER_SEC, (interval % MSEC_PER_SEC) * USEC_PER_SEC), HRTIMER_MODE_REL);
        }
    }
    else
    {
        hwlog_info("charger type = %d, do nothing\n", type);
    }
}

static int usb_notifier_call(struct notifier_block *usb_nb, unsigned long event, void *data)
{
    struct uscp_device_info *di = container_of(usb_nb, struct uscp_device_info, usb_nb);
    enum hisi_charger_type type = ((enum hisi_charger_type)event);

    charge_type_handler(di, type);
    return NOTIFY_OK;
}

static int get_one_adc_sample(void)
{
    int i =0;
    const int retry_times = 3;
    int T_sample = -1;
    struct uscp_device_info* di = g_di;

    for (i = 0; i < retry_times; ++i)
    {
        T_sample = hisi_adc_get_adc(di->adc_channel_uscp);
        if (T_sample < 0)
        {
            hwlog_err("adc read fail!\n");
        }
        else
        {
            break;
        }
    }
    return T_sample;
}
static int adc_to_temp(int adc_value)
{
    int table_size = sizeof(T_A_TABLE)/sizeof(T_A_TABLE[0]);
    int high = table_size - 1;
    int low = 0;
    int mid = 0;

    if (adc_value >= T_A_TABLE[0][1])
        return T_A_TABLE[0][0];
    if (adc_value <= T_A_TABLE[table_size - 1][1])
        return T_A_TABLE[table_size - 1][0];
    /*use binary search*/
    while (low < high)
    {
        hwlog_debug("low = %d,high = %d!\n", low, high);
        mid = (low + high) / 2;
        if (0 == mid)
            return T_A_TABLE[1][0];
        if (adc_value > T_A_TABLE[mid][1])
        {
            if (adc_value < T_A_TABLE[mid - 1][1])
                return T_A_TABLE[mid][0];
            high = mid - 1;
        }
        else if(adc_value < T_A_TABLE[mid][1])
        {
            if (adc_value >= T_A_TABLE[mid + 1][1])
                return T_A_TABLE[mid + 1][0];
            low = mid + 1;
        }
        else
            return T_A_TABLE[mid][0];
    }
    hwlog_err("transform error!\n");
    return 0;
}

static int get_temperature_value(void)
{
    int i;
    int cnt = 0;
    int adc_temp;
    const int sample_num = 3; // use 3 samples to get an average value
    int sum = 0;
    int temp = 0;

    for (i = 0; i < sample_num; ++i)
    {
        adc_temp = get_one_adc_sample();
        if (adc_temp >= 0)
        {
            sum += adc_temp;
            ++cnt;
        }
        else
        {
            hwlog_err(" get temperature fail!\n");
        }
    }
    if (cnt > 0)
    {
        temp = adc_to_temp(sum/cnt);
        return temp;
    }
    else
    {
        hwlog_err("use 0 as default temperature!\n");
        return 0;
    }
}
static void check_temperature(struct uscp_device_info* di)
{
    int temp;
    static int logprint_flag = 0;

    temp = get_temperature_value();
    if (temp >= di->open_mosfet_temp)
    {
        if (protect_dmd_notify_enable)
        {
            if (!dsm_client_ocuppy(uscp_client))
            {
                hwlog_info("record and notify\n");
                dsm_client_record(uscp_client, "usb short happened!\n");
                dsm_client_notify(uscp_client, ERROR_NO_USB_SHORT_PROTECT);
                protect_dmd_notify_enable = 0;
            }
        }
        gpio_set_value(di->gpio_uscp, 1);//open mosfet
        logprint_flag = 1;
        hwlog_err("pull up gpio_uscp!\n");
    }
    else if (temp < di->close_mosfet_temp)
    {
        gpio_set_value(di->gpio_uscp, 0);//close mosfet
        if (logprint_flag)
        {
            hwlog_info("pull down gpio_uscp!\n");
            logprint_flag = 0;
        }
    }
    else
    {
        //do nothing;
    }
    if (temp > di->interval_switch_temp)
    {
        hwlog_info("temp = %d\n", temp);
        di->check_interval = 300;
        di->keep_check_cnt = 0;
    }
    else
    {
        if (di->keep_check_cnt > 1000)
        {
            hwlog_info("cnt = %d!\n", di->keep_check_cnt);
            di->keep_check_cnt = -1;
            di->check_interval = 10000;
        }
        else if (di->keep_check_cnt >= 0)
        {
            hwlog_info("cnt = %d!\n", di->keep_check_cnt);
            di->keep_check_cnt = di->keep_check_cnt + 1;
            di->check_interval = 300;
        }
        else
        {
            di->check_interval = 10000;
        }
    }
}

static void uscp_check_work(struct work_struct *work)
{
    struct uscp_device_info *di = container_of(work,struct uscp_device_info, uscp_check_wk);
    int interval;
    enum hisi_charger_type type = hisi_get_charger_type();

    if ((CHARGER_TYPE_CDP == type) || (CHARGER_TYPE_SDP == type) || ((-1 == di->keep_check_cnt) && (CHARGER_TYPE_NONE == type)))
    {
        protect_dmd_notify_enable = 1;
        uscp_wake_unlock();
        gpio_set_value(di->gpio_uscp, 0);//close mosfet
        di->keep_check_cnt = -1;
        di->check_interval = 10000;
        hwlog_info("chargertype is %d,stop checking\n", type);
        return;
    }

    check_temperature(di);
    interval = di->check_interval;
    hrtimer_start(&di->timer, ktime_set(interval/MSEC_PER_SEC, (interval % MSEC_PER_SEC) * USEC_PER_SEC), HRTIMER_MODE_REL);

}

static enum hrtimer_restart uscp_timer_func(struct hrtimer *timer)
{
    struct uscp_device_info *di;

    di = container_of(timer, struct uscp_device_info, timer);
    queue_work(di->uscp_wq, &di->uscp_check_wk);
    return HRTIMER_NORESTART;
}

static void check_ntc_error(void)
{
    int temp;
    int sum = 0;
    int i;

    for (i = 0; i < 2; ++i)
    {
        sum += get_temperature_value();
    }
    temp = sum / 2;
    hwlog_info("check ntc error, temp = %d\n", temp);
    if (temp > 100 || temp < -30)
    {
        if (!dsm_client_ocuppy(uscp_client))
        {
            hwlog_info("ntc error notify\n");
            dsm_client_record(uscp_client, "ntc error happened!\n");
            dsm_client_notify(uscp_client, ERROR_NO_USB_SHORT_PROTECT_NTC);
        }
        protect_enable = 0;
    }
    else
    {
        hwlog_info("enable usb short protect\n");
        protect_enable = 1;
    }
}

static int uscp_probe(struct platform_device *pdev)
{
    struct device_node* np;
    struct uscp_device_info* di;
    enum hisi_charger_type type = hisi_get_charger_type();
    int ret = 0;

    np = pdev->dev.of_node;
    if(NULL == np)
    {
        hwlog_err("np is NULL\n");
        return -1;
    }
    di = kzalloc(sizeof(*di), GFP_KERNEL);
    if (!di)
    {
        hwlog_err("di is NULL\n");
        return -ENOMEM;

    }
    g_di = di;
    if (!uscp_client)
    {
        uscp_client = dsm_register_client(&dsm_uscp);
    }
    if (NULL == uscp_client)
    {
        hwlog_err("uscp register dsm fail\n");
        ret = -EINVAL;
        goto free_mem;
    }

    hwlog_info("table_size = %d\n", sizeof(T_A_TABLE)/sizeof(T_A_TABLE[0]));
    di->keep_check_cnt = -1;

    di->gpio_uscp = of_get_named_gpio(np, "gpio_usb_short_circuit_protect",0);
    if (!gpio_is_valid(di->gpio_uscp))
    {
        hwlog_err("gpio_uscp is not valid\n");
        ret = -EINVAL;
        goto free_mem;
    }
    hwlog_info("gpio_uscp = %d\n", di->gpio_uscp);

    ret = gpio_request(di->gpio_uscp, "usb_short_circuit_protect");
    if (ret)
    {
        hwlog_err("could not request gpio_uscp\n");
        ret = -EINVAL;
        goto free_mem;
    }
    gpio_direction_output(di->gpio_uscp, 0);

    ret = of_property_read_u32(np, "adc_channel_uscp", &(di->adc_channel_uscp));
    if (ret)
    {
        hwlog_err("get adc_channel_uscp info fail!\n");
        ret = -EINVAL;
        goto free_gpio;
    }
    hwlog_info("adc_channel_uscp = %d\n", di->adc_channel_uscp);
    ret = of_property_read_u32(np, "open_mosfet_temp", &(di->open_mosfet_temp));
    if (ret)
    {
        hwlog_err("get open_mosfet_temp info fail!\n");
        ret = -EINVAL;
        goto free_gpio;
    }
    hwlog_info("open_mosfet_temp = %d\n", di->open_mosfet_temp);
    ret = of_property_read_u32(np, "close_mosfet_temp", &(di->close_mosfet_temp));
    if (ret)
    {
        hwlog_err("get close_mosfet_temp info fail!\n");
        ret = -EINVAL;
        goto free_gpio;
    }
    hwlog_info("close_mosfet_temp = %d\n", di->close_mosfet_temp);
    ret = of_property_read_u32(np, "interval_switch_temp", &(di->interval_switch_temp));
    if (ret)
    {
        hwlog_err("get interval_switch_temp info fail!\n");
        ret = -EINVAL;
        goto free_gpio;
    }
    hwlog_info("interval_switch_temp = %d\n", di->interval_switch_temp);
    check_ntc_error();
    if (!protect_enable)
    {
        goto free_gpio;
    }
    wake_lock_init(&uscp_wakelock, WAKE_LOCK_SUSPEND, "usb_short_circuit_protect_wakelock");
    di->uscp_wq = create_singlethread_workqueue("usb_short_circuit_protect_wq");
    INIT_WORK(&di->uscp_check_wk, uscp_check_work);
    hrtimer_init(&di->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    di->timer.function = uscp_timer_func;
    di->usb_nb.notifier_call = usb_notifier_call;
    ret = hisi_charger_type_notifier_register(&di->usb_nb);
    if (ret < 0)
    {
        hwlog_err("hisi_charger_type_notifier_register failed\n");
        ret = -EINVAL;
        goto free_gpio;
    }
    charge_type_handler(di, type);
    hwlog_info("uscp probe ok!\n");
    return 0;

free_gpio:
    gpio_free(di->gpio_uscp);
free_mem:
    kfree(di);
    g_di = NULL;
    return ret;
}

static struct of_device_id uscp_match_table[] =
{
    {
        .compatible = "huawei,usb_short_circuit_protect",
        .data = NULL,
    },
    {
    },
};
static struct platform_driver uscp_driver = {
    .probe = uscp_probe,
    .driver = {
        .name = "huawei,usb_short_circuit_protect",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(uscp_match_table),
    },
};

static int __init uscp_init(void)
{
    return platform_driver_register(&uscp_driver);
}

device_initcall_sync(uscp_init);

static void __exit uscp_exit(void)
{
    platform_driver_unregister(&uscp_driver);
}

module_exit(uscp_exit);

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:uscp");
MODULE_AUTHOR("HUAWEI Inc");
