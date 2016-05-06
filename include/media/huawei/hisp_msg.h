


#ifndef HISP_MSG_H_INCLUDED
#define HISP_MSG_H_INCLUDED


#define MAX_INPUT_STREAM_NR (2)
#define MAX_STREAM_NR       (10)
#define NAME_LEN            (32)
#define PARAS_LEN           (400)
#define EVENT_PARAMS_LEN    (64)
#define TIME_LEN            (32)

/* based on msg len is 464 */
#define MAX_SET_ISP_NR  1//50//53//59
#define MAX_GET_ISP_NR  1//100//108//119
#define MAX_SET_I2C_NR  1//35//35//39
#define MAX_GET_I2C_NR  1//50//53//59

typedef enum
{
    PIXEL_FMT_RAW10,
    PIXEL_FMT_RAW12,
    PIXEL_FMT_RAW14,
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
    /* Request items. */
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
    COMMAND_INV_TLB,
    COMMAND_QUERY_OIS_UPDATE,
    COMMAND_OIS_UPDATE,
    COMMAND_QUERY_LASER,
    COMMAND_ACQUIRE_LASER,
    COMMAND_RELEASE_LASER,
    COMMAND_ACQUIRE_DEPTHISP,
    COMMAND_RELEASE_DEPTHISP,

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
    INV_TLB_RESPONSE,
    QUERY_OIS_UPDATE_RESPONSE,
    OIS_UPDATE_RESPONSE,
    QUERY_LASER_RESPONSE,
    ACQUIRE_LASER_RESPONSE,
    RELEASE_LASER_RESPONSE,
    ACQUIRE_DEPTHISP_RESPONSE,
    RELEASE_DEPTHISP_RESPONSE,

    /* Event items sent to AP. */
    MSG_EVENT_SENT           = 0x3000,
} api_id_e;

typedef enum _ucfg_ext_e
{
    NO_USE               = 0 << 0,
    H_VIDEO_720P_120     = 1 << 1,
    H_VIDEO_1080P_60     = 1 << 2,
    MIRROR_MODE          = 1 << 3,
    LONG_EXPOSURE_MODE   = 1 << 4,
    HDR_MOVIE            = 1 << 5,
    DARK_RAIDER_MODE     = 1 << 6,
    H_VIDEO_720P_60      = 1 << 7,
    H_VIDEO_VGA_120      = 1 << 8,
    TUNING_PRE_MODE      = 1 << 9,
    RESERVED             = 1 << 10,
} ucfg_ext_e;

typedef enum _ucfg_scene_e
{
    CAMERA_SCENE_NORMAL = 0,
    CAMERA_SCENE_VIDEO,
}ucfg_scene_e;

typedef enum
{
    PRIMARY_CAMERA = 0,
    FRONT_CAMERA,
    SECONDARY_CAMERA,
} camera_id_t;

typedef struct _msg_req_query_capability_t
{
    unsigned int cam_id;
    unsigned int csi_index;
    unsigned int i2c_index;
    char         product_name[NAME_LEN];
    char         sensor_name[NAME_LEN];
    unsigned int input_settings_buffer;
} msg_req_query_capability_t;

typedef struct _msg_ack_query_capability_t
{
    unsigned int cam_id;
    char         product_name[NAME_LEN];
    char         sensor_name[NAME_LEN];
    unsigned int output_metadata_buffer;
    int          status;
} msg_ack_query_capability_t;

typedef struct _msg_req_query_laser_t
{
    unsigned int i2c_index;
    char         product_name[NAME_LEN];
    char         name[NAME_LEN];
} msg_req_query_laser_t;

typedef struct _laser_spad_t
{
    unsigned int    ref_spad_count;
    unsigned char   is_aperture_spads;
}laser_spad_t;

typedef struct _msg_ack_query_laser_t
{
    char           name[NAME_LEN];
    unsigned char  revision;
    int            status;
    laser_spad_t   spad;
} msg_ack_query_laser_t;

