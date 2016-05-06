#include <mach/irqs.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/gpio_keys.h>
#include <mach/gpio.h>
#include <linux/mux.h>

#define BLOCK_KEY "block_key"

static int __init keyboard_iomux_init(void)
{
	struct iomux_block  *iomux_block;
	struct block_config *block_config;
	int ret;

	/* Set iomux NORMAL, If set iomux failed, we still go on */
	iomux_block = iomux_get_block(BLOCK_KEY);
	if (!iomux_block){
		printk(KERN_ERR "Get i2c iomux_block %s failed\n", BLOCK_KEY);
	    return -1;
    }

	block_config = iomux_get_blockconfig(BLOCK_KEY);
	if (!block_config){
		printk(KERN_ERR "Get i2c block_config %s failed\n", BLOCK_KEY);
	    return -1;
    }

	ret = blockmux_set(iomux_block, block_config, NORMAL);
	if (ret){
		printk(KERN_ERR "Set %s iomux to NORMAL failed, ret = %d\n", BLOCK_KEY, ret);
	    return -1;
    }

    return 0;
}

postcore_initcall(keyboard_iomux_init);

