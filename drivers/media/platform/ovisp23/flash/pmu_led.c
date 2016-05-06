/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "hisi_flash.h"
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/regulator/of_regulator.h>
#include <linux/mfd/hisi_hi3630_regulator.h>
#include <linux/regulator/consumer.h>

/* boost control register */
#define BST_CTRL9			0x0b8

/* control boost enable register */
#define BST_CTRL1			0x0b0

/* the value use to set boost output voltage to 4.5V, set OCP overload current to 4.4A*/
#define BST_VOL				0x2a

#define BST_ENABLE			0x01

/* PMU LED Registers define */
#define LED_CTRL1			0x0d9
#define LED_CTRL2			0x0da
#define LED_CTRL3			0x0db
#define LED_CTRL4			0x0dc
#define LED_CTRL5			0x0dd
#define LED_CTRL6			0x0de
#define LED_CTRL7			0x0df

#define LED_FLASH_ENABLE		0x01
#define LED_TORCH_ENABLE		0x02

#define FLASH_LED_MAX			11
#define TORCH_LED_MAX			8

#define LED_VOLTAGE_4P5V		4500000

/* Internal data struct define */
typedef enum {
	LED_CTRL_1 = 0,
	LED_CTRL_2,
	LED_CTRL_3,
	LED_CTRL_4,
	LED_CTRL_5,
	LED_CTRL_6,
	LED_CTRL_7,
	LED_CTRL_MAX,
}pmu_led_ctl_type;

struct pmu_led_private_data_t {
	unsigned int flash_led[FLASH_LED_MAX];
	unsigned int torch_led[TORCH_LED_MAX];
	unsigned int flash_led_num;
	unsigned int torch_led_num;
	unsigned int led_ctrl_flash[LED_CTRL_MAX];
	unsigned int led_ctrl_torch[LED_CTRL_MAX];
	void __iomem *pmu_base;
	struct regulator_bulk_data led_vcc;
};

/* Internal varible define */
static struct pmu_led_private_data_t pmu_led_pdata;
static struct hisi_flash_ctrl_t pmu_led_ctrl;

DEFINE_HISI_FLASH_MUTEX(pmu_led);

/* Function define */
#if 0
static unsigned char pmu_led_read(unsigned int reg)
{
	struct pmu_led_private_data_t *pdata;

	pdata = (struct pmu_led_private_data_t *)pmu_led_ctrl.pdata;

	return readl(pdata->pmu_base + (reg<<2));
}
#endif
static void pmu_led_write(unsigned int reg, unsigned int val)
{
	struct pmu_led_private_data_t *pdata;

	cam_debug("%s reg=0x%x, val=0x%x.", __func__, reg, val);

	pdata = (struct pmu_led_private_data_t *)pmu_led_ctrl.pdata;
	writel(val, (pdata->pmu_base + (reg<<2)));
}

static int pmu_led_init(struct hisi_flash_ctrl_t *flash_ctrl)
{
	struct pmu_led_private_data_t *pdata;
	struct device_node *np = NULL;
	int rc = 0;

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	pdata = (struct pmu_led_private_data_t *)flash_ctrl->pdata;

	pdata->led_vcc.supply = "led-vcc";
	rc = devm_regulator_bulk_get(flash_ctrl->dev, 1, &(pdata->led_vcc));
	if (rc) {
		cam_err("%s failed to get regulator %d.", __func__, rc);
		return rc;
	}
	regulator_set_voltage(pdata->led_vcc.consumer, LED_VOLTAGE_4P5V, LED_VOLTAGE_4P5V);

	/* map pmic io register address */
	np = of_find_node_by_name(NULL, "pmic");
	if (NULL == np) {
		cam_err("%s failed to find pmic node.", __func__);
		return -1;
	}
	pdata->pmu_base = of_iomap(np, 0);
	if (NULL == pdata->pmu_base) {
		cam_err("%s failed to iomap pmu.", __func__);
		return -1;
	}

	return 0;
}

