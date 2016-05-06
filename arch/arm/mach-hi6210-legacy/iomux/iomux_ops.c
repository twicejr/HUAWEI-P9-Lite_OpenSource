/*
 * arch/arm/mach-k3v2/k3v2_iomux.c
 *
 * Copyright (C) 2011 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 *
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <mach/platform.h>
#include "iomux_ops.h"
#include "iomux.h"

struct iomux_ops iomux_pin_ops = {
	.pin_setfunc = mach_pinmux_func,
	.pin_setpullupdown = mach_pinmux_setpullupdown,
	.pin_setdrivestrength = mach_pinmux_setdrivestrength,
};

struct iomux_ops iomux_block_ops = {
	.block_setfunc = mach_block_setfunc,
};

/*
 *the pin_fun must be set follow the document essued by hardware
 *it is useless to set a function which is not belong to a pin
 */
int mach_pinmux_func(struct iomux_pin *pin, enum lowlayer_func pin_func)
{
	int value1;
	int i = 0;
	int *func_value = NULL;
	struct iomux_iomg *reg_temp = NULL;

	reg_temp = pin->pin_iomg;
	if (reg_temp == NULL) {
		pr_debug("IOMUX:%s's iomg is NULL,don't need to set function.\r\n", pin->pin_name);
		return 0;
	}

	if (pin_func < FUNC0 || pin_func > FUNC6) {
		pr_debug("IOMUX:%d is a invalid function.\r\n", pin_func);
		return -INVALID;
	}

	func_value = reg_temp->regValue;
	/*check the pin_func is valid*/
	if (func_value[pin_func] < 0) {
		pr_debug("IOMUX:%s has no function %d.\r\n",\
			pin->pin_name, pin_func);
		return -INVALID;
	}

	/*write register*/
	value1 = func_value[pin_func];

	__raw_writel(value1, reg_temp->iomg_reg);

	pr_debug("IOMUX:%s set to function %d __raw_writel(0x%x,0x%x)\r\n",\
		pin->pin_name, (int)pin_func, (unsigned int)value1,(unsigned int)reg_temp->iomg_reg);

	pin->pin_func = pin_func;
	return 0;
}

static int iocg_writevalue(struct iomux_pin *pin, enum pull_updown
		pin_pull_updown, enum drive_strength pin_drive_strength)
{
	int value1;
	struct iomux_iocg *reg_temp = NULL;

	reg_temp = pin->pin_iocg;
	if (reg_temp == NULL) {
		pr_debug("IOMUX:%s's iocg is NULL,don't need to set the pull strength.\r\n", pin->pin_name);
		return 0;
	}
	value1 = __raw_readl(reg_temp->iocg_reg);

	if (pin_pull_updown != NOINPUT) {
		switch (reg_temp->iocg_pullupdown_mask) {
		case 1:
			/*0x0001 is pull up set bit*/
			if (pin_pull_updown == PULLDOWN) {
				pr_debug("IOMUX:can't set pull down for %s.\r\n", pin->pin_name);
				return -INVALID;
			}
			break;
		case 2:
			/*0x0002 is pull down set bit*/
			if (pin_pull_updown == PULLUP) {
				pr_debug("IOMUX:can't set pull up for %s.\r\n", pin->pin_name);
				return -INVALID;
			}
			break;
		case 3:
			/*0x0003 is pull up and down mask*/
			break;
		default:
			pr_debug("IOMUX:mask is null,don't need to set the pull up or down for %s.\r\n", pin->pin_name);
			goto drive_set;
		}

		if ((pin_pull_updown == PULLUP) && ( pin->pin_pull_updown == NOPULL)) {
			/*clear the pull up down mask bits*/
			value1 = value1 & (~reg_temp->iocg_pullupdown_mask);
			/*write pin_pull_updown to the mask bits*/
			value1 = value1 | (PULLDOWN << (__ffs(reg_temp->iocg_pullupdown_mask)));
			__raw_writel(value1, reg_temp->iocg_reg);
		}

		/*clear the pull up down mask bits*/
		value1 = value1 & (~reg_temp->iocg_pullupdown_mask);
		/*write pin_pull_updown to the mask bits*/
		value1 = value1 | (pin_pull_updown << (__ffs(reg_temp->iocg_pullupdown_mask)));
		pin->pin_pull_updown = pin_pull_updown;
	}

drive_set:
	if (pin_drive_strength != NOINPUT) {
		if (reg_temp->iocg_drivestrength_mask) {
			/*clear the driver strength mask bits*/
			value1 = value1 & (~reg_temp->iocg_drivestrength_mask);
			/*write diver_strength to the mask bits*/
			value1 = value1 | (pin_drive_strength <<\
				(__ffs(reg_temp->iocg_drivestrength_mask)));
			pin->pin_drive_strength = pin_drive_strength;
		}
	}

	__raw_writel(value1, reg_temp->iocg_reg);
	return 0;
}

