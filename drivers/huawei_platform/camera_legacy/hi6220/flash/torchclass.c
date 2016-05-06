
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/leds.h>

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "K3_TORCH"
#endif
//#define DEBUG_DEBUG 1
#include "mini_cam_log.h"

typedef  struct  _torch_class {
	struct class *classptr;
	struct device *pDevice;
}torch_class;

static torch_class torch;

//static int brightness_level = 0;
static dev_t devnum;

#define TORCH_LED    "torch_led"

#define MAX_BRIGHTNESS_FORMMI   (9)

struct led_classdev mmi_led_cdev;

int register_torch_led(struct device_attribute *attr);

static int __init torch_module_init(void)
{
	int ret;
       ret = alloc_chrdev_region(&devnum, 0, 1, TORCH_LED);
	if(ret)
	{
		printk("error %s fail to alloc a dev_t!!!\n",__func__);
		return -1;
	}

	torch.classptr= class_create(THIS_MODULE, "torch");
	if (IS_ERR(torch.classptr)) {
		pr_info("class_create failed %d\n", ret);
		ret = PTR_ERR(torch.classptr);
		return -1;
	}

	torch.pDevice  = device_create(torch.classptr, NULL, devnum,NULL,"%s",TORCH_LED);
	if (IS_ERR(torch.pDevice)) {
		pr_info("class_device_create failed %s \n", TORCH_LED);
		ret = PTR_ERR(torch.pDevice);
		return -1;
	}
	return 0;
}

int register_torch_led(struct device_attribute *attr)
{
	int ret = 0;

	ret = device_create_file(torch.pDevice,attr);
	if (ret)
	{
		pr_info("torch_led device_create_file failed %d\n", ret);
		return -1;
	}

	return 0;
}

EXPORT_SYMBOL(register_torch_led);

int mmi_register_torch_led(void	(*func)(struct led_classdev *led_cdev,
					  enum led_brightness brightness), struct device_attribute *attr)
{
    int rc;
	
	pr_info("enter %s", __func__);
	
	mmi_led_cdev.name = "torch";
	mmi_led_cdev.max_brightness = MAX_BRIGHTNESS_FORMMI;
	mmi_led_cdev.brightness_set = func;
	
    rc = led_classdev_register(NULL, &mmi_led_cdev);
	
	if (rc < 0) {
		pr_info("%s failed to register torch classdev.", __func__);
		return -1;
	}
	return 0;
}

EXPORT_SYMBOL(mmi_register_torch_led);
static void __exit torch_module_deinit(void)
{
	device_destroy(torch.classptr, devnum);
	class_destroy(torch.classptr);
	unregister_chrdev_region(devnum, 1);
}

module_init(torch_module_init);
module_exit(torch_module_deinit);
MODULE_AUTHOR("Jiezhou");
MODULE_DESCRIPTION("Torch led virtul device");
MODULE_LICENSE("GPL");
