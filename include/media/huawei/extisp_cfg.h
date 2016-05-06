


#ifndef __HW_ALAN_KERNEL_HWCAM_EXTISP_CFG_H__
#define __HW_ALAN_KERNEL_HWCAM_EXTISP_CFG_H__

#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/videodev2.h>
#include <media/huawei/camera.h>


typedef enum _tag_hwextisp_config_type
{
    HWCAM_EXTISP_POWERON,
    HWCAM_EXTISP_POWEROFF,
    HWCAM_EXTISP_LOADFW,
    HWCAM_EXTISP_CMD,
    HWCAM_EXTISP_MATCHID,
    //TODO...

} hwextisp_config_type_t;

/* 32-bit cmd mask */
enum
{
	EXTISP_CMD_DIR_FLAG_SHIT = 30,		/* [31:30] CMD dirction type */
	EXTISP_CMD_RESP_FLAG_SHIT = 28,		/* [   28] CMD response type */
	EXTISP_CMD_OUT_LEN_SHIT = 22,		/* [27:22] CMD out len 0~63byte */
	EXTISP_CMD_IN_LEN_SHIT = 16,		/* [21:16] CMD in len 0~63byte */
	EXTISP_CMD_OPCODE_SHIT = 0,			/* [15: 0] CMD opcode */

	EXTISP_CMD_DIR_FLAG_MASK = (0x3U << EXTISP_CMD_DIR_FLAG_SHIT),
	EXTISP_CMD_RESP_FLAG_MASK = (0x3U << EXTISP_CMD_RESP_FLAG_SHIT),
	EXTISP_CMD_OUT_LEN_MASK = (0x3fU << EXTISP_CMD_OUT_LEN_SHIT),
	EXTISP_CMD_IN_LEN_MASK = (0x3fU << EXTISP_CMD_IN_LEN_SHIT),
	EXTISP_CMD_OPCODE_MASK = (0xffffU << EXTISP_CMD_OPCODE_SHIT),
};

/* cmd direction type */
enum
{
	EXTISP_SET_CMD	 = 0x1U,
	EXTISP_GET_CMD	 = 0x2U,
	EXTISP_INOUT_CMD = 0x3U,
};

/* cmd response type */
enum
{
    EXTISP_BLOCK_WRITE_CMD = 2U,
	EXTISP_BLOCK_RESPONSE_CMD = 1U,
	EXTISP_NORMAL_RESPONSE_CMD = 0U,
};

enum {
	EXTISP_NULL = 1<<0,
	EXTISP_AL6045 = 1<<1,
	EXTISP_AL6010 = 1<<2,
};

struct extented_block_response_buf {
    union {
        void 	*user_buf_ptr;
		int64_t  _user_buf_ptr;
    };
    uint32_t user_buf_len;
};

typedef struct _tag_hwextisp_config_data
{
    uint32_t cfgtype;
    uint32_t cmd;
    int extisp_type;

    union {
        uint8_t  buf[64];
        uint16_t buf16[32];
    } u;
    struct extented_block_response_buf ext_buf;
}hwextisp_config_data_t;


enum
{
	HWEXTISP_NAME_SIZE                          =   32,
	HWEXTISP_V4L2_EVENT_TYPE                       =   V4L2_EVENT_PRIVATE_START + 0x00080000,

	HWEXTISP_HIGH_PRIO_EVENT                       =   0x1500,
	HWEXTISP_MIDDLE_PRIO_EVENT                     =   0x2000,
	HWEXTISP_LOW_PRIO_EVENT                        =   0x3000,
};

typedef struct _tag_hwextisp_info
{
    char                                        name[HWEXTISP_NAME_SIZE];
} hwextisp_info_t;

typedef enum _tag_hwextisp_event_kind
{
    HWEXTISP_INFO_CMD_FINISH,
    HWEXTISP_INFO_ERROR,
    HWEXTISP_INFO_DUMP,
    HWEXTISP_INFO_OIS_DONE,
} hwextisp_event_kind_t;

typedef struct _tag_hwextisp_event
{
    hwextisp_event_kind_t                          kind;
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
}hwextisp_event_t;

#define HWEXTISP_IOCTL_GET_INFO                 _IOR('S', BASE_VIDIOC_PRIVATE + 1, hwextisp_info_t)
#define HWEXTISP_IOCTL_CONFIG               	_IOWR('A', BASE_VIDIOC_PRIVATE + 2, hwextisp_config_data_t)

#endif // __HW_ALAN_KERNEL_HWCAM_EXTISP_CFG_H__

