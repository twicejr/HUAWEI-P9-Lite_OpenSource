/*
 * cyttsp5_platform.c
 * Cypress TrueTouch(TM) Standard Product V5 Platform Module.
 * For use with Cypress Txx5xx parts.
 * Supported parts include:
 * TMA5XX
 *
 * Copyright (C) 2013-2014 Cypress Semiconductor
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
#include "cyttsp5_platform.h"

#if defined (CONFIG_HUAWEI_DSM)
extern struct tp_dsm_info g_tp_dsm_info;
#endif

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_PLATFORM_FW_UPGRADE
/* FW for Panel ID = 0x00 */
#include "cyttsp5_fw_pid00.h"
static struct cyttsp5_touch_firmware cyttsp5_firmware_pid00 = {
    .img = cyttsp5_img_pid00,
    .size = ARRAY_SIZE(cyttsp5_img_pid00),
    .ver = cyttsp5_ver_pid00,
    .vsize = ARRAY_SIZE(cyttsp5_ver_pid00),
    .panel_id = 0x00,
};

/* FW for Panel ID = 0x01 */
#include "cyttsp5_fw_pid01.h"
static struct cyttsp5_touch_firmware cyttsp5_firmware_pid01 = {
    .img = cyttsp5_img_pid01,
    .size = ARRAY_SIZE(cyttsp5_img_pid01),
    .ver = cyttsp5_ver_pid01,
    .vsize = ARRAY_SIZE(cyttsp5_ver_pid01),
    .panel_id = 0x01,
};

/* FW for Panel ID not enabled (legacy) */
#include "cyttsp5_fw.h"
static struct cyttsp5_touch_firmware cyttsp5_firmware = {
    .img = cyttsp5_img,
    .size = ARRAY_SIZE(cyttsp5_img),
    .ver = cyttsp5_ver,
    .vsize = ARRAY_SIZE(cyttsp5_ver),
};
#else
/* FW for Panel ID not enabled (legacy) */
static struct cyttsp5_touch_firmware cyttsp5_firmware = {
    .img = NULL,
    .size = 0,
    .ver = NULL,
    .vsize = 0,
};
#endif

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_PLATFORM_TTCONFIG_UPGRADE
/* alice ofilm ttconfiger */
#include "./ttconfig/alice_ttconfig_ofilm.h"
static struct touch_settings cyttsp5_sett_param_regs_alice_ofilm = {
    .data = (uint8_t *)&cyttsp5_param_regs_alice_ofilm[0],
    .size = ARRAY_SIZE(cyttsp5_param_regs_alice_ofilm),
    .tag = 0,
};

static struct touch_settings cyttsp5_sett_param_size_alice_ofilm = {
    .data = (uint8_t *)&cyttsp5_param_size_alice_ofilm[0],
    .size = ARRAY_SIZE(cyttsp5_param_size_alice_ofilm),
    .tag = 0,
};

static struct cyttsp5_touch_config cyttsp5_ttconfig_alice_ofilm = {
    .param_regs = &cyttsp5_sett_param_regs_alice_ofilm,
    .param_size = &cyttsp5_sett_param_size_alice_ofilm,
    .fw_ver = ttconfig_fw_ver_alice_ofilm,
    .fw_vsize = ARRAY_SIZE(ttconfig_fw_ver_alice_ofilm),
    .panel_id = FW_OFILM,
    .product_name = PHONE_NAME_ALICE,
};

/* alice truly ttconfiger */
#include "./ttconfig/alice_ttconfig_truly.h"
static struct touch_settings cyttsp5_sett_param_regs_alice_truly = {
    .data = (uint8_t *)&cyttsp5_param_regs_alice_truly[0],
    .size = ARRAY_SIZE(cyttsp5_param_regs_alice_truly),
    .tag = 0,
};

static struct touch_settings cyttsp5_sett_param_size_alice_truly = {
    .data = (uint8_t *)&cyttsp5_param_size_alice_truly[0],
    .size = ARRAY_SIZE(cyttsp5_param_size_alice_truly),
    .tag = 0,
};

