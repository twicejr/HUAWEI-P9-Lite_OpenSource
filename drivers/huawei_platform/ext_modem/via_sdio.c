/*
 * via_sdio.c
 *
 */

#include <linux/module.h>
#include <linux/mod_devicetable.h>
#include <linux/mmc/core.h>
#include <linux/mmc/card.h>
#include <linux/mmc/sdio.h>
#include <linux/mmc/sdio_ids.h>
#include <linux/mmc/host.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/delay.h>

#include "viatel.h"
#include "ext_modem.h"
#include "modem_packet.h"
#include "via_gpios.h"
#include "4wire_wake.h"
#include "apcp_test.h"
#include "via_sdio.h"
#include "power.h"


#define VIA_SDIO_FIFO_SIZE         1024
#define VIA_SDIO_BLOCK_SIZE     512
#define VIA_SDIO_MAX_PACKET_SIZE         1024
#define MAX_SDIO_IRQ_QUERY_RETRY    8
#define VIA_SDIO_IRQ_QUERY_WAIT     200
#define MAX_SDIO_INT_STATUS_RETRY   10
#define VIA_SDIO_INT_STATUS_SET     1

/* VIA SDIO specific register */
#define VIA_SDIO_REGISTER_DATA              0x00
#define VIA_SDIO_REGISTER_INT_STATUS    0x04
#define VIA_SDIO_REGISTER_LENGTH_LOW    0x08
#define VIA_SDIO_REGISTER_LENGTH_HIGH   0x09
#define VIA_SDIO_REGISTER_RESERVED         0x28


static struct via_sdio_dev g_via_sdio;

static int test_modem_read_from_via_flag = 0;

static int modem_detect(void)
{
    /* HACK!!!
    * Rely on mmc->class_dev.class set in mmc_alloc_host
    * Tricky part: a new mmc hook is being (temporary) created
    * to discover mmc_host class.
    * Do you know more elegant way how to enumerate mmc_hosts?
    */
    struct mmc_host* mmc = NULL;
    struct class_dev_iter iter;
    struct device* dev;
    int ret = -1;

    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    mmc = mmc_alloc_host(0, NULL);

    if (!mmc)
    {
        ret =  -ENOMEM;
        goto out;
    }

    BUG_ON(!mmc->class_dev.class);
    class_dev_iter_init(&iter, mmc->class_dev.class, NULL, NULL);

    for (;;)
    {
        dev = class_dev_iter_next(&iter);

        if (!dev)
        {
            break;
        }
        else
        {
            struct mmc_host* host = container_of(dev, struct mmc_host, class_dev);

            if ( !(host->caps2 & MMC_CAP2_SUPPORT_VIA_MODEM) )
            {
                hwlog_info("%s %d mmc class_dev name: %s NOT for via\n", __func__, __LINE__, dev_name(&host->class_dev));
                continue;
            }

            hwlog_info("%s:%d find mmc host connected to via modem:%s\n", __func__, __LINE__, mmc_hostname(host));
            mmc_detect_change(host, 0);
            ret = 0;
            break;
        }
    }

    mmc_free_host(mmc);
out:
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    return ret;
}

static int func_enable_irq(struct sdio_func* pt_func, int t_enable)
{
    int func_num = 0;
    u8 cccr = 0;
    int ret = 0;

    /* Hack to access Fuction-0 */
    func_num = pt_func->num;
    pt_func->num = 0;

    cccr = sdio_readb(pt_func, SDIO_CCCR_IENx, &ret);

    if (WARN_ON(ret))
    { goto set_func; }

    if (t_enable)
    {
        /* Master interrupt enable ... */
        cccr |= BIT(0);
        /* ... for our function */
        cccr |= BIT(func_num);
    }
    else
    {
        /* Master interrupt enable ... */
        cccr &= ~(BIT(0));
        /* ... for our function */
        cccr &= ~(BIT(func_num));
    }

    sdio_writeb(pt_func, cccr, SDIO_CCCR_IENx, &ret);

    if (WARN_ON(ret))
    { goto set_func; }

    /* Restore the modem function number */
    pt_func->num = func_num;
    return 0;

set_func:
    pt_func->num = func_num;
    return ret;
}

/**
 * via_sdio_write - write subpacket through sdio bus
 * @pt_tx_subpkt_buf: high-level write subpacket buffer address
 * @t_len: length of subpacket to write
 *
 * Returns:
 *   0 - success, write subpacket success
 *   minus - error occured when write through sdio bus
 */
