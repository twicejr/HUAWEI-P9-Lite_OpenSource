

#include <linux/module.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <linux/mm.h>
#include <asm/system.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/unistd.h>
#include <linux/time.h>
#include <linux/delay.h>
#include "extisp_node.h"
#include "cam_log.h"
//#include "camera_agent.h"

#define DEVICE_MAJOR 500 /*Ö÷Éè±¸ºÅ*/
static int    mispcdev_Major = 0;
static int    mispcdev_Min = 0;


struct mispcdev
{
	struct cdev cdev;
};

struct mispcdev *misp_cdevp;
static struct class *misp_device;
static dev_t devno = MKDEV(DEVICE_MAJOR,0);
static void __exit misp_cdev_exit(void)
{
	cam_info("%s",__func__);
	cdev_del(&misp_cdevp->cdev);
	kfree(misp_cdevp);
	unregister_chrdev_region(MKDEV(mispcdev_Major, 0), 1);
}

static int misp_cdev_open(struct inode *inode,struct file *filp)
{
	cam_info("%s",__func__);
	filp->private_data = misp_cdevp;
	return 0;
}

static ssize_t misp_cdev_write(struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{
	char buff[1] = {-1};
	copy_from_user(buff,buf,1);
	cam_info("buff[0] = %c",buff[0]);
	if(-1 == buff[0]) {
		cam_err("without cmd");
		return -1;
	}else if('0' == buff[0]) {
		cam_info("open denoise");	
//		camera_agent_set_denoise_mode(1);
	}else if('1' == buff[0]) {
		cam_info("close denoise");
//		camera_agent_set_denoise_mode(0);
	}
	
	return 0;	
}
static long misp_cdev_ioctl( struct file *filp, unsigned int cmd, unsigned long arg)
{
	cam_info("enter %s cmd = %u",__func__,cmd);
	int ret =0;
	int ioarg = 0;
	int index_cmd = 0;
	if(_IOC_TYPE(cmd)!=MINIISP_CMD_MAGIC)
	{
		cam_info("MAGIC error");
		return -EINVAL;
	}
	switch(cmd)
	{
		case MINIISP_CMD_CLOSE_DENOISE:
//			camera_agent_set_denoise_mode(0);
			cam_info("MINIISP_CMD_CLOSE_DENOISE OK");
			break;
		case MINIISP_CMD_OPEN_DENOISE:
//			camera_agent_set_denoise_mode(1);
			cam_info("MINIISP_CMD_OPEN_DENOISE OK");
			break;
		default:
			cam_info("NO CMD");
			return -EINVAL;
	}
	return ret;
}


static const struct file_operations misp_cdev_file_operations =
{
	.owner = THIS_MODULE,
	.open = misp_cdev_open,
	.write = misp_cdev_write,
	.unlocked_ioctl = misp_cdev_ioctl,
};

static void misp_cdev_setup(struct mispcdev *dev,int index,dev_t  *devp)
{
	mispcdev_Major = MAJOR(*devp);
	mispcdev_Min = MINOR(*devp);
	cam_info("misp_cdev_setup mispcdev_Major = %d mispcdev_Min = %d",mispcdev_Major,mispcdev_Min);
	int err;
	cdev_init(&dev->cdev,&misp_cdev_file_operations);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &misp_cdev_file_operations;
	err = cdev_add(&dev->cdev,*devp,1);
	if(err)
	{
		cam_info("cdev add error");
	}
	 misp_device = class_create(THIS_MODULE,"misp_device0");
	//device_create(misp_device,NULL,*devp,NULL,"mispchardevice""%d",MINOR(*devp));	
	device_create(misp_device, NULL, devno,NULL,"%s","misp_cdev");
}

static int __init misp_cdev_init(void)
{
	cam_info("enter %s",__func__);
	int ret;
	
	ret = alloc_chrdev_region(&devno,0,1,"misp_cdev");
	mispcdev_Major = MAJOR(devno);
	mispcdev_Min = MINOR(devno);
	cam_info("misp_cdev_init mispcdev_Major = %d mispcdev_Min = %d",mispcdev_Major,mispcdev_Min);
	if(ret<0)
	{
		cam_info("register_chrdev_region error %d",ret);
		return -1;
	}
	misp_cdevp = kmalloc(sizeof(struct mispcdev),GFP_KERNEL);
	if(!misp_cdevp)
	{
		ret = -ENOMEM;
		goto fail_malloc;
	}
	memset(misp_cdevp,0,sizeof(struct mispcdev));
	misp_cdev_setup(misp_cdevp,0,&devno);
	return 0;
fail_malloc:
	unregister_chrdev_region(devno,1);
	return ret;
}
MODULE_AUTHOR("DingWei");
MODULE_LICENSE("Huawei/GPL");
module_init(misp_cdev_init);
module_exit(misp_cdev_exit);

