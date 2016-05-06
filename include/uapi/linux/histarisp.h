/*
 * include/uapi/linux/histarisp.h
 *
 * Copyright (c) 2013-2014 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef HISTAR_ISP_USER_H
#define HISTAR_ISP_USER_H

#include <asm/ioctl.h>

#define MAX_INPUT_STREAM_NUM (2)
#define MAX_STREAM_NUM       (8)
/* based on msg len is 464 */
#define MAX_SET_ISP_NR  1//50//53//59
#define MAX_GET_ISP_NR  1//100//108//119
#define MAX_SET_I2C_NR  1//35//35//39
#define MAX_GET_I2C_NR  1//50//53//59

#define HWSENSOR_IOCTL_POWER_UP     _IOWR('i', 0x1201, rpmsg_ioctl_arg_t)
#define HWSENSOR_IOCTL_POWER_DOWN   _IOWR('i', 0x1202, rpmsg_ioctl_arg_t)

typedef struct rpmsg_ioctl_arg {
	int index;
	char name[32];
}rpmsg_ioctl_arg_t;

typedef enum
{
    PIXEL_FMT_RAW,
    PIXEL_FMT_JPEG,
    PIXEL_FMT_YUV422,
    PIXEL_FMT_YUV420_NV12,
    PIXEL_FMT_YUV420_NV21,
} pix_format_e;

typedef enum
{
    STREAM_TYPE_INPUT,
    STREAM_TYPE_OUTPUT,
} stream_type_e;

typedef enum
{
    REGISTER_TYPE_ISP,
    REGISTER_TYPE_I2C,
} register_type_e;

typedef enum
{
    COMMAND_QUERY_CAPABILITY = 0x1000,
	COMMAND_ACQUIRE_CAMERA,
    COMMAND_RELEASE_CAMERA,
    COMMAND_USECASE_CONFIG,
    COMMAND_GET_OTP,
    COMMAND_REQUEST,
    COMMAND_JPEG_ENCODE,
    COMMAND_MAP_BUFFER,
    COMMAND_UNMAP_BUFFER,
    COMMAND_CALIBRATION_DATA,
    COMMAND_SET_ISP_REGISTERS,
    COMMAND_GET_ISP_REGISTER,
    COMMAND_SET_IIC_REGISTER,
    COMMAND_GET_IIC_REGISTER,
    COMMAND_TEST_CASE_INTERFACE,
    COMMAND_FLUSH,
    COMMAND_EXTEND_SET,
    COMMAND_EXTEND_GET,

    /* Response items. */
    QUERY_CAPABILITY_RESPONSE = 0x2000,
    ACQUIRE_CAMERA_RESPONSE,
    RELEASE_CAMERA_RESPONSE,
    USECASE_CONFIG_RESPONSE,
    GET_OTP_RESPONSE,
    REQUEST_RESPONSE,
    JPEG_ENCODE_RESPONSE,
    MAP_BUFFER_RESPONSE,
    UNMAP_BUFFER_RESPONSE,
    CALIBRATION_DATA_RESPONSE,
    SET_ISP_REGISTERS_RESPONSE,
    GET_ISP_REGISTER_RESPONSE,
    SET_IIC_REGISTER_RESPONSE,
    GET_IIC_REGISTER_RESPONSE,
    TEST_CASE_RESPONSE,
    FLUSH_RESPONSE,
    EXTEND_SET_RESPONSE,
    EXTEND_GET_RESPONSE,
} api_id_e;

typedef struct _msg_req_query_capability_t
{
    unsigned int cam_id;
    char product_name[32];
    char sensor_name[32];
    unsigned int input_settings_buffer;
} msg_req_query_capability_t;

typedef struct _msg_ack_query_capability_t
{
    unsigned int cam_id;
    char product_name[32];
    char sensor_name[32];
    unsigned int output_metadata_buffer;
    int status;
} msg_ack_query_capability_t;

typedef struct _msg_req_acquire_camera_t
{
    unsigned int cam_id;
    char sensor_name[32];
    unsigned int input_otp_buffer;
    unsigned int buffer_size;
} msg_req_acquire_camera_t;

typedef struct _msg_ack_acquire_camera_t
{
    unsigned int cam_id;
    char sensor_name[32];
} msg_ack_acquire_camera_t;

typedef struct _msg_req_release_camera_t
{
    unsigned int cam_id;
} msg_req_release_camera_t;

typedef struct _msg_ack_release_camera_t
{
    unsigned int cam_id;
} msg_ack_release_camera_t;

typedef struct _stream_config_t
{
    unsigned int type;
    unsigned int width;
    unsigned int height;
    unsigned int stride;
    unsigned int format;
} stream_config_t;

typedef struct _msg_req_usecase_config_t
{
    unsigned int cam_id;
    unsigned int extension;
    unsigned int stream_nr;
    stream_config_t stream_cfg[MAX_STREAM_NUM];
} msg_req_usecase_config_t;

