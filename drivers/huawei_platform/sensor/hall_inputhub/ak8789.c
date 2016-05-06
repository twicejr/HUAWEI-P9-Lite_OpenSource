/*
 * Copyright (C) 2014 HUAWEI, Inc.
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

#include <linux/delay.h>
#include "hall_sensor.h"
#include "ak8789.h"

#ifdef HWLOG_TAG
#undef HWLOG_TAG
#endif

#define HWLOG_TAG ak8789
HWLOG_REGIST();

static const struct of_device_id ak8789_match_table[] = {
	{.compatible = "huawei,hall_sensor,ak8789",},
	{},
};
MODULE_DEVICE_TABLE(of, ak8789_match_table);

#ifdef HALL_DATA_REPORT_INPUTHUB
static struct ak8789_data *data_ak8789;
#endif

#ifdef HALL_DSM_CONFIG
static struct dsm_dev dsm_hall = {
	.name = "dsm_hall",
	.device_name = "hal",
	.ic_name = NULL,
	.module_name = NULL,
	.fops = NULL,
	.buff_size = 1024,
};
#endif

//function
static int ak8789_get_data(struct hall_device *h_dev)
{
	packet_data p_data = 0;
	int h_type;
	if (!h_dev) {
		hwlog_err("%s done\n", __FUNCTION__);
		return -1;
	}
	h_type = h_dev->hall_type;

	if (h_type & 0x01) {
		if (!h_dev->h_info.auxiliary_io[0]) {
			p_data |= !gpio_get_value(h_dev->h_info.gpio[single_north_pole]);
		} else if (!gpio_get_value(h_dev->h_info.auxiliary_io[single_north_pole])) {
			p_data |= !gpio_get_value(h_dev->h_info.gpio[single_north_pole]);
		} else {
			hwlog_err("auxiliary io[id:%d north] status err.\n", h_dev->hall_id);
		}
	}
	if (h_type & 0x02) {
		if (!h_dev->h_info.auxiliary_io[1]) {
			p_data |= (!gpio_get_value(h_dev->h_info.gpio[single_south_pole]))<<1;
		} else if (!gpio_get_value(h_dev->h_info.auxiliary_io[single_south_pole])) {
			p_data |= (!gpio_get_value(h_dev->h_info.gpio[single_south_pole]))<<1;
		} else {
			hwlog_err("auxiliary io[id:%d south] status err.\n", h_dev->hall_id);
		}
	}

	//hwlog_info("[%s][p_data:%d][id:%d]\n", __FUNCTION__, p_data, h_dev->hall_id);

	return p_data;
}

static int ak8789_get_info(struct hall_cdev *cdev, char *buf)
{
	int ret;
	int max_length = HALL_MXA_INFO_LEN, count = 0;
	char *temp_buf = buf;
	struct ak8789_data *data = container_of(cdev, struct ak8789_data, cdev);
	struct hall_device *temp_dev;

	ret = snprintf(temp_buf, max_length, "[hall]total count:%d\n", data->count);
	if (ret <0 ) {
		hwlog_err("Get ak8789 info err.");
		return -1;
	}
	temp_buf += ret;
	max_length -= ret;
	count += ret;
	list_for_each_entry(temp_dev, &data->head, list) {
		if (max_length > 0 ) {
			ret = snprintf(temp_buf, max_length, "[hall]id:%d; type:%d;wakeup:%d; x_coor:%d; y_coor:%d\n",
				temp_dev->hall_id, temp_dev->hall_type, temp_dev->hall_hw_wakeup_support, temp_dev->hall_x_coordinate, temp_dev->hall_y_coordinate);
			if (ret <0 ) {
				hwlog_err("Get ak8789 info err.");
				return -1;
			}
			count += ret;
			temp_buf += ret;
			max_length -= ret;
		} else {
			hwlog_err("There is too many info.\n");
			return -1;
		}
	}

	if (count >= HALL_MXA_INFO_LEN-2) {
		*(temp_buf+HALL_MXA_INFO_LEN-2) = '\n';
		*(temp_buf+HALL_MXA_INFO_LEN-1) = '\0';
	} else {
		*(temp_buf+count+1) = '\n';
		*(temp_buf+count+2) = '\0';
	}

	return 0;
}

static int ak8789_get_status(struct hall_cdev *cdev)
{
	packet_data temp_data = 0,  pdata = 0;
	struct ak8789_data *data = container_of(cdev, struct ak8789_data, cdev);
	struct hall_device *temp_dev;

	list_for_each_entry(temp_dev, &data->head, list) {
		temp_data = ak8789_get_data(temp_dev);
		pdata |= temp_data << (temp_dev->hall_id ? (1<<temp_dev->hall_id):0);
	}

	return pdata;
}

static int ak8789_report_status(struct hall_cdev *cdev)
{
	packet_data pdata;
	struct ak8789_data *data = container_of(cdev, struct ak8789_data, cdev);
	pdata = cdev->hall_get_state(cdev);
	hwlog_info("[%s]value:%d\n", __FUNCTION__, pdata);
	return ak8789_report_data(data,  pdata);
}

#ifdef HALL_TEST
static inline void ak8789_test_info_init(struct hall_cdev *cdev)
{
	cdev->count = HALL_REPORT_MIN_COUNT;//1
	cdev->period = HALL_REPORT_MAX_PERIOD;//1000
	cdev->enable = 0;
	cdev->value = 0;
	cdev->flag = 0;
	cdev->enable = 0;
}

static void ak8789_set_report_value(struct hall_cdev *cdev)
{
	int i;
	int temp = 0;
	struct ak8789_data *data = container_of(cdev, struct ak8789_data, cdev);
	int count = cdev->count;
	packet_data pdata = cdev->value;
	int period = cdev->period;
	int flag = cdev->flag;

	if (!cdev->enable) {
		hwlog_info("test switch is off, please open the switch if need to test\n");
		return;
	}

	hwlog_info("value:%d; flag:%d; count:%d; period:%d\n", pdata, flag, count, period);

	for (i=0; i<count; i++) {
		ak8789_report_data(data, pdata);
		msleep(period);
		temp = pdata&(~flag);
		pdata = ~pdata;
//		hwlog_info("value:%d; flag:%d\n", pdata, flag);
		pdata &= flag;
//		hwlog_info("value:%d; flag:%d\n", pdata, flag);
		pdata |= temp;
//		hwlog_info("value:%d; flag:%d\n", pdata, flag);
	}

	ak8789_test_info_init(cdev);
}
#endif

#ifdef HALL_DATA_REPORT_INPUTHUB
int hall_first_report(bool enable)
{
	packet_data temp_data = 0,  pdata = 0;
	struct hall_device *temp_dev;
	struct ak8789_data *data = data_ak8789;

	if (!data || list_empty(&data->head)) {
		hwlog_err("none ak8789 data or list is null\n");
		return 0;
	}

	if (!enable)
		return 0;

	list_for_each_entry(temp_dev, &data->head, list) {
		temp_data = ak8789_get_data(temp_dev);
		pdata |= temp_data << (temp_dev->hall_id << 1);
	}

	hwlog_info("[%s]pdata:%d\n", __FUNCTION__, pdata);
	return ak8789_report_data(data,  pdata);
}
EXPORT_SYMBOL_GPL(hall_first_report);

int ak8789_register_report_data(int ms)
{
	struct hall_device *temp_dev;
	struct ak8789_data *data = data_ak8789;

	if (!data || list_empty(&data->head)) {
		hwlog_err("none ak8789 data\n");
		return 0;
	}

    temp_dev = list_first_entry(&data->head , struct hall_device, list);
    queue_delayed_work(data->hall_wq, &temp_dev->h_delayed_work, HZ/20);

	hwlog_info("[%s] ms:%d\n", __FUNCTION__, ms);
	return 1;
}
EXPORT_SYMBOL_GPL(ak8789_register_report_data);
#else
int hall_first_report(bool enable)
{
	return 1;
}
EXPORT_SYMBOL_GPL(hall_first_report);

int ak8789_register_report_data(int ms)
{
	return 1;
}
EXPORT_SYMBOL_GPL(ak8789_register_report_data);
#endif

static int ak8789_report_debug_data(struct hall_cdev *cdev, packet_data pdata)
{
	struct ak8789_data *data = container_of(cdev, struct ak8789_data, cdev);
	return ak8789_report_data(data,  pdata);
}

static void ak8789_report_delayed_work(struct work_struct *work)
{
	int ret = 0;
	packet_data temp_data, pdata = 0;
//	int auxiliary_gpio_flag = 0;
	struct hall_device *h_dev = container_of(work, struct hall_device, h_delayed_work.work);
	struct hall_device *temp_dev;
	struct ak8789_data *data = platform_get_drvdata(h_dev->pdev);

	if (!data) {
		hwlog_err("ak8789 data null\n");
		return;
	}

	list_for_each_entry(temp_dev, &data->head, list) {
		temp_data = ak8789_get_data(temp_dev);
		pdata |= temp_data << (temp_dev->hall_id << 1);
	}

	hwlog_info("report value:%d\n", pdata);
	ret = ak8789_report_data(data, pdata);
	if (!ret) {
		hwlog_err("report data err\n");
	}
}

static int ak8789_get_common_configs(struct hall_device *hall_dev, struct device_node *node)
{
	int ret;
	int auxiliary_flag = 0;

	ret = of_property_read_u32(node, HALL_TYPE, &hall_dev->hall_type);
	if (ret) {
		hwlog_err("Failed to get type; ret:%d\n", ret);
		goto error;
	}

	ret = of_property_read_u32(node, HALL_WAKEUP_FLAG, &hall_dev->hall_wakeup_flag);
	if(ret) {
		hwlog_err("Failed to get wake_up; ret:%d\n", ret);
		goto error;
	}

	ret = of_property_read_u32(node, HALL_ID, &hall_dev->hall_id);
	if (ret) {
		hwlog_err("Failed to get id; ret:%d\n", ret);
		goto error;
	}

	ret = of_property_read_u32(node, HALL_HW_WAKEUP_SUPPORT, &hall_dev->hall_hw_wakeup_support);
	if (ret) {
		hwlog_err("Failed to get hw wakeup support; ret:%d\n", ret);
		goto error;
	}

	ret = of_property_read_u32(node, HALL_X_COORDINATE, &hall_dev->hall_x_coordinate);
	if (ret) {
		hwlog_err("Failed to get x coordinate; ret:%d\n", ret);
		goto error;
	}

	ret = of_property_read_u32(node, HALL_Y_COORDINATE, &hall_dev->hall_y_coordinate);
	if (ret) {
		hwlog_err("Failed to get y coordinate; ret:%d\n", ret);
		goto error;
	}

	ret = of_property_read_u32(node, HALL_AUXILIARY_ID, &auxiliary_flag);
	if (ret) {
		hwlog_err("Failed to get auxiliary type; ret:%d\n", ret);
		//goto error;
	} else {
		if (auxiliary_flag & 0x01) {
			ret = of_property_read_u32(node, HALL_AUXILIARY_N, &hall_dev->h_info.auxiliary_io[0]);
			if (ret) {
				hwlog_err("Failed to get auxiliary io; ret:%d\n", ret);
				//goto error;
			}
		} else {
			hall_dev->h_info.auxiliary_io[0] = 0;
		}

		if (auxiliary_flag & 0x02) {
			ret = of_property_read_u32(node, HALL_AUXILIARY_S, &hall_dev->h_info.auxiliary_io[1]);
			if (ret) {
				hwlog_err("Failed to get auxiliary io; ret:%d\n", ret);
				//goto error;
			}
		} else {
			hall_dev->h_info.auxiliary_io[1] = 0;
		}
	}
	hwlog_info("[%s] get conf successed\n", __FUNCTION__);
	return 0;

error:
	return -EINVAL;
}

static irqreturn_t ak8789_event_handler(int irq, void *hall_dev)
{
	struct hall_device *h_dev = NULL;
	struct irq_desc *h_desc = NULL;
	int trig_val = 0;
	int ret = 0;
	struct ak8789_data *data = NULL;
#ifdef HALL_TEST
	long irq_time = 0;
	int index ;
	struct timeval now;

	do_gettimeofday(&now);
#endif
	if(! hall_dev) {
//		hwlog_err("[hall][%s] invalid pointer!\n", __FUNCTION__);
		return IRQ_NONE;
	}

	h_desc = irq_to_desc(irq);
	if (!h_desc) {
//		hwlog_err("h_desc null;\n");
		return IRQ_NONE;
	}

	h_dev = (struct hall_device *)hall_dev;

	trig_val = h_desc->irq_data.state_use_accessors & IRQD_TRIGGER_MASK;
	if (trig_val & IRQF_TRIGGER_LOW) {
		ret = irq_set_irq_type(irq, IRQF_TRIGGER_HIGH);
	} else if (trig_val & IRQF_TRIGGER_HIGH) {
		ret = irq_set_irq_type(irq, IRQF_TRIGGER_LOW);
	} else {
//		hwlog_err("Invalid trigger:%d\n", trig_val);
		return IRQ_NONE;
	}

	data = platform_get_drvdata(h_dev->pdev);
	if (!data) {
//		hwlog_err("ak8789 data null\n");
		return IRQ_NONE;
	}

	wake_lock_timeout(&data->wakelock, HZ);
#ifdef HALL_TEST
	if (irq == h_dev->h_info.irq[0]) {
		index = 0;
	} else if (irq == h_dev->h_info.irq[1]) {
		index = 1;
	} else {
//		hwlog_err("Invalid irq, look for irq err. \n");
		return IRQ_NONE;
	}

	irq_time = (now.tv_sec-h_dev->h_info.last_time[index].tv_sec)*HALL_1000000 + (now.tv_usec-h_dev->h_info.last_time[index].tv_usec);

	if (irq_time > HALL_IRQ_ABNORMAL_TIME) {
		atomic_set(&h_dev->h_info.irq_err_count[index], 0);
/* debug code */
//		queue_work(data->hall_wq, &data->inter_work);
	} else if (irq_time <= HALL_IRQ_ABNORMAL_TIME && irq_time > 0) {
		atomic_inc(&h_dev->h_info.irq_err_count[index]);
		queue_work(data->hall_wq, &data->inter_work);
	} else {
		;
//		hwlog_err("irq time get err");
	}
	h_dev->h_info.last_time[index].tv_sec = now.tv_sec;
	h_dev->h_info.last_time[index].tv_usec = now.tv_usec;
