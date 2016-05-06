


#include <linux/anon_inodes.h>
#include <linux/compiler.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/videodev2.h>
#include <media/huawei/isp_cfg.h>
#include <media/v4l2-event.h>
#include <media/v4l2-fh.h>
#include <media/v4l2-ioctl.h>
#include <media/v4l2-subdev.h>
#include <media/videobuf2-core.h>

#include "hwcam_compat32.h"
#include "hwisp_intf.h"
#include "ovisp2.3/isp_ops.h"

#define CREATE_TRACE_POINTS
#include "trace_hwisp.h"
/*
typedef struct _tag_hwisp_stream
{
    struct v4l2_fh                              rq;

    hwisp_stream_intf_t                         intf;
    struct kref                                 ref;
    struct list_head	                        node;
    struct mutex                                lock;

    unsigned long                               stream_type : 2;
    unsigned long                               stream_direction : 2;
    ovisp23_port_info_t                       port;

    hwisp_intf_t*                               isp;

    spinlock_t                                  lock_bufq;
    struct list_head                            bufq_invalid;
    struct list_head                            bufq_idle;
    struct list_head                            bufq_busy;
    struct list_head                            bufq_done;
    struct list_head                            bufq_user;
    hwisp_buf_t                                 buf[0];
} hwisp_stream_t;
*/
#define I2STM(i) container_of(i, hwisp_stream_t, intf)

#define REF2STM(r) container_of(r, hwisp_stream_t, ref)

#define NODE2STM(n) container_of(n, hwisp_stream_t, node)

#define ISP_STREAM_BUFFER_LEAST 4

static void
hwisp_stream_release(
        struct kref* r)
{
    hwisp_stream_t* stm = REF2STM(r);
    hwisp_intf_t* isp = NULL;
	u32 index = 0;
	void *vaddr = NULL;
	struct ion_handle *hdl = NULL;

    HWCAM_CFG_INFO("instance(0x%p) type=%ld, port=%d", stm, stm->stream_type, stm->port.id);

	if (stm->port.id == ISP_PORT_VC0 && !IS_ERR_OR_NULL(stm->ion_vc)) {
		HWCAM_CFG_INFO("unmap stream vc buf count=%ld", stm->enque_buf_count);
		for (index=0; index < stm->enque_buf_count; index++) {
			swap(hdl, stm->buf[index].info.ion_vc_hdl);
			swap(vaddr, stm->buf[index].info.ion_vaddr);
			if (!IS_ERR_OR_NULL(hdl)) {
				ion_unmap_kernel(stm->ion_vc, hdl);
				ion_free(stm->ion_vc, hdl);
				HWCAM_CFG_INFO("unmap stream vc buf handle index=%d", index);
			}
		}

		ion_client_destroy(stm->ion_vc);
		stm->ion_vc = NULL;
	}

    swap(isp, stm->isp);

    stm->intf.vtbl = NULL;
    kzfree(stm);
}

static void
hwisp_stream_get(
        hwisp_stream_intf_t* intf)
{
    hwisp_stream_t* stm = I2STM(intf);
    kref_get(&stm->ref);
}

static int
hwisp_stream_put(
        hwisp_stream_intf_t* intf)
{
    hwisp_stream_t* stm = I2STM(intf);
    return kref_put(&stm->ref, hwisp_stream_release);
}

static inline int
hwisp_stream_start(hwisp_stream_intf_t* intf)
{
    hwisp_stream_t* stm = I2STM(intf);
    HWCAM_CFG_ERR("enter");
    hwisp_intf_stream_start(stm->isp, intf);
    return 0;
}
static inline int
hwisp_stream_stop(hwisp_stream_intf_t* intf)
{
    hwisp_stream_t* stm = I2STM(intf);
    hwisp_buf_t* ret = NULL;
    unsigned long flags;
    HWCAM_CFG_ERR("enter");
    hwisp_intf_stream_stop(stm->isp, intf);

    spin_lock_irqsave(&stm->lock_bufq, flags);
    while (!list_empty(&stm->bufq_idle)) {
        ret = list_first_entry(&stm->bufq_idle, hwisp_buf_t, node);
        list_move_tail(&ret->node, &stm->bufq_done);
    }
    while (!list_empty(&stm->bufq_busy)) {
        ret = list_first_entry(&stm->bufq_busy, hwisp_buf_t, node);
        list_move_tail(&ret->node, &stm->bufq_done);
    }
    spin_unlock_irqrestore(&stm->lock_bufq, flags);
    return 0;
}

