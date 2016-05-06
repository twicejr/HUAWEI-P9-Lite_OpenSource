


#ifndef __HW_ALAN_KERNEL_HWCAM_ISP_CFG_H__
#define __HW_ALAN_KERNEL_HWCAM_ISP_CFG_H__

#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/videodev2.h>
#include <media/huawei/camera.h>
#include <linux/compat.h>

enum 
{
    HWISP_NAME_SIZE                             =   32, 

    HWISP_V4L2_EVENT_TYPE                       =   V4L2_EVENT_PRIVATE_START + 0x00080000,

    HWISP_HIGH_PRIO_EVENT                       =   0x1500, 
    HWISP_MIDDLE_PRIO_EVENT                     =   0x2000, 
    HWISP_LOW_PRIO_EVENT                        =   0x3000, 
}; 

typedef enum _tag_hwisp_event_kind
{
    HWISP_SOF,
    HWISP_EOF,
    HWISP_READY,
} hwisp_event_kind_t;

typedef struct _tag_hwisp_event 
{
    hwisp_event_kind_t                          kind; 
    union // can ONLY place 10 int fields here.  
    {
        struct 
        {
            uint32_t                            pipeline; 
        }                                       sof; 
        struct 
        {
            uint32_t                            pipeline; 
        }                                       eof; 
        struct 
        {
            uint32_t                            cmd;
            uint32_t                            result; 
        }                                       ready; 
    }data; 
} hwisp_event_t;

typedef struct _tag_hwisp_info
{
    char                                        name[HWISP_NAME_SIZE]; 
} hwisp_info_t;

typedef enum _tag_hwisp_stream_kind
{
    HWISP_STREAM_KIND_IMAGE                     =   0,
    HWISP_STREAM_KIND_STATS                     =   1,
} hwisp_stream_kind_t; 

typedef enum _tag_hwisp_stream_direction_kind
{
    HWISP_STREAM_DIRECTION_KIND_IN              =   0,
    HWISP_STREAM_DIRECTION_KIND_OUT             =   1,
} hwisp_stream_direction_kind_t; 

typedef enum _tag_hwisp_stream_constants
{
    HWISP_STREAM_EVENT                          =   0x1000,
} hwisp_stream_constants_t; 

typedef enum _tag_hwisp_stream_event_kind
{
    HWISP_STREAM_EVENT_MIN                      =   HWISP_STREAM_EVENT,
    HWISP_STREAM_EVENT_BUF_DONE, 
} hwisp_stream_event_kind_t; 

typedef struct _tag_hwisp_stream_event
{
    hwisp_stream_event_kind_t                   kind; 
} hwisp_stream_event_t; 

typedef struct _tag_hwisp_stream_event_buf_done
{
    hwisp_stream_event_t                        event; 
    int                                         frame_id; 
} hwisp_stream_event_buf_done_t; 

typedef enum _tag_ovisp23_port_stream_format
{
    PIX_FMT_NV21        = 0,
    PIX_FMT_NV12,
    PIX_FMT_RAW10,         
    PIX_FMT_YUYV ,         
    PIX_FMT_VC0 ,           
    PIX_FMT_MAX ,            
} ovisp23_port_stream_format_t;

typedef struct _tag_ovisp23_port_info
{
    uint32_t                                    id;
    ovisp23_port_stream_format_t                pix_format;
    uint8_t                                      use_phy_memory;// 1: use phy memory 0: use virtual memory
}ovisp23_port_info_t;
    
typedef struct _tag_hwisp_stream_info
{
    int                                         buf_queue_size; 
    uint32_t                              		stream_type;
    uint32_t                               		stream_direction;
    int                                         fd_ispstream; 
    //ovisp23_port_info_t                       port;
    uint32_t                                    portid;
    ovisp23_port_stream_format_t                pix_format;
    uint8_t                                     use_phy_memory;// 1: use phy memory 0: use virtual memory defined by user
} hwisp_stream_info_t;

struct isp_cfg_reg{	
	uint32_t                                    reg;
	uint32_t                                    val;
	uint32_t                                    val_bits;	
	uint32_t                                    mask;	
};

/* add for 32+64 */
struct isp_cfg_reg_array{
	uint32_t                                    length;
	union {
		struct isp_cfg_reg*                     reg_array;
		int64_t                                 _reg_array;
	};
};

struct ion_handle;

