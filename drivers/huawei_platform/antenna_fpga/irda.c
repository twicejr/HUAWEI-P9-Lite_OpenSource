#include <linux/init.h>
#include <linux/module.h>
#include <linux/ioctl.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/list.h>
#include <linux/errno.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/spi/spi.h>
#include <linux/io.h>
#include <linux/dma-mapping.h>
#include <linux/version.h>
#include <linux/proc_fs.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>
#include <linux/ctype.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/vmalloc.h>
#include <linux/random.h>
#include <linux/irq.h>
#include <linux/amba/pl022.h>
#include <linux/pinctrl/consumer.h>
#include <huawei_platform/log/hw_log.h>

#include <linux/cdev.h>
#include <linux/spi/spidev.h>

#include "fpga_ice40.h"

#define HWLOG_TAG irda_fpga
HWLOG_REGIST();

#define VERBOSE

#define SPI_MODE_MASK       (SPI_CPHA | SPI_CPOL | SPI_CS_HIGH \
                | SPI_LSB_FIRST | SPI_3WIRE | SPI_LOOP \
                | SPI_NO_CS | SPI_READY)

#define G_BUFSIZE 4096

extern int g_spi_fpga_cs_gpio;
static struct class *spidev_class;

static struct cdev spidev_cdev;
static unsigned int spidev_major;
static unsigned int spidev_minor;

static unsigned bufsiz = G_BUFSIZE;

fpga_spi_data* get_spi_data(void);

static int spidev_open(struct inode *inode, struct file *filp)
{
    hwlog_info("%s - spidev is opened.\n",__func__);

    return 0;
}

static int spidev_release(struct inode *inode, struct file *filp)
{
    hwlog_info("%s - spidev is closed.\n",__func__);

    return 0;
}

/* Read-only message with current device setup */
static ssize_t spidev_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    static unsigned char outdata[G_BUFSIZE];

    fpga_spi_data *spidev = NULL;
    int ret = 0;
    struct spi_message  m;
    struct spi_transfer t = {
        .rx_buf = outdata,
    };

    hwlog_info("%s: %d, count=%d\n", __FUNCTION__, __LINE__, count);

    if (count > sizeof outdata) {
        hwlog_err("%s: %d, count is larger than buffer size\n", __FUNCTION__, __LINE__);
        return -EINVAL;
    }
    t.len = count;

    spidev = get_spi_data();
    if(!spidev) {
        hwlog_err("%s - spidev is NULL.\n",__func__);
        return -EFAULT;
    }
    spi_message_init(&m);
    spi_message_add_tail(&t, &m);
    ret = spi_sync(spidev->spi, &m);
    if (ret < 0) {
        hwlog_err("%s:ice40_data_spi_recv fail , result = %d.\n", __func__, ret);
        return -EFAULT;
    }

    print_hex_dump(KERN_WARNING, NULL, DUMP_PREFIX_OFFSET, 16, 1, outdata,
            count, false);
    ret = copy_to_user(buf, outdata, count);
    hwlog_info("%s: %d, ret=%d\n", __FUNCTION__, __LINE__, ret);

    return count;
}

/* Write-only message with current device setup */
static ssize_t spidev_write(struct file *filp, const char __user *buf,
        size_t count, loff_t *f_pos)
{
    static unsigned char g_indata[G_BUFSIZE] = {0};

    ssize_t         status = 0;
    unsigned long       missing;

    hwlog_info("%s: %d, count=%d\n", __FUNCTION__, __LINE__, count);
    /* chipselect only toggles at start or end of operation */
    if (count > G_BUFSIZE)
        return -EMSGSIZE;

    missing = copy_from_user(g_indata, buf, count);
    if (missing == 0) {
        print_hex_dump(KERN_WARNING, NULL, DUMP_PREFIX_OFFSET, 16, 1, g_indata, count, false);

        status = ice40_set_cs_callback(NORMAL_RATE, g_spi_fpga_cs_gpio);
        hwlog_info("%s: %d, status=%d\n", __FUNCTION__, __LINE__, status);
        status = ice40_data_spi_write(g_indata, count);
    } else
        status = -EFAULT;

    hwlog_info("%s: %d, status=%d\n", __FUNCTION__, __LINE__, status);
    if (status == SUCCESS) {
        return count;
    } else {
        return status;
    }
}

/*
 * We can't use the standard synchronous wrappers for file I/O; we
 * need to protect against async removal of the underlying spi_device.
 */
static void spidev_complete(void *arg)
{
    complete(arg);
}

