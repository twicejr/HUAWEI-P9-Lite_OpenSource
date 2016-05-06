/*
 * Copyright (C) 2013 HUAWEI, Inc.
 * Author: tuhaibo <tuhaibo@huawei.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
 
 
 
#include "ak8789.h"
#include <huawei_platform/log/hw_log.h>
#include <huawei_platform/sensor/sensor_info.h>

#define HWLOG_TAG hall
HWLOG_REGIST();

static struct workqueue_struct *hall_wq;

static struct kobject *hall_kobject = NULL;
static struct  hall_dev *hall_dev_client=NULL;
static struct wake_lock wlock;

static const struct of_device_id hall_match_table[] = {
	{.compatible = "hall,sensor",},
	{},
};

static struct sensors_classdev ak8789_hall_cdev = {
       .path_name="hall_sensor",
	.name = "Hall sensor",
	.vendor = "akm_ak8789",
	.version = 1,
	.handle = SENSORS_HALL_HANDLE,
	.type = SENSOR_TYPE_HALL,
	.max_range = "3.0",
	.resolution = "1.0",
	.sensor_power = "0.75",
	.min_delay = 0,
	.delay_msec = 200,
	.fifo_reserved_event_count = 0,
	.fifo_max_event_count = 0,
	.enabled = 0,
	.sensors_enable = NULL,
	.sensors_poll_delay = NULL,
};

MODULE_DEVICE_TABLE(of, hall_match_table);

static void hall_work(struct work_struct *work)
{
	int ret = 0;
	packet_data event_value = 0;
	struct hall_dev *phall_dev = NULL;

	phall_dev = container_of(work, struct hall_dev, hall_work);

	if (phall_dev->ops && phall_dev->ops->packet_event_data) {
		event_value = phall_dev->ops->packet_event_data(phall_dev);
	} else {
		hall_ERR("[hall][%s] packet event data failed!\n", __func__);
		return ;
	}

	if(phall_dev->ops && phall_dev->ops->hall_event_report)
		ret = phall_dev->ops->hall_event_report(event_value,phall_dev);

	if(!ret) {
		hall_ERR("[hall][%s] hall report value failed.\n", __func__);
		return ;
	}

	hall_INFO("[hall][%s] hall report value :%d.\n", __func__, event_value);
	return ;
}

static irqreturn_t hall_event_handler(int irq, void *pdev)
{
	struct hall_dev *phall_dev = NULL;

	if(NULL == pdev) {
		hall_ERR("[hall][%s] invalid pointer!\n", __func__);
		return IRQ_NONE;
	}

	phall_dev = (struct hall_dev *)pdev;
	wake_lock_timeout(&wlock, 1*HZ);
	if (phall_dev->ops && phall_dev->ops->hall_device_irq_top_handler && hall_work_status == phall_dev->hall_status) {
		phall_dev->ops->hall_device_irq_top_handler(irq, phall_dev);
	} else {
		return IRQ_HANDLED;
	}

	queue_work(hall_wq, &phall_dev->hall_work);
	return IRQ_HANDLED;
}

static int hall_request_irq(struct hall_dev *phall_dev)
{
	int i = 0;
	int irq = 0;
	int ret = 0;
	int trigger_value = 0;
	int wake_up = 16384;
	char name[MAX_IRQ_NAME_LEN];

	if (NULL == phall_dev) {
		hall_ERR("[hall][%s] invalid pointer!\n", __func__);
		return -EINVAL;
	}

	for ( i = 0; i < phall_dev->hall_type; i++) {
		irq = phall_dev->irq_info[i].irq;
		trigger_value = phall_dev->irq_info[i].trigger_value;
		wake_up = phall_dev->irq_info[i].wake_up;
		strcpy(name, phall_dev->irq_info[i].name);
		if (irq) {
			ret = request_irq(irq, hall_event_handler,
				trigger_value | wake_up, name, phall_dev);

		}
	}

/*
  * report the current magnetic field approach status to the initialized magnetic field status approach identification.
  */
	if (phall_dev->ops && phall_dev->ops->hall_device_irq_top_handler && hall_work_status == phall_dev->hall_status) {
		phall_dev->ops->hall_device_irq_top_handler(irq, phall_dev);
		queue_work(hall_wq, &phall_dev->hall_work);
	}

	return ret;
}
static int hall_ak8789_enable_set(struct sensors_classdev *sensors_cdev,unsigned int enable)
{
       int ret = 0;
	unsigned int enable_value = 0;
	packet_data event_value = 0;
	struct hall_dev *phall_dev = NULL;
	phall_dev=hall_dev_client;
	if(phall_dev->ops && phall_dev->ops->packet_event_data)
		event_value = phall_dev->ops->packet_event_data(phall_dev);
	if(event_value < 0) {
		hall_ERR("[hall][%s] hall packet event failed.\n", __func__);
		return 0;
	}

	enable_value = enable;

	hall_INFO("[hall][%s] enable_value:%u, event_value:%d.\n", __func__, enable_value,
		event_value);	

	if(enable_value) {
		if(phall_dev->ops && phall_dev->ops->hall_event_report)
			ret = phall_dev->ops->hall_event_report(event_value,phall_dev);
		if(!ret) {

			hall_ERR("[hall][%s] hall report value failed.\n", __func__);
			return -EINVAL;
		}

		hall_INFO("[hall][%s] hall report event value:%d. \n", __func__, event_value);
	}

	return 0;
}
static ssize_t store_enable_hall_sensor(struct device *dev,
			struct device_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;
	int enable_value = 0;
	packet_data event_value = 0;
	struct hall_dev *phall_dev = NULL;
	phall_dev=hall_dev_client;
	if(phall_dev->ops && phall_dev->ops->packet_event_data)
		event_value = phall_dev->ops->packet_event_data(phall_dev);
	if(event_value < 0) {
		hall_ERR("[hall][%s] hall packet event failed.\n", __func__);
		return 1;
	}

	enable_value = simple_strtoul(buf, NULL, 10);

	hall_INFO("[hall][%s] enable_value:%u, event_value:%d.\n", __func__, enable_value,
		event_value);	

	if(enable_value) {
		if(phall_dev->ops && phall_dev->ops->hall_event_report)
			ret = phall_dev->ops->hall_event_report(event_value,phall_dev);
		if(!ret) {

			hall_ERR("[hall][%s] hall report value failed.\n", __func__);
			return -EINVAL;
		}

		hall_INFO("[hall][%s] hall report event value:%d. \n", __func__, event_value);
	}

	return 1;
}

