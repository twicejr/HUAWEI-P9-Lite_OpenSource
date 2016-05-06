/*
 * modem_ttys.c
 *
 */

#include <linux/module.h>
#include <linux/mod_devicetable.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>

#include "viatel.h"
#include "apcp_test.h"
#include "power.h"
#include "modem_ttys.h"
#include "modem_channels.h"
#include "ext_modem.h"


/* global modem ttys instance */
struct modem_ttys_mgmt g_modem_ttys;

static int check_tty_permission(struct modem_tty_dev* pt_tty_dev)
{
    if (!pt_tty_dev)
    {
        hwlog_err("%s %d: tty dev can not be found.\n", __func__, __LINE__);
        return -ENODEV;
    }

    if (0 == get_modem_bus_state())
    {
        hwlog_err("%s %d: modem_power_state=%d, m_tty_index is %d.\n", __func__, __LINE__, get_modem_bus_state(), pt_tty_dev->m_tty_index);
        return -ENODEV;
    }

    //for the reason if VIA modem reset, many userspace applications die loop repeatly call check_tty_permission, which result system busy loop.
    //ttySPI0 for respond cflag80 packet, ttySPI2 for flashlessd, ttySPI10 for rild and statusd wait CBP VPUP.
    //rild use ttySPI7 to send command after receive VPUP, but before set modem_state to MODEM_STATE_READY!
    //ttySPI1 is used by ETS log, which has too much ETS log before MODEM_STATE_READY, may result software flow ctrl.
    if ((pt_tty_dev->m_tty_index != 0) \
        && (pt_tty_dev->m_tty_index != 1) \
        && (pt_tty_dev->m_tty_index != 2) \
        && (pt_tty_dev->m_tty_index != 7) \
        && (pt_tty_dev->m_tty_index != 8) \
        && (pt_tty_dev->m_tty_index != 9) \
        && (pt_tty_dev->m_tty_index != 10) \
        && (0 == is_via_modem_state_ready()))
    {
        hwlog_err("%s %d: Flashlessd is downloading cp.rom and fsm images, pt_tty_dev m_tty_index is %d.\n", __func__, __LINE__, pt_tty_dev->m_tty_index);
        return -1;
    }

    return 0;
}

static void read_buffered_data_before_open(struct modem_tty_dev* pt_tty_dev)
{
    struct modem_buf_in_packet* p_packet = NULL;
    struct tty_struct* p_tty = NULL;
    int room;

    p_tty = tty_port_tty_get(&pt_tty_dev->m_tty_port);

    if (p_tty)
    {
        mutex_lock(&pt_tty_dev->m_buf_in_mutex);

        while (!list_empty(&pt_tty_dev->m_buf_in_list))
        {
            p_packet = list_first_entry(&pt_tty_dev->m_buf_in_list, struct modem_buf_in_packet, m_node);

            if (p_packet)
            {
                room = tty_buffer_request_room(&pt_tty_dev->m_tty_port, p_packet->m_size);

                if (room < p_packet->m_size)
                {
                    hwlog_debug("%s %d: port %d no room in tty rx buffer!\n", __func__, __LINE__, pt_tty_dev->m_tty_index);
                }
                else
                {
                    room = tty_insert_flip_string(&pt_tty_dev->m_tty_port, p_packet->pm_buffer, p_packet->m_size);

                    if (room < p_packet->m_size)
                    {
                        hwlog_err("%s %d: port %d couldn't insert all characters (TTY is full?)!\n", __func__, __LINE__, pt_tty_dev->m_tty_index);
                    }
                    else
                    {
                        tty_flip_buffer_push(&pt_tty_dev->m_tty_port);
                    }
                }

                list_del(&p_packet->m_node);
                pt_tty_dev->m_buf_in_size -= p_packet->m_size;
                kfree(p_packet->pm_buffer);
                kfree(p_packet);
                pt_tty_dev->m_buf_in_num--;
            }
            else
            {
                break;
            }
        }

        mutex_unlock(&pt_tty_dev->m_buf_in_mutex);

        tty_kref_put(p_tty);
    }
}

