/*
 *
 * Copyright (c) 2011-2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 *
 * Discription:
 *     3630 using gpio_203 realizing volume-up-key and gpio_204
 * realizing volume-down-key instead of KPC in kernel, only support simple
 * key-press at currunt version, not support combo-keys.
 *     6620 using gpio_12 realizing volume-up-key and gpio_13
 * realizing volume-down-key.
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/clk.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/regulator/consumer.h>
#include <linux/pinctrl/consumer.h>
#include <linux/wakelock.h>
#include <asm/irq.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>

#if defined (CONFIG_HUAWEI_DSM)
#include <dsm/dsm_pub.h>
#endif

#define TRUE					(1)

#define GPIO_KEY_PRESS      	(1)
#define GPIO_KEY_RELEASE     (0)


#define GPIO_HIGH_VOLTAGE   	 	(1)
#define GPIO_LOW_VOLTAGE    	 	(0)
#define TIMER_DEBOUNCE				(15)

#if defined (CONFIG_HUAWEI_DSM)
#define PRESS_KEY_INTERVAL	(80)   //the minimum press interval
#define STATISTIC_INTERVAL	(60) 	//the statistic interval for key event
#define MAX_PRESS_KEY_COUNT	(120)   //the default press count for a normal use

static int volume_up_press_count = 0;
static int volume_down_press_count = 0;
static unsigned long volume_up_last_press_time = 0;
static unsigned long volume_down_last_press_time = 0;
static struct wake_lock volume_up_key_lock;
static struct wake_lock volume_down_key_lock;
static struct timer_list dsm_gpio_key_timer; //used to reset the statistic variable

static struct dsm_dev dsm_key = {
	.name = "dsm_key",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
	.fops = NULL,
	.buff_size = 1024,
};

static struct dsm_client *key_dclient = NULL;
#endif

#ifdef CONFIG_VOLUME_KEY_MASK
#define VOLUME_KEY_ENABLE_MASK   	 	(0)
#define VOLUME_KEY_DISABLE_MASK    	 	(1)
static int key_mask_ctl = VOLUME_KEY_ENABLE_MASK;
static int key_mask_flag = VOLUME_KEY_ENABLE_MASK;
#endif

struct hisi_gpio_key {
	struct input_dev		*input_dev;
	struct delayed_work	gpio_keyup_work;
	struct delayed_work	gpio_keydown_work;
	struct timer_list		key_up_timer;
	struct timer_list		key_down_timer;
	int    				gpio_up;
	int    				gpio_down;
	int    				volume_up_irq;      /*volumn up key irq.*/
	int    				volume_down_irq;    /*volumn down key irq.*/
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_HI6XXX
	struct delayed_work	gpio_keyback_work;
	struct timer_list		key_back_timer;
	int					gpio_back;
	int					key_back_irq;
#endif
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_SMART_KEY
	struct delayed_work	gpio_keysmart_work;
	struct timer_list		key_smart_timer;
	int					gpio_smart;
	int					key_smart_irq;
#endif
	struct pinctrl *pctrl;
	struct pinctrl_state *pins_default;
	struct pinctrl_state *pins_idle;
};

static struct wake_lock volume_up_key_lock;
static struct wake_lock volume_down_key_lock;
static struct wake_lock back_key_lock;
static struct wake_lock smart_key_lock;

#if defined (CONFIG_HUAWEI_DSM)
static void dsm_gpio_key_timer_func(unsigned long data)
{
	int key_press_error_found = -1;

	if (!dsm_client_ocuppy(key_dclient)) {
		key_press_error_found++;
	}

	/* judge the press count */
	if ((!key_press_error_found) && (volume_up_press_count > MAX_PRESS_KEY_COUNT)) {
		key_press_error_found++;
		dsm_client_record(key_dclient, "volume up key trigger on the abnormal style.\n");
	} else if ((!key_press_error_found) && (volume_down_press_count > MAX_PRESS_KEY_COUNT)) {
		key_press_error_found++;
		dsm_client_record(key_dclient, "volume down key trigger on the abnormal style.\n");
	}

	if (key_press_error_found > 0) {
		dsm_client_notify(key_dclient, DSM_KEY_ERROR_NO);
	} else if (!key_press_error_found) {
		dsm_client_unocuppy(key_dclient);
	} else {
		/* key_dclient preempt failed, we have nothing to do */
	}

	/* reset the statistic variable */
	volume_up_press_count = 0;
	volume_down_press_count = 0;
	mod_timer(&dsm_gpio_key_timer, jiffies + STATISTIC_INTERVAL * HZ);

	return;
}
#endif


