

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fb.h>
#include <linux/delay.h>
#include <media/v4l2-common.h>
#include <media/v4l2-ioctl.h>
#include <asm/io.h>
#include <linux/ioctl.h>
//#include <mach/platform.h>
#include <linux/platform_device.h>
#include "k3_fake_capture.h"

#define DEBUG_DEBUG 0 
#define LOG_TAG "K3_FAKE_V4L2"
#include "log.h"

#define CAM_CAPTURE_DEF_WIDTH   2048 
#define CAM_CAPTURE_DEF_HEIGHT  1536

static camera_info sensor_info[] =
{
    {
        0,
        CAMERA_FACING_BACK,
        90,  /* orientation */
    },
    {
        1,
        CAMERA_FACING_FRONT,
        270,  /* orientation */
    }
};

/* support format for fake camera */
#define MAX_PREVIEW_FORMAT_NO 5
static u32 k3_fake_camera_support_preview_fmt[MAX_PREVIEW_FORMAT_NO] =
{
    V4L2_PIX_FMT_YYUV,
    V4L2_PIX_FMT_NV12,
    V4L2_PIX_FMT_YUV420,
    V4L2_PIX_FMT_YUYV

};

#define MAX_CAPTURE_FORMAT_NO 2
static u32 k3_fake_camera_support_capture_fmt[MAX_CAPTURE_FORMAT_NO] =
{
    V4L2_PIX_FMT_RGB565,
    V4L2_PIX_FMT_NV12
};

/* Camera control struct data */
static v4l2_ctl_struct v4l2_ctl;

static v4l2_ctl_struct *my_ctl; 

static int video_nr = 10;

/* capabilities of fake camera*/
#define THIS_AUTO_WHITE_BALANCE (1 << CAMERA_WHITEBALANCE_AUTO)
#define THIS_WHITE_BALANCE      (\
                ( 1 << CAMERA_WHITEBALANCE_INCANDESCENT)        | \
                ( 1 << CAMERA_WHITEBALANCE_FLUORESCENT)         | \
                ( 1 << CAMERA_WHITEBALANCE_DAYLIGHT)            | \
                ( 1 << CAMERA_WHITEBALANCE_CLOUDY_DAYLIGHT)       \
                )
#define THIS_BRIGHTNESS         (\
                ( 1 << CAMERA_BRIGHTNESS_L2)                    | \
                ( 1 << CAMERA_BRIGHTNESS_L1)                    | \
                ( 1 << CAMERA_BRIGHTNESS_H0)                    | \
                ( 1 << CAMERA_BRIGHTNESS_H1)                    | \
                ( 1 << CAMERA_BRIGHTNESS_H2)                      \
                )
#define THIS_CONTRAST           (\
                ( 1 << CAMERA_CONTRAST_L2)                      | \
                ( 1 << CAMERA_CONTRAST_L1)                      | \
                ( 1 << CAMERA_CONTRAST_H0)                      | \
                ( 1 << CAMERA_CONTRAST_H1)                      | \
                ( 1 << CAMERA_CONTRAST_H2)                        \
                )
#define THIS_SATURATION         (\
                ( 1 << CAMERA_SATURATION_L2)                    | \
                ( 1 << CAMERA_SATURATION_L1)                    | \
                ( 1 << CAMERA_SATURATION_H0)                    | \
                ( 1 << CAMERA_SATURATION_H1)                    | \
                ( 1 << CAMERA_SATURATION_H2)                      \
                )
#define THIS_ISO                (\
                ( 1 << CAMERA_ISO_AUTO)                         | \
                ( 1 << CAMERA_ISO_100)                          | \
                ( 1 << CAMERA_ISO_200)                          | \
                ( 1 << CAMERA_ISO_400)                          | \
                ( 1 << CAMERA_ISO_800)                            \
                )
#define THIS_EFFECT             (\
                ( 1 << CAMERA_EFFECT_NONE)                      | \
                ( 1 << CAMERA_EFFECT_MONO)                      | \
                ( 1 << CAMERA_EFFECT_NEGATIVE)                  | \
                ( 1 << CAMERA_EFFECT_REDTINT)                   | \
                ( 1 << CAMERA_EFFECT_BLUETINT)                  | \
                ( 1 << CAMERA_EFFECT_GREENTINT)                   \
                )
#define THIS_SHARPNESS          (\
                ( 1 << CAMERA_SHARPNESS_AUTO)                   | \
                ( 1 << CAMERA_SHARPNESS_1)                      | \
                ( 1 << CAMERA_SHARPNESS_2)                      | \
                ( 1 << CAMERA_SHARPNESS_3)                      | \
                ( 1 << CAMERA_SHARPNESS_4)                      | \
                ( 1 << CAMERA_SHARPNESS_5)                        \
                )
#define THIS_FLASH              (\
                ( 1 << CAMERA_FLASH_ON)                         | \
                ( 1 << CAMERA_FLASH_TORCH)                      | \
                ( 1 << CAMERA_FLASH_OFF)                        | \
                ( 1 << CAMERA_FLASH_AUTO)                         \
                )
#define THIS_FREQUENCY          (\
                ( 1 << CAMERA_FLICKER_AUTO)                     | \
                ( 1 << CAMERA_FLICKER_50Hz)                     | \
                ( 1 << CAMERA_FLICKER_60Hz)                     | \
                ( 1 << CAMERA_FLICKER_OFF)                        \
                )
#define THIS_FOCUS_MODE         (\
                ( 1 << CAMERA_FOCUS_AUTO)                       | \
                ( 1 << CAMERA_FOCUS_INFINITY)                   | \
                ( 1 << CAMERA_FOCUS_MACRO)                      | \
                ( 1 << CAMERA_FOCUS_CONTINUOUS_VIDEO)             \
                )
#define THIS_HFLIP ( 1 << CAMERA_H_FLIP)
#define THIS_VFLIP ( 1 << CAMERA_V_FLIP)

#define THIS_HDR                (\
                ( 1 << CAMERA_HDR_ON)                           | \
                ( 1 << CAMERA_HDR_OFF)                            \
                )
#define THIS_WDR                (\
                ( 1 << CAMERA_WDR_ON)                           | \
                ( 1 << CAMERA_WDR_OFF)                            \
                )
#define THIS_3D                 (\
                ( 1 << CAMERA_3D_ON)                            | \
                ( 1 << CAMERA_3D_OFF)                             \
                )
#define THIS_SCENE              (\
                ( 1 << CAMERA_SCENE_AUTO)                       | \
                ( 1 << CAMERA_SCENE_ACTION)                     | \
                ( 1 << CAMERA_SCENE_PORTRAIT)                   | \
                ( 1 << CAMERA_SCENE_LANDSPACE)                  | \
                ( 1 << CAMERA_SCENE_NIGHT)                      | \
                ( 1 << CAMERA_SCENE_NIGHT_PORTRAIT)             | \
                ( 1 << CAMERA_SCENE_THEATRE)                    | \
                ( 1 << CAMERA_SCENE_BEACH)                      | \
                ( 1 << CAMERA_SCENE_SNOW)                       | \
                ( 1 << CAMERA_SCENE_SUNSET)                     | \
                ( 1 << CAMERA_SCENE_STEADYPHOTO)                | \
                ( 1 << CAMERA_SCENE_FIREWORKS)                  | \
                ( 1 << CAMERA_SCENE_SPORTS)                     | \
                ( 1 << CAMERA_SCENE_PARTY)                      | \
                ( 1 << CAMERA_SCENE_CANDLELIGHT)                | \
                ( 1 << CAMERA_SCENE_BARCODE)                      \
                )
#define THIS_METERING           (\
                ( 1 << CAMERA_PHOTOMETRY_SPOT)                  | \
                ( 1 << CAMERA_PHOTOMETRY_CWA)                   | \
                ( 1 << CAMERA_PHOTOMETRY_AVERAGE)                 \
                )



