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

#include "hw_flash.h"
/* TPS61310 Registers define */
#define REGISTER0		0x00
#define REGISTER1		0x01
#define REGISTER2		0x02
#define REGISTER3		0x03
#define REGISTER4		0x04
#define REGISTER5		0x05
#define REGISTER6		0x06
#define REGISTER7		0x07

#define FLASH_LED13_MAX	17
#define FLASH_LED2_MAX		33
#define TORCH_LED13_MAX	8
#define TORCH_LED2_MAX		8

#define FLASH_MODE_CTRL	0x80
#define TORCH_MODE_CTRL	0x40
#define FLASH_SFT		0x02
#define SHUTDOWN_MODE		0x3f

#define LED123_ENABLE 		0x7
#define LED13_ENABLE		0x5
#define LED2_ENABLE		0x2
#define LED123_DISABLE		0xf8
#define ILIM_1750mA		0x10
#define TX_MAXK_ENABLE		0x01
#define TX_MAXK_DISABLE	0xfe
#define MODE_CTRL_SHUTDONW	0x3f

extern struct dsm_client *client_flash;

/* Internal data struct define */
typedef enum {
	RESET=0,
	STROBE0,
	STROBE1,
	MAX_PIN,
}tps61310_pin_type;

struct hw_tps61310_private_data_t {
	unsigned int flash_led13[FLASH_LED13_MAX];
	unsigned int flash_led2[FLASH_LED2_MAX];
	unsigned int torch_led13[TORCH_LED13_MAX];
	unsigned int torch_led2[TORCH_LED2_MAX];
	unsigned int flash_led13_num;
	unsigned int flash_led2_num;
	unsigned int torch_led13_num;
	unsigned int torch_led2_num;

	/* flash control pin */
	unsigned int pin[MAX_PIN];

	unsigned int chipid;
};

/* Internal varible define */
static struct hw_tps61310_private_data_t hw_tps61310_pdata;
static struct hw_flash_ctrl_t hw_tps61310_ctrl;
static struct i2c_driver hw_tps61310_i2c_driver;

DEFINE_HISI_FLASH_MUTEX(tps61310);

/* Function define */
static int hw_tps61310_set_strobe0(struct hw_flash_ctrl_t *flash_ctrl,
	unsigned int state)
{
	struct hw_tps61310_private_data_t *pdata;

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	pdata = (struct hw_tps61310_private_data_t *)flash_ctrl->pdata;

	cam_debug("%s strobe0=%d, state=%d.", __func__,
		pdata->pin[STROBE0], state);
	gpio_direction_output(pdata->pin[STROBE0], state);
	return 0;
}

static int hw_tps61310_set_strobe1(struct hw_flash_ctrl_t *flash_ctrl,
	unsigned int state)
{
	struct hw_tps61310_private_data_t *pdata;

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	pdata = (struct hw_tps61310_private_data_t *)flash_ctrl->pdata;

	cam_debug("%s strobe1=%d, state=%d.", __func__,
		pdata->pin[STROBE1], state);
	gpio_direction_output(pdata->pin[STROBE1], state);
	return 0;
}

static int hw_tps61310_set_reset(struct hw_flash_ctrl_t *flash_ctrl,
	unsigned int state)
{
	struct hw_tps61310_private_data_t *pdata;

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	pdata = (struct hw_tps61310_private_data_t *)flash_ctrl->pdata;

	cam_debug("%s reset=%d, state=%d.", __func__,
		pdata->pin[RESET], state);
	gpio_direction_output(pdata->pin[RESET], state);
	return 0;
}

static int hw_tps61310_init(struct hw_flash_ctrl_t *flash_ctrl)
{
	struct hw_tps61310_private_data_t *pdata;
	int rc = -1;

	cam_debug("%s ernter.\n", __func__);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	pdata = (struct hw_tps61310_private_data_t *)flash_ctrl->pdata;

	flash_ctrl->pctrl = devm_pinctrl_get_select(flash_ctrl->dev,
						PINCTRL_STATE_DEFAULT);
	if (NULL == flash_ctrl->pctrl) {
		cam_err("%s failed to set pin.", __func__);
		return -EIO;
	}

	rc = gpio_request(pdata->pin[RESET], "flash-reset");
	if (rc < 0) {
		cam_err("%s failed to request reset pin.", __func__);
		return -EIO;
	}

	rc = gpio_request(pdata->pin[STROBE0], "flash-strobe0");
	if (rc < 0) {
		cam_err("%s failed to request strobe0 pin.", __func__);
		goto err1;
	}

	rc = gpio_request(pdata->pin[STROBE1], "flash-strobe1");
	if (rc < 0) {
		cam_err("%s failed to request strobe1 pin.", __func__);
		goto err2;
	}

	return 0;

err2:
	gpio_free(pdata->pin[STROBE0]);
err1:
	gpio_free(pdata->pin[RESET]);

	return -EIO;
}

