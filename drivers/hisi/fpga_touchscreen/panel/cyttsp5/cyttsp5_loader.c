/*
 * cyttsp5_loader.c
 * Cypress TrueTouch(TM) Standard Product V5 FW Loader Module.
 * For use with Cypress Txx5xx parts.
 * Supported parts include:
 * TMA5XX
 *
 * Copyright (C) 2012-2014 Cypress Semiconductor, Inc.
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
#include "cyttsp5_hw.h"
#include <linux/firmware.h>
#include <linux/fs.h>
#if defined (CONFIG_HUAWEI_DSM)
#include <dsm/dsm_pub.h>
#endif

#define CYTTSP5_LOADER_NAME "cyttsp5_loader"
#define CY_FW_MANUAL_UPGRADE_FILE_NAME "cyttsp5_fw_manual_upgrade"

/* Enable UPGRADE_FW_AND_CONFIG_IN_PROBE definition
 * to perform FW and config upgrade during probe
 * instead of scheduling a work for it
 */
/* #define UPGRADE_FW_AND_CONFIG_IN_PROBE */

#define CYTTSP5_AUTO_LOAD_FOR_CORRUPTED_FW 1
#define CYTTSP5_LOADER_FW_UPGRADE_RETRY_COUNT 3

#define CYTTSP5_FW_UPGRADE \
    (defined(CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_PLATFORM_FW_UPGRADE) \
    || defined(CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_BINARY_FW_UPGRADE))

#define CYTTSP5_TTCONFIG_UPGRADE \
    (defined(CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_PLATFORM_TTCONFIG_UPGRADE) \
    || defined(CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_MANUAL_TTCONFIG_UPGRADE))

static const u8 cyttsp5_security_key[] = {
    0xA5, 0x01, 0x02, 0x03, 0xFF, 0xFE, 0xFD, 0x5A
};

/* Timeout values in ms. */
#define CY_LDR_REQUEST_EXCLUSIVE_TIMEOUT        500
#define CY_LDR_SWITCH_TO_APP_MODE_TIMEOUT        300

#define CY_MAX_STATUS_SIZE                32

#define CY_DATA_MAX_ROW_SIZE            256
#define CY_DATA_ROW_SIZE                128

#define CY_ARRAY_ID_OFFSET                0
#define CY_ROW_NUM_OFFSET                1
#define CY_ROW_SIZE_OFFSET                3
#define CY_ROW_DATA_OFFSET                5

#define CY_POST_TT_CFG_CRC_MASK            0x2
#define FILENAME_LEN_MAX                 64
#define PANEL_NAME_LEN_MAX                16

#if defined (CONFIG_HUAWEI_DSM)
extern struct tp_dsm_info g_tp_dsm_info;
extern struct dsm_client *tp_cyp_dclient;
#endif

struct cyttsp5_loader_data {
    struct device *dev;
    struct cyttsp5_sysinfo *si;
    u8 status_buf[CY_MAX_STATUS_SIZE];
    struct completion int_running;
    struct completion calibration_complete;
#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_BINARY_FW_UPGRADE
    struct completion builtin_bin_fw_complete;
    int builtin_bin_fw_status;
    bool is_manual_upgrade_enabled;
    bool is_sd_upgrade_enabled;
#endif
    struct work_struct fw_and_config_upgrade;
    struct work_struct calibration_work;
    struct cyttsp5_loader_platform_data *loader_pdata;
#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_MANUAL_TTCONFIG_UPGRADE
    struct mutex config_lock;
    u8 *config_data;
    int config_size;
    bool config_loading;
#endif
};

struct cyttsp5_dev_id {
    u32 silicon_id;
    u8 rev_id;
    u32 bl_ver;
};

struct cyttsp5_hex_image {
    u8 array_id;
    u16 row_num;
    u16 row_size;
    u8 row_data[CY_DATA_ROW_SIZE];
} __packed;

static struct cyttsp5_core_commands *cmd;

static inline struct cyttsp5_loader_data *cyttsp5_get_loader_data(
        struct device *dev)
{
    return cyttsp5_get_dynamic_data(dev, CY_MODULE_LOADER);
}

struct cyttsp5_fw_info {
    u8 *product_name;
    u8 *chip_name;
    u8 panel_id;
    u8 *id2str;
    u8 *fw_name;
};

static struct cyttsp5_fw_info hw_fw_info[] = {
    {"x1s","tma568", 0,"oflim" ,"ts/x1s_TMA568_default.bin"},
    {"x1s","tma568", 1,"lens"  ,"ts/x1s_TMA568_default.bin"},
    {"Gemini","tma568",0,"oflim","ts/Gemini_TMA568_default.bin"},
    {"Gemini","tma568",1,"lens", "ts/Gemini_TMA568_default.bin"},
    {"Alice","CS445A", 0,"default","ts/Alice_CS445A_default.bin"},
    {"Alice","CS445A", 2,"default","ts/Alice_CS445A_default.bin"},
    {"Alice","CS445A", 5,"default","ts/Alice_CS445A_default.bin"},
    {"mozart","CS448", 0,"ofilm","ts/mozart_CS448_ofilm.bin"},
    {"mozart","CS448", 1,"truly","ts/mozart_CS448_truly.bin"},
};

#if CYTTSP5_FW_UPGRADE || CYTTSP5_TTCONFIG_UPGRADE
/*
 * return code:
 * -1: Do not upgrade firmware
 *  0: Version info same, let caller decide
 *  1: Do a firmware upgrade
 */
static int cyttsp5_check_firmware_version(struct device *dev,
        u32 fw_ver_new, u32 fw_revctrl_new)
{
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    u32 fw_ver_img;
    u32 fw_revctrl_img;

    fw_ver_img = ld->si->cydata.fw_ver_major << 8;
    fw_ver_img += ld->si->cydata.fw_ver_minor;

    TS_LOG_INFO("%s: Builtin fw version:0x%04X  IC fw version:0x%04X\n", __func__,
            fw_ver_img, fw_ver_new);

    if (fw_ver_new > fw_ver_img) {
        TS_LOG_INFO("%s: Builtin fw version is High!\n", __func__);
        return 1;
    }

    if (fw_ver_new < fw_ver_img) {
        TS_LOG_INFO("%s: Builtin fw version is Low!\n", __func__);
        return -1;
    }

    fw_revctrl_img = ld->si->cydata.revctrl;

    TS_LOG_INFO("%s: Builtin fw revctrl:0x%04X IC fw revctrl:0x%04X\n", __func__,
            fw_revctrl_img, fw_revctrl_new);

    if (fw_revctrl_new > fw_revctrl_img) {
        TS_LOG_INFO("%s: Builtin fw version is High!\n", __func__);
        return 1;
    }

    if (fw_revctrl_new < fw_revctrl_img) {
        TS_LOG_INFO("%s: Builtin fw version is Low!\n", __func__);
        return -1;
    }

    TS_LOG_INFO("%s: version info same\n", __func__);

    return 0;
}

static u8 cyttsp5_get_panel_id(struct device *dev)
{
    struct cyttsp5_core_data *cd = dev_get_drvdata(dev);

    return cd->panel_id;
}
static void cyttsp5_calibrate_idacs(struct work_struct *calibration_work)
{
    struct cyttsp5_loader_data *ld = container_of(calibration_work,
            struct cyttsp5_loader_data, calibration_work);
    struct device *dev = ld->dev;
    u8 mode;
    u8 status;
    int rc;

    rc = cmd->request_exclusive(dev, CY_LDR_REQUEST_EXCLUSIVE_TIMEOUT);
    if (rc < 0) {
        TS_LOG_ERR("%s:request_exclusive fail, rc:%d\n", __func__, rc);
        goto exit;
    }

    rc = cmd->nonhid_cmd->suspend_scanning(dev, 0);
    if (rc < 0) {
        TS_LOG_ERR("%s:suspend_scanning fail, rc:%d\n", __func__, rc);
        goto release;
    }

    for (mode = 0; mode < 3; mode++) {
        rc = cmd->nonhid_cmd->calibrate_idacs(dev, 0, mode, &status);
        if (rc < 0) {
            TS_LOG_ERR("%s:calibrate_idacs fail, rc:%d, mode:%d\n", __func__, rc, mode);
            goto release;
        }
    }

    rc = cmd->nonhid_cmd->resume_scanning(dev, 0);
    if (rc < 0) {
        TS_LOG_ERR("%s:resume_scanning fail, rc:%d\n", __func__, rc);
        goto release;
    }

    TS_LOG_INFO("%s: Calibration Done\n", __func__);

release:
    cmd->release_exclusive(dev);
exit:
    complete(&ld->calibration_complete);
}

static int cyttsp5_calibration_attention(struct device *dev)
{
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    int rc = 0;

    schedule_work(&ld->calibration_work);

    cmd->unsubscribe_attention(dev, CY_ATTEN_STARTUP, CY_MODULE_LOADER,
        cyttsp5_calibration_attention, 0);

    return rc;
}


