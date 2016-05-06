/*
 * pin-controller/pin-mux/pin-config driver for Hisilicon hi6402 codec chip.
 *
 * Copyright (c) 2014 Hisilicon Technologies CO.Ltd.
 *		http://www.hisilicon.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/gpio.h>
#include <linux/device.h>
#include <linux/pinctrl/pinctrl.h>
#include <linux/pinctrl/pinmux.h>
#include <linux/pinctrl/pinconf.h>
#include <linux/pinctrl/pinconf-generic.h>
#include <linux/hisi/hi64xx/hi64xx_compat.h>

#include "core.h"
#include "pinconf.h"

#define DRIVER_NAME			"pinctrl-hi6402"

#define PIN_NAME_LENGTH		10
#define GROUP_FLAG		"_g"
#define GSUFFIX_LEN		sizeof(GROUP_FLAG)
#define FUNCTION_FLAG		"_f"
#define FSUFFIX_LEN		sizeof(FUNCTION_FLAG)

#define IOS_REG_COUNTS		5

struct hi6402_pin_group {
	const char *name;
	int *gpins;
	int ngpins;
};

struct hi6402_gpiofunc_range {
	unsigned offset;
	unsigned npins;
	unsigned gpiofunc;
};

struct hi6402_pin_mask_table {
	unsigned mask[IOS_REG_COUNTS];
};

struct hi6402_func_vals {
	unsigned val;
	unsigned *mask;
};

struct hi6402_conf_base {
	enum pin_config_param param;
	unsigned val;
	unsigned mask;
};

struct hi6402_conf_vals {
	struct hi6402_conf_base *configs;
	int nconfs;
	unsigned reg;
};

struct hi6402_conf_type {
	const char *name;
	enum pin_config_param param;
};

struct hi6402_pinctrl_function {
	const char *name;
	struct hi6402_func_vals *vals;
	unsigned nvals;
	const char **groups;
	int num_groups;
	struct hi6402_conf_vals *confs;
};

struct hi6402_pinctrl_device {
	struct device *dev;
	unsigned base_reg;
	unsigned mux_reg[IOS_REG_COUNTS];
	struct pinctrl_dev *pctl;
	const struct hi6402_pin_group *pin_groups;
	const struct hi6402_pinctrl_function *pmx_functions;
	struct hi6402_gpiofunc_range *gpio_func;
	struct hi6402_pin_mask_table *num_mask_tbl;
	unsigned ngroups;
	unsigned nfuncs;
	unsigned ngpiofuncs;
	unsigned (*read)( struct hi6402_pinctrl_device *pindev, unsigned reg);
	void (*write) (struct hi6402_pinctrl_device *pindev, unsigned val, unsigned reg);
};

/* pin config options specfied */
static struct hi6402_conf_type pin_cfgs [] = {
		{ "pinconf-hi6402,bias-pullup", PIN_CONFIG_BIAS_PULL_UP, },
		{ "pinconf-hi6402,bias-pulldown", PIN_CONFIG_BIAS_PULL_DOWN, },
		{ "pinconf-hi6402,drive-strength", PIN_CONFIG_DRIVE_STRENGTH, },
		{ "pinconf-hi6402,slew-rate", PIN_CONFIG_SLEW_RATE, },
		{ "pinconf-hi6402,input-schmitt-enable", PIN_CONFIG_INPUT_SCHMITT_ENABLE, },
		{ "pinconf-hi6402,input-schmitt", PIN_CONFIG_INPUT_SCHMITT, },
};

static enum pin_config_param pin_bias[] = {
	PIN_CONFIG_BIAS_PULL_DOWN,
	PIN_CONFIG_BIAS_PULL_UP,
};

static int hi6402_pinconf_get(struct pinctrl_dev *pctldev, unsigned pin,
			   unsigned long *config);
static int hi6402_pinconf_set(struct pinctrl_dev *pctldev, unsigned pin,
			   unsigned long config);

static unsigned hi6402_pinctrl_readl(struct hi6402_pinctrl_device *pindev, unsigned reg)
{
	return hi64xx_compat_reg_read(pindev->base_reg + reg);
}

static void hi6402_pinctrl_writel(struct hi6402_pinctrl_device *pindev, unsigned val, unsigned reg)
{
	hi64xx_compat_reg_write(pindev->base_reg + reg, val);
}

static int hi6402_get_group_count(struct pinctrl_dev *pctldev)
{
	struct hi6402_pinctrl_device *pindev;

	pindev = pinctrl_dev_get_drvdata(pctldev);
	return pindev->ngroups;
}

static const char *hi6402_get_group_name(struct pinctrl_dev *pctldev,
						unsigned selector)
{
	struct hi6402_pinctrl_device *pindev;

	pindev = pinctrl_dev_get_drvdata(pctldev);
	if (!(&pindev->pin_groups[selector])) {
		dev_err(pindev->dev, "%s could not find pingroup%i\n",
			__func__, selector);
		return NULL;
	}

	return pindev->pin_groups[selector].name;
}

