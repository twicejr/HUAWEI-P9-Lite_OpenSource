


#include <linux/anon_inodes.h>
#include <linux/dma-buf.h>
#include <linux/debugfs.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/syscalls.h>
#include <linux/videodev2.h>
#include <media/v4l2-event.h>
#include <media/v4l2-fh.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-core.h>

#include "hwcam_intf.h"
#include "hwcam_compat32.h"

#define HWCAM_CFGSTREAM_MAX                     16      //  no more than 16 streams

typedef struct _tag_hwcam_cfgstream_mount_req
{
    struct mutex                                lock; 
    struct kref                                 ref;
    hwcam_cfgreq_intf_t                         intf; 

    struct video_device*                        vdev; 

    struct list_head*                           streams; 
    hwcam_cfgpipeline_intf_t*                   pl; 
    hwcam_user_intf_t*                          user; 
    hwcam_stream_info_t*                        info; 
    struct dma_buf*                             buf; 

    hwcam_cfgstream_intf_t*                     stream; 
} hwcam_cfgstream_mount_req_t; 

static void
hwcam_cfgstream_mount_req_release(
        struct kref* r); 

#define I2MSR(i) container_of(i, hwcam_cfgstream_mount_req_t, intf)

#define REF2MSR(r) container_of(r, hwcam_cfgstream_mount_req_t, ref)

typedef struct _tag_hwcam_cfgstream
{
	struct v4l2_fh                              rq;

    hwcam_cfgstream_intf_t                      intf;
    struct kref                                 ref;
	struct list_head	                        node;

    hwcam_cfgpipeline_intf_t*                   pipeline;
    hwcam_user_intf_t*                          user;
    hwcam_cfgreq_intf_t*                        cfgreq;

    struct list_head                            bufq_idle;
    struct list_head                            bufq_busy;
    spinlock_t                                  lock_bufq;
} hwcam_cfgstream_t;

#define I2STM(i) container_of(i, hwcam_cfgstream_t, intf)

#define REF2STM(r) container_of(r, hwcam_cfgstream_t, ref)

static void
hwcam_cfgstream_release(
        struct kref* r)
{
    hwcam_cfgstream_t* stm = REF2STM(r);
    hwcam_user_intf_t* user = NULL;
    hwcam_cfgpipeline_intf_t* pipeline = NULL;

    HWCAM_CFG_DEBUG("instance(0x%p)", &stm->intf);

    swap(user, stm->user);
    swap(pipeline, stm->pipeline);

    if (user) {
        hwcam_user_intf_put(user);
    }

    if (pipeline) {
        hwcam_cfgpipeline_intf_put(pipeline);
    }

    stm->intf.vtbl = NULL;
    kzfree(stm);
}

static hwcam_cfgstream_vtbl_t s_vtbl_cfgstream;

static hwcam_cfgstream_t*
hwcam_cfgstream_create_instance(
        hwcam_cfgstream_mount_req_t* req)
{
    hwcam_cfgstream_t* stm = kzalloc(
            sizeof(hwcam_cfgstream_t), GFP_KERNEL);
    if (stm == NULL) {
        return NULL;
    }
    stm->intf.vtbl = &s_vtbl_cfgstream;
    kref_init(&stm->ref);

    stm->pipeline = req->pl;
    hwcam_cfgpipeline_intf_get(stm->pipeline);
    stm->user = req->user;
    hwcam_user_intf_get(stm->user);

    INIT_LIST_HEAD(&stm->bufq_idle);
    INIT_LIST_HEAD(&stm->bufq_busy);
    spin_lock_init(&stm->lock_bufq);

    HWCAM_CFG_DEBUG("instance(0x%p)", &stm->intf);

    return stm;
}

static void
hwcam_cfgstream_get(
        hwcam_cfgstream_intf_t* intf)
{
    hwcam_cfgstream_t* stm = I2STM(intf);
    kref_get(&stm->ref);
}

static int
hwcam_cfgstream_put(
        hwcam_cfgstream_intf_t* intf)
{
    hwcam_cfgstream_t* stm = I2STM(intf);
    return kref_put(&stm->ref, hwcam_cfgstream_release);
}

static int
hwcam_cfgstream_umount(
        hwcam_cfgstream_intf_t* intf)
{
    hwcam_cfgstream_t* stm = I2STM(intf);
    struct v4l2_event ev =
    {
        .type = HWCAM_V4L2_EVENT_TYPE,
        .id = HWCAM_CFGSTREAM_REQUEST,
    };
    hwcam_cfgreq2stream_t* req = (hwcam_cfgreq2stream_t*)ev.u.data;

    req->req.intf = NULL;
    req->kind = HWCAM_CFGSTREAM_REQ_UNMOUNT;

    hwcam_cfgdev_lock();
    if (!list_empty(&stm->node)) {
        list_del_init(&stm->node);
        hwcam_cfgstream_intf_put(&stm->intf);
    }
    hwcam_cfgdev_unlock();

    return hwcam_cfgdev_send_req(stm->user, &ev, &stm->rq, 1, NULL);
}

typedef struct _tag_hwcam_cfgstream_fmt_req
{
    struct mutex                                lock; 
    struct kref                                 ref;
    hwcam_cfgreq_intf_t                         intf;
    unsigned                                    canceled : 1; 
    unsigned                                    finished : 1; 

    hwcam_cfgstream_t*                          stm;
    struct v4l2_format*                         fmt;
} hwcam_cfgstream_fmt_req_t;

#define I2SFR(i) container_of(i, hwcam_cfgstream_fmt_req_t, intf)

#define REF2SFR(r) container_of(r, hwcam_cfgstream_fmt_req_t, ref)

static void
hwcam_cfgstream_fmt_req_release(
        struct kref* r); 

static void 
hwcam_cfgstream_fmt_req_get(
        hwcam_cfgreq_intf_t* pintf)
{
    hwcam_cfgstream_fmt_req_t* sfr = I2SFR(pintf);
    kref_get(&sfr->ref);
}

static int 
hwcam_cfgstream_fmt_req_put(
        hwcam_cfgreq_intf_t* pintf)
{
    hwcam_cfgstream_fmt_req_t* sfr = I2SFR(pintf);
    return kref_put(&sfr->ref, hwcam_cfgstream_fmt_req_release);
}

static int
hwcam_cfgstream_fmt_req_on_req(
        hwcam_cfgreq_intf_t* pintf,
        struct v4l2_event* ev)
{
    int rc = 0; 
    hwcam_cfgstream_fmt_req_t* sfr = I2SFR(pintf);
    mutex_lock(&sfr->lock); 

    if (sfr->canceled) {
        rc = -EINVAL; 
        goto exit_on_req; 
    }

    sfr->finished = 1; 
    rc = 0; 

exit_on_req: 
    mutex_unlock(&sfr->lock); 
    return rc;
}