static void clean_buffered_data_on_close(struct modem_tty_dev* pt_tty_dev)
{
    struct modem_buf_in_packet* p_packet = NULL;

    mutex_lock(&pt_tty_dev->m_buf_in_mutex);

    while (!list_empty(&pt_tty_dev->m_buf_in_list))
    {
        p_packet = list_first_entry(&pt_tty_dev->m_buf_in_list, struct modem_buf_in_packet, m_node);

        if (p_packet)
        {
            list_del(&p_packet->m_node);
            kfree(p_packet->pm_buffer);
            kfree(p_packet);
        }
        else
        {
            hwlog_err("%s %d: current packet is NULL!\n", __func__, __LINE__);
            break;
        }
    }

    mutex_unlock(&pt_tty_dev->m_buf_in_mutex);
}

/*****************************************************************************
 * tty driver interface functions
 *****************************************************************************/
/**
 *    modem_tty_install    -    install method
 *    @driver: the driver in use
 *    @tty: the tty being bound
 *
 *    Look up and bind the tty and the driver together. Initialize
 *    any needed private data (in our case the termios)
 */

static int modem_tty_install(struct tty_driver* pt_driver, struct tty_struct* pt_tty)
{
    struct modem_tty_dev* p_tty_dev ;
    int ret;

    hwlog_info("%s %d: tty dev %d.\n", __func__, __LINE__, pt_tty->index);

    p_tty_dev = g_modem_ttys.pm_tty_devs[pt_tty->index];

    ret = tty_init_termios(pt_tty);

    if (ret)
    {
        hwlog_err("%s %d: tty dev %d tty_init_termios return error, ret=%d.\n", __func__, __LINE__, pt_tty->index, ret);
        return ret;
    }

    tty_driver_kref_get(pt_driver);
    pt_tty->count++;
    pt_driver->ttys[pt_tty->index] = pt_tty;

    if (ret == 0)
        /* This is the ref modem_tty_dev get provided */
    { pt_tty->driver_data = p_tty_dev; }

    return ret;
}

/**
 *    modem_tty_cleanup    -    called on the last tty kref drop
 *    @pt_tty: the tty being destroyed
 *
 *    Called asynchronously when the last reference to the tty is dropped.
 *    We cannot destroy the tty->driver_data port kref until this point
 */
static void modem_tty_cleanup(struct tty_struct* pt_tty)
{
    struct modem_tty_dev* p_tty_dev = pt_tty->driver_data;
    pt_tty->driver_data = NULL;    /* Bug trap */

    if (p_tty_dev)
    {
        hwlog_info("%s %d: tty dev %d.\n", __func__, __LINE__, p_tty_dev->m_tty_index);
    }
    else
    {
        hwlog_info("%s %d: invalid tty dev.\n", __func__, __LINE__);
    }
}

static int modem_tty_open(struct tty_struct* pt_tty, struct file* pt_filp)
{
    struct modem_tty_dev* p_tty_dev = pt_tty->driver_data;
    hwlog_info("%s %d: tty dev %d.\n", __func__, __LINE__, p_tty_dev->m_tty_index);
    return tty_port_open(&p_tty_dev->m_tty_port, pt_tty, pt_filp);
}

static void modem_tty_close(struct tty_struct* pt_tty, struct file* pt_filp)
{
    struct modem_tty_dev* p_tty_dev = pt_tty->driver_data;

    hwlog_info("%s %d: tty dev %d.\n", __func__, __LINE__, p_tty_dev->m_tty_index);
    tty_port_close(&p_tty_dev->m_tty_port, pt_tty, pt_filp);
}

static void modem_tty_hangup(struct tty_struct* pt_tty)
{
    struct modem_tty_dev* p_tty_dev = pt_tty->driver_data;
    hwlog_info("%s %d: tty dev %d.\n", __func__, __LINE__, p_tty_dev->m_tty_index);
    tty_port_hangup(&p_tty_dev->m_tty_port);
}

