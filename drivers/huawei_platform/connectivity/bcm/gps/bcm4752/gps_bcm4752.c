#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/clk.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/pinctrl/pinctrl.h>
#include <linux/pinctrl/consumer.h>
#include <linux/printk.h>
#include <linux/huawei/gps/huawei_gps.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/stat.h>
#include <linux/rfkill.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/workqueue.h>
#include <linux/uaccess.h>
#include <linux/poll.h>
#include <linux/miscdevice.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/platform_device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/list.h>
#include <linux/version.h>
#include <linux/workqueue.h>
#include <linux/unistd.h>
#include <linux/bug.h>
#include <linux/mutex.h>
#include <linux/wakelock.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_device.h>


#ifdef CONFIG_HWCONNECTIVITY
#include <linux/huawei/hw_connectivity.h>
#endif

#define DTS_COMP_GPS_POWER_NAME "huawei,gps_power"
#define GPS_REF_CLK_FREQ_49M   (49152000L)
#define GPS_REF_CLK_FREQ_19M   (19200000L)

#define GPS_STANDBY         0
#define GPS_ACTIVE          1

#define GPS_IC_TYPE_4752 4752
#define GPS_IC_TYPE_47531 47531

#define GPS_REFCLK_SEL_ENABLE 1
#define GPS_REFCLK_SEL_DISABLE 0

extern int get_gps_ic_type(void);
extern int get_gps_ref_sel_enable(void);

typedef struct gps_bcm_info
{
    struct gpio gpioid_en;
    struct clk* clk;
    struct clk* refclk_sel;
    struct clk* refclk;
    struct pinctrl* pctrl;
    struct pinctrl_state* pins_normal;
    struct pinctrl_state* pins_idle;
} GPS_BCM_INFO;

static struct clk* gps_ref_clk = NULL;
static GPS_BCM_INFO* g_gps_bcm = NULL;

static ssize_t gps_write_proc_nstandby(struct file* filp, const char __user* buffer, size_t len, loff_t* off)
{
    char gps_nstandby = '0';
    printk(KERN_INFO "[GPS] gps_write_proc_nstandby \n");

    if ((len < 1) || (NULL == g_gps_bcm))
    {
        printk(KERN_ERR "[GPS] gps_write_proc_nstandby g_gps_bcm is NULL or read length = 0.\n");
        return -EINVAL;
    }

    if (copy_from_user(&gps_nstandby, buffer, sizeof(gps_nstandby)))
    {
        printk(KERN_ERR "[GPS] gps_write_proc_nstandby copy_from_user failed!\n");
        return -EFAULT;
    }

    if (gps_nstandby == '0')
    {
        printk(KERN_INFO "[GPS] gps nstandby.\n");
        gpio_set_value(g_gps_bcm->gpioid_en.gpio, GPS_STANDBY);
    }
    else if (gps_nstandby == '1')
    {
        printk(KERN_INFO "[GPS] gps active.\n");
        gpio_set_value(g_gps_bcm->gpioid_en.gpio, GPS_ACTIVE);
    }
    else
    {
        printk(KERN_ERR "[GPS] gps nstandby write error code[%d].\n", gps_nstandby);
    }

    return len;
}

static ssize_t gps_read_proc_nstandby(struct file* filp,  char __user* buffer, size_t len, loff_t* off)
{
    int gps_nstandby = 0;
    char tmp[2];
    memset(tmp, 0, sizeof(tmp));
    printk(KERN_INFO "[GPS] gps_read_proc_nstandby \n");
    if (len < 1 || NULL == g_gps_bcm)
    {
        printk(KERN_ERR "[GPS] gps_read_proc_nstandby g_gps_bcm is NULL or read length = 0.\n");
        return -EINVAL;
    }
    len = 1;
    printk(KERN_INFO "[GPS] gps_read_proc_nstandby off = %d\n", (unsigned int)*off);
    if ((unsigned int)*off > 0)
    {
        return 0;
    }
    gps_nstandby = gpio_get_value(g_gps_bcm->gpioid_en.gpio);
    sprintf(tmp, "%d", gps_nstandby);
    printk(KERN_INFO "[GPS] gps nstandby status[%s] \n", tmp);

    if (copy_to_user(buffer, tmp, len))
    {
        printk(KERN_ERR "[GPS] gps_read_proc_nstandby copy_to_user failed!\n");
        return -EFAULT;
    }
    *off += len;
    return len;
}

static const struct file_operations gps_proc_fops_nstandby =
{
    .owner = THIS_MODULE,
    .write = gps_write_proc_nstandby,
    .read = gps_read_proc_nstandby,
};

static int create_gps_proc_file(void)
{
    int ret = 0;
    struct proc_dir_entry* gps_dir = NULL;
    struct proc_dir_entry* gps_nstandby_file = NULL;
    gps_dir = proc_mkdir("gps", NULL);
    if (!gps_dir)
    {
        printk(KERN_ERR "[GPS] proc dir create failed\n");
        ret = -ENOMEM;
        return ret;
    }

    gps_nstandby_file = proc_create("nstandby", S_IRUGO | S_IWUSR | S_IWGRP | S_IFREG, gps_dir, &gps_proc_fops_nstandby);
    if (!gps_nstandby_file)
    {
        printk(KERN_ERR "[GPS] proc nstandby file create failed\n");
        ret = -ENOMEM;
        return ret;
    }
    printk(KERN_INFO "[GPS] gps create proc file ok. \n");

    return ret;
}

