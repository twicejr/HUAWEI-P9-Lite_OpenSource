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
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/regulator/of_regulator.h>
#include <linux/regulator/consumer.h>
#include <linux/power/hisi_hi6521_charger_power.h>
#include <linux/bitops.h>

#define FLASH_LED_MAX			(16)
#define TORCH_LED_MAX			(8)
#define FLASH_TIMEOUT_MS        (600)

#define SCHG_BOOST_REGULATOR      "pvdd-classd"    /*"schg_boost3"*/
#define SCHG_FLASH_MODE_REGULATOR "flash-led" /*"schg_source1"*/
#define SCHG_TORCH_MODE_REGULATOR "torch-led" /*"schg_source2"*/

struct hw_scharger_private_data_t {
    unsigned int flash_led[FLASH_LED_MAX];
    unsigned int torch_led[TORCH_LED_MAX];
    unsigned int flash_led_num;
    unsigned int torch_led_num;
    struct regulator *flash_inter_ldo;
    struct regulator *flash_mode_ldo;
    struct regulator *torch_mode_ldo;
    unsigned int status;
};

/* Internal varible define */
static struct hw_scharger_private_data_t hw_scharger_pdata;
static struct hw_flash_ctrl_t hw_scharger_ctrl;

DEFINE_HISI_FLASH_MUTEX(scharger);

static int hw_scharger_init(struct hw_flash_ctrl_t *flash_ctrl)
{
    struct hw_scharger_private_data_t *pdata = (struct hw_scharger_private_data_t *)flash_ctrl->pdata;
    if (NULL == pdata) {
        cam_err("%s pdata is NULL", __func__);
        return -1;
    }

    pdata->status = STANDBY_MODE;

    return 0;
}

static int hw_scharger_exit(struct hw_flash_ctrl_t *flash_ctrl)
{
    return 0;
}

static int hw_scharger_flash_mode(struct hw_flash_ctrl_t *flash_ctrl, int data)
{
    struct hw_scharger_private_data_t *pdata;
    int ret = 0;

    cam_debug("%s data=%d.\n", __func__, data);

    if (NULL == flash_ctrl) {
        cam_err("%s flash_ctrl is NULL.", __func__);
        return -1;
    }

    pdata = (struct hw_scharger_private_data_t *)flash_ctrl->pdata;

    if (data >= pdata->flash_led_num) {
        cam_err("Unsupport flash_lum_level: %d", data);
        return -1;
    }

    if ((NULL == pdata->flash_inter_ldo) || (NULL == pdata->flash_mode_ldo)) {
        cam_err("%s regulator is NULL", __func__);
        return -1;
    }

    /*if flash has already on do nothing*/
    if(BIT(FLASH_MODE) & pdata->status){
        cam_info("%s already in flash mode, do nothing",__func__);
        return 0;
    }

    ret = scharger_flash_led_timeout_config(FLASH_TIMEOUT_MS);
    if (ret < 0) {
        cam_err("%s scharger_flash_led_timeout_config  fail ret = %d ", __func__, ret);
        regulator_disable(pdata->flash_inter_ldo);
        return ret;
    }

    ret = scharger_flash_led_timeout_enable();
    if (ret < 0) {
        cam_err("%s scharger_flash_led_timeout_enable  fail ret = %d ", __func__, ret);
        return ret;
    }
    ret = regulator_enable(pdata->flash_inter_ldo);
    if (ret < 0) {
        cam_err("%s regulator_enable flash_inter_ldo fail ret = %d", __func__, ret);
/* #if defined (CONFIG_HUAWEI_DSM) */
/*         if (!dsm_client_ocuppy(client_ovisp22)){ */
/*             dsm_client_record(client_ovisp22,"[%s]regulator_enable flash_inter_ldo fail mode %d\n",__func__,mode); */
/*             dsm_client_notify(client_ovisp22, DSM_ISP22_FLASH_ERROR_NO); */
/*         } */
/* #endif */
        return ret;
    }
    udelay(500);

    ret = regulator_set_current_limit(pdata->flash_mode_ldo, pdata->flash_led[data], pdata->flash_led[data]);
    if (ret < 0) {
        cam_err("%s regulator_set_current_limit  fail ret = %d current is %d", __func__, ret, (pdata->flash_led[data]));
        regulator_disable(pdata->flash_inter_ldo);
        return ret;
    }

    ret = regulator_enable(pdata->flash_mode_ldo);
    if (ret < 0) {
        cam_err("%s regulator_enable torch_mode_ldo fail ret = %d", __func__, ret);
/* #if defined (CONFIG_HUAWEI_DSM) */
/*         if (!dsm_client_ocuppy(client_ovisp22)){ */
/*             dsm_client_record(client_ovisp22,"[%s]regulator_enable flash_mode_ldo fail mode %d\n",__func__,mode); */
/*             dsm_client_notify(client_ovisp22, DSM_ISP22_FLASH_ERROR_NO); */
/*         } */
/* #endif */
        regulator_disable(pdata->flash_inter_ldo);
        return ret;
    }

    pdata->status |= BIT(FLASH_MODE);
    return 0;
}