#endif
	queue_delayed_work(data->hall_wq, &h_dev->h_delayed_work, HZ/20);

	return IRQ_HANDLED;
}

static void hall_interrupt_abnormity_work(struct work_struct *work)
{
	struct ak8789_data *data = container_of(work, struct ak8789_data, inter_work);
	struct hall_device *temp_dev;
	int count = 0;
	int hall_type;

	list_for_each_entry(temp_dev, &data->head, list) {
		hall_type = temp_dev->hall_type;
		hwlog_info("%s done [hall id:%d][hall type:%d]\n", __FUNCTION__, temp_dev->hall_id, hall_type);
		if (hall_type & 0x01) {
			count = atomic_read(&temp_dev->h_info.irq_err_count[0]);
			hwlog_info("[%s]count:%d[1]\n", __FUNCTION__, count);
			if (count >=3) {
#ifdef HALL_DSM_CONFIG
				/* dsm report err */
				if (!dsm_client_ocuppy(data->hall_dclient)) {
					dsm_client_record(data->hall_dclient, "hall id[%d], north irq abnormity.\n", temp_dev->hall_id);
					dsm_client_notify(data->hall_dclient, DSM_HALL_ERROR_NO);
				}
#endif
				hwlog_err("hall irq abnormity, id[%d], north\n", temp_dev->hall_id);
				count = 0;
				atomic_set(&temp_dev->h_info.irq_err_count[0], 0);
			}
		}
		if (hall_type & 0x02) {
			count = atomic_read(&temp_dev->h_info.irq_err_count[1]);
			hwlog_info("[%s]count:%d[2]\n", __FUNCTION__, count);
			if (count >=3) {
#ifdef HALL_DSM_CONFIG
				/* dsm report err */
				if (!dsm_client_ocuppy(data->hall_dclient)) {
					dsm_client_record(data->hall_dclient, "hall id[%d], south irq abnormity.\n", temp_dev->hall_id);
					dsm_client_notify(data->hall_dclient, DSM_HALL_ERROR_NO);
				}
#endif
				hwlog_err("hall irq abnormity, id[%d], south\n", temp_dev->hall_id);
				count = 0;
				atomic_set(&temp_dev->h_info.irq_err_count[1], 0);
			}
		}
	}

#if 0
	/* dsm report err for debug */
	if (!dsm_client_ocuppy(data->hall_dclient)) {
		dsm_client_record(data->hall_dclient,	"hall id[%d], irq abnormity.\n", temp_dev->hall_id);
		dsm_client_notify(data->hall_dclient, DSM_HALL_ERROR_NO);
	}
#endif
	hwlog_info("%s done\n", __FUNCTION__);
	return;
}