static int hi6402_get_group_pins(struct pinctrl_dev *pctldev,
		unsigned selector, const unsigned **pins, unsigned *num_pins)
{
	struct hi6402_pinctrl_device *pindev;

	pindev = pinctrl_dev_get_drvdata(pctldev);

	if (!(&pindev->pin_groups[selector])) {
		dev_err(pindev->dev, "%s could not find pingroup%i\n",
			__func__, selector);
		return -EINVAL;
	}
	*pins = pindev->pin_groups[selector].gpins;
	*num_pins = pindev->pin_groups[selector].ngpins;
	return 0;
}

static int hi6402_dt_node_to_map(struct pinctrl_dev *pctldev,
			struct device_node *np, struct pinctrl_map **maps,
			unsigned *nmaps)
{
	struct device *dev = pctldev->dev;
	struct pinctrl_map *map;
	unsigned long *cfg = NULL;
	u32 value[2] = {0};
	char *gname, *fname = NULL;
	int cfg_cnt = 0, map_cnt = 0, idx = 0;

	/* count the number of config options specfied in the node */
	for (idx = 0; idx < ARRAY_SIZE(pin_cfgs); idx++)
		if (of_find_property(np, pin_cfgs[idx].name, NULL))
			cfg_cnt++;

	/*
	 * Find out the number of map entries to create. All the config options
	 * can be accomadated into a single config map entry.
	 */
	if (cfg_cnt)
		map_cnt = 1;
	if (of_find_property(np, "pinmux-hi6402,func-sel", NULL))
		map_cnt++;
	if (!map_cnt) {
		dev_err(dev, "node %s does not have either config or function "
				"configurations\n", np->name);
		return -EINVAL;
	}

	/* Allocate memory for pin-map entries */
	map = devm_kzalloc(dev, sizeof(*map) * map_cnt, GFP_KERNEL);
	if (!map) {
		dev_err(dev, "could not alloc memory for pin-maps\n");
		return -ENOMEM;
	}
	*nmaps = 0;

	/*
	 * Allocate memory for pin group name. The pin group name is derived
	 * from the node name from which these map entries are be created.
	 */
	gname = devm_kzalloc(dev, strlen(np->name) + GSUFFIX_LEN, GFP_KERNEL);
	if (!gname) {
		dev_err(dev, "failed to alloc memory for group name\n");
		goto free_map;
	}
	sprintf(gname, "%s%s", np->name, GROUP_FLAG);

	/* create the function map entry */
	if (of_find_property(np, "pinmux-hi6402,func-sel", NULL)) {
		fname = devm_kzalloc(dev, strlen(np->name) + FSUFFIX_LEN, GFP_KERNEL);
		if (!fname) {
			dev_err(dev, "failed to alloc memory for func name\n");
			goto free_gname;
		}
		sprintf(fname, "%s%s", np->name, FUNCTION_FLAG);

		map[*nmaps].data.mux.group = gname;
		map[*nmaps].data.mux.function = fname;
		map[*nmaps].type = PIN_MAP_TYPE_MUX_GROUP;
		*nmaps += 1;
	}

	/*
	 * don't have config options? then skip over to creating function
	 * map entries.
	 */
	if (cfg_cnt) {
		/* Allocate memory for config entries */
		cfg = devm_kzalloc(dev, sizeof(*cfg) * cfg_cnt, GFP_KERNEL);
		if (!cfg) {
			dev_err(dev, "failed to alloc memory for configs\n");
			goto free_cfg;
		}

		/* Prepare a list of config settings */
		for (idx = 0, cfg_cnt = 0; idx < ARRAY_SIZE(pin_cfgs); idx++) {
			if (!of_property_read_u32_array(np, pin_cfgs[idx].name, value, 2))
				cfg[cfg_cnt++] =
					pinconf_to_config_packed(pin_cfgs[idx].param, value[0]);
		}

		/* create the config map entry */
		map[*nmaps].data.configs.group_or_pin = gname;
		map[*nmaps].data.configs.configs = cfg;
		map[*nmaps].data.configs.num_configs = cfg_cnt;
		map[*nmaps].type = PIN_MAP_TYPE_CONFIGS_GROUP;
		*nmaps += 1;
	}

	*maps = map;
	return 0;

free_cfg:
	if (fname)
		devm_kfree(dev, fname);
free_gname:
	devm_kfree(dev, gname);
free_map:
	devm_kfree(dev, map);
	return -ENOMEM;
}



/* free the memory allocated to hold the pin-map table */
static void hi6402_dt_free_map(struct pinctrl_dev *pctldev,
			     struct pinctrl_map *map, unsigned num_maps)
{
	struct device *dev = pctldev->dev;
	int idx;