static inline hwisp_buf_t*
hwisp_stream_get_buf(
        hwisp_stream_intf_t* intf)
{
    hwisp_stream_t* stm = I2STM(intf);
    hwisp_buf_t* ret = NULL;
    unsigned long flags;

    spin_lock_irqsave(&stm->lock_bufq, flags);
    if (!list_empty(&stm->bufq_idle)) {
        ret = list_first_entry(&stm->bufq_idle, hwisp_buf_t, node);
        list_move_tail(&ret->node, &stm->bufq_busy);
    }
    spin_unlock_irqrestore(&stm->lock_bufq, flags);

    return ret;
}

static inline int
hwisp_stream_put_buf(
        hwisp_stream_intf_t* intf,
        hwisp_buf_t* vb)
{
    hwisp_stream_t* stm = I2STM(intf);
    int rc = -EINVAL;
    hwisp_buf_t* entry = NULL;
    hwisp_buf_t* tmp = NULL;
    unsigned long flags;

    spin_lock_irqsave(&stm->lock_bufq, flags);
    list_for_each_entry_safe(entry, tmp, &stm->bufq_busy, node) {
        if (entry == vb) {
            list_move(&entry->node, &stm->bufq_idle);
            rc = 0;
            break;
        }
    }
    spin_unlock_irqrestore(&stm->lock_bufq, flags);

    return rc;
}

static inline int
hwisp_stream_buf_done(
        hwisp_stream_intf_t* intf,
        hwisp_buf_t* vb)
{
    hwisp_stream_t* stm = I2STM(intf);
    int rc = -EINVAL;
    hwisp_buf_t* entry = NULL;
    hwisp_buf_t* tmp = NULL;
    unsigned long flags;

    spin_lock_irqsave(&stm->lock_bufq, flags);
    list_for_each_entry_safe(entry, tmp, &stm->bufq_busy, node) {
        if (entry == vb) {
            list_move_tail(&entry->node, &stm->bufq_done);
            trace_hwisp_stream_buf_done(vb); 
            rc = 0;
            break;
        }
    }
    spin_unlock_irqrestore(&stm->lock_bufq, flags);

    if (entry) {
        wake_up_all(&stm->rq.wait);
    }

    return rc;
}

static hwisp_stream_vtbl_t
s_vtbl_ispstream =
{
    .get = hwisp_stream_get,
    .put = hwisp_stream_put,
    .start = hwisp_stream_start,
    .stop = hwisp_stream_stop,
    .get_buf = hwisp_stream_get_buf,
    .put_buf = hwisp_stream_put_buf,
    .buf_done = hwisp_stream_buf_done,
};

static long
hwisp_stream_vo_dqevent(
        hwisp_stream_t* stm,
        struct v4l2_event* ev,
        int nb)
{
    return v4l2_event_dequeue(&stm->rq, ev, nb);
}

static long
hwisp_stream_vo_prepare_buf(
        hwisp_stream_t* stm,
        hwisp_buf_t* buf)
{
	struct ion_handle* hdl = NULL;
	void *vaddr =  NULL;

	if (stm->port.id != ISP_PORT_VC0)
		return 0;

	HWCAM_CFG_INFO("ionfd=%d", buf->info.ion_fd);

	/* check arg */
	if ((buf->info.ion_fd <= 0) || IS_ERR_OR_NULL(stm->ion_vc)) {
		HWCAM_CFG_ERR("invalid ion: fd=%d, client=%p",
					buf->info.ion_fd, stm->ion_vc);
		return -EINVAL;
	}

	/* get hdl */
	hdl = ion_import_dma_buf(stm->ion_vc, buf->info.ion_fd);
	if (IS_ERR_OR_NULL(hdl)) {
		HWCAM_CFG_ERR("failed to create ion handle!");
		return PTR_ERR(hdl);
	}
	buf->info.ion_vc_hdl = hdl;

	/* map kernel addr */
	vaddr = ion_map_kernel(stm->ion_vc, hdl);
	if (IS_ERR_OR_NULL(vaddr)) {
		HWCAM_CFG_ERR("failed to map ion buffer(fd=%lx)!", (unsigned long)hdl);
		buf->info.ion_vc_hdl = NULL;
		buf->info.ion_vaddr = NULL;
		ion_free(stm->ion_vc, hdl);
		return PTR_ERR(vaddr);
	}
	HWCAM_CFG_INFO("ion map addr=0x%lx", (unsigned long)vaddr);
	buf->info.ion_vaddr= vaddr;

    return 0;
}