static int ak8789l_request_gpio(struct hall_device *hall_dev, struct device_node *node)
{
	int ret;
	int gpio_t;
	unsigned int gpio;
	int hall_type = hall_dev->hall_type;

	if (hall_type & 0x01) {
		gpio_t = of_get_named_gpio(node, HALL_SINGLE_N_POLE, 0);
		if (!gpio_is_valid(gpio_t)){
			hwlog_err("north pole gpio is invalid\n");
			return -EINVAL;
		}
		gpio = (unsigned int)gpio_t;
		ret = gpio_request(gpio, NORTH_POLE_NAME);
		if (ret < 0) {
			hwlog_err("request north pole gpio err\n");
			return ret;
		}
		hall_dev->h_info.gpio[0] = gpio;
		ret = snprintf(hall_dev->h_info.name[0], HALL_MAX_STRING_LEN, "hall%d_north", hall_dev->hall_id);
		if (ret < 0) {
			hwlog_err("set north irq err. hall id:%d\n", hall_dev->hall_id);
			return ret;
		}
		gpio = 0;
	}

	if (hall_type & 0x02) {
		gpio_t = of_get_named_gpio(node, HALL_SINGLE_S_POLE, 0);
		if (!gpio_is_valid(gpio_t)){
			hwlog_err("north pole gpio is invalid\n");
			return -EINVAL;
		}
		gpio = (unsigned int)gpio_t;
		ret = gpio_request(gpio, SOUTH_POLE_NAME);
		if (ret < 0) {
			hwlog_err("request south pole gpio err\n");
			return ret;
		}
		hall_dev->h_info.gpio[1] = gpio;
		ret = snprintf(hall_dev->h_info.name[1], HALL_MAX_STRING_LEN, "hall%d_south", hall_dev->hall_id);
		if (ret < 0) {
			hwlog_err("set south irq err. hall id:%d\n", hall_dev->hall_id);
			return ret;
		}
	}

	hwlog_info("gpio request done\n");

	return 0;
}