static int via_sdio_write(void* pt_tx_subpkt_buf, size_t t_len)
{
    int ret = 0;

    /* copy high-level data to tx packet buffer */
    memcpy(g_via_sdio.pm_sdio_page_buf, pt_tx_subpkt_buf, t_len);

    ret = sdio_writesb(g_via_sdio.pm_sdio, VIA_SDIO_REGISTER_DATA, pt_tx_subpkt_buf, t_len);

    if (ret)
    {
        hwlog_err("%s %d: failed ret=%d\n", __func__, __LINE__, ret);
        return -1;
    }

    return 0;
}

/**
 * via_sdio_read - read subpacket through sdio bus
 * @pt_rx_subpkt_buf: high-level receive subpacket buffer address
 * @t_len: length of subpacket to read
 *
 * Returns:
 *   0 - success, read subpacket success
 *   minus - error occured when read through sdio bus
 */
static int via_sdio_read(void* pt_rx_subpkt_buf, size_t t_len)
{
    int ret = 0;

    ret = sdio_readsb(g_via_sdio.pm_sdio, pt_rx_subpkt_buf, VIA_SDIO_REGISTER_DATA, t_len);

    if (ret)
    {
        hwlog_err("%s %d: sdio read with error code = %d, read bytecount = %lu!!!\n",
                  __func__, __LINE__, ret, t_len);
        ret = -1;
    }

    if ( test_modem_read_from_via_flag )
    {
        hwlog_info("%s %d bytecnt:%lu, sdio_readsb return:%d\n", __func__, __LINE__, t_len, ret);
    }

    return ret;
}

static int via_sdio_bus_lock(int t_lock)
{
    if (t_lock)
    {
        sdio_claim_host(g_via_sdio.pm_sdio);
    }
    else
    {
        sdio_release_host(g_via_sdio.pm_sdio);
    }
    return 0;
}

static int via_sdio_irq_enable(int t_enable)
{
    int ret = 0;

    ret = func_enable_irq(g_via_sdio.pm_sdio, t_enable);
    if (ret)
    {
        hwlog_err("%s %d: sdio func irq enable=%d, fail ret=%d\n", __func__, __LINE__, t_enable, ret);
        return -1;
    }

    return 0;
}

modem_bus_t via_sdio_bus =
{
    .m_bus_type = MODEM_BUS_SDIO,
    .m_fifo_size = VIA_SDIO_FIFO_SIZE,
    .pfm_bus_write = via_sdio_write,
    .pfm_bus_read = via_sdio_read,
    .pfm_bus_lock = via_sdio_bus_lock,
    .pfm_bus_irq_enable = via_sdio_irq_enable,
};

/*query modem func's pending irq flag*/
static int modem_irq_query(struct sdio_func* pt_func, unsigned char* pt_pendingirq)
{
    int func_num = 0;
    int ret = 0;
    int retry = MAX_SDIO_IRQ_QUERY_RETRY;

    /* Hack to access Fuction-0 */
    /*CBP just support function-0*/
    func_num = pt_func->num;
    pt_func->num = 0;

    do
    {
        if (0 == get_modem_bus_state())
        {
            hwlog_err("%s %d: VIA modem reset happened\n", __func__, __LINE__);
            ret = -1;
            break;
        }

        *pt_pendingirq = sdio_readb(pt_func, SDIO_CCCR_INTx, &ret);

        if (ret)
        {
            hwlog_err("%s %d read SDIO_CCCR_INTx err ret= %d retry %d\n", __func__, __LINE__, ret, retry);
            msleep(VIA_SDIO_IRQ_QUERY_WAIT);
        }
        else
        {
            break;
        }
    }
    while (retry--);

    pt_func->num = func_num;

    return ret;
}

/*
 * This SDIO interrupt handler.
 */
