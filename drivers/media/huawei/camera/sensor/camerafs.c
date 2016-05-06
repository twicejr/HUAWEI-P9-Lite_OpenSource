
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/fs.h>
#include "cam_log.h"
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/rpmsg.h>
#include <linux/delay.h>
#include <linux/spinlock.h>


typedef  struct  _camerafs_class {
	struct class *classptr;
	struct device *pDevice;
}camerafs_class;

typedef  struct  _camerafs_ois_class {
    struct class *classptr;
    struct device *pDevice;
}camerafs_ois_class;

static camerafs_ois_class camerafs_ois;

static camerafs_class camerafs;

//static int brightness_level = 0;
static dev_t devnum;
static dev_t osi_devnum;

#define CAMERAFS_NODE    "node"
#define CAMERAFS_OIS_NODE "ois"

//#define MAX_BRIGHTNESS_FORMMI   (9)

wait_queue_head_t ois_que;
static int ois_check = 0;
#define OIS_TEST_TIMEOUT        (HZ * 8)
#ifdef DEBUG_HISI_CAMERA
static int ois_done = 0;
static int cross_width = -1;
static int cross_height = -1;
static int ic_num = -1;
#endif
spinlock_t pix_lock = SPIN_LOCK_UNLOCKED;

int register_camerafs_ois_attr(struct device_attribute *attr);
#ifdef DEBUG_HISI_CAMERA
static ssize_t hw_ois_aging_store(struct device *dev,
struct device_attribute *attr, const char *buf, size_t count)
{
    int done_flag;
    if(sscanf(buf, "%d", &done_flag) <=0)
    {
        cam_info("write data done_flag error");
        return 0;
    }
    cam_info("%s: done_flag = %d", __func__, done_flag);
    ois_done = done_flag;
    wake_up_interruptible(&ois_que);
    return count;
}
#endif
#ifdef DEBUG_HISI_CAMERA
static ssize_t hw_ois_aging_show(struct device *dev,
struct device_attribute *attr,char *buf)
{
    int ret = -1;

    cam_info("Enter: %s", __func__);
    ois_done = 0;
    //wait for start command
    msleep(50);
    ret = wait_event_interruptible_timeout(ois_que, ois_done != 0, OIS_TEST_TIMEOUT);
    if(ret <= 0) {
        cam_warn("%s: wait ois signal timeout", __func__);
    }
    ret = scnprintf(buf, PAGE_SIZE, "%d", ois_done);

    return ret;
}
#endif
#ifdef DEBUG_HISI_CAMERA
static struct device_attribute hw_ois_aging =
__ATTR(ois_aging, 0664, hw_ois_aging_show, hw_ois_aging_store);
#endif
static ssize_t hw_ois_check_store(struct device *dev,
struct device_attribute *attr, const char *buf, size_t count)
{
    int done_flag;
    if(sscanf(buf, "%d", &done_flag) <= 0)
    {
        cam_info("%s: write data done_flag error", __func__);
        return 0;
    }
    cam_info("%s: done_flag = %d", __func__, done_flag);
    ois_check = done_flag;
    wake_up_interruptible(&ois_que);
    return count;
}

static ssize_t hw_ois_check_show(struct device *dev,
struct device_attribute *attr,char *buf)
{
    int ret = -1;

    cam_info("Enter: %s", __func__);
    ois_check = 0;
    //wait for start command
    msleep(50);
    ret = wait_event_interruptible_timeout(ois_que, ois_check != 0, OIS_TEST_TIMEOUT);
    if(ret <= 0) {
        cam_warn("%s: wait ois signal timeout", __func__);
    }
    ret = scnprintf(buf, PAGE_SIZE, "%d", ois_check);

    return ret;
}

static struct device_attribute hw_ois_check =
__ATTR(ois_check, 0664, hw_ois_check_show, hw_ois_check_store);

// add for ois mmi test
#ifdef DEBUG_HISI_CAMERA
static ssize_t hw_ois_test_mmi_show(struct device *dev,
struct device_attribute *attr,char *buf)
{
    int ret = -1;

    cam_info("Enter: %s", __func__);
    spin_lock(&pix_lock);
    ret = scnprintf(buf, PAGE_SIZE, "%d,%d\n",
            cross_width, cross_height);
    cross_width = -1;
    cross_height = -1;
    spin_unlock(&pix_lock);

    return ret;
}
#endif
#ifdef DEBUG_HISI_CAMERA
static ssize_t hw_ois_test_mmi_store(struct device *dev,
struct device_attribute *attr, const char *buf, size_t count)
{
    int width, height;

    spin_lock(&pix_lock);

    if(sscanf(buf, "%d%d", &width, &height) <= 0)
    {
        cam_info("%s: write data width height error", __func__);
        spin_unlock(&pix_lock);
        return 0;
    }

