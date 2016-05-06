
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/regulator/consumer.h>
#include <linux/spi/spi.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>
#include <linux/wakelock.h>
#include "fingerprint.h"
#if defined (CONFIG_TEE_TUI)
#include "tui.h"
#endif

#if defined (CONFIG_HUAWEI_DSM)
#include <dsm/dsm_pub.h>
struct dsm_dev dsm_fingerprint =
{
	.name = "dsm_fingerprint",
	.device_name = "fpc",
	.ic_name = "NNN",
	.module_name = "NNN",
	.fops = NULL,
	.buff_size = 1024,
};
struct dsm_client *fingerprint_dclient = NULL;
#endif
#define HWLOG_TAG fingerprint
HWLOG_REGIST();

/* tui_flg will be set to 1 when tui init(which mean tui is displaying)
 * set to 0 when tui exit
 * This will let fp hal do not read from rst gpio,just return 1
 */
static int tui_flg = 0;
static DEFINE_MUTEX(tui_flg_lock);

/* fp_ready_flg will be set to 1 when fp hal has init fp sensor succeed
 * This will tell tui_fp_notify when to send msg to fp hal
 */
static int fp_ready_flg = 0;

/*
 * When tui is displaying, the fingerprint sensor will response as a fiq
 * in this situation fp_fiq_flg will be set to 1
 * When hal check gpio, if fp_fiq_flg is 1 then just return irq=1, else return irq=0
 */
static int fp_fiq_flg = 0;

extern int tp_gpio_num;
/**
 * sysf node to check the interrupt status of the sensor, the interrupt
 * handler should perform sysf_notify to allow userland to poll the node.
 */
static ssize_t irq_get(struct device* device,
                       struct device_attribute* attribute,
                       char* buffer)
{
    struct fp_data* fingerprint = dev_get_drvdata(device);
    int irq;
    printk("tui_flg is %d, fp_ready_flg is %d, fp_fiq_flg is %d\n", tui_flg, fp_ready_flg, fp_fiq_flg);
    mutex_lock(&tui_flg_lock);
    if (tui_flg == 0)
	    irq = gpio_get_value(fingerprint->irq_gpio);
    else {
        //when fp fiq comes, it should return 1 else return 0
        if (!fp_fiq_flg) {
            irq = 0;
        }
        else {
            irq = 1;
            fp_fiq_flg = 0;
        }
    }
    mutex_unlock(&tui_flg_lock);
    return scnprintf(buffer, PAGE_SIZE, "%i\n", irq);
}


/**
 * writing to the irq node will just drop a printk message
 * and return success, used for latency measurement.
 */
static ssize_t irq_ack(struct device* device,
                       struct device_attribute* attribute,
                       const char* buffer, size_t count)
{
    //hwlog_info("%s\n", __func__);
    return count;
}

static ssize_t result_show(struct device* device,
                       struct device_attribute* attribute,
                       char* buffer)
{
    struct fp_data* fingerprint = dev_get_drvdata(device);
    return scnprintf(buffer, PAGE_SIZE, "%lu", fingerprint->finger_num);
}

static ssize_t result_store(struct device* device,
                       struct device_attribute* attribute,
                       const char* buffer, size_t count)
{
    struct fp_data* fingerprint = dev_get_drvdata(device);
    fingerprint->finger_num = simple_strtoul(buffer, NULL, 10);
    sysfs_notify(&fingerprint->pf_dev->dev.kobj, NULL, "result");
    return count;
}

static ssize_t read_image_flag_show(struct device* device,
                       struct device_attribute* attribute,
                       char* buffer)
{
    struct fp_data* fingerprint = dev_get_drvdata(device);
    return scnprintf(buffer, PAGE_SIZE, "%lu", fingerprint->read_image_flag);
}
static ssize_t read_image_flag_store(struct device* device,
                       struct device_attribute* attribute,
                       const char* buffer, size_t count)
{
    struct fp_data* fingerprint = dev_get_drvdata(device);
    fingerprint->read_image_flag = simple_strtoul(buffer, NULL, 10);
    return count;
}
static DEVICE_ATTR(irq, S_IRUSR | S_IWUSR, irq_get, irq_ack);
static DEVICE_ATTR(result, S_IRUSR | S_IWUSR, result_show, result_store);
static DEVICE_ATTR(read_image_flag, S_IRUSR | S_IWUSR, read_image_flag_show, read_image_flag_store);

