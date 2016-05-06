


#include <linux/anon_inodes.h>
#include <linux/dma-buf.h>
#include <linux/debugfs.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/pid.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/videodev2.h>
#include <linux/compat.h>
#include <linux/uaccess.h>
#include <media/v4l2-event.h>
#include <media/v4l2-fh.h>
#include <media/v4l2-ioctl.h>
#include "hwcam_compat32.h"

#include "hwcam_intf.h"

typedef struct _tag_hwcam_cfgpipeline_mount_req
{
    struct mutex                                lock;
    struct kref                                 ref;
    hwcam_cfgreq_intf_t                         intf;
    unsigned                                    canceled : 1;
    unsigned                                    finished : 1;

    struct video_device*                        vdev;

    hwcam_dev_intf_t*                           cam;
    int                                         moduleID;

    hwcam_cfgpipeline_intf_t*                   pipeline;
} hwcam_cfgpipeline_mount_req_t;

#define I2MPR(i) container_of(i, hwcam_cfgpipeline_mount_req_t, intf)

#define REF2MPR(r) container_of(r, hwcam_cfgpipeline_mount_req_t, ref)

static void
hwcam_cfgpipeline_mount_req_release(
        struct kref* r);

typedef struct _tag_hwcam_cfgpipeline
{
    struct v4l2_fh                              rq;

    hwcam_cfgpipeline_intf_t                    intf;
    struct kref                                 ref;
    struct list_head	                        node;

    hwcam_dev_intf_t*                           cam;
    struct pid*                                 cfgsvr;
    struct wakeup_source*                       ws;
    struct delayed_work                         stopping;
    struct work_struct                          delayed_release;

    struct list_head	                        streams;
} hwcam_cfgpipeline_t;

#define I2PL(i) container_of(i, hwcam_cfgpipeline_t, intf)

#define REF2PL(r) container_of(r, hwcam_cfgpipeline_t, ref)

static hwcam_cfgpipeline_vtbl_t s_vtbl_cfgpipeline;

static DEFINE_SPINLOCK(s_pipelines_lock);
static LIST_HEAD(s_pipelines_opened);
static DECLARE_WAIT_QUEUE_HEAD(s_wait_closing_pipeline);
static LIST_HEAD(s_pipelines_closing);

static void hwcam_cfgpipeline_force_close(struct work_struct *work);

enum
{
    HWCAM_WAIT4STOPPING_TIME                    =   30000,   // 30s
};

static hwcam_cfgpipeline_intf_t*
hwcam_cfgpipeline_find_by_device(
        hwcam_dev_intf_t* cam)
{
    hwcam_cfgpipeline_intf_t* pl = NULL;
    hwcam_cfgpipeline_t* cur = NULL;

    spin_lock(&s_pipelines_lock);
    list_for_each_entry(cur, &s_pipelines_opened, node) {
        if (cur->cam == cam) {
            pl = &cur->intf;
            hwcam_cfgpipeline_intf_get(pl);
            break;
        }
    }
    spin_unlock(&s_pipelines_lock);
    return pl;
}

static bool
hwcam_cfgpipeline_is_device_idle(
        hwcam_dev_intf_t* cam)
{
    bool rc = true;
    hwcam_cfgpipeline_t* cur = NULL;

    spin_lock(&s_pipelines_lock);
    list_for_each_entry(cur, &s_pipelines_closing, node) {
        if (cur->cam == cam) {
            rc = false;
            break;
        }
    }
    spin_unlock(&s_pipelines_lock);
    return rc;
}

int
hwcam_cfgpipeline_wait_idle(
        hwcam_dev_intf_t* cam,
        int timeout)
{
    return wait_event_timeout(
            s_wait_closing_pipeline,
            hwcam_cfgpipeline_is_device_idle(cam),
            msecs_to_jiffies(timeout)); //lint !e666
}

static int
hwcam_cfgpipeline_on_opened(
        hwcam_cfgpipeline_t* pl)
{
    spin_lock(&s_pipelines_lock);
    hwcam_cfgpipeline_intf_get(&pl->intf);
    list_add_tail(&pl->node, &s_pipelines_opened);
    __pm_stay_awake(pl->ws);
    spin_unlock(&s_pipelines_lock);
    return 0;
}

static void
hwcam_cfgpipeline_force_close(
        struct work_struct *work)
{
    hwcam_cfgpipeline_t* pl = container_of(work,
            hwcam_cfgpipeline_t, stopping.work);
    hwcam_cfgpipeline_t* cur = NULL;

    spin_lock(&s_pipelines_lock);
    list_for_each_entry(cur, &s_pipelines_closing, node) {
        if (cur == pl) {
            HWCAM_CFG_ERR(
                    "the server failed to close pipeline, "
                    "try restarting it! ");
            kill_pid(pl->cfgsvr, SIGKILL, 1);
            break;
        }
    }
    spin_unlock(&s_pipelines_lock);
}

