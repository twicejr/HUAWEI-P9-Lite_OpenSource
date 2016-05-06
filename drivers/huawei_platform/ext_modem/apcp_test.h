/*
 * apcp_test.h
 *
 */
#ifndef APCP_TEST_H
#define APCP_TEST_H

#include <dsm/dsm_pub.h>

#include "modem_channels.h"


#define APCP_PRINT_BUFFER_SIZE     1024
#define MAX_ALLOWED_PRINT_SIZE    16 //for mask the last several telephone numbers
#define PACKET_DUMP_SIZE            32

/* apcp packet count and print */
typedef struct apcp_traffic_mgmt
{
    unsigned int m_tx_cnt;
    unsigned int m_rx_cnt;
    unsigned int m_is_current_tx; // 1 is tx, 0 is rx
    unsigned int m_is_last_tx; // 1 is tx, 0 is rx
    unsigned char m_tx_cur_pktdump[PACKET_DUMP_SIZE];
    unsigned char m_tx_last_pktdump[PACKET_DUMP_SIZE];
    unsigned char m_rx_cur_pktdump[PACKET_DUMP_SIZE];
    unsigned char m_rx_last_pktdump[PACKET_DUMP_SIZE];
    unsigned char m_print_buff[APCP_PRINT_BUFFER_SIZE];
    unsigned int m_print_buff_pos;

    unsigned int m_txpkts_on_chans[MODEM_CHANNEL_NR]; //channel num = tty num + 1
    unsigned int m_txbytes_on_chans[MODEM_CHANNEL_NR];
    unsigned int m_rxpkts_on_chans[MODEM_CHANNEL_NR];
    unsigned int m_rxbytes_on_chans[MODEM_CHANNEL_NR];
    unsigned int m_print_next_packet; /* only print next one packet on AP resume */
    unsigned int m_read_timeout_cnt;
    unsigned int m_write_timeout_cnt;
    unsigned int m_rsp80_timeout_cnt;

    unsigned int m_rx_irq_cnt;   /* record bus rx irq count */
    unsigned int m_cpwkap_cnt; /* record cp wake ap count */
} apcp_traffic_mgmt_t;

void apcp_current_subpacket_printk(char* pt_buf, unsigned int t_count,
        unsigned char t_is_tx, unsigned int t_chan_num);
void apcp_txrx_buffer_count(unsigned int t_chan_num, unsigned int t_count, unsigned char t_is_tx);
void reset_txrx_buffer_count(void);
void apcp_rx_irq_count(void);
void apcp_cpwkap_count(void);
void apcp_test_init(void);
void modem_dsm_client_notify(const char* pt_content, int t_ret, int t_err_num);

#endif