static struct cyttsp5_touch_config cyttsp5_ttconfig_alice_truly = {
    .param_regs = &cyttsp5_sett_param_regs_alice_truly,
    .param_size = &cyttsp5_sett_param_size_alice_truly,
    .fw_ver = ttconfig_fw_ver_alice_truly,
    .fw_vsize = ARRAY_SIZE(ttconfig_fw_ver_alice_truly),
    .panel_id = FW_TRULY,
    .product_name = PHONE_NAME_ALICE,
};

/* alice junda ttconfiger */
#include "./ttconfig/alice_ttconfig_junda.h"
static struct touch_settings cyttsp5_sett_param_regs_alice_junda = {
    .data = (uint8_t *)&cyttsp5_param_regs_alice_junda[0],
    .size = ARRAY_SIZE(cyttsp5_param_regs_alice_junda),
    .tag = 0,
};

static struct touch_settings cyttsp5_sett_param_size_alice_junda = {
    .data = (uint8_t *)&cyttsp5_param_size_alice_junda[0],
    .size = ARRAY_SIZE(cyttsp5_param_size_alice_junda),
    .tag = 0,
};

static struct cyttsp5_touch_config cyttsp5_ttconfig_alice_junda = {
    .param_regs = &cyttsp5_sett_param_regs_alice_junda,
    .param_size = &cyttsp5_sett_param_size_alice_junda,
    .fw_ver = ttconfig_fw_ver_alice_junda,
    .fw_vsize = ARRAY_SIZE(ttconfig_fw_ver_alice_junda),
    .panel_id = FW_JUNDA,
    .product_name = PHONE_NAME_ALICE,
};

/* TT Config for Panel ID not enabled (legacy)*/
#include "./ttconfig/default_ttconfig.h"
static struct touch_settings cyttsp5_sett_param_regs = {
    .data = (uint8_t *)&cyttsp5_param_regs[0],
    .size = ARRAY_SIZE(cyttsp5_param_regs),
    .tag = 0,
};

static struct touch_settings cyttsp5_sett_param_size = {
    .data = (uint8_t *)&cyttsp5_param_size[0],
    .size = ARRAY_SIZE(cyttsp5_param_size),
    .tag = 0,
};

static struct cyttsp5_touch_config cyttsp5_ttconfig = {
    .param_regs = &cyttsp5_sett_param_regs,
    .param_size = &cyttsp5_sett_param_size,
    .fw_ver = ttconfig_fw_ver,
    .fw_vsize = ARRAY_SIZE(ttconfig_fw_ver),
};
#else
/* TT Config for Panel ID not enabled (legacy)*/
static struct cyttsp5_touch_config cyttsp5_ttconfig = {
    .param_regs = NULL,
    .param_size = NULL,
    .fw_ver = NULL,
    .fw_vsize = 0,
};
#endif

static struct cyttsp5_touch_firmware *cyttsp5_firmwares[] = {
#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_PLATFORM_FW_UPGRADE
    &cyttsp5_firmware_pid00,
    &cyttsp5_firmware_pid01,
#endif
    NULL, /* Last item should always be NULL */
};

static struct cyttsp5_touch_config *cyttsp5_ttconfigs[] = {
#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_PLATFORM_TTCONFIG_UPGRADE
    &cyttsp5_ttconfig_alice_ofilm,
    &cyttsp5_ttconfig_alice_truly,
    &cyttsp5_ttconfig_alice_junda,
#endif
    NULL, /* Last item should always be NULL */
};

struct cyttsp5_loader_platform_data _cyttsp5_loader_platform_data = {
    .fw = &cyttsp5_firmware,
    .ttconfig = &cyttsp5_ttconfig,
    .fws = cyttsp5_firmwares,
    .ttconfigs = cyttsp5_ttconfigs,
    .flags = CY_LOADER_FLAG_CALIBRATE_AFTER_FW_UPGRADE | CY_LOADER_FLAG_CALIBRATE_AFTER_TTCONFIG_UPGRADE,
};

int cyttsp5_xres(struct cyttsp5_core_platform_data *pdata,
        struct device *dev)
{
    int rst_gpio = pdata->rst_gpio;
    int rc = 0;