static int
hwcam_cfgpipeline_on_closing(
        hwcam_cfgpipeline_t* pl)
{
    hwcam_cfgpipeline_t* cur = NULL;
    hwcam_cfgpipeline_t* tmp = NULL;

    spin_lock(&s_pipelines_lock);
    list_for_each_entry_safe(cur, tmp, &s_pipelines_opened, node) {
        if (cur == pl) {
            list_move_tail(&pl->node, &s_pipelines_closing);
            schedule_delayed_work(&pl->stopping,
                    msecs_to_jiffies(HWCAM_WAIT4STOPPING_TIME));
            break;
        }
    }
    spin_unlock(&s_pipelines_lock);
    return 0;
}

static int
hwcam_cfgpipeline_on_closed(
        hwcam_cfgpipeline_t* pl)
{
    hwcam_cfgpipeline_t* cur = NULL;
    hwcam_cfgpipeline_t* tmp = NULL;

    spin_lock(&s_pipelines_lock);
    list_for_each_entry_safe(cur, tmp, &s_pipelines_opened, node) {
        if (cur == pl) {
            struct v4l2_event ev =
            {
                .type = HWCAM_V4L2_EVENT_TYPE,
                .id = HWCAM_SERVER_CRASH,
            };
            hwcam_dev_intf_notify(pl->cam, &ev);
            break;
        }
    }
    list_for_each_entry(cur, &s_pipelines_closing, node) {
        if (cur == pl) {
            cancel_delayed_work(&pl->stopping);
            break;
        }
    }
    __pm_relax(pl->ws);
    list_del_init(&pl->node);
    hwcam_cfgpipeline_intf_put(&pl->intf);
    wake_up_all(&s_wait_closing_pipeline);
    spin_unlock(&s_pipelines_lock);
    return 0;
}

#define HWCAM_CFGPIPELINE_WAKEUP_SOURCE_NAME_SIZE (16)

static hwcam_cfgpipeline_t*
hwcam_cfgpipeline_create_instance(
        hwcam_cfgpipeline_mount_req_t* req)
{
    struct wakeup_source* ws = NULL;
    hwcam_cfgpipeline_t* pl = NULL;
    char sz_name[HWCAM_CFGPIPELINE_WAKEUP_SOURCE_NAME_SIZE] = { 0 };

    snprintf(sz_name, sizeof(sz_name),
            "hwcam_pl_%d", req->moduleID);
    ws = wakeup_source_register(sz_name);
    if (!ws) {
        goto fail_to_register_wakeup_source;
    }

    pl = kzalloc(sizeof(hwcam_cfgpipeline_t), GFP_KERNEL);
    if (pl == NULL) {
        goto fail_to_alloc;
    }

    pl->intf.vtbl = &s_vtbl_cfgpipeline;
    kref_init(&pl->ref);

	INIT_LIST_HEAD(&pl->node);
    INIT_DELAYED_WORK(&pl->stopping, hwcam_cfgpipeline_force_close);
    pl->cfgsvr = get_pid(task_pid(current));

	INIT_LIST_HEAD(&pl->streams);
    pl->cam = req->cam;
    pl->ws = ws;

    HWCAM_CFG_DEBUG("instance(0x%p)", &pl->intf);
    return pl;

fail_to_alloc:
    wakeup_source_unregister(ws);

fail_to_register_wakeup_source:
    return pl;
}

static void
hwcam_cfgpipeline_release_work(
    struct work_struct *work)
{
    hwcam_cfgpipeline_t* pl = container_of(work,hwcam_cfgpipeline_t, delayed_release);
    wakeup_source_unregister(pl->ws);
    kzfree(pl);
}

static void
hwcam_cfgpipeline_release(
        struct kref* r)
{
    hwcam_cfgpipeline_t* pl = REF2PL(r);

    HWCAM_CFG_DEBUG("instance(0x%p)", &pl->intf);

    put_pid(pl->cfgsvr);
    if (!list_empty(&pl->streams)) {
        HWCAM_CFG_ERR("the streams list is not empty!");
    }

    INIT_WORK(&pl->delayed_release,hwcam_cfgpipeline_release_work);
    schedule_work(&pl->delayed_release);
}

static void
hwcam_cfgpipeline_get(
        hwcam_cfgpipeline_intf_t* intf)
{
    hwcam_cfgpipeline_t* pl = I2PL(intf);
    kref_get(&pl->ref);
}

static int
hwcam_cfgpipeline_put(
        hwcam_cfgpipeline_intf_t* intf)
{
    hwcam_cfgpipeline_t* pl = I2PL(intf);
    return kref_put(&pl->ref, hwcam_cfgpipeline_release);
}

static int
hwcam_cfgpipeline_umount(
        hwcam_cfgpipeline_intf_t* intf)
{
    hwcam_cfgpipeline_t* pl = I2PL(intf);
    struct v4l2_event ev =
    {
        .type = HWCAM_V4L2_EVENT_TYPE,
        .id = HWCAM_CFGPIPELINE_REQUEST,
    };
    hwcam_cfgreq2pipeline_t* req = (hwcam_cfgreq2pipeline_t*)ev.u.data;

    req->req.intf = NULL;
    req->kind = HWCAM_CFGPIPELINE_REQ_UNMOUNT;

    hwcam_cfgpipeline_on_closing(pl);

    return hwcam_cfgdev_send_req(NULL, &ev, &pl->rq, 1, NULL);
}