    cross_width = width;
    cross_height = height;
    spin_unlock(&pix_lock);
    cam_info("Enter: %s (%d, %d).", __func__, cross_width, cross_height);

    return count;
}
#endif
#ifdef DEBUG_HISI_CAMERA
static struct device_attribute hw_ois_pixel =
__ATTR(ois_pixel, 0664, hw_ois_test_mmi_show, hw_ois_test_mmi_store);
#endif
#ifdef DEBUG_HISI_CAMERA
static ssize_t hw_ois_ic_num_show(struct device *dev,
struct device_attribute *attr,char *buf)
{
    int ret = -1;

    cam_info("Enter: %s", __func__);
    spin_lock(&pix_lock);
    ret = scnprintf(buf, PAGE_SIZE, "%d\n", ic_num);
    spin_unlock(&pix_lock);

    return ret;
}
#endif
#ifdef DEBUG_HISI_CAMERA
static ssize_t hw_ois_ic_num_store(struct device *dev,
struct device_attribute *attr, const char *buf, size_t count)
{
    int icnum;

    spin_lock(&pix_lock);

    if(sscanf(buf, "%d", &icnum) <= 0)
    {
        cam_info("%s: write data icnum error", __func__);
        spin_unlock(&pix_lock);
        return 0;
    }

    ic_num = icnum;
    spin_unlock(&pix_lock);
    cam_info("Enter: %s (%d).", __func__, ic_num);

    return count;
}
#endif
#ifdef DEBUG_HISI_CAMERA
static struct device_attribute hw_ois_icnum =
__ATTR(ois_icnum, 0664, hw_ois_ic_num_show, hw_ois_ic_num_store);
#endif
int register_camerafs_attr(struct device_attribute *attr);

static int __init camerafs_module_init(void)
{
	int ret;
        
        camerafs.classptr = NULL;
        camerafs.pDevice = NULL;
        spin_lock_init(&pix_lock);

       ret = alloc_chrdev_region(&devnum, 0, 1, CAMERAFS_NODE);
       ret = alloc_chrdev_region(&osi_devnum, 0, 1, CAMERAFS_OIS_NODE);
       if(ret)
       {
           printk("error %s fail to alloc a dev_t!!!\n",__func__);
           return -1;
       }

	camerafs.classptr= class_create(THIS_MODULE, "camerafs");
    camerafs_ois.classptr = camerafs.classptr;
	if (IS_ERR(camerafs.classptr)) {
		cam_err("class_create failed %d\n", ret);
		ret = PTR_ERR(camerafs.classptr);
		return -1;
	}

	camerafs.pDevice  = device_create(camerafs.classptr, NULL, devnum,NULL,"%s",CAMERAFS_NODE);
    camerafs_ois.pDevice = device_create(camerafs_ois.classptr, NULL, osi_devnum, NULL, "%s", CAMERAFS_OIS_NODE);

	if (IS_ERR(camerafs.pDevice)) {
		cam_err("class_device_create failed %s \n", CAMERAFS_NODE);
		ret = PTR_ERR(camerafs.pDevice);
		return -1;
	}

#ifdef DEBUG_HISI_CAMERA
        register_camerafs_ois_attr(&hw_ois_aging);
        register_camerafs_ois_attr(&hw_ois_pixel);
        register_camerafs_ois_attr(&hw_ois_icnum);
#endif
        register_camerafs_ois_attr(&hw_ois_check);

        init_waitqueue_head(&ois_que);
        cam_info("%s end",__func__);
	return 0;
}

int register_camerafs_attr(struct device_attribute *attr)
{
	int ret = 0;

	ret = device_create_file(camerafs.pDevice,attr);
	if (ret<0)
	{
              cam_err("camera fs creat dev attr[%s] fail", attr->attr.name);
		return -1;
	}
       cam_info("camera fs creat dev attr[%s] OK", attr->attr.name);
	return 0;
}

int register_camerafs_ois_attr(struct device_attribute *attr)
{
    int ret = 0;

    ret = device_create_file(camerafs_ois.pDevice,attr);
    if (ret<0)
    {
        cam_err("camera oiscreat dev attr[%s] fail", attr->attr.name);
        return -1;
	}
    cam_info("camera ois creat dev attr[%s] OK", attr->attr.name);
    return 0;
}

EXPORT_SYMBOL(register_camerafs_attr);

static void __exit camerafs_module_deinit(void)
{
	device_destroy(camerafs.classptr, devnum);
    device_destroy(camerafs_ois.classptr, osi_devnum);
	class_destroy(camerafs.classptr);
	unregister_chrdev_region(devnum, 1);
    unregister_chrdev_region(osi_devnum, 1);
}

module_init(camerafs_module_init);
module_exit(camerafs_module_deinit);
MODULE_AUTHOR("Jiezhou");
MODULE_DESCRIPTION("Camera fs virtul device");
MODULE_LICENSE("GPL");
