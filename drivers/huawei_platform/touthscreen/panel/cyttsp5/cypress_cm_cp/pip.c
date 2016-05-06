/******************************************************************************
 * @file pip.c
 *
 * pip.c
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

#include "../cyttsp5_regs.h"
#include "../cyttsp5_core.h"
#include "csv.h"
#include "pip.h"

/* Device specific definitins */
#define HID_DESCRIPTOR_LENGTH		32

#define APP_OUTPUT_REPORT_ID		0x2f
#define APP_INPUT_REPORT_ID		0x1f
#define COMMAND_MASK			0x7f

#define COMMAND_GET_SYSTEM_INFO         0x02
#define COMMAND_SUSPEND_SCANNING        0x03
#define COMMAND_RESUME_SCANNING         0x04
#define COMMAND_GET_PARAMETER           0x05
#define COMMAND_SET_PARAMETER           0x06
#define COMMAND_READ_DATA_BLOCK		0x22
#define COMMAND_RETRIEVE_DATA_STRUCTURE	0x24
#define COMMAND_SHORT_TEST                   0x26
#define COMMAND_CALIBRATE_IDACS		0x28
#define COMMAND_EXECUTE_PANEL_SCAN	0x2A
#define COMMAND_RETRIEVE_PANEL_SCAN	0x2B

#define SUCCESS				0x00
#define FAILURE				0x01

#define REPORT_BUFFER_SIZE		4096
#define RESPONSE_BUFFER_SIZE		4096

/* Helper macros */
#define LO_BYTE(x)	((x) & 0xff)
//#define HI_BYTE(x)	(((x) >> 8) & 0xff)
#define LO_WORD(x)	((x) & 0xffff)
#define HI_WORD(x)	(((x) >> 16) & 0xffff)
#define MERGE8(lo,hi)	((lo) + ((hi) << 8))
#define MERGE16(lo,hi)	((lo) + ((hi) << 16))

static uint8_t *report_buffer = NULL;
static uint8_t *response_buffer = NULL;
static char *command_buf = NULL;
extern struct device *gdev;

static struct hid_desc {
    uint16_t hid_desc_len;
    uint8_t packet_id;
    uint8_t reserved_byte;
    uint16_t bcd_version;
    uint16_t report_desc_len;
    uint16_t report_desc_register;
    uint16_t input_register;
    uint16_t max_input_len;
    uint16_t output_register;
    uint16_t max_output_len;
    uint16_t command_register;
    uint16_t data_register;
    uint16_t vendor_id;
    uint16_t product_id;
    uint16_t version_id;
    uint8_t reserved[4];
} hid_desc;

struct tt_output_report {
    uint8_t reg_address_lo;
    uint8_t reg_address_hi;
    uint8_t length_lo;
    uint8_t length_hi;
    uint8_t report_id;
    uint8_t reserved;
    uint8_t command;
    uint8_t parameters[0];
};

struct tt_input_report {
    uint8_t length_lo;
    uint8_t length_hi;
    uint8_t report_id;
    uint8_t reserved;
    uint8_t command;
    uint8_t return_data[0];
};

extern int cyttsp5_get_SensorData(struct device *dev,char *id,char *cmd,
                int data_len,int data_byte,int other);


static int pip_get_sensor_data(struct device *dev, uint8_t *report_buffer,
        int report_size, uint8_t *response_buffer, int *response_size)
{
    int ret = 0;
    int i = 0;
    char temp_command[] = "0x00 ";
    struct cyttsp5_device_access_data *dad  = cyttsp5_get_device_access_data(dev);
    
    if (!report_buffer || !report_size || !response_buffer || !response_size) {
        TS_LOG_ERR("%s, parameters invalid\n", __func__);
        return -EINVAL;
    }
    
    memset(response_buffer,0,RESPONSE_BUFFER_SIZE);
    memset(command_buf, 0, RESPONSE_BUFFER_SIZE);

    for (i = 0; i < report_size -1; i++) {
        snprintf(temp_command,PAGE_SIZE,"0x%02X ", report_buffer[i]);
        strncat(command_buf, temp_command, sizeof(temp_command));
    }
    snprintf(temp_command,PAGE_SIZE,"0x%02X ", report_buffer[report_size -1]);
    strncat(command_buf, temp_command, strlen(temp_command) - 1);
	TS_LOG_DEBUG("report_buffer:%s\n", command_buf);

    ret = cyttsp5_send_command_cyttsp5(dev,command_buf);
    if(ret < 0 ){
        TS_LOG_ERR("%s Failed to send command.\n",__func__);
        goto exit;
    }

    ret = cyttsp5_command_response_cyttsp5(dev,response_buffer);
    if(ret < 0){
        TS_LOG_ERR("%s Failed to get response.\n",__func__);
        goto exit;
    }

    *response_size = (int)dad->response_length;
    for (i = 0; i < *response_size; i++) {
        TS_LOG_DEBUG("response_buffer:0x%02x\n", response_buffer[i]);
    }
    
exit:
    return ret;
}

