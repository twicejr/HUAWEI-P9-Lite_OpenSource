

#ifndef __HW_ALAN_KERNEL_COMPAT32_H__
#define __HW_ALAN_KERNEL_COMPAT32_H__

#include <linux/videodev2.h>
#include <linux/compat.h>
#include <linux/uaccess.h>
#include <media/v4l2-event.h>
#include <media/v4l2-fh.h>
#include <media/huawei/isp_cfg.h>

struct v4l2_event32 {
	__u32				type;
	union {
		struct v4l2_event_vsync		vsync;
		struct v4l2_event_ctrl		ctrl;
		struct v4l2_event_frame_sync	frame_sync;
		__u8			data[128];
	} u;
	__u32				pending;
	__u32				sequence;
#ifdef CONFIG_COMPAT	
	struct compat_timespec		timestamp;
#else
	struct timespec		timestamp;
#endif
	__u32				id;
	__u32				reserved[8];
};

struct v4l2_clip32 {
	struct v4l2_rect        c;
	compat_caddr_t 		next;
};

struct v4l2_window32 {
	struct v4l2_rect        w;
	__u32		  	field;	/* enum v4l2_field */
	__u32			chromakey;
	compat_caddr_t		clips; /* actually struct v4l2_clip32 * */
	__u32			clipcount;
	compat_caddr_t		bitmap;
};


struct v4l2_format32 {
	__u32	type;	/* enum v4l2_buf_type */
	union {
		struct v4l2_pix_format	pix;
		struct v4l2_pix_format_mplane	pix_mp;
		struct v4l2_window32	win;
		struct v4l2_vbi_format	vbi;
		struct v4l2_sliced_vbi_format	sliced;
		__u8	raw_data[200];        /* user-defined */
	} fmt;
};

typedef struct _tag_hwisp_stream_buf_info32
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
        struct compat_timeval                   timestamp;
        int64_t                                 _timestamp[2];
    };

    ovisp23_port_info_t                         port;

} hwisp_stream_buf_info_t32;

typedef struct _tag_hwcam_buf_status32
{
    int id;
    int buf_status;
   struct compat_timeval tv;
} hwcam_buf_status_t32;

#define VIDIOC_G_FMT32		_IOWR('V',  4, struct v4l2_format32)
#define VIDIOC_S_FMT32		_IOWR('V',  5, struct v4l2_format32)

#define	VIDIOC_DQEVENT32	_IOR ('V', 89, struct v4l2_event32)
#define HWCAM_V4L2_IOCTL_REQUEST_ACK32   _IOW('A', BASE_VIDIOC_PRIVATE + 0x20, struct v4l2_event32)
#define HWCAM_V4L2_IOCTL_NOTIFY32	_IOW('A', BASE_VIDIOC_PRIVATE + 0x21, struct v4l2_event32)
#define HWCAM_V4L2_IOCTL_THERMAL_GUARD32 _IOWR('A', BASE_VIDIOC_PRIVATE + 0x22, struct v4l2_event32)

#define HWISP_STREAM_IOCTL_ENQUEUE_BUF32   _IOW('A', BASE_VIDIOC_PRIVATE + 0x01, hwisp_stream_buf_info_t32)
#define HWISP_STREAM_IOCTL_DEQUEUE_BUF32   _IOR('A', BASE_VIDIOC_PRIVATE + 0x02, hwisp_stream_buf_info_t32)

#define HWCAM_V4L2_IOCTL_GET_BUF32   _IOR('A', BASE_VIDIOC_PRIVATE + 0x06, hwcam_buf_status_t32)
#define HWCAM_V4L2_IOCTL_PUT_BUF32   _IOW('A', BASE_VIDIOC_PRIVATE + 0x07, hwcam_buf_status_t32)
#define HWCAM_V4L2_IOCTL_BUF_DONE32   _IOW('A', BASE_VIDIOC_PRIVATE + 0x08, hwcam_buf_status_t32)

long compat_get_v4l2_event_data(struct v4l2_event __user *pdata, struct v4l2_event32 __user *pdata32);
long compat_put_v4l2_event_data(struct v4l2_event __user *pdata, struct v4l2_event32 __user *pdata32);
long compat_get_v4l2_format_data(struct v4l2_format *kp, struct v4l2_format32 __user *up);
long compat_put_v4l2_format_data(struct v4l2_format *kp, struct v4l2_format32 __user *up);


long compat_get_hwcam_buf_status_data(hwcam_buf_status_t __user *pdata, hwcam_buf_status_t32 __user *pdata32);
long compat_put_hwcam_buf_status_data(hwcam_buf_status_t __user *pdata, hwcam_buf_status_t32 __user *pdata32);


#endif