typedef struct _msg_req_acquire_camera_t
{
    unsigned int cam_id;
    unsigned int csi_index;
    unsigned int i2c_index;
    char         sensor_name[NAME_LEN];
    char         product_name[NAME_LEN];
    unsigned int input_otp_buffer;
    unsigned int buffer_size;
} msg_req_acquire_camera_t;

typedef struct _msg_ack_acquire_camera_t
{
    unsigned int cam_id;
    char         sensor_name[NAME_LEN];
} msg_ack_acquire_camera_t;

typedef struct _laser_fov_t
{
    float          x;
    float          y;
    float          width;
    float          height;
    float          angle;
}laser_fov_t;

typedef struct _msg_req_acquire_laser_t
{
    unsigned int    i2c_index;
    char            product_name[NAME_LEN];
    char            name[NAME_LEN];
    int             offset;
    int             xtalk;
    laser_fov_t     fov_info;
    laser_spad_t    spad;
} msg_req_acquire_laser_t;

typedef struct _msg_ack_acquire_laser_t
{
    char           name[NAME_LEN];
    unsigned char  revision;
    int            status;
} msg_ack_acquire_laser_t;

typedef struct _msg_req_release_camera_t
{
    unsigned int cam_id;
} msg_req_release_camera_t;

typedef struct _msg_ack_release_camera_t
{
    unsigned int cam_id;
} msg_ack_release_camera_t;

typedef struct _msg_req_release_laser_t
{
    unsigned int i2c_index;
} msg_req_release_laser_t;

typedef struct _msg_ack_release_laser_t
{
    unsigned int i2c_index;
} msg_ack_release_laser_t;

typedef struct _msg_req_acquire_depthisp_t
{
    unsigned int  i2c_index;
    unsigned char chip_type;
    char          product_name[NAME_LEN];
    char          name[NAME_LEN];
} msg_req_acquire_depthisp_t;

typedef struct _msg_ack_acquire_depthisp_t
{
    char         name[NAME_LEN];
    int          status;
} msg_ack_acquire_depthisp_t;

typedef struct _msg_req_release_depthisp_t
{
    unsigned int i2c_index;
} msg_req_release_depthisp_t;

typedef struct _msg_ack_release_depthisp_t
{
    unsigned int i2c_index;
} msg_ack_release_depthisp_t;

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
    unsigned int    cam_id;
    unsigned int    extension;
    unsigned int    stream_nr;
    unsigned int    scene;
    stream_config_t stream_cfg[MAX_STREAM_NR];
    char            time[TIME_LEN];
} msg_req_usecase_config_t;

typedef struct _msg_ack_usecase_config_t
{
    unsigned int cam_id;
    int          status;
    unsigned int sensor_width;
    unsigned int sensor_height;
} msg_ack_usecase_config_t;
typedef struct _msg_req_get_otp_t
{
    unsigned int cam_id;
    char         sensor_name[NAME_LEN];
    unsigned int input_otp_buffer;
    unsigned int buffer_size;
} msg_req_get_otp_t;

typedef struct _msg_ack_get_otp_t
{
    unsigned int cam_id;
    char         sensor_name[NAME_LEN];
    unsigned int output_otp_buffer;
    unsigned int buffer_size;
    int          status;
} msg_ack_get_otp_t;

typedef struct _stream_info_t
{
    unsigned int buffer;
    unsigned int width;
    unsigned int height;
    unsigned int stride;
    unsigned int format;
    unsigned int valid;
} stream_info_t;

typedef struct _msg_req_request_t
{
    unsigned int cam_id;
    unsigned int num_targets;
    unsigned int target_map;
    unsigned int frame_number;
    unsigned int buf[MAX_STREAM_NR];
    unsigned int input_setting_buffer;
    unsigned int output_metadata_buffer;
} msg_req_request_t;