static int of_get_key_gpio(struct device_node *np, const char *propname,
			   int prop_index, int gpio_index, enum of_gpio_flags *flags)
{
	int ret = 0;

#ifdef CONFIG_GPIO_LOGIC
	ret = of_get_gpio_by_prop(np, propname, prop_index, gpio_index, flags);
#else
	ret = of_get_named_gpio(np, propname, prop_index);
#endif

	return ret;
}

static int hisi_gpio_key_open(struct input_dev *dev)
{
	return 0;
}

static void hisi_gpio_key_close(struct input_dev *dev)
{
	return;
}

static void hisi_gpio_keyup_work(struct work_struct *work)
{
	struct hisi_gpio_key *gpio_key = container_of(work,
		struct hisi_gpio_key, gpio_keyup_work.work);

	unsigned int keyup_value = 0;
	unsigned int report_action = GPIO_KEY_RELEASE;

	keyup_value = gpio_get_value((unsigned int)gpio_key->gpio_up);
	/*judge key is pressed or released.*/
	if (keyup_value == GPIO_LOW_VOLTAGE) {
		report_action = GPIO_KEY_PRESS;
#if defined (CONFIG_HUAWEI_DSM)
		volume_up_press_count++;
#endif
	} else if (keyup_value == GPIO_HIGH_VOLTAGE) {
		report_action = GPIO_KEY_RELEASE;
	} else {
		printk(KERN_ERR "[gpiokey][%s]invalid gpio key_value.\n", __FUNCTION__);
		return;
	}

#ifdef CONFIG_VOLUME_KEY_MASK
    /* make sure report in pair */
	if((key_mask_ctl == VOLUME_KEY_DISABLE_MASK) && (report_action == GPIO_KEY_PRESS)) {
		key_mask_flag = VOLUME_KEY_DISABLE_MASK;
	}else if(key_mask_ctl == VOLUME_KEY_ENABLE_MASK) {
		key_mask_flag = VOLUME_KEY_ENABLE_MASK;
	}

	if(key_mask_flag == VOLUME_KEY_ENABLE_MASK) {
#endif
		printk(KERN_INFO "[gpiokey] volumn key %u action %u\n", KEY_VOLUMEUP, report_action);
		input_report_key(gpio_key->input_dev, KEY_VOLUMEUP, report_action);
		input_sync(gpio_key->input_dev);
#ifdef CONFIG_VOLUME_KEY_MASK
	} else {
		printk(KERN_INFO "[gpiokey]volumn key is disabled %u\n", report_action);
	}
#endif

	if (keyup_value == GPIO_HIGH_VOLTAGE)
		wake_unlock(&volume_up_key_lock);

	return;
}

static void hisi_gpio_keydown_work(struct work_struct *work)
{
	struct hisi_gpio_key *gpio_key = container_of(work,
		struct hisi_gpio_key, gpio_keydown_work.work);

	unsigned int keydown_value = 0;
	unsigned int report_action = GPIO_KEY_RELEASE;

	keydown_value = gpio_get_value((unsigned int)gpio_key->gpio_down);
	/*judge key is pressed or released.*/
	if (keydown_value == GPIO_LOW_VOLTAGE) {
		report_action = GPIO_KEY_PRESS;
#if defined (CONFIG_HUAWEI_DSM)
		volume_down_press_count++;
#endif
	} else if (keydown_value == GPIO_HIGH_VOLTAGE) {
		report_action = GPIO_KEY_RELEASE;
	} else {
		printk(KERN_ERR "[gpiokey][%s]invalid gpio key_value.\n", __FUNCTION__);
		return;
	}

#ifdef CONFIG_VOLUME_KEY_MASK
    /* make sure report in pair */
	if((key_mask_ctl == VOLUME_KEY_DISABLE_MASK) && (report_action == GPIO_KEY_PRESS)) {
		key_mask_flag = VOLUME_KEY_DISABLE_MASK;
	}else if(key_mask_ctl == VOLUME_KEY_ENABLE_MASK) {
		key_mask_flag = VOLUME_KEY_ENABLE_MASK;
	}

	if(key_mask_flag == VOLUME_KEY_ENABLE_MASK) {
#endif
		printk(KERN_INFO "[gpiokey]volumn key %u action %u\n", KEY_VOLUMEDOWN, report_action);
		input_report_key(gpio_key->input_dev, KEY_VOLUMEDOWN, report_action);
		input_sync(gpio_key->input_dev);
#ifdef CONFIG_VOLUME_KEY_MASK
	} else {
		printk(KERN_INFO "[gpiokey]volumn key is disabled %u\n", report_action);
	}
#endif

	if (keydown_value == GPIO_HIGH_VOLTAGE)
		wake_unlock(&volume_down_key_lock);

	return;
}