static hwcam_cfgstream_intf_t*
hwcam_cfgpipeline_mount_stream(
        hwcam_cfgpipeline_intf_t* intf,
        hwcam_user_intf_t* user,
        hwcam_stream_info_t* info)
{
    hwcam_cfgpipeline_t* pl = I2PL(intf);
    int rc = -EINVAL;
    int ack = 0;
    struct v4l2_event ev =
    {
        .type = HWCAM_V4L2_EVENT_TYPE,
        .id = HWCAM_CFGPIPELINE_REQUEST,
    };
    hwcam_cfgreq2pipeline_t* req = (hwcam_cfgreq2pipeline_t*)ev.u.data;
    hwcam_cfgreq_mount_stream_intf_t* msr = NULL;
    hwcam_cfgstream_intf_t* stm = NULL;

    rc = hwcam_cfgstream_mount_req_create_instance(
            pl->rq.vdev, &pl->streams, intf, user, info, &msr);
    if (!msr) {
        goto exit_mount_stream;
    }

    req->req.intf = (hwcam_cfgreq_intf_t*)msr;
    req->kind = HWCAM_CFGPIPELINE_REQ_MOUNT_STREAM;
    rc = hwcam_cfgdev_send_req(user, &ev, &pl->rq, 0, &ack);
    if (rc) {
        goto fail_mount_stream;
    }
    rc = ack;

    hwcam_cfgreq_mount_stream_intf_get_result(msr, &stm);

fail_mount_stream:
    hwcam_cfgreq_intf_put((hwcam_cfgreq_intf_t*)msr);

exit_mount_stream:
    return stm;
}

typedef struct _tag_hwcam_cfgpipeline_mount_buf_req
{
    struct mutex                                lock;
    struct kref                                 ref;
    hwcam_cfgreq_intf_t                         intf;

    struct dma_buf*                             buf;
} hwcam_cfgpipeline_mount_buf_req_t;

#define I2PMBR(i) container_of(i, hwcam_cfgpipeline_mount_buf_req_t, intf)

#define REF2PMBR(r) container_of(r, hwcam_cfgpipeline_mount_buf_req_t, ref)

static void
hwcam_cfgpipeline_mount_buf_req_release(
        struct kref* r);

static void
hwcam_cfgpipeline_mount_buf_req_get(
        hwcam_cfgreq_intf_t* pintf)
{
    hwcam_cfgpipeline_mount_buf_req_t* mbr = I2PMBR(pintf);
    kref_get(&mbr->ref);
}

static int
hwcam_cfgpipeline_mount_buf_req_put(
        hwcam_cfgreq_intf_t* pintf)
{
    hwcam_cfgpipeline_mount_buf_req_t* mbr = I2PMBR(pintf);
    return kref_put(&mbr->ref, hwcam_cfgpipeline_mount_buf_req_release);
}

static int
hwcam_cfgpipeline_mount_buf_req_on_req(
        hwcam_cfgreq_intf_t* pintf,
        struct v4l2_event* ev)
{
    hwcam_cfgreq2pipeline_t* req = (hwcam_cfgreq2pipeline_t*)ev->u.data;
    hwcam_cfgpipeline_mount_buf_req_t* mbr = I2PMBR(pintf);
    struct dma_buf* buf = NULL;
    int rc = -ETIME;

    mutex_lock(&mbr->lock);
    swap(buf, mbr->buf);

    if (!buf) {
        goto exit_on_req;
    }