static int pmu_led_exit(struct hisi_flash_ctrl_t *flash_ctrl)
{
	struct pmu_led_private_data_t *pdata;

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	pdata = (struct pmu_led_private_data_t *)flash_ctrl->pdata;

	regulator_put(pdata->led_vcc.consumer);
	iounmap(pdata->pmu_base);

	return 0;
}

static int pmu_led_flash_mode(struct hisi_flash_ctrl_t *flash_ctrl,
	int data)
{
	struct pmu_led_private_data_t *pdata;

	cam_debug("%s data=%d.\n", __func__, data);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	pdata = (struct pmu_led_private_data_t *)flash_ctrl->pdata;

	pmu_led_write(LED_CTRL1, pdata->led_ctrl_flash[LED_CTRL_1]);
	pmu_led_write(LED_CTRL2, pdata->led_ctrl_flash[LED_CTRL_2]);
	pmu_led_write(LED_CTRL3, pdata->led_ctrl_flash[LED_CTRL_3]);

	/* set LED Flash current value */
	if (data < pdata->flash_led_num) {
		cam_debug("%s flash_led=0x%x.", __func__,
			pdata->flash_led[data]);
		pmu_led_write(LED_CTRL4, (pdata->flash_led[data] & 0x0f));
	} else {
		cam_warn("%s data(%d) > flash_led_num(%d).", __func__,
			data, pdata->flash_led_num);
		pmu_led_write(LED_CTRL4, (pdata->flash_led[pdata->flash_led_num-1] & 0x0f));
	}

	pmu_led_write(LED_CTRL5, pdata->led_ctrl_flash[LED_CTRL_5]);
	if (flash_ctrl->flash_mask_enable) {
		pmu_led_write(LED_CTRL6, (pdata->led_ctrl_flash[LED_CTRL_6] & 0xf7));
	} else {
		pmu_led_write(LED_CTRL6, (pdata->led_ctrl_flash[LED_CTRL_6] | 0x8));
	}

	pmu_led_write(LED_CTRL7, pdata->led_ctrl_flash[LED_CTRL_7]);

	pmu_led_write(LED_CTRL2, LED_FLASH_ENABLE);

	return 0;
}

static int pmu_led_torch_mode(struct hisi_flash_ctrl_t *flash_ctrl,
	int data)
{
	struct pmu_led_private_data_t *pdata;

	cam_debug("%s data=%d.\n", __func__, data);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	pdata = (struct pmu_led_private_data_t *)flash_ctrl->pdata;

	pmu_led_write(LED_CTRL1, pdata->led_ctrl_torch[LED_CTRL_1]);
	pmu_led_write(LED_CTRL2, pdata->led_ctrl_torch[LED_CTRL_2]);
	pmu_led_write(LED_CTRL3, pdata->led_ctrl_torch[LED_CTRL_3]);

	/* set LED Torch current value */
	if (data < pdata->torch_led_num) {
		cam_debug("%s torch_led=0x%x.", __func__,
			pdata->torch_led[data]);
		pmu_led_write(LED_CTRL3, ((pdata->torch_led[data] & 0x07)
				| (pdata->led_ctrl_torch[LED_CTRL_3] & 0x70)));
	} else {
		cam_warn("%s data(%d) > torch_led_num(%d).", __func__,
			data, pdata->torch_led_num);
		pmu_led_write(LED_CTRL3, ((pdata->torch_led[pdata->torch_led_num-1] & 0x07)
				| (pdata->led_ctrl_torch[LED_CTRL_3] & 0x70)));
	}
	pmu_led_write(LED_CTRL4, pdata->led_ctrl_torch[LED_CTRL_4]);
	pmu_led_write(LED_CTRL5, pdata->led_ctrl_torch[LED_CTRL_5]);
	pmu_led_write(LED_CTRL6, pdata->led_ctrl_torch[LED_CTRL_6]);
	pmu_led_write(LED_CTRL7, pdata->led_ctrl_torch[LED_CTRL_7]);

	pmu_led_write(LED_CTRL2, LED_TORCH_ENABLE);

	return 0;
}