static ssize_t show_get_hall_sensor_status(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct hall_dev *phall_dev = NULL;
	phall_dev=hall_dev_client;
	 hall_ERR("[hall]fyh show_get_hall_sensor_status\n");
	return snprintf(buf, PAGE_SIZE, "hall information:id:%04d, type:%04d\t\
		\nx_coordinate:%04d, y_coordinate:%04d.\n",phall_dev->hall_id, phall_dev->hall_type,phall_dev->hall0_x_coordinate, phall_dev->hall0_y_coordinate);
}

static DEVICE_ATTR(hall_sensor, 0664, show_get_hall_sensor_status, store_enable_hall_sensor);

static struct attribute *hall_sensor_attributes[] = {
	&dev_attr_hall_sensor.attr,
	NULL
};

static const struct attribute_group hall_sensor_attr_group = {
	.attrs = hall_sensor_attributes,
};
static int ak8789_parse_dt(struct device_node *hall_node,struct hall_dev *hall_dev)
{
	int ret,err;
	if(hall_dev ->hall_type == north_one_south_one)
	{
		ret = of_property_read_u32(hall_node, HALL0_NORTH_WAKE_UP, &hall_dev->irq_info[0].wake_up);
		if(ret) {
			hall_ERR("[hall][ak8789][%s]hall wake up flag is  not specified\n", __func__);
			err = -EINVAL;
			return err;
		}
		ret = of_property_read_u32(hall_node, HALL0_SOUTH_WAKE_UP, &hall_dev->irq_info[1].wake_up);
		if(ret) {
			hall_ERR("[hall][ak8789][%s]hall wake up flag is  not specified\n", __func__);
			err = -EINVAL;
			return err;
		}
		ret = of_property_read_u32(hall_node, HALL_ID, &hall_dev->hall_id);
		if (ret) {
			hall_ERR("[hall][ak8789][%s] hall id is  not specified\n", __func__);
			err = -EINVAL;
			return err;
		}

		ret = of_property_read_u32(hall_node, HALL0_X_COR, &hall_dev->hall0_x_coordinate);
		if (ret) {
			hall_ERR("[hall][ak8789][%s] hall x coordinate is not specified\n", __func__);
			err = -EINVAL;
			return err;
		}

		ret = of_property_read_u32(hall_node, HALL0_Y_COR, &hall_dev->hall0_y_coordinate);
		if (ret) {
			hall_ERR("[hall][ak8789][%s] hall y coordinate is not specified\n", __func__);
			err = -EINVAL;
			return err;
		}
	}
	else if(hall_dev ->hall_type == north_two_south_two)
	{
		ret = of_property_read_u32(hall_node, HALL0_NORTH_WAKE_UP, &hall_dev->irq_info[0].wake_up);
		if(ret) {
			hall_ERR("[hall][ak8789][%s]hall wake up flag is  not specified\n", __func__);
			err = -EINVAL;
			return err;
		}
		ret = of_property_read_u32(hall_node, HALL0_SOUTH_WAKE_UP, &hall_dev->irq_info[1].wake_up);
		if(ret) {
			hall_ERR("[hall][ak8789][%s]hall wake up flag is  not specified\n", __func__);
			err = -EINVAL;
			return err;
		}

		ret = of_property_read_u32(hall_node, HALL1_NORTH_WAKE_UP, &hall_dev->irq_info[2].wake_up);
		if(ret) {
			hall_ERR("[hall][ak8789][%s]hall wake up flag is  not specified\n", __func__);
			err = -EINVAL;
			return err;
		}
		ret = of_property_read_u32(hall_node, HALL1_SOUTH_WAKE_UP, &hall_dev->irq_info[3].wake_up);
		if(ret) {
			hall_ERR("[hall][ak8789][%s]hall wake up flag is  not specified\n", __func__);
			err = -EINVAL;
			return err;
		}
		ret = of_property_read_u32(hall_node, HALL_ID, &hall_dev->hall_id);
		if (ret) {
			hall_ERR("[hall][ak8789][%s] hall id is  not specified\n", __func__);
			err = -EINVAL;
			return err;
		}

		ret = of_property_read_u32(hall_node, HALL0_X_COR, &hall_dev->hall0_x_coordinate);
		if (ret) {
			hall_ERR("[hall][ak8789][%s] hall x coordinate is not specified\n", __func__);
			err = -EINVAL;
			return err;
		}

		ret = of_property_read_u32(hall_node, HALL0_Y_COR, &hall_dev->hall0_y_coordinate);
		if (ret) {
			hall_ERR("[hall][ak8789][%s] hall y coordinate is not specified\n", __func__);
			err = -EINVAL;
			return err;
		}

		ret = of_property_read_u32(hall_node, HALL1_X_COR, &hall_dev->hall1_x_coordinate);
		if (ret) {
			hall_ERR("[hall][ak8789][%s] hall x coordinate is not specified\n", __func__);
			err = -EINVAL;
			return err;
		}

		ret = of_property_read_u32(hall_node, HALL1_Y_COR, &hall_dev->hall1_y_coordinate);
		if (ret) {
			hall_ERR("[hall][ak8789][%s] hall y coordinate is not specified\n", __func__);
			err = -EINVAL;
			return err;
		}
	}
	else
	{
		hall_ERR("[hall][ak8789][%s],line %d: hall_type wrong\n", __func__,__LINE__);
		err = -EINVAL;
		return err;

	}

	return 0;

}
static int hall_probe(struct platform_device *pdev)
{
	int ret = 0;
	int err = 0;
	struct device *dev = NULL;
	struct device_node *hall_node = NULL;
	struct hall_dev *hall_dev = NULL;

	if (NULL == pdev) {
		hall_ERR("[hall][%s] invalid pointer!\n", __func__);
		return -EINVAL;
	}

	dev = &pdev->dev;
	hall_node = dev->of_node;
        hall_dev = kzalloc(sizeof(struct hall_dev), GFP_KERNEL);
	if(!hall_dev) {
		hall_ERR("[hall][%s]hall_dev kzalloc error!\n", __func__);
		err = -ENOMEM;
		goto hall_dev_kzalloc_err;
	}

	hall_dev_client=hall_dev;
	hall_wq = create_singlethread_workqueue("hall_wq");
	if(IS_ERR(hall_wq)) {

		hall_ERR("[hall][%s]work_wq kmalloc error!\n", __func__);
		err = -ENOMEM;
		goto hall_wq_err;
	}

	ret = of_property_read_u32(hall_node, HALL_TYPE, &(hall_dev->hall_type));
	if(ret)	{
		hall_ERR("[hall][%s]hall type flag is  not specified\n", __func__);
		err = -EINVAL;
	 	goto hall_type_parse_err;
	}

	hall_dev->ops = &hall_device_ops;
	INIT_WORK(&(hall_dev->hall_work), hall_work);
	if (hall_dev->ops && hall_dev->ops->hall_device_init) {
		hall_dev->ops->hall_device_init(pdev, hall_dev);
		hall_INFO("[hall][%s]hall_device_init enter!\n", __func__);
	} else {
		hall_ERR("[hall][%s]can't find hall_device_init function!", __func__);
		err = -EINVAL;
		goto hall_device_init_err;
	}

	hall_dev->hall_dev = pdev;

	/* Initialize wakelock*/
	wake_lock_init(&wlock, WAKE_LOCK_SUSPEND, "ak8789");

	ret = ak8789_parse_dt(hall_node,hall_dev);
	if (ret) {
		hall_ERR("[hall][ak8789][%s] hall id is  not specified\n", __func__);
		err = -EINVAL;
		goto dts_parse_err;
	}

	platform_set_drvdata(pdev, hall_dev);
	hall_dev->hall_status = hall_work_status;

	hall_dev->hw_input_hall = input_allocate_device();
	if (IS_ERR(hall_dev->hw_input_hall)){
		hall_ERR("[hall][ak8789][%s] hw_input_hall alloc error\n",__func__);
		goto input_err;
	}
	
	hall_dev->hw_input_hall->name = HALL_INPUT_DEV_NAME;
	set_bit(EV_MSC, hall_dev->hw_input_hall->evbit);
	set_bit(MSC_SCAN, hall_dev->hw_input_hall->mscbit);

	ret = input_register_device(hall_dev->hw_input_hall);
	if (ret){
		hall_ERR( "[hall][%s] hw_input_hall regiset error\n",__func__);
		goto input_register_fail;
	}
	ret = hall_request_irq(hall_dev);
	if (ret) {
			hall_INFO("[hall][%s] hall_type:%d, hall_id:%d\n", __func__, hall_dev->hall_type, hall_dev->hall_id);
		goto hall_request_irq_err;
	}

	if(NULL==hall_kobject)
	{
		 hall_kobject= kobject_create_and_add("hall", NULL);
		 if (!hall_kobject)
		{
			hall_ERR("[hall][%s] create hall kobjetct error!\n",__func__);
			goto sysfs_create_group_err;;
		}
		else
		{
			hall_INFO("[hall][%s] create sys/hallsuccessful!\n",__func__);
		}
	}
	else
	{
		hall_INFO("[hall] create sys/hall alraed ex\n");
	}
	ret = sysfs_create_group(hall_kobject, &hall_sensor_attr_group);
	if (ret) {
		hall_ERR("[hall][%s] hall sysfs_create_group failed", __func__);
		goto sysfs_create_group_err;
	}
       hall_dev->cdev=ak8789_hall_cdev;
       hall_dev->cdev.sensors_enable=hall_ak8789_enable_set;
       hall_dev->cdev.sensors_poll_delay=NULL;
       err = sensors_classdev_register(&pdev->dev, &hall_dev->cdev);
	if (err) 
      {
	    gs_ERR("[GS]unable to register sensors_classdev: %d\n",err);
	}
	return ret;

sysfs_create_group_err:
hall_request_irq_err:
input_register_fail:
	input_free_device(hall_dev->hw_input_hall);
input_err:
dts_parse_err:
	if( hall_dev->ops && hall_dev->ops->hall_release)
		hall_dev->ops->hall_release(hall_dev);
       destroy_workqueue(hall_wq);
hall_device_init_err:
hall_type_parse_err:
hall_wq_err:
	kfree(hall_dev);
	platform_set_drvdata(pdev, NULL);
hall_dev_kzalloc_err:
	return err;
}