#endif /* CYTTSP5_FW_UPGRADE || CYTTSP5_TTCONFIG_UPGRADE */

#if CYTTSP5_FW_UPGRADE
static u8 *cyttsp5_get_row_(struct device *dev, u8 *row_buf,
        u8 *image_buf, int size)
{
    memcpy(row_buf, image_buf, size);
    return image_buf + size;
}

static int cyttsp5_ldr_enter_(struct device *dev, struct cyttsp5_dev_id *dev_id)
{
    int rc;
    u8 return_data[8];
    u8 mode;

    dev_id->silicon_id = 0;
    dev_id->rev_id = 0;
    dev_id->bl_ver = 0;

    cmd->request_reset(dev);

    rc = cmd->request_get_mode(dev, 0, &mode);
    if (rc < 0)
        return rc;

    if (mode == CY_MODE_UNKNOWN)
        return -EINVAL;

    if (mode == CY_MODE_OPERATIONAL) {
        rc = cmd->nonhid_cmd->start_bl(dev, 0);
        if (rc < 0)
            return rc;
    }

    rc = cmd->nonhid_cmd->get_bl_info(dev, 0, return_data);
    if (rc < 0)
        return rc;

    dev_id->silicon_id = get_unaligned_le32(&return_data[0]);
    dev_id->rev_id = return_data[4];
    dev_id->bl_ver = return_data[5] + (return_data[6] << 8)
        + (return_data[7] << 16);

    return 0;
}

static int cyttsp5_ldr_init_(struct device *dev,
        struct cyttsp5_hex_image *row_image)
{
    return cmd->nonhid_cmd->initiate_bl(dev, 0, 8,
            (u8 *)cyttsp5_security_key, row_image->row_size,
            row_image->row_data);
}

static int cyttsp5_ldr_parse_row_(struct device *dev, u8 *row_buf,
    struct cyttsp5_hex_image *row_image)
{
    int rc = 0;

    row_image->array_id = row_buf[CY_ARRAY_ID_OFFSET];
    row_image->row_num = get_unaligned_be16(&row_buf[CY_ROW_NUM_OFFSET]);
    row_image->row_size = get_unaligned_be16(&row_buf[CY_ROW_SIZE_OFFSET]);

    if (row_image->row_size > ARRAY_SIZE(row_image->row_data)) {
        TS_LOG_ERR("%s: row data buffer overflow\n", __func__);
        rc = -EOVERFLOW;
        goto cyttsp5_ldr_parse_row_exit;
    }

    memcpy(row_image->row_data, &row_buf[CY_ROW_DATA_OFFSET],
           row_image->row_size);
cyttsp5_ldr_parse_row_exit:
    return rc;
}

static int cyttsp5_ldr_prog_row_(struct device *dev,
                 struct cyttsp5_hex_image *row_image)
{
    u16 length = row_image->row_size + 3;
    u8 data[3 + row_image->row_size];
    u8 offset = 0;

    data[offset++] = row_image->array_id;
    data[offset++] = LOW_BYTE(row_image->row_num);
    data[offset++] = HI_BYTE(row_image->row_num);
    memcpy(data + 3, row_image->row_data, row_image->row_size);
    return cmd->nonhid_cmd->prog_and_verify(dev, 0, length, data);
}

static int cyttsp5_ldr_verify_chksum_(struct device *dev)
{
    u8 result;
    int rc;

    rc = cmd->nonhid_cmd->verify_app_integrity(dev, 0, &result);
    if (rc)
        return rc;

    /* fail */
    if (result == 0)
        return -EINVAL;

    return 0;
}

static int cyttsp5_ldr_exit_(struct device *dev)
{
    return cmd->nonhid_cmd->launch_app(dev, 0);
}

static int cyttsp5_load_app_(struct device *dev, const u8 *fw, int fw_size)
{
    struct cyttsp5_dev_id *dev_id = NULL;
    struct cyttsp5_hex_image *row_image = NULL;
    u8 *row_buf = NULL;
    size_t image_rec_size = 0;
    size_t row_buf_size = CY_DATA_MAX_ROW_SIZE;
    int row_count = 0;
    u8 *p = NULL;
    u8 *last_row = NULL;
    int rc = 0;
    int rc_tmp = 0;

    TS_LOG_INFO("%s: Enter to load app\n", __func__);
    image_rec_size = sizeof(struct cyttsp5_hex_image);
    if (fw_size % image_rec_size != 0) {
        TS_LOG_ERR("%s: Firmware image is misaligned\n", __func__);
        TS_LOG_ERR("%s: fw_size = %d, image_rec_size = %ld\n",
                        __func__, fw_size, image_rec_size);
        rc = -EINVAL;
        goto _cyttsp5_load_app_error;
    }

    TS_LOG_INFO("%s: start load app\n", __func__);
#ifdef TTHE_TUNER_SUPPORT
    cmd->request_tthe_print(dev, NULL, 0, "start load app");
#endif

    row_buf = kzalloc(row_buf_size, GFP_KERNEL);
    row_image = kzalloc(sizeof(struct cyttsp5_hex_image), GFP_KERNEL);
    dev_id = kzalloc(sizeof(struct cyttsp5_dev_id), GFP_KERNEL);
    if (!row_buf || !row_image || !dev_id) {
        rc = -ENOMEM;
        goto _cyttsp5_load_app_exit;
    }

    cmd->request_stop_wd(dev);

    TS_LOG_INFO("%s: Send BL Loader Enter\n", __func__);
#ifdef TTHE_TUNER_SUPPORT
    cmd->request_tthe_print(dev, NULL, 0, "Send BL Loader Enter");
#endif
    rc = cyttsp5_ldr_enter_(dev, dev_id);
    if (rc) {
        TS_LOG_ERR("%s: Error cannot start Loader (ret=%d)\n",
                    __func__, rc);
        goto _cyttsp5_load_app_exit;
    }
    TS_LOG_DEBUG("%s: dev: silicon id=%08X rev=%02X bl=%08X\n",
                __func__, dev_id->silicon_id,
                dev_id->rev_id, dev_id->bl_ver);

    /* get last row */
    last_row = (u8 *)fw + fw_size - image_rec_size;
    cyttsp5_get_row_(dev, row_buf, last_row, image_rec_size);
    cyttsp5_ldr_parse_row_(dev, row_buf, row_image);

    /* initialise bootloader */
    rc = cyttsp5_ldr_init_(dev, row_image);
    if (rc) {
        TS_LOG_ERR("%s: Error cannot init Loader (ret=%d)\n", __func__, rc);
        goto _cyttsp5_load_app_exit;
    }

    TS_LOG_INFO("%s: Send BL Loader Blocks.\n", __func__);
#ifdef TTHE_TUNER_SUPPORT
    cmd->request_tthe_print(dev, NULL, 0, "Send BL Loader Blocks");
#endif
    p = (u8 *)fw;
    while (p < last_row) {
        /* Get row */
        TS_LOG_DEBUG("%s: read row=%d\n", __func__, ++row_count);
        memset(row_buf, 0, row_buf_size);
        p = cyttsp5_get_row_(dev, row_buf, p, image_rec_size);

        /* Parse row */
        TS_LOG_DEBUG("%s: p=%p buf=%p buf[0]=%02X\n", __func__, p, row_buf, row_buf[0]);
        rc = cyttsp5_ldr_parse_row_(dev, row_buf, row_image);
        TS_LOG_DEBUG("%s: array_id=%02X row_num=%04X(%d) row_size=%04X(%d)\n",
                    __func__, row_image->array_id,
                    row_image->row_num, row_image->row_num,
                    row_image->row_size, row_image->row_size);
        if (rc) {
            TS_LOG_ERR("%s: Parse Row Error (a=%d r=%d ret=%d\n",
                        __func__, row_image->array_id,
                        row_image->row_num, rc);
            goto _cyttsp5_load_app_exit;
        } else {
            TS_LOG_DEBUG("%s: Parse Row (a=%d r=%d ret=%d\n",
                        __func__, row_image->array_id,
                        row_image->row_num, rc);
        }

        /* program row */
        rc = cyttsp5_ldr_prog_row_(dev, row_image);
        if (rc) {
            TS_LOG_ERR("%s: Program Row Error (array=%d row=%d ret=%d)\n",
                        __func__, row_image->array_id,
                        row_image->row_num, rc);
            goto _cyttsp5_load_app_exit;
        }

        TS_LOG_DEBUG("%s: array=%d row_cnt=%d row_num=%04X\n",
            __func__, row_image->array_id, row_count,
            row_image->row_num);
    }

    /* exit loader */
    TS_LOG_INFO("%s: Send BL Loader Terminate.\n", __func__);
#ifdef TTHE_TUNER_SUPPORT
    cmd->request_tthe_print(dev, NULL, 0, "Send BL Loader Terminate");
#endif
    rc = cyttsp5_ldr_exit_(dev);
    if (rc) {
        TS_LOG_ERR("%s: Error on exit Loader (ret=%d)\n", __func__, rc);

        /* verify app checksum */
        rc_tmp = cyttsp5_ldr_verify_chksum_(dev);
        if (rc_tmp) {
            TS_LOG_ERR("%s: ldr_verify_chksum fail r=%d\n", __func__, rc_tmp);
        } else {
            TS_LOG_INFO("%s: APP Checksum Verified\n", __func__);
        }
    }

    TS_LOG_INFO("%s:load app successful.\n", __func__);

_cyttsp5_load_app_exit:
    kfree(row_buf);
    kfree(row_image);
    kfree(dev_id);
_cyttsp5_load_app_error:
    return rc;
}