#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_HI6XXX
static void hisi_gpio_keyback_work(struct work_struct *work)
{
	struct hisi_gpio_key *gpio_key = container_of(work,
		struct hisi_gpio_key, gpio_keyback_work.work);

	unsigned int keyback_value = 0;
	unsigned int report_action = GPIO_KEY_RELEASE;

	keyback_value = gpio_get_value((unsigned int)gpio_key->gpio_back);
	/*judge key is pressed or released.*/
	if (keyback_value == GPIO_LOW_VOLTAGE)
		report_action = GPIO_KEY_PRESS;
	else if (keyback_value == GPIO_HIGH_VOLTAGE)
		report_action = GPIO_KEY_RELEASE;
	else {
		printk(KERN_ERR "[gpiokey][%s]invalid gpio key_value.\n", __FUNCTION__);
		return;
	}

	printk(KERN_INFO "[gpiokey]back key %u action %u\n", KEY_BACK, report_action);
	input_report_key(gpio_key->input_dev, KEY_BACK, report_action);
	input_sync(gpio_key->input_dev);

	if (keyback_value == GPIO_HIGH_VOLTAGE)
		wake_unlock(&back_key_lock);

	return;
}
#endif

#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_SMART_KEY
static void hisi_gpio_keysmart_work(struct work_struct *work)
{
	struct hisi_gpio_key *gpio_key = container_of(work,
		struct hisi_gpio_key, gpio_keysmart_work.work);

	unsigned int keysmart_value = 0;
	unsigned int report_action = GPIO_KEY_RELEASE;

	keysmart_value = gpio_get_value((unsigned int)gpio_key->gpio_smart);
	/*judge key is pressed or released.*/
	if (keysmart_value == GPIO_LOW_VOLTAGE)
		report_action = GPIO_KEY_PRESS;
	else if (keysmart_value == GPIO_HIGH_VOLTAGE)
		report_action = GPIO_KEY_RELEASE;
	else {
		printk(KERN_ERR "[gpiokey][%s]invalid gpio key_value.\n", __FUNCTION__);
		return;
	}

	printk(KERN_INFO "[gpiokey]smart key %u action %u\n", KEY_F24, report_action);
	input_report_key(gpio_key->input_dev, KEY_F24, report_action);
	input_sync(gpio_key->input_dev);

	if (keysmart_value == GPIO_HIGH_VOLTAGE)
		wake_unlock(&smart_key_lock);

	return;
}
#endif

static void gpio_keyup_timer(unsigned long data)
{
	int keyup_value;
	struct hisi_gpio_key *gpio_key = (struct hisi_gpio_key *)data;

	keyup_value = gpio_get_value((unsigned int)gpio_key->gpio_up);
        /*judge key is pressed or released.*/
        if (keyup_value == GPIO_LOW_VOLTAGE){
                wake_lock(&volume_up_key_lock);

#if defined (CONFIG_HUAWEI_DSM)
		if ((jiffies - volume_up_last_press_time) < msecs_to_jiffies(PRESS_KEY_INTERVAL)) {
			if (!dsm_client_ocuppy(key_dclient)) {
				dsm_client_record(key_dclient, "volume up key trigger on the abnormal style.\n");
				dsm_client_notify(key_dclient, DSM_KEY_ERROR_NO);
			}
		}
		volume_up_last_press_time = jiffies;
#endif
	}

        schedule_delayed_work(&(gpio_key->gpio_keyup_work), 0);
	return;
}

static void gpio_keydown_timer(unsigned long data)
{
        int keydown_value;
        struct hisi_gpio_key *gpio_key = (struct hisi_gpio_key *)data;

        keydown_value = gpio_get_value((unsigned int)gpio_key->gpio_down);
        /*judge key is pressed or released.*/
        if (keydown_value == GPIO_LOW_VOLTAGE){
                wake_lock(&volume_down_key_lock);

#if defined (CONFIG_HUAWEI_DSM)
            if ((jiffies - volume_down_last_press_time) < msecs_to_jiffies(PRESS_KEY_INTERVAL)) {
                if (!dsm_client_ocuppy(key_dclient)) {
                    dsm_client_record(key_dclient, "volume down key trigger on the abnormal style.\n");
                    dsm_client_notify(key_dclient, DSM_KEY_ERROR_NO);
                }
            }
            volume_down_last_press_time = jiffies;
 #endif
	}

	schedule_delayed_work(&(gpio_key->gpio_keydown_work), 0);

	return;
}

#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_HI6XXX
static void gpio_keyback_timer(unsigned long data)
{
	int keyback_value;
	struct hisi_gpio_key *gpio_key = (struct hisi_gpio_key *)data;

	keyback_value = gpio_get_value((unsigned int)gpio_key->gpio_back);
        /*judge key is pressed or released.*/
        if (keyback_value == GPIO_LOW_VOLTAGE)
                wake_lock(&back_key_lock);

	schedule_delayed_work(&(gpio_key->gpio_keyback_work), 0);

	return;
}
#endif