typedef struct _msg_ack_request_t
{
    unsigned int  cam_id;
    unsigned int  num_targets;
    unsigned int  target_map;
    unsigned int  frame_number;
    stream_info_t stream_info[MAX_STREAM_NR];
    unsigned int  input_setting_buffer;
    unsigned int  output_metadata_buffer;
    unsigned int  timestampL;
    unsigned int  timestampH;
    unsigned int  status;
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

typedef struct _msg_req_inv_tlb_t
{
    int flag;
} msg_req_inv_tlb_t;

typedef struct _msg_ack_inv_tlb_t
{
    int status;
} msg_ack_inv_tlb_t;

typedef struct _msg_req_query_ois_update_t
{
    unsigned int cam_id;
    char sensor_name[32];
} msg_req_query_ois_update_t;

typedef struct _msg_ack_query_ois_update_t
{
    unsigned int cam_id;
    int status;
} msg_ack_query_ois_update_t;

typedef struct _msg_req_ois_update_t
{
    unsigned int cam_id;
    char sensor_name[32];
} msg_req_ois_update_t;

typedef struct _msg_ack_ois_update_t
{
    unsigned int cam_id;
    int status;
} msg_ack_ois_update_t;

typedef struct _msg_ack_jpeg_encode_t
{
    unsigned int output_buffer;
    unsigned int filesize;
    int          status;
} msg_ack_jpeg_encode_t;

typedef struct _msg_req_map_buffer_t
{
    unsigned int cam_id;
    unsigned int mem_pool_buffer;
    unsigned int buffer_size;
    unsigned int t2_enable;
    unsigned int dis_enable;
} msg_req_map_buffer_t;

typedef struct _msg_ack_map_buffer_t
{
    unsigned int cam_id;
    int          status;
} msg_ack_map_buffer_t;

typedef struct _msg_req_unmap_buffer_t
{
    unsigned int cam_id;
    unsigned int buffer;
} msg_req_unmap_buffer_t;

typedef struct _msg_ack_unmap_buffer_t
{
    unsigned int cam_id;
    int          status;
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
    int          status;
} msg_ack_cal_data_t;

typedef struct _isp_reg_info_t
{
    unsigned int register_address;
    unsigned int register_value;
} isp_reg_info_t;

typedef struct _msg_req_set_isp_regs_t
{
    unsigned int   register_type;
    unsigned int   register_count;
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
    unsigned int register_address;
    unsigned int register_value;
    unsigned char length;                   /**< value length */
} i2c_reg_set_info_t;

typedef struct _msg_req_set_i2c_regs_t
{
    unsigned int       register_type;
    unsigned int       slave_address;
    unsigned int       register_count;
    i2c_reg_set_info_t reg_info[MAX_SET_I2C_NR];
} msg_req_set_i2c_regs_t;

typedef struct _msg_ack_set_i2c_regs_t
{
    int status;
} msg_ack_set_i2c_regs_t;

typedef struct _i2c_reg_get_info_t
{
    unsigned int  register_address;
    unsigned char length;                   /**< request getting the len of the register value */
} i2c_reg_get_info_t;

typedef struct _msg_req_get_i2c_regs_t
{
    unsigned int       register_type;
    unsigned int       slave_address;
    unsigned int       register_count;
    i2c_reg_get_info_t reg_info[MAX_GET_I2C_NR];
} msg_req_get_i2c_regs_t;

typedef struct _msg_ack_get_i2c_regs_t
{
    int          status;
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
    SUBCMD_SET_M_DF_FLAG,
    SUBCMD_SET_DF_TUNING,
    SUBCMD_SET_COLOR_BAR,
    SUBCMD_ENABLE_TNR,
    SUBCMD_ENABLE_DIS,
    SUBCMD_ENABLE_FD,
    SUBCMD_SET_FACE,
    SUBCMD_AE_ANTIBANDING_MODE,
    SUBCMD_AE_EXPOSURE_COMPENSATION,
    SUBCMD_AE_LOCK,
    SUBCMD_AE_MODE,
    SUBCMD_AE_REGIONS,
    SUBCMD_AE_TARGET_FPS_RANGE,
    SUBCMD_AE_PRECAPTURE_TRIGGER,
    SUBCMD_AF_MODE,
    SUBCMD_AF_REGIONS,
    SUBCMD_AF_TRIGGER,
    SUBCMD_FLASH_MODE,
    SUBCMD_AWB_LOCK,
    SUBCMD_AWB_MODE,
    SUBCMD_AWB_REGIONS,
    SCALER_CROP_REGION,
    SUBCMD_START_CAPTURE,
    SUBCMD_STOP_CAPTURE,
    SUBCMD_SET_DEBUG_OPEN,
    SUBCMD_SET_FLASH_RATIO,
    SUBCMD_SET_MANUAL_FOCUS_MODE,
    SUBCMD_SET_VCM_CODE,
    SUBCMD_SET_BANDING_MSG,
    SUBCMD_SET_EXPO_TIME,
    SUBCMD_SET_ISO,
    SUBCMD_SET_ADGAIN,
    SUBCMD_SET_MANUAL_AWB,
    SUBCMD_SET_SCENE_MODE,
    SUBCMD_SET_OVER_EXPOSURE,
    SUBCMD_SET_DEBUG_SHADING,
    SUBCMD_RESUME_3A,
    SUBCMD_SET_CAPTURE_SHARPNESS,
    SUBCMD_SET_CAPTURE_RAWNF,
    SUBCMD_SET_CAPTURE_YUVNF,
    SUBCMD_SET_CAPTURE_GCD,
    SUBCMD_SET_SALIENCY_RESULT,
    SUBCMD_SET_PANORAMA_MODE,
    SUBCMD_SET_PANORAMA_LOCK,
    SUBCMD_SET_FAST_SNAPSHOT,
    SUBCMD_SET_SATURATION,
    SUBCMD_SET_CONTRAST,
    SUBCMD_SET_BRIGHTNESS,
    SUBCMD_SET_GSENSOR_INFO,
    SUBCMD_SET_7CM_FOCUS_MODE,
    SUBCMD_SET_7CM_FOCUS_REGIONS,
    SUBCMD_SET_BURST_COUNT,
    SUBCMD_SET_TARGET_TRACKING,
    SUBCMD_SET_OIS_MODE,
    SUBCMD_ENABLE_FBCD,
    SUBCMD_TRY_AE,
    SUBCMD_SET_CAPTURE_AE,
    SUBCMD_SET_TARGET_LUMINANCE,
    SUBCMD_GET_CAPTURE_VALID_INFO,
    SUBCMD_CAMERA_MODE,
    SUBCMD_SET_OTP_CALIBRATION,
    SUBCMD_SET_MOTIONSENSOR_INFO,
    SUBCMD_PDAF_MMI_TEST_ENABLE,
    SUBCMD_SET_PDAF_MMI_PARAM,
    SUBCMD_SET_EQUIP_MMI_MODE,
    SUBCMD_SET_FLASH_MMI_MODE,
    SUBCMD_SET_MMI_TEST_GAMMA,
    SUBCMD_SET_PROFESSION_CAMERA,
    SUBCMD_SET_METERING_MODE,
    SUBCMD_SET_WB_VALUE,
    SUBCMD_LPD_ENABLE,
    SUBCMD_SET_AE_GAIN,
    SUBCMD_AWB_ILLUMINANT,
    SUBCMD_AWB_DAMPING_PARAM,
    SUBCMD_AWB_CURRENT_WP,
    SUBCMD_GAMMA_LOCK,
    SUBCMD_GAMMA_MODE,
    SUBCMD_GAMMA_CURVE,
    SUBCMD_GAMMA_DAMPING_PARAM,
    SUBCMD_LSC_ENABLE,
    SUBCMD_DPCC_ENABLE,
    SUBCMD_YUVNF_ENABLE,
    SUBCMD_SHARPNESS_ENABLE,
    SUBCMD_RAWNF_ENABLE,
    SUBCMD_DRC_ENABLE,
    SUBCMD_DRC_MODE,
    SUBCMD_DRC_DAMPING_PARAM,
    SUBCMD_CC_ENABLE,
    SUBCMD_CC_MODE,
    SUBCMD_CC_PARAM,
    SUBCMD_CC_MATRIX,
    SUBCMD_SMART_AE_SET_EXPO_COMPENSATION,
    SUBCMD_SET_OIS_MMI_MODE,
    SUBCMD_RESUME_VCM_CODE,
    SUBCMD_PROF_FOCUS_ASSIST_MODE,
    SUBCMD_YUV_CONTRAST_RESULT,
    SUBCMD_SET_FACE_INFO,
    SUBCMD_LASER_CONTROL,
    SUBCMD_USECASE_INITIAL,
    SUBCMD_SET_DC_MMI_ENABLE,
    SUBCMD_SET_AF_MESSAGE,
    SUBCMD_CAMERA_FIRMWARE_PROPERTY,
    SUBCMD_SET_DUAL_CAM_SHELTERED,
    SUBCMD_DEPTH_INFO,
    SUBCMD_SET_MMI_7CM_PARAM,
    SUBCMD_AE_YUV_INFO,
    SUBCMD_SET_FILL_RAW,
    SUBCMD_SET_ANDROID_ISO,
    SUBCMD_SET_ANDROID_EXPO_TIME,
    SUBCMD_SET_FOCUS_DISTANCE,
    SUBCMD_SET_TONEMAP_MODE,
    SUBCMD_SET_TONEMAP_CURVE,
    SUBCMD_SET_APERTURE_MODE,
    SUBCMD_SET_STD_RAW,
    SUBCMD_SET_CAPFLASH_ON,
    SUBCMD_SET_AFC_DATA,
    SUBCMD_SET_CC_MODE,
    SUBCMD_SET_CC_TRANSFORM,
    SUBCMD_SET_CC_GAINS,
    SUBCMD_SET_CONTROL_MODE,
    SUBCMD_SET_AF_DIRECT_TRANS_BASE,
    SUBCMD_SET_CURVE_MODE,
    SUBCMD_SET_RGB2YUV_MODE,
    SUBCMD_SET_RGB2YUV_PARAM,
    SUBCMD_SET_AF_OTP_CALIB_DATA,
    SUBCMD_SET_SATURATION_COMPENSATION,
} extendset_info_e;

typedef enum
{
    SUBCMD_EG_LLT,
    SUBCMD_EG_ST,
    SUBCMD_GET_M_DF_FLAG,
    SUBCMD_GET_DF_TUNING,
} extendget_info_e;

typedef enum
{
    EVENT_ERR_CODE = 0,
    EVENT_SHUTTER,
    EVENT_INTERRUPT,
    EVENT_FLASH,
    EVENT_AF,
    EVENT_AF_MMI_DEBUG,
    EVENT_AF_DIRECT_TRANS_BASE,
    EVENT_AF_OTP_CALIB_DATA,
} event_info_e;

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
} msg_subreq_eg_llt_t;