int mach_pinmux_setpullupdown(struct iomux_pin *pin,
		enum pull_updown pin_pull_updown)
{
	int ret = 0;
	struct iomux_iocg *reg_temp = NULL;

	reg_temp = pin->pin_iocg;
	if (reg_temp == NULL) {
		pr_debug("IOMUX:%s's iocg is NULL,don't need to set the drive strength for this pin.\r\n", pin->pin_name);
		return 0;
	}

	if (pin_pull_updown < NOPULL || pin_pull_updown > PULLDOWN) {
		pr_debug("IOMUX:the pull value %d is invalid.\r\n", pin_pull_updown);
		return -INVALID;
	}

	ret = iocg_writevalue(pin, pin_pull_updown, NOINPUT);

	pr_debug("IOMUX:%s set pin updown state to %d\r\n",\
		pin->pin_name, (int)pin_pull_updown);

	return ret;
}

int mach_pinmux_setdrivestrength(struct iomux_pin *pin,
	enum drive_strength pin_drive_strength)
{
	int ret = 0;
	struct iomux_iocg *reg_temp = NULL;

	reg_temp = pin->pin_iocg;
	if (reg_temp == NULL) {
		pr_debug("IOMUX:%s's iocg is NULL,don't need to set the drive strength for this pin.\r\n", pin->pin_name);
		return 0;
	}

	if ((pin_drive_strength != LEVEL0) && (pin_drive_strength != LEVEL1) \
		&& (pin_drive_strength != LEVEL2)  && \
		(pin_drive_strength != LEVEL3)) {
		pr_debug("IOMUX:the drive strength value is invalid.\r\n");
		return -INVALID;
	}

	ret = iocg_writevalue(pin, NOINPUT, pin_drive_strength);

	pr_debug("IOMUX:%s set pin strength to %d\r\n",\
		pin->pin_name, (int)pin_drive_strength);

	return ret;
}

int mach_block_setfunc(struct iomux_block  *blockmux,
	struct block_config *config, enum iomux_func newfunc)
{
	int i = 0, ret = -INVALID;
	struct iomux_pin **pins_temp;

	if ((newfunc < NORMAL) || (newfunc > LOWPOWER)) {
		pr_debug("IOMUX:%d is a invalid function.\r\n", newfunc);
		return -INVALID;
	}

	pins_temp = blockmux->pins;
	while (*pins_temp && (config[newfunc].func_value[i] != -INVALID) \
		&& (config[newfunc].drvstrength_value[i] != -INVALID)) {
		ret = mach_pinmux_func(*pins_temp, config[newfunc].func_value[i]);
		if (ret < 0)
			break;

		if (newfunc == NORMAL)
			(*pins_temp)->pin_owner = blockmux->block_name;
		else if (newfunc == GPIO)
			(*pins_temp)->pin_owner = "gpio";
		else if (newfunc == LOWPOWER)
			(*pins_temp)->pin_owner = "lowpower";

		/*set status of block*/

		ret = iocg_writevalue(*pins_temp, config[newfunc].pullud_value[i],\
				config[newfunc].drvstrength_value[i]);
		if (ret < 0)
			break;


		pr_debug("IOMUX:%s set pin updown state to %d strength to %d\r\n",\
			(*pins_temp)->pin_name, (int)config[newfunc].pullud_value[i],(int)config[newfunc].drvstrength_value[i]);



		pins_temp++;
		i++;
	}

	if (ret == 0)
		blockmux->block_func = newfunc;

	return ret;
}




