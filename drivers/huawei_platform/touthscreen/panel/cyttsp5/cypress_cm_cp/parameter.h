/******************************************************************************
 * @file parameter.h
 *
 * parameter.h
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

#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#include <linux/fs.h>

#define MAX_STRING_LENGTH    128

enum parameter_id {
    TX_NUM,
    RX_NUM,
    BUTTON_NUM,
    SCANNING_MODE_BUTTON,
    TX_PERIOD_MUTUAL,
    TX_PERIOD_SELF,
    TX_PERIOD_BTN_MUTUAL,
    TX_PERIOD_BTN_SELF,
    MTX_ORDER,
    VDDA_MODE,
    SCALING_FACTOR_MUTUAL,
    SCALING_FACTOR_SELF,
    SCALING_FACTOR_BUTTON_MUTUAL,
    SCALING_FACTOR_BUTTON_SELF,
    BALANCING_TARGET_MUTUAL,
    BALANCING_TARGET_SELF,
    BALANCING_TARGET_BUTTON_MUTUAL,
    BALANCING_TARGET_BUTTON_SELF,
    GIDAC_MULT,
    RXDAC,
    REF_SCALE,
    ACT_LFT_EN,
    BL_H20_RJCT,
    TX_PUMP_VOLTAGE,
    SENSOR_ASSIGNMENT,
    GIDAC_LSB_CONFIG,
    INT_CAP_MUTUAL,
    INT_CAP_SELF,
    INT_CAP_BUTTON_MUTUAL,
    INT_CAP_BUTTON_SELF,
    TX_VOLTAGE_MUTUAL,
    PARAMETER_ID_MAX,
};

enum parameter_type {
    INTEGER,
    FLOAT,
    STRING,
    PARAMETER_TYPE_MAX,
};

union parameter_value {
    int32_t integer;
    int flt;
    char string[MAX_STRING_LENGTH];
};

/* SCANNING_MODE_BUTTON enumerated values */
#define SCANNING_MODE_BUTTON_SELF    "Self Capacitance"
#define SCANNING_MODE_BUTTON_MUTUAL    "Mutual Capacitance"
#define SCANNING_MODE_BUTTON_HYBRID    "Hybrid"

/* VDDA_MODE enumerated values */
#define VDDA_MODE_PUMP            "Pump Mode"
#define VDDA_MODE_BYPASS        "Bypass Mode"

/* ACT_LFT_EN enumerated values */
#define ACT_LFT_EN_DISABLED        "Disabled"
#define ACT_LFT_EN_ENABLED        "Enabled"
#define RX_IS_Y               "RX = Y; TX = X"
#define RX_IS_X               "RX = X; TX = Y"

/* BL_H20_RJCT enumerated values */
#define BL_H20_RJCT_DISABLED        "Disabled"
#define BL_H20_RJCT_ENABLED        "Enabled"

extern int parameter_init(struct file *file);

extern int parameter_get_info(enum parameter_id id, uint16_t *address,
        uint16_t *size, uint32_t *mask, enum parameter_type *type);

extern int parameter_get_enumerated_value(enum parameter_id id, int index,
        const union parameter_value **value);

extern void parameter_exit(void);

#endif /* _PARAMETER_H_ */
