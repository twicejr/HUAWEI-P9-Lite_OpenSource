/*
 * modem_channels.h
 *
 */

#ifndef MODEM_CHANNELS_H
#define MODEM_CHANNELS_H

#include <linux/init.h>
#include <linux/kfifo.h>

#include "modem_ttys.h"


/* channel num = tty num + 1 */
typedef enum
{
    MODEM_CHANNEL_CONTROL_NUM    = 0,
    MODEM_CHANNEL_RESERVED_1_NUM,
    MODEM_CHANNEL_ETS_NUM        =    (MODEM_TTY_ETS_NUM + 1),
    MODEM_CHANNEL_FLASHLESS_NUM  =    (MODEM_TTY_FLASHLESS_NUM + 1),
    MODEM_CHANNEL_AT_PC_NUM      =    (MODEM_TTY_AT_PC_NUM + 1),
    MODEM_CHANNEL_AT_PCVOICE_NUM =    (MODEM_TTY_AT_PCVOICE_NUM + 1),
    MODEM_CHANNEL_AT_AGPS_NUM    =    (MODEM_TTY_AT_AGPS_NUM + 1),
    MODEM_CHANNEL_AT_FT_NUM      =    (MODEM_TTY_AT_FT_NUM + 1), //ttySPI6 is for ProjectMenu
    MODEM_CHANNEL_RILD_CTRL_NUM  =    (MODEM_TTY_RILD_MMC_NUM + 1), //ttySPI7 transfer rild MMC command which are hex, not ASCI char.
    MODEM_CHANNEL_AT_UICC_NUM    =    (MODEM_TTY_AT_UICC_NUM + 1), //ttySPI8 is for UICC
    MODEM_CHANNEL_AT_RILD1_NUM   =    (MODEM_TTY_AT_RILD1_NUM + 1),
    MODEM_CHANNEL_AT_RILD2_NUM   =    (MODEM_TTY_AT_RILD2_NUM + 1),
    MODEM_CHANNEL_AT_LOGTOOL_NUM =    (MODEM_TTY_AT_LOGTOOL_NUM + 1), //ttySPI11 is for modemlogcat_via
    MODEM_CHANNEL_RESERVED_2_NUM,
    MODEM_CHANNEL_RESERVED_3_NUM,
    MODEM_CHANNEL_RNIC_NUM,    //channel 15 - use by RNIC adapter driver
    MODEM_CHANNEL_NR,
} MODEM_CHANNEL_NUM;

/* software flow control */
typedef enum
{
    SW_FLOW_CTRL_DISABLE = 0,
    SW_FLOW_CTRL_ENABLE
} e_flow_ctrl_state;

/* CBP control message type */
enum cbp_contrl_message_type
{
    CHAN_ONOFF_MSG_ID = 0,
    MDM_STATUS_IND_MSG_ID,
    MDM_STATUS_QUERY_MSG_ID,
    CHAN_SWITCH_REQ_MSG_ID,
    CHAN_STATUS_QUERY_MSG_ID,
    FLOW_CONTROL_MSG_ID,
    CHAN_LOOPBACK_TST_MSG_ID,
    MESSAGE_COUNT,
};

typedef enum
{
    OPT_LOOPBACK_NON  = 0,        //no operation, default 0
    OPT_LOOPBACK_OPEN  = 1,        //open loopback test
    OPT_LOOPBACK_CLOSE  = 2,        //close loopback test
    OPT_LOOPBACK_QUERY = 3,        //query loopback test
    OPT_LOOPBACK_NUM
} IOP_OPT_LOOPBACK;

typedef struct ctrl_channel_msg
{
    unsigned char m_id_hi;
    unsigned char m_id_low;
    unsigned char m_chan_num;
    unsigned char m_option;
} ctrl_channel_msg_t;

/* definition of one channel */
typedef struct modem_channel
{
    unsigned int    m_chan_num;

    wait_queue_head_t m_sw_fc_wtq;    //wait for soft flow control disable
    atomic_t m_sw_fc_stat;

    spinlock_t         m_write_lock;
    struct kfifo       m_transmit_fifo;
    unsigned char* pm_trans_buffer;
    struct semaphore   m_write_sem;

    const char*  pm_name;
    char m_arr_work_name[64];
    struct workqueue_struct* pm_write_wq; /* workqueue thread for bus write */
    struct work_struct m_write_work; /* bus write work */
} modem_channel_t;

/* management all channels */
typedef struct modem_channels_mgmt
{
    struct modem_channel* pm_channels[MODEM_CHANNEL_NR];
} modem_channels_mgmt_t;


void modem_channels_reset(void);
int modem_channel_push(void* pt_pkt_payload_buf, unsigned int t_chan_num, int t_payload_len, unsigned char m_tranHi);
int modem_tty_write_to_channel(unsigned int t_tty_index, const unsigned char* pt_tty_buf, int t_count);
int modem_rnic_write(unsigned char* pt_rnic_buf, int t_count);
unsigned int get_channel_kfifo_data_length(unsigned int t_chan_num);
void reset_channel_kfifo(unsigned int t_chan_num);
int check_software_flow_control(unsigned int t_chan_num);
int modem_channels_init(void);
void modem_channels_exit(void);


#endif