#if 1
typedef struct _tag_hwisp_stream_buf_info
{
    union {
        void*                                   user_buffer_handle; 
        int64_t                                 _user_buffer_handle;
    };

    uint32_t                                    y_addr_phy;
    uint32_t                                    u_addr_phy;
    uint32_t                                    v_addr_phy;

    uint32_t                                    y_addr_iommu;
    uint32_t                                    u_addr_iommu;
    uint32_t                                    v_addr_iommu;

    int                                         ion_fd;
    union {
        struct ion_handle                       *ion_vc_hdl;
        int64_t                                 _ion_vc_hdl;
    };
    union {
        void                                    *ion_vaddr;
        int64_t                                 _ion_vaddr;
    };

    union {
        struct timeval                          timestamp;
        int64_t                                 _timestamp[2];
    };

    ovisp23_port_info_t                         port;

} hwisp_stream_buf_info_t;

#else
typedef struct _tag_hwisp_stream_buf_info
{
    void*                                       user_buffer_handle; 

    unsigned long                               y_addr_phy;
    unsigned long                               u_addr_phy;
    unsigned long                               v_addr_phy;

    unsigned long                               y_addr_iommu;
    unsigned long                               u_addr_iommu;
    unsigned long                               v_addr_iommu;

    int											ion_fd;
	struct ion_handle 							*ion_vc_hdl;
	void										*ion_vaddr;

    struct timeval					            timestamp;
    ovisp23_port_info_t                         port;

} hwisp_stream_buf_info_t;
#endif

typedef struct {
	uint32_t exposure;
	uint16_t gain;
	uint16_t mean_y;
	uint16_t raw_stretch_low_level;
	uint16_t raw_stretch_gain;
	uint16_t b_gain;
	uint16_t g_gain;
	uint16_t r_gain;
	uint16_t b_offset;
	uint16_t g_offset;
	uint16_t r_offset;
	uint16_t lens_online_ba;
	uint16_t lens_online_br;
	uint16_t lens_profile;
} raw_buffer_info_t;

struct reprocess_param_list {
	hwisp_stream_buf_info_t input_buf_info;
	hwisp_stream_buf_info_t output_buf_info;
	uint8_t reprocess_pipeline;
	uint8_t input_pipeline;
	uint32_t input_fmt;
	uint32_t output_fmt;
	uint32_t input_width;
	uint32_t input_height;
	uint32_t output_width;
	uint32_t output_height;
	uint16_t zoom_ratio;
	raw_buffer_info_t raw_buf_info;
};

struct isp_cfg_data {
	int                                         cfgtype;
	int                                         mode;
	int                                         data;
	union {
		struct isp_cfg_reg                      reg;
		struct isp_cfg_reg_array                reg_settings;
		struct reprocess_param_list             reprocess_params;
	}reg_s;
};

enum isp_config_type
{
	CONFIG_POWER_ON                             =   0,
	CONFIG_POWER_OFF,
	CONFIG_WRITE_REG,
	CONFIG_READ_REG,
	CONFIG_WRITE_REG_SETTINGS,
	CONFIG_READ_REG_SETTINGS,
	CONFIG_BUFFER_TO_ISP,
	CONFIG_REPROCESS_CMD,
	CONFIG_MAX_INDEX
};

typedef enum _tag_hwisp_stream_buf_state_kind
{
    HWISP_STREAM_BUF_STATE_KIND_ERROR           =   -1, 
    HWISP_STREAM_BUF_STATE_KIND_DONE, 
} hwisp_stream_buf_state_kind_t; 

/* meta data struct define */
struct meta_common {
	uint32_t frame_index;
	uint16_t frame_rate;
	uint16_t scene_mode;
	uint8_t scene_change_flg;
	uint8_t digital_zoom;
	uint8_t filcker_detect_reslut;
	uint8_t module_id;
	uint16_t frame_type;
};

struct meta_ae {
	int16_t result_BV;
	uint32_t expo_time;
	uint16_t expo_line;
	uint16_t iso;
	uint16_t gain;
	uint16_t avg_raw_lum;
	uint16_t target;
	int16_t manual_ev_comp;
	uint8_t mode;
	uint8_t flash_turnon_flag;
	uint8_t converge_state;
};

struct meta_awb {
	uint8_t converge_state;
	uint8_t mode;
	uint16_t r_gain;
	uint16_t g_gain;
	uint16_t b_gain;
	int light_source;
};

struct meta_af {
	uint8_t converge_state;
	uint8_t assist_flash_turnon_flag;
	uint8_t code;
	uint8_t mode;
	int16_t final_peak_step;
	uint16_t bar_level;
};

struct meta_fe {
	uint8_t preflash1_state;
	uint8_t ae_image_cal_ready;
	uint8_t preflash1_cal_ready;
	uint8_t preflash2_cal_ready;
	uint32_t mainflash_led_enerage;
};