static long
hwisp_stream_vo_enqueue_buf(
        hwisp_stream_t* stm,
        hwisp_stream_buf_info_t* bi)
{
    long rc = -EINVAL;
    bool need_allocate = false;
    hwisp_buf_t* entry = NULL;
    hwisp_buf_t* tmp = NULL;
    unsigned long flags;

    //printk("enter %s\n",__func__);
    spin_lock_irqsave(&stm->lock_bufq, flags);
    list_for_each_entry_safe(entry, tmp, &stm->bufq_user, node) {
        if (entry->info.user_buffer_handle == bi->user_buffer_handle) {
            list_move_tail(&entry->node, &stm->bufq_idle);
            //up(&stm->buffer_readyQ);
            rc = 0;
            goto end;
        }
    }
    list_for_each_entry_safe(entry, tmp, &stm->bufq_done, node) {
        if (entry->info.user_buffer_handle == bi->user_buffer_handle) {
            list_move_tail(&entry->node, &stm->bufq_idle);
            //up(&stm->buffer_readyQ);
            rc = 0;
            goto end;
        }
    }
    list_for_each_entry_safe(entry, tmp, &stm->bufq_idle, node) {
        if (entry->info.user_buffer_handle == bi->user_buffer_handle) {
            goto end;
        }
    }
    list_for_each_entry_safe(entry, tmp, &stm->bufq_busy, node) {
        if (entry->info.user_buffer_handle == bi->user_buffer_handle) {
            goto end;
        }
    }
    need_allocate = true;
end:
    spin_unlock_irqrestore(&stm->lock_bufq, flags);
    if(rc == 0){
        if(stm->down_flag == 1)
          {
             up(&stm->buffer_readyQ);
             stm->down_flag = 0;
          }
            //wake_up(stm->wait);
    }
    if (need_allocate) {
        entry = list_first_entry(&stm->bufq_invalid, hwisp_buf_t, node);
        if (entry) {
            entry->info = *bi;
			rc = hwisp_stream_vo_prepare_buf(stm, entry);
			stm->enque_buf_count++;
            spin_lock_irqsave(&stm->lock_bufq, flags);
            list_move_tail(&entry->node, &stm->bufq_idle);
            spin_unlock_irqrestore(&stm->lock_bufq, flags);
        }
        else {
            HWCAM_CFG_ERR("no slot for buffer(0x%0lx)! \n",
                    (unsigned long)bi->user_buffer_handle);
        }
    }
    //printk("leave %s\n",__func__);
    return rc;
}

static long
hwisp_stream_vo_dequeue_buf(
        hwisp_stream_t* stm,
        hwisp_stream_buf_info_t* bi)
{
    long rc = -ENOENT;
    hwisp_buf_t* ret = NULL;
    unsigned long flags;

    spin_lock_irqsave(&stm->lock_bufq, flags);
    if (!list_empty(&stm->bufq_done)) {
        ret = list_first_entry(&stm->bufq_done, hwisp_buf_t, node);
        list_move_tail(&ret->node, &stm->bufq_user);
        memcpy(bi, &(ret->info), sizeof(hwisp_stream_buf_info_t));
        rc = 0;
    }
    spin_unlock_irqrestore(&stm->lock_bufq, flags);

    return rc;
}

