


#include <linux/debugfs.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/videodev2.h>
#include <media/v4l2-dev.h>
#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-fh.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-core.h>

#include "hwcam_intf.h"
#include "cam_log.h"

typedef struct _tag_hwcam_dev
{
    struct v4l2_device                          v4l2;
    struct mutex                                lock;
    struct video_device*                        vdev;
    struct media_device*                        mdev;

    hwcam_dev_intf_t                            intf;
    hwcam_cfgpipeline_intf_t*                   pipeline;
} hwcam_dev_t;

typedef struct _tag_hwcam_user
{
	struct v4l2_fh                              eq;
    hwcam_dev_t*                                cam; 

    hwcam_user_intf_t                           intf;
    struct kref                                 ref;

    hwcam_cfgstream_intf_t*                     stream;

    struct vb2_queue                            vb2q;
    struct v4l2_format                          format;
    unsigned long                               f_format_valid : 1;
    unsigned long                               f_pipeline_owner : 1;
} hwcam_user_t;

#define VO2USER(fpd) container_of(fpd, hwcam_user_t, eq)

#define I2USER(i) container_of(i, hwcam_user_t, intf)

#define REF2USER(r) container_of(r, hwcam_user_t, ref)

static void
hwcam_user_release(
        struct kref* r)
{
    hwcam_user_t* user = REF2USER(r);
    if (NULL == user){
        HWCAM_CFG_ERR("REF2USER returns null. \n");
        return;
    }

    HWCAM_CFG_DEBUG("instance(0x%p)", &user->intf);

    vb2_queue_release(&user->vb2q);

    user->intf.vtbl = NULL;
    kzfree(user);
}

static struct vb2_ops s_qops_hwcam_vbuf;

static struct vb2_mem_ops s_mops_hwcam_vbuf;

static hwcam_user_vtbl_t s_vtbl_hwcam_user;

static hwcam_user_t*
hwcam_user_create_instance(
        hwcam_dev_t* cam)
{
	hwcam_user_t* user = NULL;

	if(!cam){
		goto exit_create_instance;
	}

	user = kzalloc(sizeof(hwcam_user_t), GFP_KERNEL);
	if (!user) {
		goto exit_create_instance;
    }

    user->cam = cam; 
    user->intf.vtbl = &s_vtbl_hwcam_user;
    kref_init(&user->ref);

    user->f_format_valid = 0;
    memset(&user->format, 0, sizeof(user->format));

    user->vb2q.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
    user->vb2q.ops = &s_qops_hwcam_vbuf;
    user->vb2q.mem_ops = &s_mops_hwcam_vbuf;
    user->vb2q.io_modes = VB2_USERPTR;
    user->vb2q.io_flags = 0;
    user->vb2q.buf_struct_size = sizeof(hwcam_vbuf_t);
    user->vb2q.drv_priv = user;
    user->vb2q.timestamp_type = V4L2_BUF_FLAG_TIMESTAMP_COPY;
    if (vb2_queue_init(&user->vb2q)) {
        HWCAM_CFG_ERR("failed to initialize v4l2 buffer queue. \n");
        kzfree(user); 
        user = NULL; 
        goto exit_create_instance; 
    }

    HWCAM_CFG_DEBUG("instance(0x%p)", &user->intf);

exit_create_instance: 
    return user;
}

static void
hwcam_user_get(
        hwcam_user_intf_t* intf)
{
    hwcam_user_t* user = I2USER(intf);
    kref_get(&user->ref);
}

static int
hwcam_user_put(
        hwcam_user_intf_t* intf)
{
    hwcam_user_t* user = I2USER(intf);
    return kref_put(&user->ref, hwcam_user_release);
}

static void
hwcam_user_wait_begin(
        hwcam_user_intf_t* intf)
{
    hwcam_user_t* user = I2USER(intf);
    mutex_unlock(&user->cam->lock);
}