static int prepare_tt_output_report(struct tt_output_report *out,
        uint16_t length, uint8_t command)
{
    length += 5;

    out->reg_address_lo = LO_BYTE(hid_desc.output_register);
    out->reg_address_hi = HI_BYTE(hid_desc.output_register);

    out->length_lo = LO_BYTE(length);
    out->length_hi = HI_BYTE(length);

    out->report_id = APP_OUTPUT_REPORT_ID;
    out->reserved = 0x00;
    out->command = command & COMMAND_MASK;

    return 2 + length;
}

static int check_and_parse_tt_input_report(struct tt_input_report *in,
        uint16_t *length, uint8_t *command)
{
    if (in->report_id != APP_INPUT_REPORT_ID)
            return -EINVAL;

    *length = MERGE8(in->length_lo, in->length_hi);
    *command = in->command & COMMAND_MASK;

    return 0;
}

static int prepare_get_system_info_report(uint8_t *buf)
{
    struct tt_output_report *out = (struct tt_output_report *)buf;

    return prepare_tt_output_report(out, 0, COMMAND_GET_SYSTEM_INFO);
}

static int check_and_parse_get_system_info_response(
        uint8_t *buf, uint16_t read_length,
        struct cy_data *cy_data,
        struct sens_conf_data *sens_conf_data)
{
    struct tt_input_report *in = (struct tt_input_report *)buf;
    uint16_t length = 0;
    uint8_t command = 0;

    if (read_length != 51)
            return -EINVAL;

    if (check_and_parse_tt_input_report(in, &length, &command)
                    || command != COMMAND_GET_SYSTEM_INFO
                    || length != 51)
            return -EINVAL;

    cy_data->pip_ver_major = in->return_data[0];
    cy_data->pip_ver_minor = in->return_data[1];
    cy_data->fw_pid = MERGE8(in->return_data[2], in->return_data[3]);
    cy_data->fw_ver_major = in->return_data[4];
    cy_data->fw_ver_minor = in->return_data[5];
    cy_data->fw_revctrl = MERGE16(
            MERGE8(in->return_data[6], in->return_data[7]),
            MERGE8(in->return_data[8], in->return_data[9]));
    cy_data->fw_ver_conf = MERGE8(in->return_data[10], in->return_data[11]);
    cy_data->bl_ver_major = in->return_data[12];
    cy_data->bl_ver_minor = in->return_data[13];
    cy_data->family_id = in->return_data[14];
    cy_data->revision_id = in->return_data[15];
    cy_data->silicon_id = MERGE8(in->return_data[16], in->return_data[17]);
    cy_data->mfg_id[0] = in->return_data[18];
    cy_data->mfg_id[1] = in->return_data[19];
    cy_data->mfg_id[2] = in->return_data[20];
    cy_data->mfg_id[3] = in->return_data[21];
    cy_data->mfg_id[4] = in->return_data[22];
    cy_data->mfg_id[5] = in->return_data[23];
    cy_data->mfg_id[6] = in->return_data[24];
    cy_data->mfg_id[7] = in->return_data[25];
    cy_data->post_code = MERGE8(in->return_data[26], in->return_data[27]);