static int hall_remove(struct platform_device *pdev)
{
	int ret = 0;
	struct hall_dev *hall_data = NULL;
	
	hall_data = (struct hall_dev *)platform_get_drvdata(pdev);
	hall_data->hall_status = hall_removed_status;

	input_unregister_device(hall_data->hw_input_hall);
	destroy_workqueue(hall_wq);
        if( hall_data->ops && hall_data->ops->hall_release) {
                ret = hall_data->ops->hall_release(hall_data);
        }

	kfree(hall_data);
	platform_set_drvdata(pdev, NULL);

	return ret;
}

static struct platform_driver hall_driver = {
	.probe = hall_probe,
	.remove = hall_remove,
	.driver = {
			.name = HALL_SENSOR_NAME,
			.owner = THIS_MODULE,
			.of_match_table = of_match_ptr(hall_match_table),
	},
};

static int __init hall_init(void)
{
	hall_INFO("[hall]hall init!\n");
	return platform_driver_register(&hall_driver);
}

static void __exit hall_exit(void)
{
	hall_INFO("[hall]hall exit!\n");
	platform_driver_unregister(&hall_driver);
}

module_init(hall_init);
module_exit(hall_exit);

MODULE_AUTHOR("Huawei PDU_DRV Group");
MODULE_DESCRIPTION("hall platform driver");
MODULE_LICENSE("GPL");