static int hw_tps61310_exit(struct hw_flash_ctrl_t *flash_ctrl)
{
	struct hw_tps61310_private_data_t *pdata;

	cam_debug("%s ernter.\n", __func__);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	pdata = (struct hw_tps61310_private_data_t *)flash_ctrl->pdata;

	flash_ctrl->func_tbl->flash_off(flash_ctrl);

	gpio_free(pdata->pin[STROBE0]);
	gpio_free(pdata->pin[STROBE1]);
	gpio_free(pdata->pin[RESET]);

	flash_ctrl->pctrl = devm_pinctrl_get_select(flash_ctrl->dev,
						PINCTRL_STATE_IDLE);

	return 0;
}

static int hw_tps61310_led_enable(struct hw_flash_ctrl_t *flash_ctrl,
	struct hw_flash_cfg_data *cdata)
{
	struct hw_flash_i2c_client *i2c_client;
	struct hw_flash_i2c_fn_t *i2c_func;
	unsigned char val;

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	i2c_client = flash_ctrl->flash_i2c_client;
	i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;

	hw_tps61310_set_strobe0(flash_ctrl, LOW);
	hw_tps61310_set_strobe1(flash_ctrl, HIGH);

	hw_tps61310_set_reset(flash_ctrl, HIGH);

	if (flash_ctrl->flash_mask_enable) {
		i2c_func->i2c_read(i2c_client, REGISTER3, &val);
		val = val | TX_MAXK_ENABLE;
		i2c_func->i2c_write(i2c_client, REGISTER3, val);
		i2c_func->i2c_read(i2c_client, REGISTER3, &val);
	} else {
		i2c_func->i2c_read(i2c_client, REGISTER3, &val);
		val = val & TX_MAXK_DISABLE;
		i2c_func->i2c_write(i2c_client, REGISTER3, val);
		i2c_func->i2c_read(i2c_client, REGISTER3, &val);
	}

	/* set max current to 1750mA */
	i2c_func->i2c_read(i2c_client, REGISTER4, &val);
	val = val | ILIM_1750mA;
	i2c_func->i2c_write(i2c_client, REGISTER4, val);

	/* enable LED1,2,3 */
	i2c_func->i2c_read(i2c_client, REGISTER5, &val);
	if (TORCH_LEFT_MODE == cdata->mode) {
		val = (val & LED123_DISABLE) | LED13_ENABLE;
	} else if (TORCH_RIGHT_MODE == cdata->mode) {
		val = (val & LED123_DISABLE) | LED2_ENABLE;
	} else {
		val = (val & LED123_DISABLE) | LED123_ENABLE;
	}
	i2c_func->i2c_write(i2c_client, REGISTER5, val);
	i2c_func->i2c_read(i2c_client, REGISTER5, &val);

      //Add dmd log:  flash open/short  when D4 = 1
      i2c_func->i2c_read(i2c_client, REGISTER3, &val);//Apple
      val = val & 0x10;
       if(val == 0x10)
	{
	    if(!dsm_client_ocuppy(client_flash)){
              dsm_client_record(client_flash, "flash open or short\n");
              dsm_client_record(client_flash, "val = 0x%x\n", val);
              dsm_client_notify(client_flash, DSM_FLASH_OPEN_SHOTR_ERROR_NO);
              cam_info("[I/DSM] %s dsm_client_notify", client_flash->client_name);
          }
      }