static int hw_scharger_torch_mode(struct hw_flash_ctrl_t *flash_ctrl, int data)
{
    struct hw_scharger_private_data_t *pdata;
    int ret = 0;

    cam_debug("%s data=%d.\n", __func__, data);

    if (NULL == flash_ctrl) {
        cam_err("%s flash_ctrl is NULL.", __func__);
        return -1;
    }

    pdata = (struct hw_scharger_private_data_t *)flash_ctrl->pdata;

    if (data >= pdata->torch_led_num) {
        cam_err("Unsupport torch_lum_level: %d", data);
        return -1;
    }

    if ((NULL == pdata->flash_inter_ldo) || (NULL == pdata->torch_mode_ldo)) {
        cam_err("%s regulator is NULL", __func__);
        return -1;
    }

    /*if flash has already on do nothing*/
    if(BIT(TORCH_MODE) & pdata->status){
        cam_info("%s already in torch mode, do nothing",__func__);
        return 0;
    }

    ret = regulator_enable(pdata->flash_inter_ldo);
    if (ret < 0) {
        cam_err("%s regulator_enable flash_inter_ldo fail ret = %d", __func__, ret);
        /* #if defined (CONFIG_HUAWEI_DSM) */
        /* if (!dsm_client_ocuppy(client_ovisp22)){ */
        /*     dsm_client_record(client_ovisp22,"[%s]regulator_enable flash_inter_ldo fail mode %d\n",__func__,mode); */
        /*     dsm_client_notify(client_ovisp22, DSM_ISP22_FLASH_ERROR_NO); */
        /* } */
        /* #endif */
        return ret;
    }

    udelay(500);

    ret = regulator_set_current_limit(pdata->torch_mode_ldo, pdata->torch_led[data], pdata->torch_led[data]);
    if (ret < 0) {
        cam_err("%s regulator_set_current_limit  fail ret = %d current is %d", __func__, ret, (pdata->torch_led[data]));
        return ret;
    }

    ret = regulator_enable(pdata->torch_mode_ldo);
    if (ret < 0) {
        cam_err("%s regulator_enable torch_mode_ldo fail ret = %d", __func__, ret);
/* #if defined (CONFIG_HUAWEI_DSM) */
/*         if (!dsm_client_ocuppy(client_ovisp22)){ */
/*             dsm_client_record(client_ovisp22,"[%s]regulator_enable torch_mode_ldo fail mode %d\n",__func__,mode); */
/*             dsm_client_notify(client_ovisp22, DSM_ISP22_FLASH_ERROR_NO); */
/*         } */
/* #endif */
        regulator_disable(pdata->flash_inter_ldo);
        return ret;
    }
    pdata->status |= BIT(TORCH_MODE);
    return 0;
}

static int hw_scharger_on(struct hw_flash_ctrl_t *flash_ctrl, void *data)
{
    struct hw_flash_cfg_data *cdata = (struct hw_flash_cfg_data *)data;
    int rc = -1;

    if ((NULL == flash_ctrl) || (NULL == cdata)) {
        cam_err("%s flash_ctrl or cdata is NULL.", __func__);
        return rc;
    }

    cam_debug("%s mode=%d, level=%d.\n", __func__, cdata->mode, cdata->data);

    mutex_lock(flash_ctrl->hw_flash_mutex);

    if (FLASH_MODE == cdata->mode) {
        rc = hw_scharger_flash_mode(flash_ctrl, cdata->data);
    } else {
        rc = hw_scharger_torch_mode(flash_ctrl, cdata->data);
    }
    flash_ctrl->state.mode = cdata->mode;
    flash_ctrl->state.data = cdata->data;
    mutex_unlock(flash_ctrl->hw_flash_mutex);

    return rc;
}