static int gpio_index_to_name(int index, char *name)
{
	if(NULL == name) {
		hall_ERR("[hall][ak8789][%s] invalid pointer!\n", __func__);
		return -EINVAL;
	}

	switch (index) {
		case 0:
			strncpy(name, HALL0_NORTH_POLE_NAME, sizeof(HALL0_NORTH_POLE_NAME));
			break;
		case 1:
			strncpy(name, HALL0_SOUTH_POLE_NAME, sizeof(HALL0_SOUTH_POLE_NAME));
			break;
		case 2:
			strncpy(name, HALL1_NORTH_POLE_NAME, sizeof(HALL1_NORTH_POLE_NAME));
			break;
		case 3:
			strncpy(name, HALL1_SOUTH_POLE_NAME, sizeof(HALL1_SOUTH_POLE_NAME));
			break;
		default:

			hall_ERR("[hall][ak8789][%s] Invalid index!\n", __func__);
			
	}

	return 0;
}

static int setup_gpio (int gpio_id, const char *gpio_name) {
	int ret = 0;

	if(NULL == gpio_name) {

		hall_ERR("[hall][ak8789][%s] invalid pointer!\n", __func__);
		return -EINVAL;
	}

	ret = gpio_request(gpio_id, gpio_name);
	if(ret) {

		hall_ERR("[hall][%s] requset gpio %d err %d\n", __func__, gpio_id, ret);
		return ret;
	}

	ret = gpio_direction_input(gpio_id);
	if(ret) {
		hall_ERR("[hall][%s] gpio %d direction input err %d\n", __func__, gpio_id, ret);
		return ret;
	}

	return ret;
}