static int modem_tty_write_room(struct tty_struct* pt_tty)
{
    struct modem_tty_dev* p_tty_dev = pt_tty->driver_data;
    unsigned int space_len = 0; /* the tx buffer length */
    unsigned int ret;

    ret = check_tty_permission(p_tty_dev);

    if (ret < 0)
    {
        hwlog_err("%s %d: tty dev %d check_tty_permission failed\n", __func__, __LINE__, p_tty_dev->m_tty_index);
        space_len = 0;
    }
    else
    {
        space_len = FIFO_SIZE - get_channel_kfifo_data_length(p_tty_dev->m_tty_index + 1);
    }

    return space_len;
}

static int modem_tty_chars_in_buffer(struct tty_struct* pt_tty)
{
    struct modem_tty_dev* p_tty_dev = pt_tty->driver_data;
    unsigned int left_len = 0;

    /* for sync write, no data will be left when next write */
    left_len = get_channel_kfifo_data_length(p_tty_dev->m_tty_index + 1);

    return left_len;
}

static void modem_tty_set_termios(struct tty_struct* pt_tty, struct ktermios* old_termios)
{
    struct modem_tty_dev* p_tty_dev = pt_tty->driver_data;
    int ret;

    ret = check_tty_permission(p_tty_dev);

    if (ret < 0)
    {
        hwlog_err("%s %d: tty dev %d ret=%d\n", __func__, __LINE__, p_tty_dev->m_tty_index, ret);
        return ;
    }

    tty_termios_copy_hw(&(pt_tty->termios), old_termios);
}

static int modem_tty_tiocmget(struct tty_struct* pt_tty)
{
    struct modem_tty_dev* p_tty_dev = pt_tty->driver_data;
    int ret;

    ret = check_tty_permission(p_tty_dev);

    if (ret < 0)
    {
        hwlog_err("%s %d: tty dev %d ret=%d\n", __func__, __LINE__, p_tty_dev->m_tty_index, ret);
        return ret;
    }

    return 0;
}

static int modem_tty_tiocmset(struct tty_struct* pt_tty, unsigned int set, unsigned int clear)
{
    struct modem_tty_dev* p_tty_dev = pt_tty->driver_data;
    int ret;

    ret = check_tty_permission(p_tty_dev);

    if (ret < 0)
    {
        hwlog_err("%s %d: tty dev %d ret=%d\n", __func__, __LINE__, p_tty_dev->m_tty_index, ret);
        return ret;
    }

    return 0;
}

/**
 * modem_tty_write - push data to modem tty dirver
 * @pt_buf: low-level received packet buffer
 * @t_count: low-level received packet length
 * @t_tty_index: the tty index extract from packet header
 *
 * Returns:
 *   length of successfully write data in bytes
 */
static int modem_tty_write(struct tty_struct* pt_tty, const unsigned char* pt_buf, int t_count)
{
    struct modem_tty_dev* p_tty_dev = pt_tty->driver_data;
    int ret = 0;

    if ((NULL == pt_tty) || (NULL == pt_buf) || (0 == t_count))
    {
        hwlog_err("%s %d: NULL pointer! pt_tty=0x%lx, pt_buf=0x%lx, count=%d\n", \
                  __func__, __LINE__, (unsigned long)pt_tty, (unsigned long)pt_buf, t_count);
        return -1;
    }

    hwlog_debug("%s %d: tty index is %d, write length=%d\n", __func__, __LINE__, p_tty_dev->m_tty_index, t_count);
    ret = check_tty_permission(p_tty_dev);

    if (ret < 0)
    {
        hwlog_err("%s %d tty dev %d ret = %d\n", __func__, __LINE__, p_tty_dev->m_tty_index, ret);
        return ret;
    }

    p_tty_dev = pt_tty->driver_data;
    //hwlog_debug("%s %d: tty index is %d\n", __func__,__LINE__, p_tty_dev->m_tty_index);

    /* record left data length for the modem tty device */
    p_tty_dev->m_wr_left_len = t_count;

    /* call channel write function to write current packet */
    ret = modem_tty_write_to_channel(p_tty_dev->m_tty_index, pt_buf, t_count);

    return ret;
}

