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

extern int get_gps_ic_type(void);

#define DTS_COMP_GPS_POWER_NAME "huawei,gps_power"
#define HOST_WAKE_MODULE_NAME "gps_geofence_wake"
#define GPS_REF_CLK_FREQ_19M   (19200000L)

#define GPS_STANDBY         0
#define GPS_ACTIVE          1

#define GPS_IC_TYPE_4752 4752
#define GPS_IC_TYPE_47531 47531
#define GPS_IC_TYPE_4774 4774

typedef struct gps_bcm_info
{
    struct gpio gpioid_en;
    struct clk* clk;
    struct clk* refclk;
    struct pinctrl* pctrl;
    struct pinctrl_state* pins_normal;
    struct pinctrl_state* pins_idle;
    struct gpio       gpioid_hostwake;
    struct gpio       mcu_req;
    struct gpio       mcu_req_rsp;
    bool is_hostwake;
} GPS_BCM_INFO;

struct gps_geofence_wake
{
    /// irq from gpio_to_irq()
    int irq;
    /// HOST_WAKE_GPIO
    int host_req_pin;
    /// misc driver structure
    struct miscdevice misc;
    /// wake_lock
    struct wake_lock wake_lock;
};

enum procs
{
GPS_PROC_MCUREQ,
GPS_PROC_MCUREQ_RSP,
GPS_PROC_EN
};

static struct clk* gps_ref_clk = NULL;
static GPS_BCM_INFO* g_gps_bcm = NULL;
static struct proc_dir_entry* gps_dir = NULL;
static struct gps_geofence_wake g_geofence_wake;

char *Gps_DtsNodeName[] = {
"huawei,mcu_req",
"huawei,mcu_req_rsp",
"huawei,gps_en"
};

const char *Gps_DeviceNodeName[] = {
"mcu_req",
"mcu_req_rsp",
"nstandby"
};

static int gps_geofence_wake_open(struct inode* inode, struct file* filp)
{
    printk("%s\n", __func__);
    return 0;
}

static int gps_geofence_wake_release(struct inode* inode, struct file* filp)
{
    printk("%s\n", __func__);
    return 0;
}

static long gps_geofence_wake_ioctl(struct file* filp, unsigned int cmd, unsigned long arg)
{
    printk("%s\n", __func__);
    return 0;
}

static const struct file_operations gps_geofence_wake_fops =
{
    .owner = THIS_MODULE,
    .open = gps_geofence_wake_open,
    .release = gps_geofence_wake_release,
    .unlocked_ioctl = gps_geofence_wake_ioctl
};

/// set/reset wake lock by HOST_WAKE level
/// \param gpio the value of HOST_WAKE_GPIO
static void gps_geofence_wake_lock(int gpio)
{
    struct gps_geofence_wake *ac_data = &g_geofence_wake;
    //printk("%s : gpio value = %d\n", __func__, gpio);

    if (gpio) 
    {
        //wake_lock(&ac_data->wake_lock);
        wake_lock_timeout(&ac_data->wake_lock, 5 * HZ);
    }
    else 
    {
        wake_unlock(&ac_data->wake_lock);
    }
}

static irqreturn_t gps_host_wake_isr(int irq, void* dev)
{
    struct gps_geofence_wake* ac_data = &g_geofence_wake;
    int gps_host_wake = ac_data->host_req_pin;
    char gpio_value = 0x00;

    //printk("%s\n", __func__);

    gpio_value = gpio_get_value(gps_host_wake);

    // wake_lock
    gps_geofence_wake_lock(gpio_value);

    return IRQ_HANDLED;
}