	for (idx = 0; idx < num_maps; idx++) {
		if (map[idx].type == PIN_MAP_TYPE_MUX_GROUP) {
			devm_kfree(dev, (void *)map[idx].data.mux.function);
			if (!idx)
				devm_kfree(dev, (void *)map[idx].data.mux.group);
		} else if (map->type == PIN_MAP_TYPE_CONFIGS_GROUP) {
			devm_kfree(dev, map[idx].data.configs.configs);
			if (!idx)
				devm_kfree(dev, (void *)map[idx].data.configs.group_or_pin);
		}
	};

	devm_kfree(dev, map);
}

static const struct pinctrl_ops hi6402_pctrl_ops = {
	.get_groups_count	= hi6402_get_group_count,
	.get_group_name		= hi6402_get_group_name,
	.get_group_pins		= hi6402_get_group_pins,
	.dt_node_to_map		= hi6402_dt_node_to_map,
	.dt_free_map		= hi6402_dt_free_map,
};

static int hi6402_get_functions_count(struct pinctrl_dev *pctldev)
{
	struct hi6402_pinctrl_device *pindev;

	pindev = pinctrl_dev_get_drvdata(pctldev);
	return pindev->nfuncs;
}

static const char *hi6402_pinmux_get_fname(struct pinctrl_dev *pctldev,
						unsigned selector)
{
	struct hi6402_pinctrl_device *pindev;

	pindev = pinctrl_dev_get_drvdata(pctldev);

	if (!(&pindev->pmx_functions[selector])) {
		dev_err(pindev->dev, "%s could not find function%i\n",
			__func__, selector);
		return NULL;
	}

	return pindev->pmx_functions[selector].name;
}

static int hi6402_get_function(struct pinctrl_dev *pctldev, unsigned pin,
			    	const struct hi6402_pinctrl_function **func)
{
	struct hi6402_pinctrl_device *pindev = pinctrl_dev_get_drvdata(pctldev);
	struct pin_desc *pdesc = pin_desc_get(pctldev, pin);
	const struct pinctrl_setting_mux *setting;
	unsigned fselector;

	/* If pin is not described in DTS & enabled, mux_setting is NULL. */
	setting = pdesc->mux_setting;
	if (!setting) {
		dev_err(pindev->dev, "PIN-%d does not be registered\n", pin);
		return -ENOTSUPP;
	}
	fselector = setting->func;
	*func = &pindev->pmx_functions[fselector];
	if (!(*func)) {
		dev_err(pindev->dev, "%s could not find function%i\n",
			__func__, fselector);
		return -ENOTSUPP;
	}
	return 0;
}

static int hi6402_pinmux_get_groups(struct pinctrl_dev *pctldev,
		unsigned selector, const char * const **groups,
		unsigned * const num_groups)
{
	struct hi6402_pinctrl_device *pindev;
	pindev = pinctrl_dev_get_drvdata(pctldev);

	if (!(&pindev->pmx_functions[selector])) {
		dev_err(pindev->dev, "%s could not find function%i\n",
			__func__, selector);
		return -EINVAL;
	}

	*groups = pindev->pmx_functions[selector].groups;
	*num_groups = pindev->pmx_functions[selector].num_groups;

	return 0;
}

static void hi6402_pinmux_reg_ctrl(struct hi6402_pinctrl_device *pindev,
						struct hi6402_func_vals *fval,
						unsigned gpio_func,
						unsigned pin)
{
	int i;
	u32 data;
	unsigned value, *mask;

	if (fval) {
		value = fval->val;
		mask = fval->mask;
	} else {
		value = gpio_func;
		mask = pindev->num_mask_tbl[pin].mask;
	}

	for (i = 0; i < value; i++) {
		if (mask[i] == 0x20)
			continue;
		data = pindev->read(pindev, pindev->mux_reg[i]);
		data &= ~BIT(mask[i]);
		pindev->write(pindev, data, pindev->mux_reg[i]);
	}

	if (mask[i] == 0x20) {
		pr_debug("func-value could not match the mask bit\n");
		return;
	}
	data = pindev->read(pindev, pindev->mux_reg[i]);
	data |= BIT(mask[i]);
	pindev->write(pindev, data, pindev->mux_reg[i]);
}

static int hi6402_pinmux_enable(struct pinctrl_dev *pctldev, unsigned selector,
					unsigned group)
{
	struct hi6402_pinctrl_device *pindev;
	struct hi6402_func_vals *fval;

	pindev = pinctrl_dev_get_drvdata(pctldev);
	if (!(&pindev->pmx_functions[selector])) {
		dev_err(pindev->dev, "%s could not find function%i\n",
			__func__, selector);
		return -EINVAL;
	}

	fval = pindev->pmx_functions[selector].vals;
	hi6402_pinmux_reg_ctrl(pindev, fval, 0, 0);

	return 0;
}

