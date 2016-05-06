#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/fs.h>
#include <linux/delay.h>
/* standard error codes */
#include <linux/errno.h>

#include "video_config.h"


static video_sensor_config g_sensor_config = {0};

unsigned int video_get_chip_id(void)
{
	struct device_node *np = NULL;
    unsigned int chip_id = 0;

	np = of_find_compatible_node(NULL, NULL, "hisi,video_config");
	if (np ==NULL) {
		printk(KERN_ERR "the device node video_config is null\n");
		return -1;
	}

    if (of_property_read_u32(np, "chip_id", &chip_id)){
        printk(KERN_ERR "%s: chip_id read nothing.\n",__FUNCTION__);
    } else {
        printk(KERN_INFO "%s: chip_id %d\n",__FUNCTION__, chip_id);
    }

    return chip_id;
}

unsigned int video_get_board_type(void)
{
	struct device_node *np = NULL;
    unsigned int board_type = 0;

	np = of_find_compatible_node(NULL, NULL, "hisi,video_config");
	if (np ==NULL) {
		printk(KERN_ERR "the device node video_config is null\n");
		return -1;
	}

    if (of_property_read_u32(np, "board_type", &board_type)){
        printk(KERN_ERR "%s: board_type read nothing.\n", __FUNCTION__);
    } else {
        printk(KERN_INFO"%s: board_type %d\n",__FUNCTION__, board_type);
    }

    return board_type;
}

unsigned int video_get_support_isp(void)
{
	struct device_node *np = NULL;
    unsigned int support_isp = 1;

	np = of_find_compatible_node(NULL, NULL, "hisi,video_config");
	if (np ==NULL) {
		printk(KERN_ERR "the device node video_config is null\n");
		return -1;
	}

    if (of_property_read_u32(np, "support_isp", &support_isp)){
        printk(KERN_ERR "%s: support_isp read nothing.\n",__FUNCTION__);
    }
    printk(KERN_INFO "%s: support_isp %d\n",__FUNCTION__, support_isp);

    return support_isp;
}

unsigned int video_get_support_vpu(void)
{
	struct device_node *np = NULL;
    unsigned int support_vpu = 1;

	np = of_find_compatible_node(NULL, NULL, "hisi,video_config");
	if (np ==NULL) {
		printk(KERN_ERR "the device node video_config is null\n");
		return -1;
	}

    if (of_property_read_u32(np, "support_vpu", &support_vpu)){
        printk(KERN_ERR "%s: support_vpu read nothing.\n",__FUNCTION__);
    }
    printk(KERN_INFO "%s: support_vpu %d\n",__FUNCTION__, support_vpu);

    return support_vpu;
}

unsigned int video_get_support_jpu(void)
{
	struct device_node *np = NULL;
    unsigned int support_jpu = 1;

	np = of_find_compatible_node(NULL, NULL, "hisi,video_config");
	if (np ==NULL) {
		printk(KERN_ERR "the device node video_config is null\n");
		return -1;
	}

    if (of_property_read_u32(np, "support_jpu", &support_jpu)){
        printk(KERN_ERR "%s: support_jpu read nothing.\n",__FUNCTION__);
    }
    printk(KERN_INFO "%s: support_jpu %d\n",__FUNCTION__, support_jpu);

    return support_jpu;
}

unsigned int video_get_primary_sensor_flip_type(void)
{
    return g_sensor_config.primary_sensor_flip_type;
}

unsigned int video_get_secondary_sensor_flip_type(void)
{
    return g_sensor_config.secondary_sensor_flip_type;
}

unsigned int video_check_suspensory_camera(char *sensor_name)
{
    struct device_node *np = NULL;
    unsigned int type = 0;

    np = of_find_compatible_node(NULL, NULL, "hisi,hisi_sensor");
    if (np ==NULL) {
        printk(KERN_ERR "the device node hisi_sensor is null\n");
        return -1;
    }

    if (of_property_read_u32(np, sensor_name, &type)){
        printk(KERN_ERR "%s: %s read nothing.\n",__FUNCTION__, sensor_name);
    } else {
        printk(KERN_INFO "%s: %s: %d.\n",__FUNCTION__, sensor_name, type);
    }

    return type;
}

int video_get_product_name(const char ** name)
{
    struct device_node *np = NULL;

    np = of_find_compatible_node(NULL, NULL, "hisi,hisi_sensor");
    if (np ==NULL) {
        printk(KERN_ERR "the device node hisi_sensor is null\n");
        return -1;
    }

    if(of_property_read_string(np, "product",name)){
        printk(KERN_ERR "%s: read nothing.\n",__FUNCTION__);
        return -1;
    } else {
        printk(KERN_INFO "%s: %s\n",__FUNCTION__, *name);
    }

    return 0;
}

static int video_get_sensor_config(void)
{
	struct device_node *sensor_np = NULL;

	sensor_np = of_find_compatible_node(NULL, NULL, "hisi,hisi_sensor");
	if (sensor_np ==NULL) {
		printk(KERN_ERR "the device node hisi_sensor is null\n");
		return -1;
	}

    if (of_property_read_u32(sensor_np, "primary_sensor_flip_type", &g_sensor_config.primary_sensor_flip_type)){
        printk(KERN_ERR "%s: primary_sensor_flip_type read nothing.\n", __FUNCTION__);
    } else {
        printk(KERN_INFO"%s: primary_sensor_flip_type %d\n", __FUNCTION__, g_sensor_config.primary_sensor_flip_type);
    }

    if (of_property_read_u32(sensor_np, "secondary_sensor_flip_type", &g_sensor_config.secondary_sensor_flip_type)){
        printk(KERN_ERR "%s: secondary_sensor_flip_type read nothing.\n", __FUNCTION__);
    } else {
        printk(KERN_INFO"%s: secondary_sensor_flip_type %d\n", __FUNCTION__, g_sensor_config.secondary_sensor_flip_type);
    }

    return 0;
}


static int __init video_config_init(void)
{
    printk(KERN_INFO "begin video_config_init!");
    video_get_sensor_config();
    return 0;
}

static void __exit video_config_exit(void)
{
    printk(KERN_INFO "video_config_exit\n");

    return;
}

EXPORT_SYMBOL(video_get_chip_id);
EXPORT_SYMBOL(video_get_board_type);
EXPORT_SYMBOL(video_get_primary_sensor_flip_type);

module_init(video_config_init);
module_exit(video_config_exit);

MODULE_AUTHOR("balong hisilicon, Inc.");
MODULE_DESCRIPTION("common interface of video config for vpu¡¢jpeg¡¢isp driver");
MODULE_LICENSE("GPL");