/// initialize GPIO and IRQ
/// \param gpio the GPIO of HOST_WAKE
/// \return if SUCCESS, return the id of IRQ, if FAIL, return -EIO
static int gps_gpio_irq_init(int gpio)
{
    int ret = 0;
    int irq = 0;

    printk("[gps]%s\n", __func__);
    // 1. Set GPIO
    if ((gpio_request(gpio, "gps_host_wake")))
    {
        printk("[gps]Can't request HOST_REQ GPIO %d.It may be already registered in init.xyz.3rdparty.rc/init.xyz.rc\n", gpio);
        return -EIO;
    }
    gpio_export(gpio, false);
    gpio_direction_input(gpio);

    // 2. Set IRQ
    irq = gpio_to_irq(gpio);
    if (irq < 0)
    {
        printk("[gps]Could not get HOST_WAKE_GPIO = %d!, err = %d\n", gpio, irq);
        gpio_free(gpio);
        return -EIO;
    }

    ret = request_irq(irq, gps_host_wake_isr, IRQF_TRIGGER_RISING | IRQF_NO_SUSPEND|IRQF_TRIGGER_FALLING | IRQF_ONESHOT, "gps_host_wake", NULL);
    if (ret)
    {
        printk("[gps]Request_host wake irq failed.\n");
        gpio_free(gpio);
        return -EIO;
    }

    ret = irq_set_irq_wake(irq, 1);

    if (ret)
    {
        printk("[gps]Set_irq_wake failed.\n");
        gpio_free(gpio);
        free_irq(irq, NULL);
        return -EIO;
    }

    return irq;
}

/// cleanup GPIO and IRQ
#if 0
static void gps_gpio_irq_cleanup(int gpio, int irq)
{
    pr_debug("[gps]%s\n", __func__);
    gpio_free(gpio);
    free_irq(irq, NULL);
}
#endif
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

/*	For write	*/
static ssize_t gps_write_proc_mcureq(struct file* filp, const char __user* buffer, size_t len, loff_t* off)
{
    char gps_nstandby = '0';
    printk(KERN_INFO "[GPS] gps_write_proc_nstandby \n");

    if ((len < 1) || (NULL == g_gps_bcm))
    {
        printk(KERN_ERR "[GPS] gps_write_proc_mcureq g_gps_bcm is NULL or read length = 0.\n");
        return -EINVAL;
    }

    if (copy_from_user(&gps_nstandby, buffer, sizeof(gps_nstandby)))
    {
        printk(KERN_ERR "[GPS] gps_write_proc_mcureq copy_from_user failed!\n");
        return -EFAULT;
    }

    if (gps_nstandby == '0')
    {
        printk(KERN_INFO "[GPS] gps nstandby.\n");
        gpio_set_value(g_gps_bcm->mcu_req.gpio, GPS_STANDBY);
    }
    else if (gps_nstandby == '1')
    {
        printk(KERN_INFO "[GPS] gps active.\n");
        gpio_set_value(g_gps_bcm->mcu_req.gpio, GPS_ACTIVE);
    }
    else
    {
        printk(KERN_ERR "[GPS] gps nstandby write error code[%d].\n", gps_nstandby);
    }

    return len;
}

static ssize_t gps_read_proc_mcureq(struct file* filp,  char __user* buffer, size_t len, loff_t* off)
{
    int gps_nstandby = 0;
    char tmp[2];
    memset(tmp, 0, sizeof(tmp));
    printk(KERN_INFO "[GPS] gps_read_proc_nstandby \n");
    if (len < 1 || NULL == g_gps_bcm)
    {
        printk(KERN_ERR "[GPS] gps_read_proc_mcureq g_gps_bcm is NULL or read length = 0.\n");
        return -EINVAL;
    }
    len = 1;
    printk(KERN_INFO "[GPS] gps_read_proc_mcureq off = %d\n", (unsigned int)*off);
    if ((unsigned int)*off > 0)
    {
        return 0;
    }
    gps_nstandby = gpio_get_value(g_gps_bcm->mcu_req.gpio);
    sprintf(tmp, "%d", gps_nstandby);
    printk(KERN_INFO "[GPS] gps mcu_req status[%s] \n", tmp);

    if (copy_to_user(buffer, tmp, len))
    {
        printk(KERN_ERR "[GPS] mcu_req copy_to_user failed!\n");
        return -EFAULT;
    }
    *off += len;
    return len;
}

static const struct file_operations gps_proc_fops_mcureq =
{
    .owner = THIS_MODULE,
    .write = gps_write_proc_mcureq,
    .read = gps_read_proc_mcureq,
};