static void hi6402_pinmux_disable(struct pinctrl_dev *pctldev,
					unsigned selector, unsigned group)
{
	struct hi6402_pinctrl_device *pindev = pinctrl_dev_get_drvdata(pctldev);
	/* hi6402 chip dose not support to disable mux */
	dev_dbg(pindev->dev, "%s ignoring disable for function%i\n",
			__func__, selector);
	return;
}

/* hooked with gpio drivers */
static int hi6402_request_gpio(struct pinctrl_dev *pctldev,
			    struct pinctrl_gpio_range *range, unsigned pin)
{
	struct hi6402_pinctrl_device *pindev = pinctrl_dev_get_drvdata(pctldev);
	struct hi6402_gpiofunc_range *frange = NULL;
	int i;

	for (i = 0; i < pindev->ngpiofuncs; i++) {
		frange = &pindev->gpio_func[i];
		if ((pin >= (frange->offset + frange->npins)) || (pin < frange->offset))
			continue;
		if (!(&pindev->num_mask_tbl[pin])) {
			dev_err(pindev->dev, "pin-%d mask-table do not be initialized\n", pin);
			return -ENOTSUPP;
		}

		hi6402_pinmux_reg_ctrl(pindev, NULL, frange->gpiofunc, pin);
		break;
	}

	return 0;
}

static const struct pinmux_ops hi6402_pinmux_ops = {
	.get_functions_count	= hi6402_get_functions_count,
	.get_function_name	= hi6402_pinmux_get_fname,
	.get_function_groups	= hi6402_pinmux_get_groups,
	.enable			= hi6402_pinmux_enable,
	.disable		= hi6402_pinmux_disable,
	.gpio_request_enable	= hi6402_request_gpio,
};

static void hi6402_pinconf_clear_bias(struct pinctrl_dev *pctldev, unsigned pin)
{
	unsigned long config;
	int i;

	for (i = 0; i < ARRAY_SIZE(pin_bias); i++) {
		config = pinconf_to_config_packed(pin_bias[i], 0);
		hi6402_pinconf_set(pctldev, pin, config);
	}
}

/*
 * Check whether PIN_CONFIG_BIAS_DISABLE is valid.
 * It's depend on that PULL_DOWN & PULL_UP configs are all invalid.
 */
static bool hi6402_pinconf_bias_disable(struct pinctrl_dev *pctldev, unsigned pin)
{
	unsigned long config;
	int i;

	for (i = 0; i < ARRAY_SIZE(pin_bias); i++) {
		config = pinconf_to_config_packed(pin_bias[i], 0);
		if (!hi6402_pinconf_get(pctldev, pin, &config))
			goto out;
	}
	return true;
out:
	return false;
}

static int hi6402_pinconf_get(struct pinctrl_dev *pctldev, unsigned int pin,
				unsigned long *config)
{
	struct hi6402_pinctrl_device *pindev = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param;
	const struct hi6402_pinctrl_function *func;
	unsigned data, data1;
	int i, j, ret;

	ret = hi6402_get_function(pctldev, pin, &func);
	if (ret)
		return ret;

	for (i = 0; i < func->confs->nconfs; i++) {
		param = pinconf_to_config_param(*config);
		if (param == PIN_CONFIG_BIAS_DISABLE) {
			if (hi6402_pinconf_bias_disable(pctldev, pin)) {
				*config = 0;
				return 0;
			} else {
				return -ENOTSUPP;
			}
		} else if (param != func->confs->configs[i].val) {
			continue;
		}

		data = pindev->read(pindev, func->confs->reg) & func->confs->configs[i].mask;

		switch (func->confs->configs[i].param) {
		case PIN_CONFIG_BIAS_PULL_DOWN:
		case PIN_CONFIG_BIAS_PULL_UP:
		case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		case PIN_CONFIG_DRIVE_STRENGTH:
		case PIN_CONFIG_SLEW_RATE:
			*config = data;
			break;
		case PIN_CONFIG_INPUT_SCHMITT:
			for (j = 0; j < func->confs->nconfs; j++) {
				switch (func->confs->configs[j].param) {
				case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
					data1 = pindev->read(pindev, func->confs->reg) & func->confs->configs[j].mask;
					if (!data1)
						return -ENOTSUPP;
					break;
				default:
					break;
				}
			}
		default:
			*config = data;
			break;
		}
		return 0;
	}

	return -ENOTSUPP;
}

