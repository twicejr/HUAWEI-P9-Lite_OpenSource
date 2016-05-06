

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/switch.h>
#include <linux/workqueue.h>
#include <linux/gpio.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

#include <linux/of_gpio.h>
#include <linux/huawei/usb/hisi_usb.h>
#include <huawei_platform/log/hw_log.h>

#define HWLOG_TAG otgid_gpio_switch
HWLOG_REGIST();

#define GPIO_HIGH_VOLTAGE           (1)
#define GPIO_LOW_VOLTAGE            (0)
#define TIMER_DEBOUNCE              (50)

#define DEV_NAME    "switch-gpio"
#define OF_NAME     "huawei,gpio_switch_otg"

struct otg_id_switch_gpio{
    int otg_id_gpio;
    int otg_id_gpio_irq;
    int otg_id_gpio_last_state;
    struct timer_list id_timer;
    struct delayed_work gpio_switch_work;
};

static struct otg_id_switch_gpio otg_id_switch;

static void gpio_switch_work_func(struct work_struct *work)
{
    int state;

    state = gpio_get_value(otg_id_switch.otg_id_gpio);
    hwlog_info("gpio_switch_work state = %d ---\n", state);

    if (otg_id_switch.otg_id_gpio_last_state == GPIO_HIGH_VOLTAGE
            && state == GPIO_LOW_VOLTAGE) {
        hwlog_err("gpio_switch_work ID_FALL_EVENT ---\n");
        hisi_usb_id_change(ID_FALL_EVENT);
        otg_id_switch.otg_id_gpio_last_state = state;
        return;
    }

    if (otg_id_switch.otg_id_gpio_last_state == GPIO_LOW_VOLTAGE
            && state == GPIO_HIGH_VOLTAGE) {
        hwlog_err("gpio_switch_work ID_RISE_EVENT +++\n");
        hisi_usb_id_change(ID_RISE_EVENT);
        otg_id_switch.otg_id_gpio_last_state = state;
        return;
    }
}

static void otg_id_gpio_timer(unsigned long data)
{
    hwlog_info("gpio_irq_handler state = %d\n",
        gpio_get_value(otg_id_switch.otg_id_gpio));
    cancel_delayed_work(&otg_id_switch.gpio_switch_work);
    schedule_delayed_work(&otg_id_switch.gpio_switch_work, msecs_to_jiffies(0));
    return;
}

static irqreturn_t gpio_irq_handler(int irq, void *dev_id)
{
    if (irq == otg_id_switch.otg_id_gpio_irq)
    {
        mod_timer(&otg_id_switch.id_timer, jiffies + msecs_to_jiffies(TIMER_DEBOUNCE));
    }
    return IRQ_HANDLED;
}

static int gpio_switch_probe(struct platform_device *pdev)
{
    int ret = 0;
    struct device_node *np = NULL;

    if (!pdev)
        return -EBUSY;

    otg_id_switch.otg_id_gpio = -1;
    otg_id_switch.otg_id_gpio_irq = -1;
    otg_id_switch.otg_id_gpio_last_state = GPIO_HIGH_VOLTAGE;

    np = of_find_compatible_node(NULL, NULL, OF_NAME);
    if (np) {
        otg_id_switch.otg_id_gpio = of_get_named_gpio(np, "otg_int_gpio", 0);
        if (!gpio_is_valid(otg_id_switch.otg_id_gpio)) {
            hwlog_err("%s:otg_int_gpio is not config, %d\n",__FUNCTION__, otg_id_switch.otg_id_gpio);
            return -ENXIO;
        }
        hwlog_info("%s:huawei,otg_int_gpio %d\n",__FUNCTION__, otg_id_switch.otg_id_gpio);
    } else {
        hwlog_err("%s: can not find node: %s\n",__FUNCTION__, OF_NAME);
        return -ENODEV;
    }

    ret = gpio_request(otg_id_switch.otg_id_gpio, pdev->name);
    if (ret < 0) {
        hwlog_err("err_request_gpio\n");
        return -EBUSY;
    }

    ret = gpio_direction_input(otg_id_switch.otg_id_gpio);
    if (ret < 0) {
        hwlog_err("err_set_gpio_input\n");
        ret = -EBUSY;
        goto err_set_gpio_input;
    }

    INIT_DELAYED_WORK(&otg_id_switch.gpio_switch_work, gpio_switch_work_func);

    otg_id_switch.otg_id_gpio_irq = gpio_to_irq(otg_id_switch.otg_id_gpio);
    if (otg_id_switch.otg_id_gpio_irq < 0) {
        hwlog_err("err_detect_irq_num_failed\n");
        ret = otg_id_switch.otg_id_gpio_irq;
        goto err_detect_irq_num_failed;
    }

    setup_timer(&otg_id_switch.id_timer, otg_id_gpio_timer, (unsigned long )pdev);

    ret = request_irq(otg_id_switch.otg_id_gpio_irq, gpio_irq_handler,
            IRQF_NO_SUSPEND | IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING, pdev->name, pdev);
    if (ret < 0) {
        hwlog_err("err_request_irq  \n");
        goto err_request_irq;
    }

    /* Perform initial detection */
    otg_id_switch.otg_id_gpio_last_state = 1;
    if (!gpio_get_value_cansleep(otg_id_switch.otg_id_gpio))
    {
        hwlog_err("otg id fall @ init\n");
        mod_timer(&otg_id_switch.id_timer, jiffies + msecs_to_jiffies(TIMER_DEBOUNCE*10));
    }

    return 0;

err_request_irq:
err_detect_irq_num_failed:
err_set_gpio_input:
    gpio_free(otg_id_switch.otg_id_gpio);

    return ret;
}

static int gpio_switch_remove(struct platform_device *pdev)
{
    free_irq(otg_id_switch.otg_id_gpio_irq, pdev);
    cancel_work_sync(&(otg_id_switch.gpio_switch_work));
    gpio_free(otg_id_switch.otg_id_gpio);

    return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id gpio_switch_otg_ids[] = {
    { .compatible = OF_NAME },
    {},
};
MODULE_DEVICE_TABLE(of, gpio_switch_otg_ids);
#else
#define gpio_switch_otg_ids NULL
#endif

static struct platform_driver gpio_switch_driver = {
    .probe		= gpio_switch_probe,
    .remove		= gpio_switch_remove,
    .driver		= {
        .name	= DEV_NAME,
        .owner	= THIS_MODULE,
        .of_match_table = of_match_ptr(gpio_switch_otg_ids),
    },
};

static int __init gpio_switch_init(void)
{
    return platform_driver_register(&gpio_switch_driver);
}

static void __exit gpio_switch_exit(void)
{
    platform_driver_unregister(&gpio_switch_driver);
}

module_init(gpio_switch_init);
module_exit(gpio_switch_exit);

MODULE_AUTHOR("(liuqi 81004140)liuqi@huawei.com");
MODULE_DESCRIPTION("OTG ID GPIO Switch driver");
MODULE_LICENSE("GPL v2");

