


#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#define MAX_PKT_LENGTH  (128)
#define MAX_PKT_LENGTH_AP     512
#define MAX_LOG_LEN     100
#define MAX_PATTERN_SIZE 16
#define MAX_ACCEL_PARAMET_LENGTH    100
#define MAX_MAG_PARAMET_LENGTH    100
#define MAX_GYRO_PARAMET_LENGTH    100
#define MAX_ALS_PARAMET_LENGTH    100
#define MAX_PS_PARAMET_LENGTH    100
#define MAX_I2C_DATA_LENGTH     50
#define MAX_MAG_CALIBRATE_DATA_LENGTH     32
#define MAX_CAP_PROX_CALIBRATE_DATA_LENGTH     16

#ifdef CONFIG_IOM3_RECOVERY
#define IOM3_RECOVERY_UNINIT	(0)
#define IOM3_RECOVERY_IDLE		(IOM3_RECOVERY_UNINIT + 1)
#define IOM3_RECOVERY_START	(IOM3_RECOVERY_IDLE + 1)
#define IOM3_RECOVERY_MINISYS	(IOM3_RECOVERY_START + 1)
#define IOM3_RECOVERY_DOING	(IOM3_RECOVERY_MINISYS + 1)
#define IOM3_RECOVERY_FAILED	(IOM3_RECOVERY_DOING + 1)
#endif
//tag--------------------------------------------------------
typedef enum
{
    TAG_BEGIN = 0x01,
    TAG_SENSOR_BEGIN = TAG_BEGIN,
    TAG_ACCEL = TAG_SENSOR_BEGIN,
    TAG_GYRO,
    TAG_MAG,
    TAG_ALS,
    TAG_PS,
    TAG_SCREEN_ROTATE,
    TAG_LINEAR_ACCEL,
    TAG_GRAVITY,
    TAG_ORIENTATION,
    TAG_ROTATION_VECTORS,/*10*/
    TAG_PRESSURE,
    TAG_TEMP,
    TAG_HUMIDITY,
    TAG_AMBIENT_TEMP,
    TAG_LABC,
    TAG_HALL,
    TAG_MAG_UNCALIBRATED,
    TAG_GAME_RV,
    TAG_GYRO_UNCALIBRATED,
    TAG_SIGNIFICANT_MOTION,/*20*/
    TAG_STEP_DETECTOR,
    TAG_STEP_COUNTER,
    TAG_GEOMAGNETIC_RV,
    TAG_AIRPRESS,
    TAG_HANDPRESS,
    TAG_CAP_PROX,
    TAG_SENSOR_END,/*27*/
    TAG_TP = TAG_SENSOR_END,
    TAG_SPI,
    TAG_I2C,
    TAG_RGBLIGHT,
    TAG_BUTTONLIGHT,
    TAG_BACKLIGHT,
    TAG_VIBRATOR,
    TAG_SYS,/*34*/
    TAG_LOG,
    TAG_MOTION,
    TAG_CURRENT,

    TAG_END
}obj_tag_t;