static int
hwcam_cfgstream_fmt_req_on_cancel(
        hwcam_cfgreq_intf_t* pintf, 
        int reason)
{
    hwcam_cfgstream_fmt_req_t* sfr = I2SFR(pintf);
    int rc = 0; 

    mutex_lock(&sfr->lock); 

    if (sfr->finished || sfr->canceled) {
        goto exit_on_canceled; 
    }

    sfr->canceled = 1; 
    rc = reason; 

exit_on_canceled:
    mutex_unlock(&sfr->lock); 
    return rc;
}

static int
hwcam_cfgstream_fmt_req_on_ack(
        hwcam_cfgreq_intf_t* pintf,
        hwcam_cfgack_t* ack)
{
    hwcam_cfgstream_fmt_req_t* sfr = I2SFR(pintf);

    mutex_lock(&sfr->lock); 
    if (hwcam_cfgack_result(ack)) {
        HWCAM_CFG_ERR("request(0x%p) failed! \n", pintf);
    }
    mutex_unlock(&sfr->lock); 
    return 0;
}

static hwcam_cfgreq_vtbl_t
s_vtbl_req_fmt =
{
    .get = hwcam_cfgstream_fmt_req_get, 
    .put = hwcam_cfgstream_fmt_req_put, 
    .on_req = hwcam_cfgstream_fmt_req_on_req,
    .on_cancel = hwcam_cfgstream_fmt_req_on_cancel,
    .on_ack = hwcam_cfgstream_fmt_req_on_ack,
};

static int
hwcam_cfgstream_fmt_req_create_instance(
        hwcam_cfgstream_t* stm, 
        struct v4l2_format* fmt, 
        hwcam_cfgstream_fmt_req_t** req)
{
    int rc = 0;
    hwcam_cfgstream_fmt_req_t* sfr = kzalloc(
            sizeof(hwcam_cfgstream_fmt_req_t), GFP_KERNEL);
    *req = NULL; 

    if (!sfr) {
        HWCAM_CFG_ERR("out of memory! \n");
        rc = -ENOMEM; 
        goto exit_create_instance;
    }

    mutex_init(&sfr->lock);
    kref_init(&sfr->ref);
    sfr->intf.vtbl = &s_vtbl_req_fmt;
    sfr->canceled = 0; 
    sfr->finished = 0; 

    sfr->stm = stm; 
    sfr->fmt = fmt; 

    *req = sfr; 

exit_create_instance: 
    return rc;
}

static void
hwcam_cfgstream_fmt_req_release(
        struct kref* r)
{
    hwcam_cfgstream_fmt_req_t* sfr = REF2SFR(r) ; 

    hwcam_cfgstream_fmt_req_on_cancel(&sfr->intf, -ENOENT);

    kzfree(sfr);
}

static inline int
hwcam_cfgstream_try_fmt(
    hwcam_cfgstream_intf_t* intf,
    struct v4l2_format* fmt)
{
    hwcam_cfgstream_t* stm = I2STM(intf);
    int rc = 0;
    int ack = 0;
    struct v4l2_event ev =
    {
        .type = HWCAM_V4L2_EVENT_TYPE,
        .id = HWCAM_CFGSTREAM_REQUEST,
    };
    hwcam_cfgreq2stream_t* req = (hwcam_cfgreq2stream_t*)ev.u.data;
    hwcam_cfgstream_fmt_req_t* sfr = NULL; 

    rc = hwcam_cfgstream_fmt_req_create_instance(stm, fmt, &sfr);
    if (!sfr) {
        goto exit_try_fmt; 
    }

    req->req.intf = &sfr->intf;
    req->kind = HWCAM_CFGSTREAM_REQ_TRY_FMT;

    rc = hwcam_cfgdev_send_req(stm->user, &ev, &stm->rq, 0, &ack);

    hwcam_cfgreq_intf_put(&sfr->intf); 

exit_try_fmt: 
    return rc? rc: ack;
}

typedef struct _tag_hwcam_cfgstream_mount_buf_req
{
    struct mutex                                lock; 
    struct kref                                 ref;
    hwcam_cfgreq_intf_t                         intf;

    struct dma_buf*                             buf;
} hwcam_cfgstream_mount_buf_req_t;

#define I2SMBR(i) container_of(i, hwcam_cfgstream_mount_buf_req_t, intf)

#define REF2SMBR(r) container_of(r, hwcam_cfgstream_mount_buf_req_t, ref)

static void
hwcam_cfgstream_mount_buf_req_release(
        struct kref* r); 

static void 
hwcam_cfgstream_mount_buf_req_get(
        hwcam_cfgreq_intf_t* pintf)
{
    hwcam_cfgstream_mount_buf_req_t* mbr = I2SMBR(pintf);
    kref_get(&mbr->ref);
}

static int 
hwcam_cfgstream_mount_buf_req_put(
        hwcam_cfgreq_intf_t* pintf)
{
    hwcam_cfgstream_mount_buf_req_t* mbr = I2SMBR(pintf);
    return kref_put(&mbr->ref, hwcam_cfgstream_mount_buf_req_release);
}

static int
hwcam_cfgstream_mount_buf_req_on_req(
        hwcam_cfgreq_intf_t* pintf,
        struct v4l2_event* ev)
{
    hwcam_cfgstream_mount_buf_req_t* mbr = I2SMBR(pintf);
    hwcam_cfgreq2stream_t* req = (hwcam_cfgreq2stream_t*)&ev->u.data;
    struct dma_buf* buf = NULL; 
    int rc = -ETIME;

    mutex_lock(&mbr->lock); 
    swap(buf, mbr->buf); 

    if (!buf) {
        goto exit_on_req; 
    }

    rc = dma_buf_fd(buf, O_CLOEXEC);
    if (rc < 0) {
        HWCAM_CFG_ERR("failed to get fd for buffer! \n");
        dma_buf_put(buf); 
        req->req.rc = rc; 
        hwcam_cfgdev_queue_ack(ev);
        goto exit_on_req; 
    }

    req->buf.fd = rc; 
    rc = 0; 

exit_on_req:
    mutex_unlock(&mbr->lock); 
    return rc;
}

static int
hwcam_cfgstream_mount_buf_req_on_cancel(
        hwcam_cfgreq_intf_t* pintf, 
        int reason)
{
    hwcam_cfgstream_mount_buf_req_t* mbr = I2SMBR(pintf);
    int rc = 0; 
    struct dma_buf* buf = NULL; 

    mutex_lock(&mbr->lock); 
    swap(buf, mbr->buf); 

    if (!buf) {
        goto exit_on_canceled; 
    }

    dma_buf_put(buf); 
    rc = reason; 

exit_on_canceled:
    mutex_unlock(&mbr->lock); 
    return rc;
}

static int
hwcam_cfgstream_mount_buf_req_on_ack(
        hwcam_cfgreq_intf_t* pintf,
        hwcam_cfgack_t* ack)
{
    hwcam_cfgstream_mount_buf_req_t* mbr = I2SMBR(pintf);

    mutex_lock(&mbr->lock); 
    if (hwcam_cfgack_result(ack)) {
        HWCAM_CFG_ERR("request(0x%p) failed! \n", pintf);
    }
    mutex_unlock(&mbr->lock); 
    return 0;
}