static int ak8789_request_irq(struct hall_device *hall_dev)
{
	int irq;
	unsigned int gpio;
	int ret;
	int wakeup_flag;
	int trigger_val = 0;
	int hall_type = 0;

	if (!hall_dev) {
		hwlog_err("Invalid pointer of hall dev\n");
		return -EINVAL;
	}

	wakeup_flag = hall_dev->hall_wakeup_flag;
	hall_type = hall_dev->hall_type;
	if (hall_type & 0x01) {
		gpio = hall_dev->h_info.gpio[0];
		irq = gpio_to_irq(gpio);
		hall_dev->h_info.irq[0] = irq;
		trigger_val = gpio_get_value(gpio)? IRQF_TRIGGER_LOW: IRQF_TRIGGER_HIGH;
		ret = request_irq(irq, ak8789_event_handler, \
			trigger_val | wakeup_flag, hall_dev->h_info.name[0], hall_dev);
	}

	if (hall_type & 0x02) {
		gpio = hall_dev->h_info.gpio[1];
		irq = gpio_to_irq(gpio);
		hall_dev->h_info.irq[1] = irq;
		trigger_val = gpio_get_value(gpio)? IRQF_TRIGGER_LOW: IRQF_TRIGGER_HIGH;
		ret = request_irq(irq, ak8789_event_handler, \
			trigger_val | wakeup_flag, hall_dev->h_info.name[1], hall_dev);
	}

	hwlog_info("irq done[0:%d][1:%d]\n", hall_dev->h_info.irq[0], hall_dev->h_info.irq[1]);

	return 0;
}