static ssize_t spidev_sync(fpga_spi_data *spidev, struct spi_message *message)
{
    DECLARE_COMPLETION_ONSTACK(done);
    int status;

    message->complete = spidev_complete;
    message->context = &done;

    if (spidev->spi == NULL)
        status = -ESHUTDOWN;
    else
        status = spi_async(spidev->spi, message);

    if (status == 0) {
        wait_for_completion(&done);
        status = message->status;
        if (status == 0)
            status = message->actual_length;
    }
    return status;
}

static int spidev_message(fpga_spi_data *spidev,
        struct spi_ioc_transfer *u_xfers, unsigned n_xfers)
{
    struct spi_message  msg;
    struct spi_transfer *k_xfers;
    struct spi_transfer *k_tmp;
    struct spi_ioc_transfer *u_tmp;
    unsigned        n, total;
    u8          *buf;
    int         status = -EFAULT;
    static unsigned char outdata[G_BUFSIZE];

    hwlog_info("%s - enter.\n",__func__);
    hwlog_info("%s - u_xfers=%p, n_xfers=%lu\n",__func__, u_xfers, n_xfers);

    spi_message_init(&msg);
    k_xfers = kcalloc(n_xfers, sizeof(*k_tmp), GFP_KERNEL);
    if (k_xfers == NULL)
        return -ENOMEM;

    hwlog_info("%s %d\n",__func__, __LINE__);
    /* Construct spi_message, copying any tx data to bounce buffer.
     * We walk the array of user-provided transfers, using each one
     * to initialize a kernel version of the same transfer.
     */
    buf = outdata;
    total = 0;
    for (n = n_xfers, k_tmp = k_xfers, u_tmp = u_xfers;
            n;
            n--, k_tmp++, u_tmp++) {
        k_tmp->len = u_tmp->len;

        total += k_tmp->len;
        if (total > bufsiz) {
            status = -EMSGSIZE;
            goto done;
        }

        if (u_tmp->rx_buf) {
            k_tmp->rx_buf = buf;
            if (!access_ok(VERIFY_WRITE, (u8 __user *)
                        (uintptr_t) u_tmp->rx_buf,
                        u_tmp->len))
                goto done;
        }
        if (u_tmp->tx_buf) {
            k_tmp->tx_buf = buf;
            print_hex_dump(KERN_WARNING, "tx: ", DUMP_PREFIX_OFFSET, 16, 1, u_tmp->tx_buf, u_tmp->len, false);
            if (copy_from_user(buf, (const u8 __user *)
                        (uintptr_t) u_tmp->tx_buf,
                    u_tmp->len))
                goto done;
        }
        buf += k_tmp->len;

        k_tmp->cs_change = !!u_tmp->cs_change;
        k_tmp->bits_per_word = u_tmp->bits_per_word;
        k_tmp->delay_usecs = u_tmp->delay_usecs;
        /* k_tmp->speed_hz = u_tmp->speed_hz; */
        k_tmp->speed_hz = FPGA_ICE40_SPI_SPEED_NORMAL;
        hwlog_info("%s %d k_tmp->speed_hz=%d\n",__func__, __LINE__, k_tmp->speed_hz);

#ifdef VERBOSE
        dev_warn(&spidev->spi->dev,
            "  xfer len %zd %s%s%s%dbits %u usec %uHz\n",
            u_tmp->len,
            u_tmp->rx_buf ? "rx " : "",
            u_tmp->tx_buf ? "tx " : "",
            u_tmp->cs_change ? "cs " : "",
            u_tmp->bits_per_word ? : spidev->spi->bits_per_word,
            u_tmp->delay_usecs,
            u_tmp->speed_hz ? : spidev->spi->max_speed_hz);
#endif
        status = ice40_set_cs_callback(NORMAL_RATE, g_spi_fpga_cs_gpio);
        hwlog_info("%s: %d, status=%d\n", __FUNCTION__, __LINE__, status);
        spi_message_add_tail(k_tmp, &msg);
    }

    status = spidev_sync(spidev, &msg);
    hwlog_info("%s %d status=%d\n",__func__, __LINE__, status);
    if (status < 0)
        goto done;

    /* copy any rx data out of bounce buffer */
    buf = outdata;
    for (n = n_xfers, u_tmp = u_xfers; n; n--, u_tmp++) {
        if (u_tmp->rx_buf) {
            if (__copy_to_user((u8 __user *)
                    (uintptr_t) u_tmp->rx_buf, buf,
                    u_tmp->len)) {
                status = -EFAULT;
                goto done;
            }
            print_hex_dump(KERN_WARNING, "rx: ", DUMP_PREFIX_OFFSET, 16, 1, u_tmp->rx_buf, u_tmp->len, false);
        }
        buf += u_tmp->len;
    }
    status = total;
    hwlog_info("%s %d\n",__func__, __LINE__);

done:
    kfree(k_xfers);
    hwlog_info("%s - exit.\n",__func__);