#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_SMART_KEY
static void gpio_keysmart_timer(unsigned long data)
{
	int keysmart_value;
	struct hisi_gpio_key *gpio_key = (struct hisi_gpio_key *)data;

	keysmart_value = gpio_get_value((unsigned int)gpio_key->gpio_smart);
        /*judge key is pressed or released.*/
        if (keysmart_value == GPIO_LOW_VOLTAGE)
                wake_lock(&smart_key_lock);

	schedule_delayed_work(&(gpio_key->gpio_keysmart_work), 0);

	return;
}
#endif

/*以下接口变量只用于组合键进入fastboot模式，完成dump功能*/
static char s_vol_down_hold = 0;
static int vol_up_gpio = -1;
static int vol_up_active_low = -1;
static int vol_down_gpio = -1;
static int vol_down_active_low = -1;

static void gpio_key_vol_updown_press_set_bit(int bit_number)
{
	s_vol_down_hold |= (1 << bit_number);
}

void gpio_key_vol_updown_press_set_zero(void)
{
	s_vol_down_hold = 0;
}

int gpio_key_vol_updown_press_get(void)
{
	return s_vol_down_hold;
}

int is_gpio_key_vol_updown_pressed(void)
{
	int state1 = 0;
	int state2 = 0;

	if((vol_up_gpio < 0) || (vol_down_gpio < 0)
		|| (vol_up_active_low < 0) || (vol_down_active_low < 0)){
		printk(KERN_ERR "[%s]:vol_updown gpio or active_low is invalid!",__FUNCTION__);
		return 0;
	}

	mdelay(5);
	state1 = (gpio_get_value_cansleep(vol_up_gpio) ? 1 : 0) ^ vol_up_active_low;
	state2 = (gpio_get_value_cansleep(vol_down_gpio) ? 1 : 0) ^ vol_down_active_low;

	if(!!state1 && !!state2){
		return 1;
	}

	return 0;
}



static irqreturn_t hisi_gpio_key_irq_handler(int irq, void *dev_id)
{
	struct hisi_gpio_key *gpio_key = (struct hisi_gpio_key *)dev_id;
	int key_event = 0;

	/* handle gpio key volume up & gpio key volume down event at here */
	if (irq == gpio_key->volume_up_irq) {
		key_event = gpio_get_value_cansleep((unsigned int)gpio_key->gpio_up);
		if (0 == key_event) {
			gpio_key_vol_updown_press_set_bit(VOL_UP_BIT);
		} else {
			gpio_key_vol_updown_press_set_zero();
		}
		mod_timer(&(gpio_key->key_up_timer), jiffies + msecs_to_jiffies(TIMER_DEBOUNCE));
		wake_lock_timeout(&volume_up_key_lock, 50);
	} else if (irq == gpio_key->volume_down_irq) {
		key_event = gpio_get_value_cansleep((unsigned int)gpio_key->gpio_down);
		if (0 == key_event) {
			gpio_key_vol_updown_press_set_bit(VOL_DOWN_BIT);
		} else {
			gpio_key_vol_updown_press_set_zero();
		}
		wake_lock_timeout(&volume_down_key_lock, 50);
		mod_timer(&(gpio_key->key_down_timer), jiffies + msecs_to_jiffies(TIMER_DEBOUNCE));
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_HI6XXX
	} else if (irq == gpio_key->key_back_irq) {
		mod_timer(&(gpio_key->key_back_timer), jiffies + msecs_to_jiffies(TIMER_DEBOUNCE));
		wake_lock_timeout(&back_key_lock, 50);
#endif
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_SMART_KEY
	} else if (irq == gpio_key->key_smart_irq) {
		mod_timer(&(gpio_key->key_smart_timer), jiffies + msecs_to_jiffies(TIMER_DEBOUNCE));
		wake_lock_timeout(&smart_key_lock, 50);
#endif
	} else {
		printk(KERN_ERR "[gpiokey] [%s]invalid irq %d!\n", __FUNCTION__, irq);
	}
	return IRQ_HANDLED;
}

#ifdef CONFIG_OF
static const struct of_device_id hs_gpio_key_match[] = {
	{ .compatible = "hisilicon,gpio-key" },
	{},
};
MODULE_DEVICE_TABLE(of, hs_gpio_key_match);
#endif

#ifdef CONFIG_VOLUME_KEY_MASK
static ssize_t key_mask_read(struct file *file, char __user *user_buf,
			size_t count, loff_t *ppos)
{
	char buf[8] = {0};

	snprintf(buf, 8, "%d", key_mask_flag);
	printk(KERN_INFO "[%s]key_mask read:%d\n", __FUNCTION__, key_mask_flag);

	return simple_read_from_buffer(user_buf, count, ppos, buf, strlen(buf));
}

