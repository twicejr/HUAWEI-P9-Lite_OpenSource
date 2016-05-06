/*
 * ext_modem.c
 *
 * Huawei external Modem common driver
 *
 * Copyright (C) 2015 Huawei Device Co.Ltd
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/delay.h>

#include "viatel.h"
#include "via_gpios.h"
#include "modem_channels.h"
#include "via_sdio.h"
#include "4wire_wake.h"
#include "power.h"
#include "apcp_test.h"
#include "ext_modem.h"


#define DOWN_MODEM_SEMAPHORE_TIMEOUT_MS     2000 //2s
#define DOWN_MODEM_SEMAPHORE_RETRY_TIMES    150
#define DOWN_MODEM_SEMAPHORE_PRINT_LOG      15 //print log per 3 timeout

#define MAX_WAIT_DATA_ACK_RETRY    6
#define AP_HOST_CONTROLLER_RESUME_TIME    1000

ext_modem_t g_ext_modem = {0};


void modem_bus_register(modem_bus_t* pt_bus)
{
    g_ext_modem.pm_cur_bus = pt_bus;
}
EXPORT_SYMBOL(modem_bus_register);

void modem_register_reset_handle(bus_type_et t_type, pf_mdm_reset_handle pt_handle)
{
    g_ext_modem.m_arr_reset_handle[t_type] = pt_handle;
}

unsigned int get_modem_bus_state(void)
{
    return g_ext_modem.m_mdm_bus_ready;
}
EXPORT_SYMBOL(get_modem_bus_state);

void set_modem_bus_state(unsigned int t_ready)
{
    g_ext_modem.m_mdm_bus_ready = t_ready;
}
EXPORT_SYMBOL(set_modem_bus_state);

void set_ap_bus_suspend(void)
{
    atomic_set(&g_ext_modem.m_ap_resume_atom, AP_BUS_SUSPEND);
}
EXPORT_SYMBOL(set_ap_bus_suspend);

void set_ap_bus_resumed(void)
{
    atomic_set(&g_ext_modem.m_ap_resume_atom, AP_BUS_RESUMED);
    wake_up(&g_ext_modem.m_ap_resume_waitq);
}
EXPORT_SYMBOL(set_ap_bus_resumed);

/* wait AP host controller to resumed */
int wait_ap_bus_resumed(void)
{
    unsigned long remain_time = 0;
    unsigned int timeout_cnt = 0;

    hwlog_debug("%s %d entered\n", __func__, __LINE__);

    do
    {
        remain_time = wait_event_timeout(g_ext_modem.m_ap_resume_waitq, (AP_BUS_RESUMED == atomic_read(&g_ext_modem.m_ap_resume_atom)) || \
                                         (0 == get_modem_bus_state()), msecs_to_jiffies(WAIT_APCP_BUS_RESUME_TIMEOUT));

        if (0 == get_modem_bus_state())
        {
            hwlog_err("%s %d: VIA modem reset happened\n", __func__, __LINE__);
            return -1;
        }
        else if (0 == remain_time)
        {
            hwlog_info("%s %d: wait ap host controller to resume timeout\n", __func__, __LINE__);
            timeout_cnt++;

            if (timeout_cnt >= MAX_WAIT_BUS_RESUME_TIMES)
            {
                hwlog_err("%s %d: FAIL to wait ap host to resume with MAX retries\n", __func__, __LINE__);
                return -2;
            }
        }
    }
    while (0 == remain_time);

    return 0;
}
EXPORT_SYMBOL(wait_ap_bus_resumed);

