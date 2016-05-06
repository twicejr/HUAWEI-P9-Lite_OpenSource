/*
 * modem_ttys.h
 *
 */
#ifndef MODEM_TTYS_H
#define MODEM_TTYS_H

#include <linux/kref.h>
#include <linux/tty.h>
#include <linux/tty_flip.h>
#include <linux/mutex.h>
#include <linux/list.h>
#include <linux/kfifo.h>


#define MODEM_TTY_WAKEUP_CHARS    8*256


/*MODEM tty buffer in lens*/
#define MODEM_PPP_BUF_IN_MAX_NUM    100
#define MODEM_ETS_BUF_IN_MAX_NUM    500
#define MODEM_IFS_BUF_IN_MAX_NUM    100
#define MODEM_AT_BUF_IN_MAX_NUM     100
#define MODEM_PCV_BUF_IN_MAX_NUM    100
#define MODEM_DEF_BUF_IN_MAX_NUM    100
#define MODEM_BUF_IN_MAX_SIZE       64512     /*max buffer in size = 63K*/

typedef enum
{
    MODEM_TTY_RESERVED_1_NUM    = 0,
    MODEM_TTY_ETS_NUM,
    MODEM_TTY_FLASHLESS_NUM,
    MODEM_TTY_AT_PC_NUM,
    MODEM_TTY_AT_PCVOICE_NUM,
    MODEM_TTY_AT_AGPS_NUM,
    MODEM_TTY_AT_FT_NUM,        //ttySPI6 is for ProjectMenu
    MODEM_TTY_RILD_MMC_NUM,     //ttySPI7 transfer rild MMC command which are hex, not ASCI char.
    MODEM_TTY_AT_UICC_NUM,      //ttySPI8 is for UICC
    MODEM_TTY_AT_RILD1_NUM,
    MODEM_TTY_AT_RILD2_NUM,
    MODEM_TTY_AT_LOGTOOL_NUM,   //ttySPI11 is for modemlogcat_via
    MODEM_TTY_RESERVED_2_NUM,
    MODEM_TTY_RESERVED_3_NUM,
    MODEM_TTY_NR                //14 - Number of ttyVIA this driver can handle
} MODEM_TTY_NUM;

struct modem_buf_in_packet
{
    struct list_head     m_node;
    unsigned int        m_size;
    unsigned char*        pm_buffer;
};

struct modem_tty_dev
{
    struct kref        m_kref;
    struct tty_port    m_tty_port;
    struct tty_struct*  pm_tty;
    unsigned int       m_tty_index;

    unsigned int       m_wr_left_len;

    struct mutex       m_buf_in_mutex;
    struct list_head   m_buf_in_list;
    unsigned int       m_buf_in_num;    /*buffer in list num*/
    unsigned int       m_buf_in_maxnum;    /*buffer in list max num*/
    unsigned int       m_buf_in_size;    /*buffer in size*/
};

struct modem_ttys_mgmt
{
    struct tty_driver* pm_tty_drv;
    struct modem_tty_dev* pm_tty_devs[MODEM_TTY_NR];
    unsigned int m_tx_data_length;
};


int modem_tty_push(int t_tty_index, unsigned char* pt_payload_buf, int t_payload_len);
void modem_tty_devs_reset(void);
void modem_tty_wakeup(unsigned int t_tty_index);
int modem_ttys_init(void);
void modem_ttys_exit(void);


#endif