static ssize_t fingerprint_chip_info_show(struct device *device, struct device_attribute *attribute, char *buf)
{
    char module[5] = {0};
    char sensor_id[10]={0};
    const char* module_info;
    int ret = 0;
    struct fp_data* fingerprint= dev_get_drvdata(device);
    struct device* dev = fingerprint->dev;
    struct device_node* np = dev->of_node;
    switch (fingerprint->module_vendor_info)
    {
    	   case MODULEID_LOW:
            ret = of_property_read_string(np, "fingerprint,moduleid_low", &module_info);
            if (ret)
            {
                strncpy(module, "NN", 3);
                hwlog_err("%s failed to get moduleid_low from device tree\n", __func__);
	         break;
            }
            strncpy(module, module_info, 3);
            break;
	  case MODULEID_HIGT:
            ret = of_property_read_string(np, "fingerprint,moduleid_high", &module_info);
            if (ret)
            {
                strncpy(module, "NN", 3);
                hwlog_err("%s failed to get moduleid_high from device tree\n", __func__);
	         break;
            }
            strncpy(module, module_info, 3);
            break;
	  case MODULEID_FLOATING:
            ret = of_property_read_string(np, "fingerprint,moduleid_float", &module_info);
            if (ret)
            {
	 	   strncpy(module, "NN",3);
                 hwlog_err("%s failed to get fingerprint,moduleid_float from device tree\n", __func__);
	          break;
            }
            strncpy(module, module_info, 3);
            break;
	  default:
             strncpy(module, "NN",3);
	  break;
    }
    sprintf(sensor_id,"%x",fingerprint->sensor_id);
    return scnprintf(buf,50,"%s--%s\n",sensor_id,module);
}
static DEVICE_ATTR(fingerprint_chip_info, S_IRUSR  | S_IRGRP | S_IROTH, fingerprint_chip_info_show, NULL);
static struct attribute* attributes[] =
{
    &dev_attr_irq.attr,
    &dev_attr_fingerprint_chip_info.attr,
    &dev_attr_result.attr,
    &dev_attr_read_image_flag.attr,
    NULL
};

static const struct attribute_group attribute_group =
{
    .attrs = attributes,
};
static struct fp_data* g_fingerprint = NULL;
int tui_fp_notify(void)
{
    struct fp_data* fingerprint = g_fingerprint;

    if (!fingerprint)
    {
        hwlog_err("%s failed g_fingerprint is NULL\n", __func__);
        return -EINVAL;
    }
    if (!fp_ready_flg) {
        //fp not ready
        return 0;
    }
    printk("%s: fp is ready\n", __func__);
    fp_fiq_flg = 1;
	smp_rmb();

	if (fingerprint->wakeup_enabled) {
		wake_lock_timeout(&fingerprint->ttw_wl, msecs_to_jiffies(FPC_TTW_HOLD_TIME));
	}

	sysfs_notify(&fingerprint->pf_dev->dev.kobj, NULL, dev_attr_irq.attr.name);
    return 0;
}
static irqreturn_t fingerprint_irq_handler(int irq, void* handle)
{
    struct fp_data* fingerprint = handle;

    smp_rmb();

    if (fingerprint->wakeup_enabled)
    {
        wake_lock_timeout(&fingerprint->ttw_wl, msecs_to_jiffies(FPC_TTW_HOLD_TIME));
    }

    sysfs_notify(&fingerprint->pf_dev->dev.kobj, NULL, dev_attr_irq.attr.name);
    //hwlog_info("%s \n", __func__);
    return IRQ_HANDLED;
}

