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

/* LM3642 Registers define */
#define REG_ENABLE			0x0a
#define REG_FLAGS			0x0b
#define REG_FLASH_FEATURES		0x08
#define REG_CURRENT_CONTROL		0x09
#define REG_IVFM			0x01
#define REG_TORCH_RAMP_TIME		0x06

#define MODE_STANDBY			0x00
#define MODE_INDICATOR			0x01
#define MODE_TORCH			0x02
#define MODE_FLASH			0x03
#define STROBE_PIN			0x20
#define TORCH_PIN			0x10
#define TX_PIN				0x40

#define FLASH_LED_MAX			16
#define TORCH_LED_MAX			8

/* Internal data struct define */
struct lm3642_private_data_t {
	unsigned char flash_led[FLASH_LED_MAX];
	unsigned char torch_led[TORCH_LED_MAX];
	unsigned int flash_led_num;
	unsigned int torch_led_num;

	/* flash control pin */
	unsigned int strobe;

	unsigned int chipid;
};

/* Internal varible define */
static struct lm3642_private_data_t lm3642_pdata;
static struct hisi_flash_ctrl_t lm3642_ctrl;
static struct i2c_driver lm3642_i2c_driver;

DEFINE_HISI_FLASH_MUTEX(lm3642);

/* Function define */
#if 0
static int lm3642_set_strobe(struct hisi_flash_ctrl_t *flash_ctrl,
	unsigned int state)
{
	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	cam_debug("%s strobe0=%d, state=%d.", __func__,
		flash_ctrl->flash_info.strobe0, state);
	gpio_direction_output(flash_ctrl->flash_info.strobe0, state);
	return 0;
}
#endif

static int lm3642_init(struct hisi_flash_ctrl_t *flash_ctrl)
{
	struct lm3642_private_data_t *pdata;
	int rc = 0;

	cam_debug("%s ernter.\n", __func__);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	pdata = (struct lm3642_private_data_t *)flash_ctrl->pdata;
#if 1
	flash_ctrl->pctrl = devm_pinctrl_get_select(flash_ctrl->dev,
						PINCTRL_STATE_DEFAULT);

	rc = gpio_request(pdata->strobe, "flash-strobe");
	if (rc < 0) {
		cam_err("%s failed to request strobe pin.", __func__);
		return -EIO;
	}
#endif
	return rc;
}

static int lm3642_exit(struct hisi_flash_ctrl_t *flash_ctrl)
{
	struct lm3642_private_data_t *pdata;

	cam_debug("%s ernter.\n", __func__);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	flash_ctrl->func_tbl->flash_off(flash_ctrl);

	pdata = (struct lm3642_private_data_t *)flash_ctrl->pdata;

	gpio_free(pdata->strobe);
	flash_ctrl->pctrl = devm_pinctrl_get_select(flash_ctrl->dev,
						PINCTRL_STATE_IDLE);

	return 0;
}

static int lm3642_flash_mode(struct hisi_flash_ctrl_t *flash_ctrl,
	int data)
{
	struct hisi_flash_i2c_client *i2c_client;
	struct hisi_flash_i2c_fn_t *i2c_func;
	struct lm3642_private_data_t *pdata;
	unsigned char val;

	cam_info("%s data=%d.\n", __func__, data);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	i2c_client = flash_ctrl->flash_i2c_client;
	i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;
	pdata = flash_ctrl->pdata;

	/* clear error flag,resume chip */
	i2c_func->i2c_read(i2c_client, REG_FLAGS, &val);
	i2c_func->i2c_read(i2c_client, REG_CURRENT_CONTROL, &val);

	/* set LED Flash current value */
	if (data < pdata->flash_led_num) {
		cam_debug("%s flash_led=0x%x.", __func__,
			pdata->flash_led[data]);
		/* REG_CURRENT_CONTROL[3:0] control flash current */
		val = ((val & 0xf0) | (pdata->flash_led[data] & 0x0f));

	} else {
		cam_warn("%s data(%d) > flash_led_num(%d).", __func__,
			data, pdata->flash_led_num);
		/* REG_CURRENT_CONTROL[3:0] control flash current */
		val = ((val & 0xf0) | (pdata->flash_led[pdata->flash_led_num-1] & 0x0f));
	}

	i2c_func->i2c_write(i2c_client, REG_CURRENT_CONTROL, val);
	if (flash_ctrl->flash_mask_enable) {
		i2c_func->i2c_write(i2c_client, REG_ENABLE, MODE_FLASH|TX_PIN);
	} else {
		i2c_func->i2c_write(i2c_client, REG_ENABLE, MODE_FLASH);
	}

	return 0;
}