static long
hwisp_stream_vo_do_ioctl(
        struct file* filep,
        unsigned int cmd,
        void* arg)
{
    long rc = -EINVAL;
    hwisp_stream_t* stm = I2STM(filep->private_data);
	BUG_ON(!filep->private_data);
    switch (cmd)
    {
    case VIDIOC_DQEVENT:
        rc = hwisp_stream_vo_dqevent(stm,
                arg, filep->f_flags & O_NONBLOCK);
        break;
    case HWISP_STREAM_IOCTL_ENQUEUE_BUF:
        rc = hwisp_stream_vo_enqueue_buf(stm, arg);
        break;
    case HWISP_STREAM_IOCTL_DEQUEUE_BUF:
        rc = hwisp_stream_vo_dequeue_buf(stm, arg);
        break;
    case HWISP_STREAM_IOCTL_START:
        rc = hwisp_stream_intf_start(&stm->intf);
        break;
    case HWISP_STREAM_IOCTL_STOP:
        rc = hwisp_stream_intf_stop(&stm->intf);
        break;
    case VIDIOC_SUBSCRIBE_EVENT:
        rc = v4l2_event_subscribe(&stm->rq, arg, VIDEO_MAX_FRAME,NULL);
        break;
    case VIDIOC_UNSUBSCRIBE_EVENT:
        rc = v4l2_event_unsubscribe(&stm->rq, arg);
        break;
    default:
        HWCAM_CFG_ERR("invalid IOCTL CMD(%d)! \n", cmd);
        break;
    }
    return rc;
}

static unsigned int
hwisp_stream_vo_poll(
        struct file* filep,
        struct poll_table_struct* ptbl)
{
	unsigned int rc = 0;
    hwisp_stream_t* stm = I2STM(filep->private_data);
    mutex_lock(&stm->lock);
    {
        unsigned long flags;

        poll_wait(filep, &stm->rq.wait, ptbl);

        spin_lock_irqsave(&stm->lock_bufq, flags);
        if (!list_empty(&stm->bufq_done)) {
            rc |= POLLIN | POLLRDNORM;
        }
        spin_unlock_irqrestore(&stm->lock_bufq, flags);

        if (v4l2_event_pending(&stm->rq)) {
            rc = POLLIN | POLLRDNORM;
        }
    }
    mutex_unlock(&stm->lock);
	return rc;
}

static long
hwisp_stream_vo_ioctl(
        struct file* filep,
        unsigned int cmd,
        unsigned long arg)
{
    int rc = 0;
    hwisp_stream_t* stm = I2STM(filep->private_data);
    mutex_lock(&stm->lock);
    {
        rc = video_usercopy(filep, cmd, arg,
                hwisp_stream_vo_do_ioctl);
    }
    mutex_unlock(&stm->lock);
    return rc;
}

#ifdef CONFIG_COMPAT
static long
hwisp_stream_vo_ioctl32(
        struct file* filep,
        unsigned int cmd,
        unsigned long arg)
{
    int rc = 0;
    void __user *up = NULL;
    void __user *kp = NULL;
    up = compat_ptr(arg);

    switch (cmd)
    {
    case VIDIOC_DQEVENT32: cmd = VIDIOC_DQEVENT; break;
    case HWISP_STREAM_IOCTL_ENQUEUE_BUF32: cmd = HWISP_STREAM_IOCTL_ENQUEUE_BUF; break;
    case HWISP_STREAM_IOCTL_DEQUEUE_BUF32: cmd = HWISP_STREAM_IOCTL_DEQUEUE_BUF; break;
	}

    switch (cmd)
    {
    case VIDIOC_DQEVENT:
         {
			kp = compat_alloc_user_space(sizeof(struct v4l2_event));
			if (NULL == kp)
				return -EFAULT;

			rc = compat_get_v4l2_event_data(kp, up);
			if (0 != rc)
				return rc;
			rc = hwisp_stream_vo_ioctl(filep, cmd, (unsigned long)kp);
			if (0 != rc)
				return rc;
			rc = compat_put_v4l2_event_data(kp, up);
			return rc;
		}
        break;
#if 0
    case HWISP_STREAM_IOCTL_ENQUEUE_BUF:
    case HWISP_STREAM_IOCTL_DEQUEUE_BUF:
         {
            kp = compat_alloc_user_space(sizeof(hwisp_stream_buf_info_t));
            if (NULL == kp)
                return -EFAULT;

            rc = compat_get_hwisp_stream_buf_info(kp, up);
            if (0 != rc)
                return rc;
            rc = hwisp_stream_vo_ioctl(filep, cmd, (unsigned long)kp);
            if (0 != rc)
                return rc;
            rc = compat_put_hwisp_stream_buf_info(kp, up);
            return rc;
        }
        break;
#endif        
    default:
        rc = hwisp_stream_vo_ioctl(filep, cmd, arg);
        break;
    }
    return rc;
}
#endif