static int k3_gps_bcm_probe(struct platform_device* pdev)
{
    GPS_BCM_INFO* gps_bcm = NULL;
    struct device* gps_power_dev = &pdev->dev;
    struct device_node* np = gps_power_dev->of_node;
    enum of_gpio_flags gpio_flags;
    int ret = 0;

    printk(KERN_INFO "[GPS] start find gps_power and ic type is bcm4752 \n");
    gps_bcm = kzalloc(sizeof(GPS_BCM_INFO), GFP_KERNEL);
    if (!gps_bcm)
    {
        printk(KERN_ERR "[GPS] Alloc memory failed\n");
        return -ENOMEM;
    }

    gps_bcm->gpioid_en.gpio = of_get_gpio_by_prop(np , "huawei,gps_en" , 0 , 0 , &gpio_flags);

    if (!gpio_is_valid(gps_bcm->gpioid_en.gpio))
    {
        printk(KERN_ERR "[GPS] get huawei,gps_en gpio failed. and request again\n");
        gps_bcm->gpioid_en.gpio = of_get_named_gpio(np, "huawei,gps_en", 0);
        if(!gpio_is_valid(gps_bcm->gpioid_en.gpio))
        {
            printk(KERN_ERR "[GPS] get huawei,gps_en gpio failed.\n");
            ret = -1;
            goto err_free_gps;
        }
    }

    ret = gpio_request(gps_bcm->gpioid_en.gpio, "gps_enbale");
    if (ret)
    {
        printk(KERN_ERR "[GPS] gpio_direction_output %d failed, ret:%d\n", gps_bcm->gpioid_en.gpio, ret);
        goto err_free_gps_en;
    }
    gpio_export(gps_bcm->gpioid_en.gpio, false);
    ret = gpio_direction_output( gps_bcm->gpioid_en.gpio, 0);
    if (ret)
    {
        printk(KERN_ERR "[GPS] gpio_direction_output %d failed, ret:%d\n", gps_bcm->gpioid_en.gpio, ret);
        goto err_free_gps_en;
    }
    printk(KERN_INFO "[GPS] finish gpio_direction_output gps_power\n");

    ret = create_gps_proc_file();
    if (ret)
    {
        printk(KERN_ERR "[GPS] gps create proc file failed.\n");
        goto err_free_gps_en;
    }

    /* Set 32KC clock */
    gps_bcm->clk = of_clk_get_by_name(np, "gps_32k");
    if (IS_ERR(gps_bcm->clk))
    {
        printk(KERN_ERR "[GPS] clk_32k get failed!\n");
        ret = -1;
        goto err_free_gps_en;
    }
    ret = clk_prepare_enable(gps_bcm->clk);
    if (ret)
    {
        printk(KERN_ERR "[GPS] clk_32k enable is failed\n");
        goto err_free_clk;
    }
    printk(KERN_INFO "[GPS] clk_32k is finished\n");

    gps_bcm->pctrl = devm_pinctrl_get(gps_power_dev);
    if (IS_ERR(gps_bcm->pctrl))
    {
        printk(KERN_ERR "[GPS] pinctrl get error!\n");
        ret = -1;
        goto err_free_clk;
    }
    gps_bcm->pins_normal = pinctrl_lookup_state(gps_bcm->pctrl, "default");
    if (IS_ERR(gps_bcm->pins_normal))
    {
        printk(KERN_ERR "[GPS] gps_bcm->pins_normal lookup error!\n");
        ret = -1;
        goto err_free_pinctrl;
    }

    gps_bcm->pins_idle = pinctrl_lookup_state(gps_bcm->pctrl, "idle");
    if (IS_ERR(gps_bcm->pins_idle))
    {
        printk(KERN_ERR "[GPS] gps_bcm->pins_idle lookup error!\n");
        ret = -1;
        goto err_free_pinctrl;
    }

    ret = pinctrl_select_state(gps_bcm->pctrl, gps_bcm->pins_normal);
    if (ret)
    {
        printk(KERN_ERR "[GPS] pinctrl_select_state error!\n");
        goto err_free_pinctrl;
    }
    printk(KERN_INFO "[GPS] pinctrl is finish\n");

    /*Read dtsimage to get the ref_clk_enable properity*/

    if(GPS_REFCLK_SEL_ENABLE == get_gps_ref_sel_enable())
    {
        gps_bcm->refclk = of_clk_get_by_name(np, "ref_clk");
        if (IS_ERR(gps_bcm->refclk))
        {
            printk(KERN_ERR "[GPS] ref_clk get failed!\n");
            ret = -1;
            goto err_free_pinctrl;
        }
        gps_bcm->refclk_sel = of_clk_get_by_name(np, "ref_clk_sel");
        if (IS_ERR(gps_bcm->refclk_sel))
        {
            printk(KERN_ERR "[GPS] ref_clk_sel get failed!\n");
            ret = -1;
            goto err_free_refclk;
        }
        ret = clk_set_rate(gps_bcm->refclk_sel, GPS_REF_CLK_FREQ_49M);
        if (ret < 0)
        {
            printk(KERN_ERR "[GPS] ref_clk_sel set rate failed\n");
            ret = -1;
            goto err_free_refclk_sel;
        }
    }
    else
    {
        gps_bcm->refclk = of_clk_get_by_name(np, "clk_gps");
        if (IS_ERR(gps_bcm->refclk))
        {
            printk(KERN_ERR "[GPS] ref_clk get failed!\n");
            ret = -1;
            goto err_free_pinctrl;
        }
        ret = clk_set_rate(gps_bcm->refclk, GPS_REF_CLK_FREQ_19M);
        if (ret < 0)
        {
            printk(KERN_ERR "[GPS] ref_clk_sel set rate failed\n");
            ret = -1;
            goto err_free_refclk;
        }
    }

    gps_ref_clk = gps_bcm->refclk;
    printk(KERN_INFO "[GPS] ref clk is finished!\n");
    platform_set_drvdata(pdev, gps_bcm);
    g_gps_bcm = gps_bcm;
    return 0;

err_free_refclk_sel:
    clk_put(gps_bcm->refclk_sel);
err_free_refclk:
    clk_put(gps_bcm->refclk);
err_free_pinctrl:
    pinctrl_put(gps_bcm->pctrl);
err_free_clk:
    clk_put(gps_bcm->clk);
err_free_gps_en:
    gpio_free(gps_bcm->gpioid_en.gpio);
err_free_gps:
    kfree(gps_bcm);
    gps_bcm = NULL;
    g_gps_bcm = NULL;
    return ret;
}