static void
hwcam_user_wait_end(
        hwcam_user_intf_t* intf)
{
    hwcam_user_t* user = I2USER(intf);
    mutex_lock(&user->cam->lock);
}

static void
hwcam_user_notify(
        hwcam_user_intf_t* intf,
        struct v4l2_event* ev)
{
    hwcam_user_t* user = I2USER(intf);
    mutex_lock(&user->cam->lock);
    if (user->eq.vdev) {
        v4l2_event_queue_fh(&user->eq, ev);
    }
    mutex_unlock(&user->cam->lock);
}

static hwcam_user_vtbl_t
s_vtbl_hwcam_user =
{
    .get = hwcam_user_get,
    .put = hwcam_user_put,
    .wait_begin = hwcam_user_wait_begin,
    .wait_end = hwcam_user_wait_end,
    .notify = hwcam_user_notify,
};

static int
hwcam_user_vb2q_queue_setup(
        struct vb2_queue* q,
        const struct v4l2_format* fmt,
        unsigned int* num_buffers,
        unsigned int* num_planes,
        unsigned int sizes[],
        void* alloc_ctxs[])
{
    int i = 0;
	hwcam_user_t* user = NULL;
    if (NULL == q){
        HWCAM_CFG_ERR("input parameter q is null. \n");
        return -1;
    }
    user = q->drv_priv;
    *num_planes = user->format.fmt.pix_mp.num_planes;
    for (; i != user->format.fmt.pix_mp.num_planes; i++) {
        sizes[i] = user->format.fmt.pix_mp.plane_fmt[i].sizeimage;
        alloc_ctxs[i] = user;
    }

    return 0;
}

static void
hwcam_user_vb2q_wait_prepare(
        struct vb2_queue* q)
{
	hwcam_user_t* user = NULL;
    if (NULL == q){
        HWCAM_CFG_ERR("input parameter q is null. \n");
        return;
    }
    user = q->drv_priv;
    mutex_unlock(&user->cam->lock);
}

static void
hwcam_user_vb2q_wait_finish(
        struct vb2_queue* q)
{
	hwcam_user_t* user = NULL;
    if (NULL == q){
        HWCAM_CFG_ERR("input parameter q is null. \n");
        return;
    }
    user = q->drv_priv;
    mutex_lock(&user->cam->lock);
}

static int
hwcam_user_vb2q_start_streaming(
        struct vb2_queue *q,
        unsigned int count)
{
	hwcam_user_t* user = NULL;
    if (NULL == q){
        HWCAM_CFG_ERR("input parameter q is null. \n");
        return -1;
    }
    user = q->drv_priv;
    return user->stream
        ? hwcam_cfgstream_intf_start(user->stream)
        : -ENOENT;
}

static int
hwcam_user_vb2q_stop_streaming(
        struct vb2_queue *q)
{
	hwcam_user_t* user = NULL;
    if (NULL == q){
        HWCAM_CFG_ERR("input parameter q is null. \n");
        return -1;
    }
    user = q->drv_priv;
    return user->stream
        ? hwcam_cfgstream_intf_stop(user->stream)
        : -ENOENT;
}

static int
hwcam_user_vb2q_buf_init(
        struct vb2_buffer *vb)
{
    return 0;
}

static void
hwcam_user_vb2q_buf_cleanup(
        struct vb2_buffer *vb)
{
}

static void
hwcam_user_vb2q_buf_queue(
        struct vb2_buffer* vb)
{
    hwcam_user_t* user = vb->vb2_queue->drv_priv;
    hwcam_vbuf_t* buf = container_of(vb, hwcam_vbuf_t, buf);
    if (user->stream) {
        hwcam_cfgstream_intf_buf_queue(user->stream, buf);
    }
}