static int cyttsp5_upgrade_firmware(struct device *dev, const u8 *fw_img,
        int fw_size)
{
    struct cyttsp5_core_data *cd = dev_get_drvdata(dev);
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    int retry = CYTTSP5_LOADER_FW_UPGRADE_RETRY_COUNT;
    bool wait_for_calibration_complete = false;
    int rc;

    TS_LOG_INFO("%s: cyttsp5 upgrade firmware\n", __func__);

    rc = cmd->request_exclusive(dev, CY_LDR_REQUEST_EXCLUSIVE_TIMEOUT);
    if (rc < 0) {
        #if defined (CONFIG_HUAWEI_DSM)
        g_tp_dsm_info.constraints_UPDATE_status = FWU_REQUEST_EXCLUSIVE_FAIL;
        #endif
        TS_LOG_ERR("%s: request_exclusive fail, rc = %d\n",
                    __func__,rc);
        goto exit;
    }

    while (retry--) {
        rc = cyttsp5_load_app_(dev, fw_img, fw_size);
        if (rc < 0) {
            TS_LOG_ERR("%s: Firmware update failed rc=%d, retry:%d\n",
                        __func__, rc, retry);
        } else {
            break;
        }
        msleep(20);
    }
    if (rc < 0) {
        TS_LOG_ERR("%s: Firmware update failed with error code %d\n",
                    __func__, rc);
    } else if (!cd->cpdata->no_cali_flag  && ld->loader_pdata &&
            (ld->loader_pdata->flags
             & CY_LOADER_FLAG_CALIBRATE_AFTER_FW_UPGRADE)) {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 13, 0))
        reinit_completion(&ld->calibration_complete);
#else
        INIT_COMPLETION(ld->calibration_complete);
#endif
        /* set up call back for startup */
        TS_LOG_DEBUG("%s: Adding callback for calibration\n", __func__);
        rc = cmd->subscribe_attention(dev, CY_ATTEN_STARTUP,
            CY_MODULE_LOADER, cyttsp5_calibration_attention, 0);
        if (rc) {
            TS_LOG_ERR("%s: Failed adding callback for calibration\n", __func__);
            TS_LOG_ERR("%s: No calibration will be performed\n", __func__);
            rc = 0;
        } else {
            wait_for_calibration_complete = true;
        }
    }

    cmd->release_exclusive(dev);

exit:
    if (!rc) {
        cmd->request_restart(dev, true);
    }


    if (wait_for_calibration_complete) {
        wait_for_completion(&ld->calibration_complete);
    }

    return rc;
}

static int cyttsp5_loader_attention(struct device *dev)
{
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);

    complete(&ld->int_running);
    return 0;
}
#endif /* CYTTSP5_FW_UPGRADE */

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_PLATFORM_FW_UPGRADE
static int cyttsp5_check_firmware_version_platform(struct device *dev,
        struct cyttsp5_touch_firmware *fw)
{
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    u32 fw_ver_new;
    u32 fw_revctrl_new;
    int upgrade;

    if (!ld->si) {
        TS_LOG_INFO("%s: No firmware infomation found, device FW may be corrupted\n",
            __func__);
        return CYTTSP5_AUTO_LOAD_FOR_CORRUPTED_FW;
    }

    fw_ver_new = get_unaligned_be16(fw->ver + 2);
    /* 4 middle bytes are not used */
    fw_revctrl_new = get_unaligned_be32(fw->ver + 8);

    upgrade = cyttsp5_check_firmware_version(dev, fw_ver_new,
        fw_revctrl_new);

    if (upgrade > 0) {
        TS_LOG_INFO("%s:Will upgrade firmvare\n", __func__);
        return 1;
    }

    return 0;
}

static struct cyttsp5_touch_firmware *cyttsp5_get_platform_firmware(
        struct device *dev)
{
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    struct cyttsp5_touch_firmware **fws;
    struct cyttsp5_touch_firmware *fw;
    u8 panel_id;

    panel_id = cyttsp5_get_panel_id(dev);
    if (panel_id == PANEL_ID_NOT_ENABLED) {
        TS_LOG_DEBUG("%s: Panel ID not enabled, using legacy firmware\n",
            __func__);
        return ld->loader_pdata->fw;
    }

    fws = ld->loader_pdata->fws;
    if (!fws) {
        TS_LOG_ERR("%s: No firmwares provided\n", __func__);
        return NULL;
    }

    /* Find FW according to the Panel ID */
    while ((fw = *fws++)) {
        if (fw->panel_id == panel_id) {
            TS_LOG_DEBUG("%s: Found matching fw:%p with Panel ID: 0x%02X\n",
                __func__, fw, fw->panel_id);
            return fw;
        }
        TS_LOG_DEBUG("%s: Found mismatching fw:%p with Panel ID: 0x%02X\n",
            __func__, fw, fw->panel_id);
    }

    return NULL;
}

static int upgrade_firmware_from_platform(struct device *dev,
        bool forced)
{
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    struct cyttsp5_touch_firmware *fw;
    int rc = -ENOSYS;
    int upgrade;

    TS_LOG_INFO("%s: upgrade firmware from platform start.\n",
                __func__);
    if (!ld->loader_pdata) {
        TS_LOG_ERR("%s: No loader platform data\n", __func__);
        return rc;
    }

    fw = cyttsp5_get_platform_firmware(dev);
    if (!fw || !fw->img || !fw->size) {
        TS_LOG_ERR("%s: No platform firmware\n", __func__);
        return rc;
    }

    if (!fw->ver || !fw->vsize) {
        TS_LOG_ERR("%s: No platform firmware version\n",
            __func__);
        return rc;
    }

    if (forced)
        upgrade = forced;
    else
        upgrade = cyttsp5_check_firmware_version_platform(dev, fw);

    if (upgrade)
        return cyttsp5_upgrade_firmware(dev, fw->img, fw->size);

    return rc;
}
#endif /* CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_PLATFORM_FW_UPGRADE */

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_BINARY_FW_UPGRADE
static void _cyttsp5_firmware_cont(const struct firmware *fw, void *context)
{
    struct device *dev = context;
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    u8 header_size = 0;

    if (!fw) {
        #if defined (CONFIG_HUAWEI_DSM)
        g_tp_dsm_info.constraints_UPDATE_status = FWU_FW_CONT_ERROR;
        #endif
        TS_LOG_ERR("%s: Missing parameter\n", __func__);
        goto cyttsp5_firmware_cont_exit;
    }

    if (!fw->data || !fw->size) {
        #if defined (CONFIG_HUAWEI_DSM)
        g_tp_dsm_info.constraints_UPDATE_status = FWU_FW_CONT_ERROR;
        #endif
        TS_LOG_ERR("%s: No firmware received\n", __func__);
        goto cyttsp5_firmware_cont_release_exit;
    }

    header_size = fw->data[0];
    if (header_size >= (fw->size + 1)) {
        #if defined (CONFIG_HUAWEI_DSM)
        g_tp_dsm_info.constraints_UPDATE_status = FWU_FW_CONT_ERROR;
        #endif
        TS_LOG_ERR("%s: Firmware format is invalid\n", __func__);
        goto cyttsp5_firmware_cont_release_exit;
    }

    cyttsp5_upgrade_firmware(dev, &(fw->data[header_size + 1]),
        fw->size - (header_size + 1));

cyttsp5_firmware_cont_release_exit:
    release_firmware(fw);

cyttsp5_firmware_cont_exit:
    ld->is_manual_upgrade_enabled = 0;
}