extern char* obj_tag_str[];
//cmd----------------------------------------------------------------------
typedef enum
{
    //common command
    CMD_CMN_OPEN_REQ = 0x01,
    CMD_CMN_OPEN_RESP,
    CMD_CMN_CLOSE_REQ,
    CMD_CMN_CLOSE_RESP,
    CMD_CMN_INTERVAL_REQ,
    CMD_CMN_INTERVAL_RESP,

    CMD_PRIVATE = 0x1f,

    //accelerometer command
    CMD_ACCEL_DATA_REQ = CMD_PRIVATE,
    CMD_ACCEL_DATA_RESP,
    CMD_ACCEL_SELFCALI_REQ,
    CMD_ACCEL_SELFCALI_RESP,
    CMD_ACCEL_PARAMET_REQ,
    CMD_ACCEL_PARAMET_RESP,
    CMD_ACCEL_OFFSET_REQ,
    CMD_ACCEL_OFFSET_RESP,
    CMD_ACCEL_SELFTEST_REQ,
    CMD_ACCEL_SELFTEST_RESP,

    //gyroscopy command
    CMD_GYRO_DATA_REQ = CMD_PRIVATE,
    CMD_GYRO_DATA_RESP,
    CMD_GYRO_SELFTEST_REQ,
    CMD_GYRO_SELFTEST_RESP,
    CMD_GYRO_PARAMET_REQ,
    CMD_GYRO_PARAMET_RESP,
    CMD_GYRO_CONFIG_REQ,
    CMD_GYRO_CONFIG_RESP,

    //magnetometer command
    CMD_MAG_DATA_REQ = CMD_PRIVATE,
    CMD_MAG_DATA_RESP,
    CMD_MAG_SELFTEST_REQ,
    CMD_MAG_SELFTEST_RESP,
    CMD_MAG_PARAMET_REQ,
    CMD_MAG_PARAMET_RESP,
    CMD_MAG_SET_CALIBRATE_TO_MCU_REQ,
    CMD_MAG_SET_CALIBRATE_TO_MCU_RESP,
    CMD_MAG_SEND_CALIBRATE_TO_AP_REQ,
    CMD_MAG_SEND_CALIBRATE_TO_AP_RESP,

    //ambient light sensor
    CMD_ALS_DATA_REQ = CMD_PRIVATE,
    CMD_ALS_DATA_RESP,
    CMD_ALS_PARAMET_REQ,
    CMD_ALS_PARAMET_RESP,

    //proximity sensor
    CMD_PS_DATA_REQ = CMD_PRIVATE,
    CMD_PS_DATA_RESP,
    CMD_PS_PARAMET_REQ,
    CMD_PS_PARAMET_RESP,

    CMD_SCREEN_ROTATE_DATA_REQ = CMD_PRIVATE,
    CMD_SCREEN_ROTATE_DATA_RESP,

    //linear acceleration
    CMD_LINEAR_ACCEL_DATA_REQ = CMD_PRIVATE,
    CMD_LINEAR_ACCEL_DATA_RESP,

    //gravity
    CMD_GRAVITY_DATA_REQ = CMD_PRIVATE,
    CMD_GRAVITY_DATA_RESP,

    //orientation
    CMD_ORIENTATION_DATA_REQ = CMD_PRIVATE,
    CMD_ORIENTATION_DATA_RESP,

    //rotation vectors
    CMD_ROTATION_VECTORS_DATA_REQ = CMD_PRIVATE,
    CMD_ROTATION_VECTORS_DATA_RESP,

    //touch
    CMD_TP_POSITION_REQ = CMD_PRIVATE,
    CMD_TP_POSITION_RESP,
    CMD_TP_RELEASE_REQ,
    CMD_TP_RELEASE_RESP,

    //SPI
    CMD_SPI_BAUD_REQ = CMD_PRIVATE,
    CMD_SPI_BAUD_RESP,

    //I2C
    CMD_I2C_READ_REQ = CMD_PRIVATE,
    CMD_I2C_READ_RESP,
    CMD_I2C_WRITE_REQ,
    CMD_I2C_WRITE_RESP,
    CMD_I2C_READ_ONLY_REQ,
    CMD_I2C_READ_ONLY_RESP,
    CMD_I2C_WRITE_ONLY_REQ,
    CMD_I2C_WRITE_ONLY_RESP,

    //RGB light and button light
    CMD_LIGHT_BRIGHT_REQ = CMD_PRIVATE,//ÕâÀïÊÇ´ò¿ªµÆµÄÃüÁî£¬¹Ø±ÕµÆÊ¹ÓÃÍ¨ÓÃÃüÁîCMD_CMN_CLOSE_REQ
    CMD_LIGHT_BRIGHT_RESP,
    CMD_LIGHT_FLICKER_REQ,
    CMD_LIGHT_FLICKER_RESP,

    //backlight
    CMD_BACKLIGHT_LEVEL_REQ = CMD_PRIVATE,
    CMD_BACKLIGHT_LEVEL_RESP,
    CMD_BACKLIGHT_OUTPUT_REQ,
    CMD_BACKLIGHT_OUTPUT_RESP,
    CMD_BACKLIGHT_OUTPUTSTOP_REQ,
    CMD_BACKLIGHT_OUTPUTSTOP_RESP,

    //vibrator
    CMD_VIBRATOR_SINGLE_REQ = CMD_PRIVATE,
    CMD_VIBRATOR_SINGLE_RESP,
    CMD_VIBRATOR_REPEAT_REQ,
    CMD_VIBRATOR_REPEAT_RESP,

    //system status
    CMD_SYS_STATUSCHANGE_REQ= CMD_PRIVATE,
    CMD_SYS_STATUSCHANGE_RESP,/*32*/

    CMD_SYS_DYNLOAD_REQ,
    CMD_SYS_DYNLOAD_RESP,
    CMD_SYS_HEARTBEAT_REQ,
    CMD_SYS_HEARTBEAT_RESP,


    //LOG
    CMD_LOG_REPORT_REQ = CMD_PRIVATE,
    CMD_LOG_REPORT_RESP,
    CMD_LOG_CONFIG_REQ,
    CMD_LOG_CONFIG_RESP,

    //motion
    CMD_MOTION_OPEN_REQ = CMD_PRIVATE,
    CMD_MOTION_OPEN_RESP,
    CMD_MOTION_CLOSE_REQ,
    CMD_MOTION_CLOSE_RESP,
    CMD_MOTION_INTERVAL_REQ,
    CMD_MOTION_INTERVAL_RESP,
    CMD_MOTION_ATTR_ENABLE_REQ,
    CMD_MOTION_ATTR_ENABLE_RESP,
    CMD_MOTION_ATTR_DISABLE_REQ,
    CMD_MOTION_ATTR_DISABLE_RESP,
    CMD_MOTION_REPORT_REQ,
    CMD_MOTION_REPORT_RESP,

    //step counter
    CMD_STEP_COUNTER_DATA_REQ = CMD_PRIVATE,
    CMD_STEP_COUNTER_DATA_RESP,

    //current
    CMD_CURRENT_GET_REQ = CMD_PRIVATE,
    CMD_CURRENT_GET_RESP,
    CMD_CURRENT_UNGET_REQ,
    CMD_CURRENT_UNGET_RESP,
    CMD_CURRENT_DATA_REQ,
    CMD_CURRENT_DATA_RESP,
    CMD_CURRENT_CFG_REQ,
    CMD_CURRENT_CFG_RESP,

    //airpress sensor
    CMD_AIRPRESS_DATA_REQ = CMD_PRIVATE,
    CMD_AIRPRESS_DATA_RESP,
    CMD_AIRPRESS_PARAMET_REQ,
    CMD_AIRPRESS_PARAMET_RESP,

    //handpress sensor
    CMD_HANDPRESS_DATA_REQ = CMD_PRIVATE,
    CMD_HANDPRESS_DATA_RESP,
    CMD_HANDPRESS_PARAMET_REQ,
    CMD_HANDPRESS_PARAMET_RESP,

    //cap_prox sensor
    CMD_CAP_PROX_DATA_REQ = CMD_PRIVATE,
    CMD_CAP_PROX_DATA_RESP,
    CMD_CAP_PROX_PARAMET_REQ,
    CMD_CAP_PROX_PARAMET_RESP,
    CMD_CAP_PROX_SET_CALIDATA_REQ,
    CMD_CAP_PROX_SET_CALIDATA_RESP,
    CMD_CAP_PROX_CALIBRATE_REQ,
    CMD_CAP_PROX_CALIBRATE_RESP,

    //err resp
    CMD_ERR_RESP = 0xfe,

}obj_cmd_t;