struct meta_extend {
	uint32_t ext_frame_index;
	uint16_t ext_frame_rate;
	uint32_t ext_expo_time;
	uint16_t ext_expo_line;
	uint16_t ext_iso;
	uint16_t ext_gain;
	uint16_t ext_r_gain_preview;
	uint16_t ext_g_gain_preview;
	uint16_t ext_b_gain_preview;
	uint16_t ext_r_gain_capture;
	uint16_t ext_g_gain_capture;
	uint16_t ext_b_gain_capture;
	uint8_t  ext_af_converge_state;
	uint8_t  ext_af_code;
	uint8_t  ext_af_mode;
	int16_t ext_final_peak_step;
	uint16_t ext_af_vcm_step;
	uint16_t ext_af_bar_level;
};

typedef struct _meta_data_t {
	struct meta_common common_info;
	struct meta_ae ae_info;
	struct meta_awb awb_info;
	struct meta_af af_info;
	struct meta_fe fe_info;
	uint8_t reserved[32];
	struct meta_extend ext_info;
	union {
		uint8_t sw_debug_info[128];
		raw_buffer_info_t raw_info[2];
	} u;
	uint8_t iq_debug_info[1788];
	uint16_t pdaf_info[772];
}meta_data_t;


#define HWISP_IOCTL_GET_INFO                    _IOR('A', BASE_VIDIOC_PRIVATE + 0x01, hwisp_info_t)
#define HWISP_IOCTL_CREATE_ISP_STREAM           _IOWR('A', BASE_VIDIOC_PRIVATE + 0x02, hwisp_stream_info_t)

#define HWISP_STREAM_IOCTL_ENQUEUE_BUF          _IOW('A', BASE_VIDIOC_PRIVATE + 0x01, hwisp_stream_buf_info_t)
#define HWISP_STREAM_IOCTL_DEQUEUE_BUF          _IOR('A', BASE_VIDIOC_PRIVATE + 0x02, hwisp_stream_buf_info_t)
#define HWISP_STREAM_IOCTL_START                _IO('A', BASE_VIDIOC_PRIVATE + 0x03)
#define HWISP_STREAM_IOCTL_STOP                 _IO('A', BASE_VIDIOC_PRIVATE + 0x04)
#define HWISP_IOCTL_CFG_ISP          		    _IOWR('A', BASE_VIDIOC_PRIVATE + 0x05, struct isp_cfg_data)
#define HWISP_IOCTL_FIX_DDR                     _IO('A', BASE_VIDIOC_PRIVATE + 0x06)

typedef struct
{
	uint8_t low;
	uint8_t high;
}ae_target_meta_t;


typedef struct ae_coff{
    uint32_t exposure_max;
    uint32_t exposure_min;
    uint32_t gain_max;
    uint32_t gain_min;
    uint32_t luma_target_high;
    uint32_t luma_target_low;
    uint32_t exposure;
    uint32_t exposure_time;
    uint32_t gain;
    uint32_t iso;
    uint32_t aec_stable;
    uint32_t fps;
    uint32_t lum;
}ae_coff_meta_t;

typedef struct capture_ae_coeff {
    uint32_t exposure[3];
    uint32_t exposure_time[3];
    uint32_t gain[3];
    uint32_t iso[3];
    uint32_t ratio[3];
}capture_ae_coeff_t;

typedef struct extra_coff {
    uint32_t mean_y;
    uint32_t motion_x;
    uint32_t motion_y;
    uint32_t focal_length;
    uint32_t af_window_change;
    uint32_t g_gain;
    uint32_t b_gain;
    uint32_t r_gain;
    uint32_t awb_r_gain;
    uint32_t awb_gr_gain;
    uint32_t awb_gb_gain;
    uint32_t awb_b_gain;
}extra_coff_meta_t;

typedef struct
{
    ae_target_meta_t ae_target;
    //TODO...
    ae_coff_meta_t ae_coff;
    extra_coff_meta_t extra_coff;
    uint16_t hw3a_lum_matrix[16][16];
    uint8_t hw3a_hist_matrix[256][8];
    uint32_t stat_left;
    uint32_t stat_top;
    uint32_t stat_width;
    uint32_t stat_height;
    uint32_t vts;
    uint8_t  hwaAeEnable;
    raw_buffer_info_t raw_info;
    uint8_t minispEnable;
    int32_t vcmcode;
}ovisp_meta_t;

#endif // __HW_ALAN_KERNEL_HWCAM_ISP_CFG_H__