    sens_conf_data->electrodes_x = in->return_data[28];
    sens_conf_data->electrodes_y = in->return_data[29];
    sens_conf_data->len_x = MERGE8(in->return_data[30], in->return_data[31]);
    sens_conf_data->len_y = MERGE8(in->return_data[32], in->return_data[33]);
    sens_conf_data->res_x = MERGE8(in->return_data[34], in->return_data[35]);
    sens_conf_data->res_y = MERGE8(in->return_data[36], in->return_data[37]);
    sens_conf_data->max_z = MERGE8(in->return_data[38], in->return_data[39]);
    sens_conf_data->origin_x = in->return_data[40];
    sens_conf_data->origin_y = in->return_data[41];
    sens_conf_data->panel_id = in->return_data[42];
    sens_conf_data->btn = in->return_data[43];
    sens_conf_data->scan_mode = in->return_data[44];
    sens_conf_data->max_num_of_tch_per_refresh_cycle = in->return_data[45];

#ifdef DEBUG
        TS_LOG_DEBUG("%s, PIP Major Version: %d\n", __func__, cy_data->pip_ver_major);
        TS_LOG_DEBUG("PIP Minor Version: %d\n", cy_data->pip_ver_minor);
        TS_LOG_DEBUG("Touch Firmware Product Id: %d\n", cy_data->fw_pid);
        TS_LOG_DEBUG("Touch Firmware Major Version: %d\n", cy_data->fw_ver_major);
        TS_LOG_DEBUG("Touch Firmware Minor Version: %d\n", cy_data->fw_ver_minor);
        TS_LOG_DEBUG("Touch Firmware Internal Revision Control Number: %d\n",
            cy_data->fw_revctrl);
        TS_LOG_DEBUG("Customer Specified Firmware/Configuration Version: %d\n",
            cy_data->fw_ver_conf);
        TS_LOG_DEBUG("%s, Bootloader Major Version: %d\n", cy_data->bl_ver_major);
        TS_LOG_DEBUG("Bootloader Minor Version: %d\n", cy_data->bl_ver_minor);
        TS_LOG_DEBUG("Family ID: 0x%02x\n", cy_data->family_id);
        TS_LOG_DEBUG("Revision ID: 0x%02x\n", cy_data->revision_id);
        TS_LOG_DEBUG("Silicon ID: 0x%02x\n", cy_data->silicon_id);
        TS_LOG_DEBUG("Cypress Manufacturing ID[0]: 0x%02x\n", cy_data->mfg_id[0]);
        TS_LOG_DEBUG("Cypress Manufacturing ID[1]: 0x%02x\n", cy_data->mfg_id[1]);
        TS_LOG_DEBUG("Cypress Manufacturing ID[2]: 0x%02x\n", cy_data->mfg_id[2]);
        TS_LOG_DEBUG("Cypress Manufacturing ID[3]: 0x%02x\n", cy_data->mfg_id[3]);
        TS_LOG_DEBUG("Cypress Manufacturing ID[4]: 0x%02x\n", cy_data->mfg_id[4]);
        TS_LOG_DEBUG("Cypress Manufacturing ID[5]: 0x%02x\n", cy_data->mfg_id[5]);
        TS_LOG_DEBUG("Cypress Manufacturing ID[6]: 0x%02x\n", cy_data->mfg_id[6]);
        TS_LOG_DEBUG("Cypress Manufacturing ID[7]: 0x%02x\n", cy_data->mfg_id[7]);
        TS_LOG_DEBUG("POST Result Code: 0x%02x\n", cy_data->post_code);
        TS_LOG_DEBUG("Number of X Electrodes: %d\n", sens_conf_data->electrodes_x);
        TS_LOG_DEBUG("Number of Y Electrodes: %d\n", sens_conf_data->electrodes_y);
        TS_LOG_DEBUG("Panel X Axis Length: %d\n", sens_conf_data->len_x);
        TS_LOG_DEBUG("Panel Y Axis Length: %d\n", sens_conf_data->len_y);
        TS_LOG_DEBUG("Panel X Axis Resolution: %d\n", sens_conf_data->res_x);
        TS_LOG_DEBUG("Panel Y Axis Resolution: %d\n", sens_conf_data->res_y);
        TS_LOG_DEBUG("Panel Pressure Resolution: %d\n", sens_conf_data->max_z);
        TS_LOG_DEBUG("X_ORG: %d\n", sens_conf_data->origin_x);
        TS_LOG_DEBUG("Y_ORG: %d\n", sens_conf_data->origin_y);
        TS_LOG_DEBUG("Panel ID: %d\n", sens_conf_data->panel_id);
        TS_LOG_DEBUG("Buttons: 0x%02x\n", sens_conf_data->btn);
        TS_LOG_DEBUG("BAL SELF MC: 0x%02x\n", sens_conf_data->scan_mode);
        TS_LOG_DEBUG("Max Number of Touch Records per Refresh Cycle: %d\n",
            sens_conf_data->max_num_of_tch_per_refresh_cycle);
#endif

        return 0;
}

static int prepare_suspend_scanning_report(uint8_t *buf)
{
    struct tt_output_report *out = (struct tt_output_report *)buf;

    return prepare_tt_output_report(out, 0, COMMAND_SUSPEND_SCANNING);
}

static int check_suspend_scanning_response(uint8_t *buf, uint16_t read_length)
{
    struct tt_input_report *in = (struct tt_input_report *)buf;
    uint16_t length = 0;
    uint8_t command = 0;

    if (read_length != 5)
            return -EINVAL;

    if (check_and_parse_tt_input_report(in, &length, &command)
                    || command != COMMAND_SUSPEND_SCANNING
                    || length != 5)
            return -EINVAL;

    return 0;
}

static int prepare_resume_scanning_report(uint8_t *buf)
{
    struct tt_output_report *out = (struct tt_output_report *)buf;

    return prepare_tt_output_report(out, 0, COMMAND_RESUME_SCANNING);
}

static int check_resume_scanning_response(uint8_t *buf, uint16_t read_length)
{
    struct tt_input_report *in = (struct tt_input_report *)buf;
    uint16_t length = 0;
    uint8_t command = 0;

    if (read_length != 5)
            return -EINVAL;

    if (check_and_parse_tt_input_report(in, &length, &command)
                    || command != COMMAND_RESUME_SCANNING
                    || length != 5)
            return -EINVAL;

    return 0;
}