/* For read */
static ssize_t gps_read_proc_mcureq_rsp(struct file* filp,  char __user* buffer, size_t len, loff_t* off)
{
    int gps_reqrsp_data= 0;
    char tmp[2];
    memset(tmp, 0, sizeof(tmp));

    if (1 > len|| NULL == g_gps_bcm)
    {
        printk(KERN_ERR "[GPS] gps_read_proc_mcureq  g_gps_bcm is NULL or read length = 0.\n");
        return -EINVAL;
    }

    len = 1;
    printk(KERN_INFO "[GPS] gps_read_proc_nstandby off = %d\n", (unsigned int)*off);
    if ((unsigned int)*off > 0)
    {
        return 0;
    }
    gps_reqrsp_data = gpio_get_value(g_gps_bcm->mcu_req_rsp.gpio);
    sprintf(tmp, "%d", gps_reqrsp_data);
    printk(KERN_INFO "[GPS] gps gps_reqrsp_data status[%s] \n", tmp);

    if (copy_to_user(buffer, tmp, len))
    {
        printk(KERN_ERR "[GPS] gps_read_proc_nstandby copy_to_user failed!\n");
        return -EFAULT;
    }
    *off += len;
    return len;
}

/*	For write	*/
static ssize_t gps_write_proc_mcureq_rsp(struct file* filp, const char __user* buffer, size_t len, loff_t* off)
{
    char gps_nstandby = '0';
    printk(KERN_INFO "[GPS] gps_write_proc_nstandby \n");

    if ((len < 1) || (NULL == g_gps_bcm))
    {
        printk(KERN_ERR "[GPS] gps_write_proc_mcureq g_gps_bcm is NULL or read length = 0.\n");
        return -EINVAL;
    }

    if (copy_from_user(&gps_nstandby, buffer, sizeof(gps_nstandby)))
    {
        printk(KERN_ERR "[GPS] gps_write_proc_mcureq copy_from_user failed!\n");
        return -EFAULT;
    }

    if (gps_nstandby == '0')
    {
        printk(KERN_INFO "[GPS] gps nstandby.\n");
        gpio_set_value(g_gps_bcm->mcu_req_rsp.gpio, GPS_STANDBY);
    }
    else if (gps_nstandby == '1')
    {
        printk(KERN_INFO "[GPS] gps active.\n");
        gpio_set_value(g_gps_bcm->mcu_req_rsp.gpio, GPS_ACTIVE);
    }
    else
    {
        printk(KERN_ERR "[GPS] gps nstandby write error code[%d].\n", gps_nstandby);
    }

    return len;
}

static const struct file_operations gps_proc_fops_mcureq_rsp =
{
    .owner = THIS_MODULE,
    .read = gps_read_proc_mcureq_rsp,
    .write = gps_write_proc_mcureq_rsp,
};


int gps_bcm4774_node_init(struct device_node* np , struct gpio  *Pgpio,  int node,  const struct file_operations *gps_proc_fops)
{
	int ret = 0;

	Pgpio->gpio = of_get_named_gpio(np, Gps_DtsNodeName[node], 0);
	if (!gpio_is_valid(Pgpio->gpio))
	{
		printk(KERN_ERR "[GPS] of_get_named_gpio  %s failed.\n", Gps_DtsNodeName[node]);
		ret = -1;
		return ret;
	}

	ret = gpio_request(Pgpio->gpio, Gps_DeviceNodeName[node]);
	if (ret)
	{
	    printk(KERN_ERR "[GPS] gpio_requestt [%d]%s  failed, ret:%d\n", Pgpio->gpio, Gps_DeviceNodeName[node], ret);
	    return ret;
	}

	ret = gpio_export(Pgpio->gpio, false);
	if (ret)
	{
		printk(KERN_ERR "[GPS] gpio_export %d failed, ret:%d\n", Pgpio->gpio, ret);
		return ret;
	}

	/* For req*/
	ret = gpio_direction_input (Pgpio->gpio);
	if (ret)
	{
	    printk(KERN_ERR "[GPS] gpio_direction_input %d failed, ret:0x%X\n", Pgpio->gpio, ret);
	    return ret;
	}
	printk(KERN_INFO "[GPS] finish gpio_direction_input \n");

	ret = gpio_direction_output( Pgpio->gpio, 0);
	if (ret)
	{
		printk(KERN_ERR "[GPS] gpio_direction_output %d failed, ret:0x%X\n", Pgpio->gpio, ret);
		return ret;
	}

	if (NULL ==  proc_create(Gps_DeviceNodeName[node], S_IRUGO | S_IWUSR | S_IWGRP | S_IFREG, gps_dir,  gps_proc_fops))
	{
		printk(KERN_ERR "[GPS] gps create proc file [%s] failed. ret = %d\n", Gps_DeviceNodeName[node], ret);
		ret = -ENOMEM;
		return ret;
	}

	return 0;
}

