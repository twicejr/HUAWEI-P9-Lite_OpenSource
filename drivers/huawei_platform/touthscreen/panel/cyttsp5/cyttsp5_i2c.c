/*
 * cyttsp5_i2c.c
 * Cypress TrueTouch(TM) Standard Product V5 I2C Module.
 * For use with Cypress Txx5xx parts.
 * Supported parts include:
 * TMA5XX
 *
 * Copyright (C) 2012-2014 Cypress Semiconductor
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2, and only version 2, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Contact Cypress Semiconductor at www.cypress.com <ttdrivers@cypress.com>
 *
 */

#include "cyttsp5_regs.h"

#include <linux/i2c.h>
#include <linux/version.h>

#if defined (CONFIG_HUAWEI_DSM)
#include <linux/gpio.h>
#include <linux/regulator/consumer.h>
#include <dsm/dsm_pub.h>
#endif

#define CY_I2C_DATA_SIZE  (2 * 256)

#if defined (CONFIG_HUAWEI_DSM)
#define DSMINFO_LEN_MAX        64

static struct dsm_dev dsm_cyp_tp = {
    .name = "dsm_tp",
    .device_name = "TP",
    .ic_name = "CYP",
    .module_name = "NNN",
    .fops = NULL,
    .buff_size = 1024,
};

struct tp_dsm_info g_tp_dsm_info;
struct dsm_client *tp_cyp_dclient = NULL;

ssize_t cyttsp5_dsm_record_basic_err_info(struct device *dev)
{
    struct cyttsp5_core_data *cd = dev_get_drvdata(dev);
    struct cyttsp5_power_control * power_ctrl = NULL;
    char *vci_power_info = NULL, *vddio_power_info = NULL;
    int vci_value= -1, vci_status = -1, vddio_value = -1, vddio_status = -1;

    power_ctrl = &(cd->power_ctrl);

    vci_power_info = kzalloc(DSMINFO_LEN_MAX, GFP_KERNEL);
    if (!vci_power_info) {
        TS_LOG_ERR("%s: vci_power_info kzalloc fail\n", __func__);
        goto error_alloc_data;
    }

    vddio_power_info = kzalloc(DSMINFO_LEN_MAX, GFP_KERNEL);
    if (!vddio_power_info) {
        TS_LOG_ERR("%s: vddio_power_info kzalloc fail\n", __func__);
        goto error_alloc_data;
    }

    if (VCI_LDO_CTRL_MODE == power_ctrl->vci_power_type) {
        vci_value = regulator_get_voltage(power_ctrl->vci) / 1000;
        vci_status = regulator_is_enabled(power_ctrl->vci);
        snprintf(vci_power_info, DSMINFO_LEN_MAX, "[vci   power] type:ldo, volt:%d, status:%d", vci_value, vci_status);

    } else if (VCI_GPIO_CTRL_MODE == power_ctrl->vci_power_type) {
        vci_value = power_ctrl->vci_gpio_ctrl;
        vci_status = gpio_get_value(power_ctrl->vci_gpio_ctrl);
        snprintf(vci_power_info, DSMINFO_LEN_MAX, "[vci   power] type:gpio, num:%d, status:%d", vci_value, vci_status);

    } else {
        snprintf(vci_power_info, DSMINFO_LEN_MAX, "[vci   power] type:unknown");
    }

    if (VDDIO_LDO_CTRL_MODE == power_ctrl->vddio_power_type) {
        vddio_value = regulator_get_voltage(power_ctrl->vddio) / 1000;
        vddio_status = regulator_is_enabled(power_ctrl->vddio);
        snprintf(vddio_power_info, DSMINFO_LEN_MAX, "[vddio power] type:ldo, volt:%d, status:%d", vddio_value, vddio_status);

    } else if (VDDIO_GPIO_CTRL_MODE == power_ctrl->vddio_power_type) {
        vddio_value = power_ctrl->vddio_gpio_ctrl;
        vddio_status = gpio_get_value(power_ctrl->vddio_gpio_ctrl);
        snprintf(vddio_power_info, DSMINFO_LEN_MAX, "[vddio power] type:gpio, num:%3d, status:%d", vddio_value, vddio_status);

    } else {
        snprintf(vddio_power_info, DSMINFO_LEN_MAX, "[vddio power] type:unknown");
    }

    dsm_client_record(tp_cyp_dclient, "%s\n"\
                                      "%s\n"\
                                      "[irq    gpio] num: %d, irq   gpio status:%d\n"\
                                      "[reset  gpio] num:%d, reset gpio status:%d\n",\
                                      vci_power_info,\
                                      vddio_power_info,\
                                      g_tp_dsm_info.irq_gpio, gpio_get_value(g_tp_dsm_info.irq_gpio),\
                                      g_tp_dsm_info.rst_gpio, gpio_get_value(g_tp_dsm_info.rst_gpio));

    TS_LOG_ERR("%s: %s\n", __func__, vci_power_info);
    TS_LOG_ERR("%s: %s\n", __func__, vddio_power_info);
    goto exit;

error_alloc_data:
    dsm_client_record(tp_cyp_dclient, "[irq    gpio] num: %d, irq   gpio status:%d\n"\
                                      "[reset  gpio] num:%d, reset gpio status:%d\n",\
                                      g_tp_dsm_info.irq_gpio, gpio_get_value(g_tp_dsm_info.irq_gpio),\
                                      g_tp_dsm_info.rst_gpio, gpio_get_value(g_tp_dsm_info.rst_gpio));
exit:
    TS_LOG_ERR("%s: [irq    gpio] num:%3d, irq   gpio status:%d\n",
                    __func__, g_tp_dsm_info.irq_gpio, gpio_get_value(g_tp_dsm_info.irq_gpio));
    TS_LOG_ERR("%s: [reset  gpio] num:%3d, reset gpio status:%d\n",
                    __func__, g_tp_dsm_info.rst_gpio, gpio_get_value(g_tp_dsm_info.rst_gpio));

    kfree(vci_power_info);
    kfree(vddio_power_info);

    return 0;
}
#endif