static int
hwisp_stream_vo_close(
        struct inode* i,
        struct file* filep)
{
    void* pd = NULL;
    swap(pd, filep->private_data);
    if (pd) {
        hwisp_stream_t* stm = I2STM(pd);
        mutex_lock(&stm->lock);

        list_del_init(&stm->node);
        v4l2_fh_del(&stm->rq);
        v4l2_fh_exit(&stm->rq);

        mutex_unlock(&stm->lock);
        hwisp_stream_intf_put(&stm->intf);
    }
    return 0;
}

static struct file_operations
s_fops_hwisp_stream =
{
    .poll = hwisp_stream_vo_poll,
    .unlocked_ioctl = hwisp_stream_vo_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = hwisp_stream_vo_ioctl32,
#endif
    .release = hwisp_stream_vo_close,
};

hwisp_stream_intf_t*
hwisp_stream_get_by_node(
        struct list_head* node)
{
    hwisp_stream_t* stm = NODE2STM(node);
    if (node && stm->intf.vtbl == &s_vtbl_ispstream) {
        return &stm->intf;
    }
    else {
        return NULL;
    }
}

int
hwisp_create_stream(
        struct video_device* vdev,
        hwisp_intf_t* isp,
        hwisp_stream_info_t* si,
        struct list_head* streams)
{
    int ret = -1;
    hwisp_stream_t* stm = NULL;
    int i = 0;

    if (si->buf_queue_size < ISP_STREAM_BUFFER_LEAST) {
        si->buf_queue_size = ISP_STREAM_BUFFER_LEAST;
    }
    if (VIDEO_MAX_FRAME < si->buf_queue_size) {
        si->buf_queue_size = VIDEO_MAX_FRAME;
    }

    stm = kzalloc(si->buf_queue_size * sizeof(hwisp_buf_t)
            + sizeof(hwisp_stream_t), GFP_KERNEL);
    if (stm == NULL) {
        HWCAM_CFG_ERR("failed to create isp stream! \n");
        ret = -ENOMEM;
        goto end_create_stream;
    }

    stm->intf.vtbl = &s_vtbl_ispstream;
    kref_init(&stm->ref);
    mutex_init(&stm->lock);
    INIT_LIST_HEAD(&stm->node);

    stm->stream_type = si->stream_type;
    stm->stream_direction = si->stream_direction;
    //memcpy(&stm->port,&si->port,sizeof(ovisp-23_port_info_t));
    stm->port.id = si->portid;
    stm->port.pix_format = si->pix_format;
    stm->port.use_phy_memory = si->use_phy_memory;
    stm->isp = isp;
    stm->enque_buf_count = 0;

    if (si->portid == ISP_PORT_VC0) {
        stm->ion_vc = hisi_ion_client_create("hwcam-stream-vc0");
        if (IS_ERR_OR_NULL(stm->ion_vc)) {
            HWCAM_CFG_ERR("create ion err");
            i = PTR_ERR(stm->ion_vc);
            kfree(stm);
            return i;
        }
    }

    sema_init(&stm->buffer_readyQ, 0);

    spin_lock_init(&stm->lock_bufq);
    INIT_LIST_HEAD(&stm->bufq_invalid);
    INIT_LIST_HEAD(&stm->bufq_idle);
    INIT_LIST_HEAD(&stm->bufq_busy);
    INIT_LIST_HEAD(&stm->bufq_done);
    INIT_LIST_HEAD(&stm->bufq_user);
    for (i = 0; i < si->buf_queue_size; i++) {
        list_add_tail(&stm->buf[i].node, &stm->bufq_invalid);
    }

    ret = anon_inode_getfd("hwisp.stream",
            &s_fops_hwisp_stream, &stm->intf, O_CLOEXEC);
    if (ret < 0) {
        hwisp_stream_intf_put(&stm->intf);
        HWCAM_CFG_ERR("failed to mount isp stream! \n");
        goto end_create_stream;
    }
	v4l2_fh_init(&stm->rq, vdev);
    v4l2_fh_add(&stm->rq);

    list_add_tail(&stm->node, streams);

    si->fd_ispstream = ret;

    HWCAM_CFG_INFO("instance(0x%p) portid=%u", stm, stm->port.id);

end_create_stream:
    return ret;
}