void fingerprint_get_navigation_adjustvalue(struct device* dev, struct fp_data* fp_data)
{
    struct device_node* np;
    int adjust1 = NAVIGATION_ADJUST_NOREVERSE;
    int adjust2 = NAVIGATION_ADJUST_NOTURN;

    if (!dev || !dev->of_node)
    {
        hwlog_err("%s failed dev or dev node is NULL\n", __func__);
        return;
    }

    np = dev->of_node;

    (void)of_property_read_u32(np, "fingerprint,navigation_adjust1", &adjust1);

    if(adjust1 != NAVIGATION_ADJUST_NOREVERSE && adjust1 != NAVIGATION_ADJUST_REVERSE)
    {
        adjust1 = NAVIGATION_ADJUST_NOREVERSE;
        hwlog_err("%s navigation_adjust1 set err only support 0 and 1.\n", __func__);
    }

    (void)of_property_read_u32(np, "fingerprint,navigation_adjust2", &adjust2);

    if(adjust2 != NAVIGATION_ADJUST_NOTURN && adjust2 != NAVIGATION_ADJUST_TURN90 &&
            adjust2 != NAVIGATION_ADJUST_TURN180 && adjust2 != NAVIGATION_ADJUST_TURN270)
    {
        adjust2 = NAVIGATION_ADJUST_NOTURN;
        hwlog_err("%s navigation_adjust2 set err only support 0 90 180 and 270.\n", __func__);
    }

    fp_data->navigation_adjust1 = adjust1;
    fp_data->navigation_adjust2 = adjust2;

    hwlog_info("%s get navigation_adjust1 = %d, navigation_adjust2 = %d.\n", __func__,
                  fp_data->navigation_adjust1, fp_data->navigation_adjust2);
    return;
}

int fingerprint_get_dts_data(struct device* dev, struct fp_data* fp_data)
{
    struct device_node* np;
    int ret = 0;

    if (!dev || !dev->of_node)
    {
        hwlog_err("%s failed dev or dev node is NULL\n", __func__);
        return -EINVAL;
    }

    np = dev->of_node;


    ret = of_property_read_u32(np, "fingerprint,reset_gpio",
                               &fp_data->rst_gpio);

    if (ret)
    {
        fp_data->rst_gpio = -EINVAL;
        hwlog_err("%s failed to get reset gpio from device tree\n", __func__);
        goto exit;
    }

    ret = of_property_read_u32(np, "fingerprint,irq_gpio",
                               &fp_data->irq_gpio);

    if (ret)
    {
        fp_data->irq_gpio = -EINVAL;
        hwlog_err("%s failed to get irq gpio from device tree\n", __func__);
        goto exit;
    }

    fp_data->moduleID_gpio = of_get_named_gpio(np, "fingerprint,moduleid_gpio", 0);

    if ((int)(fp_data->moduleID_gpio) < 0)
    {
        ret = of_property_read_u32(np, "fingerprint,moduleid_gpio",
                                   &fp_data->moduleID_gpio);

        if (ret)
        {
            fp_data->moduleID_gpio = -EINVAL;
            hwlog_info("%s failed to moduleID_gpio gpio from device tree\n", __func__);
            //goto exit;  /* some products didn't support module ID gpio */
        }

        hwlog_info("%s moduleID_gpio=%u\n", __func__, fp_data->moduleID_gpio);
    }
    else
    {
        hwlog_info("%s moduleID_gpio=%u\n", __func__, fp_data->moduleID_gpio);
    }

    return 0;

exit:
    return  -EINVAL;
}

static int fingerprint_key_remap_reverse(int key)
{
    switch(key)
    {
        case EVENT_LEFT:
            key = EVENT_RIGHT;
            break;
        case EVENT_RIGHT:
            key = EVENT_LEFT;
            break;
        default:
            break;
    }

    return key;
}

static int fingerprint_key_remap_turn90(int key)
{
    switch(key)
    {
        case EVENT_LEFT:
            key = EVENT_UP;
            break;
        case EVENT_RIGHT:
            key = EVENT_DOWN;
            break;
        case EVENT_UP:
            key = EVENT_RIGHT;
            break;
        case EVENT_DOWN:
            key = EVENT_LEFT;
            break;
        default:
            break;
    }

    return key;
}

static int fingerprint_key_remap_turn180(int key)
{
    switch(key)
    {
        case EVENT_LEFT:
            key = EVENT_RIGHT;
            break;
        case EVENT_RIGHT:
            key = EVENT_LEFT;
            break;
        case EVENT_UP:
            key = EVENT_DOWN;
            break;
        case EVENT_DOWN:
            key = EVENT_UP;
            break;
        default:
            break;
    }

    return key;
}

static int fingerprint_key_remap_turn270(int key)
{
    switch(key)
    {
        case EVENT_LEFT:
            key = EVENT_DOWN;
            break;
        case EVENT_RIGHT:
            key = EVENT_UP;
            break;
        case EVENT_UP:
            key = EVENT_LEFT;
            break;
        case EVENT_DOWN:
            key = EVENT_RIGHT;
            break;
        default:
            break;
    }

    return key;
}

