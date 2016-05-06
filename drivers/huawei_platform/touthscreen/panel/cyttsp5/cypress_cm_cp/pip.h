/******************************************************************************
 * @file pip.h
 *
 * pip.h
 *
 * @version 0.0.1
 * @authors btok
 *
 *****************************************************************************//*
 * Copyright (2014), Cypress Semiconductor Corporation. All rights reserved.
 *
 * This software, associated documentation and materials ("Software") is owned
 * by Cypress Semiconductor Corporation ("Cypress") and is protected by and
 * subject to worldwide patent protection (United States and foreign), United
 * States copyright laws and international treaty provisions. Therefore, unless
 * otherwise specified in a separate license agreement between you and Cypress,
 * this Software must be treated like any other copyrighted material.
 * Reproduction, modification, translation, compilation, or representation of
 * this Software in any other form (e.g., paper, magnetic, optical, silicon) is
 * prohibited without Cypress's express written permission.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * Cypress reserves the right to make changes to the Software without notice.
 * Cypress does not assume any liability arising out of the application or use
 * of Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use as critical components in any products
 * where a malfunction or failure may reasonably be expected to result in
 * significant injury or death ("High Risk Product"). By including Cypress's
 * product in a High Risk Product, the manufacturer of such system or
 * application assumes all risk of such use and in doing so indemnifies Cypress
 * against all liability.
 *
 * Use of this Software may be limited by and subject to the applicable Cypress
 * software license agreement.
 *****************************************************************************/

#ifndef _PIP_H_
#define _PIP_H_

#include <linux/fs.h>

#define GET_ELEMENT_SIZE(data_format)	((data_format) & 0x07)
#define GET_MATRIX_MAPPING(data_format)	(((data_format) >> 3) & 0x01)
#define GET_SIGN(data_format)		(((data_format) >> 5) & 0x01)

#define MATRIX_MAPPING_ROW_MAJOR	0
#define MATRIX_MAPPING_COLUMN_MAJOR	1

#define SIGN_UNSIGNED			0
#define SIGN_TWOS_COMPLEMENT		1

#define NUM_MFGID			8

#define NUM_MAX_BUTTONS			4

#define IS_BTNx_ENABLED(btn, x)		(((btn) >> x) & 0x01)

struct cy_data {
    uint8_t pip_ver_major;
    uint8_t pip_ver_minor;
    uint16_t fw_pid;
    uint8_t fw_ver_major;
    uint8_t fw_ver_minor;
    uint32_t fw_revctrl;
    uint16_t fw_ver_conf;
    uint8_t bl_ver_major;
    uint8_t bl_ver_minor;
    uint8_t family_id;
    uint8_t revision_id;
    uint16_t silicon_id;
    uint8_t mfg_id[NUM_MFGID];
    uint16_t post_code;
};

struct sens_conf_data {
    uint8_t electrodes_x;
    uint8_t electrodes_y;
    uint16_t len_x;
    uint16_t len_y;
    uint16_t res_x;
    uint16_t res_y;
    uint16_t max_z;
    uint8_t origin_x;
    uint8_t origin_y;
    uint8_t panel_id;
    uint8_t btn;
    uint8_t scan_mode;
    uint8_t max_num_of_tch_per_refresh_cycle;
};

struct pip_sysinfo {
    struct cy_data cy_data;
    struct sens_conf_data sens_conf_data;
};

static inline int pip_get_buttons_number(struct pip_sysinfo *sysinfo)
{
    int num_btns = 0;
    int i;

    for (i = 0; i < NUM_MAX_BUTTONS; i++)
        if (IS_BTNx_ENABLED(sysinfo->sens_conf_data.btn, i))
            num_btns++;

    return num_btns;
}

extern int  pip_init(char *device_path, uint16_t hid_desc_register);
extern void pip_exit(void);
extern int  pip_get_system_information(struct pip_sysinfo *sysinfo);
extern int  pip_suspend_scanning(void);
extern int  pip_resume_scanning(void);
extern int  pip_get_parameter(uint8_t parameter_id, uint32_t *parameter_value);
extern int  pip_set_parameter(uint8_t parameter_id, uint8_t parameter_size,
        uint32_t parameter_value);
extern int  pip_read_data_block(uint16_t row_number, uint16_t read_length,
        uint8_t block_id, uint16_t *actual_read_length, uint8_t *data);
extern int  pip_retrieve_data_structure(uint16_t read_offset,
        uint16_t read_length, uint8_t data_id,
        uint16_t *actual_read_length, uint8_t *data_format,
        uint8_t *data);
extern int  pip_calibrate_idacs(uint8_t sensing_mode);
extern int  pip_execute_panel_scan(void);
extern int  pip_retrieve_panel_scan(uint16_t read_offset, uint16_t read_length,
        uint8_t data_id, uint16_t *actual_read_length,
        uint8_t *data_format, uint8_t *data);
extern int pip_short_test(void);
#endif /* _PIP_H_ */