static int pmu_led_on(struct hisi_flash_ctrl_t *flash_ctrl, void *data)
{
	struct pmu_led_private_data_t *pdata;
	struct flash_cfg_data *cdata = (struct flash_cfg_data *)data;
	int rc=-1;

	if ((NULL == flash_ctrl) || (NULL == cdata)) {
		cam_err("%s flash_ctrl or cdata is NULL.", __func__);
		return -1;
	}

	cam_debug("%s mode=%d, level=%d.\n", __func__, cdata->mode, cdata->data);

	mutex_lock(flash_ctrl->hisi_flash_mutex);
	pdata = (struct pmu_led_private_data_t *)flash_ctrl->pdata;

	if (STANDBY_MODE == flash_ctrl->state.mode) {
		rc = regulator_bulk_enable(1, &pdata->led_vcc);
		if (rc) {
			cam_err("failed to enable regulators %d\n", rc);
			return rc;
		}
	} else {
		cam_notice("%s flash led has been power on.", __func__);
	}

	if (FLASH_MODE == cdata->mode) {
		rc = pmu_led_flash_mode(flash_ctrl, cdata->data);
	} else {
		rc = pmu_led_torch_mode(flash_ctrl, cdata->data);
	}
	flash_ctrl->state.mode = cdata->mode;
	flash_ctrl->state.data = cdata->data;
	mutex_unlock(flash_ctrl->hisi_flash_mutex);

	return rc;
}

static int pmu_led_off(struct hisi_flash_ctrl_t *flash_ctrl)
{
	struct pmu_led_private_data_t *pdata;
	int rc=-1;

	cam_debug("%s ernter.\n", __func__);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	if (STANDBY_MODE == flash_ctrl->state.mode) {
		cam_notice("%s flash led has been powered off.", __func__);
		return 0;
	}

	mutex_lock(flash_ctrl->hisi_flash_mutex);
	pdata = (struct pmu_led_private_data_t *)flash_ctrl->pdata;
	flash_ctrl->state.mode = STANDBY_MODE;
	flash_ctrl->state.data = 0;
	pmu_led_write(LED_CTRL2, 0);
	rc = regulator_bulk_disable(1, &pdata->led_vcc);
	if (rc) {
		cam_err("failed to enable regulators %d\n", rc);
		return rc;
	}
	mutex_unlock(flash_ctrl->hisi_flash_mutex);

	return 0;
}

static int pmu_led_match(struct hisi_flash_ctrl_t *flash_ctrl)
{
	cam_debug("%s ernter.\n", __func__);
	return 0;
}

static int pmu_led_get_dt_data(struct hisi_flash_ctrl_t *flash_ctrl)
{
	struct pmu_led_private_data_t *pdata;
	struct device_node *of_node;
	int i;
	int rc = -1;

	cam_debug("%s enter.\n", __func__);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return rc;
	}

	pdata = (struct pmu_led_private_data_t *)flash_ctrl->pdata;
	of_node = flash_ctrl->dev->of_node;

	rc = of_property_read_u32(of_node, "hisi,flash_led_num",
		&pdata->flash_led_num);
	cam_debug("%s hisi,flash_led_num %d, rc %d\n", __func__,
		pdata->flash_led_num, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return rc;
	}

	rc = of_property_read_u32(of_node, "hisi,torch_led_num",
		&pdata->torch_led_num);
	cam_debug("%s hisi,torch_led_num %d, rc %d\n", __func__,
		pdata->torch_led_num, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return rc;
	}

	rc = of_property_read_u32_array(of_node, "hisi,flash_led",
		pdata->flash_led, pdata->flash_led_num);
	if (rc < 0) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		return rc;
	} else {
		for (i=0; i< pdata->flash_led_num; i++) {
			cam_debug("%s flash_led[%d]=0x%x.\n", __func__, i,
				pdata->flash_led[i]);
		}
	}

	rc = of_property_read_u32_array(of_node, "hisi,torch_led",
		pdata->torch_led, pdata->torch_led_num);
	if (rc < 0) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		return rc;
	} else {
		for (i=0; i< pdata->torch_led_num; i++) {
			cam_debug("%s torch_led[%d]=0x%x.\n", __func__, i,
				pdata->torch_led[i]);
		}
	}

	rc = of_property_read_u32_array(of_node, "hisi,led_ctrl_flash",
		pdata->led_ctrl_flash, LED_CTRL_MAX);
	if (rc < 0) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		return rc;
	} else {
		for (i=0; i< LED_CTRL_MAX; i++) {
			cam_debug("%s led_ctrl_flash[%d]=0x%x.\n", __func__, i,
				pdata->led_ctrl_flash[i]);
		}
	}

	rc = of_property_read_u32_array(of_node, "hisi,led_ctrl_torch",
		pdata->led_ctrl_torch, LED_CTRL_MAX);
	if (rc < 0) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		return rc;
	} else {
		for (i=0; i< LED_CTRL_MAX; i++) {
			cam_debug("%s led_ctrl_torch[%d]=0x%x.\n", __func__, i,
				pdata->led_ctrl_torch[i]);
		}
	}

	return rc;
}

