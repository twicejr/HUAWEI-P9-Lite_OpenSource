/*
 * modem_channels.c
 *
 */

#include <linux/module.h>
#include <linux/mod_devicetable.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/gpio.h>
#include <linux/wait.h>
#include <linux/kthread.h>
#include <linux/wakelock.h>

#include "viatel.h"
#include "modem_ttys.h"
#include "rnic_adapter.h"
#include "modem_channels.h"
#include "apcp_test.h"
#include "modem_packet.h" /* had use max channel definition in modem_channels.h, so must after it */
#include "ext_modem.h"
#include "power.h"

/* max wait times for software flow control disable of current virtual apcp port */
#define MAX_WAIT_SW_FLOW_CTRL_TIMES    150
#define WAIT_SW_FLOW_CTRL_TIMEOUT       2000


/* global modem channels instance */
static modem_channels_mgmt_t g_modem_chans = {0};


/**
 * check_software_flow_control - check and wait if need until current channel software flow control disabled
 * @t_chan_num: high-level used channel number
 *
 * Returns:
 *   none
 */
int check_software_flow_control(unsigned int t_chan_num)
{
    unsigned long remain_time;
    modem_channel_t* p_mdm_chan; /* pointer to current used channel */
    int ret = 0; /* return value of wait result */
    unsigned int failed_times = 0;
    char rst_buf[CBP_EXCEPT_STACK_LEN] = {0};

    /* get the channel instance of given channel number */
    p_mdm_chan = g_modem_chans.pm_channels[t_chan_num];

    /* wait software flow control of current channel to disabled */
    do
    {
        remain_time = wait_event_timeout(p_mdm_chan->m_sw_fc_wtq, (SW_FLOW_CTRL_DISABLE == atomic_read(&p_mdm_chan->m_sw_fc_stat) \
                                         || (0 == get_modem_bus_state())), msecs_to_jiffies(WAIT_SW_FLOW_CTRL_TIMEOUT));

        if (0 == get_modem_bus_state())
        {
            hwlog_err("%s %d: channel %d wait software contrl disable but VIA CBP reset happened!\n", __func__, __LINE__, p_mdm_chan->m_chan_num);
            ret = -1;
            break;
        }
        else if (0 == remain_time)
        {
            hwlog_err("%s %d: channel %d wait CBP software flow control disable timeout in 2s.\n", __func__, __LINE__, p_mdm_chan->m_chan_num);
            failed_times++;

            if (failed_times >= MAX_WAIT_SW_FLOW_CTRL_TIMES)
            {
                snprintf(rst_buf, CBP_EXCEPT_STACK_LEN - 1, "%s %d: fail to wait channel %d software flow control disable, notify VIA to produce ramdump\n", \
                                __func__, __LINE__, p_mdm_chan->m_chan_num);
                hwlog_err("%s %d: fail to wait channel %d software flow control disable, notify VIA to produce ramdump\n", __func__, __LINE__, p_mdm_chan->m_chan_num);
                modem_err_indication_usr_form_module(rst_buf, CBP_EXCEPT_REASON_SPI, CBP_EXCE_MID_SPI_SFLOW_TIMEOUT);
                ret = -2;
                break;
            }
        }
    }
    while (0 == remain_time);

    return ret;
}
EXPORT_SYMBOL(check_software_flow_control);

unsigned int get_channel_kfifo_data_length(unsigned int t_chan_num)
{
    modem_channel_t* p_mdm_chan = NULL; /* pointer to current used channel */
    unsigned int fifo_data_len = 0;
    unsigned long flags = 0;

    /* get the channel instance of given channel number */
    p_mdm_chan = g_modem_chans.pm_channels[t_chan_num];

    spin_lock_irqsave(&p_mdm_chan->m_write_lock, flags);
    fifo_data_len = kfifo_len(&p_mdm_chan->m_transmit_fifo);
    spin_unlock_irqrestore(&p_mdm_chan->m_write_lock, flags);

    return fifo_data_len;
}
EXPORT_SYMBOL(get_channel_kfifo_data_length);

void reset_channel_kfifo(unsigned int t_chan_num)
{
    modem_channel_t* p_mdm_chan = NULL;
    unsigned long flags = 0;

    p_mdm_chan = g_modem_chans.pm_channels[t_chan_num];

    spin_lock_irqsave(&p_mdm_chan->m_write_lock, flags);
    kfifo_reset(&p_mdm_chan->m_transmit_fifo);
    spin_unlock_irqrestore(&p_mdm_chan->m_write_lock, flags);
}
EXPORT_SYMBOL(reset_channel_kfifo);