static int fingerprint_key_remap(struct fp_data* fingerprint, int key)
{
    if(key != EVENT_RIGHT && key != EVENT_LEFT && key != EVENT_UP && key != EVENT_DOWN)
    {
        return key;
    }

    if(fingerprint->navigation_adjust1 == NAVIGATION_ADJUST_REVERSE)
    {
        key = fingerprint_key_remap_reverse(key);
    }

    switch (fingerprint->navigation_adjust2)
    {
        case NAVIGATION_ADJUST_TURN90:
            key = fingerprint_key_remap_turn90(key);
            break;
        case NAVIGATION_ADJUST_TURN180:
            key = fingerprint_key_remap_turn180(key);
            break;
        case NAVIGATION_ADJUST_TURN270:
            key = fingerprint_key_remap_turn270(key);
            break;
        default:
            break;
    }

    return key;
}


static void fingerprint_input_report(struct fp_data* fingerprint, int key)
{
    key = fingerprint_key_remap(fingerprint, key);
    hwlog_info("%s key=%d\n", __func__, key);
    input_report_key(fingerprint->input_dev, key, 1);
    input_sync(fingerprint->input_dev);
    input_report_key(fingerprint->input_dev, key, 0);
    input_sync(fingerprint->input_dev);
}

static int fingerprint_open(struct inode* inode, struct file* file)
{
    struct fp_data* fingerprint;
    hwlog_info("%s\n", __func__);
    fingerprint = container_of(inode->i_cdev, struct fp_data, cdev);
    file->private_data = fingerprint;
    return 0;
}

static ssize_t fingerprint_write(struct file* file, const char* buff, size_t count, loff_t* ppos)
{
    hwlog_info("%s\n", __func__);
    return 0;
}

static ssize_t fingerprint_read(struct file* file, char* buff, size_t count, loff_t* ppos)
{
    hwlog_info("%s\n", __func__);
    return 0;
}

static int fingerprint_get_irq_status(struct fp_data* fingerprint )
{
    int status = 0;
    status = gpio_get_value_cansleep(fingerprint->irq_gpio);
    return status;
}



static long fingerprint_ioctl(struct file* file, unsigned int cmd, unsigned long arg)
{

    int error = 0;

    struct fp_data* fingerprint;
    void __user* argp = (void __user*)arg;
    int key;
    int status;
    unsigned int sensor_id;
    fingerprint = (struct fp_data*)file->private_data;

    if (_IOC_TYPE(cmd) != FP_IOC_MAGIC)
    { return -ENOTTY; }

    switch (cmd)
    {
        case FP_IOC_CMD_ENABLE_IRQ:
            hwlog_info("%s FP_IOC_CMD_ENABLE_IRQ \n", __func__);
            fp_ready_flg  = 1;
            enable_irq(gpio_to_irq(fingerprint->irq_gpio ));
            break;

        case FP_IOC_CMD_DISABLE_IRQ:
            hwlog_info("%s FP_IOC_CMD_DISABLE_IRQ \n", __func__);
            fp_ready_flg  = 0;
            disable_irq(gpio_to_irq(fingerprint->irq_gpio ));
            break;

        case FP_IOC_CMD_SEND_UEVENT:
            if (copy_from_user(&key, argp, sizeof(key)))
            {
                hwlog_err("%s copy_from_user failed.\n", __func__);
                return -EFAULT;
            }

            fingerprint_input_report(fingerprint, key);
            hwlog_info("%s FP_IOC_CMD_SEND_UEVENT\n", __func__);
            break;

        case FP_IOC_CMD_GET_IRQ_STATUS:

            status = fingerprint_get_irq_status(fingerprint);

            error = copy_to_user(argp, &status, sizeof(status));

            if (error)
            {
                hwlog_err("%s copy_to_user failed error=%d.\n", __func__, error);
                return -EFAULT;
            }

            hwlog_info("%s FP_IOC_CMD_GET_IRQ_STATUS status=%d\n", __func__, status);
            break;

        case FP_IOC_CMD_SET_WAKELOCK_STATUS:
            if (copy_from_user(&key, argp, sizeof(key)))
            {
                hwlog_err("%s copy_from_user failed.\n", __func__);
                return -EFAULT;
            }

            if (key == 1)
            { fingerprint->wakeup_enabled = true; }
            else
            { fingerprint->wakeup_enabled = false; }

            hwlog_info("%s FP_IOC_CMD_SET_WAKELOCK_STATUS key =%d\n", __func__, key);

            break;
        case FP_IOC_CMD_SEND_SENSORID:
            if (copy_from_user(&sensor_id, argp, sizeof(sensor_id)))
            {
                hwlog_err("%s copy_from_user failed.\n", __func__);
                return -EFAULT;
            }

            fingerprint->sensor_id=sensor_id;
            hwlog_info("%s FP_IOC_CMD_SEND_SENSORID =%x\n", __func__,sensor_id);
            break;
        default:
            hwlog_err("%s error = -EFAULT.\n", __func__);
            error = -EFAULT;
            break;
    }

    return error;
}

