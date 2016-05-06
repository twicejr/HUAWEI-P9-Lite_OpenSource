 

#include <linux/compiler.h>
#include <linux/gpio.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/rpmsg.h>
#include <uapi/linux/histarisp.h>
#include <media/huawei/camera.h>

typedef enum _voltage_e
{
    LOW = 0,
    HIGH = 1,
} voltage_e;

static LIST_HEAD(g_sensor_info);

extern int hw_is_fpga_board(void);
extern int hw_sensor_power_on(void *psensor);
extern int hw_sensor_power_off(void *psensor);

static int hw_sensor_gpio_config(gpio_type pin_type, hwsensor_board_info *sensor_info, int state)
{
    int rc = -1;

    if(0 == sensor_info->gpios[pin_type].gpio) {
		printk("gpio type[%d] is not actived\n", pin_type);
		return rc;
	}

    rc = gpio_request(sensor_info->gpios[pin_type].gpio, NULL);
	if(rc < 0) {
		printk("failed to request gpio[%d]\n", sensor_info->gpios[pin_type].gpio);
		return rc;
	}
    
	rc = gpio_direction_output(sensor_info->gpios[pin_type].gpio, state);
	if(rc < 0) {
		printk("failed to control gpio[%d]\n", sensor_info->gpios[pin_type].gpio);
	}

	gpio_free(sensor_info->gpios[pin_type].gpio);

	return rc;
}

static int check_sensor_name(int index, const char *name, hwsensor_board_info **sensor_info)
{
    hwsensor_board_info *tmp_sensor_info = NULL;
    unsigned int flag = 0;
	printk("check_sensor_name: \n");
	if(list_empty_careful(&g_sensor_info)){
		printk("sensor list is empty! \n");
		return -1;
	}
		
    list_for_each_entry(tmp_sensor_info, &g_sensor_info, link)
    {
        if((!strcmp(tmp_sensor_info->sensor_name, name)) 
			&& (tmp_sensor_info->camera_id == index))
        {
            printk("[%s]find sensor %s@%d that is on the ISP board\n", 
				__func__, tmp_sensor_info->sensor_name, tmp_sensor_info->camera_id);
            flag = 1;
            break;
        }
    }

    if(0 == flag)
    {   
        printk("[%s] not find sensor %s on the board\n", __func__, name);
        return -EINVAL;
    }
    *sensor_info = tmp_sensor_info;
    return 0;
}