static void modem_sdio_irq(struct sdio_func* pt_func)
{
    unsigned char reg = 0;
    int  bytecnt = 0;
    int ret = 0;
    int iir = 0;
    int readcnt = 0;
    unsigned char pending = 0;
    char rst_buf[CBP_EXCEPT_STACK_LEN]={0};

    hwlog_debug("%s %d: enter.\n", __func__, __LINE__);
    ap_busy_wake();

    /* count rx irq */
    apcp_rx_irq_count();

    ret = modem_irq_query(pt_func, &pending);

    if (ret)
    {
        hwlog_err("%s %d read SDIO_CCCR_INTx err ret= %d\n", __func__, __LINE__, ret);
        goto err_out;
    }

    if ((pending & SDIO_FUNC_1) == 0)
    {
        hwlog_err("modem_sdio_irq pending=%d ret= %d\n", pending, ret);
        goto out;
    }

    do
    {
        /* Reading the IIR register on the slave clears the interrupt. Since host and
           slave run asynchronously, must ensure int bit is set before reading
           transfer count register  */
        iir =  sdio_readb(pt_func, VIA_SDIO_REGISTER_INT_STATUS, &ret);
    }
    while ( (iir != VIA_SDIO_INT_STATUS_SET)  && (readcnt++ <= MAX_SDIO_INT_STATUS_RETRY));

    /* judge result of sdio read */
    if (ret)
    {
        hwlog_err("%s %d read iir err ret= %d\n", __func__, __LINE__, ret);
        goto err_out;
    }

    /* judge int status read from VIA sdio register */
    if (iir != VIA_SDIO_INT_STATUS_SET)
    {
        hwlog_err("%s %d error iir value = %d!!!\n", __func__, __LINE__, iir);
        goto out;
    }

    /* Read byte count */
    reg =  sdio_readb(pt_func, VIA_SDIO_REGISTER_LENGTH_LOW, &ret);

    if (ret)
    {
        hwlog_err("%s %d read data cnt err ret= %d\n", __func__, __LINE__, ret);
        goto err_out;
    }

    bytecnt = reg;
    reg =  sdio_readb(pt_func, VIA_SDIO_REGISTER_LENGTH_HIGH, &ret);

    if (ret)
    {
        hwlog_err("%s %d read data cnt ret= %d\n", __func__, __LINE__, ret);
        goto err_out;
    }
    bytecnt |= (reg << 8);

    if (bytecnt == 0)
    {
        hwlog_err("%s %d error read size %d.\n", __func__, __LINE__, bytecnt);
        goto out;
    }

    /* call modem read handler to read data from via */
    hwlog_debug("%s %d read size %d.\n", __func__, __LINE__, bytecnt);

    modem_one_packet_read(bytecnt);
out:
    ap_timed_idle_wake();
    return;

err_out:
    hwlog_err("%s %d: let cbp die now.\n", __func__, __LINE__);
    ap_timed_idle_wake();
    snprintf(rst_buf, CBP_EXCEPT_STACK_LEN, "%s %d:read error notify VIA CBP to produce ramdump.\n", __func__, __LINE__);   
    hwlog_err("%s %d: read error notify VIA CBP to produce ramdump.\n", __func__, __LINE__);
    if(is_via_modem_state_ready())
    {
        modem_err_indication_usr_form_module(rst_buf, CBP_EXCEPT_REASON_SPI, CBP_EXCE_MID_SPI_READ_TIMEOUT);
    }
    return;
}

int test_modem_read_from_via(void)
{
    hwlog_info("%s %d enter\n", __func__, __LINE__);

    if (g_via_sdio.pm_sdio == NULL)
    {
        hwlog_info("via_modem is NULL, return\n");
        return -1;
    }

    sdio_claim_host(g_via_sdio.pm_sdio);

    ap_tx_wait_cp_ready();

    test_modem_read_from_via_flag = 1;

    modem_sdio_irq(g_via_sdio.pm_sdio);

    sdio_release_host(g_via_sdio.pm_sdio);

    test_modem_read_from_via_flag = 0;

    hwlog_info("%s %d exit\n", __func__, __LINE__);

    return 0;
}
EXPORT_SYMBOL_GPL(test_modem_read_from_via);

static int modem_sdio_probe(struct sdio_func* pt_func,
                            const struct sdio_device_id* pt_id)
{
    int ret = 0;

    hwlog_info("%s %d: enter.\n", __func__, __LINE__);
    g_via_sdio.pm_sdio = pt_func;
    sdio_set_drvdata(g_via_sdio.pm_sdio , &g_via_sdio);

    /* setup sdio */
    sdio_claim_host(g_via_sdio.pm_sdio);
    ret = sdio_enable_func(g_via_sdio.pm_sdio);

    if (ret)
    {
        hwlog_err("%s %d sdio enable func failed with ret = %d\n", __func__, __LINE__, ret);
        goto err_enable_func;
    }

    ret = sdio_set_block_size(g_via_sdio.pm_sdio, VIA_SDIO_BLOCK_SIZE);

    if (ret)
    {
        hwlog_err("%s %d: set block size failed with ret = %d\n", __func__, __LINE__, ret);
        goto error_set_block_size;
    }

    /* void sdio_writeb return no value */
    sdio_writeb(g_via_sdio.pm_sdio, 0x01, VIA_SDIO_REGISTER_RESERVED, &ret);

    ret = sdio_claim_irq(g_via_sdio.pm_sdio, modem_sdio_irq);

    if (ret)
    {
        hwlog_err("%s %d sdio claim irq failed.\n", __func__, __LINE__);
        goto error_set_block_size;
    }

    /* register via sdio bus to modem common driver */
    modem_bus_register(&via_sdio_bus);
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    sdio_release_host(g_via_sdio.pm_sdio);
    return ret;

error_set_block_size:
    sdio_disable_func(g_via_sdio.pm_sdio);
err_enable_func:
    sdio_release_host(g_via_sdio.pm_sdio);

    return ret;
}

