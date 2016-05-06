/******************************************************************************
 * @file cm_cp_test.h
 *
 * cm_cp_test.h
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

#ifndef _CM_CP_TEST_H_
#define _CM_CP_TEST_H_

#include <linux/fs.h>
#define HID_DESCRIPTOR_REGISTER				0x0001

/* Runtime Parameters */
#define FORCE_SINGLE_TX					0x1F

#define IDAC_AND_RX_ATTENUATOR_CALIBRATION_DATA_ID	0x00
#define IDAC_AND_RX_ATTENUATOR_CALIBRATION_DATA_LENGTH	10

#define RX_ATTENUATOR_MUTUAL_INDEX			0
#define IDAC_MUTUAL_INDEX				1
#define RX_ATTENUATOR_SELF_RX_INDEX			2
#define IDAC_SELF_RX_INDEX				3
#define RX_ATTENUATOR_SELF_TX_INDEX			4
#define IDAC_SELF_TX_INDEX				5
#define RX_ATTENUATOR_BUTTON_MUTUAL_INDEX		6
#define IDAC_BUTTON_MUTUAL_INDEX			7
#define RX_ATTENUATOR_BUTTON_SELF_INDEX			8
#define IDAC_BUTTON_SELF_INDEX				9

#define MUTUAL_CAP_RAW_DATA_ID				0x00
#define MUTUAL_LOCAL_PWC_DATA_ID				0x00

#define SELF_CAP_RAW_DATA_ID				0x03
#define SELF_LOCAL_PWC_DATA_ID				0x01

#define BUTTONS_DATA_ID					0x09

#define BUTTONS_NUM_ELEMENTS				4
#define BUTTONS_RAW_DATA_INDEX				0

#define CONFIG_BLOCK_ID					0x00

#define ROW_SIZE					128

#define READ_LENGTH 					100


struct gd_sensor {
    uint16_t cm_min;
    uint16_t cm_max;
    int cm_ave;
    uint16_t cm_min_exclude_edge;
    uint16_t cm_max_exclude_edge;
    int cm_ave_exclude_edge;
    int gradient_val;
};

extern int cm_cp_test_run(char *device_path, struct file *parameter_file,
		struct file *configuration_file, struct seq_file *result_file,
		int vdda, bool run_cm_test, bool run_cp_test,
		bool *cm_test_pass, bool *cp_test_pass);
#endif /* _CM_CP_TEST_H_ */
