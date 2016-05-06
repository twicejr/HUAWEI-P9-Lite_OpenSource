#include <linux/slab.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#include <mach/pwrctrl/pwrctrl_mca.h>

#define MCADEV_WRITE_TIME_OUT     (1000)

struct mcadev_wblock
{
    int cmd_id;
    union mca_udata_req udata;
};

static int mcadev_open(struct inode *inode, struct file *filp)
{
	filp->private_data = kzalloc(sizeof(union mca_udata_req), GFP_KERNEL);

	if (!filp->private_data)
    	return -EPERM;

	return 0;
}

static int mcadev_release(struct inode *inode, struct file *filp)
{
	if(filp->private_data)
    	kfree(filp->private_data);

	return 0;
}

static ssize_t mcadev_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	union mca_udata_rsp* rsp_buf = filp->private_data;

	if (!rsp_buf)
		return -EINVAL;

	return simple_read_from_buffer(buf, count, f_pos, rsp_buf, sizeof(union mca_udata_rsp));
}

static ssize_t mcadev_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
    union mca_udata_rsp* rsp_buf = filp->private_data;
    struct mcadev_wblock  wblock;

    memset(&wblock, 0, sizeof(struct mcadev_wblock));

    if(!rsp_buf)
        return -EFAULT;

	if (count > sizeof(struct mcadev_wblock))
	    return -EINVAL;

    if (copy_from_user(&wblock, buf, count))
		return -EFAULT;
#if 0
    if(mca_send(wblock.cmd_id, wblock.udata, rsp_buf, MCADEV_WRITE_TIME_OUT));
        return -EFAULT;
#endif
	return count;
}

static const struct file_operations mcadev_fops = {
	.write = mcadev_write,
	.read = mcadev_read,
	.open = mcadev_open,
	.release = mcadev_release,
};

static struct miscdevice mcadev_miscdev = {
    .name = "mca",
    .minor = MISC_DYNAMIC_MINOR,
    .fops = &mcadev_fops,
};

static int __init mcadev_init(void)
{
	return misc_register(&mcadev_miscdev);
}

late_initcall(mcadev_init);