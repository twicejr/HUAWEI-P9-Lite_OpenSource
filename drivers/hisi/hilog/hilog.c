/* Copyright (c) 2008-2015, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#include <linux/sched.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/poll.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <linux/vmalloc.h>
#include <linux/aio.h>
#include <linux/ctype.h>
#include <linux/types.h>
#include <linux/ioctl.h>
#include <asm/ioctls.h>
#include <linux/hardirq.h>

#include <hisi/hilog.h>

/* the file node name which can access in user space */
#define HILOG_DEVICE_NAME                 "log_hilog"

/* the hilog module name */
#define HILOG_MODULE_NAME                 "HiLOG"

/* define hilog ring buffer size*/
#define HILOG_BUFFER_SIZE                 (64 * 1024)

#define __HILOGIO                         0xAE

#define HILOG_GET_BUF_SIZE                _IO(__HILOGIO, 1) /* size of ring buffer */
#define HILOG_GET_LEN                     _IO(__HILOGIO, 2) /* used buffer len */
#define HILOG_GET_NEXT_ENTRY_LEN          _IO(__HILOGIO, 3) /* next entry len */
#define HILOG_FLUSH_REPORT                _IO(__HILOGIO, 4) /* flush hilog */
#define HILOG_SWITCH_ON                   _IO(__HILOGIO, 5) /* turn on hilog */
#define HILOG_SWITCH_OFF                  _IO(__HILOGIO, 6) /* turn off hilog */

#define HILOG_IOVEC_COUNT                 4

/* default length of formatted line */
#define DEFAULT_FORMATTED_LEN             (1024)

/**
 * struct hilog_entry - represents an entry in the ring buffer of hilog device.
 *
 * @len:             The length of the payload
 * @__pad:           Two bytes of padding that appear to be required
 * @pid:             The generating process' process ID
 * @tid:             The generating process' thread ID
 * @sec:             The number of seconds that have elapsed since the Epoch
 * @nsec:            The number of nanoseconds that have elapsed since @sec
 * @msg:             The message that is to be logged
 */
struct hilog_entry {
    __u16                           len;
    __u16                           __pad;
    __s32                           pid;
    __s32                           tid;
    __s32                           sec;
    __s32                           nsec;
    char                            msg[0];
};

/* define max length of hilog entry's payload */
#define HILOG_ENTRY_MAX_LEN               (4 * 1024)
#define HILOG_ENTRY_MAX_PAYLOAD           (HILOG_ENTRY_MAX_LEN - sizeof(struct hilog_entry))

/**
 * struct hilog_device - represents a hilog device
 *
 * @buffer:     The actual ring buffer
 * @misc:       The "misc" device representing the hilog device
 * @wq:         The wait queue for @readers
 * @readers:    This hilog's readers
 * @mutex:      The mutex that protects the @buffer
 * @w_off:      The current write head offset
 * @r_head:     The head, or location that readers start reading at
 * @size:       The size of the ring buffer
 */
struct hilog_device {
    unsigned char                   *buffer;
    struct miscdevice               misc;
    wait_queue_head_t               wq;
    struct list_head                readers;
    struct mutex                    mutex;
    __u32                           w_off;
    __u32                           r_head;
    __u32                           size;
};

/* define reporter device variable */
static struct hilog_device* dev = NULL;

/* default hilog is closed */
static bool is_hilog_turn_on = false;

/**
 * struct hilog_reader - a hilog device open for reading
 * @dev:       The associated device
 * @list:      The associated entry in @hilog_device's list
 * @r_off:     The current read head offset.
 */
struct hilog_reader {
    struct hilog_device*       dev;
    struct list_head           list;
    size_t                     r_off;
};

/* hilog_offset - returns index 'n' into the ring buffer of hilog device
 * only when the dev->size is the power of 2
 */
static size_t hilog_offset(struct hilog_device *dev, size_t n)
{
    return n & (dev->size - 1);
}