static int ak8789_probe(struct platform_device *pdev)
{
	struct hall_device *hall;
	struct ak8789_data	*data;
	struct device_node *node, *temp;
	int ret = 0, num_halls = 0, count = 0;
	int default_state = 0;
	const char *state;

	node = pdev->dev.of_node;
	if (node == NULL)
		return -ENODEV;

	temp = NULL;
	while((temp = of_get_next_child(node, temp)))
		num_halls++;

	if (!num_halls)
		return -ECHILD;

	data = (struct ak8789_data *)devm_kzalloc(&pdev->dev, sizeof(struct ak8789_data), GFP_KERNEL);
	if (!data) {
		hwlog_err("Failed to allocate memory for data\n");
		return -ENOMEM;
	}

	data->state = 0;
	data->pdev = pdev;

	INIT_LIST_HEAD(&data->head);
	wake_lock_init(&data->wakelock, WAKE_LOCK_SUSPEND, "hall");
	spin_lock_init(&data->spinlock);
	INIT_WORK(&data->inter_work, hall_interrupt_abnormity_work);

	data->hall_wq = create_singlethread_workqueue("hall_wq");
	if(IS_ERR(data->hall_wq)) {
		hwlog_err("[%s] work_wq kmalloc error!\n", __FUNCTION__);
		ret = -ENOMEM;
		goto free_wake_lock;
	}

#ifdef HALL_DATA_REPORT_INPUTDEV
	ret = ak8789_input_register(data);
	if (ret) {
		hwlog_err("hall input register failed\n");
		goto free_wq;
	}
#endif

#ifdef HALL_TEST
/* ak8789 init_data */
	ak8789_test_info_init(&data->cdev);
#endif

	ret = hall_register(&data->cdev);
	if (ret < 0) {
		goto err_register_err;
	}

	for_each_child_of_node(node, temp) {
		ret = of_property_read_string(temp, HALL_DEFAULT_STATE, &state);
		if (!ret) {
			if (strncmp(state, "on", sizeof("on")) == 0)
				default_state = true;
		} else
			goto free_hall_dev;

		if (default_state) {
			count++;
			hall = devm_kzalloc(&pdev->dev, (sizeof(struct hall_device)), GFP_KERNEL);
			if (!hall) {
				hwlog_err("Failed to allocate memory for hall dev\n");
				goto free_hall_dev;
			}

			hall->pdev = pdev;

			INIT_DELAYED_WORK(&hall->h_delayed_work, ak8789_report_delayed_work);

			ret = ak8789_get_common_configs(hall, temp);
			if (ret) {
				hwlog_err("Failed to read common hall configuaration, ret = %d\n", ret);
				goto free_hall_dev;
			}
			ret = snprintf(hall->name, HALL_MAX_STRING_LEN, "hall%d\n", hall->hall_id);
			if (ret<0) {
				hwlog_err("Failed to set hall dev name.\n");
				ret = -EINVAL;
				goto free_hall_dev;
			}

			ret = ak8789l_request_gpio(hall, temp);
			if (ret < 0) {
				hwlog_err("hall request gpio err\n");
			}

			ret = ak8789_request_irq(hall);
			if (ret) {
				hwlog_err("hall request irq failed\n");
				goto free_hall_dev;
			}

			list_add_tail(&hall->list, &data->head);
#ifdef HALL_TEST
			atomic_set(&hall->h_info.irq_err_count[0], 0);
			atomic_set(&hall->h_info.irq_err_count[1], 0);
			hall->h_info.last_time[0].tv_sec = 0;
			hall->h_info.last_time[0].tv_usec = 0;
			hall->h_info.last_time[1].tv_sec = 0;
			hall->h_info.last_time[1].tv_usec = 0;
#endif
		}
		default_state = 0;
	}

	data->count = count;
	data->cdev.hall_count = count;
	data->cdev.hall_get_state = ak8789_get_status;
	data->cdev.hall_report_debug_data = ak8789_report_debug_data;
	data->cdev.hall_report_state = ak8789_report_status;
	data->cdev.hall_get_info = ak8789_get_info;
#ifdef HALL_TEST
	data->cdev.hall_set_report_value = ak8789_set_report_value;
#ifdef HALL_DSM_CONFIG
	data->hall_dclient = dsm_register_client(&dsm_hall);
	if (!data->hall_dclient) {
		hwlog_err("hall dsm register err!\n");
		goto free_hall_dev;
	}

	hwlog_info("ak8789 dsm register success.\n");
#endif
#endif

	platform_set_drvdata(pdev, data);
#ifdef HALL_DATA_REPORT_INPUTHUB
	data_ak8789 = data;
#endif

	hwlog_info("ak8789 probe success.\n");
	return 0;

free_hall_dev:
	while(!list_empty(&data->head)) {
		hall = list_first_entry(&data->head, struct hall_device, list);
		list_del(&hall->list);
		kfree(hall);
	}

	hall_unregister(&data->cdev);

err_register_err:
#ifdef HALL_DATA_REPORT_INPUTDEV
	ak8789_input_unregister(data);
free_wq:
#endif
	destroy_workqueue(data->hall_wq);
free_wake_lock:
	wake_lock_destroy(&data->wakelock);

	return ret;
}