void modem_sdio_reset(void)
{
    int ret = 0;

    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    sdio_claim_host(g_via_sdio.pm_sdio);
    ret = sdio_disable_func(g_via_sdio.pm_sdio);

    if (ret < 0)
    {
        hwlog_err("%s: sdio_disable_func failed.\n", __func__);
    }

    ret = sdio_release_irq(g_via_sdio.pm_sdio);

    if (ret < 0)
    {
        hwlog_err("%s: sdio_release_irq failed.\n", __func__);
    }

    sdio_release_host(g_via_sdio.pm_sdio);
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
}

static void modem_sdio_remove(struct sdio_func* pt_sdio)
{
    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    /* first clear the sdio bus handler */
    modem_bus_register(NULL);
    modem_sdio_reset();
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);

}

static int modem_sdio_suspend(struct device* pt_dev)
{
    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    set_ap_bus_suspend();
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    return 0;
}

static int modem_sdio_resume(struct device* pt_dev)
{
    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    set_ap_bus_resumed();
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    return 0;
}

#ifdef CONFIG_PM_RUNTIME
static int modem_sdio_runtime_suspend(struct device* dev)
{
    hwlog_info(" %s %d ++ \n", __func__, __LINE__);
    hwlog_info(" %s %d -- \n", __func__, __LINE__);
    return 0;
}
static int modem_sdio_runtime_resume(struct device* dev)
{
    hwlog_info(" %s %d ++ \n", __func__, __LINE__);
    hwlog_info(" %s %d -- \n", __func__, __LINE__);
    return 0;
}
#endif

static const struct dev_pm_ops modem_sdio_pmops =
{
    SET_SYSTEM_SLEEP_PM_OPS(modem_sdio_suspend, modem_sdio_resume)
#ifdef CONFIG_PM_RUNTIME
    SET_RUNTIME_PM_OPS(modem_sdio_runtime_suspend,	modem_sdio_runtime_resume, NULL)
#endif
};


#define SDIO_VENDOR_ID_CBP        0x0296
#define SDIO_DEVICE_ID_CBP        0x5347

static const struct sdio_device_id modem_sdio_ids[] =
{
    { SDIO_DEVICE(SDIO_VENDOR_ID_CBP, SDIO_DEVICE_ID_CBP) }, /* VIA-Telecom CBP */
    {} /* Terminating entry */
};
MODULE_DEVICE_TABLE(of, modem_sdio_ids);

static struct sdio_driver modem_sdio_driver =
{
    .probe        = modem_sdio_probe,
    .remove        = modem_sdio_remove,
    .name        = "modem_sdio",
    .id_table    = modem_sdio_ids,
    .drv 			= {
        .name = "via_modem_sdio",
        .pm  = &modem_sdio_pmops,
    },
};

int via_sdio_init(void)
{
    int ret;

    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    ret = sdio_register_driver(&modem_sdio_driver);

    if (ret)
    {
        hwlog_err("%s %d: sdio_register_driver failed.\n", __func__, __LINE__);
        ret = -1;
        goto err_sdio_reg_drv;
    }

    g_via_sdio.pm_sdio_page_buf = (char*)__get_free_pages(GFP_KERNEL, 0);

    if (!g_via_sdio.pm_sdio_page_buf)
    {
        hwlog_err("%s %d: probe - sdio request via_sdio_start_buf memory error", __func__, __LINE__);
        ret = -2;
        goto err_get_page_buf;
    }

    modem_register_reset_handle(MODEM_BUS_SDIO, (pf_mdm_reset_handle)modem_detect);
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    return ret;

    free_pages((unsigned long)g_via_sdio.pm_sdio_page_buf, 0);
err_get_page_buf:
    sdio_unregister_driver(&modem_sdio_driver);
err_sdio_reg_drv:

    return ret;
}
EXPORT_SYMBOL(via_sdio_init);

void via_sdio_exit(void)
{
    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    sdio_unregister_driver(&modem_sdio_driver);

    if (g_via_sdio.pm_sdio_page_buf)
    {
        free_pages((unsigned long)g_via_sdio.pm_sdio_page_buf, 0);
    }

    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
}
EXPORT_SYMBOL(via_sdio_exit);