typedef enum
{
    EN_OK=0,
    EN_FAIL,
}err_no_t;

typedef enum
{
    NO_RESP,
    RESP,
} obj_resp_t;

typedef enum
{
    MOTION_TYPE_START,
    MOTION_TYPE_PICKUP,
    MOTION_TYPE_FLIP,
    MOTION_TYPE_PROXIMITY,
    MOTION_TYPE_SHAKE,
    MOTION_TYPE_TAP,
    MOTION_TYPE_TILT_LR,
    MOTION_TYPE_ROTATION,
    MOTION_TYPE_POCKET,
    MOTION_TYPE_ACTIVITY,
    MOTION_TYPE_TAKE_OFF,
    MOTION_TYPE_EXTEND_STEP_COUNTER,
/*!!!NOTE:add string in motion_type_str when add type*/
    MOTION_TYPE_END,
}motion_type_t;
extern char* motion_type_str[];

typedef enum
{
    //system status
    ST_NULL=0,
    ST_BEGIN,
    ST_POWERON =ST_BEGIN,
    ST_MINSYSREADY,
    ST_DYNLOAD,
    ST_MCUREADY,
    ST_TIMEOUTSCREENOFF,
    ST_SCREENON,
    ST_SCREENOFF,
    ST_SLEEP,
    ST_WAKEUP,
    ST_POWEROFF,
    ST_END
}sys_status_t;