static camera_capability this_cap[] = {
    { V4L2_CID_AUTO_WHITE_BALANCE,  THIS_AUTO_WHITE_BALANCE },
    { V4L2_CID_DO_WHITE_BALANCE,    THIS_WHITE_BALANCE      },
    { V4L2_CID_BRIGHTNESS,          THIS_BRIGHTNESS         },
    { V4L2_CID_CONTRAST,            THIS_CONTRAST           },
    { V4L2_CID_SATURATION,          THIS_SATURATION         },
    { V4L2_CID_ISO,                 THIS_ISO                },
    { V4L2_CID_EFFECT,              THIS_EFFECT             },
    { V4L2_CID_SCENE,               THIS_SCENE              },
    { V4L2_CID_SHARPNESS,           THIS_SHARPNESS          },
    { V4L2_CID_METERING,            THIS_METERING           },
    { V4L2_CID_FLASH_MODE,          THIS_FLASH              },
    { V4L2_CID_POWER_LINE_FREQUENCY,THIS_FREQUENCY          },
    { V4L2_CID_FOCUS_MODE,          THIS_FOCUS_MODE         },
    { V4L2_CID_HFLIP,               THIS_HFLIP              },
    { V4L2_CID_VFLIP,               THIS_VFLIP              },
    { V4L2_CID_HDR,                 THIS_HDR                },
    { V4L2_CID_WDR,                 THIS_WDR                },
#ifdef WITH_3D
    { V4L2_CID_3D,                  THIS_3D                 },
#endif
};

static struct v4l2_frmsizeenum fake_camera_framesizes[] =
{
    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 128,
            .discrete.height    = 96,
        },
    },


    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 160,
            .discrete.height    = 120,
        },
    },

    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 176,
            .discrete.height    = 144,
        },
    },

    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 240,
            .discrete.height    = 176,
        },
    },

    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 320,
            .discrete.height    = 240,
        },
    },

    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 352,
            .discrete.height    = 288,
        },
    },

    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 480,
            .discrete.height    = 320,
        },
    },

    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 640,
            .discrete.height    = 480,
        },
    },
    
    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 720,
            .discrete.height    = 480,
        },
    },
    
    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 720,
            .discrete.height    = 576,
        },
    },

    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 800,
            .discrete.height    = 480,
        },
    },

    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 800,
            .discrete.height    = 600,
        },
    },

    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 1024,
            .discrete.height    = 768,
        },
    },
    
    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 1280,
            .discrete.height    = 720,
        },
    },

    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 1280,
            .discrete.height    = 960,
        },
    },

    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 1280,
            .discrete.height    = 1024,
        },
    },
    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 1600,
            .discrete.height    = 1200,
        },
    },
    
    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 1920,
            .discrete.height    = 1080,
        },
    },
    
    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 1920,
            .discrete.height    = 1088,
        },
    },

    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 2048,
            .discrete.height    = 1536,
        },
    },
    
    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 2592,
            .discrete.height    = 1936,
        },
    },
    
    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 2592,
            .discrete.height    = 1944,
        },
    },
    
    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 2592,
            .discrete.height    = 1458,
        },
    },
    
    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 3264,
            .discrete.height    = 2448,
        },
    },
    
    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 3264,
            .discrete.height    = 1968,
        },
    },
    
    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 3264,
            .discrete.height    = 1836,
        },
    },
    
    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 4000,
            .discrete.height    = 3000,
        },
    },
    
    {
        .type = V4L2_FRMSIZE_TYPE_DISCRETE,
        {
            .discrete.width     = 4000,
            .discrete.height    = 2250,
        },
    },
};

static struct v4l2_frmivalenum fake_camera_frmivalenum[] =
{
    {
        .type = V4L2_FRMIVAL_TYPE_DISCRETE,
        {
            .discrete.numerator     = 1,
            .discrete.denominator   = 30,
        },
    },

    {
        .type = V4L2_FRMIVAL_TYPE_DISCRETE,
        {
            .discrete.numerator     = 1,
            .discrete.denominator   = 25,
        },
    },

    {
        .type = V4L2_FRMIVAL_TYPE_DISCRETE,
        {
            .discrete.numerator     = 1,
            .discrete.denominator   = 20,
        },
    },

    {
        .type = V4L2_FRMIVAL_TYPE_DISCRETE,
        {
            .discrete.numerator     = 1,
            .discrete.denominator   = 15,
        },
    },
    
    {
        .type = V4L2_FRMIVAL_TYPE_DISCRETE,
        {
            .discrete.numerator     = 1,
            .discrete.denominator   = 10,
        },
    },

};

/*
 **************************************************************************
 * FunctionName: dump_preview;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static __attribute__((unused))  void dump_preview ( void )
{
    int i = 0;
    print_debug("enter %s", __FUNCTION__);

    print_debug("\n");
    for(i=0; i<my_ctl->preview_nr; i++)
    {
        print_debug("preview==index=%d, phyaddr=0x%08x, viraddr=%p",    \
                    my_ctl->buf_preview[i].index,                       \
                    my_ctl->buf_preview[i].phyaddr,                     \
                    my_ctl->buf_preview[i].viraddr );    
    }
}

/*
 **************************************************************************
 * FunctionName: dump_capture;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static __attribute__((unused))  void dump_capture (void )
{
    int i = 0;
    print_debug("enter %s", __FUNCTION__);
    
    print_debug("\n");
    for(i=0; i<my_ctl->capture_nr; i++)
    {
        print_debug("capture==index=%d, phyaddr=0x%08x, viraddr=%p",    \
                    my_ctl->buf_capture[i].index,                       \
                    my_ctl->buf_capture[i].phyaddr,                     \
                    my_ctl->buf_capture[i].viraddr );    
    }
}

/*
 **************************************************************************
 * FunctionName: dump_queue_buffers;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static __attribute__((unused)) void dump_queue_buffers ( struct list_head* l )
{
    camera_frame_buf* f;
    print_debug("enter %s", __FUNCTION__);

    list_for_each_entry(f, l, queue)
    {
        print_debug("index=%d frame[%08x]", f->index, f->phyaddr);
    }
}

/*
 **************************************************************************
 * FunctionName: add_to_ready_q;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static inline void add_to_ready_q ( camera_frame_buf* f, struct list_head* l )
{
    print_debug("enter %s", __FUNCTION__);

    if(!(f->flags & CAMERA_FLAG_READYQ))
    {
        list_add_tail(&f->queue, l);
        f->flags |= CAMERA_FLAG_READYQ;
    }
    else
    {
        print_warn("frame[%08x] has been added to readyq", f->phyaddr);
    }
}

/*
 **************************************************************************
 * FunctionName: NA;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static inline void del_from_ready_q ( camera_frame_buf* f )
{
    print_debug("enter %s", __FUNCTION__);

    if(f->flags & CAMERA_FLAG_READYQ)
    {
        list_del(&f->queue);
        f->flags &= (~CAMERA_FLAG_READYQ);
    }
    else
    {
        print_warn("frame[%08x] NOT in readyq", f->phyaddr);
    }
}


/*
 **************************************************************************
 * FunctionName: set_default_capture_fmt;
 * Description : set default value of v4l2_format struct;
 * Input       : NA;
 * Output      : f: format struct need to be filled;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static inline void k3_fake_set_default_capture_fmt(struct v4l2_format *f)
{
    print_debug("enter %s", __FUNCTION__);

    WARN_ON(f == NULL);

    f->type                 = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    f->fmt.pix.width        = CAM_CAPTURE_DEF_WIDTH;
    f->fmt.pix.height       = CAM_CAPTURE_DEF_HEIGHT;
    f->fmt.pix.pixelformat  = V4L2_PIX_FMT_NV12;
    f->fmt.pix.bytesperline = f->fmt.pix.width * 3/2;
    f->fmt.pix.sizeimage    = f->fmt.pix.width * f->fmt.pix.height * 3/2;

    return;
}

/*
 **************************************************************************
 * FunctionName: set_default_preview_fmt;
 * Description : set default value of v4l2_format struct;
 * Input       : NA;
 * Output      : f: format struct need to be filled;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static inline void k3_fake_set_default_preview_fmt(struct v4l2_format *f)
{
    print_debug("enter %s", __FUNCTION__);

    WARN_ON(f == NULL);

    f->type                 = V4L2_BUF_TYPE_VIDEO_OVERLAY;
    f->fmt.pix.width        = CAM_CAPTURE_DEF_WIDTH;
    f->fmt.pix.height       = CAM_CAPTURE_DEF_HEIGHT;
    f->fmt.pix.pixelformat  = V4L2_PIX_FMT_NV12;
    f->fmt.pix.bytesperline = f->fmt.pix.width * 3/2;
    f->fmt.pix.sizeimage    = f->fmt.pix.width * f->fmt.pix.height * 3/2;

    return;
}

/*
 **************************************************************************
 * FunctionName: k3_fill_buffer;
 * Description : Set phyaddr and size of v4l2_buffer;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static inline void k3_fake_register_buffer(camera_frame_buf *a,
                       struct v4l2_buffer *b)
{
    print_debug("enter %s", __FUNCTION__);

    WARN_ON(a == NULL);
    WARN_ON(b == NULL);

    a->index    = b->index;
    a->size     = b->length;
    a->phyaddr  = b->m.offset;
    a->flags    = 0;
    print_debug("======index=%d size=%d phyaddr=0x%08x =====\n", a->index, a->size, a->phyaddr);
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_preview_off;
 * Description : A. stop preview;
 *               B. wake up process in preview_queue
 *               C. init preview_xxx_q
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_preview_off ( v4l2_ctl_struct *cam )
{
    int i = 0;
    print_info("enter %s", __FUNCTION__);

    for(; i< cam->preview_nr; i++)
    {
        iounmap(cam->buf_preview[i].viraddr);
        cam->buf_preview[i].viraddr = 0;
    }
    cam->preview_on     = 0;
    cam->preview_pid    = 0;
    
    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_capture_off;
 * Description : A. stop taking picture;
 *               B. wake up process in capture_queue
 *               C. init capture_xxx_q
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_capture_off(v4l2_ctl_struct *cam)
{
    int i=0;
    print_info("enter %s", __FUNCTION__);

    for(; i< cam->capture_nr; i++)
    {
        iounmap(cam->buf_capture[i].viraddr);    
        cam->buf_capture[i].viraddr = 0;
    }
    
    INIT_LIST_HEAD(&cam->capture_ready_q);
    
    /* disable isp to stop capture */
    cam->capture_on     = 0;
    cam->capture_pid    = 0;
    cam->capture_nr     = 0;
    
    return 0;
}