static int lm3642_torch_mode(struct hisi_flash_ctrl_t *flash_ctrl,
	int data)
{
	struct hisi_flash_i2c_client *i2c_client;
	struct hisi_flash_i2c_fn_t *i2c_func;
	struct lm3642_private_data_t *pdata;
	unsigned char val;

	cam_info("%s data=%d.\n", __func__, data);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	i2c_client = flash_ctrl->flash_i2c_client;
	i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;
	pdata = (struct lm3642_private_data_t *)flash_ctrl->pdata;

	/* clear error flag,resume chip */
	i2c_func->i2c_read(i2c_client, REG_FLAGS, &val);
	i2c_func->i2c_read(i2c_client, REG_CURRENT_CONTROL, &val);

	/* set LED Flash current value */
	if (data < pdata->torch_led_num) {
		cam_debug("%s torch_led=0x%x.", __func__,
			pdata->torch_led[data]);
		/* REG_CURRENT_CONTROL[7:4] control torch current */
		val = ((val & 0x0f) | (pdata->torch_led[data] << 4));

	} else {
		cam_warn("%s data(%d) > torch_led_num(%d).", __func__,
			data, pdata->torch_led_num);
		/* REG_CURRENT_CONTROL[7:4] control torch current */
		val = ((val & 0x0f) | (pdata->torch_led[pdata->torch_led_num-1] << 4));
		return -1;
	}

	i2c_func->i2c_write(i2c_client, REG_CURRENT_CONTROL, val);
	i2c_func->i2c_write(i2c_client, REG_ENABLE, MODE_TORCH);

	return 0;
}

static int lm3642_on(struct hisi_flash_ctrl_t *flash_ctrl, void *data)
{
	struct flash_cfg_data *cdata = (struct flash_cfg_data *)data;
	int rc=-1;

	if ((NULL == flash_ctrl) || (NULL == cdata)) {
		cam_err("%s flash_ctrl or cdata is NULL.", __func__);
		return -1;
	}

	cam_debug("%s mode=%d, level=%d.\n", __func__, cdata->mode, cdata->data);

	mutex_lock(flash_ctrl->hisi_flash_mutex);
	if (FLASH_MODE == cdata->mode) {
		rc = lm3642_flash_mode(flash_ctrl, cdata->data);
	} else {
		rc = lm3642_torch_mode(flash_ctrl, cdata->data);
	}
	flash_ctrl->state.mode = cdata->mode;
	flash_ctrl->state.data = cdata->data;
	mutex_unlock(flash_ctrl->hisi_flash_mutex);

	return rc;
}

static int lm3642_off(struct hisi_flash_ctrl_t *flash_ctrl)
{
	struct hisi_flash_i2c_client *i2c_client;
	struct hisi_flash_i2c_fn_t *i2c_func;
	unsigned char val;

	cam_debug("%s ernter.\n", __func__);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	mutex_lock(flash_ctrl->hisi_flash_mutex);
	flash_ctrl->state.mode = STANDBY_MODE;
	flash_ctrl->state.data = 0;
	i2c_client = flash_ctrl->flash_i2c_client;
	i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;

	i2c_func->i2c_read(i2c_client, REG_FLAGS, &val);
	i2c_func->i2c_write(i2c_client, REG_ENABLE, MODE_STANDBY);
	mutex_unlock(flash_ctrl->hisi_flash_mutex);

	return 0;
}

static int lm3642_match(struct hisi_flash_ctrl_t *flash_ctrl)
{
	struct hisi_flash_i2c_client *i2c_client;
	struct hisi_flash_i2c_fn_t *i2c_func;
	struct lm3642_private_data_t *pdata;
	unsigned char id;

	cam_debug("%s ernter.\n", __func__);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	i2c_client = flash_ctrl->flash_i2c_client;
	i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;
	pdata = (struct lm3642_private_data_t *)flash_ctrl->pdata;

	i2c_func->i2c_read(i2c_client, REG_FLASH_FEATURES, &id);
	cam_info("%s id=0x%x.\n", __func__, id);
	if (id != pdata->chipid) {
		cam_err("%s match error, id(0x%x) != 0x%x.",
			__func__, (id&0x7), pdata->chipid);
		return -1;
	}
	i2c_func->i2c_write(i2c_client, REG_IVFM, 0x00);

	return 0;
}