void modem_tty_wakeup(unsigned int t_tty_index)
{
    struct modem_tty_dev* p_tty_dev = NULL;
    struct tty_struct* p_tty = NULL;

    p_tty_dev = g_modem_ttys.pm_tty_devs[t_tty_index];
    p_tty = tty_port_tty_get(&p_tty_dev->m_tty_port);

    if (p_tty)
    {
        tty_wakeup(p_tty);
        tty_kref_put(p_tty);
    }
}
EXPORT_SYMBOL(modem_tty_wakeup);

static int modem_tty_port_activate(struct tty_port* pt_tty_port, struct tty_struct* pt_tty)
{
    struct modem_tty_dev* p_tty_dev = NULL;

    p_tty_dev = container_of(pt_tty_port, struct modem_tty_dev, m_tty_port);
    hwlog_info("%s %d: tty dev %d enter.\n", __func__, __LINE__, p_tty_dev->m_tty_index);

    reset_channel_kfifo(p_tty_dev->m_tty_index + 1);

    if (p_tty_dev->m_buf_in_num > 0)
    {
        read_buffered_data_before_open(p_tty_dev);
    }

    hwlog_info("%s %d: p_tty_dev %d Leave.\n", __func__, __LINE__, p_tty_dev->m_tty_index);
    return 0;
}

static void modem_tty_port_shutdown(struct tty_port* pt_port)
{
    struct modem_tty_dev* p_tty_dev = NULL;

    p_tty_dev = container_of(pt_port, struct modem_tty_dev, m_tty_port);

    if (!p_tty_dev)
    {
        hwlog_info("%s %d: tty dev cannot be found.\n", __func__, __LINE__);
        return ;
    }

    hwlog_info("%s %d: tty dev %d enter.\n", __func__, __LINE__, p_tty_dev->m_tty_index);

    clean_buffered_data_on_close(p_tty_dev);

    hwlog_info("%s %d: tty dev %d Leave.\n", __func__, __LINE__, p_tty_dev->m_tty_index);
}

static const struct tty_port_operations modem_tty_port_ops =
{
    .shutdown = modem_tty_port_shutdown,
    .activate = modem_tty_port_activate,
};

static const struct tty_operations modem_tty_ops =
{
    .open            = modem_tty_open,
    .close            = modem_tty_close,
    .write            = modem_tty_write,
    .write_room        = modem_tty_write_room,
    .chars_in_buffer    = modem_tty_chars_in_buffer,
    .set_termios        = modem_tty_set_termios,
    .tiocmget        = modem_tty_tiocmget,
    .tiocmset        = modem_tty_tiocmset,
    .hangup            = modem_tty_hangup,
    .install        = modem_tty_install,
    .cleanup        = modem_tty_cleanup,
};

static void modem_tty_remove(struct ext_modem* modem)
{
    struct modem_tty_dev* p_tty_dev;
    struct tty_struct* p_tty;
    int index;
    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);

    for (index = 0; index < MODEM_TTY_NR; index++)
    {
        p_tty_dev = g_modem_ttys.pm_tty_devs[index];
        p_tty = tty_port_tty_get(&p_tty_dev->m_tty_port);

        /* tty_hangup is async so is this safe as is ?? */
        if (p_tty)
        {
            hwlog_info("%s %d destory tty,index=%d tty device index=%d\n", __func__, __LINE__, index, p_tty_dev->m_tty_index);
            tty_hangup(p_tty);
            tty_kref_put(p_tty);
        }

        mutex_unlock(&p_tty_dev->m_tty_port.mutex);

    }

    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
}

/**
 * modem_tty_push - push data to modem tty dirver
 * @t_tty_index: the tty index extract from packet header
 * @pt_payload_buf: pointer to packet payload data
 * @t_count: low-level received packet length include offset
 *
 * Returns:
 *   0 - push sucess
 *   minus - error occurred
 */
