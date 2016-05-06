/*
 *
 * arch/arm/mach-k3v2/iomux.c
 *
 * Copyright (C) 2011 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 *
 */
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/mux.h>
#include <linux/hardirq.h>
#include <mach/boardid.h>
#include "iomux.h"


static struct iomux_block_table *blocks_table = NULL;
int iomux_register_blocks_table(struct iomux_block_table *table)
{
    blocks_table = table;

    return 0;
}
EXPORT_SYMBOL(iomux_register_blocks_table);

static struct iomux_pin_table *pins_table = NULL;
int iomux_register_pins_table(struct iomux_pin_table *table)
{
    pins_table = table;

    return 0;
}
EXPORT_SYMBOL(iomux_register_pins_table);



static DEFINE_MUTEX(iomux_lock);
static DEFINE_MUTEX(iomux_lock_debugfs);
#define iomux_lock_save(c, flags)			\
	do {						\
		spin_lock_irqsave(&c->spinlock, flags);	\
	} while (0)

#define iomux_unlock_restore(c, flags)				\
	do {							\
		spin_unlock_irqrestore(&c->spinlock, flags);	\
	} while (0)

/*get the pin by name*/
struct iomux_pin *iomux_get_pin(char *name)
{
	int i = 0;
	struct iomux_pin *pin = NULL;
	struct iomux_pin_table *pintable = pins_table;

    if (NULL == pintable){
		pr_err("Get IOMUX pin failed, iomux not init,%s %d.\r\n", __func__, __LINE__);
        return pin;
    }
	while (pintable[i].pinname) {
		if (strncmp(name, pintable[i].pinname, MAX_NAME_CHARS)) {
			i++;
		} else {
			pin = pintable[i].iomux_pin;
			if (pin->init == 0) {
				spin_lock_init(&pin->spinlock);
				pin->init = 1;
			}
			break;
		}
	}

	if (pin == NULL)
		pr_debug("IOMUX:%s pin get failed.\r\n", name);

	return pin;
}
EXPORT_SYMBOL(iomux_get_pin);

 /*set the pin as pull up or down*/
int pinmux_setpullupdown(struct  iomux_pin *pin, enum pull_updown pin_pull_updown)
{
	unsigned long flags = 0;
	int ret = 0;
	char *free_mode = "lowpower";

	iomux_lock_save(pin, flags);

	if (!pin) {
		pr_debug("IOMUX:the pin is null.\r\n");
		ret = -INVALID;
		goto out;
	}

	/*
	 *when the pin is used as low power,can't set the pull
	 *up down, only it's set as gpio and normal
	 */
	if (pin->pin_owner && !strncmp(pin->pin_owner, free_mode, MAX_NAME_CHARS)) {
		pr_debug("IOMUX:the pin %s is set as low power,can't set pull.\r\n", pin->pin_name);
		ret = -INVALID;
		goto out;
	}

	/*
	 *when it's set as low power mode,the pull and strength
	 *drive are set as low power ,can't be changed
	 */
	if (pin && pin->ops && pin->ops->pin_setpullupdown) {
		ret = pin->ops->pin_setpullupdown(pin, pin_pull_updown);
	} else {
		pr_debug("IOMUX:pull up or down setting failed.\r\n");
		ret = -INVALID;
	}
out:
	iomux_unlock_restore(pin, flags);
	return ret;
}
EXPORT_SYMBOL(pinmux_setpullupdown);

/*set the pin'driver strength*/
int pinmux_setdrivestrength(struct  iomux_pin *pin, enum drive_strength pin_drive_strength)
{
	unsigned long flags = 0;
	int ret = 0;
	char *free_mode = "lowpower";

	iomux_lock_save(pin, flags);
	/*
	 *when the pin is used by low power,can't set the drviver strength,
	 *only it's used by gpio and normal
	 */
	if (pin->pin_owner && !strncmp(pin->pin_owner, free_mode, FREEMODE_CHARS)) {
		pr_debug("IOMUX:the pin %s is low power,drive strength setting failed.\r\n", pin->pin_name);
		ret = -INVALID;
		goto out;
	}

	if (pin && pin->ops && pin->ops->pin_setdrivestrength) {
		/*
		 *when it's set as low power mode, the pull and strength
		 *drive are set as low power, can't be changed
		 */
		ret = pin->ops->pin_setdrivestrength(pin, pin_drive_strength);
	} else {
		pr_debug("IOMUX:driver strength setting failed.\r\n");
		ret = -INVALID;
	}
out:
	iomux_unlock_restore(pin, flags);
	return ret;
}
EXPORT_SYMBOL(pinmux_setdrivestrength);