static int cyttsp5_i2c_read_default(struct device *dev, void *buf, int size)
{
    struct i2c_client *client = to_i2c_client(dev);
    int rc;

    if (!buf || !size || size > CY_I2C_DATA_SIZE)
        return -EINVAL;

    rc = i2c_master_recv(client, buf, size);

    return (rc < 0) ? rc : rc != size ? -EIO : 0;
}

static int cyttsp5_i2c_read_default_nosize(struct device *dev, u8 *buf, u32 max)
{
    struct i2c_client *client = to_i2c_client(dev);
    struct i2c_msg msgs[2];
    u8 msg_count = 1;
    int rc;
    u32 size;

    if (!buf) {
        TS_LOG_ERR("%s: input parameter error.\n", __func__);
        return -EINVAL;
    }

    msgs[0].addr = client->addr;
    msgs[0].flags = (client->flags & I2C_M_TEN) | I2C_M_RD;
    msgs[0].len = 2;
    msgs[0].buf = buf;
    rc = i2c_transfer(client->adapter, msgs, msg_count);
    if (rc < 0 || rc != msg_count) {
        TS_LOG_ERR("%s: I2C transfer error, rc = %d, msg_count = %d\n",
                    __func__, rc, msg_count);
        return (rc < 0) ? rc : -EIO;
    }

    size = get_unaligned_le16(&buf[0]);
    if (!size || size == 2) {
        return 0;
    }

    if (size > max) {
        TS_LOG_ERR("%s: ERROR, size = %d, max = %d\n", __func__,size, max);
        return -EINVAL;
    }

    rc = i2c_master_recv(client, buf, size);

#if defined (CONFIG_HUAWEI_DSM)
    if ((rc < 0) || (rc != size)) {
        g_tp_dsm_info.constraints_I2C_status = rc;

        if (!dsm_client_ocuppy(tp_cyp_dclient)) {
            cyttsp5_dsm_record_basic_err_info(dev);
            dsm_client_record(tp_cyp_dclient, "i2c read error retval:%d\n",\
            g_tp_dsm_info.constraints_I2C_status);
            dsm_client_notify(tp_cyp_dclient, DSM_TP_I2C_RW_ERROR_NO);
        }
    }
#endif

    if (rc < 0) {
        TS_LOG_ERR("%s: I2C read error, rc = %d\n", __func__,rc);
        return rc;
    } else if (rc != size) {
        TS_LOG_ERR("%s: I2C read error, rc = %d, size = %d\n", __func__, rc, size);
        return -EIO;
    }

    return 0;
}

static int cyttsp5_i2c_write_read_specific(struct device *dev, u8 write_len,
        u8 *write_buf, u8 *read_buf)
{
    struct i2c_client *client = to_i2c_client(dev);
    struct i2c_msg msgs[2];
    u8 msg_count = 1;
    int rc;

    if (!write_buf || !write_len) {
        TS_LOG_ERR("%s: input parameter error.\n", __func__);
        return -EINVAL;
    }

    msgs[0].addr = client->addr;
    msgs[0].flags = client->flags & I2C_M_TEN;
    msgs[0].len = write_len;
    msgs[0].buf = write_buf;
    rc = i2c_transfer(client->adapter, msgs, msg_count);

    if (rc < 0 || rc != msg_count) {
#if defined (CONFIG_HUAWEI_DSM)
        g_tp_dsm_info.constraints_I2C_status = rc;

        if (!dsm_client_ocuppy(tp_cyp_dclient)) {
            cyttsp5_dsm_record_basic_err_info(dev);
            dsm_client_record(tp_cyp_dclient, "i2c write error retval:%d\n",\
            g_tp_dsm_info.constraints_I2C_status);
            dsm_client_notify(tp_cyp_dclient, DSM_TP_I2C_RW_ERROR_NO);
        }
#endif
        TS_LOG_ERR("%s: I2C transfer error, rc = %d\n", __func__,rc);
        return (rc < 0) ? rc : -EIO;
    }

    rc = 0;

    if (read_buf) {
        rc = cyttsp5_i2c_read_default_nosize(dev, read_buf,
                CY_I2C_DATA_SIZE);
        if (rc) {
            TS_LOG_ERR("%s: I2C read error, rc = %d\n", __func__,rc);
        }
    }

    return rc;
}