/*
 **************************************************************************
 * FunctionName: getPixelDepth;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_camera_get_pixel_pepth(int format)
{
    int depth = 0;
    print_debug("enter %s", __FUNCTION__);

    switch (format) {
    case V4L2_PIX_FMT_RGB565:
        depth = 16;
        break;

    case V4L2_PIX_FMT_RGB24:
        depth = 24;
        break;

    case V4L2_PIX_FMT_NV12:
        depth = 12;
        break;

    case V4L2_PIX_FMT_NV21:
        depth = 12;
        break;

    case V4L2_PIX_FMT_YUV420:
        depth = 12;
        break;

    case V4L2_PIX_FMT_YUYV:
        depth = 16;
        break;
    case V4L2_PIX_FMT_YVYU:
        depth = 16;
        break;

    case V4L2_PIX_FMT_UYVY:
        depth = 16;
        break;

    case V4L2_PIX_FMT_VYUY:
        depth = 16;
        break;

    case V4L2_PIX_FMT_NV16:
        depth = 16;
        break;

    case V4L2_PIX_FMT_NV61:
        depth = 16;
        break;

    case V4L2_PIX_FMT_YUV422P:
        depth = 16;
        break;

    default:
        depth = 16;
        break;
    }

    return depth;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_s_fmt_capture;
 * Description : Set format information of picture;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : 0: Success; Other: Fail;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_ioctl_s_fmt_capture(struct file *file, void *fh, struct v4l2_format *f)
{
    int bits_per_pixel      = 16;
    v4l2_ctl_struct *cam    = NULL;
    struct v4l2_frmsize_discrete fd;

    print_debug("enter %s", __FUNCTION__);

    if (!fh || !video_get_drvdata((struct video_device *)fh))
    {
        print_error("%s get video device fail", __FUNCTION__);
        return -EBADF;
    }
    
    cam = video_get_drvdata((struct video_device *)fh);

    if (cam->capture_on)
    {
        print_error("%s capturing", __FUNCTION__);
        return -EBUSY;
    }

    bits_per_pixel          = k3_fake_camera_get_pixel_pepth(f->fmt.pix.pixelformat);
    fd.width                = f->fmt.pix.width;
    fd.height               = f->fmt.pix.height;
    f->fmt.pix.sizeimage    = f->fmt.pix.width * f->fmt.pix.height * bits_per_pixel/8;
    f->fmt.pix.priv         = f->fmt.pix.width * f->fmt.pix.height * bits_per_pixel/8;
    print_info("capture size[%dx%d], sizeimage=[%d]", fd.width, fd.height, f->fmt.pix.sizeimage);

    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s get busy_lock fail", __FUNCTION__);
        return -EINTR;
    }
    cam->fmt_capture = *f;
    
    up(&cam->busy_lock);

    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_s_fmt_preview;
 * Description : Set format information of preview;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : 0: Success; Other: Fail;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_ioctl_s_fmt_preview(struct file *file, void *fh, struct v4l2_format *f)
{
    int bits_per_pixel      = 16;
    v4l2_ctl_struct *cam    = NULL;

    print_debug("enter %s", __FUNCTION__);

    if (!fh || !video_get_drvdata((struct video_device *)fh))
    {
        print_error("%s get video device fail", __FUNCTION__);
        return -EBADF;
    }
    
    cam = video_get_drvdata((struct video_device *)fh);

    if (cam->preview_on)
    {
        print_error("%s previewing", __FUNCTION__);
        return -EBUSY;
    }

    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s get busy_lock fail", __FUNCTION__);
        return -EINTR;
    }
    
    bits_per_pixel          = k3_fake_camera_get_pixel_pepth(f->fmt.pix.pixelformat);
    f->fmt.pix.sizeimage    = f->fmt.pix.width * f->fmt.pix.height * bits_per_pixel/8;
    f->fmt.pix.priv         = f->fmt.pix.width * f->fmt.pix.height * bits_per_pixel/8;
    cam->fmt_preview        = *f;

    print_info("preview size[%dx%d], sizeimage=[%d]", f->fmt.pix.width, f->fmt.pix.height, f->fmt.pix.sizeimage);
    
    up(&cam->busy_lock);

    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_g_fmt_capture;
 * Description : Get format information of picture;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : 0: Success; Other: Fail;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_ioctl_g_fmt_capture(struct file *file, void *fh, struct v4l2_format *f)
{
    v4l2_ctl_struct *cam = NULL;

    print_debug("enter %s", __FUNCTION__);

    if (!fh || !video_get_drvdata((struct video_device *)fh))
    {
        print_error("%s get video device fail", __FUNCTION__);
        return -EBADF;
    }
    
    cam = video_get_drvdata((struct video_device *)fh);
    *f  = cam->fmt_capture;

    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_g_fmt_preview;
 * Description : Get preview information of preview;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : 0: Success; Other: Fail;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_ioctl_g_fmt_preview(struct file *file, void *fh, struct v4l2_format *f)
{
    v4l2_ctl_struct *cam = NULL;

    print_debug("enter %s", __FUNCTION__);

    if (!fh || !video_get_drvdata((struct video_device *)fh))
    {
        print_error("%s get video device fail", __FUNCTION__);
        return -EBADF;
    }
    
    cam = video_get_drvdata((struct video_device *)fh);
    *f  = cam->fmt_preview;

    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_g_ctrl;
 * Description : Get control information of current sensor:
 *               white balance,
 *               brightness,
 *               contrast,
 *               ... ...
 *               1. If camera sensor does not support the function, return 0;
 *               2. Else return the current value of that control;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_ioctl_g_ctrl(struct file *file, void *fh,
                    struct v4l2_control *a)
{
    int ret                 = 0;
    v4l2_ctl_struct *cam    = NULL;
    a->value                = 0;

    print_debug("enter %s", __FUNCTION__);

    if (!fh || !video_get_drvdata((struct video_device *)fh))
    {
        print_error("%s get video device fail", __FUNCTION__);
        return -EBADF;
    }
    
    cam = video_get_drvdata((struct video_device *)fh);

    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s get busy_lock fail", __FUNCTION__);
        return -EINTR;
    }

    /*
     * get control of camera sensor:
     * 1. check if set_xxx is set by sensor
     * 2. YES: get current control value of sensor
     * 3. NO: return -EINVAL(means this control is not supported by sensor)
     */
    switch (a->id)
    {
            /* auto white balance */
        case V4L2_CID_AUTO_WHITE_BALANCE:
            {
                break;
            }
            /* manual white balance */
        case V4L2_CID_DO_WHITE_BALANCE:
            {
                break;
            }
            /* brightness */
        case V4L2_CID_BRIGHTNESS:
            {
                break;
            }
            /* flash mode */
        case V4L2_CID_FLASH_MODE:
            {
                break;
            }
            /* line frequency */
        case V4L2_CID_POWER_LINE_FREQUENCY:
            {
                break;
            }
            /* auto focus mode */
        case V4L2_CID_FOCUS_AUTO:
            {
                print_info("=====focus auto======");
                break;
            }
            /* relative focus mode */
        case V4L2_CID_FOCUS_RELATIVE:
            {
                break;
            }
            /* absolute focus mode */
        case V4L2_CID_FOCUS_ABSOLUTE:
            {
                break;
            }
            /* external focus mode */
        case V4L2_CID_EXT_FOCUS:
            {
                break;
            }
        
            /* scene mode */
        case V4L2_CID_SCENE:
            {
                break;
            }
            /* horizontal flip */
        case V4L2_CID_HFLIP:
            {
                break;
            }
            /* vertical flip */
        case V4L2_CID_VFLIP:
            {
                break;
            }
        /* relative zoom mode */
        case V4L2_CID_ZOOM_RELATIVE:
            {
                break;
            }
        case V4L2_CID_CAPTURE_MODE:
            {
                a->value = ISP_CAPTURE_ONLINE;
                break;
            }
        case V4L2_CID_MAX_FOCUS_AREA:
            {
                print_info("==== max focus area ====");
                a->value = 10;
                break;
            }
        default:
            {
                ret = -EINVAL;
                break;
            }
    }
    up(&cam->busy_lock);

    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_s_ctrl;
 * Description : SET control information of the current sensor;
 *               white balance,
 *               brightness,
 *               contrast,
 *               ... ...
 *               1. If camera sensor does not support the function, return -EINVAL;
 *               2. Else set the given value to sensor, and then it will take effect;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_ioctl_s_ctrl(struct file *file, void *fh, struct v4l2_control *v4l2_param)
{
    int ret                 = 0;
    v4l2_ctl_struct *cam    = NULL;

    print_debug("enter %s", __FUNCTION__);

    if (!fh || !video_get_drvdata((struct video_device *)fh))
    {
        print_error("%s get video device fail", __FUNCTION__);
        return -EBADF;
    }
    
    cam = video_get_drvdata((struct video_device *)fh);

    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s get busy_lock fail", __FUNCTION__);
        return -EINTR;
    }

    switch (v4l2_param->id)
    {        
            /* auto white balance */
        case V4L2_CID_AUTO_WHITE_BALANCE:
            {
                print_info("set white balance to [auto]");
                break;
            }
            /* manual white balance */
        case V4L2_CID_DO_WHITE_BALANCE:
            {
                print_info("set white balance to [%d]", v4l2_param->value);
                break;
            }
            /* brightness */
        case V4L2_CID_BRIGHTNESS:
            {
                print_info("set brightness to [%d]", v4l2_param->value);
                break;
            }
        case V4L2_CID_FLASH_MODE:
            {
                print_info("set flash mode to [%d]", v4l2_param->value);
                break;
            }
            /* line frequency */
        case V4L2_CID_POWER_LINE_FREQUENCY:
            {
                print_info("set antibanding to [%d]", v4l2_param->value);
                break;
            }
            /* auto focus mode */
        case V4L2_CID_FOCUS_AUTO:
            {
                print_info("set focus mode to [%d]", v4l2_param->value);
                break;
            }
            /* relative focus mode */
        case V4L2_CID_FOCUS_RELATIVE:
            {
                print_info("set focus mode to [%d]", v4l2_param->value);
                break;
            }
            /* absolute focus mode */
        case V4L2_CID_FOCUS_ABSOLUTE:
            {
                print_info("set focus mode to [%d]", v4l2_param->value);
                break;
            }
            /* external focus mode */
        case V4L2_CID_EXT_FOCUS:
            {
                print_info("set focus mode to [%d]", v4l2_param->value);
                break;
            }
            /* scene mode */
        case V4L2_CID_SCENE:
            {
                print_info("set scene mode to [%d]", v4l2_param->value);
                break;
            }
            /* horizontal flip */
        case V4L2_CID_HFLIP:
            {
                print_info("set h flip to [%d]", v4l2_param->value);
                break;
            }
            /* vertical flip */
        case V4L2_CID_VFLIP:
            {
                print_info("set v flip to [%d]", v4l2_param->value);
                break;
            }
        /* zoom */
        case V4L2_CID_ZOOM_RELATIVE:
            {
                print_info("set zoom to [%d]", v4l2_param->value);
                break;
            }
            /* select a sensor to be used */
        case V4L2_CID_SET_SENSOR:
            {
                print_info("set sensor to [%d]", v4l2_param->value);
                break;
            }
        case V4L2_CID_CONTRAST:
            {
                print_info("set contrast to [%d]", v4l2_param->value);
                break;
            }
        case V4L2_CID_SATURATION:
            {
                print_info("set saturation to [%d]", v4l2_param->value);
                break;
            }
        case V4L2_CID_EXPOSURE:
            {
                print_info("set exposure to [%d]", v4l2_param->value);
                break;
            }
        case V4L2_CID_EFFECT:
            {
                print_info("set effect to [%d]", v4l2_param->value);
                break;
            }
        case V4L2_CID_ISO:
            {
                print_info("set iso to [%d]", v4l2_param->value);
                break;
            }
        case V4L2_CID_SHARPNESS:
            {
                print_info("set sharpness to [%d]", v4l2_param->value);
                break;
            }
        case V4L2_CID_METERING:
            {
                print_info("set metering mode to [%d]", v4l2_param->value);    
            }

        case V4L2_CID_HDR:
            {
                print_info("set hdr mode to [%d]", v4l2_param->value);
                break;
            }
        case V4L2_CID_WDR:
            {
                print_info("set wdr mode to [%d]", v4l2_param->value);
                break;
            }

        default:
            {
                break;
            }
    }

    up(&cam->busy_lock);

    return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_fake_camera_get_capability;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_camera_get_capability(u32 id, u32 * value)
{
    int i = 0;

    print_debug("enter %s", __FUNCTION__);

    switch(id)
    {
        case V4L2_CID_ZOOM_RELATIVE:
        {
            *value = 0x00640005; //for 5xZoom
            break;
        }

        case V4L2_CID_EXPOSURE_MAX:
        {
            /* if not support, must set to 0 */
            /* -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2 */
            *value = (CAMERA_EV_MAX - 1) /2;
            break;
        }

        case V4L2_CID_EXPOSURE_STEP:
        {
            /* if not support, must set to 0 */
            /* means 50/100 */
            *value = 50;
            break;
        }

        case V4L2_CID_MAX_NUM_METERING_AREAS:
        {
            /* if not support, must set to 0 */
            *value = 10;
            break;
        }

        case V4L2_CID_FOCAL_LENGTH:
        {
            /* means 431/100 */
            *value = 431;
            break;
        }

        case V4L2_CID_HORIZONTAL_VIEW_ANGLE:
        {
            /* means 5480/100 */
            *value = 5480;
            break;
        }
        
        case V4L2_CID_VERTICAL_VIEW_ANGLE:
        {
            /* means 4250/100 */
            *value = 4250;
            break;
        }

        case V4L2_CID_SMOOTHZOOM_SUPPORT:
        {
            /* if not support, must set to 0 */
            *value = 1;
            break;
        }

        default:
        {
            for (i = 0; i < sizeof(this_cap) / sizeof(this_cap[0]); ++i)
            {
                if (id == this_cap[i].id)
                {
                    *value = this_cap[i].value;
                    break;
                }
            }
            break;
        }
    }

    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_g_caps;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static long k3_fake_v4l2_ioctl_g_caps(struct file *file, void *fh, bool valid_prio, int cmd, void *arg)
{
    int ret                             = 0;
    int i                               = 0;
    int ext_ctls_size                   = 0;
    void *mbuf                          = NULL;
    void __user *user_ptr               = NULL;
    v4l2_ctl_struct *cam                = NULL;
    struct v4l2_ext_controls *ext_ctls  = arg;
    struct v4l2_ext_control *controls   = NULL;

    if (VIDIOC_CHECK_CAP != cmd)
    {
        print_error("invalid ioctl VIDIOC_CHECK_CAP=%#x, cmd = %08x", VIDIOC_CHECK_CAP, cmd);
        return -EINVAL;
    }

    if (!fh || !video_get_drvdata((struct video_device *)fh))
    {
        print_error("%s get video device fail", __FUNCTION__);
        return -EBADF;
    }
    
    cam = video_get_drvdata((struct video_device *)fh);

    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s get busy_lock fail", __FUNCTION__);
        return -EINTR;
    }

    if (ext_ctls->ctrl_class != V4L2_CTRL_CLASS_USER)
    {
        print_error("unsupported ctrl class!");
        return -EINVAL;
    }

    /* allocate buffer */
    user_ptr        = (void __user *)ext_ctls->controls;
    ext_ctls_size   = ext_ctls->count * sizeof(struct v4l2_ext_control);
    if (ext_ctls->count)
    {
        mbuf = kmalloc(ext_ctls_size, GFP_KERNEL);
        if (!mbuf)
        {
            ret = -ENOMEM;
            print_error("fail to allocate buffer fo ext controls");
            goto out;
        }

        controls = (struct v4l2_ext_control *)mbuf;
        if (copy_from_user(mbuf, user_ptr, ext_ctls_size))
        {
            print_error("fail to copy data from user space mem");
            ret = -EFAULT;
            goto out;
        }
    }

    for (i = 0; i < ext_ctls->count; ++i)
    {
        k3_fake_camera_get_capability(controls[i].id, &controls[i].value);
    }
    
    if (ext_ctls->count)
    {
        if (copy_to_user((void __user *)user_ptr, mbuf, ext_ctls_size))
        {
            ret = -EFAULT;
            goto out;
        }
    }

out:
    if (mbuf)
    {
        kfree(mbuf);
    }

    up(&cam->busy_lock);
    return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_fake_v4l2_ioctl_g_ext_ctrls;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_ioctl_g_ext_ctrls(struct file *file, void *fh, struct v4l2_ext_controls *arg)
{
    void *mbuf              = NULL;     
    v4l2_ctl_struct *cam    = NULL;
    unsigned int cid_idx    = 0;
    int ret                 = 0;
   
    struct v4l2_ext_controls *ext_ctls  = arg;
    struct v4l2_ext_control *controls   = NULL;

    print_debug("enter %s", __FUNCTION__);

    if (!fh || !video_get_drvdata((struct video_device *)fh))
    {
        print_error("%s get video device fail", __FUNCTION__);
        return -EBADF;
    }

    cam = video_get_drvdata((struct video_device *)fh);
    
    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s get busy_lock fail", __FUNCTION__);
        return -EINTR;
    }

    if (ext_ctls->ctrl_class != V4L2_CTRL_CLASS_CAMERA)
    {
        print_error("unsupported ctrl class!");
        ret = -EINVAL;
        goto out;
    }

    controls = (struct v4l2_ext_control *)ext_ctls->controls;
        

    for(cid_idx=0; cid_idx<ext_ctls->count; cid_idx++)
    {
        switch(controls[cid_idx].id)
        {
            //get capture buffer size
            case V4L2_CID_CAPTURE_BUFSIZE:
            {                
                controls[cid_idx].value = cam->fmt_capture.fmt.pix.sizeimage;
                break;
            }

            //get camera count
            case V4L2_CID_SENSOR_COUNT:
            {
                controls[cid_idx].value = 2;
                break;
            }

            //get camera infomation, include facing and orientation
            case V4L2_CID_SENSOR_INFO:
            {
                camera_info *info = (camera_info *)(controls[cid_idx].string);
                memcpy((char *)info, &sensor_info[0], sizeof(sensor_info));
                break;
            }

            case V4L2_CID_FOCUS_RESULT:
            {
                print_info("=====read rect result=====");
                focus_result* result = (focus_result*)(controls[cid_idx].string);
                int i = 0;
                for(i = 0; i < FOCUS_AREA_MAX_NUM; i++)
                {
                    result->each_status[i] = STATUS_FOCUSED;
                }
                result->status = STATUS_FOCUSED;
                break;
            }
            default:
            {
                break;
            }
            
        }    
        
    }
out:
    if (mbuf)
    {
        kfree(mbuf);
    }

    up(&cam->busy_lock);

    return ret;
    
}