/*judge the pin is used*/
static int iomux_canget_pin(struct  iomux_pin *pin, struct  iomux_block *block)
{
	char *free_mode = "lowpower";
	char *gpio_mode = "gpio";

	if (pin->pin_owner) {
		if (!strncmp(pin->pin_owner, free_mode, FREEMODE_CHARS) || !strncmp(pin->pin_owner, gpio_mode, FREEMODE_CHARS) ||
			!strncmp(pin->pin_owner, block->block_name, MAX_NAME_CHARS)) {
			/*if the pin is free,can get it*/
			return 0;
		} else {
			/*if the pin is used by other block can't get it*/
			pr_debug("IOMUX:%s is used by %s,can't use it \
				here.\r\n", pin->pin_name, pin->pin_owner);
			return -INVALID;
		}
	}

	return 0;
}

/*get the block by name*/
struct iomux_block *iomux_get_block(char *name)
{
	int ret = 0;
	struct  iomux_block *block_temp = NULL;
	struct  iomux_pin **pins_temp = NULL;
	struct  iomux_block_table *table_temp = NULL;

#ifdef CONFIG_DEBUG_MUTEX_ERROR
	WARN(in_interrupt(), 
		KERN_ERR "ERROR: MUTEX used in interrupt context! preempt_count = 0x%x, func: %s, line: %d\n",
		preempt_count(), __func__, __LINE__);
#endif

	mutex_lock(&iomux_lock);

	table_temp = blocks_table;
    if (NULL == table_temp){
		pr_err("Get IOMUX block failed, iomux not init,%s %d.\r\n", __func__, __LINE__);
        goto out;
    }
	while ((*table_temp).name) {
		if (strncmp(name, (*table_temp).name, MAX_NAME_CHARS)) {
			table_temp++;
		} else {
			block_temp = (*table_temp).block;
			break;
		}
	}

	/*
	 *if there's pin has been used by another block, this block
	 *can't use it here,so get block failed,return NULL
	 */
	if (block_temp) {
		/* spin lock need init */
		if (block_temp->init == 0) {
			spin_lock_init(&block_temp->spinlock);
			block_temp->init = 1;
		}

		pins_temp = block_temp->pins;
		while (*pins_temp) {
			/*
			 *when the pin's function is lowpower, it isn't used
			 *by other block if its owner isn't low power, it must
			 *be used as normal by other block or as gpio, the
			 *current block can't use it.
			 */
			ret = iomux_canget_pin(*pins_temp, block_temp);
			if (ret < 0) {
				block_temp = NULL;
				pr_debug("IOMUX:block %s get failed.\r\n", name);
				goto out;
			}
			pins_temp++;
		}
	}
out:
	mutex_unlock(&iomux_lock);
	return block_temp;
}
EXPORT_SYMBOL(iomux_get_block);

struct block_config *iomux_get_blockconfig(char *name)
{
	struct block_config *config_temp = NULL;
	struct iomux_block_table *table_temp = NULL;

	table_temp = blocks_table;
    if (NULL == table_temp){
		pr_err("Get IOMUX blockconfig failed, iomux not init,%s %d.\r\n", __func__, __LINE__);
        return config_temp;
    }
	while ((*table_temp).name) {
		if (strncmp(name, (*table_temp).name, MAX_NAME_CHARS)) {
			table_temp++;
		} else {
			config_temp = (*table_temp).config_array;
			break;
		}
	}

	return config_temp;
}
EXPORT_SYMBOL(iomux_get_blockconfig);

int blockmux_set(struct iomux_block *blockmux,
	struct block_config *config, enum iomux_func newmode)
{
	int ret = 0;
	unsigned long flags;

	if (!blockmux || !config)
		return -INVALID;

	iomux_lock_save(blockmux, flags);
	if (blockmux->ops && blockmux->ops->block_setfunc) {
		ret = blockmux->ops->block_setfunc(blockmux, config, newmode);
		if (ret < 0) {
			pr_debug("IOMUX:%s's function setting failed.\r\n", blockmux->block_name);
			goto out;
		}
	} else {
		pr_debug("IOMUX:function setting failed.\r\n");
		ret = -INVALID;
	}
out:
	iomux_unlock_restore(blockmux, flags);
	return ret;
}
EXPORT_SYMBOL(blockmux_set);