static struct vb2_ops
s_qops_hwcam_vbuf =
{
    .queue_setup = hwcam_user_vb2q_queue_setup,

	.wait_prepare = hwcam_user_vb2q_wait_prepare,
	.wait_finish = hwcam_user_vb2q_wait_finish,

    .start_streaming = hwcam_user_vb2q_start_streaming,
    .stop_streaming = hwcam_user_vb2q_stop_streaming,

	.buf_init = hwcam_user_vb2q_buf_init,
    .buf_cleanup = hwcam_user_vb2q_buf_cleanup,

    .buf_queue = hwcam_user_vb2q_buf_queue,
};

static void*
hwcam_user_vb2q_get_userptr(
        void* alloc_ctx,      //  hwcam_user_t*
        unsigned long vaddr,  //  fdIon
        unsigned long size,
        int write)
{
    return alloc_ctx;
}

static void
hwcam_user_vb2q_put_userptr(
        void* buf_priv)
{
}

static struct vb2_mem_ops
s_mops_hwcam_vbuf =
{
    .get_userptr = hwcam_user_vb2q_get_userptr,
    .put_userptr = hwcam_user_vb2q_put_userptr,
};

static int
hwcam_dev_vo_querycap(
        struct file* filep,
        void* fh,
        struct v4l2_capability* cap)
{
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);
    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }
    if (user->f_pipeline_owner) {
        return hwcam_cfgpipeline_intf_query_cap(
                cam->pipeline, &user->intf);
    }
    else {
        return -EINVAL;
    }
}

static int
hwcam_dev_vo_s_crop(
        struct file *filep,
        void* fh,
        const struct v4l2_crop* crop)
{
	int rc = 0;
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(filep->private_data);
    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

    HWCAM_CFG_INFO("TODO. \n");

    if (crop->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
    }

	return rc;
}

static int
hwcam_dev_vo_g_crop(
        struct file* filep,
        void* fh,
        struct v4l2_crop* crop)
{
	int rc = 0;
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);
    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

    HWCAM_CFG_INFO("TODO. \n");

	if (crop->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
	}

	return rc;
}

static int
hwcam_dev_vo_queryctrl(
        struct file* filep,
        void* fh,
        struct v4l2_queryctrl* ctrl)
{
	int rc = 0;
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);
    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

    HWCAM_CFG_INFO("TODO. \n");

	if (ctrl->type == V4L2_CTRL_TYPE_MENU) {
	}

	return rc;
}

static int
hwcam_dev_vo_g_ctrl(
        struct file* filep,
        void* fh,
        struct v4l2_control* ctrl)
{
	int rc = -EINVAL;
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);
    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

    switch (ctrl->id)
    {
    case HWCAM_V4L2_CID_PIPELINE_PARAM:
        if (user->f_pipeline_owner) {
            rc =  hwcam_cfgpipeline_intf_query_param(
                    cam->pipeline, &user->intf);
        }
        break;
    case HWCAM_V4L2_CID_STREAM_PARAM:
        if (user->stream) {
            rc = hwcam_cfgstream_intf_query_param(
                    user->stream);
        }
        break;
    default:
        HWCAM_CFG_ERR("invalid cid kind(%d)! \n", ctrl->id);
        break;
    }
	return rc;
}

static int
hwcam_dev_vo_s_ctrl(
        struct file* filep,
        void* fh,
        struct v4l2_control* ctrl)
{
	int rc = -EINVAL;
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

    switch (ctrl->id)
    {
    case HWCAM_V4L2_CID_PIPELINE_PARAM:
        if (user->f_pipeline_owner) {
            rc =  hwcam_cfgpipeline_intf_change_param(
                    cam->pipeline, &user->intf);
        }
        break;
    case HWCAM_V4L2_CID_STREAM_PARAM:
        if (user->stream) {
            rc = hwcam_cfgstream_intf_change_param(
                    user->stream);
        }
        break;
    default:
        HWCAM_CFG_ERR("invalid cid kind(%d)! \n", ctrl->id);
        break;
    }
	return rc;
}

