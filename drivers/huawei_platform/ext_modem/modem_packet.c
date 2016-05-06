/*
 * modem_packet.c
 *
 * Huawei packet construct and extract driver
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
#include "modem_packet.h"
#include "via_sdio.h"
#include "4wire_wake.h"
#include "power.h"
#include "ext_modem.h"
#include "apcp_test.h"

#include "rnic_adapter.h"


#define MAX_READ_HEADER_RETRY    10
#define READ_HEADER_WAIT_TIME    100


static modem_packet_t g_mdm_pkt = {0};

/**
 * construct_packet_head - construct packet head for write data
 * @t_chan_num: channel num
 * @t_len: data length
 * @pt_head: out pointer of packet header
 *
 * Returns:
 *   none
 */
static inline void construct_packet_head(unsigned int t_chan_num, unsigned int t_len, \
        modem_packet_head_t* pt_head)
{
    pt_head->m_start_flag = 0xFE;
    pt_head->m_chanInfo = 0x0F & t_chan_num;
    pt_head->m_tranHi = 0x0F & (t_len >> 8);
    pt_head->m_tranLow = 0xFF & t_len;
}

static inline void construct_rnic_packet_head(unsigned int t_len, \
        unsigned char m_flag, unsigned char f_flag, modem_packet_head_t* pt_head)
{
    /* calculate the 4 bytes packet header */
    construct_packet_head(MODEM_CHANNEL_RNIC_NUM, t_len, pt_head);
    pt_head->m_tranHi |= (m_flag | f_flag);
}

/**
 * extract_packet_head - extract packet head from given buffer
 * @pt_buf: low-level received packet buffer include packet header
 * @pt_head: out pointer of packet header
 *
 * Returns:
 *   none
 */
static inline void extract_packet_head(unsigned char* pt_buf, modem_packet_head_t* pt_head)
{
    /* extract the packet header */
    pt_head->m_start_flag = (unsigned char)pt_buf[0];
    pt_head->m_chanInfo = 0x0F & (unsigned char)pt_buf[1];
    //this packet length is left, not todo as todo has changed.
    pt_head->m_tranHi = 0x0F & (unsigned char)pt_buf[2];
    pt_head->m_tranLow = 0xFF & (unsigned char)pt_buf[3];
}

/**
 * validate_packet_head - check if the packet head is valid
 * @t_head: pointer to packet header
 *
 * Returns:
 *   1 - packet head is valid
 *   0 - invalid packet
 */
static inline int validate_packet_head(modem_packet_head_t* pt_head)
{
    int ret = 0;

    /* check channel info */
    if ((0xFE == pt_head->m_start_flag) \
        && (pt_head->m_chanInfo < MODEM_CHANNEL_NR) \
        && (GET_PACKET_TRANSFER_DATA_LENGTH(pt_head) > 0) \
        && (GET_PACKET_TRANSFER_DATA_LENGTH(pt_head) <= MODEM_PACKET_MAX_TRANSFER_DATA_TLENGTH) \
       )
    {
        ret = 1;
    }

    return ret;
}

/**
 * extract_and_validate_packet_head - first extract the packet head, and then check if it is valid
 * @pt_buf: low-level received packet buffer include packet header
 * @pt_head: out pointer of packet header
 *
 * Returns:
 *   1 - packet head is valid
 *   0 - invalid packet
 */
static inline int extract_and_validate_packet_head(unsigned char* pt_buf, modem_packet_head_t* pt_head)
{
    int ret = 0;

    /* extract the packet header */
    extract_packet_head(pt_buf, pt_head);

    /* check if the packet is valid */
    ret = validate_packet_head(pt_head);

    return ret;
}

/**
 * construct_whole_packet_buffer - copy packet head and packet data to tx packet buffer
 * @pt_tx_pkt_buf: pointer to tx packet buffer
 * @pt_pkt_payload_buf: pointer to packet payload address
 * @pt_head: in pointer to packet header
 *
 * Returns:
 *   length of whole packet include both packet header size and packet data size
 */