typedef struct _msg_subreq_eg_st_t
{
} msg_subreq_eg_st_t;

typedef struct _msg_req_extend_set_t
{
    unsigned int cam_id;
    unsigned int extend_cmd;
    char         paras[PARAS_LEN];
} msg_req_extend_set_t;

typedef struct _msg_ack_extend_set_t
{
    unsigned int cam_id;
    unsigned int extend_cmd;
    int          status;
    char         ack_info[64];
} msg_ack_extend_set_t;

/* first expo and gain ack AP to select picture */
typedef struct capture_ack_t
{
    unsigned int flow;//camera_flow_e
    unsigned int expo[2];
    unsigned int gain[2];
} capture_ack_t;

typedef struct _msg_req_extend_get_t
{
    unsigned int cam_id;
    unsigned int extend_cmd;
    char         paras[PARAS_LEN];
} msg_req_extend_get_t;

typedef struct _msg_ack_extend_get_t
{
    unsigned int cam_id;
    unsigned int extend_cmd;
    char         paras[PARAS_LEN];
    int          status;
} msg_ack_extend_get_t;

typedef struct _msg_event_sent_t
{
    unsigned int cam_id;
    event_info_e event_id;
    unsigned int frame_number;
    unsigned int stream_id;
    unsigned int timestamp;
    char         event_params[EVENT_PARAMS_LEN];
} msg_event_sent_t;