/**
 * modem_channel_write - write high-level user data with given channel number
 * @t_chan_num: high-level used channel number
 * @pt_payload_buf: high-level data buffer
 * @t_count: high-level user data length, exclude packet header size
 *
 * Returns:
 *   0 - success, write user data success
 *   minus - error occured when write user data
 */
static int modem_channel_write(unsigned int t_chan_num, const unsigned char* pt_payload_buf, int t_count)
{
    int ret = 0;

    /* print tx at cmd packet */
    if ((MODEM_CHANNEL_AT_PC_NUM == t_chan_num) \
        || (MODEM_CHANNEL_AT_FT_NUM == t_chan_num) \
        || (MODEM_CHANNEL_RILD_CTRL_NUM == t_chan_num) \
        || (MODEM_CHANNEL_AT_UICC_NUM == t_chan_num) \
        || (MODEM_CHANNEL_AT_RILD1_NUM == t_chan_num) \
        || (MODEM_CHANNEL_AT_RILD2_NUM == t_chan_num) \
        || (MODEM_CHANNEL_AT_LOGTOOL_NUM == t_chan_num)
       )
    {
        apcp_current_subpacket_printk((char*)pt_payload_buf, t_count, 1, t_chan_num);
    }

    ret = kfifo_in_locked(&g_modem_chans.pm_channels[t_chan_num]->m_transmit_fifo, pt_payload_buf, t_count, \
                          &g_modem_chans.pm_channels[t_chan_num]->m_write_lock);

    if (!ret)
    {
        hwlog_info("%s %d channel %d kfifo full\n", __func__, __LINE__, t_chan_num);
    }

    /* queue work for write */
    queue_work(g_modem_chans.pm_channels[t_chan_num]->pm_write_wq, &g_modem_chans.pm_channels[t_chan_num]->m_write_work);
    return ret;
}

static void modem_channel_write_work(struct work_struct* work)
{
    int ret = 0; /* return value of channel write */
    modem_channel_t* p_mdm_chan; /* pointer to current used channel */
    unsigned int t_chan_num = 0;
    int cur_data_len = 0;
    unsigned int count = 0;
    unsigned long flags = 0;
    unsigned int fifo_size;

    p_mdm_chan = container_of(work, modem_channel_t, m_write_work);
    t_chan_num = p_mdm_chan->m_chan_num;

    if (down_interruptible(&p_mdm_chan->m_write_sem))
    {
        hwlog_err("%s %d down_interruptible failed.\n", __func__, __LINE__);
        ret =  -8;
        goto err_down_chan_sem;
    }

    spin_lock_irqsave(&p_mdm_chan->m_write_lock, flags);
    count = kfifo_len(&p_mdm_chan->m_transmit_fifo);
    spin_unlock_irqrestore(&p_mdm_chan->m_write_lock, flags);

    //for AT command problem of /r;
    if (count == 0)
    {
        hwlog_info("%s %d: channel %d (count==0)\n", __func__, __LINE__, t_chan_num);
        ret = -7;
        goto err_out;
    }

    cur_data_len = count;
    memset(p_mdm_chan->pm_trans_buffer, 0, FIFO_SIZE);
    fifo_size = kfifo_out_locked(&p_mdm_chan->m_transmit_fifo, p_mdm_chan->pm_trans_buffer, count, &p_mdm_chan->m_write_lock);

    if (cur_data_len != fifo_size)
    {
        hwlog_info(  "%s %d: channel %d todo !=  kfifo lock out size.\n", __func__, __LINE__, p_mdm_chan->m_chan_num);
        cur_data_len = fifo_size;
    }

    /* call modem_write to write the packet payload data */
    ret = modem_write_packets(p_mdm_chan->pm_trans_buffer, cur_data_len, t_chan_num);

    if (ret)
    {
        hwlog_err("%s %d: call modem_write return ERROR!\n", __func__, __LINE__);
        ret = -3;
        goto err_out;
    }

    /* again check channel kfifo just after write */
    spin_lock_irqsave(&p_mdm_chan->m_write_lock, flags);
    count = kfifo_len(&p_mdm_chan->m_transmit_fifo);
    spin_unlock_irqrestore(&p_mdm_chan->m_write_lock, flags);

    /* judge if wake up tty for next write */
    if ((count < MODEM_TTY_WAKEUP_CHARS) && (t_chan_num > MODEM_CHANNEL_CONTROL_NUM))
    {
        modem_tty_wakeup(t_chan_num - 1);
    }

err_out:
    up(&p_mdm_chan->m_write_sem);
err_down_chan_sem:

    if (ret)
    {
        hwlog_debug("%s %d: channel %d Exit ret=%d.\n", __func__, __LINE__, t_chan_num, ret);
    }

    return;
}