static int lm3642_get_dt_data(struct hisi_flash_ctrl_t *flash_ctrl)
{
	struct lm3642_private_data_t *pdata;
	struct device_node *of_node;
	int i;
	int rc = -1;

	cam_debug("%s enter.\n", __func__);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return rc;
	}

	pdata = (struct lm3642_private_data_t *)flash_ctrl->pdata;
	of_node = flash_ctrl->dev->of_node;

	rc = of_property_read_u32(of_node, "hisi,flash-pin",
		&pdata->strobe);
	cam_info("%s hisi,flash-pin %d, rc %d\n", __func__,
		pdata->strobe, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return rc;
	}

	rc = of_property_read_u32(of_node, "hisi,flash-chipid",
		&pdata->chipid);
	cam_info("%s hisi,chipid 0x%x, rc %d\n", __func__,
		pdata->chipid, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return rc;
	}

	rc = of_property_read_u32(of_node, "hisi,flash_led_num",
		&pdata->flash_led_num);
	cam_info("%s hisi,flash_led_num %d, rc %d\n", __func__,
		pdata->flash_led_num, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return rc;
	}

	rc = of_property_read_u32(of_node, "hisi,torch_led_num",
		&pdata->torch_led_num);
	cam_info("%s hisi,torch_led_num %d, rc %d\n", __func__,
		pdata->torch_led_num, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return rc;
	}

	rc = of_property_read_u8_array(of_node, "hisi,flash_led",
		pdata->flash_led, pdata->flash_led_num);
	if (rc < 0) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		return rc;
	} else {
		for (i=0; i< pdata->flash_led_num; i++) {
			cam_debug("%s flash_led[%d]=%d.\n", __func__, i,
				pdata->flash_led[i]);
		}
	}

	rc = of_property_read_u8_array(of_node, "hisi,torch_led",
		pdata->torch_led, pdata->torch_led_num);
	if (rc < 0) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		return rc;
	} else {
		for (i=0; i< pdata->torch_led_num; i++) {
			cam_debug("%s torch_led[%d]=%d.\n", __func__, i,
				pdata->torch_led[i]);
		}
	}

	return rc;
}

static ssize_t lm3642_lightness_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
        int rc=0;

        snprintf(buf, MAX_ATTRIBUTE_BUFFER_SIZE, "mode=%d, data=%d.\n",
		lm3642_ctrl.state.mode, lm3642_ctrl.state.mode);
        rc = strlen(buf)+1;
        return rc;
}

static int lm3642_param_check(char *buf, unsigned long *param,
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

static ssize_t lm3642_lightness_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct flash_cfg_data cdata = {0};
	unsigned long param[2]={0};
	int rc=0;

	rc = lm3642_param_check((char *)buf, param, 2);
	if (rc < 0) {
		cam_err("%s failed to check param.", __func__);
		return rc;
	}

	cdata.mode = (int)param[0];
	cdata.data = (int)param[1];

	if (cdata.mode == STANDBY_MODE) {
		rc = lm3642_off(&lm3642_ctrl);
		if (rc < 0) {
			cam_err("%s lm3642 flash off error.", __func__);
			return rc;
		}
	} else {
		rc = lm3642_on(&lm3642_ctrl, &cdata);
		if (rc < 0) {
			cam_err("%s lm3642 flash on error.", __func__);
			return rc;
		}
	}

	return count;
}

static ssize_t lm3642_flash_mask_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
        int rc=0;

        snprintf(buf, MAX_ATTRIBUTE_BUFFER_SIZE, "flash_mask_disabled=%d.\n",
		lm3642_ctrl.flash_mask_enable);
        rc = strlen(buf)+1;
        return rc;
}

static ssize_t lm3642_flash_mask_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	if ('0' == buf[0]) {
		lm3642_ctrl.flash_mask_enable = false;
	} else {
		lm3642_ctrl.flash_mask_enable = true;
	}
	cam_debug("%s flash_mask_enable=%d.", __func__,
			lm3642_ctrl.flash_mask_enable);
	return count;
}

static void lm3642_torch_brightness_set(struct led_classdev *cdev,
	enum led_brightness brightness)
{
	struct flash_cfg_data cdata;
	int rc;