      //Add dmd log:  flash hot die  when D6D5 = 10
      i2c_func->i2c_read(i2c_client, REGISTER4, &val);//Apple
      val = val & 0x60;
      if(val == 0x40)
	{
          if(!dsm_client_ocuppy(client_flash)){
              dsm_client_record(client_flash, "flash hot die\n");
              dsm_client_record(client_flash, "val = 0x%x\n", val);
              dsm_client_notify(client_flash, DSM_FLASH_HOT_DIE_ERROR_NO);
	       cam_info("[I/DSM] %s dsm_client_notify", client_flash->client_name);
          }
      }
	return 0;
}

static int hw_tps61310_flash_mode(struct hw_flash_ctrl_t *flash_ctrl,
	int data)
{
	struct hw_flash_i2c_client *i2c_client;
	struct hw_flash_i2c_fn_t *i2c_func;
	struct hw_tps61310_private_data_t *pdata;
	unsigned char val;

	cam_info("%s data=%d.\n", __func__, data);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	i2c_client = flash_ctrl->flash_i2c_client;
	i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;
	pdata = flash_ctrl->pdata;

	/* set LED1/2/3 Flash current value */
	if (data < pdata->flash_led2_num) {
		cam_debug("%s flash_led2=0x%x.", __func__, pdata->flash_led2[data]);
		i2c_func->i2c_write(i2c_client, REGISTER1,
			pdata->flash_led2[data] | FLASH_MODE_CTRL);
	} else {
		cam_warn("%s data(%d) > flash_led2_num(%d).", __func__,
			data, pdata->flash_led2_num);
		i2c_func->i2c_write(i2c_client, REGISTER1,
			pdata->flash_led2[pdata->flash_led2_num-1] | FLASH_MODE_CTRL);
	}

	if (data < pdata->flash_led13_num) {
		i2c_func->i2c_write(i2c_client, REGISTER2,
			pdata->flash_led13[data] | FLASH_MODE_CTRL);

	} else {
		cam_warn("%s data(%d) > flash_led13_num(%d).", __func__,
			data, pdata->flash_led13_num);
		i2c_func->i2c_write(i2c_client, REGISTER2,
			pdata->flash_led13[pdata->flash_led13_num-1] | FLASH_MODE_CTRL);
	}

	/* set start flash timer bit */
	i2c_func->i2c_read(i2c_client, REGISTER3, &val);
	i2c_func->i2c_write(i2c_client, REGISTER3, val | FLASH_SFT);

	/* start flash mode */
	hw_tps61310_set_strobe1(flash_ctrl, LOW);
	hw_tps61310_set_strobe0(flash_ctrl, HIGH);

	return 0;
}

static int hw_tps61310_torch_mode(struct hw_flash_ctrl_t *flash_ctrl,
	int data)
{
	struct hw_flash_i2c_client *i2c_client;
	struct hw_flash_i2c_fn_t *i2c_func;
	struct hw_tps61310_private_data_t *pdata;
	unsigned char val;

	cam_info("%s data=%d.\n", __func__, data);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	i2c_client = flash_ctrl->flash_i2c_client;
	i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;
	pdata = (struct hw_tps61310_private_data_t *)flash_ctrl->pdata;

	/*******************************************************
	 * TPS61310 REGISTER0[5:3] control LED1/3 tourch current,
	 * TPS61310 REGISTER0[2:0] control LED2 tourch current,
	 *******************************************************/
	if ((data < pdata->torch_led13_num) && (data < pdata->torch_led2_num)) {
		val = (((pdata->torch_led13[data] & 0x7) << 3)
			| (pdata->torch_led2[data] & 0x7));
		cam_debug("%s torch_led13=0x%x, torch_led2=0x%x.", __func__,
			pdata->torch_led13[data], pdata->torch_led2[data]);
	} else {
		cam_warn("%s data(%d) > torch_led13_num(%d) or torch_led2_num(%d)",
			__func__, data, pdata->torch_led13_num, pdata->torch_led2_num);
		val = (((pdata->torch_led13[pdata->torch_led13_num-1] & 0x7) << 3)
			| (pdata->torch_led2[pdata->torch_led2_num-1] & 0x7));
	}

	i2c_func->i2c_write(i2c_client, REGISTER0, val);

	i2c_func->i2c_read(i2c_client, REGISTER1, &val);
	i2c_func->i2c_write(i2c_client, REGISTER1, (val & MODE_CTRL_SHUTDONW) | TORCH_MODE_CTRL);
	i2c_func->i2c_read(i2c_client, REGISTER2, &val);
	i2c_func->i2c_write(i2c_client, REGISTER2, (val & MODE_CTRL_SHUTDONW) | TORCH_MODE_CTRL);

	/* start tourch mode */
	hw_tps61310_set_strobe1(flash_ctrl, HIGH);
	hw_tps61310_set_strobe0(flash_ctrl, HIGH);
	return 0;
}