static int fingerprint_release(struct inode* inode, struct file* file)
{
    hwlog_info("%s\n", __func__);
    return 0;
}

static const struct file_operations fingerprint_fops =
{
    .owner          = THIS_MODULE,
    .open            = fingerprint_open,
    .write            = fingerprint_write,
    .read             = fingerprint_read,
    .release         = fingerprint_release,
    .unlocked_ioctl = fingerprint_ioctl,
};

static int fingerprint_reset_gpio_init(struct fp_data* fingerprint)
{
    int error = 0;

    error = gpio_request(fingerprint->rst_gpio, "fingerprint_reset_gpio");

    if (error)
    {
        hwlog_err(" %s gpio_request (reset_gpio) failed.\n",__func__);
        error = -EINVAL;
        return error;
    }


    fingerprint->pctrl = devm_pinctrl_get(&fingerprint->spi->dev);

    if (IS_ERR(fingerprint->pctrl))
    {
        hwlog_err("%s devm_pinctrl_get failed\n", __func__);
        error = -EINVAL;
        return error;
    }

    fingerprint->pins_default = pinctrl_lookup_state(fingerprint->pctrl, "default");

    if (IS_ERR(fingerprint->pins_default))
    {
        hwlog_err("%s pinctrl_lookup_state failed\n", __func__);
        error = -EINVAL;
        goto err_pinctrl_put;
    }

    error = pinctrl_select_state(fingerprint->pctrl, fingerprint->pins_default);

    if (error < 0)
    {
        hwlog_err("%s pinctrl_select_state failed error=%d\n", __func__, error);
        error = -EINVAL;
        goto err_pinctrl_put;
    }

    error = gpio_direction_output(fingerprint->rst_gpio, 0);

    if (error)
    {
        hwlog_err("%s gpio_direction_output failed\n", __func__);
        return error;
    }

    return error;

err_pinctrl_put:
    devm_pinctrl_put(fingerprint->pctrl);
    return error;
}

/*
 * This Function will be called when tui init or exit
 * It will set tui_flg, when it is set to 1 this mean tui is displaying
 * Fingerprint driver cannot read rst gpio because gpio is in secure status.
 */