typedef struct _msg_ack_usecase_config_t
{
    unsigned int cam_id;
    int status;
    unsigned int sensor_width;
    unsigned int sensor_height;
} msg_ack_usecase_config_t;

typedef struct _msg_req_get_otp_t
{
    unsigned int cam_id;
    char sensor_name[32];
    unsigned int input_otp_buffer;
    unsigned int buffer_size;
} msg_req_get_otp_t;

typedef struct _msg_ack_get_otp_t
{
    unsigned int cam_id;
    char sensor_name[32];
    unsigned int output_otp_buffer;
    unsigned int buffer_size;
    int               status;
} msg_ack_get_otp_t;

typedef struct _stream_info_t
{
    unsigned int buffer;
    unsigned int width;
    unsigned int height;
    unsigned int stride;
    unsigned int format;
} stream_info_t;

typedef struct _msg_req_request_t
{
    unsigned int cam_id;
    unsigned int num_targets;
    unsigned int target_map;
    unsigned int frame_number;
    unsigned int buf[MAX_STREAM_NUM];
    unsigned int input_setting_buffer;
    unsigned int output_metadata_buffer;
} msg_req_request_t;

typedef struct _msg_ack_request_t
{
    unsigned int cam_id;
    unsigned int num_targets;
    unsigned int target_map;
    unsigned int frame_number;
    stream_info_t stream_info[MAX_STREAM_NUM];        
    unsigned int output_metadata_buffer;
} msg_ack_request_t;

typedef struct _msg_req_jpeg_encode_t
{
    unsigned int width;
    unsigned int height;
    unsigned int stride;
    unsigned int input_buffer_y;
    unsigned int input_buffer_uv;
    unsigned int output_buffer;
    unsigned int quality;
    unsigned int format;
} msg_req_jpeg_encode_t;

typedef struct _msg_ack_jpeg_encode_t
{
    unsigned int output_buffer;
    unsigned int file_size;
    int status;
} msg_ack_jpeg_encode_t;

typedef struct _msg_req_map_buffer_t
{
    unsigned int cam_id;
    unsigned int mem_pool_buffer;
    unsigned int buffer_size;
} msg_req_map_buffer_t;

typedef struct _msg_ack_map_buffer_t
{
    unsigned int cam_id;
    int status;
} msg_ack_map_buffer_t;

typedef struct _msg_req_unmap_buffer_t
{
    unsigned int cam_id;
    unsigned int buffer;
} msg_req_unmap_buffer_t;

typedef struct _msg_ack_unmap_buffer_t
{
    unsigned int cam_id;
    int status;
} msg_ack_unmap_buffer_t;

typedef struct _msg_req_cal_data_t
{
    unsigned int cam_id;
    unsigned int buffer_size;
    unsigned int cal_data_buffer;
} msg_req_cal_data_t;

typedef struct _msg_ack_cal_data_t
{
    unsigned int cam_id;
    int status;
} msg_ack_cal_data_t;

typedef struct _isp_reg_info_t
{
    unsigned int register_address;
    unsigned int register_value;
} isp_reg_info_t;

typedef struct _msg_req_set_isp_regs_t
{
    unsigned int register_type;
    unsigned int register_count;
    isp_reg_info_t reg_info[MAX_SET_ISP_NR];
} msg_req_set_isp_regs_t;

typedef struct _msg_ack_set_isp_regs_t
{
    int status;
} msg_ack_set_isp_regs_t;

typedef struct _msg_req_get_isp_regs_t
{
    unsigned int register_count;
    unsigned int register_address[MAX_GET_ISP_NR];
} msg_req_get_isp_regs_t;

typedef struct _msg_ack_get_isp_regs_t
{
    int status;
    unsigned int register_count;
    unsigned int register_value[MAX_GET_ISP_NR];
} msg_ack_get_isp_regs_t;

typedef struct _i2c_reg_set_info_t
{
    unsigned int  register_address;
    unsigned int  register_value;
    unsigned char length;                   /**< value length */
} i2c_reg_set_info_t;

typedef struct _msg_req_set_i2c_regs_t
{
    unsigned int register_type;
    unsigned int slave_address;
    unsigned int register_count;
    i2c_reg_set_info_t reg_info[MAX_SET_I2C_NR];
} msg_req_set_i2c_regs_t;

typedef struct _msg_ack_set_i2c_regs_t
{
    int status;
} msg_ack_set_i2c_regs_t;

typedef struct _i2c_reg_get_info_t
{
    unsigned int register_address;
    unsigned char length;                   /**< request getting the len of the register value */
} i2c_reg_get_info_t;

typedef struct _msg_req_get_i2c_regs_t
{
    unsigned int register_type;
    unsigned int slave_address;
    unsigned int register_count;
    i2c_reg_get_info_t reg_info[MAX_GET_I2C_NR];
} msg_req_get_i2c_regs_t;

typedef struct _msg_ack_get_i2c_regs_t
{
    int status;
    unsigned int register_count;
    unsigned int register_value[MAX_GET_I2C_NR];
} msg_ack_get_i2c_regs_t;