/*
 * file_get_hilog_device - Given a file structure, return the associated device
 *
 * This isn't aesthetic. We have several goals:
 *
 *  1) Need to quickly obtain the associated device during an I/O operation
 *  2) Readers need to maintain state (hilog_reader)
 *  3) Writers need to be very fast (open() should be a near no-op)
 *
 * In the reader case, we can trivially go file->hilog_reader->dev.
 * For a writer, we don't want to maintain a hilog_reader, so we just go
 * file->hilog_device. Thus what file->private_data points at depends on whether
 * or not the file was opened for reading. This function hides that dirtiness.
 */
static inline struct hilog_device *file_get_hilog_device(struct file *file)
{
    if (file->f_mode & FMODE_READ) {
        struct hilog_reader *reader = file->private_data;
        return reader->dev;
    } else {
        return file->private_data;
    }
}

/*
 * get_entry_header - returns a pointer to the hilog_entry header within
 * 'report' starting at offset 'off'. A temporary hilog_entry 'scratch' must
 * be provided. Typically the return value will be a pointer within
 * 'logger->buf'.  However, a pointer to 'scratch' may be returned if
 * the log entry spans the end and beginning of the circular buffer.
 */
static struct hilog_entry *get_entry_header(struct hilog_device *dev,
    size_t off, struct hilog_entry *scratch)
{
    size_t len = min(sizeof(struct hilog_entry), dev->size - off);

    if (len != sizeof(struct hilog_entry)) {
        memcpy(((void *) scratch), dev->buffer + off, len); // copy from the tail of buffer.
        memcpy(((void *) scratch) + len, dev->buffer,
            sizeof(struct hilog_entry) - len); // copy from the head of buffer.
        return scratch;
    }

    return (struct hilog_entry *) (dev->buffer + off);
}

/*
 * get_entry_msg_len - Grabs the length of the message of the entry
 * starting from from 'off'.
 *
 * An entry length is 2 bytes (16 bits) in host endian order.
 * In the report, the length does not include the size of the log entry structure.
 * This function returns the size including the report entry structure.
 *
 * Caller needs to hold dev->mutex.
 */
static __u32 get_entry_msg_len(struct hilog_device *dev, size_t off)
{
    struct hilog_entry scratch;
    struct hilog_entry *entry;

    entry = get_entry_header(dev, off, &scratch);

    return entry->len;
}

/*
 * the header length is the size of struct hilog_entry.
 */
static size_t get_user_hdr_len(void)
{
    return sizeof(struct hilog_entry);
}

/*
 * copy the content of header to user space memory.
 */
static ssize_t copy_header_to_user(struct hilog_entry *entry,
                     char __user *buf)
{
    return copy_to_user(buf, entry, get_user_hdr_len());
}

/*
 * do_read_hilog_to_user - reads exactly 'count' bytes from 'hilog entry' into the
 * user-space buffer 'buf'. Returns 'count' on success.
 *
 * Caller must hold dev->mutex.
 */
static ssize_t do_read_hilog_to_user(struct hilog_device *dev,
                   struct hilog_reader *reader,
                   char __user *buf,
                   size_t count)
{
    struct hilog_entry scratch;
    struct hilog_entry *entry;
    size_t len;
    size_t msg_start;

    /*
     * First, copy the header to userspace, using the version of
     * the header requested
     */
    entry = get_entry_header(dev, reader->r_off, &scratch);
    if (copy_header_to_user(entry, buf)) {
        return -EFAULT;
    }

    count -= get_user_hdr_len();
    buf += get_user_hdr_len();
    msg_start = hilog_offset(dev,
        reader->r_off + get_user_hdr_len());

    /*
     * We read from the msg in two disjoint operations. First, we read from
     * the current msg head offset up to 'count' bytes or to the end of
     * the report, whichever comes first.
     */
    len = min(count, dev->size - msg_start);
    if (copy_to_user(buf, dev->buffer + msg_start, len)) {
        return -EFAULT;
    }

    /*
     * Second, we read any remaining bytes, starting back at the head of
     * the report.
     */
    if (count != len) {
        if (copy_to_user(buf + len, dev->buffer, count - len)) {
            return -EFAULT;
        }
    }

    reader->r_off = hilog_offset(dev, reader->r_off +
        get_user_hdr_len() + count);

    return count + get_user_hdr_len();
}