static int prepare_get_parameter_report(uint8_t *buf, uint8_t parameter_id)
{
    struct tt_output_report *out = (struct tt_output_report *)buf;

    out->parameters[0] = parameter_id;

    return prepare_tt_output_report(out, 1, COMMAND_GET_PARAMETER);
}

static int check_and_parse_get_parameter_response(uint8_t *buf, uint16_t read_length,
        uint32_t *parameter_value)
{
    struct tt_input_report *in = (struct tt_input_report *)buf;
    uint16_t length = 0;
    uint8_t command = 0;
    uint32_t param_value = 0;
    uint8_t param_id;
    uint8_t param_size = 0;

    if (read_length != 8 && read_length != 9 && read_length != 11)
        return -EINVAL;

    if (check_and_parse_tt_input_report(in, &length, &command)
            || command != COMMAND_GET_PARAMETER
            || (length != 8 && length != 9 && length != 11))
        return -EINVAL;

    param_id = in->return_data[0];

    param_size = in->return_data[1];

    if (param_size == 1 && length == 8)
        param_value = in->return_data[2];
    else if (param_size == 2 && length == 9)
        param_value = MERGE8(in->return_data[2], in->return_data[3]);
    else if (param_size == 4 && length == 11)
        param_value = MERGE16(
                MERGE8(in->return_data[2], in->return_data[3]),
                MERGE8(in->return_data[4], in->return_data[5]));
    else
        return -EINVAL;

    *parameter_value = param_value;

    return 0;
}

static int prepare_set_parameter_report(uint8_t *buf, uint8_t parameter_id,
        uint32_t parameter_size, uint32_t parameter_value)
{
    struct tt_output_report *out = (struct tt_output_report *)buf;

    if (parameter_size != 1 && parameter_size != 2 && parameter_size != 4)
        return -EINVAL;

    out->parameters[0] = parameter_id;
    out->parameters[1] = parameter_size;
    out->parameters[2] = LO_BYTE(LO_WORD(parameter_value));
    if (parameter_size == 2 || parameter_size == 4)
        out->parameters[3] = HI_BYTE(LO_WORD(parameter_value));
    if (parameter_size == 4) {
        out->parameters[4] = LO_BYTE(HI_WORD(parameter_value));
        out->parameters[5] = HI_BYTE(HI_WORD(parameter_value));
    }

    return prepare_tt_output_report(out, 2 + parameter_size, COMMAND_SET_PARAMETER);
}

static int check_and_parse_set_parameter_response(uint8_t *buf, uint16_t read_length,
        uint8_t *parameter_id, uint8_t *parameter_size)
{
    struct tt_input_report *in = (struct tt_input_report *)buf;
    uint16_t length = 0;
    uint8_t command = 0;

    if (read_length != 7)
        return -EINVAL;

    if (check_and_parse_tt_input_report(in, &length, &command)
            || command != COMMAND_SET_PARAMETER
            || length != 7)
        return -EINVAL;

    *parameter_id = in->return_data[0];

    *parameter_size = in->return_data[1];

    return 0;
}

static int prepare_read_data_block_report(uint8_t *buf,
        uint16_t row_number, uint16_t read_length, uint8_t block_id)
{
    struct tt_output_report *out = (struct tt_output_report *)buf;

    out->parameters[0] = LO_BYTE(row_number);
    out->parameters[1] = HI_BYTE(row_number);
    out->parameters[2] = LO_BYTE(read_length);
    out->parameters[3] = HI_BYTE(read_length);
    out->parameters[4] = block_id;

    return prepare_tt_output_report(out, 5, COMMAND_READ_DATA_BLOCK);
}

static int check_and_parse_read_data_block_response(uint8_t *buf,
        uint16_t read_length, uint8_t *status, uint8_t *block_id,
        uint16_t *actual_read_length, uint8_t *data,
        uint16_t *data_crc)
{
    struct tt_input_report *in = (struct tt_input_report *)buf;
    uint16_t length = 0;
    uint8_t command = 0;

    if (read_length < 6)
        return -EINVAL;

    if (check_and_parse_tt_input_report(in, &length, &command)
            || command != COMMAND_READ_DATA_BLOCK
            || length < 6)
        return -EINVAL;

    *status = in->return_data[0];
    if (read_length == 6)
        return 0;

    if (read_length >= 7)
        *block_id = in->return_data[1];

    if (read_length >= 9)
        *actual_read_length = MERGE8(in->return_data[2],
                in->return_data[3]);

    if (read_length != 12 + *actual_read_length)
        return -EINVAL;

    memcpy(data, &in->return_data[5], *actual_read_length);

    *data_crc = MERGE8(in->return_data[5 + *actual_read_length],
            in->return_data[6 + *actual_read_length]);

    return 0;
}

