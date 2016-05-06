#include <mach/irqs.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <mach/gpio.h>
#include <linux/gpio_keys.h>
#include <linux/input.h>

static struct gpio_keys_button sft_gpio_keys_buttons[] = {
	{
		.code		= KEY_VOLUMEUP,
		.gpio		= GPIO_1_4,
		.active_low	= 1,
		.desc		= "Volume UP",
		.type		= EV_KEY,
		.wakeup		= 1,
		.no_suspend = 1,
	},
	{
		.code		= KEY_VOLUMEDOWN,
		.gpio		= GPIO_1_5,
		.active_low	= 1,
		.desc		= "Volume Down",
		.type		= EV_KEY,
		.wakeup		= 1,
		.no_suspend = 1,
	},
	{
		.code		= KEY_BACK,
		.gpio		= GPIO_1_6,
		.active_low	= 1,
		.desc		= "Back",
		.type		= EV_KEY,
		.wakeup		= 1,
		.no_suspend = 1,
	},

};

static struct gpio_keys_platform_data sft_gpio_keys = {
	.buttons = sft_gpio_keys_buttons,
	.nbuttons = ARRAY_SIZE(sft_gpio_keys_buttons),
};

static struct platform_device sft_gpio_keys_device = {
	.name = "gpio-keys",
	.id	 = -1,
	.dev = {
		.platform_data = &sft_gpio_keys,
	}
};

static int __init keyboard_dev_init(void)
{
    return platform_device_register(&sft_gpio_keys_device);;
}

arch_initcall(keyboard_dev_init);

