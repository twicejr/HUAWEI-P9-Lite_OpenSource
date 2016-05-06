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
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/stat.h>
#include <linux/huawei/gps/huawei_gps.h>
#include <linux/huawei/hw_connectivity.h>


#define DTS_COMP_GPS_POWER_NAME "hisilicon,hisi_gps"
#define HI_GPS_REF_CLK_FREQ    49152000

typedef struct hi_gps_info {
    struct clk *refclk;
    struct clk *muxclk;
    struct clk *mdmclk0;
    struct clk *mdmclk1;
    struct pinctrl *pctrl;
    struct pinctrl_state *pins_normal;
    struct pinctrl_state *pins_idle;
} HI_GPS_INFO;

static struct clk *gps_ref_clk = NULL;
static struct clk *gps_mux_clk = NULL;
static struct clk *mdm2gps_clk0 = NULL;
static struct clk *mdm2gps_clk1 = NULL;
static HI_GPS_INFO *hi_gps_info_t = NULL;

#ifdef CONFIG_HISI_GPS_REF_CLK
int set_gps_ref_clk_enable_hi110x(bool enable, gps_modem_id_enum modem_id, gps_rat_mode_enum rat_mode);
#endif

static ssize_t gps_write_proc_nstandby(struct file* filp, const char __user* buffer, size_t len, loff_t* off)
{
    char gps_nstandby = '0';
    printk(KERN_INFO "[GPS] gps_write_proc_nstandby \n");

    if ((len < 1) || (NULL == hi_gps_info_t))
    {
        printk(KERN_ERR "[GPS] gps_write_proc_nstandby hi_gps_info_t is NULL or read length = 0.\n");
        return -EINVAL;
    }

    if (copy_from_user(&gps_nstandby, buffer, sizeof(gps_nstandby)))
    {
        printk(KERN_ERR "[GPS] gps_write_proc_nstandby copy_from_user failed!\n");
        return -EFAULT;
    }

    if (gps_nstandby == '0')
    {
    #ifdef CONFIG_HISI_GPS_REF_CLK
        printk(KERN_INFO "[GPS] refclk disable.\n");
        set_gps_ref_clk_enable_hi110x(false, 0, 0);
    #endif
    }
    else if (gps_nstandby == '1')
    {
    #ifdef CONFIG_HISI_GPS_REF_CLK
        printk(KERN_INFO "[GPS] refclk SCPLL0 enable.\n");
        set_gps_ref_clk_enable_hi110x(true, 0, 0);
    #endif
    }
    else if (gps_nstandby == '2')
    {
    #ifdef CONFIG_HISI_GPS_REF_CLK
        printk(KERN_INFO "[GPS] refclk SCPLL1 enable.\n");
        set_gps_ref_clk_enable_hi110x(true, 0, 4);
    #endif
    }
    else
    {
        printk(KERN_ERR "[GPS] gps nstandby write error code[%d].\n", gps_nstandby);
    }

    return len;
}

static const struct file_operations gps_proc_fops_nstandby =
{
    .owner = THIS_MODULE,
    .write = gps_write_proc_nstandby,
};

static int create_gps_proc_file(void)
{
    int ret = 0;
    struct proc_dir_entry* gps_dir = NULL;
    struct proc_dir_entry* gps_nstandby_file = NULL;
    gps_dir = proc_mkdir("hi1102_gps", NULL);
    if (!gps_dir)
    {
        printk(KERN_ERR "[GPS] proc dir create failed\n");
        ret = -ENOMEM;
        return ret;
    }

    gps_nstandby_file = proc_create("ref_clk", S_IRUGO | S_IWUSR | S_IWGRP | S_IFREG, gps_dir, &gps_proc_fops_nstandby);
    if (!gps_nstandby_file)
    {
        printk(KERN_ERR "[GPS] proc nstandby file create failed\n");
        ret = -ENOMEM;
        return ret;
    }
    printk(KERN_INFO "[GPS] gps create proc file ok. \n");

    return ret;
}