int modem_bus_lock(void)
{
    int ret = 0;

    unsigned int nDownRetryTimes = 0;

    do
    {
        ret = down_timeout(&g_ext_modem.m_bus_sema, msecs_to_jiffies(DOWN_MODEM_SEMAPHORE_TIMEOUT_MS));

        if ( ret )
        {
            if (0 == get_modem_bus_state())
            {
                hwlog_err("%s %d down_timeout return:%d and signal_pending(current) is true or cbp_pwer_state:%d, return\n", __func__, __LINE__, ret, get_modem_bus_state());
                ret = -1;
                goto down_out;
            }

            nDownRetryTimes++;

            if (( nDownRetryTimes % DOWN_MODEM_SEMAPHORE_PRINT_LOG) == 0)
            {
                hwlog_err("%s %d down timeout return:%d, print log and continue\n", __func__, __LINE__, ret);
            }
        }
        else
        {
            //get the semaphore
            break;
        }
    }
    while (nDownRetryTimes <= DOWN_MODEM_SEMAPHORE_RETRY_TIMES);

    if (nDownRetryTimes > DOWN_MODEM_SEMAPHORE_RETRY_TIMES )
    {
        hwlog_err("%s %d down_timeout timeout exceed %d return\n", __func__, __LINE__, DOWN_MODEM_SEMAPHORE_RETRY_TIMES);
        return -2;
    }

    /* first let ap keep wake*/
    ap_busy_wake();

    return 0;

down_out:
    return ret;
}
EXPORT_SYMBOL(modem_bus_lock);

void modem_bus_unlock(void)
{
    ap_timed_idle_wake();

    up(&g_ext_modem.m_bus_sema);
}
EXPORT_SYMBOL(modem_bus_unlock);

/**
 * modem_write - write a packet payload data through bus
 * @pt_pkt_buf: high-level buffer address of packet payload data
 * @pt_header: in pointer to packet header
 *
 * Returns:
 *   0 - success write whole packet
 *   minus - error occurred when write whole tx packet
 */
