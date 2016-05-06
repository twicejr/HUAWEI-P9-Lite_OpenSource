/*
 * via_spi.c
 *
 */

#include <linux/module.h>
#include <linux/mod_devicetable.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/wait.h>
#include <linux/delay.h>

#include "viatel.h"
#include "ext_modem.h"
#include "via_spi.h"
#include "modem_packet.h"

#define VIA_SPI_MODE                        (SPI_MODE_1)
#define VIA_SPI_SPEED                       12000000
#define VIA_SPI_BIT_WIDTH                   8
#define VIA_SPI_START_BUF_SIZE         60
#define VIA_SPI_FIFO_SIZE                   512
#define SPI_TRANS_MAX_TRY_TIMES    10
#define SPI_TRANS_WAIT_TIME             2000


static struct via_spi_dev g_via_spi;


/** * via_spi_read_work - work for read packet from modem through spi
* @pt_work: read work
*
* Returns:
*   none
*/
static void via_spi_read_work(struct work_struct* pt_work)
{
    char pre_read_handshake_buf[256];
    int ret = 0;

    /*
     * -------------------------------------------------------------------------
     * |0xFE|ChanInfo(1Byte)|ThanHi(1Byte)|TranLow(1Byte)|Dummy|Paylaod|Padding|
     * -------------------------------------------------------------------------
     */
    /* VIA SPI special handshake packet before data packet read */
    pre_read_handshake_buf[0] = 0xFE;
    pre_read_handshake_buf[1] = 0x80;
    pre_read_handshake_buf[2] = 0x0;
    pre_read_handshake_buf[3] = 0x0;

    ret = modem_write(pre_read_handshake_buf, 4);

    if (ret)
    {
        hwlog_err("%s %d: modem write return %d", __func__, __LINE__, ret);
        return;
    }

    /* parameter is 0, means packet length is unknown now, need to read from packet header */
    modem_one_packet_read(0);
}

/**
 * via_spi_rts_isr - SPI request to send interrupt handler in top-half
 *
 * Returns:
 *   none
 */
void via_spi_rts_isr(void)
{
    /* queue modem read work to read data from via */
    queue_work(g_via_spi.pm_read_wq, &g_via_spi.m_read_work);
}
EXPORT_SYMBOL(via_spi_rts_isr);

/**
 * via_spi_transfer - tx or rx data through spi bus
 * @t_len: length of data to tx or rx
 * @t_is_tx: true when tx, false when rx
 *
 * Returns:
 *   0 - success, read subpacket success
 *   minus - error occured when read through spi bus
 */
static int via_spi_transfer(size_t t_len, int t_is_tx)
{
    unsigned int spi_failed_times = 0;
    int status = 0;
    struct spi_message  m;
    struct spi_transfer xfer =
    {
        .tx_buf = NULL,
        .rx_buf = NULL,
        .len = t_len,
    };

    /* first judge the transfer direction */
    if (t_is_tx)   /* SPI tx now */
    {
        xfer.tx_buf = g_via_spi.pm_spi_page_buf;
    }
    else     /* SPI rx now */
    {
        xfer.rx_buf = g_via_spi.pm_spi_page_buf;
    }

    spi_message_init(&m);
    spi_message_add_tail(&xfer, &m);

    /* SPI will retry transfer same buffer with MAX times if need */
    do
    {
        status = spi_sync(g_via_spi.pm_spi, &m);

        /* judge if spi sync success */
        if (0 == status)
        {
            break;
        }
        else
        {
            hwlog_err("%s - sync error: status=%d", __func__, status);
            msleep(SPI_TRANS_WAIT_TIME);
            spi_failed_times++;
        }
    }
    while (spi_failed_times < SPI_TRANS_MAX_TRY_TIMES);

    return status;
}

/**
 * via_spi_write - write subpacket through spi bus
 * @pt_tx_subpkt_buf: high-level write subpacket buffer address
 * @t_len: length of subpacket to write
 *
 * Returns:
 *   0 - success, write subpacket success
 *   minus - error occured when write through spi bus
 */
static int via_spi_write(void* pt_tx_subpkt_buf, size_t t_len)
{
    int status = 0;
    int len = 0;

    //hwlog_debug("%s %d: current buffer address is 0x%x, length is %d.\n", __func__, __LINE__, pt_tx_subpkt_buf, t_len);
    /* zero the spi page buffer */
    memset(g_via_spi.pm_spi_page_buf, 0, PAGE_SIZE);
    /* copy high-level data to tx packet buffer */
    memcpy(g_via_spi.pm_spi_page_buf, pt_tx_subpkt_buf, t_len);

    /* write to VIA SPI FIFO, VIA RX FIFO irq level is 60 bytes */
    if (t_len > VIA_SPI_START_BUF_SIZE)
    {
        len = t_len;
    }
    else
    {
        //for VIA RX FIFO interrupt watermark set to 60.
        len = VIA_SPI_START_BUF_SIZE;
    }

    /* set is_tx to true */
    status = via_spi_transfer(len, 1);

    return status;
}