static hwcam_cfgreq_vtbl_t
s_vtbl_req_mount_buf =
{
    .get = hwcam_cfgstream_mount_buf_req_get, 
    .put = hwcam_cfgstream_mount_buf_req_put, 
    .on_req = hwcam_cfgstream_mount_buf_req_on_req,
    .on_cancel = hwcam_cfgstream_mount_buf_req_on_cancel,
    .on_ack = hwcam_cfgstream_mount_buf_req_on_ack,
};

static int
hwcam_cfgstream_mount_buf_req_create_instance(
        hwcam_buf_info_t* buf, 
        hwcam_cfgstream_mount_buf_req_t** req)
{
    int rc = 0; 
    hwcam_cfgstream_mount_buf_req_t* mbr = kzalloc(
            sizeof(hwcam_cfgstream_mount_buf_req_t), GFP_KERNEL);
    *req = NULL;

    if (mbr == NULL) {
        HWCAM_CFG_ERR("out of memory! \n");
        rc = -ENOMEM; 
        goto exit_create_instance; 
    }

    mbr->buf = dma_buf_get(buf->fd); 
    if (IS_ERR_OR_NULL(mbr->buf)) {
        HWCAM_CFG_ERR("invalid file handle(%d)! \n", buf->fd);
        kzfree(mbr);
        rc = -EBADF; 
        goto exit_create_instance; 
    }

    mutex_init(&mbr->lock);
    kref_init(&mbr->ref);
    mbr->intf.vtbl = &s_vtbl_req_mount_buf;

    *req = mbr; 

exit_create_instance: 
    return rc;
}

static void
hwcam_cfgstream_mount_buf_req_release(
        struct kref* r)
{
    hwcam_cfgstream_mount_buf_req_t* mbr = REF2SMBR(r) ; 

    hwcam_cfgstream_mount_buf_req_on_cancel(&mbr->intf, -ENOENT);

    kzfree(mbr);
}

static inline int
hwcam_cfgstream_mount_unmount_buf(
        hwcam_cfgstream_intf_t* intf,
        hwcam_buf_info_t* buf,
        int mount)
{
    hwcam_cfgstream_t* stm = I2STM(intf);
    int rc = -EINVAL;
    int ack = 0;
    struct v4l2_event ev =
    {
        .type = HWCAM_V4L2_EVENT_TYPE,
        .id = HWCAM_CFGSTREAM_REQUEST,
    };
    hwcam_cfgreq2stream_t* req = (hwcam_cfgreq2stream_t*)ev.u.data;
    hwcam_cfgstream_mount_buf_req_t* mbr = NULL;  

    rc = hwcam_cfgstream_mount_buf_req_create_instance(buf, &mbr); 
    if (!mbr) {
        goto exit_on_req; 
    }

    req->req.intf = &mbr->intf;
    req->kind = mount
        ? HWCAM_CFGSTREAM_REQ_MOUNT_BUF
        : HWCAM_CFGSTREAM_REQ_UNMOUNT_BUF;
    req->buf = *buf;

    rc = hwcam_cfgdev_send_req(stm->user, &ev, &stm->rq, 0, &ack); 

    hwcam_cfgreq_intf_put(&mbr->intf); 

exit_on_req: 
    return rc? rc: ack;
}

static int
hwcam_cfgstream_mount_buf(
        hwcam_cfgstream_intf_t* intf,
        hwcam_buf_info_t* buf)
{
    return hwcam_cfgstream_mount_unmount_buf(
            intf, buf, 1);
}

static int
hwcam_cfgstream_unmount_buf(
        hwcam_cfgstream_intf_t* intf,
        hwcam_buf_info_t* buf)
{
    return hwcam_cfgstream_mount_unmount_buf(
            intf, buf, 0);
}

typedef struct _tag_hwcam_cfgstream_mount_graphic_buf_req
{
    struct mutex                                lock; 
    struct kref                                 ref;
    hwcam_cfgreq_intf_t                         intf; 
    unsigned                                    canceled : 1; 
    unsigned                                    finished : 1; 

    hwcam_graphic_buf_info_t*                   buf;
    struct file*                                objs[HWCAM_GRAPHIC_BUF_INFO_LENGTH];
    int                                         ints[HWCAM_GRAPHIC_BUF_INFO_LENGTH];
} hwcam_cfgstream_mount_graphic_buf_req_t;

#define I2SMGBR(i) container_of(i, hwcam_cfgstream_mount_graphic_buf_req_t, intf)

#define REF2SMGBR(r) container_of(r, hwcam_cfgstream_mount_graphic_buf_req_t, ref)

static void
hwcam_cfgstream_mount_graphic_buf_req_release(
        struct kref* r); 

static void 
hwcam_cfgstream_mount_graphic_buf_req_get(
        hwcam_cfgreq_intf_t* pintf)
{
    hwcam_cfgstream_mount_graphic_buf_req_t* mbr = I2SMGBR(pintf);
    kref_get(&mbr->ref);
}

static int 
hwcam_cfgstream_mount_graphic_buf_req_put(
        hwcam_cfgreq_intf_t* pintf)
{
    hwcam_cfgstream_mount_graphic_buf_req_t* mbr = I2SMGBR(pintf);
    return kref_put(&mbr->ref, hwcam_cfgstream_mount_graphic_buf_req_release);
}

static int
hwcam_cfgstream_mount_graphic_buf_req_on_req(
        hwcam_cfgreq_intf_t* pintf,
        struct v4l2_event* ev)
{
    int i = 0;
    int rc = 0; 
    hwcam_cfgreq2stream_t* req = (hwcam_cfgreq2stream_t*)&ev->u.data;
    hwcam_cfgstream_mount_graphic_buf_req_t* mbr = I2SMGBR(pintf);

    mutex_lock(&mbr->lock); 

    if (mbr->canceled) {
        rc = -EINVAL; 
        goto exit_on_req; 
    }

    for (; i < mbr->buf->num_fds; i++) {
        mbr->buf->data[i] = get_unused_fd_flags(O_CLOEXEC);
        if (mbr->buf->data[i] < 0) {
            HWCAM_CFG_ERR("failed to get fd for buffer! \n");
            rc = mbr->buf->data[i]; 
            goto fail_get_unused_fd;
        }
    }
    for (; i != 0; i--) {
        fd_install(mbr->buf->data[i - 1], mbr->objs[i - 1]);
    }

    mbr->finished = 1; 
    rc = 0; 

    goto exit_on_req; 

fail_get_unused_fd:
    for (; i != 0; i--) {
        put_unused_fd(mbr->buf->data[i - 1]);
        mbr->buf->data[i - 1] = -1; 
    }
    req->req.rc = mbr->buf->data[i];
    hwcam_cfgdev_queue_ack(ev);

exit_on_req: 
    mutex_unlock(&mbr->lock); 
    return rc;
}