typedef enum
{
    AUTO_MODE = 0,
    FIFO_MODE,
    INTEGRATE_MODE,
    REALTIME_MODE,
    MODE_END
}obj_report_mode_t;

typedef enum
{
    TYPE_STANDARD,
    TYPE_EXTEND
}type_step_counter_t;

//frame-------------------------------------------------------------------
typedef struct
{
    uint8_t tag;
    uint8_t partial_order;
}pkt_part_header_t;
typedef struct
{
    uint8_t tag;
    uint8_t cmd;
    uint8_t resp;//value CMD_RESP means need resp, CMD_NO_RESP means need not resp
    uint8_t partial_order;
    uint16_t tranid;
    uint16_t length;
}pkt_header_t;

#define CMN_RESP_LENGTH 4
#define RESP_ERRNO_LENGTH   4
#define PKT_LENGTH(pkt) (sizeof(pkt_header_t) + ((const pkt_header_t *)pkt)->length)

typedef struct
{
    uint8_t tag;
    uint8_t cmd;
    uint8_t resp;
    uint8_t partial_order;
    uint16_t tranid;
    uint16_t length;
    uint32_t errno;
}pkt_header_resp_t;

typedef struct
{
    pkt_header_t hd;
    uint8_t body[];
}pkt_t;

typedef struct
{
    pkt_header_t hd;
    uint32_t step_count;
    uint32_t begin_time;
    uint16_t record_count;
    uint16_t action_record[];
}pkt_step_counter_data_req_t;

typedef struct open_param {
    uint32_t period;
    uint32_t batch_count;
    uint8_t mode;
    uint8_t reserved[3];
}open_param_t;

typedef struct
{
    pkt_header_t hd;
    open_param_t param;
}pkt_cmn_interval_req_t;

typedef struct close_param{
    uint8_t reserved[4];
}close_param_t;

typedef struct
{
    pkt_header_t hd;
    close_param_t close_param;
}pkt_cmn_close_req_t;

typedef struct
{
    pkt_header_t hd;
    int32_t x;
    int32_t y;
    int32_t z;
    uint32_t accracy;
}pkt_xyz_data_req_t;

typedef struct
{
    pkt_header_resp_t hd;
    int8_t offset_x;
    int8_t offset_y;
    int8_t offset_z;
}pkt_accel_selfcali_resp_t;

typedef struct
{
    pkt_header_t hd;
    int32_t offset_x;
    int32_t offset_y;
    int32_t offset_z;
}pkt_accel_offset_req_t;

typedef struct
{
    pkt_header_t hd;
    int32_t a;
    int32_t b;
    int32_t c;
    int32_t d;
}pkt_rotation_vectors_data_req_t;

typedef struct
{
    pkt_header_t hd;
    uint8_t para[];
}pkt_parameter_req_t;
typedef struct
{
    pkt_header_t hd;
    uint8_t gyro_type;
}pkt_config_req_t;

typedef struct
{
    pkt_header_t hd;
    uint32_t data;
}pkt_als_data_req_t;

typedef struct
{
    pkt_header_t hd;
    uint32_t data;
}pkt_ps_data_req_t;

typedef struct
{
    pkt_header_t hd;
    uint32_t baudrate;
}pkt_spi_baud_req_t;