static ssize_t pmu_led_lightness_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
        int rc=0;

        snprintf(buf, MAX_ATTRIBUTE_BUFFER_SIZE, "mode=%d, data=%d.\n",
		pmu_led_ctrl.state.mode, pmu_led_ctrl.state.mode);
        rc = strlen(buf)+1;
        return rc;
}


static int pmu_led_param_check(char *buf, unsigned long *param,
	int num_of_par)
{
	char *token;
	int base, cnt;

	token = strsep(&buf, " ");

	for (cnt = 0; cnt < num_of_par; cnt++)
	{
		if (token != NULL)
		{
			if ((token[1] == 'x') || (token[1] == 'X')) {
				base = 16;
			} else {
				base = 10;
			}

			if (strict_strtoul(token, base, &param[cnt]) != 0) {
				return -EINVAL;
			}

			token = strsep(&buf, " ");
		}
		else
		{
			return -EINVAL;
		}
	}
	return 0;
}

static ssize_t pmu_led_lightness_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct flash_cfg_data cdata = {0};
	unsigned long param[2]={0};
	int rc=0;

	rc = pmu_led_param_check((char *)buf, param, 2);
	if (rc < 0) {
		cam_err("%s failed to check param.", __func__);
		return rc;
	}

	cdata.mode = (int)param[0];
	cdata.data = (int)param[1];

	if (cdata.mode == STANDBY_MODE) {
		rc = pmu_led_off(&pmu_led_ctrl);
		if (rc < 0) {
			cam_err("%s pmu_led flash off error.", __func__);
			return rc;
		}
	} else {
		rc = pmu_led_on(&pmu_led_ctrl, &cdata);
		if (rc < 0) {
			cam_err("%s pmu_led flash on error.", __func__);
			return rc;
		}
	}

	return count;
}

static ssize_t pmu_led_flash_mask_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
        int rc=0;

        snprintf(buf, MAX_ATTRIBUTE_BUFFER_SIZE, "flash_mask_disabled=%d.\n",
		pmu_led_ctrl.flash_mask_enable);
        rc = strlen(buf)+1;
        return rc;
}

static ssize_t pmu_led_flash_mask_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	if ('0' == buf[0]) {
		pmu_led_ctrl.flash_mask_enable = false;
	} else {
		pmu_led_ctrl.flash_mask_enable = true;
	}
	cam_debug("%s flash_mask_enable=%d.", __func__,
			pmu_led_ctrl.flash_mask_enable);
	return count;
}

static void pmu_torch_brightness_set(struct led_classdev *cdev,
	enum led_brightness brightness)
{
	struct flash_cfg_data cdata;
	int rc;

	if (STANDBY_MODE == (int)brightness) {
		rc = pmu_led_off(&pmu_led_ctrl);
		if (rc < 0) {
			cam_err("%s pmu_led off error.", __func__);
			return;
		}
	} else {
		cdata.mode = TORCH_MODE;
		cdata.data = brightness-1;
		rc = pmu_led_on(&pmu_led_ctrl, &cdata);
		if (rc < 0) {
			cam_err("%s pmu_led on error.", __func__);
			return;
		}
	}
}