static int
hwcam_cfgstream_mount_graphic_buf_req_on_cancel(
        hwcam_cfgreq_intf_t* pintf, 
        int reason)
{
    int rc = 0; 
    int i = 0;
    hwcam_cfgstream_mount_graphic_buf_req_t* mbr = I2SMGBR(pintf);
    mutex_lock(&mbr->lock); 

    if (mbr->finished || mbr->canceled) {
        goto exit_on_canceled; 
    }

    mbr->canceled = 1; 
    rc = reason; 

    for (; i < mbr->buf->num_fds; i++) {
        fput(mbr->objs[i]); 
    }

exit_on_canceled: 
    mutex_unlock(&mbr->lock); 
    return rc; 
}

static int
hwcam_cfgstream_mount_graphic_buf_req_on_ack(
        hwcam_cfgreq_intf_t* pintf,
        hwcam_cfgack_t* ack)
{
    hwcam_cfgstream_mount_graphic_buf_req_t* mbr = I2SMGBR(pintf);

    mutex_lock(&mbr->lock); 
    if (hwcam_cfgack_result(ack)) {
        HWCAM_CFG_ERR("request(0x%p) failed! \n", pintf);
    }
    mutex_unlock(&mbr->lock); 
    return 0;
}

static hwcam_cfgreq_vtbl_t
s_vtbl_req_mount_graphic_buf =
{
    .get = hwcam_cfgstream_mount_graphic_buf_req_get, 
    .put = hwcam_cfgstream_mount_graphic_buf_req_put, 
    .on_req = hwcam_cfgstream_mount_graphic_buf_req_on_req,
    .on_cancel = hwcam_cfgstream_mount_graphic_buf_req_on_cancel,
    .on_ack = hwcam_cfgstream_mount_graphic_buf_req_on_ack,
};

static int
hwcam_cfgstream_mount_graphic_buf_req_create_instance(
        hwcam_graphic_buf_info_t* buf, 
        hwcam_cfgstream_mount_graphic_buf_req_t** req)
{
    int rc = 0; 
    int i = 0;
    hwcam_cfgstream_mount_graphic_buf_req_t* mbr = NULL;
    *req = NULL; 

    if (HWCAM_GRAPHIC_BUF_INFO_LENGTH <= buf->num_ints + buf->num_fds) {
        HWCAM_CFG_ERR("out of range! \n");
        goto exit_create_instance;
    }

    mbr = kzalloc(sizeof(hwcam_cfgstream_mount_graphic_buf_req_t), GFP_KERNEL);
    if (mbr == NULL) {
        HWCAM_CFG_ERR("out of memory! \n");
        rc = -ENOMEM; 
        goto exit_create_instance;
    }

    for (; i < buf->num_fds; i++) {
        mbr->objs[i] = fget(buf->data[i]);
        if (mbr->objs[i] == NULL) {
            HWCAM_CFG_ERR("invalid file handle(%d)! \n", buf->data[i]);
            rc = -EBADF; 
            goto fail_to_fget;
        }
    }
    for (; i < buf->num_fds + buf->num_ints; i++) {
        mbr->ints[i] = buf->data[i];
    }

    mutex_init(&mbr->lock);
    kref_init(&mbr->ref);
    mbr->intf.vtbl = &s_vtbl_req_mount_graphic_buf;
    mbr->canceled = 0; 
    mbr->finished = 0; 

    mbr->buf = buf; 

    *req = mbr; 

    return rc;

fail_to_fget:
    for (; i != 0; i--) {
        fput(mbr->objs[i - 1]);
    }
    kzfree(mbr); 

exit_create_instance:
    return rc; 
}

static void
hwcam_cfgstream_mount_graphic_buf_req_release(
        struct kref* r)
{
    hwcam_cfgstream_mount_graphic_buf_req_t* mbr = REF2SMGBR(r); 

    hwcam_cfgstream_mount_graphic_buf_req_on_cancel(&mbr->intf, -ENOENT);

    kzfree(mbr);
}

static int
hwcam_cfgstream_mount_graphic_buf(
        hwcam_cfgstream_intf_t* intf,
        hwcam_graphic_buf_info_t* buf)
{
    hwcam_cfgstream_t* stm = I2STM(intf);
    int rc = -EINVAL;
    int ack = 0;
    struct v4l2_event ev =
    {
        .type = HWCAM_V4L2_EVENT_TYPE,
        .id = HWCAM_CFGSTREAM_REQUEST,
    };
    hwcam_cfgreq2stream_t* req = (hwcam_cfgreq2stream_t*)ev.u.data;
    hwcam_cfgstream_mount_graphic_buf_req_t* mbr = NULL; 

    rc = hwcam_cfgstream_mount_graphic_buf_req_create_instance(buf, &mbr); 
    if (!mbr) {
        goto exit_mount_graphic_buffer; 
    }

    req->req.intf = &mbr->intf;
    req->kind = HWCAM_CFGSTREAM_REQ_MOUNT_GRAPHIC_BUF;

    rc = hwcam_cfgdev_send_req(stm->user, &ev, &stm->rq, 0, &ack); 

    hwcam_cfgreq_intf_put(&mbr->intf); 

exit_mount_graphic_buffer: 
    return rc? rc: ack;
}

static int
hwcam_cfgstream_unmount_graphic_buf(
        hwcam_cfgstream_intf_t* intf,
        int index)
{
    hwcam_cfgstream_t* stm = I2STM(intf);
    int rc = -EINVAL;
    int ack = 0;
    struct v4l2_event ev =
    {
        .type = HWCAM_V4L2_EVENT_TYPE,
        .id = HWCAM_CFGSTREAM_REQUEST,
    };
    hwcam_cfgreq2stream_t* req = (hwcam_cfgreq2stream_t*)ev.u.data;

    req->req.intf = NULL;
    req->kind = HWCAM_CFGSTREAM_REQ_UNMOUNT_GRAPHIC_BUF;
    req->unmount_graphic_buf.index = index;

    rc = hwcam_cfgdev_send_req(stm->user, &ev, &stm->rq, 0, &ack);
    return rc? rc: ack;
}

static int
hwcam_cfgstream_query_param(
        hwcam_cfgstream_intf_t* intf)
{
    hwcam_cfgstream_t* stm = I2STM(intf);
    int rc = -EINVAL;
    int ack = 0;
    struct v4l2_event ev =
    {
        .type = HWCAM_V4L2_EVENT_TYPE,
        .id = HWCAM_CFGSTREAM_REQUEST,
    };
    hwcam_cfgreq2stream_t* req = (hwcam_cfgreq2stream_t*)ev.u.data;

    req->req.intf = NULL;
    req->kind = HWCAM_CFGSTREAM_REQ_QUERY_PARAM;

    rc = hwcam_cfgdev_send_req(stm->user, &ev, &stm->rq, 0, &ack);
    return rc? rc: ack;
}