typedef struct _msg_req_test_case_interface_t
{
    unsigned int case_handle;
    char         case_name[64];
} msg_req_test_case_interface_t;

typedef struct _msg_ack_test_case_interface_t
{
    int   status;
    int   flag;
} msg_ack_test_case_interface_t;

typedef struct _msg_req_flush_t
{
    unsigned int cam_id;
} msg_req_flush_t;

typedef struct _msg_ack_flush_t
{
    int status;
} msg_ack_flush_t;

typedef enum
{
    SUBCMD_ES_WATCHDOG,
    SUBCMD_ES_SYNCLOG,
} extendset_info_e;

typedef enum
{
    SUBCMD_EG_LLT,
    SUBCMD_EG_ST,
} extendget_info_e;

typedef struct _msg_subreq_es_watchdog_t
{
    unsigned int enable_watchdog;
    unsigned int timeout;
} msg_subreq_es_watchdog_t;

typedef struct _msg_subreq_es_synclog_t
{
    unsigned int reserved;
} msg_subreq_es_synclog_t;

typedef struct _msg_subreq_eg_llt_t
{
    /*TODO*/
} msg_subreq_eg_llt_t;

typedef struct _msg_subreq_eg_st_t
{
    /*TODO*/
} msg_subreq_eg_st_t;

typedef struct _msg_req_extend_set_t
{
    unsigned int cam_id;
    unsigned int extend_cmd;
    char         paras[400];
} msg_req_extend_set_t;

typedef struct _msg_ack_extend_set_t
{
    unsigned int cam_id;
    unsigned int extend_cmd;
    int          status;
} msg_ack_extend_set_t;

typedef struct _msg_req_extend_get_t
{
    unsigned int cam_id;
    unsigned int extend_cmd;
    char         paras[400];
} msg_req_extend_get_t;

typedef struct _msg_ack_extend_get_t
{
    unsigned int cam_id;
    unsigned int extend_cmd;
    char         paras[400];
    int          status;
} msg_ack_extend_get_t;

struct msg_base;

typedef void (*msg_looper_handler)(struct msg_base*, void*);

typedef struct msg_base
{
    struct list_head link;
    msg_looper_handler handler;
    void* user;
} msg_base_t;

typedef struct _isp_msg_t
{
    unsigned int message_size;
    unsigned int api_name;
    unsigned int message_id;
    unsigned int message_hash;
    union
    {
        /* Request items. */
        msg_req_query_capability_t      req_query_capability;
        msg_req_acquire_camera_t        req_acquire_camera;
        msg_req_release_camera_t        req_release_camera;
        msg_req_usecase_config_t        req_usecase_config;
        msg_req_get_otp_t               req_get_otp;
        msg_req_request_t               req_request;
        msg_req_map_buffer_t            req_map_buffer;
        msg_req_unmap_buffer_t          req_unmap_buffer;
        msg_req_cal_data_t              req_cal_data;
        msg_req_set_isp_regs_t          req_set_isp_regs;
        msg_req_get_isp_regs_t          req_get_isp_regs;
        msg_req_set_i2c_regs_t          req_set_i2c_regs;
        msg_req_get_i2c_regs_t          req_get_i2c_regs;
        msg_req_test_case_interface_t   req_test_case_interface;
        msg_req_flush_t                 req_flush;
        msg_req_extend_set_t            req_extend_set;
        msg_req_extend_get_t            req_extend_get;
        msg_req_jpeg_encode_t           req_jpeg_encode;

        /* Response items. */
        msg_ack_query_capability_t      ack_query_capability;
        msg_ack_acquire_camera_t        ack_require_camera;
        msg_ack_release_camera_t        ack_release_camera;
        msg_ack_usecase_config_t        ack_usecase_config;
        msg_ack_get_otp_t               ack_get_otp;
        msg_ack_request_t               ack_request;
        msg_ack_map_buffer_t            ack_map_buffer;
        msg_ack_unmap_buffer_t          ack_unmap_buffer;
        msg_ack_cal_data_t              ack_cal_data;
        msg_ack_set_isp_regs_t          ack_set_isp_regs;
        msg_ack_get_isp_regs_t          ack_get_isp_regs;
        msg_ack_set_i2c_regs_t          ack_set_i2c_regs;
        msg_ack_get_i2c_regs_t          ack_get_i2c_regs;
        msg_ack_test_case_interface_t   ack_test_case_interface;
        msg_ack_flush_t                 ack_flush;
        msg_ack_extend_set_t            ack_extend_set;
        msg_ack_extend_get_t            ack_extend_get;
        msg_ack_jpeg_encode_t           ack_jpeg_encode;
    }u;
    msg_base_t base;
    short token;
    struct rpmsg_ept *ept;
} isp_msg_t;

void msg_init_req(isp_msg_t* req, unsigned int api_name, unsigned int msg_id);
void msg_init_ack(isp_msg_t* req, isp_msg_t* ack);

#endif /*MESSAGE_H_INCLUDED*/