static ssize_t key_mask_write(struct file *file, const char __user *user_buf, size_t count, loff_t *ppos)
{
	char buf[8] = {0};
	int size;
	int mask = 0;

	size = (count < 8) ? count : 8;
	if (copy_from_user(buf, user_buf, size))
		return 0;

	sscanf(buf, "%d", &mask);/* [false alarm]:fortify */
	if((mask == VOLUME_KEY_ENABLE_MASK) || (mask == VOLUME_KEY_DISABLE_MASK)) {
		key_mask_ctl = mask;
	}
	printk(KERN_INFO "[%s]key_mask write:%d\n", __FUNCTION__, mask);

	return count;
}

static const struct file_operations key_mask_fops = {
	.read = key_mask_read,
	.write = key_mask_write,
};
#endif

static int hisi_gpio_key_probe(struct platform_device* pdev)
{
	struct hisi_gpio_key *gpio_key = NULL;
	struct input_dev *input_dev = NULL;
	enum of_gpio_flags flags;
	int err =0;

	if (NULL == pdev) {
		printk(KERN_ERR "[gpiokey]parameter error!\n");
		return -EINVAL;
	}

	dev_info(&pdev->dev, "hisi gpio key driver probes start!\n");
#ifdef CONFIG_OF
	if (!of_match_node(hs_gpio_key_match, pdev->dev.of_node)) {
		dev_err(&pdev->dev, "dev node is not match. exiting.\n");
		return -ENODEV;
	}
#endif

	gpio_key = devm_kzalloc(&pdev->dev, sizeof(struct hisi_gpio_key), GFP_KERNEL);
	if (!gpio_key) {
		dev_err(&pdev->dev, "Failed to allocate struct hisi_gpio_key!\n");
		return -ENOMEM;
	}

	input_dev = input_allocate_device();
	if (!input_dev) {
		dev_err(&pdev->dev, "Failed to allocate struct input_dev!\n");
		return -ENOMEM;
	}

	input_dev->name = pdev->name;
	input_dev->id.bustype = BUS_HOST;
	input_dev->dev.parent = &pdev->dev;
	input_set_drvdata(input_dev, gpio_key);
	set_bit(EV_KEY, input_dev->evbit);
	set_bit(EV_SYN, input_dev->evbit);
	set_bit(KEY_VOLUMEUP, input_dev->keybit);
	set_bit(KEY_VOLUMEDOWN, input_dev->keybit);
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_HI6XXX
	set_bit(KEY_BACK, input_dev->keybit);
#endif
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_SMART_KEY
	set_bit(KEY_F24, input_dev->keybit);
#endif
	input_dev->open = hisi_gpio_key_open;
	input_dev->close = hisi_gpio_key_close;

	gpio_key->input_dev = input_dev;

	/*initial work before we use it.*/
	INIT_DELAYED_WORK(&(gpio_key->gpio_keyup_work), hisi_gpio_keyup_work);
	INIT_DELAYED_WORK(&(gpio_key->gpio_keydown_work), hisi_gpio_keydown_work);
	wake_lock_init(&volume_down_key_lock, WAKE_LOCK_SUSPEND, "key_down_wake_lock");
	wake_lock_init(&volume_up_key_lock, WAKE_LOCK_SUSPEND, "key_up_wake_lock");
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_HI6XXX
	INIT_DELAYED_WORK(&(gpio_key->gpio_keyback_work), hisi_gpio_keyback_work);
	wake_lock_init(&back_key_lock, WAKE_LOCK_SUSPEND, "key_back_wake_lock");
#endif
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_SMART_KEY
	INIT_DELAYED_WORK(&(gpio_key->gpio_keysmart_work), hisi_gpio_keysmart_work);
	wake_lock_init(&smart_key_lock, WAKE_LOCK_SUSPEND, "key_smart_wake_lock");
#endif

	gpio_key->gpio_up = of_get_key_gpio(pdev->dev.of_node, "gpio-keyup,gpio-irq", 0, 0, &flags);
	if (!gpio_is_valid(gpio_key->gpio_up)) {
		printk(KERN_INFO "%s: gpio of volume up is not valid, check DTS\n", __FUNCTION__);
	}

	gpio_key->gpio_down = of_get_key_gpio(pdev->dev.of_node, "gpio-keydown,gpio-irq", 0, 0, &flags);
	if (!gpio_is_valid(gpio_key->gpio_down)) {
		printk(KERN_INFO "%s: gpio of volume down is not valid, check DTS\n", __FUNCTION__);
	}

#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_HI6XXX
	gpio_key->gpio_back = of_get_key_gpio(pdev->dev.of_node, "gpio-keyback,gpio-irq", 0, 0, &flags);
	if (!gpio_is_valid(gpio_key->gpio_back)) {
		printk(KERN_INFO "%s: gpio of back key is not valid, check DTS\n", __FUNCTION__);
	}
#endif
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_SMART_KEY
	gpio_key->gpio_smart = of_get_key_gpio(pdev->dev.of_node, "gpio-keysmart,gpio-irq", 0, 0, &flags);
	if (!gpio_is_valid(gpio_key->gpio_smart)) {
		printk(KERN_INFO "%s: gpio of smart key is not valid, check DTS\n", __FUNCTION__);
	}
#endif

	vol_up_gpio = gpio_key->gpio_up;
	vol_up_active_low = GPIO_KEY_PRESS;
	vol_down_gpio = gpio_key->gpio_down;
	vol_down_active_low = GPIO_KEY_PRESS;

	if (gpio_is_valid(gpio_key->gpio_up)) {
		err = gpio_request((unsigned int)gpio_key->gpio_up, "gpio_up");
		if (err < 0) {
			dev_err(&pdev->dev, "Fail request gpio:%d\n", gpio_key->gpio_up);
			goto err_get_gpio;
		}

		gpio_direction_input((unsigned int)gpio_key->gpio_up);

		gpio_key->volume_up_irq = gpio_to_irq((unsigned int)gpio_key->gpio_up);
		if (gpio_key->volume_up_irq < 0) {
			dev_err(&pdev->dev, "Failed to get gpio key press irq!\n");
			err = gpio_key->volume_up_irq;
			goto err_gpio_to_irq;
		}
	}
	if (gpio_is_valid(gpio_key->gpio_down)) {
		err = gpio_request((unsigned int)gpio_key->gpio_down, "gpio_down");
		if (err) {
			dev_err(&pdev->dev, "Fail request gpio:%d\n", gpio_key->gpio_down);
			goto err_gpio_down_req;
		}

		gpio_direction_input((unsigned int)gpio_key->gpio_down);

		gpio_key->volume_down_irq = gpio_to_irq((unsigned int)gpio_key->gpio_down);
		if (gpio_key->volume_down_irq < 0) {
			dev_err(&pdev->dev, "Failed to get gpio key release irq!\n");
			err = gpio_key->volume_down_irq;
			goto err_gpio_to_irq;
		}
	}
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_HI6XXX
	if (gpio_is_valid(gpio_key->gpio_back)) {
		err = gpio_request((unsigned int)gpio_key->gpio_back, "gpio_back");
		if (err) {
			dev_err(&pdev->dev, "Fail request gpio:%d\n", gpio_key->gpio_back);
			goto err_gpio_back_req;
		}

		gpio_direction_input((unsigned int)gpio_key->gpio_back);

		gpio_key->key_back_irq = gpio_to_irq((unsigned int)gpio_key->gpio_back);
		if (gpio_key->key_back_irq < 0) {
			dev_err(&pdev->dev, "Failed to get gpio key release irq!\n");
			err = gpio_key->key_back_irq;
			goto err_gpio_to_irq;
		}
	}
#endif
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_SMART_KEY
	if (gpio_is_valid(gpio_key->gpio_smart)) {
		err = gpio_request((unsigned int)gpio_key->gpio_smart, "gpio_smart");
		if (err) {
			dev_err(&pdev->dev, "Fail request gpio:%d\n", gpio_key->gpio_smart);
			goto err_gpio_smart_req;
		}

		gpio_direction_input((unsigned int)gpio_key->gpio_smart);

		gpio_key->key_smart_irq = gpio_to_irq((unsigned int)gpio_key->gpio_smart);
		if (gpio_key->key_smart_irq < 0) {
			dev_err(&pdev->dev, "Failed to get gpio key release irq!\n");
			err = gpio_key->key_smart_irq;
			goto err_gpio_to_irq;
		}
	}
#endif

	gpio_key->pctrl = devm_pinctrl_get(&pdev->dev);
	if (IS_ERR(gpio_key->pctrl)) {
		dev_err(&pdev->dev, "failed to devm pinctrl get\n");
		err = -EINVAL;
		goto err_pinctrl;
	}
	gpio_key->pins_default = pinctrl_lookup_state(gpio_key->pctrl, PINCTRL_STATE_DEFAULT);
	if (IS_ERR(gpio_key->pins_default)) {
		dev_err(&pdev->dev, "failed to pinctrl lookup state default\n");
		err = -EINVAL;
		goto err_pinctrl_put;
	}
	gpio_key->pins_idle = pinctrl_lookup_state(gpio_key->pctrl, PINCTRL_STATE_IDLE);
	if (IS_ERR(gpio_key->pins_idle)) {
		dev_err(&pdev->dev, "failed to pinctrl lookup state idle\n");
		err = -EINVAL;
		goto err_pinctrl_put;
	}
	err = pinctrl_select_state(gpio_key->pctrl, gpio_key->pins_default);
	if (err < 0) {
		dev_err(&pdev->dev, "set iomux normal error, %d\n", err);
		goto err_pinctrl_put;
	}

#if defined (CONFIG_HUAWEI_DSM)
	/* initialize the statistic variable */
	volume_up_press_count = 0;
	volume_down_press_count = 0;
	volume_up_last_press_time = 0;
	volume_down_last_press_time = 0;
#endif

	setup_timer(&(gpio_key->key_up_timer), gpio_keyup_timer, (unsigned long )gpio_key);
	setup_timer(&(gpio_key->key_down_timer), gpio_keydown_timer, (unsigned long )gpio_key);
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_HI6XXX
	setup_timer(&(gpio_key->key_back_timer), gpio_keyback_timer, (unsigned long )gpio_key);
#endif
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_SMART_KEY
	setup_timer(&(gpio_key->key_smart_timer), gpio_keysmart_timer, (unsigned long )gpio_key);
#endif

#if defined (CONFIG_HUAWEI_DSM)
	setup_timer(&dsm_gpio_key_timer, dsm_gpio_key_timer_func, (unsigned long)gpio_key);
#endif
	/*
	 * support failing irq that means volume-up-key is pressed,
	 * and rising irq which means volume-up-key is released.
	 */
	 if (gpio_is_valid(gpio_key->gpio_up)) {
		err = request_irq(gpio_key->volume_up_irq, hisi_gpio_key_irq_handler, IRQF_NO_SUSPEND | IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, pdev->name, gpio_key);
		if (err) {
			dev_err(&pdev->dev, "Failed to request press interupt handler!\n");
			goto err_up_irq_req;
		}
	 }

	/*
	 * support failing irq that means volume-down-key is pressed,
	 * and rising irq which means volume-down-key is released.
	 */
	 if (gpio_is_valid(gpio_key->gpio_down)) {
		err = request_irq(gpio_key->volume_down_irq, hisi_gpio_key_irq_handler, IRQF_NO_SUSPEND | IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, pdev->name, gpio_key);
		if (err) {
			dev_err(&pdev->dev, "Failed to request release interupt handler!\n");
			goto err_down_irq_req;
		}
	 }

#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_HI6XXX
	if (gpio_is_valid(gpio_key->gpio_back)) {
		err = request_irq(gpio_key->key_back_irq, hisi_gpio_key_irq_handler, IRQF_NO_SUSPEND | IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, pdev->name, gpio_key);
		if (err) {
			dev_err(&pdev->dev, "Failed to request release interupt handler!\n");
			goto err_back_irq_req;
		}
	}
#endif
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_SMART_KEY
	if (gpio_is_valid(gpio_key->gpio_smart)) {
		err = request_irq(gpio_key->key_smart_irq, hisi_gpio_key_irq_handler, IRQF_NO_SUSPEND | IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, pdev->name, gpio_key);
		if (err) {
			dev_err(&pdev->dev, "Failed to request release interupt handler!\n");
			goto err_smart_irq_req;
		}
	}
#endif

	err = input_register_device(gpio_key->input_dev);
	if (err) {
		dev_err(&pdev->dev, "Failed to register input device!\n");
		goto err_register_dev;
	}

	device_init_wakeup(&pdev->dev, TRUE);
	platform_set_drvdata(pdev, gpio_key);

#if defined (CONFIG_HUAWEI_DSM)
	if (!key_dclient) {
		key_dclient = dsm_register_client(&dsm_key);
	}

	mod_timer(&dsm_gpio_key_timer, jiffies + STATISTIC_INTERVAL * HZ);
#endif

#ifdef CONFIG_VOLUME_KEY_MASK
	if (!proc_create("key_mask", 0660, NULL, &key_mask_fops)) {
		printk(KERN_ERR "[%s]:failed to create key_mask proc\n",__FUNCTION__);
	}
#endif

	dev_info(&pdev->dev, "hisi gpio key driver probes successfully!\n");
	return 0;

err_register_dev:
#ifdef  CONFIG_HISI_GPIO_KEY_SUPPORT_HI6XXX
	free_irq(gpio_key->key_back_irq, gpio_key);
err_back_irq_req:
#endif
#ifdef  CONFIG_HISI_GPIO_KEY_SUPPORT_SMART_KEY
	free_irq(gpio_key->key_smart_irq, gpio_key);
err_smart_irq_req:
#endif
	free_irq(gpio_key->volume_down_irq, gpio_key);
err_down_irq_req:
	free_irq(gpio_key->volume_up_irq, gpio_key);
err_up_irq_req:
err_pinctrl_put:
	devm_pinctrl_put(gpio_key->pctrl);
err_pinctrl:
err_gpio_to_irq:
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_HI6XXX
	gpio_free((unsigned int)gpio_key->gpio_back);
err_gpio_back_req:
#endif
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_SMART_KEY
	gpio_free((unsigned int)gpio_key->gpio_smart);
err_gpio_smart_req:
#endif
	gpio_free((unsigned int)gpio_key->gpio_down);
err_gpio_down_req:
	gpio_free((unsigned int)gpio_key->gpio_up);
err_get_gpio:
	input_free_device(input_dev);
	wake_lock_destroy(&volume_down_key_lock);
	wake_lock_destroy(&volume_up_key_lock);
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_HI6XXX
	wake_lock_destroy(&back_key_lock);
#endif
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_SMART_KEY
	wake_lock_destroy(&smart_key_lock);
#endif
	pr_info(KERN_ERR "[gpiokey]K3v3 gpio key probe failed! ret = %d.\n", err);
	return err;
}

