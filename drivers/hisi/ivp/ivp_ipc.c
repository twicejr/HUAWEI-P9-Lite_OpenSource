#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/semaphore.h>
#include <linux/mutex.h>
#include <linux/notifier.h>
#include <linux/hisi/hisi_rproc.h>
#include <linux/list.h>
#include <linux/atomic.h>
#include "ivp.h"
#include "ivp_log.h"

#define DEFAULT_MSG_SIZE    (32)

struct ivp_ipc_packet {
    char *buff;
    size_t len;
    struct list_head list;
};

struct ivp_ipc_queue {
    struct list_head head;

    spinlock_t rw_lock;
    struct semaphore r_lock;

    atomic_t flush;
};

struct ivp_ipc_device {
    struct miscdevice device;

    struct notifier_block recv_nb;
    struct ivp_ipc_queue recv_queue;

    rproc_id_t recv_ipc;
    rproc_id_t send_ipc;
};

extern struct ivp_ipc_device ivp_ipc_dev;

#ifdef CONFIG_OF
static const struct of_device_id ivp_ipc_of_descriptor[] = {
        {.compatible = "hisilicon,hisi-ivp-ipc",},
        {},
};
MODULE_DEVICE_TABLE(of, hisi_mdev_of_match);
#endif

/*======================================================================
 * IPC Pakcet Operations
 * include get, put, remove, replace
 ======================================================================*/
static inline struct ivp_ipc_packet *ivp_ipc_alloc_packet(size_t len)
{
    struct ivp_ipc_packet *packet = NULL;
    packet = kmalloc(sizeof(struct ivp_ipc_packet), GFP_ATOMIC);
    if (packet == NULL) {
        ivp_err("malloc packet fail.");
        return NULL;
    }

    packet->buff = kzalloc(sizeof(char) * len, GFP_ATOMIC);
    if (packet->buff == NULL) {
        ivp_err("malloc packet buf fail.");
        kfree(packet);
        packet = NULL;
        return NULL;
    }

    packet->len = len;
    return packet;
}

static inline void ivp_ipc_free_packet(struct ivp_ipc_packet *packet)
{
    if (packet == NULL) {
        ivp_warn("packet is NULL.");
        return;
    }

    if (packet->buff != NULL) {
        kfree(packet->buff);
        packet->buff = NULL;
    }
    kfree(packet);
    packet = NULL;
}

static inline void ivp_ipc_init_queue(struct ivp_ipc_queue *queue)
{
    spin_lock_init(&queue->rw_lock);
    sema_init(&queue->r_lock, 0);
    atomic_set(&queue->flush, 1);
    INIT_LIST_HEAD(&queue->head);
}

static struct ivp_ipc_packet *ivp_ipc_get_packet(struct ivp_ipc_queue *queue)
{
    struct ivp_ipc_packet *packet = NULL;
    ivp_dbg("get packet");
    spin_lock_irq(&queue->rw_lock);
    packet = list_first_entry_or_null(&queue->head, struct ivp_ipc_packet, list);
    spin_unlock_irq(&queue->rw_lock);
    return packet;
}

static int ivp_ipc_add_packet(struct ivp_ipc_queue *queue, void *data, size_t len)
{
    int ret = 0;
    struct ivp_ipc_packet *new_packet = NULL;
    new_packet = ivp_ipc_alloc_packet(len);
    ivp_dbg("enter");
    if (NULL == new_packet) {
        ivp_err("new packet NULL");
        ret = -ENOMEM;
        goto ipc_exit;
    }
    memcpy(new_packet->buff, data, len);
    spin_lock_irq(&queue->rw_lock);
    list_add_tail(&new_packet->list, &queue->head);
    spin_unlock_irq(&queue->rw_lock);
    up(&queue->r_lock);
ipc_exit:
    return ret;
}

static void ivp_ipc_remove_packet(struct ivp_ipc_queue *queue, struct ivp_ipc_packet *packet)
{
    spin_lock_irq(&queue->rw_lock);
	if (packet) {
		list_del(&packet->list);
	}
    spin_unlock_irq(&queue->rw_lock);
    ivp_ipc_free_packet(packet);
}

static void ivp_ipc_remove_all_packet(struct ivp_ipc_queue *queue)
{
    struct list_head *p = NULL, *n = NULL;

    list_for_each_safe(p, n, &queue->head) {
        struct ivp_ipc_packet *packet = list_entry(p, struct ivp_ipc_packet, list);
        ivp_ipc_remove_packet(queue, packet);
    }
}