/*
 * hilog_read - our hilog device's read() method
 *
 * Behavior:
 *
 *  - O_NONBLOCK works
 *  - If there are no hilog entries to read, blocks until hilog entry is written to
 *  - Atomically reads exactly one hilog entry
 *
 * Will set errno to EINVAL if read
 * buffer is insufficient to hold next entry.
 */
static ssize_t hilog_read(struct file *file, char __user *buf,
               size_t count, loff_t *pos)
{
    struct hilog_reader *reader = file->private_data;
    ssize_t ret;
    DEFINE_WAIT(wait);

start:
    while (1) {
        mutex_lock(&dev->mutex);

        prepare_to_wait(&dev->wq, &wait, TASK_INTERRUPTIBLE);

        ret = (dev->w_off == reader->r_off);
        mutex_unlock(&dev->mutex);
        if (!ret) {
            break;
        }

        if (file->f_flags & O_NONBLOCK) {
            ret = -EAGAIN;
            break;
        }

        if (signal_pending(current)) {
            ret = -EINTR;
            break;
        }

        schedule();
    }

    finish_wait(&dev->wq, &wait);
    if (ret) {
        return ret;
    }

    mutex_lock(&dev->mutex);

    /* is there still something to read or did we race? */
    if (unlikely(dev->w_off == reader->r_off)) {
        mutex_unlock(&dev->mutex);
        goto start;
    }

    /* get the size of the next entry */
    ret = get_user_hdr_len() +
        get_entry_msg_len(dev, reader->r_off);
    if (count < ret) {
        ret = -EINVAL;
        goto out;
    }

    /* get exactly one entry from the ring buffer */
    ret = do_read_hilog_to_user(dev, reader, buf, ret);

    if (ret < 0) {
        printk(KERN_ALERT"hilog read an entry from ring buffer fail!\n");
    }

out:
    mutex_unlock(&dev->mutex);

    return ret;
}

/*
 * get_next_entry - return the offset of the first valid entry at least 'len'
 * bytes after 'off'.
 *
 * Caller must hold dev->mutex.
 */
static size_t get_next_entry(struct hilog_device *dev, size_t off, size_t len)
{
    size_t count = 0;

    do {
        size_t nr = sizeof(struct hilog_entry) +
            get_entry_msg_len(dev, off);
        off = hilog_offset(dev, off + nr);
        count += nr;
    } while (count < len);

    return off;
}

/*
 * is_between - is a < c < b, accounting for wrapping of a, b, and c
 *    positions in the buffer
 *
 * That is, if a<b, check for c between a and b
 * and if a>b, check for c outside (not between) a and b
 *
 * |------- a xxxxxxxx b --------|
 *               c^
 *
 * |xxxxx b --------- a xxxxxxxxx|
 *    c^
 *  or                    c^
 */
static inline int is_between(size_t a, size_t b, size_t c)
{
    if (a < b) {
        /* is c between a and b? */
        if (a < c && c <= b) {
            return 1;
        }
    } else {
        /* is c outside of b through a? */
        if (c <= b || a < c) {
            return 1;
        }
    }

    return 0;
}

/*
 * fix_up_readers - walk the list of all readers and "fix up" any who were
 * lapped by the writer; also do the same for the default "start head".
 * We do this by "pulling forward" the readers and start head to the first
 * entry after the new write head.
 *
 * The caller needs to hold dev->mutex.
 */