/*
 **************************************************************************
 * FunctionName: k3_fake_v4l2_ioctl_s_ext_ctrls;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_ioctl_s_ext_ctrls(struct file *file, void *fh, struct v4l2_ext_controls *arg)
{
    int ext_ctls_size       = 0;
    void *mbuf              = NULL;     
    v4l2_ctl_struct *cam    = NULL;
    unsigned int cid_idx    = 0;
    int ret                 = 0;

    struct v4l2_buffer vbuffer;
    struct v4l2_ext_controls *ext_ctls  = arg;
    struct v4l2_ext_control *controls   = NULL;
    
    print_debug("enter %s", __FUNCTION__);

    if (!fh || !video_get_drvdata((struct video_device *)fh))
    {
        print_error("%s get video device fail", __FUNCTION__);
        return -EBADF;
    }
    
    cam = video_get_drvdata((struct video_device *)fh);
    
    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s get busy_lock fail", __FUNCTION__);
        return -EINTR;
    }

    if (ext_ctls->ctrl_class != V4L2_CTRL_CLASS_CAMERA)
    {
        print_error("unsupported ctrl class!");
        ret = -EINVAL;
        goto end;
    }

    ext_ctls_size = ext_ctls->count * sizeof(struct v4l2_ext_control);
    if (ext_ctls->count)
    {
        mbuf = kmalloc(ext_ctls_size, GFP_KERNEL);
        if (!mbuf)
        {
            ret = -ENOMEM;
            print_error("fail to allocate buffer fo ext controls");
            goto end;
        }

        controls = (struct v4l2_ext_control *)mbuf;
        memcpy(mbuf, ext_ctls->controls, ext_ctls_size);
    }        

    memset(&vbuffer, 0, sizeof(vbuffer));
    for(cid_idx=0; cid_idx<ext_ctls->count; cid_idx++)
    {
        print_debug("cid_idx[%d], id[%d], value[0x%8x]", cid_idx, 
            controls[cid_idx].id - V4L2_CID_PRIVACY, controls[cid_idx].value);
        switch(controls[cid_idx].id)
        {
            //get buffer type: video or capture
            case V4L2_CID_BUFFER_TYPE:
            {                
                vbuffer.type = controls[cid_idx].value;
                break;
            }

            case V4L2_CID_BUFFER_INDEX:
            {                
                vbuffer.index = controls[cid_idx].value;
                break;
            }

            //get buffer length
            case V4L2_CID_BUFFER_LENGTH:
            {    
                vbuffer.length = controls[cid_idx].value;
                break;                
            }

            //get buffer offset
            case V4L2_CID_BUFFER_OFFSET:
            {
                vbuffer.m.offset = controls[cid_idx].value;
                break;
            }

            case V4L2_CID_FOCUS_AREA_INFO:
            {
                print_info("=====focus area info=====");
                break;
            }
            default:
            {
                print_error("%s, id=%#x, value=%#x", __FUNCTION__, 
                    controls[cid_idx].id, controls[cid_idx].value);
                break;
            }
        }    
        
    }

    if(vbuffer.type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
    {
        if(vbuffer.m.offset == 0)
        {
            cam->capture_nr = 0;
            INIT_LIST_HEAD(&cam->capture_ready_q);
        }
        else
        {
            cam->capture_nr++; 
            k3_fake_register_buffer(&(cam->buf_capture[vbuffer.index]), &vbuffer);
            INIT_LIST_HEAD(&(cam->buf_capture[vbuffer.index].queue));
        }
    }
    else if(vbuffer.type == V4L2_BUF_TYPE_VIDEO_OVERLAY)
    {
        if(vbuffer.m.offset == 0)
        {
            cam->preview_nr = 0;    
            INIT_LIST_HEAD(&cam->preview_ready_q);
        }
        else
        {
            cam->preview_nr++;
            k3_fake_register_buffer(&(cam->buf_preview[vbuffer.index]), &vbuffer);
            INIT_LIST_HEAD(&(cam->buf_preview[vbuffer.index].queue));
        }
    }
    else if(vbuffer.type == V4L2_BUF_TYPE_PRIVATE)
    {
        if(vbuffer.m.offset == 0)      
        {
            cam->ipp_nr = 0;           
            INIT_LIST_HEAD(&cam->ipp_ready_q);                                                                                                           
        }
        else
        {
            cam->ipp_nr++;
            k3_fake_register_buffer(&(cam->buf_ipp[vbuffer.index]), &vbuffer);
            INIT_LIST_HEAD(&(cam->buf_ipp[vbuffer.index].queue));                                                                                        
        }
    }

end:
    if (mbuf)
    {
        kfree(mbuf);
    }

    up(&cam->busy_lock);
    return ret;
    
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_g_fmt_private;
 * Description : for private work;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_g_fmt_private(struct file *file, void *fh, struct v4l2_format *fmt)
{
    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_fake_v4l2_ioctl_qbuf;
 * Description : Queue buffer into ready queue;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_ioctl_qbuf(struct file *file, void *fh, struct v4l2_buffer *b)
{
    unsigned long lock_flags    = 0;
    int idx                     = 0;
    int ret                     = 0;
    v4l2_ctl_struct *cam        = video_get_drvdata((struct video_device *)fh);

    print_debug("enter %s, index=%d", __FUNCTION__, b->index);

    switch (b->type)
    {
        case V4L2_BUF_TYPE_VIDEO_OVERLAY:
            {
                idx = b->index;
                /* queue buffer to ready queue */
                spin_lock_irqsave(&cam->queue_lock, lock_flags);
                add_to_ready_q(&(cam->buf_preview[idx]), &cam->preview_ready_q);
                spin_unlock_irqrestore(&cam->queue_lock, lock_flags);
 
                break;
            }
        case V4L2_BUF_TYPE_VIDEO_CAPTURE:
        case V4L2_BUF_TYPE_PRIVATE:
            {
                idx = b->index;

                /* queue buffer to ready queue */
                spin_lock_irqsave(&cam->queue_lock, lock_flags);
                add_to_ready_q(&(cam->buf_capture[idx]), &cam->capture_ready_q);
                spin_unlock_irqrestore(&cam->queue_lock, lock_flags);
                break;
            }
        default:
            {
                print_error("%s failed", __FUNCTION__);
                ret = -EINVAL;
                goto out;
            }
    }
    
