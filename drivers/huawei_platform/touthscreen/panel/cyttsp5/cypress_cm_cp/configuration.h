/******************************************************************************
 * @file configuration.h
 *
 * configuration.h
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

#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <linux/fs.h>


#define MAX_BUTTONS		4
#define MAX_SENSORS		1024
#define MAX_TX_SENSORS       128
#define MAX_RX_SENSORS       128

/* Multiply by 2 for double (min, max) values */
#define TABLE_BUTTON_MAX_SIZE	(MAX_BUTTONS * 2)
#define TABLE_SENSOR_MAX_SIZE	(MAX_SENSORS * 2)
#define TABLE_TX_MAX_SIZE (MAX_TX_SENSORS*2)
#define TABLE_RX_MAX_SIZE (MAX_RX_SENSORS*2)

struct configuration {
    int family_type;
    //int CM_EXCLUDING_COL_EDGE;
    int cm_excluding_col_edge;
    int cm_excluding_row_edge;
    //int CM_GRADIENT_CHECK_COL[];
    int cm_gradient_check_col[MAX_RX_SENSORS];
    int cm_gradient_check_row[MAX_RX_SENSORS];
    int cm_gradient_check_col_size;
    int cm_gradient_check_row_size;
    int cm_range_limit_row;
    int cm_range_limit_col;
    int cm_min_limit_cal;
    int cm_max_limit_cal;
    int cm_max_delta_sensor_percent;
    int cm_max_delta_button_percent;
    int min_sensor_rx;
    int max_sensor_rx;
    int min_sensor_tx;
    int max_sensor_tx;
    int min_button;
    int max_button;
    int max_delta_sensor;
    int cp_max_delta_sensor_rx_percent;
    int cp_max_delta_sensor_tx_percent;
    int cm_min_max_table_button[TABLE_BUTTON_MAX_SIZE];
    int cm_min_max_table_sensor[TABLE_SENSOR_MAX_SIZE];
    int cp_min_max_table_rx[TABLE_RX_MAX_SIZE];
    int cp_min_max_table_tx[TABLE_TX_MAX_SIZE];
    int cm_min_max_table_button_size;
    int cm_min_max_table_sensor_size;
    int cp_min_max_table_rx_size;
    int cp_min_max_table_tx_size;
    int cp_max_delta_button_percent;
};

int configuration_get(struct file *file, struct configuration *configuration);
#endif /* _CONFIGURATION_H_ */