static inline int construct_whole_packet_buffer(char* pt_tx_pkt_buf, char* pt_pkt_payload_buf, unsigned int t_payload_len, modem_packet_head_t* pt_head)
{
    unsigned int trans_data_len = 0; /* packet transfer data length */
    unsigned int payload_offset = GET_PACKET_PAYLOAD_OFFSET(pt_head);

    /* now copy the 4 bytes header to tx packet buffer */
    memcpy(pt_tx_pkt_buf, pt_head, sizeof(modem_packet_head_t));
    /* get packet data length from packet header */
    trans_data_len = t_payload_len;
    /* now copy the user data to tx packet buffer */
    memcpy((pt_tx_pkt_buf + sizeof(modem_packet_head_t) + payload_offset), pt_pkt_payload_buf, (trans_data_len - payload_offset));

    return (sizeof(modem_packet_head_t) + trans_data_len);
}

/**
 * get_packet_payload_buffer - get the packet payload address
 * @pt_tx_pkt_buf: pointer to tx packet buffer
 * @pt_head: in pointer to packet header
 * @ppt_pkt_payload_buf: out pointer to packet payload address
 *
 * Returns:
 *   length of packet payload
 */
static inline int get_packet_payload_buffer(char* pt_tx_pkt_buf, modem_packet_head_t* pt_head, char** ppt_pkt_payload_buf)
{
    unsigned int trans_data_len = 0; /* packet transfer data length */
    unsigned int payload_len = 0; /* packet payload length */
    unsigned int payload_offset = GET_PACKET_PAYLOAD_OFFSET(pt_head); /* payload offset in packet transfer data */

    /* get packet transfer data length from packet header */
    trans_data_len = GET_PACKET_TRANSFER_DATA_LENGTH(pt_head);
    /* calculate the packet payload buffer address */
    *ppt_pkt_payload_buf = pt_tx_pkt_buf + sizeof(modem_packet_head_t) + payload_offset;
    /* calculate payload length */
    payload_len = trans_data_len - payload_offset;

    return payload_len;
}

/**
 * modem_one_packet_write - write one packet
 * @pt_buf: high-level buffer address of packet payload data
 * @t_chan_num: channel number
 * @t_len: data length
 *
 * Returns:
 *   0 - success write whole packet
 *   minus - error occurred when write whole tx packet
 */
int modem_one_packet_write(char* pt_pkt_payload_buf, int t_pkt_payload_len, modem_packet_head_t* pt_head)
{
    modem_packet_t* p_mdm_pkt = &g_mdm_pkt;
    unsigned char* p_tx_pkt_buf = NULL; /* point to current tx packet buf */
    unsigned int cur_write_len = 0; /* current write length to the bus */
    int ret = 0;

    if (!pt_pkt_payload_buf || (t_pkt_payload_len <= 0) || !pt_head || !p_mdm_pkt || !p_mdm_pkt->pm_tx_pkt_buf)
    {
        hwlog_err("%s %d: payload buffer=0x%x, length=%d, packet header addr=0x%x, global packet addr=0x%x\n", \
                  __func__, __LINE__, pt_pkt_payload_buf, t_pkt_payload_len, pt_head, p_mdm_pkt);
        return -1;
    }

    /* point to the start address of tx packet buf */
    p_tx_pkt_buf = p_mdm_pkt->pm_tx_pkt_buf;
    /* first copy upper-layer buffer data to global tx packet buffer */
    p_mdm_pkt->m_tx_pkt_len = construct_whole_packet_buffer(p_mdm_pkt->pm_tx_pkt_buf, pt_pkt_payload_buf, t_pkt_payload_len, pt_head);
    hwlog_debug("%s %d: packet length is %d.\n", __func__, __LINE__, p_mdm_pkt->m_tx_pkt_len);

    cur_write_len = (p_mdm_pkt->m_tx_pkt_len + 3) & ~0x03;  /* Round up to nearest multiple of 4 */;
    /* print tx packet */
    apcp_txrx_buffer_count(pt_head->m_chanInfo, cur_write_len, 1);

    /* do actual bus write with max retry to write current subpacket */
    ret = modem_write(p_tx_pkt_buf, cur_write_len);

    if (ret)
    {
        hwlog_err("%s %d: retry tx error has reached MAX FAILed times.\n", __func__, __LINE__);
        return -2;
    }

    return ret;
}

/**
 * modem_write_packets - write upper layer data as packets
 * @pt_buf: high-level buffer address of packet payload data
 * @t_chan_num: channel number
 * @t_len: data length
 *
 * Returns:
 *   0 - success write all packets
 *   minus - error occurred when write tx packets
 */
