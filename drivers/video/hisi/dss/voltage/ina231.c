/*
 * Driver for ina230 or ina231 power monitor chips
 *
 * Copyright (c) 2013- Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>

struct class *ina231_class;

/* common register definitions */
#define INA231_CONFIG			0x00
#define INA231_SHUNT_VOLTAGE	0x01 /* readonly */
#define INA231_BUS_VOLTAGE	0x02 /* readonly */
#define INA231_POWER			0x03 /* readonly */
#define INA231_CURRENT			0x04 /* readonly */
#define INA231_CALIBRATION		0x05
#define INA231_MASK_ENABLE	0x06
#define INA231_ALERT_LIMIT		0x07

/* register count */
#define INA231_MAX_REGS		8

struct ina231_config {
	u16 config_sleep_in;
	u16 config_reset;
	u16 config_work;
	u16 calibrate_content;
	u16 mask_enable_content;
	u16 alert_limit_content;

	int shunt_lsb;
	int shunt_max;
	int bus_voltage_lsb;	/* uV */
	int bus_voltage_max;

	int current_lsb;	/* uA */
	int current_max;
	int power_lsb;		/* uW */
	int power_max;
};

struct ina231_data {
	struct device *dev;
	struct i2c_client *client;
	const struct ina231_config *config;
	int type;
	u16 regs[INA231_MAX_REGS];
};

static const struct ina231_config ina231_config[] = {
/*avdd*/
	[0] = {
		.config_sleep_in = 0x4124,
		.config_reset = 0x1000,
		.config_work = 0x4377,
		.calibrate_content = 0x1105,
		.mask_enable_content = 0x0,
		.alert_limit_content = 0x0,

		.shunt_lsb = 2500,  /* 2500nV/bit */
		.bus_voltage_lsb = 1250, /* 1250uV/bit */
		.current_lsb = 25, /* 25uA/bit */
		.power_lsb = 625, /* 625 uW/bit */
	},
/*elvdd*/
	[1] = {
		.config_sleep_in = 0x4124,
		.config_reset = 0x1000,
		.config_work = 0x4377,
		.calibrate_content = 0x5000,
		.mask_enable_content = 0x0,
		.alert_limit_content = 0x0,

		.shunt_lsb = 2500,  /* 2500nV/bit */
		.bus_voltage_lsb = 1250, /* 1250uV/bit */
		.current_lsb = 25, /* 25uA/bit */
		.power_lsb = 625, /* 625 uW/bit */
	},
};

static ssize_t ina231_show_value(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct ina231_data *idata = NULL;
	struct i2c_client *client = NULL;
	int shunt_lsb = 0; /* 0nV/bit */
	int bus_voltage_lsb = 0; /* 0mV/bit */
	int current_lsb = 0; /* 0uA/bit */
	int power_lsb = 0; /* 0uW/bit */
	int i = 0;

	if (!dev)
		return snprintf(buf, PAGE_SIZE, "dev is null\n");

	idata = dev_get_drvdata(dev);
	if (!idata)
		return snprintf(buf, PAGE_SIZE, "data is null\n");

	client = idata->client;
	if(!client)
		return snprintf(buf, PAGE_SIZE, "client is null\n");

	for (i = 0; i < INA231_MAX_REGS; i ++)
		idata->regs[i]= i2c_smbus_read_word_swapped(client, i);

	shunt_lsb = idata->config->shunt_lsb;
	bus_voltage_lsb = idata->config->bus_voltage_lsb;
	power_lsb = idata->config->power_lsb;
	current_lsb = idata->config->current_lsb;

	printk("[client addr=0x%x]shunt_lsb=%d(nV/bit), bus_voltage_lsb=%d(uV/bit),power_lsb=%d(uW/bit),current_lsb=%d(uA/bit)\n",
				client->addr, shunt_lsb, bus_voltage_lsb, power_lsb, current_lsb);
	printk("shunt_read=0x%x, bus_voltage_read=0x%x,power_read=0x%x,current_read=0x%x\n",
				idata->regs[INA231_SHUNT_VOLTAGE], idata->regs[INA231_BUS_VOLTAGE], idata->regs[INA231_POWER], idata->regs[INA231_CURRENT]);
	printk("Shunt_voltage:%ld(nV), Bus_voltage:%ld(uV), Power:%ld(uW), Current:%ld(uA), Mask_en:0x%0x\n",
				((long)(s16)idata->regs[INA231_SHUNT_VOLTAGE])*shunt_lsb,
				((long)(s16)idata->regs[INA231_BUS_VOLTAGE])*bus_voltage_lsb,
				((long)(s16)idata->regs[INA231_POWER])*power_lsb,
				((long)(s16)idata->regs[INA231_CURRENT])*current_lsb,
				(u16)idata->regs[INA231_MASK_ENABLE]);

	return snprintf(buf, PAGE_SIZE, "Bus_voltage:%ld, Power:%ld, Current:%ld\n",
				((long)(s16)idata->regs[INA231_BUS_VOLTAGE])*bus_voltage_lsb,
				((long)(s16)idata->regs[INA231_POWER])*power_lsb,
				((long)(s16)idata->regs[INA231_CURRENT])*current_lsb);
}