#if defined (CONFIG_TEE_TUI)
static int tui_fp_init(void *data, int secure)
{
    struct fp_data* fingerprint = g_fingerprint;
    if(!fingerprint){
        pr_err("%s:error:g_fingerprint is NULL\n", __func__);
        return -EINVAL;
    }
    //if fp rst gpio is in the same group with tui tp gpio then register the tui_fp_init
    if (fingerprint->irq_gpio/8 == tp_gpio_num/8) {
        if (secure) {
            mutex_lock(&tui_flg_lock);
            tui_flg = 1;
            mutex_unlock(&tui_flg_lock);
            disable_irq(gpio_to_irq(fingerprint->irq_gpio ));
            send_tui_msg_config(TUI_POLL_CFG_OK, 0, "fp");
        }
        else {
            mutex_lock(&tui_flg_lock);
            tui_flg = 0;
            mutex_unlock(&tui_flg_lock);
            enable_irq(gpio_to_irq(fingerprint->irq_gpio ));
        }
        printk("%s: tui_flg is %d\n", __func__, tui_flg);
    }
    return 0;
}
#endif
static int finerprint_get_module_info(struct fp_data* fingerprint)
{
    int error = 0;
    int pd_value = 0, pu_value = 0;

    error = gpio_request(fingerprint->moduleID_gpio, "fingerprint_moduleID_gpio");

    if (error)
    {
        hwlog_err("%s gpio_request failed\n", __func__);
        return error;
    }

    fingerprint->pctrl = devm_pinctrl_get(&fingerprint->spi->dev);

    if (IS_ERR(fingerprint->pctrl))
    {
        hwlog_err("%s devm_pinctrl_get failed\n", __func__);
        error = -EINVAL;
        return error;
    }

    fingerprint->pins_default = pinctrl_lookup_state(fingerprint->pctrl, "default");

    if (IS_ERR(fingerprint->pins_default))
    {
        hwlog_err("%s pinctrl_lookup_state pins_default failed\n", __func__);
        error = -EINVAL;
        goto error_pinctrl_put;
    }

    fingerprint->pins_idle = pinctrl_lookup_state(fingerprint->pctrl, "idle");

    if (IS_ERR(fingerprint->pins_idle))
    {
        hwlog_err("%s pinctrl_lookup_state pins_idle failed.\n", __func__);
        error = -EINVAL;
        goto error_pinctrl_put;
    }

    error = gpio_direction_input(fingerprint->moduleID_gpio);

    if (error < 0)
    {
        hwlog_err("%s set input mode error, error=%d.\n", __func__, error);
        error = -EINVAL;
        return error;
    }

    error = pinctrl_select_state(fingerprint->pctrl, fingerprint->pins_default);

    if (error < 0)
    {
        hwlog_err("%s set iomux normal error, error=%d.\n", __func__, error);
        error = -EINVAL;
        goto error_pinctrl_put;
    }

    mdelay(10);

    pu_value = gpio_get_value_cansleep(fingerprint->moduleID_gpio);
    hwlog_info("%s PU module id gpio = %d.\n", __func__, pu_value);

    error = gpio_direction_input(fingerprint->moduleID_gpio);

    if (error < 0)
    {
        hwlog_err("%s set input mode error, error=%d.\n", __func__, error);
        error = -EINVAL;
        return error;
    }

    error = pinctrl_select_state(fingerprint->pctrl, fingerprint->pins_idle);

    if (error < 0)
    {
        hwlog_err("%s set iomux normal error, error=%d.\n", __func__, error);
        error = -EINVAL;
        return error;
    }

    mdelay(10);

    pd_value = gpio_get_value_cansleep(fingerprint->moduleID_gpio);
    hwlog_info("%s PD module id gpio=%d.\n", __func__, pd_value);

    if (pu_value == pd_value)
    {
        if (pu_value == 1)
        {
            fingerprint->module_vendor_info = MODULEID_HIGT;
            hwlog_info("%s moduleID pin is HIGT.\n", __func__);
        }

        if (pd_value == 0)
        {
            fingerprint->module_vendor_info = MODULEID_LOW;
            hwlog_info("%s moduleID pin is LOW.\n", __func__);
        }
    }
    else
    {
        fingerprint->module_vendor_info = MODULEID_FLOATING;
        hwlog_info("%s moduleID pin is FLOATING.\n", __func__);
    }

    return error;

error_pinctrl_put:
    devm_pinctrl_put(fingerprint->pctrl);
    return error;
}