static int hw_tps61310_on(struct hw_flash_ctrl_t *flash_ctrl, void *data)
{
	struct hw_flash_cfg_data *cdata = (struct hw_flash_cfg_data *)data;
	int rc=-1;

	if ((NULL == flash_ctrl) || (NULL == cdata)) {
		cam_err("%s flash_ctrl or cdata is NULL.", __func__);
		return -1;
	}

	cam_debug("%s mode=%d, level=%d.\n", __func__, cdata->mode, cdata->data);

	mutex_lock(flash_ctrl->hw_flash_mutex);
	rc = hw_tps61310_led_enable(flash_ctrl, cdata);
	if (rc < 0) {
		cam_err("%s failed to enable tps61310 led.", __func__);
		mutex_unlock(flash_ctrl->hw_flash_mutex);
		return rc;
	}

	if (FLASH_MODE == cdata->mode) {
		rc = hw_tps61310_flash_mode(flash_ctrl, cdata->data);
	} else {
		rc = hw_tps61310_torch_mode(flash_ctrl, cdata->data);
	}
	flash_ctrl->state.mode = cdata->mode;
	flash_ctrl->state.data = cdata->data;
	mutex_unlock(flash_ctrl->hw_flash_mutex);

	return rc;
}

static int hw_tps61310_off(struct hw_flash_ctrl_t *flash_ctrl)
{
	struct hw_flash_i2c_client *i2c_client;
	struct hw_flash_i2c_fn_t *i2c_func;
	struct hw_tps61310_private_data_t *pdata;
	unsigned int state;
	unsigned char val;

	cam_debug("%s ernter.\n", __func__);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	if (STANDBY_MODE == flash_ctrl->state.mode) {
		cam_notice("%s flash led has been powered off.", __func__);
		return 0;
	}

	mutex_lock(flash_ctrl->hw_flash_mutex);
	flash_ctrl->state.mode = STANDBY_MODE;
	flash_ctrl->state.data = 0;
	i2c_client = flash_ctrl->flash_i2c_client;
	i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;
	pdata = (struct hw_tps61310_private_data_t *)flash_ctrl->pdata;

	state = gpio_get_value(pdata->pin[RESET]);
	if (state != LOW) {
		/*************************************************
		 * set flash mode ctrl reg
		 * REGISTER1[7:6] & REGISTER2[7:6]:
		 * 00:shutdown mode
		 *************************************************/
		i2c_func->i2c_read(i2c_client, REGISTER1, &val);
		i2c_func->i2c_write(i2c_client, REGISTER1, val & SHUTDOWN_MODE);
		i2c_func->i2c_read(i2c_client, REGISTER2, &val);
		i2c_func->i2c_write(i2c_client, REGISTER2, val & SHUTDOWN_MODE);
	}

	hw_tps61310_set_strobe0(flash_ctrl, LOW);
	hw_tps61310_set_strobe1(flash_ctrl, HIGH);
	hw_tps61310_set_reset(flash_ctrl, LOW);
	mutex_unlock(flash_ctrl->hw_flash_mutex);

	return 0;
}

/* check flash is open or short */
static int tps61310_check(struct hw_flash_ctrl_t *flash_ctrl)
{
	unsigned char val;
	struct hw_flash_i2c_client *i2c_client;
	struct hw_flash_i2c_fn_t *i2c_func;
	int status = -1;

	i2c_client = flash_ctrl->flash_i2c_client;
	if(i2c_client == NULL) {
		cam_err("%s: i2c client is NULL.", __func__);
		return FLASH_LED_ERROR;
	}

	i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;
	if(i2c_func == NULL) {
		cam_err("%s: i2c function is NULL.", __func__);
		return FLASH_LED_ERROR;
	}

	hw_tps61310_set_reset(flash_ctrl, HIGH);
	i2c_func->i2c_read(i2c_client, REGISTER3, &val);
	if(val & 0x10) {
		status = FLASH_LED_FAULT;
	} else {
		status = FLASH_LED_NORMAL;
	}
	hw_tps61310_set_reset(flash_ctrl, LOW);

	return status;
}

