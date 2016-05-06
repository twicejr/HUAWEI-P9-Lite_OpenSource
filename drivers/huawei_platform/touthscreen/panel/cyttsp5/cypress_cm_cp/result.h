/******************************************************************************
 * @file result.h
 *
 * result.h
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

#ifndef _RESULT_H_
#define _RESULT_H_
#include <linux/fs.h>
#include "cm_cp_test.h"
#include "configuration.h"
struct result {
    uint32_t tx_num;
    uint32_t rx_num;
    uint32_t button_num;
    uint32_t sensor_assignment;
    uint32_t config_ver;
    uint32_t revision_ctrl;
    uint32_t device_id_high;
    uint32_t device_id_low;
    bool cm_test_run;
    bool cp_test_run;
    /* Sensor Cm validation */
    bool cm_test_pass;
    bool cm_sensor_validation_pass;
    bool cm_sensor_row_delta_pass;
    bool cm_sensor_col_delta_pass;
    bool cm_sensor_calibration_pass;
    bool cm_sensor_delta_pass;
    bool cm_button_validation_pass;
    bool cm_button_delta_pass;
    int *cm_sensor_data;
    int32_t *cm_sensor_raw_data;
    int *cm_sensor_column_delta;
    int *cm_sensor_row_delta;
    int cm_sensor_calibration;
    int cm_sensor_average;
    int cm_sensor_delta;
    int *cm_button_data;
    int32_t *cm_button_raw_data;
    int cm_button_calibration;
    int cm_button_average;
    int cm_button_delta;
    struct gd_sensor*cm_gradient_col;
    struct gd_sensor*cm_gradient_row;
    /* Sensor Cp validation */
    bool cp_test_pass;
    bool cp_sensor_delta_pass;
    bool cp_sensor_rx_delta_pass;
    bool cp_sensor_tx_delta_pass;
    bool cp_sensor_average_pass;
    bool cp_button_delta_pass;
    bool cp_button_average_pass;
    bool cp_rx_validation_pass;
    bool cp_tx_validation_pass;
    int *cp_sensor_rx_data;
    int *cp_sensor_tx_data;
    int32_t *cp_sensor_rx_raw_data;
    int32_t *cp_sensor_tx_raw_data;
    int cp_sensor_rx_delta;
    int cp_sensor_tx_delta;
    int cp_sensor_rx_average;
    int cp_sensor_tx_average;
    int cp_sensor_rx_calibration;
    int cp_sensor_tx_calibration;
    int *cp_button_data;
    int32_t *cp_button_raw_data;
    int cp_button_delta;
    int cp_button_average;
    bool short_test_pass;
    bool test_summary;
};

extern int result_save(struct seq_file *file, struct configuration *configuration,
        struct result *result);
#endif /* _RESULT_H_ */
