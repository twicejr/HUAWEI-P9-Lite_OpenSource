/*
 * FileName: kernel/drivers/mtd/misc_nff.c
 * Description: complement MISC partition(or called block) read and write
 * in kernel.
 * Copyright (C) Hisilicon technologies Co., Ltd All rights reserved.
 * Revision history:
 */

#include <linux/device.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/misc_nff.h>
#include <linux/uaccess.h>
#include <linux/compat.h>

static struct MISC_struct *my_miscnff;
static struct class *miscnff_class;

/*
 * Function name:misc_read.
 * Discription:read misc partition.
 * Parameters:
 *          @ mtd:struct mtd_info pointer.
 *          @ from:emmc start block number that will be read.
 *          @ len:total bytes that will be read from emmc.
 *          @ buf:buffer used to store bytes that is read from emmc.
 */
static int misc_read(struct mtd_info *mtd, loff_t from, size_t len, u_char *buf)
{
	int ret = 0;
	size_t retlen;

	ret = mtd_read(mtd, from, len, &retlen, buf);
	if ((ret && (ret != -EUCLEAN) && (ret != -EBADMSG)) || (retlen != len)) {
		pr_err("[MISC][%s] Fatal error, read flash from = 0x%x, len = 0x%x, retlen = 0x%x, ret = 0x%x.\n",
		       __func__, (uint32_t)from, len, retlen, ret);
		ret = -ENODEV;
	} else
		ret = 0;

	return ret;
}

/*
 * Function name:misc_write.
 * Discription:write misc partition.
 * Parameters:
 *          @ mtd:struct mtd_info pointer.
 *          @ from:emmc start block number that will be written.
 *          @ len:total bytes that will be written from emmc.
 *          @ buf:given buffer whose bytes will be written to emmc.
 */
static int misc_write(struct mtd_info *mtd, loff_t from, size_t len, u_char *buf)
{
	int ret = 0;
	size_t retlen;

	if (!ret) {
		ret = mtd_write(mtd, from, len, &retlen, buf);
		if ((ret) || (retlen != len)) {
			pr_err("[MISC][%s] fatal error, write flash from = 0x%x, len = 0x%x, retlen = 0x%x, ret = 0x%x.\n",
			       __func__, (uint32_t)from, len, retlen, ret);

			ret = -ENODEV;
		}
	}
	mtd_sync(mtd);

	return ret;
}

/*
 * Function name:misc_open_ex.
 * Discription:open misc device.
 * return value:
 *          @ 0 - success.
 *          @ -1- failure.
 */
static int misc_open_ex(void)
{
	int ret = 0;
	struct mtd_info *mtd;
	struct MISC_struct *misc;

      pr_debug("[MISC][%s] enter MISC open!\n", __func__);

	/*the driver is not initialized successfully, return error*/
	if (NULL == my_miscnff) {
		ret = -ENODEV;
		pr_err("[MISC][%s]:driver is not initialized successfully.\n", __func__);
		goto out;
	} else
		misc = my_miscnff;

	/*if MISC has been initiallized,then skip following code in this function*/
	if (misc->initialized > 0) {
		pr_info("[MISC][%s]:MISC has been initialized!\n", __func__);
		goto out;
	}

	/*Get mtd handle according device's name*/
	mtd = get_mtd_device_nm(MISC_DEVICE_NAME);

	if (IS_ERR(mtd)) {
		pr_err("[MISC][%s]: get_mtd_device_nm error.\n", __func__);
		ret = PTR_ERR(mtd);
		goto out;
	}

	if (MTD_ABSENT == mtd->type) {
		put_mtd_device(mtd);
		ret = -ENODEV;
		goto out;
	}

	misc->mtd = mtd;

	misc->initialized = 1;

       pr_debug("[MISC][%s] MISC open ok!\n", __func__);

out:
	return ret;
}

/*
 * Function name:nve_open.
 * Discription:open misc device in terms of calling misc_open_ex().
 * return value:
 *          @ 0 - success.
 *          @ -1- failure.
 */
static int misc_open(struct inode *inode, struct file *file)
{
	int ret = 0;
	ret = misc_open_ex();
	return ret;
}


static int misc_close(struct inode *inode, struct file *file)
{
	return 0;
}

/*
 * Function name:misc_ioctl.
 * Discription:complement read or write MISC by terms of sending command-words.
 * return value:
 *          @ 0 - success.
 *          @ -1- failure.
 */