static int ivp_ipc_open(struct inode *inode, struct file *file)
{
    int ret = nonseekable_open(inode, file);
    ivp_info("enter");
    if (ret != 0) {
        return ret;
    }
    file->private_data = (void *)&ivp_ipc_dev;

    if (unlikely(1 != atomic_read(&ivp_ipc_dev.recv_queue.flush))) {
        ivp_warn("Flush was not set when first open! %u", atomic_read(&(ivp_ipc_dev.recv_queue.flush)));
    }
    atomic_set(&ivp_ipc_dev.recv_queue.flush, 0);

    if (unlikely(!list_empty(&ivp_ipc_dev.recv_queue.head))) {
        ivp_warn("queue is not Empty!");
        ivp_ipc_remove_all_packet(&ivp_ipc_dev.recv_queue);
    }

    sema_init(&(ivp_ipc_dev.recv_queue.r_lock), 0);

    return ret;
}
/******************************************************************************************
 *  len:   msg len. data len is (len * sizeof(msg))
 ** ***************************************************************************************/
static int ivp_ipc_recv_notifier(struct notifier_block *nb, unsigned long len, void *data)
{
    struct ivp_ipc_device *pdev = NULL;
    int ret = 0;
    if (NULL == data || NULL == nb){
        ivp_err("data or nb is NULL");
        return -EINVAL;
    }
    if (0 >= len){
        ivp_err("len equals to or less than 0");
        return -EINVAL;
    }

    pdev = container_of(nb, struct ivp_ipc_device, recv_nb);
    if (NULL == pdev) {
        ivp_err("pdev NULL");
        return -EINVAL;
    }
    if (1 == atomic_read(&(pdev->recv_queue.flush))) {
        ivp_warn("flushed.No longer receive msg.");
        ret = -ECANCELED;
    }
    else {
        len *= 4;
        ret = ivp_ipc_add_packet(&pdev->recv_queue, data, len);
    }
    return ret;
}

static ssize_t ivp_ipc_read(struct file *file,
                        char __user *buff,
                        size_t size,
                        loff_t *off)
{
    char *curr_buff_ptr = NULL;
    struct ivp_ipc_device *pdev = (struct ivp_ipc_device *) file->private_data;
    struct ivp_ipc_queue *queue = &pdev->recv_queue;
    size_t bytesToRecv = size;
    struct ivp_ipc_packet *packet = NULL;
    long len = 0;
    if (NULL == buff) {
        ivp_err("buff is null!");
        return -EINVAL;
    }
    curr_buff_ptr = buff;
    ivp_dbg("enter");
    if (DEFAULT_MSG_SIZE != size) {
        ivp_err("Size should be 32Byte.size:%lu", size);
        return -EINVAL;
    }

    //Block until IVPCore send new Msg
    if (down_interruptible(&queue->r_lock)) {
        ivp_err("interrupted.");
        return -ERESTARTSYS;
    }

    if (1 == atomic_read(&queue->flush)) {
        ivp_info("flushed.");
        return -ECANCELED;
    }
    packet = ivp_ipc_get_packet(queue);
    if (packet != NULL) {
        {
            int i = 0;
            for (; i < 8; i++) {
                ivp_dbg("msg[%d]:%#lx", i, (unsigned long)(packet->buff + i * 4));
            }
        }
        len = copy_to_user(curr_buff_ptr, packet->buff, bytesToRecv);
        if (0 == len) {
            ivp_ipc_remove_packet(queue, packet);
        }
        else {
            ivp_err("Get %ld Byte, not %lu", len, bytesToRecv);
        }
    }
    else {
        ivp_err("get packet NULL");
    }
    ivp_dbg("leave");

    return len ? 0 : size;
}

static ssize_t ivp_ipc_write(struct file *file,
                        const char __user *buff,
                        size_t size,
                        loff_t *off)
{
    int len, ret = 0;
    struct ivp_ipc_device *pdev =
              (struct ivp_ipc_device *)file->private_data;
    char *tmp_buff = NULL;

    if (NULL == buff) {
        ivp_err("buff is null!");
        return -EINVAL;
    }

    if (size != DEFAULT_MSG_SIZE) {
        ivp_err("size %lu not %d.", size, DEFAULT_MSG_SIZE);
        return -EINVAL;
    }

    tmp_buff = kmalloc(size, GFP_KERNEL);

    ivp_dbg("enter size: %lu", size);
    if (tmp_buff == NULL) {
        ivp_err("malloc buf failed.");
        return -ENOMEM;
    }

    len = copy_from_user(tmp_buff, buff, size);

    if (len) {
        ivp_err("len: %d.", len);
        ret = -EFAULT;
        goto OUT;
    }

#if 0
{
    int i = 0;
    for (; i < size/sizeof(rproc_msg_len_t); i++) {
        ivp_dbg("mbox[%d]=%#x", i, *((u32 *)tmp_buff + i));
    }
}
#endif

    ret = RPROC_ASYNC_SEND(pdev->send_ipc, (rproc_msg_t *) tmp_buff, size/sizeof(rproc_msg_len_t));

    ivp_dbg("send finish");
    if (ret) {
        ivp_err("ipc send fail [%d].", ret);
    }
OUT:
    kfree(tmp_buff);
    tmp_buff = NULL;
    return ret ? -1 : size;
}

