


#ifndef __HW_ALAN_KERNEL_HWCAM_LASER_CFG_H__
#define __HW_ALAN_KERNEL_HWCAM_LASER_CFG_H__

#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/videodev2.h>
#include <media/huawei/camera.h>


typedef enum _tag_hwlaser_config_type
{
    HWCAM_LASER_POWERON,
    HWCAM_LASER_POWEROFF,
    HWCAM_LASER_POWERON_EXT,
    HWCAM_LASER_POWEROFF_EXT,
    HWCAM_LASER_LOADFW,
    HWCAM_LASER_CMD,
    HWCAM_LASER_MATCHID,
    HWCAM_LASER_SET_FLAG,

} hwlaser_config_type_t;

/* 32-bit cmd mask */
enum
{
	LASER_CMD_DIR_FLAG_SHIT = 30,		/* [31:30] CMD dirction type */
	LASER_CMD_RESP_FLAG_SHIT = 28,		/* [   28] CMD response type */
	LASER_CMD_OUT_LEN_SHIT = 22,		/* [27:22] CMD out len 0~63byte */
	LASER_CMD_IN_LEN_SHIT = 16,		/* [21:16] CMD in len 0~63byte */
	LASER_CMD_OPCODE_SHIT = 0,			/* [15: 0] CMD opcode */

	LASER_CMD_DIR_FLAG_MASK = (0x3U << LASER_CMD_DIR_FLAG_SHIT),
	LASER_CMD_RESP_FLAG_MASK = (0x3U << LASER_CMD_RESP_FLAG_SHIT),
	LASER_CMD_OUT_LEN_MASK = (0x3fU << LASER_CMD_OUT_LEN_SHIT),
	LASER_CMD_IN_LEN_MASK = (0x3fU << LASER_CMD_IN_LEN_SHIT),
	LASER_CMD_OPCODE_MASK = (0xffffU << LASER_CMD_OPCODE_SHIT),
};

/* cmd direction type */
enum
{
	LASER_SET_CMD	 = 0x1U,
	LASER_GET_CMD	 = 0x2U,
	LASER_INOUT_CMD = 0x3U,
};

/* cmd response type */
enum
{
    LASER_BLOCK_WRITE_CMD = 2U,
	LASER_BLOCK_RESPONSE_CMD = 1U,
	LASER_NORMAL_RESPONSE_CMD = 0U,
};

enum {
	LASER_NULL = 1<<0,
	LASER_AL6045 = 1<<1,
	LASER_AL6010 = 1<<2,
};

typedef struct _tag_hwlaser_config_data
{
    uint32_t cfgtype;
    uint32_t cmd;
    int laser_type;
    int data;

    union {
        uint8_t  buf[64];
        uint16_t buf16[32];
    } u;
}hwlaser_config_data_t;


enum
{
	HWLASER_NAME_SIZE                          =   32,
	HWLASER_V4L2_EVENT_TYPE                       =   V4L2_EVENT_PRIVATE_START + 0x00080000,

	HWLASER_HIGH_PRIO_EVENT                       =   0x1500,
	HWLASER_MIDDLE_PRIO_EVENT                     =   0x2000,
	HWLASER_LOW_PRIO_EVENT                        =   0x3000,
};

typedef struct _tag_hwlaser_info
{
    char                                        product_name[HWLASER_NAME_SIZE];
    char                                        name[HWLASER_NAME_SIZE];
    int                                         i2c_idx;
} hwlaser_info_t;

typedef enum _tag_hwlaser_event_kind
{
    HWLASER_INFO_CMD_FINISH,
    HWLASER_INFO_ERROR,
    HWLASER_INFO_DUMP,
    HWLASER_INFO_OIS_DONE,
} hwlaser_event_kind_t;

typedef struct _tag_hwlaser_event
{
    hwlaser_event_kind_t                          kind;
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
}hwlaser_event_t;

#define HWLASER_IOCTL_GET_INFO                 _IOR('S', BASE_VIDIOC_PRIVATE + 1, hwlaser_info_t)
#define HWLASER_IOCTL_CONFIG               	_IOWR('A', BASE_VIDIOC_PRIVATE + 2, hwlaser_config_data_t)

#endif // __HW_ALAN_KERNEL_HWCAM_LASER_CFG_H__