static int
hwcam_cfgstream_change_param(
        hwcam_cfgstream_intf_t* intf)
{
    hwcam_cfgstream_t* stm = I2STM(intf);
    int rc = -EINVAL;
    int ack = 0;
    struct v4l2_event ev =
    {
        .type = HWCAM_V4L2_EVENT_TYPE,
        .id = HWCAM_CFGSTREAM_REQUEST,
    };
    hwcam_cfgreq2stream_t* req = (hwcam_cfgreq2stream_t*)ev.u.data;

    req->req.intf = NULL;
    req->kind = HWCAM_CFGSTREAM_REQ_CHANGE_PARAM;

    rc = hwcam_cfgdev_send_req(stm->user, &ev, &stm->rq, 0, &ack);
    return rc? rc: ack;
}

static void
hwcam_cfgstream_buf_queue(
         hwcam_cfgstream_intf_t* intf,
         hwcam_vbuf_t* buf)
{
    hwcam_cfgstream_t* stm = I2STM(intf);
    unsigned long flags;

    spin_lock_irqsave(&stm->lock_bufq, flags);
    list_add_tail(&buf->node, &stm->bufq_idle);
    spin_unlock_irqrestore(&stm->lock_bufq, flags);

    wake_up_all(&stm->rq.wait);
}

static int
hwcam_cfgstream_start(
        hwcam_cfgstream_intf_t* intf)
{
    hwcam_cfgstream_t* stm = I2STM(intf);
    int rc = -EINVAL;
    int ack = 0;
    struct v4l2_event ev =
    {
        .type = HWCAM_V4L2_EVENT_TYPE,
        .id = HWCAM_CFGSTREAM_REQUEST,
    };
    hwcam_cfgreq2stream_t* req = (hwcam_cfgreq2stream_t*)ev.u.data;

    req->req.intf = NULL;
    req->kind = HWCAM_CFGSTREAM_REQ_START;

    rc = hwcam_cfgdev_send_req(stm->user, &ev, &stm->rq, 0, &ack);
    return rc? rc: ack;
}

static int
hwcam_cfgstream_stop(
        hwcam_cfgstream_intf_t* intf)
{
    hwcam_cfgstream_t* stm = I2STM(intf);
    int rc = -EINVAL;
    int ack = 0;
    unsigned long flags;
    struct v4l2_event ev =
    {
        .type = HWCAM_V4L2_EVENT_TYPE,
        .id = HWCAM_CFGSTREAM_REQUEST,
    };
    hwcam_cfgreq2stream_t* req = (hwcam_cfgreq2stream_t*)ev.u.data;

    spin_lock_irqsave(&stm->lock_bufq, flags);
    INIT_LIST_HEAD(&stm->bufq_idle);
    INIT_LIST_HEAD(&stm->bufq_busy);
    spin_unlock_irqrestore(&stm->lock_bufq, flags);

    req->req.intf = NULL;
    req->kind = HWCAM_CFGSTREAM_REQ_STOP;

    rc = hwcam_cfgdev_send_req(stm->user, &ev, &stm->rq, 0, &ack);
    return rc? rc: ack;
}

static hwcam_cfgstream_vtbl_t
s_vtbl_cfgstream =
{
    .get = hwcam_cfgstream_get,
    .put = hwcam_cfgstream_put,
    .umount = hwcam_cfgstream_umount,

    .try_fmt = hwcam_cfgstream_try_fmt,

    .mount_buf = hwcam_cfgstream_mount_buf,
    .unmount_buf = hwcam_cfgstream_unmount_buf,
    .mount_graphic_buf = hwcam_cfgstream_mount_graphic_buf,
    .unmount_graphic_buf = hwcam_cfgstream_unmount_graphic_buf,
    .query_param = hwcam_cfgstream_query_param,
    .change_param = hwcam_cfgstream_change_param,

    .buf_queue = hwcam_cfgstream_buf_queue,

    .start = hwcam_cfgstream_start,
    .stop = hwcam_cfgstream_stop,
};

static long
hwcam_cfgstream_vo_dqevent(
        hwcam_cfgstream_t* stm,
        struct v4l2_event* ev,
        int nb)
{
    long rc = 0;
    hwcam_cfgreq_t* req = NULL;
    while (true) {
        rc = v4l2_event_dequeue(&stm->rq, ev, nb);
        if (rc != 0) { break; }

        if (stm->cfgreq) {
            hwcam_cfgreq_intf_put(stm->cfgreq); 
            stm->cfgreq = NULL; 
        }

        req = (hwcam_cfgreq_t*)ev->u.data;
        if (req->intf) {
            if (hwcam_cfgreq_intf_on_req(req->intf, ev)) {
                HWCAM_CFG_ERR("request(0x%p, 0x%08x, %u) skipped. \n",
                        req->intf, (*(unsigned*)(req + 1)), req->seq);
                hwcam_cfgreq_intf_put(req->intf); 
                continue;   // to skip failed/timeouted/interrupted events
            }
            stm->cfgreq = req->intf;
        }
        break; 
    }
    return rc;
}

static long
hwcam_cfgstream_vo_notify(
        hwcam_cfgstream_t* stm,
        struct v4l2_event* ev)
{
    hwcam_user_intf_notify(stm->user, ev);
    return 0;
}

static long
hwcam_cfgstream_vo_mount_buf(
        hwcam_cfgstream_t* stm,
        hwcam_buf_info_t* bi)
{
    long rc = -EINVAL;
    switch (bi->kind)
    {
    case HWCAM_BUF_KIND_STREAM_PARAM:
        break;
    default:
        HWCAM_CFG_ERR("invalid buffer kind(%d)! \n", bi->kind);
        break;
    }
    return rc;
}

static long
hwcam_cfgstream_vo_unmount_buf(
        hwcam_cfgstream_t* stm,
        hwcam_buf_info_t* bi)
{
    long rc = -EINVAL;
    switch (bi->kind)
    {
    case HWCAM_BUF_KIND_STREAM_PARAM:
        break;
    default:
        HWCAM_CFG_ERR("invalid buffer kind(%d)! \n", bi->kind);
        break;
    }
    return rc;
}

static long
hwcam_cfgstream_vo_get_graphic_buf(
        hwcam_cfgstream_t* stm,
        hwcam_graphic_buf_info_t* bi)
{
    long rc = -EINVAL;
    if (stm->cfgreq != NULL
            && stm->cfgreq->vtbl == &s_vtbl_req_mount_graphic_buf) {
        hwcam_cfgstream_mount_graphic_buf_req_t* req =
            container_of(stm->cfgreq, hwcam_cfgstream_mount_graphic_buf_req_t, intf);
        *bi = *req->buf;
        rc = 0;
    }
    else {
        HWCAM_CFG_ERR("failed to get graphic buffer info! \n");
    }
    return rc;
}