static int ivp_ipc_release(struct inode *inode, struct file *file)
{
    struct ivp_ipc_device *pdev = (struct ivp_ipc_device *)file->private_data;

    ivp_info("enter");
    //drop all packet
    ivp_ipc_remove_all_packet(&pdev->recv_queue);
    return 0;
}

static int ivp_ipc_flush(struct ivp_ipc_device *pdev)
{
    //non block read.Make read return HAL.
    int ret = 0;
    struct ivp_ipc_queue *queue = &pdev->recv_queue;
    ivp_info("enter");
    atomic_set(&queue->flush, 1);
    up(&queue->r_lock);
    ivp_ipc_remove_all_packet(queue);

    return ret;
}

static long ivp_ipc_ioctl(struct file *fd, unsigned int cmd, unsigned long args)
{
    int ret = 0;
    struct ivp_ipc_device *pdev = (struct ivp_ipc_device *)fd->private_data;
    ivp_info("cmd:%#x", cmd);

    ivp_dbg("IVP_IOCTL_IPC_FLUSH_ENABLE:%#lx", IVP_IOCTL_IPC_FLUSH_ENABLE);
    switch(cmd) {
        case IVP_IOCTL_IPC_FLUSH_ENABLE:
            ret = ivp_ipc_flush(pdev);
            break;
        default:
            ivp_warn("invalid cmd, %#x", cmd);
            ret = -EINVAL;
            break;
    }

    return ret;
}

static long ivp_ipc_ioctl32(struct file *fd, unsigned int cmd, unsigned long args)
{
    void *user_ptr = compat_ptr(args);
    return ivp_ipc_ioctl(fd, cmd, (unsigned long)user_ptr);
}

static struct file_operations ivp_ipc_fops = {
    .owner = THIS_MODULE,
    .open = ivp_ipc_open,
    .read = ivp_ipc_read,
    .write = ivp_ipc_write,
    .release = ivp_ipc_release,
    .unlocked_ioctl = ivp_ipc_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl = ivp_ipc_ioctl32,
#endif
};

struct ivp_ipc_device ivp_ipc_dev = {
    .device = {
        .minor = MISC_DYNAMIC_MINOR,
        .name = "ivp-ipc",
        .fops = &ivp_ipc_fops,
    },
    .send_ipc = HISI_RPROC_IVP_MBX25,
    .recv_ipc = HISI_RPROC_IVP_MBX5,
};

static inline void ivp_ipc_init_recv_nb(struct notifier_block *nb)
{
    nb->notifier_call = ivp_ipc_recv_notifier;
}

static int ivp_ipc_probe(struct platform_device *platform_pdev)
{
    int ret = 0;
    struct ivp_ipc_device *pdev = &ivp_ipc_dev;
    ret = misc_register(&pdev->device);
    if (ret < 0) {
        ivp_err("Failed to register misc device.");
        return ret;
    }
    ret = RPROC_MONITOR_REGISTER((unsigned char)ivp_ipc_dev.recv_ipc, &ivp_ipc_dev.recv_nb);
    if (ret < 0) {
        ivp_err("Failed to create receiving notifier block");
        goto err_out;
    }

    ivp_ipc_init_queue(&pdev->recv_queue);

    ivp_ipc_init_recv_nb(&pdev->recv_nb);

    platform_set_drvdata(platform_pdev, pdev);
    return ret;

err_out:
    misc_deregister(&pdev->device);
    return ret;
}

static int ivp_ipc_remove(struct platform_device *plat_devp)
{
    RPROC_MONITOR_UNREGISTER((unsigned char)ivp_ipc_dev.recv_ipc, &ivp_ipc_dev.recv_nb);
    misc_deregister(&ivp_ipc_dev.device);
    return 0;
}

static struct platform_driver ivp_ipc_driver = {
    .probe = ivp_ipc_probe,
    .remove = ivp_ipc_remove,
    .driver = {
        .name = "ivp-ipc",
        .owner = THIS_MODULE,
#ifdef CONFIG_OF
        .of_match_table = of_match_ptr(ivp_ipc_of_descriptor),
#endif
    },
};

module_platform_driver(ivp_ipc_driver);
MODULE_LICENSE("GPL");