static struct cyttsp5_bus_ops cyttsp5_i2c_bus_ops = {
    .bustype = BUS_I2C,
    .read_default = cyttsp5_i2c_read_default,
    .read_default_nosize = cyttsp5_i2c_read_default_nosize,
    .write_read_specific = cyttsp5_i2c_write_read_specific,
};

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_DEVICETREE_SUPPORT
static struct of_device_id cyttsp5_i2c_of_match[] = {
    { .compatible = "cy,cyttsp5_i2c_adapter", },
    { }
};
MODULE_DEVICE_TABLE(of, cyttsp5_i2c_of_match);
#endif

static int cyttsp5_i2c_probe(struct i2c_client *client,
    const struct i2c_device_id *i2c_id)
{
    struct device *dev = &client->dev;
#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_DEVICETREE_SUPPORT
    const struct of_device_id *match = NULL;
#endif
    int rc = 0;

    TS_LOG_INFO("%s: Probe start\n", __func__);
    if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
        TS_LOG_ERR("%s: I2C functionality not Supported.\n", __func__);
        return -EIO;
    }

/* if support device tree, get pdata from device tree */
#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_DEVICETREE_SUPPORT
    match = of_match_device(of_match_ptr(cyttsp5_i2c_of_match), dev);
    if (match) {
        rc = cyttsp5_devtree_create_and_get_pdata(dev);
        if (rc < 0) {
            TS_LOG_ERR("%s: device tree create and get pdata fail, rc = %d.\n",
                        __func__,rc);
            return rc;
        }
    } else {
        TS_LOG_ERR("%s: No device mathced.\n", __func__);
        return -ENODEV;
    }
#endif

    rc = cyttsp5_probe(&cyttsp5_i2c_bus_ops, &client->dev, client->irq,
              CY_I2C_DATA_SIZE);

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_DEVICETREE_SUPPORT
    if (rc && match) {
        cyttsp5_devtree_clean_pdata(dev);
        TS_LOG_ERR("%s: cyttsp5 probe fail.\n", __func__);
        return rc;
    }
#endif

#if defined (CONFIG_HUAWEI_DSM)
    if (!tp_cyp_dclient) {
        tp_cyp_dclient = dsm_register_client(&dsm_cyp_tp);
    }
#endif

    TS_LOG_INFO("%s: cyttsp5 probe success.\n", __func__);

    return rc;
}

static int cyttsp5_i2c_remove(struct i2c_client *client)
{
#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_DEVICETREE_SUPPORT
    struct device *dev = &client->dev;
    const struct of_device_id *match;
#endif
    struct cyttsp5_core_data *cd = i2c_get_clientdata(client);

    cyttsp5_release(cd);

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_DEVICETREE_SUPPORT
    match = of_match_device(of_match_ptr(cyttsp5_i2c_of_match), dev);
    if (match)
        cyttsp5_devtree_clean_pdata(dev);
#endif

    return 0;
}

static const struct i2c_device_id cyttsp5_i2c_id[] = {
    { CYTTSP5_I2C_NAME, 0, },
    { }
};
MODULE_DEVICE_TABLE(i2c, cyttsp5_i2c_id);

static struct i2c_driver cyttsp5_i2c_driver = {
    .driver = {
        .name = CYTTSP5_I2C_NAME,
        .owner = THIS_MODULE,
#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_DEVICETREE_SUPPORT
        .of_match_table = cyttsp5_i2c_of_match,
#endif
    },
    .probe = cyttsp5_i2c_probe,
    .remove = cyttsp5_i2c_remove,
    .id_table = cyttsp5_i2c_id,
};

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 3, 0))
module_i2c_driver(cyttsp5_i2c_driver);
#else
static int __init cyttsp5_i2c_init(void)
{
    int rc = i2c_add_driver(&cyttsp5_i2c_driver);

    if (rc) {
        TS_LOG_ERR("%s: Cypress v5 I2C Driver add fail, rc = %d.\n",__func__,rc);
    } else {
        TS_LOG_INFO("%s: Cypress TTSP v5 I2C Driver add successful.\n",__func__,rc);
    }
    return rc;
}
module_init(cyttsp5_i2c_init);

static void __exit cyttsp5_i2c_exit(void)
{
    i2c_del_driver(&cyttsp5_i2c_driver);
}
module_exit(cyttsp5_i2c_exit);
#endif

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Cypress TrueTouch(R) Standard Product I2C driver");
MODULE_AUTHOR("Cypress Semiconductor <ttdrivers@cypress.com>");