static int
hwcam_cfgstream_vo_get_buf(
        hwcam_cfgstream_t* stm,
        hwcam_buf_status_t *bufstatus)
{
    hwcam_vbuf_t* ret = NULL;
    unsigned long flags;

    spin_lock_irqsave(&stm->lock_bufq, flags);
    if (!list_empty(&stm->bufq_idle)) {
        ret = list_first_entry(&stm->bufq_idle, hwcam_vbuf_t, node);
        list_move_tail(&ret->node, &stm->bufq_busy);
    }
    spin_unlock_irqrestore(&stm->lock_bufq, flags);
    if (ret) {
        bufstatus->id = ret->buf.v4l2_buf.index;
        bufstatus->tv.tv_sec = ret->buf.v4l2_buf.timestamp.tv_sec;
        bufstatus->tv.tv_usec = ret->buf.v4l2_buf.timestamp.tv_usec;
        return 0;
    }
    else {
        bufstatus->id = -1;
        return -ENOMEM;
    }
}

static int
hwcam_cfgstream_vo_put_buf(
        hwcam_cfgstream_t* stm,
        hwcam_buf_status_t *bufstatus)
{
    int rc = -EINVAL;
    hwcam_vbuf_t* entry = NULL;
    hwcam_vbuf_t* tmp = NULL;
    unsigned long flags;

    spin_lock_irqsave(&stm->lock_bufq, flags);
    list_for_each_entry_safe(entry, tmp, &stm->bufq_busy, node) {
        if (entry->buf.v4l2_buf.index == bufstatus->id) {
            list_move(&entry->node, &stm->bufq_idle);
            rc = 0;
            break;
        }
    }
    spin_unlock_irqrestore(&stm->lock_bufq, flags);
    return rc;
}

static int
hwcam_cfgstream_vo_buf_done(
        hwcam_cfgstream_t* stm,
        hwcam_buf_status_t *bufstatus)
{
    int rc = -EINVAL;
    hwcam_vbuf_t* entry = NULL;
    hwcam_vbuf_t* tmp = NULL;
    unsigned long flags;

    spin_lock_irqsave(&stm->lock_bufq, flags);
    list_for_each_entry_safe(entry, tmp, &stm->bufq_busy, node) {
        if (entry->buf.v4l2_buf.index == bufstatus->id) {
            list_del_init(&entry->node);
            if (bufstatus->buf_status == false) {
                vb2_buffer_done(&entry->buf, VB2_BUF_STATE_DONE);
            } else {
                vb2_buffer_done(&entry->buf, VB2_BUF_STATE_ERROR);
            }
            rc = 0;
            break;
        }
    }
    spin_unlock_irqrestore(&stm->lock_bufq, flags);
    return rc;
}

static long
hwcam_cfgstream_vo_get_fmt(
        hwcam_cfgstream_t* stm,
        struct v4l2_format* fmt)
{
    long rc = -EINVAL;
    if (stm->cfgreq != NULL && stm->cfgreq->vtbl == &s_vtbl_req_fmt) {
        hwcam_cfgstream_fmt_req_t* req =
            container_of(stm->cfgreq, hwcam_cfgstream_fmt_req_t, intf);
        *fmt = *req->fmt;
        rc = 0;
    }
    return rc;
}

static long
hwcam_cfgstream_vo_set_fmt(
        hwcam_cfgstream_t* stm,
        struct v4l2_format* fmt)
{
    long rc = -EINVAL;
    if (stm->cfgreq != NULL && stm->cfgreq->vtbl == &s_vtbl_req_fmt) {
        hwcam_cfgstream_fmt_req_t* req =
            container_of(stm->cfgreq, hwcam_cfgstream_fmt_req_t, intf);
        *req->fmt = *fmt;
        rc = 0;
    }
    return rc;
}

static void 
hwcam_cfgstream_subscribed_event_ops_merge(
        const struct v4l2_event* old, 
        struct v4l2_event* new)
{
    hwcam_cfgreq2stream_t* req = (hwcam_cfgreq2stream_t*)&old->u.data;
    if (req->req.intf) {
        hwcam_cfgreq_intf_put(req->req.intf); 
    }
    HWCAM_CFG_ERR("the event queue overflowed! \n");
}

static struct v4l2_subscribed_event_ops 
s_hwcam_subscribed_event_ops = 
{
    .merge = hwcam_cfgstream_subscribed_event_ops_merge, 
}; 

static long
hwcam_cfgstream_vo_do_ioctl(
        struct file* filep,
        unsigned int cmd,
        void* arg)
{
    long rc = -EINVAL;
	hwcam_cfgstream_t* stm = NULL;
    if (NULL == filep){
        HWCAM_CFG_ERR("filep is null");
        return rc;
    }
    if (NULL == filep->private_data){
        HWCAM_CFG_ERR("private_data is null");
        return rc;
    }

    stm = I2STM(filep->private_data);

    switch (cmd)
    {
    case VIDIOC_DQEVENT:
        rc = hwcam_cfgstream_vo_dqevent(stm,
                arg, filep->f_flags & O_NONBLOCK);
        break;
    case HWCAM_V4L2_IOCTL_NOTIFY:
        rc = hwcam_cfgstream_vo_notify(stm, arg);
        break;
    case HWCAM_V4L2_IOCTL_MOUNT_BUF:
        rc = hwcam_cfgstream_vo_mount_buf(stm, arg);
        break;
    case HWCAM_V4L2_IOCTL_UNMOUNT_BUF:
        rc = hwcam_cfgstream_vo_unmount_buf(stm, arg);
        break;
    case HWCAM_V4L2_IOCTL_GET_GRAPHIC_BUF:
        rc = hwcam_cfgstream_vo_get_graphic_buf(stm, arg);
        break;
    case HWCAM_V4L2_IOCTL_GET_BUF:
        rc = hwcam_cfgstream_vo_get_buf(stm, arg);
        break;
    case HWCAM_V4L2_IOCTL_PUT_BUF:
        rc = hwcam_cfgstream_vo_put_buf(stm, arg);
        break;
    case HWCAM_V4L2_IOCTL_BUF_DONE:
        rc = hwcam_cfgstream_vo_buf_done(stm, arg);
        break;
    case VIDIOC_G_FMT:
        rc = hwcam_cfgstream_vo_get_fmt(stm, arg);
        break;
    case VIDIOC_S_FMT:
        rc = hwcam_cfgstream_vo_set_fmt(stm, arg);
        break;
    case VIDIOC_SUBSCRIBE_EVENT:
        rc = v4l2_event_subscribe(&stm->rq, arg, 32, 
                &s_hwcam_subscribed_event_ops);
        break;
    case VIDIOC_UNSUBSCRIBE_EVENT:
        rc = v4l2_event_unsubscribe(&stm->rq, arg);
        break;
    case HWCAM_V4L2_IOCTL_REQUEST_ACK:
        if (stm->cfgreq) {
            hwcam_cfgreq_intf_put(stm->cfgreq); 
            stm->cfgreq = NULL; 
        }
        rc = hwcam_cfgdev_queue_ack(arg);
        break;
    default:
        HWCAM_CFG_ERR("invalid IOCTL CMD(%d)", cmd);
        break;
    }
    return rc;
}

