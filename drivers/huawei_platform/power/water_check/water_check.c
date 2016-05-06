#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/of_irq.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/pinctrl/consumer.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define VALID_IRQ_INTERVAL 3
#define LOG_LEN 100
#define MAX_LOG_COUNT 4
#define WATER_CHECK_KOBJ_NAME "water_check"

enum {
	POSITION_EAR = 0,
	POSITION_USB,
};

struct water_check_info {
	int gpio_ear;
	int gpio_usb;
	int irq_ear;
	int irq_usb;
	int last_gpio_ear_value;
	int last_gpio_usb_value;
	struct pinctrl *pinctrl;
	struct mutex log_save_mutex;
	struct platform_device *pdev;
	u8 log_buf_bitmap;
	char log_buf[LOG_LEN * MAX_LOG_COUNT];
};

const char log_head[] = "water check is triggered, position:";
const char water_in[] = "  water in";
const char water_out[] = "  water disappear";

static int save_water_check_log(struct water_check_info *info, int position, int gpio_value)
{
	struct tm tm_rtc;
	char *tmp_buf;
	int tmp_len = 0;
	int i;

	mutex_lock(&info->log_save_mutex);

	for (i = 0; i < MAX_LOG_COUNT; i++) {
		if (!(info->log_buf_bitmap & (1 << i)))
			break;
	}
	if (i == MAX_LOG_COUNT) {
		pr_err("log buf is full, no space to store new log\n");
		mutex_unlock(&info->log_save_mutex);
		return 0;
	}
	tmp_buf = &info->log_buf[0] + i * LOG_LEN;
	memset(tmp_buf, 0, LOG_LEN);

	tmp_len += snprintf(tmp_buf, sizeof(log_head), log_head);
	switch (position) {
		case POSITION_EAR:
			tmp_len += snprintf(tmp_buf + tmp_len, 4, "ear");
			break;
		case POSITION_USB:
			tmp_len += snprintf(tmp_buf + tmp_len, 4, "usb");
			break;
		default:
			pr_err("unknown water check record postion\n");
	}

	if (gpio_value)
		tmp_len += snprintf(tmp_buf + tmp_len,
					LOG_LEN - tmp_len, water_out);
	else
		tmp_len += snprintf(tmp_buf + tmp_len,
					LOG_LEN - tmp_len, water_in);

	tmp_len += snprintf(tmp_buf + tmp_len, LOG_LEN - tmp_len,
					"  gpio value:%d", gpio_value);

	info->log_buf_bitmap |= 1 << i;
	/* notify the userspace that new log is ready */
	sysfs_notify(&info->pdev->dev.kobj, NULL, "poll_water_check");
	mutex_unlock(&info->log_save_mutex);

	return 0;

}

static ssize_t log_copy_to_userspace(struct device *dev, struct device_attribute *attr, char *buf)
{
	int i;
	struct water_check_info *info = dev_get_drvdata(dev);

	int len = 0;

	mutex_lock(&info->log_save_mutex);
	for (i = 0; i < MAX_LOG_COUNT; i++) {
		if (info->log_buf_bitmap >> i) {
			len = snprintf(buf + len, LOG_LEN, &info->log_buf[0] + i * LOG_LEN);
			info->log_buf_bitmap &= ~(1 << i);
			memset(&info->log_buf[0] + i * LOG_LEN, 0, LOG_LEN);
		}
	}
	mutex_unlock(&info->log_save_mutex);

	return len;
}

static DEVICE_ATTR(poll_water_check, (S_IRUSR | S_IRUGO), log_copy_to_userspace, NULL);