static int hisi_gpio_key_remove(struct platform_device* pdev)
{
	struct hisi_gpio_key *gpio_key = platform_get_drvdata(pdev);

	if (gpio_key == NULL) {
		printk(KERN_ERR "get invalid gpio_key pointer\n");
		return -EINVAL;
	}

	free_irq(gpio_key->volume_up_irq, gpio_key);
	free_irq(gpio_key->volume_down_irq, gpio_key);
	gpio_free((unsigned int)gpio_key->gpio_up);
	gpio_free((unsigned int)gpio_key->gpio_down);
	devm_pinctrl_put(gpio_key->pctrl);
	cancel_delayed_work(&(gpio_key->gpio_keyup_work));
	cancel_delayed_work(&(gpio_key->gpio_keydown_work));
	wake_lock_destroy(&volume_down_key_lock);
	wake_lock_destroy(&volume_up_key_lock);
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_HI6XXX
	free_irq(gpio_key->key_back_irq, gpio_key);
	gpio_free((unsigned int)gpio_key->gpio_back);
	cancel_delayed_work(&(gpio_key->gpio_keyback_work));
	wake_lock_destroy(&back_key_lock);
#endif
#ifdef CONFIG_HISI_GPIO_KEY_SUPPORT_SMART_KEY
	free_irq(gpio_key->key_smart_irq, gpio_key);
	gpio_free((unsigned int)gpio_key->gpio_smart);
	cancel_delayed_work(&(gpio_key->gpio_keysmart_work));
	wake_lock_destroy(&smart_key_lock);
#endif

	input_unregister_device(gpio_key->input_dev);
	platform_set_drvdata(pdev, NULL);
#ifdef CONFIG_VOLUME_KEY_MASK
	remove_proc_entry("key_mask", 0);
#endif
	kfree(gpio_key);
	gpio_key = NULL;
	return 0;
}