static int prepare_retrieve_data_structure_report(uint8_t *buf,
        uint16_t read_offset, uint16_t read_length, uint8_t data_id)
{
    struct tt_output_report *out = (struct tt_output_report *)buf;

    out->parameters[0] = LO_BYTE(read_offset);
    out->parameters[1] = HI_BYTE(read_offset);
    out->parameters[2] = LO_BYTE(read_length);
    out->parameters[3] = HI_BYTE(read_length);
    out->parameters[4] = data_id;

    return prepare_tt_output_report(out, 5, COMMAND_RETRIEVE_DATA_STRUCTURE);
}

static int check_and_parse_retrieve_data_structure_response(uint8_t *buf,
        uint16_t read_length, uint8_t *status, uint8_t *data_id,
        uint16_t *actual_read_length, uint8_t *data_format, uint8_t *data)
{
    struct tt_input_report *in = (struct tt_input_report *)buf;
    uint16_t length = 0;
    uint8_t command = 0;

    if (read_length < 6)
        return -EINVAL;

    if (check_and_parse_tt_input_report(in, &length, &command)
            || command != COMMAND_RETRIEVE_DATA_STRUCTURE
            || length < 6)
        return -EINVAL;

    *status = in->return_data[0];
    if (read_length == 6)
        return 0;

    if (read_length >= 7)
        *data_id = in->return_data[1];

    if (read_length >= 9)
        *actual_read_length = MERGE8(in->return_data[2],
                in->return_data[3]);

    if (read_length != 10 + *actual_read_length)
        return -EINVAL;

    *data_format = in->return_data[4];

    memcpy(data, &in->return_data[5], *actual_read_length);

    return 0;
}

static int prepare_short_test_report(uint8_t *buf)
{
    struct tt_output_report *out = (struct tt_output_report *)buf;
    out->parameters[0] = 0x04;//Automatic Shorts Self test ID is 0x04
    return prepare_tt_output_report(out, 1, COMMAND_SHORT_TEST);
}

static int prepare_calibrate_idacs_report(uint8_t *buf, uint8_t sensing_mode)
{
    struct tt_output_report *out = (struct tt_output_report *)buf;

    out->parameters[0] = sensing_mode;

    return prepare_tt_output_report(out, 1, COMMAND_CALIBRATE_IDACS);
}
static int check_and_parse_short_test_response(uint8_t *buf,
        uint16_t read_length, uint8_t *status)
{
    struct tt_input_report *in = (struct tt_input_report *)buf;
    uint16_t length = 0;
    uint8_t command = 0;
    TS_LOG_INFO("%s:begin--!\n",__func__);
    if (read_length != 7)
        return -EINVAL;

    if (check_and_parse_tt_input_report(in, &length, &command)
            || command != COMMAND_SHORT_TEST
            || length != 7)
    return -EINVAL;

    *status = in->return_data[0];

    return 0;
}

static int check_and_parse_calibrate_idacs_response(uint8_t *buf,
        uint16_t read_length, uint8_t *status)
{
    struct tt_input_report *in = (struct tt_input_report *)buf;
    uint16_t length = 0;
    uint8_t command = 0;

    if (read_length != 6)
        return -EINVAL;

    if (check_and_parse_tt_input_report(in, &length, &command)
            || command != COMMAND_CALIBRATE_IDACS
            || length != 6)
    return -EINVAL;

    *status = in->return_data[0];

    return 0;
}

static int prepare_execute_panel_scan_report(uint8_t *buf)
{
    struct tt_output_report *out = (struct tt_output_report *)buf;

    return prepare_tt_output_report(out, 0, COMMAND_EXECUTE_PANEL_SCAN);
}

static int check_and_parse_execute_panel_scan_response(uint8_t *buf,
        uint16_t read_length, uint8_t *status)
{
    struct tt_input_report *in = (struct tt_input_report *)buf;
    uint16_t length = 0;
    uint8_t command = 0;

    if (read_length != 6)
        return -EINVAL;

    if (check_and_parse_tt_input_report(in, &length, &command)
            || command != COMMAND_EXECUTE_PANEL_SCAN
            || length != 6)
    return -EINVAL;

    *status = in->return_data[0];

    return 0;
}

static int prepare_retrieve_panel_scan_report(uint8_t *buf,
        uint16_t read_offset, uint16_t read_length, uint8_t data_id)
{
    struct tt_output_report *out = (struct tt_output_report *)buf;

    out->parameters[0] = LO_BYTE(read_offset);
    out->parameters[1] = HI_BYTE(read_offset);
    out->parameters[2] = LO_BYTE(read_length);
    out->parameters[3] = HI_BYTE(read_length);
    out->parameters[4] = data_id;

    return prepare_tt_output_report(out, 5, COMMAND_RETRIEVE_PANEL_SCAN);
}