static int cyttsp5_check_firmware_version_builtin(struct device *dev,
        const struct firmware *fw)
{
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    u32 fw_ver_new;
    u32 fw_revctrl_new;
    int upgrade;

    if (!ld->si) {
        #if defined (CONFIG_HUAWEI_DSM)
        g_tp_dsm_info.constraints_UPDATE_status = FWU_GET_SYSINFO_FAIL;
        #endif
        TS_LOG_INFO("%s: No firmware infomation found, device FW may be corrupted\n",
            __func__);
        return CYTTSP5_AUTO_LOAD_FOR_CORRUPTED_FW;
    }

    fw_ver_new = get_unaligned_be16(fw->data + 3);
    /* 4 middle bytes are not used */
    fw_revctrl_new = get_unaligned_be32(fw->data + 9);

    upgrade = cyttsp5_check_firmware_version(dev, fw_ver_new, fw_revctrl_new);

    if (upgrade > 0) {
        TS_LOG_INFO("%s: fw will upgrade!\n", __func__);
        return 1;
    }

    TS_LOG_INFO("%s: fw will not upgrade!\n", __func__);
    return 0;
}

static void _cyttsp5_firmware_cont_builtin(const struct firmware *fw,
        void *context)
{
    struct device *dev = context;
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    int upgrade;

    ld->builtin_bin_fw_status = -EINVAL;

    if (!fw) {
        #if defined (CONFIG_HUAWEI_DSM)
        g_tp_dsm_info.constraints_UPDATE_status = FWU_FW_CONT_BUILTIN_ERROR;
        #endif
        TS_LOG_INFO("%s: No builtin firmware\n", __func__);
        goto _cyttsp5_firmware_cont_builtin_exit;
    }

    if (!fw->data || !fw->size) {
        #if defined (CONFIG_HUAWEI_DSM)
        g_tp_dsm_info.constraints_UPDATE_status = FWU_FW_CONT_BUILTIN_ERROR;
        #endif
        TS_LOG_ERR("%s: Invalid builtin firmware\n", __func__);
        goto _cyttsp5_firmware_cont_builtin_exit;
    }

    TS_LOG_INFO("%s: Found firmware\n", __func__);

    upgrade = cyttsp5_check_firmware_version_builtin(dev, fw);
    if (upgrade) {
        _cyttsp5_firmware_cont(fw, dev);
        ld->builtin_bin_fw_status = 0;
        complete(&ld->builtin_bin_fw_complete);
        return;
    }

    ld->builtin_bin_fw_status = 0;

_cyttsp5_firmware_cont_builtin_exit:
    release_firmware(fw);
    complete(&ld->builtin_bin_fw_complete);
}

static int upgrade_firmware_from_class(struct device *dev)
{
    int retval = 0;

    TS_LOG_INFO( "%s: Enabling firmware class loader\n", __func__);

    retval = request_firmware_nowait(THIS_MODULE, FW_ACTION_NOHOTPLUG,
            CY_FW_MANUAL_UPGRADE_FILE_NAME, dev, GFP_KERNEL, dev,
            _cyttsp5_firmware_cont);
    if (retval < 0) {
        TS_LOG_ERR("%s: Fail request firmware class file load, ret = %d\n",
                    __func__,retval);
        return retval;
    }

    return 0;
}

/*
 * Generates binary FW filename as following:
 * - Panel ID not enabled: cyttsp5_fw.bin
 * - Panel ID enabled: cyttsp5_fw_pidXX.bin
 */
static char *generate_firmware_filename(struct device *dev)
{
    const char *product_name = NULL;
    const char *chip_name = NULL;
    struct cyttsp5_platform_data *pdata = cyttsp5_get_platform_data(dev);
    struct cyttsp5_core_platform_data *core_pdata = pdata->core_pdata;
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);

    u8 panel_id = 0;
    int retval = -1;
    int length = 0;
    int index = 0;
    char *filename = NULL;
    bool findfirmware = false;

    filename = kzalloc(FILENAME_LEN_MAX, GFP_KERNEL);
    if (!filename) {
        TS_LOG_ERR("%s: kzalloc fail\n", __func__);
        return NULL;
    }

    TS_LOG_INFO("%s: start to generate_firmware_filename.\n",__func__);

    panel_id = cyttsp5_get_panel_id(dev);
    TS_LOG_INFO("%s: panel_id = %d \n", __func__, panel_id);

    product_name = core_pdata->product_name;
    TS_LOG_INFO("%s: product_name = %s\n", __func__, product_name);

    chip_name = core_pdata->chip_name;
    TS_LOG_INFO("%s: chip_name = %s\n", __func__, chip_name);

    if (!ld->si) {
        #if defined (CONFIG_HUAWEI_DSM)
        g_tp_dsm_info.constraints_UPDATE_status = FWU_GET_SYSINFO_FAIL;
        #endif
        snprintf(filename, FILENAME_LEN_MAX, "ts/%s_%s_default.bin", product_name, chip_name);
        TS_LOG_INFO("%s: sysinfo is null, use default firmware: %s\n", __func__, filename);
    } else {
        length = sizeof(hw_fw_info)/sizeof(struct cyttsp5_fw_info);
        for(index = 0; index < length; index++) {
        retval = strncasecmp(hw_fw_info[index].product_name, product_name, strlen(hw_fw_info[index].product_name));
            if(retval == 0 && hw_fw_info[index].panel_id == panel_id){
                snprintf(filename, FILENAME_LEN_MAX, "%s", hw_fw_info[index].fw_name);
                findfirmware = true;
                break;
            }
        }
    }

    if ((ld->si) && (findfirmware == false)) {
        snprintf(filename, FILENAME_LEN_MAX, "ts/%s_%s_default.bin", product_name, chip_name);
        TS_LOG_INFO("%s: no matching firmware, use default firmware: %s\n", __func__, filename);
    }

    if(strlen(filename) < strlen("ts/x_x_x.bin")){
        TS_LOG_INFO("%s: Filename = %s is inval.\n", __func__, filename);
        return NULL;
    }

    TS_LOG_INFO("%s: Filename: %s\n", __func__, filename);

    return filename;
}

static int upgrade_firmware_from_builtin(struct device *dev)
{
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    char *filename = NULL;
    int retval = 0;

    TS_LOG_INFO("%s: upgrade firmware from buildin start.\n", __func__);

    filename = generate_firmware_filename(dev);
    if (!filename) {
        #if defined (CONFIG_HUAWEI_DSM)
        g_tp_dsm_info.constraints_UPDATE_status = FWU_GENERATE_FW_NAME_FAIL;
        #endif
        TS_LOG_ERR("%s: generate firmware filename fail\n", __func__);
        return -ENOMEM;
    }

    retval = request_firmware_nowait(THIS_MODULE, FW_ACTION_HOTPLUG,
            filename, dev, GFP_KERNEL, dev,
            _cyttsp5_firmware_cont_builtin);
    if (retval < 0) {
        #if defined (CONFIG_HUAWEI_DSM)
        g_tp_dsm_info.constraints_UPDATE_status = FWU_REQUEST_FW_FAIL;
        #endif
        TS_LOG_ERR("%s: Fail request firmware class file load, ret = %d\n",
                    __func__,retval);
        goto exit;
    }

    /* wait until FW binary upgrade finishes */
    wait_for_completion(&ld->builtin_bin_fw_complete);

    retval = ld->builtin_bin_fw_status;

exit:
    kfree(filename);

    return retval;
}
#endif /* CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_BINARY_FW_UPGRADE */

#if CYTTSP5_TTCONFIG_UPGRADE
static int cyttsp5_write_config_row_(struct device *dev, u8 ebid,
        u16 row_number, u16 row_size, u8 *data)
{
    int rc;
    u16 actual_write_len;

    rc = cmd->nonhid_cmd->write_conf_block(dev, 0, row_number,
            row_size, ebid, data, (u8 *)cyttsp5_security_key,
            &actual_write_len);
    if (rc) {
        TS_LOG_ERR("%s: Fail Put EBID=%d row=%d cmd fail r=%d\n",
            __func__, ebid, row_number, rc);
        return rc;
    }

    if (actual_write_len != row_size) {
        TS_LOG_ERR("%s: Fail Put EBID=%d row=%d wrong write size=%d\n",
            __func__, ebid, row_number, actual_write_len);
        rc = -EINVAL;
    }

    return rc;
}