static irqreturn_t irq_ear_handler(int irq, void *p)
{
	int gpio_value;
	static u64 pre_jiffies = 0;
	u64 cur_jiffies;
	struct water_check_info *info = (struct water_check_info *)p;

	cur_jiffies = get_jiffies_64();
	if (pre_jiffies) {
		if (cur_jiffies - pre_jiffies < HZ * VALID_IRQ_INTERVAL) {
			pr_info("ear irq is triggered too frequently, ignore this one\n");
			pre_jiffies = cur_jiffies;
			return IRQ_HANDLED;
		}
	}

	pre_jiffies = cur_jiffies;

	gpio_value = gpio_get_value_cansleep(info->gpio_ear);
	pr_info("receive gpio_ear irq, gpio_value:%d\n", gpio_value);

	if (info->last_gpio_ear_value ^ gpio_value) {
		info->last_gpio_ear_value = gpio_value;
		save_water_check_log(info, POSITION_EAR, gpio_value);
	} else {
		pr_info("not a valid ear rasing or falling irq, ignore\n");
	}

	return IRQ_HANDLED;
}

static irqreturn_t irq_usb_handler(int irq, void *p)
{
	int gpio_value = -1;
	static u64 pre_jiffies = 0;
	u64 cur_jiffies;
	struct water_check_info *info = (struct water_check_info *)p;

	cur_jiffies = get_jiffies_64();
	if (pre_jiffies) {
		if (cur_jiffies - pre_jiffies < HZ * VALID_IRQ_INTERVAL) {
			pr_info("usb irq is triggered too frequently, ignore this one\n");
			pre_jiffies = cur_jiffies;
			return IRQ_HANDLED;
		}
	}

	pre_jiffies = cur_jiffies;

	gpio_value = gpio_get_value_cansleep(info->gpio_usb);
	pr_info("receive gpio_usb irq, gpio_value:%d\n", gpio_value);

	if (info->last_gpio_usb_value ^ gpio_value) {
		info->last_gpio_usb_value = gpio_value;
		save_water_check_log(info, POSITION_USB, gpio_value);
	} else {
		pr_info("not a valid usb rasing or falling irq, ignore\n");
	}

	return IRQ_HANDLED;
}