int modem_write_packets(char* pt_buf, int t_len, unsigned int t_chan_num)
{
    modem_packet_head_t header = {0};
    unsigned char* p_tx_buf = NULL; /* point to current tx packet buf */
    int ret = 0;
    int data_left_len = 0; /* remain tx data length */
    int cur_data_len = 0;

    if ((NULL == pt_buf) || (t_len <= 0))
    {
        hwlog_err("%s %d: invalid parameter pt_buf=0x%x, t_len=%d\n", __func__, __LINE__, pt_buf, t_len);
        ret = -1;
        goto err_out;
    }

    p_tx_buf = pt_buf;
    data_left_len = t_len;

    while (data_left_len)
    {
        ret = check_software_flow_control(t_chan_num);

        if (ret)
        {
            hwlog_err("%s %d: channel %d has been software flow control enabled!\n", __func__, __LINE__, t_chan_num);
            ret = -1;
            goto err_out;
        }

        /* lock the modem bus before write through bus */
        ret = modem_bus_lock();

        if (ret)
        {
            ret = -2;
            goto err_out;
        }

        /* calculate current packet payload length */
        if (data_left_len >= MAX_PACKET_TRANSFER_DATA_LENGTH)
        {
            cur_data_len = MAX_PACKET_TRANSFER_DATA_LENGTH;
        }
        else if (data_left_len >= SMALL_PACKET_TRANSFER_DATA_LENGTH)
        {
            cur_data_len = SMALL_PACKET_TRANSFER_DATA_LENGTH;
        }
        else
        {
            cur_data_len = data_left_len;
        }

        construct_packet_head(t_chan_num, cur_data_len, &header);
        hwlog_debug("%s %d: packet head is [%x-%x-%x-%x]\n", __func__, __LINE__, header.m_start_flag, header.m_chanInfo, \
                    header.m_tranHi, header.m_tranLow);
        /* do actual bus write with max retry to write current subpacket */
        ret = modem_one_packet_write(p_tx_buf, cur_data_len, &header);

        if (ret)
        {
            hwlog_err("%s %d: FAILed to write current packet.\n", __func__, __LINE__);
            ret = -4;
            modem_bus_unlock();
            goto err_out;
        }

        /* recalculate remain data addr and length in txrx common buf */
        p_tx_buf += cur_data_len;
        /* refresh left tx packet length */
        data_left_len -= cur_data_len;

        /* release the modem bus after write through bus */
        modem_bus_unlock();
    }

err_out:
    /* return result of write */
    return ret;
}
EXPORT_SYMBOL(modem_write_packets);

/**
 * modem_write_rnic_packets - write upper layer data as packets
 * @pt_buf: high-level buffer address of packet payload data
 * @t_chan_num: channel number
 * @t_len: data length
 *
 * Returns:
 *   0 - success write all packets
 *   minus - error occurred when write tx packets
 */