static int cyttsp5_upgrade_ttconfig(struct device *dev,
        const u8 *ttconfig_data, int ttconfig_size)
{
    struct cyttsp5_core_data *cd = dev_get_drvdata(dev);
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    bool wait_for_calibration_complete = false;
    u8 ebid = CY_TCH_PARM_EBID;
    u16 row_size = CY_DATA_ROW_SIZE;
    u16 table_size;
    u16 row_count;
    u16 residue;
    u8 *row_buf;
    u8 verify_crc_status;
    u16 calculated_crc;
    u16 stored_crc;
    int rc = 0;
    int i;

    table_size = ttconfig_size;
    row_count = table_size / row_size;
    row_buf = (u8 *)ttconfig_data;
    TS_LOG_INFO("%s: size:%d row_size=%d row_count=%d\n",
        __func__, table_size, row_size, row_count);


    rc = cmd->request_exclusive(dev, CY_LDR_REQUEST_EXCLUSIVE_TIMEOUT);
    if (rc < 0) {
        TS_LOG_ERR("%s: request_exclusive fail, rc = %d\n", __func__,rc);
        goto exit;
    }

    rc = cmd->nonhid_cmd->suspend_scanning(dev, 0);
    if (rc < 0) {
        TS_LOG_ERR("%s: suspend_scanning fail, rc = %d\n", __func__,rc);
        goto release;
    }

    for (i = 0; i < row_count; i++) {
        TS_LOG_INFO( "%s: row=%d size=%d\n", __func__, i, row_size);
        rc = cyttsp5_write_config_row_(dev, ebid, i, row_size, row_buf);
        if (rc) {
            TS_LOG_ERR( "%s: Fail put row=%d r=%d\n", __func__, i, rc);
            break;
        }
        row_buf += row_size;
    }

    if (!rc) {
        residue = table_size % row_size;
        TS_LOG_INFO( "%s: row=%d size=%d\n", __func__, i, residue);
        rc = cyttsp5_write_config_row_(dev, ebid, i, residue, row_buf);
        row_count++;

        if (rc) {
            TS_LOG_ERR( "%s: Fail put row=%d r=%d\n", __func__, i, rc);
        }
    }

    if (!rc)
        TS_LOG_DEBUG("%s: TT_CFG updated: rows:%d bytes:%d\n",
            __func__, row_count, table_size);

    rc = cmd->nonhid_cmd->verify_config_block_crc(dev, 0, ebid,
            &verify_crc_status, &calculated_crc, &stored_crc);
    if (rc || verify_crc_status)
        TS_LOG_ERR("%s: CRC Failed, ebid=%d, status=%d, scrc=%X ccrc=%X\n",
            __func__, ebid, verify_crc_status,
            calculated_crc, stored_crc);
    else
        TS_LOG_DEBUG("%s: CRC PASS, ebid=%d, status=%d, scrc=%X ccrc=%X\n",
            __func__, ebid, verify_crc_status,
            calculated_crc, stored_crc);

    rc = cmd->nonhid_cmd->resume_scanning(dev, 0);
    if (rc < 0) {
        TS_LOG_ERR( "%s: resume_scanning fail, rc = %d\n", __func__, rc);
        goto release;
    }

    if (!cd->cpdata->no_cali_flag && ld->loader_pdata &&
            (ld->loader_pdata->flags
             & CY_LOADER_FLAG_CALIBRATE_AFTER_TTCONFIG_UPGRADE)) {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 13, 0))
        reinit_completion(&ld->calibration_complete);
#else
        INIT_COMPLETION(ld->calibration_complete);
#endif
        /* set up call back for startup */
        TS_LOG_DEBUG( "%s: Adding callback for calibration\n", __func__);
        rc = cmd->subscribe_attention(dev, CY_ATTEN_STARTUP,
            CY_MODULE_LOADER, cyttsp5_calibration_attention, 0);
        if (rc) {
            TS_LOG_ERR("%s: Failed adding callback for calibration\n",
                __func__);
            TS_LOG_ERR("%s: No calibration will be performed\n",
                __func__);
            rc = 0;
        } else
            wait_for_calibration_complete = true;
    }

release:
    cmd->release_exclusive(dev);

exit:
    if (!rc)
        cmd->request_restart(dev, true);


    if (wait_for_calibration_complete)
        wait_for_completion(&ld->calibration_complete);

    return rc;
}
#endif /* CYTTSP5_TTCONFIG_UPGRADE */

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_PLATFORM_TTCONFIG_UPGRADE
static int cyttsp5_get_ttconfig_crc(struct device *dev,
        const u8 *ttconfig_data, int ttconfig_size, u16 *crc)
{
    u16 crc_loc;

    crc_loc = get_unaligned_le16(&ttconfig_data[2]);
    if (ttconfig_size < crc_loc + 2)
        return -EINVAL;

    *crc = get_unaligned_le16(&ttconfig_data[crc_loc]);

    return 0;
}

static int cyttsp5_get_ttconfig_version(struct device *dev,
        const u8 *ttconfig_data, int ttconfig_size, u16 *version)
{
    if (ttconfig_size < CY_TTCONFIG_VERSION_OFFSET
            + CY_TTCONFIG_VERSION_SIZE)
        return -EINVAL;

    *version = get_unaligned_le16(
        &ttconfig_data[CY_TTCONFIG_VERSION_OFFSET]);

    return 0;
}

static int cyttsp5_check_ttconfig_version(struct device *dev,
        const u8 *ttconfig_data, int ttconfig_size)
{
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    u16 cfg_crc_new;
    int rc;

    if (!ld->si)
        return 0;

    /* Check for config version */
    //if (ld->loader_pdata->flags &
    //        CY_LOADER_FLAG_CHECK_TTCONFIG_VERSION) {
    if (0) {
        u16 cfg_ver_new;

        rc = cyttsp5_get_ttconfig_version(dev, ttconfig_data,
                ttconfig_size, &cfg_ver_new);
        if (rc)
            return 0;

        TS_LOG_INFO( "%s: img_ver:0x%04X new_ver:0x%04X\n",
            __func__, ld->si->cydata.fw_ver_conf, cfg_ver_new);

        /* Check if config version is newer */
        if (cfg_ver_new > ld->si->cydata.fw_ver_conf) {
            TS_LOG_INFO( "%s: Config version newer, will upgrade\n", __func__);
            return 1;
        }

        TS_LOG_INFO("%s: Config version is identical or older, will NOT upgrade\n",
            __func__);
    /* Check for config CRC */
    } else {
        rc = cyttsp5_get_ttconfig_crc(dev, ttconfig_data,
                ttconfig_size, &cfg_crc_new);
        if (rc) {
            TS_LOG_INFO( "%s: crc check fail, will not upgrade ttconfig\n", __func__);
            return 0;
        }

        TS_LOG_INFO("%s: img_crc:0x%04X new_crc:0x%04X\n",
            __func__, ld->si->ttconfig.crc, cfg_crc_new);

        if (cfg_crc_new != ld->si->ttconfig.crc) {
            TS_LOG_INFO("%s: Config CRC different, will upgrade\n",
                __func__);
            return 1;
        }

        TS_LOG_INFO("%s: Config CRC equal, will NOT upgrade\n",
            __func__);
    }

    return 0;
}

static int cyttsp5_check_ttconfig_version_platform(struct device *dev,
        struct cyttsp5_touch_config *ttconfig)
{
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    u32 fw_ver_config;
    u32 fw_revctrl_config;

    if (!ld->si) {
        TS_LOG_INFO( "%s: No firmware infomation found\n", __func__);
        return 0;
    }

    fw_ver_config = get_unaligned_be16(ttconfig->fw_ver + 2);
    /* 4 middle bytes are not used */
    fw_revctrl_config = get_unaligned_be32(ttconfig->fw_ver + 8);

    /* FW versions should match */
    if (cyttsp5_check_firmware_version(dev, fw_ver_config, fw_revctrl_config)) {
        TS_LOG_ERR( "%s: FW and ttconfig versions mismatch, will not upgrade\n", __func__);
        return 0;
    }

    /* Check PowerOn Self Test, TT_CFG CRC bit */
    if ((ld->si->cydata.post_code & CY_POST_TT_CFG_CRC_MASK) == 0) {
        TS_LOG_DEBUG("%s: POST, TT_CFG failed (%X), will upgrade\n",
            __func__, ld->si->cydata.post_code);
        return 1;
    }

    return cyttsp5_check_ttconfig_version(dev, ttconfig->param_regs->data,
            ttconfig->param_regs->size);
}

static struct cyttsp5_touch_config *cyttsp5_get_platform_ttconfig(
        struct device *dev)
{
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    struct cyttsp5_touch_config **ttconfigs;
    struct cyttsp5_touch_config *ttconfig;

    struct cyttsp5_platform_data *pdata = cyttsp5_get_platform_data(dev);
    struct cyttsp5_core_platform_data *core_pdata = pdata->core_pdata;
    u8 panel_id;
    const char *product_name = NULL;

    panel_id = cyttsp5_get_panel_id(dev);
    if (panel_id == PANEL_ID_NOT_ENABLED) {
        /* TODO: Make debug message */
        TS_LOG_INFO("%s: Panel ID not enabled, using legacy ttconfig\n",
            __func__);
        return ld->loader_pdata->ttconfig;
    }

    product_name = core_pdata->product_name;

    ttconfigs = ld->loader_pdata->ttconfigs;
    if (!ttconfigs) {
        TS_LOG_ERR("%s: not ttconfigs data found\n", __func__);
        return NULL;
    }