static int fingerprint_probe(struct spi_device* spi)
{
    struct device* dev = &spi->dev;
    int rc = 0;
    int irqf;
    struct device_node* np = dev->of_node;
    struct fp_data* fingerprint = devm_kzalloc(dev, sizeof(*fingerprint),
                                  GFP_KERNEL);
#if defined (CONFIG_HUAWEI_DSM)
	if(!fingerprint_dclient)
	{
        fingerprint_dclient = dsm_register_client(&dsm_fingerprint);
    }
#endif

    if (!fingerprint)
    {
        hwlog_err("%s failed to allocate memory for struct fp_data.\n", __func__);
        rc = -ENOMEM;
        goto exit;
    }

    hwlog_info("fingerprint driver v3.0 for Android M.");

    fingerprint->dev = dev;
    dev_set_drvdata(dev, fingerprint);
    fingerprint->spi = spi;

    if (!np)
    {
        hwlog_err("%s dev->of_node not found.\n", __func__);
        rc = -EINVAL;
        goto exit;
    }

    rc = fingerprint_get_dts_data(&spi->dev, fingerprint);

    if (rc)
    {
        hwlog_err("something wrong in fingerprint_get_dts_data error=%d\n", rc);
        rc = -EINVAL;
        goto exit;
    }

    fingerprint_get_navigation_adjustvalue(&spi->dev, fingerprint);

    rc = fingerprint_reset_gpio_init(fingerprint);

    if (rc)
    {
        hwlog_err("something wrong in reset gpio init error=%d\n", rc);
        rc = -EINVAL;
        goto exit;
    }
#if defined (CONFIG_TEE_TUI)
    //when tui init, the fingerprint should know, then the fingerprint driver will not get gpio value
    //Because the gpio is set to secure status
	register_tui_driver(tui_fp_init, "fp", NULL, 1);
#endif

    if (fingerprint->moduleID_gpio >= 0)
    {
        rc = finerprint_get_module_info(fingerprint);

        if (rc < 0)
        {
            hwlog_err("unknow vendor info error=%d\n", rc);
            goto exit;
        }
    }

    fingerprint->class = class_create(THIS_MODULE, FP_CLASS_NAME);


    rc = alloc_chrdev_region(&fingerprint->devno, 0, 1, FP_DEV_NAME);

    if (rc)
    {
        hwlog_err("%s alloc_chrdev_region failed rc=%d.\n", __func__, rc);
        goto exit;
    }

    fingerprint->device = device_create(fingerprint->class, NULL, fingerprint->devno,
                                        NULL, "%s", FP_DEV_NAME);

    cdev_init(&fingerprint->cdev, &fingerprint_fops);
    fingerprint->cdev.owner = THIS_MODULE;

    rc = cdev_add(&fingerprint->cdev, fingerprint->devno, 1);

    if (rc)
    {
        hwlog_err("%s cdev_add failed rc=%d.\n", __func__, rc);
        rc = -ENOMEM;
        goto exit;
    }

    fingerprint->input_dev = devm_input_allocate_device(dev);

    if (!fingerprint->input_dev)
    {
        hwlog_err("%s failed to allocate input device.\n", __func__);
        rc = -ENOMEM;
        goto exit;
    }


    fingerprint->input_dev->name = "fingerprint";
    /* Also register the key for wake up */
    input_set_capability(fingerprint->input_dev, EV_KEY, EVENT_UP);
    input_set_capability(fingerprint->input_dev, EV_KEY, EVENT_DOWN);
    input_set_capability(fingerprint->input_dev, EV_KEY, EVENT_LEFT);
    input_set_capability(fingerprint->input_dev, EV_KEY, EVENT_RIGHT);
    input_set_capability(fingerprint->input_dev, EV_KEY, EVENT_HOLD);
    input_set_capability(fingerprint->input_dev, EV_KEY, EVENT_CLICK);
    input_set_capability(fingerprint->input_dev, EV_KEY, EVENT_HOLD);
    input_set_capability(fingerprint->input_dev, EV_KEY, EVENT_DCLICK);
    set_bit(EV_KEY, fingerprint->input_dev->evbit);
    set_bit(EVENT_UP, fingerprint->input_dev->evbit);
    set_bit(EVENT_DOWN, fingerprint->input_dev->evbit);
    set_bit(EVENT_LEFT, fingerprint->input_dev->evbit);
    set_bit(EVENT_RIGHT, fingerprint->input_dev->evbit);
    set_bit(EVENT_CLICK, fingerprint->input_dev->evbit);
    set_bit(EVENT_HOLD, fingerprint->input_dev->evbit);
    set_bit(EVENT_DCLICK, fingerprint->input_dev->evbit);
    rc = input_register_device(fingerprint->input_dev);

    if (rc)
    {
        hwlog_err("%s input_register_device failed rc=%d.\n", __func__, rc);
        goto exit;
    }


    fingerprint->wakeup_enabled = false;

    fingerprint->pf_dev = platform_device_alloc(FP_DEV_NAME, -1);

    if (!fingerprint->pf_dev)
    {
        hwlog_err("%s failed fingerprint->pf_dev is NULL.\n", __func__);
        goto  exit;
    }

    rc = platform_device_add(fingerprint->pf_dev);

    if (rc)
    {
        hwlog_err("%s platform_device_add failed.\n", __func__);
        platform_device_del(fingerprint->pf_dev);
        goto  exit;
    }
    else
    {
        dev_set_drvdata(&fingerprint->pf_dev->dev, fingerprint);

        rc = sysfs_create_group(&fingerprint->pf_dev->dev.kobj, &attribute_group);

        if (rc)
        {
            hwlog_err("%s sysfs_create_group failed rc=%d.\n", __func__, rc);
            goto exit;
        }
    }

    irqf = IRQF_TRIGGER_RISING | IRQF_ONESHOT | IRQF_NO_SUSPEND;

    device_init_wakeup(dev, 1);
    wake_lock_init(&fingerprint->ttw_wl, WAKE_LOCK_SUSPEND, "fpc_ttw_wl");

    mutex_init(&fingerprint->lock);
    rc = devm_request_threaded_irq(dev, gpio_to_irq(fingerprint->irq_gpio),
                                   NULL, fingerprint_irq_handler, irqf,
                                   dev_name(dev), fingerprint);

    if (rc)
    {
        hwlog_err("%s failed could not request irq %d.\n", __func__, gpio_to_irq(fingerprint->irq_gpio));
        goto exit;
    }

    //dev_dbg(dev, "requested irq %d\n", gpio_to_irq(fingerprint->irq_gpio));

    /* Request that the interrupt should be wakeable */
    enable_irq_wake(gpio_to_irq( fingerprint->irq_gpio ) );
    fingerprint->wakeup_enabled = true;

    g_fingerprint = fingerprint;
    hwlog_info("%s OK.\n", __func__);

exit:
   #if defined (CONFIG_HUAWEI_DSM)
    if (rc && !dsm_client_ocuppy(fingerprint_dclient)) 
    {
	    dsm_client_record(fingerprint_dclient,"fingerprint_probe failed rc=%d!\n",rc);
	    dsm_client_notify(fingerprint_dclient, DSM_FINGERPRINT_PROBE_FAIL_ERROR_NO);
    }
   #endif
    return rc;
}