int modem_tty_push(int t_tty_index, unsigned char* pt_payload_buf, int t_payload_len)
{
    struct modem_tty_dev* p_tty_dev = NULL;
    struct tty_struct* p_tty = NULL;
    struct modem_buf_in_packet* packet = NULL;
    int ret = 0;

    if ((NULL == pt_payload_buf) || (0 == t_payload_len))
    {
        hwlog_err("%s %d: input payload buffer is 0x%lx, length is %d\n", __func__, __LINE__, \
                  (unsigned long)pt_payload_buf, t_payload_len);
        return -1;
    }

    p_tty_dev = g_modem_ttys.pm_tty_devs[t_tty_index];
    if( NULL == p_tty_dev )
    {
        hwlog_err("%s %d p_tty_dev==NULL on channel index t_tty_index:%d\n", __func__, __LINE__, t_tty_index);
        return -1;
    }

    mutex_lock(&p_tty_dev->m_buf_in_mutex);
    p_tty = tty_port_tty_get(&p_tty_dev->m_tty_port);

    if (!p_tty)
    {
        p_tty_dev->m_buf_in_size += t_payload_len;

        if (p_tty_dev->m_buf_in_size > MODEM_BUF_IN_MAX_SIZE)
        {
            p_tty_dev->m_buf_in_size -= t_payload_len;
            hwlog_err("%s %d: ttyVIA%d data buffer overrun!\n", __func__, __LINE__, t_tty_index);
            goto out;
        }
        else
        {
            packet = kzalloc(sizeof(struct modem_buf_in_packet), GFP_KERNEL);
            if (!packet)
            {
                hwlog_err("%s %d: dev %d kzalloc packet error\n", __func__, __LINE__, t_tty_index);
                ret = -1;
                goto out;
            }

            packet->m_size = t_payload_len;
            packet->pm_buffer = kzalloc(packet->m_size, GFP_KERNEL);

            if (!packet->pm_buffer)
            {
                hwlog_err("%s %d: tty dev %d kzalloc packet buffer error\n", __func__, __LINE__, t_tty_index);
                kfree(packet);
                ret = -2;
                goto out;
            }

            memcpy(packet->pm_buffer, pt_payload_buf, packet->m_size);

            if (p_tty_dev->m_buf_in_num < p_tty_dev->m_buf_in_maxnum)
            {
                list_add_tail(&packet->m_node, &p_tty_dev->m_buf_in_list);
                p_tty_dev->m_buf_in_num++;
            }
            else
            {
                struct modem_buf_in_packet* old_packet = NULL;
                old_packet = list_first_entry(&p_tty_dev->m_buf_in_list, struct modem_buf_in_packet, m_node);

                if (!old_packet)
                {
                    hwlog_err("%s %d: the  packet cannot be found\n", __func__, __LINE__);
                    kfree(packet->pm_buffer);
                    kfree(packet);
                    ret = -3;
                    goto out;
                }

                list_del(&old_packet->m_node);
                p_tty_dev->m_buf_in_size -= old_packet->m_size;
                kfree(old_packet->pm_buffer);
                kfree(old_packet);
                list_add_tail(&packet->m_node, &p_tty_dev->m_buf_in_list);
            }
            hwlog_debug("%s %d: ttyVIA%d data buffered! \n", __func__, __LINE__, t_tty_index);
        }
    }

    if (p_tty && t_payload_len)
    {
        ret = tty_buffer_request_room(&p_tty_dev->m_tty_port, t_payload_len);

        if (ret < t_payload_len)
        {
            hwlog_debug("%s %d: ttyVIA%d no room in tty rx buffer!\n", __func__, __LINE__, t_tty_index);
        }
        else
        {
            ret = tty_insert_flip_string(&p_tty_dev->m_tty_port, pt_payload_buf, t_payload_len);

            if (ret < t_payload_len)
            {
                hwlog_err("%s %d: ttyVIA%d couldn't insert all characters (TTY is full?)!\n", __func__, __LINE__, t_tty_index);
            }
            else
            {
                tty_flip_buffer_push(&p_tty_dev->m_tty_port);
            }
        }
    }

out:
    tty_kref_put(p_tty);
    mutex_unlock(&p_tty_dev->m_buf_in_mutex);

    return ret;
}
EXPORT_SYMBOL(modem_tty_push);