static int water_check_probe(struct platform_device *pdev)
{
	int ret = -1;
	struct water_check_info *info = NULL;
	struct device_node *node = pdev->dev.of_node;
	struct pinctrl_state *pinctrl_def;

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->pinctrl = devm_pinctrl_get(&pdev->dev);
	if (IS_ERR(info->pinctrl)) {
		pr_err("failed to get pinctrl\n");
		goto err_pinctrl_get;
	}

	pinctrl_def = pinctrl_lookup_state(info->pinctrl, "default");
	if (IS_ERR(pinctrl_def)) {
		pr_err("failed to get pinctrl_def\n");
		goto err_pinctrl_look_state;
	}

	/* configure the gpios as no-pull state */
	ret = pinctrl_select_state(info->pinctrl, pinctrl_def);
	if (ret) {
		pr_err("failed to set pins to default state\n");
		goto err_pinctrl_set;
	}

	mutex_init(&info->log_save_mutex);

	info->gpio_ear = of_get_named_gpio(node, "gpio_ear", 0);
	if (info->gpio_ear < 0) {
		pr_err("failed to get gpio_ear\n");
		goto err_gpio_of_get;
	}
	info->gpio_usb = of_get_named_gpio(node, "gpio_usb", 0);
	if (info->gpio_usb < 0) {
		pr_err("failed to get gpio_usb\n");
		goto err_gpio_of_get;
	}

	ret = gpio_request(info->gpio_ear, "water_check_ear");
	if (ret < 0) {
		pr_err("failled to request gpio_ear:%d\n", info->gpio_ear);
		goto err_gpio_request_ear;
	}
	ret = gpio_request(info->gpio_usb, "water_check_usb");
	if (ret < 0) {
		pr_err("failled to request gpio_usb:%d\n", info->gpio_usb);
		goto err_gpio_request_usb;
	}

	/* set the gpio as input, for water check interrupt source */
	ret = gpio_direction_input(info->gpio_ear);
	if (ret) {
		pr_err("failed to set gpio_ear output high\n");
		goto err_gpio_direction_set;
	}
	ret = gpio_direction_input(info->gpio_usb);
	if (ret) {
		pr_err("failed to set gpio_usb output high\n");
		goto err_gpio_direction_set;
	}

	info->irq_ear = gpio_to_irq(info->gpio_ear);
	if (ret < 0) {
		pr_err("failed to get irq_ear\n");
		goto err_gpio_to_irq;
	}
	info->irq_usb = gpio_to_irq(info->gpio_usb);
	if (ret < 0) {
		pr_err("failed to get irq_usb\n");
		goto err_gpio_to_irq;
	}

	info->last_gpio_ear_value = gpio_get_value_cansleep(info->gpio_ear);
	info->last_gpio_usb_value = gpio_get_value_cansleep(info->gpio_usb);

	ret = request_threaded_irq(info->irq_ear, NULL, irq_ear_handler,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING
				| IRQF_NO_SUSPEND, "irq_ear", info);
	if (ret < 0) {
		pr_err("failed to register irq_ear\n");
		goto err_request_irq_ear;
	}
	ret = request_threaded_irq(info->irq_usb, NULL, irq_usb_handler,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING
				| IRQF_NO_SUSPEND, "irq_usb", info);
	if (ret < 0) {
		pr_err("failed to register irq_usb\n");
		goto err_request_irq_usb;
	}

	dev_set_drvdata(&pdev->dev, info);
	ret = sysfs_create_file(&pdev->dev.kobj, &dev_attr_poll_water_check.attr);
	if (ret) {
		pr_err("failed to create the poll node\n");
		goto err_poll_create;
	}
	/* The device name created by system is its dts name and a number postfix,
	 * the number is determined by the position in dts, so the device name and
	 * the sys path are random, change it, then userspace can access the node
	 * with a uniform path.
	 */
	device_rename(&pdev->dev, "water_check");
	info->pdev = pdev;
	pr_info("water check driver probes successfully\n");
	return ret;

err_poll_create:
	free_irq(info->irq_usb, info);
err_request_irq_usb:
	free_irq(info->irq_ear, info);
err_request_irq_ear:
err_gpio_to_irq:
err_gpio_direction_set:
	gpio_free(info->gpio_usb);
err_gpio_request_usb:
	gpio_free(info->gpio_ear);
err_gpio_request_ear:
err_gpio_of_get:
	mutex_destroy(&info->log_save_mutex);
err_pinctrl_set:
err_pinctrl_look_state:
	devm_pinctrl_put(info->pinctrl);
err_pinctrl_get:
	devm_kfree(&pdev->dev, info);
	return ret;
}

static int water_check_remove(struct platform_device *pdev)
{
	struct water_check_info *info = dev_get_drvdata(&pdev->dev);

	sysfs_remove_file(&pdev->dev.kobj, &dev_attr_poll_water_check.attr);
	free_irq(info->irq_usb, info);
	free_irq(info->irq_ear, info);
	gpio_free(info->gpio_usb);
	gpio_free(info->gpio_ear);
	mutex_destroy(&info->log_save_mutex);
	devm_pinctrl_put(info->pinctrl);
	devm_kfree(&pdev->dev, info);
	dev_set_drvdata(&pdev->dev, NULL);

	return 0;
}

static struct of_device_id water_check_of_match[] = {
	{.compatible = "hisilicon,water_check",},
	{},
};

static struct platform_driver water_check_drv = {
	.probe		= water_check_probe,
	.remove		= water_check_remove,
	.driver		= {
		.owner		= THIS_MODULE,
		.name		= "water_check",
		.of_match_table	= water_check_of_match,
	},
};

static int __init water_check_init(void)
{
	return platform_driver_register(&water_check_drv);
}

static void __exit water_check_exit(void)
{
	platform_driver_unregister(&water_check_drv);
}

/*
 * The gpios used for ear and usb water check are codec hi6402 gpio0 and gpio2,
 * while the codec hi6402 driver will change the gpio0 configuration, so call
 * our probe function later to make sure our configuration takes effect.
 */
late_initcall_sync(water_check_init);
module_exit(water_check_exit);

MODULE_DESCRIPTION("This module uses for water check at phone positon of ear and usb port");
MODULE_LICENSE("GPL v2");