int modem_write_rnic_packets(char* pt_buf, int t_len, unsigned int t_chan_num)
{
    unsigned char* p_tx_buf = NULL; /* point to current tx packet buf */
    modem_packet_head_t header = {0};
    int ret = 0;
    int data_left_len = 0; /* remain tx data length */
    int cur_data_len = 0;
    unsigned char f_flag = 0;
    unsigned char m_flag = 0;
    int isInBlockSize = 0;
    int isFirstBlock = 0;
    unsigned int data_size = 0;

    if (NULL == pt_buf)
    {
        hwlog_err("%s %d: NULL pointer!\n", __func__, __LINE__);
        ret = -1;
        goto err_out;
    }

    p_tx_buf = pt_buf;
    data_left_len = t_len;

    ret = check_software_flow_control(t_chan_num);

    if (ret)
    {
        hwlog_err("%s %d: channel %d has been software flow control enabled!\n", __func__, __LINE__, t_chan_num);
        ret = -1;
        goto err_out;
    }

    /* lock the modem bus before write through bus */
    ret = modem_bus_lock();

    if (ret)
    {
        ret = -2;
        goto err_out;
    }

    while (data_left_len)
    {
        f_flag = 0;
        m_flag = 0;

        //in this condition, it's the first segment
        if (0 == cur_data_len)
        {
            f_flag = SDIO_SLAVE_ETH_F_BIT;
            isFirstBlock = true;
        }
        else
        {
            isFirstBlock = false;

            if (isInBlockSize)
            {
                f_flag = SDIO_SLAVE_ETH_F_BIT;
                isInBlockSize = false;
            }
        }

        m_flag = SDIO_SLAVE_ETH_M_BIT;

        /* calculate current packet payload length */
        if (data_left_len > MAX_PACKET_TRANSFER_DATA_LENGTH)
        {
            cur_data_len = MAX_PACKET_TRANSFER_DATA_LENGTH;
        }
        else if (data_left_len > SMALL_PACKET_TRANSFER_DATA_LENGTH)
        {
            cur_data_len = SMALL_PACKET_TRANSFER_DATA_LENGTH;
            isInBlockSize = true;
        }
        else
        {
            cur_data_len = data_left_len;
            m_flag = 0;
        }

        if (isFirstBlock)
        {
            data_size = t_len;
        }
        else
        {
            data_size = cur_data_len;
        }

        hwlog_debug("RNIC__ %s: ip packet size= %d \n", __func__, t_len);

        construct_rnic_packet_head(data_size, m_flag, f_flag, &header);
        /* do actual bus write with max retry to write current subpacket */
        ret = modem_one_packet_write(p_tx_buf, cur_data_len, &header);

        if (ret)
        {
            hwlog_err("%s %d: FAILed to write current packet.\n", __func__, __LINE__);
            ret = -4;
            modem_bus_unlock();
            goto err_out;
        }

        /* recalculate remain data addr and length in txrx common buf */
        p_tx_buf += cur_data_len;
        /* refresh left tx packet length */
        data_left_len -= cur_data_len;
    }

    /* release the modem bus after write through bus */
    modem_bus_unlock();

err_out:
    /* return result of write */
    return ret;
}
EXPORT_SYMBOL(modem_write_rnic_packets);

/**
 * read_and_validate_packet_header - read packet head with retry when packet head is invalid
 * @pt_head: low-level received packet head
 *
 * Returns:
 *   0 - success, packet head is valid at result
 *   minus - invalid packet in all retry read
 */
int read_and_validate_packet_header(modem_packet_head_t* pt_head)
{
    int ret = 0;
    unsigned char header_retry = 0;

    do
    {
        /* read the packet header which include packet payload length information */
        modem_read((char*)pt_head, 1, sizeof(modem_packet_head_t), sizeof(modem_packet_head_t));

        /* check if the packet head is valid */
        ret = validate_packet_head(pt_head);

        /* judeg the packet head check result */
        if (ret)
        {
            //hwlog_debug("%s %d: packet head is ok. channel is %d, transfer data len is %d\n",
            //    __func__, __LINE__, GET_CHANNEL_NUMBER(pt_head), GET_PACKET_TRANSFER_DATA_LENGTH(pt_head));
            break;
        }
        else
        {
            hwlog_err("%s %d: packet header is invalid. start flag=0x%x, channel=%d, transfer data len is %d\n",
                      __func__, __LINE__, GET_START_FLAG(pt_head), GET_CHANNEL_NUMBER(pt_head), GET_PACKET_TRANSFER_DATA_LENGTH(pt_head));
            mdelay(READ_HEADER_WAIT_TIME);
        }

        header_retry++;
    }
    while (header_retry < MAX_READ_HEADER_RETRY);

    if (header_retry >= MAX_READ_HEADER_RETRY)
    {
        hwlog_err("%s %d: read invalid packet header reach MAX retry times\n", __func__, __LINE__);
        return -1;
    }

    return 0;
}

/**
 * modem_one_packet_read - read one packet from modem bus
 * @pt_buf: buffer address of packet payload data
 * @t_len: data length
 *
 * Returns:
 *   0 - success write whole packet
 *   minus - error occurred when write whole tx packet
 */