static long misc_ioctl(struct file *file, u_int cmd, u_long arg)
{
	int ret = 0;
	struct mtd_info *mtd = NULL;
	void __user *argp = (void __user *)arg;

	struct misc_info_user info;
	struct MISC_struct *misc = NULL;
        uint32_t offset = 1*1024*1024;

	if (NULL == my_miscnff) {
		pr_err("[MISC][%s]my_misc not initialized!\n", __func__);
		return -EFAULT;
	}

	misc = my_miscnff;

	mtd = misc->mtd;

	switch (cmd) {
		case MISCRW:
			if (copy_from_user(&info, argp, sizeof(struct misc_info_user))) {
				return -EFAULT;
			}

			if (MISC_READ == info.misc_operation) {
				/*read data from misc*/
				ret = misc_read(mtd, offset, MISC_PWSTATE_DATA_SIZE, info.misc_data);
				if(ret)
				{
					pr_err("[MISC][%s] misc_read error, ret = %d\n", __func__, ret);
					goto out;
				}

				/*send back to user*/
				if (copy_to_user(argp, &info, sizeof(struct misc_info_user))) {
					return -EFAULT;
				}
			} else {
				/*write data to misc*/
				ret = misc_write(mtd, offset, MISC_PWSTATE_DATA_SIZE, info.misc_data);
				if(ret)
				{
					pr_err("[MISC][%s] misc_write error, ret = %d\n", __func__, ret);
					goto out;
				}
			}
			break;
		default:
			pr_err("[MISC][%s] Unknow command!\n", __func__);
			ret = -ENOTTY;
			break;
	}

out:
	return ret;
}

#ifdef CONFIG_COMPAT
static long misc_compat_ioctl(struct file *file, u_int cmd, u_long arg)
{
	return misc_ioctl(file, cmd, (unsigned long) compat_ptr(arg));
}
#endif

static const struct file_operations misc_fops = {
	.owner             = THIS_MODULE,
	.unlocked_ioctl    = misc_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl		= misc_compat_ioctl,
#endif
	.open              = misc_open,
	.release           = misc_close,
};

static int __init init_misc(void)
{
	int error;
        void *miscdev;
	struct MISC_struct *misc = NULL;
       pr_debug("enter init_misc\n");
	my_miscnff = misc = kzalloc(sizeof(struct MISC_struct), GFP_KERNEL);

	if (misc == NULL) {
		pr_err("[MISC][%s]failed to allocate driver data in line %d.\n", __func__, __LINE__);
		return -ENOMEM;
	}

	memset (misc, 0x0, sizeof(struct MISC_struct));

	misc->misc_major_number = register_chrdev(0, "miscnff", &misc_fops);

	if (misc->misc_major_number < 0) {
		pr_err("[MISC]Can't allocate major number for Non-Volatile memory Extension device.\n");
		error = -EAGAIN;
		goto failed_free_driver_data;
	}

        miscnff_class = class_create(THIS_MODULE, "miscnff");

	if (IS_ERR(miscnff_class)) {
		pr_err("[MISC]Error creating miscnff class.\n");
		error = PTR_ERR(miscnff_class);
		goto failed_unregister_chrdev;
	}

       miscdev = device_create(miscnff_class, NULL, MKDEV(misc->misc_major_number, 0), NULL, "miscnff");
        if (IS_ERR(miscdev)) {
                pr_err("[MISC]Error creating miscnff class device.\n");
                error = PTR_ERR(miscdev);
                goto failed_destroy_class;
        }
        pr_debug("[MISC][%s]MISC init ok!\n", __func__);

	return 0;

failed_destroy_class:
        class_destroy(miscnff_class);
failed_unregister_chrdev:
        unregister_chrdev(misc->misc_major_number, "miscnff");
failed_free_driver_data:
	kfree(misc);
	my_miscnff = NULL;
	return error;
}

static void __exit cleanup_misc(void)
{
        device_destroy(miscnff_class, MKDEV(my_miscnff->misc_major_number, 0));
	class_destroy(miscnff_class);
	if (NULL != my_miscnff) {
		unregister_chrdev(my_miscnff->misc_major_number, "miscnff");
		kfree(my_miscnff);
		my_miscnff = NULL;
	}

	return;
}

module_init(init_misc);
module_exit(cleanup_misc);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("hisi-k3v200");
MODULE_DESCRIPTION("Direct character-device access to MISC devices");