/* get the pin config settings for a specified pin */
static int hi6402_pinconf_set(struct pinctrl_dev *pctldev, unsigned int pin,
					unsigned long config)
{
	struct hi6402_pinctrl_device *pindev = pinctrl_dev_get_drvdata(pctldev);
	const struct hi6402_pinctrl_function *func;
	unsigned data;
	int i, ret;
	u16 arg;

	ret = hi6402_get_function(pctldev, pin, &func);
	if (ret)
		return ret;

	for (i = 0; i < func->confs->nconfs; i++) {
		if (pinconf_to_config_param(config) == func->confs->configs[i].param) {
			data = pindev->read(pindev, func->confs->reg);
			arg = pinconf_to_config_argument(config);
			switch (func->confs->configs[i].param) {
			case PIN_CONFIG_BIAS_DISABLE:
				hi6402_pinconf_clear_bias(pctldev, pin);
				break;
			case PIN_CONFIG_BIAS_PULL_DOWN:
			case PIN_CONFIG_BIAS_PULL_UP:
				if (arg)
					hi6402_pinconf_clear_bias(pctldev, pin);
			case PIN_CONFIG_INPUT_SCHMITT:
			case PIN_CONFIG_DRIVE_STRENGTH:
			case PIN_CONFIG_SLEW_RATE:
			case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
				data &= ~func->confs->configs[i].mask;
				if (arg)
					data |= arg;
				break;
			default:
				return -ENOTSUPP;
			}

			pindev->write(pindev, data, func->confs->reg);
			return 0;
		}
	}
	return -ENOTSUPP;
}

static int hi6402_pinconf_group_get(struct pinctrl_dev *pctldev,
				unsigned group, unsigned long *config)
{
	const unsigned *pins;
	unsigned npins, old = 0;
	int i, ret;

	ret = hi6402_get_group_pins(pctldev, group, &pins, &npins);
	if (ret)
		return ret;

	for (i = 0; i < npins; i++) {
		if (hi6402_pinconf_get(pctldev, pins[i], config))
			return -ENOTSUPP;
		/* configs do not match between two pins */
		if (i && (old != *config))
			return -ENOTSUPP;
		old = *config;
	}

	return 0;
}

static int hi6402_pinconf_group_set(struct pinctrl_dev *pctldev,
				unsigned group, unsigned long config)
{
	const unsigned *pins;
	unsigned npins;
	int i, ret;

	ret = hi6402_get_group_pins(pctldev, group, &pins, &npins);
	if (ret)
		return ret;

	for (i = 0; i < npins; i++)
		if (hi6402_pinconf_set(pctldev, pins[i], config))
			return -ENOTSUPP;

	return 0;
}

static void hi6402_pinconf_dbg_show(struct pinctrl_dev *pctldev,
				struct seq_file *s, unsigned pin)
{
}

static void hi6402_pinconf_group_dbg_show(struct pinctrl_dev *pctldev,
				struct seq_file *s, unsigned selector)
{
}

static void hi6402_pinconf_config_dbg_show(struct pinctrl_dev *pctldev,
					struct seq_file *s,
					unsigned long config)
{
	pinconf_generic_dump_config(pctldev, s, config);
}

/* list of pinconfig callbacks for pinconfig vertical in the pinctrl code */
static const struct pinconf_ops hi6402_pinconf_ops = {
	.pin_config_get	= hi6402_pinconf_get,
	.pin_config_set = hi6402_pinconf_set,
	.pin_config_group_get = hi6402_pinconf_group_get,
	.pin_config_group_set = hi6402_pinconf_group_set,
	.pin_config_dbg_show = hi6402_pinconf_dbg_show,
	.pin_config_group_dbg_show = hi6402_pinconf_group_dbg_show,
	.pin_config_config_dbg_show = hi6402_pinconf_config_dbg_show,
	.is_generic = true,
};

static int hi6402_pinctrl_parse_dt_pins(struct device *dev,
			struct device_node *cfg_np, unsigned int **pin_list,
			unsigned int *npins)
{
	const __be32 *mux;
	int size;

	mux = of_get_property(cfg_np, "pinctrl-hi6402,pins", &size);
	if (!mux) {
		dev_err(dev, "no valid property for %s\n", cfg_np->name);
		return -EINVAL;
	}

	if (size < sizeof(*mux)) {
		dev_err(dev, "bad data for %s\n", cfg_np->name);
		return -EINVAL;
	}

	size /= sizeof(*mux);	/* Number of elements in array */
	*npins = size;
	*pin_list = devm_kzalloc(dev, *npins * sizeof(**pin_list), GFP_KERNEL);
	if (!*pin_list) {
		dev_err(dev, "could not allocate memory for pin list\n");
		return -ENOMEM;
	}

	return of_property_read_u32_array(cfg_np, "pinctrl-hi6402,pins",
			*pin_list, *npins);
}