int rpmsg_sensor_register(struct platform_device *pdev, void *psensor)
{
    struct device_node *of_node = pdev->dev.of_node;
	int rc = 0;
	u32 i, index = 0;
	char *gpio_tag = NULL;
    hwsensor_board_info *sensor_info = NULL;
	const char *gpio_ctrl_types[GPIO_MAX] =
		{"reset", "powerdown", "dphy_txrxz", "dphy_rstzcal", "cam_1v05_en",
		"cam_1v2_en", "cam_1v8_en", "cam_2v85_en", "cam_vcm_2v85_en", "cam_vcm_power"};

    sensor_info = (hwsensor_board_info*)kzalloc(
            sizeof(hwsensor_board_info), GFP_KERNEL);
	if (!sensor_info) {
		printk("%s failed %d\n", __func__, __LINE__);
		return -ENOMEM;
	}

    sensor_info->psensor = psensor;

    sensor_info->gpio_num = of_gpio_count(of_node);
	if(sensor_info->gpio_num < 0 ) {
		printk("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}
    rc = of_property_read_string(of_node, "huawei,sensor_name",
		(const char **)&sensor_info->sensor_name);
	printk("%s huawei,sensor_name %s, rc %d\n", __func__,
		sensor_info->sensor_name, rc);
	if (rc < 0) {
        printk("%s failed %d\n", __func__, __LINE__);
        goto fail;
	} 

	rc = of_property_read_u32(of_node, "huawei,sensor_index",
		&sensor_info->camera_id);
	if (rc < 0) {
		printk("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}
    	
	for(i = 0; i < sensor_info->gpio_num; i++) {
		rc = of_property_read_string_index(of_node, "huawei,gpio-ctrl-types",
			i, (const char **)&gpio_tag);
		if(rc < 0) {
			printk("%s failed %d\n", __func__, __LINE__);
			goto fail;
		}
		for(index = 0; index < GPIO_MAX; index++) {
			if(!strcmp(gpio_ctrl_types[index], gpio_tag)){
                sensor_info->gpios[index].gpio = of_get_gpio(of_node, i);
            }
		}
		printk("gpio ctrl types: %s\n", gpio_tag);
	}
	list_add_tail(&sensor_info->link, &g_sensor_info);
	return 0;

fail:
    kfree(sensor_info);
	sensor_info = NULL;

	return rc;
}

void rpmsg_sensor_unregister(void *ptr_sensor)
{
    hwsensor_board_info *sensor_info = NULL;
    struct list_head *pos;

    if (NULL == ptr_sensor) {
        printk("%s Null ptr\n", __func__);
        return;
    }

    sensor_info = container_of(ptr_sensor, hwsensor_board_info, psensor);

    list_for_each(pos, &g_sensor_info) {
        if (pos == &sensor_info->link) {
            list_del(&sensor_info->link);
            kfree(sensor_info);
            return;
        }
    }

    printk("%s can not find sensor\n", __func__);
}

static int do_gpio_config_on(hwsensor_board_info *sensor_info)
{
	int ret = 0;
	
	ret = hw_sensor_gpio_config(RESET, sensor_info, HIGH);
	if(ret < 0)
		return ret;
    ret = hw_sensor_gpio_config(POWERDOWN, sensor_info, LOW);
	if(ret < 0)
		return ret;
    ret = hw_sensor_gpio_config(CAM_VCM_POWER, sensor_info, HIGH);
  	if(ret < 0)
		return ret;  
    ret = hw_sensor_gpio_config(DPHY_TXRXZ, sensor_info, LOW);
  	if(ret < 0)
		return ret;  
    ret = hw_sensor_gpio_config(DPHY_RSTZCAL, sensor_info, HIGH);
	if(ret < 0)
		return ret;
    ret = hw_sensor_gpio_config(CAM_1V05_EN, sensor_info, HIGH);
    if(ret < 0)
		return ret;
    ret = hw_sensor_gpio_config(CAM_1V2_EN, sensor_info, HIGH);
	if(ret < 0)
		return ret;
    ret = hw_sensor_gpio_config(CAM_1V8_EN, sensor_info, HIGH);
	if(ret < 0)
		return ret;
    ret = hw_sensor_gpio_config(CAM_2V85_EN, sensor_info, HIGH);
	if(ret < 0)
		return ret;
    ret = hw_sensor_gpio_config(CAM_VCM_2V85_EN, sensor_info, HIGH);

	return ret;
}

static int do_gpio_config_off(hwsensor_board_info *sensor_info)
{
	int ret = 0;
	
	ret = hw_sensor_gpio_config(CAM_VCM_POWER, sensor_info, LOW);
	if(ret < 0)
		return ret;
    ret = hw_sensor_gpio_config(POWERDOWN, sensor_info, HIGH);
	if(ret < 0)
		return ret;    
    ret = hw_sensor_gpio_config(RESET, sensor_info, LOW);
	if(ret < 0)
		return ret;    
    ret = hw_sensor_gpio_config(DPHY_TXRXZ, sensor_info, HIGH);
 	if(ret < 0)
		return ret;   
    ret = hw_sensor_gpio_config(DPHY_RSTZCAL, sensor_info, LOW);
	if(ret < 0)
		return ret;
    ret = hw_sensor_gpio_config(CAM_1V05_EN, sensor_info, LOW);
	if(ret < 0)
		return ret;    
    ret = hw_sensor_gpio_config(CAM_1V2_EN, sensor_info, LOW);
	if(ret < 0)
		return ret;
    ret = hw_sensor_gpio_config(CAM_1V8_EN, sensor_info, LOW);
	if(ret < 0)
		return ret;
    ret = hw_sensor_gpio_config(CAM_2V85_EN, sensor_info, LOW);
	if(ret < 0)
		return ret;
    ret = hw_sensor_gpio_config(CAM_VCM_2V85_EN, sensor_info, LOW);

	return ret;
}

static int all_sensor_power_on(int index)
{
	hwsensor_board_info *tmp_sensor_info = NULL;
	int ret = 0;
	if(list_empty_careful(&g_sensor_info))
	{
		printk("sensor list is null! \n");
		return -EINVAL;
	}
	list_for_each_entry(tmp_sensor_info, &g_sensor_info, link)
	{
		if(index == tmp_sensor_info->camera_id)
		{
			printk("sensor %s@%d power on\n", tmp_sensor_info->sensor_name, tmp_sensor_info->camera_id);
			/* if diff sensor has diff gpio config, we need to add it to choose */
			ret = do_gpio_config_on(tmp_sensor_info);
			if(ret < 0)
				printk("sensor %s@%d power on failed!\n", tmp_sensor_info->sensor_name, tmp_sensor_info->camera_id);
		}
	}
	return ret;
}

static int all_sensor_power_off(int index)
{
	hwsensor_board_info *tmp_sensor_info = NULL;
	int ret = 0;
	if(list_empty_careful(&g_sensor_info))
	{
		printk("sensor list is null! \n");
		return -EINVAL;
	}
	list_for_each_entry(tmp_sensor_info, &g_sensor_info, link)
	{
		if(index == tmp_sensor_info->camera_id)
		{
			printk("sensor %s@%d power off\n", tmp_sensor_info->sensor_name, tmp_sensor_info->camera_id);
			/* if diff sensor has diff gpio config, we need to add it to choose */
			ret = do_gpio_config_off(tmp_sensor_info);
			if(ret < 0)
				printk("sensor %s@%d power off failed!\n", tmp_sensor_info->sensor_name, tmp_sensor_info->camera_id);
		}
	}
	return ret;
}

int do_sensor_power_on(int index, const char *name)
{
    int ret = 0;
	hwsensor_board_info *sensor_info = NULL;

	ret = check_sensor_name(index, name, &sensor_info);
	if(ret < 0)
	{
		printk("sensor %s@%d power on failed!\n", name, index);
		return -EINVAL;
	}

    if (hw_is_fpga_board()) {
        /* if diff sensor has diff gpio config, we need to add it to choose */
        ret = do_gpio_config_on(sensor_info);
        if(ret < 0){
            printk("sensor %s@%d power on failed!\n", name, index);
            return ret;
        }
    } else {
        ret = hw_sensor_power_on(sensor_info->psensor);
        if (ret < 0) {
            printk("hw sensor %s@%d power on failed!\n", name, index);
            return ret;
        }
    }

    printk("%s@%d power on \n", sensor_info->sensor_name, sensor_info->camera_id);

    return 0;
}


int do_sensor_power_off(int index, const char* name)
{
    int ret = 0;
    hwsensor_board_info *sensor_info = NULL;

	ret = check_sensor_name(index, name, &sensor_info);
	if(ret < 0)
	{
		printk("sensor %s@%d power off failed!\n", name, index);
		return -EINVAL;
	}

    if (hw_is_fpga_board()) {
        /* if diff sensor has diff gpio config, we need to add it to choose */
        ret = do_gpio_config_off(sensor_info);
        if(ret < 0){
            printk("sensor %s@%d power off failed!\n", name, index);
            return ret;
        }
    } else {
        ret = hw_sensor_power_off(sensor_info->psensor);
        if (ret < 0) {
            printk("hw sensor %s@%d power off failed!\n", name, index);
            return ret;
        }
    }

    printk("%s@%d power off \n", sensor_info->sensor_name, sensor_info->camera_id);

    return 0;
}

int rpmsg_sensor_ioctl(unsigned int cmd, int index, char *name)
{
    int ret = -EINVAL;
    printk("cmd:%d, index:%d name:%s \n", cmd, index, name);

    switch (cmd)
    {
    case HWSENSOR_IOCTL_POWER_UP:
		if(0 ==strlen(name))
		{
			ret = all_sensor_power_on(index);
			break;
		}
        ret = do_sensor_power_on(index, name);
        break;
    case HWSENSOR_IOCTL_POWER_DOWN:
		if(0 ==strlen(name))
		{
			ret = all_sensor_power_off(index);
			break;
		}
        ret = do_sensor_power_off(index, name);
        break;
    default:
        printk("invalid IOCTL CMD(%d)! \n", cmd);
        break;
    }
	if(0 != ret)
		printk("rpmsg_ioctl_config failed! ret=%d \n", ret);
    return ret;
}