static int gpio_irq_trigger_inversion(int irq)
{
        struct irq_desc *desc = NULL;
	int trigger_value = 0;
	int ret = 0;

	desc = irq_to_desc(irq);
	if (!desc) {

		hall_ERR("[hall][%s]irq_desc null!\n", __func__);
		return IRQ_NONE;
	}

	trigger_value = desc->irq_data.state_use_accessors & IRQD_TRIGGER_MASK;
	if (trigger_value & IRQF_TRIGGER_LOW) {
		ret = irq_set_irq_type(irq, IRQF_TRIGGER_HIGH);
	} else {
		ret = irq_set_irq_type(irq, IRQF_TRIGGER_LOW);
	}

	return ret;
}


static int hall_ak8789_irq_top_handler(int irq, struct hall_dev *phall_dev)
{
	int ret = 0;

	if(NULL == phall_dev) {

		hall_ERR("[hall][ak8789][%s] invalid pointer!\n", __func__);
		return -EINVAL;
	}

	if(irq)
		ret = gpio_irq_trigger_inversion(irq);

	return ret;
}

static packet_data hall_ak8789_packet_event_data(struct hall_dev *phall_dev)
{
	int i = 0;
	struct hall_ak8789_dev *hall_ak8789 = NULL;
	packet_data event_value = 0;

	if(NULL == phall_dev) {

		hall_ERR("[hall][ak8789][%s] invalid pointer!\n", __func__);
		return -EINVAL;
	}

	hall_ak8789 = phall_dev->hall_device;
	hall_ak8789->hall_ak8789_type = phall_dev->hall_type;

	for (i = 0; i < hall_ak8789->hall_ak8789_type; i++) {
		if (hall_ak8789->gpio_poles[i]) {
			event_value |= !gpio_get_value(hall_ak8789->gpio_poles[i])\
			<< (phall_dev->hall_id * 2 + i);
		}
	}

	return event_value;
}