static unsigned int
hwcam_cfgstream_vo_poll(
        struct file* filep,
        struct poll_table_struct* ptbl)
{
    unsigned int rc = 0;
    hwcam_cfgdev_lock();
    {
        void* pd = filep->private_data;
        if (pd) {
            hwcam_cfgstream_t* stm = I2STM(pd);
            unsigned long flags;

            poll_wait(filep, &stm->rq.wait, ptbl);

            spin_lock_irqsave(&stm->lock_bufq, flags);
            if (!list_empty(&stm->bufq_idle)) {
                rc |= POLLIN | POLLRDNORM;
            }
            spin_unlock_irqrestore(&stm->lock_bufq, flags);

            if (v4l2_event_pending(&stm->rq)) {
                rc |= POLLIN | POLLRDNORM;
            }
        }
    }
    hwcam_cfgdev_unlock();
	return rc;
}

static long
hwcam_cfgstream_vo_ioctl(
        struct file* filep,
        unsigned int cmd,
        unsigned long arg)
{
    int rc = 0;
    hwcam_cfgdev_lock();
    {
        rc =  video_usercopy(filep, cmd, arg,
                hwcam_cfgstream_vo_do_ioctl);
    }
    hwcam_cfgdev_unlock();
    return rc;
}

#ifdef CONFIG_COMPAT
static long
hwcam_cfgstream_vo_ioctl32(
        struct file* filep,
        unsigned int cmd,
        unsigned long arg)
{
    int rc = 0;
	void __user *up = NULL;
    void __user *kp = NULL;
	/* struct v4l2_format kpvf; */
    up = compat_ptr(arg);
	
    switch (cmd)
    {
    case VIDIOC_DQEVENT32: cmd = VIDIOC_DQEVENT; break;
    case HWCAM_V4L2_IOCTL_REQUEST_ACK32: cmd = HWCAM_V4L2_IOCTL_REQUEST_ACK; break;
    case HWCAM_V4L2_IOCTL_NOTIFY32: cmd = HWCAM_V4L2_IOCTL_NOTIFY; break;
    case HWCAM_V4L2_IOCTL_GET_BUF32: cmd = HWCAM_V4L2_IOCTL_GET_BUF; break;
    case HWCAM_V4L2_IOCTL_PUT_BUF32: cmd = HWCAM_V4L2_IOCTL_PUT_BUF; break;
    case HWCAM_V4L2_IOCTL_BUF_DONE32: cmd = HWCAM_V4L2_IOCTL_BUF_DONE; break;
    case VIDIOC_G_FMT32: cmd = VIDIOC_G_FMT; break;
    case VIDIOC_S_FMT32: cmd = VIDIOC_S_FMT; break;
    }

    switch (cmd)
    {
    case VIDIOC_DQEVENT:
    case HWCAM_V4L2_IOCTL_NOTIFY:
    case HWCAM_V4L2_IOCTL_REQUEST_ACK:
        {
            kp = compat_alloc_user_space(sizeof(struct v4l2_event));
            if (NULL == kp)
                return -EFAULT;

            rc = compat_get_v4l2_event_data(kp, up);
            if (0 != rc)
                return rc;
            rc = hwcam_cfgstream_vo_ioctl(filep, cmd, (unsigned long)kp);
            if (0 != rc)
                return rc;
            rc = compat_put_v4l2_event_data(kp, up);
            return rc;
        }
        break;
    case HWCAM_V4L2_IOCTL_GET_BUF:
    case HWCAM_V4L2_IOCTL_PUT_BUF:
    case HWCAM_V4L2_IOCTL_BUF_DONE:
        {
            kp = compat_alloc_user_space(sizeof(hwcam_buf_status_t));
            if (NULL == kp)
                return -EFAULT;
            rc = compat_get_hwcam_buf_status_data(kp, up);
            if (0 != rc)
                return rc;
            rc = hwcam_cfgstream_vo_ioctl(filep, cmd, (unsigned long)kp);
            if (0 != rc)
                return rc;
            rc = compat_put_hwcam_buf_status_data(kp, up);
            return rc;
        }
        break;
    case VIDIOC_G_FMT:
    case VIDIOC_S_FMT:
        {
	        struct v4l2_format kpvf;
            rc = compat_get_v4l2_format_data(&kpvf, up);
            if (0 != rc)
                return rc;
            hwcam_cfgdev_lock();
            rc = hwcam_cfgstream_vo_do_ioctl(filep, cmd, (void *)&kpvf);
            hwcam_cfgdev_unlock();
            if (0 != rc) 
                return rc;
            rc = compat_put_v4l2_format_data(&kpvf, up);
            return rc;
        }
        break;
    default:
        rc = hwcam_cfgstream_vo_ioctl(filep, cmd, arg);
        break;
    }
	
    return rc;
}
#endif

static int
hwcam_cfgstream_vo_close(
        struct inode* i,
        struct file* filep)
{
    void* pd = NULL;
    swap(pd, filep->private_data);
    if (pd) {
        hwcam_cfgstream_t* stm = I2STM(pd);

        HWCAM_CFG_DEBUG("instance(0x%p)", &stm->intf);

        if (!list_empty(&stm->node)) {
            list_del_init(&stm->node);
            hwcam_cfgstream_intf_put(&stm->intf);
        }

        hwcam_cfgdev_lock();
        {
            v4l2_fh_del(&stm->rq);
            v4l2_fh_exit(&stm->rq);
        }
        hwcam_cfgdev_unlock();

        hwcam_cfgstream_intf_put(&stm->intf);
    }
    return 0;
}

static struct file_operations
s_fops_cfgstream =
{
    .poll = hwcam_cfgstream_vo_poll,
    .unlocked_ioctl = hwcam_cfgstream_vo_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = hwcam_cfgstream_vo_ioctl32,
#endif
    .release = hwcam_cfgstream_vo_close,
};

static void 
hwcam_cfgstream_mount_req_get(
        hwcam_cfgreq_intf_t* pintf)
{
    hwcam_cfgstream_mount_req_t* msr = I2MSR(pintf);
    kref_get(&msr->ref);
}

static int 
hwcam_cfgstream_mount_req_put(
        hwcam_cfgreq_intf_t* pintf)
{
    hwcam_cfgstream_mount_req_t* msr = I2MSR(pintf);
    return kref_put(&msr->ref, hwcam_cfgstream_mount_req_release);
}

static int
hwcam_cfgstream_mount_req_on_req(
        hwcam_cfgreq_intf_t* pintf,
        struct v4l2_event* ev)
{
    hwcam_cfgstream_mount_req_t* msr = I2MSR(pintf);
    int rc = 0;
    int count = 0; 
    hwcam_cfgstream_t* so = NULL;
    hwcam_cfgreq2pipeline_t* req = (hwcam_cfgreq2pipeline_t*)&ev->u.data;
    struct dma_buf* buf = NULL; 

    mutex_lock(&msr->lock); 
    swap(buf, msr->buf); 

    if (!buf) {
        goto exit_mount_stream; 
    }