int modem_one_packet_read(int t_given_pkt_len)
{
    unsigned char* p_cur_buf = NULL; /* point to current available space for write in txrx common buf */
    int ret = 0;
    modem_packet_head_t pkt_hdr = {0}; /* packet header for received packet */
    unsigned int cur_read_len = 0;
    char* pkt_payload_buf = NULL; /* point to packet payload address */
    int read_length = 0;
    int is_header_valid = 0;
    int chan_num = 0;
    int need_extract_head = 0; /* if need to extract packet header from data */

    if (t_given_pkt_len < 0)
    {
        hwlog_err("%s %d packet length %d is invalid", __func__, __LINE__, t_given_pkt_len);
        ret = -1;
        goto out;
    }

    //only clear the txrx common buffer for first packet.
    memset(g_mdm_pkt.pm_rx_pkt_buf, 0, PAGE_SIZE);

    /* get the current available buffer address */
    p_cur_buf = g_mdm_pkt.pm_rx_pkt_buf;
    hwlog_debug("%s %d: read packet buf addr=0x%x, len=%d\n", __func__, __LINE__, (unsigned int)p_cur_buf, t_given_pkt_len);

    /* read packet header if not given packet length */
    if (0 == t_given_pkt_len)
    {
        /* read the packet header */
        ret = read_and_validate_packet_header(&pkt_hdr);

        if (ret)
        {
            hwlog_err("%s %d: can not read packet head after MAX retry.\n", __func__, __LINE__);
            ret = -2;
            goto out;
        }

        p_cur_buf = g_mdm_pkt.pm_rx_pkt_buf + sizeof(modem_packet_head_t);
        /* calculate packet payload length form packet header */
        cur_read_len = GET_PACKET_TRANSFER_DATA_LENGTH((&pkt_hdr));
        need_extract_head = 0; /* packet header had already been read */
    }
    else
    {
        p_cur_buf = g_mdm_pkt.pm_rx_pkt_buf;
        cur_read_len = t_given_pkt_len;
        need_extract_head = 1;
    }

    cur_read_len = (cur_read_len + 3) & ~0x03;  /* Round up to nearest multiple of 4 */

    /* read the packet */
    ret = modem_read(p_cur_buf, need_extract_head, sizeof(modem_packet_head_t), cur_read_len);

    /* judge if read the first subpacket success */
    if (ret)
    {
        hwlog_err("%s %d: can not read packet data.\n", __func__, __LINE__);
        ret = -3;
        goto out;
    }

    if (need_extract_head)
    {
        is_header_valid = extract_and_validate_packet_head(g_mdm_pkt.pm_rx_pkt_buf, &pkt_hdr);

        if (0 == is_header_valid)
        {
            hwlog_err("%s %d: read packet header is invalid!\n", __func__, __LINE__);
            apcp_current_subpacket_printk(g_mdm_pkt.pm_rx_pkt_buf, 24, 0, 0);
            ret = -4;
            goto out;
        }
    }

    /* complete read whole packet, must use the pointer to pointer get the packet payload address */
    read_length = get_packet_payload_buffer(g_mdm_pkt.pm_rx_pkt_buf, &pkt_hdr, &pkt_payload_buf);
    chan_num = GET_CHANNEL_NUMBER((&pkt_hdr));

    /* then push packet payload to upper-layer */
    modem_channel_push(pkt_payload_buf, chan_num, read_length, g_mdm_pkt.pm_rx_pkt_buf[2]);

out:
    return ret;
}
EXPORT_SYMBOL(modem_one_packet_read);

int modem_packet_init(void)
{
    int ret = 0;

    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);

    /* get page buffer for rx packet */
    g_mdm_pkt.pm_rx_pkt_buf = (char*)__get_free_pages(GFP_KERNEL, 0);

    if (!g_mdm_pkt.pm_rx_pkt_buf)
    {
        hwlog_err("%s %d: request rx packet page memory error", __func__, __LINE__);
        return -ENOMEM;
    }

    /* get page buffer for tx packet */
    g_mdm_pkt.pm_tx_pkt_buf = (char*)__get_free_pages(GFP_KERNEL, 0);

    if (!g_mdm_pkt.pm_tx_pkt_buf)
    {
        hwlog_err("%s %d: request tx packet page memory error", __func__, __LINE__);
        ret = -1;
        goto err_free_rx_buf;
    }

    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    /* initialize complete, return success */
    return ret;

err_free_rx_buf:
    free_pages((unsigned long) g_mdm_pkt.pm_rx_pkt_buf, 0);

    return ret;
}
EXPORT_SYMBOL(modem_packet_init);

void modem_packet_exit(void)
{
    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);

    if (g_mdm_pkt.pm_rx_pkt_buf)
    {
        free_pages((unsigned long) g_mdm_pkt.pm_rx_pkt_buf, 0);
    }

    if (g_mdm_pkt.pm_tx_pkt_buf)
    {
        free_pages((unsigned long)g_mdm_pkt.pm_tx_pkt_buf, 0);
    }

    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
}
EXPORT_SYMBOL(modem_packet_exit);