/**
 * via_spi_read - read subpacket through spi bus
 * @pt_rx_subpkt_buf: high-level receive subpacket buffer address
 * @t_len: length of subpacket to read
 *
 * Returns:
 *   0 - success, read subpacket success
 *   minus - error occured when read through spi bus
 */
static int via_spi_read(void* pt_rx_subpkt_buf, size_t t_len)
{
    int status;

    //hwlog_debug("%s %d: current buffer address is 0x%x, length is %d.\n", __func__, __LINE__, pt_rx_subpkt_buf, t_len);
    /* set is_tx to false */
    status = via_spi_transfer(t_len, 0);

    if (0 == status)
    {
        /* copy spi read data to rx packet buffer */
        memcpy(pt_rx_subpkt_buf, g_via_spi.pm_spi_page_buf, t_len);
    }

    return status;
}

modem_bus_t via_spi_bus =
{
    .m_bus_type = MODEM_BUS_SPI,
    .m_fifo_size = VIA_SPI_FIFO_SIZE,
    .pfm_bus_write = via_spi_write,
    .pfm_bus_read = via_spi_read,
    .pfm_bus_lock = NULL,
    .pfm_bus_irq_enable = NULL,
};

static int modem_spi_probe(struct spi_device* pt_spi)
{
    int ret = 0;

    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    g_via_spi.pm_spi = pt_spi;

    /* step 3: setup spi */
    pt_spi->mode = VIA_SPI_MODE;
    pt_spi->max_speed_hz = VIA_SPI_SPEED;
    pt_spi->bits_per_word = VIA_SPI_BIT_WIDTH;
    ret = spi_setup(pt_spi);

    if (ret < 0)
    {
        hwlog_err("%s %d: probe - setup spi error", __func__, __LINE__);
        ret = -1;
    }

    /* register via spi bus to modem common driver */
    modem_bus_register(&via_spi_bus);
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    return ret;
}

static int modem_spi_remove(struct spi_device* spi)
{
    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);

    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);

    return 0;
}

static int modem_spi_suspend(struct spi_device* spi, pm_message_t mesg)
{
    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    set_ap_bus_suspend();
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    return 0;
}

static int modem_spi_resume(struct spi_device* spi)
{
    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    set_ap_bus_resumed();
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    return 0;
}

static const struct of_device_id modem_spi_ids[] =
{
    { .compatible = "spi_dev4" },
    {},
};
MODULE_DEVICE_TABLE(of, modem_spi_ids);

static struct spi_driver modem_spi_driver =
{
    .driver = {
        .name = "spi_dev4",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(modem_spi_ids),
    },
    .probe        = modem_spi_probe,
    .remove        = modem_spi_remove,
    .suspend    = modem_spi_suspend,
    .resume        = modem_spi_resume,
};

int via_spi_init(void)
{
    int ret = 0;

    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    ret = spi_register_driver(&modem_spi_driver);

    if (ret)
    {
        hwlog_err("%s %d: spi_register_driver failed.\n", __func__, __LINE__);
        ret = -1;
        goto err_spi_reg_drv;
    }

    /* create a workqueue thread for bus read */
    g_via_spi.pm_read_wq = create_singlethread_workqueue("viaspi rd wq");

    if (g_via_spi.pm_read_wq == NULL)
    {
        hwlog_err("%s %d: error creat read workqueue \n", __func__, __LINE__);
        return -ENOMEM;
    }

    INIT_WORK(&g_via_spi.m_read_work, via_spi_read_work);

    g_via_spi.pm_spi_page_buf = (char*)__get_free_pages(GFP_KERNEL, 0);

    if (!g_via_spi.pm_spi_page_buf)
    {
        hwlog_err("%s %d: probe - spi request via_spi_start_buf memory error", __func__, __LINE__);
        ret = -2;
        goto err_get_page_buf;
    }

    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    return ret;

err_get_page_buf:
    spi_unregister_driver(&modem_spi_driver);
err_spi_reg_drv:

    return ret;
}
EXPORT_SYMBOL(via_spi_init);

void via_spi_exit(void)
{
    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    spi_unregister_driver(&modem_spi_driver);

    if (g_via_spi.pm_spi_page_buf)
    {
        free_pages((unsigned long)g_via_spi.pm_spi_page_buf, 0);
    }

    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
}
EXPORT_SYMBOL(via_spi_exit);