static void fix_up_readers(struct hilog_device *dev, size_t len)
{
    size_t old = dev->w_off;
    size_t new = hilog_offset(dev, old + len);
    struct hilog_reader *reader;

    if (is_between(old, new, dev->r_head)) {
        dev->r_head = get_next_entry(dev, dev->r_head, len);
    }

    list_for_each_entry(reader, &dev->readers, list) {
        if (is_between(old, new, reader->r_off)) {
            reader->r_off = get_next_entry(dev, reader->r_off, len);
        }
    }
}

/*
 * do_write_hilog - writes 'len' bytes of hilog_entry.
 *
 * The caller needs to hold dev->mutex.
 */
static ssize_t do_write_hilog(struct hilog_device *dev, const void *buf, size_t count)
{
    size_t len;

    len = min(count, (size_t)(dev->size - dev->w_off));
    memcpy(dev->buffer + dev->w_off, buf, len);

    if (count != len) {
        memcpy(dev->buffer, buf + len, count - len);
    }

    dev->w_off = hilog_offset(dev, dev->w_off + count);

    return count;
}

/*
 * do_write_hilog_from_user - writes 'len' bytes from the user-space buffer 'buf' to
 * the ring buffer of hilog device as a part of hilog_entry.
 *
 * The caller needs to hold dev->mutex.
 *
 * Returns 'count' on success, negative error code on failure.
 */
static ssize_t do_write_hilog_from_user(struct hilog_device *dev,
                      const void __user *buf, size_t count)
{
    size_t len;

    len = min(count, (size_t)(dev->size - dev->w_off));
    if (len && copy_from_user(dev->buffer + dev->w_off, buf, len)) {
        return -EFAULT;
    }

    if (count != len) {
        if (copy_from_user(dev->buffer, buf + len, count - len)) {
            /*
             * Note that by not updating w_off, this abandons the
             * portion of the new entry that *was* successfully
             * copied, just above.  This is intentional to avoid
             * message corruption from missing fragments.
             */
            return -EFAULT;
        }
    }

    dev->w_off = hilog_offset(dev, dev->w_off + count);

    return count;
}

/*
 * do_write - with header and iovec of payload.
 *
 * The caller needs to hold dev->mutex.
 */
static ssize_t do_write(struct hilog_entry* header, const struct iovec *iov,
                        unsigned long nr_segs, bool from_user)
{
    ssize_t ret = 0;

    /*
     * Fix up any readers, pulling them forward to the first readable
     * entry after (what will be) the new write offset. We do this now
     * because if we partially fail, we can end up with clobbered log
     * entries that encroach on readable buffer.
     */
    fix_up_readers(dev, sizeof(struct hilog_entry) + header->len);

    do_write_hilog(dev, header, sizeof(struct hilog_entry));

    while (nr_segs-- > 0) {
        size_t len;
        ssize_t nr;

        /* figure out how much of this vector we can keep */
        len = min_t(size_t, iov->iov_len, header->len - ret);

        /* write out this segment's payload */
        if (from_user) {
            nr = do_write_hilog_from_user(dev, iov->iov_base, len);
        } else {
            nr = do_write_hilog(dev, iov->iov_base, len);
        }

        if (unlikely(nr < 0)) {
            return nr;
        }

        iov++;
        ret += nr;
    }

    return ret;
}

/*
 * hilog_aio_write - our write method, implementing support for write(),
 * writev(), and aio_write(). Writes are our fast path, and we try to optimize
 * them above all else.
 */