    /* Find TT config according to the Panel ID */
    while ((ttconfig = *ttconfigs++)) {

        TS_LOG_INFO("%s: ttconfig->panel_id = %d,panel_id = %d.\n", __func__,ttconfig->panel_id, panel_id);
        TS_LOG_INFO("%s: ttconfig->product_name = %s,product_name = %s.\n", __func__,ttconfig->product_name, product_name);
        if (ttconfig->panel_id == panel_id
            && strcmp(product_name, ttconfig->product_name) == 0) {

            /* TODO: Make debug message */
            TS_LOG_INFO("%s: Found matching ttconfig:%p with Panel ID: 0x%02X\n",
                __func__, ttconfig, ttconfig->panel_id);
            return ttconfig;
        }
        TS_LOG_DEBUG("%s: Found mismatching ttconfig:%p with Panel ID: 0x%02X\n",
            __func__, ttconfig, ttconfig->panel_id);
    }

    return NULL;
}

static int upgrade_ttconfig_from_platform(struct device *dev)
{
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    struct cyttsp5_touch_config *ttconfig;
    struct touch_settings *param_regs;
    struct cyttsp5_touch_fw;
    int rc = -ENOSYS;
    int upgrade;

    TS_LOG_INFO("%s: upgrade ttconfig from platform start.\n",__func__);
    if (!ld->loader_pdata) {
        TS_LOG_INFO("%s: No loader platform data\n", __func__);
        return rc;
    }

    ttconfig = cyttsp5_get_platform_ttconfig(dev);
    if (!ttconfig) {
        TS_LOG_INFO("%s: No ttconfig data\n", __func__);
        return rc;
    }

    param_regs = ttconfig->param_regs;
    if (!param_regs) {
        TS_LOG_INFO("%s: No touch parameters\n", __func__);
        return rc;
    }

    if (!param_regs->data || !param_regs->size) {
        TS_LOG_INFO("%s: Invalid touch parameters\n", __func__);
        return rc;
    }

    if (!ttconfig->fw_ver || !ttconfig->fw_vsize) {
        TS_LOG_INFO("%s: Invalid FW version for touch parameters\n",
            __func__);
        return rc;
    }

    upgrade = cyttsp5_check_ttconfig_version_platform(dev, ttconfig);
    if (upgrade) {
        TS_LOG_INFO("%s: upgrade ttconfig\n", __func__);
        rc = cyttsp5_upgrade_ttconfig(dev, param_regs->data, param_regs->size);
        TS_LOG_INFO("%s: upgrade ttconfig, rc = %d\n", __func__,rc);
        return rc;
    }

    TS_LOG_INFO("%s: will not upgrade ttconfig\n", __func__);
    return rc;
}
#endif /* CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_PLATFORM_TTCONFIG_UPGRADE */

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_MANUAL_TTCONFIG_UPGRADE
static ssize_t cyttsp5_config_data_write(struct file *filp,
        struct kobject *kobj, struct bin_attribute *bin_attr,
        char *buf, loff_t offset, size_t count)
{
    struct device *dev = container_of(kobj, struct device, kobj);
    struct cyttsp5_loader_data *data = cyttsp5_get_loader_data(dev);
    u8 *p;

    TS_LOG_DEBUG("%s: offset:%lld count:%zu\n", __func__, offset, count);

    mutex_lock(&data->config_lock);

    if (!data->config_loading) {
        mutex_unlock(&data->config_lock);
        return -ENODEV;
    }

    p = krealloc(data->config_data, offset + count, GFP_KERNEL);
    if (!p) {
        kfree(data->config_data);
        data->config_data = NULL;
        mutex_unlock(&data->config_lock);
        return -ENOMEM;
    }
    data->config_data = p;

    memcpy(&data->config_data[offset], buf, count);
    data->config_size += count;

    mutex_unlock(&data->config_lock);

    return count;
}

static struct bin_attribute bin_attr_config_data = {
    .attr = {
        .name = "config_data",
        .mode = S_IWUSR,
    },
    .size = 0,
    .write = cyttsp5_config_data_write,
};

static ssize_t cyttsp5_config_loading_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    bool config_loading;

    mutex_lock(&ld->config_lock);
    config_loading = ld->config_loading;
    mutex_unlock(&ld->config_lock);

    return sprintf(buf, "%d\n", config_loading);
}

static int cyttsp5_verify_ttconfig_binary(struct device *dev,
        u8 *bin_config_data, int bin_config_size, u8 **start, int *len)
{
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    int header_size;
    u16 config_size;
    u32 fw_ver_config;
    u32 fw_revctrl_config;

    if (!ld->si) {
        TS_LOG_ERR("%s: No firmware infomation found, device FW may be corrupted\n",
            __func__);
        return -ENODEV;
    }

    /*
     * We need 11 bytes for FW version control info and at
     * least 6 bytes in config (Length + Max Length + CRC)
     */
    header_size = bin_config_data[0] + 1;
    if (header_size < 11 || header_size >= bin_config_size - 6) {
        TS_LOG_ERR("%s: Invalid header size %d\n", __func__,
            header_size);
        return -EINVAL;
    }

    fw_ver_config = get_unaligned_be16(&bin_config_data[1]);
    /* 4 middle bytes are not used */
    fw_revctrl_config = get_unaligned_be32(&bin_config_data[7]);

    /* FW versions should match */
    if (cyttsp5_check_firmware_version(dev, fw_ver_config,
            fw_revctrl_config)) {
        TS_LOG_ERR("%s: FW versions mismatch\n", __func__);
        return -EINVAL;
    }

    config_size = get_unaligned_le16(&bin_config_data[header_size]);
    /* Perform a simple size check (2 bytes for CRC) */
    if (config_size != bin_config_size - header_size - 2) {
        TS_LOG_ERR("%s: Config size invalid\n", __func__);
        return -EINVAL;
    }

    *start = &bin_config_data[header_size];
    *len = bin_config_size - header_size;

    return 0;
}

/*
 * 1: Start loading TT Config
 * 0: End loading TT Config and perform upgrade
 *-1: Exit loading
 */
static ssize_t cyttsp5_config_loading_store(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t size)
{
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    long value;
    u8 *start;
    int length;
    int rc;

    rc = kstrtol(buf, 10, &value);
    if (rc < 0 || value < -1 || value > 1) {
        TS_LOG_ERR("%s: Invalid value\n", __func__);
        return size;
    }

    mutex_lock(&ld->config_lock);

    if (value == 1)
        ld->config_loading = true;
    else if (value == -1)
        ld->config_loading = false;
    else if (value == 0 && ld->config_loading) {
        ld->config_loading = false;
        if (ld->config_size == 0) {
            TS_LOG_ERR("%s: No config data\n", __func__);
            goto exit_free;
        }

        rc = cyttsp5_verify_ttconfig_binary(dev,
                ld->config_data, ld->config_size,
                &start, &length);
        if (rc)
            goto exit_free;

        rc = cyttsp5_upgrade_ttconfig(dev, start, length);
    }

exit_free:
    kfree(ld->config_data);
    ld->config_data = NULL;
    ld->config_size = 0;

    mutex_unlock(&ld->config_lock);

    if (rc)
        return rc;

    return size;
}

static DEVICE_ATTR(config_loading, 0664,
    cyttsp5_config_loading_show, cyttsp5_config_loading_store);
#endif /* CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_MANUAL_TTCONFIG_UPGRADE */

static void cyttsp5_fw_and_config_upgrade(
        struct work_struct *fw_and_config_upgrade)
{
    struct cyttsp5_loader_data *ld = container_of(fw_and_config_upgrade,
            struct cyttsp5_loader_data, fw_and_config_upgrade);
    struct device *dev = ld->dev;
    struct cyttsp5_platform_data *pdata = dev_get_platdata(dev);
    struct cyttsp5_core_platform_data *core_pdata = pdata->core_pdata;
    struct cyttsp5_core_data *cd = dev_get_drvdata(dev);

    int retval = -1;

    ld->si = cmd->request_sysinfo(dev);
    if (!ld->si) {
        TS_LOG_ERR("%s: Fail get sysinfo pointer from core\n",__func__);
    }

    mutex_lock(&cd->system_lock);
    cd->fw_upgrade_flag = FW_UPGRADE_RUNNING;
    mutex_unlock(&cd->system_lock);
#if !CYTTSP5_FW_UPGRADE
    TS_LOG_INFO("%s: No FW upgrade method selected!\n", __func__);
#endif

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_PLATFORM_FW_UPGRADE
    if (!upgrade_firmware_from_platform(dev, false)) {
        TS_LOG_ERR("%s: PLATFORM_FW_UPGRADE fail\n", __func__);
    } else {
        TS_LOG_INFO("%s: update firmware from platform\n", __func__);
    }
#endif

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_BINARY_FW_UPGRADE
    retval = upgrade_firmware_from_builtin(dev);
    if (!retval) {
        TS_LOG_INFO("%s: firmware have upgraded successful.\n", __func__);
    } else {
#if defined (CONFIG_HUAWEI_DSM)
        if (!dsm_client_ocuppy(tp_cyp_dclient)) {
            cyttsp5_dsm_record_basic_err_info(dev);
            dsm_client_record(tp_cyp_dclient, "fw update result:failed\nretval is %d\nupdata status is %d\n",\
            retval,\
            g_tp_dsm_info.constraints_UPDATE_status);
            dsm_client_notify(tp_cyp_dclient, DSM_TP_FWUPDATE_ERROR_NO);
        }
#endif
        TS_LOG_INFO("%s: firmware haven't upgraded, retval = %d\n", __func__,retval);
    }
#endif