static int hall_ak8789_release(struct hall_dev *phall_dev)
{
	int i = 0;
	int irq = 0;
	int ret = 0;
	int gpio_id = 0;
	struct hall_ak8789_dev *hall_ak8789 = NULL;

	if(NULL == phall_dev) {

		hall_ERR("[hall][ak8789][%s] invalid pointer!\n", __func__);
		return -EINVAL;
	}

	hall_ak8789 = phall_dev->hall_device;
	hall_ak8789->hall_ak8789_type = phall_dev->hall_type;
	for (i=0; i < hall_ak8789->hall_ak8789_type; i++) {
		irq = phall_dev->irq_info[i].irq;
		if(irq) {
			free_irq(irq, phall_dev);
		}
	}


	for (i = 0; i< hall_ak8789->hall_ak8789_type; i++) {
		gpio_id = hall_ak8789->gpio_poles[i];
		if(gpio_id) {
			gpio_free(gpio_id);
		}
	}

	kfree(phall_dev->hall_device);
	phall_dev->hall_device = NULL;

	return ret;
}

static int hall_ak8789_device_init(struct platform_device *pdev,
		struct hall_dev *phall_dev)
{
	int err = 0;
	int i = 0;
	int gpio_id = 0;
	int gpio_value = 0;
	int hall_type_err = 0;
	char gpio_name[MAX_GPIO_NAME_LEN];
    struct device_node *hall_ak8789_node = NULL;
	struct device *dev = NULL;
	struct hall_ak8789_dev *hall_ak8789 = NULL;


	if(NULL == phall_dev || NULL == pdev) {
		hall_ERR("[hall][ak8789][%s] invalid pointer!\n", __func__);
		return -EINVAL;
	}

	hall_ak8789 = kzalloc(sizeof(struct hall_ak8789_dev), GFP_KERNEL);
	if(!hall_ak8789) {

		hall_ERR("[hall][%s]hall_dev kmalloc error!\n", __func__);
		err = -ENOMEM;
		return err;
	}