static int check_and_parse_retrieve_panel_scan_response(uint8_t *buf,
        uint16_t read_length, uint8_t *status, uint8_t *data_id,
        uint16_t *actual_read_length, uint8_t *data_format, uint8_t *data)
{
    struct tt_input_report *in = (struct tt_input_report *)buf;
    uint16_t length = 0;
    uint8_t command = 0;

    if (read_length < 6)
        return -EINVAL;

    if (check_and_parse_tt_input_report(in, &length, &command)
            || command != COMMAND_RETRIEVE_PANEL_SCAN
            || length < 6)
        return -EINVAL;

    *status = in->return_data[0];
    if (read_length == 6)
        return 0;

    if (read_length >= 7)
        *data_id = in->return_data[1];

    if (read_length >= 9)
        *actual_read_length = MERGE8(in->return_data[2],
                in->return_data[3]);

    if (read_length >= 10)
        *data_format = in->return_data[4];

    length = *actual_read_length * GET_ELEMENT_SIZE(*data_format);

    if (read_length != 10 + length)
        return -EINVAL;

    memcpy(data, &in->return_data[5], length);

    return 0;
}

static int prepare_get_hid_descriptor_report(uint8_t *buf,
        uint16_t hid_desc_register)
{
    buf[0] = LO_BYTE(hid_desc_register);
    buf[1] = HI_BYTE(hid_desc_register);

    return 2;
}

static int check_and_parse_get_hid_descriptor_response(
        uint8_t *buf, uint16_t read_length,
        struct hid_desc *hid_desc)
{
    if (read_length != 32)
        return -EINVAL;

    hid_desc->hid_desc_len = MERGE8(buf[0], buf[1]);
    hid_desc->packet_id = buf[2];
    hid_desc->reserved_byte = buf[3];
    hid_desc->bcd_version = MERGE8(buf[4], buf[5]);
    hid_desc->report_desc_len = MERGE8(buf[6], buf[7]);
    hid_desc->report_desc_register = MERGE8(buf[8], buf[9]);
    hid_desc->input_register = MERGE8(buf[10], buf[11]);
    hid_desc->max_input_len = MERGE8(buf[12], buf[13]);
    hid_desc->output_register = MERGE8(buf[14], buf[15]);
    hid_desc->max_output_len = MERGE8(buf[16], buf[17]);
    hid_desc->command_register = MERGE8(buf[18], buf[19]);
    hid_desc->data_register = MERGE8(buf[20], buf[21]);
    hid_desc->vendor_id = MERGE8(buf[22], buf[23]);
    hid_desc->product_id = MERGE8(buf[24], buf[25]);
    hid_desc->version_id = MERGE8(buf[26], buf[27]);
    hid_desc->reserved[0] = buf[28];
    hid_desc->reserved[1] = buf[29];
    hid_desc->reserved[2] = buf[30];
    hid_desc->reserved[3] = buf[31];

        return 0;
}

static int get_hid_descriptor(uint16_t hid_desc_register, struct hid_desc *hid_desc)
{
    int size;
    int ret;

    size = prepare_get_hid_descriptor_report(report_buffer, hid_desc_register);

    ret = pip_get_sensor_data(gdev, report_buffer, size, response_buffer, &size);
    if (ret < 0) {
        TS_LOG_ERR("%s, Unable to send get hid descriptor!\n", __func__);
        goto exit;
    }

    ret = check_and_parse_get_hid_descriptor_response(response_buffer, size, hid_desc);
    if (ret < 0) {
        TS_LOG_ERR("%s, Check get hid descriptor response fails!\n", __func__);
        goto exit;
    }

exit:
    return ret;
}

int pip_init(char *device_path, uint16_t hid_desc_register)
{
    int ret = 0;

    report_buffer = kzalloc(REPORT_BUFFER_SIZE, GFP_KERNEL);
    if (!report_buffer) {
        ret = -ENOMEM;
        goto exit;
    }

    response_buffer = kzalloc(RESPONSE_BUFFER_SIZE, GFP_KERNEL);
    if (!response_buffer) {
        ret = -ENOMEM;
        goto exit;
    }
    command_buf = (char*)kzalloc(REPORT_BUFFER_SIZE, GFP_KERNEL);
    if (!command_buf) {
        ret = -ENOMEM;
        goto exit;
    }
	
    ret = get_hid_descriptor(hid_desc_register, &hid_desc);
    if (ret < 0) {
        TS_LOG_ERR("%s: Error on get hid descriptor!\n",
            __func__);
        goto exit;
    }

    return 0;

exit:
    return ret;
}

void pip_exit(void)
{
    kfree(response_buffer);
    response_buffer = NULL;

    kfree(report_buffer);
    report_buffer = NULL;

    kfree(command_buf);
    command_buf = NULL;
}