static ssize_t hilog_aio_write(struct kiocb *iocb, const struct iovec *iov,
             unsigned long nr_segs, loff_t ppos)
{
    size_t orig = dev->w_off; // only for reset when write fail.
    struct hilog_entry header;
    struct timespec now;
    ssize_t ret = 0;

    now = current_kernel_time();

    header.pid = current->tgid;
    header.tid = current->pid;
    header.sec = now.tv_sec;
    header.nsec = now.tv_nsec;
    header.len = min_t(size_t, iocb->ki_left, HILOG_ENTRY_MAX_PAYLOAD);

    /* null writes succeed, return zero */
    if (unlikely(!header.len)) {
        return 0;
    }

    mutex_lock(&dev->mutex);

    ret = do_write(&header, iov, nr_segs, true);

    if (unlikely(ret < 0)) {
        dev->w_off = orig;
        mutex_unlock(&dev->mutex);
        return ret;
    }

    mutex_unlock(&dev->mutex);

    /* wake up any blocked readers */
    wake_up_interruptible(&dev->wq);

    return ret;
}

/*
 * hilog_open - the hilog device's open() file operation
 *
 * Note how near a no-op this is in the write-only case. Keep it that way!
 */
static int hilog_open(struct inode *inode, struct file *file)
{
    int ret;

    ret = nonseekable_open(inode, file);
    if (ret) {
        return ret;
    }

    if (file->f_mode & FMODE_READ) {
        struct hilog_reader *reader;

        reader = kmalloc(sizeof(struct hilog_reader), GFP_KERNEL);
        if (!reader) {
            return -ENOMEM;
        }

        reader->dev = dev;

        INIT_LIST_HEAD(&reader->list);

        mutex_lock(&dev->mutex);
        reader->r_off = dev->r_head;
        list_add_tail(&reader->list, &dev->readers);
        mutex_unlock(&dev->mutex);

        file->private_data = reader;
    } else {
        file->private_data = dev;
    }

    return 0;
}

/*
 * hilog_release - the hilog device's release file operation
 *
 * Note this is a total no-op in the write-only case. Keep it that way!
 */
static int hilog_release(struct inode *ignored, struct file *file)
{
    if (file->f_mode & FMODE_READ) {
        struct hilog_reader *reader = file->private_data;

        mutex_lock(&dev->mutex);
        list_del(&reader->list);
        mutex_unlock(&dev->mutex);

        kfree(reader);
        reader = NULL;
    }

    return 0;
}

/*
 * hilog_poll - the hilog device's poll file operation, for poll/select/epoll
 *
 * Note we always return POLLOUT, because you can always write() to the log.
 * Note also that, strictly speaking, a return value of POLLIN does not
 * guarantee that the reporter is readable without blocking, as there is a small
 * chance that the writer can lap the reader in the interim between poll()
 * returning and the read() request.
 */
static unsigned int hilog_poll(struct file *file, poll_table *wait)
{
    struct hilog_reader *reader;
    unsigned int ret = POLLOUT | POLLWRNORM;

    if (!(file->f_mode & FMODE_READ)) {
        return ret;
    }

    reader = file->private_data;

    poll_wait(file, &dev->wq, wait);

    mutex_lock(&dev->mutex);
    if (dev->w_off != reader->r_off) {
        ret |= POLLIN | POLLRDNORM;
    }
    mutex_unlock(&dev->mutex);

    return ret;
}

/*
 * hilog_ioctl - control the hilog device by send commands.
 */