int modem_write(char* pt_pkt_buf, int t_len)
{
    unsigned char* p_tx_subpkt_buf = NULL; /* point to current available space for write in tx packet buf */
    unsigned int cur_write_len = 0; /* current write length to the bus */
    int ret_wait_hw_fc = 0; /* wait and check hardware flow control to disable*/
    unsigned int left_tx_pkt_len = 0; /* remain tx packet length */
    int ret = 0;
    int err_flag = 0;
    char rst_buf[CBP_EXCEPT_STACK_LEN] = {0};
    modem_bus_t* p_cur_bus = NULL;
    unsigned int no_ack_times = 0;

    if ((NULL == pt_pkt_buf) || (0 == t_len))
    {
        hwlog_err("%s %d: NULL pointer! pt_pkt_buf=0x%lx, len=%d\n", \
                  __func__, __LINE__, (unsigned long)pt_pkt_buf, t_len);
        return -1;
    }

    /* first judge if the modem is power off */
    if (0 == get_modem_bus_state())
    {
        hwlog_err("%s %d: VIA modem reset happened\n", __func__, __LINE__);
        return -2;
    }

    if (NULL == g_ext_modem.pm_cur_bus)
    {
        hwlog_err("%s %d: current ext modem bus is NULL\n", __func__, __LINE__);
        return -3;
    }

    p_cur_bus = g_ext_modem.pm_cur_bus;

    /* wait until hardware flow control disabled */
    ret_wait_hw_fc = wait_apcp_gpio_state(GPIO_APCP_FLOW_CTRL);

    if (ret_wait_hw_fc)
    {
        if (-1 == ret_wait_hw_fc)
        {
            ret = -2;
            err_flag = 1; //notify CBP to produce ramdump
            hwlog_err("%s %d: wait hardware flow ctrl disable timeout. current packet is:\n", __func__, __LINE__);
            apcp_current_subpacket_printk(p_tx_subpkt_buf, left_tx_pkt_len, 1, 0);
        }
        else if (-2 == ret_wait_hw_fc)
        {
            ret = -3;
            hwlog_err("%s %d: ext modem reset has happened, just return.\n", __func__, __LINE__);
        }

        goto down_out;
    }

    /* split the long packet to small subpackets according to actual bus fifo size */
    /* point to the start address of tx packet buf */
    p_tx_subpkt_buf = pt_pkt_buf;
    left_tx_pkt_len = t_len;
    hwlog_debug("%s %d: write subpacket addr=0x%lx, packet length is %d.\n", \
                __func__, __LINE__, (unsigned long)p_tx_subpkt_buf, left_tx_pkt_len);

    while (left_tx_pkt_len)
    {
        /* compare the left data length in buf and actual bus fifo size */
        if (left_tx_pkt_len > p_cur_bus->m_fifo_size)
        {
            cur_write_len = p_cur_bus->m_fifo_size;
        }
        else
        {
            cur_write_len = left_tx_pkt_len;
        }

        /* wakeup cp just before write */
        ret = ap_tx_wait_cp_ready();

        if (ret)
        {
            if (-2 == ret) /* wait cp ready timeout */
            {
                modem_dsm_client_notify("can NOT wake up CBP ret=", ret, DSM_SPI_AUTO_READY_ERROR_NO);
            }
            hwlog_err("%s %d: can NOT wake up CBP ret=%d! current packet is:\n", __func__, __LINE__, ret);
            apcp_current_subpacket_printk(p_tx_subpkt_buf, left_tx_pkt_len, 1, 0);
            ret = -1;
            goto down_out;
        }

        if (0 == get_modem_bus_state())
        {
            hwlog_err("%s %d: VIA modem reset happened\n", __func__, __LINE__);
            ret = -4;
            goto down_out;
        }

        /* make sure ap bus SPI/SDIO controller had resumed before write */
        ret = wait_ap_bus_resumed();

        if (ret)
        {
            hwlog_err("%s %d:wait Host controller to resume FAILED!", __func__, __LINE__);
            ret = -5;
            goto down_out;
        }

        if (p_cur_bus->pfm_bus_lock)
        {
            p_cur_bus->pfm_bus_lock(1);
        }

        if (0 == get_modem_bus_state())
        {
            hwlog_err("%s %d: VIA modem reset happened\n", __func__, __LINE__);
            if (p_cur_bus->pfm_bus_lock)
            {
                p_cur_bus->pfm_bus_lock(0);
            }
            ret = -4;
            goto down_out;
        }

        /* first disable bus irq */
        if (p_cur_bus->pfm_bus_irq_enable)
        {
            p_cur_bus->pfm_bus_irq_enable(0);
        }

        do
        {
            /* reset DATA ACK state to inactive just before bus write */
            reset_apcp_gpio_state(GPIO_APCP_DATA_ACK);

            /* do actual bus write current subpacket */
            ret = p_cur_bus->pfm_bus_write(p_tx_subpkt_buf, cur_write_len);

            ret = wait_apcp_gpio_state(GPIO_APCP_DATA_ACK);

            if (0 == ret) /* return success */
            {
                break;
            }
            else if (-1 == ret) /* wait data ack timeout */
            {
                no_ack_times++;
                hwlog_err("%s %d: via bus write wait data ack failed times=%d, ret=%d\n", __func__, __LINE__, no_ack_times, ret);
                apcp_current_subpacket_printk(p_tx_subpkt_buf, cur_write_len, 1, 0);
                modem_dsm_client_notify("via bus write wait data ack fail ret=", ret, DSM_APCP_SDIO_WRITE_ACK_ERROR_NO);
            }
            else
            {
                hwlog_err("%s %d: wait data ack fail, ret=%d\n", __func__, __LINE__, ret);
                ret = -6;
                break;
            }

            /* judge if no ack times reach MAX retry times */
            if (no_ack_times >= MAX_WAIT_DATA_ACK_RETRY)
            {
                err_flag = 1;
                hwlog_err("%s %d: had retry write reach MAX retry times\n", __func__, __LINE__);
                ret = -7;
                break;
            }
        }
        while (1);

        /* enable bus irq after write */
        if (p_cur_bus->pfm_bus_irq_enable)
        {
            p_cur_bus->pfm_bus_irq_enable(1);
        }

        if (p_cur_bus->pfm_bus_lock)
        {
            p_cur_bus->pfm_bus_lock(0);
        }

        if (ret)
        {
            hwlog_err("%s %d: write to ext modem FAILed ret=%d\n", __func__, __LINE__, ret);
            apcp_current_subpacket_printk(p_tx_subpkt_buf, cur_write_len, 1, 0);
            goto down_out;
        }

        /* recalculate remain data addr and length in txrx common buf */
        p_tx_subpkt_buf += cur_write_len;
        /* refresh left tx packet length */
        left_tx_pkt_len -= cur_write_len;
    }

down_out:

    if (err_flag != 0)
    {
        snprintf(rst_buf, CBP_EXCEPT_STACK_LEN - 1, "%s %d:write error notify VIA CBP to produce ramdump.\n", __func__, __LINE__);
        hwlog_err("%s %d: write error notify VIA CBP to produce ramdump.\n", __func__, __LINE__);
        modem_err_indication_usr_form_module(rst_buf, CBP_EXCEPT_REASON_SPI, CBP_EXCE_MID_SPI_WRITE_TIMEOUT);
    }

    /* return result of write */
    return ret;
}