static int hi_gps_probe(struct platform_device *pdev)
{
    HI_GPS_INFO *hi_gps_info = NULL;
    struct device *gps_power_dev = &pdev->dev;
    int ret = 0;

    printk(KERN_INFO "[GPS] start find gps_power\n");
    hi_gps_info = kzalloc(sizeof(HI_GPS_INFO), GFP_KERNEL);
    if (!hi_gps_info) {
        printk(KERN_ERR "[GPS] Alloc memory failed\n");
        return -ENOMEM;
    }

    hi_gps_info->pctrl = devm_pinctrl_get(gps_power_dev);
    if (IS_ERR_OR_NULL(hi_gps_info->pctrl)) {
        printk(KERN_ERR "[GPS] pinctrl get error! %p\n", hi_gps_info->pctrl);
        ret = -1;
        goto err_pinctrl_get;
    }

    hi_gps_info->pins_normal = pinctrl_lookup_state(hi_gps_info->pctrl, "default");
    if (IS_ERR_OR_NULL(hi_gps_info->pins_normal)) {
        printk(KERN_ERR "[GPS] hi_gps_info->pins_normal lookup error! %p\n", hi_gps_info->pins_normal);
        ret = -1;
        goto err_pins_normal;
    }

    hi_gps_info->pins_idle = pinctrl_lookup_state(hi_gps_info->pctrl, "idle");
    if (IS_ERR_OR_NULL(hi_gps_info->pins_idle)) {
        printk(KERN_ERR "[GPS] hi_gps_info->pins_idle lookup error! %p\n", hi_gps_info->pins_idle);
        ret = -1;
        goto err_pins_idle;
    }

    ret = pinctrl_select_state(hi_gps_info->pctrl, hi_gps_info->pins_normal);
    if (ret) {
        printk(KERN_ERR "[GPS] pinctrl_select_state error! %d\n", ret);
        goto err_select_state;
    }
    printk(KERN_INFO "[GPS] pinctrl is finish\n");

    hi_gps_info->refclk = devm_clk_get(gps_power_dev, "ref_clk");
    if (IS_ERR_OR_NULL(hi_gps_info->refclk))
    {
        printk(KERN_ERR "[GPS] ref_clk get failed!\n");
        ret = PTR_ERR(hi_gps_info->refclk);
        goto err_refclk_get;
    }
    gps_ref_clk = hi_gps_info->refclk;

    hi_gps_info->muxclk = devm_clk_get(gps_power_dev, "mux_clk");
    if (IS_ERR_OR_NULL(hi_gps_info->muxclk))
    {
        printk(KERN_ERR "[GPS] mux_clk get failed!\n");
        ret = PTR_ERR(hi_gps_info->muxclk);
        goto err_muxclk_get;
    }
    gps_mux_clk = hi_gps_info->muxclk;

    hi_gps_info->mdmclk0 = devm_clk_get(gps_power_dev, "mdm_clk0");
    if (IS_ERR_OR_NULL(hi_gps_info->mdmclk0))
    {
        printk(KERN_ERR "[GPS] mdm_clk0 get failed!\n");
        ret = PTR_ERR(hi_gps_info->mdmclk0);
        goto err_mdmclk0_get;
    }
    mdm2gps_clk0 = hi_gps_info->mdmclk0;

    hi_gps_info->mdmclk1 = devm_clk_get(gps_power_dev, "mdm_clk1");
    if (IS_ERR_OR_NULL(hi_gps_info->mdmclk1))
    {
        printk(KERN_ERR "[GPS] mdm_clk1 get failed!\n");
        ret = PTR_ERR(hi_gps_info->mdmclk1);
        goto err_mdmclk1_get;
    }
    mdm2gps_clk1 = hi_gps_info->mdmclk1;

    printk(KERN_INFO "[GPS] ref clk is finished!\n");

    ret = create_gps_proc_file();
    if (ret)
    {
        printk(KERN_ERR "[GPS] gps create proc file failed.\n");
        goto err_mdmclk1_get;
    }

    platform_set_drvdata(pdev, hi_gps_info);
    hi_gps_info_t = hi_gps_info;

#ifdef CONFIG_HISI_GPS_REF_CLK
    register_gps_set_ref_clk_func((void*)set_gps_ref_clk_enable_hi110x);
#endif
    return 0;

err_mdmclk1_get:
    devm_clk_put(gps_power_dev, hi_gps_info->mdmclk0);
err_mdmclk0_get:
    devm_clk_put(gps_power_dev, hi_gps_info->muxclk);
err_muxclk_get:
    devm_clk_put(gps_power_dev, hi_gps_info->refclk);
err_refclk_get:
err_select_state:
err_pins_idle:
err_pins_normal:
    devm_pinctrl_put(hi_gps_info->pctrl);
err_pinctrl_get:
    kfree(hi_gps_info);
    hi_gps_info = NULL;
    hi_gps_info_t = NULL;
    return ret;
}