static int fingerprint_remove(struct spi_device* spi)
{
    struct  fp_data* fingerprint = dev_get_drvdata(&spi->dev);
    sysfs_remove_group(&fingerprint->pf_dev->dev.kobj, &attribute_group);
    cdev_del(&fingerprint->cdev);
    unregister_chrdev_region(fingerprint->devno, 1);
    input_free_device(fingerprint->input_dev);
    mutex_destroy(&fingerprint->lock);
    wake_lock_destroy(&fingerprint->ttw_wl);
    hwlog_info("%s\n", __func__);
    return 0;
}


/* -------------------------------------------------------------------- */
static int fingerprint_suspend(struct device* dev)
{
    hwlog_info("%s\n", __func__);
    return 0;
}
/* -------------------------------------------------------------------- */
static int fingerprint_resume(struct device* dev)
{
    hwlog_info("%s\n", __func__);
    return 0;
}

static const struct dev_pm_ops fingerprint_pm =
{
    .suspend = fingerprint_suspend,
    .resume = fingerprint_resume
};

static struct of_device_id fingerprint_of_match[] =
{
    { .compatible = "fpc,fingerprint", },
    {}
};
MODULE_DEVICE_TABLE(of, fingerprint_of_match);

static struct spi_driver fingerprint_driver =
{
    .driver = {
        .name	= "fingerprint",
        .owner	= THIS_MODULE,
        .of_match_table = fingerprint_of_match,
        .pm = &fingerprint_pm
    },
    .probe	= fingerprint_probe,
    .remove	= fingerprint_remove
};

static int __init fingerprint_init(void)
{
    int rc = spi_register_driver(&fingerprint_driver);

    if (!rc)
    { hwlog_info("%s OK\n", __func__); }
    else
    { hwlog_err("%s %d\n", __func__, rc); }

    return rc;
}

static void __exit fingerprint_exit(void)
{
    hwlog_info("%s\n", __func__);
    spi_unregister_driver(&fingerprint_driver);
#if defined (CONFIG_TEE_TUI)
	unregister_tui_driver("fp");
#endif
}

#ifdef CONFIG_LLT_TEST
struct LLT_fingprint_ops LLT_fingerprint = {
    .irq_get = irq_get,
    .fingerprint_irq_handler = fingerprint_irq_handler,
    .fingerprint_open = fingerprint_open,
    .fingerprint_get_irq_status = fingerprint_get_irq_status,
    .fingerprint_ioctl = fingerprint_ioctl,
    .fingerprint_reset_gpio_init = fingerprint_reset_gpio_init,
    .finerprint_get_module_info = finerprint_get_module_info,
    .fingerprint_probe = fingerprint_probe,
    .fingerprint_remove = fingerprint_remove,
};
#endif

module_init(fingerprint_init);
module_exit(fingerprint_exit);
EXPORT_SYMBOL(tui_fp_notify);

MODULE_LICENSE("GPL v2");