static int hi6402_pinctrl_parse_mask_table(struct hi6402_pinctrl_device *pindev)
{
	struct device *dev = pindev->dev;
	struct device_node *np = dev->of_node;
	struct hi6402_pin_mask_table *table;
	const __be32 *mux;
	int ret, size, rows, params = IOS_REG_COUNTS;

	mux = of_get_property(np, "pinctrl-hi6402,bits-ctrl", &size);
	if (!mux) {
		dev_err(dev, "could not get 'bits-ctrl' property\n");
		return -EINVAL;
	}

	if (size < (sizeof(*mux) * params)) {
		dev_err(dev, "bits-ctrl data is bad\n");
		return -EINVAL;
	}

	size /= sizeof(*mux);	/* Number of elements in array */
	rows = size / params;

	pr_debug("%s: number of elements is %d, rows is %d\n", __func__, size, rows);

	table = devm_kzalloc(dev, rows * sizeof(*table), GFP_KERNEL);
	if (!table) {
		dev_err(dev, "could not allocate memory for pin num-mask table\n");
		return -ENOMEM;
	}

	ret = of_property_read_u32_array(np, "pinctrl-hi6402,bits-ctrl",
						(u32 *)table, size);
	if (ret) {
		dev_err(dev, "could not read 'bits-ctrl' data\n");
		return ret;
	}

	pindev->num_mask_tbl = table;

	return 0;

}

static int hi6402_pinctrl_add_function(struct hi6402_pinctrl_device *pindev,
						struct device_node *cfg_np,
						struct hi6402_pinctrl_function *pfunc,
						char *gname)
{
	struct device *dev = pindev->dev;
	struct hi6402_pinctrl_function *func = pfunc;
	struct hi6402_func_vals *func_vals;
	struct hi6402_conf_vals *conf_vals;
	struct hi6402_conf_base *conf_base;
	u32 pin_num = 0;
	u32 function= 0;
	u32 reg = 0;
	char *fname = NULL;
	u32 value[2] = {0};
	int func_flag, conf_flag, cfg_cnt = 0, idx;

	func_flag = of_property_read_u32(cfg_np, "pinmux-hi6402,func-sel",
						&function);
	conf_flag = of_property_read_u32(cfg_np, "pinconf-hi6402,ios-ctrl-conf",
						&reg);

	if (func_flag && conf_flag) {
		dev_info(dev, "function:%s%s could not get available infomation\n",
						cfg_np->name, FUNCTION_FLAG);
		return 0;
	}

	/* derive function name from the node name */
	fname = devm_kzalloc(dev, strlen(cfg_np->name) + FSUFFIX_LEN,
				GFP_KERNEL);
	if (!fname) {
		dev_err(dev, "could not alloc memory for func(%s%s) name\n",
						cfg_np->name, FUNCTION_FLAG);
		return -ENOMEM;
	}
	sprintf(fname, "%s%s", cfg_np->name, FUNCTION_FLAG);

	if (func_flag)
		goto skip_to_config_function;

	/* add pinmux function */
	func_vals = devm_kzalloc(dev, sizeof(*func_vals), GFP_KERNEL);
	if (!func_vals) {
		dev_err(dev, "could not alloc memory for func(%s%s) vals\n",
						cfg_np->name, FUNCTION_FLAG);
		return -ENOMEM;
	}

	func->vals = func_vals;
	func_vals->val = function;

	if (of_property_read_u32_array(cfg_np, "pinctrl-hi6402,pins", &pin_num, 1)) {
		dev_err(dev, "could not get func(%s%s) pin\n",
						cfg_np->name, FUNCTION_FLAG);
		return -EINVAL;
	}

	func_vals->mask = pindev->num_mask_tbl[pin_num].mask;

skip_to_config_function:
	/* add pinconf function */
	conf_vals = devm_kzalloc(dev, sizeof(*conf_vals), GFP_KERNEL);
	if (!conf_vals) {
		dev_err(dev, "could not alloc memory for conf(%s%s) vals\n",
						cfg_np->name, FUNCTION_FLAG);
		return -ENOMEM;
	}

	func->confs = conf_vals;
	conf_vals->reg = reg;

	for (idx = 0; idx < ARRAY_SIZE(pin_cfgs); idx++)
		if (of_find_property(cfg_np, pin_cfgs[idx].name, NULL))
			cfg_cnt++;

	conf_base = devm_kzalloc(dev, sizeof(*conf_base) * cfg_cnt, GFP_KERNEL);
	if (!conf_base) {
		dev_err(dev, "could not alloc memory for conf(%s%s) base configs\n",
						cfg_np->name, FUNCTION_FLAG);
		return -ENOMEM;
	}

	conf_vals->configs = conf_base;
	conf_vals->nconfs = cfg_cnt;
	/* Prepare a list of configs */
	for (idx = 0, cfg_cnt = 0; idx < ARRAY_SIZE(pin_cfgs); idx++) {
		if (!of_property_read_u32_array(cfg_np, pin_cfgs[idx].name, value, 2)) {
			conf_base[cfg_cnt].param = pin_cfgs[idx].param;
			conf_base[cfg_cnt].val = value[0];
			conf_base[cfg_cnt].mask = value[1];
			cfg_cnt++;
		}
	}

	/* add pinctrl-functioon(pinmux&pinconf function) */
	func->name = fname;
	func->groups = devm_kzalloc(dev, sizeof(char *), GFP_KERNEL);
	if (!func->groups) {
		dev_err(dev, "could not alloc func(%s%s) memory for group list\n",
						cfg_np->name, FUNCTION_FLAG);
		return -ENOMEM;
	}

	func->groups[0] = gname;
	func->num_groups = gname ? 1 : 0;
	return 0;
}