    return status;
}

static long spidev_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    int         err = 0;
    int         retval = 0;
    fpga_spi_data *spidev = get_spi_data();
    u32         tmp;
    unsigned        n_ioc;
    struct spi_ioc_transfer *ioc;


    hwlog_info("%s - spidev is ioctl, arg=%p.\n",__func__, arg);

    /* Check type and command number */
    if (_IOC_TYPE(cmd) != SPI_IOC_MAGIC)
        return -ENOTTY;

    /* Check access direction once here; don't repeat below.
     * IOC_DIR is from the user perspective, while access_ok is
     * from the kernel perspective; so they look reversed.
     */
    if (_IOC_DIR(cmd) & _IOC_READ)
        err = !access_ok(VERIFY_WRITE,
                (void __user *)arg, _IOC_SIZE(cmd));
    if (err == 0 && _IOC_DIR(cmd) & _IOC_WRITE)
        err = !access_ok(VERIFY_READ,
                (void __user *)arg, _IOC_SIZE(cmd));
    if (err)
        return -EFAULT;

    switch (cmd) {
    /* read requests */
    case SPI_IOC_RD_MODE:
        hwlog_info("%s - SPI_IOC_RD_MODE. 0x%p\n",__func__, spidev->spi->mode & SPI_MODE_MASK);
        retval = __put_user(spidev->spi->mode & SPI_MODE_MASK,
                    (__u8 __user *)arg);
        break;
    case SPI_IOC_RD_LSB_FIRST:
        hwlog_info("%s - SPI_IOC_RD_LSB_FIRST. 0x%p\n",__func__, (spidev->spi->mode & SPI_LSB_FIRST));
        retval = __put_user((spidev->spi->mode & SPI_LSB_FIRST) ?  1 : 0,
                    (__u8 __user *)arg);
        break;
    case SPI_IOC_RD_BITS_PER_WORD:
        hwlog_info("%s - SPI_IOC_RD_BITS_PER_WORD. 0x%p\n",__func__, spidev->spi->bits_per_word);
        retval = __put_user(spidev->spi->bits_per_word, (__u8 __user *)arg);
        break;
    case SPI_IOC_RD_MAX_SPEED_HZ:
        hwlog_info("%s - SPI_IOC_RD_MAX_SPEED_HZ. %d\n",__func__, spidev->spi->max_speed_hz);
        retval = __put_user(spidev->spi->max_speed_hz, (__u32 __user *)arg);
        break;

    /* write requests */
    case SPI_IOC_WR_MODE:
        hwlog_info("%s - SPI_IOC_WR_MODE.\n",__func__);
        retval = __get_user(tmp, (u8 __user *)arg);
        if (retval == 0) {
            u8  save = spidev->spi->mode;

            if (tmp & ~SPI_MODE_MASK) {
                retval = -EINVAL;
                break;
            }

            tmp |= spidev->spi->mode & ~SPI_MODE_MASK;
            spidev->spi->mode = (u8)tmp;
            retval = spi_setup(spidev->spi);
            if (retval < 0)
                spidev->spi->mode = save;
            else
                dev_warn(&spidev->spi->dev, "spi mode %02x\n", tmp);
        }
        break;
    case SPI_IOC_WR_LSB_FIRST:
        hwlog_info("%s - SPI_IOC_WR_LSB_FIRST.\n",__func__);
        retval = __get_user(tmp, (__u8 __user *)arg);
        if (retval == 0) {
            u8  save = spidev->spi->mode;

            if (tmp)
                spidev->spi->mode |= SPI_LSB_FIRST;
            else
                spidev->spi->mode &= ~SPI_LSB_FIRST;
            retval = spi_setup(spidev->spi);
            if (retval < 0)
                spidev->spi->mode = save;
            else
                dev_warn(&spidev->spi->dev, "%csb first\n",
                        tmp ? 'l' : 'm');
        }
        break;
    case SPI_IOC_WR_BITS_PER_WORD:
        hwlog_info("%s - SPI_IOC_WR_BITS_PER_WORD.\n",__func__);
        retval = __get_user(tmp, (__u8 __user *)arg);
        if (retval == 0) {
            u8  save = spidev->spi->bits_per_word;

            spidev->spi->bits_per_word = tmp;
            retval = spi_setup(spidev->spi);
            if (retval < 0)
                spidev->spi->bits_per_word = save;
            else
                dev_warn(&spidev->spi->dev, "%d bits per word\n", tmp);
        }
        break;
    case SPI_IOC_WR_MAX_SPEED_HZ:
        hwlog_info("%s - SPI_IOC_WR_MAX_SPEED_HZ.\n",__func__);
        retval = __get_user(tmp, (__u32 __user *)arg);
        if (retval == 0) {
            u32 save = spidev->spi->max_speed_hz;

            spidev->spi->max_speed_hz = tmp;
            retval = spi_setup(spidev->spi);
            if (retval < 0)
                spidev->spi->max_speed_hz = save;
            else
                dev_warn(&spidev->spi->dev, "%d Hz (max)\n", tmp);
        }
        break;

    default:
        hwlog_info("%s - ioctl default branch.\n",__func__);
        /* segmented and/or full-duplex I/O request */
        if (_IOC_NR(cmd) != _IOC_NR(SPI_IOC_MESSAGE(0))
                || _IOC_DIR(cmd) != _IOC_WRITE) {
            retval = -ENOTTY;
            break;
        }

        tmp = _IOC_SIZE(cmd);
        if ((tmp % sizeof(struct spi_ioc_transfer)) != 0) {
            retval = -EINVAL;
            break;
        }
        n_ioc = tmp / sizeof(struct spi_ioc_transfer);
        if (n_ioc == 0)
            break;

        /* copy into scratch area */
        ioc = kmalloc(tmp, GFP_KERNEL);
        if (!ioc) {
            retval = -ENOMEM;
            break;
        }
        if (__copy_from_user(ioc, (void __user *)arg, tmp)) {
            kfree(ioc);
            retval = -EFAULT;
            break;
        }

        /* translate to spi_message, execute */
        retval = spidev_message(spidev, ioc, n_ioc);
        hwlog_info("%s - spidev_message retval=%d.\n",__func__, retval);
        kfree(ioc);
        break;
    }

    return retval;
}