static struct device_attribute pmu_led_lightness =
    __ATTR(lightness, 0664, pmu_led_lightness_show, pmu_led_lightness_store);

static struct device_attribute pmu_led_flash_mask =
    __ATTR(flash_mask, 0664, pmu_led_flash_mask_show, pmu_led_flash_mask_store);

static int pmu_led_register_attribute(struct hisi_flash_ctrl_t *flash_ctrl,
	struct device *dev)
{
	int rc = 0;

	if ((NULL == flash_ctrl) || (NULL == dev)) {
		cam_err("%s flash_ctrl or dev is NULL.", __func__);
		return -1;
	}

	flash_ctrl->cdev_torch.name = "torch";
	flash_ctrl->cdev_torch.max_brightness
		= ((struct pmu_led_private_data_t *)(flash_ctrl->pdata))->torch_led_num;
	flash_ctrl->cdev_torch.brightness_set = pmu_torch_brightness_set;
	rc = led_classdev_register((struct device *)dev, &flash_ctrl->cdev_torch);
	if (rc < 0) {
		cam_err("%s failed to register torch classdev.", __func__);
		goto err_out;
	}

	rc = device_create_file(dev, &pmu_led_lightness);
	if (rc < 0) {
		cam_err("%s failed to creat lightness attribute.", __func__);
		goto err_create_lightness_file;
	}

	rc = device_create_file(dev, &pmu_led_flash_mask);
	if (rc < 0) {
		cam_err("%s failed to creat flash_mask attribute.", __func__);
		goto err_create_flash_mask_file;
	}

	return 0;

err_create_flash_mask_file:
	device_remove_file(dev, &pmu_led_lightness);
err_create_lightness_file:
	led_classdev_unregister(&flash_ctrl->cdev_torch);
err_out:

	return rc;
}

static const struct of_device_id pmu_led_dt_match[] = {
	{.compatible = "hisi,pmu_led", .data = &pmu_led_ctrl},
	{}
};
MODULE_DEVICE_TABLE(of, pmu_led_dt_match);

static struct platform_driver pmu_led_platform_driver = {
	.driver = {
		.name = "pmu_led",
		.owner = THIS_MODULE,
		.of_match_table = pmu_led_dt_match,
	},
};

static int32_t pmu_led_platform_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;

	match = of_match_device(pmu_led_dt_match, &pdev->dev);
	if(!match) {
		cam_err("pmu led match device failed");
		return -1;
	}
	cam_debug("%s compatible=%s.\n", __func__, match->compatible);
	return hisi_flash_platform_probe(pdev, (void*)match->data);
}

static int __init pmu_led_module_init(void)
{
	int rc = 0;
	cam_debug("%s:%d\n", __func__, __LINE__);

	rc = platform_driver_probe(&pmu_led_platform_driver,
		pmu_led_platform_probe);
	if (rc < 0) {
		cam_err("%s platform_driver_probe error(%d).\n", __func__, rc);
	}
	return rc;
}

static void __exit pmu_led_module_exit(void)
{
	pmu_led_ctrl.func_tbl->flash_exit(&pmu_led_ctrl);
	platform_driver_unregister(&pmu_led_platform_driver);
}

static struct hisi_flash_fn_t pmu_led_func_tbl = {
	.flash_config = hisi_flash_config,
	.flash_init = pmu_led_init,
	.flash_exit = pmu_led_exit,
	.flash_on = pmu_led_on,
	.flash_off = pmu_led_off,
	.flash_match = pmu_led_match,
	.flash_get_dt_data = pmu_led_get_dt_data,
	.flash_register_attribute = pmu_led_register_attribute,
};

static struct hisi_flash_ctrl_t pmu_led_ctrl = {
	.func_tbl = &pmu_led_func_tbl,
	.hisi_flash_mutex = &flash_mut_pmu_led,
	.pdata = (void*)&pmu_led_pdata,
	.flash_mask_enable = true,
	.state = {
		.mode = STANDBY_MODE,
	},
};

module_init(pmu_led_module_init);
module_exit(pmu_led_module_exit);
MODULE_DESCRIPTION("PMU_LED FLASH");
MODULE_LICENSE("GPL v2");