/*
 * Parse the information about all the available pin groups and pin functions
 * from device node of the pin-controller.
 */
static int hi6402_pinctrl_parse_dt(struct device *dev,
				struct hi6402_pinctrl_device *pindev)
{
	struct device_node *dev_np = dev->of_node;
	struct device_node *cfg_np;
	struct hi6402_pin_group *groups, *grp;
	struct hi6402_pinctrl_function *functions, *func;
	unsigned *pin_list;
	unsigned int npins, grp_cnt, func_idx = 0;
	char *gname;
	int ret;

	ret = hi6402_pinctrl_parse_mask_table(pindev);
	if (ret)
		return ret;

	grp_cnt = of_get_child_count(dev_np);
	if (!grp_cnt) {
		dev_dbg(dev, "could not find config node\n");
		return 0;
	}

	groups = devm_kzalloc(dev, grp_cnt * sizeof(*groups), GFP_KERNEL);
	if (!groups) {
		dev_err(dev, "could not allocate memory for ping group list\n");
		return -EINVAL;
	}
	grp = groups;

	functions = devm_kzalloc(dev, grp_cnt * sizeof(*functions), GFP_KERNEL);
	if (!functions) {
		dev_err(dev, "could not allocate memory for function list\n");
		return -EINVAL;
	}
	func = functions;

	/*
	 * Iterate over all the child nodes of the pin controller node
	 * and create pin groups and pin function lists.
	 */
	for_each_child_of_node(dev_np, cfg_np) {
		ret = hi6402_pinctrl_parse_dt_pins(dev, cfg_np,
					&pin_list, &npins);
		if (ret) {
			gname = NULL;
			goto skip_to_pin_function;
		}

		/* derive pin group name from the node name */
		gname = devm_kzalloc(dev, strlen(cfg_np->name) + GSUFFIX_LEN,
					GFP_KERNEL);
		if (!gname) {
			dev_err(dev, "could not alloc group(%s%s) memory for name\n",
						cfg_np->name, GROUP_FLAG);
			return -ENOMEM;
		}
		sprintf(gname, "%s%s", cfg_np->name, GROUP_FLAG);

		grp->name = gname;
		grp->gpins = pin_list;
		grp->ngpins= npins;
		grp++;

skip_to_pin_function:
		if (hi6402_pinctrl_add_function(pindev, cfg_np, func, gname))
			return -ENOMEM;

		func++;
		func_idx++;
	}

	pindev->pin_groups = groups;
	pindev->ngroups = grp_cnt;
	pindev->pmx_functions = functions;
	pindev->nfuncs = func_idx;

	return 0;
}

static int hi6402_add_gpio_func(struct hi6402_pinctrl_device *pindev)
{
	struct device_node *node = pindev->dev->of_node;
	const char *propname = "pinctrl-hi6402,gpio-range";
	struct hi6402_gpiofunc_range *range;
	const __be32 *mux;
	int ret, size, rows, params = 3;

	mux = of_get_property(node, propname, &size);
	if (!mux) {
		dev_info(pindev->dev, "gpio range could not be supported\n");
		return 0;
	}

	if (size < (sizeof(*mux) * params)) {
		dev_err(pindev->dev, "gpio range data is bad\n");
		return -EINVAL;
	}

	size /= sizeof(*mux);	/* Number of elements in array */
	rows = size / params;

	pr_debug("%s: number of elements is %d, rows is %d\n", __func__, size, rows);

	range = devm_kzalloc(pindev->dev, rows * sizeof(*range), GFP_KERNEL);
	if (!range) {
		dev_err(pindev->dev, "could not alloc memory gpio range");
		return -ENOMEM;
	}

	pindev->gpio_func = range;
	ret = of_property_read_u32_array(node, propname, (u32 *)range, size);
	if (ret) {
		dev_err(pindev->dev, "could not read 'gpio-range' data\n");
		return ret;
	}
	pindev->ngpiofuncs = rows;

	return 0;
}