typedef struct
{
    pkt_header_t hd;
    uint8_t busid;
    uint8_t addr;
    uint8_t reg_type;
    uint16_t reg;
    uint16_t length;
}pkt_i2c_read_req_t;

typedef struct
{
    pkt_header_resp_t hd;
    uint8_t data[];
}pkt_i2c_read_resp_t;

typedef struct
{
    pkt_header_t hd;
    uint8_t busid;
    uint8_t addr;
    uint8_t reg_type;
    uint16_t reg;
    uint16_t length;
    uint8_t data[];
}pkt_i2c_write_req_t;

typedef struct
{
    pkt_header_t hd;
    uint32_t duration;
}pkt_vibrator_single_req_t;

typedef struct
{
    pkt_header_t hd;
    uint32_t index;
    uint32_t size;
    uint32_t pattern[MAX_PATTERN_SIZE];
}pkt_vibrator_repeat_req_t;

typedef struct
{
    pkt_header_t hd;
    uint32_t rgb;
}pkt_light_bright_req_t;

typedef struct
{
    pkt_header_t hd;
    uint32_t rgb;
    uint32_t ontime;
    uint32_t offtime;
}pkt_light_flicker_req_t;


typedef struct
{
    pkt_header_t hd;
    uint32_t level;
}pkt_baklight_level_req_t;

typedef struct
{
    pkt_header_t hd;
    uint32_t freq;
    uint32_t duty;
}pkt_backlight_output_req_t;

typedef struct
{
    pkt_header_t hd;
    uint16_t status;//sys_status_t;
    uint16_t version;//ÔÚµÚÒ»´Î·¢ST_MINSYSREADYµÄ×´Ì¬Ê±±ØÐëÌîÉÏ°æ±¾ºÅ,Ö»ÓÃÔÚMCU×îÐ¡ÏµÍ³Æô¶¯ºóÓÉMCU·¢¸øAP£¬
}pkt_sys_statuschange_req_t;

typedef struct
{
    pkt_header_t hd;
    //如果是1表示这是最后一个报文了，否则后面还有需要动态加载请求报文。
    //每次总数量不能大于
    //(MAX_PKT_LENGTH-sizeof(PKT_HEADER)-sizeof(End))/sizeof(uint16_t)
    uint8_t end;
    uint8_t file_count;
    uint16_t    file_list[];
}pkt_sys_dynload_req_t;

typedef struct
{
    pkt_header_t hd;
    uint8_t type;
    uint8_t value;
    uint16_t reserve;
}pkt_log_config_req_t;
typedef struct
{
     pkt_header_t hd;
     uint8_t module;
     uint8_t level;
     uint16_t log_length;
	 uint32_t log_time;
     char    log[];
}pkt_log_report_req_t;

typedef struct
{
    pkt_header_t hd;
    motion_type_t motion_type;
    uint16_t reserve;
}pkt_motion_open_req_t;

typedef struct
{
    pkt_header_t hd;
    motion_type_t motion_type;
    uint16_t reserve;
}pkt_motion_close_req_t;

typedef struct
{
    pkt_header_t hd;
    motion_type_t motion_type;
    uint16_t interval;
}pkt_motion_interval_req_t;

typedef struct
{
    pkt_header_t hd;
    motion_type_t motion_type;
    uint8_t     motion_result;
    int8_t     motion_status;
    uint8_t     data_len;
    int32_t     data[];
}pkt_motion_report_req_t;

typedef struct
{
    pkt_header_t hd;
    motion_type_t motion_type;
    uint16_t motion_attribute;
}pkt_motion_attr_enable_req_t;

typedef struct
{
    pkt_header_t hd;
    motion_type_t motion_type;
    uint16_t motion_attribute;
}pkt_motion_attr_disable_req_t;

typedef struct
{
    pkt_header_t hd;
    int32_t current_now;
}pkt_current_data_req_t;

typedef struct
{
    pkt_header_t hd;
    char calibrate_data[MAX_MAG_CALIBRATE_DATA_LENGTH];
}pkt_mag_calibrate_data_req_t;

#endif