    list_for_each_entry(so, msr->streams, node) {
        if (so->user == msr->user) {
            HWCAM_CFG_INFO("the stream had been mounted! \n");
            dma_buf_put(buf); 
            msr->stream = &so->intf;
            hwcam_cfgstream_intf_get(msr->stream);
            rc = 0; 
            req->req.rc = 0; 
            hwcam_cfgdev_queue_ack(ev);
            goto exit_mount_stream;
        }
        count++; 
    }
    if (count > HWCAM_CFGSTREAM_MAX) {
        HWCAM_CFG_ERR("too many streams! \n");
        dma_buf_put(buf); 
        rc = -EINVAL; 
        req->req.rc = -EINVAL; 
        hwcam_cfgdev_queue_ack(ev);
        goto exit_mount_stream;
    }

    req->stream.info = msr->info->info;
    req->stream.info.fd = dma_buf_fd(buf, O_CLOEXEC);
    req->stream.handle = NULL;
    if (req->stream.info.fd < 0) {
        HWCAM_CFG_ERR("failed to get fd for buffer! \n");
        dma_buf_put(buf); 
        rc = req->stream.info.fd;
        req->req.rc = rc; 
        hwcam_cfgdev_queue_ack(ev);
        goto exit_mount_stream;
    }

    so = hwcam_cfgstream_create_instance(msr);
    if (so == NULL) {
        HWCAM_CFG_ERR("failed to create stream! \n");
        sys_close(req->stream.info.fd);
        rc = -ENOMEM;
        req->req.rc = rc; 
        hwcam_cfgdev_queue_ack(ev);
        goto exit_mount_stream;
    }

    req->stream.fd = anon_inode_getfd("hwcam.cfg.stream",
            &s_fops_cfgstream, &so->intf, O_CLOEXEC);
    if (req->stream.fd < 0) {
        HWCAM_CFG_ERR("failed to mount stream! \n");
        hwcam_cfgstream_intf_put(&so->intf);
        sys_close(req->stream.info.fd);
        rc = req->stream.fd;
        req->req.rc = rc; 
        hwcam_cfgdev_queue_ack(ev);
        goto exit_mount_stream;
    }

	v4l2_fh_init(&so->rq, msr->vdev);
    v4l2_fh_add(&so->rq);
    msr->stream = &so->intf;
    hwcam_cfgstream_intf_get(msr->stream);

    list_add_tail(&so->node, msr->streams);
    hwcam_cfgstream_intf_get(&so->intf);

    rc = 0; 

exit_mount_stream: 
    mutex_unlock(&msr->lock); 
    return rc;
}

static int
hwcam_cfgstream_mount_req_on_cancel(
        hwcam_cfgreq_intf_t* pintf, 
        int reason)
{
    hwcam_cfgstream_mount_req_t* msr = I2MSR(pintf);

    int rc = 0; 
    struct dma_buf* buf = NULL; 

    mutex_lock(&msr->lock); 
    swap(buf, msr->buf); 

    if (!buf) {
        goto exit_on_canceled; 
    }

    dma_buf_put(buf); 
    rc = reason; 

exit_on_canceled: 
    mutex_unlock(&msr->lock); 
    return rc; 
}

static int
hwcam_cfgstream_mount_req_on_ack(
        hwcam_cfgreq_intf_t* pintf,
        hwcam_cfgack_t* ack)
{
    hwcam_cfgstream_mount_req_t* msr = I2MSR(pintf);

    mutex_lock(&msr->lock); 
    if (hwcam_cfgack_result(ack)) {
        HWCAM_CFG_ERR("request(0x%p) failed! \n", pintf);
    }
    mutex_unlock(&msr->lock); 
    return 0;
}

static void
hwcam_cfgstream_mount_req_get_result(
        hwcam_cfgreq_mount_stream_intf_t* pintf,
        hwcam_cfgstream_intf_t** stm)
{
    hwcam_cfgstream_mount_req_t* msr = I2MSR((hwcam_cfgreq_intf_t*)pintf);

    mutex_lock(&msr->lock); 
    *stm = msr->stream; 
    if (*stm) { 
        hwcam_cfgstream_intf_get(*stm); 
    }
    mutex_unlock(&msr->lock); 
}

static hwcam_cfgreq_mount_stream_vtbl_t
s_vtbl_req_mount_stream =
{
    .base = {
        .get = hwcam_cfgstream_mount_req_get, 
        .put = hwcam_cfgstream_mount_req_put, 
        .on_req = hwcam_cfgstream_mount_req_on_req,
        .on_cancel = hwcam_cfgstream_mount_req_on_cancel,
        .on_ack = hwcam_cfgstream_mount_req_on_ack,
    },
    .get_result = hwcam_cfgstream_mount_req_get_result, 
};

int
hwcam_cfgstream_mount_req_create_instance(
        struct video_device* vdev, 
        struct list_head* streams, 
        hwcam_cfgpipeline_intf_t* pl, 
        hwcam_user_intf_t* user, 
        hwcam_stream_info_t* info, 
        hwcam_cfgreq_mount_stream_intf_t** req)
{
    int rc = 0; 
    hwcam_cfgstream_mount_req_t* msr = kzalloc(
            sizeof(hwcam_cfgstream_mount_req_t), GFP_KERNEL);
    *req = NULL; 

    if (msr == NULL) {
        HWCAM_CFG_ERR("out of memory! \n");
        rc = -ENOMEM; 
        goto exit_create_instance; 
    }

    msr->buf = dma_buf_get(info->info.fd);
    if (IS_ERR_OR_NULL(msr->buf)) {
        HWCAM_CFG_ERR("invalid file handle(%d)! \n", info->info.fd);
        kzfree(msr); 
        rc = -EBADF; 
        goto exit_create_instance; 
    }

    mutex_init(&msr->lock); 
    kref_init(&msr->ref);
    msr->intf.vtbl = (hwcam_cfgreq_vtbl_t*)&s_vtbl_req_mount_stream;

    msr->vdev = vdev; 
    msr->streams = streams; 
    msr->pl = pl; 
    msr->user = user; 
    msr->info = info; 

    *req = (hwcam_cfgreq_mount_stream_intf_t*)&msr->intf;

exit_create_instance: 
    return rc; 
}

static void
hwcam_cfgstream_mount_req_release(
        struct kref* r)
{
    hwcam_cfgstream_mount_req_t* msr = REF2MSR(r);

    hwcam_cfgstream_mount_req_on_cancel(&msr->intf, -ENOENT);

    if (msr->stream) { 
        hwcam_cfgstream_intf_put(msr->stream); 
    }

    kzfree(msr); 
}

hwcam_cfgstream_intf_t*
hwcam_cfgstream_get_by_fd(int fd)
{
    struct file* fobj = fget(fd);
    hwcam_cfgstream_intf_t* stm = NULL;

    if (fobj) {
        if (fobj->f_op == &s_fops_cfgstream) {
            stm = (hwcam_cfgstream_intf_t*)fobj->private_data;
            hwcam_cfgstream_intf_get(stm);
        }
        fput(fobj);
    }
    if (!stm) {
        HWCAM_CFG_ERR("the fd(%d) is not a valid cfgstream object! \n", fd);
    }
    return stm;
}