static int hw_tps61310_match(struct hw_flash_ctrl_t *flash_ctrl)
{
	struct hw_flash_i2c_client *i2c_client;
	struct hw_flash_i2c_fn_t *i2c_func;
	struct hw_tps61310_private_data_t *pdata;
	unsigned char id;

	cam_debug("%s ernter.\n", __func__);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	i2c_client = flash_ctrl->flash_i2c_client;
	i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;
	pdata = (struct hw_tps61310_private_data_t *)flash_ctrl->pdata;

	hw_tps61310_set_reset(flash_ctrl, HIGH);

	i2c_func->i2c_read(i2c_client, REGISTER7, &id);
	cam_info("%s id=0x%x.\n", __func__, id);
	if ((id&0x7) != pdata->chipid) {
		cam_err("%s match error, id&0x7(0x%x) != 0x%x.",
			__func__, (id&0x7), pdata->chipid);
		return -1;
	}

	hw_tps61310_set_reset(flash_ctrl, LOW);

	return 0;
}

static int hw_tps61310_get_dt_data(struct hw_flash_ctrl_t *flash_ctrl)
{
	struct hw_tps61310_private_data_t *pdata;
	struct device_node *of_node;
	int i;
	int rc = -1;

	cam_debug("%s enter.\n", __func__);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return rc;
	}

	pdata = (struct hw_tps61310_private_data_t *)flash_ctrl->pdata;
	of_node = flash_ctrl->dev->of_node;

	rc = of_property_read_u32_array(of_node, "huawei,flash-pin",
		pdata->pin, MAX_PIN);
	if (rc < 0) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		return rc;
	} else {
		for (i=0; i<MAX_PIN; i++) {
			cam_debug("%s pin[%d]=%d.\n", __func__, i,
				pdata->pin[i]);
		}
	}

	rc = of_property_read_u32(of_node, "huawei,flash-chipid",
		&pdata->chipid);
	cam_info("%s hisi,chipid 0x%x, rc %d\n", __func__,
		pdata->chipid, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return rc;
	}

	rc = of_property_read_u32(of_node, "huawei,flash_led13_num",
		&pdata->flash_led13_num);
	cam_info("%s hisi,flash_led13_num %d, rc %d\n", __func__,
		pdata->flash_led13_num, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return rc;
	}

	rc = of_property_read_u32(of_node, "huawei,flash_led2_num",
		&pdata->flash_led2_num);
	cam_info("%s hisi,flash_led2_num %d, rc %d\n", __func__,
		pdata->flash_led2_num, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return rc;
	}

	rc = of_property_read_u32(of_node, "huawei,torch_led13_num",
		&pdata->torch_led13_num);
	cam_info("%s hisi,torch_led13_num %d, rc %d\n", __func__,
		pdata->torch_led13_num, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return rc;
	}

	rc = of_property_read_u32(of_node, "huawei,torch_led2_num",
		&pdata->torch_led2_num);
	cam_info("%s hisi,torch_led2_num %d, rc %d\n", __func__,
		pdata->torch_led2_num, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return rc;
	}

	rc = of_property_read_u32_array(of_node, "huawei,flash_led2",
		pdata->flash_led2, pdata->flash_led2_num);
	if (rc < 0) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		return rc;
	} else {
		for (i=0; i< pdata->flash_led2_num; i++) {
			cam_debug("%s flash_led2[%d]=%d.\n", __func__, i,
				pdata->flash_led2[i]);
		}
	}

	rc = of_property_read_u32_array(of_node, "huawei,flash_led13",
		pdata->flash_led13, pdata->flash_led13_num);
	if (rc < 0) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		return rc;
	} else {
		for (i=0; i< pdata->flash_led13_num; i++) {
			cam_debug("%s flash_led13[%d]=%d.\n", __func__, i,
				pdata->flash_led13[i]);
		}
	}

	rc = of_property_read_u32_array(of_node, "huawei,torch_led2",
		pdata->torch_led2, pdata->torch_led2_num);
	if (rc < 0) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		return rc;
	} else {
		for (i=0; i< pdata->torch_led2_num; i++) {
			cam_debug("%s torch_led2[%d]=%d.\n", __func__, i,
				pdata->torch_led2[i]);
		}
	}

	rc = of_property_read_u32_array(of_node, "huawei,torch_led13",
		pdata->torch_led13, pdata->torch_led13_num);
	if (rc < 0) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		return rc;
	} else {
		for (i=0; i< pdata->torch_led13_num; i++) {
			cam_debug("%s torch_led13[%d]=%d.\n", __func__, i,
				pdata->torch_led13[i]);
		}
	}

	return rc;
}