struct msg_base;

typedef void (*msg_looper_handler)(struct msg_base*, void*);

struct list_head2
{
    unsigned int next, prev;
};

typedef struct msg_base
{
    struct list_head2 link;
    int handler;
    unsigned int user;
}msg_base_t;

typedef struct _isp_msg_t
{
    unsigned int message_size;
    unsigned int api_name;
    unsigned int message_id;
    unsigned int message_hash;
    union
    {
        /* camera to firmware. */
        msg_req_query_capability_t  req_query_capability;
        msg_req_acquire_camera_t    req_acquire_camera;
        msg_req_release_camera_t    req_release_camera;
        msg_req_usecase_config_t    req_usecase_config;
        msg_req_get_otp_t           req_get_otp;
        msg_req_request_t           req_request;
        msg_req_map_buffer_t        req_map_buffer;
        msg_req_unmap_buffer_t      req_unmap_buffer;
        msg_req_cal_data_t          req_cal_data;
        msg_req_set_isp_regs_t      req_set_isp_regs;
        msg_req_get_isp_regs_t      req_get_isp_regs;
        msg_req_set_i2c_regs_t      req_set_i2c_regs;
        msg_req_get_i2c_regs_t      req_get_i2c_regs;
        msg_req_test_case_interface_t   req_test_case_interface;
        msg_req_flush_t             req_flush;
        msg_req_extend_set_t        req_extend_set;
        msg_req_extend_get_t        req_extend_get;
        msg_req_jpeg_encode_t       req_jpeg_encode;
        msg_req_inv_tlb_t           req_inv_tlb;
        msg_req_query_ois_update_t      req_query_ois_update;
        msg_req_ois_update_t            req_ois_update;
        msg_req_query_laser_t       req_query_laser;
        msg_req_acquire_laser_t     req_acquire_laser;
        msg_req_release_laser_t     req_release_laser;
        msg_req_acquire_depthisp_t  req_acquire_depthisp;
        msg_req_release_depthisp_t  req_release_depthisp;

        /* firmware to camera. */
        msg_ack_query_capability_t  ack_query_capability;
        msg_ack_acquire_camera_t    ack_require_camera;
        msg_ack_release_camera_t    ack_release_camera;
        msg_ack_usecase_config_t    ack_usecase_config;
        msg_ack_get_otp_t           ack_get_otp;
        msg_ack_request_t           ack_request;
        msg_ack_map_buffer_t        ack_map_buffer;
        msg_ack_unmap_buffer_t      ack_unmap_buffer;
        msg_ack_cal_data_t          ack_cal_data;
        msg_ack_set_isp_regs_t      ack_set_isp_regs;
        msg_ack_get_isp_regs_t      ack_get_isp_regs;
        msg_ack_set_i2c_regs_t      ack_set_i2c_regs;
        msg_ack_get_i2c_regs_t      ack_get_i2c_regs;
        msg_ack_test_case_interface_t   ack_test_case_interface;
        msg_ack_flush_t             ack_flush;
        msg_ack_extend_set_t        ack_extend_set;
        msg_ack_extend_get_t        ack_extend_get;
        msg_ack_jpeg_encode_t       ack_jpeg_encode;
        msg_ack_inv_tlb_t           ack_inv_tlb;
        msg_ack_query_ois_update_t      ack_query_ois_update;
        msg_ack_ois_update_t            ack_ois_update;
        msg_ack_query_laser_t       ack_query_laser;
        msg_ack_acquire_laser_t     ack_require_laser;
        msg_ack_release_laser_t     ack_release_laser;
        msg_ack_acquire_depthisp_t  ack_require_depthisp;
        msg_ack_release_depthisp_t  ack_release_depthisp;

        /* Event items sent to AP. */
        msg_event_sent_t            event_sent;
    }u;
    msg_base_t base;
    short token;
    unsigned int ept;
} hisp_msg_t;


#endif /* HISP_MSG_H_INCLUDED */