/**
 * modem_read - read data from modem
 *
 * Returns:
 *   none
 */
int modem_read(char* pt_buf, int t_include_head, int t_head_size, int t_len)
{
    unsigned char* p_cur_buf = NULL; /* point to current available space for write in txrx common buf */
    int ret = 0;
    int status = 0;
    int err_flag = 0;
    unsigned int left_rx_pkt_len = 0; /* remain rx packet length */
    unsigned int cur_read_len = 0;
    char rst_buf[CBP_EXCEPT_STACK_LEN] = {0};
    modem_bus_t* p_cur_bus = NULL;
    unsigned int no_ack_times = 0;

    if ((NULL == pt_buf) || (t_len < 0))
    {
        hwlog_err("%s %d input parameter invalid, pt_buf=0x%lx, t_len=%d\n", __func__, __LINE__, (unsigned long)pt_buf, t_len);
        ret = -1;
        goto out;
    }

    /* first judge if the modem is power off */
    if (0 == get_modem_bus_state())
    {
        hwlog_err("%s %d: VIA modem reset happened\n", __func__, __LINE__);
        return -2;
    }

    if (NULL == g_ext_modem.pm_cur_bus)
    {
        hwlog_err("%s %d: current ext modem bus is NULL\n", __func__, __LINE__);
        return -3;
    }

    p_cur_bus = g_ext_modem.pm_cur_bus;

    /* get the read length */
    left_rx_pkt_len = t_len;

    if (t_include_head)   /* read include packet header */
    {
        if (left_rx_pkt_len <= g_ext_modem.pm_cur_bus->m_fifo_size)
        {
            cur_read_len = left_rx_pkt_len;
        }
        else
        {
            cur_read_len = g_ext_modem.pm_cur_bus->m_fifo_size;
        }
    }
    else     /* only read packet payload */
    {
        if (left_rx_pkt_len <= (g_ext_modem.pm_cur_bus->m_fifo_size - t_head_size))
        {
            cur_read_len = left_rx_pkt_len;
        }
        else
        {
            cur_read_len = g_ext_modem.pm_cur_bus->m_fifo_size - t_head_size;
        }
    }

    /* get the current available buffer address */
    p_cur_buf = pt_buf;
    hwlog_debug("%s %d: read subpacket buf addr=0x%lx, current read length is %d.\n", \
                __func__, __LINE__, (unsigned long)p_cur_buf, cur_read_len);

    do
    {
        /* reset DATA ACK state to inactvie just before bus read or write */
        reset_apcp_gpio_state(GPIO_APCP_DATA_ACK);

        /* read left packet payload */
        do
        {
            hwlog_debug("%s %d: read subpacket buf addr=0x%lx, current read length is %d.\n", \
                        __func__, __LINE__, (unsigned long)p_cur_buf, cur_read_len);
            /* do actual read */
            //if (t_len > t_head_size)
            {
                status = g_ext_modem.pm_cur_bus->pfm_bus_read(p_cur_buf, cur_read_len);
            }

            if (status)
            {
                hwlog_err("%s %d: sync error has reached MAX FAILed times.\n", __func__, __LINE__);
                apcp_current_subpacket_printk(p_cur_buf, cur_read_len, 1, 0);
                ret = -4;
                goto out;
            }

            /* refresh remain packet data length */
            left_rx_pkt_len -= cur_read_len;

            /* calculate how long to read for current bus read */
            cur_read_len = (left_rx_pkt_len > g_ext_modem.pm_cur_bus->m_fifo_size) ? g_ext_modem.pm_cur_bus->m_fifo_size : left_rx_pkt_len;
            /* get the current available buffer address */
            p_cur_buf += cur_read_len;
        }
        while (left_rx_pkt_len);

        ret = wait_apcp_gpio_state(GPIO_APCP_DATA_ACK);

        if (0 == ret) /* return success */
        {
            break;
        }
        else if (-1 == ret) /* wait data ack timeout */
        {
            /* increase no ack times */
            no_ack_times++;
            hwlog_err("%s %d: ext modem read wait data ack failed times=%d, ret=%d\n", __func__, __LINE__, no_ack_times, ret);
            apcp_current_subpacket_printk(pt_buf, t_len, 0, 0);
            modem_dsm_client_notify("ext modem read wait data ack fail ret=", ret, DSM_SPI_READ_ACK_ERROR_NO);
        }
        else
        {
            hwlog_err("%s %d: wait data ack fail, ret=%d\n", __func__, __LINE__, ret);
            ret = -5;
            break;
        }

        /* judge if no ack times reach MAX retry times */
        if (no_ack_times >= MAX_WAIT_DATA_ACK_RETRY)
        {
            err_flag = 1;
            hwlog_err("%s %d: had retry read reach MAX retry times\n", __func__, __LINE__);
            ret = -6;
            break;
        }
    }
    while (1);

out:

    if (err_flag != 0)
    {
        snprintf(rst_buf, CBP_EXCEPT_STACK_LEN - 1, "%s %d:read error notify VIA CBP to produce ramdump.\n", __func__, __LINE__);
        hwlog_err("%s %d: read error notify VIA CBP to produce ramdump.\n", __func__, __LINE__);
        modem_err_indication_usr_form_module(rst_buf, CBP_EXCEPT_REASON_SPI, CBP_EXCE_MID_SPI_READ_TIMEOUT);
    }

    return ret;
}
EXPORT_SYMBOL(modem_read);