static ssize_t hw_tps61310_lightness_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
        int rc=0;

        snprintf(buf, MAX_ATTRIBUTE_BUFFER_SIZE, "mode=%d, data=%d.\n",
		hw_tps61310_ctrl.state.mode, hw_tps61310_ctrl.state.mode);
        rc = strlen(buf)+1;
        return rc;
}


static int hw_tps61310_param_check(char *buf, unsigned long *param,
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

static ssize_t hw_tps61310_lightness_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct hw_flash_cfg_data cdata = {0};
	unsigned long param[2]={0};
	int rc=0;

	rc = hw_tps61310_param_check((char *)buf, param, 2);
	if (rc < 0) {
		cam_err("%s failed to check param.", __func__);
		return rc;
	}

	cdata.mode = (int)param[0];
	cdata.data = (int)param[1];

	if (cdata.mode == STANDBY_MODE) {
		rc = hw_tps61310_off(&hw_tps61310_ctrl);
		if (rc < 0) {
			cam_err("%s tps61310 flash off error.", __func__);
			return rc;
		}
	} else {
		rc = hw_tps61310_on(&hw_tps61310_ctrl, &cdata);
		if (rc < 0) {
			cam_err("%s tps61310 flash on error.", __func__);
			return rc;
		}
	}

	return count;
}

static ssize_t hw_tps61310_flash_mask_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
        int rc=0;

        snprintf(buf, MAX_ATTRIBUTE_BUFFER_SIZE, "flash_mask_disabled=%d.\n",
		hw_tps61310_ctrl.flash_mask_enable);
        rc = strlen(buf)+1;
        return rc;
}

static ssize_t hw_tps61310_flash_mask_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	if ('0' == buf[0]) {
		hw_tps61310_ctrl.flash_mask_enable = false;
	} else {
		hw_tps61310_ctrl.flash_mask_enable = true;
	}
	cam_debug("%s flash_mask_enable=%d.", __func__,
			hw_tps61310_ctrl.flash_mask_enable);
	return count;
}

static void hw_tps61310_torch_brightness_set(struct led_classdev *cdev,
	enum led_brightness brightness)
{
	struct hw_flash_cfg_data cdata;
	int rc;
	unsigned int led_bright = brightness;

	if (STANDBY_MODE == led_bright) {
		rc = hw_tps61310_off(&hw_tps61310_ctrl);
		if (rc < 0) {
			cam_err("%s tps61310 off error.", __func__);
			return;
		}
	} else {
		/******************************************************
		  * brightness[9:8]: mode control bits.
		  * 0:TORCH MODE, 1:TORCH_LEFT_MODE,2:TORCH_RIGHT_MODE;
		  *brightness[7:0]: brightness level control bits.
		  ******************************************************/
		int max_level;
		max_level =  ((struct hw_tps61310_private_data_t *)(hw_tps61310_ctrl.pdata))->torch_led13_num;
		cdata.mode = ((brightness-1) / max_level) + TORCH_MODE;
		cdata.data =((brightness-1) % max_level);
		cam_info("%s brightness=0x%x, mode=%d, data=%d.", __func__, brightness, cdata.mode, cdata.data);
		rc = hw_tps61310_on(&hw_tps61310_ctrl, &cdata);
		if (rc < 0) {
			cam_err("%s tps61310 on error.", __func__);
			return;
		}
	}
}


static struct device_attribute hw_tps61310_lightness =
    __ATTR(lightness, 0664, hw_tps61310_lightness_show, hw_tps61310_lightness_store);

static struct device_attribute hw_tps61310_flash_mask =
    __ATTR(flash_mask, 0664, hw_tps61310_flash_mask_show, hw_tps61310_flash_mask_store);