    gpio_set_value(rst_gpio, 1);
    msleep(20);
    gpio_set_value(rst_gpio, 0);
    msleep(40);
    gpio_set_value(rst_gpio, 1);
    msleep(100);
    TS_LOG_INFO("%s: RESET CYTTSP gpio=%d r=%d\n", __func__, pdata->rst_gpio, rc);
    return rc;
}

int cyttsp5_init(struct cyttsp5_core_platform_data *pdata,
        int on, struct device *dev)
{
    int rst_gpio = -1;
    int irq_gpio = -1;
    int rc = 0;

    if (NULL == pdata || NULL == dev) {
        TS_LOG_ERR("%s %d:input parameter missing\n", __func__, __LINE__);
        return -EINVAL;
    }

    rst_gpio = pdata->rst_gpio;
    irq_gpio = pdata->irq_gpio;

#if defined (CONFIG_HUAWEI_DSM)
    g_tp_dsm_info.rst_gpio = rst_gpio;
    g_tp_dsm_info.irq_gpio = irq_gpio;
#endif

    if (on) {
        rc = gpio_request(rst_gpio,"ts_reset");
        if (rc < 0) {
            TS_LOG_ERR("%s,gpio_request fail, gpio = %d,rc = %d\n",
                        __func__,rst_gpio, rc);
            gpio_free(rst_gpio);
            rc = gpio_request(rst_gpio,"ts_reset");
        }
        if (rc < 0) {
            TS_LOG_ERR("%s: Fail request gpio=%d\n", __func__,rst_gpio);
        } else {
            rc = gpio_direction_output(rst_gpio, 1);
            if (rc < 0) {
                TS_LOG_ERR("%s: Fail set output gpio=%d\n",__func__, rst_gpio);
                gpio_free(rst_gpio);
            } else {
                rc = gpio_request(irq_gpio,"ts_irq");
                if (rc < 0) {
                    TS_LOG_ERR("%s,gpio_request fail, gpio = %d,rc = %d\n",
                                __func__,irq_gpio, rc);
                    gpio_free(irq_gpio);
                    rc = gpio_request(irq_gpio,"ts_irq");
                }
                if (rc < 0) {
                    TS_LOG_ERR("%s: Fail request gpio=%d\n",__func__, irq_gpio);
                    gpio_free(rst_gpio);
                } else {
                    gpio_direction_input(irq_gpio);
                }
            }
        }
    } else {
        gpio_free(rst_gpio);
        gpio_free(irq_gpio);
    }

    TS_LOG_INFO("%s: INIT CYTTSP RST gpio=%d and IRQ gpio=%d r=%d\n",
        __func__, rst_gpio, irq_gpio, rc);
    return rc;
}

static int cyttsp5_wakeup(struct cyttsp5_core_platform_data *pdata,
        struct device *dev, atomic_t *ignore_irq)
{
    return 0;
}

static int cyttsp5_sleep(struct cyttsp5_core_platform_data *pdata,
        struct device *dev, atomic_t *ignore_irq)
{
    return 0;
}

int cyttsp5_power(struct cyttsp5_core_platform_data *pdata,
        int on, struct device *dev, atomic_t *ignore_irq)
{
    if (on)
        return cyttsp5_wakeup(pdata, dev, ignore_irq);

    return cyttsp5_sleep(pdata, dev, ignore_irq);
}

int cyttsp5_irq_stat(struct cyttsp5_core_platform_data *pdata,
        struct device *dev)
{
    return gpio_get_value(pdata->irq_gpio);
}

#ifdef CYTTSP5_DETECT_HW
int cyttsp5_detect(struct cyttsp5_core_platform_data *pdata,
        struct device *dev, cyttsp5_platform_read read)
{
    int retry = 3;
    int rc;
    char buf[1];

    while (retry--) {
        /* Perform reset, wait for 100 ms and perform read */
        TS_LOG_INFO("%s: Performing a reset\n", __func__);
        pdata->xres(pdata, dev);
        msleep(100);
        rc = read(dev, buf, 1);
        if (!rc)
            return 0;

        TS_LOG_INFO("%s: Read unsuccessful, try=%d\n",
            __func__, 3 - retry);
    }

    return rc;
}
#endif
