


#ifndef __HW_ALAN_KERNEL_HWCAM_DEPTHISP_CFG_H__
#define __HW_ALAN_KERNEL_HWCAM_DEPTHISP_CFG_H__

#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/videodev2.h>
#include <media/huawei/camera.h>


typedef enum _tag_hwdepthisp_config_type
{
    HWCAM_DEPTHISP_POWERON,
    HWCAM_DEPTHISP_POWEROFF,
    HWCAM_DEPTHISP_LOADFW,
    HWCAM_DEPTHISP_CMD,
    HWCAM_DEPTHISP_MATCHID,
    //TODO...

} hwdepthisp_config_type_t;

/* used for different firmware type */
enum {
    DEPTHISP_FW_BASIC,
    DEPTHISP_FW_SCENARIO_TAB,
    DEPTHISP_FW_CALIBRATION_OTP,
    DEPTHISP_FW_CALIBRATION_PACK,
};

/* 32-bit cmd mask */
enum
{
	DEPTHISP_CMD_DIR_FLAG_SHIT = 30,		/* [31:30] CMD dirction type */
	DEPTHISP_CMD_RESP_FLAG_SHIT = 28,		/* [   28] CMD response type */
	DEPTHISP_CMD_OUT_LEN_SHIT = 22,		/* [27:22] CMD out len 0~63byte */
	DEPTHISP_CMD_IN_LEN_SHIT = 16,		/* [21:16] CMD in len 0~63byte */
	DEPTHISP_CMD_OPCODE_SHIT = 0,			/* [15: 0] CMD opcode */

	DEPTHISP_CMD_DIR_FLAG_MASK = (0x3U << DEPTHISP_CMD_DIR_FLAG_SHIT),
	DEPTHISP_CMD_RESP_FLAG_MASK = (0x3U << DEPTHISP_CMD_RESP_FLAG_SHIT),
	DEPTHISP_CMD_OUT_LEN_MASK = (0x3fU << DEPTHISP_CMD_OUT_LEN_SHIT),
	DEPTHISP_CMD_IN_LEN_MASK = (0x3fU << DEPTHISP_CMD_IN_LEN_SHIT),
	DEPTHISP_CMD_OPCODE_MASK = (0xffffU << DEPTHISP_CMD_OPCODE_SHIT),
};

/* cmd direction type */
enum
{
	DEPTHISP_SET_CMD	 = 0x1U,
	DEPTHISP_GET_CMD	 = 0x2U,
	DEPTHISP_INOUT_CMD = 0x3U,
};

/* cmd response type */
enum
{
    DEPTHISP_BLOCK_WRITE_CMD = 2U,
	DEPTHISP_BLOCK_RESPONSE_CMD = 1U,
	DEPTHISP_NORMAL_RESPONSE_CMD = 0U,
};

enum {
	DEPTHISP_DUMMY = 1<<0,
	DEPTHISP_AL6045 = 1<<1,
	DEPTHISP_AL6610 = 1<<2,
};

struct ext_block_response_buf {
    union {
        void 	*user_buf_ptr;
        int64_t  _user_buf_ptr;
    };
    uint32_t user_buf_len;
};

typedef struct _tag_hwdepthisp_config_data
{
    uint32_t cfgtype;
    uint32_t cmd;
    int depthisp_type;

    union {
        uint8_t  buf[64];
        uint16_t buf16[32];
    } u;
    struct ext_block_response_buf ext_buf;
}hwdepthisp_config_data_t;


enum
{
	HWDEPTHISP_NAME_SIZE                          =   32,
	HWDEPTHISP_V4L2_EVENT_TYPE                       =   V4L2_EVENT_PRIVATE_START + 0x00080000,

	HWDEPTHISP_HIGH_PRIO_EVENT                       =   0x1500,
	HWDEPTHISP_MIDDLE_PRIO_EVENT                     =   0x2000,
	HWDEPTHISP_LOW_PRIO_EVENT                        =   0x3000,
};

typedef struct _tag_hwdepthisp_info
{
    char                                        name[HWDEPTHISP_NAME_SIZE];
} hwdepthisp_info_t;

typedef enum _tag_hwdepthisp_event_kind
{
    HWDEPTHISP_INFO_CMD_FINISH,
    HWDEPTHISP_INFO_ERROR,
    HWDEPTHISP_INFO_DUMP,
    HWDEPTHISP_INFO_OIS_DONE,
} hwdepthisp_event_kind_t;

typedef struct _tag_hwdepthisp_event
{
    hwdepthisp_event_kind_t                          kind;
    union // can ONLY place 10 int fields here.
    {
        struct
        {
            uint32_t                            cmd;
            uint32_t                            result;
        }                                       cmd_finish;
        struct
        {
            uint32_t                            id;
        }                                       error;
        struct
        {
            uint32_t                            type;
        }                                       dump;
    }data;
}hwdepthisp_event_t;

#define HWDEPTHISP_IOCTL_GET_INFO                 _IOR('D', BASE_VIDIOC_PRIVATE + 1, hwdepthisp_info_t)
#define HWDEPTHISP_IOCTL_CONFIG               	_IOWR('I', BASE_VIDIOC_PRIVATE + 2, hwdepthisp_config_data_t)

#endif // __HW_ALAN_KERNEL_HWCAM_DEPTHISP_CFG_H__