static int hw_scharger_off(struct hw_flash_ctrl_t *flash_ctrl)
{
    struct hw_scharger_private_data_t *pdata;

    cam_debug("%s enter.\n", __func__);

    if (NULL == flash_ctrl) {
        cam_err("%s flash_ctrl is NULL.", __func__);
        return -1;
    }

    if (STANDBY_MODE == flash_ctrl->state.mode) {
        cam_notice("%s flash led has been powered off.", __func__);
        return 0;
    }

    pdata = (struct hw_scharger_private_data_t *)flash_ctrl->pdata;

    if ((NULL == pdata->flash_inter_ldo)
            || (NULL == pdata->flash_mode_ldo)
            || (NULL == pdata->torch_mode_ldo)) {
        cam_err("%s regulator is NULL", __func__);
        return -1;
    }

    mutex_lock(flash_ctrl->hw_flash_mutex);

    if (BIT(TORCH_MODE) & pdata->status) {
        regulator_disable(pdata->torch_mode_ldo);
        regulator_disable(pdata->flash_inter_ldo);
        pdata->status &= ~BIT(TORCH_MODE);
    }

    if (BIT(FLASH_MODE) & pdata->status) {
        regulator_disable(pdata->flash_mode_ldo);
        regulator_disable(pdata->flash_inter_ldo);
        pdata->status &= ~BIT(FLASH_MODE);
    }

    flash_ctrl->state.mode = STANDBY_MODE;
    flash_ctrl->state.data = 0;

    mutex_unlock(flash_ctrl->hw_flash_mutex);

    return 0;
}

static int hw_scharger_match(struct hw_flash_ctrl_t *flash_ctrl)
{
    cam_debug("%s ernter.\n", __func__);
    return 0;
}