static int
hwcam_dev_vo_reqbufs(
        struct file* filep,
        void* fh,
        struct v4l2_requestbuffers* req)
{
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

    return vb2_reqbufs(&user->vb2q, req);
}

static int
hwcam_dev_vo_querybuf(
        struct file* filep,
        void* fh,
        struct v4l2_buffer* pb)
{
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

    return vb2_querybuf(&user->vb2q, pb);
}

static int
hwcam_dev_vo_qbuf(
        struct file* filep,
        void* fh,
        struct v4l2_buffer* pb)
{
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

    return vb2_qbuf(&user->vb2q, pb);
}

static int
hwcam_dev_vo_dqbuf(
        struct file* filep,
        void* fh,
        struct v4l2_buffer* pb)
{
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

    return vb2_dqbuf(&user->vb2q, pb,
            filep->f_flags & O_NONBLOCK);
}

static int
hwcam_dev_vo_streamon(
        struct file* filep,
        void* fh,
        enum v4l2_buf_type buf_type)
{
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

    return vb2_streamon(&user->vb2q, buf_type);
}

static int
hwcam_dev_vo_streamoff(
        struct file* filep,
        void* fh,
        enum v4l2_buf_type buf_type)
{
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

    return vb2_streamoff(&user->vb2q, buf_type);
}

static int
hwcam_dev_vo_enum_fmt_vid_cap(
        struct file* filep,
        void* fh,
        struct v4l2_fmtdesc* f)
{
	int rc = -EINVAL;
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

    return rc;
}

static int
hwcam_dev_vo_g_fmt_vid_cap(
        struct file* filep,
        void* fh,
        struct v4l2_format* pfmt)
{
	int rc = -EINVAL;
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

	if (pfmt->type == V4L2_BUF_TYPE_VIDEO_CAPTURE
            && user->stream && user->f_format_valid) {
        *pfmt = user->format;
        rc = 0;
	}
	return rc;
}

static int
hwcam_dev_vo_s_fmt_vid_cap(
        struct file* filep,
        void* fh,
        struct v4l2_format* pfmt)
{
	int rc = -EINVAL;
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

	if (pfmt->type == V4L2_BUF_TYPE_VIDEO_CAPTURE
            && user->stream) {
        rc = hwcam_cfgstream_intf_try_fmt(
                user->stream, pfmt);
        if (rc == 0) {
            user->format = *pfmt;
            user->f_format_valid = 1;
        }
	}
	return rc;
}

static int
hwcam_dev_vo_try_fmt_vid_cap(
        struct file *filep,
        void *fh,
        struct v4l2_format *pfmt)
{
	int rc = 0;
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

	if (pfmt->type == V4L2_BUF_TYPE_VIDEO_CAPTURE
            && user->stream) {
        rc = hwcam_cfgstream_intf_try_fmt(user->stream, pfmt);
	}
	return rc;
}

static int
hwcam_dev_vo_enum_fmt_vid_out_mplane(
        struct file* filep,
        void* fh,
        struct v4l2_fmtdesc* f)
{
	int rc = -EINVAL;
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }
    return rc;
}

static int
hwcam_dev_vo_g_fmt_vid_out_mplane(
        struct file* filep,
        void* fh,
        struct v4l2_format* pfmt)
{
	int rc = -EINVAL;
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }
	if (pfmt->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE
            && user->stream) {
        *pfmt = user->format;
        rc = 0;
	}
	return rc;
}

static int
hwcam_dev_vo_s_fmt_vid_out_mplane(
        struct file* filep,
        void* fh,
        struct v4l2_format* pfmt)
{
	int rc = -EINVAL;
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

	if (pfmt->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE
            && user->stream) {
        rc = hwcam_cfgstream_intf_try_fmt(user->stream, pfmt);
        if (rc == 0) {
            user->format = *pfmt;
            user->f_format_valid = 1;
        }
	}
	return rc;
}