int pip_get_system_information(struct pip_sysinfo *sysinfo)
{
    int size;
    int ret = 0;

    if (!sysinfo)
        return -EINVAL;

    size = prepare_get_system_info_report(report_buffer);

    ret = pip_get_sensor_data(gdev, report_buffer, size, response_buffer, &size);
    if (ret < 0) {
        TS_LOG_ERR("%s,Unable to send command!\n", __func__);
        goto exit;
    }

    ret = check_and_parse_get_system_info_response(response_buffer, size,
            &sysinfo->cy_data, &sysinfo->sens_conf_data);
    if (ret < 0) {
        TS_LOG_ERR("%s, Check get system info response fails!\n", __func__);
        goto exit;
    }

exit:
    return ret;
}

int pip_suspend_scanning(void)
{
    int size;
    int ret = 0;

    size = prepare_suspend_scanning_report(report_buffer);

    ret = pip_get_sensor_data(gdev, report_buffer, size, response_buffer, &size);
    if (ret < 0) {
        TS_LOG_ERR("%s, Unable to send suspend scanning command!\n", __func__);
        goto exit;
    }

    ret = check_suspend_scanning_response(response_buffer, size);
    if (ret < 0) {
        TS_LOG_ERR("%s, Check suspend scanning response fails!\n", __func__);
        goto exit;
    }

exit:
    return ret;
}

int pip_resume_scanning(void)
{
    int size;
    int ret = 0;

    size = prepare_resume_scanning_report(report_buffer);

    ret = pip_get_sensor_data(gdev, report_buffer, size, response_buffer, &size);
    if (ret < 0) {
        TS_LOG_ERR("%s, Unable to send resume scanning command!\n", __func__);
        goto exit;
    }

    ret = check_resume_scanning_response(response_buffer, size);
    if (ret < 0) {
        TS_LOG_ERR("%s, Check resume scanning response fails!\n", __func__);
        goto exit;
    }

exit:
    return ret;
}

int pip_get_parameter(uint8_t parameter_id, uint32_t *parameter_value)
{
    int size;
    int ret;

    if (!parameter_value)
        return -EINVAL;

    size = prepare_get_parameter_report(report_buffer, parameter_id);

    ret = pip_get_sensor_data(gdev, report_buffer, size, response_buffer, &size);
    if (ret < 0) {
        TS_LOG_ERR("%s, Unable to send get parameter command!\n", __func__);
        goto exit;
    }

    ret = check_and_parse_get_parameter_response(response_buffer, size,
            parameter_value);
    if (ret < 0) {
        TS_LOG_ERR("%s, Check get parameter fails!\n", __func__);
        goto exit;
    }

exit:
    return ret;
}

int pip_read_data_block(uint16_t row_number, uint16_t read_length,
        uint8_t block_id, uint16_t *actual_read_length, uint8_t *data)
{
    uint8_t status;
    uint8_t ret_block_id = 0;
    uint16_t data_crc;
    int size;
    int ret = 0;

    if (!actual_read_length || !data)
        return -EINVAL;
    memset(report_buffer, 0,REPORT_BUFFER_SIZE );
    
    size = prepare_read_data_block_report(report_buffer, row_number,
        read_length, block_id);

    ret = pip_get_sensor_data(gdev, report_buffer, size,response_buffer, &size);
    if (ret < 0) {
        TS_LOG_ERR("%s, Unable to send read data block command!\n", __func__);
        goto exit;
    }

    ret = check_and_parse_read_data_block_response(response_buffer,
        size, &status, &ret_block_id, actual_read_length,
        data, &data_crc);
    if (ret < 0) {
        TS_LOG_ERR("%s, Check read data block fails!\n", __func__);
        goto exit;
    }
    TS_LOG_DEBUG("block_id = %x,ret_block_id = %x,status = %x\n",block_id,ret_block_id ,status);
    if (status != SUCCESS || ret_block_id != block_id)
    {
        TS_LOG_ERR("%s, block id not match!\n", __func__);
        return -EINVAL;
    }

    /* TODO: Perform data CRC check here */

exit:
    return ret;
}

int pip_set_parameter(uint8_t parameter_id, uint8_t parameter_size,
        uint32_t parameter_value)
{
    uint8_t ret_param_id;
    uint8_t ret_param_size;
    int size;
    int ret = 0;

    size = prepare_set_parameter_report(report_buffer, parameter_id,
            parameter_size, parameter_value);

    ret = pip_get_sensor_data(gdev, report_buffer, size, response_buffer, &size);
    if (ret < 0) {
        TS_LOG_ERR("%s, Unable to send set parameter command!\n", __func__);
        goto exit;
    }

    ret = check_and_parse_set_parameter_response(response_buffer, size,
            &ret_param_id, &ret_param_size);
    if (ret < 0) {
        TS_LOG_ERR("%s, Check set parameter fails!\n", __func__);
        goto exit;
    }

    if (ret_param_id != parameter_id || ret_param_size != parameter_size)
    {
        TS_LOG_ERR("%s, parameter_id or parameter_size not match!\n", __func__);
        return -EINVAL;
    }

exit:
    return ret;
}

