/*
 * apcp_test.c
 *
 */

#include <linux/delay.h>

#include "viatel.h"
#include "apcp_test.h"


static apcp_traffic_mgmt_t g_apcp_test = {0};

static struct dsm_client* gp_modem_dsm_client = NULL;

static struct  dsm_dev g_modem_dsm_dev =
{
    .name = "dsm_modem_spi",
    .fops = NULL,
    .buff_size = 1024,
};

void modem_dsm_client_notify(const char* pt_content, int t_ret, int t_err_num)
{
    if (gp_modem_dsm_client && !dsm_client_ocuppy(gp_modem_dsm_client))
    {
        if (pt_content)
        {
            dsm_client_record(gp_modem_dsm_client, "%s %d\n", pt_content, t_ret);
        }

        dsm_client_notify(gp_modem_dsm_client, t_err_num);
        hwlog_info("modem dsm_client_notify success\n");
    }
    else
    {
        hwlog_err("modem dsm_client_notify failed\n");
    }
}
EXPORT_SYMBOL(modem_dsm_client_notify);

void apcp_current_subpacket_printk(char* pt_buf, unsigned int t_count,
                                   unsigned char t_is_tx, unsigned int t_chan_num)
{
    unsigned int count = t_count;
    const unsigned char* print_buf = (const unsigned char*)pt_buf;
    unsigned int apcp_channel = t_chan_num;
    int i = 0;

    g_apcp_test.m_print_buff_pos = 0;
    memset(g_apcp_test.m_print_buff, 0, sizeof(g_apcp_test.m_print_buff));

    if (t_is_tx == 1)
    {
        g_apcp_test.m_print_buff_pos += snprintf(&g_apcp_test.m_print_buff[g_apcp_test.m_print_buff_pos], (APCP_PRINT_BUFFER_SIZE - g_apcp_test.m_print_buff_pos), \
                                        "write %d to ", count);
    }
    else
    {
        g_apcp_test.m_print_buff_pos += snprintf(&g_apcp_test.m_print_buff[g_apcp_test.m_print_buff_pos], (APCP_PRINT_BUFFER_SIZE - g_apcp_test.m_print_buff_pos), \
                                        "read %d from ", count);
    }

    g_apcp_test.m_print_buff_pos += snprintf(&g_apcp_test.m_print_buff[g_apcp_test.m_print_buff_pos], (APCP_PRINT_BUFFER_SIZE - g_apcp_test.m_print_buff_pos), \
                                    "channel %d >>", apcp_channel);

    if (count > MAX_ALLOWED_PRINT_SIZE)
    {
        count = MAX_ALLOWED_PRINT_SIZE;
    }

    for (i = 0; i < count; i++)
    {
        if ((MODEM_CHANNEL_AT_PC_NUM == apcp_channel) \
            || (MODEM_CHANNEL_AT_FT_NUM == apcp_channel) \
            || (MODEM_CHANNEL_AT_UICC_NUM == apcp_channel) \
            || (MODEM_CHANNEL_AT_RILD1_NUM == apcp_channel) \
            || (MODEM_CHANNEL_AT_RILD2_NUM == apcp_channel) \
            || (MODEM_CHANNEL_AT_LOGTOOL_NUM == apcp_channel))
        {
            if ( ('\n' == *(print_buf + i)) || ('\r' == *(print_buf + i)))
            {
                g_apcp_test.m_print_buff_pos += snprintf(&g_apcp_test.m_print_buff[g_apcp_test.m_print_buff_pos], (APCP_PRINT_BUFFER_SIZE - g_apcp_test.m_print_buff_pos), \
                                                "-");
            }
            else
            {
                g_apcp_test.m_print_buff_pos += snprintf(&g_apcp_test.m_print_buff[g_apcp_test.m_print_buff_pos], (APCP_PRINT_BUFFER_SIZE - g_apcp_test.m_print_buff_pos), \
                                                "%c", *(print_buf + i));
            }
        }
        else
        {
            if (i < count - 1)
            {
                g_apcp_test.m_print_buff_pos += snprintf(&g_apcp_test.m_print_buff[g_apcp_test.m_print_buff_pos], (APCP_PRINT_BUFFER_SIZE - g_apcp_test.m_print_buff_pos), \
                                                "%x-", *(print_buf + i));
            }
            else
            {
                g_apcp_test.m_print_buff_pos += snprintf(&g_apcp_test.m_print_buff[g_apcp_test.m_print_buff_pos], (APCP_PRINT_BUFFER_SIZE - g_apcp_test.m_print_buff_pos), \
                                                "%x", *(print_buf + i));
            }
        }
    }

    if (t_count > count)
    {
        g_apcp_test.m_print_buff_pos += snprintf(&g_apcp_test.m_print_buff[g_apcp_test.m_print_buff_pos], (APCP_PRINT_BUFFER_SIZE - g_apcp_test.m_print_buff_pos), \
                                        "...skip %d bytes...", (t_count - count));
    }

    g_apcp_test.m_print_buff_pos += snprintf(&g_apcp_test.m_print_buff[g_apcp_test.m_print_buff_pos], (APCP_PRINT_BUFFER_SIZE - g_apcp_test.m_print_buff_pos), \
                                    "rx irq=%d,cpwkap=%d", g_apcp_test.m_rx_irq_cnt, g_apcp_test.m_cpwkap_cnt);

    /* tx and rx count */
    g_apcp_test.m_print_buff_pos += snprintf(&g_apcp_test.m_print_buff[g_apcp_test.m_print_buff_pos], (APCP_PRINT_BUFFER_SIZE - g_apcp_test.m_print_buff_pos), \
                                    "; tx/rx of chan 0-15:[");

    for (i = 0; i < (MODEM_CHANNEL_NR - 1); i++)
    {
        g_apcp_test.m_print_buff_pos += snprintf(&g_apcp_test.m_print_buff[g_apcp_test.m_print_buff_pos], (APCP_PRINT_BUFFER_SIZE - g_apcp_test.m_print_buff_pos), \
                                        "%x/%x,", g_apcp_test.m_txpkts_on_chans[i], g_apcp_test.m_rxpkts_on_chans[i]);
    }

    g_apcp_test.m_print_buff_pos += snprintf(&g_apcp_test.m_print_buff[g_apcp_test.m_print_buff_pos], (APCP_PRINT_BUFFER_SIZE - g_apcp_test.m_print_buff_pos), \
                                    "%x/%x]\n", g_apcp_test.m_txpkts_on_chans[MODEM_CHANNEL_NR - 1], g_apcp_test.m_rxpkts_on_chans[MODEM_CHANNEL_NR - 1]);

    g_apcp_test.m_print_buff_pos += snprintf(&g_apcp_test.m_print_buff[g_apcp_test.m_print_buff_pos], (APCP_PRINT_BUFFER_SIZE - g_apcp_test.m_print_buff_pos), \
                                    "%x/%x\n", g_apcp_test.m_txpkts_on_chans[MODEM_CHANNEL_FLASHLESS_NUM], g_apcp_test.m_rxpkts_on_chans[MODEM_CHANNEL_FLASHLESS_NUM]);

    hwlog_info("%s", g_apcp_test.m_print_buff);
}
EXPORT_SYMBOL(apcp_current_subpacket_printk);