static ssize_t ina231_store_debug(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	int ret = 0;
	struct i2c_client *client = NULL;
	struct ina231_data *idata = NULL;
	u16 config = 0;
	u16 calibration = 0;
	u16 mask_en = 0;
	u16 alert_limit = 0;

	ret = sscanf(buf, "config=0x%x, calibration=0x%x, mask_en=0x%x, alert_limit=0x%x", 
				&config, &calibration, &mask_en, &alert_limit);
	if (ret < 0) {
		printk("check your input!!!\n");
		return count;
	}

	if (!dev) {
		printk("dev is null\n");
		return -1;
	}

	idata = dev_get_drvdata(dev);
	if (!idata) {
		printk("idata is null\n");
		return -1;
	}

	client = idata->client;
	if(!client) {
		printk("client is null\n");
		return -1;
	}

	printk("[client addr=0x%x] config=0x%x, calibration=0x%x, mask_en=0x%x, alert_limit=0x%x\n",
			client->addr, config, calibration, mask_en, alert_limit);

	/* configuration */
	i2c_smbus_write_word_swapped(client, INA231_CONFIG, config);
	/* set calibrate*/
	i2c_smbus_write_word_swapped(client, INA231_CALIBRATION, calibration);
	/*Mask_enable*/
	i2c_smbus_write_word_swapped(client, INA231_MASK_ENABLE, mask_en);
	/*set alert limit*/
	i2c_smbus_write_word_swapped(client, INA231_ALERT_LIMIT, alert_limit);

	return count;
}

static ssize_t ina231_store_set(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct i2c_client *client = NULL;
	struct ina231_data *idata = NULL;
	u8 cmd;
	int ret = 0;

	if (!dev)
		return -1;

	ret = sscanf(buf, "%d", &cmd);
	if (ret < 0) {
		printk("check your input!!!\n");
		return -1;
	}

	idata = dev_get_drvdata(dev);
	if (!idata)
		return -1;

	client = idata->client;
	if(!client)
		return -1;

	printk("[client addr=0x%x]config_sleep_in:0x%x, config_work:0x%x, calibration:0x%x, mask_en:0x%x, alert_limit:0x%x\n",
			client->addr,
			idata->config->config_sleep_in,
			idata->config->config_work,
			idata->config->calibrate_content,
			idata->config->mask_enable_content,
			idata->config->alert_limit_content);

	if (cmd) {
		printk("goto work mode, starting testing\n");
		/* configuration */
		i2c_smbus_write_word_swapped(client, INA231_CONFIG, idata->config->config_work);
		/* set calibrate*/
		i2c_smbus_write_word_swapped(client, INA231_CALIBRATION, idata->config->calibrate_content);
		/*Mask_enable*/
		i2c_smbus_write_word_swapped(client, INA231_MASK_ENABLE, idata->config->mask_enable_content);
		/*set alert limit*/
		i2c_smbus_write_word_swapped(client, INA231_ALERT_LIMIT, idata->config->alert_limit_content);
	} else {
		printk("goto sleep mode, ending testing\n");
		/* configuration to sleep */
		i2c_smbus_write_word_swapped(client, INA231_CONFIG, idata->config->config_sleep_in);
	}
	return count;
}

