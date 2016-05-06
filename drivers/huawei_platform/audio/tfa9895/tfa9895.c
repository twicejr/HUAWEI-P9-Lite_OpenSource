#include <linux/i2c.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/input.h>
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/i2c-dev.h>
#include <huawei_platform/log/hw_log.h>


#include "tfa9895.h"

#define HWLOG_TAG tfa9895
HWLOG_REGIST();

static struct i2c_client *this_client;
static struct mutex tfa9895_lock;

static int tfa9895_i2c_read(char *rxData, int length)
{
    int ret = 0;
    struct i2c_msg msg[] = {
        {
            .addr  = this_client->addr,
            .flags = I2C_M_RD,
            .len   = length,
            .buf   = rxData,
        },
    };

    ret = i2c_transfer(this_client->adapter, msg, 1);
    if (0 > ret) {
        hwlog_err("%s: transfer error %d", __FUNCTION__, ret);
        return ret;
    }

    return ret;
}

static int tfa9895_i2c_write(char *txData, int length)
{
    int ret = 0;

    struct i2c_msg msg[] = {
        {
            .addr = this_client->addr,
            .flags = 0,
            .len = length,
            .buf = txData,
        },
    };

    ret = i2c_transfer(this_client->adapter, msg, 1);
    if (0 > ret) {
        hwlog_err("%s: transfer error %d", __FUNCTION__, ret);
        return ret;
    }

    return ret;
}

static int tfa9895_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int tfa9895_release(struct inode *inode, struct file *file)
{
    return 0;
}

static ssize_t tfa9895_read(struct file *file, char __user *buf,
         size_t nbytes, loff_t *pos)
{
	int ret = 0;
	void *kern_buf;
	kern_buf = kmalloc(nbytes, GFP_KERNEL);
	if (!kern_buf) {
         hwlog_err("Failed to allocate buffer\n");
         return -ENOMEM;
    }

    ret = tfa9895_i2c_read((char *)kern_buf, nbytes);
    if (0 > ret) {
        hwlog_err("%s: i2c read error %d", __FUNCTION__, ret);
	    kfree(kern_buf);
        return ret;
    }

	if (copy_to_user((void  __user *)buf, kern_buf,  nbytes)) {
         kfree(kern_buf);
         return -EFAULT;
    }
	kfree(kern_buf);
    return nbytes;
}

static ssize_t tfa9895_write(struct file *file,
		const char __user *buf, size_t nbytes, loff_t *ppos)
{
    int ret=0;
    void *kern_buf;

	kern_buf = kmalloc(nbytes, GFP_KERNEL);
	if (!kern_buf) {
         hwlog_err("Failed to allocate buffer\n");
         return -ENOMEM;
    }

    if (copy_from_user(kern_buf, (void  __user *)buf, nbytes)) {
         kfree(kern_buf);
         return -EFAULT;
    }

    ret = tfa9895_i2c_write((char *)kern_buf, nbytes);
    if (0 > ret) {
        hwlog_err("%s: i2c write error %d", __FUNCTION__, ret);
        return ret;
    }

	kfree(kern_buf);
    return nbytes;
}


static long tfa9895_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
     struct i2c_client *client = file->private_data;

     switch (cmd) {
     case I2C_SLAVE:
     case I2C_SLAVE_FORCE:
               /* NOTE:  devices set up to work with "new style" drivers
               * can't use I2C_SLAVE, even when the device node is not
               * bound to a driver.  Only I2C_SLAVE_FORCE will work.
               *
               * Setting the PEC flag here won't affect kernel drivers,
               * which will be using the i2c_client node registered with
               * the driver model core.  Likewise, when that client has
               * the PEC flag already set, the i2c-dev driver won't see
               * (or use) this setting.
               */
               if ((arg > 0x3ff) ||
                   (((client->flags & I2C_M_TEN) == 0) && arg > 0x7f))
                        return -EINVAL;
               /*
               if (cmd == I2C_SLAVE && i2cdev_check_addr(client->adapter, arg))
                        return -EBUSY;
               */
               /* REVISIT: address could become busy later */
               this_client->addr = arg;
               return 0;
     default:
               /* NOTE:  returning a fault code here could cause trouble
               * in buggy userspace code.  Some old kernel bugs returned
               * zero in this case, and userspace code might accidentally
               * have depended on that bug.
               */
               return -ENOTTY;
     }
     return 0;
}


static const struct file_operations tfa9895_fops = {
    .owner          = THIS_MODULE,
    .open           = tfa9895_open,
    .release        = tfa9895_release,
	.read           = tfa9895_read,
	.write          = tfa9895_write,
    .unlocked_ioctl = tfa9895_ioctl,
};

static struct miscdevice tfa9895_device = {
    .minor  = MISC_DYNAMIC_MINOR,
    .name   = TFA9895_NAME,
    .fops   = &tfa9895_fops,
};

static struct of_device_id tfa9895_i2c_of_match[] = {
	{ .compatible = "huawei,tfa9895", },
	{},
};
MODULE_DEVICE_TABLE(of, tfa9895_i2c_of_match);


static int tfa9895_probe(struct i2c_client *client,const struct i2c_device_id *id)
{
    int ret = 0;

    this_client = client;
	hwlog_info("%s: enter, device '%s' , addr %x\n", __func__, id->name, this_client->addr);

    if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
        hwlog_err("%s: i2c check functionality error", __FUNCTION__);
        ret = -ENODEV;
		return ret;
    }


    ret = misc_register(&tfa9895_device);
    if (ret){
        hwlog_err("%s: tfa9895_device register failed (%d)", __FUNCTION__, ret);
    }


    return ret;
}

static int tfa9895_remove(struct i2c_client *client)
{
    misc_deregister(&tfa9895_device);
	i2c_set_clientdata(client, NULL);
    return 0;
}

static const struct i2c_device_id tfa9895_id[] = {
	{ "tfa9895", 0 },
    { }
};
MODULE_DEVICE_TABLE(i2c, tfa9895_id);

static struct i2c_driver tfa9895_driver = {
    .probe      = tfa9895_probe,
    .remove     = tfa9895_remove,
    .id_table   = tfa9895_id,
    .driver     = {
        .name = TFA9895_NAME,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(tfa9895_i2c_of_match),
    },
};

static int __init tfa9895_init(void)
{
    hwlog_info("%s", __FUNCTION__);
    mutex_init(&tfa9895_lock);
    return i2c_add_driver(&tfa9895_driver);
}

static void __exit tfa9895_exit(void)
{
    i2c_del_driver(&tfa9895_driver);
}

module_init(tfa9895_init);
module_exit(tfa9895_exit);

MODULE_DESCRIPTION("TFA9895 I2C driver");
MODULE_LICENSE("GPL");