void apcp_txrx_buffer_count(unsigned int t_chan_num, unsigned int t_count, unsigned char t_is_tx)
{
    if (t_is_tx)
    {
        g_apcp_test.m_txpkts_on_chans[t_chan_num]++;
        g_apcp_test.m_txbytes_on_chans[t_chan_num] += t_count;
    }
    else
    {
        g_apcp_test.m_rxpkts_on_chans[t_chan_num]++;
        g_apcp_test.m_rxbytes_on_chans[t_chan_num] += t_count;
    }

}
EXPORT_SYMBOL(apcp_txrx_buffer_count);

void reset_txrx_buffer_count(void)
{
    int i = 0;

    for (i = 0; i < (MODEM_CHANNEL_NR - 1); i++)
    {
        g_apcp_test.m_txpkts_on_chans[i] = 0;
        g_apcp_test.m_txbytes_on_chans[i] = 0;
        g_apcp_test.m_rxpkts_on_chans[i] = 0;
        g_apcp_test.m_rxbytes_on_chans[i] = 0;
    }

    g_apcp_test.m_tx_cnt = 0;
    g_apcp_test.m_rx_cnt = 0;

    g_apcp_test.m_print_buff_pos = 0;
    memset(g_apcp_test.m_print_buff, 0, sizeof(g_apcp_test.m_print_buff));
}
EXPORT_SYMBOL(reset_txrx_buffer_count);

void apcp_rx_irq_count(void)
{
    g_apcp_test.m_rx_irq_cnt++;
}
EXPORT_SYMBOL(apcp_rx_irq_count);

void apcp_cpwkap_count(void)
{
    g_apcp_test.m_cpwkap_cnt++;
}
EXPORT_SYMBOL(apcp_cpwkap_count);

void apcp_test_init(void)
{
    gp_modem_dsm_client = dsm_register_client(&g_modem_dsm_dev);

    if (NULL == gp_modem_dsm_client)
    {
        hwlog_err("%s %d: dsm_register_client register failed\n", __func__, __LINE__);
    }
}
EXPORT_SYMBOL(apcp_test_init);