void __init iomux_init_blocks(void)
{
	int ret;
	struct iomux_block *block_temp = NULL;
	struct block_config *config_temp = NULL;
	struct iomux_block_table *table_temp = NULL;

	table_temp = blocks_table;
	while ((*table_temp).name) {
		block_temp = (*table_temp).block;
		config_temp = (*table_temp).config_array;
		ret = blockmux_set(block_temp, config_temp, LOWPOWER);
		if (ret) {
			printk("IOMUX:iomux initialized failed.\r\n");
			break;
		}
		table_temp++;
	}
	printk("IOMUX:iomux init success.\r\n");
}

#ifdef	CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#include <linux/seq_file.h>
static char g_pullInfo[3][10] = {"NOPULL", "pullup", "pulldown"};

char *pin_pull_status(struct  iomux_pin *pin)
{
	if (pin->pin_pull_updown <= 2)
		return g_pullInfo[pin->pin_pull_updown];
	else
		return NULL;
}
static int dbg_pinmux_show(struct seq_file *s, void *unused)
{
	int i = 0;
	struct iomux_pin_table *pin_table_temp = NULL;
	struct iomux_pin *pin_temp = NULL;

	seq_printf(s, "pinname	       pin_owner        func        \
			pullud        driverstrength		\n");
	seq_printf(s, "-----------------------------------------"
			"-----------------------------------------------\n");

    pin_table_temp = pins_table;
	mutex_lock(&iomux_lock);
	while (pin_table_temp[i].pinname) {
		pin_temp = iomux_get_pin(pin_table_temp[i].pinname);
		if (pin_temp) {
			seq_printf(s, "%s        %s        %d        %s        %d\r\n",
				pin_temp->pin_name,
				pin_temp->pin_owner,
				pin_temp->pin_func,
				pin_pull_status(pin_temp),
				pin_temp->pin_drive_strength);
		}
		i++;
	}
	mutex_unlock(&iomux_lock);
	return 0;
}

static int dbg_pinmux_open(struct inode *inode, struct file *file)
{
	return single_open(file, dbg_pinmux_show, &inode->i_private);
}

static const struct file_operations debug_pin_fops = {
	.open		= dbg_pinmux_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int dbg_blockmux_show(struct seq_file *s, void *unused)
{
	struct iomux_block_table *table_temp = NULL;
	struct iomux_block *block_temp = NULL;
	struct iomux_pin **arraryp = NULL;

	seq_printf(s, "blockname	       func  		\n");
	seq_printf(s, "-----------------------------------------"
			"-----------------------------------------------\n");

	mutex_lock(&iomux_lock_debugfs);
	table_temp = blocks_table;
	while ((*table_temp).name) {
		block_temp = iomux_get_block((*table_temp).name);
		if (block_temp) {
			seq_printf(s, "Block:%s, Mode:%d\r\n",
				block_temp->block_name, block_temp->block_func);

			seq_printf(s, "currfun        pinname	  func  	pullud        driverstrength		\n");
			seq_printf(s, "-----------------------------------------"
			"-----------------------------------------------\n");

			arraryp = block_temp->pins;

			while (*arraryp) {
				seq_printf(s, "%s        %s  	%d        %s       %d\r\n",
				(*arraryp)->pin_owner,
				(*arraryp)->pin_name,
				(*arraryp)->pin_func,
				pin_pull_status(*arraryp),
				(*arraryp)->pin_drive_strength);
				arraryp++;
			}

		} else {
			seq_printf(s, "block get failed\r\n");
		}

		table_temp++;
	}
	mutex_unlock(&iomux_lock_debugfs);

	return 0;
}

static int dbg_blockmux_open(struct inode *inode, struct file *file)
{
	return single_open(file, dbg_blockmux_show, &inode->i_private);
}

static const struct file_operations debug_block_fops = {
	.open		= dbg_blockmux_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init iomux_debuginit(void)
{
	struct dentry *d;

	d = debugfs_create_dir("iomux", NULL);
	if (!d)
		return -ENOMEM;

	(void) debugfs_create_file("blockmux", S_IRUSR,
					d, NULL, &debug_block_fops);
	(void) debugfs_create_file("pinmux", S_IRUSR,
					d, NULL, &debug_pin_fops);
	return 0;
}
late_initcall(iomux_debuginit);
#endif