    if(core_pdata->upgrade_ttconfig == 0){
        TS_LOG_INFO("%s: Not need to upgrade ttconfig,return here.\n", __func__);
        goto exit;
    }

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_PLATFORM_TTCONFIG_UPGRADE
    retval = upgrade_ttconfig_from_platform(dev);
    if (!retval) {
        TS_LOG_INFO("%s: ttconfig have upgreded\n", __func__);
    } else {
        TS_LOG_INFO("%s: ttconfig haven't upgrade, retval = %d\n", __func__,retval);
    }

#endif
exit:
    mutex_lock(&cd->system_lock);
    cd->fw_upgrade_flag = FW_UPGRADE_NOT_RUNNING;
    mutex_unlock(&cd->system_lock);
}

#if CYTTSP5_FW_UPGRADE
static int cyttsp5_fw_upgrade_cb(struct device *dev)
{
#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_PLATFORM_FW_UPGRADE
    if (!upgrade_firmware_from_platform(dev, false))
        return 1;
#endif

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_BINARY_FW_UPGRADE
    if (!upgrade_firmware_from_builtin(dev))
        return 1;
#endif
    return 0;
}
#endif

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_PLATFORM_FW_UPGRADE
static ssize_t cyttsp5_forced_upgrade_store(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t size)
{
    int rc = upgrade_firmware_from_platform(dev, true);

    if (rc)
        return rc;
    return size;
}

static DEVICE_ATTR(forced_upgrade, 0220,NULL, cyttsp5_forced_upgrade_store);
#endif

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_BINARY_FW_UPGRADE
static ssize_t cyttsp5_manual_upgrade_store(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t size)
{
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    int rc;

    TS_LOG_ERR("%s: Enter manual_upgrade\n", __func__);
    if (ld->is_manual_upgrade_enabled) {
        TS_LOG_ERR("%s: System is doing fw upgrade, please try later\n",
                    __func__);
        return -EBUSY;
    }

    ld->is_manual_upgrade_enabled = 1;

    rc = upgrade_firmware_from_class(ld->dev);

    if (rc < 0) {
        TS_LOG_ERR("%s: upgrade firmware from class fail\n", __func__);
        ld->is_manual_upgrade_enabled = 0;
    }

    return size;
}

static DEVICE_ATTR(manual_upgrade, 0220, NULL, cyttsp5_manual_upgrade_store);

static int cyttsp5_file_open_firmware(u8 *file_path,u8 *databuf,
                int *file_size)
{
    struct file *filp = NULL;
    struct inode *inode = NULL;
    unsigned int file_len = 0;
    mm_segment_t oldfs;
    int retval = 0;

    if(file_path == NULL || databuf == NULL){
        TS_LOG_ERR("%s: path || buf is NULL.\n",__func__);
        return -EINVAL;
    }

    TS_LOG_INFO("%s: path = %s.\n",__func__,file_path);

    // open file
    oldfs = get_fs();
    set_fs(KERNEL_DS);
    filp = filp_open(file_path, O_RDONLY, S_IRUSR);
    if (IS_ERR(filp)){
        TS_LOG_ERR("%s: open %s error.\n", __func__,file_path);
        retval = -EIO;
        goto err;
    }

    if (filp->f_op == NULL) {
        TS_LOG_ERR("%s: File Operation Method Error\n", __func__);
        retval = -EINVAL;
        goto exit;
    }

    inode = filp->f_path.dentry->d_inode;
    if (inode == NULL) {
        TS_LOG_ERR("%s: Get inode from filp failed\n", __func__);
        retval = -EINVAL;
        goto exit;
    }

    //Get file size
    file_len = i_size_read(inode->i_mapping->host);
    if (file_len == 0){
        TS_LOG_ERR("%s: file size error,file_len = %d\n", __func__,file_len);
        retval = -EINVAL;
        goto exit;
    }

    // read image data to kernel */
    if (filp->f_op->read(filp, databuf, file_len, &filp->f_pos) != file_len) {
        TS_LOG_ERR("%s: file read error.\n", __func__);
        retval = -EINVAL;
        goto exit;
    }

    *file_size = file_len;

exit:
    filp_close(filp, NULL);
err:
    set_fs(oldfs);
    return retval;
}
static int cyttsp5_fw_update_from_sdcard(struct device *dev,u8 *file_path,bool update_flag)
{
    int retval;
    u8 *fw_data = NULL;
    int header_size = 0;
    int fw_size = 0;
	u32 fw_ver_new = 0;
	u32 fw_revctrl_new = 0;
	int upgrade = 1;
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);

    TS_LOG_INFO("%s: file_name is %s.\n",__func__,file_path);

    fw_data = kzalloc(64 * 1024, GFP_KERNEL);
    if(fw_data == NULL){
       TS_LOG_ERR("%s: kzalloc error.\n", __func__);
       return -EINVAL;
    }

    retval = cyttsp5_file_open_firmware(file_path,fw_data,&fw_size);
    if (retval != 0) {
        TS_LOG_ERR("file_open_firmware error, code = %d\n", retval);
        goto exit;
    }

    header_size = fw_data[0];

    TS_LOG_INFO("%s: header_size = %d,fw_size = %d.\n",__func__,header_size,fw_size);

    if (header_size >= (fw_size + 1)) {
        TS_LOG_ERR("%s: Firmware format is invalid,header_size = %d,fw_size = %d.\n",
            __func__,header_size,fw_size);
        goto exit;
    }

	fw_ver_new = get_unaligned_be16(&fw_data[3]);
	fw_revctrl_new = get_unaligned_be32(&fw_data[9]);

    /* check fw version needed ld->si is not NULL.*/
    if(ld->si){
	    upgrade = cyttsp5_check_firmware_version(dev, fw_ver_new,fw_revctrl_new);
    }

	if (update_flag == 1){
        TS_LOG_INFO("%s force update fw form sdcard.\n",__func__);
        retval = cyttsp5_upgrade_firmware(dev, (const u8 *)&fw_data[header_size + 1],
                    fw_size - (header_size + 1));
	}else{
        if(upgrade > 0){
            retval = cyttsp5_upgrade_firmware(dev, (const u8 *)&fw_data[header_size + 1],
                    fw_size - (header_size + 1)); 
        }
    }

    TS_LOG_INFO("%s is done\n",__func__);

exit:
    kfree(fw_data);
    return retval;
}

static ssize_t cyttsp5_fw_update_sd_store(struct device *dev,
                struct device_attribute *attr, const char *buf, size_t size)
{
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    int rc = 0;
    unsigned long update_flag = 0;

    TS_LOG_INFO("%s: start to update fw from sdcard.\n", __func__);

    if(buf == NULL){
        TS_LOG_ERR("%s: input buf is NULL.\n", __func__);
        return -EINVAL;
    }

  	rc = kstrtoul(buf, 10, &update_flag);
	if (rc < 0){
        TS_LOG_INFO("%s: kstrtoul error.\n",__func__);
		return rc;
	}

	if (update_flag != 0x01 && update_flag != 0x00){
        TS_LOG_INFO("%s: input value is error.\n",__func__);
		return -EINVAL;
	}

    if (ld->is_sd_upgrade_enabled)
        return -EBUSY;
    else
        ld->is_sd_upgrade_enabled = 1;

    TS_LOG_INFO("%s: file_path = %s.\n",__func__,CYTTSP5_FW_FROM_SD_NAME);

    rc = cyttsp5_fw_update_from_sdcard(dev,CYTTSP5_FW_FROM_SD_NAME,update_flag);
    if (rc < 0){
        TS_LOG_ERR("%s: fw update from sdcard failed.\n",__func__);
        goto exit;
    }

    TS_LOG_INFO("%s: fw update from sdcard is successful.\n",__func__);

exit:
    ld->is_sd_upgrade_enabled = 0;
    return size;
}

static DEVICE_ATTR(fw_update_sd, 0220, NULL, cyttsp5_fw_update_sd_store);
#endif

