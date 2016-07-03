
#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/jiffies.h>
#include <linux/wakelock.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/notifier.h>
#include <linux/mutex.h>
#include <huawei_platform/log/hw_log.h>

#include "huawei_platform/audio/anc_hs_interface.h"

struct anc_hs_ops *g_anc_ops = NULL;

int anc_hs_interface_dev_register(struct anc_hs_dev *dev, void * codec_data)
{
    if(NULL == g_anc_ops || NULL == g_anc_ops->anc_hs_dev_register)
        return 0;
    return g_anc_ops->anc_hs_dev_register(dev, codec_data);
}
int anc_hs_interface_check_headset_pluged_in(void)
{
    if(NULL == g_anc_ops || NULL == g_anc_ops->anc_hs_check_headset_pluged_in)
        return NO_MAX14744;
    if(g_anc_ops->anc_hs_check_headset_pluged_in())
        return HANDSET_PLUG_IN;
    else
        return HANDSET_PLUG_OUT;
}
void anc_hs_interface_start_charge(void)
{
    if(NULL == g_anc_ops || NULL == g_anc_ops->anc_hs_start_charge)
        return;
    g_anc_ops->anc_hs_start_charge();
}
void anc_hs_interface_charge_detect(int saradc_value, int headset_type)
{
    if(NULL == g_anc_ops || NULL == g_anc_ops->anc_hs_charge_detect)
        return;
    g_anc_ops->anc_hs_charge_detect(saradc_value, headset_type);
}
void anc_hs_interface_stop_charge(void)
{
    if(NULL == g_anc_ops || NULL == g_anc_ops->anc_hs_stop_charge)
        return;
    g_anc_ops->anc_hs_stop_charge();
}
void anc_hs_interface_force_charge(int disable)
{
    if(NULL == g_anc_ops || NULL == g_anc_ops->anc_hs_force_charge)
        return;
    g_anc_ops->anc_hs_force_charge(disable);
}
bool check_anc_hs_interface_support(void)
{
    if(NULL == g_anc_ops || NULL == g_anc_ops->check_anc_hs_support)
        return false;
    return g_anc_ops->check_anc_hs_support();
}
void anc_hs_interface_5v_control(int enable)
{
    if(NULL == g_anc_ops || NULL == g_anc_ops->anc_hs_5v_control)
        return;
    g_anc_ops->anc_hs_5v_control(enable);
}

bool anc_hs_interface_plug_enable(void)
{
    if(NULL == g_anc_ops || NULL == g_anc_ops->anc_hs_plug_enable)
        return false;
    return g_anc_ops->anc_hs_plug_enable();
}

void anc_hs_interface_invert_hs_control(int connect)
{
    if(NULL == g_anc_ops || NULL == g_anc_ops->anc_hs_invert_hs_control)
        return;
    g_anc_ops->anc_hs_invert_hs_control(connect);
}

void anc_hs_interface_refresh_headset_type(int headset_type)
{
    if(NULL == g_anc_ops || NULL == g_anc_ops->anc_hs_refresh_headset_type)
        return;
    g_anc_ops->anc_hs_refresh_headset_type(headset_type);
}

/**********************************************************
*  Function:       anc_hs_ops_register
*  Discription:    register the handler ops for anc_hs
*  Parameters:   ops:operations interface of anc_hs device
*  return value:  0-sucess or others-fail
**********************************************************/
int anc_hs_ops_register(struct anc_hs_ops *ops)
{
    int ret = 0;

    if(ops != NULL)
    {
        g_anc_ops = ops;
    }
    else
    {
        pr_err("anc_hs interface ops register fail!\n");
        ret = -EPERM;
    }
    return ret;
}

/**********************************************************
*  Function:       anc_hs_interface_probe
*  Discription:    anc_hs_interface module probe
*  Parameters:   pdev:platform_device
*  return value:  0-sucess or others-fail
**********************************************************/
static int anc_hs_interface_probe(struct platform_device *pdev)
{
    return 0;
}

/**********************************************************
*  Function:       anc_hs_interface_remove
*  Discription:    anc_hs_interface module remove
*  Parameters:   pdev:platform_device
*  return value:  0-sucess or others-fail
**********************************************************/
static int anc_hs_interface_remove(struct platform_device *pdev)
{
    return 0;
}

static struct of_device_id anc_hs_interface_match_table[] =
{
    {
        .compatible = "huawei,anc_hs_interface",
        .data = NULL,
    },
    {
    },
};

static struct platform_driver anc_hs_interface_driver = {
    .probe = anc_hs_interface_probe,
    .remove = anc_hs_interface_remove,

    .driver = {
        .name = "huawei,anc_hs_interface",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(anc_hs_interface_match_table),
    },
};
/**********************************************************
*  Function:       anc_hs_interface_init
*  Discription:    anc_hs module initialization
*  Parameters:   NULL
*  return value:  0-sucess or others-fail
**********************************************************/
static int __init anc_hs_interface_init(void)
{
    return platform_driver_register(&anc_hs_interface_driver);
}
/**********************************************************
*  Function:       anc_hs_interface_exit
*  Discription:    anc_hs module exit
*  Parameters:   NULL
*  return value:  NULL
**********************************************************/
static void __exit anc_hs_interface_exit(void)
{
    platform_driver_unregister(&anc_hs_interface_driver);
}

device_initcall_sync(anc_hs_interface_init);
module_exit(anc_hs_interface_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("anc hs module driver");
MODULE_AUTHOR("HUAWEI Inc");