static void hi_gps_shutdown(struct platform_device *pdev)
{
    HI_GPS_INFO *hi_gps_info = platform_get_drvdata(pdev);
    printk(KERN_INFO "[GPS] hi_gps_shutdown!\n");

    if (!hi_gps_info) {
        printk(KERN_ERR "[GPS] hi_gps_info is NULL,just return.\n");
        return;
    }

#ifdef CONFIG_HISI_GPS_REF_CLK
    register_gps_set_ref_clk_func(NULL);
#endif

    platform_set_drvdata(pdev, NULL);
    kfree(hi_gps_info);
    hi_gps_info = NULL;
    hi_gps_info_t = NULL;
    return;
}

static const struct of_device_id gps_power_match_table[] = {
    {
        .compatible = DTS_COMP_GPS_POWER_NAME,   // compatible must match with which defined in dts
        .data = NULL,
    },
    {
    },
};

MODULE_DEVICE_TABLE(of, gps_power_match_table);

static struct platform_driver hi_gps_plat_driver = {
    .probe          = hi_gps_probe,
    .suspend        = NULL,
    .remove         = NULL,
    .shutdown       = hi_gps_shutdown,
    .driver = {
        .name = "hisi_gps",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(gps_power_match_table), // dts required code
    },
};

int hi_gps_plat_init(void)
{
    int ret = -1;

    if (isMyConnectivityChip(CHIP_TYPE_HI110X))
    {
        ret = platform_driver_register(&hi_gps_plat_driver);
        if (ret)
        {
            printk(KERN_ERR "[GPS] ERROR: unable to register hisi gps plat driver! \n");
        }
    }

    return ret;
}

void hi_gps_plat_exit(void)
{
    platform_driver_unregister(&hi_gps_plat_driver);
}

#ifdef CONFIG_HISI_GPS_REF_CLK
int set_gps_ref_clk_enable_hi110x(bool enable, gps_modem_id_enum modem_id, gps_rat_mode_enum rat_mode)
{
    int ret = 0;
    struct clk *parent = NULL;

    printk(KERN_INFO "[GPS] set_gps_ref_clk_enable(%d,%d,%d) \n", enable, modem_id, rat_mode);
    if (IS_ERR_OR_NULL(gps_ref_clk)) {
        printk(KERN_ERR "[GPS] ERROR: refclk is invalid! \n");
        return -1;
    }

    if (enable)
    {
        if (gps_rat_mode_cdma == rat_mode
          || (gps_rat_mode_butt == rat_mode && gps_modem_id_1 == modem_id))
        {
            /* SCPLL1 */
            parent = mdm2gps_clk1;
            printk(KERN_INFO "[GPS] select SCPLL1 \n");
        }
        else
        {
            /* SCPLL0 */
            parent = mdm2gps_clk0;
            printk(KERN_INFO "[GPS] select SCPLL0 \n");
        }

        ret = clk_set_parent(gps_mux_clk, parent);
        if (ret < 0)
        {
            printk(KERN_ERR "[GPS] ERROR: muxclk set parent failed! \n");
            return ret;
        }

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
#endif

MODULE_AUTHOR("DRIVER_AUTHOR");
MODULE_DESCRIPTION("GPS Hi110X Platfrom driver");
MODULE_LICENSE("GPL");