	dev = &pdev->dev;
	hall_ak8789_node = dev->of_node;
	hall_ak8789->hall_ak8789_type = phall_dev->hall_type;
	for (i = 0; i < hall_ak8789->hall_ak8789_type; i++) {
		hall_ak8789->gpio_poles[i] = 0;
	}

	 hall_ERR("[hall]hall_ak8789->hall_ak8789_type=%d\n", hall_ak8789->hall_ak8789_type);
      switch (hall_ak8789->hall_ak8789_type) {
		case single_north_pole:
			hall_ak8789->gpio_poles[0] = of_get_named_gpio(hall_ak8789_node
				, HALL0_NORTH_POLE_NAME, 0);;
			break;
		case single_south_pole:
			hall_ak8789->gpio_poles[1] = of_get_named_gpio(hall_ak8789_node
				, HALL0_SOUTH_POLE_NAME, 0);
			break;
		case north_one_south_one:
			hall_ak8789->gpio_poles[0] = of_get_named_gpio(hall_ak8789_node
				, HALL0_NORTH_POLE_NAME, 0);
			hall_ak8789->gpio_poles[1] = of_get_named_gpio(hall_ak8789_node
				, HALL0_SOUTH_POLE_NAME, 0);
			break;
		case north_two_south_one:
			hall_ak8789->gpio_poles[0] = of_get_named_gpio(hall_ak8789_node
				, HALL0_NORTH_POLE_NAME, 0);
			hall_ak8789->gpio_poles[1] = of_get_named_gpio(hall_ak8789_node
				, HALL0_SOUTH_POLE_NAME, 0);
			hall_ak8789->gpio_poles[2] = of_get_named_gpio(hall_ak8789_node
				, HALL1_NORTH_POLE_NAME, 0);
			break;
		case north_two_south_two:
			hall_ak8789->gpio_poles[0] = of_get_named_gpio(hall_ak8789_node
				, HALL0_NORTH_POLE_NAME, 0);
			hall_ak8789->gpio_poles[1] = of_get_named_gpio(hall_ak8789_node
				, HALL0_SOUTH_POLE_NAME, 0);
			hall_ak8789->gpio_poles[2] = of_get_named_gpio(hall_ak8789_node
				, HALL1_NORTH_POLE_NAME, 0);
			hall_ak8789->gpio_poles[3] = of_get_named_gpio(hall_ak8789_node
				, HALL1_SOUTH_POLE_NAME, 0);
			break;
		default:

			hall_ERR("[hall][%s]Invalid hall type !\n", __func__);
			kfree(hall_ak8789);
			hall_type_err = -1;
			return hall_type_err;
	}

	for (i = 0; i < hall_ak8789->hall_ak8789_type; i++) {
		gpio_id = hall_ak8789->gpio_poles[i];
		if(gpio_id) {
			gpio_index_to_name(i, gpio_name);
			err = setup_gpio(gpio_id, gpio_name);
			if(err) {
					hall_ERR("[hall][%s] gpio %d direction input err %d\n",
					__func__, gpio_id, err);
                     }

			gpio_value = gpio_get_value(gpio_id);
			phall_dev->irq_info[i].irq = gpio_to_irq(gpio_id);
			phall_dev->irq_info[i].trigger_value = (gpio_value == GPIO_LOW_VOLTAGE)
				? IRQF_TRIGGER_HIGH : IRQF_TRIGGER_LOW;
			strcpy(phall_dev->irq_info[i].name, gpio_name);
		} else {
			phall_dev->irq_info[i].irq = 0;
			phall_dev->irq_info[i].trigger_value = 0;
		}
	}

	phall_dev->hall_device = hall_ak8789;
	return err;
}

static int hall_ak8789_event_report(packet_data packet_data,struct hall_dev *phall_dev)
{
	if(phall_dev->hw_input_hall !=NULL)
	{
		input_event(phall_dev->hw_input_hall, EV_MSC, MSC_SCAN, packet_data);
		input_sync(phall_dev->hw_input_hall);
	}
	return 1;
}