/**
 * modem_rnic_write - used by rnic driver to write ip packet data
 * @pt_rnic_buf: rnic buffer address of ip packet data
 * @t_count: length of ip packet data
 *
 * Returns:
 *   0 - success, write user data success
 *   minus - error occured when write user data
 */
int modem_rnic_write(unsigned char* pt_rnic_buf, int t_count)
{
    int ret = 0; /* return value of channel write */
    modem_channel_t* p_mdm_chan; /* pointer to current used channel */
    unsigned int t_chan_num = MODEM_CHANNEL_RNIC_NUM;

    hwlog_debug("RNIC__ %s: enter  t_chan_num=15\n", __func__);

    p_mdm_chan = g_modem_chans.pm_channels[t_chan_num];

    if (down_interruptible(&p_mdm_chan->m_write_sem))
    {
        hwlog_err("%s %d down_interruptible failed.\n", __func__, __LINE__);
        ret =  -1;
        goto err_down_chan_sem;
    }

    //for AT command problem of /r;
    if (t_count == 0)
    {
        hwlog_info("%s %d: channel %d (count==0)\n", __func__, __LINE__, t_chan_num);
        ret = -2;
        goto err_out;
    }

    ret = modem_write_rnic_packets(pt_rnic_buf, t_count, MODEM_CHANNEL_RNIC_NUM);

    if (ret)
    {
        hwlog_err("%s %d: call modem_write return ERROR!\n", __func__, __LINE__);
        ret = -3;
        goto err_out;
    }

err_out:
    up(&p_mdm_chan->m_write_sem);
err_down_chan_sem:

    if (ret)
    {
        hwlog_err("%s %d: channel %d Exit ret=%d.\n", __func__, __LINE__, t_chan_num, ret);
    }

    return ret;
}
EXPORT_SYMBOL(modem_rnic_write);

/**
 * modem_tty_write_to_channel - used by modem tty driver to write tty buffer data
 * @t_tty_index: tty index of current modem tty device
 * @pt_tty_buf: buffer address of tty buffer data
 * @t_count: length of tty buffer data
 *
 * Returns:
 *   length of successfully write data in bytes
 */
int modem_tty_write_to_channel(unsigned int t_tty_index, const unsigned char* pt_tty_buf, int t_count)
{
    int ret = -1;
    int wr_count = 0;
    /* on tty channel to write current tty buffer data */
    /* channel num = tty num + 1 */
    ret = modem_channel_write((t_tty_index + 1), pt_tty_buf, t_count);
    /* judge if write to channel success */
    /* avoid dead loop write */
    //if (0 == ret) {
    wr_count = t_count;
    //}

    /* return actually written data length in bytes */
    return wr_count;
}
EXPORT_SYMBOL(modem_tty_write_to_channel);

/**
 * ctrl_msg_analyze - analyze a control channel message
 * @t_msg: control message ID
 * @t_chan_num: the number of channel which to be control
 * @t_opt: optional control parameter
 * @pt_ctrl_chan_msg: out pointer to complete constructed control message
 *
 * Returns:
 *   none
 */