static int hw_scharger_get_dt_data(struct hw_flash_ctrl_t *flash_ctrl)
{
    struct hw_scharger_private_data_t *pdata;
    struct device_node *of_node;
    int i;
    int rc = -1;

    cam_debug("%s enter.\n", __func__);

    if (NULL == flash_ctrl) {
        cam_err("%s flash_ctrl is NULL.", __func__);
        return rc;
    }

    pdata = (struct hw_scharger_private_data_t *)flash_ctrl->pdata;
    of_node = flash_ctrl->dev->of_node;

    rc = of_property_read_u32(of_node, "huawei,flash_led_num", &pdata->flash_led_num);
    cam_debug("%s hisi,flash_led_num %d, rc %d\n", __func__, pdata->flash_led_num, rc);
    if (rc < 0) {
        cam_err("%s failed %d\n", __func__, __LINE__);
        return rc;
    }

    rc = of_property_read_u32(of_node, "huawei,torch_led_num",
            &pdata->torch_led_num);
    cam_debug("%s hisi,torch_led_num %d, rc %d\n", __func__,
            pdata->torch_led_num, rc);
    if (rc < 0) {
        cam_err("%s failed %d\n", __func__, __LINE__);
        return rc;
    }

    rc = of_property_read_u32_array(of_node, "huawei,flash_led",
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

    rc = of_property_read_u32_array(of_node, "huawei,torch_led",
            pdata->torch_led, pdata->torch_led_num);
    if (rc < 0) {
        cam_err("%s failed line %d\n", __func__, __LINE__);
        return rc;
    } else {
        for (i = 0; i < pdata->torch_led_num; i++) {
            cam_debug("%s torch_led[%d]=0x%x.\n", __func__, i,
                    pdata->torch_led[i]);
        }
    }

    return rc;
}

static ssize_t hw_scharger_lightness_show(struct device *dev,
    struct device_attribute *attr,char *buf)
{
    int rc=0;

    snprintf(buf, MAX_ATTRIBUTE_BUFFER_SIZE, "mode=%d, data=%d.\n",
            hw_scharger_ctrl.state.mode, hw_scharger_ctrl.state.data);
    rc = strlen(buf)+1;
    return rc;
}

static int hw_scharger_param_check(char *buf, unsigned long *param,
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

static ssize_t hw_scharger_lightness_store(struct device *dev,
    struct device_attribute *attr, const char *buf, size_t count)
{
    struct hw_flash_cfg_data cdata = {0};
    unsigned long param[2] = {0};
    int rc = 0;

    rc = hw_scharger_param_check((char *)buf, param, 2);
    if (rc < 0) {
        cam_err("%s failed to check param.", __func__);
        return rc;
    }

    cdata.mode = (int)param[0];
    cdata.data = (int)param[1];

    if (cdata.mode == STANDBY_MODE) {
        rc = hw_scharger_off(&hw_scharger_ctrl);
        if (rc < 0) {
            cam_err("%s scharger flash off error.", __func__);
            return rc;
        }
    } else {
        rc = hw_scharger_on(&hw_scharger_ctrl, &cdata);
        if (rc < 0) {
            cam_err("%s scharger flash on error.", __func__);
            return rc;
        }
    }

    return count;
}

static ssize_t hw_scharger_flash_mask_show(struct device *dev,
    struct device_attribute *attr,char *buf)
{
    int rc = 0;

    snprintf(buf, MAX_ATTRIBUTE_BUFFER_SIZE, "flash_mask_disabled=%d.\n",
            hw_scharger_ctrl.flash_mask_enable);
    rc = strlen(buf)+1;
    return rc;
}

static ssize_t hw_scharger_flash_mask_store(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t count)
{
    if ('0' == buf[0]) {
        hw_scharger_ctrl.flash_mask_enable = false;
    } else {
        hw_scharger_ctrl.flash_mask_enable = true;
    }
    cam_debug("%s flash_mask_enable=%d.", __func__,
            hw_scharger_ctrl.flash_mask_enable);
    return count;
}

static void hw_scharger_torch_brightness_set(struct led_classdev *cdev,
        enum led_brightness brightness)
{
    struct hw_flash_cfg_data cdata;
    int rc;
    unsigned int led_bright = brightness;

    if (STANDBY_MODE == led_bright) {
        rc = hw_scharger_off(&hw_scharger_ctrl);
        if (rc < 0) {
            cam_err("%s scharger off error.", __func__);
            return;
        }
    } else {
        cdata.mode = TORCH_MODE;
        cdata.data = brightness - 1;
        rc = hw_scharger_on(&hw_scharger_ctrl, &cdata);
        if (rc < 0) {
            cam_err("%s scharger on error.", __func__);
            return;
        }
    }
}

static struct device_attribute hw_scharger_lightness =
    __ATTR(lightness, 0664, hw_scharger_lightness_show, hw_scharger_lightness_store);

static struct device_attribute hw_scharger_flash_mask =
    __ATTR(flash_mask, 0664, hw_scharger_flash_mask_show, hw_scharger_flash_mask_store);

static int hw_scharger_register_attribute(struct hw_flash_ctrl_t *flash_ctrl,
    struct device *dev)
{
    int rc = 0;
    struct hw_scharger_private_data_t *pdata;

    if ((NULL == flash_ctrl) || (NULL == dev)) {
        cam_err("%s flash_ctrl or dev is NULL.", __func__);
        return -1;
    }

    pdata = (struct hw_scharger_private_data_t *)(flash_ctrl->pdata);
    if(NULL == pdata) {
        cam_err("%s pdata is NULL.", __func__);
        return -1;
    }

    flash_ctrl->cdev_torch.name = "torch";
    flash_ctrl->cdev_torch.max_brightness = pdata->torch_led_num;
    flash_ctrl->cdev_torch.brightness_set = hw_scharger_torch_brightness_set;
    rc = led_classdev_register((struct device *)dev, &flash_ctrl->cdev_torch);
    if (rc < 0) {
        cam_err("%s failed to register torch classdev.", __func__);
        goto err_out;
    }

    rc = device_create_file(dev, &hw_scharger_lightness);
    if (rc < 0) {
        cam_err("%s failed to creat lightness attribute.", __func__);
        goto err_create_lightness_file;
    }

    rc = device_create_file(dev, &hw_scharger_flash_mask);
    if (rc < 0) {
        cam_err("%s failed to creat flash_mask attribute.", __func__);
        goto err_create_flash_mask_file;
    }

    return 0;

err_create_flash_mask_file:
    device_remove_file(dev, &hw_scharger_lightness);
err_create_lightness_file:
    led_classdev_unregister(&flash_ctrl->cdev_torch);
err_out:

    return rc;
}

static const struct of_device_id hw_scharger_match_id[] = {
	{.compatible = "huawei,scharger_flash"},
	{}
};

MODULE_DEVICE_TABLE(of, scharger_dt_match);

static int hw_scharger_probe(struct platform_device *pdev)
{
    int ret = 0;
    struct regulator *ldo = NULL;

    memset(&hw_scharger_pdata, 0, sizeof(hw_scharger_pdata));

    ldo = devm_regulator_get(&pdev->dev, SCHG_BOOST_REGULATOR);
    if (IS_ERR_OR_NULL(ldo)) {
        cam_err("%s: Could not get regulator : %s\n", __func__, SCHG_BOOST_REGULATOR);
        ret = -ENXIO;
        goto fail;
    }

    hw_scharger_pdata.flash_inter_ldo = ldo;

    /* get flash mode regulator */
    ldo = devm_regulator_get(&pdev->dev, SCHG_FLASH_MODE_REGULATOR);
    if (IS_ERR_OR_NULL(ldo)) {
        cam_err("%s: Could not get regulator : %s\n", __func__, SCHG_FLASH_MODE_REGULATOR);
        ret =  -ENXIO;
        goto fail;
    }
    hw_scharger_pdata.flash_mode_ldo = ldo;

    /* get torch mode regulator */
    ldo = devm_regulator_get(&pdev->dev, SCHG_TORCH_MODE_REGULATOR);
    if (IS_ERR_OR_NULL(ldo)) {
        cam_err("%s: Could not get regulator : %s\n", __func__, SCHG_TORCH_MODE_REGULATOR);
        ret =  -ENXIO;
        goto fail;
    }

    hw_scharger_pdata.torch_mode_ldo = ldo;

    hw_scharger_ctrl.pdata = &hw_scharger_pdata;
    platform_set_drvdata(pdev, &hw_scharger_ctrl);

    return hw_flash_platform_probe(pdev, &hw_scharger_ctrl);

fail:
    if (NULL != hw_scharger_pdata.flash_inter_ldo) {
        devm_regulator_put(hw_scharger_pdata.flash_inter_ldo);
        hw_scharger_pdata.flash_inter_ldo = NULL;
    }
    if (NULL != hw_scharger_pdata.flash_mode_ldo) {
        devm_regulator_put(hw_scharger_pdata.flash_mode_ldo);
        hw_scharger_pdata.flash_mode_ldo = NULL;
    }

    return ret;
}

static int hw_scharger_remove(struct platform_device *pdev)
{
    return hw_scharger_ctrl.func_tbl->flash_exit(&hw_scharger_ctrl);
}

static struct platform_driver hw_scharger_platform_driver = {
    .probe = hw_scharger_probe,
    .remove = hw_scharger_remove,
    .driver = {
        .name = "scharger",
        .owner = THIS_MODULE,
#ifdef CONFIG_OF
        .of_match_table = of_match_ptr(hw_scharger_match_id),
#endif
    },
};

static struct hw_flash_fn_t hw_scharger_func_tbl = {
    .flash_config = hw_flash_config,
    .flash_init = hw_scharger_init,
    .flash_exit = hw_scharger_exit,
    .flash_on = hw_scharger_on,
    .flash_off = hw_scharger_off,
    .flash_match = hw_scharger_match,
    .flash_get_dt_data = hw_scharger_get_dt_data,
    .flash_register_attribute = hw_scharger_register_attribute,
};

static struct hw_flash_ctrl_t hw_scharger_ctrl = {
    .func_tbl = &hw_scharger_func_tbl,
    .hw_flash_mutex = &flash_mut_scharger,
    .pdata = (void*)&hw_scharger_pdata,
    .flash_mask_enable = true,
    .state = {
        .mode = STANDBY_MODE,
    },
};

module_platform_driver(hw_scharger_platform_driver);

MODULE_DESCRIPTION("SCHARGER CAMERA FLASH");
MODULE_LICENSE("GPL v2");