static void modem_tty_dev_cleanup(int t_index)
{
    struct modem_tty_dev* p_tty_dev = NULL;

    p_tty_dev = g_modem_ttys.pm_tty_devs[t_index];

    p_tty_dev->m_buf_in_num = 0;
    p_tty_dev->m_buf_in_size = 0;
}

void modem_tty_devs_reset(void)
{
    struct modem_tty_dev* p_tty_dev = NULL;
    struct tty_struct* p_tty = NULL;
    int i = 0;

    for (i = 0; i < MODEM_TTY_NR; i++)
    {
        p_tty_dev = g_modem_ttys.pm_tty_devs[i];

        mutex_lock(&p_tty_dev->m_tty_port.mutex);
        p_tty = tty_port_tty_get(&p_tty_dev->m_tty_port);

        if (p_tty)
        {
            tty_hangup(p_tty);
            tty_kref_put(p_tty);
        }

        mutex_unlock(&p_tty_dev->m_tty_port.mutex);

        clean_buffered_data_on_close(p_tty_dev);
        modem_tty_dev_cleanup(i);
    }
}
EXPORT_SYMBOL(modem_tty_devs_reset);

static void modem_buffer_in_set_max_len(struct modem_tty_dev* pt_tty_dev)
{
    unsigned int    index = pt_tty_dev->m_tty_index;

    switch (index)
    {
        case 0:
            pt_tty_dev->m_buf_in_maxnum = MODEM_PPP_BUF_IN_MAX_NUM;
            break;

        case 1:
            pt_tty_dev->m_buf_in_maxnum = MODEM_ETS_BUF_IN_MAX_NUM;
            break;

        case 2:
            pt_tty_dev->m_buf_in_maxnum = MODEM_IFS_BUF_IN_MAX_NUM;
            break;

        case 3:
            pt_tty_dev->m_buf_in_maxnum = MODEM_AT_BUF_IN_MAX_NUM;
            break;

        case 4:
            pt_tty_dev->m_buf_in_maxnum = MODEM_PCV_BUF_IN_MAX_NUM;
            break;

        default:
            pt_tty_dev->m_buf_in_maxnum = MODEM_DEF_BUF_IN_MAX_NUM;
            break;
    }
}

static int modem_tty_dev_init(int t_index)
{
    int ret = 0;
    struct modem_tty_dev* p_tty_dev = NULL;

    p_tty_dev = g_modem_ttys.pm_tty_devs[t_index];

    p_tty_dev->m_tty_index = t_index;

    mutex_init(&p_tty_dev->m_buf_in_mutex);
    INIT_LIST_HEAD(&p_tty_dev->m_buf_in_list);
    p_tty_dev->m_buf_in_num = 0;
    p_tty_dev->m_buf_in_size = 0;
    modem_buffer_in_set_max_len(p_tty_dev);

    return ret;
}