static void modem_reset_work(struct work_struct* pt_work)
{
    int i = 0;
    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);

    /* wait ap host controller to resume */
    msleep(AP_HOST_CONTROLLER_RESUME_TIME);

    for (i = 0; i < MODEM_BUS_MAX_NUM; i++)
    {
        if (g_ext_modem.m_arr_reset_handle[i])
        {
            hwlog_info("%s %d: current bus mdm_reset_handle not NULL.\n", __func__, __LINE__);
            g_ext_modem.m_arr_reset_handle[i]();
        }
        else
        {
            hwlog_info("%s %d: Warning: current bus mdm_reset_handle is NULL.\n", __func__, __LINE__);
        }
    }

    modem_channels_reset();

    four_wire_reset();
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
}

/**
 * modem_reset_handle - handle modem reset
 *
 * Returns:
 *   none
 */
void modem_reset_handle(void)
{
    queue_work(g_ext_modem.pm_reset_wq, &g_ext_modem.m_reset_work);
}
EXPORT_SYMBOL(modem_reset_handle);

int ext_modem_init(void)
{
    ext_modem_t* p_ext_modem = &g_ext_modem;
    int ret = 0;

    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    /* initialize semaphore used as bus lock */
    sema_init(&p_ext_modem->m_bus_sema, 1);

    p_ext_modem->m_mdm_bus_ready = 0;

    /* create a workqueue thread for modem reset */
    p_ext_modem->pm_reset_wq = create_singlethread_workqueue("mdm_rst_wq");

    if (NULL == p_ext_modem->pm_reset_wq)
    {
        hwlog_err("%s %d: error create modem reset workqueue\n", __func__, __LINE__);
        return -1;
    }

    INIT_WORK(&p_ext_modem->m_reset_work, modem_reset_work);

    /* initialize waitqueue for ap host resume status */
    init_waitqueue_head(&p_ext_modem->m_ap_resume_waitq);
    atomic_set(&p_ext_modem->m_ap_resume_atom, AP_BUS_RESUMED);
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    /* initialize complete, return success */
    return ret;
}
EXPORT_SYMBOL(ext_modem_init);

void ext_modem_exit(void)
{
    ext_modem_t* p_ext_modem = &g_ext_modem;

    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    p_ext_modem->m_mdm_bus_ready = 0;

    cancel_work_sync(&p_ext_modem->m_reset_work);
    if (p_ext_modem->pm_reset_wq)
    {
        destroy_workqueue(p_ext_modem->pm_reset_wq);
    }

    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
}
EXPORT_SYMBOL(ext_modem_exit);