static int
hwcam_dev_vo_try_fmt_vid_out_mplane(
        struct file *filep,
        void *fh,
        struct v4l2_format *pfmt)
{
	int rc = 0;
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

	if (pfmt->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE
            && user->stream) {
        rc = hwcam_cfgstream_intf_try_fmt(user->stream, pfmt);
	}
	return rc;
}

static int
hwcam_dev_vo_g_parm(
        struct file* filep,
        void *fh,
        struct v4l2_streamparm* a)
{
	int rc = 0;
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

    HWCAM_CFG_INFO("TODO. \n");

	return rc;
}

static int
hwcam_dev_vo_s_parm(
        struct file *filep,
        void *fh,
        struct v4l2_streamparm *parm)
{
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(fh);
    hwcam_stream_info_t* info = (hwcam_stream_info_t*)parm->parm.raw_data;

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

    if (cam->pipeline && !user->stream) {
        user->stream = hwcam_cfgpipeline_intf_mount_stream(
                cam->pipeline, &user->intf, info);
    }

    if (user->stream) {
        return 0;
    }
#if 0  //dead code
    else {
        HWCAM_CFG_ERR("failed to install stream! \n");
        return -ENOMEM;
    }
#else
	return 0;
#endif
}

static int
hwcam_dev_vo_subscribe_event(
        struct v4l2_fh* fh,
        const struct v4l2_event_subscription* sub)
{
	return v4l2_event_subscribe(fh, sub, 4,NULL);
}

static int
hwcam_dev_vo_unsubscribe_event(
        struct v4l2_fh* fh,
        const struct v4l2_event_subscription* sub)
{
	return v4l2_event_unsubscribe(fh, sub);
}

static long
hwcam_dev_vo_mount_buf(
        hwcam_dev_t* cam,
        hwcam_user_t* user,
        void* arg)
{
    long rc = -EINVAL;
    hwcam_buf_info_t* bi = arg;
    switch (bi->kind)
    {
    case HWCAM_BUF_KIND_PIPELINE_CAPABILITY:
    case HWCAM_BUF_KIND_PIPELINE_PARAM:
        if (user->f_pipeline_owner) {
            rc = hwcam_cfgpipeline_intf_mount_buf(
                    cam->pipeline, &user->intf, bi);
        }
        break;
    case HWCAM_BUF_KIND_STREAM_PARAM:
    case HWCAM_BUF_KIND_STREAM:
        if (user->stream) {
            rc = hwcam_cfgstream_intf_mount_buf(
                    user->stream, bi);
        }
        break;
    default:
        HWCAM_CFG_ERR("invalid buffer kind(%d)! \n", bi->kind);
        break;
    }
    return rc;
}

static long
hwcam_dev_vo_unmount_buf(
        hwcam_dev_t* cam,
        hwcam_user_t* user,
        void* arg)
{
    long rc = -EINVAL;
    hwcam_buf_info_t* bi = arg;
    switch (bi->kind)
    {
    case HWCAM_BUF_KIND_PIPELINE_CAPABILITY:
    case HWCAM_BUF_KIND_PIPELINE_PARAM:
        if (user->f_pipeline_owner) {
            rc = hwcam_cfgpipeline_intf_unmount_buf(
                    cam->pipeline, &user->intf, bi);
        }
        break;
    case HWCAM_BUF_KIND_STREAM_PARAM:
    case HWCAM_BUF_KIND_STREAM:
        if (user->stream) {
            rc = hwcam_cfgstream_intf_unmount_buf(
                    user->stream, bi);
        }
        break;
    default:
        HWCAM_CFG_ERR("invalid buffer kind(%d)! \n", bi->kind);
        break;
    }
    return rc;
}