	if (STANDBY_MODE == (int)brightness) {
		rc = lm3642_off(&lm3642_ctrl);
		if (rc < 0) {
			cam_err("%s pmu_led off error.", __func__);
			return;
		}
	} else {
		cdata.mode = TORCH_MODE;
		cdata.data = brightness-1;
		rc = lm3642_on(&lm3642_ctrl, &cdata);
		if (rc < 0) {
			cam_err("%s pmu_led on error.", __func__);
			return;
		}
	}
}

static struct device_attribute lm3642_lightness =
    __ATTR(lightness, 0664, lm3642_lightness_show, lm3642_lightness_store);

static struct device_attribute lm3642_flash_mask =
    __ATTR(flash_mask, 0664, lm3642_flash_mask_show, lm3642_flash_mask_store);

static int lm3642_register_attribute(struct hisi_flash_ctrl_t *flash_ctrl, struct device *dev)
{
	int rc = 0;

	if ((NULL == flash_ctrl) || (NULL == dev)) {
		cam_err("%s flash_ctrl or dev is NULL.", __func__);
		return -1;
	}

	flash_ctrl->cdev_torch.name = "torch";
	flash_ctrl->cdev_torch.max_brightness
		= ((struct lm3642_private_data_t *)(flash_ctrl->pdata))->torch_led_num;
	flash_ctrl->cdev_torch.brightness_set = lm3642_torch_brightness_set;
	rc = led_classdev_register((struct device *)dev, &flash_ctrl->cdev_torch);
	if (rc < 0) {
		cam_err("%s failed to register torch classdev.", __func__);
		goto err_out;
	}

	rc = device_create_file(dev, &lm3642_lightness);
	if (rc < 0) {
		cam_err("%s failed to creat lightness attribute.", __func__);
		goto err_create_lightness_file;
	}

	rc = device_create_file(dev, &lm3642_flash_mask);
	if (rc < 0) {
		cam_err("%s failed to creat flash_mask attribute.", __func__);
		goto err_create_flash_mask_file;
	}
	return 0;
err_create_flash_mask_file:
	device_remove_file(dev, &lm3642_lightness);
err_create_lightness_file:
	led_classdev_unregister(&flash_ctrl->cdev_torch);
err_out:
	return rc;
}

static int lm3642_remove(struct i2c_client *client)
{
	cam_debug("%s enter.", __func__);

	lm3642_ctrl.func_tbl->flash_exit(&lm3642_ctrl);

	client->adapter = NULL;
	return 0;
}

static const struct i2c_device_id lm3642_id[] = {
	{"lm3642", (unsigned long)&lm3642_ctrl},
	{}
};

static const struct of_device_id lm3642_dt_match[] = {
	{.compatible = "hisi,lm3642"},
	{}
};
MODULE_DEVICE_TABLE(of, lm3642_dt_match);

static struct i2c_driver lm3642_i2c_driver = {
	.probe	= hisi_flash_i2c_probe,
	.remove = lm3642_remove,
	.id_table	= lm3642_id,
	.driver = {
		.name = "lm3642",
		.of_match_table = lm3642_dt_match,
	},
};

static int __init lm3642_module_init(void)
{
	cam_debug("%s erter.\n", __func__);
	return i2c_add_driver(&lm3642_i2c_driver);
}

static void __exit lm3642_module_exit(void)
{
	cam_debug("%s enter.", __func__);
	i2c_del_driver(&lm3642_i2c_driver);
	return;
}

static struct hisi_flash_i2c_client lm3642_i2c_client;

static struct hisi_flash_fn_t lm3642_func_tbl = {
	.flash_config = hisi_flash_config,
	.flash_init = lm3642_init,
	.flash_exit = lm3642_exit,
	.flash_on = lm3642_on,
	.flash_off = lm3642_off,
	.flash_match = lm3642_match,
	.flash_get_dt_data = lm3642_get_dt_data,
	.flash_register_attribute = lm3642_register_attribute,
};

static struct hisi_flash_ctrl_t lm3642_ctrl = {
	.flash_i2c_client = &lm3642_i2c_client,
	.func_tbl = &lm3642_func_tbl,
	.hisi_flash_mutex = &flash_mut_lm3642,
	.pdata = (void*)&lm3642_pdata,
	.flash_mask_enable = true,
	.state = {
		.mode = STANDBY_MODE,
	},
};

module_init(lm3642_module_init);
module_exit(lm3642_module_exit);
MODULE_DESCRIPTION("LM3642 FLASH");
MODULE_LICENSE("GPL v2");