    rc = dma_buf_fd(buf, O_CLOEXEC);
    if (rc < 0) {
        HWCAM_CFG_ERR("failed to mount buffer for request(0x%p)! \n", pintf);
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
hwcam_cfgpipeline_mount_buf_req_on_cancel(
        hwcam_cfgreq_intf_t* pintf,
        int reason)
{
    hwcam_cfgpipeline_mount_buf_req_t* mbr = I2PMBR(pintf);
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
hwcam_cfgpipeline_mount_buf_req_on_ack(
        hwcam_cfgreq_intf_t* pintf,
        hwcam_cfgack_t* ack)
{
    hwcam_cfgpipeline_mount_buf_req_t* mbr = I2PMBR(pintf);

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
    .get = hwcam_cfgpipeline_mount_buf_req_get,
    .put = hwcam_cfgpipeline_mount_buf_req_put,
    .on_req = hwcam_cfgpipeline_mount_buf_req_on_req,
    .on_cancel = hwcam_cfgpipeline_mount_buf_req_on_cancel,
    .on_ack = hwcam_cfgpipeline_mount_buf_req_on_ack,
};

static int
hwcam_cfgpipeline_mount_buf_req_create_instance(
        hwcam_buf_info_t* buf,
        hwcam_cfgpipeline_mount_buf_req_t** req)
{
    int rc = 0;
    hwcam_cfgpipeline_mount_buf_req_t* mbr = kzalloc(
            sizeof(hwcam_cfgpipeline_mount_buf_req_t), GFP_KERNEL);
    *req = NULL;

    if (mbr == NULL) {
        HWCAM_CFG_ERR("out of memory! \n");
        rc = -ENOMEM;
        goto exit_create_instance;
    }

    mbr->buf = dma_buf_get(buf->fd);
    if (IS_ERR_OR_NULL(mbr->buf)) {
        kzfree(mbr);
        HWCAM_CFG_ERR("invalid file handle(%d)! \n", buf->fd);
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
hwcam_cfgpipeline_mount_buf_req_release(
        struct kref* r)
{
    hwcam_cfgpipeline_mount_buf_req_t* mbr = REF2PMBR(r) ;

    hwcam_cfgpipeline_mount_buf_req_on_cancel(&mbr->intf, -ENOENT);

    kzfree(mbr);
}

static int
hwcam_cfgpipeline_mount_unmount_buf(
        hwcam_cfgpipeline_intf_t* intf,
        hwcam_user_intf_t* user,
        hwcam_buf_info_t* buf,
        int mount)
{
    hwcam_cfgpipeline_t* pl = I2PL(intf);
    int rc = -ENOMEM;
    int ack = 0;
    struct v4l2_event ev =
    {
        .type = HWCAM_V4L2_EVENT_TYPE,
        .id = HWCAM_CFGPIPELINE_REQUEST,
    };
    hwcam_cfgreq2pipeline_t* req = (hwcam_cfgreq2pipeline_t*)ev.u.data;
    hwcam_cfgpipeline_mount_buf_req_t* mbr = NULL;

    rc = hwcam_cfgpipeline_mount_buf_req_create_instance(buf, &mbr);
    if (!mbr) {
        goto exit_on_req;
    }

    req->req.intf = &mbr->intf;
    req->kind = mount
        ? HWCAM_CFGPIPELINE_REQ_MOUNT_BUF
        : HWCAM_CFGPIPELINE_REQ_UNMOUNT_BUF;
    req->buf = *buf;

    rc = hwcam_cfgdev_send_req(user, &ev, &pl->rq, 0, &ack);

    hwcam_cfgreq_intf_put(&mbr->intf);

exit_on_req:
    return rc? rc: ack;
}

static int
hwcam_cfgpipeline_mount_buf(
        hwcam_cfgpipeline_intf_t* intf,
        hwcam_user_intf_t* user,
        hwcam_buf_info_t* buf)
{
    return hwcam_cfgpipeline_mount_unmount_buf(
            intf, user, buf, 1);
}

static int
hwcam_cfgpipeline_unmount_buf(
        hwcam_cfgpipeline_intf_t* intf,
        hwcam_user_intf_t* user,
        hwcam_buf_info_t* buf)
{
    return hwcam_cfgpipeline_mount_unmount_buf(
            intf, user, buf, 0);
}

typedef struct _tag_hwcam_cfgpipeline_fmt_req
{
    struct mutex                                lock;
    struct kref                                 ref;
    hwcam_cfgreq_intf_t                         intf;
    unsigned                                    canceled : 1;
    unsigned                                    finished : 1;

    hwcam_cfgpipeline_t*                        pl;
    struct v4l2_fmtdesc*                        fd;
} hwcam_cfgpipeline_fmt_req_t;

#define I2PFR(i) container_of(i, hwcam_cfgpipeline_fmt_req_t, intf)

#define REF2PFR(r) container_of(r, hwcam_cfgpipeline_fmt_req_t, ref)

static void
hwcam_cfgpipeline_fmt_req_release(
        struct kref* r);

static void
hwcam_cfgpipeline_fmt_req_get(
        hwcam_cfgreq_intf_t* pintf)
{
    hwcam_cfgpipeline_fmt_req_t* pfr = I2PFR(pintf);
    kref_get(&pfr->ref);
}

static int
hwcam_cfgpipeline_fmt_req_put(
        hwcam_cfgreq_intf_t* pintf)
{
    hwcam_cfgpipeline_fmt_req_t* pfr = I2PFR(pintf);
    return kref_put(&pfr->ref, hwcam_cfgpipeline_fmt_req_release);
}

static int
hwcam_cfgpipeline_fmt_req_on_req(
        hwcam_cfgreq_intf_t* pintf,
        struct v4l2_event* ev)
{
    int rc = 0;
    hwcam_cfgpipeline_fmt_req_t* pfr = I2PFR(pintf);
    mutex_lock(&pfr->lock);

    if (pfr->canceled) {
        rc = -EINVAL;
        goto exit_on_req;
    }

    pfr->finished = 1;
    rc = 0;

exit_on_req:
    mutex_unlock(&pfr->lock);
    return rc;
}

static int
hwcam_cfgpipeline_fmt_req_on_cancel(
        hwcam_cfgreq_intf_t* pintf,
        int reason)
{
    hwcam_cfgpipeline_fmt_req_t* pfr = I2PFR(pintf);
    int rc = 0;

    mutex_lock(&pfr->lock);

    if (pfr->finished || pfr->canceled) {
        goto exit_on_canceled;
    }

    pfr->canceled = 1;
    rc = reason;

exit_on_canceled:
    mutex_unlock(&pfr->lock);
    return rc;
}

static int
hwcam_cfgpipeline_fmt_req_on_ack(
        hwcam_cfgreq_intf_t* pintf,
        hwcam_cfgack_t* ack)
{
    hwcam_cfgpipeline_fmt_req_t* pfr = I2PFR(pintf);

    mutex_lock(&pfr->lock);
    if (hwcam_cfgack_result(ack)) {
        HWCAM_CFG_ERR("request(0x%p) failed! \n", pintf);
    }
    mutex_unlock(&pfr->lock);
    return 0;
}

static hwcam_cfgreq_vtbl_t
s_vtbl_req_fmt =
{
    .get = hwcam_cfgpipeline_fmt_req_get,
    .put = hwcam_cfgpipeline_fmt_req_put,
    .on_req = hwcam_cfgpipeline_fmt_req_on_req,
    .on_cancel = hwcam_cfgpipeline_fmt_req_on_cancel,
    .on_ack = hwcam_cfgpipeline_fmt_req_on_ack,
};

static int
hwcam_cfgpipeline_fmt_req_create_instance(
        hwcam_cfgpipeline_t* pl,
        struct v4l2_fmtdesc* fd,
        hwcam_cfgpipeline_fmt_req_t** req)
{
    int rc = 0;
    hwcam_cfgpipeline_fmt_req_t* pfr = kzalloc(
            sizeof(hwcam_cfgpipeline_fmt_req_t), GFP_KERNEL);
    *req = NULL;

    if (pfr == NULL) {
        HWCAM_CFG_ERR("out of memory! \n");
        rc = -ENOMEM;
        goto exit_on_req;
    }

    mutex_init(&pfr->lock);
    kref_init(&pfr->ref);
    pfr->intf.vtbl = &s_vtbl_req_fmt;
    pfr->canceled = 0;
    pfr->finished = 0;

    pfr->pl = pl;
    pfr->fd = fd;

    *req = pfr;

exit_on_req:
    return rc;
}

static void
hwcam_cfgpipeline_fmt_req_release(
        struct kref* r)
{
    hwcam_cfgpipeline_fmt_req_t* pfr = REF2PFR(r) ;

    hwcam_cfgpipeline_fmt_req_on_cancel(&pfr->intf, -ENOENT);

    kzfree(pfr);
}

static int
hwcam_cfgpipeline_enum_fmt(
        hwcam_cfgpipeline_intf_t* intf,
        hwcam_user_intf_t* user,
        struct v4l2_fmtdesc* fd)
{
    hwcam_cfgpipeline_t* pl = I2PL(intf);
    int rc = -EINVAL;
    int ack = 0;
    struct v4l2_event ev =
    {
        .type = HWCAM_V4L2_EVENT_TYPE,
        .id = HWCAM_CFGPIPELINE_REQUEST,
    };
    hwcam_cfgreq2pipeline_t* req = (hwcam_cfgreq2pipeline_t*)ev.u.data;
    hwcam_cfgpipeline_fmt_req_t* fr = NULL;

    rc = hwcam_cfgpipeline_fmt_req_create_instance(pl, fd, &fr);
    if (!fr) {
        goto exit_enum_fmt;
    }

    req->req.intf = &fr->intf;
    req->kind = HWCAM_CFGPIPELINE_REQ_ENUM_FMT;

    rc = hwcam_cfgdev_send_req(user, &ev, &pl->rq, 0, &ack);

    hwcam_cfgreq_intf_put(&fr->intf);

exit_enum_fmt:
    return rc? rc: ack;
}

static int
hwcam_cfgpipeline_query_cap(
        hwcam_cfgpipeline_intf_t* intf,
        hwcam_user_intf_t* user)
{
    hwcam_cfgpipeline_t* pl = I2PL(intf);
    int rc = -EINVAL;
    int ack = 0;
    struct v4l2_event ev =
    {
        .type = HWCAM_V4L2_EVENT_TYPE,
        .id = HWCAM_CFGPIPELINE_REQUEST,
    };
    hwcam_cfgreq2pipeline_t* req = (hwcam_cfgreq2pipeline_t*)ev.u.data;

    req->req.intf = NULL;
    req->kind = HWCAM_CFGPIPELINE_REQ_QUERY_CAPABILITY;

    rc = hwcam_cfgdev_send_req(user, &ev, &pl->rq, 0, &ack);
    return rc? rc: ack;
}

static int
hwcam_cfgpipeline_query_param(
        hwcam_cfgpipeline_intf_t* intf,
        hwcam_user_intf_t* user)
{
    hwcam_cfgpipeline_t* pl = I2PL(intf);
    int rc = -EINVAL;
    int ack = 0;
    struct v4l2_event ev =
    {
        .type = HWCAM_V4L2_EVENT_TYPE,
        .id = HWCAM_CFGPIPELINE_REQUEST,
    };
    hwcam_cfgreq2pipeline_t* req = (hwcam_cfgreq2pipeline_t*)ev.u.data;

    req->req.intf = NULL;
    req->kind = HWCAM_CFGPIPELINE_REQ_QUERY_PARAM;

    rc = hwcam_cfgdev_send_req(user, &ev, &pl->rq, 0, &ack);
    return rc? rc: ack;
}

static int
hwcam_cfgpipeline_change_param(
        hwcam_cfgpipeline_intf_t* intf,
        hwcam_user_intf_t* user)
{
    hwcam_cfgpipeline_t* pl = I2PL(intf);
    int rc = -EINVAL;
    int ack = 0;
    struct v4l2_event ev =
    {
        .type = HWCAM_V4L2_EVENT_TYPE,
        .id = HWCAM_CFGPIPELINE_REQUEST,
    };
    hwcam_cfgreq2pipeline_t* req = (hwcam_cfgreq2pipeline_t*)ev.u.data;

    req->req.intf = NULL;
    req->kind = HWCAM_CFGPIPELINE_REQ_CHANGE_PARAM;

    rc = hwcam_cfgdev_send_req(user, &ev, &pl->rq, 0, &ack);
    return rc? rc: ack;
}

static hwcam_cfgpipeline_vtbl_t
s_vtbl_cfgpipeline =
{
    .get = hwcam_cfgpipeline_get,
    .put = hwcam_cfgpipeline_put,
    .umount = hwcam_cfgpipeline_umount,

    .mount_buf = hwcam_cfgpipeline_mount_buf,
    .unmount_buf = hwcam_cfgpipeline_unmount_buf,

    .enum_fmt = hwcam_cfgpipeline_enum_fmt,
    .query_cap = hwcam_cfgpipeline_query_cap,

    .query_param = hwcam_cfgpipeline_query_param,
    .change_param = hwcam_cfgpipeline_change_param,
    .mount_stream = hwcam_cfgpipeline_mount_stream,
};

static long
hwcam_cfgpipeline_vo_dqevent(
        hwcam_cfgpipeline_t* pl,
        struct v4l2_event* ev,
        int nb)
{
    long rc = 0;
    hwcam_cfgreq_t* req = NULL;
    while (true) {
        rc = v4l2_event_dequeue(&pl->rq, ev, nb);
        if (rc != 0) { break; }

        req = (hwcam_cfgreq_t*)ev->u.data;
        if (req->intf) {
            rc = hwcam_cfgreq_intf_on_req(req->intf, ev);
            hwcam_cfgreq_intf_put(req->intf);
            if (rc) {
                HWCAM_CFG_ERR("request(0x%p, 0x%08x, %u) skipped. \n",
                        req->intf, (*(unsigned*)(req + 1)), req->seq);
                continue;   // to skip failed/timeouted/interrupted events
            }
        }
        break;
    }
    return rc;
}

static long
hwcam_cfgpipeline_vo_notify(
        hwcam_cfgpipeline_t* pl,
        struct v4l2_event* ev)
{
    hwcam_dev_intf_notify(pl->cam, ev);
    return 0;
}

static long
hwcam_cfgpipeline_vo_mount_buf(
        hwcam_cfgpipeline_t* cam,
        hwcam_buf_info_t* bi)
{
    long rc = -EINVAL;

    switch (bi->kind)
    {
    case HWCAM_BUF_KIND_PIPELINE_CAPABILITY:
        break;
    case HWCAM_BUF_KIND_PIPELINE_PARAM:
        break;
    default:
        HWCAM_CFG_ERR("invalid buffer kind(%d)! \n", bi->kind);
        break;
    }
    return rc;
}

static long
hwcam_cfgpipeline_vo_unmount_buf(
        hwcam_cfgpipeline_t* cam,
        hwcam_buf_info_t* bi)
{
    long rc = -EINVAL;

    switch (bi->kind)
    {
    case HWCAM_BUF_KIND_PIPELINE_CAPABILITY:
        break;
    case HWCAM_BUF_KIND_PIPELINE_PARAM:
        break;
    default:
        HWCAM_CFG_ERR("invalid buffer kind(%d)! \n", bi->kind);
        break;
    }
    return rc;
}

static void
hwcam_cfgpipeline_subscribed_event_ops_merge(
        const struct v4l2_event* old,
        struct v4l2_event* new)
{
    hwcam_cfgreq2pipeline_t* req = (hwcam_cfgreq2pipeline_t*)&old->u.data;
    if (req->req.intf) {
        hwcam_cfgreq_intf_put(req->req.intf);
    }
    HWCAM_CFG_ERR("the event queue overflowed! \n");
}

static struct v4l2_subscribed_event_ops
s_hwcam_subscribed_event_ops =
{
    .merge = hwcam_cfgpipeline_subscribed_event_ops_merge,
};

static long
hwcam_cfgpipeline_vo_do_ioctl(
        struct file* filep,
        unsigned int cmd,
        void* arg)
{
    hwcam_cfgpipeline_t* pl = I2PL(filep->private_data);
	int rc = -EINVAL;
    if (!pl) {
        HWCAM_CFG_ERR("%s(%d): pl is NULL!", __func__, __LINE__);
        return -EINVAL;
    }

    switch (cmd)
    {
    case VIDIOC_DQEVENT:
        rc = hwcam_cfgpipeline_vo_dqevent(pl,
                arg, filep->f_flags & O_NONBLOCK);
        break;
    case HWCAM_V4L2_IOCTL_NOTIFY:
        rc = hwcam_cfgpipeline_vo_notify(pl,
                (struct v4l2_event*)arg);
        break;
    case HWCAM_V4L2_IOCTL_MOUNT_BUF:
        rc = hwcam_cfgpipeline_vo_mount_buf(pl,
                (hwcam_buf_info_t*)arg);
        break;
    case HWCAM_V4L2_IOCTL_UNMOUNT_BUF:
        rc = hwcam_cfgpipeline_vo_unmount_buf(pl,
                (hwcam_buf_info_t*)arg);
        break;
    case VIDIOC_SUBSCRIBE_EVENT:
        rc = v4l2_event_subscribe(&pl->rq,
                (struct v4l2_event_subscription*)arg, 8,
                &s_hwcam_subscribed_event_ops);
        break;
    case VIDIOC_UNSUBSCRIBE_EVENT:
        rc = v4l2_event_unsubscribe(&pl->rq,
                (struct v4l2_event_subscription*)arg);
        break;
    case HWCAM_V4L2_IOCTL_REQUEST_ACK:
        rc = hwcam_cfgdev_queue_ack((struct v4l2_event*)arg);
        break;
    default:
        HWCAM_CFG_ERR("invalid IOCTL CMD(%d)! \n", cmd);
        break;
    }
    return rc;
}

static unsigned int
hwcam_cfgpipeline_vo_poll(
        struct file* filep,
        struct poll_table_struct* ptbl)
{
	unsigned int rc = 0;
    hwcam_cfgdev_lock();
    {
        void* pd = filep->private_data;
        if (pd) {
            hwcam_cfgpipeline_t* pl = I2PL(pd);
            poll_wait(filep, &pl->rq.wait, ptbl);
            if (v4l2_event_pending(&pl->rq)) {
                rc = POLLIN | POLLRDNORM;
            }
        }
    }
    hwcam_cfgdev_unlock();
	return rc;
}

static long
hwcam_cfgpipeline_vo_ioctl(
        struct file* filep,
        unsigned int cmd,
        unsigned long arg)
{
    int rc = 0;
    hwcam_cfgdev_lock();
    {
        rc = video_usercopy(filep, cmd, arg,
                hwcam_cfgpipeline_vo_do_ioctl);
    }
    hwcam_cfgdev_unlock();
    return rc;
}

#ifdef CONFIG_COMPAT

static long
hwcam_cfgpipeline_vo_ioctl32(
        struct file* filep,
        unsigned int cmd,
        unsigned long arg)
{
    long rc = 0;
    void __user *up = NULL;
    void __user *kp = NULL;
    up = compat_ptr(arg);

	switch (cmd)
	{
	case VIDIOC_DQEVENT32: cmd = VIDIOC_DQEVENT; break;
	case HWCAM_V4L2_IOCTL_REQUEST_ACK32: cmd = HWCAM_V4L2_IOCTL_REQUEST_ACK; break;
	case HWCAM_V4L2_IOCTL_NOTIFY32: cmd = HWCAM_V4L2_IOCTL_NOTIFY; break;
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
			rc = hwcam_cfgpipeline_vo_ioctl(filep, cmd, (unsigned long)(kp));
			if (0 != rc)
				return rc;
			rc = compat_put_v4l2_event_data(kp, up);
		}
		break;
    default:
        rc = hwcam_cfgpipeline_vo_ioctl(filep, cmd, arg);
        break;
    }
    return rc;
}
#endif

static int
hwcam_cfgpipeline_vo_close(
        struct inode* i,
        struct file* filep)
{
    void* pd = NULL;
    swap(pd, filep->private_data);
    if (pd) {
        hwcam_cfgpipeline_t* pl = I2PL(pd);

        HWCAM_CFG_DEBUG("instance(0x%p)", &pl->intf);

        hwcam_cfgpipeline_on_closed(pl);

        hwcam_cfgdev_lock();
        {
            v4l2_fh_del(&pl->rq);
            v4l2_fh_exit(&pl->rq);
        }
        hwcam_cfgdev_unlock();

        hwcam_cfgpipeline_intf_put(&pl->intf);
    }

    return 0;
}

static struct file_operations
s_fops_cfgpipeline =
{
    .poll = hwcam_cfgpipeline_vo_poll,
    .unlocked_ioctl = hwcam_cfgpipeline_vo_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl = hwcam_cfgpipeline_vo_ioctl32,
#endif
    .release = hwcam_cfgpipeline_vo_close,
};

static void
hwcam_cfgpipeline_mount_req_get(
        hwcam_cfgreq_intf_t* pintf)
{
    hwcam_cfgpipeline_mount_req_t* mpr = I2MPR(pintf);
    kref_get(&mpr->ref);
}

static int
hwcam_cfgpipeline_mount_req_put(
        hwcam_cfgreq_intf_t* pintf)
{
    hwcam_cfgpipeline_mount_req_t* mpr = I2MPR(pintf);
    return kref_put(&mpr->ref, hwcam_cfgpipeline_mount_req_release);
}

static int
hwcam_cfgpipeline_mount_req_on_req(
        hwcam_cfgreq_intf_t* pintf,
        struct v4l2_event* ev)
{
    int rc = 0;
    hwcam_cfgpipeline_mount_req_t* mpr = I2MPR(pintf);
    hwcam_cfgreq2dev_t* req = (hwcam_cfgreq2dev_t*)&ev->u.data;
    hwcam_cfgpipeline_t* plo = NULL;

    mutex_lock(&mpr->lock);
    if (mpr->canceled) {
        goto exit_on_req;
    }

    mpr->pipeline = hwcam_cfgpipeline_find_by_device(mpr->cam);
    if (mpr->pipeline) {
        HWCAM_CFG_INFO("the pipeline had been mounted!");
        rc = 0;
        req->req.rc = 0;
        hwcam_cfgdev_queue_ack(ev);
        goto exit_on_req;
    }

    plo = hwcam_cfgpipeline_create_instance(mpr);
    if (plo == NULL) {
        HWCAM_CFG_ERR("failed to create pipeline!");
        rc = -ENOMEM;
        req->req.rc = -ENOMEM;
        mpr->pipeline = NULL;
        hwcam_cfgdev_queue_ack(ev);
        goto exit_on_req;
    }

    rc = anon_inode_getfd("hwcam.cfg.pipeline",
            &s_fops_cfgpipeline, &plo->intf, O_CLOEXEC);
    if (rc < 0) {
        HWCAM_CFG_ERR("failed to mount pipeline!");
        hwcam_cfgpipeline_intf_put(&plo->intf);
        req->req.rc = rc;
        mpr->pipeline = NULL;
        hwcam_cfgdev_queue_ack(ev);
        goto exit_on_req;
    }

	v4l2_fh_init(&plo->rq, mpr->vdev);
    v4l2_fh_add(&plo->rq);

    req->pipeline.fd = rc;
    req->pipeline.moduleID = mpr->moduleID;
    mpr->pipeline = &plo->intf;
    hwcam_cfgpipeline_intf_get(mpr->pipeline);

    hwcam_cfgpipeline_on_opened(plo);

    mpr->finished = 1;
    rc = 0;

exit_on_req:
    mutex_unlock(&mpr->lock);
    return rc;
}

static int
hwcam_cfgpipeline_mount_req_on_cancel(
        hwcam_cfgreq_intf_t* pintf,
        int reason)
{
    hwcam_cfgpipeline_mount_req_t* mpr = I2MPR(pintf);
    int rc = 0;

    mutex_lock(&mpr->lock);

    if (mpr->finished || mpr->canceled) {
        goto exit_on_canceled;
    }

    mpr->canceled = 1;
    rc = reason;

exit_on_canceled:
    mutex_unlock(&mpr->lock);
    return rc;
}

static int
hwcam_cfgpipeline_mount_req_on_ack(
        hwcam_cfgreq_intf_t* pintf,
        hwcam_cfgack_t* ack)
{
    hwcam_cfgpipeline_mount_req_t* mpr = I2MPR(pintf);

    mutex_lock(&mpr->lock);
    if (hwcam_cfgack_result(ack)) {
        HWCAM_CFG_ERR("request(0x%p) failed! \n", pintf);
    }
    mutex_unlock(&mpr->lock);
    return 0;
}

static void
hwcam_cfgpipeline_mount_req_get_result(
        hwcam_cfgreq_mount_pipeline_intf_t* pintf,
        hwcam_cfgpipeline_intf_t** pl)
{
    hwcam_cfgpipeline_mount_req_t* mpr = I2MPR((hwcam_cfgreq_intf_t*)pintf);

    mutex_lock(&mpr->lock);
    *pl = mpr->pipeline;
    if (*pl) {
        hwcam_cfgpipeline_intf_get(*pl);
    }
    mutex_unlock(&mpr->lock);
}

static hwcam_cfgreq_mount_pipeline_vtbl_t
s_vtbl_req_mount_pipeline =
{
    .base = {
        .get = hwcam_cfgpipeline_mount_req_get,
        .put = hwcam_cfgpipeline_mount_req_put,
        .on_req = hwcam_cfgpipeline_mount_req_on_req,
        .on_cancel = hwcam_cfgpipeline_mount_req_on_cancel,
        .on_ack = hwcam_cfgpipeline_mount_req_on_ack,
    },
    .get_result = hwcam_cfgpipeline_mount_req_get_result,
};

int
hwcam_cfgpipeline_mount_req_create_instance(
        struct video_device* vdev,
        hwcam_dev_intf_t* cam,
        int moduleID,
        hwcam_cfgreq_mount_pipeline_intf_t** req)
{
    int rc = 0;
    hwcam_cfgpipeline_mount_req_t* mpr = kzalloc(
            sizeof(hwcam_cfgpipeline_mount_req_t), GFP_KERNEL);
    *req = NULL;

    if (mpr == NULL) {
        HWCAM_CFG_ERR("out of memory! \n");
        rc = -ENOMEM;
        goto exit_create_instance;
    }

    mutex_init(&mpr->lock);
    kref_init(&mpr->ref);
    mpr->intf.vtbl = (hwcam_cfgreq_vtbl_t*)&s_vtbl_req_mount_pipeline;
    mpr->canceled = 0;
    mpr->finished = 0;

    mpr->vdev = vdev;
    mpr->cam = cam;
    mpr->moduleID = moduleID;

    *req = (hwcam_cfgreq_mount_pipeline_intf_t*)&mpr->intf;

exit_create_instance:
    return rc;
}

static void
hwcam_cfgpipeline_mount_req_release(
        struct kref* r)
{
    hwcam_cfgpipeline_mount_req_t* mpr = REF2MPR(r);

    hwcam_cfgpipeline_mount_req_on_cancel(&mpr->intf, -ENOENT);

    if (mpr->pipeline) {
        hwcam_cfgpipeline_intf_put(mpr->pipeline);
    }

    kzfree(mpr);
}