static void ctrl_msg_analyze(char* pt_buf)
{
    modem_channel_t* p_mdm_chan;
    ctrl_channel_msg_t ctrl_chan_msg;
    unsigned int t_msg_id = 0;

    /* first copy the control message */
    if (pt_buf)
    {
        memcpy(&ctrl_chan_msg, pt_buf, sizeof(ctrl_channel_msg_t));

        t_msg_id = (ctrl_chan_msg.m_id_hi << 8) + ctrl_chan_msg.m_id_low;

        switch (t_msg_id)
        {
            case FLOW_CONTROL_MSG_ID:
                p_mdm_chan = g_modem_chans.pm_channels[ctrl_chan_msg.m_chan_num];

                if (ctrl_chan_msg.m_chan_num >= MODEM_CHANNEL_CONTROL_NUM && ctrl_chan_msg.m_chan_num < MODEM_CHANNEL_NR)
                {
                    if (SW_FLOW_CTRL_ENABLE == ctrl_chan_msg.m_option)
                    {
                        hwlog_info("%s %d: channel %d soft flow ctrl enable!\n", __func__, __LINE__, p_mdm_chan->m_chan_num);
                        atomic_set(&p_mdm_chan->m_sw_fc_stat, SW_FLOW_CTRL_ENABLE);
                    }
                    else if (SW_FLOW_CTRL_DISABLE == ctrl_chan_msg.m_option)
                    {
                        hwlog_info("%s %d: channel %d soft flow ctrl disable!\n", __func__, __LINE__, p_mdm_chan->m_chan_num);
                        atomic_set(&p_mdm_chan->m_sw_fc_stat, SW_FLOW_CTRL_DISABLE);
                        wake_up(&p_mdm_chan->m_sw_fc_wtq);
                    }
                }
                else
                {
                    hwlog_err("%s %d: unkown channel num%d!\n", __func__, __LINE__, ctrl_chan_msg.m_chan_num);
                }

                break;

            default:
                hwlog_err("%s %d: unknow control message received, message is %d\n", __func__, __LINE__, t_msg_id);
                break;
        }
    }
}

/**
 * modem_channel_push - push whole packet to modem channels dirver
 * @pt_buf: low-level received packet buffer address of packet payload data
 * @t_count: low-level received packet payload length
 *
 * Returns:
 *   0 - push sucess
 *   minus - error occurred
 */
int modem_channel_push(void* pt_pkt_payload_buf, unsigned int t_chan_num, int t_payload_len, unsigned char tranHi)
{
    unsigned int chan_num = 0; /* channel number */
    unsigned int tty_index = 0; /* tty index convert from channel number */
    unsigned int payload_len = 0; /* packet payload length */

    if (NULL == pt_pkt_payload_buf)
    {
        hwlog_err("%s %d: NULL pointer! pt_pkt_payload_buf=0x%lx\n", \
                  __func__, __LINE__, (unsigned long)pt_pkt_payload_buf);
        return -1;
    }

    /* get channel number */
    chan_num = t_chan_num;
    /* packet payload length */
    payload_len = t_payload_len;
    hwlog_debug("%s %d: channel_num = %d, payload_len = %d! \n", __func__, __LINE__, chan_num, payload_len);
    /* count rx data buffer before push to upper layer */
    apcp_txrx_buffer_count(chan_num, payload_len, 0);

    /* print rx at cmd packet */
    if ((MODEM_CHANNEL_AT_PC_NUM == chan_num) \
        || (MODEM_CHANNEL_AT_FT_NUM == chan_num) \
        || (MODEM_CHANNEL_RILD_CTRL_NUM == chan_num) \
        || (MODEM_CHANNEL_AT_UICC_NUM == chan_num) \
        || (MODEM_CHANNEL_AT_RILD1_NUM == chan_num) \
        || (MODEM_CHANNEL_AT_RILD2_NUM == chan_num) \
        || (MODEM_CHANNEL_AT_LOGTOOL_NUM == chan_num)
       )
    {
        apcp_current_subpacket_printk(pt_pkt_payload_buf, payload_len, 0, chan_num);
    }

    if (chan_num > MODEM_CHANNEL_CONTROL_NUM && chan_num < MODEM_CHANNEL_RNIC_NUM)
    {
        tty_index = chan_num - 1;

        /* push the packet data to tty, exclude both packet header and payload offset */
        modem_tty_push(tty_index, pt_pkt_payload_buf, payload_len);
    }
    else if (chan_num == MODEM_CHANNEL_RNIC_NUM)
    {
        hwlog_debug("%s %d: RNIC data buffered! \n", __func__, __LINE__);
        rnic_read_packet(pt_pkt_payload_buf, payload_len, tranHi);
    }
    else if (chan_num == MODEM_CHANNEL_CONTROL_NUM) /*control message analyze*/
    {
        ctrl_msg_analyze(pt_pkt_payload_buf);
    }
    else
    {
        hwlog_err("%s %d: error chanInfo is %d, go out.\n",
                  __func__, __LINE__, chan_num);
        return -3;
    }

    return 0;
}
EXPORT_SYMBOL_GPL(modem_channel_push);

/**
 * modem_channels_reset - clean all modem channels when modem reset, such as clean all channels software flow control flag
 *
 * Returns:
 *   none
 */