static long hilog_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    struct hilog_reader *reader;
    long ret = -EINVAL;

    mutex_lock(&dev->mutex);

    switch (cmd) {
    case HILOG_SWITCH_ON:
        is_hilog_turn_on = true;
        ret = 0;
        break;
    case HILOG_SWITCH_OFF:
        is_hilog_turn_on = false;
        ret = 0;
        break;
    case HILOG_GET_BUF_SIZE:
        ret = dev->size;
        break;
    case HILOG_GET_LEN:
        if (!(file->f_mode & FMODE_READ)) {
            ret = -EBADF;
            break;
        }
        reader = file->private_data;
        if (dev->w_off >= reader->r_off) {
            ret = dev->w_off - reader->r_off;
        }
        else {
            ret = (dev->size - reader->r_off) + dev->w_off;
        }
        break;
    case HILOG_GET_NEXT_ENTRY_LEN:
        if (!(file->f_mode & FMODE_READ)) {
            ret = -EBADF;
            break;
        }
        reader = file->private_data;

        if (dev->w_off != reader->r_off) {
            ret = get_user_hdr_len() +
                get_entry_msg_len(dev, reader->r_off);
        }
        else {
            ret = 0;
        }
        break;
    case HILOG_FLUSH_REPORT:
        if (!(file->f_mode & FMODE_WRITE)) {
            ret = -EBADF;
            break;
        }
        if (!(in_egroup_p(file->f_dentry->d_inode->i_gid) ||
                capable(CAP_SYSLOG))) {
            ret = -EPERM;
            break;
        }
        list_for_each_entry(reader, &dev->readers, list) {
            reader->r_off = dev->w_off;
        }
        dev->r_head = dev->w_off;
        ret = 0;
        break;
    }
    mutex_unlock(&dev->mutex);

    return ret;
}

/**
 * struct file_operations - a hilog device file operation func pointers.
 */
static const struct file_operations hilog_fops = {
    .owner = THIS_MODULE,
    .read = hilog_read,
    .aio_write = hilog_aio_write,
    .poll = hilog_poll,
    .unlocked_ioctl = hilog_ioctl,
    .compat_ioctl = hilog_ioctl,
    .open = hilog_open,
    .release = hilog_release,
};

/*
 * Create a hilog device of misc type, register it to system,
 * and assign it a ring buffer which size is HILOG_BUFFER_SIZE.
 */
static ssize_t create_hilog_dev(void)
{
    ssize_t err = -1;
    unsigned char *buffer = NULL;

    buffer = vmalloc(HILOG_BUFFER_SIZE);
    if (buffer == NULL) {
        return -ENOMEM;
    }

    printk(KERN_ALERT"Initializing hilog device, buffer size: %luK.\n", \
        (unsigned long) HILOG_BUFFER_SIZE >> 10);

    /* malloc space for struct varible */
    dev = kmalloc(sizeof(struct hilog_device), GFP_KERNEL);
    if(!dev) {
        err = -ENOMEM;
        printk(KERN_ALERT"Failed to alloc hilog dev.\n");
        goto out_free_buffer;
    }

    memset(dev, 0, sizeof(struct hilog_device));

    dev->buffer = buffer;
    dev->misc.minor = MISC_DYNAMIC_MINOR;
    dev->misc.name = kstrdup(HILOG_DEVICE_NAME, GFP_KERNEL);
    if (dev->misc.name == NULL) {
        err = -ENOMEM;
        goto out_free_dev;
    }

    dev->misc.fops = &hilog_fops;
    dev->misc.parent = NULL;

    init_waitqueue_head(&dev->wq);
    INIT_LIST_HEAD(&dev->readers);

    mutex_init(&dev->mutex);
    dev->w_off = 0;
    dev->r_head = 0;
    dev->size = HILOG_BUFFER_SIZE;

    /* finally, initialize the misc device */
    err = misc_register(&dev->misc);
    if (unlikely(err)) {
        printk(KERN_ALERT"failed to register misc device for hilog '%s'!\n",
            dev->misc.name);
        goto out_free_dev;
    }

    printk(KERN_ALERT"Succedded to initialize hilog device, name: %s!\n",
        HILOG_DEVICE_NAME);

    return 0;

out_free_dev:
    if (dev->misc.name) {
        kfree(dev->misc.name);
    }
    kfree(dev);
    dev = NULL;

out_free_buffer:
    vfree(buffer);
    buffer = NULL;

    return err;
}

/*
 * use to calculate the total length of iovecs.
 */
static int calc_iovc_ki_left(const struct iovec *iov, int nr_segs)
{
    int ret = 0;
    int seg;
    ssize_t len = 0;

    for (seg = 0; seg < nr_segs; seg++) {
        len = (ssize_t)iov[seg].iov_len;
        ret += len;
    }

    return ret;
}