#ifdef CONFIG_COMPAT
static long spidev_compat_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    hwlog_info("%s - spidev is compat ioctl, arg=%p.\n",__func__, arg);

    return spidev_ioctl(filp, cmd, (unsigned long)compat_ptr(arg));
}
#else
#define spidev_compat_ioctl NULL
#endif /* CONFIG_COMPAT */

static const struct file_operations spidev_fops = {
    .owner =    THIS_MODULE,
    /* REVISIT switch to aio primitives, so that userspace
     * gets more complete API coverage.  It'll simplify things
     * too, except for the locking.
     */
    .write =    spidev_write,
    .read =     spidev_read,
    .unlocked_ioctl = spidev_ioctl,
    .compat_ioctl = spidev_compat_ioctl,
    .open =     spidev_open,
    .release =  spidev_release,
    .llseek =   no_llseek,
};

int __init spidev_init(void)
{
    int status;
    dev_t dev;
    int spi_nr_devs = 32;

    hwlog_info("%s: %d", __FUNCTION__, __LINE__);
    status = alloc_chrdev_region(&dev, spidev_minor, spi_nr_devs, "spidev_fpga");
    spidev_major = MAJOR(dev);
    hwlog_info("%s: %d, spidev_major=%lu\n", __FUNCTION__, __LINE__,
            spidev_major);

    cdev_init(&spidev_cdev, &spidev_fops);
    spidev_cdev.owner = THIS_MODULE;
    spidev_cdev.ops = &spidev_fops;
    status = cdev_add (&spidev_cdev, MKDEV(spidev_major, 0), 1);
    if (status) {
        hwlog_info("%s: %d, error status=%d adding spidev_fpga\n", __FUNCTION__, __LINE__, status);
        return status;
    }

    spidev_class = class_create(THIS_MODULE, "spidev_fpga");
    if (IS_ERR(spidev_class)) {
        unregister_chrdev(spidev_major, "spidev_fpga");
        return PTR_ERR(spidev_class);
    }
    hwlog_info("%s: %d", __FUNCTION__, __LINE__);

    return status;
}

void __exit spidev_exit(void)
{
    class_destroy(spidev_class);
    unregister_chrdev(spidev_major, "spidev_fpga");
}

int irda_spidev_probe(void)
{
    int ret;
    struct device *spi_fpga_dev;

    spi_fpga_dev = device_create(spidev_class, NULL, MKDEV(spidev_major, 0),
                NULL, "spidev0.0");
    ret = PTR_RET(spi_fpga_dev);
    if (IS_ERR(spi_fpga_dev)) {
        hwlog_err("%s: device_create() failed\n", __FUNCTION__);
        return -1;
    }

    return 0;
}