void modem_channels_reset(void)
{
    modem_channel_t* p_mdm_chan;
    int index;

    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);

    for (index = 0; index < MODEM_CHANNEL_NR; index++)
    {
        p_mdm_chan = g_modem_chans.pm_channels[index];
        atomic_set(&p_mdm_chan->m_sw_fc_stat, SW_FLOW_CTRL_DISABLE);
        wake_up(&p_mdm_chan->m_sw_fc_wtq);

        if (p_mdm_chan->pm_write_wq)
        {
            cancel_work_sync(&p_mdm_chan->m_write_work);
        }

        hwlog_info("%s %d: modem channel %d reset.\n", __func__, __LINE__, p_mdm_chan->m_chan_num);
    }

    modem_tty_devs_reset();

    /* reset tx and rx count */
    reset_txrx_buffer_count();
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
}
EXPORT_SYMBOL(modem_channels_reset);

static int each_channel_init(modem_channel_t* pt_chan)
{
    int ret = 0;

    init_waitqueue_head(&pt_chan->m_sw_fc_wtq);
    atomic_set(&pt_chan->m_sw_fc_stat, SW_FLOW_CTRL_DISABLE);

    /* create port's write work queue */
    pt_chan->pm_name = "mdm_wr_wq";
    sprintf(pt_chan->m_arr_work_name, "%s%d", pt_chan->pm_name, pt_chan->m_chan_num);
    pt_chan->pm_write_wq = create_singlethread_workqueue(pt_chan->m_arr_work_name);

    if (pt_chan->pm_write_wq == NULL)
    {
        hwlog_info("%s %d error creat write workqueue \n", __func__, __LINE__);
        ret = -1;
        goto err_create_wq;
    }

    INIT_WORK(&pt_chan->m_write_work, modem_channel_write_work);

    sema_init(&pt_chan->m_write_sem, 1);

    spin_lock_init(&pt_chan->m_write_lock);

    if (kfifo_alloc(&pt_chan->m_transmit_fifo, FIFO_SIZE, GFP_KERNEL))
    {
        hwlog_info("%s %d : Couldn't allocate transmit_fifo\n", __func__, __LINE__);
        ret = -2;
        goto err_kfifo_alloc;
    }

    pt_chan->pm_trans_buffer = kzalloc(FIFO_SIZE, GFP_KERNEL);

    if (!pt_chan->pm_trans_buffer)
    {
        hwlog_err("%s %d: channel %d alloc transfer buffer FAIL!\n", __func__, __LINE__, pt_chan->m_chan_num);
        ret = -3;
        goto err_kzalloc;
    }

    return ret;

err_kzalloc:
    kfifo_free(&pt_chan->m_transmit_fifo);
err_kfifo_alloc:
    cancel_work_sync(&pt_chan->m_write_work);
    destroy_workqueue(pt_chan->pm_write_wq);
err_create_wq:
    return ret;
}

int modem_channels_init(void)
{
    modem_channel_t* p_chan = NULL;
    int ret = 0;
    int index = 0;

    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);

    /* point to start address of all channels */
    for (index = MODEM_CHANNEL_CONTROL_NUM; index < MODEM_CHANNEL_NR; index++)
    {
        p_chan = g_modem_chans.pm_channels[index] = kzalloc(sizeof(modem_channel_t), GFP_KERNEL);

        if (!p_chan)
        {
            hwlog_err("%s %d kzalloc modem_channel %d failed.\n", __func__, __LINE__, index);
            ret = -ENOMEM;
            goto err_kzalloc_out;
        }

        p_chan->m_chan_num = index;

        ret = each_channel_init(p_chan);

        if (ret)
        {
            ret = -2;
            goto err_kzalloc_out;
        }
    }

    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    return ret;
err_kzalloc_out:

    for (; index >= 0; index--)
    {
        if (g_modem_chans.pm_channels[index])
        {
            kfree(g_modem_chans.pm_channels[index]);
            g_modem_chans.pm_channels[index] = NULL;
        }
    }

    return ret;
}
EXPORT_SYMBOL(modem_channels_init);

void modem_channels_exit(void)
{
    unsigned int index = 0;

    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);

    for (index = 0; index < MODEM_CHANNEL_NR; index++)
    {
        kfree(g_modem_chans.pm_channels[index]);
        g_modem_chans.pm_channels[index] = NULL;
    }

    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
}
EXPORT_SYMBOL(modem_channels_exit);