static int k3_gps_bcm_probe(struct platform_device* pdev)
{
	GPS_BCM_INFO* gps_bcm = NULL;
	struct device* gps_power_dev = &pdev->dev;
	struct device_node* np = gps_power_dev->of_node;
	int ret = 0;
	int irq = 0;
	struct gps_geofence_wake* ac_data = &g_geofence_wake;

	printk(KERN_INFO "[GPS] start find gps_power and ic type is 4774\n");
	gps_bcm = kzalloc(sizeof(GPS_BCM_INFO), GFP_KERNEL);
	if (!gps_bcm)
	{
	    printk(KERN_ERR "[GPS] Alloc memory failed\n");
	    return -ENOMEM;
	}

	 gps_dir = proc_mkdir("gps", NULL);
	 if (!gps_dir)
	{
	    printk(KERN_ERR "[GPS] proc dir create failed\n");
	    ret = -ENOMEM;
	    goto err_free_gps;
	}

	ret = gps_bcm4774_node_init(np, &gps_bcm->gpioid_en,  GPS_PROC_EN,   &gps_proc_fops_nstandby);
	if (0 != ret)
	{
	    printk(KERN_ERR "[GPS] gps_bcm4774_node_init  gps_bcm  failed.\n");
	    ret = -1;
	    goto err_free_nstandby;
	}

    gps_bcm->gpioid_hostwake.gpio = of_get_named_gpio(np, "huawei,gps_hostwake", 0);
    if (!gpio_is_valid(gps_bcm->gpioid_hostwake.gpio))
    {
        ret = -1;
        printk(KERN_ERR "[GPS] get huawei,gps_hostwake failed.\n");
        goto err_free_gps_en;
    }
    // 1. Init GPIO and IRQ for HOST_WAKE
    printk("[gps]%s,gps_bcm->gpioid_hostwake.gpio=%d\n", __func__, gps_bcm->gpioid_hostwake.gpio);

    // 2. Register Driver
    memset(ac_data, 0, sizeof(struct gps_geofence_wake));

    // 2.1 Misc device setup
    ac_data->misc.minor = MISC_DYNAMIC_MINOR;
    ac_data->misc.name = HOST_WAKE_MODULE_NAME;
    ac_data->misc.fops = &gps_geofence_wake_fops;

    // 2.2 Information that be used later
    ac_data->irq = irq;
    ac_data->host_req_pin = gps_bcm->gpioid_hostwake.gpio;

    printk("[gps]misc register, name %s, irq %d, host req pin num %d\n", ac_data->misc.name, irq, ac_data->host_req_pin);
    // 2.3 Register misc driver
    if (0 != (ret = misc_register(&ac_data->misc)))
    {
        printk("[gps]cannot register gps geofence wake miscdev on minor=%d (%d)\n", MISC_DYNAMIC_MINOR, ret);
        goto err_free_host_wake;
    }

    // 3. Init wake_lock
    wake_lock_init(&ac_data->wake_lock, WAKE_LOCK_SUSPEND, "gps_geofence_wakelock");
    printk("[gps]wake_lock_init done\n");
    irq = gps_gpio_irq_init(gps_bcm->gpioid_hostwake.gpio);
    if (irq < 0)
    {
        printk("[gps]hostwake irq error\n");
        goto err_free_misc_register;
    }

    /* Set 32KC clock */
    gps_bcm->clk = of_clk_get_by_name(np, "gps_32k");
    if (IS_ERR(gps_bcm->clk))
    {
        printk(KERN_ERR "[GPS] clk_32k get failed!\n");
        ret = -1;
        goto err_free_misc_register;
    }
    ret = clk_prepare_enable(gps_bcm->clk);
    if (ret)
    {
        printk(KERN_ERR "[GPS] clk_32k enable is failed\n");
        goto err_free_clk;
    }
    printk(KERN_INFO "[GPS] clk_32k is finished\n");


   ret = gps_bcm4774_node_init(np, &gps_bcm->mcu_req,  GPS_PROC_MCUREQ,  &gps_proc_fops_mcureq);
   if (0 != ret)
   {
      printk(KERN_ERR "[GPS]gps_bcm4774_node_init  mcu_req  failed \n");
      goto err_free_mcureq;
   }

   ret = gps_bcm4774_node_init(np, &gps_bcm->mcu_req_rsp,  GPS_PROC_MCUREQ_RSP,  &gps_proc_fops_mcureq_rsp);
   if (0 != ret)
   {
       printk(KERN_ERR "[GPS]gps_bcm4774_node_init  mcu_req_rsp  failed \n");
       goto err_free_mcureq_rsp;
    }

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

    gps_bcm->refclk = of_clk_get_by_name(np, "clk_gps");
    if (IS_ERR(gps_bcm->refclk))
    {
        printk(KERN_ERR "[GPS] @@@ref_clk get failed!\n");
        ret = -1;
        goto err_free_pinctrl;
    }

    ret = clk_set_rate(gps_bcm->refclk , GPS_REF_CLK_FREQ_19M);
    if (ret < 0)
    {
        printk(KERN_ERR "[GPS] clk_set_rate HI3635_CLK_RATE failed\n");
        goto err_free_refclk;
    }

    gps_ref_clk = gps_bcm->refclk;

    printk(KERN_INFO "[GPS] ref clk is finished!\n");
    platform_set_drvdata(pdev, gps_bcm);
    g_gps_bcm = gps_bcm;

    return 0;

err_free_refclk:
    clk_put(gps_bcm->refclk);
err_free_pinctrl:
    pinctrl_put(gps_bcm->pctrl);

err_free_mcureq:
err_free_mcureq_rsp:
err_free_clk:
    clk_put(gps_bcm->clk);
err_free_misc_register:
    misc_deregister(&ac_data->misc);
    wake_lock_destroy(&ac_data->wake_lock);
    pr_err("%s: misc_deregister!\n", __func__);
err_free_host_wake:
    gpio_free(gps_bcm->gpioid_hostwake.gpio);
    pr_err("%s: err_free_host_wake!\n", __func__);

err_free_gps_en:
    gpio_free(gps_bcm->gpioid_en.gpio);

err_free_nstandby:
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

int bcm4774_resume(struct platform_device *p);
int bcm4774_suspend(struct platform_device *p, pm_message_t state);
static struct platform_driver k3_gps_bcm_driver =
{
	.probe = k3_gps_bcm_probe,
	.suspend = bcm4774_suspend,
	.remove = NULL,
	.resume = bcm4774_resume,
	.shutdown = K3_gps_bcm_shutdown,
	.driver = {
		   .name = "huawei,gps_power_4774",
		   .owner = THIS_MODULE,
		   .of_match_table = of_match_ptr(gps_power_match_table),	/*dts required code*/
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

    if(GPS_IC_TYPE_4774 != get_gps_ic_type())
    {
        printk(KERN_INFO "gps chip type is matched with Broadcom, but is not 4774");
        return -EINVAL;
    }
    printk(KERN_INFO "gps chip type is matched with Broadcom, and it is 4774\n");
    return platform_driver_register(&k3_gps_bcm_driver);
}

static void __exit k3_gps_bcm_exit(void)
{
    platform_driver_unregister(&k3_gps_bcm_driver);
}

int set_gps_ref_clk_enable_bcm4774(bool enable)
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
MODULE_DESCRIPTION("GPS Boardcom 4774 driver");
MODULE_LICENSE("GPL");