/* config for debug*/
static DEVICE_ATTR(ina231_debug, S_IWUSR, NULL, ina231_store_debug);

/*test*/
static DEVICE_ATTR(ina231_set, S_IWUSR, NULL, ina231_store_set);

/* get value */
static DEVICE_ATTR(ina231_value, S_IRUGO, ina231_show_value, NULL);


/* pointers to created device attributes */
static struct attribute *ina231_attributes[] = {
	&dev_attr_ina231_debug.attr,
	&dev_attr_ina231_value.attr,
	&dev_attr_ina231_set.attr,
	NULL,
};

static const struct attribute_group ina231_group = {
	.attrs = ina231_attributes,
};

static int ina231_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = client->adapter;
	struct ina231_data *idata;
	int ret = 0;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA))
		return -ENODEV;

	idata = devm_kzalloc(&client->dev, sizeof(*idata), GFP_KERNEL);
	if (!idata)
		return -ENOMEM;

	/* set the device type */
	idata->type = id->driver_data;
	idata->config = &ina231_config[idata->type];
	idata->client = client;

	/* communication check and reset device*/
	ret = i2c_smbus_write_word_swapped(client, INA231_CONFIG, idata->config->config_reset);
	if (ret < 0) {
		dev_info(&client->dev, "%s reset failed\n", client->name);
		return -ENODEV;
	}
	mdelay(20);

	/* goto sleep */
	i2c_smbus_write_word_swapped(client, INA231_CONFIG, idata->config->config_sleep_in);

	i2c_set_clientdata(client, idata);

	idata->dev = device_create(ina231_class, NULL, 0, NULL, "%s", client->name);
	if (IS_ERR(idata->dev)) {
		/* Not fatal */
		printk(KERN_WARNING "Unable to create device; errno = %ld\n", PTR_ERR(idata->dev));
		idata->dev = NULL;
	} else {
		dev_set_drvdata(idata->dev, idata);
		ret = sysfs_create_group(&idata->dev->kobj, &ina231_group);
		if (ret)
			return ret;
	}

	dev_info(&client->dev, "name:%s(address:0x%x) probe successfully\n", client->name, client->addr);
	return 0;
}

static int ina231_remove(struct i2c_client *client)
{
	sysfs_remove_group(&client->dev.kobj, &ina231_group);
	return 0;
}

static const struct i2c_device_id ina231_id[] = {
	{"ina231_0", 0},
	{"ina231_1", 1},
	{ },
};
MODULE_DEVICE_TABLE(i2c, ina231_id);

static struct of_device_id ina231_match_table[] = {
	{
		.compatible = "huawei,ina231_0",
		.data = NULL,
	},
	{
		.compatible = "huawei,ina231_1",
		.data = NULL,
	},
	{ },
};

MODULE_DEVICE_TABLE(of, ina231_of_match);

static struct i2c_driver ina231_driver = {
	.probe		= ina231_probe,
	.remove		= ina231_remove,
	.shutdown = NULL,
	.driver = {
		.name = "huawei_ina231",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(ina231_match_table),
	},
	.id_table = ina231_id,
};

static int __init ina231_module_init(void)
{
	int ret = 0;

	ina231_class = class_create(THIS_MODULE, "ina231");
	if (IS_ERR(ina231_class)) {
		printk(KERN_WARNING "Unable to create ina231 class; errno = %ld\n", PTR_ERR(ina231_class));
		ina231_class = NULL;
	}

	ret = i2c_add_driver(&ina231_driver);
	if (ret)
		pr_err("Unable to register ina231 driver\n");

	return ret;
}

late_initcall(ina231_module_init);

MODULE_DESCRIPTION("ina231 driver");
MODULE_LICENSE("GPL");