static int ak8789_remove(struct platform_device *pdev)
{
	struct ak8789_data *data = platform_get_drvdata(pdev);
	struct hall_device *data_dev;

	if (!data) {
		hwlog_err("ak8789 data null\n");
		return -ENOMEM;
	}

	while(!list_empty(&data->head)) {
		data_dev = list_first_entry(&data->head, struct hall_device, list);
		list_del(&data_dev->list);
		kfree(data_dev);
	}

	hall_unregister(&data->cdev);

#ifdef HALL_DATA_REPORT_INPUTDEV
	ak8789_input_unregister(data);
#endif

	destroy_workqueue(data->hall_wq);
	wake_lock_destroy(&data->wakelock);

	return 0;
}

struct platform_driver ak8789_driver = {
	.probe = ak8789_probe,
	.remove = ak8789_remove,
	.driver = {
		.name = HALL_SENSOR_NAME,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(ak8789_match_table),
	},
};

static int __init ak8789_init(void)
{
	hwlog_info("init!\n");
	return platform_driver_register(&ak8789_driver);
}

static void __exit ak8789_exit(void)
{
	hwlog_info("exit!\n");
	platform_driver_unregister(&ak8789_driver);
}

module_init(ak8789_init);
module_exit(ak8789_exit);

MODULE_AUTHOR("Huawei");
MODULE_DESCRIPTION("Ak8789 driver");
MODULE_LICENSE("GPL");
