#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/pinctrl/consumer.h>
#include <linux/gpio.h>
#include <linux/kernel.h>
#include <huawei_platform/log/hw_log.h>
#include <linux/slab.h>
#include <linux/kdev_t.h>

#define IRDA_COMPATIBLE_ID		"huawei,irda_maxim"
#define IRDA_POWER_CONTROL_GPIO		"gpio_power_control"
#define IRDA_BUFF_SIZE			50
#define HWLOG_TAG irda
HWLOG_REGIST();

struct irda_private_data {
	struct gpio gpio_reset;
};

struct irda_device {
	struct platform_device *pdev;
	struct device *dev;
	struct class *irda_class;
	struct irda_private_data pdata;
};

static ssize_t power_config_get(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct irda_device *irda_dev = dev_get_drvdata(dev);

	return snprintf(buf, IRDA_BUFF_SIZE, "%d\n", gpio_get_value(irda_dev->pdata.gpio_reset.gpio));
}

static ssize_t power_config_set(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int ret = -1;
	unsigned long state = 0;
	struct irda_device *irda_dev = dev_get_drvdata(dev);

	if (!strict_strtol(buf, 10, &state)){
		gpio_direction_output(irda_dev->pdata.gpio_reset.gpio, !!state);
		hwlog_info("current state:%d\n", !!state);
		ret = count;
	}
	return ret;
}

static DEVICE_ATTR(power_cfg, 0660, power_config_get, power_config_set);

static int irda_probe(struct platform_device *pdev)
{
	int ret;
	int gpio;
	struct device_node *np;
	struct irda_device *irda_dev;

	np= pdev->dev.of_node;
	if (np ==NULL) {
		hwlog_err("none device\n");
		ret = -ENODEV;
		goto error;
	}

	irda_dev = (struct irda_device *)kzalloc(sizeof(struct irda_device), GFP_KERNEL);
	if (NULL == irda_dev) {
		hwlog_err("Failed to allocate irda_dev\n");
		ret = -ENOMEM;
		goto error;
	}

	gpio = of_get_named_gpio(np, IRDA_POWER_CONTROL_GPIO, 0);
	if (!gpio_is_valid(gpio)) {
		hwlog_err("gpio is not valid\n");
		ret =  -EINVAL;
		goto free_irda_dev;
	}

	irda_dev->pdata.gpio_reset.gpio = (unsigned int)gpio;
	ret = gpio_request(irda_dev->pdata.gpio_reset.gpio, "irda_gpio");
	if (ret) {
		hwlog_err("Failed to request gpio[%ud]; ret:%d", irda_dev->pdata.gpio_reset.gpio, ret);
		goto free_irda_dev;
	}

	irda_dev->irda_class = class_create(THIS_MODULE, "irda");
	if (IS_ERR(irda_dev->irda_class)) {
		ret = PTR_ERR(irda_dev->irda_class);
		hwlog_err("Failed to create irda class; ret:%d\n", ret);
		goto free_gpio;
	}

	irda_dev->dev = device_create(irda_dev->irda_class, NULL, MKDEV(0, 0), NULL, "%s", "irda_maxim");
	if (IS_ERR(irda_dev->dev)) {
		ret = PTR_ERR(irda_dev->dev);
		hwlog_err("Failed to create dev; ret:%d\n", ret);
		goto free_class;
	}

	ret = device_create_file(irda_dev->dev, &dev_attr_power_cfg);
	if (ret) {
		hwlog_err("Failed to create file; ret:%d\n", ret);
		goto free_dev;
	}

	gpio_direction_output(irda_dev->pdata.gpio_reset.gpio, 0);
	dev_set_drvdata(irda_dev->dev, irda_dev);
	platform_set_drvdata(pdev, irda_dev);

	hwlog_info("platform device probe success\n");
	return 0;

free_dev:
	device_destroy(irda_dev->irda_class, irda_dev->dev->devt);
free_class:
	class_destroy(irda_dev->irda_class);
free_gpio:
	gpio_free(irda_dev->pdata.gpio_reset.gpio);
free_irda_dev:
	kfree(irda_dev);
error:
	return ret;
}

static int irda_remove(struct platform_device *pdev)
{
	struct irda_device *irda_dev = platform_get_drvdata(pdev);

	device_remove_file(irda_dev->dev, &dev_attr_power_cfg);
	device_destroy(irda_dev->irda_class, irda_dev->dev->devt);
	class_destroy(irda_dev->irda_class);
	gpio_free(irda_dev->pdata.gpio_reset.gpio);
	kfree(irda_dev);

	return 0;
}

static const struct of_device_id irda_match_table [] = {
		{
			.compatible = IRDA_COMPATIBLE_ID,
			.data = NULL,
		},
		{
		},
};

MODULE_DEVICE_TABLE(of, irda_match_table);

static struct platform_driver irda_driver = {
	.probe = irda_probe,
	.remove = irda_remove,
	.driver = {
		.name = "irda_maxq616",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(irda_match_table),
	},
};

static int irda_remote_init(void)
{
	return platform_driver_register(&irda_driver);
}

static void irda_remote_exit(void)
{
	platform_driver_unregister(&irda_driver);
}

module_init(irda_remote_init);
module_exit(irda_remote_exit);

MODULE_AUTHOR("Huawei");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("irda power control driver");