int pip_retrieve_data_structure(uint16_t read_offset, uint16_t read_length,
        uint8_t data_id, uint16_t *actual_read_length,
        uint8_t *data_format, uint8_t *data)
{
    uint8_t status;
    uint8_t ret_data_id = 0;
    int size;
    int ret = 0;

    if (!actual_read_length || !data_format || !data)
        return -EINVAL;

    size = prepare_retrieve_data_structure_report(report_buffer, read_offset,
            read_length, data_id);

    ret = pip_get_sensor_data(gdev, report_buffer, size, response_buffer, &size);
    if (ret < 0) {
        TS_LOG_ERR("%s, Unable to send retrieve data structure command!\n", __func__);
        goto exit;
    }

    ret = check_and_parse_retrieve_data_structure_response(response_buffer,
            size, &status, &ret_data_id, actual_read_length,
            data_format, data);
    if (ret < 0) {
        TS_LOG_ERR("%s, Check retrieve data structure fails!\n", __func__);
        goto exit;
    }

    if (status != SUCCESS || ret_data_id != data_id)
    {
        TS_LOG_ERR("%s, data id not match!\n", __func__);
        return -EINVAL;
    }

exit:
    return ret;
}

int pip_short_test(void)
{
    uint8_t status;
    int size;
    int ret;
    TS_LOG_INFO("%s:====================begin--!\n",__func__);
    size = prepare_short_test_report(report_buffer);

    ret = pip_get_sensor_data(gdev, report_buffer, size, response_buffer, &size);
    if (ret < 0) {
        TS_LOG_ERR("%s:Unable to send short test command!\n",__func__);
        goto exit;
    }
    ret = check_and_parse_short_test_response(response_buffer, size,&status);
    if (ret) {
        TS_LOG_ERR("%s:Check short test fails!\n",__func__);
        goto exit;
    }

    if (status != SUCCESS)
    {
        TS_LOG_ERR("%s:short test status error!\n",__func__);
        return -EIO;
    }

    TS_LOG_INFO("%s:finish--!\n",__func__);
exit:
    return ret;
}

int pip_calibrate_idacs(uint8_t sensing_mode)
{
    uint8_t status;
    int size;
    int ret = 0;

    size = prepare_calibrate_idacs_report(report_buffer, sensing_mode);

    ret = pip_get_sensor_data(gdev, report_buffer, size, response_buffer, &size);
    if (ret < 0) {
        TS_LOG_ERR("%s, Unable to send calibrate idacs command!\n", __func__);
        goto exit;
    }

    ret = check_and_parse_calibrate_idacs_response(response_buffer, size,
            &status);
    if (ret < 0) {
        TS_LOG_ERR("%s, Check calibrate idacs fails!\n", __func__);
        goto exit;
    }

    if (status != SUCCESS) {
        TS_LOG_ERR("%s:calibrate idacs status  error!\n",__func__);
        return -EIO;
    }

exit:
    return ret;
}

int pip_execute_panel_scan(void)
{
    uint8_t status;
    int size;
    int ret = 0;

    size = prepare_execute_panel_scan_report(report_buffer);

    ret = pip_get_sensor_data(gdev, report_buffer, size, response_buffer, &size);
    if (ret < 0) {
        TS_LOG_ERR("%s, Unable to send execute panel scan command!\n", __func__);
        goto exit;
    }

    ret = check_and_parse_execute_panel_scan_response(response_buffer, size,
            &status);
    if (ret < 0) {
        TS_LOG_ERR("%s, Check execute panel scan fails!\n", __func__);
        goto exit;
    }

    if (status != SUCCESS) {
        TS_LOG_ERR("%s:execute panel status error!\n",__func__);
        return -EIO;
    }

exit:
    return ret;
}

int pip_retrieve_panel_scan(uint16_t read_offset, uint16_t read_length,
        uint8_t data_id, uint16_t *actual_read_length,
        uint8_t *data_format, uint8_t *data)
{
    uint8_t status;
    uint8_t ret_data_id = 0;
    int size;
    int ret = 0;

    if (!actual_read_length || !data_format || !data)
        return -EINVAL;

    size = prepare_retrieve_panel_scan_report(report_buffer, read_offset,
            read_length, data_id);

    ret = pip_get_sensor_data(gdev, report_buffer, size, response_buffer, &size);
    if (ret < 0) {
        TS_LOG_ERR("%s, Unable to send retrieve panel scan command!\n", __func__);
        goto exit;
    }

    ret = check_and_parse_retrieve_panel_scan_response(response_buffer,
            size, &status, &ret_data_id, actual_read_length,
            data_format, data);
    if (ret < 0) {
        TS_LOG_ERR("%s, Check retrieve panel scan fails!\n", __func__);
        goto exit;
    }

    if (status != SUCCESS || ret_data_id != data_id)
    {
        TS_LOG_ERR("%s, data id not match!\n", __func__);
        return -EINVAL;
    }

exit:
    return ret;
}