#ifdef CONFIG_PM
static int hisi_gpio_key_suspend(struct platform_device *pdev, pm_message_t state)
{
	int err;
	struct hisi_gpio_key *gpio_key = platform_get_drvdata(pdev);

	dev_info(&pdev->dev, "%s: suspend +\n", __func__);

	err = pinctrl_select_state(gpio_key->pctrl, gpio_key->pins_idle);
	if (err < 0) {
		dev_err(&pdev->dev, "set iomux normal error, %d\n", err);
	}

	dev_info(&pdev->dev, "%s: suspend -\n", __func__);
	return 0;
}

static int hisi_gpio_key_resume(struct platform_device *pdev)
{
	int err;
	struct hisi_gpio_key *gpio_key = platform_get_drvdata(pdev);

	dev_info(&pdev->dev, "%s: resume +\n", __func__);

	err = pinctrl_select_state(gpio_key->pctrl, gpio_key->pins_default);
	if (err < 0) {
		dev_err(&pdev->dev, "set iomux idle error, %d\n", err);
	}

	dev_info(&pdev->dev, "%s: resume -\n", __func__);
	return 0;
}
#endif

struct platform_driver hisi_gpio_key_driver = {
	.probe = hisi_gpio_key_probe,
	.remove = hisi_gpio_key_remove,
	.driver = {
		.name = "hisi_gpio_key",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hs_gpio_key_match),
	},
#ifdef CONFIG_PM
	.suspend = hisi_gpio_key_suspend,
	.resume = hisi_gpio_key_resume,
#endif
};

module_platform_driver(hisi_gpio_key_driver);

MODULE_AUTHOR("Hisilicon K3 Driver Group");
MODULE_DESCRIPTION("Hisilicon keypad platform driver");
MODULE_LICENSE("GPL");