/*
 * Initialize hilog by create a hilog device.
 */
static int __init hilog_init(void)
{
    int ret;

    ret = create_hilog_dev();
    if (unlikely(ret)) {
        goto out;
    }

out:
    return ret;
}

/*
 * the mothed called when file closed.
 */
static void __exit hilog_exit(void)
{
    printk(KERN_ALERT"Destroy hilog device.\n");

    /* delete char device and free memory */
    if(dev) {
        misc_deregister(&dev->misc);
        vfree(dev->buffer);
        dev->buffer = NULL;
        kfree(dev->misc.name);
        dev->misc.name = NULL;
        kfree(dev);
        dev = NULL;
    }
}

/*
 * the method which expanded by the HiLOGE macro.
 */
extern int __hi_log_print(const size_t pri, const char* module, const char* sub_module, \
                           const char* fmt, ...)
{
    int ret = 0;
    struct hilog_entry header;
    struct timespec now;
    struct iovec vec[HILOG_IOVEC_COUNT];
    struct iovec *iov = vec;
    int nr_segs = sizeof(vec) / sizeof(vec[0]);
    int iovc_ki_left_len = 0;
    unsigned char prio = (unsigned char)pri;
    va_list ap;
    char msg[DEFAULT_FORMATTED_LEN + 1] = {0};
    size_t orig = 0; // only for reset when write fail.

    if (NULL == module || NULL == sub_module || NULL == fmt) {
        printk(KERN_ALERT"Report an exception in kernel need to tell module, sub_module and a description!\n");
        return ret;
    }

    if (NULL == dev) {
        printk(KERN_ALERT"failed to report an exception of module '%s'!\n",
            module);
        return ret;
    }

    orig = dev->w_off;

    va_start(ap, fmt);
    vsnprintf(msg, DEFAULT_FORMATTED_LEN, fmt, ap);
    va_end(ap);

    // write it into kmsg
    printk(KERN_ALERT"["HILOG_MODULE_NAME"]""%-8s %-8s: %s\n", module, sub_module, msg);

    if (!is_hilog_turn_on) {
        printk(KERN_ALERT"hilog in kernel space is closed!\n");
        return ret;
    }

    if (in_interrupt()) {
        printk(KERN_ALERT"hilog is called from an irq, you'd better remove it!\n");
        return ret;
    }

    /*according to the arguments, fill the iovec struct  */
    vec[0].iov_base   = &prio;
    vec[0].iov_len    = 1;
    vec[1].iov_base   = (void *)module;
    vec[1].iov_len    = strlen(module) + 1;
    vec[2].iov_base   = (void *)sub_module;
    vec[2].iov_len    = strlen(sub_module) + 1;
    vec[3].iov_base   = (void *)msg;
    vec[3].iov_len    = strlen(msg) + 1;

    now = current_kernel_time();
    iovc_ki_left_len = calc_iovc_ki_left(vec, nr_segs);

    header.pid = current->tgid;
    header.tid = current->pid;
    header.sec = now.tv_sec;
    header.nsec = now.tv_nsec;
    header.len = min(iovc_ki_left_len, (int)DEFAULT_FORMATTED_LEN);

    /* null writes succeed, return zero */
    if (unlikely(!header.len)) {
        return ret;
    }

    mutex_lock(&dev->mutex);

    ret = do_write(&header, iov, nr_segs, false);

    if (unlikely(ret < 0)) {
        dev->w_off = orig;
        mutex_unlock(&dev->mutex);
        return ret;
    }

    mutex_unlock(&dev->mutex);

    /* wake up any blocked readers */
    wake_up_interruptible(&dev->wq);

    return ret;
}

module_init(hilog_init);
module_exit(hilog_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Henry Zhou, <zhouhengyong@huawei.com>");
MODULE_DESCRIPTION("Hisilicon platform hisi diagnostic package support");