static void K3_gps_bcm_shutdown(struct platform_device* pdev)
{
    GPS_BCM_INFO* gps_bcm = platform_get_drvdata(pdev);
    printk(KERN_INFO "[GPS] K3_gps_bcm_shutdown!\n");

    if (!gps_bcm)
    {
        printk(KERN_ERR "[GPS] gps_bcm is NULL,just return.\n");
        return;
    }

    platform_set_drvdata(pdev, NULL);
    kfree(gps_bcm);
    gps_bcm = NULL;
    g_gps_bcm = NULL;
    return;
}

static const struct of_device_id gps_power_match_table[] =
{
    {
        .compatible = DTS_COMP_GPS_POWER_NAME,   // compatible must match with which defined in dts
        .data = NULL,
    },
    {
    },
};

MODULE_DEVICE_TABLE(of, gps_power_match_table);

static struct platform_driver k3_gps_bcm_driver =
{
    .probe          = k3_gps_bcm_probe,
    .suspend        = NULL,
    .remove         = NULL,
    .shutdown       = K3_gps_bcm_shutdown,
    .driver = {
        .name = "huawei,gps_power_4752",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(gps_power_match_table), // dts required code
    },
};

static int __init k3_gps_bcm_init(void)
{
#ifdef CONFIG_HWCONNECTIVITY
    //For OneTrack, we need check it's the right chip type or not.
    //If it's not the right chip type, don't init the driver
    if (!isMyConnectivityChip(CHIP_TYPE_BCM))
    {
        printk(KERN_ERR "gps chip type is not match, skip driver init");
        return -EINVAL;
    }
    else
    {
        printk(KERN_INFO "gps chip type is matched with Broadcom, continue");
    }
#endif
    if(GPS_IC_TYPE_4752 != get_gps_ic_type())
    {
        printk(KERN_ERR "gps chip type is matched with Broadcom, and it is not 4752\n");
        return -EINVAL;
    }
    printk(KERN_INFO "gps chip type is matched with Broadcom, and it is 4752\n");
    return platform_driver_register(&k3_gps_bcm_driver);
}

static void __exit k3_gps_bcm_exit(void)
{
    platform_driver_unregister(&k3_gps_bcm_driver);
}

int set_gps_ref_clk_enable_bcm4752(bool enable)
{
    int ret = 0;

    printk(KERN_INFO "[GPS] set_gps_ref_clk_enable(%d) \n", enable);
    if (IS_ERR(gps_ref_clk))
    {
        printk(KERN_ERR "[GPS] ERROR: refclk is invalid! \n");
        return -1;
    }

    if (enable)
    {
        ret = clk_prepare_enable(gps_ref_clk);
        if (ret < 0)
        {
            printk(KERN_ERR "[GPS] ERROR: refclk enable failed! \n");
            return -1;
        }
    }
    else
    {
        clk_disable_unprepare(gps_ref_clk);
    }
    printk(KERN_INFO "[GPS] set_gps_ref_clk_enable finish \n");

    return 0;
}

module_init(k3_gps_bcm_init);
module_exit(k3_gps_bcm_exit);

MODULE_AUTHOR("DRIVER_AUTHOR");
MODULE_DESCRIPTION("GPS Boardcom 47511 driver");
MODULE_LICENSE("GPL");