static int hw_tps61310_register_attribute(struct hw_flash_ctrl_t *flash_ctrl, struct device *dev)
{
	int rc = 0;

	if ((NULL == flash_ctrl) || (NULL == dev)) {
		cam_err("%s flash_ctrl or dev is NULL.", __func__);
		return -1;
	}

	flash_ctrl->cdev_torch.name = "torch";
	flash_ctrl->cdev_torch.max_brightness
		= ((struct hw_tps61310_private_data_t *)(flash_ctrl->pdata))->torch_led13_num
			*(TORCH_RIGHT_MODE-TORCH_MODE+1);
	flash_ctrl->cdev_torch.brightness_set = hw_tps61310_torch_brightness_set;
	rc = led_classdev_register((struct device *)dev, &flash_ctrl->cdev_torch);
	if (rc < 0) {
		cam_err("%s failed to register torch classdev.", __func__);
		goto err_out;
	}

	rc = device_create_file(dev, &hw_tps61310_lightness);
	if (rc < 0) {
		cam_err("%s failed to creat lightness attribute.", __func__);
		goto err_create_lightness_file;
	}

	rc = device_create_file(dev, &hw_tps61310_flash_mask);
	if (rc < 0) {
		cam_err("%s failed to creat flash_mask attribute.", __func__);
		goto err_create_flash_mask_file;
	}

	return 0;

err_create_flash_mask_file:
	device_remove_file(dev, &hw_tps61310_lightness);
err_create_lightness_file:
	led_classdev_unregister(&flash_ctrl->cdev_torch);
err_out:
	return rc;
}

static int hw_tps61310_remove(struct i2c_client *client)
{
	cam_debug("%s enter.", __func__);

	hw_tps61310_ctrl.func_tbl->flash_exit(&hw_tps61310_ctrl);

	client->adapter = NULL;
	return 0;
}

static const struct i2c_device_id hw_tps61310_id[] = {
	{"hw_tps61310", (unsigned long)&hw_tps61310_ctrl},
	{}
};

static const struct of_device_id hw_tps61310_dt_match[] = {
	{.compatible = "huawei,hw_tps61310"},
	{}
};
MODULE_DEVICE_TABLE(of, hw_tps61310_dt_match);

static struct i2c_driver hw_tps61310_i2c_driver = {
	.probe	= hw_flash_i2c_probe,
	.remove = hw_tps61310_remove,
	.id_table	= hw_tps61310_id,
	.driver = {
		.name = "hw_tps61310",
		.of_match_table = hw_tps61310_dt_match,
	},
};

static int __init hw_tps61310_module_init(void)
{
	cam_debug("%s erter.\n", __func__);
	return i2c_add_driver(&hw_tps61310_i2c_driver);
}

static void __exit hw_tps61310_module_exit(void)
{
	cam_debug("%s enter.", __func__);
	i2c_del_driver(&hw_tps61310_i2c_driver);
	return;
}

static struct hw_flash_i2c_client hw_tps61310_i2c_client;

static struct hw_flash_fn_t hw_tps61310_func_tbl = {
	.flash_config = hw_flash_config,
	.flash_init = hw_tps61310_init,
	.flash_exit = hw_tps61310_exit,
	.flash_on = hw_tps61310_on,
	.flash_off = hw_tps61310_off,
	.flash_match = hw_tps61310_match,
	.flash_get_dt_data = hw_tps61310_get_dt_data,
	/* check flash open or short */
	.flash_check = tps61310_check,
	.flash_register_attribute = hw_tps61310_register_attribute,
};

static struct hw_flash_ctrl_t hw_tps61310_ctrl = {
	.flash_i2c_client = &hw_tps61310_i2c_client,
	.func_tbl = &hw_tps61310_func_tbl,
	.hw_flash_mutex = &flash_mut_tps61310,
	.pdata = (void*)&hw_tps61310_pdata,
	.flash_mask_enable = true,
	.state = {
		.mode = STANDBY_MODE,
	},
};

module_init(hw_tps61310_module_init);
module_exit(hw_tps61310_module_exit);
MODULE_DESCRIPTION("TPS61310 FLASH");
MODULE_LICENSE("GPL v2");