static long
hwcam_dev_vo_ioctl_default(
        struct file* file,
        void* fh,
        bool valid_prio,
        unsigned int cmd,
        void* arg)
{
    long rc = -EINVAL;
    hwcam_dev_t* cam = video_drvdata(file);
	hwcam_user_t* user = VO2USER(fh);

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

    switch (cmd)
    {
    case HWCAM_V4L2_IOCTL_MOUNT_BUF:
        rc = hwcam_dev_vo_mount_buf(cam, user, arg);
        break;
    case HWCAM_V4L2_IOCTL_UNMOUNT_BUF:
        rc = hwcam_dev_vo_unmount_buf(cam, user, arg);
        break;
    case HWCAM_V4L2_IOCTL_MOUNT_GRAPHIC_BUF:
        if (user->stream) {
            rc = hwcam_cfgstream_intf_mount_graphic_buf(
                    user->stream, arg);
        }
        break;
    case HWCAM_V4L2_IOCTL_UNMOUNT_GRAPHIC_BUF:
        if (user->stream) {
            rc = hwcam_cfgstream_intf_unmount_graphic_buf(
                    user->stream, *((int*)arg));
        }
        break;
    default:
        HWCAM_CFG_ERR("invalid IOCTL CMD(%d)! \n", cmd);
        break;
    }
    return rc;
}

static const struct v4l2_ioctl_ops
s_iops_hwcam_dev =
{
	.vidioc_querycap = hwcam_dev_vo_querycap,

	.vidioc_s_crop = hwcam_dev_vo_s_crop,
	.vidioc_g_crop = hwcam_dev_vo_g_crop,

	.vidioc_queryctrl = hwcam_dev_vo_queryctrl,
	.vidioc_g_ctrl = hwcam_dev_vo_g_ctrl,
	.vidioc_s_ctrl = hwcam_dev_vo_s_ctrl,

    .vidioc_enum_fmt_vid_cap = hwcam_dev_vo_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap = hwcam_dev_vo_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = hwcam_dev_vo_s_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap = hwcam_dev_vo_try_fmt_vid_cap,

    .vidioc_enum_fmt_vid_out_mplane = hwcam_dev_vo_enum_fmt_vid_out_mplane,
	.vidioc_g_fmt_vid_out_mplane = hwcam_dev_vo_g_fmt_vid_out_mplane,
	.vidioc_s_fmt_vid_out_mplane = hwcam_dev_vo_s_fmt_vid_out_mplane,
	.vidioc_try_fmt_vid_out_mplane = hwcam_dev_vo_try_fmt_vid_out_mplane,

	.vidioc_g_parm = hwcam_dev_vo_g_parm,
	.vidioc_s_parm = hwcam_dev_vo_s_parm,

	.vidioc_subscribe_event = hwcam_dev_vo_subscribe_event,
	.vidioc_unsubscribe_event = hwcam_dev_vo_unsubscribe_event,

	.vidioc_reqbufs = hwcam_dev_vo_reqbufs,
	.vidioc_querybuf = hwcam_dev_vo_querybuf,
	.vidioc_qbuf = hwcam_dev_vo_qbuf,
	.vidioc_dqbuf = hwcam_dev_vo_dqbuf,

	.vidioc_streamon = hwcam_dev_vo_streamon,
	.vidioc_streamoff = hwcam_dev_vo_streamoff,

    .vidioc_default = hwcam_dev_vo_ioctl_default,
};

static unsigned int
hwcam_dev_vo_poll(
        struct file* filep,
        struct poll_table_struct* wait)
{
	unsigned int rc = 0;
    hwcam_dev_t* cam = video_drvdata(filep);
	hwcam_user_t* user = VO2USER(filep->private_data);