out:
    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_dqbuf;
 * Description : Dequeue buffer from done queue.
 *               The calling process will be sleep until buffer is ready.
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int  color_index     = 0;
static char color_value[6]  = {0, 0x40, 0x70, 0xa0, 0xc0, 0xff};
static int k3_fake_v4l2_ioctl_dqbuf(struct file *file, void *fh, struct v4l2_buffer *b)
{
    v4l2_ctl_struct *cam        = video_get_drvdata((struct video_device *)fh);
    camera_frame_buf *frame     = NULL;
    unsigned long lock_flags    = 0;
    int time                    = 1000;

    print_debug("enter %s", __FUNCTION__);

    switch (b->type) {
    case V4L2_BUF_TYPE_VIDEO_OVERLAY:
        {
            if(!cam->preview_on)
            {
                print_debug("preview is stopped");
                break;
            }

            if(list_empty(&cam->preview_ready_q))
            {
                print_error("no preview buffers in ready_q");
                msleep(1000);
                return -ETIME;
            }

            frame = list_entry(cam->preview_ready_q.next, camera_frame_buf, queue);
            spin_lock_irqsave(&cam->queue_lock, lock_flags);
            del_from_ready_q(frame);
            spin_unlock_irqrestore(&cam->queue_lock, lock_flags);

            b->index     = frame->index;
            color_index  = frame->index;
            b->bytesused = cam->fmt_preview.fmt.pix.sizeimage;
            b->m.offset  = frame->phyaddr;
            if(frame->viraddr)
            {
                memset(frame->viraddr, color_value[b->index], cam->fmt_preview.fmt.pix.sizeimage);
            }
            time = 1000 * cam->frame_rate.numerator / cam->frame_rate.denominator;
            msleep(time*2);
            
            break;
        }
    case V4L2_BUF_TYPE_VIDEO_CAPTURE:
        {
            if(!cam->capture_on)
            {
                print_debug("capture is stopped");
                break;
            }

            if(list_empty(&cam->capture_ready_q))
            {
                print_error("no capture buffers in ready_q");
                msleep(1000);
                return -ETIME;
            }

            frame = list_entry(cam->capture_ready_q.next, camera_frame_buf, queue);
 
            spin_lock_irqsave(&cam->queue_lock, lock_flags);
            del_from_ready_q(frame);
            spin_unlock_irqrestore(&cam->queue_lock, lock_flags);

            b->index = frame->index;
            b->bytesused = cam->fmt_capture.fmt.pix.sizeimage;
            b->m.offset = frame->phyaddr;
            if(frame->viraddr)
            {
                memset(frame->viraddr, color_value[color_index], cam->fmt_capture.fmt.pix.sizeimage);
            }
            msleep(100);
            break;
        }
        default:
        {
            return -EINVAL;
        }
    }
    print_debug("exit %s, index=%d", __FUNCTION__, b->index);

    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_preview_on;
 * Description : Start preview:
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_preview_on(v4l2_ctl_struct *cam)
{
    int i = 0;

    print_info("enter %s", __FUNCTION__);

    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s get busy_lock fail", __FUNCTION__);
        return -EINTR;
    }
    
    cam->preview_pid    = current->pid;
    cam->preview_on     = 1;

    print_info("-------------------------------------------------------");    
    for(; i< cam->preview_nr; i++)
    {
        cam->buf_preview[i].viraddr = ioremap(cam->buf_preview[i].phyaddr, cam->fmt_preview.fmt.pix.sizeimage);
        print_info("buf_preview[%d].viraddr=%p, buf_preview[%d].phyaddr=%08x", i, cam->buf_preview[i].viraddr, i, cam->buf_preview[i].phyaddr);
    }
    print_info("-------------------------------------------------------");    

    up(&cam->busy_lock);

    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_capture_on;
 * Description : Start taking picture;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_capture_on ( v4l2_ctl_struct* cam )
{
    int i = 0;

    print_info("enter %s", __FUNCTION__);

    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s get busy_lock fail", __FUNCTION__);
        return -EINTR;
    }
    
    cam->capture_pid = current->pid;
    cam->capture_on  = 1;

    for(; i< cam->capture_nr; i++)
    {
        cam->buf_capture[i].viraddr = ioremap(cam->buf_capture[i].phyaddr, cam->fmt_capture.fmt.pix.sizeimage);
    }

    up(&cam->busy_lock);

    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_streamon;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_ioctl_streamon(struct file *file, void *fh, enum v4l2_buf_type buf_type)
{
    int ret                 = -EINVAL;
    v4l2_ctl_struct *cam    = video_get_drvdata((struct video_device *)fh);
    my_ctl                  = cam;
    
    print_debug("enter %s", __FUNCTION__);

    if (cam->capture_on || cam->preview_on)
    {
        print_error("%s, capture_on or preview_on is lost!", __FUNCTION__);
        return -EBUSY;
    }

    switch (buf_type)
    {
        case V4L2_BUF_TYPE_VIDEO_OVERLAY:
            {
                ret = k3_fake_v4l2_preview_on(cam);
                break;
            }
        case V4L2_BUF_TYPE_VIDEO_CAPTURE:
            {
                ret = k3_fake_v4l2_capture_on(cam);
                break;
            }
        default:
            {
                print_error("error : invalid parameters;  %s() exit",  __FUNCTION__);
                break;
            }
    }

    return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_streamoff;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_ioctl_streamoff(struct file *file, void *fh, enum v4l2_buf_type buf_type)
{
    v4l2_ctl_struct *cam    = video_get_drvdata((struct video_device *)fh);
    int ret                 = 0;

    print_debug("enter %s", __FUNCTION__);

    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s get busy_lock fail", __FUNCTION__);
        return -EINTR;
    }

    switch (buf_type)
    {
        case V4L2_BUF_TYPE_VIDEO_OVERLAY:
            {
                ret = k3_fake_v4l2_preview_off(cam);
                break;
            }
        case V4L2_BUF_TYPE_VIDEO_CAPTURE:
            {
                ret = k3_fake_v4l2_capture_off(cam);
                break;
            }
        default:
            {
                print_error("error : invalid parameters; %s() exit", __FUNCTION__);
                ret = -EINVAL;
                break;
            }
    }
    up(&cam->busy_lock);

    return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_fake_camera_enum_frame_intervals;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_camera_enum_frame_intervals(struct v4l2_frmivalenum *fi)
{
    WARN_ON(fi == NULL);
    
    print_debug("enter %s", __FUNCTION__);
    
    if (fi->index >=
        sizeof(fake_camera_frmivalenum) / sizeof(fake_camera_frmivalenum[0]))
    {
        print_debug("index = %d, sizeof(fake_camera_frmivalenum) = %d",
               fi->index, sizeof(fake_camera_frmivalenum));
        return -EINVAL;       
    }  

    fi->type                    = fake_camera_frmivalenum[fi->index].type;
    fi->discrete.numerator      = fake_camera_frmivalenum[fi->index].discrete.numerator;
    fi->discrete.denominator    = fake_camera_frmivalenum[fi->index].discrete.denominator;

    return 0;
     
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_s_param;
 * Description : Set parameters for isp and now we only use it to set frame rate.
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_ioctl_s_param(struct file *file, void *fh, struct v4l2_streamparm *a)
{
    struct v4l2_frmivalenum fi;
    v4l2_ctl_struct *cam = video_get_drvdata((struct video_device *)fh);

    print_debug("enter %s", __FUNCTION__);

    /* check frame interval */
    memset(&fi, 0x00, sizeof(fi));
    fi.type                 = V4L2_FRMIVAL_TYPE_DISCRETE;
    fi.discrete.denominator = a->parm.capture.timeperframe.denominator;
    fi.discrete.numerator   = a->parm.capture.timeperframe.numerator;

    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s get busy_lock fail", __FUNCTION__);
        return -EINTR;
    }
    
    cam->frame_rate = a->parm.capture.timeperframe;
    
    up(&cam->busy_lock);

    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_g_param;
 * Description : Get parameters of isp and now we only use it to get frame rate;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_ioctl_g_param(struct file *file, void *fh, struct v4l2_streamparm *a)
{
    v4l2_ctl_struct *cam = video_get_drvdata((struct video_device *)fh);

    print_debug("enter %s", __FUNCTION__);

    if (cam->capture_on || cam->preview_on)
    {
        return -EBUSY;
    }

    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s get busy_lock fail", __FUNCTION__);
        return -EINTR;
    }
    
    a->parm.capture.timeperframe = cam->frame_rate;
    
    up(&cam->busy_lock);

    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_fake_camera_enum_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_camera_enum_framesizes(struct v4l2_frmsizeenum *framesizes)
{
    WARN_ON(framesizes == NULL);
    
    print_debug("enter %s", __FUNCTION__,);

    if (framesizes->index >=
        sizeof(fake_camera_framesizes) / sizeof(fake_camera_framesizes[0]))
    {
        return -EINVAL;
    }

    framesizes->type            = fake_camera_framesizes[framesizes->index].type;
    framesizes->discrete.width  = fake_camera_framesizes[framesizes->index].discrete.width;
    framesizes->discrete.height = fake_camera_framesizes[framesizes->index].discrete.height;     

    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_enum_framesizes;
 * Description : enumerate all frame sizes that supported by isp and
 *               camera sensors;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_ioctl_enum_framesizes(struct file *file, void *fh, struct v4l2_frmsizeenum *fsize)
{
    v4l2_ctl_struct *cam    = NULL;
    int ret                 = 0;

    print_debug("enter %s", __FUNCTION__);

    if (!fh || !video_get_drvdata((struct video_device *)fh))
    {
        print_error("%s get video device fail", __FUNCTION__);
        return -EBADF;
    }
    
    cam = video_get_drvdata((struct video_device *)fh);

    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s get busy_lock fail", __FUNCTION__);
        return -EINTR;
    }
    
    ret = k3_fake_camera_enum_framesizes(fsize);
    
    up(&cam->busy_lock);

    return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_enum_frameintervals;
 * Description : enumerate all frame intervals that supported by camera sensors;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_ioctl_enum_frameintervals(struct file *file, void *fh, struct v4l2_frmivalenum *fival)
{
    int ret                 = 0;
    v4l2_ctl_struct *cam    = NULL;

    print_debug("enter %s", __FUNCTION__);

    if (!fh || !video_get_drvdata((struct video_device *)fh))
    {
        print_error("%s get video device fail", __FUNCTION__);
        return -EBADF;
    }
    
    cam = video_get_drvdata((struct video_device *)fh);

    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s get busy_lock fail", __FUNCTION__);
        return -EINTR;
    }
    
    ret = k3_fake_camera_enum_frame_intervals(fival);
    
    up(&cam->busy_lock);

    return ret;
}

/*
 *************************************************************************
 * FunctionName: k3_fake_camera_enum_capture_fmt;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_camera_enum_capture_fmt(struct v4l2_fmtdesc *f)
{
    if(f->index >= MAX_CAPTURE_FORMAT_NO || 0 == k3_fake_camera_support_preview_fmt[f->index])
    {
        return -EINVAL;
    }

    f->pixelformat = k3_fake_camera_support_capture_fmt[f->index];
    
    return 0;
}


/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_enum_fmt_capture;
 * Description : enumerate all picture data format that supported camera sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_ioctl_enum_fmt_capture(struct file *file, void *fh,
                          struct v4l2_fmtdesc *f)
{
    int ret                 = 0;
    v4l2_ctl_struct *cam    = NULL;

    print_debug("enter %s", __FUNCTION__);

    if (!fh || !video_get_drvdata((struct video_device *)fh))
    {
        print_error("%s get video device fail", __FUNCTION__);
        return -EBADF;
    }

    cam = video_get_drvdata((struct video_device *)fh);

    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s get busy_lock fail", __FUNCTION__);
        return -EINTR;
    }
    
    ret = k3_fake_camera_enum_capture_fmt(f);
    
    up(&cam->busy_lock);

    return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_fake_camera_enum_preview_fmt;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_camera_enum_preview_fmt(struct v4l2_fmtdesc *f)
{
    if(f->index >= MAX_PREVIEW_FORMAT_NO || 0 == k3_fake_camera_support_preview_fmt[f->index])
    {
        return -EINVAL;
    }

    f->pixelformat = k3_fake_camera_support_preview_fmt[f->index];
    
    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_enum_fmt_preview;
 * Description : enumerate all preview data format that supported camera sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_ioctl_enum_fmt_preview(struct file *file, void *fh, struct v4l2_fmtdesc *f)
{
    int ret                 = 0;
    v4l2_ctl_struct *cam    = NULL;

    print_debug("enter %s", __FUNCTION__);

    if (!fh || !video_get_drvdata((struct video_device *)fh))
    {
        print_error("%s get video device fail", __FUNCTION__);
        return -EBADF;
    }
    
    cam = video_get_drvdata((struct video_device *)fh);

    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s get busy_lock fail", __FUNCTION__);
        return -EINTR;
    }

    ret = k3_fake_camera_enum_preview_fmt(f);

    up(&cam->busy_lock);

    return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_open;
 * Description : Called by linux VFS when application call 'open':
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_open(struct file *file)
{
    int ret                     = 0;
    struct video_device *dev    = video_devdata(file);
    v4l2_ctl_struct *cam        = video_get_drvdata(dev);

    WARN_ON(dev == NULL);

    print_info("enter %s", __FUNCTION__);

    if (!cam)
    {
        print_error("%s, %d", __FUNCTION__, __LINE__);
        return -ENODEV;
    }

    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s get busy_lock fail", __FUNCTION__);
        return -EINTR;
    }

    if (0 == cam->open_count++)
    {
        cam->capture_on     = 0;
        cam->preview_on     = 0;
        cam->capture_pid    = 0;
        cam->preview_pid    = 0;
        cam->capture_nr     = 0;
        cam->preview_nr     = 0;
        memset(&cam->fmt_capture, 0x00, sizeof(cam->fmt_capture));
        memset(&cam->fmt_preview, 0x00, sizeof(cam->fmt_preview));
        memset(&cam->buf_capture, 0x00, sizeof(cam->buf_capture));
        memset(&cam->buf_preview, 0x00, sizeof(cam->buf_preview));
        memset(&cam->frame_rate,  0x00, sizeof(cam->frame_rate));

        INIT_LIST_HEAD(&cam->capture_ready_q);
        INIT_LIST_HEAD(&cam->preview_ready_q);

        k3_fake_set_default_capture_fmt(&cam->fmt_capture);
        k3_fake_set_default_preview_fmt(&cam->fmt_preview);
    }
    else
    {
        print_error("%s failed : camera already opened", __FUNCTION__);
    }

    file->private_data = dev;
    up(&cam->busy_lock);

    return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_fake_v4l2_close;
 * Description : Called by linux VFS when application call 'close':
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_close(struct file *file)
{
    struct video_device *dev    = (struct video_device *)file->private_data;
    v4l2_ctl_struct *cam        = NULL;

    print_info("enter %s", __FUNCTION__);

    if (!dev || !video_get_drvdata(dev))
    {
        print_error("%s get video device fail", __FUNCTION__);
        return -EBADF;
    }
    
    cam = video_get_drvdata(dev);

    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s, %d, wait busy_lock fail", __FUNCTION__, __LINE__);
        return -EINTR;
    }

    if (--cam->open_count <= 0)
    {
        cam->open_count = 0;

        /* add close operation here */
        if (cam->capture_on)
        {
            cam->capture_on = 0;
        }
        else if (cam->preview_on)
        {
            cam->preview_on = 0;
        }
    }

    up(&cam->busy_lock);
    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_mmap;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_mmap(struct file *file, struct vm_area_struct *vma)
{
    struct video_device *dev    = (struct video_device *)file->private_data;
    v4l2_ctl_struct *cam        = NULL;
    unsigned long size          = 0;
    int ret                     = 0;

    print_debug("enter %s", __FUNCTION__);

    if (!dev || !video_get_drvdata(dev))
    {
        print_error("%s get video device fail", __FUNCTION__);
        return -EBADF;
    }
    
    cam = video_get_drvdata(dev);

    if (down_interruptible(&cam->busy_lock))
    {
        print_error("%s get busy_lock fail", __FUNCTION__);
        return -EINTR;
    }
    
    size = vma->vm_end - vma->vm_start;
    vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
    if (remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff, size, vma->vm_page_prot))
    {
        print_error("%s, %d", __FUNCTION__, __LINE__);
        ret = -ENOBUFS;
    }
    else
    {
        vma->vm_flags &= ~VM_IO;
        ret = 0;
    }

    up(&cam->busy_lock);
    return 0;
}

/* v4l2 function table */
static const struct v4l2_ioctl_ops k3_fake_v4l2_ioctl_ops =
{
    .vidioc_s_fmt_vid_cap           = k3_fake_v4l2_ioctl_s_fmt_capture,
    .vidioc_g_fmt_vid_cap           = k3_fake_v4l2_ioctl_g_fmt_capture,
    .vidioc_s_fmt_vid_overlay       = k3_fake_v4l2_ioctl_s_fmt_preview,
    .vidioc_g_fmt_vid_overlay       = k3_fake_v4l2_ioctl_g_fmt_preview,
    .vidioc_g_fmt_type_private      = k3_v4l2_ioctl_g_fmt_private,
    .vidioc_g_ctrl                  = k3_fake_v4l2_ioctl_g_ctrl,
    .vidioc_s_ctrl                  = k3_fake_v4l2_ioctl_s_ctrl,
    .vidioc_qbuf                    = k3_fake_v4l2_ioctl_qbuf,
    .vidioc_streamon                = k3_fake_v4l2_ioctl_streamon,
    .vidioc_dqbuf                   = k3_fake_v4l2_ioctl_dqbuf,
    .vidioc_streamoff               = k3_fake_v4l2_ioctl_streamoff,
    .vidioc_s_parm                  = k3_fake_v4l2_ioctl_s_param,
    .vidioc_g_parm                  = k3_fake_v4l2_ioctl_g_param,
    .vidioc_enum_fmt_vid_cap        = k3_fake_v4l2_ioctl_enum_fmt_capture,
    .vidioc_enum_fmt_vid_overlay    = k3_fake_v4l2_ioctl_enum_fmt_preview,
    .vidioc_enum_framesizes         = k3_fake_v4l2_ioctl_enum_framesizes,
    .vidioc_enum_frameintervals     = k3_fake_v4l2_ioctl_enum_frameintervals,
    .vidioc_default                 = k3_fake_v4l2_ioctl_g_caps,
    .vidioc_g_ext_ctrls             = k3_fake_v4l2_ioctl_g_ext_ctrls,
    .vidioc_s_ext_ctrls             = k3_fake_v4l2_ioctl_s_ext_ctrls,
};

static struct v4l2_file_operations k3_fake_v4l2_fops = {
    .owner      = THIS_MODULE,
    .open       = k3_fake_v4l2_open,
    .release    = k3_fake_v4l2_close,
    .mmap       = k3_fake_v4l2_mmap,
    .ioctl      = video_ioctl2,
};

/* video device template */
static struct video_device k3_fake_v4l2_camera = {
    .name       = "hik3-fake-camera",
    .minor      = -1,
    .release    = video_device_release,
    .fops       = &k3_fake_v4l2_fops,
    .ioctl_ops  = &k3_fake_v4l2_ioctl_ops,
};

/*
 **************************************************************************
 * FunctionName: k3_init_v4l2_ctl;
 * Description : Set default value of v4l2_ctl_struct;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_init_v4l2_ctl(v4l2_ctl_struct *v4l2_ctl)
{
    print_debug("enter %s", __FUNCTION__);

    memset(v4l2_ctl, 0x00, sizeof(*v4l2_ctl));
    
    /* allocate a new video device and init it */
    v4l2_ctl->video_dev = video_device_alloc();
    if (!v4l2_ctl->video_dev)
    {
        print_error("fail to allocate video device !!");
        return -ENOMEM;
    }
    
    sema_init(&v4l2_ctl->busy_lock, 1);
    spin_lock_init(&v4l2_ctl->queue_lock);

    //memcpy(v4l2_ctl->video_dev, &k3_fake_v4l2_camera, sizeof(k3_fake_v4l2_camera));
    memcpy(v4l2_ctl->video_dev, &k3_fake_v4l2_camera, sizeof(struct video_device));

    video_set_drvdata(v4l2_ctl->video_dev, v4l2_ctl);
    dev_set_drvdata(&k3_fake_v4l2_camera.dev, (void *)v4l2_ctl);
    v4l2_ctl->video_dev->minor = -1;

    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_deinit_v4l2_ctl;
 * Description : Deinit v4l2_ctl_struct;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void k3_fake_deinit_v4l2_ctl(v4l2_ctl_struct *v4l2_ctl)
{
    print_debug("enter %s", __FUNCTION__);

    if (v4l2_ctl->video_dev)
    {
        video_device_release(v4l2_ctl->video_dev);
        v4l2_ctl->video_dev = NULL;
    }

    return;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_resume;
 * Description : Resume camera isp and sensor to work state;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_resume(struct platform_device *pdev)
{
    print_warn("enter %s +", __FUNCTION__);

    if (0 == v4l2_ctl.open_count)
    {
        /* power down all camera sensor */
    } else {
        print_error("BUG: should not be HERE !! [open_count=%d]", v4l2_ctl.open_count);
    }
    
    print_warn("exit %s -", __FUNCTION__);

    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_suspend;
 * Description : Suspend isp and camera sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_fake_v4l2_suspend(struct platform_device *pdev, pm_message_t state)
{
    print_warn("enter %s +", __FUNCTION__);
    
    if (0 != v4l2_ctl.open_count)
    {
        print_error("BUG: should NOT be here [open_count=%d]", v4l2_ctl.open_count);
    }
    print_info("Camera suspend successfully");
    
    print_warn("exit %s -", __FUNCTION__);
    
    return 0;
}

static struct platform_driver k3_fake_v4l2_driver =
{
    .probe      = NULL,
    .remove     = NULL,
    .suspend    = k3_fake_v4l2_suspend,
    .resume     = k3_fake_v4l2_resume,
    .shutdown   = NULL,
    .driver     = {
                      .name     = "hik3-fake-camera-v4l2",
                      .owner    = THIS_MODULE,
                      .bus      = &platform_bus_type,
                  },
};

/*
 **************************************************************************
 * FunctionName: camera_init;
 * Description : module init function:
 *               A. register platform device and driver.
 *               B. init v4l2_ctl struct.
 *               C. init video device to kernel.
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static __init int camera_init(void)
{
    int ret = 0;
    print_debug("\nHisilicon K3 fake camera v4l2 driver init\n\n");
    
    ret = platform_driver_register(&k3_fake_v4l2_driver);
    if (ret != 0)
    {
        print_error("fail to register platform driver !!");
    }

    /* init camera control struct */
    ret = k3_fake_init_v4l2_ctl(&v4l2_ctl);
    if (ret != 0)
    {
        print_error("fail to init camera control struct !!");
        return ret;
    }
    
    ret = video_register_device(v4l2_ctl.video_dev, VFL_TYPE_GRABBER, video_nr);
    if (ret != 0)
    {
        print_error("fail to register video device !!");
        k3_fake_deinit_v4l2_ctl(&v4l2_ctl);
        return ret;
    }
        
    print_info("Hisilicon K3 fake camera v4l2 driver init OK !!");

    return ret;
}

/*
 **************************************************************************
 * FunctionName: camera_exit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void __exit camera_exit(void)
{
    print_info("Hisilicon K3 fake camera v4l2 driver exit !!");

    if (v4l2_ctl.video_dev)
    {
        video_unregister_device(v4l2_ctl.video_dev);
        v4l2_ctl.video_dev = NULL;
    }
    
    k3_fake_deinit_v4l2_ctl(&v4l2_ctl);
    
    platform_driver_unregister(&k3_fake_v4l2_driver);

    return;
}

module_init(camera_init);
module_exit(camera_exit);
module_param(video_nr, int, 0444);

MODULE_AUTHOR("qKF23847");
MODULE_DESCRIPTION("V4L2 capture driver for Hisilicon K3 fake cameras");
MODULE_LICENSE("GPL");
MODULE_SUPPORTED_DEVICE("video");

/********************************** END **********************************************/