static int cyttsp5_loader_probe(struct device *dev)
{
    struct cyttsp5_core_data *cd = dev_get_drvdata(dev);
    struct cyttsp5_loader_data *ld;
    struct cyttsp5_platform_data *pdata = dev_get_platdata(dev);
    int rc;

    if (!pdata || !pdata->loader_pdata) {
        TS_LOG_ERR("%s: Missing platform data\n", __func__);
        rc = -ENODEV;
        goto error_no_pdata;
    }

    ld = kzalloc(sizeof(*ld), GFP_KERNEL);
    if (!ld) {
        TS_LOG_ERR("%s: kzalloc fail\n", __func__);
        rc = -ENOMEM;
        goto error_alloc_data_failed;
    }

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_PLATFORM_FW_UPGRADE
    rc = device_create_file(dev, &dev_attr_forced_upgrade);
    if (rc) {
        TS_LOG_ERR("%s: Error, could not create forced_upgrade\n",
                __func__);
        goto error_create_forced_upgrade;
    } else {
        TS_LOG_INFO("%s:create PLATFORM_FW_UPGRADE success\n", __func__);
    }
#endif

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_BINARY_FW_UPGRADE
    rc = device_create_file(dev, &dev_attr_manual_upgrade);
    if (rc) {
        TS_LOG_ERR("%s: Error, could not create manual_upgrade\n",
                __func__);
        goto error_create_manual_upgrade;
    } else {
        TS_LOG_INFO("%s: create BINARY_FW_UPGRADE success\n", __func__);
    }

    rc = device_create_file(dev, &dev_attr_fw_update_sd);
    if (rc) {
        TS_LOG_ERR("%s: Error, could not create fw_update_sd\n",
                __func__);
        goto error_create_fw_update_sd;
    } else {
        TS_LOG_INFO("%s: create BINARY_FW_UPGRADE success\n", __func__);
    }
#endif

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_MANUAL_TTCONFIG_UPGRADE
    rc = device_create_file(dev, &dev_attr_config_loading);
    if (rc) {
        TS_LOG_ERR("%s: Error, could not create config_loading\n",
                __func__);
        goto error_create_config_loading;
    } else {
        TS_LOG_INFO("%s: create MANUAL_TTCONFIG_UPGRADE success\n", __func__);
    }

    rc = device_create_bin_file(dev, &bin_attr_config_data);
    if (rc) {
        TS_LOG_ERR("%s: Error, could not create config_data\n",
                __func__);
        goto error_create_config_data;
    }
#endif

    ld->loader_pdata = pdata->loader_pdata;
    ld->dev = dev;
    cd->cyttsp5_dynamic_data[CY_MODULE_LOADER] = ld;

#if CYTTSP5_FW_UPGRADE
    init_completion(&ld->int_running);
#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_BINARY_FW_UPGRADE
    init_completion(&ld->builtin_bin_fw_complete);
#endif
    cmd->subscribe_attention(dev, CY_ATTEN_IRQ, CY_MODULE_LOADER,
        cyttsp5_loader_attention, CY_MODE_BOOTLOADER);

    cmd->subscribe_attention(dev, CY_ATTEN_LOADER, CY_MODULE_LOADER,
        cyttsp5_fw_upgrade_cb, CY_MODE_UNKNOWN);
#endif
#if CYTTSP5_FW_UPGRADE || CYTTSP5_TTCONFIG_UPGRADE
    init_completion(&ld->calibration_complete);
    INIT_WORK(&ld->calibration_work, cyttsp5_calibrate_idacs);
#endif
#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_MANUAL_TTCONFIG_UPGRADE
    mutex_init(&ld->config_lock);
#endif

#ifdef UPGRADE_FW_AND_CONFIG_IN_PROBE
    /* Call FW and config upgrade directly in probe */
    cyttsp5_fw_and_config_upgrade(&ld->fw_and_config_upgrade);
#else
    INIT_WORK(&ld->fw_and_config_upgrade, cyttsp5_fw_and_config_upgrade);
    schedule_work(&ld->fw_and_config_upgrade);
#endif

    TS_LOG_INFO("%s: Successful probe %s\n", __func__, dev_name(dev));
    return 0;

#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_MANUAL_TTCONFIG_UPGRADE
error_create_config_data:
    device_remove_file(dev, &dev_attr_config_loading);
error_create_config_loading:
#endif
#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_BINARY_FW_UPGRADE
    device_remove_file(dev, &dev_attr_fw_update_sd);
error_create_fw_update_sd:
    device_remove_file(dev, &dev_attr_manual_upgrade);
error_create_manual_upgrade:
#endif
#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_PLATFORM_FW_UPGRADE
    device_remove_file(dev, &dev_attr_forced_upgrade);
error_create_forced_upgrade:
#endif
    cd->cyttsp5_dynamic_data[CY_MODULE_LOADER] = NULL;
    kfree(ld);
error_alloc_data_failed:
error_no_pdata:
    TS_LOG_ERR("%s failed.\n", __func__);
    return rc;
}

static int cyttsp5_loader_release(struct device *dev)
{
    struct cyttsp5_core_data *cd = dev_get_drvdata(dev);
    struct cyttsp5_loader_data *ld = cyttsp5_get_loader_data(dev);
    int rc = 0;

#if CYTTSP5_FW_UPGRADE
    cmd->unsubscribe_attention(dev, CY_ATTEN_IRQ, CY_MODULE_LOADER,
        cyttsp5_loader_attention, CY_MODE_BOOTLOADER);

    cmd->unsubscribe_attention(dev, CY_ATTEN_LOADER, CY_MODULE_LOADER,
        cyttsp5_fw_upgrade_cb, CY_MODE_UNKNOWN);
#endif
#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_MANUAL_TTCONFIG_UPGRADE
    device_remove_bin_file(dev, &bin_attr_config_data);
    device_remove_file(dev, &dev_attr_config_loading);
    kfree(ld->config_data);
#endif
#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_BINARY_FW_UPGRADE
    device_remove_file(dev, &dev_attr_manual_upgrade);
#endif
#ifdef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_PLATFORM_FW_UPGRADE
    device_remove_file(dev, &dev_attr_forced_upgrade);
#endif
    cd->cyttsp5_dynamic_data[CY_MODULE_LOADER] = NULL;
    kfree(ld);
    return rc;
}

static char *core_ids[CY_MAX_NUM_CORE_DEVS] = {
    CY_DEFAULT_CORE_ID,
    NULL,
    NULL,
    NULL,
    NULL
};

static int num_core_ids = 1;

module_param_array(core_ids, charp, &num_core_ids, 0);
MODULE_PARM_DESC(core_ids,
    "Core id list of cyttsp5 core devices for loader module");

static int __init cyttsp5_loader_init(void)
{
    struct cyttsp5_core_data *cd;
    int rc = 0;
    int i, j;

    /* Check for invalid or duplicate core_ids */
    for (i = 0; i < num_core_ids; i++) {
        if (!strlen(core_ids[i])) {
            TS_LOG_ERR("%s: core_id %d is empty\n",    __func__, i + 1);
            return -EINVAL;
        }

        for (j = i+1; j < num_core_ids; j++) {
            if (!strcmp(core_ids[i], core_ids[j])) {
                TS_LOG_ERR("%s: core_ids %d and %d are same\n",
                    __func__, i+1, j+1);
                return -EINVAL;
            }
        }
    }

    cmd = cyttsp5_get_commands();
    if (!cmd) {
        TS_LOG_ERR("%s: cyttsp5_get_commands fail\n", __func__);
        return -EINVAL;
    }

    for (i = 0; i < num_core_ids; i++) {
        cd = cyttsp5_get_core_data(core_ids[i]);
        if (!cd) {
            continue;
        }

        TS_LOG_INFO("%s: Registering loader module for core_id: %s\n",
            __func__, core_ids[i]);
        rc = cyttsp5_loader_probe(cd->dev);
        if (rc < 0) {
            TS_LOG_ERR("%s: Error, failed registering module\n", __func__);
            goto fail_unregister_devices;
        }
    }

    TS_LOG_INFO("%s: Cypress TTSP FW Loader Driver (Built %s) rc=%d\n",
         __func__, CY_DRIVER_DATE, rc);

    return 0;

fail_unregister_devices:
    for (i--; i >= 0; i--) {
        cd = cyttsp5_get_core_data(core_ids[i]);
        if (!cd) {
            continue;
        }

        cyttsp5_loader_release(cd->dev);
        TS_LOG_INFO("%s: Unregistering loader module for core_id: %s\n",
            __func__, core_ids[i]);
    }

    return rc;
}
module_init(cyttsp5_loader_init);

static void __exit cyttsp5_loader_exit(void)
{
    struct cyttsp5_core_data *cd;
    int i;

    for (i = 0; i < num_core_ids; i++) {
        cd = cyttsp5_get_core_data(core_ids[i]);
        if (!cd)
            continue;
        cyttsp5_loader_release(cd->dev);
        TS_LOG_INFO("%s: Unregistering loader module for core_id: %s\n",
            __func__, core_ids[i]);
    }
}
module_exit(cyttsp5_loader_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Cypress TrueTouch(R) Standard Product FW Loader Driver");
MODULE_AUTHOR("Cypress Semiconductor <ttdrivers@cypress.com>");