    if (!cam || !user) {
        HWCAM_CFG_ERR("%s(%d): cam or user is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

    if (user->f_format_valid) {
        rc = vb2_poll(&user->vb2q, filep, wait);
        rc &= ~POLLERR;
    }
    poll_wait(filep, &user->eq.wait, wait);
    if (v4l2_event_pending(&user->eq)) {
        rc |= POLLPRI | POLLOUT | POLLIN;
    }

	return rc;
}

static int
hwcam_dev_vo_close(
        struct file* filep)
{
    hwcam_dev_t* cam = NULL;
    struct v4l2_fh* eq = NULL;

    cam = (hwcam_dev_t*)video_drvdata(filep);
    swap(filep->private_data, eq);

    if (!cam || !eq) {
        HWCAM_CFG_ERR("%s(%d): cam or eq is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

	if (eq) {
        hwcam_cfgstream_intf_t* stm = NULL;
        hwcam_user_t* user = VO2USER(eq);

        swap(user->stream, stm);

        if (stm) {
            hwcam_cfgstream_intf_umount(stm);
            hwcam_cfgstream_intf_put(stm);
        }

        if (v4l2_fh_is_singular(eq)) {
            hwcam_cfgpipeline_intf_t* pl = NULL;
            swap(cam->pipeline, pl);
            if (pl) {
                hwcam_cfgpipeline_intf_umount(pl);
                hwcam_cfgpipeline_intf_put(pl);
            }
        }

        v4l2_fh_del(eq);
        v4l2_fh_exit(eq);

        hwcam_user_intf_put(&user->intf);

        HWCAM_CFG_INFO("instance(0x%p, /dev/video%d)", 
                user, cam->vdev->num);
	}

	return 0;
}

static int
hwcam_dev_vo_open(
        struct file* filep)
{
    long rc = 0;
    hwcam_dev_t* cam = NULL;
    hwcam_user_t* user = NULL;

    cam = (hwcam_dev_t*)video_drvdata(filep);
    user = hwcam_user_create_instance(cam);
    if (!user) {
        HWCAM_CFG_ERR("failed to failed to create instance! \n");
        rc = -ENOMEM;
        goto open_end;
    }

    if (!cam->pipeline) {
        hwcam_cfgpipeline_intf_t* pl = NULL;
        int ret = hwcam_cfgdev_mount_pipeline(
                NULL, &cam->intf, cam->vdev->num, &pl);
        if (pl) {
            if (!cam->pipeline) {
                cam->pipeline = pl;
            }
            else {
                hwcam_cfgpipeline_intf_put(pl);
            }
            if (!ret) {
                user->f_pipeline_owner = 1;
            }
        }
        if(ret != 0) {
            HWCAM_CFG_ERR("failed to install pipeline! \n");
            rc = -ENOENT;
            goto fail_to_mount_pipeline;
        }
    }

    if (!cam->pipeline) {
        HWCAM_CFG_ERR("failed to install pipeline! \n");
        rc = -ENOENT;
        goto fail_to_mount_pipeline;
    }

	v4l2_fh_init(&user->eq, cam->vdev);
	v4l2_fh_add(&user->eq);
    filep->private_data = &user->eq;

    HWCAM_CFG_INFO("instance(0x%p, /dev/video%d)", 
            user, cam->vdev->num);

    goto open_end;

fail_to_mount_pipeline:
    hwcam_user_intf_put(&user->intf);

open_end:
    return rc;
}

static struct v4l2_file_operations
s_fops_hwcam_dev =
{
	.owner = THIS_MODULE,
	.open	 = hwcam_dev_vo_open,
	.poll	 = hwcam_dev_vo_poll,
	.release = hwcam_dev_vo_close,
	.unlocked_ioctl = video_ioctl2,
#ifdef CONFIG_COMPAT
	.compat_ioctl32 = video_ioctl2,
#endif
};

#define I2DEV(i) container_of(i, hwcam_dev_t, intf)

static void
hwcam_dev_notify(
        hwcam_dev_intf_t* intf,
        struct v4l2_event* ev)
{
    hwcam_dev_t* cam = I2DEV(intf);
    v4l2_event_queue(cam->vdev, ev);
}

static hwcam_dev_vtbl_t
s_vtbl_hwcam_dev =
{
    .notify = hwcam_dev_notify,
};

int hwsensor_notify(struct device* pdev,struct v4l2_event* ev)
{
    struct v4l2_device* pv4l2 = NULL;
    hwcam_dev_t* pcam;
    if(pdev){
        pv4l2 = (struct v4l2_device*)dev_get_drvdata(pdev);
    }
    else{
        HWCAM_CFG_ERR("NULL pointer!");
        return -1;
    }
    if(pv4l2){
        pcam = container_of(pv4l2,hwcam_dev_t,v4l2);
    }
    else{
        HWCAM_CFG_ERR("fail to get hwcam_dev_t,fail to send notify");
        return -1;
    }
    if(pcam){
        pcam->intf.vtbl->notify(&pcam->intf,ev);
    }
    return 0;
}

int
hwcam_dev_create(
        struct device* dev,
        int* dev_num)
{
	int rc = 0;
    struct v4l2_device* v4l2 = NULL;
    struct video_device* vdev = NULL;
    struct media_device* mdev = NULL;
    hwcam_dev_t* cam = NULL;

    cam = kzalloc(sizeof(hwcam_dev_t), GFP_KERNEL);
	if (!cam) {
		rc = -ENOMEM;
		goto init_end;
	}
    v4l2 = &cam->v4l2;

    vdev = video_device_alloc();
    if (!vdev) {
		rc = -ENOMEM;
		goto video_alloc_fail;
    }

    mdev = kzalloc(sizeof(struct media_device), GFP_KERNEL);
	if (!mdev) {
		rc = -ENOMEM;
		goto media_alloc_fail;
	}

	strlcpy(mdev->model, HWCAM_MODEL_USER, sizeof(mdev->model));
	mdev->dev = dev;
	rc = media_device_register(mdev);
	if (rc < 0) {
		goto media_register_fail;
    }

	rc = media_entity_init(&vdev->entity, 0, NULL, 0);
	if (rc < 0) {
		goto entity_init_fail;
    }

    v4l2->mdev = mdev;
	v4l2->notify = NULL;
	rc = v4l2_device_register(dev, v4l2);
	if (rc < 0) {
		goto v4l2_register_fail;
    }

	strlcpy(vdev->name, "hwcam-userdev", sizeof(vdev->name));
	vdev->entity.type = MEDIA_ENT_T_DEVNODE_V4L;
	vdev->entity.group_id = HWCAM_DEVICE_GROUP_ID;
	vdev->v4l2_dev = v4l2;
	vdev->release = video_device_release;
	vdev->fops = &s_fops_hwcam_dev;
	vdev->ioctl_ops = &s_iops_hwcam_dev;
	vdev->minor = -1;
	vdev->vfl_type = VFL_TYPE_GRABBER;
	vdev->vfl_dir = VFL_DIR_TX;
    rc = video_register_device(vdev, VFL_TYPE_GRABBER, -1);
	if (rc < 0) {
		goto video_register_fail;
    }
	cam_debug("video dev name %s %s",vdev->dev.kobj.name,vdev->name);
    mutex_init(&cam->lock);
    vdev->lock = &cam->lock;
	vdev->entity.name = video_device_node_name(vdev);
	video_set_drvdata(vdev, cam);
    cam->vdev = vdev;
    cam->mdev = mdev;
    cam->intf.vtbl = &s_vtbl_hwcam_dev;
    *dev_num = vdev->num;

	goto init_end;

video_register_fail:
	v4l2_device_unregister(v4l2);

v4l2_register_fail:
	media_entity_cleanup(&vdev->entity);

entity_init_fail:
	media_device_unregister(mdev);

media_register_fail:
    kzfree(mdev);

media_alloc_fail:
	video_device_release(vdev);

video_alloc_fail:
	kzfree(cam);

init_end:
	return rc;
}