static int hi6402_pinctrl_register(struct hi6402_pinctrl_device *pindev)
{
	struct device_node *np = pindev->dev->of_node;
	struct device *dev = pindev->dev;
	struct pinctrl_desc *pinctrl_desc;
	struct pinctrl_dev *pctl_dev;
	struct pinctrl_pin_desc *pindesc, *pdesc;
	char *pin_names;
	int pin = 0;
	int ret = 0;

	pinctrl_desc = devm_kzalloc(dev, sizeof(*pinctrl_desc), GFP_KERNEL);
	if (!pinctrl_desc) {
		dev_err(dev, "could not allocate memory for pinctrl desc\n");
		return -ENOMEM;
	}

	pinctrl_desc->name = "pinctrl-hi6402";
	pinctrl_desc->owner = THIS_MODULE;
	pinctrl_desc->pctlops = &hi6402_pctrl_ops;
	pinctrl_desc->pmxops = &hi6402_pinmux_ops;
	pinctrl_desc->confops = &hi6402_pinconf_ops;

	ret = of_property_read_u32(np, "pinctrl-hi6402,pins-max-num",
						&pin);
	if (ret) {
		dev_err(dev, "could not find max pin number of the controller\n");
		return ret;
	}
	pindesc = devm_kzalloc(dev, sizeof(*pindesc) *
				pin, GFP_KERNEL);
	if (!pindesc) {
		dev_err(dev, "mem alloc for pin descriptors failed\n");
		return -ENOMEM;
	}
	pinctrl_desc->pins = pindesc;
	pinctrl_desc->npins = pin;

	for (pin = 0, pdesc = pindesc; pin < pinctrl_desc->npins; pin++, pdesc++)
		pdesc->number = pin;

	pin_names = devm_kzalloc(dev, sizeof(char) * PIN_NAME_LENGTH *
					pinctrl_desc->npins, GFP_KERNEL);
	if (!pin_names) {
		dev_err(dev, "mem alloc for pin names failed\n");
		return -ENOMEM;
	}

	/* for each pin, set the name of the pin */
	for (pin = 0; pin < pinctrl_desc->npins; pin++) {
		sprintf(pin_names, "pin%02d", pin);
		pdesc = pindesc + pin;
		pdesc->name = pin_names;
		pin_names += PIN_NAME_LENGTH;
	}

	ret = hi6402_pinctrl_parse_dt(dev, pindev);
	if (ret)
		return ret;

	pctl_dev = pinctrl_register(pinctrl_desc, dev, pindev);
	if (!pctl_dev) {
		dev_err(dev, "could not register pinctrl driver\n");
		return -EINVAL;
	}

	ret = hi6402_add_gpio_func(pindev);
	if (ret) {
		pinctrl_unregister(pctl_dev);
		return ret;
	}

	pindev->pctl = pctl_dev;
	return 0;
}

static void hi6402_pinctrl_free_resources(struct hi6402_pinctrl_device *pindev)
{
	if (pindev->pctl)
		pinctrl_unregister(pindev->pctl);
}

static int hi6402_pinctrl_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct hi6402_pinctrl_device *pindev;
	int ret;
	pindev = devm_kzalloc(dev, sizeof(*pindev), GFP_KERNEL);
	if (!pindev) {
		dev_err(dev, "could not allocate memory for device\n");
		return -ENOMEM;
	}

	pindev->dev = dev;

	pindev->read = hi6402_pinctrl_readl;
	pindev->write = hi6402_pinctrl_writel;

	ret = of_property_read_u32(np, "pinctrl-hi6402,base-reg", &pindev->base_reg);
	if (ret) {
		dev_err(dev, "could not find base address\n");
		return -ENOENT;
	}

	ret = of_property_read_u32_array(np, "pinctrl-hi6402,ios-ctrl-mux",
					pindev->mux_reg, IOS_REG_COUNTS);
	if (ret) {
		dev_err(dev, "could not find ios mux address\n");
		return -ENOENT;
	}

	ret = hi6402_pinctrl_register(pindev);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, pindev);

	dev_info(dev, "hi6402 pin controller is initialized\n");
	return 0;
}

static int hi6402_pinctrl_remove(struct platform_device *pdev)
{
	struct hi6402_pinctrl_device *pindev = platform_get_drvdata(pdev);

	if (!pindev)
		return 0;

	hi6402_pinctrl_free_resources(pindev);

	return 0;
}

static struct of_device_id hi6402_pinctrl_of_match[] = {
	{ .compatible = "hisilicon,pinctrl-hi6402" },
	{ },
};

MODULE_DEVICE_TABLE(of, hi6402_pinctrl_of_match);

static struct platform_driver hi6402_pinctrl_driver = {
	.probe		= hi6402_pinctrl_probe,
	.remove		= hi6402_pinctrl_remove,
	.driver = {
		.owner		= THIS_MODULE,
		.name		= DRIVER_NAME,
		.of_match_table	= hi6402_pinctrl_of_match,
	},
};

static int __init hi6402_pinctrl_driver_init(void)
{
	return platform_driver_register(&hi6402_pinctrl_driver);
}

static void __exit hi6402_pinctrl_driver_exit(void)
{
	platform_driver_unregister(&hi6402_pinctrl_driver);
}

rootfs_initcall(hi6402_pinctrl_driver_init);
module_exit(hi6402_pinctrl_driver_exit);

MODULE_AUTHOR("w00221409 <hw.wangxiaoyin@hisilicon.com>");
MODULE_DESCRIPTION("Hisilicon Hi6402 Codec Chip pinctrl driver");
MODULE_LICENSE("GPL v2");

