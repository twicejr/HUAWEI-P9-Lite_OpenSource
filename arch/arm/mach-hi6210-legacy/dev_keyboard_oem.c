#include <mach/irqs.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/gpio_keys.h>
#include <mach/gpio.h>
#include <linux/input.h>
#include <hsad/config_mgr.h>

#define OEM_GPIO_KEYS_MAX_BUTTONS   5

struct oem_buttons_desc {
	char *key;
	unsigned int code;
	char *desc;
};

static struct oem_buttons_desc buttons_desc[]  __initdata = 
{
	{"keyboard/key_volumn_up", KEY_VOLUMEUP, "Volume UP"},
	{"keyboard/key_volumn_down", KEY_VOLUMEDOWN, "Volume DOWN"},
	{"keyboard/key_back", KEY_BACK, "Back"},
};

static struct gpio_keys_button oem_gpio_keys_buttons[OEM_GPIO_KEYS_MAX_BUTTONS];

static struct gpio_keys_platform_data oem_gpio_keys = {
	.buttons = oem_gpio_keys_buttons,
};

static struct platform_device oem_gpio_keys_device = {
	.name = "gpio-keys",
	.id = -1,
	.dev = {
		.platform_data = &oem_gpio_keys,
	}
};

static void __init set_oem_gpio_keys_buttons(struct gpio_keys_button *button, unsigned int code, const char *desc, int gpio)
{
	button->code = code;
	button->gpio= gpio;
	button->active_low= 1;
	button->desc= desc;
	button->type= EV_KEY;
	button->wakeup = 1;
	button->no_suspend = 1;

	return ;
}

static int __init keyboard_dev_init(void)
{
    int i, ret, gpio_num;
    int buttons = 0;

    memset(oem_gpio_keys_buttons, 0, sizeof(oem_gpio_keys_buttons));
   
    for (i = 0; i < ARRAY_SIZE(buttons_desc); i++) {
        ret = get_hw_config_int(buttons_desc[i].key, &gpio_num, NULL);
        if ((true == ret) && (-1 != gpio_num)) {
             /* set the ''struct gpio_keys_button'' */
             set_oem_gpio_keys_buttons(&oem_gpio_keys_buttons[i], buttons_desc[i].code, buttons_desc[i].desc, gpio_num);
             buttons ++;
	 } 
    }

    oem_gpio_keys.nbuttons = buttons; 

    return platform_device_register(&oem_gpio_keys_device);
}

arch_initcall(keyboard_dev_init);