int modem_ttys_init(void)
{
    int ret;
    int index = 0;
    struct tty_driver* p_tty_drv;
    struct modem_tty_dev* p_tty_dev;
    struct device* dev;

    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    g_modem_ttys.pm_tty_drv = p_tty_drv = alloc_tty_driver(MODEM_TTY_NR);

    if (!p_tty_drv)
    {
        hwlog_err("%s %d: alloc_tty_driver failed, no memory!.\n", __func__, __LINE__);
        ret = -ENOMEM;
        goto err_alloc_driver;
    }

    p_tty_drv->owner = THIS_MODULE;
    p_tty_drv->driver_name = "modem_tty";
    p_tty_drv->name =   "ttySPI"; /* to be replaced by ttyVIA */
    p_tty_drv->major = 0;  // dynamically allocated
    p_tty_drv->minor_start = 0;
    p_tty_drv->type = TTY_DRIVER_TYPE_SERIAL;
    p_tty_drv->subtype = SERIAL_TYPE_NORMAL;
    p_tty_drv->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
    p_tty_drv->init_termios = tty_std_termios;
    p_tty_drv->init_termios.c_cflag = B9600 | CS8 | CREAD | HUPCL | CLOCAL;
    p_tty_drv->init_termios.c_cflag &= ~(CSIZE | CSTOPB | PARENB | PARODD);
    p_tty_drv->init_termios.c_cflag |= CREAD | CLOCAL | CS8 ;
    p_tty_drv->init_termios.c_cflag &= ~(CRTSCTS);
    p_tty_drv->init_termios.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ISIG);
    p_tty_drv->init_termios.c_iflag &= ~(INPCK | IGNPAR | PARMRK | ISTRIP | IXANY | ICRNL);
    p_tty_drv->init_termios.c_iflag &= ~(IXON | IXOFF);
    p_tty_drv->init_termios.c_oflag &= ~(OPOST | OCRNL);
    p_tty_drv->init_termios.c_ispeed = 9600;
    p_tty_drv->init_termios.c_ospeed = 9600;
    tty_set_operations(p_tty_drv, &modem_tty_ops);

    ret = tty_register_driver(p_tty_drv);

    if (ret)
    {
        hwlog_err("%s %d: tty_register_driver failed.\n", __func__, __LINE__);
        ret = -2;
        goto err_reg_driver;
    }

    for (index = 0; index < MODEM_TTY_NR; index++)
    {
        p_tty_dev = kzalloc(sizeof(struct modem_tty_dev), GFP_KERNEL);

        if (!p_tty_dev)
        {
            hwlog_err("%s %d kzalloc modem_tty_dev %d failed.\n",
                      __func__, __LINE__, index);
            ret = -ENOMEM;
            goto err_kzalloc;
        }

        tty_port_init(&p_tty_dev->m_tty_port);
        p_tty_dev->m_tty_port.ops = &modem_tty_port_ops;
        g_modem_ttys.pm_tty_devs[index] = p_tty_dev;
        /* initialize every modem tty device */
        modem_tty_dev_init(index);

        dev = tty_port_register_device(&p_tty_dev->m_tty_port, g_modem_ttys.pm_tty_drv,
                                       p_tty_dev->m_tty_index, NULL);

        if (IS_ERR(dev))
        {
            ret = PTR_ERR(dev);
            hwlog_err("%s %d: p_tty_dev %d tty register failed \n", __func__, __LINE__, p_tty_dev->m_tty_index);
            ret = -4;
            goto err_reg_device;
        }
    }

    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    return ret;

err_reg_device:
err_kzalloc:
    index--;

    for (; index >= 0; index--)
    {
        if (g_modem_ttys.pm_tty_devs[index])
        {
            kfree(g_modem_ttys.pm_tty_devs[index]);
            g_modem_ttys.pm_tty_devs[index] = NULL;
        }
    }

    tty_unregister_driver(p_tty_drv);
err_reg_driver:
err_alloc_driver:
    hwlog_err("%s %d: returning with error %d\n", __func__, __LINE__, ret);
    put_tty_driver(p_tty_drv);
    return ret;
}
EXPORT_SYMBOL(modem_ttys_init);

void modem_ttys_exit(void)
{
    struct modem_tty_dev* p_tty_dev = NULL;
    int index = 0;

    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    tty_unregister_driver(g_modem_ttys.pm_tty_drv);
    put_tty_driver(g_modem_ttys.pm_tty_drv);

    for (index = 0; index < MODEM_TTY_NR; index++)
    {
        modem_tty_dev_cleanup(index);

        p_tty_dev = g_modem_ttys.pm_tty_devs[index];
        clean_buffered_data_on_close(p_tty_dev);

        tty_unregister_device(g_modem_ttys.pm_tty_drv, index);
    }

    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
}
EXPORT_SYMBOL(modem_ttys_exit);

